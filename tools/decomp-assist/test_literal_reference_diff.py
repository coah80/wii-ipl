import contextlib
from dataclasses import replace
import io
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

import jump_table_diff as jump
import literal_reference_diff as tool


def words(*values):
    return b"".join(struct.pack(">I", value) for value in values)


def fixture(value=b"P_prdc_scrl_Left\0", code=None, call_offsets=(8,),
            text_id=1, data_id=2, function_offset=0, data_offset=0,
            references=None):
    code = code or words(0x3c800000, 0x38840000, 0x48000001, 0x4e800020)
    data = b"\0" * data_offset + value
    symbols = [jump.Symbol("dispatch", text_id, function_offset, len(code), "STT_FUNC"),
               jump.Symbol("literal", data_id, data_offset, len(value)),
               jump.Symbol("consume", "SHN_UNDEF", 0, 0, "STT_FUNC")]
    relocations = {text_id: {
        function_offset + 2: jump.Relocation(function_offset + 2, 6, 1, 0),
        function_offset + 6: jump.Relocation(function_offset + 6, 4, 1, 0),
    }}
    if references is not None:
        relocations[text_id] = {function_offset + at: jump.Relocation(
            function_offset + at, kind, 1, addend) for at, kind, addend in references}
    for at in call_offsets:
        relocations[text_id][function_offset + at] = jump.Relocation(
            function_offset + at, 10, 2, 0)
    sections = {text_id: (".text", function_offset + len(code)),
                data_id: (".data", len(data))}
    return tool.LiteralObject(jump.ObjectInfo(sections, symbols, relocations),
                              {text_id: b"\0" * function_offset + code, data_id: data})


def compare(source, reference=None):
    return tool.compare_function(source, reference or fixture(), "dispatch")


class LiteralReferenceTests(unittest.TestCase):
    def test_equal_value_with_different_section_ids_and_offsets(self):
        source = fixture(text_id=4, data_id=7, function_offset=0x40, data_offset=0x20)
        self.assertEqual(compare(source), (1, [], None))

    def test_detects_different_literal_despite_identical_code(self):
        source = fixture(b"wrong_pane\0")
        checked, differences, skipped = compare(source)
        self.assertEqual(checked, 1)
        self.assertIsNone(skipped)
        self.assertEqual(differences[0]["expected"], "P_prdc_scrl_Left")
        self.assertEqual(differences[0]["actual"], "wrong_pane")

    def test_source_empty_string_is_not_silently_ignored(self):
        self.assertEqual(compare(fixture(b"\0"))[1][0]["actual_hex"], "")

    def test_fixed_width_record_regression(self):
        names = [b"B_OffBtn", b"P_JPOffBtn", b"P_CNOffBtn", b"P_CNOnBtn",
                 b"B_prdc_scrl_Left", b"P_prdc_scrl_Left",
                 b"B_prdc_scrl_Rght", b"P_prdc_scrl_Rght"]
        widths = [12] * 4 + [20] * 4
        correct = b"".join(n.ljust(w, b"\0") for n, w in zip(names, widths)).ljust(132, b"\0")
        broken = b"".join(n.ljust(w - 1, b"\0") for n, w in zip(names, widths)).ljust(132, b"\0")
        code = words(0x3fe00000, 0x3bff0000, 0x389f0044, 0x48000001,
                     0x389f006c, 0x48000001, 0x4e800020)
        expected = fixture(correct, code, (12, 20))
        actual = fixture(broken, code, (12, 20))
        self.assertEqual(len(correct), len(broken))
        self.assertEqual(correct.count(0), broken.count(0))
        checked, differences, _ = compare(actual, expected)
        self.assertEqual(checked, 2)
        self.assertEqual([d["actual"] for d in differences], ["c_scrl_Left", "scrl_Rght"])
        self.assertEqual(compare(expected, expected), (2, [], None))

    def test_nonvolatile_base_survives_call(self):
        code = words(0x3fe00000, 0x3bff0000, 0x389f0000, 0x48000001,
                     0x389f0000, 0x48000001, 0x4e800020)
        obj = fixture(code=code, call_offsets=(12, 20))
        self.assertEqual(compare(obj, obj), (2, [], None))

    def test_volatile_argument_does_not_survive_call(self):
        obj = fixture(code=words(0x3c800000, 0x38840000, 0x48000001,
                                 0x48000001, 0x4e800020), call_offsets=(8, 12))
        self.assertEqual(compare(obj, obj), (1, [], None))

    def test_move_propagates_address(self):
        code = words(0x3fe00000, 0x3bff0000, 0x7fe4fb78, 0x48000001, 0x4e800020)
        obj = fixture(code=code, call_offsets=(12,))
        self.assertEqual(compare(obj, obj), (1, [], None))

    def test_sda21_literal_address(self):
        obj = fixture(code=words(0x38800000, 0x48000001, 0x4e800020),
                      call_offsets=(4,), references=[(0, 109, 0)])
        self.assertEqual(compare(obj, obj), (1, [], None))

    def test_high_half_alone_is_not_a_pointer(self):
        obj = fixture(code=words(0x3c800000, 0x48000001, 0x4e800020),
                      call_offsets=(4,), references=[(2, 6, 0)])
        self.assertEqual(compare(obj, obj), (0, [], None))

    def test_section_relative_literal_symbol(self):
        obj = fixture(data_offset=0x40)
        obj.info.symbols[1] = jump.Symbol("", 2, 0, 0, "STT_SECTION")
        for at in (2, 6):
            obj.info.relocations[1][at] = replace(obj.info.relocations[1][at], addend=0x40)
        self.assertEqual(compare(obj), (1, [], None))

    def test_no_assumption_of_unique_section_names(self):
        obj = fixture(text_id=3, data_id=4)
        obj.info.sections[1] = (".text", 16)
        obj.data[1] = words(0, 0, 0, 0)
        self.assertEqual(compare(obj), (1, [], None))

    def test_cntlzw_invalidates_its_actual_destination(self):
        code = words(0x3c800000, 0x38840000, 0x7ca40034, 0x48000001, 0x4e800020)
        obj = fixture(code=code, call_offsets=(12,))
        self.assertEqual(compare(obj, obj), (0, [], None))

    def test_paired_single_update_cannot_leave_a_stale_base(self):
        obj = fixture()
        fn = obj.info.symbol("dispatch")
        pointer = ("address", 2, 0)
        state = tool.transfer(obj, fn, 0, (4 << 26) | (31 << 16) | 38,
                              {31: pointer, 30: pointer})
        self.assertNotIn(31, state)
        self.assertEqual(state[30], pointer)

    def test_does_not_dereference_mutable_pointer_globals(self):
        code = words(0x3c800000, 0x38840000, 0x80840000, 0x48000001, 0x4e800020)
        obj = fixture(code=code, call_offsets=(12,))
        self.assertEqual(compare(obj, obj), (0, [], None))

    def test_relocated_data_word_is_not_character_bytes(self):
        obj = fixture(b"ABCDEFG\0")
        obj.info.relocations[2] = {0: jump.Relocation(0, 1, 0, 0)}
        self.assertEqual(compare(obj, obj), (0, [], None))

    def test_unterminated_and_control_data_are_not_strings(self):
        for value in (b"unterminated", b"a\x01b\0"):
            obj = fixture(value)
            self.assertEqual(compare(obj, obj), (0, [], None))

    def test_negative_and_out_of_bounds_addresses_are_not_strings(self):
        obj = fixture()
        for offset in (-1, 999):
            self.assertIsNone(obj.string(("address", 2, offset)))

    def test_different_callees_are_not_compared(self):
        obj = fixture(b"different\0")
        obj.info.symbols[2] = replace(obj.info.symbols[2], name="other_consumer")
        self.assertEqual(compare(obj), (0, [], None))

    def test_named_direct_tail_call_is_observed(self):
        obj = fixture(code=words(0x3c800000, 0x38840000, 0x48000000),
                      call_offsets=(8,))
        self.assertEqual(compare(obj, obj), (1, [], None))

    def test_internal_branch_is_not_misclassified_as_tail_call(self):
        obj = fixture(code=words(0x3c800000, 0x38840000, 0x48000000),
                      call_offsets=(8,))
        obj.info.relocations[1][8] = jump.Relocation(8, 10, 0, 0)
        self.assertEqual(compare(obj, obj), (0, [], None))

    def test_indirect_call_is_observed(self):
        obj = fixture(code=words(0x3c800000, 0x38840000, 0x4e800421, 0x4e800020),
                      call_offsets=())
        self.assertEqual(compare(obj, obj), (1, [], None))

    def branch_fixture(self, second_offset):
        code = words(0x3fe00000, 0x3bff0000, 0x4182000c, 0x389f0000,
                     0x48000008, 0x389f0000 | second_offset, 0x48000001, 0x4e800020)
        return fixture(b"first\0\0\0second\0", code, (24,))

    def test_conflicting_control_flow_addresses_are_unknown(self):
        obj = self.branch_fixture(8)
        self.assertEqual(compare(obj, obj), (0, [], None))

    def test_identical_control_flow_addresses_are_retained(self):
        obj = self.branch_fixture(0)
        self.assertEqual(compare(obj, obj), (1, [], None))

    def test_backward_loop_converges(self):
        code = words(0x3fe00000, 0x3bff0000, 0x389f0000,
                     0x48000001, 0x4082fff8, 0x4e800020)
        obj = fixture(code=code, call_offsets=(12,))
        self.assertEqual(compare(obj, obj), (1, [], None))

    def test_conditional_return_keeps_fallthrough(self):
        code = words(0x3c800000, 0x38840000, 0x4d820020, 0x48000001, 0x4e800020)
        obj = fixture(code=code, call_offsets=(12,))
        self.assertEqual(compare(obj, obj), (1, [], None))

    def test_unconditional_branch_skips_dead_call(self):
        code = words(0x3c800000, 0x38840000, 0x42800008, 0x48000001, 0x4e800020)
        obj = fixture(code=code, call_offsets=(12,))
        self.assertEqual(compare(obj, obj), (0, [], None))

    def test_different_function_sizes_are_reported_as_skipped(self):
        obj = fixture(code=words(0x3c800000, 0x38840000, 0x48000001, 0x60000000, 0x4e800020))
        self.assertEqual(compare(obj), (0, [], "different function sizes"))

    def test_duplicate_function_is_invalid(self):
        obj = fixture()
        obj.info.symbols.append(obj.info.symbols[0])
        with self.assertRaisesRegex(ValueError, "one defined symbol"):
            compare(obj)

    def test_invalid_code_extent_is_rejected(self):
        obj = fixture()
        obj.data[1] = b""
        with self.assertRaisesRegex(ValueError, "code is unavailable"):
            compare(obj)

    def test_conditional_link_is_explicitly_unsupported(self):
        obj = fixture(code=words(0x41820009, 0x60000000, 0x4e800020),
                      call_offsets=(), references=[])
        with self.assertRaisesRegex(ValueError, "branch-and-link"):
            compare(obj, obj)

    def test_switch_table_targets_are_reached(self):
        code = words(0x3fe00000, 0x3bff0000, 0x4e800420,
                     0x389f0000, 0x48000001, 0x4e800020,
                     0x389f0008, 0x48000001, 0x4e800020)
        obj = fixture(b"first\0\0\0second\0\0\0" + bytes(8), code, (16, 28))
        obj.info.symbols.append(jump.Symbol("jumptable_case", 2, 16, 8))
        obj.info.relocations[2] = {
            16: jump.Relocation(16, 1, 0, 12),
            20: jump.Relocation(20, 1, 0, 24),
        }
        self.assertEqual(compare(obj, obj), (2, [], None))

    def test_bad_relocation_index_is_invalid(self):
        obj = fixture()
        obj.info.relocations[1][2] = replace(obj.info.relocations[1][2], symbol=999)
        with self.assertRaisesRegex(ValueError, "symbol index"):
            compare(obj)

    def test_shift_jis_bytes_are_preserved(self):
        obj = fixture(bytes.fromhex("837483408343838b96bc82cc89fce28282f08c9f8f6f0a00"))
        self.assertEqual(compare(obj, obj), (1, [], None))

    def test_automatic_missing_name_is_disclosed_not_guessed(self):
        with tempfile.TemporaryDirectory() as directory:
            report = Path(directory) / "report.json"
            report.write_text(json.dumps({"units": [{"name": "main/demo", "functions": [
                {"name": "compiler_alias", "fuzzy_match_percent": 100}]}]}))
            output = io.StringIO()
            with patch.object(tool, "read_object", return_value=fixture()), contextlib.redirect_stdout(output):
                result = tool.main(["demo", "--report", str(report)])
            self.assertEqual(result, 0)
            parsed = json.loads(output.getvalue())
            self.assertEqual(parsed["checked_arguments"], 0)
            self.assertEqual(len(parsed["skipped_functions"]), 1)
            output = io.StringIO()
            with patch.object(tool, "read_object", return_value=fixture()), contextlib.redirect_stdout(output):
                result = tool.main(["demo", "--report", str(report), "--function", "compiler_alias"])
            self.assertEqual(result, 2)

    def test_cli_reports_candidates_and_nonzero_exit(self):
        with tempfile.TemporaryDirectory() as directory:
            report = Path(directory) / "report.json"
            report.write_text(json.dumps({"units": [{"name": "main/demo", "functions": [
                {"name": "dispatch", "fuzzy_match_percent": 100}]}]}))
            output = io.StringIO()
            def read(path):
                return fixture(b"wrong\0") if "src" in path.parts else fixture()
            with patch.object(tool, "read_object", side_effect=read), contextlib.redirect_stdout(output):
                result = tool.main(["demo", "--report", str(report)])
            self.assertEqual(result, 1)
            self.assertEqual(len(json.loads(output.getvalue())["candidates"]), 1)

    def test_rejects_unsafe_unit_paths(self):
        for name in ("../outside", "/absolute"):
            with self.assertRaisesRegex(ValueError, "relative unit"):
                tool.unit_path(name)


if __name__ == "__main__":
    unittest.main()
