# tex1 ultra attempts

43U worker branch agent/w1003/sol-tex1-ultra, initial HEAD 333eea81.
Owned units Texture_MCUtoRGBA8, Texture_MCUtoRGB565, Texture_MCUtoY8U8V8.
Read tex1.md, local AGENTS.md, unslop, prior texture attempts and both orch/perm9-progress and orch/fz20-progress diffs. No subworkers, linking, pushes or branch operations.
Initial full-build quick gate PASS, SHA1 26116613f624061ba99c8d1a299aaa6efa85670d, regressions 0.
RGBA8 objdiff/instruction-exact 2/13, code 660/6596, data 0/0.
RGB565 objdiff/instruction-exact 6/13, code 2284/6184, data 0/0.
Y8U8V8 objdiff 12/13, gate instruction-exact 2/13, code 15164/15948, data 0/0.
All pools empty and identical, confirmed with pool_diff.py using both object paths. No data symbols or extents to rename.
Reference index has no entries for these converters. Target function extents are contiguous.
Prior rejected levers excluded: state const, reversing green operands/clamps, parameter and declaration permutations alone, array-address and aggregate buffer representations.
Sibling comparison: setup functions share all switch cases and folding mismatch; planar luma loop uses indexed reads then bulk pointer advance; exact RGB565 211/edge uses explicit Y, RGB offsets, y as row counter and direct halfword indexing. RGBA8 still has in-place alpha/channel packing with different temporary lifetimes.

## TMCJPEGDEC_converterYUV444toRGB565
Origin fetch check: still baseline/open. Reference index absent. Baseline (98.71429, (6, 13), 91, 91)
- blue owns luminance with green then red then blue conversion: (98.68132, (4, 14), 91, 91); source dee765adf974.
- blue owns luminance and green packed last: (97.96703, (0, 28), 91, 91); source 62d408e571f9.
- blue owns luminance and independent RGB565 packed fields: (95.87912, (0, 43), 91, 91); source 47307eca52e3.

## TMCJPEGDEC_converterYUV411toRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (82.6033, (36, 153), 242, 242)

## TMCJPEGDEC_set_converterRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (93.91765, (36, 169), 169, 170)
Diagnosis: target keeps buffer base at entry and indirect row additions; compiled base folds in every switch case. No extent overlap. Sibling case layouts identical.
- conversion buffer as IDCT header words and byte row outputs: (93.91765, (36, 169), 169, 170); source f611dbdc1e12.
- row selection by widened MCU mode index: (84.511765, (52, 170), 181, 170); source beb08f66ec42.
- common first luminance row and MCU mode shared across switch: compiler failed, not counted. exturecvtr/Texture_MCUtoRGBA8.d build/43U/src/libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8.d ### mwcceppc.exe Compiler: #    File: libs\RVLMiddleware\TMC_JPEG\src\texturecvtr\Texture_MCUtoRGBA8.c # ------------------------------------------------------------------------- #      26:     u8* firstRow = buffer + 4;  #   Error:     ^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 

## TMCJPEGDEC_set_converterRGB565
Origin fetch check: still baseline/open. Reference index absent. Baseline (93.91765, (36, 169), 169, 170)
Diagnosis: target keeps buffer base at entry and indirect row additions; compiled base folds in every switch case. No extent overlap. Sibling case layouts identical.
- conversion buffer as IDCT header words and byte row outputs: (93.91765, (36, 169), 169, 170); source 39bb72d28eff.
- row selection by widened MCU mode index: (84.511765, (52, 170), 181, 170); source 2aea4f08a875.
- common first luminance row and MCU mode shared across switch: compiler failed, not counted. recvtr/Texture_MCUtoRGB565.d build/43U/src/libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565.d ### mwcceppc.exe Compiler: #    File: libs\RVLMiddleware\TMC_JPEG\src\texturecvtr\Texture_MCUtoRGB565.c # -------------------------------------------------------------------------- #      26:     u8* firstRow = buffer + 4;  #   Error:     ^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 

## TMCJPEGDEC_set_converterY8U8V8
Origin fetch check: still baseline/open. Reference index absent. Baseline (92.78571, (41, 195), 195, 196)
Diagnosis: target keeps buffer base at entry and indirect row additions; compiled base folds in every switch case. No extent overlap. Sibling case layouts identical.
- conversion buffer as IDCT header words and byte row outputs: (92.78571, (41, 195), 195, 196); source a866de64530c.
- row selection by widened MCU mode index: (84.755104, (57, 196), 207, 196); source 6ff79da16e0f.
- common first luminance row and MCU mode shared across switch: compiler failed, not counted. recvtr/Texture_MCUtoY8U8V8.d build/43U/src/libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8.d ### mwcceppc.exe Compiler: #    File: libs\RVLMiddleware\TMC_JPEG\src\texturecvtr\Texture_MCUtoY8U8V8.c # -------------------------------------------------------------------------- #      26:     u8* firstRow = buffer + 4;  #   Error:     ^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 

## TMCJPEGDEC_set_converterRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (93.91765, (36, 169), 169, 170)
Diagnosis: target keeps buffer base at entry and indirect row additions; compiled base folds in every switch case. No extent overlap. Sibling case layouts identical.
- common first luminance row and MCU mode shared across switch: (81.05882, (75, 168), 161, 170); source 830b58c26106.

## TMCJPEGDEC_set_converterRGB565
Origin fetch check: still baseline/open. Reference index absent. Baseline (93.91765, (36, 169), 169, 170)
Diagnosis: target keeps buffer base at entry and indirect row additions; compiled base folds in every switch case. No extent overlap. Sibling case layouts identical.
- common first luminance row and MCU mode shared across switch: (81.05882, (75, 168), 161, 170); source d471374f3880.

## TMCJPEGDEC_set_converterY8U8V8
Origin fetch check: still baseline/open. Reference index absent. Baseline (92.78571, (41, 195), 195, 196)
Diagnosis: target keeps buffer base at entry and indirect row additions; compiled base folds in every switch case. No extent overlap. Sibling case layouts identical.
- common first luminance row and MCU mode shared across switch: (81.63265, (80, 194), 187, 196); source 527c11005199.

## TMCJPEGDEC_converterYUV411toRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (82.6033, (36, 153), 242, 242)
Sibling source copied locally from RGB565 corresponding MCU, replacing only format stride/stores. Target/ours full disassembly captured; target frame/count checked before trials.
- corresponding RGB565 MCU loop and channel idioms: (74.82231, (68, 228), 230, 242); source e11cc71a0f3d.
- RGB565 sibling with named alphaRed and greenBlue packing: (74.82231, (68, 228), 230, 242); source 8a8f1e737bbf.
- RGB565 sibling with planar indexed luminance loads and bulk advance: (74.19835, (72, 228), 230, 242); source 9c2024664005.

## TMCJPEGDEC_converterYUV411toRGBA8edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (93.88393, (4, 56), 112, 112)
Sibling source copied locally from RGB565 corresponding MCU, replacing only format stride/stores. Target/ours full disassembly captured; target frame/count checked before trials.
- corresponding RGB565 MCU loop and channel idioms: (86.1875, (16, 91), 109, 112); source 9f297155d661.
- RGB565 sibling with named alphaRed and greenBlue packing: (86.1875, (16, 91), 109, 112); source 0272936bff38.
- RGB565 sibling with planar indexed luminance loads and bulk advance: (83.22321, (18, 100), 109, 112); source 931744d73e49.

## TMCJPEGDEC_converterYUV422toRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (87.72298, (10, 84), 148, 148)
Sibling source copied locally from RGB565 corresponding MCU, replacing only format stride/stores. Target/ours full disassembly captured; target frame/count checked before trials.
- corresponding RGB565 MCU loop and channel idioms: (82.695946, (40, 132), 142, 148); source 4c34b62e01fc.
- RGB565 sibling with named alphaRed and greenBlue packing: (82.695946, (40, 132), 142, 148); source c8cac5147cb0.
- RGB565 sibling with planar indexed luminance loads and bulk advance: (80.702705, (42, 132), 142, 148); source 1c209495e0b3.

## TMCJPEGDEC_converterYUV422toRGBA8edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (90.08849, (6, 68), 113, 113)
Sibling source copied locally from RGB565 corresponding MCU, replacing only format stride/stores. Target/ours full disassembly captured; target frame/count checked before trials.
- corresponding RGB565 MCU loop and channel idioms: (88.38938, (14, 81), 110, 113); source 6b3938bc9e73.
- RGB565 sibling with named alphaRed and greenBlue packing: (88.38938, (14, 81), 110, 113); source d8ed2545db44.
- RGB565 sibling with planar indexed luminance loads and bulk advance: (86.57522, (16, 90), 110, 113); source 7da76429384d.

## TMCJPEGDEC_converterYUV420toRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (89.40523, (16, 97), 153, 153)
Sibling source copied locally from RGB565 corresponding MCU, replacing only format stride/stores. Target/ours full disassembly captured; target frame/count checked before trials.
- corresponding RGB565 MCU loop and channel idioms: (81.22876, (40, 140), 147, 153); source 949ed7e811fc.
- RGB565 sibling with named alphaRed and greenBlue packing: (81.22876, (40, 140), 147, 153); source 987245235ef3.
- RGB565 sibling with planar indexed luminance loads and bulk advance: (78.75817, (40, 140), 147, 153); source 1f2027accd7c.

## TMCJPEGDEC_converterYUV420toRGBA8edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (87.458336, (12, 77), 120, 120)
Sibling source copied locally from RGB565 corresponding MCU, replacing only format stride/stores. Target/ours full disassembly captured; target frame/count checked before trials.
- corresponding RGB565 MCU loop and channel idioms: (79.84167, (25, 103), 117, 120); source ad063f2b63d1.
- RGB565 sibling with named alphaRed and greenBlue packing: (79.84167, (25, 103), 117, 120); source bae6e6f2f698.
- RGB565 sibling with planar indexed luminance loads and bulk advance: (78.25833, (27, 110), 117, 120); source a3c834981011.

## TMCJPEGDEC_converterYUV211toRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (91.15385, (6, 49), 104, 104)
Sibling source copied locally from RGB565 corresponding MCU, replacing only format stride/stores. Target/ours full disassembly captured; target frame/count checked before trials.
- corresponding RGB565 MCU loop and channel idioms: (86.25961, (19, 80), 101, 104); source 01fd64c61048.
- RGB565 sibling with named alphaRed and greenBlue packing: (86.25961, (19, 80), 101, 104); source 3185656dbf32.
- RGB565 sibling with planar indexed luminance loads and bulk advance: (83.71154, (29, 91), 101, 104); source cecf1e5e4806.

## TMCJPEGDEC_converterYUV211toRGBA8edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (92.0, (6, 49), 115, 115)
Sibling source copied locally from RGB565 corresponding MCU, replacing only format stride/stores. Target/ours full disassembly captured; target frame/count checked before trials.
- corresponding RGB565 MCU loop and channel idioms: (87.834785, (16, 93), 112, 115); source fa85e7a7f7a5.
- RGB565 sibling with named alphaRed and greenBlue packing: (87.834785, (16, 93), 112, 115); source 47a7f27e6e04.
- RGB565 sibling with planar indexed luminance loads and bulk advance: (85.48695, (29, 105), 112, 115); source 01fbb9341df9.

## TMCJPEGDEC_converterYUV444toRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (90.670105, (6, 46), 97, 97)
Sibling source copied locally from RGB565 corresponding MCU, replacing only format stride/stores. Target/ours full disassembly captured; target frame/count checked before trials.
- corresponding RGB565 MCU loop and channel idioms: (84.03093, (20, 85), 94, 97); source df769da06ad0.
- RGB565 sibling with named alphaRed and greenBlue packing: (84.03093, (20, 85), 94, 97); source 11130d95a6a6.
- RGB565 sibling with planar indexed luminance loads and bulk advance: (82.74227, (28, 92), 94, 97); source 4dc6c09cae71.

## TMCJPEGDEC_converterYUV444toRGBA8edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (88.90909, (8, 61), 110, 110)
Sibling source copied locally from RGB565 corresponding MCU, replacing only format stride/stores. Target/ours full disassembly captured; target frame/count checked before trials.
- corresponding RGB565 MCU loop and channel idioms: (87.57273, (14, 88), 107, 110); source 845653ff473d.
- RGB565 sibling with named alphaRed and greenBlue packing: (87.57273, (14, 88), 107, 110); source cba034dbba20.
- RGB565 sibling with planar indexed luminance loads and bulk advance: (85.84545, (16, 97), 107, 110); source 82b253c18fa3.

## TMCJPEGDEC_converterYUV411toRGB565
Origin fetch check: still baseline/open. Reference index absent. Baseline (90.599075, (21, 144), 217, 217)
Structural diagnosis: same target instruction counts/frame; sibling exact RGB565 211 and 422edge use distinct luminance local with RGB offset expressions, planar reads then advances pointer. Compare helpers and packing association before declarations.
- planar sibling indexed luminance with bulk MCU advance: (89.622116, (25, 158), 217, 217); source 759f79465b12.
- exact 211 sibling distinct luminance and widened signed chroma values: compiler failed, not counted. src/texturecvtr/Texture_MCUtoRGB565.d build/43U/src/libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565.d ### mwcceppc.exe Compiler: #    File: libs\RVLMiddleware\TMC_JPEG\src\texturecvtr\Texture_MCUtoRGB565.c # -------------------------------------------------------------------------- #     190:     u8 value;  #   Error:             ^ #   (10333) object 'value' redefined #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
- named RGB565 channel fields and target green outer sum: (90.599075, (21, 144), 217, 217); source b0ea4e85dab7.

## TMCJPEGDEC_converterYUV411toRGB565edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (95.37736, (4, 62), 106, 106)
Structural diagnosis: same target instruction counts/frame; sibling exact RGB565 211 and 422edge use distinct luminance local with RGB offset expressions, planar reads then advances pointer. Compare helpers and packing association before declarations.
- planar sibling indexed luminance with bulk MCU advance: (93.58491, (6, 77), 106, 106); source 58f9dd9f5bb7.
- exact 211 sibling distinct luminance and widened signed chroma values: compiler failed, not counted. recvtr/Texture_MCUtoRGB565.d ### mwcceppc.exe Compiler: #    File: libs\RVLMiddleware\TMC_JPEG\src\texturecvtr\Texture_MCUtoRGB565.c # -------------------------------------------------------------------------- #     265:     s8* cb = &work->convBuf[260];  #   Error:                                 ^ #   (10209) illegal implicit conversion from 'unsigned char *' to #   'signed char *' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
- named RGB565 channel fields and target green outer sum: (95.37736, (4, 62), 106, 106); source 9cc3cbb5146f.

## TMCJPEGDEC_converterYUV422toRGB565
Origin fetch check: still baseline/open. Reference index absent. Baseline (96.69118, (0, 58), 136, 136)
Structural diagnosis: same target instruction counts/frame; sibling exact RGB565 211 and 422edge use distinct luminance local with RGB offset expressions, planar reads then advances pointer. Compare helpers and packing association before declarations.
- planar sibling indexed luminance with bulk MCU advance: (91.36029, (2, 115), 136, 136); source 59931bc1f3ee.
- exact 211 sibling distinct luminance and widened signed chroma values: (96.43382, (0, 64), 136, 136); source 1f90a3b2b728.
- named RGB565 channel fields and target green outer sum: (90.661766, (16, 82), 136, 136); source 1e7b737a5d58.

## TMCJPEGDEC_converterYUV420toRGB565
Origin fetch check: still baseline/open. Reference index absent. Baseline (94.60993, (6, 86), 141, 141)
Structural diagnosis: same target instruction counts/frame; sibling exact RGB565 211 and 422edge use distinct luminance local with RGB offset expressions, planar reads then advances pointer. Compare helpers and packing association before declarations.
- planar sibling indexed luminance with bulk MCU advance: (91.489365, (8, 114), 141, 141); source 659a09cbe59b.
- exact 211 sibling distinct luminance and widened signed chroma values: unchanged, not counted.
- named RGB565 channel fields and target green outer sum: (94.60993, (6, 86), 141, 141); source 8b9be03502e9.

## TMCJPEGDEC_converterYUV420toRGB565edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (94.692986, (4, 73), 114, 114)
Structural diagnosis: same target instruction counts/frame; sibling exact RGB565 211 and 422edge use distinct luminance local with RGB offset expressions, planar reads then advances pointer. Compare helpers and packing association before declarations.
- planar sibling indexed luminance with bulk MCU advance: (92.54386, (6, 86), 114, 114); source e812bde84ff7.
- exact 211 sibling distinct luminance and widened signed chroma values: (94.429825, (4, 79), 114, 114); source 480723140fd8.
- named RGB565 channel fields and target green outer sum: (94.692986, (4, 73), 114, 114); source bcca9db05a61.

## TMCJPEGDEC_converterYUV411toRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (82.6033, (36, 153), 242, 242)
Corrected sibling converter expressions: preserve column within tile before doubling tile-column stride. Initial generator shifted whole column expression and is rejected, not counted. Sibling source copied locally from RGB565 corresponding MCU, replacing only format stride/stores. Target/ours full disassembly captured; target frame/count checked before trials.
- corresponding RGB565 MCU loop and channel idioms: (76.55785, (45, 192), 242, 242); source b3e3f26fe337.
- RGB565 sibling with named alphaRed and greenBlue packing: (76.55785, (45, 192), 242, 242); source caae455fb853.
- RGB565 sibling with planar indexed luminance loads and bulk advance: (75.40496, (46, 201), 242, 242); source 2155c589741e.

## TMCJPEGDEC_converterYUV411toRGBA8edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (93.88393, (4, 56), 112, 112)
Corrected sibling converter expressions: preserve column within tile before doubling tile-column stride. Initial generator shifted whole column expression and is rejected, not counted. Sibling source copied locally from RGB565 corresponding MCU, replacing only format stride/stores. Target/ours full disassembly captured; target frame/count checked before trials.
- corresponding RGB565 MCU loop and channel idioms: (85.42857, (15, 83), 112, 112); source db389f1e1e92.
- RGB565 sibling with named alphaRed and greenBlue packing: (85.42857, (15, 83), 112, 112); source 2b13c0f59cbc.
- RGB565 sibling with planar indexed luminance loads and bulk advance: (85.16071, (17, 91), 112, 112); source b21a9b64d9b9.

## TMCJPEGDEC_converterYUV422toRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (87.72298, (10, 84), 148, 148)
Corrected sibling converter expressions: preserve column within tile before doubling tile-column stride. Initial generator shifted whole column expression and is rejected, not counted. Sibling source copied locally from RGB565 corresponding MCU, replacing only format stride/stores. Target/ours full disassembly captured; target frame/count checked before trials.
- corresponding RGB565 MCU loop and channel idioms: (85.39189, (10, 109), 148, 148); source ee302f6040e8.
- RGB565 sibling with named alphaRed and greenBlue packing: (85.39189, (10, 109), 148, 148); source 85971d67dad2.
- RGB565 sibling with planar indexed luminance loads and bulk advance: (85.46622, (12, 120), 148, 148); source 6c9682c52127.

## TMCJPEGDEC_converterYUV422toRGBA8edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (90.08849, (6, 68), 113, 113)
Corrected sibling converter expressions: preserve column within tile before doubling tile-column stride. Initial generator shifted whole column expression and is rejected, not counted. Sibling source copied locally from RGB565 corresponding MCU, replacing only format stride/stores. Target/ours full disassembly captured; target frame/count checked before trials.
- corresponding RGB565 MCU loop and channel idioms: (89.24779, (12, 65), 113, 113); source efe793e99615.
- RGB565 sibling with named alphaRed and greenBlue packing: (89.24779, (12, 65), 113, 113); source de6ce0cb1e85.
- RGB565 sibling with planar indexed luminance loads and bulk advance: (86.185844, (15, 73), 113, 113); source 18113e98dc08.

## TMCJPEGDEC_converterYUV420toRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (89.40523, (16, 97), 153, 153)
Corrected sibling converter expressions: preserve column within tile before doubling tile-column stride. Initial generator shifted whole column expression and is rejected, not counted. Sibling source copied locally from RGB565 corresponding MCU, replacing only format stride/stores. Target/ours full disassembly captured; target frame/count checked before trials.
- corresponding RGB565 MCU loop and channel idioms: (85.052284, (22, 118), 153, 153); source 94b9768b1c48.
- RGB565 sibling with named alphaRed and greenBlue packing: (85.052284, (22, 118), 153, 153); source b62f01c0625d.
- RGB565 sibling with planar indexed luminance loads and bulk advance: (82.60131, (19, 123), 153, 153); source 55e106087217.

## TMCJPEGDEC_converterYUV420toRGBA8edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (87.458336, (12, 77), 120, 120)
Corrected sibling converter expressions: preserve column within tile before doubling tile-column stride. Initial generator shifted whole column expression and is rejected, not counted. Sibling source copied locally from RGB565 corresponding MCU, replacing only format stride/stores. Target/ours full disassembly captured; target frame/count checked before trials.
- corresponding RGB565 MCU loop and channel idioms: (88.933334, (13, 79), 120, 120); source 6e1de769e774.
- RGB565 sibling with named alphaRed and greenBlue packing: (88.933334, (13, 79), 120, 120); source 880bdda5a207.
- RGB565 sibling with planar indexed luminance loads and bulk advance: (86.14167, (15, 91), 120, 120); source 3491e392cb78.

## TMCJPEGDEC_converterYUV211toRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (91.15385, (6, 49), 104, 104)
Corrected sibling converter expressions: preserve column within tile before doubling tile-column stride. Initial generator shifted whole column expression and is rejected, not counted. Sibling source copied locally from RGB565 corresponding MCU, replacing only format stride/stores. Target/ours full disassembly captured; target frame/count checked before trials.
- corresponding RGB565 MCU loop and channel idioms: (84.63461, (14, 78), 104, 104); source c50f5313796f.
- RGB565 sibling with named alphaRed and greenBlue packing: (84.63461, (14, 78), 104, 104); source b4b4d299b403.
- RGB565 sibling with planar indexed luminance loads and bulk advance: (85.65385, (18, 87), 104, 104); source fab9e531bf31.

## TMCJPEGDEC_converterYUV211toRGBA8edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (92.0, (6, 49), 115, 115)
Corrected sibling converter expressions: preserve column within tile before doubling tile-column stride. Initial generator shifted whole column expression and is rejected, not counted. Sibling source copied locally from RGB565 corresponding MCU, replacing only format stride/stores. Target/ours full disassembly captured; target frame/count checked before trials.
- corresponding RGB565 MCU loop and channel idioms: (89.478264, (12, 64), 115, 115); source 46db31c436af.
- RGB565 sibling with named alphaRed and greenBlue packing: (89.478264, (12, 64), 115, 115); source f8bafa30bcd8.
- RGB565 sibling with planar indexed luminance loads and bulk advance: (86.46957, (15, 72), 115, 115); source 99fc20046713.

## TMCJPEGDEC_converterYUV444toRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (90.670105, (6, 46), 97, 97)
Corrected sibling converter expressions: preserve column within tile before doubling tile-column stride. Initial generator shifted whole column expression and is rejected, not counted. Sibling source copied locally from RGB565 corresponding MCU, replacing only format stride/stores. Target/ours full disassembly captured; target frame/count checked before trials.
- corresponding RGB565 MCU loop and channel idioms: (85.06186, (16, 61), 97, 97); source f16f0334a945.
- RGB565 sibling with named alphaRed and greenBlue packing: (85.06186, (16, 61), 97, 97); source 6e33b3221c26.
- RGB565 sibling with planar indexed luminance loads and bulk advance: (83.18557, (22, 70), 97, 97); source 0e8544494bfe.

## TMCJPEGDEC_converterYUV444toRGBA8edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (88.90909, (8, 61), 110, 110)
Corrected sibling converter expressions: preserve column within tile before doubling tile-column stride. Initial generator shifted whole column expression and is rejected, not counted. Sibling source copied locally from RGB565 corresponding MCU, replacing only format stride/stores. Target/ours full disassembly captured; target frame/count checked before trials.
- corresponding RGB565 MCU loop and channel idioms: (89.13636, (12, 61), 110, 110); source 638a028f02ef.
- RGB565 sibling with named alphaRed and greenBlue packing: (89.13636, (12, 61), 110, 110); source 970dd847e40a.
- RGB565 sibling with planar indexed luminance loads and bulk advance: (85.990906, (15, 69), 110, 110); source 1b1049be75ce.

RGB565 444 target color calculation and packing structure now identical with blue sample ownership and green outer sum. Declaration search follows structural trials, limited to this candidate.
RGB565 444 declsearch 400 builds, best structural/exact (0,28), no gain; restored original 98.71429% source.

## TMCJPEGDEC_converterYUV411toRGB565
Origin fetch check: still baseline/open. Reference index absent. Baseline (90.599075, (21, 144), 217, 217)
Structural diagnosis: same target instruction counts/frame; sibling exact RGB565 211 and 422edge use distinct luminance local with RGB offset expressions, planar reads then advances pointer. Compare helpers and packing association before declarations.
- exact 211 sibling distinct luminance and widened signed chroma values: unchanged, not counted.

## TMCJPEGDEC_converterYUV411toRGB565edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (95.37736, (4, 62), 106, 106)
Structural diagnosis: same target instruction counts/frame; sibling exact RGB565 211 and 422edge use distinct luminance local with RGB offset expressions, planar reads then advances pointer. Compare helpers and packing association before declarations.
- exact 211 sibling distinct luminance and widened signed chroma values: (95.09434, (4, 68), 106, 106); source 082e8fcbd8f1.

## TMCJPEGDEC_converterYUV422toRGB565
Origin fetch check: still baseline/open. Reference index absent. Baseline (96.69118, (0, 58), 136, 136)
Structural diagnosis: same target instruction counts/frame; sibling exact RGB565 211 and 422edge use distinct luminance local with RGB offset expressions, planar reads then advances pointer. Compare helpers and packing association before declarations.
- exact 211 sibling distinct luminance and widened signed chroma values: (96.43382, (0, 64), 136, 136); source 1f90a3b2b728.

## TMCJPEGDEC_converterYUV420toRGB565
Origin fetch check: still baseline/open. Reference index absent. Baseline (94.60993, (6, 86), 141, 141)
Structural diagnosis: same target instruction counts/frame; sibling exact RGB565 211 and 422edge use distinct luminance local with RGB offset expressions, planar reads then advances pointer. Compare helpers and packing association before declarations.
- exact 211 sibling distinct luminance and widened signed chroma values: unchanged, not counted.

## TMCJPEGDEC_converterYUV420toRGB565edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (94.692986, (4, 73), 114, 114)
Structural diagnosis: same target instruction counts/frame; sibling exact RGB565 211 and 422edge use distinct luminance local with RGB offset expressions, planar reads then advances pointer. Compare helpers and packing association before declarations.
- exact 211 sibling distinct luminance and widened signed chroma values: (94.429825, (4, 79), 114, 114); source 480723140fd8.

## TMCJPEGDEC_converterYUV444toRGB565
Origin fetch check: still baseline/open. Reference index absent. Baseline (98.71429, (6, 13), 91, 91)
- inline YCbCr pixel helper with target sample evaluation order: (87.95605, (8, 70), 91, 91); source 78d531ed643c.
- inline pixel helper using unsigned luminance argument: (87.18681, (8, 71), 91, 91); source 78d531ed643c.
- inline pixel helper scoped channel declarations in calculation order: (93.2967, (0, 70), 91, 91); source 78d531ed643c.

## TMCJPEGDEC_converterYUV411toRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (82.6033, (36, 153), 242, 242)
After sibling comparison, isolate RGBA8 packing boundary: target narrows channels before stores, creates a shared tile-column index then red tile and green/blue tile at +16 halfwords. Baseline preserves loop and arithmetic; no register search until this structural pass.
- explicit byte channel narrowing before AR and GB stores: unchanged, not counted.
- single texel index shared by AR and GB output tiles: (74.859505, (62, 212), 228, 242); source 1d4ee5677a33.
- byte locals describe clamped color channels at packing boundary: unchanged, not counted.

## TMCJPEGDEC_converterYUV411toRGBA8edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (93.88393, (4, 56), 112, 112)
After sibling comparison, isolate RGBA8 packing boundary: target narrows channels before stores, creates a shared tile-column index then red tile and green/blue tile at +16 halfwords. Baseline preserves loop and arithmetic; no register search until this structural pass.
- explicit byte channel narrowing before AR and GB stores: unchanged, not counted.
- single texel index shared by AR and GB output tiles: (90.85714, (14, 66), 109, 112); source 700d8e20b078.
- byte locals describe clamped color channels at packing boundary: unchanged, not counted.

## TMCJPEGDEC_converterYUV422toRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (87.72298, (10, 84), 148, 148)
After sibling comparison, isolate RGBA8 packing boundary: target narrows channels before stores, creates a shared tile-column index then red tile and green/blue tile at +16 halfwords. Baseline preserves loop and arithmetic; no register search until this structural pass.
- explicit byte channel narrowing before AR and GB stores: (83.13513, (21, 116), 148, 148); source 5d39db82d45f.
- single texel index shared by AR and GB output tiles: (82.98649, (30, 123), 141, 148); source f61f83500766.
- byte locals describe clamped color channels at packing boundary: (87.72298, (10, 84), 148, 148); source 4b718a31079c.

## TMCJPEGDEC_converterYUV422toRGBA8edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (90.08849, (6, 68), 113, 113)
After sibling comparison, isolate RGBA8 packing boundary: target narrows channels before stores, creates a shared tile-column index then red tile and green/blue tile at +16 halfwords. Baseline preserves loop and arithmetic; no register search until this structural pass.
- explicit byte channel narrowing before AR and GB stores: (85.76991, (19, 72), 113, 113); source 4efce886d1f9.
- single texel index shared by AR and GB output tiles: (86.57522, (16, 79), 110, 113); source f79a94abeebf.
- byte locals describe clamped color channels at packing boundary: (90.08849, (6, 68), 113, 113); source 1614f2d29c37.

## TMCJPEGDEC_converterYUV420toRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (89.40523, (16, 97), 153, 153)
After sibling comparison, isolate RGBA8 packing boundary: target narrows channels before stores, creates a shared tile-column index then red tile and green/blue tile at +16 halfwords. Baseline preserves loop and arithmetic; no register search until this structural pass.
- explicit byte channel narrowing before AR and GB stores: (84.13725, (25, 124), 153, 153); source 81a4905b87d6.
- single texel index shared by AR and GB output tiles: (82.888885, (30, 137), 146, 153); source 98d05c4408d5.
- byte locals describe clamped color channels at packing boundary: (89.40523, (16, 97), 153, 153); source dd466b834738.

## TMCJPEGDEC_converterYUV420toRGBA8edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (87.458336, (12, 77), 120, 120)
After sibling comparison, isolate RGBA8 packing boundary: target narrows channels before stores, creates a shared tile-column index then red tile and green/blue tile at +16 halfwords. Baseline preserves loop and arithmetic; no register search until this structural pass.
- explicit byte channel narrowing before AR and GB stores: (84.75, (19, 88), 120, 120); source 69e34a093227.
- single texel index shared by AR and GB output tiles: (82.0, (35, 99), 116, 120); source 51fab74e5b1c.
- byte locals describe clamped color channels at packing boundary: (87.458336, (12, 77), 120, 120); source d0df449ea505.

## TMCJPEGDEC_converterYUV211toRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (91.15385, (6, 49), 104, 104)
After sibling comparison, isolate RGBA8 packing boundary: target narrows channels before stores, creates a shared tile-column index then red tile and green/blue tile at +16 halfwords. Baseline preserves loop and arithmetic; no register search until this structural pass.
- explicit byte channel narrowing before AR and GB stores: (84.84615, (15, 62), 104, 104); source 9b792deb6ace.
- single texel index shared by AR and GB output tiles: (82.89423, (19, 94), 101, 104); source a2b37cb779e7.
- byte locals describe clamped color channels at packing boundary: (91.15385, (6, 49), 104, 104); source 8f7646c953ed.

## TMCJPEGDEC_converterYUV211toRGBA8edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (92.0, (6, 49), 115, 115)
After sibling comparison, isolate RGBA8 packing boundary: target narrows channels before stores, creates a shared tile-column index then red tile and green/blue tile at +16 halfwords. Baseline preserves loop and arithmetic; no register search until this structural pass.
- explicit byte channel narrowing before AR and GB stores: (86.90435, (15, 59), 115, 115); source ff343c912284.
- single texel index shared by AR and GB output tiles: (84.4, (19, 99), 112, 115); source 4613f3801cc1.
- byte locals describe clamped color channels at packing boundary: (92.0, (6, 49), 115, 115); source bb20cb61a8d9.

## TMCJPEGDEC_converterYUV444toRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (90.670105, (6, 46), 97, 97)
After sibling comparison, isolate RGBA8 packing boundary: target narrows channels before stores, creates a shared tile-column index then red tile and green/blue tile at +16 halfwords. Baseline preserves loop and arithmetic; no register search until this structural pass.
- explicit byte channel narrowing before AR and GB stores: (83.90722, (15, 59), 97, 97); source af0bd9f770d6.
- single texel index shared by AR and GB output tiles: (82.453606, (17, 86), 94, 97); source 14d0d2d769b1.
- byte locals describe clamped color channels at packing boundary: (90.670105, (6, 46), 97, 97); source 8d03b701fa55.

## TMCJPEGDEC_converterYUV444toRGBA8edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (88.90909, (8, 61), 110, 110)
After sibling comparison, isolate RGBA8 packing boundary: target narrows channels before stores, creates a shared tile-column index then red tile and green/blue tile at +16 halfwords. Baseline preserves loop and arithmetic; no register search until this structural pass.
- explicit byte channel narrowing before AR and GB stores: unchanged, not counted.
- single texel index shared by AR and GB output tiles: (81.84545, (24, 81), 107, 110); source 3b6c22ac223f.
- byte locals describe clamped color channels at packing boundary: unchanged, not counted.

## TMCJPEGDEC_converterYUV411toRGB565
Origin fetch check: still baseline/open. Reference index absent. Baseline (90.599075, (21, 144), 217, 217)
New boundary trial: declaration initialization and local scope, after sibling/control/data checks. C declaration permutations alone were inert, so change real input and row lifetimes.
- contiguous initialized MCU input and output metadata locals: (88.67742, (23, 160), 217, 217); source f79f51a4ce95.
- row output and tile coordinates declared at row scope: (89.308754, (21, 162), 217, 217); source 8094ec3a3d62.
- pixel luminance and channels initialized within pixel scope: (87.622116, (25, 162), 217, 217); source ee7d356404d5.

## TMCJPEGDEC_converterYUV411toRGB565edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (95.37736, (4, 62), 106, 106)
New boundary trial: declaration initialization and local scope, after sibling/control/data checks. C declaration permutations alone were inert, so change real input and row lifetimes.
- contiguous initialized MCU input and output metadata locals: unchanged, not counted.
- row output and tile coordinates declared at row scope: unchanged, not counted.
- pixel luminance and channels initialized within pixel scope: unchanged, not counted.

## TMCJPEGDEC_converterYUV422toRGB565
Origin fetch check: still baseline/open. Reference index absent. Baseline (96.69118, (0, 58), 136, 136)
New boundary trial: declaration initialization and local scope, after sibling/control/data checks. C declaration permutations alone were inert, so change real input and row lifetimes.
- contiguous initialized MCU input and output metadata locals: (92.81618, (2, 97), 136, 136); source 0108228d0330.
- row output and tile coordinates declared at row scope: (94.632355, (0, 91), 136, 136); source 54d1ae867262.
- pixel luminance and channels initialized within pixel scope: (91.58088, (4, 91), 136, 136); source 3e51610873ed.

## TMCJPEGDEC_converterYUV420toRGB565
Origin fetch check: still baseline/open. Reference index absent. Baseline (94.60993, (6, 86), 141, 141)
New boundary trial: declaration initialization and local scope, after sibling/control/data checks. C declaration permutations alone were inert, so change real input and row lifetimes.
- contiguous initialized MCU input and output metadata locals: (90.22695, (11, 107), 141, 141); source 883b29568db2.
- row output and tile coordinates declared at row scope: compiler failed, not counted. d/43U/src/libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565.d ### mwcceppc.exe Compiler: #    File: libs\RVLMiddleware\TMC_JPEG\src\texturecvtr\Texture_MCUtoRGB565.c # -------------------------------------------------------------------------- #     511:             tileRow = (y >> 2) * tileWidth;  #   Error:             ^^^^^^^ #   (10140) undefined identifier 'tileRow' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
- pixel luminance and channels initialized within pixel scope: (92.3688, (8, 96), 141, 141); source 8122b6b24890.

## TMCJPEGDEC_converterYUV420toRGB565edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (94.692986, (4, 73), 114, 114)
New boundary trial: declaration initialization and local scope, after sibling/control/data checks. C declaration permutations alone were inert, so change real input and row lifetimes.
- contiguous initialized MCU input and output metadata locals: (85.26316, (10, 77), 114, 114); source 1fb0df3df095.
- row output and tile coordinates declared at row scope: (88.02631, (10, 86), 114, 114); source a66f40019d30.
- pixel luminance and channels initialized within pixel scope: (95.70175, (4, 64), 114, 114); source 7a3306693cd2.

## TMCJPEGDEC_converterYUV444toRGB565
Origin fetch check: still baseline/open. Reference index absent. Baseline (98.71429, (6, 13), 91, 91)
New boundary trial: declaration initialization and local scope, after sibling/control/data checks. C declaration permutations alone were inert, so change real input and row lifetimes.
- contiguous initialized MCU input and output metadata locals: (94.86813, (6, 59), 91, 91); source 11fc37395d18.
- row output and tile coordinates declared at row scope: (92.39561, (8, 60), 91, 91); source 3196ca9de943.
- pixel luminance and channels initialized within pixel scope: (99.31868, (2, 10), 91, 91); source 3045865f1926.

## TMCJPEGDEC_converterYUV411toRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (82.6033, (36, 153), 242, 242)
New boundary trial: declaration initialization and local scope, after sibling/control/data checks. C declaration permutations alone were inert, so change real input and row lifetimes.
- contiguous initialized MCU input and output metadata locals: (77.89256, (45, 180), 242, 242); source 883bfb6758ad.
- row output and tile coordinates declared at row scope: compiler failed, not counted. c/libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8.d ### mwcceppc.exe Compiler: #    File: libs\RVLMiddleware\TMC_JPEG\src\texturecvtr\Texture_MCUtoRGBA8.c # ------------------------------------------------------------------------- #     207:             output = (u16*)(texture + ((row & 3) << 3));  #   Error:             ^^^^^^ #   (10140) undefined identifier 'output' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
- pixel luminance and channels initialized within pixel scope: (72.3843, (57, 202), 242, 242); source 25a8dbb7f0f8.

## TMCJPEGDEC_converterYUV411toRGBA8edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (93.88393, (4, 56), 112, 112)
New boundary trial: declaration initialization and local scope, after sibling/control/data checks. C declaration permutations alone were inert, so change real input and row lifetimes.
- contiguous initialized MCU input and output metadata locals: (88.65179, (6, 72), 112, 112); source 542e62aab9cb.
- row output and tile coordinates declared at row scope: (90.3125, (6, 72), 112, 112); source 6013ff48fe5f.
- pixel luminance and channels initialized within pixel scope: (93.88393, (4, 56), 112, 112); source 858d0df9f817.

## TMCJPEGDEC_converterYUV422toRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (87.72298, (10, 84), 148, 148)
New boundary trial: declaration initialization and local scope, after sibling/control/data checks. C declaration permutations alone were inert, so change real input and row lifetimes.
- contiguous initialized MCU input and output metadata locals: (82.0, (14, 119), 148, 148); source 7b10cf17dc41.
- row output and tile coordinates declared at row scope: (84.64865, (10, 118), 148, 148); source 9370f14f81e6.
- pixel luminance and channels initialized within pixel scope: (87.72298, (10, 84), 148, 148); source ce0b4ae259e7.

## TMCJPEGDEC_converterYUV422toRGBA8edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (90.08849, (6, 68), 113, 113)
New boundary trial: declaration initialization and local scope, after sibling/control/data checks. C declaration permutations alone were inert, so change real input and row lifetimes.
- contiguous initialized MCU input and output metadata locals: (83.31858, (8, 78), 113, 113); source bf97302c5ede.
- row output and tile coordinates declared at row scope: (87.78761, (6, 86), 113, 113); source 1eebb0779fd8.
- pixel luminance and channels initialized within pixel scope: (87.831856, (12, 84), 113, 113); source 4142970d76b7.

## TMCJPEGDEC_converterYUV420toRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (89.40523, (16, 97), 153, 153)
New boundary trial: declaration initialization and local scope, after sibling/control/data checks. C declaration permutations alone were inert, so change real input and row lifetimes.
- contiguous initialized MCU input and output metadata locals: (86.61438, (18, 114), 153, 153); source b41795663576.
- row output and tile coordinates declared at row scope: compiler failed, not counted. src/libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8.d ### mwcceppc.exe Compiler: #    File: libs\RVLMiddleware\TMC_JPEG\src\texturecvtr\Texture_MCUtoRGBA8.c # ------------------------------------------------------------------------- #     557:             output = (u16*)(texture + ((y & 3) << 3));  #   Error:             ^^^^^^ #   (10140) undefined identifier 'output' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
- pixel luminance and channels initialized within pixel scope: compiler failed, not counted. rc/libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8.d ### mwcceppc.exe Compiler: #    File: libs\RVLMiddleware\TMC_JPEG\src\texturecvtr\Texture_MCUtoRGBA8.c # ------------------------------------------------------------------------- #     570:                         s32 red = value + redOffset;  #   Error:                         ^^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 

## TMCJPEGDEC_converterYUV420toRGBA8edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (87.458336, (12, 77), 120, 120)
New boundary trial: declaration initialization and local scope, after sibling/control/data checks. C declaration permutations alone were inert, so change real input and row lifetimes.
- contiguous initialized MCU input and output metadata locals: unchanged, not counted.
- row output and tile coordinates declared at row scope: unchanged, not counted.
- pixel luminance and channels initialized within pixel scope: unchanged, not counted.

## TMCJPEGDEC_converterYUV211toRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (91.15385, (6, 49), 104, 104)
New boundary trial: declaration initialization and local scope, after sibling/control/data checks. C declaration permutations alone were inert, so change real input and row lifetimes.
- contiguous initialized MCU input and output metadata locals: (82.51923, (14, 82), 104, 104); source 3f910c53f315.
- row output and tile coordinates declared at row scope: compiler failed, not counted. uild/43U/src/libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8.d ### mwcceppc.exe Compiler: #    File: libs\RVLMiddleware\TMC_JPEG\src\texturecvtr\Texture_MCUtoRGBA8.c # ------------------------------------------------------------------------- #     725:             tileRow = (y >> 2) * tileWidth;  #   Error:             ^^^^^^^ #   (10140) undefined identifier 'tileRow' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
- pixel luminance and channels initialized within pixel scope: (86.57692, (18, 61), 104, 104); source 12ac89e32c75.

## TMCJPEGDEC_converterYUV211toRGBA8edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (92.0, (6, 49), 115, 115)
New boundary trial: declaration initialization and local scope, after sibling/control/data checks. C declaration permutations alone were inert, so change real input and row lifetimes.
- contiguous initialized MCU input and output metadata locals: (84.26087, (8, 75), 115, 115); source d5a88f2a245b.
- row output and tile coordinates declared at row scope: compiler failed, not counted. uild/43U/src/libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8.d ### mwcceppc.exe Compiler: #    File: libs\RVLMiddleware\TMC_JPEG\src\texturecvtr\Texture_MCUtoRGBA8.c # ------------------------------------------------------------------------- #     815:             tileRow = (y >> 2) * tileWidth;  #   Error:             ^^^^^^^ #   (10140) undefined identifier 'tileRow' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
- pixel luminance and channels initialized within pixel scope: (85.73044, (18, 84), 115, 115); source e7fb76871cc6.

## TMCJPEGDEC_converterYUV444toRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (90.670105, (6, 46), 97, 97)
New boundary trial: declaration initialization and local scope, after sibling/control/data checks. C declaration permutations alone were inert, so change real input and row lifetimes.
- contiguous initialized MCU input and output metadata locals: (80.71134, (13, 72), 97, 97); source ed3807019cda.
- row output and tile coordinates declared at row scope: (84.68041, (10, 78), 97, 97); source dd9e76e4b64f.
- pixel luminance and channels initialized within pixel scope: (85.78351, (16, 56), 97, 97); source b53542b95323.

## TMCJPEGDEC_converterYUV444toRGBA8edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (88.90909, (8, 61), 110, 110)
New boundary trial: declaration initialization and local scope, after sibling/control/data checks. C declaration permutations alone were inert, so change real input and row lifetimes.
- contiguous initialized MCU input and output metadata locals: (84.09091, (10, 74), 110, 110); source 29cfdedf2713.
- row output and tile coordinates declared at row scope: (86.954544, (8, 83), 110, 110); source 0a5681923d7f.
- pixel luminance and channels initialized within pixel scope: (87.045456, (14, 74), 110, 110); source d9011c3a4ed8.

RGB565444 scoped pixel reached 99.31868%, 91/91 instructions, 10 differences. Remaining two multiply order choices and luminance destination ownership. Test original-looking scoped pixel channel definitions.
- scoped blue luminance then green and red channels: (98.68132, (4, 14), 91, 91); source 4dc60099342c.
- scoped independent value then RGB channels: (99.89011, (0, 1), 91, 91); source dc25faf87b2b.
- scoped blue with target channel overflow operands: (98.62637, (4, 15), 91, 91); source e14fc84dc985.
Scoped independent luminance reaches 99.89011%; target structural score 0 and one operand difference. Candidate restored for focused final operand diagnosis.
- scoped independent luminance and blue red green overflow test: (99.83517, (0, 2), 91, 91); source 07b24558fb06.
- scoped independent color range check red | green | blue: (100.0, (0, 0), 91, 91); source 2eacd0560691.
Exact candidate retained for independent gate; no commit yet.

## Accepted exact RGB565444
TMCJPEGDEC_converterYUV444toRGB565 98.71429% -> 100.0%, 91/91 instructions, ctxdiff diffs 0. Full clean all-three-unit gate PASS; unchanged DOL target SHA1, regressions/forbidden/readability 0. Code 2284 -> 2648/6184; instruction-exact 6 -> 7/13. Retained pixel scope, distinct luminance, green then red then blue expressions and red/green/blue overflow operands.

full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] objdiff: code 660/6596 data None/None functions 2/13 fuzzy 90.3232 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   section .text size 6596 match 90.32323
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_set_converterRGBA8 93.91765
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8 82.6033
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8edge 93.88393
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8 87.72298
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8edge 90.08849
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8 89.40523
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8edge 87.458336
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8 91.15385
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8edge 92.0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8 90.670105
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8edge 88.90909
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] baseline: code 660/6596 data None functions 2 fuzzy 90.3232
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] objdiff: code 2648/6184 data None/None functions 7/13 fuzzy 96.5207 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] instruction-exact functions: 7/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   section .text size 6184 match 96.5207
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_set_converterRGB565 93.91765
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565 90.599075
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565edge 95.37736
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565 96.69118
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565 94.60993
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565edge 94.692986
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] baseline: code 2284/6184 data None functions 6 fuzzy 96.4450
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] objdiff: code 15164/15948 data None/None functions 12/13 fuzzy 99.6453 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   section .text size 15948 match 99.64535
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEGDEC_set_converterY8U8V8 92.78571
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] baseline: code 15164/15948 data None functions 12 fuzzy 99.6453
regressions vs baseline: 0
global matched_code_percent: 91.58086 -> 91.59302
global fuzzy_match_percent: 99.70061 -> 99.70077
global complete_code_percent: 74.74593 -> 74.74593
global matched_data_percent: 99.77803 -> 99.77803
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS

## TMCJPEGDEC_converterYUV444toRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (90.670105, (6, 46), 97, 97)
New exact donor: RGB565444 now byte and instruction exact. Port its scoped luminance and channel idioms to RGBA8 before further work.
- new exact RGB565444 pixel scope port: (85.47423, (16, 58), 97, 97); source 9b59c76c33d8.
- new exact RGB565444 scope with named RGBA8 packing: (85.47423, (16, 58), 97, 97); source a5a3c27db79e.
- new exact RGB565444 scope with planar indexed samples: (83.69072, (18, 69), 97, 97); source 5d22fa74b85d.

## TMCJPEGDEC_converterYUV411toRGB565
Origin fetch check: still baseline/open. Reference index absent. Baseline (90.599075, (21, 144), 217, 217)
Exact RGB565444 donor pixel shape: independent initialized luminance, scoped green/red/blue temporaries, shared chroma outside pixel, red/green/blue range test. Apply to this MCU while keeping its proven row/column/pointer stepping.
- exact RGB565444 independent scoped pixel template: (87.9447, (25, 161), 217, 217); source 54bc1eb238f5.
- exact RGB565444 scoped template with byte luminance input: (84.4424, (42, 162), 217, 217); source a49f70599e1a.

## TMCJPEGDEC_converterYUV411toRGB565edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (95.37736, (4, 62), 106, 106)
Exact RGB565444 donor pixel shape: independent initialized luminance, scoped green/red/blue temporaries, shared chroma outside pixel, red/green/blue range test. Apply to this MCU while keeping its proven row/column/pointer stepping.
- exact RGB565444 independent scoped pixel template: (95.28302, (4, 63), 106, 106); source 707515bac55b.
- exact RGB565444 scoped template with byte luminance input: (95.28302, (4, 63), 106, 106); source d4798ff95c45.

## TMCJPEGDEC_converterYUV422toRGB565
Origin fetch check: still baseline/open. Reference index absent. Baseline (96.69118, (0, 58), 136, 136)
Exact RGB565444 donor pixel shape: independent initialized luminance, scoped green/red/blue temporaries, shared chroma outside pixel, red/green/blue range test. Apply to this MCU while keeping its proven row/column/pointer stepping.
- exact RGB565444 independent scoped pixel template: (89.44853, (6, 99), 136, 136); source caf68980868d.
- exact RGB565444 scoped template with byte luminance input: (91.10294, (4, 92), 136, 136); source 74d37039aca8.

## TMCJPEGDEC_converterYUV420toRGB565
Origin fetch check: still baseline/open. Reference index absent. Baseline (94.60993, (6, 86), 141, 141)
Exact RGB565444 donor pixel shape: independent initialized luminance, scoped green/red/blue temporaries, shared chroma outside pixel, red/green/blue range test. Apply to this MCU while keeping its proven row/column/pointer stepping.
- exact RGB565444 independent scoped pixel template: (92.049644, (8, 103), 141, 141); source 1c733f91fe02.
- exact RGB565444 scoped template with byte luminance input: (90.38298, (10, 103), 141, 141); source f228da2a14ef.

## TMCJPEGDEC_converterYUV420toRGB565edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (94.692986, (4, 73), 114, 114)
Exact RGB565444 donor pixel shape: independent initialized luminance, scoped green/red/blue temporaries, shared chroma outside pixel, red/green/blue range test. Apply to this MCU while keeping its proven row/column/pointer stepping.
- exact RGB565444 independent scoped pixel template: (96.00877, (4, 61), 114, 114); source 5fd30949ab98.
- exact RGB565444 scoped template with byte luminance input: (96.00877, (4, 61), 114, 114); source daeeb99a8bc4.

## TMCJPEGDEC_converterYUV411toRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (82.6033, (36, 153), 242, 242)
Exact RGB565444 donor pixel shape: independent initialized luminance, scoped green/red/blue temporaries, shared chroma outside pixel, red/green/blue range test. Apply to this MCU while keeping its proven row/column/pointer stepping.

## TMCJPEGDEC_converterYUV411toRGBA8
Origin fetch check: still baseline/open. Reference index absent. Baseline (82.6033, (36, 153), 242, 242)
Exact RGB565444 donor pixel shape: independent initialized luminance, scoped green/red/blue temporaries, shared chroma outside pixel, red/green/blue range test. Apply to this MCU while keeping its proven row/column/pointer stepping.
- exact RGB565444 independent scoped pixel template: (73.74793, (47, 202), 242, 242); source 5c4c86f88c2f.
- exact RGB565444 scoped template with byte luminance input: (72.3843, (57, 202), 242, 242); source 0ec3cc0701f8.

## TMCJPEGDEC_converterYUV411toRGBA8edge
Origin fetch check: still baseline/open. Reference index absent. Baseline (93.88393, (4, 56), 112, 112)
Exact RGB565444 donor pixel shape: independent initialized luminance, scoped green/red/blue temporaries, shared chroma outside pixel, red/green/blue range test. Apply to this MCU while keeping its proven row/column/pointer stepping.

## Final ownership and completeness audit
No new fuzzy-only source changes retained. Only the new exact RGB565444 pixel scope remains. All failed or non-exact candidates restored. No headers, symbol extents, linking flags, force-active data, or other translation units changed.
Initial RGBA8 sibling generator wrongly grouped the within-tile column into the left shift. Those initial trials are rejected and excluded from completeness; the corrected generator preserved the column remainder. Compiler failures and unchanged variants are excluded. No generator failures affected the retained source.

RGBA8: objdiff exact 2 -> 2/13; code 660 -> 660/6596; data 0 -> 0/0.
Open TMCJPEGDEC_set_converterRGBA8 93.91765%; instructions 169/170; structural/exact differences (36, 169); 3 distinct valid source variants; shared conversion-buffer base folds into case addresses; dimension/store scheduling.
Open TMCJPEGDEC_converterYUV411toRGBA8 82.6033%; instructions 242/242; structural/exact differences (36, 153); 8 distinct valid source variants; channel/output scheduling and live temporary ownership.
Open TMCJPEGDEC_converterYUV411toRGBA8edge 93.88393%; instructions 112/112; structural/exact differences (4, 56); 7 distinct valid source variants; channel/output scheduling and live temporary ownership.
Open TMCJPEGDEC_converterYUV422toRGBA8 87.72298%; instructions 148/148; structural/exact differences (10, 84); 9 distinct valid source variants; channel/output scheduling and live temporary ownership.
Open TMCJPEGDEC_converterYUV422toRGBA8edge 90.08849%; instructions 113/113; structural/exact differences (6, 68); 9 distinct valid source variants; channel/output scheduling and live temporary ownership.
Open TMCJPEGDEC_converterYUV420toRGBA8 89.40523%; instructions 153/153; structural/exact differences (16, 97); 7 distinct valid source variants; channel/output scheduling and live temporary ownership.
Open TMCJPEGDEC_converterYUV420toRGBA8edge 87.458336%; instructions 120/120; structural/exact differences (12, 77); 6 distinct valid source variants; channel/output scheduling and live temporary ownership.
Open TMCJPEGDEC_converterYUV211toRGBA8 91.15385%; instructions 104/104; structural/exact differences (6, 49); 8 distinct valid source variants; channel/output scheduling and live temporary ownership.
Open TMCJPEGDEC_converterYUV211toRGBA8edge 92.0%; instructions 115/115; structural/exact differences (6, 49); 8 distinct valid source variants; channel/output scheduling and live temporary ownership.
Open TMCJPEGDEC_converterYUV444toRGBA8 90.670105%; instructions 97/97; structural/exact differences (6, 46); 12 distinct valid source variants; channel/output scheduling and live temporary ownership.
Open TMCJPEGDEC_converterYUV444toRGBA8edge 88.90909%; instructions 110/110; structural/exact differences (8, 61); 12 distinct valid source variants; channel/output scheduling and live temporary ownership.
RGB565: objdiff exact 6 -> 7/13; code 2284 -> 2648/6184; data 0 -> 0/0.
Open TMCJPEGDEC_set_converterRGB565 93.91765%; instructions 169/170; structural/exact differences (36, 169); 3 distinct valid source variants; shared conversion-buffer base folds into case addresses; dimension/store scheduling.
Open TMCJPEGDEC_converterYUV411toRGB565 90.599075%; instructions 217/217; structural/exact differences (21, 144); 7 distinct valid source variants; channel/output scheduling and live temporary ownership.
Open TMCJPEGDEC_converterYUV411toRGB565edge 95.37736%; instructions 106/106; structural/exact differences (4, 62); 5 distinct valid source variants; channel/output scheduling and live temporary ownership.
Open TMCJPEGDEC_converterYUV422toRGB565 96.69118%; instructions 136/136; structural/exact differences (0, 58); 8 distinct valid source variants; register allocation only.
Open TMCJPEGDEC_converterYUV420toRGB565 94.60993%; instructions 141/141; structural/exact differences (6, 86); 6 distinct valid source variants; channel/output scheduling and live temporary ownership.
Open TMCJPEGDEC_converterYUV420toRGB565edge 94.692986%; instructions 114/114; structural/exact differences (4, 73); 8 distinct valid source variants; channel/output scheduling and live temporary ownership.
Y8U8V8: objdiff exact 12 -> 12/13; code 15164 -> 15164/15948; data 0 -> 0/0.
Open TMCJPEGDEC_set_converterY8U8V8 92.78571%; instructions 195/196; structural/exact differences (41, 195); 3 distinct valid source variants; shared conversion-buffer base folds into case addresses; dimension/store scheduling.

Y8U8V8 gate discrepancy independently verified: all twelve converter functions have byte-identical entire function bodies in source and original objects, totalling 15164 bytes. gate.py prints instruction-exact 2/13 because odiff.dis mistakes the explicit condition-register operand for the target of conditional branches. No gate/tool changes made. Objdiff 12/13 is correct; setup remains non-exact.

All owned target extents checked: no overlap, no allocated data beyond text, no possible data rename/extent fix. All eighteen remaining functions have at least three distinct valid compiled source attempts this run. Source patch reviewed: scoped initialized value and channel calculations, no new comments or prohibited patterns.


Gate instruction-count evidence TMCJPEG_814EFEAC: raw function bytes identical; offsets 0x30c / 0x310; odiff first differences [(161, ('bge', -1411), ('bge', -1415)), (169, ('bgt', -1443), ('bgt', -1447))].

## Final full clean gate
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] objdiff: code 660/6596 data None/None functions 2/13 fuzzy 90.3232 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   section .text size 6596 match 90.32323
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_set_converterRGBA8 93.91765
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8 82.6033
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV411toRGBA8edge 93.88393
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8 87.72298
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV422toRGBA8edge 90.08849
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8 89.40523
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV420toRGBA8edge 87.458336
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8 91.15385
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV211toRGBA8edge 92.0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8 90.670105
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8]   below 100: TMCJPEGDEC_converterYUV444toRGBA8edge 88.90909
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8] baseline: code 660/6596 data None functions 2 fuzzy 90.3232
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] objdiff: code 2648/6184 data None/None functions 7/13 fuzzy 96.5207 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] instruction-exact functions: 7/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   section .text size 6184 match 96.5207
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_set_converterRGB565 93.91765
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565 90.599075
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV411toRGB565edge 95.37736
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV422toRGB565 96.69118
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565 94.60993
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565]   below 100: TMCJPEGDEC_converterYUV420toRGB565edge 94.692986
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565] baseline: code 2284/6184 data None functions 6 fuzzy 96.4450
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] objdiff: code 15164/15948 data None/None functions 12/13 fuzzy 99.6453 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] instruction-exact functions: 2/13
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   section .text size 15948 match 99.64535
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8]   below 100: TMCJPEGDEC_set_converterY8U8V8 92.78571
[libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8] baseline: code 15164/15948 data None functions 12 fuzzy 99.6453
regressions vs baseline: 0
global matched_code_percent: 91.58086 -> 91.59302
global fuzzy_match_percent: 99.70061 -> 99.70077
global complete_code_percent: 74.74593 -> 74.74593
global matched_data_percent: 99.77803 -> 99.77803
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
