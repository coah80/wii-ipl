# RGBA422 normal: fixed-neighborhood official-fuzzy audit

Base `e8c465a0827d9c907fa6b6da62d93ad633ca33ac`, branch
`agent/bittle/jpeg-rgba422-fixed-neighbors`, 43U only.
Target: `TMCJPEGDEC_converterYUV422toRGBA8` in
`libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8.c`.
Only the 24 existing, used, uninitialized declarations at lines 368–391
were eligible. Every other source byte, type, initializer, assignment,
expression, scope and sibling is fixed.

## Historical overlap and scoring gap

`rgba422-declaration-context.attempts.md` records a 1,000-evaluation capped
search, followed by a 783-evaluation continuation that exhausted the retained
center's 782 immediate swap/move neighbors. The latter reached a fixed point
only for the tool's structural/positional score `(10,80)`. Its log explicitly
disclaims independent official-fuzzy closure. The current function is
byte-identical to the retained function merged in #1080 (`dc3eede8`).

**All 783 function orders here repeat historical compilation.** This audit
records the previously missing official-fuzzy objective for those orders; it
does not claim new function-order discovery. The translation unit now also
contains later sibling improvements, which remain fixed. Historical intermediate
objects and per-order official reports are unavailable after the workspace reset.

## Pinned context and baseline

SHA256, with function text including exactly one final newline:

- Baseline whole source: `abc1cf9f5e6fefd42b6f2ff26b5c019ef6116cd363ab12e0277527850e3bb961`
- Baseline function: `f2d1efd572a63cfd47123772d01e6737fdf3165fb657170c9e1a31044ced60e1`
- Baseline declaration block: `14a72166a3ea127d0d26d3a2495fe255226db57d36f692c5cfc7f00f022bebbb`
- Function excluding block: `6a1fd8dd14eeac689e869a4c354153ba44967eb033c13701b55f09ae19c03b13`
- Whole source excluding block: `7f77574aa869aa865217408262e26fa582518b1d5a1d7f0fb95742d4c57ea990`
- Baseline whole object: `eec82815d9ab939e8f31df96df0311db4953fb5b72f13190c89aa28fe66adbf2`
- Original whole object: `47227ca66537a3dfc3b41add42a36442ca35f4253279580cc77cf2cd02eab65e`

The fresh leaf used the verified main cache, then explicit cached compiler,
dtk, objdiff and sjiswrap paths with `../toolchain/wibo-release64/wibo` and
`WIBO_SJIS_MISSING_IMPORTS=1`. Ordinary default Ninja rebuilt the leaf and its
report. All 1,027 resulting object hashes and the complete report matched
verified main. Baseline target fuzzy was 88.060814%; pools were empty/identical.
The initial configure-triggered build also ran the repository's BSTool download
edge; no source or production compilation flags were changed.

A preflight extraction accidentally selected a prototype, failing its hash
assertion before baseline artifacts existed. The enumeration then failed on
that missing baseline before touching source or invoking Ninja. The definition
was correctly selected and re-pinned before the single actual enumeration.
`preflight-missing-baseline.log` preserves that setup failure; it is not an
additional compilation, candidate run or search restart.

## Exactly one fixed-center enumeration

The unchanged official `declsearch.py` neighbor generators give 276 pair
swaps and 529 distinct remove/insert moves, with 23 overlaps: 782 unique
neighbors plus baseline. No adaptive center, structural filtering, alternate
flags, restart or continuation was used. The repository tool remains SHA256
`9642fe689ee3a4d80236b5f790fdda83397214cd209c62ce07088b3f2b3726bb`.

The recorder always invokes ordinary real Ninja with the supplied arguments.
Each call records its source/order/hash, successful object/hash, timestamps,
output and status. All 783 calls performed real MWCC compilation; no no-work,
failed or unstable-source calls occurred. There are 783 distinct source orders
and 382 distinct whole objects.

Every immutable snapshot receives official objdiff scoring under a private
copy of the actual project configuration. Diff settings, metadata and mappings
are preserved; only unit names and original/snapshot object paths change.
No `--deduplicate`, live-object swapping or artificial aggregate ranking is used.
A one-unit private baseline reproduces the full report's raw unit results.

All 783 snapshots preserve all twelve sibling bodies/scores, both exact
functions, allocated non-code content, code/data/function/link measures and
totals. Of the neighbors, two improve official fuzzy, 184 tie, and 596 lose.
The unique highest admissible score is snapshot **0027**, 88.195946%.
It swaps only `s32 lumaSkip;` and `u16* output;` at lines 369 and 373.
The other improving snapshot reaches 88.0946%.

Stop: complete fixed baseline neighborhood, 782/782 neighbors scored.
The retained winner's neighborhood has only 5/782 orders in this manifest;
777 are unobserved here. No retained-winner fixed-point or global-optimum
claim, and no continuation.

## Fresh retained-source gates

- Target fuzzy: **88.060814% → 88.195946%**
- Unit fuzzy: **90.60522% → 90.61734%**
- Global fuzzy on this base: **99.73129% → 99.731316%**
- Instructions stay 148/148; ctxdiff stays 80; proxy score stays `(10,80)`
- Exact remains 2/13 and matched code 660/6596 bytes; no linking change
- All twelve sibling bodies unchanged, including normal411 at 82.70661%
- Both YUV400 siblings remain original-byte exact and official 100%
- Baseline, candidate and original allocated non-code sections are empty/equal
- Pools identical; literal audit: twelve functions analyzed, no candidates/errors,
  with the unchanged unequal-size setter skipped
- All 1,027 full-report/object gates pass; only the RGBA8 object and target score change
- Fresh rebuilt object equals immutable snapshot 0027; fresh full-report raw unit
  functions, sections and measures equal that snapshot's official report
- Default Ninja, explicit progress/report/43U `ok`, and `git diff --check` pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`

The completion checker remains incomplete because of existing repository-wide
code/data/link gaps; this is partial fuzzy progress only.

Retained SHA256 values:

- Whole source: `1d4cb40cbbc2db10aebe68c0dbbbe1696eef476d1352010ddd3476fbdf7ba06f`
- Function: `7a98f7a236cb6e6c060929d16ce9665d6561e5ed37f862dd24d6273f7422a74f`
- Declaration block: `41e165b29ac31c6f9b09812896119453c7f7a52945c02d9e8e1ad70049829c78`
- Whole object: `ed891692675bc95d734ccb74bcc94f0bc6c1b7924b9b404b8c7cf419891f32d5`

## Exact integer pixel and allocation-valid alias model

The independent scalar reference passes **12,889 vectors / 38,667 object
executions** against retained, original and baseline objects, with all 148
instructions covered in each. Physical planes are Y[8][16], Cb[8][8] and
Cr[8][8] at conversion-buffer offsets 4/132/196. Scales 1/2/4/8 produce
16/scale by 8/scale output, with fixed source-row strides 16/8/8.

- 2,016 geometry/pattern cases cover scales, even column residues, every row
  residue, tile crossings, minimal rounded/large texture widths and sample patterns
- 6,400 saturation cases cross all 256 luminance values with the 25 Cb/Cr pairs
  from `{-128,-1,0,1,127}`
- 4,473 halfword-aligned overlap cases keep every output halfword wholly inside
  the actual 0x184-byte conversion allocation, with descriptors/state separate

The model independently computes 4×4 tiled AR/GB addresses and exact integer
chroma arithmetic. It reads current memory sequentially and caches chroma per
two-pixel group, preserving live input/output alias observations. Every integer
intermediate is checked within signed-32 range; there are no FP operations.
Every non-stack byte, including guards, matches. The interpreter verifies
GPR14–31, stack pointer and LR. Additional residue/alias cases are bounded
machine-level checks, not extensions of API validity or formal/hardware proofs.

The unchanged repository JPEG suite also passes **9,456 paired cases** over
28 functions, including all 148 instructions of RGBA422 normal.

## Reproduction evidence

`/tmp/jpeg-rgba422-neighbors/` contains baseline source/object/report and
context hashes, frozen original/config, all `snapshots/0000.*` through
`snapshots/0782.*`, recorder/enumerator, calls, manifest, selection, private
report project, all raw snapshot reports, full reports/object hash inventories,
build/pool/ctx/literal/completion results and both model logs.

From the leaf root:

```sh
../.venv/bin/python /tmp/jpeg-rgba422-neighbors/score_snapshots.py
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/jpeg-rgba422-neighbors/verify.py
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/jpeg-rgba422-neighbors/audit.py
PYTHONPATH=../local-tools ../.venv/bin/python tools/decomp-assist/jpeg_differential_audit.py
```

Local source/evidence commit only. All previous leaves and evidence preserved;
no remote writes, additional audit or continuation.
