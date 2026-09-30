# CHANSVm fourth continuation

Baseline: 42647c75, instruction-exact 205/233, objdiff functions 206/233, code 32348/53564, data 2232/6904.

Result: instruction-exact 206/233, objdiff functions 207/233, code 32400/53564, data 2232/6904.

## Retained changes

- CHANSVmStrCpyToU16FromU8: use a byte destination pointer for the two widening stores. 13/13 instructions, diffs 0.
- CHANSVmGetSourceLine: decode line bytes relative to the line table, as in the target, rather than relative to the selected entry. 97.71739% to 97.82609%.
- CHANSVmNewObjData: failed chunk allocation follows the target cleanup path through the zero offset. 99.375% to 99.427086%.
- VmCallMethod: read method identifier from instruction bytes one and two with the existing big-endian helper. The old halfword access read bytes two and three. 96.565834% to 97.2242%; 279/281 to 281/281 instructions.
- VmBlobCopyRangeFrom: require a nonnegative count and sufficient bytes remaining in each blob; retain distinct destination and source validation state. 91.67647% to 93.492645%.
- CHANSVmStep: equality uses the equality conversion table; string deletion status and array creation status propagate through the target joins; failed array expansion returns its error. 94.7901% to 94.81804%; 1249/1253 to 1252/1253 instructions.

## Remaining functions

CHANSVmGetSourceLine, 97.82609%, line-table origin fixed; register allocation remains.
CHANSVmNewObjData, 99.427086%, allocation-failure cleanup fixed; ten register differences remain.
CHANSVmParseInt, 94.69388%, three instruction scheduling differences.
CHANSVm_8144B4D4, 96.92771%, register allocation and parse-end initialization scheduling.
VmArraySlice, 96.2782%, signed index clipping, branch layout and register allocation.
VmDateDtor, 94.96703%, seven argument-load scheduling differences.
VmStringFromCharCode, 99.40678%, six register differences.
VmStringReplace, 97.106064%, string field-load scheduling and register allocation.
VmStringSplit, 96.04955%, register allocation, scheduling and branch operands.
CHANSVm_8145049C, 98.58237%, character/string formatting paths, scheduling and register allocation.
CHANSVm_81450D14, 97.391304%, one missing branch and addition operand order; 45/46 instructions.
VmBlobCopyRangeFrom, 93.492645%, range predicates fixed; register allocation and scheduling, 139/136 instructions.
VmBlobGetHexString, 98.71951%, fourteen register differences.
VmBlobCalcRangeSHA1Digest, 96.484535%, range-check scheduling and register allocation.
VmBlobCalcHMAC, 99.453125%, seven register differences.
VmBlobCalcRangeHMAC, 99.97479%, three context-address differences: stack +0x0c versus +0x10; context layout unresolved.
vmBlobParsePackFormatString, 99.69827%, decimal accumulator register allocation.
VmBlobPackCommon, 92.603294%, stack layout and control flow, 675/668 instructions.
VmBlobUnpack, 92.083176%, control flow and register allocation, 531/517 instructions.
VmImageCtor, 99.0%, four register differences.
VmWinEmuWrite, 99.62687%, five register differences.
CHANSVmAddExe, 99.1063%, register allocation, relocation-loop scheduling and addition operands.
CHANSVm_81455654, 94.0%, missing initial null-result instruction, 34/35 instructions.
CHANSVmLinkModules, 98.677246%, register allocation and dispatch traversal scheduling.
VmCallMethod, 97.2242%, operand bytes fixed; register allocation and scheduling, 281/281 instructions.
CHANSVmStep, 94.81804%, stack layout, register allocation and interpreter branches, 1252/1253 instructions.
VmBlobFill, 100.0%, objdiff 100%, raw 252 bytes identical; ctxdiff/gate report two CR1 branch differences after address normalization.

## Data audit and uncertainty

Pool: all 125 strings identical and in target order. .rodata, .sdata, .sdata2 and .sbss score 100%. .data scores 18.050066%. Its 4672 raw bytes are identical, but 108 canonical relocation destinations still differ, all inside CHANSVmStep jump tables (120 at baseline). The retained interpreter changes fix twelve destinations naturally. No manual table addresses or padding were added.

.rodata has identical 1432 raw bytes and zero canonical relocation differences; .sdata2 has identical 184 raw bytes and zero canonical relocation differences. .sdata and .sbss have trailing target alignment space (593/600 and 12/16 raw bytes) and already score 100%; no dummy storage added. String-symbol aliases resolve to the same section offsets.

VmBlobCalcRangeHMAC context placement remains unresolved. VmBlobFill is byte-identical and scores 100% in objdiff, but two CR1 branch operands differ in the address-normalized instruction checker. Tooling was not changed and this function is not claimed instruction-exact.

## Attempt log

92 recorded trials: 87 compiled, five failed compilation and were restored. The unused-input trial noted below is excluded from the three-attempt minimum. Every remaining function has at least three distinct compiling source-level trials. Kept below means retained at that point in the experiment sequence; the retained-change list above describes the final source.

### VmBlobCalcRangeHMAC

- scope hash context next to checked range state: 99.97479%; 119/119 instructions; 3 positional diffs; restored.
- declare range offset after context in method scope: 99.97479%; 119/119 instructions; 3 positional diffs; restored.
- byte input declared after context and output: 99.72269%; 119/119 instructions; 9 positional diffs; restored.

### vmBlobParsePackFormatString

- scope current parameter character with numeric accumulator: 98.06035%; 117/116 instructions; 40 positional diffs; restored.
- declare parameter accumulator before decoded character: 98.534485%; 116/116 instructions; 32 positional diffs; restored.
- accumulate signed decoded decimal digit: 99.69827%; 116/116 instructions; 6 positional diffs; restored.

### VmWinEmuWrite

- declare lengths before string conversion result: 99.17911%; 67/67 instructions; 8 positional diffs; restored.
- declare output buffer before string state: 99.62687%; 67/67 instructions; 5 positional diffs; restored.
- decode string payload in local scope: 99.62687%; 67/67 instructions; 5 positional diffs; restored; unused input temporary, excluded from required attempts.
- use named Unicode input pointer in conversion: 74.61194%; 67/67 instructions; 16 positional diffs; restored.

### VmBlobCalcHMAC

- scope output byte pointers before context: 99.140625%; 64/64 instructions; 11 positional diffs; restored.
- output header declared before source blob: 99.90625%; 64/64 instructions; 6 positional diffs; restored.
- context placed after result header and before input bytes: 99.609375%; 64/64 instructions; 5 positional diffs; restored.

### VmStringFromCharCode

- name character mask before loop counters: 99.40678%; 59/59 instructions; 6 positional diffs; restored.
- declare index before byte cursor: 98.72881%; 59/59 instructions; 12 positional diffs; restored.
- declare byte cursor before converted argument: 99.40678%; 59/59 instructions; 6 positional diffs; restored.

### CHANSVmNewObjData

- allocation failure shares exhausted-chunk cleanup: 99.427086%; 96/96 instructions; 10 positional diffs; kept at this point.
- track chunk slot through typed pointer: 99.427086%; 96/96 instructions; 10 positional diffs; restored.
- declare chunk scan index after entry cursor: 99.427086%; 96/96 instructions; 10 positional diffs; restored.

### CHANSVmAddExe

- use typed module element during initialization: 99.15354%; 254/254 instructions; 34 positional diffs; restored.
- calculate dispatch string end with pointer addition: 97.86614%; 253/254 instructions; 89 positional diffs; restored.
- use typed line-table entry size: 99.1063%; 254/254 instructions; 35 positional diffs; restored.

### VmImageCtor

- reference image header through local typed pointer: 99.0%; 25/25 instructions; 4 positional diffs; restored.
- hold image data in condition initializer scope: 99.0%; 25/25 instructions; 4 positional diffs; restored.
- return status through signed integer local: 99.0%; 25/25 instructions; 4 positional diffs; restored.

### VmBlobGetHexString

- declare byte input before destination pointer: compile failed; restored; #   (10141) expression syntax error.
- derive second output index from first output cursor: 98.71951%; 82/82 instructions; 14 positional diffs; restored.
- name high nibble before output writes: 98.71951%; 82/82 instructions; 14 positional diffs; restored.
- read byte input before extracting output payload: 94.560974%; 82/82 instructions; 27 positional diffs; restored.

### CHANSVmLinkModules

- retain dispatch pointer beside module iterator: 98.783066%; 189/189 instructions; 40 positional diffs; restored.
- declare traversal pointers before pass result: 98.677246%; 189/189 instructions; 43 positional diffs; restored.
- advance module traversal in for-loop increment: 98.677246%; 189/189 instructions; 43 positional diffs; restored.

### CHANSVm_8145049C

- format argument counter declared before formatting buffers: compile failed; restored; #   (10333) object 'argIdxCounter' redefined.
- output byte pointer declared before format buffers: 96.37819%; 431/431 instructions; 159 positional diffs; restored.
- work byte pointer declared alongside VM state: 98.14153%; 431/431 instructions; 74 positional diffs; restored.
- declare argument counter before format buffers without duplication: 98.28074%; 431/431 instructions; 63 positional diffs; restored.

### CHANSVmStrCpyToU16FromU8

- compute byte destination pointer for both stores: 100.0%; 13/13 instructions; 0 positional diffs; kept at this point.
- advance byte destination from end to start: compile failed; restored; #   (10141) expression syntax error.

### CHANSVmGetSourceLine

- use table origin and cached byte position bound: 97.391304%; 46/46 instructions; 20 positional diffs; kept at this point.
- declare decoded line offset after byte bitmap pointer: 97.391304%; 46/46 instructions; 20 positional diffs; restored.
- name bit mask and keep loop bound as unsigned word: 97.82609%; 46/46 instructions; 18 positional diffs; restored.
- resolve table-relative line data without byte-bound temporary: 97.82609%; 46/46 instructions; 16 positional diffs; kept at this point.

### CHANSVm_81450D14

- explicit positive and negative normalization branches: 89.565216%; 50/46 instructions; 33 positional diffs; restored.
- branch to validation result after nonnegative bounds: 97.391304%; 45/46 instructions; 29 positional diffs; restored.
- use wider unsigned sum after relative offset validation: 97.391304%; 45/46 instructions; 29 positional diffs; restored.

### VmStringReplace

- declare destination string before source argument objects: 96.5%; 132/132 instructions; 64 positional diffs; restored.
- use explicit source scan loop control: 97.106064%; 132/132 instructions; 53 positional diffs; restored.
- use direct destination clipping with local size: 97.106064%; 132/132 instructions; 53 positional diffs; restored.

### CHANSVm_8144B4D4

- parsed end pointer in character pointer form: 96.92771%; 83/83 instructions; 13 positional diffs; restored.
- declare parsed float before output object: 96.92771%; 83/83 instructions; 13 positional diffs; restored.
- initialize keyword scan in loop clause: 96.92771%; 83/83 instructions; 13 positional diffs; restored.

### CHANSVmStep

- use equality conversion matrix for equality operators: 94.7901%; 1249/1253 instructions; 1173 positional diffs; kept at this point.
- retain string deletion result and reload active module field: 94.79489%; 1251/1253 instructions; 1153 positional diffs; kept at this point.
- check new-array expansion result before returning value: 94.603355%; 1256/1253 instructions; 1178 positional diffs; kept at this point.
- new-array status joins helper results before opcode result: 94.81804%; 1252/1253 instructions; 1032 positional diffs; kept at this point.

### VmCallMethod

- decode method identifier from opcode bytes one and two: compile failed; restored; #   (10140) undefined identifier 'pConstObj'.
- declare native callback before context and return state: 96.33452%; 279/281 instructions; 230 positional diffs; restored.
- declare argument frame counts before return status: 96.88612%; 279/281 instructions; 219 positional diffs; restored.
- decode method identifier with typed instruction byte stream: 97.2242%; 281/281 instructions; 97 positional diffs; kept at this point.

### VmBlobCalcRangeSHA1Digest

- declare output header before range conversion state: 96.484535%; 97/97 instructions; 14 positional diffs; restored.
- place byte pointers and header before input blob: 96.69072%; 97/97 instructions; 10 positional diffs; restored.
- derive hash input before constructing output blob: 70.24742%; 97/97 instructions; 29 positional diffs; restored.

### VmArraySlice

- scope negative end relative to array length: 96.2782%; 133/133 instructions; 56 positional diffs; restored.
- destination element declared after source element: 96.2782%; 133/133 instructions; 56 positional diffs; restored.
- iterate array copy with remaining count: 94.586464%; 134/133 instructions; 84 positional diffs; restored.

### VmStringSplit

- array result declared before separator argument state: 96.04955%; 222/222 instructions; 81 positional diffs; restored.
- declare source text next to source byte length: 95.98198%; 222/222 instructions; 84 positional diffs; restored.
- split segment count declaration follows output count: 96.04955%; 222/222 instructions; 81 positional diffs; restored.

### VmDateDtor

- format month pointer declared after calendar fields: 94.96703%; 91/91 instructions; 7 positional diffs; restored.
- declare calendar before text buffer: 94.96703%; 91/91 instructions; 7 positional diffs; restored.
- use size type for formatted character count: 94.96703%; 91/91 instructions; 7 positional diffs; restored.

### CHANSVmParseInt

- initialize end pointer through buffer conversion scope: 78.44898%; 49/49 instructions; 33 positional diffs; restored.
- declare parse output pointer before byte buffer: 94.69388%; 49/49 instructions; 3 positional diffs; restored.
- normalize empty parse by conditional expression: 84.79592%; 50/49 instructions; 26 positional diffs; restored.

### VmBlobCopyRangeFrom

- validate both bounds with separate source validity result: 91.52941%; 139/136 instructions; 71 positional diffs; kept at this point.
- combine each signed count and available range predicate: compile failed; restored; #   (10141) expression syntax error.
- declare copy result before requested byte count: 91.52941%; 139/136 instructions; 71 positional diffs; restored.
- compute independent available counts before range predicates: 90.911766%; 138/136 instructions; 69 positional diffs; restored.
- inline both predicates with cached range origins: 93.492645%; 139/136 instructions; 72 positional diffs; kept at this point.
- range flags use logical comparisons directly: 85.84559%; 147/136 instructions; 80 positional diffs; restored.

### CHANSVm_81455654

- scope argument result pointer in argument branch: 94.0%; 34/35 instructions; 35 positional diffs; restored.
- place result declaration after active module retrieval: 94.0%; 34/35 instructions; 35 positional diffs; restored.
- read global result through typed module entry field: 91.71429%; 34/35 instructions; 35 positional diffs; restored.

### VmBlobPackCommon

- format and array objects declared before parent blob: 92.655685%; 675/668 instructions; 637 positional diffs; restored.
- name argument count from active execution context: 91.949104%; 675/668 instructions; 642 positional diffs; restored.
- initialize format result count after type and size: 92.59281%; 675/668 instructions; 644 positional diffs; restored.

### VmBlobUnpack

- declare word buffer before blob parse state: 92.083176%; 531/517 instructions; 496 positional diffs; restored.
- decode UTF16 format count by division: 92.083176%; 531/517 instructions; 496 positional diffs; restored.
- format decoder results initialized at declarations: 92.083176%; 531/517 instructions; 496 positional diffs; restored.

### VmBlobFill

- declare byte count before converted arguments: 100.0%; 63/63 instructions; 2 positional diffs; restored.
- native fill value masked to one byte explicitly: 100.0%; 63/63 instructions; 2 positional diffs; restored.
- scope actual write buffer beside fill operation: 100.0%; 63/63 instructions; 2 positional diffs; restored.

## Final full gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/channelScript/CHANSVm] pool: IDENTICAL
[src/channelScript/CHANSVm] objdiff: code 32400/53564 data 2232/6904 functions 207/233 fuzzy 98.3499 linked code 0
[src/channelScript/CHANSVm] instruction-exact functions: 206/233
[src/channelScript/CHANSVm]   section .data size 4672 match 18.050066
[src/channelScript/CHANSVm]   section .rodata size 1432 match 100.0
[src/channelScript/CHANSVm]   section .sbss size 16 match 100.0
[src/channelScript/CHANSVm]   section .sdata size 600 match 100.0
[src/channelScript/CHANSVm]   section .sdata2 size 184 match 100.0
[src/channelScript/CHANSVm]   section .text size 53564 match 98.34994
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
[src/channelScript/CHANSVm]   below 100: VmBlobCopyRangeFrom 93.492645
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
[src/channelScript/CHANSVm]   below 100: CHANSVmStep 94.81804
[src/channelScript/CHANSVm] baseline: code 32348/53564 data 2232 functions 206 fuzzy 98.3128
regressions vs baseline: 0
global matched_code_percent: 72.37634 -> 72.37808
global fuzzy_match_percent: 81.02148 -> 81.02215
global complete_code_percent: 56.76068 -> 56.76068
global matched_data_percent: 86.27652 -> 86.27652
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
