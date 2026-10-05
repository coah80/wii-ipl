# WUD stored-device deletion wait

Original validation base: `f18082e88b680072eaeafbd8f6fe11c6198b9200`.
Current leaf base after mechanical rebase: `f762dfef` (PRs #1233–#1235).
Leaf: `agent/fix/wud-deletion-wait`.

## Defect and correction

The `_WUDDeleteStoredDevice` routine added in PR #1232 is absent from the 43U
retail object and final ELF. Its empty loop reads the nonvolatile
`WUDCB::deleteState` field. MWCC hoists the load to `.text+0x581c`; the compare at
`0x5820` and backward branch at `0x5824` repeatedly test the same register.
If deletion is still pending on the first read, later completion cannot release
the caller.

The field genuinely crosses execution contexts:

- `WUDiDeleteAllLinkKeys` asks the registered clear-device callback to act, or
  calls `WUDStartClearDevice` when there is no callback
- `WUDStartClearDevice` checks library/busy state, sets deletion state 1 with
  interrupts disabled, and installs `DeleteAllHandler0` as a 20 ms periodic alarm
- The alarm runs `DeleteAllHandler` through the WUD handler fiber. It advances
  states 1, 2, 3, and 5; state 3 can wait for links, and state 5 can wait for SC
- `WUDiCleanUp` advances to 6 before asynchronous settings flush, or directly to
  8 when neither settings write succeeds. `DeleteFlushCallback` advances to 8
  for either flush success or failure, unless already idle
- The next alarm's `WUDiDeleteAllComplete` cancels the alarm and restores state 0

The correction snapshots `deleteState` between `OSDisableInterrupts` and
`OSRestoreInterrupts` on every iteration, using the established WUD access
pattern. The saved interrupt state is restored before testing the snapshot.
No declaration-wide qualifier, use-site cast, fake state, dummy operation,
assembly, compiler flag, or matching classification is introduced.

The resulting MWCC loop is:

```text
0x581c  bl      OSDisableInterrupts
0x5820  lbz     r28,0xd(r30)
0x5824  bl      OSRestoreInterrupts
0x5828  cmpwi   r28,0
0x582c  bne     0x581c
```

The load preserves the saved interrupt state in r3 for `OSRestoreInterrupts`.
An interrupt can advance the state after restoration; the next iteration then
reloads it. This remains a blocking helper: pending work still requires the
normal interrupt/callback machinery to run. No timeout, cancellation, or error
reporting contract is invented.

## Original snapshot validation

The unmodified `f18082e8` base was fully rebuilt in this leaf for 43U before editing.
Its report, WUD object, all source-object hashes, ELF and DOL were preserved.
The candidate passed a full build, report generation and `build/43U/ok` using
the recovered tools and `../wii-toolchain-venv`. The measurements below compare
that original candidate against its `f18082e8` snapshot, not against later main
revisions.

- Every report entry and global measure is byte-for-byte unchanged. WUD remains
  66/66 retail functions, 18,852/18,852 code bytes, and 12,016/12,016 data bytes;
  matching and linkage are all 100%
- All 66 retail functions have identical raw instruction bytes and resolved
  relocation identities against the original object: 4,713 instructions,
  zero differences
- All 92 other compiled source functions retain their baseline raw instruction
  bytes and resolved relocation identities. Only the non-retail wait changes,
  from 126 to 128 instructions
- Only WUD.o changes among 1,027 source objects. Every allocated WUD data section
  and its relocations are identical to the baseline
- The existing source-versus-retail data extent differences are unchanged:
  `.data`, `.sbss` and `.sdata2` omit trailing alignment zeroes; `.sdata` retains
  the non-retail `start\n` string. Shared extents and data relocation referents
  match the retail object, and final linked bytes are unchanged
- Pool audit: 107/107 strings, no divergence. Direct-call audit: 511/511 calls
  preserve destinations, no skips or errors. Literal-reference audit: 66
  functions, no candidates, skips or errors. DeleteAllHandler's jump table:
  9/9 entries match
- Every ELF section header and all section bytes except `.strtab` are identical
  to the baseline. The only `.strtab` changes are non-allocated compiler-generated
  `@NNNN` label names. Raw ctxdiff reports such label-name differences, including
  ones already present before this fix; the raw-byte/resolved-relocation audit
  verifies their actual instruction and referent equality
- DOL bytes are identical to the baseline; SHA1 remains
  `26116613f624061ba99c8d1a299aaa6efa85670d`
- `git diff --check` passes

`verify_wud_delete_wait.py` extracts the actual wait, request, busy-state,
cleanup, flush-callback and completion functions into a bounded host harness.
It models alarm delivery only after interrupt restoration, with delayed link
drain and settings completion. It covers normal asynchronous completion, SC
busy retries, failed flush, both settings writes failing, either write failing,
library rejection, unrelated busy state, callback-owned requests, an already
active deletion, idle calls with interrupts disabled, and late flush callbacks.
The candidate passes; the baseline times out on the pending-deletion case.
This is not Wii hardware or complete Bluetooth emulation.

Re-run the host and MWCC loop checks from this leaf:

```sh
../wii-toolchain-venv/bin/python tools/decomp-assist/verify_wud_delete_wait.py \
  --object build/43U/src/libs/RVL_SDK/src/wud/WUD.o
```

Original-snapshot evidence is under `build/wud-deletion-review/`: baseline/candidate objects,
reports and build logs, object-hash lists, disassemblies, pool/call/literal/jump
audits, positive and negative host-test results, `validate_objects.py`, and
`validation.json`. The baseline files and validator still refer to `f18082e8`;
they must not be mistaken for a fresh `f762dfef` comparison.

## Rebase and independent verification

The parent independently forced the original candidate's build and reran the
host/compiled-loop checks and object audit successfully. PRs #1233–#1235 then
advanced main to `f762dfef`. These commits do not change `WUD.c` or
`WUDInternal.h`; the parent mechanically rebased this leaf without changing the
correction or regression test.

The parent is rebuilding the rebased candidate and will compare it with a fresh
`f762dfef` main report and linked bytes before publication. That verification
was still in progress when this documentation-only update was committed; the
original global report equality is not a claim that unrelated incoming work
left global progress unchanged. No competing worker build was started.

The worker performed no push, PR, merge, upload, or upstream action.

ORIGINAL-SNAPSHOT GATE PASS: pending-state reload corrected; retail code, data,
linkage, progress report and DOL preserved. Rebased acceptance belongs to the
parent's fresh verification.
