# rx2 allocator experiments

Branch agent/w1005/rx2, starting commit 21c5ceda. Assigned six existing asm bodies. Accept only readable C/C++ with exact-name objdiff 100.0%, ctxdiff zero differences, unchanged pools, and a full gate preserving DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Otherwise restore the existing body and retain the rejected C in build/rx2.

Read deasm-round.md, common.md, levers 20-22, mwdbg README, da7 attempts, and prior g9/da6/da1b logs. The last three logs are absent on origin/main at 21c5ceda; recovered them read-only through git objects 88f7db56, 072e18a9, and 74f101d6. Fresh origin fetch confirms the assigned bodies remain asm.

The initial local mwdbg launcher redirected output and GDB working directory into this worktree and opened the shared port lock read-only. Later emulator include, encoding, and port workarounds are documented below and validated against normal wibo objects. The compiler executable, production build flags, and shared tooling were never modified. Original sources, rejected candidates, allocator captures and gate output live under build/rx2.

- exception-00-plain: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 99.18367%; insns 98/98, diffs 13; pool IDENTICAL 0/0

- cdb-00-plain: CDBFSIsCDBFileOnSD 98.85827%; insns 127/127, diffs 20; pool IDENTICAL 0/0

- sdi-00-best: ISD_GetCardSize 98.39286%; insns 84/84, diffs 20; pool IDENTICAL 4/4

- warning-00-best: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- title-00-best: getTitleName__Q33ipl7channel7ManagerCFiii 99.366196%; insns 71/71, diffs 7; pool IDENTICAL 9/9

## Baseline and target value maps

Fresh baseline quick gate passes, all six units exact with their existing asm, DOL 26116613f624061ba99c8d1a299aaa6efa85670d. Gate baseline is f22468d1, the nearest saved report one commit before this branch. No initial source edits.

- TVRC best C reproduced at 198/198, seven differences. Target r6 is the reloaded file after memcmp, r7 is cmd*8, r4 is the reloaded file plus command-table index, and r5 is the command record addressed through the original entry offset. Source selects r4/r3/r4 respectively and also loads repeatOffset through a different cached base at instruction 69. This is not established as a pure rename. Initial compile lacked the utility declaration; compiler failure was caught from the build log, the missing existing header was included, and all subsequent results require successful compilation before measurement.
- getTitleName best C reproduced at 71/71, seven differences. First check target r0 holds language*84 then nameIndex*42 + language*84, r3 holds metadata then the final address. C groups metadata + language*84 before nameIndex*42. Loop target r0 holds metadata + nameIndex*42; r5 holds language*84; r4 combines them. C groups the two offsets first. The addition trees differ before coloring.
- Exception plain C reproduces 99.18367%, 98/98, 13 differences without the older HorizontalPosition carrier. Target r29 holds xCur, r27 holds loop count 4, and r26 holds the KPADRead byte offset. C uses r26, r29, r27 respectively. Other saved values match: r31 yCur, r30 scroll maximum, r28 this, r25 previous y, r24 previous x, r23 read channel.
- CDB plain C gives 98.85827%, 127/127, 20 differences. Target r3 is the filename cursor, r6 the locale table, r5 the sign-extended character, r4 the ctype map. Plain C chooses r6, r5, r4, r3. The older 99.09449% candidate uses a forbidden cursor carrier; retained trials use plain locals.
- ISD best C reproduces 98.39286%, 84/84, 20 differences. Target r3 holds sectorCount and sizeMultiplier at different times, r4 clamped readBlockLength then its shift, r5 eraseBlockSize, r0 eraseBlockCount at the final stores. Source sectorCount is r4, readBlockLength r3 then shift r6, and sizeMultiplier r5.
- warning_run best C reproduces 98.66477%, 176/176, 47 differences. Target r28 is smArg base, r29 saved pointer visibility, r30 conversion constant 0x4330, r31 sound-system address. C chooses r31, r28, r29, r30. Target and source r27 both hold the render-mode pointer.

All reproduced pools are identical. Immutable C snapshots are used for queued captures, so later trials cannot alter a pending debugger input. No carrier, functor, register keyword, or new asm is proposed.

- cdb-01-indexed-prefix: CDBFSIsCDBFileOnSD 97.125984%; insns 128/127, diffs 117; pool IDENTICAL 0/0

- cdb-02-prefix-helper: CDBFSIsCDBFileOnSD 95.03937%; insns 132/127, diffs 87; pool IDENTICAL 0/0

- cdb-03-reused-parameter: CDBFSIsCDBFileOnSD 98.70079%; insns 127/127, diffs 24; pool IDENTICAL 0/0

- cdb-04-character-result: CDBFSIsCDBFileOnSD 98.85827%; insns 127/127, diffs 20; pool IDENTICAL 0/0

- sdi-01-reuse-erase-size: ISD_GetCardSize 97.38095%; insns 84/84, diffs 21; pool IDENTICAL 4/4

- sdi-02-reuse-clamped-length: ISD_GetCardSize 98.39286%; insns 84/84, diffs 20; pool IDENTICAL 4/4

- sdi-03-reuse-multiplier: ISD_GetCardSize 98.39286%; insns 84/84, diffs 20; pool IDENTICAL 4/4

- sdi-04-reuse-arithmetic: ISD_GetCardSize 97.38095%; insns 84/84, diffs 21; pool IDENTICAL 4/4

- sdi-05-erase-bits-local: ISD_GetCardSize 98.39286%; insns 84/84, diffs 20; pool IDENTICAL 4/4

- sdi-06-separate-multiplier-result: ISD_GetCardSize 98.39286%; insns 84/84, diffs 20; pool IDENTICAL 4/4

- cdb-05-cursor-function: CDBFSIsCDBFileOnSD 98.85827%; insns 127/127, diffs 20; pool IDENTICAL 0/0

- cdb-06-outer-inline: CDBFSIsCDBFileOnSD 98.74016%; insns 127/127, diffs 22; pool IDENTICAL 0/0

- cdb-07-typed-pair-cursor: CDBFSIsCDBFileOnSD 98.85827%; insns 127/127, diffs 20; pool IDENTICAL 0/0

- cdb-08-pair-cursor-indexed: CDBFSIsCDBFileOnSD 99.09449%; insns 127/127, diffs 17; pool IDENTICAL 0/0

- cdb-09-returned-advance: CDBFSIsCDBFileOnSD 98.85827%; insns 127/127, diffs 20; pool IDENTICAL 0/0

- sdi-07-reuse-size-word: ISD_GetCardSize 98.15476%; insns 84/84, diffs 21; pool IDENTICAL 4/4

- sdi-08-reuse-return-for-size: ISD_GetCardSize 98.39286%; insns 84/84, diffs 20; pool IDENTICAL 4/4

- sdi-09-named-unclamped: ISD_GetCardSize 98.39286%; insns 84/84, diffs 20; pool IDENTICAL 4/4

- sdi-10-clamp-boundaries: ISD_GetCardSize 98.39286%; insns 84/84, diffs 20; pool IDENTICAL 4/4

- sdi-11-size-outside-branch: COMPILE FAIL ### mwcceppc.exe Compiler:
#    File: build\rx2\trials\sdi-11-size-outside-branch\sdi_api.c
# --------------------------------------------------------------
#     808:         u32 blockScale;
#   Error:         ^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...


- sdi-12-inline-geometry: ISD_GetCardSize 98.39286%; insns 84/84, diffs 20; pool IDENTICAL 4/4

## Debugger compatibility and first allocator findings

Retrowin32 crashes at compiler PC 0x47e090 before CodeGen when the four C++ commands use `-enc SJIS`. The same TVRC source without that encoding option compiles successfully under retrowin32 and is byte-identical to the real Ninja/wibo object, SHA256 5997280a44179dc00bafb87d4743e2c206332e836201e672e2c3260ac528b0b8. Debug captures omit only this frontend encoding option when present; production builds and trial scoring keep the real flags. Each successful capture is independently compared against wibo. This is an emulator compatibility workaround, not a retained compiler flag change.

CDB capture cdb-00: no coalescing candidates. Named ptr r35 is simplified early and colored after locale r37, character r41 and map-address r48. Their colors are r6, r5, r4, r3. To get target cursor r3, its priority must move ahead of the map-address temporaries. Tested indexed prefix, whole-prefix helper, reused parameter, a classifier result local, whole-function inline, typed pair pointer, indexed pair pointer, and returned advancement. The indexed pair array produces 99.09449% with 17 differences using ordinary C, matching the old carrier's score. It gives the compiler a real array stride and a synthesized loop cursor. Others remain worse. All pools identical.

ISD capture sdi-00: r71 is the packed erase-block-size intermediate, colored r3 before r40 sectorCount. Their interference forces r40 into r4. r60 is clamped readBlockLength minus nine, colored r6; r58 is the upper-clamp result, colored r3. Plain variable-reuse and named arithmetic experiments test whether these temporaries can become the named output or shift local. No target-color result yet. No spill or coalescing event explains the initial mismatch; it is priority and interference among ordinary low-degree nodes.

- cdb-10-scan-byte-helper: CDBFSIsCDBFileOnSD 97.27559%; insns 127/127, diffs 33; pool IDENTICAL 0/0

- cdb-11-advance-prefix-inline: CDBFSIsCDBFileOnSD 97.27559%; insns 127/127, diffs 33; pool IDENTICAL 0/0

- cdb-12-pair-reference: CDBFSIsCDBFileOnSD 99.09449%; insns 127/127, diffs 17; pool IDENTICAL 0/0

- cdb-13-array-inline: CDBFSIsCDBFileOnSD 97.125984%; insns 128/127, diffs 117; pool IDENTICAL 0/0

- cdb-14-pair-loop-local: CDBFSIsCDBFileOnSD 99.09449%; insns 127/127, diffs 17; pool IDENTICAL 0/0

- cdb-15-const-pair-array: CDBFSIsCDBFileOnSD 99.09449%; insns 127/127, diffs 17; pool IDENTICAL 0/0

- title-01-name-language-header: getTitleName__Q33ipl7channel7ManagerCFiii 95.07042%; insns 72/71, diffs 66; pool IDENTICAL 9/9

- title-01-language-name-header: getTitleName__Q33ipl7channel7ManagerCFiii 95.07042%; insns 72/71, diffs 66; pool IDENTICAL 9/9

- title-01-language-entry-name: getTitleName__Q33ipl7channel7ManagerCFiii 92.39436%; insns 74/71, diffs 63; pool IDENTICAL 9/9

- title-02-flat-titles: getTitleName__Q33ipl7channel7ManagerCFiii 79.26761%; insns 80/71, diffs 62; pool IDENTICAL 9/9

- title-03-flat-titles-reversed: getTitleName__Q33ipl7channel7ManagerCFiii 79.26761%; insns 80/71, diffs 62; pool IDENTICAL 9/9

- title-04-zero-name-offset: getTitleName__Q33ipl7channel7ManagerCFiii 90.19718%; insns 76/71, diffs 66; pool IDENTICAL 9/9

- sdi-13-erase-reuse-sizeMultiplier: ISD_GetCardSize 98.39286%; insns 84/84, diffs 20; pool IDENTICAL 4/4

- sdi-13-erase-reuse-capacity: ISD_GetCardSize 98.39286%; insns 84/84, diffs 20; pool IDENTICAL 4/4

- sdi-13-erase-reuse-eraseBlockCount: ISD_GetCardSize 98.39286%; insns 84/84, diffs 20; pool IDENTICAL 4/4

- sdi-13-erase-reuse-blockScale: ISD_GetCardSize 98.39286%; insns 84/84, diffs 20; pool IDENTICAL 4/4

- sdi-14-reversed-erase-expression: ISD_GetCardSize 97.61905%; insns 84/84, diffs 20; pool IDENTICAL 4/4

- sdi-15-reused-sector-arithmetic: ISD_GetCardSize 97.559525%; insns 84/84, diffs 27; pool IDENTICAL 4/4

- sdi-16-size-outside-fixed: ISD_GetCardSize 98.21429%; insns 84/84, diffs 23; pool IDENTICAL 4/4

- sdi-17-expression-0: ISD_GetCardSize 98.39286%; insns 84/84, diffs 20; pool IDENTICAL 4/4

- sdi-17-expression-1: ISD_GetCardSize 90.27381%; insns 84/84, diffs 26; pool IDENTICAL 4/4

- sdi-17-expression-2: ISD_GetCardSize 98.39286%; insns 84/84, diffs 20; pool IDENTICAL 4/4

- sdi-17-expression-3: ISD_GetCardSize 91.46429%; insns 84/84, diffs 20; pool IDENTICAL 4/4

- sdi-18-response-helper: ISD_GetCardSize 95.89286%; insns 85/84, diffs 49; pool IDENTICAL 4/4

- sdi-19-erase-before-size: ISD_GetCardSize 100.0%; insns 84/84, diffs 0; pool IDENTICAL 4/4

- tvrc-01-shared-repeat-entry: TVRCSendStartAsync 98.5101%; insns 196/198, diffs 142; pool IDENTICAL 0/0

- tvrc-02-reuse-table-pointer: TVRCSendStartAsync 99.77273%; insns 198/198, diffs 7; pool IDENTICAL 0/0

- tvrc-03-separate-command-pointers: TVRCSendStartAsync 98.5101%; insns 196/198, diffs 142; pool IDENTICAL 0/0

- tvrc-04-plain-direct-repeat: TVRCSendStartAsync 99.747475%; insns 198/198, diffs 9; pool IDENTICAL 0/0

- tvrc-05-command-helper: TVRCSendStartAsync 98.5101%; insns 196/198, diffs 142; pool IDENTICAL 0/0

- tvrc-06-reused-file-base: TVRCSendStartAsync 98.5101%; insns 196/198, diffs 142; pool IDENTICAL 0/0

- tvrc-07-bits-helper-0: TVRCSendStartAsync 99.77273%; insns 198/198, diffs 7; pool IDENTICAL 0/0

- tvrc-07-bits-helper-1: TVRCSendStartAsync 99.77273%; insns 198/198, diffs 7; pool IDENTICAL 0/0

- tvrc-07-bits-helper-2: TVRCSendStartAsync 99.77273%; insns 198/198, diffs 7; pool IDENTICAL 0/0

- tvrc-07-bits-helper-3: TVRCSendStartAsync 99.77273%; insns 198/198, diffs 7; pool IDENTICAL 0/0

- tvrc-08-repeat-helper: TVRCSendStartAsync 99.77273%; insns 198/198, diffs 7; pool IDENTICAL 0/0

- exception-01-read-local: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 99.18367%; insns 98/98, diffs 13; pool IDENTICAL 0/0

- exception-02-read-channel-temporary: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 99.18367%; insns 98/98, diffs 13; pool IDENTICAL 0/0

- exception-03-reuse-scroll-index: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 98.46939%; insns 98/98, diffs 23; pool IDENTICAL 0/0

- exception-04-single-channel-index: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 98.46939%; insns 98/98, diffs 23; pool IDENTICAL 0/0

- exception-05-y-loop-reuse: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 97.85714%; insns 98/98, diffs 36; pool IDENTICAL 0/0

- exception-06-loop-local-x: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 97.60204%; insns 98/98, diffs 39; pool IDENTICAL 0/0

- exception-07-short-x: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 92.29592%; insns 103/98, diffs 54; pool IDENTICAL 0/0

- exception-08-short-saved-x: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 98.11224%; insns 99/98, diffs 21; pool IDENTICAL 0/0

- exception-09-do-read: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 99.18367%; insns 98/98, diffs 13; pool IDENTICAL 0/0

- tvrc-09-order-0: TVRCSendStartAsync 98.66161%; insns 198/198, diffs 14; pool IDENTICAL 0/0

- tvrc-09-order-1: TVRCSendStartAsync 96.43434%; insns 198/198, diffs 17; pool IDENTICAL 0/0

- tvrc-09-order-2: TVRCSendStartAsync 99.747475%; insns 198/198, diffs 9; pool IDENTICAL 0/0

- tvrc-09-order-3: TVRCSendStartAsync 99.747475%; insns 198/198, diffs 9; pool IDENTICAL 0/0

- exception-10-priority-0: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 97.60204%; insns 98/98, diffs 39; pool IDENTICAL 0/0

- exception-10-priority-1: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 97.39796%; insns 98/98, diffs 39; pool IDENTICAL 0/0

- exception-10-priority-2: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 98.77551%; insns 98/98, diffs 22; pool IDENTICAL 0/0

- exception-10-priority-3: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 98.77551%; insns 98/98, diffs 22; pool IDENTICAL 0/0

- exception-10-priority-4: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 99.28571%; insns 98/98, diffs 14; pool IDENTICAL 0/0

- exception-10-priority-5: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 97.39796%; insns 98/98, diffs 39; pool IDENTICAL 0/0

ISD exact candidate sdi-19-erase-before-size: compute eraseBlockSize before sectorCount in the standard-capacity branch. This changes expression creation order so the earlier erase-field temporary no longer takes r3 before the sector arithmetic. Real Ninja compilation: 84/84, ctxdiff zero, pool 4/4 identical; exact-name objdiff 100.0%. Candidate copied to the owned source pending confirmation capture and full gate. Arithmetic is unchanged and response words are immutable between calculations.

C++ retrowin32 also performs case-sensitive include lookup. The existing source asks for nw4r/lyt/textbox.h while the file is textBox.h. A lowercase include alias exists only under build/rx2/include, pointing to the existing header. Debug commands add that overlay; wibo verification uses the same snapshot and proves compiler output equivalence. Shared headers and tools remain untouched.

TVRC tvrc-02 capture shows the last repeat-offset load already uses virtual r49, the original entry address, before register allocation. The desired target uses the reloaded-file entry instead. Named repeat-entry lifetime variants collapse two instructions; plain direct access preserves all 198 instructions with nine differences. Helpers for command-record lookup, bit assignment and repeat assignment did not change the seven-difference candidate. These are compiler CSE and liveness changes, not a target-proven volatile access.

Exception exception-01 capture: xCur r43 is simplified at degree 26 before later nodes; the loop-bound r35 has 32 interference neighbors and survives longer. Final coloring claims yCur r42->r31, max r40->r30, bound r35->r29, this r32->r28, controller byte offset r67->r27, then xCur r43->r26. Target wants xCur r29, bound r27, offset r26. Moving xCur earlier in the virtual-number walk requires later source declaration, with dependencies' declarations separated from assignments. Pointer-local, channel-local, reused-index, short-coordinate and do-loop trials do not reach exactness; next trials test the measured simplify order directly.

- exception-11-bound-order-0: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 99.69388%; insns 98/98, diffs 5; pool IDENTICAL 0/0

- exception-11-bound-order-1: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 97.85714%; insns 98/98, diffs 36; pool IDENTICAL 0/0

- exception-11-bound-order-2: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 97.60204%; insns 98/98, diffs 39; pool IDENTICAL 0/0

- exception-11-bound-order-3: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 97.60204%; insns 98/98, diffs 39; pool IDENTICAL 0/0

- exception-11-bound-order-4: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 98.77551%; insns 98/98, diffs 22; pool IDENTICAL 0/0

- exception-11-bound-order-5: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 98.77551%; insns 98/98, diffs 22; pool IDENTICAL 0/0

- exception-11-bound-order-6: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 98.77551%; insns 98/98, diffs 22; pool IDENTICAL 0/0

- exception-12-self-local-0: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 99.69388%; insns 98/98, diffs 5; pool IDENTICAL 0/0

- exception-12-self-local-1: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 99.69388%; insns 98/98, diffs 5; pool IDENTICAL 0/0

- exception-12-self-local-2: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 99.69388%; insns 98/98, diffs 5; pool IDENTICAL 0/0

- exception-12-self-local-3: COMPILE FAIL ### mwcceppc.exe Compiler:
#    File: build\rx2\trials\exception-12-self-local-3\iplException.cpp
# --------------------------------------------------------------------
#      34:     }
# Warning:     ^
#   (10184) return value expected
### mwcceppc.exe Compiler:
#      93:         s32 line = nw4r::db::Console_GetBufferHeadLine(exception->mConsole);
#   Error:                                                        ^^^^^^^^^
#   (10140) undefined identifier 'exception'
#   Too many errors printed, aborting program

User break, cancelled...


- exception-12-self-local-4: COMPILE FAIL ### mwcceppc.exe Compiler:
#    File: build\rx2\trials\exception-12-self-local-4\iplException.cpp
# --------------------------------------------------------------------
#      34:     }
# Warning:     ^
#   (10184) return value expected
### mwcceppc.exe Compiler:
#      93:         s32 line = nw4r::db::Console_GetBufferHeadLine(exception->mConsole);
#   Error:                                                        ^^^^^^^^^
#   (10140) undefined identifier 'exception'
#   Too many errors printed, aborting program

User break, cancelled...


- exception-12-self-local-5: COMPILE FAIL ### mwcceppc.exe Compiler:
#    File: build\rx2\trials\exception-12-self-local-5\iplException.cpp
# --------------------------------------------------------------------
#      34:     }
# Warning:     ^
#   (10184) return value expected
### mwcceppc.exe Compiler:
#      93:         s32 line = nw4r::db::Console_GetBufferHeadLine(exception->mConsole);
#   Error:                                                        ^^^^^^^^^
#   (10140) undefined identifier 'exception'
#   Too many errors printed, aborting program

User break, cancelled...


- exception-13-reuse-autoscroll: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 99.69388%; insns 98/98, diffs 5; pool IDENTICAL 0/0

- exception-14-constant-count: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 99.28571%; insns 98/98, diffs 14; pool IDENTICAL 0/0

- exception-15-read-array-index: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 99.69388%; insns 98/98, diffs 5; pool IDENTICAL 0/0

- exception-16-explicit-byte-count: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 97.65306%; insns 98/98, diffs 6; pool IDENTICAL 0/0

- warning-01-integer-visibility: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-02-direct-render-mode: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-03-viewport-dimensions: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-04-save-frame-reference: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-05-direct-sound-reference: warning_run__Q23ipl6SystemFv 96.619316%; insns 173/176, diffs 80; pool IDENTICAL 52/52

- exception-17-index-0: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 99.69388%; insns 98/98, diffs 5; pool IDENTICAL 0/0

- exception-17-index-1: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 99.69388%; insns 98/98, diffs 5; pool IDENTICAL 0/0

- exception-17-index-2: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 99.69388%; insns 98/98, diffs 5; pool IDENTICAL 0/0

- warning-06-fader-helper: warning_run__Q23ipl6SystemFv 96.72159%; insns 177/176, diffs 97; pool IDENTICAL 52/52

- exception-17-index-3: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 99.69388%; insns 98/98, diffs 5; pool IDENTICAL 0/0

- exception-17-index-4: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 99.69388%; insns 98/98, diffs 5; pool IDENTICAL 0/0

- cdb-16-explicit-pair: CDBFSIsCDBFileOnSD 98.85827%; insns 127/127, diffs 20; pool IDENTICAL 0/0

- cdb-17-classifier-indices: CDBFSIsCDBFileOnSD 98.85827%; insns 127/127, diffs 20; pool IDENTICAL 0/0

- cdb-18-reversed-classifier: CDBFSIsCDBFileOnSD 98.85827%; insns 127/127, diffs 20; pool IDENTICAL 0/0

- cdb-19-check-all-by-array: CDBFSIsCDBFileOnSD 99.09449%; insns 127/127, diffs 17; pool IDENTICAL 0/0

- cdb-20-classifier-promoted: CDBFSIsCDBFileOnSD 98.85827%; insns 127/127, diffs 20; pool IDENTICAL 0/0

- tvrc-10-entry-table: TVRCSendStartAsync 99.747475%; insns 198/198, diffs 9; pool IDENTICAL 0/0

- tvrc-11-separate-entries: TVRCSendStartAsync 99.747475%; insns 198/198, diffs 9; pool IDENTICAL 0/0

- tvrc-12-record-block: TVRCSendStartAsync 99.747475%; insns 198/198, diffs 9; pool IDENTICAL 0/0

- tvrc-13-size-index: TVRCSendStartAsync 99.747475%; insns 198/198, diffs 9; pool IDENTICAL 0/0

- tvrc-14-direct-entry-offset: TVRCSendStartAsync 98.93939%; insns 199/198, diffs 150; pool IDENTICAL 0/0

- title-05-reused-name: getTitleName__Q33ipl7channel7ManagerCFiii 99.366196%; insns 71/71, diffs 6; pool IDENTICAL 9/9

- title-06-constant-index: getTitleName__Q33ipl7channel7ManagerCFiii 99.366196%; insns 71/71, diffs 7; pool IDENTICAL 9/9

- title-07-name-reference: getTitleName__Q33ipl7channel7ManagerCFiii 99.366196%; insns 71/71, diffs 7; pool IDENTICAL 9/9

- title-08-signed-language: getTitleName__Q33ipl7channel7ManagerCFiii 97.11268%; insns 70/71, diffs 26; pool IDENTICAL 9/9

- title-09-name-index-copy: getTitleName__Q33ipl7channel7ManagerCFiii 99.366196%; insns 71/71, diffs 7; pool IDENTICAL 9/9

Exception declaration changes put xCur in target r29. Moving the named remaining-controller count to the function's first declaration yields 99.69388%, 98/98, five differences: count r26 and byte offset r27 are swapped against target r27/r26. This is an honest improvement over the earlier best C; source snapshot build/rx2/trials/exception-11-bound-order-0/iplException.cpp. It is not retained as a conversion. Named self pointer aliases, narrower saved coordinates, array-reference/pair forms, and an independent controller index did not resolve this last swap. The explicit second index also reverses argument setup scheduling and is rejected.

Full clean ISD gate passed, zero regressions, zero forbidden additions, zero readability warnings, 22/22 instruction-exact functions, code 5948/5948 and data 248/248. DOL remains 26116613f624061ba99c8d1a299aaa6efa85670d. Log build/rx2/sdi-full-gate.log.

- exception-18-loop-0: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 97.79592%; insns 100/98, diffs 42; pool IDENTICAL 0/0

- exception-18-loop-1: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 100.0%; insns 98/98, diffs 0; pool IDENTICAL 0/0

- exception-18-loop-2: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 99.69388%; insns 98/98, diffs 5; pool IDENTICAL 0/0

- exception-18-loop-3: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 94.28571%; insns 98/98, diffs 59; pool IDENTICAL 0/0

- exception-18-loop-4: exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead 100.0%; insns 98/98, diffs 0; pool IDENTICAL 0/0

ISD confirmation sdi-19: packed erase-size intermediate moved from r71 to r63 and now colors r5. Capacity product becomes r71->r0, block scale r66->r3, shift r65->r4, sectorCount r40->r3, and sizeMultiplier r36->r3. These are the target choices. Captured object equals real wibo object byte for byte, SHA256 dd93fb5dcf72bacd041b3d18bc6ae5bb81f25c988a0f6c78a970666aa7af2d4d. The full gate and normal Ninja build both pass. Retain this conversion.

- tvrc-15-repeat-helper-0: TVRCSendStartAsync 99.36869%; insns 199/198, diffs 145; pool IDENTICAL 0/0

- tvrc-15-repeat-helper-1: TVRCSendStartAsync 99.36869%; insns 199/198, diffs 145; pool IDENTICAL 0/0

- tvrc-15-repeat-helper-2: TVRCSendStartAsync 99.36869%; insns 199/198, diffs 145; pool IDENTICAL 0/0

- tvrc-15-repeat-helper-3: TVRCSendStartAsync 99.36869%; insns 199/198, diffs 145; pool IDENTICAL 0/0

- tvrc-16-parameters-helper-0: TVRCSendStartAsync 99.747475%; insns 198/198, diffs 9; pool IDENTICAL 0/0

- tvrc-16-parameters-helper-1: TVRCSendStartAsync 98.22727%; insns 197/198, diffs 160; pool IDENTICAL 0/0

The additional relative include mismatch tiHWKeyboard.h versus tiHwKeyboard.h required an alias and include/keyboard in debug commands. A standalone retrowin32 compile of the full title unit now succeeds. These aliases remain scratch-only; no shared header path changes.

Exception exact candidate exception-18-loop-1 uses one ascending `chan` loop for applying controller input, without a separate countdown local. With the measured declaration order, this keeps xCur at r29 and moves the loop invariant and synthesized read offset to their target registers. Real build and ctxdiff: 98/98, diffs zero. Pool identical, objdiff 100.0%. Full clean gate passed at 7/7 exact, code 1004/1004, data 32/32, zero regressions and the required DOL hash. Removed surplus blank lines and fixed function indentation afterward; fresh object still has zero differences. Confirmation capture is pending.

TVRC direct-access capture tvrc-direct confirms a pure remaining swap in that variant: command byte offset r43->r6, file bases r39/r38->r7. Target is offset r7 and file r6. This direct form correctly keeps the repeat entry in r62->r4. The higher fuzzy seven-difference form has a different CSE dependency and is not a simple rename. This distinction is why the nine-difference C remains a separate starting point.

- tvrc-17-offset-pairs: TVRCSendStartAsync 99.747475%; insns 198/198, diffs 9; pool IDENTICAL 0/0

- tvrc-18-pointer-entries: TVRCSendStartAsync 99.747475%; insns 198/198, diffs 9; pool IDENTICAL 0/0

- tvrc-19-const-file: TVRCSendStartAsync 99.747475%; insns 198/198, diffs 9; pool IDENTICAL 0/0

CDB confirmation cdb-08: indexed pairs turn the cursor into compiler-generated r38, above locale r36 but still below character r41 and map r48. It colors r5, while locale now correctly colors r6; target cursor remains r3. The map and character take r3/r4 first. The captures have no spill or accepted coalescing responsible for this cycle. Whole-object validation is identical, SHA256 4ccd7408fc0490bd066afce2d58314d6c1bc642e8b51df48aea0ee758bb102aa. Additional explicit pair checks, argument-order classifier helpers and direct indexed pairs do not raise the best score. Existing exact asm remains.

Completed source searches: TVRC 155 trials, unchanged 99.747475%; title-name 38 trials, unchanged 99.366196%. Both retained their starting instruction count. No best.c or solution.c was adopted. CDB and warning searches remain queued behind the shared CPU limiter at this checkpoint.

- tvrc-20-const-file-pointer: TVRCSendStartAsync 99.747475%; insns 198/198, diffs 9; pool IDENTICAL 0/0

- tvrc-21-const-command-parameter: TVRCSendStartAsync 99.747475%; insns 198/198, diffs 9; pool IDENTICAL 0/0

- tvrc-22-byte-command-index: TVRCSendStartAsync 99.469696%; insns 198/198, diffs 9; pool IDENTICAL 0/0

- warning-07-whole-state-0: warning_run__Q23ipl6SystemFv 97.443184%; insns 174/176, diffs 62; pool IDENTICAL 52/52

- warning-07-whole-state-1: warning_run__Q23ipl6SystemFv 97.443184%; insns 174/176, diffs 62; pool IDENTICAL 52/52

- warning-07-whole-state-2: warning_run__Q23ipl6SystemFv 97.443184%; insns 174/176, diffs 62; pool IDENTICAL 52/52

- warning-07-whole-state-3: warning_run__Q23ipl6SystemFv 97.443184%; insns 174/176, diffs 62; pool IDENTICAL 52/52

- warning-08-direct-state: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- tvrc-23-byte-index-0: TVRCSendStartAsync 98.80808%; insns 197/198, diffs 144; pool IDENTICAL 0/0

- cdb-21-pair-local-0: CDBFSIsCDBFileOnSD 97.44095%; insns 128/127, diffs 117; pool IDENTICAL 0/0

- cdb-21-pair-local-1: CDBFSIsCDBFileOnSD 97.44095%; insns 128/127, diffs 117; pool IDENTICAL 0/0

- tvrc-23-byte-index-1: TVRCSendStartAsync 98.80808%; insns 197/198, diffs 144; pool IDENTICAL 0/0

- cdb-21-pair-local-2: COMPILE FAIL ### mwcceppc.exe Compiler:
#    File: build\rx2\trials\cdb-21-pair-local-2\CDBFileSystemUtils.c
# ------------------------------------------------------------------
#     115:             const signed char* pair = fileName + i * 2;
#   Error:                                                       ^
#   (10209) illegal implicit conversion from 'char *' to
#   'const signed char *'
#   Too many errors printed, aborting program

User break, cancelled...


- tvrc-23-byte-index-2: TVRCSendStartAsync 98.80808%; insns 197/198, diffs 144; pool IDENTICAL 0/0

- cdb-22-prefix-array: CDBFSIsCDBFileOnSD 99.09449%; insns 127/127, diffs 17; pool IDENTICAL 0/0

Warning source search completed 27 trials with no score or instruction-count improvement. Whole-state pointer/reference variants remove two instructions by reusing the final base; direct member expressions keep the original 47-register cycle. Neither is a conversion.

- warning-09-viewport-helper-0: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-09-viewport-helper-1: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-09-viewport-helper-2: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-10-viewport-size-helper: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

The shared 9001 debugger queue delayed the exception confirmation for over 20 minutes. A worktree-local bind adapter now changes only the emulator debugger listen port to 9202. The local driver differs only in its fixed tooling root and connection port; all allocator decoding and the compiler executable remain unchanged. Local captures serialize on build/rx2/.debug.lock. The adapter, driver, launcher, objects and logs are confined to this worktree. Cancelled only the four still-queued rx2 launchers before resubmitting. A network namespace probe was unavailable and made no persistent change. Every successful capture still requires complete object byte identity against normal wibo.

Exception confirmation exception-confirm proves the final choices: xCur is now v35 with 30 graph neighbors, so it remains in the high-degree set while simpler nodes are removed; its final simplify position follows this and precedes lineScrollMax/yCur. Reverse coloring is yCur v42->r31, lineScrollMax v40->r30, xCur v35->r29, this v32->r28. The single ascending controller loop creates the loop count as v67 and the read byte offset as v66; count colors r27 before offset r26. Previous y v39->r25, previous x v38->r24 and channel v37->r23 also match. There are no accepted copy coalesces that explain the correction. The complete captured object equals normal wibo, SHA256 3862ac3524d092b8ba337df97f43e6273c74e09a0369c264a5ab34646ed760a9. All local values are initialized before use. Retain the readable C++ conversion.

Title original capture title-original disproves a pure-color explanation. Before allocation B4 computes v52=language*84, v53=metadata, v54=v53+v52, v55=v54+nameOffset(v40). The target adds nameOffset+languageOffset first. In B9 the source computes v69=languageOffset(v39)+nameOffset(v40), v70=metadata(v68)+v69; the target first adds metadata+nameOffset. Coloring faithfully follows those different trees: v53/v54->r0, v52/v55->r3, and loop v68/v70->r4, v69->r0, v39->r5. A register renaming cannot make either dependency graph match. The complete capture is byte-identical to normal wibo, SHA256 d0aee5db097c084a462921523b78017dc289389dd6a5b7be5c0d52ed2b180ed7. The reused-name source is awaiting its confirmation capture.

CDB source search eventually acquired a shared slot and completed one trial with no improvement at 99.09449%, 127/127. The additional local-pair and whole-prefix array variants also did not solve cursor coloring. All search jobs have finished.

- warning-11-state-final-accessor: warning_run__Q23ipl6SystemFv 98.607956%; insns 176/176, diffs 48; pool IDENTICAL 52/52

- warning-12-state-tail-scope: warning_run__Q23ipl6SystemFv 98.607956%; insns 176/176, diffs 48; pool IDENTICAL 52/52

- warning-13-state-visible-tail: warning_run__Q23ipl6SystemFv 94.03409%; insns 180/176, diffs 67; pool IDENTICAL 52/52

- warning-14-state-reset-accessor: warning_run__Q23ipl6SystemFv 97.443184%; insns 174/176, diffs 62; pool IDENTICAL 52/52

- warning-15-output-visibility-0: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-15-output-visibility-1: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-15-output-visibility-2: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-15-output-visibility-3: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-16-outer-guard: warning_run__Q23ipl6SystemFv 98.66477%; insns 176/176, diffs 47; pool IDENTICAL 52/52

- warning-17-cached-sound: warning_run__Q23ipl6SystemFv 95.767044%; insns 177/176, diffs 161; pool IDENTICAL 52/52

- warning-18-cached-sound-declared: warning_run__Q23ipl6SystemFv 95.767044%; insns 177/176, diffs 161; pool IDENTICAL 52/52

Title confirmation title-confirm uses the ordinary reused-name pointer and improves seven differences to six without reaching exactness. B4 still adds metadata+languageOffset before nameOffset. B9 now adds metadata(v69)+languageOffset(v40), then nameOffset(v41); v69 colors r0, which fixes the metadata load register, but the target adds metadata+nameOffset first. No physical recoloring can fix this dependency order. Whole-object wibo identity holds, SHA256 dbdeef5bab9ffc04fbc862c8834774f7209c38b8289f2152fd6c57f701ee339d. Keep original asm.

Warning original capture warning-original: smArg base v44 has 32 neighbors. After earlier render-mode v37 and visibility v40 are simplified, its degree remains 30, above the 29-color limit. It is deferred until the end and colors first to r31. Sound-address v124 is then r30, conversion constant v70 is r29, and visibility v40 is r28. The target requires smArg r28, visibility r29, constant r30 and sound r31. Visibility is simplified at degree 27 and constant at degree 20; these choices explain the whole 47-register cycle. Whole-object wibo identity holds, SHA256 de3e209117c222d6433bed833bdba23e53e4004bc97b9958f8fba6bd2e74de4b. Directed whole-state reference/lifetime variants preserve the color cycle while changing address materialization; output-reference/pointer visibility helpers keep the original stream and cycle.

Compiled snapshot coverage: TVRC 35, title 12, exception 40, CDB 24, SDI 25, warning 27 (163 total, including baselines; compile failures excluded). Each assigned function received at least three distinct compiled source-level trials. Separate automated searches reported TVRC 155, title 38, CDB 1, warning 27 iterations; none improved the selected baseline. Best rejected C, source snapshots, diffs and reports remain in build/rx2/trials.

Warning confirmation warning-confirm uses an ordinary output-reference visibility helper. MWCC folds it into the same graph: smArg v44->r31 is still simplified last, sound v124->r30, conversion v70->r29, visibility v40->r28, render mode v37->r27. The priority and interference cause is unchanged. Complete object matches normal wibo, SHA256 d4bc5a2cbaffbc16b87adaca2e45880ab27c4868fec7ae29b5c9a719c2b73a5a. An inverted outer guard also keeps 47 differences; explicitly caching the sound pointer adds an instruction and is rejected. Keep original asm.

All allocator jobs and source searches are finished. Four unconverted production files are byte-identical to their versions at 21c5ceda. Only ISD_GetCardSize and Exception::exception_callback are retained C/C++ conversions. The final six-unit clean gate is next.

## Final handoff

Converted ISD_GetCardSize and Exception::exception_callback from existing asm to readable C/C++. Retained original asm for TVRCSendStartAsync, Manager::getTitleName, CDBFSIsCDBFileOnSD and System::warning_run. The four retained source files are byte-identical to 21c5ceda; their rejected C and allocator evidence remain under build/rx2.

| Unit | Exact functions before -> after | Exact code bytes | Exact data bytes |
| --- | --- | --- | --- |
| TVRC | 9/9 -> 9/9 | 2312/2312 | 280/280 |
| iplChannelManager | 74/74 -> 74/74 | 12552/12552 | 1080/1080 |
| iplException | 7/7 -> 7/7 | 1004/1004 | 32/32 |
| CDBFileSystemUtils | 11/11 -> 11/11 | 2480/2480 | 8/8 |
| sdi_api | 22/22 -> 22/22 | 5948/5948 | 248/248 |
| iplSystem | 63/63 -> 63/63 | 12456/12456 | 2228/2228 |

Exact-function counts stay unchanged because the original asm was already exact. Two of the six requested bodies are now C/C++.

- GATE PASS: SDI clean gate, build/rx2/sdi-full-gate.log.
- GATE PASS: exception clean gate, build/rx2/exception-full-gate.log.
- GATE PASS: final clean six-unit gate, build/rx2/final-full-gate.log. Zero regressions, zero forbidden additions, zero readability warnings. All 186 functions and every owned code/data section remain exact; all 36752 code bytes remain linked.
- Fresh exact-name objdiff is 100.0% for all six requested symbols. Fresh ctxdiff instruction counts are 198/198, 71/71, 98/98, 127/127, 84/84 and 176/176, respectively, all with diffs 0. Pools are identical in every unit. Evidence: build/rx2/final-verification.txt and final-verification.json.
- DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d. ninja -C . build/43U/ok passes.
- Source commits: 764e8f6a (SDI), c9175a03 (exception). The final log is committed separately.
- Final source scope: libs/RVL_SDK/src/sdi/sdi_api.c, src/system/iplException.cpp and this attempts log. No shared headers or build configuration changed. No push, PR, merge, rebase, or other-worktree edits. No rx2 search or debugger process remains running.
