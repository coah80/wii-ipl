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


_PS_ARITH = {
    40: "ps_sum0", 41: "ps_sum1", 20: "ps_sum0", 21: "ps_sum1",
    32: "ps_muls0", 33: "ps_muls1", 28: "ps_madds0", 29: "ps_madds1",
    12: "ps_mul", 14: "ps_div", 10: "ps_add", 11: "ps_sub",
    26: "ps_madd", 30: "ps_nmsub", 31: "ps_msub", 28 >> 2: "x",
    18: "ps_merge00", 528: "ps_merge00", 560: "ps_merge01",
    592: "ps_merge10", 624: "ps_merge11", 25: "ps_mul",
}


def _ps_decode(w):
    major = w >> 26
    if major in (56, 57, 60, 61):  # psq_l psq_lu psq_st psq_stu
        names = {56: "psq_l", 57: "psq_lu", 60: "psq_st", 61: "psq_stu"}
        fd = (w >> 21) & 31
        ra = (w >> 16) & 31
        w_ = (w >> 15) & 1
        i = (w >> 12) & 7
        d = w & 0xFFF
        if d & 0x800:
            d -= 0x1000
        return "%s f%d, %d(r%d), %d, %d" % (names[major], fd, d, ra, w_, i)
    if major in (6, 7):  # psq_lx psq_stx
        names = {6: "psq_lx", 7: "psq_stx"}
        fd = (w >> 21) & 31
        ra = (w >> 16) & 31
        rb = (w >> 11) & 31
        w_ = (w >> 10) & 1
        i = (w >> 7) & 7
        return "%s f%d, r%d, r%d, %d, %d" % (names[major], fd, ra, rb, w_, i)
    if major == 4:  # ps_* arithmetic
        xo = (w >> 1) & 0x3FF
        rc = w & 1
        fd = (w >> 21) & 31
        fa = (w >> 16) & 31
        fb = (w >> 11) & 31
        fc = (w >> 6) & 31
        names = {18: "ps_div", 20: "ps_sub", 21: "ps_add", 23: "ps_sel",
                 24: "ps_res", 25: "ps_mul", 26: "ps_rsqrte", 28: "ps_msub",
                 29: "ps_madd", 30: "ps_nmsub", 31: "ps_nmadd", 10: "ps_sum0",
                 11: "ps_sum1", 12: "ps_muls0", 13: "ps_muls1",
                 14: "ps_madds0", 15: "ps_madds1", 16: "ps_cmpu0",
                 32: "ps_cmpo0", 40: "ps_cmpu1", 48: "ps_cmpo1",
                 66: "ps_neg", 34: "ps_mr", 136: "ps_nabs", 264: "ps_abs",
                 528: "ps_merge00", 560: "ps_merge01", 592: "ps_merge10",
                 624: "ps_merge11", 1014: "dcbz_l"}
        n = names.get(xo)
        if n is None:
            return None
        if xo in (34, 66, 136, 264):
            return "%s%s f%d, f%d" % (n, "." if rc else "", fd, fb)
        if xo in (528, 560, 592, 624):
            return "%s%s f%d, f%d, f%d" % (n, "." if rc else "", fd, fa, fb)
        if xo in (16, 32, 40, 48):
            return "%s cr%d, f%d, f%d" % (n, fd >> 2, fa, fb)
        if xo in (10, 11):
            return "%s%s f%d, f%d, f%d, f%d" % (n, "." if rc else "", fd, fc, fa, fb)
        return "%s%s f%d, f%d, f%d, f%d" % (n, "." if rc else "", fd, fa, fc, fb)
    return None


def dis(path, off, size, section=".text"):
    data, syms, relocs = _load(path)
    sec_data = data[section][1]

    # Word-granular disassembly: capstone with paired-single fallback.
    class _I:
        __slots__ = ("address", "mnemonic", "op_str")

        def __init__(self, a, m, o):
            self.address = a
            self.mnemonic = m
            self.op_str = o

    insns = []
    pos = off
    end = off + size
    md = Cs(CS_ARCH_PPC, CS_MODE_32 + CS_MODE_BIG_ENDIAN)
    while pos < end:
        w = int.from_bytes(sec_data[pos:pos + 4], "big")
        major = w >> 26
        is_ps = major in (4, 56, 57, 60, 61) or (
            major in (6, 7) and ((w >> 1) & 0x3FF) == 18)
        if is_ps:
            t = _ps_decode(w)
            if t is None:
                insns.append(_I(pos, ".long", hex(w)))
            else:
                parts = t.split(" ", 1)
                insns.append(_I(pos, parts[0], parts[1]))
            pos += 4
            continue
        chunk = sec_data[pos:end]
        done = False
        for i in md.disasm(chunk, pos):
            insns.append(i)
            done = True
            break
        if not done:
            w = int.from_bytes(sec_data[pos:pos + 4], "big")
            t = _ps_decode(w)
            if t is None:
                insns.append(_I(pos, ".long", hex(w)))
            else:
                parts = t.split(" ", 1)
                insns.append(_I(pos, parts[0], parts[1]))
        pos += 4

    out = []
    for i in insns:
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
