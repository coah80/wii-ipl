/* opus-ph best C. Not exact; the retail asm stays in the source. */

/* libs/RevoEX/src/nwc24/NWC24UserId.c getUnScrambleId: 161/161 insns, odiff 68 differing (prior best 97). */

#define GET_BYTE(id, n) ((u8)((id) >> ((n) * 8)))
#define SET_BYTE(id, n, b) (((id) & ~((u64)0xFF << ((n) * 8))) | ((u64)(b) << ((n) * 8)))
#define UNSCRAMBLE(b) ((u8)((TtableInv[(b) >> 4] << 4) | TtableInv[(b) & 0xF]))

static NWC24UserId getUnScrambleId(NWC24UserId id) {
    u64 mixId;
    u64 copy;
    u8 b;

    mixId = id;
    mixId &= 0x001FFFFFFFFFFFFFULL;
    mixId ^= 0x00005E5E5E5E5E5EULL;
    mixId &= 0x001FFFFFFFFFFFFFULL;
    mixId |= (mixId & 1) << 53;
    mixId >>= 1;

    copy = mixId;
    b = GET_BYTE(copy, 1);
    mixId = SET_BYTE(mixId, 0, b);
    b = GET_BYTE(copy, 5);
    mixId = SET_BYTE(mixId, 1, b);
    b = GET_BYTE(copy, 0);
    mixId = SET_BYTE(mixId, 2, b);
    b = GET_BYTE(copy, 4);
    mixId = SET_BYTE(mixId, 3, b);
    b = GET_BYTE(copy, 2);
    mixId = SET_BYTE(mixId, 4, b);
    b = GET_BYTE(copy, 3);
    mixId = SET_BYTE(mixId, 5, b);

    b = GET_BYTE(mixId, 0);
    mixId = SET_BYTE(mixId, 0, UNSCRAMBLE(b));
    b = GET_BYTE(mixId, 1);
    mixId = SET_BYTE(mixId, 1, UNSCRAMBLE(b));
    b = GET_BYTE(mixId, 2);
    mixId = SET_BYTE(mixId, 2, UNSCRAMBLE(b));
    b = GET_BYTE(mixId, 3);
    mixId = SET_BYTE(mixId, 3, UNSCRAMBLE(b));
    b = GET_BYTE(mixId, 4);
    mixId = SET_BYTE(mixId, 4, UNSCRAMBLE(b));
    b = GET_BYTE(mixId, 5);
    mixId = SET_BYTE(mixId, 5, UNSCRAMBLE(b));

    mixId = ((mixId & 0x7FFFFFFFFFFULL) << 10) | ((mixId >> 43) & 0x3FF);
    mixId ^= 0x0000B3B3B3B3B3B3ULL;
    return mixId;
}

/* libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main.c TMCJPEGDEC_err_restart: 115/115 insns, odiff 21 differing (prior 114/115). */

static inline s32 finishRestart(TMCCJPEGDecWork* work, TMCCJPEGDecState* state, u8 marker) {
    u8 restartDistance;
    s32 result;
    s32 next;
    u8 skipped;
    s32 quotient;
    s32 remainder;
    u16 y;
    u16 x;
    u16 pitch;
    u16 interval;
    u32 position;
    restartDistance = marker + 8 - (work->rstMarkerIdx + 0xCF);
    if (marker > work->rstMarkerIdx + 0xCF) {
        restartDistance = marker - (work->rstMarkerIdx + 0xCF);
    }
    pitch = state->maxX;
    interval = work->restartInterval;
    skipped = restartDistance * interval;
    work->rstMarkerIdx = (marker + 1) & 7;
    position = work->mcuPos;
    next = (u8)position * pitch + (skipped + (position >> 16));
    quotient = next / pitch;
    remainder = next - quotient * pitch;
    y = quotient;
    work->mcuPos = ((u32)remainder << 16) + y;
    x = remainder;
    work->components.dcPredict[0] = 0;
    work->components.dcPredict[1] = 0;
    work->components.dcPredict[2] = 0;
    work->components.dcPredict[3] = 0;
    work->restartCnt = 0;
    result = TMCJPEGDEC_init_buff(work);
    if (result < 0) {
        return result;
    }
    state->posX = x;
    state->posY = y;
    state->position = TMCJPEGDEC_get_position(work);
    return state->result - state->posY * state->maxX - state->posX;
}

s32 TMCJPEGDEC_err_restart(TMCCJPEGDecWork* work) {
    u8 byte;
    TMCCJPEGDecState* state;
    s32 result;
    u8 marker;

    state = work->pState;
    if (work->scanCount == 1) {
        state->decodeResult = 0;
        return 0;
    }
    result = TMCJPEGDEC_rewind_ptr(work);
    if (result < 0) {
        return result;
    }
    byte = *work->pBufCur;
    for (;;) {
        while (byte != 0xFF) {
            result = TMCJPEGDEC_get_byte(&byte, work);
            if (result < 0) {
                return result;
            }
        }
        result = TMCJPEGDEC_get_byte(&byte, work);
        marker = byte;
        if (marker == 0xD9) {
            if (result < 0 && result != TMCC_ERROR_UNDERFLOW) {
                return result;
            }
            return 0;
        }
        if (result < 0) {
            return result;
        }
        switch (marker) {
        case 0xD0:
        case 0xD1:
        case 0xD2:
        case 0xD3:
        case 0xD4:
        case 0xD5:
        case 0xD6:
        case 0xD7:
            return finishRestart(work, state, marker);
        }
    }
}
