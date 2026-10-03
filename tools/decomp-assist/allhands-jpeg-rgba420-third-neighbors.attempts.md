# RGBA420 normal: fixed neighborhood around 90.745094%

Base `d124cf0530ecc04998f611c8a39c76c53f55982a`, branch
`agent/bittle/jpeg-rgba420-third-neighbors`, 43U only.
Target: `TMCJPEGDEC_converterYUV420toRGBA8` in
`libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8.c`.
Only the same 24 existing, used, uninitialized declarations at lines 520–543
could reorder. All types, including `s8 crValue`, and every other source byte,
assignment, expression, initializer, helper and scope remain unchanged.

## Prior coverage and baseline

#1108 retained 90.745094%, previously snapshot 0083. Only 5/782 neighbors of
that selected order occurred in its official manifest, motivating this separately
authorized fixed-center pass. Eight current orders overlap the union of the two
earlier official manifests: indices 0, 73, 83, 195, 357, 358, 701 and 702
(baseline plus seven neighbors). The other 775 neighbors are absent from that
union. Earlier structural searches may overlap further; no global novelty claim.

Baseline SHA256, with function text including exactly one trailing newline:

- Whole source: `5e527b2a6315cfd6919e06a16d93e1cd7d546ccdd5f14f45c786ef28e1c80e36`
- Function: `8aac60450ce746db2e86f3d021d78a85f1c9dbd3cf40add3b0469bd545d26766`
- Declaration block: `5e8d6fbbda0908e9c983996495d1833f776530d678425bed6b3c79e133a674c7`
- Function excluding block: `227ede5e96d002bbf01db50bf41093b8557d91d249704e673906557552a44f28`
- Whole source excluding block: `a47bd121a71d5cad81c23415239e4b2d4965aee423bb460a734a9bdae479800c`
- Whole object: `d461da38f781adecced0ccc269c6c656b3e984566421fcf6412c93db8b8857f8`
- Original whole object: `47227ca66537a3dfc3b41add42a36442ca35f4253279580cc77cf2cd02eab65e`

The fresh leaf copied verified idle main cache and configured explicit cached
compiler, dtk, objdiff, sjiswrap and BSTool paths with
`../toolchain/wibo-release64/wibo` and `WIBO_SJIS_MISSING_IMPORTS=1`.
Ordinary default Ninja reproduced the complete main report and all 1,027
object hashes at 90.745094% before enumeration. Empty pools matched.
Production flags and repository tools are unchanged.

## One complete fixed-center audit

Unchanged official neighbor generation gives 276 pair swaps and 529 distinct
remove/insert moves, overlapping in 23 orders: 782 neighbors plus baseline.
The center was fixed throughout, with no adaptive search, structural filtering,
restart, semantic/body variation, other declaration group or continuation.

All 783 source orders received real ordinary Ninja/MWCC compilation. Immutable
source/order/object snapshots, hashes, timestamps, compiler output and status
were recorded; source stability and allowed boundaries were checked each time.
There are 377 distinct whole objects and no failed, no-work or unstable calls.

Every object was officially scored under a private copy of actual objdiff config,
preserving diff settings, metadata and mappings. Only unique unit names and
frozen original/snapshot paths changed; no deduplication, live-object swapping
or artificial aggregate ranking. The private one-unit baseline reproduces the
full baseline's raw functions, sections and measures.

Every snapshot passes sibling/exact/code/data/link/total preservation checks.
Neighbor outcomes are four official-fuzzy gains, 190 ties and 588 losses;
scores span 85.16994% to 90.87582%. The unique highest admissible snapshot is
**0063**, **90.87582%**. It swaps only `s32 tileRow;` and `s32 lumaSkip;`
at lines 522 and 540.

Stop: all 782/782 baseline neighbors scored. The selected winner has only
5/782 neighbors represented here, leaving 777 unobserved. No winner fixed-point
or global-optimum claim, and no continuation.
Unchanged `declsearch.py` SHA256:
`9642fe689ee3a4d80236b5f790fdda83397214cd209c62ce07088b3f2b3726bb`.

## Fresh retained-object gates

- Target fuzzy: **90.745094% → 90.87582%**
- Unit fuzzy: **90.66283% → 90.67496%**
- Global fuzzy on this base: **99.73146% → 99.73151%**
- Instructions stay 153/153; ctxdiff 79 → 77; proxy `(16,79)` → `(16,77)`
- Exact stays 2/13 and matched code 660/6596; link/data measures unchanged
- All twelve sibling bodies/scores preserved, including normal411 at 82.70661%
  and normal422 at 88.195946%
- Both YUV400 siblings remain original-byte exact and official 100%
- All allocated non-code sections empty/identical to baseline and original
- Pools identical; literal audit analyzes twelve functions with no candidates/errors
  and the unchanged unequal-size setter skip
- All 1,027 full-report/object gates pass; only RGBA8 object and target score change
- Fresh rebuilt object equals snapshot 0063; its fresh full-report raw unit
  functions, sections and measures equal the official snapshot report
- Default build, explicit progress/report/43U `ok`, and diff check pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`

Partial fuzzy progress only; the completion checker continues to report the
repository's existing code/data/link gaps.

Retained SHA256 values:

- Whole source: `58f728841fcbc43523879afce4b9880f98b064b21cfb3e5d1516cb61b630f3bd`
- Function: `78a678ef02b74e65d47108af9f6772ce9b8c54eafe679ee69c0fe2147047d568`
- Declaration block: `345ea4a26e16b7cb5df65c9bd9ef8a67bac2b0730e1d6b1de97e4601ff247cec`
- Whole object: `b2118c5da3e73a869363de55bc4a247320a9def43a5801a1c7a1d804139327e5`

## Sequential pixel and contained-alias validation

The independent exact integer reference passes **11,138 vectors / 33,414
object executions** against retained, original and newly rebuilt baseline,
with **153/153 instruction coverage** in each. The repository JPEG suite
passes **9,456 paired cases** over 28 functions, including full target coverage.

Reference coverage: 1,792 geometry/pattern vectors, 6,400 saturation vectors and
2,946 contained overlaps. The model independently computes 4×4 tiled AR/GB
addresses, integer chroma arithmetic and clamps for Y[16][16], Cb[8][8], Cr[8][8]
at conversion-buffer offsets 4/260/324. It reads current memory sequentially,
caches chroma per horizontal pair, writes AR then GB, and models vertical
chroma reuse from absolute output-row parity.

Cases cover scales 1/2/4/8, even column residues, row parity, tile crossings,
texture widths and sample patterns. Saturation crosses every luminance byte
with the 25 Cb/Cr pairs from `{-128,-1,0,1,127}`. All overlapping output
halfwords fit the actual 0x184-byte conversion allocation, with descriptors/state
separate. Physical input-plane reads and signed-32 arithmetic are bounded;
no FP is involved. Full-height odd-origin diagnostics that would cross chroma
plane bounds are excluded; shorter scaled odd-row cases remain covered.
All non-stack bytes/guards and GPR14–31, stack pointer and LR agree.
These are finite interpreter diagnostics, not API extensions or formal/hardware proofs.

## Reproduction

`/tmp/jpeg-rgba420-third-neighbors/` preserves baseline/context, frozen
original/config, all `snapshots/0000.*` through `0782.*`, recorder/enumeration,
calls/manifest/selection, every raw official snapshot report, full reports,
all-object inventories, gate logs and model/suite evidence. From the leaf root:

```sh
../.venv/bin/python /tmp/jpeg-rgba420-third-neighbors/score_snapshots.py
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/jpeg-rgba420-third-neighbors/verify.py
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/jpeg-rgba420-third-neighbors/audit.py
PYTHONPATH=../local-tools ../.venv/bin/python tools/decomp-assist/jpeg_differential_audit.py
```

Local source/evidence commit only. Earlier leaves/evidence remain preserved;
no remote writes, other converter work or continuation.
