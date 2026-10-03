# RGBA420 normal: next fixed-center official-fuzzy neighborhood

Base `ccffee8af5cd76fe326187d93418d3d62ee3c177`, branch
`agent/bittle/jpeg-rgba420-next-neighbors`, 43U only.
Target: `TMCJPEGDEC_converterYUV420toRGBA8` in
`libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8.c`.
Only the same 24 existing, used, uninitialized declarations at lines 520–543
are eligible. All types, including `s8 crValue`, and every other source byte,
assignment, expression, initializer, helper and scope remain fixed.

## Context and recorded historical overlap

The preceding audit selected snapshot 0073 at 90.35294%, merged as #1107.
That audit repeated the earlier structurally scored compilation neighborhood
to supply its missing official-fuzzy scores. Its retained center had only
5/782 immediate neighbors in the surviving official manifest.

This separately authorized pass fixes that new center throughout. Six current
orders, indices 0, 73, 347, 348, 491 and 492, overlap the preceding manifest:
baseline plus five neighbors. The other 777 neighbors were absent from that
manifest. Older structural runs may overlap further; no global novelty claim.
No pixel-lifetime/body rewrite, adaptive center, restart, other group or continuation.

Baseline SHA256, with function text including exactly one trailing newline:

- Whole source: `ac49d186094861e300e7a066d5b006c133d131dc2d348b1142902441c5559c72`
- Function: `a2686af50fb1cfd223d6b304d4b7f784bb3ea948f2b1801882ac1a6532fcb075`
- Declaration block: `c3af93f9d96f858ef115f13a6f3206facd0893504f6c81dc16776a531d56eeb6`
- Function excluding block: `227ede5e96d002bbf01db50bf41093b8557d91d249704e673906557552a44f28`
- Whole source excluding block: `a47bd121a71d5cad81c23415239e4b2d4965aee423bb460a734a9bdae479800c`
- Whole object: `aa74b466e7cf3ad626a90399cafde841928ab775e1cd6a7cf1fd3be72c9fa28a`
- Original whole object: `47227ca66537a3dfc3b41add42a36442ca35f4253279580cc77cf2cd02eab65e`

The fresh leaf copied verified idle main cache and configured explicit cached
compiler, dtk, objdiff, sjiswrap and BSTool paths with
`../toolchain/wibo-release64/wibo` and `WIBO_SJIS_MISSING_IMPORTS=1`.
Ordinary default Ninja reproduced the full main report and all 1,027 object
hashes before enumeration. Baseline target was 90.35294%; pools were empty/equal.
Production flags and repository tools remain unchanged.

## Complete fixed baseline enumeration

Unchanged official neighbor-generation logic yields 276 pair swaps and 529
distinct remove/insert moves, overlapping in 23 orders: 782 unique neighbors
plus baseline. Every order received real ordinary Ninja/MWCC compilation and
immutable source/order/object snapshots, hashes, timestamps, output and status.
Source stability and the exact authorized block boundary were checked each time.

- 783 distinct source orders and successful real compilations
- 377 distinct whole objects; no failed, no-work or unstable-source calls
- Every frozen object officially scored using a private copy of actual objdiff
  config, preserving diff settings, metadata and mappings
- Only unique unit names and frozen original/snapshot paths changed; no deduplication,
  live-object swapping, structural filtering or artificial aggregate ranking
- Private one-unit baseline raw results match the full baseline report
- Every snapshot passes sibling/exact/code/data/link/total preservation checks
- Neighbor outcomes: 16 official gains, 200 ties and 566 losses
- Score range: 85.16994% to 90.745094%

The unique highest admissible snapshot is **0083**, **90.745094%**. It swaps
only `s32 lumaSkip;` and `u16* output;` at lines 523 and 540.
The center did not change during enumeration. Stop: all 782/782 baseline
neighbors scored. Only 5/782 neighbors of this winner appear in the manifest;
777 remain unobserved here. No winner fixed-point or global-optimum claim.

`declsearch.py` is unchanged, SHA256
`9642fe689ee3a4d80236b5f790fdda83397214cd209c62ce07088b3f2b3726bb`.

## Fresh retained-source gates

- Target fuzzy: **90.35294% → 90.745094%**
- Unit fuzzy: **90.62644% → 90.66283%**
- Global fuzzy on this base: **99.7314% → 99.73146%**
- Instructions remain 153/153; ctxdiff 84 → 79; proxy `(16,84)` → `(16,79)`
- Exact remains 2/13 and matched code 660/6596; link/data measures unchanged
- All twelve sibling bodies/scores preserved, including normal411 at 82.70661%
  and normal422 at 88.195946%
- Both YUV400 siblings remain original-byte exact and official 100%
- Allocated non-code sections empty/identical to baseline and original
- Pools identical; literal audit analyzes twelve functions with no candidates/errors,
  retaining the unchanged unequal-size setter skip
- All 1,027 full-report/object gates pass; only the RGBA8 object and target score change
- Fresh rebuilt object equals snapshot 0083; fresh full-report raw unit functions,
  sections and measures equal that snapshot's official report
- Default build, explicit progress/report/43U `ok`, and diff check pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`

This is partial fuzzy progress only; the completion checker still reports the
repository's existing code/data/link gaps.

Retained SHA256 values:

- Whole source: `5e527b2a6315cfd6919e06a16d93e1cd7d546ccdd5f14f45c786ef28e1c80e36`
- Function: `8aac60450ce746db2e86f3d021d78a85f1c9dbd3cf40add3b0469bd545d26766`
- Declaration block: `5e8d6fbbda0908e9c983996495d1833f776530d678425bed6b3c79e133a674c7`
- Whole object: `d461da38f781adecced0ccc269c6c656b3e984566421fcf6412c93db8b8857f8`

## Sequential behavior and valid allocation overlaps

The independent exact integer reference again passes **11,138 vectors / 33,414
object executions**, now against the retained, original and freshly rebuilt
90.35294% baseline objects. All **153/153 instructions** are covered in each.
The unchanged repository JPEG suite also passes **9,456 paired cases** over
28 functions, including full RGBA420-normal coverage.

Reference cases: 1,792 geometry/pattern vectors, 6,400 saturation vectors and
2,946 contained overlap vectors. They cover scales 1/2/4/8, even column residues,
row parity, tile crossings, minimal rounded/large texture widths and constant/
random planes. Saturation crosses every luminance byte with all 25 Cb/Cr pairs
from `{-128,-1,0,1,127}`.

The physical planes are Y[16][16], Cb[8][8], Cr[8][8] at offsets 4/260/324.
The model independently computes 4×4 AR/GB tile addresses, exact integer color
arithmetic and clamps. It reads live memory sequentially, caches chroma per
horizontal pair, writes AR then GB, and models vertical chroma reuse from
absolute row parity. All alias output halfwords stay inside the actual 0x184-byte
conversion allocation, with descriptors/state separate. Physical input-plane
read indices and signed-32 arithmetic are bounded; no FP is involved.
Full-height odd-origin diagnostics are excluded because their reads would cross
the chroma planes; shorter scaled odd-row cases remain covered.

Every non-stack byte, including guards, agrees; GPR14–31, stack pointer and LR
are preserved. These bounded interpreter diagnostics are not API extensions,
formal equivalence proofs or Wii hardware tests.

## Reproduction evidence

`/tmp/jpeg-rgba420-next-neighbors/` contains pinned baseline/context, frozen
original/config, all `snapshots/0000.*` through `0782.*`, recorder/enumeration,
calls, manifest, selection, every official raw snapshot score, full reports,
all-object inventories, build/pool/ctx/literal/status/completion logs and model
and suite evidence. Run from the leaf root:

```sh
../.venv/bin/python /tmp/jpeg-rgba420-next-neighbors/score_snapshots.py
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/jpeg-rgba420-next-neighbors/verify.py
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/jpeg-rgba420-next-neighbors/audit.py
PYTHONPATH=../local-tools ../.venv/bin/python tools/decomp-assist/jpeg_differential_audit.py
```

Local source/evidence commit only. Previous leaves/evidence preserved; no
remote writes, other converter work or continuation.
