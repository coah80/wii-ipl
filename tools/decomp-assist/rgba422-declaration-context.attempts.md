# RGBA422 final-expression declaration search

Base `f3f295c6`; branch `agent/bittle/rgba422-declaration-context`; 43U only.
Target `TMCJPEGDEC_converterYUV422toRGBA8` in
`libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8.c`.
Only the 24 existing, used, uninitialized scalar/pointer declarations at lines
368..391 were eligible. Every initializer, expression, statement, scope, type,
helper, and source byte outside that block is unchanged.

The earlier search-end function at `c7896c380230bd05f4f8c011166e96451c9eabfb`
differs from this run's baseline only in two overflow tests, subsequently
changed from `(blue | green | red)` to `(red | green | blue)`. Function hashes:

- Earlier search-end: `75c7c6c5514ea74cf138ec599037151bc3649d1581dc890bd7919c2f0a58991a`
- Baseline: `65b045a5ed9e1b16a4bcb879821663ad4d2e354ba28d36cfd63be990ebe07899`
- Retained candidate: `f2d1efd572a63cfd47123772d01e6737fdf3165fb657170c9e1a31044ced60e1`

## One bounded official run

The unchanged repository tool was invoked once with ordinary compilation:

```sh
WIBO_SJIS_MISSING_IMPORTS=1 NINJA=../.venv/bin/ninja \
  PYTHONPATH=../local-tools ../.venv/bin/python -u \
  tools/decomp-assist/declsearch.py \
  libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 \
  TMCJPEGDEC_converterYUV422toRGBA8 --lines 368 391 --max-evals 1000
```

Trajectory `(10,84) -> (10,81) -> (10,80)`; exactly 1,000 evaluated orders.
Stopped at its cap, not at an established local fixed point. The immediate
neighborhood of 24 declarations contains 782 unique single-swap/single-move
orders. The tool restarts enumeration after improvement, and its log does not
retain each tested order; no final-neighborhood exhaustion is claimed.
No restart, body variant, alternate compiler setting, or tool modification.

## Fresh verification

- Official target fuzzy: `87.72298% -> 88.060814%`
- Unit fuzzy: `90.40206% -> 90.43238%`
- Global fuzzy: `99.72492% -> 99.72499%`
- Instructions: `148/148`; ctxdiff differences: `84 -> 80`
- Exact functions unchanged: `2/13`; matched code unchanged: `660/6596`
- All code/link/data totals unchanged; no 1,027-unit report regressions
- All twelve sibling object bodies byte-identical to the saved baseline
- Both YUV400 siblings remain objdiff 100%, raw-byte exact, and ctxdiff zero
  (`76/76` and `89/89` instructions)
- Baseline, candidate, and original contain no allocated non-code sections
- Baseline/final pools identical and empty; literal audit has zero candidates
  or errors, twelve functions analyzed, unchanged unequal-size setter skipped
- Candidate object deleted and freshly rebuilt, identical to search-end object
- Full 43U build, `build/43U/ok`, and `git diff --check` pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`

This is partial fuzzy progress, not an exact match or a linking gain. The global
completion checker remains `DECOMPLETE_FAIL` (exit 1) because the repository
still contains incomplete code/data/linking; its totals are unchanged here.

## Independent pixel and alias audit

The unchanged repository JPEG differential audit passes 9,456 paired cases.
A separate scalar 4:2:2 oracle passes 10,013 vectors against candidate, original,
and saved baseline: 30,039 object executions, covering all 148 instructions in
each object. The tested physical planes are Y[8][16], Cb[8][8], Cr[8][8] at
convBuf offsets 4/132/196. Scaled dimensions are 16/scale by 8/scale; source
row strides remain 16/8/8, with no chroma-row reuse. Coverage:

- 384 scale/tiled-origin cases with constant and random sample planes
- 64 additional machine-level row/column-residue cases
- 6,400 saturation cases: every luminance byte crossed with Cb/Cr pairs from
  `{-128,-1,0,1,127}`
- 3,165 halfword-aligned overlap cases entirely inside the actual 0x184-byte
  conversion allocation, with descriptors/state kept separate

The independent oracle models sequential memory reads and pair-local chroma
when output aliases future input. Every non-stack byte, including guards,
agrees. The interpreter checks GPR14..31, stack pointer, and LR restoration.
Full-size MCU output cannot fit wholly inside convBuf and is excluded from
that contained-overlap set. Additional residue/alias cases are machine-level
checks, not claims of public API validity. These finite integer-interpreter
tests are not formal equivalence or Wii hardware validation.

## Reproduction artifacts

`build/43U/rgba422-declaration-context/` retains baseline source/object/report,
`search.log`, search-end and rebuilt objects, candidate/final reports,
`candidate.ctx`, `exact-siblings.ctx`, `full-build.log`, pool/literal results,
status/completion results, `verify.py`, `verification.log`, `differential.log`,
`audit.py`, `audit-output.txt`, and `audit-results.json`.
Run either verification script from the worktree root with
`PYTHONPATH=../local-tools ../.venv/bin/python`.
Candidate entire-source SHA256:
`c90f879594dac677d81bfc9524fc4653d847d2a4a9fc68f3999759f1ab440b12`.
No remote writes, linking changes, or edits to previously frozen branches.

## Separately authorized finite continuation

The initial candidate was frozen as `103f816e`, with clean source and all gates
above complete. One subsequent unchanged official run was separately
authorized, with `--max-evals 1600` and the same lines 368..391. Before it ran,
the exact committed source was verified, its object was deleted/rebuilt, and
its fresh full report was byte-identical to the initial final report.
The initial source/object/report and all earlier frozen branches remain intact.

- Trajectory: `(10,80)` throughout; no improving step
- Actual evaluations: 783, including the baseline
- Stop reason: natural local fixed point, before the 1,600-evaluation cap
- Neighborhood: 276 distinct pair swaps, 529 distinct remove/insert moves,
  23 common neighbors, hence 782 distinct immediate neighbors
- Coverage established: baseline plus all 782 neighbors, with no better
  structural/positional lexicographic score
- The tool restored the exact prior validated source and rebuilt its object
- No further search was run

This is a local fixed point for the tool's score, not exhaustion of 24! orders,
plateau paths, combined moves, other source forms, or the official fuzzy
objective considered independently. The two authorized runs total 1,783
evaluations; cross-run overlaps are not recorded, so this is not a claim of
1,783 unique orders across both runs.

### Repeated final validation

Source and whole object are byte-identical to the fresh `103f816e` baseline.
The post-full-build report is byte-identical across all 1,027 units. The
consolidated source gain remains `87.72298% -> 88.060814%`, unit fuzzy
`90.40206% -> 90.43238%`, and ctxdiff `148/148` instructions with `80` differences.
All exact/link/data totals and sibling bytes remain unchanged. Both exact
siblings remain 100%/zero differences; pool is empty/identical; literal audit
again has no candidates/errors and the same unequal-size setter skip.
Full 43U build, `build/43U/ok`, and `git diff --check` pass; DOL SHA1 remains
`26116613f624061ba99c8d1a299aaa6efa85670d`. Global completion remains incomplete.

The unchanged focused oracle was rerun against candidate/original and this
continuation's freshly rebuilt baseline: all 10,013 vectors / 30,039 executions
pass, including 3,165 overlaps and all 148 instructions in all three objects.
The repository differential audit again passes all 9,456 paired cases.
The scope and interpreter limitations above still apply.

Continuation artifacts are in `build/43U/rgba422-local-fixedpoint/`:
baseline source/object/report, `search.log`, `neighborhood-size.json`,
`final-report.json`, `final.ctx`, exact/pool/literal/build/status/completion
results, `verify.py`, `verification.log`, `audit.py`, `audit-output.txt`,
`audit-results.json`, and `differential.log`.
The full source SHA256 remains
`c90f879594dac677d81bfc9524fc4653d847d2a4a9fc68f3999759f1ab440b12`.
