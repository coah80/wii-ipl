# Version-query workspace formals, 2026-10-03

Base: 9c7d87ab. Owned source: zi8ver.c only. This is source-contract
reconstruction with no percentage gain.

The local declarations in zi8getc2.c already describe Zi8GetVersion,
Zi8GetOEMID and Zi8GetBuildID as taking one ziPtr workspace. The definitions
instead had old-style empty parameter lists. Add only the existing workspace
formal to those three definitions. Bodies, constants, return types, callers
and headers are unchanged.

A fresh scan of all original objects finds exactly four executable references:
Zi8GetEngineSignature calls GetVersion twice, GetOEMID once and GetBuildID
once. There are no other address references or function-pointer escapes.
That caller preserves its incoming second argument, workspace, in r28 and
moves it to the fixed first-argument register r3 immediately before each call.
The workspace register is not redefined between its incoming copy and the
final restore. No argument-register permutation is used for this check.

Each original callee consists of exactly two instructions: load its existing
constant into r3, then return. Thus each overwrites r3 before any read of its
incoming value. There is no helper or tail target. The formal is unused in
this implementation but is established by every declaration and target call;
it adds no local state, storage or assignment.

Fresh configure and baseline/final full 43U builds used the approved wrapper
and WIBO_SJIS_MISSING_IMPORTS=1. Pool first: identical and empty. The entire
owned object, all 1,027 source objects, and the complete 1,027-unit objdiff
report are byte-for-byte / structurally identical to baseline. All allocated
payloads and canonical relocations also match the original target.

Each helper remains 2/2 instructions with ctxdiff-equivalent zero differences.
Unit exact code remains 24/24 bytes and functions 3/3; there are no allocated
data bytes. Full build passes and DOL SHA1 remains
26116613f624061ba99c8d1a299aaa6efa85670d. git diff --check passes.

Private evidence: /tmp/ezi-version-baseline.json,
/tmp/ezi-version-final-report.json, /tmp/ezi-version-final-build.log and
/tmp/ezi-version-verification.txt. No linking, assembly, volatile, forced
registers, dummy assignments, shared-header edits, other-region builds or
remote writes.
