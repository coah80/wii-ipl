# Assembly inventory

Snapshot: `agent/w1005/da5` after the WPADiManageHandler and _CNTCACHEDeleteTitle C conversions, based on `7aa71d29`.

Scope: every `asm` function body, `asm` block, and `__asm` block in C/C++ sources and headers under `src/` and `libs/`, including inactive platform branches. Each block gets its own row. Declarations, comments, and standalone assembly files are outside this scan.

Count: 209 bodies/blocks, 160 ORIGINAL-ASM and 49 PLACEHOLDER. The scan also excluded 65 asm declarations.

ORIGINAL-ASM requires a matching asm function in the ogws reference or a concrete hardware/runtime register convention. An ordinary prologue, `nofralloc`, or a call to `_savegpr_*` does not establish that a function was originally assembly. PLACEHOLDER means the logic belongs in C/C++, even when the current assembly matches exactly.

`ogws_sdk/` references resolve under `/mnt/drive2/projects/wii-ipl-workers/_refs/prior/ogws_sdk/`. Linked ogws files supplement those copies for runtime and NW4R routines. The remote files were read on 2026-10-05. The local reference versions can differ from the 2010 target.

This inventory classifies the other workers' files without modifying them. It records this branch's contents, including placeholders another worker may have already converted elsewhere.

| File and line | Function | Form | Verdict | Evidence |
| --- | --- | --- | --- | --- |
| `src/BS2/BS2Init.c:22` | `ClearOtherBATs` | body | ORIGINAL-ASM | isync and direct IBAT/DBAT register writes. |
| `src/BS2/BS2Mach.c:246` | `Run` | body | ORIGINAL-ASM | Clears ABI registers, replaces r1, uses dcbz/dcbf, and jumps via LR. |
| `src/BS2/BS2Start.c:22` | `__start` | body | ORIGINAL-ASM | Runs before the C stack and ABI registers exist; constructs the initial stack. |
| `src/BS2/BS2Start.c:97` | `__init_registers` | body | ORIGINAL-ASM | Initializes GPRs, r1, r2, and r13 for the C runtime. |
| `src/channelScript/CHANSVm.c:6512` | `VmPushFuncReturnInfo` | body | PLACEHOLDER | VM frame bookkeeping with ordinary loads, stores, and calls. |
| `src/keyboard/tiGUIManager.cpp:359` | `draw__Q39textinput3gui13PaneComponentFv` | body | PLACEHOLDER | GUI pane traversal and drawing calls. |
| `src/keyboard/tiInputForm.cpp:1600` | `create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer` | body | PLACEHOLDER | Input-form allocation and initialization. |
| `src/scene/button/iplButton.cpp:971` | `push_button_queue` | body | PLACEHOLDER | Button queue traversal and updates. |
| `src/scene/channelSelect/iplChannelSelect.cpp:1336` | `updateDiskState__Q33ipl5scene13ChannelSelectFv` | body | PLACEHOLDER | Disc-state updates and scene calls. |
| `src/scene/nakamuraTest/gamespy/common/gsPlatformUtil.c:474` | `GetTicks` | block 1 | ORIGINAL-ASM | Inactive PS2 branch reads the CP0 Count register with mfc0 $9. |
| `src/sound/iplSound.cpp:341` | `resetAllSound__Q33ipl3snd6SystemFv` | body | PLACEHOLDER | Sound-system reset calls and state writes. |
| `src/system/TVRC.cpp:224` | `TVRCSendStartAsync` | body | PLACEHOLDER | IR send setup and ordinary SDK calls. |
| `src/system/TVRC.cpp:436` | `__FTVRCLoop0Handler__7LibTVRCFP7OSAlarmP9OSContext` | body | PLACEHOLDER | Timer callback logic and SDK calls. |
| `src/system/iplCdbBackup.cpp:394` | `cdb_backup_delete_task_` | body | PLACEHOLDER | Database deletion task control flow. |
| `src/system/iplCdbBackup.cpp:502` | `cdb_backup_move_task_` | body | PLACEHOLDER | Database move task control flow. |
| `src/system/iplChannelManager.cpp:472` | `getTitleName__Q33ipl7channel7ManagerCFiii` | body | PLACEHOLDER | Channel-title selection and string copying. |
| `src/system/iplException.cpp:95` | `Exception::exception_callback` | body | PLACEHOLDER | Console drawing, key polling, and scrolling logic. |
| `src/system/iplSaveDataManager.cpp:149` | `Manager::hasChannel` | body | PLACEHOLDER | Title-ID comparisons and channel-slot search. |
| `src/system/iplSaveDataManager.cpp:599` | `Manager::makePriorTitleIDList` | body | PLACEHOLDER | Title-ID filtering and ordering. |
| `src/system/iplSaveDataManager.cpp:807` | `Manager::doUpdateChanInfos` | body | PLACEHOLDER | Channel metadata validation and updates. |
| `src/system/iplSystem.cpp:1089` | `System::warning_run` | body | PLACEHOLDER | Warning-scene control flow and calls. |
| `src/system/rvl_dec.c:17` | `Rvl_decode` | block 1 | PLACEHOLDER | Compression signature dispatch, expressible as C branches. |
| `src/system/rvl_dec.c:72` | `Rvl_decode_szs` | body | PLACEHOLDER | Yaz/SZS byte-copy decompression loops. |
| `src/system/rvl_dec.c:233` | `Rvl_decode_ash` | body | PLACEHOLDER | ASH bitstream and Huffman decoding. |
| `src/system/rvl_dec.c:717` | `Rvl_decode_asr` | body | PLACEHOLDER | ASR decompression control flow and buffer writes. |
| `libs/MetroTRK/src/Export/targsupp.c:12` | `TRKAccessFile` | body | ORIGINAL-ASM | twi 31,r0,0 is the debugger file-service trap, with debugger-controlled return registers. |
| `libs/MetroTRK/src/Export/targsupp.c:22` | `TRKOpenFile` | body | ORIGINAL-ASM | twi 31,r0,0 is the debugger file-service trap, with debugger-controlled return registers. |
| `libs/MetroTRK/src/Export/targsupp.c:30` | `TRKCloseFile` | body | ORIGINAL-ASM | twi 31,r0,0 is the debugger file-service trap, with debugger-controlled return registers. |
| `libs/MetroTRK/src/Export/targsupp.c:38` | `TRKPositionFile` | body | ORIGINAL-ASM | twi 31,r0,0 is the debugger file-service trap, with debugger-controlled return registers. |
| `libs/NW4R/include/nw4r/math/arithmetic.h:30` | `FSelect` | block 1 | ORIGINAL-ASM | Same function contains ASM in [ogws math_arithmetic.h](https://github.com/doldecomp/ogws/blob/master/include/nw4r/math/math_arithmetic.h#L91). |
| `libs/NW4R/include/nw4r/math/arithmetic.h:38` | `FAbs` | block 1 | ORIGINAL-ASM | Same function contains ASM in [ogws math_arithmetic.h](https://github.com/doldecomp/ogws/blob/master/include/nw4r/math/math_arithmetic.h#L30). |
| `libs/NW4R/include/nw4r/math/types.h:230` | `VEC3Add` | block 1 | ORIGINAL-ASM | Paired-single psq_l/psq_st and ps_* vector or matrix operations. |
| `libs/NW4R/include/nw4r/math/types.h:258` | `VEC3Sub` | block 1 | ORIGINAL-ASM | Paired-single psq_l/psq_st and ps_* vector or matrix operations. |
| `libs/NW4R/include/nw4r/math/types.h:287` | `VEC3Scale` | block 1 | ORIGINAL-ASM | Paired-single psq_l/psq_st and ps_* vector or matrix operations. |
| `libs/NW4R/src/math/math_arithmetic.cpp:11` | `FrSqrt` | block 1 | ORIGINAL-ASM | frsqrte and fixed floating-point refinement; same function uses ASM in [ogws math_arithmetic.cpp](https://github.com/doldecomp/ogws/blob/master/src/nw4r/math/math_arithmetic.cpp#L65). |
| `libs/NW4R/src/math/math_types.cpp:11` | `MTX44Identity` | block 1 | ORIGINAL-ASM | Paired-single psq_l/psq_st and ps_* vector or matrix operations. |
| `libs/RVLMiddleware/TMC_JPEG/src/buffer/getcode.c:4` | `TMCJPEGDEC_init_buff_thumbnail` | body | PLACEHOLDER | JPEG parsing, table construction, or decode arithmetic using ordinary integer operations and calls. |
| `libs/RVLMiddleware/TMC_JPEG/src/buffer/mkhdec3.c:7` | `TMCJPEGDEC_make_huffdec` | body | PLACEHOLDER | JPEG parsing, table construction, or decode arithmetic using ordinary integer operations and calls. |
| `libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main.c:110` | `TMCJPEGDEC_imagestart` | body | PLACEHOLDER | JPEG parsing, table construction, or decode arithmetic using ordinary integer operations and calls. |
| `libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main.c:366` | `TMCJPEGDEC_scan_varinit` | body | PLACEHOLDER | JPEG parsing, table construction, or decode arithmetic using ordinary integer operations and calls. |
| `libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main.c:594` | `TMCJPEGDEC_restart_interval` | body | PLACEHOLDER | JPEG parsing, table construction, or decode arithmetic using ordinary integer operations and calls. |
| `libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main.c:787` | `TMCJPEGDEC_parse_para` | body | PLACEHOLDER | JPEG parsing, table construction, or decode arithmetic using ordinary integer operations and calls. |
| `libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main.c:1173` | `TMCJPEGDEC_parse_dht` | body | PLACEHOLDER | JPEG parsing, table construction, or decode arithmetic using ordinary integer operations and calls. |
| `libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main.c:1484` | `TMCJPEGDEC_parse_sof` | body | PLACEHOLDER | JPEG parsing, table construction, or decode arithmetic using ordinary integer operations and calls. |
| `libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main.c:1963` | `TMCJPEGDEC_parse_sos` | body | PLACEHOLDER | JPEG parsing, table construction, or decode arithmetic using ordinary integer operations and calls. |
| `libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main.c:2208` | `TMCJPEGDEC_err_restart` | body | PLACEHOLDER | JPEG parsing, table construction, or decode arithmetic using ordinary integer operations and calls. |
| `libs/RVLMiddleware/TMC_JPEG/src/reschange/iqdec_resolution_change_a3.c:8` | `TMCJPEGDEC_decode_iquant_rc` | body | PLACEHOLDER | JPEG parsing, table construction, or decode arithmetic using ordinary integer operations and calls. |
| `libs/RVL_SDK/include/revolution/os/OSFastCast.h:13` | `OSInitFastCast` | block 1 | ORIGINAL-ASM | mtspr programs the GQR quantization registers. |
| `libs/RVL_SDK/include/revolution/os/OSFastCast.h:40` | `__OSu16tof32` | block 1 | ORIGINAL-ASM | Paired-single psq_l/psq_st or ps_* operations; fast-cast variants also use GQR conversion formats. |
| `libs/RVL_SDK/include/revolution/os/OSFastCast.h:58` | `__OSf32tou8` | block 1 | ORIGINAL-ASM | Paired-single psq_l/psq_st or ps_* operations; fast-cast variants also use GQR conversion formats. |
| `libs/RVL_SDK/include/revolution/os/OSFastCast.h:77` | `__OSf32tou16` | block 1 | ORIGINAL-ASM | Paired-single psq_l/psq_st or ps_* operations; fast-cast variants also use GQR conversion formats. |
| `libs/RVL_SDK/include/revolution/os/OSFastCast.h:92` | `__OSs16tof32` | block 1 | ORIGINAL-ASM | Paired-single psq_l/psq_st or ps_* operations; fast-cast variants also use GQR conversion formats. |
| `libs/RVL_SDK/include/revolution/os/OSFastCast.h:108` | `__OSf32tos16` | block 1 | ORIGINAL-ASM | Paired-single psq_l/psq_st or ps_* operations; fast-cast variants also use GQR conversion formats. |
| `libs/RVL_SDK/src/ai/ai.c:154` | `__AICallbackStackSwitch` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/AI_ai.c:146. |
| `libs/RVL_SDK/src/base/PPCArch.c:6` | `PPCMfmsr` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mfmsr r3`. |
| `libs/RVL_SDK/src/base/PPCArch.c:14` | `PPCMtmsr` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mtmsr newMSR`. |
| `libs/RVL_SDK/src/base/PPCArch.c:22` | `PPCOrMsr` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mfmsr r4`. |
| `libs/RVL_SDK/src/base/PPCArch.c:31` | `PPCAndMsr` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mfmsr r4`. |
| `libs/RVL_SDK/src/base/PPCArch.c:40` | `PPCAndCMsr` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mfmsr r4`. |
| `libs/RVL_SDK/src/base/PPCArch.c:49` | `PPCMfhid0` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mfspr r3, HID0`. |
| `libs/RVL_SDK/src/base/PPCArch.c:57` | `PPCMthid0` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mtspr HID0, newHID0`. |
| `libs/RVL_SDK/src/base/PPCArch.c:65` | `PPCMfhid1` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mfspr r3, HID1`. |
| `libs/RVL_SDK/src/base/PPCArch.c:73` | `PPCMfl2cr` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mfspr r3, L2CR`. |
| `libs/RVL_SDK/src/base/PPCArch.c:81` | `PPCMtl2cr` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mtspr L2CR, newL2cr`. |
| `libs/RVL_SDK/src/base/PPCArch.c:89` | `PPCMtdec` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mtdec newDec`. |
| `libs/RVL_SDK/src/base/PPCArch.c:97` | `PPCMfdec` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mfdec r3`. |
| `libs/RVL_SDK/src/base/PPCArch.c:105` | `PPCSync` | body | ORIGINAL-ASM | Special-register or synchronization operation: `sc`. |
| `libs/RVL_SDK/src/base/PPCArch.c:113` | `PPCEieio` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mfmsr r5`, `mtmsr r6`. |
| `libs/RVL_SDK/src/base/PPCArch.c:133` | `PPCHalt` | body | ORIGINAL-ASM | Special-register or synchronization operation: `sync`. |
| `libs/RVL_SDK/src/base/PPCArch.c:145` | `PPCMfmmcr0` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mfspr r3, MMCR0`. |
| `libs/RVL_SDK/src/base/PPCArch.c:153` | `PPCMtmmcr0` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mtspr MMCR0, newMmcr0`. |
| `libs/RVL_SDK/src/base/PPCArch.c:161` | `PPCMfmmcr1` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mfspr r3, MMCR1`. |
| `libs/RVL_SDK/src/base/PPCArch.c:169` | `PPCMtmmcr1` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mtspr MMCR1, newMmcr1`. |
| `libs/RVL_SDK/src/base/PPCArch.c:177` | `PPCMfpmc1` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mfspr r3, PMC1`. |
| `libs/RVL_SDK/src/base/PPCArch.c:185` | `PPCMtpmc1` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mtspr PMC1, newPmc1`. |
| `libs/RVL_SDK/src/base/PPCArch.c:193` | `PPCMfpmc2` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mfspr r3, PMC2`. |
| `libs/RVL_SDK/src/base/PPCArch.c:201` | `PPCMtpmc2` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mtspr PMC2, newPmc2`. |
| `libs/RVL_SDK/src/base/PPCArch.c:209` | `PPCMfpmc3` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mfspr r3, PMC3`. |
| `libs/RVL_SDK/src/base/PPCArch.c:217` | `PPCMtpmc3` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mtspr PMC3, newPmc3`. |
| `libs/RVL_SDK/src/base/PPCArch.c:225` | `PPCMfpmc4` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mfspr r3, PMC4`. |
| `libs/RVL_SDK/src/base/PPCArch.c:233` | `PPCMtpmc4` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mtspr PMC4, newPmc4`. |
| `libs/RVL_SDK/src/base/PPCArch.c:244` | `PPCMffpscr` | block 1 | ORIGINAL-ASM | Special-register or synchronization operation: `mffs fp31`. |
| `libs/RVL_SDK/src/base/PPCArch.c:252` | `PPCMfsia` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mfspr r3, SIA`. |
| `libs/RVL_SDK/src/base/PPCArch.c:260` | `PPCMtsia` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mtspr SIA, newSia`. |
| `libs/RVL_SDK/src/base/PPCArch.c:272` | `PPCMtfpscr` | block 1 | ORIGINAL-ASM | Special-register or synchronization operation: `mtfsf 0xff, fp31`. |
| `libs/RVL_SDK/src/base/PPCArch.c:282` | `PPCMfhid2` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mfspr r3, HID2`. |
| `libs/RVL_SDK/src/base/PPCArch.c:290` | `PPCMthid2` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mtspr HID2, newhid2`. |
| `libs/RVL_SDK/src/base/PPCArch.c:298` | `PPCMfwpar` | body | ORIGINAL-ASM | Special-register or synchronization operation: `sync`, `mfspr r3, WPAR`. |
| `libs/RVL_SDK/src/base/PPCArch.c:307` | `PPCMtwpar` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mtspr WPAR, newwpar`. |
| `libs/RVL_SDK/src/base/PPCArch.c:315` | `PPCMfdmaU` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mfspr r3, DMA_U`. |
| `libs/RVL_SDK/src/base/PPCArch.c:323` | `PPCMfdmaL` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mfspr r3, DMA_L`. |
| `libs/RVL_SDK/src/base/PPCArch.c:331` | `PPCMtdmaU` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mtspr DMA_U, newdmau`. |
| `libs/RVL_SDK/src/base/PPCArch.c:339` | `PPCMtdmaL` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mtspr DMA_L, newdmal`. |
| `libs/RVL_SDK/src/base/PPCArch.c:347` | `PPCMfpvr` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mfspr r3, PVR`. |
| `libs/RVL_SDK/src/base/PPCArch.c:363` | `PPCSetFpIEEEMode` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mtfsb0 FPSCR_NI_BIT`. |
| `libs/RVL_SDK/src/base/PPCArch.c:371` | `PPCSetFpNonIEEEMode` | body | ORIGINAL-ASM | Special-register or synchronization operation: `mtfsb1 FPSCR_NI_BIT`. |
| `libs/RVL_SDK/src/base/PPCArch.c:382` | `PPCMthid4` | block 1 | ORIGINAL-ASM | Special-register or synchronization operation: `mtspr HID4, val`. |
| `libs/RVL_SDK/src/base/PPCArch.c:389` | `PPCMthid4` | block 2 | ORIGINAL-ASM | Special-register or synchronization operation: `mtspr HID4, val`. |
| `libs/RVL_SDK/src/cntcache/cntcache.c:66` | `CNTCACHEClear` | body | PLACEHOLDER | NAND reads and token dispatch; live-literal reconstruction still lacks four retained pool entries. |
| `libs/RVL_SDK/src/cntcache/cntcache.c:266` | `_CNTCACHEIsTitleRemovable` | body | PLACEHOLDER | NAND usage and typed TMD checks; C trials still differ in return copies and scheduling. |
| `libs/RVL_SDK/src/cntcache/cntcache.c:360` | `_CNTCACHEDeleteContent` | body | PLACEHOLDER | Token parsing, typed content traversal, and ES deletion calls. |
| `libs/RVL_SDK/src/db/db.c:27` | `__DBExceptionDestination` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/DB_db.c:23. |
| `libs/RVL_SDK/src/gx/GXLight.c:20` | `PushLight` | block 1 | ORIGINAL-ASM | Paired-single psq_l/psq_st or ps_* operations; fast-cast variants also use GQR conversion formats. |
| `libs/RVL_SDK/src/gx/GXTransform.c:19` | `WriteProjPS` | block 1 | ORIGINAL-ASM | Paired-single psq_l/psq_st or ps_* operations; fast-cast variants also use GQR conversion formats. |
| `libs/RVL_SDK/src/gx/GXTransform.c:36` | `Copy6Floats` | block 1 | ORIGINAL-ASM | Paired-single psq_l/psq_st or ps_* operations; fast-cast variants also use GQR conversion formats. |
| `libs/RVL_SDK/src/gx/GXTransform.c:58` | `WriteMTXPS4x3` | block 1 | ORIGINAL-ASM | Paired-single psq_l/psq_st or ps_* operations; fast-cast variants also use GQR conversion formats. |
| `libs/RVL_SDK/src/gx/GXTransform.c:86` | `WriteMTXPS3x3from3x4` | block 1 | ORIGINAL-ASM | Paired-single psq_l/psq_st or ps_* operations; fast-cast variants also use GQR conversion formats. |
| `libs/RVL_SDK/src/gx/GXTransform.c:112` | `WriteMTXPS4x2` | block 1 | ORIGINAL-ASM | Paired-single psq_l/psq_st or ps_* operations; fast-cast variants also use GQR conversion formats. |
| `libs/RVL_SDK/src/mtx/mtx.c:36` | `PSMTXIdentity` | block 1 | ORIGINAL-ASM | Paired-single psq_l/psq_st or ps_* operations; fast-cast variants also use GQR conversion formats. |
| `libs/RVL_SDK/src/mtx/mtx.c:65` | `PSMTXCopy` | body | ORIGINAL-ASM | Paired-single psq_l/psq_st or ps_* operations; fast-cast variants also use GQR conversion formats. |
| `libs/RVL_SDK/src/mtx/mtx.c:111` | `PSMTXConcat` | body | ORIGINAL-ASM | Paired-single psq_l/psq_st or ps_* operations; fast-cast variants also use GQR conversion formats. |
| `libs/RVL_SDK/src/mtx/mtx.c:209` | `PSMTXInverse` | body | ORIGINAL-ASM | Paired-single psq_l/psq_st or ps_* operations; fast-cast variants also use GQR conversion formats. |
| `libs/RVL_SDK/src/mtx/mtx.c:317` | `PSMTXInvXpose` | body | ORIGINAL-ASM | Paired-single psq_l/psq_st or ps_* operations; fast-cast variants also use GQR conversion formats. |
| `libs/RVL_SDK/src/mtx/mtx.c:449` | `PSMTXRotTrig` | block 1 | ORIGINAL-ASM | frsp prepares the operands for the paired-single rotation block in this same SDK function. |
| `libs/RVL_SDK/src/mtx/mtx.c:457` | `PSMTXRotTrig` | block 2 | ORIGINAL-ASM | Paired-single psq_l/psq_st or ps_* operations; fast-cast variants also use GQR conversion formats. |
| `libs/RVL_SDK/src/mtx/mtx.c:527` | `PSMTXTrans` | block 1 | ORIGINAL-ASM | Paired-single psq_l/psq_st or ps_* operations; fast-cast variants also use GQR conversion formats. |
| `libs/RVL_SDK/src/mtx/mtx.c:560` | `PSMTXTransApply` | body | ORIGINAL-ASM | Paired-single psq_l/psq_st or ps_* operations; fast-cast variants also use GQR conversion formats. |
| `libs/RVL_SDK/src/mtx/mtx.c:601` | `PSMTXScale` | block 1 | ORIGINAL-ASM | Paired-single psq_l/psq_st or ps_* operations; fast-cast variants also use GQR conversion formats. |
| `libs/RVL_SDK/src/mtx/mtx.c:629` | `PSMTXScaleApply` | body | ORIGINAL-ASM | Paired-single psq_l/psq_st or ps_* operations; fast-cast variants also use GQR conversion formats. |
| `libs/RVL_SDK/src/mtx/mtxvec.c:16` | `PSMTXMultVec` | body | ORIGINAL-ASM | Paired-single psq_l/psq_st or ps_* operations; fast-cast variants also use GQR conversion formats. |
| `libs/RVL_SDK/src/mtx/vec.c:29` | `PSVECNormalize` | block 1 | ORIGINAL-ASM | Paired-single psq_l/psq_st or ps_* operations; fast-cast variants also use GQR conversion formats. |
| `libs/RVL_SDK/src/mtx/vec.c:58` | `PSVECCrossProduct` | body | ORIGINAL-ASM | Paired-single psq_l/psq_st or ps_* operations; fast-cast variants also use GQR conversion formats. |
| `libs/RVL_SDK/src/os/OS.c:86` | `__OSFPRInit` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OS.c:52. |
| `libs/RVL_SDK/src/os/OS.c:582` | `OSInit` | block 1 | PLACEHOLDER | This block only pins __ArenaLo with lis/addi; ogws OS_OS.c uses the C linker-symbol pointer. |
| `libs/RVL_SDK/src/os/OS.c:617` | `OSInit` | block 2 | PLACEHOLDER | This block only pins __ArenaLo with lis/addi; ogws OS_OS.c uses the C linker-symbol pointer. |
| `libs/RVL_SDK/src/os/OS.c:771` | `__OSDBIntegrator` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OS.c:699. |
| `libs/RVL_SDK/src/os/OS.c:794` | `__OSDBJump` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OS.c:729. |
| `libs/RVL_SDK/src/os/OS.c:816` | `OSExceptionVector` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OS.c:752. |
| `libs/RVL_SDK/src/os/OS.c:876` | `OSDefaultExceptionHandler` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OS.c:817. |
| `libs/RVL_SDK/src/os/OS.c:917` | `__OSPSInit` | block 1 | ORIGINAL-ASM | mtspr resets GQR0 through GQR7 for paired-single operations. |
| `libs/RVL_SDK/src/os/OSAlarm.c:195` | `DecrementerExceptionHandler` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSAlarm.c:193. |
| `libs/RVL_SDK/src/os/OSCache.c:13` | `DCEnable` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSCache.c:5. |
| `libs/RVL_SDK/src/os/OSCache.c:28` | `DCInvalidateRange` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSCache.c:18. |
| `libs/RVL_SDK/src/os/OSCache.c:50` | `DCFlushRange` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSCache.c:40. |
| `libs/RVL_SDK/src/os/OSCache.c:73` | `DCStoreRange` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSCache.c:63. |
| `libs/RVL_SDK/src/os/OSCache.c:96` | `DCFlushRangeNoSync` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSCache.c:86. |
| `libs/RVL_SDK/src/os/OSCache.c:118` | `DCZeroRange` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSCache.c:130. |
| `libs/RVL_SDK/src/os/OSCache.c:140` | `ICInvalidateRange` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSCache.c:152. |
| `libs/RVL_SDK/src/os/OSCache.c:165` | `ICFlashInvalidate` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSCache.c:177. |
| `libs/RVL_SDK/src/os/OSCache.c:177` | `ICEnable` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSCache.c:189. |
| `libs/RVL_SDK/src/os/OSCache.c:192` | `LCDisable` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSCache.c:275. |
| `libs/RVL_SDK/src/os/OSContext.c:11` | `__OSLoadFPUContext` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSContext.c:5. |
| `libs/RVL_SDK/src/os/OSContext.c:97` | `__OSSaveFPUContext` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSContext.c:91. |
| `libs/RVL_SDK/src/os/OSContext.c:184` | `OSLoadFPUContext` | body | ORIGINAL-ASM | Transfers control directly into the FPU context loader, which restores caller-visible FPRs. |
| `libs/RVL_SDK/src/os/OSContext.c:192` | `OSSaveFPUContext` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSContext.c:178. |
| `libs/RVL_SDK/src/os/OSContext.c:200` | `OSSetCurrentContext` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSContext.c:187. |
| `libs/RVL_SDK/src/os/OSContext.c:240` | `OSSaveContext` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSContext.c:227. |
| `libs/RVL_SDK/src/os/OSContext.c:280` | `OSLoadContext` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSContext.c:275. |
| `libs/RVL_SDK/src/os/OSContext.c:353` | `OSGetStackPointer` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSContext.c:351. |
| `libs/RVL_SDK/src/os/OSContext.c:361` | `OSSwitchStack` | body | ORIGINAL-ASM | Returns the old r1 and installs the supplied stack pointer directly. |
| `libs/RVL_SDK/src/os/OSContext.c:371` | `OSSwitchFiber` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSContext.c:360. |
| `libs/RVL_SDK/src/os/OSContext.c:389` | `OSSwitchFiberEx` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSContext.c:384. |
| `libs/RVL_SDK/src/os/OSContext.c:421` | `OSInitContext` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSContext.c:418. |
| `libs/RVL_SDK/src/os/OSContext.c:534` | `OSSwitchFPUContext` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSContext.c:537. |
| `libs/RVL_SDK/src/os/OSContext.c:583` | `OSFillFPUContext` | body | ORIGINAL-ASM | mfmsr/mtmsr/isync enable the FPU before saving all floating-point registers. |
| `libs/RVL_SDK/src/os/OSInterrupt.c:40` | `OSDisableInterrupts` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSInterrupt.c:21. |
| `libs/RVL_SDK/src/os/OSInterrupt.c:55` | `OSEnableInterrupts` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSInterrupt.c:40. |
| `libs/RVL_SDK/src/os/OSInterrupt.c:69` | `OSRestoreInterrupts` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSInterrupt.c:55. |
| `libs/RVL_SDK/src/os/OSInterrupt.c:479` | `ExternalInterruptHandler` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSInterrupt.c:534. |
| `libs/RVL_SDK/src/os/OSMemory.c:89` | `ConfigMEM1_24MB` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSMemory.c:50. |
| `libs/RVL_SDK/src/os/OSMemory.c:136` | `ConfigMEM1_48MB` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSMemory.c:89. |
| `libs/RVL_SDK/src/os/OSMemory.c:184` | `ConfigMEM2_52MB` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSMemory.c:128. |
| `libs/RVL_SDK/src/os/OSMemory.c:266` | `ConfigMEM2_56MB` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSMemory.c:191. |
| `libs/RVL_SDK/src/os/OSMemory.c:348` | `ConfigMEM2_64MB` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSMemory.c:254. |
| `libs/RVL_SDK/src/os/OSMemory.c:412` | `ConfigMEM2_112MB` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSMemory.c:304. |
| `libs/RVL_SDK/src/os/OSMemory.c:493` | `ConfigMEM2_128MB` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSMemory.c:367. |
| `libs/RVL_SDK/src/os/OSMemory.c:557` | `ConfigMEM_ES1_0` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSMemory.c:417. |
| `libs/RVL_SDK/src/os/OSMemory.c:590` | `RealMode` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSMemory.c:444. |
| `libs/RVL_SDK/src/os/OSSync.c:6` | `SystemCallVector` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSSync.c:11. |
| `libs/RVL_SDK/src/os/OSTime.c:22` | `OSGetTime` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSTime.c:23. |
| `libs/RVL_SDK/src/os/OSTime.c:38` | `OSGetTick` | body | ORIGINAL-ASM | Same function is asm in ogws_sdk/OS_OSTime.c:39. |
| `libs/RVL_SDK/src/os/OSTime.c:48` | `__SetTime` | body | ORIGINAL-ASM | mttbl/mttbu/mttbl update the hardware time base in a fixed sequence. |
| `libs/RVL_SDK/src/os/__ppc_eabi_init.cpp:33` | `__init_hardware` | body | ORIGINAL-ASM | Same function is asm in [ogws __ppc_eabi_init.c](https://github.com/doldecomp/ogws/blob/master/src/revolution/OS/__ppc_eabi_init.c#L9). |
| `libs/RVL_SDK/src/os/__ppc_eabi_init.cpp:55` | `__flush_cache` | body | ORIGINAL-ASM | Same function is asm in [ogws __ppc_eabi_init.c](https://github.com/doldecomp/ogws/blob/master/src/revolution/OS/__ppc_eabi_init.c#L31). |
| `libs/RVL_SDK/src/os/__ppc_eabi_init.cpp:85` | `__init_user` | body | ORIGINAL-ASM | Same function is asm in [ogws __ppc_eabi_init.c](https://github.com/doldecomp/ogws/blob/master/src/revolution/OS/__ppc_eabi_init.c#L55). |
| `libs/RVL_SDK/src/sdi/sdi_api.c:785` | `ISD_GetCardSize` | body | PLACEHOLDER | CSD bitfield decoding and arithmetic; no special-register operation. |
| `libs/RevoEX/src/cdb/CDBDatabase.c:399` | `CDBDatabaseSearchRecordLayer` | body | PLACEHOLDER | Database traversal or filename checks with ordinary data access and calls. |
| `libs/RevoEX/src/cdb/CDBDatabase.c:892` | `CDBDatabaseSearchMinuteLayer` | body | PLACEHOLDER | Database traversal or filename checks with ordinary data access and calls. |
| `libs/RevoEX/src/cdb/CDBDatabase.c:1154` | `CDBDatabaseSearchHourLayer` | body | PLACEHOLDER | Database traversal or filename checks with ordinary data access and calls. |
| `libs/RevoEX/src/cdb/CDBDatabase.c:1411` | `CDBDatabaseSearchDayLayer` | body | PLACEHOLDER | Database traversal or filename checks with ordinary data access and calls. |
| `libs/RevoEX/src/cdb/CDBDatabase.c:1693` | `CDBDatabaseSearchMonthLayer` | body | PLACEHOLDER | Database traversal or filename checks with ordinary data access and calls. |
| `libs/RevoEX/src/cdb/CDBDatabase.c:1963` | `CDBDatabaseSearchYearLayer` | body | PLACEHOLDER | Database traversal or filename checks with ordinary data access and calls. |
| `libs/RevoEX/src/cdb/CDBFileSystemUtils.c:112` | `CDBFSIsCDBFileOnSD` | body | PLACEHOLDER | Database traversal or filename checks with ordinary data access and calls. |
| `libs/RevoEX/src/nwc24/NWC24Manage.c:305` | `NWC24Check` | body | PLACEHOLDER | Account validation and integer bit operations, expressible in C. |
| `libs/RevoEX/src/nwc24/NWC24UserId.c:11` | `NWC24CheckUserId` | body | PLACEHOLDER | Account validation and integer bit operations, expressible in C. |
| `libs/RevoEX/src/nwc24/NWC24UserId.c:95` | `getUnScrambleId` | body | PLACEHOLDER | Account validation and integer bit operations, expressible in C. |
| `libs/RevoEX/src/vf/develop/nand_drv.c:420` | `_MountPrfFile` | body | PLACEHOLDER | Profile-file mounting and error-handling control flow. |
| `libs/RevoEX/src/wd/WDScan.c:313` | `WDiFindVendorSpecificIE` | body | PLACEHOLDER | Vendor information-element search and byte comparisons. |
| `libs/Runtime/src/Gecko_setjmp.c:30` | `__setjmp` | body | ORIGINAL-ASM | Saves or restores caller GPRs/FPRs, LR, CR, and stack state across nonlocal returns. |
| `libs/Runtime/src/Gecko_setjmp.c:79` | `longjmp` | body | ORIGINAL-ASM | Saves or restores caller GPRs/FPRs, LR, CR, and stack state across nonlocal returns. |
| `libs/Runtime/src/__init_cpp_exceptions.cpp:23` | `__exception_info_constants` | block 1 | ORIGINAL-ASM | Reads the caller ABI TOC register r2 directly for exception registration. |
| `libs/Runtime/src/ptmf.c:13` | `__ptmf_scall` | body | ORIGINAL-ASM | Same function is asm in [ogws ptmf.c](https://github.com/doldecomp/ogws/blob/master/src/runtime/ptmf.c#L37). |
| `libs/Runtime/src/runtime.c:101` | `__cvt_fp2unsigned` | body | ORIGINAL-ASM | Same function is asm in [ogws runtime.c](https://github.com/doldecomp/ogws/blob/master/src/runtime/runtime.c#L9). |
| `libs/Runtime/src/runtime.c:138` | `__save_fpr` | body | ORIGINAL-ASM | Same function is asm in [ogws runtime.c](https://github.com/doldecomp/ogws/blob/master/src/runtime/runtime.c#L82). |
| `libs/Runtime/src/runtime.c:182` | `__restore_fpr` | body | ORIGINAL-ASM | Same function is asm in [ogws runtime.c](https://github.com/doldecomp/ogws/blob/master/src/runtime/runtime.c#L95). |
| `libs/Runtime/src/runtime.c:225` | `__save_gpr` | body | ORIGINAL-ASM | Same function is asm in [ogws runtime.c](https://github.com/doldecomp/ogws/blob/master/src/runtime/runtime.c#L108). |
| `libs/Runtime/src/runtime.c:268` | `__restore_gpr` | body | ORIGINAL-ASM | Same function is asm in [ogws runtime.c](https://github.com/doldecomp/ogws/blob/master/src/runtime/runtime.c#L121). |
| `libs/Runtime/src/runtime.c:311` | `__div2u` | body | ORIGINAL-ASM | Same function is asm in [ogws runtime.c](https://github.com/doldecomp/ogws/blob/master/src/runtime/runtime.c#L130). |
| `libs/Runtime/src/runtime.c:384` | `__div2i` | body | ORIGINAL-ASM | Same function is asm in [ogws runtime.c](https://github.com/doldecomp/ogws/blob/master/src/runtime/runtime.c#L214). |
| `libs/Runtime/src/runtime.c:480` | `__mod2u` | body | ORIGINAL-ASM | Same function is asm in [ogws runtime.c](https://github.com/doldecomp/ogws/blob/master/src/runtime/runtime.c#L325). |
| `libs/Runtime/src/runtime.c:551` | `__mod2i` | body | ORIGINAL-ASM | Same function is asm in [ogws runtime.c](https://github.com/doldecomp/ogws/blob/master/src/runtime/runtime.c#L407). |
| `libs/Runtime/src/runtime.c:635` | `__shl2i` | body | ORIGINAL-ASM | Same function is asm in [ogws runtime.c](https://github.com/doldecomp/ogws/blob/master/src/runtime/runtime.c#L505). |
| `libs/Runtime/src/runtime.c:649` | `__shr2u` | body | ORIGINAL-ASM | Compiler shift-helper register convention: r3:r4 is the 64-bit operand/result and r5 is the shift count. |
| `libs/Runtime/src/runtime.c:663` | `__shr2i` | body | ORIGINAL-ASM | Compiler shift-helper register convention: r3:r4 is the 64-bit operand/result and r5 is the shift count. |
| `libs/Runtime/src/runtime.c:679` | `__cvt_sll_dbl` | body | ORIGINAL-ASM | Compiler conversion-helper register convention: r3:r4 input, f1 result, and explicit carry/rounding operations. |
| `libs/Runtime/src/runtime.c:732` | `__cvt_ull_dbl` | body | ORIGINAL-ASM | Compiler conversion-helper register convention: r3:r4 input, f1 result, and explicit carry/rounding operations. |
| `libs/Runtime/src/runtime.c:779` | `__cvt_ull_flt` | body | ORIGINAL-ASM | Compiler conversion-helper register convention: r3:r4 input, f1 result, and explicit carry/rounding operations. |
| `libs/Runtime/src/runtime.c:827` | `__cvt_dbl_usll` | body | ORIGINAL-ASM | Compiler conversion-helper register convention: f1 input and r3:r4 integer result without a recursive compiler conversion call. |
| `libs/Runtime/src/runtime.c:889` | `__cvt_dbl_ull` | body | ORIGINAL-ASM | Same function is asm in [ogws runtime.c](https://github.com/doldecomp/ogws/blob/master/src/runtime/runtime.c#L523). |
