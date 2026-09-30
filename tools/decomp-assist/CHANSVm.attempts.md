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

## 2026-09-30 switch mapping and range-copy match

Baseline: 206/233 instruction-exact, 207/233 objdiff-exact; code 32400/53564; data 2232/6904; .data 18.050066%.
Accepted: VmBlobCopyRangeFrom, 100.0% objdiff, 136/136 instructions, ctxdiff diffs 0. Boolean range assignments replace conditional flag stores.
Final: 207/233 instruction-exact, 208/233 objdiff-exact; code 32944/53564; data 2232/6904; .data 18.050066%.

### Switch mapping

All 64 main opcode entries and their shared labels already have the target source-body order. Reordering those bodies would break the current order.
The three CHANSVmStep tables contain 121 relocations. The type table at .data+0x105c has 0/10 incorrect offsets; the operator table at 0x1084 has 47/47; the opcode table at 0x1140 has 51/64. Total: 98 incorrect offsets.
The main table offsets differ by 8 or 16 bytes through most of the interpreter. Its source and target function sizes are both 0x1394. Source/target .data payloads are byte-identical before relocation.
Stack/local, table-base hoisting, shared-tail and register allocation differences explain the shifted labels. No case reorder was retained.

opcode | source label | target offset | emitted offset
--- | --- | --- | ---
0x18 | CHANS_VM_OP_LOAD_IMM_1 | 0x013c | 0x0144
0x27 | CHANS_VM_OP_LOAD_IMM_2 | 0x0144 | 0x014c
0x28 | CHANS_VM_OP_LOAD_IMM_4 | 0x014c | 0x0154
0x29 | CHANS_VM_OP_LOAD_IMM_8 | 0x0154 | 0x015c
0x2a | CHANS_VM_OP_LOAD_FLOAT | 0x0188 | 0x0190
0x19 | CHANS_VM_OP_ADD_IMM | 0x01c4 | 0x01cc
0x1a | CHANS_VM_OP_SUB_IMM | 0x01d4 | 0x01dc
0x1b | CHANS_VM_OP_MUL_IMM | 0x01e4 | 0x01ec
0x1c | CHANS_VM_OP_DIV_IMM | 0x01f4 | 0x01fc
0x1d | CHANS_VM_OP_MOD_IMM | 0x0204 | 0x020c
0x1e | CHANS_VM_OP_AND_IMM | 0x0214 | 0x021c
0x1f | CHANS_VM_OP_OR_IMM | 0x0224 | 0x022c
0x20 | CHANS_VM_OP_XOR_IMM | 0x0234 | 0x023c
0x21 | CHANS_VM_OP_CMP_EQ_IMM | 0x0244 | 0x024c
0x22 | CHANS_VM_OP_CMP_NEQ_IMM | 0x0254 | 0x025c
0x23 | CHANS_VM_OP_CMP_LT_IMM | 0x0264 | 0x026c
0x24 | CHANS_VM_OP_CMP_GT_IMM | 0x0274 | 0x027c
0x25 | CHANS_VM_OP_CMP_LEQ_IMM | 0x0284 | 0x028c
0x26 | CHANS_VM_OP_CMP_GEQ_IMM | 0x0294 | 0x029c
0x04 | CHANS_VM_OP_PUSH | 0x0500 | 0x0510
0x05 | CHANS_VM_OP_POP | 0x056c | 0x057c
0x06 | CHANS_VM_OP_ADD | 0x0580 | 0x0590
0x07 | CHANS_VM_OP_SUB | 0x0590 | 0x05a0
0x08 | CHANS_VM_OP_MUL | 0x05a0 | 0x05b0
0x09 | CHANS_VM_OP_DIV | 0x05b0 | 0x05c0
0x0a | CHANS_VM_OP_MOD | 0x05c0 | 0x05d0
0x0b | CHANS_VM_OP_BIT_AND | 0x05d0 | 0x05e0
0x0c | CHANS_VM_OP_BIT_OR | 0x05e0 | 0x05f0
0x0d | CHANS_VM_OP_BIT_XOR | 0x05f0 | 0x0600
0x0e | CHANS_VM_OP_ULSHIFT | 0x0600 | 0x0610
0x0f | CHANS_VM_OP_ARSHIFT | 0x0610 | 0x0620
0x10 | CHANS_VM_OP_CMP_EQ | 0x0620 | 0x0630
0x11 | CHANS_VM_OP_CMP_NEQ | 0x0630 | 0x0640
0x12 | CHANS_VM_OP_CMP_LT | 0x0640 | 0x0650
0x13 | CHANS_VM_OP_CMP_GT | 0x0650 | 0x0660
0x14 | CHANS_VM_OP_CMP_LEQ | 0x0660 | 0x0670
0x15 | CHANS_VM_OP_CMP_GEQ | 0x0670 | 0x0680
0x00 | CHANS_VM_OP_RETURN | 0x06a0 | 0x06b0
0x01 | CHANS_VM_OP_RETURN_VALUE | 0x06d0 | 0x06e0
0x16 | CHANS_VM_OP_BIT_NOT | 0x06e8 | 0x06f8
0x17 | CHANS_VM_OP_LOG_NOT | 0x07a8 | 0x07b8
0x3e | CHANS_VM_OP_LOAD_INDIRECT | 0x07e4 | 0x07f4
0x30 | CHANS_VM_OP_CALL_METHOD | 0x0854 | 0x0864
0x02 | CHANS_VM_OP_IS_CLASS | 0x0894 | 0x08a4
0x31 | CHANS_VM_OP_CALL_FUNCTION | 0x08b0 | 0x08c0
0x32 | CHANS_VM_OP_PROP_GET | 0x08f4 | 0x0904
0x33 | CHANS_VM_OP_PROP_SET | 0x08f4 | 0x0904
0x3f | CHANS_VM_OP_STORE_INDIRECT | 0x0940 | 0x0950
0x2c | CHANS_VM_OP_LOAD_STRING_CONST | 0x09c8 | 0x09d8
0x2d | CHANS_VM_OP_SET_INDEX | 0x0a6c | 0x0a7c
0x34 | CHANS_VM_OP_GET_PROPERTY_NAME | 0x0b8c | 0x0b94
0x03 | CHANS_VM_OP_NEW_ARRAY | 0x0da4 | 0x0da4
0x35 | CHANS_VM_OP_JUMP | 0x0e74 | 0x0e74
0x2b | CHANS_VM_OP_STORE_UNDEFINED | 0x0f14 | 0x0f14
0x36 | CHANS_VM_OP_DELETE_SYMBOL | 0x0f2c | 0x0f2c
0x37 | CHANS_VM_OP_DELETE_INDIRECT | 0x0f80 | 0x0f80

### Remaining functions

CHANSVmGetSourceLine: 97.82609% | 16 register-allocation differences
CHANSVmNewObjData: 99.427086% | 10 register-allocation differences
CHANSVmParseInt: 94.69388% | endpoint initialization scheduling; 3 differences
CHANSVm_8144B4D4: 96.92771% | endpoint store scheduling and register allocation; 13 differences
VmArraySlice: 96.2782% | index clamping scheduling and registers; 56 differences
VmDateDtor: 94.96703% | calendar argument and table-load scheduling; 7 differences
VmStringFromCharCode: 99.40678% | output offset and mask register allocation; 6 differences
VmStringReplace: 97.106064% | 53 register-allocation differences
VmStringSplit: 96.04955% | 81 register-allocation differences
CHANSVm_8145049C: 98.58237% | character/shared-tail scheduling and registers; 42 differences
CHANSVm_81450D14: 97.391304% | 45/46 instructions; branch layout and add operand order
VmBlobGetHexString: 98.71951% | hex output counter/register allocation; 14 differences
VmBlobCalcRangeSHA1Digest: 96.484535% | range check scheduling and register allocation; 14 differences
VmBlobCalcHMAC: 99.453125% | 7 register-allocation differences
VmBlobCalcRangeHMAC: 99.97479% | context stack offset 0xc versus target 0x10; 3 differences
vmBlobParsePackFormatString: 99.69827% | decimal accumulator and character registers; 6 differences
VmBlobPackCommon: 92.603294% | 675/668 instructions; parser locals, switches, pack conversions
VmBlobUnpack: 92.083176% | 531/517 instructions; parser locals, switches, numeric conversions
VmImageCtor: 99.0% | image/pixel pointer register allocation; 4 differences
VmWinEmuWrite: 99.62687% | string and total-length register allocation; 5 differences
CHANSVmAddExe: 99.1063% | loop scheduling, address addition order, registers; 35 differences
CHANSVm_81455654: 94.0% | 34/35 instructions; return-pointer and branch layout
CHANSVmLinkModules: 98.677246% | 43 register-allocation differences
VmCallMethod: 97.2242% | call state and argument register allocation; 97 differences
CHANSVmStep: 95.172386% | 1253/1253 instructions; 894 differences, stack/register/base-address scheduling

VmBlobFill has objdiff 100.0% but two raw conditional-branch operands differ. It was unchanged; this accounts for the one-function discrepancy between the objdiff and instruction-exact gates. The instruction counter is stricter than objdiff for this function; relocation-aware linking was not investigated in this matching-only phase.

### Attempts

All unsuccessful candidates were restored. Each remaining objdiff-inexact function has at least three compiled, distinct source-level trials. VmBlobCopyRangeFrom reached exact on its first trial; a later output-offset-order trial regressed and was restored.
Compile-error probes were corrected and rerun or discarded; they are excluded from the attempt counts below.

CHANSVmStep: 1: two enum types and a two-object indirect/index scratch array; objdiff 95.18675; insns 1253/1253, diffs 876; .data 18.050066
CHANSVmStep: 2: reorder live temporaries; use copied index; propagate boolean error; order float bounds like target; objdiff 94.71907; insns 1249/1253, diffs 1230; .data 18.050066
CHANSVmStep: 3: typed two-entry enum array with direct indexing instead of byte-stride temporary; objdiff 94.847565; insns 1253/1253, diffs 899; .data 18.050066
VmBlobCalcRangeHMAC: 1: declare digest object before HMAC context; objdiff 99.97479; insns 119/119, diffs 3; .data 18.050066
VmBlobCalcRangeHMAC: 2: promote HMAC context to function scope; objdiff 99.97479; insns 119/119, diffs 3; .data 18.050066
VmBlobCalcRangeHMAC: 3: place context first among function locals; objdiff 99.97479; insns 119/119, diffs 3; .data 18.050066
vmBlobParsePackFormatString: 1: promote current format character to u32; objdiff 99.69827; insns 116/116, diffs 6; .data 18.050066
VmWinEmuWrite: 1: compute string length before offset initialization; objdiff 99.62687; insns 67/67, diffs 5; .data 18.050066
VmWinEmuWrite: 2: early return for nonstring argument; objdiff 94.62687; insns 69/67, diffs 54; .data 18.050066
VmWinEmuWrite: 3: declare total length before argument object; objdiff 99.17911; insns 67/67, diffs 8; .data 18.050066
CHANSVmNewObjData: 1: initialize entry search offset before chunk index; objdiff 99.427086; insns 96/96, diffs 10; .data 18.050066
CHANSVmNewObjData: 2: declare chunk pointer before loop index; objdiff 99.427086; insns 96/96, diffs 10; .data 18.050066
CHANSVmNewObjData: 3: count chunk search with for loop; objdiff 99.427086; insns 96/96, diffs 10; .data 18.050066
VmStringFromCharCode: 1: initialize output offset before argument index; objdiff 99.32204; insns 59/59, diffs 7; .data 18.050066
VmStringFromCharCode: 2: express character truncation as u16 conversion; objdiff 94.32204; insns 57/59, diffs 45; .data 18.050066
VmStringFromCharCode: 3: use a for loop for the argument traversal; objdiff 99.32204; insns 59/59, diffs 7; .data 18.050066
vmBlobParsePackFormatString: 2: put current character first in decimal accumulation; objdiff 99.69827; insns 116/116, diffs 6; .data 18.050066
vmBlobParsePackFormatString: 3: split decimal multiplication and digit addition; objdiff 99.655174; insns 116/116, diffs 6; .data 18.050066
VmBlobCalcHMAC: 1: declare key blob before parent blob; objdiff 99.453125; insns 64/64, diffs 7; .data 18.050066
VmBlobCalcHMAC: 2: hold argument only while resolving the key blob; objdiff 99.4375; insns 64/64, diffs 12; .data 18.050066
VmBlobCalcHMAC: 3: assign parent and key argument after declaring all locals; objdiff 99.453125; insns 64/64, diffs 7; .data 18.050066
VmImageCtor: 1: name pixel buffer before validating it; objdiff 86.6; insns 25/25, diffs 8; .data 18.050066
VmImageCtor: 2: express nested image checks with early return; objdiff 47.8; insns 17/25, diffs 25; .data 18.050066
VmImageCtor: 3: name image size as a separate scalar; objdiff 86.36; insns 25/25, diffs 10; .data 18.050066
CHANSVmAddExe: 1: initialize module during declaration; objdiff 99.1063; insns 254/254, diffs 35; .data 18.050066
CHANSVmAddExe: 2: increment table index before table byte offset; objdiff 99.15354; insns 254/254, diffs 34; .data 18.050066
CHANSVmAddExe: 3: initialize module before VM local; commute relocation additions; objdiff 99.185036; insns 254/254, diffs 33; .data 18.050066
VmDateDtor: 1: resolve month name before day name; objdiff 94.96703; insns 91/91, diffs 7; .data 18.050066
VmDateDtor: 2: resolve day name before month name; objdiff 94.96703; insns 91/91, diffs 7; .data 18.050066
VmDateDtor: 3: use direct date member access for formatted fields; objdiff 89.14286; insns 90/91, diffs 85; .data 18.050066
CHANSVmParseInt: 1: initialize parse endpoint before loading type; objdiff 83.67347; insns 49/49, diffs 5; .data 18.050066
CHANSVmParseInt: 2: declare initialized endpoint before output buffer; objdiff 94.69388; insns 49/49, diffs 3; .data 18.050066
CHANSVmParseInt: 3: load object type after initializing endpoint; objdiff 83.67347; insns 49/49, diffs 5; .data 18.050066
CHANSVm_81455654: 1: preserve result pointer through a single function return; objdiff 88.28571; insns 33/35, diffs 18; .data 18.050066
CHANSVm_81455654: 2: assign global reference through object field before shared return; objdiff 88.28571; insns 33/35, diffs 18; .data 18.050066
CHANSVm_81455654: 3: compute argument array separately before shared return; objdiff 88.28571; insns 33/35, diffs 18; .data 18.050066
CHANSVm_81450D14: 1: invert range validity branch; objdiff 97.391304; insns 45/46, diffs 29; .data 18.050066
CHANSVm_81450D14: 2: add blob size before negative relative index; objdiff 97.391304; insns 45/46, diffs 29; .data 18.050066
CHANSVm_81450D14: 3: return through explicit success result; objdiff 81.63043; insns 42/46, diffs 45; .data 18.050066
VmBlobGetHexString: 1: initialize emitted-digit index before output offset; objdiff 98.71951; insns 82/82, diffs 14; .data 18.050066
VmBlobGetHexString: 2: initialize traversal loop before output indices; objdiff 98.71951; insns 82/82, diffs 14; .data 18.050066
VmBlobGetHexString: 3: update output index before emitted-digit index; objdiff 98.71951; insns 82/82, diffs 14; .data 18.050066
VmBlobCalcRangeSHA1Digest: 1: cache range offset before checking two bounds; objdiff 99.793816; insns 97/97, diffs 4; .data 18.050066
VmBlobCalcRangeSHA1Digest: 2: separate signed range-validity calculation; objdiff 96.484535; insns 97/97, diffs 14; .data 18.050066
VmBlobCalcRangeSHA1Digest: 3: reuse cached offset for data address; objdiff 98.50516; insns 96/97, diffs 28; .data 18.050066
CHANSVm_8145049C: 1: assign character-format length before character pointer; objdiff 98.58237; insns 431/431, diffs 42; .data 18.050066
CHANSVm_8145049C: 2: hold copied string data before memcpy; objdiff 98.689095; insns 430/431, diffs 171; .data 18.050066
CHANSVm_8145049C: 3: terminate the character string before setting shared-format locals; objdiff 94.967514; insns 432/431, diffs 358; .data 18.050066
CHANSVmGetSourceLine: 1: cache program counter byte for the line-bit scan; objdiff 98.36957; insns 46/46, diffs 14; .data 18.050066
CHANSVmGetSourceLine: 2: read baseline offset after deriving bitfield; objdiff 97.82609; insns 46/46, diffs 16; .data 18.050066
CHANSVmGetSourceLine: 3: cache debug module once for validation and table access; objdiff 97.82609; insns 46/46, diffs 16; .data 18.050066
CHANSVmLinkModules: 1: initialize module iterator before blocking allocation; objdiff 98.677246; insns 189/189, diffs 43; .data 18.050066
CHANSVmLinkModules: 2: use a for loop for module traversal; objdiff 98.677246; insns 189/189, diffs 43; .data 18.050066
CHANSVmLinkModules: 3: copy dispatch entry fields into separate locals; objdiff 94.33862; insns 189/189, diffs 59; .data 18.050066
VmStringReplace: 1: load all string lengths before their data pointers; objdiff 97.106064; insns 132/132, diffs 53; .data 18.050066
VmStringReplace: 2: initialize output byte count before output data pointer; objdiff 97.030304; insns 132/132, diffs 55; .data 18.050066
VmStringReplace: 3: limit each converted argument to the validation/data setup scope; objdiff 97.106064; insns 132/132, diffs 53; .data 18.050066
VmStringSplit: 1: load delimiter length before its data pointer; objdiff 96.04955; insns 222/222, diffs 81; .data 18.050066
VmStringSplit: 2: initialize split limit before fetching delimiter; objdiff 95.14414; insns 222/222, diffs 93; .data 18.050066
VmStringSplit: 3: scope the limit argument to the optional limit block; objdiff 96.04955; insns 222/222, diffs 81; .data 18.050066
VmCallMethod: 1: initialize call state in declaration order; objdiff 97.2242; insns 281/281, diffs 97; .data 18.050066
VmCallMethod: 2: initialize accumulator during declaration; objdiff 97.2242; insns 281/281, diffs 97; .data 18.050066
VmCallMethod: 3: split end-depth and header-count declarations; objdiff 97.2242; insns 281/281, diffs 97; .data 18.050066
CHANSVm_8144B4D4: 1: use a typed endpoint instead of a volatile integer; objdiff 96.92771; insns 83/83, diffs 13; .data 18.050066
CHANSVm_8144B4D4: 2: remove endpoint volatility and initialize before type load; objdiff 94.518074; insns 83/83, diffs 13; .data 18.050066
CHANSVm_8144B4D4: 3: keep keyword/number endpoint as a scoped pointer; objdiff 94.518074; insns 83/83, diffs 13; .data 18.050066
VmArraySlice: 1: represent array length as signed 64-bit for index clamping; objdiff 84.50376; insns 138/133, diffs 107; .data 18.050066
VmArraySlice: 2: compute each negative index once as a signed value; objdiff 96.2782; insns 133/133, diffs 56; .data 18.050066
VmArraySlice: 3: add array length before negative argument index; objdiff 95.97744; insns 133/133, diffs 56; .data 18.050066
VmBlobCopyRangeFrom: 1: assign both range-validity flags from the bounds expression; objdiff 100.0; insns 136/136, diffs 0; .data 18.050066
VmBlobCopyRangeFrom: 3: initialize destination offset before source offset; objdiff 99.98529; insns 136/136, diffs 2; .data 18.050066
VmBlobPackCommon: 1: combine create-mode and parent validity check; objdiff 92.603294; insns 675/668, diffs 642; .data 18.050066
VmBlobPackCommon: 2: give sizing and output passes separate parsed format locals; objdiff 92.597305; insns 675/668, diffs 637; .data 18.050066
VmBlobPackCommon: 3: use signed opcode comparisons in both format passes; objdiff 92.603294; insns 675/668, diffs 642; .data 18.050066
VmBlobUnpack: 1: reject invalid format before the sizing switch; objdiff 92.067696; insns 530/517, diffs 497; .data 18.050066
VmBlobUnpack: 2: use signed format type comparisons in sizing pass; objdiff 92.083176; insns 531/517, diffs 496; .data 18.050066
VmBlobUnpack: 3: remove redundant initializations overwritten before parsing; objdiff 92.083176; insns 531/517, diffs 496; .data 18.050066
VmImageCtor: 4: bind pixel buffer within callback branch; objdiff 99.0; insns 25/25, diffs 4; .data 18.050066
CHANSVmParseInt: 4: promote object type to full integer; objdiff 94.69388; insns 49/49, diffs 3; .data 18.050066
CHANSVmGetSourceLine: 4: cache program counter before table indexing; objdiff 97.82609; insns 46/46, diffs 16; .data 18.050066
CHANSVmGetSourceLine: 5: type the local program counter as the debug offset; objdiff 97.82609; insns 46/46, diffs 16; .data 18.050066
CHANSVmParseInt: 5: scope output buffer and endpoint to the string conversion; objdiff 87.755104; insns 49/49, diffs 6; .data 18.050066

### Full gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/channelScript/CHANSVm] pool: IDENTICAL
[src/channelScript/CHANSVm] objdiff: code 32944/53564 data 2232/6904 functions 208/233 fuzzy 98.4492 linked code 0
[src/channelScript/CHANSVm] instruction-exact functions: 207/233
[src/channelScript/CHANSVm]   section .data size 4672 match 18.050066
[src/channelScript/CHANSVm]   section .rodata size 1432 match 100.0
[src/channelScript/CHANSVm]   section .sbss size 16 match 100.0
[src/channelScript/CHANSVm]   section .sdata size 600 match 100.0
[src/channelScript/CHANSVm]   section .sdata2 size 184 match 100.0
[src/channelScript/CHANSVm]   section .text size 53564 match 98.44918
[src/channelScript/CHANSVm]   below 100: CHANSVmGetSourceLine 97.82609
[src/channelScript/CHANSVm]   below 100: CHANSVmNewObjData 99.427086
[src/channelScript/CHANSVm]   below 100: CHANSVmParseInt 94.69388
[src/channelScript/CHANSVm]   below 100: CHANSVm_8144B4D4 96.92771
[src/channelScript/CHANSVm]   below 100: VmArraySlice 96.2782
[src/channelScript/CHANSVm]   below 100: VmDateDtor 94.96703
[src/channelScript/CHANSVm]   below 100: VmStringFromCharCode 99.40678
[src/channelScript/CHANSVm]   below 100: VmStringReplace 97.106064
[src/channelScript/CHANSVm]   below 100: VmStringSplit 96.04955
[src/channelScript/CHANSVm]   below 100: CHANSVm_8145049C 98.58237
[src/channelScript/CHANSVm]   below 100: CHANSVm_81450D14 97.391304
[src/channelScript/CHANSVm]   below 100: VmBlobGetHexString 98.71951
[src/channelScript/CHANSVm]   below 100: VmBlobCalcRangeSHA1Digest 96.484535
[src/channelScript/CHANSVm]   below 100: VmBlobCalcHMAC 99.453125
[src/channelScript/CHANSVm]   below 100: VmBlobCalcRangeHMAC 99.97479
[src/channelScript/CHANSVm]   below 100: vmBlobParsePackFormatString 99.69827
[src/channelScript/CHANSVm]   below 100: VmBlobPackCommon 92.603294
[src/channelScript/CHANSVm]   below 100: VmBlobUnpack 92.083176
[src/channelScript/CHANSVm]   below 100: VmImageCtor 99.0
[src/channelScript/CHANSVm]   below 100: VmWinEmuWrite 99.62687
[src/channelScript/CHANSVm]   below 100: CHANSVmAddExe 99.1063
[src/channelScript/CHANSVm]   below 100: CHANSVm_81455654 94.0
[src/channelScript/CHANSVm]   below 100: CHANSVmLinkModules 98.677246
[src/channelScript/CHANSVm]   below 100: VmCallMethod 97.2242
[src/channelScript/CHANSVm]   below 100: CHANSVmStep 95.172386
[src/channelScript/CHANSVm] baseline: code 32400/53564 data 2232 functions 207 fuzzy 98.3831
regressions vs baseline: 0
global matched_code_percent: 84.84254 -> 84.86070
global fuzzy_match_percent: 98.08433 -> 98.08551
global complete_code_percent: 59.34297 -> 59.34297
global matched_data_percent: 90.43305 -> 90.43305
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

No source/header/configuration outside this leaf changed. No linking promotion was attempted.

## 2026-09-30 interpreter body sizes

Baseline 23/121 correct interpreter jump-table relocations. Main case order is already correct. Inspecting instruction-count spans from the top; register differences are excluded from this structural measurement.

first unequal instruction-count span target+0x30; jump relocations 23/121; size 0x1394/0x1394
Unequal instruction-count spans: [('delete', 12, 13, 12, 12), ('delete', 15, 16, 14, 14), ('insert', 22, 22, 20, 22), ('insert', 25, 25, 25, 27), ('insert', 187, 187, 189, 190), ('insert', 209, 209, 212, 213), ('insert', 511, 511, 515, 516), ('delete', 512, 513, 517, 517), ('insert', 598, 598, 602, 603), ('delete', 599, 600, 604, 604), ('insert', 641, 641, 645, 646), ('delete', 665, 666, 670, 670), ('delete', 667, 668, 671, 671), ('insert', 670, 670, 673, 674), ('delete', 671, 672, 675, 675), ('replace', 729, 731, 732, 733), ('delete', 758, 759, 760, 760), ('insert', 773, 773, 774, 775), ('delete', 775, 776, 777, 777), ('insert', 804, 804, 805, 806), ('insert', 834, 834, 836, 837), ('delete', 837, 839, 840, 840), ('delete', 842, 843, 843, 843), ('delete', 993, 994, 993, 993), ('insert', 999, 999, 998, 999), ('delete', 1073, 1074, 1073, 1073), ('insert', 1076, 1076, 1075, 1076), ('insert', 1154, 1154, 1154, 1155), ('delete', 1159, 1160, 1160, 1160)]
Body spans: target start-end | mine start-end | instruction counts | entries
013c-0144 | 0144-014c | 2/2 | 1
0144-014c | 014c-0154 | 2/2 | 1
014c-0154 | 0154-015c | 2/2 | 1
0154-0188 | 015c-0190 | 13/13 | 1
0188-01c4 | 0190-01cc | 15/15 | 1
01c4-01d4 | 01cc-01dc | 4/4 | 1
01d4-01e4 | 01dc-01ec | 4/4 | 1
01e4-01f4 | 01ec-01fc | 4/4 | 1
01f4-0204 | 01fc-020c | 4/4 | 1
0204-0214 | 020c-021c | 4/4 | 1
0214-0224 | 021c-022c | 4/4 | 1
0224-0234 | 022c-023c | 4/4 | 1
0234-0244 | 023c-024c | 4/4 | 1
0244-0254 | 024c-025c | 4/4 | 1
0254-0264 | 025c-026c | 4/4 | 1
0264-0274 | 026c-027c | 4/4 | 1
0274-0284 | 027c-028c | 4/4 | 1
0284-0294 | 028c-029c | 4/4 | 1
0294-0344 | 029c-0350 | 44/45 | 1
0344-034c | 0350-035c | 2/3 | 1
034c-0354 | 035c-0364 | 2/2 | 4
0354-035c | 0364-036c | 2/2 | 1
035c-0364 | 036c-0374 | 2/2 | 1
0364-036c | 0374-037c | 2/2 | 2
036c-0500 | 037c-0510 | 101/101 | 38
0500-056c | 0510-057c | 27/27 | 1
056c-0580 | 057c-0590 | 5/5 | 1
0580-0590 | 0590-05a0 | 4/4 | 1
0590-05a0 | 05a0-05b0 | 4/4 | 1
05a0-05b0 | 05b0-05c0 | 4/4 | 1
05b0-05c0 | 05c0-05d0 | 4/4 | 1
05c0-05d0 | 05d0-05e0 | 4/4 | 1
05d0-05e0 | 05e0-05f0 | 4/4 | 1
05e0-05f0 | 05f0-0600 | 4/4 | 1
05f0-0600 | 0600-0610 | 4/4 | 1
0600-0610 | 0610-0620 | 4/4 | 1
0610-0620 | 0620-0630 | 4/4 | 1
0620-0630 | 0630-0640 | 4/4 | 1
0630-0640 | 0640-0650 | 4/4 | 1
0640-0650 | 0650-0660 | 4/4 | 1
0650-0660 | 0660-0670 | 4/4 | 1
0660-0670 | 0670-0680 | 4/4 | 1
0670-06a0 | 0680-06b0 | 12/12 | 1
06a0-06d0 | 06b0-06e0 | 12/12 | 1
06d0-06e8 | 06e0-06f8 | 6/6 | 1
06e8-07a8 | 06f8-07b8 | 48/48 | 1
07a8-07e4 | 07b8-07f4 | 15/15 | 1
07e4-0854 | 07f4-0864 | 28/28 | 1
0854-0894 | 0864-08a4 | 16/16 | 1
0894-08b0 | 08a4-08c0 | 7/7 | 1
08b0-08f4 | 08c0-0904 | 17/17 | 1
08f4-0940 | 0904-0950 | 19/19 | 2
0940-09c8 | 0950-09d8 | 34/34 | 1
09c8-0a6c | 09d8-0a7c | 41/41 | 1
0a6c-0b8c | 0a7c-0b94 | 72/70 | 1
0b8c-0da4 | 0b94-0da4 | 134/132 | 1
0da4-0e74 | 0da4-0e74 | 52/52 | 1
0e74-0f14 | 0e74-0f14 | 40/40 | 1
0f14-0f2c | 0f14-0f2c | 6/6 | 1
0f2c-0f80 | 0f2c-0f80 | 21/21 | 1
0f80-0fb8 | 0f80-0fb8 | 14/14 | 1
0fb8-1114 | 0fb8-1114 | 87/87 | 8
1114-113c | 1114-113c | 10/10 | 1
113c-1154 | 113c-1154 | 6/6 | 1
1154-11a4 | 1154-11a4 | 20/20 | 1
11a4-11ac | 11a4-11ac | 2/2 | 1
11ac-11f0 | 11ac-11f0 | 17/17 | 4
11f0-1394 | 11f0-1394 | 105/105 | 2

### Source trials

- const-qualified result-table rows: first unequal instruction-count span target+0x30; jump relocations 23/121; size 0x1394/0x1394; restored.
- const byte pointers for result-table conversion: first unequal instruction-count span target+0x30; jump relocations 23/121; size 0x1394/0x1394; restored.
- Conversion table address: first unequal instruction-count span target+0x30; jump relocations 23/121; size 0x1394/0x1394; restored.
- Conversion table base_pointer: first unequal instruction-count span target+0x30; jump relocations 0/121; size 0x1390/0x1394; restored.
- Conversion table row_pointer: first unequal instruction-count span target+0x30; jump relocations 23/121; size 0x1394/0x1394; restored.
- Conversion table array_temporary: first unequal instruction-count span target+0x30; jump relocations 96/121; size 0x1384/0x1394; retained.
- Conversion default table initialization: frame now 0xf0 (target 0xf0), first opcode label now 0x13c (target 0x13c); remaining ADD target entry skips an empty case. Full gate PASS, 208/233 objdiff, 207/233 instruction-exact, .data 18.050066.
- Initial conversion matrix arith: first unequal instruction-count span target+0x30; jump relocations 23/121; size 0x1394/0x1394; restored.
- Initial conversion matrix cmp: first unequal instruction-count span target+0x30; jump relocations 23/121; size 0x1394/0x1394; restored.
- Initial conversion matrix eq: first unequal instruction-count span target+0x30; jump relocations 23/121; size 0x1394/0x1394; restored.
- Initial conversion matrix bitShift: first unequal instruction-count span target+0x30; jump relocations 23/121; size 0x1394/0x1394; restored.
- SET_INDEX cache: first unequal instruction-count span target+0x30; jump relocations 96/121; size 0x1388/0x1394; restored.
- SET_INDEX common: first unequal instruction-count span target+0x30; jump relocations 96/121; size 0x1388/0x1394; restored.
- SET_INDEX cache_common: first unequal instruction-count span target+0x30; jump relocations 97/121; size 0x138c/0x1394; retained.
- SET_INDEX cache_common_float: compiler error, restored.
- SET_INDEX shared result check and accumulator pointer: target/source body counts 72/72, GET_PROPERTY_NAME entry restored to 0xb8c. Full gate PASS, relocation targets 97/121; .data 18.050066.
- GET_PROPERTY_NAME length: first unequal instruction-count span target+0x30; jump relocations 97/121; size 0x13a0/0x1394; restored.
- GET_PROPERTY_NAME cache_length: compiler error, restored.
- GET_PROPERTY_NAME cache_length_branch: compiler error, restored.
- GET_PROPERTY_NAME cache_length_branch_signed_counter_tail: compiler error, restored.
- GET_PROPERTY_NAME cached accumulator, remaining counter, string-length validation and shared status: first unequal instruction-count span target+0x30; jump relocations 62/121; size 0x1388/0x1394; restored.
- GET_PROPERTY_NAME baseline structured candidate diagnostic: first unequal instruction-count span target+0x30; jump relocations 62/121; size 0x1388/0x1394; restored.
- GET_PROPERTY_NAME corrected cache_length: first unequal instruction-count span target+0x30; jump relocations 97/121; size 0x13a4/0x1394; restored.
- GET_PROPERTY_NAME corrected cache_length_branch: first unequal instruction-count span target+0x30; jump relocations 2/121; size 0x13a4/0x1394; restored.
- GET_PROPERTY_NAME corrected cache_length_branch_signed_counter_tail: first unequal instruction-count span target+0x30; jump relocations 2/121; size 0x13a0/0x1394; restored.
- GET_PROPERTY_NAME shape init_index: first unequal instruction-count span target+0x30; jump relocations 62/121; size 0x138c/0x1394; restored.
- GET_PROPERTY_NAME shape nonarray_else: first unequal instruction-count span target+0x30; jump relocations 62/121; size 0x1390/0x1394; restored.
- GET_PROPERTY_NAME shape init_index_nonarray_else: first unequal instruction-count span target+0x30; jump relocations 85/121; size 0x1394/0x1394; restored.
- GET_PROPERTY_NAME shape global_index: first unequal instruction-count span target+0x30; jump relocations 62/121; size 0x1388/0x1394; restored.
- GET_PROPERTY_NAME shape arrayflag: first unequal instruction-count span target+0x30; jump relocations 62/121; size 0x138c/0x1394; restored.
- GET_PROPERTY_NAME body with status_local: first unequal instruction-count span target+0x30; jump relocations 62/121; size 0x1390/0x1394; restored.
- GET_PROPERTY_NAME body with log_not: first unequal instruction-count span target+0x30; jump relocations 95/121; size 0x1394/0x1394; restored.
- GET_PROPERTY_NAME body with copy_temps: first unequal instruction-count span target+0x30; jump relocations 62/121; size 0x1390/0x1394; restored.
- GET_PROPERTY_NAME body with result_length: first unequal instruction-count span target+0x30; jump relocations 62/121; size 0x1390/0x1394; restored.
- GET_PROPERTY_NAME body with result_string_length: first unequal instruction-count span target+0x30; jump relocations 62/121; size 0x1390/0x1394; restored.
- GET_PROPERTY_NAME body with opfunc_first: first unequal instruction-count span target+0x30; jump relocations 62/121; size 0x1390/0x1394; restored.
- GET_PROPERTY_NAME body with opkind_signed: first unequal instruction-count span target+0x30; jump relocations 62/121; size 0x1390/0x1394; restored.
- LOAD_INDIRECT indexed reference with load: first unequal instruction-count span target+0x30; jump relocations 97/121; size 0x138c/0x1394; restored.
- LOAD_INDIRECT indexed reference with property_load: first unequal instruction-count span target+0x30; jump relocations 62/121; size 0x1390/0x1394; restored.
- LOAD_INDIRECT indexed reference with property_init_load: first unequal instruction-count span target+0x30; jump relocations 85/121; size 0x1394/0x1394; restored.
- LOAD_INDIRECT indexed reference with property_load_lognot: first unequal instruction-count span target+0x30; jump relocations 95/121; size 0x1394/0x1394; restored.
- LOAD_INDIRECT indexed reference with property_init_load_lognot: first unequal instruction-count span target+0x30; jump relocations 72/121; size 0x1398/0x1394; restored.
- Boolean status tail with boolean_local: first unequal instruction-count span target+0x30; jump relocations 97/121; size 0x138c/0x1394; restored.
- Boolean status tail with property_boolean_local: first unequal instruction-count span target+0x30; jump relocations 62/121; size 0x1390/0x1394; restored.
- Boolean status tail with property_boolean_local_load: first unequal instruction-count span target+0x30; jump relocations 62/121; size 0x1390/0x1394; restored.
- Boolean status tail with property_init_boolean_local_load: first unequal instruction-count span target+0x30; jump relocations 85/121; size 0x1394/0x1394; restored.
- Property body and declaration scope result_outer: first unequal instruction-count span target+0x30; jump relocations 62/121; size 0x1390/0x1394; restored.
- Property body and declaration scope all_outer: first unequal instruction-count span target+0x30; jump relocations 62/121; size 0x1390/0x1394; restored.
- Property body and declaration scope binary_outer: first unequal instruction-count span target+0x30; jump relocations 62/121; size 0x1390/0x1394; restored.
- Property body and declaration scope object_temps_first: first unequal instruction-count span target+0x30; jump relocations 62/121; size 0x1390/0x1394; restored.
- Property body and declaration scope types_before_objects: first unequal instruction-count span target+0x30; jump relocations 62/121; size 0x1390/0x1394; restored.
- Property body and declaration scope bool_correct_property_scope: first unequal instruction-count span target+0x30; jump relocations 62/121; size 0x1390/0x1394; restored.
- Original property control flow error_gotos: first unequal instruction-count span target+0x30; jump relocations 97/121; size 0x1380/0x1394; restored.
- Original property control flow error_gotos_length: first unequal instruction-count span target+0x30; jump relocations 97/121; size 0x1390/0x1394; restored.
- Original property control flow error_gotos_length_nozero: first unequal instruction-count span target+0x30; jump relocations 97/121; size 0x138c/0x1394; restored.
- Original property control flow error_gotos_length_branch: first unequal instruction-count span target+0x30; jump relocations 25/121; size 0x1390/0x1394; restored.
- Original property control flow result_local_error: first unequal instruction-count span target+0x30; jump relocations 97/121; size 0x137c/0x1394; restored.
- Original property control flow helper_format: first unequal instruction-count span target+0x30; jump relocations 97/121; size 0x1380/0x1394; restored.
- Operand conversion types_pointer_outer: first unequal instruction-count span target+0x30; jump relocations 97/121; size 0x138c/0x1394; restored.
- Operand conversion types_pointer_inner: first unequal instruction-count span target+0x30; jump relocations 97/121; size 0x138c/0x1394; restored.
- Operand conversion type_indexing: first unequal instruction-count span target+0x30; jump relocations 97/121; size 0x138c/0x1394; restored.
- Operand conversion table_pointer_outer: first unequal instruction-count span target+0x58; jump relocations 0/121; size 0x1398/0x1394; restored.
- Operand conversion pointer_array_inner: first unequal instruction-count span target+0x30; jump relocations 97/121; size 0x138c/0x1394; restored.
- Operand conversion void_table_inner: first unequal instruction-count span target+0x30; jump relocations 97/121; size 0x138c/0x1394; restored.
- Operand conversion table_switch_result: first unequal instruction-count span target+0x30; jump relocations 0/121; size 0x139c/0x1394; restored.
- Property validation refinement integer_signed_bounds: first unequal instruction-count span target+0x30; jump relocations 97/121; size 0x13c4/0x1394; restored.
- Property validation refinement high_low_bounds: first unequal instruction-count span target+0x30; jump relocations 97/121; size 0x13bc/0x1394; restored.
- Property validation refinement delete_assign: first unequal instruction-count span target+0x30; jump relocations 97/121; size 0x1390/0x1394; restored.
- Property validation refinement newobject_assign: first unequal instruction-count span target+0x30; jump relocations 97/121; size 0x1390/0x1394; restored.
- Property validation refinement string_length_copy: compiler error, restored.
- Property validation refinement negative_length: first unequal instruction-count span target+0x30; jump relocations 97/121; size 0x1388/0x1394; restored.
- Property validation refinement foundidx_computed: first unequal instruction-count span target+0x30; jump relocations 120/121; size 0x1394/0x1394; retained.
- Property validation refinement boolean_flag: first unequal instruction-count span target+0x30; jump relocations 97/121; size 0x1390/0x1394; restored.
- Property validation refinement loop_for: first unequal instruction-count span target+0x30; jump relocations 97/121; size 0x1390/0x1394; restored.
- Property validation refinement loop_do: first unequal instruction-count span target+0x30; jump relocations 120/121; size 0x1394/0x1394; restored.
- Metric clarification: mnemonic SequenceMatcher initially reports 0x30 because the readonly base load moves across memset; this is instruction scheduling, not a size difference. Use the first wrong cumulative case-label offset as the size anchor: initial 0x13c, current 0x344. Initial loop entry 0x78 vs target 0x70; current loop entry 0x70. Current first extra table-header instructions are at source 0x324/0x32c, balanced by an empty ADD case.
- GET_PROPERTY_NAME now 134/134 instructions. Carry the found element index in computedAddr, keep enumeration remaining separate, validate formatted string length, and share error completion. Full gate PASS; jump offsets 120/121 correct; all case intervals except ADD table label/header now match counts.
- File-private interpreter-only result type table linkage diagnostic: first unequal instruction-count span target+0x30; jump relocations 120/121; size 0x1394/0x1394; restored (support declaration outside requested function).
- ADD table control/lifetime goto_cases: first wrong cumulative size anchor target+0x344; jump relocations 120/121; size 0x1394/0x1394; restored.
- ADD table control/lifetime outer_declaration: first wrong cumulative size anchor target+0x344; jump relocations 120/121; size 0x1394/0x1394; restored.
- ADD table control/lifetime operator_declaration: first wrong cumulative size anchor target+0x344; jump relocations 120/121; size 0x1394/0x1394; restored.
- ADD table control/lifetime function_initialization: first wrong cumulative size anchor target+0x13c; jump relocations 0/121; size 0x13a4/0x1394; restored.
- ADD table control/lifetime typecheck_initialization: first wrong cumulative size anchor target+0x13c; jump relocations 0/121; size 0x13a4/0x1394; restored.
- ADD table control/lifetime operator_initialization: first wrong cumulative size anchor target+0x13c; jump relocations 0/121; size 0x13a4/0x1394; restored.
- ADD table control/lifetime enum_kind: first wrong cumulative size anchor target+0x344; jump relocations 120/121; size 0x1394/0x1394; restored.
- ADD table control/lifetime case_value_normalization: first wrong cumulative size anchor target+0x344; jump relocations 120/121; size 0x1394/0x1394; restored.
- ADD table control/lifetime case_scope: first wrong cumulative size anchor target+0x13c; jump relocations 0/121; size 0x13a4/0x1394; restored.
- ADD table control/lifetime result_default: first wrong cumulative size anchor target+0x344; jump relocations 74/121; size 0x1394/0x1394; restored.
- Inline result table helper table_return: first wrong cumulative size anchor target+0x13c; jump relocations 0/121; size 0x13ac/0x1394; restored.
- Inline result table helper table_return_default: first wrong cumulative size anchor target+0x13c; jump relocations 0/121; size 0x13a8/0x1394; restored.
- Inline result table helper table_out: first wrong cumulative size anchor target+0x13c; jump relocations 0/121; size 0x13c0/0x1394; restored.
- Inline result table helper enum_and_table: first wrong cumulative size anchor target+0x13c; jump relocations 0/121; size 0x13b4/0x1394; restored.
- Operator table with loop form table_math_normalize: first wrong cumulative size anchor target+0x13c; jump relocations 0/121; size 0x139c/0x1394; restored.
- Operator table with loop form table_do: first wrong cumulative size anchor target+0x13c; jump relocations 0/121; size 0x139c/0x1394; restored.
- Operator table with loop form table_math_do: first wrong cumulative size anchor target+0x344; jump relocations 19/121; size 0x1398/0x1394; restored.
- Operator table with loop form table_math_do_typeptr: first wrong cumulative size anchor target+0x1394; jump relocations 121/121; size 0x1394/0x1394; retained.
- Operator table with loop form table_ternary_do_typeptr: compiler error, restored.
- Operator table with loop form table_math_do_reverse_types: compiler error, restored.
- Operator table with loop form table_math_do_array_ptr: compiler error, restored.
- Complete interpreter layout: all 68 distinct case/shared-tail intervals have matching counts; all 121 relocation offsets match (type 10/10, operator 47/47, opcode 64/64). First mismatched size anchor: none. Entry prefix and final tail sizes match; 1253/1253 total instructions.
- The final operator-table change uses the actual resultTypes pointer and a moving enum-output pointer. Normalize zero step counts arithmetically and use a do loop with the existing count value. These remove the entry copy/branch while retaining the requested iteration count. No synthetic data, offsets or padding were added.
```text
first wrong cumulative size anchor target+0x1394; jump relocations 121/121; size 0x1394/0x1394
Unequal instruction-count spans: [('insert', 13, 13, 13, 14), ('delete', 16, 18, 17, 17), ('insert', 22, 22, 21, 23), ('delete', 27, 28, 28, 28), ('insert', 187, 187, 187, 188), ('delete', 188, 189, 189, 189), ('insert', 511, 511, 511, 512), ('delete', 512, 513, 513, 513), ('insert', 598, 598, 598, 599), ('delete', 599, 600, 600, 600), ('insert', 641, 641, 641, 642), ('delete', 665, 666, 666, 666), ('insert', 773, 773, 773, 774), ('delete', 842, 843, 843, 843), ('delete', 993, 994, 993, 993), ('insert', 999, 999, 998, 999), ('delete', 1073, 1074, 1073, 1073), ('insert', 1076, 1076, 1075, 1076), ('insert', 1154, 1154, 1154, 1155), ('delete', 1159, 1160, 1160, 1160), ('insert', 1236, 1236, 1236, 1237), ('delete', 1237, 1238, 1238, 1238)]
Body spans: target start-end | mine start-end | instruction counts | entries
013c-0144 | 013c-0144 | 2/2 | 1
0144-014c | 0144-014c | 2/2 | 1
014c-0154 | 014c-0154 | 2/2 | 1
0154-0188 | 0154-0188 | 13/13 | 1
0188-01c4 | 0188-01c4 | 15/15 | 1
01c4-01d4 | 01c4-01d4 | 4/4 | 1
01d4-01e4 | 01d4-01e4 | 4/4 | 1
01e4-01f4 | 01e4-01f4 | 4/4 | 1
01f4-0204 | 01f4-0204 | 4/4 | 1
0204-0214 | 0204-0214 | 4/4 | 1
0214-0224 | 0214-0224 | 4/4 | 1
0224-0234 | 0224-0234 | 4/4 | 1
0234-0244 | 0234-0244 | 4/4 | 1
0244-0254 | 0244-0254 | 4/4 | 1
0254-0264 | 0254-0264 | 4/4 | 1
0264-0274 | 0264-0274 | 4/4 | 1
0274-0284 | 0274-0284 | 4/4 | 1
0284-0294 | 0284-0294 | 4/4 | 1
0294-0344 | 0294-0344 | 44/44 | 1
0344-034c | 0344-034c | 2/2 | 1
034c-0354 | 034c-0354 | 2/2 | 4
0354-035c | 0354-035c | 2/2 | 1
035c-0364 | 035c-0364 | 2/2 | 1
0364-036c | 0364-036c | 2/2 | 2
036c-0500 | 036c-0500 | 101/101 | 38
0500-056c | 0500-056c | 27/27 | 1
056c-0580 | 056c-0580 | 5/5 | 1
0580-0590 | 0580-0590 | 4/4 | 1
0590-05a0 | 0590-05a0 | 4/4 | 1
05a0-05b0 | 05a0-05b0 | 4/4 | 1
05b0-05c0 | 05b0-05c0 | 4/4 | 1
05c0-05d0 | 05c0-05d0 | 4/4 | 1
05d0-05e0 | 05d0-05e0 | 4/4 | 1
05e0-05f0 | 05e0-05f0 | 4/4 | 1
05f0-0600 | 05f0-0600 | 4/4 | 1
0600-0610 | 0600-0610 | 4/4 | 1
0610-0620 | 0610-0620 | 4/4 | 1
0620-0630 | 0620-0630 | 4/4 | 1
0630-0640 | 0630-0640 | 4/4 | 1
0640-0650 | 0640-0650 | 4/4 | 1
0650-0660 | 0650-0660 | 4/4 | 1
0660-0670 | 0660-0670 | 4/4 | 1
0670-06a0 | 0670-06a0 | 12/12 | 1
06a0-06d0 | 06a0-06d0 | 12/12 | 1
06d0-06e8 | 06d0-06e8 | 6/6 | 1
06e8-07a8 | 06e8-07a8 | 48/48 | 1
07a8-07e4 | 07a8-07e4 | 15/15 | 1
07e4-0854 | 07e4-0854 | 28/28 | 1
0854-0894 | 0854-0894 | 16/16 | 1
0894-08b0 | 0894-08b0 | 7/7 | 1
08b0-08f4 | 08b0-08f4 | 17/17 | 1
08f4-0940 | 08f4-0940 | 19/19 | 2
0940-09c8 | 0940-09c8 | 34/34 | 1
09c8-0a6c | 09c8-0a6c | 41/41 | 1
0a6c-0b8c | 0a6c-0b8c | 72/72 | 1
0b8c-0da4 | 0b8c-0da4 | 134/134 | 1
0da4-0e74 | 0da4-0e74 | 52/52 | 1
0e74-0f14 | 0e74-0f14 | 40/40 | 1
0f14-0f2c | 0f14-0f2c | 6/6 | 1
0f2c-0f80 | 0f2c-0f80 | 21/21 | 1
0f80-0fb8 | 0f80-0fb8 | 14/14 | 1
0fb8-1114 | 0fb8-1114 | 87/87 | 8
1114-113c | 1114-113c | 10/10 | 1
113c-1154 | 113c-1154 | 6/6 | 1
1154-11a4 | 1154-11a4 | 20/20 | 1
11a4-11ac | 11a4-11ac | 2/2 | 1
11ac-11f0 | 11ac-11f0 | 17/17 | 4
11f0-1394 | 11f0-1394 | 105/105 | 2
```
- Final full gate PASS: objdiff code 32944/53564, data 6904/6904, functions 208/233; instruction-exact 207/233; .data 100.0; CHANSVmStep 96.199524. Zero regressions, forbidden patterns and readability warnings. Instruction-exact count is unchanged; this round completes the requested case-size/relocation work, not full instruction matching.
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/channelScript/CHANSVm] pool: IDENTICAL
[src/channelScript/CHANSVm] objdiff: code 32944/53564 data 6904/6904 functions 208/233 fuzzy 98.5453 linked code 0
[src/channelScript/CHANSVm] instruction-exact functions: 207/233
[src/channelScript/CHANSVm]   section .data size 4672 match 100.0
[src/channelScript/CHANSVm]   section .rodata size 1432 match 100.0
[src/channelScript/CHANSVm]   section .sbss size 16 match 100.0
[src/channelScript/CHANSVm]   section .sdata size 600 match 100.0
[src/channelScript/CHANSVm]   section .sdata2 size 184 match 100.0
[src/channelScript/CHANSVm]   section .text size 53564 match 98.54529
[src/channelScript/CHANSVm]   below 100: CHANSVmGetSourceLine 97.82609
[src/channelScript/CHANSVm]   below 100: CHANSVmNewObjData 99.427086
[src/channelScript/CHANSVm]   below 100: CHANSVmParseInt 94.69388
[src/channelScript/CHANSVm]   below 100: CHANSVm_8144B4D4 96.92771
[src/channelScript/CHANSVm]   below 100: VmArraySlice 96.2782
[src/channelScript/CHANSVm]   below 100: VmDateDtor 94.96703
[src/channelScript/CHANSVm]   below 100: VmStringFromCharCode 99.40678
[src/channelScript/CHANSVm]   below 100: VmStringReplace 97.106064
[src/channelScript/CHANSVm]   below 100: VmStringSplit 96.04955
[src/channelScript/CHANSVm]   below 100: CHANSVm_8145049C 98.58237
[src/channelScript/CHANSVm]   below 100: CHANSVm_81450D14 97.391304
[src/channelScript/CHANSVm]   below 100: VmBlobGetHexString 98.71951
[src/channelScript/CHANSVm]   below 100: VmBlobCalcRangeSHA1Digest 96.484535
[src/channelScript/CHANSVm]   below 100: VmBlobCalcHMAC 99.453125
[src/channelScript/CHANSVm]   below 100: VmBlobCalcRangeHMAC 99.97479
[src/channelScript/CHANSVm]   below 100: vmBlobParsePackFormatString 99.69827
[src/channelScript/CHANSVm]   below 100: VmBlobPackCommon 92.603294
[src/channelScript/CHANSVm]   below 100: VmBlobUnpack 92.083176
[src/channelScript/CHANSVm]   below 100: VmImageCtor 99.0
[src/channelScript/CHANSVm]   below 100: VmWinEmuWrite 99.62687
[src/channelScript/CHANSVm]   below 100: CHANSVmAddExe 99.1063
[src/channelScript/CHANSVm]   below 100: CHANSVm_81455654 94.0
[src/channelScript/CHANSVm]   below 100: CHANSVmLinkModules 98.677246
[src/channelScript/CHANSVm]   below 100: VmCallMethod 97.2242
[src/channelScript/CHANSVm]   below 100: CHANSVmStep 96.199524
[src/channelScript/CHANSVm] baseline: code 32944/53564 data 2232 functions 208 fuzzy 98.4492
regressions vs baseline: 0
global matched_code_percent: 84.94337 -> 84.94337
global fuzzy_match_percent: 98.15556 -> 98.15729
global complete_code_percent: 59.34297 -> 59.34297
global matched_data_percent: 90.43501 -> 90.68994
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
