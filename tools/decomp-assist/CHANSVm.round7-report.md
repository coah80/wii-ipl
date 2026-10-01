GATE PASS

Instruction-exact 216/233 -> 217/233. Objdiff code 35484/53564 -> 35720/53564. Data 6904/6904 -> 6904/6904; .data 100.0%, all 121 interpreter jump-table relocations identical.

VmStringFromCharCode 100.0%; 59/59 instructions, ctxdiff diffs 0. Source commit 6f879ba3.

Remaining functions:

CHANSVmGetSourceLine 97.826090%, module, entry, bitfield and line-offset registers; 46/46 instructions, structural 0, diffs 16; 5 distinct compiling source attempts.
CHANSVmNewObjData 99.583336%, seven chunk-index and table-slot register differences; 96/96 instructions, structural 0, diffs 7; 17 distinct compiling source attempts.
CHANSVmParseInt 94.693880%, three prologue positions schedule endpoint initialization after argument copies; 49/49 instructions, structural 2, diffs 3; 8 distinct compiling source attempts.
CHANSVm_8144B4D4 97.590360%, endpoint store and type comparison are scheduled in opposite order; 83/83 instructions, structural 2, diffs 2; 5 distinct compiling source attempts.
VmDateDtor 94.967030%, seven calendar table-load and variadic argument positions are scheduled differently; 91/91 instructions, structural 5, diffs 7; 5 distinct compiling source attempts.
VmStringReplace 97.878784%, source/search/replacement and traversal register allocation; 132/132 instructions, structural 0, diffs 40; 4 distinct compiling source attempts.
VmStringSplit 98.040540%, delimiter, cursor, array and element register allocation; 222/222 instructions, structural 0, diffs 66; 4 distinct compiling source attempts.
CHANSVm_8145049C 99.849190%, thirteen string-format payload and owner register differences; 431/431 instructions, structural 0, diffs 13; 3 distinct compiling source attempts.
VmBlobGetHexString 98.719510%, fourteen hex index, cursor and digit register differences; 82/82 instructions, structural 0, diffs 14; 7 distinct compiling source attempts.
VmBlobPackCommon 97.934135%, two branch destinations plus packing-state register allocation; 668/668 instructions, structural 2, diffs 246; 4 distinct compiling source attempts.
VmBlobUnpack 98.268860%, format, cursor and decoded-value register allocation; 517/517 instructions, structural 0, diffs 156; 3 distinct compiling source attempts.
VmWinEmuWrite 99.626870%, five converted-string and aligned-length register differences; 67/67 instructions, structural 0, diffs 5; 10 distinct compiling source attempts.
CHANSVmAddExe 99.153540%, module, size and relocation-loop register allocation; 254/254 instructions, structural 0, diffs 34; 3 distinct compiling source attempts.
CHANSVmLinkModules 98.677246%, module, dispatch and object-iterator register allocation; 189/189 instructions, structural 0, diffs 43; 5 distinct compiling source attempts.
VmCallMethod 98.060500%, call-frame, native target and property selector register allocation; 281/281 instructions, structural 0, diffs 91; 3 distinct compiling source attempts.
CHANSVmStep 96.452515%, countdown control flow, table-base addressing, operand-type spill and registers; 1253/1253 instructions, structural 71, diffs 318; 8 distinct compiling source attempts.

Files changed: src/channelScript/CHANSVm.c; tools/decomp-assist/CHANSVm.round7-attempts.md; CHANSVm.round7-gates.txt; CHANSVm.round7-final-gate.txt; CHANSVm.round7-report.md.

Uncertain: compiler cause of remaining scheduling and register allocation.

Final full gate:

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/channelScript/CHANSVm] pool: IDENTICAL
[src/channelScript/CHANSVm] objdiff: code 35720/53564 data 6904/6904 functions 217/233 fuzzy 99.2758 linked code 0
[src/channelScript/CHANSVm] instruction-exact functions: 217/233
[src/channelScript/CHANSVm]   section .data size 4672 match 100.0
[src/channelScript/CHANSVm]   section .rodata size 1432 match 100.0
[src/channelScript/CHANSVm]   section .sbss size 16 match 100.0
[src/channelScript/CHANSVm]   section .sdata size 600 match 100.0
[src/channelScript/CHANSVm]   section .sdata2 size 184 match 100.0
[src/channelScript/CHANSVm]   section .text size 53564 match 99.27578
[src/channelScript/CHANSVm]   below 100: CHANSVmGetSourceLine 97.82609
[src/channelScript/CHANSVm]   below 100: CHANSVmNewObjData 99.583336
[src/channelScript/CHANSVm]   below 100: CHANSVmParseInt 94.69388
[src/channelScript/CHANSVm]   below 100: CHANSVm_8144B4D4 97.59036
[src/channelScript/CHANSVm]   below 100: VmDateDtor 94.96703
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
[src/channelScript/CHANSVm] baseline: code 35484/53564 data 6904 functions 216 fuzzy 99.2732
regressions vs baseline: 0
global matched_code_percent: 86.76230 -> 86.77018
global fuzzy_match_percent: 99.32123 -> 99.32127
global complete_code_percent: 60.61288 -> 60.61288
global matched_data_percent: 91.11620 -> 91.11620
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
