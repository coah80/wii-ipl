#!/usr/bin/env python3
import copy
import json
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

from check_decomp_complete import check_dol, check_report, exact


class WorkflowGuardTests(unittest.TestCase):
    def test_exact_percent_is_strict(self):
        self.assertTrue(exact(100.0))
        self.assertFalse(exact(99.9999995))

    def test_empty_report_fails_expected_schema(self):
        failures = check_report({"version": 2, "measures": {}, "units": [], "categories": []})
        self.assertTrue(any("total_units" in failure for failure in failures))
        self.assertTrue(any("missing categories" in failure for failure in failures))

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

    @unittest.skipUnless(
        (Path(__file__).resolve().parents[1] / "build/43U/report.json").is_file(),
        "generated 43U report is not available",
    )
    def test_complete_report_schema_passes(self):
        report_path = Path(__file__).resolve().parents[1] / "build/43U/report.json"
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
        self.assertEqual(check_report(report), [])

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
