#!/usr/bin/env python3
"""vmap.py <capdir> <unit> <symbol> [--project DIR]: map each GPR virtual to (our phys, target phys)."""
import json, re, sys, collections
sys.path.insert(0, '/home/cole/projects/tests')
from capstone import Cs, CS_ARCH_PPC, CS_MODE_32, CS_MODE_BIG_ENDIAN
from elftools.elf.elffile import ELFFile
cap, unit, sym = sys.argv[1:4]
proj = '/mnt/drive2/projects/wii-ipl-workers/data-d4'
if '--project' in sys.argv: proj = sys.argv[sys.argv.index('--project') + 1]

def fn_insns(path):
    with open(path, 'rb') as f:
        e = ELFFile(f)
        st = e.get_section_by_name('.symtab')
        s = [x for x in st.iter_symbols() if x.name == sym][0]
        sec = e.get_section(s['st_shndx'])
        data = sec.data()[s['st_value']:s['st_value'] + s['st_size']]
    md = Cs(CS_ARCH_PPC, CS_MODE_32 + CS_MODE_BIG_ENDIAN)
    out = []
    for i in range(0, len(data), 4):
        l = list(md.disasm(data[i:i+4], i))
        out.append((l[0].mnemonic, re.findall(r'\br(\d+)\b', l[0].op_str)) if l else ('?', []))
    return out

ours = fn_insns(f'{proj}/build/43U/src/{unit}.o')
targ = fn_insns(f'{proj}/build/43U/obj/{unit}.o')
assert len(ours) == len(targ), (len(ours), len(targ))

def gprs(ins):
    return [o['reg'] for o in ins['operands'] if o.get('kind') == 0 and o.get('reg_class') == 4]

bc = json.load(open(f'{cap}/regalloc-gpr-pass-1-before-color.json'))
ac = json.load(open(f'{cap}/regalloc-gpr-pass-1-after-color.json'))
# use last successful pass if present
import glob
passes = sorted(glob.glob(f'{cap}/regalloc-gpr-pass-*-before-color.json'))
bc = json.load(open(passes[-1])); ac = json.load(open(passes[-1].replace('before', 'after')))
b4 = json.load(open(f'{cap}/backend-04-after-scheduling.json'))
names = {}
for line in open(passes[-1].replace('before-color.json', 'all.txt')):
    m = re.match(r'r(\d+) -> r(\d+) (\S*)', line)
    if m: names[int(m.group(1))] = m.group(3)
# per block: list of (key, virtual regs) from after-color/before-color
blk = {}
for B, A in zip(bc, ac):
    lst = []
    for ib, ia in zip(B['instructions'], A['instructions']):
        lst.append([ia['mnemonic'], gprs(ia), gprs(ib), False])
    blk[A['index']] = lst
seq = []  # final instruction order: list of virtual-reg lists (or None)
for B in b4:
    pool = blk.get(B['index'], [])
    for ins in B['instructions']:
        key = (ins['mnemonic'], gprs(ins))
        hit = None
        for c in pool:
            if not c[3] and c[0] == key[0] and c[1] == key[1]:
                hit = c; break
        if hit:
            hit[3] = True; seq.append((ins['mnemonic'], hit[2], key[1]))
        else:
            seq.append((ins['mnemonic'], None, key[1]))
# align seq with ours by mnemonic order
res = collections.defaultdict(lambda: collections.Counter())
ourp = {}
j = 0
mis = 0
for mn, virt, phys in seq:
    if j >= len(ours): break
    # skip pcode pseudo instructions that don't emit
    if virt is None and mn.lower() not in [o[0].rstrip('.') for o in ours[j:j+1]]:
        pass
    o = ours[j]; t = targ[j]; j += 1
    if virt is None: continue
    # register operands only compare if counts match
    if [int(x) for x in o[1]] != phys[:len(o[1])] and [int(x) for x in o[1]] != phys:
        mis += 1; continue
    for k, v in enumerate(virt[:len(o[1])]):
        if v >= 32 and k < len(t[1]):
            res[v][int(t[1][k])] += 1
            ourp[v] = int(o[1][k])
print(f'# aligned {len(seq)} pcode vs {len(ours)} insns, operand mismatches {mis}')
for v in sorted(res):
    tgt = res[v].most_common()
    flag = '' if len(tgt) == 1 and tgt[0][0] == ourp[v] else ' *'
    print(f'r{v} {names.get(v, "?")} ours=r{ourp[v]} target={",".join(f"r{r}x{c}" for r, c in tgt)}{flag}')
