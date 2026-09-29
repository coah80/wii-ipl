# CHANSVm third continuation

Baseline: 46f34f11, instruction-exact 204/233, objdiff functions 205/233, code 31960/53564, data 800/6904.

Result: instruction-exact 205/233, objdiff functions 206/233, code 32348/53564, data 2232/6904.

## Retained changes

- VmBlobCalcRangeMD5Digest: declare byte input and digest before argument conversion. 97/97 instructions, diffs 0; raw 388 bytes identical.
- VmBlobCalcRangeHMAC: the same declaration order removes all register differences, improving 99.72269% to 99.97479%. Three context stack addresses remain.
- VmTypeConvertFuncTbl: restore the six diagonal null entries and converters to their actual destination/source cells. Size unchanged at 144 bytes. The .rodata score is now 100%; all 20 differing relocations are fixed.
- CHANSVmGetEnumedType: classify native object instances with class/method references; global references fall through to invalid. The two incorrect switch relocations are fixed, with identical function instructions and raw bytes.

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
VmBlobCopyRangeFrom, 91.67647%, range-check control flow, 139/136 instructions.
VmBlobGetHexString, 98.71951%, fourteen register differences.
VmBlobCalcRangeSHA1Digest, 96.484535%, range-check scheduling and register allocation.
VmBlobCalcHMAC, 99.453125%, seven register differences.
VmBlobCalcRangeHMAC, 99.97479%, three context-address differences: stack +0x0c versus +0x10; context layout remains unresolved.
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
VmBlobFill, 100.0%, objdiff 100%, raw 252 bytes identical; gate/ctxdiff report two CR1 branch address differences after normalization.

## Data audit and uncertainty

The string pool contains 125 identical strings in the same order. All raw .data and .rodata bytes match, including the automatic tables before relocation. .rodata, .sdata, .sdata2 and .sbss have objdiff scores of 100%. .data remains 18.050066%.

Relocations normalized to target section and symbol-relative offset leave 120 .data differences, all targeting CHANSVmStep switch blocks. The two CHANSVmGetEnumedType discrepancies and all .rodata discrepancies are resolved. Symbol-name aliases at the same section/offset were distinguished from these real differences; no symbol metadata was edited.

The source .sdata/.sbss section extents are 593/12 bytes versus target 600/16, with target trailing alignment zeros; objdiff scores both 100%. No padding was introduced.

VmBlobFill has identical raw bytes but gate/ctxdiff normalize two CR1 conditional branches to different absolute addresses. The tool result is reported unchanged; the authoritative gate count remains 205, while objdiff counts 206.

The HMAC context is an existing opaque byte buffer. Its precise type/layout is unknown; no alignment member, padding, register coercion or replacement structure was invented.

CHANSVmGetSourceLine still appears to resolve offsets from the selected entry instead of the table base. The table-base experiments did not reach an exact match and were restored. VmBlobCopyRangeFrom bounds also remain questionable; corrected-range experiments were restored because they did not match.

## Attempts

131 recorded experiments (six compiler failures). Every baseline non-matching function and VmBlobFill has at least three distinct compiling source-level variations. Failed C89 declaration placement and pointer-type experiments were restored. The temporary hex-loop variant that omitted cursor advancement, the signed conversion-length clamp and the signed snprintf-bound experiment were discarded and excluded from the three-attempt minimum. Exploratory whole-function rewrites were restored before the retained changes. An interrupted decimal-accumulation experiment was restored and rerun successfully.

### VmBlobCalcRangeMD5Digest

- derive input pointer at update call: 90.515465%; instructions 96/97, differing positions 26; restored.
- scope result object and digest together: 99.793816%; instructions 97/97, differing positions 4; restored.
- use signed size for range validation: 91.85567%; instructions 102/97, differing positions 76; restored.
- declare and initialize result in success branch: 99.793816%; instructions 97/97, differing positions 4; restored.
- scope digest with input pointer after range validation: 99.793816%; instructions 97/97, differing positions 4; restored.
- remaining bytes as named unsigned bound: 99.793816%; instructions 97/97, differing positions 4; restored.
- declare digest before range arguments: 99.793816%; instructions 97/97, differing positions 4; restored.
- declare input data and digest before range arguments: 100.0%; instructions 97/97, differing positions 0; temporarily retained during iteration.

### VmBlobCalcRangeHMAC

- derive input pointer at update call: 85.411766%; instructions 118/119, differing positions 32; restored.
- scope result object and digest together: 99.890755%; instructions 119/119, differing positions 5; restored.
- use signed size for range validation: 93.0%; instructions 124/119, differing positions 88; restored.
- hash context declared before range offset: 99.72269%; instructions 119/119, differing positions 9; restored.
- digest declared after result object with outer hash context: 99.890755%; instructions 119/119, differing positions 5; restored.
- declare digest after the data pointer: 99.890755%; instructions 119/119, differing positions 5; restored.
- input and digest declared before range arguments: 99.97479%; instructions 119/119, differing positions 3; restored.
- output object and digest before range arguments: 99.890755%; instructions 119/119, differing positions 5; restored.
- declare context and offset in method scope: did not compile; restored.
- retain input and digest declarations before conversions: 99.97479%; instructions 119/119, differing positions 3; temporarily retained during iteration.

### vmBlobParsePackFormatString

- decimal digit before accumulation: 99.69827%; instructions 116/116, differing positions 6; restored.
- character-sized current character: 99.69827%; instructions 116/116, differing positions 6; restored.
- decimal digit before accumulation: 99.69827%; instructions 116/116, differing positions 6; restored.
- character-sized current character: 99.69827%; instructions 116/116, differing positions 6; restored.
- accumulator multiply then add: 99.784485%; instructions 116/116, differing positions 5; restored.

### VmWinEmuWrite

- offset progression in loop clause: 99.62687%; instructions 67/67, differing positions 5; restored.
- reverse declarations of conversion lengths: 99.55224%; instructions 67/67, differing positions 10; restored.
- bounded input length assigned separately: 87.82089%; instructions 67/67, differing positions 13; restored.
- clamp unsigned remaining count before division: 96.343285%; instructions 68/67, differing positions 41; restored.

### VmBlobCalcHMAC

- inline source size into update: 96.859375%; instructions 63/64, differing positions 31; restored.
- order data load before size load: 99.265625%; instructions 64/64, differing positions 11; restored.
- read input data directly at update: 96.953125%; instructions 63/64, differing positions 30; restored.
- shorten native key object lifetime: 99.4375%; instructions 64/64, differing positions 12; restored.
- declare output object beside key object: 99.609375%; instructions 64/64, differing positions 5; restored.
- declare digest before initial key lookup: 99.4375%; instructions 64/64, differing positions 12; restored.
- input and digest declared before native key lookup: 99.4375%; instructions 64/64, differing positions 12; restored.
- output object then data declarations before key lookup: 99.046875%; instructions 64/64, differing positions 17; restored.
- input size and digest declarations before key lookup: 99.4375%; instructions 64/64, differing positions 12; restored.

### VmStringFromCharCode

- increment character before byte offset: 99.40678%; instructions 59/59, differing positions 6; restored.
- for-loop index progression: 99.40678%; instructions 59/59, differing positions 6; restored.
- compute destination offset from character index: 95.0%; instructions 60/59, differing positions 39; restored.

### CHANSVmNewObjData

- explicit wrap branch: 84.114586%; instructions 98/96, differing positions 52; restored.
- chunk number shift: 99.375%; instructions 96/96, differing positions 11; restored.
- allocation byte count before chunk pointer: 99.375%; instructions 96/96, differing positions 11; restored.

### CHANSVmAddExe

- clear module memory in typed extent: 97.75197%; instructions 254/254, differing positions 44; restored.
- advance free-executable pointer via module end: 97.68898%; instructions 253/254, differing positions 227; restored.
- calculate aligned line table count with shift: 99.1063%; instructions 254/254, differing positions 35; restored.

### VmImageCtor

- name validated image data: 99.0%; instructions 25/25, differing positions 4; restored.
- declare callback return after image: 99.0%; instructions 25/25, differing positions 4; restored.
- return directly after validation: 61.4%; instructions 17/25, differing positions 25; restored.

### VmBlobGetHexString

- combine blob input address and cursor: 98.57317%; instructions 82/82, differing positions 16; restored.
- write low hex nibble after first index: 92.86585%; instructions 78/82, differing positions 38; restored.
- increment hex output cursor at loop end: 96.15854%; instructions 81/82, differing positions 34; restored.
- increment hex cursor before source advance: 96.15854%; instructions 81/82, differing positions 34; restored.

### CHANSVmLinkModules

- dispatch entry by const pointer: did not compile; restored.
- read dispatch entry fields through typed pointer: 94.25926%; instructions 189/189, differing positions 52; restored.
- scope each native index loop: did not compile; restored.
- explicit named table record fields: did not compile; restored.
- move module index increment into while condition: 98.677246%; instructions 189/189, differing positions 43; restored.
- copy dispatch record after local declarations: 98.677246%; instructions 189/189, differing positions 43; restored.

### CHANSVm_8145049C

- derive half work size from private VM: 97.65429%; instructions 431/431, differing positions 44; restored.
- scope format pointer with its buffer: 98.58237%; instructions 431/431, differing positions 42; restored.
- signed escaped flag: 98.58237%; instructions 431/431, differing positions 42; restored.

### CHANSVmStrCpyToU16FromU8

- promote loaded source character: 98.46154%; instructions 13/13, differing positions 3; restored.
- load character before destination offset: 98.46154%; instructions 13/13, differing positions 3; restored.
- use decrement in loop control: 98.46154%; instructions 13/13, differing positions 3; restored.
- loaded character in function scope: 97.69231%; instructions 13/13, differing positions 4; restored.
- destination offset in function scope: 98.46154%; instructions 13/13, differing positions 3; restored.
- both character and destination offset in function scope: 97.69231%; instructions 13/13, differing positions 4; restored.

### CHANSVmGetSourceLine

- resolve line data from table origin: 97.82609%; instructions 46/46, differing positions 16; restored.
- cache table origin for bounds and data: 97.82609%; instructions 46/46, differing positions 16; restored.
- cache program offset for bit count: 97.82609%; instructions 46/46, differing positions 16; restored.
- explicit module and table validation: 78.58696%; instructions 54/46, differing positions 52; temporarily retained during iteration.
- compute byte loop bound before entry: 79.347824%; instructions 54/46, differing positions 52; temporarily retained during iteration.
- unsigned base-line accumulator: 79.347824%; instructions 54/46, differing positions 52; temporarily retained during iteration.
- chained validation with cached references: 96.847824%; instructions 46/46, differing positions 21; temporarily retained during iteration.

### CHANSVm_81450D14

- add size before signed value: 97.391304%; instructions 45/46, differing positions 29; restored.
- negative range rejection first: 70.978264%; instructions 45/46, differing positions 29; restored.
- positive range checked in nested branches: 97.391304%; instructions 45/46, differing positions 29; restored.
- positive range jumps to common store: 97.391304%; instructions 45/46, differing positions 29; restored.
- nested positive range reaches common store: 97.391304%; instructions 45/46, differing positions 29; restored.
- signed low word adjusted for output: 97.391304%; instructions 45/46, differing positions 29; restored.

### VmStringReplace

- load parent pointer before parent length: 97.106064%; instructions 132/132, differing positions 53; restored.
- cache argument conversion in nested call: 97.106064%; instructions 132/132, differing positions 53; restored.
- count offsets as signed values: 97.106064%; instructions 132/132, differing positions 53; restored.

### CHANSVm_8144B4D4

- ordinary parsed end pointer: 96.92771%; instructions 83/83, differing positions 13; restored.
- for-loop keyword lookup: 96.92771%; instructions 83/83, differing positions 13; restored.
- unsigned keyword source type: 96.92771%; instructions 83/83, differing positions 13; restored.

### VmCallMethod

- initialize accumulator pointer at declaration: 96.565834%; instructions 279/281, differing positions 228; restored.
- initialize native target before call state: 96.565834%; instructions 279/281, differing positions 228; restored.
- declare stack sizes separately: 96.565834%; instructions 279/281, differing positions 228; restored.

### VmBlobCalcRangeSHA1Digest

- digest pointer declaration before context: 96.484535%; instructions 97/97, differing positions 14; restored.
- derive update input directly: 87.206184%; instructions 96/97, differing positions 36; restored.
- signed range size: 89.26804%; instructions 102/97, differing positions 76; restored.
- input and digest declared before argument conversion: 96.69072%; instructions 97/97, differing positions 10; restored.

### VmArraySlice

- positive slice length conditional: 92.06767%; instructions 131/133, differing positions 106; restored.
- cache negative start as signed offset: 96.2782%; instructions 133/133, differing positions 56; restored.
- end clipping before start clipping: 96.2782%; instructions 133/133, differing positions 56; restored.

### VmStringSplit

- combined delimiter conversion: 96.04955%; instructions 222/222, differing positions 81; restored.
- explicit boolean count result: 96.04955%; instructions 222/222, differing positions 81; restored.
- signed output limit: 96.04955%; instructions 222/222, differing positions 81; restored.

### VmDateDtor

- direct calendar address instead of pointer: 94.96703%; instructions 91/91, differing positions 7; restored.
- signed formatting return converted at bound: 94.30769%; instructions 91/91, differing positions 8; restored.
- inline calendar field access: 89.14286%; instructions 90/91, differing positions 85; restored.
- load calendar month before day at formatting: 94.96703%; instructions 91/91, differing positions 7; restored.
- load calendar day separately: 94.96703%; instructions 91/91, differing positions 7; restored.
- format result uses unsigned bound: 94.96703%; instructions 91/91, differing positions 7; restored.

### CHANSVmStep

- initialize interpreter private state at declaration: 94.7901%; instructions 1249/1253, differing positions 1173; restored.
- use pointer indexing for opcode load: 94.7901%; instructions 1249/1253, differing positions 1173; restored.
- use unsigned operation byte: 94.56265%; instructions 1249/1253, differing positions 1173; restored.

### CHANSVmParseInt

- buffer terminator through end pointer: 94.69388%; instructions 49/49, differing positions 3; restored.
- separate end and result declarations: 94.69388%; instructions 49/49, differing positions 3; restored.
- source length loaded after type validation: 94.69388%; instructions 49/49, differing positions 3; restored.
- initialize parsed end before source type: 83.67347%; instructions 49/49, differing positions 5; restored.
- assign cached source type after end initialization: 83.67347%; instructions 49/49, differing positions 5; restored.
- null parse cursor initializer: 94.69388%; instructions 49/49, differing positions 3; restored.

### CHANSVm_81455654

- shared result across module local and argument branches: did not compile; restored.
- argument branch before frame header branch: did not compile; restored.
- extract signed frame displacement inline: 94.0%; instructions 34/35, differing positions 35; restored.
- typed module lookup with shared return: 67.14286%; instructions 33/35, differing positions 23; restored.
- typed lookup with argument branch before headers: 88.28571%; instructions 33/35, differing positions 18; restored.

### VmBlobPackCommon

- combine argument count and format start assignments: 92.588326%; instructions 675/668, differing positions 644; restored.
- use shift for UTF16 format count: 92.603294%; instructions 675/668, differing positions 642; restored.
- scope packed words before format return fields: 92.603294%; instructions 675/668, differing positions 642; restored.

### VmBlobUnpack

- remove redundant buffer base alias: 92.083176%; instructions 531/517, differing positions 496; restored.
- scope format result declarations in storage order: 92.083176%; instructions 531/517, differing positions 496; restored.
- unsigned output parameter flag type: 92.083176%; instructions 531/517, differing positions 496; restored.

### VmBlobCopyRangeFrom

- destination remaining validates count: 91.382355%; instructions 139/136, differing positions 71; restored.
- validate upper bounds for both source and destination: 91.52941%; instructions 139/136, differing positions 71; restored.
- separate available byte values and shared validation: 91.52941%; instructions 139/136, differing positions 71; restored.

### VmBlobFill

- explicit integer conversion type: 100.0%; instructions 63/63, differing positions 2; restored.
- size type count declaration: 100.0%; instructions 63/63, differing positions 2; restored.
- direct length after validated header: 91.74603%; instructions 60/63, differing positions 43; restored.

## Final full gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/channelScript/CHANSVm] pool: IDENTICAL
[src/channelScript/CHANSVm] objdiff: code 32348/53564 data 2232/6904 functions 206/233 fuzzy 98.3128 linked code 0
[src/channelScript/CHANSVm] instruction-exact functions: 205/233
[src/channelScript/CHANSVm]   section .data size 4672 match 18.050066
[src/channelScript/CHANSVm]   section .rodata size 1432 match 100.0
[src/channelScript/CHANSVm]   section .sbss size 16 match 100.0
[src/channelScript/CHANSVm]   section .sdata size 600 match 100.0
[src/channelScript/CHANSVm]   section .sdata2 size 184 match 100.0
[src/channelScript/CHANSVm]   section .text size 53564 match 98.31282
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
[src/channelScript/CHANSVm]   below 100: VmCallMethod 96.565834
[src/channelScript/CHANSVm]   below 100: CHANSVmStep 94.7901
[src/channelScript/CHANSVm] baseline: code 31960/53564 data 800 functions 205 fuzzy 98.3091
regressions vs baseline: 0
global matched_code_percent: 72.27324 -> 72.28620
global fuzzy_match_percent: 81.01270 -> 81.01278
global complete_code_percent: 56.76068 -> 56.76068
global matched_data_percent: 86.19839 -> 86.27652
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
