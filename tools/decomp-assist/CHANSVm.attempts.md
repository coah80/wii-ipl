# CHANSVm attempt log

43U only. Baseline: 201/233 instruction-exact, 202/233 objdiff-matched, code 30984/53564 bytes, data 16/6904 bytes. The original string pool has 125 strings and matches the initial source pool.

Each experiment rebuilt only CHANSVm.o, regenerated objdiff, compared instruction counts and instruction operands, and checked previously matched functions in this unit. Unaccepted experiments were restored. No shared headers or other source units changed.

Accepted source changes: VmDateGetRTC preserves the 64-bit subtraction mask; VmStringSplice expresses the clipped result length with a conditional. vmNoError and vmUnknownError are character arrays, matching the original symbol sizes 12 and 10, rather than pointers. Their writable array definitions preserve the pool; const arrays moved their text into .rodata and regressed CHANSVmInit, so that variant was restored.

A CalcRangeMD5Digest experiment reached zero instruction differences by reusing an object pointer for byte data. It was discarded because that pointer reuse was less readable than the existing code. Its later exact variants were discarded with it.

VmBlobFill has 100% objdiff but two raw conditional-branch operand differences in the baseline. The same discrepancy remains; it is included below.

## CHANSVmGetSourceLine

- use lineData once for bounds and read: did not compile, C89 declaration placement; restored. A corrected compiling variant is recorded separately.
- reverse entry and offset addition: 97.71739%; instructions 46/46, differing instruction positions 16; restored.
- while loop with explicit increment: 97.71739%; instructions 46/46, differing instruction positions 16; restored.
- hoist lineData declaration and common address: 97.71739%; instructions 46/46, differing instruction positions 16; restored.
- source line offsets relative to line table base: 97.82609%; instructions 46/46, differing instruction positions 16; restored.
- cache module and line table with base relative offsets: 97.391304%; instructions 46/46, differing instruction positions 17; restored.

## CHANSVmNewObjData

- allocation failure returns null immediately: 97.239586%; instructions 98/96, differing instruction positions 69; restored.
- chunk scan for loop: 99.375%; instructions 96/96, differing instruction positions 11; restored.
- inner entry scan for loop: 99.375%; instructions 96/96, differing instruction positions 11; restored.
- all failure paths return directly: 92.135414%; instructions 102/96, differing instruction positions 90; restored.

## CHANSVmStrCpyToU16FromU8

- reassign source argument at end: did not compile, C89 declaration placement; restored. A corrected compiling variant is recorded separately.
- assign length byte offset and use loop counter: 81.92308%; instructions 13/13, differing instruction positions 6; restored.
- pointer destination reverse walk: 97.30769%; instructions 13/13, differing instruction positions 5; restored.
- reuse input argument after declarations: 80.76923%; instructions 13/13, differing instruction positions 7; restored.
- initialize byte offset before source pointer: 81.53846%; instructions 13/13, differing instruction positions 7; restored.
- set output high byte before low byte: 67.69231%; instructions 13/13, differing instruction positions 6; restored.

## CHANSVmParseInt

- initialize end pointer in declaration: 94.69388%; instructions 49/49, differing instruction positions 3; restored.
- initialize end pointer before type load: 83.67347%; instructions 49/49, differing instruction positions 5; restored.
- direct object type comparison: 83.67347%; instructions 49/49, differing instruction positions 5; restored.
- zero parsing end pointer with memset: 77.02041%; instructions 53/49, differing instruction positions 51; restored.
- scope end pointer with parsing buffer: 87.755104%; instructions 49/49, differing instruction positions 6; restored.
- split number and end pointer initialization in parsing call scope: 78.44898%; instructions 49/49, differing instruction positions 33; restored.

## CHANSVm_8144B4D4

- ordinary char end pointer for strtod: 96.92771%; instructions 83/83, differing instruction positions 13; restored.
- initialize end pointer before object allocation: 94.518074%; instructions 83/83, differing instruction positions 20; restored.
- direct object type test: 94.518074%; instructions 83/83, differing instruction positions 13; restored.

## VmArrayExpandCommon

- separate capacity and element byte offset: 98.70588%; instructions 85/85, differing instruction positions 17; restored.
- declare chunk before capacity: 99.35294%; instructions 85/85, differing instruction positions 8; restored.
- inline allocation size expression: 99.35294%; instructions 85/85, differing instruction positions 8; restored.

## VmArraySlice

- mutable signed start and end indexes: 95.75188%; instructions 133/133, differing instruction positions 65; restored.
- initialize end beside length: 94.172935%; instructions 132/133, differing instruction positions 93; restored.
- loop index while form: 96.2782%; instructions 133/133, differing instruction positions 56; restored.

## VmDateDtor

- load month name before snprintf: 94.96703%; instructions 91/91, differing instruction positions 7; restored.
- load day then month into local names: 94.96703%; instructions 91/91, differing instruction positions 7; restored.
- use date aggregate fields for formatting: 82.12088%; instructions 97/91, differing instruction positions 80; restored.

## VmDateGetRTC

- explicit unsigned integer result mask: 100.0%; instructions 38/38, differing instruction positions 0; retained during iteration.
- cast seconds before subtracting bias: 100.0%; instructions 38/38, differing instruction positions 0; retained during iteration.
- signed seconds temporary: 83.947365%; instructions 38/38, differing instruction positions 5; restored.
- remove obsolete narrowed result local: 100.0%; instructions 38/38, differing instruction positions 0; retained during iteration.

## VmStringFromCharCode

- separate narrowed codepoint temporary: 94.32204%; instructions 57/59, differing instruction positions 45; restored.
- reverse offset and index update order: 99.40678%; instructions 59/59, differing instruction positions 6; restored.
- for loop with byte offset: 99.40678%; instructions 59/59, differing instruction positions 6; restored.

## VmStringReplace

- load search fields before parent fields: 97.257576%; instructions 132/132, differing instruction positions 52; restored.
- load parent pointer before lengths: 97.106064%; instructions 132/132, differing instruction positions 53; restored.
- cache parent and search value structures: 97.82576%; instructions 132/132, differing instruction positions 47; restored.

## VmStringSplice

- signed byte offsets update in place: 97.55372%; instructions 121/121, differing instruction positions 8; restored.
- conditional result length: 100.0%; instructions 121/121, differing instruction positions 0; retained during iteration.
- shift integer offsets to byte offsets: 100.0%; instructions 121/121, differing instruction positions 0; retained during iteration.
- retain multiplication for signed byte offsets: 100.0%; instructions 121/121, differing instruction positions 0; retained during iteration.

## VmStringSplit

- read parent and delimiter lengths first: 95.936935%; instructions 222/222, differing instruction positions 92; restored.
- read delimiter fields first: 95.96847%; instructions 222/222, differing instruction positions 90; restored.
- initialize array count in declaration: 96.04955%; instructions 222/222, differing instruction positions 81; restored.

## CHANSVm_8145049C

- use real wide character buffer for character format: 98.53133%; instructions 431/431, differing instruction positions 62; restored.
- load source and destination string data before memcpy: did not compile, C89 declaration placement; restored. A corrected compiling variant is recorded separately.
- initialize literal length before char buffer pointer: 98.58237%; instructions 431/431, differing instruction positions 42; restored.
- cache both string buffers within C89 block: 98.58237%; instructions 431/431, differing instruction positions 42; restored.

## CHANSVm_81450D14

- reverse bounds addition operands: 97.391304%; instructions 45/46, differing instruction positions 29; restored.
- explicit valid range branch: 97.391304%; instructions 45/46, differing instruction positions 29; restored.
- negative range validation early returns: 86.195656%; instructions 44/46, differing instruction positions 29; restored.

## VmBlobCopyRangeFrom

- correct both available range bounds from target: 91.52941%; instructions 139/136, differing instruction positions 71; restored.
- combine target range bounds: 93.80882%; instructions 138/136, differing instruction positions 50; restored.
- snapshot offsets for target bounds: 91.57353%; instructions 139/136, differing instruction positions 93; restored.

## VmBlobGetHexString

- load byte once per hexadecimal pair: 92.36585%; instructions 81/82, differing instruction positions 36; restored.
- merge byte and destination counters: 90.060974%; instructions 83/82, differing instruction positions 38; restored.
- direct pointer advancement for hex output: 88.53658%; instructions 77/82, differing instruction positions 40; restored.

## VmBlobCalcRangeSHA1Digest

- reuse argument header for digest object: 96.484535%; instructions 97/97, differing instruction positions 14; restored.
- declare output header before data and digest: 96.484535%; instructions 97/97, differing instruction positions 14; restored.
- form data pointer before creating digest object: 70.24742%; instructions 97/97, differing instruction positions 29; restored.
- reuse argument pointer for data buffer: 96.69072%; instructions 97/97, differing instruction positions 10; restored.
- cache range valid result in named boolean: 96.484535%; instructions 97/97, differing instruction positions 14; restored.

## VmBlobCalcRangeMD5Digest

- reuse argument header for digest object: 99.793816%; instructions 97/97, differing instruction positions 4; restored.
- declare output header before data and digest: 99.793816%; instructions 97/97, differing instruction positions 4; restored.
- form data pointer before creating digest object: 74.98969%; instructions 96/97, differing instruction positions 38; restored.
- reuse argument pointer for data buffer: 100.0%; instructions 97/97, differing instruction positions 0; later discarded for readability.
- cache range valid result in named boolean: 100.0%; instructions 97/97, differing instruction positions 0; later discarded for readability.
- reuse converted argument as new digest object: 99.793816%; instructions 97/97, differing instruction positions 4; restored.
- scope range data to digest block: 99.793816%; instructions 97/97, differing instruction positions 4; restored.
- scope digest pointer to allocation and hash block: 99.793816%; instructions 97/97, differing instruction positions 4; restored.
- use const byte pointer for hash input: 99.793816%; instructions 97/97, differing instruction positions 4; restored.

## VmBlobCalcHMAC

- reuse input argument for digest header: 99.90625%; instructions 64/64, differing instruction positions 6; restored.
- capture blob data before creating digest: 93.34375%; instructions 64/64, differing instruction positions 22; restored.
- declare key blob before initialized input header: 99.453125%; instructions 64/64, differing instruction positions 7; restored.

## VmBlobCalcRangeHMAC

- reuse argument header for output object: 99.890755%; instructions 119/119, differing instruction positions 5; restored.
- scope digest context for entire function: 99.72269%; instructions 119/119, differing instruction positions 9; restored.
- capture data pointer before digest creation: 75.56303%; instructions 118/119, differing instruction positions 75; restored.

## vmBlobParsePackFormatString

- accumulate decimal product before character add: 99.69827%; instructions 116/116, differing instruction positions 6; restored.
- use separate parameter character: 98.01724%; instructions 117/116, differing instruction positions 41; restored.
- unsigned digit temporary with explicit character truncation: 99.69827%; instructions 116/116, differing instruction positions 6; restored.

## VmBlobPackCommon

- initialize parser type before parser size: 92.61826%; instructions 679/668, differing instruction positions 668; restored.
- move parser output scalars into parsing scope: 92.621254%; instructions 675/668, differing instruction positions 638; restored.
- explicit source blob check before format scan: 92.603294%; instructions 675/668, differing instruction positions 642; restored.

## VmBlobUnpack

- initialize parser scalar outputs with constants: 92.083176%; instructions 531/517, differing instruction positions 496; restored.
- read format length before format pointer: 91.32108%; instructions 531/517, differing instruction positions 496; restored.
- validate source blob before converting format argument: 90.92263%; instructions 533/517, differing instruction positions 517; restored.

## VmImageCtor

- early true return for absent callback: 79.8%; instructions 25/25, differing instruction positions 15; restored.
- declare image before result: 99.0%; instructions 25/25, differing instruction positions 4; restored.
- return callback directly for valid image: 58.4%; instructions 17/25, differing instruction positions 25; restored.
- save image data pointer before callback test: 86.6%; instructions 25/25, differing instruction positions 8; restored.
- cache constructor callback before image lookup: 99.0%; instructions 25/25, differing instruction positions 4; restored.

## VmWinEmuWrite

- hoist input string value pointer: did not compile, incorrect guessed structure type; restored. A corrected compiling variant is recorded separately.
- initialize input and output lengths in reverse order: 90.67164%; instructions 67/67, differing instruction positions 12; restored.
- for loop over input chunks: 99.62687%; instructions 67/67, differing instruction positions 5; restored.
- cache correctly typed wide string structure: 96.1194%; instructions 65/67, differing instruction positions 54; restored.

## CHANSVmAddExe

- read header size before assigning module variable: 99.1063%; instructions 254/254, differing instruction positions 35; restored.
- split format magic and alignment validation: 99.1063%; instructions 254/254, differing instruction positions 35; restored.
- integer aligned size check: 99.1063%; instructions 254/254, differing instruction positions 35; restored.

## CHANSVm_81455654

- direct module offset assignment: 94.0%; instructions 34/35, differing instruction positions 35; restored.
- inline active context access: 94.0%; instructions 34/35, differing instruction positions 35; restored.
- early null return on negative frame index: 76.57143%; instructions 36/35, differing instruction positions 36; restored.
- separate result pointer from table pointer: 94.0%; instructions 34/35, differing instruction positions 35; restored.

## CHANSVmLinkModules

- for module traversal: 98.677246%; instructions 189/189, differing instruction positions 43; restored.
- remove copied dispatch entry in global pass: 94.25926%; instructions 189/189, differing instruction positions 52; restored.
- early return when linking blocked or no modules: 96.44974%; instructions 189/189, differing instruction positions 173; restored.

## VmCallMethod

- initialize dispatch state in declarations: 96.565834%; instructions 279/281, differing instruction positions 228; restored.
- cache method reference table entry: did not compile, incorrect guessed structure type; restored. A corrected compiling variant is recorded separately.
- reuse existing accumulator argument header pointer: 96.565834%; instructions 279/281, differing instruction positions 228; restored.
- cache correctly typed name table entry: 96.565834%; instructions 279/281, differing instruction positions 228; restored.

## CHANSVmStep

- for step counter with decrement after body: 94.630486%; instructions 1249/1253, differing instruction positions 1173; restored.
- inline initial comparison constants: 94.73823%; instructions 1249/1253, differing instruction positions 1173; restored.
- initialize interpreter private pointer at declaration: 94.7901%; instructions 1249/1253, differing instruction positions 1173; restored.

## VmBlobFill

- remove redundant blob conditional after null check: 91.74603%; instructions 60/63, differing instruction positions 43; restored. Unit function regressions: VmBlobFill.
- explicit separate input null checks: 96.666664%; instructions 65/63, differing instruction positions 39; restored. Unit function regressions: VmBlobFill.
- snapshot data and offset before memset: 99.809525%; instructions 63/63, differing instruction positions 5; restored. Unit function regressions: VmBlobFill.

## Final validation

Full gate after a clean 43U rebuild: GATE PASS. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Pool identical. Regression count 0; forbidden patterns 0; readability warnings 0.

Instruction-exact functions 201 -> 203; objdiff-matched functions 202 -> 204; code bytes 30984 -> 31620 out of 53564; data bytes 16 -> 16 out of 6904. VmDateGetRTC has 38/38 instructions and diffs 0; VmStringSplice has 121/121 instructions and diffs 0. Every remaining function has at least three distinct compiling source-level attempts recorded above. The unit remains NonMatching. Data is still incomplete; the matching string pool alone does not establish matching data.
