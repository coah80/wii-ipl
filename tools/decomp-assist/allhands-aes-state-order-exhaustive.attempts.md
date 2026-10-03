# AES four-state declaration order: exhaustive official-fuzzy comparison

Base `a2c008c4`; leaf `agent/bittle/aes-state-order-exhaustive`. The accepted
`ce3cbf5f` source is the baseline: decrypt76.70518%, existing state declaration
order d,b,c,a. The previous frozen candidate remains preserved.

Only four existing uninitialized `u32` declarations are reordered to b,a,c,d.
All other source bytes, initializers, expressions, assignments, scopes, types,
helpers, tables, public APIs, configuration and linking status are unchanged.
This is a declaration-order matching gain, not new algorithmic behavior.

## Why a complete comparison was needed

The prior official search reached a local fixed point after17 evaluated orders,
optimizing `(structural difference, positional difference)` rather than official
objdiff fuzzy. Its saved log did not record intermediate orders. Before this
experiment, a read-only traversal reconstruction admitted three possible
17-order histories, so the original complete visited set was not recoverable
uniquely from saved artifacts alone. The remaining seven could not be reliably
named, and the prior intermediate orders had no official-fuzzy measurements.

The authorized experiment therefore deliberately rebuilt all24 permutations.
The official search tool, compiler, options and cache behavior were untouched.
A separate private driver changed only lines201-204, invoked ordinary Ninja
compilation and the official objdiff report tool for every order, and saved
source/object/report snapshots plus a manifest. No compilation was skipped,
no surrogate score replaced objdiff, and no restart or extra dimension occurred.

The fresh dbca baseline was rebuilt and measured first. The other23 orders were
then compiled once each. There are12 distinct whole-object hashes across the24
orders. After selection, one additional ordinary object rebuild restored the
best source. Ninja independently records25 successful object rebuilds after the
saved baseline, matching24 evaluations plus the final selection rebuild.

## Complete results

Every row passed all preservation gates: every other unit's full report is
identical; all eight sibling functions retain their instruction streams and
resolved relocations; every existing exact function/code/data measure is
preserved; all allocated non-code bytes, extents and alignments are identical;
and source text outside the four declarations is unchanged. Each row has a
fresh official report, source snapshot/hash and object snapshot/hash in the
private manifest. Object hashes below are SHA256 of the entire compiled AES
object, not instruction-score hashes.

| Order | Official decrypt fuzzy | Structural/raw | Preservation gates | Object SHA256 |
|---|---:|---:|---|---|
| dbca | 76.70518 | 60/205 | PASS | `9eaf814a28a1585d780efa84a36f8981711b95c64566f67cf99469154eefc970` |
| abcd | 72.30677 | 93/217 | PASS | `426958cfec4e8d48869177e56a9f9d8afed12af28934980d88918c8bd6d05177` |
| abdc | 70.972115 | 72/216 | PASS | `5adf70c02ada68e520d1c533339eb830e4c86227c99dba537113e4ea1d47bf1c` |
| acbd | 72.30677 | 93/217 | PASS | `426958cfec4e8d48869177e56a9f9d8afed12af28934980d88918c8bd6d05177` |
| acdb | 72.123505 | 93/217 | PASS | `f7779c0547ac63397ed0f8631cbcafeed598ca9f734e271eadb68568a396bb69` |
| adbc | 70.972115 | 72/216 | PASS | `5adf70c02ada68e520d1c533339eb830e4c86227c99dba537113e4ea1d47bf1c` |
| adcb | 76.525894 | 68/216 | PASS | `44f7dd4aea84e4d62c9bca2ba6c034c368ca48c1e8bb7497924124641f34c558` |
| bacd | 78.95618 | 68/215 | PASS | `1a37fcb561221b6b60fb66feaf06411cc02fafef101d705b60ce2c69a4379569` |
| badc | 74.99602 | 71/213 | PASS | `427ae222f6c756f3a525e53f7aba7cf232c9d509c80d37c0c87b3ad5ffe5e9e1` |
| bcad | 78.95618 | 68/215 | PASS | `1a37fcb561221b6b60fb66feaf06411cc02fafef101d705b60ce2c69a4379569` |
| bcda | 76.525894 | 78/211 | PASS | `57052da319d896c187a83017e6e31d69e7bc4fd0bda1f1cf8f4795aa8d838e3b` |
| bdac | 74.99602 | 71/213 | PASS | `427ae222f6c756f3a525e53f7aba7cf232c9d509c80d37c0c87b3ad5ffe5e9e1` |
| bdca | 78.876495 | 65/213 | PASS | `8398c78fc241ecfb72a89ad0b14fc9b71118dd9f64cca7bc071ee5730f2001ec` |
| cabd | 73.32271 | 70/214 | PASS | `79f077cea200aefb8fb66ae2d108fbd2ef2985e4977d0b5fd63b108b9cde5114` |
| cadb | 73.32271 | 70/214 | PASS | `79f077cea200aefb8fb66ae2d108fbd2ef2985e4977d0b5fd63b108b9cde5114` |
| cbad | 73.836655 | 63/216 | PASS | `7651aa61c79c62ebe0af0b750639552ba00079357cd9865b4dedf7b884271f9b` |
| cbda | 73.836655 | 63/216 | PASS | `7651aa61c79c62ebe0af0b750639552ba00079357cd9865b4dedf7b884271f9b` |
| cdab | 73.32271 | 70/214 | PASS | `79f077cea200aefb8fb66ae2d108fbd2ef2985e4977d0b5fd63b108b9cde5114` |
| cdba | 73.836655 | 63/216 | PASS | `7651aa61c79c62ebe0af0b750639552ba00079357cd9865b4dedf7b884271f9b` |
| dabc | 75.76892 | 61/214 | PASS | `e0190031dca922706310bbe3d26ffff12e9224a7f13442fd1ecad4f83a0cf416` |
| dacb | 75.76892 | 61/214 | PASS | `e0190031dca922706310bbe3d26ffff12e9224a7f13442fd1ecad4f83a0cf416` |
| dbac | 76.70518 | 60/205 | PASS | `9eaf814a28a1585d780efa84a36f8981711b95c64566f67cf99469154eefc970` |
| dcab | 75.76892 | 61/214 | PASS | `e0190031dca922706310bbe3d26ffff12e9224a7f13442fd1ecad4f83a0cf416` |
| dcba | 76.70518 | 60/205 | PASS | `9eaf814a28a1585d780efa84a36f8981711b95c64566f67cf99469154eefc970` |

The maximum official fuzzy is **78.95618%**, shared by bacd and bcad, which
produce byte-identical objects. The first strictly improving maximum, bacd,
is retained. All24 orders are covered; this four-declaration space is now
exhausted for this exact expression/compiler context.

Using the newly measured score table, a read-only replay of the unchanged
hill-climbing traversal reproduces the original trajectory and17-order count:
`abcd (93,217) -> bacd (68,215) -> dacb (61,214) -> dbca (60,205)`.
Thus the best official-fuzzy form had been the first improvement in the old
run, then was displaced by its structural-first objective. This replay uses
new exhaustive measurements; it is not claimed as recovery from old logs alone.

## Final measures and gates

- AESiDecryptBlock: **76.70518 ->78.95618%**,251/251 instructions.
- AESiEncryptBlock: **65.81013% unchanged**,158/158; entire function unchanged.
- AES unit fuzzy: **83.64971 ->84.47093%**.
- Exact functions **7/9**, exact code **1116/2752**, data **2800/2800**, unchanged.
- Full1027-unit baseline/final comparison: only AES changes, no existing exact,
  code, data or per-function fuzzy regression in the retained result.
- Pool4/4 identical; literal audit covers nine functions/five arguments, with
  no candidates, skips or errors.
- Fresh full43U baseline and final full43U builds pass using
  `../toolchain/wibo-build/wibo` and `WIBO_SJIS_MISSING_IMPORTS=1`.
- Default `progress build/43U/report.json` and `build/43U/ok` pass.
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`.
- `git diff --check` passes. No remote action or linking change.

## Behavior and alias validation

The production C is compiled unchanged for native tests with minimal PPC-type/
OS shims and target-endian numeric words. Candidate and actual baseline each
pass2406 independent AES-128/192/256 known-answer/randomized CBC comparisons,
including in-place/separate buffers and incremental calls. The candidate also
passes2688 direct-block input/output overlaps at offsets-3..+3 words. Both
native validation paths run under UBSan with no recovery and no runtime error.

An interpreter of actual source and original final-round instructions passes
4608 cases for both, against an independent packing/publication oracle. These
include separate output and eight placements overlapping/adjoining final key
words. The interleaved K0-load/O0-store through K3-load/O3-store event sequence
is preserved. Candidate decrypt's incoming state registers are r6/r0/r5/r10,
verified from actual input/key XORs and round-result assignments; its key cursor
is r9. Only that map was adapted from the existing independent interpreter.

Immutable S-box load scheduling remains nonexact: source has5/13/16/16 table
loads before successive stores, versus target5/11/16/16. This does not change
the key-load/store alias order and is not hidden by the fuzzy gain. Key-overlap
cases remain diagnostics, not a new supported public API promise. No live Wii
runtime execution is claimed.

## Reproduction and frozen evidence

Private evidence directory: `/tmp/aes-state-order-exhaustive/`. It contains
`manifest.json` with every order/hash/score/gate,24 corresponding source/object/
report snapshots, compiler logs, baseline/final reports, the enumeration driver,
known-answer/overlap/publication scripts and results, and full/default-progress/
pool/ctxdiff/literal gates. Retail objects and disassembly remain private.
Do not rerun the exhausted enumeration. Read-only reproduction checks and tests:

```sh
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/aes-state-order-exhaustive/verify_exhaustive.py
python3 /tmp/aes-state-order-exhaustive/validate_aes.py
python3 /tmp/aes-state-order-exhaustive/test_input_overlap.py
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/aes-state-order-exhaustive/final_publication_audit.py
```

Baseline source SHA256:
`29f201a50b18799eea47820c52ebdb26254e5ccdc2904c858ffffe71cea9f109`.
Final source SHA256:
`af7e472e1d862675b353679af97ff4f90115891d14eb9b327941995e56dae48c`.
Final whole-object SHA256:
`1a37fcb561221b6b60fb66feaf06411cc02fafef101d705b60ce2c69a4379569`.

GATE PASS: strict official fuzzy gain, complete24-order coverage, all exact/
code/data/source/alias/default-progress/43U/DOL gates preserved. Source frozen;
no further order experiment running or needed in this context.
