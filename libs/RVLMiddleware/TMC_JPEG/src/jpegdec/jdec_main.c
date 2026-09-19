#include <tmc_jpeg_internal.h>

extern void* memset(void* dest, s32 val, u32 count);

extern const u32 lbl_8161E080[64] = {
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
    u8* compMapBase;
    u8* compMapPtr;
    u32* mcuDataInfo;

    u8* curBlockInfo;
    u8* specificConvRowPtr;

    u8* blockCountPtr;
    u8* entTblBase;

    s32 mcuIdx;
    s32 compIdx;
    s32 blockIdx;
    u16 pitch;

    u8* frameInfo;
    u8* scaleInfo;

    u8* convRowPtrs;
    TMCCJPEGDecState* state;

    TMCIdctFunc* idctFunc;
    TMCIdctFunc* idctLumiFunc;
    TMCDecodeFunc* decodeFunc;

    state = work->pState;
    compMapBase = work->compMap;
    frameInfo = (u8*)work + 0x17f0;
    compMapPtr = compMapBase;
    scaleInfo = (u8*)work + 0x58;
    convRowPtrs = (u8*)work + 0x183c;
    mcuDataInfo = (u32*)(compMapBase + 4);
    mcuIdx = 0;

    decodeFunc = work->decodePtr;
    idctFunc = work->idctPtr;
    idctLumiFunc = work->idctLumiPtr;

    pitch = work->pitch;

    while (mcuIdx < (s32) * (frameInfo + 0x1b)) {
        compIdx = *compMapPtr;
        entTblBase = scaleInfo + ((u32) * (compMapBase + compIdx + 0x18) << 8);
        TMCJPEGDEC_set_entropytbl((TMCCJPEGDecWork*)scaleInfo, *(compMapBase + compIdx + 0x1c), *(compMapBase + compIdx + 0x20));

        curBlockInfo = convRowPtrs;
        specificConvRowPtr = convRowPtrs + (compIdx << 2);
        blockCountPtr = frameInfo + mcuIdx;
        blockIdx = 0;

        while (blockIdx < (s32) * (blockCountPtr + 0x1c)) {
            s32 stackBlock[64];
            s32 ret;

            ret = decodeFunc(stackBlock, entTblBase, mcuDataInfo, work);
            if (ret < 0)
                return ret;

            if (compIdx == 0) {
                idctFunc(stackBlock, *(u8**)(curBlockInfo), pitch, ret);
            } else {
                idctLumiFunc(stackBlock, *(u8**)(specificConvRowPtr + 0x10), pitch, ret);
            }

            curBlockInfo += 4;
            blockIdx++;
        }

        mcuDataInfo = (u32*)((u8*)mcuDataInfo + 4);
        mcuIdx++;
        compMapPtr++;
    }

    if (maxMCU != state->dataSizeX && mcuCount != state->dataSizeY)
        work->pConverterFunc(work, maxMCU, mcuCount);
    else {
        work->pConverterFuncEdge(work, maxMCU, mcuCount);
    }

    if (*(u16*)(frameInfo + 0x2a) != 0) {
        s32 r = TMCJPEGDEC_restart_interval(work, maxMCU, mcuCount);
        if (r < 0) {
            return r;
        }
    }

    return 0;
}

#ifdef __MWERKS__
asm s32 TMCJPEGDEC_imagestart(register TMCCJPEGDecWork* work) {
    nofralloc

    stwu r1, -0x20(r1)
    mflr r0
    lis r8, TMCJPEGDEC_Zigzag_data@ha
    li r4, 0
    stw r0, 0x24(r1)
    li r0, 4
    addi r8, r8, TMCJPEGDEC_Zigzag_data@l
    li r7, 0
    stw r31, 0x1c(r1)
    mr r31, r3
    sth r4, 0x181a(r3)
    stb r4, 0x181c(r3)
    mtctr r0

_imagestart_loop:
    lbz r6, 0(r8)
    add r9, r3, r7
    lbz r5, 1(r8)
    addi r7, r7, 8
    rlwinm r6, r6, 2, 0x18, 0x1d
    lbz r4, 2(r8)
    stb r6, 0x458(r9)
    rlwinm r5, r5, 2, 0x18, 0x1d
    rlwinm r6, r4, 2, 0x18, 0x1d
    lbz r0, 3(r8)
    stb r5, 0x459(r9)
    rlwinm r5, r0, 2, 0x18, 0x1d
    lbz r4, 4(r8)
    stb r6, 0x45a(r9)
    rlwinm r6, r4, 2, 0x18, 0x1d
    lbz r4, 6(r8)
    stb r5, 0x45b(r9)
    lbz r0, 5(r8)
    rlwinm r4, r4, 2, 0x18, 0x1d
    stb r6, 0x45c(r9)
    rlwinm r5, r0, 2, 0x18, 0x1d
    lbz r0, 7(r8)
    stb r5, 0x45d(r9)
    lbz r6, 8(r8)
    rlwinm r0, r0, 2, 0x18, 0x1d
    stb r4, 0x45e(r9)
    lbz r5, 9(r8)
    rlwinm r6, r6, 2, 0x18, 0x1d
    stb r0, 0x45f(r9)
    add r9, r3, r7
    lbz r4, 0xa(r8)
    rlwinm r5, r5, 2, 0x18, 0x1d
    stb r6, 0x458(r9)
    addi r7, r7, 8
    rlwinm r6, r4, 2, 0x18, 0x1d
    lbz r0, 0xb(r8)
    stb r5, 0x459(r9)
    rlwinm r5, r0, 2, 0x18, 0x1d
    lbz r4, 0xc(r8)
    stb r6, 0x45a(r9)
    rlwinm r6, r4, 2, 0x18, 0x1d
    lbz r4, 0xe(r8)
    stb r5, 0x45b(r9)
    lbz r0, 0xd(r8)
    rlwinm r4, r4, 2, 0x18, 0x1d
    stb r6, 0x45c(r9)
    rlwinm r5, r0, 2, 0x18, 0x1d
    lbz r0, 0xf(r8)
    stb r5, 0x45d(r9)
    addi r8, r8, 0x10
    rlwinm r0, r0, 2, 0x18, 0x1d
    stb r4, 0x45e(r9)
    stb r0, 0x45f(r9)
    bdnz _imagestart_loop

    mr r4, r31
    addi r3, r1, 8
    bl TMCJPEGDEC_get_wbyte
    cmpwi r3, 0
    bge _imagestart_have_marker
    b _imagestart_return

_imagestart_have_marker:
    lhz r0, 8(r1)
    cmplwi r0, 0xffd8
    beq _imagestart_parse
    li r3, -0x20
    b _imagestart_return

_imagestart_parse:
    li r0, 0
    mr r4, r31
    sth r0, 8(r1)
    addi r3, r1, 8
    bl TMCJPEGDEC_parse_para
    cmpwi r3, 0
    bge _imagestart_check_sof
    b _imagestart_return

_imagestart_check_sof:
    lhz r0, 8(r1)
    cmplwi r0, 0xffc0
    beq _imagestart_parse_sof
    li r3, -0x10
    b _imagestart_return

_imagestart_parse_sof:
    mr r3, r31
    bl TMCJPEGDEC_parse_sof
    srawi r0, r3, 0x1f
    and r3, r3, r0

_imagestart_return:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
#else
s32 TMCJPEGDEC_imagestart(TMCCJPEGDecWork* work) {
    u16 marker;
    s32 r;
    u32 off;
    u8* p;
    int i;
    const u8* zigzag;

    zigzag = TMCJPEGDEC_Zigzag_data;
    work->restartInterval = 0;
    work->scanCount = 0;
    off = 0;
    i = 4;

    do {
        p = (u8*)work + off;
        off += 8;
        p[0x458] = (zigzag[0] & 0x3F) << 2;
        p[0x459] = (zigzag[1] & 0x3F) << 2;
        p[0x45a] = (zigzag[2] & 0x3F) << 2;
        p[0x45b] = (zigzag[3] & 0x3F) << 2;
        p[0x45c] = (zigzag[4] & 0x3F) << 2;
        p[0x45e] = (zigzag[6] & 0x3F) << 2;
        p[0x45d] = (zigzag[5] & 0x3F) << 2;
        p[0x45f] = (zigzag[7] & 0x3F) << 2;

        p = (u8*)work + off;
        off += 8;
        p[0x458] = (zigzag[8] & 0x3F) << 2;
        p[0x459] = (zigzag[9] & 0x3F) << 2;
        p[0x45a] = (zigzag[10] & 0x3F) << 2;
        p[0x45b] = (zigzag[11] & 0x3F) << 2;
        p[0x45c] = (zigzag[12] & 0x3F) << 2;
        p[0x45d] = (zigzag[13] & 0x3F) << 2;
        p[0x45e] = (zigzag[14] & 0x3F) << 2;
        p[0x45f] = (zigzag[15] & 0x3F) << 2;

        zigzag += 16;
    } while (--i != 0);

    r = TMCJPEGDEC_get_wbyte(&marker, work);
    if (r < 0) {
        return r;
    }

    if (marker != 0xFFD8) {
        return -0x20;
    }

    marker = 0;
    r = TMCJPEGDEC_parse_para(&marker, work);
    if (r < 0) {
        return r;
    }

    if (marker != 0xFFC0) {
        return -0x10;
    }

    r = TMCJPEGDEC_parse_sof(work);
    if (r < 0) {
        return r;
    }

    return 0;
}
#endif

s32 TMCJPEGDEC_imageend(TMCCJPEGDecWork* work) {
    if (work->pState->unk_0x21 == 1)
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

        if (marker != 0xFFD9) {
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

    if (marker != 0xFFDA) {
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

    work->dcPredict[0] = 0;
    work->dcPredict[1] = 0;
    work->dcPredict[2] = 0;
    work->dcPredict[3] = 0;
    work->restartCnt = 0;
    r = TMCJPEGDEC_init_buff(work);
    if (r < 0) {
        return r;
    }

    work->rstMarkerIdx = 0;
    work->mcuPos = 0;
    return 0;
}

#ifdef __MWERKS__
asm s32 TMCJPEGDEC_scan_varinit(register TMCCJPEGDecWork* work) {
    nofralloc

    lbz r4, 0x17fc(r3)
    addi r5, r3, 0x17f0
    lbz r0, 0x180b(r3)
    ori r4, r4, 0x100
    cmplwi r0, 1
    stb r4, 0x17fc(r3)
    bne _scan_varinit_multi

    lbz r0, 0x2c(r3)
    lbz r6, 0x28(r5)
    add r8, r5, r0
    lbz r0, 0x29(r5)
    lbz r4, 0x20(r8)
    slwi r9, r6, 3
    slwi r7, r0, 3
    lhz r6, 0(r5)
    divw r0, r9, r4
    lhz r4, 2(r5)
    stb r0, 0xd(r5)
    clrlwi r0, r0, 0x18
    divw r0, r6, r0
    lbz r6, 0x24(r8)
    divw r6, r7, r6
    sth r0, 0x10(r5)
    clrlwi r0, r6, 0x18
    stb r6, 0xe(r5)
    divw r0, r4, r0
    sth r0, 0x12(r5)
    b _scan_varinit_after_mcu

_scan_varinit_multi:
    lbz r4, 0x28(r5)
    lbz r0, 0x29(r5)
    rlwinm r7, r4, 3, 0x18, 0x1c
    lhz r4, 0(r5)
    rlwinm r6, r0, 3, 0x18, 0x1c
    lhz r0, 2(r5)
    divw r4, r4, r7
    stb r7, 0xd(r5)
    stb r6, 0xe(r5)
    divw r0, r0, r6
    sth r4, 0x10(r5)
    sth r0, 0x12(r5)

_scan_varinit_after_mcu:
    lhz r12, 0(r5)
    li r4, 0
    lbz r11, 0xd(r5)
    lhz r10, 2(r5)
    divw r8, r12, r11
    lbz r6, 0xe(r5)
    lhz r9, 0x10(r5)
    lhz r7, 0x12(r5)
    mullw r8, r8, r11
    subf r11, r8, r12
    divw r0, r10, r6
    stb r11, 0x18(r5)
    mullw r8, r0, r6
    clrlwi r6, r11, 0x18
    neg r0, r6
    subf r10, r8, r10
    or r8, r0, r6
    stb r10, 0x19(r5)
    clrlwi r6, r10, 0x18
    neg r0, r6
    srwi r8, r8, 0x1f
    or r0, r0, r6
    add r8, r9, r8
    srwi r0, r0, 0x1f
    sth r8, 0x10(r5)
    add r7, r7, r0
    clrlwi r6, r8, 0x10
    clrlwi r0, r7, 0x10
    sth r7, 0x12(r5)
    mullw r0, r6, r0
    stw r0, 0x14(r5)
    b _scan_varinit_condition

_scan_varinit_component:
    add r6, r3, r4
    cmplwi r0, 1
    lbz r0, 0x2c(r6)
    bne _scan_varinit_component_multi
    li r0, 1
    b _scan_varinit_store_component

_scan_varinit_component_multi:
    add r7, r5, r0
    lbz r6, 0x20(r7)
    lbz r0, 0x24(r7)
    mullw r0, r6, r0

_scan_varinit_store_component:
    add r6, r5, r4
    addi r4, r4, 1
    stb r0, 0x1c(r6)
_scan_varinit_condition:
    lbz r0, 0x1b(r5)
    cmpw r4, r0
    blt _scan_varinit_component

    cmpwi r4, 4
    subfic r3, r4, 4
    li r7, 0
    bge _scan_varinit_return
    rlwinm. r0, r3, 0x1d, 3, 0x1f
    mtctr r0
    beq _scan_varinit_tail_setup

_scan_varinit_unrolled:
    add r6, r5, r4
    addi r4, r4, 1
    stb r7, 0x1c(r6)
    add r6, r5, r4
    addi r4, r4, 1
    stb r7, 0x1c(r6)
    add r6, r5, r4
    addi r4, r4, 1
    stb r7, 0x1c(r6)
    add r6, r5, r4
    addi r4, r4, 1
    stb r7, 0x1c(r6)
    add r6, r5, r4
    addi r4, r4, 1
    stb r7, 0x1c(r6)
    add r6, r5, r4
    addi r4, r4, 1
    stb r7, 0x1c(r6)
    add r6, r5, r4
    addi r4, r4, 1
    stb r7, 0x1c(r6)
    add r6, r5, r4
    addi r4, r4, 1
    stb r7, 0x1c(r6)
    bdnz _scan_varinit_unrolled
    andi. r3, r3, 7
    beq _scan_varinit_return

_scan_varinit_tail_setup:
    mtctr r3

_scan_varinit_tail:
    add r6, r5, r4
    addi r4, r4, 1
    stb r7, 0x1c(r6)
    bdnz _scan_varinit_tail

_scan_varinit_return:
    li r3, 0
    blr
}
#else
s32 TMCJPEGDEC_scan_varinit(TMCCJPEGDecWork* work) {
    s32 idx;
    TMCJpegFrameInfo* p;
    u16 remX;
    u16 remY;

    p = (TMCJpegFrameInfo*)((u8*)work + 0x17f0);
    work->componentCount = work->componentCount | 0x100;

    if (work->scanCompCount == 1) {
        u8 hSamp;
        u8 vSamp;
        int hMul8;
        int vMul8;
        u8 qTblH;
        u8 qTblV;
        TMCJpegFrameInfo* compPtr;

        hSamp = p->maxHSamp;
        compPtr = (TMCJpegFrameInfo*)((u8*)p + work->compMap[0]);
        vSamp = p->maxVSamp;
        qTblH = compPtr->hSampFactor[0];
        hMul8 = hSamp * 8;
        vMul8 = vSamp * 8;
        p->mcuXCount = (u8)(hMul8 / qTblH);
        qTblV = compPtr->vSampFactor[0];
        p->mcuYCount = p->frameWidth / p->mcuXCount;
        p->mcuXRem = (u8)(vMul8 / qTblV);
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

    p->unk_0x18 = remX;
    p->unk_0x19 = remY;

    p->mcuYCount = p->mcuYCount + ((u8)remX != 0 ? 1 : 0);
    p->mcuXCount2 = p->mcuXCount2 + ((u8)remY != 0 ? 1 : 0);
    p->unk_0x14 = (u32)p->mcuYCount * (u32)p->mcuXCount2;

    for (idx = 0; idx < (s32)p->scanCompCount; idx++) {
        u8 compId;
        u32 blocks;

        compId = work->compMap[idx];
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
#endif

s32 TMCJPEGDEC_restart_interval(TMCCJPEGDecWork* work, u32 maxMCU, u32 mcuCount) {
    u16 restartCount;
    u16 interval;
    TMCCJPEGDecState* state;

    restartCount = work->restartCnt;
    interval = work->restartInterval;
    restartCount++;
    state = work->pState;
    work->restartCnt = restartCount;

    if (restartCount == interval) {
        s32 result;
        u16 marker;

        result = TMCJPEGDEC_rewind_ptr(work);
        if (result >= 0) {
            result = TMCJPEGDEC_get_wbyte(&marker, work);
            if (marker == 0xFFD9) {
                work->scanCount = 1;
            }
            if (result >= 0) {
                if (marker >= 0xFFC0 && (marker < 0xFFD0 || marker > 0xFFD7)) {
                    result = TMCJPEGDEC_move_ptr(-2, work);
                    if (result < 0) {
                        return result;
                    }
                } else {
                    s32 expected = work->rstMarkerIdx + 0xFFD0;
                    if (marker != expected) {
                        return -0x23;
                    }
                }

                {
                    u16 idx;
                    u8 stepY;
                    u8 stepX;
                    u16 pitch;

                    idx = work->rstMarkerIdx;
                    idx++;
                    idx &= 7;
                    work->rstMarkerIdx = idx;
                    stepY = state->stepY;
                    stepX = state->stepX;
                    pitch = state->maxX;
                    work->dcPredict[0] = 0;
                    work->dcPredict[1] = 0;
                    work->dcPredict[2] = 0;
                    work->dcPredict[3] = 0;
                    work->restartCnt = 0;

                    {
                        u16 blockCount;
                        u16 mcux;
                        u16 temp;
                        u16 div;
                        u16 rem;

                        blockCount = (u16)(mcuCount / stepY);
                        mcux = (u16)(blockCount * pitch);
                        temp = (u16)(mcux + maxMCU / stepX + 1);
                        div = (u16)(temp / pitch);
                        rem = (u16)(temp - div * pitch);
                        work->mcuPos = ((u32)rem << 16) + div;
                    }
                }

                result = TMCJPEGDEC_init_buff(work);
            }
        }
        return result;
    }
    return 0;
}

#ifdef __MWERKS__
static asm s32 TMCJPEGDEC_parse_para(register u16* marker, register TMCCJPEGDecWork* work) {
    nofralloc

    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stmw r26, 0x18(r1)
    mr r28, r3
    mr r29, r4
    li r31, 0
    lis r26, 1
    li r27, 1
    lhz r30, 0(r3)

_parse_para_loop:
    mr r4, r29
    addi r3, r1, 0x12
    bl TMCJPEGDEC_get_wbyte
    cmpwi r3, 0
    bge _parse_para_marker_loaded
    cmpwi r3, -0x90
    bne _parse_para_return
    lhz r0, 0x12(r1)
    cmplwi r0, 0xffd9
    bne _parse_para_return
    li r3, 0
    b _parse_para_marker_loaded
    b _parse_para_return

_parse_para_marker_loaded:
    lhz r0, 0x12(r1)
    b _parse_para_marker_condition

_parse_para_marker_byte:
    mr r4, r29
    addi r3, r1, 8
    bl TMCJPEGDEC_get_byte
    cmpwi r3, 0
    bge _parse_para_marker_byte_loaded
    b _parse_para_return

_parse_para_marker_byte_loaded:
    lbz r0, 8(r1)
    ori r0, r0, 0xff00
    sth r0, 0x12(r1)

_parse_para_marker_condition:
    clrlwi r4, r0, 0x10
    cmplwi r4, 0xffff
    beq _parse_para_marker_byte
    cmplwi r4, 0xffe0
    blt _parse_para_switch
    cmplwi r4, 0xffef
    bgt _parse_para_switch
    mr r4, r29
    addi r3, r1, 0x10
    bl TMCJPEGDEC_get_wbyte
    cmpwi r3, 0
    bge _parse_para_app_length
    b _parse_para_check_result

_parse_para_app_length:
    lhz r3, 0x10(r1)
    cmplwi r3, 2
    bge _parse_para_app_move
    li r3, -0x45
    b _parse_para_check_result

_parse_para_app_move:
    addi r0, r3, -2
    mr r4, r29
    sth r0, 0x10(r1)
    clrlwi r3, r0, 0x10
    bl TMCJPEGDEC_move_ptr
    srawi r0, r3, 0x1f
    and r3, r3, r0
    srawi r0, r3, 0x1f
    and r3, r3, r0
    b _parse_para_check_result

_parse_para_switch:
    addi r0, r26, -0x27
    cmpw r4, r0
    beq _parse_para_eoi
    bge _parse_para_switch_ge_ffc2
    addi r0, r26, -0x3e
    cmpw r4, r0
    beq _parse_para_sos
    bge _parse_para_switch_ge_ffc4
    addi r0, r26, -0x40
    cmpw r4, r0
    beq _parse_para_sof
    b _parse_para_unknown

_parse_para_switch_ge_ffc4:
    addi r0, r26, -0x3c
    cmpw r4, r0
    beq _parse_para_dht
    b _parse_para_unknown

_parse_para_switch_ge_ffc2:
    addi r0, r26, -0x23
    cmpw r4, r0
    beq _parse_para_dri
    bge _parse_para_switch_ge_ffdc
    addi r0, r26, -0x25
    cmpw r4, r0
    beq _parse_para_dqt
    bge _parse_para_dnl
    b _parse_para_com_marker

_parse_para_switch_ge_ffdc:
    addi r0, r26, -2
    cmpw r4, r0
    beq _parse_para_com
    b _parse_para_unknown

_parse_para_dht:
    mr r3, r30
    mr r4, r29
    bl TMCJPEGDEC_parse_dht
    b _parse_para_check_result

_parse_para_dqt:
    mr r3, r29
    bl TMCJPEGDEC_parse_dqt
    b _parse_para_check_result

_parse_para_dri:
    mr r4, r29
    addi r3, r1, 0xe
    bl TMCJPEGDEC_get_wbyte
    cmpwi r3, 0
    bge _parse_para_dri_length
    b _parse_para_check_result

_parse_para_dri_length:
    lhz r0, 0xe(r1)
    cmplwi r0, 4
    beq _parse_para_dri_value
    li r3, -0x42
    b _parse_para_check_result

_parse_para_dri_value:
    mr r4, r29
    addi r3, r1, 0xe
    bl TMCJPEGDEC_get_wbyte
    cmpwi r3, 0
    bge _parse_para_dri_store
    b _parse_para_check_result

_parse_para_dri_store:
    lhz r0, 0xe(r1)
    li r3, 0
    sth r0, 0x181a(r29)
    b _parse_para_check_result

_parse_para_dnl:
    mr r4, r29
    addi r3, r1, 0xc
    bl TMCJPEGDEC_get_wbyte
    cmpwi r3, 0
    bge _parse_para_dnl_length
    b _parse_para_check_result

_parse_para_dnl_length:
    lhz r0, 0xc(r1)
    cmplwi r0, 4
    beq _parse_para_dnl_value
    li r3, -0x43
    b _parse_para_check_result

_parse_para_dnl_value:
    mr r4, r29
    addi r3, r1, 0xc
    bl TMCJPEGDEC_get_wbyte
    cmpwi r3, 0
    bge _parse_para_dnl_store
    b _parse_para_check_result

_parse_para_dnl_store:
    lhz r0, 0xc(r1)
    li r3, 0
    sth r0, 0x17f2(r29)
    b _parse_para_check_result

_parse_para_com:
    mr r4, r29
    addi r3, r1, 0xa
    bl TMCJPEGDEC_get_wbyte
    cmpwi r3, 0
    bge _parse_para_com_length
    b _parse_para_check_result

_parse_para_com_length:
    lhz r3, 0xa(r1)
    cmplwi r3, 2
    bge _parse_para_com_move
    li r3, -0x44
    b _parse_para_check_result

_parse_para_com_move:
    addi r0, r3, -2
    mr r4, r29
    sth r0, 0xa(r1)
    clrlwi r3, r0, 0x10
    bl TMCJPEGDEC_move_ptr
    srawi r0, r3, 0x1f
    and r3, r3, r0
    srawi r0, r3, 0x1f
    and r3, r3, r0
    b _parse_para_check_result

_parse_para_sof:
    li r31, 1
    b _parse_para_check_result

_parse_para_sos:
    li r31, 1
    b _parse_para_check_result

_parse_para_com_marker:
    li r31, 1
    b _parse_para_check_result

_parse_para_eoi:
    stb r27, 0x181c(r29)
    li r31, 1
    b _parse_para_check_result

_parse_para_unknown:
    li r3, -0x2f

_parse_para_check_result:
    cmpwi r3, 0
    bge _parse_para_keep_going
    li r31, 1

_parse_para_keep_going:
    cmpwi r31, 0
    beq _parse_para_loop
    lhz r0, 0x12(r1)
    sth r0, 0(r28)

_parse_para_return:
    lmw r26, 0x18(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}
#else
static s32 TMCJPEGDEC_parse_para(u16* marker, TMCCJPEGDecWork* work) {
    u8 byte;
    u16 local;
    u16 appSize;
    u16 driSize;
    u16 dnlSize;
    u16 comSize;
    s32 result;

    u32 keepGoing = 0;
    u16 firstMarker = *marker;

    do {
        result = TMCJPEGDEC_get_wbyte(&local, work);
        if (result < 0) {
            if (result == TMCC_ERROR_UNDERFLOW && local == 0xFFD9) {
                result = 0;
            } else {
                return result;
            }
        }

        while (local == 0xFFFF) {
            result = TMCJPEGDEC_get_byte(&byte, work);
            if (result < 0) {
                return result;
            }
            local = 0xFF00 | byte;
        }

        if (local >= 0xFFE0 && local <= 0xFFEF) {
            result = TMCJPEGDEC_get_wbyte(&appSize, work);
            if (result < 0) {
                goto _check;
            }
            if (appSize < 2) {
                result = -0x45;
                goto _check;
            }
            appSize -= 2;
            result = TMCJPEGDEC_move_ptr(appSize, work);
            result = result & (result >> 31);
            result = result & (result >> 31);
        } else {
            switch ((s32)local) {
                case 0xFFC4: {
                    result = TMCJPEGDEC_parse_dht(firstMarker, work);
                    break;
                }
                case 0xFFDB: {
                    result = TMCJPEGDEC_parse_dqt(work);
                    break;
                }
                case 0xFFDD: {
                    result = TMCJPEGDEC_get_wbyte(&driSize, work);
                    if (result >= 0) {
                        if (driSize != 4) {
                            result = -0x42;
                        } else {
                            result = TMCJPEGDEC_get_wbyte(&driSize, work);
                            if (result < 0) {
                                goto _check;
                            }
                            work->restartInterval = driSize;
                            result = 0;
                        }
                    }
                    break;
                }
                case 0xFFDC: {
                    result = TMCJPEGDEC_get_wbyte(&dnlSize, work);
                    if (result >= 0) {
                        if (dnlSize != 4) {
                            result = -0x43;
                        } else {
                            result = TMCJPEGDEC_get_wbyte(&dnlSize, work);
                            if (result >= 0) {
                                work->frameHeight = dnlSize;
                                result = 0;
                            }
                        }
                    }
                    break;
                }
                case 0xFFFE: {
                    result = TMCJPEGDEC_get_wbyte(&comSize, work);
                    if (result >= 0) {
                        if (comSize < 2) {
                            result = -0x44;
                        } else {
                            comSize -= 2;
                            result = TMCJPEGDEC_move_ptr(comSize, work);
                            result = result & result >> 31;
                            result = result & result >> 31;
                        }
                    }
                    break;
                }
                case 0xFFC0: {
                    keepGoing = 1;
                    break;
                }
                case 0xFFC2: {
                    keepGoing = 1;
                    break;
                }
                case 0xFFDA: {
                    keepGoing = 1;
                    break;
                }
                case 0xFFD9: {
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

    _check:
        if (result < 0) {
            keepGoing = 1;
        }
    } while (keepGoing == 0);

    *marker = local;
    return result;
}
#endif

#ifdef __MWERKS__
static asm s32 TMCJPEGDEC_parse_dht(register s32 first, register TMCCJPEGDecWork* work) {
    nofralloc

    stwu r1, -0x160(r1)
    mflr r0
    li r5, 0x11
    stw r0, 0x164(r1)
    addi r3, r1, 0x20
    stmw r25, 0x144(r1)
    mr r30, r4
    addi r31, r4, 0x58
    li r4, 0
    bl memset
    mr r4, r30
    addi r3, r1, 0xa
    bl TMCJPEGDEC_get_wbyte
    cmpwi r3, 0
    bge _parse_dht_have_length
    b _parse_dht_return

_parse_dht_have_length:
    lhz r3, 0xa(r1)
    li r29, 0
    addi r0, r3, -2
    sth r0, 0xa(r1)

_parse_dht_table:
    lhz r5, 0xa(r1)
    mr r4, r30
    addi r3, r1, 8
    addi r0, r5, -0x11
    sth r0, 0xa(r1)
    bl TMCJPEGDEC_get_byte
    cmpwi r3, 0
    bge _parse_dht_have_info
    b _parse_dht_return

_parse_dht_have_info:
    lbz r0, 8(r1)
    srawi r27, r0, 4
    clrlwi r26, r0, 0x1c
    cmpwi r27, 2
    bge _parse_dht_bad_table
    cmpwi r26, 2
    blt _parse_dht_valid_table

_parse_dht_bad_table:
    li r3, -0x40
    b _parse_dht_return

_parse_dht_valid_table:
    stb r29, 0x20(r1)
    addi r28, r1, 0x21
    li r25, 1

_parse_dht_count_loop:
    mr r4, r30
    addi r3, r1, 8
    bl TMCJPEGDEC_get_byte
    cmpwi r3, 0
    bge _parse_dht_have_count
    b _parse_dht_return

_parse_dht_have_count:
    lbz r3, 8(r1)
    addi r25, r25, 1
    lhz r0, 0xa(r1)
    cmpwi r25, 0x10
    stb r3, 0(r28)
    addi r28, r28, 1
    subf r0, r3, r0
    sth r0, 0xa(r1)
    ble _parse_dht_count_loop

    lbz r4, 0x21(r1)
    lbz r0, 0x22(r1)
    lbz r3, 0x23(r1)
    add r25, r4, r0
    lbz r0, 0x24(r1)
    add r25, r25, r3
    lbz r3, 0x25(r1)
    add r25, r25, r0
    lbz r0, 0x26(r1)
    add r25, r25, r3
    lbz r3, 0x27(r1)
    add r25, r25, r0
    lbz r0, 0x28(r1)
    add r25, r25, r3
    lbz r4, 0x29(r1)
    add r25, r25, r0
    lbz r0, 0x2a(r1)
    add r25, r25, r4
    lbz r3, 0x2b(r1)
    add r25, r25, r0
    lbz r0, 0x2c(r1)
    add r25, r25, r3
    lbz r3, 0x2d(r1)
    add r25, r25, r0
    lbz r0, 0x2e(r1)
    add r25, r25, r3
    lbz r3, 0x2f(r1)
    add r25, r25, r0
    lbz r0, 0x30(r1)
    add r25, r25, r3
    add r25, r25, r0
    cmpwi r25, 0xb0
    ble _parse_dht_valid_count
    li r3, -0x40
    b _parse_dht_return

_parse_dht_valid_count:
    mr r5, r30
    addi r3, r1, 0x38
    clrlwi r4, r25, 0x18
    bl TMCJPEGDEC_get_sbyte
    cmpwi r3, 0
    bge _parse_dht_have_symbols
    b _parse_dht_return

_parse_dht_have_symbols:
    stb r25, 0x1c(r1)
    mr r4, r27
    mr r5, r26
    mr r6, r31
    addi r3, r1, 0x10
    bl TMCJPEGDEC_set_HuffmanTable
    addi r3, r1, 0x20
    addi r4, r1, 0x38
    addi r5, r1, 0x10
    bl TMCJPEGDEC_make_huffdec
    cmpwi r3, 0
    bge _parse_dht_check_length
    b _parse_dht_return

_parse_dht_check_length:
    lhz r0, 0xa(r1)
    cmpwi r0, 0
    bne _parse_dht_table
    li r3, 0

_parse_dht_return:
    lmw r25, 0x144(r1)
    lwz r0, 0x164(r1)
    mtlr r0
    addi r1, r1, 0x160
    blr
}
#else
static s32 TMCJPEGDEC_parse_dht(s32 first, TMCCJPEGDecWork* work) {
    TMCUnknownInfo* scaleInfo;
    u16 len;
    u8 countBuf[17];
    u8 symBuf[256];
    s32 r;
    TMCHuffParam tblSet;

    scaleInfo = (TMCUnknownInfo*)&work->scaleFlag;

    memset(countBuf, 0, 17);

    r = TMCJPEGDEC_get_wbyte(&len, work);
    if (r < 0) {
        return r;
    }
    len -= 2;

    do {
        u8 htByte;
        u8* pCount;
        s32 idx;
        s32 totalCodes;

        s32 tblID;
        s32 tblClass;

        len -= 0x11;
        r = TMCJPEGDEC_get_byte(&htByte, work);
        if (r < 0) {
            return r;
        }

        tblClass = htByte >> 4;
        tblID = htByte & 0xF;

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

        totalCodes = countBuf[1];
        totalCodes += countBuf[2];
        totalCodes += countBuf[3];
        totalCodes += countBuf[4];
        totalCodes += countBuf[5];
        totalCodes += countBuf[6];
        totalCodes += countBuf[7];
        totalCodes += countBuf[8];
        totalCodes += countBuf[9];
        totalCodes += countBuf[10];
        totalCodes += countBuf[11];
        totalCodes += countBuf[12];
        totalCodes += countBuf[13];
        totalCodes += countBuf[14];
        totalCodes += countBuf[15];
        totalCodes += countBuf[16];

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
#endif

#ifdef __MWERKS__
static asm s32 TMCJPEGDEC_parse_dqt(register TMCCJPEGDecWork* work) {
    nofralloc

    stwu r1, -0x130(r1)
    mflr r0
    lis r4, lbl_8161E080@ha
    stw r0, 0x134(r1)
    addi r4, r4, lbl_8161E080@l
    li r0, 0x20
    addi r6, r1, 0xc
    stmw r24, 0x110(r1)
    mr r30, r3
    addi r5, r4, -4
    mtctr r0

_parse_dqt_copy:
    lwz r4, 4(r5)
    lwzu r0, 8(r5)
    stw r4, 4(r6)
    stwu r0, 8(r6)
    bdnz _parse_dqt_copy

    addi r31, r3, 0x58
    mr r4, r30
    addi r3, r1, 0xa
    bl TMCJPEGDEC_get_wbyte
    cmpwi r3, 0
    bge _parse_dqt_have_length
    b _parse_dqt_return

_parse_dqt_have_length:
    lhz r3, 0xa(r1)
    addi r29, r1, 0x10
    li r27, 1
    lis r28, TMCJPEGDEC_Zigzag_data@ha
    addi r0, r3, -2
    sth r0, 0xa(r1)

_parse_dqt_table:
    lhz r5, 0xa(r1)
    mr r4, r30
    addi r3, r1, 9
    addi r0, r5, -0x41
    sth r0, 0xa(r1)
    bl TMCJPEGDEC_get_byte
    cmpwi r3, 0
    bge _parse_dqt_have_qt_info
    b _parse_dqt_return

_parse_dqt_have_qt_info:
    lbz r0, 9(r1)
    cmplwi r0, 4
    ble _parse_dqt_valid_qt_info
    li r3, -0x41
    b _parse_dqt_return

_parse_dqt_valid_qt_info:
    add r3, r31, r0
    addi r26, r28, TMCJPEGDEC_Zigzag_data@l
    stb r27, 0x1790(r3)
    li r25, 0

_parse_dqt_coeff:
    lbz r24, 0(r26)
    cmpwi r24, 0x3f
    ble _parse_dqt_valid_coeff
    li r3, -0x41
    b _parse_dqt_return

_parse_dqt_valid_coeff:
    mr r4, r30
    addi r3, r1, 8
    bl TMCJPEGDEC_get_byte
    cmpwi r3, 0
    bge _parse_dqt_have_coeff
    b _parse_dqt_return

_parse_dqt_have_coeff:
    slwi r4, r24, 2
    lbz r3, 9(r1)
    add r0, r4, r31
    lbz r5, 8(r1)
    lwzx r4, r29, r4
    slwi r3, r3, 8
    mullw. r4, r5, r4
    stwx r4, r3, r0
    bne _parse_dqt_nonzero
    li r3, -0x41
    b _parse_dqt_return

_parse_dqt_nonzero:
    addi r25, r25, 1
    addi r26, r26, 1
    cmpwi r25, 0x40
    blt _parse_dqt_coeff
    lhz r0, 0xa(r1)
    cmpwi r0, 0
    bne _parse_dqt_table
    li r3, 0

_parse_dqt_return:
    lmw r24, 0x110(r1)
    lwz r0, 0x134(r1)
    mtlr r0
    addi r1, r1, 0x130
    blr
}
#else
static s32 TMCJPEGDEC_parse_dqt(TMCCJPEGDecWork* work) {
    typedef struct {
        u32 data[64];
    } CopyBlock64;

    u8* scaleInfo;
    u32 tblCopy[65];
    u32* tblPtr;
    u32* d;
    u16 len;
    s32 r;

    d = tblCopy;
    *(CopyBlock64*)(d + 1) = *(CopyBlock64*)lbl_8161E080;

    scaleInfo = (u8*)work + 0x58;

    r = TMCJPEGDEC_get_wbyte(&len, work);
    if (r < 0) {
        return r;
    }
    len -= 2;

    tblPtr = &tblCopy[1];

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

        scaleInfo[qtInfo + 0x1790] = 1;  // quantTblFlag[0..3]

        zigPtr = TMCJPEGDEC_Zigzag_data;
        for (zzIdx = 0; zzIdx < 64; zzIdx++) {
            u32 tmp;

            zz = *zigPtr;
            if (zz > 0x3F) {
                return -0x41;
            }

            r = TMCJPEGDEC_get_byte(&byte, work);
            if (r < 0) {
                return r;
            }

            tmp = (zz << 2) + ((u32)qtInfo << 8);
            val = (u32)byte * tblPtr[zz];
            *(u32*)(tmp + scaleInfo) = val;
            if (val == 0) {
                return -0x41;
            }

            zigPtr++;
        }
    } while (len != 0);

    return 0;
}
#endif

#ifdef __MWERKS__
static asm s32 TMCJPEGDEC_parse_sof(register TMCCJPEGDecWork* work) {
    nofralloc

    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stmw r25, 0x14(r1)
    mr r27, r3
    addi r29, r3, 0x17f0
    addi r28, r3, 0x2c
    addi r3, r1, 0xa
    mr r4, r27
    bl TMCJPEGDEC_get_wbyte
    cmpwi r3, 0
    bge _parse_sof_have_length
    b _parse_sof_return

_parse_sof_have_length:
    lhz r0, 0xa(r1)
    cmplwi r0, 2
    bge _parse_sof_have_precision
    li r3, -0x50
    b _parse_sof_return

_parse_sof_have_precision:
    mr r4, r27
    addi r3, r1, 8
    bl TMCJPEGDEC_get_byte
    cmpwi r3, 0
    bge _parse_sof_check_precision
    b _parse_sof_return

_parse_sof_check_precision:
    lbz r0, 8(r1)
    cmplwi r0, 8
    beq _parse_sof_get_height
    li r3, -0x50
    b _parse_sof_return

_parse_sof_get_height:
    mr r4, r27
    addi r3, r1, 0xa
    bl TMCJPEGDEC_get_wbyte
    cmpwi r3, 0
    bge _parse_sof_store_height
    b _parse_sof_return

_parse_sof_store_height:
    lhz r0, 0xa(r1)
    mr r4, r27
    addi r3, r1, 0xa
    sth r0, 2(r29)
    bl TMCJPEGDEC_get_wbyte
    cmpwi r3, 0
    bge _parse_sof_store_width
    b _parse_sof_return

_parse_sof_store_width:
    lhz r0, 0xa(r1)
    mr r4, r27
    addi r3, r1, 8
    sth r0, 0(r29)
    bl TMCJPEGDEC_get_byte
    cmpwi r3, 0
    bge _parse_sof_store_components
    b _parse_sof_return

_parse_sof_store_components:
    lbz r0, 8(r1)
    cmpwi r0, 0
    stb r0, 0x1a(r29)
    ble _parse_sof_bad_header
    cmpwi r0, 4
    ble _parse_sof_components_valid

_parse_sof_bad_header:
    li r3, -0x50
    b _parse_sof_return

_parse_sof_components_valid:
    li r30, 0
    li r31, 0
    li r25, 0
    b _parse_sof_component_condition

_parse_sof_component_loop:
    mr r4, r27
    addi r3, r1, 8
    bl TMCJPEGDEC_get_byte
    cmpwi r3, 0
    bge _parse_sof_have_component_id
    b _parse_sof_return

_parse_sof_have_component_id:
    lbz r0, 8(r1)
    add r26, r28, r25
    mr r4, r27
    addi r3, r1, 8
    stb r0, 0x14(r26)
    bl TMCJPEGDEC_get_byte
    cmpwi r3, 0
    bge _parse_sof_have_sampling
    b _parse_sof_return

_parse_sof_have_sampling:
    lbz r0, 8(r1)
    add r4, r29, r25
    srawi r3, r0, 4
    clrlwi r0, r0, 0x1c
    stb r3, 0x20(r4)
    cmpw r3, r31
    stb r0, 0x24(r4)
    ble _parse_sof_check_v_sampling
    mr r31, r3

_parse_sof_check_v_sampling:
    lbz r0, 0x24(r4)
    cmpw r0, r30
    ble _parse_sof_get_qtable
    mr r30, r0

_parse_sof_get_qtable:
    mr r4, r27
    addi r3, r1, 8
    bl TMCJPEGDEC_get_byte
    cmpwi r3, 0
    bge _parse_sof_store_qtable
    b _parse_sof_return

_parse_sof_store_qtable:
    lbz r0, 8(r1)
    addi r25, r25, 1
    stb r0, 0x18(r26)

_parse_sof_component_condition:
    lbz r0, 0x1a(r29)
    cmpw r25, r0
    blt _parse_sof_component_loop
    clrlwi. r0, r31, 0x10
    beq _parse_sof_bad_sampling
    clrlwi. r0, r30, 0x10
    bne _parse_sof_sampling_valid

_parse_sof_bad_sampling:
    li r3, -0x50
    b _parse_sof_return

_parse_sof_sampling_valid:
    li r0, 6
    lis r6, TMCJPEGDEC_SampleComps@ha
    lis r7, TMCJPEGDEC_SampleH_N@ha
    lis r8, TMCJPEGDEC_SampleV_N@ha
    stb r31, 0x28(r29)
    addi r6, r6, TMCJPEGDEC_SampleComps@l
    addi r7, r7, TMCJPEGDEC_SampleH_N@l
    addi r8, r8, TMCJPEGDEC_SampleV_N@l
    stb r30, 0x29(r29)
    li r10, 0
    stb r0, 0xc(r29)

_parse_sof_sample_loop:
    lbz r5, 0x1a(r29)
    lbz r0, 0(r6)
    cmplw r5, r0
    bne _parse_sof_sample_next
    mr r4, r7
    mr r3, r8
    li r11, 0
    mtctr r5
    cmpwi r5, 0
    ble _parse_sof_sample_match

_parse_sof_sample_compare:
    add r9, r29, r11
    lbz r0, 0(r4)
    lbz r5, 0x20(r9)
    cmplw r5, r0
    bne _parse_sof_sample_next
    lbz r5, 0x24(r9)
    lbz r0, 0(r3)
    cmplw r5, r0
    bne _parse_sof_sample_next
    addi r11, r11, 1
    addi r3, r3, 1
    addi r4, r4, 1
    bdnz _parse_sof_sample_compare

_parse_sof_sample_match:
    stb r10, 0xc(r29)

_parse_sof_sample_next:
    addi r10, r10, 1
    addi r7, r7, 4
    cmpwi r10, 6
    addi r8, r8, 4
    addi r6, r6, 1
    blt _parse_sof_sample_loop
    lbz r0, 0xc(r29)
    cmplwi r0, 6
    bne _parse_sof_setup_mcu
    li r3, -0x70
    b _parse_sof_return

_parse_sof_setup_mcu:
    lhz r9, 0(r29)
    rlwinm r8, r31, 3, 0x18, 0x1c
    rlwinm r12, r30, 3, 0x18, 0x1c
    lhz r11, 2(r29)
    divw r6, r9, r8
    stb r8, 0xd(r29)
    lbz r5, 0x180a(r27)
    addi r3, r27, 0x17f0
    addi r0, r27, 0x2c
    stb r12, 0xe(r29)
    clrlwi r10, r6, 0x10
    li r4, 0
    mullw r6, r6, r8
    divw r7, r11, r12
    subf r6, r6, r9
    stb r6, 0x18(r29)
    mullw r9, r7, r12
    clrlwi r8, r7, 0x10
    clrlwi r7, r6, 0x18
    neg r6, r7
    subf r11, r9, r11
    or r9, r6, r7
    stb r11, 0x19(r29)
    clrlwi r7, r11, 0x18
    neg r6, r7
    srwi r9, r9, 0x1f
    or r6, r6, r7
    add r9, r10, r9
    srwi r6, r6, 0x1f
    sth r9, 0x10(r29)
    add r8, r8, r6
    clrlwi r7, r9, 0x10
    clrlwi r6, r8, 0x10
    sth r8, 0x12(r29)
    mullw r6, r7, r6
    stw r6, 0x14(r29)
    mtctr r5
    cmpwi r5, 0
    ble _parse_sof_component_check_done

_parse_sof_component_check:
    add r5, r3, r4
    lbz r6, 0x20(r5)
    cmplwi r6, 1
    blt _parse_sof_bad_component
    cmplwi r6, 4
    ble _parse_sof_check_v_factor

_parse_sof_bad_component:
    li r3, -0x50
    b _parse_sof_return

_parse_sof_check_v_factor:
    lbz r5, 0x24(r5)
    cmplwi r5, 1
    blt _parse_sof_bad_v_factor
    cmplwi r5, 4
    ble _parse_sof_check_qtable

_parse_sof_bad_v_factor:
    li r3, -0x50
    b _parse_sof_return

_parse_sof_check_qtable:
    add r5, r0, r4
    lbz r5, 0x18(r5)
    cmplwi r5, 4
    ble _parse_sof_next_check
    li r3, -0x50
    b _parse_sof_return

_parse_sof_next_check:
    addi r4, r4, 1
    bdnz _parse_sof_component_check

_parse_sof_component_check_done:
    li r3, 0

_parse_sof_return:
    lmw r25, 0x14(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}
#else
static s32 TMCJPEGDEC_parse_sof(TMCCJPEGDecWork* work) {
    TMCJpegFrameInfo* frameInfo = (TMCJpegFrameInfo*)((u8*)work + 0x17f0);

    u16 len;
    u8 precision;
    u16 height;
    u16 width;
    u8 compCount;
    s32 r;
    s32 maxHSamp;
    s32 maxVSamp;
    u32 idx;

    maxHSamp = 0;
    maxVSamp = 0;

    r = TMCJPEGDEC_get_wbyte(&len, work);
    if (r < 0) {
        return r;
    }
    if (len < 2) {
        return TMCC_ERROR_HEADER;
    }

    r = TMCJPEGDEC_get_byte(&precision, work);
    if (r < 0) {
        return r;
    }
    if (precision != 8) {
        return TMCC_ERROR_HEADER;
    }

    r = TMCJPEGDEC_get_wbyte(&height, work);
    if (r < 0) {
        return r;
    }
    frameInfo->frameHeight = height;

    r = TMCJPEGDEC_get_wbyte(&width, work);
    if (r < 0) {
        return r;
    }
    frameInfo->frameWidth = width;

    r = TMCJPEGDEC_get_byte(&compCount, work);
    if (r < 0) {
        return r;
    }
    if (compCount <= 0 || compCount > 4) {
        return TMCC_ERROR_HEADER;
    }

    frameInfo->compCount = compCount;

    for (idx = 0; idx < compCount; idx++) {
        u8 compId;
        u8 hSamp;
        u8 vSamp;
        u8 qTbl;

        r = TMCJPEGDEC_get_byte(&compId, work);
        if (r < 0) {
            return r;
        }
        work->compId[idx] = compId;

        r = TMCJPEGDEC_get_byte(&hSamp, work);
        if (r < 0) {
            return r;
        }
        vSamp = hSamp & 0xF;
        hSamp = hSamp >> 4;

        frameInfo->hSampFactor[idx] = hSamp;
        frameInfo->vSampFactor[idx] = vSamp;

        if (hSamp > maxHSamp)
            maxHSamp = hSamp;

        if (vSamp > maxVSamp)
            maxVSamp = vSamp;

        r = TMCJPEGDEC_get_byte(&qTbl, work);
        if (r < 0) {
            return r;
        }
        work->compQTbl[idx] = qTbl;
    }

    if (maxHSamp == 0 || maxVSamp == 0) {
        return TMCC_ERROR_HEADER;
    }

    frameInfo->maxHSamp = maxHSamp;
    frameInfo->maxVSamp = maxVSamp;
    frameInfo->componentCount = 6;

    {
        u32 sampleIdx;

        for (sampleIdx = 0; sampleIdx < 6; sampleIdx++) {
            u32 c;
            u8 match;

            if (frameInfo->compCount != TMCJPEGDEC_SampleComps[sampleIdx]) {
                continue;
            }

            match = TRUE;
            for (c = 0; c < frameInfo->compCount; c++) {
                if (frameInfo->hSampFactor[c] != TMCJPEGDEC_SampleH_N[sampleIdx * 4 + c] ||
                    frameInfo->vSampFactor[c] != TMCJPEGDEC_SampleV_N[sampleIdx * 4 + c]) {
                    match = FALSE;
                    break;
                }
            }

            if (match) {
                frameInfo->componentCount = sampleIdx;
                break;
            }
        }
    }

    if (frameInfo->componentCount == 6) {
        return -0x70;
    }

    {
        u16 fw = frameInfo->frameWidth;
        u16 fh = frameInfo->frameHeight;
        u8 mcuX = (maxHSamp & 0x07) << 3;
        u8 mcuY = (maxVSamp & 0x07) << 3;
        u16 mcuCountX;
        u16 mcuCountY;
        u16 remX;
        u16 remY;
        u32 compCount2;

        frameInfo->mcuXCount = mcuX;
        frameInfo->mcuXRem = mcuY;

        mcuCountX = fw / mcuX;
        mcuCountY = fh / mcuY;

        remX = fw - mcuCountX * mcuX;
        remY = fh - mcuCountY * mcuY;

        work->unk_0x1808 = remX;
        work->unk_0x1809 = remY;

        {
            u16 xr = (remX != 0) ? 1 : 0;
            u16 yr = (remY != 0) ? 1 : 0;
            mcuCountX += xr;
            mcuCountY += yr;
            frameInfo->mcuYCount = mcuCountX;
            frameInfo->mcuXCount2 = mcuCountY;
            work->unk_0x1804 = (u32)mcuCountX * (u32)mcuCountY;
        }

        compCount2 = frameInfo->compCount;
        for (idx = 0; idx < compCount2; idx++) {
            u8 hSamp2;
            u8 vSamp2;
            u8 qTbl2;

            hSamp2 = frameInfo->hSampFactor[idx];
            if (hSamp2 < 1 || hSamp2 > 4) {
                return TMCC_ERROR_HEADER;
            }

            vSamp2 = frameInfo->vSampFactor[idx];
            if (vSamp2 < 1 || vSamp2 > 4) {
                return TMCC_ERROR_HEADER;
            }

            qTbl2 = work->compQTbl[idx];
            if (qTbl2 > 4) {
                return TMCC_ERROR_HEADER;
            }
        }
    }

    return 0;
}
#endif

#ifdef __MWERKS__
static asm s32 TMCJPEGDEC_parse_sos(register TMCCJPEGDecWork* work) {
    nofralloc

    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stmw r27, 0x1c(r1)
    mr r28, r3
    addi r30, r3, 0x2c
    addi r29, r3, 0x58
    addi r3, r1, 0xa
    mr r4, r28
    bl TMCJPEGDEC_get_wbyte
    cmpwi r3, 0
    bge _parse_sos_have_length
    b _parse_sos_return

_parse_sos_have_length:
    lhz r0, 0xa(r1)
    cmplwi r0, 2
    bge _parse_sos_have_count
    li r3, -0x51
    b _parse_sos_return

_parse_sos_have_count:
    mr r4, r28
    addi r3, r1, 8
    bl TMCJPEGDEC_get_byte
    cmpwi r3, 0
    bge _parse_sos_store_count
    b _parse_sos_return

_parse_sos_store_count:
    lbz r3, 8(r1)
    cmplwi r3, 4
    stb r3, 0x180b(r28)
    bgt _parse_sos_bad_count
    lbz r0, 0x180a(r28)
    cmplw r3, r0
    beq _parse_sos_count_valid

_parse_sos_bad_count:
    li r3, -0x51
    b _parse_sos_return

_parse_sos_count_valid:
    li r31, 0
    b _parse_sos_loop_condition

_parse_sos_loop:
    mr r4, r28
    addi r3, r1, 8
    bl TMCJPEGDEC_get_byte
    cmpwi r3, 0
    bge _parse_sos_have_component
    b _parse_sos_return

_parse_sos_have_component:
    lbz r0, 0x180a(r28)
    li r5, 0
    lbz r4, 8(r1)
    mtctr r0
    cmpwi r0, 0
    ble _parse_sos_bad_component

_parse_sos_find_component:
    add r3, r30, r5
    lbz r0, 0x14(r3)
    cmpw r4, r0
    bne _parse_sos_next_component
    stbx r5, r30, r31
    add r27, r30, r31
    b _parse_sos_found_component

_parse_sos_next_component:
    addi r5, r5, 1
    bdnz _parse_sos_find_component

_parse_sos_bad_component:
    li r3, -0x51
    b _parse_sos_return

_parse_sos_found_component:
    mr r4, r28
    addi r3, r1, 8
    bl TMCJPEGDEC_get_byte
    cmpwi r3, 0
    bge _parse_sos_have_tables
    b _parse_sos_return

_parse_sos_have_tables:
    lbz r0, 8(r1)
    srawi r5, r0, 4
    clrlwi r6, r0, 0x1c
    cmpwi r5, 1
    bgt _parse_sos_bad_tables
    cmpwi r6, 1
    ble _parse_sos_tables_valid

_parse_sos_bad_tables:
    li r3, -0x51
    b _parse_sos_return

_parse_sos_tables_valid:
    lbz r0, 0(r27)
    add r3, r29, r5
    add r4, r30, r0
    stb r5, 0x1c(r4)
    lbz r0, 0(r27)
    add r4, r30, r0
    stb r6, 0x20(r4)
    lbz r0, 0x1794(r3)
    cmplwi r0, 1
    beq _parse_sos_ac_valid
    li r3, -0x40
    b _parse_sos_return

_parse_sos_ac_valid:
    add r3, r29, r6
    lbz r0, 0x1796(r3)
    cmplwi r0, 1
    beq _parse_sos_quant_valid
    li r3, -0x40
    b _parse_sos_return

_parse_sos_quant_valid:
    lbz r0, 0x18(r27)
    add r3, r29, r0
    lbz r0, 0x1790(r3)
    cmplwi r0, 1
    beq _parse_sos_next
    li r3, -0x41
    b _parse_sos_return

_parse_sos_next:
    addi r31, r31, 1

_parse_sos_loop_condition:
    lbz r0, 0x180b(r28)
    cmpw r31, r0
    blt _parse_sos_loop
    mr r4, r28
    li r3, 3
    bl TMCJPEGDEC_move_ptr
    srawi r0, r3, 0x1f
    and r3, r3, r0

_parse_sos_return:
    lmw r27, 0x1c(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}
#else
static s32 TMCJPEGDEC_parse_sos(TMCCJPEGDecWork* work) {
    s32 idx;
    u8* compPtr;
    TMCUnknownInfo* scalePtr;
    u8* mapPtr;

    s32 dcTbl;
    s32 acTbl;

    u16 len;
    s32 r;
    s32 moveResult;
    s32 ci;
    u8 scanByte;

    compPtr = (u8*)work->compMap;
    scalePtr = (TMCUnknownInfo*)&work->scaleFlag;

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

    if (scanByte > 4 || scanByte != work->compCount) {
        return -0x51;
    }

    work->scanCompCount = scanByte;

    for (idx = 0; idx < (s32)work->scanCompCount; idx++) {
        r = TMCJPEGDEC_get_byte(&scanByte, work);
        if (r < 0) {
            return r;
        }

        for (ci = 0; ci < (s32)work->compCount; ci++) {
            if ((s32)compPtr[ci + 0x14] == (s32)scanByte) {
                compPtr[idx] = ci;
                mapPtr = compPtr + idx;
                break;
            }
        }

        // TODO: This isn't right...
        if (ci >= (s32)work->compCount) {
            return -0x51;
        }

        r = TMCJPEGDEC_get_byte(&scanByte, work);
        if (r < 0) {
            return r;
        }

        dcTbl = scanByte >> 4;
        acTbl = scanByte & 0xF;

        if (dcTbl > 1 || acTbl > 1) {
            return -0x51;
        }

        compPtr[*mapPtr + 0x1c] = dcTbl;
        compPtr[*mapPtr + 0x20] = acTbl;

        if (scalePtr->dcTblFlag[dcTbl] != 1) {
            return -0x40;
        }

        if (scalePtr->acTblFlag[acTbl] != 1) {
            return -0x40;
        }

        if (scalePtr->quantTblFlag[mapPtr[0x18]] != 1) {
            return -0x41;
        }
    }

    moveResult = TMCJPEGDEC_move_ptr(3, work);
    return moveResult & (moveResult >> 31);
}
#endif

s32 TMCJPEGDEC_err_restart(TMCCJPEGDecWork* work) {
    TMCCJPEGDecState* state;

    u16 interval;
    u16 pitch;
    u32 val;
    s32 rem;
    s32 div;
    s32 next;

    u8 rstDiff;
    u8 byte;
    s32 r;

    state = work->pState;

    if (work->scanCount == 1) {
        state->decodeResult = 0;
        return 0;
    }

    r = TMCJPEGDEC_rewind_ptr(work);
    if (r < 0) {
        return r;
    }

    byte = *work->pBufCur;

    while (TRUE) {
        while (byte != 0xFF) {
            r = TMCJPEGDEC_get_byte(&byte, work);
            if (r < 0) {
                return r;
            }
        }

        r = TMCJPEGDEC_get_byte(&byte, work);

        if (byte == 0xD9) {
            if (r < 0 && r != TMCC_ERROR_UNDERFLOW) {
                return r;
            }
            return 0;
        }

        if (r < 0) {
            return r;
        }

        if (byte < 0xD0 || byte > 0xD7) {
            continue;
        }

        if (byte > work->rstMarkerIdx + 0xCF) {
            rstDiff = byte - (work->rstMarkerIdx + 0xCF);
        } else {
            rstDiff = (byte + 0x08) - (work->rstMarkerIdx + 0xCF);
        }

        work->rstMarkerIdx = (byte + 1) & 7;
        interval = work->restartInterval;
        pitch = state->maxX;
        val = work->mcuPos;

        work->dcPredict[0] = 0;
        work->dcPredict[1] = 0;
        work->dcPredict[2] = 0;
        work->dcPredict[3] = 0;
        work->restartCnt = 0;

        next = (u8)(val & 0xFF) * (s32)pitch + (val >> 16) + (s32)(u8)(rstDiff * interval);
        div = next / (s32)pitch;
        rem = next - div * (s32)pitch;
        work->mcuPos = (rem << 16) + (u16)div;

        r = TMCJPEGDEC_init_buff(work);
        if (r < 0) {
            return r;
        }

        state->posX = rem;
        state->posY = div;
        state->position = TMCJPEGDEC_get_position(work);

        return state->result - (state->posY * state->maxX) - state->posY;
    }
}

void TMCJPEGDEC_set_entropytbl(TMCCJPEGDecWork* work, s32 idx, u8 data) {
    switch (idx) {
        case 0: {
            work->pDCACPtrs[0] = &work->zigzagData[8];
            work->pDCACPtrs[2] = work->maxCodeDC0;
            work->pDCACPtrs[1] = work->valPtrDC0;
            break;
        }
        case 1: {
            work->pDCACPtrs[0] = work->huffDecTblDC1;
            work->pDCACPtrs[2] = work->maxCodeDC1;
            work->pDCACPtrs[1] = work->valPtrDC1;
            break;
        }
    }

    if ((s32)data == 1) {
        goto ac1;
    }
    if ((s32)data < 1 && (s32)data >= 0) {
        work->pDCACPtrs[4] = work->huffDecTblAC0;
        *(void**)work->zigzagData = work->maxCodeAC0;
        work->pDCACPtrs[5] = work->valPtrAC0;
    }
    return;

ac1:
    work->pDCACPtrs[4] = work->huffDecTblAC1;
    *(void**)work->zigzagData = work->maxCodeAC1;
    work->pDCACPtrs[5] = work->valPtrAC1;
}
