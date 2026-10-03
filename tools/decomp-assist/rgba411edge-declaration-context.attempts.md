# RGBA411 edge final-expression declaration search

Base `dc3eede8`; branch `agent/bittle/rgba411edge-declaration-context`; 43U only.
The previously validated RGBA422 branch and its artifacts remain frozen.
Target: `TMCJPEGDEC_converterYUV411toRGBA8edge` in
`libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8.c`.

## Eligible context

Only lines 288..310 were eligible: 23 existing, used, uninitialized scalar or
pointer declarations. The declaration `s8 crValue` and every other type were
preserved. No initializer, expression, scope, helper, statement, compilation
flag, or source byte outside the declaration block changed.

The prior official search is logged in `fz20.attempts.md:759..820`: 250
evaluations, capped after `(6,69) -> (4,56)`, fuzzy `90.80357% -> 93.83929%`.
Its retained source is `c7896c38`. Commit `786a2dd3` subsequently changed only
one overflow expression in this function: `(blue | red | green)` to
`(green | red | blue)`, yielding `93.88393%` (`fz20.attempts.md:1725..1730`).
Exact function comparison confirms no other change from that search-end body;
current function bytes are identical at `786a2dd3`, `e8241734`, and `dc3eede8`.
Later `tex1.attempts.md` records rejected structural trials and excludes
standalone declaration permutations. No final-context official fixed point
was recorded before this authorized run.

Pinned SHA256 values:

- Earlier search-end function: `3b0e7a0a09706d2d7654871dfb5d47d4d2c72d7c78a1801bcad4315932145a2b`
- Current baseline function: `f3f785894e5a5599289837cb775af58065dae32e8dd03cdcae0ccf38efa3cf8e`
- Baseline declaration block: `4ca4c6dbe945ee8cbba7c5d3c45ee13328ae89d2333df40d1314456cc759c09f`
- Baseline whole source: `c90f879594dac677d81bfc9524fc4653d847d2a4a9fc68f3999759f1ab440b12`
- Retained candidate function: `a47aed8fea3a4cafeb4a5128698b610323977fa3aaa476f372c71da51f3c5e56`
- Retained whole source: `ec53fd090e5d068e301192ad320ad471c1f933e9caf5c7f38233e813b1c380a4`

## Single authorized run

The unchanged official tool compiled every evaluated order normally:

```sh
WIBO_SJIS_MISSING_IMPORTS=1 NINJA=../.venv/bin/ninja \
  PYTHONPATH=../local-tools ../.venv/bin/python -u \
  tools/decomp-assist/declsearch.py \
  libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 \
  TMCJPEGDEC_converterYUV411toRGBA8edge --lines 288 310 --max-evals 1600
```

- Actual evaluations: 1,227 distinct orders within this invocation
- Trajectory: `(4,56) -> (4,53) -> (4,52) -> (4,51)`
- Stop: natural local fixed point, before the 1,600-evaluation cap
- Final immediate neighborhood: 253 pair swaps + 484 distinct moves minus
  22 common neighbors = 715 unique neighboring orders, all scored without a
  lexicographic structural/positional improvement
- No restart, continuation, source-body trial, or modified search tool

The fixed point concerns this official tool's objective and immediate
neighborhood; it does not exhaust 23! permutations, plateau paths, combined
moves, other source forms, or the official fuzzy objective independently.

## Retained result and gates

- Official function fuzzy: `93.88393% -> 94.10714%`
- Unit fuzzy: `90.43238% -> 90.44754%`
- Global fuzzy: `99.72499% -> 99.725006%`
- Instructions `112/112`; ctxdiff differences `56 -> 51`
- Exact functions unchanged `2/13`; matched code unchanged `660/6596`
- All full-report exact/link/data totals unchanged; no 1,027-unit regressions
- All twelve sibling function bodies byte-identical to the saved baseline
- Both exact YUV400 siblings stay objdiff 100%, retail-byte-identical, and
  ctxdiff zero (`76/76` and `89/89` instructions)
- Source block is precisely a permutation; all other source bytes identical
- Baseline and candidate objects freshly rebuilt; final object is identical
  to the official tool's retained search-end object
- Baseline/candidate/original have no allocated non-code sections
- Pool identical and empty; all-functions literal audit has zero candidates
  or errors, twelve functions analyzed, unchanged unequal-size setter skipped
- Full 43U build, `build/43U/ok`, and `git diff --check` pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`

This is partial fuzzy progress, with no new exact function or linking gain.
The global completion checker remains `DECOMPLETE_FAIL`, exit 1, due to the
repository's existing incomplete code/data/link totals, unchanged here.

## Independent edge-pixel and alias model

The repository JPEG differential audit passes all 9,456 paired cases.
A separate scalar 4:1:1 edge model passes 11,828 vectors against candidate,
original, and saved baseline: 35,484 object executions. Input planes are
Y[8][32], Cb[8][8], Cr[8][8], at conversion-buffer offsets 4/260/324. Each
chroma sample serves four horizontal pixels, without chroma-row reuse.
All tested x origins satisfy the existing four-pixel alignment assertion.

- 1,257 edge-size cases: every width 0..32/scale and height 0..8/scale for
  scales 1, 2, 4, 8 at three output origins, including partial chroma groups
- 256 cases independently cover both dimension-selection branches, four
  row/tile origins, and constant/random planes
- 6,400 saturation cases: every luminance byte crossed with Cb/Cr pairs from
  `{-128,-1,0,1,127}`, with partial groups and multiple rows
- 3,915 halfword-aligned input/output overlaps wholly inside the actual
  0x184-byte conversion buffer; descriptors and state remain separate

All 112 instructions are covered in each object. Every byte below the
interpreter's reserved stack region, including output guards, agrees with the
scalar model; GPR14..31, stack pointer, and LR are restored. The alias model
uses actual sequential reads/stores and group-local cached chroma. Aliasing
and additional row residues are machine-level checks, not a claim that the
public API permits them. Finite integer-interpreter tests are not formal
equivalence or Wii hardware validation.

## Reproduction

`build/43U/rgba411edge-declaration-context/` retains baseline hashes/source/
object/report, `search.log`, rebuilt candidate/search-end objects, final report,
`candidate.ctx`, exact-sibling/pool/literal/build/status/completion results,
`verify.py`, `verification.log`, `audit.py`, `audit-output.txt`,
`audit-results.json`, and `differential.log`. Run either verification script
from this worktree root using `PYTHONPATH=../local-tools ../.venv/bin/python`.
No remote writes, linking changes, or previously frozen branch edits.
