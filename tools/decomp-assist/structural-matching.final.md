# Structural matching final evidence

All 32 initially open functions have at least three distinct compiled source experiments; 114 compiled attempts are recorded. Failed builds do not count. One additional function is exact. Thirty-one remain open. Shared headers and configure.py were not changed.

## Before and after

| Unit | Exact objdiff functions | Matched code bytes | Matched data bytes | Fuzzy percent |
| --- | --- | --- | --- | --- |
| libs/RVL_SDK/src/nup/nup | 17 -> 17 / 23 | 5164 -> 5164 / 10764 | 1720 -> 1720 / 1720 | 92.89669 -> 93.24786 |
| libs/RVL_SDK/src/kbd/kbd_lib | 13 -> 13 / 21 | 1744 -> 1744 / 5764 | 3992 -> 3992 / 5296 | 93.70091 -> 96.35184 |
| src/scene/memoryCard/iplMemoryCardManager | 16 -> 16 / 26 | 2032 -> 2032 / 5396 | not present | 95.71090 -> 96.10749 |
| src/keyboard/tiZiString | 24 -> 25 / 29 | 2324 -> 2912 / 5504 | 7680 -> 7680 / 7680 | 95.52398 -> 96.10247 |
| libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse | 3 -> 3 / 6 | 1348 -> 1348 / 5088 | not present | 92.70361 -> 96.28931 |

## Remaining functions in object address order

__nupParseServerInfo__FP14NUPContextInfoPcPcUx: 98.108406%; instructions 452/452; operand/register allocation differs; 148 ctxdiff differences; 3 compiled attempts.
__nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc: 99.93104%; instructions 145/145; operand/register allocation differs; 1 ctxdiff differences; 10 compiled attempts.
__nupBase64Encode__FPUcPUcUl: 94.20635%; instructions 63/63; instruction scheduling/selection and register allocation differ; 21 ctxdiff differences; 3 compiled attempts.
__nupGetBootVersion__FP14ESTitleVersion: unavailable%; instructions 163/163; source/target signature mismatch prevents exact-name comparison; cross-name 17 instruction differences; 3 compiled attempts.
__nupGetTitleSize__FP12NUPTitleInfo: 99.100716%; instructions 139/139; operand/register allocation differs; 22 ctxdiff differences; 3 compiled attempts.
__nupOp: 98.8242%; instructions 440/438; instruction count and block scheduling differ; 3 compiled attempts.
kbdEventHandler: 99.83871%; instructions 186/186; operand/register allocation differs; 5 ctxdiff differences; 3 compiled attempts.
kbdProcKey: 97.5%; instructions 174/172; instruction count and block scheduling differ; 3 compiled attempts.
kbdProcMod: 93.18359%; instructions 261/256; instruction count and block scheduling differ; 3 compiled attempts.
kbd_led_handler: 70.0%; instructions 24/25; instruction count and block scheduling differ; 3 compiled attempts.
KBDSetLedsAsync: 90.69136%; instructions 84/81; instruction count and block scheduling differ; 3 compiled attempts.
KBDSetLeds: 81.48101%; instructions 78/79; instruction count and block scheduling differ; 3 compiled attempts.
KBDSetModState: 99.40476%; instructions 42/42; operand/register allocation differs; 4 ctxdiff differences; 3 compiled attempts.
KBDTranslateHidCode: 99.63415%; instructions 164/164; operand/register allocation differs; 9 ctxdiff differences; 3 compiled attempts.
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl: 93.13559%; instructions 118/118; instruction scheduling/selection and register allocation differ; 41 ctxdiff differences; 4 compiled attempts.
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl: 93.13559%; instructions 118/118; instruction scheduling/selection and register allocation differ; 41 ctxdiff differences; 4 compiled attempts.
isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs: 92.30769%; instructions 26/26; instruction scheduling/selection and register allocation differ; 8 ctxdiff differences; 3 compiled attempts.
update_icon_anm__Q33ipl5scene17MemoryCardManagerFv: 98.27381%; instructions 83/84; instruction count and block scheduling differ; 3 compiled attempts.
update_file_array__Q33ipl5scene17MemoryCardManagerFUc: 99.72222%; instructions 90/90; operand/register allocation differs; 4 ctxdiff differences; 3 compiled attempts.
create_icon__Q33ipl5scene17MemoryCardManagerFUcs: 86.84314%; instructions 50/51; instruction count and block scheduling differ; 3 compiled attempts.
_create_icon__Q33ipl5scene17MemoryCardManagerFUcsl: 87.55%; instructions 100/100; instruction scheduling/selection and register allocation differ; 37 ctxdiff differences; 3 compiled attempts.
getComment__Q33ipl5scene17MemoryCardManagerFUcsi: 98.94309%; instructions 123/123; operand/register allocation differs; 20 ctxdiff differences; 3 compiled attempts.
create_banner__Q33ipl5scene17MemoryCardManagerFUcs: 90.42453%; instructions 106/106; instruction scheduling/selection and register allocation differ; 70 ctxdiff differences; 3 compiled attempts.
getBlocks__Q33ipl5scene17MemoryCardManagerFUcs: 92.0%; instructions 25/25; instruction scheduling/selection and register allocation differ; 9 ctxdiff differences; 3 compiled attempts.
clearCandidates__Q39textinput8tistring6WithZiFv: 91.049385%; instructions 84/81; instruction count and block scheduling differ; 3 compiled attempts.
update__Q39textinput8tistring6WithZiFv: 91.70852%; instructions 447/446; instruction count and block scheduling differ; 3 compiled attempts.
setElementBuffer__Q39textinput8tistring6WithZiFv: 89.87692%; instructions 65/65; instruction scheduling/selection and register allocation differ; 22 ctxdiff differences; 3 compiled attempts.
setCurrentWord__Q39textinput8tistring6WithZiFPCw: 94.96429%; instructions 55/56; instruction count and block scheduling differ; 5 compiled attempts.
TMCJPEGDEC_exif_parse: 98.679245%; instructions 212/212; operand/register allocation differs; 46 ctxdiff differences; 3 compiled attempts.
TMCJPEGDEC_IFD0_tag_parse: 94.241165%; instructions 481/481; instruction scheduling/selection and register allocation differ; 446 ctxdiff differences; 6 compiled attempts.
TMCJPEGDEC_IFD1_tag_parse: 93.099174%; instructions 239/242; instruction count and block scheduling differ; 6 compiled attempts.

## Verification limits

KBDResetChannel is 100% in objdiff, but the gate counts 12/21 keyboard instruction-exact functions rather than 13/21. ctxdiff treats the condition-register operand as a branch destination: indices 5 and 26 have identical raw instruction words 4086000c and 4186000c, respectively. Original/source function offsets differ by 32 bytes. The gate and ctxdiff were preserved.

The target boot-version symbol omits the context argument present in the source signature. Assembly uses both arguments. The function was not renamed, and no exact match is claimed.

kbd .data bytes are physically identical, but jump-table relocation matching remains below 100%; the reported 3992/5296 matched data bytes are unchanged. Memory-card and EXIF objects have no data sections. The full DOL hash passes; this does not establish that any unlinked unit is fully matched.

Memory-card destinationState is assigned through isDistSlot before every read. isDistSlot assigns its non-null out parameter unconditionally before returning. No uninitialized value is consumed.

## Files changed

libs/RVL_SDK/src/nup/nup.cpp
libs/RVL_SDK/src/kbd/kbd_lib.c
src/scene/memoryCard/iplMemoryCardManager.cpp
src/keyboard/tiZiString.cpp
libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse.c
tools/decomp-assist/structural-matching.attempts.md
tools/decomp-assist/structural-matching.ctxdiff.md
tools/decomp-assist/structural-matching.final.md

## Source commits

```text
faa734ec match korean leading letter lookup
4c02833c align exif tag decoding blocks
98ba65f2 align zi buffer and word copy lifetimes
4d29665d align memory card validation and counters
5288b266 align keyboard modifier and led blocks
1378c3d6 align nup title and version lifetimes
```

## Final full gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/nup/nup] pool: IDENTICAL
[libs/RVL_SDK/src/nup/nup] objdiff: code 5164/10764 data 1720/1720 functions 17/23 fuzzy 93.2479 linked code 0
[libs/RVL_SDK/src/nup/nup] instruction-exact functions: 17/23
[libs/RVL_SDK/src/nup/nup]   section .data size 1592 match 100.0
[libs/RVL_SDK/src/nup/nup]   section .rodata size 88 match 100.0
[libs/RVL_SDK/src/nup/nup]   section .sbss size 8 match 100.0
[libs/RVL_SDK/src/nup/nup]   section .sdata size 32 match 100.0
[libs/RVL_SDK/src/nup/nup]   section .text size 10764 match 93.24786
[libs/RVL_SDK/src/nup/nup]   below 100: __nupParseServerInfo__FP14NUPContextInfoPcPcUx 98.108406
[libs/RVL_SDK/src/nup/nup]   below 100: __nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc 99.93104
[libs/RVL_SDK/src/nup/nup]   below 100: __nupBase64Encode__FPUcPUcUl 94.20635
[libs/RVL_SDK/src/nup/nup]   below 100: __nupGetBootVersion__FP14ESTitleVersion None
[libs/RVL_SDK/src/nup/nup]   below 100: __nupGetTitleSize__FP12NUPTitleInfo 99.100716
[libs/RVL_SDK/src/nup/nup]   below 100: __nupOp 98.8242
[libs/RVL_SDK/src/nup/nup] baseline: code 5164/10764 data 1720 functions 17 fuzzy 92.8967
[libs/RVL_SDK/src/kbd/kbd_lib] pool: IDENTICAL
[libs/RVL_SDK/src/kbd/kbd_lib] objdiff: code 1744/5764 data 3992/5296 functions 13/21 fuzzy 96.3518 linked code 0
[libs/RVL_SDK/src/kbd/kbd_lib] instruction-exact functions: 12/21
[libs/RVL_SDK/src/kbd/kbd_lib]   section .bss size 3968 match 100.0
[libs/RVL_SDK/src/kbd/kbd_lib]   section .data size 1304 match 84.024574
[libs/RVL_SDK/src/kbd/kbd_lib]   section .sbss size 16 match 100.0
[libs/RVL_SDK/src/kbd/kbd_lib]   section .sdata size 8 match 100.0
[libs/RVL_SDK/src/kbd/kbd_lib]   section .text size 5764 match 96.35184
[libs/RVL_SDK/src/kbd/kbd_lib]   below 100: kbdEventHandler 99.83871
[libs/RVL_SDK/src/kbd/kbd_lib]   below 100: kbdProcKey 97.5
[libs/RVL_SDK/src/kbd/kbd_lib]   below 100: kbdProcMod 93.18359
[libs/RVL_SDK/src/kbd/kbd_lib]   below 100: kbd_led_handler 70.0
[libs/RVL_SDK/src/kbd/kbd_lib]   below 100: KBDSetLedsAsync 90.69136
[libs/RVL_SDK/src/kbd/kbd_lib]   below 100: KBDSetLeds 81.48101
[libs/RVL_SDK/src/kbd/kbd_lib]   below 100: KBDSetModState 99.40476
[libs/RVL_SDK/src/kbd/kbd_lib]   below 100: KBDTranslateHidCode 99.63415
[libs/RVL_SDK/src/kbd/kbd_lib] baseline: code 1744/5764 data 3992 functions 13 fuzzy 93.7009
[src/scene/memoryCard/iplMemoryCardManager] pool: IDENTICAL
[src/scene/memoryCard/iplMemoryCardManager] objdiff: code 2032/5396 data None/None functions 16/26 fuzzy 96.1075 linked code 0
[src/scene/memoryCard/iplMemoryCardManager] instruction-exact functions: 16/26
[src/scene/memoryCard/iplMemoryCardManager]   section .text size 5396 match 96.10749
[src/scene/memoryCard/iplMemoryCardManager]   below 100: isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl 93.13559
[src/scene/memoryCard/iplMemoryCardManager]   below 100: isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl 93.13559
[src/scene/memoryCard/iplMemoryCardManager]   below 100: isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs 92.30769
[src/scene/memoryCard/iplMemoryCardManager]   below 100: update_icon_anm__Q33ipl5scene17MemoryCardManagerFv 98.27381
[src/scene/memoryCard/iplMemoryCardManager]   below 100: update_file_array__Q33ipl5scene17MemoryCardManagerFUc 99.72222
[src/scene/memoryCard/iplMemoryCardManager]   below 100: create_icon__Q33ipl5scene17MemoryCardManagerFUcs 86.84314
[src/scene/memoryCard/iplMemoryCardManager]   below 100: _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl 87.55
[src/scene/memoryCard/iplMemoryCardManager]   below 100: getComment__Q33ipl5scene17MemoryCardManagerFUcsi 98.94309
[src/scene/memoryCard/iplMemoryCardManager]   below 100: create_banner__Q33ipl5scene17MemoryCardManagerFUcs 90.42453
[src/scene/memoryCard/iplMemoryCardManager]   below 100: getBlocks__Q33ipl5scene17MemoryCardManagerFUcs 92.0
[src/scene/memoryCard/iplMemoryCardManager] baseline: code 2032/5396 data None functions 16 fuzzy 95.7109
[src/keyboard/tiZiString] pool: IDENTICAL
[src/keyboard/tiZiString] objdiff: code 2912/5504 data 7680/7680 functions 25/29 fuzzy 96.1025 linked code 0
[src/keyboard/tiZiString] instruction-exact functions: 25/29
[src/keyboard/tiZiString]   section .bss size 7296 match 100.0
[src/keyboard/tiZiString]   section .data size 328 match 100.0
[src/keyboard/tiZiString]   section .rodata size 56 match 100.0
[src/keyboard/tiZiString]   section .text size 5504 match 96.10247
[src/keyboard/tiZiString]   below 100: clearCandidates__Q39textinput8tistring6WithZiFv 91.049385
[src/keyboard/tiZiString]   below 100: update__Q39textinput8tistring6WithZiFv 91.70852
[src/keyboard/tiZiString]   below 100: setElementBuffer__Q39textinput8tistring6WithZiFv 89.87692
[src/keyboard/tiZiString]   below 100: setCurrentWord__Q39textinput8tistring6WithZiFPCw 94.96429
[src/keyboard/tiZiString] baseline: code 2324/5504 data 7680 functions 24 fuzzy 95.5240
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] objdiff: code 1348/5088 data None/None functions 3/6 fuzzy 96.2893 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] instruction-exact functions: 3/6
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   section .text size 5088 match 96.28931
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_exif_parse 98.679245
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD0_tag_parse 94.241165
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD1_tag_parse 93.099174
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] baseline: code 1348/5088 data None functions 3 fuzzy 92.7036
regressions vs baseline: 0
global matched_code_percent: 86.00588 -> 86.02551
global fuzzy_match_percent: 98.74086 -> 98.75509
global complete_code_percent: 59.99415 -> 59.99415
global matched_data_percent: 90.86673 -> 90.86673
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
