# Data d14 attempts

Baseline origin/main checked after fetch; assigned source and symbol entries unchanged from HEAD. Baseline full build and DOL hash passed.
zkokeyp: data 96/180; instruction-exact 1/7; code 332/5200.
zprepare: data 8/68; instruction-exact 0/1; code 0/3760.
tiTextDrawer: data 1560/1608; instruction-exact 24/24; code 3476/3476.
All three pool_diff.py comparisons identical, zero strings.

## Classification
zkokeyp .data: 40-byte compiler jump table, all ten relocation addends into exact Zi8_81483118 identical; no name mismatch. extab: 56 bytes identical. extabindex: function lengths differ for Zi8_814834AC (1376 vs 1372) and Zi8GetKOcandidates (2692 vs 2676). Remaining gap is code-dependent unwind data, not an initializer or symbol extent error.
zprepare .data: 48-byte compiler jump table, all twelve relocation addends into non-exact Zi8PrepareMatch shifted -16 bytes; real code-position mismatch. extab identical; extabindex function length 3756 vs 3760. No proven data symbol rename.
tiTextDrawer .bss and .data identical; .sdata2 first 44 bytes identical. Final float literal extent absorbs four trailing alignment bytes.
Proof: lbl_81694E08 at .sdata2:0x81694E08 is loaded by lfs in beginDraw, source float 100.0f is compiler @2181 size 4 with bytes 42c80000; target extent 8 includes 00000000 alignment through unchanged split end 0x81694E10. Correct size to 4, preserve address and section total 48.

Zi8_8148302C: 1 widen table count local: objdiff 96.52542%; data 96/180; exact 1/7; ['src 0xe8 base 0xec insns 58/59', '--- replace mine 7:8 base 7:8']; reverted

Zi8_8148302C: 2 reverse local declaration order: objdiff 99.32204%; data 96/180; exact 1/7; ['src 0xec base 0xec insns 59/59', 'diffs 8: [7, 12, 14, 32, 34, 38, 44, 49]']; reverted

Zi8_8148302C: 3 typed entry character access: objdiff 93.81356%; data 96/180; exact 1/7; ['src 0xe4 base 0xec insns 57/59', '--- replace mine 6:8 base 6:8']; reverted

Zi8_81483264: 1 widen scratch index: objdiff 93.65854%; data 96/180; exact 1/7; ['src 0x9c base 0xa4 insns 39/41', '--- replace mine 6:7 base 6:7']; reverted

Zi8_81483264: 2 pointer typed scratch alias: objdiff 88.268295%; data 40/180; exact 1/7; ['src 0xac base 0xa4 insns 43/41', '--- replace mine 6:11 base 6:9']; reverted

Zi8_81483264: 3 scope loop index initialization: objdiff 91.46342%; data 96/180; exact 1/7; ['src 0xa0 base 0xa4 insns 40/41', '--- replace mine 6:7 base 6:7']; reverted

Zi8_81483308: 1 widen scratch index: objdiff 95.43104%; data 96/180; exact 1/7; ['src 0xe0 base 0xe8 insns 56/58', '--- replace mine 7:8 base 7:8']; reverted

Zi8_81483308: 2 pointer typed scratch alias: objdiff 93.10345%; data 40/180; exact 1/7; ['src 0xe4 base 0xe8 insns 57/58', '--- replace mine 6:10 base 6:9']; reverted

Zi8_81483308: 3 scope loop index initialization: objdiff 93.86207%; data 96/180; exact 1/7; ['src 0xe4 base 0xe8 insns 57/58', '--- replace mine 7:8 base 7:8']; reverted

Zi8_814833F0: 1 widen scratch index: objdiff 94.46809%; data 96/180; exact 1/7; ['src 0xb4 base 0xbc insns 45/47', '--- replace mine 6:7 base 6:7']; reverted

Zi8_814833F0: 2 pointer typed scratch alias: objdiff 89.87234%; data 40/180; exact 1/7; ['src 0xc4 base 0xbc insns 49/47', '--- replace mine 6:8 base 6:7']; reverted

Zi8_814833F0: 3 scope loop index initialization: objdiff 92.53191%; data 96/180; exact 1/7; ['src 0xb8 base 0xbc insns 46/47', '--- replace mine 6:7 base 6:7']; reverted

Zi8_814834AC: 1 initialize packed keys in narrow to wide order: objdiff 98.77551%; data 96/180; exact 1/7; ['src 0x560 base 0x55c insns 344/343', '--- replace mine 9:10 base 9:10']; reverted

Zi8_814834AC: 2 split packed keys initialization: objdiff 99.3586%; data 96/180; exact 1/7; ['src 0x560 base 0x55c insns 344/343', '--- replace mine 9:10 base 9:10']; reverted

Zi8_814834AC: 3 reverse character expression operands: objdiff 98.755104%; data 96/180; exact 1/7; ['src 0x560 base 0x55c insns 344/343', '--- replace mine 9:10 base 9:10']; reverted

Zi8GetKOcandidates: 1 chain packed keys initialization: objdiff 97.67564%; data 96/180; exact 1/7; ['src 0xa84 base 0xa74 insns 673/669', '--- delete mine 11:13 base 11:11']; reverted

Zi8GetKOcandidates: 2 reorder key pointer declarations: objdiff 97.96712%; data 96/180; exact 1/7; ['src 0xa84 base 0xa74 insns 673/669', '--- replace mine 11:13 base 11:13']; reverted

Zi8GetKOcandidates: 3 reverse key initialization order: objdiff 97.66816%; data 96/180; exact 1/7; ['src 0xa84 base 0xa74 insns 673/669', '--- delete mine 11:13 base 11:11']; reverted

Zi8PrepareMatch: 1 split element load and component assignment: objdiff 96.297874%; data 8/68; ['src 0xeac base 0xeb0 insns 939/940', '--- replace mine 11:13 base 11:13']; reverted

Zi8PrepareMatch: 2 use indexed component address expression: objdiff 96.319145%; data 8/68; ['src 0xeac base 0xeb0 insns 939/940', '--- replace mine 11:13 base 11:13']; reverted

Zi8PrepareMatch: 3 factor component length calculation into typed local: objdiff 95.607445%; data 8/68; ['src 0xeb4 base 0xeb0 insns 941/940', '--- replace mine 10:13 base 10:13']; reverted

## Final open-function audit
Zi8_8148302C: three distinct built source trials recorded above; no accepted code change.
Zi8_81483264: three distinct built source trials recorded above; no accepted code change.
Zi8_81483308: three distinct built source trials recorded above; no accepted code change.
Zi8_814833F0: three distinct built source trials recorded above; no accepted code change.
Zi8_814834AC: three distinct built source trials recorded above; no accepted code change.
Zi8GetKOcandidates: three distinct built source trials recorded above; no accepted code change.
Zi8PrepareMatch: three distinct built source trials recorded above; no accepted code change.
First four Korean helpers retain instruction counts and differ only in callee-saved register assignment. Zi8_814834AC retains an extra zero-extension and register differences. Zi8GetKOcandidates retains initialization, operand ordering, and branch/code-size differences. Zi8PrepareMatch retains code-position and instruction differences; target writes a component-present byte at stack+0xF twice but never reads it. No dummy local or forced instruction was added to reproduce those writes.
No remaining target data symbol has a proven real-name mismatch. zkokeyp and zprepare residual non-text gaps require code matching; no address or section extent was changed there. tiTextDrawer is now 1608/1608 data with all non-text sections 100%; all 24 instruction-exact functions remain exact.

## Final full gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
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
[libs/RVLMiddleware/eZiText/src/clib/zprepare] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zprepare] objdiff: code None/3760 data 8/68 functions 0/1 fuzzy 96.3191 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zprepare] instruction-exact functions: 0/1
[libs/RVLMiddleware/eZiText/src/clib/zprepare]   section .data size 48 match None
[libs/RVLMiddleware/eZiText/src/clib/zprepare]   section .text size 3760 match 96.319145
[libs/RVLMiddleware/eZiText/src/clib/zprepare]   section extab size 8 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zprepare]   section extabindex size 12 match 91.66667
[libs/RVLMiddleware/eZiText/src/clib/zprepare]   below 100: Zi8PrepareMatch 96.319145
[libs/RVLMiddleware/eZiText/src/clib/zprepare] baseline: code None/3760 data 8 functions 0 fuzzy 96.3191
[src/keyboard/tiTextDrawer] pool: IDENTICAL
[src/keyboard/tiTextDrawer] objdiff: code 3476/3476 data 1608/1608 functions 24/24 fuzzy 100.0000 linked code 3476
[src/keyboard/tiTextDrawer] instruction-exact functions: 24/24
[src/keyboard/tiTextDrawer]   section .bss size 1408 match 100.0
[src/keyboard/tiTextDrawer]   section .data size 152 match 100.0
[src/keyboard/tiTextDrawer]   section .sdata2 size 48 match 100.0
[src/keyboard/tiTextDrawer]   section .text size 3476 match 100.0
[src/keyboard/tiTextDrawer] baseline: code 3476/3476 data 1560 functions 24 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 88.57407 -> 88.57407
global fuzzy_match_percent: 99.45531 -> 99.45531
global complete_code_percent: 63.16065 -> 63.16065
global matched_data_percent: 98.18649 -> 98.18910
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: config/43U/symbols.txt (orchestrator reviews every config/symbols change)
GATE PASS
```
Full clean 43U rebuild passed; DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Regression count 0. All experimental source changes reverted. Only the proven float extent correction is retained.
