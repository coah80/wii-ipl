#!/usr/bin/env python3
import argparse
import hashlib
import json
import math
import re
import sys
from pathlib import Path


EXPECTED_DOL_SHA1 = "26116613f624061ba99c8d1a299aaa6efa85670d"
EXPECTED_TOTAL_UNITS = 1026
EXPECTED_TOTAL_CODE = 2995172
EXPECTED_TOTAL_DATA = 1832684
EXPECTED_TOTAL_FUNCTIONS = 12563
INTEGER_PATTERN = re.compile(r"-?(0|[1-9][0-9]*)\Z")
CODE_SECTIONS = frozenset({".text", ".init"})
AGGREGATE_FIELDS = (
    "total_units",
    "total_code",
    "total_data",
    "total_functions",
    "matched_code",
    "complete_code",
    "matched_data",
    "complete_data",
    "matched_functions",
    "complete_units",
)


def integer(value):
    if isinstance(value, bool):
        raise ValueError("boolean is not an integer")
    if isinstance(value, int):
        return value
    if isinstance(value, str) and INTEGER_PATTERN.fullmatch(value):
        return int(value)
    raise ValueError(f"invalid integer: {value!r}")


def exact(value):
    return (
        isinstance(value, (int, float))
        and not isinstance(value, bool)
        and math.isfinite(float(value))
        and float(value) == 100.0
    )


def required(measures, field, label, failures):
    if field not in measures or measures[field] is None:
        failures.append(f"{label}: missing {field}")
        return None
    return measures[field]


def count(measures, field, label, failures):
    value = required(measures, field, label, failures)
    if value is None:
        return None
    try:
        parsed = integer(value)
    except ValueError:
        failures.append(f"{label}: invalid integer {value!r}")
        return None
    if parsed < 0:
        failures.append(f"{label}: invalid non-negative integer {value!r}")
        return None
    return parsed


def equal(measures, matched, total, label, failures):
    matched_value = count(measures, matched, label, failures)
    total_value = count(measures, total, label, failures)
    if matched_value is None or total_value is None:
        return
    if matched_value != total_value:
        failures.append(f"{label}: {matched_value} / {total_value}")


def percent(measures, field, label, failures):
    value = required(measures, field, label, failures)
    if value is not None and not exact(value):
        failures.append(f"{label}: {value}")


def check_complete_measures(measures, label, failures):
    for matched, total, name in (
        ("matched_code", "total_code", "code match"),
        ("complete_code", "total_code", "code link"),
        ("matched_data", "total_data", "data match"),
        ("complete_data", "total_data", "data link"),
        ("matched_functions", "total_functions", "function match"),
        ("complete_units", "total_units", "unit link"),
    ):
        equal(measures, matched, total, f"{label} {name}", failures)
    for field in (
        "matched_code_percent",
        "complete_code_percent",
        "matched_data_percent",
        "complete_data_percent",
        "matched_functions_percent",
        "fuzzy_match_percent",
    ):
        percent(measures, field, f"{label} {field}", failures)


def key_for(value):
    return type(value).__name__, repr(value)


def check_report(report):
    failures = []
    if not isinstance(report, dict):
        return ["report root is not an object"]
    if report.get("version") != 2:
        failures.append(f"report version: {report.get('version')}")

    measures = report.get("measures", {})
    if not isinstance(measures, dict):
        failures.append("overall: missing measures")
        measures = {}
    expected_totals = {
        "total_units": EXPECTED_TOTAL_UNITS,
        "total_code": EXPECTED_TOTAL_CODE,
        "total_data": EXPECTED_TOTAL_DATA,
        "total_functions": EXPECTED_TOTAL_FUNCTIONS,
    }
    for field, expected in expected_totals.items():
        value = count(measures, field, "overall", failures)
        if value is not None and value != expected:
            failures.append(f"overall {field}: {value} != {expected}")
    check_complete_measures(measures, "overall", failures)

    units = report.get("units")
    if not isinstance(units, list) or len(units) != EXPECTED_TOTAL_UNITS:
        failures.append(f"unit report length: {len(units) if isinstance(units, list) else 'missing'}")
        units = units if isinstance(units, list) else []
    names = [
        unit.get("name", "<unnamed>") if isinstance(unit, dict) else "<invalid>"
        for unit in units
    ]
    if len({key_for(name) for name in names}) != len(names):
        failures.append("unit names are not unique")

    unit_sums = {field: 0 for field in AGGREGATE_FIELDS}
    for unit in units:
        if not isinstance(unit, dict):
            failures.append("invalid unit entry")
            continue
        name = unit.get("name", "<unnamed>")
        unit_measures = unit.get("measures")
        if not isinstance(unit_measures, dict):
            failures.append(f"{name}: missing measures")
            continue
        for field in AGGREGATE_FIELDS:
            if field in unit_measures:
                value = count(unit_measures, field, name, failures)
                if value is not None:
                    unit_sums[field] += value
        metadata = unit.get("metadata")
        if not isinstance(metadata, dict) or metadata.get("complete") is not True:
            failures.append(f"unit incomplete: {name}")

        total_units = count(unit_measures, "total_units", name, failures)
        if total_units is not None and total_units != 1:
            failures.append(f"{name} total_units: {total_units}")
        equal(unit_measures, "complete_units", "total_units", f"{name} unit link", failures)

        has_total_code = "total_code" in unit_measures
        has_total_data = "total_data" in unit_measures
        has_total_functions = "total_functions" in unit_measures
        total_functions = count(unit_measures, "total_functions", name, failures) if has_total_functions else None
        if not has_total_code and not has_total_data:
            failures.append(f"{name}: missing code and data totals")
        if has_total_code:
            equal(unit_measures, "matched_code", "total_code", f"{name} code match", failures)
            equal(unit_measures, "complete_code", "total_code", f"{name} code link", failures)
            percent(unit_measures, "matched_code_percent", f"{name} code percent", failures)
            percent(unit_measures, "complete_code_percent", f"{name} code link percent", failures)
            percent(unit_measures, "fuzzy_match_percent", f"{name} fuzzy percent", failures)
        if has_total_data:
            equal(unit_measures, "matched_data", "total_data", f"{name} data match", failures)
            equal(unit_measures, "complete_data", "total_data", f"{name} data link", failures)
            percent(unit_measures, "matched_data_percent", f"{name} data percent", failures)
            percent(unit_measures, "complete_data_percent", f"{name} data link percent", failures)
        if has_total_functions:
            equal(unit_measures, "matched_functions", "total_functions", f"{name} function match", failures)
            percent(unit_measures, "matched_functions_percent", f"{name} function percent", failures)

        sections = unit.get("sections")
        if not isinstance(sections, list):
            failures.append(f"{name}: missing sections")
        else:
            for section in sections:
                if not isinstance(section, dict):
                    failures.append(f"{name}: invalid section entry")
                    continue
                section_name = section.get("name", "<unnamed>")
                if "fuzzy_match_percent" in section:
                    percent(section, "fuzzy_match_percent", f"{name} section {section_name}", failures)
                elif isinstance(section_name, str) and section_name in CODE_SECTIONS:
                    failures.append(f"{name} section {section_name}: missing fuzzy_match_percent")

        functions = unit.get("functions", [])
        if total_functions is not None and total_functions > 0:
            if not isinstance(functions, list) or len(functions) != total_functions:
                failures.append(f"{name} function list: {len(functions) if isinstance(functions, list) else 'missing'} / {total_functions}")
            else:
                for function in functions:
                    if not isinstance(function, dict):
                        failures.append(f"{name}: invalid function entry")
                        continue
                    percent(function, "fuzzy_match_percent", f"{name} function {function.get('name', '<unnamed>')}", failures)
        elif has_total_functions and total_functions == 0 and functions:
            failures.append(f"{name}: unexpected functions")
        elif not has_total_functions and functions:
            failures.append(f"{name}: unexpected functions")

    for field in AGGREGATE_FIELDS:
        expected = count(measures, field, "overall", failures)
        if expected is not None and unit_sums[field] != expected:
            failures.append(f"unit aggregate {field}: {unit_sums[field]} != {expected}")

    categories = report.get("categories")
    if not isinstance(categories, list) or not categories:
        failures.append("missing categories")
        categories = categories if isinstance(categories, list) else []
    category_names = [
        category.get("name", "<unnamed>") if isinstance(category, dict) else "<invalid>"
        for category in categories
    ]
    if len({key_for(name) for name in category_names}) != len(category_names):
        failures.append("category names are not unique")

    category_sums = {field: 0 for field in AGGREGATE_FIELDS}
    for category in categories:
        if not isinstance(category, dict):
            failures.append("invalid category entry")
            continue
        name = category.get("name", "<unnamed>")
        category_measures = category.get("measures")
        if not isinstance(category_measures, dict):
            failures.append(f"{name}: missing measures")
            continue
        check_complete_measures(category_measures, name, failures)
        for field in AGGREGATE_FIELDS:
            if field in category_measures:
                value = count(category_measures, field, name, failures)
                if value is not None:
                    category_sums[field] += value
    for field, expected in expected_totals.items():
        if category_sums[field] != expected:
            failures.append(f"category {field}: {category_sums[field]} != {expected}")
    for field in AGGREGATE_FIELDS:
        expected = count(measures, field, "overall", failures)
        if expected is not None and category_sums[field] != expected:
            failures.append(f"category aggregate {field}: {category_sums[field]} != {expected}")
    return failures


def check_dol(path):
    try:
        digest = hashlib.sha1(path.read_bytes()).hexdigest()
    except OSError as error:
        return [f"DOL read failed: {error}"]
    if digest != EXPECTED_DOL_SHA1:
        return [f"DOL SHA1: {digest} != {EXPECTED_DOL_SHA1}"]
    return []


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("report", type=Path)
    parser.add_argument("--dol", type=Path, required=True)
    args = parser.parse_args()
    try:
        report = json.loads(args.report.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError) as error:
        print("DECOMPLETE_FAIL")
        print(f"- report read failed: {error}")
        return 1
    failures = check_report(report)
    failures.extend(check_dol(args.dol))
    if failures:
        print("DECOMPLETE_FAIL")
        for failure in failures[:40]:
            print(f"- {failure}")
        if len(failures) > 40:
            print(f"- ... {len(failures) - 40} more failures")
        return 1
    print("DECOMPLETE_OK")
    return 0


if __name__ == "__main__":
    sys.exit(main())
