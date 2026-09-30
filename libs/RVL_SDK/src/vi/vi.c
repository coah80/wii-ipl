#define VI_MATCHING_SOURCE
#include <private/vi.h>
#include <private/vistructs.h>
#include <private/hollywood/flipper.h>
#include <private/dvd.h>
#include <private/os/OSInterrupt.h>
#include <private/os/OSTime.h>
#include <revolution/os.h>
#include <revolution/os/OSReset.h>
#include <revolution/sc.h>

extern void SIRefreshSamplingRate(void);
extern void VISetRGBModeImm(void);
extern void __VISetRevolutionModeSimple(void);
extern u32 Vdac_Flag_Changed_816991E0;
extern void __VISetYUVSEL(u32 enable);
extern void __VISetFilter4EURGB60(u32 enable);
extern void __VISetCGMS(void);
extern void __VISetWSS(void);
extern void __VISetClosedCaption(void);
extern void __VISetMacrovision(void);
extern void __VISetGamma(void);
extern void __VISetTrapFilter(void);
extern void __VISetRGBOverDrive(void);
extern DVDCommandBlock __DVDStopMotorCommandBlock;
extern u64 __shl2i(u64 value, s32 shift);

const char* __VIVersion =
    "<< RVL_SDK - VI \trelease build: Apr 20 2010 11:20:54 (0x4199_60831) >>";

static u16 shdwRegs[59];
static u16 regs[59];
static VIHorVer HorVer;
static u32 __VIDimmingFlag_DEV_IDLE[10];
static u32 IsInitialized;
static u32 vsync_timing_err_cnt;
static u32 vsync_timing_test_flag;

static VITiming timing[11] = {
    { 6, 240, 24, 25, 3, 2, 12, 13, 12, 13, 520, 519, 520, 519, 525, 429, 64, 71, 105, 162, 373, 122, 412 },
    { 6, 240, 24, 24, 4, 4, 12, 12, 12, 12, 520, 520, 520, 520, 526, 429, 64, 71, 105, 162, 373, 122, 412 },
    { 5, 287, 35, 36, 1, 0, 13, 12, 11, 10, 619, 618, 617, 620, 625, 432, 64, 75, 106, 172, 380, 133, 420 },
    { 5, 287, 33, 33, 2, 2, 13, 11, 13, 11, 619, 621, 619, 621, 624, 432, 64, 75, 106, 172, 380, 133, 420 },
    { 6, 240, 24, 25, 3, 2, 16, 15, 14, 13, 518, 517, 516, 519, 525, 429, 64, 78, 112, 162, 373, 122, 412 },
    { 6, 240, 24, 24, 4, 4, 16, 14, 16, 14, 518, 520, 518, 520, 526, 429, 64, 78, 112, 162, 373, 122, 412 },
    { 12, 480, 48, 48, 6, 6, 24, 24, 24, 24, 1038, 1038, 1038, 1038, 1050, 429, 64, 71, 105, 162, 373, 122, 412 },
    { 12, 480, 44, 44, 10, 10, 24, 24, 24, 24, 1038, 1038, 1038, 1038, 1050, 429, 64, 71, 105, 168, 379, 122, 412 },
    { 6, 241, 24, 25, 1, 0, 12, 13, 12, 13, 520, 519, 520, 519, 525, 429, 64, 71, 105, 159, 370, 122, 412 },
    { 12, 480, 48, 48, 6, 6, 24, 24, 24, 24, 1038, 1038, 1038, 1038, 1050, 429, 64, 71, 105, 180, 391, 122, 412 },
    { 10, 576, 62, 62, 6, 6, 20, 20, 20, 20, 1240, 1240, 1240, 1240, 1250, 432, 64, 75, 106, 172, 380, 122, 412 },
};

static u16 taps[25] = {
    0x01F0, 0x01DC, 0x01AE, 0x0174, 0x0129, 0x00DB, 0x008E, 0x0046, 0x000C,
    0x00E2, 0x00CB, 0x00C0, 0x00C4, 0x00CF, 0x00DE, 0x00EC, 0x00FC, 0x0008,
    0x000F, 0x0013, 0x0013, 0x000F, 0x000C, 0x0008, 0x0001,
};

static VIRetraceCallback PreCB;
static VIRetraceCallback PostCB;
static void (*PositionCallback)(s16, s16);
static VITiming* timingExtra;
static void* CurrBufAddr;
static u32 encoderType;
static u32 retraceCount;
static OSThreadQueue retraceQueue;
static u64 changed;
static u64 shdwChanged;
static u32 changeMode;
static u32 shdwChangeMode;
static u32 FBSet;
static u32 flushFlag;
static u32 flushFlag3in1;
static u32 NextBufAddr;
static s16 displayOffsetH;
static s16 displayOffsetV;
static u32 CurrTvMode;
static VITiming* CurrTiming;
static u32 __VIDimming_All_Clear;
static u32 __VIDimmingState;
static u32 _gIdleCount_dimming;
static u32 _gIdleCount_dvd;
static u32 __VIDimmingFlag_SI_IDLE;
static u32 __VIDimmingFlag_RF_IDLE;
static BOOL __VIDVDStopFlag_Enable;
static BOOL __VIDimmingFlag_Enable;
static s32 g_current_time_to_dim;
static u32 THD_TIME_TO_DIMMING;
static u32 NEW_TIME_TO_DIMMING;
static u32 THD_TIME_TO_DVD_STOP;

#define MARK_CHANGED(index) (changed |= (1LL << (63 - (index))))
#pragma dont_inline on
static VITiming* getTiming(VITVMode mode);
static void AdjustPosition(u16 acv);
static s32 cntlzd(u64 bits);
static u32 getCurrentHalfLine(void);
void __VIDisplayPositionToXY(u32 horizontalCount, u32 verticalCount,
                             s16* pixelX, s16* pixelY);
#pragma dont_inline reset

static BOOL OnShutdown(BOOL final, u32 event)
{
    static BOOL first = TRUE;
    static u32 previousRetraceCount;
    BOOL enabled;
    s32 registerIndex;

    if (final) {
        goto returnTrue;
    }
    if ((s32)event < 4) {
        if (event == 0) {
            goto returnTrue;
        }
        if ((s32)event >= 0) {
            goto beginShutdown;
        }
        return final;
    }
    if ((s32)event >= 7) {
        return final;
    }
    goto returnTrue;
beginShutdown:
    if (first) {
        VISetRGBModeImm();
        enabled = OSDisableInterrupts();
        shdwChangeMode |= changeMode;
        changeMode = 0;
        shdwChanged |= changed;
        while (changed != 0) {
            registerIndex = cntlzd(changed);
            shdwRegs[registerIndex] = regs[registerIndex];
            changed &= ~__shl2i((u64)1, 63 - registerIndex);
        }
        flushFlag = 1;
        flushFlag3in1 = 1;
        NextBufAddr = HorVer.bufAddr;
        OSRestoreInterrupts(enabled);
        previousRetraceCount = retraceCount;
        first = FALSE;
        return FALSE;
    }
    if (previousRetraceCount == retraceCount) {
        return FALSE;
    }
    goto returnTrue;

returnTrue:
    return TRUE;
}

static OSShutdownFunctionInfo shutdownFunction = { OnShutdown, 0x7F, 0, 0 };

static BOOL VISetRegs(void)
{
    u32 halfLine;
    s32 registerIndex;

    if (shdwChangeMode == 1) {
        halfLine = getCurrentHalfLine();
        if (halfLine >= CurrTiming->nhlines) {
            return FALSE;
        }
    }
    while (shdwChanged != 0) {
        registerIndex = cntlzd(shdwChanged);
        __VIRegs[registerIndex] = shdwRegs[registerIndex];
        shdwChanged &= ~((u64)1 << (63 - registerIndex));
    }
    shdwChangeMode = 0;
    CurrTiming = HorVer.timing;
    CurrTvMode = HorVer.tv;
    CurrBufAddr = (void*)NextBufAddr;
    return TRUE;
}

static void __VIRetraceHandler(__OSInterrupt interrupt, OSContext* context)
{
    OSContext exceptionContext;
    u16 registerValue;
    u32 interruptFlags;
    static u32 oldDtvStatus = 999;
    static u32 oldTvType = 999;
    static BOOL oldDimmingEnable = TRUE;
    static BOOL oldDvdStopEnable = TRUE;
    static u32 dimmingOnPending;
    static u32 dimmingOffPending;
    u32 currentDtvStatus;
    u32 currentTvType;
    u32 changeBit;
    u32 deviceIndex;

    interruptFlags = 0;
    registerValue = __VIRegs[0x18];
    if (registerValue & 0x8000) {
        __VIRegs[0x18] = registerValue & ~0x8000;
        interruptFlags |= 1;
    }
    registerValue = __VIRegs[0x1A];
    if (registerValue & 0x8000) {
        __VIRegs[0x1A] = registerValue & ~0x8000;
        interruptFlags |= 2;
    }
    registerValue = __VIRegs[0x1C];
    if (registerValue & 0x8000) {
        __VIRegs[0x1C] = registerValue & ~0x8000;
        interruptFlags |= 4;
    }
    registerValue = __VIRegs[0x1E];
    if (registerValue & 0x8000) {
        __VIRegs[0x1E] = registerValue & ~0x8000;
        interruptFlags |= 8;
    }
    registerValue = __VIRegs[0x1E];
    if (interruptFlags & 4) {
        goto position_interrupt;
    }
    if (interruptFlags & 8) {
position_interrupt:
    {
        u32 previousVertical;
        u32 horizontal;
        u32 vertical;
        s16 pixelX;
        s16 pixelY;

        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        if (PositionCallback != 0) {
            vertical = __VIRegs[22] & 0x7FF;
            do {
                previousVertical = vertical;
                horizontal = __VIRegs[23] & 0x7FF;
                vertical = __VIRegs[22] & 0x7FF;
            } while (previousVertical != vertical);
            __VIDisplayPositionToXY(horizontal, vertical, &pixelX, &pixelY);
            PositionCallback(pixelX, pixelY);
        }
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
        return;
    }
    }
    retraceCount++;
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);
    if (PreCB != 0) {
        PreCB(retraceCount);
    }
    if (vsync_timing_test_flag != 0) {
        u32 previousVertical;
        u32 horizontal;
        u32 vertical;
        u32 currentLine;

        vertical = __VIRegs[22] & 0x7FF;
        do {
            previousVertical = vertical;
            horizontal = __VIRegs[23] & 0x7FF;
            vertical = __VIRegs[22] & 0x7FF;
        } while (previousVertical != vertical);
        currentLine = (CurrTiming->nhlines / 2) + 1;
        if (vertical != 1 && vertical != currentLine) {
            vsync_timing_err_cnt++;
        }
    }
    if (flushFlag != 0 && VISetRegs()) {
        flushFlag = 0;
        SIRefreshSamplingRate();
    }
    {
        BOOL enabled;

        enabled = OSDisableInterrupts();
        currentDtvStatus = __VIRegs[55] & 3;
        OSRestoreInterrupts(enabled);
    }
    currentDtvStatus &= 1;
    if (currentDtvStatus != oldDtvStatus) {
        __VISetYUVSEL(currentDtvStatus);
    }
    oldDtvStatus = currentDtvStatus;
    {
        BOOL enabled;

        enabled = OSDisableInterrupts();
        currentTvType = CurrTvMode;
        switch (CurrTvMode) {
        case 0:
        case 3:
        case 6:
        case 7:
        case 8:
            currentTvType = 0;
            break;
        case 1:
        case 4:
            currentTvType = 1;
            break;
        }
        OSRestoreInterrupts(enabled);
    }
    if (currentTvType != oldTvType) {
        __VISetFilter4EURGB60(currentTvType == 5);
        if (currentTvType == 1) {
            switch (g_current_time_to_dim) {
            case 1:
                NEW_TIME_TO_DIMMING = 30000;
                break;
            case 2:
                NEW_TIME_TO_DIMMING = 45000;
                break;
            default:
                NEW_TIME_TO_DIMMING = 15000;
                break;
            }
            THD_TIME_TO_DVD_STOP = 90000;
        } else {
            switch (g_current_time_to_dim) {
            case 1:
                NEW_TIME_TO_DIMMING = 36000;
                break;
            case 2:
                NEW_TIME_TO_DIMMING = 54000;
                break;
            default:
                NEW_TIME_TO_DIMMING = 18000;
                break;
            }
            THD_TIME_TO_DVD_STOP = 108000;
        }
        _gIdleCount_dimming = 0;
        _gIdleCount_dvd = 0;
    }
    oldTvType = currentTvType;
    if (flushFlag3in1 != 0) {
        while (Vdac_Flag_Changed_816991E0 != 0) {
            changeBit = 1U << (31 - __cntlzw(Vdac_Flag_Changed_816991E0));
            switch (changeBit) {
            case 1:
                __VISetCGMS();
                break;
            case 2:
                __VISetWSS();
                break;
            case 4:
                __VISetClosedCaption();
                break;
            case 8:
                __VISetMacrovision();
                break;
            case 16:
                __VISetGamma();
                break;
            case 32:
                __VISetTrapFilter();
                break;
            case 64:
                __VISetRGBOverDrive();
                break;
            case 128:
                __VISetRGBModeImm();
                break;
            }
            Vdac_Flag_Changed_816991E0 &= ~changeBit;
        }
        flushFlag3in1 = 0;
    }
    if (PostCB != 0) {
        OSClearContext(&exceptionContext);
        PostCB(retraceCount);
    }
    OSWakeupThread(&retraceQueue);
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
    if (__VIDimming_All_Clear == 1 &&
        __OSSetVIForceDimming(FALSE, 0, 0) == TRUE) {
        __VIDimming_All_Clear = 0;
        _gIdleCount_dimming = 0;
    }
    for (deviceIndex = 0; deviceIndex < 10; deviceIndex++) {
        if (__VIDimmingFlag_DEV_IDLE[deviceIndex] == 0) {
            __VIDimmingFlag_DEV_IDLE[deviceIndex] = 0;
            break;
        }
    }
    if (__VIDimmingFlag_RF_IDLE != 0 && __VIDimmingFlag_SI_IDLE != 0 &&
        __VIDimmingFlag_DEV_IDLE[0] != 0) {
        if (__VIDimmingFlag_Enable == TRUE &&
            _gIdleCount_dimming < 0xFFFFFFFF) {
            _gIdleCount_dimming++;
        }
        if (__VIDVDStopFlag_Enable == TRUE && _gIdleCount_dvd < 0xFFFFFFFF) {
            _gIdleCount_dvd++;
        }
    } else {
        if (_gIdleCount_dimming >= THD_TIME_TO_DIMMING) {
            dimmingOffPending = 1;
        }
        if (_gIdleCount_dvd >= THD_TIME_TO_DVD_STOP) {
            __DVDRestartMotor();
        }
        _gIdleCount_dimming = 0;
        _gIdleCount_dvd = 0;
        THD_TIME_TO_DIMMING = NEW_TIME_TO_DIMMING;
    }
    if (oldDimmingEnable != __VIDimmingFlag_Enable) {
        if (__VIDimmingFlag_Enable == FALSE &&
            _gIdleCount_dimming >= THD_TIME_TO_DIMMING) {
            dimmingOffPending = 1;
        }
        _gIdleCount_dimming = 0;
        THD_TIME_TO_DIMMING = NEW_TIME_TO_DIMMING;
    }
    if (_gIdleCount_dimming == THD_TIME_TO_DIMMING) {
        dimmingOnPending = 1;
    }
    if (dimmingOffPending != 0 &&
        __OSSetVIForceDimming(FALSE, 2, 2) == TRUE) {
        dimmingOffPending = 0;
        __VIDimmingState = 0;
    }
    if (dimmingOnPending != 0 &&
        __OSSetVIForceDimming(TRUE, 2, 2) == TRUE) {
        dimmingOnPending = 0;
        __VIDimmingState = 1;
    }
    if (oldDvdStopEnable != __VIDVDStopFlag_Enable) {
        if (__VIDVDStopFlag_Enable == FALSE &&
            _gIdleCount_dvd >= THD_TIME_TO_DVD_STOP) {
            __DVDRestartMotor();
        }
        _gIdleCount_dvd = 0;
    }
    if (_gIdleCount_dvd == THD_TIME_TO_DVD_STOP) {
        __DVDStopMotorAsync(&__DVDStopMotorCommandBlock, 0);
    }
    __VIDimmingFlag_RF_IDLE = 1;
    __VIDimmingFlag_SI_IDLE = 1;
    for (deviceIndex = 0; deviceIndex < 10; deviceIndex++) {
        __VIDimmingFlag_DEV_IDLE[deviceIndex] = 1;
    }
    oldDimmingEnable = __VIDimmingFlag_Enable;
    oldDvdStopEnable = __VIDVDStopFlag_Enable;
    if (NEW_TIME_TO_DIMMING > _gIdleCount_dimming && __VIDimmingState == 0) {
        THD_TIME_TO_DIMMING = NEW_TIME_TO_DIMMING;
    }
}

VIRetraceCallback VISetPreRetraceCallback(VIRetraceCallback callback)
{
    BOOL enabled;
    VIRetraceCallback oldCallback;

    oldCallback = PreCB;
    enabled = OSDisableInterrupts();
    PreCB = callback;
    OSRestoreInterrupts(enabled);
    return oldCallback;
}

VIRetraceCallback VISetPostRetraceCallback(VIRetraceCallback callback)
{
    BOOL enabled;
    VIRetraceCallback oldCallback;

    oldCallback = PostCB;
    enabled = OSDisableInterrupts();
    PostCB = callback;
    OSRestoreInterrupts(enabled);
    return oldCallback;
}

#pragma dont_inline on
static VITiming* getTiming(VITVMode mode)
{
    switch (mode) {
    case 0:
        return &timing[0];
    case 1:
        return &timing[1];
    case 4:
        return &timing[2];
    case 5:
        return &timing[3];
    case 20:
        return &timing[0];
    case 21:
        return &timing[1];
    case 8:
        return &timing[4];
    case 9:
        return &timing[5];
    case 2:
    case 10:
    case 22:
        return &timing[6];
    case 3:
    case 11:
        return &timing[7];
    case 16:
        return &timing[2];
    case 17:
        return &timing[3];
    case 24:
        return &timing[8];
    case 26:
        return &timing[9];
    case 6:
        return &timing[10];
    case 28:
    case 29:
    case 30:
    case 34:
        return timingExtra;
    default:
        return 0;
    }
}
#pragma dont_inline reset

void __VIInit(VITVMode mode)
{
    VITiming* currentTiming;
    u32 nonInter;
    s32 tv;
    u32 i;
    u16 hct;
    u16 vct;

    nonInter = mode & 3;
    tv = (u32)mode >> 2;
    *(u32*)OSPhysicalToCached(0xCC) = tv;
    currentTiming = getTiming(mode);
    __VIRegs[1] = 2;
    for (i = 0; i < 1000; i++) {
    }
    __VIRegs[1] = 0;
    __VIRegs[3] = currentTiming->hlw;
    __VIRegs[2] = currentTiming->hce | (currentTiming->hcs << 8);
    __VIRegs[5] = currentTiming->hsy | ((currentTiming->hbe640 & 0x1FF) << 7);
    __VIRegs[4] = (currentTiming->hbe640 >> 9) | (currentTiming->hbs640 << 1);
    if (encoderType == 0) {
        __VIRegs[0x39] = currentTiming->hbeCCIR656 | 0x8000;
        __VIRegs[0x3A] = currentTiming->hbsCCIR656;
    }
    __VIRegs[0] = currentTiming->equ;
    __VIRegs[7] = currentTiming->prbOdd + (currentTiming->acv * 2) - 2;
    __VIRegs[6] = currentTiming->psbOdd + 2;
    __VIRegs[9] = currentTiming->prbEven + (currentTiming->acv * 2) - 2;
    __VIRegs[8] = currentTiming->psbEven + 2;
    __VIRegs[11] = currentTiming->bs1 | (currentTiming->be1 << 5);
    __VIRegs[10] = currentTiming->bs3 | (currentTiming->be3 << 5);
    __VIRegs[13] = currentTiming->bs2 | (currentTiming->be2 << 5);
    __VIRegs[12] = currentTiming->bs4 | (currentTiming->be4 << 5);
    __VIRegs[36] = 0x2828;
    __VIRegs[27] = 1;
    __VIRegs[26] = 0x1001;
    hct = currentTiming->hlw + 1;
    vct = (currentTiming->nhlines / 2) + 1;
    __VIRegs[25] = hct;
    __VIRegs[24] = vct | 0x1000;
    switch (tv) {
    case VI_PAL:
    case VI_MPAL:
    case VI_DEBUG:
        break;
    default:
        tv = 0;
        break;
    }
    if (nonInter <= 1) {
        __VIRegs[1] = (nonInter << 2) | 1 | (tv << 8);
        __VIRegs[54] = 0;
    } else {
        __VIRegs[1] = (tv << 8) | 5;
        __VIRegs[54] = 1;
    }
}

static void __VIRetraceHandler(s16 interrupt, OSContext* context);

void VIInit(void)
{
    u16* acv;
    BOOL enabled;
    u16 displayConfig;
    u32 value;
    u32 tv;
    u32 bootromTv;
    u32 scanMode;
    u32 field;

    if (IsInitialized != 0) {
        return;
    }
    OSRegisterVersion(__VIVersion);
    IsInitialized = 1;
    if ((__VIRegs[1] & 1) == 0) {
        __VIInit(0);
    }
    retraceCount = 0;
    changed = 0;
    shdwChanged = 0;
    changeMode = 0;
    shdwChangeMode = 0;
    flushFlag = 0;
    flushFlag3in1 = 0;
    __VIRegs[39] = taps[0] | ((taps[1] & 0x3F) << 10);
    __VIRegs[38] = (taps[1] >> 6) | (taps[2] << 4);
    __VIRegs[41] = taps[3] | ((taps[4] & 0x3F) << 10);
    __VIRegs[40] = (taps[4] >> 6) | (taps[5] << 4);
    __VIRegs[43] = taps[6] | ((taps[7] & 0x3F) << 10);
    __VIRegs[42] = (taps[7] >> 6) | (taps[8] << 4);
    __VIRegs[45] = taps[9] | (taps[10] << 8);
    __VIRegs[44] = taps[11] | (taps[12] << 8);
    __VIRegs[47] = taps[13] | (taps[14] << 8);
    __VIRegs[46] = taps[15] | (taps[16] << 8);
    __VIRegs[49] = taps[17] | (taps[18] << 8);
    __VIRegs[48] = taps[19] | (taps[20] << 8);
    __VIRegs[51] = taps[21] | (taps[22] << 8);
    __VIRegs[50] = taps[23] | (taps[24] << 8);
    __VIRegs[56] = 0x280;
    displayOffsetH = SCGetDisplayOffsetH();
    displayOffsetV = 0;
    bootromTv = *(u32*)0x800000CC;
    displayConfig = __VIRegs[1];
    enabled = OSDisableInterrupts();
    if ((u32)(__VIRegs[54] & 1) == 1U) {
        scanMode = 2;
    } else {
        field = (__VIRegs[1] >> 2) & 1;
        scanMode = ((0U - field) | field) >> 31;
    }
    OSRestoreInterrupts(enabled);
    HorVer.nonInter = scanMode;
    tv = (displayConfig >> 8) & 3;
    HorVer.tv = tv;
    if (bootromTv == 5 || (bootromTv == 1 && tv == 0)) {
        HorVer.tv = 5;
    }
    regs[1] = displayConfig;
    CurrTiming = getTiming(VI_TVMODE(HorVer.tv == 3 ? 0 : HorVer.tv,
                                    HorVer.nonInter));
    CurrTvMode = HorVer.tv;
    HorVer.timing = CurrTiming;
    HorVer.DispSizeX = 0x280;
    acv = &CurrTiming->acv;
    HorVer.DispSizeY = *acv * 2;
    HorVer.DispPosX = (0x2D0 - HorVer.DispSizeX) / 2;
    HorVer.DispPosY = 0;
    AdjustPosition(CurrTiming->acv);
    HorVer.FBSizeX = 0x280;
    HorVer.FBSizeY = (*acv & 0x7FFF) << 1;
    HorVer.PanPosX = 0;
    HorVer.PanPosY = 0;
    HorVer.PanSizeX = 0x280;
    HorVer.PanSizeY = (*acv & 0x7FFF) << 1;
    HorVer.FBMode = VI_XFBMODE_SF;
    HorVer.wordPerLine = 0x28;
    HorVer.std = 0x28;
    HorVer.wpl = 0x28;
    HorVer.xof = 0;
    HorVer.black = TRUE;
    HorVer.threeD = FALSE;
    OSInitThreadQueue(&retraceQueue);
    value = __VIRegs[24] & ~0x8000;
    __VIRegs[24] = value;
    value = __VIRegs[26] & ~0x8000;
    __VIRegs[26] = value;
    PreCB = 0;
    PostCB = 0;
    __OSSetInterruptHandler(0x18, __VIRetraceHandler);
    __OSUnmaskInterrupts(0x80);
    OSRegisterShutdownFunction(&shutdownFunction);
    enabled = OSDisableInterrupts();
    value = CurrTvMode;
    switch (CurrTvMode) {
    case 0:
    case 3:
    case 6:
    case 7:
    case 8:
        value = 0;
        break;
    case 1:
    case 4:
        value = 1;
        break;
    }
    OSRestoreInterrupts(enabled);
    if (value == 1) {
        THD_TIME_TO_DIMMING = 30000;
        NEW_TIME_TO_DIMMING = 30000;
        THD_TIME_TO_DVD_STOP = 90000;
    } else {
        THD_TIME_TO_DIMMING = 18000;
        NEW_TIME_TO_DIMMING = 18000;
        THD_TIME_TO_DVD_STOP = 108000;
    }
    _gIdleCount_dimming = 0;
    _gIdleCount_dvd = 0;
    g_current_time_to_dim = 0;
    __VIDimming_All_Clear = 1;
    __VIDimmingState = 0;
    __VIDimmingFlag_Enable = TRUE;
    if (SCGetScreenSaverMode() == 0) {
        __VIDimmingFlag_Enable = FALSE;
    }
    __VIDVDStopFlag_Enable = 0;
    __VISetRevolutionModeSimple();
}

void VIWaitForRetrace(void)
{
    BOOL enabled;
    u32 count;

    enabled = OSDisableInterrupts();
    count = retraceCount;
    for (;;) {
        OSSleepThread(&retraceQueue);
        if (count != retraceCount) {
            break;
        }
    }
    OSRestoreInterrupts(enabled);
}

static void calcFbbs(u32 bufferAddress, u16 panPosX, u16 panPosY,
                     u8 wordPerLine, VIXFBMode fbMode, u16 displayPosY,
                     u32* topBuffer, u32* bottomBuffer)
{
    u32 bytesPerLine;
    u32 xOffsetInWords;
    u32 temp;

    xOffsetInWords = (panPosX & ~0xF) >> 4;
    bytesPerLine = (wordPerLine & 0xFF) << 5;
    *topBuffer = bufferAddress + (xOffsetInWords << 5) + (bytesPerLine * panPosY);
    *bottomBuffer = fbMode == VI_XFBMODE_SF ? *topBuffer : *topBuffer + bytesPerLine;
    if (displayPosY % 2 == 1) {
        temp = *topBuffer;
        *topBuffer = *bottomBuffer;
        *bottomBuffer = temp;
    }
    *topBuffer &= 0x3FFFFFFF;
    *bottomBuffer &= 0x3FFFFFFF;
}

static void setFbbRegs(VIHorVer* mode, u32* topBuffer, u32* bottomBuffer,
                       u32* rightTopBuffer, u32* rightBottomBuffer)
{
    u32 shifted;

    calcFbbs(mode->bufAddr, mode->PanPosX, mode->AdjustedPanPosY,
             mode->wordPerLine, mode->FBMode, mode->AdjustedDispPosY,
             topBuffer, bottomBuffer);
    if (mode->threeD) {
        calcFbbs(mode->rbufAddr, mode->PanPosX, mode->AdjustedPanPosY,
                 mode->wordPerLine, mode->FBMode, mode->AdjustedDispPosY,
                 rightTopBuffer, rightBottomBuffer);
    }
    if (*topBuffer < 0x01000000 && *bottomBuffer < 0x01000000 &&
        *rightTopBuffer < 0x01000000 && *rightBottomBuffer < 0x01000000) {
        shifted = 0;
    } else {
        shifted = 1;
    }
    if (shifted) {
        *topBuffer >>= 5;
        *bottomBuffer >>= 5;
        *rightTopBuffer >>= 5;
        *rightBottomBuffer >>= 5;
    }
    regs[15] = (u16)*topBuffer & 0xFFFF;
    MARK_CHANGED(15);
    regs[14] = (shifted << 12) | ((*topBuffer >> 16) | (mode->xof << 8));
    MARK_CHANGED(14);
    regs[19] = (u16)*bottomBuffer & 0xFFFF;
    MARK_CHANGED(19);
    regs[18] = *bottomBuffer >> 16;
    MARK_CHANGED(18);
    if (mode->threeD) {
        regs[17] = (u16)*rightTopBuffer & 0xFFFF;
        MARK_CHANGED(17);
        regs[16] = *rightTopBuffer >> 16;
        MARK_CHANGED(16);
        regs[21] = (u16)*rightBottomBuffer & 0xFFFF;
        MARK_CHANGED(21);
        regs[20] = *rightBottomBuffer >> 16;
        MARK_CHANGED(20);
    }
}

#pragma dont_inline on
static void setHorizontalRegs(VITiming* currentTiming, u16 displayPosX,
                              u16 displaySizeX)
{
    u32 hbe;
    u32 hbs;
    u32 hbeLow;
    u32 hbeHigh;

    regs[3] = currentTiming->hlw;
    MARK_CHANGED(3);
    regs[2] = currentTiming->hce | (currentTiming->hcs << 8);
    MARK_CHANGED(2);
    if (HorVer.tv == 8) {
        hbe = currentTiming->hbe640 + 0xAC;
        hbs = currentTiming->hbs640;
    } else {
        hbe = currentTiming->hbe640 - 40 + displayPosX;
        hbs = currentTiming->hbs640 + 40 + displayPosX -
              (720 - displaySizeX);
    }
    hbeLow = hbe & 0x1FF;
    hbeHigh = hbe >> 9;
    regs[5] = currentTiming->hsy | (hbeLow << 7);
    MARK_CHANGED(5);
    regs[4] = hbeHigh | (hbs * 2);
    MARK_CHANGED(4);
}

#pragma dont_inline reset

#pragma dont_inline on
static void setVerticalRegs(s32 displayPosY, s32 displaySizeY, u8 equ,
                            u16 acv, u16 prbOdd, u16 prbEven, u16 psbOdd,
                            u16 psbEven, int black)
{
    u16 actualPrbOdd;
    u16 actualPrbEven;
    u16 actualPsbOdd;
    u16 actualPsbEven;
    u16 actualAcv;
    s32 d;
    s32 c;

    if (HorVer.nonInter == 2 || HorVer.nonInter == 3) {
        c = 1;
        d = 2;
    } else {
        c = 2;
        d = 1;
    }
    if ((displayPosY % 2) == 0) {
        actualPrbOdd = prbOdd + (d * displayPosY);
        actualPsbOdd = psbOdd + (d * (((c * acv) - displaySizeY) - displayPosY));
        actualPrbEven = prbEven + (d * displayPosY);
        actualPsbEven = psbEven + (d * (((c * acv) - displaySizeY) - displayPosY));
    } else {
        actualPrbOdd = prbEven + (d * displayPosY);
        actualPsbOdd = psbEven + (d * (((c * acv) - displaySizeY) - displayPosY));
        actualPrbEven = prbOdd + (d * displayPosY);
        actualPsbEven = psbOdd + (d * (((c * acv) - displaySizeY) - displayPosY));
    }
    actualAcv = displaySizeY / c;
    if (black) {
        actualPrbOdd += actualAcv * 2 - 2;
        actualPsbOdd += 2;
        actualPrbEven += actualAcv * 2 - 2;
        actualPsbEven += 2;
        actualAcv = 0;
    }
    MARK_CHANGED(0);
    regs[7] = actualPrbOdd;
    MARK_CHANGED(7);
    regs[0] = equ | (actualAcv << 4);
    regs[6] = (u16)(u32)actualPsbOdd;
    MARK_CHANGED(6);
    regs[9] = (u16)(u32)actualPrbEven;
    MARK_CHANGED(9);
    regs[8] = (u16)(u32)actualPsbEven;
    MARK_CHANGED(8);
}

#pragma dont_inline reset

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define CLAMP(value, low, high) ((value) > (high) ? (high) : ((value) < (low) ? (low) : (value)))

static void AdjustPosition(u16 acv)
{
    s32 coeff;
    s32 frac;

    HorVer.AdjustedDispPosX = CLAMP((s16)HorVer.DispPosX + displayOffsetH, 0,
                                    0x2D0 - HorVer.DispSizeX);
    coeff = HorVer.FBMode == VI_XFBMODE_SF ? 2 : 1;
    frac = HorVer.DispPosY & 1;
    HorVer.AdjustedDispPosY = MAX((s16)HorVer.DispPosY + displayOffsetV, frac);
    HorVer.AdjustedDispSizeY =
        HorVer.DispSizeY +
        MIN((s16)HorVer.DispPosY + displayOffsetV - frac, 0) -
        MAX((s16)HorVer.DispPosY + (s16)HorVer.DispSizeY + displayOffsetV -
                (((s16)acv * 2) - frac),
            0);
    HorVer.AdjustedPanPosY =
        HorVer.PanPosY -
        (MIN((s16)HorVer.DispPosY + displayOffsetV - frac, 0) / coeff);
    HorVer.AdjustedPanSizeY =
        HorVer.PanSizeY +
        (MIN((s16)HorVer.DispPosY + displayOffsetV - frac, 0) / coeff) -
        (MAX((s16)HorVer.DispPosY + (s16)HorVer.DispSizeY + displayOffsetV -
                 (((s16)acv * 2) - frac),
             0) /
         coeff);
}

static void setInterruptRegs(VITiming* currentTiming)
{
    u16 hct;
    u16 vct;
    u16 borrow;

    vct = currentTiming->nhlines / 2;
    borrow = currentTiming->nhlines % 2;
    if (borrow != 0) {
        hct = currentTiming->hlw;
    } else {
        hct = 0;
    }
    vct++;
    hct++;
    regs[25] = hct;
    MARK_CHANGED(25);
    regs[24] = vct | 0x1000;
    MARK_CHANGED(24);
}

static void setPicConfig(u16 fbSizeX, VIXFBMode fbMode, u16 panPosX,
                         u16 panSizeX, u8* wordPerLine, u8* standard,
                         u8* wordsPerLine, u8* xOffset)
{
    *wordPerLine = (fbSizeX + 15) / 16;
    *standard = fbMode == VI_XFBMODE_SF ? *wordPerLine : (u8)(*wordPerLine * 2);
    *xOffset = panPosX % 16;
    *wordsPerLine = (*xOffset + panSizeX + 15) / 16;
    regs[0x24] = *standard | (*wordsPerLine << 8);
    changed |= 0x8000000;
}

static void setBBIntervalRegs(VITiming* currentTiming)
{
    u16 value;

    value = currentTiming->bs1 | (currentTiming->be1 << 5);
    regs[11] = value;
    changed |= 0x10000000000000;
    value = currentTiming->bs3 | (currentTiming->be3 << 5);
    regs[10] = value;
    changed |= 0x20000000000000;
    value = currentTiming->bs2 | (currentTiming->be2 << 5);
    regs[13] = value;
    changed |= 0x4000000000000;
    value = currentTiming->bs4 | (currentTiming->be4 << 5);
    regs[12] = value;
    changed |= (1LL << (63 - 12));
}

static void setScalingRegs(u16 panSizeX, u16 displaySizeX, BOOL threeD)
{
    u32 scale;

    panSizeX = threeD ? (panSizeX << 1) : panSizeX;
    if (panSizeX < displaySizeX) {
        scale = ((u32)displaySizeX + ((u32)panSizeX << 8) - 1) /
                (u32)displaySizeX;
        regs[37] = scale | 0x1000;
        changed |= 0x04000000;
        regs[56] = panSizeX;
        changed |= 0x80;
    } else {
        regs[37] = 0x100;
        changed |= 0x04000000;
    }
}

static s32 cntlzd(u64 bits)
{
    u32 high;
    u32 low;
    s32 count;

    high = bits >> 32;
    low = bits & 0xFFFFFFFF;
    count = __cntlzw(high);
    if (count < 32) {
        return count;
    }
    return __cntlzw(low) + 32;
}

void VIConfigure(const GXRenderModeObj* renderMode)
{
    VITiming* currentTiming;
    u32 register1;
    u32 register54;
    BOOL enabled;
    u32 nonInter;
    u32 tvInBootrom;
    u32 tvInGame;
    static u32 warnedDebugPal;

    enabled = OSDisableInterrupts();
    nonInter = renderMode->viTVmode & 3;
    if (HorVer.nonInter != nonInter) {
        changeMode = 1;
        HorVer.nonInter = nonInter;
    }
    tvInBootrom = *(u32*)OSPhysicalToCached(0xCC);
    tvInGame = (u32)renderMode->viTVmode >> 2;
    if (tvInGame == VI_DEBUG_PAL && warnedDebugPal == 0) {
        warnedDebugPal = 1;
        OSReport("***************************************\n");
        OSReport(" ! ! ! C A U T I O N ! ! !             \n");
        OSReport("This TV format \"DEBUG_PAL\" is only for \n");
        OSReport("temporary solution until PAL DAC board \n");
        OSReport("is available. Please do NOT use this   \n");
        OSReport("mode in real games!!!                  \n");
        OSReport("***************************************\n");
    }
    if (((tvInBootrom != 1 && tvInBootrom != 5) &&
         (tvInGame == 1 || tvInGame == 5)) ||
        ((tvInBootrom == 1 || tvInBootrom == 5) &&
         tvInGame != 1 && tvInGame != 5)) {
        OSPanic("vi.c", 0xA57,
                "VIConfigure(): Tried to change mode from (%d) to (%d), which is forbidden\n",
                tvInBootrom, tvInGame);
    }
    if (tvInGame == VI_NTSC || tvInGame == VI_MPAL) {
        HorVer.tv = tvInBootrom;
    } else {
        HorVer.tv = tvInGame;
    }
    HorVer.DispPosX = renderMode->viXOrigin;
    HorVer.DispPosY = HorVer.nonInter == 1 ? renderMode->viYOrigin * 2
                                            : renderMode->viYOrigin;
    HorVer.DispSizeX = renderMode->viWidth;
    HorVer.FBSizeX = renderMode->fbWidth;
    HorVer.FBSizeY = renderMode->xfbHeight;
    HorVer.FBMode = renderMode->xFBmode;
    HorVer.PanSizeX = HorVer.FBSizeX;
    HorVer.PanSizeY = HorVer.FBSizeY;
    HorVer.PanPosX = 0;
    HorVer.PanPosY = 0;
    if (HorVer.nonInter == 2 || HorVer.nonInter == 3) {
        HorVer.DispSizeY = HorVer.PanSizeY;
    } else if (HorVer.FBMode == VI_XFBMODE_SF) {
        HorVer.DispSizeY = HorVer.PanSizeY * 2;
    } else {
        HorVer.DispSizeY = HorVer.PanSizeY;
    }
    HorVer.threeD = HorVer.nonInter == 3 ? 1 : 0;
    currentTiming = getTiming(VI_TVMODE(HorVer.tv, HorVer.nonInter));
    HorVer.timing = currentTiming;
    AdjustPosition(currentTiming->acv);
    if (encoderType == 0) {
        HorVer.tv = 3;
    }
    setInterruptRegs(currentTiming);
    register1 = regs[1];
    if (HorVer.nonInter == VI_MPAL || HorVer.nonInter == VI_DEBUG) {
        register1 = (register1 & ~(1 << 2)) | (1 << 2);
    } else {
        register1 = (register1 & ~(1 << 2)) | ((HorVer.nonInter & 1) << 2);
    }
    register1 = (register1 & ~(1 << 3)) | (HorVer.threeD << 3);
    if (HorVer.tv == VI_DEBUG_PAL || HorVer.tv == VI_EURGB60) {
        register1 &= ~(3 << 8);
    } else {
        register1 = (register1 & ~(3 << 8)) | (HorVer.tv << 8);
    }
    regs[1] = register1;
    MARK_CHANGED(1);
    register54 = regs[54];
    if (HorVer.nonInter == 2 || HorVer.nonInter == 3) {
        register54 |= 1;
    } else {
        register54 &= ~1;
    }
    regs[54] = register54;
    MARK_CHANGED(54);
    setScalingRegs(HorVer.PanSizeX, HorVer.DispSizeX, HorVer.threeD);
    setHorizontalRegs(currentTiming, HorVer.AdjustedDispPosX, HorVer.DispSizeX);
    setBBIntervalRegs(currentTiming);
    setPicConfig(HorVer.FBSizeX, HorVer.FBMode, HorVer.PanPosX,
                 HorVer.PanSizeX, &HorVer.wordPerLine, &HorVer.std,
                 &HorVer.wpl, &HorVer.xof);
    if (FBSet != 0) {
        setFbbRegs(&HorVer, &HorVer.tfbb, &HorVer.bfbb, &HorVer.rtfbb,
                   &HorVer.rbfbb);
    }
    setVerticalRegs(HorVer.AdjustedDispPosY, HorVer.AdjustedDispSizeY,
                    currentTiming->equ, currentTiming->acv,
                    currentTiming->prbOdd, currentTiming->prbEven,
                    currentTiming->psbOdd, currentTiming->psbEven,
                    HorVer.black);
    OSRestoreInterrupts(enabled);
}

void VIConfigurePan(u16 xOrigin, u16 yOrigin, u16 width, u16 height)
{
    BOOL enabled;
    VITiming* currentTiming;

    enabled = OSDisableInterrupts();
    HorVer.PanPosX = xOrigin;
    HorVer.PanPosY = yOrigin;
    HorVer.PanSizeX = width;
    HorVer.PanSizeY = height;
    if (HorVer.nonInter != 2 && HorVer.nonInter != 3 &&
        HorVer.FBMode == VI_XFBMODE_SF) {
        height *= 2;
    }
    HorVer.DispSizeY = height;
    currentTiming = HorVer.timing;
    AdjustPosition(currentTiming->acv);
    setScalingRegs(HorVer.PanSizeX, HorVer.DispSizeX, HorVer.threeD);
    setPicConfig(HorVer.FBSizeX, HorVer.FBMode, HorVer.PanPosX,
                 HorVer.PanSizeX, &HorVer.wordPerLine, &HorVer.std,
                 &HorVer.wpl, &HorVer.xof);
    if (FBSet != 0) {
        setFbbRegs(&HorVer, &HorVer.tfbb, &HorVer.bfbb, &HorVer.rtfbb,
                   &HorVer.rbfbb);
    }
    setVerticalRegs(HorVer.AdjustedDispPosY, HorVer.DispSizeY,
                    currentTiming->equ, currentTiming->acv,
                    currentTiming->prbOdd, currentTiming->prbEven,
                    currentTiming->psbOdd, currentTiming->psbEven,
                    HorVer.black);
    OSRestoreInterrupts(enabled);
}

void VIFlush(void)
{
    BOOL enabled;
    s32 registerIndex;

    enabled = OSDisableInterrupts();
    shdwChangeMode = shdwChangeMode | changeMode;
    changeMode = 0;
    shdwChanged = shdwChanged | changed;
    while (changed != 0) {
        registerIndex = cntlzd(changed);
        shdwRegs[registerIndex] = regs[registerIndex];
        changed &= ~__shl2i((u64)1, 63 - registerIndex);
    }
    flushFlag = 1;
    flushFlag3in1 = 1;
    NextBufAddr = HorVer.bufAddr;
    OSRestoreInterrupts(enabled);
}

void VISetNextFrameBuffer(void* frameBuffer)
{
    BOOL enabled;

    enabled = OSDisableInterrupts();
    HorVer.bufAddr = (u32)frameBuffer;
    FBSet = 1;
    setFbbRegs(&HorVer, &HorVer.tfbb, &HorVer.bfbb, &HorVer.rtfbb,
               &HorVer.rbfbb);
    OSRestoreInterrupts(enabled);
}

void* VIGetCurrentFrameBuffer(void)
{
    return CurrBufAddr;
}

void VISetBlack(BOOL black)
{
    BOOL enabled;
    VITiming* currentTiming;

    enabled = OSDisableInterrupts();
    HorVer.black = black;
    currentTiming = HorVer.timing;
    setVerticalRegs(HorVer.AdjustedDispPosY, HorVer.DispSizeY,
                    currentTiming->equ, currentTiming->acv,
                    currentTiming->prbOdd, currentTiming->prbEven,
                    currentTiming->psbOdd, currentTiming->psbEven,
                    HorVer.black);
    OSRestoreInterrupts(enabled);
}

u32 VIGetRetraceCount(void)
{
    return retraceCount;
}

static u32 getCurrentHalfLine(void)
{
    u32 horizontalCount;
    u32 previousVerticalCount;
    u32 verticalCount;

    verticalCount = __VIRegs[22] & 0x7FF;
    for (;;) {
        previousVerticalCount = verticalCount;
        horizontalCount = __VIRegs[23] & 0x7FF;
        verticalCount = __VIRegs[22] & 0x7FF;
        if (previousVerticalCount == verticalCount) {
            break;
        }
    }
    return ((verticalCount - 1) * 2) + ((horizontalCount - 1) / CurrTiming->hlw);
}

u32 VIGetCurrentLine(void)
{
    u32 halfLine;
    u32 previousVerticalCount;
    u32 horizontalCount;
    u32 verticalCount;
    VITiming* currentTiming;
    BOOL enabled;

    currentTiming = CurrTiming;
    enabled = OSDisableInterrupts();
    verticalCount = __VIRegs[22] & 0x7FF;
    do {
        previousVerticalCount = verticalCount;
        horizontalCount = __VIRegs[23] & 0x7FF;
        verticalCount = __VIRegs[22] & 0x7FF;
    } while (previousVerticalCount != verticalCount);
    halfLine = ((verticalCount - 1) * 2) +
               ((horizontalCount - 1) / CurrTiming->hlw);
    OSRestoreInterrupts(enabled);
    if (halfLine >= currentTiming->nhlines) {
        halfLine -= currentTiming->nhlines;
    }
    return halfLine >> 1;
}

u32 VIGetTvFormat(void)
{
    BOOL enabled;
    u32 format;

    enabled = OSDisableInterrupts();
    format = CurrTvMode;
    switch (CurrTvMode) {
    case 0:
    case 3:
    case 6:
    case 7:
    case 8:
        format = 0;
        break;
    case 1:
    case 4:
        format = 1;
        break;
    case 2:
    case 5:
        break;
    }
    OSRestoreInterrupts(enabled);
    return format;
}

u32 VIGetScanMode(void)
{
    BOOL enabled;
    u32 field;
    u32 scanMode;

    enabled = OSDisableInterrupts();
    if ((u32)(__VIRegs[54] & 1) == 1U) {
        scanMode = 2;
    } else {
        field = (__VIRegs[1] >> 2) & 1;
        scanMode = ((0U - field) | field) >> 31;
    }
    OSRestoreInterrupts(enabled);
    return scanMode;
}

u32 VIGetDTVStatus(void)
{
    BOOL enabled;
    u32 status;

    enabled = OSDisableInterrupts();
    status = __VIRegs[55] & 3;
    OSRestoreInterrupts(enabled);
    return status & 1;
}

void __VISetAdjustingValues(s16 horizontalOffset, s16 verticalOffset)
{
    BOOL enabled;
    VITiming* currentTiming;

    enabled = OSDisableInterrupts();
    displayOffsetH = horizontalOffset;
    displayOffsetV = verticalOffset;
    currentTiming = HorVer.timing;
    AdjustPosition(currentTiming->acv);
    setHorizontalRegs(currentTiming, HorVer.AdjustedDispPosX, HorVer.DispSizeX);
    if (FBSet != 0) {
        setFbbRegs(&HorVer, &HorVer.tfbb, &HorVer.bfbb, &HorVer.rtfbb,
                   &HorVer.rbfbb);
    }
    setVerticalRegs(HorVer.AdjustedDispPosY, HorVer.AdjustedDispSizeY,
                    currentTiming->equ, currentTiming->acv,
                    currentTiming->prbOdd, currentTiming->prbEven,
                    currentTiming->psbOdd, currentTiming->psbEven,
                    HorVer.black);
    OSRestoreInterrupts(enabled);
}

void __VIDisplayPositionToXY(u32 horizontalCount, u32 verticalCount,
                             s16* pixelX, s16* pixelY)
{
    VITiming* currentTiming;
    u32 halfLine;
    u32 fieldLine;
    u32 fieldStart;
    u32 fieldEnd;

    currentTiming = CurrTiming;
    halfLine = ((verticalCount - 1) * 2) +
               ((horizontalCount - 1) / currentTiming->hlw);
    if (HorVer.nonInter == 0) {
        if (halfLine < currentTiming->nhlines) {
            fieldStart = ((u32)currentTiming->equ << 2) - currentTiming->equ;
            fieldEnd = currentTiming->nhlines - currentTiming->psbOdd;
            if (halfLine < fieldStart + currentTiming->prbOdd) {
                *pixelY = -1;
            } else if (halfLine >= fieldEnd) {
                *pixelY = -1;
            } else {
                *pixelY = (halfLine - fieldStart - currentTiming->prbOdd) & ~1U;
            }
        } else {
            fieldLine = halfLine - currentTiming->nhlines;
            fieldStart = ((u32)currentTiming->equ << 2) - currentTiming->equ;
            fieldEnd = currentTiming->nhlines - currentTiming->psbEven;
            if (fieldLine < fieldStart + currentTiming->prbEven) {
                *pixelY = -1;
            } else if (fieldLine >= fieldEnd) {
                *pixelY = -1;
            } else {
                *pixelY = ((fieldLine - fieldStart - currentTiming->prbEven) & ~1U) + 1;
            }
        }
    } else if (HorVer.nonInter == 1) {
        if (halfLine >= currentTiming->nhlines) {
            halfLine -= currentTiming->nhlines;
        }
        fieldStart = ((u32)currentTiming->equ << 2) - currentTiming->equ;
        fieldEnd = currentTiming->nhlines - currentTiming->psbOdd;
        if (halfLine < fieldStart + currentTiming->prbOdd) {
            *pixelY = -1;
        } else if (halfLine >= fieldEnd) {
            *pixelY = -1;
        } else {
            *pixelY = (halfLine - fieldStart - currentTiming->prbOdd) & ~1U;
        }
    } else if (HorVer.nonInter == 2) {
        if (halfLine < currentTiming->nhlines) {
            fieldStart = ((u32)currentTiming->equ << 2) - currentTiming->equ;
            fieldEnd = currentTiming->nhlines - currentTiming->psbOdd;
            if (halfLine < fieldStart + currentTiming->prbOdd) {
                *pixelY = -1;
            } else if (halfLine >= fieldEnd) {
                *pixelY = -1;
            } else {
                *pixelY = halfLine - fieldStart - currentTiming->prbOdd;
            }
        } else {
            fieldLine = halfLine - currentTiming->nhlines;
            fieldStart = ((u32)currentTiming->equ << 2) - currentTiming->equ;
            fieldEnd = currentTiming->nhlines - currentTiming->psbEven;
            if (fieldLine < fieldStart + currentTiming->prbEven) {
                *pixelY = -1;
            } else if (fieldLine >= fieldEnd) {
                *pixelY = -1;
            } else {
                *pixelY = (fieldLine - fieldStart - currentTiming->prbEven) & ~1U;
            }
        }
    }
    *pixelX = horizontalCount - 1;
}

BOOL VIEnableDimming(BOOL enable)
{
    u32 oldEnable;

    oldEnable = __VIDimmingFlag_Enable;
    if (enable == TRUE && SCGetScreenSaverMode() == 0) {
        enable = FALSE;
    }
    __VIDimmingFlag_Enable = enable;
    return oldEnable;
}

s32 VISetTimeToDimming(s32 time)
{
    BOOL enabled;
    s32 format;
    u32 oldTime;

    oldTime = g_current_time_to_dim;
    g_current_time_to_dim = time;
    enabled = OSDisableInterrupts();
    format = CurrTvMode;
    switch (CurrTvMode) {
    case 0:
    case 3:
    case 6:
    case 7:
    case 8:
        format = 0;
        break;
    case 1:
    case 4:
        format = 1;
        break;
    case 2:
    case 5:
        break;
    }
    OSRestoreInterrupts(enabled);
    switch (format) {
    case 1:
        switch (g_current_time_to_dim) {
        case 1:
            NEW_TIME_TO_DIMMING = 30000;
            break;
        case 2:
            NEW_TIME_TO_DIMMING = 45000;
            break;
        default:
            NEW_TIME_TO_DIMMING = 15000;
            break;
        }
        break;
    default:
        switch (g_current_time_to_dim) {
        case 1:
            NEW_TIME_TO_DIMMING = 36000;
            break;
        case 2:
            NEW_TIME_TO_DIMMING = 54000;
            break;
        default:
            NEW_TIME_TO_DIMMING = 18000;
            break;
        }
        break;
    }
    return oldTime;
}

BOOL VIResetDimmingCount(void)
{
    __VIDimmingFlag_DEV_IDLE[0] = 0;
    return TRUE;
}

BOOL __VIResetRFIdle(void)
{
    __VIDimmingFlag_RF_IDLE = 0;
    return TRUE;
}

BOOL __VIResetSIIdle(void)
{
    __VIDimmingFlag_SI_IDLE = 0;
    return TRUE;
}

void WaitMicroTime(s32 microseconds)
{
    OSTime elapsedMicroseconds;
    OSTime clockDivisor;
    OSTime startTime;

    startTime = __OSGetSystemTime();
    do {
        elapsedMicroseconds = (__OSGetSystemTime() - startTime) * 8;
        clockDivisor = __mulhwu(0x431BDE83, *(u32*)0x800000F8 >> 2) >> 15;
        elapsedMicroseconds /= clockDivisor;
    } while (elapsedMicroseconds < microseconds);
}
