# Lumi fixed immediate-neighborhood audit

Base: `b41f95f9` (merged #1093), 43U only.
Leaf: `wii-jpeg-lumi-neighbors`.
Branch: `agent/bittle/jpeg-lumi-fixed-neighbors`.

## Scope and fixed center

The authorized audit holds the retained **86.15953%** Lumi order fixed as its
center and evaluates baseline plus every unique single swap/move neighbor of
the same 30 uninitialized `s32` declarations at lines **31-60**. It is not an
adaptive hill climb or another official declsearch invocation. The scratch array,
`dst` pointer, retained inner order from #1091 and every source byte outside
lines 31-60 remain frozen. No initializer, expression, assignment, type, scope,
helper, compiler flag, data or link configuration changes.

Baseline whole source SHA256:
`65930a8c92d8acfd1cb6ee35715a0ff475b46b1abf649ba6ee3a3216cb51e087`.
Baseline Lumi function-text SHA256:
`250a74ae5b9b7f901bfe79dda1ae0dd0ae4ce29e1383d3e636c19ac00f7e4606`.

The exact two neighbor-generation loops from unchanged official
`tools/decomp-assist/declsearch.py` are reused: all index-pair swaps, then all
ordered index-pair pop/insert moves. Duplicate source orders are removed before
compilation, while preserving first-seen order. There are 435 unique swaps and
841 unique moves with 29 shared adjacent swaps: **1,247 unique neighbors**.
Scores never change the enumeration center or the set of orders.

Official tool SHA256, unchanged:
`9642fe689ee3a4d80236b5f790fdda83397214cd209c62ce07088b3f2b3726bb`.
The baseline was freshly rebuilt with the existing cached-tool configure
settings, `../toolchain/wibo-release64/wibo`, and
`WIBO_SJIS_MISSING_IMPORTS=1`, followed by ordinary default Ninja, explicit
43U `ok`, and a fresh full official report.

## Compilation, scoring and historical overlap

Exactly **1,248 recorded orders** were compiled: baseline and all 1,247 unique
neighbors. The recorder invokes real Ninja with unchanged arguments/environment,
saves source and successful object snapshots, verifies source stability and the
permitted declaration range, and records hashes, timestamps, compiler output
and return status. Every call emitted the actual MWCC object build and changed
the object mtime. There were zero failed, no-work or unstable-source calls.
The orders produced **207 distinct whole-object hashes**. The initial baseline
and final selected-source full builds are separate validation operations.

The previous capped run recorded only the center and two of these neighbors.
This exact overlap is verified from source-order manifests and equal surrounding
source, and occurs at current enumeration indices **0, 250 and 413**. The
remaining 1,245 neighbors were not recorded in that prior run. No claim about
all historical compilations is made.

All 1,248 saved objects are scored by official objdiff using a private copy of
the actual configuration, preserving diff settings, metadata and mappings.
Unique snapshot unit names point to the frozen original object and each frozen
candidate object. No `--deduplicate`, skipped compilation, live-object swapping
or batch aggregate score is used. The private one-unit baseline report first
matches the actual full baseline's functions, sections and unit measures.

Every snapshot preserves Col's raw body and **92.47577%** score, the same
function set, exact-code/completion metrics, and empty allocated non-code
sections. There are no non-fuzzy gate failures. There are 497 admissible orders:
496 baseline ties and **one strict improvement**. The other 751 lose unit fuzzy.

The unique best is **snapshot 0256**, swapping only the existing declarations
`o` and `n` (baseline lines 41 and 52). Its official Lumi score is
**86.178986%**, compared with baseline **86.15953%**. Both have the same
internal structural/positional score `(22,185)`, so official fuzzy determines
retention.

## Coverage and stopping condition

The enumeration completed the entire authorized fixed neighborhood:

- Original center: **1,247/1,247 immediate neighbors compiled**, none missing
- New winner: **5/1,247 immediate neighbors observed**, 1,242 unobserved

These counts come from the recorded exact orders intersected with the same
swap/move generators. Because an improving neighbor was found, the original
center is not a local maximum. The new winner is **not claimed to be a fixed
point**. No adaptive search, continuation, restart or further variant occurred.

## Fresh retained-source gates

The selected source is rebuilt with ordinary default Ninja and explicit
`build/43U/ok`, then receives a fresh full official report.

- Lumi: **86.15953% -> 86.178986%**, 1028/1028 bytes, 257/257 instructions
- Normalized positional ctxdiff remains **185**
- Col: **92.47577%**, 454/454 instructions; raw body unchanged
- Unit fuzzy: **90.19269% -> 90.19972%**
- Global fuzzy: **99.728836% -> 99.72885%**
- Unit exact functions/code remain **0/2, 0/2844**; this is a fuzzy gain
- All 1027 units and every function checked: no regression; only Lumi changes
- Fresh whole object equals saved snapshot 0256 byte-for-byte
- Fresh full-report IDCT functions/sections/measures equal the saved snapshot
- Original/baseline/candidate have zero allocated non-code bytes; pool identical
- Literal audit: both functions analyzed, zero candidates, errors or skips
- Ordinary default build/progress and explicit 43U `ok` pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`
- `git diff --check` passes

## Semantics and behavior

This is only an uninitialized scalar declaration swap in an existing contiguous
block. Both scalars retain every assignment, use, type and scope; their addresses
do not escape. All actual integer operation dependencies, fixed-point shifts,
read/write expressions, the scratch array and inner butterfly order are unchanged.
The inspected original/baseline/selected IDCT bodies contain no FPU instructions.

The same exact-integer scalar model was rerun against selected, original and
this audit's saved baseline objects. **6,569 vectors / 19,707 object executions
pass**, with **257/257 instruction coverage** in each object:

- 1,280 dimension, pitch and coefficient-pattern combinations
- 2,304 single-coefficient position/scaling cases
- 777 DC clipping threshold and adjacent-value cases
- 2,208 in-allocation input/output overlap cases

Every model intermediate is checked within signed-32-bit range. Every non-stack
memory byte and guard agrees exactly. Overlap stores stay within the actual
64-s32 input allocation; there is no stack alias or outside-object pointer.
These overlap arrangements are machine-level diagnostics, not an expanded API
contract. No tolerance-based numeric comparison is used.

The repository JPEG suite separately passes **9,456 paired cases** across
28 functions, including 704 Lumi and 704 Col cases with full IDCT own-body
coverage, preserving GPR14-GPR31, stack pointer and LR. These bounded
interpreter/model tests do not constitute a formal proof or Wii hardware run.

## Preserved evidence

`/tmp/jpeg-lumi-neighbors/` contains baseline source/object/report, frozen
original object, all `snapshots/0000.*` through `snapshots/1247.*`,
`enumerate.py`, `enumeration.json`, `enumeration-output.txt`, `ninja-record.py`,
`calls.jsonl`, actual/private objdiff configs, `score_snapshots.py`,
`all-snapshot-reports.json`, `manifest.json`, `selection.json`, final full report,
build logs, `verify.py`, `verification.txt`, `candidate.ctx`, literal output,
`audit.py`, `audit-results.json`, audit output and the differential suite log.
The manifest records every source/object hash and raw official score.

Run from the leaf:

```sh
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/jpeg-lumi-neighbors/audit.py
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/jpeg-lumi-neighbors/verify.py
```

Baseline whole object:
`fe1ea30df17ae6263527744a5478eebfac008de2799226b312b80d8dc01e68ed`.
Retained whole object:
`488b560695d7bf58b10147e38224b077e9d70786a2d4ea30edb9b318ba2ac03e`.
Retained whole source:
`e0f98086d67cd3bfedb640a3cacd0801428d929da4ac2397ef61754e2b0e4002`.
Retained Lumi function text:
`958b01bf2966f73f06b3b67673d2a653814262e86454d2a23d356ad2bc4129e7`.
