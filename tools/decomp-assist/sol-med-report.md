# sol-med matching report

Final full gate command:

`python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py libs/RevoEX/src/nwc24/NWC24Download libs/RVL_SDK/src/nup/nup src/scene/setting/iplSetting --base f00336cc`

GATE PASS; clean 43U build; expected DOL SHA1; zero regressions, forbidden patterns, and readability warnings; all three pools identical.

| Unit | Instruction exact before -> after | Objdiff functions before -> after | Matched code bytes before -> after | Matched data bytes before -> after |
| --- | --- | --- | --- | --- |
| libs/RevoEX/src/nwc24/NWC24Download | 19 -> 21 | 19 -> 21 | 4752 -> 5668 | 80 -> 80 |
| libs/RVL_SDK/src/nup/nup | 18 -> 18 | 18 -> 18 | 5744 -> 5744 | 1720 -> 1720 |
| src/scene/setting/iplSetting | 104 -> 104 | 105 -> 105 | 30532 -> 30532 | 1040 -> 1040 |

Exact additions: `NWC24GetDlTask` (92/92 instructions, ctxdiff diffs 0) and `NWC24ExtendDlTaskList` (137/137, diffs 0).

Remaining functions (every one has at least three distinct compiled source attempts recorded in sol-med-attempts.jsonl):

- NWC24InitDlTask: objdiff 98.923615; 4 attempts; same 144 instructions; 31 register differences.
- NWC24SetDlInterval: objdiff 99.89796; 5 attempts; same 147 instructions; terminal task ID uses r28 instead of r30.
- NWC24IterateDlTask: objdiff 99.303795; 11 attempts; same 79 instructions; 10 cached work/header register differences.
- NWC24UpdateDlTask: objdiff 95.00395; 3 attempts; stack frame 0x30 versus 0x20; retry helper branch and register differences.
- NWC24AddDlTask: objdiff 97.552444; 3 attempts; extra saved register and universal-time branch; next-time helper temporaries.
- NWC24PurgeOldestDlTask: objdiff 87.11364; 3 attempts; iteration initialization and deletion inline boundaries; register assignments.
- NWC24ManageDlTaskListForMenu: objdiff 96.74342; 3 attempts; deletion validation and return boundary differ by two instructions.
- NWC24iCheckDlHeaderConsistency: objdiff 98.77358; 4 attempts; same 212 instructions; first three parameter/address moves scheduled differently.
- AddTaskInternal: objdiff 97.7182; 3 attempts; URL validation, retry helper, and free-task search branches differ.
- __nupParseServerInfo__FP14NUPContextInfoPcPcUx: objdiff 98.108406; 4 attempts; same 452 instructions; 148 register differences across tag helper expansions.
- __nupBase64Encode__FPUcPUcUl: objdiff 94.20635; 7 attempts; same 63 instructions; digit load/store scheduling and count register differ.
- __nupGetBootVersion__FP14ESTitleVersion: objdiff None; 3 attempts; target symbol encodes one parameter but assembly uses r3 context and r4 title; source retains two-parameter signature; 17 register differences under cross-name comparison.
- __nupGetTitleSize__FP12NUPTitleInfo: objdiff 99.100716; 4 attempts; same 139 instructions; content helper registers and 64-bit addition temporaries differ.
- __nupOp: objdiff 99.25799; 3 attempts; same 438 instructions; boot-version initialization/check placement and title-loop registers differ.
- createBrowser__Q33ipl5scene7SettingFv: objdiff 98.8505; 6 attempts; stack frame 0x200 versus 0x210; direct-page switch and register allocation differ.
- draw__Q33ipl5scene7SettingFv: objdiff 91.525314; 4 attempts; render-mode aggregate copy, side-rectangle floating-point scheduling and texture order differ.
- initKeyboard__Q33ipl5scene7SettingFPCc: objdiff 98.38498; 3 attempts; extra safe initializations of keyboard limits plus register differences; target leaves unsupported form limits uninitialized.
- calcKeyboard__Q33ipl5scene7SettingFv: objdiff 98.0; 3 attempts; asterisk loop pointer scheduling and cancellation branch temporaries differ; retains defined defaults.
- convertRevIP__Q33ipl5scene7SettingFPUcPCc: objdiff 98.69863; 4 attempts; same 73 instructions; 16 register differences.
- scanAP__Q33ipl5scene7SettingFv: objdiff 95.39338; 4 attempts; animation-playing boolean materialization and member-read ordering differ.
- setUSBAP__Q33ipl5scene7SettingFv: objdiff 98.070175; 3 attempts; target reads completion byte twice; compiler reuses one read; no volatile cast added.

Gate limitations:

- The default merge-base 0c554a16 has no provided baseline report. The final gate uses its immediate ancestor f00336cc, whose baseline exists. Baseline files and gate.py were not modified.
- iplSetting objdiff reports 105 exact functions, while the gate reports 104 instruction-exact. setUpdate_NoUpdateDialog___Q33ipl5scene7SettingFv remains objdiff 100; the gate compares unresolved relocated blt offsets whose values depend on preceding function sizes. This discrepancy existed before this run.
- The __nupGetBootVersion target symbol/signature mismatch remains unresolved. No real functions or config symbols were renamed.
- Removed initial values on draw rectangle output pointers are not uninitialized reads: BrowserWindow::GetTextureBuffer assigns the output rectangle before returning a non-null buffer (src/iplwww/www_window.cpp:445); draw uses those pointers only when both returned buffers are non-null. No shared header or other translation unit was edited.

Source paths changed:

- libs/RevoEX/src/nwc24/NWC24Download.c
- libs/RVL_SDK/src/nup/nup.cpp
- src/scene/setting/iplSetting.cpp

Supporting files: sol-med-attempts.jsonl and sol-med-final-gate.txt.
