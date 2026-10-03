#!/usr/bin/env python3
"""Read-only compatibility proof for right-scroll capture on base 5af01fa8.

Use the project venv with PYTHONPATH=../local-tools. No input is modified.
"""
import argparse
import copy
import hashlib
import json
import re
import struct
from pathlib import Path

from capstone import Cs, CS_ARCH_PPC, CS_MODE_32, CS_MODE_BIG_ENDIAN
from odiff import dis, sym
from verify_tiCandidateBox_window_name import read_object, changes

FUNCTION = "create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator"
BASE_SHA = "6f9055cfa4b93bb03d9013f13e9569eff6ec36cbab02bf21af56b7b9cd87866d"
CANDIDATE_SHA = "b3a52f551c2ac0f28f5580a332789e837446b5bd139512989bd2e020f09c85e4"
DOL_SHA1 = "26116613f624061ba99c8d1a299aaa6efa85670d"


def location(offset):
    return offset + 4 * (offset >= 0x474) + 4 * (offset >= 0x478)


def dol_read(dol, address, size):
    matches = []
    for off_base, address_base, size_base, count in [(0, 0x48, 0x90, 7), (0x1C, 0x64, 0xAC, 11)]:
        for i in range(count):
            offset, start, extent = [struct.unpack_from(">I", dol, base + 4 * i)[0]
                                     for base in (off_base, address_base, size_base)]
            if start <= address and address + size <= start + extent:
                matches.append(dol[offset + address - start:offset + address - start + size])
    assert len(matches) == 1 and len(matches[0]) == size
    return matches[0]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("baseline", type=Path)
    parser.add_argument("candidate", type=Path)
    parser.add_argument("--target", required=True, type=Path)
    parser.add_argument("--runtime", required=True, type=Path)
    parser.add_argument("--original-runtime", required=True, type=Path)
    parser.add_argument("--original-dol", required=True, type=Path)
    parser.add_argument("--details", type=Path)
    parser.add_argument("--evidence", required=True, type=Path, help="Completed current-base/candidate source, report, and all-object hash snapshots")
    args = parser.parse_args()
    assert hashlib.sha256(args.baseline.read_bytes()).hexdigest() == BASE_SHA
    assert hashlib.sha256(args.candidate.read_bytes()).hexdigest() == CANDIDATE_SHA
    ah, asecs, asyms, arels = read_object(args.baseline)
    bh, bsecs, bsyms, brels = read_object(args.candidate)
    _, tsecs, tsyms, trels = read_object(args.target)
    assert asecs.keys() == bsecs.keys() and len(asyms) == len(bsyms) == 337
    owner = next(s for s in asyms if s["name"] == FUNCTION)
    start = owner["st_value"]

    # All symbol fields and indices are accounted. Only private object names,
    # this function's size, and later function positions may change.
    renamed, shifted, symbol_proof = [], [], []
    for old, new in zip(asyms, bsyms):
        expected = dict(old)
        if re.fullmatch(r"@\d+", old["name"]):
            assert old["st_info"] == {"bind": "STB_LOCAL", "type": "STT_OBJECT"}
            assert old["section"] != ".text"
            expected["name"] = "@" + str(int(old["name"][1:]) + 2)
            renamed.append([old["index"], old["name"], new["name"]])
        if old["name"] == FUNCTION:
            assert old["st_size"] == 1416
            expected["st_size"] = 1424
        elif old["section"] == ".text" and old["st_value"] >= start + 1416:
            assert old["st_info"]["type"] == "STT_FUNC"
            expected["st_value"] += 8
            shifted.append(old["index"])
        assert new == expected, (old, new, expected)
        symbol_proof.append({"before": old, "after": new})
    assert len(renamed) == 59 and len(shifted) == 129
    # Reconstruct every string-table byte, including symbol name offsets.
    for sections, symbols in [(asecs, asyms), (bsecs, bsyms)]:
        data = sections[".strtab"]["data"]
        reconstructed, covered = bytearray(len(data)), {0}
        for s in symbols:
            encoded, at = s["name"].encode() + b"\0", s["st_name"]
            assert data[at:at + len(encoded)] == encoded
            reconstructed[at:at + len(encoded)] = encoded
            covered.update(range(at, at + len(encoded)))
        assert bytes(reconstructed) == data and len(covered) == len(data)

    relocation_proof, moved_relocations = [], []
    assert arels.keys() == brels.keys()
    for section in arels:
        assert len(arels[section]) == len(brels[section])
        for old, new in zip(arels[section], brels[section]):
            expected = dict(old)
            if section == ".rela.text":
                relative = old["offset"] - start
                expected["offset"] = start + location(relative)
            assert new == expected, (section, old, new, expected)
            # The checked same-index symbol relationship preserves the target,
            # including unnamed section references and compiler-private labels.
            before, after = asyms[old["symbol_index"]], bsyms[new["symbol_index"]]
            assert before["section"] == after["section"]
            if before["section"] == ".text":
                assert before["st_info"]["type"] == "STT_FUNC"
                if before["name"] == FUNCTION:
                    assert old["addend"] == 0
                else:
                    assert before["st_size"] == after["st_size"]
                    assert 0 <= old["addend"] < before["st_size"]
                    at = before["st_value"] + old["addend"]
                    bt = after["st_value"] + new["addend"]
                    assert asecs[".text"]["data"][at:at + 4] == bsecs[".text"]["data"][bt:bt + 4]
            if old["offset"] != new["offset"]:
                moved_relocations.append([old["offset"], new["offset"]])
            relocation_proof.append({"section": section, "before": old, "after": new,
                                     "target_before": before, "target_after": after})
    assert len(relocation_proof) == 752
    assert all(y - x == 8 for x, y in moved_relocations)

    section_changes, header_changes = {}, {}
    for name in asecs:
        a, b = asecs[name], bsecs[name]
        if a["header"]["sh_flags"] & 2 and name != ".text":
            assert a["data"] == b["data"] and a["header"]["sh_size"] == b["header"]["sh_size"]
        delta = changes(a["header"], b["header"])
        if delta:
            header_changes[name] = delta
            if name == ".text":
                assert delta == {"sh_size": [28576, 28584]}
            else:
                assert delta == {"sh_offset": [a["header"]["sh_offset"], a["header"]["sh_offset"] + 8]}
        if a["data"] != b["data"]:
            diffs = [[i, x, y] for i, (x, y) in enumerate(zip(a["data"], b["data"])) if x != y]
            section_changes[name] = {"old_size": len(a["data"]), "new_size": len(b["data"]),
                                     "changed_common_bytes": len(diffs), "byte_differences": diffs,
                                     "old_tail": list(a["data"][len(b["data"]):]),
                                     "new_tail": list(b["data"][len(a["data"]):])}
    assert {k: v["changed_common_bytes"] for k, v in section_changes.items()} == {
        ".text": 20906, ".rela.text": 338, ".symtab": 134, ".strtab": 75}
    assert changes(ah, bh) == {"e_shoff": [66064, 66072]}
    assert args.candidate.stat().st_size == args.baseline.stat().st_size + 8
    at, bt = asecs[".text"]["data"], bsecs[".text"]["data"]
    assert at[:start] + at[start + 1416:] == bt[:start] + bt[start + 1424:]

    a = dis(str(args.baseline), *sym(str(args.baseline), FUNCTION))
    b = dis(str(args.candidate), *sym(str(args.candidate), FUNCTION))
    target = dis(str(args.target), *sym(str(args.target), FUNCTION))
    assert (len(a), len(b), len(target)) == (354, 356, 352)
    inserted = {0x474: ("addi", "r25, r30, 0x58"), 0x47C: ("addi", "r26, r30, 0x6c")}
    replacements = {0x478: ("beq", "0x488"), 0x498: ("mr", "r4, r26"),
                    0x4A8: ("mr", "r4, r25"), 0x4B8: ("mr", "r4, r26"),
                    0x518: ("beq", "0x528")}
    expected = [None] * 356
    for offset, instruction in inserted.items():
        expected[offset // 4] = instruction
    for i, instruction in enumerate(a):
        expected[location(4 * i) // 4] = replacements.get(4 * i, instruction)
    assert expected == b
    branch_proof = []
    for i, (mnemonic, operands) in enumerate(a):
        if mnemonic.startswith("b") and mnemonic not in ("bl", "blr", "bctrl", "bctr"):
            assert re.fullmatch(r"0x[0-9a-f]+", operands), (i, mnemonic, operands)
            assert b[location(4 * i) // 4] == (mnemonic, hex(location(int(operands, 16))))
            branch_proof.append([4 * i, location(4 * i), int(operands, 16), location(int(operands, 16))])
    calls = lambda seq: [instruction for instruction in seq if instruction[0] in ("bl", "bctrl")]
    assert calls(a) == calls(b)
    # There is no register substitution elsewhere. New definitions occur after
    # all left-name uses and end before the separate window-name definition.
    old_refs = [(4 * i, instruction) for i, instruction in enumerate(a)
                if re.search(r"\br25\b|\br26\b", instruction[1])]
    new_refs = [(4 * i, instruction) for i, instruction in enumerate(b)
                if re.search(r"\br25\b|\br26\b", instruction[1])]
    assert not [x for x in old_refs if 0x450 <= x[0] < 0x514]
    assert [(x, y) for x, y in new_refs if 0x450 <= x < 0x51C] == [
        (0x474, inserted[0x474]), (0x47C, inserted[0x47C]),
        (0x4A0, ("mr", "r4, r26")), (0x4B0, ("mr", "r4, r25")), (0x4C0, ("mr", "r4, r26"))]
    assert a[0x14 // 4] == ("lis", "r29, .data+0 [reloc 6]")
    assert a[0x28 // 4] == ("addi", "r29, r29, .data+0 [reloc 4]")
    assert a[0x29C // 4] == ("addi", "r30, r29, 0x6b4")
    assert not any(mnemonic in ("mr", "addi", "lis", "lwz", "add", "li") and operands.startswith("r30,")
                   for mnemonic, operands in a[0x2A0 // 4:])
    assert a[0] == b[0] == ("stwu", "r1, -0x30(r1)")
    assert target[0] == ("stwu", "r1, -0x20(r1)")
    stack = lambda seq: [(4 * i, instruction) for i, instruction in enumerate(seq)
                         if re.search(r"\br1\b|\br11\b", instruction[1])]
    assert stack(b) == [(location(offset), instruction) for offset, instruction in stack(a)]
    assert [offset for offset, _ in stack(a)] == [0, 8, 12, 0x570, 0x578, 0x580]
    helpers = {}
    operands = ["r25, -0x1c(r11)", "r26, -0x18(r11)", "r27, -0x14(r11)",
                "r28, -0x10(r11)", "r29, -0xc(r11)", "r30, -8(r11)", "r31, -4(r11)"]
    for name, mnemonic in [("_savegpr_25", "stw"), ("_restgpr_25", "lwz")]:
        helper = [(mnemonic, op) for op in operands] + [("blr", "")]
        for path in [args.runtime, args.original_runtime]:
            offset, _ = sym(str(path), name)
            assert dis(str(path), offset, 32) == helper
        helpers[name] = helper

    arrays = []
    for sections, symbols in [(asecs, asyms), (bsecs, bsyms), (tsecs, tsyms)]:
        array = next(s for s in symbols if s["name"] == "scPaneNameTable")
        assert array["section"] == ".data" and array["st_value"] == 0x6B4 and array["st_size"] == 132
        data = sections[".data"]["data"][0x6B4:0x738]
        assert data[88:105] == b"B_prdc_scrl_Rght\0" and data[108:125] == b"P_prdc_scrl_Rght\0"
        arrays.append(data)
    dol = args.original_dol.read_bytes()
    assert hashlib.sha1(dol).hexdigest() == DOL_SHA1
    arrays.append(dol_read(dol, 0x8165D984, 132))
    assert all(data == arrays[0] for data in arrays)
    target_owner = next(s for s in tsyms if s["name"] == FUNCTION)
    target_start = target_owner["st_value"]
    object_text = tsecs[".text"]["data"][target_start:target_start + 1408]
    dol_text = dol_read(dol, 0x814288D0, 1408)
    relocation_words = {(r["offset"] - target_start) & ~3 for r in trels[".rela.text"]
                        if target_start <= r["offset"] < target_start + 1408}
    for offset in range(0, 1408, 4):
        if offset not in relocation_words:
            assert object_text[offset:offset + 4] == dol_text[offset:offset + 4]
    md = Cs(CS_ARCH_PPC, CS_MODE_32 | CS_MODE_BIG_ENDIAN)
    for name, address in [("_savegpr_25", 0x815F94B8), ("_restgpr_25", 0x815F9504)]:
        actual = [(i.mnemonic, i.op_str) for i in md.disasm(dol_read(dol, address, 32), 0)]
        assert actual == helpers[name]
    original = {i.address: (i.mnemonic, i.op_str) for i in md.disasm(dol_text, 0)}
    assert original[0x14] == ("lis", "r30, -0x7e9a")
    assert original[0x28] == ("addi", "r30, r30, -0x2d30")
    assert ((0x8166 << 16) - 0x2D30) == 0x8165D984 - 0x6B4
    right_target = {0x464: ("addi", "r28, r30, 0x70c"), 0x46C: ("addi", "r27, r30, 0x720"),
                    0x490: ("mr", "r4, r27"), 0x4A0: ("mr", "r4, r28"), 0x4B0: ("mr", "r4, r27")}
    for offset, instruction in right_target.items():
        assert target[offset // 4] == original[offset] == instruction
    # Revalidate the exact current source hunk and current 110-function baseline.
    # Historical d0 hashes and proof remain separate; no old snapshot is used as
    # a substitute for the current external geometry implementation.
    source_base = (args.evidence / "baseline.cpp").read_bytes()
    source_candidate = (args.evidence / "candidate.cpp").read_bytes()
    assert hashlib.sha256(source_base).hexdigest() == "318b7768c0b35d2e0f785c655aae39183a7aa61e44abb76bf2e70f7df2899f1c"
    assert hashlib.sha256(source_candidate).hexdigest() == "b3677b0adccaf52b31b3abb4514f4174cf14be775820e7aa84805faa0b5f9b7d"
    old = b"            mRightScroll.Create(this, paneNames + 108, paneNames + 88);"
    new = (b"            const char* rightScrollBoundName = paneNames + 88;\n"
           b"            const char* rightScrollPaneName = paneNames + 108;\n"
           b"            mRightScroll.Create(this, rightScrollPaneName, rightScrollBoundName);")
    assert source_base.count(old) == 1 and source_base.replace(old, new) == source_candidate
    reports = [json.loads((args.evidence / (tag + "-report.json")).read_text())
               for tag in ("baseline", "candidate")]
    units = [{u["name"]: u for u in report["units"]} for report in reports]
    assert units[0].keys() == units[1].keys() and len(units[0]) == 1027
    unit = "main/src/keyboard/tiCandidateBox"
    assert all(units[0][n] == units[1][n] for n in units[0] if n != unit)
    before, after = units[0][unit], units[1][unit]
    for u in (before, after):
        assert u["measures"]["matched_functions"] == 110
        assert u["measures"]["matched_code"] == "21728"
        assert u["measures"]["matched_data"] == "4652"
    assert [u["measures"]["fuzzy_match_percent"] for u in (before, after)] == [99.6285, 99.71067]
    normalized = copy.deepcopy(after)
    normalized["measures"]["fuzzy_match_percent"] = before["measures"]["fuzzy_match_percent"]
    for old_function, new_function in zip(before["functions"], normalized["functions"]):
        if old_function["name"] == FUNCTION:
            assert (old_function["fuzzy_match_percent"], new_function["fuzzy_match_percent"]) == (94.59091, 95.99148)
            new_function["fuzzy_match_percent"] = old_function["fuzzy_match_percent"]
    for old_section, new_section in zip(before["sections"], normalized["sections"]):
        if old_section["name"] == ".text":
            new_section["fuzzy_match_percent"] = old_section["fuzzy_match_percent"]
    assert normalized == before
    exact = []
    for f in after["functions"]:
        if f["fuzzy_match_percent"] == 100:
            for path in (args.baseline, args.candidate):
                actual = dis(str(path), *sym(str(path), f["name"]))
                original_function = dis(str(args.target), *sym(str(args.target), f["name"]))
                assert actual == original_function, f["name"]
            exact.append(f["name"])
    geometry = "CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv"
    assert geometry in exact and len(exact) == 110
    objects = [json.loads((args.evidence / (tag + "-all-objects.json")).read_text())
               for tag in ("baseline", "candidate")]
    assert objects[0].keys() == objects[1].keys() and len(objects[0]) == 1027
    owned_object = "build/43U/src/src/keyboard/tiCandidateBox.o"
    assert [n for n in objects[0] if objects[0][n] != objects[1][n]] == [owned_object]
    assert objects[0][owned_object] == BASE_SHA and objects[1][owned_object] == CANDIDATE_SHA
    current_state = {"base": "5af01fa8b9ed69e08d153b6ecb6aae4eb43e9efb",
                     "candidate": "376d425a7393b9dfe6a381df9d0e3a751ae06f80",
                     "unchanged_exact_functions": exact, "other_unit_records_unchanged": 1026,
                     "other_object_hashes_unchanged": 1026, "source_hunk_exact": True,
                     "geometry_preserved_exact": True, "nonfuzzy_unit_fields_unchanged": True}
    result = {"verified": True, "counts": {"baseline": [1416, 354], "candidate": [1424, 356], "target": [1408, 352]},
              "current_state": current_state,
              "frames": {"baseline": 48, "candidate": 48, "target": 32},
              "insertions_at_candidate_offsets": inserted, "replacements_at_baseline_offsets": replacements,
              "branches": branch_proof, "unchanged_call_sequence": calls(a), "old_register_references": old_refs,
              "new_register_references": new_refs, "stack_references": stack(b), "helper_bodies": helpers,
              "original_dol_sha1": DOL_SHA1, "original_dol_unrelocated_instruction_words_checked": 352 - len(relocation_words),
              "right_target": right_target, "pane_name_bytes": arrays[0].hex(), "pane_name_address": 0x8165D984,
              "symbol_proof": symbol_proof, "private_renames": renamed, "shifted_symbols": shifted,
              "relocation_proof": relocation_proof, "shifted_relocations": moved_relocations,
              "section_changes": section_changes, "section_header_changes": header_changes, "elf_header_changes": changes(ah, bh),
              "all_allocated_nontext_bytes_identical": True, "all_nontext_relocations_identical": True,
              "all_sibling_text_identical_under_splice": True, "all_other_section_payloads_identical": True}
    if args.details:
        args.details.write_text(json.dumps(result, indent=2) + "\n")
    print(json.dumps({"verified": True, "current_exact_functions": len(exact), "current_geometry_preserved_exact": True,
                      "other_objects_and_unit_records_unchanged": 1026, "counts": result["counts"], "frames": result["frames"],
                      "private_names": len(renamed), "symbol_indices_changed": 0, "shifted_symbols": len(shifted),
                      "relocations_checked": len(relocation_proof), "relocations_moved": len(moved_relocations),
                      "changed_section_bytes": {k: v["changed_common_bytes"] for k, v in section_changes.items()},
                      "original_dol_unrelocated_instruction_words_checked": result["original_dol_unrelocated_instruction_words_checked"]}, indent=2))


if __name__ == "__main__":
    main()
