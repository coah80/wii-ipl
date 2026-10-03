# RGBA420 normal: fixed neighborhood around 90.87582%

Base `636f8eb03a7d3f314d9cb32912230c61d932fd5b`, branch
`agent/bittle/jpeg-rgba420-fourth-neighbors`, 43U only.
Target: `TMCJPEGDEC_converterYUV420toRGBA8` in
`libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8.c`.
Only the same 24 existing, used, uninitialized declarations at lines 520–543
were eligible. All types, including `s8 crValue`, and every other source byte,
assignment, expression, initializer, helper and scope remain fixed.

## Context and historical coverage

#1110 retained 90.87582%, previously snapshot 0063. Its own immediate
neighborhood had only 5/782 orders in that audit's manifest. This separately
authorized pass fixes that new center throughout. Ten current orders overlap
the union of the three earlier official manifests: indices 0, 46, 63, 83, 336,
337, 357, 358, 700 and 701 (baseline plus nine neighbors). The other 773
neighbors are absent from that union. Earlier structural searches may overlap
further; no global novelty claim. No adaptive center, restart, semantic/body
rewrite, other declaration group or continuation.

Baseline SHA256, with function text including exactly one trailing newline:

- Whole source: `58f728841fcbc43523879afce4b9880f98b064b21cfb3e5d1516cb61b630f3bd`
- Function: `78a678ef02b74e65d47108af9f6772ce9b8c54eafe679ee69c0fe2147047d568`
- Declaration block: `345ea4a26e16b7cb5df65c9bd9ef8a67bac2b0730e1d6b1de97e4601ff247cec`
- Function excluding block: `227ede5e96d002bbf01db50bf41093b8557d91d249704e673906557552a44f28`
- Whole source excluding block: `a47bd121a71d5cad81c23415239e4b2d4965aee423bb460a734a9bdae479800c`
- Whole object: `b2118c5da3e73a869363de55bc4a247320a9def43a5801a1c7a1d804139327e5`
- Original whole object: `47227ca66537a3dfc3b41add42a36442ca35f4253279580cc77cf2cd02eab65e`

The fresh leaf copied verified idle main cache and configured explicit cached
compiler, dtk, objdiff, sjiswrap and BSTool paths with
`../toolchain/wibo-release64/wibo` and `WIBO_SJIS_MISSING_IMPORTS=1`.
Ordinary default Ninja reproduced the entire verified main report and all
1,027 object hashes before enumeration. Baseline target was 90.87582%; empty
pools matched. Production flags and repository tools remain unchanged.

During final validation main advanced to the disjoint RGB565 commit `d4b9850a`.
Per parent instruction, this leaf and evidence remain on the frozen base above;
the parent will independently apply and verify the candidate on current main.
No additional cache/evidence duplication or previous-evidence deletion occurred.

## Exactly one fixed-center audit

The unchanged official generators yield 276 pair swaps and 529 distinct
remove/insert moves, overlapping in 23 orders: 782 unique neighbors plus
baseline. All 783 received actual ordinary Ninja/MWCC compilation with exact
immutable source/order/object snapshots, hashes, timestamps, output and status.
Every source remained stable and inside the authorized declaration block.

- 783 distinct source orders and successful real compilations
- 377 distinct whole objects; no failed, no-work or unstable-source calls
- Every frozen object officially scored using a private copy of actual objdiff
  config, preserving diff settings, metadata and mappings
- Only unique unit names and frozen original/snapshot paths changed; no deduplication,
  live-object swapping, structural filtering or artificial aggregate ranking
- Private one-unit baseline raw results equal the full baseline report
- Every snapshot passes sibling/exact/code/data/link/total preservation gates
- Neighbor outcomes: one official-fuzzy gain, 189 ties and 592 losses
- Score range: 85.16994% to 90.973854%

The unique highest admissible snapshot is **0120**, **90.973854%**. It swaps
only `u8* texture;` and `s32 tileRow;` at lines 525 and 540.
Stop: complete fixed baseline neighborhood, 782/782 neighbors scored.
Only 5/782 neighbors of the selected winner appear here, leaving 777 unobserved;
no winner fixed-point or global-optimum claim and no continuation.
Unchanged `declsearch.py` SHA256:
`9642fe689ee3a4d80236b5f790fdda83397214cd209c62ce07088b3f2b3726bb`.

## Fresh retained-object and full gates

- Target fuzzy: **90.87582% → 90.973854%**
- Unit fuzzy: **90.67496% → 90.68405%**
- Reported global fuzzy on this base remains **99.73153%**
- Instructions stay 153/153; ctxdiff 77 → 76; proxy `(16,77)` → `(16,76)`
- Exact stays 2/13 and matched code 660/6596; link/data measures unchanged
- All twelve sibling bodies/scores preserved, including normal411 at 82.70661%
  and normal422 at 88.195946%
- Both YUV400 siblings remain original-byte exact and official 100%
- Allocated non-code sections remain empty/identical to baseline and original
- Pools identical; literal audit analyzes twelve functions with no candidates/errors,
  preserving the unchanged unequal-size setter skip
- All 1,027 full-report/object gates pass; only RGBA8 object and target score change
- Fresh rebuilt object equals snapshot 0120; fresh full-report raw unit functions,
  sections and measures equal the official snapshot report
- Default build, explicit progress/report/43U `ok`, and diff check pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`

This is partial fuzzy progress, with no exact or linking gain. The completion
checker still reports the repository's existing code/data/link gaps.

Retained SHA256 values:

- Whole source: `2f4008ca7f732fe6cbd6dbf52947f396a48a61fc4f7c9dba2706be580165904b`
- Function: `daab783219951ea15431e6cb6d32c2b7207bca7235f96216380dd2f5a4c169b7`
- Declaration block: `f037631306aa1d201c98de679c69aa08f2e04294bf6949d127610d4046830650`
- Whole object: `5165adeb51f85cc889c49f0597c35fc5a2cc1e45a48ef7614aa5a7549ce8203b`

## Sequential pixel and allocation-valid alias gates

The independent exact integer reference passes **11,138 vectors / 33,414
object executions** against retained, original and freshly rebuilt baseline,
with all **153/153 instructions** covered in each. The unchanged JPEG suite
also passes **9,456 paired cases** over 28 functions, including full target coverage.

The reference covers 1,792 geometry/pattern vectors, 6,400 saturation vectors
and 2,946 contained overlaps. It independently computes 4×4 tiled AR/GB
addresses, integer color arithmetic and clamps for Y[16][16], Cb[8][8], Cr[8][8]
at conversion-buffer offsets 4/260/324. It reads live memory sequentially,
caches chroma per horizontal pair, writes AR then GB, and models vertical
chroma reuse using absolute output-row parity.

Cases cover scales 1/2/4/8, even column residues, row parity, tile crossings,
texture widths and sample patterns. Saturation crosses every luminance byte
with all 25 Cb/Cr pairs from `{-128,-1,0,1,127}`. Every aliased output halfword
fits the actual 0x184-byte conversion allocation; descriptors/state remain
separate. Physical input-plane read indices and signed-32 arithmetic are bounded.
Full-height odd-origin diagnostics that would cross chroma-plane bounds are
excluded; shorter scaled odd-row cases remain covered. No FP is involved.
Every non-stack byte/guard and GPR14–31, stack pointer and LR agree.
These are bounded interpreter diagnostics, not API extensions or formal/hardware proofs.

## Reproduction evidence

`/tmp/jpeg-rgba420-fourth-neighbors/` preserves baseline/context, frozen
original/config, all `snapshots/0000.*` through `0782.*`, recorder/enumeration,
calls/manifest/selection, every raw official snapshot report, full reports,
all-object inventories, gate logs and model/suite evidence. From the leaf root:

```sh
../.venv/bin/python /tmp/jpeg-rgba420-fourth-neighbors/score_snapshots.py
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/jpeg-rgba420-fourth-neighbors/verify.py
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/jpeg-rgba420-fourth-neighbors/audit.py
PYTHONPATH=../local-tools ../.venv/bin/python tools/decomp-assist/jpeg_differential_audit.py
```

Local source/evidence commit only. Previous leaves/evidence preserved; no remote
writes, main edits, other converter work or continuation.
