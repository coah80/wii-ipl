#include <private/axfx.h>
#include <revolution/axfx.h>
#include <revolution/os.h>
#include <string.h>

static BOOL __InitParams(AXFX_CHORUS_EXP* fx);
static void __CalcLFO(s32* output, AXFX_CHORUS_EXP_LFO* lfo);

static BOOL __AllocDelayLine(AXFX_CHORUS_EXP* fx) {
    u32 channel;
    for (channel = 0; channel < 3; channel++) {
        fx->delay.line[channel] = __AXFXAlloc(fx->delay.size * sizeof(f32));
        if (fx->delay.line[channel] == NULL) return FALSE;
    }
    return TRUE;
}
static BOOL __BzeroDelayLine(AXFX_CHORUS_EXP* fx) {
    u32 channel;
    for (channel = 0; channel < 3; channel++) {
        if (fx->delay.line[channel] == NULL) return FALSE;
        memset(fx->delay.line[channel], 0, fx->delay.size * sizeof(f32));
    }
    fx->delay.inPos = 0;
    fx->delay.outPos = (fx->delay.size - (u32)(32.0f * fx->delayTime)) << 16;
    fx->delay.lastPos = fx->delay.outPos;
    fx->delay.sizeFP = fx->delay.size << 16;
    return TRUE;
}
u32 AXFXChorusExpGetMemSize(const AXFX_CHORUS_EXP* fx) {
    return 0x9600;
}
BOOL AXFXChorusExpInit(AXFX_CHORUS_EXP* fx) {
    BOOL enabled = OSDisableInterrupts();
    fx->active |= 1;
    fx->delay.size = 3200;
    if (!__AllocDelayLine(fx)) {
        AXFXChorusExpShutdown(fx);
        OSRestoreInterrupts(enabled);
        return FALSE;
    }
    if (!__BzeroDelayLine(fx)) {
        AXFXChorusExpShutdown(fx);
        OSRestoreInterrupts(enabled);
        return FALSE;
    }
    if (!__InitParams(fx)) {
        AXFXChorusExpShutdown(fx);
        OSRestoreInterrupts(enabled);
        return FALSE;
    }
    fx->active &= ~1;
    OSRestoreInterrupts(enabled);
    return TRUE;
}
BOOL AXFXChorusExpSettings(AXFX_CHORUS_EXP* fx) {
    BOOL result;
    BOOL enabled = OSDisableInterrupts();
    fx->active |= 1;
    AXFXChorusExpShutdown(fx);
    result = AXFXChorusExpInit(fx);
    if (!result) {
        AXFXChorusExpShutdown(fx);
        OSRestoreInterrupts(enabled);
        return FALSE;
    }
    fx->active = (fx->active | 2) & ~1;
    OSRestoreInterrupts(enabled);
    return result;
}
static void __FreeDelayLine(AXFX_CHORUS_EXP* fx) {
    u32 channel;
    for (channel = 0; channel < 3; channel++) {
        if (fx->delay.line[channel] != NULL) __AXFXFree(fx->delay.line[channel]);
        fx->delay.line[channel] = NULL;
    }
}
void AXFXChorusExpShutdown(AXFX_CHORUS_EXP* fx) {
    BOOL enabled = OSDisableInterrupts();
    fx->active |= 1;
    __FreeDelayLine(fx);
    OSRestoreInterrupts(enabled);
}
void AXFXChorusExpCallback(AXFX_BUFFERUPDATE* update, AXFX_CHORUS_EXP* fx) {
    s32* output[3];
    s32* input[3];
    s32* send[3];
    s32 modulation[96];
    u32 sample;
    if (fx->active != 0) {
        fx->active &= ~2;
        return;
    }
    output[0] = update->left;
    output[1] = update->right;
    output[2] = update->surround;
    if (fx->busIn != NULL) {
        input[0] = fx->busIn->left;
        input[1] = fx->busIn->right;
        input[2] = fx->busIn->surround;
    }
    if (fx->busOut != NULL) {
        send[0] = fx->busOut->left;
        send[1] = fx->busOut->right;
        send[2] = fx->busOut->surround;
    }
    __CalcLFO(modulation, &fx->lfo);
    for (sample = 0; sample < 96; sample++) {
        s32 position = fx->delay.outPos + modulation[sample];
        u32 distance;
        u32 whole, fraction, source, history, channel;
        f32* coefficients;
        if (position >= (s32)fx->delay.sizeFP) position -= fx->delay.sizeFP;
        else if (position < 0) position += fx->delay.sizeFP;
        distance = position - fx->delay.lastPos;
        if ((s32)distance < 0) distance += fx->delay.sizeFP;
        whole = distance >> 16;
        fraction = distance & 0xFFFF;
        source = fx->delay.lastPos >> 16;
        history = fx->histIndex;
        while (whole != 0) {
            fx->history[0][history] = fx->delay.line[0][source];
            fx->history[1][history] = fx->delay.line[1][source];
            fx->history[2][history] = fx->delay.line[2][source];
            history++;
            history &= 3;
            source++;
            whole--;
            if (source >= fx->delay.size) source = 0;
        }
        fx->delay.lastPos = position & 0xFFFF0000;
        coefficients = __AXFXGetSrcCoef((fraction >> 9) & 0x7F);
        for (channel = 0; channel < 3; channel++) {
            f32 filtered = 0.0f;
            f32 dry;
            filtered += coefficients[0] * fx->history[channel][history];
            history++;
            history &= 3;
            filtered += coefficients[1] * fx->history[channel][history];
            history++;
            history &= 3;
            filtered += coefficients[2] * fx->history[channel][history];
            history++;
            history &= 3;
            filtered += coefficients[3] * fx->history[channel][history];
            history++;
            history &= 3;
            if (fx->busIn != NULL) dry = *output[channel] + *input[channel]++;
            else dry = *output[channel];
            fx->delay.line[channel][fx->delay.inPos] = dry + filtered * fx->feedback;
            *output[channel]++ = filtered * fx->outGain;
            if (fx->busOut != NULL) *send[channel]++ = filtered * fx->sendGain;
        }
        fx->histIndex = history;
        fx->delay.inPos++;
        if (fx->delay.inPos >= fx->delay.size) fx->delay.inPos = 0;
        fx->delay.outPos += 0x10000;
        if (fx->delay.outPos >= fx->delay.sizeFP) fx->delay.outPos = 0;
    }
}
static inline void chorus_gradient(AXFX_CHORUS_EXP_LFO* lfo, f32 depth, f32 step) {
    depth /= step;
    lfo->gradFactor = 65536.0f * depth;
}
static BOOL __InitParams(AXFX_CHORUS_EXP* fx) {
    f32 delay;
    f32 depth;
    f32 step;
    u32 channel;
    u32 sample;
    s32 stepSamp;
    s32 phaseAdd;
    s32 depthSamp;

    if (fx->delayTime < 0.1f || fx->delayTime > 50.0f) return FALSE;
    if (fx->depth < 0.0f || fx->depth > 1.0f) return FALSE;
    if (fx->rate < 0.1f || fx->rate > 2.0f) return FALSE;
    if (fx->feedback < 0.0f || fx->feedback >= 1.0f) return FALSE;
    if (fx->outGain < 0.0f || fx->outGain > 1.0f) return FALSE;
    if (fx->sendGain < 0.0f || fx->sendGain > 1.0f) return FALSE;
    fx->lfo.table = __AXFXGetLfoSinTable();
    delay = 32.0f * fx->delayTime;
    depth = delay * fx->depth;
    if (depth >= delay) {
        depth -= 1.0f;
        if (depth < 0.0f) depth = 0.0f;
    }
    fx->lfo.lastNum = -1;
    fx->lfo.phase = 0;
    fx->lfo.sign = 0;
    fx->lfo.lastValue = 0;
    fx->lfo.grad = 0;
    depthSamp = 65536.0f * depth;
    phaseAdd = 65536.0f * (256.0f * fx->rate / 32000.0f);
    step = (32000.0f / fx->rate) / 256.0f;
    stepSamp = 65536.0f * step;
    fx->lfo.depthSamp = depthSamp;
    fx->lfo.phaseAdd = phaseAdd;
    fx->lfo.stepSamp = stepSamp;
    chorus_gradient(&fx->lfo, depth, step);
    for (channel = 0; channel < 3; channel++) {
        for (sample = 0; sample < 4; sample++) {
            fx->history[channel][sample] = 0.0f;
        }
    }
    fx->histIndex = 0;
    return TRUE;
}
static void __CalcLFO(s32* output, AXFX_CHORUS_EXP_LFO* lfo) {
    s32 start;
    s64 value;
    s32 difference;
    s64 gradient;
    u32 phase;
    u32 sample;
    for (sample = 0; sample < 96; sample++) {
        phase = lfo->phase & 0xFFFF0000;
        if (phase != lfo->lastNum) {
            lfo->lastNum = phase;
            phase >>= 16;
            start = lfo->table[phase];
            difference = lfo->table[(phase + 1) & 0x7F] - start;
            gradient = difference;
            gradient *= lfo->gradFactor;
            lfo->grad = gradient >> 24;
            value = (s64)start * lfo->depthSamp;
            value >>= 24;
        } else {
            value = lfo->lastValue + lfo->grad;
        }
        lfo->lastValue = value;
        if (lfo->sign >= 1) value = -value;
        lfo->phase += lfo->phaseAdd;
        if (lfo->phase & 0xFF800000) {
            lfo->phase &= 0x7FFFFF;
            lfo->sign ^= 1;
        }
        *output++ = value;
    }
}
