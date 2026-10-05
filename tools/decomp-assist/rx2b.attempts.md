# rx2b allocator follow-up

Start: agent/w1005/rx2b at bfbaf84f, already prepared from origin/main and verified clean after fetching origin. PR 1180 includes the previous SDI and exception conversions. This round owns only TVRCSendStartAsync, Manager::getTitleName, CDBFSIsCDBFileOnSD and System::warning_run. Prior experiments and captures in build/rx2 and rx2.attempts.md are the starting evidence; do not repeat them blindly.

Acceptance: readable C/C++, exact-name objdiff 100.0%, ctxdiff zero, identical pools and sections, full clean gate, DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. No assembly, carrier structs, artificial state, uninitialized reads, header/layout tricks or compiler flag changes. Each conversion gets its own local commit. No push, PR, merge, rebase or other-worktree edits.

Debugger: reuse the prior local port-9202 adapter and decoder without changes. All captures must be byte-identical to normal wibo with production flags. Fresh outputs live in build/rx2b. Ghidra exports use worktree-local project and output directories.

- warning-b00: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- title-b00: getTitleName__Q33ipl7channel7ManagerCFiii 99.366196%; insns 71/71, diffs 7; pool IDENTICAL 9/9

- tvrc-b00: TVRCSendStartAsync 99.747475%; insns 198/198, diffs 9; pool IDENTICAL 0/0

- cdb-b00: CDBFSIsCDBFileOnSD 99.09449%; insns 127/127, diffs 17; pool IDENTICAL 0/0

- cdb-b01-pair-0-indexed: COMPILE FAIL ### mwcceppc.exe Compiler:
#    File: build\rx2b\trials\cdb-b01-pair-0-indexed\CDBFileSystemUtils.c
# ----------------------------------------------------------------------
#     112:     for (int index = 0; index < 2; index++) { 
#   Error:          ^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...


- cdb-b01-pair-0-pointer: COMPILE FAIL ### mwcceppc.exe Compiler:
#    File: build\rx2b\trials\cdb-b01-pair-0-pointer\CDBFileSystemUtils.c
# ----------------------------------------------------------------------
#     112:     for (int index = 0; index < 2; index++) { 
#   Error:          ^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...


- cdb-b01-pair-1-indexed: CDBFSIsCDBFileOnSD 97.44095%; insns 125/127, diffs 104; pool IDENTICAL 0/0

- cdb-b01-pair-1-pointer: CDBFSIsCDBFileOnSD 97.20473%; insns 125/127, diffs 104; pool IDENTICAL 0/0

- cdb-b01-pair-2-indexed: CDBFSIsCDBFileOnSD 93.77165%; insns 129/127, diffs 117; pool IDENTICAL 0/0

- cdb-b01-pair-2-pointer: CDBFSIsCDBFileOnSD 94.00787%; insns 129/127, diffs 117; pool IDENTICAL 0/0

- warning-b01-reused-BOOL: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-b01-reused-bool: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-b02-reset-pointer: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-b03-reset-visible-pointer: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-b02-reset-reference: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-b03-reset-visible-reference: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- cdb-b02-pair-0-indexed: CDBFSIsCDBFileOnSD 94.52756%; insns 132/127, diffs 94; pool IDENTICAL 0/0

- cdb-b02-pair-0-pointer: CDBFSIsCDBFileOnSD 94.291336%; insns 132/127, diffs 94; pool IDENTICAL 0/0

- title-b01-predicate-0: getTitleName__Q33ipl7channel7ManagerCFiii 92.39436%; insns 74/71, diffs 63; pool IDENTICAL 9/9

- title-b01-predicate-1: getTitleName__Q33ipl7channel7ManagerCFiii 92.39436%; insns 74/71, diffs 63; pool IDENTICAL 9/9

- title-b01-predicate-2: getTitleName__Q33ipl7channel7ManagerCFiii 92.39436%; insns 74/71, diffs 63; pool IDENTICAL 9/9

- title-b02-language-cast-0: getTitleName__Q33ipl7channel7ManagerCFiii 99.366196%; insns 71/71, diffs 7; pool IDENTICAL 9/9

- title-b02-language-cast-1: getTitleName__Q33ipl7channel7ManagerCFiii 99.366196%; insns 71/71, diffs 7; pool IDENTICAL 9/9

- title-b02-language-cast-2: getTitleName__Q33ipl7channel7ManagerCFiii 97.1831%; insns 72/71, diffs 55; pool IDENTICAL 9/9

- title-b03-reused-character: getTitleName__Q33ipl7channel7ManagerCFiii 99.366196%; insns 71/71, diffs 7; pool IDENTICAL 9/9

- tvrc-b01-file-locals-ptr: TVRCSendStartAsync 99.747475%; insns 198/198, diffs 9; pool IDENTICAL 0/0

- tvrc-b01-file-locals-ref: TVRCSendStartAsync 99.09091%; insns 199/198, diffs 143; pool IDENTICAL 0/0

- tvrc-b02-entry-helper-first: TVRCSendStartAsync 99.747475%; insns 198/198, diffs 9; pool IDENTICAL 0/0

- tvrc-b02-entry-helper-repeat: TVRCSendStartAsync 98.5101%; insns 196/198, diffs 142; pool IDENTICAL 0/0

- tvrc-b02-entry-helper-both: TVRCSendStartAsync 98.5101%; insns 196/198, diffs 142; pool IDENTICAL 0/0

- warning-b04-draw-dialogs: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- tvrc-b03-distinct-entry-locals: TVRCSendStartAsync 98.39899%; insns 197/198, diffs 149; pool IDENTICAL 0/0

- warning-b05-draw-overlays: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-b06-controller-update: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-b07-reset-helper-bool: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-b07-reset-helper-BOOL: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-b08-result-BOOL-bool: warning_run__Q23ipl6SystemFv 97.38636%; insns 178/176, diffs 151; pool IDENTICAL 52/52

- warning-b08-result-BOOL-BOOL: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-b08-result-u32-bool: warning_run__Q23ipl6SystemFv 97.38636%; insns 178/176, diffs 151; pool IDENTICAL 52/52

- warning-b08-result-u32-u32: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-b08-result-u8-bool: warning_run__Q23ipl6SystemFv 97.38636%; insns 178/176, diffs 151; pool IDENTICAL 52/52

- warning-b08-result-u8-u8: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- cdb-b03-cursor-live-0: CDBFSIsCDBFileOnSD 97.27559%; insns 127/127, diffs 33; pool IDENTICAL 0/0

- cdb-b03-cursor-live-1: CDBFSIsCDBFileOnSD 97.27559%; insns 127/127, diffs 33; pool IDENTICAL 0/0

- cdb-b03-cursor-live-2: CDBFSIsCDBFileOnSD 97.95276%; insns 126/127, diffs 118; pool IDENTICAL 0/0

- warning-b09-float-size-0: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-b09-float-size-1: warning_run__Q23ipl6SystemFv 98.59659%; insns 176/176, diffs 51; pool IDENTICAL 52/52

- warning-b09-float-size-2: warning_run__Q23ipl6SystemFv 96.84659%; insns 178/176, diffs 131; pool IDENTICAL 52/52

- warning-b09-float-size-3: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-b10-break-loop: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-b11-reused-result: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- cdb-b04-unrolled-indexed: CDBFSIsCDBFileOnSD 99.09449%; insns 127/127, diffs 17; pool IDENTICAL 0/0

- cdb-b05-unrolled-int-index: CDBFSIsCDBFileOnSD 97.519684%; insns 125/127, diffs 116; pool IDENTICAL 0/0

- tvrc-b04-bit-array-u32: TVRCSendStartAsync 99.747475%; insns 198/198, diffs 9; pool IDENTICAL 0/0

- cdb-b06-unrolled-reference: CDBFSIsCDBFileOnSD 99.09449%; insns 127/127, diffs 17; pool IDENTICAL 0/0

- tvrc-b04-bit-array-u16: TVRCSendStartAsync 99.747475%; insns 198/198, diffs 9; pool IDENTICAL 0/0

- cdb-b07-classification-u16: CDBFSIsCDBFileOnSD 98.149605%; insns 127/127, diffs 19; pool IDENTICAL 0/0

- tvrc-b04-bit-array-char: TVRCSendStartAsync 99.747475%; insns 198/198, diffs 9; pool IDENTICAL 0/0

- cdb-b07-classification-u32: CDBFSIsCDBFileOnSD 99.09449%; insns 127/127, diffs 17; pool IDENTICAL 0/0

- tvrc-b05-positive-range: TVRCSendStartAsync 97.676765%; insns 198/198, diffs 167; pool IDENTICAL 0/0

- cdb-b07-classification-int: CDBFSIsCDBFileOnSD 99.09449%; insns 127/127, diffs 17; pool IDENTICAL 0/0

- tvrc-b06-reused-status: TVRCSendStartAsync 99.747475%; insns 198/198, diffs 9; pool IDENTICAL 0/0

- title-b04-text-view-0: getTitleName__Q33ipl7channel7ManagerCFiii 90.26761%; insns 76/71, diffs 66; pool IDENTICAL 9/9

- title-b04-text-view-1: getTitleName__Q33ipl7channel7ManagerCFiii 90.26761%; insns 76/71, diffs 66; pool IDENTICAL 9/9

- title-b05-flat-text-view: getTitleName__Q33ipl7channel7ManagerCFiii 86.014084%; insns 79/71, diffs 65; pool IDENTICAL 9/9

- warning-b12-begin-0: warning_run__Q23ipl6SystemFv 94.17614%; insns 183/176, diffs 153; pool IDENTICAL 52/52

- title-b06-pointer-grouping-1: getTitleName__Q33ipl7channel7ManagerCFiii 99.366196%; insns 71/71, diffs 7; pool IDENTICAL 9/9

- warning-b12-begin-1: warning_run__Q23ipl6SystemFv 94.17614%; insns 183/176, diffs 153; pool IDENTICAL 52/52

- title-b06-pointer-grouping-2: getTitleName__Q33ipl7channel7ManagerCFiii 99.366196%; insns 71/71, diffs 7; pool IDENTICAL 9/9

- title-b06-pointer-grouping-3: getTitleName__Q33ipl7channel7ManagerCFiii 99.366196%; insns 71/71, diffs 7; pool IDENTICAL 9/9

- cdb-b08-single-index-char: CDBFSIsCDBFileOnSD 90.8189%; insns 128/127, diffs 109; pool IDENTICAL 0/0

- cdb-b08-single-index-int: CDBFSIsCDBFileOnSD 100.0%; insns 127/127, diffs 0; pool IDENTICAL 0/0

- cdb-b08-single-index-u32: CDBFSIsCDBFileOnSD 100.0%; insns 127/127, diffs 0; pool IDENTICAL 0/0

- cdb-b09-filename-record-pairs: CDBFSIsCDBFileOnSD 99.09449%; insns 127/127, diffs 17; pool IDENTICAL 0/0

- cdb-b09-filename-record-bytes: CDBFSIsCDBFileOnSD 97.125984%; insns 128/127, diffs 117; pool IDENTICAL 0/0

- title-b07-header-pointer-ref-0: getTitleName__Q33ipl7channel7ManagerCFiii 88.211266%; insns 74/71, diffs 63; pool IDENTICAL 9/9

- title-b07-header-pointer-ref-1: getTitleName__Q33ipl7channel7ManagerCFiii 88.211266%; insns 74/71, diffs 63; pool IDENTICAL 9/9

- title-b07-header-pointer-ref-2: getTitleName__Q33ipl7channel7ManagerCFiii 88.211266%; insns 74/71, diffs 63; pool IDENTICAL 9/9

- title-b08-name-first-helper-0: getTitleName__Q33ipl7channel7ManagerCFiii 99.366196%; insns 71/71, diffs 7; pool IDENTICAL 9/9

- title-b08-name-first-helper-1: getTitleName__Q33ipl7channel7ManagerCFiii 99.366196%; insns 71/71, diffs 7; pool IDENTICAL 9/9

- tvrc-b07-stride-uses-2: TVRCSendStartAsync 97.87374%; insns 198/198, diffs 16; pool IDENTICAL 0/0

- tvrc-b07-stride-uses-3: TVRCSendStartAsync 97.44949%; insns 198/198, diffs 17; pool IDENTICAL 0/0

- tvrc-b07-stride-uses-4: TVRCSendStartAsync 98.35354%; insns 199/198, diffs 140; pool IDENTICAL 0/0

- tvrc-b07-stride-uses-5: TVRCSendStartAsync 99.14141%; insns 199/198, diffs 146; pool IDENTICAL 0/0

- tvrc-b07-stride-uses-6: TVRCSendStartAsync 98.52525%; insns 197/198, diffs 144; pool IDENTICAL 0/0

- tvrc-b07-stride-uses-7: TVRCSendStartAsync 98.80808%; insns 197/198, diffs 144; pool IDENTICAL 0/0

Allocator follow-through, first checkpoint:

- CDBFSIsCDBFileOnSD: converted candidate b08-single-index-int is 100.0%, 127/127 instructions, zero differences, whole unit 11/11 and code 2480/2480, data 8/8. The target's pair loop was produced by compiler unrolling of a single `int i` loop over eight characters. Writing pairs in source introduced the cursor during high-level optimization, before classifier temporaries, so it lost r3. In the successful capture, backend-00 has `lbzx v39, fileName(v32), i(v33)` and no cursor. Backend-01 introduces cursor v55 and unrolls to loads at offsets 0 and 1. Reverse simplify order colors v55 to r3 before classifier map v45 to r4, character v39 to r5, and locale v35 to r6. The original character-index loop prevented this late transformation; the pair-array rewrites reproduced the output instructions but not the virtual-register creation order. Both signed int and u32 loops match; retained the ordinary int loop. Capture `build/rx2b/mwdbg/cdb-single-int` is whole-object identical to normal wibo/SJIS, SHA256 d6ad604c47f946ac149ddcfcb396fd213e0debab49be8afe2febe58d2dc2990e. Applied only after that confirmation; normal Ninja/pool/ctxdiff passed. Removed the compiler-specific asm branch and its old non-MW fallback together.
- CDB manual pair confirmation `cdb-unrolled`: the two explicit checks have exactly the same object as the typed pair loop, SHA256 4ccd7408fc0490bd066afce2d58314d6c1bc642e8b51df48aea0ee758bb102aa. Cursor v37 is already present in backend-00; later map v47 and character v41 still take r3 and r4 before cursor gets r5. This rejected capture led to restoring a scalar byte loop instead of introducing another cursor helper.
- TVRC: file pointer locals preserve the 198-instruction stream and the r6/r7 swap. Returning a command entry by reference from an inline helper instead causes backend-00 to retain one entry address v40 from the original file v38. B13/B14 then load both repeat offsets through v40; the target reloads the current file and constructs its entry address separately. The helper loses two instructions before allocation, so it is rejected. Capture `tvrc-entry-helper` is whole-object identical to normal wibo/SJIS, SHA256 27a391b23d49e0e9df1f5c3c0ea27e3eba7d6d5e6772a3aa2806a6255302e208. Explicit stride uses in one or both repeat expressions change alias/CSE behavior and do not preserve the target stream.
- warning_run: reusing an ordinary BOOL for the initial reset result and saved pointer visibility creates a copy in backend-00, but backend-01 removes it. The saved visibility is still v41->r28, smArg base v45->r31, sound address v125->r30 and conversion constant v71->r29. smArg still has 32 neighbors and is deferred. The inline initial-display helper changes control flow and adds seven instructions. Other display/controller helper boundaries and float size locals canonicalize to the original graph. Capture `warning-reused` is whole-object identical to normal wibo/SJIS, SHA256 1011337a995d404050ecfba000d201e39ec91aa34c04d5fe443a1a6e0106ffa8.
- getTitleName: regenerated target Ghidra export in `build/rx2b/ghidra/src/system/iplChannelManager.c`. It confirms that the first character check combines the name/language offsets before adding metadata, while the fallback loop adds metadata/name before language. Pointer operand grouping preserves the original seven differences. Accessors taking a metadata pointer by reference defer the load but move the name stride past getLanguage and add three instructions. Accessors taking the name array preserve the seven-difference stream. These are address-tree and evaluation-boundary changes, not a solvable physical register permutation alone.

- tvrc-b08-offset-ref: TVRCSendStartAsync 99.747475%; insns 198/198, diffs 9; pool IDENTICAL 0/0

- tvrc-b08-offset-ptr: TVRCSendStartAsync 99.747475%; insns 198/198, diffs 9; pool IDENTICAL 0/0

- tvrc-b09-method-mutable-False: TVRCSendStartAsync 98.5101%; insns 196/198, diffs 142; pool IDENTICAL 0/0

- tvrc-b09-method-mutable-True: TVRCSendStartAsync 98.5101%; insns 196/198, diffs 142; pool IDENTICAL 0/0

- tvrc-b09-method-const-False: TVRCSendStartAsync 99.26768%; insns 197/198, diffs 148; pool IDENTICAL 0/0

- tvrc-b09-method-const-True: TVRCSendStartAsync 97.51515%; insns 197/198, diffs 166; pool IDENTICAL 0/0

- title-b09-boolean-name-bool: getTitleName__Q33ipl7channel7ManagerCFiii 99.366196%; insns 71/71, diffs 7; pool IDENTICAL 9/9

- title-b09-boolean-name-BOOL: getTitleName__Q33ipl7channel7ManagerCFiii 99.366196%; insns 71/71, diffs 7; pool IDENTICAL 9/9

- title-b10-loop-lang-int: getTitleName__Q33ipl7channel7ManagerCFiii 99.57746%; insns 71/71, diffs 4; pool IDENTICAL 9/9

- title-b10-loop-lang-unsigned-int: getTitleName__Q33ipl7channel7ManagerCFiii 99.57746%; insns 71/71, diffs 4; pool IDENTICAL 9/9

- title-b10-loop-lang-long: getTitleName__Q33ipl7channel7ManagerCFiii 99.57746%; insns 71/71, diffs 4; pool IDENTICAL 9/9

- title-b11-name-index-unsigned-int: getTitleName__Q33ipl7channel7ManagerCFiii 91.54929%; insns 74/71, diffs 62; pool IDENTICAL 9/9

- title-b12-language-index-unsigned-int: getTitleName__Q33ipl7channel7ManagerCFiii 99.57746%; insns 71/71, diffs 4; pool IDENTICAL 9/9

- title-b11-name-index-unsigned-long: getTitleName__Q33ipl7channel7ManagerCFiii 91.54929%; insns 74/71, diffs 62; pool IDENTICAL 9/9

- title-b12-language-index-unsigned-long: getTitleName__Q33ipl7channel7ManagerCFiii 99.57746%; insns 71/71, diffs 4; pool IDENTICAL 9/9

- title-b11-name-index-long: getTitleName__Q33ipl7channel7ManagerCFiii 99.57746%; insns 71/71, diffs 4; pool IDENTICAL 9/9

- title-b12-language-index-long: getTitleName__Q33ipl7channel7ManagerCFiii 99.57746%; insns 71/71, diffs 4; pool IDENTICAL 9/9

- tvrc-b10-index-cast-int-1: TVRCSendStartAsync 99.36869%; insns 199/198, diffs 145; pool IDENTICAL 0/0

- tvrc-b10-index-cast-int-2: TVRCSendStartAsync 99.36869%; insns 199/198, diffs 145; pool IDENTICAL 0/0

- tvrc-b10-index-cast-int-3: TVRCSendStartAsync 99.747475%; insns 198/198, diffs 9; pool IDENTICAL 0/0

- tvrc-b10-index-cast-unsigned-int-1: TVRCSendStartAsync 99.36869%; insns 199/198, diffs 145; pool IDENTICAL 0/0

- tvrc-b10-index-cast-unsigned-int-2: TVRCSendStartAsync 99.36869%; insns 199/198, diffs 145; pool IDENTICAL 0/0

- tvrc-b10-index-cast-unsigned-int-3: TVRCSendStartAsync 99.747475%; insns 198/198, diffs 9; pool IDENTICAL 0/0

- tvrc-b10-index-cast-u32-1: TVRCSendStartAsync 99.36869%; insns 199/198, diffs 145; pool IDENTICAL 0/0

- title-b11-name-index-int: getTitleName__Q33ipl7channel7ManagerCFiii 99.57746%; insns 71/71, diffs 4; pool IDENTICAL 9/9

- tvrc-b10-index-cast-u32-2: TVRCSendStartAsync 99.36869%; insns 199/198, diffs 145; pool IDENTICAL 0/0

- tvrc-b10-index-cast-u32-3: TVRCSendStartAsync 99.747475%; insns 198/198, diffs 9; pool IDENTICAL 0/0

- title-b13-assigned-in-index-u32: getTitleName__Q33ipl7channel7ManagerCFiii 99.57746%; insns 71/71, diffs 4; pool IDENTICAL 9/9

- title-b13-assigned-in-index-int: getTitleName__Q33ipl7channel7ManagerCFiii 99.366196%; insns 71/71, diffs 7; pool IDENTICAL 9/9

- warning-b13-reset-check-0: warning_run__Q23ipl6SystemFv 98.03977%; insns 177/176, diffs 165; pool IDENTICAL 52/52

- warning-b13-reset-check-1: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-b13-reset-check-2: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-b13-reset-check-3: warning_run__Q23ipl6SystemFv 98.63636%; insns 176/176, diffs 48; pool IDENTICAL 52/52

- warning-b14-reset-value-bool: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-b14-reset-value-BOOL: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- title-b14-all-name-index-unsigned-int: getTitleName__Q33ipl7channel7ManagerCFiii 99.57746%; insns 71/71, diffs 4; pool IDENTICAL 9/9

- title-b14-all-name-index-u32: getTitleName__Q33ipl7channel7ManagerCFiii 99.57746%; insns 71/71, diffs 4; pool IDENTICAL 9/9

- title-b14-all-name-index-long: getTitleName__Q33ipl7channel7ManagerCFiii 99.57746%; insns 71/71, diffs 4; pool IDENTICAL 9/9

- title-b15-local-language-int: getTitleName__Q33ipl7channel7ManagerCFiii 99.366196%; insns 71/71, diffs 7; pool IDENTICAL 9/9

- title-b15-local-language-unsigned-int: getTitleName__Q33ipl7channel7ManagerCFiii 99.57746%; insns 71/71, diffs 4; pool IDENTICAL 9/9

First clean gate, after CDB conversion: `build/rx2b/gate-first.log` reports GATE PASS, no regressions, no new forbidden patterns, no readability warnings, and DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Four units remain 157/157 instruction-exact including retained asm, code 29800/29800 and data 3596/3596. CDB source committed as 64a4a009.

Title progress: b10-loop-lang-int reaches 99.57746%, 71/71 instructions, four differences. The only source change from b00 is casting the language lookup value to int at the fallback-loop character check. This prevents high-level sharing of the language stride between the check and return. Capture `title-loop-language-cast`: backend-00 B9 loads metadata v67, computes language stride v68, adds metadata+name stride in v69, then v68+v69 in v70, exactly the target dependency order. B10 independently computes the return stride v73. Backend-01 combines v73 with v68 after the correct addition tree already exists. Colors now match the fallback loop: metadata/address v67/v69->r0, language stride v68->r5, final address v70->r4. The first check in B4 remains metadata+language then name stride, leaving four differences. Full captured object and normal wibo/SJIS object are identical, SHA256 c75ff51bc2a3a5561c5ff875a35aea213fab8bdef7419839e742287668d4b736. Equivalent unsigned-int and long casts also fix this loop; array accessor helpers and casting the first getLanguage result do not fix B4. Retain asm until all four remaining differences are gone.

- title-b16-inverted-else: getTitleName__Q33ipl7channel7ManagerCFiii 79.71831%; insns 71/71, diffs 43; pool IDENTICAL 9/9

- title-b17-inverted-early: getTitleName__Q33ipl7channel7ManagerCFiii 79.71831%; insns 71/71, diffs 43; pool IDENTICAL 9/9

- title-b18-nonempty-value-bool: getTitleName__Q33ipl7channel7ManagerCFiii 97.253525%; insns 72/71, diffs 55; pool IDENTICAL 9/9

- title-b18-nonempty-value-BOOL: getTitleName__Q33ipl7channel7ManagerCFiii 97.253525%; insns 72/71, diffs 55; pool IDENTICAL 9/9

Source-search queue status: four stock srcsearch seeds requested 180 seconds each. All stayed behind the shared 24-slot limiter with no output directory and zero compiled trials. Cancelled only this worktree's four queued processes after the manual/debugger work; these are not counted as completed searches. Elapsed wall seconds, including the short pause during the clean gate: warning 1085, title 1086, tvrc 1087, cdb 1087. No limiter or shared tool was changed. Manual trials above cover each owned function.

TVRC final confirmation: `tvrc-offset-reference` uses an ordinary reference to the actual offset field instead of a reference to the whole entry. Backend-00 still gives stride v43 and current-file bases v39/v38; reverse simplify colors v43 to r6 before v39/v38 receive r7. The target needs the inverse assignment. Backend-01 keeps the correct current-file repeat-entry dependency, but the nine register differences remain. Whole-object identity against normal wibo/SJIS is confirmed, SHA256 7e55013d99f4a7890699e712aae47387a39b691fdedbeec4f8b63d87db270663. Inline file methods, signedness conversions in individual subscripts, and explicit byte strides change CSE or add/remove instructions. No TVRC source change is retained.

warning_run final source tests: explicit reset-result locals and boolean normalization preserve the deferred smArg graph. Comparing the reset predicate with TRUE adds one instruction; comparing with greater-than-zero retains the 176 count but changes the condition instruction as well. The graph-confirmed 98.66477% candidate remains best. No warning source change is retained.

Title final source tests: unsigned name-index conversions shared across all uses preserve 71 instructions but leave B4's four differences. Changing local language signedness, assigning getLanguage in the index, or moving the fallback into the first branch does not fix B4. Explicit has-name BOOL/bool locals add an instruction. Best safe candidate is `build/rx2b/trials/title-b10-loop-lang-int/iplChannelManager.cpp`; only the fallback check uses `names[(int)language][nameIndex][0]`. The four remaining instructions are the initial mulli/lwz and two address adds, before allocation. No title source change is retained.

Completed compiled candidates, including each fresh baseline: cdb 21, title 42, tvrc 33, warning 32. Every open function has more than three distinct compiled source changes. All candidate and debugger artifacts are under build/rx2b; only CDB source is retained.

Reproducible improved title candidate, 99.57746%, four pre-allocation address differences. This is reference C, not an accepted source replacement:

```cpp
wchar_t* Manager::getTitleName(int page, int index, int nameIndex) const {
    u32 language;
    const u32* languages;
    if (!mChannels[page][index].loadedBnr) {
        return NULL;
    }
    if (mChannels[page][index].metaHdr->names[System::getLanguage()][nameIndex][0]) {
        return mChannels[page][index].metaHdr->names[System::getLanguage()][nameIndex];
    }
    languages = scLangLookup[System::getRegion()];
    for (int i = 0; i < 16; i++) {
        language = languages[i];
        if (mChannels[page][index].metaHdr->names[(int)language][nameIndex][0]) {
            return mChannels[page][index].metaHdr->names[language][nameIndex];
        }
        if (language == -1) {
            break;
        }
    }
    return mChannels[page][index].metaHdr->names[languages[0]][nameIndex];
}
```

Final acceptance:

- Clean full gate: `build/rx2b/gate-final.log`, exit 0, GATE PASS. Full 43U build passes. Regressions 0; net forbidden additions 0; readability warnings 0. Every owned section is 100.0%.
- [src/system/TVRC] instruction-exact functions: 9/9; code 2312/2312; data 280/280; linked code 2312.
- [src/system/iplChannelManager] instruction-exact functions: 74/74; code 12552/12552; data 1080/1080; linked code 12552.
- [libs/RevoEX/src/cdb/CDBFileSystemUtils] instruction-exact functions: 11/11; code 2480/2480; data 8/8; linked code 2480.
- [src/system/iplSystem] instruction-exact functions: 63/63; code 12456/12456; data 2228/2228; linked code 12456.
- Before -> after including existing asm: exact functions 157 -> 157, code bytes 29800 -> 29800, data bytes 3596 -> 3596. One additional asm function is now readable exact C: CDBFSIsCDBFileOnSD, source commit 64a4a009.
- Fresh per-symbol validation after the final clean gate: all four exact-name objdiff values are 100.0%, pools identical, ctxdiff zero at 198/198, 71/71, 127/127 and 176/176 instructions. The three open functions retain their original asm. Machine-readable evidence: `build/rx2b/final-verification.json`.
- DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d.
- Regenerated `decomp_status.py` output under build/rx2b. The global completion checker returns 1 with DECOMPLETE_FAIL because the project still has unmatched and unlinked units; it is not a failure of this leaf gate. Overall code is 2780152/2995176 matched and 2314228/2995176 linked; no claim of project completion.
- Final tracked source diff against bfbaf84f is only CDBFileSystemUtils.c. TVRC.cpp, iplChannelManager.cpp and iplSystem.cpp remain byte-identical to this branch's original main baseline. Branch remains agent/w1005/rx2b; no push, PR, merge, rebase or other-worktree edits. All own queued search processes stopped; no debugger left running.
