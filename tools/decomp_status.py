import argparse
import json
import os
from pathlib import Path


def number(value):
    return int(value)


def percent(value, total):
    if total == 0:
        return 0.0
    return round(value * 100.0 / total, 5)


def byte_measure(measures, kind):
    total = number(measures[f"total_{kind}"])
    matched = number(measures[f"matched_{kind}"])
    complete = number(measures[f"complete_{kind}"])
    return {
        "total": total,
        "matched": matched,
        "matched_percent": percent(matched, total),
        "complete": complete,
        "complete_percent": percent(complete, total),
    }


def build_status(report):
    measures = report["measures"]
    total_units = number(measures["total_units"])
    complete_units = number(measures["complete_units"])
    categories = []
    for category in report.get("categories", []):
        category_measures = category["measures"]
        category_total_units = number(category_measures["total_units"])
        category_complete_units = number(category_measures["complete_units"])
        categories.append(
            {
                "id": category["id"],
                "name": category["name"],
                "decompiled_percent": float(category_measures["matched_code_percent"]),
                "fully_linked_percent": float(category_measures["complete_code_percent"]),
                "units": {
                    "total": category_total_units,
                    "complete": category_complete_units,
                    "complete_percent": percent(category_complete_units, category_total_units),
                },
            }
        )
    return {
        "report_version": report["version"],
        "commit": os.environ.get("GITHUB_SHA"),
        "decompiled_percent": float(measures["matched_code_percent"]),
        "fully_linked_percent": float(measures["complete_code_percent"]),
        "code": byte_measure(measures, "code"),
        "data": byte_measure(measures, "data"),
        "functions": {
            "total": number(measures["total_functions"]),
            "matched": number(measures["matched_functions"]),
            "matched_percent": float(measures["matched_functions_percent"]),
        },
        "units": {
            "total": total_units,
            "complete": complete_units,
            "complete_percent": percent(complete_units, total_units),
        },
        "categories": categories,
    }


def markdown(status):
    lines = [
        f"## Wii Menu is {status['decompiled_percent']:.2f}% decompiled",
        f"**{status['fully_linked_percent']:.2f}% fully linked**",
        "",
        "| Metric | Matched | Fully linked | Total |",
        "| --- | ---: | ---: | ---: |",
        f"| Code | {status['code']['matched_percent']:.2f}% | {status['code']['complete_percent']:.2f}% | {status['code']['total']:,} bytes |",
        f"| Data | {status['data']['matched_percent']:.2f}% | {status['data']['complete_percent']:.2f}% | {status['data']['total']:,} bytes |",
        f"| Functions | {status['functions']['matched_percent']:.2f}% | — | {status['functions']['total']:,} |",
        f"| Units | {status['units']['complete_percent']:.2f}% | — | {status['units']['total']:,} |",
        "",
        "### Categories",
        "",
        "| Category | Decompiled | Fully linked | Units complete |",
        "| --- | ---: | ---: | ---: |",
    ]
    for category in status["categories"]:
        units = category["units"]
        lines.append(
            f"| {category['name']} | {category['decompiled_percent']:.2f}% | "
            f"{category['fully_linked_percent']:.2f}% | {units['complete']}/{units['total']} |"
        )
    return "\n".join(lines)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("report", type=Path)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--summary", type=Path)
    args = parser.parse_args()

    status = build_status(json.loads(args.report.read_text(encoding="utf-8")))
    args.output.write_text(json.dumps(status, indent=2) + "\n", encoding="utf-8")
    output = markdown(status)
    if args.summary:
        with args.summary.open("a", encoding="utf-8") as summary:
            summary.write(output + "\n")
    print(output)


if __name__ == "__main__":
    main()
