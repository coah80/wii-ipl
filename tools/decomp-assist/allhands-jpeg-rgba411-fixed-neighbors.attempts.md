# RGBA411 normal fixed declaration neighborhood

Base: `17e497e06d6793662fd32eb58f69a710e4b71c71`, 43U only.
Leaf: `wii-jpeg-rgba411-neighbors`.
Branch: `agent/bittle/jpeg-rgba411-neighbors`.
Target: `TMCJPEGDEC_converterYUV411toRGBA8`, the normal converter.

## Scope and historical scoring gap

The authorized audit fixes the **82.6033%** baseline center and evaluates
baseline plus all **852 unique swap/move neighbors** of the 25 existing,
genuinely used, uninitialized declarations at lines **169-193**. All types,
including `s8 crValue` and `u8 value`, remain unchanged. Every source byte outside
this block, every assignment/expression/scope/initializer/helper, and all sibling
functions remain fixed. There are no adaptive center changes or semantic trials.

The current function is source-identical to `786a2dd3`, `e8241734`, `d170fbb8`
and `f46483af`. Historical coverage is not assumed novel or exhaustive:

- `jpeg-round4-attempts.md:2091-2106` records 600 structural-ranked declaration
  swaps and 13 retained improvements in an earlier expression/type context
- `fz20.attempts.md:681-756` records a 250-evaluation cap, structural trajectory
  `(36,161) -> (36,157) -> (36,154)`, fuzzy 82.25207% -> 82.54132%
- That search-end function at `c7896c38` differs from current only in its four
  overflow-OR expressions, subsequently changed to `(red | green | blue)`
- `fz20.attempts.md:1640-1648` records that expression change reaching 82.6033%
- `fz20.attempts.md:1919-1980` records a current-body 300-evaluation cap,
  `(36,153) -> (34,149)`. Its final redOffset/blueOffset declaration swap scored
  only 82.13636% and was restored
- Later `tex1.attempts.md` records rejected lifetime/packing variants and excludes
  standalone declaration permutations; none of those source formulations recur

No per-order source/object/official-fuzzy manifest survives those historical
searches. Their exact overlap and best official intermediate cannot be recovered.
This audit newly records the official objective for every compiled order; it
does not claim that an earlier search discarded this candidate or that these
orders have never been compiled. Closed RGBA211 and RGBA420 contexts are untouched.

## Pinned source and baseline

Baseline whole source SHA256:
`b58c82974159e852c29f437365d55fec5330676a775fc1f5e81ce418ef224978`.
Function text, definition through closing brace plus one newline:
`1a5015bcaebe6ceef86d3c75f8a4b26cfa9badbaf22a32ea9d4fde98ef76a007`.
Declaration block SHA256:
`9728888e0fcae0f0bf140902c88080544668fa8824e09ccfacfd7c3a4521cba8`.
Function context excluding this block:
`92ee6206ea45b05713e198d59f8e1c89828981635eed1af7a92a07a7ece338e2`.
Whole source context excluding this block:
`783b382fad7270896030180bbe712af8e563f91912f1bbacb6f83c382fa0b4cb`.

The fresh leaf uses explicit cached compiler/dtk/objdiff/sjiswrap paths,
`../toolchain/wibo-release64/wibo` and `WIBO_SJIS_MISSING_IMPORTS=1`.
Ordinary default Ninja, explicit 43U `ok`, a full official report and the
empty-pool check verify baseline before enumeration.

## Fixed enumeration and official snapshots

The unchanged official `declsearch.py` swap/move generators yield 300 pair
swaps plus 576 distinct moves, with 24 shared adjacent swaps: **852 neighbors**.
Duplicate source orders are removed before compiling, in first-seen order.
The center never changes and scores never influence enumeration. This is not
an adaptive declsearch invocation. Official tool SHA256 remains
`9642fe689ee3a4d80236b5f790fdda83397214cd209c62ce07088b3f2b3726bb`.

All **853 unique orders** actually compile with ordinary real Ninja/MWCC.
The recorder invokes Ninja with unchanged arguments/environment and preserves
exact source/object snapshots, hashes, mtimes, argv, stdout/stderr and status.
Every call emits an actual MWCC build, changes the object mtime, and has stable
source confined to the permitted block. There are zero failed, no-work or
unstable calls, yielding **266 distinct whole objects**. Initial baseline and
final retained-source full builds are separate validation operations.

Every frozen object receives official objdiff scoring using a private copy of
the actual config, preserving settings, metadata and mappings. Unique unit names
point to the frozen original and each frozen candidate. No deduplication,
skipped compilation, live-object swapping or batch aggregate objective is used.
A private one-unit baseline first equals the full baseline's raw functions,
sections and measures.

All 853 snapshots preserve the twelve sibling raw bodies, both exact functions,
function set, existing code/data/completion metrics and empty allocated non-code
sections. There are zero non-fuzzy gate failures. There are **350 baseline ties**,
**two strict gains at 82.70661%**, and **501 unit-fuzzy losses**. The tied winners
are snapshots 0243 and 0799, with different object hashes. Snapshot **0243** is
the deterministic first highest admissible score and is retained. It swaps only
`u16* output` and `s32 greenOffset`, baseline lines 182 and 191.

The baseline neighborhood is fully covered: **852/852 neighbors compiled and
scored**. The selected winner has only **5/852 immediate neighbors observed**,
with 847 unobserved. It is not claimed to be a fixed point or global optimum.
No restart, continuation or additional source trial occurred.

## Fresh retained-source gates

The selected source was freshly rebuilt with ordinary default Ninja/report/
progress, explicit `build/43U/ok` and a full official report.

- RGBA411 normal: **82.6033% -> 82.70661%**, 968/968 bytes, 242/242 instructions
- Normalized positional ctxdiff remains **153**; internal comparator remains
  `(36,153)` for baseline and selected object
- All twelve sibling raw bodies and official scores are unchanged
- Unit exact functions/code remain **2/13 and 660/6596 bytes**
- Both YUV400 siblings remain original-byte-identical and official 100%
- Unit fuzzy: **90.59006% -> 90.60522%**
- Global fuzzy: **99.731224% -> 99.73127%**
- All 1,027 units/every function checked: no regression, only the target changes
- All 1,027 whole-object hashes checked: only the RGBA8 object changes
- Fresh object equals snapshot 0243 byte-for-byte; full-report unit raw functions,
  sections and measures equal its frozen snapshot report
- Empty pool identical; original/baseline/candidate allocated non-code bytes zero
- Literal audit: 12 functions analyzed, zero candidates/errors; unchanged
  unequal-size converter setter skipped, as in baseline
- Actual config unchanged; default build/progress, 43U `ok`, diff checks pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`

This is a fuzzy gain, with no exact-function or linking gain.

## Retained-object integer pixel and alias reference

An independent scalar model runs against the actual retained, original and
saved baseline objects. It models Y[8][32], Cb[8][8], Cr[8][8] at buffer offsets
4/260/324, one cached chroma pair per four sequential luminance samples, and
separate tiled AR/GB halfword planes. Tile addressing uses 4x4 pixel tiles of
64 bytes with the GB plane at +32 bytes. Signed chroma arithmetic, clipping,
alpha 255 and sequential AR-then-GB stores are modeled exactly.

**11,245 vectors / 33,735 object executions pass**, with **242/242 instruction
coverage in each of the three objects**:

- 2,016 geometry/pattern cases: scales 1/2/4/8, seven aligned x origins, nine y
  origins spanning all row residues and tile crossings, minimal/wide texture
  widths, random/neutral/saturated input planes
- 6,400 saturation cases: every luminance byte crossed with each Cb/Cr pair in
  `{-128,-1,0,1,127}`, across output origins
- 2,829 halfword-aligned input/output overlap cases, with every actual store
  wholly inside the real 0x184-byte conversion buffer; state/descriptors separate

The alias model reads live memory in actual group/pixel order, so prior stores
can affect subsequent luminance or chroma reads. All x origins are four-pixel
aligned, scales are nonzero supported values, and widths accommodate the entire
normal MCU. Every arithmetic intermediate is checked within signed-32-bit range.
Every non-stack byte and guard agrees exactly; no numeric tolerance or FPU
approximation is used. The inspected target/source body contains no FPU code.
Allocation-valid overlap and extra origins are machine-level diagnostics, not
an expanded public API contract. These finite tests are not formal or hardware
proofs. The declaration swap preserves types/scopes and all actual operation
and observation order in the source; neither moved local's address escapes.

The repository JPEG suite separately passes **9,456 paired cases** across 28
functions, including all 100 normal-RGBA411 cases with full 242-instruction
coverage, preserving GPR14-GPR31, stack pointer and LR.

## Preserved evidence and hashes

`/tmp/jpeg-rgba411-neighbors/` contains baseline/original source/object/report,
`context.json`, all `snapshots/0000.*` through `snapshots/0852.*`, enumeration,
recording and scoring scripts/output, `calls.jsonl`, actual/private configs,
`all-snapshot-reports.json`, `manifest.json`, `selection.json`, final full report,
baseline/final all-object hashes, build/pool/literal/ctx output, `verify.py`,
`verification.txt`, `audit.py`, `audit-results.json`, audit output and suite log.
Every compiled source/object hash and raw official score is preserved.

Run from the leaf:

```sh
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/jpeg-rgba411-neighbors/audit.py
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/jpeg-rgba411-neighbors/verify.py
```

Baseline object:
`aa9e89c3e1dbff717184c6920c7523b6875e59f6da8612d84ca2308495709b5a`.
Original object:
`47227ca66537a3dfc3b41add42a36442ca35f4253279580cc77cf2cd02eab65e`.
Retained object:
`eec82815d9ab939e8f31df96df0311db4953fb5b72f13190c89aa28fe66adbf2`.
Retained source:
`abc1cf9f5e6fefd42b6f2ff26b5c019ef6116cd363ab12e0277527850e3bb961`.
Retained target function text:
`3a5938e426332900bacf48472947e92b350de10035c247ecf7ec06fdbae86d9c`.
