# big1 max round

43U only. Worker scope: src/BS2/BS2Mach, src/scene/setting/AOSS, src/BS2/BS2Update, src/channelScript/CHANSVm
HEAD bdd15186a7a7ead832da3fc5e2688bf0552a4b4f
origin/main bdd15186a7a7ead832da3fc5e2688bf0552a4b4f

## src/BS2/BS2Mach
Initial instruction-exact 24/29. Objdiff {"fuzzy_match_percent": 98.159485, "total_code": "16980", "matched_code": "4940", "matched_code_percent": 29.093052, "total_data": "158528", "matched_data": "155504", "matched_data_percent": 98.092445, "total_functions": 29, "matched_functions": 24, "matched_functions_percent": 82.75862, "total_units": 1}
POOL IDENTICAL up to 91 (mine=91 base=91)

Open Run 16.744186%; 172 bytes.
Open BS2StartGame 98.72774%; 1572 bytes.
Open BS2StartGCGame 99.5614%; 912 bytes.
Open CheckBS2CommandStatus 99.50739%; 1624 bytes.
Open BS2Tick 98.230415%; 7760 bytes.
## src/scene/setting/AOSS
Initial instruction-exact 15/21. Objdiff {"fuzzy_match_percent": 96.777916, "total_code": "16192", "matched_code": "6436", "matched_code_percent": 39.748024, "total_data": "3928", "matched_data": "3928", "matched_data_percent": 100.0, "total_functions": 21, "matched_functions": 16, "matched_functions_percent": 76.190475, "total_units": 1}
POOL IDENTICAL up to 1 (mine=1 base=1)

Open AOSS_Init_old 93.78725%; 6336 bytes.
Open AOSSDecryptMessage 97.74143%; 1284 bytes.
Open AOSSApplyAuthOptions 98.77193%; 456 bytes.
Open AOSSSendHelloRequest 92.190475%; 1092 bytes.
Open AOSSXorBufferWithKey 98.605446%; 588 bytes.
## src/BS2/BS2Update
Initial instruction-exact 9/10. Objdiff {"fuzzy_match_percent": 94.23001, "total_code": "4052", "matched_code": "400", "matched_code_percent": 9.871669, "total_data": "10488", "matched_data": "10488", "matched_data_percent": 100.0, "total_functions": 10, "matched_functions": 9, "matched_functions_percent": 90.0, "total_units": 1}
POOL IDENTICAL up to 55 (mine=55 base=55)

Open UpdateThread 93.59803%; 3652 bytes.
## src/channelScript/CHANSVm
Initial instruction-exact 221/233. Objdiff {"fuzzy_match_percent": 99.364426, "total_code": "53564", "matched_code": "37608", "matched_code_percent": 70.211334, "total_data": "6904", "matched_data": "6904", "matched_data_percent": 100.0, "total_functions": 233, "matched_functions": 221, "matched_functions_percent": 94.849785, "total_units": 1}
POOL IDENTICAL up to 125 (mine=125 base=125)

Open CHANSVmConvertToFloatFromStr 97.59036%; 332 bytes.
Open VmDateDtor 94.96703%; 364 bytes.
Open VmStringReplace 97.878784%; 528 bytes.
Open VmStringSplit 98.04054%; 888 bytes.
Open CHANSVmFormatString 99.84919%; 1724 bytes.
Open VmBlobGetHexString 98.71951%; 328 bytes.
Open VmBlobPackCommon 97.949104%; 2672 bytes.
Open VmBlobUnpack 98.452614%; 2068 bytes.
Open VmWinEmuWrite 99.62687%; 268 bytes.
Open CHANSVmAddExe 99.625984%; 1016 bytes.
Open CHANSVmLinkModules 98.677246%; 756 bytes.
Open CHANSVmStep 96.46608%; 5012 bytes.

## src/BS2/BS2Mach::BS2Tick
Remote bdd15186, owned source UNCHANGED, local objdiff 98.230415%.
- ATTEMPT BS2Tick: reset progress pointer before partition stores through a dedicated inline initializer; source feebdf09ee6c; 98.230415%; instructions 1934/1940; structural/operand (136, 1665); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: read boot console code and write device code through distinct typed helpers; source 0da822d85d78; 98.230415%; instructions 1934/1940; structural/operand (136, 1665); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: compute game partition offset before the cached versus DVD path; source 24a6f27be2be; BUILD FAILED /MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -W nomissingreturn -ipa file -gccinc -fp_contract off -O4,s -enc SJIS -lang=c -MMD -c src/BS2/BS2Mach.c -o build/43U/src/src/BS2 && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/BS2/BS2Mach.d build/43U/src/src/BS2/BS2Mach.d ### mwcceppc.exe Compiler: #    File: src\BS2\BS2Mach.c # -------------------------- #    1165:     case 0x26: {  #   Error:     ^^^^ #   (10169) illegal use of keyword #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. ; restored.
- ATTEMPT BS2Tick: compute game partition offset before both cached and DVD branches; source 679382637c01; 98.4732%; instructions 1934/1940; structural/operand (131, 1665); exact 24; data 155504; regress []; RETAINED.
- ATTEMPT BS2Tick: read-only disc header and separate read-only disc title view; source 1257019edfae; 98.48866%; instructions 1935/1940; structural/operand (132, 1703); exact 24; data 155504; regress []; RETAINED.
- ATTEMPT BS2Tick: calculate banner alignment by removing the actual address remainder; source ab0b8724bcda; 98.6768%; instructions 1936/1940; structural/operand (119, 1702); exact 24; data 155504; regress []; RETAINED.
- ATTEMPT BS2Tick: carry both IOS words in one native version value before storing low then high; source 52473c630592; 98.6665%; instructions 1936/1940; structural/operand (119, 1702); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: store IOS low word before reading and storing IOS high word; source a57c902cb098; 98.423195%; instructions 1936/1940; structural/operand (121, 1702); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: encode title-prefix dispatch as the original D R S T switch cases; source 330c30a0c312; 98.59175%; instructions 1937/1940; structural/operand (110, 1699); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: use native loader output locals ordered length address offset; source 7814326d92a8; 98.66392%; instructions 1936/1940; structural/operand (147, 1702); exact 24; data 155504; regress []; restored.

## src/scene/setting/AOSS::AOSS_Init_old
Remote 786a2dd3, owned source UNCHANGED, local objdiff 93.78725%.
Structural audit: instructions 1575/1584, structural/operand (1141, 1524).
Data audit: AOSS, BS2Update and CHANSVm already have 100% named/data measures. BS2Mach .bss/.sbss/.sdata are 100%; .data is pooled literals plus four jump tables with relocation targets in nonexact functions. No unmatched real named object or unjustified extent correction identified.

Checkpoint: four-unit quick GATE PASS, full 43U build ok, DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d, regressions 0, forbidden additions 0, readability warnings 0. BS2Tick 98.230415 -> 98.6768%; 1934 -> 1936 of 1940 instructions; no new exact function yet. Evidence /tmp/big1.gate-first.txt.
- ATTEMPT AOSS_Init_old: model the two independent default wait halfwords as named constant objects; source d1fefb8e620a; 93.67803%; instructions 1574/1584; structural/operand (1130, 1300); exact 15; data 3920; regress []; restored.
- ATTEMPT AOSS_Init_old: independent default arrays retain the target halfword loads; source d2b427a6baff; 93.88952%; instructions 1574/1584; structural/operand (1128, 1297); exact 15; data 3920; regress []; restored.
- ATTEMPT AOSS_Init_old: derive transaction record after random generation from the same byte cursor; source 5c8b5ebeec65; 93.68813%; instructions 1573/1584; structural/operand (1138, 1523); exact 15; data 3928; regress []; restored.
- ATTEMPT AOSS_Init_old: place send and receive address lifetimes in their target stack declaration order; source d643ade7e48d; 93.79419%; instructions 1575/1584; structural/operand (195, 1524); exact 15; data 3928; regress []; RETAINED.
- ATTEMPT AOSS_Init_old: use zero-first timeout branch sequence instead of a three-way switch; source 65a027183cc1; 94.179924%; instructions 1573/1584; structural/operand (185, 1519); exact 15; data 3928; regress []; RETAINED.
- ATTEMPT AOSS_Init_old: use matching zero-first timeout sequence after state dispatch; source e264e471f42f; 94.420456%; instructions 1571/1584; structural/operand (165, 1516); exact 15; data 3928; regress []; RETAINED.
- ATTEMPT AOSS_Init_old: read connection-state word with the target unsigned comparison; source bacde7f2d0bc; 94.31881%; instructions 1571/1584; structural/operand (163, 1516); exact 15; data 3928; regress []; restored.
- ATTEMPT AOSS_Init_old: share retry sleep call after choosing the bounded duration; source 02df5a9ef693; 94.48674%; instructions 1570/1584; structural/operand (154, 1510); exact 15; data 3928; regress []; RETAINED.
Target AOSS_Init_old reads r14 at 0xa20 before any assignment to r14 in the function. Existing initialized initializationResult retains defined source behavior; recreating an uninitialized value is forbidden and was not attempted.

## src/BS2/BS2Update::UpdateThread
Remote bf6bc87f, owned source UNCHANGED, local objdiff 93.59803%.
Structural audit: instructions 904/913, structural/operand (97, 745).
EntriesCount volatile proof: target UpdateThread 0xc2c stw r17,EntriesCount; 0xc30 lwz r0,EntriesCount, immediately rereads the stored global with no intervening instruction. Change is local to this static definition; other units cannot observe its definition qualifier.
- ATTEMPT UpdateThread: declare asynchronously published entry count volatile at its definition; source c23cf5584600; 93.90471%; instructions 905/913; structural/operand (94, 747); exact 9; data 10488; regress []; RETAINED.
- ATTEMPT UpdateThread: use an immutable view when validating input update entries; source cf860c856a75; BUILD FAILED /include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -W nomissingreturn -ipa file -gccinc -fp_contract off -O4,s -enc SJIS -lang=c -MMD -c src/BS2/BS2Update.c -o build/43U/src/src/BS2 && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/BS2/BS2Update.d build/43U/src/src/BS2/BS2Update.d ### mwcceppc.exe Compiler: #    File: src\BS2\BS2Update.c # ---------------------------- #     255:             discEntries[index].size = scratch.file.length;  #   Error:                                                          ^ #   (10179) illegal assignment to constant #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. ; restored.
- ATTEMPT UpdateThread: form the selected seat pointer after reading the seat file; source 23c61edba9da; 93.76999%; instructions 905/913; structural/operand (98, 748); exact 9; data 10488; regress []; restored.
- ATTEMPT UpdateThread: use a read-only disc entry view during the import loop; source 51b4d2f7f9ec; BUILD FAILED /include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -W nomissingreturn -ipa file -gccinc -fp_contract off -O4,s -enc SJIS -lang=c -MMD -c src/BS2/BS2Update.c -o build/43U/src/src/BS2 && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/BS2/BS2Update.d build/43U/src/src/BS2/BS2Update.d ### mwcceppc.exe Compiler: #    File: src\BS2\BS2Update.c # ---------------------------- #     447:                      CurrentEntry = &discEntries[UpdateProgress];  #   Error:                                                                 ^ #   (10209) illegal implicit conversion from 'const struct BS2UpdateEntry *'  #   to #   'struct BS2UpdateEntry *' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. ; restored.
- ATTEMPT UpdateThread: read-only import view with mutable entry publication through the real table; source b2940a9daf08; 93.77875%; instructions 905/913; structural/operand (95, 747); exact 9; data 10488; regress []; restored.
- ATTEMPT UpdateThread: recompute import failure title from the real table instead of the cached view; source 3c5af61789ff; 93.56955%; instructions 905/913; structural/operand (96, 747); exact 9; data 10488; regress []; restored.
- ATTEMPT UpdateThread: start the capacity totals before selected count to reflect target live ranges; source a94c0c8c97ec; 93.89923%; instructions 905/913; structural/operand (94, 748); exact 9; data 10488; regress []; restored.

## src/channelScript/CHANSVm::CHANSVmConvertToFloatFromStr
Remote bf6bc87f, owned source UNCHANGED, local objdiff 97.59036%.
Structural audit: instructions 83/83, structural/operand (2, 2).
- ATTEMPT CHANSVmConvertToFloatFromStr: parse floating strings through a const input-object view; source 08f3842e7fed; 97.59036%; instructions 83/83; structural/operand (2, 2); exact 221; data 6904; regress []; restored.

## src/channelScript/CHANSVm::CHANSVmStep
Remote bf6bc87f, owned source UNCHANGED, local objdiff 96.46608%.
Structural audit: instructions 1253/1253, structural/operand (65, 313).
disasm_fn.py stops at the first unsupported paired-single save. Both required dumps were run; /tmp/big1.step.{target,ours}.full.asm supplements them with per-instruction decoding and relocation names. Target uses explicit zero-count branch and a pretested countdown loop; source uses arithmetic normalization and posttested loop. Frames both 0xf0; operand scratch at 0x60.
- ATTEMPT CHANSVmStep: normalize the requested instruction count with the target explicit branch; source b4399d1d991c; 96.86832%; instructions 1254/1253; structural/operand (60, 1229); exact 221; data 2232; regress []; restored.
- ATTEMPT CHANSVmStep: use the target pretested instruction countdown loop; source 85374133139a; 96.09896%; instructions 1258/1253; structural/operand (86, 1242); exact 221; data 2232; regress []; restored.
- ATTEMPT CHANSVmStep: access opcode result types directly instead of keeping a live table pointer; source f4b87f4270c2; 96.322426%; instructions 1254/1253; structural/operand (83, 1094); exact 221; data 2232; regress []; restored.
Discarded pretested-loop trial above used a mismatched tail substitution; it is excluded from distinct valid coverage. Following trials decrement inside the loop and preserve the target exit semantics.
- ATTEMPT CHANSVmStep: complete pretested countdown with one decrement after each interpreted instruction; source bbe417f69a7a; 96.26656%; instructions 1254/1253; structural/operand (65, 1237); exact 221; data 2232; regress []; restored.
- ATTEMPT CHANSVmStep: combine native zero-count normalization and complete pretested countdown; source fc94f5ea0968; 96.8332%; instructions 1255/1253; structural/operand (60, 1229); exact 221; data 2232; regress []; restored.
- ATTEMPT CHANSVmStep: keep copies indexed through their named scratch fields at inline boundaries; source b7504e908356; BUILD FAILED e -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -W nomissingreturn -ipa file -gccinc -fp_contract off -O4,s -enc SJIS -lang=c -MMD -c src/channelScript/CHANSVm.c -o build/43U/src/src/channelScript && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/channelScript/CHANSVm.d build/43U/src/src/channelScript/CHANSVm.d ### mwcceppc.exe Compiler: #    File: src\channelScript\CHANSVm.c # ------------------------------------ #    7761:                         int typeByte = &scratch.copies[0]->type;  #   Error:                                                          ^^ #   (10499) a pointer/array type was expected for this operation instead of  #   'struct CHANSVmObjHdr' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. ; restored.

## src/BS2/BS2Mach::BS2StartGCGame
Remote bf6bc87f, owned source DIFFERS: inspect remote before experimenting, local objdiff 99.5614%.

## src/BS2/BS2Mach::BS2StartGCGame
Remote bf6bc87f, owned source UNCHANGED, local objdiff 99.5614%.
Structural audit: instructions 228/228, structural/operand (2, 7).
- ATTEMPT BS2StartGCGame: poll existing volatile DVD command state directly as the target does; source 037ee4dd017f; 97.82895%; instructions 228/228; structural/operand (4, 9); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2StartGCGame: put timer frequency first in the native 64-bit clock product; source 62468e7959ef; 99.429825%; instructions 228/228; structural/operand (2, 11); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2StartGCGame: combine direct volatile cover polling with frequency-first clock multiplication; source 600487df3cf1; 97.697365%; instructions 228/228; structural/operand (4, 13); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2StartGCGame: use a const command-block view for cover polling and native clock product; source f70c0636b462; 97.697365%; instructions 228/228; structural/operand (4, 13); exact 24; data 155504; regress []; restored.

## src/BS2/BS2Mach::CheckBS2CommandStatus
Remote 27abfe81, owned source UNCHANGED, local objdiff 99.50739%.
Structural audit: instructions 406/406, structural/operand (2, 2).
- ATTEMPT CheckBS2CommandStatus: publish cache-command flag before computing the partition byte count; source ec11f8913900; 99.48276%; instructions 406/406; structural/operand (2, 4); exact 24; data 155504; regress []; restored.
- ATTEMPT CheckBS2CommandStatus: read partition count from an immutable TOC view; source 9deaa5878d9b; 99.50739%; instructions 406/406; structural/operand (2, 2); exact 24; data 155504; regress []; restored.
- ATTEMPT CheckBS2CommandStatus: read the partition count before publishing cache completion then round its bytes; source fee8dd9e67a9; 99.445816%; instructions 406/406; structural/operand (2, 7); exact 24; data 155504; regress []; restored.

## src/BS2/BS2Mach::Run
Remote 1f0eb50f, owned source UNCHANGED, local objdiff 16.744186%.
Structural audit: instructions 11/43, structural/operand (40, 42).
- ATTEMPT Run: guard the cache loop then use its native posttested block countdown; source 2d3f1492b5af; 11.976745%; instructions 11/43; structural/operand (42, 43); exact 24; data 155504; regress []; restored.
- ATTEMPT Run: use an indexed counted cache-block traversal; source 7e48cf01d356; 16.744186%; instructions 11/43; structural/operand (40, 42); exact 24; data 155504; regress []; restored.
- ATTEMPT Run: keep the entry callback typed separately from cache traversal; source 68ead673d9b4; 16.744186%; instructions 11/43; structural/operand (40, 42); exact 24; data 155504; regress []; restored.
Run remains an ABI trampoline: the target zeroes r2-r31 and r1, sets LR to entryPoint, and returns directly into it. Ordinary C preserves the ABI; new assembly and uninitialized values are forbidden. All three cache-loop/callback forms restored.

## src/BS2/BS2Mach::BS2StartGame
Remote 1f0eb50f, owned source UNCHANGED, local objdiff 98.72774%.
Structural audit: instructions 393/393, structural/operand (4, 10).
- ATTEMPT BS2StartGame: use the SDK-declared volatile PI register through a typed register pointer; source 0f002cb4ee53; 98.72774%; instructions 393/393; structural/operand (4, 10); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2StartGame: put the precomputed DI enable mask before the loaded register value; source 66df856a1c6c; 98.71501%; instructions 393/393; structural/operand (4, 10); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2StartGame: poll the cover block through an immutable command view; source 449060454a23; 98.72774%; instructions 393/393; structural/operand (4, 10); exact 24; data 155504; regress []; restored.

## src/scene/setting/AOSS::AOSSDecryptMessage
Remote 1f0eb50f, owned source UNCHANGED, local objdiff 97.74143%.
Structural audit: instructions 321/321, structural/operand (2, 89).

## src/channelScript/CHANSVm::CHANSVmConvertToFloatFromStr
Remote e9114959, owned source UNCHANGED, local objdiff 97.59036%.
Structural audit: instructions 83/83, structural/operand (2, 2).
- ATTEMPT CHANSVmConvertToFloatFromStr: initialize the parse end pointer at its local declaration; source 6799748b27b4; 97.59036%; instructions 83/83; structural/operand (2, 2); exact 221; data 6904; regress []; restored.
- ATTEMPT CHANSVmConvertToFloatFromStr: read the object type directly at the parse branch boundary; source 76ea6ee2c272; 95.180725%; instructions 83/83; structural/operand (2, 3); exact 221; data 6904; regress []; restored.
- ATTEMPT CHANSVmConvertToFloatFromStr: widen the local type tag to its natural comparison width; source 9429a50f549b; 97.59036%; instructions 83/83; structural/operand (2, 2); exact 221; data 6904; regress []; restored.

## src/scene/setting/AOSS::AOSSDecryptMessage
Remote e9114959, owned source UNCHANGED, local objdiff 97.74143%.
Structural audit: instructions 321/321, structural/operand (2, 89).
- ATTEMPT AOSSDecryptMessage: derive cipher state after calculating the next stream index; source 57165f16c767; 97.74143%; instructions 321/321; structural/operand (2, 89); exact 15; data 3928; regress []; restored.
- ATTEMPT AOSSDecryptMessage: place the keystream byte before the input byte in XOR expression; source 0caf30a1b22e; 97.74143%; instructions 321/321; structural/operand (2, 89); exact 15; data 3928; regress []; restored.
- ATTEMPT AOSSDecryptMessage: use an immutable input message view while retaining the writable output payload; source 0366d2d5dc6b; 97.74143%; instructions 321/321; structural/operand (2, 89); exact 15; data 3928; regress []; restored.

## src/scene/setting/AOSS::AOSSApplyAuthOptions
Remote e9114959, owned source UNCHANGED, local objdiff 98.77193%.
Structural audit: instructions 114/114, structural/operand (0, 22).
- ATTEMPT AOSSApplyAuthOptions: reuse the response record cursor for the nested option traversal; source f32e89b5aae4; 96.18421%; instructions 114/114; structural/operand (2, 38); exact 15; data 3928; regress []; restored.
- ATTEMPT AOSSApplyAuthOptions: initialize accumulated flags immediately after validation and before record search; source 199c114043b3; 96.97369%; instructions 114/114; structural/operand (3, 26); exact 15; data 3928; regress []; restored.
- ATTEMPT AOSSApplyAuthOptions: use the input length itself as the mutable traversal length; source 23c89be53628; 98.20175%; instructions 114/114; structural/operand (0, 32); exact 15; data 3928; regress []; restored.

## src/scene/setting/AOSS::AOSSSendHelloRequest
Remote e9114959, owned source UNCHANGED, local objdiff 92.190475%.
Structural audit: instructions 271/273, structural/operand (33, 254).
- ATTEMPT AOSSSendHelloRequest: compute the hello-record checksum with one complete byte traversal; source 62cfc775fc13; 87.02198%; instructions 270/273; structural/operand (43, 266); exact 15; data 3928; regress []; restored.
- ATTEMPT AOSSSendHelloRequest: read request records through a const payload view; source b65700d357f7; 92.190475%; instructions 271/273; structural/operand (33, 254); exact 15; data 3928; regress []; restored.
- ATTEMPT AOSSSendHelloRequest: derive cipher state after advancing the schedule index; source ef030a5a74e4; 92.190475%; instructions 271/273; structural/operand (33, 254); exact 15; data 3928; regress []; restored.

## src/scene/setting/AOSS::AOSSXorBufferWithKey
Remote e9114959, owned source UNCHANGED, local objdiff 98.605446%.
Structural audit: instructions 147/147, structural/operand (2, 36).
- ATTEMPT AOSSXorBufferWithKey: form each XOR byte with the key mask as its first operand; source af3b0a3e996c; 97.993195%; instructions 147/147; structural/operand (2, 46); exact 15; data 3928; regress []; restored.
- ATTEMPT AOSSXorBufferWithKey: keep the byte XOR in an unsigned word before storing the byte; source 5788be6f728c; 98.605446%; instructions 147/147; structural/operand (2, 36); exact 15; data 3928; regress []; restored.
- ATTEMPT AOSSXorBufferWithKey: update packet bytes with a direct compound XOR; source 7fa4dbc9d5a9; 98.23129%; instructions 147/147; structural/operand (2, 46); exact 15; data 3928; regress []; restored.

## src/channelScript/CHANSVm::CHANSVmFormatString
Remote e9114959, owned source UNCHANGED, local objdiff 99.84919%.
Structural audit: instructions 431/431, structural/operand (0, 13).
- ATTEMPT CHANSVmFormatString: read the converted source object through a const object view; source 22c45d4d7f1a; 99.84919%; instructions 431/431; structural/operand (0, 13); exact 221; data 6904; regress []; restored.
- ATTEMPT CHANSVmFormatString: scope the converted string object with the string-format branch; source d00bd2acb89a; 99.84919%; instructions 431/431; structural/operand (0, 13); exact 221; data 6904; regress []; restored.
- ATTEMPT CHANSVmFormatString: load the source string length before incrementing the format argument cursor; source e47a93d20ac4; 99.19489%; instructions 433/431; structural/operand (29, 132); exact 220; data 2232; regress ['VmBlobFill']; restored.

## src/channelScript/CHANSVm::VmDateDtor
Remote e9114959, owned source UNCHANGED, local objdiff 94.96703%.
Structural audit: instructions 91/91, structural/operand (5, 7).
- ATTEMPT VmDateDtor: read fields directly from the calendar local after the calendar helper returns; source 43d213e09f16; 89.14286%; instructions 90/91; structural/operand (11, 85); exact 220; data 6904; regress ['VmBlobFill']; restored.
- ATTEMPT VmDateDtor: read calendar name tables through const pointer-entry views; source 650a83106ab7; 91.62637%; instructions 91/91; structural/operand (30, 63); exact 221; data 6904; regress []; restored.
- ATTEMPT VmDateDtor: isolate calendar formatting in a typed inline read-only calendar helper; source cb719e233153; 80.14286%; instructions 98/91; structural/operand (33, 84); exact 220; data 6904; regress ['VmBlobFill']; restored.

## src/channelScript/CHANSVm::VmStringReplace
Remote e9114959, owned source UNCHANGED, local objdiff 97.878784%.
Structural audit: instructions 132/132, structural/operand (0, 40).
- ATTEMPT VmStringReplace: load search payload length before the parent payload length; source fe576a4d2273; 97.992424%; instructions 132/132; structural/operand (0, 40); exact 221; data 6904; regress []; RETAINED.
- ATTEMPT VmStringReplace: declare input byte views inside the validated argument payload region; source ff6e49dfad3a; BUILD FAILED /include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -W nomissingreturn -ipa file -gccinc -fp_contract off -O4,s -enc SJIS -lang=c -MMD -c src/channelScript/CHANSVm.c -o build/43U/src/src/channelScript && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/channelScript/CHANSVm.d build/43U/src/src/channelScript/CHANSVm.d ### mwcceppc.exe Compiler: #    File: src\channelScript\CHANSVm.c # ------------------------------------ #    3100:     const char* parentStr = VmParentObj->value.string_v->spData;  #   Error:     ^^^^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. ; restored.
- ATTEMPT VmStringReplace: initialize input and output cursors in traversal order; source 45cfca463149; 97.954544%; instructions 132/132; structural/operand (0, 41); exact 221; data 6904; regress []; restored.

## src/channelScript/CHANSVm::VmStringSplit
Remote e9114959, owned source UNCHANGED, local objdiff 98.04054%.
Structural audit: instructions 222/222, structural/operand (0, 66).
- ATTEMPT VmStringSplit: keep the delimiter argument as a const object view after conversion; source 42c5506b1761; BUILD FAILED VL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -W nomissingreturn -ipa file -gccinc -fp_contract off -O4,s -enc SJIS -lang=c -MMD -c src/channelScript/CHANSVm.c -o build/43U/src/src/channelScript && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/channelScript/CHANSVm.d build/43U/src/src/channelScript/CHANSVm.d ### mwcceppc.exe Compiler: #    File: src\channelScript\CHANSVm.c # ------------------------------------ #    3258:  CHANSVmConvertObjectType(VmInst, CHANS_VM_OBJ_TYPE_STRING, arg0);  #   Error:                                                                 ^ #   (10209) illegal implicit conversion from 'const struct CHANSVmObjHdr *' to #   'struct CHANSVmObjHdr *' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. ; restored.
- ATTEMPT VmStringSplit: load source and delimiter lengths before their byte views; source 3ef334cea05b; 97.96397%; instructions 222/222; structural/operand (2, 76); exact 221; data 6904; regress []; restored.
- ATTEMPT VmStringSplit: normalize zero-delimiter element traversal as a counted for loop; source 72b421800c7b; 97.96397%; instructions 222/222; structural/operand (2, 68); exact 221; data 6904; regress []; restored.

## src/channelScript/CHANSVm::VmBlobGetHexString
Remote e9114959, owned source UNCHANGED, local objdiff 98.71951%.
Structural audit: instructions 82/82, structural/operand (0, 14).
- ATTEMPT VmBlobGetHexString: read hexadecimal source bytes and digit characters through const views; source f11f1776011f; 98.71951%; instructions 82/82; structural/operand (0, 14); exact 221; data 6904; regress []; restored.
- ATTEMPT VmBlobGetHexString: use one advancing destination cursor for both hexadecimal characters; source e83f180ba7cb; 88.53658%; instructions 77/82; structural/operand (14, 40); exact 221; data 6904; regress []; restored.
- ATTEMPT VmBlobGetHexString: load each input byte once before selecting both hexadecimal digits; source 3876a1dc4063; 92.36585%; instructions 81/82; structural/operand (11, 36); exact 221; data 6904; regress []; restored.

## src/channelScript/CHANSVm::VmStringReplace
Remote e9114959, owned source UNCHANGED, local objdiff 97.992424%.
Structural audit: instructions 132/132, structural/operand (0, 40).
- ATTEMPT VmStringReplace: keep parent, search, and replacement byte buffers as const input views; source 2eff216b221b; 97.992424%; instructions 132/132; structural/operand (0, 40); exact 221; data 6904; regress []; restored.

## src/channelScript/CHANSVm::VmStringSplit
Remote e9114959, owned source UNCHANGED, local objdiff 98.04054%.
Structural audit: instructions 222/222, structural/operand (0, 66).
- ATTEMPT VmStringSplit: keep source and delimiter bytes as const input views; source f3a96f95b2fa; 98.04054%; instructions 222/222; structural/operand (0, 66); exact 221; data 6904; regress []; restored.

## src/channelScript/CHANSVm::CHANSVmFormatString
Remote 45aaeb16, owned source UNCHANGED, local objdiff 99.84919%.
Structural audit: instructions 431/431, structural/operand (0, 13).
- ATTEMPT CHANSVmFormatString: separate the temporary string object lifetime from the formatted byte length; source 47f052bd0f87; 99.84919%; instructions 431/431; structural/operand (0, 13); exact 221; data 6904; regress []; restored.

## src/channelScript/CHANSVm::VmBlobPackCommon
Remote 45aaeb16, owned source UNCHANGED, local objdiff 97.949104%.
Structural audit: instructions 668/668, structural/operand (0, 244).
- ATTEMPT VmBlobPackCommon: read source blob descriptors through const pointers; source 285844da5341; 97.949104%; instructions 668/668; structural/operand (0, 244); exact 221; data 6904; regress []; restored.
- ATTEMPT VmBlobPackCommon: load the high integer word before the low word in integer packing; source da34f1b29bad; 97.949104%; instructions 668/668; structural/operand (0, 244); exact 221; data 6904; regress []; restored.
- ATTEMPT VmBlobPackCommon: initialize format traversal before argument traversal in packing; source b5ddd715f33b; 97.949104%; instructions 668/668; structural/operand (0, 244); exact 221; data 6904; regress []; restored.

## src/channelScript/CHANSVm::VmBlobUnpack
Remote 45aaeb16, owned source UNCHANGED, local objdiff 98.452614%.
Structural audit: instructions 517/517, structural/operand (0, 141).
- ATTEMPT VmBlobUnpack: read the unpack format through a const wide-character view; source ceb7d96fa71c; 98.452614%; instructions 517/517; structural/operand (0, 141); exact 221; data 6904; regress []; restored.
- ATTEMPT VmBlobUnpack: initialize decoded-buffer words in their memory order; source 2b671815931d; 98.448746%; instructions 517/517; structural/operand (2, 143); exact 221; data 6904; regress []; restored.
- ATTEMPT VmBlobUnpack: initialize format traversal before result-element traversal in unpacking; source ea2dbd1d2bba; 98.44294%; instructions 517/517; structural/operand (0, 142); exact 221; data 6904; regress []; restored.

## src/channelScript/CHANSVm::VmWinEmuWrite
Remote 45aaeb16, owned source UNCHANGED, local objdiff 99.62687%.
Structural audit: instructions 67/67, structural/operand (0, 5).
- ATTEMPT VmWinEmuWrite: read the converted document string through a const object view; source fbab2e4baed3; 99.62687%; instructions 67/67; structural/operand (0, 5); exact 221; data 6904; regress []; restored.
- ATTEMPT VmWinEmuWrite: calculate string extent before initializing its byte cursor; source c1191ce56414; 99.62687%; instructions 67/67; structural/operand (0, 5); exact 221; data 6904; regress []; restored.
- ATTEMPT VmWinEmuWrite: use a counted block traversal for document encoding; source c2c25edecf0a; 99.62687%; instructions 67/67; structural/operand (0, 5); exact 221; data 6904; regress []; restored.

## src/channelScript/CHANSVm::CHANSVmAddExe
Remote 45aaeb16, owned source UNCHANGED, local objdiff 99.625984%.
Structural audit: instructions 254/254, structural/operand (0, 16).
- ATTEMPT CHANSVmAddExe: retain the executable-type argument as an explicit scalar; source e81b2f9afb42; 99.625984%; instructions 254/254; structural/operand (0, 16); exact 221; data 6904; regress []; restored.
- ATTEMPT CHANSVmAddExe: read module-header validation fields through a const descriptor view; source 4b55dbb9eea2; 99.625984%; instructions 254/254; structural/operand (0, 16); exact 221; data 6904; regress []; restored.
- ATTEMPT CHANSVmAddExe: derive the executable payload through its typed module member; source 2dd735c854a6; 98.19292%; instructions 254/254; structural/operand (7, 26); exact 221; data 6904; regress []; restored.

## src/channelScript/CHANSVm::CHANSVmLinkModules
Remote 45aaeb16, owned source UNCHANGED, local objdiff 98.677246%.
Structural audit: instructions 189/189, structural/operand (0, 43).
- ATTEMPT CHANSVmLinkModules: read dispatch table entries through a const table view; source 99fcdb1d7c09; 98.677246%; instructions 189/189; structural/operand (0, 43); exact 221; data 6904; regress []; restored.
- ATTEMPT CHANSVmLinkModules: keep each copied dispatch descriptor const within the name-resolution pass; source 4a3167bdf8c3; 98.677246%; instructions 189/189; structural/operand (0, 43); exact 221; data 6904; regress []; restored.
- ATTEMPT CHANSVmLinkModules: separate module traversal from the two scoped name-resolution iterators; source 4c8d4dcbf81f; 98.677246%; instructions 189/189; structural/operand (0, 43); exact 221; data 6904; regress []; restored.

DECLSEARCH AOSSApplyAuthOptions: source-level structure and const/lifetime trials exhausted; run declaration-order search, maximum 300 evaluations.
DECLSEARCH AOSSApplyAuthOptions:  | regress [].
DECLSEARCH AOSSApplyAuthOptions: restored due to failure or exact-function regression.

DECLSEARCH AOSSDecryptMessage: source-level structure and const/lifetime trials exhausted; run declaration-order search, maximum 300 evaluations.
DECLSEARCH AOSSDecryptMessage:  | regress [].
DECLSEARCH AOSSDecryptMessage: restored due to failure or exact-function regression.

DECLSEARCH AOSSXorBufferWithKey: source-level structure and const/lifetime trials exhausted; run declaration-order search, maximum 300 evaluations.
DECLSEARCH AOSSXorBufferWithKey:  | regress [].
DECLSEARCH AOSSXorBufferWithKey: restored due to failure or exact-function regression.

DECLSEARCH AOSSApplyAuthOptions: source-level structure and const/lifetime trials exhausted; run declaration-order search, maximum 300 evaluations.

DECLSEARCH CHANSVmFormatString: source-level structure and const/lifetime trials exhausted; run declaration-order search, maximum 300 evaluations.
DECLSEARCH AOSSApplyAuthOptions: declaration block: |       u32 flags = 0; |       const AOSSReplyOption* responseRecord; |       AOSSConfigRecord* configRecord; |       AOSSStoredConfig* wep40Config; |       AOSSStoredConfig* wep104Config; |       AOSSStoredConfig* tkipConfig; |       AOSSStoredConfig* aesConfig; |       u8* networkSettings; |       const AOSSReplyOption* option; |       u32 length; |       s32 remainingLength = responseLength; |       int result; | start (0, 22) | best (0, 22) after 177 builds; source restored; best order was: |     u32 flags = 0; |     const AOSSReplyOption* responseRecord; |     AOSSConfigRecord* configRecord; |     AOSSStoredConfig* wep40Config; |     AOSSStoredConfig* wep104Config; |     AOSSStoredConfig* tkipConfig; |     AOSSStoredConfig* aesConfig; |     u8* networkSettings; |     const AOSSReplyOption* option; |     u32 length; |     s32 remainingLength = responseLength; |     int result; |  | regress [].

DECLSEARCH AOSSDecryptMessage: source-level structure and const/lifetime trials exhausted; run declaration-order search, maximum 300 evaluations.

Coverage exclusions: CHANSVmStep source 85374133139a had the wrong countdown tail and is excluded; CHANSVmAddExe source using header = mod->module reads a pointer member instead of deriving the adjacent payload and is excluded. Failed compilations never count as successful source attempts.
Data proof: target BS2Mach .data contains seven pooled literal ranges at offsets 0, 0x22, 0x3c, 0x428, 0x452, 0x648, 0x669 and four relocated switch tables at 0x3f4, 0x590, 0xa4c, 0xaa8. Their table destinations belong to nonexact command/tick code. No named source object can justify a target symbol rename or extent correction; no config address/extent edits made.
DECLSEARCH AOSSDecryptMessage: declaration block: |       u32 checksum; |       u8 manufacturerAddress[8]; |       AOSSKeySchedule schedule; |       AOSSEncryptedPayload* encrypted = &message->payload.encrypted; |       u8* decryptedData; |       u32 controlFlags; |       u32 dataLength; |       u32 i; |       s32 crcIndex; |       u32 firstIndex; |       u32 secondIndex; |       u32 firstValue; |       u32 secondValue; |       u32 stateIndex; |       u32 crc; |       const u8* inputCursor; |       u8* state; |       u8* outputCursor; |       int result; | start (0, 87) | best (0, 87) after 300 builds; source restored; best order was: |     u32 checksum; |     u8 manufacturerAddress[8]; |     AOSSKeySchedule schedule; |     AOSSEncryptedPayload* encrypted = &message->payload.encrypted; |     u8* decryptedData; |     u32 controlFlags; |     u32 dataLength; |     u32 i; |     s32 crcIndex; |     u32 firstIndex; |     u32 secondIndex; |     u32 firstValue; |     u32 secondValue; |     u32 stateIndex; |     u32 crc; |     const u8* inputCursor; |     u8* state; |     u8* outputCursor; |     int result; |  | regress [].

DECLSEARCH AOSSXorBufferWithKey: source-level structure and const/lifetime trials exhausted; run declaration-order search, maximum 300 evaluations.
DECLSEARCH AOSSXorBufferWithKey: declaration block: |       u8* temporaryHalf; |       s32 halfLength = length / 2; |       u8* packetHalf; |       s32 round; |       u8* keyMask; |       u8* temporary; |       s32 keyIndex; |       s32 index; |       int result = -1; |       u8* packetBytes; | start (0, 34) | best (0, 34) after 118 builds; source restored; best order was: |     u8* temporaryHalf; |     s32 halfLength = length / 2; |     u8* packetHalf; |     s32 round; |     u8* keyMask; |     u8* temporary; |     s32 keyIndex; |     s32 index; |     int result = -1; |     u8* packetBytes; |  | regress [].
DECLSEARCH CHANSVmFormatString: declaration block: |       u8* fmtBuf; |       wchar_t wideFmt[32]; |       u32 halfMaxSize; |       BOOL flag; |       CHANSVmObjHdr* tempObj; |       u32 argIdxCounter; |       u32 totalLen; |       u8* str; |       u32 strLen; |       u32 strPos; |       u32 segStart; |       u32 fmtBufPos; |       u8* tmpBuf; |       u32 maxSize; |       u8* outputBuf; |       u32 outputPos; |       u32 maxLitLen; |       u32 litLen; |       u32 isEscaped; |       CHANSVmObjHdr* cv; |       CHANSVmPrivate* pVm; |       CHANSVmObjHdr* argObj; | start (0, 13) | best (0, 13) after 300 builds; source restored; best order was: |     u8* fmtBuf; |     wchar_t wideFmt[32]; |     u32 halfMaxSize; |     BOOL flag; |     CHANSVmObjHdr* tempObj; |     u32 argIdxCounter; |     u32 totalLen; |     u8* str; |     u32 strLen; |     u32 strPos; |     u32 segStart; |     u32 fmtBufPos; |     u8* tmpBuf; |     u32 maxSize; |     u8* outputBuf; |     u32 outputPos; |     u32 maxLitLen; |     u32 litLen; |     u32 isEscaped; |     CHANSVmObjHdr* cv; |     CHANSVmPrivate* pVm; |     CHANSVmObjHdr* argObj; |  | regress [].

DECLSEARCH VmWinEmuWrite: source-level structure and const/lifetime trials exhausted; run declaration-order search, maximum 300 evaluations.

## src/BS2/BS2Mach::BS2Tick
Remote 29fe1efa, owned source UNCHANGED, local objdiff 98.6768%.
Structural audit: instructions 1936/1940, structural/operand (119, 1702).
Device-code access proof: private/os.h defines vu16 __OSDeviceCode with ADDRESS(OS_BASE_CACHED | OS_ADDR_DEVICE_CODE), 0x800030e6. Target case 5 uses an independent lis for each write; use the existing SDK object instead of a nonvolatile raw pointer.
DECLSEARCH VmWinEmuWrite: declaration block: |       CHANSVmObjHdr* strObj; |       u32 offset; |       u32 totalLength; |       u8 buf[VM_STRING_SIZE]; |       s32 outLen; |       s32 inLen; |       s32 result; |       u32 remaining; | start (0, 5) | best (0, 5) after 71 builds; source restored; best order was: |     CHANSVmObjHdr* strObj; |     u32 offset; |     u32 totalLength; |     u8 buf[VM_STRING_SIZE]; |     s32 outLen; |     s32 inLen; |     s32 result; |     u32 remaining; |  | regress [].
- ATTEMPT BS2Tick: write the device code through its SDK-declared volatile low-memory object; source 91b01c705232; 98.6768%; instructions 1936/1940; structural/operand (119, 1702); exact 24; data 155504; regress []; restored.

DECLSEARCH CHANSVmAddExe: source-level structure and const/lifetime trials exhausted; run declaration-order search, maximum 300 evaluations.
- ATTEMPT BS2Tick: make title-prefix fallthrough and unrestricted-prefix branches explicit; source f576609ce6f4; 98.6768%; instructions 1936/1940; structural/operand (119, 1702); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: put the existing-partition transition before the missing-partition exit; source 24a8cfb915ec; 98.59278%; instructions 1937/1940; structural/operand (113, 1699); exact 24; data 155504; regress []; restored.
DECLSEARCH CHANSVmAddExe: declaration block: |       CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm; |       ModuleHeader* mod; |       CHANSVmModule* header; |       u32 maxEnd; |       u32 size; |       u32 cnt; |       u32 ofs; | start (0, 16) | best (0, 16) after 52 builds; source restored; best order was: |     CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm; |     ModuleHeader* mod; |     CHANSVmModule* header; |     u32 maxEnd; |     u32 size; |     u32 cnt; |     u32 ofs; |  | regress [].

DECLSEARCH CHANSVmLinkModules: source-level structure and const/lifetime trials exhausted; run declaration-order search, maximum 300 evaluations.
DECLSEARCH CHANSVmLinkModules: declaration block: |       CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm; |       CHANSVmModule* module; |       u32 modIdx; |       u32 i; | start (0, 43) | best (0, 43) after 13 builds; source restored; best order was: |     CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm; |     CHANSVmModule* module; |     u32 modIdx; |     u32 i; |  | regress [].

## src/channelScript/CHANSVm::CHANSVmAddExe
Remote 29fe1efa, owned source UNCHANGED, local objdiff 99.625984%.
Structural audit: instructions 254/254, structural/operand (0, 16).
- ATTEMPT CHANSVmAddExe: derive the adjacent payload before module validation without reading its fields early; source 4101ec2d810b; 98.31102%; instructions 254/254; structural/operand (28, 60); exact 221; data 6904; regress []; restored.

## src/BS2/BS2Mach::CheckBS2CommandStatus
Remote 29fe1efa, owned source UNCHANGED, local objdiff 99.50739%.
Structural audit: instructions 406/406, structural/operand (2, 2).
- ATTEMPT CheckBS2CommandStatus: calculate partition cache extent through a const TOC inline helper; source 6fc3d898a116; 98.81527%; instructions 406/406; structural/operand (4, 12); exact 24; data 155504; regress []; restored.

## src/channelScript/CHANSVm::CHANSVmConvertToFloatFromStr
Remote 29fe1efa, owned source UNCHANGED, local objdiff 97.59036%.
Structural audit: instructions 83/83, structural/operand (2, 2).
- ATTEMPT CHANSVmConvertToFloatFromStr: load the parse type after initializing the addressable end pointer; source 993ebfb33b38; 95.180725%; instructions 83/83; structural/operand (2, 3); exact 221; data 6904; regress []; restored.
- ATTEMPT CHANSVmConvertToFloatFromStr: save the string-type predicate before end-pointer initialization; source 2de2182cafda; 94.93976%; instructions 85/83; structural/operand (5, 74); exact 220; data 6904; regress ['VmBlobFill']; restored.

AOSSParseNetworkSettings is already 100.0% in objdiff and 0 structural/0 operand differences with declsearch disassembly. ctxdiff/gate odiff normalization reports five CR1 branch false differences: the first operand is cr1, not the branch destination, and the -56 difference equals the function start-offset shift. Per the already-matched-function rule it was not retuned. Acceptance tool left unchanged; its reported instruction-exact count remains 15/21.

Checkpoint: final retained AOSS_Init_old, UpdateThread and VmStringReplace improvements pass the four-unit quick gate. Full 43U build succeeds; DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d; zero regressions, forbidden additions and readability warnings. All instruction-exact/code/data counts remain unchanged. Evidence /tmp/big1.gate-second.txt.

## Final clean-build gate and coverage

Full non-quick gate: four owned units, GATE PASS. Full 43U build ok; DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d; pools IDENTICAL; regressions 0; forbidden additions 0; readability warnings 0. Raw gate evidence follows.

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/BS2/BS2Mach] pool: IDENTICAL
[src/BS2/BS2Mach] objdiff: code 4940/16980 data 155504/158528 functions 24/29 fuzzy 98.3635 linked code 0
[src/BS2/BS2Mach] instruction-exact functions: 24/29
[src/BS2/BS2Mach]   section .bss size 155232 match 100.0
[src/BS2/BS2Mach]   section .data size 3024 match None
[src/BS2/BS2Mach]   section .sbss size 240 match 100.0
[src/BS2/BS2Mach]   section .sdata size 32 match 100.0
[src/BS2/BS2Mach]   section .text size 16980 match 98.36349
[src/BS2/BS2Mach]   below 100: Run 16.744186
[src/BS2/BS2Mach]   below 100: BS2StartGame 98.72774
[src/BS2/BS2Mach]   below 100: BS2StartGCGame 99.5614
[src/BS2/BS2Mach]   below 100: CheckBS2CommandStatus 99.50739
[src/BS2/BS2Mach]   below 100: BS2Tick 98.6768
[src/BS2/BS2Mach] baseline: code 4940/16980 data 155504 functions 24 fuzzy 98.1595
[src/scene/setting/AOSS] pool: IDENTICAL
[src/scene/setting/AOSS] objdiff: code 6436/16192 data 3928/3928 functions 16/21 fuzzy 97.0516 linked code 0
[src/scene/setting/AOSS] instruction-exact functions: 15/21
[src/scene/setting/AOSS]   section .bss size 3496 match 100.0
[src/scene/setting/AOSS]   section .data size 368 match 100.0
[src/scene/setting/AOSS]   section .sbss size 32 match 100.0
[src/scene/setting/AOSS]   section .sdata size 24 match 100.0
[src/scene/setting/AOSS]   section .sdata2 size 8 match 100.0
[src/scene/setting/AOSS]   section .text size 16192 match 97.05163
[src/scene/setting/AOSS]   below 100: AOSS_Init_old 94.48674
[src/scene/setting/AOSS]   below 100: AOSSDecryptMessage 97.74143
[src/scene/setting/AOSS]   below 100: AOSSApplyAuthOptions 98.77193
[src/scene/setting/AOSS]   below 100: AOSSSendHelloRequest 92.190475
[src/scene/setting/AOSS]   below 100: AOSSXorBufferWithKey 98.605446
[src/scene/setting/AOSS] baseline: code 6436/16192 data 3928 functions 16 fuzzy 96.7779
[src/BS2/BS2Update] pool: IDENTICAL
[src/BS2/BS2Update] objdiff: code 400/4052 data 10488/10488 functions 9/10 fuzzy 94.5064 linked code 0
[src/BS2/BS2Update] instruction-exact functions: 9/10
[src/BS2/BS2Update]   section .bss size 9056 match 100.0
[src/BS2/BS2Update]   section .data size 1328 match 100.0
[src/BS2/BS2Update]   section .sbss size 80 match 100.0
[src/BS2/BS2Update]   section .sdata size 24 match 100.0
[src/BS2/BS2Update]   section .text size 4052 match 94.50642
[src/BS2/BS2Update]   below 100: UpdateThread 93.90471
[src/BS2/BS2Update] baseline: code 400/4052 data 10488 functions 9 fuzzy 94.2300
[src/channelScript/CHANSVm] pool: IDENTICAL
[src/channelScript/CHANSVm] objdiff: code 37608/53564 data 6904/6904 functions 221/233 fuzzy 99.3655 linked code 0
[src/channelScript/CHANSVm] instruction-exact functions: 221/233
[src/channelScript/CHANSVm]   section .data size 4672 match 100.0
[src/channelScript/CHANSVm]   section .rodata size 1432 match 100.0
[src/channelScript/CHANSVm]   section .sbss size 16 match 100.0
[src/channelScript/CHANSVm]   section .sdata size 600 match 100.0
[src/channelScript/CHANSVm]   section .sdata2 size 184 match 100.0
[src/channelScript/CHANSVm]   section .text size 53564 match 99.36555
[src/channelScript/CHANSVm]   below 100: CHANSVmConvertToFloatFromStr 97.59036
[src/channelScript/CHANSVm]   below 100: VmDateDtor 94.96703
[src/channelScript/CHANSVm]   below 100: VmStringReplace 97.992424
[src/channelScript/CHANSVm]   below 100: VmStringSplit 98.04054
[src/channelScript/CHANSVm]   below 100: CHANSVmFormatString 99.84919
[src/channelScript/CHANSVm]   below 100: VmBlobGetHexString 98.71951
[src/channelScript/CHANSVm]   below 100: VmBlobPackCommon 97.949104
[src/channelScript/CHANSVm]   below 100: VmBlobUnpack 98.452614
[src/channelScript/CHANSVm]   below 100: VmWinEmuWrite 99.62687
[src/channelScript/CHANSVm]   below 100: CHANSVmAddExe 99.625984
[src/channelScript/CHANSVm]   below 100: CHANSVmLinkModules 98.677246
[src/channelScript/CHANSVm]   below 100: CHANSVmStep 96.46608
[src/channelScript/CHANSVm] baseline: code 37608/53564 data 6904 functions 221 fuzzy 99.3644
regressions vs baseline: 0
global matched_code_percent: 90.71801 -> 90.71801
global fuzzy_match_percent: 99.57510 -> 99.57810
global complete_code_percent: 71.01273 -> 71.01273
global matched_data_percent: 99.36639 -> 99.36639
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
review note: src/BS2/BS2Update.c: volatile object declaration (orchestrator checks the target really re-reads it) (+1 net), e.g. static volatile u32 EntriesCount = 0;
GATE PASS
```

Remaining source functions (every listed function has at least three distinct successful semantic trials; failed or invalid experiments excluded):

src/BS2/BS2Mach: instruction-exact 24; code 4940 -> 4940 / 16980; data 155504 -> 155504 / 158528.
- Run 16.744186%; 11/43 instructions, structure/operands (40, 42); 3 successful distinct source attempts; ABI register clearing and stack/LR handoff require an assembly trampoline; new assembly is forbidden.
- BS2StartGame 98.72774%; 393/393 instructions, structure/operands (4, 10); 3 successful distinct source attempts; instruction scheduling or control-flow shape differs.
- BS2StartGCGame 99.5614%; 228/228 instructions, structure/operands (2, 7); 4 successful distinct source attempts; instruction scheduling or control-flow shape differs.
- CheckBS2CommandStatus 99.50739%; 406/406 instructions, structure/operands (2, 2); 4 successful distinct source attempts; instruction scheduling or control-flow shape differs.
- BS2Tick 98.6768%; 1936/1940 instructions, structure/operands (119, 1702); 12 successful distinct source attempts; four instructions short; low-memory base loads, branch shape and scheduling differ.

src/scene/setting/AOSS: instruction-exact 15; code 6436 -> 6436 / 16192; data 3928 -> 3928 / 3928.
- AOSS_Init_old 94.48674%; 1570/1584 instructions, structure/operands (154, 1510); 8 successful distinct source attempts; stack/branch/control-flow differences remain; target r14 read before assignment is unresolved and uninitialized C is forbidden.
- AOSSDecryptMessage 97.74143%; 321/321 instructions, structure/operands (0, 87); 3 successful distinct source attempts; register allocation and commutative operand selection; declaration/lifetime/const views did not make it exact.
- AOSSApplyAuthOptions 98.77193%; 114/114 instructions, structure/operands (0, 22); 3 successful distinct source attempts; register allocation and commutative operand selection; declaration/lifetime/const views did not make it exact.
- AOSSSendHelloRequest 92.190475%; 271/273 instructions, structure/operands (33, 254); 3 successful distinct source attempts; two instructions short; global-base grouping, checksum unrolling and cipher lifetimes differ.
- AOSSXorBufferWithKey 98.605446%; 147/147 instructions, structure/operands (0, 34); 3 successful distinct source attempts; register allocation and commutative operand selection; declaration/lifetime/const views did not make it exact.

src/BS2/BS2Update: instruction-exact 9; code 400 -> 400 / 4052; data 10488 -> 10488 / 10488.
- UpdateThread 93.90471%; 905/913 instructions, structure/operands (94, 747); 5 successful distinct source attempts; eight instructions short; loop and local lifetimes remain different after the proven volatile reload fix.

src/channelScript/CHANSVm: instruction-exact 221; code 37608 -> 37608 / 53564; data 6904 -> 6904 / 6904.
- CHANSVmConvertToFloatFromStr 97.59036%; 83/83 instructions, structure/operands (2, 2); 6 successful distinct source attempts; instruction scheduling or control-flow shape differs.
- VmDateDtor 94.96703%; 91/91 instructions, structure/operands (5, 7); 3 successful distinct source attempts; instruction scheduling or control-flow shape differs.
- VmStringReplace 97.992424%; 132/132 instructions, structure/operands (0, 40); 3 successful distinct source attempts; register allocation and commutative operand selection; declaration/lifetime/const views did not make it exact.
- VmStringSplit 98.04054%; 222/222 instructions, structure/operands (0, 66); 3 successful distinct source attempts; register allocation and commutative operand selection; declaration/lifetime/const views did not make it exact.
- CHANSVmFormatString 99.84919%; 431/431 instructions, structure/operands (0, 13); 4 successful distinct source attempts; register allocation and commutative operand selection; declaration/lifetime/const views did not make it exact.
- VmBlobGetHexString 98.71951%; 82/82 instructions, structure/operands (0, 14); 3 successful distinct source attempts; register allocation and commutative operand selection; declaration/lifetime/const views did not make it exact.
- VmBlobPackCommon 97.949104%; 668/668 instructions, structure/operands (0, 244); 3 successful distinct source attempts; register allocation and commutative operand selection; declaration/lifetime/const views did not make it exact.
- VmBlobUnpack 98.452614%; 517/517 instructions, structure/operands (0, 141); 3 successful distinct source attempts; register allocation and commutative operand selection; declaration/lifetime/const views did not make it exact.
- VmWinEmuWrite 99.62687%; 67/67 instructions, structure/operands (0, 5); 3 successful distinct source attempts; register allocation and commutative operand selection; declaration/lifetime/const views did not make it exact.
- CHANSVmAddExe 99.625984%; 254/254 instructions, structure/operands (0, 16); 3 successful distinct source attempts; register allocation and commutative operand selection; declaration/lifetime/const views did not make it exact.
- CHANSVmLinkModules 98.677246%; 189/189 instructions, structure/operands (0, 43); 3 successful distinct source attempts; register allocation and commutative operand selection; declaration/lifetime/const views did not make it exact.
- CHANSVmStep 96.46608%; 1253/1253 instructions, structure/operands (65, 313); 4 successful distinct source attempts; opcode branch/local layout differs; pretested loop attempts lowered the data measure and were restored.

No exact-function gain in this round. Retained fuzzy improvements: BS2Tick 98.230415 -> 98.6768; AOSS_Init_old 93.78725 -> 94.48674; UpdateThread 93.59803 -> 93.90471; VmStringReplace 97.878784 -> 97.992424. Unit code/data match counts did not change. No configure/symbol extent edits, no new assembly, no push/PR or other worktree operations. All edits remain in the four owned C files and this log. The pre-existing fz18.attempts.md was preserved.

# MAX continuation from 84867e93
Priority: BS2Tick, AOSS_Init_old, UpdateThread, VmStringReplace. No exact claims without gate evidence; structural blocks before declaration search.
src/BS2/BS2Mach continuation pool: POOL IDENTICAL up to 91 (mine=91 base=91)
src/scene/setting/AOSS continuation pool: POOL IDENTICAL up to 1 (mine=1 base=1)
src/BS2/BS2Update continuation pool: POOL IDENTICAL up to 55 (mine=55 base=55)
src/channelScript/CHANSVm continuation pool: POOL IDENTICAL up to 125 (mine=125 base=125)

## src/BS2/BS2Mach::BS2Tick
Remote 29fe1efa, owned source UNCHANGED, local objdiff 98.6768%.
Structural audit: instructions 1936/1940, structural/operand (119, 1702).
Block audit MAX: frame 0x70 matches. First differences at instructions38-53 are progress/partition/cover stores and constant scheduling; no immediate reload proves additional volatility. Case5 is missing two independent low-memory base loads; case9 disc-title base is hoisted ahead of magic test; case0xb streaming load is scheduled after state store. Later two missing unconditional branches and loader output field-load order remain.
- ATTEMPT BS2Tick: initialize progress through the freshly assigned progress pointer rather than a second absolute lvalue; source 869aad1e235f; 98.6768%; instructions 1936/1940; structural/operand (119, 1702); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: initialize transfer flag before partition reset and cover state after disk-presence snapshot; source 47b9d7e2def3; 98.6299%; instructions 1936/1940; structural/operand (117, 1704); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: create the disc-title read-only view only inside the Revolution magic branch; source b0d211abd366; 98.66392%; instructions 1936/1940; structural/operand (114, 1702); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: load the streaming decision before clearing the audio-buffer state; source 145217e14adc; 98.671646%; instructions 1936/1940; structural/operand (119, 1702); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: view the console hardware word as the existing OSBootInfo consoleType field; source ab02c01748ef; BUILD FAILED ibs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -W nomissingreturn -ipa file -gccinc -fp_contract off -O4,s -enc SJIS -lang=c -MMD -c src/BS2/BS2Mach.c -o build/43U/src/src/BS2 && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/BS2/BS2Mach.d build/43U/src/src/BS2/BS2Mach.d ### mwcceppc.exe Compiler: #    File: src\BS2\BS2Mach.c # -------------------------- #    1392:             if ((((const OSBootInfo *)0x80000000)->consoleType & 0xf0000000) == 0)  #   Error:                                     ^ #   (10115) ')' expected #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. ; restored.
- ATTEMPT BS2Tick: reset partition progress and cover through typed writable helper parameters; source 951fea4f79f5; 98.6768%; instructions 1936/1940; structural/operand (119, 1702); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: put title-prefix acceptance and region dispatch in one read-only title helper; source 6da0db03d000; 98.6768%; instructions 1936/1940; structural/operand (119, 1702); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: use the SDK console structure and SDK device-code object for both hardware accesses; source b5e249de0a3e; 98.6768%; instructions 1936/1940; structural/operand (119, 1702); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: make the GameCube streaming header an immutable view; source e5b308c14018; 98.6768%; instructions 1936/1940; structural/operand (119, 1702); exact 24; data 155504; regress []; restored.

## src/scene/setting/AOSS::AOSS_Init_old
Remote 2d9e3ee1, owned source UNCHANGED, local objdiff 94.48674%.
Structural audit: instructions 1570/1584, structural/operand (154, 1510).
- ATTEMPT BS2Tick: express title-prefix acceptance as the two explicit accepting exits; source 9d5ea2e488cf; 98.547424%; instructions 1937/1940; structural/operand (115, 1699); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: publish the loader address before the loader length as in the target load order; source 715eaa5af0d3; 98.67783%; instructions 1936/1940; structural/operand (117, 1700); exact 24; data 155504; regress []; RETAINED.
- ATTEMPT BS2Tick: keep the initial progress address in its native pointer local until the reset store; source a35e1c93cd04; 98.67783%; instructions 1936/1940; structural/operand (117, 1700); exact 24; data 155504; regress []; restored.
MAX block audit: frame/local offsets match. Target has an additional second zero-result test at0x6f0 and a full cleanup return before allocation at0x734; current if/else collapsed that block. Target manufacturer-length branch has explicit branch-around-copy. Three connect loops use a second status test before the config flag. Poll timeout shows duplicate division and an explicit 64-bit zero carry; remaining stack stores precede clock read in a different order. SDK cleanup calls target compare <0, source writes -1<result.
- ATTEMPT AOSS_Init_old: restore the target second zero-result guard and independent cleanup before access-point allocation; source 9e90b4a698a7; 95.48232%; instructions 1587/1584; structural/operand (138, 1461); exact 15; data 3928; regress []; RETAINED.
- ATTEMPT AOSS_Init_old: use the transaction record field directly for rand and host-to-network conversion; source 7914992ed878; 95.655304%; instructions 1584/1584; structural/operand (130, 918); exact 16; data 3928; regress []; RETAINED.
- ATTEMPT AOSS_Init_old: compare socket cleanup results directly against zero; source 546cd099ab1e; 95.65909%; instructions 1584/1584; structural/operand (128, 918); exact 16; data 3928; regress []; RETAINED.
- ATTEMPT AOSS_Init_old: keep the final reconnect decrement in its explicit bounded-sleep branch form; source 338ebdc5a2ab; 95.91161%; instructions 1584/1584; structural/operand (123, 915); exact 16; data 3928; regress []; RETAINED.
Checkpoint cbd9898a: BS2Tick target loader output loads address then length; publication order changed accordingly. Quick Mach gate PASS, regression0, pools identical. 1936/1940 remains, objdiff98.6768 ->98.67783. No new hardware volatile declarations or helpers retained.
Retained setup guard proof: target0x6a0 compares NCD result once, branches0x6f0 on zero, then immediately branches0x734 on the same zero flag. Both intervening error paths free config/list and return-1. Source now preserves both guards and cleanup blocks; no dummy object or new call. Request field loads remove three extra instructions, yielding1584/1584. Raw gate16/21 includes already-objdiff100 ParseNetworkSettings now at its target offset; this is not a newly matched source function.
- ATTEMPT AOSS_Init_old: give the send dispatch its own result lifetime ending before polling; source bf3e41e05d18; 95.91161%; instructions 1584/1584; structural/operand (123, 915); exact 16; data 3928; regress []; restored.
- ATTEMPT AOSS_Init_old: use unsigned host-state comparisons in both reconnect loops; source 23352e349173; 95.809975%; instructions 1584/1584; structural/operand (121, 914); exact 16; data 3928; regress []; restored.
- ATTEMPT AOSS_Init_old: use a direct nonnegative test for the final socket cleanup; source cb4fece669a6; 95.915405%; instructions 1584/1584; structural/operand (121, 913); exact 16; data 3928; regress []; RETAINED.
- ATTEMPT AOSS_Init_old: assign the message opcode before the reserved byte to keep their distinct values live; source 1467c2b23c1d; 95.9173%; instructions 1584/1584; structural/operand (125, 913); exact 16; data 3928; regress []; RETAINED.
- ATTEMPT AOSS_Init_old: widen the microsecond product before the tick right shift and carry addition; source 8bb2dd51b2bd; 95.9173%; instructions 1584/1584; structural/operand (125, 913); exact 16; data 3928; regress []; restored.

## src/BS2/BS2Update::UpdateThread
Remote 7851b2b2, owned source UNCHANGED, local objdiff 93.90471%.
Structural audit: instructions 905/913, structural/operand (94, 747).
MAX block audit UpdateThread: target913/source905, frame0xf0 matches. Four missing instructions are State=5 stores eliminated before final selected-count test; source has those writes, suggesting a selection-helper boundary. Seat-pointer arithmetic uses addis instead of target lis/add twice. Target reloads selected entry type between zero/type-one tests. Error logging derives base anew. Capacity/local declaration order is secondary to these differences.
- ATTEMPT UpdateThread: separate entry selection into its typed inline return boundary before the worker import loop; source b3c58dd43faa; 93.95947%; instructions 905/913; structural/operand (94, 747); exact 9; data 10488; regress []; RETAINED.
- ATTEMPT UpdateThread: read the type-one discriminator through the published current entry; source a4fc190f5b59; BUILD FAILED EBUG=1 -DTARGET_RVL -W nomissingreturn -ipa file -gccinc -fp_contract off -O4,s -enc SJIS -lang=c -MMD -c src/BS2/BS2Update.c -o build/43U/src/src/BS2 && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/BS2/BS2Update.d build/43U/src/src/BS2/BS2Update.d Traceback (most recent call last):   File "/mnt/drive2/projects/wii-ipl-workers/w0929-fix-board/tools/transform_dep.py", line 84, in <module>     main()   File "/mnt/drive2/projects/wii-ipl-workers/w0929-fix-board/tools/transform_dep.py", line 77, in main     output = import_d_file(args.d_file)              ^^^^^^^^^^^^^^^^^^^^^^^^^^   File "/mnt/drive2/projects/wii-ipl-workers/w0929-fix-board/tools/transform_dep.py", line 31, in import_d_file     with open(in_file) as file:          ^^^^^^^^^^^^^ FileNotFoundError: [Errno 2] No such file or directory: 'build/43U/src/src/BS2/BS2Update.d' ninja: build stopped: subcommand failed. ; restored.
- ATTEMPT UpdateThread: clear current-entry pointer before publishing completion progress; source d04823cb1529; 93.97043%; instructions 905/913; structural/operand (94, 747); exact 9; data 10488; regress []; RETAINED.
- ATTEMPT UpdateThread: recheck the published current-entry type after the zero-type branch; source 3cacd17bf8b9; 93.948524%; instructions 906/913; structural/operand (94, 747); exact 9; data 10488; regress []; restored.
- ATTEMPT UpdateThread: give the worker import loop a const entry view after selecting writable entries; source 2c210a0ec798; 93.83899%; instructions 905/913; structural/operand (95, 747); exact 9; data 10488; regress []; restored.
- ATTEMPT UpdateThread: derive the two seat-array cursors as separate base and entry-count steps; source bd0e352d40b9; 94.278206%; instructions 906/913; structural/operand (83, 746); exact 9; data 10488; regress []; RETAINED.
- ATTEMPT UpdateThread: reset cancellation before start while the selection helper initializes its counters; source 6800170e5598; 94.278206%; instructions 906/913; structural/operand (83, 746); exact 9; data 10488; regress []; restored.

## src/channelScript/CHANSVm::VmStringReplace
Remote 63f4c7ae, owned source UNCHANGED, local objdiff 97.992424%.
Structural audit: instructions 132/132, structural/operand (0, 40).
Checkpoint: continued AOSS setup now95.9173%, target-length1584insns; UpdateThread typed selection boundary and explicit seat cursors94.278206%,906/913insns. Four-unit quick gate PASS, regression0, forbidden0, readability0. Artifact /tmp/big1.max.checkpoint1.txt. All unit matched code/data bytes unchanged; AOSS raw instruction-exact16 is the known CR1-normalization artifact disappearing, not a new objdiff-exact source function.
MAX structural audit VmStringReplace:132/132 instructions, frame0x40, branch topology and operand-independent sequence match. Remaining40 operand changes are VM/return/argument and payload/cursor register assignments. C89-correct payload const/lifetime trials precede first declaration search on the current source.
- ATTEMPT VmStringReplace: cache the three actual payloads in const typed views declared at function entry; source d1c16fee5c88; 97.992424%; instructions 132/132; structural/operand (0, 45); exact 221; data 6904; regress []; restored.
- ATTEMPT VmStringReplace: end the converted-object lifetimes after capturing their payload fields; source f95c78ffa31b; 97.992424%; instructions 132/132; structural/operand (0, 40); exact 221; data 6904; regress []; restored.
- ATTEMPT VmStringReplace: limit the tail-segment length to the trailing-copy block; source 6dae86b9c20d; 97.992424%; instructions 132/132; structural/operand (0, 40); exact 221; data 6904; regress []; restored.
- ATTEMPT VmStringReplace: express the source and destination offset advances as assignments to their old values; source b87ac8404da8; 97.992424%; instructions 132/132; structural/operand (0, 40); exact 221; data 6904; regress []; restored.

DECLSEARCH VmStringReplace: source-level structure and const/lifetime trials exhausted; run declaration-order search, maximum 300 evaluations.
Continuation data audit: AOSS .sdata2 bytes ffffffff00000000, sh_align8. Init relocations at0x24c/0x254 address target halfwords at+0/+2; real source s_defaultOptions currently size8 at+0 and both relocs use its base. This is a structural load-boundary difference despite already100% unit data. No metadata rename/extent is justified unless a candidate emits same bytes and independent real objects at+0/+2. Mach remaining3024 bytes are pooled literals and four jump tables, whose code relocation targets are still nonexact; all three other units already have100% data. No config edit made.
- ATTEMPT AOSS_Init_old: audit real independent halfword default objects and their emitted offsets before any symbol rename; source 03ab1c03df1a; 96.28156%; instructions 1583/1584; structural/operand (112, 963); exact 15; data 3920; regress ['AOSSParseNetworkSettings']; restored.
Independent defaults data audit: emitted .sdata2 ffff0000ffff, objects [('', 0, 0), ('s_defaultConnection', 0, 2), ('s_defaultResponse', 4, 2)]. Any unequal byte order or offset prevents a name-only correction; addresses are not to be moved.
- ATTEMPT AOSS_Init_old: put the network-settings copy and overlong-manufacturer exit in a typed inline builder; source 87329728c23c; 94.3952%; instructions 1563/1584; structural/operand (145, 1526); exact 15; data 3928; regress ['AOSSParseNetworkSettings']; restored.
- ATTEMPT AOSS_Init_old: derive the request record after rand has produced the transaction value; source 71aa914f1bb8; 95.96149%; instructions 1584/1584; structural/operand (124, 912); exact 16; data 3928; regress []; RETAINED.
- ATTEMPT AOSS_Init_old: compute the subnet broadcast bound before the next-host candidate; source b5ef29f88a8e; 96.09154%; instructions 1584/1584; structural/operand (121, 911); exact 16; data 3928; regress []; RETAINED.
- ATTEMPT BS2Tick: snapshot disk presence before the volatile cover-state reset in the initialization block; source 3592347b5692; 98.77062%; instructions 1936/1940; structural/operand (115, 1701); exact 24; data 155504; regress []; RETAINED.
- ATTEMPT BS2Tick: combine both target conditional transition shapes rather than score either jump shift in isolation; source 31a2e79d4f84; 98.66289%; instructions 1938/1940; structural/operand (43, 1704); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: use one const boot-disc view across the magic and audio-buffer cases with title view scoped to the magic branch; source 6dc24f2d9e8a; BUILD FAILED libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -W nomissingreturn -ipa file -gccinc -fp_contract off -O4,s -enc SJIS -lang=c -MMD -c src/BS2/BS2Mach.c -o build/43U/src/src/BS2 && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/BS2/BS2Mach.d build/43U/src/src/BS2/BS2Mach.d ### mwcceppc.exe Compiler: #    File: src\BS2\BS2Mach.c # -------------------------- #    1458:         u32 audioBufferSize;  #   Error:         ^^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. ; restored.
Independent-default name audit is negative: two real u16[1] objects compile at source offsets0 and4, bytesffff0000ffff, size6; target halfwords are at0 and2 in8 bytes. This is not a name-only gap. No rename or extent correction retained. Source arrays restored. Prior AOSS trials that list ParseNetworkSettings as a regression reflect the previously established odiff CR1 rebasing artifact, not changed code.
- ATTEMPT BS2Tick: hold the two proven target branch shapes for follow-up block alignment rather than register-score selection; source 31a2e79d4f84; 98.66289%; instructions 1938/1940; structural/operand (43, 1704); exact 24; data 155504; regress []; RETAINED.
- ATTEMPT BS2Tick: write the device code from read-only boot and drive-info inputs across a single typed inline boundary; source ac4fac6065fb; 98.66289%; instructions 1938/1940; structural/operand (43, 1704); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: give both disc cases one read-only boot view with C89 declaration order and branch-scoped title view; source 9020631e669d; 99.013916%; instructions 1938/1940; structural/operand (38, 1704); exact 24; data 155504; regress []; RETAINED.
DECLSEARCH VmStringReplace: declaration block: |       CHANSVmObjHdr* arg0; |       CHANSVmObjHdr* arg1; |       vmString parentStr; |       vmString searchStr; |       vmString replaceStr; |       u32 parentLen; |       u32 srcOffs; |       u32 dstOffs; |       u32 searchLen; |       u32 replaceLen; |       u32 dstBufLen; |       vmString newStr; |       u32 segLen; | start (0, 40) | improved (0, 39) | improved (0, 37) | improved (0, 35) | improved (0, 34) | improved (0, 28) | best (0, 28) after 285 builds; kept in source: |     vmString replaceStr; |     vmString searchStr; |     vmString parentStr; |     u32 parentLen; |     u32 srcOffs; |     u32 searchLen; |     CHANSVmObjHdr* arg0; |     u32 dstOffs; |     CHANSVmObjHdr* arg1; |     u32 replaceLen; |     u32 dstBufLen; |     vmString newStr; |     u32 segLen; |  | regress [].
DECLSEARCH VmStringReplace: retained declaration order pending full gate; instruction-exact 221 -> 221.
- ATTEMPT AOSS_Init_old: initialize the actual wait-interval aggregate locally instead of loading an artificial four-element default array; source 44412852d753; 96.36048%; instructions 1583/1584; structural/operand (108, 964); exact 16; data 3920; regress []; restored.
- ATTEMPT AOSS_Init_old: use the timer conversion with native unsigned-wide seconds and microseconds products; source 63db745418c9; 95.97096%; instructions 1586/1584; structural/operand (138, 1238); exact 16; data 3928; regress []; restored.
- ATTEMPT AOSS_Init_old: derive the microsecond remainder from a second quotient after setting the poll event; source 7ce9eece1186; 96.09154%; instructions 1584/1584; structural/operand (121, 911); exact 16; data 3928; regress []; restored.
VmStringReplace declaration-order search:285 builds, 40 ->28 operand differences, structural0. Candidate objdiff 98.82576%, code 37608, data 6904; pending gate.
VmStringReplace def-use audit after declaration search: target loads parent payload then search payload and parentLen before searchLen. Current source loads search payload then parent; register-blind structure0 obscures this semantic operand-order divergence. Restore parent-first field capture before more register tuning.
- ATTEMPT VmStringReplace: load parent length before search length on the improved declaration order; source 62caace862eb; 98.82576%; instructions 132/132; structural/operand (0, 28); exact 221; data 6904; regress []; restored.
- ATTEMPT VmStringReplace: cache the parent-first immutable payloads before accessing the two lengths; source e9e0f446b0f7; 98.82576%; instructions 132/132; structural/operand (0, 28); exact 221; data 6904; regress []; restored.
- ATTEMPT VmStringReplace: carry the actual private VM view through argument and return-object calls; source 1b161afe60d4; 98.82576%; instructions 132/132; structural/operand (0, 28); exact 221; data 6904; regress []; restored.
- ATTEMPT VmStringReplace: use one converted-object definition for each argument with direct nested calls; source b68869ff4e67; 98.82576%; instructions 132/132; structural/operand (0, 28); exact 221; data 6904; regress []; restored.
- ATTEMPT BS2Tick: snapshot all loader outputs before publishing length then address then offset; source 96d0e4f4997b; 99.01134%; instructions 1938/1940; structural/operand (38, 1705); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: reset progress from the partition-reset expression through the typed progress pointer; source 87d17635de34; 99.013405%; instructions 1938/1940; structural/operand (41, 1704); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: dispatch the console class as a switch with independent SDK device-code branches; source 3e77d38da8c3; 99.03144%; instructions 1939/1940; structural/operand (39, 1696); exact 24; data 155504; regress []; RETAINED.
- ATTEMPT BS2Tick: snapshot the read-only streaming decision before clearing configuration state on the aligned branch layout; source 0b72694d4151; 98.97165%; instructions 1940/1940; structural/operand (33, 191); exact 24; data 155504; regress []; restored.
- ATTEMPT VmStringReplace: make both fully converted argument objects read-only views for all subsequent field loads; source aae0575dc38c; 98.82576%; instructions 132/132; structural/operand (0, 28); exact 221; data 6904; regress []; restored.
- ATTEMPT VmStringReplace: give the two-pass byte replacement a typed inline helper with read-only buffer inputs; source a4681b7b245b; 93.67424%; instructions 132/132; structural/operand (12, 74); exact 221; data 6904; regress []; restored.
- ATTEMPT VmStringReplace: capture each input string as its actual pointer-and-length pair; source b49d643b4456; 97.27273%; instructions 132/132; structural/operand (0, 52); exact 221; data 6904; regress []; restored.

## src/BS2/BS2Mach::BS2Tick
Remote f05f7bbc, owned source UNCHANGED, local objdiff 99.03144%.
Structural audit: instructions 1939/1940, structural/operand (39, 1696).
- ATTEMPT BS2Tick: capture the native streaming byte before resetting audio configuration without boolean normalization; source 62e2b885dae7; 99.02629%; instructions 1939/1940; structural/operand (39, 1696); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: write both SDK device-code branches through a typed inline setter with ordinary if topology; source 4ff71a4e24c2; 99.013916%; instructions 1938/1940; structural/operand (38, 1704); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: capture only the loader address before publishing the volatile length and address; source 664260dcee6e; 99.03918%; instructions 1939/1940; structural/operand (39, 1696); exact 24; data 155504; regress []; RETAINED.
- ATTEMPT BS2Tick: use an immutable disc pointer definition in the audio case and a separate magic-check view; source fe5540942653; 98.81753%; instructions 1939/1940; structural/operand (42, 1696); exact 24; data 155504; regress []; restored.

## src/scene/setting/AOSS::AOSS_Init_old
Remote a8ab2099, owned source UNCHANGED, local objdiff 96.09154%.
Structural audit: instructions 1584/1584, structural/operand (121, 911).
- ATTEMPT BS2Tick: sequence the reset writes with their dependent status tests as native comma expressions; source 416d5f589a87; 99.03918%; instructions 1939/1940; structural/operand (39, 1696); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: publish the typed read-only data TOC view before loading its count for reporting; source e24edf585527; 99.106186%; instructions 1939/1940; structural/operand (35, 1696); exact 24; data 155504; regress []; RETAINED.
- ATTEMPT BS2Tick: keep the real partition reset and proven volatile region read across a typed inline boundary; source 035cc9f94dbe; 99.106186%; instructions 1939/1940; structural/operand (35, 1696); exact 24; data 155504; regress []; restored.
Checkpoint3: Mach quick GATE PASS, target DOL SHA1, regressions0, forbidden0, readability0. BS2Tick99.013916 ->99.106186: SDK console-class branch, native loader-address capture, and read-only data-TOC publication. /tmp/big1.max.checkpoint3.txt. No exact count or matched-byte increase.
- ATTEMPT AOSS_Init_old: dispatch the bounded manufacturer copy as its actual zero-or-one case rather than a skip branch; source 7c3457cb28bc; 95.741165%; instructions 1591/1584; structural/operand (127, 1548); exact 16; data 3928; regress []; restored.
Connect topology proof: target0x7f8 bne810 followed immediately by0x7fc bne8fc with the same cmpwi0 flags; reconnect repeats at0xd50/0xd54 and final-connect block. Testing the nested result guard restores the missing second condition without adding any data or undefined value.
- ATTEMPT AOSS_Init_old: restore both result guards before the configuration flag in all three connect tests; source 5284e701f1db; 96.32513%; instructions 1587/1584; structural/operand (116, 1515); exact 16; data 3928; regress []; RETAINED.
- ATTEMPT AOSS_Init_old: capture the actual request-array byte base before entering the three-record initialization loop; source 14b53b87c5be; 96.268936%; instructions 1586/1584; structural/operand (117, 1395); exact 16; data 3928; regress []; restored.

## src/BS2/BS2Update::UpdateThread
Remote 6b95233f, owned source UNCHANGED, local objdiff 94.278206%.
Structural audit: instructions 906/913, structural/operand (83, 746).
- ATTEMPT UpdateThread: define the typed selection helper after its call so file IPA supplies the inline boundary; source c01fc560098e; 94.278206%; instructions 906/913; structural/operand (83, 746); exact 9; data 10488; regress []; restored.
- ATTEMPT UpdateThread: recheck the type-one case through the published entry on the explicit-seat-cursor layout; source 00b744a3eed3; 94.381165%; instructions 907/913; structural/operand (83, 745); exact 9; data 10488; regress []; RETAINED.
- ATTEMPT AOSS_Init_old: return the protocol send result directly from a typed inline handshake dispatch; source d48ef9b99a91; BUILD FAILED s/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -W nomissingreturn -ipa file -gccinc -fp_contract off -O4,s -enc SJIS -lang=c -O4,p -inline off -MMD -c src/scene/setting/AOSS.c -o build/43U/src/src/scene/setting && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/scene/setting/AOSS.d build/43U/src/src/scene/setting/AOSS.d ### mwcceppc.exe Compiler: #    File: src\scene\setting\AOSS.c # --------------------------------- #     419:     memcpy(messageIdentity,requestRecords->records[2],8);  #   Error:                                                        ^ #   (10209) illegal implicit conversion from 'struct AOSSRequestRecord' to #   'const void *' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. ; restored.
- ATTEMPT AOSS_Init_old: preserve the positive manufacturer-length branch followed by the common IP-setup continuation; source 453d818162df; 96.32513%; instructions 1587/1584; structural/operand (116, 1515); exact 16; data 3928; regress []; restored.
- ATTEMPT AOSS_Init_old: use native pointer-zero tests for both reconnect allocations; source 43454fbe3646; 96.49558%; instructions 1587/1584; structural/operand (114, 1515); exact 16; data 3928; regress []; RETAINED.
- ATTEMPT UpdateThread: give the import discriminator an explicit zero-type dispatch before the published type-one test; source b98142b126ed; 94.46988%; instructions 908/913; structural/operand (85, 746); exact 9; data 10488; regress []; RETAINED.
- ATTEMPT UpdateThread: load each import-error title through a const table-and-index inline helper; source 05215033703a; 94.282585%; instructions 908/913; structural/operand (87, 746); exact 9; data 10488; regress []; restored.
- ATTEMPT UpdateThread: pass the selection status output through the typed inline boundary before publishing the count; source de6d3c74a49b; 94.46988%; instructions 908/913; structural/operand (85, 746); exact 9; data 10488; regress []; restored.
- ATTEMPT AOSS_Init_old: correct the typed send-dispatch helper with the actual address of the third request record; source 8048fbbe5b03; 90.522095%; instructions 1487/1584; structural/operand (198, 1493); exact 16; data 3928; regress []; restored.
Checkpoint4: AOSS/Update quick GATE PASS, all pools identical, target DOL SHA1, regressions0, forbidden0, readability0. AOSS nested connection-result conditions match the three target double-bne blocks, pointer-null test restores cmpwi; Init96.09154 ->96.49558. Update rechecks published CurrentEntry and explicitly dispatches zero-type,94.278206 ->94.46988. No matched-byte or objdiff-exact gain. /tmp/big1.max.checkpoint4.txt.

## src/channelScript/CHANSVm::VmStringReplace
Remote a2a04605, owned source UNCHANGED, local objdiff 98.82576%.
Structural audit: instructions 132/132, structural/operand (0, 28).
DECLSEARCH BS2Tick: block-by-block structural work complete through loader/TOC publication; search native secondary locals after the target stack aggregate (1289-1300), max300.
- ATTEMPT VmStringReplace: carry the complete method through an inline helper with a formal const parent-object input; source a61f20789f6a; 96.666664%; instructions 132/132; structural/operand (0, 64); exact 221; data 6904; regress []; restored.
- ATTEMPT VmStringReplace: use the actual const byte-buffer types for all three replacement inputs; source 2aafce1f83f8; 98.82576%; instructions 132/132; structural/operand (0, 28); exact 221; data 6904; regress []; restored.
- ATTEMPT VmStringReplace: scope immutable converted-object pointer definitions to the input-capture block; source 487c8a8f31af; 98.82576%; instructions 132/132; structural/operand (0, 28); exact 221; data 6904; regress []; restored.

## src/BS2/BS2Mach::CheckBS2CommandStatus
Remote ffeed96e, owned source UNCHANGED, local objdiff 99.50739%.
Structural audit: instructions 406/406, structural/operand (2, 2).
DECLSEARCH BS2Tick: declaration block: |       DVDFileInfo bannerFile; |       u32 discRegion; |       s32 status; |       u64 currentTime; |       BOOL regionMatches; |       char productRegion; |       u32 iosHigh; |       char *ticketByte; |       u32 entryCount; |       u32 readInterruptsEnabled; |       u32 readAddress; |       const DVDGameTOC *dataToc; | start (35, 1696) | best (35, 1696) after 177 builds; source restored; best order was: |     DVDFileInfo bannerFile; |     u32 discRegion; |     s32 status; |     u64 currentTime; |     BOOL regionMatches; |     char productRegion; |     u32 iosHigh; |     char *ticketByte; |     u32 entryCount; |     u32 readInterruptsEnabled; |     u32 readAddress; |     const DVDGameTOC *dataToc; | ; 99.106186%; regress[]; RETAINED.
DECLSEARCH BS2Tick: block-by-block structural work complete through loader/TOC publication; search leading register locals before the target stack aggregate (1279-1283), max80.
DECLSEARCH BS2Tick: declaration block: |       u32 interruptsEnabled = OSDisableInterrupts(); |       u32 titleCode; |       const DVDDiskID *bootDisc; |       s32 titlePrefix; |       u8 titleCharacters[4]; | start (35, 1696) | best (35, 1696) after 23 builds; source restored; best order was: |     u32 interruptsEnabled = OSDisableInterrupts(); |     u32 titleCode; |     const DVDDiskID *bootDisc; |     s32 titlePrefix; |     u8 titleCharacters[4]; | ; 99.106186%; regress[]; RETAINED.

## src/channelScript/CHANSVm::CHANSVmConvertToFloatFromStr
Remote ffeed96e, owned source UNCHANGED, local objdiff 97.59036%.
Structural audit: instructions 83/83, structural/operand (2, 2).
- ATTEMPT CHANSVmConvertToFloatFromStr: define the parse end pointer before the input type initializer at the inline helper entry; source 6e14bf12ffd3; 95.180725%; instructions 83/83; structural/operand (2, 3); exact 221; data 6904; regress []; restored.
- ATTEMPT CHANSVmConvertToFloatFromStr: declare the parse helper input as a formal pointer to const rather than casting a local view; source ebf2e0ddb903; 97.59036%; instructions 83/83; structural/operand (2, 2); exact 221; data 6904; regress []; restored.
- ATTEMPT CHANSVmConvertToFloatFromStr: give the parse output its immutable formal pointer definition; source e94e39411c2d; 97.59036%; instructions 83/83; structural/operand (2, 2); exact 221; data 6904; regress []; restored.
Additional volatile audit: target request record stores at0x9a4 and0x9b4 have clrlwi16 between the first store and SOHtoNs, not an immediate memory reload. No transactionId qualifier change is supported; no new volatile field was added.
- ATTEMPT CheckBS2CommandStatus: declare the actual data TOC global as a pointer to its read-only input object; source 50723bf52f25; 99.50739%; instructions 406/406; structural/operand (2, 2); exact 24; data 155504; regress []; restored.
- ATTEMPT CheckBS2CommandStatus: declare the zero-or-one cache completion flag as its native BOOL type; source c874ab91a1d3; 99.50739%; instructions 406/406; structural/operand (2, 2); exact 24; data 155504; regress []; restored.
- ATTEMPT CheckBS2CommandStatus: compute the cache partition extent with its explicit 32-bit unsigned size operand; source 30e7aec0e44c; 99.50739%; instructions 406/406; structural/operand (2, 2); exact 24; data 155504; regress []; restored.

## src/BS2/BS2Mach::BS2StartGCGame
Remote a9a3f36c, owned source UNCHANGED, local objdiff 99.5614%.
Structural audit: instructions 228/228, structural/operand (2, 7).
- ATTEMPT BS2StartGCGame: define one immutable cover-block address outside the volatile status polling loop; source 83b6e72ca5e4; 97.82895%; instructions 228/228; structural/operand (4, 9); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2StartGCGame: poll cover status through a formal read-only command-block helper and precomputed address; source f0679e8dbefd; 97.82895%; instructions 228/228; structural/operand (4, 9); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2StartGCGame: keep the cover address before the explicit target polling label; source 20cf15703f86; 97.82895%; instructions 228/228; structural/operand (4, 9); exact 24; data 155504; regress []; restored.
Definition-level volatile candidate proof (Mach): target BS2DVDCallback0x114 stw State then0x118 lwz State, repeated at0x14c/0x150,0x19c/0x1a0,0x1c0/0x1c4. This supports auditing State at its definition; retain only if all prior exact functions remain exact.
- ATTEMPT BS2Tick: qualify the state object at its definition using four proven target store/reload pairs; source 832e7c9e8ddd; 98.93299%; instructions 1939/1940; structural/operand (39, 1698); exact 17; data 155504; regress ['BS2AbortStateMachine', 'BS2DVDCallback', 'BS2GetLockedTitles', 'BS2IsTitleAvailable', 'BS2NANDCallback', 'BS2StartLoadingTitle', 'CheckDVDCommandStatus']; restored.

## src/channelScript/CHANSVm::CHANSVmStep
Remote 8864436c, owned source UNCHANGED, local objdiff 96.46608%.
Structural audit: instructions 1253/1253, structural/operand (65, 313).
Definition-level volatile candidate proof (Step): target default inversion path0xc528 stw r29,0x18(r1), immediately0xc52c lwz r0,0x18(r1); this is the high half of the bit-not converted integer at stack18. Candidate qualifies only that actual local, never casts a use to volatile. Required disasm_fn dumps stop at paired-single saves; per-instruction target dump proves the pair.
- ATTEMPT CHANSVmStep: qualify the target-proven inversion local and its parser output pointer at their definitions; source 95db9aea7828; 96.46608%; instructions 1253/1253; structural/operand (65, 313); exact 221; data 6904; regress []; restored.
- ATTEMPT CHANSVmStep: keep the target-proven inversion local volatile while parsing through a distinct native unsigned output; source b4ecc8559b01; 96.01596%; instructions 1258/1253; structural/operand (156, 901); exact 221; data 2232; regress []; restored.
- ATTEMPT CHANSVmStep: give the signed float-conversion and bit-not local its native signed integer type; source ce1352fc7fea; 96.46608%; instructions 1253/1253; structural/operand (65, 313); exact 221; data 6904; regress []; restored.

## MAX continuation final audit
Every remaining function has at least three distinct successful semantic source trials, excluding all failed compilations, invalid Step countdown source85374133139a and incorrect AddExe payload source2dd735c854a6. Coverage regenerated from current report; 23 open functions. Additional declaration searches: VmStringReplace285 builds kept40->28 operand differences; BS2Tick177+23 builds found no improvement. New proven volatile candidates (Mach State and Step inversion local) were tested and restored; only the earlier target-proven EntriesCount qualifier remains.
Current continued-round fuzzy: BS2Tick98.6768 ->99.106186; AOSS_Init_old94.48674 ->96.49558; UpdateThread93.90471 ->94.46988; VmStringReplace97.992424 ->98.82576. Exact counts and matched code/data bytes unchanged. AOSS raw gate count is again15/21: sourceInit has three excess instructions, exposing the known CR1 branch-normalization offset artifact in already-objdiff100 ParseNetworkSettings. The transient16 count was never treated as a new source match.
Source review: only four owned C files and this attempts log changed. No shared header, config address/extent, generated report, compiler flags, assembly, pinned labels, volatile casts, register declarations, dummy data, other worktree or remote writes. All unsuccessful trials restored. Pre-existing untracked fz18.attempts.md left untouched. Running final full non-quick gate over all four units.

## MAX final full gate and remaining-function coverage
Full non-quick four-unit gate PASS. Raw clean-build evidence:

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/BS2/BS2Mach] pool: IDENTICAL
[src/BS2/BS2Mach] objdiff: code 4940/16980 data 155504/158528 functions 24/29 fuzzy 98.5597 linked code 0
[src/BS2/BS2Mach] instruction-exact functions: 24/29
[src/BS2/BS2Mach]   section .bss size 155232 match 100.0
[src/BS2/BS2Mach]   section .data size 3024 match None
[src/BS2/BS2Mach]   section .sbss size 240 match 100.0
[src/BS2/BS2Mach]   section .sdata size 32 match 100.0
[src/BS2/BS2Mach]   section .text size 16980 match 98.559715
[src/BS2/BS2Mach]   below 100: Run 16.744186
[src/BS2/BS2Mach]   below 100: BS2StartGame 98.72774
[src/BS2/BS2Mach]   below 100: BS2StartGCGame 99.5614
[src/BS2/BS2Mach]   below 100: CheckBS2CommandStatus 99.50739
[src/BS2/BS2Mach]   below 100: BS2Tick 99.106186
[src/BS2/BS2Mach] baseline: code 4940/16980 data 155504 functions 24 fuzzy 98.1595
[src/scene/setting/AOSS] pool: IDENTICAL
[src/scene/setting/AOSS] objdiff: code 6436/16192 data 3928/3928 functions 16/21 fuzzy 97.8377 linked code 0
[src/scene/setting/AOSS] instruction-exact functions: 15/21
[src/scene/setting/AOSS]   section .bss size 3496 match 100.0
[src/scene/setting/AOSS]   section .data size 368 match 100.0
[src/scene/setting/AOSS]   section .sbss size 32 match 100.0
[src/scene/setting/AOSS]   section .sdata size 24 match 100.0
[src/scene/setting/AOSS]   section .sdata2 size 8 match 100.0
[src/scene/setting/AOSS]   section .text size 16192 match 97.8377
[src/scene/setting/AOSS]   below 100: AOSS_Init_old 96.49558
[src/scene/setting/AOSS]   below 100: AOSSDecryptMessage 97.74143
[src/scene/setting/AOSS]   below 100: AOSSApplyAuthOptions 98.77193
[src/scene/setting/AOSS]   below 100: AOSSSendHelloRequest 92.190475
[src/scene/setting/AOSS]   below 100: AOSSXorBufferWithKey 98.605446
[src/scene/setting/AOSS] baseline: code 6436/16192 data 3928 functions 16 fuzzy 96.7779
[src/BS2/BS2Update] pool: IDENTICAL
[src/BS2/BS2Update] objdiff: code 400/4052 data 10488/10488 functions 9/10 fuzzy 95.0158 linked code 0
[src/BS2/BS2Update] instruction-exact functions: 9/10
[src/BS2/BS2Update]   section .bss size 9056 match 100.0
[src/BS2/BS2Update]   section .data size 1328 match 100.0
[src/BS2/BS2Update]   section .sbss size 80 match 100.0
[src/BS2/BS2Update]   section .sdata size 24 match 100.0
[src/BS2/BS2Update]   section .text size 4052 match 95.01579
[src/BS2/BS2Update]   below 100: UpdateThread 94.46988
[src/BS2/BS2Update] baseline: code 400/4052 data 10488 functions 9 fuzzy 94.2300
[src/channelScript/CHANSVm] pool: IDENTICAL
[src/channelScript/CHANSVm] objdiff: code 37608/53564 data 6904/6904 functions 221/233 fuzzy 99.3738 linked code 0
[src/channelScript/CHANSVm] instruction-exact functions: 221/233
[src/channelScript/CHANSVm]   section .data size 4672 match 100.0
[src/channelScript/CHANSVm]   section .rodata size 1432 match 100.0
[src/channelScript/CHANSVm]   section .sbss size 16 match 100.0
[src/channelScript/CHANSVm]   section .sdata size 600 match 100.0
[src/channelScript/CHANSVm]   section .sdata2 size 184 match 100.0
[src/channelScript/CHANSVm]   section .text size 53564 match 99.37376
[src/channelScript/CHANSVm]   below 100: CHANSVmConvertToFloatFromStr 97.59036
[src/channelScript/CHANSVm]   below 100: VmDateDtor 94.96703
[src/channelScript/CHANSVm]   below 100: VmStringReplace 98.82576
[src/channelScript/CHANSVm]   below 100: VmStringSplit 98.04054
[src/channelScript/CHANSVm]   below 100: CHANSVmFormatString 99.84919
[src/channelScript/CHANSVm]   below 100: VmBlobGetHexString 98.71951
[src/channelScript/CHANSVm]   below 100: VmBlobPackCommon 97.949104
[src/channelScript/CHANSVm]   below 100: VmBlobUnpack 98.452614
[src/channelScript/CHANSVm]   below 100: VmWinEmuWrite 99.62687
[src/channelScript/CHANSVm]   below 100: CHANSVmAddExe 99.625984
[src/channelScript/CHANSVm]   below 100: CHANSVmLinkModules 98.677246
[src/channelScript/CHANSVm]   below 100: CHANSVmStep 96.46608
[src/channelScript/CHANSVm] baseline: code 37608/53564 data 6904 functions 221 fuzzy 99.3644
regressions vs baseline: 0
global matched_code_percent: 90.71801 -> 90.71801
global fuzzy_match_percent: 99.57510 -> 99.58431
global complete_code_percent: 71.01273 -> 71.01273
global matched_data_percent: 99.36639 -> 99.36639
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
review note: src/BS2/BS2Update.c: volatile object declaration (orchestrator checks the target really re-reads it) (+1 net), e.g. static volatile u32 EntriesCount = 0;
GATE PASS
```


src/BS2/BS2Mach: exact-name objdiff functions 24/29; code 4940 -> 4940 / 16980; data 155504 -> 155504 / 158528.
- Run 16.744186%; 11/43 instructions, structure/operands (40, 42); 3 distinct successful source trials; ABI register clearing and stack/LR handoff need an assembly trampoline; new assembly is forbidden.
- BS2StartGame 98.72774%; 393/393 instructions, structure/operands (4, 10); 3 distinct successful source trials; initial low-memory publication scheduling and commutative integer/FP operand order remain.
- BS2StartGCGame 99.5614%; 228/228 instructions, structure/operands (2, 7); 7 distinct successful source trials; target inlines and hoists cover-state polling; correcting that boundary changes initial scheduling and clock-product operand order.
- CheckBS2CommandStatus 99.50739%; 406/406 instructions, structure/operands (2, 2); 7 distinct successful source trials; only the adjacent cache-completion store and partition-count shift are swapped; const input, flag type and unsigned-width trials did not change them.
- BS2Tick 99.106186%; 1939/1940 instructions, structure/operands (35, 1696); 39 distinct successful source trials; two device-base materializations missing, one extra console switch jump; remaining global load/store scheduling and register choices differ.

src/scene/setting/AOSS: exact-name objdiff functions 16/21; code 6436 -> 6436 / 16192; data 3928 -> 3928 / 3928.
- AOSS_Init_old 96.49558%; 1587/1584 instructions, structure/operands (114, 1515); 30 distinct successful source trials; manufacturer/connect/send/poll boundaries and constant hoisting differ; target r14 is read before assignment, while source keeps a defined initialization result.
- AOSSDecryptMessage 97.74143%; 321/321 instructions, structure/operands (0, 87); 3 distinct successful source trials; register allocation and commutative operand selection; const/lifetime trials and 300 declaration evaluations did not improve.
- AOSSApplyAuthOptions 98.77193%; 114/114 instructions, structure/operands (0, 22); 3 distinct successful source trials; register allocation and commutative operand selection; const/lifetime trials and 177 declaration evaluations did not improve.
- AOSSSendHelloRequest 92.190475%; 271/273 instructions, structure/operands (33, 254); 3 distinct successful source trials; two instructions short; global-base grouping, checksum unrolling and cipher lifetimes differ.
- AOSSXorBufferWithKey 98.605446%; 147/147 instructions, structure/operands (0, 34); 3 distinct successful source trials; register allocation and commutative operand selection; 118 declaration evaluations did not improve.

src/BS2/BS2Update: exact-name objdiff functions 9/10; code 400 -> 400 / 4052; data 10488 -> 10488 / 10488.
- UpdateThread 94.46988%; 908/913 instructions, structure/operands (85, 746); 16 distinct successful source trials; selection error State stores are eliminated, logging bases reused; indexed type reload and zero-case dispatch differ. Frame remains0xf0.

src/channelScript/CHANSVm: exact-name objdiff functions 221/233; code 37608 -> 37608 / 53564; data 6904 -> 6904 / 6904.
- CHANSVmConvertToFloatFromStr 97.59036%; 83/83 instructions, structure/operands (2, 2); 9 distinct successful source trials; only the adjacent end-pointer stack store and string-tag compare are swapped; formal const input and definition-order trials did not fix scheduling.
- VmDateDtor 94.96703%; 91/91 instructions, structure/operands (5, 7); 3 distinct successful source trials; argument setup and call/return scheduling differ.
- VmStringReplace 98.82576%; 132/132 instructions, structure/operands (0, 28); 17 distinct successful source trials; parent/search payload metadata load order and register allocation; frame/count/topology match. 285 declaration evaluations reduced40->28 operand differences.
- VmStringSplit 98.04054%; 222/222 instructions, structure/operands (0, 66); 3 distinct successful source trials; register allocation and operand selection after matching frame/count/topology.
- CHANSVmFormatString 99.84919%; 431/431 instructions, structure/operands (0, 13); 4 distinct successful source trials; register allocation; 300 declaration evaluations did not improve.
- VmBlobGetHexString 98.71951%; 82/82 instructions, structure/operands (0, 14); 3 distinct successful source trials; register allocation and byte-result temporary lifetime.
- VmBlobPackCommon 97.949104%; 668/668 instructions, structure/operands (0, 244); 3 distinct successful source trials; register allocation and commutative operand selection; loop/local/const trials did not fix.
- VmBlobUnpack 98.452614%; 517/517 instructions, structure/operands (0, 141); 3 distinct successful source trials; register allocation and commutative operand selection; loop/local/const trials did not fix.
- VmWinEmuWrite 99.62687%; 67/67 instructions, structure/operands (0, 5); 3 distinct successful source trials; register allocation; 71 declaration evaluations did not improve.
- CHANSVmAddExe 99.625984%; 254/254 instructions, structure/operands (0, 16); 3 distinct successful source trials; register allocation; 52 declaration evaluations did not improve. Incorrect payload-member trial excluded.
- CHANSVmLinkModules 98.677246%; 189/189 instructions, structure/operands (0, 43); 3 distinct successful source trials; register allocation; 13 declaration evaluations did not improve.
- CHANSVmStep 96.46608%; 1253/1253 instructions, structure/operands (65, 313); 7 distinct successful source trials; opcode countdown/branch/local layout differs; target-proven volatile inversion-local trials were identical or regressed. Invalid countdown trial excluded.

Final interpretation: zero new exact functions and unchanged matched code/data bytes. Continued-round gains are fuzzy, recorded above and committed only after GATE PASS. Raw instruction counts remain Mach24/29, AOSS15/21, Update9/10, Vm221/233. AOSSParseNetworkSettings is still exact in objdiff/proper disassembly; raw count15 reflects the existing CR1-normalization offset artifact. Data audit found no eligible name/extent correction. AOSS r14 read-before-assignment remains uncertain; no uninitialized source was introduced.
Changed files: src/BS2/BS2Mach.c, src/scene/setting/AOSS.c, src/BS2/BS2Update.c, src/channelScript/CHANSVm.c, tools/decomp-assist/big1.attempts.md. Continued source checkpoints: cbd9898a,746ce740,f4721a92,2e016fe1,2738dcf4,c4f1e876. Final log-only validation commit follows; no source change after the final full gate.

# MAX continuation 2 at 6778cff9
Continuation priorities: BS2Tick, AOSS_Init_old, UpdateThread, VmStringReplace; preserve existing exact functions and full data. Fresh baseline saved in /tmp/big1.max2-before.json.
Initial pools: BS2Mach 91/91, AOSS 1/1, BS2Update 55/55, CHANSVm 125/125, all identical.

## src/BS2/BS2Mach::BS2Tick
Remote e3457d11, owned source UNCHANGED, local objdiff 99.106186%.
Structural audit: instructions 1939/1940, structural/operand (35, 1696).
MAX2 block audit: first divergence remains case-0 materialization/store order (38-53); case-5 uses an extra switch branch and lacks two low-memory LIS instructions. Target frame and all stack locals remain matched. No new global qualifier proof exists except State, already audited; use typed source boundaries before register search.
- ATTEMPT BS2Tick: return the disk-presence snapshot from the typed reset helper after the actual volatile cover write; source 8b1dd7868930; 99.106186%; instructions 1939/1940; structural/operand (35, 1696); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: separate read-only console-class lookup from the two SDK device-code stores; source ca0be2a204de; 99.08866%; instructions 1938/1940; structural/operand (34, 1706); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: keep the next-state store at each real device-code branch exit rather than after switch dispatch; source d241bbcb5d28; 98.91083%; instructions 1940/1940; structural/operand (22, 78); exact 24; data 158528; regress []; restored.
- ATTEMPT BS2Tick: hold target-aligned duplicated next-state branch exits for block audit; restores full jump-table data pairing; source d241bbcb5d28; 98.91083%; instructions 1940/1940; structural/operand (22, 78); exact 24; data 158528; regress []; RETAINED.

## src/scene/setting/AOSS::AOSS_Init_old
Remote 26d7e1e0, owned source UNCHANGED, local objdiff 96.49558%.
Structural audit: instructions 1587/1584, structural/operand (114, 1515).
- ATTEMPT BS2Tick: give the audio reset a formal const disc input and actual mutable flag output across an inline boundary; source 51706ca013a6; 98.91083%; instructions 1940/1940; structural/operand (22, 78); exact 24; data 158528; regress []; restored.
- ATTEMPT BS2Tick: read the signed native console-class word before the device branches; source 3dd5f3192552; 98.91083%; instructions 1940/1940; structural/operand (22, 78); exact 24; data 158528; regress []; restored.
- ATTEMPT BS2Tick: keep device publication and next-state publication in one typed inline writer at both exits; source 96cba28ffab6; 98.91083%; instructions 1940/1940; structural/operand (22, 78); exact 24; data 158528; regress []; restored.
MAX2 AOSS audit: first genuine missing instruction is the manufacturer-copy branch-around; default constants still have a section-base load (data already exact). At dispatch compare0x135c target defers protocolState publication to0x1818; source publishes before branch, producing an extra MR and a different backedge. The changed non-2 state must still resume immediately, while unchanged state performs the retry wait; preserve that behavior.
- ATTEMPT AOSS_Init_old: express the bounded manufacturer copy as the single-iteration pretested block seen in target; source d0e4d1c40623; 96.33207%; instructions 1589/1584; structural/operand (118, 1553); exact 16; data 3928; regress []; restored.
- ATTEMPT AOSS_Init_old: defer changed protocol-state publication to its real common resume label after the reconnect path; source ddefbc8ec565; 96.59344%; instructions 1586/1584; structural/operand (110, 1516); exact 16; data 3928; regress []; RETAINED.
- ATTEMPT AOSS_Init_old: keep all immutable initialization input fields behind one const view while status writes use the output object; source 7ba2671cb31d; BUILD FAILED RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -W nomissingreturn -ipa file -gccinc -fp_contract off -O4,s -enc SJIS -lang=c -O4,p -inline off -MMD -c src/scene/setting/AOSS.c -o build/43U/src/src/scene/setting && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/scene/setting/AOSS.d build/43U/src/src/scene/setting/AOSS.d ### mwcceppc.exe Compiler: #    File: src\scene\setting\AOSS.c # --------------------------------- #     473:   s_runtime.config = readInput->ssid;  #   Error:                                     ^ #   (10209) illegal implicit conversion from 'const unsigned char[256]' to #   'void *' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. ; restored.
- ATTEMPT AOSS_Init_old: read only the scalar options and request identity through the const input view; retain mutable buffers on the output view; source 6a0e00ed01c3; 96.59344%; instructions 1586/1584; structural/operand (110, 1516); exact 16; data 3928; regress []; restored.
MAX2 device-branch hold rejected for promotion: data158528/158528 is caused by matching downstream label offsets, but source has duplicate State8 stores where target has one; fuzzy98.91083 falls below99.106186. Restore shared-store baseline and pursue actual control/materialization differences, rather than retain incidental alignment.
MAX2 checkpoint: AOSS quick GATE PASS (/tmp/big1.max2.gate-aoss1.txt), full build/DOL SHA1 exact, regressions0, forbidden0, readability0. Delayed protocol publication removes one extra MR: Init96.49558 ->96.59344,1587 ->1586 instructions; existing instruction-exact count unchanged. Mach incidental-alignment hold is restored.

## src/BS2/BS2Update::UpdateThread
Remote 26d7e1e0, owned source UNCHANGED, local objdiff 94.46988%.
Structural audit: instructions 908/913, structural/operand (85, 746).
MAX2 Update audit: first divergence is selection/start-reset scheduling. Frame0xf0 and scratch offsets match. Four State5 instructions are optimized away across the inline selection boundary; no immediate State store/reload or SDK qualifier proof authorizes volatility. The import zero-type switch has one extra jump; target reloads the indexed type again for case1. Test actual const access boundaries and natural if shape before register allocation.
- ATTEMPT UpdateThread: use the natural zero-type exit followed by an independent read-only indexed type view; source 1cd852a33e72; 94.70427%; instructions 907/913; structural/operand (82, 745); exact 9; data 10488; regress []; RETAINED.
- ATTEMPT UpdateThread: keep the second discriminator at a const table-and-index inline boundary after the natural zero-type exit; source 0aac9ab02e4d; 94.70427%; instructions 907/913; structural/operand (82, 745); exact 9; data 10488; regress []; restored.
- ATTEMPT UpdateThread: use a read-only view for the complete import phase after the natural zero-type exit; source 7abc6f85a058; 94.480835%; instructions 906/913; structural/operand (84, 746); exact 9; data 10488; regress []; restored.

## src/channelScript/CHANSVm::VmStringReplace
Remote 26d7e1e0, owned source UNCHANGED, local objdiff 98.82576%.
Structural audit: instructions 132/132, structural/operand (0, 28).
- ATTEMPT UpdateThread: derive import fields directly from the actual fixed entry table instead of retaining a mutable cursor; source 53077a1455ef; 92.79737%; instructions 906/913; structural/operand (98, 746); exact 9; data 10488; regress []; restored.
MAX2 checkpoint: Update quick GATE PASS, full build and target DOL SHA1, regressions0/forbidden0/readability0. Natural zero-type exit plus separate const indexed test:94.46988 ->94.70427,908 ->907/913 instructions, structure85 ->82, same9 exact and10488 data. No State qualifier introduced.
MAX2 Replace block audit: frame0x40,132 instructions and both replacement passes exactly shaped. Target parent-payload metadata loads precede search; source reverses them. Target VM/result use r27/r28, three buffers r31/r30/r29; source VM/result r30/r31 and buffers r26/r27/r28. Try formal/local ownership and const input boundaries, then declaration-order search on changed graphs only.
- ATTEMPT VmStringReplace: give execution, parent and result views actual local definitions separate from incoming parameters; source 2d0015e17a39; 98.82576%; instructions 132/132; structural/operand (0, 28); exact 221; data 6904; regress []; restored.
- ATTEMPT VmStringReplace: carry the VM and destination as the two fields of the execution view used by conversion and allocation; source 78eda6b2bebf; 98.82576%; instructions 132/132; structural/operand (0, 28); exact 221; data 6904; regress []; restored.
- ATTEMPT VmStringReplace: keep the actual parent metadata reads behind an independently declared const object view; source c8737f3f6078; 98.82576%; instructions 132/132; structural/operand (0, 28); exact 221; data 6904; regress []; restored.
- ATTEMPT VmStringReplace: give the three native byte strings their read-only char pointer definitions without payload intermediates; source 0faf43351030; 98.82576%; instructions 132/132; structural/operand (0, 28); exact 221; data 6904; regress []; restored.
- ATTEMPT VmStringReplace: read the UTF16 payload through its actual wide-string union view while retaining byte offsets for copies; source 932669fa8ba1; 98.82576%; instructions 132/132; structural/operand (0, 28); exact 221; data 6904; regress []; restored.
- ATTEMPT VmStringReplace: read parent-first string metadata through const formal object parameters in small inline accessors; source b5aa06d9aebe; 98.068184%; instructions 132/132; structural/operand (0, 38); exact 221; data 6904; regress []; restored.
- ATTEMPT VmStringReplace: define immutable parent-first payload metadata at the start of the validated replacement block; source a557f3f0ea3d; 97.083336%; instructions 132/132; structural/operand (0, 54); exact 221; data 6904; regress []; restored.
- ATTEMPT VmStringReplace: hold const-formal metadata accessors for declaration-order search on the new read-only graph; source b5aa06d9aebe; 98.068184%; instructions 132/132; structural/operand (0, 38); exact 221; data 6904; regress []; RETAINED.
MAX2 DECLSEARCH Replace const-accessor graph: frame/count/branches already exact; maximum400 declaration evaluations after the metadata-boundary trials.
MAX2 DECLSEARCH const-accessor result: declaration block: |       vmString replaceStr; |       vmString searchStr; |       vmString parentStr; |       u32 parentLen; |       u32 srcOffs; |       u32 searchLen; |       CHANSVmObjHdr* arg0; |       u32 dstOffs; |       CHANSVmObjHdr* arg1; |       u32 replaceLen; |       u32 dstBufLen; |       vmString newStr; |       u32 segLen; | start (0, 38) | improved (0, 36) | improved (0, 33) | improved (0, 31) | best (0, 31) after 326 builds; kept in source: |     u32 searchLen; |     vmString searchStr; |     u32 parentLen; |     u32 srcOffs; |     vmString replaceStr; |     CHANSVmObjHdr* arg0; |     u32 dstOffs; |     CHANSVmObjHdr* arg1; |     u32 replaceLen; |     u32 dstBufLen; |     vmString parentStr; |     vmString newStr; |     u32 segLen; | .
MAX2 DECLSEARCH accessor graph final (0, 31), fuzzy98.75; restored original28-operand state.
- ATTEMPT VmStringReplace: hold the complete formal-const parent helper for declaration search after its frame and control flow passed; source a61f20789f6a; 96.666664%; instructions 132/132; structural/operand (0, 64); exact 221; data 6904; regress []; RETAINED.
MAX2 DECLSEARCH Replace formal-const parent helper: matched frame/count/branch topology, maximum400 evaluations of the real helper locals, wrapper signature unchanged.
MAX2 DECLSEARCH parent-helper result: declaration block: |       vmString replaceStr; |       vmString searchStr; |       vmString parentStr; |       u32 parentLen; |       u32 srcOffs; |       u32 searchLen; |       CHANSVmObjHdr* arg0; |       u32 dstOffs; |       CHANSVmObjHdr* arg1; |       u32 replaceLen; |       u32 dstBufLen; |       vmString newStr; |       u32 segLen; | start (0, 64) | improved (0, 62) | improved (0, 61) | improved (0, 38) | improved (0, 37) | improved (0, 32) | improved (0, 23) | improved (0, 21) | improved (0, 16) | improved (0, 6) | best (0, 6) after 400 builds; kept in source: |     CHANSVmObjHdr* arg0; |     vmString replaceStr; |     vmString searchStr; |     vmString parentStr; |     vmString newStr; |     u32 dstBufLen; |     u32 replaceLen; |     u32 dstOffs; |     CHANSVmObjHdr* arg1; |     u32 searchLen; |     u32 srcOffs; |     u32 parentLen; |     u32 segLen; | .
MAX2 DECLSEARCH parent-helper final (0, 6), fuzzy99.77273; retained pending gate.
MAX2 native type audit: AudioBufferUnconfigured, LoadingTitle, PartitionOpen and RestartRequested are only assigned0/1; use real BOOL definitions as an alternative alias/type graph. DvdProgress is only cleared or tested as a signed word. No volatile qualification or dummy store is involved.
- ATTEMPT BS2Tick: declare the audio configuration flag with its actual BOOL value domain; source a8faa86d122a; 99.106186%; instructions 1939/1940; structural/operand (35, 1696); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: declare restart, partition and title-loading state flags with their native BOOL type; source 6edf878867ab; 99.106186%; instructions 1939/1940; structural/operand (35, 1696); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: give the cleared and signed-tested progress word its signed native pointer type; source c6561d62de5e; 99.106186%; instructions 1939/1940; structural/operand (35, 1696); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: carry system-clock instants in the SDK OSTime type used by all signed deadline comparisons; source 1e679def56c9; 99.106186%; instructions 1939/1940; structural/operand (35, 1696); exact 24; data 155504; regress []; restored.

## src/channelScript/CHANSVm::VmStringReplace
Remote 2d3bc63c, owned source UNCHANGED, local objdiff 99.77273%.
Structural audit: instructions 132/132, structural/operand (0, 6).
MAX2 Replace final six operands: formal-const parent helper now matches every register assignment and control-flow instruction; only parent/search metadata load ordering differs. Re-test source order on this new graph before another declaration search.
- ATTEMPT VmStringReplace: read parent length before search length on the matched const-parent helper graph; source 746260e487a0; 99.77273%; instructions 132/132; structural/operand (0, 6); exact 221; data 6904; regress []; restored.
- ATTEMPT VmStringReplace: read complete parent metadata before the search payload on the const-parent graph; source 909649390f5a; 99.77273%; instructions 132/132; structural/operand (0, 6); exact 221; data 6904; regress []; restored.
- ATTEMPT VmStringReplace: retain actual const parent and search payload views before extracting their lengths and buffers; source a53b6dcac429; 100.0%; instructions 132/132; structural/operand (0, 0); exact 222; data 6904; regress []; RETAINED.
MAX2 EXACT VmStringReplace: formal-const parent helper plus explicit const payload views resolves both inline-boundary register allocation and metadata scheduling. objdiff100.0,132/132 instructions,ctxdiff0,pool125/125 identical; unit222/233 raw exact,38136/53564 matched code,6904/6904 data. All-unit quick gate /tmp/big1.max2.gate-replace1.txt: GATE PASS, full43U build/targetDOL SHA1, regression0/forbidden0/readability0. Public method symbol and VM callback signature remain unchanged.

## src/scene/setting/AOSS::AOSS_Init_old
Remote 449529d9, owned source UNCHANGED, local objdiff 96.59344%.
Structural audit: instructions 1586/1584, structural/operand (110, 1516).
MAX2 AOSS continuation: first copy guard is target BLE-copy then unconditional skip; source BGT-skip. Scalar const locals did not change aliasing; test actual switch shape and formal const scalar-input boundary, with writable ssid/status supplied separately.
- ATTEMPT AOSS_Init_old: use the boolean manufacturer-copy dispatch with one genuine copy case and a default exit; source 314d0c31b90b; 96.11301%; instructions 1593/1584; structural/operand (116, 1561); exact 16; data 3928; regress []; restored.
- ATTEMPT AOSS_Init_old: supply initialization scalars through a formal const input while the real status and ssid output use their writable view; source 8ba94f246fff; BUILD FAILED OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -W nomissingreturn -ipa file -gccinc -fp_contract off -O4,s -enc SJIS -lang=c -O4,p -inline off -MMD -c src/scene/setting/AOSS.c -o build/43U/src/src/scene/setting && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/scene/setting/AOSS.d build/43U/src/src/scene/setting/AOSS.d ### mwcceppc.exe Compiler: #    File: src\scene\setting\AOSS.c # --------------------------------- #    1404:     protocolResult = AOSSValidateInitConfig(input);  #   Error:                                                  ^ #   (10209) illegal implicit conversion from 'const struct AOSSInitInput *' to #   'struct AOSSInitInput *' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. ; restored.
- ATTEMPT AOSS_Init_old: retain the immutable authentication request record across its identity-copy boundary; source 45d38dad82d3; 96.58586%; instructions 1586/1584; structural/operand (112, 1516); exact 16; data 3928; regress []; restored.
- ATTEMPT AOSS_Init_old: dispatch all supported native manufacturer lengths directly, avoiding boolean materialization; source 896c92d95c18; 96.486115%; instructions 1589/1584; structural/operand (112, 1539); exact 16; data 3928; regress []; restored.
- ATTEMPT AOSS_Init_old: read the existing default halfwords through their native wait-settings union rather than array element addressing; source 674300c90fc5; 96.59344%; instructions 1586/1584; structural/operand (110, 1516); exact 16; data 3928; regress []; restored.

## src/channelScript/CHANSVm::CHANSVmConvertToFloatFromStr
Remote 449529d9, owned source UNCHANGED, local objdiff 97.59036%.
Structural audit: instructions 83/83, structural/operand (2, 2).
MAX2 Float audit:83/83 instructions,frame0x70,end pointer8 and text buffer12 match; only initial type comparison and end-pointer zero store are swapped. No immediate store/reload proves volatility. Test caller return shape and real parse scratch aggregate before register search.
- ATTEMPT CHANSVmConvertToFloatFromStr: return failed parses directly while the allocated result has one immutable local definition; source 0a880fd10234; 95.481926%; instructions 84/83; structural/operand (6, 12); exact 221; data 6904; regress ['VmBlobFill']; restored.
- ATTEMPT CHANSVmConvertToFloatFromStr: keep the end pointer and converted text in the native parser scratch record; source aeebfa0fe322; 97.59036%; instructions 83/83; structural/operand (2, 2); exact 222; data 6904; regress []; restored.
- ATTEMPT CHANSVmConvertToFloatFromStr: carry the complete string conversion through a formal const input boundary while preserving the public callback signature; source 9e89a701c621; 97.59036%; instructions 83/83; structural/operand (2, 2); exact 222; data 6904; regress []; restored.

## src/BS2/BS2Update::UpdateThread
Remote 449529d9, owned source UNCHANGED, local objdiff 94.70427%.
Structural audit: instructions 907/913, structural/operand (82, 745).
MAX2 Update continuation: early State5 stores are removed across the count-return boundary, even though final volatile EntriesCount store/reload matches. Test genuine selection output parameters; no State volatility is proven.
- ATTEMPT UpdateThread: write the actual selection phase through a typed output parameter across the selection boundary; source 636b9e8d9fe3; 94.70427%; instructions 907/913; structural/operand (82, 745); exact 9; data 10488; regress []; restored.
- ATTEMPT UpdateThread: publish the selected count through its proven volatile destination at the selection boundary before the worker tests it; source b13425bc38d9; 94.70427%; instructions 907/913; structural/operand (82, 745); exact 9; data 10488; regress []; restored.
- ATTEMPT UpdateThread: return directly from the two actual selection failures that target publishes before leaving selection; source 3da6da199fa1; 94.70427%; instructions 907/913; structural/operand (82, 745); exact 9; data 10488; regress []; restored.

## src/scene/setting/AOSS::AOSSSendHelloRequest
Remote 449529d9, owned source UNCHANGED, local objdiff 92.190475%.
Structural audit: instructions 271/273, structural/operand (33, 254).
MAX2 Hello audit:frame/count271/273 and checksum/cipher traversal retain structural differences; packet request is read-only for its entire lifetime, but only a const local view was tested previously. Test the formal read-only contract without changing writable payload/schedule.
- ATTEMPT AOSSSendHelloRequest: declare the whole hello-request input formally const and keep the writable response separate; source 1d377c6e2603; 92.190475%; instructions 271/273; structural/operand (33, 254); exact 16; data 3928; regress []; restored.

## src/scene/setting/AOSS::AOSSXorBufferWithKey
Remote 449529d9, owned source UNCHANGED, local objdiff 98.605446%.
Structural audit: instructions 147/147, structural/operand (0, 34).
MAX2 XOR audit:147/147 instructions,frame0x40 and register-blind structure0; surviving34 operands allocate packet/key/temp counters differently. The key is read-only throughout; test its formal const contract before further declaration-order work.
- ATTEMPT AOSSXorBufferWithKey: declare the actual encryption key as a formal read-only byte-string input; source 527206155ae8; 95.17007%; instructions 146/147; structural/operand (12, 108); exact 16; data 3928; regress []; restored.

## src/BS2/BS2Mach::BS2Tick
Remote 449529d9, owned source UNCHANGED, local objdiff 99.106186%.
Structural audit: instructions 1939/1940, structural/operand (35, 1696).
MAX2 Tick final structural trials: the current source is one instruction short; case5 has an extra switch jump and reuses the low-memory base. Target audio loads the streaming byte before publishing the clear flag. Test actual constant lifetimes and native branch publication, retaining no duplicated state store merely for table alignment.
- ATTEMPT BS2Tick: define the actual initialization audio-state value before resetting partition progress; source 83b5d8bd66f5; 99.0366%; instructions 1939/1940; structural/operand (35, 1709); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: publish audio configuration state at both actual streaming-configuration paths after reading the immutable header; source d872644b8b0b; 98.89742%; instructions 1941/1940; structural/operand (48, 1701); exact 24; data 155504; regress []; restored.
- ATTEMPT BS2Tick: compute the native drive device code before publishing it once through the SDK hardware object; source d43d983f8935; 98.957214%; instructions 1938/1940; structural/operand (37, 1703); exact 24; data 155504; regress []; restored.

## MAX2 final coverage before clean full gate
src/BS2/BS2Mach: objdiff exact functions 24 -> 24 / 29; code 4940 -> 4940 / 16980; data 155504 -> 155504 / 158528.
- COVERED Run 16.744186%; valid distinct source attempts 3.
- COVERED BS2StartGame 98.72774%; valid distinct source attempts 3.
- COVERED BS2StartGCGame 99.5614%; valid distinct source attempts 7.
- COVERED CheckBS2CommandStatus 99.50739%; valid distinct source attempts 7.
- COVERED BS2Tick 99.106186%; valid distinct source attempts 52.
src/scene/setting/AOSS: objdiff exact functions 16 -> 16 / 21; code 6436 -> 6436 / 16192; data 3928 -> 3928 / 3928.
- COVERED AOSS_Init_old 96.59344%; valid distinct source attempts 37.
- COVERED AOSSDecryptMessage 97.74143%; valid distinct source attempts 3.
- COVERED AOSSApplyAuthOptions 98.77193%; valid distinct source attempts 3.
- COVERED AOSSSendHelloRequest 92.190475%; valid distinct source attempts 4.
- COVERED AOSSXorBufferWithKey 98.605446%; valid distinct source attempts 4.
src/BS2/BS2Update: objdiff exact functions 9 -> 9 / 10; code 400 -> 400 / 4052; data 10488 -> 10488 / 10488.
- COVERED UpdateThread 94.70427%; valid distinct source attempts 23.
src/channelScript/CHANSVm: objdiff exact functions 221 -> 222 / 233; code 37608 -> 38136 / 53564; data 6904 -> 6904 / 6904.
- COVERED CHANSVmConvertToFloatFromStr 97.59036%; valid distinct source attempts 12.
- COVERED VmDateDtor 94.96703%; valid distinct source attempts 3.
- COVERED VmStringSplit 98.04054%; valid distinct source attempts 3.
- COVERED CHANSVmFormatString 99.84919%; valid distinct source attempts 4.
- COVERED VmBlobGetHexString 98.71951%; valid distinct source attempts 3.
- COVERED VmBlobPackCommon 97.949104%; valid distinct source attempts 3.
- COVERED VmBlobUnpack 98.452614%; valid distinct source attempts 3.
- COVERED VmWinEmuWrite 99.62687%; valid distinct source attempts 3.
- COVERED CHANSVmAddExe 99.625984%; valid distinct source attempts 3.
- COVERED CHANSVmLinkModules 98.677246%; valid distinct source attempts 3.
- COVERED CHANSVmStep 96.46608%; valid distinct source attempts 7.
All22 remaining functions have3+ distinct successful source-level attempts; failed compilations and invalid prior Step/AddExe substitutions excluded. VmStringReplace is now instruction-exact; untouched open functions retain earlier validated attempts. No source changes remain uncommitted.
Final remote audit 449529d9: owned source paths unchanged from merge base; no duplicate remote match.

## MAX2 final clean full gate and handoff
Full non-quick gate over all four owned units. Raw evidence:

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/BS2/BS2Mach] pool: IDENTICAL
[src/BS2/BS2Mach] objdiff: code 4940/16980 data 155504/158528 functions 24/29 fuzzy 98.5597 linked code 0
[src/BS2/BS2Mach] instruction-exact functions: 24/29
[src/BS2/BS2Mach]   section .bss size 155232 match 100.0
[src/BS2/BS2Mach]   section .data size 3024 match None
[src/BS2/BS2Mach]   section .sbss size 240 match 100.0
[src/BS2/BS2Mach]   section .sdata size 32 match 100.0
[src/BS2/BS2Mach]   section .text size 16980 match 98.559715
[src/BS2/BS2Mach]   below 100: Run 16.744186
[src/BS2/BS2Mach]   below 100: BS2StartGame 98.72774
[src/BS2/BS2Mach]   below 100: BS2StartGCGame 99.5614
[src/BS2/BS2Mach]   below 100: CheckBS2CommandStatus 99.50739
[src/BS2/BS2Mach]   below 100: BS2Tick 99.106186
[src/BS2/BS2Mach] baseline: code 4940/16980 data 155504 functions 24 fuzzy 98.1595
[src/scene/setting/AOSS] pool: IDENTICAL
[src/scene/setting/AOSS] objdiff: code 6436/16192 data 3928/3928 functions 16/21 fuzzy 97.8760 linked code 0
[src/scene/setting/AOSS] instruction-exact functions: 15/21
[src/scene/setting/AOSS]   section .bss size 3496 match 100.0
[src/scene/setting/AOSS]   section .data size 368 match 100.0
[src/scene/setting/AOSS]   section .sbss size 32 match 100.0
[src/scene/setting/AOSS]   section .sdata size 24 match 100.0
[src/scene/setting/AOSS]   section .sdata2 size 8 match 100.0
[src/scene/setting/AOSS]   section .text size 16192 match 97.87599
[src/scene/setting/AOSS]   below 100: AOSS_Init_old 96.59344
[src/scene/setting/AOSS]   below 100: AOSSDecryptMessage 97.74143
[src/scene/setting/AOSS]   below 100: AOSSApplyAuthOptions 98.77193
[src/scene/setting/AOSS]   below 100: AOSSSendHelloRequest 92.190475
[src/scene/setting/AOSS]   below 100: AOSSXorBufferWithKey 98.605446
[src/scene/setting/AOSS] baseline: code 6436/16192 data 3928 functions 16 fuzzy 96.7779
[src/BS2/BS2Update] pool: IDENTICAL
[src/BS2/BS2Update] objdiff: code 400/4052 data 10488/10488 functions 9/10 fuzzy 95.2271 linked code 0
[src/BS2/BS2Update] instruction-exact functions: 9/10
[src/BS2/BS2Update]   section .bss size 9056 match 100.0
[src/BS2/BS2Update]   section .data size 1328 match 100.0
[src/BS2/BS2Update]   section .sbss size 80 match 100.0
[src/BS2/BS2Update]   section .sdata size 24 match 100.0
[src/BS2/BS2Update]   section .text size 4052 match 95.22705
[src/BS2/BS2Update]   below 100: UpdateThread 94.70427
[src/BS2/BS2Update] baseline: code 400/4052 data 10488 functions 9 fuzzy 94.2300
[src/channelScript/CHANSVm] pool: IDENTICAL
[src/channelScript/CHANSVm] objdiff: code 38136/53564 data 6904/6904 functions 222/233 fuzzy 99.3853 linked code 0
[src/channelScript/CHANSVm] instruction-exact functions: 222/233
[src/channelScript/CHANSVm]   section .data size 4672 match 100.0
[src/channelScript/CHANSVm]   section .rodata size 1432 match 100.0
[src/channelScript/CHANSVm]   section .sbss size 16 match 100.0
[src/channelScript/CHANSVm]   section .sdata size 600 match 100.0
[src/channelScript/CHANSVm]   section .sdata2 size 184 match 100.0
[src/channelScript/CHANSVm]   section .text size 53564 match 99.38533
[src/channelScript/CHANSVm]   below 100: CHANSVmConvertToFloatFromStr 97.59036
[src/channelScript/CHANSVm]   below 100: VmDateDtor 94.96703
[src/channelScript/CHANSVm]   below 100: VmStringSplit 98.04054
[src/channelScript/CHANSVm]   below 100: CHANSVmFormatString 99.84919
[src/channelScript/CHANSVm]   below 100: VmBlobGetHexString 98.71951
[src/channelScript/CHANSVm]   below 100: VmBlobPackCommon 97.949104
[src/channelScript/CHANSVm]   below 100: VmBlobUnpack 98.452614
[src/channelScript/CHANSVm]   below 100: VmWinEmuWrite 99.62687
[src/channelScript/CHANSVm]   below 100: CHANSVmAddExe 99.625984
[src/channelScript/CHANSVm]   below 100: CHANSVmLinkModules 98.677246
[src/channelScript/CHANSVm]   below 100: CHANSVmStep 96.46608
[src/channelScript/CHANSVm] baseline: code 37608/53564 data 6904 functions 221 fuzzy 99.3644
regressions vs baseline: 0
global matched_code_percent: 90.71801 -> 90.73564
global fuzzy_match_percent: 99.57510 -> 99.58501
global complete_code_percent: 71.01273 -> 71.01273
global matched_data_percent: 99.36639 -> 99.36639
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
review note: src/BS2/BS2Update.c: volatile object declaration (orchestrator checks the target really re-reads it) (+1 net), e.g. static volatile u32 EntriesCount = 0;
GATE PASS
```


src/BS2/BS2Mach: objdiff exact functions 24 -> 24 / 29; code 4940 -> 4940 / 16980; data 155504 -> 155504 / 158528.
- Run 16.744186%; 11/43 instructions, structure/operands (40, 42); 3 distinct successful source trials; ABI register clearing and stack/LR handoff need an assembly trampoline; new assembly is forbidden.
- BS2StartGame 98.72774%; 393/393 instructions, structure/operands (4, 10); 3 distinct successful source trials; initial low-memory publication scheduling and commutative integer/FP operand order remain.
- BS2StartGCGame 99.5614%; 228/228 instructions, structure/operands (2, 7); 7 distinct successful source trials; target inlines and hoists cover-state polling; correcting that boundary changes initial scheduling and clock-product operand order.
- CheckBS2CommandStatus 99.50739%; 406/406 instructions, structure/operands (2, 2); 7 distinct successful source trials; only the adjacent cache-completion store and partition-count shift are swapped; const input, flag type and unsigned-width trials did not change them.
- BS2Tick 99.106186%; 1939/1940 instructions, structure/operands (35, 1696); 52 distinct successful source trials; two device-base materializations missing, one extra console switch jump; remaining global load/store scheduling and register choices differ.

src/scene/setting/AOSS: objdiff exact functions 16 -> 16 / 21; code 6436 -> 6436 / 16192; data 3928 -> 3928 / 3928.
- AOSS_Init_old 96.59344%; 1586/1584 instructions, structure/operands (110, 1516); 37 distinct successful source trials; default-halfword base, manufacturer skip branch, send-result/poll temporaries and scheduling differ. Protocol-state resume publication now matches. Target r14 read-before-definition remains uncertain; no uninitialized source introduced.
- AOSSDecryptMessage 97.74143%; 321/321 instructions, structure/operands (0, 87); 3 distinct successful source trials; register allocation and commutative operand selection; const/lifetime trials and 300 declaration evaluations did not improve.
- AOSSApplyAuthOptions 98.77193%; 114/114 instructions, structure/operands (0, 22); 3 distinct successful source trials; register allocation and commutative operand selection; const/lifetime trials and 177 declaration evaluations did not improve.
- AOSSSendHelloRequest 92.190475%; 271/273 instructions, structure/operands (33, 254); 4 distinct successful source trials; two instructions short; global-base grouping, checksum unrolling and cipher lifetimes differ. Formal const request did not change the discrepancy.
- AOSSXorBufferWithKey 98.605446%; 147/147 instructions, structure/operands (0, 34); 4 distinct successful source trials; register allocation and commutative operand selection; const-key formal removes a real target mask store and regresses, so mutable-key baseline retained.

src/BS2/BS2Update: objdiff exact functions 9 -> 9 / 10; code 400 -> 400 / 4052; data 10488 -> 10488 / 10488.
- UpdateThread 94.70427%; 907/913 instructions, structure/operands (82, 745); 23 distinct successful source trials; six instructions short: two early selection State5 stores are optimized away and error logging reuses a table base; selection output/return boundary trials unchanged. Frame0xf0 and native zero-type exit/indexed const test now closer.

src/channelScript/CHANSVm: objdiff exact functions 221 -> 222 / 233; code 37608 -> 38136 / 53564; data 6904 -> 6904 / 6904.
- CHANSVmConvertToFloatFromStr 97.59036%; 83/83 instructions, structure/operands (2, 2); 12 distinct successful source trials; only adjacent end-pointer zero store and string-tag compare differ. Formal const whole-conversion boundary and real scratch-record trials unchanged; direct-return trial regresses and was restored.
- VmDateDtor 94.96703%; 91/91 instructions, structure/operands (5, 7); 3 distinct successful source trials; argument setup and call/return scheduling differ.
- VmStringSplit 98.04054%; 222/222 instructions, structure/operands (0, 66); 3 distinct successful source trials; register allocation and operand selection after matching frame/count/topology.
- CHANSVmFormatString 99.84919%; 431/431 instructions, structure/operands (0, 13); 4 distinct successful source trials; register allocation; 300 declaration evaluations did not improve.
- VmBlobGetHexString 98.71951%; 82/82 instructions, structure/operands (0, 14); 3 distinct successful source trials; register allocation and byte-result temporary lifetime.
- VmBlobPackCommon 97.949104%; 668/668 instructions, structure/operands (0, 244); 3 distinct successful source trials; register allocation and commutative operand selection; loop/local/const trials did not fix.
- VmBlobUnpack 98.452614%; 517/517 instructions, structure/operands (0, 141); 3 distinct successful source trials; register allocation and commutative operand selection; loop/local/const trials did not fix.
- VmWinEmuWrite 99.62687%; 67/67 instructions, structure/operands (0, 5); 3 distinct successful source trials; register allocation; 71 declaration evaluations did not improve.
- CHANSVmAddExe 99.625984%; 254/254 instructions, structure/operands (0, 16); 3 distinct successful source trials; register allocation; 52 declaration evaluations did not improve. Incorrect payload-member trial excluded.
- CHANSVmLinkModules 98.677246%; 189/189 instructions, structure/operands (0, 43); 3 distinct successful source trials; register allocation; 13 declaration evaluations did not improve.
- CHANSVmStep 96.46608%; 1253/1253 instructions, structure/operands (65, 313); 7 distinct successful source trials; opcode countdown/branch/local layout differs; target-proven volatile inversion-local trials were identical or regressed. Invalid countdown trial excluded.

VmStringReplace after the clean build: objdiff100.0,132/132 identical instructions,ctxdiff0. Natural formal const parent view plus const payload views and real local declaration order; public symbol/callback preserved. Code +528 bytes; no data metadata correction needed.
This round from6778cff9: instruction-exact counts Mach24 ->24/29, AOSS15 ->15/21, Update9 ->9/10, Vm221 ->222/233. Objdiff AOSS16/21 already includes ParseNetworkSettings; raw15 is the unchanged previously audited CR1-normalization offset artifact, not a loss or new match. Aggregate objdiff code49384 ->49912/90788; data176824 ->176824/179848.
Big-function scores this round: BS2Tick99.106186 ->99.106186; AOSS_Init_old96.49558 ->96.59344; UpdateThread94.46988 ->94.70427; VmStringReplace98.82576 ->100.0. Other open functions retain their measured baselines.
Final data ownership audit: pools identical for all four units; AOSS/Update/Vm data100. Mach literals have identical bytes/offsets, while unresolved .data differences are jump-table relocations inside nonexact code and extracted trailing alignment. No eligible name-only object or proven extent correction found; no symbol/address/section total changed. Weak/inline duplicate objects left alone.
Uncertainty: AOSS target tests saved r14 at0xa20 before any definition in this function. Defined source initialization remains; reproducing undefined input is forbidden. Complete-unit100% not claimed. All22 residual functions have3+ valid trials, with failed compilations/invalid prior substitutions excluded.
Source checkpoint commits this round:85515018 (AOSS),c924d33e (Update),df894b4e (exact Replace). Changed paths:src/scene/setting/AOSS.c,src/BS2/BS2Update.c,src/channelScript/CHANSVm.c,tools/decomp-assist/big1.attempts.md. Final log-only commit follows; no source change after full gate. Untracked fz18.attempts.md pre-existed and is untouched.
