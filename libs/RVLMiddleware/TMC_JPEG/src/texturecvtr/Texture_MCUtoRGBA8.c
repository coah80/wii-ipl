#include <revolution/os.h>
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
            work->pConverterFunc = TMCJPEGDEC_converterYUV411toRGBA8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV411toRGBA8edge;
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
            work->pConverterFunc = TMCJPEGDEC_converterYUV422toRGBA8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV422toRGBA8edge;
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
            work->pConverterFunc = TMCJPEGDEC_converterYUV420toRGBA8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV420toRGBA8edge;
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
            work->pConverterFunc = TMCJPEGDEC_converterYUV211toRGBA8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV211toRGBA8edge;
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
            converter = TMCJPEGDEC_converterYUV444toRGBA8;
            edgeConverter = TMCJPEGDEC_converterYUV444toRGBA8edge;
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
            converter = TMCJPEGDEC_converterYUV400toRGBA8;
            edgeConverter = TMCJPEGDEC_converterYUV400toRGBA8edge;
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
        state->convWidth = ((u32)width / 4 + (width % 4 != 0)) * 4;
        state->convHeight = ((u32)height / 4 + (height % 4 != 0)) * 4;

    }
    return 0;
}

static void TMCJPEGDEC_converterYUV411toRGBA8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 red;
    u8* luminance;
    u8* cb;
    u8* cr;
    TMCCJPEGDecState* state;
    u8* texture;
    s32 height;
    s32 column;
    s32 xEnd;
    s32 green;
    s32 yEnd;
    s32 tileWidth;
    s32 blueOffset;
    s32 greenOffset;
    s32 tileRow;
    s32 lumaSkip;
    s8 crValue;
    s32 chromaSkip;
    s32 width;
    s32 cbValue;
    u8 value;
    s32 row;
    u16* output;
    s32 redOffset;
    s32 blue;

    luminance = work->convBuf + 4;
    cb = work->convBuf + 260;
    cr = work->convBuf + 324;
    state = work->pState;
    tileWidth = (state->convWidth >> 2) << 1;
    texture = state->pTexBuffer;

    width = 32 / state->scaleFactor;
    height = 8 / state->scaleFactor;
    {
        yEnd = y + height;
        xEnd = x + width;
        lumaSkip = 32 - width;
        chromaSkip = lumaSkip >> 2;
        for (row = y; row < yEnd; row++) {
            output = (u16*)(texture + ((row & 3) << 3));
            tileRow = (row >> 2) * tileWidth;

            for (column = x; column < xEnd; column += 4) {

                {
                    cbValue = (s8)*cb++;
                    crValue = (s8)*cr++;
                    redOffset = (crValue * 359) >> 8;
                    greenOffset = -(crValue * 183 + cbValue * 88) >> 8;
                    blueOffset = (cbValue * 454) >> 8;
                }
                {
                    value = *luminance++;
                    green = value + greenOffset;
                    red = value + redOffset;
                    blue = value + blueOffset;
                    if ((red | green | blue) >> 8) {
                        blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                        green = green > 255 ? 255 : green < 0 ? 0 : green;
                        red = red > 255 ? 255 : red < 0 ? 0 : red;
                    }
                    red = (u8)red + 0x10000 - 0x100;
                    output[(column & 3) + (((((column) >> 2) << 1) + tileRow) << 4)] = red;
                    output[(column & 3) + (((((column) >> 2) << 1) + tileRow + 1) << 4)] = ((green & 255) << 8) + (blue & 255);
                }
                {
                    value = *luminance++;
                    green = value + greenOffset;
                    red = value + redOffset;
                    blue = value + blueOffset;
                    if ((red | green | blue) >> 8) {
                        blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                        green = green > 255 ? 255 : green < 0 ? 0 : green;
                        red = red > 255 ? 255 : red < 0 ? 0 : red;
                    }
                    red = (u8)red + 0x10000 - 0x100;
                    output[(column + 1 & 3) + (((((column + 1) >> 2) << 1) + tileRow) << 4)] = red;
                    output[(column + 1 & 3) + (((((column + 1) >> 2) << 1) + tileRow + 1) << 4)] = ((green & 255) << 8) + (blue & 255);
                }
                {
                    value = *luminance++;
                    green = value + greenOffset;
                    red = value + redOffset;
                    blue = value + blueOffset;
                    if ((red | green | blue) >> 8) {
                        blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                        green = green > 255 ? 255 : green < 0 ? 0 : green;
                        red = red > 255 ? 255 : red < 0 ? 0 : red;
                    }
                    red = (u8)red + 0x10000 - 0x100;
                    output[(column + 2 & 3) + (((((column + 2) >> 2) << 1) + tileRow) << 4)] = red;
                    output[(column + 2 & 3) + (((((column + 2) >> 2) << 1) + tileRow + 1) << 4)] = ((green & 255) << 8) + (blue & 255);
                }
                {
                    value = *luminance++;
                    green = value + greenOffset;
                    red = value + redOffset;
                    blue = value + blueOffset;
                    if ((red | green | blue) >> 8) {
                        blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                        green = green > 255 ? 255 : green < 0 ? 0 : green;
                        red = red > 255 ? 255 : red < 0 ? 0 : red;
                    }
                    red = (u8)red + 0x10000 - 0x100;
                    output[(column + 3 & 3) + (((((column + 3) >> 2) << 1) + tileRow) << 4)] = red;
                    output[(column + 3 & 3) + (((((column + 3) >> 2) << 1) + tileRow + 1) << 4)] = ((green & 255) << 8) + (blue & 255);
                }

            }
            luminance += lumaSkip;
            cb += chromaSkip;
            cr += chromaSkip;
        }
    }
}

static void TMCJPEGDEC_converterYUV411toRGBA8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 chromaSkip;
    s32 tileRow;
    s32 lumaSkip;
    u8* texture;
    TMCCJPEGDecState* state;
    u8* luminance;
    u8* cb;
    s32 width;
    s32 height;
    u8* cr;
    s32 column;
    s32 xEnd;
    s32 yEnd;
    s32 tileWidth;
    s32 redOffset;
    s32 cbValue;
    s8 crValue;
    u16* output;
    s32 blueOffset;
    s32 greenOffset;
    s32 blue;
    s32 red;
    s32 green;

    luminance = work->convBuf + 4;
    cb = &work->convBuf[260];
    cr = &work->convBuf[324];
    state = work->pState;
    tileWidth = (state->convWidth >> 2) << 1;
    texture = state->pTexBuffer;
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
    lumaSkip = 32 - width;
    chromaSkip = lumaSkip >> 2;
    ASSERTLINE((x & 3) == 0, __LINE__);
    for (; y < yEnd; y++) {
        tileRow = (y >> 2) * tileWidth;
        output = (u16*)(texture + ((y & 3) << 3));
        for (column = x; column < xEnd; column += 1) {
            if ((column & 3) == 0) {
                cbValue = (s8)*cb++;
                crValue = (s8)*cr++;
                redOffset = (crValue * 359) >> 8;
                greenOffset = -(cbValue * 88 + crValue * 183) >> 8;
                blueOffset = (cbValue * 454) >> 8;
            }
            blue = *luminance++;
            red = blue + redOffset;
            green = blue + greenOffset;
            blue = blue + blueOffset;
            if ((green | red | blue) >> 8) {
                blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                green = green > 255 ? 255 : green < 0 ? 0 : green;
                red = red > 255 ? 255 : red < 0 ? 0 : red;
            }
            {
                red = (u8)red + 0x10000 - 0x100;
                green = (green & 255) << 8;
                blue = blue & 255;
                output[(column & 3) + ((((column >> 2) << 1) + tileRow) << 4)] = red;
                output[(column & 3) + ((((column >> 2) << 1) + tileRow + 1) << 4)] = green + blue;
            }
        }
        luminance += lumaSkip;
        cb += chromaSkip;
        cr += chromaSkip;
    }
}

static void TMCJPEGDEC_converterYUV422toRGBA8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 chromaSkip;
    u16* output;
    s32 cbValue;
    s32 tileRow;
    TMCCJPEGDecState* state;
    s32 lumaSkip;
    u8* texture;
    s32 width;
    s32 height;
    u8* luminance;
    u8* cb;
    s32 red;
    u8* cr;
    s32 column;
    s32 xEnd;
    s32 yEnd;
    s32 tileWidth;
    s32 redOffset;
    s32 greenOffset;
    s32 blueOffset;
    s32 value;
    s32 green;
    s32 blue;
    s32 crValue;

    luminance = work->convBuf + 4;
    cb = &work->convBuf[132];
    cr = &work->convBuf[196];
    state = work->pState;
    tileWidth = (state->convWidth >> 2) << 1;
    texture = state->pTexBuffer;
    width = 16 / state->scaleFactor;
    height = 8 / state->scaleFactor;
    xEnd = x + width;
    yEnd = y + height;
    lumaSkip = 16 - width;
    chromaSkip = lumaSkip >> 1;
    for (; y < yEnd; y++) {
        output = (u16*)(texture + ((y & 3) << 3));
        tileRow = (y >> 2) * tileWidth;
        for (column = x; column < xEnd; column += 2) {
            cbValue = (s8)*cb++;
            crValue = (s8)*cr++;
            redOffset = (crValue * 359) >> 8;
            greenOffset = -(cbValue * 88 + crValue * 183) >> 8;
            blueOffset = (cbValue * 454) >> 8;
            value = *luminance++;
            green = value + greenOffset;
            red = value + redOffset;
            blue = value + blueOffset;
            if ((red | green | blue) >> 8) {
                blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                green = green > 255 ? 255 : green < 0 ? 0 : green;
                red = red > 255 ? 255 : red < 0 ? 0 : red;
            }
            output[(column & 3) + ((((column >> 2) << 1) + tileRow) << 4)] = (u8)red + 0x10000 - 0x100;
            output[(column & 3) + ((((column >> 2) << 1) + tileRow + 1) << 4)] = ((green & 255) << 8) + (blue & 255);
            value = *luminance++;
            green = value + greenOffset;
            red = value + redOffset;
            blue = value + blueOffset;
            if ((red | green | blue) >> 8) {
                blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                green = green > 255 ? 255 : green < 0 ? 0 : green;
                red = red > 255 ? 255 : red < 0 ? 0 : red;
            }
            output[((column + 1) & 3) + (((((column + 1) >> 2) << 1) + tileRow) << 4)] = (u8)red + 0x10000 - 0x100;
            output[((column + 1) & 3) + (((((column + 1) >> 2) << 1) + tileRow + 1) << 4)] = ((green & 255) << 8) + (blue & 255);
        }
        luminance += lumaSkip;
        cb += chromaSkip;
        cr += chromaSkip;
    }
}

static void TMCJPEGDEC_converterYUV422toRGBA8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 chromaSkip;
    u16* output;
    s32 tileRow;
    s32 lumaSkip;
    TMCCJPEGDecState* state;
    u8* texture;
    u8* luminance;
    s32 width;
    s32 height;
    u8* cb;
    u8* cr;
    s32 column;
    s32 xEnd;
    s32 yEnd;
    s32 tileWidth;
    s32 cbValue;
    s32 crValue;
    s32 redOffset;
    s32 greenOffset;
    s32 blueOffset;
    s32 value;
    s32 red;
    s32 green;
    s32 blue;

    luminance = work->convBuf + 4;
    cb = &work->convBuf[132];
    cr = &work->convBuf[196];
    state = work->pState;
    tileWidth = (state->convWidth >> 2) << 1;
    texture = state->pTexBuffer;
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
    lumaSkip = 16 - width;
    chromaSkip = lumaSkip >> 1;
    ASSERTLINE((x & 1) == 0, __LINE__);
    for (; y < yEnd; y++) {
        output = (u16*)(texture + ((y & 3) << 3));
        tileRow = (y >> 2) * tileWidth;
        for (column = x; column < xEnd; column += 1) {
            if ((column & 1) == 0) {
                cbValue = (s8)*cb++;
                crValue = (s8)*cr++;
                redOffset = (crValue * 359) >> 8;
                greenOffset = -(cbValue * 88 + crValue * 183) >> 8;
                blueOffset = (cbValue * 454) >> 8;
            }
            value = *luminance++;
            red = value + redOffset;
            blue = value + blueOffset;
            green = value + greenOffset;
            if ((red | green | blue) >> 8) {
                blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                green = green > 255 ? 255 : green < 0 ? 0 : green;
                red = red > 255 ? 255 : red < 0 ? 0 : red;
            }
            output[(column & 3) + ((((column >> 2) << 1) + tileRow) << 4)] = (u8)red + 0x10000 - 0x100;
            output[(column & 3) + ((((column >> 2) << 1) + tileRow + 1) << 4)] = ((green & 255) << 8) + (blue & 255);
        }
        luminance += lumaSkip;
        cb += chromaSkip;
        cr += chromaSkip;
    }
}

static void TMCJPEGDEC_converterYUV420toRGBA8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 chromaSkip;
    s8 crValue;
    s32 lumaSkip;
    u16* output;
    TMCCJPEGDecState* state;
    s32 tileRow;
    s32 width;
    s32 height;
    s32 green;
    s32 blue;
    u8* luminance;
    u8* cb;
    u8* cr;
    s32 value;
    s32 column;
    s32 xEnd;
    s32 yEnd;
    s32 tileWidth;
    s32 redOffset;
    s32 greenOffset;
    u8* texture;
    s32 blueOffset;
    s32 red;
    s32 cbValue;

    luminance = work->convBuf + 4;
    cb = &work->convBuf[260];
    cr = &work->convBuf[324];
    state = work->pState;
    tileWidth = (state->convWidth >> 2) << 1;
    texture = state->pTexBuffer;

    width = 16 / state->scaleFactor;
    height = 16 / state->scaleFactor;
    {
        yEnd = y + height;
        xEnd = x + width;
        lumaSkip = 16 - width;
        chromaSkip = lumaSkip >> 1;
        for (; y < yEnd; y++) {
            output = (u16*)(texture + ((y & 3) << 3));
            tileRow = (y >> 2) * tileWidth;

            for (column = x; column < xEnd; column += 2) {

                {
                    cbValue = (s8)*cb++;
                    crValue = (s8)*cr++;

                }
                {
                    value = *luminance++;
                    redOffset = (crValue * 359) >> 8;
                    red = value + redOffset;
                    greenOffset = -(cbValue * 88 + crValue * 183) >> 8;
                    green = value + greenOffset;
                    blueOffset = (cbValue * 454) >> 8;
                    blue = value + blueOffset;



                    if ((red | green | blue) >> 8) {
                        blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                        green = green > 255 ? 255 : green < 0 ? 0 : green;
                        red = red > 255 ? 255 : red < 0 ? 0 : red;
                    }
                    output[(column & 3) + (((((column) >> 2) << 1) + tileRow) << 4)] =
                        (u8)red + 0x10000 - 0x100;
                    output[(column & 3) + (((((column) >> 2) << 1) + tileRow + 1) << 4)] =
                        ((green & 255) << 8) + (blue & 255);
                }
                {
                    value = *luminance++;
                    green = value + greenOffset;
                    red = value + redOffset;
                    blue = value + blueOffset;
                    if ((red | green | blue) >> 8) {
                        blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                        green = green > 255 ? 255 : green < 0 ? 0 : green;
                        red = red > 255 ? 255 : red < 0 ? 0 : red;
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
    s32 width;
    TMCCJPEGDecState* state = work->pState;
    s32 tileWidth = (state->convWidth >> 2) << 1;
    u8* texture = state->pTexBuffer;
    u8* cr = work->convBuf + 324;
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
        s32 redOffset;
        s32 blueOffset;
        s32 greenOffset;
        ASSERTLINE((x & 1) == 0, __LINE__);
    for (; y < yEnd; y++) {
            u16* output = (u16*)(texture + ((y & 3) << 3));
            s32 tileRow = (y >> 2) * tileWidth;
            s32 column;
            for (column = x; column < xEnd; column += 1) {
                if ((column & 1) == 0) {
                    s32 cbValue = (s8)*cb++;
                    s32 crValue = (s8)*cr++;
                    redOffset = (crValue * 359) >> 8;
                    greenOffset = -(cbValue * 88 + crValue * 183) >> 8;
                    blueOffset = (cbValue * 454) >> 8;
                }
                {
                    s32 red = *luminance++;
                    s32 green = red + greenOffset;
                    s32 blue = red + blueOffset;
                    red = red + redOffset;
                    if ((green | red | blue) >> 8) {
                        blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                        green = green > 255 ? 255 : green < 0 ? 0 : green;
                        red = red > 255 ? 255 : red < 0 ? 0 : red;
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
    u16* output;
    s32 tileRow;
    s32 redOffset;
    TMCCJPEGDecState* state;
    s32 lumaSkip;
    u8* texture;
    u8* luminance;
    u8* cb;
    u8* cr;
    s32 height;
    s32 column;
    s32 chromaSkip;
    s32 width;
    s32 xEnd;
    s32 yEnd;
    s32 cbValue;
    s32 tileWidth;
    s32 blueOffset;
    s32 red;
    s32 crValue;
    s32 value;
    s32 green;
    s32 blue;
    s32 greenOffset;

    luminance = work->convBuf + 4;
    cb = work->convBuf + 132;
    cr = work->convBuf + 196;
    state = work->pState;
    tileWidth = (state->convWidth >> 2) << 1;
    texture = state->pTexBuffer;

    width = 8 / state->scaleFactor;
    height = 16 / state->scaleFactor;
    {
        yEnd = y + height;
        xEnd = x + width;
        lumaSkip = 8 - width;
        chromaSkip = lumaSkip >> 0;
        for (; y < yEnd; y++) {
            tileRow = (y >> 2) * tileWidth;
            output = (u16*)(texture + ((y & 3) << 3));

            for (column = x; column < xEnd; column += 1) {

                {
                    cbValue = (s8)*cb++;
                    crValue = (s8)*cr++;
                    redOffset = (crValue * 359) >> 8;
                    greenOffset = -(cbValue * 88 + crValue * 183) >> 8;
                    blueOffset = (cbValue * 454) >> 8;
                }
                {
                    value = *luminance++;
                    green = value + greenOffset;
                    red = value + redOffset;
                    blue = value + blueOffset;
                    if ((red | green | blue) >> 8) {
                        blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                        green = green > 255 ? 255 : green < 0 ? 0 : green;
                        red = red > 255 ? 255 : red < 0 ? 0 : red;
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
    u16* output;
    s32 tileRow;
    s32 blue;
    u8* texture;
    u8* luminance;
    u8* cb;
    u8* cr;
    s32 column;
    s32 height;
    s32 width;
    s32 xEnd;
    TMCCJPEGDecState* state;
    s32 chromaSkip;
    s32 greenOffset;
    s32 yEnd;
    s32 cbValue;
    s32 tileWidth;
    s32 blueOffset;
    s32 red;
    s8 crValue;
    u8 value;
    s32 green;
    s32 redOffset;
    s32 lumaSkip;

    luminance = work->convBuf + 4;
    cb = work->convBuf + 132;
    cr = work->convBuf + 196;
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
        height = 16 / state->scaleFactor;
    }
    {
        yEnd = y + height;
        xEnd = x + width;
        lumaSkip = 8 - width;
        chromaSkip = lumaSkip >> 0;
        for (; y < yEnd; y++) {
            tileRow = (y >> 2) * tileWidth;
            output = (u16*)(texture + ((y & 3) << 3));
            for (column = x; column < xEnd; column += 1) {

                {
                    cbValue = (s8)*cb++;
                    crValue = (s8)*cr++;
                    redOffset = (crValue * 359) >> 8;
                    greenOffset = -(cbValue * 88 + crValue * 183) >> 8;
                    blueOffset = (cbValue * 454) >> 8;
                }
                {
                    value = *luminance++;
                    green = value + greenOffset;
                    red = value + redOffset;
                    blue = value + blueOffset;
                    if ((red | green | blue) >> 8) {
                        blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                        green = green > 255 ? 255 : green < 0 ? 0 : green;
                        red = red > 255 ? 255 : red < 0 ? 0 : red;
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

static void TMCJPEGDEC_converterYUV444toRGBA8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    u16* output;
    s32 tileRow;
    s32 rowSkip;
    u8* texture;
    u8* luminance;
    u8* cb;
    u8* cr;
    TMCCJPEGDecState* state;
    s32 crValue;
    s32 height;
    s32 width;
    s32 column;
    s32 xEnd;
    s32 yEnd;
    s32 tileWidth;
    s32 row;
    s32 red;
    s32 cbValue;
    s32 green;
    s32 blue;
    s32 value;

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
        tileRow = (row >> 2) * tileWidth;

        output = (u16*)(texture + ((row & 3) << 3));
        for (column = x; column < xEnd; column++) {
            cbValue = (s8)*cb++;
            crValue = (s8)*cr++;
            value = *luminance++;
            green = value + (-(cbValue * 88 + crValue * 183) >> 8);
            red = value + ((crValue * 359) >> 8);
            blue = value + ((cbValue * 454) >> 8);
            if ((red | green | blue) >> 8) {
                blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                green = green > 255 ? 255 : green < 0 ? 0 : green;
                red = red > 255 ? 255 : red < 0 ? 0 : red;
            }
            output[(column & 3) + ((((column >> 2) << 1) + tileRow) << 4)] =
                (u8)red + 0x10000 - 0x100;
            output[(column & 3) + ((((column >> 2) << 1) + tileRow + 1) << 4)] =
                ((green & 255) << 8) + (blue & 255);
        }
        luminance += rowSkip;
        cb += rowSkip;
        cr += rowSkip;
    }
}

static void TMCJPEGDEC_converterYUV444toRGBA8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 rowSkip;
    s32 tileRow;
    u16* output;
    s32 green;
    u8* luminance;
    u8* cb;
    u8* cr;
    s32 column;
    s32 xEnd;
    s32 width;
    s32 yEnd;
    s32 red;
    s32 height;
    s32 tileWidth;
    s32 cbValue;
    s32 crValue;
    s32 value;
    TMCCJPEGDecState* state;
    u8* texture;
    s32 blue;

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
            blue = value + ((cbValue * 454) >> 8);
            if ((blue | red | green) >> 8) {
                blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                green = green > 255 ? 255 : green < 0 ? 0 : green;
                red = red > 255 ? 255 : red < 0 ? 0 : red;
            }
            output[(column & 3) + ((((column >> 2) << 1) + tileRow) << 4)] =
                (u8)red + 0x10000 - 0x100;
            output[(column & 3) + ((((column >> 2) << 1) + tileRow + 1) << 4)] =
                (blue & 255) + ((green & 255) << 8);
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
