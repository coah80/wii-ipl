#define TMC_JPEG_PLANAR_OUTPUT
#include <tmc_jpeg_internal.h>

static void TMCJPEGDEC_converterYUV411toY8U8V8(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV411toY8U8V8edge(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV422toY8U8V8(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV422toY8U8V8edge(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV420toY8U8V8(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV420toY8U8V8edge(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV211toY8U8V8(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV211toY8U8V8edge(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV444toY8U8V8(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV444toY8U8V8edge(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV400toY8U8V8(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV400toY8U8V8edge(TMCCJPEGDecWork*, s32, s32);

s32 TMCJPEGDEC_set_converterY8U8V8(TMCCJPEGDecWork* work) {
    u8* buffer;
    s32 componentCount;
    TMCCJPEGDecState* state;

    buffer = work->convBuf;
    componentCount = work->componentCount;
    state = work->pState;

    switch (componentCount) {
        case 0: {
            u8 mode;
            u8* firstRow;
            u8* secondRow;
            u8* thirdRow;
            u8* fourthRow;
            u8* cbBlock;
            u8* crBlock;

            mode = work->idctMode;
            firstRow = buffer + 4;
            work->pConverterFunc = TMCJPEGDEC_converterYUV411toY8U8V8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV411toY8U8V8edge;
            secondRow = firstRow + mode;
            thirdRow = secondRow + mode;
            fourthRow = thirdRow + mode;
            cbBlock = buffer + 260;
            crBlock = buffer + 324;
            work->pConvRowPtrs[0] = firstRow;
            work->pConvRowPtrs[1] = secondRow;
            work->pConvRowPtrs[2] = thirdRow;
            work->pConvRowPtrs[3] = fourthRow;
            work->pConvRowPtrs[5] = cbBlock;
            work->pConvRowPtrs[6] = crBlock;
            work->pitch = 32;
            work->converterFlags = 0;
            break;
        }
        case 1: {
            u8 mode;
            u8* firstRow;
            u8* secondRow;
            u8* cbBlock;
            u8* crBlock;

            mode = work->idctMode;
            firstRow = buffer + 4;
            work->pConverterFunc = TMCJPEGDEC_converterYUV422toY8U8V8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV422toY8U8V8edge;
            secondRow = firstRow + mode;
            cbBlock = buffer + 132;
            crBlock = buffer + 196;
            work->pConvRowPtrs[0] = firstRow;
            work->pConvRowPtrs[1] = secondRow;
            work->pConvRowPtrs[5] = cbBlock;
            work->pConvRowPtrs[6] = crBlock;
            work->pitch = 16;
            work->converterFlags = 0;
            break;
        }
        case 2: {
            u8 mode;
            u8* firstRow;
            u8* secondRow;
            u8* thirdRow;
            u8* fourthRow;
            u8* cbBlock;
            u8* crBlock;

            mode = work->idctMode;
            firstRow = buffer + 4;
            work->pConverterFunc = TMCJPEGDEC_converterYUV420toY8U8V8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV420toY8U8V8edge;
            secondRow = firstRow + mode;
            thirdRow = firstRow + mode * 16;
            fourthRow = thirdRow + mode;
            cbBlock = buffer + 260;
            crBlock = buffer + 324;
            work->pConvRowPtrs[0] = firstRow;
            work->pConvRowPtrs[1] = secondRow;
            work->pConvRowPtrs[2] = thirdRow;
            work->pConvRowPtrs[3] = fourthRow;
            work->pConvRowPtrs[5] = cbBlock;
            work->pConvRowPtrs[6] = crBlock;
            work->pitch = 16;
            work->converterFlags = 0;
            break;
        }
        case 3: {
            u8 mode;
            u8* firstRow;
            u8* secondRow;
            u8* cbBlock;
            u8* crBlock;

            mode = work->idctMode;
            firstRow = buffer + 4;
            work->pConverterFunc = TMCJPEGDEC_converterYUV211toY8U8V8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV211toY8U8V8edge;
            secondRow = firstRow + mode * 8;
            cbBlock = buffer + 132;
            crBlock = buffer + 196;
            work->pConvRowPtrs[0] = firstRow;
            work->pConvRowPtrs[1] = secondRow;
            work->pConvRowPtrs[5] = cbBlock;
            work->pConvRowPtrs[6] = crBlock;
            work->pitch = 8;
            work->converterFlags = 0;
            break;
        }
        case 4: {
            TMCConverterFunc* converter;
            TMCConverterFunc* edgeConverter;
            converter = TMCJPEGDEC_converterYUV444toY8U8V8;
            edgeConverter = TMCJPEGDEC_converterYUV444toY8U8V8edge;
            work->pConvRowPtrs[0] = buffer + 4;
            work->pConvRowPtrs[5] = buffer + 0x44;
            work->pConvRowPtrs[6] = buffer + 0x84;
            work->pConverterFunc = converter;
            work->pConverterFuncEdge = edgeConverter;
            work->pitch = 0x08;
            work->converterFlags = 0;
            break;
        }
        case 5: {
            TMCConverterFunc* converter;
            TMCConverterFunc* edgeConverter;
            converter = TMCJPEGDEC_converterYUV400toY8U8V8;
            edgeConverter = TMCJPEGDEC_converterYUV400toY8U8V8edge;
            work->pConvRowPtrs[0] = buffer + 4;
            work->pConverterFunc = converter;
            work->pConverterFuncEdge = edgeConverter;
            work->pitch = 0x08;
            work->converterFlags = 0;
            break;
        }
        default: {
            return TMCC_ERROR_FORMAT;
        }
    }

    {
        s32 width = state->jpegWidth;
        s32 height = state->jpegHeight;
        state->convWidth = ((u32)width / 8 + (width % 8 != 0)) * 8;
        state->convHeight = ((u32)height / 4 + (height % 4 != 0)) * 4;
        width = state->outputWidth;
        height = state->outputHeight;
        state->chromaWidth = ((u32)width / 8 + (width % 8 != 0)) * 8;
        state->chromaHeight = ((u32)height / 4 + (height % 4 != 0)) * 4;
    }
    return 0;
}

static void TMCJPEGDEC_converterYUV411toY8U8V8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 rowSkip;
    u8* output;
    u32 tileRow;
    s32 chromaYEnd;
    u8* lumaTexture;
    TMCCJPEGDecState* state;
    u8* luminance;
    s32 column;
    s32 row;
    u8* cbTexture;
    s32 xEnd;
    s32 height;
    u8* crTexture;
    s32 yEnd;
    u8* cb;
    u8* cr;
    u32 tileWidth;
    s32 width;

    row = y;
    luminance = work->convBuf + 4;
    cb = &work->convBuf[260];
    cr = &work->convBuf[324];
    state = work->pState;
    tileWidth = state->convWidth >> 3;
    lumaTexture = state->pLumaBuffer;
    cbTexture = state->pCbBuffer;
    crTexture = state->pCrBuffer;
    width = 32 / state->scaleFactor;
    height = 8 / state->scaleFactor;
    xEnd = x + width;
    yEnd = y + height;
    rowSkip = 32 - width;
    for (; row < yEnd; row++) {
        output = lumaTexture + ((row & 3) << 3);
        tileRow = (row >> 2) * tileWidth;
        for (column = x; column < xEnd; column += 4) {
            (output + (column & 7))[(s32)(((column >> 3) + tileRow) << 5)] = luminance[0];
            (output + ((column + 1) & 7))[(s32)((((column + 1) >> 3) + tileRow) << 5)] = luminance[1];
            (output + ((column + 2) & 7))[(s32)((((column + 2) >> 3) + tileRow) << 5)] = luminance[2];
            (output + ((column + 3) & 7))[(s32)((((column + 3) >> 3) + tileRow) << 5)] = luminance[3];
            luminance += 4;
        }
        luminance += rowSkip;
    }
    tileWidth = state->chromaWidth >> 3;
    x = (u32)x >> 2;
    width = 8 / state->scaleFactor;
    height = 8 / state->scaleFactor;
    xEnd = x + width;
    chromaYEnd = y + height;
    for (; y < chromaYEnd; y++) {
        for (column = x; column < xEnd; column += 1) {
            (cbTexture + ((y & 3) << 3) + (column & 7))[(s32)(((column >> 3) + (y >> 2) * tileWidth) << 5)] = *cb + 128;
            cb++;
            (crTexture + ((y & 3) << 3) + (column & 7))[(s32)(((column >> 3) + (y >> 2) * tileWidth) << 5)] = *cr + 128;
            cr++;
        }
        cb += 8 - width;
        cr += 8 - width;
    }
}

static void TMCJPEGDEC_converterYUV411toY8U8V8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* state;
    u8* lumaTexture;
    u8* luminance;
    s32 column;
    s32 row;
    s32 chromaEnd;
    u8* cbTexture;
    u8* crTexture;
    u32 tileRow;
    s32 height;
    s32 yEnd;
    u8* output;
    u8* cb;
    u8* cr;
    s32 width;
    s32 tileOffset;
    s32 xEnd;
    u32 tileWidth;

    luminance = work->convBuf + 4;
    cb = &work->convBuf[260];
    cr = &work->convBuf[324];
    state = work->pState;
    tileWidth = state->convWidth >> 3;
    lumaTexture = state->pLumaBuffer;
    cbTexture = state->pCbBuffer;
    crTexture = state->pCrBuffer;
    if (state->dataSizeX == (u32)x) {
        width = state->stepXExt;
    } else {
        width = 32 / state->scaleFactor;
    }
    if (state->dataSizeY == (u32)y) {
        height = state->stepYExt;
    } else {
        height = 8 / state->scaleFactor;
    }
    xEnd = x + width;
    yEnd = y + height;
    for (row = y; row < yEnd; row++) {
        for (column = x; column < xEnd; column += 1) {
            tileRow = (row >> 2) * tileWidth;
            tileOffset = ((column >> 3) + tileRow) << 5;
            output = lumaTexture + ((row & 3) << 3) + (column & 7);
            output[tileOffset] = *luminance++;
        }
        luminance += 32 - width;
    }
    x = (u32)x >> 2;
    width = (width + 3) >> 2;
    xEnd = x + width;
    tileWidth = state->chromaWidth >> 3;
    chromaEnd = y + height;
    for (; y < chromaEnd; y++) {
        for (column = x; column < xEnd; column += 1) {
            (cbTexture + ((y & 3) << 3) + (column & 7))[(s32)(((column >> 3) + (y >> 2) * tileWidth) << 5)] = *cb + 128;
            cb++;
            (crTexture + ((y & 3) << 3) + (column & 7))[(s32)(((column >> 3) + (y >> 2) * tileWidth) << 5)] = *cr + 128;
            cr++;
        }
        cb += 8 - width;
        cr += 8 - width;
    }
}

static void TMCJPEGDEC_converterYUV422toY8U8V8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 chromaYEnd;
    u8* lumaTexture;
    u8* luminance;
    s32 column;
    s32 chromaXEnd;
    s32 row;
    u32 chromaTileWidth;
    TMCCJPEGDecState* state;
    s32 width;
    s32 height;
    u8* cbTexture;
    s32 xEnd;
    u8* crTexture;
    s32 yEnd;
    u8* cb;
    u32 tileWidth;
    u8* cr;
    s32 chromaRowSkip;

    row = y;
    luminance = work->convBuf + 4;
    cb = &work->convBuf[132];
    cr = &work->convBuf[196];
    state = work->pState;
    tileWidth = state->convWidth >> 3;
    lumaTexture = state->pLumaBuffer;
    cbTexture = state->pCbBuffer;
    crTexture = state->pCrBuffer;
    width = 16 / state->scaleFactor;
    height = 8 / state->scaleFactor;
    xEnd = x + width;
    yEnd = y + height;
    for (; row < yEnd; row++) {
        for (column = x; column < xEnd; column += 2) {
            (lumaTexture + ((row & 3) << 3) + (column & 7))[(s32)(((column >> 3) + (row >> 2) * tileWidth) << 5)] = *luminance++;
            (lumaTexture + ((row & 3) << 3) + ((column + 1) & 7))[(s32)((((column + 1) >> 3) + (row >> 2) * tileWidth) << 5)] = *luminance++;
        }
        luminance += 16 - width;
    }
    x = (u32)x >> 1;
    width = 8 / state->scaleFactor;
    height = 8 / state->scaleFactor;
    chromaXEnd = x + width;
    chromaYEnd = y + height;
    chromaTileWidth = state->chromaWidth >> 3;
    chromaRowSkip = 8 - width;
    for (; y < chromaYEnd; y++) {
        for (column = x; column < chromaXEnd; column += 1) {
            (cbTexture + ((y & 3) << 3) + (column & 7))[(s32)(((column >> 3) + (y >> 2) * chromaTileWidth) << 5)] = *cb + 128;
            cb++;
            (crTexture + ((y & 3) << 3) + (column & 7))[(s32)(((column >> 3) + (y >> 2) * chromaTileWidth) << 5)] = *cr + 128;
            cr++;
        }
        cb += chromaRowSkip;
        cr += 8 - width;
    }
}

static void TMCJPEGDEC_converterYUV422toY8U8V8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* state;
    u8* lumaTexture;
    u8* luminance;
    s32 column;
    s32 row;
    s32 chromaEnd;
    u8* cbTexture;
    u8* crTexture;
    u32 tileRow;
    s32 height;
    s32 yEnd;
    u8* output;
    u8* cb;
    u8* cr;
    s32 width;
    s32 tileOffset;
    s32 xEnd;
    u32 tileWidth;

    luminance = work->convBuf + 4;
    cb = &work->convBuf[132];
    cr = &work->convBuf[196];
    state = work->pState;
    tileWidth = state->convWidth >> 3;
    lumaTexture = state->pLumaBuffer;
    cbTexture = state->pCbBuffer;
    crTexture = state->pCrBuffer;
    if (state->dataSizeX == (u32)x) {
        width = state->stepXExt;
    } else {
        width = 16 / state->scaleFactor;
    }
    if (state->dataSizeY == (u32)y) {
        height = state->stepYExt;
    } else {
        height = 8 / state->scaleFactor;
    }
    xEnd = x + width;
    yEnd = y + height;
    for (row = y; row < yEnd; row++) {
        for (column = x; column < xEnd; column += 1) {
            tileRow = (row >> 2) * tileWidth;
            tileOffset = ((column >> 3) + tileRow) << 5;
            output = lumaTexture + ((row & 3) << 3) + (column & 7);
            output[tileOffset] = *luminance++;
        }
        luminance += 16 - width;
    }
    x = (u32)x >> 1;
    width = (width + 1) >> 1;
    xEnd = x + width;
    tileWidth = state->chromaWidth >> 3;
    chromaEnd = y + height;
    for (; y < chromaEnd; y++) {
        for (column = x; column < xEnd; column += 1) {
            (cbTexture + ((y & 3) << 3) + (column & 7))[(s32)(((column >> 3) + (y >> 2) * tileWidth) << 5)] = *cb + 128;
            cb++;
            (crTexture + ((y & 3) << 3) + (column & 7))[(s32)(((column >> 3) + (y >> 2) * tileWidth) << 5)] = *cr + 128;
            cr++;
        }
        cb += 8 - width;
        cr += 8 - width;
    }
}

static void TMCJPEGDEC_converterYUV420toY8U8V8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 chromaYEnd;
    u8* lumaTexture;
    s32 height;
    u8* luminance;
    s32 column;
    u8* cbTexture;
    s32 row;
    u8* crTexture;
    s32 xEnd;
    u8* cb;
    TMCCJPEGDecState* state;
    s32 yEnd;
    s32 width;
    u8* cr;
    u32 tileWidth;

    row = y;
    luminance = work->convBuf + 4;
    cb = &work->convBuf[260];
    cr = &work->convBuf[324];
    state = work->pState;
    tileWidth = state->convWidth >> 3;
    lumaTexture = state->pLumaBuffer;
    cbTexture = state->pCbBuffer;
    crTexture = state->pCrBuffer;
    width = 16 / state->scaleFactor;
    height = 16 / state->scaleFactor;
    xEnd = x + width;
    yEnd = y + height;
    for (; row < yEnd; row++) {
        for (column = x; column < xEnd; column += 2) {
            (lumaTexture + ((row & 3) << 3) + (column & 7))[(s32)(((column >> 3) + (row >> 2) * tileWidth) << 5)] = *luminance++;
            (lumaTexture + ((row & 3) << 3) + ((column + 1) & 7))[(s32)((((column + 1) >> 3) + (row >> 2) * tileWidth) << 5)] = *luminance++;
        }
        luminance += 16 - width;
    }
    x = (u32)x >> 1;
    y = (u32)y >> 1;
    width = 8 / state->scaleFactor;
    height = 8 / state->scaleFactor;
    xEnd = x + width;
    chromaYEnd = y + height;
    tileWidth = state->chromaWidth >> 3;
    for (; y < chromaYEnd; y++) {
        for (column = x; column < xEnd; column += 1) {
            (cbTexture + ((y & 3) << 3) + (column & 7))[(s32)(((column >> 3) + (y >> 2) * tileWidth) << 5)] = *cb + 128;
            cb++;
            (crTexture + ((y & 3) << 3) + (column & 7))[(s32)(((column >> 3) + (y >> 2) * tileWidth) << 5)] = *cr + 128;
            cr++;
        }
        cb += 8 - width;
        cr += 8 - width;
    }
}

static void TMCJPEGDEC_converterYUV420toY8U8V8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* state;
    u8* lumaTexture;
    u8* luminance;
    s32 column;
    s32 row;
    s32 chromaEnd;
    u8* cbTexture;
    u8* crTexture;
    u32 tileRow;
    s32 height;
    s32 width;
    u8* output;
    u8* cb;
    u8* cr;
    s32 xEnd;
    s32 tileOffset;
    s32 yEnd;
    u32 tileWidth;

    luminance = work->convBuf + 4;
    cb = &work->convBuf[260];
    cr = &work->convBuf[324];
    state = work->pState;
    tileWidth = state->convWidth >> 3;
    lumaTexture = state->pLumaBuffer;
    cbTexture = state->pCbBuffer;
    crTexture = state->pCrBuffer;
    if (state->dataSizeX == (u32)x) {
        width = state->stepXExt;
    } else {
        width = 16 / state->scaleFactor;
    }
    if (state->dataSizeY == (u32)y) {
        height = state->stepYExt;
    } else {
        height = 16 / state->scaleFactor;
    }
    xEnd = x + width;
    yEnd = y + height;
    for (row = y; row < yEnd; row++) {
        for (column = x; column < xEnd; column += 1) {
            tileRow = (row >> 2) * tileWidth;
            tileOffset = ((column >> 3) + tileRow) << 5;
            output = lumaTexture + ((row & 3) << 3) + (column & 7);
            output[tileOffset] = *luminance++;
        }
        luminance += 16 - width;
    }
    y = (u32)y >> 1;
    x = (u32)x >> 1;
    width = (width + 1) >> 1;
    xEnd = x + width;
    tileWidth = state->chromaWidth >> 3;
    chromaEnd = y + ((height + 1) >> 1);
    for (; y < chromaEnd; y++) {
        for (column = x; column < xEnd; column += 1) {
            (cbTexture + ((y & 3) << 3) + (column & 7))[(s32)(((column >> 3) + (y >> 2) * tileWidth) << 5)] = *cb + 128;
            cb++;
            (crTexture + ((y & 3) << 3) + (column & 7))[(s32)(((column >> 3) + (y >> 2) * tileWidth) << 5)] = *cr + 128;
            cr++;
        }
        cb += 8 - width;
        cr += 8 - width;
    }
}

static void TMCJPEGDEC_converterYUV211toY8U8V8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    u8* lumaTexture;
    TMCCJPEGDecState* state;
    u8* luminance;
    s32 column;
    s32 row;
    s32 chromaEnd;
    u8* cbTexture;
    u8* crTexture;
    u32 tileRow;
    s32 height;
    s32 yEnd;
    u8* output;
    u8* cb;
    u8* cr;
    s32 xEnd;
    s32 tileOffset;
    s32 width;
    u32 tileWidth;

    luminance = work->convBuf + 4;
    cb = &work->convBuf[132];
    cr = &work->convBuf[196];
    state = work->pState;
    tileWidth = state->convWidth >> 3;
    lumaTexture = state->pLumaBuffer;
    cbTexture = state->pCbBuffer;
    crTexture = state->pCrBuffer;
    width = 8 / state->scaleFactor;
    height = 16 / state->scaleFactor;
    xEnd = x + width;
    yEnd = y + height;
    for (row = y; row < yEnd; row++) {
        for (column = x; column < xEnd; column += 1) {
            tileRow = (row >> 2) * tileWidth;
            tileOffset = ((column >> 3) + tileRow) << 5;
            output = lumaTexture + ((row & 3) << 3) + (column & 7);
            output[tileOffset] = *luminance++;
        }
        luminance += 8 - width;
    }
    y = (u32)y >> 1;
    tileWidth = state->chromaWidth >> 3;
    chromaEnd = y + 8 / state->scaleFactor;
    for (; y < chromaEnd; y++) {
        for (column = x; column < xEnd; column += 1) {
            (cbTexture + ((y & 3) << 3) + (column & 7))[(s32)(((column >> 3) + (y >> 2) * tileWidth) << 5)] = *cb + 128;
            cb++;
            (crTexture + ((y & 3) << 3) + (column & 7))[(s32)(((column >> 3) + (y >> 2) * tileWidth) << 5)] = *cr + 128;
            cr++;
        }
        cb += 8 - width;
        cr += 8 - width;
    }
}

static void TMCJPEGDEC_converterYUV211toY8U8V8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    u32 chromaTileWidth;
    TMCCJPEGDecState* state;
    u8* lumaTexture;
    u8* luminance;
    s32 column;
    s32 row;
    s32 chromaEnd;
    u8* cbTexture;
    u8* crTexture;
    u32 tileRow;
    s32 height;
    s32 yEnd;
    u8* output;
    u8* cb;
    u8* cr;
    s32 xEnd;
    s32 tileOffset;
    s32 width;
    u32 tileWidth;

    luminance = work->convBuf + 4;
    cb = &work->convBuf[132];
    cr = &work->convBuf[196];
    state = work->pState;
    tileWidth = state->convWidth >> 3;
    lumaTexture = state->pLumaBuffer;
    cbTexture = state->pCbBuffer;
    crTexture = state->pCrBuffer;
    if (state->dataSizeX == (u32)x) {
        width = state->stepXExt;
    } else {
        width = 8 / state->scaleFactor;
    }
    if (state->dataSizeY == (u32)y) {
        height = state->stepYExt;
    } else {
        height = 16 / state->scaleFactor;
    }
    xEnd = x + width;
    yEnd = y + height;
    for (row = y; row < yEnd; row++) {
        for (column = x; column < xEnd; column += 1) {
            tileRow = (row >> 2) * tileWidth;
            tileOffset = ((column >> 3) + tileRow) << 5;
            output = lumaTexture + ((row & 3) << 3) + (column & 7);
            output[tileOffset] = *luminance++;
        }
        luminance += 8 - width;
    }
    y = (u32)y >> 1;
    chromaTileWidth = state->chromaWidth >> 3;
    chromaEnd = y + ((height + 1) >> 1);
    for (; y < chromaEnd; y++) {
        for (column = x; column < xEnd; column += 1) {
            (cbTexture + ((y & 3) << 3) + (column & 7))[(s32)(((column >> 3) + (y >> 2) * chromaTileWidth) << 5)] = *cb + 128;
            cb++;
            (crTexture + ((y & 3) << 3) + (column & 7))[(s32)(((column >> 3) + (y >> 2) * chromaTileWidth) << 5)] = *cr + 128;
            cr++;
        }
        cb += 8 - width;
        cr += 8 - width;
    }
}

static void TMCJPEGDEC_converterYUV444toY8U8V8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 rowSkip;
    u8* output;
    s32 height;
    s32 tileRow;
    u8* cbOutput;
    TMCCJPEGDecState* state;
    u8* crOutput;
    s32 pixelOffset;
    s32 tileOffset;
    u8* lumaTexture;
    s32 width;
    u32 rowOffset;
    u8* cbTexture;
    u8* crTexture;
    u8* luminance;
    u8* cb;
    u8* cr;
    s32 column;
    s32 xEnd;
    s32 yEnd;
    u32 tileWidth;

    luminance = work->convBuf + 4;
    cb = &work->convBuf[68];
    cr = &work->convBuf[132];
    state = work->pState;
    tileWidth = state->convWidth >> 3;
    lumaTexture = state->pLumaBuffer;
    cbTexture = state->pCbBuffer;
    crTexture = state->pCrBuffer;
    width = 8 / state->scaleFactor;
    height = 8 / state->scaleFactor;
    xEnd = x + width;
    yEnd = y + height;
    rowSkip = 8 - width;
    for (; y < yEnd; y++) {
        tileRow = (y >> 2) * tileWidth;
        rowOffset = (y & 3) << 3;
        output = lumaTexture + rowOffset;
        cbOutput = cbTexture + rowOffset;
        crOutput = crTexture + rowOffset;
        for (column = x; column < xEnd;) {
            tileOffset = ((column >> 3) + tileRow) << 5;
            pixelOffset = column++ & 7;
            (output + pixelOffset)[tileOffset] = *luminance++;
            (cbOutput + pixelOffset)[tileOffset] = *cb++ + 128;
            (crOutput + pixelOffset)[tileOffset] = *cr++ + 128;
        }
        luminance += rowSkip;
        cb += rowSkip;
        cr += rowSkip;
    }
}

static void TMCJPEGDEC_converterYUV444toY8U8V8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 rowSkip;
    u8* output;
    s32 height;
    s32 tileRow;
    u8* cbOutput;
    TMCCJPEGDecState* state;
    u8* crOutput;
    s32 pixelOffset;
    s32 tileOffset;
    u8* lumaTexture;
    s32 width;
    u32 rowOffset;
    u8* cbTexture;
    u8* crTexture;
    u8* luminance;
    u8* cb;
    u8* cr;
    s32 column;
    s32 xEnd;
    s32 yEnd;
    u32 tileWidth;

    luminance = work->convBuf + 4;
    cb = &work->convBuf[68];
    cr = &work->convBuf[132];
    state = work->pState;
    tileWidth = state->convWidth >> 3;
    lumaTexture = state->pLumaBuffer;
    cbTexture = state->pCbBuffer;
    crTexture = state->pCrBuffer;
    if (state->dataSizeX == (u32)x) {
        width = state->stepXExt;
    } else {
        width = 8 / state->scaleFactor;
    }
    if (state->dataSizeY == (u32)y) {
        height = state->stepYExt;
    } else {
        height = 8 / state->scaleFactor;
    }
    xEnd = x + width;
    yEnd = y + height;
    rowSkip = 8 - width;
    for (; y < yEnd; y++) {
        tileRow = (y >> 2) * tileWidth;
        rowOffset = (y & 3) << 3;
        output = lumaTexture + rowOffset;
        cbOutput = cbTexture + rowOffset;
        crOutput = crTexture + rowOffset;
        for (column = x; column < xEnd;) {
            tileOffset = ((column >> 3) + tileRow) << 5;
            pixelOffset = column++ & 7;
            (output + pixelOffset)[tileOffset] = *luminance++;
            (cbOutput + pixelOffset)[tileOffset] = *cb++ + 128;
            (crOutput + pixelOffset)[tileOffset] = *cr++ + 128;
        }
        luminance += rowSkip;
        cb += rowSkip;
        cr += rowSkip;
    }
}

static void TMCJPEGDEC_converterYUV400toY8U8V8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 height;
    u8* lumaTexture;
    u8* luminance;
    s32 column;
    s32 xEnd;
    s32 yEnd;
    u8* output;
    s32 width;
    TMCCJPEGDecState* state;
    u32 tileRow;
    u32 tileWidth;
    s32 tileOffset;
    s32 row;

    luminance = work->convBuf + 4;
    state = work->pState;
    tileWidth = state->convWidth >> 3;
    lumaTexture = state->pLumaBuffer;
    width = 8 / state->scaleFactor;
    height = 8 / state->scaleFactor;
    {
        xEnd = x + width;
        yEnd = y + height;
        for (row = y; row < yEnd; row++) {
            for (column = x; column < xEnd; column += 1) {
                tileRow = (row >> 2) * tileWidth;
                tileOffset = ((column >> 3) + tileRow) << 5;
                output = lumaTexture + ((row & 3) << 3) + (column & 7);
                output[tileOffset] = *luminance++;
            }
            luminance += 8 - width;
        }
    }
}

static void TMCJPEGDEC_converterYUV400toY8U8V8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 height;
    u8* lumaTexture;
    u8* luminance;
    s32 column;
    s32 xEnd;
    s32 yEnd;
    u8* output;
    s32 width;
    TMCCJPEGDecState* state;
    u32 tileRow;
    u32 tileWidth;
    s32 tileOffset;
    s32 row;

    luminance = work->convBuf + 4;
    state = work->pState;
    tileWidth = state->convWidth >> 3;
    lumaTexture = state->pLumaBuffer;
    if (state->dataSizeX == (u32)x) {
        width = state->stepXExt;
    } else {
        width = 8 / state->scaleFactor;
    }
    if (state->dataSizeY == (u32)y) {
        height = state->stepYExt;
    } else {
        height = 8 / state->scaleFactor;
    }
    {
        xEnd = x + width;
        yEnd = y + height;
        for (row = y; row < yEnd; row++) {
            for (column = x; column < xEnd; column += 1) {
                tileRow = (row >> 2) * tileWidth;
                tileOffset = ((column >> 3) + tileRow) << 5;
                output = lumaTexture + ((row & 3) << 3) + (column & 7);
                output[tileOffset] = *luminance++;
            }
            luminance += 8 - width;
        }
    }
}
