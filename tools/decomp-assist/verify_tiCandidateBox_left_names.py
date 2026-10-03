#!/usr/bin/env python3
"""Read-only verification of the single two-address left-scroll candidate.

Use the project's venv with PYTHONPATH=../local-tools. Inputs are immutable
compiled objects; no compilation or source rewriting is performed.
"""

import argparse
import hashlib
import json
import re

from pathlib import Path
from odiff import dis, sym
from verify_tiCandidateBox_window_name import read_object, changes


FUNCTION = "create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator"
BASE_SHA = "677fd43d2cc7dc39bb0c728006c67d9498f9ca1a5046c2bc6812b2fe80a31fe4"
CANDIDATE_SHA = "31106c95cfcd2e8274f43ee2b5eb51be9861e577a5d967a96e667766feb71200"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("baseline", type=Path)
    parser.add_argument("candidate", type=Path)
    parser.add_argument("--target", type=Path, required=True)
    parser.add_argument("--runtime", type=Path, required=True)
    parser.add_argument("--original-runtime", type=Path, required=True)
    parser.add_argument("--details", type=Path)
    args = parser.parse_args()
    assert hashlib.sha256(args.baseline.read_bytes()).hexdigest() == BASE_SHA
    assert hashlib.sha256(args.candidate.read_bytes()).hexdigest() == CANDIDATE_SHA
    ah, asecs, asyms, arels = read_object(args.baseline)
    bh, bsecs, bsyms, brels = read_object(args.candidate)
    _, tsecs, tsyms, _ = read_object(args.target)
    assert asecs.keys() == bsecs.keys() and len(asyms) == len(bsyms) == 337
    owner = next(s for s in asyms if s["name"] == FUNCTION)
    start = owner["st_value"]
    insertion = start + 0x404
    mapping = {}
    private_names = []
    symbol_proof = []
    code_shifts = []
    for old in asyms:
        private = re.fullmatch(r"@\d+", old["name"]) and old["st_info"]["bind"] == "STB_LOCAL"
        if not old["name"]:
            matches = [s for s in bsyms if s == old]
        elif private:
            matches = [s for s in bsyms if s["name"] == "@" + str(int(old["name"][1:]) + 2)]
        else:
            matches = [s for s in bsyms if s["name"] == old["name"]]
        assert len(matches) == 1, old["name"]
        new = matches[0]
        mapping[old["index"]] = new["index"]
        # String offsets and indices may move, but all semantic fields are checked.
        expected = dict(old, index=new["index"], st_name=new["st_name"], name=new["name"])
        if private:
            assert old["st_info"] == {"bind": "STB_LOCAL", "type": "STT_OBJECT"}
            assert old["section"] != ".text"
            private_names.append([old["index"], old["name"], new["name"]])
        else:
            assert old["name"] == new["name"]
        if old["name"] == FUNCTION:
            assert old["st_size"] == 1408
            expected["st_size"] = 1416
        elif old["section"] == ".text" and old["st_value"] >= start + 1408:
            assert old["st_info"]["type"] == "STT_FUNC"
            expected["st_value"] += 8
            code_shifts.append(old["index"])
        assert new == expected, (old, new, expected)
        symbol_proof.append({"before": old, "after": new})
    assert len(set(mapping.values())) == 337 and len(private_names) == 59 and len(code_shifts) == 129
    assert sum(i != j for i, j in mapping.items()) == 44
    arrays = []
    for sections, symbols in [(asecs, asyms), (bsecs, bsyms), (tsecs, tsyms)]:
        array = next(s for s in symbols if s["name"] == "scPaneNameTable")
        assert array["section"] == ".data" and array["st_value"] == 0x6B4 and array["st_size"] == 132
        data = sections[".data"]["data"][0x6B4:0x6B4 + 132]
        assert data[48:65] == b"B_prdc_scrl_Left\0" and data[68:85] == b"P_prdc_scrl_Left\0"
        arrays.append(data)
    assert arrays[0] == arrays[1] == arrays[2]

    # Reconstruct both complete string tables from their symbol-name intervals.
    # This also verifies every st_name and accounts for every metadata byte.
    for sections, symbols in [(asecs, asyms), (bsecs, bsyms)]:
        data = sections[".strtab"]["data"]
        reconstructed = bytearray(len(data))
        covered = {0}
        for s in symbols:
            encoded = s["name"].encode() + b"\0"
            at = s["st_name"]
            assert data[at:at + len(encoded)] == encoded
            reconstructed[at:at + len(encoded)] = encoded
            covered.update(range(at, at + len(encoded)))
        assert bytes(reconstructed) == data and len(covered) == len(data)
    ac, bc = asecs[".comment"]["data"], bsecs[".comment"]["data"]
    assert ac[:44] == bc[:44] and len(ac) == len(bc) == 44 + 8 * 337
    comment_records = []
    for i, j in mapping.items():
        old, new = ac[44 + 8 * i:44 + 8 * (i + 1)], bc[44 + 8 * j:44 + 8 * (j + 1)]
        assert old == new
        comment_records.append([i, j, old.hex()])

    relocation_proof = []
    helper_changes = []
    assert arels.keys() == brels.keys()
    for section in arels:
        assert len(arels[section]) == len(brels[section])
        for old, new in zip(arels[section], brels[section]):
            expected = dict(old)
            expected["symbol_index"] = mapping[old["symbol_index"]]
            if section == ".rela.text" and old["offset"] >= insertion:
                expected["offset"] += 8
            target = asyms[old["symbol_index"]]
            if section == ".rela.text" and old["offset"] in (start + 0x10, start + 0x56C):
                required = "_savegpr_27" if old["offset"] == start + 0x10 else "_restgpr_27"
                assert target["name"] == required and old["type"] == 10 and old["addend"] == 0
                new_name = required.replace("27", "25")
                new_target = next(s for s in bsyms if s["name"] == new_name)
                expected["symbol_index"] = new_target["index"]
                helper_changes.append([required, new_name, old["offset"], expected["offset"]])
            else:
                new_target = bsyms[expected["symbol_index"]]
                if target["name"] == FUNCTION:
                    assert old["addend"] == 0
                # The proved bijection checks exact identity/extent for data and
                # named function plus unchanged addend for all code referents.
                assert new_target["section"] == target["section"]
            assert new == expected, (section, old, new, expected)
            relocation_proof.append({"section": section, "before": old, "after": new,
                                     "target_before": target, "target_after": bsyms[new["symbol_index"]]})
    assert len(helper_changes) == 2 and len(relocation_proof) == 752

    section_changes = {}
    header_changes = {}
    for name in asecs:
        a, b = asecs[name], bsecs[name]
        if a["header"]["sh_flags"] & 2 and name != ".text":
            assert a["data"] == b["data"] and a["header"]["sh_size"] == b["header"]["sh_size"]
        delta = changes(a["header"], b["header"])
        if delta:
            header_changes[name] = delta
            if name == ".text":
                assert delta == {"sh_size": [28568, 28576]}
            else:
                assert delta == {"sh_offset": [a["header"]["sh_offset"], a["header"]["sh_offset"] + 8]}
        if a["data"] != b["data"]:
            diffs = [[i, x, y] for i, (x, y) in enumerate(zip(a["data"], b["data"])) if x != y]
            section_changes[name] = {"old_size": len(a["data"]), "new_size": len(b["data"]),
                                     "changed_common_bytes": len(diffs), "byte_differences": diffs,
                                     "old_tail": list(a["data"][len(b["data"]):]),
                                     "new_tail": list(b["data"][len(a["data"]):])}
    assert set(section_changes) == {".text", ".rela.text", ".rela.data", ".symtab", ".strtab", ".comment"}
    assert {k: v["changed_common_bytes"] for k, v in section_changes.items()} == {
        ".text": 21016, ".rela.text": 397, ".rela.data": 40, ".symtab": 320, ".strtab": 2665, ".comment": 26}
    assert changes(ah, bh) == {"e_shoff": [66056, 66064]}
    assert args.candidate.stat().st_size == args.baseline.stat().st_size + 8
    at, bt = asecs[".text"]["data"], bsecs[".text"]["data"]
    assert at[:start] + at[start + 1408:] == bt[:start] + bt[start + 1416:]

    a = dis(str(args.baseline), *sym(str(args.baseline), FUNCTION))
    b = dis(str(args.candidate), *sym(str(args.candidate), FUNCTION))
    original = dis(str(args.target), *sym(str(args.target), FUNCTION))
    assert len(a) == len(original) == 352 and len(b) == 354
    expected = list(a)
    replacements = {
        0x000: ("stwu", "r1, -0x30(r1)"), 0x008: ("stw", "r0, 0x34(r1)"),
        0x00C: ("addi", "r11, r1, 0x30"), 0x010: ("bl", "_savegpr_25+0 [reloc 10]"),
        0x018: ("mr", "r25, r4"), 0x024: ("mr", "r3, r25"),
        0x054: ("mr", "r4, r25"), 0x064: ("mr", "r3, r25"),
        0x0CC: ("mr", "r4, r25"), 0x110: ("mr", "r4, r25"),
        0x404: ("beq", "0x414"), 0x424: ("mr", "r4, r25"),
        0x434: ("mr", "r4, r26"), 0x444: ("mr", "r4, r25"),
        0x470: ("beq", "0x480"), 0x50C: ("addi", "r25, r29, 0x738"),
        0x510: ("beq", "0x520"), 0x52C: ("mr", "r4, r25"),
        0x53C: ("mr", "r4, r25"), 0x568: ("addi", "r11, r1, 0x30"),
        0x56C: ("bl", "_restgpr_25+0 [reloc 10]"), 0x570: ("lwz", "r0, 0x34(r1)"),
        0x578: ("addi", "r1, r1, 0x30"),
    }
    for offset, instruction in replacements.items():
        assert expected[offset // 4] != instruction
        expected[offset // 4] = instruction
    point = 0x404 // 4
    inserted = [("addi", "r26, r30, 0x30"), ("addi", "r25, r30, 0x44")]
    expected[point:point] = inserted
    assert expected == b
    # Explicit provenance of both captured values and the retained window name.
    assert a[0x14 // 4] == ("lis", "r29, .data+0 [reloc 6]")
    assert a[0x28 // 4] == ("addi", "r29, r29, .data+0 [reloc 4]")
    assert a[0x29C // 4] == ("addi", "r30, r29, 0x6b4")
    stack_refs = [(4 * i, instruction) for i, instruction in enumerate(b)
                  if re.search(r"\br1\b|\br11\b", instruction[1])]
    assert [x[0] for x in stack_refs] == [0, 8, 12, 0x570, 0x578, 0x580]
    # No other baseline use of these new registers can be hidden by a rename.
    assert not any(re.search(r"\br25\b|\br26\b", operands) for _, operands in a)
    allocator_refs = [4 * i for i, (_, op) in enumerate(a[:0x118 // 4]) if re.search(r"\br27\b", op)]
    assert allocator_refs == [0x18, 0x24, 0x54, 0x64, 0xCC, 0x110]
    window_refs = [4 * i for i, (_, op) in enumerate(a[0x50C // 4:], 0x50C // 4) if re.search(r"\br28\b", op)]
    assert window_refs == [0x50C, 0x52C, 0x53C]
    assert a[0] == original[0] == ("stwu", "r1, -0x20(r1)")
    helpers = {}
    operands = ["r25, -0x1c(r11)", "r26, -0x18(r11)", "r27, -0x14(r11)",
                "r28, -0x10(r11)", "r29, -0xc(r11)", "r30, -8(r11)", "r31, -4(r11)"]
    for name, mnemonic in [("_savegpr_25", "stw"), ("_restgpr_25", "lwz")]:
        expected_helper = [(mnemonic, op) for op in operands] + [("blr", "")]
        for path in [args.runtime, args.original_runtime]:
            offset, _ = sym(str(path), name)
            assert dis(str(path), offset, 32) == expected_helper
        helpers[name] = expected_helper
    result = {"function_counts": {"baseline": [1408, 352], "candidate": [1416, 354], "target": [1408, 352]},
              "frames": {"baseline": 32, "candidate": 48, "target": 32},
              "extra_stack_bytes": 16, "stack_references": stack_refs, "helper_bodies": helpers,
              "inserted_instructions": inserted, "instruction_replacements_at_baseline_offsets": replacements,
              "symbol_bijection": mapping, "symbol_proof": symbol_proof, "private_names": private_names,
              "comment_record_bijection": comment_records, "section_changes": section_changes,
              "section_header_changes": header_changes, "elf_header_changes": changes(ah, bh),
              "relocation_proof": relocation_proof, "helper_relocation_changes": helper_changes,
              "all_allocated_nontext_bytes_identical": True, "all_sibling_text_identical_under_splice": True,
              "ordinary_call_arguments_and_branch_continuations_preserved": True,
              "no_stack_address_arguments_except_proved_save_restore_helpers": True}
    if args.details:
        args.details.write_text(json.dumps(result, indent=2) + "\n")
    print(json.dumps({"verified": True, "function_counts": result["function_counts"], "frames": result["frames"],
                      "private_names": len(private_names), "symbol_indices_moved": 44, "code_symbols_shifted": len(code_shifts),
                      "relocations_checked": len(relocation_proof), "helper_target_changes": helper_changes,
                      "changed_section_bytes": {k: v["changed_common_bytes"] for k, v in section_changes.items()}}, indent=2))


if __name__ == "__main__":
    main()
