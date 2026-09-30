#include <tmc_jpeg_internal.h>

static void TMCJPEGDEC_converterYUV411toRGBA8(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV411toRGBA8edge(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV422toRGBA8(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV422toRGBA8edge(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV420toRGBA8(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV420toRGBA8edge(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV211toRGBA8(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV211toRGBA8edge(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV444toRGBA8(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV444toRGBA8edge(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV400toRGBA8(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV400toRGBA8edge(TMCCJPEGDecWork*, s32, s32);

s32 TMCJPEGDEC_set_converterRGBA8(TMCCJPEGDecWork* work) {
    u8* ob;
    s32 cc;
    TMCCJPEGDecState* st;

    ob = work->convBuf;
    cc = work->componentCount;
    st = work->pState;

    switch (cc) {
        case 0: {
            u8 mode = work->idctMode;
            u8* ptr = ob + 4;
            u8* p1 = ptr + mode;
            u8* p2 = p1 + mode;
            u8* p3 = p2 + mode;

            work->pConvRowPtrs[0] = (void*)ptr;
            work->pConvRowPtrs[1] = (void*)p1;
            work->pConvRowPtrs[2] = (void*)p2;
            work->pConvRowPtrs[3] = (void*)p3;
            work->pConvRowPtrs[5] = (void*)(ob + 0x104);
            work->pConvRowPtrs[6] = (void*)(ob + 0x144);
            work->pConverterFunc = TMCJPEGDEC_converterYUV411toRGBA8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV411toRGBA8edge;
            work->pitch = 0x20;
            work->converterFlags = 0;
            break;
        }
        case 1: {
            u8 mode = work->idctMode;
            u8* ptr = ob + 4;
            work->pConvRowPtrs[0] = (void*)ptr;
            work->pConvRowPtrs[1] = (void*)(ptr + mode);
            work->pConvRowPtrs[5] = (void*)(ob + 0x84);
            work->pConvRowPtrs[6] = (void*)(ob + 0xC4);
            work->pConverterFunc = TMCJPEGDEC_converterYUV422toRGBA8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV422toRGBA8edge;
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
            work->pConvRowPtrs[0] = (void*)ptr;
            work->pConvRowPtrs[1] = (void*)p1;
            work->pConvRowPtrs[2] = (void*)p2;
            work->pConvRowPtrs[3] = (void*)p3;
            work->pConvRowPtrs[5] = (void*)(ob + 0x104);
            work->pConvRowPtrs[6] = (void*)(ob + 0x144);
            work->pConverterFunc = TMCJPEGDEC_converterYUV420toRGBA8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV420toRGBA8edge;
            work->pitch = 0x10;
            work->converterFlags = 0;
            break;
        }
        case 3: {
            u8 mode = work->idctMode;
            u8* ptr = ob + 4;
            work->pConvRowPtrs[0] = (void*)ptr;
            work->pConvRowPtrs[1] = (void*)(ptr + mode * 8);
            work->pConvRowPtrs[5] = (void*)(ob + 0x84);
            work->pConvRowPtrs[6] = (void*)(ob + 0xC4);
            work->pConverterFunc = TMCJPEGDEC_converterYUV211toRGBA8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV211toRGBA8edge;
            work->pitch = 0x08;
            work->converterFlags = 0;
            break;
        }
        case 4: {
            work->pConvRowPtrs[0] = (void*)(ob + 4);
            work->pConvRowPtrs[5] = (void*)(ob + 0x44);
            work->pConvRowPtrs[6] = (void*)(ob + 0x84);
            work->pConverterFunc = TMCJPEGDEC_converterYUV444toRGBA8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV444toRGBA8edge;
            work->pitch = 0x08;
            work->converterFlags = 0;
            break;
        }
        case 5: {
            work->pConvRowPtrs[0] = (void*)(ob + 4);
            work->pConverterFunc = TMCJPEGDEC_converterYUV400toRGBA8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV400toRGBA8edge;
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
        st->convWidth = ((u32)width / 4 + (width % 4 != 0)) * 4;
        st->convHeight = ((u32)height / 4 + (height % 4 != 0)) * 4;
    }
    return 0;
}

static void TMCJPEGDEC_converterYUV411toRGBA8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 row;
    u8* luminance = work->convBuf + 4;
    u8* cb = work->convBuf + 260;
    u8* cr = work->convBuf + 324;
    TMCCJPEGDecState* state = work->pState;
    s32 tileWidth = (state->convWidth >> 2) << 1;
    u8* texture = state->pTexBuffer;
    s32 width;
    s32 height;
    width = 32 / state->scaleFactor;
    height = 8 / state->scaleFactor;
    {
        s32 yEnd = y + height;
        s32 xEnd = x + width;
        s32 lumaSkip = 32 - width;
        s32 chromaSkip = lumaSkip >> 2;
        for (row = y; row < yEnd; row++) {
            u16* output = (u16*)(texture + ((row & 3) << 3));
            s32 tileRow = (row >> 2) * tileWidth;
            s32 column;
            for (column = x; column < xEnd; column += 4) {
                s32 redOffset, greenOffset, blueOffset;
                {
                    s32 cbValue = (s8)*cb++;
                    s32 crValue = (s8)*cr++;
                    greenOffset = -(cbValue * 88 + crValue * 183) >> 8;
                    redOffset = (crValue * 359) >> 8;
                    blueOffset = (cbValue * 454) >> 8;
                }
                {
                    s32 value = *luminance++;
                    s32 green = value + greenOffset;
                    s32 red = value + redOffset;
                    s32 blue = value + blueOffset;
                    if ((blue | green | red) >> 8) {
                        blue = (blue > 255) ? 255 : blue & ~(blue >> 31);
                        green = (green > 255) ? 255 : green & ~(green >> 31);
                        red = (red > 255) ? 255 : red & ~(red >> 31);
                    }
                    output[(column & 3) + (((((column) >> 2) << 1) + tileRow) << 4)] =
                        (u8)red + 0x10000 - 0x100;
                    output[(column & 3) + (((((column) >> 2) << 1) + tileRow + 1) << 4)] =
                        ((green & 255) << 8) + (blue & 255);
                }
                {
                    s32 value = *luminance++;
                    s32 green = value + greenOffset;
                    s32 red = value + redOffset;
                    s32 blue = value + blueOffset;
                    if ((blue | green | red) >> 8) {
                        blue = (blue > 255) ? 255 : blue & ~(blue >> 31);
                        green = (green > 255) ? 255 : green & ~(green >> 31);
                        red = (red > 255) ? 255 : red & ~(red >> 31);
                    }
                    output[(column + 1 & 3) + (((((column + 1) >> 2) << 1) + tileRow) << 4)] =
                        (u8)red + 0x10000 - 0x100;
                    output[(column + 1 & 3) + (((((column + 1) >> 2) << 1) + tileRow + 1) << 4)] =
                        ((green & 255) << 8) + (blue & 255);
                }
                {
                    s32 value = *luminance++;
                    s32 green = value + greenOffset;
                    s32 red = value + redOffset;
                    s32 blue = value + blueOffset;
                    if ((blue | green | red) >> 8) {
                        blue = (blue > 255) ? 255 : blue & ~(blue >> 31);
                        green = (green > 255) ? 255 : green & ~(green >> 31);
                        red = (red > 255) ? 255 : red & ~(red >> 31);
                    }
                    output[(column + 2 & 3) + (((((column + 2) >> 2) << 1) + tileRow) << 4)] =
                        (u8)red + 0x10000 - 0x100;
                    output[(column + 2 & 3) + (((((column + 2) >> 2) << 1) + tileRow + 1) << 4)] =
                        ((green & 255) << 8) + (blue & 255);
                }
                {
                    s32 value = *luminance++;
                    s32 green = value + greenOffset;
                    s32 red = value + redOffset;
                    s32 blue = value + blueOffset;
                    if ((blue | green | red) >> 8) {
                        blue = (blue > 255) ? 255 : blue & ~(blue >> 31);
                        green = (green > 255) ? 255 : green & ~(green >> 31);
                        red = (red > 255) ? 255 : red & ~(red >> 31);
                    }
                    output[(column + 3 & 3) + (((((column + 3) >> 2) << 1) + tileRow) << 4)] =
                        (u8)red + 0x10000 - 0x100;
                    output[(column + 3 & 3) + (((((column + 3) >> 2) << 1) + tileRow + 1) << 4)] =
                        ((green & 255) << 8) + (blue & 255);
                }

            }
            luminance += lumaSkip;
            cb += chromaSkip;
            cr += chromaSkip;
        }
    }
}

static void TMCJPEGDEC_converterYUV411toRGBA8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 column;
    u8* luminance = work->convBuf + 4;
    u8* cb = work->convBuf + 260;
    u8* cr = work->convBuf + 324;
    TMCCJPEGDecState* state = work->pState;
    s32 tileWidth = (state->convWidth >> 2) << 1;
    u8* texture = state->pTexBuffer;
    s32 width;
    s32 height;
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
        s32 yEnd = y + height;
        s32 xEnd = x + width;
        s32 lumaSkip = 32 - width;
        s32 chromaSkip = lumaSkip >> 2;
        s32 redOffset = 0, greenOffset = 0, blueOffset = 0;
        for (; y < yEnd; y++) {
            s32 tileRow = (y >> 2) * tileWidth;
            u16* output = (u16*)(texture + ((y & 3) << 3));
            for (column = x; column < xEnd; column += 1) {
                if ((column & 3) == 0) {
                    s32 cbValue = (s8)*cb++;
                    s32 crValue = (s8)*cr++;
                    greenOffset = -(cbValue * 88 + crValue * 183) >> 8;
                    redOffset = (crValue * 359) >> 8;
                    blueOffset = (cbValue * 454) >> 8;
                }
                {
                    s32 value = luminance[0];
                    s32 green = value + greenOffset;
                    s32 red = value + redOffset;
                    s32 blue = value + blueOffset;
                    if ((blue | green | red) >> 8) {
                        blue = (blue > 255) ? 255 : blue & ~(blue >> 31);
                        green = (green > 255) ? 255 : green & ~(green >> 31);
                        red = (red > 255) ? 255 : red & ~(red >> 31);
                    }
                    output[(column & 3) + (((((column) >> 2) << 1) + tileRow) << 4)] =
                        (u8)red + 0x10000 - 0x100;
                    output[(column & 3) + (((((column) >> 2) << 1) + tileRow + 1) << 4)] =
                        ((green & 255) << 8) + (blue & 255);
                }
                luminance += 1;
            }
            luminance += lumaSkip;
            cb += chromaSkip;
            cr += chromaSkip;
        }
    }
}

static void TMCJPEGDEC_converterYUV422toRGBA8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    u8* luminance;
    u8* cb;
    u8* cr;
    TMCCJPEGDecState* state;
    s32 tileWidth;
    u8* texture;
    s32 width;
    s32 height;
    s32 xEnd;
    s32 yEnd;
    s32 lumaSkip;
    s32 chromaSkip;
    s32 tileRow;
    u16* output;
    s32 column;
    s32 cbValue;
    s32 crValue;
    s32 value;
    s32 green;
    s32 red;
    s32 blue;
    luminance = work->convBuf + 4;
    cb = work->convBuf + 132;
    cr = work->convBuf + 196;
    state = work->pState;
    tileWidth = (state->convWidth >> 2) << 1;
    texture = state->pTexBuffer;

    width = 16 / state->scaleFactor;
    height = 8 / state->scaleFactor;
    {
        xEnd = x + width;
        yEnd = y + height;
        lumaSkip = 16 - width;
        chromaSkip = lumaSkip >> 1;
        for (; y < yEnd; y++) {
            tileRow = (y >> 2) * tileWidth;
            output = (u16*)(texture + ((y & 3) << 3));

            for (column = x; column < xEnd; column += 2) {
                s32 redOffset, greenOffset, blueOffset;
                {
                    cbValue = (s8)*cb++;
                    crValue = (s8)*cr++;
                    greenOffset = -(cbValue * 88 + crValue * 183) >> 8;
                    redOffset = (crValue * 359) >> 8;
                    blueOffset = (cbValue * 454) >> 8;
                }
                {
                    value = luminance[0];
                    green = value + greenOffset;
                    red = value + redOffset;
                    blue = value + blueOffset;
                    if ((blue | green | red) >> 8) {
                        blue = (blue > 255) ? 255 : blue & ~(blue >> 31);
                        green = (green > 255) ? 255 : green & ~(green >> 31);
                        red = (red > 255) ? 255 : red & ~(red >> 31);
                    }
                    output[(column & 3) + (((((column) >> 2) << 1) + tileRow) << 4)] =
                        (u8)red + 0x10000 - 0x100;
                    output[(column & 3) + (((((column) >> 2) << 1) + tileRow + 1) << 4)] =
                        ((green & 255) << 8) + (blue & 255);
                }
                {
                    s32 value = luminance[1];
                    s32 green = value + greenOffset;
                    s32 red = value + redOffset;
                    s32 blue = value + blueOffset;
                    if ((blue | green | red) >> 8) {
                        blue = (blue > 255) ? 255 : blue & ~(blue >> 31);
                        green = (green > 255) ? 255 : green & ~(green >> 31);
                        red = (red > 255) ? 255 : red & ~(red >> 31);
                    }
                    output[(column + 1 & 3) + (((((column + 1) >> 2) << 1) + tileRow) << 4)] =
                        (u8)red + 0x10000 - 0x100;
                    output[(column + 1 & 3) + (((((column + 1) >> 2) << 1) + tileRow + 1) << 4)] =
                        ((green & 255) << 8) + (blue & 255);
                }
                luminance += 2;
            }
            luminance += lumaSkip;
            cb += chromaSkip;
            cr += chromaSkip;
        }
    }
}

static void TMCJPEGDEC_converterYUV422toRGBA8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 column;
    u8* luminance = work->convBuf + 4;
    u8* cb = work->convBuf + 132;
    u8* cr = work->convBuf + 196;
    TMCCJPEGDecState* state = work->pState;
    s32 tileWidth = (state->convWidth >> 2) << 1;
    u8* texture = state->pTexBuffer;
    s32 width;
    s32 height;
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
        s32 yEnd = y + height;
        s32 xEnd = x + width;
        s32 lumaSkip = 16 - width;
        s32 chromaSkip = lumaSkip >> 1;
        s32 redOffset = 0, greenOffset = 0, blueOffset = 0;
        for (; y < yEnd; y++) {
            s32 tileRow = (y >> 2) * tileWidth;
            u16* output = (u16*)(texture + ((y & 3) << 3));
            for (column = x; column < xEnd; column += 1) {
                if ((column & 1) == 0) {
                    s32 cbValue = (s8)*cb++;
                    s32 crValue = (s8)*cr++;
                    greenOffset = -(cbValue * 88 + crValue * 183) >> 8;
                    redOffset = (crValue * 359) >> 8;
                    blueOffset = (cbValue * 454) >> 8;
                }
                {
                    s32 value = luminance[0];
                    s32 green = value + greenOffset;
                    s32 red = value + redOffset;
                    s32 blue = value + blueOffset;
                    if ((blue | green | red) >> 8) {
                        blue = (blue > 255) ? 255 : blue & ~(blue >> 31);
                        green = (green > 255) ? 255 : green & ~(green >> 31);
                        red = (red > 255) ? 255 : red & ~(red >> 31);
                    }
                    output[(column & 3) + (((((column) >> 2) << 1) + tileRow) << 4)] =
                        (u8)red + 0x10000 - 0x100;
                    output[(column & 3) + (((((column) >> 2) << 1) + tileRow + 1) << 4)] =
                        ((green & 255) << 8) + (blue & 255);
                }
                luminance += 1;
            }
            luminance += lumaSkip;
            cb += chromaSkip;
            cr += chromaSkip;
        }
    }
}

static void TMCJPEGDEC_converterYUV420toRGBA8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    u8* luminance = work->convBuf + 4;
    s8* cb = (s8*) work->convBuf + 260;
    s8* cr = (s8*) work->convBuf + 324;
    TMCCJPEGDecState* state = work->pState;
    s32 tileWidth = (state->convWidth >> 2) << 1;
    u8* texture = state->pTexBuffer;
    s32 width;
    s32 height;
    width = 16 / state->scaleFactor;
    height = 16 / state->scaleFactor;
    {
        s32 yEnd = y + height;
        s32 xEnd = x + width;
        s32 lumaSkip = 16 - width;
        s32 chromaSkip = lumaSkip >> 1;
        for (; y < yEnd; y++) {
            s32 tileRow = (y >> 2) * tileWidth;
            u16* output = (u16*)(texture + ((y & 3) << 3));
            s32 column;
            for (column = x; column < xEnd; column += 2) {
                s32 redOffset, greenOffset, blueOffset;
                {
                    s32 cbValue = (s8)*cb++;
                    s32 crValue = (s8)*cr++;
                    greenOffset = -(cbValue * 88 + crValue * 183) >> 8;
                    redOffset = (crValue * 359) >> 8;
                    blueOffset = (cbValue * 454) >> 8;
                }
                {
                    s32 value = *luminance++;
                    s32 green = value + greenOffset;
                    s32 red = value + redOffset;
                    s32 blue = value + blueOffset;
                    if ((blue | green | red) >> 8) {
                        blue = (blue > 255) ? 255 : blue & ~(blue >> 31);
                        green = (green > 255) ? 255 : green & ~(green >> 31);
                        red = (red > 255) ? 255 : red & ~(red >> 31);
                    }
                    output[(column & 3) + (((((column) >> 2) << 1) + tileRow) << 4)] =
                        (u8)red + 0x10000 - 0x100;
                    output[(column & 3) + (((((column) >> 2) << 1) + tileRow + 1) << 4)] =
                        ((green & 255) << 8) + (blue & 255);
                }
                {
                    s32 value = *luminance++;
                    s32 green = value + greenOffset;
                    s32 red = value + redOffset;
                    s32 blue = value + blueOffset;
                    if ((blue | green | red) >> 8) {
                        blue = (blue > 255) ? 255 : blue & ~(blue >> 31);
                        green = (green > 255) ? 255 : green & ~(green >> 31);
                        red = (red > 255) ? 255 : red & ~(red >> 31);
                    }
                    output[(column + 1 & 3) + (((((column + 1) >> 2) << 1) + tileRow) << 4)] =
                        (u8)red + 0x10000 - 0x100;
                    output[(column + 1 & 3) + (((((column + 1) >> 2) << 1) + tileRow + 1) << 4)] =
                        ((green & 255) << 8) + (blue & 255);
                }

            }
            luminance += lumaSkip;
            if (y & 1) {
                cb += chromaSkip;
                cr += chromaSkip;
            } else {
                cb -= (width + 1) >> 1;
                cr -= (width + 1) >> 1;
            }
        }
    }
}

static void TMCJPEGDEC_converterYUV420toRGBA8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    u8* luminance = work->convBuf + 4;
    u8* cb = work->convBuf + 260;
    u8* cr = work->convBuf + 324;
    TMCCJPEGDecState* state = work->pState;
    s32 tileWidth = (state->convWidth >> 2) << 1;
    u8* texture = state->pTexBuffer;
    s32 width;
    s32 height;
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
        s32 yEnd = y + height;
        s32 xEnd = x + width;
        s32 lumaSkip = 16 - width;
        s32 chromaSkip = lumaSkip >> 1;
        s32 redOffset = 0, greenOffset = 0, blueOffset = 0;
        for (; y < yEnd; y++) {
            u16* output = (u16*)(texture + ((y & 3) << 3));
            s32 tileRow = (y >> 2) * tileWidth;
            s32 column;
            for (column = x; column < xEnd; column += 1) {
                if ((column & 1) == 0) {
                    s32 cbValue = (s8)*cb++;
                    s32 crValue = (s8)*cr++;
                    greenOffset = -(cbValue * 88 + crValue * 183) >> 8;
                    redOffset = (crValue * 359) >> 8;
                    blueOffset = (cbValue * 454) >> 8;
                }
                {
                    s32 value = *luminance++;
                    s32 green = value + greenOffset;
                    s32 red = value + redOffset;
                    s32 blue = value + blueOffset;
                    if ((blue | green | red) >> 8) {
                        blue = (blue > 255) ? 255 : blue & ~(blue >> 31);
                        green = (green > 255) ? 255 : green & ~(green >> 31);
                        red = (red > 255) ? 255 : red & ~(red >> 31);
                    }
                    output[(column & 3) + (((((column) >> 2) << 1) + tileRow) << 4)] =
                        (u8)red + 0x10000 - 0x100;
                    output[(column & 3) + (((((column) >> 2) << 1) + tileRow + 1) << 4)] =
                        ((green & 255) << 8) + (blue & 255);
                }

            }
            luminance += lumaSkip;
            if (y & 1) {
                cb += chromaSkip;
                cr += chromaSkip;
            } else {
                cb -= (width + 1) >> 1;
                cr -= (width + 1) >> 1;
            }
        }
    }
}

static void TMCJPEGDEC_converterYUV211toRGBA8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    u8* luminance = work->convBuf + 4;
    u8* cb = work->convBuf + 132;
    u8* cr = work->convBuf + 196;
    TMCCJPEGDecState* state = work->pState;
    s32 tileWidth = (state->convWidth >> 2) << 1;
    u8* texture = state->pTexBuffer;
    s32 width;
    s32 height;
    width = 8 / state->scaleFactor;
    height = 16 / state->scaleFactor;
    {
        s32 yEnd = y + height;
        s32 xEnd = x + width;
        s32 lumaSkip = 8 - width;
        s32 chromaSkip = lumaSkip >> 0;
        for (; y < yEnd; y++) {
            s32 tileRow = (y >> 2) * tileWidth;
            u16* output = (u16*)(texture + ((y & 3) << 3));
            s32 column;
            for (column = x; column < xEnd; column += 1) {
                s32 redOffset, greenOffset, blueOffset;
                {
                    s32 cbValue = (s8)*cb++;
                    s32 crValue = (s8)*cr++;
                    greenOffset = -(cbValue * 88 + crValue * 183) >> 8;
                    redOffset = (crValue * 359) >> 8;
                    blueOffset = (cbValue * 454) >> 8;
                }
                {
                    s32 value = *luminance++;
                    s32 green = value + greenOffset;
                    s32 red = value + redOffset;
                    s32 blue = value + blueOffset;
                    if ((blue | green | red) >> 8) {
                        blue = (blue > 255) ? 255 : blue & ~(blue >> 31);
                        green = (green > 255) ? 255 : green & ~(green >> 31);
                        red = (red > 255) ? 255 : red & ~(red >> 31);
                    }
                    output[(column & 3) + (((((column) >> 2) << 1) + tileRow) << 4)] =
                        (u8)red + 0x10000 - 0x100;
                    output[(column & 3) + (((((column) >> 2) << 1) + tileRow + 1) << 4)] =
                        ((green & 255) << 8) + (blue & 255);
                }

            }
            luminance += lumaSkip;
            if (y & 1) {
                cb += chromaSkip;
                cr += chromaSkip;
            } else {
                cb -= (width + 0) >> 0;
                cr -= (width + 0) >> 0;
            }
        }
    }
}

static void TMCJPEGDEC_converterYUV211toRGBA8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 column;
    u8* luminance = work->convBuf + 4;
    u8* cb = work->convBuf + 132;
    u8* cr = work->convBuf + 196;
    TMCCJPEGDecState* state = work->pState;
    s32 tileWidth = (state->convWidth >> 2) << 1;
    u8* texture = state->pTexBuffer;
    s32 width;
    s32 height;
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
        s32 yEnd = y + height;
        s32 xEnd = x + width;
        s32 lumaSkip = 8 - width;
        s32 chromaSkip = lumaSkip >> 0;
        for (; y < yEnd; y++) {
            s32 tileRow = (y >> 2) * tileWidth;
            u16* output = (u16*)(texture + ((y & 3) << 3));
            for (column = x; column < xEnd; column += 1) {
                s32 redOffset, greenOffset, blueOffset;
                {
                    s32 cbValue = (s8)*cb++;
                    s32 crValue = (s8)*cr++;
                    greenOffset = -(cbValue * 88 + crValue * 183) >> 8;
                    redOffset = (crValue * 359) >> 8;
                    blueOffset = (cbValue * 454) >> 8;
                }
                {
                    s32 value = luminance[0];
                    s32 green = value + greenOffset;
                    s32 red = value + redOffset;
                    s32 blue = value + blueOffset;
                    if ((blue | green | red) >> 8) {
                        blue = (blue > 255) ? 255 : blue & ~(blue >> 31);
                        green = (green > 255) ? 255 : green & ~(green >> 31);
                        red = (red > 255) ? 255 : red & ~(red >> 31);
                    }
                    output[(column & 3) + (((((column) >> 2) << 1) + tileRow) << 4)] =
                        (u8)red + 0x10000 - 0x100;
                    output[(column & 3) + (((((column) >> 2) << 1) + tileRow + 1) << 4)] =
                        ((green & 255) << 8) + (blue & 255);
                }
                luminance += 1;
            }
            luminance += lumaSkip;
            if (y & 1) {
                cb += chromaSkip;
                cr += chromaSkip;
            } else {
                cb -= (width + 0) >> 0;
                cr -= (width + 0) >> 0;
            }
        }
    }
}

static void TMCJPEGDEC_converterYUV444toRGBA8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 row;
    s32 column;
    s32 tileRow;
    u16* output;
    u8* luminance;
    u8* cb;
    u8* cr;
    TMCCJPEGDecState* state;
    s32 tileWidth;
    u8* texture;
    s32 width;
    s32 height;
    s32 xEnd;
    s32 yEnd;
    s32 rowSkip;
    s32 cbValue;
    s32 crValue;
    s32 value;
    s32 green;
    s32 red;

    luminance = work->convBuf + 4;
    cb = work->convBuf + 68;
    cr = work->convBuf + 132;
    state = work->pState;
    tileWidth = (state->convWidth >> 2) << 1;
    texture = state->pTexBuffer;
    width = 8 / state->scaleFactor;
    height = 8 / state->scaleFactor;
    xEnd = x + width;
    yEnd = y + height;
    rowSkip = 8 - width;
    for (row = y; row < yEnd; row++) {
        output = (u16*)(texture + ((row & 3) << 3));
        tileRow = (row >> 2) * tileWidth;
        for (column = x; column < xEnd; column++) {
            cbValue = (s8)*cb++;
            crValue = (s8)*cr++;
            value = *luminance++;
            green = value + (-(cbValue * 88 + crValue * 183) >> 8);
            red = value + ((crValue * 359) >> 8);
            value += (cbValue * 454) >> 8;
            if ((value | green | red) >> 8) {
                value &= ~(value >> 31);
                if (value > 255) {
                    value = 255;
                }
                green &= ~(green >> 31);
                if (green > 255) {
                    green = 255;
                }
                red &= ~(red >> 31);
                if (red > 255) {
                    red = 255;
                }
            }
            output[(column & 3) + ((((column >> 2) << 1) + tileRow) << 4)] =
                (u8)red + 0x10000 - 0x100;
            output[(column & 3) + ((((column >> 2) << 1) + tileRow + 1) << 4)] =
                ((green & 255) << 8) + (value & 255);
        }
        luminance += rowSkip;
        cb += rowSkip;
        cr += rowSkip;
    }
}

static void TMCJPEGDEC_converterYUV444toRGBA8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 column;
    s32 tileRow;
    u16* output;
    u8* luminance;
    u8* cb;
    u8* cr;
    TMCCJPEGDecState* state;
    s32 tileWidth;
    u8* texture;
    s32 width;
    s32 height;
    s32 xEnd;
    s32 yEnd;
    s32 rowSkip;
    s32 cbValue;
    s32 crValue;
    s32 value;
    s32 green;
    s32 red;

    luminance = work->convBuf + 4;
    cb = work->convBuf + 68;
    cr = work->convBuf + 132;
    state = work->pState;
    tileWidth = (state->convWidth >> 2) << 1;
    texture = state->pTexBuffer;
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
        output = (u16*)(texture + ((y & 3) << 3));
        tileRow = (y >> 2) * tileWidth;
        for (column = x; column < xEnd; column++) {
            cbValue = (s8)*cb++;
            crValue = (s8)*cr++;
            value = *luminance++;
            green = value + (-(cbValue * 88 + crValue * 183) >> 8);
            red = value + ((crValue * 359) >> 8);
            value += (cbValue * 454) >> 8;
            if ((value | green | red) >> 8) {
                value &= ~(value >> 31);
                if (value > 255) {
                    value = 255;
                }
                green &= ~(green >> 31);
                if (green > 255) {
                    green = 255;
                }
                red &= ~(red >> 31);
                if (red > 255) {
                    red = 255;
                }
            }
            output[(column & 3) + ((((column >> 2) << 1) + tileRow) << 4)] =
                (u8)red + 0x10000 - 0x100;
            output[(column & 3) + ((((column >> 2) << 1) + tileRow + 1) << 4)] =
                ((green & 255) << 8) + (value & 255);
        }
        luminance += rowSkip;
        cb += rowSkip;
        cr += rowSkip;
    }
}

static void TMCJPEGDEC_converterYUV400toRGBA8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 value;
    u16* output;
    s32 tileRow;
    u8* texture;
    u8* luminance;
    s32 column;
    s32 xEnd;
    s32 green;
    s32 yEnd;
    TMCCJPEGDecState* state;
    s32 row;
    s32 tileWidth;
    s32 height;
    s32 width;
    s32 blue;

    state = work->pState;
    texture = state->pTexBuffer;
    luminance = work->convBuf + 4;
    tileWidth = (state->convWidth >> 2) << 1;
    width = 8 / state->scaleFactor;
    height = 8 / state->scaleFactor;
    {
        xEnd = x + width;
        yEnd = y + height;
        width = 8 - width;
        for (row = y; row < yEnd; row++) {
            output = (u16*)(texture + ((row & 3) << 3));
            tileRow = (row >> 2) * tileWidth;
            for (column = x; column < xEnd; column += 1) {
                value = *luminance++;
                if (value >> 8) {
                    blue = value > 255 ? 255 : value < 0 ? 0 : value;
                    green = value > 255 ? 255 : value < 0 ? 0 : value;
                    value = value > 255 ? 255 : value < 0 ? 0 : value;
                } else {
                    green = blue = value;
                }
                output[(column & 3) + ((((column >> 2) << 1) + tileRow) << 4)] =
                    (u8)value + 0x10000 - 0x100;
                output[(column & 3) + ((((column >> 2) << 1) + tileRow + 1) << 4)] =
                    ((green & 255) << 8) + (blue & 255);
            }
            luminance += width;
        }
    }
}

static void TMCJPEGDEC_converterYUV400toRGBA8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 value;
    u16* output;
    s32 tileRow;
    u8* texture;
    u8* luminance;
    s32 column;
    s32 xEnd;
    s32 green;
    s32 yEnd;
    TMCCJPEGDecState* state;
    s32 row;
    s32 tileWidth;
    s32 height;
    s32 width;
    s32 blue;

    state = work->pState;
    texture = state->pTexBuffer;
    luminance = work->convBuf + 4;
    tileWidth = (state->convWidth >> 2) << 1;
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
        width = 8 - width;
        for (row = y; row < yEnd; row++) {
            output = (u16*)(texture + ((row & 3) << 3));
            tileRow = (row >> 2) * tileWidth;
            for (column = x; column < xEnd; column += 1) {
                value = *luminance++;
                if (value >> 8) {
                    blue = value > 255 ? 255 : value < 0 ? 0 : value;
                    green = value > 255 ? 255 : value < 0 ? 0 : value;
                    value = value > 255 ? 255 : value < 0 ? 0 : value;
                } else {
                    green = blue = value;
                }
                output[(column & 3) + ((((column >> 2) << 1) + tileRow) << 4)] =
                    (u8)value + 0x10000 - 0x100;
                output[(column & 3) + ((((column >> 2) << 1) + tileRow + 1) << 4)] =
                    ((green & 255) << 8) + (blue & 255);
            }
            luminance += width;
        }
    }
}
