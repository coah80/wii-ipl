#include <stddef.h>
#include <tmc_jpeg_internal.h>

s32 TMCJPEGDEC_init_buff_thumbnail(TMCCJPEGDecWork* work, u8* dst, u8* src) {
    TMCCJPEGDecWork* buffer = (TMCCJPEGDecWork*)dst;
    const TMCCJPEGDecInitParam* input = (const TMCCJPEGDecInitParam*)(src - offsetof(TMCCJPEGDecInitParam, pBuf2));
    s32 endAddress;
    u8* start;
    const TMCCJPEGDecExifData* exif = (const TMCCJPEGDecExifData*)work;

    if (input->buf2Size == 0) {
        return -1;
    }
    if (input->dataSize == 0) {
        return -1;
    }

    start = input->pBuf2;
    buffer->pBufOrg = start;
    buffer->bufLen = input->buf2Size;
    buffer->remaining = input->dataSize;
    buffer->pCallback = input->pCallback;
    buffer->pCbCtx = input->pContext;
    buffer->pBufStart = start;
    buffer->pBufCur = exif->thumbnailData + exif->thumbnailOffset;
    endAddress = exif->thumbnailLength;
    endAddress = (u32)buffer->pBufCur + endAddress;
    buffer->remaining = 0;
    buffer->pBufEnd = (u8*)endAddress;
    buffer->pBufMark = (u8*)endAddress - 0x22;
    return 0;
}

s32 TMCJPEGDEC_init_buff(TMCCJPEGDecWork* work) {
    work->bitBuf = 0;
    work->bitCount = 0;
    return TMCJPEGDEC_load_buff(work);
}

s32 TMCJPEGDEC_rewind_ptr(TMCCJPEGDecWork* work) {
    u32 bitBuf = work->bitBuf;
    s32 bitCount = work->bitCount;

    bitCount -= 8;
    for (; bitCount >= 0; bitCount -= 8) {
        s32 r = TMCJPEGDEC_move_ptr(-1, work);
        if (r < 0) {
            return r;
        }

        if ((u8)bitBuf == 0xFF) {
            r = TMCJPEGDEC_move_ptr(-1, work);
            if (r < 0) {
                return r;
            }
        }

        bitBuf >>= 8;
    }

    work->bitCount = 0;
    work->bitBuf = 0;
    return 0;
}
