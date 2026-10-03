"""Authored synthetic PPC/ELF/DOL fixtures only; no original executable bytes."""
import contextlib
import hashlib
import io
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

import call_target_diff as tool

BASE = 0x80001000
BLR = 0x4E800020
LI_ONE = 0x38600001
LI_TWO = 0x38600002


def put_word(data, offset, word):
    data[offset:offset + 4] = word.to_bytes(4, "big")


def bl(address, destination, absolute=False):
    displacement = destination if absolute else destination - address
    return 0x48000001 | (displacement & 0x03FFFFFC) | (2 if absolute else 0)


def make_elf(text, symbols, relocations):
    """Minimal ELF32 big-endian PowerPC relocatable, built from authored fields."""
    strings = bytearray(b"\0")
    symbol_data = bytearray(16)
    for name, value, size, section, kind in symbols:
        name_offset = len(strings)
        strings.extend(name.encode() + b"\0")
        symbol_data.extend(struct.pack(">IIIBBH", name_offset, value, size,
                                       0x10 | kind, 0, section))
    relocation_data = b"".join(struct.pack(">IIi", offset, index << 8 | kind, addend)
                               for offset, index, kind, addend in relocations)
    section_names = b"\0.text\0.symtab\0.strtab\0.rela.text\0.shstrtab\0"
    entries = [("", 0, 0, b"", 0, 0, 0),
               (".text", 1, 6, bytes(text), 0, 0, 0),
               (".symtab", 2, 0, bytes(symbol_data), 3, 1, 16),
               (".strtab", 3, 0, bytes(strings), 0, 0, 0),
               (".rela.text", 4, 0, relocation_data, 2, 1, 12),
               (".shstrtab", 3, 0, section_names, 0, 0, 0)]
    raw = bytearray(52)
    headers = []
    for name, kind, flags, data, link, info, item_size in entries:
        while len(raw) % 4:
            raw.append(0)
        offset = len(raw) if data else 0
        raw.extend(data)
        headers.append(struct.pack(">10I", section_names.index(name.encode() + b"\0"),
                                   kind, flags, 0, offset, len(data), link, info,
                                   4 if name else 0, item_size))
    while len(raw) % 4:
        raw.append(0)
    section_offset = len(raw)
    raw.extend(b"".join(headers))
    ident = b"\x7fELF\x01\x02\x01" + bytes(9)
    raw[:52] = ident + struct.pack(">HHIIIIIHHHHHH", 1, 20, 1, 0, 0,
                                   section_offset, 0, 52, 0, 0, 40, 6, 5)
    return bytes(raw)


def make_dol(text):
    header = [0] * 64
    header[0], header[18], header[36] = 256, BASE, len(text)
    return struct.pack(">64I", *header) + bytes(text)


def fixture(root, source_call="B", source_raw=False, reference_raw=False,
            source_start=0x20, alias_body=False, renamed=False, score=100, size=8):
    text = bytearray(0x80)
    for offset, value in [(0, LI_ONE), (4, BLR), (8, LI_ONE if alias_body else LI_TWO),
                          (12, BLR), (0x24, BLR)]:
        put_word(text, offset, value)
    reference_text = bytearray(text)
    put_word(reference_text, 0x20, bl(0x20, 8) if reference_raw else bl(0, 0))
    source_text = bytearray(text)
    put_word(source_text, source_start + 4, BLR)
    destination = 0 if source_call == "A" else 8
    put_word(source_text, source_start,
             bl(source_start, destination) if source_raw else bl(0, 0))
    symbols = [("A", 0, 8, 1, 2), ("B", 8, 8, 1, 2), ("caller", 0x20, 8, 1, 2)]
    source_symbols = [("renamed" if renamed and n == source_call else n,
                       source_start if n == "caller" else v,
                       size if n == "caller" else length, sec, kind)
                      for n, v, length, sec, kind in symbols]
    source_relocs = [] if source_raw else [(source_start, 1 if source_call == "A" else 2, 10, 0)]
    reference_relocs = [] if reference_raw else [(0x20, 2, 10, 0)]
    source = root / "build/43U/src/toy.o"
    reference = root / "build/43U/obj/toy.o"
    for path, data in [(source, make_elf(source_text, source_symbols, source_relocs)),
                       (reference, make_elf(reference_text, symbols, reference_relocs))]:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(data)
    put_word(text, 0x20, bl(BASE + 0x20, BASE + 8))
    dol = root / "original.dol"
    dol.write_bytes(make_dol(text))
    report = {"units": [{"name": "main/toy", "functions": [
        {"name": "caller", "fuzzy_match_percent": score}],
        "metadata": {"source_path": "toy.c"}}]}
    report_path = root / "build/43U/report.json"
    report_path.write_text(json.dumps(report))
    config = root / "config/43U"
    config.mkdir(parents=True, exist_ok=True)
    (config / "symbols.txt").write_text(
        "A = .text:0x80001000; // type:function size:0x8\n"
        "B = .text:0x80001008; // type:function size:0x8\n"
        "caller = .text:0x80001020; // type:function size:0x8\n")
    (config / "splits.txt").write_text("toy.c:\n\t.text start:0x80001000 end:0x80001080\n")
    return report_path, dol, hashlib.sha1(dol.read_bytes()).hexdigest()


class CallTargetTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)

    def run_fixture(self, **options):
        report, dol, sha = fixture(self.root, **options)
        return tool.audit(self.root, report, dol, sha)

    def test_relocated_destination_matches_original_dol(self):
        result, status = self.run_fixture()
        self.assertEqual(status, 0)
        self.assertEqual(result["counts"]["same_destination"], 1)
        self.assertIn(str(self.root / "build/43U/src/toy.o"), result["provenance"]["sha256"])

    def test_wrong_callee_detected_despite_identical_relocated_call_bytes(self):
        result, status = self.run_fixture(source_call="A")
        self.assertEqual(status, 1)
        row = result["rows"][0]
        self.assertEqual(row["classification"], "different_destination")
        self.assertEqual(row["source_addresses"], [BASE])
        self.assertEqual(row["dol_destination"], BASE + 8)
        self.assertIsNone(row["alias_hint"])

    def test_raw_local_calls_with_shifted_source_function(self):
        result, status = self.run_fixture(source_raw=True, reference_raw=True, source_start=0x40)
        self.assertEqual(status, 0)
        self.assertEqual(result["counts"]["source_raw_relative"], 1)
        self.assertEqual(result["counts"]["reference_raw_relative"], 1)

    def rewrite_source(self, symbols, relocations):
        text = bytearray(0x80)
        for offset, word in [(0, LI_ONE), (4, BLR), (8, LI_TWO),
                             (12, BLR), (0x20, bl(0, 0)), (0x24, BLR)]:
            put_word(text, offset, word)
        (self.root / "build/43U/src/toy.o").write_bytes(make_elf(text, symbols, relocations))

    def test_section_symbol_relocation_resolves_actual_function_start(self):
        report, dol, sha = fixture(self.root)
        self.rewrite_source([("A", 0, 8, 1, 2), ("B", 8, 8, 1, 2),
                             ("caller", 0x20, 8, 1, 2), ("", 0, 0, 1, 3)],
                            [(0x20, 4, 10, 8)])
        result, status = tool.audit(self.root, report, dol, sha)
        self.assertEqual(status, 0)
        self.assertEqual(result["counts"]["same_destination"], 1)

    def test_same_address_alias_is_visible_without_claiming_a_bug(self):
        report, dol, sha = fixture(self.root)
        self.rewrite_source([("A", 0, 8, 1, 2), ("alias", 0, 0, 0, 2),
                             ("caller", 0x20, 8, 1, 2)], [(0x20, 2, 10, 0)])
        with (self.root / "config/43U/symbols.txt").open("a") as stream:
            stream.write("alias = .text:0x80001008; // type:function size:0x8\n")
        result, status = tool.audit(self.root, report, dol, sha)
        self.assertEqual(status, 1)
        self.assertEqual(result["rows"][0]["classification"], "same_address_alias")

    def test_unknown_external_symbol_is_unresolved_not_guessed(self):
        report, dol, sha = fixture(self.root)
        self.rewrite_source([("A", 0, 8, 1, 2), ("unknown", 0, 0, 0, 2),
                             ("caller", 0x20, 8, 1, 2)], [(0x20, 2, 10, 0)])
        result, status = tool.audit(self.root, report, dol, sha)
        self.assertEqual(status, 1)
        self.assertEqual(result["rows"][0]["classification"], "unresolved_destination")
        self.assertEqual(result["rows"][0]["source_addresses"], [])

    def test_wrong_relocation_kind_or_symbol_is_an_input_error(self):
        for index, kind in [(2, 1), (99, 10)]:
            with self.subTest(index=index, kind=kind):
                report, dol, sha = fixture(self.root)
                self.rewrite_source([("A", 0, 8, 1, 2), ("B", 8, 8, 1, 2),
                                     ("caller", 0x20, 8, 1, 2)], [(0x20, index, kind, 0)])
                result, status = tool.audit(self.root, report, dol, sha)
                self.assertEqual(status, 2)
                self.assertTrue(result["errors"])

    def test_wrong_raw_local_callee_detected(self):
        result, status = self.run_fixture(source_call="A", source_raw=True)
        self.assertEqual(status, 1)
        self.assertEqual(result["rows"][0]["source"]["names"], ["A"])

    def test_decoder_signed_absolute_and_non_call_cases(self):
        self.assertEqual(tool.branch_target(bl(0x20, 0), 0x20), 0)
        self.assertEqual(tool.branch_target(bl(0x20, 0x40), 0x20), 0x40)
        self.assertEqual(tool.branch_target(bl(0, 8, True), 0x100), 8)
        self.assertEqual(tool.branch_target(bl(0, -4, True), 0), 0xFFFFFFFC)
        self.assertIsNone(tool.branch_target(0x48000010, 0))  # tail branch
        self.assertIsNone(tool.branch_target(0x4E800421, 0))  # indirect bctrl

    def test_raw_interior_destination_retains_addend(self):
        report, dol, sha = fixture(self.root, source_raw=True)
        obj = tool.read_object(self.root / "build/43U/src/toy.o", tool.Inputs())
        data = bytearray(obj.data[1])
        put_word(data, 0x20, bl(0x20, 12))
        obj.data[1] = bytes(data)
        destination = obj.call(obj.function("caller"), 0)
        self.assertEqual((destination["names"], destination["addend"]), (["B"], 4))

    def test_renamed_relocation_free_wrapper_is_retained_for_review(self):
        result, status = self.run_fixture(renamed=True)
        self.assertEqual(status, 1)
        self.assertEqual(result["rows"][0]["classification"], "unresolved_destination")
        self.assertIn("identical_relocation_free_local_body", result["rows"][0]["alias_hint"])

    def test_identical_original_bodies_do_not_silently_suppress_names(self):
        result, status = self.run_fixture(source_call="A", alias_body=True)
        self.assertEqual(status, 1)
        self.assertEqual(result["rows"][0]["classification"], "different_destination")
        self.assertIn("identical_original_leaf_bodies", result["rows"][0]["alias_hint"])

    def test_nonexact_function_is_not_audited(self):
        result, status = self.run_fixture(score=99.9)
        self.assertEqual(status, 0)
        self.assertEqual(result["counts"].get("calls", 0), 0)

    def test_unequal_extents_are_explicitly_skipped(self):
        result, status = self.run_fixture(size=4)
        self.assertEqual(status, 1)
        self.assertIn("extents differ", result["skipped_functions"][0]["reason"])

    def test_missing_requested_function_or_unit_is_explicit(self):
        report, dol, sha = fixture(self.root)
        result, status = tool.audit(self.root, report, dol, sha, ["toy"], "missing")
        self.assertEqual(status, 1)
        self.assertTrue(result["skipped_functions"])
        result, status = tool.audit(self.root, report, dol, sha, ["missing"])
        self.assertEqual(status, 2)
        self.assertTrue(result["errors"])

    def test_reference_dol_disagreement_is_an_input_error(self):
        report, dol, sha = fixture(self.root)
        raw = bytearray(dol.read_bytes())
        put_word(raw, 256 + 0x20, bl(BASE + 0x20, BASE))
        dol.write_bytes(raw)
        result, status = tool.audit(self.root, report, dol, hashlib.sha1(raw).hexdigest())
        self.assertEqual(status, 2)
        self.assertIn("ELF/DOL disagreement", result["errors"][0]["reason"])

    def test_call_only_in_original_dol_is_not_missed(self):
        report, dol, sha = fixture(self.root)
        raw = bytearray(dol.read_bytes())
        put_word(raw, 256 + 0x24, bl(BASE + 0x24, BASE))
        dol.write_bytes(raw)
        result, status = tool.audit(self.root, report, dol, hashlib.sha1(raw).hexdigest())
        self.assertEqual(status, 2)
        self.assertIn("ELF/DOL disagreement at +0x4", result["errors"][0]["reason"])

    def test_removed_source_call_is_a_shape_candidate(self):
        report, dol, sha = fixture(self.root)
        source = self.root / "build/43U/src/toy.o"
        text = bytearray(0x80)
        put_word(text, 0x20, LI_ONE)
        put_word(text, 0x24, BLR)
        source.write_bytes(make_elf(text, [("caller", 0x20, 8, 1, 2)], []))
        result, status = tool.audit(self.root, report, dol, sha)
        self.assertEqual(status, 1)
        self.assertEqual(result["rows"][0]["classification"], "call_shape_difference")

    def test_dol_integrity_and_bounds_validation(self):
        raw = make_dol(bytes(8))
        with self.assertRaisesRegex(ValueError, "SHA1"):
            tool.Dol(raw, "0" * 40)
        with self.assertRaisesRegex(ValueError, "truncated"):
            tool.Dol(b"", hashlib.sha1(b"").hexdigest())
        image = tool.Dol(raw, hashlib.sha1(raw).hexdigest())
        with self.assertRaisesRegex(ValueError, "not in one DOL section"):
            image.read(BASE + 8, 4)

    def test_no_body_alias_hint_for_position_dependent_code(self):
        self.assertFalse(tool.position_independent_leaf(bl(0, 0x100).to_bytes(4, "big")))
        self.assertFalse(tool.position_independent_leaf(bl(0, 0).to_bytes(4, "big")))

    def test_changed_input_and_head_are_reported(self):
        path = self.root / "input"
        path.write_bytes(b"first")
        inputs = tool.Inputs()
        inputs.read(path)
        path.write_bytes(b"second")
        self.assertEqual(inputs.changed(), [str(path)])
        with self.assertRaisesRegex(ValueError, "changed while reading"):
            inputs.read(path)
        report, dol, sha = fixture(self.root)
        with patch.object(tool, "git_head", side_effect=["before", "after"]):
            result, status = tool.audit(self.root, report, dol, sha)
        self.assertEqual(status, 2)
        self.assertEqual(result["errors"][-1]["reason"], "inputs changed during audit")

    def test_cli_json_exit_status_and_input_overwrite_protection(self):
        report, dol, sha = fixture(self.root)
        output = self.root / "results.json"
        args = ["--root", str(self.root), "--dol", str(dol), "--dol-sha1", sha]
        self.assertEqual(tool.main(args + ["--output", str(output)]), 0)
        self.assertTrue(json.loads(output.read_text())["advisory"])
        with contextlib.redirect_stderr(io.StringIO()):
            self.assertEqual(tool.main(args + ["--output", str(report)]), 2)
        self.assertIn("units", json.loads(report.read_text()))


if __name__ == "__main__":
    unittest.main()
