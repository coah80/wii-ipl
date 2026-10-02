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
