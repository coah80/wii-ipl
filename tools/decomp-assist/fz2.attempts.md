# fz2 matching attempts

Baseline HEAD 2f0f5a44c72cb84e23732e09fc8e75487c788f76; origin/main 5d63d152486a556fa24edf46b65dee7ce88474d6

All four units already have fully paired data, no symbol renames or extent changes needed.

libs/RVLMiddleware/eZiText/src/clib/zmtkey: POOL IDENTICAL up to 0 (mine=0 base=0)

libs/RVL_SDK/src/fa/pf_file: POOL IDENTICAL up to 0 (mine=0 base=0)

libs/RVL_SDK/src/kpr/kpr_lib: POOL IDENTICAL up to 2 (mine=2 base=2)

libs/RVLMiddleware/eZiText/src/clib/zconvert: POOL IDENTICAL up to 0 (mine=0 base=0)

## Structural diagnosis
- Zi8getKeyLayout: 182/182 instructions, same 0x40 frame and branch/inline boundaries; only language/tableCount r26/r27 swapped, 16 differences.
- PFFILE_GetSFD: 113/113 instructions, frame and branch layout identical; four saved register assignments differ and index/pointer increments reversed, 18 differences.
- KPRProcessAltKeypad: 96/96 instructions, leaf function without frame; branch form/operand order/helper boundaries identical; leadingZero/value/index register assignment differs, 21 differences.
- Zi8ConvertUC2WC: 124/124 instructions, identical frame/branches/operands/helper boundaries; table/first/mapped saved registers differ, 8 differences.
- Zi8ConvertUC2Key: 207/207 instructions, identical frame/branches/operands/helper boundaries; work/key r27/r28 swapped, 18 differences.

Before each initial function investigation origin fetched under flock; source identical to origin/main in all four owned units, so none already matched remotely.
- Zi8getKeyLayout / scope table count to builtin table path: 186/182 instructions; structural 12, positional differences 181
- Zi8getKeyLayout / use separate character total after table lookup: 182/182 instructions; structural 2, positional differences 4
- Zi8getKeyLayout / nested fallback branches instead of goto: 182/182 instructions; structural 0, positional differences 16
- Zi8getKeyLayout / wide lookup count with explicit narrow comparison: 184/182 instructions; structural 8, positional differences 113
- Zi8getKeyLayout / signed lookup count with explicit narrow comparison: 184/182 instructions; structural 8, positional differences 113
- Zi8getKeyLayout / carry lookup count into accumulated total initializer: 184/182 instructions; structural 8, positional differences 67
- Zi8getKeyLayout / initialize separate count and total together: 183/182 instructions; structural 7, positional differences 65
- Zi8getKeyLayout / lookup count used for later zero character check: 183/182 instructions; structural 7, positional differences 52
- Zi8getKeyLayout / use ziU8 language local: 186/182 instructions; structural 34, positional differences 180
- Zi8getKeyLayout / use ziU16 language local: 186/182 instructions; structural 34, positional differences 180
- Zi8getKeyLayout / use ziU32 language local: 186/182 instructions; structural 34, positional differences 180
- Zi8getKeyLayout / lookup count declaration after key characters: 182/182 instructions; structural 0, positional differences 16
- Zi8getKeyLayout / narrow table count on reads with wide storage: 180/182 instructions; structural 7, positional differences 116
- PFFILE_GetSFD / pointer increment before index in loop latch: 113/113 instructions; structural 0, positional differences 18
- PFFILE_GetSFD / separate free slot index and pointer initialization: 113/113 instructions; structural 2, positional differences 19
- PFFILE_GetSFD / pointer iteration with existing index comparisons: 113/113 instructions; structural 0, positional differences 18
- PFFILE_GetSFD / free index declaration before free slot pointer: 113/113 instructions; structural 0, positional differences 42
- Zi8getKeyLayout / declaration search: 52 orders, best remained structural 0 and 16 register differences; source restored.
- KPRProcessAltKeypad / leading zero declared before accumulator: 96/96 instructions; structural 0, positional differences 7
- KPRProcessAltKeypad / converted value scoped to non-digit path: 96/96 instructions; structural 0, positional differences 21
- KPRProcessAltKeypad / keypad value fetched into accumulator local: 96/96 instructions; structural 0, positional differences 21
- KPRProcessAltKeypad / declare conversion and shift locals together: 96/96 instructions; structural 0, positional differences 25
- KPRProcessAltKeypad / leading zero first and reuse accumulator for converted value: 96/96 instructions; structural 0, positional differences 7
- KPRProcessAltKeypad / leading zero first and shift locals at function scope: 96/96 instructions; structural 0, positional differences 7
- KPRProcessAltKeypad / leading zero first and converted declared beside value: 96/96 instructions; structural 0, positional differences 7
- KPRProcessAltKeypad / leading zero first and converted before value: 96/96 instructions; structural 0, positional differences 7
- KPRProcessAltKeypad / leading zero first and shift index before destination: 96/96 instructions; structural 0, positional differences 15
- PFFILE_GetSFD / use formal volume through typed field casts: 113/113 instructions; structural 9, positional differences 61
- PFFILE_GetSFD / separate volume alias from initialization: 113/113 instructions; structural 2, positional differences 31
- PFFILE_GetSFD / index initializer before volume and entry aliases: 113/113 instructions; structural 0, positional differences 39
- PFFILE_GetSFD / free pointer and index initialized in first loop clause: 113/113 instructions; structural 0, positional differences 19
- KPRProcessAltKeypad / all keypad locals before active-value branch: 96/96 instructions; structural 0, positional differences 21
- KPRProcessAltKeypad / all locals at function scope including conversion and shifting: 96/96 instructions; structural 0, positional differences 25
- KPRProcessAltKeypad / leading zero signed local: 96/96 instructions; structural 0, positional differences 21
- KPRProcessAltKeypad / reuse value local for digit accumulator: 96/96 instructions; structural 0, positional differences 21
- KPRProcessAltKeypad / initialize value from stored accumulator in branch declaration: BUILD FAIL ivate/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/kpr/kpr_lib.c -o build/43U/src/libs/RVL_SDK/src/kpr && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpr/kpr_lib.d build/43U/src/libs/RVL_SDK/src/kpr/kpr_lib.d ### mwcceppc.exe Compiler: #    File: libs\RVL_SDK\src\kpr\kpr_lib.c # --------------------------------------- #     257:         u32 value = queue->altVal;  #   Error:         ^^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
- KPRProcessAltKeypad / declaration order (0, 1, 2): 96/96 instructions; structural 0, positional differences 21
- KPRProcessAltKeypad / declaration order (0, 2, 1): 96/96 instructions; structural 0, positional differences 21
- KPRProcessAltKeypad / declaration order (1, 0, 2): 96/96 instructions; structural 0, positional differences 21
- KPRProcessAltKeypad / declaration order (1, 2, 0): 96/96 instructions; structural 0, positional differences 21
- KPRProcessAltKeypad / declaration order (2, 0, 1): 96/96 instructions; structural 0, positional differences 7
- KPRProcessAltKeypad / declaration order (2, 1, 0): 96/96 instructions; structural 0, positional differences 7
- PFFILE_GetSFD / declsearch after swapped loop latch: 23 orders, structural 0, 18 differences; no exact gain, original source restored.
- Zi8ConvertUC2WC / declaration search: initial 6 orders reduced 8 to 6 differences; corrected full leading block search tried 11 orders and reached structural 0, diffs 0, 124/124 instructions. Final order defaults, mapped, cursor, first/last, table. A mistaken initial line range included the following if block, produced no gain and was restored before corrected range.

UC2WC final full gate PASS: zconvert 3/4 exact, code 1380/2208, data 112/112; regressions/forbidden/readability 0; DOL 26116613f624061ba99c8d1a299aaa6efa85670d.
- Zi8getKeyLayout / count declaration split with character count: 182/182 instructions; structural 0, positional differences 16
- Zi8getKeyLayout / all builtin table locals grouped in function scope: 182/182 instructions; structural 0, positional differences 16
- Zi8getKeyLayout / initialize address in declaration: 182/182 instructions; structural 0, positional differences 16
- Zi8getKeyLayout / initialize num keys at declaration after other locals: 182/182 instructions; structural 2, positional differences 20
- Zi8getKeyLayout / scope copy pointer and lookup count in mutually exclusive paths: 186/182 instructions; structural 12, positional differences 181
- KPRProcessAltKeypad / value declared outside the active accumulator branch: 96/96 instructions; structural 0, positional differences 21
- KPRProcessAltKeypad / leading zero declared outside the active branch: 96/96 instructions; structural 0, positional differences 7
- KPRProcessAltKeypad / accumulator declared outside the active branch: BUILD FAIL L_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/kpr/kpr_lib.c -o build/43U/src/libs/RVL_SDK/src/kpr && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpr/kpr_lib.d build/43U/src/libs/RVL_SDK/src/kpr/kpr_lib.d ### mwcceppc.exe Compiler: #    File: libs\RVL_SDK\src\kpr\kpr_lib.c # --------------------------------------- #     249:         u32 value;  #   Error:         ^^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
- KPRProcessAltKeypad / value and leading zero declared at function scope: 96/96 instructions; structural 0, positional differences 7
- KPRProcessAltKeypad / all locals initialized after declarations with zero flag first: 96/96 instructions; structural 0, positional differences 21
- PFFILE_GetSFD / full declaration permutation (0, 1, 2, 3, 4): 113/113 instructions; structural 2, positional differences 18
- PFFILE_GetSFD / full declaration permutation (0, 1, 2, 4, 3): 113/113 instructions; structural 2, positional differences 19
- PFFILE_GetSFD / full declaration permutation (0, 1, 3, 2, 4): 113/113 instructions; structural 2, positional differences 18
- PFFILE_GetSFD / full declaration permutation (0, 1, 3, 4, 2): 113/113 instructions; structural 2, positional differences 22
- PFFILE_GetSFD / full declaration permutation (0, 1, 4, 2, 3): 113/113 instructions; structural 2, positional differences 22
- PFFILE_GetSFD / full declaration permutation (0, 1, 4, 3, 2): 113/113 instructions; structural 2, positional differences 22
- PFFILE_GetSFD / full declaration permutation (0, 2, 1, 3, 4): 113/113 instructions; structural 2, positional differences 18
- PFFILE_GetSFD / full declaration permutation (0, 2, 1, 4, 3): 113/113 instructions; structural 2, positional differences 19
- PFFILE_GetSFD / full declaration permutation (0, 2, 3, 1, 4): 113/113 instructions; structural 2, positional differences 42
- PFFILE_GetSFD / full declaration permutation (0, 2, 3, 4, 1): 113/113 instructions; structural 2, positional differences 43
- PFFILE_GetSFD / full declaration permutation (0, 2, 4, 1, 3): 113/113 instructions; structural 2, positional differences 18
- PFFILE_GetSFD / full declaration permutation (0, 2, 4, 3, 1): 113/113 instructions; structural 2, positional differences 42
- PFFILE_GetSFD / full declaration permutation (0, 3, 1, 2, 4): 113/113 instructions; structural 2, positional differences 42
- PFFILE_GetSFD / full declaration permutation (0, 3, 1, 4, 2): 113/113 instructions; structural 2, positional differences 45
- PFFILE_GetSFD / full declaration permutation (0, 3, 2, 1, 4): 113/113 instructions; structural 2, positional differences 42
- PFFILE_GetSFD / full declaration permutation (0, 3, 2, 4, 1): 113/113 instructions; structural 2, positional differences 43
- PFFILE_GetSFD / full declaration permutation (0, 3, 4, 1, 2): 113/113 instructions; structural 2, positional differences 45
- PFFILE_GetSFD / full declaration permutation (0, 3, 4, 2, 1): 113/113 instructions; structural 2, positional differences 45
- PFFILE_GetSFD / full declaration permutation (0, 4, 1, 2, 3): 113/113 instructions; structural 2, positional differences 21
- PFFILE_GetSFD / full declaration permutation (0, 4, 1, 3, 2): 113/113 instructions; structural 2, positional differences 21
- PFFILE_GetSFD / full declaration permutation (0, 4, 2, 1, 3): 113/113 instructions; structural 2, positional differences 21
- PFFILE_GetSFD / full declaration permutation (0, 4, 2, 3, 1): 113/113 instructions; structural 2, positional differences 44
- PFFILE_GetSFD / full declaration permutation (0, 4, 3, 1, 2): 113/113 instructions; structural 2, positional differences 44
- PFFILE_GetSFD / full declaration permutation (0, 4, 3, 2, 1): 113/113 instructions; structural 2, positional differences 44
- PFFILE_GetSFD / full declaration permutation (1, 0, 2, 3, 4): 113/113 instructions; structural 2, positional differences 41
- PFFILE_GetSFD / full declaration permutation (1, 0, 2, 4, 3): 113/113 instructions; structural 2, positional differences 42
- PFFILE_GetSFD / full declaration permutation (1, 0, 3, 2, 4): 113/113 instructions; structural 2, positional differences 41
- PFFILE_GetSFD / full declaration permutation (1, 0, 3, 4, 2): 113/113 instructions; structural 2, positional differences 44
- PFFILE_GetSFD / full declaration permutation (1, 0, 4, 2, 3): 113/113 instructions; structural 2, positional differences 44
- PFFILE_GetSFD / full declaration permutation (1, 0, 4, 3, 2): 113/113 instructions; structural 2, positional differences 44
- PFFILE_GetSFD / full declaration permutation (1, 3, 0, 2, 4): 113/113 instructions; structural 2, positional differences 40
- PFFILE_GetSFD / full declaration permutation (1, 3, 0, 4, 2): 113/113 instructions; structural 2, positional differences 43
- PFFILE_GetSFD / full declaration permutation (1, 3, 4, 0, 2): 113/113 instructions; structural 2, positional differences 43
- PFFILE_GetSFD / full declaration permutation (1, 4, 0, 2, 3): 113/113 instructions; structural 2, positional differences 44
- PFFILE_GetSFD / full declaration permutation (1, 4, 0, 3, 2): 113/113 instructions; structural 2, positional differences 44
- PFFILE_GetSFD / full declaration permutation (1, 4, 3, 0, 2): 113/113 instructions; structural 2, positional differences 44
- PFFILE_GetSFD / full declaration permutation (3, 0, 1, 2, 4): 113/113 instructions; structural 2, positional differences 39
- PFFILE_GetSFD / full declaration permutation (3, 0, 1, 4, 2): 113/113 instructions; structural 2, positional differences 43
- PFFILE_GetSFD / full declaration permutation (3, 0, 2, 1, 4): 113/113 instructions; structural 2, positional differences 39
- PFFILE_GetSFD / full declaration permutation (3, 0, 2, 4, 1): 113/113 instructions; structural 2, positional differences 40
- PFFILE_GetSFD / full declaration permutation (3, 0, 4, 1, 2): 113/113 instructions; structural 2, positional differences 43
- PFFILE_GetSFD / full declaration permutation (3, 0, 4, 2, 1): 113/113 instructions; structural 2, positional differences 43
- PFFILE_GetSFD / full declaration permutation (3, 1, 0, 2, 4): 113/113 instructions; structural 2, positional differences 14
- Zi8ConvertUC2Key / separate key declaration and initial assignment: 207/207 instructions; structural 0, positional differences 18
- PFFILE_GetSFD / full declaration permutation (3, 1, 0, 4, 2): 113/113 instructions; structural 2, positional differences 19
- Zi8ConvertUC2Key / scope keyed table lookup locals in their path: 210/207 instructions; structural 14, positional differences 205
- PFFILE_GetSFD / full declaration permutation (3, 1, 4, 0, 2): 113/113 instructions; structural 2, positional differences 19
- Zi8ConvertUC2Key / negative table lookup with default path first: 207/207 instructions; structural 138, positional differences 155
- PFFILE_GetSFD / full declaration permutation (3, 4, 0, 1, 2): 113/113 instructions; structural 2, positional differences 43
- Zi8ConvertUC2Key / wide key local with narrow result reads: 205/207 instructions; structural 11, positional differences 130
- PFFILE_GetSFD / full declaration permutation (3, 4, 0, 2, 1): 113/113 instructions; structural 2, positional differences 43
- PFFILE_GetSFD / full declaration permutation (3, 4, 1, 0, 2): 113/113 instructions; structural 2, positional differences 20
- PFFILE_GetSFD / full declaration permutation (4, 0, 1, 2, 3): 113/113 instructions; structural 2, positional differences 21
- PFFILE_GetSFD / full declaration permutation (4, 0, 1, 3, 2): 113/113 instructions; structural 2, positional differences 21
- PFFILE_GetSFD / full declaration permutation (4, 0, 2, 1, 3): 113/113 instructions; structural 2, positional differences 21
- PFFILE_GetSFD / full declaration permutation (4, 0, 2, 3, 1): 113/113 instructions; structural 2, positional differences 44
- PFFILE_GetSFD / full declaration permutation (4, 0, 3, 1, 2): 113/113 instructions; structural 2, positional differences 44
- PFFILE_GetSFD / full declaration permutation (4, 0, 3, 2, 1): 113/113 instructions; structural 2, positional differences 44
- PFFILE_GetSFD / full declaration permutation (4, 1, 0, 2, 3): 113/113 instructions; structural 2, positional differences 45
- PFFILE_GetSFD / full declaration permutation (4, 1, 0, 3, 2): 113/113 instructions; structural 2, positional differences 45
- PFFILE_GetSFD / full declaration permutation (4, 1, 3, 0, 2): 113/113 instructions; structural 2, positional differences 45
- PFFILE_GetSFD / full declaration permutation (4, 3, 0, 1, 2): 113/113 instructions; structural 2, positional differences 44
- PFFILE_GetSFD / full declaration permutation (4, 3, 0, 2, 1): 113/113 instructions; structural 2, positional differences 44
- PFFILE_GetSFD / full declaration permutation (4, 3, 1, 0, 2): 113/113 instructions; structural 2, positional differences 21
- Zi8getKeyLayout / descriptive local tableCount to tableSize: 182/182 instructions; structural 0, positional differences 16
- Zi8getKeyLayout / descriptive local language to languageId: 182/182 instructions; structural 0, positional differences 16
- Zi8getKeyLayout / descriptive local tableCount to characterTotal: 182/182 instructions; structural 0, positional differences 16
- Zi8ConvertUC2Key / descriptive local key to keyCode: 207/207 instructions; structural 0, positional differences 18
- KPRProcessAltKeypad / inline codepage conversion helper: 96/96 instructions; structural 0, positional differences 0; EXACT candidate retained
- KPRProcessAltKeypad / clear alt accumulator with compound assignment: 96/96 instructions; structural 0, positional differences 21
- KPRProcessAltKeypad / combine digit arithmetic with accumulator assignment: 96/96 instructions; structural 0, positional differences 21
- KPRProcessAltKeypad / keep converted character in outer value but use shift pointer loop: 96/96 instructions; structural 0, positional differences 21

Zi8ConvertUC2Key declaration search covered 36 legal orders without gain; a mistaken first range included the declaration of the function, yielded no gain, and restored source. The later correct range was 127-132.
PFFILE_GetSFD exhaustive search covered 60 dependency-valid declaration orders, none exact, best 113/113 with 14 differences. No fuzzy candidates retained.

KPRProcessAltKeypad: codepage conversion extracted to readable inline helper; 96/96 instructions, diffs 0; final full gate PASS 9/9, code 1536/1536 data 1104/1104, DOL correct, zero regressions/forbidden/style. Helper indentation normalized, verification repeated before commit.
- Zi8getKeyLayout / inline custom key character copy: 168/182 instructions; structural 28, positional differences 151
- Zi8getKeyLayout / inline builtin key character count: 175/182 instructions; structural 13, positional differences 68
- Zi8getKeyLayout / inline little endian key character read: 174/182 instructions; structural 18, positional differences 50
- Zi8ConvertUC2Key / inline key table value decoding: 193/207 instructions; structural 32, positional differences 167
- Zi8ConvertUC2Key / inline all conversion entry decoding: 189/207 instructions; structural 38, positional differences 165
- Zi8ConvertUC2Key / scope default mapping variables in fallback branch: 210/207 instructions; structural 6, positional differences 205
- Zi8ConvertUC2Key / entry offset access through byte pointer local: 212/207 instructions; structural 19, positional differences 128
- PFFILE_GetSFD / inline descriptor initialization with original volume alias: 113/113 instructions; structural 2, positional differences 18
- PFFILE_GetSFD / inline descriptor initialization with pointer-first latch: 113/113 instructions; structural 0, positional differences 18
- PFFILE_GetSFD / inline cluster link setup: 113/113 instructions; structural 2, positional differences 18
- PFFILE_GetSFD / both descriptor and link setup helpers: 113/113 instructions; structural 2, positional differences 18
- Zi8getKeyLayout / inline ziU16 table count wrapper: 182/182 instructions; structural 0, positional differences 16
- Zi8getKeyLayout / inline ziU32 table count wrapper: 180/182 instructions; structural 6, positional differences 116
- Zi8getKeyLayout / table count initialized from character summation in separate block: 182/182 instructions; structural 0, positional differences 16

## Completion audit
- Remaining Zi8getKeyLayout: at least three distinct structural/source attempts, declaration search and helper variations logged; no exact candidate. Baseline 182/182, 16 register differences.
- Remaining PFFILE_GetSFD: at least three distinct structural/source attempts plus 60 legal declaration permutations and helper variations logged; no exact candidate. Baseline 113/113, 18 differences including increment order.
- Remaining Zi8ConvertUC2Key: at least three distinct structural/source attempts, full declaration search and decoding/scope variations logged; no exact candidate. Baseline 207/207, 18 work/key register differences.
- Matched Zi8ConvertUC2WC: 124/124 diffs 0. Matched KPRProcessAltKeypad: 96/96 diffs 0.
- Every owned data unit is 100% paired from baseline through final candidate; no config edits made. All nonexact experimental changes restored.

## Final full gate over all four units

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/eZiText/src/clib/zmtkey] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zmtkey] objdiff: code 1488/2216 data 60/60 functions 3/4 fuzzy 99.8466 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zmtkey] instruction-exact functions: 3/4
[libs/RVLMiddleware/eZiText/src/clib/zmtkey]   section .text size 2216 match 99.84657
[libs/RVLMiddleware/eZiText/src/clib/zmtkey]   section extab size 24 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zmtkey]   section extabindex size 36 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zmtkey]   below 100: Zi8getKeyLayout 99.53297
[libs/RVLMiddleware/eZiText/src/clib/zmtkey] baseline: code 1488/2216 data 60 functions 3 fuzzy 99.8466
[libs/RVL_SDK/src/fa/pf_file] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_file] objdiff: code 17368/17820 data None/None functions 44/45 fuzzy 99.9771 linked code 0
[libs/RVL_SDK/src/fa/pf_file] instruction-exact functions: 44/45
[libs/RVL_SDK/src/fa/pf_file]   section .text size 17820 match 99.977104
[libs/RVL_SDK/src/fa/pf_file]   below 100: PFFILE_GetSFD 99.09734
[libs/RVL_SDK/src/fa/pf_file] baseline: code 17368/17820 data None functions 44 fuzzy 99.9771
[libs/RVL_SDK/src/kpr/kpr_lib] pool: IDENTICAL
[libs/RVL_SDK/src/kpr/kpr_lib] objdiff: code 1536/1536 data 1104/1104 functions 9/9 fuzzy 100.0000 linked code 0
[libs/RVL_SDK/src/kpr/kpr_lib] instruction-exact functions: 9/9
[libs/RVL_SDK/src/kpr/kpr_lib]   section .data size 112 match 100.0
[libs/RVL_SDK/src/kpr/kpr_lib]   section .rodata size 968 match 100.0
[libs/RVL_SDK/src/kpr/kpr_lib]   section .sbss size 16 match 100.0
[libs/RVL_SDK/src/kpr/kpr_lib]   section .sdata size 8 match 100.0
[libs/RVL_SDK/src/kpr/kpr_lib]   section .text size 1536 match 100.0
[libs/RVL_SDK/src/kpr/kpr_lib] baseline: code 1152/1536 data 1104 functions 8 fuzzy 99.6875
[libs/RVLMiddleware/eZiText/src/clib/zconvert] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zconvert] objdiff: code 1380/2208 data 112/112 functions 3/4 fuzzy 99.8370 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zconvert] instruction-exact functions: 3/4
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section .rodata size 32 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section .text size 2208 match 99.83696
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section extab size 32 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section extabindex size 48 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   below 100: Zi8ConvertUC2Key 99.565216
[libs/RVLMiddleware/eZiText/src/clib/zconvert] baseline: code 884/2208 data 112 functions 2 fuzzy 99.7645
regressions vs baseline: 0
global matched_code_percent: 88.57407 -> 88.60345
global fuzzy_match_percent: 99.45531 -> 99.45553
global complete_code_percent: 63.16065 -> 63.16065
global matched_data_percent: 98.20482 -> 98.20482
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Before -> after instruction-exact functions / matched code bytes / matched data bytes:
- zmtkey: 3->3 / 1488->1488 / 60->60.
- pf_file: 44->44 / 17368->17368 / no data symbols.
- kpr_lib: 8->9 / 1152->1536 / 1104->1104.
- zconvert: 2->3 / 884->1380 / 112->112.
Source commits: 57bab7c8, 36278f38. No uncertainty about the reported measurements; remaining source levers unknown.

# Round 2 after landing
Baseline cbf6363d0f5e07b6dceadc43693694c14d58a229
- Zi8getKeyLayout / r2 inline layout helper with existing argument order: 18/182 instructions; structural 187, positional differences 180
- Zi8getKeyLayout / r2 inline layout helper with work pointer first: 18/182 instructions; structural 187, positional differences 180
- Zi8getKeyLayout / r2 inline layout helper with wide scalars: BUILD FAIL tkey.c -o build/43U/src/libs/RVLMiddleware/eZiText/src/clib && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVLMiddleware/eZiText/src/clib/zmtkey.d build/43U/src/libs/RVLMiddleware/eZiText/src/clib/zmtkey.d ### mwcceppc.exe Compiler: #    File: libs\RVLMiddleware\eZiText\src\clib\zmtkey.c # ----------------------------------------------------- #      61:         if (!Zi8MapKeyCode(key, &key, __zi8_work_data)) {  #   Error:                                                      ^ #   (10209) illegal implicit conversion from 'unsigned long *' to #   'unsigned short *' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 

Round 2 live diagnosis, all pools identical before source experiments.
- Zi8getKeyLayout: same 0x40 frame, 182/182 instructions, branches, operands and inline boundaries equal after register normalization. Language/tableCount r26/r27 coloring remains.
- PFFILE_GetSFD: same 0x20 frame, 113/113 instructions; indexed traversal generates three induction updates in different order; volume/entry/free-index saved registers differ.
- Zi8ConvertUC2Key: same 0x40 frame, 207/207 instructions, branches/temporaries/operands/helper boundaries equal after register normalization. Work/key r27/r28 coloring remains.
All three owned sources identical to newly fetched origin/main before their initial function investigations.
- Zi8getKeyLayout / r2 split primary table lookup assignment from condition: 182/182 instructions; structural 0, positional differences 16
- Zi8getKeyLayout / r2 split both table lookup assignments from conditions: 182/182 instructions; structural 0, positional differences 22
- Zi8getKeyLayout / r2 signed 16 bit count with unsigned reads: 182/182 instructions; structural 3, positional differences 16
- Zi8getKeyLayout / r2 direct count addition instead of compound assignment: 183/182 instructions; structural 7, positional differences 72
- Zi8getKeyLayout / r2 unsigned sum widened only at increment: 184/182 instructions; structural 8, positional differences 75
- Zi8getKeyLayout / r2 index initialized with count in common assignment: 182/182 instructions; structural 0, positional differences 16
- Zi8getKeyLayout / r2 key count helper ziU16 locals and ziU16 result: 175/182 instructions; structural 13, positional differences 68
- Zi8getKeyLayout / r2 key count helper ziU16 locals and ziU32 result: 175/182 instructions; structural 13, positional differences 68
- Zi8getKeyLayout / r2 key count helper ziU32 locals and ziU16 result: 175/182 instructions; structural 13, positional differences 68
- Zi8getKeyLayout / r2 key count helper ziU32 locals and ziU32 result: 175/182 instructions; structural 13, positional differences 68
- PFFILE_GetSFD / r2 pointer advance in body before index loop update: 113/113 instructions; structural 0, positional differences 18
- PFFILE_GetSFD / r2 index advance in body before pointer loop update: 113/113 instructions; structural 2, positional differences 18
- PFFILE_GetSFD / r2 while loop with separate induction updates: 113/113 instructions; structural 0, positional differences 18
- PFFILE_GetSFD / r2 prefix index and pointer updates: 113/113 instructions; structural 2, positional differences 18
- PFFILE_GetSFD / r2 initialize saved slot index before free slot pointer: 113/113 instructions; structural 2, positional differences 19
- PFFILE_GetSFD / r2 free descriptor predicate helper: 121/113 instructions; structural 13, positional differences 113
- PFFILE_GetSFD / r2 matching directory entry comparison helper: 117/113 instructions; structural 12, positional differences 102
- Zi8ConvertUC2Key / r2 signed key with unsigned bit-pattern reads: 208/207 instructions; structural 17, positional differences 53
- Zi8ConvertUC2Key / r2 constant character and language parameters: 207/207 instructions; structural 0, positional differences 18
- Zi8ConvertUC2Key / r2 explicit constant work pointer parameter: 207/207 instructions; structural 0, positional differences 18
- Zi8ConvertUC2Key / r2 common result block entered by goto after table lookup: 207/207 instructions; structural 0, positional differences 18
- Zi8ConvertUC2Key / r2 inverse entry exclusion condition nested body: 206/207 instructions; structural 13, positional differences 137
- PFFILE_GetSFD / r2 use existing correct SDK volume layout in internal function signature: 113/113 instructions; structural 2, positional differences 28
- PFFILE_GetSFD / r2 correct volume signature and pointer-first loop latch: 113/113 instructions; structural 0, positional differences 28
- PFFILE_GetSFD / r2 correct volume signature and first free index declaration first: 113/113 instructions; structural 2, positional differences 2
- PFFILE_GetSFD / r2 signed traversal index: 113/113 instructions; structural 2, positional differences 18
- PFFILE_GetSFD / r2 signed saved slot index: 113/113 instructions; structural 2, positional differences 18
- PFFILE_GetSFD / r2 signed traversal and saved slot indices: 113/113 instructions; structural 2, positional differences 18
- PFFILE_GetSFD / r2 unsigned int traversal and saved slot indices: 113/113 instructions; structural 2, positional differences 18
- PFFILE_GetSFD / r2 constant volume alias and entry pointers: 113/113 instructions; structural 2, positional differences 18
- PFFILE_GetSFD / r2 typed volume saved index first pointer-first latch: 113/113 instructions; structural 0, positional differences 2
- PFFILE_GetSFD / r2 typed volume saved index first body pointer update: 113/113 instructions; structural 0, positional differences 2
- PFFILE_GetSFD / r2 typed volume saved index first separate while updates: 113/113 instructions; structural 0, positional differences 2
- PFFILE_GetSFD / r2 typed volume saved index first explicit pointer assignment: 113/113 instructions; structural 0, positional differences 2
- PFFILE_GetSFD / r2 typed volume saved index first explicit index assignment: 113/113 instructions; structural 0, positional differences 2
- PFFILE_GetSFD / r2 typed volume saved index first both compound additions: 113/113 instructions; structural 0, positional differences 2
- PFFILE_GetSFD / r2 typed volume saved index first next index temporary: 113/113 instructions; structural 0, positional differences 2
- PFFILE_GetSFD / r2 typed volume saved index first next descriptor temporary: 113/113 instructions; structural 2, positional differences 2
- PFFILE_GetSFD / r2 original formal volume retained after traversal: 113/113 instructions; structural 4, positional differences 5
- PFFILE_GetSFD / r2 original formal volume retained pointer-first latch: 113/113 instructions; structural 2, positional differences 5
- PFFILE_GetSFD / r2 volume traversal alias declared after saved indices: 113/113 instructions; structural 4, positional differences 5
- Zi8ConvertUC2Key / r2 ziPtr work context local declared first: 213/207 instructions; structural 44, positional differences 206
- Zi8ConvertUC2Key / r2 ziPtr work context local declared last: 213/207 instructions; structural 44, positional differences 206
- Zi8ConvertUC2Key / r2 struct __zi8_work_data_s* work context local declared first: 213/207 instructions; structural 44, positional differences 206
- Zi8ConvertUC2Key / r2 struct __zi8_work_data_s* work context local declared last: 213/207 instructions; structural 44, positional differences 206
- Zi8getKeyLayout / r2 noncompound accumulator expression same operand order: 183/182 instructions; structural 7, positional differences 72
- Zi8getKeyLayout / r2 zero test using logical not for lookup result: 182/182 instructions; structural 0, positional differences 16
- Zi8getKeyLayout / r2 chained initialization from index to total: 182/182 instructions; structural 0, positional differences 16
- Zi8getKeyLayout / r2 prefix key index increments in all traversal loops: 182/182 instructions; structural 0, positional differences 16
- Zi8getKeyLayout / r2 builtin character count assignment separated from zero test: 182/182 instructions; structural 1, positional differences 17
- PFFILE_GetSFD / r2 typed volume derive free slot directly from indexed array: 113/113 instructions; structural 0, positional differences 0; EXACT candidate retained
- PFFILE_GetSFD / r2 typed volume indexed free slot with for loop: 113/113 instructions; structural 0, positional differences 0; EXACT candidate retained
- PFFILE_GetSFD / r2 typed volume indexed free slot and declaration-only loop index: 113/113 instructions; structural 0, positional differences 0; EXACT candidate retained
- Zi8ConvertUC2Key / r2 separate every short declaration: 207/207 instructions; structural 0, positional differences 18
- Zi8ConvertUC2Key / r2 key grouped with count index and bounds: 207/207 instructions; structural 0, positional differences 18
- Zi8ConvertUC2Key / r2 lookup index kept wide with narrow reads: 207/207 instructions; structural 0, positional differences 18
- Zi8ConvertUC2Key / r2 default mapping pointer const qualification: 208/207 instructions; structural 13, positional differences 53

Round 2 PFFILE_GetSFD structural resolution: the existing PFFILE_VOLUME_DIRS type is the SDK layout used for all accessed fields, with sfds at 0x40, sizeof(SFD)=0x29c and cluster-link at 0x1f94. Use that type directly in the internal function signature, cast the two callers without changing their generated code. Saved slot index initialization precedes free slot pointer. Derive the free slot from the indexed array instead of maintaining a redundant pointer. The compiler now creates its two induction pointers in target order. 113/113 instructions, diffs 0. Full gate 45/45 exact, code 17820/17820, no data symbols; correct DOL; zero regressions/forbidden/style.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/fa/pf_file] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_file] objdiff: code 17820/17820 data None/None functions 45/45 fuzzy 100.0000 linked code 0
[libs/RVL_SDK/src/fa/pf_file] instruction-exact functions: 45/45
[libs/RVL_SDK/src/fa/pf_file]   section .text size 17820 match 100.0
[libs/RVL_SDK/src/fa/pf_file] baseline: code 17368/17820 data None functions 44 fuzzy 99.9771
regressions vs baseline: 0
global matched_code_percent: 88.60345 -> 88.61855
global fuzzy_match_percent: 99.45553 -> 99.45567
global complete_code_percent: 63.16065 -> 63.16065
global matched_data_percent: 98.50994 -> 98.50994
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
- Zi8getKeyLayout / r2 readonly pointer qualifiers dataAddress: 182/182 instructions; structural 0, positional differences 16
- Zi8getKeyLayout / r2 readonly pointer qualifiers customTable: 182/182 instructions; structural 0, positional differences 16
- Zi8getKeyLayout / r2 readonly pointer qualifiers dataAddress,customTable: 182/182 instructions; structural 0, positional differences 16
- Zi8getKeyLayout / r2 readonly pointer qualifiers keyChars: 183/182 instructions; structural 5, positional differences 140
- Zi8getKeyLayout / r2 readonly pointer qualifiers dataAddress,keyChars: 183/182 instructions; structural 5, positional differences 140
- Zi8getKeyLayout / r2 readonly pointer qualifiers customTable,keyChars: 183/182 instructions; structural 5, positional differences 140
- Zi8getKeyLayout / r2 readonly pointer qualifiers dataAddress,customTable,keyChars: 183/182 instructions; structural 5, positional differences 140
- Zi8ConvertUC2Key / r2 readonly pointer qualifiers table: 207/207 instructions; structural 0, positional differences 18
- Zi8ConvertUC2Key / r2 readonly pointer qualifiers ranges: 207/207 instructions; structural 0, positional differences 18
- Zi8ConvertUC2Key / r2 readonly pointer qualifiers table,ranges: 207/207 instructions; structural 0, positional differences 18
- Zi8ConvertUC2Key / r2 readonly pointer qualifiers entry: 207/207 instructions; structural 0, positional differences 18
- Zi8ConvertUC2Key / r2 readonly pointer qualifiers table,entry: 207/207 instructions; structural 0, positional differences 18
- Zi8ConvertUC2Key / r2 readonly pointer qualifiers ranges,entry: 207/207 instructions; structural 0, positional differences 18
- Zi8ConvertUC2Key / r2 readonly pointer qualifiers table,ranges,entry: 207/207 instructions; structural 0, positional differences 18

Round 2 compiler diagnosis: eZiText units compile with -inline off -opt off, explaining why new helper calls shortened callers without matching target instruction streams. SDK pf_file uses -O4,p -inline auto -ipa file; structural source changes were effective there. No compiler flags changed. zmtkey declaration search tried 52 orders, no improvement, source restored.

Round 2 Zi8ConvertUC2Key expanded declaration search: split the four grouped short declarations, explored 93 orders across all nine declarations, best remained structural 0 / 18 differences. Restored original source, including grouped declarations.

## Round 2 remaining-function audit
- Zi8getKeyLayout: 25 distinct logged source experiments this round; at least three complete, no exact candidate.
- Zi8ConvertUC2Key: 20 distinct logged source experiments this round; at least three complete, no exact candidate.
- PFFILE_GetSFD: exact 113/113, zero instruction differences; all 45 target functions exact after full gate.
- No nonexact source changes retained. Data unchanged and fully paired. Only pf_file source and this attempts log changed.

## Round 2 final full gate over all owned units
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/eZiText/src/clib/zmtkey] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zmtkey] objdiff: code 1488/2216 data 60/60 functions 3/4 fuzzy 99.8466 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zmtkey] instruction-exact functions: 3/4
[libs/RVLMiddleware/eZiText/src/clib/zmtkey]   section .text size 2216 match 99.84657
[libs/RVLMiddleware/eZiText/src/clib/zmtkey]   section extab size 24 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zmtkey]   section extabindex size 36 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zmtkey]   below 100: Zi8getKeyLayout 99.53297
[libs/RVLMiddleware/eZiText/src/clib/zmtkey] baseline: code 1488/2216 data 60 functions 3 fuzzy 99.8466
[libs/RVL_SDK/src/fa/pf_file] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_file] objdiff: code 17820/17820 data None/None functions 45/45 fuzzy 100.0000 linked code 0
[libs/RVL_SDK/src/fa/pf_file] instruction-exact functions: 45/45
[libs/RVL_SDK/src/fa/pf_file]   section .text size 17820 match 100.0
[libs/RVL_SDK/src/fa/pf_file] baseline: code 17368/17820 data None functions 44 fuzzy 99.9771
[libs/RVLMiddleware/eZiText/src/clib/zconvert] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zconvert] objdiff: code 1380/2208 data 112/112 functions 3/4 fuzzy 99.8370 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zconvert] instruction-exact functions: 3/4
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section .rodata size 32 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section .text size 2208 match 99.83696
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section extab size 32 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section extabindex size 48 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   below 100: Zi8ConvertUC2Key 99.565216
[libs/RVLMiddleware/eZiText/src/clib/zconvert] baseline: code 1380/2208 data 112 functions 3 fuzzy 99.8370
regressions vs baseline: 0
global matched_code_percent: 88.60345 -> 88.61855
global fuzzy_match_percent: 99.45553 -> 99.45567
global complete_code_percent: 63.16065 -> 63.16065
global matched_data_percent: 98.50994 -> 98.50994
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Instruction-exact functions / matched code bytes / matched data bytes, before -> after:
- zmtkey: 3->3 / 1488->1488 / 60->60.
- pf_file: 44->45 / 17368->17820 / no data symbols.
- zconvert: 3->3 / 1380->1380 / 112->112.
Commit ac0541dd contains the exact source improvement. Remaining eZiText compiler coloring fixes are unknown.

# Round 3 expanded fuzzy lane
Baseline c44fbd720965dadcc282b8cea9f6fba352c2f559
libs/RVLMiddleware/eZiText/src/clib/zmtkey: POOL IDENTICAL up to 0 (mine=0 base=0)
libs/RVLMiddleware/eZiText/src/clib/zconvert: POOL IDENTICAL up to 0 (mine=0 base=0)
libs/RevoEX/src/nhttp/NHTTP_socket_RVL: POOL IDENTICAL up to 0 (mine=0 base=0)
src/scene/channelSelect/iplChannelObj: POOL IDENTICAL up to 20 (mine=20 base=20)
src/scene/board/iplBoard: POOL IDENTICAL up to 18 (mine=18 base=18)
libs/NW4R/src/lyt/lyt_window: POOL IDENTICAL up to 1 (mine=1 base=1)
- Zi8getKeyLayout / r3 byte pair index shift rather than multiply: 182/182 instructions; structural 0, positional differences 16
- Zi8getKeyLayout / r3 sum offset explicitly grouped with key header: 182/182 instructions; structural 0, positional differences 16
- Zi8getKeyLayout / r3 explicit mapped key failure comparison: 182/182 instructions; structural 0, positional differences 16
- Zi8ConvertUC2Key / r3 separate entry value byte assembly: 207/207 instructions; structural 2, positional differences 22
- Zi8ConvertUC2Key / r3 use shift for character stride: 207/207 instructions; structural 0, positional differences 18
- Zi8ConvertUC2Key / r3 explicit braces around user key return: 207/207 instructions; structural 0, positional differences 18
- NHTTPi_SocRecv_sub / r3 memcpy source offset evaluated into local: BUILD FAIL nclude/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RevoEX/src/nhttp/NHTTP_socket_RVL.c -o build/43U/src/libs/RevoEX/src/nhttp && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RevoEX/src/nhttp/NHTTP_socket_RVL.d build/43U/src/libs/RevoEX/src/nhttp/NHTTP_socket_RVL.d ### mwcceppc.exe Compiler: #    File: libs\RevoEX\src\nhttp\NHTTP_socket_RVL.c # ------------------------------------------------- #      99:             u8* source = buffer + connection->recvBufOffset;  #   Error:             ^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
- NHTTPi_SocRecv_sub / r3 pass source offset plus buffer in opposite operand order: 67/67 instructions; structural 0, positional differences 4
- NHTTPi_SocRecv_sub / r3 narrow unsigned count local reused for copy length: 67/67 instructions; structural 0, positional differences 4
- NHTTPi_SocRecv_sub / r3 copy source local declared before body: 67/67 instructions; structural 0, positional differences 4
- NHTTPi_SocRecv_sub / r3 copy offset local declared before body: 67/67 instructions; structural 0, positional differences 4
- NHTTPi_SocRecv_sub / r3 inline received copy boundary: 67/67 instructions; structural 0, positional differences 4
- NHTTPi_SocSend_sub / r3 leading send positive branch with negative else: 102/102 instructions; structural 0, positional differences 0; EXACT candidate retained
- NHTTPi_SocSend_sub / r3 leading send nested complete transfer branch: 102/102 instructions; structural 4, positional differences 5
- NHTTPi_SocSend_sub / r3 leading send separate nonpositive and short branches: 102/102 instructions; structural 4, positional differences 5

Round 3 structural diagnosis:
- Zi8getKeyLayout: 182/182, unchanged frame and branches, language/count r26/r27 tie remains.
- Zi8ConvertUC2Key: 207/207, unchanged frame and branches, work/key r27/r28 tie remains.
- NHTTPi_SocRecv_sub: 67/67, identical 0x20 frame, only memcpy argument scheduling differs in four instructions.
- NHTTPi_SocSend_sub: 101/102, aligned frame identical, leading partial transfer uses early returns while target has a positive-result block and negative else, with two redundant branch boundaries. Positive block restored exact 102/102.
- NHTTPi_SocSend: 43/43, identical 0x10 frame, SSL id field load precedes register save in target but follows it in ours.
- setLangPane: 195/195, stack byte arrays misplaced and language code indexing uses byte stride where target has four-byte records; loop pointer temporaries differ.
- calcCursorAnim: objdiff 100%, three conditional CR1 branch operands in ctxdiff are misdecoded by odiff as absolute offsets. disasm_fn decodes real local relative branches; no source change needed. The instruction-exact gate count discrepancy is advisory-tool normalization, not a new unmatched function.
- appendRecord: 283/283, frame 0x90 vs target 0xa0; interrupt saves promoted to registers whereas target stores three flags beside the address-taken dataSize slot.
- DrawFrame: 376/376, instruction skeleton and float schedule identical; saved register allocation shifted, static texture-coordinate map placed in r31 instead of r21; data .sdata2 gap requires separate inspection.
- NHTTPi_SocSend / r3 direct SSL id field reads without saved local: 43/43 instructions; structural 2, positional differences 3
- NHTTPi_SocSend / r3 SSL id initialization before result declaration: 43/43 instructions; structural 2, positional differences 3
- NHTTPi_SocSend / r3 assignment in SSL comparison instead of initializer: 43/43 instructions; structural 2, positional differences 3
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r3 language code records represented as ten four-byte strings: 196/195 instructions; structural 16, positional differences 120
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r3 language records and uncached fallback group names: 196/195 instructions; structural 16, positional differences 120
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r3 language records and four-byte RSO name buffer: 196/195 instructions; structural 25, positional differences 126
- appendRecord__Q33ipl5scene5BoardFP10_CDBRecord / r3 record read state groups interrupt saves with address-taken size: BUILD FAIL :6 #       Z:\mnt\drive2\projects\wii-ipl-workers\data- #   d6\include\scene\iplSceneManager.h:14 #       Z:\mnt\drive2\projects\wii-ipl-workers\data-d6\include\iplSceneUI.h:11 #       Z:\mnt\drive2\projects\wii-ipl-workers\data- #   d6\src\scene\board\iplBoard.cpp:4) ### mwcceppc.exe Compiler: #    File: src\scene\board\iplBoard.cpp # ------------------------------------- #     508:             if (!cdbManager->getDataSize(record, &interrupts.dataSize)) {  #   Error:                                                              ^^^^^^^^ #   (10140) undefined identifier 'dataSize' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
- appendRecord__Q33ipl5scene5BoardFP10_CDBRecord / r3 record read state before metadata declarations: BUILD FAIL workers\data- #   d6\include\scene\iplSceneBase.h:6 #       Z:\mnt\drive2\projects\wii-ipl-workers\data- #   d6\include\scene\iplSceneManager.h:14 #       Z:\mnt\drive2\projects\wii-ipl-workers\data-d6\include\iplSceneUI.h:11 #       Z:\mnt\drive2\projects\wii-ipl-workers\data- #   d6\src\scene\board\iplBoard.cpp:4) ### mwcceppc.exe Compiler: #    File: src\scene\board\iplBoard.cpp # ------------------------------------- #     449:             struct RecordReadState {  #   Error:                                    ^ #   (10296) class 'ipl::scene::Board::RecordReadState' redefined #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
- appendRecord__Q33ipl5scene5BoardFP10_CDBRecord / r3 independent interrupt state locals instead of promotable struct: 283/283 instructions; structural 52, positional differences 48
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r3 four-byte language records and stop after fallback group: 196/195 instructions; structural 8, positional differences 54
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r3 records fallback stop and explicit current group pointer: 196/195 instructions; structural 8, positional differences 66
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r3 records fallback stop and uncached fallback group: 195/195 instructions; structural 4, positional differences 8
- appendRecord__Q33ipl5scene5BoardFP10_CDBRecord / r3 corrected read state with escaping data size: 283/283 instructions; structural 29, positional differences 29
- appendRecord__Q33ipl5scene5BoardFP10_CDBRecord / r3 corrected read state declared before metadata: 283/283 instructions; structural 38, positional differences 38
- appendRecord__Q33ipl5scene5BoardFP10_CDBRecord / r3 corrected read state reverse interrupt declaration order: 283/283 instructions; structural 29, positional differences 29
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r3 four-byte records with eight-byte RSO names: 195/195 instructions; structural 1, positional differences 5
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r3 four-byte records names8 and null-terminated fallback table: 195/195 instructions; structural 0, positional differences 4
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r3 null-terminated fallback table preserving six-byte names: 195/195 instructions; structural 3, positional differences 7
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r3 shared group declaration: 195/195 instructions; structural 0, positional differences 4
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r3 iterator initializer from group expression: 195/195 instructions; structural 3, positional differences 5

## lyt_window round3
- Fetch origin: owned source unchanged; pool identical. DrawFrame 376/376, frame0xe0 identical; inlined texture helper allocation shifts preserved argument registers; inspect declaration lifetime before register search.
- DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc / r3 declare colors before material setup: 372/376 instructions; structural 90, positional differences 374
- DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc / r3 declare geometry before texture coordinates: 376/376 instructions; structural 0, positional differences 119
- DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc / r3 draw quad use conditional colors temporary: 364/376 instructions; structural 188, positional differences 373
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r3 group declared before language: 195/195 instructions; structural 0, positional differences 4
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r3 group declared before found flag: 195/195 instructions; structural 0, positional differences 4
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r3 group and outer iterator both explicit: 196/195 instructions; structural 4, positional differences 191
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r3 pane iterator declared before group pointers: BUILD FAIL \wii-ipl-workers\data- #   d6\include\system\iplSystem.h:15 #       Z:\mnt\drive2\projects\wii-ipl-workers\data-d6\include\iplSystem.h:9 #       Z:\mnt\drive2\projects\wii-ipl-workers\data- #   d6\src\scene\channelSelect\iplChannelObj.cpp:8) ### mwcceppc.exe Compiler: #    File: src\scene\channelSelect\iplChannelObj.cpp # -------------------------------------------------- #     645: st().GetBeginIter(); it != layout->GetGroupList().GetEndIter(); paneIt++) {  #   Error:                                                                 ^^^^^^ #   (10140) undefined identifier 'paneIt' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r3 pane list reference instead of group pointer: 195/195 instructions; structural 6, positional differences 6
- appendRecord__Q33ipl5scene5BoardFP10_CDBRecord / r3 unified metadata and read state structure: 279/283 instructions; structural 18, positional differences 258
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r3 separate pane iterator declarations: 199/195 instructions; structural 9, positional differences 86
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r3 const group pointer: 195/195 instructions; structural 0, positional differences 4
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r3 pane iterators prefix increment: 187/195 instructions; structural 51, positional differences 93
- appendRecord__Q33ipl5scene5BoardFP10_CDBRecord / r3 metadata zeroing loop: 284/283 instructions; structural 23, positional differences 249
- appendRecord__Q33ipl5scene5BoardFP10_CDBRecord / r3 read state constructor initializes type array: 277/283 instructions; structural 20, positional differences 265
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r3 shared inline visibility helper: 153/195 instructions; structural 77, positional differences 103
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r3 group references instead of pointers: 195/195 instructions; structural 0, positional differences 4
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r3 found flag integer boolean: 195/195 instructions; structural 0, positional differences 4
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r3 group pointer declaration before assignment in each branch: 195/195 instructions; structural 0, positional differences 4
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r3 pane iterator comparison reversed: 195/195 instructions; structural 14, positional differences 14
- DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc / r3 texture flip helper uses explicit selected entry pointer: 376/376 instructions; structural 0, positional differences 119
- DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc / r3 texture flip helper uses table pointer indexing: 376/376 instructions; structural 0, positional differences 119
- DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc / r3 texture helper y index declaration first: 376/376 instructions; structural 0, positional differences 119
- appendRecord__Q33ipl5scene5BoardFP10_CDBRecord / r3 read state owns interrupt flags and scalar metadata: 283/283 instructions; structural 59, positional differences 58

### Round 3 declaration search and data ownership audit
- Zi8getKeyLayout: 52 declaration orders after structural attempts, best (0,16), original restored.
- NHTTPi_SocRecv_sub: two leading declaration orders, best (0,4), original restored.
- NHTTPi_SocSend: two leading declaration orders, best (2,3), original restored; remaining three differences are SSL-id load scheduling, not a frame mismatch.
- setLangPane: two initialized language declarations and 23 expanded leading declaration orders, best (0,4); target still colors both group pointers r30 whereas compiler selects r28. The four-byte language records, eight-byte RSO name buffer and null-terminated/first-match fallback correct the structural skeleton; all fuzzy candidates restored because no exact function gained.
- appendRecord: grouping flags with escaping dataSize forces the target spills and frame; best structural experiment 29 stack-slot differences. Expanded declaration search 76 orders stopped at (45,57); all candidates restored because none exact. Unified metadata structures and their zero-initialization alternatives failed to reproduce the target local layout without extra initialization instructions.
- DrawFrame: 52 declaration orders, best (0,119); helper index declarations and explicit selected-entry/table pointers leave allocation unchanged. All candidates restored.
- Data: zmtkey 60/60, zconvert 112/112, ChannelObj 2216/2216, Board 896/896; NHTTP has no data symbols. No symbol-name or extent edit justified in these units.
- lyt_window relocation proof: target .sdata2 offsets0..19 are five distinct RGBA byte quartets used by GetVtxColorElement, SetVtxColorElement, DrawFrame4/8, GetVtxColor and SetVtxColor; target offsets40..43 are scLytFatalColorR/G/B/A used by GetFrameMaterial. Ours emits only the shared named quartet at0..3; this is a real 16-byte duplicate-constant emission gap, not a missing-name pair or weak vtable. No fake objects, labels or extent changes added. Target .sdata2 total48, source24; remaining float/double constants retain proper relocation uses.
- Audit: every objdiff-open function has at least three distinct successful source-level experiments in this round. NHTTPi_SocSend_sub is exact and committed; others remain open as documented. calcCursorAnim is already objdiff100 and is only an instruction-normalization artifact.

- Advisory literal_reference_diff: 182 functions analyzed, 86 arguments checked, zero candidates/errors/skips. This checks actual string bytes at corresponding uses and does not claim complete data matching.
- Zi8ConvertUC2Key: final corrected leading-declarations range127..132, 36 orders, best(0,18); original restored. The preceding wider range accidentally included the first if statement and its invalid permutations were discarded.
- Final successful-attempt count audit: Zi8getKeyLayout=3, Zi8ConvertUC2Key=3, NHTTPi_SocRecv_sub=5, NHTTPi_SocSend_sub=3, NHTTPi_SocSend=3, setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object=23, appendRecord__Q33ipl5scene5BoardFP10_CDBRecord=8, DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc=6.

## Round 3 final full gate (all six units)
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/eZiText/src/clib/zmtkey] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zmtkey] objdiff: code 1488/2216 data 60/60 functions 3/4 fuzzy 99.8466 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zmtkey] instruction-exact functions: 3/4
[libs/RVLMiddleware/eZiText/src/clib/zmtkey]   section .text size 2216 match 99.84657
[libs/RVLMiddleware/eZiText/src/clib/zmtkey]   section extab size 24 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zmtkey]   section extabindex size 36 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zmtkey]   below 100: Zi8getKeyLayout 99.53297
[libs/RVLMiddleware/eZiText/src/clib/zmtkey] baseline: code 1488/2216 data 60 functions 3 fuzzy 99.8466
[libs/RVLMiddleware/eZiText/src/clib/zconvert] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zconvert] objdiff: code 1380/2208 data 112/112 functions 3/4 fuzzy 99.8370 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zconvert] instruction-exact functions: 3/4
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section .rodata size 32 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section .text size 2208 match 99.83696
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section extab size 32 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section extabindex size 48 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   below 100: Zi8ConvertUC2Key 99.565216
[libs/RVLMiddleware/eZiText/src/clib/zconvert] baseline: code 1380/2208 data 112 functions 3 fuzzy 99.8370
[libs/RevoEX/src/nhttp/NHTTP_socket_RVL] pool: IDENTICAL
[libs/RevoEX/src/nhttp/NHTTP_socket_RVL] objdiff: code 1700/2140 data None/None functions 8/10 fuzzy 99.5701 linked code 0
[libs/RevoEX/src/nhttp/NHTTP_socket_RVL] instruction-exact functions: 8/10
[libs/RevoEX/src/nhttp/NHTTP_socket_RVL]   section .text size 2140 match 99.57009
[libs/RevoEX/src/nhttp/NHTTP_socket_RVL]   below 100: NHTTPi_SocRecv_sub 99.55224
[libs/RevoEX/src/nhttp/NHTTP_socket_RVL]   below 100: NHTTPi_SocSend 95.34884
[libs/RevoEX/src/nhttp/NHTTP_socket_RVL] baseline: code 1292/2140 data None functions 7 fuzzy 98.9907
[src/scene/channelSelect/iplChannelObj] pool: IDENTICAL
[src/scene/channelSelect/iplChannelObj] objdiff: code 10144/10924 data 2216/2216 functions 55/56 fuzzy 99.7993 linked code 0
[src/scene/channelSelect/iplChannelObj] instruction-exact functions: 54/56
[src/scene/channelSelect/iplChannelObj]   section .data size 1240 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .rodata size 784 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .sdata size 120 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .sdata2 size 72 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .text size 10924 match 99.79934
[src/scene/channelSelect/iplChannelObj]   below 100: setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object 97.18974
[src/scene/channelSelect/iplChannelObj] baseline: code 10144/10924 data 2216 functions 55 fuzzy 99.7993
[src/scene/board/iplBoard] pool: IDENTICAL
[src/scene/board/iplBoard] objdiff: code 19144/20276 data 896/896 functions 93/94 fuzzy 99.8765 linked code 0
[src/scene/board/iplBoard] instruction-exact functions: 93/94
[src/scene/board/iplBoard]   section .data size 744 match 100.0
[src/scene/board/iplBoard]   section .rodata size 104 match 100.0
[src/scene/board/iplBoard]   section .sdata size 40 match 100.0
[src/scene/board/iplBoard]   section .sdata2 size 8 match 100.0
[src/scene/board/iplBoard]   section .text size 20276 match 99.8765
[src/scene/board/iplBoard]   below 100: appendRecord__Q33ipl5scene5BoardFP10_CDBRecord 97.78799
[src/scene/board/iplBoard] baseline: code 19144/20276 data 896 functions 93 fuzzy 99.8765
[libs/NW4R/src/lyt/lyt_window] pool: IDENTICAL
[libs/NW4R/src/lyt/lyt_window] objdiff: code 9848/11352 data 268/316 functions 20/21 fuzzy 99.7586 linked code 0
[libs/NW4R/src/lyt/lyt_window] instruction-exact functions: 20/21
[libs/NW4R/src/lyt/lyt_window]   section .ctors size 4 match 100.0
[libs/NW4R/src/lyt/lyt_window]   section .data size 256 match 100.0
[libs/NW4R/src/lyt/lyt_window]   section .sbss size 8 match 100.0
[libs/NW4R/src/lyt/lyt_window]   section .sdata2 size 48 match 66.66667
[libs/NW4R/src/lyt/lyt_window]   section .text size 11352 match 99.75864
[libs/NW4R/src/lyt/lyt_window]   below 100: DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc 98.17819
[libs/NW4R/src/lyt/lyt_window] baseline: code 9848/11352 data 268 functions 20 fuzzy 99.7586
regressions vs baseline: 0
global matched_code_percent: 88.66222 -> 88.67584
global fuzzy_match_percent: 99.47330 -> 99.47371
global complete_code_percent: 63.16065 -> 63.16065
global matched_data_percent: 98.51344 -> 98.51344
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Before -> after instruction-exact functions / objdiff code bytes / matched data bytes:
- zmtkey: 3/4 -> 3/4; 1488 -> 1488; 60 -> 60.
- zconvert: 3/4 -> 3/4; 1380 -> 1380; 112 -> 112.
- NHTTP_socket_RVL: 7/10 -> 8/10; 1292 -> 1700; no data symbols.
- iplChannelObj: instruction gate 54/56 -> 54/56 (objdiff 55/56 unchanged, calcCursorAnim decoding artifact); 10144 -> 10144; 2216 -> 2216.
- iplBoard: 93/94 -> 93/94; 19144 -> 19144; 896 -> 896.
- lyt_window: 20/21 -> 20/21; 9848 -> 9848; 268 -> 268.
Final full gate passes, correct DOL SHA1, zero regressions, zero net forbidden patterns and zero readability warnings. NHTTPi_SocSend_sub has 102/102 instructions and ctxdiff diffs0 after the clean build. Remaining compiler allocation/local layout fixes and the lyt_window duplicate-constant emission are unresolved. Only NHTTP_socket_RVL.c and this attempts log differ from round3 baseline; source improvement commit bf69c042.

# Round 4
Baseline 950bb0dda6ba1980970a54d6f575670f4e07aee8; fetch origin/main b84b3c0d; all six owned sources unchanged remotely.
- libs/RevoEX/src/nhttp/NHTTP_socket_RVL: POOL IDENTICAL up to 0 (mine=0 base=0)
- src/scene/channelSelect/iplChannelObj: POOL IDENTICAL up to 20 (mine=20 base=20)
- src/scene/board/iplBoard: POOL IDENTICAL up to 18 (mine=18 base=18)
- libs/NW4R/src/lyt/lyt_window: POOL IDENTICAL up to 1 (mine=1 base=1)
- libs/RVLMiddleware/eZiText/src/clib/zmtkey: POOL IDENTICAL up to 0 (mine=0 base=0)
- libs/RVLMiddleware/eZiText/src/clib/zconvert: POOL IDENTICAL up to 0 (mine=0 base=0)
- Recv_sub structural diagnosis: 67/67, same0x20 frame/branches, only source-offset load and memcpy argument moves reordered at37..40; last-round temporaries did not help. This round probes operand expression and helper argument boundaries.
- NHTTPi_SocRecv_sub / r4 array subscript address for buffered source: 67/67 instructions; structural 0, positional differences 4
- NHTTPi_SocRecv_sub / r4 copy helper evaluates offset before destination: 67/67 instructions; structural 0, positional differences 4
- NHTTPi_SocRecv_sub / r4 copy helper size-first parameter ordering: 67/67 instructions; structural 0, positional differences 4
- setLangPane diagnosis:195/195; initial structural fixes are four-byte records, eight-byte name capacity and terminating fallback table/first match. Last round narrowed to four pointer-register differences. Reconstruct that candidate to inspect further loop scopes.
- Send diagnosis:43/43,0x10 frame identical; early SSL-id load scheduled after save/copy instead of before. Probe expression branch, const local and helper boundary before register search.
- NHTTPi_SocSend / r4 conditional operator chooses socket writer: 43/43 instructions; structural 2, positional differences 3
- NHTTPi_SocSend / r4 const saved SSL identifier: 43/43 instructions; structural 2, positional differences 3
- NHTTPi_SocSend / r4 inline SSL identifier accessor: 43/43 instructions; structural 2, positional differences 3
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r4 structural candidate with distinct group pointer names: 195/195 instructions; structural 0, positional differences 4
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r4 explicit pane loop scopes: 195/195 instructions; structural 0, positional differences 4
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r4 range group pointer initialized through iterator dereference type: 195/195 instructions; structural 0, positional differences 4
- appendRecord structural diagnosis:283/283, frame0x90 vs0xa0; target three interruption saves spill beside metadata. Prior read-state groups forced spills but slots differ. Probe contiguous metadata state with explicit real type-array initialization and scoped status locals.
- appendRecord__Q33ipl5scene5BoardFP10_CDBRecord / r4 metadata state type bytes explicitly cleared: 283/283 instructions; structural 12, positional differences 8
- appendRecord__Q33ipl5scene5BoardFP10_CDBRecord / r4 reverse loop clearing metadata type bytes: 284/283 instructions; structural 23, positional differences 249
- appendRecord__Q33ipl5scene5BoardFP10_CDBRecord / r4 interrupt states declared at each disabling call: 283/283 instructions; structural 52, positional differences 57
- lyt_window extent proof: scLytFatalColorA at0x81695553 is source extern C const u8 (size1) and GetFrameMaterial loads it with lbz before assembling GXColor RGBA; target recorded size5 includes four trailing section-alignment bytes. Correct size5->1; address and .sdata2 section total remain unchanged, four padding bytes unowned.
- appendRecord__Q33ipl5scene5BoardFP10_CDBRecord / r4 metadata type bytes initialized ascending: 283/283 instructions; structural 0, positional differences 0; EXACT candidate retained
- appendRecord__Q33ipl5scene5BoardFP10_CDBRecord / r4 metadata type chained assignments reversed: 283/283 instructions; structural 0, positional differences 0; EXACT candidate retained
- DrawFrame diagnosis:376/376, frame0xe0 identical; all119 surviving differences are register coloring including static flip table r31/r21 and subsequent temporary allocation. Probe geometry/quad storage boundaries before final declaration search.
- DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc / r4 quad texture coordinates passed by first element address: 376/376 instructions; structural 0, positional differences 119
- DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc / r4 geometry aggregated into local quad state: 376/376 instructions; structural 23, positional differences 142
- DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc / r4 material kept as meaningful local before texture check: 375/376 instructions; structural 8, positional differences 364
- appendRecord exact result: one RecordReadState groups all real metadata and three saved interruption flags; address-taken metadata causes the target stack storage rather than promotion. Target offsets relative to sp: third8,dataSize0xc,second0x10,first0x14,second-of-minute0x18,minute0x1c,hour0x20,gameCode0x24,CDBId0x28,type0x30,Date0x38,key0x48. All fields are consumed by real metadata/restore calls. Clearing the real eight-byte type buffer in ascending byte order reproduces target stores; no padding or dummy objects. Final readable candidate uses separate byte assignments, recordSecond name, 283/283 and ctxdiff diffs0.

### First round4 gate
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/board/iplBoard] pool: IDENTICAL
[src/scene/board/iplBoard] objdiff: code 20276/20276 data 896/896 functions 94/94 fuzzy 100.0000 linked code 0
[src/scene/board/iplBoard] instruction-exact functions: 94/94
[src/scene/board/iplBoard]   section .data size 744 match 100.0
[src/scene/board/iplBoard]   section .rodata size 104 match 100.0
[src/scene/board/iplBoard]   section .sdata size 40 match 100.0
[src/scene/board/iplBoard]   section .sdata2 size 8 match 100.0
[src/scene/board/iplBoard]   section .text size 20276 match 100.0
[src/scene/board/iplBoard] baseline: code 19144/20276 data 896 functions 93 fuzzy 99.8765
[libs/NW4R/src/lyt/lyt_window] pool: IDENTICAL
[libs/NW4R/src/lyt/lyt_window] objdiff: code 9848/11352 data 268/316 functions 20/21 fuzzy 99.7586 linked code 0
[libs/NW4R/src/lyt/lyt_window] instruction-exact functions: 20/21
[libs/NW4R/src/lyt/lyt_window]   section .ctors size 4 match 100.0
[libs/NW4R/src/lyt/lyt_window]   section .data size 256 match 100.0
[libs/NW4R/src/lyt/lyt_window]   section .sbss size 8 match 100.0
[libs/NW4R/src/lyt/lyt_window]   section .sdata2 size 48 match 70.588234
[libs/NW4R/src/lyt/lyt_window]   section .text size 11352 match 99.75864
[libs/NW4R/src/lyt/lyt_window]   below 100: DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc 98.17819
[libs/NW4R/src/lyt/lyt_window] baseline: code 9848/11352 data 268 functions 20 fuzzy 99.7586
regressions vs baseline: 0
global matched_code_percent: 88.74257 -> 88.78037
global fuzzy_match_percent: 99.47580 -> 99.47663
global complete_code_percent: 64.69724 -> 64.69724
global matched_data_percent: 98.77142 -> 98.77142
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: config/43U/symbols.txt (orchestrator reviews every config/symbols change)
GATE PASS
```
- Zi8getKeyLayout diagnosis:182/182, frame/branches/operand order identical; r26/r27 language/count still exchanged. Probe char-count assignment boundary, custom-key copy loop and pointer offset decomposition before declaration search.
- Zi8getKeyLayout / r4 character count assigned before emptiness branch: 182/182 instructions; structural 1, positional differences 17
- Zi8getKeyLayout / r4 custom-key copy as while loop: 182/182 instructions; structural 0, positional differences 16
- Zi8getKeyLayout / r4 separate skip key header and character offset: 182/182 instructions; structural 2, positional differences 20
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r4 const node iterators for visibility loops: 195/195 instructions; structural 0, positional differences 4
- Zi8ConvertUC2Key diagnosis:207/207, frame and branch skeleton identical; work/key r27/r28 exchanged. Probe mapped table addressing and valid-character loop forms before declaration search.
- Zi8ConvertUC2Key / r4 mapped character table explicit subscript address: 207/207 instructions; structural 0, positional differences 18
- Zi8ConvertUC2Key / r4 single-range exit uses explicit braces: 207/207 instructions; structural 0, positional differences 18
- Zi8ConvertUC2Key / r4 character invalid range expressed as negated valid range: 207/207 instructions; structural 0, positional differences 18
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r4 found language exits before fallback block: 195/195 instructions; structural 0, positional differences 4
- setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object / r4 explicit language fallback control labels: 195/195 instructions; structural 0, positional differences 4

### Round4 final open-function and data audit
- Recv_sub: three successful source variants, final declaration search two orders best(0,4); restored baseline, scheduling unchanged.
- Send: three successful source variants, final declaration search two orders best(2,3); restored baseline, scheduling unchanged.
- setLangPane: six successful variants after reconstructing last-round structural fix; final leading declaration search23 orders best(0,4); all fuzzy candidates restored. Original stays97.18974%, candidate's only four differences are r28/r30 group pointers. No exact result claimed. calcCursorAnim remains objdiff100; instruction counter's54/56 remains the previously documented conditional-branch normalization artifact.
- DrawFrame: three successful variants; final declaration search52 orders best(0,119); restored baseline. Texture flip/argument coloring remains unresolved.
- Zi8getKeyLayout: three successful variants; declaration search52 orders best(0,16); restored baseline.
- Zi8ConvertUC2Key: three successful variants; correct six-declaration search36 orders best(0,18); restored baseline.
- appendRecord now exact: readable interrupt field names slotInterrupts/waitInterrupts/recordInterrupts preserve283/283 and ctxdiff diffs0. No declaration search needed after resolving the structural stack layout.
- Successful-attempt audit: NHTTPi_SocRecv_sub=3, NHTTPi_SocSend=3, setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object=6, appendRecord__Q33ipl5scene5BoardFP10_CDBRecord=5, DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc=3, Zi8getKeyLayout=3, Zi8ConvertUC2Key=3. All remaining objdiff-open functions have at least three distinct successful source-level attempts this round.
- Data ownership: NHTTP has no data symbols; ChannelObj, Board, zmtkey and zconvert retain100% data, no supported rename/extent correction found. lyt_window .data/vtables are100%; .sdata2 target48 bytes vs source24 reflects16 bytes of duplicated fatal RGBA constants plus trailing alignment. Target unnamed quartets have no distinct real source objects to pair by name, so no renames justified. Four trailing bytes of scLytFatalColorA's old extent were corrected to unowned padding with the relocation/type proof above. Section addresses/totals remain unchanged. No weak vtables suppressed.

- Final advisory literal-reference audit:183 matched functions,86 arguments checked, no candidates/errors/skips. Final formatting cleanup removed a whitespace-only line and wrapped metadata call; ctxdiff remains283/283,diffs0.

## Round4 final full gate over all units
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nhttp/NHTTP_socket_RVL] pool: IDENTICAL
[libs/RevoEX/src/nhttp/NHTTP_socket_RVL] objdiff: code 1700/2140 data None/None functions 8/10 fuzzy 99.5701 linked code 0
[libs/RevoEX/src/nhttp/NHTTP_socket_RVL] instruction-exact functions: 8/10
[libs/RevoEX/src/nhttp/NHTTP_socket_RVL]   section .text size 2140 match 99.57009
[libs/RevoEX/src/nhttp/NHTTP_socket_RVL]   below 100: NHTTPi_SocRecv_sub 99.55224
[libs/RevoEX/src/nhttp/NHTTP_socket_RVL]   below 100: NHTTPi_SocSend 95.34884
[libs/RevoEX/src/nhttp/NHTTP_socket_RVL] baseline: code 1700/2140 data None functions 8 fuzzy 99.5701
[src/scene/channelSelect/iplChannelObj] pool: IDENTICAL
[src/scene/channelSelect/iplChannelObj] objdiff: code 10144/10924 data 2216/2216 functions 55/56 fuzzy 99.7993 linked code 0
[src/scene/channelSelect/iplChannelObj] instruction-exact functions: 54/56
[src/scene/channelSelect/iplChannelObj]   section .data size 1240 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .rodata size 784 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .sdata size 120 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .sdata2 size 72 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .text size 10924 match 99.79934
[src/scene/channelSelect/iplChannelObj]   below 100: setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object 97.18974
[src/scene/channelSelect/iplChannelObj] baseline: code 10144/10924 data 2216 functions 55 fuzzy 99.7993
[src/scene/board/iplBoard] pool: IDENTICAL
[src/scene/board/iplBoard] objdiff: code 20276/20276 data 896/896 functions 94/94 fuzzy 100.0000 linked code 0
[src/scene/board/iplBoard] instruction-exact functions: 94/94
[src/scene/board/iplBoard]   section .data size 744 match 100.0
[src/scene/board/iplBoard]   section .rodata size 104 match 100.0
[src/scene/board/iplBoard]   section .sdata size 40 match 100.0
[src/scene/board/iplBoard]   section .sdata2 size 8 match 100.0
[src/scene/board/iplBoard]   section .text size 20276 match 100.0
[src/scene/board/iplBoard] baseline: code 19144/20276 data 896 functions 93 fuzzy 99.8765
[libs/NW4R/src/lyt/lyt_window] pool: IDENTICAL
[libs/NW4R/src/lyt/lyt_window] objdiff: code 9848/11352 data 268/316 functions 20/21 fuzzy 99.7586 linked code 0
[libs/NW4R/src/lyt/lyt_window] instruction-exact functions: 20/21
[libs/NW4R/src/lyt/lyt_window]   section .ctors size 4 match 100.0
[libs/NW4R/src/lyt/lyt_window]   section .data size 256 match 100.0
[libs/NW4R/src/lyt/lyt_window]   section .sbss size 8 match 100.0
[libs/NW4R/src/lyt/lyt_window]   section .sdata2 size 48 match 70.588234
[libs/NW4R/src/lyt/lyt_window]   section .text size 11352 match 99.75864
[libs/NW4R/src/lyt/lyt_window]   below 100: DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc 98.17819
[libs/NW4R/src/lyt/lyt_window] baseline: code 9848/11352 data 268 functions 20 fuzzy 99.7586
[libs/RVLMiddleware/eZiText/src/clib/zmtkey] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zmtkey] objdiff: code 1488/2216 data 60/60 functions 3/4 fuzzy 99.8466 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zmtkey] instruction-exact functions: 3/4
[libs/RVLMiddleware/eZiText/src/clib/zmtkey]   section .text size 2216 match 99.84657
[libs/RVLMiddleware/eZiText/src/clib/zmtkey]   section extab size 24 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zmtkey]   section extabindex size 36 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zmtkey]   below 100: Zi8getKeyLayout 99.53297
[libs/RVLMiddleware/eZiText/src/clib/zmtkey] baseline: code 1488/2216 data 60 functions 3 fuzzy 99.8466
[libs/RVLMiddleware/eZiText/src/clib/zconvert] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zconvert] objdiff: code 1380/2208 data 112/112 functions 3/4 fuzzy 99.8370 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zconvert] instruction-exact functions: 3/4
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section .rodata size 32 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section .text size 2208 match 99.83696
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section extab size 32 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section extabindex size 48 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   below 100: Zi8ConvertUC2Key 99.565216
[libs/RVLMiddleware/eZiText/src/clib/zconvert] baseline: code 1380/2208 data 112 functions 3 fuzzy 99.8370
regressions vs baseline: 0
global matched_code_percent: 88.74257 -> 88.78037
global fuzzy_match_percent: 99.47580 -> 99.47663
global complete_code_percent: 64.69724 -> 64.69724
global matched_data_percent: 98.77142 -> 98.77142
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: config/43U/symbols.txt (orchestrator reviews every config/symbols change)
GATE PASS
```

Before -> after instruction-exact functions / objdiff matched code bytes / matched data bytes:
- NHTTP_socket_RVL:8/10->8/10 /1700->1700 /no data symbols.
- iplChannelObj:54/56->54/56 raw instruction counter,55/56->55/56 objdiff;10144->10144 /2216->2216. The calcCursorAnim counter discrepancy is unchanged.
- iplBoard:93/94->94/94 /19144->20276 /896->896. All code/data sections100%.
- lyt_window:20/21->20/21 /9848->9848 /268->268; scLytFatalColorA extent5->1, target section size48 unchanged.
- zmtkey:3/4->3/4 /1488->1488 /60->60.
- zconvert:3/4->3/4 /1380->1380 /112->112.
Remaining objdiff-open functions: NHTTPi_SocRecv_sub99.55224% scheduling;NHTTPi_SocSend95.34884% scheduling;setLangPane97.18974% original stack/branch structure (structurally corrected candidate remains four register differences);DrawFrame98.17819% coloring;Zi8getKeyLayout99.53297% language/count coloring;Zi8ConvertUC2Key99.565216% work/key coloring. All at least three successful distinct attempts this round, restored. Unresolved data emission:lyt_window16 duplicated fatal-color bytes; no evidence justifying data symbol renames.
Changed paths:src/scene/board/iplBoard.cpp,config/43U/symbols.txt,tools/decomp-assist/fz2.attempts.md. Source/extent improvement committed f70c5ddc; final descriptive field names and audit are committed separately after final GATE PASS. No untried remaining functions.
