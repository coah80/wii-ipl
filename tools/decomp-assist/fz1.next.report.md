# Fuzzy lane continuation

Baseline: `711ee737f98c1febb2e3d9580bec9be423fd3b19`. Four new exact functions; AxAdpcmPlayer was already matched and linked after origin/main #774.

| Unit | Instruction-exact before → after | Objdiff functions before → after | Code bytes before → after / total | Data bytes before → after / total |
| --- | --- | --- | --- | --- |
| `libs/RVL_SDK/src/fa/api/FAAttach` | 0/1 → 0/1 | 0/1 → 0/1 | 0 → 0 / 500 | 240 → 240 / 240 |
| `src/bannerSound/AxAdpcmPlayer` | 12/13 → 12/13 | 13/13 → 13/13 | 3088 → 3088 / 3088 | 6476 → 6476 / 6476 |
| `libs/RVLMiddleware/eZiText/src/clib/zkokeyp` | 1/7 → 1/7 | 1/7 → 1/7 | 332 → 332 / 5200 | 96 → 96 / 180 |
| `src/scene/board/iplFocusObject` | 88/89 → 89/89 | 88/89 → 89/89 | 19772 → 20332 / 20332 | 2576 → 2576 / 2576 |
| `src/system/iplKeyboard` | 31/32 → 31/32 | 31/32 → 31/32 | 4752 → 4752 / 6024 | 1184 → 1184 / 1184 |
| `libs/RVL_SDK/src/fa/pf_dir` | 35/38 → 38/38 | 35/38 → 38/38 | 11704 → 18976 / 18976 | 40 → 40 / 40 |

Instruction-exact counts above reproduce the gate. Ax reports 12/13 there despite objdiff 13/13; the existing CR1 branch-disassembly normalization issue is independently proven: `checkFile__19AxAdpcmSimplePlayerFPvUl` has all 372 encoded function bytes identical, while odiff displays two different CR1 branch targets. It contributes no new gain.

## Remaining functions

- `FAAttach` 99.36% — 125/125 instructions; ten index/scaled-index/table-base register differences. 3 distinct compiled source forms; attempts lines 3166–3168.
- `Zi8_8148302C` 99.49152% — 59/59 instructions; six work-pointer/value register differences. 4 distinct compiled source forms; attempts lines 3173–3176.
- `Zi8_81483264` 98.902435% — 41/41 instructions; eight metadata/index register differences. 9 distinct compiled source forms; attempts lines 3180–3190.
- `Zi8_81483308` 99.13793% — 58/58 instructions; nine count-pointer/index register differences. 7 distinct compiled source forms; attempts lines 3194–3200.
- `Zi8_814833F0` 99.04256% — 47/47 instructions; eight key/index register differences. 5 distinct compiled source forms; attempts lines 3205–3209.
- `Zi8_814834AC` 99.3586% — 344/343 instructions; extra narrowing in initialized-byte chain, operand scheduling and register differences. 21 distinct compiled source forms; attempts lines 3213–3235.
- `Zi8GetKOcandidates` 97.96712% — 673/669 instructions; extra zero load, helper-return narrowing, final postincrement copy, addressing/condition scheduling. 14 distinct compiled source forms; attempts lines 3241–3257.
- `create__Q33ipl8keyboard7ManagerFPQ33ipl4nand4FilePQ23EGG4Heap` 94.00944% — 318/318 instructions; allocation-result moves across null constructors, dictionary index scheduling and MemoSetting stack-temporary order. 24 distinct compiled source forms; attempts lines 3293–3318.

## Matched functions and source review

`focus_object::cmn_calc`: added a real VEC3 sum and result temporary, with reciprocal evaluation inside normalization; frame 0x60 → 0x70, 140/140 instructions, zero differences.
`PFDIR_p_move`: corrected the six-argument entry-search prototype, used the matching table entry as the current-directory base, moved the actual cluster read inside that helper, separated LFN traversal lifetimes; 631/631 instructions, zero differences.
`PFDIR_p_rename`: shared the typed filename cursor and separated the file, retreat and remaining-LFN counters; corrected error-return branches and count mask; 625/625 instructions, zero differences.
`PFDIR_p_mkdir`: ordinary 11-byte short-name loop and full real scalar declaration order, preserving addressable local order; 562/562 instructions, zero differences.

## Data proof

FAAttach 240/240, Ax 6476/6476, focus 2576/2576, keyboard 1184/1184, PF 40/40 already have all data matched. No config/symbol rename or extent edit was justified.
zkokeyp .data 40-byte ten-entry switch table is byte-identical and each relocation names the exact Zi8_81483118 at the same offset/addend. extab 56 bytes match. extabindex 84 bytes differ only at length words offset64 (1376 versus1372 for Zi8_814834AC) and offset76 (2692 versus2676 for Zi8GetKOcandidates). Exception relocations resolve to identical extab offsets0,8,16,24,32,40,48; anonymous compiler symbol names differ as expected. The candidate function begins four bytes later in our .text because the previous function has an extra instruction. The remaining data differences follow these two code lengths.

## Files and local commits

- `libs/RVL_SDK/src/fa/pf_dir.c`
- `src/scene/board/iplFocusObject.cpp`
- `tools/decomp-assist/fz1.attempts.md`
- `tools/decomp-assist/fz1.next.final-gate.txt`
- `tools/decomp-assist/fz1.next.report.md`

- d4976af8 match focus vector interpolation
- 0035e899 match directory move and correct entry prototype
- d5de7189 match directory rename traversal
- 9170cd3e match directory creation locals

The final evidence commit is identified in the final reply. Matching phase only; the gate retains the existing linked status.

## Final clean gate, verbatim

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/fa/api/FAAttach] pool: IDENTICAL
[libs/RVL_SDK/src/fa/api/FAAttach] objdiff: code None/500 data 240/240 functions 0/1 fuzzy 99.3600 linked code 0
[libs/RVL_SDK/src/fa/api/FAAttach] instruction-exact functions: 0/1
[libs/RVL_SDK/src/fa/api/FAAttach]   section .bss size 208 match 100.0
[libs/RVL_SDK/src/fa/api/FAAttach]   section .data size 24 match 100.0
[libs/RVL_SDK/src/fa/api/FAAttach]   section .sdata size 8 match 100.0
[libs/RVL_SDK/src/fa/api/FAAttach]   section .text size 500 match 99.36
[libs/RVL_SDK/src/fa/api/FAAttach]   below 100: FAAttach 99.36
[libs/RVL_SDK/src/fa/api/FAAttach] baseline: code None/500 data 240 functions 0 fuzzy 99.3600
[src/bannerSound/AxAdpcmPlayer] pool: IDENTICAL
[src/bannerSound/AxAdpcmPlayer] objdiff: code 3088/3088 data 6476/6476 functions 13/13 fuzzy 100.0000 linked code 3088
[src/bannerSound/AxAdpcmPlayer] instruction-exact functions: 12/13
[src/bannerSound/AxAdpcmPlayer]   section .bss size 6400 match 100.0
[src/bannerSound/AxAdpcmPlayer]   section .ctors size 4 match 100.0
[src/bannerSound/AxAdpcmPlayer]   section .data size 32 match 100.0
[src/bannerSound/AxAdpcmPlayer]   section .sbss size 16 match 100.0
[src/bannerSound/AxAdpcmPlayer]   section .sdata size 8 match 100.0
[src/bannerSound/AxAdpcmPlayer]   section .sdata2 size 16 match 100.0
[src/bannerSound/AxAdpcmPlayer]   section .text size 3088 match 100.0
[src/bannerSound/AxAdpcmPlayer] baseline: code 3088/3088 data 6476 functions 13 fuzzy 100.0000
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp] objdiff: code 332/5200 data 96/180 functions 1/7 fuzzy 98.6539 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp] instruction-exact functions: 1/7
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   section .data size 40 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   section .text size 5200 match 98.65385
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   section extab size 56 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   section extabindex size 84 match 97.61904
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   below 100: Zi8_8148302C 99.49152
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   below 100: Zi8_81483264 98.902435
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   below 100: Zi8_81483308 99.13793
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   below 100: Zi8_814833F0 99.04256
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   below 100: Zi8_814834AC 99.3586
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   below 100: Zi8GetKOcandidates 97.96712
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp] baseline: code 332/5200 data 96 functions 1 fuzzy 98.6539
[src/scene/board/iplFocusObject] pool: IDENTICAL
[src/scene/board/iplFocusObject] objdiff: code 20332/20332 data 2576/2576 functions 89/89 fuzzy 100.0000 linked code 0
[src/scene/board/iplFocusObject] instruction-exact functions: 89/89
[src/scene/board/iplFocusObject]   section .data size 2168 match 100.0
[src/scene/board/iplFocusObject]   section .rodata size 176 match 100.0
[src/scene/board/iplFocusObject]   section .sdata size 176 match 100.0
[src/scene/board/iplFocusObject]   section .sdata2 size 56 match 100.0
[src/scene/board/iplFocusObject]   section .text size 20332 match 100.0
[src/scene/board/iplFocusObject] baseline: code 19772/20332 data 2576 functions 88 fuzzy 99.6471
[src/system/iplKeyboard] pool: IDENTICAL
[src/system/iplKeyboard] objdiff: code 4752/6024 data 1184/1184 functions 31/32 fuzzy 98.7351 linked code 0
[src/system/iplKeyboard] instruction-exact functions: 31/32
[src/system/iplKeyboard]   section .data size 1168 match 100.0
[src/system/iplKeyboard]   section .sdata size 8 match 100.0
[src/system/iplKeyboard]   section .sdata2 size 8 match 100.0
[src/system/iplKeyboard]   section .text size 6024 match 98.73506
[src/system/iplKeyboard]   below 100: create__Q33ipl8keyboard7ManagerFPQ33ipl4nand4FilePQ23EGG4Heap 94.00944
[src/system/iplKeyboard] baseline: code 4752/6024 data 1184 functions 31 fuzzy 98.7351
[libs/RVL_SDK/src/fa/pf_dir] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_dir] objdiff: code 18976/18976 data 40/40 functions 38/38 fuzzy 100.0000 linked code 0
[libs/RVL_SDK/src/fa/pf_dir] instruction-exact functions: 38/38
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata size 32 match 100.0
[libs/RVL_SDK/src/fa/pf_dir]   section .sdata2 size 8 match 100.0
[libs/RVL_SDK/src/fa/pf_dir]   section .text size 18976 match 100.0
[libs/RVL_SDK/src/fa/pf_dir] baseline: code 11704/18976 data 40 functions 35 fuzzy 99.5432
regressions vs baseline: 0
global matched_code_percent: 88.93407 -> 89.19556
global fuzzy_match_percent: 99.50078 -> 99.50607
global complete_code_percent: 65.19670 -> 65.19670
global matched_data_percent: 99.07044 -> 99.07044
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
