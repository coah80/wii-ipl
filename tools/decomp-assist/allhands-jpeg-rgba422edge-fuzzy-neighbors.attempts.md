# RGBA422 edge: fixed historical-repeat neighborhood with official scores

Base `86e56941932022ad22c325d39aa0191785a37f0f`, 43U only. Branch:
`agent/bittle/jpeg-rgba422edge-fuzzy-neighbors`. The retained production change
only swaps the adjacent uninitialized `lumaSkip` and `tileRow` declarations in
`TMCJPEGDEC_converterYUV422toRGBA8edge`. Official fuzzy improves
**91.9469% -> 92.0354%**, with all existing exact/code/data/link gates preserved.

## Exact scope and source safety

Only the 24 contiguous leading declarations at lines 444–467 of
`Texture_MCUtoRGBA8.c` were eligible: 18 `s32` scalars and six pointers. Every
declaration is used and initializer-free. They share one existing function
scope; there is no shadowing, local address-taking/escape, declaration-dependent
initializer, variably modified type, or intervening statement. No expression,
assignment, initializer, type, scope, helper, production flag, or other source
byte changes. The retained change is a readable two-line reorder.

All locals are assigned before reads under the existing even-x requirement:

- Luminance, Cb, Cr, state, tile width and texture are assigned before use
- Both branches assign width/height before endpoint and skip computations
- Endpoints/skips are assigned before loops; output/tile row at row entry
- The column for-initializer precedes its condition and increments
- Even x makes the first pixel of each nonempty row assign chroma values and
  offsets; the paired odd pixel reuses those assigned offsets
- Each pixel assigns value and all colors before overflow tests, clamps/stores

`scope-proof.json` records the proof and body hash. The complete function,
including its retained center, equals #1087 (`9f39cd84`) through all seven later
RGBA source commits. Later normal411/422/420 improvements are frozen.

Baseline SHA256 pins:

- Function: `ed89120c68826826bdf016e86abfdd149158f3df7b265d9cc85acb5767f3e622`
- Declaration block: `d9d873456f5673c6578c306d3abc7336d50cfe5230d1bd54bcd299649d2a6ca7`
- Body after declarations: `0aab5733305424b14a14b0b7c28d6562296a3b29b071f7ffa067b9f3d4282f7b`
- Whole source: `2f4008ca7f732fe6cbd6dbf52947f396a48a61fc4f7c9dba2706be580165904b`
- Whole object: `5165adeb51f85cc889c49f0597c35fc5a2cc1e45a48ef7614aa5a7549ce8203b`

## Historical repetition and the actual scoring gap

`rgba422edge-declaration-context.attempts.md` records the earlier 1,392-evaluation
run, capped at 1,600 but naturally stopping at structural/positional `(6,51)`.
Its final 782 immediate neighbors were fully compiled without an improvement
under that proxy. It explicitly does not establish independent official-fuzzy
closure. The older 250-evaluation cap in `fz20.attempts.md:886–950` predates the
retained overflow-test context.

**All 783 function orders here repeat historical compilation.** The purpose is
to obtain the missing official scores, not new-order discovery. Earlier per-order
artifacts did not survive the workspace reset; the historical coverage statement
comes from the committed log, not a reconstructed per-order manifest. The wider
translation unit includes later sibling improvements, all held fixed here.

## Exactly one fixed neighborhood

Fresh default build, full official report and all 1,027 object hashes reproduced
verified main. The source/block/body pins and 91.9469% baseline were checked.
An initial preparation assertion used an incorrectly substituted expected hash;
it stopped before any order compilation or source change and was corrected to
the independently pinned hash. The authorized enumeration itself ran once.

The unchanged official `declsearch.py` swap and pop/insert neighbor generators
were reused around one fixed center: 276 swaps + 529 distinct moves - 23 shared
orders = 782 unique neighbors, plus baseline. No adaptive center, restart,
continuation, semantic variation, or other converter trial occurred.

- Exactly 783 successful real MWCC/Ninja compilations; 783 distinct orders
- Zero failed/no-work calls and zero unstable sources; 424 distinct objects
- Every immutable source/object/hash, actual argv/timestamps/mtime and compiler
  output recorded; every ordinary Ninja call compiled the requested object
- All snapshots officially scored using a private copy of actual objdiff config,
  preserving options, metadata and mappings, with a frozen original object
- No deduplication, live-object swapping, proxy filtering or batch-aggregate ranking
- Private baseline functions/sections/measures equal the full baseline report
- All 783 pass raw outside-target bytes, section headers, relocation vectors,
  sibling raw/report/exact, allocated non-code and code/data/link checks

Six neighbors improve fuzzy, 158 tie the baseline and 618 lose. The highest
score is 92.0354%, reached by snapshots 0046, 0047 and 0321, all yielding the same
whole object. The first minimal tied winner, 0046, swaps only lumaSkip/tileRow.
Both baseline and winner retain proxy `(6,51)` and ctxdiff 51, explaining why the
old strict-proxy search did not select this improvement.

Stop reason: all 782 neighbors of the authorized baseline completed. Only
49/782 immediate neighbors of the selected winner are present in this set;
733 remain unobserved here. This is not a winner fixed-point or global-optimum
claim. No continuation was performed.

## Fresh retained-object gates

The selected exact source was freshly built by default Ninja and its whole
object equals saved snapshot 0046. Explicit progress/report/43U-ok, fresh full
report, source safety, diff check and all 1,027 object/report comparisons pass.
Only this target function's code/fuzzy changes; all other units and sibling
improvements remain preserved.

- Target: 91.9469% -> 92.0354%; 113/113 instructions, ctxdiff 51 unchanged
- RGBA unit: 90.68405% -> 90.69012%
- Global fuzzy on this base: 99.73161% -> 99.731636%
- Exact stays 2/13 functions; matched code stays 660/6596 bytes
- Both YUV400 siblings remain raw-byte exact; all twelve sibling bodies fixed
- All raw section headers/relocations and bytes outside target fixed
- No allocated non-code; empty pools identical
- Literal audit: 12 functions analyzed, zero candidates/errors; setter's unequal
  size remains the same skip
- All 186 shared immutable compiler/tool hashes and actual objdiff config unchanged
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`
- Overall completion remains `DECOMPLETE_FAIL`; this is a partial fuzzy gain

Retained SHA256 values:

- Function: `4eaeed366d0ad2c9ee3a8f2cb518eb0458604625222ffce0d6770b447b02f23c`
- Declaration block: `6bcbbd5a7ad8e43490ae08be9fdb02e40637effb3ddeed5fef2f137b8c96986b`
- Whole source: `6340fe5b79280f8429092aaa62b9ae7fc252c06af956fe6aa0eb884aceb8136b`
- Whole object: `64dff303c3c0525eef81e5f1925fdf7e22733a43fe68a099b79f9163e7609eca`
- Full report: `f89df6b296a442c8a713fefda15c6f8d6ab732c425396de3133c1c711b5e8e12`

## Sequential pixel and contained-alias validation

The independent integer reference passes **11,895 vectors / 35,685 executions**
against the actual retained object, original and baseline, covering all 113
instructions in each. It uses physical Y[8][16], Cb[8][8], Cr[8][8] at offsets
4/132/196; horizontal pairs cache chroma, source strides remain 16/8/8, and
AR/GB stores are sequential. Odd widths process the final partial pair. All
origins satisfy the existing even-x requirement.

- 657 cases cover every bounded width/height at scales 1/2/4/8 and three origins
- 256 cases cover both dimension-selection branches, four origins/patterns
- 64 additional tiled row/column residue cases
- 6,400 saturation cases cross all luminance bytes with signed Cb/Cr values
  {-128,-1,0,1,127}, partial pairs and two rows
- 4,518 halfword-aligned overlaps wholly inside the actual 0x184-byte convBuf

Descriptors/state stay separate; subsequent aliased input reads observe earlier
stores, while the current pair retains its cached chroma. All non-stack bytes,
guards, preserved GPRs, SP and LR pass. These finite interpreter cases are not
formal equivalence or Wii hardware testing; extra overlap/residue cases are
machine-level checks, not expanded public API guarantees. The repository JPEG
suite independently passes **9,456 paired cases across 28 functions**.

## Evidence and independent reproduction

Leaf: `/workspace/scratch/0128b1ed02cc/wii-jpeg-rgba422edge-fuzzy-neighbors`.
Evidence: `/workspace/scratch/0128b1ed02cc/jpeg-evidence/rgba422edge-fuzzy-neighbors/`.
All new evidence is in workspace storage. Shared tools are reused read-only;
prior branches/evidence are untouched. No remote writes or main edits occurred.

The directory contains `pin_baseline.py`, `enumerate.py`, `ninja-record.py`,
`score_snapshots.py`, `object_invariants.py`, `verify.py`, `final_gates.py`,
`audit.py`, source/object snapshots, official reports, manifests, full baseline/
final reports and 1,027-object hashes, scope/context/retained hashes and all logs.
The enumeration refuses a restart after its recorded calls exist.

From the leaf, independent read/re-score/model reproduction:

```sh
PYTHONPATH=../local-tools ../.venv/bin/python ../jpeg-evidence/rgba422edge-fuzzy-neighbors/score_snapshots.py
PYTHONPATH=../local-tools ../.venv/bin/python ../jpeg-evidence/rgba422edge-fuzzy-neighbors/verify.py
PYTHONPATH=../local-tools ../.venv/bin/python ../jpeg-evidence/rgba422edge-fuzzy-neighbors/audit.py
PYTHONPATH=../local-tools ../.venv/bin/python tools/decomp-assist/jpeg_differential_audit.py
```
