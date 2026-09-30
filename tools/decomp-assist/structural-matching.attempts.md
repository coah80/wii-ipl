# Structural matching continuation

43U only. Initial full build and DOL SHA1 pass, pools identical, regressions zero. pool_diff.py cannot inspect absent .data in memoryCard and exif; gate confirms both empty pools. Shared keyboard headers are preserved. Every entry records a compiled distinct source experiment and ctxdiff, with full diagnostics in /tmp/sol-low-attempts. Exact symbol names remain unchanged.


## libs/RVL_SDK/src/nup/nup __nupGetBootVersion__FP14ESTitleVersion
__nupGetBootVersion__FP14ESTitleVersion attempt 1: stack-frame block uses explicit local boot-version validation instead of inline helper. objdiff None%; Cross-name diagnostic only: source __nupGetBootVersion__FP14NUPContextInfoP14ESTitleVersion; target __nupGetBootVersion__FP14ESTitleVersion; insns 163/163; discarded
__nupGetBootVersion__FP14ESTitleVersion attempt 2: content traversal advances typed entry pointer in target address order. objdiff None%; Cross-name diagnostic only: source __nupGetBootVersion__FP14NUPContextInfoP14ESTitleVersion; target __nupGetBootVersion__FP14ESTitleVersion; insns 164/163; discarded
__nupGetBootVersion__FP14ESTitleVersion attempt 3: owned-title scan saves count before loop and checks that count at join. objdiff None%; Cross-name diagnostic only: source __nupGetBootVersion__FP14NUPContextInfoP14ESTitleVersion; target __nupGetBootVersion__FP14ESTitleVersion; insns 163/163; discarded

## libs/RVL_SDK/src/nup/nup __nupOp
__nupOp attempt 1: entry block initializes title pointers together after context and API buffers. objdiff 96.906395%; src 0x6d4 base 0x6d8 insns 437/438; --- replace mine 6:7 base 6:7; retained
__nupOp attempt 2: second API block tests narrowed version through explicit temporary and ternary error. objdiff 97.72831%; src 0x6e0 base 0x6d8 insns 440/438; --- replace mine 6:7 base 6:7; retained
__nupOp attempt 3: title selection uses loop-local id at each comparison. objdiff 98.8242%; src 0x6e0 base 0x6d8 insns 440/438; --- delete mine 8:9 base 8:8; retained

## libs/RVL_SDK/src/nup/nup __nupParseServerInfo__FP14NUPContextInfoPcPcUx
__nupParseServerInfo__FP14NUPContextInfoPcPcUx attempt 1: tag extraction keeps after-end cursor local to each version block. objdiff 98.108406%; src 0x710 base 0x710 insns 452/452; diffs 148: [13, 14, 15, 18, 21, 23, 26, 30, 32, 33, 34, 36, 41, 43, 44, 49, 52, 53, 56, 59]; discarded
__nupParseServerInfo__FP14NUPContextInfoPcPcUx attempt 2: parsed title version checks truncation directly without cached narrow temporary. objdiff 97.97566%; src 0x710 base 0x710 insns 452/452; diffs 157: [13, 14, 15, 18, 21, 23, 26, 30, 32, 33, 34, 36, 41, 43, 44, 49, 52, 53, 56, 59]; discarded
__nupParseServerInfo__FP14NUPContextInfoPcPcUx attempt 3: title result fields use a typed entry reference after parser calls. objdiff 97.22345%; src 0x700 base 0x710 insns 448/452; --- replace mine 13:16 base 13:16; discarded

## libs/RVL_SDK/src/nup/nup __nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc
__nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc attempt 1: request size addition follows target operand order. objdiff 99.10345%; src 0x244 base 0x244 insns 145/145; diffs 22: [6, 11, 17, 21, 33, 39, 45, 51, 54, 58, 59, 63, 64, 67, 89, 90, 99, 100, 126, 128]; discarded
__nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc attempt 2: request allocation size has separately named country length. objdiff 99.10345%; src 0x244 base 0x244 insns 145/145; diffs 22: [6, 11, 17, 21, 33, 39, 45, 51, 54, 58, 59, 63, 64, 67, 89, 90, 99, 100, 126, 128]; discarded
__nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc attempt 3: request size uses left-to-right ordinary length sum. objdiff 99.793106%; src 0x244 base 0x244 insns 145/145; diffs 5: [49, 52, 54, 58, 59]; discarded

## libs/RVL_SDK/src/nup/nup __nupBase64Encode__FPUcPUcUl
__nupBase64Encode__FPUcPUcUl attempt 1: encode blocks load first character before second to follow target schedule. objdiff 94.20635%; src 0xfc base 0xfc insns 63/63; diffs 21: [5, 9, 11, 16, 17, 18, 20, 21, 22, 23, 25, 31, 35, 38, 42, 44, 48, 52, 55, 58]; discarded
__nupBase64Encode__FPUcPUcUl attempt 2: encode loop writes first character before third lookup and resets group count after store. objdiff 94.20635%; src 0xfc base 0xfc insns 63/63; diffs 21: [5, 9, 11, 16, 17, 18, 20, 21, 22, 23, 25, 31, 35, 38, 42, 44, 48, 52, 55, 58]; discarded
__nupBase64Encode__FPUcPUcUl attempt 3: encode loop uses preincrement counter and direct first-character store. objdiff 92.22222%; src 0xfc base 0xfc insns 63/63; diffs 19: [5, 9, 11, 17, 19, 21, 23, 25, 27, 31, 35, 38, 42, 44, 48, 52, 55, 58, 59]; discarded

## libs/RVL_SDK/src/nup/nup __nupGetTitleSize__FP12NUPTitleInfo
__nupGetTitleSize__FP12NUPTitleInfo attempt 1: content block copies cid before content-presence test. objdiff 99.100716%; src 0x22c base 0x22c insns 139/139; diffs 22: [39, 40, 42, 43, 56, 57, 58, 59, 61, 62, 67, 68, 69, 71, 74, 75, 78, 80, 90, 91]; retained
__nupGetTitleSize__FP12NUPTitleInfo attempt 2: installed allocation arithmetic uses named aligned TMD size. objdiff 98.884895%; src 0x22c base 0x22c insns 139/139; diffs 25: [39, 40, 42, 43, 56, 57, 58, 59, 61, 62, 66, 67, 68, 69, 71, 72, 74, 75, 76, 78]; discarded
__nupGetTitleSize__FP12NUPTitleInfo attempt 3: title size loop advances typed TMD content cursor. objdiff 79.992805%; src 0x234 base 0x22c insns 141/139; --- replace mine 24:26 base 24:30; discarded

## libs/RVL_SDK/src/nup/nup __nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc
__nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc attempt 4: request size expression adds running sum before country call result, matching target add operands. objdiff 99.10345%; src 0x244 base 0x244 insns 145/145; diffs 22: [6, 11, 17, 21, 33, 39, 45, 51, 54, 58, 59, 63, 64, 67, 89, 90, 99, 100, 126, 128]; discarded

## libs/RVL_SDK/src/kbd/kbd_lib kbdProcKey
kbdProcKey attempt 1: stack event initializes modifiers only on getter error, avoiding redundant success store. objdiff 94.62209%; src 0x2d4 base 0x2b0 insns 181/172; --- replace mine 16:19 base 16:17; discarded
kbdProcKey attempt 2: translation block takes event modifier directly and uses event result for dispatch. objdiff 93.808136%; src 0x2ac base 0x2b0 insns 171/172; --- replace mine 6:9 base 6:9; discarded
kbdProcKey attempt 3: repeat lookup has signed bounded counter in address-order loop. objdiff 97.15116%; src 0x2b8 base 0x2b0 insns 174/172; --- replace mine 6:9 base 6:9; discarded

## libs/RVL_SDK/src/kbd/kbd_lib kbdProcMod
kbdProcMod attempt 1: stack modifier word and typed bitfield view preserve separate load/store blocks. objdiff 78.90625%; src 0x3a0 base 0x400 insns 232/256; --- replace mine 2:3 base 2:3; discarded
kbdProcMod attempt 2: getter failure fallback initializes stack modifier word while success follows target entry. objdiff 85.3125%; src 0x400 base 0x400 insns 256/256; diffs 235: [3, 5, 6, 8, 9, 10, 13, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32]; retained
kbdProcMod attempt 3: right-alt and left-shift blocks clear destination masks before inserting boolean bit. objdiff 88.18359%; src 0x408 base 0x400 insns 258/256; --- replace mine 3:4 base 3:4; retained

## libs/RVL_SDK/src/kbd/kbd_lib kbd_led_handler
kbd_led_handler attempt 1: callback status uses target conditional branch instead of switch. objdiff 39.36%; src 0x58 base 0x64 insns 22/25; --- replace mine 2:4 base 2:4; discarded
kbd_led_handler attempt 2: callback result local is passed through ternary status conversion. objdiff 39.36%; src 0x58 base 0x64 insns 22/25; --- replace mine 2:4 base 2:4; discarded
kbd_led_handler attempt 3: callback address is reloaded directly after status block, retains typed index. objdiff 39.36%; src 0x58 base 0x64 insns 22/25; --- replace mine 2:4 base 2:4; discarded

## libs/RVL_SDK/src/kbd/kbd_lib KBDSetLedsAsync
KBDSetLedsAsync attempt 1: validation block keeps full channel after bounds check, matching target multiply. objdiff 82.48148%; src 0x140 base 0x144 insns 80/81; --- replace mine 7:9 base 7:9; discarded
KBDSetLedsAsync attempt 2: return block follows target error-then-success join. objdiff 79.604935%; src 0x138 base 0x144 insns 78/81; --- replace mine 7:9 base 7:9; discarded
KBDSetLedsAsync attempt 3: reservation blocks advance typed command cursor and keep separate index. BUILD FAILED: ninja: build stopped: subcommand failed.

## libs/RVL_SDK/src/kbd/kbd_lib KBDSetLeds
KBDSetLeds attempt 1: stack/register lifetime narrows LED bits before interrupt call, keeps channel separately. objdiff 81.48101%; src 0x138 base 0x13c insns 78/79; --- insert mine 4:4 base 4:5; retained
KBDSetLeds attempt 2: clear-command block directly reloads command array after USB call and returns error first. objdiff 72.620255%; src 0x134 base 0x13c insns 77/79; --- insert mine 4:4 base 4:5; discarded
KBDSetLeds attempt 3: reservation blocks use target counted loop form and direct array at each use. objdiff 72.620255%; src 0x134 base 0x13c insns 77/79; --- insert mine 4:4 base 4:5; discarded

## libs/RVL_SDK/src/kbd/kbd_lib kbdEventHandler
kbdEventHandler attempt 1: report status is loaded once before error guard, uses named status in branch. objdiff 99.22043%; src 0x2e4 base 0x2e8 insns 185/186; --- replace mine 34:40 base 34:40; discarded
kbdEventHandler attempt 2: report status initialized before channel pointer, matching target load lifetime. objdiff 99.38172%; src 0x2e4 base 0x2e8 insns 185/186; --- replace mine 34:36 base 34:36; discarded
kbdEventHandler attempt 3: channel pointer is formed by indexed array expression rather than compound pointer addition. objdiff 99.78494%; src 0x2e8 base 0x2e8 insns 186/186; diffs 6: [35, 36, 37, 38, 39, 42]; discarded

## libs/RVL_SDK/src/kbd/kbd_lib KBDSetModState
KBDSetModState attempt 1: modifier update loads physical bitfields directly from typed channel view. objdiff 98.690475%; src 0xa8 base 0xa8 insns 42/42; diffs 7: [26, 27, 29, 30, 31, 32, 33]; discarded
KBDSetModState attempt 2: modifier update builds next flags before forming state pointer. objdiff 98.690475%; src 0xa8 base 0xa8 insns 42/42; diffs 7: [26, 27, 29, 30, 31, 32, 33]; discarded
KBDSetModState attempt 3: modifier update uses explicit union source word then physical bits. objdiff 99.40476%; src 0xa8 base 0xa8 insns 42/42; diffs 4: [30, 31, 32, 33]; retained

## libs/RVL_SDK/src/kbd/kbd_lib KBDTranslateHidCode
KBDTranslateHidCode attempt 1: lookup entry and mask have word-sized locals to match separate target registers. objdiff 99.63415%; src 0x290 base 0x290 insns 164/164; diffs 9: [44, 45, 46, 79, 81, 83, 88, 91, 102]; discarded
KBDTranslateHidCode attempt 2: key flag mask is explicitly unsigned while comparison remains identical. objdiff 98.07927%; src 0x288 base 0x290 insns 162/164; --- replace mine 44:47 base 44:48; discarded
KBDTranslateHidCode attempt 3: entry flag test computes activeFlag directly from shiftFlag and offset. objdiff 99.63415%; src 0x290 base 0x290 insns 164/164; diffs 9: [44, 45, 46, 79, 81, 83, 88, 91, 102]; discarded

## libs/RVL_SDK/src/kbd/kbd_lib KBDSetLedsAsync
KBDSetLedsAsync attempt 4: command cursor declared with other C locals, target bounded reservation loop. objdiff 84.234566%; src 0x138 base 0x144 insns 78/81; --- insert mine 7:7 base 7:8; discarded

## libs/RVL_SDK/src/nup/nup __nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc
__nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc attempt 5: country length is accumulated before adding fixed request overhead. objdiff 99.93104%; src 0x244 base 0x244 insns 145/145; diffs 2: [58, 59]; discarded
__nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc attempt 6: country length plus parenthesized running sum keeps target final add order. objdiff 99.10345%; src 0x244 base 0x244 insns 145/145; diffs 22: [6, 11, 17, 21, 33, 39, 45, 51, 54, 58, 59, 63, 64, 67, 89, 90, 99, 100, 126, 128]; discarded

## src/scene/memoryCard/iplMemoryCardManager isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl attempt 1: failure-state output is initialized by isDistSlot before all reads; no redundant stack store. objdiff 93.13559%; src 0x1d8 base 0x1d8 insns 118/118; diffs 41: [13, 14, 17, 19, 26, 28, 29, 33, 34, 35, 36, 37, 38, 41, 42, 45, 48, 51, 52, 63]; retained
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl attempt 2: entry computes file before initializing enabled result, matching target register reuse. objdiff 93.13559%; src 0x1d8 base 0x1d8 insns 118/118; diffs 41: [13, 14, 17, 19, 26, 28, 29, 33, 34, 35, 36, 37, 38, 41, 42, 45, 48, 51, 52, 63]; discarded
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl attempt 3: success and failure key blocks form destination pointer before source-key load. objdiff 86.73729%; src 0x1e8 base 0x1d8 insns 122/118; --- insert mine 13:13 base 13:14; discarded
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl attempt 4: retranslate success guards as address-ordered basic blocks with shared failure join. objdiff 91.65254%; src 0x1d8 base 0x1d8 insns 118/118; diffs 38: [13, 14, 17, 19, 26, 28, 34, 35, 36, 37, 38, 39, 41, 45, 51, 52, 63, 71, 73, 76]; discarded

## src/scene/memoryCard/iplMemoryCardManager isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl attempt 1: failure-state output is initialized by isDistSlot before all reads; no redundant stack store. objdiff 93.13559%; src 0x1d8 base 0x1d8 insns 118/118; diffs 41: [13, 14, 17, 19, 26, 28, 29, 33, 34, 35, 36, 37, 38, 41, 42, 45, 48, 51, 52, 63]; retained
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl attempt 2: entry computes file before initializing enabled result, matching target register reuse. objdiff 93.13559%; src 0x1d8 base 0x1d8 insns 118/118; diffs 41: [13, 14, 17, 19, 26, 28, 29, 33, 34, 35, 36, 37, 38, 41, 42, 45, 48, 51, 52, 63]; discarded
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl attempt 3: success and failure key blocks form destination pointer before source-key load. objdiff 86.73729%; src 0x1e8 base 0x1d8 insns 122/118; --- insert mine 13:13 base 13:14; discarded
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl attempt 4: retranslate success guards as address-ordered basic blocks with shared failure join. objdiff 91.65254%; src 0x1d8 base 0x1d8 insns 118/118; diffs 38: [13, 14, 17, 19, 26, 28, 34, 35, 36, 37, 38, 39, 41, 45, 51, 52, 63, 71, 73, 76]; discarded

## src/scene/memoryCard/iplMemoryCardManager update_icon_anm__Q33ipl5scene17MemoryCardManagerFv
update_icon_anm__Q33ipl5scene17MemoryCardManagerFv attempt 1: counter block retains word sum until signed halfword comparison. objdiff 96.96429%; src 0x14c base 0x150 insns 83/84; --- replace mine 10:11 base 10:11; retained
update_icon_anm__Q33ipl5scene17MemoryCardManagerFv attempt 2: upper-bound ping-pong block reads max directly from original icon array. objdiff 98.27381%; src 0x14c base 0x150 insns 83/84; --- replace mine 29:30 base 29:30; retained
update_icon_anm__Q33ipl5scene17MemoryCardManagerFv attempt 3: wrap and lower-bound blocks share typed cell pointer after counter sum. objdiff 91.940475%; src 0x154 base 0x150 insns 85/84; --- replace mine 0:1 base 0:1; discarded

## src/scene/memoryCard/iplMemoryCardManager create_icon__Q33ipl5scene17MemoryCardManagerFUcs
create_icon__Q33ipl5scene17MemoryCardManagerFUcs attempt 1: frame blocks load counter once before loop and sign-extend frame for duration shift. objdiff 86.17647%; src 0xcc base 0xcc insns 51/51; diffs 19: [16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 29, 30, 34, 36, 38, 39, 42]; discarded
create_icon__Q33ipl5scene17MemoryCardManagerFUcs attempt 2: duration block uses signed postincrement frame directly as target. objdiff 86.17647%; src 0xcc base 0xcc insns 51/51; diffs 19: [16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 29, 30, 34, 36, 38, 39, 42]; discarded
create_icon__Q33ipl5scene17MemoryCardManagerFUcs attempt 3: loop retains typed icon state and counter across duration accumulation. objdiff 86.17647%; src 0xcc base 0xcc insns 51/51; diffs 19: [16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 29, 30, 34, 36, 38, 39, 42]; discarded

## src/scene/memoryCard/iplMemoryCardManager isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs
isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs attempt 1: banner flag read directly as return expression. objdiff 92.30769%; src 0x68 base 0x68 insns 26/26; diffs 8: [11, 12, 13, 14, 15, 16, 17, 18]; discarded
isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs attempt 2: banner flag local widens to word before bool return. objdiff 92.30769%; src 0x68 base 0x68 insns 26/26; diffs 8: [11, 12, 13, 14, 15, 16, 17, 18]; discarded
isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs attempt 3: banner flag lookup uses typed row then direct file index. objdiff 92.30769%; src 0x68 base 0x68 insns 26/26; diffs 8: [11, 12, 13, 14, 15, 16, 17, 18]; discarded

## src/scene/memoryCard/iplMemoryCardManager update_file_array__Q33ipl5scene17MemoryCardManagerFUc
update_file_array__Q33ipl5scene17MemoryCardManagerFUc attempt 1: range guard uses separately declared unsigned command. objdiff 99.72222%; src 0x168 base 0x168 insns 90/90; diffs 4: [15, 16, 17, 20]; discarded
update_file_array__Q33ipl5scene17MemoryCardManagerFUc attempt 2: range guard is inline member expression with preserved subtraction form. objdiff 99.72222%; src 0x168 base 0x168 insns 90/90; diffs 4: [15, 16, 17, 20]; discarded
update_file_array__Q33ipl5scene17MemoryCardManagerFUc attempt 3: range guard follows explicit signed upper and lower bounds. objdiff 97.5%; src 0x16c base 0x168 insns 91/90; --- replace mine 16:20 base 16:19; discarded

## src/scene/memoryCard/iplMemoryCardManager _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl
_create_icon__Q33ipl5scene17MemoryCardManagerFUcsl attempt 1: format block retains loaded signed format value across mutually exclusive checks. objdiff 87.55%; src 0x190 base 0x190 insns 100/100; diffs 37: [19, 20, 22, 23, 24, 34, 39, 40, 42, 44, 45, 46, 47, 48, 57, 59, 63, 64, 65, 66]; discarded
_create_icon__Q33ipl5scene17MemoryCardManagerFUcsl attempt 2: RGB and CI blocks share texture destination while palette reload stays direct. objdiff 65.63%; src 0x178 base 0x190 insns 94/100; --- replace mine 0:1 base 0:1; discarded
_create_icon__Q33ipl5scene17MemoryCardManagerFUcsl attempt 3: CI block names palette destination after texture initializer call. objdiff 87.55%; src 0x190 base 0x190 insns 100/100; diffs 37: [19, 20, 22, 23, 24, 34, 39, 40, 42, 44, 45, 46, 47, 48, 57, 59, 63, 64, 65, 66]; discarded

## src/scene/memoryCard/iplMemoryCardManager getComment__Q33ipl5scene17MemoryCardManagerFUcsi
getComment__Q33ipl5scene17MemoryCardManagerFUcsi attempt 1: comment entry uses signed short file index then full typed destination. objdiff 89.9187%; src 0x1f0 base 0x1ec insns 124/123; --- replace mine 5:12 base 5:15; discarded
getComment__Q33ipl5scene17MemoryCardManagerFUcsi attempt 2: ASCII trim uses single decrementing read/write pointer. objdiff 97.34146%; src 0x1e4 base 0x1ec insns 121/123; --- replace mine 10:11 base 10:11; discarded
getComment__Q33ipl5scene17MemoryCardManagerFUcsi attempt 3: line-termination scan uses local character after count check. objdiff 98.94309%; src 0x1ec base 0x1ec insns 123/123; diffs 20: [10, 12, 14, 19, 20, 21, 23, 24, 45, 46, 48, 49, 51, 62, 66, 67, 86, 90, 91, 117]; discarded

## src/scene/memoryCard/iplMemoryCardManager create_banner__Q33ipl5scene17MemoryCardManagerFUcs
create_banner__Q33ipl5scene17MemoryCardManagerFUcs attempt 1: banner format block retains one signed load before RGB and CI guards. objdiff 90.42453%; src 0x1a8 base 0x1a8 insns 106/106; diffs 70: [5, 6, 9, 11, 14, 16, 17, 18, 19, 23, 24, 25, 26, 27, 32, 33, 34, 35, 36, 37]; discarded
create_banner__Q33ipl5scene17MemoryCardManagerFUcs attempt 2: banner initialization shares typed texture destination after validity checks. objdiff 62.792454%; src 0x178 base 0x1a8 insns 94/106; --- replace mine 0:1 base 0:1; discarded
create_banner__Q33ipl5scene17MemoryCardManagerFUcs attempt 3: banner CI block forms palette destination after initializer, reloads source offset directly. objdiff 90.42453%; src 0x1a8 base 0x1a8 insns 106/106; diffs 70: [5, 6, 9, 11, 14, 16, 17, 18, 19, 23, 24, 25, 26, 27, 32, 33, 34, 35, 36, 37]; discarded

## src/scene/memoryCard/iplMemoryCardManager getBlocks__Q33ipl5scene17MemoryCardManagerFUcs
getBlocks__Q33ipl5scene17MemoryCardManagerFUcs attempt 1: directory entry uses explicit signed file number local. objdiff 92.0%; src 0x64 base 0x64 insns 25/25; diffs 9: [11, 12, 13, 14, 15, 16, 17, 18, 19]; discarded
getBlocks__Q33ipl5scene17MemoryCardManagerFUcs attempt 2: directory entry uses row-local pointer and typed file reference. objdiff 92.0%; src 0x64 base 0x64 insns 25/25; diffs 9: [11, 12, 13, 14, 15, 16, 17, 18, 19]; discarded
getBlocks__Q33ipl5scene17MemoryCardManagerFUcs attempt 3: directory size uses word local before halfword return. objdiff 92.0%; src 0x64 base 0x64 insns 25/25; diffs 9: [11, 12, 13, 14, 15, 16, 17, 18, 19]; discarded

## src/keyboard/tiZiString clearCandidates__Q39textinput8tistring6WithZiFv
clearCandidates__Q39textinput8tistring6WithZiFv attempt 1: entry names real buffer pointers before dictionary guard, stack frame first. objdiff 83.34568%; src 0x140 base 0x144 insns 80/81; --- replace mine 3:6 base 3:4; discarded
clearCandidates__Q39textinput8tistring6WithZiFv attempt 2: clear blocks use typed indexed subarrays, search output indexes wchar view. objdiff 91.049385%; src 0x150 base 0x144 insns 84/81; --- insert mine 4:4 base 4:6; discarded
clearCandidates__Q39textinput8tistring6WithZiFv attempt 3: search-parameter block forms real buffer pointers before virtual language call. objdiff 91.049385%; src 0x150 base 0x144 insns 84/81; --- insert mine 4:4 base 4:6; discarded

## src/keyboard/tiZiString update__Q39textinput8tistring6WithZiFv
update__Q39textinput8tistring6WithZiFv attempt 1: entry retains real candidate output pointer before setElementBuffer call. objdiff 91.70852%; src 0x6fc base 0x6f8 insns 447/446; --- replace mine 7:8 base 7:8; retained
update__Q39textinput8tistring6WithZiFv attempt 2: phone-key blocks index true candidate slots directly and reload holding key after writes. objdiff 90.92601%; src 0x700 base 0x6f8 insns 448/446; --- replace mine 7:8 base 7:8; discarded
update__Q39textinput8tistring6WithZiFv attempt 3: context copy is explicit source/destination pointer loop in target block order. objdiff 89.53363%; src 0x6e4 base 0x6f8 insns 441/446; --- replace mine 7:8 base 7:8; discarded

## src/keyboard/tiZiString partialConfirmForKR__Q39textinput8tistring6WithZiFv
partialConfirmForKR__Q39textinput8tistring6WithZiFv attempt 1: leading-letter scan has its own initialized index separate from final scan. objdiff 99.4898%; src 0x24c base 0x24c insns 147/147; diffs 12: [63, 65, 67, 69, 74, 79, 84, 89, 94, 99, 104, 105]; discarded
partialConfirmForKR__Q39textinput8tistring6WithZiFv attempt 2: leading-letter scan initializes bounded index in loop initializer after table pointer. objdiff 99.4898%; src 0x24c base 0x24c insns 147/147; diffs 12: [63, 65, 67, 69, 74, 79, 84, 89, 94, 99, 104, 105]; discarded
partialConfirmForKR__Q39textinput8tistring6WithZiFv attempt 3: leading-letter scan uses indexed ordinary table access instead of moving pointer. objdiff 99.4898%; src 0x24c base 0x24c insns 147/147; diffs 12: [63, 65, 67, 69, 74, 79, 84, 89, 94, 99, 104, 105]; discarded

## src/keyboard/tiZiString setElementBuffer__Q39textinput8tistring6WithZiFv
setElementBuffer__Q39textinput8tistring6WithZiFv attempt 1: element copy pointers are formed after target clear blocks. objdiff 89.87692%; src 0x104 base 0x104 insns 65/65; diffs 22: [5, 7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 18, 20, 29, 36, 46, 49, 50, 51, 52]; retained
setElementBuffer__Q39textinput8tistring6WithZiFv attempt 2: element copy index is zero-extended word while count remains full word. objdiff 87.815384%; src 0x104 base 0x104 insns 65/65; diffs 24: [5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 20, 29, 36, 46, 49, 50]; discarded
setElementBuffer__Q39textinput8tistring6WithZiFv attempt 3: element conversion block uses typed reference after loaded source character. objdiff 87.815384%; src 0x104 base 0x104 insns 65/65; diffs 24: [5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 20, 29, 36, 46, 49, 50]; discarded

## src/keyboard/tiZiString setCurrentWord__Q39textinput8tistring6WithZiFPCw
setCurrentWord__Q39textinput8tistring6WithZiFPCw attempt 1: word copy has target separate source pointer, source index and destination index. objdiff 94.82143%; src 0xdc base 0xe0 insns 55/56; --- replace mine 13:14 base 13:14; retained
setCurrentWord__Q39textinput8tistring6WithZiFPCw attempt 2: word copy retains typed destination array base and separate index. objdiff 94.64286%; src 0xdc base 0xe0 insns 55/56; --- replace mine 13:14 base 13:14; discarded
setCurrentWord__Q39textinput8tistring6WithZiFPCw attempt 3: word copy uses signed independent indices for target indexed accesses. objdiff 94.82143%; src 0xdc base 0xe0 insns 55/56; --- replace mine 13:14 base 13:14; discarded

## libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse TMCJPEGDEC_IFD0_tag_parse
TMCJPEGDEC_IFD0_tag_parse attempt 1: pixel dimensions retranslated as SHORT block then LONG block, decode only selected type. objdiff 93.60707%; src 0x790 base 0x784 insns 484/481; --- replace mine 0:1 base 0:1; retained
TMCJPEGDEC_IFD0_tag_parse attempt 2: ignored tags each terminate own switch block in target decision order. objdiff 92.75468%; src 0x7a0 base 0x784 insns 488/481; --- replace mine 0:1 base 0:1; discarded
TMCJPEGDEC_IFD0_tag_parse attempt 3: tag decoder keeps zero-extended signed selector for target compare tree. objdiff 93.29522%; src 0x7a0 base 0x784 insns 488/481; --- replace mine 0:1 base 0:1; discarded

## libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse TMCJPEGDEC_exif_parse
TMCJPEGDEC_exif_parse attempt 1: header and entry-count decode use common byte-order primitive like target load order. objdiff 98.113205%; src 0x350 base 0x350 insns 212/212; diffs 58: [7, 27, 28, 30, 31, 32, 34, 61, 69, 70, 72, 73, 74, 76, 77, 79, 80, 82, 86, 89]; discarded
TMCJPEGDEC_exif_parse attempt 2: three IFD traversal blocks share cursor/count locals to target stack register lifetimes. objdiff 98.679245%; src 0x350 base 0x350 insns 212/212; diffs 46: [7, 27, 28, 30, 31, 32, 34, 61, 69, 70, 72, 73, 74, 76, 77, 79, 80, 82, 86, 89]; retained
TMCJPEGDEC_exif_parse attempt 3: IFD setup subtracts count header before entry-size multiply in target schedule. objdiff 98.679245%; src 0x350 base 0x350 insns 212/212; diffs 46: [7, 27, 28, 30, 31, 32, 34, 61, 69, 70, 72, 73, 74, 76, 77, 79, 80, 82, 86, 89]; discarded

## libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse TMCJPEGDEC_IFD1_tag_parse
TMCJPEGDEC_IFD1_tag_parse attempt 1: decision tree explicitly accounts for ignored FlashPix color and dimension tags. objdiff 92.421486%; src 0x3d0 base 0x3c8 insns 244/242; --- replace mine 9:15 base 9:15; retained
TMCJPEGDEC_IFD1_tag_parse attempt 2: ignored thumbnail tags each end their own switch block before shared default. objdiff 86.818184%; src 0x41c base 0x3c8 insns 263/242; --- replace mine 9:15 base 9:15; discarded
TMCJPEGDEC_IFD1_tag_parse attempt 3: rational denominator blocks reload thumbnail base and add offset-plus-four. objdiff 87.024796%; src 0x41c base 0x3c8 insns 263/242; --- replace mine 9:15 base 9:15; discarded

## libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse TMCJPEGDEC_IFD0_tag_parse
TMCJPEGDEC_IFD0_tag_parse attempt 4: IFD0 selector widens after read to signed word, preserves existing ignored-tag group. objdiff 93.83576%; src 0x790 base 0x784 insns 484/481; --- replace mine 0:1 base 0:1; retained
TMCJPEGDEC_IFD0_tag_parse attempt 5: IFD0 SHORT/LONG type widens after read to unsigned word. objdiff 93.88566%; src 0x78c base 0x784 insns 483/481; --- replace mine 0:1 base 0:1; retained
TMCJPEGDEC_IFD0_tag_parse attempt 6: IFD0 ignored-tag group reaches common function exit through switch break. objdiff 94.241165%; src 0x784 base 0x784 insns 481/481; diffs 446: [0, 2, 3, 4, 5, 7, 10, 11, 12, 13, 14, 15, 16, 18, 19, 20, 21, 22, 23, 24]; retained

## libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse TMCJPEGDEC_IFD1_tag_parse
TMCJPEGDEC_IFD1_tag_parse attempt 4: IFD1 ignored-tag group reaches common exit through switch break. objdiff 91.694214%; src 0x3bc base 0x3c8 insns 239/242; --- replace mine 9:11 base 9:11; discarded
TMCJPEGDEC_IFD1_tag_parse attempt 5: IFD1 retains original recognized tags and uses common switch exit. objdiff 93.099174%; src 0x3bc base 0x3c8 insns 239/242; --- replace mine 9:11 base 9:11; retained
TMCJPEGDEC_IFD1_tag_parse attempt 6: all IFD1 case bodies converge through single function exit. objdiff 93.099174%; src 0x3bc base 0x3c8 insns 239/242; --- replace mine 9:11 base 9:11; discarded

## libs/RVL_SDK/src/nup/nup __nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc
__nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc attempt 7: variable-sized request subtotal before fixed XML overhead. objdiff 99.17242%; src 0x244 base 0x244 insns 145/145; diffs 22: [6, 11, 17, 21, 33, 39, 45, 51, 54, 58, 59, 63, 64, 67, 89, 90, 99, 100, 126, 128]; discarded
__nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc attempt 8: request subtotal groups accumulated lengths and fixed overhead on right. objdiff 99.17242%; src 0x244 base 0x244 insns 145/145; diffs 22: [6, 11, 17, 21, 33, 39, 45, 51, 54, 58, 59, 63, 64, 67, 89, 90, 99, 100, 126, 128]; discarded
__nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc attempt 9: fixed request overhead is first operand before country length. objdiff 99.93104%; src 0x244 base 0x244 insns 145/145; diffs 1: [58]; discarded
__nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc attempt 10: request size uses country result plus existing request length, then fixed overhead. objdiff 99.06896%; src 0x244 base 0x244 insns 145/145; diffs 22: [6, 11, 17, 21, 33, 39, 45, 51, 54, 58, 59, 63, 64, 67, 89, 90, 99, 100, 126, 128]; discarded

## src/keyboard/tiZiString partialConfirmForKR__Q39textinput8tistring6WithZiFv
partialConfirmForKR__Q39textinput8tistring6WithZiFv attempt 4: ordinary inline leading-letter lookup variation 1. objdiff 100.0%; src 0x24c base 0x24c insns 147/147; diffs 0: []; retained
partialConfirmForKR__Q39textinput8tistring6WithZiFv attempt 5: ordinary inline leading-letter lookup variation 2. BUILD FAILED: ninja: build stopped: subcommand failed.
partialConfirmForKR__Q39textinput8tistring6WithZiFv attempt 6: ordinary inline leading-letter lookup variation 3. BUILD FAILED: ninja: build stopped: subcommand failed.

## src/keyboard/tiZiString setCurrentWord__Q39textinput8tistring6WithZiFPCw
setCurrentWord__Q39textinput8tistring6WithZiFPCw attempt 4: word copy reads by retained result count rather than redundant separate index. objdiff 94.96429%; src 0xdc base 0xe0 insns 55/56; --- replace mine 13:14 base 13:14; retained
setCurrentWord__Q39textinput8tistring6WithZiFPCw attempt 5: word copy writes by retained total-length index and increments after store. objdiff 86.66071%; src 0xe0 base 0xe0 insns 56/56; diffs 21: [13, 15, 18, 24, 30, 31, 32, 33, 34, 35, 37, 38, 39, 40, 41, 42, 43, 44, 47, 50]; discarded

## Final coverage and acceptance

32 initially open functions; 114 compiled source attempts; minimum three per function. Failed builds excluded.
Korean partial confirmation: 100.0% objdiff, 147/147 instructions, ctxdiff differences zero.
Removed unused sourceOffset after selecting result-count indexing; remaining setCurrentWord code generation unchanged.
All five pools identical; full build and DOL SHA1 pass; regressions, forbidden additions and readability warnings zero.
Detailed final metrics, remaining functions, diagnostic limitations and gate output: structural-matching.final.md.
Final per-function disassembly differences: structural-matching.ctxdiff.md.
