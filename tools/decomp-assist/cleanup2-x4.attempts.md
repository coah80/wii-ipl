# cleanup2-x4 attempts

Assigned worktree `/mnt/drive2/projects/wii-ipl-workers/data-d1`, branch `agent/w1009/cleanup2-x4`; baseline `aed62d85`. Scope is `src/system/` and `src/utility/`, excluding `iplNandSDWorker.cpp`, `iplSystem.cpp`, `iplSaveDataManager.cpp`, and `iplESMisc.cpp`. The pre-existing untracked `rx67c.attempts.md` is left alone.

Read cleanup-common.md fully, including wave-2 guidance, and ran the full 43U build before source inspection. Baseline is 1028/1028 linked units, 12563/12563 exact functions, 100% code and data; completion checker returned `DECOMPLETE_OK`. DOL SHA1 is `26116613f624061ba99c8d1a299aaa6efa85670d`.

Saved owned source files, built objects and report in `/tmp/cleanup2-x4-baseline`. Each trial changes one function or independent expression, builds its object, and compares all allocated section bytes, sizes, alignment, exported symbols and relocation targets. Local relocation targets resolve to section and offset so compiler literal renumbering cannot hide a code or data difference. Rejected trials restore the prior source and rebuild its exact object.

Earlier cleanup-c2 trials already exhausted simple pragma removal and scoped-address variants in ChannelManager, Scroller pragma removal, cursor-copy alternatives, and set_string loop/flag versions. This pass does not repeat those families. Ordinary shared error/cleanup exits remain unless a useful exact simplification succeeds. Unknown header fields stay because headers are outside this worker's file assignment.

## Trials
- KEEP `src/system/odh` decompressLoop use early returns for work-buffer errors: allocated sections, exported symbols and resolved relocations identical.
- ODH compressor retains two idiomatic jumps to its single return. Decoder work-buffer errors now return early, removing 17 gotos and the label; ctxdiff is 899/899 instructions, diffs 0.
- KEEP `src/system/iplDialogWindow` start_trig_event move button lookup out of comma condition: allocated sections, exported symbols and resolved relocations identical.
- REVERT `src/system/iplNwc24Manager` addDlTask move retry delay to loop tail and remove entry goto: .text 12756->12756 bytes; .text relocation targets; addDlTask__Q33ipl5nwc247ManagerFv: 80 diffs, 98->98 instructions
- REVERT `src/system/iplNwc24Manager` addDlTask express retry delay and count as for-loop update: .text 12756->12756 bytes; .text relocation targets; addDlTask__Q33ipl5nwc247ManagerFv: 80 diffs, 98->98 instructions
- KEEP `src/system/iplNwc24Manager` addDlTask poll open in the while condition and return on timeout: allocated sections, exported symbols and resolved relocations identical.
- KEEP `src/system/iplNwc24Manager` receive name the received-message and cleanup labels: allocated sections, exported symbols and resolved relocations identical.
- NWC24 make_text and receive retain their ordinary shared cleanup jumps; utility set_string and Scroller retain the compiler requirements already tested in cleanup-c2. NAND File and MetaFile keep their shared cleanup/error exits. No unproven header-field rename was introduced.
- REVERT `src/system/iplPlayTimeLog` create_new_record read attachment constants without use-site volatility: .sdata2 36->52 bytes; .text relocation targets
- REVERT `src/system/iplPlayTimeLog` write_record read attachment constants without use-site volatility: .sdata2 36->52 bytes
- REVERT `src/system/iplTVRCManager` loadResources return directly when opening settings fails: .text 3484->3480 bytes; exported symbols; .text relocation targets; loadResources___Q23ipl11TVRCManagerFPQ23EGG4Heap: 116 diffs, 140->139 instructions
- KEEP `src/system/iplTVRCManager` update replace shared empty exit goto with return: allocated sections, exported symbols and resolved relocations identical.
- KEEP `src/system/iplTVRCManager` update use normal STATE_1 to STATE_2 switch fallthrough: allocated sections, exported symbols and resolved relocations identical.
- REVERT `src/system/iplPlayTimeLog` create_new_record move required attachment volatility to constant declarations: .sbss2 missing->8 bytes; .sdata2 36->28 bytes; .text 4900->4900 bytes; exported symbols; .text relocation targets; create_new_record__Q23ipl11PlayTimeLogFPCQ23ipl11EventBuffer: 10 diffs, 79->79 instructions
- REVERT `src/system/iplPlayTimeLog` write_record move required attachment volatility to constant declarations: .sbss2 missing->8 bytes; .sdata2 36->28 bytes; .text 4900->4900 bytes; .text relocation targets; write_record__Q23ipl11PlayTimeLogFP10_CDBRecordPQ23ipl11EventBufferPUc: 11 diffs, 70->70 instructions
- REVERT `src/system/iplControllerManager` read structure probe dispatch and empty-read handling, removing seven gotos: .text 1632->1664 bytes; exported symbols; .text relocation targets; read__Q33ipl10controller7ManagerFv: 196 diffs, 190->198 instructions
- KEEP `src/system/iplPlayTimeLog` replace stale matching notes with one-line reasons for retained volatile reads: allocated sections, exported symbols and resolved relocations identical.
- REVERT `src/system/iplTVRCManager` loadResources guard settings processing with a structured open-success branch: .text 3484->3484 bytes; loadResources___Q23ipl11TVRCManagerFPQ23EGG4Heap: 2 diffs, 140->140 instructions
- REVERT `src/system/iplControllerManager` read structure the empty-read branch independently of probe dispatch: .text 1632->1632 bytes; .text relocation targets; read__Q33ipl10controller7ManagerFv: 71 diffs, 190->190 instructions
- REVERT `src/system/iplNandShared` openTicketFile remove two self-assignments: .text 1396->1388 bytes; exported symbols; .text relocation targets; openTicketFile___Q33ipl4nand10SharedFileFv: 137 diffs, 180->178 instructions
- REVERT `src/system/iplNandMeta` readTicketBlock combine seek failures in a structured read guard: .text 1560->1552 bytes; exported symbols; .text relocation targets; readTicketBlock___Q33ipl4nand8MetaFileFPvii: 38 diffs, 58->56 instructions
- KEEP `src/system/iplNigaoeManager` constructor name the MAC-byte text buffer: allocated sections, exported symbols and resolved relocations identical.
- KEEP `src/system/iplControllerManager` read put the zero-read branch first to preserve count/null block order: allocated sections, exported symbols and resolved relocations identical.
- KEEP `src/system/iplNandMeta` readTicketBlock move shared failure label outside the read condition: allocated sections, exported symbols and resolved relocations identical.
- KEEP `src/system/iplNandShared` openTicketFile name ticket/error locals and document required self-copies: allocated sections, exported symbols and resolved relocations identical.
- REVERT `src/system/iplControllerManager` read replace remaining probe dispatch with short-circuit range guards: .text 1632->1636 bytes; exported symbols; .text relocation targets; read__Q33ipl10controller7ManagerFv: 155 diffs, 190->191 instructions
- KEEP `src/system/iplControllerManager` remove unused register-helper declarations and explain retained probe dispatch: allocated sections, exported symbols and resolved relocations identical.
- KEEP `src/system/iplTVRCManager` explain retained settings return block and remove stale notes: allocated sections, exported symbols and resolved relocations identical.

## Retained cleanup and compiler requirements

- odh.cpp: removed 17 decoder error gotos and its label. Kept the compressor's ordinary shared return.
- iplDialogWindow.cpp: separated the button lookup from its comma condition while preserving the page-fade short circuit.
- iplNwc24Manager.cpp: replaced the jump into the retry loop with while (!open()), named retryCount, and named the received-message/cleanup labels. Kept ordinary shared message cleanup exits.
- iplPlayTimeLog.cpp: removed stale matching notes and documented the required volatile reads. Plain reads add 16 bytes of attachment constants; declaration-level volatility moves zero constants into .sbss2 and changes code.
- iplTVRCManager.cpp: removed the update exit goto and switch-entry goto through ordinary fallthrough. Kept the settings open-error entry with a compiler note. Direct return removes one instruction; a structured open-success branch changes two instructions.
- iplControllerManager.cpp: removed two empty-read gotos and one label, plus eight unused register-helper declarations. Kept probe dispatch with a compiler note; fully structured guards add one or eight instructions. Putting the zero-read branch first is exact.
- iplNandMeta.cpp: moved the read failure label out of the conditional block and used an early successful return. Kept the shared seek-error exit; merging its two seek checks removes two instructions.
- iplNandShared.cpp: named ticket list/count/index, content descriptor/index and error stage/code. Kept two self-copies with a compiler note; removal drops two instructions. Kept the idiomatic shared error report.
- iplNigaoeManager.cpp: renamed temp to macByteText where two hexadecimal digits become a MAC byte.

Largest-first inventory covered all owned sources. There are no remaining owned decompiler local/var/temp placeholder declarations. Remaining unk_0x names are declarations in excluded headers or SDK headers, so no field role was guessed. ChannelManager and Scroller pragmas and utility runtime-type exit retain prior cleanup-c2 evidence. Other owned files contain ordinary loops/call arguments or common cleanup exits, not condition comma operators.

All nine changed object images equal the saved baseline in every allocated section byte, size, alignment, exported symbol and resolved relocation. Pools are identical against retail objects. The 12 affected/reviewed functions have identical instruction counts and ctxdiff diffs 0. Every changed unit's live objdiff code, data, functions, sections and link measures remain 100% before the final gate. git diff --check passed.

## Source commits

- ff2a2f70 cleanup: return directly from ODH buffer errors
- bfa11006 cleanup: separate dialog button lookup from condition
- a257fe26 cleanup: structure NWC24 retries and name cleanup paths
- bc6239c1 cleanup: explain retained play-log constant loads
- 40e8f604 cleanup: use TV remote switch fallthrough
- 06ebd40d cleanup: structure zero-read handling and remove unused declarations
- b18898b8 cleanup: move NAND metadata failure label to common exit
- a5ea226e cleanup: name shared NAND ticket and error locals
- fa0522a3 cleanup: name MAC-byte text buffer

## Final gate

Ran gate.py once over all nine changed units with --quick, as required by cleanup-common.md. Full 43U build passed; zero regressions, forbidden-pattern additions or readability warnings. The DOL SHA1 remains 26116613f624061ba99c8d1a299aaa6efa85670d. The regenerated live report and linked DOL passed DECOMPLETE_OK; build/43U/ok is current.

| Unit | Exact functions before -> after | Code bytes | Data bytes | Sections and links |
| --- | --- | --- | --- | --- |
| src/system/iplControllerManager | 10/10 -> 10/10 | 1632/1632 | 320/320 | 100% |
| src/system/iplNandShared | 8/8 -> 8/8 | 1372/1372 | 136/136 | 100% |
| src/system/iplNandMeta | 13/13 -> 13/13 | 1536/1536 | 136/136 | 100% |
| src/system/iplNigaoeManager | 9/9 -> 9/9 | 1148/1148 | 24/24 | 100% |
| src/system/iplPlayTimeLog | 18/18 -> 18/18 | 4856/4856 | 388/388 | 100% |
| src/system/iplNwc24Manager | 53/53 -> 53/53 | 10252/10252 | 888/888 | 100% |
| src/system/iplDialogWindow | 67/67 -> 67/67 | 12984/12984 | 1548/1548 | 100% |
| src/system/odh | 28/28 -> 28/28 | 14684/14684 | 6360/6360 | 100% |
| src/system/iplTVRCManager | 13/13 -> 13/13 | 3484/3484 | 120/120 | 100% |

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/system/odh] pool: IDENTICAL
[src/system/odh] objdiff: code 14684/14684 data 6360/6360 functions 28/28 fuzzy 100.0000 linked code 14684
[src/system/odh] instruction-exact functions: 28/28
[src/system/odh]   section .data size 464 match 100.0
[src/system/odh]   section .rodata size 5856 match 100.0
[src/system/odh]   section .sdata2 size 40 match 100.0
[src/system/odh]   section .text size 14684 match 100.0
[src/system/odh] baseline: code 14684/14684 data 6360 functions 28 fuzzy 100.0000
[src/system/iplDialogWindow] pool: IDENTICAL
[src/system/iplDialogWindow] objdiff: code 12984/12984 data 1548/1548 functions 67/67 fuzzy 100.0000 linked code 12984
[src/system/iplDialogWindow] instruction-exact functions: 67/67
[src/system/iplDialogWindow]   section .ctors size 4 match 100.0
[src/system/iplDialogWindow]   section .data size 1376 match 100.0
[src/system/iplDialogWindow]   section .sbss size 16 match 100.0
[src/system/iplDialogWindow]   section .sdata size 104 match 100.0
[src/system/iplDialogWindow]   section .sdata2 size 48 match 100.0
[src/system/iplDialogWindow]   section .text size 12984 match 100.0
[src/system/iplDialogWindow] baseline: code 12984/12984 data 1548 functions 67 fuzzy 100.0000
[src/system/iplNwc24Manager] pool: IDENTICAL
[src/system/iplNwc24Manager] objdiff: code 10252/10252 data 888/888 functions 53/53 fuzzy 100.0000 linked code 10252
[src/system/iplNwc24Manager] instruction-exact functions: 53/53
[src/system/iplNwc24Manager]   section .bss size 256 match 100.0
[src/system/iplNwc24Manager]   section .data size 576 match 100.0
[src/system/iplNwc24Manager]   section .sdata size 16 match 100.0
[src/system/iplNwc24Manager]   section .sdata2 size 40 match 100.0
[src/system/iplNwc24Manager]   section .text size 10252 match 100.0
[src/system/iplNwc24Manager] baseline: code 10252/10252 data 888 functions 53 fuzzy 100.0000
[src/system/iplPlayTimeLog] pool: IDENTICAL
[src/system/iplPlayTimeLog] objdiff: code 4856/4856 data 388/388 functions 18/18 fuzzy 100.0000 linked code 4856
[src/system/iplPlayTimeLog] instruction-exact functions: 18/18
[src/system/iplPlayTimeLog]   section .bss size 208 match 100.0
[src/system/iplPlayTimeLog]   section .ctors size 4 match 100.0
[src/system/iplPlayTimeLog]   section .data size 88 match 100.0
[src/system/iplPlayTimeLog]   section .rodata size 24 match 100.0
[src/system/iplPlayTimeLog]   section .sdata size 24 match 100.0
[src/system/iplPlayTimeLog]   section .sdata2 size 40 match 100.0
[src/system/iplPlayTimeLog]   section .text size 4856 match 100.0
[src/system/iplPlayTimeLog] baseline: code 4856/4856 data 388 functions 18 fuzzy 100.0000
[src/system/iplTVRCManager] pool: IDENTICAL
[src/system/iplTVRCManager] objdiff: code 3484/3484 data 120/120 functions 13/13 fuzzy 100.0000 linked code 3484
[src/system/iplTVRCManager] instruction-exact functions: 13/13
[src/system/iplTVRCManager]   section .data size 112 match 100.0
[src/system/iplTVRCManager]   section .sbss size 8 match 100.0
[src/system/iplTVRCManager]   section .text size 3484 match 100.0
[src/system/iplTVRCManager] baseline: code 3484/3484 data 120 functions 13 fuzzy 100.0000
[src/system/iplControllerManager] pool: IDENTICAL
[src/system/iplControllerManager] objdiff: code 1632/1632 data 320/320 functions 10/10 fuzzy 100.0000 linked code 1632
[src/system/iplControllerManager] instruction-exact functions: 10/10
[src/system/iplControllerManager]   section .data size 280 match 100.0
[src/system/iplControllerManager]   section .sbss size 16 match 100.0
[src/system/iplControllerManager]   section .sdata2 size 24 match 100.0
[src/system/iplControllerManager]   section .text size 1632 match 100.0
[src/system/iplControllerManager] baseline: code 1632/1632 data 320 functions 10 fuzzy 100.0000
[src/system/iplNandMeta] pool: IDENTICAL
[src/system/iplNandMeta] objdiff: code 1536/1536 data 136/136 functions 13/13 fuzzy 100.0000 linked code 1536
[src/system/iplNandMeta] instruction-exact functions: 13/13
[src/system/iplNandMeta]   section .data size 128 match 100.0
[src/system/iplNandMeta]   section .sdata size 8 match 100.0
[src/system/iplNandMeta]   section .text size 1536 match 100.0
[src/system/iplNandMeta] baseline: code 1536/1536 data 136 functions 13 fuzzy 100.0000
[src/system/iplNandShared] pool: IDENTICAL
[src/system/iplNandShared] objdiff: code 1372/1372 data 136/136 functions 8/8 fuzzy 100.0000 linked code 1372
[src/system/iplNandShared] instruction-exact functions: 8/8
[src/system/iplNandShared]   section .data size 128 match 100.0
[src/system/iplNandShared]   section .sdata size 8 match 100.0
[src/system/iplNandShared]   section .text size 1372 match 100.0
[src/system/iplNandShared] baseline: code 1372/1372 data 136 functions 8 fuzzy 100.0000
[src/system/iplNigaoeManager] pool: IDENTICAL
[src/system/iplNigaoeManager] objdiff: code 1148/1148 data 24/24 functions 9/9 fuzzy 100.0000 linked code 1148
[src/system/iplNigaoeManager] instruction-exact functions: 9/9
[src/system/iplNigaoeManager]   section .data size 24 match 100.0
[src/system/iplNigaoeManager]   section .text size 1148 match 100.0
[src/system/iplNigaoeManager] baseline: code 1148/1148 data 24 functions 9 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 100.00000 -> 100.00000
global fuzzy_match_percent: 99.99989 -> 99.99989
global complete_code_percent: 100.00000 -> 100.00000
global matched_data_percent: 100.00000 -> 100.00000
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

While this worker ran, origin/main advanced to 164de9ceaf496d1e69294db53cbed45881d168e1. Before the documentation commit, the leaf is 9 ahead / 6 behind. The assigned baseline stays aed62d85; no fetch, rebase, merge, push, PR or cross-worktree edit was performed. Parent integration must validate against its current main. The pre-existing untracked rx67c.attempts.md remains unchanged.
