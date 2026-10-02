# rt7 fuzzy lane
Baseline HEAD 1994d24f06dd864b04864cae6c34df2d30636f33; origin/main 1994d24f06dd864b04864cae6c34df2d30636f33
src/scene/channelSelect/iplChannelSelect {'fuzzy_match_percent': 99.76344, 'total_code': '25668', 'matched_code': '24736', 'matched_code_percent': 96.36902, 'total_data': '2336', 'matched_data': '2336', 'matched_data_percent': 100.0, 'total_functions': 102, 'matched_functions': 101, 'matched_functions_percent': 99.01961, 'total_units': 1}
POOL IDENTICAL up to 98 (mine=98 base=98)

libs/RevoEX/src/nhttp/NHTTP_recvbuf {'fuzzy_match_percent': 96.36407, 'total_code': '1692', 'matched_code': '1196', 'matched_code_percent': 70.68558, 'matched_data_percent': 100.0, 'total_functions': 7, 'matched_functions': 6, 'matched_functions_percent': 85.71429, 'complete_data_percent': 100.0, 'total_units': 1}
POOL IDENTICAL up to 0 (mine=0 base=0)

libs/NW4R/src/ut/ut_ArchiveFontBase {'fuzzy_match_percent': 98.46797, 'total_code': '5120', 'matched_code': '4164', 'matched_code_percent': 81.328125, 'total_data': '96', 'matched_data': '96', 'matched_data_percent': 100.0, 'total_functions': 23, 'matched_functions': 22, 'matched_functions_percent': 95.652176, 'total_units': 1}
POOL IDENTICAL up to 0 (mine=0 base=0)


http 1 enclose valid range, branch bge: (22, 64), insns 124/124

http 2 keep raw read int, compare token first: (16, 88), insns 123/124

http 3 raw read int, response first comparison: (18, 48), insns 123/124

http 4 token lowercase ternary, token first: (18, 48), insns 123/124

http 5 both lowercase ternaries: (12, 40), insns 124/124

http 6 reverse equality operands of ternaries: (4, 5), insns 124/124

http 7 bounds leading locals: (4, 5), insns 124/124

http 8 bounds after initial character: /src/nhttp/NHTTP_recvbuf.o
FAILED: [code=2] build/43U/src/libs/RevoEX/src/nhttp/NHTTP_recvbuf.o 
build/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RevoEX/src/nhttp/NHTTP_recvbuf.c -o build/43U/src/libs/RevoEX/src/nhttp && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RevoEX/src/nhttp/NHTTP_recvbuf.d build/43U/src/libs/RevoEX/src/nhttp/NHTTP_recvbuf.d
### mwcceppc.exe Compiler:
#    File: libs\RevoEX\src\nhttp\NHTTP_recvbuf.c
# ----------------------------------------------
#      83:     int lowerBound = 'A'; 
#   Error:     ^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


http 9 precompute lastPosition before initial read: (5, 33), insns 124/124

http 10/11 termination predicate order ('position==limit-1', '*token==0', "*token==' '", '*token==delimiter'): (14, 16), insns 124/124

http 10/11 termination predicate order ('*token==delimiter', '*token==0', "*token==' '", 'position==limit-1'): (14, 72), insns 125/124

http 12 character type u8: (9, 74), insns 126/124

http 12 character type s32: (4, 5), insns 124/124

http 12 character type char: (10, 74), insns 125/124

http 13 ternary inline helper retains operand order: (4, 5), insns 124/124

channel 1 swap bottom/top projection division source order: (23, 68), insns 233/233

channel 2 horizontal expression before vertical expression: (36, 64), insns 233/233

channel 3 declare position before extent: (38, 73), insns 233/233

font 1 calculate flag stride after flag offset: (26, 97), insns 239/239

font 2 load glyph/block counts after flags offset calculation: (26, 97), insns 239/239

font 3 const font read view: (26, 87), insns 239/239

http 14 cache token: (24, 76), insns 125/124

http 14 cache signed delimiter: (7, 65), insns 124/124

http 14 cache bounds before block: (4, 5), insns 124/124

http 14 initial token lowercase: (42, 116), insns 138/124

font 4 consolidate function locals before implementation: (41, 114), insns 239/239

Structural diagnosis: ChannelSelect frame/instruction count identical (233), initial projection bottom/top operand order and zoom expression scheduling diverge; no immediate stack reload evidence for volatile. NHTTP compare frame 0x20 vs target 0x30 and 126 vs124 instructions; early return inversion, raw character width, ternary lowercase and comparison operand order reduce to five constant-scheduling differences at identical 124 instructions/frame 0x30. Font GLGR frame/count identical (239), surviving offset calculation scheduling plus inline helper register choices, no volatile reload evidence. All three data measures are already 100%, so no symbol rename/extent corrections justified. Origin/main source of owned units identical to HEAD on fetch.
HTTP declaration search: six orders, best structural4 exact5; restored. Font initial declaration search:13 orders no improvement.

http 15 reverse range test order: (14, 82), insns 124/124

http 16 char literal cast bounds: (4, 5), insns 124/124

http 17 inline boundary local token lower result: (68, 63), insns 124/124

http 18 replace return in body by break flag: (9, 119), insns 125/124

http 19 for loop increment expression: (4, 5), insns 124/124

http 20 do loop explicit mismatch exit: (68, 63), insns 124/124

http 21 initial read for loop clause: (4, 5), insns 124/124

font 5 offset helper expand typed intermediates: (42, 92), insns 239/239

font 6 reverse flags base addition operand: (41, 91), insns 239/239

font 7 const helper glgr views: (41, 91), insns 239/239

http 22 move locals into valid range block: (4, 5), insns 124/124

http 23 normalize lowercase with inverted test: (60, 111), insns 127/124

http 24 split initial char declaration initializer: : [code=2] build/43U/src/libs/RevoEX/src/nhttp/NHTTP_recvbuf.o 
build/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RevoEX/src/nhttp/NHTTP_recvbuf.c -o build/43U/src/libs/RevoEX/src/nhttp && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RevoEX/src/nhttp/NHTTP_recvbuf.d build/43U/src/libs/RevoEX/src/nhttp/NHTTP_recvbuf.d
### mwcceppc.exe Compiler:
#    File: libs\RevoEX\src\nhttp\NHTTP_recvbuf.c
# ----------------------------------------------
#      81:     int character=ReadHeaderChar(response,&block,&offset); 
#   Error:     ^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


font 8 remaining workspace before sheet reads: (31, 99), insns 239/239

font 9 remaining workspace before flags calculation: (31, 99), insns 239/239

font 10 compute stride between size and scratch calculation: (26, 97), insns 239/239

font 11 const view restricted to metadata calculations: mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -Cpp_exceptions off -lang=c++ -MMD -c libs/NW4R/src/ut/ut_ArchiveFontBase.cpp -o build/43U/src/libs/NW4R/src/ut && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/NW4R/src/ut/ut_ArchiveFontBase.d build/43U/src/libs/NW4R/src/ut/ut_ArchiveFontBase.d
### mwcceppc.exe Compiler:
#    File: libs\NW4R\src\ut\ut_ArchiveFontBase.cpp
# ------------------------------------------------
#     386:                 pGlgr = &fontView->glgr; 
#   Error:                                        ^
#   (10209) illegal implicit conversion from 'const 
#   nw4r::ut::HeaderedGlyphGroups *' to
#   'nw4r::ut::HeaderedGlyphGroups *'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


Font expanded declaration search 160 builds: best structural41 exact91; no exact gain, restored baseline. Channel six-local declaration search36 builds: structural23 exact68 no gain, restored baseline. All three open functions have at least three distinct source-level attempts. HTTP retained readable ternary inline lowercase, raw int read with signed-char comparison, valid-range enclosure. Final HTTP ctxdiff pending: best five scheduled loop invariant instructions, no operand/value/control-flow mismatch; does not meet instruction-exact handoff. No data edits: each owned unit data is100%.

http 25 explicit inline lowercase helper: (4, 5), insns 124/124

http 26 const lowercase argument: (4, 5), insns 124/124

http 27 conditional result local: (30, 46), insns 125/124

Final audit: ChannelSelect attempts1 projection order,2 horizontal/vertical expression order,3 position/extent declaration order plus36 declaration-search builds. ArchiveFontBase attempts1 flag stride placement,2 glyph/block count load order,3 const read view,4 consolidated locals,5 typed helper expansion,6 pointer addition operands,7 const helper views,8/9 workspace load placement,10 stride placement,11 const metadata view;160 declaration-search builds plus13 initial. NHTTP attempts1-27 cover valid-range branch, raw char type, comparison operands, lowercase ternaries/helper boundary, bounds/termination caching, loop forms, local scopes and inline/const helper. No owned open function is untried. Every data section already100%; no missing symbol pairing, no justified extent change.
Quick gate: PASS, DOL26116613f624061ba99c8d1a299aaa6efa85670d, regressions0, forbidden0, readability0; HTTP fuzzy87.59677->97.32258 with exact6/7 unchanged. Full gate in progress; no exact-gain acceptance claimed.

Final non-quick full gate:
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/channelSelect/iplChannelSelect] pool: IDENTICAL
[src/scene/channelSelect/iplChannelSelect] objdiff: code 24736/25668 data 2336/2336 functions 101/102 fuzzy 99.7634 linked code 0
[src/scene/channelSelect/iplChannelSelect] instruction-exact functions: 101/102
[src/scene/channelSelect/iplChannelSelect]   section .data size 2144 match 100.0
[src/scene/channelSelect/iplChannelSelect]   section .rodata size 16 match 100.0
[src/scene/channelSelect/iplChannelSelect]   section .sbss size 8 match 100.0
[src/scene/channelSelect/iplChannelSelect]   section .sdata size 80 match 100.0
[src/scene/channelSelect/iplChannelSelect]   section .sdata2 size 88 match 100.0
[src/scene/channelSelect/iplChannelSelect]   section .text size 25668 match 99.76344
[src/scene/channelSelect/iplChannelSelect]   below 100: setChannelScissor__Q33ipl5scene13ChannelSelectCFPCQ33ipl5scene10ChannelObj 93.48498
[src/scene/channelSelect/iplChannelSelect] baseline: code 24736/25668 data 2336 functions 101 fuzzy 99.7634
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] pool: IDENTICAL
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] objdiff: code 1196/1692 data None/None functions 6/7 fuzzy 99.2151 linked code 0
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] instruction-exact functions: 6/7
[libs/RevoEX/src/nhttp/NHTTP_recvbuf]   section .text size 1692 match 99.21513
[libs/RevoEX/src/nhttp/NHTTP_recvbuf]   below 100: NHTTPi_compareTokenN_HdrRecvBuf 97.32258
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] baseline: code 1196/1692 data None functions 6 fuzzy 96.3641
[libs/NW4R/src/ut/ut_ArchiveFontBase] pool: IDENTICAL
[libs/NW4R/src/ut/ut_ArchiveFontBase] objdiff: code 4164/5120 data 96/96 functions 22/23 fuzzy 98.4680 linked code 0
[libs/NW4R/src/ut/ut_ArchiveFontBase] instruction-exact functions: 22/23
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .data size 88 match 100.0
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .sbss2 size 8 match 100.0
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .text size 5120 match 98.46797
[libs/NW4R/src/ut/ut_ArchiveFontBase]   below 100: ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader 91.794975
[libs/NW4R/src/ut/ut_ArchiveFontBase] baseline: code 4164/5120 data 96 functions 22 fuzzy 98.4680
regressions vs baseline: 0
global matched_code_percent: 90.62359 -> 90.62359
global fuzzy_match_percent: 99.57204 -> 99.57364
global complete_code_percent: 70.30611 -> 70.30611
global matched_data_percent: 99.36639 -> 99.36639
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
HTTP final ctxdiff124/124 insns, diffs5 at54-58: target li A,li Z,extsb delimiter,limit-1,li0 vs ours extsb delimiter,limit-1,li A,li0,li Z. Register assignments and all remaining instructions identical. Fuzzy-only improvement; exact gain criterion unmet. Restored all ChannelSelect and ArchiveFontBase experiments.

# HIGH round
Same branch, begin NHTTP compare97.32258%124/124 insns5 scheduling differences; source check after origin fetch pending same ownership.

http HIGH1 lowercase argument s16: (4, 5), insns 124/124

http HIGH1 lowercase argument u16: (37, 112), insns 131/124

http HIGH1 lowercase argument s8: (4, 5), insns 124/124

http HIGH1 lowercase argument u8: (38, 109), insns 128/124

http HIGH1 lowercase argument const s16: (4, 5), insns 124/124

http HIGH2 character widening s16: (9, 74), insns 126/124

http HIGH2 character widening u16: (9, 74), insns 126/124

http HIGH2 character widening u32: (4, 5), insns 124/124

http HIGH2 character widening s64: (9, 72), insns 126/124

http HIGH2 character widening u64: (9, 72), insns 126/124

http HIGH3 read helper result s16: (9, 74), insns 126/124

http HIGH3 read helper result s8: (11, 74), insns 126/124

http HIGH3 read helper result u16: (9, 74), insns 126/124

http HIGH4 compare inline boundary int character, const char* token: (4, 5), insns 124/124

http HIGH4 compare inline boundary int character, int tokenChar: (4, 5), insns 124/124

http HIGH4 compare inline boundary int tokenChar, int character: (4, 5), insns 124/124

http HIGH4 compare inline boundary s8 character, s8 tokenChar: (4, 5), insns 124/124

http HIGH5 do loop initial goto comparison: (4, 5), insns 124/124

http HIGH6 bound literal type 65LL, 90LL: (4, 5), insns 124/124

http HIGH6 bound literal type 65L, 90L: (4, 5), insns 124/124

http HIGH6 bound literal type (s64)'A', (s64)'Z': (4, 5), insns 124/124

http HIGH6 bound literal type (s16)'A', (s16)'Z': (4, 5), insns 124/124

http HIGH6 bound literal type (s8)'A', (s8)'Z': (4, 5), insns 124/124

http HIGH6 bound literal type 65U, 90U: (35, 110), insns 129/124

http HIGH6 bound literal type 65ULL, 90ULL: (31, 58), insns 134/124

http HIGH7 lowercase result width s16: (9, 35), insns 126/124

http HIGH7 lowercase result width u16: (10, 35), insns 126/124

http HIGH7 lowercase result width s64: (12, 30), insns 128/124

http HIGH8 termination inline boundary s8 character, s8 delimiter, s32 position, s32 limit: (17, 73), insns 128/124

http HIGH8 termination inline boundary const char* token, int delimiter, s32 position, s32 limit: (17, 73), insns 128/124

http HIGH8 termination inline boundary s32 position, s32 limit, s8 delimiter, const char* token: (17, 73), insns 128/124

http HIGH9 termination byte widened s16: (4, 5), insns 124/124

http HIGH9 termination byte widened u16: (10, 72), insns 125/124

http HIGH9 termination byte widened int: (4, 5), insns 124/124

http HIGH9 termination byte widened unsigned char: (6, 7), insns 124/124

http HIGH10 termination branch grouping 0: (16, 76), insns 130/124

http HIGH10 termination branch grouping 1: (14, 70), insns 126/124

http HIGH10 termination branch grouping 2: (16, 68), insns 125/124

http HIGH10 termination branch grouping 3: (17, 73), insns 128/124

http HIGH11 asymmetric inline lowercase (0, 0): (4, 5), insns 124/124

http HIGH11 asymmetric inline lowercase (0, 1): (16, 88), insns 123/124

http HIGH11 asymmetric inline lowercase (0, 2): (4, 5), insns 124/124

http HIGH11 asymmetric inline lowercase (1, 0): (18, 48), insns 123/124

http HIGH11 asymmetric inline lowercase (1, 1): (18, 48), insns 123/124

http HIGH11 asymmetric inline lowercase (1, 2): (26, 35), insns 124/124

http HIGH11 asymmetric inline lowercase (2, 0): (12, 40), insns 124/124

http HIGH11 asymmetric inline lowercase (2, 1): (12, 40), insns 124/124

http HIGH11 asymmetric inline lowercase (2, 2): (30, 46), insns 125/124

channel HIGH1 baseline readable locals: (27, 67), insns 233/233

channel HIGH1 const render mode read view: (27, 67), insns 233/233

channel HIGH1 16-bit render dimensions widened u32: (27, 67), insns 233/233

channel HIGH1 16-bit render dimensions widened s32: (66, 176), insns 239/233

channel HIGH1 render dimensions converted float: (75, 178), insns 209/233

channel HIGH search outer ('scissorWidth', 'scissorY', 'scissorX', 'scissorHeight'): (27, 67), insns 233/233

channel HIGH search outer ('scissorWidth', 'scissorY', 'scissorHeight', 'scissorX'): (27, 67), insns 233/233

channel HIGH search outer ('scissorWidth', 'scissorX', 'scissorY', 'scissorHeight'): (29, 75), insns 233/233

channel HIGH search outer ('scissorWidth', 'scissorX', 'scissorHeight', 'scissorY'): (29, 75), insns 233/233

channel HIGH search outer ('scissorWidth', 'scissorHeight', 'scissorY', 'scissorX'): (27, 67), insns 233/233

channel HIGH search outer ('scissorWidth', 'scissorHeight', 'scissorX', 'scissorY'): (29, 75), insns 233/233

channel HIGH search outer ('scissorY', 'scissorWidth', 'scissorX', 'scissorHeight'): (27, 67), insns 233/233

channel HIGH search outer ('scissorY', 'scissorWidth', 'scissorHeight', 'scissorX'): (27, 67), insns 233/233

channel HIGH search outer ('scissorY', 'scissorX', 'scissorWidth', 'scissorHeight'): (27, 67), insns 233/233

channel HIGH search outer ('scissorY', 'scissorX', 'scissorHeight', 'scissorWidth'): (27, 67), insns 233/233

channel HIGH search outer ('scissorY', 'scissorHeight', 'scissorWidth', 'scissorX'): (27, 67), insns 233/233

channel HIGH search outer ('scissorY', 'scissorHeight', 'scissorX', 'scissorWidth'): (27, 67), insns 233/233

channel HIGH search outer ('scissorX', 'scissorWidth', 'scissorY', 'scissorHeight'): (29, 75), insns 233/233

channel HIGH search outer ('scissorX', 'scissorWidth', 'scissorHeight', 'scissorY'): (29, 75), insns 233/233

channel HIGH search outer ('scissorX', 'scissorY', 'scissorWidth', 'scissorHeight'): (29, 75), insns 233/233

channel HIGH search outer ('scissorX', 'scissorY', 'scissorHeight', 'scissorWidth'): (29, 75), insns 233/233

channel HIGH search outer ('scissorX', 'scissorHeight', 'scissorWidth', 'scissorY'): (29, 75), insns 233/233

channel HIGH search outer ('scissorX', 'scissorHeight', 'scissorY', 'scissorWidth'): (29, 75), insns 233/233

channel HIGH search outer ('scissorHeight', 'scissorWidth', 'scissorY', 'scissorX'): (27, 67), insns 233/233

channel HIGH search outer ('scissorHeight', 'scissorWidth', 'scissorX', 'scissorY'): (29, 75), insns 233/233

channel HIGH search outer ('scissorHeight', 'scissorY', 'scissorWidth', 'scissorX'): (27, 67), insns 233/233

channel HIGH search outer ('scissorHeight', 'scissorY', 'scissorX', 'scissorWidth'): (27, 67), insns 233/233

channel HIGH search outer ('scissorHeight', 'scissorX', 'scissorWidth', 'scissorY'): (29, 75), insns 233/233

channel HIGH search outer ('scissorHeight', 'scissorX', 'scissorY', 'scissorWidth'): (29, 75), insns 233/233

http HIGH12 explicit lowercased locals (0, 0): (68, 63), insns 124/124

http HIGH12 explicit lowercased locals (0, 1): (68, 63), insns 124/124

http HIGH12 explicit lowercased locals (1, 0): (63, 71), insns 124/124

http HIGH12 explicit lowercased locals (1, 1): (63, 71), insns 124/124

http HIGH13 explicit lowercased assignments 0: (68, 63), insns 124/124

http HIGH13 explicit lowercased assignments 1: (63, 71), insns 124/124

http HIGH14 immutable delimiter: (4, 5), insns 124/124

http HIGH14 immutable response pointer: (4, 5), insns 124/124

http HIGH14 immutable limit: (4, 5), insns 124/124

http HIGH14 16-bit delimiter widening: (7, 65), insns 124/124

http HIGH15 const linked header buffer read view: (4, 5), insns 124/124

HIGH NHTTP target asm read:124instructions, frame0x30,_savegpr_25, initial raw header byte load may be unsigned but compare casts signed. Bounds A/Z and delimiter/limit loop invariants are the only five remaining ordered differences. No back-to-back store/reload to justify volatile. HIGH1-15 tried >60 source variants: helper and byte16/64-bit widening, inline compare and termination boundaries, asymmetric lowercase forms, signed/unsigned bounds, range/scalar const views and initial goto/do/for loop forms. All best candidates remain exact-diff5; retain medium readable97.32258% version while proceeding to other units.

channel HIGH search projection (0, 1, 2, 3): (27, 67), insns 233/233

channel HIGH search projection (0, 1, 3, 2): (23, 68), insns 233/233

channel HIGH search projection (0, 2, 1, 3): (27, 68), insns 233/233

channel HIGH search projection (0, 2, 3, 1): (27, 69), insns 233/233

channel HIGH search projection (0, 3, 1, 2): (25, 70), insns 233/233

channel HIGH search projection (0, 3, 2, 1): (23, 69), insns 233/233

channel HIGH search projection (1, 0, 2, 3): (29, 68), insns 233/233

font HIGH1 metadata sheetCount widened u32: (43, 97), insns 239/239

font HIGH1 glyphCount/dataBlock widened u32: (41, 97), insns 239/239

channel HIGH search projection (1, 0, 3, 2): (25, 69), insns 233/233

channel HIGH search projection (1, 2, 0, 3): (29, 69), insns 233/233

channel HIGH search projection (1, 2, 3, 0): (29, 70), insns 233/233

font HIGH1 all metadata counts widened u32: (43, 97), insns 239/239

font HIGH1 font read const view: (41, 87), insns 239/239

channel HIGH search projection (1, 3, 0, 2): (25, 70), insns 233/233

channel HIGH search projection (1, 3, 2, 0): (25, 70), insns 233/233

channel HIGH search projection (2, 0, 1, 3): (34, 70), insns 233/233

channel HIGH search projection (2, 0, 3, 1): (34, 71), insns 233/233

channel HIGH search projection (2, 1, 0, 3): (38, 70), insns 233/233

channel HIGH search projection (2, 1, 3, 0): (38, 71), insns 233/233

channel HIGH search projection (2, 3, 0, 1): (36, 72), insns 233/233

channel HIGH search projection (2, 3, 1, 0): (38, 71), insns 233/233

channel HIGH search projection (3, 0, 1, 2): (34, 71), insns 233/233

channel HIGH search projection (3, 0, 2, 1): (34, 71), insns 233/233

channel HIGH search projection (3, 1, 0, 2): (34, 71), insns 233/233

channel HIGH search projection (3, 1, 2, 0): (34, 71), insns 233/233

channel HIGH search projection (3, 2, 0, 1): (38, 72), insns 233/233

channel HIGH search projection (3, 2, 1, 0): (34, 71), insns 233/233

font HIGH2 typed byte offset helper flags: (41, 97), insns 239/239

font HIGH2 byte offset pointer flags: (41, 97), insns 239/239

font HIGH2 metadata const subview: (41, 87), insns 239/239

font HIGH2 workspace const subview: (20, 97), insns 239/239

font HIGH2 workspace ptr diff signed: (29, 153), insns 242/239

font HIGH3 const workspace and font: (20, 87), insns 239/239

font HIGH3 flags helper const workspace: (20, 97), insns 239/239

font HIGH3 scope const workspace immediately after validation: (20, 97), insns 239/239

channel HIGH search projection-coordinates (0, 1, 2, 3): (27, 67), insns 233/233

channel HIGH search projection-coordinates (0, 1, 3, 2): (29, 67), insns 233/233

font HIGH4 const workspace includes final extent check: (41, 87), insns 239/239

font HIGH4 remaining size local reused check: (41, 87), insns 239/239

channel HIGH search projection-coordinates (0, 2, 1, 3): (27, 67), insns 233/233

channel HIGH search projection-coordinates (0, 2, 3, 1): (29, 66), insns 233/233

channel HIGH search projection-coordinates (0, 3, 1, 2): (29, 66), insns 233/233

channel HIGH search projection-coordinates (0, 3, 2, 1): (29, 66), insns 233/233

channel HIGH search projection-coordinates (1, 0, 2, 3): (29, 69), insns 233/233

channel HIGH search projection-coordinates (1, 0, 3, 2): (31, 70), insns 233/233

channel HIGH search projection-coordinates (1, 2, 0, 3): (29, 69), insns 233/233

font HIGH5 use SDK sheet-offset size helper: (41, 102), insns 239/239

font HIGH5 const metadata struct reference: (41, 102), insns 239/239

font HIGH5 const metadata struct pointer: (41, 102), insns 239/239

channel HIGH search projection-coordinates (1, 2, 3, 0): (29, 69), insns 233/233

font HIGH5 helper operand reverse sheet flag stride: (41, 97), insns 239/239

channel HIGH search projection-coordinates (1, 3, 0, 2): (32, 71), insns 233/233

channel HIGH search projection-coordinates (1, 3, 2, 0): (29, 69), insns 233/233

channel HIGH search projection-coordinates (2, 0, 1, 3): (29, 69), insns 233/233

channel HIGH search projection-coordinates (2, 0, 3, 1): (31, 70), insns 233/233

channel HIGH search projection-coordinates (2, 1, 0, 3): (29, 69), insns 233/233

channel HIGH search projection-coordinates (2, 1, 3, 0): (29, 69), insns 233/233

channel HIGH search projection-coordinates (2, 3, 0, 1): (31, 70), insns 233/233

channel HIGH search projection-coordinates (2, 3, 1, 0): (27, 69), insns 233/233

HIGH font target structural read: frame0x40/239insns, metadata size/flags/workspace calculations overlap at109-147; target read-only font livesr25 and ctxr20, raw workspace difference reused for bounds and scratch. Definition-level volatile unsupported by target: no immediate stack store/reload. 16-bit counts widenedu32 preserve239insns but no gain; const font read view improves97->87 exact positional differences; const workspace subview changes scheduling without exact gain. SDK offset and size helpers, const metadata views and stride helper tested.

channel HIGH search projection-coordinates (3, 0, 1, 2): (29, 69), insns 233/233

channel HIGH search projection-coordinates (3, 0, 2, 1): (29, 69), insns 233/233

channel HIGH search projection-coordinates (3, 1, 0, 2): (29, 69), insns 233/233

channel HIGH search projection-coordinates (3, 1, 2, 0): (27, 69), insns 233/233

channel HIGH search projection-coordinates (3, 2, 0, 1): (29, 69), insns 233/233

channel HIGH search projection-coordinates (3, 2, 1, 0): (27, 69), insns 233/233

http HIGH16 explicit comma-condition lowercase (0, 'int'): (4, 5), insns 124/124

http HIGH16 explicit comma-condition lowercase (0, 's16'): (9, 35), insns 126/124

http HIGH16 explicit comma-condition lowercase (0, 's32'): (4, 5), insns 124/124

http HIGH16 explicit comma-condition lowercase (1, 'int'): (12, 40), insns 124/124

http HIGH16 explicit comma-condition lowercase (1, 's16'): (17, 50), insns 126/124

http HIGH16 explicit comma-condition lowercase (1, 's32'): (12, 40), insns 124/124

channel HIGH search zoom-assignments (1, 2, 3, 4, 5): (27, 67), insns 233/233

channel HIGH search zoom-assignments (1, 2, 3, 5, 4): (31, 68), insns 233/233

channel HIGH search zoom-assignments (1, 2, 4, 3, 5): (38, 71), insns 233/233

channel HIGH search zoom-assignments (1, 2, 4, 5, 3): (38, 71), insns 233/233

channel HIGH search zoom-assignments (1, 2, 5, 3, 4): (33, 68), insns 233/233

channel HIGH search zoom-assignments (1, 2, 5, 4, 3): (38, 71), insns 233/233

channel HIGH search zoom-assignments (1, 4, 2, 3, 5): (38, 70), insns 233/233

channel HIGH search zoom-assignments (1, 4, 2, 5, 3): (38, 70), insns 233/233

font HIGH helper parameter order setSheetOffsetBooleans (0, 1, 2, 3, 4, 5): (20, 87), insns 239/239

font HIGH helper parameter order setSheetOffsetBooleans (1, 0, 2, 3, 4, 5): (20, 87), insns 239/239

font HIGH helper parameter order setSheetOffsetBooleans (2, 0, 1, 3, 4, 5): (20, 87), insns 239/239

channel HIGH search zoom-assignments (1, 4, 5, 2, 3): (38, 70), insns 233/233

font HIGH helper parameter order setSheetOffsetBooleans (3, 0, 1, 2, 4, 5): (20, 87), insns 239/239

font HIGH helper parameter order setSheetOffsetBooleans (4, 0, 1, 2, 3, 5): (20, 87), insns 239/239

font HIGH helper parameter order setSheetOffsetBooleans (5, 0, 1, 2, 3, 4): (20, 87), insns 239/239

font HIGH helper parameter order setSheetOffsetBooleans (5, 4, 3, 2, 1, 0): (20, 87), insns 239/239

channel HIGH search zoom-assignments (1, 5, 2, 3, 4): (33, 68), insns 233/233

channel HIGH search zoom-assignments (1, 5, 2, 4, 3): (38, 71), insns 233/233

channel HIGH search zoom-assignments (1, 5, 4, 2, 3): (38, 70), insns 233/233

channel HIGH search zoom-assignments (2, 1, 3, 4, 5): (33, 63), insns 233/233

channel HIGH search zoom-assignments (2, 1, 3, 5, 4): (36, 63), insns 233/233

http HIGH17 grouped header cursor 0: (4, 44), insns 124/124

http HIGH17 grouped header cursor 1: (4, 44), insns 124/124

http HIGH18 expand header consumption into compare: (18, 83), insns 126/124

channel HIGH search zoom-assignments (2, 1, 4, 3, 5): (43, 71), insns 233/233

channel HIGH search zoom-assignments (2, 1, 4, 5, 3): (43, 71), insns 233/233

channel HIGH search zoom-assignments (2, 1, 5, 3, 4): (37, 64), insns 233/233

channel HIGH search zoom-assignments (2, 1, 5, 4, 3): (40, 69), insns 233/233

font HIGH6 glyph header scopes separated: (41, 101), insns 239/239

font HIGH6 const glgr end read view: (41, 97), insns 239/239

channel HIGH search zoom-assignments (2, 3, 1, 4, 5): (40, 63), insns 233/233

font HIGH6 readonly font pointer declared after validation: (41, 102), insns 239/239

font HIGH6 move pGlgr reassignment before metadata reads: (48, 197), insns 238/239

channel HIGH search zoom-assignments (2, 3, 1, 5, 4): (45, 68), insns 233/233

channel HIGH search zoom-assignments (2, 3, 4, 1, 5): (36, 70), insns 233/233

channel HIGH search zoom-assignments (2, 3, 4, 5, 1): (35, 70), insns 233/233

channel HIGH search zoom-assignments (2, 3, 5, 1, 4): (41, 68), insns 233/233

channel HIGH search zoom-assignments (2, 3, 5, 4, 1): (39, 70), insns 233/233

channel HIGH search zoom-assignments (2, 4, 1, 3, 5): (37, 70), insns 233/233

font HIGH7 clear/group iteration inline in owner: (20, 90), insns 239/239

font HIGH8 sheet-offset conversion inline in owner: (20, 82), insns 239/239

font HIGH9 sheet-flag scan inline in owner: (20, 84), insns 239/239

channel HIGH search zoom-assignments (2, 4, 1, 5, 3): (37, 70), insns 233/233

channel HIGH search zoom-assignments (2, 4, 3, 1, 5): (42, 70), insns 233/233

channel HIGH search zoom-assignments (2, 4, 3, 5, 1): (41, 70), insns 233/233

channel HIGH search zoom-assignments (2, 4, 5, 1, 3): (40, 70), insns 233/233

font HIGH10 group name operand offset first: (20, 82), insns 239/239

font HIGH10 group name offset widened u32: (20, 82), insns 239/239

font HIGH10 group name offset widened s16: (21, 82), insns 239/239

channel HIGH search zoom-assignments (2, 4, 5, 3, 1): (41, 70), insns 233/233

channel HIGH search zoom-assignments (2, 5, 1, 3, 4): (42, 64), insns 233/233

channel HIGH search zoom-assignments (2, 5, 1, 4, 3): (40, 69), insns 233/233

channel HIGH search zoom-assignments (2, 5, 3, 1, 4): (36, 64), insns 233/233

channel HIGH search zoom-assignments (2, 5, 3, 4, 1): (43, 70), insns 233/233

channel HIGH search zoom-assignments (2, 5, 4, 1, 3): (37, 70), insns 233/233

font HIGH metadata declaration search (0, 1, 2, 3, 4, 5, 6, 7, 8): (20, 87), insns 239/239

font HIGH metadata declaration search (1, 0, 2, 3, 4, 5, 6, 7, 8): (20, 87), insns 239/239

channel HIGH search zoom-assignments (2, 5, 4, 3, 1): (52, 69), insns 233/233

font HIGH metadata declaration search (2, 1, 0, 3, 4, 5, 6, 7, 8): (20, 87), insns 239/239

font HIGH metadata declaration search (3, 1, 2, 0, 4, 5, 6, 7, 8): (20, 87), insns 239/239

font HIGH metadata declaration search (4, 1, 2, 3, 0, 5, 6, 7, 8): (20, 87), insns 239/239

font HIGH metadata declaration search (5, 1, 2, 3, 4, 0, 6, 7, 8): (20, 87), insns 239/239

font HIGH metadata declaration search (6, 1, 2, 3, 4, 5, 0, 7, 8): (20, 87), insns 239/239

channel HIGH search zoom-assignments (4, 1, 2, 3, 5): (55, 69), insns 233/233

font HIGH metadata declaration search (7, 1, 2, 3, 4, 5, 6, 0, 8): (20, 87), insns 239/239

font HIGH metadata declaration search (8, 1, 2, 3, 4, 5, 6, 7, 0): (20, 87), insns 239/239

font HIGH metadata declaration search (0, 2, 1, 3, 4, 5, 6, 7, 8): (20, 87), insns 239/239

font HIGH metadata declaration search (0, 3, 2, 1, 4, 5, 6, 7, 8): (20, 87), insns 239/239

font HIGH metadata declaration search (0, 4, 2, 3, 1, 5, 6, 7, 8): (20, 87), insns 239/239

font HIGH metadata declaration search (0, 5, 2, 3, 4, 1, 6, 7, 8): (20, 87), insns 239/239

font HIGH metadata declaration search (0, 6, 2, 3, 4, 5, 1, 7, 8): (20, 87), insns 239/239

channel HIGH search zoom-assignments (4, 1, 2, 5, 3): (55, 69), insns 233/233

font HIGH metadata declaration search (0, 7, 2, 3, 4, 5, 6, 1, 8): (20, 87), insns 239/239

font HIGH metadata declaration search (0, 8, 2, 3, 4, 5, 6, 7, 1): (20, 87), insns 239/239

font HIGH metadata declaration search (0, 1, 3, 2, 4, 5, 6, 7, 8): (20, 87), insns 239/239

font HIGH metadata declaration search (0, 1, 4, 3, 2, 5, 6, 7, 8): (20, 87), insns 239/239

font HIGH metadata declaration search (0, 1, 5, 3, 4, 2, 6, 7, 8): (20, 87), insns 239/239

font HIGH metadata declaration search (0, 1, 6, 3, 4, 5, 2, 7, 8): (20, 87), insns 239/239

font HIGH metadata declaration search (0, 1, 7, 3, 4, 5, 6, 2, 8): (20, 87), insns 239/239

font HIGH metadata declaration search (0, 1, 8, 3, 4, 5, 6, 7, 2): (20, 87), insns 239/239

channel HIGH search zoom-assignments (4, 1, 5, 2, 3): (55, 69), insns 233/233

font HIGH metadata declaration search (0, 1, 2, 4, 3, 5, 6, 7, 8): (20, 87), insns 239/239

font HIGH metadata declaration search (0, 1, 2, 5, 4, 3, 6, 7, 8): (20, 87), insns 239/239

font HIGH metadata declaration search (0, 1, 2, 6, 4, 5, 3, 7, 8): (20, 87), insns 239/239

font HIGH metadata declaration search (0, 1, 2, 7, 4, 5, 6, 3, 8): (20, 87), insns 239/239

channel HIGH search zoom-assignments (4, 2, 1, 3, 5): (42, 69), insns 233/233

font HIGH metadata declaration search (0, 1, 2, 8, 4, 5, 6, 7, 3): (20, 86), insns 239/239

font HIGH metadata declaration search (1, 0, 2, 8, 4, 5, 6, 7, 3): (20, 86), insns 239/239

font HIGH metadata declaration search (2, 1, 0, 8, 4, 5, 6, 7, 3): (20, 86), insns 239/239

font HIGH metadata declaration search (8, 1, 2, 0, 4, 5, 6, 7, 3): (20, 86), insns 239/239

font HIGH metadata declaration search (4, 1, 2, 8, 0, 5, 6, 7, 3): (20, 86), insns 239/239

channel HIGH search zoom-assignments (4, 2, 1, 5, 3): (42, 69), insns 233/233

font HIGH metadata declaration search (5, 1, 2, 8, 4, 0, 6, 7, 3): (20, 86), insns 239/239

font HIGH metadata declaration search (6, 1, 2, 8, 4, 5, 0, 7, 3): (20, 86), insns 239/239

font HIGH metadata declaration search (7, 1, 2, 8, 4, 5, 6, 0, 3): (20, 87), insns 239/239

font HIGH metadata declaration search (3, 1, 2, 8, 4, 5, 6, 7, 0): (20, 87), insns 239/239

font HIGH metadata declaration search (0, 2, 1, 8, 4, 5, 6, 7, 3): (20, 86), insns 239/239

font HIGH metadata declaration search (0, 8, 2, 1, 4, 5, 6, 7, 3): (20, 86), insns 239/239

channel HIGH search zoom-assignments (4, 2, 3, 1, 5): (49, 69), insns 233/233

font HIGH metadata declaration search (0, 4, 2, 8, 1, 5, 6, 7, 3): (20, 86), insns 239/239

font HIGH metadata declaration search (0, 5, 2, 8, 4, 1, 6, 7, 3): (20, 86), insns 239/239

font HIGH metadata declaration search (0, 6, 2, 8, 4, 5, 1, 7, 3): (20, 86), insns 239/239

font HIGH metadata declaration search (0, 7, 2, 8, 4, 5, 6, 1, 3): (20, 87), insns 239/239

font HIGH metadata declaration search (0, 3, 2, 8, 4, 5, 6, 7, 1): (20, 87), insns 239/239

font HIGH metadata declaration search (0, 1, 8, 2, 4, 5, 6, 7, 3): (20, 86), insns 239/239

http HIGH19 equal lowercase predicate form 0: (4, 5), insns 124/124

font HIGH metadata declaration search (0, 1, 4, 8, 2, 5, 6, 7, 3): (20, 86), insns 239/239

http HIGH19 equal lowercase predicate form 1: (5, 6), insns 124/124

font HIGH metadata declaration search (0, 1, 5, 8, 4, 2, 6, 7, 3): (20, 86), insns 239/239

http HIGH19 equal lowercase predicate form 2: (5, 6), insns 124/124

font HIGH metadata declaration search (0, 1, 6, 8, 4, 5, 2, 7, 3): (20, 86), insns 239/239

http HIGH19 equal lowercase predicate form 3: (4, 5), insns 124/124

font HIGH metadata declaration search (0, 1, 7, 8, 4, 5, 6, 2, 3): (20, 87), insns 239/239

font HIGH metadata declaration search (0, 1, 3, 8, 4, 5, 6, 7, 2): (20, 87), insns 239/239

font HIGH metadata declaration search (0, 1, 2, 4, 8, 5, 6, 7, 3): (20, 86), insns 239/239

font HIGH metadata declaration search (0, 1, 2, 5, 4, 8, 6, 7, 3): (20, 86), insns 239/239

channel HIGH search zoom-assignments (4, 2, 3, 5, 1): (40, 68), insns 233/233

font HIGH metadata declaration search (0, 1, 2, 6, 4, 5, 8, 7, 3): (20, 86), insns 239/239

font HIGH metadata declaration search (0, 1, 2, 7, 4, 5, 6, 8, 3): (20, 87), insns 239/239

font HIGH metadata declaration search (0, 1, 2, 8, 5, 4, 6, 7, 3): (20, 86), insns 239/239

HIGH source searches include24 outer scalar orders,24 projection divide orders,24 projection-coordinate orders,60 legal zoom assignment orders, and metadata local swaps. Each source candidate is rebuilt separately with instruction-level measurements logged; these are compiler invocations in addition to the outer tool-call count.

font HIGH metadata declaration search (0, 1, 2, 8, 6, 5, 4, 7, 3): (20, 86), insns 239/239

font HIGH metadata declaration search (0, 1, 2, 8, 7, 5, 6, 4, 3): (20, 87), insns 239/239

font HIGH metadata declaration search (0, 1, 2, 8, 3, 5, 6, 7, 4): (20, 87), insns 239/239

channel HIGH search zoom-assignments (4, 2, 5, 1, 3): (43, 69), insns 233/233

font HIGH metadata declaration search (0, 1, 2, 8, 4, 6, 5, 7, 3): (20, 86), insns 239/239

font HIGH metadata declaration search (0, 1, 2, 8, 4, 7, 6, 5, 3): (20, 87), insns 239/239

font HIGH metadata declaration search (0, 1, 2, 8, 4, 3, 6, 7, 5): (20, 86), insns 239/239

font HIGH metadata declaration search (0, 1, 2, 8, 4, 5, 7, 6, 3): (20, 87), insns 239/239

font HIGH metadata declaration search (0, 1, 2, 8, 4, 5, 3, 7, 6): (20, 86), insns 239/239

font HIGH metadata declaration search (0, 1, 2, 8, 4, 5, 6, 3, 7): (20, 87), insns 239/239

channel HIGH search zoom-assignments (4, 2, 5, 3, 1): (40, 69), insns 233/233

channel HIGH search zoom-assignments (4, 5, 1, 2, 3): (52, 69), insns 233/233

channel HIGH search zoom-assignments (4, 5, 2, 1, 3): (43, 69), insns 233/233

Audit correction: zoom-assignment search must keep widthScale computation before both X computation and scissorWidth overwrite. Trials that overwrite the projection width before widthScale are semantically invalid and discarded regardless of score. Final selection will restrict to dependency-valid orders; no invalid result may be retained.

channel HIGH search zoom-assignments (4, 5, 2, 3, 1): (40, 69), insns 233/233

channel HIGH search zoom-assignments (5, 1, 2, 3, 4): (30, 68), insns 233/233

channel HIGH search zoom-assignments (5, 1, 2, 4, 3): (32, 70), insns 233/233

channel HIGH search zoom-assignments (5, 1, 4, 2, 3): (39, 69), insns 233/233

channel HIGH valid zoom selection (2, 1, 3, 4, 5): (33, 63), insns 233/233

font HIGH helper parameter order updateSheetFlags (0, 1, 2, 3, 4): (20, 87), insns 239/239

font HIGH helper parameter order updateSheetFlags (1, 0, 2, 3, 4): (20, 87), insns 239/239

font HIGH helper parameter order updateSheetFlags (2, 0, 1, 3, 4): (20, 87), insns 239/239

font HIGH helper parameter order updateSheetFlags (3, 0, 1, 2, 4): (20, 87), insns 239/239

font HIGH helper parameter order updateSheetFlags (4, 0, 1, 2, 3): (20, 87), insns 239/239

font HIGH helper parameter order updateSheetFlags (4, 3, 2, 1, 0): (20, 87), insns 239/239

channel HIGH2 direct orthographic call expressions: (48, 66), insns 233/233

channel HIGH3 combine projection divide and add expressions: (48, 66), insns 233/233

channel HIGH4 combined projection reverse argument order: (29, 51), insns 233/233

font HIGH helper parameter order convertSheetOffsetBooleansToOffsets (0, 1): (20, 87), insns 239/239

font HIGH helper parameter order convertSheetOffsetBooleansToOffsets (1, 0): (20, 87), insns 239/239

channel HIGH5 fixed projection zoom ('scale', 'width', 'x', 'y', 'height'): (38, 58), insns 233/233

channel HIGH5 fixed projection zoom ('scale', 'width', 'y', 'x', 'height'): (33, 58), insns 233/233

font HIGH11 clear pointer before index: (20, 87), insns 239/239

channel HIGH5 fixed projection zoom ('scale', 'height', 'width', 'x', 'y'): (48, 57), insns 233/233

font HIGH11 clear index before pointer: (20, 82), insns 239/239

channel HIGH5 fixed projection zoom ('scale', 'x', 'width', 'y', 'height'): (32, 58), insns 233/233

HIGH channel first real structural gain: combine projection divide/add into four bounds declared right,left,bottom,top. Initial orthographic block now instruction-exact throughindex70, from prior divergence38. Overallctxdiff67->51 at233/233. Remaining zoom arithmetic scheduling and final X/width register interchange investigated independently; no definition-level volatile justified.

font HIGH helper parameter order copyFlagOffsets (0, 1, 2, 3): (20, 87), insns 239/239

font HIGH helper parameter order copyFlagOffsets (0, 1, 3, 2): (20, 87), insns 239/239

font HIGH helper parameter order copyFlagOffsets (0, 2, 1, 3): (20, 87), insns 239/239

font HIGH helper parameter order copyFlagOffsets (0, 2, 3, 1): (20, 87), insns 239/239

font HIGH helper parameter order copyFlagOffsets (0, 3, 1, 2): (20, 87), insns 239/239

font HIGH helper parameter order copyFlagOffsets (0, 3, 2, 1): (20, 87), insns 239/239

channel HIGH6 projection width independent, thumb temporaries (('width', 'x', 'y', 'height'), False): (37, 58), insns 233/233

font HIGH helper parameter order copyFlagOffsets (1, 0, 2, 3): (20, 87), insns 239/239

font HIGH helper parameter order copyFlagOffsets (1, 0, 3, 2): (20, 87), insns 239/239

font HIGH helper parameter order copyFlagOffsets (1, 2, 0, 3): (20, 87), insns 239/239

font HIGH helper parameter order copyFlagOffsets (1, 2, 3, 0): (20, 87), insns 239/239

font HIGH helper parameter order copyFlagOffsets (1, 3, 0, 2): (20, 87), insns 239/239

channel HIGH6 projection width independent, thumb temporaries (('width', 'x', 'y', 'height'), True): (27, 58), insns 233/233

font HIGH helper parameter order copyFlagOffsets (1, 3, 2, 0): (20, 87), insns 239/239

font HIGH helper parameter order copyFlagOffsets (2, 0, 1, 3): (20, 87), insns 239/239

font HIGH helper parameter order copyFlagOffsets (2, 0, 3, 1): (20, 87), insns 239/239

font HIGH helper parameter order copyFlagOffsets (2, 1, 0, 3): (20, 87), insns 239/239

font HIGH helper parameter order copyFlagOffsets (2, 1, 3, 0): (20, 87), insns 239/239

font HIGH helper parameter order copyFlagOffsets (2, 3, 0, 1): (20, 87), insns 239/239

channel HIGH6 projection width independent, thumb temporaries (('x', 'width', 'y', 'height'), False): (43, 58), insns 233/233

font HIGH helper parameter order copyFlagOffsets (2, 3, 1, 0): (20, 87), insns 239/239

font HIGH helper parameter order copyFlagOffsets (3, 0, 1, 2): (20, 87), insns 239/239

font HIGH helper parameter order copyFlagOffsets (3, 0, 2, 1): (20, 87), insns 239/239

font HIGH helper parameter order copyFlagOffsets (3, 1, 0, 2): (20, 87), insns 239/239

font HIGH helper parameter order copyFlagOffsets (3, 1, 2, 0): (20, 87), insns 239/239

font HIGH helper parameter order copyFlagOffsets (3, 2, 0, 1): (20, 87), insns 239/239

font HIGH helper parameter order copyFlagOffsets (3, 2, 1, 0): (20, 87), insns 239/239

channel HIGH6 projection width independent, thumb temporaries (('x', 'width', 'y', 'height'), True): (39, 58), insns 233/233

channel HIGH6 projection width independent, thumb temporaries (('x', 'y', 'width', 'height'), False): (2, 15), insns 233/233

channel HIGH6 projection width independent, thumb temporaries (('x', 'y', 'width', 'height'), True): (7, 47), insns 233/233

font HIGH12 explicit conversion cursor ('glyph', 'index', 'pointer'): (22, 82), insns 239/239

font HIGH12 explicit conversion cursor ('glyph', 'pointer', 'index'): (22, 84), insns 239/239

font HIGH12 explicit conversion cursor ('index', 'glyph', 'pointer'): (22, 79), insns 239/239

font HIGH12 explicit conversion cursor ('index', 'pointer', 'glyph'): (22, 83), insns 239/239

font HIGH12 explicit conversion cursor ('pointer', 'glyph', 'index'): (22, 82), insns 239/239

font HIGH12 explicit conversion cursor ('pointer', 'index', 'glyph'): (22, 83), insns 239/239

channel HIGH6 projection width independent, thumb temporaries (('y', 'x', 'width', 'height'), False): (36, 58), insns 233/233

channel HIGH6 projection width independent, thumb temporaries (('y', 'x', 'width', 'height'), True): (38, 59), insns 233/233

HIGH channel second structural gain: use independent projectionWidth temporary; inline both horizontal fbWidth/projectionWidth ratios, remove widthScale temporary; order X,Y,width,height. Exact positional differences51->15, same233insns, structural2 pendingctxdiff. This follows target duplicate width conversions and lets projectionWidth lifetime end before final width assignment.

font HIGH13 all five initial local declaration swap (0, 1, 2, 3, 4): (20, 82), insns 239/239

font HIGH13 all five initial local declaration swap (1, 0, 2, 3, 4): (20, 82), insns 239/239

font HIGH13 all five initial local declaration swap (2, 1, 0, 3, 4): (20, 82), insns 239/239

font HIGH13 all five initial local declaration swap (3, 1, 2, 0, 4): (20, 90), insns 239/239

font HIGH13 all five initial local declaration swap (4, 1, 2, 3, 0): (20, 90), insns 239/239

font HIGH13 all five initial local declaration swap (0, 2, 1, 3, 4): (20, 82), insns 239/239

font HIGH13 all five initial local declaration swap (0, 3, 2, 1, 4): (20, 82), insns 239/239

font HIGH13 all five initial local declaration swap (0, 4, 2, 3, 1): (20, 79), insns 239/239

font HIGH13 all five initial local declaration swap (0, 1, 3, 2, 4): (20, 82), insns 239/239

font HIGH13 all five initial local declaration swap (0, 1, 4, 3, 2): (20, 79), insns 239/239

font HIGH13 all five initial local declaration swap (0, 1, 2, 4, 3): (20, 79), insns 239/239

HIGH ChannelSelect candidate exact:233/233instructions ctxdiff0, pool98/98 identical. Structural fixes combine right,left,bottom,top bounds, use a separate projectionWidth, evaluate horizontal/vertical scissor coordinates before extents, and remove widthScale temporary. Final declsearch after structural fixes swapped X and width declarations, resolving f29/f31 interchange in three builds. Definition-level volatile, use-site casts, pinned data, asm and configure changes absent. Full clean gate starts with Font restored to baseline to isolate ChannelSelect acceptance.

HIGH ChannelSelect clean acceptance gate:
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/channelSelect/iplChannelSelect] pool: IDENTICAL
[src/scene/channelSelect/iplChannelSelect] objdiff: code 25668/25668 data 2336/2336 functions 102/102 fuzzy 100.0000 linked code 0
[src/scene/channelSelect/iplChannelSelect] instruction-exact functions: 102/102
[src/scene/channelSelect/iplChannelSelect]   section .data size 2144 match 100.0
[src/scene/channelSelect/iplChannelSelect]   section .rodata size 16 match 100.0
[src/scene/channelSelect/iplChannelSelect]   section .sbss size 8 match 100.0
[src/scene/channelSelect/iplChannelSelect]   section .sdata size 80 match 100.0
[src/scene/channelSelect/iplChannelSelect]   section .sdata2 size 88 match 100.0
[src/scene/channelSelect/iplChannelSelect]   section .text size 25668 match 100.0
[src/scene/channelSelect/iplChannelSelect] baseline: code 24736/25668 data 2336 functions 101 fuzzy 99.7634
regressions vs baseline: 0
global matched_code_percent: 90.62359 -> 90.65471
global fuzzy_match_percent: 99.57204 -> 99.57567
global complete_code_percent: 70.30611 -> 70.30611
global matched_data_percent: 99.36639 -> 99.36639
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

http HIGH20 explicit last position ('after read', False): (6, 15), insns 124/124

http HIGH20 explicit last position ('after read', True): (4, 5), insns 124/124

http HIGH20 explicit last position ('after find', False): (5, 33), insns 124/124

http HIGH20 explicit last position ('after find', True): (4, 5), insns 124/124

http HIGH20 explicit last position ('after valid range', False): (5, 54), insns 124/124

http HIGH20 explicit last position ('after valid range', True): (4, 5), insns 124/124

font HIGH14 sheet offsets size before flags stride: (45, 98), insns 239/239

font HIGH14 sheet offsets size before flags offset: (45, 98), insns 239/239

font HIGH14 scratch first, then flags offset: (24, 99), insns 239/239

http HIGH21 explicit uppercase-range helper temporaries 0: (4, 5), insns 124/124

http HIGH21 explicit uppercase-range helper temporaries 1: (4, 5), insns 124/124

http HIGH21 explicit uppercase-range helper temporaries 2: (4, 5), insns 124/124

http HIGH21 explicit uppercase-range helper temporaries 3: (4, 5), insns 124/124

http HIGH21 explicit uppercase-range helper temporaries 4: (4, 5), insns 124/124

http HIGH21 explicit uppercase-range helper temporaries 5: (4, 5), insns 124/124

HIGH late audit: scratch-first/flags-offset experiment constructed an invalid use-before-size-assignment variant; discarded, baseline restored immediately. No uninitialized variant retained. ChannelSelect exact commit5a04fc07 independently clean-gated; no configure/link changes. Remaining NHTTP at least21 HIGH experiment families, Font at least14 HIGH families plus local/helper searches; both preserve owneddata100%, no symbol renames/extents warranted.

font HIGH authoritative candidate /tmp/rt7-high-font-font_read_const_view.cpp: (41, 87), insns 239/239
Font authoritative objdiff /tmp/rt7-high-font-font_read_const_view.cpp: 92.08787%; exact functions22/23, data96/96

font HIGH authoritative candidate /tmp/rt7-high-font-clear_index_before_pointer.cpp: (20, 82), insns 239/239
Font authoritative objdiff /tmp/rt7-high-font-clear_index_before_pointer.cpp: 91.167366%; exact functions22/23, data96/96

font HIGH authoritative candidate /tmp/rt7-high-font-expanded-conversion.cpp: (20, 82), insns 239/239
Font authoritative objdiff /tmp/rt7-high-font-expanded-conversion.cpp: 91.230125%; exact functions22/23, data96/96

font HIGH authoritative candidate /tmp/rt7-high-font-best-metadata.cpp: (20, 86), insns 239/239
Font authoritative objdiff /tmp/rt7-high-font-best-metadata.cpp: 91.08368%; exact functions22/23, data96/96

HIGH final acceptance audit: ChannelSelect100% code/data/function metrics,233/233instructionsctxdiff0,pool98 identical, clean gatePASS,DOL26116613f624061ba99c8d1a299aaa6efa85670d, regressions0. NHTTP all HIGH attempts returnbest97.32258%124/124instructionsfivepreheader scheduling differences; source unchanged frommediumacceptedcommit. Font raw positional score97->79 did not imply objdiff improvement: best initial-declaration candidate only91.230125%, below91.794975baseline, discarded; final selection uses authoritative objdiff of readable candidates, not rawdiff count.

Font retained HIGH partial is only const ArchiveFontBinaryLayout read view with mutable pGlgr for the copy destinations:91.794975->92.08787%, exact22/23,data96/96. All helper, loop, declaration and workspace experiments discarded. NHTTP remainsmediumsource97.32258% withnoHIGHsourcechange. All openfunctions have many distinct logged source-level attempts. All three owneddata metrics already100%, no renames/extent edits. Final clean gate across all threeunits follows.

HIGH final non-quick gate across all owned units:
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/channelSelect/iplChannelSelect] pool: IDENTICAL
[src/scene/channelSelect/iplChannelSelect] objdiff: code 25668/25668 data 2336/2336 functions 102/102 fuzzy 100.0000 linked code 0
[src/scene/channelSelect/iplChannelSelect] instruction-exact functions: 102/102
[src/scene/channelSelect/iplChannelSelect]   section .data size 2144 match 100.0
[src/scene/channelSelect/iplChannelSelect]   section .rodata size 16 match 100.0
[src/scene/channelSelect/iplChannelSelect]   section .sbss size 8 match 100.0
[src/scene/channelSelect/iplChannelSelect]   section .sdata size 80 match 100.0
[src/scene/channelSelect/iplChannelSelect]   section .sdata2 size 88 match 100.0
[src/scene/channelSelect/iplChannelSelect]   section .text size 25668 match 100.0
[src/scene/channelSelect/iplChannelSelect] baseline: code 24736/25668 data 2336 functions 101 fuzzy 99.7634
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] pool: IDENTICAL
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] objdiff: code 1196/1692 data None/None functions 6/7 fuzzy 99.2151 linked code 0
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] instruction-exact functions: 6/7
[libs/RevoEX/src/nhttp/NHTTP_recvbuf]   section .text size 1692 match 99.21513
[libs/RevoEX/src/nhttp/NHTTP_recvbuf]   below 100: NHTTPi_compareTokenN_HdrRecvBuf 97.32258
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] baseline: code 1196/1692 data None functions 6 fuzzy 96.3641
[libs/NW4R/src/ut/ut_ArchiveFontBase] pool: IDENTICAL
[libs/NW4R/src/ut/ut_ArchiveFontBase] objdiff: code 4164/5120 data 96/96 functions 22/23 fuzzy 98.5227 linked code 0
[libs/NW4R/src/ut/ut_ArchiveFontBase] instruction-exact functions: 22/23
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .data size 88 match 100.0
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .sbss2 size 8 match 100.0
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .text size 5120 match 98.52266
[libs/NW4R/src/ut/ut_ArchiveFontBase]   below 100: ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader 92.08787
[libs/NW4R/src/ut/ut_ArchiveFontBase] baseline: code 4164/5120 data 96 functions 22 fuzzy 98.4680
regressions vs baseline: 0
global matched_code_percent: 90.62359 -> 90.65471
global fuzzy_match_percent: 99.57204 -> 99.57575
global complete_code_percent: 70.30611 -> 70.30611
global matched_data_percent: 99.36639 -> 99.36639
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
HIGH final state: ChannelSelect101->102instruction-exact,code24736->25668,data2336->2336; NHTTP6->6,code1196->1196,data0; ArchiveFontBase22->22,code4164->4164,data96->96,GLGR91.794975->92.08787%. Final clean build/DOL gatePASS, regressions0, pools identical, forbidden0/readability0. ChannelSelect owns allsections100% and is ready for parent verification. NHTTP andGLGR remain open after383individual HIGH source trials logged; no fake exact claim. No source changes outside owned units; no new comments, asm, volatile, pinned symbols, extent edits or configure changes.
