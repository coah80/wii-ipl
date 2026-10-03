# RGBA211 edge final-expression declaration search

Base `7b324519`; branch `agent/bittle/rgba211edge-declaration-context`; 43U only.
Previously validated RGBA422 and RGBA411edge branches/evidence remain frozen.
Target: `TMCJPEGDEC_converterYUV211toRGBA8edge` in
`libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8.c`.

## Eligible context and pinned hashes

Only the 24 existing, used, uninitialized scalar/pointer declarations at lines
770..793 could move. `s8 crValue`, `u8 value`, and all other types are unchanged.
No initializer, body expression, scope, helper, statement, compilation flag,
or source byte outside that block changed.

The prior official search in `fz20.attempts.md:1139..1195` capped at 250
evaluations: `(6,50) -> (6,49)`, fuzzy `91.86957% -> 91.95652%`.
Its retained function is at `c7896c38`. The sole later function change, in
`786a2dd3`, changed `(blue | green | red)` to `(red | green | blue)`, producing
92.0% (`fz20.attempts.md:1760..1766`). Exact function comparison confirms every
other byte is unchanged; the current body is identical at `786a2dd3`,
`e8241734`, and `7b324519`. Earlier round-four custom declaration trials,
including 500 plateau-inclusive trials, preceded this final expression
context. No current-context official fixed point was recorded before this run.

SHA256 values:

- Earlier search-end function: `f31a696a5d86b6506aea4d249fbaa91b5cfe1423f1c94f26e21de0039f0400e7`
- Current baseline function: `e5f462250086267d4b6460b8f659c0cd51770272d130e25c077389789bd1c7fb`
- Baseline declarations: `5451a3f84e856afed80e9ed6fedd97f172995ed352e9073e48543b5c4d935da7`
- Baseline entire source: `ec53fd090e5d068e301192ad320ad471c1f933e9caf5c7f38233e813b1c380a4`
- Retained candidate function: `5020a311cf9a6b2e70a81a8dc70bf5606d921472986f14dc3c8f0949d707e6f3`
- Retained entire source: `c35b810dd4c60332563f54f424cf3887ebdee99698cd51e8909d5bf5c298b490`

## One authorized official run

Fresh baseline object/full build/report reproduced 92.0% before this one
unchanged official invocation, with ordinary compilation for every evaluation:

```sh
WIBO_SJIS_MISSING_IMPORTS=1 NINJA=../.venv/bin/ninja \
  PYTHONPATH=../local-tools ../.venv/bin/python -u \
  tools/decomp-assist/declsearch.py \
  libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 \
  TMCJPEGDEC_converterYUV211toRGBA8edge --lines 770 793 --max-evals 1600
```

- Actual evaluations: 1,080 distinct orders within this invocation
- Trajectory: `(6,49) -> (6,48) -> (6,47)`
- Stop: natural local fixed point, before the 1,600-evaluation cap
- Final immediate neighborhood: 276 swaps + 529 distinct moves minus 23
  shared neighbors = 782 unique neighbors, all scored without an improvement
- No restart, continuation, other-converter search, or tool modification

The fixed point is relative to the structural/positional lexicographic score.
It does not exhaust all 24! orders, plateau paths, combinations, other source
forms, or the official fuzzy objective independently.

## Fresh gates and retained progress

- Official function fuzzy: `92.0% -> 92.17391%`
- Unit fuzzy: `90.44754% -> 90.45967%`
- Global fuzzy: `99.72511% -> 99.72516%`
- Instructions `115/115`; ctxdiff differences `49 -> 47`
- Exact functions unchanged `2/13`; matched code unchanged `660/6596`
- No full 1,027-unit report regressions; all exact/link/data totals unchanged
- All twelve sibling object bodies byte-identical to the saved baseline
- Both YUV400 siblings remain objdiff 100%, retail-byte exact, ctxdiff zero
  (`76/76` and `89/89` instructions)
- Source change is solely the authorized declaration permutation
- Candidate object deleted and freshly rebuilt; identical to search-end object
- Baseline/candidate/original have no allocated non-code sections
- Pool empty/identical; literal audit has zero candidates/errors, twelve
  functions analyzed, unchanged unequal-size setter skipped
- Full default 43U build, explicit `progress build/43U/report.json
  build/43U/ok`, and `git diff --check` pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`

This is partial fuzzy progress, with no added exact function or linking gain.
The global completion checker remains `DECOMPLETE_FAIL`, exit 1, due to
existing incomplete repository code/data/linking totals, unchanged here.

## Independent vertical-chroma edge and alias checks

The repository JPEG differential audit passes all 9,456 paired cases.
A separate scalar vertical-2:1 model passes 12,591 vectors against candidate,
original, and saved baseline: 37,773 object executions. The physical planes are
Y[16][8], Cb[8][8], Cr[8][8], at conversion-buffer offsets 4/132/196. Scaled
MCU dimensions are 8/scale by 16/scale. Chroma samples are reused vertically;
the independent model directly calculates row `(dy + (y & 1)) / 2`, preserving
the original dependence on absolute output-row parity.

- 657 cases cover every edge width 0..8/scale and height 0..16/scale, scales
  1, 2, 4, 8, at three even-row output origins
- 256 cases independently exercise both dimension-selection branches,
  varying origins and constant/random planes
- 64 additional machine-level row/column residue cases include odd starting
  rows; their heights keep reads within the logical chroma planes
- 6,400 saturation vectors cross every luminance byte with Cb/Cr pairs from
  `{-128,-1,0,1,127}`, using multiple columns and three rows
- 5,214 halfword-aligned input/output overlaps are wholly within the actual
  0x184-byte convBuf; descriptors and state remain separate

All 115 instructions are covered in each object. Every byte below the reserved
stack region, including guards, agrees with the scalar model. The interpreter
checks GPR14..31, stack pointer, and LR restoration. Alias cases preserve actual
read/store sequencing and reread chroma after its vertical rewind, so writes
can affect later input. Additional residues/alias cases are machine-level
checks, not claims that the public API permits these inputs. These bounded
integer-interpreter tests are not formal equivalence or Wii runtime validation.

## Reproduction artifacts

`build/43U/rgba211edge-declaration-context/` retains baseline hashes/source/
object/report, `search.log`, search-end/candidate objects, candidate/final
reports, `candidate.ctx`, exact-sibling/pool/literal/build/status/completion
results, `verify.py`, `verification.log`, `audit.py`, `audit-output.txt`,
`audit-results.json`, and `differential.log`. Run either verification script
from this worktree root with `PYTHONPATH=../local-tools ../.venv/bin/python`.
No remote writes, linking changes, or edits to previously frozen branches.
