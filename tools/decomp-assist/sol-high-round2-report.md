# Matching round 2

Baseline: 7a6efe8a. Final code: 6eb8458d. No unit was changed to Matching.

| Unit | Instruction-exact functions | Fuzzy % | Exact code bytes | Exact data bytes |
|---|---:|---:|---:|---:|
| libs/RVL_SDK/src/fa/pf_dir | 34 -> 34/38 | 98.878790 -> 99.262856 | 11428 -> 11428/18976 | 8 -> 40/40 |
| libs/RevoEX/src/nwc24/NWC24Download | 16 -> 17/30 | 95.993600 -> 97.146930 | 3220 -> 3640/12496 | 80 -> 80/80 |
| src/keyboard/tiCellPhone | 79 -> 83/86 | 97.737650 -> 99.774020 | 10900 -> 12824/19028 | 4 -> 3860/3860 |

pf_dir gained exact data and improved fuzzy code, but its instruction-exact count remains 34/38. All three units have 100% data. Twenty functions remain below 100%.

## Remaining functions

PFDIR_GetSDD | 99.710144% | 69/69 instructions | ordering of two induction-pointer advances (2 instruction differences)
PFDIR_p_mkdir | 99.649470% | 562/562 instructions | register allocation and order of dot-entry constants (36 differences)
PFDIR_p_rename | 97.808000% | 628/625 instructions | current-directory traversal addressing and short-name return/rollback branches; 3 extra instructions
PFDIR_p_move | 96.973060% | 636/631 instructions | ancestry checks and long-name arithmetic/control flow; 5 extra instructions
NWC24InitDlTask | 98.923615% | 144/144 instructions | register allocation only (31 differences)
NWC24SetDlInterval | 99.897960% | 147/147 instructions | final task-ID register allocation only (3 differences)
NWC24IterateDlTask | 95.000000% | 78/79 instructions | loop-entry branch and increment scheduling; 1 instruction missing
NWC24IterateDlTaskEx | 97.931040% | 145/145 instructions | comparison operands, flag-store scheduling and registers
NWC24UpdateDlTask | 94.173910% | 247/253 instructions | retry/validation branches and saved-register frame; 6 instructions missing
NWC24AddDlTask | 97.552444% | 146/143 instructions | inlined initialization and validation branches; 3 extra instructions
NWC24GetDlTask | 99.728264% | 92/92 instructions | retained destination/task-ID registers only (5 differences)
NWC24PurgeOldestDlTask | 85.829544% | 171/176 instructions | iterator initialization, menu-task skip and deletion/error blocks; 5 instructions missing
NWC24ManageDlTaskListForMenu | 94.736840% | 151/152 instructions | read/delete result blocks and register lifetimes; 1 instruction missing
NWC24ExtendDlTaskList | 99.854010% | 137/137 instructions | final reload-result register only (4 differences)
NWC24iCheckDlHeaderConsistency | 98.773580% | 212/212 instructions | three prologue moves scheduled in a different order
NWC24iCreateDlTaskList | 99.624060% | 133/133 instructions | header-pointer register allocation only (10 differences)
AddTaskInternal | 93.578550% | 397/401 instructions | URL checks and free-slot/purge/update loop; 4 instructions missing
onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv | 99.670090% | 682/682 instructions | register allocation only (37 differences)
create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | 99.819820% | 333/333 instructions | register allocation only (11 differences)
init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv | 98.526120% | 536/536 instructions | register allocation only (155 differences)

## Attempt audit

Successful trials only; failed compiler trials are excluded. Distinct bodies were counted from the saved source for each logged trial after normalizing whitespace. The attempt log records each result.

PFDIR_GetSDD | 7 distinct successful source bodies
PFDIR_p_rename | 3 distinct successful source bodies
PFDIR_p_move | 3 distinct successful source bodies
PFDIR_p_mkdir | 10 distinct successful source bodies
NWC24SetDlInterval | 3 distinct successful source bodies
NWC24ExtendDlTaskList | 3 distinct successful source bodies
NWC24GetDlTask | 3 distinct successful source bodies
NWC24iCreateDlTaskList | 3 distinct successful source bodies
NWC24iCheckDlHeaderConsistency | 3 distinct successful source bodies
NWC24DeleteDlTask | 3 distinct successful source bodies
NWC24AddDlTask | 3 distinct successful source bodies
NWC24InitDlTask | 3 distinct successful source bodies
NWC24ManageDlTaskListForMenu | 3 distinct successful source bodies
AddTaskInternal | 3 distinct successful source bodies
NWC24UpdateDlTask | 3 distinct successful source bodies
NWC24IterateDlTaskEx | 3 distinct successful source bodies
NWC24PurgeOldestDlTask | 3 distinct successful source bodies
NWC24IterateDlTask | 6 distinct successful source bodies
onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv | 6 distinct successful source bodies
init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv | 3 distinct successful source bodies
doNumericWithDotMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb | 3 distinct successful source bodies
doNumericMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb | 3 distinct successful source bodies
create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | 10 distinct successful source bodies
changeInputMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFQ59textinput8keyboard13cellphonetype4Base9InputMode | 4 distinct successful source bodies
setSignWindowButton__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb | 3 distinct successful source bodies

## Files and commits

Changed: libs/RVL_SDK/src/fa/pf_dir.c; libs/RevoEX/src/nwc24/NWC24Download.c; src/keyboard/tiCellPhone.cpp; include/keyboard/tiCellPhone.h; include/keyboard/tiCellPhoneLayout.h; include/keyboard/tiKeyboard.h; tools/decomp-assist/sol-high-round2-attempts.md; this report.

6eb8458d complete keyboard data and refine remaining bodies
1669eba5 match keyboard vtables and command constants
18c13528 match keyboard pane literals and animation tables
c7b37722 refine download iterator control flow
9febc706 match download deletion and directory data

Header declaration ordering changes are guarded by TI_CELLPHONE_MATCH_LAYOUT, defined only in tiCellPhone.cpp. Every original conditional branch of the moved layout declaration is retained.

Command 32 writes the convert-space query result in tiInputForm.cpp:1104 before use. This is an output parameter.

Uncertainty: no known data mismatch remains. Equal instruction counts in the three keyboard bodies still leave register allocation differences; exact source forms are unresolved.

## Every gate block

### sol-high-round2-before-gate.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
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
[libs/RevoEX/src/nwc24/NWC24Download] baseline: code 3220/12496 data 80 functions 16 fuzzy 95.9936
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
[libs/RVL_SDK/src/fa/pf_dir] baseline: code 11428/18976 data 8 functions 34 fuzzy 98.8788
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
[src/keyboard/tiCellPhone] baseline: code 10900/19028 data 4 functions 79 fuzzy 97.7377
regressions vs baseline: 0
global matched_code_percent: 83.50505 -> 83.50505
global fuzzy_match_percent: 97.03687 -> 97.03687
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 89.93258 -> 89.93258
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-high-round2-pool-gate.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/fa/pf_dir] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_dir] objdiff: code 11428/18976 data 40/40 functions 34/38 fuzzy 98.8788 linked code 0
[libs/RVL_SDK/src/fa/pf_dir] instruction-exact functions: 34/38
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata size 32 match 100.0
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata2 size 8 match 100.0
[libs/RVL_SDK/src/fa/pf_dir]   section .text size 18976 match 98.87879
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_GetSDD 99.710144
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_mkdir 96.8879
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_rename 97.376
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_move 96.97306
[libs/RVL_SDK/src/fa/pf_dir] baseline: code 11428/18976 data 8 functions 34 fuzzy 98.8788
regressions vs baseline: 0
global matched_code_percent: 83.50505 -> 83.50505
global fuzzy_match_percent: 97.03687 -> 97.03687
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 89.93258 -> 89.93433
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-high-round2-first-full.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/fa/pf_dir] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_dir] objdiff: code 11428/18976 data 40/40 functions 34/38 fuzzy 98.8788 linked code 0
[libs/RVL_SDK/src/fa/pf_dir] instruction-exact functions: 34/38
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata size 32 match 100.0
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata2 size 8 match 100.0
[libs/RVL_SDK/src/fa/pf_dir]   section .text size 18976 match 98.87879
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_GetSDD 99.710144
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_mkdir 96.8879
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_rename 97.376
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_move 96.97306
[libs/RVL_SDK/src/fa/pf_dir] baseline: code 11428/18976 data 8 functions 34 fuzzy 98.8788
[libs/RevoEX/src/nwc24/NWC24Download] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Download] objdiff: code 3640/12496 data 80/80 functions 17/30 fuzzy 96.1690 linked code 0
[libs/RevoEX/src/nwc24/NWC24Download] instruction-exact functions: 17/30
[libs/RevoEX/src/nwc24/NWC24Download]   section .data size 56 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .text size 12496 match 96.169014
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24InitDlTask 98.923615
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24SetDlInterval 99.89796
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTask 83.96203
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTaskEx 90.68965
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24UpdateDlTask 90.992096
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24AddDlTask 97.552444
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24GetDlTask 99.728264
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24PurgeOldestDlTask 84.3125
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24ManageDlTaskListForMenu 94.335526
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24ExtendDlTaskList 99.85401
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCheckDlHeaderConsistency 98.77358
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCreateDlTaskList 99.62406
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: AddTaskInternal 93.57855
[libs/RevoEX/src/nwc24/NWC24Download] baseline: code 3220/12496 data 80 functions 16 fuzzy 95.9936
regressions vs baseline: 0
global matched_code_percent: 83.50505 -> 83.51907
global fuzzy_match_percent: 97.03687 -> 97.03761
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 89.93258 -> 89.93433
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-high-round2-nwc-full.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24Download] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Download] objdiff: code 3640/12496 data 80/80 functions 17/30 fuzzy 97.1373 linked code 0
[libs/RevoEX/src/nwc24/NWC24Download] instruction-exact functions: 17/30
[libs/RevoEX/src/nwc24/NWC24Download]   section .data size 56 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .text size 12496 match 97.13732
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24InitDlTask 98.923615
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24SetDlInterval 99.89796
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTask 94.620255
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTaskEx 97.93104
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24UpdateDlTask 94.17391
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24AddDlTask 97.552444
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24GetDlTask 99.728264
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24PurgeOldestDlTask 85.829544
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24ManageDlTaskListForMenu 94.73684
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24ExtendDlTaskList 99.85401
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCheckDlHeaderConsistency 98.77358
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCreateDlTaskList 99.62406
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: AddTaskInternal 93.57855
[libs/RevoEX/src/nwc24/NWC24Download] baseline: code 3220/12496 data 80 functions 16 fuzzy 95.9936
regressions vs baseline: 0
global matched_code_percent: 83.50505 -> 83.55567
global fuzzy_match_percent: 97.03687 -> 97.04997
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 89.93258 -> 90.00635
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-high-round2-keyboard-full.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/fa/pf_dir] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_dir] objdiff: code 11428/18976 data 40/40 functions 34/38 fuzzy 99.0601 linked code 0
[libs/RVL_SDK/src/fa/pf_dir] instruction-exact functions: 34/38
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata size 32 match 100.0
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata2 size 8 match 100.0
[libs/RVL_SDK/src/fa/pf_dir]   section .text size 18976 match 99.060074
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_GetSDD 99.710144
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_mkdir 97.93772
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_rename 97.808
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_move 96.97306
[libs/RVL_SDK/src/fa/pf_dir] baseline: code 11428/18976 data 8 functions 34 fuzzy 98.8788
[src/keyboard/tiCellPhone] pool: IDENTICAL
[src/keyboard/tiCellPhone] objdiff: code 12824/19028 data 1324/3860 functions 83/86 fuzzy 99.1997 linked code 0
[src/keyboard/tiCellPhone] instruction-exact functions: 83/86
[src/keyboard/tiCellPhone]   section .ctors size 4 match 100.0
[src/keyboard/tiCellPhone]   section .data size 2416 match 56.210873
[src/keyboard/tiCellPhone]   section .rodata size 1320 match 100.0
[src/keyboard/tiCellPhone]   section .sdata size 112 match None
[src/keyboard/tiCellPhone]   section .sdata2 size 8 match 55.555557
[src/keyboard/tiCellPhone]   section .text size 19028 match 99.19971
[src/keyboard/tiCellPhone]   below 100: onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv 96.8959
[src/keyboard/tiCellPhone]   below 100: create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator 97.297295
[src/keyboard/tiCellPhone]   below 100: init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv 98.52612
[src/keyboard/tiCellPhone] baseline: code 10900/19028 data 4 functions 79 fuzzy 97.7377
regressions vs baseline: 0
global matched_code_percent: 83.50505 -> 83.58331
global fuzzy_match_percent: 97.03687 -> 97.05209
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 89.93258 -> 90.00635
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-high-round2-resume-gate.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/fa/pf_dir] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_dir] objdiff: code 11428/18976 data 40/40 functions 34/38 fuzzy 99.0601 linked code 0
[libs/RVL_SDK/src/fa/pf_dir] instruction-exact functions: 34/38
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata size 32 match 100.0
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata2 size 8 match 100.0
[libs/RVL_SDK/src/fa/pf_dir]   section .text size 18976 match 99.060074
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_GetSDD 99.710144
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_mkdir 97.93772
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_rename 97.808
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_move 96.97306
[libs/RVL_SDK/src/fa/pf_dir] baseline: code 11428/18976 data 8 functions 34 fuzzy 98.8788
[libs/RevoEX/src/nwc24/NWC24Download] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Download] objdiff: code 3640/12496 data 80/80 functions 17/30 fuzzy 97.1373 linked code 0
[libs/RevoEX/src/nwc24/NWC24Download] instruction-exact functions: 17/30
[libs/RevoEX/src/nwc24/NWC24Download]   section .data size 56 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .text size 12496 match 97.13732
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24InitDlTask 98.923615
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24SetDlInterval 99.89796
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTask 94.620255
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTaskEx 97.93104
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24UpdateDlTask 94.17391
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24AddDlTask 97.552444
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24GetDlTask 99.728264
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24PurgeOldestDlTask 85.829544
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24ManageDlTaskListForMenu 94.73684
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24ExtendDlTaskList 99.85401
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCheckDlHeaderConsistency 98.77358
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCreateDlTaskList 99.62406
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: AddTaskInternal 93.57855
[libs/RevoEX/src/nwc24/NWC24Download] baseline: code 3220/12496 data 80 functions 16 fuzzy 95.9936
[src/keyboard/tiCellPhone] pool: IDENTICAL
[src/keyboard/tiCellPhone] objdiff: code 12824/19028 data 1332/3860 functions 83/86 fuzzy 99.1997 linked code 0
[src/keyboard/tiCellPhone] instruction-exact functions: 83/86
[src/keyboard/tiCellPhone]   section .ctors size 4 match 100.0
[src/keyboard/tiCellPhone]   section .data size 2416 match 56.49574
[src/keyboard/tiCellPhone]   section .rodata size 1320 match 100.0
[src/keyboard/tiCellPhone]   section .sdata size 112 match None
[src/keyboard/tiCellPhone]   section .sdata2 size 8 match 100.0
[src/keyboard/tiCellPhone]   section .text size 19028 match 99.19971
[src/keyboard/tiCellPhone]   below 100: onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv 96.8959
[src/keyboard/tiCellPhone]   below 100: create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator 97.297295
[src/keyboard/tiCellPhone]   below 100: init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv 98.52612
[src/keyboard/tiCellPhone] baseline: code 10900/19028 data 4 functions 79 fuzzy 97.7377
regressions vs baseline: 0
global matched_code_percent: 83.50505 -> 83.58331
global fuzzy_match_percent: 97.03687 -> 97.05209
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 89.93258 -> 90.00679
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-high-round2-data-full.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/keyboard/tiCellPhone] pool: IDENTICAL
[src/keyboard/tiCellPhone] objdiff: code 12824/19028 data 3748/3860 functions 83/86 fuzzy 99.5974 linked code 0
[src/keyboard/tiCellPhone] instruction-exact functions: 83/86
[src/keyboard/tiCellPhone]   section .ctors size 4 match 100.0
[src/keyboard/tiCellPhone]   section .data size 2416 match 100.0
[src/keyboard/tiCellPhone]   section .rodata size 1320 match 100.0
[src/keyboard/tiCellPhone]   section .sdata size 112 match None
[src/keyboard/tiCellPhone]   section .sdata2 size 8 match 100.0
[src/keyboard/tiCellPhone]   section .text size 19028 match 99.597435
[src/keyboard/tiCellPhone]   below 100: onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv 99.67009
[src/keyboard/tiCellPhone]   below 100: create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator 97.297295
[src/keyboard/tiCellPhone]   below 100: init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv 98.52612
[src/keyboard/tiCellPhone] baseline: code 10900/19028 data 4 functions 79 fuzzy 97.7377
regressions vs baseline: 0
global matched_code_percent: 83.50505 -> 83.58331
global fuzzy_match_percent: 97.03687 -> 97.05460
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 89.93258 -> 90.13861
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-high-round2-final-full.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/fa/pf_dir] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_dir] objdiff: code 11428/18976 data 40/40 functions 34/38 fuzzy 99.2629 linked code 0
[libs/RVL_SDK/src/fa/pf_dir] instruction-exact functions: 34/38
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata size 32 match 100.0
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata2 size 8 match 100.0
[libs/RVL_SDK/src/fa/pf_dir]   section .text size 18976 match 99.262856
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_GetSDD 99.710144
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_mkdir 99.64947
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_rename 97.808
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_move 96.97306
[libs/RVL_SDK/src/fa/pf_dir] baseline: code 11428/18976 data 8 functions 34 fuzzy 98.8788
[libs/RevoEX/src/nwc24/NWC24Download] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Download] objdiff: code 3640/12496 data 80/80 functions 17/30 fuzzy 97.1373 linked code 0
[libs/RevoEX/src/nwc24/NWC24Download] instruction-exact functions: 17/30
[libs/RevoEX/src/nwc24/NWC24Download]   section .data size 56 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .text size 12496 match 97.13732
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24InitDlTask 98.923615
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24SetDlInterval 99.89796
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTask 94.620255
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTaskEx 97.93104
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24UpdateDlTask 94.17391
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24AddDlTask 97.552444
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24GetDlTask 99.728264
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24PurgeOldestDlTask 85.829544
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24ManageDlTaskListForMenu 94.73684
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24ExtendDlTaskList 99.85401
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCheckDlHeaderConsistency 98.77358
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCreateDlTaskList 99.62406
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: AddTaskInternal 93.57855
[libs/RevoEX/src/nwc24/NWC24Download] baseline: code 3220/12496 data 80 functions 16 fuzzy 95.9936
[src/keyboard/tiCellPhone] pool: IDENTICAL
[src/keyboard/tiCellPhone] objdiff: code 12824/19028 data 3748/3860 functions 83/86 fuzzy 99.7740 linked code 0
[src/keyboard/tiCellPhone] instruction-exact functions: 83/86
[src/keyboard/tiCellPhone]   section .ctors size 4 match 100.0
[src/keyboard/tiCellPhone]   section .data size 2416 match 100.0
[src/keyboard/tiCellPhone]   section .rodata size 1320 match 100.0
[src/keyboard/tiCellPhone]   section .sdata size 112 match None
[src/keyboard/tiCellPhone]   section .sdata2 size 8 match 100.0
[src/keyboard/tiCellPhone]   section .text size 19028 match 99.77402
[src/keyboard/tiCellPhone]   below 100: onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv 99.67009
[src/keyboard/tiCellPhone]   below 100: create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator 99.81982
[src/keyboard/tiCellPhone]   below 100: init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv 98.52612
[src/keyboard/tiCellPhone] baseline: code 10900/19028 data 4 functions 79 fuzzy 97.7377
regressions vs baseline: 0
global matched_code_percent: 83.50505 -> 83.58331
global fuzzy_match_percent: 97.03687 -> 97.05702
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 89.93258 -> 90.13861
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-high-round2-final-data-full.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/fa/pf_dir] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_dir] objdiff: code 11428/18976 data 40/40 functions 34/38 fuzzy 99.2629 linked code 0
[libs/RVL_SDK/src/fa/pf_dir] instruction-exact functions: 34/38
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata size 32 match 100.0
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata2 size 8 match 100.0
[libs/RVL_SDK/src/fa/pf_dir]   section .text size 18976 match 99.262856
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_GetSDD 99.710144
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_mkdir 99.64947
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_rename 97.808
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_move 96.97306
[libs/RVL_SDK/src/fa/pf_dir] baseline: code 11428/18976 data 8 functions 34 fuzzy 98.8788
[libs/RevoEX/src/nwc24/NWC24Download] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Download] objdiff: code 3640/12496 data 80/80 functions 17/30 fuzzy 97.1373 linked code 0
[libs/RevoEX/src/nwc24/NWC24Download] instruction-exact functions: 17/30
[libs/RevoEX/src/nwc24/NWC24Download]   section .data size 56 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .text size 12496 match 97.13732
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24InitDlTask 98.923615
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24SetDlInterval 99.89796
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTask 94.620255
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTaskEx 97.93104
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24UpdateDlTask 94.17391
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24AddDlTask 97.552444
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24GetDlTask 99.728264
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24PurgeOldestDlTask 85.829544
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24ManageDlTaskListForMenu 94.73684
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24ExtendDlTaskList 99.85401
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCheckDlHeaderConsistency 98.77358
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCreateDlTaskList 99.62406
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: AddTaskInternal 93.57855
[libs/RevoEX/src/nwc24/NWC24Download] baseline: code 3220/12496 data 80 functions 16 fuzzy 95.9936
[src/keyboard/tiCellPhone] pool: IDENTICAL
[src/keyboard/tiCellPhone] objdiff: code 12824/19028 data 3860/3860 functions 83/86 fuzzy 99.7740 linked code 0
[src/keyboard/tiCellPhone] instruction-exact functions: 83/86
[src/keyboard/tiCellPhone]   section .ctors size 4 match 100.0
[src/keyboard/tiCellPhone]   section .data size 2416 match 100.0
[src/keyboard/tiCellPhone]   section .rodata size 1320 match 100.0
[src/keyboard/tiCellPhone]   section .sdata size 112 match 100.0
[src/keyboard/tiCellPhone]   section .sdata2 size 8 match 100.0
[src/keyboard/tiCellPhone]   section .text size 19028 match 99.77402
[src/keyboard/tiCellPhone]   below 100: onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv 99.67009
[src/keyboard/tiCellPhone]   below 100: create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator 99.81982
[src/keyboard/tiCellPhone]   below 100: init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv 98.52612
[src/keyboard/tiCellPhone] baseline: code 10900/19028 data 4 functions 79 fuzzy 97.7377
regressions vs baseline: 0
global matched_code_percent: 83.50505 -> 83.58331
global fuzzy_match_percent: 97.03687 -> 97.05702
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 89.93258 -> 90.14473
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-high-round2-final-gate.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/fa/pf_dir] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_dir] objdiff: code 11428/18976 data 40/40 functions 34/38 fuzzy 99.2629 linked code 0
[libs/RVL_SDK/src/fa/pf_dir] instruction-exact functions: 34/38
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata size 32 match 100.0
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata2 size 8 match 100.0
[libs/RVL_SDK/src/fa/pf_dir]   section .text size 18976 match 99.262856
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_GetSDD 99.710144
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_mkdir 99.64947
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_rename 97.808
[libs/RVL_SDK/src/fa/pf_dir]   below 100: PFDIR_p_move 96.97306
[libs/RVL_SDK/src/fa/pf_dir] baseline: code 11428/18976 data 8 functions 34 fuzzy 98.8788
[libs/RevoEX/src/nwc24/NWC24Download] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Download] objdiff: code 3640/12496 data 80/80 functions 17/30 fuzzy 97.1469 linked code 0
[libs/RevoEX/src/nwc24/NWC24Download] instruction-exact functions: 17/30
[libs/RevoEX/src/nwc24/NWC24Download]   section .data size 56 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .text size 12496 match 97.14693
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24InitDlTask 98.923615
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24SetDlInterval 99.89796
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTask 95.0
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTaskEx 97.93104
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24UpdateDlTask 94.17391
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24AddDlTask 97.552444
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24GetDlTask 99.728264
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24PurgeOldestDlTask 85.829544
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24ManageDlTaskListForMenu 94.73684
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24ExtendDlTaskList 99.85401
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCheckDlHeaderConsistency 98.77358
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCreateDlTaskList 99.62406
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: AddTaskInternal 93.57855
[libs/RevoEX/src/nwc24/NWC24Download] baseline: code 3220/12496 data 80 functions 16 fuzzy 95.9936
[src/keyboard/tiCellPhone] pool: IDENTICAL
[src/keyboard/tiCellPhone] objdiff: code 12824/19028 data 3860/3860 functions 83/86 fuzzy 99.7740 linked code 0
[src/keyboard/tiCellPhone] instruction-exact functions: 83/86
[src/keyboard/tiCellPhone]   section .ctors size 4 match 100.0
[src/keyboard/tiCellPhone]   section .data size 2416 match 100.0
[src/keyboard/tiCellPhone]   section .rodata size 1320 match 100.0
[src/keyboard/tiCellPhone]   section .sdata size 112 match 100.0
[src/keyboard/tiCellPhone]   section .sdata2 size 8 match 100.0
[src/keyboard/tiCellPhone]   section .text size 19028 match 99.77402
[src/keyboard/tiCellPhone]   below 100: onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv 99.67009
[src/keyboard/tiCellPhone]   below 100: create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator 99.81982
[src/keyboard/tiCellPhone]   below 100: init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv 98.52612
[src/keyboard/tiCellPhone] baseline: code 10900/19028 data 4 functions 79 fuzzy 97.7377
regressions vs baseline: 0
global matched_code_percent: 83.50505 -> 83.58331
global fuzzy_match_percent: 97.03687 -> 97.05706
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 89.93258 -> 90.14473
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

