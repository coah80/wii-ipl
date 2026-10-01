# Structural round 12 final report

Matching-only pass in the current worktree. No linking configuration, symbols, assembly, shared-header changes, remote operations or other worktrees were retained.

## Final full gate

Command:

```text
python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py libs/RevoEX/src/nwc24/NWC24Download libs/RVL_SDK/src/nup/nup src/scene/setting/iplSetting
```

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24Download] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Download] objdiff: code 8140/12496 data 80/80 functions 25/30 fuzzy 99.1521 linked code 0
[libs/RevoEX/src/nwc24/NWC24Download] instruction-exact functions: 25/30
[libs/RevoEX/src/nwc24/NWC24Download]   section .data size 56 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .text size 12496 match 99.15205
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24InitDlTask 98.923615
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTask 99.303795
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24UpdateDlTask 95.00395
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCheckDlHeaderConsistency 98.77358
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: AddTaskInternal 97.7182
[libs/RevoEX/src/nwc24/NWC24Download] baseline: code 6828/12496 data 80 functions 23 fuzzy 98.2676
[libs/RVL_SDK/src/nup/nup] pool: IDENTICAL
[libs/RVL_SDK/src/nup/nup] objdiff: code 7496/10764 data 1720/1720 functions 19/23 fuzzy 93.4430 linked code 0
[libs/RVL_SDK/src/nup/nup] instruction-exact functions: 19/23
[libs/RVL_SDK/src/nup/nup]   section .data size 1592 match 100.0
[libs/RVL_SDK/src/nup/nup]   section .rodata size 88 match 100.0
[libs/RVL_SDK/src/nup/nup]   section .sbss size 8 match 100.0
[libs/RVL_SDK/src/nup/nup]   section .sdata size 32 match 100.0
[libs/RVL_SDK/src/nup/nup]   section .text size 10764 match 93.442955
[libs/RVL_SDK/src/nup/nup]   below 100: __nupParseServerInfo__FP14NUPContextInfoPcPcUx 98.108406
[libs/RVL_SDK/src/nup/nup]   below 100: __nupBase64Encode__FPUcPUcUl 94.20635
[libs/RVL_SDK/src/nup/nup]   below 100: __nupGetBootVersion__FP14ESTitleVersion None
[libs/RVL_SDK/src/nup/nup]   below 100: __nupGetTitleSize__FP12NUPTitleInfo 99.100716
[libs/RVL_SDK/src/nup/nup] baseline: code 5744/10764 data 1720 functions 18 fuzzy 93.3222
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 30760/37884 data 1040/5696 functions 106/112 fuzzy 99.1581 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 105/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match 32.25412
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 99.15806
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 98.8505
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 91.525314
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 98.38498
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 98.0
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.69863
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 95.39338
[src/scene/setting/iplSetting] baseline: code 30760/37884 data 1040 functions 106 fuzzy 99.1581
regressions vs baseline: 0
global matched_code_percent: 87.68906 -> 87.79135
global fuzzy_match_percent: 99.36968 -> 99.37380
global complete_code_percent: 61.81448 -> 61.81448
global matched_data_percent: 91.26920 -> 91.26920
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## Before -> after

| Unit | Instruction exact | Objdiff exact functions | Objdiff exact code bytes | Objdiff data bytes |
| --- | --- | --- | --- | --- |
| libs/RevoEX/src/nwc24/NWC24Download | 23/30 -> 25/30 | 23/30 -> 25/30 | 6828 -> 8140 / 12496 | 80 -> 80 / 80 |
| libs/RVL_SDK/src/nup/nup | 18/23 -> 19/23 | 18/23 -> 19/23 | 5744 -> 7496 / 10764 | 1720 -> 1720 / 1720 |
| src/scene/setting/iplSetting | 105/112 -> 105/112 | 106/112 -> 106/112 | 30760 -> 30760 / 37884 | 1040 -> 1040 / 5696 |

Starting HEAD: `a348c9777aa65410b85f255be2a24363187d83aa`. Fresh start report: `/tmp/sol-med-structural12/start-report.json`; fresh final report: `/tmp/sol-med-structural12/final-report.json`. All 1024 unowned units retain identical measures, function records and section records to the starting report.

## Exact improvements and commits

| Commit | Source | Result | Full gate evidence |
| --- | --- | --- | --- |
| `8913ba0c` | `libs/RevoEX/src/nwc24/NWC24Download.c` | `NWC24ManageDlTaskListForMenu`: 150/152 -> 152/152; objdiff 100.0; ctxdiff 0. Fresh task-pointer assignment separates read and delete lifetimes. | `/tmp/sol-med-structural12/menu-full-gate.txt` |
| `785f85ad` | `libs/RevoEX/src/nwc24/NWC24Download.c` | `NWC24PurgeOldestDlTask`: 167/176 -> 176/176; objdiff 100.0; ctxdiff 0. Real iterator initializer boundary, selected-ID declaration order and successful-iteration read/delete lifetimes. | `/tmp/sol-med-structural12/purge-full-gate.txt` |
| `7cbf242f` | `libs/RVL_SDK/src/nup/nup.cpp` | `__nupOp`: 438/438 with 47 differences -> 438/438 with 0; objdiff 100.0. Width-valid boot output store plus direct context-title access. | `/tmp/sol-med-structural12/op-full-gate.txt` |

Each improvement passed a full clean 43U gate before its local commit. Every pool, including string offsets, remains identical. The final full gate independently rebuilt all three units and confirms zero baseline regressions, zero forbidden additions, zero readability warnings and the original DOL SHA-1. Setting remains unchanged; fuzzy-only experiments were restored.

The boot-version local in `__nupOp` is an output parameter initialized by the successful getter. `ES_GetBoot2Version` writes its output only for `IPC_RESULT_OK` (0); `private/ipc/types.h` defines negative IPC errors. The inline conversion initializes the caller output after width validation and the caller exits on a negative result. This does not read an uninitialized value on the API success/error paths.

## Remaining nonmatching functions

Percentages below describe the retained final source. Better partial candidates are rejected snapshots, not claimed gains. Structural and positional scores come from declsearch; the instruction count comes from disassembly. Every remaining function has at least three successful, distinct logged source attempts and three source snapshots.

| Unit | Exact symbol | Objdiff percent | Instructions; score; attempts | Remaining difference |
| --- | --- | --- | --- | --- |
| libs/RevoEX/src/nwc24/NWC24Download | `NWC24InitDlTask` | 98.923615 | 144/144; (0, 31); 5 attempts, 5 snapshots | 144/144 instructions; cached header, owner halves and home-path zero register allocation differ. Five source forms plus a 71-build declaration search did not change the register plateau. |
| libs/RevoEX/src/nwc24/NWC24Download | `NWC24IterateDlTask` | 99.303795 | 79/79; (0, 10); 3 attempts, 3 snapshots | 79/79 instructions; cached work/header registers are exchanged. Three loop/header/helper forms and a 36-build declaration search did not produce exact allocation. |
| libs/RevoEX/src/nwc24/NWC24Download | `NWC24UpdateDlTask` | 95.003950 | 249/253; (19, 250); 13 attempts, 13 snapshots | 249/253 instructions; permission helper boundaries, retry-header branch and saved-register/frame allocation differ. Thirteen source trials reduced the best rejected candidate to 253/253 and register-only score (0,26), 99.48617%; its declaration search did not improve. |
| libs/RevoEX/src/nwc24/NWC24Download | `NWC24iCheckDlHeaderConsistency` | 98.773580 | 212/212; (2, 3); 3 attempts, 3 snapshots | 212/212 instructions; three prologue instructions initialize the stack-task pointer after the two parameter aliases rather than before them. Two inline-loop argument orders regressed NWC24iOpenDlTaskList and were restored; repair-alias and declaration search also failed. |
| libs/RevoEX/src/nwc24/NWC24Download | `AddTaskInternal` | 97.718200 | 398/401; (20, 323); 3 attempts, 3 snapshots | 398/401 instructions; URL failure/helper boundaries, free-slot narrowing and inline retry bookkeeping differ. A wide free-slot counter reached 400/401, 98.81546%, with structural differences remaining; all three candidates were restored. |
| libs/RVL_SDK/src/nup/nup | `__nupParseServerInfo__FP14NUPContextInfoPcPcUx` | 98.108406 | 452/452; (0, 148); 3 attempts, 3 snapshots | 452/452 instructions; register allocation across repeated inline tag searches differs. Split checks, cursor declarations and output-store temporaries were tried before a 36-build declaration search; no exact candidate. |
| libs/RVL_SDK/src/nup/nup | `__nupBase64Encode__FPUcPUcUl` | 94.206350 | 63/63; (9, 21); 7 attempts, 7 snapshots | 63/63 instructions; first/second sextet extraction, table load/store scheduling and byte-count register differ. Seven distinct source trials plus declaration search did not match; swapping first/second source declarations compiled to the same mismatch. |
| libs/RVL_SDK/src/nup/nup | `__nupGetBootVersion__FP14ESTitleVersion` | None (unpaired) | 163/163; (0, 17); 3 attempts, 3 snapshots | 163/163 instructions after manual alias pairing; 17 register differences in title/content loops. Target symbol omits the context parameter present in the implementation and target ABI. Three title-ID/count/conversion trials were restored. No rename, symbol or configuration change. |
| libs/RVL_SDK/src/nup/nup | `__nupGetTitleSize__FP12NUPTitleInfo` | 99.100716 | 139/139; (0, 22); 3 attempts, 3 snapshots | 139/139 instructions; wide-size addition and installed-content lookup register allocation differ. Progress order, explicit rounded size and helper declarations were tried before declaration search; no exact candidate. |
| src/scene/setting/iplSetting | `createBrowser__Q33ipl5scene7SettingFv` | 98.850500 | 299/301; (15, 114); 3 attempts, 3 snapshots | 299/301 instructions; 0x200 frame versus target 0x210, saved-register allocation and direct-page switch branches differ. The target has explicit case seven and an unreachable default retaining r30; safe default variants retain extra instructions. Three explicit branch/declaration/index trials were restored. |
| src/scene/setting/iplSetting | `draw__Q33ipl5scene7SettingFv` | 91.525314 | 595/632; (82, 570); 15 attempts, 15 snapshots | 595/632 instructions; render-mode initialization emits a block copy instead of target typed assignment, scroll-store branches and side-rectangle integer/float scheduling also differ. Fifteen trials found a rejected 629/632, 98.34335% candidate using ordinary render-mode assignment and corrected branches; rectangle variants remained structural mismatches. |
| src/scene/setting/iplSetting | `initKeyboard__Q33ipl5scene7SettingFPCc` | 98.384980 | 215/213; (4, 195); 3 attempts, 3 snapshots | 215/213 instructions; defined row/string fallback values add instructions and affect frame/register allocation. Default-branch assignments, validation lifetime and dictionary temporaries were tried. No uninitialized fallback values were introduced. |
| src/scene/setting/iplSetting | `calcKeyboard__Q33ipl5scene7SettingFv` | 98.000000 | 292/290; (15, 258); 3 attempts, 3 snapshots | 292/290 instructions; defined form-text defaults and asterisk-loop index/store scheduling differ. Initialized commit pointer, separate store/update and explicit switch defaults were tried. No uninitialized form-text values were introduced. |
| src/scene/setting/iplSetting | `convertRevIP__Q33ipl5scene7SettingFPUcPCc` | 98.698630 | 73/73; (0, 16); 8 attempts, 8 snapshots | 73/73 instructions; ASCII buffer, output cursor, index and terminator register allocation differ. Eight source trials plus a 23-build declaration search left the best rejected candidate at eight register differences, 99.31507%. |
| src/scene/setting/iplSetting | `scanAP__Q33ipl5scene7SettingFv` | 95.393380 | 266/272; (53, 160); 11 attempts, 8 snapshots | 266/272 instructions; animation BOOL materialization, case-seven flag/index order and case-nine layout/index scheduling differ. Eleven distinct source trials reached a rejected 272/272 candidate with seven differences, 99.14706%; three branches use bgt instead of target bne, with four load-order differences. Guarded header experiments regressed other exact functions and were fully restored. |

## Measurement uncertainties

- `__nupGetBootVersion__FP14ESTitleVersion` is unpaired in objdiff because the source symbol includes `NUPContextInfo*`. Manual pairing proves 163/163 instructions and 17 register differences; no percentage was invented and no symbol was renamed.
- `setUpdate_NoUpdateDialog___Q33ipl5scene7SettingFv` is already objdiff 100.0 and its 120 raw code bytes match. The odiff comparator used by the gate interprets the CR operand of two conditional branches as an immediate and subtracts the function address, reporting two false branch differences. This explains instruction exact 105/112 versus objdiff 106/112 in Setting; the function was left untouched.
- Setting data remains 1040/5696: original zero-filled weak vtable/inline sections from DOL extraction prevent complete object data matching. No data padding, symbol-address pinning or link work was attempted. The full gate verifies the unchanged linked DOL, which does not claim this nonmatching unit is linked.

## Files and evidence

- Source: `libs/RevoEX/src/nwc24/NWC24Download.c`, `libs/RVL_SDK/src/nup/nup.cpp`.
- Attempt log: `tools/decomp-assist/sol-med-structural-round12.attempts.md`.
- Full final gate: `tools/decomp-assist/sol-med-structural-round12.final-gate.txt`.
- This report: `tools/decomp-assist/sol-med-structural-round12.report.md`.
- Target assembly, baseline/variant diffs, distinct source snapshots and declaration-search output remain under `/tmp/sol-med-structural12/`.
- Earlier untracked round 8, 9 and 11 records were preserved.
