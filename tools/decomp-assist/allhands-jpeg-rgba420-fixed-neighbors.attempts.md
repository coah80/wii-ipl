# RGBA420 normal: fixed-neighborhood official-fuzzy audit

Base `36f0d43f2dcd838d2b8312576c31d624819564bc`, branch
`agent/bittle/jpeg-rgba420-fixed-neighbors`, 43U only.
Target: `TMCJPEGDEC_converterYUV420toRGBA8` in
`libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8.c`.
Only the 24 existing, used, uninitialized declarations at lines 520–543 could
move. `s8 crValue` and every other type remain unchanged. All expressions,
assignments, initializers, scopes, helpers and source bytes outside that block
are fixed. No pixel-lifetime reconstruction or other converter trial.

## Historical repetition and missing objective

`rgba420-final-expression.attempts.md` records a 783-evaluation capped search
that selected 90.254906%, followed by a separately authorized continuation.
That continuation evaluated baseline plus all 782 immediate neighbors and
stopped at a structural/positional fixed point `(16,84)`. Its log explicitly
disclaims independent official-fuzzy closure. Current function text matches
the retained #1076 function at `d170fbb8` and subsequent merged source.

**All 783 function orders here repeat historical compilation.** The purpose
is to record the missing official-fuzzy score for every order. This is not
new-order discovery, and no historical gain was assumed. The translation unit
now contains later sibling improvements, all preserved. Historical per-order
objects and official reports are unavailable after the workspace reset.

## Pinned context and fresh baseline

SHA256, with function text including exactly one final newline:

- Whole source: `1d4cb40cbbc2db10aebe68c0dbbbe1696eef476d1352010ddd3476fbdf7ba06f`
- Function: `19c5fa9f0f72f32af94d32bafaed408ba7c733502f7a739304b5ad2a27f745d7`
- Declaration block: `bc511e4c78245efdf633e594729a8c7203d04c29743a8e55a3097c193435a176`
- Function excluding block: `227ede5e96d002bbf01db50bf41093b8557d91d249704e673906557552a44f28`
- Whole source excluding block: `a47bd121a71d5cad81c23415239e4b2d4965aee423bb460a734a9bdae479800c`
- Whole object: `ed891692675bc95d734ccb74bcc94f0bc6c1b7924b9b404b8c7cf419891f32d5`
- Original whole object: `47227ca66537a3dfc3b41add42a36442ca35f4253279580cc77cf2cd02eab65e`

The fresh leaf copied the verified idle main cache, then configured explicit
cached compiler, dtk, objdiff, sjiswrap and BSTool paths with
`../toolchain/wibo-release64/wibo` and `WIBO_SJIS_MISSING_IMPORTS=1`.
Ordinary default Ninja rebuilt the leaf. Its full report and all 1,027 object
hashes equaled verified main. Baseline target fuzzy was 90.254906%; pools were
empty and identical. Production flags and repository tools are unchanged.

## Exactly one fixed-center audit

The unchanged official `declsearch.py` generators give 276 pair swaps and 529
distinct remove/insert moves, with 23 overlaps: 782 unique neighbors plus
baseline. The center never changed; no structural filtering, adaptive search,
restart, additional declaration group or continuation was used.
The repository tool remains SHA256
`9642fe689ee3a4d80236b5f790fdda83397214cd209c62ce07088b3f2b3726bb`.

Every order received ordinary real Ninja compilation with an immutable exact
source/order/object snapshot. The recorder preserved hashes, timestamps,
compiler output and status, and checked source stability and allowed bounds.
There were 783 distinct source orders, 783 real successful MWCC compilations,
377 distinct whole objects, and zero failed/no-work/unstable-source calls.

All immutable objects received official objdiff scores using a private copy of
the actual project config. Diff settings, metadata and mappings were preserved;
only unique unit names and frozen original/snapshot paths changed. There was no
deduplication, live-object swapping or artificial aggregate ranking. The private
one-unit baseline matched the full baseline's raw functions, sections and measures.

All 783 snapshots preserve all twelve sibling bodies/scores, both exact functions,
allocated non-code contents and code/data/function/link measures and totals.
Among neighbors, one improves official fuzzy, 200 tie and 581 lose. The unique
highest admissible score is snapshot **0073**, **90.35294%**. It swaps only
`u8* luminance;` and `s32 lumaSkip;` at lines 523 and 530. Scores span
86.39216% to 90.35294%.

Stop: complete fixed baseline neighborhood, all 782/782 neighbors scored.
Only 5/782 neighbors of the selected winner occur in this manifest; 777 are
unobserved here. No winner fixed-point or global-optimum claim, and no continuation.

## Fresh retained-object and full-build gates

- Target fuzzy: **90.254906% → 90.35294%**
- Unit fuzzy: **90.61734% → 90.62644%**
- Global fuzzy on this base: **99.73138% → 99.7314%**
- Instructions remain 153/153, ctxdiff 84, proxy score `(16,84)`
- Exact stays 2/13 and matched code 660/6596 bytes; link/data totals unchanged
- All twelve sibling bodies preserved, including normal411 at 82.70661% and
  normal422 at 88.195946%
- Both YUV400 siblings remain original-byte exact and official 100%
- Allocated non-code sections remain empty/identical to baseline and original
- Baseline/final pools identical; literal audit has twelve functions analyzed,
  no candidates/errors, and the unchanged unequal-size setter skip
- All 1,027 full-report/object gates pass; only the RGBA8 object and target score change
- Fresh rebuilt object equals snapshot 0073 byte-for-byte; fresh full-report raw
  unit functions, sections and measures equal its official snapshot report
- Default build, explicit progress/report/43U `ok`, and diff check pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`

This is partial fuzzy progress; the completion checker still reports existing
repository-wide code/data/link gaps, with no new loss.

Retained SHA256 values:

- Whole source: `ac49d186094861e300e7a066d5b006c133d131dc2d348b1142902441c5559c72`
- Function: `a2686af50fb1cfd223d6b304d4b7f784bb3ea948f2b1801882ac1a6532fcb075`
- Declaration block: `c3af93f9d96f858ef115f13a6f3206facd0893504f6c81dc16776a531d56eeb6`
- Whole object: `aa74b466e7cf3ad626a90399cafde841928ab775e1cd6a7cf1fd3be72c9fa28a`

## Sequential pixel and contained-overlap validation

An independent exact integer reference passes **11,138 vectors / 33,414
object executions** against retained, original and baseline objects, exercising
all **153/153 instructions** in each. Physical planes are Y[16][16], Cb[8][8]
and Cr[8][8] at conversion-buffer offsets 4/260/324. Output is
16/scale by 16/scale for scales 1/2/4/8, with two-pixel horizontal chroma groups.

- 1,792 geometry/pattern cases cover scales, even column residues, row parity,
  tile crossings, minimal rounded/large texture widths and sample patterns
- 6,400 saturation cases cross every luminance byte with all 25 Cb/Cr pairs
  from `{-128,-1,0,1,127}`
- 2,946 halfword-aligned overlaps place every output halfword wholly inside the
  actual 0x184-byte conversion allocation, keeping work/state descriptors separate

The model independently computes 4×4 tiled AR/GB addresses, exact chroma
arithmetic and clamp results. It reads live memory sequentially, caches chroma
per horizontal pair, writes AR then GB, and models vertical chroma reuse from
absolute output-row parity. Subsequent aliased input reads see prior stores.
Physical-plane read indices and all signed-32 integer intermediates are bounded.
There are no floating-point operations. Full-height odd-row diagnostic origins
are excluded because they would read beyond the chroma planes; shorter scaled
odd-row cases remain covered. Every non-stack byte and guard matches, and GPR14–31,
stack pointer and LR are preserved. These are finite machine-level diagnostics,
not extensions of API validity or formal/hardware proofs.

The unchanged JPEG differential suite also passes **9,456 paired cases** over
28 functions, including all 153 instructions of RGBA420 normal.

## Reproduction evidence

`/tmp/jpeg-rgba420-neighbors/` contains pinned baseline source/object/full report,
context, frozen original/config, all `snapshots/0000.*` through `0782.*`, ordinary
Ninja recorder, fixed enumeration, calls, manifest, selection, every raw official
snapshot report, all-object inventories, full build/report/pool/ctx/literal/status
and completion logs, and the reference/suite evidence.

From the leaf root:

```sh
../.venv/bin/python /tmp/jpeg-rgba420-neighbors/score_snapshots.py
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/jpeg-rgba420-neighbors/verify.py
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/jpeg-rgba420-neighbors/audit.py
PYTHONPATH=../local-tools ../.venv/bin/python tools/decomp-assist/jpeg_differential_audit.py
```

Local source/evidence commit only. Previous leaves and evidence are preserved;
no remote writes, additional audit or continuation.
