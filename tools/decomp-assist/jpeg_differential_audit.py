#!/usr/bin/env python3
"""Read-only, bounded PPC integer interpreter for differential JPEG checks.
Loads source and original ELF .text; never copies original code into sources.
Only memset is external. No FPU/system instructions are supported.
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

def run(fn, initial, args):
    pc, ins, calls = fn
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
            break
        elif op == 'bl':
            assert calls.get(pc - 4) == 'memset', calls.get(pc - 4)
            assert r[3] + r[5] <= len(mem)
            mem[r[3]:r[3] + r[5]] = bytes([r[4] & 255]) * r[5]
            # Model ABI-permitted call clobbers rather than preserving temporaries.
            for reg in [0] + list(range(4, 13)):
                r[reg] = (0xBAD00000 + reg) & U32
            for field in [0, 1, 5, 6, 7]:
                cr[field] = -1
            lr = pc
        elif op == 'b':
            pc = a[0]
        elif op == 'bdnz':
            ctr = ctr - 1 & U32
            if ctr:
                pc = a[0]
        elif op in ['beq', 'bne', 'ble', 'bge', 'blt', 'bgt']:
            c = cr[a[0][1]] if len(a) > 1 else cr[0]
            if {'beq': c == 0, 'bne': c != 0, 'ble': c <= 0, 'bge': c >= 0, 'blt': c < 0, 'bgt': c > 0}[op]:
                pc = a[-1]
        elif op in ['cmpwi', 'cmpw', 'cmplw']:
            c = a[0][1] if isinstance(a[0], tuple) else 0
            a = ins[pc - 4][1]
            if isinstance(a[0], tuple):
                a = a[1:]
            x = r[a[0]]
            y = a[1] if op == 'cmpwi' else r[a[1]]
            if op != 'cmplw':
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
    a, ra, ca = run(src[name], m, args)
    b, rb, cb = run(orig[name], m, args)
    # The stack can differ because each implementation owns its frame.
    if a[:0x3E000] != b[:0x3E000]:
        diff = [hex(i) for i in range(0x3E000) if a[i] != b[i]][:12]
        raise AssertionError((name, case, 'memory mismatch', diff))
    if returns and ra != rb:
        raise AssertionError((name, case, 'return', ra, rb))
    return (ca, cb)

def main():
    total_cases = 0
    rng = random.Random(449529)
    root = 'build/43U/{}/libs/RVLMiddleware/TMC_JPEG/src/{}'
    for unit in ['texturecvtr/Texture_MCUtoRGBA8', 'texturecvtr/Texture_MCUtoRGB565', 'buffer/idct_block_var']:
        src = load_object(root.format('src', unit) + '.o')
        orig = load_object(root.format('obj', unit) + '.o')
        assert src.keys() == orig.keys(), (unit, 'Function sets differ')
        assert len(src) == (2 if unit.startswith('buffer/') else 13)
        for name in src:
            n = 0
            sa = set()
            sb = set()
            if 'IdctBlock' in name:
                for rows in range(1, 9):
                    for cols in [1, 2, 3, 8]:
                        for pattern in range(22):
                            m = bytearray([0xA5]) * 0x40000
                            block = [0] * 64
                            for y in range(rows):
                                for x in range(cols):
                                    if pattern < 6:
                                        block[y * 8 + x] = [0, 1, -1, 0x3FFFF, 0x40000, -0x40000][pattern] if x == 0 and y == 0 else 0
                                    elif pattern < 14:
                                        block[y * 8 + x] = rng.randrange(-10000, 10001) if rng.randrange(4) == 0 else 0
                                    else:
                                        block[y * 8 + x] = rng.randrange(-150000, 150001)
                            for i, v in enumerate(block):
                                put(m, 0x1000 + i * 4, v)
                            pitch = [8, 16, 32][pattern % 3]
                            args = [0x1000, 0x2000, pitch, rows << 4 | cols]
                            ca, cb = compare(src, orig, name, m, args, (rows, cols, pattern))
                            sa |= ca
                            sb |= cb
                            n += 1
            elif 'set_converter' in name:
                for component in range(256):
                    for mode in [1, 2, 4, 8]:
                        m = bytearray([0xA5]) * 0x40000
                        work = 0x1000
                        state = 0x4000
                        put(m, work + 0x17FC, component, 1)
                        put(m, work + 0x19DC, mode, 1)
                        put(m, work + 0x19E4, state)
                        put(m, state + 0x24, rng.randrange(65536), 2)
                        put(m, state + 0x26, rng.randrange(65536), 2)
                        ca, cb = compare(src, orig, name, m, [work], (component, mode), True)
                        sa |= ca
                        sb |= cb
                        n += 1
            else:
                sampling = re.search('YUV(\\d+)to', name)[1]
                w, h = {'411': (32, 8), '422': (16, 8), '420': (16, 16), '211': (8, 16), '444': (8, 8), '400': (8, 8)}[sampling]
                for scale in [1, 2, 4, 8]:
                    for pattern in range(25):
                        for border in range(4 if name.endswith('edge') else 1):
                            m = bytearray([0xA5]) * 0x40000
                            work = 0x1000
                            state = 0x4000
                            tex = 0x8000
                            x = 32 * (pattern % 2)
                            y = 16 * (pattern % 3)
                            ww = w // scale
                            hh = h // scale
                            put(m, work + 0x19E4, state)
                            put(m, state + 0x20, scale, 1)
                            put(m, state + 0x2C, 96)
                            put(m, state + 0x48, tex)
                            put(m, state + 0x18, x if border & 1 else x + 1)
                            put(m, state + 0x1C, y if border & 2 else y + 1)
                            put(m, state + 0x16, pattern % (ww + 1), 1)
                            put(m, state + 0x17, pattern % (hh + 1), 1)
                            for i in range(0x184):
                                m[work + 0x1858 + i] = [0, 127, 128, 255][pattern % 4] if pattern < 4 else rng.randrange(256)
                            ca, cb = compare(src, orig, name, m, [work, x, y], (scale, pattern, border))
                            sa |= ca
                            sb |= cb
                            n += 1
            total_cases += n
            print(f'{name}: {n} cases PASS; instruction coverage source {len(sa)}/{len(src[name][1])}, original {len(sb)}/{len(orig[name][1])}', flush=True)
    print(f'TOTAL: {total_cases} differential cases PASS; GPR14-GPR31, stack pointer and LR preserved')
if __name__ == '__main__':
    main()
