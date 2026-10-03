# RGB565411 edge grouped offset declarations

Base: `17130b4b` (merged RGB565411 normal improvement), 43U only.
Branch: `agent/bittle/jpeg-rgb411edge-triple`.
Target: `TMCJPEGDEC_converterYUV411toRGB565edge` in
`libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565.c`.

## Scope and historical coverage

The only source change splits the existing line 287 declaration in place and
orders its three uninitialized `s32` scalars as redOffset, blueOffset,
greenOffset. All assignments, initializers, expressions, types, scopes, helpers,
assertions and traversal remain unchanged. There are no new locals.

These are the three chroma contributions shared by each four-pixel group. The
existing x-alignment assertion guarantees entry at a chroma-group boundary.
The existing branch assigns all three offsets, in its original red/green/blue
assignment order, before the first pixel reads them. No address escapes.
Declaration order changes no arithmetic or observation order.

Current original function text SHA256 (definition through closing brace and
newline):
`ed020f92da0ea0584d9d7fc4ecbcad9f11f8f7621a8829cfcd9fabf135361207`.
This exact function hash also occurs at `180e620c`, `be7ded2f`, `6ec48a1b`
and `cdc22045`; this is not a newly changed expression context.

Historical round4 lines 1538-1544 establish the signed chroma-pointer context
and 95.37736% baseline. Round5 lines 251, 302-306 and 698 record endpoint,
output-pointer and row-template probes. The tex1 log at lines 137-143, 243-246,
346-352 and 520-525 records structural, input-type and lifetime trials. Its
statement that declaration permutations were inert provides no individual
order manifest. The grouped-declaration inventory also cited wider split
searches containing these offsets, but did not establish exhaustive coverage
of the current internal triple with every surrounding declaration fixed.

This trial closes that specific finite measurement gap. Possible historical
order overlap is acknowledged; no claim that these six orders were never
compiled before is made. No wider declaration search or continuation occurred.

## Bounded experiment

1. Preserve prior branch refs; create a fresh branch at merged `17130b4b`.
2. Copy the parent-verified idle main cache, configure the approved local
   wrapper/tool overrides, and run ordinary default Ninja, explicit 43U `ok`,
   and a fresh full official objdiff report.
3. Compile the same-order red/green/blue split first. The entire object and
   full 1027-unit official report are exactly identical to baseline. This
   prerequisite passes before any permutation is measured.
4. Enumerate exactly the six permutations of these three existing declarations.
   Each source is rebuilt by ordinary Ninja with unchanged compiler arguments;
   each call emits the MWCC object-build line and updates the object mtime.
   Exact source stability across each compile is checked. Save each source,
   object, SHA256, build output and fresh official full report.
5. Select the first highest official-fuzzy order passing the sibling/code/data
   gates; then freshly rebuild the selected source with default Ninja and the
   explicit 43U `ok` target. No additional variant is tested.

The independent same-order neutrality compile is separate from the six
permutation compiles. The final selected-source rebuild is validation, not an
additional searched order. No compiler call is suppressed or replaced.

| Order | Function fuzzy | Unit fuzzy | Sibling/exact/code/data gates |
| --- | ---: | ---: | --- |
| red, green, blue | 95.37736 | 96.84735 | pass |
| red, blue, green | 95.42453 | 96.850586 | pass; retained |
| green, red, blue | 95.37736 | 96.84735 | pass |
| green, blue, red | 95.42453 | 96.850586 | pass |
| blue, red, green | 95.42453 | 96.850586 | pass |
| blue, green, red | 95.42453 | 96.850586 | pass |

All six raw full reports were compared against baseline. All twelve sibling
function records and raw bodies remain unchanged in every permutation; all
seven existing exact functions remain raw-byte exact and at 100%. Exact code,
data and completion measures do not decrease. No other unit changes. The
six-order space is exhausted in this exact surrounding source context; this
says nothing about broader neighborhoods or eventual exact matching.

## Fresh selected-source gates

- Function: **95.37736% -> 95.42453%**, 424/424 bytes, 106/106 instructions
- Normalized positional ctxdiff: **62 -> 61**
- Unit fuzzy: **96.84735% -> 96.850586%**
- Global fuzzy: **99.727745% -> 99.72777%**
- Exact functions: **7/13**, exact code **2648/6184**, unchanged
- Merged RGB565411 normal gain remains **90.89862%**, raw body unchanged
- All 1027 units and every reported function checked: no regressions
- Fresh selected whole object equals saved permutation-1 object exactly
- Fresh final full report equals saved permutation-1 full report exactly
- Seven exact functions independently checked against original bytes and
  normalized disassembly: ctxdiff 0 for each
- Baseline, candidate and original have zero allocated non-code bytes; empty
  pool identical. No symbol/data/relocation/configuration change
- Literal audit: 12 functions analyzed, zero candidates/errors; setter skipped
  because its source/target sizes differ, as at baseline
- Ordinary default build/progress plus explicit `build/43U/ok` pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`
- `git diff --check` passes

## Behavior and ordering

The existing `jpeg_differential_audit.py` passes **9,456 paired cases** across
28 JPEG functions, including preserved GPR14-GPR31, stack pointer and LR.

A focused independent scalar RGB565411-edge model checks **12,689 vectors**
against candidate, original and saved baseline objects, for **38,067 object
executions**:

- 1,257 vectors span every edge width and height at supported scales 1/2/4/8,
  including zero extents, partial four-pixel chroma groups, aligned x origins,
  tiled boundaries and differing row residues
- 256 vectors exercise both dimension-selection branches independently with
  random and constant samples
- 6,400 vectors cover all 256 luminance values for all pairs of signed chroma
  values in {-128, -1, 0, 1, 127}, including saturation boundaries and partial
  groups across rows
- 4,776 overlap vectors cover all fitting even destination bases for the
  specified full/partial groups, pitches and row starts; every store remains
  within the actual 0x184-byte conversion-buffer allocation

All non-stack bytes, including guards, agree with the sequential scalar model.
All three objects reach **106/106 instructions**. The overlap oracle reads from
its evolving buffer, preserving read/write observation order; state and
descriptor objects remain separate. These overlap arrangements are additional
machine-level diagnostics, not a new public API alias contract. Input samples
and bounded dimensions keep intermediate arithmetic within signed integer
range. The converter contains only integer arithmetic; no floating-point
reassociation is involved. The unchanged assignment/evaluation order is also
verified by the exact source replacement check.

This is bounded execution in the repository's PPC integer interpreter, not a
formal proof or a Wii hardware run.

## Preserved evidence

`/tmp/jpeg-rgb411edge-triple/` contains baseline source/object/report, frozen
original object, `split-neutral.*`, `permutation-0.*` through
`permutation-5.*`, `manifest.json`, `selection.json`, `trial.py`,
`trial-output.txt`, build logs, final report, `verify.py`, `verification.txt`,
`candidate.ctx`, literal output, `audit.py`, `audit-results.json`, audit output
and the differential result log. All six source/object snapshots are retained.

Baseline whole object SHA256:
`fec999a214f95c1f348632de53cac7672c15d70cbaea9b3566d7a7383a4e1b70`.
Retained whole object SHA256:
`f82e514864af9c85e1857e2fd59bfd976deb0aba1f651662b322730ced490ad6`.
Retained source SHA256:
`8fb0c89b7b0bcb7b0467ca1be3dfcdb70dfa43b1ec085d926d028e156470749a`.
Retained function-text SHA256:
`fff97c26d8afa6d734a253ae3b9aeaa648b3a28b682c0ef98fb8aeb7b07bb5ca`.
