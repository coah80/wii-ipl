# NWC24 writable-task validation recovery, 2026-10-03

Base: `57ccda38`. One bounded source trial in
`libs/RevoEX/src/nwc24/NWC24Download.c`; 43U only. This is a partial
instruction-structure gain, not an exact match, behavior fix or linking change.

## Recovery screening and source rationale

Older exact-only attempts had restored valid partials: pk2 records a task-view
permission helper at 98.695656%; structural round12 records more extensive
permission/access/retry forms up to 99.48617%. Their temporary source artifacts
are absent in this workspace. This candidate was reconstructed from current
source and original instructions, not copied from an unavailable best snapshot.
Only the smallest writable validation operation was tried; no retry helper,
AddTaskInternal, compareToken or ATERM variant was mixed into it.

The new private `ValidateWritableDlTask(const NWC24DlTask*)` returns the same
NWC24Err as the existing validator with write=TRUE. It reads the actual task
view and snapshots its cached header. In the owner-mismatch fallback, it reads
flags and the u16 group ID into operation-local values, initializes a real
permission result false, and makes it true only when bit 0x40 permits the group
query and the IDs match. These values belong to that validation operation;
none is dummy state, an optimization barrier or artificial spill.

Only NWC24UpdateDlTask's two existing writable validation calls use this helper.
The shared validator and all other callers stay unchanged. The second call
reacquires the current header and repeats tool/owner/group permission checks
after the time update. Its failure deliberately suppresses only the two reset
stores, rather than returning early; the original retry/store behavior remains.
No object is allocated, freed or written by the new helper. No pointer escapes,
public type changes, flags, assembly, padding or forced register use is added.

## Original call/data-flow checks

- Target and candidate place all nine direct calls at identical instruction
  indices: tool/app/group queries, universal-time query, signed divide helper,
  repeated tool/app/group queries, final StoreDlTask.
- Tool query precedes owner query, and group query occurs only after both fail
  and flags bit 0x40 is set. The three query callees consume no incoming argument;
  their actual implementations read process/library metadata.
- Both group IDs are loaded before NWC24GetGroupId and compared as u16 after
  the call. Flags are u32; the permission result is BOOL. The task/header are
  read-only, and the cached header lifetime survives the query sequence.
- Null task/header return -3/-9 before metadata queries. Permission failure is
  -7. The 0xFFFF sentinel and u16 maximum-count checks retain their ordering.
- The time-output pointer remains the same eight-byte stack slot; __div2i still
  receives the high/low time words and signed divisor 60. StoreDlTask receives
  the original task pointer. No file/resource cleanup is owned by this helper.
- Current unsigned retry-mask semantics, retry loop, time helper, ID rechecks
  and second-failure behavior are unchanged.

## Fresh measurements and validation

- NWC24UpdateDlTask: 95.00395 -> 98.695656%; source 249 -> 253 instructions,
  target 253. Frame 0x30 -> target 0x20. Positional ctxdiff 250 -> 43 differences.
- Unit: 99.252884 -> 99.55186%; exact functions 27/30 and exact code 9304/12496
  preserved; data 80/80 preserved. No linking changes.
- Every other one of the 29 functions has identical instructions and resolved
  relocations versus the baseline, including all 27 exact functions.
- Every allocated data byte and section extent is unchanged. Existing source/
  target alignment extents (.data 49/56 and .sbss 4/8) are unchanged; .sdata 16/16.
- Pool 3/3 identical. Literal advisory: 29 functions, 5 arguments, no candidates
  or errors; unchanged AddTaskInternal is skipped because its size differs
  from original. It remains 97.7182% and was not edited.
- Full 1,027-unit reports show only UpdateDlTask improved and no exact-function,
  code, data or fuzzy regressions. Final post-build report equals candidate.
- ASan/UBSan: 262,144 exhaustive u16 group/flag cases, mutating the task group
  during the group query to verify captured-value semantics. Seven directed
  cases check nulls, sentinel/range behavior, tool/owner short-circuiting and
  successful/failed second-validation stores.
- ASan/UBSan: 60,000 baseline/candidate Update scenarios compare return values,
  task/header bytes, selected work pointer and ordered external call traces.
  They cover metadata-query/time/store statuses, ID boundaries, group/owner
  mismatches, retry counts/masks including bit 31, signed times, and controlled
  task/header/work mutations at query boundaries. Actual production helper
  bodies are extracted unchanged; metadata/time/store I/O is stubbed. No network
  or file operation is performed. Leak detection is disabled for ptrace;
  address and undefined-behavior instrumentation remain enabled.
- Full 43U build and build/43U/ok pass. DOL SHA1:
  `26116613f624061ba99c8d1a299aaa6efa85670d`.
- git diff --check passes.

Private evidence: `/tmp/nwc24-write-permission/` contains baseline/candidate
sources and objects, reports, disassembly audit, host test generator/harness,
pool/ctxdiff/literal results and build logs. The preceding read-only screen is
in `/tmp/network-partial-recovery-screen/`. No retail assembly/binary is committed.

GATE: single justified partial recovery passes; frozen for independent review.
Historical 99.48617% is not claimed. Exact matching and linking remain open.
