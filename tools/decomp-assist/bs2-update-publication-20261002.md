# BS2 update-thread publication recovery, 2026-10-02

Baseline b26e248b. Source-only candidate in src/BS2/BS2Update.c.
The assignment's .cpp spelling was checked; this unit is C.

## Retained target-proven declarations

- EntriesCount: original UpdateThread object offsets 0xC2C/0xC30 store the
  selected count then immediately reload it, with no intervening call or store.
  The old source tests the still-live local count and omits that reload.
  Definition-level volatile restores the published global read.
- State: target writes the failure state at 0x4F4 and 0xB4C before joining
  selection completion. The zero-selection exit writes State=5 again at 0xC44.
  The old source loses the first two store sequences because MWCC sees a later
  overwrite without an intervening function call. Definition-level volatile
  restores both observable failure-state publications. State is also exposed
  through BS2UpdateState for polling by the boot state machine.

These are real existing state objects. No use-site qualifier casts, added
storage, fabricated barriers, assembly, metadata, or linking changes.

## Measurements

| Source form | UpdateThread fuzzy | Instructions |
| --- | ---: | ---: |
| Baseline | 93.59803% | 904/913 |
| EntriesCount publication reread | 93.90471% | 905/913 |
| Also preserve State publications | 94.5575% | 909/913 |

Unit fuzzy improves 94.23001% -> 95.094765%. Exact code remains 400/4052,
exact functions 9/10, data 10488/10488. This is partial source reconstruction,
not an exact function or linking candidate.

Rejected independent source-structure experiments, based on the count-reread
candidate: explicit selected-entry byte progression (93.73275%, 905/913),
seatholder byte progression (93.47755%, 905/913), and separate disc-base
expressions in error logging (93.56955%, 905/913). All were restored. The
remaining four missing target instructions are a repeated entry.type read and
three address-materialization differences. Register allocation and scheduling
also differ. The type declaration requires separate shared-header review.

## Fresh verification

- Configured only 43U with ../toolchain/wibo-build/wibo
- WIBO_SJIS_MISSING_IMPORTS=1 ../.venv/bin/ninja all_source build/43U/report.json build/43U/ok
- Pool: 55/55 identical
- Exact-name report and fresh ctxdiff preserve all nine exact functions
- Literal audit: 5 arguments across 9 exact functions, no skips/candidates/errors
- Every other unit's complete report unchanged; no per-function regression
- All four data sections still report 100%
- git diff --check passes
- DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d

GATE: source-only nonregression/build/pool/DOL checks pass. Awaiting independent
parent review; no complete decompilation, matching, or linking claim.

## Separate shared entry-type declaration

Parent authorized a separate experiment on the actual shared type declaration,
without a translation-unit-specific qualifier. Changed BS2UpdateEntry.type to
vu32 in include/BS2/BS2Update.h for every consumer.

Original UpdateThread offsets 0xCE8 and 0xD00 read the same entry.type field.
Between them are only the type-zero branch and its skipped increment/continue
path: the nonzero path has no call or write that could require a normal reload.
The shared declaration restores that second observable read. No new guard or
use-site qualifier cast was introduced.

- UpdateThread: 94.5575% -> 94.66265%, 909 -> 910/913 instructions
- Overall from initial baseline: 93.59803% -> 94.66265%, 904 -> 910/913
- Unit fuzzy: 94.23001% -> 95.18954%
- Exact functions remain 9/10 and code remains 400/4052
- Data remains 10488/10488, with every allocated non-text byte unchanged

All generated source objects were deleted and rebuilt with the configured 43U
all_source/report/ok targets. The prior cache had 1028 objects, including an
obsolete keyboard/tiManager.o absent from build.ninja, objdiff.json, and
configure.py. The current build graph cleanly rebuilt all 1027 configured
objects. Hash comparison of those objects against the source-only checkpoint
found only BS2Update.o changed. All 1026 other unit reports are identical.
This includes every shared-header consumer; none needed source adjustment.

Fresh final pool: 55/55 identical. Literal audit: 5 arguments across 9 exact
functions, no skips/candidates/errors. Fresh ctxdiff preserves all 9 exact
functions. DOL SHA1 remains 26116613f624061ba99c8d1a299aaa6efa85670d.
git diff --check passes.

The final three missing target instructions are address materializations:
seatholder table construction uses separate load/add in the target, and both
error-log calls materialize their own disc-table base. These are not omitted
source operations; register and scheduling differences remain as well. No
register sweep or artificial materialization was retained.

GATE: clean all-source build, cross-unit/object nonregression, complete data,
pool, exact-function preservation, and DOL checks pass. Leaf frozen for
independent parent review. Both commits are partial reconstruction gains.
