# sol-y8 kbd_lib attempts

Scope: data-d12, agent/w1009/data-d12, baseline d558bb14. First requested Ninja object build passed. Fetch confirmed HEAD equals origin/main. Raw baseline exact 18/21; setter 4/42, processor 4/256, LED handler 3/25; pools identical.

History read: sol-common.md, brief-v2.md, levers.md, kbd_lib, rx6, rx6b, rx6c, perm4, fz15, structural-matching, opus-art, lv19, sol-tiny and data-d4 g2 attempt logs. Empty sol-tiny.kbd_lib.diff is unchanged baseline. Do not repeat pointer-local, old-first, declaration permutation, index casts, scalar mask merges, union field copies, status output helpers or duplicated callback-index experiments.

Fresh setter capture: /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/KBDSetModState-20261008-223655. Whole object matches baseline. Address v48=r5 and old word v49=r4 have an interference edge. Regsim reproduces 23/23 and reaches 0/2 desired colors with named-local reorder. Whole-unit optsweep optimization levels 0-3 and IRO 0-1 returned no leads.

| Trial | Setter diffs/insns | Processor diffs/insns | LED diffs/insns | Other exact losses |
| --- | --- | --- | --- | --- |
| led-optimization_level-0-if | 4/42 | 4/256 | 51/51 | 0 |
| led-optimization_level-0-else | 4/42 | 4/256 | 51/51 | 0 |
| led-optimization_level-0-switch | 4/42 | 4/256 | 51/51 | 0 |
| led-optimization_level-1-if | 4/42 | 4/256 | 35/35 | 0 |
| led-optimization_level-1-else | 4/42 | 4/256 | 35/35 | 0 |
| led-optimization_level-1-switch | 4/42 | 4/256 | 33/33 | 0 |
| led-optimization_level-2-if | 4/42 | 4/256 | 24/24 | 0 |
| led-optimization_level-2-else | 4/42 | 4/256 | 24/24 | 0 |
| led-optimization_level-2-switch | 4/42 | 4/256 | 3/25 | 0 |
| led-optimization_level-3-if | 4/42 | 4/256 | 23/23 | 0 |
| led-optimization_level-3-else | 4/42 | 4/256 | 23/22 | 0 |
| led-optimization_level-3-switch | 4/42 | 4/256 | 3/25 | 0 |
| led-ppc_iro_level-0-if | 4/42 | 4/256 | 9/25 | 0 |
| led-ppc_iro_level-0-else | 4/42 | 4/256 | 12/25 | 0 |
| led-ppc_iro_level-0-switch | 4/42 | 4/256 | 12/25 | 0 |
| led-ppc_iro_level-1-if | 4/42 | 4/256 | 25/23 | 0 |
| led-ppc_iro_level-1-else | 4/42 | 4/256 | 25/22 | 0 |
| led-ppc_iro_level-1-switch | 4/42 | 4/256 | 12/25 | 0 |
| mod-optimization_level-0 | 50/51 | 4/256 | 3/25 | 0 |
| mod-optimization_level-1 | 32/49 | 4/256 | 3/25 | 0 |
| mod-optimization_level-2 | 26/45 | 4/256 | 3/25 | 0 |
| mod-optimization_level-3 | 7/42 | 4/256 | 3/25 | 0 |
| mod-ppc_iro_level-0 | 7/42 | 4/256 | 3/25 | 0 |
| mod-ppc_iro_level-1 | 4/42 | 4/256 | 3/25 | 0 |
| mod-nested-plain | 4/42 | 4/256 | 3/25 | 0 |
| mod-nested-union | 4/42 | 4/256 | 3/25 | 0 |
| mod-nested-union-copy-load | 4/42 | 4/256 | 3/25 | 0 |
| mod-nested-overlay | 4/42 | 4/256 | 3/25 | 0 |
| mod-nested-overlay-union-load | 4/42 | 4/256 | 3/25 | 0 |
| mod-accessor-u32-load | 7/42 | 47/253 | 3/25 | 0 |
| mod-accessor-u32-store | 4/42 | 4/256 | 3/25 | 0 |
| mod-accessor-u32-both | 7/42 | 4/256 | 3/25 | 0 |
| mod-accessor-s32-load | 7/42 | 251/261 | 3/25 | 0 |
| mod-accessor-s32-store | 4/42 | 251/261 | 3/25 | 0 |
| mod-accessor-s32-both | 7/42 | 254/258 | 3/25 | 0 |
| mod-accessor-const-u32-load | 7/42 | 251/261 | 3/25 | 0 |
| mod-accessor-const-u32-store | 4/42 | 251/261 | 3/25 | 0 |
| mod-accessor-const-u32-both | 7/42 | 254/258 | 3/25 | 0 |
| mod-accessor-u8-load | 22/45 | 252/262 | 3/25 | 0 |
| mod-accessor-u8-store | 21/45 | 252/262 | 3/25 | 0 |
| mod-accessor-u8-both | 20/43 | 255/259 | 3/25 | 0 |
| mod-parameter-s32 | 5/42 | 254/259 | 3/25 | KBDResetChannel |
| mod-parameter-u8 | 4/42 | 256/261 | 3/25 | KBDResetChannel |
| mod-parameter-const-u32 | 4/42 | 254/259 | 3/25 | 0 |
| led-iro0-decls-callback-index-err | 4/42 | 4/256 | 9/25 | 0 |
| led-iro0-decls-callback-err-index | 4/42 | 4/256 | 9/25 | 0 |
| led-iro0-decls-index-callback-err | 4/42 | 4/256 | 9/25 | 0 |
| led-iro0-decls-index-err-callback | 4/42 | 4/256 | 9/25 | 0 |
| led-iro0-decls-err-callback-index | 4/42 | 4/256 | 9/25 | 0 |
| led-iro0-decls-err-index-callback | 4/42 | 4/256 | 9/25 | 0 |
| led-iro0-u32-pointer-null | 4/42 | 4/256 | 9/25 | 0 |
| led-iro0-u32-pointer-device | 4/42 | 4/256 | 9/25 | 0 |
| led-iro0-u32-value-null | 4/42 | 4/256 | 10/25 | 0 |
| led-iro0-u32-value-device | 4/42 | 4/256 | 10/25 | 0 |
| led-iro0-u32-direct-null | 4/42 | 4/256 | 0/25 | 0 |
| led-iro0-u32-direct-device | 4/42 | 4/256 | 0/25 | 0 |
| led-iro0-s32-pointer-null | 4/42 | 4/256 | 9/25 | 0 |
| led-iro0-s32-pointer-device | 4/42 | 4/256 | 9/25 | 0 |
| led-iro0-s32-value-null | 4/42 | 4/256 | 10/25 | 0 |
| led-iro0-s32-value-device | 4/42 | 4/256 | 10/25 | 0 |
| led-iro0-s32-direct-null | 4/42 | 4/256 | 0/25 | 0 |
| led-iro0-s32-direct-device | 4/42 | 4/256 | 0/25 | 0 |
| led-iro0-clean-index-uses | 4/42 | 4/256 | 0/25 | 0 |
| led-iro0-clean-index-init | 4/42 | 4/256 | 0/25 | 0 |
| led-iro0-clean-result-type | 4/42 | 4/256 | 0/25 | 0 |
| led-iro0-clean-direct-arg | compile failed | - | - | - |

## Retained LED handler match

The target preserves a success==TRUE if/else, supplies zero on the fallthrough and seven on the taken path, then rematerializes the mutable callback-table address. Default optimization folds the ordinary if/else into arithmetic or places a switch error block first. A function-scoped ppc_iro_level 0 preserves the target control flow. Removing the cached callback-record pointer fixes the remaining nine initial address/zero register differences. Direct table reads, a plain NULL guard and the existing per-slot index match all 25 instructions. Success remains exactly TRUE, rather than any nonzero value. Command release still precedes the callback guard and invocation.

Retained source uses u32 index, USBKBDErr err and direct index reads throughout. Normal requested Ninja build passed. ctxdiff and odiff each report 0/25 differences, equal 100-byte size. Exact-name objdiff is 100.0%; unit gains 18/21 -> 19/21 and matched code 4472 -> 4572 bytes. All four owned data sections remain 100%, total 5296/5296 bytes; pool identical. Other 20 functions unchanged. The modifier pair remains 4/42 and 4/256. No configure.py flip while two functions remain open.

The clean-direct-arg scratch generator removed index declarations in unrelated functions and failed compilation. That failed generator is excluded from source-attempt coverage. Whole-unit optimization sweep is diagnostic; only the scoped LED setting is retained.

## Modifier representation with scoped optimization

These trials combine the supported scoped settings with scalar/bitfield update forms. They test whether suppressing IRO copy/address rewriting retains an old-word virtual register before the destination address; the ordinary default-setting versions were already exhausted and are not repeated. All scratch compilations now include the retained exact LED handler.

| Trial | Setter diffs/insns | Processor diffs/insns | LED diffs/insns | Other exact losses |
| --- | --- | --- | --- | --- |
| mod-combo-ppc_iro_level-0-scalar-old | 7/42 | 5/256 | 0/25 | 0 |
| mod-combo-ppc_iro_level-0-scalar-new | 7/42 | 5/256 | 0/25 | 0 |
| mod-combo-ppc_iro_level-0-scalar-expression | 7/42 | 5/256 | 0/25 | 0 |
| mod-combo-ppc_iro_level-0-union-old-first | 7/42 | 4/256 | 0/25 | 0 |
| mod-combo-ppc_iro_level-0-union-old-copy | 6/42 | 7/256 | 0/25 | 0 |
| mod-combo-ppc_iro_level-0-union-physical-input | 7/42 | 4/256 | 0/25 | 0 |
| mod-combo-ppc_iro_level-0-scalar-with-physical-field | 7/42 | 5/256 | 0/25 | 0 |
| mod-combo-ppc_iro_level-0-field-physical | 7/42 | 47/253 | 0/25 | 0 |
| mod-combo-ppc_iro_level-0-field-copy | 7/42 | 4/256 | 0/25 | 0 |
| mod-combo-optimization_level-3-scalar-old | 7/42 | 5/256 | 0/25 | 0 |
| mod-combo-optimization_level-3-scalar-new | 7/42 | 5/256 | 0/25 | 0 |
| mod-combo-optimization_level-3-scalar-expression | 7/42 | 5/256 | 0/25 | 0 |
| mod-combo-optimization_level-3-union-old-first | 7/42 | 4/256 | 0/25 | 0 |
| mod-combo-optimization_level-3-union-old-copy | 6/42 | 7/256 | 0/25 | 0 |
| mod-combo-optimization_level-3-union-physical-input | 7/42 | 4/256 | 0/25 | 0 |
| mod-combo-optimization_level-3-scalar-with-physical-field | 7/42 | 5/256 | 0/25 | 0 |
| mod-combo-optimization_level-3-field-physical | 7/42 | 47/253 | 0/25 | 0 |
| mod-combo-optimization_level-3-field-copy | 7/42 | 4/256 | 0/25 | 0 |
| mod-combo-ppc_iro_level-1-scalar-old | 4/42 | 5/256 | 0/25 | 0 |
| mod-combo-ppc_iro_level-1-scalar-new | 7/42 | 5/256 | 0/25 | 0 |
| mod-combo-ppc_iro_level-1-scalar-expression | 7/42 | 5/256 | 0/25 | 0 |
| mod-combo-ppc_iro_level-1-union-old-first | 4/42 | 4/256 | 0/25 | 0 |
| mod-combo-ppc_iro_level-1-union-old-copy | 6/42 | 7/256 | 0/25 | 0 |
| mod-combo-ppc_iro_level-1-union-physical-input | 4/42 | 4/256 | 0/25 | 0 |
| mod-combo-ppc_iro_level-1-scalar-with-physical-field | 7/42 | 5/256 | 0/25 | 0 |
| mod-combo-ppc_iro_level-1-field-physical | 7/42 | 47/253 | 0/25 | 0 |
| mod-combo-ppc_iro_level-1-field-copy | 4/42 | 4/256 | 0/25 | 0 |

## Modifier result

Twenty new layout/accessor/parameter trials plus six scoped baseline settings and twenty-seven scoped representation combinations produced no accepted modifier improvement. Nested lock-processing/state records, union overlays and complete state copies preserve four differences. Returning an element from an inline accessor either preserves the four or adds earlier address swaps. Signature signedness/width/const trials regress inlined processor or sibling reset code. Supported low optimization settings leave seven register differences or unequal sizes. All rejected source remained in private /tmp/sol-y8-* files; retained setter/processor definitions are unchanged.

The direct-field variants under IRO 0/1 lose three instructions in the inlined processor. Scalar forms preserve 42/256 counts but alter insert shape. Physical union extraction continues to disappear into unnamed v48/v49, whose priority cannot be changed by local declaration order. Best remains baseline 4/42 and 4/256. No fuzzy-only modifier change is retained.

Private best diff will include the exact LED match only. Unit remains NonMatching at 19/21. Final gate recorded below.

## Final gate

Command: python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py libs/RVL_SDK/src/kbd/kbd_lib --quick. Exit 0, GATE PASS. Full 43U build passed; DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Instruction-exact and objdiff exact functions 19/21; code 4572/5764 bytes; data 5296/5296 bytes. Pools identical, all four data sections 100%. Global and unit regressions 0; net forbidden patterns 0; readability warnings 0. The gate flags the supported scoped pragma for orchestrator review. Target rematerializes callback-table base after the success/error branch, although no intervening call or write modifies the callback table; IRO 0 reproduces that repeated address computation and the target branch layout.

Raw gate output: /tmp/sol-y8-gate.log. Live report regenerated with Ninja progress build/43U/report.json. Private focused diff: /mnt/drive2/projects/wii-ipl-workers/_luna-runs/best/sol-y8.kbd_lib.diff. Retained source commit 56a9d48d. No Matching flip, because KBDSetModState and kbdProcMod remain nonexact. Worker handoff requires parent independent verification before landing.
