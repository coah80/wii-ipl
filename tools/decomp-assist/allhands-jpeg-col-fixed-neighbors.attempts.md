# Col fixed immediate-neighborhood audit

Base: `02d634d30bdf6e5acd249b5c6b1aa17c7551d646`, 43U only.
Leaf: `wii-jpeg-col-neighbors`.
Branch: `agent/bittle/jpeg-col-fixed-neighbors`.

## Scope and historical gap

The authorized audit holds Col's **92.47577%** baseline as a fixed center and
compiles baseline plus **1,246 unique swap/move neighbors**, excluding the
previously rejected `d`/`w` declaration swap. Only the 30 contiguous,
uninitialized `s32` declarations at lines **230-259**, `done` through `e`,
may move. The scratch array, `dst` pointer, all inner blocks, all Lumi source
and every other byte stay fixed. No initializer, expression, assignment, type,
scope, helper, compiler flag, data or linking change is involved.

Historical records do not establish complete current-center official-fuzzy
coverage. `jpeg-round4-attempts.md:480-486` records 500 distinct swaps with four
retained structural improvements, but no per-order source/object/official-score
manifest or final-neighborhood exhaustion. Its retained Col function is identical
to current Col. `four-leaves-r9.attempts.md:105` records 180 builds over 32
leading declarations, including the array and pointer, ranked `(18,290)` to
`(16,287)`. Its initial baseline Col function is identical, but the actual
search snapshots/context are unavailable. `four-leaves-r11.attempts.md:128`
records 160 builds on a different clamp-helper context, `(16,276)` to `(14,273)`.
That context is not imported. These intermediate artifacts did not survive the
workspace reset. Exact overlap with this new enumeration cannot be reconstructed;
no novel-order or previously-discarded-gain claim is made.

The separately measured `d`/`w` swap at the unchanged Col function context
regressed **92.47577% -> 92.32819%** and remains closed. That order is explicitly
excluded, not freshly compiled or rescored in this audit.

## Pinned context and tools

Baseline whole source SHA256:
`e0f98086d67cd3bfedb640a3cacd0801428d929da4ac2397ef61754e2b0e4002`.
Col function text, definition through closing brace plus one newline:
`703e8856cb8549914189ba88fc15b94ed58dceca3e0e711e571f505a94e91c4b`.
Thirty-line block SHA256:
`3c199cfbac654d2216b34a69c709c3acc1985ea2349b01550e87c256a1a8533d`.
Col function context with this block omitted:
`61c684b575fd84bea1a06b8c0c438f0662e51368a519a666043186a23bdd2cb6`.
Whole source context with this block omitted:
`20bc2895d06f686aae8c997637f51423cf395d61b2559bf4f5ac9e20cfe2cd7c`.

The fresh leaf used explicit cached compiler/dtk/objdiff/sjiswrap paths,
`../toolchain/wibo-release64/wibo` and `WIBO_SJIS_MISSING_IMPORTS=1`.
Ordinary default Ninja, explicit 43U `ok`, full official report and empty-pool
check established the baseline. Lumi was **86.178986%** and remained frozen.
The unchanged official `declsearch.py` SHA256 is
`9642fe689ee3a4d80236b5f790fdda83397214cd209c62ce07088b3f2b3726bb`.

## Fixed enumeration and official scores

The official tool's same two neighbor generators are used: 435 unique swaps and
841 unique moves with 29 shared adjacent swaps yield 1,247 distinct neighbors.
After removing the closed `d`/`w` order (scalar indices 2 and 21), **1,246
neighbors plus baseline = 1,247 orders** are compiled. Duplicate source orders
are removed in first-seen order. The center never changes and scores do not
influence which orders compile. This is not an adaptive declsearch invocation.

All 1,247 calls invoke ordinary real Ninja unchanged and actually compile with
MWCC. The recorder captures source/object hashes, source stability, allowed-range
membership, object mtimes, stdout/stderr, argv and status. Every call emits the
MWCC object build and changes the object mtime. There are zero failed/no-work/
unstable calls and **117 distinct whole objects**. Initial baseline and final
selected-source builds are separate validation operations.

Every frozen object receives official objdiff scoring under a private copy of
the actual project config, preserving settings, metadata and mappings. Unique
unit names point to the frozen original and each candidate. No deduplication,
skipped compilation, live-object swapping or artificial batch aggregate objective
is used. The private one-unit baseline first matches the full baseline's raw
functions, sections and measures.

Every snapshot preserves Lumi's raw bytes and 86.178986% score, function set,
existing exact/code/data/completion gates and empty allocated non-code sections.
There are zero non-fuzzy gate failures. Of 1,247 orders, **628 tie baseline**,
**two strictly improve**, and **617 lose unit fuzzy**. The improving snapshots
are 0368 at 92.81057% and **0389 at 92.90529%**. Snapshot 0389 is the unique
highest admissible official score and is retained. It only swaps the existing
`y` and `e` declarations, baseline lines 249 and 259.

## Stop and coverage

The authorized fixed set completed: **1,246/1,247 neighbors freshly compiled**,
with the documented `d`/`w` order excluded separately. The full neighborhood is
not claimed to have been freshly compiled. The retained new winner has only
**5/1,247 neighbors observed** in this run and 1,242 unobserved. It is not claimed
to be a fixed point or global optimum. No adaptive step, restart, continuation
or additional source variant was performed.

## Fresh selected-source gates

The selected source was freshly rebuilt with default Ninja/report/progress,
explicit `build/43U/ok` and a full official report.

- Col: **92.47577% -> 92.90529%**, 1816/1816 bytes, 454/454 instructions
- Positional ctxdiff remains **290**; internal tool score `(18,290) -> (17,290)`
- Lumi remains **86.178986%**, 257/257 instructions and byte-identical raw body
- Unit fuzzy: **90.19972% -> 90.47398%**
- Global fuzzy: **99.72896% -> 99.72922%**
- Unit exact functions/code remain **0/2, 0/2844**; this is a fuzzy gain
- All 1,027 units and every function checked: no regression, only Col changes
- All 1,027 whole-object hashes checked: only the IDCT object changes
- Fresh whole object equals saved snapshot 0389 byte-for-byte
- Full-report IDCT raw functions/sections/measures equal the snapshot report
- Empty pool identical; zero allocated non-code bytes in original/baseline/candidate
- Literal audit: two analyzed functions, zero skips, candidates or errors
- Actual report config unchanged; default build/progress and 43U `ok` pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`
- `git diff --check` passes

## Integer semantics and behavior

Only two genuinely used, uninitialized scalar declarations exchange order within
the same scope. Their addresses do not escape. All assignments, read/write
expressions, operation dependencies, fixed-point shifts, clamps, helpers and
Lumi source remain unchanged. The inspected original/baseline/selected IDCT
bodies contain no FPU instructions.

The exact-integer scalar Col reference was run against original, saved baseline
and the freshly rebuilt retained object: **8,390 vectors / 25,170 executions
pass**, with **454/454 instruction coverage in each object**:

- 1,280 dimension/pitch/pattern cases, including all row/column modes, DC, sparse,
  dense and alternating coefficients
- 2,304 single-coefficient position/scaling cases
- 774 DC signed-clipping transitions and adjacent fixed-point values
- 96 cases explicitly checking the unused pitch argument across 0 through 65535
- 3,936 input/output overlap cases wholly inside the actual 64-s32 input allocation

The reference handles the one-DC contiguous 64-byte memset, reduced two-coefficient
row path, general butterflies and signed-byte saturation. Col writes an 8x8
contiguous byte block regardless of pitch. Every intermediate arithmetic result
is checked within signed-32-bit range; every non-stack memory byte and guard
agrees exactly. The DC shortcut captures its input before writing; other paths
consume coefficients into the local scratch array before output. Aliases use
character stores within the real input object, without stack aliasing or
outside-object pointers. These bounded arrangements are machine-level diagnostics,
not an expanded API contract or a formal/hardware proof. No numeric tolerance
or floating-point approximation is used.

The repository JPEG suite independently passes **9,456 paired cases** across
28 functions, including 704 Lumi and 704 Col cases with full IDCT own-body
coverage, preserving GPR14-GPR31, stack pointer and LR.

## Preserved evidence and hashes

`/tmp/jpeg-col-neighbors/` contains `context.json`, original/baseline source/
object/report, `snapshots/0000.*` through `snapshots/1246.*`, enumeration and
recorder scripts/output, `calls.jsonl`, copied actual/private configs,
`score_snapshots.py`, `all-snapshot-reports.json`, `manifest.json`,
`selection.json`, final report/build logs, baseline/final all-object hashes,
`verify.py`, `verification.txt`, pool/literal/ctx output, `audit.py`,
`audit-results.json`, audit output and `differential.log`.
Every source/object hash and raw official score is recorded in the manifest.

Run from the leaf:

```sh
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/jpeg-col-neighbors/audit.py
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/jpeg-col-neighbors/verify.py
```

Baseline object:
`488b560695d7bf58b10147e38224b077e9d70786a2d4ea30edb9b318ba2ac03e`.
Original object:
`d24fd161b199d694512f691398049b84d1d624d9f992de7a5206ab82daf490c8`.
Retained object:
`abee5fc34b05e5ab30aca3573b64d414cf6dfedad5a3e1625020580f3990a080`.
Retained source:
`76038e3b2e14c24232f9f169d1691ffa09a2a9da2c7b7e1d0df2e561bd8f84a0`.
Retained Col function text:
`42448f5fffe9cb3fc3ef1a32b618ddf634a52ec1aba64e18c94b4bb61590df9e`.
