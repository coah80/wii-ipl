
# prior1 MAX reference round

Scope: VIInit, Window::DrawFrame, SOGetSockName and owned data. No wprintf edits.
Origin fetch succeeded; 26d7e1e052a80ea55d0591a82653370965ad5bb2; owned source and symbols match HEAD/origin. Shell execution works; historical bubblewrap blocker does not apply.

BASELINE main/libs/RevoEX/src/so/SOBasic {'fuzzy_match_percent': 99.79452, 'total_code': '4088', 'matched_code': '3836', 'matched_code_percent': 93.83562, 'total_data': '144', 'matched_data': '144', 'matched_data_percent': 100.0, 'total_functions': 22, 'matched_functions': 21, 'matched_functions_percent': 95.454544, 'total_units': 1}
Initial string pool IDENTICAL; data already 100% for every owned section. No symbol renames or extent changes needed.

BASELINE main/libs/NW4R/src/lyt/lyt_window {'fuzzy_match_percent': 99.75864, 'total_code': '11352', 'matched_code': '9848', 'matched_code_percent': 86.751236, 'total_data': '316', 'matched_data': '316', 'matched_data_percent': 100.0, 'total_functions': 21, 'matched_functions': 20, 'matched_functions_percent': 95.2381, 'total_units': 1}
Initial string pool IDENTICAL; data already 100% for every owned section. No symbol renames or extent changes needed.

BASELINE main/libs/RVL_SDK/src/vi/vi {'fuzzy_match_percent': 99.97521, 'total_code': '11296', 'matched_code': '9944', 'matched_code_percent': 88.03116, 'total_data': '1944', 'matched_data': '1944', 'matched_data_percent': 100.0, 'total_functions': 30, 'matched_functions': 29, 'matched_functions_percent': 96.666664, 'total_units': 1}
Initial string pool IDENTICAL; data already 100% for every owned section. No symbol renames or extent changes needed.

VIInit structural diagnosis: both frames 0x30; 338/338 instructions. Only 14 differences: clip active-height/top locals r29/r30/r31 rotate with shared framebuffer/PreCB/PostCB zero. No target spill/reload proof for new volatile. Reference changes declarations, explicit narrowing in AdjustPosition, and DVD-stop inline boundary; data 1944/1944.

VIInit | V1 reference removes unused format, DVD previous state block scoped | insns 338/338 structural/exact (0, 14) | objdiff 99.7929 | lost [] | data 1944/1944 | POOL IDENTICAL up to 7 (mine=7 base=7) | 63b67f44ab8a

199 M ('slwi', 'r29, r7, 1') B ('slwi', 'r30, r7, 1')
201 M ('subf', 'r26, r6, r29') B ('subf', 'r26, r6, r30')
222 M ('and', 'r30, r25, r10') B ('and', 'r31, r25, r10')
225 M ('and', 'r29, r26, r12') B ('and', 'r30, r26, r12')
227 M ('add', 'r7, r7, r30') B ('add', 'r7, r7, r31')
235 M ('li', 'r31, 0') B ('li', 'r29, 0')
238 M ('divw', 'r8, r29, r5') B ('divw', 'r8, r30, r5')
248 M ('sth', 'r31, 0x16(r4)') B ('sth', 'r29, 0x16(r4)')
250 M ('sth', 'r31, 0x18(r4)') B ('sth', 'r29, 0x18(r4)')
255 M ('stw', 'r31, 0x20(r4)') B ('stw', 'r29, 0x20(r4)')
260 M ('stb', 'r31, 0x3c(r4)') B ('stb', 'r29, 0x3c(r4)')
262 M ('stw', 'r31, 0x44(r4)') B ('stw', 'r29, 0x44(r4)')
274 M ('stw', 'r31, 0(0)') B ('stw', 'r29, 0(0)')
275 M ('stw', 'r31, 0(0)') B ('stw', 'r29, 0(0)')

VIInit | V2 reference scalar declaration group and required volatile DVD read | insns 338/338 structural/exact (0, 14) | objdiff 99.7929 | lost [] | data 1944/1944 | POOL IDENTICAL up to 7 (mine=7 base=7) | b4b22213ff0c

199 M ('slwi', 'r29, r7, 1') B ('slwi', 'r30, r7, 1')
201 M ('subf', 'r26, r6, r29') B ('subf', 'r26, r6, r30')
222 M ('and', 'r30, r25, r10') B ('and', 'r31, r25, r10')
225 M ('and', 'r29, r26, r12') B ('and', 'r30, r26, r12')
227 M ('add', 'r7, r7, r30') B ('add', 'r7, r7, r31')
235 M ('li', 'r31, 0') B ('li', 'r29, 0')
238 M ('divw', 'r8, r29, r5') B ('divw', 'r8, r30, r5')
248 M ('sth', 'r31, 0x16(r4)') B ('sth', 'r29, 0x16(r4)')
250 M ('sth', 'r31, 0x18(r4)') B ('sth', 'r29, 0x18(r4)')
255 M ('stw', 'r31, 0x20(r4)') B ('stw', 'r29, 0x20(r4)')
260 M ('stb', 'r31, 0x3c(r4)') B ('stb', 'r29, 0x3c(r4)')
262 M ('stw', 'r31, 0x44(r4)') B ('stw', 'r29, 0x44(r4)')
274 M ('stw', 'r31, 0(0)') B ('stw', 'r29, 0(0)')
275 M ('stw', 'r31, 0(0)') B ('stw', 'r29, 0(0)')

VIInit | V3 reference interrupt register value assignment order | insns 338/338 structural/exact (0, 0) | objdiff 100.0 | lost [] | data 1944/1944 | POOL IDENTICAL up to 7 (mine=7 base=7) | 4cf8217f30f5



VIInit | V4 reference clipping explicit u16 stores and grouped locals | insns 338/338 structural/exact (0, 14) | objdiff 99.7929 | lost [] | data 1944/1944 | POOL IDENTICAL up to 7 (mine=7 base=7) | 5e17b0aaa91d

199 M ('slwi', 'r29, r7, 1') B ('slwi', 'r30, r7, 1')
201 M ('subf', 'r26, r6, r29') B ('subf', 'r26, r6, r30')
222 M ('and', 'r30, r25, r10') B ('and', 'r31, r25, r10')
225 M ('and', 'r29, r26, r12') B ('and', 'r30, r26, r12')
227 M ('add', 'r7, r7, r30') B ('add', 'r7, r7, r31')
235 M ('li', 'r31, 0') B ('li', 'r29, 0')
238 M ('divw', 'r8, r29, r5') B ('divw', 'r8, r30, r5')
248 M ('sth', 'r31, 0x16(r4)') B ('sth', 'r29, 0x16(r4)')
250 M ('sth', 'r31, 0x18(r4)') B ('sth', 'r29, 0x18(r4)')
255 M ('stw', 'r31, 0x20(r4)') B ('stw', 'r29, 0x20(r4)')
260 M ('stb', 'r31, 0x3c(r4)') B ('stb', 'r29, 0x3c(r4)')
262 M ('stw', 'r31, 0x44(r4)') B ('stw', 'r29, 0x44(r4)')
274 M ('stw', 'r31, 0(0)') B ('stw', 'r29, 0(0)')
275 M ('stw', 'r31, 0(0)') B ('stw', 'r29, 0(0)')

VIInit | V5 hardware register value uses its actual u16 width | insns 338/338 structural/exact (0, 0) | objdiff 100.0 | lost [] | data 1944/1944 | POOL IDENTICAL up to 7 (mine=7 base=7) | 91d73ae4ffad



V5 clean full gate before commit
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/vi/vi] pool: IDENTICAL
[libs/RVL_SDK/src/vi/vi] objdiff: code 11296/11296 data 1944/1944 functions 30/30 fuzzy 100.0000 linked code 0
[libs/RVL_SDK/src/vi/vi] instruction-exact functions: 30/30
[libs/RVL_SDK/src/vi/vi]   section .bss size 368 match 100.0
[libs/RVL_SDK/src/vi/vi]   section .data size 1368 match 100.0
[libs/RVL_SDK/src/vi/vi]   section .sbss size 176 match 100.0
[libs/RVL_SDK/src/vi/vi]   section .sdata size 32 match 100.0
[libs/RVL_SDK/src/vi/vi]   section .text size 11296 match 100.0
[libs/RVL_SDK/src/vi/vi] baseline: code 9944/11296 data 1944 functions 29 fuzzy 99.9752
regressions vs baseline: 0
global matched_code_percent: 91.05281 -> 91.09795
global fuzzy_match_percent: 99.58826 -> 99.58836
global complete_code_percent: 73.73083 -> 74.01916
global matched_data_percent: 99.42271 -> 99.42271
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: no baseline for merge-base 26d7e1e0; compared against nearest snapshotted ancestor d7821052 (1 commits back)
GATE PASS
```

VIInit accepted locally: value now u16, matching the VI hardware register width. Both masks preserve 16 bits. This changes only register coloring, resolves every 14 instruction difference, and retains all sections at 100%. Clean full gate PASS; ctxdiff 338/338 diffs 0; pool 7/7 identical; zero regressions and forbidden/readability patterns. No configure.py or symbols change.

DrawFrame origin pre-function fetch: 26d7e1e052a80ea55d0591a82653370965ad5bb2; owned source identical to origin. Target frame 0xe0, 376/376 instructions. All 119 differences are registers: persistent flip table r21 vs r31 shifts geometry and alpha. Static table, branches, helper operations, floating-point order, and stack offsets identical; reference lacks the target-proven texture-count guard and has mutable bool. No volatile spill/reload proof; all 316 data bytes matched. Extent 0x5e0 ends exactly at DrawFrame4.

DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc | W1 reference mutable bUseVtxCol | insns 376/376 structural/exact (0, 119) | objdiff 98.17819 | lost [] | data 316/316 | POOL IDENTICAL up to 1 (mine=1 base=1) | e4d4a68bdadd

DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc | W2 material setup result separate declaration and assignment | insns 376/376 structural/exact (0, 119) | objdiff 98.17819 | lost [] | data 316/316 | POOL IDENTICAL up to 1 (mine=1 base=1) | 645a40fa68ea

DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc | W3 texture dimensions separate declaration and assignment | insns 381/376 structural/exact (161, 358) | objdiff 80.97607 | lost [] | data 316/316 | POOL IDENTICAL up to 1 (mine=1 base=1) | 356336b28e11

DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc | W4 coordinates passed via reference to the quad array | insns 381/376 structural/exact (96, 326) | objdiff 76.89096 | lost [] | data 316/316 | POOL IDENTICAL up to 1 (mine=1 base=1) | b75bb1a0e722

DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc | W5 alpha parameter const-qualified at definition | insns 376/376 structural/exact (0, 119) | objdiff 98.17819 | lost [] | data 316/316 | POOL IDENTICAL up to 1 (mine=1 base=1) | c852083af7e9

DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc | W6 explicitly narrow texture unit argument in vertex format and dimension query | insns 376/376 structural/exact (0, 119) | objdiff 98.17819 | lost [] | data 316/316 | POOL IDENTICAL up to 1 (mine=1 base=1) | 19a85be12cc2

DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc | W7 texture index ix uses u8 | insns 376/376 structural/exact (0, 119) | objdiff 98.17819 | lost [] | data 316/316 | POOL IDENTICAL up to 1 (mine=1 base=1) | 5cef145ed39c

DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc | W7 texture index iy uses u8 | insns 376/376 structural/exact (0, 119) | objdiff 98.17819 | lost [] | data 316/316 | POOL IDENTICAL up to 1 (mine=1 base=1) | 962c307d665a

DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc | W7 texture index ix,iy uses u8 | insns 376/376 structural/exact (0, 119) | objdiff 98.17819 | lost [] | data 316/316 | POOL IDENTICAL up to 1 (mine=1 base=1) | fba15f864c06

DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc | W7 texture index ix,iy uses u16 | insns 376/376 structural/exact (0, 119) | objdiff 98.17819 | lost [] | data 316/316 | POOL IDENTICAL up to 1 (mine=1 base=1) | 9230751b3b92

DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc | W7 texture index ix,iy uses u32 | insns 376/376 structural/exact (0, 119) | objdiff 98.17819 | lost [] | data 316/316 | POOL IDENTICAL up to 1 (mine=1 base=1) | 01617eecae4e

DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc | W7 texture index ix,iy uses unsigned long | insns 376/376 structural/exact (0, 119) | objdiff 98.17819 | lost [] | data 316/316 | POOL IDENTICAL up to 1 (mine=1 base=1) | aefd446c1d1d

DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc | W8 reference plain struct declaration for TextureFlipInfo | insns 376/376 structural/exact (0, 119) | objdiff 98.17819 | lost [] | data 316/316 | POOL IDENTICAL up to 1 (mine=1 base=1) | 127501278333

DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc | W9 reference texture-flip type declared outside anonymous namespace | BUILD FAILED | a29d9ea4e268
2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -Cpp_exceptions off -lang=c++ -MMD -c libs/NW4R/src/lyt/lyt_window.cpp -o build/43U/src/libs/NW4R/src/lyt && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/NW4R/src/lyt/lyt_window.d build/43U/src/libs/NW4R/src/lyt/lyt_window.d
### mwcceppc.exe Compiler:
#    File: libs\NW4R\src\lyt\lyt_window.cpp
# -----------------------------------------
#      48:         u8 coords[VERTEXCOLOR_MAX][FLIPINDEX_MAX];  // 0x00
#   Error:                   ^^^^^^^^^^^^^^^
#   (10140) undefined identifier 'VERTEXCOLOR_MAX'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc | W10 reference helper declarations before definitions | insns 376/376 structural/exact (0, 119) | objdiff 98.17819 | lost [] | data 316/316 | POOL IDENTICAL up to 1 (mine=1 base=1) | a4897278131e

DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc | W9b reference global texture-flip struct with real array dimensions | insns 376/376 structural/exact (0, 119) | objdiff 98.17819 | lost [] | data 316/316 | POOL IDENTICAL up to 1 (mine=1 base=1) | c3ee228d2a7f

DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc | W11 explicit inline boundary for GetTexutreFlipInfo | insns 376/376 structural/exact (0, 119) | objdiff 98.17819 | lost [] | data 60/316 | POOL IDENTICAL up to 1 (mine=1 base=1) | e833af53f19d

DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc | W11 explicit inline boundary for GetLTTexCoord | insns 376/376 structural/exact (0, 119) | objdiff 98.17819 | lost [] | data 316/316 | POOL IDENTICAL up to 1 (mine=1 base=1) | 383a08cfd390

DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc | W11 explicit inline boundary for GetRTTexCoord | insns 376/376 structural/exact (0, 119) | objdiff 98.17819 | lost [] | data 316/316 | POOL IDENTICAL up to 1 (mine=1 base=1) | 3d074b950c89

DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc | W11 explicit inline boundary for GetLBTexCoord | insns 376/376 structural/exact (0, 119) | objdiff 98.17819 | lost [] | data 316/316 | POOL IDENTICAL up to 1 (mine=1 base=1) | 7a08a15fb0f3

DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc | W11 explicit inline boundary for GetRBTexCoord | insns 376/376 structural/exact (0, 119) | objdiff 98.17819 | lost [] | data 316/316 | POOL IDENTICAL up to 1 (mine=1 base=1) | 0e6faa8f9403

DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc | W12 geometry and texture-coordinate helpers explicit inline | insns 376/376 structural/exact (0, 119) | objdiff 98.17819 | lost [] | data 60/316 | POOL IDENTICAL up to 1 (mine=1 base=1) | 1ccea4bdb91d

DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc | W13 polygon size constructor explicitly initializes its dimensions | insns 376/376 structural/exact (0, 119) | objdiff 98.17819 | lost [] | data 316/316 | POOL IDENTICAL up to 1 (mine=1 base=1) | dadaf033b0f2

DrawFrame W14 final declaration-order search after structural/reference/type trials
declaration block:
              const Size texSize = detail::GetTextureSize(frame.pMaterial, GX_TEXMAP0);
              const ut::Color vtxColors[VERTEXCOLOR_MAX];

              detail::TexCoords texCds[1];

              math::VEC2 polPt;
              Size polSize;
start (0, 119)
best (0, 119) after 52 builds; source restored; best order was:
            const Size texSize = detail::GetTextureSize(frame.pMaterial, GX_TEXMAP0);
            const ut::Color vtxColors[VERTEXCOLOR_MAX];

            detail::TexCoords texCds[1];

            math::VEC2 polPt;
            Size polSize;


DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc | W14 final declaration-order result | insns 376/376 structural/exact (0, 119) | objdiff 98.17819 | lost [] | data 316/316 | POOL IDENTICAL up to 1 (mine=1 base=1) | 3cc7e4df0b05

SOGetSockName origin pre-function fetch: 805e84045c82629c645e9ef1787c30d2bc33b5e7; owned source identical to origin. Pool 1/1 identical. Both frames 0x30,63/63 instructions; only first memcpy setup differs (ours destination/source/length, target source/length/destination). Neighbor extent starts at 0x814B34CC, exactly 0x814B33D0+0xFC; no overlap. All 144 target data bytes matched. Reference uses early goto conclude, address initializer, sizeof comparison, separate prepare assignment; wire request raw-offset expressions replaced by existing NameRequest field.

SOGetSockName | S1 reference statement order and conclude goto, with typed wire fields | insns 63/63 structural/exact (2, 3) | objdiff 96.666664 | lost [] | data 144/144 | POOL IDENTICAL up to 1 (mine=1 base=1) | 33cc57840375

32 M ('mr', 'r3, r28') B ('mr', 'r4, r27')
33 M ('mr', 'r4, r27') B ('lbz', 'r5, 0(r27)')
34 M ('lbz', 'r5, 0(r27)') B ('mr', 'r3, r28')

SOGetSockName | S2 reference address initialization and separate prepare assignment | insns 63/63 structural/exact (2, 3) | objdiff 96.666664 | lost [] | data 144/144 | POOL IDENTICAL up to 1 (mine=1 base=1) | b5a1a7e874aa

32 M ('mr', 'r3, r28') B ('mr', 'r4, r27')
33 M ('mr', 'r4, r27') B ('lbz', 'r5, 0(r27)')
34 M ('lbz', 'r5, 0(r27)') B ('mr', 'r3, r28')

SOGetSockName | S3 first address copy uses an explicit const input view | insns 63/63 structural/exact (2, 3) | objdiff 96.666664 | lost [] | data 144/144 | POOL IDENTICAL up to 1 (mine=1 base=1) | 53088c5d144f

32 M ('mr', 'r3, r28') B ('mr', 'r4, r27')
33 M ('mr', 'r4, r27') B ('lbz', 'r5, 0(r27)')
34 M ('lbz', 'r5, 0(r27)') B ('mr', 'r3, r28')

SOGetSockName | S4 const socket address view for validation and input, mutable output parameter | insns 63/63 structural/exact (2, 5) | objdiff 96.349205 | lost [] | data 144/144 | POOL IDENTICAL up to 1 (mine=1 base=1) | c08e5df4c7de

5 M ('mr', 'r27, r4') B ('mr', 'r28, r3')
6 M ('mr', 'r28, r3') B ('mr', 'r27, r4')
32 M ('mr', 'r3, r28') B ('mr', 'r4, r27')
33 M ('mr', 'r4, r27') B ('lbz', 'r5, 0(r27)')
34 M ('lbz', 'r5, 0(r27)') B ('mr', 'r3, r28')

SOGetSockName | S5 first copy views its header as const bytes | insns 63/63 structural/exact (2, 3) | objdiff 96.666664 | lost [] | data 144/144 | POOL IDENTICAL up to 1 (mine=1 base=1) | 9e0bb74dd11a

32 M ('mr', 'r3, r28') B ('mr', 'r4, r27')
33 M ('mr', 'r4, r27') B ('lbz', 'r5, 0(r27)')
34 M ('lbz', 'r5, 0(r27)') B ('mr', 'r3, r28')

SOGetSockName | S6 typed copy helper with const source boundary | insns 63/63 structural/exact (2, 3) | objdiff 96.666664 | lost [] | data 144/144 | POOL IDENTICAL up to 1 (mine=1 base=1) | 6a49cab5c214

32 M ('mr', 'r3, r28') B ('mr', 'r4, r27')
33 M ('mr', 'r4, r27') B ('lbz', 'r5, 0(r27)')
34 M ('lbz', 'r5, 0(r27)') B ('mr', 'r3, r28')

SOGetSockName | S7 allocation size declared u32 | insns 63/63 structural/exact (2, 3) | objdiff 96.666664 | lost [] | data 144/144 | POOL IDENTICAL up to 1 (mine=1 base=1) | 68140082eff9

32 M ('mr', 'r3, r28') B ('mr', 'r4, r27')
33 M ('mr', 'r4, r27') B ('lbz', 'r5, 0(r27)')
34 M ('lbz', 'r5, 0(r27)') B ('mr', 'r3, r28')

SOGetSockName | S7 allocation size declared u16 | insns 63/63 structural/exact (3, 4) | objdiff 95.71429 | lost [] | data 144/144 | POOL IDENTICAL up to 1 (mine=1 base=1) | 404166a4490e

22 M ('rlwinm', 'r31, r0, 0, 0x10, 0x1a') B ('rlwinm', 'r31, r0, 0, 0, 0x1a')
32 M ('mr', 'r3, r28') B ('mr', 'r4, r27')
33 M ('mr', 'r4, r27') B ('lbz', 'r5, 0(r27)')
34 M ('lbz', 'r5, 0(r27)') B ('mr', 'r3, r28')

SOGetSockName | S7 allocation size declared size_t | insns 63/63 structural/exact (2, 3) | objdiff 96.666664 | lost [] | data 144/144 | POOL IDENTICAL up to 1 (mine=1 base=1) | 73d720d3670d

32 M ('mr', 'r3, r28') B ('mr', 'r4, r27')
33 M ('mr', 'r4, r27') B ('lbz', 'r5, 0(r27)')
34 M ('lbz', 'r5, 0(r27)') B ('mr', 'r3, r28')

SOGetSockName | S8 first copy separately reads length as u8 | insns 63/63 structural/exact (2, 3) | objdiff 96.666664 | lost [] | data 144/144 | POOL IDENTICAL up to 1 (mine=1 base=1) | c847ce10914f

32 M ('mr', 'r3, r28') B ('mr', 'r4, r27')
33 M ('mr', 'r4, r27') B ('lbz', 'r5, 0(r27)')
34 M ('lbz', 'r5, 0(r27)') B ('mr', 'r3, r28')

SOGetSockName | S8 first copy separately reads length as u16 | insns 63/63 structural/exact (2, 3) | objdiff 96.666664 | lost [] | data 144/144 | POOL IDENTICAL up to 1 (mine=1 base=1) | becaa347c984

32 M ('mr', 'r3, r28') B ('mr', 'r4, r27')
33 M ('mr', 'r4, r27') B ('lbz', 'r5, 0(r27)')
34 M ('lbz', 'r5, 0(r27)') B ('mr', 'r3, r28')

SOGetSockName | S8 first copy separately reads length as u32 | insns 63/63 structural/exact (2, 3) | objdiff 96.666664 | lost [] | data 144/144 | POOL IDENTICAL up to 1 (mine=1 base=1) | a1d015de3910

32 M ('mr', 'r3, r28') B ('mr', 'r4, r27')
33 M ('mr', 'r4, r27') B ('lbz', 'r5, 0(r27)')
34 M ('lbz', 'r5, 0(r27)') B ('mr', 'r3, r28')

SOGetSockName | S8 first copy separately reads length as int | insns 63/63 structural/exact (2, 3) | objdiff 96.666664 | lost [] | data 144/144 | POOL IDENTICAL up to 1 (mine=1 base=1) | d235318a13b5

32 M ('mr', 'r3, r28') B ('mr', 'r4, r27')
33 M ('mr', 'r4, r27') B ('lbz', 'r5, 0(r27)')
34 M ('lbz', 'r5, 0(r27)') B ('mr', 'r3, r28')

SOGetSockName | S8 first copy separately reads length as size_t | insns 63/63 structural/exact (2, 3) | objdiff 96.666664 | lost [] | data 144/144 | POOL IDENTICAL up to 1 (mine=1 base=1) | 43864ee20f80

32 M ('mr', 'r3, r28') B ('mr', 'r4, r27')
33 M ('mr', 'r4, r27') B ('lbz', 'r5, 0(r27)')
34 M ('lbz', 'r5, 0(r27)') B ('mr', 'r3, r28')

SOGetSockName | S9 reference command allocation is int pointer with typed address-field view | insns 63/63 structural/exact (2, 3) | objdiff 96.666664 | lost [] | data 144/144 | POOL IDENTICAL up to 1 (mine=1 base=1) | f42be4f4821b

32 M ('mr', 'r3, r28') B ('mr', 'r4, r27')
33 M ('mr', 'r4, r27') B ('lbz', 'r5, 0(r27)')
34 M ('lbz', 'r5, 0(r27)') B ('mr', 'r3, r28')

SOGetSockName | S10 reply buffer held as opaque IOCTL buffer with typed length view | insns 63/63 structural/exact (2, 3) | objdiff 96.666664 | lost [] | data 144/144 | POOL IDENTICAL up to 1 (mine=1 base=1) | 39d08eea8df3

32 M ('mr', 'r3, r28') B ('mr', 'r4, r27')
33 M ('mr', 'r4, r27') B ('lbz', 'r5, 0(r27)')
34 M ('lbz', 'r5, 0(r27)') B ('mr', 'r3, r28')

SOGetSockName | S11 promote first copy length through unsigned halfword | insns 63/63 structural/exact (2, 3) | objdiff 96.666664 | lost [] | data 144/144 | POOL IDENTICAL up to 1 (mine=1 base=1) | 8dae136f16d1

32 M ('mr', 'r3, r28') B ('mr', 'r4, r27')
33 M ('mr', 'r4, r27') B ('lbz', 'r5, 0(r27)')
34 M ('lbz', 'r5, 0(r27)') B ('mr', 'r3, r28')

SOGetSockName | S12 syscall result declared s16 | insns 63/63 structural/exact (8, 20) | objdiff 91.5873 | lost [] | data 144/144 | POOL IDENTICAL up to 1 (mine=1 base=1) | 2e50fd103218

10 M ('extsh.', 'r3, r3') B ('cmpwi', 'r3, 0')
19 M ('b', '136') B ('b', '140')
29 M ('b', '96') B ('b', '100')
32 M ('mr', 'r3, r28') B ('mr', 'r4, r27')
33 M ('mr', 'r4, r27') B ('lbz', 'r5, 0(r27)')
34 M ('lbz', 'r5, 0(r27)') B ('mr', 'r3, r28')
43 M ('extsh.', 'r30, r3') B ('cmpwi', 'r3, 0')
44 M ('blt', '20') B ('mr', 'r30, r3')
45 M ('lbz', 'r5, 0(r28)') B ('blt', '20')
46 M ('mr', 'r3, r27') B ('lbz', 'r5, 0(r28)')
47 M ('mr', 'r4, r28') B ('mr', 'r3, r27')
48 M ('bl', '0') B ('mr', 'r4, r28')
49 M ('mr', 'r4, r29') B ('bl', '0')
50 M ('mr', 'r5, r31') B ('mr', 'r4, r29')
51 M ('li', 'r3, 0xc') B ('mr', 'r5, r31')
52 M ('bl', '0') B ('li', 'r3, 0xc')
53 M ('mr', 'r4, r30') B ('bl', '0')
54 M ('li', 'r3, 0') B ('mr', 'r4, r30')
55 M ('bl', '0') B ('li', 'r3, 0')
56 M ('extsh', 'r3, r3') B ('bl', '0')

SOGetSockName | S12 syscall result declared long | insns 63/63 structural/exact (2, 3) | objdiff 96.666664 | lost [] | data 144/144 | POOL IDENTICAL up to 1 (mine=1 base=1) | b72c9cdddb5e

32 M ('mr', 'r3, r28') B ('mr', 'r4, r27')
33 M ('mr', 'r4, r27') B ('lbz', 'r5, 0(r27)')
34 M ('lbz', 'r5, 0(r27)') B ('mr', 'r3, r28')

SOGetSockName | S12 syscall result declared s32 | insns 63/63 structural/exact (2, 3) | objdiff 96.666664 | lost [] | data 144/144 | POOL IDENTICAL up to 1 (mine=1 base=1) | 1ab005e08c72

32 M ('mr', 'r3, r28') B ('mr', 'r4, r27')
33 M ('mr', 'r4, r27') B ('lbz', 'r5, 0(r27)')
34 M ('lbz', 'r5, 0(r27)') B ('mr', 'r3, r28')

SOGetSockName | S13 reply initialized through memcpy destination return | insns 63/63 structural/exact (10, 20) | objdiff 89.12698 | lost [] | data 144/144 | POOL IDENTICAL up to 1 (mine=1 base=1) | 7693f4b6b84c

5 M ('mr', 'r29, r3') B ('mr', 'r28, r3')
18 M ('li', 'r29, -0x1c') B ('li', 'r30, -0x1c')
22 M ('rlwinm', 'r30, r0, 0, 0, 0x1a') B ('rlwinm', 'r31, r0, 0, 0, 0x1a')
23 M ('mr', 'r4, r30') B ('mr', 'r4, r31')
26 M ('mr', 'r28, r3') B ('mr', 'r29, r3')
28 M ('li', 'r29, -0x31') B ('li', 'r30, -0x31')
30 M ('stw', 'r29, 0(r3)') B ('stw', 'r28, 0(r3)')
31 M ('mr', 'r4, r27') B ('addi', 'r28, r3, 0x20')
32 M ('addi', 'r3, r3, 0x20') B ('mr', 'r4, r27')
34 M ('bl', '0') B ('mr', 'r3, r28')
35 M ('mr', 'r31, r3') B ('bl', '0')
37 M ('lbz', 'r8, 0(r27)') B ('mr', 'r5, r29')
38 M ('mr', 'r5, r28') B ('lbz', 'r8, 0(r27)')
39 M ('mr', 'r7, r31') B ('mr', 'r7, r28')
44 M ('mr', 'r29, r3') B ('mr', 'r30, r3')
46 M ('lbz', 'r5, 0(r31)') B ('lbz', 'r5, 0(r28)')
48 M ('mr', 'r4, r31') B ('mr', 'r4, r28')
50 M ('mr', 'r4, r28') B ('mr', 'r4, r29')
51 M ('mr', 'r5, r30') B ('mr', 'r5, r31')
54 M ('mr', 'r4, r29') B ('mr', 'r4, r30')

SOGetSockName | S14 reply pointer obtained from the initial address-field copy | insns 63/63 structural/exact (10, 6) | objdiff 90.07937 | lost [] | data 144/144 | POOL IDENTICAL up to 1 (mine=1 base=1) | 59b28a410bde

31 M ('mr', 'r4, r27') B ('addi', 'r28, r3, 0x20')
32 M ('addi', 'r3, r3, 0x20') B ('mr', 'r4, r27')
34 M ('bl', '0') B ('mr', 'r3, r28')
35 M ('mr', 'r28, r3') B ('bl', '0')
37 M ('lbz', 'r8, 0(r27)') B ('mr', 'r5, r29')
38 M ('mr', 'r5, r29') B ('lbz', 'r8, 0(r27)')

SOGetSockName | S15 socket command and read-only address initialized in one typed helper | insns 63/63 structural/exact (2, 3) | objdiff 96.666664 | lost [] | data 144/144 | POOL IDENTICAL up to 1 (mine=1 base=1) | 53a9d11f1936

32 M ('mr', 'r3, r28') B ('mr', 'r4, r27')
33 M ('mr', 'r4, r27') B ('lbz', 'r5, 0(r27)')
34 M ('lbz', 'r5, 0(r27)') B ('mr', 'r3, r28')

SOGetSockName | S16 source-first read-only request initializer returns the address buffer | insns 63/63 structural/exact (2, 19) | objdiff 95.39683 | lost [] | data 144/144 | POOL IDENTICAL up to 1 (mine=1 base=1) | 7a7c904069d2

5 M ('mr', 'r29, r3') B ('mr', 'r28, r3')
18 M ('li', 'r29, -0x1c') B ('li', 'r30, -0x1c')
22 M ('rlwinm', 'r30, r0, 0, 0, 0x1a') B ('rlwinm', 'r31, r0, 0, 0, 0x1a')
23 M ('mr', 'r4, r30') B ('mr', 'r4, r31')
26 M ('mr', 'r28, r3') B ('mr', 'r29, r3')
28 M ('li', 'r29, -0x31') B ('li', 'r30, -0x31')
30 M ('stw', 'r29, 0(r3)') B ('stw', 'r28, 0(r3)')
31 M ('addi', 'r31, r3, 0x20') B ('addi', 'r28, r3, 0x20')
32 M ('mr', 'r3, r31') B ('mr', 'r4, r27')
33 M ('mr', 'r4, r27') B ('lbz', 'r5, 0(r27)')
34 M ('lbz', 'r5, 0(r27)') B ('mr', 'r3, r28')
37 M ('mr', 'r5, r28') B ('mr', 'r5, r29')
39 M ('mr', 'r7, r31') B ('mr', 'r7, r28')
44 M ('mr', 'r29, r3') B ('mr', 'r30, r3')
46 M ('lbz', 'r5, 0(r31)') B ('lbz', 'r5, 0(r28)')
48 M ('mr', 'r4, r31') B ('mr', 'r4, r28')
50 M ('mr', 'r4, r28') B ('mr', 'r4, r29')
51 M ('mr', 'r5, r30') B ('mr', 'r5, r31')
54 M ('mr', 'r4, r29') B ('mr', 'r4, r30')

SOGetSockName S17 final declaration-order search after reference/copy-type/helper trials
declaration block:
      int size;
      int result;
      s32 rm;
      NameRequest* request;
      SOSockAddr* reply;
      SOSockAddr* addr;
start (2, 3)
best (2, 3) after 36 builds; source restored; best order was:
    int size;
    int result;
    s32 rm;
    NameRequest* request;
    SOSockAddr* reply;
    SOSockAddr* addr;


SOGetSockName | S17 final declaration-order result | insns 63/63 structural/exact (2, 3) | objdiff 96.666664 | lost [] | data 144/144 | POOL IDENTICAL up to 1 (mine=1 base=1) | 73d59f1449b9

32 M ('mr', 'r3, r28') B ('mr', 'r4, r27')
33 M ('mr', 'r4, r27') B ('lbz', 'r5, 0(r27)')
34 M ('lbz', 'r5, 0(r27)') B ('mr', 'r3, r28')

FINAL OPEN AUDIT | SOGetSockName | objdiff 96.666664% | 25 distinct successful source trials | all unsuccessful source restored
FINAL OPEN AUDIT | DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc | objdiff 98.17819% | 23 distinct successful source trials | all unsuccessful source restored
Retained source: VIInit hardware register value u16 only, local commit bfe67f5a. No other source/config/header changes. All owned data sections 100%; data symbol/extent corrections unnecessary. DrawFrame remains register-only at 376/376, 119 differences; SOGetSockName remains first-copy setup scheduling at 63/63, 3 differences.

Final full clean gate over all owned units
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/vi/vi] pool: IDENTICAL
[libs/RVL_SDK/src/vi/vi] objdiff: code 11296/11296 data 1944/1944 functions 30/30 fuzzy 100.0000 linked code 0
[libs/RVL_SDK/src/vi/vi] instruction-exact functions: 30/30
[libs/RVL_SDK/src/vi/vi]   section .bss size 368 match 100.0
[libs/RVL_SDK/src/vi/vi]   section .data size 1368 match 100.0
[libs/RVL_SDK/src/vi/vi]   section .sbss size 176 match 100.0
[libs/RVL_SDK/src/vi/vi]   section .sdata size 32 match 100.0
[libs/RVL_SDK/src/vi/vi]   section .text size 11296 match 100.0
[libs/RVL_SDK/src/vi/vi] baseline: code 9944/11296 data 1944 functions 29 fuzzy 99.9752
[libs/NW4R/src/lyt/lyt_window] pool: IDENTICAL
[libs/NW4R/src/lyt/lyt_window] objdiff: code 9848/11352 data 316/316 functions 20/21 fuzzy 99.7586 linked code 0
[libs/NW4R/src/lyt/lyt_window] instruction-exact functions: 20/21
[libs/NW4R/src/lyt/lyt_window]   section .ctors size 4 match 100.0
[libs/NW4R/src/lyt/lyt_window]   section .data size 256 match 100.0
[libs/NW4R/src/lyt/lyt_window]   section .sbss size 8 match 100.0
[libs/NW4R/src/lyt/lyt_window]   section .sdata2 size 48 match 100.0
[libs/NW4R/src/lyt/lyt_window]   section .text size 11352 match 99.75864
[libs/NW4R/src/lyt/lyt_window]   below 100: DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc 98.17819
[libs/NW4R/src/lyt/lyt_window] baseline: code 9848/11352 data 316 functions 20 fuzzy 99.7586
[libs/RevoEX/src/so/SOBasic] pool: IDENTICAL
[libs/RevoEX/src/so/SOBasic] objdiff: code 3836/4088 data 144/144 functions 21/22 fuzzy 99.7945 linked code 0
[libs/RevoEX/src/so/SOBasic] instruction-exact functions: 21/22
[libs/RevoEX/src/so/SOBasic]   section .bss size 40 match 100.0
[libs/RevoEX/src/so/SOBasic]   section .data size 88 match 100.0
[libs/RevoEX/src/so/SOBasic]   section .sbss size 8 match 100.0
[libs/RevoEX/src/so/SOBasic]   section .sdata size 8 match 100.0
[libs/RevoEX/src/so/SOBasic]   section .text size 4088 match 99.79452
[libs/RevoEX/src/so/SOBasic]   below 100: SOGetSockName 96.666664
[libs/RevoEX/src/so/SOBasic] baseline: code 3836/4088 data 144 functions 21 fuzzy 99.7945
regressions vs baseline: 0
global matched_code_percent: 91.05281 -> 91.09795
global fuzzy_match_percent: 99.58826 -> 99.58836
global complete_code_percent: 74.01916 -> 74.01916
global matched_data_percent: 99.42271 -> 99.42271
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Post-gate checks: ninja -C . build/43U/ok progress build/43U/report.json PASS. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. VIInit ctxdiff 338/338 diffs 0; SOGetSockName 63/63 diffs 3. Final pools identical: vi 7/7, window 1/1, SOBasic 1/1. Git diff --check PASS.
Final owned metrics (exact functions, matched code bytes, matched data bytes): vi 29/30,9944/11296,1944/1944 -> 30/30,11296/11296,1944/1944; lyt_window 20/21,9848/11352,316/316 unchanged; SOBasic 21/22,3836/4088,144/144 unchanged.
Final origin/main advanced to 805e84045c82629c645e9ef1787c30d2bc33b5e7 during other workers: the local scope diff against merge-base 26d7e1e0 contains only vi.c and this attempts log; no out-of-scope edits. Worker did not rebase, link, push or contact upstream.
