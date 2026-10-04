#!/usr/bin/env python3
"""Bounded 43U VmBlobPackCommon candidate verifier.

Requires preinstalled pyelftools and capstone. Reads only the supplied objects,
DOL and symbols; writes a JSON report in a new output directory. This does not
compile, download, publish binaries or claim complete VM/Wii runtime coverage.
"""

import argparse
from pathlib import Path
import hashlib
import json
import random
import re
import struct
from collections import deque

from elftools.elf.elffile import ELFFile
from capstone import Cs, CS_ARCH_PPC, CS_MODE_32, CS_MODE_BIG_ENDIAN


def object_instructions(path, name):
    """Decode one defined ELF function, resolving instruction relocations."""
    with path.open('rb') as stream:
        elf = ELFFile(stream)
        symbols = elf.get_section_by_name('.symtab')
        candidates = [s for s in symbols.get_symbol_by_name(name) or []
                      if isinstance(s['st_shndx'], int)]
        assert len(candidates) == 1, (path, name, len(candidates))
        symbol = candidates[0]
        section_index = symbol['st_shndx']
        offset, size = symbol['st_value'], symbol['st_size']
        assert size == 2672
        code = elf.get_section(section_index).data()[offset:offset + size]
        relocations = {}
        for section in elf.iter_sections():
            if section['sh_type'] != 'SHT_RELA' or section['sh_info'] != section_index:
                continue
            table = elf.get_section(section['sh_link'])
            for relocation in section.iter_relocations():
                at = relocation['r_offset']
                if not offset <= at < offset + size:
                    continue
                target = table.get_symbol(relocation['r_info_sym'])
                label, addend = target.name, relocation['r_addend']
                if isinstance(target['st_shndx'], int) and target['st_info']['type'] in ('STT_OBJECT', 'STT_SECTION', 'STT_NOTYPE'):
                    label = elf.get_section(target['st_shndx']).name
                    addend += target['st_value']
                if not label and isinstance(target['st_shndx'], int):
                    label = elf.get_section(target['st_shndx']).name
                instruction_offset = at // 4 * 4
                assert instruction_offset not in relocations
                relocations[instruction_offset] = (relocation['r_info_type'], label, addend)
    decoder = Cs(CS_ARCH_PPC, CS_MODE_32 | CS_MODE_BIG_ENDIAN)
    result = []
    for instruction in decoder.disasm(code, offset):
        operand = instruction.op_str
        if instruction.mnemonic.startswith('b') and not instruction.mnemonic.endswith(('lr', 'ctr')):
            operand = re.sub(r'0x[0-9a-f]+$', lambda m: hex(int(m.group(), 16) - offset), operand)
        relocation = relocations.get(instruction.address)
        if relocation:
            kind, label, addend = relocation
            target = f'{label}{addend:+d} [reloc {kind}]'
            if instruction.mnemonic.startswith('b'):
                operand = target
            else:
                operand = re.sub(r'(?<![A-Za-z0-9_])(?:-?0x[0-9a-f]+|-?\d+)(?=\(|$)', target, operand)
        result.append((instruction.mnemonic, operand))
    assert len(result) * 4 == size
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--baseline-object', required=True, type=Path)
    parser.add_argument('--candidate-object', required=True, type=Path)
    parser.add_argument('--original-object', required=True, type=Path)
    parser.add_argument('--dol', required=True, type=Path, help='Authorized local original 43U DOL (uncompressed)')
    parser.add_argument('--symbols', required=True, type=Path, help='43U symbols.txt')
    parser.add_argument('--output-dir', required=True, type=Path, help='New, nonexistent directory for the report')
    args = parser.parse_args()
    if not __debug__:
        parser.error('Run without Python optimization; this verifier requires assertions')
    paths = [args.baseline_object, args.candidate_object, args.original_object]
    for path in paths + [args.dol, args.symbols]:
        if not path.is_file():
            parser.error(f'Input is not a readable file: {path}')
    out = args.output_dir
    if out.exists():
        parser.error('Output directory must not already exist')
    out.mkdir(parents=True)
    name = 'VmBlobPackCommon'
    ins = [object_instructions(path, name) for path in paths]
    assert all(len(a) == 668 for a in ins)
    mask = lambda a: [(m, re.sub(r'\br\d+\b', 'R', o)) for m, o in a]
    assert mask(ins[0]) == mask(ins[1]) == mask(ins[2])

    # Equal CFG and may-reaching definitions are diagnostic evidence about
    # explicit/ABI argument uses. The relational checker below is stronger.
    call_args = {
        'VmGetStrFromObjHdr': [3], 'VmGetIntFromObjHdr': [3],
        'CHANSVmGetArg': [3, 4], 'CHANSVmConvertObjectType': [3, 4, 5],
        'CHANSVmGetArrayElement': [3, 4, 5], 'CHANSVmGetArrayLength': [3, 4],
        'CHANSVmCheckNativeInstance': [3, 4], 'VmBlobCreateDirect': [3, 4, 5],
        'CHANSVmBlobHasSpace': [3, 5, 6], 'CHANSVmMakeU64': [3, 4],
        'CHANSVmStrCpyToU8FromU16': [3, 4, 5], 'memcpy': [3, 4, 5],
        'memmove': [3, 4, 5], 'memset': [3, 4, 5],
        'vmBlobParsePackFormatString': list(range(3, 10)),
    }

    def roles(i, a):
        m, operand = a[i]
        regs = list(map(int, re.findall(r'\br(\d+)\b', operand)))
        if m == 'bl':
            target = operand.split('+')[0]
            if target.startswith(('_savegpr_', '_restgpr_')):
                return [], []
            return call_args[target], [0] + list(range(3, 13))
        if m == 'blr':
            return [3], []
        if m == 'stwu':
            return regs, [regs[-1]]
        if m.startswith(('st', 'cmp', 'mt')):
            return regs, []
        if m.startswith('b'):
            return [], []
        assert regs, (i, a[i])
        return regs[1:], regs[:1]

    def successors(i, a):
        m, o = a[i]
        if m == 'blr':
            return []
        if m.startswith('b') and m != 'bl':
            assert o.startswith('0x'), (i, a[i])
            target = int(o, 16) // 4
            return [target] if m == 'b' else [target, i + 1]
        return [i + 1] if i + 1 < len(a) else []

    def reaching(a):
        states = [None] * len(a)
        states[0] = tuple(frozenset([('entry', r)]) for r in range(32))
        todo = deque([0])
        while todo:
            i = todo.popleft()
            after = list(states[i])
            used, written = roles(i, a)
            for r in written:
                # Normal calls produce values at ABI-fixed physical registers.
                after[r] = frozenset([('call', i, r) if a[i][0] == 'bl' else ('def', i)])
            for j in successors(i, a):
                merged = tuple(after) if states[j] is None else tuple(x | y for x, y in zip(states[j], after))
                if merged != states[j]:
                    states[j] = merged
                    todo.append(j)
        return states

    states = [reaching(a) for a in ins]
    uses_checked = 0
    for i in range(668):
        assert successors(i, ins[0]) == successors(i, ins[1]) == successors(i, ins[2])
        uses = [roles(i, a)[0] for a in ins]
        values = [[st[i][r] for r in use] for st, use in zip(states, uses)]
        assert values[0] == values[1] == values[2], ('register value mismatch', hex(i * 4), values)
        uses_checked += len(uses[0])

    # A separate must-equality relation intersects corresponding predecessor
    # edges. Unlike may-reaching-definition sets, this does not erase which
    # predecessor supplied a value. Each operation is interpreted relationally:
    # equal inputs to the same opcode/callee produce equal corresponding outputs.
    CR0, CA, CTR, LR, MEMORY = range(32, 37)

    def full_roles(i, a):
        m, operand = a[i]
        read, write = roles(i, a)
        read, write = list(read), list(write)
        if m == 'bl':
            target = operand.split('+')[0]
            if target.startswith('_savegpr_'):
                return [11] + list(range(17, 32)) + [MEMORY], [LR, MEMORY]
            if target.startswith('_restgpr_'):
                return [11, MEMORY], list(range(17, 32)) + [LR]
            # Caller-saved CR0/XER.CA/CTR/LR are clobbered by the opaque callee;
            # the complete memory state is an input/output of its fixed contract.
            return read + [MEMORY], write + [CR0, CA, CTR, LR, MEMORY]
        if m == 'blr':
            return read + list(range(17, 32)) + [LR, MEMORY], []
        if m.startswith('cmp') or m.endswith('.'):
            write.append(CR0)
        if m in ('beq', 'bne', 'ble', 'bge', 'blt', 'bgt'):
            read.append(CR0)
        if m == 'srawi':
            write.append(CA)
        if m == 'addze':
            read.append(CA)
            write.append(CA)
        if m == 'mtctr':
            write.append(CTR)
        if m == 'bdnz':
            read.append(CTR)
            write.append(CTR)
        if m == 'mflr':
            read.append(LR)
        if m == 'mtlr':
            write.append(LR)
        if m.startswith(('lw', 'lh', 'lb')):
            read.append(MEMORY)
        if m.startswith('st'):
            read.append(MEMORY)
            write.append(MEMORY)
        if '[reloc 109]' in operand:
            # The identical SDA21 relocation selects the same EABI small-data base.
            read.extend([2, 13])
        return read, write

    def must_equal(left, right):
        entry = frozenset((r, r) for r in range(37))
        incoming = [None] * len(left)
        incoming[0] = entry
        work = deque([0])
        while work:
            i = work.popleft()
            lu, ld = full_roles(i, left)
            ru, rd = full_roles(i, right)
            assert len(lu) == len(ru) and len(ld) == len(rd)
            guaranteed_outputs = list(zip(ld, rd))
            if left[i][0] == 'bl':
                target = left[i][1].split('+')[0]
                if not target.startswith(('_savegpr_', '_restgpr_')):
                    # Kill undocumented caller-saved scratch outputs. Only the
                    # documented return registers and coupled memory effect remain.
                    returns = [3, 4] if target == 'CHANSVmMakeU64' else [3]
                    guaranteed_outputs = [(r, r) for r in returns + [MEMORY]]
            after = frozenset((l, r) for l, r in incoming[i] if l not in ld and r not in rd) | frozenset(guaranteed_outputs)
            for j in successors(i, left):
                joined = after if incoming[j] is None else incoming[j] & after
                if joined != incoming[j]:
                    incoming[j] = joined
                    work.append(j)
        checked = 0
        for i in range(len(left)):
            lu, _ = full_roles(i, left)
            ru, _ = full_roles(i, right)
            for pair in zip(lu, ru):
                assert pair in incoming[i], ('must-equality failed', hex(i * 4), left[i], right[i], pair)
                checked += 1
        return checked

    must_uses = [must_equal(ins[0], ins[j]) for j in [1, 2]]
    negative_controls = {}
    bad_register = list(ins[1])
    bad_register[0x4F4 // 4] = ('cmplw', 'r12, r18')
    try:
        must_equal(ins[0], bad_register)
    except AssertionError:
        negative_controls['undocumented_call_scratch_output_rejected'] = True
    else:
        raise AssertionError('Must-equality negative control did not reject r12 after memmove')

    def metadata(path):
        with path.open('rb') as f:
            e = ELFFile(f)
            sections = {}
            functions = {}
            syms = e.get_section_by_name('.symtab')
            for section in e.iter_sections():
                if section.name not in ('.text', '.strtab'):
                    sections[section.name] = (dict(section.header), hashlib.sha256(section.data()).hexdigest())
            for s in syms.iter_symbols():
                if s['st_info']['type'] == 'STT_FUNC' and isinstance(s['st_shndx'], int) and s['st_size']:
                    data = e.get_section(s['st_shndx']).data()[s['st_value']:s['st_value'] + s['st_size']]
                    functions[s.name] = (dict(s.entry), hashlib.sha256(data).hexdigest())
            return sections, functions

    bm, bf = metadata(paths[0])
    cm, cf = metadata(paths[1])
    assert bm == cm, 'Non-text sections, symbol metadata or relocations differ'
    assert bf.keys() == cf.keys()
    assert len(bf) == 233
    assert [n for n in bf if bf[n] != cf[n]] == [name]
    assert bf[name][0] == cf[name][0]
    renamed_symbols = []
    with paths[0].open('rb') as f, paths[1].open('rb') as g:
        be, ce = ELFFile(f), ELFFile(g)
        bs, cs = be.get_section_by_name('.symtab'), ce.get_section_by_name('.symtab')
        assert bs.num_symbols() == cs.num_symbols()
        expected_strings = bytearray(be.get_section_by_name('.strtab').data())
        for index, (b, c) in enumerate(zip(bs.iter_symbols(), cs.iter_symbols())):
            assert b.entry == c.entry
            if b.name != c.name:
                assert re.fullmatch(r'@\d+', b.name) and re.fullmatch(r'@\d+', c.name)
                assert b['st_info']['bind'] == 'STB_LOCAL' and b['st_info']['type'] == 'STT_OBJECT'
                assert len(b.name) == len(c.name)
                at = b['st_name']
                expected_strings[at:at + len(c.name)] = c.name.encode()
                renamed_symbols.append({'index': index, 'before': b.name, 'after': c.name, 'value': b['st_value'], 'size': b['st_size'], 'section': be.get_section(b['st_shndx']).name})
        assert bytes(expected_strings) == ce.get_section_by_name('.strtab').data()

    # Read the target function directly from the supplied original DOL, not a
    # generated source object. Resolve its two external slice calls by exact address.
    dol = args.dol.read_bytes()
    assert hashlib.sha1(dol).hexdigest() == '26116613f624061ba99c8d1a299aaa6efa85670d'
    header = struct.unpack('>64I', dol[:256])
    regions = list(zip(header[:7], header[18:25], header[36:43])) + list(zip(header[7:18], header[25:36], header[43:54]))
    address = 0x81453670
    fileoff = next(fo + address - va for fo, va, size in regions if va <= address and address + 0xA70 <= va + size)
    function = dol[fileoff:fileoff + 0xA70]
    with paths[2].open('rb') as stream:
        elf = ELFFile(stream)
        symbol = elf.get_section_by_name('.symtab').get_symbol_by_name(name)[0]
        section_index, value = symbol['st_shndx'], symbol['st_value']
        original_code = elf.get_section(section_index).data()[value:value + 0xA70]
        relocated_words = set()
        for section in elf.iter_sections():
            if section['sh_type'] == 'SHT_RELA' and section['sh_info'] == section_index:
                for relocation in section.iter_relocations():
                    if value <= relocation['r_offset'] < value + 0xA70:
                        relocated_words.add((relocation['r_offset'] - value) // 4)
        assert len(relocated_words) == 65
        assert all(function[i * 4:i * 4 + 4] == original_code[i * 4:i * 4 + 4]
                   for i in range(668) if i not in relocated_words)
    symbols = dict((int(addr, 16), n) for n, addr in re.findall(r'^(\w+) = \.(?:text|init):0x([0-9A-Fa-f]+);', args.symbols.read_text(), re.M))
    md = Cs(CS_ARCH_PPC, CS_MODE_32 | CS_MODE_BIG_ENDIAN)
    start, stop = 0x4BC, 0x518
    dol_ins = [None] * 668
    for i in md.disasm(function[start:stop], address + start):
        operand = i.op_str
        if i.mnemonic == 'bl':
            target = int(operand, 16)
            operand = symbols[target] + '+0 [reloc 10]'
        elif i.mnemonic.startswith('b') and i.mnemonic != 'blr':
            operand = re.sub(r'0x[0-9a-f]+$', lambda m: hex(int(m.group(), 16) - address), operand)
        dol_ins[(i.address - address) // 4] = (i.mnemonic, operand)
    assert dol_ins[start // 4:stop // 4] == ins[2][start // 4:stop // 4]
    helper_tails = {}
    for helper_name in ['_savegpr_17', '_restgpr_17']:
        helper_address = next(addr for addr, label in symbols.items() if label == helper_name)
        offset = next(fo + helper_address - va for fo, va, size in regions if va <= helper_address < va + size)
        code = list(md.disasm(dol[offset:offset + 64], helper_address))
        assert len(code) == 16 and code[-1].mnemonic == 'blr'
        for j, instruction in enumerate(code[:-1]):
            assert instruction.mnemonic == ('stw' if helper_name.startswith('_save') else 'lwz')
            match = re.fullmatch(r'r(\d+), (-?(?:0x[0-9a-f]+|\d+))\(r11\)', instruction.op_str)
            assert match and int(match[1]) == 17 + j and int(match[2], 0) == -(15 - j) * 4
        helper_tails[helper_name] = {'address': hex(helper_address), 'size': 64, 'operations': 15, 'first_register': 17, 'last_register': 31, 'base': 'r11', 'return': 'blr'}

    def getword(memory, address):
        return struct.unpack_from('>I', memory, address)[0]

    def putword(memory, address, value):
        struct.pack_into('>I', memory, address, value & 0xFFFFFFFF)

    def execute(a, memory, dst, src, count, register_map, faulty_forward_copy=False):
        memory = bytearray(memory)
        r = [0] * 32
        for reg, val in zip(register_map, [dst, src, count]):
            r[reg] = val
        pc = start
        comparison = 0
        trace = []
        iterations = 0
        while pc < stop:
            iterations += 1
            assert iterations <= 32
            m, o = a[pc // 4]
            args = o.split(', ')
            reg = lambda t: int(t[1:])
            nextpc = pc + 4
            if m in ('lwz', 'stw'):
                match = re.fullmatch(r'(-?(?:0x[0-9a-f]+|\d+))\(r(\d+)\)', args[1])
                address = (r[int(match[2])] + int(match[1], 0)) & 0xFFFFFFFF
                if m == 'lwz':
                    value = getword(memory, address)
                    r[reg(args[0])] = value
                    trace.append(('read32', address, value))
                else:
                    value = r[reg(args[0])]
                    putword(memory, address, value)
                    trace.append(('write32', address, value))
            elif m in ('add', 'subf'):
                left, right = r[reg(args[1])], r[reg(args[2])]
                r[reg(args[0])] = (left + right if m == 'add' else right - left) & 0xFFFFFFFF
            elif m == 'mr':
                r[reg(args[0])] = r[reg(args[1])]
            elif m == 'li':
                r[reg(args[0])] = int(args[1], 0) & 0xFFFFFFFF
            elif m == 'cmplw':
                comparison = (r[reg(args[0])] > r[reg(args[1])]) - (r[reg(args[0])] < r[reg(args[1])])
            elif m in ('ble', 'bge'):
                if comparison <= 0 if m == 'ble' else comparison >= 0:
                    nextpc = int(o, 16)
            elif m == 'bl':
                target = o.split('+')[0]
                dest, argument, length = r[3], r[4], r[5]
                assert 0 <= length <= 128 and dest + length <= len(memory)
                trace.append((target, dest, argument, length))
                if target == 'memmove':
                    assert argument + length <= len(memory)
                    # Directional byte implementation, separate from the reference's snapshot.
                    indices = range(length - 1, -1, -1) if not faulty_forward_copy and argument < dest < argument + length else range(length)
                    for j in indices:
                        memory[dest + j] = memory[argument + j]
                elif target == 'memset':
                    for j in range(length):
                        memory[dest + j] = argument & 255
                else:
                    raise AssertionError(target)
                for j in [0] + list(range(3, 13)):
                    r[j] = 0xDEAD0000 + j
                r[3] = dest
            else:
                raise AssertionError((pc, m, o))
            pc = nextpc
        assert pc == stop
        return bytes(memory), trace

    def reference(memory, dst, src, count):
        memory = bytearray(memory)
        trace = []
        def read(address):
            value = getword(memory, address)
            trace.append(('read32', address, value))
            return value
        offset = read(src)
        size = read(src + 4)
        data = read(dst + 8)
        extent = (size - offset) & 0xFFFFFFFF
        output = data + read(dst)
        available = min(extent, count)
        input_start = read(src + 8) + offset
        trace.append(('memmove', output, input_start, available))
        snapshot = bytes(memory[input_start:input_start + available])
        memory[output:output + available] = snapshot
        if available < count:
            trace.append(('memset', output + available, 0, count - available))
            memory[output + available:output + count] = bytes(count - available)
        final = (read(dst) + count) & 0xFFFFFFFF
        putword(memory, dst, final)
        trace.append(('write32', dst, final))
        return bytes(memory), trace

    rng = random.Random(0x81453670)
    cases = []
    for same in [False, True]:
        for source_base in [0x400, 0x410, 0x440]:
            for dest_base in [0x400, 0x408, 0x440]:
                for source_offset in [0, 1, 15, 32]:
                    for dest_offset in [0, 1, 15, 32]:
                        for available in [0, 1, 15, 32, 64]:
                            for count in [0, 1, 15, 16, 32, 64]:
                                if same and (source_base != dest_base or source_offset != dest_offset or count > available):
                                    continue
                                cases.append((same, source_base, dest_base, source_offset, dest_offset, available, count))
    for _ in range(1000):
        cases.append((False, rng.randrange(0x400, 0x480), rng.randrange(0x400, 0x480), rng.randrange(33), rng.randrange(33), rng.randrange(65), rng.randrange(65)))

    counts = dict(total=0, same_header=0, padding=0, zero_copy=0, overlap_forward=0, overlap_backward=0, identical_range=0)
    for case in cases:
        same, sp, dp, so, do, available, count = case
        memory = bytearray((i * 37 + 13) & 255 for i in range(0x800))
        src, dst = (0x100, 0x100) if same else (0x100, 0x180)
        for hdr, offset, size, data in [(src, so, so + available, sp), (dst, do, so + available if same else do + 128, dp)]:
            for field, value in [(0, offset), (4, size), (8, data)]:
                putword(memory, hdr + field, value)
        expected = reference(memory, dst, src, count)
        for a, registers in [(ins[0], [31, 25, 18]), (ins[1], [31, 25, 18]), (dol_ins, [21, 29, 24])]:
            actual = execute(a, memory, dst, src, count, registers)
            assert actual == expected, case
        trace = expected[1]
        assert trace[-2][0:2] == ('read32', dst) and trace[-1][0:2] == ('write32', dst)
        assert [e[0] for e in trace].count('memmove') == 1
        assert [e[0] for e in trace].count('memset') == int(available < count)
        counts['total'] += 1
        counts['same_header'] += same
        counts['padding'] += available < count
        counts['zero_copy'] += min(available, count) == 0
        first, output, length = sp + so, dp + do, min(available, count)
        counts['overlap_forward'] += first < output < first + length
        counts['overlap_backward'] += output < first < output + length
        counts['identical_range'] += first == output

    # Independent negative controls exercise the checks themselves, not additional
    # C candidates or compiler experiments.
    memory = bytearray((i * 37 + 13) & 255 for i in range(0x800))
    src, dst, count = 0x100, 0x180, 16
    for hdr, offset, size, data in [(src, 0, 32, 0x400), (dst, 1, 128, 0x400)]:
        for field, value in [(0, offset), (4, size), (8, data)]:
            putword(memory, hdr + field, value)
    expected = reference(memory, dst, src, count)
    assert execute(ins[1], memory, dst, src, count, [31, 25, 18], faulty_forward_copy=True) != expected
    negative_controls['overlap_unsafe_forward_copy_rejected'] = True
    omitted_read = list(ins[1])
    omitted_read[0x50C // 4] = ('mr', 'r0, r0')
    omitted_result = execute(omitted_read, memory, dst, src, count, [31, 25, 18])
    assert omitted_result != expected
    assert ('read32', dst, 1) not in omitted_result[1][-2:]
    negative_controls['omitted_volatile_postcopy_read_rejected'] = True

    result = {
        'inputs_sha256': {label: hashlib.sha256(path.read_bytes()).hexdigest() for label, path in [('baseline_object', paths[0]), ('candidate_object', paths[1]), ('original_object', paths[2]), ('dol', args.dol), ('symbols', args.symbols)]},
        'instructions': 668, 'candidate_target_diffs': sum(a != b for a, b in zip(ins[1], ins[2])),
        'baseline_candidate_instruction_diffs': sum(a != b for a, b in zip(ins[0], ins[1])),
        'gpr_normalized_full_function_equal': True,
        'full_function_reaching_definition_uses_checked': uses_checked,
        'must_equality_uses_baseline_vs_candidate_and_target': must_uses,
        'must_equality_scope': 'Corresponding CFG edges; predecessor intersection, explicit GPRs plus CR0, XER.CA, CTR, LR and complete memory; fixed opaque ABI/callee contracts. Memory operations and caller saves/restores included. This is a bounded custom checker, not a general verified PPC semantics implementation.',
        'cfg_calls_stack_offsets_and_operation_order_equal': True,
        'all_nontext_sections_except_strtab_byte_identical': True,
        'raw_symbol_entries_and_all_relocations_byte_identical': True,
        'strtab_differences_exhaustively_accounted_local_object_names': renamed_symbols,
        'all_232_sibling_functions_byte_identical': True,
        'original_dol_sha1': hashlib.sha1(dol).hexdigest(),
        'full_original_function_nonrelocated_words_checked': 603,
        'full_original_function_relocated_words_excluded': 65,
        'direct_original_dol_slice': [hex(start), hex(stop)],
        'copy_slice_instructions': (stop - start) // 4,
        'cases': counts,
        'case_comparisons': counts['total'] * 3,
        'original_save_restore_helpers_verified': helper_tails,
        'negative_controls': negative_controls,
        'call_clobbers': 'Kill GPR0, GPR3..12, CR0, XER.CA, CTR, LR at ordinary calls. Establish equality only for documented r3 returns, additionally r4 for CHANSVmMakeU64, and coupled memory effects. Exact save/restore helper tails have separate verified effects.',
        'limits': 'Bounded instruction interpretation with modeled libc calls; no complete VM/Wii runtime claim. Aliased payload views are contained in a shared valid memory allocation; constructors ordinarily own their payload. Header-overwriting malformed pointers are not asserted valid.',
    }
    (out / 'semantic-proof.json').write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps(result, indent=2))


if __name__ == '__main__':
    main()
