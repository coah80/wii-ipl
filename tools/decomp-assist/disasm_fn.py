#!/usr/bin/env python3
"""Disassemble a function from an object file with relocations resolved.

Usage: disasm_fn.py <objectfile> <symbol>
"""
import sys

from capstone import CS_ARCH_PPC, CS_MODE_32, CS_MODE_BIG_ENDIAN, Cs
from elftools.elf.elffile import ELFFile


def main():
    path, name = sys.argv[1], sys.argv[2]
    with open(path, "rb") as f:
        e = ELFFile(f)
        st = e.get_section_by_name(".symtab")
        syms = list(st.iter_symbols())
        names = [s.name for s in syms]
        target = next(s for s in syms if s.name == name)
        off, size = target["st_value"], target["st_size"]
        relocs = {}
        rt = e.get_section_by_name(".rela.text")
        for r in rt.iter_relocations():
            relocs[r["r_offset"]] = names[r["r_info_sym"]]
        data = e.get_section_by_name(".text").data()[off:off + size]
    md = Cs(CS_ARCH_PPC, CS_MODE_32 + CS_MODE_BIG_ENDIAN)
    md.detail = True
    print(f"{name}  size {hex(size)}  ({size // 4} insns)")
    for i in md.disasm(data, off):
        note = ""
        if i.address in relocs:
            note = "   ; " + relocs[i.address]
        print(f"{hex(i.address)}  {i.mnemonic:<8} {i.op_str}{note}")


if __name__ == "__main__":
    main()
