# REA CDB source conversion, 2026-10-05

Baseline: `9d40859ee8f4ee37dc692e444727d17367bfcbeb`.
REA: `coah80/rea` commit `d19af8526975e8380da733c4f7313f73ee6a1c74`.
Ghidra 12.1.4, language `PowerPC:BE:32:Gekko_Broadway`.

## Filename validator, rejected

`CDBFSIsCDBFileOnSD`: REA confirmed eight hexadecimal characters, a dot,
and three hexadecimal characters, with a bounded length check of 13.
The existing C fallback compiled to 127/127 instructions with 20 register
differences. The assembly body was restored; no filename source change is kept.

Compiled trials:

- advance-pointer: src 0x1fc base 0x1fc insns 127/127; diffs 33: [9, 11, 12, 13, 16, 18, 20, 27, 28, 29, 35, 37, 38, 39, 40, 41, 42, 43, 44, 45].
- afterlength: src 0x1fc base 0x1fc insns 127/127; diffs 27: [8, 9, 10, 11, 12, 13, 14, 16, 18, 20, 27, 28, 29, 35, 37, 39, 46, 47, 48, 55].
- before: src 0x204 base 0x1fc insns 129/127; --- replace mine 5:8 base 5:6.
- char-local: src 0x204 base 0x1fc insns 129/127; --- replace mine 8:10 base 8:10.
- early-length: src 0x1fc base 0x1fc insns 127/127; diffs 113: [8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27].
- index-base: src 0x200 base 0x1fc insns 128/127; --- replace mine 8:10 base 8:10.
- index-expression: src 0x1fc base 0x1fc insns 127/127; diffs 20: [9, 11, 12, 13, 16, 18, 20, 27, 28, 29, 35, 37, 39, 46, 47, 48, 55, 73, 92, 111].
- indices-first: src 0x1fc base 0x1fc insns 127/127; diffs 22: [9, 11, 12, 13, 14, 16, 18, 20, 27, 28, 29, 35, 37, 39, 46, 47, 48, 54, 55, 73].
- indices-int: src 0x1f4 base 0x1fc insns 125/127; --- replace mine 8:10 base 8:10.
- indices-short: src 0x1fc base 0x1fc insns 127/127; diffs 20: [9, 11, 12, 13, 16, 18, 20, 27, 28, 29, 35, 37, 39, 46, 47, 48, 55, 73, 92, 111].
- indices-signed-char: src 0x1fc base 0x1fc insns 127/127; diffs 20: [9, 11, 12, 13, 16, 18, 20, 27, 28, 29, 35, 37, 39, 46, 47, 48, 55, 73, 92, 111].
- indices-unsigned-char: src 0x1fc base 0x1fc insns 127/127; diffs 20: [9, 11, 12, 13, 16, 18, 20, 27, 28, 29, 35, 37, 39, 46, 47, 48, 55, 73, 92, 111].
- indices-unsigned-short: src 0x1fc base 0x1fc insns 127/127; diffs 20: [9, 11, 12, 13, 16, 18, 20, 27, 28, 29, 35, 37, 39, 46, 47, 48, 55, 73, 92, 111].
- indices-unsigned: src 0x1f4 base 0x1fc insns 125/127; --- replace mine 8:10 base 8:10.
- inside: src 0x1fc base 0x1fc insns 127/127; diffs 24: [9, 11, 12, 13, 16, 18, 20, 27, 28, 29, 35, 37, 39, 46, 47, 48, 55, 57, 62, 73].
- local-int: src 0x1fc base 0x1fc insns 127/127; diffs 22: [9, 11, 12, 13, 14, 16, 18, 20, 27, 28, 29, 35, 37, 39, 46, 47, 48, 54, 55, 73].
- outer-decls-4: src 0x1fc base 0x1fc insns 127/127; diffs 20: [9, 11, 12, 13, 16, 18, 20, 27, 28, 29, 35, 37, 39, 46, 47, 48, 55, 73, 92, 111].
- outer-decls-5: src 0x1fc base 0x1fc insns 127/127; diffs 22: [9, 11, 12, 13, 14, 16, 18, 20, 27, 28, 29, 35, 37, 39, 46, 47, 48, 54, 55, 73].
- pointer-after-indices: src 0x1fc base 0x1fc insns 127/127; diffs 20: [9, 11, 12, 13, 16, 18, 20, 27, 28, 29, 35, 37, 39, 46, 47, 48, 55, 73, 92, 111].
- pointer-before-call: src 0x204 base 0x1fc insns 129/127; --- delete mine 6:8 base 6:6.
- pointer-const: src 0x1fc base 0x1fc insns 127/127; diffs 20: [9, 11, 12, 13, 16, 18, 20, 27, 28, 29, 35, 37, 39, 46, 47, 48, 55, 73, 92, 111].
- pointer-loop-init: src 0x1fc base 0x1fc insns 127/127; diffs 20: [9, 11, 12, 13, 16, 18, 20, 27, 28, 29, 35, 37, 39, 46, 47, 48, 55, 73, 92, 111].
- pointer-subscript: src 0x1fc base 0x1fc insns 127/127; diffs 20: [9, 11, 12, 13, 16, 18, 20, 27, 28, 29, 35, 37, 39, 46, 47, 48, 55, 73, 92, 111].
- positive-condition: src 0x1fc base 0x1fc insns 127/127; diffs 20: [9, 11, 12, 13, 16, 18, 20, 27, 28, 29, 35, 37, 39, 46, 47, 48, 55, 73, 92, 111].
- separate-checks: src 0x1fc base 0x1fc insns 127/127; diffs 20: [9, 11, 12, 13, 16, 18, 20, 27, 28, 29, 35, 37, 39, 46, 47, 48, 55, 73, 92, 111].
- separate-index: src 0x1fc base 0x1fc insns 127/127; diffs 20: [9, 11, 12, 13, 16, 18, 20, 27, 28, 29, 35, 37, 39, 46, 47, 48, 55, 73, 92, 111].
- unrolled-0: src 0x1f4 base 0x1fc insns 125/127; --- replace mine 8:10 base 8:10.
- unrolled-1: src 0x1f4 base 0x1fc insns 125/127; --- replace mine 8:10 base 8:10.

## Search callback, exact candidate

REA imported the original CDBDatabase object, listed its functions, and
exported `CDBDatabaseSearchCallCallback` assembly and pseudocode.
The input SHA-256 is `336938cc4483cf2cd8e1c0a9e188fc567f09c0a4a4911b10fdc4e173d4b02605`.

Used existing typed database state, search conditions, and record fields.
Corrected the local `CDBRecordOpenReadOnly` declaration to return `CDBErr`.
Kept the success block nested under `result == CDB_ERROR_OK`, with the error
return in its else block. This preserves the target's extra branch that the
prior early-return trials in `asm-conversions.attempts.md` did not reproduce.

First compiled candidate: 61/61 instructions, 244/244 bytes, ctxdiff zero.
String pool: identical, seven entries. This replaces an existing matching
assembly body; it does not increase the already-counted exact function total.

REA evidence remains locally in `build/rea-cdbcallback/elf.json` and `elf.c`.
The verifier command was:

```
node /mnt/drive2/projects/rea-wii/scripts/verify-wii-powerpc.mjs \
  build/43U/obj/libs/RevoEX/src/cdb/CDBDatabase.o \
  CDBDatabaseSearchCallCallback build/rea-cdbcallback
```

## Full validation

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/cdb/CDBDatabase] pool: IDENTICAL
[libs/RevoEX/src/cdb/CDBDatabase] objdiff: code 12152/12152 data 312/312 functions 33/33 fuzzy 100.0000 linked code 12152
[libs/RevoEX/src/cdb/CDBDatabase] instruction-exact functions: 33/33
[libs/RevoEX/src/cdb/CDBDatabase]   section .data size 312 match 100.0
[libs/RevoEX/src/cdb/CDBDatabase]   section .text size 12152 match 100.0
[libs/RevoEX/src/cdb/CDBDatabase] baseline: code 12152/12152 data 312 functions 33 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 92.73726 -> 92.73726
global fuzzy_match_percent: 99.78007 -> 99.78007
global complete_code_percent: 76.40339 -> 76.40339
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

The final completion checker still fails for the incomplete overall project.
After this candidate was exact, a read-only check found the separate `data-d2`
worker had independently converted this callback too. The draft PR notes
this overlap so the reviewer can choose one implementation.
