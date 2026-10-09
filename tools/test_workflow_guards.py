#!/usr/bin/env python3
import copy
import json
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

from check_decomp_complete import check_dol, check_report, check_sections, exact
from check_asm_inventory import check_inventory


class AssemblyInventoryTests(unittest.TestCase):
    def setUp(self):
        directory = tempfile.TemporaryDirectory()
        self.addCleanup(directory.cleanup)
        self.root = Path(directory.name)
        for name in ("src", "libs", "docs"):
            (self.root / name).mkdir()
        (self.root / "configure.py").write_text("objects = []\n", encoding="utf-8")

    def inventory(self, *rows):
        text = "| File | Function | Classification | Evidence |\n| --- | --- | --- | --- |\n"
        for file, function, verdict in rows:
            text += f"| `{file}` | `{function}` | {verdict} | test fixture |\n"
        (self.root / "docs/asm-inventory.md").write_text(text, encoding="utf-8")

    def check(self):
        return check_inventory(self.root)

    def test_asm_declarations_comments_and_literals_are_not_bodies(self):
        source = r'''
extern "C" asm void declared();
asm int Widget::declared() const;
// asm void comment() { nofralloc }
/* void comment() { asm { sync } } */
const char* message = "asm { nofralloc }";
const char* raw = R"tag(quote " asm { sync })tag";
// continued comment \
asm void hidden() { nofralloc }
'''
        (self.root / "src/declared.cpp").write_text(source, encoding="utf-8")
        self.inventory()
        bodies, _, failures = self.check()
        self.assertEqual(bodies, [])
        self.assertEqual(failures, [])

    def test_all_inline_forms_and_inactive_headers_are_inventoried(self):
        source = '''
asm void whole() { nofralloc; blr; }
void mixed() { if (ready) { asm volatile { sync } } __asm__("isync"); }
int Widget::read() const { __asm { mfspr r3, 1 } return 0; }
void bare() { nofralloc; blr; }
#if 0
void inactive() { asm("sync"); }
#endif
'''
        (self.root / "libs/arch.h").write_text(source, encoding="utf-8")
        names = {"whole", "mixed", "Widget::read", "bare", "inactive"}
        self.inventory(*[("libs/arch.h", name, "ORIGINAL") for name in sorted(names)])
        bodies, _, failures = self.check()
        self.assertEqual({body.function for body in bodies}, names)
        self.assertEqual(len(bodies), 6)
        self.assertEqual(failures, [])

    def test_unlisted_asm_fails(self):
        (self.root / "src/missing.c").write_text("void missing() { asm { sync } }", encoding="utf-8")
        self.inventory()
        self.assertIn("unlisted assembly: src/missing.c: missing", self.check()[2])

    def test_placeholder_and_original_cli_exit_codes(self):
        (self.root / "src/entry.c").write_text("asm void entry() { nofralloc; blr; }", encoding="utf-8")
        script = Path(__file__).resolve().with_name("check_asm_inventory.py")
        for verdict, status in (("PLACEHOLDER", 1), ("ORIGINAL", 0)):
            with self.subTest(verdict=verdict):
                self.inventory(("src/entry.c", "entry", verdict))
                result = subprocess.run([sys.executable, str(script), "--root", str(self.root)], capture_output=True, text=True)
                self.assertEqual(result.returncode, status, result.stderr)
                if status:
                    self.assertIn("placeholder: src/entry.c: entry", result.stderr)
                else:
                    self.assertIn("ASM INVENTORY PASS", result.stdout)

    def test_utf16_source_is_scanned(self):
        (self.root / "src/wide.cpp").write_text("asm void wide() { nofralloc; blr; }", encoding="utf-16")
        self.inventory()
        self.assertIn("unlisted assembly: src/wide.cpp: wide", self.check()[2])

    def test_configured_assembly_and_tree_assembly_are_scanned(self):
        (self.root / "boot").mkdir()
        (self.root / "configure.py").write_text('objects = [Object(Matching, "boot/start.s")]\n', encoding="utf-8")
        (self.root / "boot/start.s").write_text(".text\n.global start\nstart:\n sync\n.Lloop:\n blr\n", encoding="utf-8")
        (self.root / "libs/helper.S").write_text(".section .text\n.fn helper, global\n blr\n.endfn helper\n", encoding="utf-8")
        (self.root / "src/labels.s").write_text(".text\n.globl first, lbl_exported\nfirst:\n b first\nlbl_exported:\n blr\n.data\nvalue:\n.long 1\n", encoding="utf-8")
        self.inventory(("boot/start.s", "start", "ORIGINAL"), ("libs/helper.S", "helper", "ORIGINAL"), ("src/labels.s", "first", "ORIGINAL"))
        self.assertIn("unlisted assembly: src/labels.s: lbl_exported", self.check()[2])
        self.inventory(("boot/start.s", "start", "ORIGINAL"), ("libs/helper.S", "helper", "ORIGINAL"), ("src/labels.s", "first", "ORIGINAL"), ("src/labels.s", "lbl_exported", "ORIGINAL"))
        self.assertEqual(self.check()[2], [])

    def test_unresolved_configured_assembly_fails(self):
        (self.root / "configure.py").write_text('objects = ["missing.s"]\n', encoding="utf-8")
        self.inventory()
        self.assertTrue(any("unresolved" in failure for failure in self.check()[2]))

    def test_dynamic_assembly_path_requires_inspection(self):
        (self.root / "configure.py").write_text('objects = [path + ".s"]\n', encoding="utf-8")
        self.inventory()
        self.assertTrue(any("dynamic assembly path" in failure for failure in self.check()[2]))

    def test_unknown_syntax_and_unowned_assembly_fail_closed(self):
        self.inventory()
        for source in ("nofralloc", 'asm("sync");', "#define HARDWARE asm { sync }"):
            with self.subTest(source=source):
                (self.root / "src/unknown.c").write_text(source, encoding="utf-8")
                self.assertTrue(self.check()[2])
        (self.root / "src/unknown.c").unlink()
        (self.root / "src/unowned.s").write_text(".text\nblr\n", encoding="utf-8")
        self.assertTrue(any("without a function label" in failure for failure in self.check()[2]))
        (self.root / "src/unowned.s").write_text(".text\nfirst: blr\nsecond: blr\n", encoding="utf-8")
        self.inventory(("src/unowned.s", "first", "ORIGINAL"))
        self.assertTrue(any("untyped assembly label" in failure for failure in self.check()[2]))

    def test_same_name_in_distinct_functions_is_not_silently_merged(self):
        (self.root / "src/scopes.cpp").write_text("namespace one { void f() { asm { sync } } }\nnamespace two { void f() { asm { isync } } }", encoding="utf-8")
        self.inventory(("src/scopes.cpp", "f", "ORIGINAL"))
        self.assertTrue(any("ambiguous assembly function name" in failure for failure in self.check()[2]))

    def test_stale_duplicate_and_invalid_rows_fail(self):
        self.inventory(("src/gone.c", "gone", "ORIGINAL"), ("src/gone.c", "gone", "UNKNOWN"))
        failures = self.check()[2]
        for message in ("stale inventory entry", "duplicate entry", "invalid entry"):
            self.assertTrue(any(message in failure for failure in failures), failures)

    def test_missing_inventory_fails(self):
        self.assertTrue(any("inventory:" in failure for failure in self.check()[2]))


class SectionCoverageTests(unittest.TestCase):
    def check(self, sections, **measures):
        failures = []
        check_sections(sections, measures, "fixture", failures)
        return failures

    def test_code_and_data_coverage_pass(self):
        sections = [
            {"name": ".init", "size": "16", "fuzzy_match_percent": 100.0},
            {"name": ".data", "size": "8", "fuzzy_match_percent": 100.0},
        ]
        self.assertEqual(self.check(sections, total_code="16", total_data="8"), [])

    def test_data_only_and_proto_zero_sizes_pass(self):
        self.assertEqual(self.check([{"name": ".sbss", "size": "64"}], total_data="64"), [])
        self.assertEqual(self.check([], total_code=0, total_data=0), [])
        self.assertEqual(self.check([
            {"name": ".text", "fuzzy_match_percent": 100.0},
            {"name": ".bss"},
        ], total_code=0, total_data=0), [])

    def test_deduplicated_code_is_not_required_to_equal_section_size(self):
        sections = [{"name": ".text", "size": "28", "fuzzy_match_percent": 100.0}]
        self.assertEqual(self.check(sections, total_code="16"), [])
        self.assertEqual(self.check(sections, total_code=0), [])

    def test_deleted_or_truncated_sections_fail(self):
        for sections in ([], [{"name": ".text", "size": "12", "fuzzy_match_percent": 100.0}]):
            with self.subTest(sections=sections):
                failures = self.check(sections, total_code="16", total_data="8")
                self.assertTrue(any("section code coverage" in item for item in failures))
                self.assertTrue(any("section data coverage" in item for item in failures))

    def test_excess_data_is_not_hidden_by_code_slack(self):
        failures = self.check([
            {"name": ".text", "size": "28", "fuzzy_match_percent": 100.0},
            {"name": ".bss", "size": "12"},
        ], total_code="16", total_data="8")
        self.assertIn("fixture section data coverage: 12 != 8", failures)

    def test_invalid_section_sizes_fail(self):
        for size in (-1, "-1", True, 1.5, "1.5", None):
            with self.subTest(size=size):
                self.assertTrue(self.check([{"name": ".data", "size": size}], total_data=0))

    def test_invalid_and_duplicate_section_names_fail(self):
        for name in (None, [], "", ".unknown"):
            with self.subTest(name=name):
                self.assertTrue(self.check([{"name": name, "size": "8"}], total_data="8"))
        section = {"name": ".data", "size": "4"}
        self.assertIn("fixture section .data: duplicate section", self.check([section, section], total_data="8"))

    def test_section_scores_remain_strict(self):
        for section in (
            {"name": ".text", "size": "16"},
            {"name": ".text", "size": "16", "fuzzy_match_percent": 99.9999},
            {"name": ".data", "size": "8", "fuzzy_match_percent": 99.9999},
        ):
            with self.subTest(section=section):
                failures = self.check([section], total_code="16", total_data="8")
                self.assertTrue(any("fixture section " + section["name"] in item for item in failures))


class WorkflowGuardTests(unittest.TestCase):
    def test_exact_percent_is_strict(self):
        self.assertTrue(exact(100.0))
        self.assertFalse(exact(99.9999995))

    def test_empty_report_fails_expected_schema(self):
        failures = check_report({"version": 2, "measures": {}, "units": [], "categories": []})
        self.assertTrue(any("total_units" in failure for failure in failures))
        self.assertTrue(any("missing categories" in failure for failure in failures))

    def test_obsolete_overlapping_code_total_is_rejected(self):
        failures = check_report({
            "version": 2,
            "measures": {"total_code": 2995188},
            "units": [],
            "categories": [],
        })
        self.assertIn("overall total_code: 2995188 != 2995176", failures)

    def test_malformed_report_values_fail_without_crashing(self):
        failures = check_report(
            {
                "version": 2,
                "measures": {"total_units": 1.5},
                "units": [None],
                "categories": [None],
            }
        )
        self.assertTrue(any("invalid integer" in failure for failure in failures))
        self.assertTrue(any("invalid unit entry" in failure for failure in failures))
        self.assertTrue(any("invalid category entry" in failure for failure in failures))
        failures = check_report({"version": 2, "measures": {"total_units": -1}})
        self.assertTrue(any("invalid non-negative integer" in failure for failure in failures))

    @unittest.skipUnless(
        (Path(__file__).resolve().parents[1] / "build/43U/report.json").is_file(),
        "generated 43U report is not available",
    )
    def test_data_section_without_code_score_is_allowed(self):
        report_path = Path(__file__).resolve().parents[1] / "build/43U/report.json"
        report = json.loads(report_path.read_text(encoding="utf-8"))
        failures = check_report(report)
        self.assertFalse(any("enc_dummy section .sbss" in failure for failure in failures))

    def complete_report(self):
        report_path = Path(__file__).resolve().parents[1] / "build/43U/report.json"
        if not report_path.is_file():
            self.skipTest("generated 43U report is not available")
        report = copy.deepcopy(json.loads(report_path.read_text(encoding="utf-8")))

        def fill(measures):
            for total, matched, linked in (
                ("total_code", "matched_code", "complete_code"),
                ("total_data", "matched_data", "complete_data"),
                ("total_functions", "matched_functions", None),
                ("total_units", None, "complete_units"),
            ):
                if total in measures:
                    if matched:
                        measures[matched] = measures[total]
                    if linked:
                        measures[linked] = measures[total]
            for field in (
                "matched_code_percent",
                "complete_code_percent",
                "matched_data_percent",
                "complete_data_percent",
                "matched_functions_percent",
                "fuzzy_match_percent",
            ):
                if field.endswith("data_percent") and "total_data" not in measures:
                    continue
                if field.endswith("code_percent") and "total_code" not in measures:
                    continue
                if field == "matched_functions_percent" and "total_functions" not in measures:
                    continue
                if field == "fuzzy_match_percent" and "total_code" not in measures:
                    continue
                measures[field] = 100.0

        fill(report["measures"])
        for unit in report["units"]:
            unit["metadata"]["complete"] = True
            fill(unit["measures"])
            for section in unit["sections"]:
                section["fuzzy_match_percent"] = 100.0
            for function in unit.get("functions", []):
                function["fuzzy_match_percent"] = 100.0
        for category in report["categories"]:
            fill(category["measures"])
        return report

    def test_complete_report_schema_passes(self):
        self.assertEqual(check_report(self.complete_report()), [])

    def test_empty_section_arrays_cannot_claim_completion(self):
        report = self.complete_report()
        for unit in report["units"]:
            unit["sections"] = []
        failures = check_report(report)
        self.assertTrue(any("section code coverage" in failure for failure in failures))
        self.assertTrue(any("section data coverage" in failure for failure in failures))

    def test_deleting_one_code_or_data_section_fails(self):
        for kind, section_name in (("code", ".text"), ("data", ".sbss")):
            with self.subTest(kind=kind):
                report = self.complete_report()
                unit = next(unit for unit in report["units"]
                            if any(section["name"] == section_name for section in unit["sections"]))
                unit["sections"] = [section for section in unit["sections"] if section["name"] != section_name]
                self.assertTrue(any(f"{unit['name']} section {kind} coverage" in failure
                                    for failure in check_report(report)))

    def test_every_current_section_is_required_for_coverage(self):
        for unit in self.complete_report()["units"]:
            for index, section in enumerate(unit["sections"]):
                with self.subTest(unit=unit["name"], section=section["name"]):
                    remaining = unit["sections"][:index] + unit["sections"][index + 1:]
                    failures = []
                    check_sections(remaining, unit["measures"], unit["name"], failures)
                    self.assertTrue(any("coverage" in failure for failure in failures), failures)

    def test_inventory_gate_is_only_in_strict_completion_step(self):
        workflow = (Path(__file__).resolve().parents[1] / ".github/workflows/build.yml").read_text(encoding="utf-8")
        steps = workflow.split("    - name: ")
        inventory_steps = [step for step in steps if "python tools/check_asm_inventory.py" in step]
        self.assertEqual(len(inventory_steps), 1)
        step = inventory_steps[0]
        self.assertTrue(step.startswith("Enforce completion gate\n"))
        self.assertIn("if: matrix.version == '43U' && github.event_name == 'workflow_dispatch' && inputs.require_complete == true", step)
        self.assertIn("python tools/check_decomp_complete.py", step)

    def test_aggregate_fuzzy_float_rounding_passes_only_when_fully_matched(self):
        report = self.complete_report()
        report["measures"]["fuzzy_match_percent"] = 99.999886
        report["categories"][0]["measures"]["fuzzy_match_percent"] = 99.999886
        self.assertEqual(check_report(report), [])

        code_unit = next(unit for unit in report["units"] if "total_code" in unit["measures"])
        code_unit["measures"]["fuzzy_match_percent"] = 99.999886
        self.assertIn(f"{code_unit['name']} fuzzy percent: 99.999886", check_report(report))

        report = self.complete_report()
        report["measures"]["fuzzy_match_percent"] = 99.9
        self.assertIn("overall fuzzy_match_percent: 99.9", check_report(report))

        report = self.complete_report()
        report["measures"]["fuzzy_match_percent"] = 99.999886
        report["measures"]["matched_code"] = int(report["measures"]["total_code"]) - 4
        self.assertIn("overall fuzzy_match_percent: 99.999886", check_report(report))

    def test_missing_or_extra_unit_fails(self):
        for total_units in (1027, 1029):
            with self.subTest(total_units=total_units):
                report = self.complete_report()
                if total_units == 1027:
                    report["units"].pop()
                else:
                    extra = copy.deepcopy(report["units"][-1])
                    extra["name"] += "/extra"
                    report["units"].append(extra)
                failures = check_report(report)
                self.assertIn(f"unit report length: {total_units}", failures)
                self.assertIn(f"unit aggregate total_units: {total_units} != 1028", failures)

    def test_wrong_unit_totals_fail(self):
        for total_units in (1027, 1029):
            with self.subTest(total_units=total_units):
                report = self.complete_report()
                delta = total_units - 1028
                for field in ("total_units", "complete_units"):
                    report["measures"][field] = total_units
                    report["categories"][0]["measures"][field] += delta
                failures = check_report(report)
                self.assertIn(f"overall total_units: {total_units} != 1028", failures)
                self.assertIn(f"category total_units: {total_units} != 1028", failures)

    @unittest.skipUnless(
        (Path(__file__).resolve().parents[1] / "build/43U/report.json").is_file(),
        "generated 43U report is not available",
    )
    def test_missing_unit_data_does_not_pass(self):
        report_path = Path(__file__).resolve().parents[1] / "build/43U/report.json"
        report = json.loads(report_path.read_text(encoding="utf-8"))
        unit = next(unit for unit in report["units"] if unit["name"] == "main/src/system/enc_dummy")
        forged = copy.deepcopy(report)
        forged_unit = next(item for item in forged["units"] if item["name"] == unit["name"])
        forged_unit["metadata"]["complete"] = True
        forged_unit["measures"].pop("matched_data", None)
        failures = check_report(forged)
        self.assertTrue(any("enc_dummy data match" in failure for failure in failures))

    def test_dol_hash_is_checked(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "main.dol"
            path.write_bytes(b"not the Wii Menu DOL")
            self.assertTrue(check_dol(path))


if __name__ == "__main__":
    unittest.main()
