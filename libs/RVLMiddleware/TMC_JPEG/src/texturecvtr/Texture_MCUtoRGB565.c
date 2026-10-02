#include <revolution/os.h>
#include <tmc_jpeg_internal.h>

static void TMCJPEGDEC_converterYUV411toRGB565(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV411toRGB565edge(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV422toRGB565(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV422toRGB565edge(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV420toRGB565(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV420toRGB565edge(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV211toRGB565(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV211toRGB565edge(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV444toRGB565(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV444toRGB565edge(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV400toRGB565(TMCCJPEGDecWork*, s32, s32);
static void TMCJPEGDEC_converterYUV400toRGB565edge(TMCCJPEGDecWork*, s32, s32);

s32 TMCJPEGDEC_set_converterRGB565(TMCCJPEGDecWork* work) {
    s32 componentCount;
    TMCCJPEGDecState* state;

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
            firstRow = work->convBuf + 4;
            work->pConverterFunc = TMCJPEGDEC_converterYUV411toRGB565;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV411toRGB565edge;
            secondRow = firstRow + mode;
            thirdRow = secondRow + mode;
            fourthRow = thirdRow + mode;
            cbBlock = work->convBuf + 260;
            crBlock = work->convBuf + 324;
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
            firstRow = work->convBuf + 4;
            work->pConverterFunc = TMCJPEGDEC_converterYUV422toRGB565;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV422toRGB565edge;
            secondRow = firstRow + mode;
            cbBlock = work->convBuf + 132;
            crBlock = work->convBuf + 196;
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
            firstRow = work->convBuf + 4;
            work->pConverterFunc = TMCJPEGDEC_converterYUV420toRGB565;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV420toRGB565edge;
            secondRow = firstRow + mode;
            thirdRow = firstRow + mode * 16;
            fourthRow = thirdRow + mode;
            cbBlock = work->convBuf + 260;
            crBlock = work->convBuf + 324;
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
            firstRow = work->convBuf + 4;
            work->pConverterFunc = TMCJPEGDEC_converterYUV211toRGB565;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV211toRGB565edge;
            secondRow = firstRow + mode * 8;
            cbBlock = work->convBuf + 132;
            crBlock = work->convBuf + 196;
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
            converter = TMCJPEGDEC_converterYUV444toRGB565;
            edgeConverter = TMCJPEGDEC_converterYUV444toRGB565edge;
            work->pConverterFunc = converter;
            work->pConverterFuncEdge = edgeConverter;
            work->pConvRowPtrs[0] = work->convBuf + 4;
            work->pConvRowPtrs[5] = work->convBuf + 0x44;
            work->pConvRowPtrs[6] = work->convBuf + 0x84;
            work->pitch = 0x08;
            work->converterFlags = 0;
            break;
        }
        case 5: {
            TMCConverterFunc* converter;
            TMCConverterFunc* edgeConverter;
            converter = TMCJPEGDEC_converterYUV400toRGB565;
            edgeConverter = TMCJPEGDEC_converterYUV400toRGB565edge;
            work->pConverterFunc = converter;
            work->pConverterFuncEdge = edgeConverter;
            work->pConvRowPtrs[0] = work->convBuf + 4;
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

static void TMCJPEGDEC_converterYUV411toRGB565(TMCCJPEGDecWork* work, s32 x, s32 y) {
    u16* output;
    s32 lumaSkip;
    s32 cbValue;
    s32 blue;
    TMCCJPEGDecState* state;
    u32 tileWidth;
    s32 crValue;
    s32 width;
    s32 height;
    u8* cb;
    u8* texture;
    u8* luminance;
    s32 chromaSkip;
    u8* cr;
    s32 column;
    s32 xEnd;
    s32 yEnd;
    s32 redOffset;
    s32 tileRow;
    s32 blueOffset;
    u8 value;
    s32 red;
    s32 greenOffset;
    s32 green;

    luminance = work->convBuf + 4;
    cb = &work->convBuf[260];
    cr = &work->convBuf[324];
    state = work->pState;
    tileWidth = state->convWidth >> 2;
    texture = state->pTexBuffer;
    width = 32 / state->scaleFactor;
    height = 8 / state->scaleFactor;
    xEnd = x + width;
    yEnd = y + height;
    lumaSkip = 32 - width;
    chromaSkip = lumaSkip >> 2;
    for (; y < yEnd; y++) {
        tileRow = (y >> 2) * tileWidth;
        output = (u16*)(texture + ((y & 3) << 3));
        for (column = x; column < xEnd; column += 4) {
            cbValue = (s8)*cb++;
            crValue = (s8)*cr++;
            redOffset = (crValue * 359) >> 8;
            greenOffset = -(cbValue * 88 + crValue * 183) >> 8;
            blueOffset = (cbValue * 454) >> 8;
            value = *luminance++;
            red = value + redOffset;
            green = value + greenOffset;
            blue = value + blueOffset;
            if ((blue | red | green) >> 8) {
                blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                green = green > 255 ? 255 : green < 0 ? 0 : green;
                red = red > 255 ? 255 : red < 0 ? 0 : red;
            }
            output[(column & 3) + (((column >> 2) + tileRow) << 4)] = ((blue & 0xF8) >> 3) + ((red & 0xF8) << 8) + ((green & 0xFC) << 3);
            value = *luminance++;
            red = value + redOffset;
            green = value + greenOffset;
            blue = value + blueOffset;
            if ((blue | red | green) >> 8) {
                blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                green = green > 255 ? 255 : green < 0 ? 0 : green;
                red = red > 255 ? 255 : red < 0 ? 0 : red;
            }
            output[((column + 1) & 3) + ((((column + 1) >> 2) + tileRow) << 4)] = ((blue & 0xF8) >> 3) + ((red & 0xF8) << 8) + ((green & 0xFC) << 3);
            value = *luminance++;
            red = value + redOffset;
            green = value + greenOffset;
            blue = value + blueOffset;
            if ((blue | red | green) >> 8) {
                blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                green = green > 255 ? 255 : green < 0 ? 0 : green;
                red = red > 255 ? 255 : red < 0 ? 0 : red;
            }
            output[((column + 2) & 3) + ((((column + 2) >> 2) + tileRow) << 4)] = ((blue & 0xF8) >> 3) + ((red & 0xF8) << 8) + ((green & 0xFC) << 3);
            value = *luminance++;
            red = value + redOffset;
            green = value + greenOffset;
            blue = value + blueOffset;
            if ((blue | red | green) >> 8) {
                blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                green = green > 255 ? 255 : green < 0 ? 0 : green;
                red = red > 255 ? 255 : red < 0 ? 0 : red;
            }
            output[((column + 3) & 3) + ((((column + 3) >> 2) + tileRow) << 4)] = ((blue & 0xF8) >> 3) + ((red & 0xF8) << 8) + ((green & 0xFC) << 3);
        }
        luminance += lumaSkip;
        cb += chromaSkip;
        cr += chromaSkip;
    }
}

static void TMCJPEGDEC_converterYUV411toRGB565edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 column;
    u8* luminance = work->convBuf + 4;
    s8* cb = (s8*)&work->convBuf[260];
    s8* cr = (s8*)&work->convBuf[324];
    TMCCJPEGDecState* state = work->pState;
    u32 tileWidth = state->convWidth >> 2;
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
        s32 xEnd = x + width;
        s32 yEnd = y + height;
        s32 lumaSkip = 32 - width;
        s32 chromaSkip = lumaSkip >> 2;
        s32 redOffset, greenOffset, blueOffset;
        ASSERTLINE((x & 3) == 0, __LINE__);
        for (; y < yEnd; y++) {
            s32 tileRow = (y >> 2) * tileWidth;
            u16* output = (u16*)(texture + ((y & 3) << 3));
            for (column = x; column < xEnd; column += 1) {
                if ((column & 3) == 0) {
                    s32 cbValue = *cb++;
                    s32 crValue = *cr++;
                    redOffset = (crValue * 359) >> 8;
                    greenOffset = -(cbValue * 88 + crValue * 183) >> 8;
                    blueOffset = (cbValue * 454) >> 8;
                }
                {
                    s32 value = *luminance++;
                    s32 green = value + greenOffset;
                    s32 red = value + redOffset;
                    s32 blue = value + blueOffset;
                    if ((blue | red | green) >> 8) {
                        blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                        green = green > 255 ? 255 : green < 0 ? 0 : green;
                        red = red > 255 ? 255 : red < 0 ? 0 : red;
                    }
                    output[(column & 3) + ((((column) >> 2) + tileRow) << 4)] =
                        ((blue & 0xF8) >> 3) + ((red & 0xF8) << 8) + ((green & 0xFC) << 3);
                }
            }
            luminance += lumaSkip;
            cb += chromaSkip;
            cr += chromaSkip;
        }
    }
}

static void TMCJPEGDEC_converterYUV422toRGB565(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 chromaSkip;
    s32 width;
    s32 blue;
    s32 lumaSkip;
    s32 red;
    s32 tileRow;
    u16* output;
    u32 tileWidth;
    u8* texture;
    TMCCJPEGDecState* state;
    s32 crValue;
    u8* luminance;
    u8* cb;
    u8* cr;
    s32 height;
    s32 column;
    s32 cbValue;
    s32 xEnd;
    s32 yEnd;
    s32 redOffset;
    s32 greenOffset;
    s32 blueOffset;
    s32 green;

    luminance = work->convBuf + 4;
    cb = &work->convBuf[132];
    cr = &work->convBuf[196];
    state = work->pState;
    tileWidth = state->convWidth >> 2;
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
            blue = *luminance++;
            green = blue + greenOffset;
            red = blue + redOffset;


            blue = blue + blueOffset;
            if ((blue | red | green) >> 8) {
                blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                green = green > 255 ? 255 : green < 0 ? 0 : green;
                red = red > 255 ? 255 : red < 0 ? 0 : red;
            }
            output[(column & 3) + (((column >> 2) + tileRow) << 4)] = ((blue & 0xF8) >> 3) + (((red & 0xF8) << 8) + ((green & 0xFC) << 3));
            blue = *luminance++;
            green = blue + greenOffset;
            red = blue + redOffset;


            blue = blue + blueOffset;
            if ((blue | red | green) >> 8) {
                blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                green = green > 255 ? 255 : green < 0 ? 0 : green;
                red = red > 255 ? 255 : red < 0 ? 0 : red;
            }
            output[((column + 1) & 3) + ((((column + 1) >> 2) + tileRow) << 4)] = ((blue & 0xF8) >> 3) + (((red & 0xF8) << 8) + ((green & 0xFC) << 3));
        }
        luminance += lumaSkip;
        cb += chromaSkip;
        cr += chromaSkip;
    }
}

static void TMCJPEGDEC_converterYUV422toRGB565edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 lumaSkip;
    s32 chromaSkip;
    u16* output;
    s32 tileRow;
    u8* texture;
    u8* luminance;
    u8* cb;
    u8* cr;
    s32 column;
    s32 xEnd;
    s32 height;
    s32 cbValue;
    s32 yEnd;
    TMCCJPEGDecState* state;
    s32 width;
    u32 tileWidth;
    s32 red;
    s32 redOffset;
    s32 greenOffset;
    s8 crValue;
    s32 blue;
    s32 blueOffset;
    s32 green;
    s32 value;

    luminance = work->convBuf + 4;
    cb = &work->convBuf[132];
    cr = &work->convBuf[196];
    state = work->pState;
    tileWidth = state->convWidth >> 2;
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
            output[(column & 3) + (((column >> 2) + tileRow) << 4)] = ((blue & 0xF8) >> 3) + (((red & 0xF8) << 8) + ((green & 0xFC) << 3));
        }
        luminance += lumaSkip;
        cb += chromaSkip;
        cr += chromaSkip;
    }
}

static void TMCJPEGDEC_converterYUV420toRGB565(TMCCJPEGDecWork* work, s32 x, s32 y) {
    u16* output;
    s32 width;
    s32 redOffset;
    s32 green;
    u32 tileWidth;
    u8* texture;
    s32 chromaSkip;
    s32 height;
    s32 yEnd;
    u8* luminance;
    s32 crValue;
    s32 value;
    u8* cb;
    s32 xEnd;
    s32 column;
    u8* cr;
    s32 greenOffset;
    s32 tileRow;
    s32 cbValue;
    s32 lumaSkip;
    s32 blueOffset;
    s32 red;
    TMCCJPEGDecState* state;
    s32 blue;

    luminance = work->convBuf + 4;
    cb = work->convBuf + 260;
    cr = work->convBuf + 324;
    state = work->pState;
    tileWidth = state->convWidth >> 2;
    texture = state->pTexBuffer;

    width = 16 / state->scaleFactor;
    height = 16 / state->scaleFactor;
    {
        xEnd = x + width;
        yEnd = y + height;
        lumaSkip = 16 - width;
        chromaSkip = lumaSkip >> 1;
        for (; y < yEnd; y++) {
            tileRow = (y >> 2) * tileWidth;
            output = (u16*)(texture + ((y & 3) << 3));

            for (column = x; column < xEnd; column += 2) {

                {
                    cbValue = (s8)*cb++;
                    crValue = (s8)*cr++;
                    redOffset = (crValue * 359) >> 8;
                    greenOffset = -(cbValue * 88 + crValue * 183) >> 8;
                    blueOffset = (cbValue * 454) >> 8;
                }
                {
                    value = *luminance++;
                    red = value + redOffset;
                    green = value + greenOffset;
                    blue = value + blueOffset;
                    if ((blue | red | green) >> 8) {
                        blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                        green = green > 255 ? 255 : green < 0 ? 0 : green;
                        red = red > 255 ? 255 : red < 0 ? 0 : red;
                    }
                    output[(column & 3) + ((((column) >> 2) + tileRow) << 4)] =
                        ((blue & 0xF8) >> 3) + ((red & 0xF8) << 8) + ((green & 0xFC) << 3);
                }
                {
                    value = *luminance++;
                    red = value + redOffset;
                    green = value + greenOffset;
                    blue = value + blueOffset;
                    if ((blue | red | green) >> 8) {
                        blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                        green = green > 255 ? 255 : green < 0 ? 0 : green;
                        red = red > 255 ? 255 : red < 0 ? 0 : red;
                    }
                    output[(column + 1 & 3) + ((((column + 1) >> 2) + tileRow) << 4)] =
                        ((blue & 0xF8) >> 3) + ((red & 0xF8) << 8) + ((green & 0xFC) << 3);
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

static void TMCJPEGDEC_converterYUV420toRGB565edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    u16* output;
    s8 crValue;
    s32 tileRow;
    u8* texture;
    u8* luminance;
    s8* cb;
    s32 width;
    s8* cr;
    s32 column;
    s32 xEnd;
    s8 cbValue;
    s32 yEnd;
    s32 red;
    s32 blue;
    u32 tileWidth;
    s32 height;
    TMCCJPEGDecState* state;
    s32 green;
    s32 lumaSkip;
    s32 chromaSkip;
    s32 redOffset;
    s32 greenOffset;
    s32 blueOffset;

    luminance = work->convBuf + 4;
    cb = (s8*)&work->convBuf[260];
    cr = (s8*)&work->convBuf[324];
    state = work->pState;
    tileWidth = state->convWidth >> 2;
    texture = state->pTexBuffer;
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
    lumaSkip = 16 - width;
    chromaSkip = lumaSkip >> 1;
    ASSERTLINE((x & 1) == 0, __LINE__);
    for (; y < yEnd; y++) {
        output = (u16*)(texture + ((y & 3) << 3));
        tileRow = (y >> 2) * tileWidth;
        for (column = x; column < xEnd; column += 1) {
            if ((column & 1) == 0) {
                cbValue = *cb++;
                crValue = *cr++;
                redOffset = (crValue * 359) >> 8;
                greenOffset = -(cbValue * 88 + crValue * 183) >> 8;
                blueOffset = (cbValue * 454) >> 8;
            }
            blue = *luminance++;
            red = blue + redOffset;
            green = blue + greenOffset;
            blue = blue + blueOffset;
            if ((blue | red | green) >> 8) {
                blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                green = green > 255 ? 255 : green < 0 ? 0 : green;
                red = red > 255 ? 255 : red < 0 ? 0 : red;
            }
            output[(column & 3) + (((column >> 2) + tileRow) << 4)] = ((blue & 0xF8) >> 3) + ((red & 0xF8) << 8) + ((green & 0xFC) << 3);
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

static void TMCJPEGDEC_converterYUV211toRGB565(TMCCJPEGDecWork* work, s32 x, s32 y) {
    u16* output;
    s32 lumaSkip;
    s32 tileRow;
    u8* texture;
    u8* luminance;
    s32 red;
    u8* cb;
    u8* cr;
    s32 column;
    s32 height;
    s32 width;
    s32 greenOffset;
    s32 redOffset;
    s32 cbValue;
    s32 blueOffset;
    s8 crValue;
    s32 xEnd;
    s32 value;
    s32 yEnd;
    u32 tileWidth;
    TMCCJPEGDecState* state;
    s32 blue;
    s32 green;
    s32 chromaSkip;

    luminance = work->convBuf + 4;
    cb = work->convBuf + 132;
    cr = work->convBuf + 196;
    state = work->pState;
    tileWidth = state->convWidth >> 2;
    texture = state->pTexBuffer;

    width = 8 / state->scaleFactor;
    height = 16 / state->scaleFactor;
    {
        xEnd = x + width;
        yEnd = y + height;
        lumaSkip = 8 - width;
        chromaSkip = lumaSkip >> 0;
        for (; y < yEnd; y++) {
            output = (u16*)(texture + ((y & 3) << 3));
            tileRow = (y >> 2) * tileWidth;
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
                    output[(column & 3) + ((((column) >> 2) + tileRow) << 4)] =
                        ((blue & 0xF8) >> 3) + (((red & 0xF8) << 8) + ((green & 0xFC) << 3));
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

static void TMCJPEGDEC_converterYUV211toRGB565edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 lumaSkip;
    u16* output;
    s32 tileRow;
    s32 greenOffset;
    u8* texture;
    u8* luminance;
    u8* cb;
    s32 redOffset;
    u8* cr;
    s32 column;
    s32 width;
    TMCCJPEGDecState* state;
    s32 xEnd;
    s8 crValue;
    s32 value;
    s32 red;
    s32 blueOffset;
    s32 yEnd;
    u32 tileWidth;
    s32 blue;
    s32 cbValue;
    s32 green;
    s32 chromaSkip;
    s32 height;

    luminance = work->convBuf + 4;
    cb = work->convBuf + 132;
    cr = work->convBuf + 196;
    state = work->pState;
    tileWidth = state->convWidth >> 2;
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
        xEnd = x + width;
        yEnd = y + height;
        lumaSkip = 8 - width;
        chromaSkip = lumaSkip >> 0;
        for (; y < yEnd; y++) {
            output = (u16*)(texture + ((y & 3) << 3));
            tileRow = (y >> 2) * tileWidth;
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
                    output[(column & 3) + ((((column) >> 2) + tileRow) << 4)] =
                        ((blue & 0xF8) >> 3) + (((red & 0xF8) << 8) + ((green & 0xFC) << 3));
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

static void TMCJPEGDEC_converterYUV444toRGB565(TMCCJPEGDecWork* work, s32 x, s32 y) {
    u16* output;
    s8 crValue;
    TMCCJPEGDecState* state;
    s32 rowSkip;
    s32 width;
    s32 tileRow;
    u8* texture;
    u8* luminance;
    u8* cb;
    u8* cr;
    s32 value;
    s32 column;
    s32 xEnd;
    s32 cbValue;
    s32 yEnd;
    u32 tileWidth;
    s32 green;
    s32 blue;
    s32 red;
    s32 height;

    luminance = work->convBuf + 4;
    cb = work->convBuf + 68;
    cr = work->convBuf + 132;
    state = work->pState;
    tileWidth = state->convWidth >> 2;
    texture = state->pTexBuffer;
    width = 8 / state->scaleFactor;
    height = 8 / state->scaleFactor;
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
            if ((blue | green | red) >> 8) {
                blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                green = green > 255 ? 255 : green < 0 ? 0 : green;
                red = red > 255 ? 255 : red < 0 ? 0 : red;
            }
            output[(column & 3) + (((column >> 2) + tileRow) << 4)] =
                ((blue & 0xF8) >> 3) + ((red & 0xF8) << 8) + ((green & 0xFC) << 3);
        }
        luminance += rowSkip;
        cb += rowSkip;
        cr += rowSkip;
    }
}

static void TMCJPEGDEC_converterYUV444toRGB565edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 rowSkip;
    u16* output;
    s8 crValue;
    s32 tileRow;
    u8* texture;
    u8* luminance;
    u8* cb;
    s32 width;
    u8* cr;
    s32 column;
    s32 xEnd;
    s32 cbValue;
    s32 yEnd;
    s32 red;
    s32 value;
    s32 blue;
    u32 tileWidth;
    s32 height;
    TMCCJPEGDecState* state;
    s32 green;

    luminance = work->convBuf + 4;
    cb = work->convBuf + 68;
    cr = work->convBuf + 132;
    state = work->pState;
    tileWidth = state->convWidth >> 2;
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
            if ((red | green | blue) >> 8) {
                blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                green = green > 255 ? 255 : green < 0 ? 0 : green;
                red = red > 255 ? 255 : red < 0 ? 0 : red;
            }
            output[(column & 3) + (((column >> 2) + tileRow) << 4)] =
                ((blue & 0xF8) >> 3) + (((red & 0xF8) << 8) + ((green & 0xFC) << 3));
        }
        luminance += rowSkip;
        cb += rowSkip;
        cr += rowSkip;
    }
}

static void TMCJPEGDEC_converterYUV400toRGB565(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 value;
    u16* output;
    s32 tileRow;
    u8* texture;
    u8* luminance;
    s32 column;
    s32 xEnd;
    s32 green;
    s32 blue;
    TMCCJPEGDecState* state;
    s32 row;
    s32 yEnd;
    s32 height;
    s32 width;
    u32 tileWidth;

    state = work->pState;
    texture = state->pTexBuffer;
    luminance = work->convBuf + 4;
    tileWidth = state->convWidth >> 2;
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
                output[(column & 3) + (((column >> 2) + tileRow) << 4)] =
                    ((blue & 0xF8) >> 3) + (((value & 0xF8) << 8) + ((green & 0xFC) << 3));
            }
            luminance += width;
        }
    }
}

static void TMCJPEGDEC_converterYUV400toRGB565edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 value;
    u16* output;
    s32 tileRow;
    u8* texture;
    u8* luminance;
    s32 column;
    s32 xEnd;
    s32 green;
    s32 blue;
    TMCCJPEGDecState* state;
    s32 row;
    s32 yEnd;
    s32 height;
    s32 width;
    u32 tileWidth;

    state = work->pState;
    texture = state->pTexBuffer;
    luminance = work->convBuf + 4;
    tileWidth = state->convWidth >> 2;
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
                output[(column & 3) + (((column >> 2) + tileRow) << 4)] =
                    ((blue & 0xF8) >> 3) + (((value & 0xF8) << 8) + ((green & 0xFC) << 3));
            }
            luminance += width;
        }
    }
}
