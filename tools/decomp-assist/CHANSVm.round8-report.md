GATE PASS

Before -> after, measured against fresh initial HEAD 0c554a16:
Instruction-exact functions 217/233 -> 218/233.
Objdiff matched code bytes 35720/53564 -> 36844/53564.
Objdiff matched data bytes 6904/6904 -> 6904/6904.
.data 4672/4672 bytes, 100.0% -> 100.0%; all 121 interpreter jump-table relocations identical. All 255 .data code relocations also have identical normalized destinations. Pools identical at 125/125 strings.
VmCallMethod 98.060500% -> 100.0%; 281/281 instructions, ctxdiff diffs 0, independently rebuilt after the full clean gate.

Remaining non-matching functions, in object order:

CHANSVmGetSourceLine 97.826090%, module, entry, bitfield and line-offset registers; 46/46 instructions, structural 0, diffs 16, 9 compiling attempts.
CHANSVmNewObjData 99.583336%, chunk ordinal and compiler-generated table-slot registers; 96/96 instructions, structural 0, diffs 7, 12 compiling attempts.
CHANSVmParseInt 94.693880%, endpoint store scheduled after base/output argument copies; 49/49 instructions, structural 2, diffs 3, 6 compiling attempts.
CHANSVm_8144B4D4 97.590360%, endpoint store and object-type comparison scheduled in opposite order; 83/83 instructions, structural 2, diffs 2, 6 compiling attempts.
VmDateDtor 94.967030%, weekday/month table loads and variadic stack argument scheduling; 91/91 instructions, structural 5, diffs 7, 3 compiling attempts.
VmStringReplace 97.878784%, source/search/replacement strings and traversal registers; 132/132 instructions, structural 0, diffs 40, 3 compiling attempts.
VmStringSplit 98.040540%, delimiter, array/element ownership and traversal registers; 222/222 instructions, structural 0, diffs 66, 4 compiling attempts.
CHANSVm_8145049C 99.849190%, temporary formatted-string payload and owner registers; 431/431 instructions, structural 0, diffs 13, 10 compiling attempts.
VmBlobGetHexString 98.719510%, hex character index, byte cursor and digit registers; 82/82 instructions, structural 0, diffs 14, 5 compiling attempts.
VmBlobPackCommon 97.949104%, packing-state registers after both structural branch differences were removed; 668/668 instructions, structural 0, diffs 244, 6 compiling attempts.
VmBlobUnpack 98.452614%, format/cursor/decoded-value registers after array-element lifetime was shared; 517/517 instructions, structural 0, diffs 141, 4 compiling attempts.
VmWinEmuWrite 99.626870%, converted string and aligned byte-length registers; 67/67 instructions, structural 0, diffs 5, 5 compiling attempts.
CHANSVmAddExe 99.625984%, module/type registers, module-clear counter and one addition operand order; 254/254 instructions, structural 0, diffs 16, 7 compiling attempts.
CHANSVmLinkModules 98.677246%, module, dispatch, global/native iterator and index registers; 189/189 instructions, structural 0, diffs 43, 7 compiling attempts.
CHANSVmStep 96.466080%, countdown control flow, result-table base, operand-type spill, result merge and registers; 1253/1253 instructions, structural 65, diffs 313, 10 compiling attempts.

Files changed:

src/channelScript/CHANSVm.c
tools/decomp-assist/CHANSVm.round8-attempts.md
tools/decomp-assist/CHANSVm.round8-final-gate.txt
tools/decomp-assist/CHANSVm.round8-report.md

Source improvements were committed only after their full clean gates passed:

8a87f2c2 refine module table traversal ordering
15c33bf7 match vm method dispatch
802c636a align blob packing validation branches
407c0895 share unpacked array element lifetime
1019c675 align interpreter constructor branch

Final report/log commit is the next commit after these source commits.

Uncertain: exact compiler causes of the remaining scheduling/register choices are unconfirmed. The default gate has no immutable baseline for HEAD 0c554a16; full gates therefore use --base f00336cc, the nearest ancestor with an existing baseline. Its printed baseline is 216 functions/35484 code bytes. The fresh initial unit report separately proves this run improved 217 -> 218 without regressing any initial exact function. No baseline, config, header or other translation unit was changed.

Every remaining function has at least three distinct compiling source-level attempts; the declaration-order search also tried 52 orders. Size/data regressions were restored. This is partial matching progress, with 15 functions still open and the unit remaining NonMatching/unlinked as requested.

Final full gate summary, copied verbatim:

```text
[src/channelScript/CHANSVm] pool: IDENTICAL
[src/channelScript/CHANSVm] objdiff: code 36844/53564 data 6904/6904 functions 218/233 fuzzy 99.3346 linked code 0
[src/channelScript/CHANSVm] instruction-exact functions: 218/233
[src/channelScript/CHANSVm]   section .data size 4672 match 100.0
GATE PASS
```

Final full non-quick gate:

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/channelScript/CHANSVm] pool: IDENTICAL
[src/channelScript/CHANSVm] objdiff: code 36844/53564 data 6904/6904 functions 218/233 fuzzy 99.3346 linked code 0
[src/channelScript/CHANSVm] instruction-exact functions: 218/233
[src/channelScript/CHANSVm]   section .data size 4672 match 100.0
[src/channelScript/CHANSVm]   section .rodata size 1432 match 100.0
[src/channelScript/CHANSVm]   section .sbss size 16 match 100.0
[src/channelScript/CHANSVm]   section .sdata size 600 match 100.0
[src/channelScript/CHANSVm]   section .sdata2 size 184 match 100.0
[src/channelScript/CHANSVm]   section .text size 53564 match 99.33456
[src/channelScript/CHANSVm]   below 100: CHANSVmGetSourceLine 97.82609
[src/channelScript/CHANSVm]   below 100: CHANSVmNewObjData 99.583336
[src/channelScript/CHANSVm]   below 100: CHANSVmParseInt 94.69388
[src/channelScript/CHANSVm]   below 100: CHANSVm_8144B4D4 97.59036
[src/channelScript/CHANSVm]   below 100: VmDateDtor 94.96703
[src/channelScript/CHANSVm]   below 100: VmStringReplace 97.878784
[src/channelScript/CHANSVm]   below 100: VmStringSplit 98.04054
[src/channelScript/CHANSVm]   below 100: CHANSVm_8145049C 99.84919
[src/channelScript/CHANSVm]   below 100: VmBlobGetHexString 98.71951
[src/channelScript/CHANSVm]   below 100: VmBlobPackCommon 97.949104
[src/channelScript/CHANSVm]   below 100: VmBlobUnpack 98.452614
[src/channelScript/CHANSVm]   below 100: VmWinEmuWrite 99.62687
[src/channelScript/CHANSVm]   below 100: CHANSVmAddExe 99.625984
[src/channelScript/CHANSVm]   below 100: CHANSVmLinkModules 98.677246
[src/channelScript/CHANSVm]   below 100: CHANSVmStep 96.46608
[src/channelScript/CHANSVm] baseline: code 35484/53564 data 6904 functions 216 fuzzy 99.2732
regressions vs baseline: 0
global matched_code_percent: 86.88876 -> 86.93417
global fuzzy_match_percent: 99.32283 -> 99.32392
global complete_code_percent: 60.61288 -> 60.61288
global matched_data_percent: 91.11620 -> 91.11620
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
