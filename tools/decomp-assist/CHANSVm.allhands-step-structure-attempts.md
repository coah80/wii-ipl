# CHANSVm opcode error-path reconstruction

Baseline: 2f399716. This is a separate structural-reconstruction candidate; it preserves the preceding LOAD_STRING_CONST behavior fix. Only CHANSVm.c changed apart from this log. No headers, linking flags, remote branches, or original assets were changed.

## Retained changes and target evidence

- Failed binary-operand conversion returns CHANS_VM_ERR_RESULT_TYPE directly. Target Step relative +0x410 selects the error and +0x414 returns through +0x1364.
- Invalid GET_PROPERTY_NAME and JUMP destinations return CHANS_VM_ERR_CODE_RANGE directly. Target error tails are +0xd90/+0xd94 and +0xefc/+0xf00, respectively, both ending at +0x1364.
- DELETE_INDIRECT has a typed accumulator and a local deletion result, and reads the index through value.data.len rather than an offset-based u32 pointer cast. SET_INDEX elsewhere in the same function establishes this field as the index-reference index. The target holds the opcode-local result until the merge at +0xfb0, then assigns the common interpreter status. The rebuilt +0xf80 through +0xfb4 block is instruction-identical to the target.

These preserve existing C behavior. Unlike the preceding deletion-error fix, no new behavioral defect is claimed.

## Measurements

- Exact functions: 221/233 -> 221/233. Every previously exact function remains instruction-exact, not merely objdiff-exact.
- Decompiled/fuzzy unit: 99.383840% -> 99.406320%.
- CHANSVmStep: 96.673584% -> 96.913800%; 1253/1253 instructions; differing positions 297 -> 285.
- Exact code: unchanged, 37608/53564 bytes (70.211334%).
- Exact data: unchanged, 6904/6904 bytes (100%).
- Per-function score regressions: zero.
- Unit remains NonMatching/unlinked; twelve functions remain non-exact.

## Rejected investigations

All rejected source changes were restored, and no register forcing or declaration-order sweep was used.

- GET_PROPERTY_NAME output-state separation: a local found flag, initialized flag, shared index/output, and inline helper. These produced 1251-1253 instructions but moved generated data-table destinations; rejected.
- Direct result-type-table accesses, an explicit zero-count normalization/pretested loop, and indexed operand-type enumeration: 1254-1257 instructions; generated data-table destinations moved; rejected.
- Internal linkage for result-type or constant-header tables, individually and together, did not change those results; restored.
- CASE strict-comparison result separation, case-local match state, byte-sized operand types, and indexed operand enumeration: improved some local structure but introduced an operand-type spill and 1254-1255 instructions; generated tables moved; rejected.
- Direct exceptional returns alone: retained for combination, 96.697525%, data 100%.
- Typed DELETE_INDIRECT and local result alone: retained for combination, 96.889860%, data 100%.
- Combined direct returns and typed deletion result: accepted candidate, 96.913800%, data 100%.
- A first combination script used an obsolete substring end offset and did not compile; restored, corrected, and rerun. No source from the malformed attempt remains.
- Adding strict-comparison restructuring to the retained combination still produced 1254 instructions and data regression; rejected.

## Validation

- Full 43U build passed with the assigned wrapper and WIBO_SJIS_MISSING_IMPORTS=1.
- DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d.
- pool_diff: 125/125 strings identical.
- .data: 4672/4672 raw bytes and 352/352 canonical relocations identical.
- .rodata: 1432/1432 raw bytes and 258/258 canonical relocations identical.
- All 233 target functions compared: 221 instruction-exact; zero falsely exact objdiff functions; zero per-function score regressions from 2f399716.
- Narrow-string-reference audit: all 233 functions analyzed, 40 arguments checked, no candidates/errors/skips.
- Source-extracted host C tests: four DELETE_INDIRECT cases passed (wrong type, successful deletion, deletion failure, and null element forwarding), including exact unsigned index forwarding. The six prior LOAD_STRING_CONST cases also passed unchanged. These stub surrounding VM dependencies and are not Wii runtime tests.
- git diff --check passed.

The focused candidate is paused for independent parent review.
