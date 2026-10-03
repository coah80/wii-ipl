# Lumi IDCT inner declaration order

Base: `f46483af` (merged #1090), 43U only.
Leaf: `wii-jpeg-lumi-orders`.
Branch: `agent/bittle/jpeg-lumi-inner-orders`.

## Supported scope and prior coverage

The only source change swaps the existing `oddLowDifference` and `oddHighSum`
uninitialized `s32` declarations in the first-pass non-DC butterfly of
`TMCJPEGDEC_IdctBlock_Lumi`, `idct_block_var.c` lines 94-98. The final order is:

```c
s32 oddLowSum;
s32 oddHighSum;
s32 oddLowDifference;
s32 oddHighDifference;
s32 dcValue;
```

All assignments, initializers, types, scopes, expressions, stores, outer locals,
helpers and configuration remain exactly as baseline. The five scalars are
assigned in the same existing order before use, have no escaping addresses,
and have the same lifetimes. This is a declaration-order experiment within an
existing butterfly block, not a new arithmetic formulation.

#978 (`e8241734`) introduced the two explicit odd-difference locals into this
Lumi row block, raising fuzzy from 82.31518% to 83.05058%. Current Lumi function
text hash equals #978 and differs from the earlier declaration-search context:

- Current / #978:
  `b36fab286108bb17821cbb9eb73c1c5965f00616e74d0cdb32b6763b75ca3c7e`
- Earlier `449529d9`, `c9fb0697`, `eecf16f0`, `6ec48a1b`:
  `205f5989dfd43b3ee513978e2ff2d596bab180b68e6bb968b4954acc7b16d4e0`

Hashes include the function definition through closing brace and newline.
Current Col hash is unchanged across those contexts:
`703e8856cb8549914189ba88fc15b94ed58dceca3e0e711e571f505a94e91c4b`.

The round4 log at lines 469-486 records older 500-swap outer declaration runs.
`four-leaves-r9.attempts.md:94,105` records capped 180-build outer-block searches;
`four-leaves-r11.attempts.md:116,128` records capped 140/160-build outer-block
searches after helper trials. Their printed 31/32-entry blocks do not include
this inner group. `jpeg-remainder-attempts.md` explicitly says no declaration
permutation search accompanied #978. No recorded exhaustive current inner-block
search was found. Old available IDCT objects were baseline snapshots rather
than a manifest of intermediate search candidates. The rejected Col d/w swap
remains closed and was not repeated.

The workspace reset occurred before any new trial. After recovery, the parent
verified main's default build/report/DOL and authorized a new leaf. This trial
uses the recovered `../toolchain/wibo-release64/wibo` with
`WIBO_SJIS_MISSING_IMPORTS=1`, cached-tool configure overrides and ordinary Ninja.
No production compiler flags or search tools were modified.

Baseline whole-source SHA256:
`d8a0e7c0741e1cddb595479ab02a34313bc6c057d0d821f72e3b760117ffeee5`.
Baseline five-line block SHA256, including newlines:
`86364b4d268da18f558cec13968e1312391163d5fa8e19e8bdbf18923d3019c9`.

## Exact finite experiment

Enumerated all **5! = 120** permutations of exactly lines 94-98, once each,
with every other source byte fixed. Each order was compiled with ordinary Ninja
and received a fresh official **full 1027-unit objdiff report**. Before/after
source hashes, actual MWCC build output, changed object mtime, successful exit,
source/object snapshots, hashes and raw function/unit scores were recorded.
No no-work call, suppressed compiler call, failed build, restart or continuation
was counted. The ordinary unchanged baseline build and final selected-source
rebuild are outside the 120 searched orders.

All 120 orders preserved Col's raw body and official 92.47577% score, all other
1026 unit reports, and every exact-code, data and completion metric. They
produced 12 distinct whole-object hashes and six raw Lumi fuzzy values:

| Lumi fuzzy | Number of orders |
| ---: | ---: |
| 79.72373 | 20 |
| 79.76265 | 20 |
| 80.0 | 20 |
| 83.01167 | 20 |
| 83.05058 | 20 |
| **83.657585** | **20** |

First best is zero-based order **6**, the single adjacent declaration swap.
The tied best orders are 6, 8, 9, 14, 15, 17, 48, 50, 51, 60, 61, 64, 74, 75,
77, 84, 85, 88, 91 and 94. Official fuzzy determined retention; structural or
positional diff counts did not determine the winner. All 120 possible orders
are exhausted in this fixed source context. No broader neighborhood is claimed.

## Fresh retained-source gates

- Lumi: **83.05058% -> 83.657585%**, 1028/1028 bytes, 257/257 instructions
- Lumi normalized positional ctxdiff remains **187**
- Col: **92.47577%**, 454/454 instructions, raw body unchanged
- Unit fuzzy: **89.06892% -> 89.28833%**
- Global fuzzy: **99.72777% -> 99.72798%**
- Unit exact functions/code remain **0/2, 0/2844**; this is a fuzzy gain
- All 1027 units and every function checked: no regression; only Lumi changes
- Fresh retained object equals order-006 object byte-for-byte
- Fresh final full report equals order-006 full report exactly
- Baseline, retained and original objects contain no allocated non-code bytes
- Pool identical, zero strings; literal audit analyzes both functions with
  zero candidates, errors or skips
- Ordinary default build/progress and explicit `build/43U/ok` pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`
- `git diff --check` passes

These IDCT functions and all three inspected objects are integer-only; no FPU
instructions or floating-point tolerance are involved. Every candidate preserves
all source arithmetic dependencies and read/write expressions exactly, including
signed fixed-point multiply/shift ordering. Only uninitialized scalar declaration
order changes. There is no reassociation or altered rounding in the source.

## Focused integer and alias validation

An independent scalar integer two-pass Lumi model was compared with the
retained, original and saved baseline PPC objects. Every scalar intermediate is
checked to fit signed 32-bit range; right shifts and clipping are compared
exactly. It uses no floating-point approximation or numeric tolerance.

**6,569 vectors / 19,707 object executions pass:**

- 1,280 combinations of all row extents 1-8, column-mode values 1-8, pitches
  8/9/16/32, and zero/DC/sparse/dense/alternating coefficient patterns
- 2,304 single-coefficient cases cover every active coefficient position at
  each row extent, with values -65536, -2048, -2047, -1, 1, 2047, 2048, 65536
- 777 DC vectors cover every output level from -1 through 257 at its fixed-point
  threshold and adjacent integer values, including lower/upper clipping edges
- 2,208 input/output overlap cases span selected fitting byte offsets, pitches
  8/16/24/32, row extents 1/2/8, column modes 1/2/3/8, and random/clipping data

Every overlap output byte stays within the actual 64-s32 input allocation.
Input alignment remains valid; output uses character stores. All input rows
have been consumed into the real local scratch array before output begins.
No stack/input overlap or fabricated outside-object pointer is tested. These
are additional machine-level alias diagnostics, not an expanded public API
contract. All non-stack memory and guards agree exactly. Candidate, original
and baseline each reach **257/257 instructions**.

The existing repository JPEG differential suite separately passes **9,456
paired cases** across 28 functions, including 704 Lumi and 704 Col cases,
with full own-body instruction coverage for both IDCT functions and preserved
GPR14-GPR31, stack pointer and LR.

This is bounded execution in the repository PPC integer interpreter, plus a
separate scalar model and exact source-preservation check. It is not a formal
CPU proof, exhaustive input proof, or Wii hardware execution.

## Evidence and hashes

`/tmp/jpeg-lumi-inner-orders/` contains baseline source/object/report, frozen
original object, all `order-000.*` through `order-119.*` sources/objects/build
logs/full official reports, `manifest.json`, `selection.json`, `trial.py`,
`trial-output.txt`, configure/default build logs, final report, `verify.py`,
`verification.txt`, `candidate.ctx`, literal output, `audit.py`,
`audit-results.json`, audit output and the existing differential suite log.
The full 120-order manifest contains each source/object hash and raw score.

Baseline whole object:
`4ff4646efa3353c76cbc55b721014cd682766e1c9b3d992640edea7eaf200112`.
Retained whole object:
`a2434d346c31d526b66073460fceb08924db12ce3eca7fef9847dc2285b0d2a8`.
Retained function bytes:
`17775253c68aed0bc209593fb6c73039c839a7d08bf5f621b15a3b8ef8af7a03`.
Retained whole source:
`8e55f74add4f4da8bfab7a69dc1c5e6a13e467e58a8c3ba6a8bd23e93e5946f3`.
Retained Lumi function text:
`8d3eca6f5cf34ade61942232c855dac36920db522111cbf40df15f9402819d2f`.
