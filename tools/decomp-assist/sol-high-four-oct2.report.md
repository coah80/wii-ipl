# Four-unit matching result, 2026-10-02

Source commit: 92c886dd, match partition sector conversion.

| Unit | Instruction-exact functions before -> after | Objdiff matched code bytes before -> after | Objdiff matched data bytes before -> after |
| --- | --- | --- | --- |
| src/keyboard/tiPcKeyboard | 138/141 -> 138/141 | 27712/28484 -> 27712/28484 | 18548/18564 -> 18548/18564 |
| libs/RVL_SDK/src/fa/pdm_partition | 17/20 -> 18/20 | 2072/3716 -> 2276/3716 | absent -> absent |
| libs/RVL_SDK/src/axfx/AXFXChorusExp | 5/7 -> 5/7 | 1920/2684 -> 1920/2684 | 48/48 -> 48/48 |
| libs/RevoEX/src/net/aes | 6/9 -> 6/9 | 684/2752 -> 684/2752 | 2800/2800 -> 2800/2800 |

## Accepted change

pdm_part_chg_ltop: 100.0% objdiff, 51/51 instructions, ctxdiff diffs 0. Extracted the unchanged conversion into an inline implementation and kept the public function out of line with NO_INLINE, matching the calls in the target's logical read/write functions. A wrapper without NO_INLINE matched conversion but expanded both callers from 57 to 87 instructions, so that candidate was rejected. Final logical read/write remain exact. Full clean gate has identical pools, zero regressions, zero forbidden patterns, zero readability warnings and the required DOL hash.

## Remaining functions

setTranslateMode__Q49textinput8keyboard6pctype4BaseFQ59textinput8keyboard6pctype4Base13TranslateMode, 99.04762%: 106/105 instructions; defined invalid-enum fallback adds mr r31,r30. Target default appears uninitialized. No undefined fallback introduced.
onPressedShift__Q49textinput8keyboard6pctype12LayoutByNW4RFb, 99.081635%: 49/49 instructions; flags and owner exchange r4/r6, eight positional differences. Getter/setter boundaries and final explicit declaration search did not resolve allocation.
onReleasedShift__Q49textinput8keyboard6pctype12LayoutByNW4RFv, 98.84615%: 39/39 instructions; flags and owner exchange r4/r6, eight positional differences. Getter/setter boundaries and final explicit declaration search did not resolve allocation.
pdm_part_is_master_boot_sector, 86.5%: 86/84 instructions; extra saved register enlarges frame from target 0x30 to 0x40. Endian load scheduling and pointer allocation differ. Helper reduced frame and count, but remained non-exact.
pdm_part_get_start_sector, 82.56159%: 276/276 instructions; endian operand association, byte-load scheduling and retained traversal registers differ. Array and success-exit variants remained non-exact.
__InitParams, 69.9127%: 126/126 instructions; comparison operand order and floating/state-store scheduling differ. History-loop repair plus direct period division reached 97.81746%, 16 positional differences, but remained non-exact and was restored.
__CalcLFO, 68.53846%: 51/65 instructions; missing full signed 64-bit sample/gradient lifetime and CTR loop. Independent compound wide products reached 65/65 instructions, but retained 26 scheduling/allocation differences and were restored.
AESiEncryptBlock, 60.348103%: 158/158 instructions; initial state lifetime, table lookup scheduling and XOR associations differ. Three compiled helper/expression/declaration trials remained non-exact.
AESiDecryptBlock, 61.49004%: 249/251 instructions; target retains schedule base separately and different inverse MixColumns intermediate lifetimes. Base-pointer trial reached 251/251 but remained non-exact; restored.
NETAESCreateEx, 88.98148%: 107/108 instructions; quotient reuse prevents separate key-word recomputation, and substituted-byte association differs. Context initialization boundary reached 92.73148% but remained non-exact; restored.

## Attempt audit

85 compiled source attempts across all 11 initially open functions. Every remaining function has at least three distinct compiled source attempts. Declaration-search results and origin/main checks are recorded in sol-high-four-oct2.attempts.jsonl. Every function start fetched origin and compared current source with origin/main. Initial owned sources matched origin/main; subsequent differences were inspected owned experiments. No push, PR, worktree change, shared header change, or configure.py matching-status change.

## Files changed

- libs/RVL_SDK/src/fa/pdm_partition.c, committed in 92c886dd.
- tools/decomp-assist/sol-high-four-oct2.attempts.jsonl, attempt and validation evidence.
- tools/decomp-assist/sol-high-four-oct2.report.md, this report.

## Uncertainty

The intended invalid-enum fallback and the exact original LFO/compiler allocation boundaries remain unresolved. No uncertain source experiment was retained.

## Final full gate, copied verbatim

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/keyboard/tiPcKeyboard] pool: IDENTICAL
[src/keyboard/tiPcKeyboard] objdiff: code 27712/28484 data 18548/18564 functions 138/141 fuzzy 99.9733 linked code 0
[src/keyboard/tiPcKeyboard] instruction-exact functions: 138/141
[src/keyboard/tiPcKeyboard]   section .bss size 16 match None
[src/keyboard/tiPcKeyboard]   section .ctors size 4 match 100.0
[src/keyboard/tiPcKeyboard]   section .data size 12576 match 100.0
[src/keyboard/tiPcKeyboard]   section .rodata size 5816 match 100.0
[src/keyboard/tiPcKeyboard]   section .sbss size 8 match 100.0
[src/keyboard/tiPcKeyboard]   section .sdata size 136 match 100.0
[src/keyboard/tiPcKeyboard]   section .sdata2 size 8 match 100.0
[src/keyboard/tiPcKeyboard]   section .text size 28484 match 99.97332
[src/keyboard/tiPcKeyboard]   below 100: setTranslateMode__Q49textinput8keyboard6pctype4BaseFQ59textinput8keyboard6pctype4Base13TranslateMode 99.04762
[src/keyboard/tiPcKeyboard]   below 100: onPressedShift__Q49textinput8keyboard6pctype12LayoutByNW4RFb 99.081635
[src/keyboard/tiPcKeyboard]   below 100: onReleasedShift__Q49textinput8keyboard6pctype12LayoutByNW4RFv 98.84615
[src/keyboard/tiPcKeyboard] baseline: code 27712/28484 data 18548 functions 138 fuzzy 99.9733
[libs/RVL_SDK/src/fa/pdm_partition] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pdm_partition] objdiff: code 2276/3716 data None/None functions 18/20 fuzzy 93.5985 linked code 0
[libs/RVL_SDK/src/fa/pdm_partition] instruction-exact functions: 18/20
[libs/RVL_SDK/src/fa/pdm_partition]   section .text size 3716 match 93.598495
[libs/RVL_SDK/src/fa/pdm_partition]   below 100: pdm_part_is_master_boot_sector 86.5
[libs/RVL_SDK/src/fa/pdm_partition]   below 100: pdm_part_get_start_sector 82.56159
[libs/RVL_SDK/src/fa/pdm_partition] baseline: code 2072/3716 data None functions 17 fuzzy 93.4801
[libs/RVL_SDK/src/axfx/AXFXChorusExp] pool: IDENTICAL
[libs/RVL_SDK/src/axfx/AXFXChorusExp] objdiff: code 1920/2684 data 48/48 functions 5/7 fuzzy 91.3025 linked code 0
[libs/RVL_SDK/src/axfx/AXFXChorusExp] instruction-exact functions: 5/7
[libs/RVL_SDK/src/axfx/AXFXChorusExp]   section .sdata2 size 48 match 100.0
[libs/RVL_SDK/src/axfx/AXFXChorusExp]   section .text size 2684 match 91.302536
[libs/RVL_SDK/src/axfx/AXFXChorusExp]   below 100: __InitParams 69.9127
[libs/RVL_SDK/src/axfx/AXFXChorusExp]   below 100: __CalcLFO 68.53846
[libs/RVL_SDK/src/axfx/AXFXChorusExp] baseline: code 1920/2684 data 48 functions 5 fuzzy 91.3025
[libs/RevoEX/src/net/aes] pool: IDENTICAL
[libs/RevoEX/src/net/aes] objdiff: code 684/2752 data 2800/2800 functions 6/9 fuzzy 75.1148 linked code 0
[libs/RevoEX/src/net/aes] instruction-exact functions: 6/9
[libs/RevoEX/src/net/aes]   section .data size 200 match 100.0
[libs/RevoEX/src/net/aes]   section .rodata size 2592 match 100.0
[libs/RevoEX/src/net/aes]   section .sdata2 size 8 match 100.0
[libs/RevoEX/src/net/aes]   section .text size 2752 match 75.11482
[libs/RevoEX/src/net/aes]   below 100: AESiEncryptBlock 60.348103
[libs/RevoEX/src/net/aes]   below 100: AESiDecryptBlock 61.49004
[libs/RevoEX/src/net/aes]   below 100: NETAESCreateEx 88.98148
[libs/RevoEX/src/net/aes] baseline: code 684/2752 data 2800 functions 6 fuzzy 75.1148
regressions vs baseline: 0
global matched_code_percent: 88.09116 -> 88.09798
global fuzzy_match_percent: 99.38004 -> 99.38019
global complete_code_percent: 62.52416 -> 62.52416
global matched_data_percent: 92.11517 -> 92.11517
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
