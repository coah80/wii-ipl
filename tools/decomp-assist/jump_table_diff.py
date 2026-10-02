"""Compare relocated switch destinations after checking instructions with ctxdiff.

Usage: python jump_table_diff.py <unit> <function> [--table <reference-symbol>]
Paths follow ctxdiff.py: build/43U/{src,obj}/<unit>.o. Requires pyelftools.
Exit 0: all selected tables match (or no tables); 1: mismatch; 2: invalid or
ambiguous input. This checks relative destinations, not behavioral equivalence.

Automatic selection covers jumptable_* symbols and multi-entry data objects
whose R_PPC_ADDR32 entries all target the selected function, with at least one
interior destination for objects lacking the jumptable_ prefix. This includes
compiler-generated @ names and custom names, but excludes ordinary callback
tables/vtables. Source locations are inferred from corresponding function relocations,
never from an assumption that both data sections have the same layout.
"""

import argparse
from dataclasses import dataclass
from pathlib import Path
import sys

from elftools.common.exceptions import ELFError
from elftools.elf.elffile import ELFFile


@dataclass(frozen=True)
class Symbol:
    name: str
    section: object
    value: int
    size: int
    kind: str = "STT_OBJECT"


@dataclass(frozen=True)
class Relocation:
    offset: int
    kind: int
    symbol: int
    addend: int


@dataclass
class ObjectInfo:
    sections: dict
    symbols: list
    relocations: dict

    def symbol(self, name):
        found = [s for s in self.symbols if s.name == name
                 and isinstance(s.section, int) and s.size]
        if len(found) != 1:
            raise ValueError("expected one defined symbol: " + name)
        symbol = found[0]
        if (symbol.section not in self.sections or symbol.value < 0
                or symbol.size <= 0
                or symbol.value + symbol.size > self.sections[symbol.section][1]):
            raise ValueError("symbol is outside its section: " + name)
        return symbol

    def location(self, relocation):
        if not 0 <= relocation.symbol < len(self.symbols):
            raise ValueError("relocation symbol index is out of range")
        symbol = self.symbols[relocation.symbol]
        if not isinstance(symbol.section, int):
            return None
        if symbol.section not in self.sections:
            raise ValueError("relocation symbol has an invalid section")
        return symbol.section, symbol.value + relocation.addend

    def relocs(self, section):
        return self.relocations.get(section, {})


def read_object(path):
    with open(path, "rb") as stream:
        elf = ELFFile(stream)
        if (elf.elfclass != 32 or elf.little_endian
                or elf["e_machine"] != "EM_PPC" or elf["e_type"] != "ET_REL"):
            raise ValueError("expected a relocatable big-endian ELF32 PowerPC object")
        symtab = elf.get_section_by_name(".symtab")
        if symtab is None:
            raise ValueError("object has no .symtab")
        symbols = [Symbol(s.name, s["st_shndx"], s["st_value"], s["st_size"],
                          s["st_info"]["type"]) for s in symtab.iter_symbols()]
        sections = {}
        relocations = {}
        for index, section in enumerate(elf.iter_sections()):
            sections[index] = (section.name, section["sh_size"])
            if section["sh_type"] == "SHT_REL":
                raise ValueError("REL relocations are unsupported; expected RELA")
            if section["sh_type"] != "SHT_RELA":
                continue
            if elf.get_section(section["sh_link"]).name != ".symtab":
                raise ValueError("relocation uses a different symbol table")
            entries = relocations.setdefault(section["sh_info"], {})
            for r in section.iter_relocations():
                if r["r_offset"] in entries:
                    raise ValueError("multiple relocations at the same offset")
                entries[r["r_offset"]] = Relocation(
                    r["r_offset"], r["r_info_type"], r["r_info_sym"], r["r_addend"])
        return ObjectInfo(sections, symbols, relocations)


def jump_target(obj, relocation, function):
    if relocation is None or relocation.kind != 1:  # R_PPC_ADDR32
        return None
    location = obj.location(relocation)
    if location is None or location[0] != function.section:
        return None
    offset = location[1] - function.value
    if offset < 0 or offset >= function.size or offset % 4:
        return None
    return offset


def reference_tables(obj, function, name=None):
    candidates = [obj.symbol(name)] if name else [
        s for s in obj.symbols if s.size and (
            s.name.startswith("jumptable_") or (
                s.kind == "STT_OBJECT" and s.size >= 8
                and isinstance(s.section, int)
                and obj.sections[s.section][0] in (".data", ".rodata", ".sdata", ".sdata2")))]
    result = []
    for table in candidates:
        if not isinstance(table.section, int) or table.size % 4:
            if name:
                raise ValueError("invalid reference table extent")
            continue
        section_size = obj.sections[table.section][1]
        if table.value < 0 or table.value + table.size > section_size:
            raise ValueError("reference table is outside its section")
        targets = []
        for offset in range(table.value, table.value + table.size, 4):
            target = jump_target(obj, obj.relocs(table.section).get(offset), function)
            if target is None:
                break
            targets.append(target)
        if targets and len(targets) == table.size // 4:
            if name or table.name.startswith("jumptable_") or any(targets):
                result.append((table, targets))
        elif name:
            raise ValueError("reference table does not target the selected function")
    return result


def source_table_location(source, reference, source_fn, reference_fn, table):
    if source_fn.size != reference_fn.size:
        raise ValueError("function sizes differ; check ctxdiff before table matching")
    locations = set()
    for relocation in reference.relocs(reference_fn.section).values():
        if not reference_fn.value <= relocation.offset < reference_fn.value + reference_fn.size:
            continue
        if reference.location(relocation) != (table.section, table.value):
            continue
        offset = source_fn.value + relocation.offset - reference_fn.value
        other = source.relocs(source_fn.section).get(offset)
        if other is None or other.kind != relocation.kind:
            raise ValueError("table-reference relocations differ; check ctxdiff")
        location = source.location(other)
        if location is None:
            raise ValueError("source table reference is undefined")
        if source.sections[location[0]][0] != reference.sections[table.section][0]:
            raise ValueError("source table resolves to a different section")
        locations.add(location)
    if len(locations) != 1:
        raise ValueError("cannot infer one source table from function relocations")
    section, offset = next(iter(locations))
    sizes = {s.size for s in source.symbols if s.section == section
             and s.value == offset and s.size and s.kind != "STT_SECTION"}
    if len(sizes) != 1:
        raise ValueError("source table extent is missing or ambiguous")
    size = next(iter(sizes))
    if size % 4 or offset < 0 or offset + size > source.sections[section][1]:
        raise ValueError("invalid source table extent")
    return section, offset, size


def compare_table(source, reference, source_fn, reference_fn, table, expected):
    section, offset, size = source_table_location(
        source, reference, source_fn, reference_fn, table)
    actual = [jump_target(source, source.relocs(section).get(i), source_fn)
              for i in range(offset, offset + size, 4)]
    differences = []
    for i in range(max(len(actual), len(expected))):
        src = actual[i] if i < len(actual) else None
        ref = expected[i] if i < len(expected) else None
        if i >= min(len(actual), len(expected)) or src != ref:
            differences.append((i, src, ref))
    return actual, differences


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("unit", help="e.g. src/scene/sdChannelSelect/iplSDChannelSelect")
    parser.add_argument("function", help="exact function symbol used by ctxdiff")
    parser.add_argument("--table", help="optional exact reference jump-table symbol")
    args = parser.parse_args(argv)
    try:
        source = read_object(Path("build/43U/src") / (args.unit + ".o"))
        reference = read_object(Path("build/43U/obj") / (args.unit + ".o"))
        source_fn = source.symbol(args.function)
        reference_fn = reference.symbol(args.function)
        tables = reference_tables(reference, reference_fn, args.table)
        mismatch = False
        for table, expected in tables:
            actual, differences = compare_table(
                source, reference, source_fn, reference_fn, table, expected)
            matched = sum(a == b for a, b in zip(actual, expected))
            print("%s: %d/%d entries match (source=%d reference=%d)" %
                  (table.name, matched, len(expected), len(actual), len(expected)))
            for index, src, ref in differences:
                src_text = "unresolved/missing" if src is None else "+0x%X" % src
                ref_text = "missing" if ref is None else "+0x%X" % ref
                print("  [%d] source %s; reference %s" % (index, src_text, ref_text))
            mismatch |= bool(differences)
        print("Compared %d jump table(s); instruction correctness requires ctxdiff." % len(tables))
        return 1 if mismatch else 0
    except (OSError, ValueError, ELFError) as error:
        print("ERROR: %s" % error, file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
