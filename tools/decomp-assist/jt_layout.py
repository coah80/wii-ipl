#!/usr/bin/env python3
"""Compare PPC switch cases using ELF relocations and MWCC bounds checks.

Offsets are function-relative. Block lengths end at the next control-flow
leader. Spans extend to the next distinct case or bounds-check default; the
final destination has no known span.
"""
import argparse
import json
from pathlib import Path

from capstone import CS_ARCH_PPC, CS_MODE_32, CS_MODE_BIG_ENDIAN, Cs
from elftools.elf.elffile import ELFFile


def immediate(operand):
    return int(operand, 0)


def read_tables(path, function):
    with open(path, "rb") as stream:
        elf = ELFFile(stream)
        symbols = list(elf.get_section_by_name(".symtab").iter_symbols())
        owner = next(symbol for symbol in symbols if symbol.name == function)
        start, size = owner["st_value"], owner["st_size"]
        code = elf.get_section(owner["st_shndx"])
        decoder = Cs(CS_ARCH_PPC, CS_MODE_32 | CS_MODE_BIG_ENDIAN)
        instructions = {
            ins.address: ins for ins in decoder.disasm(code.data()[start:start + size], start)
        }
        relocations = {}
        for section in elf.iter_sections():
            if section["sh_type"] == "SHT_RELA":
                relocations.setdefault(section["sh_info"], []).extend(section.iter_relocations())
        tables = []
        for relocation in relocations.get(owner["st_shndx"], []):
            address = relocation["r_offset"] & ~3
            if not start <= address < start + size or relocation["r_info_type"] != 6:
                continue
            symbol = symbols[relocation["r_info_sym"]]
            section_index = symbol["st_shndx"]
            if not isinstance(section_index, int) or elf.get_section(section_index)["sh_flags"] & 4:
                continue
            compare = instructions.get(address - 8)
            branch = instructions.get(address - 4)
            if not compare or compare.mnemonic != "cmplwi" or not branch or branch.mnemonic != "bgt":
                continue
            count = immediate(compare.op_str.split(", ")[-1]) + 1
            index_register = compare.op_str.split(", ")[-2]
            lower = 0
            adjustment = instructions.get(address - 12)
            if adjustment and adjustment.mnemonic == "addi":
                operands = adjustment.op_str.split(", ")
                if operands[0] == index_register:
                    lower = -immediate(operands[2])
                    high = instructions.get(address - 16)
                    if high and high.mnemonic == "addis":
                        high_operands = high.op_str.split(", ")
                        if high_operands[0] == operands[1]:
                            lower -= immediate(high_operands[2]) << 16
            default = immediate(branch.op_str.split(", ")[-1]) - start
            offset = symbol["st_value"] + relocation["r_addend"]
            entries = {}
            for entry in relocations.get(section_index, []):
                if not offset <= entry["r_offset"] < offset + count * 4:
                    continue
                destination = symbols[entry["r_info_sym"]]
                if entry["r_info_type"] != 1 or destination["st_shndx"] != owner["st_shndx"]:
                    raise ValueError(f"{path}: unexpected table relocation at {entry['r_offset']:#x}")
                value = destination["st_value"] + entry["r_addend"] - start
                if not 0 <= value < size:
                    raise ValueError(f"{path}: case outside {function}: {value:#x}")
                entries[(entry["r_offset"] - offset) // 4] = value
            if len(entries) != count:
                raise ValueError(f"{path}: incomplete table at {offset:#x}: {len(entries)}/{count}")
            boundaries = sorted(set(entries.values()) | {default})
            lengths = {left: right - left for left, right in zip(boundaries, boundaries[1:])}
            leaders = set(boundaries) | {0, size}
            for ins in instructions.values():
                if not ins.mnemonic.startswith("b") or ins.mnemonic in ("bl", "bla", "bctrl", "bclrl"):
                    continue
                leaders.add(ins.address + 4 - start)
                destination = ins.op_str.split(", ")[-1]
                if destination.startswith("0x"):
                    destination = immediate(destination) - start
                    if 0 <= destination < size:
                        leaders.add(destination)
            ordered = sorted(leaders)
            blocks = {left: right - left for left, right in zip(ordered, ordered[1:])}
            tables.append({
                "section": elf.get_section(section_index).name,
                "offset": offset, "dispatch": address - start, "lower": lower,
                "default": default, "count": count,
                "cases": [
                    {"label": lower + index, "offset": entries[index],
                     "length": lengths.get(entries[index]), "block_length": blocks[entries[index]], "default": entries[index] == default}
                    for index in range(count)
                ],
            })
        return {"size": size, "tables": sorted(tables, key=lambda table: (table["section"], table["offset"]))}


def compare_tables(target, source):
    ours = {(table["section"], table["offset"]): table for table in source["tables"]}
    rows = []
    for table in target["tables"]:
        other = ours.pop((table["section"], table["offset"]), None)
        if other is None or (other["lower"], other["count"]) != (table["lower"], table["count"]):
            raise ValueError(f"table layout differs at {table['section']}+{table['offset']:#x}")
        rows.append({"target": table, "source": other, "matched": sum(
            left["offset"] == right["offset"] for left, right in zip(table["cases"], other["cases"])
        )})
    if ours:
        raise ValueError("source has extra jump tables")
    return rows


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("unit", help="unit path without extension")
    parser.add_argument("function")
    parser.add_argument("--target", type=Path)
    parser.add_argument("--source", type=Path)
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()
    target = read_tables(args.target or Path(f"build/43U/obj/{args.unit}.o"), args.function)
    source = read_tables(args.source or Path(f"build/43U/src/{args.unit}.o"), args.function)
    rows = compare_tables(target, source)
    matched = sum(row["matched"] for row in rows)
    count = sum(row["target"]["count"] for row in rows)
    if args.json:
        print(json.dumps({"function": args.function, "target_size": target["size"],
                          "source_size": source["size"], "matched": matched, "count": count, "tables": rows}, indent=2))
        return
    print(f"{args.function}: instructions target={target['size'] // 4} ours={source['size'] // 4}")
    for row in rows:
        left, right = row["target"], row["source"]
        print(f"\n{left['section']}+{left['offset']:#x}: {left['count']} entries, {row['matched']} at target offset")
        print("case          target    ours      target block  our block  target span  our span  delta")
        for case, other in zip(left["cases"], right["cases"]):
            target_length = "?" if case["length"] is None else hex(case["length"])
            our_length = "?" if other["length"] is None else hex(other["length"])
            label = f"{case['label']:#x}" + ("/default" if case["default"] else "")
            print(f"{label:<14} {case['offset']:#08x}  {other['offset']:#08x}  {case['block_length']:#12x}  {other['block_length']:#9x}  {target_length:>11}  {our_length:>8}  {other['offset'] - case['offset']:+d}")
    print(f"\nCases at target offset: {matched}/{count}")


if __name__ == "__main__":
    main()
