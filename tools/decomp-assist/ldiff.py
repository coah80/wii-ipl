#!/usr/bin/env python3
"""Local ctxdiff: compare a function in my .o vs orig .o.
usage: ldiff.py <unit> <symbol> [unit2]   — unit like keyboard/tiCellPhone"""
import sys, subprocess, re

def disasm(obj, sym):
    out = subprocess.check_output(['powerpc-eabi-objdump', '-dr', obj],
        stderr=subprocess.DEVNULL).decode('latin1')
    lines = out.splitlines()
    res, cur = [], None
    for l in lines:
        m = re.match(r'^[0-9a-f]+ <([^>]+)>:', l)
        if m:
            cur = m.group(1)
        if cur == sym:
            im = re.match(r'^\s*([0-9a-f]+):\s+([0-9a-f ]+)\s+(\S+)(.*)$', l)
            if im:
                res.append((im.group(3), im.group(4).strip()))
            if res and l.strip() == '':
                break
    return res

def main():
    unit, name = sys.argv[1], sys.argv[2]
    mine = disasm(f'build/43U/src/src/{unit}.o', name)
    base = disasm(f'build/43U/obj/src/{unit}.o', name)
    print(f'insns mine={len(mine)} base={len(base)}')
    import difflib
    a = [f'{m} {o}' for m, o in mine]
    b = [f'{m} {o}' for m, o in base]
    for d in difflib.unified_diff(b, a, 'base', 'mine', lineterm='', n=3):
        print(d)

main()
