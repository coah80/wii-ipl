# sol-med matching attempts

43U only. All trials built only the owned object. Scores are structural/exact instruction differences; retained trial candidates were provisional. All fuzzy-only candidates were restored before final verification.

Baseline gate: NWC24Download instruction-exact 18/30, code 4172/12496, data 80/80; nup 17/23, code 5164/10764, data 1720/1720; iplSetting instruction-exact 104/112, objdiff 105/112, code 30532/37884, data 1040/5696. All pools identical.

## Structural diagnosis from target asm and ctxdiff

libs/RevoEX/src/nwc24/NWC24Download NWC24InitDlTask | src 0x240 base 0x240 insns 144/144 | diffs 31: [5, 7, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 26, 31, 32]
libs/RevoEX/src/nwc24/NWC24Download NWC24SetDlInterval | src 0x24c base 0x24c insns 147/147 | diffs 3: [126, 127, 137]
libs/RevoEX/src/nwc24/NWC24Download NWC24IterateDlTask | src 0x138 base 0x13c insns 78/79 | --- replace mine 22:24 base 22:24
libs/RevoEX/src/nwc24/NWC24Download NWC24IterateDlTaskEx | src 0x244 base 0x244 insns 145/145 | diffs 17: [8, 15, 25, 26, 28, 29, 31, 32, 43, 56, 57, 58, 83, 87, 103, 120, 130]
libs/RevoEX/src/nwc24/NWC24Download NWC24UpdateDlTask | src 0x3dc base 0x3f4 insns 247/253 | --- replace mine 0:1 base 0:1
libs/RevoEX/src/nwc24/NWC24Download NWC24AddDlTask | src 0x248 base 0x23c insns 146/143 | --- delete mine 6:7 base 6:6
libs/RevoEX/src/nwc24/NWC24Download NWC24GetDlTask | src 0x170 base 0x170 insns 92/92 | diffs 5: [4, 6, 60, 64, 73]
libs/RevoEX/src/nwc24/NWC24Download NWC24PurgeOldestDlTask | src 0x2ac base 0x2c0 insns 171/176 | --- replace mine 9:10 base 9:11
libs/RevoEX/src/nwc24/NWC24Download NWC24ManageDlTaskListForMenu | src 0x258 base 0x260 insns 150/152 | --- replace mine 18:19 base 18:19
libs/RevoEX/src/nwc24/NWC24Download NWC24ExtendDlTaskList | src 0x224 base 0x224 insns 137/137 | diffs 4: [122, 124, 126, 128]
libs/RevoEX/src/nwc24/NWC24Download NWC24iCheckDlHeaderConsistency | src 0x350 base 0x350 insns 212/212 | diffs 3: [5, 6, 7]
libs/RevoEX/src/nwc24/NWC24Download AddTaskInternal | src 0x634 base 0x644 insns 397/401 | --- replace mine 58:59 base 58:59
libs/RVL_SDK/src/nup/nup __nupParseServerInfo__FP14NUPContextInfoPcPcUx | src 0x710 base 0x710 insns 452/452 | diffs 148: [13, 14, 15, 18, 21, 23, 26, 30, 32, 33, 34, 36, 41, 43, 44, 49, 52, 53, 56, 59]
libs/RVL_SDK/src/nup/nup __nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc | src 0x244 base 0x244 insns 145/145 | diffs 1: [58]
libs/RVL_SDK/src/nup/nup __nupBase64Encode__FPUcPUcUl | src 0xfc base 0xfc insns 63/63 | diffs 21: [5, 9, 11, 16, 17, 18, 20, 21, 22, 23, 25, 31, 35, 38, 42, 44, 48, 52, 55, 58]
libs/RVL_SDK/src/nup/nup __nupGetBootVersion__FP14ESTitleVersion |  | symbol absent from built object
libs/RVL_SDK/src/nup/nup __nupGetTitleSize__FP12NUPTitleInfo | src 0x22c base 0x22c insns 139/139 | diffs 22: [39, 40, 42, 43, 56, 57, 58, 59, 61, 62, 67, 68, 69, 71, 74, 75, 78, 80, 90, 91]
libs/RVL_SDK/src/nup/nup __nupOp | src 0x6e0 base 0x6d8 insns 440/438 | --- delete mine 8:9 base 8:8
src/scene/setting/iplSetting createBrowser__Q33ipl5scene7SettingFv | src 0x4ac base 0x4b4 insns 299/301 | --- replace mine 0:1 base 0:1
src/scene/setting/iplSetting draw__Q33ipl5scene7SettingFv | src 0x958 base 0x9e0 insns 598/632 | --- replace mine 18:19 base 18:19
src/scene/setting/iplSetting initKeyboard__Q33ipl5scene7SettingFPCc | src 0x350 base 0x354 insns 212/213 | --- replace mine 8:9 base 8:9
src/scene/setting/iplSetting calcKeyboard__Q33ipl5scene7SettingFv | src 0x484 base 0x488 insns 289/290 | --- replace mine 11:12 base 11:12
src/scene/setting/iplSetting convertRevIP__Q33ipl5scene7SettingFPUcPCc | src 0x124 base 0x124 insns 73/73 | diffs 21: [6, 8, 12, 15, 16, 17, 18, 19, 21, 28, 29, 30, 36, 38, 45, 46, 47, 48, 50, 64]
src/scene/setting/iplSetting scanAP__Q33ipl5scene7SettingFv | src 0x428 base 0x440 insns 266/272 | --- replace mine 7:8 base 7:8
src/scene/setting/iplSetting setUSBAP__Q33ipl5scene7SettingFv | src 0xe0 base 0xe4 insns 56/57 | --- replace mine 8:9 base 8:9

Trials: structural/exact differences, with only verified improvements kept.
__nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc | country length temporary | (0, 1) -> (0, 22) | restored
NWC24SetDlInterval | task pointer before work and header | (0, 3) -> (0, 3) | restored
NWC24ExtendDlTaskList | reuse task identifier scope for close result | (0, 4) -> BUILD FAIL | restored
NWC24iCheckDlHeaderConsistency | move task pointer initialization ahead of aliases | (2, 3) -> (2, 3) | restored
__nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc | reverse compound operand | (0, 1) -> (0, 22) | restored
__nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc | split country size expression | (0, 1) -> (0, 22) | restored
__nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc | named country length before compound addition | (0, 1) -> (0, 0) | kept
NWC24ManageDlTaskListForMenu | nested success preserves removal result boundary | (12, 36) -> (12, 36) | restored
NWC24iCheckDlHeaderConsistency | task pointer before argument aliases declarations | (2, 3) -> (2, 20) | restored
NWC24ExtendDlTaskList | common close result uses operation result | (0, 4) -> (0, 4) | restored
createBrowser__Q33ipl5scene7SettingFv | separate direct page seven from default | (15, 114) -> (14, 111) | kept
initKeyboard__Q33ipl5scene7SettingFPCc | use manager getter across inline helper boundaries | (18, 183) -> (4, 195) | kept
setUSBAP__Q33ipl5scene7SettingFv | preserve owner nickname BOOL result | (7, 21) -> (9, 23) | restored
NWC24SetDlInterval | scoped final identifier temporary | (0, 3) -> (0, 3) | restored
NWC24SetDlInterval | final identifier declared before task pointer | (0, 3) -> (0, 3) | restored
NWC24ExtendDlTaskList | close and load status share lifetime | (0, 4) -> (0, 4) | restored
NWC24iCheckDlHeaderConsistency | direct local task use in inline helpers | (2, 3) -> (5, 6) | restored
createBrowser__Q33ipl5scene7SettingFv | move direct page path declaration before search loop | (14, 111) -> (14, 111) | restored
createBrowser__Q33ipl5scene7SettingFv | local heap size declarations before initial allocation | (14, 111) -> (14, 117) | restored
initKeyboard__Q33ipl5scene7SettingFPCc | keyboard limits reordered by lifetime | (4, 195) -> (6, 195) | restored
initKeyboard__Q33ipl5scene7SettingFPCc | setting fields assigned in declaration order | (4, 195) -> (5, 195) | restored
setUSBAP__Q33ipl5scene7SettingFv | guard completion with early switch exit | (7, 21) -> (7, 21) | restored
setUSBAP__Q33ipl5scene7SettingFv | materialize completion flag | (7, 21) -> (7, 21) | restored
scanAP__Q33ipl5scene7SettingFv | materialize animation state in int | (56, 165) -> (56, 165) | restored
scanAP__Q33ipl5scene7SettingFv | animation index before state store | (56, 165) -> BUILD FAIL | restored
scanAP__Q33ipl5scene7SettingFv | store animation BOOL before branch | (56, 165) -> BUILD FAIL | restored
NWC24SetDlInterval | restore timestamp inline helper boundary | (0, 3) -> (0, 8) | restored
NWC24InitDlTask | high and low identifiers scoped after parsing | (0, 31) -> BUILD FAIL | restored
NWC24InitDlTask | direct header getter for initial validation | (0, 31) -> (0, 31) | restored
NWC24InitDlTask | scope group identifier validation through task helper | (0, 31) -> (0, 31) | restored
NWC24IterateDlTask | for loop with first condition instead of do while | (3, 50) -> (5, 20) | restored
NWC24IterateDlTask | unsigned task identifier widened before loop | (3, 50) -> (12, 48) | restored
NWC24IterateDlTask | cache entry header only after loop check | (3, 50) -> BUILD FAIL | restored
NWC24IterateDlTaskEx | selected identifier temporary before result stores | (2, 17) -> (8, 104) | restored
NWC24IterateDlTaskEx | descending signed flag form | (2, 17) -> (2, 17) | restored
NWC24IterateDlTaskEx | callback declaration after candidate flags | (2, 17) -> (2, 14) | kept
NWC24UpdateDlTask | operation time helper common result exit | (25, 249) -> (28, 252) | restored
NWC24UpdateDlTask | retry loop uses explicit call and break | (25, 249) -> (34, 250) | restored
NWC24UpdateDlTask | scope task identifier before time query | (25, 249) -> BUILD FAIL | restored
NWC24AddDlTask | use explicit next time helper return status | (5, 140) -> (5, 140) | restored
NWC24AddDlTask | scope next timestamp after universal time query | (5, 140) -> BUILD FAIL | restored
NWC24AddDlTask | group universal time success with timestamp assignment | (5, 140) -> (6, 139) | restored
NWC24GetDlTask | task destination alias before file declaration | (0, 5) -> (0, 5) | restored
NWC24GetDlTask | scoped identifier for seek and read | (0, 5) -> BUILD FAIL | restored
NWC24GetDlTask | read status as conditional value | (0, 5) -> (0, 5) | restored
NWC24GetDlTask | read helper as whole function body | (0, 5) -> (0, 5) | restored
NWC24iCheckDlHeaderConsistency | task pointer declared after argument copies | (2, 3) -> (2, 20) | restored
NWC24IterateDlTask | loop entry through common condition label | (3, 50) -> (5, 20) | restored
NWC24InitDlTask | reorder scalar initialization stores | (0, 31) -> (2, 31) | restored
NWC24UpdateDlTask | result declaration before task and time declarations | (25, 249) -> (25, 249) | restored
NWC24AddDlTask | scope interval conversion after multiplication | (5, 140) -> (5, 140) | restored
NWC24ManageDlTaskListForMenu | shared read and remove result common success exit | (12, 36) -> (15, 46) | restored
NWC24ManageDlTaskListForMenu | removal destination uses initialized task pointer | (12, 36) -> (15, 137) | restored
NWC24ManageDlTaskListForMenu | scope count and task locals by declaration lifetime | (12, 36) -> (12, 36) | restored
NWC24PurgeOldestDlTask | done handling at shared final exit | (33, 166) -> (32, 167) | kept
NWC24PurgeOldestDlTask | read and remove common status return | (32, 167) -> (33, 165) | restored
NWC24PurgeOldestDlTask | swap selected task and destination declaration order | (32, 167) -> (32, 167) | restored
AddTaskInternal | URL pointer kept across inline string validation | (36, 328) -> (37, 337) | restored
AddTaskInternal | nested success path for URL checks | (36, 328) -> (41, 324) | restored
AddTaskInternal | URL scheme failure normalized at common exit | (36, 328) -> (39, 328) | restored
AddTaskInternal | retry condition in loop header in inline update | (36, 328) -> (27, 328) | kept
AddTaskInternal | access-time status through separate local | (27, 328) -> (27, 327) | kept
AddTaskInternal | candidate retry mask operand order | (27, 327) -> (27, 327) | restored
NWC24InitDlTask | initialize cached header before path parsing | (0, 31) -> (0, 31) | restored
NWC24InitDlTask | initialize task pointer at declaration | (0, 31) -> (0, 31) | restored
NWC24SetDlInterval | widen shared task identifier | (0, 3) -> (1, 3) | restored
NWC24SetDlInterval | separate validation and final entry identifier lifetimes | (0, 3) -> (0, 3) | restored
NWC24UpdateDlTask | shift mask first in bitwise test | (25, 249) -> (25, 249) | restored
NWC24iCheckDlHeaderConsistency | order argument copy declarations after stack pointer | (2, 3) -> (2, 3) | restored
__nupBase64Encode__FPUcPUcUl | first and second output direct assignments | (9, 21) -> (9, 21) | restored
__nupBase64Encode__FPUcPUcUl | first character temporary declared before second | (9, 21) -> (9, 21) | restored
__nupBase64Encode__FPUcPUcUl | count before value declaration | (9, 21) -> (9, 27) | restored
__nupParseServerInfo__FP14NUPContextInfoPcPcUx | end pointer declared before start pointer | (0, 148) -> (0, 148) | restored
__nupParseServerInfo__FP14NUPContextInfoPcPcUx | scope value pointer temporary before output writes | (0, 148) -> (0, 148) | restored
__nupParseServerInfo__FP14NUPContextInfoPcPcUx | sequential guards instead of compound short circuit | (0, 148) -> (83, 471) | restored
__nupGetTitleSize__FP12NUPTitleInfo | progress update after first size rounding | (0, 22) -> (11, 29) | restored
__nupGetTitleSize__FP12NUPTitleInfo | content size uses saved descriptor | (0, 22) -> (15, 82) | restored
__nupGetTitleSize__FP12NUPTitleInfo | content existence result scoped before branch | (0, 22) -> (0, 22) | restored
__nupOp | uninitialized boot version removed initial zero only via query initialization | (7, 429) -> (7, 429) | restored
__nupBase64Encode__FPUcPUcUl | direct four alphabet lookups in output order | (9, 21) -> (8, 17) | kept
__nupBase64Encode__FPUcPUcUl | pointer increments for encoded characters | (8, 17) -> (19, 43) | restored
__nupBase64Encode__FPUcPUcUl | count and value use unsigned long locals | (8, 17) -> (8, 17) | restored
NWC24IterateDlTaskEx | found declaration before callback pointer | (2, 14) -> (2, 3) | kept
NWC24ExtendDlTaskList | initialize close result in closing scope | (0, 4) -> (0, 4) | restored
__nupBase64Encode__FPUcPUcUl | accumulator shift and input as one expression | (8, 17) -> (8, 19) | restored
__nupBase64Encode__FPUcPUcUl | output first character through scoped byte temporary | (8, 17) -> (8, 17) | restored
__nupBase64Encode__FPUcPUcUl | consume count before next group after first store | (8, 17) -> (8, 17) | restored
NWC24IterateDlTaskEx | read comparison identifier before selected value store | (2, 3) -> (0, 0) | kept
setUSBAP__Q33ipl5scene7SettingFv | signed completion byte comparison | (7, 21) -> (8, 21) | restored
convertRevIP__Q33ipl5scene7SettingFPUcPCc | index declared ahead of component locals | (0, 21) -> (0, 21) | restored
convertRevIP__Q33ipl5scene7SettingFPUcPCc | component start and output pointer declarations reversed | (0, 21) -> (0, 21) | restored
convertRevIP__Q33ipl5scene7SettingFPUcPCc | component value with common saturation expression | (0, 21) -> (6, 54) | restored
draw__Q33ipl5scene7SettingFv | texture rectangles local order follows calls | (123, 334) -> (120, 570) | kept
draw__Q33ipl5scene7SettingFv | initialize each texture and LOD together | (120, 570) -> (120, 570) | restored
draw__Q33ipl5scene7SettingFv | side rectangle floats initialized in target order | (120, 570) -> (126, 571) | restored
__nupGetBootVersion__FP14ESTitleVersion | owned title comparison uses requested title first | (0, 17) -> (0, 17) | restored; ABI uses context and title but original symbol encodes title only
__nupGetBootVersion__FP14ESTitleVersion | view pointer declaration before operation result | (0, 17) -> (0, 17) | restored; ABI uses context and title but original symbol encodes title only
__nupGetBootVersion__FP14ESTitleVersion | title search while loop with explicit next index | (0, 17) -> (0, 17) | restored; ABI uses context and title but original symbol encodes title only
calcKeyboard__Q33ipl5scene7SettingFv | default cases initialize form text instead of entry | (37, 251) -> (79, 211) | restored
calcKeyboard__Q33ipl5scene7SettingFv | explicit valid form switch instead of range checks | (37, 251) -> (24, 253) | kept
calcKeyboard__Q33ipl5scene7SettingFv | vacancy success branch first | (24, 253) -> (17, 253) | kept
scanAP__Q33ipl5scene7SettingFv | bool compared with false at call boundary | (56, 165) -> (56, 165) | restored
__nupOp | boot version overflow uses explicit error branch | (7, 429) -> (4, 56) | kept
scanAP__Q33ipl5scene7SettingFv | animation state scalar outside switch | (56, 165) -> (56, 165) | restored
scanAP__Q33ipl5scene7SettingFv | animation index scalar outside switch | (56, 165) -> (26, 160) | kept
__nupOp | current title equality operand order | (4, 56) -> (4, 56) | restored
__nupOp | title descriptor search count cached for loop | (4, 56) -> (22, 221) | restored
createBrowser__Q33ipl5scene7SettingFv | direct path pointer declared at entry | (14, 111) -> (14, 111) | restored
initKeyboard__Q33ipl5scene7SettingFPCc | zero limits initialized in default case | (4, 195) -> (18, 158) | restored
convertRevIP__Q33ipl5scene7SettingFPUcPCc | leading declarations with preserved assignment lifetimes | (0, 21) -> (0, 10) | kept
convertRevIP__Q33ipl5scene7SettingFPUcPCc | output pointer initialized at declaration | (0, 10) -> (2, 18) | restored
convertRevIP__Q33ipl5scene7SettingFPUcPCc | index initialization before component start | (0, 10) -> (0, 8) | kept
convertRevIP__Q33ipl5scene7SettingFPUcPCc | named component buffer pointer across parse calls | (0, 8) -> (9, 51) | restored

## /tmp/sol-init-decl

declaration block:
      char homePath[64] = {0};
      u32 nwc24IdHigh;
      u32 nwc24IdLow;
      DlTaskData* task;
      DlTaskListHeader* header;
      NWC24Err result;
      BOOL allowed;
      BOOL useContentFile;
start (0, 31)
best (0, 31) after 71 builds; source restored; best order was:
    char homePath[64] = {0};
    u32 nwc24IdHigh;
    u32 nwc24IdLow;
    DlTaskData* task;
    DlTaskListHeader* header;
    NWC24Err result;
    BOOL allowed;
    BOOL useContentFile;

## /tmp/sol-parse-decl

declaration block:
      s32 result = 0;
      char* start;
      char* afterEnd;
      char* cursor;
      size_t valueLength;
      size_t titleCount;
start (0, 148)
best (0, 148) after 36 builds; source restored; best order was:
    s32 result = 0;
    char* start;
    char* afterEnd;
    char* cursor;
    size_t valueLength;
    size_t titleCount;

## /tmp/sol-convert-decl

declaration block:
              char ascii[20];
              int componentStart;
              u8* output;
              int index;
              int count = 0;
start (0, 10)
best (0, 10) after 23 builds; source restored; best order was:
            char ascii[20];
            int componentStart;
            u8* output;
            int index;
            int count = 0;

Register-only declaration searches: SetDlInterval 71 builds, GetDlTask 13 builds, ExtendDlTaskList 23 builds, all restored without improvement.

Gate caveat: setUpdate_NoUpdateDialog_ is objdiff 100.0; odiff.dis reads the first operand of a CR1 conditional branch as its target, causing two address-dependent false differences. No change to this byte-exact function or to gate tools. Boot-version original symbol encodes only ESTitleVersion but its assembly receives context in r3 and title in r4. The readable source preserves both parameters; renaming or pinning symbols was excluded.

Final attempt audit: all 23 remaining objdiff-nonmatching functions have at least three distinct compiled source trials.

## Final remaining functions

NWC24InitDlTask | 98.923615% | register allocation, 144/144 instructions
NWC24SetDlInterval | 99.89796% | final identifier register, 147/147 instructions
NWC24IterateDlTask | 95.0% | loop entry branch and temporaries, 78/79 instructions
NWC24UpdateDlTask | 94.17391% | stack frame and inline result/retry boundaries, 247/253 instructions
NWC24AddDlTask | 97.552444% | timestamp helper lifetimes and extra branches, 146/143 instructions
NWC24GetDlTask | 99.728264% | destination and identifier saved registers, 92/92 instructions
NWC24PurgeOldestDlTask | 85.829544% | iteration initialization and removal helper boundaries, 171/176 instructions
NWC24ManageDlTaskListForMenu | 96.74342% | removal helper result boundary, 150/152 instructions
NWC24ExtendDlTaskList | 99.85401% | closing status saved register, 137/137 instructions
NWC24iCheckDlHeaderConsistency | 98.77358% | entry assignment scheduling, 212/212 instructions
AddTaskInternal | 93.57855% | URL and retry helper boundaries and candidate loop branches, 397/401 instructions
__nupParseServerInfo__FP14NUPContextInfoPcPcUx | 98.108406% | inline tag helper register allocation, 452/452 instructions
__nupBase64Encode__FPUcPUcUl | 94.20635% | lookup/store scheduling and count lifetime, 63/63 instructions
__nupGetBootVersion__FP14ESTitleVersion | None / no original-name symbol | original name missing; actual two-parameter ABI preserved; alternate-name body has 17 register differences
__nupGetTitleSize__FP12NUPTitleInfo | 99.100716% | 64-bit accumulation scheduling and content helper registers, 139/139 instructions
__nupOp | 98.8242% | boot version conversion branches and local initialization/lifetimes, 440/438 instructions
createBrowser__Q33ipl5scene7SettingFv | 98.8505% | stack frame, direct-page switch and local lifetimes, 299/301 instructions
draw__Q33ipl5scene7SettingFv | 91.03639% | texture/rectangle local layout, inline boundaries and render-mode copy, 598/632 instructions
initKeyboard__Q33ipl5scene7SettingFPCc | 93.30986% | manager getter boundaries and defined defaults, 212/213 instructions
calcKeyboard__Q33ipl5scene7SettingFv | 92.42069% | form dispatch, pointer lifetimes and vacancy branch, 289/290 instructions
convertRevIP__Q33ipl5scene7SettingFPUcPCc | 98.15069% | register allocation, 73/73 instructions
scanAP__Q33ipl5scene7SettingFv | 94.5625% | animation boolean materialization and argument/store order, 266/272 instructions
setUSBAP__Q33ipl5scene7SettingFv | 98.070175% | target reloads completion byte, ours forwards first load, 56/57 instructions

Final source changes only: NWC24IterateDlTaskEx and __nupGetServerInfo, each objdiff 100.0, 145/145 instructions and ctxdiff diffs 0. All three pool_diff.py runs identical, NWC24Download 3 strings, nup 28 strings, iplSetting 108 strings. Raw bytes of setUpdate_NoUpdateDialog_ independently equal despite the gate decoder caveat. No source changes retained in iplSetting.

Source commits: 15d4e4b5, 4f34eabc. Final full gate follows.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24Download] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Download] objdiff: code 4752/12496 data 80/80 functions 19/30 fuzzy 97.3566 linked code 0
[libs/RevoEX/src/nwc24/NWC24Download] instruction-exact functions: 19/30
[libs/RevoEX/src/nwc24/NWC24Download]   section .data size 56 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .text size 12496 match 97.3566
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24InitDlTask 98.923615
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24SetDlInterval 99.89796
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24IterateDlTask 95.0
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24UpdateDlTask 94.17391
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24AddDlTask 97.552444
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24GetDlTask 99.728264
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24PurgeOldestDlTask 85.829544
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24ManageDlTaskListForMenu 96.74342
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24ExtendDlTaskList 99.85401
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCheckDlHeaderConsistency 98.77358
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: AddTaskInternal 93.57855
[libs/RevoEX/src/nwc24/NWC24Download] baseline: code 4172/12496 data 80 functions 18 fuzzy 97.2654
[libs/RVL_SDK/src/nup/nup] pool: IDENTICAL
[libs/RVL_SDK/src/nup/nup] objdiff: code 5744/10764 data 1720/1720 functions 18/23 fuzzy 93.2516 linked code 0
[libs/RVL_SDK/src/nup/nup] instruction-exact functions: 18/23
[libs/RVL_SDK/src/nup/nup]   section .data size 1592 match 100.0
[libs/RVL_SDK/src/nup/nup]   section .rodata size 88 match 100.0
[libs/RVL_SDK/src/nup/nup]   section .sbss size 8 match 100.0
[libs/RVL_SDK/src/nup/nup]   section .sdata size 32 match 100.0
[libs/RVL_SDK/src/nup/nup]   section .text size 10764 match 93.25158
[libs/RVL_SDK/src/nup/nup]   below 100: __nupParseServerInfo__FP14NUPContextInfoPcPcUx 98.108406
[libs/RVL_SDK/src/nup/nup]   below 100: __nupBase64Encode__FPUcPUcUl 94.20635
[libs/RVL_SDK/src/nup/nup]   below 100: __nupGetBootVersion__FP14ESTitleVersion None
[libs/RVL_SDK/src/nup/nup]   below 100: __nupGetTitleSize__FP12NUPTitleInfo 99.100716
[libs/RVL_SDK/src/nup/nup]   below 100: __nupOp 98.8242
[libs/RVL_SDK/src/nup/nup] baseline: code 5164/10764 data 1720 functions 17 fuzzy 93.2479
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 30532/37884 data 1040/5696 functions 105/112 fuzzy 98.8008 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 104/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match 32.25412
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 98.80076
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 98.8505
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 91.03639
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 93.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 92.42069
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 94.5625
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 98.070175
[src/scene/setting/iplSetting] baseline: code 30532/37884 data 1040 functions 105 fuzzy 98.8008
regressions vs baseline: 0
global matched_code_percent: 86.76230 -> 86.80102
global fuzzy_match_percent: 99.31232 -> 99.31272
global complete_code_percent: 60.61288 -> 60.61288
global matched_data_percent: 91.11031 -> 91.11031
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
