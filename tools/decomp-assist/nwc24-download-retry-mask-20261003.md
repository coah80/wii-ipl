# NWC24Download source and retry-mask audit, 2026-10-03

Baseline: 1fa33882. Read AGENTS, CONTRIBUTING, NWC24Download, pk2, fz10,
and structural round 10/12 attempt records. PR #954 is already present.
Only libs/RevoEX/src/nwc24/NWC24Download.c changes, plus this evidence file.

## Retained correction

CheckDlTaskRetry accepts retry counts 0 through 31 and reads a u32 mask.
The reconstructed `1 << retryCount` has undefined signed-left-shift behavior
at count 31. Use `1U << retryCount` to express the target's 32-bit mask.
The target checks the upper bound before shifting; that order stays intact.

The full compiled object is byte-identical to the baseline, SHA256:
85cc303983a219bdb34b3765ecc3a352fade4238e1ce911a7cba8078e3e9b42a
This is a source-definedness correction, not a fuzzy or exact-match gain.

## Semantic coverage and remaining differences

- NWC24InitDlTask: all 144 instructions have the same operations, constants,
  branch destinations and relocation targets after register normalization.
  Home-path parsing, identifier halves, byte/halfword task stores, default
  intervals, content filename, and permission-result propagation agree.
- NWC24iCheckDlHeaderConsistency: 212/212 instructions; its only differences
  are scheduling three entry instructions. Repair dispatch, signed subtask
  halfword test, read/delete contracts and error branches agree.
- NWC24UpdateDlTask: reviewed both permission checks, time retrieval and signed
  64-bit division by 60, task/header validation, reset stores, retry error
  constants, mask handling and StoreDlTask arguments. The target's repeated
  work/header reads and retry-field accesses are present. Remaining shape
  differences concern saved lifetimes/frame and equivalent retry branches.
- AddTaskInternal: reviewed URL validation, update path, free-slot bounds and
  16-byte entry addressing, task-ID halfword stores, purge error propagation,
  and repeated lookup/update control flow. No omitted call, wrong field
  offset, or different error constant was found.
- The task record is 0x200 bytes; retry count/enabled/mask offsets are
  0x24/0x25/0x28. The list has a 0x80-byte prefix and 120 0x10-byte entries,
  matching its 0x800-byte read/write contract.

## Rejected investigations

All are restored; none is part of the retained source diff.

- Widening AddTaskInternal/FindFreeDlTask bounds to u32 while retaining the
  halfword loop cursor: Add 97.7182% -> 97.14464%.
- Reusing the existing CheckDlUrlString helper in ValidateDlTaskUrl:
  Add 97.7182% -> 96.38404%. The shared helper did not recover the original
  inlined error boundary.
- Shared group permission helper taking a const task and an explicit nested
  boolean: Update 95.00395% -> 98.81423%, Init -> 99.02778%, but five exact
  sibling functions regressed and Add fell to 97.58105%. No special-purpose
  update-only copy was introduced to isolate allocation effects.
- Wide bounds with a wide search cursor initially narrowed to NWC24DlId:
  Add -> 98.0424%. This did not establish the original bounds contract or
  recover the complete loop form, so the existing types were preserved.

Prior logs already contain stronger but discarded Update helper-boundary
scores, including 99.48617%. Those are historical results, not new gains.
No register/declaration sweep, qualifier trick, dummy storage, new assembly,
header change, or linking change was used.

## Verification

- Configured only 43U with ../toolchain/wibo-build/wibo
- WIBO_SJIS_MISSING_IMPORTS=1 ../.venv/bin/ninja all_source build/43U/report.json build/43U/ok
- Complete object and complete project report identical to the fresh baseline
- All 26 exact functions compared with relocation-aware ctxdiff: zero differences
- Pool: identical, 3/3 strings
- Literal audit: 4 arguments, 26 functions, no skips/candidates/errors
- Exact code 8456/12496, exact functions 26/30, data 80/80 and fuzzy 99.169655%, unchanged
- DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d
- git diff --check passes

A native C11 harness extracts the actual helper, task layout and error enum,
with a validation-result stub. GCC -O2 -Wall -Wextra -Werror and UBSan checks
270336 combinations: every u8 count, 66 zero/all/one-hot/complement masks,
four enabled values and four validation outcomes. It uses an independent
right-shift predicate as its expected mask result. All retained-helper cases
and layout assertions pass. The otherwise identical baseline harness fails
at count 31: signed left shift cannot be represented in int.

Local harness: /tmp/nwc24-retry-mask-test.c (executable without .c).
Baseline reproducer: /tmp/nwc24-retry-mask-baseline-test.c.
These test the local retry predicate, not filesystem or network integration.

GATE: byte preservation, exact-function/data preservation, complete-report
nonregression, pool, literals, native UBSan and full 43U/DOL checks pass.
