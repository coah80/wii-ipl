# CHANSVm wave 5 attempts

Partial progress only. Instruction-exact functions remain 206/233; objdiff functions remain 207/233. Code remains 32400/53564 bytes and data remains 2232/6904 bytes. The instruction-exact gain required by the task was not achieved.

CHANSVmStep improves from 94.81804% to 95.172386% and from 1252/1253 to 1253/1253 instructions. The strict comparison blank case follows strings, empty and equal strings share the true tail, and symbol load/store labels follow the target. Canonical .data relocation differences fall from 108 to 98. All ten strict-comparison table entries at .data+0x105c through +0x1080 now match. No explicit table data or pinned addresses were added.

The pool remains identical. Objdiff still reports .data at 18.050066%; .rodata, .sbss, .sdata and .sdata2 remain 100%. The .data raw bytes agree; its remaining canonical relocation mismatches all point inside CHANSVmStep. The .rodata raw bytes and canonical relocations agree. Shorter raw .sdata and .sbss section lengths are existing trailing alignment differences; the gate reports both at 100%.

Only the selected switch changes remain in CHANSVm.c. Every other experiment was restored. A trial marked kept in the temporary JSON log was retained for the next experiment, not necessarily in the final source.

## Remaining functions

- CHANSVmGetSourceLine, 97.82609%, 46/46 instructions, 16 differing instructions. 16 register differences in module lookup and line-marker traversal.
- CHANSVmNewObjData, 99.427086%, 96/96 instructions, 10 differing instructions. Ten register differences swap the chunk counter and slot address, and reuse the counter register for allocation size.
- CHANSVmParseInt, 94.69388%, 49/49 instructions, 3 differing instructions. Three prologue scheduling differences place the parse endpoint store after argument copies.
- CHANSVm_8144B4D4, 96.92771%, 83/83 instructions, 13 differing instructions. Register allocation and instruction scheduling differ in keyword conversion and strtod setup.
- VmArraySlice, 96.2782%, 133/133 instructions, 56 differing instructions. Bounds clipping branches and element traversal registers differ.
- VmDateDtor, 94.96703%, 91/91 instructions, 7 differing instructions. Seven differences in calendar argument loads and scheduling.
- VmStringFromCharCode, 99.40678%, 59/59 instructions, 6 differing instructions. Six differences swap the byte cursor and UTF-16 mask registers.
- VmStringReplace, 97.106064%, 132/132 instructions, 53 differing instructions. Replacement traversal registers and load scheduling differ.
- VmStringSplit, 96.04955%, 222/222 instructions, 81 differing instructions. Delimiter traversal registers and scheduling differ.
- CHANSVm_8145049C, 98.58237%, 431/431 instructions, 42 differing instructions. Format parsing registers and scheduling differ.
- CHANSVm_81450D14, 97.391304%, 45/46 instructions, instruction alignment differs. One branch instruction is missing from the absolute/relative range join; addc operands are reversed.
- VmBlobFill, 100.0%, 63/63 instructions, 2 differing instructions. Objdiff is 100% and the 252 instruction bytes are identical. ctxdiff reports two CR1 branch normalization differences because the preceding function is four bytes shorter.
- VmBlobCopyRangeFrom, 93.492645%, 139/136 instructions, instruction alignment differs. Three extra instructions, range predicate branches, and register allocation differ.
- VmBlobGetHexString, 98.71951%, 82/82 instructions, 14 differing instructions. Hex pair loop registers and store scheduling differ.
- VmBlobCalcRangeSHA1Digest, 96.484535%, 97/97 instructions, 14 differing instructions. Digest setup registers and range-check scheduling differ.
- VmBlobCalcHMAC, 99.453125%, 64/64 instructions, 7 differing instructions. Seven register differences in input pointer and length setup.
- VmBlobCalcRangeHMAC, 99.97479%, 119/119 instructions, 3 differing instructions. Three HMAC context addresses use stack +0xc instead of +0x10. The opaque SDK context alignment remains unresolved.
- vmBlobParsePackFormatString, 99.69827%, 116/116 instructions, 6 differing instructions. Six register differences in parameter digit decoding and multiplication.
- VmBlobPackCommon, 92.603294%, 675/668 instructions, instruction alignment differs. Seven extra instructions; stack layout, integer packing, and case control flow differ.
- VmBlobUnpack, 92.083176%, 531/517 instructions, instruction alignment differs. Fourteen extra instructions; unpacking control flow, stack layout, and registers differ.
- VmImageCtor, 99.0%, 25/25 instructions, 4 differing instructions. Four differences use r4 for the image and r0 for its data instead of r6 and r4.
- VmWinEmuWrite, 99.62687%, 67/67 instructions, 5 differing instructions. Five differences swap the converted string and aligned byte-length registers.
- CHANSVmAddExe, 99.1063%, 254/254 instructions, 35 differing instructions. Module table loop registers and scheduling differ.
- CHANSVm_81455654, 94.0%, 34/35 instructions, instruction alignment differs. One instruction missing; execution context/module registers and the negative-index return differ.
- CHANSVmLinkModules, 98.677246%, 189/189 instructions, 43 differing instructions. Module traversal registers and scheduling differ.
- VmCallMethod, 97.2242%, 281/281 instructions, 97 differing instructions. Call frame setup registers, stack accesses, and scheduling differ.
- CHANSVmStep, 95.172386%, 1253/1253 instructions, 894 differing instructions. Instruction counts now agree, but stack layout, register allocation, constant-table base loads, and several opcode/error tails differ; 98 generated table relocations remain wrong.

## Compiling source attempts

Each function has at least three distinct compiling variants. Failed compilations are listed separately and do not count. The FromCharCode trial that introduced an unused offset is also excluded from the count. Declaration-order trials that compiled to the same instructions are recorded as plateaus.

### CHANSVmGetSourceLine

- cache module beside execution context for source line lookup: 97.391304%, 46/46 instructions, 17 differences.
- scan line markers with a while loop: 97.82609%, 46/46 instructions, 16 differences.
- scope the line byte address and range check together: 97.82609%, 46/46 instructions, 16 differences.

### CHANSVmNewObjData

- advance chunk byte offset before its index: 99.427086%, 96/96 instructions, 10 differences.
- declare chunk pointer before chunk traversal counters: 99.427086%, 96/96 instructions, 10 differences.
- scope aligned allocation size beside the allocation: 99.427086%, 96/96 instructions, 10 differences.
- index chunk slots using the tracked table byte offset: 98.28125%, 97/96 instructions, 73 differences.
- scope the current chunk slot around allocation and scan: 99.427086%, 96/96 instructions, 10 differences.
- scan chunks with a post-tested loop: 99.427086%, 96/96 instructions, 10 differences.
- scan chunks with a for loop increment: 99.427086%, 96/96 instructions, 10 differences.
- use a typed chunk entry pointer instead of the traversal union: 99.114586%, 96/96 instructions, 16 differences.
- declare the typed entry after the chunk counter and current chunk: 99.114586%, 96/96 instructions, 16 differences.

### CHANSVmParseInt

- initialize parse endpoint before reading object type: 83.67347%, 49/49 instructions, 5 differences.
- initialize parse endpoint in its declaration: 94.69388%, 49/49 instructions, 3 differences.
- declare initialized endpoint before the byte object type: 83.67347%, 49/49 instructions, 5 differences.
- load object type after initializing the endpoint but before parsing: 83.67347%, 49/49 instructions, 5 differences.
- set endpoint immediately before the string conversion call: 82.244896%, 51/49 instructions, 41 differences.
- separate the type check with an early return: 90.408165%, 51/49 instructions, 43 differences.

### CHANSVm_8144B4D4

- initialize parse endpoint before converted output allocation: 94.518074%, 83/83 instructions, 20 differences.
- derive string length before checking its type: 96.92771%, 83/83 instructions, 13 differences.
- declare character count beside its input byte buffer: 96.92771%, 83/83 instructions, 13 differences.

### VmArraySlice

- derive slice length after testing start before end: 96.2782%, 133/133 instructions, 56 differences.
- fetch parent length before resetting the default start: 95.827065%, 133/133 instructions, 59 differences.
- load source element before destination element: 88.68421%, 133/133 instructions, 60 differences.

### VmDateDtor

- use calendar fields directly for the formatting arguments: 82.12088%, 97/91 instructions, 80 differences.
- use a scoped calendar pointer initialized at declaration: 94.96703%, 91/91 instructions, 7 differences.
- name calendar weekday and month before formatting: 94.96703%, 91/91 instructions, 7 differences.

### VmStringFromCharCode

- declare character count before its byte position: 99.15254%, 59/59 instructions, 9 differences.
- name the UTF16 character mask before iterating: 99.40678%, 59/59 instructions, 6 differences.
- increment character count before byte position: 99.40678%, 59/59 instructions, 6 differences.
- iterate characters with a for loop and explicit byte position: 99.32204%, 59/59 instructions, 7 differences.
- derive character index from the byte cursor: 91.94915%, 57/59 instructions, 44 differences.
- scope the decoded character over its two byte stores: 99.40678%, 59/59 instructions, 6 differences.

### VmStringReplace

- load replacement length before parent string data: 97.106064%, 132/132 instructions, 53 differences.
- declare replacement state before search state: 97.106064%, 132/132 instructions, 53 differences.
- advance the output position before source position: 97.181816%, 132/132 instructions, 52 differences.

### VmStringSplit

- initialize default limit before delimiter conversion: 95.14414%, 222/222 instructions, 93 differences.
- declare delimiter length before parent length: 95.95946%, 222/222 instructions, 84 differences.
- scope the delimiter conversion argument at method entry: 96.04955%, 222/222 instructions, 81 differences.

### CHANSVm_8145049C

- declare format buffers after string state variables: 98.58237%, 431/431 instructions, 42 differences.
- initialize formatting buffer pointer at declaration: 97.74014%, 431/431 instructions, 70 differences.
- declare character buffer before temporary formatted output: 98.58237%, 431/431 instructions, 42 differences.

### CHANSVm_81450D14

- add blob size before the negative relative offset: 97.391304%, 45/46 instructions, 29 differences.
- nest the negative check inside the relative range check: 92.934784%, 47/46 instructions, 30 differences.
- join relative offset failures at a checked error label: 86.304344%, 44/46 instructions, 29 differences.
- share relative range validation through the negative offset entry: 97.391304%, 45/46 instructions, 29 differences.
- handle absolute offsets before sharing the relative validation tail: 97.391304%, 45/46 instructions, 29 differences.
- route oversized absolute offsets into the negative offset branch: 97.391304%, 45/46 instructions, 29 differences.
- join valid absolute and normalized relative offsets before output: 97.391304%, 45/46 instructions, 29 differences.
- return checked absolute offsets before normalizing relative offsets: 89.565216%, 50/46 instructions, 33 differences.
- dispatch relative offset normalization through a boolean switch with correct block scope: 92.934784%, 49/46 instructions, 32 differences.
- name the absolute offset range predicate declared before normalization: 93.804344%, 48/46 instructions, 31 differences.
- return checked absolute offsets before normalizing relative offsets: 89.565216%, 50/46 instructions, 33 differences.
- inline the absolute offset range predicate: 93.804344%, 48/46 instructions, 31 differences.
- inline positive absolute offset validation: 94.13043%, 48/46 instructions, 29 differences.
- inline explicit relative offset predicate branches: 90.434784%, 48/46 instructions, 37 differences.
- inline an absolute offset predicate with a shared true tail: 90.76087%, 50/46 instructions, 33 differences.

### VmBlobFill

- cache the blob offset for fill count conversion: 96.82539%, 63/63 instructions, 3 differences; rejected regression in VmBlobFill.
- declare fill count before the blob header: 100.0%, 63/63 instructions, 2 differences.
- scope the fill destination beside memset: 100.0%, 63/63 instructions, 2 differences.

### VmBlobCopyRangeFrom

- check source offset before destination offset: 93.33088%, 139/136 instructions, 78 differences.
- scope converted size beside the checked source and destination: 93.492645%, 139/136 instructions, 72 differences.
- declare destination state before source state: 93.492645%, 139/136 instructions, 72 differences.

### VmBlobGetHexString

- compute second output character from the destination cursor: 98.71951%, 82/82 instructions, 14 differences.
- increment output count after writing the hex pair: 96.15854%, 81/82 instructions, 34 differences.
- read the hex byte once for both output digits: 92.36585%, 81/82 instructions, 36 differences.

### VmBlobCalcRangeSHA1Digest

- declare digest output before the hashing context: 96.484535%, 97/97 instructions, 14 differences.
- scope hashing context below the checked range: 96.484535%, 97/97 instructions, 14 differences.
- cache available range before the signed predicate: 93.40206%, 97/97 instructions, 9 differences.

### VmBlobCalcHMAC

- name data and byte count before digest storage: 99.453125%, 64/64 instructions, 7 differences.
- capture blob input before creating the output digest: 93.34375%, 64/64 instructions, 22 differences.
- scope output and digest below native key conversion: 99.453125%, 64/64 instructions, 7 differences.

### VmBlobCalcRangeHMAC

- keep converted size next to digest context: 99.97479%, 119/119 instructions, 3 differences.
- use the checked offset for digest input: 98.84034%, 118/119 instructions, 33 differences.
- scope input pointer only over digest operations: 99.72269%, 119/119 instructions, 9 differences.

### vmBlobParsePackFormatString

- update the decimal accumulator in separate arithmetic statements: 99.655174%, 116/116 instructions, 6 differences.
- add the decoded character before the decimal subtotal: 99.69827%, 116/116 instructions, 6 differences.
- use a separate character for parameter scanning: 98.31896%, 117/116 instructions, 35 differences.
- promote decoded Unicode character to an unsigned word: 99.69827%, 116/116 instructions, 6 differences.
- accumulate decimal digits with unsigned arithmetic and signed overflow check: 99.69827%, 116/116 instructions, 6 differences.
- subtract the digit base before adding it to the decimal subtotal: 99.69827%, 116/116 instructions, 6 differences.

### VmBlobPackCommon

- derive format length by shift after obtaining its string: 92.603294%, 675/668 instructions, 642 differences.
- declare packed integer buffer before parse counters: 92.603294%, 675/668 instructions, 642 differences.
- reset parameter count before output element size: 92.60479%, 675/668 instructions, 642 differences.

### VmBlobUnpack

- declare packed input words before the format state: 92.083176%, 531/517 instructions, 496 differences.
- reset output parameter before decoded element type: 92.09284%, 531/517 instructions, 496 differences.
- initialize input word pointer at declaration: 92.083176%, 531/517 instructions, 496 differences.

### VmImageCtor

- load image payload beside callback validation: 83.0%, 25/25 instructions, 7 differences.
- return the constructor callback directly after image validation: 58.4%, 17/25 instructions, 25 differences.
- retain typed image storage before its payload: 99.0%, 25/25 instructions, 4 differences.
- name the image data tested after callback lookup: 99.0%, 25/25 instructions, 4 differences.
- check image allocation through a named data pointer: 99.0%, 25/25 instructions, 4 differences.
- use failure tests before invoking the constructor callback: 47.8%, 17/25 instructions, 25 differences.
- scope callback and image validation together: 99.0%, 25/25 instructions, 4 differences.

### VmWinEmuWrite

- initialize the output loop offset in a for loop: 99.62687%, 67/67 instructions, 5 differences.
- compute aligned string length before resetting offset: 99.62687%, 67/67 instructions, 5 differences.
- declare the total length before converted string state: 99.17911%, 67/67 instructions, 8 differences.
- move the aligned length calculation into the loop initializer: 99.62687%, 67/67 instructions, 5 differences.
- scope the converted string over the conversion loop: 99.62687%, 67/67 instructions, 5 differences.
- use a decrementing byte count for loop completion: 94.10448%, 66/67 instructions, 46 differences.

### CHANSVmAddExe

- initialize header block position at declaration: 99.1063%, 254/254 instructions, 35 differences.
- use a typed module entry during zero initialization: 99.15354%, 254/254 instructions, 34 differences.
- increment module table byte offset in the for loop: 99.15354%, 254/254 instructions, 34 differences.

### CHANSVm_81455654

- join local and argument lookups at the result return: 88.28571%, 33/35 instructions, 18 differences.
- declare traversal locals before initializing the lookup result: 94.0%, 34/35 instructions, 35 differences.
- separate the typed module entry from the initially null result: 94.0%, 34/35 instructions, 35 differences.
- return the initially null result early for negative frame indices: 76.57143%, 36/35 instructions, 36 differences.
- keep null lookup result across module and early frame returns: 76.57143%, 36/35 instructions, 36 differences.
- test frame base before computing signed local displacement: 82.57143%, 38/35 instructions, 38 differences.
- place local lookup in the module lookup else branch: 94.0%, 34/35 instructions, 35 differences.
- initialize the return header between context and module reads: 94.0%, 34/35 instructions, 35 differences.
- join the global dereference with the module entry return: 94.0%, 34/35 instructions, 35 differences.

### CHANSVmLinkModules

- declare dispatch table before pass result: 98.677246%, 189/189 instructions, 43 differences.
- advance module count before traversing next module: 98.677246%, 189/189 instructions, 43 differences.
- use a for loop for module traversal: 98.677246%, 189/189 instructions, 43 differences.

### VmCallMethod

- initialize the accumulator pointer with its declaration: 97.2242%, 281/281 instructions, 97 differences.
- declare instruction before the new program counter: 97.2242%, 281/281 instructions, 97 differences.
- derive instruction pointer before the next program counter: 97.2242%, 281/281 instructions, 97 differences.

### CHANSVmStep

- size the operand type array for two operands: 94.81804%, 1252/1253 instructions, 1032 differences.
- use a separate local header for indirect stores: 94.21867%, 1250/1253 instructions, 1202 differences.
- load indirect index from copied reference header: 94.068634%, 1247/1253 instructions, 1221 differences.
- retain logical conversion error in the shared result: 93.98883%, 1248/1253 instructions, 1231 differences.
- convert bit-not float operand to unsigned integer: 93.98883%, 1248/1253 instructions, 1231 differences.
- place strict blank comparison after the string case: 94.52035%, 1248/1253 instructions, 1231 differences.
- join empty and equal strings at the strict string success flag: 94.60016%, 1249/1253 instructions, 1230 differences.
- select the left operand type with the nonzero iteration branch: 94.59617%, 1249/1253 instructions, 1230 differences.
- give property enumeration one checked success and error tail: 94.96488%, 1254/1253 instructions, 1234 differences.
- put symbol load before symbol store with the target argument directions: 94.97286%, 1254/1253 instructions, 1234 differences.
- check the lower float index bound before the upper bound: 94.97286%, 1254/1253 instructions, 1234 differences.
- evaluate float magnitude before its sign for bit-not: 94.57781%, 1258/1253 instructions, 1216 differences.
- return directly when binary operand conversion fails: 94.58579%, 1258/1253 instructions, 1216 differences.
- keep the result conversion loop in the interpreter with two type slots: 94.95371%, 1254/1253 instructions, 1234 differences.
- extract property name enumeration as an inline helper with a checked found output: 94.800476%, 1255/1253 instructions, 1215 differences.
- use separate copied index reference objects for indirect load and store: 94.049484%, 1247/1253 instructions, 1230 differences.
- return the boolean conversion status and use unsigned float conversion for bit inversion: 93.96967%, 1248/1253 instructions, 1240 differences.
- share strict string equality success and place the blank case after strings: 94.58101%, 1249/1253 instructions, 1239 differences.
- give the symbol load and store cases their target labels and source order: 94.58899%, 1249/1253 instructions, 1239 differences.
- check lower float index bound first and return immediately on operand conversion failure: 94.59697%, 1249/1253 instructions, 1239 differences.
- independent layout: strict blank case after strings only: 95.080605%, 1252/1253 instructions, 1029 differences; 105 data relocation differences.
- independent layout: strict string shared success tail only: 94.90183%, 1253/1253 instructions, 917 differences; 102 data relocation differences.
- independent layout: strict blank order and string success together: 95.164406%, 1253/1253 instructions, 896 differences; 98 data relocation differences.
- independent layout: correct symbol labels and order only: 94.82602%, 1252/1253 instructions, 1030 differences; 108 data relocation differences.
- independent layout: unsigned bit-not conversion only: 94.81804%, 1252/1253 instructions, 1032 differences; 108 data relocation differences.
- independent layout: logical status assignment only: 94.73823%, 1253/1253 instructions, 1106 differences; 115 data relocation differences.
- independent layout: strict order with correct symbol cases: 95.088585%, 1252/1253 instructions, 1027 differences; 105 data relocation differences.
- independent layout: strict order and unsigned inversion with symbol cases: 95.088585%, 1252/1253 instructions, 1027 differences; 105 data relocation differences.
- independent layout: all strict equality fixes with symbol cases: 95.172386%, 1253/1253 instructions, 894 differences; 98 data relocation differences.
- independent layout: strict equality and symbols with boolean status: 95.092575%, 1254/1253 instructions, 1201 differences; 121 data relocation differences.

## Additional table and context experiments

- Extracted VmGetResultType as a static inline helper with two type slots. Fully inlined; no extra function emitted. Intermediate Step result was 94.77414%, 1249/1253 instructions. Restored because later variants left 121 table relocation differences.
- Made VmResultTypeTbl internal, then the undefined-string objects and result table internal together. Constant bases still loaded independently; no useful change. Restored.
- Grouped existing string headers, constants, keywords, conversion functions and result matrices in a typed aggregate. Step reached 95.49242%, but aggregate tail alignment grew .rodata by four bytes and source token order moved the short NaN literal. The gate found nine regressions. Restored; no aggregate, artificial packing, or padding remains.
- Changed the opaque HMAC context byte buffer to word storage after inspecting SDK word accesses. Range HMAC still had the same three stack-address differences, and full HMAC still had seven register differences. Restored. No alignment field was fabricated.
- Reversing the bit-not magnitude/sign multiplication operands added four instructions and lowered Step to 94.57781%. Restored.
- The excluded FromCharCode declaration trial added an unused offset and stayed at 99.40678%. It does not count toward the three-attempt requirement.

## Failed compilations

- VmImageCtor: retain image storage pointer before dereferencing it; illegal implicit conversion from 'void **' to; restored.
- CHANSVm_81455654: use a separate module entry from the initially null result; illegal implicit conversion from 'struct ModuleEntry *' to; restored.
- CHANSVmParseInt: declare initialized endpoint before object type; undefined identifier 'endPtr'; restored.
- CHANSVmGetSourceLine: derive the line table byte address once at the range check; expression syntax error; restored.
- CHANSVmParseInt: initialize endpoint before the object type declaration with matching type; undefined identifier 'endPtr'; restored.
- CHANSVm_81450D14: dispatch relative offset normalization through a boolean switch; illegal use of keyword; restored.
- CHANSVm_81450D14: name the absolute offset range predicate before normalization; expression syntax error; restored.
- VmStringFromCharCode: name the string storage separately for each byte store; illegal implicit conversion from 'char *' to; restored.

## Validation

Focused object builds, ctxdiff, the string-pool check, and canonical ELF relocation audits were run. The selected quick gate passed with zero regressions, zero added forbidden patterns, and zero net readability warnings. The final full gate passed. Its output follows.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/channelScript/CHANSVm] pool: IDENTICAL
[src/channelScript/CHANSVm] objdiff: code 32400/53564 data 2232/6904 functions 207/233 fuzzy 98.3831 linked code 0
[src/channelScript/CHANSVm] instruction-exact functions: 206/233
[src/channelScript/CHANSVm]   section .data size 4672 match 18.050066
[src/channelScript/CHANSVm]   section .rodata size 1432 match 100.0
[src/channelScript/CHANSVm]   section .sbss size 16 match 100.0
[src/channelScript/CHANSVm]   section .sdata size 600 match 100.0
[src/channelScript/CHANSVm]   section .sdata2 size 184 match 100.0
[src/channelScript/CHANSVm]   section .text size 53564 match 98.383095
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
[src/channelScript/CHANSVm]   below 100: CHANSVmStep 95.172386
[src/channelScript/CHANSVm] baseline: code 32400/53564 data 2232 functions 207 fuzzy 98.3499
regressions vs baseline: 0
global matched_code_percent: 72.81211 -> 72.81211
global fuzzy_match_percent: 82.03284 -> 82.03342
global complete_code_percent: 56.76068 -> 56.76068
global matched_data_percent: 86.27674 -> 86.27674
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
