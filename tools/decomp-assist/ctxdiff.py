#!/usr/bin/env python3
"""Compact function diff with context: python ctxdiff.py <unit> <symbol> [--full]"""
import sys

sys.path.insert(0, "/home/cole/projects/tests")
from odiff import dis, sym
import os
import itertools

os.chdir("/home/cole/projects/tests/wii-ipl")


def main():
    unit, name = sys.argv[1], sys.argv[2]
    so, ss = sym(f"build/43U/src/{unit}.o", name)
    bo, bs = sym(f"build/43U/obj/{unit}.o", name)
    a = dis(f"build/43U/src/{unit}.o", so, ss)
    b = dis(f"build/43U/obj/{unit}.o", bo, bs)
    print(f"src {hex(ss)} base {hex(bs)} insns {len(a)}/{len(b)}")
    if len(a) != len(b):
        import difflib
        sm = difflib.SequenceMatcher(None, [str(x) for x in a], [str(x) for x in b], autojunk=False)
        for tag, i1, i2, j1, j2 in sm.get_opcodes():
            if tag == 'equal':
                continue
            print(f"--- {tag} mine {i1}:{i2} base {j1}:{j2}")
            for k in range(i1, i2):
                print(f"  M {k:>4} {a[k][0]} {a[k][1]}")
            for k in range(j1, j2):
                print(f"  B {k:>4} {b[k][0]} {b[k][1]}")
        return
    diffs = [i for i, (x, y) in enumerate(zip(a, b)) if x != y]
    print(f"diffs {len(diffs)}: {diffs[:20]}")
    for i, (x, y) in enumerate(zip(a, b)):
        if x != y:
            print(f"  {i:>4} M {x[0]} {x[1]}")
            print(f"       B {y[0]} {y[1]}")


if __name__ == "__main__":
    main()
