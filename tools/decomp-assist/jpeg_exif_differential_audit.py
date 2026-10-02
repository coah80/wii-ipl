#!/usr/bin/env python3
"""Read-only, bounded PPC integer interpreter for differential EXIF checks.
Loads source and original ELF .text; never copies original code into sources.
Only internal EXIF calls are supported. No FPU/system instructions are supported.
"""
import random
import re
import struct
import zlib

import capstone
from elftools.elf.elffile import ELFFile
U32 = 0xFFFFFFFF

def signed(x):
    x &= U32
    return x - 0x100000000 if x & 0x80000000 else x

def rotate(x, n):
    return (x << n | x >> (32 - n if n else 32)) & U32

def mask(b, e):
    return sum((1 << 31 - i for i in range(32) if b <= i <= e or (b > e and (i >= b or i <= e))))

def load_object(path):
    with open(path, 'rb') as f:
        e = ELFFile(f)
        section = e.get_section_by_name('.text')
        data = bytearray(section.data())
        syms = e.get_section_by_name('.symtab')
        calls = {}
        symbol_addresses = {}
        rel = e.get_section_by_name('.rela.text')
        if rel:
            for r in rel.iter_relocations():
                name = syms.get_symbol(r['r_info_sym']).name
                off = r['r_offset']
                typ = r['r_info_type']
                addr = 0x800000 + (zlib.crc32(name.encode()) & 0x7FFF) * 4 + r['r_addend']
                assert addr not in symbol_addresses or symbol_addresses[addr] == name
                symbol_addresses[addr] = name
                if typ == 10:
                    calls[off] = name
                elif typ == 4:
                    data[off:off + 2] = struct.pack('>H', addr & 65535)
                elif typ == 6:
                    data[off:off + 2] = struct.pack('>H', addr + 0x8000 >> 16 & 65535)
                else:
                    raise ValueError(('relocation', typ))
        dis = capstone.Cs(capstone.CS_ARCH_PPC, capstone.CS_MODE_32 | capstone.CS_MODE_BIG_ENDIAN)
        funcs = {}
        for sym in syms.iter_symbols():
            if sym['st_info']['type'] != 'STT_FUNC' or not sym['st_size']:
                continue
            start = sym['st_value']
            size = sym['st_size']
            inst = {}
            for i in dis.disasm(bytes(data[start:start + size]), start):
                ops = []
                for o in i.op_str.split(', '):
                    if not o:
                        continue
                    if o.startswith('cr'):
                        ops.append(('cr', int(o[2:])))
                    elif o.startswith('r'):
                        ops.append(int(o[1:]))
                    elif '(' in o:
                        off, reg = o.split('(')
                        ops.append((int(off, 0), int(reg[1:-1])))
                    else:
                        ops.append(int(o, 0))
                inst[i.address] = (i.mnemonic, ops)
            funcs[sym.name] = (start, inst, calls)
    return funcs

def run(functions, name, initial, args):
    pc = functions[name][0]
    ins = {address: instruction for _, body, _ in functions.values() for address, instruction in body.items()}
    calls = functions[name][2]
    mem = bytearray(initial)
    r = [i * 1122867 & U32 for i in range(32)]
    r[1] = 0x3F000
    r[3:3 + len(args)] = args
    saved_registers = r[14:].copy()
    cr = [0] * 8
    ctr = 0
    lr = 0
    steps = 0
    coverage = set()

    def ld(a, n):
        assert 0 <= a <= len(mem) - n, hex(a)
        return int.from_bytes(mem[a:a + n], 'big')

    def st(a, v, n):
        assert 0 <= a <= len(mem) - n, hex(a)
        mem[a:a + n] = (v & (1 << 8 * n) - 1).to_bytes(n, 'big')
    while True:
        steps += 1
        if steps > 100000:
            raise RuntimeError('step bound')
        coverage.add(pc)
        op, a = ins[pc]
        pc += 4
        dot = op.endswith('.')
        op = op.rstrip('.')
        val = None
        if op == 'blr':
            if lr == 0:
                break
            pc = lr
        elif op == 'bl':
            callee = calls.get(pc - 4)
            assert callee in functions, ('Unsupported external call', callee)
            lr = pc
            pc = functions[callee][0]
        elif op == 'b':
            pc = a[0]
        elif op == 'bdnz':
            ctr = ctr - 1 & U32
            if ctr:
                pc = a[0]
        elif op in ['beqlr', 'bnelr', 'blelr', 'bgelr', 'bltlr', 'bgtlr']:
            c = cr[a[0][1]] if a else cr[0]
            condition = {'beqlr': c == 0, 'bnelr': c != 0, 'blelr': c <= 0, 'bgelr': c >= 0, 'bltlr': c < 0, 'bgtlr': c > 0}[op]
            if condition:
                if lr == 0:
                    break
                pc = lr
        elif op in ['beq', 'bne', 'ble', 'bge', 'blt', 'bgt']:
            c = cr[a[0][1]] if len(a) > 1 else cr[0]
            if {'beq': c == 0, 'bne': c != 0, 'ble': c <= 0, 'bge': c >= 0, 'blt': c < 0, 'bgt': c > 0}[op]:
                pc = a[-1]
        elif op in ['cmpwi', 'cmpw', 'cmplw', 'cmplwi']:
            c = a[0][1] if isinstance(a[0], tuple) else 0
            a = ins[pc - 4][1]
            if isinstance(a[0], tuple):
                a = a[1:]
            x = r[a[0]]
            y = a[1] if op in ['cmpwi', 'cmplwi'] else r[a[1]]
            if op not in ['cmplw', 'cmplwi']:
                x = signed(x)
                y = signed(y)
            cr[c] = (x > y) - (x < y)
        elif op in ['lbz', 'lhz', 'lwz', 'lmw']:
            off, reg = a[1]
            addr = (r[reg] if reg else 0) + off & U32
            if op == 'lmw':
                for j in range(a[0], 32):
                    r[j] = ld(addr + (j - a[0]) * 4, 4)
            else:
                r[a[0]] = ld(addr, {'lbz': 1, 'lhz': 2, 'lwz': 4}[op])
        elif op in ['stb', 'sth', 'stw', 'stwu', 'stmw']:
            off, reg = a[1]
            addr = (r[reg] if reg else 0) + off & U32
            if op == 'stmw':
                for j in range(a[0], 32):
                    st(addr + (j - a[0]) * 4, r[j], 4)
            else:
                st(addr, r[a[0]], {'stb': 1, 'sth': 2, 'stw': 4, 'stwu': 4}[op])
            if op == 'stwu':
                r[reg] = addr
        elif op in ['stbx', 'sthx']:
            st((r[a[1]] if a[1] else 0) + r[a[2]] & U32, r[a[0]], 1 if op == 'stbx' else 2)
        elif op == 'mflr':
            r[a[0]] = lr
        elif op == 'mtlr':
            lr = r[a[0]]
        elif op == 'mtctr':
            ctr = r[a[0]]
        else:
            d = a[0]
            if op == 'li':
                val = a[1]
            elif op == 'lis':
                val = a[1] << 16
            elif op == 'mr':
                val = r[a[1]]
            elif op == 'add':
                val = r[a[1]] + r[a[2]]
            elif op == 'addi':
                val = (r[a[1]] if a[1] else 0) + a[2]
            elif op == 'addis':
                val = (r[a[1]] if a[1] else 0) + (a[2] << 16)
            elif op == 'subf':
                val = r[a[2]] - r[a[1]]
            elif op == 'subfic':
                val = a[2] - r[a[1]]
            elif op == 'mulli':
                val = r[a[1]] * a[2]
            elif op == 'mullw':
                val = r[a[1]] * r[a[2]]
            elif op == 'divw':
                x = signed(r[a[1]])
                y = signed(r[a[2]])
                val = abs(x) // abs(y) * (-1 if (x < 0) != (y < 0) else 1)
            elif op == 'or':
                val = r[a[1]] | r[a[2]]
            elif op == 'andc':
                val = r[a[1]] & ~r[a[2]]
            elif op == 'andi':
                val = r[a[1]] & a[2]
            elif op == 'neg':
                val = -r[a[1]]
            elif op == 'extsb':
                val = (r[a[1]] & 255) - (256 if r[a[1]] & 128 else 0)
            elif op == 'srawi':
                val = signed(r[a[1]]) >> a[2]
            elif op == 'srwi':
                val = r[a[1]] >> a[2]
            elif op == 'slwi':
                val = r[a[1]] << a[2]
            elif op == 'clrlwi':
                val = r[a[1]] & (1 << 32 - a[2]) - 1
            elif op == 'rotlwi':
                val = rotate(r[a[1]], a[2])
            elif op == 'rlwimi':
                bits = mask(a[3], a[4])
                val = (r[d] & ~bits) | (rotate(r[a[1]], a[2]) & bits)
            elif op == 'rlwinm':
                val = rotate(r[a[1]], a[2]) & mask(a[3], a[4])
            else:
                raise ValueError((hex(pc - 4), op, a))
            r[d] = val & U32
            if dot:
                cr[0] = (signed(val) > 0) - (signed(val) < 0)
    assert r[1] == 0x3F000, 'Stack pointer not restored'
    assert lr == 0, 'Link register not restored'
    assert r[14:] == saved_registers, 'Nonvolatile registers not restored'
    return (mem, r[3], coverage)

def put(m, a, v, n=4):
    m[a:a + n] = (v & (1 << 8 * n) - 1).to_bytes(n, 'big')

def compare(src, orig, name, m, args, case, returns=False):
    a, ra, ca = run(src, name, m, args)
    b, rb, cb = run(orig, name, m, args)
    # The stack can differ because each implementation owns its frame.
    if a[:0x3E000] != b[:0x3E000]:
        diff = [hex(i) for i in range(0x3E000) if a[i] != b[i]][:12]
        raise AssertionError((name, case, 'memory mismatch', diff))
    if returns and ra != rb:
        raise AssertionError((name, case, 'return', ra, rb))
    return (ca, cb)


def main():
    import argparse
    from collections import defaultdict
    path = 'build/43U/{}/libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse.o'
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source-object', default=path.format('src'))
    parser.add_argument('--target-object', default=path.format('obj'))
    parser.add_argument('--overlap-only', action='store_true')
    args = parser.parse_args()
    src = load_object(args.source_object)
    orig = load_object(args.target_object)
    assert src.keys() == orig.keys()
    assert len(src) == 6
    names = ['TMCJPEGDEC_IFD0_tag_parse', 'TMCJPEGDEC_IFD1_tag_parse', 'TMCJPEGDEC_exif_parse']
    coverage = {name: [set(), set()] for name in names}
    counts = defaultdict(int)
    rng = random.Random(449529)
    info, entry, data = 0x1000, 0x2000, 0x3000
    memory = bytearray([0xA5]) * 0x40000
    memory[data:data + 0x2000] = bytes(rng.randrange(256) for _ in range(0x2000))
    put(memory, info + 0x674, data)
    put(memory, info + 0x678, data + 0x1000)

    def exif_put(m, pos, value, size, order):
        m[pos:pos + size] = (value & ((1 << (8 * size)) - 1)).to_bytes(size, 'little' if order == 0x4949 else 'big')

    def check(name, m, args, case, returns=False):
        ca, cb = compare(src, orig, name, m, args, case, returns)
        coverage[name][0].update(ca)
        coverage[name][1].update(cb)
        counts[name] += 1

    for order in [0x4949, 0x4D4D]:
        for tag, offset in [(0x9000, 0x63C), (0x9101, 0x640), (0xA000, 0x644)]:
            for delta in range(-3, 4):
                m = bytearray(memory)
                destination = info + offset
                aliased_entry = destination + delta - 8
                exif_put(m, aliased_entry, tag, 2, order)
                m[aliased_entry + 8:aliased_entry + 12] = bytes([1, 2, 3, 4])
                check(names[0], m, [info, order, aliased_entry], ('overlapping-version-bytes', order, tag, delta))

    if args.overlap_only:
        print('TOTAL', sum(counts.values()), 'overlapping version-byte calls PASS')
        return

    for name in names[:2]:
        selector_start = counts[name]
        for order in [0x4949, 0x4D4D]:
            exif_put(memory, entry + 2, 4, 2, order)
            exif_put(memory, entry + 4, 1, 4, order)
            exif_put(memory, entry + 8, 0x100, 4, order)
            for tag in range(0x10000):
                exif_put(memory, entry, tag, 2, order)
                check(name, memory, [info, order, entry], ('all-tags', order, tag))
        print(name, counts[name] - selector_start, 'selector cases PASS', flush=True)
        for order in [0x4949, 0x4D4D]:
            for tag in [0x103, 0x112, 0x11A, 0x11B, 0x128, 0x12D, 0x132, 0x201, 0x202, 0x213, 0x8769, 0x9000, 0x9101, 0xA000, 0xA001, 0xA002, 0xA003]:
                exif_put(memory, entry, tag, 2, order)
                for field_type in [0, 3, 4, 0xFFFF]:
                    exif_put(memory, entry + 2, field_type, 2, order)
                    for offset in [0, 1, 0xFF0, 0xFEC, 0xFF8, 0xFFC, 0xFFE, 0xFFF, 0x1000, 0x1001, 0xFFFFFFFF, 0xFFFFD000]:
                        exif_put(memory, entry + 8, offset, 4, order)
                        check(name, memory, [info, order, entry], ('bounds', order, tag, field_type, offset))

    name = names[2]
    for order in [0x4949, 0x4D4D, 0, 0x1234]:
        for size in [0, 1, 7, 8, 9, 10, 13, 14, 25, 26, 40, 64, 128, 0x1000]:
            for ifd_offset in [0, 2, 8, 10, 0x1000, 0xFFFFFFFF]:
                for count in [0, 1, 2, 0xFFFF]:
                    m = bytearray(memory)
                    m[data:data + 0x1000] = bytes(0x1000)
                    exif_put(m, data, order, 2, order)
                    exif_put(m, data + 2, 42, 2, order)
                    exif_put(m, data + 4, ifd_offset, 4, order)
                    if 8 <= ifd_offset < 0x1000:
                        exif_put(m, data + ifd_offset, count, 2, order)
                    check(name, m, [data, size, info], ('header-bounds', order, size, ifd_offset, count), True)

    for order in [0x4949, 0x4D4D]:
        for magic in [0, 41, 43, 0xFFFF]:
            m = bytearray(memory)
            exif_put(m, data, order, 2, order)
            exif_put(m, data + 2, magic, 2, order)
            check(name, m, [data, 128, info], ('invalid-TIFF-magic', order, magic), True)

    for order in [0x4949, 0x4D4D]:
        for count0 in [0, 1, 2, 3]:
            for count1 in [0, 1, 2, 3]:
                for size in [40, 64, 65, 66, 70, 79, 80, 100, 128, 129, 130, 140, 144, 160, 256]:
                    m = bytearray(memory)
                    m[data:data + 0x1000] = bytes(0x1000)
                    exif_put(m, data, order, 2, order)
                    exif_put(m, data + 2, 42, 2, order)
                    exif_put(m, data + 4, 8, 4, order)
                    exif_put(m, data + 8, count0, 2, order)
                    for index, tag in enumerate([0x112, 0xA002, 0x8769][:count0]):
                        pos = data + 10 + index * 12
                        exif_put(m, pos, tag, 2, order)
                        exif_put(m, pos + 2, 4, 2, order)
                        exif_put(m, pos + 8, 128 if tag == 0x8769 else 3, 4, order)
                    exif_put(m, data + 10 + count0 * 12, 64, 4, order)
                    exif_put(m, data + 64, count1, 2, order)
                    for index, tag in enumerate([0x103, 0x201, 0x202][:count1]):
                        pos = data + 66 + index * 12
                        exif_put(m, pos, tag, 2, order)
                        exif_put(m, pos + 2, 4, 2, order)
                        exif_put(m, pos + 8, 6, 4, order)
                    exif_put(m, data + 128, 1, 2, order)
                    exif_put(m, data + 130, 0xA003, 2, order)
                    exif_put(m, data + 132, 4, 2, order)
                    exif_put(m, data + 138, 640, 4, order)
                    check(name, m, [data, size, info], ('directory-chain', order, count0, count1, size), True)

    for name in names:
        source_body = set(src[name][1])
        original_body = set(orig[name][1])
        print(name, counts[name], 'cases PASS; own-body instruction coverage', len(coverage[name][0] & source_body), '/', len(source_body), 'source;', len(coverage[name][1] & original_body), '/', len(original_body), 'original', flush=True)
    print('TOTAL', sum(counts.values()), 'paired EXIF calls PASS')

if __name__ == '__main__':
    main()
