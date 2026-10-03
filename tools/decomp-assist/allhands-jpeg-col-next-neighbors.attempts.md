# Col fixed neighborhood after the retained y/e order

Base: `405fc376c5c2c475910065296e2d9cb566b94417` (merged #1098), 43U only.
Leaf: `wii-jpeg-col-neighbors-final`.
Branch: `agent/bittle/jpeg-col-neighbors-final`.

## Fixed scope and context

One authorized fixed-center audit around Col **92.90529%**: baseline plus all
**1,247 unique swap/move neighbors** of the same 30 contiguous uninitialized
`s32` declarations at lines **230-259**. The scratch array, `dst`, all inner
blocks, all Lumi source and every other byte remain fixed. There is no adaptive
center change, expression, initializer, assignment, type, scope, helper, compiler
flag, data or linking change.

Baseline whole source SHA256:
`76038e3b2e14c24232f9f169d1691ffa09a2a9da2c7b7e1d0df2e561bd8f84a0`.
Col function, definition through closing brace plus one newline:
`42448f5fffe9cb3fc3ef1a32b618ddf634a52ec1aba64e18c94b4bb61590df9e`.
Thirty-line block SHA256:
`5887ed810033ea47111b4419183f6797d5354af4c2e085f4fb094fc7eea516a9`.
Function context excluding this block:
`61c684b575fd84bea1a06b8c0c438f0662e51368a519a666043186a23bdd2cb6`.
Whole source context excluding this block:
`20bc2895d06f686aae8c997637f51423cf395d61b2559bf4f5ac9e20cfe2cd7c`.

Explicit cached compiler/dtk/objdiff/sjiswrap paths,
`../toolchain/wibo-release64/wibo` and `WIBO_SJIS_MISSING_IMPORTS=1` were used.
Ordinary default Ninja, explicit 43U `ok`, full official report and empty-pool
check verified the baseline before enumeration. Lumi remains **86.178986%**.

## Old d/w order and historical overlap

The previously excluded absolute `d`/`w` order belongs to the old `y`/`e`
context. Its exact source-order tuple is absent from this new neighborhood:
it differs from the new center at scalar positions 2, 19, 21 and 29. It is not
compiled or relabeled. The distinct new-context `d`/`w` swap is **snapshot 0076**,
which scores **92.89427%** and is rejected. No order is excluded from this run.

The previous recorded fixed audit overlaps exactly six current orders, indices
**0, 390, 975, 976, 1239 and 1240**, including this center. This comparison uses
exact order tuples and identical surrounding source. All six are freshly
compiled. The other 1,242 neighbors were absent from that manifest, but older
capped structural searches have no surviving per-order manifests. No global
historical-novelty or discarded-intermediate claim is made.

## Enumeration, immutable snapshots and official objective

The unchanged official tool's two generator loops yield 435 unique swaps and
841 unique moves, with 29 shared adjacent swaps: **1,247 unique neighbors**.
Duplicate source orders are removed in first-seen order. No score affects the
center or enumeration. This is not another adaptive declsearch invocation.
Official `declsearch.py` SHA256 remains
`9642fe689ee3a4d80236b5f790fdda83397214cd209c62ce07088b3f2b3726bb`.

**1,248 orders** were actually compiled with real Ninja/MWCC. Every call emitted
an MWCC object build, changed the object mtime, and had stable source within the
permitted block. The unchanged-argument recorder preserves source/object hashes,
argv, timestamps, stdout/stderr and status. There were zero failed, no-work or
unstable calls, yielding **105 distinct whole objects**. Initial baseline and
final selected-source full builds are separate validation operations.

All frozen snapshots are scored by official objdiff under a private copy of the
actual config, preserving settings, metadata and mappings. Unique unit names
point to the frozen original and each frozen candidate. No deduplication,
skipped compilation, live-object swapping or batch aggregate objective is used.
A private one-unit baseline first equals the full baseline's raw functions,
sections and measures.

Every snapshot preserves Lumi's raw bytes and 86.178986% score, function set,
exact/code/data/completion gates, and empty allocated non-code sections. There
are zero non-fuzzy gate failures. Results:

- **687 baseline ties**, including baseline
- **41 strict gains**: 27 at **92.927315%**, 14 at 92.9163%
- **520 unit-fuzzy losses**, rejected

Snapshot **0012** is the first highest-scoring admissible order and is retained.
It swaps only `done` and `a`, baseline lines 230 and 242. The 27 best-scoring
orders produce two whole-object hashes; selection is the deterministic first
best, not an additional trial. The selected and baseline internal scores both
remain `(17,290)`, while official fuzzy improves.

The full original-center neighborhood is covered: **1,247/1,247 neighbors**.
The selected winner has only **5/1,247 immediate neighbors observed** in this
run, with 1,242 unobserved. It is not claimed to be a local fixed point or global
optimum. The fixed enumeration completed; no continuation or restart followed.

## Fresh retained-source gates

The selected source was freshly rebuilt with ordinary default Ninja/report/
progress, explicit `build/43U/ok` and a full official report.

- Col: **92.90529% -> 92.927315%**, 1816/1816 bytes, 454/454 instructions
- Normalized positional ctxdiff remains **290**
- Lumi: **86.178986%**, unchanged raw body, 257/257 instructions
- Unit fuzzy: **90.47398% -> 90.488045%**
- Global fuzzy: **99.73095% -> 99.73097%**
- Unit exact functions/code remain **0/2, 0/2844**; this is a fuzzy gain
- All 1,027 units/every function checked: no regression, only Col changes
- All 1,027 whole-object hashes checked: only the IDCT object changes
- Fresh whole object is byte-identical to snapshot 0012
- Full-report IDCT raw functions/sections/measures equal the snapshot report
- Empty pool identical; zero allocated non-code bytes across all three objects
- Literal audit: both functions analyzed, zero skips/candidates/errors
- Actual config unchanged; default build/progress and 43U `ok` pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`
- `git diff --check` passes

## Integer and allocation-valid behavior checks

This only exchanges two genuinely used, uninitialized scalar declarations in
one scope. Their addresses do not escape. Every actual integer operation,
fixed-point shift, assignment, read/write expression and clamp remains unchanged.
Original/baseline/retained IDCT bodies contain no FPU instructions.

The Col exact-integer reference was rerun against the actual retained, original
and this audit's baseline objects: **8,390 vectors / 25,170 executions pass**,
with **454/454 instruction coverage in each object**. This includes 1,280
row/column/pitch/pattern combinations, 2,304 single-coefficient cases, 774 signed
DC clipping transitions, 96 unused-pitch cases and **3,936 allocation-valid
input/output overlaps**.

The reference handles the one-DC 64-byte memset, reduced two-coefficient rows,
full butterflies, signed-byte saturation and Col's fixed 8-byte output stride.
Every intermediate is checked within signed-32-bit range; all non-stack memory
and guards compare exactly. Overlap byte writes remain within the real 64-s32
input allocation. The DC shortcut captures its input before writing; other
paths consume coefficients into local scratch before output. No stack alias,
outside-object pointer or numeric tolerance is used. These bounded diagnostics
do not extend the API contract and are not formal or Wii-hardware proof.

The repository JPEG suite passes **9,456 paired cases** across 28 functions,
including 704 Lumi and 704 Col cases with full IDCT own-body coverage, preserving
GPR14-GPR31, stack pointer and LR.

## Evidence and hashes

`/tmp/jpeg-col-neighbors-final/` contains baseline/original source/object/report,
`context.json`, all `snapshots/0000.*` through `snapshots/1247.*`, enumeration/
recording/scoring scripts and output, `calls.jsonl`, copied actual/private configs,
`all-snapshot-reports.json`, `manifest.json`, `selection.json`, final full report,
build/pool/literal/ctx logs, baseline/final all-object hashes, `verify.py`,
`verification.txt`, `audit.py`, `audit-results.json`, audit output and suite log.
The manifest records every source/object hash and raw official score.

Run from the leaf:

```sh
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/jpeg-col-neighbors-final/audit.py
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/jpeg-col-neighbors-final/verify.py
```

Baseline object:
`abee5fc34b05e5ab30aca3573b64d414cf6dfedad5a3e1625020580f3990a080`.
Original object:
`d24fd161b199d694512f691398049b84d1d624d9f992de7a5206ab82daf490c8`.
Retained object:
`3aa24a3711866c03d7dab669ca9fda3762047177cafe15d59e83067f031d54b8`.
Retained source:
`f538c710722cbd51859cb7a907d76152fdcf58d986415d376c3494c2d5d8f129`.
Retained Col function text:
`274aefebe11189efb28b14f3e5e2f4d93db27fabbb34a394e839488fb7a6cfcd`.
