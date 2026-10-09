#define TMC_JPEG_FRAME_PARSER
#include <tmc_jpeg_internal.h>
#include <stddef.h>

extern void* memset(void* dest, s32 val, u32 count);

extern const u32 scJpegAanScale[64] = {
    0x00000100, 0x000000B9, 0x000000C4, 0x000000DA, 0x00000100, 0x00000146, 0x000001D9, 0x000003A0, 0x000000B9, 0x00000085, 0x0000008D,
    0x0000009D, 0x000000B9, 0x000000EB, 0x00000155, 0x0000029D, 0x000000C4, 0x0000008D, 0x00000096, 0x000000A7, 0x000000C4, 0x000000F9,
    0x0000016A, 0x000002C6, 0x000000DA, 0x0000009D, 0x000000A7, 0x000000B9, 0x000000DA, 0x00000115, 0x00000192, 0x00000315, 0x00000100,
    0x000000B9, 0x000000C4, 0x000000DA, 0x00000100, 0x00000146, 0x000001D9, 0x000003A0, 0x00000146, 0x000000EB, 0x000000F9, 0x00000115,
    0x00000146, 0x0000019F, 0x0000025A, 0x0000049D, 0x000001D9, 0x00000155, 0x0000016A, 0x00000192, 0x000001D9, 0x0000025A, 0x0000036A,
    0x000006B2, 0x000003A0, 0x0000029D, 0x000002C6, 0x00000315, 0x000003A0, 0x0000049D, 0x000006B2, 0x00000D23};

static s32 TMCJPEGDEC_parse_para(u16* marker, TMCCJPEGDecWork* work);
static s32 TMCJPEGDEC_parse_dht(s32 first, TMCCJPEGDecWork* work);
static s32 TMCJPEGDEC_parse_dqt(TMCCJPEGDecWork* work);
static s32 TMCJPEGDEC_parse_sof(TMCCJPEGDecWork* work);
static s32 TMCJPEGDEC_parse_sos(TMCCJPEGDecWork* work);

s32 TMCJPEGDEC_decompmcu(u32 maxMCU, u32 mcuCount, TMCCJPEGDecWork* work, void* buf) {
    TMCFrameComponents* compMapBase;
    u8* compMapPtr;
    u32* mcuDataInfo;

    u8** curBlockInfo;
    u8** specificConvRowPtr;

    u8* blockCountPtr;
    u8* entTblBase;

    s32 mcuIdx;
    s32 compIdx;
    s32 blockIdx;
    u16 pitch;

    u8* frameInfo;
    TMCJpegTableInfo* scaleInfo;

    u8** convRowPtrs;
    TMCCJPEGDecState* state;

    TMCIdctFunc* idctFunc;
    TMCIdctFunc* idctLumiFunc;
    TMCDecodeFunc* decodeFunc;

    state = work->pState;
    compMapBase = &work->components;
    frameInfo = (u8*)&work->frameWidth;
    compMapPtr = compMapBase->map;
    scaleInfo = &work->tables;
    convRowPtrs = work->pConvRowPtrs;
    mcuDataInfo = compMapBase->dcPredict;
    mcuIdx = 0;

    decodeFunc = work->decodePtr;
    idctFunc = work->idctPtr;
    idctLumiFunc = work->idctLumiPtr;

    pitch = work->pitch;

    while (mcuIdx < ((TMCJpegFrameInfo*)frameInfo)->scanCompCount) {
        compIdx = *compMapPtr;
        entTblBase = (u8*)scaleInfo->coefficients[compMapBase->quantTable[compIdx]];
        TMCJPEGDEC_set_entropytbl(scaleInfo, compMapBase->dcTable[compIdx], compMapBase->acTable[compIdx]);

        curBlockInfo = convRowPtrs;
        specificConvRowPtr = convRowPtrs + compIdx;
        blockCountPtr = frameInfo + mcuIdx;
        blockIdx = 0;

        while (blockIdx < *(blockCountPtr + offsetof(TMCJpegFrameInfo, blockCount))) {
            s32 stackBlock[64];
            s32 ret;

            ret = decodeFunc(stackBlock, entTblBase, mcuDataInfo, work);
            if (ret < 0)
                return ret;

            if (compIdx == 0) {
                idctFunc(stackBlock, *curBlockInfo, pitch, ret);
            } else {
                idctLumiFunc(stackBlock, specificConvRowPtr[4], pitch, ret);
            }

            curBlockInfo++;
            blockIdx++;
        }

        mcuDataInfo++;
        mcuIdx++;
        compMapPtr++;
    }

    if (maxMCU != state->dataSizeX && mcuCount != state->dataSizeY)
        work->pConverterFunc(work, maxMCU, mcuCount);
    else {
        work->pConverterFuncEdge(work, maxMCU, mcuCount);
    }

    if (((TMCJpegFrameInfo*)frameInfo)->restartInterval != 0) {
        s32 r = TMCJPEGDEC_restart_interval(work, maxMCU, mcuCount);
        if (r < 0) {
            return r;
        }
    }

    return 0;
}

static inline void initZigzag(TMCCJPEGDecWork* work) {
    const u8* zigzag = TMCJPEGDEC_Zigzag_data;
    s32 i;
    work->restartInterval = 0;
    work->scanCount = 0;
    for (i = 0; i < 64; i++) {
        work->tables.zigzagData[i] = *zigzag++ << 2;
    }

}

s32 TMCJPEGDEC_imagestart(TMCCJPEGDecWork* work) {
    u16 marker;
    s32 r;
    initZigzag(work);

    r = TMCJPEGDEC_get_wbyte(&marker, work);
    if (r < 0) {
        return r;
    }
    if (marker != TMC_JPEG_MARKER_SOI) {
        return -0x20;
    }
    marker = 0;
    r = TMCJPEGDEC_parse_para(&marker, work);
    if (r < 0) {
        return r;
    }
    if (marker != TMC_JPEG_MARKER_SOF0) {
        return -0x10;
    }
    r = TMCJPEGDEC_parse_sof(work);
    if (r < 0) {
        return r;
    }
    return 0;
}

s32 TMCJPEGDEC_imageend(TMCCJPEGDecWork* work) {
    if (work->pState->noEoiCheck == 1)
        return 0;

    if (work->scanCount == 0) {
        u16 marker;
        s32 r;

        r = TMCJPEGDEC_rewind_ptr(work);
        if (r < 0) {
            return r;
        }

        r = TMCJPEGDEC_get_wbyte(&marker, work);
        if (r < 0 && r != TMCC_ERROR_UNDERFLOW) {
            return r;
        }

        if (marker != TMC_JPEG_MARKER_EOI) {
            work->pState->decodeResult = -0x21;
            return 0;
        }
    }
    return 0;
}

s32 TMCJPEGDEC_scanstart(TMCCJPEGDecWork* work) {
    u16 marker;
    s32 r;

    marker = 0;
    r = TMCJPEGDEC_parse_para(&marker, work);
    if (r < 0) {
        return r;
    }

    if (marker != TMC_JPEG_MARKER_SOS) {
        return -0x22;
    }

    r = TMCJPEGDEC_parse_sos(work);
    if (r < 0) {
        return r;
    }

    if (work->frameHeight == 0) {
        return TMCC_ERROR_HEADER;
    }

    r = TMCJPEGDEC_scan_varinit(work);
    if (r < 0) {
        return r;
    }

    work->components.dcPredict[0] = 0;
    work->components.dcPredict[1] = 0;
    work->components.dcPredict[2] = 0;
    work->components.dcPredict[3] = 0;
    work->restartCnt = 0;
    r = TMCJPEGDEC_init_buff(work);
    if (r < 0) {
        return r;
    }

    work->rstMarkerIdx = 0;
    work->mcuPos = 0;
    return 0;
}

s32 TMCJPEGDEC_scan_varinit(TMCCJPEGDecWork* work) {
    s32 idx;
    TMCJpegFrameInfo* p;
    u16 remX;
    u16 remY;

    p = (TMCJpegFrameInfo*)&work->frameWidth;
    work->componentCount = work->componentCount | 0x100;

    if (work->scanCompCount == 1) {
        u8 hSamp;
        int hMul8;
        u8 qTblH;
        u8 component;

        hSamp = p->maxHSamp;
        component = work->components.map[0];
        qTblH = p->hSampFactor[component];
        hMul8 = hSamp * 8;
        p->mcuXCount = hMul8 / qTblH;
        p->mcuXRem = p->maxVSamp * 8 / p->vSampFactor[component];
        p->mcuYCount = p->frameWidth / p->mcuXCount;
        p->mcuXCount2 = p->frameHeight / p->mcuXRem;
    } else {
        u8 vSamp;
        u8 hSamp;

        hSamp = (p->maxHSamp & 0x1f) << 3;
        vSamp = (p->maxVSamp & 0x1f) << 3;
        p->mcuXCount = hSamp;
        p->mcuXRem = vSamp;
        p->mcuYCount = p->frameWidth / hSamp;
        p->mcuXCount2 = p->frameHeight / vSamp;
    }

    remX = p->frameWidth % p->mcuXCount;
    remY = p->frameHeight % p->mcuXRem;

    p->remX = remX;
    p->remY = remY;

    p->mcuYCount = p->mcuYCount + ((u8)remX != 0);
    p->mcuXCount2 = p->mcuXCount2 + ((u8)remY != 0);
    p->mcuTotal = (u32)p->mcuYCount * p->mcuXCount2;

    for (idx = 0; idx < p->scanCompCount; idx++) {
        u8 compId;
        u32 blocks;

        compId = work->components.map[idx];
        if (p->scanCompCount == 1) {
            blocks = 1;
        } else {
            blocks = p->hSampFactor[compId] * p->vSampFactor[compId];
        }
        p->blockCount[idx] = blocks;
    }

    for (; idx < 4; idx++) {
        p->blockCount[idx] = 0;
    }

    return 0;
}

static inline void restartMcuPosition(TMCCJPEGDecWork* work, TMCCJPEGDecState* state, u32 maxMCU, u32 mcuCount) {
    u16 blockCount;
    u16 column;
    u16 position;
    s32 row;
    s32 remainder;
    u8 stepY;
    u8 stepX;
    u16 pitch;

    stepY = state->stepY;
    stepX = state->stepX;
    pitch = state->maxX;
    blockCount = mcuCount / stepY;
    column = maxMCU / stepX;
    position = blockCount * pitch + column + 1;
    work->components.dcPredict[0] = 0;
    work->components.dcPredict[1] = 0;
    work->components.dcPredict[2] = 0;
    work->components.dcPredict[3] = 0;
    work->restartCnt = 0;
    row = position / pitch;
    remainder = position - row * pitch;
    work->mcuPos = ((u32)remainder << 16) + row;
}

s32 TMCJPEGDEC_restart_interval(TMCCJPEGDecWork* work, u32 maxMCU, u32 mcuCount) {
    u16 restartCount;
    TMCCJPEGDecState* state;
    s32 result = 0;

    restartCount = work->restartCnt;
    restartCount++;
    state = work->pState;
    work->restartCnt = restartCount;

    if (restartCount == work->restartInterval) {
        u16 marker;

        result = TMCJPEGDEC_rewind_ptr(work);
        if (result < 0) {
            return result;
        }
        result = TMCJPEGDEC_get_wbyte(&marker, work);
        if (marker == TMC_JPEG_MARKER_EOI) {
            work->scanCount = 1;
        }
        if (result < 0) {
            return result;
        }
        if (marker >= TMC_JPEG_MARKER_SOF0 && (marker < TMC_JPEG_MARKER_RST0 || marker > TMC_JPEG_MARKER_RST7)) {
            result = TMCJPEGDEC_move_ptr(-2, work);
            if (result < 0) {
                return result;
            }
        } else {
            s32 expected = work->rstMarkerIdx + TMC_JPEG_MARKER_RST0;
            if (marker != expected) {
                return -0x23;
            }
        }

        work->rstMarkerIdx = (work->rstMarkerIdx + 1) & 7;
        restartMcuPosition(work, state, maxMCU, mcuCount);
        result = TMCJPEGDEC_init_buff(work);
    }
    return result;
}


static inline s32 skipSegmentData(u16 length, TMCCJPEGDecWork* work) {
    s32 result = TMCJPEGDEC_move_ptr(length, work);
    if (result < 0) {
        return result;
    }
    return 0;
}

static inline s32 parseApplication(TMCCJPEGDecWork* work) {
    u16 length;
    s32 result = TMCJPEGDEC_get_wbyte(&length, work);
    if (result < 0) {
        return result;
    }
    if (length < 2) {
        return -0x45;
    }
    length -= 2;
    result = skipSegmentData(length, work);
    if (result < 0) {
        return result;
    }
    return 0;
}

static inline s32 parseRestartInterval(TMCCJPEGDecWork* work) {
    u16 length;
    s32 result = TMCJPEGDEC_get_wbyte(&length, work);
    if (result < 0) {
        return result;
    }
    if (length != 4) {
        return -0x42;
    }
    result = TMCJPEGDEC_get_wbyte(&length, work);
    if (result < 0) {
        return result;
    }
    work->restartInterval = length;
    return 0;
}

static inline s32 parseNumberOfLines(TMCCJPEGDecWork* work) {
    u16 length;
    s32 result = TMCJPEGDEC_get_wbyte(&length, work);
    if (result < 0) {
        return result;
    }
    if (length != 4) {
        return -0x43;
    }
    result = TMCJPEGDEC_get_wbyte(&length, work);
    if (result < 0) {
        return result;
    }
    work->frameHeight = length;
    return 0;
}

static inline s32 parseComment(TMCCJPEGDecWork* work) {
    u16 length;
    s32 result = TMCJPEGDEC_get_wbyte(&length, work);
    if (result < 0) {
        return result;
    }
    if (length < 2) {
        return -0x44;
    }
    length -= 2;
    result = skipSegmentData(length, work);
    if (result < 0) {
        return result;
    }
    return 0;
}

static s32 TMCJPEGDEC_parse_para(u16* marker, TMCCJPEGDecWork* work) {
    u8 byte;
    u16 local;
    s32 result;

    u32 keepGoing = 0;
    u16 firstMarker = *marker;

    do {
        result = TMCJPEGDEC_get_wbyte(&local, work);
        if (result < 0) {
            if (result == TMCC_ERROR_UNDERFLOW && local == TMC_JPEG_MARKER_EOI) {
                result = 0;
            } else {
                return result;
            }
        }

        while (local == TMC_JPEG_MARKER_FILL) {
            result = TMCJPEGDEC_get_byte(&byte, work);
            if (result < 0) {
                return result;
            }
            local = TMC_JPEG_MARKER_PREFIX | byte;
        }

        if (local >= TMC_JPEG_MARKER_APP0 && local <= TMC_JPEG_MARKER_APP15) {
            result = parseApplication(work);
        } else {
            switch (local) {
                case TMC_JPEG_MARKER_DHT: {
                    result = TMCJPEGDEC_parse_dht(firstMarker, work);
                    break;
                }
                case TMC_JPEG_MARKER_DQT: {
                    result = TMCJPEGDEC_parse_dqt(work);
                    break;
                }
                case TMC_JPEG_MARKER_DRI: {
                    result = parseRestartInterval(work);
                    break;
                }
                case TMC_JPEG_MARKER_DNL: {
                    result = parseNumberOfLines(work);
                    break;
                }
                case TMC_JPEG_MARKER_COM: {
                    result = parseComment(work);
                    break;
                }
                case TMC_JPEG_MARKER_SOF0: {
                    keepGoing = 1;
                    break;
                }
                case TMC_JPEG_MARKER_SOF2: {
                    keepGoing = 1;
                    break;
                }
                case TMC_JPEG_MARKER_SOS: {
                    keepGoing = 1;
                    break;
                }
                case TMC_JPEG_MARKER_EOI: {
                    work->scanCount = 1;
                    keepGoing = 1;
                    break;
                }
                default: {
                    result = -0x2F;
                    break;
                }
            }
        }

        if (result < 0) {
            keepGoing = 1;
        }
    } while (keepGoing == 0);

    *marker = local;
    return result;
}

static s32 TMCJPEGDEC_parse_dht(s32 first, TMCCJPEGDecWork* work) {
    TMCJpegTableInfo* scaleInfo;
    u16 len;
    u8 countBuf[17];
    u8 symBuf[256];
    s32 r;
    TMCHuffParam tblSet;

    scaleInfo = &work->tables;

    memset(countBuf, 0, sizeof(countBuf));

    r = TMCJPEGDEC_get_wbyte(&len, work);
    if (r < 0) {
        return r;
    }
    len -= 2;

    do {
        u8 htByte;
        u8* pCount;
        s32 tblClass;
        s32 tblID;
        s32 idx;
        s32 totalCodes;

        len -= 0x11;
        r = TMCJPEGDEC_get_byte(&htByte, work);
        if (r < 0) {
            return r;
        }

        tblID = (htByte & 0xF);
        tblClass = (htByte >> 4);

        if (tblClass >= 2 || tblID >= 2) {
            return -0x40;
        }

        pCount = &countBuf[1];
        idx = 1;

        countBuf[0] = 0;
        while (idx <= 16) {
            r = TMCJPEGDEC_get_byte(&htByte, work);
            if (r < 0) {
                return r;
            }
            len -= htByte;
            *pCount++ = htByte;
            idx++;
        }

        totalCodes = 0;
        for (idx = 1; idx <= 16; idx++) {
            totalCodes += countBuf[idx];
        }

        if (totalCodes > 0xB0) {
            return -0x40;
        }

        r = TMCJPEGDEC_get_sbyte(symBuf, (u8)totalCodes, work);
        if (r < 0) {
            return r;
        }

        tblSet.count = totalCodes;

        TMCJPEGDEC_set_HuffmanTable(&tblSet, tblClass, tblID, scaleInfo);
        r = TMCJPEGDEC_make_huffdec(countBuf, symBuf, &tblSet);
        if (r < 0) {
            return r;
        }
    } while (len != 0);

    return 0;
}

static s32 TMCJPEGDEC_parse_dqt(TMCCJPEGDecWork* work) {
    typedef struct {
        u32 data[64];
    } CopyBlock64;

    TMCJpegTableInfo* scaleInfo;
    u32 tblCopy[64];
    u32* d;
    u16 len;
    s32 r;

    d = tblCopy;
    *(CopyBlock64*)d = *(CopyBlock64*)scJpegAanScale;

    scaleInfo = &work->tables;

    r = TMCJPEGDEC_get_wbyte(&len, work);
    if (r < 0) {
        return r;
    }
    len -= 2;

    do {
        u8 qtInfo;
        const u8* zigPtr;
        s32 zzIdx;
        u8 byte;
        u32 val;
        s32 zz;

        len -= 0x41;
        r = TMCJPEGDEC_get_byte(&qtInfo, work);
        if (r < 0) {
            return r;
        }

        if (qtInfo > 4) {
            return -0x41;
        }

        scaleInfo->quantTblFlag[qtInfo] = 1;

        zigPtr = TMCJPEGDEC_Zigzag_data;
        for (zzIdx = 0; zzIdx < 64; zzIdx++) {

            zz = *zigPtr;
            if (zz > 0x3F) {
                return -0x41;
            }

            r = TMCJPEGDEC_get_byte(&byte, work);
            if (r < 0) {
                return r;
            }

            val = byte * tblCopy[zz];
            scaleInfo->coefficients[qtInfo][zz] = val;
            if (val == 0) {
                return -0x41;
            }

            zigPtr++;
        }
    } while (len != 0);

    return 0;
}

static inline void initFrameGeometry(TMCJpegFrameInfo* frameInfo, s32 maxHSamp, s32 maxVSamp) {
    u8 mcuWidth;
    u8 mcuHeight;
    u16 frameWidth;
    u16 frameHeight;
    s32 columnQuotient;
    s32 rowQuotient;
    u16 columns;
    u16 rows;
    mcuWidth = maxHSamp * 8;
    mcuHeight = maxVSamp * 8;
    frameWidth = frameInfo->frameWidth;
    frameHeight = frameInfo->frameHeight;
    columnQuotient = frameWidth / mcuWidth;
    rowQuotient = frameHeight / mcuHeight;
    columns = columnQuotient;
    rows = rowQuotient;
    frameInfo->mcuXCount = mcuWidth;
    frameInfo->mcuXRem = mcuHeight;
    frameInfo->remX = frameWidth - columnQuotient * mcuWidth;
    frameInfo->remY = frameHeight - rowQuotient * mcuHeight;
    frameInfo->mcuYCount = columns + (frameInfo->remX != 0);
    frameInfo->mcuXCount2 = rows + (frameInfo->remY != 0);
    frameInfo->mcuTotal = (u32)frameInfo->mcuYCount * frameInfo->mcuXCount2;
}

static inline s32 storeSampling(TMCJpegFrameInfo* frame, s32 index, u8 packed) {
    s32 horizontal = packed >> 4;
    frame->hSampFactor[index] = horizontal;
    frame->vSampFactor[index] = packed & 15;
    return horizontal;
}

static inline s32 validateFrameComponents(TMCCJPEGDecWork* work) {
    s32 idx;
    TMCJpegFrameInfo* frameInfo = (TMCJpegFrameInfo*)&work->frameWidth;
    TMCFrameComponents* components = &work->components;
    for (idx = 0; idx < frameInfo->compCount; idx++) {
        if (frameInfo->hSampFactor[idx] < 1 || frameInfo->hSampFactor[idx] > 4) {
            return TMCC_ERROR_HEADER;
        }
        if (frameInfo->vSampFactor[idx] < 1 || frameInfo->vSampFactor[idx] > 4) {
            return TMCC_ERROR_HEADER;
        }
        if (components->quantTable[idx] > 4) {
            return TMCC_ERROR_HEADER;
        }
    }
    return 0;
}

static s32 TMCJPEGDEC_parse_sof(TMCCJPEGDecWork* work) {
    s32 maxHSamp;
    s32 maxVSamp;
    TMCJpegFrameInfo* frameInfo = (TMCJpegFrameInfo*)&work->frameWidth;
    TMCFrameComponents* components = &work->components;
    u16 value;
    u8 byte;
    s32 r;
    s32 idx;

    r = TMCJPEGDEC_get_wbyte(&value, work);
    if (r < 0) {
        return r;
    }
    if (value < 2) {
        return TMCC_ERROR_HEADER;
    }
    r = TMCJPEGDEC_get_byte(&byte, work);
    if (r < 0) {
        return r;
    }
    if (byte != 8) {
        return TMCC_ERROR_HEADER;
    }
    r = TMCJPEGDEC_get_wbyte(&value, work);
    if (r < 0) {
        return r;
    }
    frameInfo->frameHeight = value;
    r = TMCJPEGDEC_get_wbyte(&value, work);
    if (r < 0) {
        return r;
    }
    frameInfo->frameWidth = value;
    r = TMCJPEGDEC_get_byte(&byte, work);
    if (r < 0) {
        return r;
    }
    frameInfo->compCount = byte;
    if ((s32)frameInfo->compCount <= 0 || (s32)frameInfo->compCount > 4) {
        return TMCC_ERROR_HEADER;
    }

    maxVSamp = 0;
    maxHSamp = 0;
    for (idx = 0; idx < frameInfo->compCount; idx++) {
        s32 hSamp;
        s32 vSamp;
        r = TMCJPEGDEC_get_byte(&byte, work);
        if (r < 0) {
            return r;
        }
        components->id[idx] = byte;
        r = TMCJPEGDEC_get_byte(&byte, work);
        if (r < 0) {
            return r;
        }
        hSamp = storeSampling(frameInfo, idx, byte);
        if (hSamp > maxHSamp) {
            maxHSamp = hSamp;
        }
        vSamp = frameInfo->vSampFactor[idx];
        if (vSamp > maxVSamp) {
            maxVSamp = vSamp;
        }
        r = TMCJPEGDEC_get_byte(&byte, work);
        if (r < 0) {
            return r;
        }
        components->quantTable[idx] = byte;
    }
    if ((u16)maxHSamp == 0 || (u16)maxVSamp == 0) {
        return TMCC_ERROR_HEADER;
    }
    frameInfo->maxHSamp = maxHSamp;
    frameInfo->maxVSamp = maxVSamp;
    frameInfo->componentCount = 6;
    {
        s32 sample;
        for (sample = 0; sample < 6; sample++) {
            s32 component;
            u32 factor;
            if (frameInfo->compCount == TMCJPEGDEC_SampleComps[sample]) {
                for (component = 0; component < frameInfo->compCount; component++) {
                    factor = frameInfo->hSampFactor[component];
                    if (factor != TMCJPEGDEC_SampleH_N[sample][component]) {
                        goto nextSample;
                    }
                    factor = frameInfo->vSampFactor[component];
                    if (factor != TMCJPEGDEC_SampleV_N[sample][component]) {
                        goto nextSample;
                    }
                }
                frameInfo->componentCount = sample;
            }
nextSample:
            continue;
        }
    }
    if (frameInfo->componentCount == 6) {
        return TMCC_ERROR_FORMAT;
    }
    initFrameGeometry(frameInfo, maxHSamp, maxVSamp);
    return validateFrameComponents(work);
}

static s32 TMCJPEGDEC_parse_sos(TMCCJPEGDecWork* work) {
    s32 idx;
    TMCFrameComponents* components;
    TMCJpegTableInfo* scalePtr;
    u8* mapPtr;

    s32 dcTbl;
    s32 acTbl;

    u16 len;
    s32 r;
    s32 moveResult;
    s32 ci;
    u8 scanByte;

    components = &work->components;
    scalePtr = &work->tables;

    r = TMCJPEGDEC_get_wbyte(&len, work);
    if (r < 0) {
        return r;
    }
    if (len < 2) {
        return -0x51;
    }

    r = TMCJPEGDEC_get_byte(&scanByte, work);
    if (r < 0) {
        return r;
    }

    work->scanCompCount = scanByte;

    if (work->scanCompCount > 4 || work->scanCompCount != work->compCount) {
        return -0x51;
    }

    for (idx = 0; idx < work->scanCompCount; idx++) {
        r = TMCJPEGDEC_get_byte(&scanByte, work);
        if (r < 0) {
            return r;
        }

        for (ci = 0; ci < work->compCount; ci++) {
            if ((s32)scanByte == (s32)components->id[ci]) {
                components->map[idx] = ci;
                mapPtr = &components->map[idx];
                goto componentFound;
            }
        }
        return -0x51;

componentFound:
        r = TMCJPEGDEC_get_byte(&scanByte, work);
        if (r < 0) {
            return r;
        }

        dcTbl = scanByte >> 4;
        acTbl = scanByte & 0xF;

        if (dcTbl > 1 || acTbl > 1) {
            return -0x51;
        }

        components->dcTable[*mapPtr] = dcTbl;
        components->acTable[*mapPtr] = acTbl;

        if (scalePtr->dcTblFlag[dcTbl] != 1) {
            return -0x40;
        }

        if (scalePtr->acTblFlag[acTbl] != 1) {
            return -0x40;
        }

        if (scalePtr->quantTblFlag[components->quantTable[idx]] != 1) {
            return -0x41;
        }
    }

    moveResult = TMCJPEGDEC_move_ptr(3, work);
    if (moveResult < 0) {
        return moveResult;
    }
    return 0;
}

static inline s32 restartFromMarker(TMCCJPEGDecWork* work, TMCCJPEGDecState* state, u8 marker) {
    u8 skip;
    u16 pitch;
    u32 pos;
    u16 row;
    u16 column;
    s32 mcuIndex;
    u16 y;
    u16 x;
    s32 result;

    if (marker > work->rstMarkerIdx + 0xCF) {
        skip = marker - (work->rstMarkerIdx + 0xCF);
    } else {
        skip = (marker + 8) - (work->rstMarkerIdx + 0xCF);
    }
    skip *= work->restartInterval;
    pitch = state->maxX;
    pos = work->mcuPos;
    row = pos & 0xFF;
    column = pos >> 16;
    mcuIndex = row * pitch + (skip + column);
    work->rstMarkerIdx = (marker + 1) & 7;
    y = mcuIndex / pitch;
    x = mcuIndex % pitch;
    work->components.dcPredict[0] = 0;
    work->components.dcPredict[1] = 0;
    work->components.dcPredict[2] = 0;
    work->components.dcPredict[3] = 0;
    work->restartCnt = 0;
    work->mcuPos = (x << 16) + y;
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
    TMCCJPEGDecState* state;
    TMCCJPEGDecWork* stream;
    s32 result;
    u8 byte;
    u8 marker;

    state = work->pState;
    if (work->scanCount == 1) {
        state->decodeResult = 0;
        return 0;
    }
    stream = work;
    result = TMCJPEGDEC_rewind_ptr(stream);
    if (result < 0) {
        return result;
    }
    byte = *stream->pBufCur;
    for (;;) {
        while (byte != 0xFF) {
            result = TMCJPEGDEC_get_byte(&byte, stream);
            if (result < 0) {
                return result;
            }
        }
        result = TMCJPEGDEC_get_byte(&byte, stream);
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
        if (marker >= 0xD0 && marker <= 0xD7) {
            break;
        }
        // MWCC needs the stream reset here to keep the retail loop-exit branch layout.
        stream = work;
    }
    return restartFromMarker(work, state, marker);
}

void TMCJPEGDEC_set_entropytbl(TMCJpegTableInfo* work, s32 idx, u8 data) {
    switch (idx) {
        case 0: {
            work->pDCFast = work->huffDecTblDC0;
            work->pDCHuffSym = work->maxCodeDC0;
            work->pDCHuffTbl = work->valPtrDC0;
            break;
        }
        case 1: {
            work->pDCFast = work->huffDecTblDC1;
            work->pDCHuffSym = work->maxCodeDC1;
            work->pDCHuffTbl = work->valPtrDC1;
            break;
        }
    }

    if ((s32)data != 1) {
        if ((s32)data < 1 && (s32)data >= 0) {
            work->pACFast = work->huffDecTblAC0;
            work->pACHuffSym = work->maxCodeAC0;
            work->pACHuffTbl = work->valPtrAC0;
        }
    } else {
        work->pACFast = work->huffDecTblAC1;
        work->pACHuffSym = work->maxCodeAC1;
        work->pACHuffTbl = work->valPtrAC1;
    }
}
