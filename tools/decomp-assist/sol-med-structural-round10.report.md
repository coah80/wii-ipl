# Structural round 10

Committed one new exact function: `Setting::setUSBAP`, with an inline result-byte predicate that preserves the target's separate guard and argument loads. The source change adds five lines and changes one condition. No volatile access, new assembly, hand-placed data, header or configuration changes.

| Unit | Instruction-exact before -> after | Objdiff exact before -> after | Matched code bytes before -> after | Matched data bytes before -> after |
| --- | --- | --- | --- | --- |
| libs/RevoEX/src/nwc24/NWC24Download | 23 -> 23 / 30 | 23 -> 23 / 30 | 6828 -> 6828 / 12496 | 80 -> 80 / 80 |
| libs/RVL_SDK/src/nup/nup | 18 -> 18 / 23 | 18 -> 18 / 23 | 5744 -> 5744 / 10764 | 1720 -> 1720 / 1720 |
| src/scene/setting/iplSetting | 104 -> 105 / 112 | 105 -> 106 / 112 | 30532 -> 30760 / 37884 | 1040 -> 1040 / 5696 |

## Remaining functions

NWC24InitDlTask | 98.923615 | 144/144 instructions; local and ownership-helper register colors.
NWC24IterateDlTask | 99.303795 | 79/79 instructions; work/header r6/r7 colors reversed.
NWC24UpdateDlTask | 95.00395 | 249/253 instructions; 0x30/0x20 frame, ownership/timestamp inline boundaries, retry branch and mask operands.
NWC24PurgeOldestDlTask | 87.11364 | 167/176 instructions; iterator initializer, shared read/removal result and error conversion boundaries.
NWC24ManageDlTaskListForMenu | 96.74342 | 150/152 instructions; inline validation/removal status lifetime and argument registers.
NWC24iCheckDlHeaderConsistency | 98.77358 | 212/212 instructions; three prologue instructions scheduled in a different order.
AddTaskInternal | 97.7182 | 398/401 instructions; URL failure branch, free-slot short counter, update helper boundaries.
__nupParseServerInfo__FP14NUPContextInfoPcPcUx | 98.108406 | 452/452 instructions; colors across repeated tag-helper expansion.
__nupBase64Encode__FPUcPUcUl | 94.20635 | 63/63 instructions; quartet load/store schedule and counter register.
__nupGetBootVersion__FP14ESTitleVersion | unpaired | target name omits context although asm uses both parameters; actual two-parameter body has 163/163 instructions and 17 register differences.
__nupGetTitleSize__FP12NUPTitleInfo | 99.100716 | 139/139 instructions; wide-add high word and installed-content search colors.
__nupOp | 99.25799 | 438/438 instructions; output initialization and conversion branches plus title selection colors. Provisional structural fixes reached 11 register differences, then were restored without exact gain.
createBrowser__Q33ipl5scene7SettingFv | 98.8505 | 299/301 instructions; frame 0x200/0x210 and direct-page switch/default shape. Uninitialized default was not reproduced.
draw__Q33ipl5scene7SettingFv | 91.525314 | 595/632 instructions; GX mode scalar copy, scroll/window branches, rectangle and texture lifetimes.
initKeyboard__Q33ipl5scene7SettingFPCc | 98.38498 | 215/213 instructions; safe limit defaults, settings stores and local colors.
calcKeyboard__Q33ipl5scene7SettingFv | 98.0 | 292/290 instructions; safe form defaults, asterisk update and cancellation pointer lifetime.
convertRevIP__Q33ipl5scene7SettingFPUcPCc | 98.69863 | 73/73 instructions; component counter and buffer/output pointer colors.
scanAP__Q33ipl5scene7SettingFv | 95.39338 | 266/272 instructions; animation boolean materialization and animation/state store order.

## Attempts and scope

Every remaining function has at least three distinct logged source attempts that built successfully. The final audit excludes the discarded purge trial with incorrect source slicing. Structural diagnosis preceded edits. Declaration searches ran last; explicit source line ranges bypassed the tool's SDK-symbol name parser limitation. For the boot-version body, the target lookup was mapped only in the temporary Python runner, without renaming source functions.

All rejected or fuzzy-only code changes were restored. No output from another translation unit was changed. Starting untracked round 8 and round 9 records were preserved.

Detailed attempts: `sol-med-structural-round10.attempts.md`. Complete source trial diffs and target assembly: `/tmp/sol-med-round10/diffs.txt`. Provisional source snapshots remain in `/tmp/sol-med-round10` for diagnostic evidence only.

## Validation and commits

Code commit: `31cd9401`, `match usb access point completion handling`.

The first clean full gate passed: build successful, DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`, identical Setting pool, zero regressions, zero forbidden patterns and zero readability problems. `setUSBAP` has 57/57 instructions, ctxdiff diffs 0 and exact-name objdiff 100.0.

Final clean full gate over all three units is recorded in `sol-med-structural-round10.final-gate.txt`. Final clean full gate: `GATE PASS`. All three pools identical; full build successful; target DOL SHA1 retained; zero regressions, forbidden patterns and readability problems. Independent comparison of all 1027 unit reports confirms that only Setting changed. Exact `setUSBAP` was rechecked after the clean rebuild.

## Measurement uncertainties

Setting's instruction comparator reports one fewer exact function than objdiff. Fresh verification finds identical 120-byte bodies for `setUpdate_NoUpdateDialog_`, with structural/exact score `(0, 0)` in the operand-corrected disassembler. The gate/ctxdiff disassembler reads the first CR operand of `blt cr1` as an immediate rather than using the branch target operand; different function offsets therefore create two false differences. Prior round records attributed this to NaN; current evidence supports the CR-operand parsing explanation. No verification tooling was changed. Setting data remains 1040/5696; original weak/inline data may have been deduplicated by the linker. Linking is outside this phase. The boot-version target's one-parameter mangled name does not describe its two-parameter machine code.

## Final gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24Download] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Download] objdiff: code 6828/12496 data 80/80 functions 23/30 fuzzy 98.2676 linked code 0
[libs/RevoEX/src/nwc24/NWC24Download] instruction-exact functions: 23/30
[libs/RevoEX/src/nwc24/NWC24Download]   section .data size 56 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .text size 12496 match 98.26761
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24InitDlTask 98.923615
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTask 99.303795
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24UpdateDlTask 95.00395
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24PurgeOldestDlTask 87.11364
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24ManageDlTaskListForMenu 96.74342
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCheckDlHeaderConsistency 98.77358
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: AddTaskInternal 97.7182
[libs/RevoEX/src/nwc24/NWC24Download] baseline: code 6828/12496 data 80 functions 23 fuzzy 98.2676
[libs/RVL_SDK/src/nup/nup] pool: IDENTICAL
[libs/RVL_SDK/src/nup/nup] objdiff: code 5744/10764 data 1720/1720 functions 18/23 fuzzy 93.3222 linked code 0
[libs/RVL_SDK/src/nup/nup] instruction-exact functions: 18/23
[libs/RVL_SDK/src/nup/nup]   section .data size 1592 match 100.0
[libs/RVL_SDK/src/nup/nup]   section .rodata size 88 match 100.0
[libs/RVL_SDK/src/nup/nup]   section .sbss size 8 match 100.0
[libs/RVL_SDK/src/nup/nup]   section .sdata size 32 match 100.0
[libs/RVL_SDK/src/nup/nup]   section .text size 10764 match 93.32218
[libs/RVL_SDK/src/nup/nup]   below 100: __nupParseServerInfo__FP14NUPContextInfoPcPcUx 98.108406
[libs/RVL_SDK/src/nup/nup]   below 100: __nupBase64Encode__FPUcPUcUl 94.20635
[libs/RVL_SDK/src/nup/nup]   below 100: __nupGetBootVersion__FP14ESTitleVersion None
[libs/RVL_SDK/src/nup/nup]   below 100: __nupGetTitleSize__FP12NUPTitleInfo 99.100716
[libs/RVL_SDK/src/nup/nup]   below 100: __nupOp 99.25799
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
[src/scene/setting/iplSetting] baseline: code 30532/37884 data 1040 functions 105 fuzzy 99.1465
regressions vs baseline: 0
global matched_code_percent: 87.12394 -> 87.13156
global fuzzy_match_percent: 99.36623 -> 99.36638
global complete_code_percent: 61.40923 -> 61.40923
global matched_data_percent: 91.13999 -> 91.13999
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
