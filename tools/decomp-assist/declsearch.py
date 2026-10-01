#!/usr/bin/env python3
"""Search local-declaration orders that improve a function's register allocation.

usage: declsearch.py <unit> <symbol> [--version 43U] [--max-evals N] [--lines START END] [--score-only]

  unit    path without extension, e.g. src/system/odh
  symbol  name as in the object, e.g. huffmanCoder__9CArGBAOdhFPUsP21SArCDJ_HuffmanRequest

MWCC colors registers partly in declaration order, so permuting the leading
declaration block of a function can turn a register-only diff into a match.
The search hill-climbs over swaps and moves of those lines, rebuilding the
object each time, and leaves the best order in the file (the original text is
restored on error or Ctrl-C). Run from the worktree root. Set NINJA to the
ninja binary if it is not on PATH. --lines takes 1-based inclusive line numbers
of the declaration block when the automatic detection picks the wrong lines.
"""
import argparse
import difflib
import itertools
import os
import re
import subprocess
import sys

from capstone import CS_ARCH_PPC, CS_MODE_32, CS_MODE_BIG_ENDIAN, Cs
from elftools.elf.elffile import ELFFile

BRANCHES = {"b", "bl", "beq", "bne", "bge", "blt", "ble", "bgt", "bdnz", "bdz", "bc"}
DECL = re.compile(r"^\s+(?!return\b|if\b|for\b|while\b|do\b|switch\b|goto\b)"
                  r"(const\s+|volatile\s+|unsigned\s+|signed\s+|struct\s+)*[A-Za-z_]\w*"
                  r"(\s*\*+\s*|\s+)\**\s*[A-Za-z_]\w*(\[[^\]]*\])*(\s*=.*)?;\s*$")


def find_symbol(path, name):
    with open(path, "rb") as f:
        elf = ELFFile(f)
        for s in elf.get_section_by_name(".symtab").iter_symbols():
            if s.name == name:
                section = elf.get_section(s["st_shndx"])
                return section.data()[s["st_value"]:s["st_value"] + s["st_size"]]
    raise KeyError(f"{name} not in {path}")


def disassemble(code):
    md = Cs(CS_ARCH_PPC, CS_MODE_32 + CS_MODE_BIG_ENDIAN)
    md.detail = True
    out = []
    for pos in range(0, len(code), 4):
        insns = list(md.disasm(code[pos:pos + 4], pos))
        if not insns:
            out.append((".long", code[pos:pos + 4].hex()))
            continue
        insn = insns[0]
        operand = insn.op_str
        if insn.mnemonic.rstrip("+-") in BRANCHES and insn.operands:
            last = insn.operands[-1]
            if last.type == 2:  # immediate: make the target function-relative
                operand = str(last.imm - pos)
        out.append((insn.mnemonic, operand))
    return out


def score(mine, target):
    """(structural diff ignoring register names, positional exact diff)."""
    norm = lambda insns: [(m, re.sub(r"\b[rf]\d+\b", "r", o)) for m, o in insns]
    sm = difflib.SequenceMatcher(None, norm(mine), norm(target), autojunk=False)
    structural = sum(max(i2 - i1, j2 - j1) for tag, i1, i2, j1, j2 in sm.get_opcodes() if tag != "equal")
    exact = sum(1 for x, y in zip(mine, target) if x != y) + abs(len(mine) - len(target))
    return structural, exact


def source_for(unit):
    for ext in (".c", ".cpp", ".cp"):
        if os.path.exists(unit + ext):
            return unit + ext
    sys.exit(f"no source file for {unit}")


def function_name(symbol):
    """Regex for the definition name: Class::name for member functions, else name."""
    m = re.match(r"(\w+?)__(Q(\d))?(\d.*)", symbol)
    if not m:
        return re.escape(symbol)
    rest, names = m.group(4), []
    for _ in range(int(m.group(3) or 1)):
        length = re.match(r"\d+", rest)
        if not length:
            break
        start = length.end()
        names.append(rest[start:start + int(length.group())])
        rest = rest[start + int(length.group()):]
    if not names or not rest.startswith(("F", "C")):
        return re.escape(m.group(1))
    return rf"{names[-1]}::{m.group(1)}"


def declaration_block(lines, symbol):
    pattern = re.compile(rf"^\s*[A-Za-z_].*\b{function_name(symbol)}\s*\(")
    for start, line in enumerate(lines):
        if pattern.match(line) and not line.rstrip().endswith(";"):
            break
    else:
        sys.exit(f"definition of {symbol} not found")
    body = next(i for i in range(start, len(lines)) if lines[i].rstrip().endswith("{")) + 1
    end = body
    while end < len(lines) and DECL.match(lines[end]):
        end += 1
    if end - body < 2:
        sys.exit("fewer than two leading declarations; pass --lines START END")
    return body, end


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("unit")
    ap.add_argument("symbol")
    ap.add_argument("--version", default="43U")
    ap.add_argument("--max-evals", type=int, default=300)
    ap.add_argument("--lines", type=int, nargs=2, metavar=("START", "END"))
    ap.add_argument("--score-only", action="store_true")
    args = ap.parse_args()

    ninja = os.environ.get("NINJA", "ninja")
    built = f"build/{args.version}/src/{args.unit}.o"
    target = disassemble(find_symbol(f"build/{args.version}/obj/{args.unit}.o", args.symbol))

    def evaluate():
        if subprocess.run([ninja, built], capture_output=True).returncode:
            return (10**6, 10**6)
        return score(disassemble(find_symbol(built, args.symbol)), target)

    if args.score_only:
        print("structural %d exact %d" % evaluate())
        return

    path = source_for(args.unit)
    with open(path) as f:
        original = f.read()
    lines = original.split("\n")
    if args.lines:
        body, end = args.lines[0] - 1, args.lines[1]
    else:
        body, end = declaration_block(lines, args.symbol)
    decls = lines[body:end]
    print("declaration block:", *decls, sep="\n  ")

    cache = {}

    def order_score(order):
        if order not in cache:
            text = lines[:body] + [decls[i] for i in order] + lines[end:]
            with open(path, "w") as f:
                f.write("\n".join(text))
            cache[order] = evaluate()
        return cache[order]

    start = best = tuple(range(len(decls)))
    finished = False
    try:
        best_score = order_score(best)
        print("start", best_score, flush=True)
        improved = True
        while improved and best_score != (0, 0) and len(cache) < args.max_evals:
            improved = False
            candidates = []
            for i, j in itertools.combinations(range(len(best)), 2):
                swapped = list(best)
                swapped[i], swapped[j] = swapped[j], swapped[i]
                candidates.append(tuple(swapped))
            for i, j in itertools.permutations(range(len(best)), 2):
                moved = list(best)
                moved.insert(j, moved.pop(i))
                candidates.append(tuple(moved))
            for cand in candidates:
                if len(cache) >= args.max_evals:
                    break
                s = order_score(cand)
                if s < best_score:
                    best, best_score, improved = cand, s, True
                    print("improved", s, flush=True)
                    break
        finished = True
    finally:
        keep = finished and best != start
        with open(path, "w") as f:
            f.write("\n".join(lines[:body] + [decls[i] for i in best] + lines[end:]) if keep else original)
        subprocess.run([ninja, built], capture_output=True)
        print(f"best {cache.get(best)} after {len(cache)} builds;",
              "kept in source:" if keep else "source restored; best order was:")
        print(*[decls[i] for i in best], sep="\n")


if __name__ == "__main__":
    main()
