# AOSS decrypt: one fixed-center declaration neighborhood

Base: `5a2bf89d0c590bbc5996636cb8cfa0c791287caf`.
Leaf: `agent/bittle/aoss-decrypt-fixed-neighbors`.
Only the existing uninitialized `state` and `dataLength` declaration positions
are exchanged in `src/scene/setting/AOSS.c`. All other source bytes, including
initializers, arrays, aggregate storage, expressions, assignments and scopes,
remain unchanged. No types, helpers, configuration or linking changes.

## Scope and coverage

The previous accepted center scores 97.88162%. Its source SHA256 is
`3176094eb46f60ea3fbfad5d70d3d169752650d58fadafa30d17ca7add7567ba`;
its whole-object SHA256 is
`243e1cae7fc57681cee68ea32b602aa57c2c97a5454e8afb517ad11c2885d0d0`.
A fresh baseline build and official full report reproduce verified main's
object and full report byte-for-byte. The baseline pool is identical.

One fixed-center experiment covers the same 15 plain uninitialized declarations
at lines 1858-1872. The unchanged swap/move generation block is extracted
verbatim from the repository's `declsearch.py`, whose SHA256 is
`9642fe689ee3a4d80236b5f790fdda83397214cd209c62ce07088b3f2b3726bb`.
The center never changes. Duplicate generated orders are removed before
evaluation, retaining the official generation order; every resulting order is
actually compiled and officially scored.

There are 105 distinct swaps and 196 distinct moves, with 14 common orders:
287 nonbaseline neighbors, plus one baseline, for **288 evaluations**.
All 288 completed. The stop reason is complete fixed-center coverage, with
no adaptive search, restart, numerical-cap truncation or subsequent trial.
Six orders overlap the preceding recorded 288-order neighborhood; 282 are
beyond that recorded set. Additional older historical coverage is unknown.
This does not claim coverage of all 15! orders or a fixed point around the
newly selected order. The tested center has a strictly better neighbor.

## Real builds and official scoring

Configuration uses the supported cached tool paths to avoid downloads:

```
python3 configure.py --version 43U \
  --wrapper ../toolchain/wibo-release64/wibo \
  --dtk build/tools/dtk --objdiff build/tools/objdiff-cli \
  --sjiswrap build/tools/sjiswrap.exe --bstool build/tools/bstool \
  --compilers build/compilers --binutils build/binutils
```

Every evaluation invokes real Ninja with `WIBO_SJIS_MISSING_IMPORTS=1` and
requires successful actual MWCC compilation. A recorder snapshots source and
object only after checking that source stayed stable across compilation. Each
record includes source/object hashes, full configuration hashes and compiler
output. No compilation is skipped or replaced by a cached/surrogate score.

Every immutable snapshot gets a fresh official objdiff report in a private
project retaining the complete 1,027-unit configuration; only the owned object's
base path changes to its snapshot. A private baseline report first reproduced
the full live baseline report byte-for-byte. No live object swapping is used
for scoring, and identical objects still receive separate official reports.

All 288 snapshots pass the declaration-only source constraint, every sibling
report and instruction/relocation comparison, allocated non-code bytes,
extents/alignment/relocations, exact/code/data/link measures and the other
1,026 complete unit reports.

The first official-fuzzy maximum is **snapshot 037**, swapping `state` with
`dataLength`: **97.88162% -> 97.990654%**. Nine orders tie this maximum and
produce one identical whole object. The structural/raw diagnostic changes
from (0,87) to (0,90); it is not used to rank candidates. The companion CSV
records all 288 orders, source/object hashes, official scores and preservation
gates. Snapshot 000 is the baseline; 001-287 are nonbaseline neighbors.

After selection, an ordinary fresh rebuild reproduces snapshot 037's whole
object and full official report byte-for-byte. Selected source SHA256:
`059dfba32d87ac92600fe0352fd2eb282dc2980cd679aa8da9a9e2edbd6e7f4c`.
Selected object SHA256:
`870d93a96190004b296f96bd7f41d05a547d6e69274574123b33f3caf2503509`.

## Current-object semantic verification

The selected and baseline objects contain the same 321 instruction opcodes.
Only 87 register operands differ, within 0x154-0x2E8. Every instruction outside
that region and all 23 call positions/destinations remain unchanged.

A symbolic evaluator checks the actual current object against the fresh
baseline. It proves the initialization, paired-byte loop, parity/count setup,
single-byte tail and exit setup independently. Equal live input roles and
arbitrary common memory give identical ordered memory reads/stores, resulting
memory, CTR/CR values, branch predicates and live output roles. The loop steps
preserve their entry invariant, including input/output advancement. Scratch
registers are excluded only after checking their actual read-before-write
behavior; the proof does not assume that state, stack and payload addresses
are distinct.

The original `AOSSInitCrc32Table` callee is inspected directly: its only live
GPR input is r4. It overwrites r3/r5 and does not observe the changed r6-r10
scratch values. The unchanged caller tail overwrites those values before use,
or reaches a call which does not accept them. Original `AOSSi_Free` forwards
the owned buffer from r3 into the callback's r4 and explicitly sets its other
two arguments; no changed scratch register enters that contract. Key-schedule
arguments and all preceding calls are untouched. Cleanup/error paths and
publication order remain the existing retail behavior.

The actual production decryptor and key-schedule, CRC, address-check and
manufacturer-scrambling functions are extracted without body changes into a
native UBSan harness. Selected and baseline versions each pass **2,120 cases**:

- Every valid payload length 0 through 1472, plus 512 seeded random cases,
  checked against independent stream-cipher and zlib CRC expectations
- Checksum mismatch, disabled encryption, missing/mismatched/stored address,
  and each of four allocation failures
- Whole-packet bytes, output length, key bytes, address state, error code,
  allocation counts, allocation guard bytes and complete cleanup ownership

The allocator and byte-order wrappers are controlled scaffolding. No network
or real-device test is claimed. UBSan runs without recovery.

## Final gates and reproduction

- AOSSDecryptMessage: 97.88162% -> 97.990654%, 321/321 instructions
- Unit fuzzy: 97.72777% -> 97.73641%
- Exact functions 16/21, exact code 6436/16192, data 3928/3928 and linking unchanged
- All 20 siblings and other 1,026 unit reports preserved for all 288 snapshots
- Pool identical 1/1; literal audit 19 functions/12 arguments, no candidates/errors
- Existing unequal-size AOSS_Init_old/AOSSSendHelloRequest literal skips unchanged
- Full 43U build, default progress/report/ok and source diff checks pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`

Private reproduction evidence is `/tmp/aoss-decrypt-fixed-neighbors/`:
`run_fixed_neighbors.py`, the verbatim official generation fragment,
`orders.json`, all 288 source/object snapshots and compiler outputs,
full-config private projects/reports, `scored-manifest.json`, selection and
full-build logs, symbolic audit and host harness. Original objects and
disassembly remain private. The enumeration has an exclusive started marker
and must not be restarted. From this leaf, the read-only evidence checks and
host validation are:

```
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/aoss-decrypt-fixed-neighbors/verify_evidence.py
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/aoss-decrypt-fixed-neighbors/audit_changed_regions.py
python3 /tmp/aoss-decrypt-fixed-neighbors/validate_decrypt.py
```

GATE PASS: strict official-fuzzy partial gain; complete fixed-center coverage;
source semantics and exact/code/data/link preserved; full 43U/default/DOL pass.
