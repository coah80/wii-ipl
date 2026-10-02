import contextlib
from dataclasses import replace
import io
import unittest
from unittest.mock import patch

import jump_table_diff as tool


def fixture(entries=(0x10, 0x20, 0x30), function_offset=0x100,
            table_offset=0x40, source=False, section_ids=(1, 2)):
    text, data = section_ids
    symbols = [
        tool.Symbol("dispatch", text, function_offset, 0x80, "STT_FUNC"),
        tool.Symbol("@123" if source else "jumptable_test", data,
                    table_offset, len(entries) * 4),
    ]
    references = {
        text: {
            function_offset + 2: tool.Relocation(function_offset + 2, 6, 1, 0),
            function_offset + 6: tool.Relocation(function_offset + 6, 4, 1, 0),
        },
        data: {table_offset + i * 4: tool.Relocation(table_offset + i * 4, 1, 0, value)
               for i, value in enumerate(entries)},
    }
    return tool.ObjectInfo({text: (".text", 0x1000), data: (".data", 0x1000)},
                           symbols, references)


def compare(source, reference=None):
    reference = reference or fixture()
    src_fn = source.symbol("dispatch")
    ref_fn = reference.symbol("dispatch")
    table, expected = tool.reference_tables(reference, ref_fn, "jumptable_test")[0]
    return tool.compare_table(source, reference, src_fn, ref_fn, table, expected)


class JumpTableTests(unittest.TestCase):
    def test_infers_shifted_source_table_and_function(self):
        source = fixture(source=True, function_offset=0x200, table_offset=0x90,
                         section_ids=(3, 4))
        self.assertEqual(compare(source), ([0x10, 0x20, 0x30], []))

    def test_detects_swapped_destinations_despite_same_function_size(self):
        actual, differences = compare(fixture((0x20, 0x10, 0x30), source=True))
        self.assertEqual(actual, [0x20, 0x10, 0x30])
        self.assertEqual(differences, [(0, 0x20, 0x10), (1, 0x10, 0x20)])

    def test_section_relative_code_reference(self):
        source = fixture(source=True, table_offset=0x90)
        source.symbols.append(tool.Symbol("", 2, 0, 0, "STT_SECTION"))
        for offset, relocation in list(source.relocations[1].items()):
            source.relocations[1][offset] = replace(relocation, symbol=2, addend=0x90)
        self.assertEqual(compare(source)[1], [])

    def test_section_relative_table_entries(self):
        source = fixture(source=True)
        source.symbols.append(tool.Symbol("", 1, 0, 0, "STT_SECTION"))
        for offset, relocation in list(source.relocations[2].items()):
            source.relocations[2][offset] = replace(
                relocation, symbol=2, addend=0x100 + relocation.addend)
        self.assertEqual(compare(source)[1], [])

    def test_missing_entry_is_mismatch(self):
        source = fixture(source=True)
        del source.relocations[2][0x44]
        self.assertEqual(compare(source)[1], [(1, None, 0x20)])

    def test_wrong_relocation_kind_is_mismatch(self):
        source = fixture(source=True)
        source.relocations[2][0x44] = replace(source.relocations[2][0x44], kind=10)
        self.assertEqual(compare(source)[1], [(1, None, 0x20)])

    def test_out_of_function_destination_is_mismatch(self):
        source = fixture(source=True)
        source.relocations[2][0x44] = replace(source.relocations[2][0x44], addend=0x80)
        self.assertEqual(compare(source)[1], [(1, None, 0x20)])

    def test_extra_source_entry_is_not_a_pass(self):
        self.assertEqual(compare(fixture((0x10, 0x20, 0x30, 0x40), source=True))[1],
                         [(3, 0x40, None)])

    def test_short_source_table_is_not_a_pass(self):
        self.assertEqual(compare(fixture((0x10, 0x20), source=True))[1],
                         [(2, None, 0x30)])

    def test_different_function_sizes_reject_inference(self):
        source = fixture(source=True)
        source.symbols[0] = replace(source.symbols[0], size=0x84)
        with self.assertRaisesRegex(ValueError, "function sizes differ"):
            compare(source)

    def test_disagreeing_code_references_reject_inference(self):
        source = fixture(source=True)
        source.relocations[1][0x106] = replace(source.relocations[1][0x106], addend=4)
        with self.assertRaisesRegex(ValueError, "infer one source table"):
            compare(source)

    def test_missing_code_reference_rejects_inference(self):
        source = fixture(source=True)
        del source.relocations[1][0x106]
        with self.assertRaisesRegex(ValueError, "table-reference relocations differ"):
            compare(source)

    def test_ambiguous_source_extent_rejects_inference(self):
        source = fixture(source=True)
        source.symbols.append(tool.Symbol("alias", 2, 0x40, 16))
        with self.assertRaisesRegex(ValueError, "extent is missing or ambiguous"):
            compare(source)

    def test_different_source_section_rejects_inference(self):
        source = fixture(source=True)
        source.sections[2] = (".rodata", 0x1000)
        with self.assertRaisesRegex(ValueError, "different section"):
            compare(source)

    def test_undefined_source_reference_rejects_inference(self):
        source = fixture(source=True)
        source.symbols[1] = replace(source.symbols[1], section="SHN_UNDEF")
        with self.assertRaisesRegex(ValueError, "reference is undefined"):
            compare(source)

    def test_invalid_relocation_symbol_rejected(self):
        source = fixture(source=True)
        source.relocations[2][0x44] = replace(source.relocations[2][0x44], symbol=999)
        with self.assertRaisesRegex(ValueError, "symbol index is out of range"):
            compare(source)

    def test_duplicate_function_rejected(self):
        source = fixture(source=True)
        source.symbols.append(source.symbols[0])
        with self.assertRaisesRegex(ValueError, "one defined symbol"):
            compare(source)

    def test_out_of_section_symbol_rejected(self):
        source = fixture(source=True)
        source.symbols[0] = replace(source.symbols[0], size=0x2000)
        with self.assertRaisesRegex(ValueError, "outside its section"):
            compare(source)

    def test_unrelated_reference_table_is_not_selected(self):
        reference = fixture((0x80, 0x84, 0x88))
        self.assertEqual(tool.reference_tables(reference, reference.symbol("dispatch")), [])
        with self.assertRaisesRegex(ValueError, "does not target"):
            tool.reference_tables(reference, reference.symbol("dispatch"), "jumptable_test")

    def test_discovers_compiler_and_custom_names(self):
        for name in ("@123", "scCharacterDispatch"):
            reference = fixture()
            reference.symbols[1] = replace(reference.symbols[1], name=name)
            tables = tool.reference_tables(reference, reference.symbol("dispatch"))
            self.assertEqual([(t.name, entries) for t, entries in tables],
                             [(name, [0x10, 0x20, 0x30])])

    def test_custom_table_can_include_function_entry(self):
        reference = fixture((0, 0x10, 0x20), source=True)
        tables = tool.reference_tables(reference, reference.symbol("dispatch"))
        self.assertEqual(tables[0][1], [0, 0x10, 0x20])

    def test_function_entry_callback_array_is_not_auto_selected(self):
        reference = fixture((0, 0, 0), source=True)
        fn = reference.symbol("dispatch")
        self.assertEqual(tool.reference_tables(reference, fn), [])
        self.assertEqual(tool.reference_tables(reference, fn, "@123")[0][1],
                         [0, 0, 0])

    def test_single_pointer_requires_explicit_name(self):
        reference = fixture((0x10,), source=True)
        fn = reference.symbol("dispatch")
        self.assertEqual(tool.reference_tables(reference, fn), [])
        self.assertEqual(tool.reference_tables(reference, fn, "@123")[0][1], [0x10])

    def test_custom_table_requires_data_object(self):
        reference = fixture(source=True)
        reference.symbols[1] = replace(reference.symbols[1], kind="STT_NOTYPE")
        self.assertEqual(tool.reference_tables(reference, reference.symbol("dispatch")), [])
        reference.symbols[1] = replace(reference.symbols[1], kind="STT_OBJECT")
        reference.sections[2] = (".text", 0x1000)
        self.assertEqual(tool.reference_tables(reference, reference.symbol("dispatch")), [])

    def test_custom_table_with_missing_or_external_entry_is_not_selected(self):
        for entries in ((0x10, 0x20, 0x80), (0x10, 0x20, 0x30)):
            reference = fixture(entries, source=True)
            if entries[-1] == 0x30:
                del reference.relocations[2][0x48]
            self.assertEqual(tool.reference_tables(reference, reference.symbol("dispatch")), [])

    def test_auto_custom_table_still_detects_swapped_entries(self):
        reference = fixture(source=True)
        source = fixture((0x20, 0x10, 0x30), source=True, table_offset=0x90)
        with patch.object(tool, "read_object", side_effect=[source, reference]):
            with contextlib.redirect_stdout(io.StringIO()) as output:
                self.assertEqual(tool.main(["unused", "dispatch"]), 1)
            self.assertIn("@123: 1/3 entries match", output.getvalue())

    def test_cli_exit_codes(self):
        for source, expected_status in [(fixture(source=True), 0),
                                        (fixture((0x20, 0x10, 0x30), source=True), 1)]:
            with patch.object(tool, "read_object", side_effect=[source, fixture()]):
                with contextlib.redirect_stdout(io.StringIO()):
                    self.assertEqual(tool.main(["unused", "dispatch"]), expected_status)
        with patch.object(tool, "read_object", side_effect=ValueError("bad object")):
            with contextlib.redirect_stderr(io.StringIO()):
                self.assertEqual(tool.main(["unused", "dispatch"]), 2)


if __name__ == "__main__":
    unittest.main()
