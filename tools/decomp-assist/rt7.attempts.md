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

# HIGH continued after ChannelSelect landing
HEAD 1f0eb50f01f35b4684fea10099f8b8bf851d5e93 origin/main 1f0eb50f01f35b4684fea10099f8b8bf851d5e93
Own only NHTTP_recvbuf and ut_ArchiveFontBase; prior ChannelSelect is landed and excluded. Baseline sources backed up below.

http C1 range operand order character >= 'A' character <= 'Z': (4, 5), insns 124/124

http C1 range operand order character >= 'A' 'Z' >= character: (4, 5), insns 124/124

http C1 range operand order 'A' <= character character <= 'Z': (4, 5), insns 124/124

http C1 range operand order 'A' <= character 'Z' >= character: (4, 5), insns 124/124

http C2 plain char delimiter: (4, 5), insns 124/124

http C2 signed byte token view: (4, 5), insns 124/124

http C2 16-bit widened read comparison: (4, 5), insns 124/124

http C2 16-bit widened token comparison: (4, 5), insns 124/124

font C3 split glyph metadata inline helper 0: (41, 119), insns 239/239

font C3 split glyph metadata inline helper 1: (41, 119), insns 239/239

font C3 split glyph metadata inline helper 2: (41, 119), insns 239/239

http C4 complete compare inline boundary order 0: (10, 49), insns 124/124

http C4 complete compare inline boundary order 1: (10, 49), insns 124/124

http C4 complete compare inline boundary order 2: (10, 49), insns 124/124

http C4 complete compare inline boundary order 3: (10, 49), insns 124/124

http C4 complete compare inline boundary order 4: (10, 49), insns 124/124

http C4 complete compare inline boundary order 5: (10, 49), insns 124/124

http C4 complete compare inline boundary order 6: (10, 49), insns 124/124

http C4 complete compare inline boundary order 7: (10, 49), insns 124/124

http C5 lowercase bounds inline helper parameters ('character', 'lowerBound', 'upperBound'): (4, 5), insns 124/124

http C5 lowercase bounds inline helper parameters ('character', 'upperBound', 'lowerBound'): (4, 5), insns 124/124

http C5 lowercase bounds inline helper parameters ('lowerBound', 'character', 'upperBound'): (4, 5), insns 124/124

http C5 lowercase bounds inline helper parameters ('lowerBound', 'upperBound', 'character'): (4, 5), insns 124/124

http C5 lowercase bounds inline helper parameters ('upperBound', 'character', 'lowerBound'): (4, 5), insns 124/124

http C5 lowercase bounds inline helper parameters ('upperBound', 'lowerBound', 'character'): (4, 5), insns 124/124

font C6 const glgr helper view: (41, 87), insns 239/239

font C6 separate GLGR extent first: tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -Cpp_exceptions off -lang=c++ -MMD -c libs/NW4R/src/ut/ut_ArchiveFontBase.cpp -o build/43U/src/libs/NW4R/src/ut && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/NW4R/src/ut/ut_ArchiveFontBase.d build/43U/src/libs/NW4R/src/ut/ut_ArchiveFontBase.d
### mwcceppc.exe Compiler:
#    File: libs\NW4R\src\ut\ut_ArchiveFontBase.cpp
# ------------------------------------------------
#     351:                 fontSizeToEndOfGlgr = glgrEnd - (u8*)font;
#   Error:                 ^^^^^^^^^^^^^^^^^^^
#   (10140) undefined identifier 'fontSizeToEndOfGlgr'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


font C6 separate GLGR extent metadata: (41, 87), insns 239/239

font C6 separate GLGR extent near check: (41, 87), insns 239/239

font C6 metadata const pointer: (0, 82), insns 239/239

font C6 metadata const reference: (41, 87), insns 239/239

font C6 metadata typed pointer: (41, 87), insns 239/239

font C6 scratch copy u16 end pointer: (41, 83), insns 239/239

font C6 scratch copy byte end pointer: (30, 146), insns 240/239

font C6 scratch copy size via signed half: (29, 145), insns 238/239

font C6 scratch copy size via ptrdiff helper: (30, 146), insns 240/239

font C6 authority structural-zero metadata header view: (0, 82), insns 239/239

font C7 consolidate metadata declaration block with const header view: (0, 82), insns 239/239

C7 initial explicit declaration range accidentally included font assignment; interrupted and restored by declsearch, discarded. Corrected contiguous declaration-only range follows. Preliminary register-only search reached72 differences without structural changes; no candidate retained from invalid range.

http C8 independent lowercase forms (0, 0, True): (12, 40), insns 124/124

http C8 independent lowercase forms (0, 1, True): (16, 88), insns 123/124

http C8 independent lowercase forms (0, 2, True): (16, 88), insns 123/124

http C8 independent lowercase forms (0, 3, False): (16, 88), insns 123/124

http C8 independent lowercase forms (0, 3, True): (30, 46), insns 125/124

http C8 independent lowercase forms (0, 4, False): (23, 50), insns 127/124

http C8 independent lowercase forms (0, 4, True): (23, 50), insns 127/124

http C8 independent lowercase forms (1, 0, True): (18, 48), insns 123/124

http C8 independent lowercase forms (1, 1, True): (16, 88), insns 123/124

http C8 independent lowercase forms (1, 2, True): (16, 88), insns 123/124

http C8 independent lowercase forms (1, 3, False): (26, 32), insns 124/124

http C8 independent lowercase forms (1, 3, True): (26, 32), insns 124/124

http C8 independent lowercase forms (1, 4, False): (41, 50), insns 126/124

http C8 independent lowercase forms (1, 4, True): (41, 50), insns 126/124

http C8 independent lowercase forms (2, 0, True): (18, 48), insns 123/124

http C8 independent lowercase forms (2, 1, True): (16, 88), insns 123/124

http C8 independent lowercase forms (2, 2, True): (16, 88), insns 123/124

http C8 independent lowercase forms (2, 3, False): (26, 32), insns 124/124

http C8 independent lowercase forms (2, 3, True): (26, 32), insns 124/124

http C8 independent lowercase forms (2, 4, False): (41, 50), insns 126/124

http C8 independent lowercase forms (2, 4, True): (41, 50), insns 126/124

http C8 independent lowercase forms (3, 0, False): (10, 37), insns 125/124

http C8 independent lowercase forms (3, 0, True): (18, 48), insns 123/124

http C8 independent lowercase forms (3, 1, False): (26, 75), insns 124/124

http C8 independent lowercase forms (3, 1, True): (26, 75), insns 124/124

http C8 independent lowercase forms (3, 2, False): (26, 75), insns 124/124

http C8 independent lowercase forms (3, 2, True): (26, 75), insns 124/124

http C8 independent lowercase forms (3, 3, False): (26, 75), insns 124/124

http C8 independent lowercase forms (3, 3, True): (26, 32), insns 124/124

http C8 independent lowercase forms (3, 4, False): (41, 50), insns 126/124

http C8 independent lowercase forms (3, 4, True): (41, 50), insns 126/124

http C8 independent lowercase forms (4, 0, False): (15, 90), insns 127/124

http C8 independent lowercase forms (4, 0, True): (15, 90), insns 127/124

http C8 independent lowercase forms (4, 1, False): (22, 90), insns 126/124

http C8 independent lowercase forms (4, 1, True): (22, 90), insns 126/124

http C8 independent lowercase forms (4, 2, False): (22, 90), insns 126/124

http C8 independent lowercase forms (4, 2, True): (22, 90), insns 126/124

http C8 independent lowercase forms (4, 3, False): (22, 90), insns 126/124

http C8 independent lowercase forms (4, 3, True): (22, 90), insns 126/124

http C8 independent lowercase forms (4, 4, False): (36, 108), insns 130/124

http C8 independent lowercase forms (4, 4, True): (41, 108), insns 130/124

C7 proper declaration-only declsearch:439 builds, structural0/exact82->59; first111 instructions now identical. declaration block:
                  u32 glgrInnerLen;
                  HeaderedGlyphGroups* pGlgr;
                  const ArchiveFontBinaryLayout* font;
                  u8* glgrEnd;
                  u32 expectedMaxSize;
                  u16 countSheet;
                  u16 sheetGlyphCount;
                  u16 dataBlockCount;
                  u32 stepSheetFlags;
                  u32 flagsSheetsOff;
                  const u32* flagsSheets;
                  u32 sheetOffsetsSize;
                  u16* sheetOffsetsScratch;
                  u32 sheetOffsetsScratchSize;
                  const HeaderedGlyphGroups* groups;
start (0, 82)
improved (0, 79)
improved (0, 72)
improved (0, 64)
improved (0, 61)
improved (0, 59)
best (0, 59) after 439 builds; kept in source:
                const HeaderedGlyphGroups* groups;
                HeaderedGlyphGroups* pGlgr;
                const ArchiveFontBinaryLayout* font;
                u32 flagsSheetsOff;
                u32 glgrInnerLen;
                u16 countSheet;
                u16 sheetGlyphCount;
                u16 dataBlockCount;
                const u32* flagsSheets;
                u8* glgrEnd;
                u32 expectedMaxSize;
                u32 sheetOffsetsSize;
                u16* sheetOffsetsScratch;
                u32 sheetOffsetsScratchSize;
                u32 stepSheetFlags;


font C9 count assignments ('sheetGlyphCount = groups->inner.sheetGlyphCount;', 'dataBlockCount = font->hdr.dataBlocks;', 'countSheet = groups->inner.sheetCount;'): (0, 59), insns 239/239

font C9 count assignments ('sheetGlyphCount = groups->inner.sheetGlyphCount;', 'countSheet = groups->inner.sheetCount;', 'dataBlockCount = font->hdr.dataBlocks;'): (0, 59), insns 239/239

font C9 count assignments ('dataBlockCount = font->hdr.dataBlocks;', 'sheetGlyphCount = groups->inner.sheetGlyphCount;', 'countSheet = groups->inner.sheetCount;'): (2, 59), insns 239/239

font C9 count assignments ('dataBlockCount = font->hdr.dataBlocks;', 'countSheet = groups->inner.sheetCount;', 'sheetGlyphCount = groups->inner.sheetGlyphCount;'): (2, 58), insns 239/239

font C9 count assignments ('countSheet = groups->inner.sheetCount;', 'sheetGlyphCount = groups->inner.sheetGlyphCount;', 'dataBlockCount = font->hdr.dataBlocks;'): (0, 59), insns 239/239

font C9 count assignments ('countSheet = groups->inner.sheetCount;', 'dataBlockCount = font->hdr.dataBlocks;', 'sheetGlyphCount = groups->inner.sheetGlyphCount;'): (2, 58), insns 239/239

font C10 commute flags pointer addition: (0, 59), insns 239/239

font C10 commute name pointer addition: (0, 59), insns 239/239

font C10 commute group flag multiply and bit add: (0, 58), insns 239/239

font C10 explicit clear cursor declarations False: (2, 55), insns 239/239

font C10 explicit clear cursor declarations True: (2, 59), insns 239/239

font C10 explicit conversion cursor declarations ('glyph', 'index', 'pointer'): (2, 58), insns 239/239

font C10 explicit conversion cursor declarations ('glyph', 'pointer', 'index'): (2, 61), insns 239/239

font C10 explicit conversion cursor declarations ('index', 'glyph', 'pointer'): (2, 53), insns 239/239

font C10 explicit conversion cursor declarations ('index', 'pointer', 'glyph'): (2, 59), insns 239/239

font C10 explicit conversion cursor declarations ('pointer', 'glyph', 'index'): (2, 59), insns 239/239

font C10 explicit conversion cursor declarations ('pointer', 'index', 'glyph'): (2, 61), insns 239/239

font C11 reuse const header view: (0, 59), insns 239/239

font C11 scope mutable copy destination: (0, 59), insns 239/239

font C11 reuse typed header reference: (0, 84), insns 239/239

font C11 initialize main header after validation: (0, 84), insns 239/239

font C12 objdiff authority rt7c-font-best59.cpp: (0, 59), insns 239/239
C12 authoritative rt7c-font-best59.cpp 98.3682%

font C12 objdiff authority rt7c-font-view4.cpp: (0, 82), insns 239/239
C12 authoritative rt7c-font-view4.cpp 97.782425%

font C12 objdiff authority rt7c-font-view7.cpp: (41, 83), insns 239/239
C12 authoritative rt7c-font-view7.cpp 92.25523%

font C12 objdiff authority rt7c-font-loop0.cpp: (0, 59), insns 239/239
C12 authoritative rt7c-font-loop0.cpp 98.3682%

font C12 objdiff authority rt7c-font-loop1.cpp: (0, 59), insns 239/239
C12 authoritative rt7c-font-loop1.cpp 98.3682%

font C12 objdiff authority rt7c-font-loop2.cpp: (0, 58), insns 239/239
C12 authoritative rt7c-font-loop2.cpp 98.41004%

font C12 objdiff authority rt7c-font-loop3.cpp: (2, 55), insns 239/239
C12 authoritative rt7c-font-loop3.cpp 98.44351%

font C12 objdiff authority rt7c-font-loop4.cpp: (2, 59), insns 239/239
C12 authoritative rt7c-font-loop4.cpp 98.44351%

font C12 objdiff authority rt7c-font-loop5.cpp: (2, 58), insns 239/239
C12 authoritative rt7c-font-loop5.cpp 98.35983%

font C12 objdiff authority rt7c-font-loop6.cpp: (2, 61), insns 239/239
C12 authoritative rt7c-font-loop6.cpp 98.31799%

font C12 objdiff authority rt7c-font-loop7.cpp: (2, 53), insns 239/239
C12 authoritative rt7c-font-loop7.cpp 98.48536%

font C12 objdiff authority rt7c-font-loop8.cpp: (2, 59), insns 239/239
C12 authoritative rt7c-font-loop8.cpp 98.31799%

font C12 objdiff authority rt7c-font-loop9.cpp: (2, 59), insns 239/239
C12 authoritative rt7c-font-loop9.cpp 98.44351%

font C12 objdiff authority rt7c-font-loop10.cpp: (2, 61), insns 239/239
C12 authoritative rt7c-font-loop10.cpp 98.31799%

font C12 objdiff authority rt7c-font-alias0.cpp: (0, 59), insns 239/239
C12 authoritative rt7c-font-alias0.cpp 98.3682%

font C12 objdiff authority rt7c-font-alias1.cpp: (0, 59), insns 239/239
C12 authoritative rt7c-font-alias1.cpp 98.3682%

font C12 objdiff authority rt7c-font-alias2.cpp: (0, 84), insns 239/239
C12 authoritative rt7c-font-alias2.cpp 97.677826%

font C12 objdiff authority rt7c-font-alias3.cpp: (0, 84), insns 239/239
C12 authoritative rt7c-font-alias3.cpp 97.677826%

font C13 combine clear/convert cursors and flag operand order: (4, 48), insns 239/239

font C13 metadata scalar widths ('u16', 'u16', 'u16'): (4, 48), insns 239/239

font C13 metadata scalar widths ('u16', 'u16', 'u32'): (4, 71), insns 239/239

font C13 metadata scalar widths ('u16', 'u16', 's32'): (4, 71), insns 239/239

font C13 metadata scalar widths ('u16', 'u32', 'u16'): (4, 71), insns 239/239

font C13 metadata scalar widths ('u16', 'u32', 'u32'): (4, 71), insns 239/239

font C13 metadata scalar widths ('u16', 'u32', 's32'): (4, 71), insns 239/239

font C13 metadata scalar widths ('u16', 's32', 'u16'): (4, 71), insns 239/239

font C13 metadata scalar widths ('u16', 's32', 'u32'): (4, 71), insns 239/239

font C13 metadata scalar widths ('u16', 's32', 's32'): (4, 71), insns 239/239

font C13 metadata scalar widths ('u32', 'u16', 'u16'): (6, 71), insns 239/239

font C13 metadata scalar widths ('u32', 'u16', 'u32'): (6, 70), insns 239/239

font C13 metadata scalar widths ('u32', 'u16', 's32'): (6, 70), insns 239/239

font C13 metadata scalar widths ('u32', 'u32', 'u16'): (6, 71), insns 239/239

font C13 metadata scalar widths ('u32', 'u32', 'u32'): (6, 66), insns 239/239

font C13 metadata scalar widths ('u32', 'u32', 's32'): (6, 66), insns 239/239

font C13 metadata scalar widths ('u32', 's32', 'u16'): (6, 71), insns 239/239

font C13 metadata scalar widths ('u32', 's32', 'u32'): (6, 66), insns 239/239

font C13 metadata scalar widths ('u32', 's32', 's32'): (6, 66), insns 239/239

font C13 metadata scalar widths ('s32', 'u16', 'u16'): (6, 71), insns 239/239

font C13 metadata scalar widths ('s32', 'u16', 'u32'): (6, 70), insns 239/239

font C13 metadata scalar widths ('s32', 'u16', 's32'): (6, 70), insns 239/239

font C13 metadata scalar widths ('s32', 'u32', 'u16'): (6, 71), insns 239/239

font C13 metadata scalar widths ('s32', 'u32', 'u32'): (6, 66), insns 239/239

font C13 metadata scalar widths ('s32', 'u32', 's32'): (6, 66), insns 239/239

font C13 metadata scalar widths ('s32', 's32', 'u16'): (6, 71), insns 239/239

font C13 metadata scalar widths ('s32', 's32', 'u32'): (6, 66), insns 239/239

font C13 metadata scalar widths ('s32', 's32', 's32'): (6, 66), insns 239/239

http C14 negated mismatch condition: (4, 5), insns 124/124

http C14 conditional truth compare: (4, 5), insns 124/124

http C14 read and position increments for clause: (4, 5), insns 124/124

http C14 initial and next read for clause order 0: (4, 5), insns 124/124

http C14 initial and next read for clause order 1: (8, 25), insns 124/124

http C14 initial and next read for clause order 2: (6, 25), insns 124/124

http C14 postincrement cursors ++position;
            token++;: (4, 5), insns 124/124

http C14 postincrement cursors position++;
            ++token;: (4, 5), insns 124/124

http C14 postincrement cursors position++;
            token++;: (4, 5), insns 124/124

font C13 combined cursors authoritative candidate: (4, 48), insns 239/239

C13 combined improvement: metadata loads use a const HeaderedGlyphGroups view (same layout, glgr at font+16), which matches target arithmetic/load schedule; top declaration search matches first111 instructions. Explicit clear/conversion cursors and group multiplication operand order reduce59->48 positional differences. No volatile evidence; no 8/16-bit clrlwi/shift discrepancy; no symbol overlap. Both units retain100% data, no rename/extent change justified.
Quick gate evidence:
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] pool: IDENTICAL
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] objdiff: code 1196/1692 data None/None functions 6/7 fuzzy 99.2151 linked code 0
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] instruction-exact functions: 6/7
[libs/RevoEX/src/nhttp/NHTTP_recvbuf]   section .text size 1692 match 99.21513
[libs/RevoEX/src/nhttp/NHTTP_recvbuf]   below 100: NHTTPi_compareTokenN_HdrRecvBuf 97.32258
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] baseline: code 1196/1692 data None functions 6 fuzzy 99.2151
[libs/NW4R/src/ut/ut_ArchiveFontBase] pool: IDENTICAL
[libs/NW4R/src/ut/ut_ArchiveFontBase] objdiff: code 4164/5120 data 96/96 functions 22/23 fuzzy 99.7391 linked code 0
[libs/NW4R/src/ut/ut_ArchiveFontBase] instruction-exact functions: 22/23
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .data size 88 match 100.0
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .sbss2 size 8 match 100.0
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .text size 5120 match 99.73906
[libs/NW4R/src/ut/ut_ArchiveFontBase]   below 100: ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader 98.60251
[libs/NW4R/src/ut/ut_ArchiveFontBase] baseline: code 4164/5120 data 96 functions 22 fuzzy 98.5227
regressions vs baseline: 0
global matched_code_percent: 90.80962 -> 90.80962
global fuzzy_match_percent: 99.58569 -> 99.58778
global complete_code_percent: 71.43246 -> 71.43246
global matched_data_percent: 99.36639 -> 99.36639
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
Removed obsolete commented experiments from changed GLGR function; no output change.

font C15 cursor pointer increments before indices: (0, 44), insns 239/239

font C15 typed inline helper header views (False, False, False): (0, 44), insns 239/239

font C15 typed inline helper header views (False, False, True): (0, 44), insns 239/239

font C15 typed inline helper header views (False, True, False): (0, 44), insns 239/239

font C15 typed inline helper header views (False, True, True): (0, 44), insns 239/239

font C15 typed inline helper header views (True, False, False): NAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -Cpp_exceptions off -lang=c++ -MMD -c libs/NW4R/src/ut/ut_ArchiveFontBase.cpp -o build/43U/src/libs/NW4R/src/ut && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/NW4R/src/ut/ut_ArchiveFontBase.d build/43U/src/libs/NW4R/src/ut/ut_ArchiveFontBase.d
### mwcceppc.exe Compiler:
#    File: libs\NW4R\src\ut\ut_ArchiveFontBase.cpp
# ------------------------------------------------
#     287: heetFlags(glgrHdr, i, sheetOffsets, sheetFlagsSize, bitBlocksPtr);
#   Error:                                                                 ^
#   (10248) function call 'updateSheetFlags({lval} const void *, {lval} int,
#   {lval} unsigned short *, {lval} unsigned long, {lval} const unsigned long
#   *)' does not match
#   'nw4r::ut::detail::updateSheetFlags(const nw4r::ut::HeaderedGlyphGroups *,
#   unsigned long, unsigned short *, unsigned long, const unsigned long *)'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


font C15 typed inline helper header views (True, False, True): NAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -Cpp_exceptions off -lang=c++ -MMD -c libs/NW4R/src/ut/ut_ArchiveFontBase.cpp -o build/43U/src/libs/NW4R/src/ut && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/NW4R/src/ut/ut_ArchiveFontBase.d build/43U/src/libs/NW4R/src/ut/ut_ArchiveFontBase.d
### mwcceppc.exe Compiler:
#    File: libs\NW4R\src\ut\ut_ArchiveFontBase.cpp
# ------------------------------------------------
#     287: heetFlags(glgrHdr, i, sheetOffsets, sheetFlagsSize, bitBlocksPtr);
#   Error:                                                                 ^
#   (10248) function call 'updateSheetFlags({lval} const void *, {lval} int,
#   {lval} unsigned short *, {lval} unsigned long, {lval} const unsigned long
#   *)' does not match
#   'nw4r::ut::detail::updateSheetFlags(const nw4r::ut::HeaderedGlyphGroups *,
#   unsigned long, unsigned short *, unsigned long, const unsigned long *)'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


font C15 typed inline helper header views (True, True, False): (0, 44), insns 239/239

font C15 typed inline helper header views (True, True, True): (0, 44), insns 239/239

font C16 const metadata definitions (False, False, False): (0, 44), insns 239/239

font C16 const metadata definitions (False, False, True): (0, 72), insns 239/239

font C16 const metadata definitions (False, True, False): (0, 72), insns 239/239

font C16 const metadata definitions (False, True, True): (0, 72), insns 239/239

font C16 const metadata definitions (True, False, False): (0, 72), insns 239/239

font C16 const metadata definitions (True, False, True): (0, 71), insns 239/239

font C16 const metadata definitions (True, True, False): (0, 72), insns 239/239

font C16 const metadata definitions (True, True, True): (0, 66), insns 239/239

font C16 metadata declaration initializers ('countSheet', 'sheetGlyphCount', 'dataBlockCount'): (0, 44), insns 239/239

font C16 metadata declaration initializers ('countSheet', 'dataBlockCount', 'sheetGlyphCount'): (2, 43), insns 239/239

font C16 metadata declaration initializers ('sheetGlyphCount', 'countSheet', 'dataBlockCount'): (0, 44), insns 239/239

font C16 metadata declaration initializers ('sheetGlyphCount', 'dataBlockCount', 'countSheet'): (0, 44), insns 239/239

font C16 metadata declaration initializers ('dataBlockCount', 'countSheet', 'sheetGlyphCount'): (2, 43), insns 239/239

font C16 metadata declaration initializers ('dataBlockCount', 'sheetGlyphCount', 'countSheet'): (2, 44), insns 239/239

font C17 metadata helper boundary font-endFalse: (0, 99), insns 239/239

font C17 metadata helper boundary font-endTrue: (0, 99), insns 239/239

font C17 metadata helper boundary font-groups-endFalse: (47, 121), insns 239/239

font C17 metadata helper boundary font-groups-endTrue: (47, 121), insns 239/239

font C17 metadata helper boundary font-spanFalse: (0, 99), insns 239/239

font C17 metadata helper boundary font-spanTrue: (0, 99), insns 239/239

font C17 metadata helper boundary font-groups-spanFalse: (47, 121), insns 239/239

font C17 metadata helper boundary font-groups-spanTrue: (47, 121), insns 239/239

http C18 lowercase predicate/result representation 0: (13, 32), insns 126/124

http C18 lowercase predicate/result representation 1: (4, 5), insns 124/124

http C18 lowercase predicate/result representation 2: (4, 5), insns 124/124

http C18 lowercase predicate/result representation 3: (4, 5), insns 124/124

http C18 lowercase predicate/result representation 4: (12, 38), insns 126/124

http C18 lowercase predicate/result representation 5: (12, 38), insns 126/124

http C18 lowercase predicate/result representation 6: (12, 38), insns 126/124

http C18 lowercase predicate/result representation 7: (4, 5), insns 124/124

http C18 lowercase predicate/result representation 8: (13, 90), insns 126/124

http C18 lowercase predicate/result representation 9: (4, 5), insns 124/124

http C18 lowercase predicate/result representation 10: (13, 92), insns 128/124

http C18 lowercase predicate/result representation 11: (13, 92), insns 128/124

font C19 set booleans consolidated named locals: (0, 44), insns 239/239

font C20 file-relative address integer addition name: (0, 43), insns 239/239

font C20 file-relative address integer addition flags: (0, 44), insns 239/239

font C20 file-relative address integer addition both: (0, 43), insns 239/239

http C21 lowercase helper placement before header lookup: (4, 5), insns 124/124

http C21 lowercase helper placement before read helper: (4, 5), insns 124/124

http C21 lowercase helper placement before compare: (4, 5), insns 124/124

font C22 POD metadata field order ('countSheet', 'sheetGlyphCount', 'dataBlockCount'): ild/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -Cpp_exceptions off -lang=c++ -MMD -c libs/NW4R/src/ut/ut_ArchiveFontBase.cpp -o build/43U/src/libs/NW4R/src/ut && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/NW4R/src/ut/ut_ArchiveFontBase.d build/43U/src/libs/NW4R/src/ut/ut_ArchiveFontBase.d
### mwcceppc.exe Compiler:
#    File: libs\NW4R\src\ut\ut_ArchiveFontBase.cpp
# ------------------------------------------------
#     364:                 metrics.sheetGlyphCount = groups->inner.metrics.sheetGlyphCount;
#   Error:                                                         ^^^^^^^
#   (10140) undefined identifier 'metrics'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


font C22 POD metadata field order ('countSheet', 'dataBlockCount', 'sheetGlyphCount'): ild/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -Cpp_exceptions off -lang=c++ -MMD -c libs/NW4R/src/ut/ut_ArchiveFontBase.cpp -o build/43U/src/libs/NW4R/src/ut && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/NW4R/src/ut/ut_ArchiveFontBase.d build/43U/src/libs/NW4R/src/ut/ut_ArchiveFontBase.d
### mwcceppc.exe Compiler:
#    File: libs\NW4R\src\ut\ut_ArchiveFontBase.cpp
# ------------------------------------------------
#     364:                 metrics.sheetGlyphCount = groups->inner.metrics.sheetGlyphCount;
#   Error:                                                         ^^^^^^^
#   (10140) undefined identifier 'metrics'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


font C22 POD metadata field order ('sheetGlyphCount', 'countSheet', 'dataBlockCount'): ild/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -Cpp_exceptions off -lang=c++ -MMD -c libs/NW4R/src/ut/ut_ArchiveFontBase.cpp -o build/43U/src/libs/NW4R/src/ut && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/NW4R/src/ut/ut_ArchiveFontBase.d build/43U/src/libs/NW4R/src/ut/ut_ArchiveFontBase.d
### mwcceppc.exe Compiler:
#    File: libs\NW4R\src\ut\ut_ArchiveFontBase.cpp
# ------------------------------------------------
#     364:                 metrics.sheetGlyphCount = groups->inner.metrics.sheetGlyphCount;
#   Error:                                                         ^^^^^^^
#   (10140) undefined identifier 'metrics'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


font C22 POD metadata field order ('sheetGlyphCount', 'dataBlockCount', 'countSheet'): ild/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -Cpp_exceptions off -lang=c++ -MMD -c libs/NW4R/src/ut/ut_ArchiveFontBase.cpp -o build/43U/src/libs/NW4R/src/ut && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/NW4R/src/ut/ut_ArchiveFontBase.d build/43U/src/libs/NW4R/src/ut/ut_ArchiveFontBase.d
### mwcceppc.exe Compiler:
#    File: libs\NW4R\src\ut\ut_ArchiveFontBase.cpp
# ------------------------------------------------
#     364:                 metrics.sheetGlyphCount = groups->inner.metrics.sheetGlyphCount;
#   Error:                                                         ^^^^^^^
#   (10140) undefined identifier 'metrics'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


font C22 POD metadata field order ('dataBlockCount', 'countSheet', 'sheetGlyphCount'): ild/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -Cpp_exceptions off -lang=c++ -MMD -c libs/NW4R/src/ut/ut_ArchiveFontBase.cpp -o build/43U/src/libs/NW4R/src/ut && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/NW4R/src/ut/ut_ArchiveFontBase.d build/43U/src/libs/NW4R/src/ut/ut_ArchiveFontBase.d
### mwcceppc.exe Compiler:
#    File: libs\NW4R\src\ut\ut_ArchiveFontBase.cpp
# ------------------------------------------------
#     364:                 metrics.sheetGlyphCount = groups->inner.metrics.sheetGlyphCount;
#   Error:                                                         ^^^^^^^
#   (10140) undefined identifier 'metrics'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


font C22 POD metadata field order ('dataBlockCount', 'sheetGlyphCount', 'countSheet'): ild/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -Cpp_exceptions off -lang=c++ -MMD -c libs/NW4R/src/ut/ut_ArchiveFontBase.cpp -o build/43U/src/libs/NW4R/src/ut && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/NW4R/src/ut/ut_ArchiveFontBase.d build/43U/src/libs/NW4R/src/ut/ut_ArchiveFontBase.d
### mwcceppc.exe Compiler:
#    File: libs\NW4R\src\ut\ut_ArchiveFontBase.cpp
# ------------------------------------------------
#     364:                 metrics.sheetGlyphCount = groups->inner.metrics.sheetGlyphCount;
#   Error:                                                         ^^^^^^^
#   (10140) undefined identifier 'metrics'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


font C22 POD metadata field order ('countSheet', 'sheetGlyphCount', 'dataBlockCount'): (0, 44), insns 239/239

font C22 POD metadata field order ('countSheet', 'dataBlockCount', 'sheetGlyphCount'): (0, 44), insns 239/239

font C22 POD metadata field order ('sheetGlyphCount', 'countSheet', 'dataBlockCount'): (0, 73), insns 239/239

font C22 POD metadata field order ('sheetGlyphCount', 'dataBlockCount', 'countSheet'): (0, 73), insns 239/239

font C22 POD metadata field order ('dataBlockCount', 'countSheet', 'sheetGlyphCount'): (0, 73), insns 239/239

font C22 POD metadata field order ('dataBlockCount', 'sheetGlyphCount', 'countSheet'): (0, 73), insns 239/239

http C23 read-only termination parameter views (False, False): (4, 5), insns 124/124

http C23 read-only termination parameter views (False, True): (4, 5), insns 124/124

http C23 read-only termination parameter views (True, False): (6, 72), insns 125/124

http C23 read-only termination parameter views (True, True): (6, 72), insns 125/124

font C24 const context pointer metadata: (0, 43), insns 239/239

font C24 const context pointer entry: (0, 43), insns 239/239

font C24 const context reference metadata: (2, 52), insns 239/239

font C24 const context reference entry: (2, 52), insns 239/239

C25 final registry search: NHTTP six declaration-only permutations remain structural4/exact5,124insns,frame0x30. Font main declaration-only280 trials remain structural0/exact43,239insns,frame0x40. Group helper declaration-only52 trials remain structural0/exact43. No candidate retained from failed compilations.
declaration block:
      NHTTPi_HDRBUFLIST* block;
      s32 offset;
      int character;
start (4, 5)
best (4, 5) after 6 builds; source restored; best order was:
    NHTTPi_HDRBUFLIST* block;
    s32 offset;
    int character;
declaration block:
                  const HeaderedGlyphGroups* pGlgr;
                  int sheetIndex;
                  u16* sheetOffset;
                  int groupIndex;
                  const char* includedGroups;
                  u16 offset;
                  const char* name;
start (0, 43)
best (0, 43) after 52 builds; source restored; best order was:
                const HeaderedGlyphGroups* pGlgr;
                int sheetIndex;
                u16* sheetOffset;
                int groupIndex;
                const char* includedGroups;
                u16 offset;
                const char* name;
declaration block:
                  const HeaderedGlyphGroups* groups;
                  HeaderedGlyphGroups* pGlgr;
                  const ArchiveFontBinaryLayout* font;
                  u32 flagsSheetsOff;
                  u32 glgrInnerLen;
                  u16 countSheet;
                  u16 sheetGlyphCount;
                  u16 dataBlockCount;
                  const u32* flagsSheets;
                  u8* glgrEnd;
                  u32 expectedMaxSize;
                  u32 sheetOffsetsSize;
                  u16* sheetOffsetsScratch;
                  u32 sheetOffsetsScratchSize;
                  u32 stepSheetFlags;
start (0, 43)
best (0, 43) after 280 builds; source restored; best order was:
                const HeaderedGlyphGroups* groups;
                HeaderedGlyphGroups* pGlgr;
                const ArchiveFontBinaryLayout* font;
                u32 flagsSheetsOff;
                u32 glgrInnerLen;
                u16 countSheet;
                u16 sheetGlyphCount;
                u16 dataBlockCount;
                const u32* flagsSheets;
                u8* glgrEnd;
                u32 expectedMaxSize;
                u32 sheetOffsetsSize;
                u16* sheetOffsetsScratch;
                u32 sheetOffsetsScratchSize;
                u32 stepSheetFlags;

Final open-function audit: NHTTP compare remains open after C1 operand order,C2 byte widths,C4 complete inline boundary,C5 lowercase bounds helper,C8 independent lowercase forms,C14 loops,C18 boolean/return type forms,C21 helper placement,C23 const parameter views and six final declaration permutations. GLGR remains open after C3/C17 inline boundaries,C6 metadata views,C7 declaration search,C9 assignments,C10 cursors/operand order,C11 alias/scope,C13 widths,C15 helper views,C16 definitions,C19 named helper locals,C20 relative offset operands,C22 POD metadata,C24 const context views and final declaration searches. Both have far more than three distinct source-level attempts; no untried owned function.
NHTTP extent0x1f0 ends814966b0, exactly nextload symbol; GLGR extent0x3bc ends815158e4, exactly nextFINF. No overlap, no extent edits. No immediate stack store/reload evidence in either target, so no volatile added. No byte-before-shift widening discrepancy applies. Font data96/96 and NHTTP no data, so no symbol pairing rename or type extent change warranted.
Final source: added const header read view, declared real locals in selected order, explicit scratch cursors, operand order in actual group/name calculations. Instruction counts preserved; first111 GLGR instructions exact; remaining43 register/operand differences. NHTTP original five preheader scheduling differences unchanged. Final clean full gate follows.

Final full clean gate (both owned units, not --quick):
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] pool: IDENTICAL
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] objdiff: code 1196/1692 data None/None functions 6/7 fuzzy 99.2151 linked code 0
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] instruction-exact functions: 6/7
[libs/RevoEX/src/nhttp/NHTTP_recvbuf]   section .text size 1692 match 99.21513
[libs/RevoEX/src/nhttp/NHTTP_recvbuf]   below 100: NHTTPi_compareTokenN_HdrRecvBuf 97.32258
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] baseline: code 1196/1692 data None functions 6 fuzzy 99.2151
[libs/NW4R/src/ut/ut_ArchiveFontBase] pool: IDENTICAL
[libs/NW4R/src/ut/ut_ArchiveFontBase] objdiff: code 4164/5120 data 96/96 functions 22/23 fuzzy 99.7812 linked code 0
[libs/NW4R/src/ut/ut_ArchiveFontBase] instruction-exact functions: 22/23
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .data size 88 match 100.0
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .sbss2 size 8 match 100.0
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .text size 5120 match 99.78125
[libs/NW4R/src/ut/ut_ArchiveFontBase]   below 100: ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader 98.82845
[libs/NW4R/src/ut/ut_ArchiveFontBase] baseline: code 4164/5120 data 96 functions 22 fuzzy 98.5227
regressions vs baseline: 0
global matched_code_percent: 90.80962 -> 90.80962
global fuzzy_match_percent: 99.58569 -> 99.58785
global complete_code_percent: 71.43246 -> 71.43246
global matched_data_percent: 99.36639 -> 99.36639
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
HIGH continuation result: no new exact function. NHTTP6/7->6/7, exact code1196/1692 unchanged, no data, compare97.32258% unchanged withfive invariant scheduling differences. ArchiveFontBase22/23->22/23, exact code4164/5120 unchanged, data96/96 unchanged; GLGR92.08787->98.82845%,87->43 positionaldifferences, matching239instructions/frame0x40 and complete instruction/operand structure except register allocation and commuting register operands. Main declaration search439+280trials, helper52 and HTTP6; individual source alternatives C1-C24 logged. No new asm, volatile, pinned data, config or sharedheader edits. Only Font source plus this log changed. Full build/DOL hash PASS, pools identical, regressions0, forbidden0,readability0. Partial fuzzy improvement is preserved for next effort round; exact objective remains open.

# XHIGH on retained HIGH branch
HEAD 9b34a9d2367f44c48d5e9e848f3f1e14edb7c894 origin/main 29fe1efaf200c57ac4e229c08a373aece57983a1
Origin/main owned sources remain old baseline, no newly exact owned function. Start GLGR98.82845%,43 register/operand differences at239/239instructions,frame0x40,exact22/23,code4164/5120,data96/96. NHTTP97.32258%,five invariant scheduling differences,124/124insns,frame0x30,exact6/7,code1196/1692,no data. Font pool identical0/0; no data rename/extent correction needed. No immediate store/reload volatile or byte-before-shift widening evidence.
font XHIGH X1 inline metrics setter ('countSheet', 'sheetGlyphCount', 'dataBlockCount'): (0, 43), insns 239/239
font XHIGH X1 inline metrics setter ('countSheet', 'dataBlockCount', 'sheetGlyphCount'): (0, 43), insns 239/239
font XHIGH X1 inline metrics setter ('sheetGlyphCount', 'countSheet', 'dataBlockCount'): (0, 43), insns 239/239
font XHIGH X1 inline metrics setter ('sheetGlyphCount', 'dataBlockCount', 'countSheet'): (0, 43), insns 239/239
font XHIGH X1 inline metrics setter ('dataBlockCount', 'countSheet', 'sheetGlyphCount'): (0, 43), insns 239/239
font XHIGH X1 inline metrics setter ('dataBlockCount', 'sheetGlyphCount', 'countSheet'): (0, 43), insns 239/239
font XHIGH X2 separate const file header entry: (0, 43), insns 239/239
font XHIGH X2 separate const file header metadata: (0, 43), insns 239/239
font XHIGH X2 separate const file header initialization: (0, 43), insns 239/239
font XHIGH X2 group reference: (0, 72), insns 239/239
font XHIGH X2 font reference: (0, 43), insns 239/239
font XHIGH X2 header reference: (0, 43), insns 239/239
font XHIGH X3 direct const count reads in calculations (False, False, False): (0, 43), insns 239/239
font XHIGH X3 direct const count reads in calculations (False, False, True): (0, 44), insns 239/239
font XHIGH X3 direct const count reads in calculations (False, True, False): (0, 44), insns 239/239
font XHIGH X3 direct const count reads in calculations (False, True, True): (0, 44), insns 239/239
font XHIGH X3 direct const count reads in calculations (True, False, False): (0, 74), insns 239/239
font XHIGH X3 direct const count reads in calculations (True, False, True): (0, 74), insns 239/239
font XHIGH X3 direct const count reads in calculations (True, True, False): (0, 74), insns 239/239
font XHIGH X3 direct const count reads in calculations (True, True, True): (0, 74), insns 239/239
font XHIGH X3 offset inline helper header pointer: (0, 44), insns 239/239
font XHIGH X3 offset inline helper inner pointer: (0, 44), insns 239/239
font XHIGH X3 offset inline helper header reference: (0, 44), insns 239/239
font XHIGH X3 offset inline helper font pointer: (25, 133), insns 240/239
font XHIGH X3 inspect metadata color variation 4: (0, 74), insns 239/239
font XHIGH X3 inspect metadata color variation 2: (0, 44), insns 239/239
font XHIGH X3 inspect metadata color variation 1: (0, 44), insns 239/239
font XHIGH X4 flatten inline-helper scopes (False, False, False, False): (0, 43), insns 239/239
font XHIGH X4 flatten inline-helper scopes (False, False, False, True): (0, 43), insns 239/239
font XHIGH X4 flatten inline-helper scopes (False, False, True, False): (0, 51), insns 239/239
font XHIGH X4 flatten inline-helper scopes (False, False, True, True): (0, 51), insns 239/239
font XHIGH X4 flatten inline-helper scopes (True, False, False, False): (0, 72), insns 239/239
font XHIGH X4 flatten inline-helper scopes (True, False, False, True): (0, 72), insns 239/239
font XHIGH X4 flatten inline-helper scopes (True, False, True, False): (0, 79), insns 239/239
font XHIGH X4 flatten inline-helper scopes (True, False, True, True): (0, 79), insns 239/239
font XHIGH X4 flatten inline-helper scopes (True, True, False, False): (0, 74), insns 239/239
font XHIGH X4 flatten inline-helper scopes (True, True, False, True): (0, 74), insns 239/239
font XHIGH X4 flatten inline-helper scopes (True, True, True, False): (0, 81), insns 239/239
font XHIGH X4 flatten inline-helper scopes (True, True, True, True): (0, 81), insns 239/239
font XHIGH X4 inspect flattened allocation 8: (0, 72), insns 239/239
font XHIGH X4 inspect flattened allocation 12: (0, 74), insns 239/239
font XHIGH X4 inspect flattened allocation 15: (0, 81), insns 239/239
font XHIGH X5 combine helper flatten 8 and const reads (False, False, False): (0, 72), insns 239/239
font XHIGH X5 combine helper flatten 8 and const reads (False, False, True): (0, 72), insns 239/239
font XHIGH X5 combine helper flatten 8 and const reads (False, True, False): (0, 72), insns 239/239
font XHIGH X5 combine helper flatten 8 and const reads (False, True, True): (0, 72), insns 239/239
font XHIGH X5 combine helper flatten 8 and const reads (True, False, False): (0, 45), insns 239/239
font XHIGH X5 combine helper flatten 8 and const reads (True, False, True): (0, 45), insns 239/239
font XHIGH X5 combine helper flatten 8 and const reads (True, True, False): (0, 45), insns 239/239
font XHIGH X5 combine helper flatten 8 and const reads (True, True, True): (0, 45), insns 239/239
font XHIGH X5 combine helper flatten 10 and const reads (False, False, False): (0, 79), insns 239/239
font XHIGH X5 combine helper flatten 10 and const reads (False, False, True): (0, 79), insns 239/239
font XHIGH X5 combine helper flatten 10 and const reads (False, True, False): (0, 79), insns 239/239
font XHIGH X5 combine helper flatten 10 and const reads (False, True, True): (0, 79), insns 239/239
font XHIGH X5 combine helper flatten 10 and const reads (True, False, False): (0, 53), insns 239/239
font XHIGH X5 combine helper flatten 10 and const reads (True, False, True): (0, 53), insns 239/239
font XHIGH X5 combine helper flatten 10 and const reads (True, True, False): (0, 53), insns 239/239
font XHIGH X5 combine helper flatten 10 and const reads (True, True, True): (0, 53), insns 239/239
font XHIGH X5 combine helper flatten 12 and const reads (False, False, False): (0, 74), insns 239/239
font XHIGH X5 combine helper flatten 12 and const reads (False, False, True): (0, 74), insns 239/239
font XHIGH X5 combine helper flatten 12 and const reads (False, True, False): (0, 74), insns 239/239
font XHIGH X5 combine helper flatten 12 and const reads (False, True, True): (0, 74), insns 239/239
font XHIGH X5 combine helper flatten 12 and const reads (True, False, False): (0, 47), insns 239/239
font XHIGH X5 combine helper flatten 12 and const reads (True, False, True): (0, 47), insns 239/239
font XHIGH X5 combine helper flatten 12 and const reads (True, True, False): (0, 47), insns 239/239
font XHIGH X5 combine helper flatten 12 and const reads (True, True, True): (0, 47), insns 239/239
font XHIGH X5 combine helper flatten 14 and const reads (False, False, False): (0, 81), insns 239/239
font XHIGH X5 combine helper flatten 14 and const reads (False, False, True): (0, 81), insns 239/239
font XHIGH X5 combine helper flatten 14 and const reads (False, True, False): (0, 81), insns 239/239
font XHIGH X5 combine helper flatten 14 and const reads (False, True, True): (0, 81), insns 239/239
font XHIGH X5 combine helper flatten 14 and const reads (True, False, False): (0, 55), insns 239/239
font XHIGH X5 combine helper flatten 14 and const reads (True, False, True): (0, 55), insns 239/239
font XHIGH X5 combine helper flatten 14 and const reads (True, True, False): (0, 55), insns 239/239
font XHIGH X5 combine helper flatten 14 and const reads (True, True, True): (0, 55), insns 239/239
font XHIGH X5 inspect combined color map: (0, 45), insns 239/239
font XHIGH X6 base immutable metadata flagsSheets False: (0, 53), insns 239/239
font XHIGH X6 base immutable metadata flagsSheets True: (0, 53), insns 239/239
font XHIGH X6 base immutable metadata sheetOffsetsScratch False: (0, 48), insns 239/239
font XHIGH X6 base immutable metadata sheetOffsetsScratch True: (0, 48), insns 239/239
font XHIGH X6 base immutable metadata sheetOffsetsSize False: (0, 48), insns 239/239
font XHIGH X6 base immutable metadata sheetOffsetsSize True: (0, 48), insns 239/239
font XHIGH X6 base immutable metadata stepSheetFlags False: (0, 43), insns 239/239
font XHIGH X6 base immutable metadata stepSheetFlags True: (0, 43), insns 239/239
font XHIGH X6 base immutable metadata flagsSheetsOff False: (0, 43), insns 239/239
font XHIGH X6 base immutable metadata flagsSheetsOff True: (0, 43), insns 239/239
font XHIGH X6 base const metadata definitions (False, False, False, True, True): (0, 43), insns 239/239
font XHIGH X6 base const metadata definitions (False, False, True, False, True): (0, 48), insns 239/239
font XHIGH X6 base const metadata definitions (False, False, True, True, False): (0, 48), insns 239/239
font XHIGH X6 base const metadata definitions (False, False, True, True, True): (0, 48), insns 239/239
font XHIGH X6 base const metadata definitions (False, True, False, False, True): (0, 48), insns 239/239
font XHIGH X6 base const metadata definitions (False, True, False, True, False): (0, 48), insns 239/239
font XHIGH X6 base const metadata definitions (False, True, False, True, True): (0, 48), insns 239/239
font XHIGH X6 base const metadata definitions (False, True, True, False, False): (0, 48), insns 239/239
font XHIGH X6 base const metadata definitions (False, True, True, False, True): (0, 48), insns 239/239
font XHIGH X6 base const metadata definitions (False, True, True, True, False): (0, 48), insns 239/239
font XHIGH X6 base const metadata definitions (False, True, True, True, True): (0, 48), insns 239/239
font XHIGH X6 base const metadata definitions (True, False, False, False, True): (0, 53), insns 239/239
font XHIGH X6 base const metadata definitions (True, False, False, True, False): (0, 53), insns 239/239
font XHIGH X6 base const metadata definitions (True, False, False, True, True): (0, 53), insns 239/239
font XHIGH X6 base const metadata definitions (True, False, True, False, False): (0, 53), insns 239/239
font XHIGH X6 base const metadata definitions (True, False, True, False, True): (0, 53), insns 239/239
font XHIGH X6 base const metadata definitions (True, False, True, True, False): (0, 53), insns 239/239
font XHIGH X6 base const metadata definitions (True, False, True, True, True): (0, 53), insns 239/239
font XHIGH X6 base const metadata definitions (True, True, False, False, False): (0, 53), insns 239/239
font XHIGH X6 base const metadata definitions (True, True, False, False, True): (0, 53), insns 239/239
font XHIGH X6 base const metadata definitions (True, True, False, True, False): (0, 53), insns 239/239
font XHIGH X6 base const metadata definitions (True, True, False, True, True): (0, 53), insns 239/239
font XHIGH X6 base const metadata definitions (True, True, True, False, False): (0, 53), insns 239/239
font XHIGH X6 base const metadata definitions (True, True, True, False, True): (0, 53), insns 239/239
font XHIGH X6 base const metadata definitions (True, True, True, True, False): (0, 53), insns 239/239
font XHIGH X6 base const metadata definitions (True, True, True, True, True): (0, 53), insns 239/239
font XHIGH X6 flat immutable metadata flagsSheets False: (0, 53), insns 239/239
font XHIGH X6 flat immutable metadata flagsSheets True: (0, 53), insns 239/239
font XHIGH X6 flat immutable metadata sheetOffsetsScratch False: (0, 45), insns 239/239
font XHIGH X6 flat immutable metadata sheetOffsetsScratch True: (0, 45), insns 239/239
font XHIGH X6 flat immutable metadata sheetOffsetsSize False: (0, 48), insns 239/239
font XHIGH X6 flat immutable metadata sheetOffsetsSize True: (0, 48), insns 239/239
font XHIGH X6 flat immutable metadata stepSheetFlags False: (0, 45), insns 239/239
font XHIGH X6 flat immutable metadata stepSheetFlags True: (0, 45), insns 239/239
font XHIGH X6 flat immutable metadata flagsSheetsOff False: (0, 45), insns 239/239
font XHIGH X6 flat immutable metadata flagsSheetsOff True: (0, 45), insns 239/239
font XHIGH X6 flat const metadata definitions (False, False, False, True, True): (0, 45), insns 239/239
font XHIGH X6 flat const metadata definitions (False, False, True, False, True): (0, 48), insns 239/239
font XHIGH X6 flat const metadata definitions (False, False, True, True, False): (0, 48), insns 239/239
font XHIGH X6 flat const metadata definitions (False, False, True, True, True): (0, 48), insns 239/239
font XHIGH X6 flat const metadata definitions (False, True, False, False, True): (0, 45), insns 239/239
font XHIGH X6 flat const metadata definitions (False, True, False, True, False): (0, 45), insns 239/239
font XHIGH X6 flat const metadata definitions (False, True, False, True, True): (0, 45), insns 239/239
font XHIGH X6 flat const metadata definitions (False, True, True, False, False): (0, 45), insns 239/239
font XHIGH X6 flat const metadata definitions (False, True, True, False, True): (0, 45), insns 239/239
font XHIGH X6 flat const metadata definitions (False, True, True, True, False): (0, 45), insns 239/239
font XHIGH X6 flat const metadata definitions (False, True, True, True, True): (0, 45), insns 239/239
font XHIGH X6 flat const metadata definitions (True, False, False, False, True): (0, 53), insns 239/239
font XHIGH X6 flat const metadata definitions (True, False, False, True, False): (0, 53), insns 239/239
font XHIGH X6 flat const metadata definitions (True, False, False, True, True): (0, 53), insns 239/239
font XHIGH X6 flat const metadata definitions (True, False, True, False, False): (0, 53), insns 239/239
font XHIGH X6 flat const metadata definitions (True, False, True, False, True): (0, 53), insns 239/239
font XHIGH X6 flat const metadata definitions (True, False, True, True, False): (0, 53), insns 239/239
font XHIGH X6 flat const metadata definitions (True, False, True, True, True): (0, 53), insns 239/239
font XHIGH X6 flat const metadata definitions (True, True, False, False, False): (0, 50), insns 239/239
font XHIGH X6 flat const metadata definitions (True, True, False, False, True): (0, 50), insns 239/239
font XHIGH X6 flat const metadata definitions (True, True, False, True, False): (0, 50), insns 239/239
font XHIGH X6 flat const metadata definitions (True, True, False, True, True): (0, 50), insns 239/239
font XHIGH X6 flat const metadata definitions (True, True, True, False, False): (0, 50), insns 239/239
font XHIGH X6 flat const metadata definitions (True, True, True, False, True): (0, 50), insns 239/239
font XHIGH X6 flat const metadata definitions (True, True, True, True, False): (0, 50), insns 239/239
font XHIGH X6 flat const metadata definitions (True, True, True, True, True): (0, 50), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('u16', 'u16', 'u16'): (0, 43), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('u16', 'u16', 'u32'): (0, 67), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('u16', 'u16', 's32'): (0, 67), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('u16', 'u32', 'u16'): (0, 67), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('u16', 'u32', 'u32'): (0, 67), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('u16', 'u32', 's32'): (0, 67), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('u16', 's32', 'u16'): (0, 67), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('u16', 's32', 'u32'): (0, 67), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('u16', 's32', 's32'): (0, 67), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('u32', 'u16', 'u16'): (0, 67), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('u32', 'u16', 'u32'): (0, 66), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('u32', 'u16', 's32'): (0, 66), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('u32', 'u32', 'u16'): (0, 67), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('u32', 'u32', 'u32'): (0, 62), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('u32', 'u32', 's32'): (0, 62), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('u32', 's32', 'u16'): (0, 67), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('u32', 's32', 'u32'): (0, 62), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('u32', 's32', 's32'): (0, 62), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('s32', 'u16', 'u16'): (0, 67), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('s32', 'u16', 'u32'): (0, 66), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('s32', 'u16', 's32'): (0, 66), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('s32', 'u32', 'u16'): (0, 67), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('s32', 'u32', 'u32'): (0, 62), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('s32', 'u32', 's32'): (0, 62), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('s32', 's32', 'u16'): (0, 67), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('s32', 's32', 'u32'): (0, 62), insns 239/239
font XHIGH X7 base cached field widths with u16 copy extent ('s32', 's32', 's32'): (0, 62), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('u16', 'u16', 'u16'): (0, 45), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('u16', 'u16', 'u32'): (0, 67), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('u16', 'u16', 's32'): (0, 67), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('u16', 'u32', 'u16'): (0, 68), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('u16', 'u32', 'u32'): (0, 68), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('u16', 'u32', 's32'): (0, 68), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('u16', 's32', 'u16'): (0, 68), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('u16', 's32', 'u32'): (0, 68), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('u16', 's32', 's32'): (0, 68), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('u32', 'u16', 'u16'): (0, 45), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('u32', 'u16', 'u32'): (0, 67), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('u32', 'u16', 's32'): (0, 67), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('u32', 'u32', 'u16'): (0, 68), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('u32', 'u32', 'u32'): (0, 68), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('u32', 'u32', 's32'): (0, 68), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('u32', 's32', 'u16'): (0, 68), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('u32', 's32', 'u32'): (0, 68), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('u32', 's32', 's32'): (0, 68), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('s32', 'u16', 'u16'): (0, 45), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('s32', 'u16', 'u32'): (0, 67), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('s32', 'u16', 's32'): (0, 67), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('s32', 'u32', 'u16'): (0, 68), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('s32', 'u32', 'u32'): (0, 68), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('s32', 'u32', 's32'): (0, 68), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('s32', 's32', 'u16'): (0, 68), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('s32', 's32', 'u32'): (0, 68), insns 239/239
font XHIGH X7 flat cached field widths with u16 copy extent ('s32', 's32', 's32'): (0, 68), insns 239/239
font XHIGH X7 allocation/lifetime segment base-1: (0, 67), insns 239/239
font XHIGH X7 allocation/lifetime segment base-3: (0, 67), insns 239/239
font XHIGH X7 allocation/lifetime segment base-9: (0, 67), insns 239/239
font XHIGH X7 allocation/lifetime segment base-13: (0, 62), insns 239/239
font XHIGH X7 allocation/lifetime segment flat-1: (0, 67), insns 239/239
font XHIGH X7 allocation/lifetime segment flat-3: (0, 68), insns 239/239
font XHIGH X7 allocation/lifetime segment flat-9: (0, 45), insns 239/239
font XHIGH X7 allocation/lifetime segment flat-13: (0, 68), insns 239/239
font XHIGH X8 base SDK sheet offset extent helper: (0, 68), insns 239/239
font XHIGH X8 base scratch helper value u16 returns size: (20, 98), insns 239/239
font XHIGH X8 base scratch helper value u16 returns pointer: (20, 98), insns 239/239
font XHIGH X8 base scratch helper value u32 returns size: (20, 98), insns 239/239
font XHIGH X8 base scratch helper value u32 returns pointer: (20, 98), insns 239/239
font XHIGH X8 base scratch helper context u16 returns size: (2, 86), insns 239/239
font XHIGH X8 base scratch helper context u16 returns pointer: (2, 86), insns 239/239
font XHIGH X8 base scratch helper context u32 returns size: (2, 86), insns 239/239
font XHIGH X8 base scratch helper context u32 returns pointer: (2, 86), insns 239/239
font XHIGH X8 flat SDK sheet offset extent helper: (0, 72), insns 239/239
font XHIGH X8 flat scratch helper value u16 returns size: (20, 96), insns 239/239
font XHIGH X8 flat scratch helper value u16 returns pointer: (20, 96), insns 239/239
font XHIGH X8 flat scratch helper value u32 returns size: (20, 96), insns 239/239
font XHIGH X8 flat scratch helper value u32 returns pointer: (20, 96), insns 239/239
font XHIGH X8 flat scratch helper context u16 returns size: (2, 84), insns 239/239
font XHIGH X8 flat scratch helper context u16 returns pointer: (2, 84), insns 239/239
font XHIGH X8 flat scratch helper context u32 returns size: (2, 84), insns 239/239
font XHIGH X8 flat scratch helper context u32 returns pointer: (2, 84), insns 239/239
font XHIGH X9 direct signed flag stride ((s32)countSheet + 31) / 32 * 4: (0, 43), insns 239/239
font XHIGH X9 direct signed flag stride (countSheet + 31) / 32 * 4: (0, 43), insns 239/239
font XHIGH X9 direct signed flag stride ((s32)countSheet + 31) / 32 << 2: (0, 43), insns 239/239
font XHIGH X9 direct signed flag stride ((s32)(countSheet + 31) / 32) * 4: (0, 43), insns 239/239
font XHIGH X9 direct signed flag stride (31 + (s32)countSheet) / 32 * 4: (0, 43), insns 239/239
font XHIGH X9 stride inline argument u16: (0, 43), insns 239/239
font XHIGH X9 stride inline argument s32: (0, 43), insns 239/239
font XHIGH X9 stride inline argument const u16: (0, 43), insns 239/239
font XHIGH X9 stride inline argument const u32: (0, 43), insns 239/239
font XHIGH X10 cache unchanged file-header block count u16 after font: (7, 152), insns 239/239
font XHIGH X10 cache unchanged file-header block count u16 before signature: (7, 152), insns 239/239
font XHIGH X10 cache unchanged file-header block count u16 after work check: (4, 110), insns 239/239
font XHIGH X10 cache unchanged file-header block count u16 after expected size: (4, 110), insns 239/239
font XHIGH X10 cache unchanged file-header block count u16 after glgr copy: (5, 78), insns 239/239
font XHIGH X10 cache unchanged file-header block count u16 before validation: (5, 78), insns 239/239
font XHIGH X10 cache unchanged file-header block count u32 after font: (7, 157), insns 239/239
font XHIGH X10 cache unchanged file-header block count u32 before signature: (7, 157), insns 239/239
font XHIGH X10 cache unchanged file-header block count u32 after work check: (4, 120), insns 239/239
font XHIGH X10 cache unchanged file-header block count u32 after expected size: (4, 120), insns 239/239
font XHIGH X10 cache unchanged file-header block count u32 after glgr copy: (5, 93), insns 239/239
font XHIGH X10 cache unchanged file-header block count u32 before validation: (5, 93), insns 239/239
font XHIGH X8 inspect scratch helper colors base-context-u16-size: (2, 86), insns 239/239
font XHIGH X8 inspect scratch helper colors base-value-u16-size: (20, 98), insns 239/239
font XHIGH X8 inspect scratch helper colors flat-context-u16-size: (2, 84), insns 239/239
font XHIGH X11 flag stride local type u16: (1, 43), insns 239/239
font XHIGH X11 flag stride local type int: (0, 43), insns 239/239
font XHIGH X11 flag stride local type unsigned int: (0, 43), insns 239/239
font XHIGH X11 native block count type int: (0, 67), insns 239/239
font XHIGH X11 native block count type unsigned int: (0, 67), insns 239/239
font XHIGH X12 readonly metadata field references (False, False, False): (0, 43), insns 239/239
font XHIGH X12 readonly metadata field references (False, False, True): (5, 159), insns 239/239
font XHIGH X12 readonly metadata field references (False, True, False): (6, 159), insns 239/239
font XHIGH X12 readonly metadata field references (False, True, True): (7, 162), insns 239/239
font XHIGH X12 readonly metadata field references (True, False, False): (15, 96), insns 241/239
font XHIGH X12 readonly metadata field references (True, False, True): (17, 171), insns 241/239
font XHIGH X12 readonly metadata field references (True, True, False): (18, 171), insns 241/239
font XHIGH X12 readonly metadata field references (True, True, True): (25, 177), insns 241/239
font XHIGH X13 inner metadata helper cached widths (False, False, False): (0, 99), insns 239/239
font XHIGH X13 inner metadata helper cached widths (False, False, True): (0, 98), insns 239/239
font XHIGH X13 inner metadata helper cached widths (False, True, False): (0, 99), insns 239/239
font XHIGH X13 inner metadata helper cached widths (False, True, True): (0, 94), insns 239/239
font XHIGH X13 inner metadata helper cached widths (True, False, False): (0, 99), insns 239/239
font XHIGH X13 inner metadata helper cached widths (True, False, True): (0, 93), insns 239/239
font XHIGH X13 inner metadata helper cached widths (True, True, False): (0, 94), insns 239/239
font XHIGH X13 inner metadata helper cached widths (True, True, True): (0, 98), insns 239/239
font XHIGH X14 inner metadata font input opaque pointer: (0, 98), insns 239/239
font XHIGH X14 inner metadata font input byte pointer: (0, 98), insns 239/239
font XHIGH X14 inner metadata font input pointer reference: (0, 98), insns 239/239
font XHIGH X14 inner metadata font input object reference: (0, 98), insns 239/239
font XHIGH X14 inner metadata font input const pointer: (0, 98), insns 239/239
http XHIGH X15 lowercase expressions reverse False: (4, 5), insns 124/124
http XHIGH X15 lowercase expressions reverse True: (12, 40), insns 124/124
http XHIGH X15 lowercase macro reverse False: (4, 5), insns 124/124
http XHIGH X15 lowercase macro reverse True: (12, 40), insns 124/124
http XHIGH X15 lowercase scalar ABI s32 returns int: (4, 5), insns 124/124
http XHIGH X15 lowercase scalar ABI s32 returns s32: (4, 5), insns 124/124
http XHIGH X15 lowercase scalar ABI const s32 returns int: (4, 5), insns 124/124
http XHIGH X15 lowercase scalar ABI const s32 returns s32: (4, 5), insns 124/124
http XHIGH X15 lowercase scalar ABI unsigned int returns int: (35, 110), insns 129/124
http XHIGH X15 lowercase scalar ABI unsigned int returns s32: (35, 110), insns 129/124
font XHIGH X16 scratch plan counts wide False: (0, 43), insns 239/239
font XHIGH X16 scratch plan counts wide True: (0, 42), insns 239/239
font XHIGH X16 scratch plan work wide False: (0, 89), insns 239/239
font XHIGH X16 scratch plan work wide True: (0, 89), insns 239/239
font XHIGH X16 scratch plan combined wide False: (0, 89), insns 239/239
font XHIGH X16 scratch plan combined wide True: (0, 88), insns 239/239
font XHIGH X16 scratch plan mixed wide False: (0, 89), insns 239/239
font XHIGH X16 scratch plan mixed wide True: (0, 88), insns 239/239
font XHIGH X16 inspect wide metrics plan: (0, 42), insns 239/239
font XHIGH X17 full scratch plan pointers False readonly stride False: (0, 92), insns 239/239
font XHIGH X17 full scratch plan pointers False readonly stride True: (0, 93), insns 239/239
font XHIGH X17 full scratch plan pointers True readonly stride False: (0, 93), insns 239/239
font XHIGH X17 full scratch plan pointers True readonly stride True: (0, 92), insns 239/239
font XHIGH X18 metrics POD declaration search: 396 distinct builds, structural 0 and raw 72 -> 40; objdiff GLGR 98.91213% vs 98.82845% start. Readable scalar caching still preferred if same gain obtainable without type.
http XHIGH X19 readonly ASCII range ('int', 'int') const AsciiUppercaseRange* range leading: (8, 123), insns 128/124
http XHIGH X19 readonly ASCII range ('int', 'int') const AsciiUppercaseRange* range valid: (9, 122), insns 128/124
http XHIGH X19 readonly ASCII range ('int', 'int') const AsciiUppercaseRange* range read: (7, 102), insns 126/124
http XHIGH X19 readonly ASCII range ('int', 'int') AsciiUppercaseRange range leading: (21, 123), insns 132/124
http XHIGH X19 readonly ASCII range ('int', 'int') AsciiUppercaseRange range valid: (21, 122), insns 132/124
http XHIGH X19 readonly ASCII range ('int', 'int') AsciiUppercaseRange range read: (19, 109), insns 130/124
http XHIGH X19 readonly ASCII range ('s16', 's16') const AsciiUppercaseRange* range leading: (8, 123), insns 128/124
http XHIGH X19 readonly ASCII range ('s16', 's16') const AsciiUppercaseRange* range valid: (9, 122), insns 128/124
http XHIGH X19 readonly ASCII range ('s16', 's16') const AsciiUppercaseRange* range read: (9, 105), insns 128/124
http XHIGH X19 readonly ASCII range ('s16', 's16') AsciiUppercaseRange range leading: (21, 129), insns 134/124
http XHIGH X19 readonly ASCII range ('s16', 's16') AsciiUppercaseRange range valid: (21, 128), insns 134/124
http XHIGH X19 readonly ASCII range ('s16', 's16') AsciiUppercaseRange range read: (20, 112), insns 134/124
http XHIGH X19 readonly ASCII range ('s8', 's8') const AsciiUppercaseRange* range leading: (10, 120), insns 130/124
http XHIGH X19 readonly ASCII range ('s8', 's8') const AsciiUppercaseRange* range valid: (10, 119), insns 130/124
http XHIGH X19 readonly ASCII range ('s8', 's8') const AsciiUppercaseRange* range read: (10, 74), insns 128/124
http XHIGH X19 readonly ASCII range ('s8', 's8') AsciiUppercaseRange range leading: (25, 133), insns 138/124
http XHIGH X19 readonly ASCII range ('s8', 's8') AsciiUppercaseRange range valid: (25, 132), insns 138/124
http XHIGH X19 readonly ASCII range ('s8', 's8') AsciiUppercaseRange range read: (24, 116), insns 138/124
http XHIGH X20 named ASCII constants enum helper reverse False: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants enum helper reverse True: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants enum global reverse False: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants enum global reverse True: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants enum function reverse False: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants enum function reverse True: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants const int helper reverse False: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants const int helper reverse True: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants const int global reverse False: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants const int global reverse True: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants const int function reverse False: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants const int function reverse True: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants const s8 helper reverse False: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants const s8 helper reverse True: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants const s8 global reverse False: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants const s8 global reverse True: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants const s8 function reverse False: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants const s8 function reverse True: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants static const int helper reverse False: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants static const int helper reverse True: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants static const int global reverse False: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants static const int global reverse True: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants static const int function reverse False: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants static const int function reverse True: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants static const s8 helper reverse False: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants static const s8 helper reverse True: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants static const s8 global reverse False: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants static const s8 global reverse True: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants static const s8 function reverse False: (4, 5), insns 124/124
http XHIGH X20 named ASCII constants static const s8 function reverse True: (4, 5), insns 124/124
font XHIGH X21 cached sheet and data-block counts widened u32, glyph count remains u16, explicit u16 copy-length view; leading declaration search 394 builds: structural 0/raw66 ->33. Active wide scalar declarations now influence allocation; compare report before retaining.
declaration block:
      NHTTPi_HDRBUFLIST* block;
      s32 offset;
      int character;
start (4, 5)
best (4, 5) after 6 builds; source restored; best order was:
    NHTTPi_HDRBUFLIST* block;
    s32 offset;
    int character;

font XHIGH X22 target arithmetic operand order 0: (0, 33), insns 239/239
font XHIGH X22 target arithmetic operand order 1: (0, 32), insns 239/239
font XHIGH X22 target arithmetic operand order 2: (0, 33), insns 239/239
font XHIGH X22 target arithmetic operand order 3: (0, 32), insns 239/239
font XHIGH X23 helper loop-index declaration 0: (0, 32), insns 239/239
font XHIGH X23 helper loop-index declaration 1: (0, 32), insns 239/239
font XHIGH X23 helper loop-index declaration 2: (0, 32), insns 239/239
font XHIGH X23 helper loop-index declaration 3: (14, 143), insns 240/239
font XHIGH X23 helper loop-index declaration 4: (20, 147), insns 241/239
font XHIGH X23 helper loop-index declaration 5: (0, 32), insns 239/239
http XHIGH X24 readonly input byte view char delimiter: (7, 65), insns 124/124
http XHIGH X24 readonly input byte view char token: (11, 113), insns 127/124
http XHIGH X24 readonly input byte view char both: (13, 120), insns 127/124
http XHIGH X24 readonly input byte view signed char delimiter: (4, 5), insns 124/124
http XHIGH X24 readonly input byte view signed char token: (11, 113), insns 127/124
http XHIGH X24 readonly input byte view signed char both: (11, 113), insns 127/124
http XHIGH X24 readonly input byte view const char delimiter: (7, 65), insns 124/124
http XHIGH X24 readonly input byte view const char token: (11, 113), insns 127/124
http XHIGH X24 readonly input byte view const char both: (13, 120), insns 127/124
http XHIGH X24 readonly input byte view s16 delimiter: (7, 65), insns 124/124
http XHIGH X24 readonly input byte view s32 delimiter: (7, 65), insns 124/124
font XHIGH X25 sheet flags pointer address operand order: (0, 33), insns 239/239
font XHIGH X26 typed readonly helper updateSheetFlags const HeaderedGlyphGroups*: (0, 33), insns 239/239
font XHIGH X26 typed readonly helper updateSheetFlags HeaderedGlyphGroups*: (0, 33), insns 239/239
font XHIGH X26 typed readonly helper setSheetOffsetBooleans const HeaderedGlyphGroups*: (0, 33), insns 239/239
font XHIGH X26 typed readonly helper setSheetOffsetBooleans HeaderedGlyphGroups*: (0, 33), insns 239/239
font XHIGH X26 typed readonly helper convertSheetOffsetBooleansToOffsets const HeaderedGlyphGroups*: (0, 33), insns 239/239
font XHIGH X26 typed readonly helper convertSheetOffsetBooleansToOffsets HeaderedGlyphGroups*: (0, 33), insns 239/239
font XHIGH X27 wide metrics expanded group loop block direct stride False: (0, 71), insns 239/239
font XHIGH X27 wide metrics expanded group loop block direct stride True: (0, 49), insns 239/239
font XHIGH X27 wide metrics expanded group loop function direct stride False: (0, 71), insns 239/239
font XHIGH X27 wide metrics expanded group loop function direct stride True: (0, 49), insns 239/239
font XHIGH X27 wide metrics expanded group loop leading-counter direct stride False: (0, 36), insns 239/239
font XHIGH X27 wide metrics expanded group loop leading-counter direct stride True: (0, 67), insns 239/239
font XHIGH X27 wide metrics expanded group loop leading-all direct stride False: (0, 36), insns 239/239
font XHIGH X27 wide metrics expanded group loop leading-all direct stride True: (0, 67), insns 239/239
http XHIGH X28 input signature const signed char* token s32 limit: (4, 5), insns 124/124
http XHIGH X28 input signature const signed char* token const s32 limit: (4, 5), insns 124/124
http XHIGH X28 input signature const signed char* token u32 limit: (6, 7), insns 124/124
http XHIGH X28 input signature const s8* token s32 limit: (4, 5), insns 124/124
http XHIGH X28 input signature const s8* token const s32 limit: (4, 5), insns 124/124
http XHIGH X28 input signature const s8* token u32 limit: (6, 7), insns 124/124
http XHIGH X28 input signature const char token[] s32 limit: (4, 5), insns 124/124
http XHIGH X28 input signature const char token[] const s32 limit: (4, 5), insns 124/124
http XHIGH X28 input signature const char token[] u32 limit: (6, 7), insns 124/124
http XHIGH X28 input signature const char* const token s32 limit: compile rejected: #   Error:                    ^
http XHIGH X28 input signature const char* const token const s32 limit: compile rejected: #   Error:                    ^
http XHIGH X28 input signature const char* const token u32 limit: compile rejected: #   Error:                    ^
http XHIGH X28 input signature const unsigned char* token s32 limit: (19, 47), insns 123/124
http XHIGH X28 input signature const unsigned char* token const s32 limit: (19, 47), insns 123/124
http XHIGH X28 input signature const unsigned char* token u32 limit: (21, 49), insns 123/124
http XHIGH X29 inline helper source boundary order (0, 1, 2): (4, 5), insns 124/124
http XHIGH X29 inline helper source boundary order (0, 2, 1): (4, 5), insns 124/124
http XHIGH X29 inline helper source boundary order (1, 0, 2): (4, 5), insns 124/124
http XHIGH X29 inline helper source boundary order (1, 2, 0): (4, 5), insns 124/124
http XHIGH X29 inline helper source boundary order (2, 0, 1): (4, 5), insns 124/124
http XHIGH X29 inline helper source boundary order (2, 1, 0): (4, 5), insns 124/124
http XHIGH X29 lowercase helper boundary after-findnext: (4, 5), insns 124/124
http XHIGH X29 lowercase helper boundary after-skipspace: (4, 5), insns 124/124
font XHIGH X31 expanded group-selection loop with leading signed group counter, cached u32 counts; declaration search:
declaration block:
                  int groupIndex;
                  u32 stepSheetFlags;
                  const u32* flagsSheets;
                  u32 sheetOffsetsSize;
                  u32 flagsSheetsOff;
                  u32 glgrInnerLen;
                  const ArchiveFontBinaryLayout* font;
                  u16 sheetGlyphCount;
                  u32 countSheet;
                  HeaderedGlyphGroups* pGlgr;
                  u8* glgrEnd;
                  u32 expectedMaxSize;
                  u32 dataBlockCount;
                  u16* sheetOffsetsScratch;
                  u32 sheetOffsetsScratchSize;
                  const HeaderedGlyphGroups* groups;
start (0, 36)
improved (0, 27)
best (0, 27) after 345 builds; kept in source:
                const HeaderedGlyphGroups* groups;
                u32 stepSheetFlags;
                const u32* flagsSheets;
                u32 sheetOffsetsSize;
                u32 flagsSheetsOff;
                u32 glgrInnerLen;
                const ArchiveFontBinaryLayout* font;
                u16 sheetGlyphCount;
                u32 countSheet;
                HeaderedGlyphGroups* pGlgr;
                u8* glgrEnd;
                u32 expectedMaxSize;
                u32 dataBlockCount;
                u16* sheetOffsetsScratch;
                u32 sheetOffsetsScratchSize;
                int groupIndex;

font XHIGH X30 sheet flag pointer walk False base outside False declaration 0: (0, 26), insns 239/239
font XHIGH X30 sheet flag pointer walk False base outside False declaration 1: (0, 26), insns 239/239
font XHIGH X30 sheet flag pointer walk False base outside False declaration 2: (0, 26), insns 239/239
font XHIGH X30 sheet flag pointer walk False base outside False declaration 3: (0, 26), insns 239/239
font XHIGH X30 sheet flag pointer walk False base outside True declaration 0: (0, 26), insns 239/239
font XHIGH X30 sheet flag pointer walk False base outside True declaration 1: (0, 25), insns 239/239
font XHIGH X30 sheet flag pointer walk False base outside True declaration 2: (0, 26), insns 239/239
font XHIGH X30 sheet flag pointer walk False base outside True declaration 3: (0, 25), insns 239/239
font XHIGH X30 sheet flag pointer walk True base outside False declaration 0: (2, 24), insns 239/239
font XHIGH X30 sheet flag pointer walk True base outside False declaration 1: (2, 26), insns 239/239
font XHIGH X30 sheet flag pointer walk True base outside False declaration 2: (2, 24), insns 239/239
font XHIGH X30 sheet flag pointer walk True base outside False declaration 3: (2, 26), insns 239/239
font XHIGH X30 sheet flag pointer walk True base outside True declaration 0: (2, 24), insns 239/239
font XHIGH X30 sheet flag pointer walk True base outside True declaration 1: (2, 26), insns 239/239
font XHIGH X30 sheet flag pointer walk True base outside True declaration 2: (2, 24), insns 239/239
font XHIGH X30 sheet flag pointer walk True base outside True declaration 3: (2, 23), insns 239/239
font XHIGH X31 ctxdiff diagnosis: prefix exact; metadata count24/block23/glyph31/groups29/stride28/flags27/scratch22/groupIndex21 now exact. Remaining long-lived swap size26/name-walker30 vs size30/name-walker26 plus clear/update loop temps and copy arithmetic temps; 27 raw diffs, 239/239.
font XHIGH X32 clear pointer declared before index: (0, 19), insns 239/239
font XHIGH X33 sheet flag pointer parameter declaration 0 advance 0: (2, 19), insns 239/239
font XHIGH X33 sheet flag pointer parameter declaration 0 advance 1: (0, 18), insns 239/239
font XHIGH X33 sheet flag pointer parameter declaration 0 advance 2: (0, 18), insns 239/239
font XHIGH X33 sheet flag pointer parameter declaration 1 advance 0: (2, 22), insns 239/239
font XHIGH X33 sheet flag pointer parameter declaration 1 advance 1: (0, 22), insns 239/239
font XHIGH X33 sheet flag pointer parameter declaration 1 advance 2: (0, 22), insns 239/239
font XHIGH X33 sheet flag pointer parameter declaration 2 advance 0: (2, 19), insns 239/239
font XHIGH X33 sheet flag pointer parameter declaration 2 advance 1: (0, 18), insns 239/239
font XHIGH X33 sheet flag pointer parameter declaration 2 advance 2: (0, 18), insns 239/239
font XHIGH X33 sheet flag pointer parameter declaration 3 advance 0: (2, 22), insns 239/239
font XHIGH X33 sheet flag pointer parameter declaration 3 advance 1: (0, 22), insns 239/239
font XHIGH X33 sheet flag pointer parameter declaration 3 advance 2: (0, 22), insns 239/239
font XHIGH X33 sheet flag pointer cursor declaration 0 advance 0: (2, 20), insns 239/239
font XHIGH X33 sheet flag pointer cursor declaration 0 advance 1: (0, 20), insns 239/239
font XHIGH X33 sheet flag pointer cursor declaration 0 advance 2: (0, 20), insns 239/239
font XHIGH X33 sheet flag pointer cursor declaration 1 advance 0: (2, 18), insns 239/239
font XHIGH X33 sheet flag pointer cursor declaration 1 advance 1: (0, 17), insns 239/239
font XHIGH X33 sheet flag pointer cursor declaration 1 advance 2: (0, 17), insns 239/239
font XHIGH X33 sheet flag pointer cursor declaration 2 advance 0: (2, 14), insns 239/239
font XHIGH X33 sheet flag pointer cursor declaration 2 advance 1: (0, 12), insns 239/239
font XHIGH X33 sheet flag pointer cursor declaration 2 advance 2: (0, 12), insns 239/239
font XHIGH X33 sheet flag pointer cursor declaration 3 advance 0: (2, 20), insns 239/239
font XHIGH X33 sheet flag pointer cursor declaration 3 advance 1: (0, 20), insns 239/239
font XHIGH X33 sheet flag pointer cursor declaration 3 advance 2: (0, 20), insns 239/239
font XHIGH X34 active name/size source lifetime array-pointer: (51, 58), insns 239/239
font XHIGH X34 active name/size source lifetime cursor-pointer: (53, 92), insns 239/239
font XHIGH X34 active name/size source lifetime helper: (0, 12), insns 239/239
font XHIGH X34 active name/size source lifetime size-initialized: (0, 55), insns 239/239
font XHIGH X34 active name/size source lifetime size-const: (0, 55), insns 239/239
font XHIGH X34 active name/size source lifetime size-signed: (0, 12), insns 239/239
font XHIGH X35 copy helper parameter order (0, 1, 2, 3): (0, 12), insns 239/239
font XHIGH X35 copy helper parameter order (0, 1, 3, 2): (0, 12), insns 239/239
font XHIGH X35 copy helper parameter order (0, 2, 1, 3): (0, 12), insns 239/239
font XHIGH X35 copy helper parameter order (0, 2, 3, 1): (0, 12), insns 239/239
font XHIGH X35 copy helper parameter order (0, 3, 1, 2): (0, 12), insns 239/239
font XHIGH X35 copy helper parameter order (0, 3, 2, 1): (0, 12), insns 239/239
font XHIGH X35 copy helper parameter order (1, 0, 2, 3): (0, 12), insns 239/239
font XHIGH X35 copy helper parameter order (1, 0, 3, 2): (0, 12), insns 239/239
font XHIGH X35 copy helper parameter order (1, 2, 0, 3): (0, 12), insns 239/239
font XHIGH X35 copy helper parameter order (1, 2, 3, 0): (0, 12), insns 239/239
font XHIGH X35 copy helper parameter order (1, 3, 0, 2): (0, 12), insns 239/239
font XHIGH X35 copy helper parameter order (1, 3, 2, 0): (0, 12), insns 239/239
font XHIGH X35 copy helper parameter order (2, 0, 1, 3): (0, 12), insns 239/239
font XHIGH X35 copy helper parameter order (2, 0, 3, 1): (0, 12), insns 239/239
font XHIGH X35 copy helper parameter order (2, 1, 0, 3): (0, 12), insns 239/239
font XHIGH X35 copy helper parameter order (2, 1, 3, 0): (0, 12), insns 239/239
font XHIGH X35 copy helper parameter order (2, 3, 0, 1): (0, 12), insns 239/239
font XHIGH X35 copy helper parameter order (2, 3, 1, 0): (0, 12), insns 239/239
font XHIGH X35 copy helper parameter order (3, 0, 1, 2): (0, 12), insns 239/239
font XHIGH X35 copy helper parameter order (3, 0, 2, 1): (0, 12), insns 239/239
font XHIGH X35 copy helper parameter order (3, 1, 0, 2): (0, 12), insns 239/239
font XHIGH X35 copy helper parameter order (3, 1, 2, 0): (0, 12), insns 239/239
font XHIGH X35 copy helper parameter order (3, 2, 0, 1): (0, 12), insns 239/239
font XHIGH X35 copy helper parameter order (3, 2, 1, 0): (0, 12), insns 239/239
font XHIGH X36 SDK sheet-copy extent arithmetic 0: (0, 7), insns 239/239
font XHIGH X36 SDK sheet-copy extent arithmetic 1: (0, 7), insns 239/239
font XHIGH X36 SDK sheet-copy extent arithmetic 2: (11, 34), insns 236/239
font XHIGH X36 SDK sheet-copy extent arithmetic 3: (11, 34), insns 236/239
font XHIGH X36 SDK sheet-copy extent arithmetic 4: (11, 34), insns 236/239
font XHIGH X36 SDK sheet-copy extent arithmetic 5: (0, 7), insns 239/239
font XHIGH X36 SDK sheet-copy extent arithmetic 6: (0, 12), insns 239/239
font XHIGH X36 SDK sheet-copy extent arithmetic 7: (11, 34), insns 236/239
font XHIGH X36 sheet offset workspace sdk: (0, 19), insns 239/239
font XHIGH X36 sheet offset workspace signed: (0, 12), insns 239/239
font XHIGH X36 sheet offset workspace unsigned: (0, 12), insns 239/239
font XHIGH X36 sheet offset workspace const-helper: (0, 22), insns 239/239
http XHIGH final source audit: restored 97.32258% baseline after X15 explicit expressions/helper scalar ABI, X19 const ASCII-range objects, X20 named constant storage/order, X24 byte/read-only views, X28 signature const/signed views, X29 inline boundaries and six declaration permutations. Best remains five preheader scheduling differences only; 124/124, frame0x30 unchanged, pool0 and no data/extent gap. No store/reload or byte-to-16-bit shift evidence permits volatile/widening.
font XHIGH X36 signed copy-byte division ((s32)(u16)countSheet*2/2)*2 now produces target temporary order: raw12 ->7, structural0,239/239; only workspace-size26/name-offset walker30 allocation remains vs target30/26.
font XHIGH X37 immutable workspace extent view const u32& macro: (0, 19), insns 239/239
font XHIGH X37 immutable workspace extent view const u32& sdk: (0, 19), insns 239/239
font XHIGH X37 immutable workspace extent view const s32& macro: (0, 19), insns 239/239
font XHIGH X37 immutable workspace extent view const s32& sdk: (0, 19), insns 239/239
font XHIGH X37 immutable workspace extent view const u32 macro: (0, 51), insns 239/239
font XHIGH X37 immutable workspace extent view const u32 sdk: (0, 13), insns 239/239
font XHIGH X37 immutable workspace extent view const s32 macro: (0, 51), insns 239/239
font XHIGH X37 immutable workspace extent view const s32 sdk: (0, 51), insns 239/239
font XHIGH X37 immutable workspace extent view u32 macro: (0, 51), insns 239/239
font XHIGH X37 immutable workspace extent view u32 sdk: (0, 13), insns 239/239
font XHIGH X37 immutable workspace extent view s32 macro: (0, 51), insns 239/239
font XHIGH X37 immutable workspace extent view s32 sdk: (0, 51), insns 239/239
font XHIGH X38 workspace extent helper u16 sheetCount u32 size: (0, 13), insns 239/239
font XHIGH X38 workspace extent helper u16 sheetCount s32 size: (0, 13), insns 239/239
font XHIGH X38 workspace extent helper u16 sheetCount const u32 size: (0, 13), insns 239/239
font XHIGH X38 workspace extent helper u16 sheetCount const s32 size: (0, 13), insns 239/239
font XHIGH X38 workspace extent helper u32 sheetCount u32 size: (0, 13), insns 239/239
font XHIGH X38 workspace extent helper u32 sheetCount s32 size: (0, 13), insns 239/239
font XHIGH X38 workspace extent helper u32 sheetCount const u32 size: (0, 13), insns 239/239
font XHIGH X38 workspace extent helper u32 sheetCount const s32 size: (0, 13), insns 239/239
font XHIGH X38 workspace extent helper s32 sheetCount u32 size: (0, 13), insns 239/239
font XHIGH X38 workspace extent helper s32 sheetCount s32 size: (0, 13), insns 239/239
font XHIGH X38 workspace extent helper s32 sheetCount const u32 size: (0, 13), insns 239/239
font XHIGH X38 workspace extent helper s32 sheetCount const s32 size: (0, 13), insns 239/239
font XHIGH X38 workspace extent helper const u32& sheetCount u32 size: (0, 13), insns 239/239
font XHIGH X38 workspace extent helper const u32& sheetCount s32 size: (0, 17), insns 239/239
font XHIGH X38 workspace extent helper const u32& sheetCount const u32 size: (0, 17), insns 239/239
font XHIGH X38 workspace extent helper const u32& sheetCount const s32 size: (0, 17), insns 239/239
font XHIGH X39 included group load scope inline order (0, 1, 2): (0, 13), insns 239/239
font XHIGH X39 included group load scope inline order (1, 0, 2): (0, 13), insns 239/239
font XHIGH X39 included group load scope inline order (1, 2, 0): (0, 13), insns 239/239
font XHIGH X39 included group load scope leading order (0, 1, 2): (0, 13), insns 239/239
font XHIGH X39 included group load scope leading order (1, 0, 2): (0, 13), insns 239/239
font XHIGH X39 included group load scope leading order (1, 2, 0): (0, 13), insns 239/239
font XHIGH X39 included group load scope loop-top order (0, 1, 2): (0, 13), insns 239/239
font XHIGH X39 included group load scope loop-top order (1, 0, 2): (0, 13), insns 239/239
font XHIGH X39 included group load scope loop-top order (1, 2, 0): (0, 13), insns 239/239
font XHIGH X39 name offset widening s16: (1, 13), insns 239/239
font XHIGH X39 name offset widening s32: (0, 13), insns 239/239
font XHIGH X39 name offset widening u32: (0, 13), insns 239/239
font XHIGH X39 name offset widening const u32: (0, 13), insns 239/239
font XHIGH X40 group loop readonly view sizeexpr-0 groups: (0, 7), insns 239/239
font XHIGH X40 group loop readonly view sizeexpr-0 font->glgr: (53, 174), insns 238/239
font XHIGH X40 group loop readonly view sizeexpr-0 inner-reference: (56, 148), insns 240/239
font XHIGH X40 group loop readonly view sizeexpr-0 header-reference: (0, 7), insns 239/239
font XHIGH X40 group loop readonly view sizeview-u32-sdk groups: (0, 13), insns 239/239
font XHIGH X40 group loop readonly view sizeview-u32-sdk font->glgr: (53, 174), insns 238/239
font XHIGH X40 group loop readonly view sizeview-u32-sdk inner-reference: (56, 148), insns 240/239
font XHIGH X40 group loop readonly view sizeview-u32-sdk header-reference: (0, 13), insns 239/239
font XHIGH X41 group offset indexing form 0: (0, 7), insns 239/239
font XHIGH X41 group offset indexing form 1: (0, 7), insns 239/239
font XHIGH X41 group offset indexing form 2: (0, 7), insns 239/239
font XHIGH X41 group offset indexing form 3: (0, 7), insns 239/239
font XHIGH X41 group offset indexing form 4: (12, 142), insns 240/239
font XHIGH X41 group offset indexing form 5: (9, 111), insns 239/239
font XHIGH X41 group offset indexing form 6: compile rejected: #   Error:                                                                 ^
font XHIGH X41 group offset indexing form 7: compile rejected: #   Error:                                                                 ^
font XHIGH X41 group offset indexing form 8: (0, 7), insns 239/239
font XHIGH X42 sheet copy iterator range helper leading: (13, 36), insns 241/239
font XHIGH X42 sheet copy iterator range helper initialized: (13, 36), insns 241/239
font XHIGH X42 sheet copy iterator range helper expression: (0, 7), insns 239/239
font XHIGH X42 sheet copy iterator range inline leading: (0, 7), insns 239/239
font XHIGH X42 sheet copy iterator range inline initialized: (0, 7), insns 239/239
font XHIGH X42 sheet copy iterator range inline expression: (0, 7), insns 239/239
font XHIGH X42 sheet copy iterator range copy-count leading: (0, 7), insns 239/239
font XHIGH X42 sheet copy iterator range copy-count initialized: (0, 7), insns 239/239
font XHIGH X42 sheet copy iterator range copy-count expression: (0, 7), insns 239/239
font XHIGH X42 retained ordinary u16 source iterator range: copy helper derives bytes from (end-start)*sizeof(u16), replacing explicit signed-alignment operations while preserving target temporary schedule (7 raw differences). No new data or helper output.
XHIGH improvement quick gate over both units:
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/NW4R/src/ut/ut_ArchiveFontBase] pool: IDENTICAL
[libs/NW4R/src/ut/ut_ArchiveFontBase] objdiff: code 4164/5120 data 96/96 functions 22/23 fuzzy 99.9688 linked code 0
[libs/NW4R/src/ut/ut_ArchiveFontBase] instruction-exact functions: 22/23
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .data size 88 match 100.0
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .sbss2 size 8 match 100.0
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .text size 5120 match 99.96875
[libs/NW4R/src/ut/ut_ArchiveFontBase]   below 100: ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader 99.832634
[libs/NW4R/src/ut/ut_ArchiveFontBase] baseline: code 4164/5120 data 96 functions 22 fuzzy 98.5227
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] pool: IDENTICAL
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] objdiff: code 1196/1692 data None/None functions 6/7 fuzzy 99.2151 linked code 0
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] instruction-exact functions: 6/7
[libs/RevoEX/src/nhttp/NHTTP_recvbuf]   section .text size 1692 match 99.21513
[libs/RevoEX/src/nhttp/NHTTP_recvbuf]   below 100: NHTTPi_compareTokenN_HdrRecvBuf 97.32258
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] baseline: code 1196/1692 data None functions 6 fuzzy 99.2151
regressions vs baseline: 0
global matched_code_percent: 90.80962 -> 90.80962
global fuzzy_match_percent: 99.58569 -> 99.58817
global complete_code_percent: 71.43246 -> 71.43246
global matched_data_percent: 99.36639 -> 99.36639
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS

font XHIGH X43 extent scalar type unsigned int: (0, 7), insns 239/239
font XHIGH X43 extent scalar type unsigned long: (0, 7), insns 239/239
font XHIGH X43 extent scalar type signed int: (0, 7), insns 239/239
font XHIGH X43 extent scalar type signed long: (0, 7), insns 239/239
font XHIGH X43 extent scalar type size_t: (0, 7), insns 239/239
font XHIGH X43 extent scalar type const u32&: (0, 19), insns 239/239
XHIGH completeness audit: exactly two functions remain open. ConstructOpAnalyzeGLGR has >3 distinct structural/source families (const views, width and local lifetime, helper boundaries, loop pointer/index forms, copy iterator ranges) followed by declaration searches. NHTTPi_compareTokenN_HdrRecvBuf has >3 distinct source families (literal bounds/storage, const range and byte views, helper boundaries, scalar ABI, loop conditions) followed by declaration search. All failures restored; no untried owned function.
XHIGH data ownership audit: ArchiveFontBase target .data88+.sbss2 8 matches96/96; NHTTP_recvbuf has no data sections. No unpaired real data name or inflated extent found, so symbols.txt unchanged. GLGR 0x81515528+0x3bc=0x815158e4 (next FINF); HTTP compare0x814964c0+0x1f0=0x814966b0(next load). No symbol overlap.
XHIGH proven-lever audit: both frame/branch/instruction counts agree. Neither target has a back-to-back stack store/reload requiring definition-level volatile, or clrlwi0x18 vs0x10 before a byte shift. Read-only header/context/byte views tested; preserved source uses const font/header views and ordinary u16 range arithmetic.
http XHIGH X44 const linked cursor const-pointer: (4, 5), insns 124/124
http XHIGH X44 const linked cursor const-buffer: (4, 5), insns 124/124
http XHIGH X44 const linked cursor explicit-signed-read: (11, 74), insns 126/124
font XHIGH X45 final range-helper declaration search:
declaration block:
                  const HeaderedGlyphGroups* groups;
                  u32 stepSheetFlags;
                  const u32* flagsSheets;
                  u32 sheetOffsetsSize;
                  u32 flagsSheetsOff;
                  u32 glgrInnerLen;
                  const ArchiveFontBinaryLayout* font;
                  u16 sheetGlyphCount;
                  u32 countSheet;
                  HeaderedGlyphGroups* pGlgr;
                  u8* glgrEnd;
                  u32 expectedMaxSize;
                  u32 dataBlockCount;
                  u16* sheetOffsetsScratch;
                  int groupIndex;
start (0, 7)
best (0, 7) after 288 builds; source restored; best order was:
                const HeaderedGlyphGroups* groups;
                u32 stepSheetFlags;
                const u32* flagsSheets;
                u32 sheetOffsetsSize;
                u32 flagsSheetsOff;
                u32 glgrInnerLen;
                const ArchiveFontBinaryLayout* font;
                u16 sheetGlyphCount;
                u32 countSheet;
                HeaderedGlyphGroups* pGlgr;
                u8* glgrEnd;
                u32 expectedMaxSize;
                u32 dataBlockCount;
                u16* sheetOffsetsScratch;
                int groupIndex;

XHIGH final full (non --quick) gate over both owned units:
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/NW4R/src/ut/ut_ArchiveFontBase] pool: IDENTICAL
[libs/NW4R/src/ut/ut_ArchiveFontBase] objdiff: code 4164/5120 data 96/96 functions 22/23 fuzzy 99.9688 linked code 0
[libs/NW4R/src/ut/ut_ArchiveFontBase] instruction-exact functions: 22/23
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .data size 88 match 100.0
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .sbss2 size 8 match 100.0
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .text size 5120 match 99.96875
[libs/NW4R/src/ut/ut_ArchiveFontBase]   below 100: ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader 99.832634
[libs/NW4R/src/ut/ut_ArchiveFontBase] baseline: code 4164/5120 data 96 functions 22 fuzzy 98.5227
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] pool: IDENTICAL
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] objdiff: code 1196/1692 data None/None functions 6/7 fuzzy 99.2151 linked code 0
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] instruction-exact functions: 6/7
[libs/RevoEX/src/nhttp/NHTTP_recvbuf]   section .text size 1692 match 99.21513
[libs/RevoEX/src/nhttp/NHTTP_recvbuf]   below 100: NHTTPi_compareTokenN_HdrRecvBuf 97.32258
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] baseline: code 1196/1692 data None functions 6 fuzzy 99.2151
regressions vs baseline: 0
global matched_code_percent: 90.80962 -> 90.80962
global fuzzy_match_percent: 99.58569 -> 99.58817
global complete_code_percent: 71.43246 -> 71.43246
global matched_data_percent: 99.36639 -> 99.36639
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS

XHIGH final open-function re-list: ConstructOpAnalyzeGLGR 99.832634%, 239/239, structural0/raw7, only r26/r30 workspace-size/name-walker swap after X37-X43 distinct residual attempts and X45 288 declaration builds. NHTTPi_compareTokenN_HdrRecvBuf 97.32258%, 124/124, raw5, invariant bounds/delimiter/limit initialization scheduling after X15/X19/X20/X24/X28/X29/X44 and declaration permutations. Both have >=3 distinct logged source-level attempts. No new instruction-exact functions: font22->22, exactcode4164->4164, data96->96; HTTP6->6, exactcode1196->1196, no data. Partial GLGR gain98.82845->99.832634 retained at c51656cc; remaining original declaration order unknown.

## MAX continuation
HEAD c0fcbb2e352516c891fde6ffbf9be414cb332388; fetched origin/main 6f49df32b3d1be83a41250c810670894ebe27efe
Font first: pool identical0; frame0x40/save19,239/239, branch forms and normalized operands all exact. Target extent0x3bc ends at next FINF, no overlap. Seven raw differences identify ours r26=sheetOffsetsSize (ROUNDUP countSheet*sizeof(u16), used129/137/142/220), targetr30; ours r30=compiler-created induction cursor for pGlgr->inner.nameOffsets[groupIndex] (mr161,lhz166,advance192), targetr26. The second value is not a declared scalar, so directly swapping two leading declarations alone cannot name it. First glgrInnerLen also usesr26, dies before either remaining value. Definition volatile has no target store/reload proof. Byte-to-16bit shift lever has no differing opcode here; u16 range view already retained.
font MAX M0 origin source authority check: (41, 87), insns 239/239
font MAX M0 restore MAX baseline: (0, 7), insns 239/239
font MAX M1 first workspace assignment position 0: (21, 33), insns 239/239
font MAX M1 first workspace assignment position 1: (21, 33), insns 239/239
font MAX M1 first workspace assignment position 2: (21, 33), insns 239/239
font MAX M1 first workspace assignment position 3: (0, 7), insns 239/239
font MAX M2 split extent leading u32 bytes: (0, 7), insns 239/239
font MAX M2 split extent leading u32 words: (46, 130), insns 238/239
font MAX M2 split extent leading s32 bytes: (0, 7), insns 239/239
font MAX M2 split extent leading s32 words: (46, 130), insns 238/239
font MAX M2 split extent leading u16 bytes: (1, 8), insns 239/239
font MAX M2 split extent leading u16 words: (46, 130), insns 238/239
font MAX M2 split extent definition u32 bytes: (0, 7), insns 239/239
font MAX M2 split extent definition u32 words: (46, 130), insns 238/239
font MAX M2 split extent definition s32 bytes: (0, 7), insns 239/239
font MAX M2 split extent definition s32 words: (46, 130), insns 238/239
font MAX M2 split extent definition u16 bytes: (1, 8), insns 239/239
font MAX M2 split extent definition u16 words: (46, 130), insns 238/239
font MAX M3 workspace extent lifetime split constant-late: (0, 17), insns 239/239
font MAX M3 workspace extent lifetime split duplicate-assignment: (0, 17), insns 239/239
font MAX M3 workspace extent lifetime split copy-helper: (0, 17), insns 239/239
font MAX M3 workspace extent lifetime split scratch-expression: (0, 17), insns 239/239
font MAX M3 workspace extent lifetime split work-expression: (0, 17), insns 239/239
font MAX M4 named const array view array-ref first assigned groups: compile rejected: #   Error:                                           ^ #   (10124) illegal constant expression
font MAX M4 named const array view array-ref first assigned size: compile rejected: #   Error:                                           ^ #   (10124) illegal constant expression
font MAX M4 named const array view array-ref first assigned clear: compile rejected: #   Error:                                           ^ #   (10124) illegal constant expression
font MAX M4 named const array view array-ref first assigned names: compile rejected: #   Error:                                               ^ #   (10124) illegal constant expression
font MAX M4 named const array view array-pointer first assigned groups: compile rejected: #   Error:                                           ^ #   (10124) illegal constant expression
font MAX M4 named const array view array-pointer first assigned size: compile rejected: #   Error:                                           ^ #   (10124) illegal constant expression
font MAX M4 named const array view array-pointer first assigned clear: compile rejected: #   Error:                                           ^ #   (10124) illegal constant expression
font MAX M4 named const array view array-pointer first assigned names: compile rejected: #   Error:                                               ^ #   (10124) illegal constant expression
font MAX M4 named const array view u16-pointer first assigned groups: (49, 76), insns 239/239
font MAX M4 named const array view u16-pointer first assigned size: (49, 76), insns 239/239
font MAX M4 named const array view u16-pointer first assigned clear: (51, 80), insns 239/239
font MAX M4 named const array view u16-pointer first assigned names: (51, 53), insns 239/239
font MAX M4 named const array view u16-cursor first assigned groups: (51, 76), insns 239/239
font MAX M4 named const array view u16-cursor first assigned size: (51, 76), insns 239/239
font MAX M4 named const array view u16-cursor first assigned clear: (53, 80), insns 239/239
font MAX M4 named const array view u16-cursor first assigned names: (53, 88), insns 239/239
font MAX M5 extent alias const u32& lifetime size: (0, 19), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r30,blocks:r23,size:r31,stride:r27,scratch:r22,flags:r26,names:r29,index:r21
font MAX M5 extent alias const u32& lifetime names: (0, 19), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r30,blocks:r23,size:r31,stride:r27,scratch:r22,flags:r26,names:r29,index:r21
font MAX M5 extent alias const u32& lifetime copy: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M5 extent alias u32& lifetime size: (0, 19), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r30,blocks:r23,size:r31,stride:r27,scratch:r22,flags:r26,names:r29,index:r21
font MAX M5 extent alias u32& lifetime names: (0, 19), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r30,blocks:r23,size:r31,stride:r27,scratch:r22,flags:r26,names:r29,index:r21
font MAX M5 extent alias u32& lifetime copy: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M5 extent alias const s32 lifetime size: (0, 51), insns 239/239; colors font:r26,count:r25,groups:r29,glyph:r31,blocks:r24,size:r21,stride:r28,scratch:r23,flags:r27,names:r30,index:r22
font MAX M5 extent alias const s32 lifetime names: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M5 extent alias const s32 lifetime copy: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M5 extent alias u32 lifetime size: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M5 extent alias u32 lifetime names: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M5 extent alias u32 lifetime copy: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M6 real workspace plan sheetOffsetsSize,sheetOffsetsScratch declared first: (0, 54), insns 239/239; colors font:r24,count:r23,groups:r27,glyph:r31,blocks:r22,size:r30,stride:r26,scratch:r29,flags:r25,names:r28,index:r21
font MAX M6 real workspace plan sheetOffsetsSize,sheetOffsetsScratch declared old-size: (0, 54), insns 239/239; colors font:r24,count:r23,groups:r27,glyph:r31,blocks:r22,size:r30,stride:r26,scratch:r29,flags:r25,names:r28,index:r21
font MAX M6 real workspace plan sheetOffsetsSize,sheetOffsetsScratch declared last: (0, 54), insns 239/239; colors font:r24,count:r23,groups:r27,glyph:r31,blocks:r22,size:r30,stride:r26,scratch:r29,flags:r25,names:r28,index:r21
font MAX M6 real workspace plan sheetOffsetsScratch,sheetOffsetsSize declared first: (0, 54), insns 239/239; colors font:r24,count:r23,groups:r27,glyph:r31,blocks:r22,size:r30,stride:r26,scratch:r29,flags:r25,names:r28,index:r21
font MAX M6 real workspace plan sheetOffsetsScratch,sheetOffsetsSize declared old-size: (0, 54), insns 239/239; colors font:r24,count:r23,groups:r27,glyph:r31,blocks:r22,size:r30,stride:r26,scratch:r29,flags:r25,names:r28,index:r21
font MAX M6 real workspace plan sheetOffsetsScratch,sheetOffsetsSize declared last: (0, 54), insns 239/239; colors font:r24,count:r23,groups:r27,glyph:r31,blocks:r22,size:r30,stride:r26,scratch:r29,flags:r25,names:r28,index:r21
font MAX M6 real workspace plan sheetOffsetsSize,groups declared first: (0, 13), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r31,blocks:r23,size:r30,stride:r27,scratch:r22,flags:r26,names:r29,index:r21
font MAX M6 real workspace plan sheetOffsetsSize,groups declared old-size: (0, 13), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r31,blocks:r23,size:r30,stride:r27,scratch:r22,flags:r26,names:r29,index:r21
font MAX M6 real workspace plan sheetOffsetsSize,groups declared last: (0, 13), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r31,blocks:r23,size:r30,stride:r27,scratch:r22,flags:r26,names:r29,index:r21
font MAX M6 real workspace plan groups,sheetOffsetsSize declared first: (0, 13), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r31,blocks:r23,size:r30,stride:r27,scratch:r22,flags:r26,names:r29,index:r21
font MAX M6 real workspace plan groups,sheetOffsetsSize declared old-size: (0, 13), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r31,blocks:r23,size:r30,stride:r27,scratch:r22,flags:r26,names:r29,index:r21
font MAX M6 real workspace plan groups,sheetOffsetsSize declared last: (0, 13), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r31,blocks:r23,size:r30,stride:r27,scratch:r22,flags:r26,names:r29,index:r21
font MAX M6 real workspace plan sheetOffsetsSize,groupIndex declared first: (0, 57), insns 239/239; colors font:r24,count:r23,groups:r27,glyph:r31,blocks:r22,size:r30,stride:r26,scratch:r21,flags:r25,names:r28,index:r29
font MAX M6 real workspace plan sheetOffsetsSize,groupIndex declared old-size: (0, 57), insns 239/239; colors font:r24,count:r23,groups:r27,glyph:r31,blocks:r22,size:r30,stride:r26,scratch:r21,flags:r25,names:r28,index:r29
font MAX M6 real workspace plan sheetOffsetsSize,groupIndex declared last: (0, 57), insns 239/239; colors font:r24,count:r23,groups:r27,glyph:r31,blocks:r22,size:r30,stride:r26,scratch:r21,flags:r25,names:r28,index:r29
font MAX M6 real workspace plan groupIndex,sheetOffsetsSize declared first: (0, 57), insns 239/239; colors font:r24,count:r23,groups:r27,glyph:r31,blocks:r22,size:r30,stride:r26,scratch:r21,flags:r25,names:r28,index:r29
font MAX M6 real workspace plan groupIndex,sheetOffsetsSize declared old-size: (0, 57), insns 239/239; colors font:r24,count:r23,groups:r27,glyph:r31,blocks:r22,size:r30,stride:r26,scratch:r21,flags:r25,names:r28,index:r29
font MAX M6 real workspace plan groupIndex,sheetOffsetsSize declared last: (0, 57), insns 239/239; colors font:r24,count:r23,groups:r27,glyph:r31,blocks:r22,size:r30,stride:r26,scratch:r21,flags:r25,names:r28,index:r29
font MAX M6 real workspace plan sheetOffsetsSize,sheetOffsetsScratch,groups,groupIndex declared first: (0, 60), insns 239/239; colors font:r23,count:r22,groups:r26,glyph:r31,blocks:r21,size:r30,stride:r25,scratch:r29,flags:r24,names:r27,index:r28
font MAX M6 real workspace plan sheetOffsetsSize,sheetOffsetsScratch,groups,groupIndex declared old-size: (0, 60), insns 239/239; colors font:r23,count:r22,groups:r26,glyph:r31,blocks:r21,size:r30,stride:r25,scratch:r29,flags:r24,names:r27,index:r28
font MAX M6 real workspace plan sheetOffsetsSize,sheetOffsetsScratch,groups,groupIndex declared last: (0, 60), insns 239/239; colors font:r23,count:r22,groups:r26,glyph:r31,blocks:r21,size:r30,stride:r25,scratch:r29,flags:r24,names:r27,index:r28
font MAX M6 real workspace plan groupIndex,groups,sheetOffsetsScratch,sheetOffsetsSize declared first: (0, 60), insns 239/239; colors font:r23,count:r22,groups:r26,glyph:r31,blocks:r21,size:r30,stride:r25,scratch:r29,flags:r24,names:r27,index:r28
font MAX M6 real workspace plan groupIndex,groups,sheetOffsetsScratch,sheetOffsetsSize declared old-size: (0, 60), insns 239/239; colors font:r23,count:r22,groups:r26,glyph:r31,blocks:r21,size:r30,stride:r25,scratch:r29,flags:r24,names:r27,index:r28
font MAX M6 real workspace plan groupIndex,groups,sheetOffsetsScratch,sheetOffsetsSize declared last: (0, 60), insns 239/239; colors font:r23,count:r22,groups:r26,glyph:r31,blocks:r21,size:r30,stride:r25,scratch:r29,flags:r24,names:r27,index:r28
font MAX M7 secondary name induction s32 index: (2, 8), insns 239/239
font MAX M7 secondary name induction s32 byte-index: (16, 121), insns 241/239
font MAX M7 secondary name induction s32 prior-index: (2, 8), insns 239/239
font MAX M7 secondary name induction s32 countdown: (15, 123), insns 242/239
font MAX M7 secondary name induction u32 index: (2, 8), insns 239/239
font MAX M7 secondary name induction u32 byte-index: (16, 121), insns 241/239
font MAX M7 secondary name induction u32 prior-index: (2, 8), insns 239/239
font MAX M7 secondary name induction u32 countdown: (15, 123), insns 242/239
font MAX M7 secondary name induction u16 index: (9, 111), insns 239/239
font MAX M7 secondary name induction u16 byte-index: (15, 122), insns 242/239
font MAX M7 secondary name induction u16 prior-index: (9, 111), insns 239/239
font MAX M7 secondary name induction u16 countdown: (16, 124), insns 243/239
font MAX M8 initial name-index/view definition 0 zero: (3, 38), insns 239/239
font MAX M8 initial name-index/view definition 0 view: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M8 initial name-index/view definition 0 temporary: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M8 initial name-index/view definition 1 zero: (3, 38), insns 239/239
font MAX M8 initial name-index/view definition 1 view: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M8 initial name-index/view definition 1 temporary: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M8 initial name-index/view definition 2 zero: (3, 38), insns 239/239
font MAX M8 initial name-index/view definition 2 view: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M8 initial name-index/view definition 2 temporary: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M8 initial name-index/view definition 3 zero: (2, 17), insns 239/239
font MAX M8 initial name-index/view definition 3 view: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M8 initial name-index/view definition 3 temporary: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M9 definition lifetimes groups/stride/flags/extent 0 SDK False: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M9 definition lifetimes groups/stride/flags/extent 1 SDK False: (0, 58), insns 239/239; colors font:r26,count:r25,groups:r21,glyph:r31,blocks:r24,size:r27,stride:r29,scratch:r23,flags:r28,names:r30,index:r22
font MAX M9 definition lifetimes groups/stride/flags/extent 2 SDK False: (0, 53), insns 239/239; colors font:r26,count:r25,groups:r29,glyph:r31,blocks:r24,size:r27,stride:r21,scratch:r23,flags:r28,names:r30,index:r22
font MAX M9 definition lifetimes groups/stride/flags/extent 3 SDK False: (0, 58), insns 239/239; colors font:r27,count:r26,groups:r22,glyph:r31,blocks:r25,size:r28,stride:r21,scratch:r24,flags:r29,names:r30,index:r23
font MAX M9 definition lifetimes groups/stride/flags/extent 4 SDK False: (0, 52), insns 239/239; colors font:r26,count:r25,groups:r29,glyph:r31,blocks:r24,size:r27,stride:r28,scratch:r23,flags:r21,names:r30,index:r22
font MAX M9 definition lifetimes groups/stride/flags/extent 5 SDK False: (0, 58), insns 239/239; colors font:r27,count:r26,groups:r22,glyph:r31,blocks:r25,size:r28,stride:r29,scratch:r24,flags:r21,names:r30,index:r23
font MAX M9 definition lifetimes groups/stride/flags/extent 6 SDK False: (0, 53), insns 239/239; colors font:r27,count:r26,groups:r29,glyph:r31,blocks:r25,size:r28,stride:r22,scratch:r24,flags:r21,names:r30,index:r23
font MAX M9 definition lifetimes groups/stride/flags/extent 7 SDK False: (0, 58), insns 239/239; colors font:r28,count:r27,groups:r23,glyph:r31,blocks:r26,size:r29,stride:r22,scratch:r25,flags:r21,names:r30,index:r24
font MAX M9 definition lifetimes groups/stride/flags/extent 8 SDK False: (0, 51), insns 239/239; colors font:r26,count:r25,groups:r29,glyph:r31,blocks:r24,size:r21,stride:r28,scratch:r23,flags:r27,names:r30,index:r22
font MAX M9 definition lifetimes groups/stride/flags/extent 9 SDK False: (0, 58), insns 239/239; colors font:r27,count:r26,groups:r22,glyph:r31,blocks:r25,size:r21,stride:r29,scratch:r24,flags:r28,names:r30,index:r23
font MAX M9 definition lifetimes groups/stride/flags/extent 10 SDK False: (0, 53), insns 239/239; colors font:r27,count:r26,groups:r29,glyph:r31,blocks:r25,size:r21,stride:r22,scratch:r24,flags:r28,names:r30,index:r23
font MAX M9 definition lifetimes groups/stride/flags/extent 11 SDK False: (0, 58), insns 239/239; colors font:r28,count:r27,groups:r23,glyph:r31,blocks:r26,size:r21,stride:r22,scratch:r25,flags:r29,names:r30,index:r24
font MAX M9 definition lifetimes groups/stride/flags/extent 12 SDK False: (0, 52), insns 239/239; colors font:r27,count:r26,groups:r29,glyph:r31,blocks:r25,size:r21,stride:r28,scratch:r24,flags:r22,names:r30,index:r23
font MAX M9 definition lifetimes groups/stride/flags/extent 13 SDK False: (0, 58), insns 239/239; colors font:r28,count:r27,groups:r23,glyph:r31,blocks:r26,size:r21,stride:r29,scratch:r25,flags:r22,names:r30,index:r24
font MAX M9 definition lifetimes groups/stride/flags/extent 14 SDK False: (0, 53), insns 239/239; colors font:r28,count:r27,groups:r29,glyph:r31,blocks:r26,size:r21,stride:r23,scratch:r25,flags:r22,names:r30,index:r24
font MAX M9 definition lifetimes groups/stride/flags/extent 15 SDK False: (0, 58), insns 239/239; colors font:r29,count:r28,groups:r24,glyph:r31,blocks:r27,size:r21,stride:r23,scratch:r26,flags:r22,names:r30,index:r25
font MAX M9 definition lifetimes groups/stride/flags/extent 0 SDK True: (0, 13), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r31,blocks:r23,size:r30,stride:r27,scratch:r22,flags:r26,names:r29,index:r21
font MAX M9 definition lifetimes groups/stride/flags/extent 1 SDK True: (0, 52), insns 239/239; colors font:r26,count:r25,groups:r21,glyph:r31,blocks:r24,size:r30,stride:r28,scratch:r23,flags:r27,names:r29,index:r22
font MAX M9 definition lifetimes groups/stride/flags/extent 2 SDK True: (0, 53), insns 239/239; colors font:r26,count:r25,groups:r28,glyph:r31,blocks:r24,size:r30,stride:r21,scratch:r23,flags:r27,names:r29,index:r22
font MAX M9 definition lifetimes groups/stride/flags/extent 3 SDK True: (0, 54), insns 239/239; colors font:r27,count:r26,groups:r22,glyph:r31,blocks:r25,size:r30,stride:r21,scratch:r24,flags:r28,names:r29,index:r23
font MAX M9 definition lifetimes groups/stride/flags/extent 4 SDK True: (0, 54), insns 239/239; colors font:r26,count:r25,groups:r28,glyph:r31,blocks:r24,size:r30,stride:r27,scratch:r23,flags:r21,names:r29,index:r22
font MAX M9 definition lifetimes groups/stride/flags/extent 5 SDK True: (0, 53), insns 239/239; colors font:r27,count:r26,groups:r22,glyph:r31,blocks:r25,size:r30,stride:r28,scratch:r24,flags:r21,names:r29,index:r23
font MAX M9 definition lifetimes groups/stride/flags/extent 6 SDK True: (0, 54), insns 239/239; colors font:r27,count:r26,groups:r28,glyph:r31,blocks:r25,size:r30,stride:r22,scratch:r24,flags:r21,names:r29,index:r23
font MAX M9 definition lifetimes groups/stride/flags/extent 7 SDK True: (0, 54), insns 239/239; colors font:r28,count:r27,groups:r23,glyph:r31,blocks:r26,size:r30,stride:r22,scratch:r25,flags:r21,names:r29,index:r24
font MAX M9 definition lifetimes groups/stride/flags/extent 8 SDK True: (0, 13), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r31,blocks:r23,size:r30,stride:r27,scratch:r22,flags:r26,names:r29,index:r21
font MAX M9 definition lifetimes groups/stride/flags/extent 9 SDK True: (0, 52), insns 239/239; colors font:r26,count:r25,groups:r21,glyph:r31,blocks:r24,size:r30,stride:r28,scratch:r23,flags:r27,names:r29,index:r22
font MAX M9 definition lifetimes groups/stride/flags/extent 10 SDK True: (0, 53), insns 239/239; colors font:r26,count:r25,groups:r28,glyph:r31,blocks:r24,size:r30,stride:r21,scratch:r23,flags:r27,names:r29,index:r22
font MAX M9 definition lifetimes groups/stride/flags/extent 11 SDK True: (0, 54), insns 239/239; colors font:r27,count:r26,groups:r22,glyph:r31,blocks:r25,size:r30,stride:r21,scratch:r24,flags:r28,names:r29,index:r23
font MAX M9 definition lifetimes groups/stride/flags/extent 12 SDK True: (0, 54), insns 239/239; colors font:r26,count:r25,groups:r28,glyph:r31,blocks:r24,size:r30,stride:r27,scratch:r23,flags:r21,names:r29,index:r22
font MAX M9 definition lifetimes groups/stride/flags/extent 13 SDK True: (0, 53), insns 239/239; colors font:r27,count:r26,groups:r22,glyph:r31,blocks:r25,size:r30,stride:r28,scratch:r24,flags:r21,names:r29,index:r23
font MAX M9 definition lifetimes groups/stride/flags/extent 14 SDK True: (0, 54), insns 239/239; colors font:r27,count:r26,groups:r28,glyph:r31,blocks:r25,size:r30,stride:r22,scratch:r24,flags:r21,names:r29,index:r23
font MAX M9 definition lifetimes groups/stride/flags/extent 15 SDK True: (0, 54), insns 239/239; colors font:r28,count:r27,groups:r23,glyph:r31,blocks:r26,size:r30,stride:r22,scratch:r25,flags:r21,names:r29,index:r24
font MAX M10 read-only groups/stride/flags/extent references 1 SDK False: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M10 read-only groups/stride/flags/extent references 2 SDK False: (0, 79), insns 239/239; colors font:r26,count:r25,groups:r29,glyph:r31,blocks:r24,size:r27,stride:r20,scratch:r23,flags:r28,names:r30,index:r22
font MAX M10 read-only groups/stride/flags/extent references 3 SDK False: (0, 79), insns 239/239; colors font:r26,count:r25,groups:r29,glyph:r31,blocks:r24,size:r27,stride:r20,scratch:r23,flags:r28,names:r30,index:r22
font MAX M10 read-only groups/stride/flags/extent references 4 SDK False: (0, 78), insns 239/239; colors font:r26,count:r25,groups:r29,glyph:r31,blocks:r24,size:r27,stride:r28,scratch:r23,flags:r20,names:r30,index:r22
font MAX M10 read-only groups/stride/flags/extent references 5 SDK False: (0, 78), insns 239/239; colors font:r26,count:r25,groups:r29,glyph:r31,blocks:r24,size:r27,stride:r28,scratch:r23,flags:r20,names:r30,index:r22
font MAX M10 read-only groups/stride/flags/extent references 6 SDK False: (0, 81), insns 239/239; colors font:r27,count:r26,groups:r29,glyph:r31,blocks:r25,size:r28,stride:r21,scratch:r24,flags:r20,names:r30,index:r23
font MAX M10 read-only groups/stride/flags/extent references 7 SDK False: (0, 81), insns 239/239; colors font:r27,count:r26,groups:r29,glyph:r31,blocks:r25,size:r28,stride:r21,scratch:r24,flags:r20,names:r30,index:r23
font MAX M10 read-only groups/stride/flags/extent references 8 SDK False: (0, 19), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r30,blocks:r23,size:r31,stride:r27,scratch:r22,flags:r26,names:r29,index:r21
font MAX M10 read-only groups/stride/flags/extent references 9 SDK False: (0, 19), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r30,blocks:r23,size:r31,stride:r27,scratch:r22,flags:r26,names:r29,index:r21
font MAX M10 read-only groups/stride/flags/extent references 10 SDK False: (0, 83), insns 239/239; colors font:r26,count:r25,groups:r28,glyph:r30,blocks:r24,size:r31,stride:r20,scratch:r23,flags:r27,names:r29,index:r22
font MAX M10 read-only groups/stride/flags/extent references 11 SDK False: (0, 83), insns 239/239; colors font:r26,count:r25,groups:r28,glyph:r30,blocks:r24,size:r31,stride:r20,scratch:r23,flags:r27,names:r29,index:r22
font MAX M10 read-only groups/stride/flags/extent references 12 SDK False: (0, 84), insns 239/239; colors font:r26,count:r25,groups:r28,glyph:r30,blocks:r24,size:r31,stride:r27,scratch:r23,flags:r20,names:r29,index:r22
font MAX M10 read-only groups/stride/flags/extent references 13 SDK False: (0, 84), insns 239/239; colors font:r26,count:r25,groups:r28,glyph:r30,blocks:r24,size:r31,stride:r27,scratch:r23,flags:r20,names:r29,index:r22
font MAX M10 read-only groups/stride/flags/extent references 14 SDK False: (0, 86), insns 239/239; colors font:r27,count:r26,groups:r28,glyph:r30,blocks:r25,size:r31,stride:r21,scratch:r24,flags:r20,names:r29,index:r23
font MAX M10 read-only groups/stride/flags/extent references 15 SDK False: (0, 86), insns 239/239; colors font:r27,count:r26,groups:r28,glyph:r30,blocks:r25,size:r31,stride:r21,scratch:r24,flags:r20,names:r29,index:r23
font MAX M10 read-only groups/stride/flags/extent references 1 SDK True: (0, 13), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r31,blocks:r23,size:r30,stride:r27,scratch:r22,flags:r26,names:r29,index:r21
font MAX M10 read-only groups/stride/flags/extent references 2 SDK True: (0, 79), insns 239/239; colors font:r26,count:r25,groups:r28,glyph:r31,blocks:r24,size:r30,stride:r20,scratch:r23,flags:r27,names:r29,index:r22
font MAX M10 read-only groups/stride/flags/extent references 3 SDK True: (0, 79), insns 239/239; colors font:r26,count:r25,groups:r28,glyph:r31,blocks:r24,size:r30,stride:r20,scratch:r23,flags:r27,names:r29,index:r22
font MAX M10 read-only groups/stride/flags/extent references 4 SDK True: (0, 80), insns 239/239; colors font:r26,count:r25,groups:r28,glyph:r31,blocks:r24,size:r30,stride:r27,scratch:r23,flags:r20,names:r29,index:r22
font MAX M10 read-only groups/stride/flags/extent references 5 SDK True: (0, 80), insns 239/239; colors font:r26,count:r25,groups:r28,glyph:r31,blocks:r24,size:r30,stride:r27,scratch:r23,flags:r20,names:r29,index:r22
font MAX M10 read-only groups/stride/flags/extent references 6 SDK True: (0, 82), insns 239/239; colors font:r27,count:r26,groups:r28,glyph:r31,blocks:r25,size:r30,stride:r21,scratch:r24,flags:r20,names:r29,index:r23
font MAX M10 read-only groups/stride/flags/extent references 7 SDK True: (0, 82), insns 239/239; colors font:r27,count:r26,groups:r28,glyph:r31,blocks:r25,size:r30,stride:r21,scratch:r24,flags:r20,names:r29,index:r23
font MAX M10 read-only groups/stride/flags/extent references 8 SDK True: (0, 19), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r30,blocks:r23,size:r31,stride:r27,scratch:r22,flags:r26,names:r29,index:r21
font MAX M10 read-only groups/stride/flags/extent references 9 SDK True: (0, 19), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r30,blocks:r23,size:r31,stride:r27,scratch:r22,flags:r26,names:r29,index:r21
font MAX M10 read-only groups/stride/flags/extent references 10 SDK True: (0, 83), insns 239/239; colors font:r26,count:r25,groups:r28,glyph:r30,blocks:r24,size:r31,stride:r20,scratch:r23,flags:r27,names:r29,index:r22
font MAX M10 read-only groups/stride/flags/extent references 11 SDK True: (0, 83), insns 239/239; colors font:r26,count:r25,groups:r28,glyph:r30,blocks:r24,size:r31,stride:r20,scratch:r23,flags:r27,names:r29,index:r22
font MAX M10 read-only groups/stride/flags/extent references 12 SDK True: (0, 84), insns 239/239; colors font:r26,count:r25,groups:r28,glyph:r30,blocks:r24,size:r31,stride:r27,scratch:r23,flags:r20,names:r29,index:r22
font MAX M10 read-only groups/stride/flags/extent references 13 SDK True: (0, 84), insns 239/239; colors font:r26,count:r25,groups:r28,glyph:r30,blocks:r24,size:r31,stride:r27,scratch:r23,flags:r20,names:r29,index:r22
font MAX M10 read-only groups/stride/flags/extent references 14 SDK True: (0, 86), insns 239/239; colors font:r27,count:r26,groups:r28,glyph:r30,blocks:r25,size:r31,stride:r21,scratch:r24,flags:r20,names:r29,index:r23
font MAX M10 read-only groups/stride/flags/extent references 15 SDK True: (0, 86), insns 239/239; colors font:r27,count:r26,groups:r28,glyph:r30,blocks:r25,size:r31,stride:r21,scratch:r24,flags:r20,names:r29,index:r23
font MAX M10 read-only glyph group object reference, extent reference False: (0, 58), insns 239/239; colors font:r26,count:r25,groups:r21,glyph:r31,blocks:r24,size:r27,stride:r29,scratch:r23,flags:r28,names:r30,index:r22
font MAX M10 read-only glyph group object reference, extent reference True: (0, 57), insns 239/239; colors font:r26,count:r25,groups:r21,glyph:r30,blocks:r24,size:r31,stride:r28,scratch:r23,flags:r27,names:r29,index:r22
font MAX M11 definition/use 16-bit read view size: (26, 126), insns 238/239
font MAX M11 definition/use 16-bit read view stride: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M11 definition/use 16-bit read view flags: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M11 definition/use 16-bit read view name: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M11 definition/use 16-bit read view all: (26, 126), insns 238/239
font MAX M12 immutable input context workspace: compile rejected: #   Error:                         ^^^^^
font MAX M12 immutable input context names: (4, 200), insns 238/239
font MAX M12 immutable input context header: (4, 200), insns 238/239
font MAX M12 immutable input context all: compile rejected: #   Error:                                                  ^^^^^
font MAX M12 readonly helper input copyFlagOffsets const u32&: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M12 readonly helper input copyFlagOffsets const s32&: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M12 readonly helper input copyFlagOffsets const u32: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M12 readonly helper input copyFlagOffsets const s32: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M12 readonly helper input updateSheetFlags const u32&: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M12 readonly helper input updateSheetFlags const s32&: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M12 readonly helper input updateSheetFlags const u32: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M12 readonly helper input updateSheetFlags const s32: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
MAX M1-M12 structural/source audit: size first-assignment movement before stride/flag calculations changes normalized scheduling21, latest position remains7; split byte extent and copy/work/scratch recomputation min7; secondary name-index forms, array/cursor const views, POD workspace fields, initialized local lifetimes, read-only context/helper references and u16 count/name views tested. Read-only extent materialization shifts size to31 or30 but also pushes generated cursor to29/28 and changes other colors, not a direct fix. M2 u16 byte extent rejected for possible truncation above32767 sheets regardless of score; no such edit retained. Need inspect declaration allocation of generated cursor separately from explicit extent.
http MAX M13 incoming delimiter width int signed byte conversion termination-use: (4, 5), insns 124/124
http MAX M13 incoming delimiter width int signed byte conversion assign-after-read: (4, 5), insns 124/124
http MAX M13 incoming delimiter width int signed byte conversion helper-lowercase: (6, 72), insns 125/124
http MAX M13 incoming delimiter width int signed byte conversion local-view: (7, 65), insns 124/124
http MAX M13 incoming delimiter width s16 signed byte conversion termination-use: (4, 5), insns 124/124
http MAX M13 incoming delimiter width s16 signed byte conversion assign-after-read: (4, 5), insns 124/124
http MAX M13 incoming delimiter width s16 signed byte conversion helper-lowercase: (4, 5), insns 124/124
http MAX M13 incoming delimiter width s16 signed byte conversion local-view: (7, 65), insns 124/124
http MAX M13 incoming delimiter width u16 signed byte conversion termination-use: (4, 5), insns 124/124
http MAX M13 incoming delimiter width u16 signed byte conversion assign-after-read: (7, 72), insns 125/124
http MAX M13 incoming delimiter width u16 signed byte conversion helper-lowercase: (6, 72), insns 125/124
http MAX M13 incoming delimiter width u16 signed byte conversion local-view: (7, 65), insns 124/124
http MAX M13 incoming delimiter width u32 signed byte conversion termination-use: (4, 5), insns 124/124
http MAX M13 incoming delimiter width u32 signed byte conversion assign-after-read: (5, 6), insns 124/124
http MAX M13 incoming delimiter width u32 signed byte conversion helper-lowercase: (6, 72), insns 125/124
http MAX M13 incoming delimiter width u32 signed byte conversion local-view: (7, 65), insns 124/124
MAX NHTTP authority before start: fetch origin complete; origin/main NHTTP_recvbuf.c identical to current, still97.32258%,124/124. Pool identical0. Frame0x30/save25, all body/branch/count/register operands exceptpreheader54-58 exact. Target initializes lower65,upper90,delimiter sign-extension,lastposition,zero; ours delimiter,lastposition,lower65,zero,upper90. No stackstore/reload or byte-shiftmask discrepancy. Testing actual input widths/const views before declaration tie-breaks.
http MAX M14 readonly lowercase input header value token value: (4, 5), insns 124/124
http MAX M14 readonly lowercase input header value token const-pointer: (4, 5), insns 124/124
http MAX M14 readonly lowercase input header value token signed-const-pointer: (14, 77), insns 125/124
http MAX M14 readonly lowercase input header const-pointer token value: (4, 5), insns 124/124
http MAX M14 readonly lowercase input header const-pointer token const-pointer: (4, 5), insns 124/124
http MAX M14 readonly lowercase input header const-pointer token signed-const-pointer: (14, 77), insns 125/124
http MAX M14 readonly lowercase input header pointer token value: (4, 5), insns 124/124
http MAX M14 readonly lowercase input header pointer token const-pointer: (4, 5), insns 124/124
http MAX M14 readonly lowercase input header pointer token signed-const-pointer: (14, 77), insns 125/124
MAX M13 declaration search after structural variants:
declaration block:
                  const HeaderedGlyphGroups* groups;
                  u32 stepSheetFlags;
                  const u32* flagsSheets;
                  u32 sheetOffsetsSize;
                  u32 flagsSheetsOff;
                  u32 glgrInnerLen;
                  const ArchiveFontBinaryLayout* font;
                  u16 sheetGlyphCount;
                  u32 countSheet;
                  HeaderedGlyphGroups* pGlgr;
                  u8* glgrEnd;
                  u32 expectedMaxSize;
                  u32 dataBlockCount;
                  u16* sheetOffsetsScratch;
                  int groupIndex;
start (0, 7)
best (0, 7) after 288 builds; source restored; best order was:
                const HeaderedGlyphGroups* groups;
                u32 stepSheetFlags;
                const u32* flagsSheets;
                u32 sheetOffsetsSize;
                u32 flagsSheetsOff;
                u32 glgrInnerLen;
                const ArchiveFontBinaryLayout* font;
                u16 sheetGlyphCount;
                u32 countSheet;
                HeaderedGlyphGroups* pGlgr;
                u8* glgrEnd;
                u32 expectedMaxSize;
                u32 dataBlockCount;
                u16* sheetOffsetsScratch;
                int groupIndex;

font MAX M15 group-selection helper named index int& macro const HeaderedGlyphGroups*: (0, 23), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M15 group-selection helper named index int& macro HeaderedGlyphGroups*: (0, 23), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M15 group-selection helper named index int& sdk const HeaderedGlyphGroups*: (0, 29), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r31,blocks:r23,size:r30,stride:r27,scratch:r22,flags:r26,names:r29,index:r21
font MAX M15 group-selection helper named index int& sdk HeaderedGlyphGroups*: (0, 29), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r31,blocks:r23,size:r30,stride:r27,scratch:r22,flags:r26,names:r29,index:r21
font MAX M15 group-selection helper named index int* macro const HeaderedGlyphGroups*: (0, 23), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M15 group-selection helper named index int* macro HeaderedGlyphGroups*: (0, 23), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX M15 group-selection helper named index int* sdk const HeaderedGlyphGroups*: (0, 29), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r31,blocks:r23,size:r30,stride:r27,scratch:r22,flags:r26,names:r29,index:r21
font MAX M15 group-selection helper named index int* sdk HeaderedGlyphGroups*: (0, 29), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r31,blocks:r23,size:r30,stride:r27,scratch:r22,flags:r26,names:r29,index:r21
font MAX M15 group-selection helper named index int macro const HeaderedGlyphGroups*: (0, 75), insns 239/239; colors font:r24,count:r23,groups:r28,glyph:r31,blocks:r22,size:r25,stride:r27,scratch:r21,flags:r26,names:r29,index:r30
font MAX M15 group-selection helper named index int macro HeaderedGlyphGroups*: (0, 75), insns 239/239; colors font:r24,count:r23,groups:r28,glyph:r31,blocks:r22,size:r25,stride:r27,scratch:r21,flags:r26,names:r29,index:r30
font MAX M15 group-selection helper named index int sdk const HeaderedGlyphGroups*: (0, 75), insns 239/239; colors font:r24,count:r23,groups:r27,glyph:r31,blocks:r22,size:r29,stride:r26,scratch:r21,flags:r25,names:r28,index:r30
font MAX M15 group-selection helper named index int sdk HeaderedGlyphGroups*: (0, 75), insns 239/239; colors font:r24,count:r23,groups:r27,glyph:r31,blocks:r22,size:r29,stride:r26,scratch:r21,flags:r25,names:r28,index:r30
http MAX M16 lowercase representation BOOL bitwise: (4, 5), insns 124/124
http MAX M16 lowercase representation BOOL boolean-temporaries: (12, 40), insns 124/124
http MAX M16 lowercase representation BOOL inverted-reject: (53, 82), insns 127/124
http MAX M16 lowercase representation u32 bitwise: (5, 6), insns 124/124
http MAX M16 lowercase representation u32 boolean-temporaries: (13, 40), insns 124/124
http MAX M16 lowercase representation u32 inverted-reject: (54, 82), insns 127/124
http MAX M16 lowercase representation s32 bitwise: (4, 5), insns 124/124
http MAX M16 lowercase representation s32 boolean-temporaries: (12, 40), insns 124/124
http MAX M16 lowercase representation s32 inverted-reject: (53, 82), insns 127/124
http MAX M16 lowercase representation u16 bitwise: (10, 35), insns 126/124
http MAX M16 lowercase representation u16 boolean-temporaries: (35, 47), insns 127/124
http MAX M16 lowercase representation u16 inverted-reject: (56, 85), insns 130/124
http MAX M16 lowercase representation s16 bitwise: (9, 35), insns 126/124
http MAX M16 lowercase representation s16 boolean-temporaries: (22, 51), insns 128/124
http MAX M16 lowercase representation s16 inverted-reject: (66, 86), insns 131/124
http MAX M16 lowercase representation s8 bitwise: (9, 35), insns 126/124
http MAX M16 lowercase representation s8 boolean-temporaries: (22, 51), insns 128/124
http MAX M16 lowercase representation s8 inverted-reject: (59, 86), insns 131/124
font MAX M17 separate writable copy and readonly parsed header leading mutable-leading macro: (0, 49), insns 239/239; colors font:r26,count:r25,groups:r24,glyph:r31,blocks:r23,size:r27,stride:r29,scratch:r22,flags:r28,names:r30,index:r21
font MAX M17 separate writable copy and readonly parsed header leading mutable-leading sdk: (0, 42), insns 239/239; colors font:r26,count:r25,groups:r24,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r29,index:r21
font MAX M17 separate writable copy and readonly parsed header leading const-leading macro: (0, 49), insns 239/239; colors font:r26,count:r25,groups:r24,glyph:r31,blocks:r23,size:r27,stride:r29,scratch:r22,flags:r28,names:r30,index:r21
font MAX M17 separate writable copy and readonly parsed header leading const-leading sdk: (0, 42), insns 239/239; colors font:r26,count:r25,groups:r24,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r29,index:r21
font MAX M17 separate writable copy and readonly parsed header leading const-definition macro: (0, 58), insns 239/239; colors font:r26,count:r25,groups:r21,glyph:r31,blocks:r24,size:r27,stride:r29,scratch:r23,flags:r28,names:r30,index:r22
font MAX M17 separate writable copy and readonly parsed header leading const-definition sdk: (0, 52), insns 239/239; colors font:r26,count:r25,groups:r21,glyph:r31,blocks:r24,size:r30,stride:r28,scratch:r23,flags:r27,names:r29,index:r22
font MAX M17 separate writable copy and readonly parsed header leading const-inner-view macro: (55, 143), insns 240/239
font MAX M17 separate writable copy and readonly parsed header leading const-inner-view sdk: (55, 144), insns 240/239
font MAX M17 separate writable copy and readonly parsed header block mutable-leading macro: (0, 49), insns 239/239; colors font:r26,count:r25,groups:r24,glyph:r31,blocks:r23,size:r27,stride:r29,scratch:r22,flags:r28,names:r30,index:r21
font MAX M17 separate writable copy and readonly parsed header block mutable-leading sdk: (0, 42), insns 239/239; colors font:r26,count:r25,groups:r24,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r29,index:r21
font MAX M17 separate writable copy and readonly parsed header block const-leading macro: (0, 49), insns 239/239; colors font:r26,count:r25,groups:r24,glyph:r31,blocks:r23,size:r27,stride:r29,scratch:r22,flags:r28,names:r30,index:r21
font MAX M17 separate writable copy and readonly parsed header block const-leading sdk: (0, 42), insns 239/239; colors font:r26,count:r25,groups:r24,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r29,index:r21
font MAX M17 separate writable copy and readonly parsed header block const-definition macro: (0, 58), insns 239/239; colors font:r26,count:r25,groups:r21,glyph:r31,blocks:r24,size:r27,stride:r29,scratch:r23,flags:r28,names:r30,index:r22
font MAX M17 separate writable copy and readonly parsed header block const-definition sdk: (0, 52), insns 239/239; colors font:r26,count:r25,groups:r21,glyph:r31,blocks:r24,size:r30,stride:r28,scratch:r23,flags:r27,names:r29,index:r22
font MAX M17 separate writable copy and readonly parsed header block const-inner-view macro: (55, 143), insns 240/239
font MAX M17 separate writable copy and readonly parsed header block const-inner-view sdk: (55, 144), insns 240/239
http MAX M18 explicit helper inline boundary static inline 1: (4, 5), insns 124/124
http MAX M18 explicit helper inline boundary static inline 2: (4, 5), insns 124/124
http MAX M18 explicit helper inline boundary static inline 3: (4, 5), insns 124/124
http MAX M18 explicit helper inline boundary static inline 4: (4, 5), insns 124/124
http MAX M18 explicit helper inline boundary static inline 5: (4, 5), insns 124/124
http MAX M18 explicit helper inline boundary static inline 6: (4, 5), insns 124/124
http MAX M18 explicit helper inline boundary static inline 7: (4, 5), insns 124/124
http MAX M18 explicit helper inline boundary static __inline 1: (4, 5), insns 124/124
http MAX M18 explicit helper inline boundary static __inline 2: (4, 5), insns 124/124
http MAX M18 explicit helper inline boundary static __inline 3: (4, 5), insns 124/124
http MAX M18 explicit helper inline boundary static __inline 4: (4, 5), insns 124/124
http MAX M18 explicit helper inline boundary static __inline 5: (4, 5), insns 124/124
font MAX M19 extent vs groups: (0, 13), insns 239/239; colors font:r25,count:r24,groups:r26,glyph:r31,blocks:r23,size:r29,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
http MAX M18 explicit helper inline boundary static __inline 6: (4, 5), insns 124/124
font MAX M19 extent vs pGlgr: (0, 40), insns 239/239; colors font:r26,count:r25,groups:r29,glyph:r31,blocks:r23,size:r24,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
http MAX M18 explicit helper inline boundary static __inline 7: (4, 5), insns 124/124
font MAX M19 extent vs font: (0, 35), insns 239/239; colors font:r26,count:r24,groups:r29,glyph:r31,blocks:r23,size:r25,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
http MAX M18 explicit helper inline boundary inline 1: (4, 5), insns 124/124
font MAX M19 extent vs groupIndex: (0, 11), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r21,stride:r28,scratch:r22,flags:r27,names:r30,index:r26
http MAX M18 explicit helper inline boundary inline 2: (4, 5), insns 124/124
font MAX M19 extent vs stepSheetFlags: (0, 9), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r28,stride:r26,scratch:r22,flags:r27,names:r30,index:r21
http MAX M18 explicit helper inline boundary inline 3: (4, 5), insns 124/124
font MAX M19 extent vs flagsSheets: (0, 9), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r27,stride:r28,scratch:r22,flags:r26,names:r30,index:r21
http MAX M18 explicit helper inline boundary inline 4: (4, 5), insns 124/124
http MAX M18 explicit helper inline boundary inline 5: (4, 5), insns 124/124
font MAX M19 extent vs sheetOffsetsScratch: (0, 12), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r22,stride:r28,scratch:r26,flags:r27,names:r30,index:r21
http MAX M18 explicit helper inline boundary inline 6: (4, 5), insns 124/124
font MAX M19 declaration full permutation 0: (0, 64), insns 239/239; colors font:r22,count:r29,groups:r24,glyph:r31,blocks:r26,size:r27,stride:r25,scratch:r21,flags:r28,names:r30,index:r23
http MAX M18 explicit helper inline boundary inline 7: (4, 5), insns 124/124
font MAX M19 declaration full permutation 1: (0, 55), insns 239/239; colors font:r29,count:r27,groups:r24,glyph:r31,blocks:r28,size:r22,stride:r21,scratch:r25,flags:r23,names:r30,index:r26
http MAX M18 explicit helper inline boundary __inline 1: (4, 5), insns 124/124
font MAX M19 declaration full permutation 2: (0, 58), insns 239/239; colors font:r29,count:r28,groups:r22,glyph:r31,blocks:r24,size:r27,stride:r26,scratch:r21,flags:r25,names:r30,index:r23
http MAX M18 explicit helper inline boundary __inline 2: (4, 5), insns 124/124
font MAX M19 declaration full permutation 3: (0, 58), insns 239/239; colors font:r29,count:r21,groups:r22,glyph:r31,blocks:r27,size:r26,stride:r25,scratch:r24,flags:r28,names:r30,index:r23
http MAX M18 explicit helper inline boundary __inline 3: (4, 5), insns 124/124
font MAX M19 declaration full permutation 4: (0, 50), insns 239/239; colors font:r27,count:r29,groups:r26,glyph:r31,blocks:r25,size:r22,stride:r21,scratch:r23,flags:r28,names:r30,index:r24
http MAX M18 explicit helper inline boundary __inline 4: (4, 5), insns 124/124
font MAX M19 declaration full permutation 5: (0, 63), insns 239/239; colors font:r22,count:r27,groups:r25,glyph:r31,blocks:r28,size:r26,stride:r29,scratch:r21,flags:r23,names:r30,index:r24
http MAX M18 explicit helper inline boundary __inline 5: (4, 5), insns 124/124
http MAX M18 explicit helper inline boundary __inline 6: (4, 5), insns 124/124
font MAX M19 declaration full permutation 6: (0, 35), insns 239/239; colors font:r25,count:r27,groups:r29,glyph:r31,blocks:r21,size:r28,stride:r23,scratch:r22,flags:r24,names:r30,index:r26
http MAX M18 explicit helper inline boundary __inline 7: (4, 5), insns 124/124
font MAX M19 declaration full permutation 7: (0, 52), insns 239/239; colors font:r28,count:r24,groups:r25,glyph:r31,blocks:r21,size:r29,stride:r26,scratch:r27,flags:r22,names:r30,index:r23
font MAX M19 declaration full permutation 8: (0, 47), insns 239/239; colors font:r28,count:r25,groups:r27,glyph:r31,blocks:r29,size:r22,stride:r26,scratch:r21,flags:r24,names:r30,index:r23
font MAX M19 declaration full permutation 9: (0, 56), insns 239/239; colors font:r28,count:r29,groups:r23,glyph:r31,blocks:r24,size:r25,stride:r22,scratch:r21,flags:r27,names:r30,index:r26
font MAX M19 declaration full permutation 10: (0, 64), insns 239/239; colors font:r22,count:r23,groups:r21,glyph:r31,blocks:r28,size:r27,stride:r24,scratch:r25,flags:r26,names:r30,index:r29
font MAX M19 declaration full permutation 11: (0, 64), insns 239/239; colors font:r23,count:r27,groups:r21,glyph:r31,blocks:r24,size:r26,stride:r29,scratch:r25,flags:r28,names:r30,index:r22
font MAX M19 declaration full permutation 12: (0, 35), insns 239/239; colors font:r25,count:r24,groups:r26,glyph:r31,blocks:r28,size:r21,stride:r23,scratch:r22,flags:r29,names:r30,index:r27
font MAX M19 declaration full permutation 13: (0, 75), insns 239/239; colors font:r27,count:r23,groups:r24,glyph:r31,blocks:r25,size:r22,stride:r21,scratch:r26,flags:r29,names:r30,index:r28
font MAX M19 declaration full permutation 14: (0, 64), insns 239/239; colors font:r23,count:r27,groups:r24,glyph:r31,blocks:r26,size:r29,stride:r22,scratch:r21,flags:r25,names:r30,index:r28
font MAX M19 declaration full permutation 15: (0, 67), insns 239/239; colors font:r21,count:r23,groups:r24,glyph:r31,blocks:r28,size:r26,stride:r27,scratch:r22,flags:r29,names:r30,index:r25
font MAX M19 declaration full permutation 16: (0, 69), insns 239/239; colors font:r27,count:r24,groups:r21,glyph:r31,blocks:r25,size:r26,stride:r29,scratch:r28,flags:r23,names:r30,index:r22
font MAX M19 declaration full permutation 17: (0, 74), insns 239/239; colors font:r23,count:r27,groups:r22,glyph:r31,blocks:r24,size:r21,stride:r28,scratch:r26,flags:r29,names:r30,index:r25
font MAX M19 declaration full permutation 18: (0, 57), insns 239/239; colors font:r23,count:r26,groups:r28,glyph:r31,blocks:r25,size:r22,stride:r24,scratch:r29,flags:r27,names:r30,index:r21
font MAX M19 declaration full permutation 19: (0, 75), insns 239/239; colors font:r23,count:r29,groups:r22,glyph:r31,blocks:r24,size:r25,stride:r21,scratch:r26,flags:r28,names:r30,index:r27
font MAX M19 declaration full permutation 20: (0, 52), insns 239/239; colors font:r22,count:r24,groups:r23,glyph:r31,blocks:r29,size:r21,stride:r27,scratch:r25,flags:r26,names:r30,index:r28
font MAX M19 declaration full permutation 21: (0, 46), insns 239/239; colors font:r25,count:r27,groups:r29,glyph:r31,blocks:r24,size:r26,stride:r22,scratch:r21,flags:r23,names:r30,index:r28
font MAX M19 declaration full permutation 22: (0, 61), insns 239/239; colors font:r22,count:r27,groups:r24,glyph:r31,blocks:r28,size:r23,stride:r25,scratch:r26,flags:r29,names:r30,index:r21
font MAX M19 declaration full permutation 23: (0, 55), insns 239/239; colors font:r27,count:r29,groups:r26,glyph:r31,blocks:r25,size:r22,stride:r24,scratch:r28,flags:r23,names:r30,index:r21
font MAX M19 declaration full permutation 24: (0, 74), insns 239/239; colors font:r22,count:r27,groups:r23,glyph:r31,blocks:r21,size:r29,stride:r28,scratch:r25,flags:r24,names:r30,index:r26
font MAX M19 declaration full permutation 25: (0, 45), insns 239/239; colors font:r28,count:r25,groups:r21,glyph:r31,blocks:r27,size:r23,stride:r24,scratch:r22,flags:r26,names:r30,index:r29
font MAX M19 declaration full permutation 26: (0, 60), insns 239/239; colors font:r27,count:r21,groups:r25,glyph:r31,blocks:r26,size:r22,stride:r29,scratch:r24,flags:r23,names:r30,index:r28
font MAX M19 declaration full permutation 27: (0, 61), insns 239/239; colors font:r28,count:r27,groups:r22,glyph:r31,blocks:r26,size:r25,stride:r24,scratch:r29,flags:r23,names:r30,index:r21
font MAX M19 declaration full permutation 28: (0, 53), insns 239/239; colors font:r27,count:r24,groups:r25,glyph:r31,blocks:r29,size:r22,stride:r23,scratch:r28,flags:r21,names:r30,index:r26
font MAX M19 declaration full permutation 29: (0, 47), insns 239/239; colors font:r25,count:r27,groups:r21,glyph:r31,blocks:r23,size:r24,stride:r22,scratch:r29,flags:r28,names:r30,index:r26
font MAX M19 declaration full permutation 30: (0, 53), insns 239/239; colors font:r22,count:r23,groups:r29,glyph:r31,blocks:r28,size:r21,stride:r27,scratch:r25,flags:r24,names:r30,index:r26
font MAX M19 declaration full permutation 31: (0, 61), insns 239/239; colors font:r23,count:r21,groups:r25,glyph:r31,blocks:r27,size:r24,stride:r22,scratch:r29,flags:r28,names:r30,index:r26
font MAX M20 name induction signed view u32 cast-index: (13, 137), insns 240/239
font MAX M20 name induction signed view u32 cast-both: (13, 137), insns 240/239
font MAX M20 name induction signed view u32 cast-count: (14, 137), insns 240/239
font MAX M20 name induction signed view unsigned int cast-index: (13, 137), insns 240/239
font MAX M20 name induction signed view unsigned int cast-both: (13, 137), insns 240/239
font MAX M20 name induction signed view unsigned int cast-count: (14, 137), insns 240/239
font MAX M20 name induction signed view u16 cast-index: (19, 147), insns 241/239
font MAX M20 name induction signed view u16 cast-both: (19, 147), insns 241/239
font MAX M20 name induction signed view u16 cast-count: (19, 147), insns 241/239
font MAX M20 name induction signed view s16 cast-index: (12, 79), insns 241/239
font MAX M20 name induction signed view s16 cast-both: (12, 79), insns 241/239
font MAX M20 name induction signed view s16 cast-count: (12, 79), insns 241/239
MAX M19 full-order evidence:39 direct swaps/random full permutations, every normalized-exact variant retained generated name cursor inr30. This cursor is an optimizer-generated induction value, unaffected by ordinary source-variable declaration order; direct extent swaps only reshuffle explicit values. SDK size/const-ref materialization reservesr30/r31 for extent but moves cursor29 and changes groups/stride/flags, not exact. M17 separate copy and const parsed header min42; no target-justified volatile. MAX baseline restored.
MAX HTTP final declaration search after M13 incoming widths, M14 pointer-to-const lowercase inputs, M16 output/range representations, M18 explicit inline boundaries:
declaration block:
      NHTTPi_HDRBUFLIST* block;
      s32 offset;
      int character;
start (4, 5)
best (4, 5) after 6 builds; source restored; best order was:
    NHTTPi_HDRBUFLIST* block;
    s32 offset;
    int character;

MAX completeness before full gate: two owned functions remain, each has at least3 distinct new source-level families logged. Font M1 first-assignment order, M2/M3 extent split/recompute, M4/M5 named const views, M6 POD fields, M7/M8 name-index lifetimes, M9 definition scopes, M10/M12 const inputs, M11 16-bit views, M15/M17 helper/header boundaries, M19 explicit/full declaration permutations, M20 signed-counter views; best remains7 and source restored. HTTP M13 incoming widths, M14 readonly scalar/byte inputs, M16 return/range representations and M18 explicit inline boundaries, then all leading declaration permutations; best remains5 and source restored. No unit has an untried remaining function.
MAX data/extent audit unchanged: Font .data88+.sbss2 8=96/96, HTTPno data. No unpaired source/target named object to correct; no addresses, extents, section totals or config changed. Neither target supports definition volatile or the byte-to-16-bit shift-mask lever; applicable const views and u16-to-u32 field views were tested without improvement.
MAX final full gate, both owned units, non --quick:
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/NW4R/src/ut/ut_ArchiveFontBase] pool: IDENTICAL
[libs/NW4R/src/ut/ut_ArchiveFontBase] objdiff: code 4164/5120 data 96/96 functions 22/23 fuzzy 99.9688 linked code 0
[libs/NW4R/src/ut/ut_ArchiveFontBase] instruction-exact functions: 22/23
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .data size 88 match 100.0
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .sbss2 size 8 match 100.0
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .text size 5120 match 99.96875
[libs/NW4R/src/ut/ut_ArchiveFontBase]   below 100: ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader 99.832634
[libs/NW4R/src/ut/ut_ArchiveFontBase] baseline: code 4164/5120 data 96 functions 22 fuzzy 98.5227
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] pool: IDENTICAL
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] objdiff: code 1196/1692 data None/None functions 6/7 fuzzy 99.2151 linked code 0
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] instruction-exact functions: 6/7
[libs/RevoEX/src/nhttp/NHTTP_recvbuf]   section .text size 1692 match 99.21513
[libs/RevoEX/src/nhttp/NHTTP_recvbuf]   below 100: NHTTPi_compareTokenN_HdrRecvBuf 97.32258
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] baseline: code 1196/1692 data None functions 6 fuzzy 99.2151
regressions vs baseline: 0
global matched_code_percent: 90.80962 -> 90.80962
global fuzzy_match_percent: 99.58569 -> 99.58817
global complete_code_percent: 71.43246 -> 71.43246
global matched_data_percent: 99.36639 -> 99.36639
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS

MAX final re-list: ConstructOpAnalyzeGLGR99.832634%,239/239, seven r26/r30 operand differences remain: explicit sheetOffsetsSize vs automatically synthesized name-offset induction cursor. NHTTPi_compareTokenN_HdrRecvBuf97.32258%,124/124, five preheader initialization scheduling differences remain. Each remaining function has >=3 distinct new source-level attempts; all source experiments reverted, baseline code byte-for-byte preserved. No new exact function and no new fuzzy gain this MAX round. Code/data/exact counts font4164/5120,96/96,22/23 ->same; HTTP1196/1692,no data,6/7 ->same. Fullbuild/DOL hash pass, regression0, forbidden0, readability0. Original source declarations/inline structure remain unknown; no unsupported definition volatile, masks, renames or symbol-extent edits.

## MAX reference-accessor continuation
Fetched origin/main 26d7e1e052a80ea55d0591a82653370965ad5bb2; remote GLGR source remains the original unmatched implementation (local 22/23, GLGR99.832634%). Pool identical (zero strings). Structural diagnosis:239/239 instructions, frame0x40/save19; seven operand differences are sheetOffsetsSize (oursr26,targetr30) versus synthesized name-offset cursor (oursr30,targetr26). No branch, opcode, temporary arithmetic, byte-widening or stack-reload difference. Authorized read-only News Channel reference uses accessor and first-use const definitions numSheet,glyphsPerSheet,numBlocks,sizeAdjustTable,remain,pAdjustTable. Test that structure using owned types; no other reference functions copied.
font MAX R1 reference accessor and first-use const definitions: (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R2 accessor member declaration order (0, 1, 3, 2): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R2 accessor member declaration order (0, 2, 1, 3): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R2 accessor member declaration order (0, 2, 3, 1): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R2 accessor member declaration order (0, 3, 1, 2): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R2 accessor member declaration order (0, 3, 2, 1): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R2 accessor member declaration order (1, 0, 2, 3): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R2 accessor member declaration order (1, 0, 3, 2): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R2 accessor member declaration order (1, 2, 0, 3): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R2 accessor member declaration order (1, 2, 3, 0): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R2 accessor member declaration order (1, 3, 0, 2): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R2 accessor member declaration order (1, 3, 2, 0): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R2 accessor member declaration order (2, 0, 1, 3): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R2 accessor member declaration order (2, 0, 3, 1): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R2 accessor member declaration order (2, 1, 0, 3): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R2 accessor member declaration order (2, 1, 3, 0): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R2 accessor member declaration order (2, 3, 0, 1): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R2 accessor member declaration order (2, 3, 1, 0): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R2 accessor member declaration order (3, 0, 1, 2): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R2 accessor member declaration order (3, 0, 2, 1): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R2 accessor member declaration order (3, 1, 0, 2): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R2 accessor member declaration order (3, 1, 2, 0): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R2 accessor member declaration order (3, 2, 0, 1): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R2 accessor member declaration order (3, 2, 1, 0): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R3 first-use metadata widths u16/int: (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R3 first-use metadata widths u16/u16: (0, 21), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r31,blocks:r24,size:r23,stride:r30,scratch:r22,flags:r28,names:r27,index:r21
font MAX R3 first-use metadata widths u16/u32: (0, 51), insns 239/239; colors font:r26,count:r27,groups:r30,glyph:r25,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r29,names:r28,index:r21
font MAX R3 first-use metadata widths u32/int: (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R3 first-use metadata widths u32/u16: (0, 21), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r31,blocks:r24,size:r23,stride:r30,scratch:r22,flags:r28,names:r27,index:r21
font MAX R3 first-use metadata widths u32/u32: (0, 51), insns 239/239; colors font:r26,count:r27,groups:r30,glyph:r25,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r29,names:r28,index:r21
font MAX R3 first-use metadata widths int/int: (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R3 first-use metadata widths int/u16: (0, 21), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r31,blocks:r24,size:r23,stride:r30,scratch:r22,flags:r28,names:r27,index:r21
font MAX R3 first-use metadata widths int/u32: (0, 51), insns 239/239; colors font:r26,count:r27,groups:r30,glyph:r25,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r29,names:r28,index:r21
font MAX R4 pre-validation declaration block, first-use accessor metadata u16/int: (0, 26), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R4 pre-validation declaration block, first-use accessor metadata u32/u16: (0, 24), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r31,blocks:r24,size:r23,stride:r30,scratch:r22,flags:r28,names:r27,index:r21
font MAX R4 pre-validation declaration block, first-use accessor metadata u16/u16: (0, 24), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r31,blocks:r24,size:r23,stride:r30,scratch:r22,flags:r28,names:r27,index:r21
font MAX R4 pre-validation declaration block, first-use accessor metadata u32/int: (0, 26), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R5 first-use const extent u32/(RoundUp)(numSheet * sizeof(u16), 4): (0, 47), insns 239/239; colors font:r24,count:r25,groups:r28,glyph:r30,blocks:r23,size:r29,stride:r31,scratch:r22,flags:r27,names:r26,index:r21
font MAX R5 first-use const extent u32/ROUNDUP(numSheet * sizeof(u16), 4): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R5 first-use const extent u32/CalcSizeSheetOffsets(numSheet): (0, 47), insns 239/239; colors font:r24,count:r25,groups:r28,glyph:r30,blocks:r23,size:r29,stride:r31,scratch:r22,flags:r27,names:r26,index:r21
font MAX R5 first-use const extent u32/(RoundUp)(numSheet * 2, 4): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R5 first-use const extent int/(RoundUp)(numSheet * sizeof(u16), 4): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R5 first-use const extent int/ROUNDUP(numSheet * sizeof(u16), 4): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R5 first-use const extent int/CalcSizeSheetOffsets(numSheet): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R5 first-use const extent int/(RoundUp)(numSheet * 2, 4): (0, 47), insns 239/239; colors font:r24,count:r25,groups:r28,glyph:r30,blocks:r23,size:r29,stride:r31,scratch:r22,flags:r27,names:r26,index:r21
font MAX R5 first-use const extent s32/(RoundUp)(numSheet * sizeof(u16), 4): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R5 first-use const extent s32/ROUNDUP(numSheet * sizeof(u16), 4): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R5 first-use const extent s32/CalcSizeSheetOffsets(numSheet): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R5 first-use const extent s32/(RoundUp)(numSheet * 2, 4): (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R6 accessor constructor body all, widths u32/int/int: (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R6 accessor constructor body all, widths int/int/int: (17, 145), insns 240/239
font MAX R6 accessor constructor body all, widths u32/u16/u32: (0, 46), insns 239/239; colors font:r24,count:r25,groups:r28,glyph:r31,blocks:r23,size:r29,stride:r30,scratch:r22,flags:r27,names:r26,index:r21
font MAX R6 accessor constructor body all, widths int/u16/u32: (17, 135), insns 240/239
font MAX R6 accessor constructor body all, widths int/u16/int: (17, 145), insns 240/239
font MAX R6 accessor constructor flags before stride, widths u32/int/int: (27, 36), insns 239/239
font MAX R6 accessor constructor flags before stride, widths int/int/int: (44, 155), insns 240/239
font MAX R6 accessor constructor flags before stride, widths u32/u16/u32: (27, 58), insns 239/239
font MAX R6 accessor constructor flags before stride, widths int/u16/u32: (44, 149), insns 240/239
font MAX R6 accessor constructor flags before stride, widths int/u16/int: (44, 155), insns 240/239
font MAX R6 accessor constructor initializer all, widths u32/int/int: (25, 134), insns 240/239
font MAX R6 accessor constructor initializer all, widths int/int/int: (37, 174), insns 241/239
font MAX R6 accessor constructor initializer all, widths u32/u16/u32: (25, 152), insns 240/239
font MAX R6 accessor constructor initializer all, widths int/u16/u32: (37, 174), insns 241/239
font MAX R6 accessor constructor initializer all, widths int/u16/int: (37, 174), insns 241/239
font MAX R6 accessor constructor inner const first, widths u32/int/int: (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R6 accessor constructor inner const first, widths int/int/int: (17, 145), insns 240/239
font MAX R6 accessor constructor inner const first, widths u32/u16/u32: (0, 46), insns 239/239; colors font:r24,count:r25,groups:r28,glyph:r31,blocks:r23,size:r29,stride:r30,scratch:r22,flags:r27,names:r26,index:r21
font MAX R6 accessor constructor inner const first, widths int/u16/u32: (17, 135), insns 240/239
font MAX R6 accessor constructor inner const first, widths int/u16/int: (17, 145), insns 240/239
font MAX R6 accessor constructor const step local, widths u32/int/int: (0, 27), insns 239/239; colors font:r25,count:r26,groups:r30,glyph:r31,blocks:r24,size:r23,stride:r29,scratch:r22,flags:r28,names:r27,index:r21
font MAX R6 accessor constructor const step local, widths int/int/int: (17, 145), insns 240/239
font MAX R6 accessor constructor const step local, widths u32/u16/u32: (0, 34), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R6 accessor constructor const step local, widths int/u16/u32: (17, 135), insns 240/239
font MAX R6 accessor constructor const step local, widths int/u16/int: (17, 145), insns 240/239
font MAX R6 accessor constructor no offset local, widths u32/int/int: (0, 23), insns 239/239; colors font:r25,count:r26,groups:r29,glyph:r30,blocks:r24,size:r23,stride:r31,scratch:r22,flags:r28,names:r27,index:r21
font MAX R6 accessor constructor no offset local, widths int/int/int: (17, 145), insns 240/239
font MAX R6 accessor constructor no offset local, widths u32/u16/u32: (0, 46), insns 239/239; colors font:r24,count:r25,groups:r28,glyph:r31,blocks:r23,size:r29,stride:r30,scratch:r22,flags:r27,names:r26,index:r21
font MAX R6 accessor constructor no offset local, widths int/u16/u32: (17, 135), insns 240/239
font MAX R6 accessor constructor no offset local, widths int/u16/int: (17, 145), insns 240/239
font MAX R7 const constructor stride temporary with typed extent: (0, 34), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R8 accessor input and const view const void parameter: (0, 34), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R8 accessor input and const view byte pointer parameter: (0, 34), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R8 accessor input and const view byte pointer top: (0, 34), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R8 accessor input and const view header reference: (0, 34), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R8 accessor input and const view header pointer: (0, 34), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R8 accessor input and const view count getter int: (0, 34), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R8 accessor input and const view count getter u32: (3, 37), insns 239/239
font MAX R8 accessor input and const view const accessor: (0, 34), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R8 accessor input and const view glyph getter u16: (0, 34), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R9 font/count storage font pointer const: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R9 font/count storage font reference: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R9 font/count storage sheet int: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R9 font/count storage sheet u32: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R9 font/count storage sheet unsigned int: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R9 font/count storage sheet signed long: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R9 font/count storage sheet const reference: (2, 24), insns 239/239
font MAX R9 font/count storage sheet getter reference: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R9 font/count storage const GG members: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R9 font/count storage sheet value by helper: (26, 115), insns 238/239
font MAX R9 font/count storage header size const view: (3, 234), insns 240/239
R7/R8 analysis: accessor plus a real const flagsStep constructor temporary and typed RoundUp extent fixes the original size/name-cursor allocation, while the first-use numSheet and font now swap r25/r24. All seven other saved variables match. Pre-validation declaration search25 builds reduced34 to23 raw differences (zero structural); changing const pointer/reference views or metadata widths did not alter that last swap. Accessor first-use path is structurally identical to target239/239.
font MAX R10 accessor getter inline boundary const u16 temporary: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R10 accessor getter inline boundary u16 temporary: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R10 accessor getter inline boundary const int temporary: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R10 accessor getter inline boundary const u32 temporary: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R10 accessor getter inline boundary const s32 temporary: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R10 accessor getter inline boundary inner reference: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R10 accessor getter inline boundary inner pointer: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R10 accessor getter inline boundary u32 return: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R10 accessor getter inline boundary u32 reference return: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order int/u32/0: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order int/u32/1: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order int/int/0: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order int/int/1: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order int/s32/0: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order int/s32/1: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order int/unsigned int/0: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order int/unsigned int/1: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order s32/u32/0: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order s32/u32/1: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order s32/int/0: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order s32/int/1: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order s32/s32/0: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order s32/s32/1: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order s32/unsigned int/0: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order s32/unsigned int/1: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order u32/u32/0: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order u32/u32/1: (0, 35), insns 239/239; colors font:r24,count:r25,groups:r28,glyph:r31,blocks:r23,size:r29,stride:r30,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order u32/int/0: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order u32/int/1: (0, 35), insns 239/239; colors font:r24,count:r25,groups:r28,glyph:r31,blocks:r23,size:r29,stride:r30,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order u32/s32/0: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order u32/s32/1: (0, 35), insns 239/239; colors font:r24,count:r25,groups:r28,glyph:r31,blocks:r23,size:r29,stride:r30,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order u32/unsigned int/0: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order u32/unsigned int/1: (0, 35), insns 239/239; colors font:r24,count:r25,groups:r28,glyph:r31,blocks:r23,size:r29,stride:r30,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order unsigned int/u32/0: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order unsigned int/u32/1: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order unsigned int/int/0: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order unsigned int/int/1: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order unsigned int/s32/0: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order unsigned int/s32/1: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order unsigned int/unsigned int/0: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R11 constructor temporary types/order unsigned int/unsigned int/1: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R12 accessor underlying view byte file field: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R12 accessor underlying view void file field: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R12 accessor underlying view header file field: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R12 accessor underlying view integer file field: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R12 accessor underlying view mutable main font: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R12 accessor underlying view mutable GG group: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R12 accessor underlying view groups constructor argument: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R13 accessor delayed resource binding declaration position 0: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R13 accessor delayed resource binding declaration position 1: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R13 accessor delayed resource binding declaration position 2: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R13 accessor delayed resource binding declaration position 3: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R13 accessor delayed resource binding declaration position 4: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R13 accessor delayed resource binding declaration position 5: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R13 accessor delayed resource binding declaration position 6: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R13 accessor delayed resource binding declaration position 7: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R13 accessor delayed resource binding declaration position 8: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R14 cached sheet count lifetime mutable count first use: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R14 cached sheet count lifetime mutable count leading: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R14 cached sheet count lifetime leading snapshot: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R14 cached sheet count lifetime leading snapshot reuse: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R14 cached sheet count lifetime u32 snapshot: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R14 cached sheet count lifetime first-use snapshot: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R14 cached sheet count lifetime all mutable first use: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R15 accessor constructor cached count u16/const first use: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R15 accessor constructor cached count u16/mutable first use: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R15 accessor constructor cached count u16/mutable leading: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R15 accessor constructor cached count u32/const first use: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R15 accessor constructor cached count u32/mutable first use: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R15 accessor constructor cached count u32/mutable leading: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R15 accessor constructor cached count int/const first use: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R15 accessor constructor cached count int/mutable first use: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R15 accessor constructor cached count int/mutable leading: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R15 accessor constructor cached count s32/const first use: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R15 accessor constructor cached count s32/mutable first use: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R15 accessor constructor cached count s32/mutable leading: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R16 accessor cache boundary pointer-only constructor: (65, 141), insns 239/239
font MAX R16 accessor cache boundary GetFlags methods: (65, 141), insns 239/239
font MAX R16 accessor cache boundary early prepare: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R16 accessor cache boundary prepare count argument: (0, 38), insns 239/239; colors font:r24,count:r30,groups:r28,glyph:r31,blocks:r23,size:r29,stride:r27,scratch:r22,flags:r26,names:r25,index:r21
font MAX R16 accessor cache boundary prepare getter arguments: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R16 accessor cache boundary constructor count argument: (42, 140), insns 240/239
font MAX R17 metadata signedness/types u32/u32/u16: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types u32/u32/int: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types u32/int/u16: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types u32/int/int: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types u32/s32/u16: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types u32/s32/int: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types int/u32/u16: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types int/u32/int: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types int/int/u16: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types int/int/int: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types int/s32/u16: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types int/s32/int: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types unsigned int/u32/u16: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types unsigned int/u32/int: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types unsigned int/int/u16: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types unsigned int/int/int: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types unsigned int/s32/u16: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types unsigned int/s32/int: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types s32/u32/u16: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types s32/u32/int: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types s32/int/u16: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types s32/int/int: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types s32/s32/u16: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types s32/s32/int: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types u16/u32/u16: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types u16/u32/int: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types u16/int/u16: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types u16/int/int: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types u16/s32/u16: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R17 metadata signedness/types u16/s32/int: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R18 accessor reference fields font/groups False/False: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R18 accessor reference fields font/groups False/True: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R18 accessor reference fields font/groups True/False: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R18 accessor reference fields font/groups True/True: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R19 accessor constructor named views/cache locals 1: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R19 accessor constructor named views/cache locals 2: (0, 33), insns 239/239; colors font:r24,count:r25,groups:r30,glyph:r31,blocks:r23,size:r29,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R19 accessor constructor named views/cache locals 3: (0, 33), insns 239/239; colors font:r24,count:r25,groups:r30,glyph:r31,blocks:r23,size:r29,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R19 accessor constructor named views/cache locals 4: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R19 accessor constructor named views/cache locals 5: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R19 accessor constructor named views/cache locals 6: (0, 33), insns 239/239; colors font:r24,count:r25,groups:r30,glyph:r31,blocks:r23,size:r29,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R19 accessor constructor named views/cache locals 7: (0, 33), insns 239/239; colors font:r24,count:r25,groups:r30,glyph:r31,blocks:r23,size:r29,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R19 accessor constructor named views/cache locals 8: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R19 accessor constructor named views/cache locals 9: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R19 accessor constructor named views/cache locals 10: (0, 33), insns 239/239; colors font:r24,count:r25,groups:r30,glyph:r31,blocks:r23,size:r29,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R19 accessor constructor named views/cache locals 11: (0, 33), insns 239/239; colors font:r24,count:r25,groups:r30,glyph:r31,blocks:r23,size:r29,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R19 accessor constructor named views/cache locals 12: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R19 accessor constructor named views/cache locals 13: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R19 accessor constructor named views/cache locals 14: (0, 33), insns 239/239; colors font:r24,count:r25,groups:r30,glyph:r31,blocks:r23,size:r29,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R19 accessor constructor named views/cache locals 15: (0, 33), insns 239/239; colors font:r24,count:r25,groups:r30,glyph:r31,blocks:r23,size:r29,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R20 first-use metadata const references u16/1: (2, 24), insns 239/239
font MAX R20 first-use metadata const references u16/3: (2, 74), insns 239/239
font MAX R20 first-use metadata const references u16/5: (2, 60), insns 239/239
font MAX R20 first-use metadata const references u16/9: (2, 24), insns 239/239
font MAX R20 first-use metadata const references int/1: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R20 first-use metadata const references int/3: (0, 73), insns 239/239; colors font:r25,count:r26,groups:r30,glyph:r20,blocks:r24,size:r31,stride:r29,scratch:r23,flags:r28,names:r27,index:r22
font MAX R20 first-use metadata const references int/5: (0, 59), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r20,size:r30,stride:r28,scratch:r23,flags:r27,names:r26,index:r22
font MAX R20 first-use metadata const references int/9: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R20 first-use metadata const references u32/1: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R20 first-use metadata const references u32/3: (0, 73), insns 239/239; colors font:r25,count:r26,groups:r30,glyph:r20,blocks:r24,size:r31,stride:r29,scratch:r23,flags:r28,names:r27,index:r22
font MAX R20 first-use metadata const references u32/5: (0, 59), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r20,size:r30,stride:r28,scratch:r23,flags:r27,names:r26,index:r22
font MAX R20 first-use metadata const references u32/9: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R20 first-use metadata const references s32/1: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R20 first-use metadata const references s32/3: (0, 73), insns 239/239; colors font:r25,count:r26,groups:r30,glyph:r20,blocks:r24,size:r31,stride:r29,scratch:r23,flags:r28,names:r27,index:r22
font MAX R20 first-use metadata const references s32/5: (0, 59), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r20,size:r30,stride:r28,scratch:r23,flags:r27,names:r26,index:r22
font MAX R20 first-use metadata const references s32/9: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R21 post-validation inline boundary ('ctx', 'font', 'glgrEnd') font reference False: (0, 94), insns 239/239; colors font:r21,count:r22,groups:r26,glyph:r31,blocks:r28,size:r27,stride:r25,scratch:r29,flags:r24,names:r23,index:r30
font MAX R21 post-validation inline boundary ('ctx', 'font', 'glgrEnd') font reference True: (0, 94), insns 239/239; colors font:r21,count:r22,groups:r26,glyph:r31,blocks:r28,size:r27,stride:r25,scratch:r29,flags:r24,names:r23,index:r30
font MAX R21 post-validation inline boundary ('ctx', 'glgrEnd', 'font') font reference False: (0, 94), insns 239/239; colors font:r21,count:r22,groups:r26,glyph:r31,blocks:r28,size:r27,stride:r25,scratch:r29,flags:r24,names:r23,index:r30
font MAX R21 post-validation inline boundary ('ctx', 'glgrEnd', 'font') font reference True: (0, 94), insns 239/239; colors font:r21,count:r22,groups:r26,glyph:r31,blocks:r28,size:r27,stride:r25,scratch:r29,flags:r24,names:r23,index:r30
font MAX R21 post-validation inline boundary ('font', 'ctx', 'glgrEnd') font reference False: (0, 94), insns 239/239; colors font:r21,count:r22,groups:r26,glyph:r31,blocks:r28,size:r27,stride:r25,scratch:r29,flags:r24,names:r23,index:r30
font MAX R21 post-validation inline boundary ('font', 'ctx', 'glgrEnd') font reference True: (0, 94), insns 239/239; colors font:r21,count:r22,groups:r26,glyph:r31,blocks:r28,size:r27,stride:r25,scratch:r29,flags:r24,names:r23,index:r30
font MAX R21 post-validation inline boundary ('font', 'glgrEnd', 'ctx') font reference False: (0, 94), insns 239/239; colors font:r21,count:r22,groups:r26,glyph:r31,blocks:r28,size:r27,stride:r25,scratch:r29,flags:r24,names:r23,index:r30
font MAX R21 post-validation inline boundary ('font', 'glgrEnd', 'ctx') font reference True: (0, 94), insns 239/239; colors font:r21,count:r22,groups:r26,glyph:r31,blocks:r28,size:r27,stride:r25,scratch:r29,flags:r24,names:r23,index:r30
font MAX R21 post-validation inline boundary ('glgrEnd', 'ctx', 'font') font reference False: (0, 94), insns 239/239; colors font:r21,count:r22,groups:r26,glyph:r31,blocks:r28,size:r27,stride:r25,scratch:r29,flags:r24,names:r23,index:r30
font MAX R21 post-validation inline boundary ('glgrEnd', 'ctx', 'font') font reference True: (0, 94), insns 239/239; colors font:r21,count:r22,groups:r26,glyph:r31,blocks:r28,size:r27,stride:r25,scratch:r29,flags:r24,names:r23,index:r30
font MAX R21 post-validation inline boundary ('glgrEnd', 'font', 'ctx') font reference False: (0, 94), insns 239/239; colors font:r21,count:r22,groups:r26,glyph:r31,blocks:r28,size:r27,stride:r25,scratch:r29,flags:r24,names:r23,index:r30
font MAX R21 post-validation inline boundary ('glgrEnd', 'font', 'ctx') font reference True: (0, 94), insns 239/239; colors font:r21,count:r22,groups:r26,glyph:r31,blocks:r28,size:r27,stride:r25,scratch:r29,flags:r24,names:r23,index:r30
font MAX R22 accessor main cache calculations 0/0/0: (41, 57), insns 239/239
font MAX R22 accessor main cache calculations 0/0/1: (41, 49), insns 239/239
font MAX R22 accessor main cache calculations 0/1/0: (41, 57), insns 239/239
font MAX R22 accessor main cache calculations 0/1/1: (41, 49), insns 239/239
font MAX R22 accessor main cache calculations 1/0/0: (41, 57), insns 239/239
font MAX R22 accessor main cache calculations 1/0/1: (41, 58), insns 239/239
font MAX R22 accessor main cache calculations 1/1/0: (41, 57), insns 239/239
font MAX R22 accessor main cache calculations 1/1/1: (41, 58), insns 239/239
font MAX R23 flags caches before first-use metadata 000: (41, 53), insns 239/239
font MAX R23 flags caches before first-use metadata 010: (41, 53), insns 239/239
font MAX R23 flags caches before first-use metadata 100: (41, 62), insns 239/239
font MAX R23 flags caches before first-use metadata 110: (41, 62), insns 239/239
font MAX R23 flags caches before first-use metadata 101: (41, 47), insns 239/239
font MAX R23 flags caches before first-use metadata 111: (41, 47), insns 239/239
font MAX R24 accessor constructor getter calls 1/u16: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R24 accessor constructor getter calls 1/int: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R24 accessor constructor getter calls 1/u32: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R24 accessor constructor getter calls 2/u16: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R24 accessor constructor getter calls 2/int: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R24 accessor constructor getter calls 2/u32: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R24 accessor constructor getter calls 3/u16: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R24 accessor constructor getter calls 3/int: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R24 accessor constructor getter calls 3/u32: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R24 accessor constructor getter calls 4/u16: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R24 accessor constructor getter calls 4/int: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R24 accessor constructor getter calls 4/u32: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R24 accessor constructor getter calls 5/u16: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R24 accessor constructor getter calls 5/int: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R24 accessor constructor getter calls 5/u32: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R24 accessor constructor getter calls 6/u16: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R24 accessor constructor getter calls 6/int: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R24 accessor constructor getter calls 6/u32: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R24 accessor constructor getter calls 7/u16: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R24 accessor constructor getter calls 7/int: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R24 accessor constructor getter calls 7/u32: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R25 meaningful identifier variant numSheet/countSheet: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R25 meaningful identifier variant glyphsPerSheet/sheetGlyphCount: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R25 meaningful identifier variant numBlocks/dataBlockCount: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R25 meaningful identifier variant sizeAdjustTable/sheetOffsetsSize: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R25 meaningful identifier variant pAdjustTable/sheetOffsetsScratch: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R25 meaningful identifier variant gg/glyphGroups: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R25 meaningful identifier variant font/fontData: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R25 meaningful identifier variant mFont/mFileTop: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R25 meaningful identifier variant mGroups/mGlyphGroups: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R25 meaningful identifier variant mFlagsStep/mBytesPerFlagSet: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R25 meaningful identifier variant mSheetFlags/mSheetFlagData: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R25 meaningful identifier variant all/all: (0, 23), insns 239/239; colors font:r24,count:r25,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
font MAX R26 preserved explicit metadata signed stride temporary/macro: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX R26 preserved explicit metadata signed stride temporary/round: (0, 13), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r31,blocks:r23,size:r30,stride:r27,scratch:r22,flags:r26,names:r29,index:r21
font MAX R26 preserved explicit metadata signed stride temporary/sdk: (0, 13), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r31,blocks:r23,size:r30,stride:r27,scratch:r22,flags:r26,names:r29,index:r21
font MAX R26 preserved explicit metadata unsigned stride temporary/macro: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r30,index:r21
font MAX R26 preserved explicit metadata unsigned stride temporary/round: (0, 13), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r31,blocks:r23,size:r30,stride:r27,scratch:r22,flags:r26,names:r29,index:r21
font MAX R26 preserved explicit metadata unsigned stride temporary/sdk: (0, 13), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r31,blocks:r23,size:r30,stride:r27,scratch:r22,flags:r26,names:r29,index:r21
font MAX R26 preserved explicit metadata first-use stride const/macro: (0, 53), insns 239/239; colors font:r26,count:r25,groups:r29,glyph:r31,blocks:r24,size:r27,stride:r21,scratch:r23,flags:r28,names:r30,index:r22
font MAX R26 preserved explicit metadata first-use stride const/round: (0, 53), insns 239/239; colors font:r26,count:r25,groups:r28,glyph:r31,blocks:r24,size:r30,stride:r21,scratch:r23,flags:r27,names:r29,index:r22
font MAX R26 preserved explicit metadata first-use stride const/sdk: (0, 53), insns 239/239; colors font:r26,count:r25,groups:r28,glyph:r31,blocks:r24,size:r30,stride:r21,scratch:r23,flags:r27,names:r29,index:r22
font MAX R26 preserved explicit metadata group pointer const first-use/macro: (0, 58), insns 239/239; colors font:r26,count:r25,groups:r21,glyph:r31,blocks:r24,size:r27,stride:r29,scratch:r23,flags:r28,names:r30,index:r22
font MAX R26 preserved explicit metadata group pointer const first-use/round: (0, 52), insns 239/239; colors font:r26,count:r25,groups:r21,glyph:r31,blocks:r24,size:r30,stride:r28,scratch:r23,flags:r27,names:r29,index:r22
font MAX R26 preserved explicit metadata group pointer const first-use/sdk: (0, 52), insns 239/239; colors font:r26,count:r25,groups:r21,glyph:r31,blocks:r24,size:r30,stride:r28,scratch:r23,flags:r27,names:r29,index:r22
font MAX R27 thin accessor with existing scalar caches macro/0: (0, 13), insns 239/239; colors font:r25,count:r24,groups:r30,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r29,index:r21
font MAX R27 thin accessor with existing scalar caches macro/1: (0, 13), insns 239/239; colors font:r25,count:r24,groups:r30,glyph:r31,blocks:r23,size:r26,stride:r28,scratch:r22,flags:r27,names:r29,index:r21
font MAX R27 thin accessor with existing scalar caches round/0: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r27,scratch:r22,flags:r26,names:r28,index:r21
font MAX R27 thin accessor with existing scalar caches round/1: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r27,scratch:r22,flags:r26,names:r28,index:r21
font MAX R27 thin accessor with existing scalar caches sdk/0: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r27,scratch:r22,flags:r26,names:r28,index:r21
font MAX R27 thin accessor with existing scalar caches sdk/1: (0, 7), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r27,scratch:r22,flags:r26,names:r28,index:r21
font MAX R28 thin accessor cached flag members 0: (0, 13), insns 239/239; colors font:r25,count:r24,groups:r28,glyph:r31,blocks:r23,size:r29,stride:r30,scratch:r22,flags:r27,names:r26,index:r21
font MAX R28 thin accessor cached flag members 1: (0, 0), insns 239/239; colors font:r25,count:r24,groups:r29,glyph:r31,blocks:r23,size:r30,stride:r28,scratch:r22,flags:r27,names:r26,index:r21
R28 exact breakthrough: thin read-only FontGlyphGroupsAcs getters preserve font/count caching; a first-use const flags stride copied into the accessor and RoundUp returning the typed extent reserve stride r28,flags r27,groups r29,size r30 and leave the generated name cursor r26. All target239/239 instructions now exact (ctxdiff0), with the other cached registers font25,count24,blocks23,glyph31 preserved. Literal reference constructor-first caches changed count/font allocation; existing real cached-value declarations retained for the exact candidate. No definition volatile or widening needed (target has neither proof).
R28 authority quick gate after the exact accessor candidate: full build ok; DOL26116613f624061ba99c8d1a299aaa6efa85670d; NW4R23/23,code5120/5120,data96/96,all sections100%; NHTTP6/7,code1196/1692,no data. All other22 Font functions remain exact. Regression0,forbidden0,readability0,GATE PASS. Cosmetic blank-line cleanup rebuilt and retained239/239,ctxdiff0. Data ownership: all Font.data88 and.sbss2 8 already paired100%; NHTTP owns no data; no symbol rename or extent correction justified.

## MAX reference round NHTTP follow-up
Fetched origin/main 449529d92405f8f7fda610660c7794914a81dfe6; compareToken source is byte-for-byte the same as our baseline and remains97.32258%,6/7. Pool identical/no data. disasm_fn structural diagnosis: frame0x30/save25,124/124 instructions,size0x1f0 ending at next loadFrom symbol. Every operation and operand exact apart from five independent preheader initializations54-58: target upper-range constants A,Z then delimiter sign extension,last-position subtraction,zero carry constant; ours delimiter,last-position,A,zero,Z. No volatile reload or 8/16-bit shift-mask evidence. Apply the font accessor insight to a real const token-match descriptor and inline comparison helper before final declaration search.
http MAX R29 real token-match descriptor leading/const0: compile rejected: #   Error:                                                                 ^ #   (10124) illegal constant expression
http MAX R29 real token-match descriptor leading/const1: compile rejected: #   Error:                                                                 ^ #   (10124) illegal constant expression
http MAX R29 real token-match descriptor before find/const0: compile rejected: #   Error:                                                                 ^ #   (10124) illegal constant expression
http MAX R29 real token-match descriptor before find/const1: compile rejected: #   Error:                                                                 ^ #   (10124) illegal constant expression
http MAX R29 real token-match descriptor before read/const0: compile rejected: #   Error:     ^^^^^^^^^^^^^^^^^^^^ #   (10141) expression syntax error
http MAX R29 real token-match descriptor before read/const1: compile rejected: #   Error:     ^^^^^ #   (10141) expression syntax error
http MAX R29 real token-match descriptor after read/const0: compile rejected: #   Error:     ^^^^^^^^^^^^^^^^^^^^ #   (10141) expression syntax error
http MAX R29 real token-match descriptor after read/const1: compile rejected: #   Error:     ^^^^^ #   (10141) expression syntax error
http MAX R30 descriptor field first-assignment order before find/('firstUpper', 'lastUpper', 'delimiter', 'lastPosition'): (5, 55), insns 124/124
http MAX R30 descriptor field first-assignment order before find/('delimiter', 'lastPosition', 'firstUpper', 'lastUpper'): (5, 55), insns 124/124
http MAX R30 descriptor field first-assignment order before find/('firstUpper', 'delimiter', 'lastUpper', 'lastPosition'): (5, 55), insns 124/124
http MAX R30 descriptor field first-assignment order before find/('lastPosition', 'delimiter', 'lastUpper', 'firstUpper'): (5, 55), insns 124/124
http MAX R30 descriptor field first-assignment order before read/('firstUpper', 'lastUpper', 'delimiter', 'lastPosition'): (5, 34), insns 124/124
http MAX R30 descriptor field first-assignment order before read/('delimiter', 'lastPosition', 'firstUpper', 'lastUpper'): (5, 34), insns 124/124
http MAX R30 descriptor field first-assignment order before read/('firstUpper', 'delimiter', 'lastUpper', 'lastPosition'): (5, 34), insns 124/124
http MAX R30 descriptor field first-assignment order before read/('lastPosition', 'delimiter', 'lastUpper', 'firstUpper'): (5, 34), insns 124/124
http MAX R30 descriptor field first-assignment order after read/('firstUpper', 'lastUpper', 'delimiter', 'lastPosition'): (6, 16), insns 124/124
http MAX R30 descriptor field first-assignment order after read/('delimiter', 'lastPosition', 'firstUpper', 'lastUpper'): (6, 16), insns 124/124
http MAX R30 descriptor field first-assignment order after read/('firstUpper', 'delimiter', 'lastUpper', 'lastPosition'): (6, 16), insns 124/124
http MAX R30 descriptor field first-assignment order after read/('lastPosition', 'delimiter', 'lastUpper', 'firstUpper'): (6, 16), insns 124/124
http MAX R31 const ASCII range accessor int/leading/0: (8, 123), insns 128/124
http MAX R31 const ASCII range accessor int/leading/1: (8, 123), insns 128/124
http MAX R31 const ASCII range accessor int/if entry/0: (9, 122), insns 128/124
http MAX R31 const ASCII range accessor int/if entry/1: (9, 122), insns 128/124
http MAX R31 const ASCII range accessor int/scoped after read/0: (7, 102), insns 126/124
http MAX R31 const ASCII range accessor int/scoped after read/1: (7, 102), insns 126/124
http MAX R31 const ASCII range accessor s32/leading/0: (8, 123), insns 128/124
http MAX R31 const ASCII range accessor s32/leading/1: (8, 123), insns 128/124
http MAX R31 const ASCII range accessor s32/if entry/0: (9, 122), insns 128/124
http MAX R31 const ASCII range accessor s32/if entry/1: (9, 122), insns 128/124
http MAX R31 const ASCII range accessor s32/scoped after read/0: (7, 102), insns 126/124
http MAX R31 const ASCII range accessor s32/scoped after read/1: (7, 102), insns 126/124
http MAX R31 const ASCII range accessor s8/leading/0: (10, 120), insns 130/124
http MAX R31 const ASCII range accessor s8/leading/1: (10, 120), insns 130/124
http MAX R31 const ASCII range accessor s8/if entry/0: (10, 119), insns 130/124
http MAX R31 const ASCII range accessor s8/if entry/1: (10, 119), insns 130/124
http MAX R31 const ASCII range accessor s8/scoped after read/0: (10, 74), insns 128/124
http MAX R31 const ASCII range accessor s8/scoped after read/1: (10, 74), insns 128/124
http MAX R31 const ASCII range accessor u16/leading/0: (8, 123), insns 128/124
http MAX R31 const ASCII range accessor u16/leading/1: (8, 123), insns 128/124
http MAX R31 const ASCII range accessor u16/if entry/0: (9, 122), insns 128/124
http MAX R31 const ASCII range accessor u16/if entry/1: (9, 122), insns 128/124
http MAX R31 const ASCII range accessor u16/scoped after read/0: (7, 102), insns 126/124
http MAX R31 const ASCII range accessor u16/scoped after read/1: (7, 102), insns 126/124
http MAX R32 inline equality boundary pointer/int/0: (4, 5), insns 124/124
http MAX R32 inline equality boundary pointer/int/1: (4, 5), insns 124/124
http MAX R32 inline equality boundary pointer/BOOL/0: (4, 5), insns 124/124
http MAX R32 inline equality boundary pointer/BOOL/1: (4, 5), insns 124/124
http MAX R32 inline equality boundary pointer/s32/0: (4, 5), insns 124/124
http MAX R32 inline equality boundary pointer/s32/1: (4, 5), insns 124/124
http MAX R32 inline equality boundary scalar int/int/0: (4, 5), insns 124/124
http MAX R32 inline equality boundary scalar int/int/1: (4, 5), insns 124/124
http MAX R32 inline equality boundary scalar int/BOOL/0: (4, 5), insns 124/124
http MAX R32 inline equality boundary scalar int/BOOL/1: (4, 5), insns 124/124
http MAX R32 inline equality boundary scalar int/s32/0: (4, 5), insns 124/124
http MAX R32 inline equality boundary scalar int/s32/1: (4, 5), insns 124/124
http MAX R32 inline equality boundary scalar s8/int/0: (4, 5), insns 124/124
http MAX R32 inline equality boundary scalar s8/int/1: (4, 5), insns 124/124
http MAX R32 inline equality boundary scalar s8/BOOL/0: (4, 5), insns 124/124
http MAX R32 inline equality boundary scalar s8/BOOL/1: (4, 5), insns 124/124
http MAX R32 inline equality boundary scalar s8/s32/0: (4, 5), insns 124/124
http MAX R32 inline equality boundary scalar s8/s32/1: (4, 5), insns 124/124
http MAX R32 inline equality boundary scalar u8/int/0: (4, 5), insns 124/124
http MAX R32 inline equality boundary scalar u8/int/1: (4, 5), insns 124/124
http MAX R32 inline equality boundary scalar u8/BOOL/0: (4, 5), insns 124/124
http MAX R32 inline equality boundary scalar u8/BOOL/1: (4, 5), insns 124/124
http MAX R32 inline equality boundary scalar u8/s32/0: (4, 5), insns 124/124
http MAX R32 inline equality boundary scalar u8/s32/1: (4, 5), insns 124/124
http MAX R32 inline equality boundary scalar s32/int/0: (4, 5), insns 124/124
http MAX R32 inline equality boundary scalar s32/int/1: (4, 5), insns 124/124
http MAX R32 inline equality boundary scalar s32/BOOL/0: (4, 5), insns 124/124
http MAX R32 inline equality boundary scalar s32/BOOL/1: (4, 5), insns 124/124
http MAX R32 inline equality boundary scalar s32/s32/0: (4, 5), insns 124/124
http MAX R32 inline equality boundary scalar s32/s32/1: (4, 5), insns 124/124
R29-R32 NHTTP diagnosis: runtime match-descriptor field order/lifetimes compiled124/124 but introduced16-55 raw differences; constant ASCII range structs compiled126-130 instructions with stack/object work; equality helper pointer/scalar/return-type/argument-order variants all preserved the original five preheader differences. These are three distinct compiled source-level families, all rejected and reverted. No target proof for volatile or 16-bit byte widening, and both public input views are already const. Final declaration search follows; source restored to original97.32258% candidate.

R33 declaration search NHTTP: all6 local declaration permutations retained(4,5),124/124,source restored.
Reference-round completeness audit: GLGR now100%,239/239,ctxdiff0; no remaining NW4R function or data gap. Sole remaining owned function is NHTTPi_compareTokenN_HdrRecvBuf97.32258%,124/124,preheader54-58 initialization order. It has >=3 distinct compiled attempts this round (descriptor field order/lifetime,const ASCII range objects,inline equality boundaries), plus earlier const/type/loop/operand studies and declaration searches. NHTTP source is byte-for-byte the start-of-round/origin implementation. Font source exact candidate committed31e327a3; no symbol,extent,shared-header,configure or unrelated source changes. Running final full clean gate on both units.

## Reference-round final full gate (clean rebuild, both owned units)

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/NW4R/src/ut/ut_ArchiveFontBase] pool: IDENTICAL
[libs/NW4R/src/ut/ut_ArchiveFontBase] objdiff: code 5120/5120 data 96/96 functions 23/23 fuzzy 100.0000 linked code 0
[libs/NW4R/src/ut/ut_ArchiveFontBase] instruction-exact functions: 23/23
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .data size 88 match 100.0
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .sbss2 size 8 match 100.0
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .text size 5120 match 100.0
[libs/NW4R/src/ut/ut_ArchiveFontBase] baseline: code 4164/5120 data 96 functions 22 fuzzy 98.5227
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] pool: IDENTICAL
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] objdiff: code 1196/1692 data None/None functions 6/7 fuzzy 99.2151 linked code 0
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] instruction-exact functions: 6/7
[libs/RevoEX/src/nhttp/NHTTP_recvbuf]   section .text size 1692 match 99.21513
[libs/RevoEX/src/nhttp/NHTTP_recvbuf]   below 100: NHTTPi_compareTokenN_HdrRecvBuf 97.32258
[libs/RevoEX/src/nhttp/NHTTP_recvbuf] baseline: code 1196/1692 data None functions 6 fuzzy 99.2151
regressions vs baseline: 0
global matched_code_percent: 90.80962 -> 90.84154
global fuzzy_match_percent: 99.58569 -> 99.58823
global complete_code_percent: 71.43246 -> 71.43246
global matched_data_percent: 99.36639 -> 99.36639
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Final open-function re-list from clean gate: only NHTTPi_compareTokenN_HdrRecvBuf97.32258%,124/124,preheader54-58 ordering remains; three distinct new compiled families R30/R31/R32 and all6 declaration permutations logged. GLGR100%,239/239,code5120/5120,data96/96,23/23 instruction exact. Before->after Font22->23,code4164->5120,data96->96; HTTP6->6,code1196->1196,no data. All failures restored; source change only Font accessor/const stride/RoundUp/loop use. No linker/configuration/symbol renames/extent changes. Original NHTTP initialization/inline ordering is the remaining uncertainty.
