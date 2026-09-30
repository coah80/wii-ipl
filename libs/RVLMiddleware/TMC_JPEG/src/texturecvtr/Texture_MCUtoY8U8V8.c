#define TMC_JPEG_PLANAR_OUTPUT
#include <tmc_jpeg_internal.h>

static void TMCJPEG_814EFEAC(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEG_814F043C(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEG_814F0A58(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEG_814F11C4(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEG_814F17E0(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEG_814F1F48(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEG_814F2570(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEG_814F2B50(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEG_814F3158(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEG_814F32E4(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEG_814F34A4(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEG_814F372C(TMCCJPEGDecWork*, s32, s32);

s32 TMCJPEGDEC_set_converterY8U8V8(TMCCJPEGDecWork* work) {
    u8* ob;
    s32 cc;
    TMCCJPEGDecState* st;

    ob = (u8*)&work->convBuf;
    cc = work->componentCount;
    st = work->pState;

    switch (cc) {
        case 0: {
            u8 mode = work->idctMode;
            u8* ptr = ob + 4;
            u8* p1 = ptr + mode;
            u8* p2 = p1 + mode;
            u8* p3 = p2 + mode;

            work->pConverterFunc = TMCJPEG_814EFEAC;
            work->pConverterFuncEdge = TMCJPEG_814F043C;
            work->pConvRowPtrs[0] = (void*)ptr;
            work->pConvRowPtrs[1] = (void*)p1;
            work->pConvRowPtrs[2] = (void*)p2;
            work->pConvRowPtrs[3] = (void*)p3;
            work->pConvRowPtrs[5] = (void*)(ob + 0x104);
            work->pConvRowPtrs[6] = (void*)(ob + 0x144);
            work->pitch = 0x20;
            work->converterFlags = 0;
            break;
        }
        case 1: {
            u8 mode = work->idctMode;
            u8* ptr = ob + 4;
            work->pConverterFunc = TMCJPEG_814F0A58;
            work->pConverterFuncEdge = TMCJPEG_814F11C4;
            work->pConvRowPtrs[0] = (void*)ptr;
            work->pConvRowPtrs[1] = (void*)(ptr + mode);
            work->pConvRowPtrs[5] = (void*)(ob + 0x84);
            work->pConvRowPtrs[6] = (void*)(ob + 0xC4);
            work->pitch = 0x10;
            work->converterFlags = 0;
            break;
        }
        case 2: {
            u8 mode = work->idctMode;
            u8* ptr = ob + 4;
            u8* p1 = ptr + mode;
            u8* p2 = ptr + mode * 16;
            u8* p3 = p2 + mode;
            work->pConverterFunc = TMCJPEG_814F17E0;
            work->pConverterFuncEdge = TMCJPEG_814F1F48;
            work->pConvRowPtrs[0] = (void*)ptr;
            work->pConvRowPtrs[1] = (void*)p1;
            work->pConvRowPtrs[2] = (void*)p2;
            work->pConvRowPtrs[3] = (void*)p3;
            work->pConvRowPtrs[5] = (void*)(ob + 0x104);
            work->pConvRowPtrs[6] = (void*)(ob + 0x144);
            work->pitch = 0x10;
            work->converterFlags = 0;
            break;
        }
        case 3: {
            u8 mode = work->idctMode;
            u8* ptr = ob + 4;
            work->pConverterFunc = TMCJPEG_814F2570;
            work->pConverterFuncEdge = TMCJPEG_814F2B50;
            work->pConvRowPtrs[0] = (void*)ptr;
            work->pConvRowPtrs[1] = (void*)(ptr + mode * 8);
            work->pConvRowPtrs[5] = (void*)(ob + 0x84);
            work->pConvRowPtrs[6] = (void*)(ob + 0xC4);
            work->pitch = 0x08;
            work->converterFlags = 0;
            break;
        }
        case 4: {
            work->pConverterFunc = TMCJPEG_814F3158;
            work->pConverterFuncEdge = TMCJPEG_814F32E4;
            work->pConvRowPtrs[0] = (void*)(ob + 4);
            work->pConvRowPtrs[5] = (void*)(ob + 0x44);
            work->pConvRowPtrs[6] = (void*)(ob + 0x84);
            work->pitch = 0x08;
            work->converterFlags = 0;
            break;
        }
        case 5: {
            work->pConverterFunc = TMCJPEG_814F34A4;
            work->pConverterFuncEdge = TMCJPEG_814F372C;
            work->pConvRowPtrs[0] = (void*)(ob + 4);
            work->pitch = 0x08;
            work->converterFlags = 0;
            break;
        }
        default: {
            return TMCC_ERROR_FORMAT;
        }
    }

    {
        s32 width = st->jpegWidth;
        s32 height = st->jpegHeight;
        st->convWidth = ((u32)width / 8 + (width % 8 != 0)) * 8;
        st->convHeight = ((u32)height / 4 + (height % 4 != 0)) * 4;
        width = st->outputWidth;
        height = st->outputHeight;
        st->chromaWidth = ((u32)width / 8 + (width % 8 != 0)) * 8;
        st->chromaHeight = ((u32)height / 4 + (height % 4 != 0)) * 4;
    }
    return 0;
}

static void TMCJPEG_814EFEAC(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 column;
    u8* luminance = work->convBuf + 4;
    s8* cb = (s8*)&work->convBuf[260];
    s8* cr = (s8*)&work->convBuf[324];
    TMCCJPEGDecState* state = work->pState;
    u32 tileWidth = state->convWidth >> 3;
    u8* lumaTexture = state->pLumaBuffer;
    u8* cbTexture = state->pCbBuffer;
    u8* crTexture = state->pCrBuffer;
    s32 width, height;
    width = 32 / state->scaleFactor;
    height = 8 / state->scaleFactor;
    {
        s32 xEnd = x + width;
        s32 yEnd = y + height;
        s32 row;
        for (row = y; row < yEnd; row++) {
            u32 tileRow = (row >> 2) * tileWidth;
            u8* output = lumaTexture + ((row & 3) << 3);
            for (column = x; column < xEnd; column += 4) {
                output[((column) & 7) + ((((column) >> 3) + tileRow) << 5)] = luminance[0];
                output[((column + 1) & 7) + ((((column + 1) >> 3) + tileRow) << 5)] = luminance[1];
                output[((column + 2) & 7) + ((((column + 2) >> 3) + tileRow) << 5)] = luminance[2];
                output[((column + 3) & 7) + ((((column + 3) >> 3) + tileRow) << 5)] = luminance[3];
                luminance += 4;
            }
            luminance += 32 - width;
        }
        x = (u32)x >> 2;
        width = 8 / state->scaleFactor;
        height = 8 / state->scaleFactor;
        xEnd = x + width;
        yEnd = y + height;
        tileWidth = state->chromaWidth >> 3;
        for (; y < yEnd; y++) {
            for (column = x; column < xEnd; column++) {
                u32 tileRow = (y >> 2) * tileWidth;
                u8* cbOutput = cbTexture + ((y & 3) << 3);
                u8* crOutput = crTexture + ((y & 3) << 3);
                cbOutput[(column & 7) + (((column >> 3) + tileRow) << 5)] = *cb++ + 128;
                crOutput[(column & 7) + (((column >> 3) + tileRow) << 5)] = *cr++ + 128;
            }
            cb += 8 - width;
            cr += 8 - width;
        }
    }
}

static void TMCJPEG_814F043C(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 column;
    u8* luminance = work->convBuf + 4;
    s8* cb = (s8*)&work->convBuf[260];
    s8* cr = (s8*)&work->convBuf[324];
    TMCCJPEGDecState* state = work->pState;
    u32 tileWidth = state->convWidth >> 3;
    u8* lumaTexture = state->pLumaBuffer;
    u8* cbTexture = state->pCbBuffer;
    u8* crTexture = state->pCrBuffer;
    s32 width, height;
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
    {
        s32 xEnd = x + width;
        s32 yEnd = y + height;
        s32 row;
        for (row = y; row < yEnd; row++) {
            u32 tileRow = (row >> 2) * tileWidth;
            u8* output = lumaTexture + ((row & 3) << 3);
            for (column = x; column < xEnd; column += 1) {
                output[((column) & 7) + ((((column) >> 3) + tileRow) << 5)] = luminance[0];
                luminance += 1;
            }
            luminance += 32 - width;
        }
        x = (u32)x >> 2;
        width = (width + 3) >> 2;
        xEnd = x + width;
        yEnd = y + height;
        tileWidth = state->chromaWidth >> 3;
        for (; y < yEnd; y++) {
            u32 tileRow = (y >> 2) * tileWidth;
            u8* cbOutput = cbTexture + ((y & 3) << 3);
            u8* crOutput = crTexture + ((y & 3) << 3);
            for (column = x; column < xEnd; column++) {
                cbOutput[(column & 7) + (((column >> 3) + tileRow) << 5)] = *cb++ + 128;
                crOutput[(column & 7) + (((column >> 3) + tileRow) << 5)] = *cr++ + 128;
            }
            cb += 8 - width;
            cr += 8 - width;
        }
    }
}

static void TMCJPEG_814F0A58(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 column;
    u8* luminance = work->convBuf + 4;
    s8* cb = (s8*)&work->convBuf[132];
    s8* cr = (s8*)&work->convBuf[196];
    TMCCJPEGDecState* state = work->pState;
    u32 tileWidth = state->convWidth >> 3;
    u8* lumaTexture = state->pLumaBuffer;
    u8* cbTexture = state->pCbBuffer;
    u8* crTexture = state->pCrBuffer;
    s32 width, height;
    width = 16 / state->scaleFactor;
    height = 8 / state->scaleFactor;
    {
        s32 xEnd = x + width;
        s32 yEnd = y + height;
        s32 row;
        for (row = y; row < yEnd; row++) {
            u32 tileRow = (row >> 2) * tileWidth;
            u8* output = lumaTexture + ((row & 3) << 3);
            for (column = x; column < xEnd; column += 2) {
                output[((column) & 7) + ((((column) >> 3) + tileRow) << 5)] = luminance[0];
                output[((column + 1) & 7) + ((((column + 1) >> 3) + tileRow) << 5)] = luminance[1];
                luminance += 2;
            }
            luminance += 16 - width;
        }
        x = (u32)x >> 1;
        width = 8 / state->scaleFactor;
        height = 8 / state->scaleFactor;
        xEnd = x + width;
        yEnd = y + height;
        tileWidth = state->chromaWidth >> 3;
        for (; y < yEnd; y++) {
            u32 tileRow = (y >> 2) * tileWidth;
            u8* cbOutput = cbTexture + ((y & 3) << 3);
            u8* crOutput = crTexture + ((y & 3) << 3);
            for (column = x; column < xEnd; column++) {
                cbOutput[(column & 7) + (((column >> 3) + tileRow) << 5)] = *cb++ + 128;
                crOutput[(column & 7) + (((column >> 3) + tileRow) << 5)] = *cr++ + 128;
            }
            cb += 8 - width;
            cr += 8 - width;
        }
    }
}

static void TMCJPEG_814F11C4(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 column;
    u8* luminance = work->convBuf + 4;
    s8* cb = (s8*)&work->convBuf[132];
    s8* cr = (s8*)&work->convBuf[196];
    TMCCJPEGDecState* state = work->pState;
    u32 tileWidth = state->convWidth >> 3;
    u8* lumaTexture = state->pLumaBuffer;
    u8* cbTexture = state->pCbBuffer;
    u8* crTexture = state->pCrBuffer;
    s32 width, height;
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
    {
        s32 xEnd = x + width;
        s32 yEnd = y + height;
        s32 row;
        for (row = y; row < yEnd; row++) {
            u32 tileRow = (row >> 2) * tileWidth;
            u8* output = lumaTexture + ((row & 3) << 3);
            for (column = x; column < xEnd; column += 1) {
                output[((column) & 7) + ((((column) >> 3) + tileRow) << 5)] = luminance[0];
                luminance += 1;
            }
            luminance += 16 - width;
        }
        x = (u32)x >> 1;
        width = (width + 1) >> 1;
        xEnd = x + width;
        yEnd = y + height;
        tileWidth = state->chromaWidth >> 3;
        for (; y < yEnd; y++) {
            u32 tileRow = (y >> 2) * tileWidth;
            u8* cbOutput = cbTexture + ((y & 3) << 3);
            u8* crOutput = crTexture + ((y & 3) << 3);
            for (column = x; column < xEnd; column++) {
                cbOutput[(column & 7) + (((column >> 3) + tileRow) << 5)] = *cb++ + 128;
                crOutput[(column & 7) + (((column >> 3) + tileRow) << 5)] = *cr++ + 128;
            }
            cb += 8 - width;
            cr += 8 - width;
        }
    }
}

static void TMCJPEG_814F17E0(TMCCJPEGDecWork* work, s32 x, s32 y) {
    u8* luminance = work->convBuf + 4;
    s8* cb = (s8*)&work->convBuf[260];
    s8* cr = (s8*)&work->convBuf[324];
    TMCCJPEGDecState* state = work->pState;
    u32 tileWidth = state->convWidth >> 3;
    u8* lumaTexture = state->pLumaBuffer;
    u8* cbTexture = state->pCbBuffer;
    u8* crTexture = state->pCrBuffer;
    s32 width, height;
    width = 16 / state->scaleFactor;
    height = 16 / state->scaleFactor;
    {
        s32 xEnd = x + width;
        s32 yEnd = y + height;
        s32 row;
        for (row = y; row < yEnd; row++) {
            u32 tileRow = (row >> 2) * tileWidth;
            u8* output = lumaTexture + ((row & 3) << 3);
            s32 column;
            for (column = x; column < xEnd; column += 2) {
                output[((column) & 7) + ((((column) >> 3) + tileRow) << 5)] = luminance[0];
                output[((column + 1) & 7) + ((((column + 1) >> 3) + tileRow) << 5)] = luminance[1];
                luminance += 2;
            }
            luminance += 16 - width;
        }
        x = (u32)x >> 1;
        y = (u32)y >> 1;
        width = 8 / state->scaleFactor;
        height = 8 / state->scaleFactor;
        xEnd = x + width;
        yEnd = y + height;
        tileWidth = state->chromaWidth >> 3;
        for (; y < yEnd; y++) {
            u32 tileRow = (y >> 2) * tileWidth;
            u8* cbOutput = cbTexture + ((y & 3) << 3);
            u8* crOutput = crTexture + ((y & 3) << 3);
            s32 column;
            for (column = x; column < xEnd; column++) {
                cbOutput[(column & 7) + (((column >> 3) + tileRow) << 5)] = *cb++ + 128;
                crOutput[(column & 7) + (((column >> 3) + tileRow) << 5)] = *cr++ + 128;
            }
            cb += 8 - width;
            cr += 8 - width;
        }
    }
}

static void TMCJPEG_814F1F48(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 column;
    u8* luminance = work->convBuf + 4;
    s8* cb = (s8*)&work->convBuf[260];
    s8* cr = (s8*)&work->convBuf[324];
    TMCCJPEGDecState* state = work->pState;
    u32 tileWidth = state->convWidth >> 3;
    u8* lumaTexture = state->pLumaBuffer;
    u8* cbTexture = state->pCbBuffer;
    u8* crTexture = state->pCrBuffer;
    s32 width, height;
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
    {
        s32 xEnd = x + width;
        s32 yEnd = y + height;
        s32 row;
        for (row = y; row < yEnd; row++) {
            u32 tileRow = (row >> 2) * tileWidth;
            u8* output = lumaTexture + ((row & 3) << 3);
            for (column = x; column < xEnd; column += 1) {
                output[((column) & 7) + ((((column) >> 3) + tileRow) << 5)] = luminance[0];
                luminance += 1;
            }
            luminance += 16 - width;
        }
        x = (u32)x >> 1;
        y = (u32)y >> 1;
        width = (width + 1) >> 1;
        height = (height + 1) >> 1;
        xEnd = x + width;
        yEnd = y + height;
        tileWidth = state->chromaWidth >> 3;
        for (; y < yEnd; y++) {
            u32 tileRow = (y >> 2) * tileWidth;
            u8* cbOutput = cbTexture + ((y & 3) << 3);
            u8* crOutput = crTexture + ((y & 3) << 3);
            for (column = x; column < xEnd; column++) {
                cbOutput[(column & 7) + (((column >> 3) + tileRow) << 5)] = *cb++ + 128;
                crOutput[(column & 7) + (((column >> 3) + tileRow) << 5)] = *cr++ + 128;
            }
            cb += 8 - width;
            cr += 8 - width;
        }
    }
}

static void TMCJPEG_814F2570(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 column;
    u8* luminance = work->convBuf + 4;
    s8* cb = (s8*)&work->convBuf[132];
    s8* cr = (s8*)&work->convBuf[196];
    TMCCJPEGDecState* state = work->pState;
    u32 tileWidth = state->convWidth >> 3;
    u8* lumaTexture = state->pLumaBuffer;
    u8* cbTexture = state->pCbBuffer;
    u8* crTexture = state->pCrBuffer;
    s32 width, height;
    width = 8 / state->scaleFactor;
    height = 16 / state->scaleFactor;
    {
        s32 xEnd = x + width;
        s32 yEnd = y + height;
        s32 row;
        for (row = y; row < yEnd; row++) {
            u32 tileRow = (row >> 2) * tileWidth;
            u8* output = lumaTexture + ((row & 3) << 3);
            for (column = x; column < xEnd; column += 1) {
                output[((column) & 7) + ((((column) >> 3) + tileRow) << 5)] = luminance[0];
                luminance += 1;
            }
            luminance += 8 - width;
        }
        y = (u32)y >> 1;
        width = 8 / state->scaleFactor;
        height = 8 / state->scaleFactor;
        xEnd = x + width;
        yEnd = y + height;
        tileWidth = state->chromaWidth >> 3;
        for (; y < yEnd; y++) {
            u32 tileRow = (y >> 2) * tileWidth;
            u8* cbOutput = cbTexture + ((y & 3) << 3);
            u8* crOutput = crTexture + ((y & 3) << 3);
            for (column = x; column < xEnd; column++) {
                cbOutput[(column & 7) + (((column >> 3) + tileRow) << 5)] = *cb++ + 128;
                crOutput[(column & 7) + (((column >> 3) + tileRow) << 5)] = *cr++ + 128;
            }
            cb += 8 - width;
            cr += 8 - width;
        }
    }
}

static void TMCJPEG_814F2B50(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 column;
    u8* luminance = work->convBuf + 4;
    s8* cb = (s8*)&work->convBuf[132];
    s8* cr = (s8*)&work->convBuf[196];
    TMCCJPEGDecState* state = work->pState;
    u32 tileWidth = state->convWidth >> 3;
    u8* lumaTexture = state->pLumaBuffer;
    u8* cbTexture = state->pCbBuffer;
    u8* crTexture = state->pCrBuffer;
    s32 width, height;
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
    {
        s32 xEnd = x + width;
        s32 yEnd = y + height;
        s32 row;
        for (row = y; row < yEnd; row++) {
            u32 tileRow = (row >> 2) * tileWidth;
            u8* output = lumaTexture + ((row & 3) << 3);
            for (column = x; column < xEnd; column += 1) {
                output[((column) & 7) + ((((column) >> 3) + tileRow) << 5)] = luminance[0];
                luminance += 1;
            }
            luminance += 8 - width;
        }
        y = (u32)y >> 1;
        height = (height + 1) >> 1;
        xEnd = x + width;
        yEnd = y + height;
        tileWidth = state->chromaWidth >> 3;
        for (; y < yEnd; y++) {
            u32 tileRow = (y >> 2) * tileWidth;
            u8* cbOutput = cbTexture + ((y & 3) << 3);
            u8* crOutput = crTexture + ((y & 3) << 3);
            for (column = x; column < xEnd; column++) {
                cbOutput[(column & 7) + (((column >> 3) + tileRow) << 5)] = *cb++ + 128;
                crOutput[(column & 7) + (((column >> 3) + tileRow) << 5)] = *cr++ + 128;
            }
            cb += 8 - width;
            cr += 8 - width;
        }
    }
}

static void TMCJPEG_814F3158(TMCCJPEGDecWork* work, s32 x, s32 y) {
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

static void TMCJPEG_814F32E4(TMCCJPEGDecWork* work, s32 x, s32 y) {
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

static void TMCJPEG_814F34A4(TMCCJPEGDecWork* work, s32 x, s32 y) {
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

static void TMCJPEG_814F372C(TMCCJPEGDecWork* work, s32 x, s32 y) {
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
