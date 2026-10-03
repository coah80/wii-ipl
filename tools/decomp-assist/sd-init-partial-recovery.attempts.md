# SD initialization partial recovery

Base: `d170fbb8`, Wii Menu 4.3U only. Unit remains NonMatching; no linking,
configuration, header, symbol, or data edits.

The round-4 log recorded a natural initialized/uninitialized branch form at
93.125%, but discarded it because its 141 instructions did not equal the
144-instruction target. Recover that strictly improving partial under the
current fuzzy-first acceptance rule.

## Trials

1. Keep the already-initialized report first. Return -44 only for another disk;
   put new initialization in the `else` arm and share the final success return.
   `pfd_sddrv_init`: 92.326385 -> 93.125%, 141/144 instructions. Retained.
2. Historical explicit status-result form: set the real return status to zero,
   assign -44 for another disk, then return it. 92.94444%, 142/144 instructions.
   Reverted in favor of trial 1. No wider source search was performed.

The target at 0x815EA638 uses a conditional disk-identity branch. The baseline
compiler instead emits a branchless subtraction/NOR selector. The retained
ordinary control flow recovers the conditional comparison. It still shares the
success exit, whereas the target contains a separate success load/branch. The
initial null comparison and existing state-store scheduling differences also
remain. This is a partial improvement, not an exact match.

## Behavior review

The null-disk return is unchanged. An initialized driver still reports its
state, succeeds only for the registered disk, and returns -44 for a different
disk. Only an uninitialized driver reaches initialization. Every call, field
write, error return, and callback selection in that path is unchanged and in
the same source order. No local, initializer, or artificial operation was added.

A host-compiled differential oracle extracts the actual baseline and candidate
function bodies and supplies deterministic SDK stubs. All 279,936 combinations
pass: 16 flag values, three insertion values, null/same/different input and
registered disks, four device-status bit patterns, all 81 combinations of
zero/negative/positive results from the four fallible SDK operations, and two
mounted-device identities. It compares return status, the complete driver
record, device storage, event value, and ordered external-call trace. This
checks source behavior, not hardware execution or instruction matching.

## Final gates

- Full `all_source progress build/43U/report.json build/43U/ok` build passes.
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`.
- String pool: all 46 payloads and offsets identical to the target.
- All 25 other function instruction streams unchanged from the fresh base.
- Unit: 22/26 exact functions and 9260/11760 exact code bytes, unchanged.
- Unit data: 3592/3592 matched bytes, unchanged.
- Unit fuzzy: 99.10204 -> 99.14116%.
- Global fuzzy: 99.724495 -> 99.72465%; exact, data, and linked totals unchanged.
- Whole-report regressions: zero; only this unit's fuzzy score changes.
- All 1027 allocated-object comparisons: only this unit's `.text` changes;
  every non-code section and relocation stream is unchanged.
- Eight workflow-guard tests pass; `git diff --check` passes.
