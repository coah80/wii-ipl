# Lumi outer declarations after the retained inner order

Base: `3dd12f63` (merged #1091), 43U only.
Leaf: `wii-jpeg-lumi-outer-orders`.
Branch: `agent/bittle/jpeg-lumi-outer-orders`.

## Scope and new allocator context

One authorized invocation of unchanged official `declsearch.py` permutes only
`TMCJPEGDEC_IdctBlock_Lumi` lines **31-60**, the 30 existing uninitialized `s32`
scalars from `done` through `b1`. The scratch array at line 29 and `dst` pointer
at line 30 remain fixed. The retained inner order from #1091 and every source
byte outside lines 31-60 remain fixed. There are no changes to initializers,
assignments, expressions, types, scopes, helpers, compiler flags or data.

The outer declaration block is contiguous and contains no initializer. All
variables retain their original uses and assignments. This is a contextual
register-allocation search, not a claim of a semantic defect. The earlier
outer searches in round4/four-leaves-r9/r11 predate the retained #1091 inner
order. The 120-order #1091 experiment kept all outer declarations fixed.

Baseline Lumi function text SHA256:
`8d3eca6f5cf34ade61942232c855dac36920db522111cbf40df15f9402819d2f`.
Baseline whole source SHA256:
`8e55f74add4f4da8bfab7a69dc1c5e6a13e467e58a8c3ba6a8bd23e93e5946f3`.
Authorized 30-line block SHA256, including newlines:
`f1ac9e00d55cd1d240a370083c6181f6673f43f52e46e91e05aacc0d8ced5469`.

The fresh unchanged baseline was rebuilt using ordinary default Ninja and
explicit 43U `ok`; fresh official report confirms Lumi **83.657585%**, Col
**92.47577%**. The approved wrapper is `../toolchain/wibo-release64/wibo`, with
`WIBO_SJIS_MISSING_IMPORTS=1` and the existing cached-tool configure overrides.

## Single bounded run and recording

```sh
WIBO_SJIS_MISSING_IMPORTS=1 \
NINJA=/tmp/jpeg-lumi-outer-orders/ninja-record.py \
PYTHONPATH=../local-tools ../.venv/bin/python -u \
  tools/decomp-assist/declsearch.py \
  libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var \
  TMCJPEGDEC_IdctBlock_Lumi --lines 31 60 --max-evals 1250
```

Official tool SHA256, unchanged before and after:
`9642fe689ee3a4d80236b5f790fdda83397214cd209c62ce07088b3f2b3726bb`.

The recorder always invokes the real `.venv/bin/ninja` with the exact supplied
arguments and inherited environment. It saves the exact source before each
call, checks the authorized range, verifies source stability after compilation,
and saves the successful object. It records declaration order, source/object
hashes, timestamps, object mtime, compiler stdout/stderr and return status.
It does not replace, suppress, accelerate or alter compilation.

There were **1,250 distinct evaluated orders**, plus the tool's separate final
restoration call: **1,251 actual MWCC object compilations**. Every call succeeded,
updated the object mtime and had stable source. There were zero failed, no-work
or unstable-source calls. The evaluated orders produced **542 distinct whole
objects**. The original baseline build and final chosen-source validation build
are separate from these recorded calls.

The official internal trajectory was:

```text
(40,187) -> (33,187) -> (32,187) -> (32,186)
         -> (28,186) -> (28,185) -> (22,185)
```

The invocation **hit the 1,250-evaluation cap**. It did not establish a local
fixed point. There was no restart, continuation or second invocation.

## Official scoring of frozen snapshots

A private copy of actual `objdiff.json` preserves all diff settings, unit
metadata and mappings. Its units are copies of the real IDCT unit, with unique
names, frozen original-object `target_path` and each saved-object `base_path`.
Official `objdiff-cli report generate -p PRIVATE_DIR -o REPORT -f json` scores
all 1,251 snapshots without `--deduplicate` or swapping live source/objects.
First, a one-unit private baseline report was verified identical to the real
full-project baseline's functions, sections and unit measures.

Only each candidate's raw function/unit scores are used; the artificial batch
aggregate is ignored. Every snapshot preserved Col's raw body and 92.47577%
fuzzy score, the same function set, exact-code/completion metrics, and empty
allocated non-code sections. All source snapshots preserve the exact authorized
block multiset and all other bytes. There are no non-fuzzy gate failures.

Of the 1,250 evaluations, 632 were admissible (including baseline ties), and
618 strictly improved Lumi. The other 618 were rejected for unit fuzzy loss.
The unique official-fuzzy best is **call 1033**, at **86.15953%**. The tool-final
order scores **86.08171%**. Both have internal tool score `(22,185)`, illustrating
why the internal comparator alone cannot select the best official fuzzy result.
Call 1033 is retained, not the tool-final order.

Retained order (all existing `s32` declarations):

```text
d, t, i, y, b2, b1, b4, b5, b6, b7, o, m, a, done, z,
v, p, p_part, m_part, u, r, n, x, x_factor, z_factor,
iter, q, w, e, b3
```

## Recorded neighborhood coverage

For 30 distinct declaration lines, the official swap/move generators produce
435 distinct swaps and 841 distinct moves, with 29 overlapping adjacent swaps:
**1,247 distinct immediate neighbors**. Baseline plus that neighborhood is 1,248
orders, but accepted improvements restart around new centers, so the cap does
not imply full coverage of the final neighborhood.

Coverage below is computed by comparing the exact recorded evaluated orders
with those generators, rather than inferred from the evaluation count:

- Tool-final order: **467/1,247** neighbors compiled; **780** uncompiled
- Retained official-fuzzy best: **2/1,247** neighbors compiled; **1,245** uncompiled

These are coverage facts for this invocation, not claims about all historical
orders or a global optimum. Neither neighborhood is exhausted. No additional
search was run.

## Fresh retained-source gates

After choosing call 1033, rebuild its saved source with ordinary default Ninja,
then explicit `build/43U/ok`, and generate a fresh full official report.

- Lumi: **83.657585% -> 86.15953%**, 1028/1028 bytes, 257/257 instructions
- Normalized positional ctxdiff: **187 -> 185**
- Col: **92.47577%**, 454/454 instructions; raw body unchanged
- Unit fuzzy: **89.28833% -> 90.19269%**
- Global fuzzy: **99.72798% -> 99.728836%**
- Unit exact functions/code remain **0/2, 0/2844**; this is a fuzzy gain
- All 1027 units and every function checked: zero regressions; only Lumi changes
- Fresh retained whole object equals saved snapshot 1033 byte-for-byte
- Fresh full-report IDCT functions/sections/measures equal the saved raw snapshot
- Original/baseline/candidate have zero allocated non-code bytes; pool identical
- Literal audit: two functions, zero candidates, errors or skips
- Ordinary default build/progress and explicit 43U `ok` pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`
- `git diff --check` passes

## Integer, dependency and alias validation

Only scalar declaration order changes; all actual integer operation dependencies,
read/write ordering, fixed-point multiply/shift expressions and scopes are
unchanged. No addresses of these scalar locals escape. The scratch array,
pointer declarations and retained inner butterfly declarations are untouched.
The baseline, selected and original IDCT objects contain no FPU instructions.

The existing independent scalar Lumi model was rerun against selected,
original and this run's freshly saved baseline objects:

- **6,569 vectors / 19,707 object executions**, all exact-byte comparisons pass
- 1,280 row/column-mode, pitch and coefficient-pattern combinations
- 2,304 single-coefficient position/scaling cases
- 777 DC clipping threshold and adjacent-value cases
- 2,208 input/output overlap cases, every output byte inside the actual
  64-s32 input allocation; no stack alias or outside-object pointer
- All scalar intermediates checked within signed-32-bit range
- All non-stack memory and guards agree; **257/257** instruction coverage for
  selected, original and saved baseline

The repository JPEG differential suite also passes **9,456 paired cases** across
28 functions, including 704 Lumi and 704 Col cases with full own-body coverage;
GPR14-GPR31, stack pointer and LR are preserved. These are bounded integer
interpreter/model checks, not a formal proof or Wii hardware execution. The
alias cases are additional machine-level diagnostics, not an expanded API
contract. No tolerance-based arithmetic comparison is used.

## Evidence and retained hashes

`/tmp/jpeg-lumi-outer-orders/` contains `baseline.c/.o`, `original.o`, baseline
and final full reports, actual/private objdiff configs, `calls.jsonl`, all
`snapshots/0000.*` through `snapshots/1250.*`, `ninja-record.py`,
`search-output.txt`, `score_snapshots.py`, `all-snapshot-reports.json`,
`manifest.json`, `selection.json`, configure/default build logs, `verify.py`,
`verification.txt`, `candidate.ctx`, literal audit, `audit.py`,
`audit-results.json`, audit output and the 9,456-case differential log.

Run the model and validation from the leaf with the shared Python environment:

```sh
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/jpeg-lumi-outer-orders/audit.py
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/jpeg-lumi-outer-orders/verify.py
```

Baseline whole object:
`a2434d346c31d526b66073460fceb08924db12ce3eca7fef9847dc2285b0d2a8`.
Retained whole object:
`fe1ea30df17ae6263527744a5478eebfac008de2799226b312b80d8dc01e68ed`.
Retained whole source:
`65930a8c92d8acfd1cb6ee35715a0ff475b46b1abf649ba6ee3a3216cb51e087`.
Retained Lumi function text:
`250a74ae5b9b7f901bfe79dda1ae0dd0ae4ce29e1383d3e636c19ac00f7e4606`.
