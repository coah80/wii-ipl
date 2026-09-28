#!/usr/bin/env python3
"""Standalone ctxdiff replacement using dtk elf disasm.

Usage: ctxdiff2.py <unit> <symbol>
  unit: path relative to src/ and obj/ dirs (e.g. src/scene/channelSelect/iplChannelSelect)
  symbol: mangled name
"""
import sys
import os
import re
import difflib
import subprocess
import tempfile

DTK = 'build/tools/dtk'
MINE = 'build/43U/src/%s.o'
BASE = 'build/43U/obj/%s.o'


def disasm_fn(path, name, tmp):
    out = os.path.join(tmp, 'out.s')
    subprocess.run([DTK, 'elf', 'disasm', path, out], check=True,
                   stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    lines = []
    inside = False
    for line in open(out, errors='replace'):
        line = line.rstrip('\n')
        if line.startswith('.fn ' + name):
            inside = True
            continue
        if inside and line.startswith('.endfn ' + name):
            break
        if inside:
            lines.append(line)
    return lines


def norm(line):
    # keep only instruction part: strip leading comment/addr bytes
    m = re.search(r'\*/\s*(.*)$', line)
    if m:
        ins = m.group(1).strip()
    else:
        ins = line.strip()
    return ins


def main():
    unit, name = sys.argv[1], sys.argv[2]
    with tempfile.TemporaryDirectory() as tmp:
        a = disasm_fn(MINE % unit, name, os.path.join(tmp, 'a'))
        b = disasm_fn(BASE % unit, name, os.path.join(tmp, 'b'))
    print(f"src insns {len(a)}  base insns {len(b)}")
    sm = difflib.SequenceMatcher(None, [norm(x) for x in a], [norm(x) for x in b], autojunk=False)
    ndiff = 0
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == 'equal':
            continue
        ndiff += 1
        print(f"--- {tag} mine {i1}:{i2} base {j1}:{j2}")
        for k in range(i1, i2):
            print(f"  M {k:>4} {a[k]}")
        for k in range(j1, j2):
            print(f"  B {k:>4} {b[k]}")
    if ndiff == 0:
        print('diffs 0')


if __name__ == '__main__':
    main()
