# rx1 allocator investigation

## Retained result

Two new exact functions in `src/channelScript/CHANSVm.c`: CHANSVmFormatString 99.84919% -> 100.0% (431/431 instructions, zero differences), and VmStringSplit 98.04054% -> 100.0% (222/222, zero differences). Format uses separate typed input/owner pointers, removing six pointer/integer casts; Split reuses the reset counter, separates the final-element pointer and adjusts declaration/evaluation order. Both final allocator captures validate every register rewrite and produce whole objects identical to the normal compiler. The actual source and combined captured source have SHA256 `6c01fb86d0eddf5150fc42afeccf19ec25642548d1190926911fa31e5da0a7d4`.

CHANSVm exact count is 224 -> 226 of 233, matched code 39908 -> 42520 of 53564 bytes, data 6904/6904 unchanged. nup stays 22/23 exact, code 8956/10764, data 1720/1720. ATERM stays 20/26 exact, code 12200/19204, data 18864/18864. All three units remain unlinked. No nup or ATERM source change is retained.

The clean final gate passed, all pools are identical, the DOL SHA1 is `26116613f624061ba99c8d1a299aaa6efa85670d`, and no code/data/function regression or added forbidden/readability pattern was found. A fresh comparison against the exact checkout baseline also found zero regressions across every unit and function. All private searches and debugger captures have exited. Source commit: `dc0f2351`. Detailed allocator explanations, rejected source trials and final validation follow below.

Five requested functions remain open. AES has a rejected two-store-order scratch result at 99.95522%; the other four retain their baseline scores. The scratch AES result is not part of the retained source.

## Allocator handoff

| Function | Retained objdiff | Observed cause and result |
| --- | --- | --- |
| CHANSVmFormatString | 99.84919 -> 100.0 | Final pass 2 selects the typed owner as the cost-4, degree-29 optimistic spill candidate. Owner rank 18 gets r14; input rank 14, length rank 19 and result rank 60 get r18. |
| VmStringSplit | 98.04054 -> 100.0 | Reusing the reset counter changes its liveness and puts it third in coloring order. Distinct final-element/remaining-length lifetimes get r25/r26. No new coalesces or spills. |
| VmWinEmuWrite | 99.62687 -> 99.62687 | The converted result is anonymous v40; named strObj is dead. No VM/result interference edge and no VM/result move candidate. Reverse coloring gives the result r29 before length gets r27; VM later reuses r27. |
| VmBlobGetHexString | 98.71951 -> 98.71951 | Synthesized byte offset colors second into r4; anonymous digit values claim r5 before named character cursor reaches r7. Named digit reuse changes its rank but leaves the wrong cursor color. |
| __nupParseServerInfo | 99.26991 -> 99.26991 | Named helper return copies disappear. Opening tag/start/end values retain the same coloring order and r24/r26/r22 assignment, instead of target r22/r24/r26. |
| ATERMBuildAssociationRequest | 98.7594 -> 98.7594 | Input pointers simplify at degree 14 and reach coloring ranks 54/61 in r9. Nibble order changes output cursor colors, leaving the input mismatch and worsening both loop users. |
| ATERMAesExpandEncryptKey | 98.94403 -> 98.94403 | Direct global table access fixes the 128-bit loop. Anonymous first-word v58 requests r27 at rank 217. The final scratch result has every target register but stores words in order 0,3,2,1; two instructions differ and it is rejected. |

| Changed-source capture | Validated GPR / CR operands | Whole object equals normal compiler |
| --- | --- | --- |
| mwdbg-format-and-split-final | 810 / 223 | Yes |
| mwdbg-split-tail-owner-order-1 | 478 / 130 | Yes |
| mwdbg-write-result-reuse | 129 / 36 | Yes |
| mwdbg-hex-reused-digit-19-s32 | 177 / 37 | Yes |
| mwdbg-nup-result-typed-copy | 1186 / 364 | Yes |
| mwdbg-assoc-low-before-high | 272 / 53 | Yes |
| mwdbg-aes-held-final-stores-321 | 546 / 12 | Yes |

All capture paths are under ignored `build/rx1/`; none of the rejected source is committed. Diagnostic launchers and the read-only GDB memory cache also live there. The debugger omits `-enc SJIS` to avoid the emulator's pre-codegen crash; all normal builds keep the original flag, and complete object equality validates the diagnostic run. Shared debugger and CPU locks were retained.

Base: 21c5ceda, agent/w1005/rx1. Scope: CHANSVmFormatString, VmWinEmuWrite, VmBlobGetHexString, VmStringSplit, __nupParseServerInfo, ATERMBuildAssociationRequest, ATERMAesExpandEncryptKey. No push, merge, rebase, subagents, or source edits outside rx1.

Setup: checkout lacked orig/43U/00000008.app and build.ninja. Copied retail input read-only from an archived checkout under /mnt/drive2/.Trash-1000/files into rx1; configure and split validate the image. Original main and verify-fix were not used. Private build/rx1/mwdbg.py changes only launcher ROOT to the installed tools and capture containment to the selected project; captures stay under build/rx1. Shared debugger port lock retained.

Prior evidence: CHANSVm helper-only round h4 exhausted 55 forms without a match; round8 parameter reuse for parent/ret and declaration-only changes did not fix VmWinEmuWrite. New attempts use actual allocator evidence.

- write-typed-string: VmWinEmuWrite. Test stable string payload instead of header, while checking alias reload changes. {"label": "write-typed-string", "function": "VmWinEmuWrite", "error": "### mwcceppc.exe Compiler:\n#    File: build\\rx1\\trials\\write-typed-string\\CHANSVm.c\n# ------------------------------------------------------\n#    6098:     CHANSVmString* string; \n#   Error:     ^^^^^^^^^^^^^\n#   (10140) undefined identifier 'CHANSVmString'\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\n"}

## VmWinEmuWrite baseline allocator

Target: VM and converted header reuse r27, offset r28, aligned byte length r29, capacity r30, zero r31. Baseline mwdbg with -enc SJIS omitted produced a complete object byte-identical to the normal Ninja object. Installed launcher crashes before codegen with the encoding option at 0x47e090; no source or normal-build flags changed.

PCode before allocation assigns the call result to anonymous r40, not named strObj r37, which is dead. Simplify removes vm r32 degree12, length r35 degree22, offset r36 degree23, then result r40 degree22. Reverse coloring assigns zero r51 to r31, capacity r44 to r30, result r40 to r29, offset r36 to r28, length r35 to r27; vm r32 then reuses r27. r40 has 26 initial neighbors; r35 has 23. There is NO vm/strObj move candidate and no interference edge between r32 and r40. Only call-result copies to physical r3 are rejected for interference. This is priority-driven color reuse, not a failed vm/strObj coalescing attempt. The source needs length above the propagated object temporary in priority, or a persistent lower-numbered object value.

- write-typed-string-fixed: VmWinEmuWrite. Use stable string payload local; check target reloads. {"label": "write-typed-string-fixed", "function": "VmWinEmuWrite", "score": 96.49254, "insns": [65, 67], "diffs": 52, "drops": [["VmWinEmuWrite", 99.62687, 96.49254]]}

- write-length-expression: VmWinEmuWrite. Two real length assignments. {"label": "write-length-expression", "function": "VmWinEmuWrite", "score": 99.477615, "insns": [67, 67], "diffs": 6, "drops": [["VmWinEmuWrite", 99.62687, 99.477615]]}

- write-result-reuse: VmWinEmuWrite. Raw then converted header lifetime. {"label": "write-result-reuse", "function": "VmWinEmuWrite", "score": 99.62687, "insns": [67, 67], "diffs": 5, "drops": []}

- write-object-declared-last: VmWinEmuWrite. Lower named object vreg, test propagated temporary. {"label": "write-object-declared-last", "function": "VmWinEmuWrite", "score": 99.62687, "insns": [67, 67], "diffs": 5, "drops": []}

- write-length-local-expression: VmWinEmuWrite. Scope length at first use. {"label": "write-length-local-expression", "function": "VmWinEmuWrite", "score": 99.62687, "insns": [67, 67], "diffs": 5, "drops": []}

- write-length-inline: VmWinEmuWrite. Try later expression vreg through a plain length helper. {"label": "write-length-inline", "function": "VmWinEmuWrite", "score": 99.62687, "insns": [67, 67], "diffs": 5, "drops": []}

- write-length-inline-local: VmWinEmuWrite. Try later expression vreg through a plain length helper. {"label": "write-length-inline-local", "function": "VmWinEmuWrite", "score": 99.62687, "insns": [67, 67], "diffs": 5, "drops": []}

- write-length-inline-const: VmWinEmuWrite. Try later expression vreg through a plain length helper. {"label": "write-length-inline-const", "function": "VmWinEmuWrite", "score": 99.62687, "insns": [67, 67], "diffs": 5, "drops": []}

- nup-end-before-guard: __nupParseServerInfo__FP14NUPContextInfoPcPcUx. Give closing cursor an initial real pointer lifetime before its search. {"label": "nup-end-before-guard", "function": "__nupParseServerInfo__FP14NUPContextInfoPcPcUx", "score": 99.26991, "insns": [452, 452], "diffs": 66, "drops": []}

- nup-const-tag-params: __nupParseServerInfo__FP14NUPContextInfoPcPcUx. Use top-level const on inline tag pointer parameters. {"label": "nup-const-tag-params", "function": "__nupParseServerInfo__FP14NUPContextInfoPcPcUx", "score": 85.70575, "insns": [430, 452], "diffs": 414, "drops": [["__nupParseServerInfo__FP14NUPContextInfoPcPcUx", 99.26991, 85.70575]]}

- nup-end-conditional: __nupParseServerInfo__FP14NUPContextInfoPcPcUx. Boolean assignment guard changes propagation construction. {"label": "nup-end-conditional", "function": "__nupParseServerInfo__FP14NUPContextInfoPcPcUx", "score": 99.26991, "insns": [452, 452], "diffs": 66, "drops": []}

- nup-nested-guards: __nupParseServerInfo__FP14NUPContextInfoPcPcUx. Separate helper assignments from guards to test creation order without changing calls. {"label": "nup-nested-guards", "function": "__nupParseServerInfo__FP14NUPContextInfoPcPcUx", "score": 89.048676, "insns": [496, 452], "diffs": 425, "drops": [["__nupParseServerInfo__FP14NUPContextInfoPcPcUx", 99.26991, 89.048676]]}

- nup-result-typed-copy: __nupParseServerInfo__FP14NUPContextInfoPcPcUx. Name helper return before the caller copy. {"label": "nup-result-typed-copy", "function": "__nupParseServerInfo__FP14NUPContextInfoPcPcUx", "score": 99.26991, "insns": [452, 452], "diffs": 66, "drops": []}

- write-print-helper: VmWinEmuWrite. Rendering helper receives already validated object and aligned length; test copy and parameter vreg order. {"label": "write-print-helper", "function": "VmWinEmuWrite", "score": 99.10448, "insns": [67, 67], "diffs": 13, "drops": [["VmWinEmuWrite", 99.62687, 99.10448]]}

- write-print-helper-reverse: VmWinEmuWrite. Rendering helper receives already validated object and aligned length; test copy and parameter vreg order. {"label": "write-print-helper-reverse", "function": "VmWinEmuWrite", "score": 99.10448, "insns": [67, 67], "diffs": 13, "drops": [["VmWinEmuWrite", 99.62687, 99.10448]]}

- write-print-helper-size: VmWinEmuWrite. Rendering helper receives already validated object and aligned length; test copy and parameter vreg order. {"label": "write-print-helper-size", "function": "VmWinEmuWrite", "score": 99.10448, "insns": [67, 67], "diffs": 13, "drops": [["VmWinEmuWrite", 99.62687, 99.10448]]}

- write-normalized-header: VmWinEmuWrite. Normalize non-string conversion to null to introduce a real second definition. {"label": "write-normalized-header", "function": "VmWinEmuWrite", "score": 94.850746, "insns": [70, 67], "diffs": 52, "drops": [["VmWinEmuWrite", 99.62687, 94.850746]]}

- write-early-validation: VmWinEmuWrite. Early validation scopes successful output separately. {"label": "write-early-validation", "function": "VmWinEmuWrite", "score": 94.62687, "insns": [69, 67], "diffs": 52, "drops": [["VmWinEmuWrite", 99.62687, 94.62687]]}

- write-length-loop-init: VmWinEmuWrite. Length assignment in loop initializer changes expression lifetime. {"label": "write-length-loop-init", "function": "VmWinEmuWrite", "score": 99.62687, "insns": [67, 67], "diffs": 5, "drops": []}

- format-object-before-length: CHANSVmFormatString. Move nObj before objLen: baseline nObj r35 is colored early and claims r18; target needs r14. {"label": "format-object-before-length", "function": "CHANSVmFormatString", "score": 99.84919, "insns": [431, 431], "diffs": 13, "drops": []}

- format-object-top-first: CHANSVmFormatString. Top-level object declaration changes its ID relative to high-degree format state. {"label": "format-object-top-first", "function": "CHANSVmFormatString", "score": 97.38979, "insns": [431, 431], "diffs": 147, "drops": [["CHANSVmFormatString", 99.84919, 97.38979]]}

- format-object-top-last: CHANSVmFormatString. Object declared after outer locals moves ID oppositely. {"label": "format-object-top-last", "function": "CHANSVmFormatString", "score": 99.84919, "insns": [431, 431], "diffs": 13, "drops": []}

- format-length-outer: CHANSVmFormatString. Move objLen across the branch scope to alter its simplify position. {"label": "format-length-outer", "function": "CHANSVmFormatString", "score": 99.84919, "insns": [431, 431], "diffs": 13, "drops": []}

- format-string-pointer: CHANSVmFormatString. Give character/string buffer a typed pointer instead of sharing isEscaped integer lifetime. {"label": "format-string-pointer", "function": "CHANSVmFormatString", "score": 99.187935, "insns": [431, 431], "diffs": 53, "drops": [["CHANSVmFormatString", 99.84919, 99.187935]]}

## CHANSVmFormatString baseline allocator

Target r14 owns the temporary string header to delete. Target r18 owns the character buffer address, aligned string length, formatted input pointer and swprintf result, in disjoint lifetimes. Use final GPR pass 2, not failed pass 1: actual pass-1 spills include r165/r56/r161/r153/r57/r168/r94/r98/r126/r163. In pass2 nObj r35 has 44 neighbors, simplify degree25, priority13, claims r18. The shared string input pointer r65 has 40 neighbors, degree29, priority17 and claims r14. objLen r36 has degree29 priority18 and reuses r14; swprintf result r169 degree28 priority59 also reuses r14. LitLen string-owner copies coalesce into nObj, which is why ordinary isEscaped/litLen declaration swaps miss the actual cause. Tested moving the owner and length declarations, and separating a real typed string pointer; none yet exact.

## __nupParseServerInfo baseline allocator

Complete debugger object equals normal Ninja object. First tag: target opening literal r22, found opening tag/value r24, closing literal r25, found closing tag r26. Source opening literal r109->r24, found start r106->r26, closing literal r108->r25, found end anonymous r114->r22. Coloring priority is r114 at102, r109 at106, r108 at107, r106 at109. Simplify degrees are21/20/22/22. Available masks are0x2c400000/0x2f000000/0x2e000000/0x2c000000, and lowest available colors explain r22/r24/r25/r26. Later DeviceId has target end literal r27, start literal r26, found start r29, found end r18; source r29/r27/r18/r26. Repeated scalar helpers share this permutation. All call-result merge attempts here reject interference with physical r3; there is no register-pressure spill. Output state and late title-loop locals color before these helper temporaries. Top-level const on helper parameters materially changes inlining/CSE and drops to430 instructions; reverted.

- format-reuse-cv: CHANSVmFormatString. Reuse a non-overlapping object local instead of nObj, targeting the saved-color request order. {"label": "format-reuse-cv", "function": "CHANSVmFormatString", "score": 97.38979, "insns": [431, 431], "diffs": 147, "drops": [["CHANSVmFormatString", 99.84919, 97.38979]]}

- format-reuse-argObj: CHANSVmFormatString. Reuse a non-overlapping object local instead of nObj, targeting the saved-color request order. {"label": "format-reuse-argObj", "function": "CHANSVmFormatString", "score": 97.38979, "insns": [431, 431], "diffs": 147, "drops": [["CHANSVmFormatString", 99.84919, 97.38979]]}

- format-object-order-1: CHANSVmFormatString. Allocator-guided nObj declaration position after u8 pad0[8]; {"label": "format-object-order-1", "function": "CHANSVmFormatString", "score": 97.38979, "insns": [431, 431], "diffs": 147, "drops": [["CHANSVmFormatString", 99.84919, 97.38979]]}

- format-object-order-2: CHANSVmFormatString. Allocator-guided nObj declaration position after u8 tempBuf[16]; {"label": "format-object-order-2", "function": "CHANSVmFormatString", "score": 97.38979, "insns": [431, 431], "diffs": 147, "drops": [["CHANSVmFormatString", 99.84919, 97.38979]]}

- format-object-order-3: CHANSVmFormatString. Allocator-guided nObj declaration position after u8 fmtBufData[32]; {"label": "format-object-order-3", "function": "CHANSVmFormatString", "score": 97.38979, "insns": [431, 431], "diffs": 147, "drops": [["CHANSVmFormatString", 99.84919, 97.38979]]}

- format-object-order-4: CHANSVmFormatString. Allocator-guided nObj declaration position after u8* fmtBuf; {"label": "format-object-order-4", "function": "CHANSVmFormatString", "score": 97.563805, "insns": [431, 431], "diffs": 145, "drops": [["CHANSVmFormatString", 99.84919, 97.563805]]}

- format-object-order-5: CHANSVmFormatString. Allocator-guided nObj declaration position after wchar_t wideFmt[32]; {"label": "format-object-order-5", "function": "CHANSVmFormatString", "score": 97.563805, "insns": [431, 431], "diffs": 145, "drops": [["CHANSVmFormatString", 99.84919, 97.563805]]}

- format-object-order-6: CHANSVmFormatString. Allocator-guided nObj declaration position after u32 halfMaxSize; {"label": "format-object-order-6", "function": "CHANSVmFormatString", "score": 97.563805, "insns": [431, 431], "diffs": 145, "drops": [["CHANSVmFormatString", 99.84919, 97.563805]]}

- format-object-order-7: CHANSVmFormatString. Allocator-guided nObj declaration position after BOOL flag; {"label": "format-object-order-7", "function": "CHANSVmFormatString", "score": 97.563805, "insns": [431, 431], "diffs": 145, "drops": [["CHANSVmFormatString", 99.84919, 97.563805]]}

- format-object-order-8: CHANSVmFormatString. Allocator-guided nObj declaration position after CHANSVmObjHdr* tempObj; {"label": "format-object-order-8", "function": "CHANSVmFormatString", "score": 97.563805, "insns": [431, 431], "diffs": 145, "drops": [["CHANSVmFormatString", 99.84919, 97.563805]]}

- format-object-order-9: CHANSVmFormatString. Allocator-guided nObj declaration position after u32 argIdxCounter; {"label": "format-object-order-9", "function": "CHANSVmFormatString", "score": 97.691414, "insns": [431, 431], "diffs": 137, "drops": [["CHANSVmFormatString", 99.84919, 97.691414]]}

- format-object-order-10: CHANSVmFormatString. Allocator-guided nObj declaration position after u32 totalLen; {"label": "format-object-order-10", "function": "CHANSVmFormatString", "score": 97.83063, "insns": [431, 431], "diffs": 129, "drops": [["CHANSVmFormatString", 99.84919, 97.83063]]}

- format-object-order-11: CHANSVmFormatString. Allocator-guided nObj declaration position after u8* str; {"label": "format-object-order-11", "function": "CHANSVmFormatString", "score": 98.02784, "insns": [431, 431], "diffs": 128, "drops": [["CHANSVmFormatString", 99.84919, 98.02784]]}

- format-object-order-12: CHANSVmFormatString. Allocator-guided nObj declaration position after u32 strLen; {"label": "format-object-order-12", "function": "CHANSVmFormatString", "score": 98.15545, "insns": [431, 431], "diffs": 126, "drops": [["CHANSVmFormatString", 99.84919, 98.15545]]}

- format-object-order-13: CHANSVmFormatString. Allocator-guided nObj declaration position after u32 strPos; {"label": "format-object-order-13", "function": "CHANSVmFormatString", "score": 98.7935, "insns": [431, 431], "diffs": 87, "drops": [["CHANSVmFormatString", 99.84919, 98.7935]]}

- format-object-order-14: CHANSVmFormatString. Allocator-guided nObj declaration position after u32 segStart; {"label": "format-object-order-14", "function": "CHANSVmFormatString", "score": 98.85151, "insns": [431, 431], "diffs": 82, "drops": [["CHANSVmFormatString", 99.84919, 98.85151]]}

- format-object-order-15: CHANSVmFormatString. Allocator-guided nObj declaration position after u32 fmtBufPos; {"label": "format-object-order-15", "function": "CHANSVmFormatString", "score": 99.37355, "insns": [431, 431], "diffs": 48, "drops": [["CHANSVmFormatString", 99.84919, 99.37355]]}

- format-object-order-16: CHANSVmFormatString. Allocator-guided nObj declaration position after u8* tmpBuf; {"label": "format-object-order-16", "function": "CHANSVmFormatString", "score": 99.44315, "insns": [431, 431], "diffs": 42, "drops": [["CHANSVmFormatString", 99.84919, 99.44315]]}

- format-object-order-17: CHANSVmFormatString. Allocator-guided nObj declaration position after u32 maxSize; {"label": "format-object-order-17", "function": "CHANSVmFormatString", "score": 99.489555, "insns": [431, 431], "diffs": 38, "drops": [["CHANSVmFormatString", 99.84919, 99.489555]]}

- format-object-order-18: CHANSVmFormatString. Allocator-guided nObj declaration position after u8* outputBuf; {"label": "format-object-order-18", "function": "CHANSVmFormatString", "score": 99.59397, "insns": [431, 431], "diffs": 32, "drops": [["CHANSVmFormatString", 99.84919, 99.59397]]}

- format-object-order-19: CHANSVmFormatString. Allocator-guided nObj declaration position after u32 outputPos; {"label": "format-object-order-19", "function": "CHANSVmFormatString", "score": 99.75638, "insns": [431, 431], "diffs": 21, "drops": [["CHANSVmFormatString", 99.84919, 99.75638]]}

- format-object-order-20: CHANSVmFormatString. Allocator-guided nObj declaration position after u32 maxLitLen; {"label": "format-object-order-20", "function": "CHANSVmFormatString", "score": 99.84919, "insns": [431, 431], "diffs": 13, "drops": []}

- nup-const-params-1: __nupParseServerInfo__FP14NUPContextInfoPcPcUx. Restrict top-level const to selected inline parameters to isolate literal folding from register order. {"label": "nup-const-params-1", "function": "__nupParseServerInfo__FP14NUPContextInfoPcPcUx", "score": 99.26991, "insns": [452, 452], "diffs": 66, "drops": []}

- format-object-order-21: CHANSVmFormatString. Allocator-guided nObj declaration position after u32 litLen; {"label": "format-object-order-21", "function": "CHANSVmFormatString", "score": 99.84919, "insns": [431, 431], "diffs": 13, "drops": []}

- nup-const-params-2: __nupParseServerInfo__FP14NUPContextInfoPcPcUx. Restrict top-level const to selected inline parameters to isolate literal folding from register order. {"label": "nup-const-params-2", "function": "__nupParseServerInfo__FP14NUPContextInfoPcPcUx", "score": 91.0177, "insns": [441, 452], "diffs": 423, "drops": [["__nupParseServerInfo__FP14NUPContextInfoPcPcUx", 99.26991, 91.0177]]}

- nup-const-params-3: __nupParseServerInfo__FP14NUPContextInfoPcPcUx. Restrict top-level const to selected inline parameters to isolate literal folding from register order. {"label": "nup-const-params-3", "function": "__nupParseServerInfo__FP14NUPContextInfoPcPcUx", "score": 91.0177, "insns": [441, 452], "diffs": 423, "drops": [["__nupParseServerInfo__FP14NUPContextInfoPcPcUx", 99.26991, 91.0177]]}

- nup-const-params-4: __nupParseServerInfo__FP14NUPContextInfoPcPcUx. Restrict top-level const to selected inline parameters to isolate literal folding from register order. {"label": "nup-const-params-4", "function": "__nupParseServerInfo__FP14NUPContextInfoPcPcUx", "score": 91.98009, "insns": [441, 452], "diffs": 423, "drops": [["__nupParseServerInfo__FP14NUPContextInfoPcPcUx", 99.26991, 91.98009]]}

- format-object-order-22: CHANSVmFormatString. Allocator-guided nObj declaration position after u32 isEscaped; {"label": "format-object-order-22", "function": "CHANSVmFormatString", "score": 99.84919, "insns": [431, 431], "diffs": 13, "drops": []}

- nup-const-params-5: __nupParseServerInfo__FP14NUPContextInfoPcPcUx. Restrict top-level const to selected inline parameters to isolate literal folding from register order. {"label": "nup-const-params-5", "function": "__nupParseServerInfo__FP14NUPContextInfoPcPcUx", "score": 91.98009, "insns": [441, 452], "diffs": 423, "drops": [["__nupParseServerInfo__FP14NUPContextInfoPcPcUx", 99.26991, 91.98009]]}

- nup-const-params-6: __nupParseServerInfo__FP14NUPContextInfoPcPcUx. Restrict top-level const to selected inline parameters to isolate literal folding from register order. {"label": "nup-const-params-6", "function": "__nupParseServerInfo__FP14NUPContextInfoPcPcUx", "score": 85.70575, "insns": [430, 452], "diffs": 414, "drops": [["__nupParseServerInfo__FP14NUPContextInfoPcPcUx", 99.26991, 85.70575]]}

- format-object-order-23: CHANSVmFormatString. Allocator-guided nObj declaration position after CHANSVmObjHdr* cv; {"label": "format-object-order-23", "function": "CHANSVmFormatString", "score": 99.84919, "insns": [431, 431], "diffs": 13, "drops": []}

- nup-positive-guard: __nupParseServerInfo__FP14NUPContextInfoPcPcUx. Positive guard keeps tag-call order but changes control-flow lowering. {"label": "nup-positive-guard", "function": "__nupParseServerInfo__FP14NUPContextInfoPcPcUx", "score": 89.048676, "insns": [452, 452], "diffs": 160, "drops": [["__nupParseServerInfo__FP14NUPContextInfoPcPcUx", 99.26991, 89.048676]]}

- format-object-order-24: CHANSVmFormatString. Allocator-guided nObj declaration position after CHANSVmPrivate* pVm; {"label": "format-object-order-24", "function": "CHANSVmFormatString", "score": 99.84919, "insns": [431, 431], "diffs": 13, "drops": []}

- format-object-order-25: CHANSVmFormatString. Allocator-guided nObj declaration position after CHANSVmObjHdr* argObj; {"label": "format-object-order-25", "function": "CHANSVmFormatString", "score": 99.84919, "insns": [431, 431], "diffs": 13, "drops": []}

- format-typed-owner-1: CHANSVmFormatString. Separate temporary-string ownership from numeric length; declare after u8 pad0[8]; {"label": "format-typed-owner-1", "function": "CHANSVmFormatString", "score": 97.38979, "insns": [431, 431], "diffs": 147, "drops": [["CHANSVmFormatString", 99.84919, 97.38979]]}

- write-minimum-with-if: VmWinEmuWrite. Use branch-local bounded input length as in target Ghidra; all actual values unchanged. {"label": "write-minimum-with-if", "function": "VmWinEmuWrite", "score": 96.343285, "insns": [68, 67], "diffs": 40, "drops": [["VmWinEmuWrite", 99.62687, 96.343285]]}

- format-typed-owner-2: CHANSVmFormatString. Separate temporary-string ownership from numeric length; declare after u8 tempBuf[16]; {"label": "format-typed-owner-2", "function": "CHANSVmFormatString", "score": 97.38979, "insns": [431, 431], "diffs": 147, "drops": [["CHANSVmFormatString", 99.84919, 97.38979]]}

- write-aligned-length-const: VmWinEmuWrite. Immutable validated length scoped to output. {"label": "write-aligned-length-const", "function": "VmWinEmuWrite", "score": 99.62687, "insns": [67, 67], "diffs": 5, "drops": []}

- format-typed-owner-3: CHANSVmFormatString. Separate temporary-string ownership from numeric length; declare after u8 fmtBufData[32]; {"label": "format-typed-owner-3", "function": "CHANSVmFormatString", "score": 97.38979, "insns": [431, 431], "diffs": 147, "drops": [["CHANSVmFormatString", 99.84919, 97.38979]]}

- write-for-offset: VmWinEmuWrite. Natural counted loop relocates offset definition and update. Binding and update semantics preserved on break. {"label": "write-for-offset", "function": "VmWinEmuWrite", "score": 99.62687, "insns": [67, 67], "diffs": 5, "drops": []}

- format-typed-owner-4: CHANSVmFormatString. Separate temporary-string ownership from numeric length; declare after u8* fmtBuf; {"label": "format-typed-owner-4", "function": "CHANSVmFormatString", "score": 97.563805, "insns": [431, 431], "diffs": 145, "drops": [["CHANSVmFormatString", 99.84919, 97.563805]]}

- format-typed-owner-5: CHANSVmFormatString. Separate temporary-string ownership from numeric length; declare after wchar_t wideFmt[32]; {"label": "format-typed-owner-5", "function": "CHANSVmFormatString", "score": 97.563805, "insns": [431, 431], "diffs": 145, "drops": [["CHANSVmFormatString", 99.84919, 97.563805]]}

- format-typed-owner-6: CHANSVmFormatString. Separate temporary-string ownership from numeric length; declare after u32 halfMaxSize; {"label": "format-typed-owner-6", "function": "CHANSVmFormatString", "score": 97.563805, "insns": [431, 431], "diffs": 145, "drops": [["CHANSVmFormatString", 99.84919, 97.563805]]}

- format-typed-owner-7: CHANSVmFormatString. Separate temporary-string ownership from numeric length; declare after BOOL flag; {"label": "format-typed-owner-7", "function": "CHANSVmFormatString", "score": 97.563805, "insns": [431, 431], "diffs": 145, "drops": [["CHANSVmFormatString", 99.84919, 97.563805]]}

- format-typed-owner-8: CHANSVmFormatString. Separate temporary-string ownership from numeric length; declare after CHANSVmObjHdr* tempObj; {"label": "format-typed-owner-8", "function": "CHANSVmFormatString", "score": 97.563805, "insns": [431, 431], "diffs": 145, "drops": [["CHANSVmFormatString", 99.84919, 97.563805]]}

- format-typed-owner-9: CHANSVmFormatString. Separate temporary-string ownership from numeric length; declare after u32 argIdxCounter; {"label": "format-typed-owner-9", "function": "CHANSVmFormatString", "score": 97.691414, "insns": [431, 431], "diffs": 137, "drops": [["CHANSVmFormatString", 99.84919, 97.691414]]}

- format-typed-owner-10: CHANSVmFormatString. Separate temporary-string ownership from numeric length; declare after u32 totalLen; {"label": "format-typed-owner-10", "function": "CHANSVmFormatString", "score": 97.83063, "insns": [431, 431], "diffs": 129, "drops": [["CHANSVmFormatString", 99.84919, 97.83063]]}

- format-typed-owner-11: CHANSVmFormatString. Separate temporary-string ownership from numeric length; declare after u8* str; {"label": "format-typed-owner-11", "function": "CHANSVmFormatString", "score": 98.02784, "insns": [431, 431], "diffs": 128, "drops": [["CHANSVmFormatString", 99.84919, 98.02784]]}

- format-typed-owner-12: CHANSVmFormatString. Separate temporary-string ownership from numeric length; declare after u32 strLen; {"label": "format-typed-owner-12", "function": "CHANSVmFormatString", "score": 98.15545, "insns": [431, 431], "diffs": 126, "drops": [["CHANSVmFormatString", 99.84919, 98.15545]]}

- format-typed-owner-13: CHANSVmFormatString. Separate temporary-string ownership from numeric length; declare after u32 strPos; {"label": "format-typed-owner-13", "function": "CHANSVmFormatString", "score": 98.7935, "insns": [431, 431], "diffs": 87, "drops": [["CHANSVmFormatString", 99.84919, 98.7935]]}

- format-typed-owner-14: CHANSVmFormatString. Separate temporary-string ownership from numeric length; declare after u32 segStart; {"label": "format-typed-owner-14", "function": "CHANSVmFormatString", "score": 98.85151, "insns": [431, 431], "diffs": 82, "drops": [["CHANSVmFormatString", 99.84919, 98.85151]]}

- format-typed-owner-15: CHANSVmFormatString. Separate temporary-string ownership from numeric length; declare after u32 fmtBufPos; {"label": "format-typed-owner-15", "function": "CHANSVmFormatString", "score": 99.37355, "insns": [431, 431], "diffs": 48, "drops": [["CHANSVmFormatString", 99.84919, 99.37355]]}

- hex-byte-offset: VmBlobGetHexString. Make high-digit position a byte cursor matching target r4, avoiding generated induction r69. {"label": "hex-byte-offset", "function": "VmBlobGetHexString", "score": 97.37805, "insns": [82, 82], "diffs": 14, "drops": [["VmBlobGetHexString", 98.71951, 97.37805]]}

- hex-index-low-store: VmBlobGetHexString. Move real character-index update after both writes so high-nibble temporaries no longer interfere with the old index. {"label": "hex-index-low-store", "function": "VmBlobGetHexString", "score": 96.15854, "insns": [81, 82], "diffs": 33, "drops": [["VmBlobGetHexString", 98.71951, 96.15854]]}

- format-typed-owner-16: CHANSVmFormatString. Separate temporary-string ownership from numeric length; declare after u8* tmpBuf; {"label": "format-typed-owner-16", "function": "CHANSVmFormatString", "score": 99.44315, "insns": [431, 431], "diffs": 42, "drops": [["CHANSVmFormatString", 99.84919, 99.44315]]}

- hex-digits-named: VmBlobGetHexString. Explicit high digit shifts temporary creation before index arithmetic. {"label": "hex-digits-named", "function": "VmBlobGetHexString", "score": 98.71951, "insns": [82, 82], "diffs": 14, "drops": []}

- format-typed-owner-17: CHANSVmFormatString. Separate temporary-string ownership from numeric length; declare after u32 maxSize; {"label": "format-typed-owner-17", "function": "CHANSVmFormatString", "score": 99.489555, "insns": [431, 431], "diffs": 38, "drops": [["CHANSVmFormatString", 99.84919, 99.489555]]}

- hex-reuse-index: VmBlobGetHexString. Use one real character index for both digits; remove redundant high-store index. {"label": "hex-reuse-index", "function": "VmBlobGetHexString", "score": 90.060974, "insns": [83, 82], "diffs": 37, "drops": [["VmBlobGetHexString", 98.71951, 90.060974]]}

- format-typed-owner-18: CHANSVmFormatString. Separate temporary-string ownership from numeric length; declare after u8* outputBuf; {"label": "format-typed-owner-18", "function": "CHANSVmFormatString", "score": 99.59397, "insns": [431, 431], "diffs": 32, "drops": [["CHANSVmFormatString", 99.84919, 99.59397]]}

- format-typed-owner-19: CHANSVmFormatString. Separate temporary-string ownership from numeric length; declare after u32 outputPos; {"label": "format-typed-owner-19", "function": "CHANSVmFormatString", "score": 99.75638, "insns": [431, 431], "diffs": 21, "drops": [["CHANSVmFormatString", 99.84919, 99.75638]]}

- format-typed-owner-20: CHANSVmFormatString. Separate temporary-string ownership from numeric length; declare after u32 maxLitLen; {"label": "format-typed-owner-20", "function": "CHANSVmFormatString", "score": 99.84919, "insns": [431, 431], "diffs": 13, "drops": []}

- format-typed-owner-21: CHANSVmFormatString. Separate temporary-string ownership from numeric length; declare after u32 litLen; {"label": "format-typed-owner-21", "function": "CHANSVmFormatString", "score": 99.84919, "insns": [431, 431], "diffs": 13, "drops": []}

- format-typed-owner-22: CHANSVmFormatString. Separate temporary-string ownership from numeric length; declare after u32 isEscaped; {"label": "format-typed-owner-22", "function": "CHANSVmFormatString", "score": 99.84919, "insns": [431, 431], "diffs": 13, "drops": []}

- format-typed-owner-23: CHANSVmFormatString. Separate temporary-string ownership from numeric length; declare after CHANSVmObjHdr* cv; {"label": "format-typed-owner-23", "function": "CHANSVmFormatString", "score": 99.84919, "insns": [431, 431], "diffs": 13, "drops": []}

- format-typed-owner-24: CHANSVmFormatString. Separate temporary-string ownership from numeric length; declare after CHANSVmPrivate* pVm; {"label": "format-typed-owner-24", "function": "CHANSVmFormatString", "score": 99.84919, "insns": [431, 431], "diffs": 13, "drops": []}

- format-typed-owner-25: CHANSVmFormatString. Separate temporary-string ownership from numeric length; declare after CHANSVmObjHdr* argObj; {"label": "format-typed-owner-25", "function": "CHANSVmFormatString", "score": 99.84919, "insns": [431, 431], "diffs": 13, "drops": []}

- hex-direct-loop-index: VmBlobGetHexString. Derive character indices from byte ordinal; allow strength reduction to create late cursor vreg. {"label": "hex-direct-loop-index", "function": "VmBlobGetHexString", "score": 93.78049, "insns": [79, 82], "diffs": 34, "drops": [["VmBlobGetHexString", 98.71951, 93.78049]]}

- hex-low-index-reused: VmBlobGetHexString. Carry odd character position directly instead of temporary idx2. {"label": "hex-low-index-reused", "function": "VmBlobGetHexString", "score": 97.48781, "insns": [81, 82], "diffs": 33, "drops": [["VmBlobGetHexString", 98.71951, 97.48781]]}

- hex-index-from-dest: VmBlobGetHexString. Use actual destination character index for both writes, preserving original update positions. {"label": "hex-index-from-dest", "function": "VmBlobGetHexString", "score": 98.71951, "insns": [82, 82], "diffs": 14, "drops": []}

- hex-descending-count: VmBlobGetHexString. Explicit countdown loop matches target CTR count and may renumber induction temporaries. {"label": "hex-descending-count", "function": "VmBlobGetHexString", "score": 97.92683, "insns": [82, 82], "diffs": 16, "drops": [["VmBlobGetHexString", 98.71951, 97.92683]]}

## VmBlobGetHexString baseline allocator

Target high-digit byte offset is r4, low-digit character cursor r5, input byte pointer r6, digit temporaries r7, table r8. Baseline strength reduction synthesizes byte offset r69, colored second to r4, while all digit temporaries r55-r64 color earlier than named destOff r39 and take r5. Input r41 then takes r6 and destOff r39 gets r7. Named i r38 is dead: common induction analysis merged it into destOff, so moving i alone cannot change allocation. No useful coalesces or spills. Testing explicit byte indexing, a direct ordinal index, odd-index induction, and countdown while preserving each original byte read.

- split-separate-elements: VmStringSplit. Target matched-segment header r26 and tail header r25 are separate lifetimes; expose separate semantic names. {"label": "split-separate-elements", "function": "VmStringSplit", "score": 97.9054, "insns": [222, 222], "diffs": 75, "drops": [["VmStringSplit", 98.04054, 97.9054]]}

- split-tail-length-local: VmStringSplit. Target tail length r26 differs from middle-segment length r19; narrow scope to create its own local lifetime. {"label": "split-tail-length-local", "function": "VmStringSplit", "score": 98.04054, "insns": [222, 222], "diffs": 66, "drops": []}

- split-byte-count-order: VmStringSplit. Move count last among traversal state so reverse local numbering can claim target r29. {"label": "split-byte-count-order", "function": "VmStringSplit", "score": 98.04054, "insns": [222, 222], "diffs": 66, "drops": []}

- split-inputs-grouped: VmStringSplit. Group each string pointer and length; target delimiters r21/r22 and parent length r24. {"label": "split-inputs-grouped", "function": "VmStringSplit", "score": 97.927925, "insns": [222, 222], "diffs": 69, "drops": [["VmStringSplit", 98.04054, 97.927925]]}

- hex-reused-digit-19-s32: VmBlobGetHexString. Reuse one named nibble conversion local through both reads to move digit coloring after induction state. {"label": "hex-reused-digit-19-s32", "function": "VmBlobGetHexString", "score": 98.71951, "insns": [82, 82], "diffs": 14, "drops": []}

- hex-reused-digit-19-u32: VmBlobGetHexString. Reuse one named nibble conversion local through both reads to move digit coloring after induction state. {"label": "hex-reused-digit-19-u32", "function": "VmBlobGetHexString", "score": 98.71951, "insns": [82, 82], "diffs": 14, "drops": []}

- hex-reused-digit-66-s32: VmBlobGetHexString. Reuse one named nibble conversion local through both reads to move digit coloring after induction state. {"label": "hex-reused-digit-66-s32", "function": "VmBlobGetHexString", "score": 98.71951, "insns": [82, 82], "diffs": 14, "drops": []}

- hex-reused-digit-66-u32: VmBlobGetHexString. Reuse one named nibble conversion local through both reads to move digit coloring after induction state. {"label": "hex-reused-digit-66-u32", "function": "VmBlobGetHexString", "score": 98.71951, "insns": [82, 82], "diffs": 14, "drops": []}

- hex-reused-digit-18-s32: VmBlobGetHexString. Reuse one named nibble conversion local through both reads to move digit coloring after induction state. {"label": "hex-reused-digit-18-s32", "function": "VmBlobGetHexString", "score": 98.71951, "insns": [82, 82], "diffs": 14, "drops": []}

- hex-reused-digit-18-u32: VmBlobGetHexString. Reuse one named nibble conversion local through both reads to move digit coloring after induction state. {"label": "hex-reused-digit-18-u32", "function": "VmBlobGetHexString", "score": 98.71951, "insns": [82, 82], "diffs": 14, "drops": []}

- assoc-reuse-address: ATERMBuildAssociationRequest. Use a natural helper-local lifetime change; all helper callers measured for regressions. {"label": "assoc-reuse-address", "function": "ATERMBuildAssociationRequest", "score": 97.55639, "insns": [133, 133], "diffs": 50, "drops": [["ATERMDiscoverAccessPoints", 98.31939, 98.015205], ["ATERMBuildAssociationRequest", 98.7594, 97.55639]]}

- assoc-pointer-output-last: ATERMBuildAssociationRequest. Use a natural helper-local lifetime change; all helper callers measured for regressions. {"label": "assoc-pointer-output-last", "function": "ATERMBuildAssociationRequest", "score": 97.55639, "insns": [133, 133], "diffs": 50, "drops": [["ATERMDiscoverAccessPoints", 98.31939, 98.015205], ["ATERMBuildAssociationRequest", 98.7594, 97.55639]]}

## VmStringSplit baseline allocator

Target VmInst r27, parent r29, return r28; delimiter header initially r31, limit r30; parent data r31 and length r24, delimiter data r21 and length r22; output array r20, count r29, source offset r25, segment start r23, segment length r19, element r26. Baseline final GPR pass1 instead colors limit r47 first->r31, parentStr r45 second->r30, return r34 third->r29, parent r33 fourth->r28, vm r32 fifth->r27. Their initial edges41/39/43/35/53 and final simplify degrees12/13/14/15/16 show a pressure core deferred until short-lived values disappear. Segment variables then reuse the available saved colors according to reverse IDs; separate middle/tail element locals changes this ordering but regresses75 diffs. Next tests move limit relative to the input pointers and array/count relative to the loop state, keeping caller argument order intact.

- split-limit-after-parent: VmStringSplit. Allocator-guided ordering: reverse the limiting core or move count/array across the input lifetimes. {"label": "split-limit-after-parent", "function": "VmStringSplit", "score": 98.28829, "insns": [222, 222], "diffs": 62, "drops": []}

- split-limit-after-delimiter: VmStringSplit. Allocator-guided ordering: reverse the limiting core or move count/array across the input lifetimes. {"label": "split-limit-after-delimiter", "function": "VmStringSplit", "score": 98.28829, "insns": [222, 222], "diffs": 62, "drops": []}

- split-array-before-count: VmStringSplit. Allocator-guided ordering: reverse the limiting core or move count/array across the input lifetimes. {"label": "split-array-before-count", "function": "VmStringSplit", "score": 97.9054, "insns": [222, 222], "diffs": 75, "drops": [["VmStringSplit", 98.04054, 97.9054]]}

- split-count-before-inputs: VmStringSplit. Allocator-guided ordering: reverse the limiting core or move count/array across the input lifetimes. {"label": "split-count-before-inputs", "function": "VmStringSplit", "score": 98.04054, "insns": [222, 222], "diffs": 67, "drops": []}

- split-limit-first: VmStringSplit. Move limit across the 29-color pressure core relative to parentStr. {"label": "split-limit-first", "function": "VmStringSplit", "score": 98.04054, "insns": [222, 222], "diffs": 66, "drops": []}

- split-limit-last: VmStringSplit. Move limit across the 29-color pressure core relative to parentStr. {"label": "split-limit-last", "function": "VmStringSplit", "score": 98.28829, "insns": [222, 222], "diffs": 62, "drops": []}

- aes-swap-first-second-declarations: ATERMAesExpandEncryptKey. Target first word occupies r27 and second r10; source swaps the first two initial load trees. {"label": "aes-swap-first-second-declarations", "function": "ATERMAesExpandEncryptKey", "score": 98.94403, "insns": [268, 268], "diffs": 49, "drops": []}

- aes-reuse-first-word: ATERMAesExpandEncryptKey. Use first key word as the later expansion scratch after its initial store; genuine non-overlapping values. {"label": "aes-reuse-first-word", "function": "ATERMAesExpandEncryptKey", "score": 98.94403, "insns": [268, 268], "diffs": 49, "drops": []}

- aes-declare-key-pointers-last: ATERMAesExpandEncryptKey. Move pointer declarations after scalar key state to test transient expression vreg ordering. {"label": "aes-declare-key-pointers-last", "function": "ATERMAesExpandEncryptKey", "score": 98.94403, "insns": [268, 268], "diffs": 49, "drops": []}

- aes-read-word-helper: ATERMAesExpandEncryptKey. Plain big-endian word reader moves each initial expression across an inline boundary. {"label": "aes-read-word-helper", "function": "ATERMAesExpandEncryptKey", "score": 98.75746, "insns": [268, 268], "diffs": 53, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.75746]]}

- split-target-order-0: VmStringSplit. Order loop state according to the target saved-register ownership; preserve every statement. {"label": "split-target-order-0", "function": "VmStringSplit", "score": 98.175674, "insns": [222, 222], "diffs": 65, "drops": []}

- assoc-nibble-initializer: ATERMBuildAssociationRequest. Initialize nibble pair in natural order; array is real conversion data, no carrier. {"label": "assoc-nibble-initializer", "function": "ATERMBuildAssociationRequest", "error": "### mwcceppc.exe Compiler:\n#    File: build\\rx1\\trials\\assoc-nibble-initializer\\ATERM.c\n# ----------------------------------------------------------\n#     859:     s32 nibbles[2] = {(byte & 0xF0) >> 4, byte & 0xF}; \n#   Error:                                                      ^\n#   (10124) illegal constant expression\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\n"}

- assoc-low-before-high: ATERMBuildAssociationRequest. Independent nibble assignments in low/high order changes creation order. {"label": "assoc-low-before-high", "function": "ATERMBuildAssociationRequest", "score": 98.233086, "insns": [133, 133], "diffs": 40, "drops": [["ATERMDiscoverAccessPoints", 98.31939, 98.05323], ["ATERMBuildAssociationRequest", 98.7594, 98.233086]]}

- split-target-order-1: VmStringSplit. Order loop state according to the target saved-register ownership; preserve every statement. {"label": "split-target-order-1", "function": "VmStringSplit", "score": 97.65766, "insns": [222, 222], "diffs": 82, "drops": [["VmStringSplit", 98.04054, 97.65766]]}

- assoc-byte-parameter-reused: ATERMBuildAssociationRequest. Consume byte parameter in the high-nibble extraction after saving low nibble. {"label": "assoc-byte-parameter-reused", "function": "ATERMBuildAssociationRequest", "score": 98.08271, "insns": [133, 133], "diffs": 40, "drops": [["ATERMDiscoverAccessPoints", 98.31939, 98.015205], ["ATERMBuildAssociationRequest", 98.7594, 98.08271]]}

- split-target-order-2: VmStringSplit. Order loop state according to the target saved-register ownership; preserve every statement. {"label": "split-target-order-2", "function": "VmStringSplit", "score": 97.65766, "insns": [222, 222], "diffs": 82, "drops": [["VmStringSplit", 98.04054, 97.65766]]}

- nup-reuse-closing-cursor: __nupParseServerInfo__FP14NUPContextInfoPcPcUx. Closing search cursor is reused as the returned post-tag cursor; two semantic definitions may keep named end instead of anonymous r114. {"label": "nup-reuse-closing-cursor", "function": "__nupParseServerInfo__FP14NUPContextInfoPcPcUx", "score": 99.26991, "insns": [452, 452], "diffs": 66, "drops": []}

- nup-reuse-closing-assignment: __nupParseServerInfo__FP14NUPContextInfoPcPcUx. Same cursor reuse with explicit assignment. {"label": "nup-reuse-closing-assignment", "function": "__nupParseServerInfo__FP14NUPContextInfoPcPcUx", "score": 99.26991, "insns": [452, 452], "diffs": 66, "drops": []}

- nup-reuse-both-cursors: __nupParseServerInfo__FP14NUPContextInfoPcPcUx. Advance both real tag cursors rather than producing fresh return expressions. {"label": "nup-reuse-both-cursors", "function": "__nupParseServerInfo__FP14NUPContextInfoPcPcUx", "score": 97.31195, "insns": [460, 452], "diffs": 389, "drops": [["__nupParseServerInfo__FP14NUPContextInfoPcPcUx", 99.26991, 97.31195]]}

Allocator confirmation write-result-reuse: capture `build/rx1/mwdbg-write-result-reuse`, whole-object equality with normal compiler True.

- split-model-5: VmStringSplit. Declaration order predicted by a graph model that exactly reproduces baseline allocator decisions; predicted mismatch count 5 {"label": "split-model-5", "function": "VmStringSplit", "score": 99.324326, "insns": [222, 222], "diffs": 26, "drops": []}

- split-model-3: VmStringSplit. Declaration order predicted by a graph model that exactly reproduces baseline allocator decisions; predicted mismatch count 3 {"label": "split-model-3", "function": "VmStringSplit", "score": 99.54955, "insns": [222, 222], "diffs": 19, "drops": []}

- split-model-2: VmStringSplit. Declaration order predicted by a graph model that exactly reproduces baseline allocator decisions; predicted mismatch count 2 {"label": "split-model-2", "function": "VmStringSplit", "score": 99.54955, "insns": [222, 222], "diffs": 19, "drops": []}

- split-model-count: VmStringSplit. Use the existing element count for the empty-delimiter path; target carries the index in the same r29. {"label": "split-model-count", "function": "VmStringSplit", "score": 99.72973, "insns": [222, 222], "diffs": 12, "drops": []}

- split-model-tail-scope: VmStringSplit. Scope the tail length while retaining modeled declaration order. {"label": "split-model-tail-scope", "function": "VmStringSplit", "score": 98.24324, "insns": [222, 222], "diffs": 63, "drops": []}

- split-model-load-order: VmStringSplit. Swap independent input data loads to alter r3/r4 header temporary numbering. {"label": "split-model-load-order", "function": "VmStringSplit", "score": 99.54955, "insns": [222, 222], "diffs": 19, "drops": []}

## Allocator model validation

A scratch graph-coloring model reproduces every recorded simplify priority and final GPR color for VmWinEmuWrite, VmBlobGetHexString, VmStringSplit, and ATERMBuildAssociationRequest. It scans virtual IDs ascending, repeatedly removes degree<29 nodes, colors in reverse removal order, chooses the lowest available color in the current pool, and requests saved registers from r31 down only when no existing color is legal. Coalesced nodes use the recorded representative graph. This is a diagnostic model, never emitted code. Virtual-ID permutations predict declarations before compiling.

For Split, a predicted order compiled to99.549550%,222/222 instructions,19 diffs, no unit drops, down from66 baseline diffs. The model fixed the parent/return swap and most loop variables. Remaining groups: six r3/r4 input-header temporary differences, six tail-length/element r25/r26 differences, seven empty-delimiter counter/header differences. This confirms that some historical register ties are source-numbering problems, but this result remains nonexact and will not be retained alone.

## ATERMBuildAssociationRequest baseline allocator

Target both MAC readers use r5 for input, r8 for output, r7 for count, r9 for low nibble; high nibble/output cursor uses r6. First low nibble source r68 gets r5 at priority28, while input r43 degree14 is colored later at priority53 and gets r9. Second input r36 also gets r9 at priority60; low nibble r82 gets r4 at priority14, high nibble r80 gets r5 at priority16, and zero r76 gets r6 at priority20. Inline nibble-array unrolling creates the high/low temporaries after the named input pointer. No accepted coalesces or spills. Model exactly reproduces all GPR choices. Reusing helper input parameter and moving output declaration each regressed50 diffs and affected DiscoverAccessPoints; swapping independent nibble assignments regressed40 diffs. All rejected source copies remain under build/rx1 only.

- split-tail-length-expression: VmStringSplit. Remove cached tail length so CSE may create a later anonymous value and color it before the element result. {"label": "split-tail-length-expression", "function": "VmStringSplit", "score": 98.063065, "insns": [222, 222], "diffs": 17, "drops": []}

- split-input-header-locals: VmStringSplit. Explicit typed header views give the two short-lived field bases independent source IDs. {"label": "split-input-header-locals", "function": "VmStringSplit", "score": 99.72973, "insns": [222, 222], "diffs": 12, "drops": []}

- split-tail-before-element: VmStringSplit. Place tail length beside its actual output object in the successful modeled state. {"label": "split-tail-before-element", "function": "VmStringSplit", "score": 99.054054, "insns": [222, 222], "diffs": 31, "drops": []}

- split-input-order-1: VmStringSplit. Independent input field evaluation order targets the r3/r4 base pair. {"label": "split-input-order-1", "function": "VmStringSplit", "score": 99.86487, "insns": [222, 222], "diffs": 6, "drops": []}

- split-input-order-2: VmStringSplit. Independent input field evaluation order targets the r3/r4 base pair. {"label": "split-input-order-2", "function": "VmStringSplit", "score": 99.72072, "insns": [222, 222], "diffs": 12, "drops": []}

- split-input-order-3: VmStringSplit. Independent input field evaluation order targets the r3/r4 base pair. {"label": "split-input-order-3", "function": "VmStringSplit", "score": 99.72072, "insns": [222, 222], "diffs": 12, "drops": []}

- split-input-order-4: VmStringSplit. Independent input field evaluation order targets the r3/r4 base pair. {"label": "split-input-order-4", "function": "VmStringSplit", "score": 99.86487, "insns": [222, 222], "diffs": 6, "drops": []}

- split-input-order-5: VmStringSplit. Independent input field evaluation order targets the r3/r4 base pair. {"label": "split-input-order-5", "function": "VmStringSplit", "score": 99.72072, "insns": [222, 222], "diffs": 12, "drops": []}

- split-input-order-6: VmStringSplit. Independent input field evaluation order targets the r3/r4 base pair. {"label": "split-input-order-6", "function": "VmStringSplit", "score": 99.72973, "insns": [222, 222], "diffs": 12, "drops": []}

- split-input-order-7: VmStringSplit. Independent input field evaluation order targets the r3/r4 base pair. {"label": "split-input-order-7", "function": "VmStringSplit", "score": 99.77477, "insns": [222, 222], "diffs": 8, "drops": []}

- split-input-order-8: VmStringSplit. Independent input field evaluation order targets the r3/r4 base pair. {"label": "split-input-order-8", "function": "VmStringSplit", "score": 99.6982, "insns": [222, 222], "diffs": 12, "drops": []}

- split-input-order-9: VmStringSplit. Independent input field evaluation order targets the r3/r4 base pair. {"label": "split-input-order-9", "function": "VmStringSplit", "score": 99.74324, "insns": [222, 222], "diffs": 9, "drops": []}

- split-input-order-10: VmStringSplit. Independent input field evaluation order targets the r3/r4 base pair. {"label": "split-input-order-10", "function": "VmStringSplit", "score": 99.77477, "insns": [222, 222], "diffs": 8, "drops": []}

- split-input-order-11: VmStringSplit. Independent input field evaluation order targets the r3/r4 base pair. {"label": "split-input-order-11", "function": "VmStringSplit", "score": 99.74324, "insns": [222, 222], "diffs": 9, "drops": []}

- split-input-order-12: VmStringSplit. Independent input field evaluation order targets the r3/r4 base pair. {"label": "split-input-order-12", "function": "VmStringSplit", "score": 99.6982, "insns": [222, 222], "diffs": 12, "drops": []}

- split-input-order-13: VmStringSplit. Independent input field evaluation order targets the r3/r4 base pair. {"label": "split-input-order-13", "function": "VmStringSplit", "score": 99.6982, "insns": [222, 222], "diffs": 12, "drops": []}

- split-input-order-14: VmStringSplit. Independent input field evaluation order targets the r3/r4 base pair. {"label": "split-input-order-14", "function": "VmStringSplit", "score": 99.675674, "insns": [222, 222], "diffs": 12, "drops": []}

- split-input-order-15: VmStringSplit. Independent input field evaluation order targets the r3/r4 base pair. {"label": "split-input-order-15", "function": "VmStringSplit", "score": 99.810814, "insns": [222, 222], "diffs": 8, "drops": []}

- split-input-order-16: VmStringSplit. Independent input field evaluation order targets the r3/r4 base pair. {"label": "split-input-order-16", "function": "VmStringSplit", "score": 99.6982, "insns": [222, 222], "diffs": 12, "drops": []}

- split-input-order-17: VmStringSplit. Independent input field evaluation order targets the r3/r4 base pair. {"label": "split-input-order-17", "function": "VmStringSplit", "score": 99.810814, "insns": [222, 222], "diffs": 8, "drops": []}

- split-input-order-18: VmStringSplit. Independent input field evaluation order targets the r3/r4 base pair. {"label": "split-input-order-18", "function": "VmStringSplit", "score": 99.86487, "insns": [222, 222], "diffs": 6, "drops": []}

- split-input-order-19: VmStringSplit. Independent input field evaluation order targets the r3/r4 base pair. {"label": "split-input-order-19", "function": "VmStringSplit", "score": 99.72072, "insns": [222, 222], "diffs": 12, "drops": []}

- split-input-order-20: VmStringSplit. Independent input field evaluation order targets the r3/r4 base pair. {"label": "split-input-order-20", "function": "VmStringSplit", "score": 99.77477, "insns": [222, 222], "diffs": 8, "drops": []}

- split-input-order-21: VmStringSplit. Independent input field evaluation order targets the r3/r4 base pair. {"label": "split-input-order-21", "function": "VmStringSplit", "score": 99.74324, "insns": [222, 222], "diffs": 9, "drops": []}

- split-input-order-22: VmStringSplit. Independent input field evaluation order targets the r3/r4 base pair. {"label": "split-input-order-22", "function": "VmStringSplit", "score": 99.6982, "insns": [222, 222], "diffs": 12, "drops": []}

- hex-post-index: VmBlobGetHexString. Use one character index advanced after each digit store; count and loaded bytes unchanged. {"label": "hex-post-index", "function": "VmBlobGetHexString", "score": 92.243904, "insns": [79, 82], "diffs": 35, "drops": [["VmBlobGetHexString", 98.71951, 92.243904]]}

- split-input-order-23: VmStringSplit. Independent input field evaluation order targets the r3/r4 base pair. {"label": "split-input-order-23", "function": "VmStringSplit", "score": 99.810814, "insns": [222, 222], "diffs": 8, "drops": []}

- hex-ulong-dest: VmBlobGetHexString. Equivalent unsigned 32-bit typedef family may affect induction equivalence. {"label": "hex-ulong-dest", "function": "VmBlobGetHexString", "score": 98.71951, "insns": [82, 82], "diffs": 14, "drops": []}

- hex-ulong-i: VmBlobGetHexString. Change only the identical-width unsigned low-digit cursor type. {"label": "hex-ulong-i", "function": "VmBlobGetHexString", "score": 98.71951, "insns": [82, 82], "diffs": 14, "drops": []}

- hex-const-source: VmBlobGetHexString. Read-only byte pointer may keep a distinct induction expression. {"label": "hex-const-source", "function": "VmBlobGetHexString", "score": 98.71951, "insns": [82, 82], "diffs": 14, "drops": []}

- hex-const-table: VmBlobGetHexString. Read-only table pointer changes alias type without changing data. {"label": "hex-const-table", "function": "VmBlobGetHexString", "score": 98.71951, "insns": [82, 82], "diffs": 14, "drops": []}

- split-tail-helper-standard: VmStringSplit. Evaluate tail span as a real inline argument before the array guard; target length color is now an expression temporary. {"label": "split-tail-helper-standard", "function": "VmStringSplit", "score": 93.96397, "insns": [227, 222], "diffs": 165, "drops": [["VmStringSplit", 98.04054, 93.96397]]}

- split-tail-helper-length-first: VmStringSplit. Evaluate tail span as a real inline argument before the array guard; target length color is now an expression temporary. {"label": "split-tail-helper-length-first", "function": "VmStringSplit", "score": 93.96397, "insns": [227, 222], "diffs": 165, "drops": [["VmStringSplit", 98.04054, 93.96397]]}

- split-tail-helper-length-after-vm: VmStringSplit. Evaluate tail span as a real inline argument before the array guard; target length color is now an expression temporary. {"label": "split-tail-helper-length-after-vm", "function": "VmStringSplit", "score": 93.96397, "insns": [227, 222], "diffs": 165, "drops": [["VmStringSplit", 98.04054, 93.96397]]}

- split-tail-const-length: VmStringSplit. Const tail length at first use may preserve an expression temporary instead of mutable named state. {"label": "split-tail-const-length", "function": "VmStringSplit", "score": 98.558556, "insns": [222, 222], "diffs": 54, "drops": []}

- split-tail-retain-length: VmStringSplit. Two real length assignments make liveness explicit. {"label": "split-tail-retain-length", "function": "VmStringSplit", "score": 99.86487, "insns": [222, 222], "diffs": 6, "drops": []}

- split-tail-reuse-argument: VmStringSplit. Reuse the consumed string argument header as tail string object, with no pointer/integer cast. {"label": "split-tail-reuse-argument", "function": "VmStringSplit", "score": 99.86487, "insns": [222, 222], "diffs": 6, "drops": []}

- split-tail-separate-result: VmStringSplit. Separate middle and tail headers within the improved declaration state. {"label": "split-tail-separate-result", "function": "VmStringSplit", "score": 99.25676, "insns": [222, 222], "diffs": 26, "drops": []}

- split-tail-length-inline-plain: VmStringSplit. Use a plain substring-length helper to test temporary creation across the inline boundary. {"label": "split-tail-length-inline-plain", "function": "VmStringSplit", "score": 100.0, "insns": [222, 222], "diffs": 0, "drops": []}

- split-tail-length-inline-const-param: VmStringSplit. Use a plain substring-length helper to test temporary creation across the inline boundary. {"label": "split-tail-length-inline-const-param", "function": "VmStringSplit", "score": 100.0, "insns": [222, 222], "diffs": 0, "drops": []}

- split-tail-length-inline-twostep: VmStringSplit. Use a plain substring-length helper to test temporary creation across the inline boundary. {"label": "split-tail-length-inline-twostep", "function": "VmStringSplit", "score": 100.0, "insns": [222, 222], "diffs": 0, "drops": []}

Split improvement sequence: modeled declarations99.549550%/19 diffs, real counter reuse99.729730%/12 diffs, natural parent/delimiter field assignment order99.864870%/6 diffs. Input order is parent data, delimiter data, delimiter length, parent length. Remaining six differences exclusively swap tail length r25/r26 with returned tail-element pointer. Removing cached tail length gets the target registers but moves the subtraction across the null-array branch, so it is rejected. A separate named tail element obtains target length r26 but shifts other colors; its allocator capture supersedes the queued19-diff capture. Plain helpers and const length failed to match; all remain scratch candidates.

- split-tail-comma-guard: VmStringSplit. Bind tail span in the same guard expression, preserving unconditional evaluation. {"label": "split-tail-comma-guard", "function": "VmStringSplit", "score": 99.86487, "insns": [222, 222], "diffs": 6, "drops": []}

- split-tail-full-expression: VmStringSplit. Equivalent unsigned difference tests lowering into expression vs named state. {"label": "split-tail-full-expression", "function": "VmStringSplit", "score": 99.86487, "insns": [222, 222], "diffs": 6, "drops": []}

- split-tail-u32-return: VmStringSplit. Use the memcpy length type for tail bytes, same unsigned 32-bit semantics. {"label": "split-tail-u32-return", "function": "VmStringSplit", "score": 99.86487, "insns": [222, 222], "diffs": 6, "drops": []}

- split-tail-getter-separate-guard: VmStringSplit. Separate the two failure guards to test copy propagation and the tail-header virtual register. {"label": "split-tail-getter-separate-guard", "function": "VmStringSplit", "score": 99.86487, "insns": [222, 222], "diffs": 6, "drops": []}

Write confirmation: raw-then-converted strObj source still creates an anonymous converted-header value, now r41 instead of r40. It colors to r29; totalLength remains r35->r27, offset r36->r28, VM r32->r27. Whole debugger object equals the normal trial object. Source-level object reuse alone did not keep the named value live. The allocator explanation is confirmed, not inferred from register spellings alone.

- split-tail-owner-order-1: VmStringSplit. Place the independent tail header after u32 remaining;, preserving all modeled state declarations. {"label": "split-tail-owner-order-1", "function": "VmStringSplit", "score": 100.0, "insns": [222, 222], "diffs": 0, "drops": []}

Allocator confirmation format-typed-owner-20: capture `build/rx1/mwdbg-format-typed-owner-20`, whole-object equality with normal compiler True.

- nup-mutable-tag-start: __nupParseServerInfo__FP14NUPContextInfoPcPcUx. Use an ordinary mutable string parameter, which leaves bytes/calls unchanged but alters inline parameter typing. {"label": "nup-mutable-tag-start", "function": "__nupParseServerInfo__FP14NUPContextInfoPcPcUx", "score": 99.26991, "insns": [452, 452], "diffs": 66, "drops": []}

- nup-mutable-tag-end: __nupParseServerInfo__FP14NUPContextInfoPcPcUx. Use an ordinary mutable string parameter, which leaves bytes/calls unchanged but alters inline parameter typing. {"label": "nup-mutable-tag-end", "function": "__nupParseServerInfo__FP14NUPContextInfoPcPcUx", "score": 99.26991, "insns": [452, 452], "diffs": 66, "drops": []}

- nup-mutable-tag-both: __nupParseServerInfo__FP14NUPContextInfoPcPcUx. Use an ordinary mutable string parameter, which leaves bytes/calls unchanged but alters inline parameter typing. {"label": "nup-mutable-tag-both", "function": "__nupParseServerInfo__FP14NUPContextInfoPcPcUx", "score": 99.26991, "insns": [452, 452], "diffs": 66, "drops": []}

## Exact VmStringSplit candidate

`split-tail-owner-order-1`:100.000000%,222/222 instructions,ctxdiff0,no unit score drops. Real source changes: declare the separate tail header alongside its byte length, put saved state in the model-predicted declaration order, load delimiter length before parent length, and reuse the existing count in the empty-delimiter loop. No new casts, carrier structs, helpers, comments, or assembly. All three changes preserve values, call order, and memory accesses. Tail element owns only the final segment; count is reset before its disjoint empty-delimiter use. Fresh normal Ninja object and pool checks are required below. Superseded Split source searches stopped after this exact candidate; remaining functions continue their1200-second searches.

- write-const-object: VmWinEmuWrite. Test genuine constness of the converted header or binding without VM casts or artificial state. {"label": "write-const-object", "function": "VmWinEmuWrite", "score": 99.62687, "insns": [67, 67], "diffs": 5, "drops": []}

- write-const-binding: VmWinEmuWrite. Test genuine constness of the converted header or binding without VM casts or artificial state. {"label": "write-const-binding", "function": "VmWinEmuWrite", "score": 99.62687, "insns": [67, 67], "diffs": 5, "drops": []}

- write-const-binding-first: VmWinEmuWrite. Test genuine constness of the converted header or binding without VM casts or artificial state. {"label": "write-const-binding-first", "function": "VmWinEmuWrite", "score": 99.62687, "insns": [67, 67], "diffs": 5, "drops": []}

- aes-store-order-0132: ATERMAesExpandEncryptKey. All initial key bytes are read into real words before any output store; reorder four independent word stores to test which expression survives propagation. {"label": "aes-store-order-0132", "function": "ATERMAesExpandEncryptKey", "score": 98.95522, "insns": [268, 268], "diffs": 49, "drops": []}

- aes-store-order-0213: ATERMAesExpandEncryptKey. All initial key bytes are read into real words before any output store; reorder four independent word stores to test which expression survives propagation. {"label": "aes-store-order-0213", "function": "ATERMAesExpandEncryptKey", "score": 97.89552, "insns": [268, 268], "diffs": 56, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 97.89552]]}

- aes-store-order-0231: ATERMAesExpandEncryptKey. All initial key bytes are read into real words before any output store; reorder four independent word stores to test which expression survives propagation. {"label": "aes-store-order-0231", "function": "ATERMAesExpandEncryptKey", "score": 97.910446, "insns": [268, 268], "diffs": 56, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 97.910446]]}

- aes-store-order-0312: ATERMAesExpandEncryptKey. All initial key bytes are read into real words before any output store; reorder four independent word stores to test which expression survives propagation. {"label": "aes-store-order-0312", "function": "ATERMAesExpandEncryptKey", "score": 98.95522, "insns": [268, 268], "diffs": 49, "drops": []}

- aes-store-order-0321: ATERMAesExpandEncryptKey. All initial key bytes are read into real words before any output store; reorder four independent word stores to test which expression survives propagation. {"label": "aes-store-order-0321", "function": "ATERMAesExpandEncryptKey", "score": 97.910446, "insns": [268, 268], "diffs": 56, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 97.910446]]}

- aes-store-order-1023: ATERMAesExpandEncryptKey. All initial key bytes are read into real words before any output store; reorder four independent word stores to test which expression survives propagation. {"label": "aes-store-order-1023", "function": "ATERMAesExpandEncryptKey", "score": 98.966415, "insns": [268, 268], "diffs": 45, "drops": []}

- aes-store-order-1032: ATERMAesExpandEncryptKey. All initial key bytes are read into real words before any output store; reorder four independent word stores to test which expression survives propagation. {"label": "aes-store-order-1032", "function": "ATERMAesExpandEncryptKey", "score": 98.977615, "insns": [268, 268], "diffs": 45, "drops": []}

- aes-store-order-1203: ATERMAesExpandEncryptKey. All initial key bytes are read into real words before any output store; reorder four independent word stores to test which expression survives propagation. {"label": "aes-store-order-1203", "function": "ATERMAesExpandEncryptKey", "score": 97.91418, "insns": [268, 268], "diffs": 52, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 97.91418]]}

- aes-store-order-1230: ATERMAesExpandEncryptKey. All initial key bytes are read into real words before any output store; reorder four independent word stores to test which expression survives propagation. {"label": "aes-store-order-1230", "function": "ATERMAesExpandEncryptKey", "score": 97.92911, "insns": [268, 268], "diffs": 52, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 97.92911]]}

- aes-store-order-1302: ATERMAesExpandEncryptKey. All initial key bytes are read into real words before any output store; reorder four independent word stores to test which expression survives propagation. {"label": "aes-store-order-1302", "function": "ATERMAesExpandEncryptKey", "score": 98.977615, "insns": [268, 268], "diffs": 45, "drops": []}

- aes-store-order-1320: ATERMAesExpandEncryptKey. All initial key bytes are read into real words before any output store; reorder four independent word stores to test which expression survives propagation. {"label": "aes-store-order-1320", "function": "ATERMAesExpandEncryptKey", "score": 97.92911, "insns": [268, 268], "diffs": 52, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 97.92911]]}

- aes-store-order-2013: ATERMAesExpandEncryptKey. All initial key bytes are read into real words before any output store; reorder four independent word stores to test which expression survives propagation. {"label": "aes-store-order-2013", "function": "ATERMAesExpandEncryptKey", "score": 98.97388, "insns": [268, 268], "diffs": 41, "drops": []}

- aes-store-order-2031: ATERMAesExpandEncryptKey. All initial key bytes are read into real words before any output store; reorder four independent word stores to test which expression survives propagation. {"label": "aes-store-order-2031", "function": "ATERMAesExpandEncryptKey", "score": 98.98881, "insns": [268, 268], "diffs": 41, "drops": []}

- aes-store-order-2103: ATERMAesExpandEncryptKey. All initial key bytes are read into real words before any output store; reorder four independent word stores to test which expression survives propagation. {"label": "aes-store-order-2103", "function": "ATERMAesExpandEncryptKey", "score": 97.92538, "insns": [268, 268], "diffs": 48, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 97.92538]]}

- aes-store-order-2130: ATERMAesExpandEncryptKey. All initial key bytes are read into real words before any output store; reorder four independent word stores to test which expression survives propagation. {"label": "aes-store-order-2130", "function": "ATERMAesExpandEncryptKey", "score": 97.9403, "insns": [268, 268], "diffs": 48, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 97.9403]]}

- aes-store-order-2301: ATERMAesExpandEncryptKey. All initial key bytes are read into real words before any output store; reorder four independent word stores to test which expression survives propagation. {"label": "aes-store-order-2301", "function": "ATERMAesExpandEncryptKey", "score": 98.98881, "insns": [268, 268], "diffs": 41, "drops": []}

- aes-store-order-2310: ATERMAesExpandEncryptKey. All initial key bytes are read into real words before any output store; reorder four independent word stores to test which expression survives propagation. {"label": "aes-store-order-2310", "function": "ATERMAesExpandEncryptKey", "score": 97.9403, "insns": [268, 268], "diffs": 48, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 97.9403]]}

- aes-store-order-3012: ATERMAesExpandEncryptKey. All initial key bytes are read into real words before any output store; reorder four independent word stores to test which expression survives propagation. {"label": "aes-store-order-3012", "function": "ATERMAesExpandEncryptKey", "score": 98.81343, "insns": [268, 268], "diffs": 38, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.81343]]}

- aes-store-order-3021: ATERMAesExpandEncryptKey. All initial key bytes are read into real words before any output store; reorder four independent word stores to test which expression survives propagation. {"label": "aes-store-order-3021", "function": "ATERMAesExpandEncryptKey", "score": 98.79851, "insns": [268, 268], "diffs": 38, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.79851]]}

- aes-store-order-3102: ATERMAesExpandEncryptKey. All initial key bytes are read into real words before any output store; reorder four independent word stores to test which expression survives propagation. {"label": "aes-store-order-3102", "function": "ATERMAesExpandEncryptKey", "score": 97.95149, "insns": [268, 268], "diffs": 40, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 97.95149]]}

- aes-store-order-3120: ATERMAesExpandEncryptKey. All initial key bytes are read into real words before any output store; reorder four independent word stores to test which expression survives propagation. {"label": "aes-store-order-3120", "function": "ATERMAesExpandEncryptKey", "score": 97.97388, "insns": [268, 268], "diffs": 39, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 97.97388]]}

- aes-store-order-3201: ATERMAesExpandEncryptKey. All initial key bytes are read into real words before any output store; reorder four independent word stores to test which expression survives propagation. {"label": "aes-store-order-3201", "function": "ATERMAesExpandEncryptKey", "score": 98.79851, "insns": [268, 268], "diffs": 38, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.79851]]}

- aes-store-order-3210: ATERMAesExpandEncryptKey. All initial key bytes are read into real words before any output store; reorder four independent word stores to test which expression survives propagation. {"label": "aes-store-order-3210", "function": "ATERMAesExpandEncryptKey", "score": 97.97388, "insns": [268, 268], "diffs": 39, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 97.97388]]}

## AES allocator diagnosis

The baseline capture is byte-identical to the complete normal ATERM object. Initial PCode already evaluates key words in order 1,2,3,0, before scheduling or allocation. The firstWord assignment has been propagated into its first output store; secondWord, thirdWord and fourthWord remain named live values. Target word loads run 0,1,2,3, with final words in r27,r10,r8,r0. This is a frontend evaluation-order difference plus coloring, not a pure register swap.

Baseline GPR values: secondWord r43 -> r25, priority229, simplify degree23 of24 neighbors, available mask0x0e000000; thirdWord r42 -> r10, priority230, degree12, mask0xfc001400; fourthWord r44 -> r8, priority228, degree8 of10, mask0xfe001f00; firstWord becomes expression r87 -> r0, priority186, degree4 of6, mask0x80001fc1. The only successful coalescing is roundKey r46 into physical r3. No word coalescing or spill explains the difference. Target first 128-bit round needs roundConstant r4 and substitution r9; baseline named constants r39/r40 color at priority3/2 to r5/r4, degree5/4 of31 neighbors, after generatedRounds r41 claims r6 at priority1. The 192/256-bit loops already match. Reordering independent initial stores tests propagation while preserving all four initial loads before output writes.

- aes-word-store-helper-0123: ATERMAesExpandEncryptKey. Pass four real word values to an inline four-word store helper; all key input is evaluated before the output writes. {"label": "aes-word-store-helper-0123", "function": "ATERMAesExpandEncryptKey", "score": 98.94403, "insns": [268, 268], "diffs": 49, "drops": []}

- aes-word-store-helper-3210: ATERMAesExpandEncryptKey. Pass four real word values to an inline four-word store helper; all key input is evaluated before the output writes. {"label": "aes-word-store-helper-3210", "function": "ATERMAesExpandEncryptKey", "score": 98.94403, "insns": [268, 268], "diffs": 49, "drops": []}

- aes-word-store-helper-1023: ATERMAesExpandEncryptKey. Pass four real word values to an inline four-word store helper; all key input is evaluated before the output writes. {"label": "aes-word-store-helper-1023", "function": "ATERMAesExpandEncryptKey", "score": 98.94403, "insns": [268, 268], "diffs": 49, "drops": []}

- aes-word-store-helper-2013: ATERMAesExpandEncryptKey. Pass four real word values to an inline four-word store helper; all key input is evaluated before the output writes. {"label": "aes-word-store-helper-2013", "function": "ATERMAesExpandEncryptKey", "score": 98.94403, "insns": [268, 268], "diffs": 49, "drops": []}

- aes-word-store-helper-3012: ATERMAesExpandEncryptKey. Pass four real word values to an inline four-word store helper; all key input is evaluated before the output writes. {"label": "aes-word-store-helper-3012", "function": "ATERMAesExpandEncryptKey", "score": 98.94403, "insns": [268, 268], "diffs": 49, "drops": []}

- aes-initial-four-word-array: ATERMAesExpandEncryptKey. Keep all initial input reads ahead of stores while making the word value boundary explicit. {"label": "aes-initial-four-word-array", "function": "ATERMAesExpandEncryptKey", "score": 98.75746, "insns": [268, 268], "diffs": 53, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.75746]]}

- aes-initial-word-initializers: ATERMAesExpandEncryptKey. Keep all initial input reads ahead of stores while making the word value boundary explicit. {"label": "aes-initial-word-initializers", "function": "ATERMAesExpandEncryptKey", "score": 98.75746, "insns": [268, 268], "diffs": 53, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.75746]]}

- aes-initial-xor-assign: ATERMAesExpandEncryptKey. Keep all initial input reads ahead of stores while making the word value boundary explicit. {"label": "aes-initial-xor-assign", "function": "ATERMAesExpandEncryptKey", "score": 86.768654, "insns": [268, 268], "diffs": 83, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 86.768654]]}

- aes-initial-split-low-high: ATERMAesExpandEncryptKey. Keep all initial input reads ahead of stores while making the word value boundary explicit. {"label": "aes-initial-split-low-high", "function": "ATERMAesExpandEncryptKey", "score": 98.94403, "insns": [268, 268], "diffs": 49, "drops": []}

- aes-first-loop-global-table: ATERMAesExpandEncryptKey. Target 128-bit constant/table base colors differ despite matching 192/256 loops; test natural constant-pointer scope and named versus compiler-generated table base. {"label": "aes-first-loop-global-table", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-first-loop-outer-pointers: ATERMAesExpandEncryptKey. Target 128-bit constant/table base colors differ despite matching 192/256 loops; test natural constant-pointer scope and named versus compiler-generated table base. {"label": "aes-first-loop-outer-pointers", "function": "ATERMAesExpandEncryptKey", "error": "### mwcceppc.exe Compiler:\n#    File: build\\rx1\\trials\\aes-first-loop-outer-pointers\\ATERM.c\n# ---------------------------------------------------------------\n#    1950:     const u32* substitution; \n#   Error:     ^^^^^\n#   (10141) expression syntax error\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\n"}

- aes-first-loop-swap-pointer-decls: ATERMAesExpandEncryptKey. Target 128-bit constant/table base colors differ despite matching 192/256 loops; test natural constant-pointer scope and named versus compiler-generated table base. {"label": "aes-first-loop-swap-pointer-decls", "function": "ATERMAesExpandEncryptKey", "score": 99.05597, "insns": [268, 268], "diffs": 45, "drops": []}

- aes-first-loop-shared-pointers: ATERMAesExpandEncryptKey. Target 128-bit constant/table base colors differ despite matching 192/256 loops; test natural constant-pointer scope and named versus compiler-generated table base. {"label": "aes-first-loop-shared-pointers", "function": "ATERMAesExpandEncryptKey", "score": 98.49627, "insns": [268, 268], "diffs": 69, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.49627]]}

- aes-global-accumulate-1-0: ATERMAesExpandEncryptKey. Word accumulator holds one real half-word XOR before combining the other; test retention instead of first-word expression propagation. {"label": "aes-global-accumulate-1-0", "function": "ATERMAesExpandEncryptKey", "score": 95.62687, "insns": [268, 268], "diffs": 40, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 95.62687]]}

- aes-global-accumulate-1-1: ATERMAesExpandEncryptKey. Word accumulator holds one real half-word XOR before combining the other; test retention instead of first-word expression propagation. {"label": "aes-global-accumulate-1-1", "function": "ATERMAesExpandEncryptKey", "score": 96.08209, "insns": [268, 268], "diffs": 41, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 96.08209]]}

- aes-global-accumulate-2-0: ATERMAesExpandEncryptKey. Word accumulator holds one real half-word XOR before combining the other; test retention instead of first-word expression propagation. {"label": "aes-global-accumulate-2-0", "function": "ATERMAesExpandEncryptKey", "score": 95.5597, "insns": [268, 268], "diffs": 43, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 95.5597]]}

- aes-global-accumulate-2-1: ATERMAesExpandEncryptKey. Word accumulator holds one real half-word XOR before combining the other; test retention instead of first-word expression propagation. {"label": "aes-global-accumulate-2-1", "function": "ATERMAesExpandEncryptKey", "score": 96.029854, "insns": [268, 268], "diffs": 44, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 96.029854]]}

- aes-global-accumulate-4-0: ATERMAesExpandEncryptKey. Word accumulator holds one real half-word XOR before combining the other; test retention instead of first-word expression propagation. {"label": "aes-global-accumulate-4-0", "function": "ATERMAesExpandEncryptKey", "score": 94.02612, "insns": [268, 268], "diffs": 51, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 94.02612]]}

- aes-global-accumulate-4-1: ATERMAesExpandEncryptKey. Word accumulator holds one real half-word XOR before combining the other; test retention instead of first-word expression propagation. {"label": "aes-global-accumulate-4-1", "function": "ATERMAesExpandEncryptKey", "score": 93.42538, "insns": [268, 268], "diffs": 51, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 93.42538]]}

- aes-global-accumulate-8-0: ATERMAesExpandEncryptKey. Word accumulator holds one real half-word XOR before combining the other; test retention instead of first-word expression propagation. {"label": "aes-global-accumulate-8-0", "function": "ATERMAesExpandEncryptKey", "score": 94.43657, "insns": [268, 268], "diffs": 50, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 94.43657]]}

- aes-global-accumulate-8-1: ATERMAesExpandEncryptKey. Word accumulator holds one real half-word XOR before combining the other; test retention instead of first-word expression propagation. {"label": "aes-global-accumulate-8-1", "function": "ATERMAesExpandEncryptKey", "score": 94.970146, "insns": [268, 268], "diffs": 50, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 94.970146]]}

- aes-global-accumulate-3-0: ATERMAesExpandEncryptKey. Word accumulator holds one real half-word XOR before combining the other; test retention instead of first-word expression propagation. {"label": "aes-global-accumulate-3-0", "function": "ATERMAesExpandEncryptKey", "score": 94.42164, "insns": [268, 268], "diffs": 49, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 94.42164]]}

- aes-global-accumulate-3-1: ATERMAesExpandEncryptKey. Word accumulator holds one real half-word XOR before combining the other; test retention instead of first-word expression propagation. {"label": "aes-global-accumulate-3-1", "function": "ATERMAesExpandEncryptKey", "score": 93.38433, "insns": [268, 268], "diffs": 49, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 93.38433]]}

- aes-global-accumulate-7-0: ATERMAesExpandEncryptKey. Word accumulator holds one real half-word XOR before combining the other; test retention instead of first-word expression propagation. {"label": "aes-global-accumulate-7-0", "function": "ATERMAesExpandEncryptKey", "score": 91.74627, "insns": [268, 268], "diffs": 49, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 91.74627]]}

- aes-global-accumulate-7-1: ATERMAesExpandEncryptKey. Word accumulator holds one real half-word XOR before combining the other; test retention instead of first-word expression propagation. {"label": "aes-global-accumulate-7-1", "function": "ATERMAesExpandEncryptKey", "score": 92.37687, "insns": [268, 268], "diffs": 49, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 92.37687]]}

- aes-global-accumulate-15-0: ATERMAesExpandEncryptKey. Word accumulator holds one real half-word XOR before combining the other; test retention instead of first-word expression propagation. {"label": "aes-global-accumulate-15-0", "function": "ATERMAesExpandEncryptKey", "score": 87.66418, "insns": [268, 268], "diffs": 55, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 87.66418]]}

- aes-global-accumulate-15-1: ATERMAesExpandEncryptKey. Word accumulator holds one real half-word XOR before combining the other; test retention instead of first-word expression propagation. {"label": "aes-global-accumulate-15-1", "function": "ATERMAesExpandEncryptKey", "score": 92.970146, "insns": [268, 268], "diffs": 50, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 92.970146]]}

- aes-global-word-decls-0123: ATERMAesExpandEncryptKey. Match frontend word load order by delaying fourth-word expression, then tune real word virtual numbering with declarations. {"label": "aes-global-word-decls-0123", "function": "ATERMAesExpandEncryptKey", "score": 99.708954, "insns": [268, 268], "diffs": 10, "drops": []}

- aes-global-word-decls-0132: ATERMAesExpandEncryptKey. Match frontend word load order by delaying fourth-word expression, then tune real word virtual numbering with declarations. {"label": "aes-global-word-decls-0132", "function": "ATERMAesExpandEncryptKey", "score": 99.708954, "insns": [268, 268], "diffs": 10, "drops": []}

- aes-global-word-decls-0213: ATERMAesExpandEncryptKey. Match frontend word load order by delaying fourth-word expression, then tune real word virtual numbering with declarations. {"label": "aes-global-word-decls-0213", "function": "ATERMAesExpandEncryptKey", "score": 99.89552, "insns": [268, 268], "diffs": 5, "drops": []}

- aes-global-word-decls-0231: ATERMAesExpandEncryptKey. Match frontend word load order by delaying fourth-word expression, then tune real word virtual numbering with declarations. {"label": "aes-global-word-decls-0231", "function": "ATERMAesExpandEncryptKey", "score": 99.89552, "insns": [268, 268], "diffs": 5, "drops": []}

- aes-global-word-decls-0312: ATERMAesExpandEncryptKey. Match frontend word load order by delaying fourth-word expression, then tune real word virtual numbering with declarations. {"label": "aes-global-word-decls-0312", "function": "ATERMAesExpandEncryptKey", "score": 99.708954, "insns": [268, 268], "diffs": 10, "drops": []}

- aes-global-word-decls-0321: ATERMAesExpandEncryptKey. Match frontend word load order by delaying fourth-word expression, then tune real word virtual numbering with declarations. {"label": "aes-global-word-decls-0321", "function": "ATERMAesExpandEncryptKey", "score": 99.89552, "insns": [268, 268], "diffs": 5, "drops": []}

- aes-global-word-decls-1023: ATERMAesExpandEncryptKey. Match frontend word load order by delaying fourth-word expression, then tune real word virtual numbering with declarations. {"label": "aes-global-word-decls-1023", "function": "ATERMAesExpandEncryptKey", "score": 99.708954, "insns": [268, 268], "diffs": 10, "drops": []}

- aes-global-word-decls-1032: ATERMAesExpandEncryptKey. Match frontend word load order by delaying fourth-word expression, then tune real word virtual numbering with declarations. {"label": "aes-global-word-decls-1032", "function": "ATERMAesExpandEncryptKey", "score": 99.708954, "insns": [268, 268], "diffs": 10, "drops": []}

- aes-global-word-decls-1203: ATERMAesExpandEncryptKey. Match frontend word load order by delaying fourth-word expression, then tune real word virtual numbering with declarations. {"label": "aes-global-word-decls-1203", "function": "ATERMAesExpandEncryptKey", "score": 99.708954, "insns": [268, 268], "diffs": 10, "drops": []}

- aes-global-word-decls-1230: ATERMAesExpandEncryptKey. Match frontend word load order by delaying fourth-word expression, then tune real word virtual numbering with declarations. {"label": "aes-global-word-decls-1230", "function": "ATERMAesExpandEncryptKey", "score": 99.708954, "insns": [268, 268], "diffs": 10, "drops": []}

- aes-global-word-decls-1302: ATERMAesExpandEncryptKey. Match frontend word load order by delaying fourth-word expression, then tune real word virtual numbering with declarations. {"label": "aes-global-word-decls-1302", "function": "ATERMAesExpandEncryptKey", "score": 99.708954, "insns": [268, 268], "diffs": 10, "drops": []}

- aes-global-word-decls-1320: ATERMAesExpandEncryptKey. Match frontend word load order by delaying fourth-word expression, then tune real word virtual numbering with declarations. {"label": "aes-global-word-decls-1320", "function": "ATERMAesExpandEncryptKey", "score": 99.708954, "insns": [268, 268], "diffs": 10, "drops": []}

- aes-global-word-decls-2013: ATERMAesExpandEncryptKey. Match frontend word load order by delaying fourth-word expression, then tune real word virtual numbering with declarations. {"label": "aes-global-word-decls-2013", "function": "ATERMAesExpandEncryptKey", "score": 99.89552, "insns": [268, 268], "diffs": 5, "drops": []}

- aes-global-word-decls-2031: ATERMAesExpandEncryptKey. Match frontend word load order by delaying fourth-word expression, then tune real word virtual numbering with declarations. {"label": "aes-global-word-decls-2031", "function": "ATERMAesExpandEncryptKey", "score": 99.89552, "insns": [268, 268], "diffs": 5, "drops": []}

- aes-global-word-decls-2103: ATERMAesExpandEncryptKey. Match frontend word load order by delaying fourth-word expression, then tune real word virtual numbering with declarations. {"label": "aes-global-word-decls-2103", "function": "ATERMAesExpandEncryptKey", "score": 99.89552, "insns": [268, 268], "diffs": 5, "drops": []}

- aes-global-word-decls-2130: ATERMAesExpandEncryptKey. Match frontend word load order by delaying fourth-word expression, then tune real word virtual numbering with declarations. {"label": "aes-global-word-decls-2130", "function": "ATERMAesExpandEncryptKey", "score": 99.89552, "insns": [268, 268], "diffs": 5, "drops": []}

- aes-global-word-decls-2301: ATERMAesExpandEncryptKey. Match frontend word load order by delaying fourth-word expression, then tune real word virtual numbering with declarations. {"label": "aes-global-word-decls-2301", "function": "ATERMAesExpandEncryptKey", "score": 99.89552, "insns": [268, 268], "diffs": 5, "drops": []}

- aes-global-word-decls-2310: ATERMAesExpandEncryptKey. Match frontend word load order by delaying fourth-word expression, then tune real word virtual numbering with declarations. {"label": "aes-global-word-decls-2310", "function": "ATERMAesExpandEncryptKey", "score": 99.89552, "insns": [268, 268], "diffs": 5, "drops": []}

- aes-global-word-decls-3012: ATERMAesExpandEncryptKey. Match frontend word load order by delaying fourth-word expression, then tune real word virtual numbering with declarations. {"label": "aes-global-word-decls-3012", "function": "ATERMAesExpandEncryptKey", "score": 99.708954, "insns": [268, 268], "diffs": 10, "drops": []}

- aes-global-word-decls-3021: ATERMAesExpandEncryptKey. Match frontend word load order by delaying fourth-word expression, then tune real word virtual numbering with declarations. {"label": "aes-global-word-decls-3021", "function": "ATERMAesExpandEncryptKey", "score": 99.89552, "insns": [268, 268], "diffs": 5, "drops": []}

- aes-global-word-decls-3102: ATERMAesExpandEncryptKey. Match frontend word load order by delaying fourth-word expression, then tune real word virtual numbering with declarations. {"label": "aes-global-word-decls-3102", "function": "ATERMAesExpandEncryptKey", "score": 99.708954, "insns": [268, 268], "diffs": 10, "drops": []}

- aes-global-word-decls-3120: ATERMAesExpandEncryptKey. Match frontend word load order by delaying fourth-word expression, then tune real word virtual numbering with declarations. {"label": "aes-global-word-decls-3120", "function": "ATERMAesExpandEncryptKey", "score": 99.708954, "insns": [268, 268], "diffs": 10, "drops": []}

- aes-global-word-decls-3201: ATERMAesExpandEncryptKey. Match frontend word load order by delaying fourth-word expression, then tune real word virtual numbering with declarations. {"label": "aes-global-word-decls-3201", "function": "ATERMAesExpandEncryptKey", "score": 99.89552, "insns": [268, 268], "diffs": 5, "drops": []}

- aes-global-word-decls-3210: ATERMAesExpandEncryptKey. Match frontend word load order by delaying fourth-word expression, then tune real word virtual numbering with declarations. {"label": "aes-global-word-decls-3210", "function": "ATERMAesExpandEncryptKey", "score": 99.89552, "insns": [268, 268], "diffs": 5, "drops": []}

- aes-global-types-s32-1: ATERMAesExpandEncryptKey. Equivalent 32-bit word type tests frontend propagation without changing the key reads or stores. {"label": "aes-global-types-s32-1", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-global-types-s32-2: ATERMAesExpandEncryptKey. Equivalent 32-bit word type tests frontend propagation without changing the key reads or stores. {"label": "aes-global-types-s32-2", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-global-types-s32-4: ATERMAesExpandEncryptKey. Equivalent 32-bit word type tests frontend propagation without changing the key reads or stores. {"label": "aes-global-types-s32-4", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-global-types-s32-8: ATERMAesExpandEncryptKey. Equivalent 32-bit word type tests frontend propagation without changing the key reads or stores. {"label": "aes-global-types-s32-8", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-global-types-s32-15: ATERMAesExpandEncryptKey. Equivalent 32-bit word type tests frontend propagation without changing the key reads or stores. {"label": "aes-global-types-s32-15", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-global-types-long-1: ATERMAesExpandEncryptKey. Equivalent 32-bit word type tests frontend propagation without changing the key reads or stores. {"label": "aes-global-types-long-1", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-global-types-long-2: ATERMAesExpandEncryptKey. Equivalent 32-bit word type tests frontend propagation without changing the key reads or stores. {"label": "aes-global-types-long-2", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-global-types-long-4: ATERMAesExpandEncryptKey. Equivalent 32-bit word type tests frontend propagation without changing the key reads or stores. {"label": "aes-global-types-long-4", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-global-types-long-8: ATERMAesExpandEncryptKey. Equivalent 32-bit word type tests frontend propagation without changing the key reads or stores. {"label": "aes-global-types-long-8", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-global-types-long-15: ATERMAesExpandEncryptKey. Equivalent 32-bit word type tests frontend propagation without changing the key reads or stores. {"label": "aes-global-types-long-15", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-global-types-ulong-1: ATERMAesExpandEncryptKey. Equivalent 32-bit word type tests frontend propagation without changing the key reads or stores. {"label": "aes-global-types-ulong-1", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-global-types-ulong-2: ATERMAesExpandEncryptKey. Equivalent 32-bit word type tests frontend propagation without changing the key reads or stores. {"label": "aes-global-types-ulong-2", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-global-types-ulong-4: ATERMAesExpandEncryptKey. Equivalent 32-bit word type tests frontend propagation without changing the key reads or stores. {"label": "aes-global-types-ulong-4", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-global-types-ulong-8: ATERMAesExpandEncryptKey. Equivalent 32-bit word type tests frontend propagation without changing the key reads or stores. {"label": "aes-global-types-ulong-8", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-global-types-ulong-15: ATERMAesExpandEncryptKey. Equivalent 32-bit word type tests frontend propagation without changing the key reads or stores. {"label": "aes-global-types-ulong-15", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-global-const-init-1: ATERMAesExpandEncryptKey. Use immutable initial word values; unchanged input bytes and output values. {"label": "aes-global-const-init-1", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-global-const-init-2: ATERMAesExpandEncryptKey. Use immutable initial word values; unchanged input bytes and output values. {"label": "aes-global-const-init-2", "function": "ATERMAesExpandEncryptKey", "error": "### mwcceppc.exe Compiler:\n#    File: build\\rx1\\trials\\aes-global-const-init-2\\ATERM.c\n# ---------------------------------------------------------\n#    1941:     const u32 secondWord = (((u32)keyBytes[7] ^ ((u32)keyBytes[6] << 8)) ^ (((u32)keyBytes[4] << 24) ^ ((u32)keyBytes[5] << 16)\n#   Error:     ^^^^^\n#   (10141) expression syntax error\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\n"}

- aes-global-const-init-4: ATERMAesExpandEncryptKey. Use immutable initial word values; unchanged input bytes and output values. {"label": "aes-global-const-init-4", "function": "ATERMAesExpandEncryptKey", "error": "### mwcceppc.exe Compiler:\n#    File: build\\rx1\\trials\\aes-global-const-init-4\\ATERM.c\n# ---------------------------------------------------------\n#    1942:     const u32 thirdWord = (((u32)keyBytes[11] ^ ((u32)keyBytes[10] << 8)) ^ (((u32)keyBytes[8] << 24) ^ ((u32)keyBytes[9] << 16\n#   Error:     ^^^^^\n#   (10141) expression syntax error\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\n"}

- aes-global-const-init-8: ATERMAesExpandEncryptKey. Use immutable initial word values; unchanged input bytes and output values. {"label": "aes-global-const-init-8", "function": "ATERMAesExpandEncryptKey", "error": "### mwcceppc.exe Compiler:\n#    File: build\\rx1\\trials\\aes-global-const-init-8\\ATERM.c\n# ---------------------------------------------------------\n#    1943:     const u32 fourthWord = (((u32)keyBytes[15] ^ ((u32)keyBytes[14] << 8)) ^ (((u32)keyBytes[12] << 24) ^ ((u32)keyBytes[13] <<\n#   Error:     ^^^^^\n#   (10141) expression syntax error\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\n"}

- aes-global-const-init-3: ATERMAesExpandEncryptKey. Use immutable initial word values; unchanged input bytes and output values. {"label": "aes-global-const-init-3", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-global-const-init-7: ATERMAesExpandEncryptKey. Use immutable initial word values; unchanged input bytes and output values. {"label": "aes-global-const-init-7", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-global-const-init-15: ATERMAesExpandEncryptKey. Use immutable initial word values; unchanged input bytes and output values. {"label": "aes-global-const-init-15", "function": "ATERMAesExpandEncryptKey", "score": 99.652985, "insns": [268, 268], "diffs": 25, "drops": []}

- aes-global-output-cursor: ATERMAesExpandEncryptKey. Test ordinary output cursor or explicit high/low word values while retaining all input reads before all output writes. {"label": "aes-global-output-cursor", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-global-output-alias: ATERMAesExpandEncryptKey. Test ordinary output cursor or explicit high/low word values while retaining all input reads before all output writes. {"label": "aes-global-output-alias", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-global-word-halves: ATERMAesExpandEncryptKey. Test ordinary output cursor or explicit high/low word values while retaining all input reads before all output writes. {"label": "aes-global-word-halves", "function": "ATERMAesExpandEncryptKey", "score": 96.93657, "insns": [268, 268], "diffs": 40, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 96.93657]]}

- aes-global-word-halves-last: ATERMAesExpandEncryptKey. Test ordinary output cursor or explicit high/low word values while retaining all input reads before all output writes. {"label": "aes-global-word-halves-last", "function": "ATERMAesExpandEncryptKey", "score": 95.24627, "insns": [268, 268], "diffs": 42, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 95.24627]]}

- aes-global-shape-initializer-array: ATERMAesExpandEncryptKey. Use normal word array/copy, loop, or assignment grouping to test pre-allocation expression retention, preserving every input byte. {"label": "aes-global-shape-initializer-array", "function": "ATERMAesExpandEncryptKey", "error": "### mwcceppc.exe Compiler:\n#    File: build\\rx1\\trials\\aes-global-shape-initializer-array\\ATERM.c\n# --------------------------------------------------------------------\n#    1934:  8)) ^ (((u32)keyBytes[12] << 24) ^ ((u32)keyBytes[13] << 16)))}; \n#   Error:                                                                 ^\n#   (10124) illegal constant expression\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\n"}

- aes-global-shape-copy-array: ATERMAesExpandEncryptKey. Use normal word array/copy, loop, or assignment grouping to test pre-allocation expression retention, preserving every input byte. {"label": "aes-global-shape-copy-array", "function": "ATERMAesExpandEncryptKey", "score": 86.89179, "insns": [274, 268], "diffs": 265, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 86.89179]]}

- aes-global-shape-loop-array: ATERMAesExpandEncryptKey. Use normal word array/copy, loop, or assignment grouping to test pre-allocation expression retention, preserving every input byte. {"label": "aes-global-shape-loop-array", "function": "ATERMAesExpandEncryptKey", "score": 99.652985, "insns": [268, 268], "diffs": 25, "drops": []}

- aes-global-shape-copy-array-inline: ATERMAesExpandEncryptKey. Use normal word array/copy, loop, or assignment grouping to test pre-allocation expression retention, preserving every input byte. {"label": "aes-global-shape-copy-array-inline", "function": "ATERMAesExpandEncryptKey", "score": 86.89179, "insns": [274, 268], "diffs": 265, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 86.89179]]}

- aes-global-shape-comma-words: ATERMAesExpandEncryptKey. Use normal word array/copy, loop, or assignment grouping to test pre-allocation expression retention, preserving every input byte. {"label": "aes-global-shape-comma-words", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-global-shape-single-comma: ATERMAesExpandEncryptKey. Use normal word array/copy, loop, or assignment grouping to test pre-allocation expression retention, preserving every input byte. {"label": "aes-global-shape-single-comma", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-global-shape-high-half-reuse: ATERMAesExpandEncryptKey. Use normal word array/copy, loop, or assignment grouping to test pre-allocation expression retention, preserving every input byte. {"label": "aes-global-shape-high-half-reuse", "function": "ATERMAesExpandEncryptKey", "score": 96.08209, "insns": [268, 268], "diffs": 41, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 96.08209]]}

Allocator confirmation nup-result-typed-copy: capture `build/rx1/mwdbg-nup-result-typed-copy`, whole-object equality with normal compiler True.

- aes-base-low-temp-high-owner: ATERMAesExpandEncryptKey. Use genuine first-word half temporaries or initial-word scope/lifetime; target firstWord must share the high-half color r27 rather than low-half r25. {"label": "aes-base-low-temp-high-owner", "function": "ATERMAesExpandEncryptKey", "score": 96.08209, "insns": [268, 268], "diffs": 41, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 96.08209]]}

- aes-base-high-temp-low-owner: ATERMAesExpandEncryptKey. Use genuine first-word half temporaries or initial-word scope/lifetime; target firstWord must share the high-half color r27 rather than low-half r25. {"label": "aes-base-high-temp-low-owner", "function": "ATERMAesExpandEncryptKey", "score": 95.62687, "insns": [268, 268], "diffs": 40, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 95.62687]]}

- aes-base-two-half-temps: ATERMAesExpandEncryptKey. Use genuine first-word half temporaries or initial-word scope/lifetime; target firstWord must share the high-half color r27 rather than low-half r25. {"label": "aes-base-two-half-temps", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-base-two-half-temp-late: ATERMAesExpandEncryptKey. Use genuine first-word half temporaries or initial-word scope/lifetime; target firstWord must share the high-half color r27 rather than low-half r25. {"label": "aes-base-two-half-temp-late", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-base-first-fourth-scope: ATERMAesExpandEncryptKey. Use genuine first-word half temporaries or initial-word scope/lifetime; target firstWord must share the high-half color r27 rather than low-half r25. {"label": "aes-base-first-fourth-scope", "function": "ATERMAesExpandEncryptKey", "score": 99.652985, "insns": [268, 268], "diffs": 25, "drops": []}

- aes-base-initial-word-reuse: ATERMAesExpandEncryptKey. Use genuine first-word half temporaries or initial-word scope/lifetime; target firstWord must share the high-half color r27 rather than low-half r25. {"label": "aes-base-initial-word-reuse", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-near-low-temp-high-owner: ATERMAesExpandEncryptKey. Use genuine first-word half temporaries or initial-word scope/lifetime; target firstWord must share the high-half color r27 rather than low-half r25. {"label": "aes-near-low-temp-high-owner", "function": "ATERMAesExpandEncryptKey", "score": 96.033585, "insns": [268, 268], "diffs": 42, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 96.033585]]}

- aes-near-high-temp-low-owner: ATERMAesExpandEncryptKey. Use genuine first-word half temporaries or initial-word scope/lifetime; target firstWord must share the high-half color r27 rather than low-half r25. {"label": "aes-near-high-temp-low-owner", "function": "ATERMAesExpandEncryptKey", "score": 95.57836, "insns": [268, 268], "diffs": 41, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 95.57836]]}

## Capture and trial notes

Correction to the intermediate Split paragraph: the three `split-tail-length-inline-*` variants did reach 100% after the earlier helper variants failed. The retained `split-tail-owner-order-1` achieves the same match with ordinary locals and no helper. The claimed failed helpers were the older `split-tail-helper-*` variants.

The local debugger launcher also omits `-enc SJIS` for diagnostic captures because the emulator crashes before code generation with it on CHANSVm and ATERM. Every completed captured object is compared byte-for-byte to the corresponding ordinary wibo/SJIS compile. Normal Ninja flags remain unchanged. A second local driver adds read-only 4-KiB memory caching, cleared whenever the inferior continues, to reduce GDB remote reads. The shared port lock remains active. Captures record the driver hash. Allocation rewrite validation and whole-object equality must both pass before using this driver's evidence.

AES now has an honest 99.89552% scratch candidate, 268/268 instructions, five differences. Starting from the baseline: use the global substitution table directly only in the 128-bit loop; declare initial words first/third/second/fourth; store fourth, first, second, third. All initial input loads still occur before any store. The remaining differences are firstWord r25 vs target r27 at XOR/store, then three final word stores in the wrong order. The best source is `build/rx1/trials/aes-global-word-decls-0213/ATERM.c`; it is not retained in tracked source. Seeds224,225,226 run from this state with 1200 seconds each and the shared 24-slot limit.

- aes-near-two-half-temps: ATERMAesExpandEncryptKey. Use genuine first-word half temporaries or initial-word scope/lifetime; target firstWord must share the high-half color r27 rather than low-half r25. {"label": "aes-near-two-half-temps", "function": "ATERMAesExpandEncryptKey", "score": 99.89552, "insns": [268, 268], "diffs": 5, "drops": []}

- aes-near-two-half-temp-late: ATERMAesExpandEncryptKey. Use genuine first-word half temporaries or initial-word scope/lifetime; target firstWord must share the high-half color r27 rather than low-half r25. {"label": "aes-near-two-half-temp-late", "function": "ATERMAesExpandEncryptKey", "score": 99.86567, "insns": [268, 268], "diffs": 17, "drops": []}

- aes-near-first-fourth-scope: ATERMAesExpandEncryptKey. Use genuine first-word half temporaries or initial-word scope/lifetime; target firstWord must share the high-half color r27 rather than low-half r25. {"label": "aes-near-first-fourth-scope", "function": "ATERMAesExpandEncryptKey", "score": 99.89552, "insns": [268, 268], "diffs": 5, "drops": []}

- aes-near-initial-word-reuse: ATERMAesExpandEncryptKey. Use genuine first-word half temporaries or initial-word scope/lifetime; target firstWord must share the high-half color r27 rather than low-half r25. {"label": "aes-near-initial-word-reuse", "function": "ATERMAesExpandEncryptKey", "score": 99.89552, "insns": [268, 268], "diffs": 5, "drops": []}

- aes-base-byte-accum-0: ATERMAesExpandEncryptKey. Real bytewise word accumulation can retain the high-half variable through its final XOR instead of propagating a single assignment. {"label": "aes-base-byte-accum-0", "function": "ATERMAesExpandEncryptKey", "score": 95.6194, "insns": [268, 268], "diffs": 43, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 95.6194]]}

- aes-base-byte-accum-1: ATERMAesExpandEncryptKey. Real bytewise word accumulation can retain the high-half variable through its final XOR instead of propagating a single assignment. {"label": "aes-base-byte-accum-1", "function": "ATERMAesExpandEncryptKey", "score": 96.04478, "insns": [268, 268], "diffs": 41, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 96.04478]]}

- aes-base-byte-accum-2: ATERMAesExpandEncryptKey. Real bytewise word accumulation can retain the high-half variable through its final XOR instead of propagating a single assignment. {"label": "aes-base-byte-accum-2", "function": "ATERMAesExpandEncryptKey", "score": 96.99627, "insns": [268, 268], "diffs": 42, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 96.99627]]}

- aes-base-byte-accum-3: ATERMAesExpandEncryptKey. Real bytewise word accumulation can retain the high-half variable through its final XOR instead of propagating a single assignment. {"label": "aes-base-byte-accum-3", "function": "ATERMAesExpandEncryptKey", "score": 96.06716, "insns": [268, 268], "diffs": 41, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 96.06716]]}

- aes-base-byte-accum-4: ATERMAesExpandEncryptKey. Real bytewise word accumulation can retain the high-half variable through its final XOR instead of propagating a single assignment. {"label": "aes-base-byte-accum-4", "function": "ATERMAesExpandEncryptKey", "score": 94.31343, "insns": [268, 268], "diffs": 43, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 94.31343]]}

- aes-base-byte-accum-5: ATERMAesExpandEncryptKey. Real bytewise word accumulation can retain the high-half variable through its final XOR instead of propagating a single assignment. {"label": "aes-base-byte-accum-5", "function": "ATERMAesExpandEncryptKey", "score": 94.29478, "insns": [268, 268], "diffs": 43, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 94.29478]]}

- aes-near-byte-accum-0: ATERMAesExpandEncryptKey. Real bytewise word accumulation can retain the high-half variable through its final XOR instead of propagating a single assignment. {"label": "aes-near-byte-accum-0", "function": "ATERMAesExpandEncryptKey", "score": 95.57089, "insns": [268, 268], "diffs": 44, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 95.57089]]}

- aes-near-byte-accum-1: ATERMAesExpandEncryptKey. Real bytewise word accumulation can retain the high-half variable through its final XOR instead of propagating a single assignment. {"label": "aes-near-byte-accum-1", "function": "ATERMAesExpandEncryptKey", "score": 95.99627, "insns": [268, 268], "diffs": 42, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 95.99627]]}

- aes-near-byte-accum-2: ATERMAesExpandEncryptKey. Real bytewise word accumulation can retain the high-half variable through its final XOR instead of propagating a single assignment. {"label": "aes-near-byte-accum-2", "function": "ATERMAesExpandEncryptKey", "score": 96.94776, "insns": [268, 268], "diffs": 43, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 96.94776]]}

- aes-near-byte-accum-3: ATERMAesExpandEncryptKey. Real bytewise word accumulation can retain the high-half variable through its final XOR instead of propagating a single assignment. {"label": "aes-near-byte-accum-3", "function": "ATERMAesExpandEncryptKey", "score": 96.018654, "insns": [268, 268], "diffs": 42, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 96.018654]]}

- aes-near-byte-accum-4: ATERMAesExpandEncryptKey. Real bytewise word accumulation can retain the high-half variable through its final XOR instead of propagating a single assignment. {"label": "aes-near-byte-accum-4", "function": "ATERMAesExpandEncryptKey", "score": 94.26492, "insns": [268, 268], "diffs": 45, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 94.26492]]}

- aes-near-byte-accum-5: ATERMAesExpandEncryptKey. Real bytewise word accumulation can retain the high-half variable through its final XOR instead of propagating a single assignment. {"label": "aes-near-byte-accum-5", "function": "ATERMAesExpandEncryptKey", "score": 94.24627, "insns": [268, 268], "diffs": 45, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 94.24627]]}

- assoc-indexed-input: ATERMBuildAssociationRequest. Baseline input is a low-numbered inline local colored after anonymous nibble temporaries; indexed access may create an induced pointer with later virtual numbering and target r5. {"label": "assoc-indexed-input", "function": "ATERMBuildAssociationRequest", "score": 95.646614, "insns": [133, 133], "diffs": 64, "drops": [["ATERMDiscoverAccessPoints", 98.31939, 97.52091], ["ATERMBuildAssociationRequest", 98.7594, 95.646614]]}

- assoc-indexed-output: ATERMBuildAssociationRequest. Baseline input is a low-numbered inline local colored after anonymous nibble temporaries; indexed access may create an induced pointer with later virtual numbering and target r5. {"label": "assoc-indexed-output", "function": "ATERMBuildAssociationRequest", "score": 88.451126, "insns": [141, 133], "diffs": 85, "drops": [["ATERMDiscoverAccessPoints", 98.31939, 95.53232], ["ATERMBuildAssociationRequest", 98.7594, 88.451126]]}

- assoc-indexed-both: ATERMBuildAssociationRequest. Baseline input is a low-numbered inline local colored after anonymous nibble temporaries; indexed access may create an induced pointer with later virtual numbering and target r5. {"label": "assoc-indexed-both", "function": "ATERMBuildAssociationRequest", "score": 88.451126, "insns": [141, 133], "diffs": 85, "drops": [["ATERMDiscoverAccessPoints", 98.31939, 95.51711], ["ATERMBuildAssociationRequest", 98.7594, 88.451126]]}

- assoc-for-input-step: ATERMBuildAssociationRequest. Baseline input is a low-numbered inline local colored after anonymous nibble temporaries; indexed access may create an induced pointer with later virtual numbering and target r5. {"label": "assoc-for-input-step", "function": "ATERMBuildAssociationRequest", "score": 95.90225, "insns": [133, 133], "diffs": 64, "drops": [["ATERMDiscoverAccessPoints", 98.31939, 97.59696], ["ATERMBuildAssociationRequest", 98.7594, 95.90225]]}

- assoc-countdown-input: ATERMBuildAssociationRequest. Baseline input is a low-numbered inline local colored after anonymous nibble temporaries; indexed access may create an induced pointer with later virtual numbering and target r5. {"label": "assoc-countdown-input", "function": "ATERMBuildAssociationRequest", "score": 95.52631, "insns": [131, 133], "diffs": 83, "drops": [["ATERMDiscoverAccessPoints", 98.31939, 97.47148], ["ATERMBuildAssociationRequest", 98.7594, 95.52631]]}

- assoc-index-address-expression: ATERMBuildAssociationRequest. Baseline input is a low-numbered inline local colored after anonymous nibble temporaries; indexed access may create an induced pointer with later virtual numbering and target r5. {"label": "assoc-index-address-expression", "function": "ATERMBuildAssociationRequest", "score": 95.646614, "insns": [133, 133], "diffs": 64, "drops": [["ATERMDiscoverAccessPoints", 98.31939, 97.52091], ["ATERMBuildAssociationRequest", 98.7594, 95.646614]]}

## Confirmed changed-source allocator results

Format typed-owner trial keeps exactly the baseline register graph decision. `formattedObj` v42 still owns r18; `objLen` v35 and the propagated string pointer still use r14. GPR pass2 validates810 operand rewrites with zero mismatches; the complete normal and debugger objects are identical. Moving the real object owner through every outer declaration position cannot put it after the competing pointer in the coloring order without disturbing other allocations.

Nup return-value naming adds11 inline virtual registers across the repeated helpers, but its first-tag live values remain isomorphic: opening literal v120->r24, closing literal v119->r25, opening match v116->r26, closing match v125->r22. Their simplify degrees remain20,22,22,21. The named return copies are dead. Coloring ranks, counting successful assignments from1, are107,108,111,103. Both captures validate1186 GPR operand rewrites and364 CR rewrites, with zero mismatches; complete objects are identical. Earlier Format and Nup priority numbers used zero-based indices; relative ordering is unchanged.

Association also tested six natural loop shapes after the four nibble/helper trials: indexed input, indexed output, both indexed, input increment in the for step, countdown, and indexed address expression. They changed the pointer allocation but regressed Association and DiscoverAccessPoints, so none is retained. The indexed-input variant preserves133 instructions but has64 differences instead of28.

Allocator confirmation split-tail-owner-order-1: capture `build/rx1/mwdbg-split-tail-owner-order-1`, whole-object equality with normal compiler True.

- aes-global-branch-key-stores: ATERMAesExpandEncryptKey. Place real initial output stores in each key-size path; multiple uses can keep initial-word values live across the guard before common-store hoisting. {"label": "aes-global-branch-key-stores", "function": "ATERMAesExpandEncryptKey", "score": 89.283585, "insns": [272, 268], "diffs": 221, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 89.283585]]}

- aes-global-branch-first-word: ATERMAesExpandEncryptKey. Place real initial output stores in each key-size path; multiple uses can keep initial-word values live across the guard before common-store hoisting. {"label": "aes-global-branch-first-word", "function": "ATERMAesExpandEncryptKey", "score": 91.81716, "insns": [269, 268], "diffs": 205, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 91.81716]]}

- aes-global-branch-fourth-word: ATERMAesExpandEncryptKey. Place real initial output stores in each key-size path; multiple uses can keep initial-word values live across the guard before common-store hoisting. {"label": "aes-global-branch-fourth-word", "function": "ATERMAesExpandEncryptKey", "score": 86.70149, "insns": [269, 268], "diffs": 208, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 86.70149]]}

## Exact Split allocator confirmation

Capture `build/rx1/mwdbg-split-tail-owner-order-1` is byte-identical to the ordinary compiler's complete exact candidate object. GPR validation checks478 operand rewrites with zero mismatches. Baseline and candidate each have one accepted coalesce, v91 into physical r4, and no spills. The match comes from liveness and priority changes, not added coalescing.

One-based coloring order changes from limit v47/r31, parentStr v45/r30, return v34/r29, parent v33/r28, VM v32/r27 to parentStr v46/r31, limit v44/r30, count v37/r29, return v34/r28, parent v33/r29, VM v32/r27. Their candidate simplify degrees are12,13,14,15,15,17. Reusing count in the empty-delimiter loop makes it survive the first simplify scan; it colors third and later shares r29 with the dead parent header. Parent string and limit declarations reverse which one first requests saved r31. This explains the formerly widespread saved-register swaps.

The last six differences needed a distinct tail header. Remaining length v49 colors to r26 at rank59, simplify degree18, mask0x04000000; tailElement v48 colors next to r25 at rank60, degree18, mask0x02000000. This gives the exact subtraction/NewObject/memcpy register sequence. The separate header is a normal pointer with a shorter lifetime, assigned before every use. Swapping the independent delimiter-length/parent-length reads supplies the target r3/r4 input-base order. Full unit data remains100%; fresh full gate follows after the searches finish.

Prior branch audit, read-only Git objects: s1,s3,s5,s6,s7,s8 have no owned-unit source changes from their merge bases. s2 changes only the128-bit AES table/round-constant declaration order, already reproduced here as `aes-first-loop-swap-pointer-decls`,99.05597%/45 differences. s4 swaps delimiter/parent length evaluation, which is included in the exact Split result. The rejected `6250718a` Write result stores a string pointer into the VM parameter through casts; that source was inspected but never copied or compiled here.

Allocator confirmation hex-reused-digit-19-s32: capture `build/rx1/mwdbg-hex-reused-digit-19-s32`, whole-object equality with normal compiler True.

- format-spill-cost-baseline-tc-before: CHANSVmFormatString. Pass2 spill candidates are objLen cost3 then input pointer cost4. A typed input pointer with earlier virtual numbering may let the real owner win the equal-cost optimistic-spill selection, exchanging r14/r18. {"label": "format-spill-cost-baseline-tc-before", "function": "CHANSVmFormatString", "score": 99.187935, "insns": [431, 431], "diffs": 53, "drops": [["CHANSVmFormatString", 99.84919, 99.187935]]}

- format-spill-cost-baseline-tc-after: CHANSVmFormatString. Pass2 spill candidates are objLen cost3 then input pointer cost4. A typed input pointer with earlier virtual numbering may let the real owner win the equal-cost optimistic-spill selection, exchanging r14/r18. {"label": "format-spill-cost-baseline-tc-after", "function": "CHANSVmFormatString", "score": 99.187935, "insns": [431, 431], "diffs": 53, "drops": [["CHANSVmFormatString", 99.84919, 99.187935]]}

- format-spill-cost-baseline-function-first: CHANSVmFormatString. Pass2 spill candidates are objLen cost3 then input pointer cost4. A typed input pointer with earlier virtual numbering may let the real owner win the equal-cost optimistic-spill selection, exchanging r14/r18. {"label": "format-spill-cost-baseline-function-first", "function": "CHANSVmFormatString", "score": 99.84919, "insns": [431, 431], "diffs": 13, "drops": []}

- format-spill-cost-baseline-function-last: CHANSVmFormatString. Pass2 spill candidates are objLen cost3 then input pointer cost4. A typed input pointer with earlier virtual numbering may let the real owner win the equal-cost optimistic-spill selection, exchanging r14/r18. {"label": "format-spill-cost-baseline-function-last", "function": "CHANSVmFormatString", "score": 99.187935, "insns": [431, 431], "diffs": 53, "drops": [["CHANSVmFormatString", 99.84919, 99.187935]]}

- format-spill-cost-baseline-owner-before: CHANSVmFormatString. Pass2 spill candidates are objLen cost3 then input pointer cost4. A typed input pointer with earlier virtual numbering may let the real owner win the equal-cost optimistic-spill selection, exchanging r14/r18. {"label": "format-spill-cost-baseline-owner-before", "function": "CHANSVmFormatString", "score": 99.187935, "insns": [431, 431], "diffs": 53, "drops": [["CHANSVmFormatString", 99.84919, 99.187935]]}

- format-spill-cost-baseline-owner-after: CHANSVmFormatString. Pass2 spill candidates are objLen cost3 then input pointer cost4. A typed input pointer with earlier virtual numbering may let the real owner win the equal-cost optimistic-spill selection, exchanging r14/r18. {"label": "format-spill-cost-baseline-owner-after", "function": "CHANSVmFormatString", "score": 99.187935, "insns": [431, 431], "diffs": 53, "drops": [["CHANSVmFormatString", 99.84919, 99.187935]]}

- format-spill-cost-owner-tc-before: CHANSVmFormatString. Pass2 spill candidates are objLen cost3 then input pointer cost4. A typed input pointer with earlier virtual numbering may let the real owner win the equal-cost optimistic-spill selection, exchanging r14/r18. {"label": "format-spill-cost-owner-tc-before", "function": "CHANSVmFormatString", "score": 99.29234, "insns": [431, 431], "diffs": 45, "drops": [["CHANSVmFormatString", 99.84919, 99.29234]]}

- format-spill-cost-owner-tc-after: CHANSVmFormatString. Pass2 spill candidates are objLen cost3 then input pointer cost4. A typed input pointer with earlier virtual numbering may let the real owner win the equal-cost optimistic-spill selection, exchanging r14/r18. {"label": "format-spill-cost-owner-tc-after", "function": "CHANSVmFormatString", "score": 99.29234, "insns": [431, 431], "diffs": 45, "drops": [["CHANSVmFormatString", 99.84919, 99.29234]]}

- format-spill-cost-owner-function-first: CHANSVmFormatString. Pass2 spill candidates are objLen cost3 then input pointer cost4. A typed input pointer with earlier virtual numbering may let the real owner win the equal-cost optimistic-spill selection, exchanging r14/r18. {"label": "format-spill-cost-owner-function-first", "function": "CHANSVmFormatString", "score": 99.84919, "insns": [431, 431], "diffs": 13, "drops": []}

- format-spill-cost-owner-function-last: CHANSVmFormatString. Pass2 spill candidates are objLen cost3 then input pointer cost4. A typed input pointer with earlier virtual numbering may let the real owner win the equal-cost optimistic-spill selection, exchanging r14/r18. {"label": "format-spill-cost-owner-function-last", "function": "CHANSVmFormatString", "score": 99.29234, "insns": [431, 431], "diffs": 45, "drops": [["CHANSVmFormatString", 99.84919, 99.29234]]}

- format-spill-cost-owner-owner-before: CHANSVmFormatString. Pass2 spill candidates are objLen cost3 then input pointer cost4. A typed input pointer with earlier virtual numbering may let the real owner win the equal-cost optimistic-spill selection, exchanging r14/r18. {"label": "format-spill-cost-owner-owner-before", "function": "CHANSVmFormatString", "score": 99.187935, "insns": [431, 431], "diffs": 53, "drops": [["CHANSVmFormatString", 99.84919, 99.187935]]}

- format-spill-cost-owner-owner-after: CHANSVmFormatString. Pass2 spill candidates are objLen cost3 then input pointer cost4. A typed input pointer with earlier virtual numbering may let the real owner win the equal-cost optimistic-spill selection, exchanging r14/r18. {"label": "format-spill-cost-owner-owner-after", "function": "CHANSVmFormatString", "score": 99.29234, "insns": [431, 431], "diffs": 45, "drops": [["CHANSVmFormatString", 99.84919, 99.29234]]}

- format-owner-spill-order-0: CHANSVmFormatString. With a real typed string pointer, maxSize takes r14. Change owner virtual number relative to maxSize so the owner, not maxSize, can be selected at equal spill cost4. {"label": "format-owner-spill-order-0", "function": "CHANSVmFormatString", "score": 100.0, "insns": [431, 431], "diffs": 0, "drops": []}

- format-and-split: CHANSVmFormatString. Combine exact typed Format ownership and exact Split local lifetimes. Both original source bodies are otherwise preserved; all unit functions are compared against the starting report. {"label": "format-and-split", "function": "CHANSVmFormatString", "score": 100.0, "insns": [431, 431], "diffs": 0, "drops": []}

Allocator confirmation aes-first-loop-global-table: capture `build/rx1/mwdbg-aes-first-loop-global-table`, whole-object equality with normal compiler True.

Hex confirmation `hex-reused-digit-19-s32` validates177 GPR rewrites and produces a complete object identical to the normal trial. The named digit survives as v36 but still gets r5, rank32, degree9, legal mask0x1e20. A separate propagated digit temporary v62 already colors r5 at rank7. The character cursor v40 colors to r7 at rank28, degree14, mask0x1f80; source v42 gets r6 at rank26; synthesized high-digit byte offset v67 gets r4 at rank2. The unchanged pre-loop arg-to-r4 coalesce is unrelated to the loop swap. No spills or loop coalesces explain the mismatch.

AES confirmation `aes-first-loop-global-table` is byte-identical to the normal trial, with546 GPR and12 CR rewrites checked. Removing only the128-bit named table pointer replaces it with compiler-generated base v92. v92 has31 neighbors, simplifies at degree28, colors at rank183 with mask0x80001e00, and gets target r9. The round-constant pointer v39 now colors second with degree4 and gets target r4. The old named table pointer had stayed in the high-degree core and colored second to r4, forcing constants to r5. Thus every128-bit loop difference is fixed; initial-word propagation still leaves21 differences.

## Exact Format candidate

`format-owner-spill-order-0` reaches100%,431/431 instructions,zero differences. Format pass2's optimistic spill candidates were objLen v36 at cost3, then input pointer v65 at cost4. Both are later colored successfully, so these are candidates, not actual pass2 spills. The other cost4 contenders include nObj and maxSize. A real typed stringData pointer changes the contender set; with the owner declared late, maxSize receives r14 and45 differences remain. Declaring the real formattedObj owner just after pad0 then gives the exact target.

The retained source separates formattedObj from numeric litLen, and stringData from numeric isEscaped. Both pointers are assigned in every path entering common_string_format: the character case supplies pad0/null owner; the string case supplies the allocated object's data/owner. The same object is deleted under the same guard. All exits reset or overwrite litLen before it is used again. Six pointer-to-integer or integer-to-pointer casts disappear. No added comments, helper boundaries, carrier types, or instructions.

`format-and-split` combines only this Format body with the exact Split body. Fresh normal Ninja build: both functions100%,431/431 and222/222,ctxdiff0; all125 pool strings identical. Quick gate `build/rx1/candidate2-gate.txt` passes with CHANSVm226/233 functions,42520/53564 code bytes,6904/6904 data bytes, zero regressions/forbidden additions/readability warnings. Fresh exact Format allocator capture and clean full gate remain pending.

Allocator confirmation assoc-low-before-high: capture `build/rx1/mwdbg-assoc-low-before-high`, whole-object equality with normal compiler True.

Association changed-source confirmation: `assoc-low-before-high` validates272 GPR rewrites, with complete object equality to the normal trial. Reordering the independent nibble assignments changes their virtual IDs and colors, but both input pointers remain v43/v36->r9, one-based coloring ranks54/61, degree14. The first output cursor changes r6 to r5 and the second r5 to r4. This confirms the high/low temporary ordering lever affects the wrong allocation group and explains the40-difference regression. No coalesces or spills occur in either Association capture. Earlier baseline Association priority indices were zero-based.

Allocator confirmation aes-global-word-decls-0213: capture `build/rx1/mwdbg-aes-global-word-decls-0213`, whole-object equality with normal compiler True.

- aes-direct-key-word-stores: ATERMAesExpandEncryptKey. Test ordinary direct big-endian word stores. Target word0 may be an anonymous store-expression result rather than a named local. Source sequencing differs for arbitrary partial overlap; only an exact target instruction stream can validate identical actual input load/output store order. {"label": "aes-direct-key-word-stores", "function": "ATERMAesExpandEncryptKey", "score": 98.910446, "insns": [268, 268], "diffs": 9, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.910446]]}

- aes-direct-held-words-0: ATERMAesExpandEncryptKey. Test genuine direct versus held key-word values. Direct word0 gives target r27 as an anonymous expression; every candidate requires exact assembly to prove the target input/output memory order, including overlap behavior. {"label": "aes-direct-held-words-0", "function": "ATERMAesExpandEncryptKey", "score": 98.910446, "insns": [268, 268], "diffs": 9, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.910446]]}

- aes-direct-held-words-1: ATERMAesExpandEncryptKey. Test genuine direct versus held key-word values. Direct word0 gives target r27 as an anonymous expression; every candidate requires exact assembly to prove the target input/output memory order, including overlap behavior. {"label": "aes-direct-held-words-1", "function": "ATERMAesExpandEncryptKey", "score": 98.906715, "insns": [268, 268], "diffs": 11, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.906715]]}

- aes-direct-held-words-2: ATERMAesExpandEncryptKey. Test genuine direct versus held key-word values. Direct word0 gives target r27 as an anonymous expression; every candidate requires exact assembly to prove the target input/output memory order, including overlap behavior. {"label": "aes-direct-held-words-2", "function": "ATERMAesExpandEncryptKey", "score": 98.92164, "insns": [268, 268], "diffs": 10, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.92164]]}

- aes-direct-held-words-3: ATERMAesExpandEncryptKey. Test genuine direct versus held key-word values. Direct word0 gives target r27 as an anonymous expression; every candidate requires exact assembly to prove the target input/output memory order, including overlap behavior. {"label": "aes-direct-held-words-3", "function": "ATERMAesExpandEncryptKey", "score": 98.902985, "insns": [268, 268], "diffs": 11, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.902985]]}

- aes-direct-held-words-4: ATERMAesExpandEncryptKey. Test genuine direct versus held key-word values. Direct word0 gives target r27 as an anonymous expression; every candidate requires exact assembly to prove the target input/output memory order, including overlap behavior. {"label": "aes-direct-held-words-4", "function": "ATERMAesExpandEncryptKey", "score": 98.86567, "insns": [268, 268], "diffs": 11, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.86567]]}

- aes-direct-held-words-5: ATERMAesExpandEncryptKey. Test genuine direct versus held key-word values. Direct word0 gives target r27 as an anonymous expression; every candidate requires exact assembly to prove the target input/output memory order, including overlap behavior. {"label": "aes-direct-held-words-5", "function": "ATERMAesExpandEncryptKey", "score": 98.847015, "insns": [268, 268], "diffs": 12, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.847015]]}

- aes-direct-held-words-6: ATERMAesExpandEncryptKey. Test genuine direct versus held key-word values. Direct word0 gives target r27 as an anonymous expression; every candidate requires exact assembly to prove the target input/output memory order, including overlap behavior. {"label": "aes-direct-held-words-6", "function": "ATERMAesExpandEncryptKey", "score": 99.93284, "insns": [268, 268], "diffs": 3, "drops": []}

- aes-direct-held-words-7: ATERMAesExpandEncryptKey. Test genuine direct versus held key-word values. Direct word0 gives target r27 as an anonymous expression; every candidate requires exact assembly to prove the target input/output memory order, including overlap behavior. {"label": "aes-direct-held-words-7", "function": "ATERMAesExpandEncryptKey", "score": 99.89552, "insns": [268, 268], "diffs": 5, "drops": []}

- aes-direct-held-words-8: ATERMAesExpandEncryptKey. Test genuine direct versus held key-word values. Direct word0 gives target r27 as an anonymous expression; every candidate requires exact assembly to prove the target input/output memory order, including overlap behavior. {"label": "aes-direct-held-words-8", "function": "ATERMAesExpandEncryptKey", "score": 98.910446, "insns": [268, 268], "diffs": 9, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.910446]]}

- aes-direct-held-words-9: ATERMAesExpandEncryptKey. Test genuine direct versus held key-word values. Direct word0 gives target r27 as an anonymous expression; every candidate requires exact assembly to prove the target input/output memory order, including overlap behavior. {"label": "aes-direct-held-words-9", "function": "ATERMAesExpandEncryptKey", "score": 98.92911, "insns": [268, 268], "diffs": 10, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.92911]]}

- aes-direct-held-words-10: ATERMAesExpandEncryptKey. Test genuine direct versus held key-word values. Direct word0 gives target r27 as an anonymous expression; every candidate requires exact assembly to prove the target input/output memory order, including overlap behavior. {"label": "aes-direct-held-words-10", "function": "ATERMAesExpandEncryptKey", "score": 98.962685, "insns": [268, 268], "diffs": 9, "drops": []}

- aes-direct-held-words-11: ATERMAesExpandEncryptKey. Test genuine direct versus held key-word values. Direct word0 gives target r27 as an anonymous expression; every candidate requires exact assembly to prove the target input/output memory order, including overlap behavior. {"label": "aes-direct-held-words-11", "function": "ATERMAesExpandEncryptKey", "score": 98.94403, "insns": [268, 268], "diffs": 10, "drops": []}

- aes-direct-held-words-12: ATERMAesExpandEncryptKey. Test genuine direct versus held key-word values. Direct word0 gives target r27 as an anonymous expression; every candidate requires exact assembly to prove the target input/output memory order, including overlap behavior. {"label": "aes-direct-held-words-12", "function": "ATERMAesExpandEncryptKey", "score": 98.843285, "insns": [268, 268], "diffs": 19, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.843285]]}

- aes-direct-held-words-13: ATERMAesExpandEncryptKey. Test genuine direct versus held key-word values. Direct word0 gives target r27 as an anonymous expression; every candidate requires exact assembly to prove the target input/output memory order, including overlap behavior. {"label": "aes-direct-held-words-13", "function": "ATERMAesExpandEncryptKey", "score": 98.89179, "insns": [268, 268], "diffs": 10, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.89179]]}

- aes-direct-held-words-14: ATERMAesExpandEncryptKey. Test genuine direct versus held key-word values. Direct word0 gives target r27 as an anonymous expression; every candidate requires exact assembly to prove the target input/output memory order, including overlap behavior. {"label": "aes-direct-held-words-14", "function": "ATERMAesExpandEncryptKey", "score": 99.712685, "insns": [268, 268], "diffs": 19, "drops": []}

- aes-direct-held-words-15: ATERMAesExpandEncryptKey. Test genuine direct versus held key-word values. Direct word0 gives target r27 as an anonymous expression; every candidate requires exact assembly to prove the target input/output memory order, including overlap behavior. {"label": "aes-direct-held-words-15", "function": "ATERMAesExpandEncryptKey", "score": 99.652985, "insns": [268, 268], "diffs": 25, "drops": []}

- aes-direct-read-helper: ATERMAesExpandEncryptKey. Test ordinary endian-read helpers or real input/output cursors after identifying the first-word anonymous result; require target load/store sequencing before accepting a direct-store reconstruction. {"label": "aes-direct-read-helper", "function": "ATERMAesExpandEncryptKey", "score": 98.910446, "insns": [268, 268], "diffs": 9, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.910446]]}

- aes-direct-read-helper-locals: ATERMAesExpandEncryptKey. Test ordinary endian-read helpers or real input/output cursors after identifying the first-word anonymous result; require target load/store sequencing before accepting a direct-store reconstruction. {"label": "aes-direct-read-helper-locals", "function": "ATERMAesExpandEncryptKey", "score": 98.910446, "insns": [268, 268], "diffs": 9, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.910446]]}

- aes-direct-input-cursor: ATERMAesExpandEncryptKey. Test ordinary endian-read helpers or real input/output cursors after identifying the first-word anonymous result; require target load/store sequencing before accepting a direct-store reconstruction. {"label": "aes-direct-input-cursor", "function": "ATERMAesExpandEncryptKey", "score": 98.910446, "insns": [268, 268], "diffs": 9, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.910446]]}

- aes-direct-output-cursor: ATERMAesExpandEncryptKey. Test ordinary endian-read helpers or real input/output cursors after identifying the first-word anonymous result; require target load/store sequencing before accepting a direct-store reconstruction. {"label": "aes-direct-output-cursor", "function": "ATERMAesExpandEncryptKey", "score": 98.910446, "insns": [268, 268], "diffs": 9, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.910446]]}

- aes-held-read-helper: ATERMAesExpandEncryptKey. Test ordinary endian-read helpers or real input/output cursors after identifying the first-word anonymous result; require target load/store sequencing before accepting a direct-store reconstruction. {"label": "aes-held-read-helper", "function": "ATERMAesExpandEncryptKey", "score": 99.74627, "insns": [268, 268], "diffs": 8, "drops": []}

- aes-held-read-helper-locals: ATERMAesExpandEncryptKey. Test ordinary endian-read helpers or real input/output cursors after identifying the first-word anonymous result; require target load/store sequencing before accepting a direct-store reconstruction. {"label": "aes-held-read-helper-locals", "function": "ATERMAesExpandEncryptKey", "score": 99.74627, "insns": [268, 268], "diffs": 8, "drops": []}

- aes-held-store-helper: ATERMAesExpandEncryptKey. Test ordinary endian-read helpers or real input/output cursors after identifying the first-word anonymous result; require target load/store sequencing before accepting a direct-store reconstruction. {"label": "aes-held-store-helper", "function": "ATERMAesExpandEncryptKey", "score": 99.899254, "insns": [268, 268], "diffs": 15, "drops": []}

- aes-held-input-cursor: ATERMAesExpandEncryptKey. Test ordinary endian-read helpers or real input/output cursors after identifying the first-word anonymous result; require target load/store sequencing before accepting a direct-store reconstruction. {"label": "aes-held-input-cursor", "function": "ATERMAesExpandEncryptKey", "score": 99.93284, "insns": [268, 268], "diffs": 3, "drops": []}

- aes-held-final-stores-123: ATERMAesExpandEncryptKey. Test the last three real output stores in target order after the held-word candidate isolates the store-scheduling mismatch. Keep only an exact instruction stream after memory-order review. {"label": "aes-held-final-stores-123", "function": "ATERMAesExpandEncryptKey", "score": 98.93657, "insns": [268, 268], "diffs": 16, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.93657]]}

- aes-held-final-stores-123-reverse-decls: ATERMAesExpandEncryptKey. Test the last three real output stores in target order after the held-word candidate isolates the store-scheduling mismatch. Keep only an exact instruction stream after memory-order review. {"label": "aes-held-final-stores-123-reverse-decls", "function": "ATERMAesExpandEncryptKey", "score": 98.93657, "insns": [268, 268], "diffs": 16, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.93657]]}

- aes-held-final-stores-132: ATERMAesExpandEncryptKey. Test the last three real output stores in target order after the held-word candidate isolates the store-scheduling mismatch. Keep only an exact instruction stream after memory-order review. {"label": "aes-held-final-stores-132", "function": "ATERMAesExpandEncryptKey", "score": 98.89179, "insns": [268, 268], "diffs": 18, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.89179]]}

- aes-held-final-stores-132-reverse-decls: ATERMAesExpandEncryptKey. Test the last three real output stores in target order after the held-word candidate isolates the store-scheduling mismatch. Keep only an exact instruction stream after memory-order review. {"label": "aes-held-final-stores-132-reverse-decls", "function": "ATERMAesExpandEncryptKey", "score": 98.89179, "insns": [268, 268], "diffs": 18, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.89179]]}

- aes-held-final-stores-213: ATERMAesExpandEncryptKey. Test the last three real output stores in target order after the held-word candidate isolates the store-scheduling mismatch. Keep only an exact instruction stream after memory-order review. {"label": "aes-held-final-stores-213", "function": "ATERMAesExpandEncryptKey", "score": 98.962685, "insns": [268, 268], "diffs": 9, "drops": []}

- aes-held-final-stores-213-reverse-decls: ATERMAesExpandEncryptKey. Test the last three real output stores in target order after the held-word candidate isolates the store-scheduling mismatch. Keep only an exact instruction stream after memory-order review. {"label": "aes-held-final-stores-213-reverse-decls", "function": "ATERMAesExpandEncryptKey", "score": 98.962685, "insns": [268, 268], "diffs": 9, "drops": []}

- aes-held-final-stores-231: ATERMAesExpandEncryptKey. Test the last three real output stores in target order after the held-word candidate isolates the store-scheduling mismatch. Keep only an exact instruction stream after memory-order review. {"label": "aes-held-final-stores-231", "function": "ATERMAesExpandEncryptKey", "score": 98.92164, "insns": [268, 268], "diffs": 10, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.92164]]}

- aes-held-final-stores-231-reverse-decls: ATERMAesExpandEncryptKey. Test the last three real output stores in target order after the held-word candidate isolates the store-scheduling mismatch. Keep only an exact instruction stream after memory-order review. {"label": "aes-held-final-stores-231-reverse-decls", "function": "ATERMAesExpandEncryptKey", "score": 98.92164, "insns": [268, 268], "diffs": 10, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.92164]]}

- aes-held-final-stores-321: ATERMAesExpandEncryptKey. Test the last three real output stores in target order after the held-word candidate isolates the store-scheduling mismatch. Keep only an exact instruction stream after memory-order review. {"label": "aes-held-final-stores-321", "function": "ATERMAesExpandEncryptKey", "score": 99.95522, "insns": [268, 268], "diffs": 2, "drops": []}

- aes-held-final-stores-321-reverse-decls: ATERMAesExpandEncryptKey. Test the last three real output stores in target order after the held-word candidate isolates the store-scheduling mismatch. Keep only an exact instruction stream after memory-order review. {"label": "aes-held-final-stores-321-reverse-decls", "function": "ATERMAesExpandEncryptKey", "score": 99.731346, "insns": [268, 268], "diffs": 8, "drops": []}

- aes-direct-store-helper-0123: ATERMAesExpandEncryptKey. Test ordinary four-word store utility with directly evaluated key inputs, or the existing roundKey output alias. Input values have real uses; no carrier values or forced assembly. {"label": "aes-direct-store-helper-0123", "function": "ATERMAesExpandEncryptKey", "score": 98.8097, "insns": [268, 268], "diffs": 28, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.8097]]}

- aes-direct-store-helper-3210: ATERMAesExpandEncryptKey. Test ordinary four-word store utility with directly evaluated key inputs, or the existing roundKey output alias. Input values have real uses; no carrier values or forced assembly. {"label": "aes-direct-store-helper-3210", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-direct-store-helper-1023: ATERMAesExpandEncryptKey. Test ordinary four-word store utility with directly evaluated key inputs, or the existing roundKey output alias. Input values have real uses; no carrier values or forced assembly. {"label": "aes-direct-store-helper-1023", "function": "ATERMAesExpandEncryptKey", "score": 98.8097, "insns": [268, 268], "diffs": 28, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.8097]]}

- aes-direct-store-helper-2013: ATERMAesExpandEncryptKey. Test ordinary four-word store utility with directly evaluated key inputs, or the existing roundKey output alias. Input values have real uses; no carrier values or forced assembly. {"label": "aes-direct-store-helper-2013", "function": "ATERMAesExpandEncryptKey", "score": 98.843285, "insns": [268, 268], "diffs": 19, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.843285]]}

- aes-direct-store-helper-0213: ATERMAesExpandEncryptKey. Test ordinary four-word store utility with directly evaluated key inputs, or the existing roundKey output alias. Input values have real uses; no carrier values or forced assembly. {"label": "aes-direct-store-helper-0213", "function": "ATERMAesExpandEncryptKey", "score": 98.843285, "insns": [268, 268], "diffs": 19, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.843285]]}

- aes-direct-store-helper-0321: ATERMAesExpandEncryptKey. Test ordinary four-word store utility with directly evaluated key inputs, or the existing roundKey output alias. Input values have real uses; no carrier values or forced assembly. {"label": "aes-direct-store-helper-0321", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-held-output-alias-123: ATERMAesExpandEncryptKey. Test ordinary four-word store utility with directly evaluated key inputs, or the existing roundKey output alias. Input values have real uses; no carrier values or forced assembly. {"label": "aes-held-output-alias-123", "function": "ATERMAesExpandEncryptKey", "score": 99.95522, "insns": [268, 268], "diffs": 2, "drops": []}

- aes-held-output-alias-321: ATERMAesExpandEncryptKey. Test ordinary four-word store utility with directly evaluated key inputs, or the existing roundKey output alias. Input values have real uses; no carrier values or forced assembly. {"label": "aes-held-output-alias-321", "function": "ATERMAesExpandEncryptKey", "score": 99.95522, "insns": [268, 268], "diffs": 2, "drops": []}

## AES final scheduling boundary

`aes-held-final-stores-321` reaches 99.95522%, 268/268 instructions, with exactly two differences: instruction 48 stores r0 to output[3] instead of r10 to output[1], and instruction 50 makes the reverse swap. Every register and every other instruction now agrees. The source writes word 0 directly, holds words 1 and 2, writes word 3 directly, then stores words 2 and 1. No tracked AES edit is retained. The source-level read/write sequence can differ for partially overlapping buffers; this scratch reconstruction is evidence for the compiler investigation and is not accepted on fuzzy score. The target's complete instruction order remains mandatory.

Putting the final stores in target order makes the frontend propagate a different word expression and regresses to 16 differences. Reversing only the last two held stores reduces three differences to two. Four-word inline store helpers with direct input expressions leave 19-28 differences; using the existing roundKey output alias leaves the same two differences. The final scratch capture is queued to distinguish allocator success from the remaining scheduler order.

## Completed search rounds

All searches kept the installed global 24-slot CPU lock. Seeds 221/222/223 each ran for 1200 wall-clock seconds after acquiring a shared slot on each open function. Trial counts: Format 562/542/564; Write 779/771/798; Hex 569/558/531; nup 1226/1237/1241; Association 1083/1132/1105; AES 874/862/897. None found a new exact function. Split searches were stopped after the independently compiled exact manual result superseded them. Additional AES searches from the five-difference state: seed 224 completed 574 trials and seed 225 completed 846, both without improvement; seed 226 is still waiting for the shared slot. Every target also has at least three distinct manual compiled source attempts above.

The first final Format capture timed out at 600 seconds under host CPU contention after completing GPR pass 1. It is not validation evidence. Retrying the same source and diagnostic driver with a 1800-second capture timeout; normal compiler flags stay unchanged.

- aes-ghidra-word-parts-low: ATERMAesExpandEncryptKey. Check the target decompiler's cached byte/half-word values using aligned byte accesses and normal locals, not its inferred unaligned ushort casts. Store words in target order. Scratch only unless the full stream is exact and source semantics are proven. {"label": "aes-ghidra-word-parts-low", "function": "ATERMAesExpandEncryptKey", "score": 92.58209, "insns": [268, 268], "diffs": 49, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 92.58209]]}

- aes-ghidra-word-parts-high: ATERMAesExpandEncryptKey. Check the target decompiler's cached byte/half-word values using aligned byte accesses and normal locals, not its inferred unaligned ushort casts. Store words in target order. Scratch only unless the full stream is exact and source semantics are proven. {"label": "aes-ghidra-word-parts-high", "function": "ATERMAesExpandEncryptKey", "score": 93.970146, "insns": [268, 268], "diffs": 49, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 93.970146]]}

- aes-ghidra-word-parts-both: ATERMAesExpandEncryptKey. Check the target decompiler's cached byte/half-word values using aligned byte accesses and normal locals, not its inferred unaligned ushort casts. Store words in target order. Scratch only unless the full stream is exact and source semantics are proven. {"label": "aes-ghidra-word-parts-both", "function": "ATERMAesExpandEncryptKey", "score": 96.93657, "insns": [268, 268], "diffs": 40, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 96.93657]]}

- aes-ghidra-word-parts-bytes: ATERMAesExpandEncryptKey. Check the target decompiler's cached byte/half-word values using aligned byte accesses and normal locals, not its inferred unaligned ushort casts. Store words in target order. Scratch only unless the full stream is exact and source semantics are proven. {"label": "aes-ghidra-word-parts-bytes", "function": "ATERMAesExpandEncryptKey", "score": 95.477615, "insns": [268, 268], "diffs": 42, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 95.477615]]}

- aes-ghidra-word-parts-low-direct-zero: ATERMAesExpandEncryptKey. Check the target decompiler's cached byte/half-word values using aligned byte accesses and normal locals, not its inferred unaligned ushort casts. Store words in target order. Scratch only unless the full stream is exact and source semantics are proven. {"label": "aes-ghidra-word-parts-low-direct-zero", "function": "ATERMAesExpandEncryptKey", "score": 93.843285, "insns": [268, 268], "diffs": 49, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 93.843285]]}

- aes-ghidra-word-parts-high-direct-zero: ATERMAesExpandEncryptKey. Check the target decompiler's cached byte/half-word values using aligned byte accesses and normal locals, not its inferred unaligned ushort casts. Store words in target order. Scratch only unless the full stream is exact and source semantics are proven. {"label": "aes-ghidra-word-parts-high-direct-zero", "function": "ATERMAesExpandEncryptKey", "score": 92.95149, "insns": [268, 268], "diffs": 49, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 92.95149]]}

- aes-ghidra-word-parts-both-direct-zero: ATERMAesExpandEncryptKey. Check the target decompiler's cached byte/half-word values using aligned byte accesses and normal locals, not its inferred unaligned ushort casts. Store words in target order. Scratch only unless the full stream is exact and source semantics are proven. {"label": "aes-ghidra-word-parts-both-direct-zero", "function": "ATERMAesExpandEncryptKey", "score": 98.0597, "insns": [268, 268], "diffs": 24, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.0597]]}

- aes-ghidra-word-parts-bytes-direct-zero: ATERMAesExpandEncryptKey. Check the target decompiler's cached byte/half-word values using aligned byte accesses and normal locals, not its inferred unaligned ushort casts. Store words in target order. Scratch only unless the full stream is exact and source semantics are proven. {"label": "aes-ghidra-word-parts-bytes-direct-zero", "function": "ATERMAesExpandEncryptKey", "score": 96.42538, "insns": [268, 268], "diffs": 40, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 96.42538]]}

## Target decompiler cross-check

Read all seven owned functions in the installed `_ghidra` exports and copied their bodies into ignored `build/rx1/*.ghidra.c` for comparison. Format's decompiler distinguishes the temporary string owner and input buffer at the shared character/string formatting path, consistent with the retained typed pointers. Split has separate delimiter, ordinary element, final element and empty-delimiter paths; the retained counter reset does not change those paths. Write reloads the string data inside each conversion iteration, so caching the payload pointer is not equivalent to the target's access sequence. Hex maintains both byte and character indices. nup repeats the same tag helper expansion for each field. Association has two hex-formatting loops with the same branch structure. AES's decompiler combines adjacent byte reads into inferred ushort accesses; those casts are not source evidence and were not copied. Eight byte/half-word local reconstructions using actual byte accesses regressed to 24-49 differences and were rejected.

Manual normal-compiler trials completed: Format 71, Split 60, Write 20, Hex 19, nup 18, Association 10, AES 184. These counts exclude seven compiler errors, all preserved above. Every target has a baseline allocator capture and at least one changed-source capture with complete object equality checked against the normal compiler.

Allocator confirmation aes-held-final-stores-321: capture `build/rx1/mwdbg-aes-held-final-stores-321`, whole-object equality with normal compiler True.

AES final scratch confirmation: `mwdbg-aes-held-final-stores-321` validates 546 GPR and 12 CR rewrites, zero mismatches, and its whole object equals the normal compiler's trial object. Word 0 is now anonymous v58 rather than named firstWord: it simplifies at degree 22 and colors at rank 217 with no available existing color, requesting saved r27. The named version colored near the end and reused r25. Words 1/2 are v41/v42, ranks 233/232, degrees 12/9, colors r10/r8. Word 3 is anonymous v86, rank 189, degree 4, color r0. The 128-bit table base remains v92, rank 183, degree 28, color r9. There are no spills; the only coalesce is roundKey v44 into physical r3. The source's store order 0,3,2,1 is already visible in initial PCode and survives both allocation and final scheduling. The target requires 0,1,2,3. This capture isolates the remaining mismatch to frontend propagation and store scheduling, after solving every register choice. The two-difference source remains scratch only.

## Exact Format allocation confirmed

The final GPR pass is pass 2. The completed register rewrite validates 810 GPR operands and 223 CR operands, zero mismatches. All coloring ranks below are one-based; earlier baseline notes used zero-based priority indices.

Baseline pass 2 selected objLen v36 (cost 3, degree 29) and anonymous string input v65 (cost 4, degree 29) as optimistic spill candidates. Input v65 colored at rank 18 and requested saved r14; objLen at rank 19 reused r14. Object owner nObj v35 simplified after those removals at degree 25, colored at rank 14, and requested r18. That accounts for the r14/r18 swap.

The retained typed pointers change the relevant nodes. Final pass 2 selects objLen v35 (cost 3, degree 29) and formattedObj v59 (cost 4, degree 29). formattedObj colors at rank 18, sees no existing available color, requests r14, then receives mask 0x00004000. stringData v37 simplifies at degree 25, colors at rank 14 and requests r18 (mask 0x00040000). objLen colors at rank 19 and reuses r18; swprintf result v168 colors at rank 60, degree 28, with mask 0x01040000 and also receives r18. maxSize stays at rank 10 in r22.

This is an observed change in optimistic-spill selection, not an assumed general tie rule. The typed-pointer rewrite removes the baseline pass-1 owner-copy coalesce v62 into nObj v35; the only remaining final-source pass-1 coalesce is unrelated v135 into physical r3. Neither baseline nor final pass 2 coalesces any nodes or actually spills one. The source removes six pointer/integer casts while preserving every call and branch. Capture path: `build/rx1/mwdbg-format-and-split-final`; whole-object equality with the normal compiler is confirmed. The same object also equals the current Ninja-built object.

Allocator confirmation format-and-split: capture `build/rx1/mwdbg-format-and-split-final`, whole-object equality with normal compiler True.

- aes-held-final-stores-123-round-counter-after-1: ATERMAesExpandEncryptKey. Move the real round-counter initialization toward its first use, testing whether the frontend word-expression propagation changes without changing values, accesses, or control flow. {"label": "aes-held-final-stores-123-round-counter-after-1", "function": "ATERMAesExpandEncryptKey", "score": 98.93657, "insns": [268, 268], "diffs": 16, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.93657]]}

- aes-held-final-stores-123-round-counter-after-2: ATERMAesExpandEncryptKey. Move the real round-counter initialization toward its first use, testing whether the frontend word-expression propagation changes without changing values, accesses, or control flow. {"label": "aes-held-final-stores-123-round-counter-after-2", "function": "ATERMAesExpandEncryptKey", "score": 98.93657, "insns": [268, 268], "diffs": 16, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.93657]]}

- aes-held-final-stores-123-round-counter-after-3: ATERMAesExpandEncryptKey. Move the real round-counter initialization toward its first use, testing whether the frontend word-expression propagation changes without changing values, accesses, or control flow. {"label": "aes-held-final-stores-123-round-counter-after-3", "function": "ATERMAesExpandEncryptKey", "score": 98.93657, "insns": [268, 268], "diffs": 16, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.93657]]}

- aes-held-final-stores-123-round-counter-after-4: ATERMAesExpandEncryptKey. Move the real round-counter initialization toward its first use, testing whether the frontend word-expression propagation changes without changing values, accesses, or control flow. {"label": "aes-held-final-stores-123-round-counter-after-4", "function": "ATERMAesExpandEncryptKey", "score": 98.93657, "insns": [268, 268], "diffs": 16, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.93657]]}

- aes-held-final-stores-123-round-counter-after-5: ATERMAesExpandEncryptKey. Move the real round-counter initialization toward its first use, testing whether the frontend word-expression propagation changes without changing values, accesses, or control flow. {"label": "aes-held-final-stores-123-round-counter-after-5", "function": "ATERMAesExpandEncryptKey", "score": 98.93657, "insns": [268, 268], "diffs": 16, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.93657]]}

- aes-held-final-stores-123-round-counter-after-6: ATERMAesExpandEncryptKey. Move the real round-counter initialization toward its first use, testing whether the frontend word-expression propagation changes without changing values, accesses, or control flow. {"label": "aes-held-final-stores-123-round-counter-after-6", "function": "ATERMAesExpandEncryptKey", "score": 98.93657, "insns": [268, 268], "diffs": 16, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.93657]]}

- aes-held-final-stores-321-round-counter-after-1: ATERMAesExpandEncryptKey. Move the real round-counter initialization toward its first use, testing whether the frontend word-expression propagation changes without changing values, accesses, or control flow. {"label": "aes-held-final-stores-321-round-counter-after-1", "function": "ATERMAesExpandEncryptKey", "score": 99.95522, "insns": [268, 268], "diffs": 2, "drops": []}

- aes-held-final-stores-321-round-counter-after-2: ATERMAesExpandEncryptKey. Move the real round-counter initialization toward its first use, testing whether the frontend word-expression propagation changes without changing values, accesses, or control flow. {"label": "aes-held-final-stores-321-round-counter-after-2", "function": "ATERMAesExpandEncryptKey", "score": 99.95522, "insns": [268, 268], "diffs": 2, "drops": []}

- aes-held-final-stores-321-round-counter-after-3: ATERMAesExpandEncryptKey. Move the real round-counter initialization toward its first use, testing whether the frontend word-expression propagation changes without changing values, accesses, or control flow. {"label": "aes-held-final-stores-321-round-counter-after-3", "function": "ATERMAesExpandEncryptKey", "score": 99.95522, "insns": [268, 268], "diffs": 2, "drops": []}

- aes-held-final-stores-321-round-counter-after-4: ATERMAesExpandEncryptKey. Move the real round-counter initialization toward its first use, testing whether the frontend word-expression propagation changes without changing values, accesses, or control flow. {"label": "aes-held-final-stores-321-round-counter-after-4", "function": "ATERMAesExpandEncryptKey", "score": 99.95522, "insns": [268, 268], "diffs": 2, "drops": []}

- aes-held-final-stores-321-round-counter-after-5: ATERMAesExpandEncryptKey. Move the real round-counter initialization toward its first use, testing whether the frontend word-expression propagation changes without changing values, accesses, or control flow. {"label": "aes-held-final-stores-321-round-counter-after-5", "function": "ATERMAesExpandEncryptKey", "score": 99.95522, "insns": [268, 268], "diffs": 2, "drops": []}

- aes-held-final-stores-321-round-counter-after-6: ATERMAesExpandEncryptKey. Move the real round-counter initialization toward its first use, testing whether the frontend word-expression propagation changes without changing values, accesses, or control flow. {"label": "aes-held-final-stores-321-round-counter-after-6", "function": "ATERMAesExpandEncryptKey", "score": 99.95522, "insns": [268, 268], "diffs": 2, "drops": []}

- aes-first-loop-global-table-round-counter-after-1: ATERMAesExpandEncryptKey. Move the real round-counter initialization toward its first use, testing whether the frontend word-expression propagation changes without changing values, accesses, or control flow. {"label": "aes-first-loop-global-table-round-counter-after-1", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-first-loop-global-table-round-counter-after-2: ATERMAesExpandEncryptKey. Move the real round-counter initialization toward its first use, testing whether the frontend word-expression propagation changes without changing values, accesses, or control flow. {"label": "aes-first-loop-global-table-round-counter-after-2", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-first-loop-global-table-round-counter-after-3: ATERMAesExpandEncryptKey. Move the real round-counter initialization toward its first use, testing whether the frontend word-expression propagation changes without changing values, accesses, or control flow. {"label": "aes-first-loop-global-table-round-counter-after-3", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-first-loop-global-table-round-counter-after-4: ATERMAesExpandEncryptKey. Move the real round-counter initialization toward its first use, testing whether the frontend word-expression propagation changes without changing values, accesses, or control flow. {"label": "aes-first-loop-global-table-round-counter-after-4", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-first-loop-global-table-round-counter-after-5: ATERMAesExpandEncryptKey. Move the real round-counter initialization toward its first use, testing whether the frontend word-expression propagation changes without changing values, accesses, or control flow. {"label": "aes-first-loop-global-table-round-counter-after-5", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-first-loop-global-table-round-counter-after-6: ATERMAesExpandEncryptKey. Move the real round-counter initialization toward its first use, testing whether the frontend word-expression propagation changes without changing values, accesses, or control flow. {"label": "aes-first-loop-global-table-round-counter-after-6", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-first-loop-global-table-round-counter-after-7: ATERMAesExpandEncryptKey. Move the real round-counter initialization toward its first use, testing whether the frontend word-expression propagation changes without changing values, accesses, or control flow. {"label": "aes-first-loop-global-table-round-counter-after-7", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-first-loop-global-table-round-counter-after-8: ATERMAesExpandEncryptKey. Move the real round-counter initialization toward its first use, testing whether the frontend word-expression propagation changes without changing values, accesses, or control flow. {"label": "aes-first-loop-global-table-round-counter-after-8", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- write-validated-return-conditional: VmWinEmuWrite. Normalize the converted string to a nullable typed return in an ordinary inline argument helper. The actual success/null branches introduce a real merged pointer lifetime; test whether this retains the owner instead of the propagated anonymous result. Calls and loop payload reloads remain unchanged. {"label": "write-validated-return-conditional", "function": "VmWinEmuWrite", "score": 86.64179, "insns": [75, 67], "diffs": 52, "drops": [["VmWinEmuWrite", 99.62687, 86.64179]]}

- write-validated-return-positive-return: VmWinEmuWrite. Normalize the converted string to a nullable typed return in an ordinary inline argument helper. The actual success/null branches introduce a real merged pointer lifetime; test whether this retains the owner instead of the propagated anonymous result. Calls and loop payload reloads remain unchanged. {"label": "write-validated-return-positive-return", "function": "VmWinEmuWrite", "score": 90.522385, "insns": [71, 67], "diffs": 54, "drops": [["VmWinEmuWrite", 99.62687, 90.522385]]}

- write-validated-return-negative-return: VmWinEmuWrite. Normalize the converted string to a nullable typed return in an ordinary inline argument helper. The actual success/null branches introduce a real merged pointer lifetime; test whether this retains the owner instead of the propagated anonymous result. Calls and loop payload reloads remain unchanged. {"label": "write-validated-return-negative-return", "function": "VmWinEmuWrite", "score": 90.44776, "insns": [71, 67], "diffs": 54, "drops": [["VmWinEmuWrite", 99.62687, 90.44776]]}

The requested three initial 1200-second seeds completed for every open function. After two additional completed AES searches from the five-difference state, extra seed 226 remained in the shared slot queue for over 84 minutes without compiling a trial. Canceled only that queued optional process; no shared lock or other worker was altered. No result is claimed for seed 226. The clean final gate now runs after all private searches and debugger captures have exited.

Twenty further AES counter-initialization placements left their starting instruction streams unchanged (21, 16, or 2 differences). Three Write helpers that return a validated nullable string introduced real pointer merges but also 4-8 extra instructions (71-75 vs 67); rejected. Final manual normal-compiler counts are Format 71, Split 60, Write 23, Hex 19, nup 18, Association 10, AES 204, plus seven recorded compiler failures.

## Final clean validation

Source commit: `dc0f2351` (`Match CHANSVm formatting and splitting allocation`). Only `src/channelScript/CHANSVm.c` and this attempts log are committed. No push, PR, merge, rebase, configuration change or other-worktree source edit.

Ran the gate without `--quick`, which removed and rebuilt `build/43U`:

```
python3 -u /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py src/channelScript/CHANSVm libs/RVL_SDK/src/nup/nup src/scene/setting/ATERM
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/channelScript/CHANSVm] pool: IDENTICAL
[src/channelScript/CHANSVm] objdiff: code 42520/53564 data 6904/6904 functions 226/233 fuzzy 99.5047 linked code 0
[src/channelScript/CHANSVm] instruction-exact functions: 226/233
[libs/RVL_SDK/src/nup/nup] pool: IDENTICAL
[libs/RVL_SDK/src/nup/nup] objdiff: code 8956/10764 data 1720/1720 functions 22/23 fuzzy 99.8774 linked code 0
[libs/RVL_SDK/src/nup/nup] instruction-exact functions: 22/23
[src/scene/setting/ATERM] pool: IDENTICAL
[src/scene/setting/ATERM] objdiff: code 12200/19204 data 18864/18864 functions 20/26 fuzzy 98.2020 linked code 0
[src/scene/setting/ATERM] instruction-exact functions: 20/26
regressions vs baseline: 0
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Regenerated the live report with `/home/cole/projects/tests/.venv/bin/ninja -C . progress build/43U/report.json`. Compared it with `build/rx1/before.json` from exact starting checkout `21c5ceda`: zero decreases in any unit's matched code/data/function count and zero decreases or missing names in any function's objdiff score. The freshly rebuilt CHANSVm object still equals the final debugger object byte for byte.

Fresh ctxdiff results:

| Function | Instructions source / target | Differences |
| --- | --- | --- |
| CHANSVmFormatString | 431 / 431 | 0 |
| VmStringSplit | 222 / 222 | 0 |
| VmWinEmuWrite | 67 / 67 | 5 |
| VmBlobGetHexString | 82 / 82 | 14 |
| __nupParseServerInfo | 452 / 452 | 66 |
| ATERMBuildAssociationRequest | 133 / 133 | 28 |
| ATERMAesExpandEncryptKey | 268 / 268 | 49 |

Full evidence remains in `build/rx1/final-gate.txt`, `build/rx1/final-contexts.txt` and `build/rx1/final-verification.json`. CHANSVm gained two exact functions and 2612 matched code bytes with unchanged data; nup and ATERM retained their baseline code/data/function measures. The five open functions and the three unlinked units are not claimed complete. Parent verification is still required before accepting the leaf.
