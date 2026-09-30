#include <private/axfx.h>
#include <revolution/axfx.h>

#include <revolution/ax.h>

#include <revolution/os.h>

#include <math.h>
#include <string.h>

static BOOL __AllocDelay(AXFX_CHORUS_EXP* chorus);
static BOOL __InitDelay(AXFX_CHORUS_EXP* chorus);
static void __FreeDelay(AXFX_CHORUS_EXP* chorus);

static BOOL __InitParams(AXFX_CHORUS_EXP* chorus);
static void __CalcLFO(s32* lfoBuf, AXFX_CHORUS_EXP_LFO* lfo);

u32 AXFXChorusExpGetMemSize(AXFX_CHORUS_EXP* chorus) {
    return 0x3200 * AXFX_STEREO_CHANNEL_MAX;
}

BOOL AXFXChorusExpInit(AXFX_CHORUS_EXP* chorus) {
    BOOL result;
    BOOL enabled;

    enabled = OSDisableInterrupts();

    chorus->active |= 1;

    result = __AllocDelay(chorus);
    if (result == FALSE) {
        AXFXChorusExpShutdown(chorus);
        OSRestoreInterrupts(enabled);
        return FALSE;
    }

    result = __InitDelay(chorus);
    if (result == FALSE) {
        AXFXChorusExpShutdown(chorus);
        OSRestoreInterrupts(enabled);
        return FALSE;
    }

    result = __InitParams(chorus);
    if (result == FALSE) {
        AXFXChorusExpShutdown(chorus);
        OSRestoreInterrupts(enabled);
        return FALSE;
    }

    chorus->active &= ~1;

    OSRestoreInterrupts(enabled);

    return TRUE;
}

BOOL AXFXChorusExpSettings(AXFX_CHORUS_EXP* chorus) {
    BOOL result;
    BOOL enabled = OSDisableInterrupts();

    chorus->active |= 1;

    AXFXChorusExpShutdown(chorus);
    result = AXFXChorusExpInit(chorus);
    if (!result) {
        AXFXChorusExpShutdown(chorus);
        OSRestoreInterrupts(enabled);
        return FALSE;
    }

    chorus->active |= 2;
    chorus->active &= ~1;

    OSRestoreInterrupts(enabled);

    return result;
}

void AXFXChorusExpShutdown(AXFX_CHORUS_EXP* reverb) {
    BOOL enabled = OSDisableInterrupts();

    reverb->active |= 1;

    __FreeDelay(reverb);

    OSRestoreInterrupts(enabled);
}

void AXFXChorusExpCallback(AXFX_BUS* bus, AXFX_CHORUS_EXP* chorus) {
    u32 ch;
    u32 samp;
    s32* input[3];
    s32* inBusData[3];
    s32* outBusData[3];
    s32 lfoOut[96];
    s32 pos;
    s32 diff;
    u32 steps;
    u32 frac;
    u32 walk;
    u32 histIdx;
    u32 i;
    f32* coef;
    f32 data;
    f32 fir;
    AXFX_CHORUS_EXP* fx;

    fx = chorus;

    if (fx->active != 0) {
        fx->active &= ~2;
        return;
    }

    input[0] = bus->left;
    input[1] = bus->right;
    input[2] = bus->surround;

    if (fx->busIn != NULL) {
        inBusData[0] = fx->busIn->left;
        inBusData[1] = fx->busIn->right;
        inBusData[2] = fx->busIn->surround;
    }

    if (fx->busOut != NULL) {
        outBusData[0] = fx->busOut->left;
        outBusData[1] = fx->busOut->right;
        outBusData[2] = fx->busOut->surround;
    }

    __CalcLFO(lfoOut, &fx->lfo);

    for (samp = 0; samp < 96; samp++) {
        pos = fx->delay.outPos + lfoOut[samp];
        if (pos >= (s32)fx->delay.sizeFP) {
            pos -= fx->delay.sizeFP;
        } else if (pos < 0) {
            pos += fx->delay.sizeFP;
        }

        diff = pos - fx->delay.lastPos;
        if (diff < 0) {
            diff += fx->delay.sizeFP;
        }

        steps = (u32)(diff >> 16) & 0xFFFF;
        frac = diff & 0xFFFF;
        walk = fx->delay.lastPos >> 16;
        histIdx = fx->histIndex;

        while (steps--) {
            fx->history[0][histIdx] = fx->delay.line[0][walk];
            fx->history[1][histIdx] = fx->delay.line[1][walk];
            fx->history[2][histIdx++] = fx->delay.line[2][walk++];
            histIdx &= 3;
            if (walk >= fx->delay.size) {
                walk = 0;
            }
        }

        fx->delay.lastPos = pos & 0xFFFF0000;
        coef = __AXFXGetSrcCoef((frac >> 9) & 0x7F);

        for (ch = 0; ch < 3; ch++) {
            fir = 0.0f;
            fir += coef[0] * fx->history[ch][histIdx++];
            histIdx &= 3;
            fir += coef[1] * fx->history[ch][histIdx++];
            histIdx &= 3;
            fir += coef[2] * fx->history[ch][histIdx++];
            histIdx &= 3;
            fir += coef[3] * fx->history[ch][histIdx++];
            histIdx &= 3;

            if (fx->busIn != NULL) {
                data = (f32)(*(input[ch]) + *(inBusData[ch]++));
            } else {
                data = (f32)(*input[ch]);
            }

            fx->delay.line[ch][fx->delay.inPos] = data + fir * fx->feedback;

            *(input[ch]++) = (s32)(fir * fx->outGain);

            if (fx->busOut != NULL) {
                *(outBusData[ch]++) = (s32)(fir * fx->sendGain);
            }
        }

        fx->histIndex = histIdx;

        if (++fx->delay.inPos >= fx->delay.size) {
            fx->delay.inPos = 0;
        }

        fx->delay.outPos += 0x10000;
        if (fx->delay.outPos >= fx->delay.sizeFP) {
            fx->delay.outPos = 0;
        }
    }
}

static BOOL __AllocDelay(AXFX_CHORUS_EXP* chorus) {
    AXFX_CHORUS_EXP* pChorus = chorus;
    u32 i;

    pChorus->delay.size = 0xC80;
    for (i = 0; i < AXFX_STEREO_CHANNEL_MAX; i++) {
        pChorus->delay.line[i] = __AXFXAlloc(pChorus->delay.size * 4);
        ASSERTMSGLINE(443, pChorus->delay.line[i], "Can't allocate the memory.");
        if (!pChorus->delay.line[i]) {
            return FALSE;
        }
    }
    return TRUE;
}

static BOOL __InitDelay(AXFX_CHORUS_EXP* chorus) {
    AXFX_CHORUS_EXP* pChorus = chorus;
    u32 i;

    for (i = 0; i < AXFX_STEREO_CHANNEL_MAX; i++) {
        ASSERTMSGLINE(469, pChorus->delay.line[i], "Buffer is not allocated.");
        if (!pChorus->delay.line[i]) {
            return FALSE;
        }
        memset(pChorus->delay.line[i], 0, pChorus->delay.size * 4);
    }

    pChorus->delay.inPos = 0;
    pChorus->delay.outPos = pChorus->delay.size - (u32)(32.0f * chorus->delayTime);
    pChorus->delay.outPos <<= 0x10;
    pChorus->delay.lastPos = pChorus->delay.outPos;
    pChorus->delay.sizeFP = pChorus->delay.size << 0x10;

    return TRUE;
}

static void __FreeDelay(AXFX_CHORUS_EXP* chorus) {
    u32 i;
    AXFX_CHORUS_EXP* pChorus;

    pChorus = chorus;

    for (i = 0; i < AXFX_STEREO_CHANNEL_MAX; i++) {
        if (pChorus->delay.line[i]) {
            __AXFXFree(pChorus->delay.line[i]);
        }
        pChorus->delay.line[i] = NULL;
    }
}

static BOOL __InitParams(AXFX_CHORUS_EXP* chorus) {
    u32 i, j;

    f32 var_f28;
    f32 var_f30;
    f32 var_f29;
    f32 var_f31;

    ASSERTMSGLINE(767, chorus->delayTime >= 0.1f && chorus->delayTime <= 50.0f, "The value of specified parameter is out of range.");
    if (chorus->delayTime < 0.1f || chorus->delayTime > 50.0f) {
        return FALSE;
    }

    ASSERTMSGLINE(767, chorus->depth >= 0.0f && chorus->depth <= 1.0f, "The value of specified parameter is out of range.");
    if (chorus->depth < 0.0f || chorus->depth > 1.0f) {
        return FALSE;
    }

    ASSERTMSGLINE(767, chorus->rate >= 0.1f && chorus->rate <= 2.0f, "The value of specified parameter is out of range.");
    if (chorus->rate < 0.1f || chorus->rate > 2.0f) {
        return FALSE;
    }

    ASSERTMSGLINE(767, chorus->feedback >= 0.0f && chorus->feedback < 1.0f, "The value of specified parameter is out of range.");
    if (chorus->feedback < 0.0f || chorus->feedback >= 1.0f) {
        return FALSE;
    }

    ASSERTMSGLINE(767, chorus->outGain >= 0.0f && chorus->outGain <= 1.0f, "The value of specified parameter is out of range.");
    if (chorus->outGain < 0.0f || chorus->outGain > 1.0f) {
        return FALSE;
    }

    ASSERTMSGLINE(767, chorus->sendGain >= 0.0f && chorus->sendGain <= 1.0f, "The value of specified parameter is out of range.");
    if (chorus->sendGain < 0.0f || chorus->sendGain > 1.0f) {
        return FALSE;
    }

    chorus->lfo.table = __AXFXGetLfoSinTable();

    var_f30 = 32.0f * chorus->delayTime;
    var_f31 = var_f30 * chorus->depth;

    if (var_f31 >= var_f30) {
        var_f31 -= 1.0f;
        if (var_f31 < 0.0f) {
            var_f31 = 0.0f;
        }
    }

    chorus->lfo.depthSamp = (65536.0f * var_f31);
    chorus->lfo.phaseAdd = (65536.0f * ((256.0f * chorus->rate) / 32000.0f));
    var_f29 = (32000.0f / chorus->rate) * 0.00390625f;
    chorus->lfo.stepSamp = (65536.0f * var_f29);
    var_f28 = var_f31 / var_f29;
    chorus->lfo.gradFactor = (65536.0f * var_f28);
    chorus->lfo.phase = 0;
    chorus->lfo.sign = 0;
    chorus->lfo.lastNum = -1;
    chorus->lfo.lastValue = 0;
    chorus->lfo.grad = 0;

    for (i = 0; i < AXFX_STEREO_CHANNEL_MAX; i++) {
        for (j = 0; j < 4; j++) {
            chorus->history[i][j] = 0.0f;
        }
    }

    chorus->histIndex = 0;

    return TRUE;
}

static void __CalcLFO(s32* lfoBuf, AXFX_CHORUS_EXP_LFO* lfo) {
    u32 i;

    s32 srcCoefIndex;
    s32 var_r24;
    s32 var_r25;
    u32 histIndex;
    s64 var_r31;
    s64 var_r28;

    var_r31 = 0;

    for (i = 0; i < 96; i++) {
        histIndex = lfo->phase & 0xFFFF0000;
        if (histIndex != lfo->lastNum) {
            lfo->lastNum = histIndex;
            histIndex = histIndex >> 0x10U;
            var_r25 = histIndex + 1;
            var_r25 &= 0x7F;
            var_r24 = lfo->table[histIndex];
            srcCoefIndex = lfo->table[var_r25];
            var_r28 = srcCoefIndex - var_r24;
            var_r28 = var_r28 * lfo->gradFactor;
            var_r28 = var_r28 >> 0x18;
            lfo->grad = var_r28;
            var_r31 = (s64)var_r24 * (s64)lfo->depthSamp;
            var_r31 = var_r31 >> 0x18;
        } else {
            var_r31 = lfo->lastValue + lfo->grad;
        }
        lfo->lastValue = var_r31;
        if (lfo->sign >= 1) {
            var_r31 *= -1;
        }
        lfo->phase += lfo->phaseAdd;
        if ((lfo->phase & 0xFF800000) != 0) {
            lfo->phase &= 0x7FFFFF;
            lfo->sign ^= 1;
        }
        lfoBuf[i] = var_r31;
    }
}
