# WADBackupEx target-backed owner-zero swap (2026-10-03)

## Retained result

Base: `ae5a5769e1b826f44cddb413170658c36d2a256d`, after the earlier
output-buffer initialization gain and the external EGG linking change.

Only swap the existing `titleMetaBuffer = 0;` and `files = 0;` assignments.
Keep the earlier `outputBuffer = 0;` position, all declarations, cleanup flags,
initializers and every other statement unchanged.

- WADBackupEx: **97.38042% -> 97.385124%**
- Unit fuzzy: **98.943184% -> 98.944%**
- Source/target instructions: 1057/1062, unchanged
- Frame: same 64-byte-aligned 0x8C0 allocation
- Exact functions: 35/40, code 13,180/24,500, data 528/528, link status unchanged

This is a fuzzy gain, not an exact function or linking gain.

## Why this single candidate

The previous fixed 146-order search selected order 117. A read-only comparison
showed that its own immediate 146-order neighborhood overlapped only 15 saved
orders, leaving 131 unmeasured source orders. That alone did not justify another
search. Actual objects showed a narrower opportunity: order 117 matched target
zero-register writes at instructions 18 and 21 but still missed `li r25, 0` at
instruction 16. No saved order matched all three positions simultaneously.
Across the 146 saved objects, only initialization instructions 11–24 changed;
the rest of the function and the set of six zeroed GPRs were unchanged.

Exactly one predicted swap was authorized and compiled. Using the canonical
indices from `wad-backup-zero-orders-20261003.md`, the new order is:
`0,1,4,3,7,2,5,6,8,9,10`.
This is a new target-backed candidate, not a recovered historical variant.
No next-neighborhood search, alternate form, or additional candidate was run.

## Source and actual-code equivalence

Both assignments write literal zero to distinct nonvolatile automatic pointer
locals. There are no intervening reads of either value, calls, address escapes,
branches, or shared-object writes. The entire initial zero block and unchanged
cleanup initialization finish before validation or any callback/API use. No
allocator or pointee state is changed by moving these pointer-local writes.

Only two actual instructions change relative to this task's baseline:

| Index | Baseline | Candidate |
|---:|---|---|
| 16 | `li r14, 0` | `li r25, 0` |
| 20 | `li r25, 0` | `li r14, 0` |

The six-instruction window 16–21 also contains unchanged zero writes to r17,
r24 and r21, and `stw r0, 0x68(r1)`. Symbolic execution from arbitrary incoming
GPR values proves identical register state and the same store event at the
window exit. The store does not use either exchanged register. The proof needs
no memory-disjointness or pointer-alias assumption. These `li`/`stw` instructions
leave CR/LR/CTR/XER unchanged, and no branch enters the window or its interior.

All other instructions are identical. The same saved-register prologue precedes
the window and the same epilogue follows. Thus the ABI, frame, argument
lifetimes, CFG, every subsequent memory/global effect, all allocator operations,
99 call sites, callbacks, lock/wait/cancel/join paths, loop iterations and
failure/cleanup behavior are identical to baseline. This is an exact local
machine-state proof with identical continuations, not whole-Wii execution or a
claim that untouched baseline behavior is corrected.

Only four bytes in the entire ELF object changed, all within those two `li`
words. Every other ELF byte is identical, including nontext payloads, section
headers, symbols, relocations, extents, alignments and all sibling functions.
All 35 exact functions independently retain zero symbolic instruction
differences against the target. All 39 sibling reports, every nonfuzzy global
metric, link metadata and the other 1,026 whole source objects are unchanged.

The predicted third attainable zero-position match was obtained: instructions
16, 18 and 21 now match target. The other target zero destinations are absent
from the fixed source register set observed in the previous search. No further
ordering experiment was inferred or performed.

## Build and original-target gates

Before mutation, all 3,125 current-main build files were copied with independent
inodes and matching content. Original source, source/target objects, full report
and all 1,027 object hashes were frozen read-only. A normal fresh baseline build
actually compiled all 1,027 source objects, then reproduced the entire frozen
object set and full official report byte-for-byte.

Exactly one candidate compile and official report followed. Full all_source,
report/ok and default 43U builds passed. DOL SHA1:
`26116613f624061ba99c8d1a299aaa6efa85670d`.
Pool: 18/18 identical. Literal audit: 37 functions, 32 arguments, no
candidates/errors; existing unequal-size skips remain WADImportGetBlocks,
WADBackupEx and WADImportDVDExForBS. Both backup path literals were additionally
checked against source/target bytes; unchanged data/relocations and exact
machine-state equivalence preserve their actual call arguments.

Original WADBackupEx at 0x815C137C is 4,248 bytes. All 965 nonrelocated words
match the extracted target. All 92 direct-call destinations were independently
decoded from original DOL branch words. Source/target have the same ordered
92 direct calls and seven callback sites. The other five target relocations
cover path literals and the export-thread entry address; corresponding source
relocations are unchanged. Original artifacts remain local.

## Reproduction and evidence

Workspace-only evidence: `../wad-backup-owner-swap-evidence/` contains immutable
baseline artifacts, the one candidate source/object/report, build logs and
`verify_candidate.py` with its actual-instruction symbolic proof.

Normal cached 43U configuration/tools were used. Baseline and candidate builds:
`WIBO_SJIS_MISSING_IMPORTS=1 ../.venv/bin/ninja -j4 all_source build/43U/report.json build/43U/ok`.
Candidate compilation was verbose to record the actual compiler command;
no compiler flags were changed. Default build and diff-check also passed.

Preflight: 1,526,972,416 bytes free, estimated peak use 168 MB, leaving about
73 MB above the required 1.1 GiB floor plus 100 MiB review reserve. The same
floor was checked before the candidate and verification. No remote actions,
downloads, cache deletion or frozen-leaf mutation occurred.

SHA256:

- Candidate source: `77aa40b55e6d5b9e7706ca89c0ea2587b770dc332b3821826a80dd379f30f897`
- Candidate object: `f01582e383157d6ba98197f04bb2d199118c9b6341677950f568f6d2253fedc5`
- Full report: `d623a134d7babd8ac8b22578ceb0882ce02938383cebb45b6a03cda78ab10896`

GATE: one strict official fuzzy gain; exact source/actual-code state equivalence;
35 exact functions, 528 data bytes, all siblings/link metrics preserved;
full 43U and DOL passed. Awaiting independent parent review; no remote actions.
