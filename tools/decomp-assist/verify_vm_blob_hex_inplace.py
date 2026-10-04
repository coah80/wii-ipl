#!/usr/bin/env python3
"""Verify the fixed in-place 43U hex decoder candidate.

Requires preinstalled pyelftools/capstone and the published common verifier.
Reads the supplied artifacts; writes reports only in a fresh output directory.
No compilation, downloads, binary publication or full VM runtime claims.
"""
import argparse
from pathlib import Path
import hashlib
import importlib.util
import json
import re
import struct
import subprocess
import sys
from elftools.elf.elffile import ELFFile
from capstone import Cs, CS_ARCH_PPC, CS_MODE_32, CS_MODE_BIG_ENDIAN

parser = argparse.ArgumentParser(description=__doc__)
for arg in ['baseline-object', 'candidate-object', 'original-object', 'dol', 'symbols', 'source', 'output-dir']:
    parser.add_argument('--' + arg, required=True, type=Path)
parser.add_argument('--common-verifier', type=Path,
                    default=Path(__file__).with_name('verify_vm_blob_copy_padded.py'),
                    help='Published common verifier; defaults to the sibling repository script')
args = parser.parse_args()
if not __debug__:
    parser.error('Run without Python optimization; this verifier requires assertions')
if args.output_dir.exists():
    parser.error('Output directory must not already exist')
for path in [args.baseline_object, args.candidate_object, args.original_object, args.dol, args.symbols, args.common_verifier, args.source]:
    if not path.is_file():
        parser.error(f'Input is not a file: {path}')
assert hashlib.sha256(args.source.read_bytes()).hexdigest() == '2a4903c930eed51968ef99d018dc46256807cb59bb4f69287e3065b883591faf'
assert hashlib.sha256(args.baseline_object.read_bytes()).hexdigest() == 'a60ea527623793184e6e3edd0584e0e335c534248a5a9902dfe217cefdf39999'
assert hashlib.sha256(args.candidate_object.read_bytes()).hexdigest() == '7325c84d335b08f2fb58405e87ca76fc0245fcd8549bb640ec4ef7911893b053'
assert hashlib.sha256(args.common_verifier.read_bytes()).hexdigest() == '80eaf647c3935200f5b52d268de974417c4949184a1593cc1e9ee373a0e6f80a'
args.output_dir.mkdir(parents=True)
common_output = args.output_dir / 'common-proof'
command = [sys.executable, str(args.common_verifier),
           '--baseline-object', str(args.baseline_object),
           '--candidate-object', str(args.candidate_object),
           '--original-object', str(args.original_object),
           '--dol', str(args.dol), '--symbols', str(args.symbols),
           '--output-dir', str(common_output)]
with (args.output_dir / 'common-proof.log').open('wb') as log:
    completed = subprocess.run(command, stdout=log, stderr=subprocess.STDOUT)
assert completed.returncode == 0, 'Common proof failed; inspect common-proof.log'
common_result = json.loads((common_output / 'semantic-proof.json').read_text())
assert common_result['must_equality_uses_baseline_vs_candidate_and_target'] == [944, 944]
assert all(common_result['negative_controls'].values())
spec = importlib.util.spec_from_file_location('common_proof', args.common_verifier)
common = importlib.util.module_from_spec(spec)
spec.loader.exec_module(common)
objects = [args.baseline_object, args.candidate_object, args.original_object]
streams = [common.object_instructions(p, 'VmBlobPackCommon') for p in objects]

dol = args.dol.read_bytes()
assert hashlib.sha1(dol).hexdigest() == '26116613f624061ba99c8d1a299aaa6efa85670d'
header = struct.unpack('>64I', dol[:256])
regions = list(zip(header[:7], header[18:25], header[36:43])) + list(zip(header[7:18], header[25:36], header[43:54]))
address = 0x81453670
fileoff = next(fo + address - va for fo, va, size in regions if va <= address and address + 0xA70 <= va + size)
symbols = dict((int(a, 16), n) for n, a in re.findall(r'^(\w+) = \.(?:text|init):0x([0-9A-Fa-f]+);', args.symbols.read_text(), re.M))
decoded_dol = [None] * 668
md = Cs(CS_ARCH_PPC, CS_MODE_32 | CS_MODE_BIG_ENDIAN)
START, BODY, END_LOOP, END = 0x978, 0x9A8, 0xA2C, 0xA38
for inst in md.disasm(dol[fileoff + START:fileoff + END], address + START):
    operand = inst.op_str
    if inst.mnemonic == 'bl':
        operand = symbols[int(operand, 16)] + '+0 [reloc 10]'
    elif inst.mnemonic.startswith('b'):
        operand = re.sub(r'0x[0-9a-f]+$', lambda m: hex(int(m.group(), 16) - address), operand)
    decoded_dol[(inst.address - address) // 4] = (inst.mnemonic, operand)
assert decoded_dol[START // 4:END // 4] == streams[2][START // 4:END // 4]
assert streams[0][0x4BC // 4:0x518 // 4] == streams[1][0x4BC // 4:0x518 // 4]
def copy_slice_bytes(path):
    with path.open('rb') as stream:
        elf = ELFFile(stream)
        symbol = elf.get_section_by_name('.symtab').get_symbol_by_name('VmBlobPackCommon')[0]
        begin = symbol['st_value']
        return elf.get_section(symbol['st_shndx']).data()[begin + 0x4BC:begin + 0x518]
assert copy_slice_bytes(objects[0]) == copy_slice_bytes(objects[1])
differences = [i * 4 for i, (a, b) in enumerate(zip(streams[0], streams[1])) if a != b]
assert len(differences) == 13 and all(BODY <= x < END_LOOP for x in differences)

def compile_stream(stream):
    result = {}
    for pc in range(START, END, 4):
        op, operands = stream[pc // 4]
        words = operands.split(', ')
        register = lambda x: int(x[1:])
        if op in ('lwz', 'lbz', 'stw', 'stb'):
            match = re.fullmatch(r'(-?(?:0x[0-9a-f]+|\d+))\(r(\d+)\)', words[1])
            values = [register(words[0]), int(match[1], 0), int(match[2])]
        elif op in ('lhzx', 'add', 'or'):
            values = [register(x) for x in words]
        elif op in ('addi', 'clrlwi', 'clrlwi.', 'slwi'):
            values = [register(words[0]), register(words[1]), int(words[2], 0)]
        elif op in ('li', 'cmpwi', 'cmplwi'):
            values = [register(words[0]), int(words[1], 0)]
        elif op == 'mr':
            values = [register(x) for x in words]
        elif op == 'mtctr':
            values = [register(words[0])]
        elif op == 'bl':
            assert operands == 'memset+0 [reloc 10]'
            values = []
        else:
            assert op in ('b', 'blt', 'bgt', 'ble', 'bge', 'beq', 'bne', 'bdnz'), (pc, op)
            values = [int(operands, 16)]
        result[pc] = (op, values)
    return result

programs = [compile_stream(s) for s in [streams[0], streams[1], decoded_dol]]
# Register maps follow actual entry values in the disassembled slice:
# source data, byte count, character count, parent header, destination cursor.
maps = [(25, 17, 21, 31, 18), (25, 17, 21, 31, 18), (29, 24, 17, 21, 25)]

def word(memory, address):
    return struct.unpack_from('>I', memory, address)[0]

def putword(memory, address, value):
    struct.pack_into('>I', memory, address, value & 0xFFFFFFFF)

def execute(program, register_map, initial, src, dst, parent, count, parity=None):
    memory = bytearray(initial)
    r = [0] * 32
    source_reg, size_reg, count_reg, parent_reg, dest_reg = register_map
    r[source_reg], r[size_reg], r[count_reg], r[parent_reg] = src, (count + 1) // 2, count, parent
    ctr = 0
    comparison = 0
    pc, stop = START, END
    if parity is not None:
        pc, stop = BODY, END_LOOP
        r[6], r[3], ctr, r[dest_reg] = parity, parity * 2, 1, dst
    trace = []
    budget = 64 * (count + 2)
    while pc < stop:
        budget -= 1
        assert budget >= 0
        op, a = program[pc]
        nextpc = pc + 4
        if op in ('lwz', 'lbz', 'stw', 'stb'):
            reg, off, base = a
            addr = r[base] + off
            if op == 'lwz':
                r[reg] = word(memory, addr)
                trace.append(('read32', addr, r[reg]))
            elif op == 'lbz':
                r[reg] = memory[addr]
                trace.append(('read8', addr, r[reg]))
            elif op == 'stw':
                putword(memory, addr, r[reg])
                trace.append(('write32', addr, r[reg]))
            else:
                memory[addr] = r[reg] & 255
                trace.append(('write8', addr, r[reg] & 255))
        elif op == 'lhzx':
            addr = r[a[1]] + r[a[2]]
            r[a[0]] = struct.unpack_from('>H', memory, addr)[0]
            trace.append(('read16', addr, r[a[0]]))
        elif op in ('li', 'mr', 'addi', 'add', 'or', 'clrlwi', 'clrlwi.', 'slwi'):
            if op == 'li': value = a[1]
            elif op == 'mr': value = r[a[1]]
            elif op == 'addi': value = r[a[1]] + a[2]
            elif op == 'add': value = r[a[1]] + r[a[2]]
            elif op == 'or': value = r[a[1]] | r[a[2]]
            elif op in ('clrlwi', 'clrlwi.'): value = r[a[1]] & ((1 << (32 - a[2])) - 1)
            else: value = r[a[1]] << a[2]
            r[a[0]] = value & 0xFFFFFFFF
            if op == 'clrlwi.':
                signed = r[a[0]] if r[a[0]] < 0x80000000 else r[a[0]] - 0x100000000
                comparison = (signed > 0) - (signed < 0)
        elif op in ('cmpwi', 'cmplwi'):
            value = r[a[0]]
            if op == 'cmpwi' and value >= 0x80000000:
                value -= 0x100000000
            comparison = (value > a[1]) - (value < a[1])
        elif op == 'mtctr':
            ctr = r[a[0]]
        elif op == 'bl':
            trace.append(('memset', r[3], r[4], r[5]))
            memory[r[3]:r[3] + r[5]] = bytes([r[4] & 255]) * r[5]
            returned = r[3]
            for reg in [0] + list(range(3, 13)):
                r[reg] = 0xDEAD0000 + reg
            r[3] = returned
            ctr = 0xDEAD0034
            comparison = 1
        elif op == 'bdnz':
            ctr = (ctr - 1) & 0xFFFFFFFF
            if ctr: nextpc = a[0]
        elif op == 'b':
            nextpc = a[0]
        else:
            conditions = {'beq': comparison == 0, 'bne': comparison != 0,
                          'blt': comparison < 0, 'bgt': comparison > 0,
                          'ble': comparison <= 0, 'bge': comparison >= 0}
            if conditions[op]: nextpc = a[0]
        pc = nextpc
    assert pc == stop
    return bytes(memory), trace, (r[6], r[3], r[dest_reg], ctr)

digits = {ord(c): i for i, c in enumerate('0123456789abcdef')}
digits.update({ord(c): i for i, c in enumerate('0123456789ABCDEF')})

def reference(initial, src, dst, parent, count, parity=None):
    memory = bytearray(initial)
    trace = []
    if parity is None:
        data = word(memory, parent + 8)
        trace.append(('read32', parent + 8, data))
        offset = word(memory, parent)
        trace.append(('read32', parent, offset))
        dst = data + offset
        size = (count + 1) // 2
        trace.append(('memset', dst, 0, size))
        for j in range(size): memory[dst + j] = 0
        indexes = range(count)
    else:
        indexes = [parity]
    for i in indexes:
        value = struct.unpack_from('>H', memory, src + i * 2)[0]
        trace.append(('read16', src + i * 2, value))
        nibble = digits.get(value, 0)
        if i % 2 == 0: nibble <<= 4
        before = memory[dst]
        trace.append(('read8', dst, before))
        memory[dst] = before | nibble
        trace.append(('write8', dst, memory[dst]))
        if i % 2: dst += 1
    if parity is None:
        before = word(memory, parent)
        trace.append(('read32', parent, before))
        putword(memory, parent, before + (count + 1) // 2)
        trace.append(('write32', parent, before + (count + 1) // 2))
    return bytes(memory), trace, dst

scalar_cases = 0
memory = bytearray(256)
for value in range(65536):
    for parity in [0, 1]:
        struct.pack_into('>H', memory, 32 + parity * 2, value)
        memory[128] = (value * 13 + parity * 47) & 255
        expected = reference(memory, 32, 128, 0, 1, parity)
        for program, register_map in zip(programs, maps):
            actual = execute(program, register_map, memory, 32, 128, 0, 1, parity)
            assert actual[:2] == expected[:2], (value, parity)
            assert actual[2] == (parity + 1, (parity + 1) * 2, expected[2], 0)
        scalar_cases += 1

string_cases = overlap_cases = 0
patterns = ['0123456789abcdef', 'ABCDEF0123456789', 'gGzZ!@ /', 'a0F!b1E?', '\x00\uffff\u0100\ud800']
for count in [0, 1, 2, 3, 7, 16, 31, 64]:
    for pattern in patterns:
        for delta in [-16, -4, -1, 0, 1, 2, 7, 256]:
            for offset in [0, 5]:
                memory = bytearray((i * 37 + 11) & 255 for i in range(2048))
                src, dst, parent = 512, 512 + delta, 64
                for i in range(count): struct.pack_into('>H', memory, src + i * 2, ord(pattern[i % len(pattern)]))
                putword(memory, parent, offset)
                putword(memory, parent + 4, 256)
                putword(memory, parent + 8, dst - offset)
                expected = reference(memory, src, dst, parent, count)
                for program, register_map in zip(programs, maps):
                    actual = execute(program, register_map, memory, src, dst, parent, count)
                    assert actual[:2] == expected[:2], (count, pattern, delta, offset)
                    assert actual[2][2] == expected[2]
                string_cases += 1
                overlap_cases += count > 0 and max(src, dst) < min(src + count * 2, dst + (count + 1) // 2)

source = args.source.read_text()
lo = source.index('static vmBoolInt VmBlobPackCommon(')
hi = source.index('\nstatic u64 CHANSVmMakeU64', lo)
body = source[lo:hi]
lo = body.index('                for (i = 0; (s32)i < count; i++) {')
hi = body.index('                parentBlob->offset += bufSize;', lo)
loop = body[lo:hi]
outside = body[:lo] + body[hi:]
assert re.findall(r'\bch\b', outside) == ['ch'] and '    u32 ch;' in outside
assert loop.index('ch = ((const u16*)srcData)[i];') < loop.index('if (ch >=')
assert 'nibble' not in loop and re.search(r'\bch\b', loop)

# Negative controls alter the interpreter input, not C source or compiler forms.
memory = bytearray(256)
struct.pack_into('>H', memory, 32, ord('a'))
expected = reference(memory, 32, 128, 0, 1, 0)
bad = dict(programs[1])
bad[0x9D4] = ('addi', [7, 7, -0x58])
assert execute(bad, maps[1], memory, 32, 128, 0, 1, 0)[:2] != expected[:2]
bad = dict(programs[1])
bad[0xA00] = ('slwi', [7, 7, 0])
assert execute(bad, maps[1], memory, 32, 128, 0, 1, 0)[:2] != expected[:2]

result = {
    'common_verifier_sha256': hashlib.sha256(args.common_verifier.read_bytes()).hexdigest(),
    'common_proof_report_sha256': hashlib.sha256((common_output / 'semantic-proof.json').read_bytes()).hexdigest(),
    'common_must_equality_uses': common_result['must_equality_uses_baseline_vs_candidate_and_target'],
    'common_copy_case_comparisons': common_result['case_comparisons'],
    'common_negative_controls': common_result['negative_controls'],
    'local_object_names_accounted': len(common_result['strtab_differences_exhaustively_accounted_local_object_names']),
    'candidate_sha256': hashlib.sha256(args.candidate_object.read_bytes()).hexdigest(),
    'source_sha256': hashlib.sha256(args.source.read_bytes()).hexdigest(),
    'direct_original_dol_slice': [hex(START), hex(END)],
    'changed_instruction_offsets': [hex(x) for x in differences],
    'changed_instructions': len(differences),
    'copy_slice_bytes_unchanged': True,
    'scalar_input_parity_cases': scalar_cases,
    'scalar_comparisons': scalar_cases * 3,
    'bounded_string_cases': string_cases,
    'bounded_string_comparisons': string_cases * 3,
    'contained_overlapping_string_cases': overlap_cases,
    'complete_memory_and_ordered_traces_equal': True,
    'ch_does_not_escape_loop_and_is_overwritten_before_each_use': True,
    'negative_controls': ['wrong_lowercase_digit_base_rejected', 'missing_high_nibble_shift_rejected'],
    'limits': 'Bounded custom PPC interpreter; modeled memset; valid allocated input/output spans. No full VM/Wii runtime coverage claim. Other function paths require the separate whole-function and project gates.',
}
(args.output_dir / 'hex-proof.json').write_text(json.dumps(result, indent=2) + '\n')
print(json.dumps(result, indent=2))
