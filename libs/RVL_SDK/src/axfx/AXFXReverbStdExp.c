#include <private/axfx.h>
#include <revolution/AXFX.h>
#include <revolution/MEM.h>
#include <revolution/OS.h>
#include <revolution/ax.h>

#include <math.h>
#include <string.h>

static BOOL __AllocDelayLine(AXFX_REVERBSTD_EXP* fx);
static void __BzeroDelayLines(AXFX_REVERBSTD_EXP* fx);
static void __FreeDelayLine(AXFX_REVERBSTD_EXP* fx);
static BOOL __InitParams(AXFX_REVERBSTD_EXP* fx);

static u32 __EarlySizeTable[8] = {163, 317, 479, 641, 797, 967, 1123, 1283};

static u32 __FilterSizeTable[7][4] = {{1789, 1999, 433, 149},   {149, 293, 251, 103},   {947, 1361, 433, 137},
                                      {1279, 1531, 509, 149}, {1531, 1847, 563, 179}, {1823, 2357, 571, 137},
                                      {1823, 2357, 571, 179}};

u32 AXFXReverbStdExpGetMemSize(AXFX_REVERBSTD_EXP* fx) {
    u32 sum = 0;
    u32 i = 0;

    sum += __EarlySizeTable[7];
    sum += (int)(fx->preDelayTimeMax * 32000);

    for (i = 0; i < 4; i++) {
        sum += __FilterSizeTable[6][i];
    }

    sum *= 3;
    sum *= 4;

    return sum;
}

BOOL AXFXReverbStdExpInit(AXFX_REVERBSTD_EXP* fx) {
    u32 ch, i;
    BOOL result = TRUE;
    BOOL mask = OSDisableInterrupts();

    fx->active = 1;

    if (fx->preDelayTimeMax < 0.0f) {
        AXFXReverbStdExpShutdown(fx);
        OSRestoreInterrupts(mask);
        return FALSE;
    }

    fx->earlyMaxLength = __EarlySizeTable[8 - 1];
    fx->preDelayMaxLength = (u32)(fx->preDelayTimeMax * 32000);

    for (i = 0; i < 2; i++) {
        fx->combMaxLength[i] = __FilterSizeTable[6][i];
    }

    for (i = 0; i < 2; i++) {
        fx->allpassMaxLength[i] = __FilterSizeTable[6][2 + i];
    }

    result = __AllocDelayLine(fx);
    if (result == FALSE) {
        AXFXReverbStdExpShutdown(fx);
        OSRestoreInterrupts(mask);
        return FALSE;
    }

    __BzeroDelayLines(fx);
    result = __InitParams(fx);
    if (result == FALSE) {
        AXFXReverbStdExpShutdown(fx);
        OSRestoreInterrupts(mask);
        return FALSE;
    }

    fx->active &= ~1;
    OSRestoreInterrupts(mask);
    return TRUE;
}

BOOL AXFXReverbStdExpSettings(AXFX_REVERBSTD_EXP* fx) {
    BOOL mask = OSDisableInterrupts();
    fx->active = fx->active | 1;
    AXFXReverbStdExpShutdown(fx);

    if (!AXFXReverbStdExpInit(fx)) {
        AXFXReverbStdExpShutdown(fx);
        OSRestoreInterrupts(mask);
        return FALSE;
    } else {
        fx->active |= 2;
        fx->active &= ~1;
        OSRestoreInterrupts(mask);
        return TRUE;
    }

}

void AXFXReverbStdExpShutdown(AXFX_REVERBSTD_EXP* fx) {
    BOOL mask = OSDisableInterrupts();
    fx->active |= 1;
    __FreeDelayLine(fx);
    OSRestoreInterrupts(mask);
}


void AXFXReverbStdExpCallback(AXFX_BUS* bus, AXFX_REVERBSTD_EXP* reverb) {
    u32 i, j;

    s32* busParam[AXFX_STEREO_CHANNEL_MAX];
    s32* busIn[AXFX_STEREO_CHANNEL_MAX];
    s32* busOut[AXFX_STEREO_CHANNEL_MAX];
    u32 earlyPos;
    u32 preDelayPos;
    u32 combPos0;
    u32 combPos1;
    u32 allpassPos0;
    u32 allpassPos1;
    f32 sp64;
    f32 sp60;
    f32* earlyLine;
    f32 sp58;
    f32 earlyCoef;
    f32* preDelayLine;
    f32 sp4C;
    f32* combLine0;
    f32* combLine1;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 combCoef0;
    f32 combCoef1;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 allpassCoef;
    f32 sp18;
    f32 sp14;
    f32 lpfCoef;
    f32 spC;
    f32 sp8;
    f32* allpassLine;

    if (reverb->active != 0) {
        reverb->active &= ~2;
        return;
    }
    busParam[AX_STEREO_L] = bus->left;
    busParam[AX_STEREO_R] = bus->right;
    busParam[AX_STEREO_S] = bus->surround;
    if (reverb->busIn) {
        busIn[AX_STEREO_L] = reverb->busIn->left;
        busIn[AX_STEREO_R] = reverb->busIn->right;
        busIn[AX_STEREO_S] = reverb->busIn->surround;
    }
    if (reverb->busOut) {
        busOut[AX_STEREO_L] = reverb->busOut->left;
        busOut[AX_STEREO_R] = reverb->busOut->right;
        busOut[AX_STEREO_S] = reverb->busOut->surround;
    }
    sp14 = 1.0f - reverb->lpfCoef;
    lpfCoef = reverb->lpfCoef;
    earlyCoef = reverb->earlyCoef;
    combCoef0 = reverb->combCoef[0];
    combCoef1 = reverb->combCoef[1];
    allpassCoef = reverb->allpassCoef;
    spC = 0.6f * reverb->earlyGain;
    sp8 = 0.6f * reverb->fusedGain;

    for (i = 0; i < 96; i++) {
        earlyPos = reverb->earlyPos;
        preDelayPos = reverb->preDelayPos;
        combPos0 = reverb->combPos[0];
        combPos1 = reverb->combPos[1];
        allpassPos0 = reverb->allpassPos[0];
        allpassPos1 = reverb->allpassPos[1];

        for (j = 0; j < AXFX_STEREO_CHANNEL_MAX; j++) {
            if (reverb->busIn) {
                sp64 = *busParam[j] + *busIn[j]++;
            } else {
                sp64 = *busParam[j];
            }
            earlyLine = reverb->earlyLine[j];
            sp58 = earlyLine[earlyPos];
            earlyLine[earlyPos] = sp64 + (sp58 * earlyCoef);
            if (reverb->preDelayLength != 0) {
                preDelayLine = reverb->preDelayLine[j];
                sp4C = preDelayLine[preDelayPos];
                preDelayLine[preDelayPos] = sp64;
            } else {
                sp4C = sp64;
            }
            combLine0 = reverb->combLine[j][0];
            sp40 = combLine0[combPos0];
            combLine0[combPos0] = sp4C + (sp40 * combCoef0);
            combLine1 = reverb->combLine[j][1];
            sp3C = combLine1[combPos1];
            combLine1[combPos1] = sp4C + (sp3C * combCoef1);
            sp38 = sp40 + sp3C;
            allpassLine = reverb->allpassLine[j][0];
            sp2C = allpassLine[allpassPos0];
            sp28 = sp38 + (sp2C * allpassCoef);
            allpassLine[allpassPos0] = sp28;
            sp24 = sp2C - (sp28 * allpassCoef);
            sp18 = (sp14 * sp24) + (lpfCoef * reverb->lastLpfOut[j]);
            reverb->lastLpfOut[j] = sp18;
            allpassLine = reverb->allpassLine[j][1];
            sp2C = allpassLine[allpassPos1];
            sp28 = sp18 + (sp2C * allpassCoef);
            allpassLine[allpassPos1] = sp28;
            sp20 = sp2C - (sp28 * allpassCoef);
            sp60 = (sp58 * spC) + (sp20 * sp8);
            *busParam[j]++ = (sp60 * reverb->outGain);
            if (reverb->busOut) {
                *busOut[j]++ = (sp60 * reverb->sendGain);
            }
        }
        if (++reverb->earlyPos >= reverb->earlyLength) {
            reverb->earlyPos = 0;
        }
        if (reverb->preDelayLength != 0) {
            if (++reverb->preDelayPos >= reverb->preDelayLength) {
                reverb->preDelayPos = 0;
            }
        }
        if (++reverb->combPos[0] >= reverb->combLength[0]) {
            reverb->combPos[0] = 0;
        }
        if (++reverb->combPos[1] >= reverb->combLength[1]) {
            reverb->combPos[1] = 0;
        }
        if (++reverb->allpassPos[0] >= reverb->allpassLength[0]) {
            reverb->allpassPos[0] = 0;
        }
        if (++reverb->allpassPos[1] >= reverb->allpassLength[1]) {
            reverb->allpassPos[1] = 0;
        }
    }
}

static BOOL __AllocDelayLine(AXFX_REVERBSTD_EXP* fx) {
    u32 ch, i;

    for (ch = 0; ch < 3; ch++) {
        fx->earlyLine[ch] = (f32*)__AXFXAlloc(sizeof(f32) * fx->earlyMaxLength);
        if (fx->earlyLine[ch] == NULL)
            return FALSE;

        if (fx->preDelayMaxLength) {
            fx->preDelayLine[ch] = (f32*)__AXFXAlloc(sizeof(f32) * fx->preDelayMaxLength);
            if (fx->preDelayLine[ch] == NULL)
                return FALSE;
        } else {
            fx->preDelayLine[ch] = NULL;
        }

        for (i = 0; i < 2; i++) {
            fx->combLine[ch][i] = (f32*)__AXFXAlloc(sizeof(f32) * fx->combMaxLength[i]);
            if (fx->combLine[ch][i] == NULL)
                return FALSE;
        }

        for (i = 0; i < 2; i++) {
            fx->allpassLine[ch][i] = (f32*)__AXFXAlloc(sizeof(f32) * fx->allpassMaxLength[i]);
            if (fx->allpassLine[ch][i] == NULL)
                return FALSE;
        }
    }

    return TRUE;
}

static void __BzeroDelayLines(AXFX_REVERBSTD_EXP* fx) {
    u32 ch, i;

    for (ch = 0; ch < 3; ch++) {
        if (fx->earlyLine[ch])
            memset(fx->earlyLine[ch], 0, sizeof(f32) * fx->earlyMaxLength);

        if (fx->preDelayLine[ch])
            memset(fx->preDelayLine[ch], 0, sizeof(f32) * fx->preDelayMaxLength);

        for (i = 0; i < 2; i++) {
            if (fx->combLine[ch][i])
                memset(fx->combLine[ch][i], 0, sizeof(f32) * fx->combMaxLength[i]);
        }

        for (i = 0; i < 2; i++) {
            if (fx->allpassLine[ch][i])
                memset(fx->allpassLine[ch][i], 0, sizeof(f32) * fx->allpassMaxLength[i]);
        }
    }
}

static void __FreeDelayLine(AXFX_REVERBSTD_EXP* fx) {
    u32 ch, i;

    for (ch = 0; ch < 3; ch++) {
        if (fx->earlyLine[ch]) {
            __AXFXFree(fx->earlyLine[ch]);
            fx->earlyLine[ch] = NULL;
        }

        if (fx->preDelayLine[ch]) {
            __AXFXFree(fx->preDelayLine[ch]);
            fx->preDelayLine[ch] = NULL;
        }

        for (i = 0; i < 2; i++) {
            if (fx->combLine[ch][i]) {
                __AXFXFree(fx->combLine[ch][i]);
                fx->combLine[ch][i] = NULL;
            }
        }

        for (i = 0; i < 2; i++) {
            if (fx->allpassLine[ch][i]) {
                __AXFXFree(fx->allpassLine[ch][i]);
                fx->allpassLine[ch][i] = NULL;
            }
        }
    }
}


static BOOL __InitParams(AXFX_REVERBSTD_EXP* fx) {
    u32 i;

    if (fx->earlyMode >= 8)
        return FALSE;

    if (fx->preDelayTime < 0.0f || fx->preDelayTime > fx->preDelayTimeMax)
        return FALSE;

    if (fx->fusedMode >= 6)
        return FALSE;

    if (fx->fusedTime < 0.0f)
        return FALSE;

    if (fx->coloration < 0.0f || fx->coloration > 1.0f)
        return FALSE;

    if (fx->damping < 0.0f || fx->damping > 1.0f)
        return FALSE;

    if (fx->earlyGain < 0.0f || fx->earlyGain > 1.0f)
        return FALSE;

    if (fx->fusedGain < 0.0f || fx->fusedGain > 1.0f)
        return FALSE;

    if (fx->outGain < 0.0f || fx->outGain > 1.0f)
        return FALSE;

    if (fx->sendGain < 0.0f || fx->sendGain > 1.0f)
        return FALSE;

    fx->earlyPos = 0;
    fx->earlyLength = __EarlySizeTable[fx->earlyMode];
    if (fx->earlyMode <= 3) {
        fx->earlyCoef = -0.33f;
    } else {
        fx->earlyCoef = 0.33f;
    }

    fx->preDelayPos = 0;
    fx->preDelayLength = (u32)(fx->preDelayTime * 32000);

    for (i = 0; i < 2; i++) {
        f32 t;
        fx->combPos[i] = 0;
        fx->combLength[i] = __FilterSizeTable[fx->fusedMode][i];
        t = -3.0f * (f32)(fx->combLength[i]) / (f32)(fx->fusedTime * 32000);
        fx->combCoef[i] = pow(10.0f, t);
    }

    fx->allpassPos[0] = 0;
    fx->allpassLength[0] = __FilterSizeTable[fx->fusedMode][2];
    fx->allpassPos[1] = 0;
    fx->allpassLength[1] = __FilterSizeTable[fx->fusedMode][3];

    fx->allpassCoef = fx->coloration;
    fx->lpfCoef = 1.0f - fx->damping;
    if (fx->lpfCoef > 0.95f) {
        fx->lpfCoef = 0.95f;
    }

    fx->lastLpfOut[0] = 0.0f;
    fx->lastLpfOut[1] = 0.0f;
    fx->lastLpfOut[2] = 0.0f;

    return TRUE;
}
