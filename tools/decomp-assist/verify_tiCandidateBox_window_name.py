#!/usr/bin/env python3
"""Verify the single window-name capture against its compiled baseline.

Run with the project's venv and PYTHONPATH pointing to local-tools:
  python verify_tiCandidateBox_window_name.py baseline.o candidate.o --details proof.json
This reads objects only. It never compiles or changes either input.
"""

import argparse
import hashlib
import json
import re
from pathlib import Path

from elftools.elf.elffile import ELFFile
from odiff import dis, sym


FUNCTION = "create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator"
BASE_SHA = "60d61cfbc40a8bd72bb04628c7a385004aff7c2b17a72421f3f10129a624f9cb"
CANDIDATE_SHA = "677fd43d2cc7dc39bb0c728006c67d9498f9ca1a5046c2bc6812b2fe80a31fe4"


def read_object(path):
    with path.open("rb") as stream:
        elf = ELFFile(stream)
        sections = {}
        for section in elf.iter_sections():
            sections[section.name] = {
                "header": dict(section.header),
                "data": section.data(),
            }
        symbols = []
        for index, symbol in enumerate(elf.get_section_by_name(".symtab").iter_symbols()):
            fields = dict(symbol.entry)
            fields["st_info"] = dict(fields["st_info"])
            fields["st_other"] = dict(fields["st_other"])
            fields["name"] = symbol.name
            fields["index"] = index
            section_index = symbol["st_shndx"]
            fields["section"] = elf.get_section(section_index).name if isinstance(section_index, int) else section_index
            symbols.append(fields)
        relocations = {}
        for section in elf.iter_sections():
            if section["sh_type"] != "SHT_RELA":
                continue
            relocations[section.name] = [
                {
                    "offset": relocation["r_offset"],
                    "type": relocation["r_info_type"],
                    "symbol_index": relocation["r_info_sym"],
                    "addend": relocation["r_addend"],
                }
                for relocation in section.iter_relocations()
            ]
        return dict(elf.header), sections, symbols, relocations


def changes(before, after):
    return {key: [before[key], after[key]] for key in before if before[key] != after[key]}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("baseline", type=Path)
    parser.add_argument("candidate", type=Path)
    parser.add_argument("--target", type=Path, help="Original local tiCandidateBox object, for target size/count checks")
    parser.add_argument("--details", type=Path)
    args = parser.parse_args()
    assert hashlib.sha256(args.baseline.read_bytes()).hexdigest() == BASE_SHA
    assert hashlib.sha256(args.candidate.read_bytes()).hexdigest() == CANDIDATE_SHA
    ah, asecs, asyms, arels = read_object(args.baseline)
    bh, bsecs, bsyms, brels = read_object(args.candidate)
    assert asecs.keys() == bsecs.keys() and len(asyms) == len(bsyms) == 337
    owner = next(s for s in asyms if s["name"] == FUNCTION)
    start = owner["st_value"]
    insertion = start + 0x50C
    changed_sections = {}
    header_changes = {}
    for name in asecs:
        a, b = asecs[name], bsecs[name]
        delta = changes(a["header"], b["header"])
        if delta:
            header_changes[name] = delta
        if a["data"] != b["data"]:
            byte_differences = [[i, x, y] for i, (x, y) in enumerate(zip(a["data"], b["data"])) if x != y]
            changed_sections[name] = {
                "allocated": bool(a["header"]["sh_flags"] & 2),
                "old_size": len(a["data"]),
                "new_size": len(b["data"]),
                "changed_common_bytes": len(byte_differences),
                "byte_differences": byte_differences,
                "old_tail": list(a["data"][len(b["data"]):]),
                "new_tail": list(b["data"][len(a["data"]):]),
            }
    assert set(changed_sections) == {".text", ".rela.text", ".symtab", ".strtab"}
    assert changed_sections[".strtab"]["changed_common_bytes"] == 65
    assert changed_sections[".symtab"]["changed_common_bytes"] == 131
    assert changed_sections[".rela.text"]["changed_common_bytes"] == 335
    assert len(bsecs[".text"]["data"]) == len(asecs[".text"]["data"]) + 4
    # Section payload bytes and section-header physical placement are distinct.
    assert ah == bh
    assert header_changes == {
        ".text": {"sh_size": [28564, 28568]},
        ".ctors": {"sh_offset": [28616, 28620]},
    }
    # Four bytes of pre-rodata file alignment absorb the longer text section.
    assert args.baseline.stat().st_size == args.candidate.stat().st_size
    assert asecs[".ctors"]["header"]["sh_size"] == bsecs[".ctors"]["header"]["sh_size"] == 4
    assert asecs[".rodata"]["header"]["sh_offset"] == bsecs[".rodata"]["header"]["sh_offset"] == 28624
    assert args.baseline.read_bytes()[28620:28624] == bytes(4)

    symbol_changes = []
    renamed = []
    shifted = []
    for a, b in zip(asyms, bsyms):
        delta = changes(a, b)
        if not delta:
            continue
        symbol_changes.append({"index": a["index"], "before": a, "after": b, "changes": delta})
        if "name" in delta:
            assert set(delta) == {"name"}
            assert a["st_info"] == {"bind": "STB_LOCAL", "type": "STT_OBJECT"}
            assert re.fullmatch(r"@\d+", a["name"]) and re.fullmatch(r"@\d+", b["name"])
            assert a["section"] != ".text"
            renamed.append(a["index"])
        elif "st_size" in delta:
            assert set(delta) == {"st_size"} and a["name"] == FUNCTION
            assert a["st_size"] == 1404 and b["st_size"] == 1408
        else:
            assert set(delta) == {"st_value"} and a["section"] == ".text"
            assert a["st_info"]["type"] == "STT_FUNC"
            assert a["st_value"] >= start + 1404 and b["st_value"] == a["st_value"] + 4
            shifted.append(a["index"])
    assert len(renamed) == 59 and len(shifted) == 129 and len(symbol_changes) == 189

    assert arels.keys() == brels.keys()
    referent_checks = []
    for section in arels:
        assert len(arels[section]) == len(brels[section])
        for a, b in zip(arels[section], brels[section]):
            expected_offset = a["offset"] + (4 if section == ".rela.text" and a["offset"] >= insertion else 0)
            assert b == dict(a, offset=expected_offset)
            before, after = asyms[a["symbol_index"]], bsyms[b["symbol_index"]]
            if before["section"] == ".text":
                # Code referents retain the same named function and addend.
                assert before["name"] == after["name"] and before["st_info"]["type"] == "STT_FUNC"
                if before["name"] == FUNCTION:
                    assert a["addend"] == 0
            else:
                assert before["section"] == after["section"]
                assert before["st_value"] == after["st_value"] and before["st_size"] == after["st_size"]
                if before["name"] != after["name"]:
                    assert before["index"] in renamed
            referent_checks.append({"relocation_section": section, "before": a, "after": b, "target_before": before, "target_after": after})
        if section != ".rela.text":
            assert asecs[section]["data"] == bsecs[section]["data"]

    at, bt = asecs[".text"]["data"], bsecs[".text"]["data"]
    assert at[:start] + at[start + 1404:] == bt[:start] + bt[start + 1408:]
    a = dis(str(args.baseline), *sym(str(args.baseline), FUNCTION))
    b = dis(str(args.candidate), *sym(str(args.candidate), FUNCTION))
    point = 0x50C // 4
    assert a[:point] == b[:point] and b[point] == ("addi", "r28, r29, 0x738")
    instruction_changes = []
    for i, old in enumerate(a):
        j = i + (i >= point)
        if old != b[j]:
            instruction_changes.append((4 * i, 4 * j, old, b[j]))
    assert instruction_changes == [
        (0x50C, 0x510, ("beq", "0x514"), ("beq", "0x518")),
        (0x528, 0x52C, ("addi", "r4, r29, 0x738"), ("mr", "r4, r28")),
        (0x538, 0x53C, ("addi", "r4, r29, 0x738"), ("mr", "r4, r28")),
    ]
    assert not any(re.search(r"\br28\b", operands) for _, operands in a[point:])
    assert a[0] == b[0] == ("stwu", "r1, -0x20(r1)") and a[4] == b[4] and a[-6:] == b[-6:]
    target_count = None
    if args.target:
        target_offset, target_size = sym(str(args.target), FUNCTION)
        target = dis(str(args.target), target_offset, target_size)
        assert target_size == 1408 and len(target) == 352 and target[0] == a[0]
        target_count = {"bytes": target_size, "instructions": len(target)}
    report = {
        "function_counts": {"baseline": {"bytes": 1404, "instructions": len(a)}, "candidate": {"bytes": 1408, "instructions": len(b)}, "target": target_count},
        "changed_sections": changed_sections,
        "elf_header_changes": changes(ah, bh),
        "section_header_changes": header_changes,
        "symbol_changes": symbol_changes,
        "private_renamed_symbols": renamed,
        "relocation_referent_checks": referent_checks,
        "instruction_changes_besides_insert": instruction_changes,
        "all_allocated_nontext_payloads_identical": True,
        "all_nontext_raw_relocation_sections_identical": True,
        "all_sibling_text_identical_under_function_splice": True,
        "all_relocation_referents_preserved": True,
        "abi_and_branch_continuations_preserved": True,
    }
    if args.details:
        args.details.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps({"verified": True, "changed_sections": {k: {x: y for x, y in v.items() if x not in ("byte_differences", "old_tail", "new_tail")} for k, v in changed_sections.items()}, "private_name_changes": len(renamed), "code_symbol_shifts": len(shifted), "relocations_verified": len(referent_checks)}, indent=2))


if __name__ == "__main__":
    main()
