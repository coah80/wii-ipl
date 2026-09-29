#!/usr/bin/env python3
"""Rewrite the progress block in README.md from an objdiff report.

usage: update_readme_progress.py <report.json> <README.md> [commit]
"""
import datetime
import json
import sys

START = "<!-- progress:start -->"
END = "<!-- progress:end -->"


def pct(measures, key):
    return float(measures.get(key) or 0.0)


def main():
    report_path, readme_path = sys.argv[1], sys.argv[2]
    commit = sys.argv[3][:8] if len(sys.argv) > 3 else ""
    m = json.load(open(report_path))["measures"]

    stamp = datetime.datetime.now(datetime.timezone.utc).strftime("%Y-%m-%d %H:%M UTC")
    block = "\n".join([
        START,
        "| Decompiled | Matched | Linked | Data |",
        "|:---:|:---:|:---:|:---:|",
        f"| {pct(m, 'fuzzy_match_percent'):.2f}% | {pct(m, 'matched_code_percent'):.2f}% "
        f"| {pct(m, 'complete_code_percent'):.2f}% | {pct(m, 'matched_data_percent'):.2f}% |",
        "",
        f"units {m.get('complete_units')}/{m.get('total_units')} complete, "
        f"functions {m.get('matched_functions')}/{m.get('total_functions')} matched.",
        "",
        "decompiled = code with a C/C++ implementation (objdiff fuzzy), matched = byte-exact code, "
        "linked = code actually linked into the DOL, data = byte-exact data",
        END,
    ])

    text = open(readme_path, encoding="utf-8").read()
    if START in text and END in text:
        head, rest = text.split(START, 1)
        _, tail = rest.split(END, 1)
        new = head + block + tail
    else:
        anchor = "Progress\n========\n"
        if anchor not in text:
            raise SystemExit("no progress anchor in README")
        new = text.replace(anchor, anchor + block + "\n\n", 1)

    if new != text:
        open(readme_path, "w", encoding="utf-8").write(new)
        print("README progress updated")
    else:
        print("README progress unchanged")


if __name__ == "__main__":
    main()
