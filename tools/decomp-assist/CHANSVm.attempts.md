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

## 2026-09-30 code continuation on agent/w0930/chansvm-code

- Fresh branch at latest origin/main 2a34d370. Latest-main gate has no baseline report; use supported --base 3f5248be, the nearest existing ancestor baseline and the merged interpreter data fix. No baseline files changed. Initial instruction-exact 207/233, objdiff 208/233; code 32944/53564; data 6904/6904; .data 100%; jump targets 121/121. Step first, then all remaining 25 raw-inexact functions by percentage.
- CHANSVmStep: two typed enum slots and two copy headers prevent scratch overlap: 96.213890%; insns 1253/1253; diffs 337; jump targets 121/121; .data 100.0%; restored.
- CHANSVmStep: typed enum slots alone align the output type buffer: 96.199524%; insns 1253/1253; diffs 355; jump targets 121/121; .data 100.0%; restored.
- CHANSVmStep: preserve Boolean conversion status in a local and one result tail: 96.215485%; insns 1253/1253; diffs 351; jump targets 121/121; .data 100.0%; restored.
- CHANSVmStep: load indirect array index from its copied reference: 96.407020%; insns 1253/1253; diffs 354; jump targets 121/121; .data 100.0%; restored.
- Baseline gate audit before source changes: origin/main 2a34d370 has no stored report; nearest report 3f5248be reports 16 existing fa-driver regressions on unmodified latest main. Supported --base 30809a5b is the nearest available ancestor whose baseline is preserved by unmodified latest main (208/233 CHANSVm functions). Keep a separately generated fresh latest-main report in /tmp and require no regressions relative to it as well. No report or gate tool was modified.
- CHANSVmStep: two typed enum slots and two copy headers prevent scratch overlap: 96.213890%; insns 1253/1253; diffs 337; jump targets 121/121; .data 100.0%; retained, quick gate PASS.
- Step scratch-layout improvement: full gate PASS with --base 30809a5b. Two actual copy slots and two enum slots remove the out-of-bounds adjacent-header access; score 96.213890%, 337 raw differences versus 355. All jump targets 121/121 and .data 100%.
- CHANSVmStep: keep Boolean status in one local and copy it after conversion: 96.229850%; insns 1253/1253; diffs 333; jump targets 121/121; .data 100.0%; retained, quick gate PASS.
- CHANSVmStep: read LOAD_INDIRECT index from copied reference header: 96.437350%; insns 1253/1253; diffs 332; jump targets 121/121; .data 100.0%; retained, quick gate PASS.
- CHANSVmStep: test nonnegative float index before upper bound: 96.437350%; insns 1253/1253; diffs 332; jump targets 121/121; .data 100.0%; restored.
- CHANSVmStep: read copied floating index through its value field: 96.437350%; insns 1253/1253; diffs 332; jump targets 121/121; .data 100.0%; restored.
- CHANSVmStep: use bounded type-array indices for conversion outputs: 96.380684%; insns 1254/1253; diffs 1133; jump targets 19/121; .data 18.050066%; restored.
- CHANSVmStep: declare conversion enum buffer before scratch headers: 96.437350%; insns 1253/1253; diffs 332; jump targets 121/121; .data 100.0%; restored.
- VmBlobFill: use integer enum names for both argument conversions: 100.000000%; insns 63/63; diffs 2; jump targets 121/121; .data 100.0%; restored.
- VmBlobFill: remove redundant parent recheck after null rejection: 91.746030%; insns 60/63; diffs 43; jump targets 121/121; .data 100.0%; restored.
- VmBlobFill: reject missing parent and value in separate guards: 96.666664%; insns 65/63; diffs 39; jump targets 121/121; .data 100.0%; restored.
- VmBlobCalcRangeHMAC: represent the one digest context as a one-element context buffer: 99.974790%; insns 119/119; diffs 3; jump targets 121/121; .data 100.0%; restored.
- VmBlobCalcRangeHMAC: use a word buffer for the word-accessed SDK context workspace: 99.974790%; insns 119/119; diffs 3; jump targets 121/121; .data 100.0%; restored.
- VmBlobCalcRangeHMAC: reuse an explicit pointer to the existing context for all API calls: 96.722690%; insns 120/119; diffs 44; jump targets 121/121; .data 100.0%; restored.
- vmBlobParsePackFormatString: perform decimal multiplication, character addition and zero subtraction separately: 99.655174%; insns 116/116; diffs 6; jump targets 121/121; .data 100.0%; restored.
- vmBlobParsePackFormatString: scope the numeric input character to its parameter iteration: 98.017240%; insns 117/116; diffs 41; jump targets 121/121; .data 100.0%; restored.
- vmBlobParsePackFormatString: use one bounded unsigned decimal digit test: 98.353450%; insns 115/116; diffs 45; jump targets 121/121; .data 100.0%; restored.
- VmWinEmuWrite: advance the output cursor with the matching string-size constant: 99.626870%; insns 67/67; diffs 5; jump targets 121/121; .data 100.0%; restored.
- VmWinEmuWrite: limit remaining bytes before converting byte count to character count: 87.820890%; insns 67/67; diffs 13; jump targets 121/121; .data 100.0%; restored.
- VmWinEmuWrite: declare and initialize the converted string only at its use: 99.626870%; insns 67/67; diffs 5; jump targets 121/121; .data 100.0%; restored.
- VmBlobCalcHMAC: keep the key argument retrieval beside its instance check: 99.453125%; insns 64/64; diffs 7; jump targets 121/121; .data 100.0%; restored.
- VmBlobCalcHMAC: cache key payload and size at digest initialization: 99.453125%; insns 64/64; diffs 7; jump targets 121/121; .data 100.0%; restored.
- VmBlobCalcHMAC: use the context as an API work buffer array: 99.453125%; insns 64/64; diffs 7; jump targets 121/121; .data 100.0%; restored.
- CHANSVmNewObjData: initialize candidate allocation size where it is consumed: compiler error; restored.
- CHANSVmNewObjData: separate slot-pointer assignment from the next slot index update: 93.687500%; insns 96/96; diffs 21; jump targets 121/121; .data 100.0%; restored.
- CHANSVmNewObjData: replace the dead byte-offset accumulator with a typed chunk-table cursor: 90.177086%; insns 96/96; diffs 51; jump targets 121/121; .data 100.0%; restored.
- VmStringFromCharCode: form the truncation mask through the character range expression: 99.406780%; insns 59/59; diffs 6; jump targets 121/121; .data 100.0%; restored.
- VmStringFromCharCode: compute the second byte store index after the first store: 99.406780%; insns 59/59; diffs 6; jump targets 121/121; .data 100.0%; restored.
- VmStringFromCharCode: initialize the UTF-16 character value before the null-object branch: 94.237290%; insns 58/59; diffs 33; jump targets 121/121; .data 100.0%; restored.
- CHANSVmNewObjData: scope aligned allocation size with the allocation payload: 99.427086%; insns 96/96; diffs 10; jump targets 121/121; .data 100.0%; restored.
- CHANSVmAddExe: increment the module index before advancing the clear offset: 99.153540%; insns 254/254; diffs 34; jump targets 121/121; .data 100.0%; retained, quick gate PASS.
- CHANSVmAddExe: address the cleared module entry through its declared table type: 99.153540%; insns 254/254; diffs 34; jump targets 121/121; .data 100.0%; restored.
- CHANSVmAddExe: commute region-size arithmetic at method bounds validation: 99.153540%; insns 254/254; diffs 34; jump targets 121/121; .data 100.0%; restored.
- VmImageCtor: load the image callback into its API callback type: compiler error; restored.
- VmImageCtor: load payload and size within the callback branch: 98.920000%; insns 25/25; diffs 4; jump targets 121/121; .data 100.0%; restored.
- VmImageCtor: express successful no-callback construction as an early return: 91.800000%; insns 26/25; diffs 13; jump targets 121/121; .data 100.0%; restored.
- VmBlobGetHexString: advance both hexadecimal character indices after their stores: 96.158540%; insns 81/82; diffs 34; jump targets 121/121; .data 100.0%; restored.
- VmBlobGetHexString: initialize the low-nibble character index before the high-nibble index: 98.719510%; insns 82/82; diffs 14; jump targets 121/121; .data 100.0%; restored.
- VmBlobGetHexString: cache each source byte before converting its nibbles: 92.365850%; insns 81/82; diffs 36; jump targets 121/121; .data 100.0%; restored.
- CHANSVmLinkModules: scope each dispatch-pass index to its module iteration: 98.677246%; insns 189/189; diffs 43; jump targets 121/121; .data 100.0%; restored.
- CHANSVmLinkModules: load the dispatch table after its iteration cursor is initialized: 98.640210%; insns 189/189; diffs 43; jump targets 121/121; .data 100.0%; restored.
- CHANSVmLinkModules: advance the linked-module iteration number before its module pointer: 98.677246%; insns 189/189; diffs 43; jump targets 121/121; .data 100.0%; restored.
- CHANSVmGetSourceLine: cache the program-counter byte and block index for source lookup: 97.826090%; insns 46/46; diffs 18; jump targets 121/121; .data 100.0%; restored.
- CHANSVmGetSourceLine: move line-offset initialization after the bitfield address: 97.826090%; insns 46/46; diffs 16; jump targets 121/121; .data 100.0%; restored.
- CHANSVmGetSourceLine: use the source-line bitfield length to compute the byte position: 97.826090%; insns 46/46; diffs 16; jump targets 121/121; .data 100.0%; restored.
- CHANSVm_81450D14: handle negative positions before checking the upper bound: 49.673912%; insns 39/46; diffs 41; jump targets 121/121; .data 100.0%; restored.
- CHANSVm_81450D14: express the out-of-range test as the inverse of two bounds: 97.391304%; insns 45/46; diffs 29; jump targets 121/121; .data 100.0%; restored.
- CHANSVm_81450D14: keep negative-offset normalization at a shared success label: 97.391304%; insns 45/46; diffs 29; jump targets 121/121; .data 100.0%; restored.
- VmStringReplace: load replacement length after all three string payloads: 97.840910%; insns 132/132; diffs 41; jump targets 121/121; .data 100.0%; retained, quick gate PASS.
- VmStringReplace: initialize destination and source cursors in destination-first order: 97.878784%; insns 132/132; diffs 40; jump targets 121/121; .data 100.0%; retained, quick gate PASS.
- VmStringReplace: advance copied UTF-16 output before advancing input: 97.803030%; insns 132/132; diffs 41; jump targets 121/121; .data 100.0%; restored.
- VmImageCtor: cache the registered image-construction callback in its real API type: 99.000000%; insns 25/25; diffs 4; jump targets 121/121; .data 100.0%; restored.
- CHANSVm_8145049C: represent the temporary formatted object using its actual object type: 98.582370%; insns 431/431; diffs 42; jump targets 121/121; .data 100.0%; restored.
- CHANSVm_8145049C: represent the UTF-16 character workspace with typed character storage: 98.582370%; insns 431/431; diffs 42; jump targets 121/121; .data 100.0%; restored.
- CHANSVm_8145049C: initialize the source position after the segment and argument cursors: 98.542920%; insns 431/431; diffs 45; jump targets 121/121; .data 100.0%; restored.
- VmCallMethod: return missing-method and missing-property errors directly: 96.316730%; insns 280/281; diffs 246; jump targets 121/121; .data 100.0%; restored.
- VmCallMethod: initialize the call header counts before resolving the target: 97.224200%; insns 281/281; diffs 97; jump targets 121/121; .data 100.0%; restored.
- VmCallMethod: scope the code address and instruction pointer to one execution-context load: 97.224200%; insns 281/281; diffs 97; jump targets 121/121; .data 100.0%; restored.
- CHANSVm_8144B4D4: use a real end-pointer local instead of a volatile integer alias: 96.927710%; insns 83/83; diffs 13; jump targets 121/121; .data 100.0%; restored.
- CHANSVm_8144B4D4: initialize the conversion result after clearing the parsed end pointer: 94.518074%; insns 83/83; diffs 13; jump targets 121/121; .data 100.0%; restored.
- CHANSVm_8144B4D4: advance the string terminator through the character count before parsing: 96.987950%; insns 83/83; diffs 10; jump targets 121/121; .data 100.0%; retained, quick gate PASS.
- VmBlobCalcRangeSHA1Digest: initialize the source data pointer directly at the digest update call: 87.206184%; insns 96/97; diffs 36; jump targets 121/121; .data 100.0%; restored.
- VmBlobCalcRangeSHA1Digest: declare the range offset after the digest workspace: 96.484535%; insns 97/97; diffs 14; jump targets 121/121; .data 100.0%; restored.
- VmBlobCalcRangeSHA1Digest: represent the SHA1 workspace as a one-element API context buffer: 96.484535%; insns 97/97; diffs 14; jump targets 121/121; .data 100.0%; restored.
- VmArraySlice: compute the slice end before initializing its beginning: 95.827065%; insns 133/133; diffs 59; jump targets 121/121; .data 100.0%; restored.
- VmArraySlice: load each source element before acquiring the destination slot: 88.684210%; insns 133/133; diffs 60; jump targets 121/121; .data 100.0%; restored.
- VmArraySlice: compute an empty slice with an explicit end-before-start branch: 92.067670%; insns 131/133; diffs 106; jump targets 121/121; .data 100.0%; restored.
- VmStringSplit: load both string lengths before their payload addresses: 95.936935%; insns 222/222; diffs 92; jump targets 121/121; .data 100.0%; restored.
- VmStringSplit: initialize the segment cursor and count before the scanning cursor: 96.049550%; insns 222/222; diffs 81; jump targets 121/121; .data 100.0%; restored.
- VmStringSplit: advance the empty-delimiter byte cursor before its array index: 95.995500%; insns 222/222; diffs 82; jump targets 121/121; .data 100.0%; restored.
- VmDateDtor: declare the calendar structure before its formatting buffer: 94.967030%; insns 91/91; diffs 7; jump targets 121/121; .data 100.0%; restored.
- VmDateDtor: initialize the calendar pointer at its declaration: 94.967030%; insns 91/91; diffs 7; jump targets 121/121; .data 100.0%; restored.
- VmDateDtor: clear the calendar through its named value instead of its pointer: 94.967030%; insns 91/91; diffs 7; jump targets 121/121; .data 100.0%; restored.
- CHANSVmParseInt: declare the numeric parse end pointer before the character buffer: 94.693880%; insns 49/49; diffs 3; jump targets 121/121; .data 100.0%; restored.
- CHANSVmParseInt: initialize the type discriminator after its parse-end pointer: 83.673470%; insns 49/49; diffs 5; jump targets 121/121; .data 100.0%; restored.
- CHANSVmParseInt: limit the parsed numeric temporary to the successful conversion block: 94.693880%; insns 49/49; diffs 3; jump targets 121/121; .data 100.0%; restored.
- CHANSVm_81455654: form the global object directly from its typed module-table entry: 94.000000%; insns 34/35; diffs 35; jump targets 121/121; .data 100.0%; restored.
- CHANSVm_81455654: select local headers before argument slots in the valid-frame branch: 71.000000%; insns 34/35; diffs 35; jump targets 121/121; .data 100.0%; restored.
- CHANSVm_81455654: compute the argument slot by subtracting the frame displacement first: 87.428570%; insns 34/35; diffs 35; jump targets 121/121; .data 100.0%; restored.
- VmBlobPackCommon: load the numeric packed value through the real integer object field: 92.603294%; insns 675/668; diffs 642; jump targets 121/121; .data 100.0%; restored.
- VmBlobPackCommon: initialize the format cursor before its packed argument cursor: 92.588326%; insns 675/668; diffs 644; jump targets 121/121; .data 100.0%; restored.
- VmBlobPackCommon: compute the copied destination pointer before the source byte count: 92.603294%; insns 675/668; diffs 642; jump targets 121/121; .data 100.0%; restored.
- VmBlobUnpack: declare the two-word unpack buffer as a typed integer union: 92.104450%; insns 531/517; diffs 496; jump targets 121/121; .data 100.0%; retained, quick gate PASS.
- VmBlobUnpack: scope the initial parse defaults to their format iteration: 91.655710%; insns 531/517; diffs 500; jump targets 121/121; .data 100.0%; restored.
- VmBlobUnpack: initialize string-termination character count before scanning: 92.404260%; insns 532/517; diffs 500; jump targets 121/121; .data 100.0%; retained, quick gate PASS.
- CHANSVmParseInt: initialize the parse end pointer before reading the object type: 83.673470%; insns 49/49; diffs 5; jump targets 121/121; .data 100.0%; restored.
- CHANSVmParseInt: initialize the parse end pointer beside the input-buffer declaration: 94.693880%; insns 49/49; diffs 3; jump targets 121/121; .data 100.0%; restored.
- CHANSVmParseInt: scope the base and output copies to the successful string branch: 94.693880%; insns 49/49; diffs 3; jump targets 121/121; .data 100.0%; restored.
- CHANSVm_81450D14: use explicit normalization and output blocks for the two bounds: 97.391304%; insns 45/46; diffs 29; jump targets 121/121; .data 100.0%; restored.
- CHANSVm_81450D14: leave the valid upper-bound branch with an explicit output jump: 97.391304%; insns 45/46; diffs 29; jump targets 121/121; .data 100.0%; restored.
- CHANSVm_81450D14: separate valid and normalized positions with a positive-bounds success test: 97.391304%; insns 45/46; diffs 29; jump targets 121/121; .data 100.0%; restored.
- CHANSVm_81455654: return a null pointer explicitly for an invalid argument slot: 88.142860%; insns 36/35; diffs 36; jump targets 121/121; .data 100.0%; restored.
- CHANSVm_81455654: return the initial null result before looking up a negative frame slot: 76.571430%; insns 36/35; diffs 36; jump targets 121/121; .data 100.0%; restored.
- CHANSVm_81455654: initialize the module-object result only in the global table branch: 94.000000%; insns 34/35; diffs 35; jump targets 121/121; .data 100.0%; restored.
- CHANSVmStep: set the default instruction budget with an explicit zero-count branch: 96.838780%; insns 1254/1253; diffs 1230; jump targets 0/121; .data 18.050066%; restored.
- CHANSVmStep: store floating immediate bytes in their natural floating-point value: 96.437350%; insns 1253/1253; diffs 332; jump targets 121/121; .data 100.0%; restored.
- CHANSVmStep: initialize enum cursor after operand discriminator loads: 96.437350%; insns 1253/1253; diffs 332; jump targets 121/121; .data 100.0%; restored.
- CHANSVmStep: form conversion enum cursor from a byte count within its array: 96.547485%; insns 1251/1253; diffs 1104; jump targets 19/121; .data 18.050066%; restored.
- CHANSVmStep: restore countdown entry test and select result matrices directly from their table: 96.756584%; insns 1256/1253; diffs 1231; jump targets 0/121; .data 18.050066%; restored.
- CHANSVmStep: keep the original budget and select each conversion matrix by direct member address: 96.292900%; insns 1254/1253; diffs 1096; jump targets 20/121; .data 18.050066%; restored.
- vmBlobParsePackFormatString: retain the Unicode input character in an unsigned code-point variable: 99.698270%; insns 116/116; diffs 6; jump targets 121/121; .data 100.0%; restored.
- vmBlobParsePackFormatString: accumulate decimal digits with a wide intermediate before overflow rejection: 89.991380%; insns 123/116; diffs 102; jump targets 121/121; .data 100.0%; restored.
- vmBlobParsePackFormatString: isolate the decimal product before reusing the parameter accumulator: 99.698270%; insns 116/116; diffs 6; jump targets 121/121; .data 100.0%; restored.
- VmWinEmuWrite: scope the string length to the successful conversion branch: 99.626870%; insns 67/67; diffs 5; jump targets 121/121; .data 100.0%; restored.
- VmWinEmuWrite: scope the converted string object to its output loop: 99.626870%; insns 67/67; diffs 5; jump targets 121/121; .data 100.0%; restored.
- VmWinEmuWrite: initialize the output cursor after reading the string byte count: 99.626870%; insns 67/67; diffs 5; jump targets 121/121; .data 100.0%; restored.
- VmBlobCalcHMAC: scope the key object to its native-instance resolution: 99.437500%; insns 64/64; diffs 12; jump targets 121/121; .data 100.0%; restored.
- VmBlobCalcHMAC: scope the newly created blob header to digest-buffer retrieval: compiler error; restored.
- VmBlobCalcHMAC: read the blob payload before its digest input size: 99.265625%; insns 64/64; diffs 11; jump targets 121/121; .data 100.0%; restored.
- VmImageCtor: cache the image payload within the callback guard: 99.000000%; insns 25/25; diffs 4; jump targets 121/121; .data 100.0%; restored.
- VmImageCtor: scope the image header to the callback path: 83.000000%; insns 25/25; diffs 7; jump targets 121/121; .data 100.0%; restored.
- VmImageCtor: declare the image header before initializing its constructor result: 99.000000%; insns 25/25; diffs 4; jump targets 121/121; .data 100.0%; restored.
- VmDateDtor: name day and month text at the formatting call: 94.967030%; insns 91/91; diffs 7; jump targets 121/121; .data 100.0%; restored.
- VmDateDtor: retrieve the month text before the weekday text: 94.967030%; insns 91/91; diffs 7; jump targets 121/121; .data 100.0%; restored.
- VmDateDtor: name the calendar year before selecting its format strings: 94.967030%; insns 91/91; diffs 7; jump targets 121/121; .data 100.0%; restored.
- VmBlobUnpack: read the signed eight-byte packed integer through the integer-union value: 92.404260%; insns 532/517; diffs 500; jump targets 121/121; .data 100.0%; restored.
- CHANSVm_81450D14: compare the combined range-rejection predicate with the VM false value: 93.804344%; insns 48/46; diffs 31; jump targets 121/121; .data 100.0%; restored.
- CHANSVm_81450D14: compare both range predicates with the VM true value: 84.782610%; insns 52/46; diffs 35; jump targets 121/121; .data 100.0%; restored.
- CHANSVm_81450D14: retain a Boolean range predicate for normalization: 93.804344%; insns 48/46; diffs 31; jump targets 121/121; .data 100.0%; restored.
- VmBlobUnpack: retain typed 64-bit union-member reads as a readability correction with identical compiled instructions, percentage, unit measures, pool and 121/121 targets; quick gate PASS. The integer member is actively used to decode the eight-byte packed integer; it is not unused alignment storage.

### Final code-round audit

- Every remaining function has at least three distinct, compiling source-level attempts in this round. All accepted edits passed the quick gate, the string pool, 121/121 Step jump relocations and .data 100%.
- A separate fresh project-wide report comparison against the unmodified latest-main 2a34d370 report found zero reductions in matched code/data, linked code/data or function counts across every unit. Gate fallback does not hide a latest-main regression.
- Instruction-exact count is unchanged: 207/233. Objdiff-exact count is unchanged: 208/233. No new exact function is claimed. The retained changes improve fuzzy matching and repair actual scratch storage and unset values.

| Open function | Objdiff % | Instructions | Raw differences | Distinct compiling attempts | Remaining difference |
|---|---:|---:|---:|---:|---|
| CHANSVmStep | 96.437350 | 1253/1253 | 332 | 16 | stack slots, registers, entry/countdown control flow; all case counts and jump relocations match |
| VmBlobFill | 100.000000 | 63/63 | 2 | 3 | 100% objdiff; ctxdiff CR-qualified branch decoding uses absolute address, leaving two tool differences |
| VmBlobCalcRangeHMAC | 99.974790 | 119/119 | 3 | 3 | context stack offset 0x0c versus 0x10 |
| vmBlobParsePackFormatString | 99.698270 | 116/116 | 6 | 6 | register allocation and instruction scheduling |
| VmWinEmuWrite | 99.626870 | 67/67 | 5 | 6 | register allocation and instruction scheduling |
| VmBlobCalcHMAC | 99.453125 | 64/64 | 7 | 5 | register allocation and instruction scheduling |
| CHANSVmNewObjData | 99.427086 | 96/96 | 10 | 3 | register allocation and instruction scheduling |
| VmStringFromCharCode | 99.406780 | 59/59 | 6 | 3 | register allocation and instruction scheduling |
| CHANSVmAddExe | 99.153540 | 254/254 | 34 | 3 | register allocation and instruction scheduling |
| VmImageCtor | 99.000000 | 25/25 | 4 | 6 | register allocation and instruction scheduling |
| VmBlobGetHexString | 98.719510 | 82/82 | 14 | 3 | register allocation and instruction scheduling |
| CHANSVmLinkModules | 98.677246 | 189/189 | 43 | 3 | register allocation and instruction scheduling |
| CHANSVm_8145049C | 98.582370 | 431/431 | 42 | 3 | register allocation and instruction scheduling |
| VmStringReplace | 97.878784 | 132/132 | 40 | 3 | register allocation and instruction scheduling |
| CHANSVmGetSourceLine | 97.826090 | 46/46 | 16 | 3 | register allocation and instruction scheduling |
| CHANSVm_81450D14 | 97.391304 | 45/46 | 29 | 9 | missing upper-bound branch; one commuted add operand |
| VmCallMethod | 97.224200 | 281/281 | 97 | 3 | register allocation and instruction scheduling |
| CHANSVm_8144B4D4 | 96.987950 | 83/83 | 10 | 3 | register allocation and instruction scheduling |
| VmBlobCalcRangeSHA1Digest | 96.484535 | 97/97 | 14 | 3 | register allocation and instruction scheduling |
| VmArraySlice | 96.278200 | 133/133 | 56 | 3 | register allocation and instruction scheduling |
| VmStringSplit | 96.049550 | 222/222 | 81 | 3 | register allocation and instruction scheduling |
| VmDateDtor | 94.967030 | 91/91 | 7 | 6 | day/month table address and format-argument scheduling |
| CHANSVmParseInt | 94.693880 | 49/49 | 3 | 6 | end-pointer store scheduled after parameter copies |
| CHANSVm_81455654 | 94.000000 | 34/35 | 35 | 6 | control flow and instruction count |
| VmBlobPackCommon | 92.603294 | 675/668 | 642 | 3 | control flow and instruction count |
| VmBlobUnpack | 92.404260 | 532/517 | 500 | 4 | control flow and instruction count |

- VmBlobFill tool-artifact confirmation: both complete function byte strings are identical. Both objects contain 0x4186000c at function+0x68 and 0x41860018 at function+0x7c; Capstone displays CR1-qualified branches with absolute destinations separated by the four-byte function-placement difference. Objdiff correctly reports 100%.
- Final non-quick gate uses supported --base 30809a5b because latest main 2a34d370 has no baseline report, while the nearer available 3f5248be baseline reports sixteen preexisting fa-driver regressions on the unmodified latest main. This fallback and the separate latest-main report comparison are explicitly disclosed. Baseline reports and gate tooling were not modified.
- The original increase-in-instruction-exact-count acceptance condition was not achieved in this round; this is partial progress after the required attempts, not a completed unit.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/channelScript/CHANSVm] pool: IDENTICAL
[src/channelScript/CHANSVm] objdiff: code 32944/53564 data 6904/6904 functions 208/233 fuzzy 98.5888 linked code 0
[src/channelScript/CHANSVm] instruction-exact functions: 207/233
[src/channelScript/CHANSVm]   section .data size 4672 match 100.0
[src/channelScript/CHANSVm]   section .rodata size 1432 match 100.0
[src/channelScript/CHANSVm]   section .sbss size 16 match 100.0
[src/channelScript/CHANSVm]   section .sdata size 600 match 100.0
[src/channelScript/CHANSVm]   section .sdata2 size 184 match 100.0
[src/channelScript/CHANSVm]   section .text size 53564 match 98.58883
[src/channelScript/CHANSVm]   below 100: CHANSVmGetSourceLine 97.82609
[src/channelScript/CHANSVm]   below 100: CHANSVmNewObjData 99.427086
[src/channelScript/CHANSVm]   below 100: CHANSVmParseInt 94.69388
[src/channelScript/CHANSVm]   below 100: CHANSVm_8144B4D4 96.98795
[src/channelScript/CHANSVm]   below 100: VmArraySlice 96.2782
[src/channelScript/CHANSVm]   below 100: VmDateDtor 94.96703
[src/channelScript/CHANSVm]   below 100: VmStringFromCharCode 99.40678
[src/channelScript/CHANSVm]   below 100: VmStringReplace 97.878784
[src/channelScript/CHANSVm]   below 100: VmStringSplit 96.04955
[src/channelScript/CHANSVm]   below 100: CHANSVm_8145049C 98.58237
[src/channelScript/CHANSVm]   below 100: CHANSVm_81450D14 97.391304
[src/channelScript/CHANSVm]   below 100: VmBlobGetHexString 98.71951
[src/channelScript/CHANSVm]   below 100: VmBlobCalcRangeSHA1Digest 96.484535
[src/channelScript/CHANSVm]   below 100: VmBlobCalcHMAC 99.453125
[src/channelScript/CHANSVm]   below 100: VmBlobCalcRangeHMAC 99.97479
[src/channelScript/CHANSVm]   below 100: vmBlobParsePackFormatString 99.69827
[src/channelScript/CHANSVm]   below 100: VmBlobPackCommon 92.603294
[src/channelScript/CHANSVm]   below 100: VmBlobUnpack 92.40426
[src/channelScript/CHANSVm]   below 100: VmImageCtor 99.0
[src/channelScript/CHANSVm]   below 100: VmWinEmuWrite 99.62687
[src/channelScript/CHANSVm]   below 100: CHANSVmAddExe 99.15354
[src/channelScript/CHANSVm]   below 100: CHANSVm_81455654 94.0
[src/channelScript/CHANSVm]   below 100: CHANSVmLinkModules 98.677246
[src/channelScript/CHANSVm]   below 100: VmCallMethod 97.2242
[src/channelScript/CHANSVm]   below 100: CHANSVmStep 96.43735
[src/channelScript/CHANSVm] baseline: code 32944/53564 data 2232 functions 208 fuzzy 98.4492
regressions vs baseline: 0
global matched_code_percent: 85.36819 -> 85.36819
global fuzzy_match_percent: 98.27361 -> 98.27611
global complete_code_percent: 59.70596 -> 59.70596
global matched_data_percent: 90.52625 -> 90.78117
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
- Post-full-clean-build latest-main comparison repeated: zero project-wide matched/linked/function regressions; 121/121 Step jump relocations preserved.
- Local improvement commits: c4ae8bcc correct interpreter scratch object storage; 743f0580 improve chansvmstep code matching; f9928196 improve chansvmstep code matching; 572a7c04 improve chansvmaddexe code matching; 076645dc improve vmstringreplace code matching; 647f5007 improve vmstringreplace code matching; 5e75409f improve chansvm_8144b4d4 code matching; 179218d7 improve vmblobunpack code matching; d125aec2 improve vmblobunpack code matching; 051a713b read unpacked integers through their typed value.
CHANSVmNewObjData declaration order [0, 1, 2, 3, 4, 5]: structural/exact (0, 10)
CHANSVmNewObjData diagnosis: (0, 10); target size 384; declaration entries ['    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;\n', '    u32 idx;\n', '    u32 chunkIdx;\n', '    union {\n        u32 off;\n        ChunkEntry* entry;\n    } u;\n', '    ChunkEntry* chunk;\n', '    u32 memSize;\n']
CHANSVmNewObjData declaration order [1, 0, 2, 3, 4, 5]: structural/exact (0, 10)
CHANSVmNewObjData declaration order [2, 1, 0, 3, 4, 5]: structural/exact (0, 10)
CHANSVmNewObjData declaration order [5, 1, 2, 3, 4, 0]: structural/exact (0, 7)
CHANSVmNewObjData result (0, 7), attempts 163, RESTORED
VmStringFromCharCode declaration order [0, 1, 2, 3, 4]: structural/exact (0, 6)
VmStringFromCharCode diagnosis: (0, 6); target size 236; declaration entries ['    CHANSVmObjHdr* arg;\n', '    u32 offs;\n', '    u32 argc;\n', '    u32 ch;\n', '    u32 i;\n']
VmStringFromCharCode declaration order [1, 0, 2, 3, 4]: structural/exact (0, 6)
VmStringFromCharCode declaration order [2, 1, 0, 3, 4]: structural/exact (0, 9)
VmStringFromCharCode result (0, 6), attempts 90, RESTORED
VmWinEmuWrite declaration order [0, 1, 2, 3, 4, 5, 6, 7]: structural/exact (0, 5)
VmWinEmuWrite diagnosis: (0, 5); target size 268; declaration entries ['    CHANSVmObjHdr* strObj;\n', '    u32 offset;\n', '    u32 totalLength;\n', '    u8 buf[VM_STRING_SIZE];\n', '    s32 outLen;\n', '    s32 inLen;\n', '    s32 result;\n', '    u32 remaining;\n']
VmWinEmuWrite declaration order [1, 0, 2, 3, 4, 5, 6, 7]: structural/exact (0, 5)
VmWinEmuWrite declaration order [2, 1, 0, 3, 4, 5, 6, 7]: structural/exact (0, 8)
VmWinEmuWrite declaration-order search stopped after 3+ distinct compiled orders without improvement; restored original source.

## 2026-10-01 215/233 baseline continuation
Target and current instructions have equal counts for all 18 open functions. Full structural ctxdiff was captured before each experiment. Baseline pool IDENTICAL, .data 100%, 121/121 jump relocations. Declaration-only trials above did not produce exactness.
vmBlobParsePackFormatString: distinct parameter digit scope then split accumulation; 116/116 instructions, 6 differences each; restored. Target preserves format character in r11 and uses distinct numeric digit r0.
vmBlobParsePackFormatString: u32 digit, decimal digit + paramValue * 10 - 0x30: 99.69827%; 116/116 insns; structural/exact (0, 6); .data 100.0%; RESTORED
vmBlobParsePackFormatString: u32 digit, decimal paramValue * 10 + (digit - 0x30): 99.69827%; 116/116 insns; structural/exact (0, 6); .data 100.0%; RESTORED
vmBlobParsePackFormatString: u32 digit, decimal paramValue * 10;
            paramValue += digit;
            paramValue -= 0x30: 99.82758%; 116/116 insns; structural/exact (0, 2); .data 100.0%; RESTORED
vmBlobParsePackFormatString: wchar_t digit, decimal digit + paramValue * 10 - 0x30: 99.69827%; 116/116 insns; structural/exact (0, 6); .data 100.0%; RESTORED
vmBlobParsePackFormatString: wchar_t digit, decimal paramValue * 10 + (digit - 0x30): 99.69827%; 116/116 insns; structural/exact (0, 6); .data 100.0%; RESTORED
vmBlobParsePackFormatString: wchar_t digit, decimal paramValue * 10;
            paramValue += digit;
            paramValue -= 0x30: 99.82758%; 116/116 insns; structural/exact (0, 2); .data 100.0%; RESTORED
vmBlobParsePackFormatString: s32 digit, decimal digit + paramValue * 10 - 0x30: 98.27586%; 116/116 insns; structural/exact (3, 6); .data 100.0%; RESTORED
vmBlobParsePackFormatString: s32 digit, decimal paramValue * 10 + (digit - 0x30): 98.27586%; 116/116 insns; structural/exact (3, 6); .data 100.0%; RESTORED
vmBlobParsePackFormatString: s32 digit, decimal paramValue * 10;
            paramValue += digit;
            paramValue -= 0x30: 98.27586%; 116/116 insns; structural/exact (3, 5); .data 100.0%; RESTORED
vmBlobParsePackFormatString: u16 digit, decimal digit + paramValue * 10 - 0x30: 99.69827%; 116/116 insns; structural/exact (0, 6); .data 100.0%; RESTORED
vmBlobParsePackFormatString: u16 digit, decimal paramValue * 10 + (digit - 0x30): 99.69827%; 116/116 insns; structural/exact (0, 6); .data 100.0%; RESTORED
vmBlobParsePackFormatString: u16 digit, decimal paramValue * 10;
            paramValue += digit;
            paramValue -= 0x30: 99.82758%; 116/116 insns; structural/exact (0, 2); .data 100.0%; RESTORED
vmBlobParsePackFormatString: u32 digit, decimal digit + paramValue * 10 - 0x30: 99.69827%; 116/116 insns; structural/exact (0, 6); .data 100.0%; RESTORED
vmBlobParsePackFormatString: u32 digit, decimal paramValue * 10 + (digit - 0x30): 99.69827%; 116/116 insns; structural/exact (0, 6); .data 100.0%; RESTORED
vmBlobParsePackFormatString: u32 digit, decimal paramValue * 10;
            paramValue += digit;
            paramValue -= 0x30: 99.82758%; 116/116 insns; structural/exact (0, 2); .data 100.0%; RESTORED
vmBlobParsePackFormatString: wchar_t digit, decimal digit + paramValue * 10 - 0x30: 99.69827%; 116/116 insns; structural/exact (0, 6); .data 100.0%; RESTORED
vmBlobParsePackFormatString: wchar_t digit, decimal paramValue * 10 + (digit - 0x30): 99.69827%; 116/116 insns; structural/exact (0, 6); .data 100.0%; RESTORED
vmBlobParsePackFormatString: wchar_t digit, decimal paramValue * 10;
            paramValue += digit;
            paramValue -= 0x30: 99.82758%; 116/116 insns; structural/exact (0, 2); .data 100.0%; RESTORED
vmBlobParsePackFormatString: s32 digit, decimal digit + paramValue * 10 - 0x30: 98.27586%; 116/116 insns; structural/exact (3, 6); .data 100.0%; RESTORED
vmBlobParsePackFormatString: s32 digit, decimal paramValue * 10 + (digit - 0x30): 98.27586%; 116/116 insns; structural/exact (3, 6); .data 100.0%; RESTORED
vmBlobParsePackFormatString: s32 digit, decimal paramValue * 10;
            paramValue += digit;
            paramValue -= 0x30: 98.27586%; 116/116 insns; structural/exact (3, 5); .data 100.0%; RESTORED
vmBlobParsePackFormatString: u16 digit, decimal digit + paramValue * 10 - 0x30: 99.69827%; 116/116 insns; structural/exact (0, 6); .data 100.0%; RESTORED
vmBlobParsePackFormatString: u16 digit, decimal paramValue * 10 + (digit - 0x30): 99.69827%; 116/116 insns; structural/exact (0, 6); .data 100.0%; RESTORED
vmBlobParsePackFormatString: u16 digit, decimal paramValue * 10;
            paramValue += digit;
            paramValue -= 0x30: 99.82758%; 116/116 insns; structural/exact (0, 2); .data 100.0%; RESTORED
vmBlobParsePackFormatString: split decimal with paramValue *= 10;
            paramValue = digit + paramValue - 0x30;: 99.69827%; 116/116 insns; structural/exact (0, 6); .data 100.0%; RESTORED
vmBlobParsePackFormatString: split decimal with paramValue *= 10;
            digit += paramValue;
            paramValue = digit - 0x30;: 99.69827%; 116/116 insns; structural/exact (0, 6); .data 100.0%; RESTORED
vmBlobParsePackFormatString: split decimal with paramValue *= 10;
            paramValue = (s32)(digit + paramValue) - 0x30;: 99.61207%; 116/116 insns; structural/exact (0, 7); .data 100.0%; RESTORED
vmBlobParsePackFormatString: split decimal with paramValue *= 10;
            paramValue = (digit + paramValue);
            paramValue -= 0x30;: 99.61207%; 116/116 insns; structural/exact (0, 7); .data 100.0%; RESTORED
vmBlobParsePackFormatString: split decimal with paramValue *= 10;
            {
                s32 sum = digit + paramValue;
                paramValue = sum - 0x30;
            }: 99.61207%; 116/116 insns; structural/exact (0, 7); .data 100.0%; RESTORED
vmBlobParsePackFormatString: split decimal with paramValue *= 10;
            {
                u32 sum = digit + paramValue;
                paramValue = sum - 0x30;
            }: 99.69827%; 116/116 insns; structural/exact (0, 6); .data 100.0%; RESTORED
vmBlobParsePackFormatString: decimal operand/cast paramValue *= 10;
            paramValue += digit - 0x30;: 99.913795%; 116/116 insns; structural/exact (0, 1); .data 100.0%; RESTORED
vmBlobParsePackFormatString: decimal operand/cast paramValue *= 10;
            paramValue = paramValue + digit - 0x30;: 99.69827%; 116/116 insns; structural/exact (0, 6); .data 100.0%; RESTORED
vmBlobParsePackFormatString: decimal operand/cast paramValue *= 10;
            paramValue += (s32)digit;
            paramValue -= 0x30;: 99.82758%; 116/116 insns; structural/exact (0, 2); .data 100.0%; RESTORED
vmBlobParsePackFormatString: decimal operand/cast paramValue *= 10;
            digit = paramValue + digit;
            paramValue = digit - 0x30;: 99.69827%; 116/116 insns; structural/exact (0, 6); .data 100.0%; RESTORED
vmBlobParsePackFormatString: decimal operand/cast paramValue *= 10;
            paramValue = digit + (u32)paramValue;
            paramValue -= 0x30;: 99.61207%; 116/116 insns; structural/exact (0, 7); .data 100.0%; RESTORED
vmBlobParsePackFormatString: decimal final operand paramValue = (digit - 0x30) + paramValue;: 99.69827%; 116/116 insns; structural/exact (0, 6); .data 100.0%; RESTORED
vmBlobParsePackFormatString: decimal final operand paramValue = digit - 0x30 + paramValue;: 99.69827%; 116/116 insns; structural/exact (0, 6); .data 100.0%; RESTORED
vmBlobParsePackFormatString: decimal final operand paramValue -= 0x30 - digit;: 97.75862%; 116/116 insns; structural/exact (3, 3); .data 100.0%; RESTORED
vmBlobParsePackFormatString: decimal final operand paramValue += digit + -0x30;: 99.913795%; 116/116 insns; structural/exact (0, 1); .data 100.0%; RESTORED
vmBlobParsePackFormatString: decimal final operand paramValue += (s32)digit - 0x30;: 99.913795%; 116/116 insns; structural/exact (0, 1); .data 100.0%; RESTORED
vmBlobParsePackFormatString: decimal final operand paramValue += (u32)(digit - 0x30);: 100.0%; 116/116 insns; structural/exact (0, 0); .data 100.0%; KEPT exact; quick GATE PASS
VmStringFromCharCode: character mask/cursor form 0: 99.40678%; 59/59 insns; structural/exact (0, 6); .data 100.0%; RESTORED
VmStringFromCharCode: character mask/cursor form 1: 99.40678%; 59/59 insns; structural/exact (0, 6); .data 100.0%; RESTORED
VmStringFromCharCode: character mask/cursor form 2: 94.32204%; 57/59 insns; structural/exact (9, 45); .data 100.0%; RESTORED
VmStringFromCharCode: character mask/cursor form 3: 94.32204%; 57/59 insns; structural/exact (9, 45); .data 100.0%; RESTORED
VmStringFromCharCode: character mask/cursor form 4: 99.32204%; 59/59 insns; structural/exact (0, 7); .data 100.0%; RESTORED
VmStringFromCharCode: character mask/cursor form 5: 99.40678%; 59/59 insns; structural/exact (0, 6); .data 100.0%; RESTORED
VmStringFromCharCode: character mask/cursor form 6: 99.40678%; 59/59 insns; structural/exact (0, 6); .data 100.0%; RESTORED
VmStringFromCharCode: character mask/cursor form 7: 99.40678%; 59/59 insns; structural/exact (0, 6); .data 100.0%; RESTORED
VmWinEmuWrite: size type: 99.62687%; 67/67 insns; structural/exact (0, 5); .data 100.0%; RESTORED
VmWinEmuWrite: signed size: 99.62687%; 67/67 insns; structural/exact (0, 5); .data 100.0%; RESTORED
VmWinEmuWrite: cache payload: COMPILE FAIL orm_dep.py build/43U/src/src/channelScript/CHANSVm.d build/43U/src/src/channelScript/CHANSVm.d
### mwcceppc.exe Compiler:
#    File: src\channelScript\CHANSVm.c
# ------------------------------------
#    6073:         strValue = strObj->value.wstring_v; 
#   Error:                                           ^
#   (10209) illegal implicit conversion from 'struct  *' to
#   'struct  *'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.
; RESTORED
VmWinEmuWrite: unmasked cached size: 99.62687%; 67/67 insns; structural/exact (0, 5); .data 100.0%; RESTORED
CHANSVmParseInt: one-slot end buffer: 94.69388%; 49/49 insns; structural/exact (2, 3); .data 100.0%; RESTORED
CHANSVmParseInt: parse scratch structure: 94.69388%; 49/49 insns; structural/exact (2, 3); .data 100.0%; RESTORED
CHANSVmParseInt: initialized parse end: 94.69388%; 49/49 insns; structural/exact (2, 3); .data 100.0%; RESTORED
CHANSVmParseInt: explicit type after end initialization: 83.67347%; 49/49 insns; structural/exact (4, 5); .data 100.0%; RESTORED
CHANSVm_8144B4D4: one-slot end buffer: 97.59036%; 83/83 insns; structural/exact (2, 2); .data 100.0%; RESTORED
CHANSVm_8144B4D4: parse scratch structure: 97.59036%; 83/83 insns; structural/exact (2, 2); .data 100.0%; RESTORED
CHANSVm_8144B4D4: initialized parse end: 97.59036%; 83/83 insns; structural/exact (2, 2); .data 100.0%; RESTORED
CHANSVm_8144B4D4: explicit type after end initialization: 95.180725%; 83/83 insns; structural/exact (2, 3); .data 100.0%; RESTORED
CHANSVmGetSourceLine: explicit source table and guards 0: 79.13043%; 54/46 insns; structural/exact (12, 52); .data 100.0%; RESTORED
CHANSVmGetSourceLine: explicit source table and guards 1: 79.13043%; 54/46 insns; structural/exact (12, 52); .data 100.0%; RESTORED
CHANSVmGetSourceLine: explicit source table and guards 2: 79.13043%; 54/46 insns; structural/exact (12, 52); .data 100.0%; RESTORED
CHANSVmGetSourceLine: explicit source table and guards 3: 79.13043%; 54/46 insns; structural/exact (12, 52); .data 100.0%; RESTORED
CHANSVmGetSourceLine: explicit source table and guards 4: 62.065216%; 50/46 insns; structural/exact (21, 48); .data 100.0%; RESTORED
CHANSVmGetSourceLine: explicit source table and guards 5: 79.13043%; 54/46 insns; structural/exact (12, 52); .data 100.0%; RESTORED
VmDateDtor: month and weekday pointer scopes: 94.96703%; 91/91 insns; structural/exact (5, 7); .data 100.0%; RESTORED
VmDateDtor: calendar by value fields: 89.14286%; 90/91 insns; structural/exact (11, 85); .data 100.0%; RESTORED
VmDateDtor: return format length directly to limit: 94.96703%; 91/91 insns; structural/exact (5, 7); .data 100.0%; RESTORED
VmDateDtor: month table indexed pointer expression: 94.96703%; 91/91 insns; structural/exact (5, 7); .data 100.0%; RESTORED
VmDateDtor: short-lived month pointer: 94.96703%; 91/91 insns; structural/exact (5, 7); .data 100.0%; RESTORED
CHANSVmGetSourceLine: module cached in null-guard scope 0: 97.82609%; 46/46 insns; structural/exact (0, 16); .data 100.0%; RESTORED
CHANSVmGetSourceLine: module cached in null-guard scope 1: 97.82609%; 46/46 insns; structural/exact (0, 18); .data 100.0%; RESTORED
CHANSVmGetSourceLine: module cached in null-guard scope 2: 97.82609%; 46/46 insns; structural/exact (0, 16); .data 100.0%; RESTORED
CHANSVmGetSourceLine: module cached in null-guard scope 3: 97.82609%; 46/46 insns; structural/exact (0, 16); .data 100.0%; RESTORED
CHANSVmGetSourceLine: module cached in null-guard scope 4: 97.82609%; 46/46 insns; structural/exact (0, 16); .data 100.0%; RESTORED
VmStringFromCharCode: integer argument helper: 99.40678%; 59/59 insns; structural/exact (0, 6); .data 100.0%; RESTORED
VmWinEmuWrite: string argument helper: 99.62687%; 67/67 insns; structural/exact (0, 5); .data 100.0%; RESTORED
VmStringReplace: two string argument helpers: 97.878784%; 132/132 insns; structural/exact (0, 40); .data 100.0%; RESTORED
VmStringSplit: string and integer argument helpers: 98.04054%; 222/222 insns; structural/exact (0, 66); .data 100.0%; RESTORED
VmBlobGetHexString: integer argument helper: 98.71951%; 82/82 insns; structural/exact (0, 14); .data 100.0%; RESTORED
VmBlobPackCommon: typed argument helper boundaries: COMPILE FAIL .py build/43U/src/src/channelScript/CHANSVm.d build/43U/src/src/channelScript/CHANSVm.d
### mwcceppc.exe Compiler:
#    File: src\channelScript\CHANSVm.c
# ------------------------------------
#    4976:     argArr = CHANSVmGetArgArray(VmInst, 1); 
#   Error:                                           ^
#   (10209) illegal implicit conversion from 'int' to
#   'struct CHANSVmObjHdr *'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.
; RESTORED
VmBlobUnpack: typed string argument helper boundary: 98.26886%; 517/517 insns; structural/exact (0, 156); .data 100.0%; RESTORED
CHANSVmNewObjData: separate index-offset and entry locals: 97.1875%; 95/96 insns; structural/exact (7, 59); .data 100.0%; RESTORED
CHANSVmNewObjData: scope computed chunk address: 99.427086%; 96/96 insns; structural/exact (0, 10); .data 100.0%; RESTORED
CHANSVmNewObjData: scope slot index to table scan: 99.583336%; 96/96 insns; structural/exact (0, 7); .data 100.0%; RESTORED
CHANSVmNewObjData: counted chunk traversal: 99.427086%; 96/96 insns; structural/exact (0, 10); .data 100.0%; RESTORED
VmStringReplace declaration order [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]: structural/exact (0, 40)
VmStringReplace diagnosis: (0, 40); target size 528; declaration entries ['    CHANSVmObjHdr* arg0;\n', '    CHANSVmObjHdr* arg1;\n', '    vmString parentStr;\n', '    vmString searchStr;\n', '    vmString replaceStr;\n', '    u32 parentLen;\n', '    u32 srcOffs;\n', '    u32 dstOffs;\n', '    u32 searchLen;\n', '    u32 replaceLen;\n', '    u32 dstBufLen;\n', '    vmString newStr;\n', '    u32 segLen;\n']
VmStringReplace declaration order [1, 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]: structural/exact (0, 40)
VmStringReplace declaration order [2, 1, 0, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]: structural/exact (0, 40)
VmStringReplace declaration order [4, 1, 2, 3, 5, 6, 8, 7, 0, 9, 10, 11, 12]: structural/exact (0, 28)
VmStringReplace result (0, 28), attempts 29, RESTORED
VmStringSplit declaration order [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]: structural/exact (0, 66)
VmStringSplit diagnosis: (0, 66); target size 888; declaration entries ['    CHANSVmObjHdr* arg0;\n', '    CHANSVmObjHdr* arg1;\n', '    u32 limit;\n', '    CHANSVmObjHdr* array;\n', '    vmString parentStr;\n', '    vmString delimStr;\n', '    u32 parentLen;\n', '    u32 delimLen;\n', '    u32 count;\n', '    u32 srcOffs;\n', '    u32 segStart;\n', '    u32 arrayCount;\n', '    u32 segLen;\n', '    u32 remaining;\n', '    CHANSVmObjHdr* elem;\n', '    u32 i;\n']
VmStringSplit declaration order [1, 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]: structural/exact (0, 66)
VmStringSplit declaration order [2, 1, 0, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]: structural/exact (0, 66)
VmStringSplit declaration order [14, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 15]: structural/exact (0, 61)
VmStringSplit result (0, 61), attempts 29, RESTORED
CHANSVmAddExe declaration order [0, 1, 2, 3, 4, 5, 6]: structural/exact (0, 34)
CHANSVmAddExe diagnosis: (0, 34); target size 1016; declaration entries ['    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;\n', '    ModuleHeader* mod;\n', '    CHANSVmModule* header;\n', '    u32 maxEnd;\n', '    u32 size;\n', '    u32 cnt;\n', '    u32 ofs;\n']
CHANSVmAddExe declaration order [1, 0, 2, 3, 4, 5, 6]: structural/exact (0, 34)
CHANSVmAddExe declaration order [2, 1, 0, 3, 4, 5, 6]: structural/exact (0, 34)
CHANSVmAddExe result (0, 34), attempts 29, RESTORED
CHANSVmLinkModules declaration order [0, 1, 2, 3]: structural/exact (0, 43)
CHANSVmLinkModules diagnosis: (0, 43); target size 756; declaration entries ['    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;\n', '    CHANSVmModule* module;\n', '    u32 modIdx;\n', '    u32 i;\n']
CHANSVmLinkModules declaration order [1, 0, 2, 3]: structural/exact (0, 43)
CHANSVmLinkModules declaration order [2, 1, 0, 3]: structural/exact (0, 46)
CHANSVmLinkModules result (0, 43), attempts 19, RESTORED
VmCallMethod declaration order [0, 1, 2, 3]: structural/exact (4, 97)
VmCallMethod diagnosis: (4, 97); target size 1124; declaration entries ['    CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm;\n', '    CHANSVmObjHdr* acc;\n', '    u32 retVal;\n', '    CHANSVmNativeClass* target;\n']
VmCallMethod declaration order [1, 0, 2, 3]: structural/exact (4, 97)
VmCallMethod declaration order [2, 1, 0, 3]: structural/exact (4, 109)
VmCallMethod result (4, 97), attempts 19, RESTORED
VmBlobPackCommon declaration order [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26]: structural/exact (2, 246)
VmBlobPackCommon diagnosis: (2, 246); target size 2672; declaration entries ['    u32 packBuf[2];\n', '    BlobHeader* parentBlob;\n', '    CHANSVmObjHdr* argStr;\n', '    const wchar_t* fmtStr;\n', '    u32 fmtLen;\n', '    CHANSVmObjHdr* argArr;\n', '    u32 fmtPos;\n', '    u32 argCount;\n', '    u32 totalSize;\n', '    s32 count;\n', '    u32 i;\n', '    CHANSVmObjHdr* obj;\n', '    BlobHeader* srcBlob;\n', '    s32 copySize;\n', '    u32 dataSize;\n', '    u32 srcOff;\n', '    CHANSVmObjHdr* strObj;\n', '    u8* srcData;\n', '    u32 charCount;\n', '    u32 strLen;\n', '    CHANSVmObjHdr* intObj;\n', '    u32 valLow;\n', '    u32 valHigh;\n', '    s32 bufSize;\n', '    u8* dest;\n', '    u32 ch;\n', '    CHANSVmExecutionCtx* execCtx;\n']
VmBlobPackCommon declaration order [1, 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26]: structural/exact (2, 246)
VmBlobPackCommon declaration order [2, 1, 0, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26]: structural/exact (2, 246)
VmBlobPackCommon declaration order [15, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26]: structural/exact (2, 244)
VmBlobPackCommon result (2, 244), attempts 29, RESTORED
VmBlobUnpack declaration order [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]: structural/exact (0, 156)
VmBlobUnpack diagnosis: (0, 156); target size 2068; declaration entries ['    union {\n        u64 value;\n        u32 words[2];\n    } unpackBuf;\n', '    BlobHeader* srcBlob;\n', '    CHANSVmObjHdr* argStr;\n', '    wchar_t* fmtStr;\n', '    u32 fmtLen;\n', '    u32 blobOff;\n', '    u32 argCount;\n', '    u32 fmtPos;\n', '    s32 count;\n', '    u32 elemIdx;\n', '    u32 iterIdx;\n', '    s64 value;\n', '    CHANSVmObjHdr* arrElem;\n']
VmBlobUnpack declaration order [1, 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]: structural/exact (0, 156)
VmBlobUnpack declaration order [2, 1, 0, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]: structural/exact (0, 156)
VmBlobUnpack declaration order [1, 9, 2, 3, 4, 5, 6, 7, 8, 0, 10, 11, 12]: structural/exact (0, 146)
VmBlobUnpack result (0, 146), attempts 29, RESTORED
CHANSVmNewObjData: offset before chunk scan initialization: 99.427086%; 96/96 insns; structural/exact (0, 10); .data 100.0%; RESTORED
CHANSVmNewObjData: declare scanned chunk inside block: 99.583336%; 96/96 insns; structural/exact (0, 7); .data 100.0%; RESTORED
CHANSVmNewObjData: aligned allocation declared in its lifetime: 99.427086%; 96/96 insns; structural/exact (0, 10); .data 100.0%; RESTORED
VmWinEmuWrite: use byte-string member for output address and length: 99.62687%; 67/67 insns; structural/exact (0, 5); .data 100.0%; RESTORED
VmWinEmuWrite: immutable converted string header: 99.62687%; 67/67 insns; structural/exact (0, 5); .data 100.0%; RESTORED
VmWinEmuWrite: cache wide-string payload: 96.49254%; 65/67 insns; structural/exact (6, 54); .data 100.0%; RESTORED
VmStringFromCharCode: scope byte offset to output creation: 98.72881%; 59/59 insns; structural/exact (0, 12); .data 100.0%; RESTORED
VmStringFromCharCode: immutable argument pointer for char conversion: COMPILE FAIL lScript/CHANSVm.d
### mwcceppc.exe Compiler:
#    File: src\channelScript\CHANSVm.c
# ------------------------------------
#    2873:  CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_INTEGER, arg); 
#   Error:                                                                 ^
#   (10209) illegal implicit conversion from 'const struct CHANSVmObjHdr *' to
#   'struct CHANSVmObjHdr *'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.
; RESTORED
VmStringFromCharCode: decrement argument count traversal: 96.10169%; 60/59 insns; structural/exact (7, 31); .data 100.0%; RESTORED
VmDateDtor: calendar format inline helper char* buffer, OSCalendarTime* date: 94.96703%; 91/91 insns; structural/exact (5, 7); .data 100.0%; RESTORED
VmDateDtor: calendar format inline helper OSCalendarTime* date, char* buffer: 94.96703%; 91/91 insns; structural/exact (5, 7); .data 100.0%; RESTORED
VmDateDtor: calendar format inline helper char* buffer, OSCalendarTime date: 72.98901%; 107/91 insns; structural/exact (52, 97); .data 100.0%; RESTORED
CHANSVm_8145049C: formatted string payload/character lifetime 0: 99.35035%; 430/431 insns; structural/exact (25, 142); .data 18.050066%; RESTORED
CHANSVm_8145049C: formatted string payload/character lifetime 1: COMPILE FAIL ript && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/channelScript/CHANSVm.d build/43U/src/src/channelScript/CHANSVm.d
### mwcceppc.exe Compiler:
#    File: src\channelScript\CHANSVm.c
# ------------------------------------
#    3625:                     wchar_t* characterText = (wchar_t*)pad0; 
#   Error:                     ^^^^^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.
; RESTORED
CHANSVm_8145049C: formatted string payload/character lifetime 2: COMPILE FAIL ript && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/channelScript/CHANSVm.d build/43U/src/src/channelScript/CHANSVm.d
### mwcceppc.exe Compiler:
#    File: src\channelScript\CHANSVm.c
# ------------------------------------
#    3625:                     wchar_t* characterText = (wchar_t*)pad0; 
#   Error:                     ^^^^^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.
; RESTORED
CHANSVm_8145049C: formatted string payload/character lifetime 3: COMPILE FAIL ript && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/channelScript/CHANSVm.d build/43U/src/src/channelScript/CHANSVm.d
### mwcceppc.exe Compiler:
#    File: src\channelScript\CHANSVm.c
# ------------------------------------
#    3625:                     wchar_t* characterText = (wchar_t*)pad0; 
#   Error:                     ^^^^^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.
; RESTORED
CHANSVm_8145049C: formatted string payload/character lifetime 4: COMPILE FAIL ript && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/channelScript/CHANSVm.d build/43U/src/src/channelScript/CHANSVm.d
### mwcceppc.exe Compiler:
#    File: src\channelScript\CHANSVm.c
# ------------------------------------
#    3625:                     wchar_t* characterText = (wchar_t*)pad0; 
#   Error:                     ^^^^^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.
; RESTORED
CHANSVm_8145049C: formatted string payload/character lifetime 5: 98.58237%; 431/431 insns; structural/exact (10, 42); .data 100.0%; RESTORED
CHANSVm_8145049C: formatted string payload/character lifetime 0: 99.35035%; 430/431 insns; structural/exact (25, 142); .data 18.050066%; RESTORED
CHANSVm_8145049C: formatted string payload/character lifetime 1: 96.960556%; 430/431 insns; structural/exact (25, 248); .data 18.050066%; RESTORED
CHANSVm_8145049C: formatted string payload/character lifetime 2: 97.4594%; 431/431 insns; structural/exact (0, 143); .data 100.0%; RESTORED
CHANSVm_8145049C: formatted string payload/character lifetime 3: 96.19257%; 431/431 insns; structural/exact (10, 170); .data 100.0%; RESTORED
CHANSVm_8145049C: formatted string payload/character lifetime 4: 94.967514%; 432/431 insns; structural/exact (46, 358); .data 18.050066%; RESTORED
CHANSVm_8145049C: formatted string payload/character lifetime 5: 98.58237%; 431/431 insns; structural/exact (10, 42); .data 100.0%; RESTORED
VmBlobGetHexString declaration order [0, 1, 2, 3, 4, 5, 6]: structural/exact (0, 14)
VmBlobGetHexString diagnosis: (0, 14); target size 328; declaration entries ['        wchar_t* dest = (wchar_t*)VmGetStrFromObjHdr(VmReturnObj);\n', '        u8* src = blob->pData;\n', '        u32 offset = blob->offset;\n', '        u32 destOff = 0;\n', '        u32 i = 0;\n', '        char* hexTbl = lbl_816976E4;\n', '        u32 loop_i;\n']
VmBlobGetHexString declaration order [1, 0, 2, 3, 4, 5, 6]: structural/exact (4, 27)
VmBlobGetHexString declaration order [2, 1, 0, 3, 4, 5, 6]: structural/exact (8, 27)
VmBlobGetHexString result (0, 14), attempts 98, RESTORED
VmCallMethod: separate resolved method index and return status 0: 97.2242%; 281/281 insns; structural/exact (4, 97); .data 100.0%; RESTORED
VmCallMethod: separate resolved method index and return status 1: 97.2242%; 281/281 insns; structural/exact (4, 97); .data 100.0%; RESTORED
VmCallMethod: separate resolved method index and return status 2: 97.2242%; 281/281 insns; structural/exact (4, 97); .data 100.0%; RESTORED
VmCallMethod: separate resolved method index and return status 3: 97.29537%; 281/281 insns; structural/exact (2, 93); .data 100.0%; RESTORED
CHANSVm_8145049C: cache string data and explicit char terminator lifetime 0: 99.84919%; 431/431 insns; structural/exact (0, 13); .data 100.0%; RESTORED
CHANSVm_8145049C: cache string data and explicit char terminator lifetime 1: 99.35035%; 430/431 insns; structural/exact (25, 142); .data 18.050066%; RESTORED
CHANSVm_8145049C: cache string data and explicit char terminator lifetime 2: 99.35035%; 430/431 insns; structural/exact (25, 142); .data 18.050066%; RESTORED
CHANSVm_8145049C: cache string data and explicit char terminator lifetime 3: 99.35035%; 430/431 insns; structural/exact (25, 142); .data 18.050066%; RESTORED
CHANSVm_8145049C: cache string data and explicit char terminator lifetime 4: 99.35035%; 430/431 insns; structural/exact (25, 142); .data 18.050066%; RESTORED
CHANSVm_8145049C: cached string payload before memcpy and assign the formatting-object tag after UTF-16 terminator storage; 99.84919%; 431/431 instructions, 13 register-only differences, .data 100%; KEPT quick GATE PASS.
CHANSVm_8145049C declaration order [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]: structural/exact (0, 13)
CHANSVm_8145049C diagnosis: (0, 13); target size 1724; declaration entries ['    u32 halfMaxSize;\n', '    BOOL flag;\n', '    CHANSVmObjHdr* tempObj;\n', '    u32 argIdxCounter;\n', '    u32 totalLen;\n', '    u8* str;\n', '    u32 strLen;\n', '    u32 strPos;\n', '    u32 segStart;\n', '    u32 fmtBufPos;\n', '    u8* tmpBuf;\n', '    u32 maxSize;\n', '    u8* outputBuf;\n', '    u32 outputPos;\n', '    u32 maxLitLen;\n', '    u32 litLen;\n', '    u32 isEscaped;\n', '    CHANSVmObjHdr* cv;\n', '    CHANSVmPrivate* pVm;\n', '    CHANSVmObjHdr* argObj;\n']
CHANSVm_8145049C declaration order [1, 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]: structural/exact (5, 18)
CHANSVm_8145049C declaration order [2, 1, 0, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]: structural/exact (5, 18)
CHANSVm_8145049C result (0, 13), attempts 199, RESTORED
VmBlobGetHexString: hexadecimal nibble temporaries/cursor order 0: 98.71951%; 82/82 insns; structural/exact (0, 14); .data 100.0%; RESTORED
VmBlobGetHexString: hexadecimal nibble temporaries/cursor order 1: 98.71951%; 82/82 insns; structural/exact (0, 14); .data 100.0%; RESTORED
VmBlobGetHexString: hexadecimal nibble temporaries/cursor order 2: 98.71951%; 82/82 insns; structural/exact (0, 14); .data 100.0%; RESTORED
VmBlobGetHexString: hexadecimal nibble temporaries/cursor order 3: 96.15854%; 81/82 insns; structural/exact (8, 34); .data 100.0%; RESTORED
VmCallMethod: direct missing method/property conditional return: 97.29537%; 281/281 insns; structural/exact (2, 93); .data 100.0%; RESTORED
VmCallMethod: call argument/operand scheduling 0: 97.98933%; 281/281 insns; structural/exact (2, 95); .data 100.0%; RESTORED
VmCallMethod: call argument/operand scheduling 1: 98.0605%; 281/281 insns; structural/exact (0, 91); .data 100.0%; RESTORED
VmCallMethod: call argument/operand scheduling 2: 97.29537%; 281/281 insns; structural/exact (2, 93); .data 100.0%; RESTORED
CHANSVmStep: typed interpreter scratch layout 0: 96.452515%; 1253/1253 insns; structural/exact (71, 318); .data 100.0%; RESTORED
CHANSVmStep: typed interpreter scratch layout 1: 96.43735%; 1253/1253 insns; structural/exact (90, 332); .data 100.0%; RESTORED
CHANSVmStep: typed interpreter scratch layout 2: 96.440544%; 1253/1253 insns; structural/exact (86, 329); .data 100.0%; RESTORED
CHANSVmStep: entry count branch and pretested loop: 96.96728%; 1255/1253 insns; structural/exact (82, 1229); .data 18.050066%; RESTORED
CHANSVmStep: pretested countdown retaining default count arithmetic: 96.400635%; 1254/1253 insns; structural/exact (87, 1238); .data 18.050066%; RESTORED
CHANSVmStep: separate operand enums before copy headers: 96.43735%; 1253/1253 insns; structural/exact (90, 332); .data 100.0%; RESTORED
VmCallMethod: direct missing-method/property return and choose header argument at call boundary; 98.0605%; 281/281 instructions, 91 register-only differences, structural differences 0; .data 100%; KEPT quick GATE PASS.
CHANSVmStep: group actual type, floating-immediate, copy-header, load-header, and operand workspaces; all fields actively used, no padding or dummy fields; 96.452515%; 1253/1253 instructions, structural/exact 71/318; .data 100%; KEPT quick GATE PASS.
CHANSVmNewObjData: declaration-order coverage 164 distinct source orders; best structural/exact (0, 7); no new exact result, restored previous accepted source.
VmStringFromCharCode: declaration-order coverage 91 distinct source orders; best structural/exact (0, 6); no new exact result, restored previous accepted source.
VmWinEmuWrite: declaration-order coverage 85 distinct source orders; best structural/exact (0, 5); no new exact result, restored previous accepted source.
VmStringReplace: declaration-order coverage 30 distinct source orders; best structural/exact (0, 28); no new exact result, restored previous accepted source.
VmStringSplit: declaration-order coverage 30 distinct source orders; best structural/exact (0, 61); no new exact result, restored previous accepted source.
CHANSVmAddExe: declaration-order coverage 30 distinct source orders; best structural/exact (0, 34); no new exact result, restored previous accepted source.
CHANSVmLinkModules: declaration-order coverage 20 distinct source orders; best structural/exact (0, 43); no new exact result, restored previous accepted source.
VmCallMethod: declaration-order coverage 20 distinct source orders; best structural/exact (4, 97); no new exact result, restored previous accepted source.
VmBlobPackCommon: declaration-order coverage 30 distinct source orders; best structural/exact (2, 244); no new exact result, restored previous accepted source.
VmBlobUnpack: declaration-order coverage 30 distinct source orders; best structural/exact (0, 146); no new exact result, restored previous accepted source.
VmBlobGetHexString: declaration-order coverage 99 distinct source orders; best structural/exact (0, 14); no new exact result, restored previous accepted source.
CHANSVm_8145049C: declaration-order coverage 200 distinct source orders; best structural/exact (0, 13); no new exact result, restored previous accepted source.

## 2026-10-01 final handoff after clean full gate

Instruction-exact 215/233 -> 216/233; objdiff matched code 35020/53564 -> 35484/53564; data 6904/6904 -> 6904/6904; .data 100%. vmBlobParsePackFormatString is now 100% objdiff with 116/116 instructions and ctxdiff diffs 0. All 121 Step and all 89 formatter jump-table relocation offsets, types, and addends match after the clean rebuild.

| Open function | Objdiff % | Structural / raw differences | Distinct current-round attempts | Remaining difference |
|---|---:|---:|---:|---|
| CHANSVmGetSourceLine | 97.82609 | 0 / 16 | 11 | register allocation |
| CHANSVmNewObjData | 99.427086 | 0 / 10 | 171 | register allocation |
| CHANSVmParseInt | 94.69388 | 2 / 3 | 4 | parse-end store after parameter copies |
| CHANSVm_8144B4D4 | 97.59036 | 2 / 2 | 4 | parse-end store after type comparison |
| VmDateDtor | 94.96703 | 5 / 7 | 8 | month/day argument-load scheduling |
| VmStringFromCharCode | 99.40678 | 0 / 6 | 102 | register allocation |
| VmStringReplace | 97.878784 | 0 / 40 | 31 | register allocation |
| VmStringSplit | 98.04054 | 0 / 66 | 31 | register allocation |
| CHANSVm_8145049C | 99.84919 | 0 / 13 | 214 | register allocation |
| VmBlobGetHexString | 98.71951 | 0 / 14 | 104 | register allocation |
| VmBlobPackCommon | 97.934135 | 2 / 246 | 30 | register allocation and two operand-order differences |
| VmBlobUnpack | 98.26886 | 0 / 156 | 31 | register allocation |
| VmWinEmuWrite | 99.62687 | 0 / 5 | 92 | register allocation |
| CHANSVmAddExe | 99.15354 | 0 / 34 | 30 | register allocation |
| CHANSVmLinkModules | 98.677246 | 0 / 43 | 20 | register allocation |
| VmCallMethod | 98.0605 | 0 / 91 | 29 | register allocation |
| CHANSVmStep | 96.452515 | 71 / 318 | 7 | entry/countdown flow, result-table base, registers and remaining spills |

The unit remains partial with 17 open functions; all have at least three distinct compiled source-level attempts in this run. No linking/configuration changes. Compiler tie-breaks remain unresolved. Four local source commits: d6ec7d58, aa49bd1b, 9283affb, 9265fb79.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/channelScript/CHANSVm] pool: IDENTICAL
[src/channelScript/CHANSVm] objdiff: code 35484/53564 data 6904/6904 functions 216/233 fuzzy 99.2720 linked code 0
[src/channelScript/CHANSVm] instruction-exact functions: 216/233
[src/channelScript/CHANSVm]   section .data size 4672 match 100.0
[src/channelScript/CHANSVm]   section .rodata size 1432 match 100.0
[src/channelScript/CHANSVm]   section .sbss size 16 match 100.0
[src/channelScript/CHANSVm]   section .sdata size 600 match 100.0
[src/channelScript/CHANSVm]   section .sdata2 size 184 match 100.0
[src/channelScript/CHANSVm]   section .text size 53564 match 99.27205
[src/channelScript/CHANSVm]   below 100: CHANSVmGetSourceLine 97.82609
[src/channelScript/CHANSVm]   below 100: CHANSVmNewObjData 99.427086
[src/channelScript/CHANSVm]   below 100: CHANSVmParseInt 94.69388
[src/channelScript/CHANSVm]   below 100: CHANSVm_8144B4D4 97.59036
[src/channelScript/CHANSVm]   below 100: VmDateDtor 94.96703
[src/channelScript/CHANSVm]   below 100: VmStringFromCharCode 99.40678
[src/channelScript/CHANSVm]   below 100: VmStringReplace 97.878784
[src/channelScript/CHANSVm]   below 100: VmStringSplit 98.04054
[src/channelScript/CHANSVm]   below 100: CHANSVm_8145049C 99.84919
[src/channelScript/CHANSVm]   below 100: VmBlobGetHexString 98.71951
[src/channelScript/CHANSVm]   below 100: VmBlobPackCommon 97.934135
[src/channelScript/CHANSVm]   below 100: VmBlobUnpack 98.26886
[src/channelScript/CHANSVm]   below 100: VmWinEmuWrite 99.62687
[src/channelScript/CHANSVm]   below 100: CHANSVmAddExe 99.15354
[src/channelScript/CHANSVm]   below 100: CHANSVmLinkModules 98.677246
[src/channelScript/CHANSVm]   below 100: VmCallMethod 98.0605
[src/channelScript/CHANSVm]   below 100: CHANSVmStep 96.452515
[src/channelScript/CHANSVm] baseline: code 35020/53564 data 6904 functions 215 fuzzy 99.2097
regressions vs baseline: 0
global matched_code_percent: 86.68724 -> 86.70274
global fuzzy_match_percent: 99.30689 -> 99.30802
global complete_code_percent: 60.61288 -> 60.61288
global matched_data_percent: 91.11031 -> 91.11031
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## CHANSVmStep objs[4] frame decode (w1009/update)

- Base places operand@r1+0x60, load@0x30, copies elems @0x40/0x50 = a single `CHANSVmObjHdr objs[4]` array (objs[0]=load, objs[1..2]=copies, objs[3]=operand). Declaring separate `operand/load/copies[2]` packs operand first at 0x40. Rewriting uses as `&objs[N]`/`objs[N].` fixed the frame (263->259 diffs).
- `ppc_iro_level 0` around CHANSVmStep: +11 insns (unfuses the stepCount select but adds mrs) — rejected.
- stepCount head: `stepCount += (stepCount == 0)` folds to cntlzw+srwi+add (1253 insns, 259 diffs); `if (stepCount == 0) { stepCount = 1; }` emits base's cmpwi+bne+li but 1254 insns and shifts every downstream block target — rejected. Base's extra `b 0xd0fc` is a test-first loop entry: `while (stepCount-- != 1)` reproduces it but emits +3 insns (1256) — rejected. Orig plausibly used if-clamp + while-loop; neither form converges alone.
- insnClass==0 guard: `(raw & 0xC0)`/((u8)raw) emit mask-only rlwinm like base but +1 insn (fields.bitfield access keeps union web differently); kept `fields.instructionClass`.
- `lis r28/addi r28` symbol-materialization at head = `&VmResultTypeTbl` pointer web, NOT a static copies[].
- Residual 259 diffs: head select-fold + callee web-homing ties (r26/r21, r23/r17, r24 rotations).

## aes-lever sweep (w1009/update, post-#1315 rebase)

Leaf reduced to CHANSVmStep + nup __nupParseServerInfo (VmWinEmuWrite/VmBlobGetHexString/VmBlobPackCommon landed upstream #1315).

- declsearch.py (needed a __-symbol fix — patched copy at /tmp): nup decl block (6 decls, 36 evals) and CHANSVmStep block (8 decls, 50 evals) — current order is optimal in both; rotations are web-priority, not decl order.
- nup all-static locals (`static` on all 5 shared decls): 507 insns, frame -0x40 + savegpr_20 — rejected. (Base's r28+off materializations are the .data tag-string pool, present in mine identically.)
- nup `char*&`/`size_t&` reference params on __nupFindTag: 79 diffs — rejected.
- nup FindTag `start += strlen(tag); *value = start;` (self-add web merge): +8 insns — rejected.
- CHANSVmStep `__rlwinm(raw,0,24,25)==0` and `(raw & 0xC0)==0` for instructionClass: both +1 insn (1254) — bitfield access kept (1253/259).

## o2-chansvm roadmap transfer (w1009/update)

Their Step findings (o2-chansvm.attempts.md) applied and measured on this leaf:
- `if (stepCount==0) stepCount=1;` + `while (stepCount-- != 0)`: loop tail matches byte-exact (cmpwi r16,0;addi r16,-1;bne) and base's entry `b` to the test site is reproduced — but net +2 insns (1255), so it needs the rest of their restructure to converge.
- Frame decode retained: `CHANSVmObjHdr objs[4]` gives exact base slots (operand@0x60 etc.) — their map: 0x30=stackPtr obj, 0x40=STORE_INDIRECT obj, 0x50=load, 0x60=operand (separate decls in orig; frame identical either way).
- Batched application of their remaining items (operandTypes[indexed] + BRANCH_CASE early stackTop + GET_PROPERTY_NAME foundEntry/shouldBranch) → 1260 insns, reverted. These must land as a set with their numbering context, not piecemeal.
- Their meta-levers: copy-use (`mr` copy keeps a named local's web), static-inline helper numbering, signedness mixing (int index over u32 counter), pass 10=SR / pass 14=CTR conversion — all relevant to the residual 259 web-coloring diffs; apply with a score.py whole-unit harness.
