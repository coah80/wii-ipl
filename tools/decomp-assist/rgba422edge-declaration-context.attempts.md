# RGBA422 edge final-expression declaration search

Base `a2c008c4`; branch `agent/bittle/rgba422edge-declaration-context`; 43U only.
All previous RGBA branches/evidence remain frozen. Target:
`TMCJPEGDEC_converterYUV422toRGBA8edge` in
`libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8.c`.

## Verified context

Only lines 444..467 were eligible: 24 existing, used, uninitialized scalar or
pointer declarations. Every type, initializer, body expression, statement,
scope, helper, compilation flag, and source byte outside the block is unchanged.

The earlier official search (`fz20.attempts.md:886..950`) capped at 250
evaluations, ending `(6,68)` after starting `(12,84)`; its retained fuzzy was
90.04425%. The search-end function at `c7896c38` differs from the current
baseline only by the overflow test changed in `786a2dd3` from
`(blue | green | red)` to `(red | green | blue)`, producing 90.08849%
(`fz20.attempts.md:1692..1701`). Exact function comparison was repeated before
this run. No current-context official fixed point was recorded before it.

Pinned SHA256 values:

- Earlier search-end function: `ab286761736afb0a3b812b5f19878fea2fd47189126132af9342f52a2b7a0ed8`
- Baseline function: `65979211dfeff0f56a50370b739b3694c57a386f9f52a21b0d3eb780a764dbe2`
- Baseline declarations: `5d7f99140080df5b3f1d760f49b3b97259c613f08155b57c40c99af0a00557ce`
- Baseline source: `c35b810dd4c60332563f54f424cf3887ebdee99698cd51e8909d5bf5c298b490`
- Retained function: `ed89120c68826826bdf016e86abfdd149158f3df7b265d9cc85acb5767f3e622`
- Retained source: `d4651ae1f7dd68082c84008ecce8b12c8f9d1053bc09ec1c0694acbb114b9cba`

## One authorized run

Fresh baseline object/full build/report reproduced 90.08849%, 113/113
instructions, and score `(6,68)`. The unchanged official tool was run once,
with ordinary compilation at every evaluation:

```sh
WIBO_SJIS_MISSING_IMPORTS=1 NINJA=../.venv/bin/ninja \
  PYTHONPATH=../local-tools ../.venv/bin/python -u \
  tools/decomp-assist/declsearch.py \
  libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 \
  TMCJPEGDEC_converterYUV422toRGBA8edge --lines 444 467 --max-evals 1600
```

- Actual evaluations: 1,392 distinct orders within this invocation
- Trajectory: `(6,68) -> (6,65) -> (6,64) -> (6,61) -> (6,60) -> (6,59)
  -> (6,55) -> (6,51)`
- Stop: natural local fixed point, before the 1,600-evaluation cap
- Final immediate neighborhood: 276 pair swaps + 529 distinct moves minus
  23 shared neighbors = 782 unique neighbors, all scored without improvement
- No restart, continuation, other-converter run, or modified search tool

The fixed point is relative to the structural/positional lexicographic score,
not an exhaustive search of 24! permutations, plateau paths, combined moves,
other source forms, or the official fuzzy objective considered independently.

## Strict retained gain and gates

- Official function fuzzy: `90.08849% -> 91.9469%`
- Unit fuzzy: `90.45967% -> 90.58702%`
- Global fuzzy: `99.72663% -> 99.72691%`
- Instructions `113/113`; ctxdiff differences `68 -> 51`
- Exact functions unchanged `2/13`; matched code unchanged `660/6596`
- All 1,027-unit exact/link/data totals unchanged; zero report regressions
- All twelve sibling object bodies byte-identical to the saved baseline
- Both YUV400 siblings remain objdiff 100%, retail-byte exact, ctxdiff zero
  (`76/76` and `89/89` instructions)
- The source block is exactly a permutation; all other source bytes identical
- Candidate object deleted and freshly rebuilt; identical to search-end object
- Baseline/candidate/original contain no allocated non-code sections
- Empty/identical pools; literal audit has zero candidates/errors, twelve
  functions analyzed, unchanged unequal-size setter skipped
- Full default 43U build, explicit progress/report/`build/43U/ok` targets,
  and `git diff --check` pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`

This is partial fuzzy progress, with no new exact function or linking gain.
The global completion checker remains `DECOMPLETE_FAIL`, exit 1, reflecting
existing repository-wide incomplete code/data/link totals, unchanged here.

## Independent 4:2:2 edge and alias audit

The repository JPEG differential audit passes all 9,456 paired cases.
A separate scalar 4:2:2 edge model passes 11,420 vectors against candidate,
original, and saved baseline: 34,260 object executions. Physical planes are
Y[8][16], Cb[8][8], Cr[8][8], at conversion-buffer offsets 4/132/196. Each chroma
sample serves two horizontal pixels, with fresh chroma every row. Scaled MCU
dimensions are 16/scale by 8/scale. All x origins satisfy the existing even-x
assertion; tiled x residue 2 is exercised.

- 657 edge-size cases: every width 0..16/scale and height 0..8/scale for
  scales 1, 2, 4, 8 at three origins, including empty blocks and odd widths
- 256 cases independently exercise both dimension-selection branches,
  four row/tile origins, and constant/random planes
- 6,400 saturation cases cross all luminance bytes with signed Cb/Cr pairs
  from `{-128,-1,0,1,127}`, using partial pairs and multiple rows
- 4,107 halfword-aligned overlaps lie wholly within the actual 0x184-byte
  conversion allocation, with descriptors and state kept separate

All 113 instructions are covered in each object. Every byte below the reserved
stack region, including guards, agrees with the scalar model. The interpreter
checks GPR14..31, stack pointer, and LR restoration. The alias oracle preserves
sequential reads/stores and pair-local chroma caching. Aliasing and additional
row residues are machine-level checks, not claims of public API validity.
These finite integer-interpreter tests are not formal equivalence or Wii
hardware validation.

## Reproduction artifacts

`build/43U/rgba422edge-declaration-context/` retains baseline hashes/source/
object/report, `prior-search.txt`, `search.log`, search-end/candidate objects,
candidate/final reports, `candidate.ctx`, exact-sibling/pool/literal/build/
status/completion results, `verify.py`, `verification.log`, `audit.py`,
`audit-output.txt`, `audit-results.json`, and `differential.log`. Run either
verification script from this root with `PYTHONPATH=../local-tools
../.venv/bin/python`. No remote writes or linking changes.
