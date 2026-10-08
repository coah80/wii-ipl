# Assembly inventory

4.3U, 2026-10-05. 170 functions contain 172 assembly
bodies/blocks: 162 ORIGINAL functions and 8 PLACEHOLDER functions.

Run `python3 tools/check_asm_inventory.py`. Completion requires exit 0, complete
coverage and zero placeholders. The checker also rejects stale/duplicate rows,
invalid classifications and syntax it cannot inspect. This audit supersedes the
historical inventory in `tools/decomp-assist/asm-inventory.md`.

Scope: C/C++ sources and headers in `src/` and `libs/`, including inactive
platform branches, plus standalone assembly there or referenced by
`configure.py`. There are currently no standalone assembly files in that scope.
One row covers all blocks in a function; runtime save/restore entry labels belong
to their enclosing assembly body. Names use their source spelling. Declarations,
comments and string contents do not count.

ORIGINAL requires hardware, startup, runtime or original SDK assembly evidence.
An SDK path, `nofralloc` alone or an exact assembled object proves no C conversion.
The rvl_dec family follows the original decoder convention specified for this
audit; ASH/ASR also show unsigned `lis @h`/`ori @l` address construction and
hand-built `stmw` frames. C scores below are recorded rejected trials, not fresh
measurements or scores of the retained assembly. Unrecorded means no C score was
found. Historical logs absent from this branch have commit IDs and excerpts in
[the audit log](../tools/decomp-assist/rx36.attempts.md).

| File | Function | Classification | Evidence |
| --- | --- | --- | --- |
| `libs/MetroTRK/src/Export/targsupp.c` | `TRKAccessFile` | ORIGINAL | twi 31,r0,0 is the debugger file-service trap, with debugger-controlled return registers. |
| `libs/MetroTRK/src/Export/targsupp.c` | `TRKOpenFile` | ORIGINAL | twi 31,r0,0 is the debugger file-service trap, with debugger-controlled return registers. |
| `libs/MetroTRK/src/Export/targsupp.c` | `TRKCloseFile` | ORIGINAL | twi 31,r0,0 is the debugger file-service trap, with debugger-controlled return registers. |
| `libs/MetroTRK/src/Export/targsupp.c` | `TRKPositionFile` | ORIGINAL | twi 31,r0,0 is the debugger file-service trap, with debugger-controlled return registers. |
| `libs/NW4R/include/nw4r/math/arithmetic.h` | `FSelect` | ORIGINAL | fsel inline assembly matches the public [NW4R arithmetic header][arithmetic-h]. |
| `libs/NW4R/include/nw4r/math/arithmetic.h` | `FAbs` | ORIGINAL | fabs inline assembly matches the public [NW4R arithmetic header][arithmetic-h]. |
| `libs/NW4R/include/nw4r/math/types.h` | `VEC3Add` | ORIGINAL | psq_l/ps_add/psq_st implements paired-single vector/matrix operations. |
| `libs/NW4R/include/nw4r/math/types.h` | `VEC3Sub` | ORIGINAL | psq_l/ps_sub/psq_st implements paired-single vector/matrix operations. |
| `libs/NW4R/include/nw4r/math/types.h` | `VEC3Scale` | ORIGINAL | psq_l/ps_muls0/psq_st implements paired-single vector/matrix operations. |
| `libs/NW4R/src/math/math_arithmetic.cpp` | `FrSqrt` | ORIGINAL | frsqrte plus fixed refinement matches the public [NW4R arithmetic assembly][arithmetic-cpp]. |
| `libs/NW4R/src/math/math_types.cpp` | `MTX44Identity` | ORIGINAL | psq_st/ps_merge01/ps_merge10 implements paired-single vector/matrix operations. |
| `libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main.c` | `TMCJPEGDEC_err_restart` | PLACEHOLDER | JPEG marker scan; best C 95.73913%, 114/115 instructions, folded exit branch, [rx19](../tools/decomp-assist/rx19.attempts.md), [rx24][rx24]. |
| `libs/RVL_SDK/include/revolution/os/OSFastCast.h` | `OSInitFastCast` | ORIGINAL | mtspr programs the GQR quantization registers. |
| `libs/RVL_SDK/include/revolution/os/OSFastCast.h` | `__OSu16tof32` | ORIGINAL | psq_l uses a GQR integer conversion format for the fast cast. |
| `libs/RVL_SDK/include/revolution/os/OSFastCast.h` | `__OSf32tou8` | ORIGINAL | psq_st uses a GQR integer conversion format for the fast cast. |
| `libs/RVL_SDK/include/revolution/os/OSFastCast.h` | `__OSf32tou16` | ORIGINAL | psq_st uses a GQR integer conversion format for the fast cast. |
| `libs/RVL_SDK/include/revolution/os/OSFastCast.h` | `__OSs16tof32` | ORIGINAL | psq_l uses a GQR integer conversion format for the fast cast. |
| `libs/RVL_SDK/include/revolution/os/OSFastCast.h` | `__OSf32tos16` | ORIGINAL | psq_st uses a GQR integer conversion format for the fast cast. |
| `libs/RVL_SDK/src/ai/ai.c` | `__AICallbackStackSwitch` | ORIGINAL | Saves r1 to __OldStack, installs __CallbackStack, calls through LR, then restores r1. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMfmsr` | ORIGINAL | Special-register or synchronization operation: `mfmsr r3`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMtmsr` | ORIGINAL | Special-register or synchronization operation: `mtmsr newMSR`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCOrMsr` | ORIGINAL | Special-register or synchronization operation: `mfmsr r4`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCAndMsr` | ORIGINAL | Special-register or synchronization operation: `mfmsr r4`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCAndCMsr` | ORIGINAL | Special-register or synchronization operation: `mfmsr r4`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMfhid0` | ORIGINAL | Special-register or synchronization operation: `mfspr r3, HID0`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMthid0` | ORIGINAL | Special-register or synchronization operation: `mtspr HID0, newHID0`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMfhid1` | ORIGINAL | Special-register or synchronization operation: `mfspr r3, HID1`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMfl2cr` | ORIGINAL | Special-register or synchronization operation: `mfspr r3, L2CR`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMtl2cr` | ORIGINAL | Special-register or synchronization operation: `mtspr L2CR, newL2cr`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMtdec` | ORIGINAL | Special-register or synchronization operation: `mtdec newDec`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMfdec` | ORIGINAL | Special-register or synchronization operation: `mfdec r3`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCSync` | ORIGINAL | Special-register or synchronization operation: `sc`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCEieio` | ORIGINAL | Special-register or synchronization operation: `mfmsr r5`, `mtmsr r6`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCHalt` | ORIGINAL | Special-register or synchronization operation: `sync`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMfmmcr0` | ORIGINAL | Special-register or synchronization operation: `mfspr r3, MMCR0`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMtmmcr0` | ORIGINAL | Special-register or synchronization operation: `mtspr MMCR0, newMmcr0`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMfmmcr1` | ORIGINAL | Special-register or synchronization operation: `mfspr r3, MMCR1`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMtmmcr1` | ORIGINAL | Special-register or synchronization operation: `mtspr MMCR1, newMmcr1`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMfpmc1` | ORIGINAL | Special-register or synchronization operation: `mfspr r3, PMC1`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMtpmc1` | ORIGINAL | Special-register or synchronization operation: `mtspr PMC1, newPmc1`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMfpmc2` | ORIGINAL | Special-register or synchronization operation: `mfspr r3, PMC2`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMtpmc2` | ORIGINAL | Special-register or synchronization operation: `mtspr PMC2, newPmc2`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMfpmc3` | ORIGINAL | Special-register or synchronization operation: `mfspr r3, PMC3`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMtpmc3` | ORIGINAL | Special-register or synchronization operation: `mtspr PMC3, newPmc3`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMfpmc4` | ORIGINAL | Special-register or synchronization operation: `mfspr r3, PMC4`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMtpmc4` | ORIGINAL | Special-register or synchronization operation: `mtspr PMC4, newPmc4`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMffpscr` | ORIGINAL | Special-register or synchronization operation: `mffs fp31`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMfsia` | ORIGINAL | Special-register or synchronization operation: `mfspr r3, SIA`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMtsia` | ORIGINAL | Special-register or synchronization operation: `mtspr SIA, newSia`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMtfpscr` | ORIGINAL | Special-register or synchronization operation: `mtfsf 0xff, fp31`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMfhid2` | ORIGINAL | Special-register or synchronization operation: `mfspr r3, HID2`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMthid2` | ORIGINAL | Special-register or synchronization operation: `mtspr HID2, newhid2`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMfwpar` | ORIGINAL | Special-register or synchronization operation: `sync`, `mfspr r3, WPAR`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMtwpar` | ORIGINAL | Special-register or synchronization operation: `mtspr WPAR, newwpar`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMfdmaU` | ORIGINAL | Special-register or synchronization operation: `mfspr r3, DMA_U`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMfdmaL` | ORIGINAL | Special-register or synchronization operation: `mfspr r3, DMA_L`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMtdmaU` | ORIGINAL | Special-register or synchronization operation: `mtspr DMA_U, newdmau`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMtdmaL` | ORIGINAL | Special-register or synchronization operation: `mtspr DMA_L, newdmal`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMfpvr` | ORIGINAL | Special-register or synchronization operation: `mfspr r3, PVR`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCSetFpIEEEMode` | ORIGINAL | Special-register or synchronization operation: `mtfsb0 FPSCR_NI_BIT`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCSetFpNonIEEEMode` | ORIGINAL | Special-register or synchronization operation: `mtfsb1 FPSCR_NI_BIT`. |
| `libs/RVL_SDK/src/base/PPCArch.c` | `PPCMthid4` | ORIGINAL | Both branches write HID4 with mtspr; the fallback preserves the Broadway H4A bit. |
| `libs/RVL_SDK/src/cntcache/cntcache.c` | `CNTCACHEClear` | PLACEHOLDER | NAND/token logic; best C 47/151 differing, 149/151 instructions; pool solved with stripped writer literals, two post-delete compares missing, [rx30][rx30], [opus-cntc](../tools/decomp-assist/opus-cntc.attempts.md). |
| `libs/RVL_SDK/src/db/db.c` | `__DBExceptionDestination` | ORIGINAL | mfmsr/mtmsr enable address translation before the exception-handler tail branch. |
| `libs/RVL_SDK/src/gx/GXLight.c` | `PushLight` | ORIGINAL | psq_l/psq_st transfers paired-single values for the GX command stream. |
| `libs/RVL_SDK/src/gx/GXTransform.c` | `WriteProjPS` | ORIGINAL | psq_l/psq_st transfers paired-single values for the GX command stream. |
| `libs/RVL_SDK/src/gx/GXTransform.c` | `Copy6Floats` | ORIGINAL | psq_l/psq_st copies three pairs of floats. |
| `libs/RVL_SDK/src/gx/GXTransform.c` | `WriteMTXPS4x3` | ORIGINAL | psq_l/psq_st transfers paired-single values for the GX command stream. |
| `libs/RVL_SDK/src/gx/GXTransform.c` | `WriteMTXPS3x3from3x4` | ORIGINAL | psq_l/psq_st transfers paired-single values for the GX command stream. |
| `libs/RVL_SDK/src/gx/GXTransform.c` | `WriteMTXPS4x2` | ORIGINAL | psq_l/psq_st transfers paired-single values for the GX command stream. |
| `libs/RVL_SDK/src/mtx/mtx.c` | `PSMTXIdentity` | ORIGINAL | psq_st/ps_merge01/ps_merge10 implements paired-single vector/matrix operations. |
| `libs/RVL_SDK/src/mtx/mtx.c` | `PSMTXCopy` | ORIGINAL | psq_l/psq_st implements paired-single vector/matrix operations. |
| `libs/RVL_SDK/src/mtx/mtx.c` | `PSMTXConcat` | ORIGINAL | psq_l/ps_muls0/ps_madds1/ps_madds0 implements paired-single vector/matrix operations. |
| `libs/RVL_SDK/src/mtx/mtx.c` | `PSMTXInverse` | ORIGINAL | psq_l/ps_merge10/ps_mul/ps_msub implements paired-single vector/matrix operations. |
| `libs/RVL_SDK/src/mtx/mtx.c` | `PSMTXInvXpose` | ORIGINAL | psq_l/ps_merge10/ps_mul/ps_msub implements paired-single vector/matrix operations. |
| `libs/RVL_SDK/src/mtx/mtx.c` | `PSMTXRotTrig` | ORIGINAL | Two blocks use frsp, ps_neg, ps_merge00 and psq_st to construct a paired-single rotation. |
| `libs/RVL_SDK/src/mtx/mtx.c` | `PSMTXTrans` | ORIGINAL | psq_st implements paired-single vector/matrix operations. |
| `libs/RVL_SDK/src/mtx/mtx.c` | `PSMTXTransApply` | ORIGINAL | psq_l/psq_st/ps_sum1 implements paired-single vector/matrix operations. |
| `libs/RVL_SDK/src/mtx/mtx.c` | `PSMTXScale` | ORIGINAL | psq_st implements paired-single vector/matrix operations. |
| `libs/RVL_SDK/src/mtx/mtx.c` | `PSMTXScaleApply` | ORIGINAL | psq_l/ps_muls0/psq_st implements paired-single vector/matrix operations. |
| `libs/RVL_SDK/src/mtx/mtxvec.c` | `PSMTXMultVec` | ORIGINAL | psq_l/ps_mul/ps_madd/ps_sum0 implements paired-single vector/matrix operations. |
| `libs/RVL_SDK/src/mtx/vec.c` | `PSVECNormalize` | ORIGINAL | psq_l/ps_mul/ps_madd/ps_sum0 implements paired-single vector/matrix operations. |
| `libs/RVL_SDK/src/mtx/vec.c` | `PSVECCrossProduct` | ORIGINAL | psq_l/ps_merge10/ps_mul/ps_muls0 implements paired-single vector/matrix operations. |
| `libs/RVL_SDK/src/os/OS.c` | `__OSFPRInit` | ORIGINAL | mfmsr/mtmsr enable the FPU; psq_l initializes paired registers and mtfsf initializes FPSCR. |
| `libs/RVL_SDK/src/os/OS.c` | `__OSDBIntegrator` | ORIGINAL | nofralloc debug-vector fragment changes MSR and transfers through the saved hook LR. |
| `libs/RVL_SDK/src/os/OS.c` | `__OSDBJump` | ORIGINAL | Single absolute bla __OSDBJumpTarget between entry labels copied into exception vectors. |
| `libs/RVL_SDK/src/os/OS.c` | `OSExceptionVector` | ORIGINAL | Saves interrupted state, sets SRR0/SRR1 and executes rfi into the exception handler. |
| `libs/RVL_SDK/src/os/OS.c` | `OSDefaultExceptionHandler` | ORIGINAL | Captures GQR1..7 with mfspr and interrupted r13..31 with stmw before dispatch. |
| `libs/RVL_SDK/src/os/OS.c` | `__OSPSInit` | ORIGINAL | mtspr initializes GQR0..7 for paired-single quantization. |
| `libs/RVL_SDK/src/os/OSAlarm.c` | `DecrementerExceptionHandler` | ORIGINAL | Saves interrupted GPRs and GQR1..7 via stmw/mfspr before the C callback. |
| `libs/RVL_SDK/src/os/OSCache.c` | `DCEnable` | ORIGINAL | sync and HID0 mfspr/mtspr enable the data cache. |
| `libs/RVL_SDK/src/os/OSCache.c` | `DCInvalidateRange` | ORIGINAL | dcbi invalidates each cache line. |
| `libs/RVL_SDK/src/os/OSCache.c` | `DCFlushRange` | ORIGINAL | dcbf flushes cache lines; sc invokes the synchronization vector. |
| `libs/RVL_SDK/src/os/OSCache.c` | `DCStoreRange` | ORIGINAL | dcbst writes cache lines; sc invokes the synchronization vector. |
| `libs/RVL_SDK/src/os/OSCache.c` | `DCFlushRangeNoSync` | ORIGINAL | dcbf flushes cache lines without the synchronization call. |
| `libs/RVL_SDK/src/os/OSCache.c` | `DCZeroRange` | ORIGINAL | dcbz zeroes each cache line. |
| `libs/RVL_SDK/src/os/OSCache.c` | `ICInvalidateRange` | ORIGINAL | icbi invalidates instructions, followed by sync/isync. |
| `libs/RVL_SDK/src/os/OSCache.c` | `ICFlashInvalidate` | ORIGINAL | HID0 mfspr/mtspr triggers instruction-cache flash invalidation. |
| `libs/RVL_SDK/src/os/OSCache.c` | `ICEnable` | ORIGINAL | isync and HID0 mfspr/mtspr enable the instruction cache. |
| `libs/RVL_SDK/src/os/OSCache.c` | `LCDisable` | ORIGINAL | dcbi clears locked-cache lines; HID2 mfspr/mtspr disables the locked cache. |
| `libs/RVL_SDK/src/os/OSContext.c` | `__OSLoadFPUContext` | ORIGINAL | Restores caller FPRs, FPSCR and paired-single halves using mtfsf/psq_l. |
| `libs/RVL_SDK/src/os/OSContext.c` | `__OSSaveFPUContext` | ORIGINAL | Captures caller FPSCR/FPRs and paired-single halves using mffs/psq_st. |
| `libs/RVL_SDK/src/os/OSContext.c` | `OSLoadFPUContext` | ORIGINAL | Moves context to r4 and tail-branches to __OSLoadFPUContext, which replaces caller FPRs. |
| `libs/RVL_SDK/src/os/OSContext.c` | `OSSaveFPUContext` | ORIGINAL | Moves context to r5 and tail-branches to __OSSaveFPUContext before caller FPRs change. |
| `libs/RVL_SDK/src/os/OSContext.c` | `OSSetCurrentContext` | ORIGINAL | mfmsr/mtmsr/isync change the FPU-enable bit while installing context pointers. |
| `libs/RVL_SDK/src/os/OSContext.c` | `OSSaveContext` | ORIGINAL | Captures caller r1/r2, GPRs, GQR1..7, CR, LR, XER and MSR for a later nonlocal return. |
| `libs/RVL_SDK/src/os/OSContext.c` | `OSLoadContext` | ORIGINAL | Restores GPRs and GQR1..7, sets SRR0/SRR1 and resumes interrupted execution with rfi. |
| `libs/RVL_SDK/src/os/OSContext.c` | `OSGetStackPointer` | ORIGINAL | nofralloc leaf returns the caller stack pointer directly with mr r3,r1. |
| `libs/RVL_SDK/src/os/OSContext.c` | `OSSwitchStack` | ORIGINAL | Returns the old r1 and installs the supplied stack pointer directly. |
| `libs/RVL_SDK/src/os/OSContext.c` | `OSSwitchFiber` | ORIGINAL | Installs another r1 and calls the supplied PC through LR; restores the old stack afterward. |
| `libs/RVL_SDK/src/os/OSContext.c` | `OSSwitchFiberEx` | ORIGINAL | Preserves r3..r6 arguments while switching r1 and calling the supplied PC through LR. |
| `libs/RVL_SDK/src/os/OSContext.c` | `OSInitContext` | ORIGINAL | Copies live ABI registers r2/r13 directly and seeds SRR state for a new execution context. |
| `libs/RVL_SDK/src/os/OSContext.c` | `OSSwitchFPUContext` | ORIGINAL | mfmsr/mtmsr/isync enable the FPU; the exception path restores SRR state and uses rfi. |
| `libs/RVL_SDK/src/os/OSContext.c` | `OSFillFPUContext` | ORIGINAL | mfmsr/mtmsr/isync enable the FPU before mffs and paired-single register saves. |
| `libs/RVL_SDK/src/os/OSInterrupt.c` | `OSDisableInterrupts` | ORIGINAL | mfmsr/mtmsr read and clear MSR_EE atomically within the restartable sequence. |
| `libs/RVL_SDK/src/os/OSInterrupt.c` | `OSEnableInterrupts` | ORIGINAL | mfmsr/mtmsr read and set MSR_EE. |
| `libs/RVL_SDK/src/os/OSInterrupt.c` | `OSRestoreInterrupts` | ORIGINAL | mfmsr/mtmsr replace MSR_EE with the saved interrupt state. |
| `libs/RVL_SDK/src/os/OSInterrupt.c` | `ExternalInterruptHandler` | ORIGINAL | Captures interrupted GPRs and GQR1..7 with stmw/mfspr before C interrupt dispatch. |
| `libs/RVL_SDK/src/os/OSMemory.c` | `ConfigMEM1_24MB` | ORIGINAL | isync and mtspr program IBAT/DBAT mappings; SRR0/SRR1 and rfi return with translation enabled. |
| `libs/RVL_SDK/src/os/OSMemory.c` | `ConfigMEM1_48MB` | ORIGINAL | isync and mtspr program IBAT/DBAT mappings; SRR0/SRR1 and rfi return with translation enabled. |
| `libs/RVL_SDK/src/os/OSMemory.c` | `ConfigMEM2_52MB` | ORIGINAL | isync and mtspr program IBAT/DBAT mappings; SRR0/SRR1 and rfi return with translation enabled. |
| `libs/RVL_SDK/src/os/OSMemory.c` | `ConfigMEM2_56MB` | ORIGINAL | isync and mtspr program IBAT/DBAT mappings; SRR0/SRR1 and rfi return with translation enabled. |
| `libs/RVL_SDK/src/os/OSMemory.c` | `ConfigMEM2_64MB` | ORIGINAL | isync and mtspr program IBAT/DBAT mappings; SRR0/SRR1 and rfi return with translation enabled. |
| `libs/RVL_SDK/src/os/OSMemory.c` | `ConfigMEM2_112MB` | ORIGINAL | isync and mtspr program IBAT/DBAT mappings; SRR0/SRR1 and rfi return with translation enabled. |
| `libs/RVL_SDK/src/os/OSMemory.c` | `ConfigMEM2_128MB` | ORIGINAL | isync and mtspr program IBAT/DBAT mappings; SRR0/SRR1 and rfi return with translation enabled. |
| `libs/RVL_SDK/src/os/OSMemory.c` | `ConfigMEM_ES1_0` | ORIGINAL | isync and mtspr program IBAT/DBAT mappings; SRR0/SRR1 and rfi return with translation enabled. |
| `libs/RVL_SDK/src/os/OSMemory.c` | `RealMode` | ORIGINAL | Writes SRR0/SRR1 and executes rfi with address translation disabled. |
| `libs/RVL_SDK/src/os/OSSync.c` | `SystemCallVector` | ORIGINAL | Changes HID0 with mfspr/mtspr around sync/isync, then returns with rfi. |
| `libs/RVL_SDK/src/os/OSTime.c` | `OSGetTime` | ORIGINAL | mftbu/mftb/mftbu retries until the upper time-base word is stable. |
| `libs/RVL_SDK/src/os/OSTime.c` | `OSGetTick` | ORIGINAL | mftb reads the hardware time-base register. |
| `libs/RVL_SDK/src/os/OSTime.c` | `__SetTime` | ORIGINAL | mttbl/mttbu/mttbl updates the hardware time base in a fixed sequence. |
| `libs/RVL_SDK/src/os/__ppc_eabi_init.cpp` | `__init_hardware` | ORIGINAL | Before normal C startup, mfmsr/mtmsr enables the FPU and r31 holds LR across init calls. |
| `libs/RVL_SDK/src/os/__ppc_eabi_init.cpp` | `__flush_cache` | ORIGINAL | dcbst/sync/icbi/isync make freshly initialized code visible to instruction fetch. |
| `libs/RVL_SDK/src/os/__ppc_eabi_init.cpp` | `__init_user` | ORIGINAL | fralloc/bl __init_cpp/frfree/blr matches the public [SDK startup assembly][sdk-init]. |
| `libs/RevoEX/src/nwc24/NWC24UserId.c` | `getUnScrambleId` | PLACEHOLDER | Integer byte permutation; best C 76.27329%, 161/161 instructions, 97 register/scheduling differences, [rx30][rx30]. |
| `libs/Runtime/src/Gecko_setjmp.c` | `__setjmp` | ORIGINAL | Saves or restores caller GPRs/FPRs, LR, CR, and stack state across nonlocal returns. |
| `libs/Runtime/src/Gecko_setjmp.c` | `longjmp` | ORIGINAL | Saves or restores caller GPRs/FPRs, LR, CR, and stack state across nonlocal returns. |
| `libs/Runtime/src/__init_cpp_exceptions.cpp` | `__exception_info_constants` | ORIGINAL | Reads the caller ABI TOC register r2 directly for exception registration. |
| `libs/Runtime/src/ptmf.c` | `__ptmf_scall` | ORIGINAL | Special compiler ABI takes the member-function descriptor in r12 and tail-dispatches through CTR. |
| `libs/Runtime/src/runtime.c` | `__cvt_fp2unsigned` | ORIGINAL | Unsigned conversion runtime helper with explicit CR0/CR6/CR7 tests; [public runtime assembly][runtime]. |
| `libs/Runtime/src/runtime.c` | `__save_fpr` | ORIGINAL | Entry labels _savefpr_14..31 store caller FPRs relative to r11 without an ABI call frame. |
| `libs/Runtime/src/runtime.c` | `__restore_fpr` | ORIGINAL | Entry labels _restfpr_14..31 reload caller FPRs relative to r11 without an ABI call frame. |
| `libs/Runtime/src/runtime.c` | `__save_gpr` | ORIGINAL | Entry labels _savegpr_14..31 store caller GPRs relative to r11 without an ABI call frame. |
| `libs/Runtime/src/runtime.c` | `__restore_gpr` | ORIGINAL | Entry labels _restgpr_14..31 reload caller GPRs relative to r11 without an ABI call frame. |
| `libs/Runtime/src/runtime.c` | `__div2u` | ORIGINAL | 64-bit compiler division helper uses r3:r4/r5:r6 and carry chains; [public assembly][runtime]. |
| `libs/Runtime/src/runtime.c` | `__div2i` | ORIGINAL | Signed 64-bit compiler division helper manages register-pair signs/carry; [public assembly][runtime]. |
| `libs/Runtime/src/runtime.c` | `__mod2u` | ORIGINAL | 64-bit compiler remainder helper uses register-pair restoring division; [public assembly][runtime]. |
| `libs/Runtime/src/runtime.c` | `__mod2i` | ORIGINAL | Signed 64-bit compiler remainder helper manages register-pair signs/carry; [public assembly][runtime]. |
| `libs/Runtime/src/runtime.c` | `__shl2i` | ORIGINAL | Compiler helper shifts r3:r4 by r5 without recursively calling the 64-bit shift helper. |
| `libs/Runtime/src/runtime.c` | `__shr2u` | ORIGINAL | Compiler helper shifts unsigned r3:r4 by r5 across the word boundary. |
| `libs/Runtime/src/runtime.c` | `__shr2i` | ORIGINAL | Compiler helper shifts signed r3:r4 by r5, explicitly propagating the sign. |
| `libs/Runtime/src/runtime.c` | `__cvt_sll_dbl` | ORIGINAL | Compiler conversion ABI uses r3:r4 input and f1 result with explicit carry/rounding. |
| `libs/Runtime/src/runtime.c` | `__cvt_ull_dbl` | ORIGINAL | Compiler conversion ABI uses r3:r4 input and f1 result with explicit carry/rounding. |
| `libs/Runtime/src/runtime.c` | `__cvt_ull_flt` | ORIGINAL | Compiler conversion ABI uses r3:r4 input and f1 result with explicit single-precision rounding. |
| `libs/Runtime/src/runtime.c` | `__cvt_dbl_usll` | ORIGINAL | Compiler conversion ABI uses f1 input and r3:r4 result without a recursive conversion call. |
| `libs/Runtime/src/runtime.c` | `__cvt_dbl_ull` | ORIGINAL | Compiler conversion helper decodes f1 into r3:r4; [public runtime assembly][runtime]. |
| `src/BS2/BS2Init.c` | `ClearOtherBATs` | ORIGINAL | isync and direct IBAT/DBAT register writes. |
| `src/BS2/BS2Mach.c` | `Run` | ORIGINAL | Clears ABI registers, replaces r1, uses dcbz/dcbf, and jumps via LR. |
| `src/BS2/BS2Start.c` | `__start` | ORIGINAL | Runs before the C stack and ABI registers exist; constructs the initial stack. |
| `src/BS2/BS2Start.c` | `__init_registers` | ORIGINAL | Initializes GPRs, r1, r2, and r13 for the C runtime. |
| `src/scene/nakamuraTest/gamespy/common/gsPlatformUtil.c` | `GetTicks` | ORIGINAL | Inactive PS2 branch reads the CP0 Count register with mfc0 $9. |
| `src/system/iplChannelManager.cpp` | `getTitleName__Q33ipl7channel7ManagerCFiii` | PLACEHOLDER | Channel-name copying; best C 99.57746%, 71/71 instructions, four address-order differences, [rx17][rx17]. |
| `src/system/iplSaveDataManager.cpp` | `Manager::hasChannel` | PLACEHOLDER | Title-slot search; best C 98.87324%, 71/71 instructions, 14 mask/base register differences, [rx30][rx30]. |
| `src/system/iplSystem.cpp` | `System::warning_run` | PLACEHOLDER | Scene/render calls; best C 98.66477%, 176/176 instructions, 47 saved-register differences, [rx17][rx17]. |
| `src/system/rvl_dec.c` | `Rvl_decode` | ORIGINAL | Direct beq decoder entries preserve r3/r4 and LR; lis/ori builds the format signatures. |
| `src/system/rvl_dec.c` | `Rvl_decode_szs` | ORIGINAL | Original SZS decoder convention: nofralloc, r0 retains output length, fixed r3..r10/CTR byte-copy pipeline. |
| `src/system/rvl_dec.c` | `Rvl_decode_ash` | ORIGINAL | nofralloc hand-built 0x40 frame saves r21..31 with stmw; work address uses lis @h/ori @l. |
| `src/system/rvl_dec.c` | `Rvl_decode_asr` | ORIGINAL | nofralloc hand-built 0x40 frame saves r21..31 with stmw; work address uses lis @h/ori @l. |

[rx17]: ../tools/decomp-assist/rx36.attempts.md#rx17
[rx24]: ../tools/decomp-assist/rx36.attempts.md#rx24
[rx30]: ../tools/decomp-assist/rx36.attempts.md#rx30
[rx36-osinit]: ../tools/decomp-assist/rx36.attempts.md#osinit
[sdk-init]: https://github.com/doldecomp/ogws/blob/master/src/revolution/OS/__ppc_eabi_init.c
[runtime]: https://github.com/doldecomp/ogws/blob/master/src/runtime/runtime.c
[arithmetic-h]: https://github.com/doldecomp/ogws/blob/master/include/nw4r/math/math_arithmetic.h
[arithmetic-cpp]: https://github.com/doldecomp/ogws/blob/master/src/nw4r/math/math_arithmetic.cpp
