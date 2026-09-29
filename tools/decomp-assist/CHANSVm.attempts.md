# CHANSVm continuation attempt log

The live checkout started at 02e50d2d without the earlier CHANSVm source changes or its attempt log, despite the continuation description. The live gate baseline is used below. No branch, remote or worktree operations were performed.

## Final full gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/channelScript/CHANSVm] pool: IDENTICAL
[src/channelScript/CHANSVm] objdiff: code 31960/53564 data 800/6904 functions 205/233 fuzzy 98.3091 linked code 0
[src/channelScript/CHANSVm] instruction-exact functions: 204/233
[src/channelScript/CHANSVm]   section .data size 4672 match 18.050066
[src/channelScript/CHANSVm]   section .rodata size 1432 match 97.2067
[src/channelScript/CHANSVm]   section .sbss size 16 match 100.0
[src/channelScript/CHANSVm]   section .sdata size 600 match 100.0
[src/channelScript/CHANSVm]   section .sdata2 size 184 match 100.0
[src/channelScript/CHANSVm]   section .text size 53564 match 98.30909
[src/channelScript/CHANSVm]   below 100: CHANSVmGetSourceLine 97.71739
[src/channelScript/CHANSVm]   below 100: CHANSVmNewObjData 99.375
[src/channelScript/CHANSVm]   below 100: CHANSVmStrCpyToU16FromU8 98.46154
[src/channelScript/CHANSVm]   below 100: CHANSVmParseInt 94.69388
[src/channelScript/CHANSVm]   below 100: CHANSVm_8144B4D4 96.92771
[src/channelScript/CHANSVm]   below 100: VmArraySlice 96.2782
[src/channelScript/CHANSVm]   below 100: VmDateDtor 94.96703
[src/channelScript/CHANSVm]   below 100: VmStringFromCharCode 99.40678
[src/channelScript/CHANSVm]   below 100: VmStringReplace 97.106064
[src/channelScript/CHANSVm]   below 100: VmStringSplit 96.04955
[src/channelScript/CHANSVm]   below 100: CHANSVm_8145049C 98.58237
[src/channelScript/CHANSVm]   below 100: CHANSVm_81450D14 97.391304
[src/channelScript/CHANSVm]   below 100: VmBlobCopyRangeFrom 91.67647
[src/channelScript/CHANSVm]   below 100: VmBlobGetHexString 98.71951
[src/channelScript/CHANSVm]   below 100: VmBlobCalcRangeSHA1Digest 96.484535
[src/channelScript/CHANSVm]   below 100: VmBlobCalcRangeMD5Digest 99.793816
[src/channelScript/CHANSVm]   below 100: VmBlobCalcHMAC 99.453125
[src/channelScript/CHANSVm]   below 100: VmBlobCalcRangeHMAC 99.72269
[src/channelScript/CHANSVm]   below 100: vmBlobParsePackFormatString 99.69827
[src/channelScript/CHANSVm]   below 100: VmBlobPackCommon 92.603294
[src/channelScript/CHANSVm]   below 100: VmBlobUnpack 92.083176
[src/channelScript/CHANSVm]   below 100: VmImageCtor 99.0
[src/channelScript/CHANSVm]   below 100: VmWinEmuWrite 99.62687
[src/channelScript/CHANSVm]   below 100: CHANSVmAddExe 99.1063
[src/channelScript/CHANSVm]   below 100: CHANSVm_81455654 94.0
[src/channelScript/CHANSVm]   below 100: CHANSVmLinkModules 98.677246
[src/channelScript/CHANSVm]   below 100: VmCallMethod 96.565834
[src/channelScript/CHANSVm]   below 100: CHANSVmStep 94.7901
[src/channelScript/CHANSVm] baseline: code 30984/53564 data 16 functions 202 fuzzy 98.2665
regressions vs baseline: 0
global matched_code_percent: 72.11085 -> 72.14343
global fuzzy_match_percent: 80.97820 -> 80.97897
global complete_code_percent: 56.76068 -> 56.76068
global matched_data_percent: 86.15517 -> 86.19795
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## Before and after

Instruction-exact functions: 201/233 -> 204/233. Objdiff-matched functions: 202/233 -> 205/233. Code bytes: 30984/53564 -> 31960/53564. Data bytes: 16/6904 -> 800/6904.

VmArrayExpandCommon: 85/85 instructions, diffs 0. VmDateGetRTC: 38/38 instructions, diffs 0. VmStringSplice: 121/121 instructions, diffs 0. The clock and slice fixes were reverified and reapplied because they were absent from the live checkout.

CHANSVmStrCpyToU16FromU8 improves from 97.30769% to 98.46154%; it remains non-matching, with three register differences.

## Data work

- UTF-16 NaN and comma literals use ordinary escaped string literals with the original single-byte terminator.
- The empty string data is a real object header with an empty-string pointer, matching the original relocation at .rodata+0x50.
- The fifth constant object has a null pointer, matching the absence of a target relocation at .rodata+0xa0.
- The final floating constant keyword is NaN, rather than a duplicate Infinity. Its source position precedes the floating-point format string.
- Error success and unknown messages are arrays, matching the original data symbols, rather than pointers.
- Shared report and integer format arrays eliminate duplicate pooled literals in the document writer and interpreter.
- .sdata, .sdata2 and .sbss score 100% in objdiff. .rodata improves from 85.50279% to 97.2067%. .data improves from 17.614084% to 18.050066%.

Raw bytes, before applying relocations, are identical for .data, .rodata and .sdata2. The .sdata source bytes match the target prefix; objdiff accepts the target trailing zero alignment and scores it 100%. Raw-byte identity does not establish relocation-exact data. No new labels, forced sections, dummy objects or measurement mappings were introduced.

## Remaining functions

CHANSVmGetSourceLine, 97.71739%, register allocation and line-data address operands.
CHANSVmNewObjData, 99.375%, register allocation and allocation-failure branch destination.
CHANSVmStrCpyToU16FromU8, 98.46154%, three register differences after the decrement-first rewrite.
CHANSVmParseInt, 94.69388%, three instruction scheduling differences.
CHANSVm_8144B4D4, 96.92771%, register allocation and parse-end initialization scheduling.
VmArraySlice, 96.2782%, signed index clipping, branch layout and register allocation.
VmDateDtor, 94.96703%, seven argument-load scheduling differences.
VmStringFromCharCode, 99.40678%, six register differences.
VmStringReplace, 97.106064%, string field-load scheduling and register allocation.
VmStringSplit, 96.04955%, register allocation, scheduling and branch operands.
CHANSVm_8145049C, 98.58237%, character and string formatting paths, scheduling and register allocation.
CHANSVm_81450D14, 97.391304%, one missing instruction and branch layout.
VmBlobFill, 100.0%, two raw conditional branch operands differ despite objdiff 100%.
VmBlobCopyRangeFrom, 91.67647%, range-check control flow, 139/136 instructions.
VmBlobGetHexString, 98.71951%, fourteen register differences.
VmBlobCalcRangeSHA1Digest, 96.484535%, range-check scheduling and register allocation.
VmBlobCalcRangeMD5Digest, 99.793816%, four register differences.
VmBlobCalcHMAC, 99.453125%, seven register differences.
VmBlobCalcRangeHMAC, 99.72269%, register allocation and hash context stack offset.
vmBlobParsePackFormatString, 99.69827%, decimal accumulator register allocation.
VmBlobPackCommon, 92.603294%, stack layout and control flow, 675/668 instructions.
VmBlobUnpack, 92.083176%, control flow and register allocation, 531/517 instructions.
VmImageCtor, 99.0%, four register differences.
VmWinEmuWrite, 99.62687%, five register differences.
CHANSVmAddExe, 99.1063%, register allocation, relocation loop scheduling and addition operands.
CHANSVm_81455654, 94.0%, missing initial null-result instruction, 34/35 instructions.
CHANSVmLinkModules, 98.677246%, register allocation and dispatch traversal scheduling.
VmCallMethod, 96.565834%, control flow and register allocation, 279/281 instructions.
CHANSVmStep, 94.7901%, stack layout and interpreter paths, 1249/1253 instructions.

## Attempts

Each compiling attempt rebuilt only CHANSVm.o, regenerated objdiff and compared raw instructions against the original. Every remaining function has at least three distinct compiling source-level attempts. Failed compiler experiments are recorded separately. Changes with regressions were restored. Exact variants retained during iteration were cleaned up before the final gate; the source diff is the authority for retained changes.

### VmBlobCalcRangeMD5Digest

- name the range validation boolean: 99.793816%; instructions 97/97, differing positions 4; restored.
- test digest buffer before allocated object: 99.639175%; instructions 97/97, differing positions 7; restored.
- load range pointer directly into update argument: 90.515465%; instructions 96/97, differing positions 26; restored.

### VmBlobCalcRangeHMAC

- declare hash context before pointer locals: 99.890755%; instructions 119/119, differing positions 5; restored.
- check digest pointer before output object: 99.68067%; instructions 119/119, differing positions 10; restored.
- write data argument directly in hash update: 85.411766%; instructions 118/119, differing positions 32; restored.

### vmBlobParsePackFormatString

- scope a signed numeric character beside accumulator: 98.01724%; instructions 117/116, differing positions 41; restored.
- subtract ascii zero before adding decimal product: 99.69827%; instructions 116/116, differing positions 6; restored.
- parameter loop with explicit position increment: 99.69827%; instructions 116/116, differing positions 6; restored.

### VmWinEmuWrite

- read string length before resetting offset: 99.62687%; instructions 67/67, differing positions 5; restored.
- separate conversion input data pointer: 99.62687%; instructions 67/67, differing positions 5; restored.
- two byte string terminators with memset: 89.31343%; instructions 68/67, differing positions 57; restored.

### VmBlobCalcHMAC

- check output buffer before header: 99.453125%; instructions 64/64, differing positions 7; restored.
- explicit boolean native key test: 99.453125%; instructions 64/64, differing positions 7; restored.
- load data before size at hash setup: 99.265625%; instructions 64/64, differing positions 11; restored.

### VmStringFromCharCode

- cache upper bound for code points: 99.40678%; instructions 59/59, differing positions 6; restored.
- code point masking after low word load: 94.32204%; instructions 57/59, differing positions 45; restored.
- assign byte offset before index counter: 99.32204%; instructions 59/59, differing positions 7; restored.

### CHANSVmNewObjData

- cache chunk slot as typed pointer: 99.375%; instructions 96/96, differing positions 11; restored.
- invert allocation success branch within scan: 99.375%; instructions 96/96, differing positions 11; restored.
- advance free entry pointer during entry scan: did not compile due to C89 declaration placement; restored and followed by a compiling variant.
- pointer scan with declaration in function scope: 97.552086%; instructions 95/96, differing positions 65; restored.

### VmArrayExpandCommon

- derive element offset from index: 100.0%; instructions 85/85, differing positions 0; retained during iteration.
- iterate element headers with typed pointer: 100.0%; instructions 85/85, differing positions 0; retained during iteration.
- narrow allocation size lifetime to allocation block: 100.0%; instructions 85/85, differing positions 0; retained during iteration.
- use array chunk element field for destinations: 100.0%; instructions 85/85, differing positions 0; retained during iteration.

### CHANSVmAddExe

- reverse initial typed module and context declarations: 99.1063%; instructions 254/254, differing positions 35; restored.
- use module element fields instead of byte offset: 99.15354%; instructions 254/254, differing positions 34; restored.
- test typed execution id using temporary: 99.1063%; instructions 254/254, differing positions 35; restored.

### VmImageCtor

- name data pointer inside callback branch: 99.0%; instructions 25/25, differing positions 4; restored.
- store return object pointer in image lookup temporary: 99.0%; instructions 25/25, differing positions 4; restored.
- use pointer truth test and retain size test: 99.0%; instructions 25/25, differing positions 4; restored.

### VmBlobGetHexString

- separate high and low nibble values: 98.71951%; instructions 82/82, differing positions 14; restored.
- reverse nibble lookup operand order: 98.71951%; instructions 82/82, differing positions 14; restored.
- signed destination byte count: 98.71951%; instructions 82/82, differing positions 14; restored.

### CHANSVm_8145049C

- use typed temporary string header: 98.58237%; instructions 431/431, differing positions 42; restored.
- use typed character string buffer and retained buffer size: 98.58237%; instructions 431/431, differing positions 42; restored.
- scope string output data before source data: 98.58237%; instructions 431/431, differing positions 42; restored.

### CHANSVmLinkModules

- load module count into loop bound: 95.544975%; instructions 189/189, differing positions 123; restored.
- increment module index before loading next module: 98.677246%; instructions 189/189, differing positions 43; restored.
- copy dispatch entry fields separately: did not compile due to C89 declaration placement; restored and followed by a compiling variant.
- copy dispatch fields after local declarations: 92.53439%; instructions 197/189, differing positions 186; restored.

### CHANSVmGetSourceLine

- source offset relative to cached table start: 97.82609%; instructions 46/46, differing positions 16; restored.
- byte-sized program offset loop bound: 98.04348%; instructions 46/46, differing positions 15; restored.
- bit test with indexed table field: 89.021736%; instructions 45/46, differing positions 39; restored.

### VmStringSplice

- use conditional for clipped byte length: 100.0%; instructions 121/121, differing positions 0; retained during iteration.
- calculate length only in positive range: 97.06612%; instructions 120/121, differing positions 29; restored.
- name starting argument signed byte offset: 100.0%; instructions 121/121, differing positions 0; retained during iteration.

### CHANSVm_81450D14

- positive range early successful fallthrough: 89.565216%; instructions 50/46, differing positions 33; restored.
- test negative value before negative size bound: 70.978264%; instructions 45/46, differing positions 29; restored.
- cache unsigned blob size in signed scalar: 79.565216%; instructions 44/46, differing positions 40; restored.

### CHANSVmStrCpyToU16FromU8

- decrement count before byte offset calculation: 98.46154%; instructions 13/13, differing positions 3; restored.
- input indexed by reverse character counter: 69.61539%; instructions 14/13, differing positions 14; restored.
- byte output pointer scoped beside reverse input: 97.30769%; instructions 13/13, differing positions 5; restored.
- inspect decrement-first offset variant: 98.46154%; instructions 13/13, differing positions 3; retained during iteration.
- distinct remaining character counter: 98.46154%; instructions 13/13, differing positions 3; restored.
- hold narrowed byte value as signed char: 98.46154%; instructions 13/13, differing positions 4; restored.
- use byte load directly in low-byte store: 98.46154%; instructions 13/13, differing positions 4; restored.

### VmStringReplace

- cache all three string value structures in load order: 97.82576%; instructions 132/132, differing positions 47; restored.
- convert replacement after search is validated: 94.11364%; instructions 132/132, differing positions 59; restored.
- reverse initial argument declaration order: 97.106064%; instructions 132/132, differing positions 53; restored.

### CHANSVm_8144B4D4

- use ordinary typed parse end pointer: 96.92771%; instructions 83/83, differing positions 13; restored.
- read string length before allocating converted object: 82.349396%; instructions 89/83, differing positions 84; restored.
- local typed result pointer before floating store: did not compile due to C89 declaration placement; restored and followed by a compiling variant.
- scoped typed result pointer after store label: 96.92771%; instructions 83/83, differing positions 13; restored.

### VmBlobCalcRangeSHA1Digest

- load range offset for both bounds and hash pointer: 98.09278%; instructions 96/97, differing positions 35; restored.
- test output buffer before digest object: 96.329895%; instructions 97/97, differing positions 17; restored.
- assign range validity to a named boolean: 96.484535%; instructions 97/97, differing positions 14; restored.

### VmArraySlice

- mutate signed indices before clipping to array length: 95.07519%; instructions 134/133, differing positions 100; restored.
- assign end length before start range checks: 94.172935%; instructions 132/133, differing positions 93; restored.
- array element source acquired before destination: 88.68421%; instructions 133/133, differing positions 60; restored.

### VmStringSplit

- cache string structures before loading lengths: 95.64414%; instructions 222/222, differing positions 101; restored.
- derive empty-delimiter byte offset from character index: 96.04955%; instructions 222/222, differing positions 81; restored.
- validate array before getting first created element: 92.58108%; instructions 223/222, differing positions 131; restored.

### VmDateDtor

- load both calendar name tables into pointers: 91.79121%; instructions 91/91, differing positions 63; restored.
- read month before day and pass names as locals: 94.96703%; instructions 91/91, differing positions 7; restored.
- use calendar object directly instead of calendar pointer: 89.14286%; instructions 90/91, differing positions 85; restored.

### CHANSVmParseInt

- group end pointer and input buffer into parse context: 94.69388%; instructions 49/49, differing positions 3; restored.
- cache string value before type test: 94.69388%; instructions 49/49, differing positions 3; restored.
- initialize parsing end pointer after string length load: 81.42857%; instructions 50/49, differing positions 41; restored.

### VmDateGetRTC

- apply unsigned 64-bit mask after bias subtraction: 100.0%; instructions 38/38, differing positions 0; retained during iteration.
- name rtc seconds after division: 100.0%; instructions 38/38, differing positions 0; retained during iteration.
- unsigned bias widened before subtraction: 100.0%; instructions 38/38, differing positions 0; retained during iteration.
- remove experimental block around seconds calculation: 100.0%; instructions 38/38, differing positions 0; retained during iteration.

### CHANSVm_81455654

- assign result instead of returning through negative-index branch: 88.28571%; instructions 33/35, differing positions 18; restored.
- separate argument table from return pointer: 94.0%; instructions 34/35, differing positions 35; restored.
- initialize result after active context retrieval: 94.0%; instructions 34/35, differing positions 35; restored.

### VmCallMethod

- cache active module during operand range validation: 96.565834%; instructions 279/281, differing positions 228; restored.
- cache native property method state as bool: 96.6726%; instructions 279/281, differing positions 228; restored.
- separate argument count operand pointer: 96.565834%; instructions 279/281, differing positions 228; restored.

### CHANSVmStep

- named execution context for initial range validation: 94.56664%; instructions 1249/1253, differing positions 1172; restored.
- signed opcode instead of unsigned dispatch scalar: 94.52673%; instructions 1249/1253, differing positions 1173; restored.
- load float operand into double object directly: 94.7901%; instructions 1249/1253, differing positions 1173; restored.

### VmBlobPackCommon

- typed signed parser parameter address: 92.603294%; instructions 675/668, differing positions 642; restored.
- derive format length with shift: 92.603294%; instructions 675/668, differing positions 642; restored.
- validate parent only for pack operation: 92.61078%; instructions 675/668, differing positions 641; restored.

### VmBlobUnpack

- array buffer declared before scalar pointers: 92.083176%; instructions 531/517, differing positions 496; restored.
- named constant parser defaults: 92.083176%; instructions 531/517, differing positions 496; restored.
- signed count for unpacked elements: 92.083176%; instructions 531/517, differing positions 496; restored.

### VmBlobCopyRangeFrom

- target bounds checks with named availability: 91.52941%; instructions 139/136, differing positions 71; restored.
- use existing range predicate for both blobs: 93.80882%; instructions 138/136, differing positions 50; restored.
- load source and destination offsets after count conversion: 94.08088%; instructions 137/136, differing positions 73; restored.

### VmBlobFill

- name converted byte value before memset: 100.0%; instructions 63/63, differing positions 2; restored.
- scope fill byte and destination pointer together: 100.0%; instructions 63/63, differing positions 2; restored.
- advance offset before memory fill with original offset cached: 87.01588%; instructions 63/63, differing positions 12; restored. Regressions: VmBlobFill.

## Uncertainty

The reason for VmBlobFill raw branch differences remains unresolved. Register-only mismatches may be compiler tie-breaks; the attempts do not prove that no readable C variation can match them. Remaining .data/.rodata relocation and symbol comparisons are unresolved, so the unit is not complete.
