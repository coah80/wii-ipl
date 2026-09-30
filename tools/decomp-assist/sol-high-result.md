# Matching result

Final full gate: all three units, fresh 43U rebuild; pools identical; zero regressions, forbidden additions and readability warnings. DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`.

| Unit | Instruction-exact functions | Fuzzy | Exact code bytes | Exact data bytes |
| --- | --- | --- | --- | --- |
| libs/RVL_SDK/src/fa/pf_dir | 30/38 -> 34/38 | 67.96859% -> 98.87879% | 8024 -> 11428 / 18976 | 0 -> 8 / 40 |
| libs/RevoEX/src/nwc24/NWC24Download | 13/30 -> 16/30 | 83.35883% -> 95.99360% | 2020 -> 3220 / 12496 | 80 -> 80 / 80 |
| src/keyboard/tiCellPhone | 72/86 -> 79/86 | 86.62876% -> 97.73765% | 7488 -> 10900 / 19028 | 4 -> 4 / 3860 |

## Remaining functions

Instruction counts below are source/target. Every initially nonexact function has at least three distinct logged source attempts; failed compilations are additional evidence, not counted toward the minimum. Explanations identify the surviving diff area; they do not establish a compiler tie-break.

### libs/RVL_SDK/src/fa/pf_dir

- `PFDIR_GetSDD`: 99.710144%; 69/69 instructions; load scheduling.
- `PFDIR_p_mkdir`: 96.887900%; 571/562 instructions; allocation and directory-write block scheduling.
- `PFDIR_p_rename`: 97.376000%; 626/625 instructions; retained path and directory temporaries.
- `PFDIR_p_move`: 96.973060%; 636/631 instructions; directory traversal and write block scheduling.

### libs/RevoEX/src/nwc24/NWC24Download

- `NWC24InitDlTask`: 96.541664%; 143/144 instructions; validation and default-field store scheduling.
- `NWC24SetDlInterval`: 99.897960%; 147/147 instructions; temporary register allocation.
- `NWC24IterateDlTask`: 83.962030%; 74/79 instructions; loop termination and callback-result scheduling.
- `NWC24IterateDlTaskEx`: 90.689650%; 144/145 instructions; inlined read-loop and callback-result scheduling.
- `NWC24UpdateDlTask`: 90.992096%; 247/253 instructions; retry-validation and timestamp block scheduling.
- `NWC24DeleteDlTask`: 98.047620%; 107/105 instructions; validation and deletion block scheduling.
- `NWC24AddDlTask`: 97.552444%; 146/143 instructions; validation and slot-search block scheduling.
- `NWC24GetDlTask`: 99.728264%; 92/92 instructions; parameter register allocation.
- `NWC24PurgeOldestDlTask`: 84.312500%; 167/176 instructions; slot-scan and inlined deletion blocks.
- `NWC24ManageDlTaskListForMenu`: 94.335526%; 149/152 instructions; menu-limit and task-deletion blocks.
- `NWC24ExtendDlTaskList`: 99.854010%; 137/137 instructions; reload-result register allocation.
- `NWC24iCheckDlHeaderConsistency`: 98.773580%; 212/212 instructions; prologue move scheduling.
- `NWC24iCreateDlTaskList`: 99.624060%; 133/133 instructions; header-pointer register allocation.
- `AddTaskInternal`: 93.578550%; 397/401 instructions; slot search and timestamp-update blocks.

### src/keyboard/tiCellPhone

- `onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv`: 96.895900%; 681/682 instructions; key lookup, command-payload and register scheduling.
- `create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator`: 92.228226%; 337/333 instructions; descriptor address setup and constructor scheduling.
- `init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv`: 96.468285%; 544/536 instructions; pane address setup, key-set reload and virtual-call scheduling.
- `changeInputMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFQ59textinput8keyboard13cellphonetype4Base9InputMode`: 90.062805%; 216/207 instructions; mode-branch and pane-address scheduling.
- `doNumericMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb`: 93.923080%; 173/169 instructions; pane-address and shared visibility-value scheduling.
- `doNumericWithDotMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb`: 95.000000%; 36/35 instructions; extra pane-address calculation.
- `setSignWindowButton__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb`: 87.071430%; 70/70 instructions; regional pane-address setup and scheduling.

## Validation

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/fa/pf_dir] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_dir] objdiff: code 11428/18976 data 8/40 functions 34/38 fuzzy 98.8788 linked code 0
[libs/RVL_SDK/src/fa/pf_dir] instruction-exact functions: 34/38
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata size 32 match 92.85714
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata2 size 8 match 100.0
[libs/RVL_SDK/src/fa/pf_dir]   section .text size 18976 match 98.87879
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_GetSDD 99.710144
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_mkdir 96.8879
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_rename 97.376
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_move 96.97306
[libs/RVL_SDK/src/fa/pf_dir] baseline: code 8024/18976 data None functions 30 fuzzy 67.9686
[libs/RevoEX/src/nwc24/NWC24Download] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Download] objdiff: code 3220/12496 data 80/80 functions 16/30 fuzzy 95.9936 linked code 0
[libs/RevoEX/src/nwc24/NWC24Download] instruction-exact functions: 16/30
[libs/RevoEX/src/nwc24/NWC24Download]   section .data size 56 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .text size 12496 match 95.9936
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24InitDlTask 96.541664
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24SetDlInterval 99.89796
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTask 83.96203
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTaskEx 90.68965
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24UpdateDlTask 90.992096
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24DeleteDlTask 98.04762
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24AddDlTask 97.552444
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24GetDlTask 99.728264
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24PurgeOldestDlTask 84.3125
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24ManageDlTaskListForMenu 94.335526
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24ExtendDlTaskList 99.85401
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCheckDlHeaderConsistency 98.77358
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCreateDlTaskList 99.62406
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: AddTaskInternal 93.57855
[libs/RevoEX/src/nwc24/NWC24Download] baseline: code 2020/12496 data 80 functions 13 fuzzy 83.3588
[src/keyboard/tiCellPhone] pool: IDENTICAL
[src/keyboard/tiCellPhone] objdiff: code 10900/19028 data 4/3860 functions 79/86 fuzzy 97.7377 linked code 0
[src/keyboard/tiCellPhone] instruction-exact functions: 79/86
[src/keyboard/tiCellPhone]   section .ctors size 4 match 100.0
[src/keyboard/tiCellPhone]   section .data size 2416 match 56.210873
[src/keyboard/tiCellPhone]   section .rodata size 1320 match 99.69697
[src/keyboard/tiCellPhone]   section .sdata size 112 match None
[src/keyboard/tiCellPhone]   section .sdata2 size 8 match 55.555557
[src/keyboard/tiCellPhone]   section .text size 19028 match 97.73765
[src/keyboard/tiCellPhone]   below 100: onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv 96.8959
[src/keyboard/tiCellPhone]   below 100: create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator 92.228226
[src/keyboard/tiCellPhone]   below 100: init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv 96.468285
[src/keyboard/tiCellPhone]   below 100: changeInputMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFQ59textinput8keyboard13cellphonetype4Base9InputMode 90.062805
[src/keyboard/tiCellPhone]   below 100: doNumericMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb 93.92308
[src/keyboard/tiCellPhone]   below 100: doNumericWithDotMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb 95.0
[src/keyboard/tiCellPhone]   below 100: setSignWindowButton__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb 87.07143
[src/keyboard/tiCellPhone] baseline: code 7488/19028 data 4 functions 72 fuzzy 86.6288
regressions vs baseline: 0
global matched_code_percent: 83.03911 -> 83.30673
global fuzzy_match_percent: 96.63766 -> 96.95678
global complete_code_percent: 58.19218 -> 58.19218
global matched_data_percent: 89.88587 -> 89.88631
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## Files and commits

- `libs/RVL_SDK/src/fa/pf_dir.c`: `26c329e5`, `f7cce6f6`.
- `libs/RevoEX/src/nwc24/NWC24Download.c`: `59a7118e`.
- `src/keyboard/tiCellPhone.cpp`, `include/keyboard/tiCellPhone.h`, `include/keyboard/tiCpData.h`, `include/keyboard/tiHKBManager.h`: `965687ab`.
- `tools/decomp-assist/sol-high-attempts.md`: source attempts and their measurements.

## Limits

25 functions and partial pf_dir/tiCellPhone data remain unmatched. No unit was switched to Matching. Linking was left for the later phase. The residual data differences were not proven to be only linker-deduplicated weak data; the matching-only result does not claim complete units.
