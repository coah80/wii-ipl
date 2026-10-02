#!/usr/bin/env python3
"""Write shields.io endpoint JSON files from an objdiff report.

usage: progress_badges.py <report.json> <out-dir>

The README badges read these files from the progress-data branch, so the
numbers update without committing to main.
"""
import json
import os
import sys

COLOR = "33b8ff"
DONE_COLOR = "brightgreen"


def badge(label, message, done):
    return {
        "schemaVersion": 1,
        "label": label,
        "message": message,
        "color": DONE_COLOR if done else COLOR,
        "labelColor": "7c7c7c",
        "style": "plastic",
    }


def percent(measures, key):
    value = float(measures.get(key) or 0.0)
    return f"{value:.2f}%", value >= 100.0


def count(measures, done_key, total_key):
    done = int(measures.get(done_key) or 0)
    total = int(measures.get(total_key) or 0)
    return f"{done:,} / {total:,}", total > 0 and done == total


def main():
    if len(sys.argv) != 3:
        raise SystemExit(__doc__)
    report_path, out_dir = sys.argv[1], sys.argv[2]
    measures = json.load(open(report_path))["measures"]

    badges = {
        "decompiled": ("Decompiled", percent(measures, "fuzzy_match_percent")),
        "matched": ("Matched", percent(measures, "matched_code_percent")),
        "linked": ("Linked", percent(measures, "complete_code_percent")),
        "data": ("Data", percent(measures, "matched_data_percent")),
        "functions": ("Functions", count(measures, "matched_functions", "total_functions")),
        "units": ("Units", count(measures, "complete_units", "total_units")),
    }

    os.makedirs(out_dir, exist_ok=True)
    for name, (label, (message, done)) in badges.items():
        with open(os.path.join(out_dir, f"{name}.json"), "w", encoding="utf-8") as f:
            json.dump(badge(label, message, done), f)
            f.write("\n")
        print(f"{label}: {message}")


if __name__ == "__main__":
    main()
