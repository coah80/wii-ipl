# Restore unresolved launch/delete placeholders

Original validation base: `1fd097072852bed32c47c51795fcc0204b8ed5ed` (fork PR #1243).
Current leaf base after mechanical rebase: `c3dbaf8c8ec41e7c48bd0e93c895c97e089de65d`
(fork PRs #1244–#1245).
This is a corrective rollback of unsupported source, not a recovered launch or
shared-content deletion implementation. No new match or completion is claimed.

## Scope and reason

Restore these files exactly, leaving all other production files unchanged:

- `libs/RVL_SDK/src/os/OSExec.c` from `712bd2f^` (before PR #1242)
- `src/utility/iplESMisc.cpp` and `include/utility/iplESMisc.h` from `1fd0970^`
  (before PR #1243)

The restored `DECOMP_FORCE_ACTIVE` blocks are known string-retention
placeholders. They preserve the observed literal bytes and ordering; they do
not reconstruct the missing owners or advertise callable replacement APIs.
The earlier `grok-osexec.attempts.md` and `grok-esmisc.attempts.md` remain as
history, but their passing retail gates do not validate the discarded bodies.

The added bodies have no counterparts in the 43U retail objects or final ELF.
Neither their attempts logs nor the reviewed PR evidence provides a pinned
source, original disassembly, or recovered contract for those implementations.
The earlier `rx67b.classification.md` also records these reconstruction gaps.
The concrete blockers in the original validation base include:

- Different-partition launches can pass uninitialized ticket/TMD buffers and a
  zero TMD length to `DVDLowOpenPartitionWithTmdAndTicketView`
- `ESP_CloseLib` precedes the play-time query that requires its open descriptor;
  failed ticket acquisition can also leave the query's ticket uninitialized
- DVDLow submission failures are ignored before waiting for a callback, although
  rejected asynchronous requests can return without scheduling that callback
- The public launch paths return after firmware reload/reopen without loading
  an apploader/DOL or transferring execution; constructed launch arguments are
  discarded or stored in a BI2 buffer where an `OSExecParams` object is required
- The new public deletion method refers to `ES_DeleteSharedContent`, which has
  no definition/retail symbol in the checkout, and can overwrite an earlier
  deletion failure with a subsequent success

Partition-count bounds, asynchronous disk-ID lifetime/alignment, and TMD
length/count validation have additional unresolved risks. Repairing these
speculatively would still not recover the stripped originals. Pinned recovery
and API-contract evidence is required before replacing the placeholders again.
No runtime regression in the existing linked retail DOL is asserted.

## Original-snapshot 43U validation

The untouched `1fd09707` base was fully rebuilt first in an isolated worktree
using the restored source-built tools. Its entire `build/43U` output was
preserved before restoring the three files. The measurements below compare
original candidate `5a26ca8485a3f7fb25c21d211718143dc401a193` with that base, not
with the later `c3dbaf8c` revision. Only 43U was configured and built.

- Baseline and candidate full Ninja builds, explicit `build/43U/ok`, report and
  progress targets pass
- The complete report is byte-for-byte identical, including every unit,
  function, section and global measure (SHA256
  `b11f5b449a1426e2ebf16edc60ece3dfad28d0204a72de8f06c99a6e93a3c7f0`)
- All 10 retained OSExec functions preserve 3,476 raw instruction bytes and 112
  normalized relocation records; all also equal their retail counterparts
- All 31 retained ESMisc functions preserve 11,200 raw instruction bytes and 357
  normalized relocation records. The existing 30 exact functions remain exact;
  `DeleteUnauthorizedData` remains the same nonmatch (99.14254% fuzzy)
- Literal pools are identical to retail: OSExec 17/17 and ESMisc 114/114.
  Source `.data` and `.sdata` bytes and their relocation sets are unchanged.
  They match retail after the existing trailing zero alignment padding
- Removing OSExec's discarded globals reduces source `.sbss` from 12 to 4
  bytes. The retained `__OSInReboot` object and its referents are unchanged;
  the retail `.sbss` extent is 8 bytes including alignment padding
- 1,004 of 1,027 source objects remain wholly identical. Besides the two owned
  objects, 21 objects have only non-allocated string/debug metadata changes
  from removing the ESMisc declaration. Their allocated bytes and normalized
  relocation records are unchanged
- Every linked ELF section has identical bytes except non-allocated `.strtab`.
  DOL bytes are identical; SHA1 is
  `26116613f624061ba99c8d1a299aaa6efa85670d`
- Direct-call audit: 323/323 same destinations across 40 exact functions, no
  skips/errors. Literal-reference audit: 40 functions, 215 arguments, no
  candidates/skips/errors. The existing nonexact ESMisc function is outside
  those exact-function advisory scans but is covered by the baseline audit
- Stock `ctxdiff.py` cannot import its external `odiff` dependency in this
  environment. The raw-instruction/resolved-relocation audit above supplies
  direct comparison instead; no unavailable ctxdiff result is claimed
- All 20 workflow-guard tests pass; `git diff --check` passes
- The terminal checker correctly returns `DECOMPLETE_FAIL`: code 96.43266%
  exact, 99.86033% fuzzy, 83.58948% linked; data 100% exact and 85.56216% linked;
  12,491/12,563 functions exact and 993/1,027 units complete

Local evidence is under `build/audit-launch/`: baseline outputs, build logs,
`validate_objects.py`, `validation.json`, pool/call/literal audits, status,
workflow tests and the expected incomplete-completion result. The validator
compares all retained function bytes and resolves relocation targets by
function-relative identity or actual data location rather than compiler label
spelling. It also checks the other rebuilt objects and linked allocated bytes.
The saved baseline and validator results refer to the original `1fd09707`
comparison. The validator reads the live candidate build; after rebasing, it
must not be used to claim a fresh `c3dbaf8c` comparison without corresponding
baseline/candidate snapshots. The recovered Python is
`../wii-toolchain-venv/bin/python`; the isolated build helper is
`build/build-43U.sh`.

## Rebase and independent verification

The parent independently forced both owned translation units to rebuild and
reran the direct byte/relocation validator successfully on the original
candidate. PRs #1244 and #1245 then advanced main to `c3dbaf8c`. Those commits
change disjoint parental-settings and board-focus files. The parent
mechanically rebased this leaf to `18c224fd519ce64196814bd119c639c5717a204b`
without changing any of the three restored source/header files.

The parent completed fresh full builds and explicit `build/43U/ok` checks on
both main at `c3dbaf8c` and the rebased candidate. Both pass with DOL SHA1
`26116613f624061ba99c8d1a299aaa6efa85670d`, and their complete reports are
byte-for-byte identical. The detailed all-object comparison above remains
the original `1fd09707` snapshot proof; it is not relabeled as a fresh
all-object comparison against `c3dbaf8c`.

This candidate is a local source correction only. No push, PR, merge, upstream
contact or upload is part of this work.
