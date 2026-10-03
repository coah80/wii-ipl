# RGB565420 edge bounded declaration search

Base: `32be36cb4e57bdaf05af9bbccc0a4ff6a63cb1aa`; branch
`agent/bittle/jpeg-edge-declaration-search`; 43U only.

The function at entry exactly matched the merged pixel-lifetime candidate
from #1061. Its function-text SHA256 was
`b0117318407c1fb445baef7534c6f0d28908412e0e8c26bc113efc4ed956f57f`.
The contiguous leading block at source lines 566..585 contains twenty existing
uninitialized scalar/pointer declarations. Initialized pixel locals at 620..623
were excluded. Earlier tex1 coverage used the older function-wide RGB locals;
the #1061 evidence explicitly records no declaration search on its new body.

## Authorized search and stop

Ran the unchanged repository tool exactly once:

```sh
WIBO_SJIS_MISSING_IMPORTS=1 NINJA=../.venv/bin/ninja \
  PYTHONPATH=../local-tools ../.venv/bin/python \
  tools/decomp-assist/declsearch.py \
  libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565 \
  TMCJPEGDEC_converterYUV420toRGB565edge --lines 566 585 --max-evals 32
```

Structural/positional trajectory: `(4,65)` -> `(4,58)`.
The tool stopped at 32 distinct scored orders, then rebuilt its retained order.
This was the finite evaluation cap, not exhaustion of the final neighborhood.
There was no custom search, extra variant, helper edit, or initializer move.

The sole retained source change swaps the leading declarations of `column`
(s32) and `crValue` (s8). Both are genuinely used uninitialized scalar locals.
All expression tokens, initialization statements, scopes, helper bodies,
clamps, arithmetic, and pointer steps remain byte-for-byte unchanged.
There are no floating-point operations in this converter.

## Fresh official result

- Function fuzzy: 95.570175 -> 95.96491%
- Instruction count: 114/114; ctxdiff differences: 65 -> 58
- Unit fuzzy: 96.58538 -> 96.61449%
- Exact remains 7/13; matched code remains 2648/6184 bytes
- No allocated non-code sections; data remains 100%
- Global fuzzy: 99.71971 -> 99.71977%; all exact/link/data totals unchanged
- Full report: zero function/unit regressions; only this unit changes
- Only this function's bytes change; all twelve sibling bodies are identical
  to the saved pre-search object
- All seven existing exact siblings remain objdiff 100% and ctxdiff zero

This is partial fuzzy progress, not an exact or linking result.

## Gates

Full 43U build and `ninja build/43U/ok`: PASS.
DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`.
Pool before and after: identical, zero strings. `git diff --check`: PASS.
Literal audit: no candidates/errors; twelve functions analyzed, unchanged
setter skipped for unequal function sizes.

The unchanged prior pixel oracle passed 8,721 vectors / 26,163 object executions
against the candidate, original, and its saved pre-#1061 baseline: 808 edge-size
cases, 256 dimension-branch cases, 6,400 saturation cases, and 1,257 aligned
input/output overlaps wholly inside the actual conversion buffer. Every one of
114 instructions was exercised in each object. The interpreter checks every
non-stack byte, LR, stack pointer, and preserved GPRs. Valid rows exercise both
column parities; odd input x remains outside the existing asserted contract.
The prior oracle's bounded-input and interpreter limitations still apply;
this is not formal equivalence or Wii runtime validation.

## Unsearched neighborhood, read-only count

For twenty declarations, the retained order has:

- 190 distinct pair-swap neighbors
- 361 distinct remove/insert move neighbors
- 19 neighbors common to both sets
- 532 distinct neighbors in their union

The tool's deterministic enumeration reaches the sole improvement at evaluation
27: swapping zero-based positions 1 and 8. Five new final-order neighbors are
then scored before reaching 32. The initial order is also a final-order neighbor
(the inverse swap), giving 6 covered and 526 unscored final-order neighbors.
This count was reproduced without compiling any additional order. It is inferred
from the unchanged tool, its logged single improvement and final 32-build count.
A fresh official run lacks the prior cache and would repeat those six neighbors;
533 total evaluations can cover one fixed order plus its entire neighborhood if
no intervening improvement causes the tool to restart from another order.
No continuation run was performed.

## Evidence

`/tmp/jpeg-edge-declaration-search/` contains `search-output.txt`, baseline and
candidate reports, the saved pre-search object, `candidate.ctx`, `full-build.log`,
`verification.txt`, `audit-output.txt`, `audit-results.json`, and `neighborhood.json`.
The read-only `verify.py` asserts the source consists of exactly the two-line
swap and compares reports, allocated sections, and sibling object bytes.
The prior oracle remains `/tmp/jpeg-pixel-lifetime/audit.py`, unchanged.
No remote writes, link flags, shared headers, or tool changes.

## Separately authorized 533-evaluation continuation

The preceding 32-evaluation candidate was preserved on its own branch. A new
branch, `agent/bittle/jpeg-edge-order-finish`, starts at base `32be36cb` with that
candidate cherry-picked as `81df2b4e26f36c1b63a74840754ea720dc4f1c72`.
The 95.96491% baseline was rebuilt and freshly measured before proceeding.

Ran the unchanged official command above exactly once more, changing only
`--max-evals 32` to `--max-evals 533`. The same twenty leading uninitialized
declarations remained the complete writable search range. All source outside
that block was checked byte-for-byte against the entry source, and the block's
declaration multiset was unchanged. No initialized local, scope, expression,
helper, type, array, or evaluation-order edit occurred.

The structural/positional trajectory was:

```text
(4,58) -> (4,57) -> (4,56) -> (4,55) -> (4,52) -> (4,49)
       -> (4,48) -> (4,44) -> (4,43) -> (4,39) -> (4,35)
```

The tool stopped after 533 distinct scored orders and rebuilt its retained
order. The evaluation cap stopped this run; a local fixed point was not reached.
There was no extra search or source variant afterward.

### Final measured result and repeated gates

- Function fuzzy: 95.96491 -> 97.850876%; compared with merged #1061: 95.570175%
- Unit fuzzy: 96.61449 -> 96.753555%; compared with merged #1061: 96.58538%
- 114/114 instructions; ctxdiff differences: 58 -> 35
- Global fuzzy on this branch: 99.71977 -> 99.72007%
- Exact remains 7/13; matched code 2648/6184 bytes; link/data totals unchanged
- Zero full-report function/unit regressions; only this unit changes
- Only the targeted function body changes; all twelve siblings remain
  byte-identical to the saved 95.96491% entry object
- All seven exact siblings remain objdiff 100% and ctxdiff zero
- Empty allocated non-code sections and empty string pool unchanged
- Full 43U build, `ninja build/43U/ok`, and `git diff --check`: PASS
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`
- Literal audit: no candidates/errors; twelve functions analyzed; unchanged
  setter skipped for unequal size
- The unchanged prior oracle again passes all 8,721 vectors / 26,163 object
  executions with complete 114-instruction coverage in all three objects

The same bounded-oracle limitations listed above apply. This is partial fuzzy
progress and does not add an exact function or change linking.

Final source SHA256:
`3b0ed19e076c09dfbcd841fc63b79e48ef0ae84703bd4148fdac56c8cfd2c6d3`.

### Final neighborhood coverage

The new final order again has 532 distinct one-swap/one-move neighbors. The
official tool restarts its neighborhood after an improvement; ten improvements
therefore moved the center during the finite run.

An exact final-neighbor coverage count is unavailable: the unchanged tool logs
score improvements and its final declaration order, but does not retain the
identity of each intermediate tested order. No identities were invented.
Read-only enumeration establishes these conservative bounds:

- The final order itself, the starting order, and the first tested swap are
  three scored orders outside the final neighbor set
- The last improving parent is a scored final-order neighbor
- Between 1 and 530 of 532 final neighbors were scored in this continuation
- At least 2 final neighbors remain unscored; the neighborhood is not exhausted

These bounds concern the continuation, not a claim of cumulative coverage
across other runs. No further continuation was performed or implied.

### Continuation artifacts

`/tmp/jpeg-edge-order-finish/` contains the complete score trajectory, freshly
rebuilt baseline report/object/source, candidate report, `candidate.ctx`, full
build log, independent verification output, unchanged-oracle output/results,
and read-only neighborhood calculation results. Its `verify.py` checks that
only the leading-declaration order changes, then checks full reports, exact
siblings, all sibling bytes and allocated non-code sections.

The separately preserved 32-evaluation branch is unchanged. The final source
and this combined evidence log are ready for independent review as one PR.
No remote writes occurred.

## Final authorized fixed-point check

A final separate branch, `agent/bittle/jpeg-edge-order-fixedpoint`, preserves
the validated source on current main `a4d145c0` through cherry-picked commits
`8b2366be` and `a4f3d380`. The 97.850876% baseline was rebuilt and freshly
measured before the search. Its source is identical to the preceding frozen
candidate `7423b762`.

Ran the same unchanged official command once with `--max-evals 1200`, still
restricted to source lines 566..585 and the same twenty uninitialized
scalar/pointer declarations. No other source region was writable by this run.

Actual result:

```text
start (4, 35)
best (4, 35) after 533 builds; source restored
```

There were zero improvements. The run stopped at a local fixed point before
its 1200-evaluation cap. Its 533 scored orders comprise the baseline plus all
532 distinct pair-swap/remove-insert neighbors of that baseline. The center
never moved, so complete final-neighborhood coverage is established directly
from the unchanged deterministic tool and its count. No inferred intermediate
permutations are needed.

This is a fixed point under declsearch's structural/positional comparator.
Official objdiff fuzzy was measured at entry and exit, both 97.850876%; the
tool does not measure official fuzzy for each intermediate neighbor. No claim
of globally optimal fuzzy score or exhaustion of multi-step permutations is made.
No additional run followed the fixed point.

### Retained-source verification on current main

The complete source and whole RGB565 object are byte-identical to the freshly
rebuilt 97.850876% entry baseline. The complete 1027-unit report is identical
before and after the final full rebuild, with zero function/unit regressions.

- Function fuzzy remains 97.850876%; unit fuzzy remains 96.753555%
- 114/114 instructions, 35 ctxdiff differences; exact remains 7/13
- All seven exact siblings remain objdiff 100% and ctxdiff zero
- Allocated non-code sections remain empty; pool identical, zero strings
- Full 43U build, `ninja build/43U/ok`, and `git diff --check`: PASS
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`
- Literal audit: no candidates/errors; twelve functions analyzed, unchanged
  setter skipped for unequal size
- Unchanged pixel oracle: all 8,721 vectors / 26,163 object executions pass,
  with full 114-instruction coverage and the previously documented limitations
- Current-base global fuzzy: 99.72187%; this neutral search changes no totals

Final evidence is in `/tmp/jpeg-edge-order-fixedpoint/`: baseline report,
object and source; full trajectory; candidate report; full build log; verification
output; pixel-oracle output/results; and exact neighborhood counts. Source SHA256
remains `3b0ed19e076c09dfbcd841fc63b79e48ef0ae84703bd4148fdac56c8cfd2c6d3`.
Only this evidence append is new in the final check; the best source is retained.
No remote writes, new variants, helper changes, or initialized-local edits.
