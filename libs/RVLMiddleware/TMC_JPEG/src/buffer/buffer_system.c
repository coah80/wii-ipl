#include <stddef.h>
#include <tmc_jpeg_internal.h>

static s32 refillJpegBufferAfterFF(TMCCJPEGDecWork* work);
static s32 refillJpegBuffer(TMCCJPEGDecWork* work);

s32 TMCJPEGDEC_init_ptr_buff(TMCCJPEGDecWork* work, void* param) {
    u32 readSize;
    u8* dest;
    u8* newEnd;
    u8* bufOrg;
    u32 newRemaining;
    const TMCCJPEGDecInitParam* input = (const TMCCJPEGDecInitParam*)((u8*)param - offsetof(TMCCJPEGDecInitParam, pBuf2));

    if ((u32)input->pBuf2 & (DEFAULT_ALIGN - 1))
        return -1;
    if (input->buf2Size & (DEFAULT_ALIGN - 1))
        return -1;
    if (input->dataSize == 0)
        return -1;
    if (input->buf2Size < 0x10040)
        return -1;

    work->pBufOrg = input->pBuf2;
    dest = work->pBufOrg + 0x20;
    work->bufLen = input->buf2Size - 0x20;
    readSize = input->dataSize;
    work->remaining = readSize;
    work->pCallback = input->pCallback;
    work->pCbCtx = input->pContext;
    if (work->bufLen - 0x20 < readSize) {
        readSize = work->bufLen - 0x20;
    }

    if (work->pCallback(work->pCbCtx, dest, readSize) < 0) {
        return TMCC_ERROR_USER_CALLBACK;
    }

    newEnd = dest + readSize;
    bufOrg = work->pBufOrg;
    newRemaining = work->remaining - readSize;

    work->pBufCur = dest;
    work->remaining = newRemaining;
    work->pBufStart = bufOrg;
    work->pBufEnd = newEnd;
    work->pBufMark = newEnd - 0x22;
    return 0;
}

s32 TMCJPEGDEC_get_byte(u8* dst, TMCCJPEGDecWork* work) {
    u8* cur;
    u8 byte;

    if (work->pBufCur >= work->pBufEnd) {
        if (work->remaining != 0) {
            s32 r = refillJpegBuffer(work);
            if (r < 0) {
                return r;
            }
        } else {
            return TMCC_ERROR_UNDERFLOW;
        }
    }

    cur = work->pBufCur;
    byte = *cur;
    cur++;
    *dst = byte;
    work->pBufCur = cur;

    if (cur >= work->pBufEnd) {
        if (work->remaining != 0) {
            s32 r = refillJpegBuffer(work);
            if (r < 0) {
                return r;
            }
        } else {
            return TMCC_ERROR_UNDERFLOW;
        }
    }

    return 0;
}

s32 TMCJPEGDEC_get_wbyte(u16* dst, TMCCJPEGDecWork* work) {
    u8 byte;
    u32 highByte;
    s32 result;

    u8* cur;
    u8* end;
    u8* next;

    // MWCC needs the empty else branches to preserve refill branch direction.
    do {
        if (work->pBufCur >= work->pBufEnd) {
            if (work->remaining != 0) {
                result = refillJpegBuffer(work);
                if (result < 0) {
                    break;
                } else {
                }
            } else {
                result = TMCC_ERROR_UNDERFLOW;
                break;
            }
        }

        {
            u8* bufferCursor = work->pBufCur;
            end = work->pBufEnd;
            cur = bufferCursor;
            next = bufferCursor + 1;
        }

        work->pBufCur = next;
        byte = *cur;
        if (next >= end) {
            if (work->remaining != 0) {
                result = refillJpegBuffer(work);
                if (result < 0) {
                    break;
                } else {
                }
            } else {
                result = TMCC_ERROR_UNDERFLOW;
                break;
            }
        }
        result = 0;
    } while (0);
    highByte = (u32)byte << 8;
    if (result < 0) {
        return result;
    }

    do {
        if (work->pBufCur >= work->pBufEnd) {
            if (work->remaining != 0) {
                result = refillJpegBuffer(work);
                if (result < 0) {
                    break;
                } else {
                }
            } else {
                result = TMCC_ERROR_UNDERFLOW;
                break;
            }
        }

        cur = work->pBufCur;
        end = work->pBufEnd;
        next = cur + 1;
        work->pBufCur = next;
        byte = *cur;
        if (next >= end) {
            if (work->remaining != 0) {
                result = refillJpegBuffer(work);
                if (result < 0) {
                    break;
                } else {
                }
            } else {
                result = TMCC_ERROR_UNDERFLOW;
                break;
            }
        }
        result = 0;
    } while (0);
    *dst = highByte + byte;
    return result < 0 ? result : 0;
}

s32 TMCJPEGDEC_get_sbyte(u8* dst, u32 count, TMCCJPEGDecWork* work) {
    int result = 0;
    u32 i;
    u8 byte;
    u8* cur;

    for (i = 0; i < count; i++) {
        // MWCC needs the empty else branches to preserve refill branch direction.
        do {
            if (work->pBufCur >= work->pBufEnd) {
                if (work->remaining != 0) {
                    result = refillJpegBuffer(work);
                    if (result < 0) {
                        break;
                    } else {
                    }
                } else {
                    result = TMCC_ERROR_UNDERFLOW;
                    break;
                }
            }

            cur = work->pBufCur;
            work->pBufCur += 1;
            byte = *cur;

            if (work->pBufCur >= work->pBufEnd) {
                if (work->remaining != 0) {
                    result = refillJpegBuffer(work);
                    if (result < 0) {
                        break;
                    } else {
                    }
                } else {
                    result = TMCC_ERROR_UNDERFLOW;
                    break;
                }
            }
            result = 0;
        } while (0);
        *dst = byte;
        dst++;

        if (result < 0)
            return result;
    }
    return 0;
}

s32 TMCJPEGDEC_move_ptr(s32 offset, TMCCJPEGDecWork* work) {
    s32 avail;
    s32 r;

    if (offset >= 0) {
        while (work->pBufEnd - work->pBufCur <= offset) {
            avail = work->pBufEnd - work->pBufCur;
            offset -= avail;
            if (work->remaining != 0) {
                r = refillJpegBuffer(work);
                if (r >= 0) {
                    continue;
                }
                return r;
            } else {
                return TMCC_ERROR_UNDERFLOW;
            }
        }
        work->pBufCur += offset;
        if (work->pBufEnd > work->pBufCur) {
            goto done;
        }
        if (work->remaining != 0) {
            r = refillJpegBuffer(work);
            if (r >= 0) {
                goto done;
            }
            return r;
        } else {
            return TMCC_ERROR_UNDERFLOW;
        }
    } else {
        offset = -offset;
        if (work->pBufCur - work->pBufStart < offset) {
            return TMCC_ERROR_UNDERFLOW;
        }
        work->pBufCur -= offset;
    }
done:
    return 0;
}

s32 TMCJPEGDEC_load_buff(TMCCJPEGDecWork* work) {
    u32 bitBuf;
    s32 bitCount;
    u8 byte;
    u8* cur = work->pBufCur;
    u8* end = work->pBufMark;
    s32 r;

    if (cur < end) {
        bitBuf = work->bitBuf;
        bitCount = work->bitCount;
        do {
            byte = *cur;
            cur++;
            bitBuf = (bitBuf << 8) + byte;
            bitCount += 8;
            if (byte == 0xFF) {
                cur++;
            }
        } while (bitCount <= 24);
        work->bitBuf = bitBuf;
        work->bitCount = bitCount;
        work->pBufCur = cur;
    } else {
        do {
            if (work->pBufEnd <= work->pBufCur) {
                if (work->remaining == 0) {
                    break;
                }
                r = refillJpegBufferAfterFF(work);
                if (r < 0) {
                    return r;
                }
            }

            {
                u32 bb = work->bitBuf;
                u8* c = work->pBufCur;
                u8* next;
                u8 byte = *c;

                next = c + 1;
                work->pBufCur = next;
                work->bitBuf = (bb << 8) + byte;
                work->bitCount += 8;
                if (byte == 0xFF) {
                    work->pBufCur = next + 1;
                }
            }

            if (work->pBufEnd <= work->pBufCur) {
                if (work->remaining == 0) {
                    break;
                }
                r = refillJpegBufferAfterFF(work);
                if (r < 0) {
                    return r;
                }
            }
        } while (work->bitCount <= 24);
    }

    return 0;
}

s32 TMCJPEGDEC_get_position(TMCCJPEGDecWork* work) {
    return work->pBufCur - work->pBufStart;
}

s32 TMCJPEGDEC_chk_possible_size(TMCCJPEGDecWork* work) {
    return work->pBufEnd - work->pBufCur;
}

static s32 refillJpegBufferAfterFF(TMCCJPEGDecWork* work) {
    u8 marker;
    u32 readSize;
    u8* dest;
    u8* beforeEnd;
    u32 i, j;

    {
        u8* tmpEndPtr = work->pBufEnd - 1;

        marker = 0;
        if (*tmpEndPtr == 0xFF) {
            marker = 1;
        }
        beforeEnd = tmpEndPtr;
    }

    for (i = 0; i < 32; i += 8) {
        for (j = 0; j < 8; j++) {
            work->pBufStart[i + j] = *(beforeEnd - (0x1f - (i + j)));
        }
    }

    dest = work->pBufOrg + 0x20;
    readSize = work->remaining;
    if (work->bufLen - 0x20 < readSize) {
        readSize = work->bufLen - 0x20;
    }

    if (work->pCallback(work->pCbCtx, dest, readSize) != 0) {
        return TMCC_ERROR_USER_CALLBACK;
    }

    {
        s32 oldRemaining = work->remaining;
        s32 newRemaining = oldRemaining - readSize;

        work->pBufEnd = dest + readSize;
        work->remaining = newRemaining;
        work->pBufCur = dest + marker;
        work->pBufMark = dest + readSize - 0x22;
    }

    return 0;
}

static s32 refillJpegBuffer(TMCCJPEGDecWork* work) {
    u8* end;
    u32 i, j;
    s32 readSize;
    u8* dest;

    end = work->pBufEnd;

    for (i = 0; i < 32; i += 8) {
        for (j = 0; j < 8; j++) {
            work->pBufStart[i + j] = *(end - 1 - (0x1f - (i + j)));
        }
    }

    dest = work->pBufOrg + 0x20;
    readSize = work->remaining;
    if (work->bufLen - 0x20 < readSize) {
        readSize = work->bufLen - 0x20;
    }

    if (work->pCallback(work->pCbCtx, dest, readSize) != 0) {
        return TMCC_ERROR_USER_CALLBACK;
    }

    {
        s32 oldRemaining = work->remaining;
        s32 newRemaining = oldRemaining - readSize;

        work->pBufCur = dest;
        work->remaining = newRemaining;
        work->pBufEnd = dest + readSize;
        work->pBufMark = dest + readSize - 0x22;
    }

    return 0;
}
