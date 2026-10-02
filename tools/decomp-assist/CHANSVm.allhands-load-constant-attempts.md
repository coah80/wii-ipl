# CHANSVm load-constant error preservation

Baseline: 449529d92405f8f7fda610660c7794914a81dfe6. Scope: CHANSVm.c only; no linking classifications or headers changed.

## Retained correction

LOAD_STRING_CONST must preserve a failure from CHANSVmDeleteObject. The original object tests the deletion return and branches directly to the local result merge when it is nonzero. The load-string error is selected only after deletion succeeds and the constant index is out of range or has no string payload. The prior C instead overwrote every deletion error with CHANS_VM_ERR_LOAD_STRING_CONST.

A native destructor that returns false is a concrete error-producing path through CHANSVmDeleteObject; this distinction is observable, not merely a compiler-scheduling preference.

The new local loadResult preserves that error, keeps constant validation and installation inside the successful-deletion block, and merges the result afterward. Target and rebuilt blocks have the same instruction count and control-flow destinations; remaining operand differences are registers. No strings, data layout, or generated jump-table destinations changed.

## Measurements

- All 233 target functions have compiled C implementations; this is not a claim that all are exact or independently behavior-proven.
- Instruction-exact functions: 221/233 -> 221/233; every objdiff-exact function also passes ctxdiff.
- Unit decompiled/fuzzy: 99.364426% -> 99.383840%.
- Exact code: 37608/53564 bytes -> 37608/53564 bytes (70.211334%).
- Exact data: 6904/6904 bytes -> 6904/6904 bytes (100%).
- CHANSVmStep: 96.466080% -> 96.673584%; 1253/1253 instructions; ctxdiff differing positions 314 -> 297.
- Per-function score regressions relative to the fresh baseline report: zero.
- The unit remains NonMatching/unlinked; no link flags were changed.

## Attempts

1. Read previous round/wave logs and recent local trials; establish live baseline and run pool_diff first: 125 strings identical.
2. Replace the load-string shared error/goto path with a typed local error result and successful-deletion-only constant validation. Retained: correct error behavior, higher fuzzy score, unchanged exact code/data.
3. Separately tried consolidating GET_PROPERTY_NAME's local found flag and removing two unused array-index assignments. Rejected and restored completely: Step shrank to 1249 instructions and data dropped to 2232/6904. This unrelated trial is absent from the final source.

## Validation

- Full 43U build passed with the assigned wibo wrapper and WIBO_SJIS_MISSING_IMPORTS=1.
- DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d.
- pool_diff: 125/125 identical strings.
- .data: 4672/4672 bytes identical; all 352 canonical relocations identical.
- .rodata: 1432/1432 bytes identical; all 258 canonical relocations identical.
- All 233 functions compared with ctxdiff/odiff: 221 exact; no falsely exact objdiff functions.
- git diff --check passed.
- Source-extracted host C harness passed six load-constant cases: missing operand; deletion failure with valid index; deletion failure with invalid index; invalid index after successful deletion; null payload; successful installation. The harness stubs surrounding VM dependencies and checks C behavior only; no Wii runtime execution is claimed.

Source is paused after this focused candidate for parent review. The remaining 12 functions are still non-exact.
