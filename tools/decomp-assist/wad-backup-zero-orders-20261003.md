# WADBackupEx bounded zero-initialization search (2026-10-03)

## Retained change and result

Move only the existing `outputBuffer = 0;` assignment ahead of `files = 0;` in
`WADBackupEx`. All declarations, other statements, cleanup initialization,
control flow, types, calls and data definitions are unchanged.

Base: `49be1c79c5ad6869edbc2b5655359ae655e93aa5`.
Function official fuzzy: **97.370995% -> 97.38042%**.
Unit official fuzzy: **98.94155% -> 98.943184%**.
Function source/target remain 1057/1062 instructions; frame remains the same
64-byte-aligned 0x8C0 allocation. Unit exact functions remain 35/40, matched code
13,180/24,500, exact data 528/528, and link status unchanged. This is a verified
fuzzy gain, not an exact function or linking gain.

## Historical lead and the new hypothesis

`data-d5.attempts.md:122` records an earlier 97.37571% result from reordering
independent metadata/cache zero initializations, restored under an exact-only
gate. The exact source order was not recovered. Its recorded temporary files
are absent. Both the worker and squash commits for data-d5b/data-d5c change only
symbols and logs; their WADBackupEx bodies equal the current baseline. Sixty-four
reachable WAD source-history commits were checked, including separate unmerged
WAD variants, without recovering that order.

This experiment is a **new fixed hypothesis**, not a reconstruction of the old
variant. Twenty-one orders reproduced the old numeric score, which does not
identify the historical source. The selected order scored better.

The approved region was the 11 existing zero assignments at baseline lines
1261–1271. Canonical indices:

0. `titleMetaSize = 0;`
1. `contentDataSize = 0;`
2. `titleMetaBuffer = 0;`
3. `titleMeta = 0;`
4. `files = 0;`
5. `fileCount = 0;`
6. `importedSize = 0;`
7. `outputBuffer = 0;`
8. `encryptionBuffer = 0;`
9. `fileDataSize = 0;`
10. `installedContentCount = 0;`

Exactly 146 unique orders: baseline + 55 transpositions + 100 distinct
single-element insertions - 10 adjacent-swap overlaps. No adaptive search,
additional forms, proxy filtering, or object-based skipping occurred. Every
order was actually compiled and individually officially scored.

Selected order 117: `0,1,2,3,7,4,5,6,8,9,10`. It was the unique highest-scoring
order in this set. Seventy-four distinct object hashes were counted only after
all 146 measurements; equal-object candidates were still compiled and scored.

## Source safety and exact actual-code proof

Before modeling, the source region was checked: its left sides are distinct
nonvolatile automatic scalar/pointer locals and every right side is literal
zero. There are no reads, calls, branches, field writes, or address escapes
within or before this block. The existing `threadCreated` initializer and all
following cleanup-flag initializations remain in place. All 11 writes finish
before the first validation branch and before any callback or API can observe
the locals. Thus the source change merely commutes independent local writes;
no allocator, pointer alias, synchronization, or failure behavior is changed.

The final object differs from baseline at exactly these instruction positions:

| Instruction | Baseline | Selected |
|---:|---|---|
| 18 | `li r25, 0` | `li r24, 0` |
| 19 | `stw r0, 0x68(r1)` | identical |
| 20 | `li r21, 0` | `li r25, 0` |
| 21 | `li r24, 0` | `li r21, 0` |

The actual four-instruction window was symbolically executed from arbitrary
incoming GPR values. Both versions produce the identical store to r1+0x68 using
unchanged r0, then identical final register states with r21, r24 and r25 zero.
The store neither reads nor changes those three registers. This proof makes no
memory-disjointness or caller-pointer alias assumption. `li` and `stw` leave
CR/LR/CTR/XER unchanged. There is no branch into the window or its interior.

Every instruction before index 18 and after index 21 is byte-identical. The
prologue has already saved the same callee-saved registers before these writes;
frame construction, saved argument lifetimes and epilogue are unchanged. At the
window exit the complete architectural state is identical. Consequently all
later branch decisions, loads/stores, globals, arguments, callbacks, allocator
operations, lock/wait/cancel/join paths, failures, and cleanup traces are the
same as baseline, including every loop iteration. All 99 call sites retain
their exact instructions, relocation targets and positions. This is an exact
local machine-state proof with identical continuations, not whole-Wii runtime
execution or a claim that pre-existing baseline behavior has been repaired.

Only five bytes in the entire ELF object changed, all within those three `li`
words. All other bytes are identical, including every sibling function,
nontext section, section header, symbol, relocation, extent and alignment.
All 35 official exact functions were independently disassembled against the
original with zero symbolic instruction differences. All 39 sibling function
reports and all other 1,026 whole source objects remain unchanged.

## Baseline, final build, and original-target evidence

The current-main cache was copied independently before any candidate: all 3,125
copied build files had different inodes and matching contents. Immutable source,
source/target objects, full report, and 1,027-object hash manifest were saved.
A normal baseline build actually compiled all 1,027 source objects and then
reproduced the entire frozen object set and full official report byte-for-byte.
This baseline compile/report counts as order 0.

After all orders, the selected source was actually compiled once more. Its
object and complete report exactly reproduce the recorded order-117 snapshot.
All nonfuzzy global metrics and other unit reports are unchanged. Full 43U build,
default build, `build/43U/ok`, and whitespace check passed. Final DOL SHA1:
`26116613f624061ba99c8d1a299aaa6efa85670d`.

Original WADBackupEx: address 0x815C137C, 4,248 bytes. All 965 nonrelocated
instruction words agree with the extracted target. All 92 relocated direct-call
destinations were decoded from real DOL branch words and checked against the
symbol addresses. The source/target ordered call sequence contains the same
92 direct calls plus seven callbacks. The remaining five target relocations
are the two actual path-format string references and export-thread entry
address pair; their corresponding source relocations remain identical to
baseline. The strings `/title/` and `/title/%x/%x` were separately checked in
both source and target sections. Original artifacts stay local.

Pool check: 18/18 identical. Literal audit: 37 functions and 32 arguments, no
candidates/errors. Existing unequal-size skips remain WADImportGetBlocks,
WADBackupEx and WADImportDVDExForBS. For this skipped backup function, unchanged
whole-object data/relocations and the exact state-equivalence proof preserve
all actual literal arguments; both path literals were additionally checked.

## Evidence and reproduction

Private workspace evidence: `../wad-backup-zero-orders-evidence/`. It contains
the fixed runner and order list, immutable baseline, every compiler log, all
146 full XZ-compressed official reports and objects, measurement manifest,
selected-build logs and `verify_selected.py` with its machine-state proof.

Normal cached 43U tools only:

- Configure 43U with existing wrapper, dtk, objdiff, sjiswrap, bstool, compiler
  and binutils paths
- Baseline: `WIBO_SJIS_MISSING_IMPORTS=1 ../.venv/bin/ninja -j4 all_source build/43U/report.json build/43U/ok`
- Each alternate: normal `ninja -v build/43U/src/libs/RVL_SDK/src/wad/wad.o`,
  then `ninja build/43U/report.json`
- Selected final compile: normal all_source/report/ok, followed by default build

The preflight estimated 211.9 MB peak use against 1.621 GB free, preserving the
1.1 GiB floor plus 100 MiB review reserve. The same floor was checked before
every candidate. No compiler options, downloads, remote operations or cache
deletions were performed by this worker.

SHA256 anchors:

- Baseline WADBackupEx body: `6d74fa7f3eb12ef843a5ae08deb5c37bcf37075d9d6dff76d3027a4fae357156`
- Selected full source: `41e3d021105627ae29e54d2b2b67cd14e4b42cb12b6e60346f0caf7917db13b0`
- Selected source object: `558b0b94d293d81ad722b6b3ccd4ba63e1b21e67331bf768257df085616142dc`
- Selected full report: `07ff5d759013734b9a8b32f4e6d5e11db872d5203d9a9d304b3906b22f9f24e0`
- Measurement manifest: `e63835b29ff6ada51be2d35ead480a7e6a4f641ad2ea73cd7b4bca99e47323d8`
- Order list: `200117728c7e698b26e3524f5d08a3c260051a6223c1a9cc251d05f00c4321b1`

## Per-order official results

Indices reference the canonical assignment list above. Each row was separately
compiled and officially scored.

| Order | Assignment indices | Official fuzzy |
|---:|---|---:|
| 0 | 0,1,2,3,4,5,6,7,8,9,10 | 97.370995 |
| 1 | 1,0,2,3,4,5,6,7,8,9,10 | 97.36912 |
| 2 | 2,1,0,3,4,5,6,7,8,9,10 | 97.36912 |
| 3 | 3,1,2,0,4,5,6,7,8,9,10 | 97.36912 |
| 4 | 4,1,2,3,0,5,6,7,8,9,10 | 97.373825 |
| 5 | 5,1,2,3,4,0,6,7,8,9,10 | 97.36912 |
| 6 | 6,1,2,3,4,5,0,7,8,9,10 | 97.36817 |
| 7 | 7,1,2,3,4,5,6,0,8,9,10 | 97.37288 |
| 8 | 8,1,2,3,4,5,6,7,0,9,10 | 97.37288 |
| 9 | 9,1,2,3,4,5,6,7,8,0,10 | 97.36912 |
| 10 | 10,1,2,3,4,5,6,7,8,9,0 | 97.36912 |
| 11 | 0,2,1,3,4,5,6,7,8,9,10 | 97.370995 |
| 12 | 0,3,2,1,4,5,6,7,8,9,10 | 97.370995 |
| 13 | 0,4,2,3,1,5,6,7,8,9,10 | 97.37571 |
| 14 | 0,5,2,3,4,1,6,7,8,9,10 | 97.36912 |
| 15 | 0,6,2,3,4,5,1,7,8,9,10 | 97.36912 |
| 16 | 0,7,2,3,4,5,6,1,8,9,10 | 97.373825 |
| 17 | 0,8,2,3,4,5,6,7,1,9,10 | 97.373825 |
| 18 | 0,9,2,3,4,5,6,7,8,1,10 | 97.36912 |
| 19 | 0,10,2,3,4,5,6,7,8,9,1 | 97.36912 |
| 20 | 0,1,3,2,4,5,6,7,8,9,10 | 97.370995 |
| 21 | 0,1,4,3,2,5,6,7,8,9,10 | 97.37571 |
| 22 | 0,1,5,3,4,2,6,7,8,9,10 | 97.370995 |
| 23 | 0,1,6,3,4,5,2,7,8,9,10 | 97.370995 |
| 24 | 0,1,7,3,4,5,6,2,8,9,10 | 97.370995 |
| 25 | 0,1,8,3,4,5,6,7,2,9,10 | 97.370995 |
| 26 | 0,1,9,3,4,5,6,7,8,2,10 | 97.36912 |
| 27 | 0,1,10,3,4,5,6,7,8,9,2 | 97.36817 |
| 28 | 0,1,2,4,3,5,6,7,8,9,10 | 97.370995 |
| 29 | 0,1,2,5,4,3,6,7,8,9,10 | 97.370995 |
| 30 | 0,1,2,6,4,5,3,7,8,9,10 | 97.370995 |
| 31 | 0,1,2,7,4,5,6,3,8,9,10 | 97.370995 |
| 32 | 0,1,2,8,4,5,6,7,3,9,10 | 97.370995 |
| 33 | 0,1,2,9,4,5,6,7,8,3,10 | 97.36912 |
| 34 | 0,1,2,10,4,5,6,7,8,9,3 | 97.36817 |
| 35 | 0,1,2,3,5,4,6,7,8,9,10 | 97.370995 |
| 36 | 0,1,2,3,6,5,4,7,8,9,10 | 97.370995 |
| 37 | 0,1,2,3,7,5,6,4,8,9,10 | 97.37571 |
| 38 | 0,1,2,3,8,5,6,7,4,9,10 | 97.370995 |
| 39 | 0,1,2,3,9,5,6,7,8,4,10 | 97.36912 |
| 40 | 0,1,2,3,10,5,6,7,8,9,4 | 97.36817 |
| 41 | 0,1,2,3,4,6,5,7,8,9,10 | 97.370995 |
| 42 | 0,1,2,3,4,7,6,5,8,9,10 | 97.37571 |
| 43 | 0,1,2,3,4,8,6,7,5,9,10 | 97.37571 |
| 44 | 0,1,2,3,4,9,6,7,8,5,10 | 97.36912 |
| 45 | 0,1,2,3,4,10,6,7,8,9,5 | 97.36912 |
| 46 | 0,1,2,3,4,5,7,6,8,9,10 | 97.37571 |
| 47 | 0,1,2,3,4,5,8,7,6,9,10 | 97.370995 |
| 48 | 0,1,2,3,4,5,9,7,8,6,10 | 97.370995 |
| 49 | 0,1,2,3,4,5,10,7,8,9,6 | 97.36912 |
| 50 | 0,1,2,3,4,5,6,8,7,9,10 | 97.370995 |
| 51 | 0,1,2,3,4,5,6,9,8,7,10 | 97.370995 |
| 52 | 0,1,2,3,4,5,6,10,8,9,7 | 97.36912 |
| 53 | 0,1,2,3,4,5,6,7,9,8,10 | 97.370995 |
| 54 | 0,1,2,3,4,5,6,7,10,9,8 | 97.36912 |
| 55 | 0,1,2,3,4,5,6,7,8,10,9 | 97.36912 |
| 56 | 1,2,0,3,4,5,6,7,8,9,10 | 97.36912 |
| 57 | 1,2,3,0,4,5,6,7,8,9,10 | 97.36912 |
| 58 | 1,2,3,4,0,5,6,7,8,9,10 | 97.36912 |
| 59 | 1,2,3,4,5,0,6,7,8,9,10 | 97.36817 |
| 60 | 1,2,3,4,5,6,0,7,8,9,10 | 97.36817 |
| 61 | 1,2,3,4,5,6,7,0,8,9,10 | 97.36817 |
| 62 | 1,2,3,4,5,6,7,8,0,9,10 | 97.36817 |
| 63 | 1,2,3,4,5,6,7,8,9,0,10 | 97.36723 |
| 64 | 1,2,3,4,5,6,7,8,9,10,0 | 97.36629 |
| 65 | 0,2,3,1,4,5,6,7,8,9,10 | 97.370995 |
| 66 | 0,2,3,4,1,5,6,7,8,9,10 | 97.370995 |
| 67 | 0,2,3,4,5,1,6,7,8,9,10 | 97.36912 |
| 68 | 0,2,3,4,5,6,1,7,8,9,10 | 97.36912 |
| 69 | 0,2,3,4,5,6,7,1,8,9,10 | 97.36912 |
| 70 | 0,2,3,4,5,6,7,8,1,9,10 | 97.36912 |
| 71 | 0,2,3,4,5,6,7,8,9,1,10 | 97.36817 |
| 72 | 0,2,3,4,5,6,7,8,9,10,1 | 97.36723 |
| 73 | 2,0,1,3,4,5,6,7,8,9,10 | 97.370995 |
| 74 | 0,1,3,4,2,5,6,7,8,9,10 | 97.370995 |
| 75 | 0,1,3,4,5,2,6,7,8,9,10 | 97.370995 |
| 76 | 0,1,3,4,5,6,2,7,8,9,10 | 97.370995 |
| 77 | 0,1,3,4,5,6,7,2,8,9,10 | 97.370995 |
| 78 | 0,1,3,4,5,6,7,8,2,9,10 | 97.370995 |
| 79 | 0,1,3,4,5,6,7,8,9,2,10 | 97.370995 |
| 80 | 0,1,3,4,5,6,7,8,9,10,2 | 97.370995 |
| 81 | 3,0,1,2,4,5,6,7,8,9,10 | 97.370995 |
| 82 | 0,3,1,2,4,5,6,7,8,9,10 | 97.370995 |
| 83 | 0,1,2,4,5,3,6,7,8,9,10 | 97.370995 |
| 84 | 0,1,2,4,5,6,3,7,8,9,10 | 97.370995 |
| 85 | 0,1,2,4,5,6,7,3,8,9,10 | 97.370995 |
| 86 | 0,1,2,4,5,6,7,8,3,9,10 | 97.370995 |
| 87 | 0,1,2,4,5,6,7,8,9,3,10 | 97.370995 |
| 88 | 0,1,2,4,5,6,7,8,9,10,3 | 97.370995 |
| 89 | 4,0,1,2,3,5,6,7,8,9,10 | 97.37571 |
| 90 | 0,4,1,2,3,5,6,7,8,9,10 | 97.37571 |
| 91 | 0,1,4,2,3,5,6,7,8,9,10 | 97.37571 |
| 92 | 0,1,2,3,5,6,4,7,8,9,10 | 97.370995 |
| 93 | 0,1,2,3,5,6,7,4,8,9,10 | 97.370995 |
| 94 | 0,1,2,3,5,6,7,8,4,9,10 | 97.370995 |
| 95 | 0,1,2,3,5,6,7,8,9,4,10 | 97.370995 |
| 96 | 0,1,2,3,5,6,7,8,9,10,4 | 97.370995 |
| 97 | 5,0,1,2,3,4,6,7,8,9,10 | 97.36817 |
| 98 | 0,5,1,2,3,4,6,7,8,9,10 | 97.36912 |
| 99 | 0,1,5,2,3,4,6,7,8,9,10 | 97.370995 |
| 100 | 0,1,2,5,3,4,6,7,8,9,10 | 97.370995 |
| 101 | 0,1,2,3,4,6,7,5,8,9,10 | 97.370995 |
| 102 | 0,1,2,3,4,6,7,8,5,9,10 | 97.370995 |
| 103 | 0,1,2,3,4,6,7,8,9,5,10 | 97.36912 |
| 104 | 0,1,2,3,4,6,7,8,9,10,5 | 97.36817 |
| 105 | 6,0,1,2,3,4,5,7,8,9,10 | 97.370995 |
| 106 | 0,6,1,2,3,4,5,7,8,9,10 | 97.370995 |
| 107 | 0,1,6,2,3,4,5,7,8,9,10 | 97.370995 |
| 108 | 0,1,2,6,3,4,5,7,8,9,10 | 97.370995 |
| 109 | 0,1,2,3,6,4,5,7,8,9,10 | 97.370995 |
| 110 | 0,1,2,3,4,5,7,8,6,9,10 | 97.370995 |
| 111 | 0,1,2,3,4,5,7,8,9,6,10 | 97.370995 |
| 112 | 0,1,2,3,4,5,7,8,9,10,6 | 97.370995 |
| 113 | 7,0,1,2,3,4,5,6,8,9,10 | 97.37571 |
| 114 | 0,7,1,2,3,4,5,6,8,9,10 | 97.37571 |
| 115 | 0,1,7,2,3,4,5,6,8,9,10 | 97.37571 |
| 116 | 0,1,2,7,3,4,5,6,8,9,10 | 97.37571 |
| 117 | 0,1,2,3,7,4,5,6,8,9,10 | 97.38042 |
| 118 | 0,1,2,3,4,7,5,6,8,9,10 | 97.37571 |
| 119 | 0,1,2,3,4,5,6,8,9,7,10 | 97.370995 |
| 120 | 0,1,2,3,4,5,6,8,9,10,7 | 97.370995 |
| 121 | 8,0,1,2,3,4,5,6,7,9,10 | 97.37571 |
| 122 | 0,8,1,2,3,4,5,6,7,9,10 | 97.37571 |
| 123 | 0,1,8,2,3,4,5,6,7,9,10 | 97.37571 |
| 124 | 0,1,2,8,3,4,5,6,7,9,10 | 97.37571 |
| 125 | 0,1,2,3,8,4,5,6,7,9,10 | 97.37571 |
| 126 | 0,1,2,3,4,8,5,6,7,9,10 | 97.37571 |
| 127 | 0,1,2,3,4,5,8,6,7,9,10 | 97.37571 |
| 128 | 0,1,2,3,4,5,6,7,9,10,8 | 97.370995 |
| 129 | 9,0,1,2,3,4,5,6,7,8,10 | 97.36723 |
| 130 | 0,9,1,2,3,4,5,6,7,8,10 | 97.36817 |
| 131 | 0,1,9,2,3,4,5,6,7,8,10 | 97.36912 |
| 132 | 0,1,2,9,3,4,5,6,7,8,10 | 97.36912 |
| 133 | 0,1,2,3,9,4,5,6,7,8,10 | 97.36912 |
| 134 | 0,1,2,3,4,9,5,6,7,8,10 | 97.36912 |
| 135 | 0,1,2,3,4,5,9,6,7,8,10 | 97.370995 |
| 136 | 0,1,2,3,4,5,6,9,7,8,10 | 97.370995 |
| 137 | 10,0,1,2,3,4,5,6,7,8,9 | 97.36629 |
| 138 | 0,10,1,2,3,4,5,6,7,8,9 | 97.36723 |
| 139 | 0,1,10,2,3,4,5,6,7,8,9 | 97.36817 |
| 140 | 0,1,2,10,3,4,5,6,7,8,9 | 97.36817 |
| 141 | 0,1,2,3,10,4,5,6,7,8,9 | 97.36817 |
| 142 | 0,1,2,3,4,10,5,6,7,8,9 | 97.36817 |
| 143 | 0,1,2,3,4,5,10,6,7,8,9 | 97.36912 |
| 144 | 0,1,2,3,4,5,6,10,7,8,9 | 97.36912 |
| 145 | 0,1,2,3,4,5,6,7,10,8,9 | 97.36912 |

GATE: strict official fuzzy gain; source-only assignment movement; exact machine-state equivalence and complete ELF accounting; 35 exact functions, 528 data bytes, all siblings/link metrics preserved; full 43U and DOL passed. Awaiting independent parent review; no remote actions.
