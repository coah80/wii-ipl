"""Audit statically addressed narrow-string call arguments after ctxdiff.

Usage: python literal_reference_diff.py [unit ...] [--function NAME]
--function requires exactly one unit. With no units, inspect all units in build/43U/report.json. By default, select
functions scored 100%; --all-functions includes other equal-sized functions.
Requires pyelftools and the sibling jump_table_diff.py.

This is an advisory audit, not a matching gate. It compares bytes, not relocation
names or offsets, and follows constant addresses through GPR moves/additions and
control-flow joins. It deliberately does not dereference mutable pointer globals,
infer dynamic indices, or establish which arguments a callee actually consumes.
Only corresponding calls with the same identity are compared. Binary data can
look like a string: inspect every candidate against the original assembly.
Missing exact symbol names are explicitly skipped in report-driven selection;
compiler aliases are never guessed. No candidates does not prove complete data matching. Exit 0 means no candidates,
1 means candidates require review, and 2 means invalid/incomplete input.
"""

import argparse
from collections import deque
from dataclasses import dataclass
import json
from pathlib import Path
import sys

from elftools.common.exceptions import ELFError
from elftools.elf.elffile import ELFFile

import jump_table_diff as jump

DATA_SECTIONS = {".data", ".rodata", ".sdata", ".sdata2"}
VOLATILE_GPRS = {0, *range(3, 13)}


@dataclass
class LiteralObject:
    info: jump.ObjectInfo
    data: dict

    def relocation(self, section, offset):
        entries = self.info.relocs(section)
        found = [entries[p] for p in (offset, offset + 2) if p in entries]
        if len(found) > 1:
            raise ValueError("multiple relocations in one instruction")
        return found[0] if found else None

    def string(self, pointer, limit=512):
        if pointer is None or pointer[0] != "address":
            return None
        _, section, offset = pointer
        if section not in self.info.sections:
            return None
        if self.info.sections[section][0] not in DATA_SECTIONS or offset < 0:
            return None
        data = self.data.get(section, b"")
        if offset >= len(data):
            return None
        raw = data[offset:offset + limit]
        end = raw.find(b"\0")
        if end < 0:
            return None
        raw = raw[:end]
        if not all(c >= 32 or c in (9, 10, 13) for c in raw):
            return None
        # A relocated word is an address, not literal character bytes.
        if any(offset <= at < offset + end + 1
               for at in self.info.relocs(section)):
            return None
        return raw


def read_object(path):
    info = jump.read_object(path)
    with open(path, "rb") as stream:
        elf = ELFFile(stream)
        data = {i: s.data() for i, s in enumerate(elf.iter_sections())
                if s["sh_type"] == "SHT_PROGBITS" and s["sh_flags"] & 2}
    return LiteralObject(info, data)


def signed(value, bits):
    return value - (1 << bits) if value & (1 << (bits - 1)) else value


def is_call(word):
    op, xo = word >> 26, (word >> 1) & 1023
    return bool(word & 1) and (op == 18 or op == 19 and xo in (16, 528))



def is_tail_call(obj, function, offset, word):
    if word >> 26 != 18 or word & 1:
        return False
    relocation = obj.relocation(function.section, function.value + offset)
    if relocation is None or relocation.kind != 10:
        return False
    if not 0 <= relocation.symbol < len(obj.info.symbols):
        raise ValueError("tail-call relocation symbol is out of range")
    symbol = obj.info.symbols[relocation.symbol]
    return bool(symbol.name) and (not isinstance(symbol.section, int)
                                 or symbol.kind == "STT_FUNC" and symbol.name != function.name)


def call_identity(obj, function, offset, word):
    relocation = obj.relocation(function.section, function.value + offset)
    if relocation is not None:
        if relocation.kind != 10:  # R_PPC_REL24
            return None
        if not 0 <= relocation.symbol < len(obj.info.symbols):
            raise ValueError("call relocation symbol is out of range")
        symbol = obj.info.symbols[relocation.symbol]
        return ("direct", symbol.name, relocation.addend)
    if word >> 26 == 19:
        return ("indirect", (word >> 1) & 1023)
    # A non-relocated direct call has no reliably paired cross-object identity.
    return None


def transfer(obj, function, offset, word, incoming):
    state = dict(incoming)
    op = word >> 26
    rd, ra, rb = (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    xo = (word >> 1) & 1023
    immediate = signed(word & 0xffff, 16)
    if is_call(word):
        return {r: p for r, p in state.items() if r not in VOLATILE_GPRS}
    if op in (14, 15):
        relocation = obj.relocation(function.section, function.value + offset)
        if relocation and relocation.kind in (4, 6, 109):
            location = obj.info.location(relocation)
            if location is not None:
                kind = "high" if relocation.kind == 6 else "address"
                state[rd] = (kind, *location)
                return state
        pointer = incoming.get(ra) if ra else None
        if op == 14 and pointer and pointer[0] == "address":
            state[rd] = ("address", pointer[1], pointer[2] + immediate)
        else:
            state.pop(rd, None)
    elif op == 31 and xo == 444 and rd == rb:  # mr = or rA,rS,rS
        state.pop(ra, None)
        if rd in incoming:
            state[ra] = incoming[rd]
    elif op in (7, 8, 12, 13, 32, 34, 40, 42):
        state.pop(rd, None)
    elif op in (33, 35, 41, 43):
        state.pop(rd, None)
        state.pop(ra, None)
    elif op in (20, 21, 23, 24, 25, 26, 27, 28, 29):
        state.pop(ra, None)
    elif op == 46:  # lmw
        state = {r: p for r, p in state.items() if r < rd}
    elif op in (37, 39, 45, 49, 51, 53, 55, 57, 61):
        state.pop(ra, None)
    elif op == 4:
        # Paired-single indexed updates may write rA. Forget it conservatively.
        state.pop(ra, None)
    elif op in (10, 11, 16, 18, 19, 36, 38, 44, 47, 48, 50,
                52, 54, 56, 59, 60, 63):
        pass
    elif op == 31:
        if xo in (0, 32, 144, 467, 151, 215, 407, 535, 599, 663, 727,
                  598, 854):
            pass
        elif xo in (28, 60, 124, 284, 316, 412, 444, 476, 24, 26, 536,
                    792, 824, 922, 954):
            state.pop(ra, None)
        elif xo in (8, 10, 11, 19, 23, 40, 75, 87, 104, 136,
                    138, 200, 202, 232, 234, 235, 266, 279, 339,
                    343, 459, 491):
            state.pop(rd, None)
        elif xo in (55, 119, 311, 375):
            state.pop(rd, None)
            state.pop(ra, None)
        elif xo in (183, 247, 439, 567, 631, 695, 759):
            state.pop(ra, None)
        else:
            state.clear()
    else:
        state.clear()
    return state


def call_strings(obj, name):
    function = obj.info.symbol(name)
    if function.kind != "STT_FUNC" or function.size % 4 or function.value % 4:
        raise ValueError("expected an aligned function: " + name)
    code = obj.data.get(function.section, b"")
    if function.value + function.size > len(code):
        raise ValueError("function code is unavailable: " + name)
    code = code[function.value:function.value + function.size]
    words = [int.from_bytes(code[i:i + 4], "big") for i in range(0, len(code), 4)]
    targets = set()
    for _, entries in jump.reference_tables(obj.info, function):
        targets.update(entries)
    states, pending = {0: {}}, deque([0])

    def offer(offset, state):
        if offset < 0 or offset >= function.size or offset % 4:
            return
        if offset not in states:
            states[offset] = dict(state)
            pending.append(offset)
            return
        old = states[offset]
        merged = {r: p for r, p in old.items() if state.get(r) == p}
        if merged != old:
            states[offset] = merged
            pending.append(offset)

    while pending:
        offset = pending.popleft()
        word = words[offset // 4]
        op, xo = word >> 26, (word >> 1) & 1023
        state = transfer(obj, function, offset, word, states[offset])
        if is_tail_call(obj, function, offset, word):
            continue
        if op == 18 and not word & 1:
            if word & 2:
                continue  # Absolute branches do not name local section offsets.
            offer(offset + signed(word & 0x03fffffc, 26), state)
        elif op == 16:
            if word & 1:
                raise ValueError("conditional branch-and-link is unsupported")
            if not word & 2:
                offer(offset + signed(word & 0xfffc, 16), state)
            if ((word >> 21) & 0x14) != 0x14:
                offer(offset + 4, state)
        elif op == 19 and xo in (16, 528) and not word & 1:
            if xo == 528:
                for target in targets:
                    offer(target, state)
            if ((word >> 21) & 0x14) != 0x14:
                offer(offset + 4, state)
        else:
            offer(offset + 4, state)

    result = {}
    for offset, state in states.items():
        word = words[offset // 4]
        if not (is_call(word) or is_tail_call(obj, function, offset, word)):
            continue
        identity = call_identity(obj, function, offset, word)
        if identity is None:
            continue
        for gpr in range(3, 11):
            value = obj.string(state.get(gpr))
            if value is not None:
                result[(offset, gpr)] = (identity, value)
    return result


def compare_function(source, reference, name):
    if source.info.symbol(name).size != reference.info.symbol(name).size:
        return 0, [], "different function sizes"
    actual = call_strings(source, name)
    expected = call_strings(reference, name)
    checked, differences = 0, []
    for key, (callee, value) in expected.items():
        # Short/binary-looking data has especially ambiguous string semantics.
        if len(value) < 3 or key not in actual or actual[key][0] != callee:
            continue
        checked += 1
        if value != actual[key][1]:
            differences.append({"offset": key[0], "register": key[1],
                                "expected_hex": value.hex(),
                                "actual_hex": actual[key][1].hex(),
                                "expected": value.decode("utf-8", "replace"),
                                "actual": actual[key][1].decode("utf-8", "replace")})
    return checked, differences, None


def unit_path(name):
    path = Path(name.removeprefix("main/"))
    if path.is_absolute() or ".." in path.parts or not path.parts:
        raise ValueError("expected a relative unit path")
    return path


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("units", nargs="*")
    parser.add_argument("--function", action="append", default=[])
    parser.add_argument("--all-functions", action="store_true")
    parser.add_argument("--build", type=Path, default=Path("build/43U"))
    parser.add_argument("--report", type=Path)
    args = parser.parse_args(argv)
    if args.function and len(args.units) != 1:
        parser.error("--function requires exactly one unit")
    output = {"checked_arguments": 0, "analyzed_functions": 0,
              "skipped_functions": [], "candidates": [], "errors": []}
    try:
        report = json.loads((args.report or args.build / "report.json").read_text())
        selected = {str(unit_path(n)) for n in args.units}
        units = {str(unit_path(u["name"])): u for u in report["units"]}
        if selected - units.keys():
            raise ValueError("unit is absent from report: " + ", ".join(sorted(selected - units.keys())))
        for unit in sorted(selected or units.keys()):
            source = read_object(args.build / "src" / (unit + ".o"))
            reference = read_object(args.build / "obj" / (unit + ".o"))
            functions = args.function or [f["name"] for f in units[unit].get("functions", [])
                                          if args.all_functions or f.get("fuzzy_match_percent") == 100]
            for name in functions:
                try:
                    if not args.function:
                        missing = [label for label, obj in (("source", source), ("reference", reference))
                                   if not any(s.name == name and isinstance(s.section, int) and s.size
                                              for s in obj.info.symbols)]
                        if missing:
                            output["skipped_functions"].append({
                                "unit": unit, "function": name,
                                "reason": "missing exact symbol name in " + ", ".join(missing)
                                          + "; no compiler-alias inference"})
                            continue
                    checked, differences, skipped = compare_function(source, reference, name)
                    if skipped:
                        output["skipped_functions"].append({"unit": unit, "function": name, "reason": skipped})
                        continue
                    output["analyzed_functions"] += 1
                    output["checked_arguments"] += checked
                    output["candidates"].extend(dict(unit=unit, function=name, **d) for d in differences)
                except ValueError as error:
                    output["errors"].append({"unit": unit, "function": name, "error": str(error)})
    except (OSError, ELFError, ValueError, KeyError, TypeError) as error:
        output["errors"].append({"error": str(error)})
    print(json.dumps(output, indent=2))
    return 2 if output["errors"] else 1 if output["candidates"] else 0


if __name__ == "__main__":
    sys.exit(main())
