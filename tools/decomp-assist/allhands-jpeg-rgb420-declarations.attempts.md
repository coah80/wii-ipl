# RGB565420 normal bounded declaration search

Base: `f3f295c6`; branch: `agent/bittle/jpeg-rgb420-declarations`; 43U only.
The closed RGB565411, RGB565422 and RGB565420-edge contexts and all prior
branches remain preserved. No RGBA8 source was changed.

## Context and eligibility

Function: `TMCJPEGDEC_converterYUV420toRGB565` in
`libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565.c`.
The verified block at lines 474–497 contains exactly 24 existing, genuinely
used, uninitialized scalar/pointer declarations. The only retained change is
within this block. Every type, initializer, body expression, statement order,
scope, helper, clamp, packing operation and cursor step is unchanged.

Entry function-text SHA256, definition through closing brace plus newline:
`cb8768325af825089c3ac634b533d972d902158c9481ccdee269ea08ccd80308`.
The full function is identical at `cdc22045`, `6ec48a1b`, `be7ded2f` and
`f3f295c6`. The baseline object was rebuilt and officially scored 94.60993.

`jpeg-round4-attempts.md:749-762` records a 400-swap capped search with eleven
improvements ending at this score. That record does not establish exhaustion
of the final neighborhood. Later individual structural/template trials do not
establish an official fixed point. Only this normal converter was authorized
for the new run.

## Single authorized run and stop

The unchanged official tool was invoked exactly once:

```sh
WIBO_SJIS_MISSING_IMPORTS=1 NINJA=../.venv/bin/ninja PYTHONPATH=../local-tools \
  ../.venv/bin/python -u tools/decomp-assist/declsearch.py \
  libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565 \
  TMCJPEGDEC_converterYUV420toRGB565 --lines 474 497 --max-evals 1000
```

Tool SHA256:
`9642fe689ee3a4d80236b5f790fdda83397214cd209c62ce07088b3f2b3726bb`.
Each evaluation used the ordinary Ninja/MWCC object build with the approved
wibo wrapper and `WIBO_SJIS_MISSING_IMPORTS=1`.

Trajectory: `(6,86)` -> `(6,84)` -> `(6,81)`.
The tool stopped at 1,000 cached order evaluations, its authorized cap.
It did not establish a local fixed point. For 24 declarations, each fixed
order has 782 distinct immediate neighbors: 276 swaps + 529 distinct moves
minus 23 overlaps. The center changed twice and per-order coverage was not
logged, so exact coverage of the final neighborhood is unknown. No automatic
continuation, custom search or intermediate-order recovery was performed.

## Fresh official result

- Function fuzzy: 94.60993 -> 95.17731
- Unit fuzzy: 96.753555 -> 96.805305
- Instructions: 141/141; ctxdiff differences: 86 -> 81
- Exact functions unchanged at 7/13; matched code unchanged at 2648/6184 bytes
- All twelve sibling function bodies byte-identical to the saved baseline
- All seven prior exact siblings retain exact-name objdiff 100, raw-byte
  equality and ctxdiff zero
- No allocated non-code sections in baseline, candidate or original objects
- Global fuzzy on this base: 99.72492 -> 99.72503
- All 1,027 units and every function score checked: no regression; only the
  owned RGB565 unit changes

This is partial fuzzy progress, not exact completion or a linking change.

## Gates and differential behavior

Full 43U build and `build/43U/ok` pass. DOL SHA1:
`26116613f624061ba99c8d1a299aaa6efa85670d`.
Pool checks before search and after the final build: identical and empty.
Literal audit: twelve functions analyzed, no candidates/errors; unchanged
setter skipped for unequal function sizes. `git diff --check` passes.

The unchanged repository `jpeg_differential_audit.py` passes all 9,456 paired
calls. A separate scalar RGB565420 model passes 7,280 vectors against the
candidate, original and saved baseline, totaling 21,840 object executions:

- 384 supported-scale/MCU-origin cases with random and constant samples
- 64 additional tiled-row and column-residue machine-level cases
- 6,400 saturation cases: every luminance byte crossed with signed Cb/Cr
  values from {-128, -1, 0, 1, 127}
- 432 halfword-aligned input/output overlap cases whose stores remain entirely
  within the actual 0x184-byte conversion buffer; descriptor/state stay separate

The independent reference reads and writes the overlapping buffer sequentially.
Every non-stack byte, including guards, matches. The interpreter checks SP, LR
and GPR14–GPR31 restoration. All 141 instructions in each of the three objects
were exercised. Arithmetic is integer-only; there are no floating-point
operations or newly introduced overflow cases. Additional residue and overlap
cases are machine-level checks, not claims about permitted public API inputs.
These bounded tests are not formal equivalence proofs or Wii runtime tests;
the repository interpreter's existing unsupported-instruction/device limits
continue to apply.

## Frozen evidence

Final function SHA256:
`c8c40679d9d2fd3ce5841870fc4098c88a371a7e9082d41242ca6c8655507aee`.
Final entire source SHA256:
`4216dc6aa323936fe4cc747c05d37bdce37d9a7c3861021c47920d2cfc0e4b3d`.
Local evidence is preserved in `/tmp/jpeg-rgb420-declarations/`: baseline
source/object/report, candidate and final reports, search-output.txt,
candidate.ctx, full-build.log, literal-all.txt, verify.py, verification.txt,
differential.log, audit.py, audit-output.txt and audit-results.json.

The focused scalar audit can be rerun from this worktree with:

```sh
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/jpeg-rgb420-declarations/audit.py
```

No remote writes, configuration/header changes or linking changes are retained.

## Separately authorized continuation on latest base

The initial candidate `b7e74104` was preserved on its original branch and
cherry-picked cleanly as `41f83f91` onto latest main `dc3eede8` in
`agent/bittle/jpeg-rgb420-fixedpoint`. The owned object and `build/43U/ok` target were rebuilt before
search. Both recorded source hashes and official function fuzzy 95.17731 were
reverified. The same 24 uninitialized declarations at lines 474–497 were used.

Exactly one further unchanged official invocation used `--max-evals 1600`,
with all other command arguments and build settings as above. It reported:

```text
start (6, 81)
best (6, 81) after 783 builds; source restored; best order was:
```

There were no improving steps. This run stopped at a local fixed point before
its cap: one baseline and all 782 distinct immediate single-swap/single-move
neighbors were evaluated. Because the center never changed, that coverage is
established directly by the tool's enumeration and 783-evaluation count.
The fixed point concerns the tool's structural/positional comparator; it does
not exhaust all 24! orders, plateau paths or the official fuzzy objective.
There were two separately authorized runs totaling 1,783 evaluations; overlap
between the runs was not logged, so this is not a unique-order total.

The prior 95.17731 candidate remains the final source. Source and entire object
are byte-identical to the rebuilt continuation baseline. The initial regenerated report matched the entry report, but both contained a
stale unrelated NonMatching object; the corrected full-report comparison below
supersedes that interim result. All seven exact siblings retain raw
byte equality and ctxdiff zero; all twelve siblings remain unchanged. Pool
remains identical and empty, with zero allocated non-code bytes. Literal audit
again reports no candidates/errors. The DOL build target passes; DOL
SHA1 remains `26116613f624061ba99c8d1a299aaa6efa85670d`.
The source, compiler settings and converter instructions are unchanged from
the candidate that passed the 9,456-case paired audit and 7,280-vector pixel
model above; those behavior tests were not repeated for this neutral search.

Continuation evidence is preserved in `/tmp/jpeg-rgb420-fixedpoint/`, including
baseline source/object/report, baseline-build.log, search-output.txt,
final-report.json, full-build.log, literal-all.txt, verify.py and
verification.txt. No third run, restart, further source change or remote write
was performed. The source gain and this evidence are frozen for parent review.


### Corrected full progress gate

Before final handoff, the continuation report was found to retain the old
RGBA422 NonMatching object: its cached score was 87.72298 instead of the
merged 88.060814. `build/43U/ok` verifies the DOL but does not refresh every
NonMatching object. This did not affect the rebuilt owned RGB565 object,
source hashes, search scores, fixed-point count or pixel-model evidence.

Ran the default `WIBO_SJIS_MISSING_IMPORTS=1 ../.venv/bin/ninja` progress build
and then `build/43U/ok`, and regenerated the official final report. All source
objects are now current. The RGB565 object is byte-identical to the committed
95.17731 continuation baseline, and the DOL hash still passes. Compared with
the freshly built main report at exact commit
`dc3eede8d3781762e566f72e2ae9aa0f49dbaf69`, only the RGB565 unit differs across
all 1,027 units; no function, exact/code/data or linking metric regresses.
RGBA422's merged 88.060814 result is preserved. The corrected latest-base
global fuzzy comparison is 99.72499 -> 99.72510.

In the continuation evidence directory, `latest-main-report.json` is the
verified dc3eede8 comparison report, `final-report.json` is the corrected
full candidate report, and `full-progress-build.log` records the default
full build. `verify.py` and `verification.txt` use that current-main comparison.
The original `baseline-report.json`, `pre-progress-report.json` and
`pre-progress-verification.txt` are preserved as explicitly stale interim
evidence and must not be used for the latest-base aggregate comparison.
