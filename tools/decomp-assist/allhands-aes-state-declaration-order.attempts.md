# AES decrypt state declaration order

Base `7b32451989deae9f6732e74fc2ed95f3afb27b28`, leaf
`agent/bittle/aes-state-declaration-order`. Only the existing four uninitialized
AESiDecryptBlock state declarations and this log change. No initializer,
expression, assignment, scope, type, helper, table, ABI or linking change.

## Source and original-object screening

Baseline aes.c SHA256:
`5829cc15a496ed08767b7b857d4fa5ad099974dfc48182fd0f8a0eb00d61725a`.
It is byte-identical to the accepted #1020 source. The original/source audit
found no new missing round, key/table access, width or ownership operation.
It confirmed cyclic T-table byte indices/rotations, forward/backward four-word
key traversal, lazy inverse-key writes and round-count reload, transform-flag
clear, and final key-load/output-store ordering. Existing source/target alias
proofs from #1020 remain relevant; keys must not be snapshotted before earlier
output stores. The residual also includes arithmetic scheduling and dependency
shape, so it is not described as exclusively register coloring.

Earlier key-base/local trials in `/tmp/crypto-remainder/` moved initialized
rounds/key declarations or changed initialized next-state lifetimes/scopes.
Those precede the accepted round and final-expression changes. The three
allhands AES logs and #1020's five-trial evidence show no four-state declaration
search in the current expression context. Initialized encryption/round
locals were excluded.

## Neutral split, followed by exactly one official search

The original line201, `u32 a,b,c,d;`, was first split in place into four plain
`u32` declarations in the same a,b,c,d order. This adds no state or initializer.
All four values are assigned by the existing input/key sequence before their
first use; the preceding lazy-transform branch does not access them.

Before any order search, a fresh compiler rebuild proved the **entire object
byte-identical** to baseline, SHA256:
`426958cfec4e8d48869177e56a9f9d8afed12af28934980d88918c8bd6d05177`.
The fresh full 1027-unit report was also byte-identical. This neutral split
was an explicit prerequisite to the following single authorized run:

```sh
WIBO_SJIS_MISSING_IMPORTS=1 NINJA=../.venv/bin/ninja PYTHONPATH=../local-tools \
  ../.venv/bin/python tools/decomp-assist/declsearch.py libs/RevoEX/src/net/aes \
  AESiDecryptBlock --lines 201 204 --max-evals 24
```

The official tool was unchanged, SHA256
`9642fe689ee3a4d80236b5f790fdda83397214cd209c62ce07088b3f2b3726bb`.
It performed ordinary compiler rebuilds; Ninja records the split rebuild,
17 evaluation rebuilds and the final selected-order rebuild after baseline.

Official score trajectory:
`(93,217) -> (68,215) -> (61,214) -> (60,205)`.
It stopped at a **local fixed point after 17 unique evaluated orders**, below
the 24 cap. This covers the final swap/move neighborhood and orders visited
along the improving path, **not all 24 permutations**. No second run occurred.

Retained declarations, in their original scope:

```c
u32 d;
u32 b;
u32 c;
u32 a;
```

All source text outside the old grouped declaration is byte-for-byte unchanged.
This is a compiler declaration-order gain, not newly reconstructed behavior.

## Fresh measures and full gates

- AESiDecryptBlock: **72.30677 -> 76.70518%**, 251/251 instructions;
  positional differences217 ->205.
- AESiEncryptBlock: **65.81013% unchanged**, 158/158, emitted body unchanged.
- Unit fuzzy: **82.04506 ->83.64971%**.
- Exact functions **7/9**, exact code **1116/2752**, data **2800/2800**, unchanged.
- All eight sibling function instruction streams and resolved relocations
  unchanged, including all seven exact API/CBC functions.
- Every allocated non-code section preserves bytes, extent and alignment.
- Full1027-unit comparison: AES is the only changed unit; no exact function,
  code, data, function-size total or per-function fuzzy regression.
- Pool4/4 identical. Literal audit: nine functions, five arguments, no
  candidates, skips or errors.
- Full43U build, default `progress build/43U/report.json`, and `build/43U/ok`
  pass with `../toolchain/wibo-build/wibo` and `WIBO_SJIS_MISSING_IMPORTS=1`.
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`.
- `git diff --check` passes.

## Independent behavior and alias validation

Private scripts use the actual production C unchanged and minimal native
PPC-type/OS shims, with key/input/IV words represented in target-endian numeric
form. Known-answer/randomized outputs are checked against an independent AES
implementation. Native libraries use UBSan with no recovery.

- `validate_aes.py`: candidate and actual baseline each pass **2406**
  AES-128/192/256 CBC cases, including separate/in-place buffers and incremental
  calls, with no UBSan failure.
- `test_input_overlap.py`: candidate passes **2688** direct-block cases with
  output displaced -3 through +3 words relative to input, in both directions.
- `final_publication_audit.py`: interprets actual source and original final-round
  instructions; **4608** final-state cases pass for both, including separate
  output and eight output placements overlapping/adjoining final key words.
  Every case checks K0-load/O0-store/K1-load/O1-store/K2-load/O2-store/K3-load/
  O3-store ordering against an independent word/publication oracle.

The candidate's incoming decrypt state registers are r10/r6/r5/r0, established
from actual input-key XORs and round-result assignments; the final key cursor
is r9. Only this register map was updated in the saved interpreter. The actual
instruction streams, original-object data, and independent oracle are read
rather than replaced by synthetic code.

Pure immutable S-box load scheduling still differs: candidate decrypt has
5/12/16/16 table loads before successive output stores versus target5/11/16/16.
The key-load/store sequence is preserved. This remaining instruction mismatch
does not justify another source variant or a changed alias contract. The
key-overlap cases are diagnostics, not a new public-API support promise.
No live Wii runtime execution is claimed.

## Reproduction and freeze

Private evidence directory: `/tmp/aes-state-declaration-order/`. From this leaf:

```sh
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/aes-state-declaration-order/verify_candidate.py
python3 /tmp/aes-state-declaration-order/validate_aes.py
python3 /tmp/aes-state-declaration-order/test_input_overlap.py
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/aes-state-declaration-order/final_publication_audit.py
```

The directory also contains baseline/split/searched/final reports, baseline
and candidate source/objects, search trajectory, build/default-progress logs,
vector/overlap/publication outputs, and pool/ctxdiff/literal evidence. Retail
objects/disassembly remain private and are not committed.

Final source SHA256:
`29f201a50b18799eea47820c52ebdb26254e5ccdc2904c858ffffe71cea9f109`.
Final source-object SHA256:
`9eaf814a28a1585d780efa84a36f8981711b95c64566f67cf99469154eefc970`.

GATE PASS: strict official partial fuzzy gain; all exact/code/data/behavior
and full43U/DOL gates preserved. Candidate frozen; no further search running.
