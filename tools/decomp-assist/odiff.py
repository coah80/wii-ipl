#!/usr/bin/env python3
"""odiff: symbol lookup + normalized disassembly for object files.

Recreated for this environment (original lived on the author's machine).
"""

import re

from capstone import CS_ARCH_PPC, CS_MODE_32, CS_MODE_BIG_ENDIAN, Cs
from elftools.elf.elffile import ELFFile

_cache = {}


def _load(path):
    if path in _cache:
        return _cache[path]
    with open(path, "rb") as f:
        e = ELFFile(f)
        st = e.get_section_by_name(".symtab")
        names = [s.name for s in st.iter_symbols()]
        syms = {s.name: (s["st_value"], s["st_size"]) for s in st.iter_symbols()}
        data = {}
        for sec in e.iter_sections():
            data[sec.name] = (sec["sh_offset"], sec.data())
        relocs = {}
        for sec in e.iter_sections():
            if sec.name.startswith(".rela"):
                target = sec.name[5:]
                for r in sec.iter_relocations():
                    relocs[(target, r["r_offset"])] = names[r["r_info_sym"]]
        _cache[path] = (data, syms, relocs)
    return _cache[path]


def sym(path, name):
    _, syms, _ = _load(path)
    return syms[name]


def dis(path, off, size, section=".text"):
    data, syms, relocs = _load(path)
    sec_data = data[section][1]
    md = Cs(CS_ARCH_PPC, CS_MODE_32 + CS_MODE_BIG_ENDIAN)
    out = []
    for i in md.disasm(sec_data[off:off + size], off):
        text = i.mnemonic + " " + i.op_str
        m = re.search(r"0x[0-9a-fA-F]+", i.op_str)
        if (section, i.address) in relocs:
            # External reference: show the symbol, drop the raw addend
            text = i.mnemonic + " " + re.sub(r"0x[0-9a-fA-F]+",
                                             "<" + relocs[(section, i.address)] + ">",
                                             i.op_str)
        elif m and i.mnemonic.startswith("b"):
            val = int(m.group(0), 16)
            if off <= val < off + size:
                # Intra-function branch: normalize to function-relative
                text = i.mnemonic + " " + (i.op_str[:m.start()] +
                                           "+" + hex(val - off) +
                                           i.op_str[m.end():])
        out.append((i.address - off, text))
    return out
