# CHANSVm typed comparison reconstruction

Baseline: ec75ddb0. This candidate is separate from the accepted load-string and opcode-error-path work. Those commits and their logs are unchanged. Only CHANSVm.c and this log changed; no headers, linking classifications, metadata, or original assets changed.

## Retained reconstruction

- LOAD_FLOAT copies the eight-byte literal into a double scratch member and passes that value directly. This replaces a u64 temporary followed by a double-pointer reinterpretation. Scratch alignment, member offsets, and emitted code are unchanged.
- SET_INDEX reads the floating operand through its union member and checks its lower bound before its upper bound, matching the target's comparison order. The accepted interval remains [0, 4294967294], with NaN and infinities rejected.
- Strict integer equality uses the declared 64-bit integer values rather than four offset-based u32 loads and manual XOR/OR expressions.
- Strict floating equality uses the declared floating values directly.
- Strict string equality uses named, read-only payload pointers rather than recreating a header pointer. The stack operand is consistently first in the outer type comparison, following the target.

This is structural/type reconstruction, not a newly discovered behavior fix. No register forcing, declaration sweep, or alignment padding was introduced.

## Target evidence

After rebuilding, the integer-comparison block (Step instructions 1093-1102), floating-comparison block (1103-1108), string-comparison block (1109-1128), and floating-index block (703-712) have the same instructions, control flow, constants, and memory offsets as the target after register names are normalized. This comparison is advisory: register differences remain, and Step is not exact.

The floating range's instruction forms now use the target's lower-bound-first order. Integer equality emits the same target ten-instruction two-word equality sequence naturally from the 64-bit value comparison. LOAD_FLOAT retains its original eight-byte copy and call sequence without a pointer reinterpretation.

## Measurements

- Instruction-exact functions: 221/233 -> 221/233; no previously exact function regressed.
- Unit Decompiled/fuzzy: 99.406320% -> 99.413185%.
- Step: 96.913800% -> 96.987230%; 1253/1253 instructions; differing positions 285 -> 276.
- Exact code: unchanged at 37608/53564 bytes (70.211334%).
- Exact data: unchanged at 6904/6904 bytes (100%).
- Per-function score regressions: zero.
- Unit remains NonMatching/unlinked, with twelve non-exact functions.

## Attempts

- Direct 64-bit equality alone: Step 96.933760%, data 100%; retained for combination.
- Typed integer/float/string comparison paths: 96.971270%, data 100%; retained.
- Those typed paths plus a separate strict-comparison local error result: 1254 instructions, table relocations moved; rejected.
- Floating index member access alone preserves the typed-comparison score. Lower-bound-first range checking raises it to 96.983240%, data 100%; retained.
- A union literal temporary produced the same code; simplified to a direct double member instead, also with identical code.
- Stack-first type comparison raises Step to 96.987230% with unchanged data; retained.

## Verification

- Full 43U build passed with the assigned wrapper and WIBO_SJIS_MISSING_IMPORTS=1.
- DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d.
- pool_diff: all 125 strings identical.
- .data: 4672/4672 raw bytes and 352/352 canonical relocations identical.
- .rodata: 1432/1432 raw bytes and 258/258 canonical relocations identical.
- All 233 functions checked with ctxdiff/odiff: 221 instruction-exact; no falsely exact objdiff functions.
- Literal-reference audit: 233 functions analyzed, 40 resolvable call-string arguments checked, no candidates/errors/skips.
- Source-extracted host C harnesses passed 20 strict-comparison cases, nine floating-index-bound cases, and eight floating-literal bit patterns. Coverage includes signed integer extremes, differing high words, signed zero, NaN, infinities, strings, references, deletion errors, and literal payload preservation. They stub surrounding dependencies and do not constitute Wii runtime execution.
- git diff --check passed.

Source is paused for independent parent verification.
