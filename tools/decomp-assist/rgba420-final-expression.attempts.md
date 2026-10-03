# RGBA420 final-expression declaration search

Base: `a4d145c010bc8a8d3198e68baff458a161899c96`, branch
`agent/bittle/rgba420-final-expression`, 43U only. One authorized invocation of
the repository's unchanged `declsearch.py`; no restart or other source trial.

## Exact source context and prior coverage

Function: `TMCJPEGDEC_converterYUV420toRGBA8`, in
`libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8.c`.
Only lines 520..543 were eligible: 24 contiguous, used, uninitialized scalar or
pointer declarations. No initializer, expression, statement, scope, helper,
type, or compilation flag changed. This is a final-expression-context search,
not a new lifetime reconstruction.

The last earlier official search is recorded in `fz20.attempts.md:951..1028`:
250 evaluations ending at `(16,97)`, fuzzy `89.33987%`. Its retained body is in
`c7896c380230bd05f4f8c011166e96451c9eabfb`. The two overflow tests were subsequently
changed from `(blue | green | red)` to `(red | green | blue)`, bringing fuzzy to
`89.40523%` (`fz20.attempts.md:1702..1710`, committed in `786a2dd3`). An exact
function-text comparison proves these are the only body differences from that
earlier search-end source. No logged official search of the final expression
context was found. Every current expression, including those tests, is preserved.

SHA256 values (function text includes the definition and final newline):

- Earlier search-end function:
  `dff1079f008083bd675f82b5833db53fd6f1371598dffe54e11eb047313aa581`
- Current baseline function:
  `8c197113de5254c7d06af3d418d32af4a5888b5c8f3a93e0c4ea3e206d09b1b3`
- Current baseline entire source:
  `8ccd215e42081ccec87718048c2e40495fdfe213c642b3f0e65d6bfc2571c8d6`
- Unchanged baseline declaration block:
  `a49ed85463bb956f9473a91acc7cfbee94e7c7916ac97dea737112a19ca8cc18`
- Retained candidate function:
  `19c5fa9f0f72f32af94d32bafaed408ba7c733502f7a739304b5ad2a27f745d7`
- Retained candidate entire source:
  `b1518ffb17443d16f5cf62616c4356c8a6884ebefbeb9eaf3cca2011512e3514`

## Single bounded run

Verified the baseline hashes and all 24 declarations, reconfigured 43U with the
existing wibo wrapper and cached tool paths, rebuilt the object, and saved the
baseline source/object/report before running:

```sh
WIBO_SJIS_MISSING_IMPORTS=1 NINJA=../.venv/bin/ninja \
  PYTHONPATH=../local-tools ../.venv/bin/python -u \
  tools/decomp-assist/declsearch.py \
  libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 \
  TMCJPEGDEC_converterYUV420toRGBA8 --lines 520 543 --max-evals 783
```

The budget equals 782 unique single-swap/single-move neighbors plus baseline.
The official tool hill-climbs after improvement, so this budget is not a claim
that any full later neighborhood was exhausted.

- Actual evaluations: 783
- Trajectory: `(16,97) -> (16,96) -> (16,91) -> (16,90) -> (16,84)`
- Stop reason: configured evaluation cap; no restart
- Official function fuzzy: `89.40523% -> 90.254906%`
- Instructions: `153/153`; ctxdiff differences `97 -> 84`
- Unit fuzzy: `90.32323% -> 90.40206%`
- Exact functions: `2/13 -> 2/13`; matched code `660/6596 -> 660/6596`
- Global fuzzy: `99.721504% -> 99.72167%`
- All exact, linked, and data measures unchanged

The gain is partial decompilation progress, not an exact match or linking gain.
Retention is based on official objdiff, not the internal search score alone.

## Source, object, and build gates

A source comparison proves lines outside 520..543 are byte-identical and the
permitted block is exactly a permutation of its baseline lines. There are no
initializers, VLAs, unused/dummy variables, new register/volatile qualifiers,
assembly, or helper changes. All assignments and reads remain unchanged.

All twelve other function bodies are byte-identical to baseline. The two exact
YUV400 functions remain raw-byte identical to their originals, with exact-name
objdiff 100% and ctxdiff zero differences (76/76 and 89/89 instructions).
Source, original, and baseline objects have no allocated non-code sections.
Pool checks before search and after the full build are identical, zero strings.
The regenerated complete 1027-unit report has no function- or unit-level
regressions; the only changed function is YUV420. `git diff --check` passes.
The all-functions literal audit analyzed twelve functions with zero candidates
or errors; the unchanged setter was skipped for unequal sizes.

Full 43U `ninja` build passed, followed by `ninja build/43U/ok` with no work
pending. DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`.

## Pixel and alias validation

The repository's `jpeg_differential_audit.py` passed all 9,456 paired cases.
A separate scalar RGBA420 model also passed 7,265 vectors against candidate,
original, and saved baseline objects: 21,795 object executions.

- 384 supported-scale/tiled-origin MCU cases with constant and random samples
- 64 additional row-parity and column-residue machine-level cases
- 6,400 saturation cases: all 256 luminance bytes crossed with Cb/Cr pairs
  from `{-128,-1,0,1,127}`
- 417 halfword-aligned input/output overlap vectors, with every output store
  contained in the actual 0x184-byte conversion buffer and state kept separate

All 153 instructions in each of the three function objects were exercised.
Every non-stack byte, including guards, matched the independent model; the
interpreter also checked GPR14..GPR31, stack pointer, and LR restoration.
Additional odd-row/column-residue and overlap cases are machine-level checks,
not claims about permitted public JPEG API inputs. These bounded interpreter
tests are not formal equivalence proofs or Wii runtime validation.

## Reproduction artifacts

All local artifacts are in `build/43U/rgba420-final-expression/`:
`baseline.c`, `baseline.o`, `baseline-report.json`, `search.log`,
`candidate-report.json`, `candidate.ctx`, `final-report.json`,
`full-build.log`, `differential.log`, `audit.py`, `audit-output.txt`,
`audit-results.json`, and `literals-all.log`.

The focused audit reads the current candidate/original and saved baseline:

```sh
PYTHONPATH=../local-tools ../.venv/bin/python \
  build/43U/rgba420-final-expression/audit.py
```

No remote writes were made. The only retained source change is the authorized
declaration order in this function.

## Separately authorized finite continuation

Latest-main base: `84d0c74f`; the validated source/log change was cherry-picked
as `62fc8b19` on `agent/bittle/rgba420-local-fixedpoint`. Before this continuation,
the source SHA256 was verified as
`b1518ffb17443d16f5cf62616c4356c8a6884ebefbeb9eaf3cca2011512e3514`,
the same 24 uninitialized declarations were rechecked, and a fresh object/report
reproduced `90.254906%` with internal score `(16,84)`.

The earlier 783-evaluation run had stopped at its cap after improvements. It
did not establish exhaustion of the resulting final neighborhood; its log did
not record per-neighborhood candidate coverage. One further unchanged official
invocation was explicitly authorized, with no restart:

```sh
WIBO_SJIS_MISSING_IMPORTS=1 NINJA=../.venv/bin/ninja \
  PYTHONPATH=../local-tools ../.venv/bin/python -u \
  tools/decomp-assist/declsearch.py \
  libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 \
  TMCJPEGDEC_converterYUV420toRGBA8 --lines 520 543 --max-evals 1600
```

- Actual evaluations: 783, including the baseline
- Trajectory: `(16,84)`, no improving step
- Stop reason: natural local fixed point, before the 1,600-evaluation cap
- Coverage established: baseline plus all 782 unique immediate single-swap or
  single-move declaration neighbors, with none improving the tool's score
- The tool restored the prior validated order and rebuilt the object
- Function and unit fuzzy remain `90.254906%` and `90.40206%`
- This continuation introduced no further source change

The local fixed point is relative to the official tool's structural/exact
lexicographic score and its immediate neighborhood. It does not exhaust all
24! orders, combined moves, plateau paths, different source forms, or the
official fuzzy objective independently. There were two separately authorized
YUV420 runs totaling 1,566 evaluations; cross-run duplicate orders were not
logged, so that total must not be described as unique orders.

### Latest-main restoration and consolidated validation

After the continuation, both the source and entire object were byte-identical
to the rebuilt 90.254906% baseline. The full 43U build and `build/43U/ok` passed
again; DOL SHA1 remained
`26116613f624061ba99c8d1a299aaa6efa85670d`. A report regenerated after that full
build is identical across all 1,027 units to the continuation baseline report.
Both exact siblings remain raw-byte exact; pool remains identical and empty;
`git diff --check` passes. Final ctxdiff is 153/153 instructions, 84 differences.

The 9,456-case repository differential audit was rerun and passed. The same
independent pixel/alias model was rerun against the final candidate, original,
and this continuation's rebuilt baseline: 7,265 vectors, 21,795 object
executions, 417 overlap vectors, all 153 instructions covered in each object,
all checks passed. The earlier interpreter and API-scope limitations still apply.

Continuation evidence is in `build/43U/rgba420-local-fixedpoint/`, including
`baseline.c`, `baseline.o`, `baseline-report.json`, `search.log`, `final.ctx`,
`final-report.json`, `full-build.log`, `differential.log`, `audit.py`,
`audit-output.txt`, and `audit-results.json`.

The consolidated source gain remains `89.40523% -> 90.254906%`; exact/link/data
counts remain unchanged by the RGBA420 work. No additional search was run and
no remote writes were made.
