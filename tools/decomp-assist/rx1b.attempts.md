# rx1b allocator and scheduling round

Worktree `/mnt/drive2/projects/wii-ipl-workers/rx1`, branch `agent/w1005/rx1b`.
Baseline `afabe7ca32b4d069af22630ca9181832d9cdb2bb`, fetched fork origin/main.
The branch already existed at that commit when the worker resumed. No checkout,
rebase, merge, push, or other-worktree write was performed.

Prior evidence: `rx1.attempts.md` and `build/rx1/`. The two accepted CHANSVm
functions are now part of the baseline after #1185. New experiments use
`build/rx1b/`, preserving the old captures. Normal compiler flags are unchanged.
The private debugger launcher and read-only GDB cache retain the shared GDB
lock. Diagnostic runs omit `-enc SJIS` due to the recorded emulator failure;
every successful capture must equal the complete normal-compiler object.
The private source search retains all 24 shared CPU slots and uses three
1200-second annealing seeds per unresolved function.

## Retained result

Only `VmBlobUnpack` changes in tracked source. Its ordinary-compiler objdiff score is 98.452614 -> 100.0, instruction count 517 -> 517, and ctxdiff differences 141 -> 0. Separate format-case values and integer high/low words expose the real lifetimes; ordered declarations then give the allocator the target choices. Moving the hex-source increment to the loop iteration expression removes the last two scheduling differences. The whole object from the full chronological debugger capture equals the ordinary object.

The other requested functions keep their baseline source and scores. Their best scratch candidates and allocator explanations below are evidence for the next round, not accepted matching gains. The final clean gate passes. Fresh whole-project objdiff changes only Unpack, and the final audit is recorded at the end.

## Baseline

- ATERMBuildAssociationRequest: 98.7594%.
- ATERMAesExpandEncryptKey: 98.94403%.
- CHANSVmConvertToFloatFromStr: 97.59036%.
- VmDateDtor: 94.96703%.
- VmBlobGetHexString: 98.71951%.
- VmBlobPackCommon: 98.0988%.
- VmBlobUnpack: 98.452614%.
- VmWinEmuWrite: 99.62687%.
- CHANSVmStep: 96.98723%.
- __nupParseServerInfo__FP14NUPContextInfoPcPcUx: 99.26991%.

## AES starting evidence

`build/rx1/mwdbg-aes-held-final-stores-321/backend-02-after-regalloc.txt` and `backend-04-after-scheduling.txt`
already have the stores in output order 0,3,2,1. The final scheduler preserves
that order. This is not a scheduling-only error introduced by backend-04.
The old scratch reaches 266/268 matching instructions, all register choices
correct. The source's initial reads and stores are interleaved, so partial
input/output overlap needs care. New candidates must preserve input reads
before output writes, or demonstrate the same valid API behavior. The safer
old all-read-first scratch still has five differences. Neither is retained.

## Attempts

- date-base: VmDateDtor. Fresh baseline copy for debugger; not counted as a source attempt. {"label": "date-base", "function": "VmDateDtor", "score": 94.96703, "insns": [91, 91], "diffs": 7, "drops": []}

- unpack-base: VmBlobUnpack. Fresh baseline copy for debugger; not counted as a source attempt. {"label": "unpack-base", "function": "VmBlobUnpack", "score": 98.452614, "insns": [517, 517], "diffs": 141, "drops": []}

- pack-base: VmBlobPackCommon. Fresh baseline copy for debugger; not counted as a source attempt. {"label": "pack-base", "function": "VmBlobPackCommon", "score": 98.0988, "insns": [668, 668], "diffs": 230, "drops": []}

- step-base: CHANSVmStep. Fresh baseline copy for debugger; not counted as a source attempt. {"label": "step-base", "function": "CHANSVmStep", "score": 96.98723, "insns": [1253, 1253], "diffs": 276, "drops": []}

- aes-out-reader-1: ATERMAesExpandEncryptKey. Typed endian-reader output arguments retain all initial reads before stores; test whether scalar promotion gives the first word an anonymous register without reversing stores. {"label": "aes-out-reader-1", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-out-reader-15: ATERMAesExpandEncryptKey. Typed endian-reader output arguments retain all initial reads before stores; test whether scalar promotion gives the first word an anonymous register without reversing stores. {"label": "aes-out-reader-15", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- aes-out-reader-9: ATERMAesExpandEncryptKey. Typed endian-reader output arguments retain all initial reads before stores; test whether scalar promotion gives the first word an anonymous register without reversing stores. {"label": "aes-out-reader-9", "function": "ATERMAesExpandEncryptKey", "score": 99.839554, "insns": [268, 268], "diffs": 21, "drops": []}

- float-type-after-zero: CHANSVmConvertToFloatFromStr. The target initializes the address-taken end pointer before the type compare; vary the real initialization boundary in the shared inline parser, checking every other function. {"label": "float-type-after-zero", "function": "CHANSVmConvertToFloatFromStr", "score": 95.180725, "insns": [83, 83], "diffs": 3, "drops": [["CHANSVmConvertToFloatFromStr", 97.59036, 95.180725]]}

- float-direct-type: CHANSVmConvertToFloatFromStr. The target initializes the address-taken end pointer before the type compare; vary the real initialization boundary in the shared inline parser, checking every other function. {"label": "float-direct-type", "function": "CHANSVmConvertToFloatFromStr", "score": 95.180725, "insns": [83, 83], "diffs": 3, "drops": [["CHANSVmConvertToFloatFromStr", 97.59036, 95.180725]]}

- float-endptr-initializer: CHANSVmConvertToFloatFromStr. The target initializes the address-taken end pointer before the type compare; vary the real initialization boundary in the shared inline parser, checking every other function. {"label": "float-endptr-initializer", "function": "CHANSVmConvertToFloatFromStr", "score": 97.59036, "insns": [83, 83], "diffs": 2, "drops": []}

- date-month-first: VmDateDtor. Target loads the month pointer before day and before argument setup; give those real values explicit evaluation boundaries without moving the format literal. {"label": "date-month-first", "function": "VmDateDtor", "score": 94.96703, "insns": [91, 91], "diffs": 7, "drops": []}

- date-day-first: VmDateDtor. Target loads the month pointer before day and before argument setup; give those real values explicit evaluation boundaries without moving the format literal. {"label": "date-day-first", "function": "VmDateDtor", "score": 94.96703, "insns": [91, 91], "diffs": 7, "drops": []}

- date-month-only: VmDateDtor. Target loads the month pointer before day and before argument setup; give those real values explicit evaluation boundaries without moving the format literal. {"label": "date-month-only", "function": "VmDateDtor", "score": 94.96703, "insns": [91, 91], "diffs": 7, "drops": []}

- hex-loop-helper-0: VmBlobGetHexString. Move the actual hex loop behind a scalar inline boundary; the synthesized parameter values can color before digit-expression temporaries. Preserve both byte loads and the owner offset update. {"label": "hex-loop-helper-0", "function": "VmBlobGetHexString", "score": 97.439026, "insns": [82, 82], "diffs": 32, "drops": [["VmBlobGetHexString", 98.71951, 97.439026]]}

- hex-loop-helper-1: VmBlobGetHexString. Move the actual hex loop behind a scalar inline boundary; the synthesized parameter values can color before digit-expression temporaries. Preserve both byte loads and the owner offset update. {"label": "hex-loop-helper-1", "function": "VmBlobGetHexString", "score": 97.439026, "insns": [82, 82], "diffs": 32, "drops": [["VmBlobGetHexString", 98.71951, 97.439026]]}

- hex-loop-helper-2: VmBlobGetHexString. Move the actual hex loop behind a scalar inline boundary; the synthesized parameter values can color before digit-expression temporaries. Preserve both byte loads and the owner offset update. {"label": "hex-loop-helper-2", "function": "VmBlobGetHexString", "score": 97.439026, "insns": [82, 82], "diffs": 32, "drops": [["VmBlobGetHexString", 98.71951, 97.439026]]}

- assoc-direct-pointers: ATERMBuildAssociationRequest. Test actual helper pointer/value boundaries behind the two inlined MAC loops; target input should claim r5 before the low nibble. Shared Discover function is checked for regression. {"label": "assoc-direct-pointers", "function": "ATERMBuildAssociationRequest", "score": 97.55639, "insns": [133, 133], "diffs": 50, "drops": [["ATERMDiscoverAccessPoints", 98.31939, 98.015205], ["ATERMBuildAssociationRequest", 98.7594, 97.55639]]}

- assoc-byte-u32: ATERMBuildAssociationRequest. Test actual helper pointer/value boundaries behind the two inlined MAC loops; target input should claim r5 before the low nibble. Shared Discover function is checked for regression. {"label": "assoc-byte-u32", "function": "ATERMBuildAssociationRequest", "score": 98.7594, "insns": [133, 133], "diffs": 28, "drops": []}

- assoc-nibble-scalar-switch: ATERMBuildAssociationRequest. Test actual helper pointer/value boundaries behind the two inlined MAC loops; target input should claim r5 before the low nibble. Shared Discover function is checked for regression. {"label": "assoc-nibble-scalar-switch", "function": "ATERMBuildAssociationRequest", "score": 95.6391, "insns": [135, 133], "diffs": 80, "drops": [["ATERMDiscoverAccessPoints", 98.31939, 97.36882], ["ATERMBuildAssociationRequest", 98.7594, 95.6391]]}

- nup-live-cursor-0: __nupParseServerInfo__FP14NUPContextInfoPcPcUx. Use meaningful response/cursor initialization or split the two length computations. Test whether frontend propagation retains any return-copy candidate; call and tag literal order stay fixed. {"label": "nup-live-cursor-0", "function": "__nupParseServerInfo__FP14NUPContextInfoPcPcUx", "score": 99.26991, "insns": [452, 452], "diffs": 66, "drops": []}

- nup-live-cursor-1: __nupParseServerInfo__FP14NUPContextInfoPcPcUx. Use meaningful response/cursor initialization or split the two length computations. Test whether frontend propagation retains any return-copy candidate; call and tag literal order stay fixed. {"label": "nup-live-cursor-1", "function": "__nupParseServerInfo__FP14NUPContextInfoPcPcUx", "score": 99.26991, "insns": [452, 452], "diffs": 66, "drops": []}

- nup-live-cursor-2: __nupParseServerInfo__FP14NUPContextInfoPcPcUx. Use meaningful response/cursor initialization or split the two length computations. Test whether frontend propagation retains any return-copy candidate; call and tag literal order stay fixed. {"label": "nup-live-cursor-2", "function": "__nupParseServerInfo__FP14NUPContextInfoPcPcUx", "score": 99.26991, "insns": [452, 452], "diffs": 66, "drops": []}

- write-length-boundary-1: VmWinEmuWrite. Vary only the real length computation lifetime; avoid the forbidden VM-parameter cast and preserve payload reloads inside the loop. {"label": "write-length-boundary-1", "function": "VmWinEmuWrite", "score": 99.477615, "insns": [67, 67], "diffs": 6, "drops": [["VmWinEmuWrite", 99.62687, 99.477615]]}

- write-length-boundary-2: VmWinEmuWrite. Vary only the real length computation lifetime; avoid the forbidden VM-parameter cast and preserve payload reloads inside the loop. {"label": "write-length-boundary-2", "function": "VmWinEmuWrite", "score": 97.83582, "insns": [68, 67], "diffs": 48, "drops": [["VmWinEmuWrite", 99.62687, 97.83582]]}

- write-length-before-offset: VmWinEmuWrite. Evaluate string length before initializing the genuine offset; independent statements can change allocator priority while preserving all memory accesses. {"label": "write-length-before-offset", "function": "VmWinEmuWrite", "score": 99.62687, "insns": [67, 67], "diffs": 5, "drops": []}

Fresh baseline pools: CHANSVm 125/125, nup 28/28, ATERM 0/0 identical. Full baseline build passed with the expected DOL SHA1. CHANSVm exact 226/233, nup 22/23, ATERM 20/26.

Float baseline capture `build/rx1b/mwdbg-float-base` equals the complete normal object: True. Initial PCode has lbz / li / stw / cmpli; by backend-03 it has lbz / li / cmpli / stw. Backend-04 keeps it. This local scheduling divergence predates the final scheduler. No float arithmetic differs.

- float-type-u32: CHANSVmConvertToFloatFromStr. Initial PCode already loads type, initializes endPtr, then compares; an earlier backend stage hoists the compare. Vary the real type or control-flow node to change scheduling dependencies. {"label": "float-type-u32", "function": "CHANSVmConvertToFloatFromStr", "score": 97.59036, "insns": [83, 83], "diffs": 2, "drops": []}

- float-type-s32: CHANSVmConvertToFloatFromStr. Initial PCode already loads type, initializes endPtr, then compares; an earlier backend stage hoists the compare. Vary the real type or control-flow node to change scheduling dependencies. {"label": "float-type-s32", "function": "CHANSVmConvertToFloatFromStr", "score": 97.59036, "insns": [83, 83], "diffs": 2, "drops": []}

- float-type-enum: CHANSVmConvertToFloatFromStr. Initial PCode already loads type, initializes endPtr, then compares; an earlier backend stage hoists the compare. Vary the real type or control-flow node to change scheduling dependencies. {"label": "float-type-enum", "function": "CHANSVmConvertToFloatFromStr", "score": 97.59036, "insns": [83, 83], "diffs": 2, "drops": []}

- float-comma-initialize: CHANSVmConvertToFloatFromStr. Initial PCode already loads type, initializes endPtr, then compares; an earlier backend stage hoists the compare. Vary the real type or control-flow node to change scheduling dependencies. {"label": "float-comma-initialize", "function": "CHANSVmConvertToFloatFromStr", "score": 97.59036, "insns": [83, 83], "diffs": 2, "drops": []}

- float-switch-type: CHANSVmConvertToFloatFromStr. Initial PCode already loads type, initializes endPtr, then compares; an earlier backend stage hoists the compare. Vary the real type or control-flow node to change scheduling dependencies. {"label": "float-switch-type", "function": "CHANSVmConvertToFloatFromStr", "score": 96.26506, "insns": [84, 83], "diffs": 68, "drops": [["CHANSVmConvertToFloatFromStr", 97.59036, 96.26506]]}

- float-zero-endptr-with-memset: CHANSVmConvertToFloatFromStr. Initial PCode already loads type, initializes endPtr, then compares; an earlier backend stage hoists the compare. Vary the real type or control-flow node to change scheduling dependencies. {"label": "float-zero-endptr-with-memset", "function": "CHANSVmConvertToFloatFromStr", "score": 93.915665, "insns": [86, 83], "diffs": 71, "drops": [["CHANSVmConvertToFloatFromStr", 97.59036, 93.915665]]}

- date-format-helper-0: VmDateDtor. Give date formatting a scalar inline boundary. Its pointer argument and variadic argument evaluations can change scheduler priority while preserving the same call and literal order. {"label": "date-format-helper-0", "function": "VmDateDtor", "score": 94.96703, "insns": [91, 91], "diffs": 7, "drops": []}

- date-format-helper-1: VmDateDtor. Give date formatting a scalar inline boundary. Its pointer argument and variadic argument evaluations can change scheduler priority while preserving the same call and literal order. {"label": "date-format-helper-1", "function": "VmDateDtor", "score": 94.96703, "insns": [91, 91], "diffs": 7, "drops": []}

- aes-doubleword-loads-0: ATERMAesExpandEncryptKey. Load the 128-bit key as two real 64-bit values before writing the output words. This preserves input/output overlap behavior while moving the word results into split scalar values rather than single-use named u32 copies. {"label": "aes-doubleword-loads-0", "function": "ATERMAesExpandEncryptKey", "score": 98.910446, "insns": [268, 268], "diffs": 9, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.910446]]}

- aes-doubleword-loads-1: ATERMAesExpandEncryptKey. Load the 128-bit key as two real 64-bit values before writing the output words. This preserves input/output overlap behavior while moving the word results into split scalar values rather than single-use named u32 copies. {"label": "aes-doubleword-loads-1", "function": "ATERMAesExpandEncryptKey", "score": 98.910446, "insns": [268, 268], "diffs": 9, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.910446]]}

- aes-doubleword-loads-2: ATERMAesExpandEncryptKey. Load the 128-bit key as two real 64-bit values before writing the output words. This preserves input/output overlap behavior while moving the word results into split scalar values rather than single-use named u32 copies. {"label": "aes-doubleword-loads-2", "function": "ATERMAesExpandEncryptKey", "score": 98.8694, "insns": [268, 268], "diffs": 26, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.8694]]}

- aes-doubleword-loads-3: ATERMAesExpandEncryptKey. Load the 128-bit key as two real 64-bit values before writing the output words. This preserves input/output overlap behavior while moving the word results into split scalar values rather than single-use named u32 copies. {"label": "aes-doubleword-loads-3", "function": "ATERMAesExpandEncryptKey", "score": 99.95522, "insns": [268, 268], "diffs": 2, "drops": []}

- unpack-case-counts: VmBlobUnpack. Target second-pass counts occupy different saved registers by case, and the second format position reuses first-pass blob-offset r23. Split real per-case/per-phase values to expose disjoint lifetimes. {"label": "unpack-case-counts", "function": "VmBlobUnpack", "score": 98.93617, "insns": [517, 517], "diffs": 92, "drops": []}

- unpack-output-position: VmBlobUnpack. Target second-pass counts occupy different saved registers by case, and the second format position reuses first-pass blob-offset r23. Split real per-case/per-phase values to expose disjoint lifetimes. {"label": "unpack-output-position", "function": "VmBlobUnpack", "score": 98.82979, "insns": [517, 517], "diffs": 103, "drops": []}

- unpack-count-and-position: VmBlobUnpack. Target second-pass counts occupy different saved registers by case, and the second format position reuses first-pass blob-offset r23. Split real per-case/per-phase values to expose disjoint lifetimes. {"label": "unpack-count-and-position", "function": "VmBlobUnpack", "score": 98.55899, "insns": [517, 517], "diffs": 130, "drops": []}

- pack-local-values-0: VmBlobPackCommon. Target separates per-format counts and allocates persistent VM/flag before the input and format cursors. Test local lifetime splitting and real declaration ordering, preserving the two passes and calls. {"label": "pack-local-values-0", "function": "VmBlobPackCommon", "score": 98.1512, "insns": [668, 668], "diffs": 223, "drops": []}

- pack-local-values-1: VmBlobPackCommon. Target separates per-format counts and allocates persistent VM/flag before the input and format cursors. Test local lifetime splitting and real declaration ordering, preserving the two passes and calls. {"label": "pack-local-values-1", "function": "VmBlobPackCommon", "score": 98.0988, "insns": [668, 668], "diffs": 230, "drops": []}

- pack-local-values-2: VmBlobPackCommon. Target separates per-format counts and allocates persistent VM/flag before the input and format cursors. Test local lifetime splitting and real declaration ordering, preserving the two passes and calls. {"label": "pack-local-values-2", "function": "VmBlobPackCommon", "score": 98.1512, "insns": [668, 668], "diffs": 223, "drops": []}

- step-target-form-0: CHANSVmStep. Address a structural target difference before allocator ties: explicit zero-step branch, shared result-table base, or indexed type-array traversal. No carrier type or padding is introduced. {"label": "step-target-form-0", "function": "CHANSVmStep", "score": 97.389465, "insns": [1254, 1253], "diffs": 1231, "drops": []}

- step-target-form-1: CHANSVmStep. Address a structural target difference before allocator ties: explicit zero-step branch, shared result-table base, or indexed type-array traversal. No carrier type or padding is introduced. {"label": "step-target-form-1", "function": "CHANSVmStep", "score": 96.843575, "insns": [1254, 1253], "diffs": 1096, "drops": [["CHANSVmStep", 96.98723, 96.843575]]}

- step-target-form-2: CHANSVmStep. Address a structural target difference before allocator ties: explicit zero-step branch, shared result-table base, or indexed type-array traversal. No carrier type or padding is introduced. {"label": "step-target-form-2", "function": "CHANSVmStep", "score": 96.931366, "insns": [1254, 1253], "diffs": 1133, "drops": [["CHANSVmStep", 96.98723, 96.931366]]}

- aes-pair-word-order-1: ATERMAesExpandEncryptKey. Reverse the internal order of two real words in a 64-bit temporary, unpacking them into the same output positions. All byte reads still precede stores; inspect split-value register and scheduling changes. {"label": "aes-pair-word-order-1", "function": "ATERMAesExpandEncryptKey", "score": 98.88806, "insns": [268, 268], "diffs": 17, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.88806]]}

- aes-pair-word-order-2: ATERMAesExpandEncryptKey. Reverse the internal order of two real words in a 64-bit temporary, unpacking them into the same output positions. All byte reads still precede stores; inspect split-value register and scheduling changes. {"label": "aes-pair-word-order-2", "function": "ATERMAesExpandEncryptKey", "score": 98.843285, "insns": [268, 268], "diffs": 19, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.843285]]}

- aes-pair-word-order-3: ATERMAesExpandEncryptKey. Reverse the internal order of two real words in a 64-bit temporary, unpacking them into the same output positions. All byte reads still precede stores; inspect split-value register and scheduling changes. {"label": "aes-pair-word-order-3", "function": "ATERMAesExpandEncryptKey", "score": 98.82089, "insns": [268, 268], "diffs": 27, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.82089]]}

Allocator confirmation date-base: capture `build/rx1b/mwdbg-date-base`, whole-object equality with normal compiler True.

- float-type-u16: CHANSVmConvertToFloatFromStr. Test a value-preserving scalar type for the object type byte at the early scheduler boundary. Reject any extra extension or changed comparison. {"label": "float-type-u16", "function": "CHANSVmConvertToFloatFromStr", "score": 97.59036, "insns": [83, 83], "diffs": 2, "drops": []}

- float-type-s16: CHANSVmConvertToFloatFromStr. Test a value-preserving scalar type for the object type byte at the early scheduler boundary. Reject any extra extension or changed comparison. {"label": "float-type-s16", "function": "CHANSVmConvertToFloatFromStr", "score": 98.07229, "insns": [84, 83], "diffs": 68, "drops": []}

- step-pretest-0: CHANSVmStep. Target branches to the step-count test before the first dispatch. Replace the do-while with a pretest loop, preserving execution count including negative counts until an error, and test explicit zero default. {"label": "step-pretest-0", "function": "CHANSVmStep", "score": 97.35435, "insns": [1255, 1253], "diffs": 1227, "drops": []}

- float-type-s8: CHANSVmConvertToFloatFromStr. Test a value-preserving scalar type for the object type byte at the early scheduler boundary. Reject any extra extension or changed comparison. {"label": "float-type-s8", "function": "CHANSVmConvertToFloatFromStr", "score": 97.59036, "insns": [83, 83], "diffs": 2, "drops": []}

- float-type-unsigned-long: CHANSVmConvertToFloatFromStr. Test a value-preserving scalar type for the object type byte at the early scheduler boundary. Reject any extra extension or changed comparison. {"label": "float-type-unsigned-long", "function": "CHANSVmConvertToFloatFromStr", "score": 97.59036, "insns": [83, 83], "diffs": 2, "drops": []}

- step-pretest-1: CHANSVmStep. Target branches to the step-count test before the first dispatch. Replace the do-while with a pretest loop, preserving execution count including negative counts until an error, and test explicit zero default. {"label": "step-pretest-1", "function": "CHANSVmStep", "score": 97.143654, "insns": [1256, 1253], "diffs": 1229, "drops": []}

- date-table-expression-0: VmDateDtor. The bounds checks guarantee valid small indices. Compare equivalent table-address expressions and index widths to alter early scheduling without changing calls or literal order. {"label": "date-table-expression-0", "function": "VmDateDtor", "score": 94.96703, "insns": [91, 91], "diffs": 7, "drops": []}

- step-pretest-2: CHANSVmStep. Target branches to the step-count test before the first dispatch. Replace the do-while with a pretest loop, preserving execution count including negative counts until an error, and test explicit zero default. {"label": "step-pretest-2", "function": "CHANSVmStep", "score": 96.78771, "insns": [1254, 1253], "diffs": 1239, "drops": [["CHANSVmStep", 96.98723, 96.78771]]}

- date-table-expression-1: VmDateDtor. The bounds checks guarantee valid small indices. Compare equivalent table-address expressions and index widths to alter early scheduling without changing calls or literal order. {"label": "date-table-expression-1", "function": "VmDateDtor", "score": 94.96703, "insns": [91, 91], "diffs": 7, "drops": []}

- date-table-expression-2: VmDateDtor. The bounds checks guarantee valid small indices. Compare equivalent table-address expressions and index widths to alter early scheduling without changing calls or literal order. {"label": "date-table-expression-2", "function": "VmDateDtor", "score": 94.96703, "insns": [91, 91], "diffs": 7, "drops": []}

- date-table-expression-3: VmDateDtor. The bounds checks guarantee valid small indices. Compare equivalent table-address expressions and index widths to alter early scheduling without changing calls or literal order. {"label": "date-table-expression-3", "function": "VmDateDtor", "score": 93.64835, "insns": [91, 91], "diffs": 9, "drops": [["VmDateDtor", 94.96703, 93.64835]]}

- date-table-expression-4: VmDateDtor. The bounds checks guarantee valid small indices. Compare equivalent table-address expressions and index widths to alter early scheduling without changing calls or literal order. {"label": "date-table-expression-4", "function": "VmDateDtor", "score": 93.64835, "insns": [91, 91], "diffs": 9, "drops": [["VmDateDtor", 94.96703, 93.64835]]}

- date-table-expression-5: VmDateDtor. The bounds checks guarantee valid small indices. Compare equivalent table-address expressions and index widths to alter early scheduling without changing calls or literal order. {"label": "date-table-expression-5", "function": "VmDateDtor", "score": 86.2967, "insns": [93, 91], "diffs": 54, "drops": [["VmDateDtor", 94.96703, 86.2967]]}

- date-names-as-parameters: VmDateDtor. Evaluate real month and day name arguments before formatting through a scalar inline helper, with month encountered first. {"label": "date-names-as-parameters", "function": "VmDateDtor", "score": 94.96703, "insns": [91, 91], "diffs": 7, "drops": []}

- write-length-output-0: VmWinEmuWrite. Expose the real length result through a typed output parameter and optional block scope. This can delay scalar promotion relative to the converted object without misusing the VM parameter. {"label": "write-length-output-0", "function": "VmWinEmuWrite", "score": 99.62687, "insns": [67, 67], "diffs": 5, "drops": []}

- aes-doubleword-output-0: ATERMAesExpandEncryptKey. The 64-bit-load variant matches all registers and all reads. Test real output cursor spellings and a sequenced group of natural-order stores; no compiler flags or volatile accesses. {"label": "aes-doubleword-output-0", "function": "ATERMAesExpandEncryptKey", "score": 99.95522, "insns": [268, 268], "diffs": 2, "drops": []}

- write-length-output-1: VmWinEmuWrite. Expose the real length result through a typed output parameter and optional block scope. This can delay scalar promotion relative to the converted object without misusing the VM parameter. {"label": "write-length-output-1", "function": "VmWinEmuWrite", "score": 99.62687, "insns": [67, 67], "diffs": 5, "drops": []}

- aes-doubleword-output-1: ATERMAesExpandEncryptKey. The 64-bit-load variant matches all registers and all reads. Test real output cursor spellings and a sequenced group of natural-order stores; no compiler flags or volatile accesses. {"label": "aes-doubleword-output-1", "function": "ATERMAesExpandEncryptKey", "score": 99.95522, "insns": [268, 268], "diffs": 2, "drops": []}

- aes-doubleword-output-2: ATERMAesExpandEncryptKey. The 64-bit-load variant matches all registers and all reads. Test real output cursor spellings and a sequenced group of natural-order stores; no compiler flags or volatile accesses. {"label": "aes-doubleword-output-2", "function": "ATERMAesExpandEncryptKey", "score": 98.910446, "insns": [268, 268], "diffs": 9, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.910446]]}

- write-length-output-2: VmWinEmuWrite. Expose the real length result through a typed output parameter and optional block scope. This can delay scalar promotion relative to the converted object without misusing the VM parameter. {"label": "write-length-output-2", "function": "VmWinEmuWrite", "score": 99.62687, "insns": [67, 67], "diffs": 5, "drops": []}

- hex-single-position-0: VmBlobGetHexString. Express high and low character positions from one logical position, preserving two source loads. Test whether loop strength reduction gives the second cursor a late virtual register before digit temporaries. {"label": "hex-single-position-0", "function": "VmBlobGetHexString", "score": 93.78049, "insns": [79, 82], "diffs": 34, "drops": [["VmBlobGetHexString", 98.71951, 93.78049]]}

- hex-single-position-1: VmBlobGetHexString. Express high and low character positions from one logical position, preserving two source loads. Test whether loop strength reduction gives the second cursor a late virtual register before digit temporaries. {"label": "hex-single-position-1", "function": "VmBlobGetHexString", "score": 93.78049, "insns": [79, 82], "diffs": 34, "drops": [["VmBlobGetHexString", 98.71951, 93.78049]]}

- hex-single-position-2: VmBlobGetHexString. Express high and low character positions from one logical position, preserving two source loads. Test whether loop strength reduction gives the second cursor a late virtual register before digit temporaries. {"label": "hex-single-position-2", "function": "VmBlobGetHexString", "score": 92.243904, "insns": [79, 82], "diffs": 35, "drops": [["VmBlobGetHexString", 98.71951, 92.243904]]}

- hex-single-position-3: VmBlobGetHexString. Express high and low character positions from one logical position, preserving two source loads. Test whether loop strength reduction gives the second cursor a late virtual register before digit temporaries. {"label": "hex-single-position-3", "function": "VmBlobGetHexString", "score": 92.243904, "insns": [79, 82], "diffs": 35, "drops": [["VmBlobGetHexString", 98.71951, 92.243904]]}

- assoc-scalar-nibbles-0: ATERMBuildAssociationRequest. Replace the genuinely unrolled two-nibble formatting loop with equivalent scalar branches behind an inline boundary; this removes array-derived temporary IDs that currently claim the input pointer target color. {"label": "assoc-scalar-nibbles-0", "function": "ATERMBuildAssociationRequest", "score": 53.857143, "insns": [191, 133], "diffs": 81, "drops": [["ATERMDiscoverAccessPoints", 98.31939, 86.8327], ["ATERMBuildAssociationRequest", 98.7594, 53.857143]]}

- assoc-scalar-nibbles-1: ATERMBuildAssociationRequest. Replace the genuinely unrolled two-nibble formatting loop with equivalent scalar branches behind an inline boundary; this removes array-derived temporary IDs that currently claim the input pointer target color. {"label": "assoc-scalar-nibbles-1", "function": "ATERMBuildAssociationRequest", "score": 53.857143, "insns": [191, 133], "diffs": 81, "drops": [["ATERMDiscoverAccessPoints", 98.31939, 86.8327], ["ATERMBuildAssociationRequest", 98.7594, 53.857143]]}

- assoc-scalar-nibbles-2: ATERMBuildAssociationRequest. Replace the genuinely unrolled two-nibble formatting loop with equivalent scalar branches behind an inline boundary; this removes array-derived temporary IDs that currently claim the input pointer target color. {"label": "assoc-scalar-nibbles-2", "function": "ATERMBuildAssociationRequest", "score": 51.676693, "insns": [191, 133], "diffs": 83, "drops": [["ATERMDiscoverAccessPoints", 98.31939, 86.28137], ["ATERMBuildAssociationRequest", 98.7594, 51.676693]]}

- assoc-nibble-array-u32: ATERMBuildAssociationRequest. Nibbles are always 0..15. Use a value-preserving array element width to test the virtual-register ordering created by unrolling without changing the formatting branches. {"label": "assoc-nibble-array-u32", "function": "ATERMBuildAssociationRequest", "score": 98.7594, "insns": [133, 133], "diffs": 28, "drops": []}

- assoc-nibble-array-u16: ATERMBuildAssociationRequest. Nibbles are always 0..15. Use a value-preserving array element width to test the virtual-register ordering created by unrolling without changing the formatting branches. {"label": "assoc-nibble-array-u16", "function": "ATERMBuildAssociationRequest", "score": 97.25564, "insns": [135, 133], "diffs": 70, "drops": [["ATERMDiscoverAccessPoints", 98.31939, 97.93916], ["ATERMBuildAssociationRequest", 98.7594, 97.25564]]}

- assoc-nibble-array-s16: ATERMBuildAssociationRequest. Nibbles are always 0..15. Use a value-preserving array element width to test the virtual-register ordering created by unrolling without changing the formatting branches. {"label": "assoc-nibble-array-s16", "function": "ATERMBuildAssociationRequest", "score": 96.2782, "insns": [135, 133], "diffs": 82, "drops": [["ATERMDiscoverAccessPoints", 98.31939, 97.539925], ["ATERMBuildAssociationRequest", 98.7594, 96.2782]]}

- assoc-nibble-array-u8: ATERMBuildAssociationRequest. Nibbles are always 0..15. Use a value-preserving array element width to test the virtual-register ordering created by unrolling without changing the formatting branches. {"label": "assoc-nibble-array-u8", "function": "ATERMBuildAssociationRequest", "score": 97.25564, "insns": [135, 133], "diffs": 70, "drops": [["ATERMDiscoverAccessPoints", 98.31939, 97.93916], ["ATERMBuildAssociationRequest", 98.7594, 97.25564]]}

- assoc-nibble-array-s8: ATERMBuildAssociationRequest. Nibbles are always 0..15. Use a value-preserving array element width to test the virtual-register ordering created by unrolling without changing the formatting branches. {"label": "assoc-nibble-array-s8", "function": "ATERMBuildAssociationRequest", "score": 94.77444, "insns": [137, 133], "diffs": 82, "drops": [["ATERMDiscoverAccessPoints", 98.31939, 97.1597], ["ATERMBuildAssociationRequest", 98.7594, 94.77444]]}

Initial new manual findings: Unpack per-case count scopes improve 141 to 92 differences, but combining separate first/second parser positions regresses to 130. AES two 64-bit input values preserve every initial read before any output store and reproduce the same 2 store-order differences as the old scratch. Neither gain is retained without exactness. The first Write length-boundary trial included an unused zero initialization; rejected for source quality as well as its sixth instruction difference. All later Write trials omit such initialization.

Queued source searches: seeds 301/302/303, 1200 seconds each, anneal, all ten requested functions, shared 24-slot limiter unchanged. Association searches its actual inlined MAC formatter, nup its actual tag helper, Float its parser. Large-function seeds begin from the improved per-case-count source for Pack/Unpack. Search job arguments and PIDs are in `build/rx1b/search/jobs*.json`. A queued job has not consumed its compile budget.

Ghidra export inspection: Float, Date, Pack and Unpack bodies copied to `build/rx1b/*.ghidra.c`. CHANSVmStep is only a halt_baddata stub in the installed export, so its target assembly remains the authority; no C reconstruction is inferred from that stub.

- float-parser-boundary-0: CHANSVmConvertToFloatFromStr. The one-use parser is inline in the target. Test its real scope and parameter boundary to alter early scheduling while keeping all parsing branches and result semantics intact. {"label": "float-parser-boundary-0", "function": "CHANSVmConvertToFloatFromStr", "score": 96.50603, "insns": [83, 83], "diffs": 18, "drops": [["CHANSVmConvertToFloatFromStr", 97.59036, 96.50603]]}

- float-parser-boundary-1: CHANSVmConvertToFloatFromStr. The one-use parser is inline in the target. Test its real scope and parameter boundary to alter early scheduling while keeping all parsing branches and result semantics intact. {"label": "float-parser-boundary-1", "function": "CHANSVmConvertToFloatFromStr", "score": 96.50603, "insns": [83, 83], "diffs": 18, "drops": [["CHANSVmConvertToFloatFromStr", 97.59036, 96.50603]]}

- float-parser-boundary-2: CHANSVmConvertToFloatFromStr. The one-use parser is inline in the target. Test its real scope and parameter boundary to alter early scheduling while keeping all parsing branches and result semantics intact. {"label": "float-parser-boundary-2", "function": "CHANSVmConvertToFloatFromStr", "score": 97.59036, "insns": [83, 83], "diffs": 2, "drops": []}

- float-parser-boundary-3: CHANSVmConvertToFloatFromStr. The one-use parser is inline in the target. Test its real scope and parameter boundary to alter early scheduling while keeping all parsing branches and result semantics intact. {"label": "float-parser-boundary-3", "function": "CHANSVmConvertToFloatFromStr", "score": 97.59036, "insns": [83, 83], "diffs": 2, "drops": []}

Allocator confirmation unpack-base: capture `build/rx1b/mwdbg-unpack-base`, whole-object equality with normal compiler True.

- unpack-color-order-0: VmBlobUnpack. The verified baseline graph colors late SSA counts before persistent source/format values. Use per-case count scopes plus target-ranked real declaration order; synthetic second format position can be separated by phase. {"label": "unpack-color-order-0", "function": "VmBlobUnpack", "score": 98.71373, "insns": [517, 517], "diffs": 120, "drops": []}

- unpack-color-order-1: VmBlobUnpack. The verified baseline graph colors late SSA counts before persistent source/format values. Use per-case count scopes plus target-ranked real declaration order; synthetic second format position can be separated by phase. {"label": "unpack-color-order-1", "function": "VmBlobUnpack", "score": 99.13927, "insns": [517, 517], "diffs": 77, "drops": []}

- unpack-color-order-2: VmBlobUnpack. The verified baseline graph colors late SSA counts before persistent source/format values. Use per-case count scopes plus target-ranked real declaration order; synthetic second format position can be separated by phase. {"label": "unpack-color-order-2", "function": "VmBlobUnpack", "score": 98.71373, "insns": [517, 517], "diffs": 120, "drops": []}

- unpack-color-order-3: VmBlobUnpack. The verified baseline graph colors late SSA counts before persistent source/format values. Use per-case count scopes plus target-ranked real declaration order; synthetic second format position can be separated by phase. {"label": "unpack-color-order-3", "function": "VmBlobUnpack", "score": 99.13927, "insns": [517, 517], "diffs": 77, "drops": []}

- unpack-color-order-4: VmBlobUnpack. The verified baseline graph colors late SSA counts before persistent source/format values. Use per-case count scopes plus target-ranked real declaration order; synthetic second format position can be separated by phase. {"label": "unpack-color-order-4", "function": "VmBlobUnpack", "score": 99.09091, "insns": [517, 517], "diffs": 81, "drops": []}

- unpack-color-order-5: VmBlobUnpack. The verified baseline graph colors late SSA counts before persistent source/format values. Use per-case count scopes plus target-ranked real declaration order; synthetic second format position can be separated by phase. {"label": "unpack-color-order-5", "function": "VmBlobUnpack", "score": 98.68472, "insns": [517, 517], "diffs": 121, "drops": []}

- unpack-color-order-6: VmBlobUnpack. The verified baseline graph colors late SSA counts before persistent source/format values. Use per-case count scopes plus target-ranked real declaration order; synthetic second format position can be separated by phase. {"label": "unpack-color-order-6", "function": "VmBlobUnpack", "score": 99.03288, "insns": [517, 517], "diffs": 86, "drops": []}

- unpack-color-order-7: VmBlobUnpack. The verified baseline graph colors late SSA counts before persistent source/format values. Use per-case count scopes plus target-ranked real declaration order; synthetic second format position can be separated by phase. {"label": "unpack-color-order-7", "function": "VmBlobUnpack", "score": 98.55899, "insns": [517, 517], "diffs": 130, "drops": []}

## Unpack baseline allocator

Target VM r30 and return object r31 already match. Target blob r25, format pointer r21, format length r20, first-pass blob offset r23, array count r22, output element index r24 and integer loop index r26 differ. The dump uses v61 blob->r24, v59 format->r23, v58 length->r22, v57 blob offset->r25, v56 array count->r26, v53 output index->r21, v52 integer index->r20. The shared source `count` becomes separate SSA values v68 through v71. v69/v70/v71 color at ranks 11/10/9 before persistent v61/v59/v58 at ranks 12/13/14, occupying r25 in disjoint cases. Synthetic second format position v72 colors at rank8 to r26. The graph has no spills; 944 GPR rewrite operands validate with zero mismatches and the complete normal object matches. The local simplify/color model reproduces the exact baseline priority order, so it can propose declaration and scope candidates. Source changes still require real compiler and debugger confirmation.

The first offline declaration-order model accidentally swapped desired integer-count and hex-count colors; its output is discarded. The corrected model maps v69 integer count to r22 and v71 hex count to r19. Only actual compiled source results count as progress.

- unpack-case-counts-element-scope-0: VmBlobUnpack. The same named result pointer is split into several SSA values in the baseline. Give each output case its own genuine object/result and optionally scope the integer iterator/value so target r22/r26 lifetimes can be reused. {"label": "unpack-case-counts-element-scope-0", "function": "VmBlobUnpack", "score": 98.75242, "insns": [517, 517], "diffs": 107, "drops": []}

- unpack-case-counts-element-scope-1: VmBlobUnpack. The same named result pointer is split into several SSA values in the baseline. Give each output case its own genuine object/result and optionally scope the integer iterator/value so target r22/r26 lifetimes can be reused. {"label": "unpack-case-counts-element-scope-1", "function": "VmBlobUnpack", "score": 98.646034, "insns": [517, 517], "diffs": 118, "drops": []}

- unpack-color-order-1-element-scope-0: VmBlobUnpack. The same named result pointer is split into several SSA values in the baseline. Give each output case its own genuine object/result and optionally scope the integer iterator/value so target r22/r26 lifetimes can be reused. {"label": "unpack-color-order-1-element-scope-0", "function": "VmBlobUnpack", "score": 98.95551, "insns": [517, 517], "diffs": 92, "drops": []}

- unpack-color-order-1-element-scope-1: VmBlobUnpack. The same named result pointer is split into several SSA values in the baseline. Give each output case its own genuine object/result and optionally scope the integer iterator/value so target r22/r26 lifetimes can be reused. {"label": "unpack-color-order-1-element-scope-1", "function": "VmBlobUnpack", "score": 98.26886, "insns": [517, 517], "diffs": 156, "drops": [["VmBlobUnpack", 98.452614, 98.26886]]}

- unpack-color-order-4-element-scope-0: VmBlobUnpack. The same named result pointer is split into several SSA values in the baseline. Give each output case its own genuine object/result and optionally scope the integer iterator/value so target r22/r26 lifetimes can be reused. {"label": "unpack-color-order-4-element-scope-0", "function": "VmBlobUnpack", "score": 98.90716, "insns": [517, 517], "diffs": 96, "drops": []}

- unpack-color-order-4-element-scope-1: VmBlobUnpack. The same named result pointer is split into several SSA values in the baseline. Give each output case its own genuine object/result and optionally scope the integer iterator/value so target r22/r26 lifetimes can be reused. {"label": "unpack-color-order-4-element-scope-1", "function": "VmBlobUnpack", "score": 98.77176, "insns": [517, 517], "diffs": 109, "drops": []}

- unpack-named-lifetimes-0: VmBlobUnpack. The exact baseline allocation model needs the late SSA count and second-parser-position nodes interleaved with persistent input locals. Represent each actual format count and parser phase by a named scalar at function scope so declaration order can express that graph order. {"label": "unpack-named-lifetimes-0", "function": "VmBlobUnpack", "score": 98.71373, "insns": [517, 517], "diffs": 118, "drops": []}

- unpack-named-lifetimes-1: VmBlobUnpack. The exact baseline allocation model needs the late SSA count and second-parser-position nodes interleaved with persistent input locals. Represent each actual format count and parser phase by a named scalar at function scope so declaration order can express that graph order. {"label": "unpack-named-lifetimes-1", "function": "VmBlobUnpack", "score": 98.71373, "insns": [517, 517], "diffs": 118, "drops": []}

- unpack-named-lifetimes-2: VmBlobUnpack. The exact baseline allocation model needs the late SSA count and second-parser-position nodes interleaved with persistent input locals. Represent each actual format count and parser phase by a named scalar at function scope so declaration order can express that graph order. {"label": "unpack-named-lifetimes-2", "function": "VmBlobUnpack", "score": 98.71373, "insns": [517, 517], "diffs": 118, "drops": []}

Allocator confirmation aes-doubleword-loads-3: capture `build/rx1b/mwdbg-aes-doubleword-loads-3`, whole-object equality with normal compiler True.

- aes-initial-boundary-0: ATERMAesExpandEncryptKey. Keep the real two-half key load and stores but change the key-size guard or scalar lifetime boundary. Check whether the early scheduler changes store order without adding a branch or altering data accesses. {"label": "aes-initial-boundary-0", "function": "ATERMAesExpandEncryptKey", "score": 99.95522, "insns": [268, 268], "diffs": 2, "drops": []}

- aes-initial-boundary-1: ATERMAesExpandEncryptKey. Keep the real two-half key load and stores but change the key-size guard or scalar lifetime boundary. Check whether the early scheduler changes store order without adding a branch or altering data accesses. {"label": "aes-initial-boundary-1", "function": "ATERMAesExpandEncryptKey", "score": 99.95522, "insns": [268, 268], "diffs": 2, "drops": []}

- aes-initial-boundary-2: ATERMAesExpandEncryptKey. Keep the real two-half key load and stores but change the key-size guard or scalar lifetime boundary. Check whether the early scheduler changes store order without adding a branch or altering data accesses. {"label": "aes-initial-boundary-2", "function": "ATERMAesExpandEncryptKey", "score": 99.95522, "insns": [268, 268], "diffs": 2, "drops": []}

- aes-pair-extraction-0: ATERMAesExpandEncryptKey. With all initial input reads complete, write outputs in natural order and vary actual 64-bit word extraction. Check whether scalar splitting retains the target arithmetic order and colors before scheduling stores. {"label": "aes-pair-extraction-0", "function": "ATERMAesExpandEncryptKey", "score": 98.910446, "insns": [268, 268], "diffs": 9, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.910446]]}

- aes-pair-extraction-1: ATERMAesExpandEncryptKey. With all initial input reads complete, write outputs in natural order and vary actual 64-bit word extraction. Check whether scalar splitting retains the target arithmetic order and colors before scheduling stores. {"label": "aes-pair-extraction-1", "function": "ATERMAesExpandEncryptKey", "score": 91.60448, "insns": [271, 268], "diffs": 262, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 91.60448]]}

- aes-pair-extraction-2: ATERMAesExpandEncryptKey. With all initial input reads complete, write outputs in natural order and vary actual 64-bit word extraction. Check whether scalar splitting retains the target arithmetic order and colors before scheduling stores. {"label": "aes-pair-extraction-2", "function": "ATERMAesExpandEncryptKey", "score": 91.60448, "insns": [271, 268], "diffs": 262, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 91.60448]]}

- aes-pair-extraction-3: ATERMAesExpandEncryptKey. With all initial input reads complete, write outputs in natural order and vary actual 64-bit word extraction. Check whether scalar splitting retains the target arithmetic order and colors before scheduling stores. {"label": "aes-pair-extraction-3", "function": "ATERMAesExpandEncryptKey", "score": 91.60448, "insns": [271, 268], "diffs": 262, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 91.60448]]}

- aes-pair-extraction-4: ATERMAesExpandEncryptKey. With all initial input reads complete, write outputs in natural order and vary actual 64-bit word extraction. Check whether scalar splitting retains the target arithmetic order and colors before scheduling stores. {"label": "aes-pair-extraction-4", "function": "ATERMAesExpandEncryptKey", "error": "### mwcceppc.exe Compiler:\n#    File: build\\rx1b\\trials\\aes-pair-extraction-4\\ATERM.c\n# --------------------------------------------------------\n#    1939:     u32 firstWord = (u32)(firstHalf >> 32); \n#   Error:     ^^^\n#   (10141) expression syntax error\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\n"}

- aes-pair-extraction-5: ATERMAesExpandEncryptKey. With all initial input reads complete, write outputs in natural order and vary actual 64-bit word extraction. Check whether scalar splitting retains the target arithmetic order and colors before scheduling stores. {"label": "aes-pair-extraction-5", "function": "ATERMAesExpandEncryptKey", "score": 98.910446, "insns": [268, 268], "diffs": 9, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.910446]]}

AES new confirmation `build/rx1b/mwdbg-aes-doubleword-loads-3`: full object equals normal compiler, 546 GPR and 12 CR rewrites, zero mismatches. The four word results are anonymous v60/v73/v84/v97, assigned target r27/r10/r8/r0 at coloring ranks 231/218/207/194. The real 64-bit source values become dead scalar pair nodes; both halves are read before stores. Initial PCode, backend-01, backend-02 and backend-04 all keep source output order 0,3,2,1. The two final differences remain store1/store3 order, not a register tie. Natural-order outputs instead disturb nine initial instructions. No partial AES change is retained.

CHANSVmStep disasm_fn.py stops after four instructions at the paired-single save. Re-read all 1253 target/current words through odiff.dis, storing `CHANSVmStep.{obj,src}.full.txt`. Target has explicit zero-step defaulting, an initial jump to `cmpwi count,0; addi count,-1`, and one shared data base. Baseline uses branchless defaulting, a do-while compare against one, and a second result-table base. Treating all 276 differences as register-only would be wrong.

- step-postdecrement-test-0: CHANSVmStep. The full target stream tests count against zero and decrements at the test, with an initial jump. Use the exact while(count-- != 0) control flow, plus independent direct table/index reconstruction. Capstone bulk disassembly stops at paired-single saves, so compare the entire stream with odiff.dis. {"label": "step-postdecrement-test-0", "function": "CHANSVmStep", "score": 97.51796, "insns": [1255, 1253], "diffs": 1227, "drops": []}

- step-postdecrement-test-1: CHANSVmStep. The full target stream tests count against zero and decrements at the test, with an initial jump. Use the exact while(count-- != 0) control flow, plus independent direct table/index reconstruction. Capstone bulk disassembly stops at paired-single saves, so compare the entire stream with odiff.dis. {"label": "step-postdecrement-test-1", "function": "CHANSVmStep", "score": 97.30727, "insns": [1256, 1253], "diffs": 1229, "drops": []}

- step-postdecrement-test-2: CHANSVmStep. The full target stream tests count against zero and decrements at the test, with an initial jump. Use the exact while(count-- != 0) control flow, plus independent direct table/index reconstruction. Capstone bulk disassembly stops at paired-single saves, so compare the entire stream with odiff.dis. {"label": "step-postdecrement-test-2", "function": "CHANSVmStep", "score": 97.33121, "insns": [1256, 1253], "diffs": 1224, "drops": []}

- step-postdecrement-test-3: CHANSVmStep. The full target stream tests count against zero and decrements at the test, with an initial jump. Use the exact while(count-- != 0) control flow, plus independent direct table/index reconstruction. Capstone bulk disassembly stops at paired-single saves, so compare the entire stream with odiff.dis. {"label": "step-postdecrement-test-3", "function": "CHANSVmStep", "score": 97.13966, "insns": [1257, 1253], "diffs": 1215, "drops": []}

- step-flat-temporaries-0: CHANSVmStep. Replace the existing anonymous scratch aggregate with the actual independent interpreter temporaries. Use normal declarations, with no new carrier, dummy padding, or fixed offsets; compare compiler stack reuse against the target. {"label": "step-flat-temporaries-0", "function": "CHANSVmStep", "score": 97.1229, "insns": [1257, 1253], "diffs": 1215, "drops": []}

- step-flat-temporaries-1: CHANSVmStep. Replace the existing anonymous scratch aggregate with the actual independent interpreter temporaries. Use normal declarations, with no new carrier, dummy padding, or fixed offsets; compare compiler stack reuse against the target. {"label": "step-flat-temporaries-1", "function": "CHANSVmStep", "score": 97.12689, "insns": [1257, 1253], "diffs": 1215, "drops": []}

- step-flat-temporaries-2: CHANSVmStep. Replace the existing anonymous scratch aggregate with the actual independent interpreter temporaries. Use normal declarations, with no new carrier, dummy padding, or fixed offsets; compare compiler stack reuse against the target. {"label": "step-flat-temporaries-2", "function": "CHANSVmStep", "score": 97.1229, "insns": [1257, 1253], "diffs": 1215, "drops": []}

- step-type-table-0: CHANSVmStep. Target keeps right/left type bytes in r27/r14 and computes the row address before adding the second index. Change real declaration order, equivalent selection and table-row addressing to remove a spill and match that dataflow. {"label": "step-type-table-0", "function": "CHANSVmStep", "score": 97.179565, "insns": [1257, 1253], "diffs": 1216, "drops": []}

- step-type-table-1: CHANSVmStep. Target keeps right/left type bytes in r27/r14 and computes the row address before adding the second index. Change real declaration order, equivalent selection and table-row addressing to remove a spill and match that dataflow. {"label": "step-type-table-1", "function": "CHANSVmStep", "score": 97.151634, "insns": [1257, 1253], "diffs": 1216, "drops": []}

- step-type-table-2: CHANSVmStep. Target keeps right/left type bytes in r27/r14 and computes the row address before adding the second index. Change real declaration order, equivalent selection and table-row addressing to remove a spill and match that dataflow. {"label": "step-type-table-2", "function": "CHANSVmStep", "score": 97.143654, "insns": [1257, 1253], "diffs": 1216, "drops": []}

- step-type-table-3: CHANSVmStep. Target keeps right/left type bytes in r27/r14 and computes the row address before adding the second index. Change real declaration order, equivalent selection and table-row addressing to remove a spill and match that dataflow. {"label": "step-type-table-3", "function": "CHANSVmStep", "score": 97.171585, "insns": [1257, 1253], "diffs": 1215, "drops": []}

- step-type-table-4: CHANSVmStep. Target keeps right/left type bytes in r27/r14 and computes the row address before adding the second index. Change real declaration order, equivalent selection and table-row addressing to remove a spill and match that dataflow. {"label": "step-type-table-4", "function": "CHANSVmStep", "score": 97.147644, "insns": [1257, 1253], "diffs": 1216, "drops": []}

- step-type-table-5: CHANSVmStep. Target keeps right/left type bytes in r27/r14 and computes the row address before adding the second index. Change real declaration order, equivalent selection and table-row addressing to remove a spill and match that dataflow. {"label": "step-type-table-5", "function": "CHANSVmStep", "score": 97.13966, "insns": [1257, 1253], "diffs": 1216, "drops": []}

## Float and Date baseline decisions

Float target/source both hold new object r27, original string/buffer end r28, character/constant index r29, coalesced zero/table-byte index r30 and constant-table base r31. In the dump, newObj v34 has 27 neighbors, object v33 15, constant zero v46 21, and table v51 17. No register choice is wrong. Initial type v37->r0 and zero v46->r30 produce the correct lbz/li operands. Backend-01 has already moved the cmpli ahead of the endPtr stw; final backend-04 retains it. Parser boundary/type/index-width variants either preserve these two differences or add instructions.

Date target/source both hold VM r28, return object r29, date address r30, shared data base r31, month index r3, weekday index r4, year r6, date/hour/minute in r8/r9/r10. Month-table base v50 colors sixth to r3 with degree12; month offset v49 colors seventh to r0 with degree12; day-table base v48 colors eighth to r4 with degree13 and day offset v47 ninth to r5 with degree12. These are target colors. Source backend-01 schedules the day-table address/load first, which forces the year in r6 to be stored before the day name overwrites it. Target loads month first and stores year later. Explicit month/day locals and scalar formatter/name helpers are propagated away; narrower indices add masks. No allocator coalescing change is needed here.

Allocator confirmation pack-base: capture `build/rx1b/mwdbg-pack-base`, whole-object equality with normal compiler True.

## Pack baseline allocator

Target flag r31 and VM r30, parent blob r21, format pointer r20, format length r19, argument array r18. Baseline colors the high-degree core in the reverse preference: parentBlob v58 rank1 ->r31, fmtStr v56 rank2 ->r30, fmtLen v55 rank3 ->r29, argArr v54 rank4 ->r28, flag v35 rank5 ->r27, VM v32 rank6 ->r26. Initial degrees are 130/129/128/128/129/129. No spills occur; allocator simulation reproduces the exact priority. The complete normal object is identical and 1448 GPR / 437 CR operand rewrites pass. Per-case counts alone cannot change this six-value core, explaining their small 230->223 difference improvement.

Degree precision for Float/Date: the earlier Date degree numbers describe the interference graph before simplification. Actual removal degrees are month-base v50=6, month-offset v49=6, day-base v48=7, day-offset v47=7. Float actual removal degrees are newObj v34=26, object v33=15, type v37=2, zero v46=13, table v51=12. Both functions still choose all target registers.

- pack-parameter-binding-0: VmBlobPackCommon. Baseline core colors parentBlob/format/array first, VM sixth and flag fifth; target VM/flag color first. Test actual typed local bindings of the VM and create flag, preserving all calls and conditions, then verify whether copies survive. {"label": "pack-parameter-binding-0", "function": "VmBlobPackCommon", "score": 98.0988, "insns": [668, 668], "diffs": 230, "drops": []}

- pack-parameter-binding-1: VmBlobPackCommon. Baseline core colors parentBlob/format/array first, VM sixth and flag fifth; target VM/flag color first. Test actual typed local bindings of the VM and create flag, preserving all calls and conditions, then verify whether copies survive. {"label": "pack-parameter-binding-1", "function": "VmBlobPackCommon", "score": 98.0988, "insns": [668, 668], "diffs": 230, "drops": []}

- pack-parameter-binding-2: VmBlobPackCommon. Baseline core colors parentBlob/format/array first, VM sixth and flag fifth; target VM/flag color first. Test actual typed local bindings of the VM and create flag, preserving all calls and conditions, then verify whether copies survive. {"label": "pack-parameter-binding-2", "function": "VmBlobPackCommon", "score": 98.0988, "insns": [668, 668], "diffs": 230, "drops": []}

- pack-parameter-binding-3: VmBlobPackCommon. Baseline core colors parentBlob/format/array first, VM sixth and flag fifth; target VM/flag color first. Test actual typed local bindings of the VM and create flag, preserving all calls and conditions, then verify whether copies survive. {"label": "pack-parameter-binding-3", "function": "VmBlobPackCommon", "score": 98.0988, "insns": [668, 668], "diffs": 230, "drops": []}

- pack-argument-lifetime-0: VmBlobPackCommon. The converted format argument dies before the converted array argument is fetched, and target both use r18. Reuse that actual object binding and test the format-pointer const boundary, without changing any call or parser use. {"label": "pack-argument-lifetime-0", "function": "VmBlobPackCommon", "score": 98.0988, "insns": [668, 668], "diffs": 230, "drops": []}

- pack-argument-lifetime-1: VmBlobPackCommon. The converted format argument dies before the converted array argument is fetched, and target both use r18. Reuse that actual object binding and test the format-pointer const boundary, without changing any call or parser use. {"label": "pack-argument-lifetime-1", "function": "VmBlobPackCommon", "score": 98.0988, "insns": [668, 668], "diffs": 230, "drops": []}

- pack-argument-lifetime-2: VmBlobPackCommon. The converted format argument dies before the converted array argument is fetched, and target both use r18. Reuse that actual object binding and test the format-pointer const boundary, without changing any call or parser use. {"label": "pack-argument-lifetime-2", "function": "VmBlobPackCommon", "score": 98.0988, "insns": [668, 668], "diffs": 230, "drops": []}

- pack-valid-case-counts: VmBlobPackCommon. Source audit removed the unused case-4 count accidentally introduced by the first scope batch. Keep only counts that the numeric/string/hex cases actually use. No candidate with an unused local may be retained. {"label": "pack-valid-case-counts", "function": "VmBlobPackCommon", "score": 98.1512, "insns": [668, 668], "diffs": 223, "drops": []}

Source audit: the first Pack case-scope generator inserted an unused count in case4, which actually uses copySize. Those scratch candidates are rejected. Removed that declaration in `pack-valid-case-counts`; the three original Pack searches had not obtained CPU slots or compiled anything. Terminated only those recorded owned queued PIDs and restarted seeds301/302/303 from the corrected source, retaining the shared limiter and full1200-second budget.

## Fresh baseline instruction classification

- ATERMBuildAssociationRequest: 28 differing positions, 28 differing only in register names; 0 scheduling, address, or control-flow positions.
- ATERMAesExpandEncryptKey: 49 differing positions, 31 differing only in register names; 18 scheduling, address, or control-flow positions.
- CHANSVmConvertToFloatFromStr: 2 differing positions, 0 differing only in register names; 2 scheduling, address, or control-flow positions.
- VmDateDtor: 7 differing positions, 1 differing only in register names; 6 scheduling, address, or control-flow positions.
- VmBlobGetHexString: 14 differing positions, 14 differing only in register names; 0 scheduling, address, or control-flow positions.
- VmBlobPackCommon: 230 differing positions, 230 differing only in register names; 0 scheduling, address, or control-flow positions.
- VmBlobUnpack: 141 differing positions, 141 differing only in register names; 0 scheduling, address, or control-flow positions.
- VmWinEmuWrite: 5 differing positions, 5 differing only in register names; 0 scheduling, address, or control-flow positions.
- CHANSVmStep: 276 differing positions, 164 differing only in register names; 112 scheduling, address, or control-flow positions.
- __nupParseServerInfo__FP14NUPContextInfoPcPcUx: 66 differing positions, 66 differing only in register names; 0 scheduling, address, or control-flow positions.

Classification compares each complete fixed-width PPC word, preserving branch displacements. It is not a claim of semantic equivalence or an exact-match substitute. Paired-single encodings not decoded by Capstone remain raw words.

- hex-derived-low-position-0: VmBlobGetHexString. Preserve the high-digit destination cursor, but derive the low-digit index from the real loop index. Strength reduction can now synthesize both character and byte cursors late enough to color before anonymous digit temporaries. {"label": "hex-derived-low-position-0", "function": "VmBlobGetHexString", "score": 95.53658, "insns": [81, 82], "diffs": 35, "drops": [["VmBlobGetHexString", 98.71951, 95.53658]]}

- hex-derived-low-position-1: VmBlobGetHexString. Preserve the high-digit destination cursor, but derive the low-digit index from the real loop index. Strength reduction can now synthesize both character and byte cursors late enough to color before anonymous digit temporaries. {"label": "hex-derived-low-position-1", "function": "VmBlobGetHexString", "score": 95.53658, "insns": [81, 82], "diffs": 35, "drops": [["VmBlobGetHexString", 98.71951, 95.53658]]}

- hex-derived-low-position-2: VmBlobGetHexString. Preserve the high-digit destination cursor, but derive the low-digit index from the real loop index. Strength reduction can now synthesize both character and byte cursors late enough to color before anonymous digit temporaries. {"label": "hex-derived-low-position-2", "function": "VmBlobGetHexString", "score": 95.53658, "insns": [81, 82], "diffs": 35, "drops": [["VmBlobGetHexString", 98.71951, 95.53658]]}

- float-constant-loop-0: CHANSVmConvertToFloatFromStr. The end-pointer zero is coalesced with the later constant-table byte index. Test the genuine lookup loop initialization/syntax to change that zero value lifetime and early scheduling, preserving all four comparisons. {"label": "float-constant-loop-0", "function": "CHANSVmConvertToFloatFromStr", "score": 95.54217, "insns": [83, 83], "diffs": 31, "drops": [["CHANSVmConvertToFloatFromStr", 97.59036, 95.54217]]}

- float-constant-loop-1: CHANSVmConvertToFloatFromStr. The end-pointer zero is coalesced with the later constant-table byte index. Test the genuine lookup loop initialization/syntax to change that zero value lifetime and early scheduling, preserving all four comparisons. {"label": "float-constant-loop-1", "function": "CHANSVmConvertToFloatFromStr", "score": 97.59036, "insns": [83, 83], "diffs": 2, "drops": []}

- float-constant-loop-2: CHANSVmConvertToFloatFromStr. The end-pointer zero is coalesced with the later constant-table byte index. Test the genuine lookup loop initialization/syntax to change that zero value lifetime and early scheduling, preserving all four comparisons. {"label": "float-constant-loop-2", "function": "CHANSVmConvertToFloatFromStr", "score": 97.59036, "insns": [83, 83], "diffs": 2, "drops": []}

Allocator confirmation unpack-case-counts: capture `build/rx1b/mwdbg-unpack-case-counts`, whole-object equality with normal compiler True.

- unpack-flat-values-0: VmBlobUnpack. Give every real decoded count, object and data cursor a distinct semantic name and normal function-scope declaration. Initializations stay at their original execution points. This makes the allocator graph ordering expressible without carriers or dummy variables. {"label": "unpack-flat-values-0", "function": "VmBlobUnpack", "score": 98.27853, "insns": [517, 517], "diffs": 153, "drops": [["VmBlobUnpack", 98.452614, 98.27853]]}

- unpack-flat-values-1: VmBlobUnpack. Give every real decoded count, object and data cursor a distinct semantic name and normal function-scope declaration. Initializations stay at their original execution points. This makes the allocator graph ordering expressible without carriers or dummy variables. {"label": "unpack-flat-values-1", "function": "VmBlobUnpack", "score": 99.2263, "insns": [517, 517], "diffs": 71, "drops": []}

Private lightweight debugger mode for declaration-order modeling: `build/rx1b/gc3-graphs.py` keeps only pass-start, before-simplify, color-start/end and after-rewrite breakpoints, plus the five backend stages. It reads the actual graph/priority/final colors and still checks every register rewrite and whole-object equality, but does not claim chronological coalescing/simplify events. The existing full driver is unchanged. Both launchers keep the same shared GDB lock and pinned compiler. Any exact retained candidate will still receive full trace confirmation.

- pack-case-local-values-0: VmBlobPackCommon. Scope every genuinely case-local count, object, byte/word value and buffer in the sizing pass, writing pass, or both. Remove outer declarations made unused by the change. This tests whether reducing SSA merges lowers the persistent-pointer degrees before the parameter core is simplified. {"label": "pack-case-local-values-0", "function": "VmBlobPackCommon", "score": 98.0988, "insns": [668, 668], "diffs": 230, "drops": []}

- pack-case-local-values-1: VmBlobPackCommon. Scope every genuinely case-local count, object, byte/word value and buffer in the sizing pass, writing pass, or both. Remove outer declarations made unused by the change. This tests whether reducing SSA merges lowers the persistent-pointer degrees before the parameter core is simplified. {"label": "pack-case-local-values-1", "function": "VmBlobPackCommon", "score": 98.83234, "insns": [668, 668], "diffs": 141, "drops": []}

- pack-case-local-values-2: VmBlobPackCommon. Scope every genuinely case-local count, object, byte/word value and buffer in the sizing pass, writing pass, or both. Remove outer declarations made unused by the change. This tests whether reducing SSA merges lowers the persistent-pointer degrees before the parameter core is simplified. {"label": "pack-case-local-values-2", "function": "VmBlobPackCommon", "score": 98.83234, "insns": [668, 668], "diffs": 141, "drops": []}

Full case-local scoping improves Pack 230->141 differences with 668/668 instructions; the first sizing pass alone does nothing. The writing pass determines the surviving graph ordering. Unpack distinct function-scope scalar values improve its best 77->71 differences with 517/517 instructions. These remain scratch-only pending complete matching.

- pack-object-order-0: VmBlobPackCommon. Pack case scopes already give VM and flag target r30/r31. The sizing-pass object should take r25 before the persistent values currently shifted up one register. Move the real object declaration around those values and check allocator priority without modifying execution. {"label": "pack-object-order-0", "function": "VmBlobPackCommon", "score": 98.83234, "insns": [668, 668], "diffs": 141, "drops": []}

- pack-object-order-1: VmBlobPackCommon. Pack case scopes already give VM and flag target r30/r31. The sizing-pass object should take r25 before the persistent values currently shifted up one register. Move the real object declaration around those values and check allocator priority without modifying execution. {"label": "pack-object-order-1", "function": "VmBlobPackCommon", "score": 98.83234, "insns": [668, 668], "diffs": 141, "drops": []}

- pack-object-order-2: VmBlobPackCommon. Pack case scopes already give VM and flag target r30/r31. The sizing-pass object should take r25 before the persistent values currently shifted up one register. Move the real object declaration around those values and check allocator priority without modifying execution. {"label": "pack-object-order-2", "function": "VmBlobPackCommon", "score": 98.83234, "insns": [668, 668], "diffs": 141, "drops": []}

- pack-object-order-3: VmBlobPackCommon. Pack case scopes already give VM and flag target r30/r31. The sizing-pass object should take r25 before the persistent values currently shifted up one register. Move the real object declaration around those values and check allocator priority without modifying execution. {"label": "pack-object-order-3", "function": "VmBlobPackCommon", "score": 98.83234, "insns": [668, 668], "diffs": 141, "drops": []}

Source-order modeling setup: map each surviving before-color PCode instruction address into backend-04, align the real source disassembly against target, and infer desired colors for its virtual operands. On Unpack case-counts this aligns 512/517 instructions; the only conflicting requirements are the already-known reversed hex index/source increments (use the majority mapping and inspect these separately). `build/rx1b/color_targets.py` and `optimize_order.py` only propose reordered real scalar declarations; compiler output remains the authority.

F-round branch reuse check: inspected owned-path commits on agent/w1004/s1..s8 with git log/show (no checkout). Only s2 `5b5c3850` and s4 `a904d889` have relevant later commits. s2 swaps AES substitution/roundConstant declarations; the stronger scratch already uses the proven direct 128-bit substitution-table reference. s4 changes Split load order, superseded by the exact Split in #1185. No additional unapplied source family found.

- aes-pair-copy-0: ATERMAesExpandEncryptKey. Copy real fully assembled 64-bit key halves into the 32-bit output with memcpy, preserving alignment safety and all reads before writes. Test whether the copy boundary schedules natural output order without changing the word-result coloring. {"label": "aes-pair-copy-0", "function": "ATERMAesExpandEncryptKey", "score": 85.847015, "insns": [278, 268], "diffs": 265, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 85.847015]]}

- aes-pair-copy-1: ATERMAesExpandEncryptKey. Copy real fully assembled 64-bit key halves into the 32-bit output with memcpy, preserving alignment safety and all reads before writes. Test whether the copy boundary schedules natural output order without changing the word-result coloring. {"label": "aes-pair-copy-1", "function": "ATERMAesExpandEncryptKey", "score": 85.156715, "insns": [279, 268], "diffs": 265, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 85.156715]]}

- aes-pair-copy-2: ATERMAesExpandEncryptKey. Copy real fully assembled 64-bit key halves into the 32-bit output with memcpy, preserving alignment safety and all reads before writes. Test whether the copy boundary schedules natural output order without changing the word-result coloring. {"label": "aes-pair-copy-2", "function": "ATERMAesExpandEncryptKey", "score": 85.07836, "insns": [275, 268], "diffs": 263, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 85.07836]]}

- aes-pair-copy-3: ATERMAesExpandEncryptKey. Copy real fully assembled 64-bit key halves into the 32-bit output with memcpy, preserving alignment safety and all reads before writes. Test whether the copy boundary schedules natural output order without changing the word-result coloring. {"label": "aes-pair-copy-3", "function": "ATERMAesExpandEncryptKey", "score": 82.716415, "insns": [274, 268], "diffs": 263, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 82.716415]]}

Allocator confirmation step-base: capture `build/rx1b/mwdbg-step-base`, whole-object equality with normal compiler True.

Step baseline confirmation: full normal object equals `build/rx1b/mwdbg-step-base/unit.o`; 636 CR, 1211 FPR and 2356 final-pass GPR rewrites, zero mismatches. GPR pass1 performs 13 coalesces and spills leftTypeByte v68 plus 27 anonymous/rematerialized nodes; v68 has degree57, removal degree30, colors 19th after rightTypeByte v67 (removal29, rank18), and finds no color. Pass2 retains vm v32 r15/rank17, stepCount v33 r16/rank16, resultTypes v85 r27/rank5, stackPtr v87 r28/rank4; rightTypeByte gets r14/rank18 and leftTypeByte is a stack value. Target keeps the two type bytes in r14/r27, with a single shared-data base r28. The extra long-lived resultTypes base is part of the pressure divergence. This is in addition to the independently observed zero-count guard, loop test, and table-index addressing differences.

The queued Step candidate will use the graph-only mwdbg driver: the full baseline has now recorded both allocation passes and the coalescing/spill reasons. The candidate snapshot still records before-simplify graphs, actual priorities, final colors, all backend stages, rewrite validation and full-object equality. It does not claim chronological coalescing events; this avoids repeating thousands of costly per-event debugger stops on a non-exact structural trial.

- pack-flat-values-0: VmBlobPackCommon. Give each sizing/output case its own named scalar and declare those real values at function scope. Preserve case initialization and accesses. This keeps separate lifetimes while making source declaration order available to the allocator model. {"label": "pack-flat-values-0", "function": "VmBlobPackCommon", "score": 98.39072, "insns": [668, 668], "diffs": 190, "drops": []}

- pack-flat-values-1: VmBlobPackCommon. Give each sizing/output case its own named scalar and declare those real values at function scope. Preserve case initialization and accesses. This keeps separate lifetimes while making source declaration order available to the allocator model. {"label": "pack-flat-values-1", "function": "VmBlobPackCommon", "score": 97.76946, "insns": [668, 668], "diffs": 267, "drops": [["VmBlobPackCommon", 98.0988, 97.76946]]}

Debugger queue optimization: future non-exact candidate captures use graph-only mode; captures already running keep their original driver. Full baseline traces and the completed AES/Unpack candidate traces retain chronological allocation evidence. Graph-only captures provide actual pre-simplify/final representative maps, priorities, colors and rewrite validation, but no event-order or coalescing-attempt claims. Any exact candidate will receive a full trace through the `-exact` capture label before retention. All launches retain the shared lock and pinned compiler; every successful object is compared in full to the normal compiler output.

- unpack-integer-words-0: VmBlobUnpack. Target places the decoded integer high/low words in r18/r19, opposite the current 64-bit scalar pair. Test unsigned storage and two real scalar words reconstructed for SetInteger, preserving sign extension, endian conversion and the exact bit pattern. {"label": "unpack-integer-words-0", "function": "VmBlobUnpack", "score": 99.2263, "insns": [517, 517], "diffs": 71, "drops": []}

- unpack-integer-words-1: VmBlobUnpack. Target places the decoded integer high/low words in r18/r19, opposite the current 64-bit scalar pair. Test unsigned storage and two real scalar words reconstructed for SetInteger, preserving sign extension, endian conversion and the exact bit pattern. {"label": "unpack-integer-words-1", "function": "VmBlobUnpack", "score": 99.2263, "insns": [517, 517], "diffs": 71, "drops": []}

- unpack-integer-words-2: VmBlobUnpack. Target places the decoded integer high/low words in r18/r19, opposite the current 64-bit scalar pair. Test unsigned storage and two real scalar words reconstructed for SetInteger, preserving sign extension, endian conversion and the exact bit pattern. {"label": "unpack-integer-words-2", "function": "VmBlobUnpack", "score": 99.4294, "insns": [517, 517], "diffs": 54, "drops": []}

Unpack integer-value hypothesis confirmed by ordinary compilation: `unpack-integer-words-2` represents the actual decoded 64-bit integer as valueLow/valueHigh, uses arithmetic sign extension for signed inputs and zero high words for unsigned inputs, then reconstructs the same bits at CHANSVmSetInteger. Declaring low before high gives target r18/r19 and removes 17 differences (71 to54), with identical 517 instructions and no unit drops. The model can treat these real high/low words independently; it is still only a proposal until compiled and traced. No scalar is a dummy or register carrier.

- unpack-local-order-0: VmBlobUnpack. The target/source mapping shows a blob count/data r18/r19 swap and a three-value string count/object/data cycle. Test the corresponding declaration-order changes on independent real per-format scalars, retaining the already-correct integer word pair. {"label": "unpack-local-order-0", "function": "VmBlobUnpack", "score": 99.53578, "insns": [517, 517], "diffs": 43, "drops": []}

- unpack-local-order-1: VmBlobUnpack. The target/source mapping shows a blob count/data r18/r19 swap and a three-value string count/object/data cycle. Test the corresponding declaration-order changes on independent real per-format scalars, retaining the already-correct integer word pair. {"label": "unpack-local-order-1", "function": "VmBlobUnpack", "score": 99.57447, "insns": [517, 517], "diffs": 39, "drops": []}

- unpack-local-order-2: VmBlobUnpack. The target/source mapping shows a blob count/data r18/r19 swap and a three-value string count/object/data cycle. Test the corresponding declaration-order changes on independent real per-format scalars, retaining the already-correct integer word pair. {"label": "unpack-local-order-2", "function": "VmBlobUnpack", "score": 99.53578, "insns": [517, 517], "diffs": 43, "drops": []}

Allocator confirmation pack-valid-case-counts: capture `build/rx1b/mwdbg-pack-valid-case-counts`, whole-object equality with normal compiler True.

Allocator confirmation float-type-after-zero: capture `build/rx1b/mwdbg-float-type-after-zero`, whole-object equality with normal compiler True.

Allocator confirmation unpack-flat-values-1: capture `build/rx1b/mwdbg-unpack-flat-values-1-graphs`, whole-object equality with normal compiler True.

- unpack-flat-values-1-modeled-9: VmBlobUnpack. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "unpack-flat-values-1-modeled-9", "function": "VmBlobUnpack", "score": 99.01354, "insns": [517, 517], "diffs": 85, "drops": []}

- unpack-flat-values-1-modeled-8: VmBlobUnpack. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "unpack-flat-values-1-modeled-8", "function": "VmBlobUnpack", "score": 99.11025, "insns": [517, 517], "diffs": 79, "drops": []}

- unpack-flat-values-1-modeled-6: VmBlobUnpack. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "unpack-flat-values-1-modeled-6", "function": "VmBlobUnpack", "score": 99.65184, "insns": [517, 517], "diffs": 32, "drops": []}

- unpack-flat-values-1-modeled-4: VmBlobUnpack. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "unpack-flat-values-1-modeled-4", "function": "VmBlobUnpack", "score": 99.47775, "insns": [517, 517], "diffs": 52, "drops": []}

- unpack-flat-values-1-modeled-2: VmBlobUnpack. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "unpack-flat-values-1-modeled-2", "function": "VmBlobUnpack", "score": 98.742744, "insns": [517, 517], "diffs": 111, "drops": []}

- unpack-flat-values-1-modeled-0: VmBlobUnpack. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "unpack-flat-values-1-modeled-0", "function": "VmBlobUnpack", "score": 99.96132, "insns": [517, 517], "diffs": 2, "drops": []}

- unpack-string-lifetime-0: VmBlobUnpack. mwdbg shows output stringData has degree29 and colors only twentieth, after the long-lived core; its desired r26 is taken earlier by iterator/hex source values. Reuse the actual string-data pointer through input conversion and output scanning, or consume the source address directly, to test the resulting SSA split without changing types, reads or calls. {"label": "unpack-string-lifetime-0", "function": "VmBlobUnpack", "score": 99.642166, "insns": [517, 517], "diffs": 32, "drops": []}

- unpack-string-lifetime-1: VmBlobUnpack. mwdbg shows output stringData has degree29 and colors only twentieth, after the long-lived core; its desired r26 is taken earlier by iterator/hex source values. Reuse the actual string-data pointer through input conversion and output scanning, or consume the source address directly, to test the resulting SSA split without changing types, reads or calls. {"label": "unpack-string-lifetime-1", "function": "VmBlobUnpack", "score": 99.642166, "insns": [517, 517], "diffs": 32, "drops": []}

- unpack-string-lifetime-2: VmBlobUnpack. mwdbg shows output stringData has degree29 and colors only twentieth, after the long-lived core; its desired r26 is taken earlier by iterator/hex source values. Reuse the actual string-data pointer through input conversion and output scanning, or consume the source address directly, to test the resulting SSA split without changing types, reads or calls. {"label": "unpack-string-lifetime-2", "function": "VmBlobUnpack", "score": 97.97872, "insns": [518, 517], "diffs": 188, "drops": [["VmBlobUnpack", 98.452614, 97.97872]]}

- unpack-loop-increments-0: VmBlobUnpack. The graph-model proposal compiles with every target register and 515/517 exact instructions. Only independent hexSource and hexIndex increments are exchanged. Place those real loop updates at equivalent sequencing points; preserve the single input byte load, two output characters and odd-nibble tail. {"label": "unpack-loop-increments-0", "function": "VmBlobUnpack", "score": 100.0, "insns": [517, 517], "diffs": 0, "drops": []}

- unpack-loop-increments-1: VmBlobUnpack. The graph-model proposal compiles with every target register and 515/517 exact instructions. Only independent hexSource and hexIndex increments are exchanged. Place those real loop updates at equivalent sequencing points; preserve the single input byte load, two output characters and odd-nibble tail. {"label": "unpack-loop-increments-1", "function": "VmBlobUnpack", "score": 99.96132, "insns": [517, 517], "diffs": 2, "drops": []}

- unpack-loop-increments-2: VmBlobUnpack. The graph-model proposal compiles with every target register and 515/517 exact instructions. Only independent hexSource and hexIndex increments are exchanged. Place those real loop updates at equivalent sequencing points; preserve the single input byte load, two output characters and odd-nibble tail. {"label": "unpack-loop-increments-2", "function": "VmBlobUnpack", "score": 99.96132, "insns": [517, 517], "diffs": 2, "drops": []}

- unpack-loop-increments-3: VmBlobUnpack. The graph-model proposal compiles with every target register and 515/517 exact instructions. Only independent hexSource and hexIndex increments are exchanged. Place those real loop updates at equivalent sequencing points; preserve the single input byte load, two output characters and odd-nibble tail. {"label": "unpack-loop-increments-3", "function": "VmBlobUnpack", "score": 100.0, "insns": [517, 517], "diffs": 0, "drops": []}

- unpack-loop-increments-4: VmBlobUnpack. The graph-model proposal compiles with every target register and 515/517 exact instructions. Only independent hexSource and hexIndex increments are exchanged. Place those real loop updates at equivalent sequencing points; preserve the single input byte load, two output characters and odd-nibble tail. {"label": "unpack-loop-increments-4", "function": "VmBlobUnpack", "score": 99.96132, "insns": [517, 517], "diffs": 2, "drops": []}

- unpack-loop-increments-5: VmBlobUnpack. The graph-model proposal compiles with every target register and 515/517 exact instructions. Only independent hexSource and hexIndex increments are exchanged. Place those real loop updates at equivalent sequencing points; preserve the single input byte load, two output characters and odd-nibble tail. {"label": "unpack-loop-increments-5", "function": "VmBlobUnpack", "score": 99.96132, "insns": [517, 517], "diffs": 2, "drops": []}

- unpack-loop-increments-6: VmBlobUnpack. The graph-model proposal compiles with every target register and 515/517 exact instructions. Only independent hexSource and hexIndex increments are exchanged. Place those real loop updates at equivalent sequencing points; preserve the single input byte load, two output characters and odd-nibble tail. {"label": "unpack-loop-increments-6", "function": "VmBlobUnpack", "score": 99.96132, "insns": [517, 517], "diffs": 2, "drops": []}

Allocator confirmation pack-case-local-values-1: capture `build/rx1b/mwdbg-pack-case-local-values-1-graphs`, whole-object equality with normal compiler True.

- pack-case-local-values-1-modeled-14: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-case-local-values-1-modeled-14", "function": "VmBlobPackCommon", "score": 99.094315, "insns": [668, 668], "diffs": 107, "drops": []}

- pack-case-local-values-1-modeled-12: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-case-local-values-1-modeled-12", "function": "VmBlobPackCommon", "score": 99.32635, "insns": [668, 668], "diffs": 85, "drops": []}

- pack-case-local-values-1-modeled-11: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-case-local-values-1-modeled-11", "function": "VmBlobPackCommon", "score": 99.24401, "insns": [668, 668], "diffs": 91, "drops": []}

- pack-case-local-values-1-modeled-10: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-case-local-values-1-modeled-10", "function": "VmBlobPackCommon", "score": 99.3488, "insns": [668, 668], "diffs": 82, "drops": []}

- unpack-matched: VmBlobUnpack. Exact candidate: independent scalar declarations follow the modeled graph ordering, signed/unsigned decoded values use explicit high/low words, and the hex loop advances source before index in its iteration expression. Collapse experimental blank lines only. No changed calls, accessed bytes, literal order, or carrier aggregate. {"label": "unpack-matched", "function": "VmBlobUnpack", "score": 100.0, "insns": [517, 517], "diffs": 0, "drops": []}

Unpack exact candidate retained in the real source after source review and a fresh normal build: objdiff 98.452614 ->100.0, ctxdiff 517/517 with 0 differences, pool125/125 identical, no other function score changes. Unit exact count226 ->227/233. The full chronological mwdbg capture is queued as `mwdbg-unpack-matched-exact`; final gate waits for it and all searches. The candidate is ordinary scalar source: four distinct per-format counts, separate parse positions, actual high/low integer words, and equivalent hex-loop updates. The pointer-recomputation trial `unpack-string-lifetime-2` is rejected: it moved a blob-field read across calls and added an instruction. Neither string-pointer lifetime variant is retained.

Allocator confirmation pack-flat-values-0: capture `build/rx1b/mwdbg-pack-flat-values-0-graphs`, whole-object equality with normal compiler True.

- pack-flat-values-0-modeled-25: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-flat-values-0-modeled-25", "function": "VmBlobPackCommon", "score": 98.60779, "insns": [668, 668], "diffs": 168, "drops": []}

- pack-flat-values-0-modeled-23: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-flat-values-0-modeled-23", "function": "VmBlobPackCommon", "score": 98.76497, "insns": [668, 668], "diffs": 153, "drops": []}

- pack-flat-values-0-modeled-22: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-flat-values-0-modeled-22", "function": "VmBlobPackCommon", "score": 98.81737, "insns": [668, 668], "diffs": 147, "drops": []}

- pack-flat-values-0-modeled-14: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-flat-values-0-modeled-14", "function": "VmBlobPackCommon", "score": 99.094315, "insns": [668, 668], "diffs": 105, "drops": []}

- pack-flat-values-0-modeled-13: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-flat-values-0-modeled-13", "function": "VmBlobPackCommon", "score": 99.22156, "insns": [668, 668], "diffs": 92, "drops": []}

- pack-flat-values-0-modeled-12: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-flat-values-0-modeled-12", "function": "VmBlobPackCommon", "score": 99.32635, "insns": [668, 668], "diffs": 83, "drops": []}

- pack-flat-values-0-modeled-11: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-flat-values-0-modeled-11", "function": "VmBlobPackCommon", "score": 99.146706, "insns": [668, 668], "diffs": 109, "drops": []}

- pack-flat-values-0-modeled-10: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-flat-values-0-modeled-10", "function": "VmBlobPackCommon", "score": 99.303894, "insns": [668, 668], "diffs": 83, "drops": []}

- pack-flat-values-0-modeled-9: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-flat-values-0-modeled-9", "function": "VmBlobPackCommon", "score": 99.393715, "insns": [668, 668], "diffs": 74, "drops": []}

- pack-flat-values-0-modeled-8: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-flat-values-0-modeled-8", "function": "VmBlobPackCommon", "score": 99.43114, "insns": [668, 668], "diffs": 71, "drops": []}

- aes-half-store-helper-0: ATERMAesExpandEncryptKey. The previous round exhausted four-u32 store helpers. Test the new real 64-bit key halves through a two-half store boundary with natural output order. Input evaluation remains complete before stores; no alignment casts, volatile or carrier structs. {"label": "aes-half-store-helper-0", "function": "ATERMAesExpandEncryptKey", "score": 98.910446, "insns": [268, 268], "diffs": 9, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.910446]]}

- aes-half-store-helper-1: ATERMAesExpandEncryptKey. The previous round exhausted four-u32 store helpers. Test the new real 64-bit key halves through a two-half store boundary with natural output order. Input evaluation remains complete before stores; no alignment casts, volatile or carrier structs. {"label": "aes-half-store-helper-1", "function": "ATERMAesExpandEncryptKey", "score": 98.910446, "insns": [268, 268], "diffs": 9, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.910446]]}

- aes-half-store-helper-2: ATERMAesExpandEncryptKey. The previous round exhausted four-u32 store helpers. Test the new real 64-bit key halves through a two-half store boundary with natural output order. Input evaluation remains complete before stores; no alignment casts, volatile or carrier structs. {"label": "aes-half-store-helper-2", "function": "ATERMAesExpandEncryptKey", "score": 98.910446, "insns": [268, 268], "diffs": 9, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.910446]]}

- pack-pass-values-0: VmBlobPackCommon. Pack graph leaves eight wrong colors. The writing-pass argCount/fmtPos are anonymous SSA nodes v85/v84 (degree98), coloring eleventh/twelfth before persistent pointers and case byte counts. Give those real writing-pass state values their own scalar declarations, as the Unpack capture showed effective for its second parser position. {"label": "pack-pass-values-0", "function": "VmBlobPackCommon", "score": 98.80988, "insns": [668, 668], "diffs": 150, "drops": []}

- pack-pass-values-1: VmBlobPackCommon. Pack graph leaves eight wrong colors. The writing-pass argCount/fmtPos are anonymous SSA nodes v85/v84 (degree98), coloring eleventh/twelfth before persistent pointers and case byte counts. Give those real writing-pass state values their own scalar declarations, as the Unpack capture showed effective for its second parser position. {"label": "pack-pass-values-1", "function": "VmBlobPackCommon", "score": 98.91467, "insns": [668, 668], "diffs": 130, "drops": []}

- pack-pass-values-2: VmBlobPackCommon. Pack graph leaves eight wrong colors. The writing-pass argCount/fmtPos are anonymous SSA nodes v85/v84 (degree98), coloring eleventh/twelfth before persistent pointers and case byte counts. Give those real writing-pass state values their own scalar declarations, as the Unpack capture showed effective for its second parser position. {"label": "pack-pass-values-2", "function": "VmBlobPackCommon", "score": 98.1512, "insns": [668, 668], "diffs": 223, "drops": []}

- pack-pass-values-2-modeled-25: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-pass-values-2-modeled-25", "function": "VmBlobPackCommon", "score": 98.211075, "insns": [668, 668], "diffs": 217, "drops": []}

- pack-pass-values-2-modeled-24: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-pass-values-2-modeled-24", "function": "VmBlobPackCommon", "score": 98.30838, "insns": [668, 668], "diffs": 208, "drops": []}

- pack-pass-values-2-modeled-23: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-pass-values-2-modeled-23", "function": "VmBlobPackCommon", "score": 98.39072, "insns": [668, 668], "diffs": 199, "drops": []}

- pack-pass-values-2-modeled-14: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-pass-values-2-modeled-14", "function": "VmBlobPackCommon", "score": 99.08683, "insns": [668, 668], "diffs": 106, "drops": []}

- pack-pass-values-2-modeled-13: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-pass-values-2-modeled-13", "function": "VmBlobPackCommon", "score": 99.11677, "insns": [668, 668], "diffs": 104, "drops": []}

- pack-pass-values-2-modeled-12: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-pass-values-2-modeled-12", "function": "VmBlobPackCommon", "score": 99.07934, "insns": [668, 668], "diffs": 107, "drops": []}

- pack-pass-values-2-modeled-11: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-pass-values-2-modeled-11", "function": "VmBlobPackCommon", "score": 99.288925, "insns": [668, 668], "diffs": 86, "drops": []}

- pack-pass-values-2-modeled-10: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-pass-values-2-modeled-10", "function": "VmBlobPackCommon", "score": 99.41617, "insns": [668, 668], "diffs": 73, "drops": []}

- pack-pass-values-2-modeled-9: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-pass-values-2-modeled-9", "function": "VmBlobPackCommon", "score": 99.43862, "insns": [668, 668], "diffs": 70, "drops": []}

- pack-pass-values-2-modeled-7: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-pass-values-2-modeled-7", "function": "VmBlobPackCommon", "score": 99.483536, "insns": [668, 668], "diffs": 64, "drops": []}

- pack-pass-values-2-modeled-6: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-pass-values-2-modeled-6", "function": "VmBlobPackCommon", "score": 99.51347, "insns": [668, 668], "diffs": 60, "drops": []}

- pack-pass-values-2-modeled-5: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-pass-values-2-modeled-5", "function": "VmBlobPackCommon", "score": 99.53593, "insns": [668, 668], "diffs": 54, "drops": []}

- pack-pass-values-2-modeled-4: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-pass-values-2-modeled-4", "function": "VmBlobPackCommon", "score": 99.565865, "insns": [668, 668], "diffs": 50, "drops": []}

- pack-pass-values-2-modeled-3: VmBlobPackCommon. Use the validated mwdbg graph to reorder real scalar declarations by the exact simplify/color algorithm. Model is a source-proposal tool only; this result is measured with the untouched compiler. {"label": "pack-pass-values-2-modeled-3", "function": "VmBlobPackCommon", "score": 99.588326, "insns": [668, 668], "diffs": 47, "drops": []}

Pack model extension: the flat graph identifies writing-pass position and argument count as anonymous v84/v85 with degree98. Separating them as writeFmtPos/writeArgCount gives named source-order control without changing execution. The diagnostic prediction treats those nodes as declarations and shifts the intervening anonymous-node ordering; it is an explicit hypothesis until a fresh dump validates the new graph. Compiled proposals reach 47 differences at model cost3. No partial Pack source is retained.

- pack-converted-argument-0: VmBlobPackCommon. All remaining differences are array argument r23 versus target r18 and the two argument counters r18 versus target r23. Both converted format-header and array-header values use target r18 in non-overlapping phases. Represent the actual current converted argument by one correctly typed argObject pointer, without casts or changing evaluation/call order. {"label": "pack-converted-argument-0", "function": "VmBlobPackCommon", "score": 99.24401, "insns": [668, 668], "diffs": 87, "drops": []}

- pack-converted-argument-1: VmBlobPackCommon. All remaining differences are array argument r23 versus target r18 and the two argument counters r18 versus target r23. Both converted format-header and array-header values use target r18 in non-overlapping phases. Represent the actual current converted argument by one correctly typed argObject pointer, without casts or changing evaluation/call order. {"label": "pack-converted-argument-1", "function": "VmBlobPackCommon", "score": 99.24401, "insns": [668, 668], "diffs": 87, "drops": []}

Allocator confirmation step-postdecrement-test-3: capture `build/rx1b/mwdbg-step-postdecrement-test-3`, whole-object equality with normal compiler True.

Allocator confirmation date-names-as-parameters: capture `build/rx1b/mwdbg-date-names-as-parameters`, whole-object equality with normal compiler True.

- pack-argument-helper-0: VmBlobPackCommon. At the three-color plateau, factor the two repeated array-or-positional argument lookup into one scalar inline helper. Its returned object and parameter values are the actual operation inputs/outputs. Preserve all per-arm conversion calls and test whether this meaningful boundary changes array/count coalescing or degree. {"label": "pack-argument-helper-0", "function": "VmBlobPackCommon", "score": 97.13323, "insns": [652, 668], "diffs": 564, "drops": [["VmBlobPackCommon", 98.0988, 97.13323]]}

- pack-argument-helper-1: VmBlobPackCommon. At the three-color plateau, factor the two repeated array-or-positional argument lookup into one scalar inline helper. Its returned object and parameter values are the actual operation inputs/outputs. Preserve all per-arm conversion calls and test whether this meaningful boundary changes array/count coalescing or degree. {"label": "pack-argument-helper-1", "function": "VmBlobPackCommon", "score": 97.16317, "insns": [652, 668], "diffs": 564, "drops": [["VmBlobPackCommon", 98.0988, 97.16317]]}

- pack-argument-helper-2: VmBlobPackCommon. At the three-color plateau, factor the two repeated array-or-positional argument lookup into one scalar inline helper. Its returned object and parameter values are the actual operation inputs/outputs. Preserve all per-arm conversion calls and test whether this meaningful boundary changes array/count coalescing or degree. {"label": "pack-argument-helper-2", "function": "VmBlobPackCommon", "score": 97.13323, "insns": [652, 668], "diffs": 564, "drops": [["VmBlobPackCommon", 98.0988, 97.13323]]}

- pack-current-object-0: VmBlobPackCommon. Test one correctly typed current VM object local through receiver lookup and actual argument conversion phases. It is initialized from the receiver and consumed before reassignment; no parameter is repurposed, no cast changes object kind, and every original call and side effect remains in order. This follows lever21 plain variable reuse. {"label": "pack-current-object-0", "function": "VmBlobPackCommon", "score": 99.24401, "insns": [668, 668], "diffs": 87, "drops": []}

- pack-current-object-1: VmBlobPackCommon. Test one correctly typed current VM object local through receiver lookup and actual argument conversion phases. It is initialized from the receiver and consumed before reassignment; no parameter is repurposed, no cast changes object kind, and every original call and side effect remains in order. This follows lever21 plain variable reuse. {"label": "pack-current-object-1", "function": "VmBlobPackCommon", "score": 99.588326, "insns": [668, 668], "diffs": 47, "drops": []}

- pack-current-object-2: VmBlobPackCommon. Test one correctly typed current VM object local through receiver lookup and actual argument conversion phases. It is initialized from the receiver and consumed before reassignment; no parameter is repurposed, no cast changes object kind, and every original call and side effect remains in order. This follows lever21 plain variable reuse. {"label": "pack-current-object-2", "function": "VmBlobPackCommon", "score": 99.588326, "insns": [668, 668], "diffs": 47, "drops": []}

Allocator confirmation unpack-matched: capture `build/rx1b/mwdbg-unpack-matched-exact`, whole-object equality with normal compiler True.

## Unpack full allocator confirmation

`build/rx1b/mwdbg-unpack-matched-exact`: whole object equals normal compiler; [('cr', 1, {'register_operands_checked': 275, 'mismatches': 0}), ('gpr', 1, {'register_operands_checked': 944, 'mismatches': 0})]. No GPR spills.

(name, virtual, initial degree, simplify degree, color rank, physical):

```text
('VmInst', 32, 135, 13, 2, 30)
('VmReturnObj', 34, 135, 12, 1, 31)
('srcBlob', 66, 135, 20, 9, 25)
('fmtStr', 51, 135, 26, 15, 21)
('fmtLen', 44, 134, 28, 17, 20)
('argCount', 52, 43, 17, 14, 22)
('blobOff', 42, 43, 20, 18, 23)
('elemIdx', 64, 107, 19, 10, 24)
('iterIdx', 56, 37, 20, 12, 26)
('unpackPos', 57, 107, 20, 11, 23)
('blobCount', 43, 26, 25, 172, 18)
('blobData', 35, 23, 23, 177, 19)
('elementCount', 47, 38, 22, 16, 22)
('valueHigh', 40, 25, 24, 174, 18)
('valueLow', 39, 25, 25, 175, 19)
('charCount', 36, 39, 22, 20, 19)
('stringSource', 38, 25, 25, 176, 18)
('stringElement', 63, 32, 28, 164, 22)
('stringData', 54, 29, 28, 167, 26)
('digitCount', 37, 41, 24, 19, 19)
('hexByteCount', 69, 44, 17, 8, 26)
('hexSourceData', 53, 37, 21, 13, 22)
('hexIndex', 62, 25, 24, 165, 6)
```

The per-format counts and second parser position now have source-controlled virtual ordering, instead of appended SSA versions of shared locals. The reverse simplify stack introduces r26 for hexByteCount at rank8, r25 for srcBlob at rank9 and r24 for elemIdx at rank10; iterIdx reuses r26 at rank12, before the format/counter group r23/r22/r21/r20. Blob count/data share r18/r19 in the opposite order from baseline; the decoded integer words and string/hex values now get all target colors. Moving the hex source increment into the for update before the index preserves every loaded byte and the odd-digit tail, and fixes the last two scheduling differences. The existing unpack union remains the actual eight-byte input buffer; no carrier type was added.

Critical Unpack color events: `[{"event":"available-colors","virtual":69,"mask":"0x0"},{"event":"new-saved-register","virtual":69,"physical":26},{"event":"available-colors","virtual":69,"mask":"0x4000000"},{"event":"available-colors","virtual":66,"mask":"0x0"},{"event":"new-saved-register","virtual":66,"physical":25},{"event":"available-colors","virtual":66,"mask":"0x2000000"},{"event":"available-colors","virtual":64,"mask":"0x0"},{"event":"new-saved-register","virtual":64,"physical":24},{"event":"available-colors","virtual":64,"mask":"0x1000000"},{"event":"available-colors","virtual":56,"mask":"0x4000000"},{"event":"available-colors","virtual":54,"mask":"0x4000000"},{"event":"available-colors","virtual":43,"mask":"0x44c0000"},{"event":"available-colors","virtual":35,"mask":"0x4480000"}]`.

- pack-null-first-0: VmBlobPackCommon. With only the array/count saved-register exchange left, invert the optional-array selection in the sizing pass, writing pass, or both. Each pointer test and selected call sequence is unchanged; check whether CFG/value numbering changes the deferred interference core without altering emitted branch layout. {"label": "pack-null-first-0", "function": "VmBlobPackCommon", "score": 96.45958, "insns": [668, 668], "diffs": 74, "drops": [["VmBlobPackCommon", 98.0988, 96.45958]]}

- pack-null-first-1: VmBlobPackCommon. With only the array/count saved-register exchange left, invert the optional-array selection in the sizing pass, writing pass, or both. Each pointer test and selected call sequence is unchanged; check whether CFG/value numbering changes the deferred interference core without altering emitted branch layout. {"label": "pack-null-first-1", "function": "VmBlobPackCommon", "score": 95.72605, "insns": [668, 668], "diffs": 84, "drops": [["VmBlobPackCommon", 98.0988, 95.72605]]}

- pack-null-first-2: VmBlobPackCommon. With only the array/count saved-register exchange left, invert the optional-array selection in the sizing pass, writing pass, or both. Each pointer test and selected call sequence is unchanged; check whether CFG/value numbering changes the deferred interference core without altering emitted branch layout. {"label": "pack-null-first-2", "function": "VmBlobPackCommon", "score": 93.33084, "insns": [668, 668], "diffs": 111, "drops": [["VmBlobPackCommon", 98.0988, 93.33084]]}

Allocator confirmation pack-pass-values-2-modeled-3: capture `build/rx1b/mwdbg-pack-pass-values-2-modeled-3-graphs`, whole-object equality with normal compiler True.

Allocator confirmation hex-loop-helper-0: capture `build/rx1b/mwdbg-hex-loop-helper-0`, whole-object equality with normal compiler True.

- pack-object-parameter-0: VmBlobPackCommon. Check a typed VM-object parameter used first to read the receiver and then as the current converted argument object. Every value is a CHANSVmObjHdr pointer and the receiver data is cached before reassignment; there is no reinterpretation of a VM pointer or fabricated storage. This tests whether the early parameter virtual slot can explain the target array register. Review source quality independently of score. {"label": "pack-object-parameter-0", "function": "VmBlobPackCommon", "score": 98.52545, "insns": [668, 668], "diffs": 174, "drops": []}

- pack-object-parameter-1: VmBlobPackCommon. Check a typed VM-object parameter used first to read the receiver and then as the current converted argument object. Every value is a CHANSVmObjHdr pointer and the receiver data is cached before reassignment; there is no reinterpretation of a VM pointer or fabricated storage. This tests whether the early parameter virtual slot can explain the target array register. Review source quality independently of score. {"label": "pack-object-parameter-1", "function": "VmBlobPackCommon", "score": 99.24401, "insns": [668, 668], "diffs": 87, "drops": []}

Allocator confirmation assoc-direct-pointers: capture `build/rx1b/mwdbg-assoc-direct-pointers`, whole-object equality with normal compiler True.

Allocator confirmation nup-live-cursor-2: capture `build/rx1b/mwdbg-nup-live-cursor-2`, whole-object equality with normal compiler True.

- pack-conversion-input-0: VmBlobPackCommon. Split the real GetArg input from ConvertObjectType, either reusing its correctly typed header local or using one inputObject local for both conversions. Preserve evaluation order and every call. Check whether the array result keeps a named register rather than the current pressure-core position. {"label": "pack-conversion-input-0", "function": "VmBlobPackCommon", "score": 99.24401, "insns": [668, 668], "diffs": 87, "drops": []}

- pack-conversion-input-1: VmBlobPackCommon. Split the real GetArg input from ConvertObjectType, either reusing its correctly typed header local or using one inputObject local for both conversions. Preserve evaluation order and every call. Check whether the array result keeps a named register rather than the current pressure-core position. {"label": "pack-conversion-input-1", "function": "VmBlobPackCommon", "score": 99.24401, "insns": [668, 668], "diffs": 87, "drops": []}

- pack-conversion-input-2: VmBlobPackCommon. Split the real GetArg input from ConvertObjectType, either reusing its correctly typed header local or using one inputObject local for both conversions. Preserve evaluation order and every call. Check whether the array result keeps a named register rather than the current pressure-core position. {"label": "pack-conversion-input-2", "function": "VmBlobPackCommon", "score": 99.588326, "insns": [668, 668], "diffs": 47, "drops": []}

Allocator confirmation write-length-output-2: capture `build/rx1b/mwdbg-write-length-output-2`, whole-object equality with normal compiler True.

AES seed303 had not acquired a CPU slot (empty log, no output directory). Replaced that queued invocation with seed303 from the newer safe `aes-doubleword-loads-3` two-difference source. The original source was the earlier five-difference scalar-word variant. New label `aes-303-best`; full1200-second budget and the unchanged24-slot limiter remain. The cancelled queued invocation is not counted as a completed seed.

- write-print-object-0: VmWinEmuWrite. Old print helpers validated the header in the caller and retained the anonymous returned pointer. Move the entire genuine print-object operation, including null/type validation, into a typed scalar inline helper and pass the conversion result directly. Hypothesis: the real header parameter can color after length/offset, permitting r27 reuse with the dead VM without any pointer cast or parameter abuse. Preserve all calls, reloads and strings. {"label": "write-print-object-0", "function": "VmWinEmuWrite", "score": 99.10448, "insns": [67, 67], "diffs": 13, "drops": [["VmWinEmuWrite", 99.62687, 99.10448]]}

- write-print-object-1: VmWinEmuWrite. Old print helpers validated the header in the caller and retained the anonymous returned pointer. Move the entire genuine print-object operation, including null/type validation, into a typed scalar inline helper and pass the conversion result directly. Hypothesis: the real header parameter can color after length/offset, permitting r27 reuse with the dead VM without any pointer cast or parameter abuse. Preserve all calls, reloads and strings. {"label": "write-print-object-1", "function": "VmWinEmuWrite", "score": 99.55224, "insns": [67, 67], "diffs": 10, "drops": [["VmWinEmuWrite", 99.62687, 99.55224]]}

- write-print-object-2: VmWinEmuWrite. Old print helpers validated the header in the caller and retained the anonymous returned pointer. Move the entire genuine print-object operation, including null/type validation, into a typed scalar inline helper and pass the conversion result directly. Hypothesis: the real header parameter can color after length/offset, permitting r27 reuse with the dead VM without any pointer cast or parameter abuse. Preserve all calls, reloads and strings. {"label": "write-print-object-2", "function": "VmWinEmuWrite", "score": 99.17911, "insns": [67, 67], "diffs": 8, "drops": [["VmWinEmuWrite", 99.62687, 99.17911]]}

- write-print-object-3: VmWinEmuWrite. Old print helpers validated the header in the caller and retained the anonymous returned pointer. Move the entire genuine print-object operation, including null/type validation, into a typed scalar inline helper and pass the conversion result directly. Hypothesis: the real header parameter can color after length/offset, permitting r27 reuse with the dead VM without any pointer cast or parameter abuse. Preserve all calls, reloads and strings. {"label": "write-print-object-3", "function": "VmWinEmuWrite", "score": 99.62687, "insns": [67, 67], "diffs": 5, "drops": []}

Allocator confirmation write-print-object-3: capture `build/rx1b/mwdbg-write-print-object-3`, whole-object equality with normal compiler True.

## Final candidate snapshot evidence
These are actual mwdbg graph snapshots. Empty event arrays in the snapshot-only runs do not establish that coalescing was absent. Initial degree is after graph construction/coalescing, removal degree is at simplify, and rank is the recorded reverse simplify/coloring priority. Every captured object equals its ordinary-compiler trial object.

`hex-loop-helper-0`: 177 checked GPR rewrites, 0 mismatches.
| Value | Virtual | Initial degree | Removal degree | Color rank | Register |
|---|---:|---:|---:|---:|---:|
| high byte offset | 70 | 20 | 3 | 3 | r4 |
| char index | 40 | 20 | 3 | 33 | r8 |
| input | 45 | 18 | 3 | 28 | r6 |
| hex table | 42 | 20 | 3 | 31 | r7 |
| high byte | 56 | 10 | 2 | 17 | r5 |
| high digit | 59 | 9 | 2 | 14 | r5 |
| low digit | 65 | 9 | 2 | 8 | r5 |

`assoc-direct-pointers`: 272 checked GPR rewrites, 0 mismatches.
| Value | Virtual | Initial degree | Removal degree | Color rank | Register |
|---|---:|---:|---:|---:|---:|
| first input | 48 | 14 | 2 | 49 | r8 |
| second input | 41 | 14 | 2 | 56 | r8 |
| first output | 49 | 16 | 2 | 48 | r7 |
| first index | 43 | 14 | 2 | 54 | r9 |
| first low nibble | 68 | 11 | 2 | 29 | r5 |
| first high nibble | 66 | 9 | 2 | 31 | r6 |
| first output cursor | 46 | 11 | 2 | 51 | r6 |

`nup-live-cursor-2`: 1186 checked GPR rewrites, 0 mismatches.
| Value | Virtual | Initial degree | Removal degree | Color rank | Register |
|---|---:|---:|---:|---:|---:|
| opening literal | 129 | 22 | 12 | 107 | r24 |
| start match | 124 | 22 | 12 | 112 | r26 |
| closing literal | 128 | 23 | 12 | 108 | r25 |
| end match | 134 | 24 | 12 | 103 | r22 |

`date-names-as-parameters`: 149 checked GPR rewrites, 0 mismatches.
| Value | Virtual | Initial degree | Removal degree | Color rank | Register |
|---|---:|---:|---:|---:|---:|
| month base | 51 | 12 | 6 | 6 | r3 |
| month offset | 50 | 12 | 5 | 7 | r0 |
| day base | 49 | 13 | 5 | 8 | r4 |
| day offset | 48 | 12 | 4 | 9 | r5 |
| year | 37 | 13 | 4 | 17 | r6 |

`write-length-output-2`: 129 checked GPR rewrites, 0 mismatches.
| Value | Virtual | Initial degree | Removal degree | Color rank | Register |
|---|---:|---:|---:|---:|---:|
| converted header | 40 | 26 | 12 | 14 | r29 |
| length | 33 | 23 | 12 | 20 | r27 |
| offset | 36 | 25 | 12 | 18 | r28 |
| VM | 32 | 12 | 12 | 21 | r27 |
| capacity | 44 | 25 | 12 | 10 | r30 |
| zero | 51 | 25 | 12 | 3 | r31 |

Hex helper conclusion: the loop boundary changes virtual IDs but leaves the later digit expressions ahead of the named character cursor. They still take r5; the helper additionally exchanges table/cursor registers (r7/r8), explaining its 32 differences. No improvement is retained.

Association helper conclusion: replacing indexed input with incrementing input pointers moves those inputs to r8 instead of baseline r9, while output/index move to r7/r9. Low-nibble virtual68 still takes r5 before the input pointers can color. It does not produce target input r5 and low nibble r9, and it also regresses Discover; rejected.

NUP cursor conclusion: introducing real cursor lifetimes only renumbers the helper expansion. The start/end return copies have already propagated into anonymous match values before graph construction. End134 colors before opening129, closing128 and start124, preserving the wrong22/24/25/26 assignment. The old full chronological capture documents why physical-r3 return-copy coalescing is rejected for interference; there is no surviving named end-value copy to reorder here.

Date helper conclusion: the real month/day arguments preserve all target registers but preserve the seven scheduling differences. Month-base51 and day-base49 color as r3/r4, so declaration reordering is not the remaining issue. Backend01 has already placed the day-address/load before the month-address/load; the year value in r6 must be stored before the day result overwrites r6. Backend04 preserves that order.

Write length-output conclusion: changing the real length computation through an output parameter does not keep strObj37 live; it has no neighbors. The propagated header40 still colors at rank14, six places ahead of length33, giving r29/r27. VM32 has no header40 edge but also no header40 move candidate. Lack of interference alone is not a request to coalesce; the target swap needs different value ordering or a real copy relationship, not a cast of the VM parameter.

## Pack final plateau

`mwdbg-pack-pass-values-2-modeled-3-graphs` equals the complete ordinary object and validates 1448 GPR rewrites with 0 mismatches. Every one of its 47 differences is the remaining array/counter register exchange. Recorded values (virtual, initial degree, color rank, register): flag(35,129,1,r31), VM(32,129,2,r30), argArr(73,128,13,r23), writeFmtPos(70,98,14,r22), parentBlob(68,130,15,r21), fmtStr(60,129,16,r20), fmtLen(57,128,17,r19), writeArgCount(56,98,18,r18), argCount(48,47,23,r18). Target wants argArr r18 and both argument counters r23. The array interferes with both counters; the two counters have disjoint pass lifetimes and share r18.

The actual graph reproduces the no-spill allocation model. Distinct real pass counters and declaration order solve the other register choices. Sixteen 8000-proposal graph refinements cannot improve the remaining three wrong value colors. Their predictions are not counted as compiler trials. Null-first branches, typed object lifetime reuse, argument-conversion input locals, and real getter helpers were separately compiled and rejected for worse output or extra calls. The baseline full trace and changed graph snapshots show no spill-based explanation. The 47-difference source remains scratch, not accepted code.

Write whole-operation helper confirmation: `mwdbg-write-print-object-3` equals the normal object, 129 checked GPR rewrites and 0 mismatches. Even a typed inline helper parameter covering null/type validation and rendering is eliminated before allocation. Header v40 remains anonymous (degree26, removal12, rank14, r29); synthesized length v34 has degree23/rank19/r27, offset v35 degree25/rank18/r28; VM32 degree12/rank21/r27. The helper reproduces the five baseline differences, not the target swap. It is not retained.

## Coverage audit

Every requested function has at least three compiled source-level trials in this round. Counts include successful compiles with rejected output; baseline captures, compile errors, annealing iterations and model-only proposals are excluded. Counts at the audit:

- ATERMAesExpandEncryptKey: 28.
- ATERMBuildAssociationRequest: 11.
- CHANSVmConvertToFloatFromStr: 20.
- CHANSVmStep: 19.
- VmBlobGetHexString: 10.
- VmBlobPackCommon: 67.
- VmBlobUnpack: 45.
- VmDateDtor: 12.
- VmWinEmuWrite: 10.
- __nupParseServerInfo__FP14NUPContextInfoPcPcUx: 3.

The preliminary quick gate passed after the retained Unpack edit: CHANSVm instruction-exact 226/233 -> 227/233, matched code 42520 -> 44588 bytes, data 6904/6904 unchanged. nup and ATERM metrics are unchanged. All pools match, all-unit regressions are zero, and forbidden/readability additions are zero. DOL SHA1 remains `26116613f624061ba99c8d1a299aaa6efa85670d`. The required final clean gate remains pending until the private compiler jobs finish.

- pack-measure-helper-0: VmBlobPackCommon. Give the real sizing pass its own scalar inline helper with a boolean status and one size output. Preserve parser/call/literal order and the caller error path. The new parameter lifetimes may change the array/counter allocation; no aggregate carrier or dummy value is used. {"label": "pack-measure-helper-0", "function": "VmBlobPackCommon", "score": 97.112274, "insns": [674, 668], "diffs": 546, "drops": [["VmBlobPackCommon", 98.0988, 97.112274]]}

- pack-measure-helper-1: VmBlobPackCommon. Give the real sizing pass its own scalar inline helper with a boolean status and one size output. Preserve parser/call/literal order and the caller error path. The new parameter lifetimes may change the array/counter allocation; no aggregate carrier or dummy value is used. {"label": "pack-measure-helper-1", "function": "VmBlobPackCommon", "score": 97.112274, "insns": [674, 668], "diffs": 546, "drops": [["VmBlobPackCommon", 98.0988, 97.112274]]}

- pack-measure-helper-2: VmBlobPackCommon. Give the real sizing pass its own scalar inline helper with a boolean status and one size output. Preserve parser/call/literal order and the caller error path. The new parameter lifetimes may change the array/counter allocation; no aggregate carrier or dummy value is used. {"label": "pack-measure-helper-2", "function": "VmBlobPackCommon", "score": 97.112274, "insns": [674, 668], "diffs": 546, "drops": [["VmBlobPackCommon", 98.0988, 97.112274]]}

- aes-const-half-0: ATERMAesExpandEncryptKey. The safe two-half key reconstruction reads all 16 input bytes before any output store. Give one or both immutable halves declaration initializers and compare the observed 0/3/2/1 and natural 0/1/2/3 store orders. This tests binding propagation before scheduling without changing reads or adding dependencies. {"label": "aes-const-half-0", "function": "ATERMAesExpandEncryptKey", "score": 99.95522, "insns": [268, 268], "diffs": 2, "drops": []}

- aes-const-half-1: ATERMAesExpandEncryptKey. The safe two-half key reconstruction reads all 16 input bytes before any output store. Give one or both immutable halves declaration initializers and compare the observed 0/3/2/1 and natural 0/1/2/3 store orders. This tests binding propagation before scheduling without changing reads or adding dependencies. {"label": "aes-const-half-1", "function": "ATERMAesExpandEncryptKey", "error": "### mwcceppc.exe Compiler:\n#    File: build\\rx1b\\trials\\aes-const-half-1\\ATERM.c\n# ---------------------------------------------------\n#    1937:     const u64 secondHalf = ((u64)(((u32)keyBytes[11] ^ ((u32)keyBytes[10] << 8)) ^ (((u32)keyBytes[8] << 24) ^ ((u32)keyBytes[9\n#   Error:     ^^^^^\n#   (10141) expression syntax error\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\n"}

- aes-const-half-2: ATERMAesExpandEncryptKey. The safe two-half key reconstruction reads all 16 input bytes before any output store. Give one or both immutable halves declaration initializers and compare the observed 0/3/2/1 and natural 0/1/2/3 store orders. This tests binding propagation before scheduling without changing reads or adding dependencies. {"label": "aes-const-half-2", "function": "ATERMAesExpandEncryptKey", "score": 99.95522, "insns": [268, 268], "diffs": 2, "drops": []}

- aes-const-half-3: ATERMAesExpandEncryptKey. The safe two-half key reconstruction reads all 16 input bytes before any output store. Give one or both immutable halves declaration initializers and compare the observed 0/3/2/1 and natural 0/1/2/3 store orders. This tests binding propagation before scheduling without changing reads or adding dependencies. {"label": "aes-const-half-3", "function": "ATERMAesExpandEncryptKey", "score": 98.910446, "insns": [268, 268], "diffs": 9, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.910446]]}

- aes-const-half-4: ATERMAesExpandEncryptKey. The safe two-half key reconstruction reads all 16 input bytes before any output store. Give one or both immutable halves declaration initializers and compare the observed 0/3/2/1 and natural 0/1/2/3 store orders. This tests binding propagation before scheduling without changing reads or adding dependencies. {"label": "aes-const-half-4", "function": "ATERMAesExpandEncryptKey", "error": "### mwcceppc.exe Compiler:\n#    File: build\\rx1b\\trials\\aes-const-half-4\\ATERM.c\n# ---------------------------------------------------\n#    1937:     const u64 secondHalf = ((u64)(((u32)keyBytes[11] ^ ((u32)keyBytes[10] << 8)) ^ (((u32)keyBytes[8] << 24) ^ ((u32)keyBytes[9\n#   Error:     ^^^^^\n#   (10141) expression syntax error\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\n"}

- aes-const-half-5: ATERMAesExpandEncryptKey. The safe two-half key reconstruction reads all 16 input bytes before any output store. Give one or both immutable halves declaration initializers and compare the observed 0/3/2/1 and natural 0/1/2/3 store orders. This tests binding propagation before scheduling without changing reads or adding dependencies. {"label": "aes-const-half-5", "function": "ATERMAesExpandEncryptKey", "score": 98.910446, "insns": [268, 268], "diffs": 9, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.910446]]}

- aes-const-half-1-c89: ATERMAesExpandEncryptKey. Correct the second-only const binding to a C89 block after the first half has been read. Both real halves remain available for the initial stores, with the original input-before-output access order. The failed declaration-after-statement trials above do not count as compiled candidates. {"label": "aes-const-half-1-c89", "function": "ATERMAesExpandEncryptKey", "score": 99.95522, "insns": [268, 268], "diffs": 2, "drops": []}

- aes-const-half-4-c89: ATERMAesExpandEncryptKey. Correct the second-only const binding to a C89 block after the first half has been read. Both real halves remain available for the initial stores, with the original input-before-output access order. The failed declaration-after-statement trials above do not count as compiled candidates. {"label": "aes-const-half-4-c89", "function": "ATERMAesExpandEncryptKey", "score": 98.910446, "insns": [268, 268], "diffs": 9, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.910446]]}

- aes-halves-store-order-0132: ATERMAesExpandEncryptKey. The initial PCode for the two-half source can reorder stores and XORs even before backend04. Test the other store encounter orders for this new safe two-half family; every byte read precedes all four disjoint output stores. The earlier scalar-word permutations did not test this pair representation. {"label": "aes-halves-store-order-0132", "function": "ATERMAesExpandEncryptKey", "score": 98.86567, "insns": [268, 268], "diffs": 11, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.86567]]}

- aes-halves-store-order-0213: ATERMAesExpandEncryptKey. The initial PCode for the two-half source can reorder stores and XORs even before backend04. Test the other store encounter orders for this new safe two-half family; every byte read precedes all four disjoint output stores. The earlier scalar-word permutations did not test this pair representation. {"label": "aes-halves-store-order-0213", "function": "ATERMAesExpandEncryptKey", "score": 98.962685, "insns": [268, 268], "diffs": 9, "drops": []}

- aes-halves-store-order-0231: ATERMAesExpandEncryptKey. The initial PCode for the two-half source can reorder stores and XORs even before backend04. Test the other store encounter orders for this new safe two-half family; every byte read precedes all four disjoint output stores. The earlier scalar-word permutations did not test this pair representation. {"label": "aes-halves-store-order-0231", "function": "ATERMAesExpandEncryptKey", "score": 98.92164, "insns": [268, 268], "diffs": 10, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.92164]]}

- aes-halves-store-order-0312: ATERMAesExpandEncryptKey. The initial PCode for the two-half source can reorder stores and XORs even before backend04. Test the other store encounter orders for this new safe two-half family; every byte read precedes all four disjoint output stores. The earlier scalar-word permutations did not test this pair representation. {"label": "aes-halves-store-order-0312", "function": "ATERMAesExpandEncryptKey", "score": 99.93284, "insns": [268, 268], "diffs": 3, "drops": []}

- aes-halves-store-order-1023: ATERMAesExpandEncryptKey. The initial PCode for the two-half source can reorder stores and XORs even before backend04. Test the other store encounter orders for this new safe two-half family; every byte read precedes all four disjoint output stores. The earlier scalar-word permutations did not test this pair representation. {"label": "aes-halves-store-order-1023", "function": "ATERMAesExpandEncryptKey", "score": 98.910446, "insns": [268, 268], "diffs": 9, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.910446]]}

- aes-halves-store-order-1032: ATERMAesExpandEncryptKey. The initial PCode for the two-half source can reorder stores and XORs even before backend04. Test the other store encounter orders for this new safe two-half family; every byte read precedes all four disjoint output stores. The earlier scalar-word permutations did not test this pair representation. {"label": "aes-halves-store-order-1032", "function": "ATERMAesExpandEncryptKey", "score": 98.86567, "insns": [268, 268], "diffs": 11, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.86567]]}

- aes-halves-store-order-1203: ATERMAesExpandEncryptKey. The initial PCode for the two-half source can reorder stores and XORs even before backend04. Test the other store encounter orders for this new safe two-half family; every byte read precedes all four disjoint output stores. The earlier scalar-word permutations did not test this pair representation. {"label": "aes-halves-store-order-1203", "function": "ATERMAesExpandEncryptKey", "score": 98.94776, "insns": [268, 268], "diffs": 9, "drops": []}

- aes-halves-store-order-1230: ATERMAesExpandEncryptKey. The initial PCode for the two-half source can reorder stores and XORs even before backend04. Test the other store encounter orders for this new safe two-half family; every byte read precedes all four disjoint output stores. The earlier scalar-word permutations did not test this pair representation. {"label": "aes-halves-store-order-1230", "function": "ATERMAesExpandEncryptKey", "score": 98.92538, "insns": [268, 268], "diffs": 10, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.92538]]}

- aes-halves-store-order-1302: ATERMAesExpandEncryptKey. The initial PCode for the two-half source can reorder stores and XORs even before backend04. Test the other store encounter orders for this new safe two-half family; every byte read precedes all four disjoint output stores. The earlier scalar-word permutations did not test this pair representation. {"label": "aes-halves-store-order-1302", "function": "ATERMAesExpandEncryptKey", "score": 98.86567, "insns": [268, 268], "diffs": 11, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.86567]]}

- aes-halves-store-order-1320: ATERMAesExpandEncryptKey. The initial PCode for the two-half source can reorder stores and XORs even before backend04. Test the other store encounter orders for this new safe two-half family; every byte read precedes all four disjoint output stores. The earlier scalar-word permutations did not test this pair representation. {"label": "aes-halves-store-order-1320", "function": "ATERMAesExpandEncryptKey", "score": 98.88806, "insns": [268, 268], "diffs": 10, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.88806]]}

- aes-halves-store-order-2013: ATERMAesExpandEncryptKey. The initial PCode for the two-half source can reorder stores and XORs even before backend04. Test the other store encounter orders for this new safe two-half family; every byte read precedes all four disjoint output stores. The earlier scalar-word permutations did not test this pair representation. {"label": "aes-halves-store-order-2013", "function": "ATERMAesExpandEncryptKey", "score": 98.962685, "insns": [268, 268], "diffs": 9, "drops": []}

- aes-halves-store-order-2031: ATERMAesExpandEncryptKey. The initial PCode for the two-half source can reorder stores and XORs even before backend04. Test the other store encounter orders for this new safe two-half family; every byte read precedes all four disjoint output stores. The earlier scalar-word permutations did not test this pair representation. {"label": "aes-halves-store-order-2031", "function": "ATERMAesExpandEncryptKey", "score": 98.92164, "insns": [268, 268], "diffs": 10, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.92164]]}

- aes-halves-store-order-2103: ATERMAesExpandEncryptKey. The initial PCode for the two-half source can reorder stores and XORs even before backend04. Test the other store encounter orders for this new safe two-half family; every byte read precedes all four disjoint output stores. The earlier scalar-word permutations did not test this pair representation. {"label": "aes-halves-store-order-2103", "function": "ATERMAesExpandEncryptKey", "score": 98.94776, "insns": [268, 268], "diffs": 9, "drops": []}

- aes-halves-store-order-2130: ATERMAesExpandEncryptKey. The initial PCode for the two-half source can reorder stores and XORs even before backend04. Test the other store encounter orders for this new safe two-half family; every byte read precedes all four disjoint output stores. The earlier scalar-word permutations did not test this pair representation. {"label": "aes-halves-store-order-2130", "function": "ATERMAesExpandEncryptKey", "score": 98.92538, "insns": [268, 268], "diffs": 10, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.92538]]}

- aes-halves-store-order-2301: ATERMAesExpandEncryptKey. The initial PCode for the two-half source can reorder stores and XORs even before backend04. Test the other store encounter orders for this new safe two-half family; every byte read precedes all four disjoint output stores. The earlier scalar-word permutations did not test this pair representation. {"label": "aes-halves-store-order-2301", "function": "ATERMAesExpandEncryptKey", "score": 98.92164, "insns": [268, 268], "diffs": 10, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.92164]]}

- aes-halves-store-order-2310: ATERMAesExpandEncryptKey. The initial PCode for the two-half source can reorder stores and XORs even before backend04. Test the other store encounter orders for this new safe two-half family; every byte read precedes all four disjoint output stores. The earlier scalar-word permutations did not test this pair representation. {"label": "aes-halves-store-order-2310", "function": "ATERMAesExpandEncryptKey", "score": 98.92538, "insns": [268, 268], "diffs": 10, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.92538]]}

- aes-halves-store-order-3012: ATERMAesExpandEncryptKey. The initial PCode for the two-half source can reorder stores and XORs even before backend04. Test the other store encounter orders for this new safe two-half family; every byte read precedes all four disjoint output stores. The earlier scalar-word permutations did not test this pair representation. {"label": "aes-halves-store-order-3012", "function": "ATERMAesExpandEncryptKey", "score": 99.93284, "insns": [268, 268], "diffs": 3, "drops": []}

- aes-halves-store-order-3021: ATERMAesExpandEncryptKey. The initial PCode for the two-half source can reorder stores and XORs even before backend04. Test the other store encounter orders for this new safe two-half family; every byte read precedes all four disjoint output stores. The earlier scalar-word permutations did not test this pair representation. {"label": "aes-halves-store-order-3021", "function": "ATERMAesExpandEncryptKey", "score": 99.95522, "insns": [268, 268], "diffs": 2, "drops": []}

- aes-halves-store-order-3102: ATERMAesExpandEncryptKey. The initial PCode for the two-half source can reorder stores and XORs even before backend04. Test the other store encounter orders for this new safe two-half family; every byte read precedes all four disjoint output stores. The earlier scalar-word permutations did not test this pair representation. {"label": "aes-halves-store-order-3102", "function": "ATERMAesExpandEncryptKey", "score": 98.86567, "insns": [268, 268], "diffs": 11, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.86567]]}

- aes-halves-store-order-3120: ATERMAesExpandEncryptKey. The initial PCode for the two-half source can reorder stores and XORs even before backend04. Test the other store encounter orders for this new safe two-half family; every byte read precedes all four disjoint output stores. The earlier scalar-word permutations did not test this pair representation. {"label": "aes-halves-store-order-3120", "function": "ATERMAesExpandEncryptKey", "score": 98.88806, "insns": [268, 268], "diffs": 10, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.88806]]}

- aes-halves-store-order-3201: ATERMAesExpandEncryptKey. The initial PCode for the two-half source can reorder stores and XORs even before backend04. Test the other store encounter orders for this new safe two-half family; every byte read precedes all four disjoint output stores. The earlier scalar-word permutations did not test this pair representation. {"label": "aes-halves-store-order-3201", "function": "ATERMAesExpandEncryptKey", "score": 99.95522, "insns": [268, 268], "diffs": 2, "drops": []}

- aes-halves-store-order-3210: ATERMAesExpandEncryptKey. The initial PCode for the two-half source can reorder stores and XORs even before backend04. Test the other store encounter orders for this new safe two-half family; every byte read precedes all four disjoint output stores. The earlier scalar-word permutations did not test this pair representation. {"label": "aes-halves-store-order-3210", "function": "ATERMAesExpandEncryptKey", "score": 98.88806, "insns": [268, 268], "diffs": 10, "drops": [["ATERMAesExpandEncryptKey", 98.94403, 98.88806]]}

Pack targeted-model follow-up: the independently confirmed best graph has no desired-color interference collisions; therefore this is not evidence that the target colors are impossible. Twelve 10000-proposal searches temporarily weighted the array/counter constraints eight times higher before returning to the full color objective. They reached one wrong array/counter color while disturbing others, but never beat the original three total wrong colors. No new compiler candidate was generated. Three separately compiled sizing-pass helpers preserved semantics but produced 674 rather than 668 instructions and were rejected.

AES binding and store-order follow-up: const initialization of either or both real u64 halves leaves the same two store differences. The second-only declaration initially violated C89 declaration placement; corrected block-scoped trials compile and give the same result. Natural 0/1/2/3 stores produce nine differences because early PCode scheduling moves the word1 XOR/store ahead of word0 and changes its register to r6. All 24 store encounter orders for the safe two-half family were covered (two existing trials and 22 new ones); none is exact. The best remains 99.95522 with two store positions different and every register correct. This source is still scratch only.

AES annealing completed: seed301: 1199 trials and seed302: 1315 trials from the safe five-difference scalar-word start; replacement seed303: 1112 trials from the safe two-difference halves start. No search improved its starting state. Each received 1200 seconds after acquiring an unchanged shared CPU slot. Original queued aes303 was cancelled before acquiring a slot and does not count.

Unpack chronological coalesces (14): v60(fmtPos) -> r9; v89(@15633) -> v41(count); v87(@15637) -> v70(@15671); v85(@15641) -> v71(@15669); v83(@15645) -> v72(@15667); v81(@15649) -> v43(blobCount); v58(blobElement) -> r4; v80(@15651) -> r6; v79(@15653) -> v47(elementCount); v61(integerElement) -> r4; v77(@15657) -> v36(charCount); v73(@15665) -> v37(digitCount); v49(hexDestination) -> r3; v59(hexSource) -> v53(hexSourceData). These are recorded move coalesces, distinct from later reuse of the same physical register by disjoint values.

## Completed shared-slot searches

All 30 required seeds completed. Each had a 1200-second budget after slot acquisition, using the unchanged 24-slot limiter. No seed improved its starting state. Counts below are actual compiler/search iterations, not allocator-model proposals. Replacement pack seeds use the valid case-count source; AES seed303 uses the newer safe two-difference source. Cancelled invocations never acquired a slot and are excluded.

| Function family | Seed301 trials | Seed302 trials | Seed303 trials | Final search score |
|---|---:|---:|---:|---:|
| aes | 1199 | 1315 | 1112 | 99.8955 / 99.8955 / 99.9552 |
| hex | 824 | 789 | 817 | 98.7195 |
| assoc | 1244 | 1220 | 1230 | 98.7594 |
| nup | 1946 | 1894 | 1885 | 99.2699 |
| write | 959 | 1052 | 1124 | 99.6269 |
| float | 751 | 801 | 788 | 97.5904 |
| date | 769 | 774 | 829 | 94.967 |
| unpack | 812 | 925 | 808 | 98.9362 |
| pack | 890 | 834 | 832 | 98.1512 |
| step | 804 | 801 | 753 | 96.9872 |

Final manual compiled-candidate counts: ATERMAesExpandEncryptKey 56; ATERMBuildAssociationRequest 11; CHANSVmConvertToFloatFromStr 20; CHANSVmStep 19; VmBlobGetHexString 10; VmBlobPackCommon 70; VmBlobUnpack 45; VmDateDtor 12; VmWinEmuWrite 10; __nupParseServerInfo__FP14NUPContextInfoPcPcUx 3. Distinct source families and measurements are logged above.

## Final clean gate and handoff

Command: `python3 -u /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py src/channelScript/CHANSVm libs/RVL_SDK/src/nup/nup src/scene/setting/ATERM --base afabe7ca32b4d069af22630ca9181832d9cdb2bb`. No `--quick`; the gate rebuilt the complete 43U tree after all private compiler jobs finished. Exit 0. Raw output follows.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/channelScript/CHANSVm] pool: IDENTICAL
[src/channelScript/CHANSVm] objdiff: code 44588/53564 data 6904/6904 functions 227/233 fuzzy 99.5644 linked code 0
[src/channelScript/CHANSVm] instruction-exact functions: 227/233
[src/channelScript/CHANSVm]   section .data size 4672 match 100.0
[src/channelScript/CHANSVm]   section .rodata size 1432 match 100.0
[src/channelScript/CHANSVm]   section .sbss size 16 match 100.0
[src/channelScript/CHANSVm]   section .sdata size 600 match 100.0
[src/channelScript/CHANSVm]   section .sdata2 size 184 match 100.0
[src/channelScript/CHANSVm]   section .text size 53564 match 99.56441
[src/channelScript/CHANSVm]   below 100: CHANSVmConvertToFloatFromStr 97.59036
[src/channelScript/CHANSVm]   below 100: VmDateDtor 94.96703
[src/channelScript/CHANSVm]   below 100: VmBlobGetHexString 98.71951
[src/channelScript/CHANSVm]   below 100: VmBlobPackCommon 98.0988
[src/channelScript/CHANSVm]   below 100: VmWinEmuWrite 99.62687
[src/channelScript/CHANSVm]   below 100: CHANSVmStep 96.98723
[src/channelScript/CHANSVm] baseline: code 42520/53564 data 6904 functions 226 fuzzy 99.5047
[libs/RVL_SDK/src/nup/nup] pool: IDENTICAL
[libs/RVL_SDK/src/nup/nup] objdiff: code 8956/10764 data 1720/1720 functions 22/23 fuzzy 99.8774 linked code 0
[libs/RVL_SDK/src/nup/nup] instruction-exact functions: 22/23
[libs/RVL_SDK/src/nup/nup]   section .data size 1592 match 100.0
[libs/RVL_SDK/src/nup/nup]   section .rodata size 88 match 100.0
[libs/RVL_SDK/src/nup/nup]   section .sbss size 8 match 100.0
[libs/RVL_SDK/src/nup/nup]   section .sdata size 32 match 100.0
[libs/RVL_SDK/src/nup/nup]   section .text size 10764 match 99.87737
[libs/RVL_SDK/src/nup/nup]   below 100: __nupParseServerInfo__FP14NUPContextInfoPcPcUx 99.26991
[libs/RVL_SDK/src/nup/nup] baseline: code 8956/10764 data 1720 functions 22 fuzzy 99.8774
[src/scene/setting/ATERM] pool: IDENTICAL
[src/scene/setting/ATERM] objdiff: code 12200/19204 data 18864/18864 functions 20/26 fuzzy 98.2020 linked code 0
[src/scene/setting/ATERM] instruction-exact functions: 20/26
[src/scene/setting/ATERM]   section .bss size 8160 match 100.0
[src/scene/setting/ATERM]   section .data size 280 match 100.0
[src/scene/setting/ATERM]   section .rodata size 10280 match 100.0
[src/scene/setting/ATERM]   section .sbss size 80 match 100.0
[src/scene/setting/ATERM]   section .sdata size 56 match 100.0
[src/scene/setting/ATERM]   section .sdata2 size 8 match 100.0
[src/scene/setting/ATERM]   section .text size 19204 match 98.20204
[src/scene/setting/ATERM]   below 100: ATERMDiscoverAccessPoints 98.31939
[src/scene/setting/ATERM]   below 100: ATERMBuildEncryptedMessage 99.791664
[src/scene/setting/ATERM]   below 100: ATERMBuildAssociationRequest 98.7594
[src/scene/setting/ATERM]   below 100: ATERMRunConfigProtocol 92.100945
[src/scene/setting/ATERM]   below 100: ATERMi_AutoConfigThread 94.75
[src/scene/setting/ATERM]   below 100: ATERMAesExpandEncryptKey 98.94403
[src/scene/setting/ATERM] baseline: code 12200/19204 data 18864 functions 20 fuzzy 98.2020
regressions vs baseline: 0
global matched_code_percent: 92.97337 -> 93.04241
global fuzzy_match_percent: 99.78430 -> 99.78537
global complete_code_percent: 77.30203 -> 77.30203
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Fresh independent report `build/rx1b/final.json` changes exactly one function score, Unpack; no other whole-project function changes or drops. Direct fresh ctxdiff:

```text
src 0x814 base 0x814 insns 517/517
diffs 0: []
```

| Requested function | Baseline objdiff | Retained objdiff |
|---|---:|---:|
| VmBlobUnpack | 98.452614 | 100.0 |
| ATERMAesExpandEncryptKey | 98.94403 | 98.94403 |
| VmBlobGetHexString | 98.71951 | 98.71951 |
| ATERMBuildAssociationRequest | 98.7594 | 98.7594 |
| __nupParseServerInfo__FP14NUPContextInfoPcPcUx | 99.26991 | 99.26991 |
| VmWinEmuWrite | 99.62687 | 99.62687 |
| CHANSVmConvertToFloatFromStr | 97.59036 | 97.59036 |
| VmDateDtor | 94.96703 | 94.96703 |
| VmBlobPackCommon | 98.0988 | 98.0988 |
| CHANSVmStep | 96.98723 | 96.98723 |

Unit instruction-exact counts: CHANSVm 226/233 -> 227/233; nup 22/23 -> 22/23; ATERM 20/26 -> 20/26. Matched code: CHANSVm 42520 -> 44588 bytes, nup 8956 unchanged, ATERM 12200 unchanged. Data remains 6904/6904, 1720/1720, 18864/18864 respectively. Pools are identical and DOL SHA1 is `26116613f624061ba99c8d1a299aaa6efa85670d`.

Tracked source scope is only `src/channelScript/CHANSVm.c`, within VmBlobUnpack. All other source candidates remain in ignored `build/rx1b/trials/`. No carrier structs, new assembly, compiler-option changes, volatile casts, register keywords, or extra source comments were retained. No configure/linking change was made. No push, PR, merge, rebase, or other-worktree edit was performed.
