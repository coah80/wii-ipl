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

#pragma push
#pragma optimization_level 1
s32 TMCJPEGDEC_set_converterRGBA8(TMCCJPEGDecWork* work) {
    u8 mode411;
    u8* crBlock411;
    u8* cbBlock411;
    u8* fourthRow411;
    u8* thirdRow411;
    u8* secondRow411;
    u8* firstRow411;
    TMCConverterFunc* edgeConverter411;
    TMCConverterFunc* converter411;

    u8 mode422;
    u8* crBlock422;
    u8* cbBlock422;
    u8* secondRow422;
    u8* firstRow422;
    TMCConverterFunc* edgeConverter422;
    TMCConverterFunc* converter422;

    u8 mode420;
    u8* crBlock420;
    u8* cbBlock420;
    u8* fourthRow420;
    u8* thirdRow420;
    u8* secondRow420;
    u8* firstRow420;
    TMCConverterFunc* edgeConverter420;
    TMCConverterFunc* converter420;

    u8* buffer;
    s32 componentCount;
    TMCCJPEGDecState* state;

    buffer = work->convBuf;
    componentCount = work->componentCount;
    state = work->pState;

    switch (componentCount) {
        case 0: {
            mode411 = work->idctMode;
            firstRow411 = buffer + 4;
            converter411 = TMCJPEGDEC_converterYUV411toRGBA8;
            edgeConverter411 = TMCJPEGDEC_converterYUV411toRGBA8edge;
            secondRow411 = firstRow411 + mode411;
            thirdRow411 = secondRow411 + mode411;
            fourthRow411 = thirdRow411 + mode411;
            cbBlock411 = buffer + 260;
            crBlock411 = buffer + 324;
            work->pConverterFunc = converter411;
            work->pConverterFuncEdge = edgeConverter411;
            work->pConvRowPtrs[0] = firstRow411;
            work->pConvRowPtrs[1] = secondRow411;
            work->pConvRowPtrs[2] = thirdRow411;
            work->pConvRowPtrs[3] = fourthRow411;
            work->pConvRowPtrs[5] = cbBlock411;
            work->pConvRowPtrs[6] = crBlock411;
            work->pitch = 32;
            work->converterFlags = 0;
            break;
        }
        case 1: {
            mode422 = work->idctMode;
            firstRow422 = buffer + 4;
            converter422 = TMCJPEGDEC_converterYUV422toRGBA8;
            edgeConverter422 = TMCJPEGDEC_converterYUV422toRGBA8edge;
            secondRow422 = firstRow422 + mode422;
            cbBlock422 = buffer + 132;
            crBlock422 = buffer + 196;
            work->pConverterFunc = converter422;
            work->pConverterFuncEdge = edgeConverter422;
            work->pConvRowPtrs[0] = firstRow422;
            work->pConvRowPtrs[1] = secondRow422;
            work->pConvRowPtrs[5] = cbBlock422;
            work->pConvRowPtrs[6] = crBlock422;
            work->pitch = 16;
            work->converterFlags = 0;
            break;
        }
        case 2: {
            mode420 = work->idctMode;
            firstRow420 = buffer + 4;
            converter420 = TMCJPEGDEC_converterYUV420toRGBA8;
            edgeConverter420 = TMCJPEGDEC_converterYUV420toRGBA8edge;
            secondRow420 = firstRow420 + mode420;
            thirdRow420 = firstRow420 + mode420 * 16;
            fourthRow420 = thirdRow420 + mode420;
            cbBlock420 = buffer + 260;
            crBlock420 = buffer + 324;
            work->pConverterFunc = converter420;
            work->pConverterFuncEdge = edgeConverter420;
            work->pConvRowPtrs[0] = firstRow420;
            work->pConvRowPtrs[1] = secondRow420;
            work->pConvRowPtrs[2] = thirdRow420;
            work->pConvRowPtrs[3] = fourthRow420;
            work->pConvRowPtrs[5] = cbBlock420;
            work->pConvRowPtrs[6] = crBlock420;
            work->pitch = 16;
            work->converterFlags = 0;
            break;
        }
        case 3: {
            u32 mode;
            u8* crBlock;
            u8* cbBlock;
            u8* secondRow;
            u8* firstRow;
            TMCConverterFunc* edgeConverter;
            TMCConverterFunc* converter;
            mode = work->idctMode;
            firstRow = buffer + 4;
            converter = TMCJPEGDEC_converterYUV211toRGBA8;
            edgeConverter = TMCJPEGDEC_converterYUV211toRGBA8edge;
            secondRow = firstRow + mode * 8;
            cbBlock = buffer + 132;
            crBlock = buffer + 196;
            work->pConverterFunc = converter;
            work->pConverterFuncEdge = edgeConverter;
            work->pConvRowPtrs[0] = firstRow;
            work->pConvRowPtrs[1] = secondRow;
            work->pConvRowPtrs[5] = cbBlock;
            work->pConvRowPtrs[6] = crBlock;
            work->pitch = 8;
            work->converterFlags = 0;
            break;
        }
        case 4: {
            TMCConverterFunc* edgeConverter;
            TMCConverterFunc* converter;
            converter = TMCJPEGDEC_converterYUV444toRGBA8;
            edgeConverter = TMCJPEGDEC_converterYUV444toRGBA8edge;
            work->pConverterFunc = converter;
            work->pConverterFuncEdge = edgeConverter;
            work->pConvRowPtrs[0] = buffer + 4;
            work->pConvRowPtrs[5] = buffer + 0x44;
            work->pConvRowPtrs[6] = buffer + 0x84;
            work->pitch = 0x08;
            work->converterFlags = 0;
            break;
        }
        case 5: {
            TMCConverterFunc* edgeConverter;
            TMCConverterFunc* converter;
            converter = TMCJPEGDEC_converterYUV400toRGBA8;
            edgeConverter = TMCJPEGDEC_converterYUV400toRGBA8edge;
            work->pConverterFunc = converter;
            work->pConverterFuncEdge = edgeConverter;
            work->pConvRowPtrs[0] = buffer + 4;
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
        s32 roundedWidth;
        s32 heightPadding;

        roundedWidth = (u32)width / 4 + (width % 4 != 0);
        heightPadding = height % 4 != 0;
        state->convWidth = roundedWidth * 4;
        state->convHeight = ((u32)height / 4 + heightPadding) * 4;
    }
    return 0;
}

#pragma pop

static void TMCJPEGDEC_converterYUV411toRGBA8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    u16* output;
    s32 tileRow;
    s32 secondGreen;
    s32 thirdGreen;
    s32 fourthBlue;
    s32 columnInTile;
    s32 secondColumnInTile;
    s32 thirdColumnInTile;
    s32 fourthColumnInTile;
    s32 red;
    s32 secondBlue;
    s32 thirdBlue;
    s32 fourthGreen;
    s32 green;
    s32 secondRed;
    s32 thirdRed;
    s32 fourthRed;
    u8* texture;
    u8* luminance;
    u8* cb;
    u8* cr;
    s32 column;
    s32 xEnd;
    s32 yEnd;
    s32 tileWidth;
    s32 redOffset;
    s32 greenOffset;
    s32 blueOffset;
    s32 blue;
    s32 value;
    TMCCJPEGDecState* state;
    s32 width;
    s32 height;
    s8 crValue;
    s32 cbValue;

    luminance = work->convBuf + 4;
    cb = &work->convBuf[260];
    cr = &work->convBuf[324];
    state = work->pState;
    tileWidth = (state->convWidth >> 2) << 1;
    texture = state->pTexBuffer;
    width = 32 / state->scaleFactor;
    height = 8 / state->scaleFactor;
    xEnd = x + width;
    yEnd = y + height;
    for (; y < yEnd; y++) {
        for (column = x; column < xEnd; column += 4) {
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
            columnInTile = column & 3;
            (output = (u16*)(texture + ((y & 3) << 3)))[
                columnInTile + ((((column >> 2) << 1) +
                                 (tileRow = (y >> 2) * tileWidth)) << 4)] = (u8)red + 0x10000 - 0x100;
            output[columnInTile + ((((column >> 2) << 1) + (tileRow + 1)) << 4)] = ((green & 255) << 8) + (blue & 255);
            value = *luminance++;
            secondGreen = value + greenOffset;
            secondRed = value + redOffset;
            secondBlue = value + blueOffset;
            if ((secondRed | secondGreen | secondBlue) >> 8) {
                secondBlue = secondBlue > 255 ? 255 : secondBlue < 0 ? 0 : secondBlue;
                secondGreen = secondGreen > 255 ? 255 : secondGreen < 0 ? 0 : secondGreen;
                secondRed = secondRed > 255 ? 255 : secondRed < 0 ? 0 : secondRed;
            }
            secondColumnInTile = (column + 1) & 3;
            output[secondColumnInTile + (((((column + 1) >> 2) << 1) + tileRow) << 4)] = (u8)secondRed + 0x10000 - 0x100;
            output[secondColumnInTile + (((((column + 1) >> 2) << 1) + (tileRow + 1)) << 4)] = ((secondGreen & 255) << 8) + (secondBlue & 255);
            value = *luminance++;
            thirdGreen = value + greenOffset;
            thirdRed = value + redOffset;
            thirdBlue = value + blueOffset;
            if ((thirdRed | thirdGreen | thirdBlue) >> 8) {
                thirdBlue = thirdBlue > 255 ? 255 : thirdBlue < 0 ? 0 : thirdBlue;
                thirdGreen = thirdGreen > 255 ? 255 : thirdGreen < 0 ? 0 : thirdGreen;
                thirdRed = thirdRed > 255 ? 255 : thirdRed < 0 ? 0 : thirdRed;
            }
            thirdColumnInTile = (column + 2) & 3;
            output[thirdColumnInTile + (((((column + 2) >> 2) << 1) + tileRow) << 4)] = (u8)thirdRed + 0x10000 - 0x100;
            output[thirdColumnInTile + (((((column + 2) >> 2) << 1) + (tileRow + 1)) << 4)] = ((thirdGreen & 255) << 8) + (thirdBlue & 255);
            value = *luminance++;
            fourthGreen = value + greenOffset;
            fourthRed = value + redOffset;
            fourthBlue = value + blueOffset;
            if ((fourthRed | fourthGreen | fourthBlue) >> 8) {
                fourthBlue = fourthBlue > 255 ? 255 : fourthBlue < 0 ? 0 : fourthBlue;
                fourthGreen = fourthGreen > 255 ? 255 : fourthGreen < 0 ? 0 : fourthGreen;
                fourthRed = fourthRed > 255 ? 255 : fourthRed < 0 ? 0 : fourthRed;
            }
            fourthColumnInTile = (column + 3) & 3;
            output[fourthColumnInTile + (((((column + 3) >> 2) << 1) + tileRow) << 4)] = (u8)fourthRed + 0x10000 - 0x100;
            output[fourthColumnInTile + (((((column + 3) >> 2) << 1) + (tileRow + 1)) << 4)] = ((fourthGreen & 255) << 8) + (fourthBlue & 255);
        }
        luminance += (32 - width);
        cb += ((32 - width) >> 2);
        cr += ((32 - width) >> 2);
    }
}

static void TMCJPEGDEC_converterYUV411toRGBA8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 lumaSkip;
    s32 red;
    s32 chromaSkip;
    u16* output;
    s32 tileRow;
    s32 columnInTile;
    u8* texture;
    u8* luminance;
    u8* cb;
    u8* cr;
    s32 column;
    s32 xEnd;
    s32 yEnd;
    s32 tileWidth;
    s32 redOffset;
    s32 greenOffset;
    s32 blueOffset;
    s32 green;
    s32 blue;
    s32 value;
    s32 width;
    s32 height;
    TMCCJPEGDecState* state;
    s32 cbValue;
    s8 crValue;

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
        output = (u16*)(texture + ((y & 3) << 3));
        tileRow = (y >> 2) * tileWidth;
        for (column = x; column < xEnd; column += 1) {
            columnInTile = column & 3;
            if (columnInTile == 0) {
                cbValue = (s8)*cb++;
                crValue = (s8)*cr++;
                redOffset = (crValue * 359) >> 8;
                greenOffset = -(cbValue * 88 + crValue * 183) >> 8;
                blueOffset = (cbValue * 454) >> 8;
            }
            value = *luminance++;
            red = value + redOffset;
            green = value + greenOffset;
            blue = value + blueOffset;
            if ((red | green | blue) >> 8) {
                blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                green = green > 255 ? 255 : green < 0 ? 0 : green;
                red = red > 255 ? 255 : red < 0 ? 0 : red;
            }
            output[columnInTile + ((((column >> 2) << 1) + tileRow) << 4)] = (u8)red + 0x10000 - 0x100;
            output[columnInTile + ((((column >> 2) << 1) + (tileRow + 1)) << 4)] = ((green & 255) << 8) + (blue & 255);
        }
        luminance += lumaSkip;
        cb += chromaSkip;
        cr += chromaSkip;
    }
}

static void TMCJPEGDEC_converterYUV422toRGBA8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 lumaSkip;
    s32 chromaSkip;
    u16* output;
    s32 tileRow;
    s32 red;
    s32 secondBlue;
    s32 columnInTile;
    u8* texture;
    u8* luminance;
    u8* cb;
    u8* cr;
    s32 column;
    s32 xEnd;
    s32 yEnd;
    s32 tileWidth;
    s32 redOffset;
    s32 greenOffset;
    s32 blueOffset;
    s32 green;
    s32 blue;
    s32 secondGreen;
    s32 secondRed;
    s32 secondColumnInTile;
    s32 value;
    TMCCJPEGDecState* state;
    s32 width;
    s32 height;
    s8 crValue;
    s32 cbValue;

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
            columnInTile = column & 3;
            output[columnInTile + ((((column >> 2) << 1) + tileRow) << 4)] = (u8)red + 0x10000 - 0x100;
            output[columnInTile + ((((column >> 2) << 1) + (tileRow + 1)) << 4)] = ((green & 255) << 8) + (blue & 255);
            value = *luminance++;
            secondGreen = value + greenOffset;
            secondRed = value + redOffset;
            secondBlue = value + blueOffset;
            if ((secondRed | secondGreen | secondBlue) >> 8) {
                secondBlue = secondBlue > 255 ? 255 : secondBlue < 0 ? 0 : secondBlue;
                secondGreen = secondGreen > 255 ? 255 : secondGreen < 0 ? 0 : secondGreen;
                secondRed = secondRed > 255 ? 255 : secondRed < 0 ? 0 : secondRed;
            }
            secondColumnInTile = (column + 1) & 3;
            output[secondColumnInTile + (((((column + 1) >> 2) << 1) + tileRow) << 4)] = (u8)secondRed + 0x10000 - 0x100;
            output[secondColumnInTile + (((((column + 1) >> 2) << 1) + (tileRow + 1)) << 4)] = ((secondGreen & 255) << 8) + (secondBlue & 255);
        }
        luminance += lumaSkip;
        cb += chromaSkip;
        cr += chromaSkip;
    }
}

static void TMCJPEGDEC_converterYUV422toRGBA8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 lumaSkip;
    s32 chromaSkip;
    u16* output;
    s32 tileRow;
    s32 columnInTile;
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
    s8 crValue;
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
            columnInTile = column & 3;
            output[columnInTile + ((((column >> 2) << 1) + tileRow) << 4)] = (u8)red + 0x10000 - 0x100;
            output[columnInTile + ((((column >> 2) << 1) + (tileRow + 1)) << 4)] = ((green & 255) << 8) + (blue & 255);
        }
        luminance += lumaSkip;
        cb += chromaSkip;
        cr += chromaSkip;
    }
}

static void TMCJPEGDEC_converterYUV420toRGBA8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 lumaSkip;
    s32 red;
    s32 secondBlue;
    s32 chromaSkip;
    s32 chromaWidth;
    u16* output;
    s32 tileRow;
    s32 columnInTile;
    u8* texture;
    u8* luminance;
    u8* cb;
    u8* cr;
    s32 column;
    s32 xEnd;
    s32 yEnd;
    s32 tileWidth;
    s32 redOffset;
    s32 greenOffset;
    s32 blueOffset;
    s32 green;
    s32 blue;
    s32 secondGreen;
    s32 secondRed;
    s32 secondColumnInTile;
    s32 value;
    TMCCJPEGDecState* state;
    s32 width;
    s32 height;
    s8 crValue;
    s32 cbValue;

    luminance = work->convBuf + 4;
    cb = &work->convBuf[260];
    cr = &work->convBuf[324];
    state = work->pState;
    tileWidth = (state->convWidth >> 2) << 1;
    texture = state->pTexBuffer;
    width = 16 / state->scaleFactor;
    height = 16 / state->scaleFactor;
    xEnd = x + width;
    yEnd = y + height;
    lumaSkip = 16 - width;
    chromaSkip = lumaSkip >> 1;
    chromaWidth = (width + 1) >> 1;
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
            columnInTile = column & 3;
            output[columnInTile + ((((column >> 2) << 1) + tileRow) << 4)] = (u8)red + 0x10000 - 0x100;
            output[columnInTile + ((((column >> 2) << 1) + (tileRow + 1)) << 4)] = ((green & 255) << 8) + (blue & 255);
            value = *luminance++;
            secondGreen = value + greenOffset;
            secondRed = value + redOffset;
            secondBlue = value + blueOffset;
            if ((secondRed | secondGreen | secondBlue) >> 8) {
                secondBlue = secondBlue > 255 ? 255 : secondBlue < 0 ? 0 : secondBlue;
                secondGreen = secondGreen > 255 ? 255 : secondGreen < 0 ? 0 : secondGreen;
                secondRed = secondRed > 255 ? 255 : secondRed < 0 ? 0 : secondRed;
            }
            secondColumnInTile = (column + 1) & 3;
            output[secondColumnInTile + (((((column + 1) >> 2) << 1) + tileRow) << 4)] = (u8)secondRed + 0x10000 - 0x100;
            output[secondColumnInTile + (((((column + 1) >> 2) << 1) + (tileRow + 1)) << 4)] = ((secondGreen & 255) << 8) + (secondBlue & 255);
        }
        luminance += lumaSkip;
        if (y & 1) {
            cb += chromaSkip;
            cr += chromaSkip;
        } else {
            cb -= chromaWidth;
            cr -= chromaWidth;
        }
    }
}

static void TMCJPEGDEC_converterYUV420toRGBA8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 lumaSkip;
    s32 red;
    s32 chromaSkip;
    s32 chromaWidth;
    u16* output;
    s32 tileRow;
    s32 columnInTile;
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
    s8 crValue;
    s32 redOffset;
    s32 greenOffset;
    s32 blueOffset;
    s32 value;
    s32 green;
    s32 blue;

    luminance = work->convBuf + 4;
    cb = &work->convBuf[260];
    cr = &work->convBuf[324];
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
        height = 16 / state->scaleFactor;
    }
    xEnd = x + width;
    yEnd = y + height;
    lumaSkip = 16 - width;
    chromaSkip = lumaSkip >> 1;
    chromaWidth = (width + 1) >> 1;
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
            columnInTile = column & 3;
            output[columnInTile + ((((column >> 2) << 1) + tileRow) << 4)] = (u8)red + 0x10000 - 0x100;
            output[columnInTile + ((((column >> 2) << 1) + (tileRow + 1)) << 4)] = ((green & 255) << 8) + (blue & 255);
        }
        luminance += lumaSkip;
        if (y & 1) {
            cb += chromaSkip;
            cr += chromaSkip;
        } else {
            cb -= chromaWidth;
            cr -= chromaWidth;
        }
    }
}

static void TMCJPEGDEC_converterYUV211toRGBA8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 lumaSkip;
    u16* output;
    s32 tileRow;
    s32 columnInTile;
    u8* texture;
    u8* luminance;
    u8* cb;
    u8* cr;
    s32 column;
    s32 width;
    s32 xEnd;
    s32 yEnd;
    s32 tileWidth;
    s32 red;
    s32 green;
    s32 blue;
    s32 redOffset;
    TMCCJPEGDecState* state;
    s32 height;
    s32 chromaSkip;
    s32 cbValue;
    s32 blueOffset;
    s8 crValue;
    s32 value;
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
                    columnInTile = column & 3;
                    output[columnInTile + ((((column >> 2) << 1) + tileRow) << 4)] = (u8)red + 0x10000 - 0x100;
                    output[columnInTile + ((((column >> 2) << 1) + (tileRow + 1)) << 4)] = ((green & 255) << 8) + (blue & 255);
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
    s32 lumaSkip;
    u16* output;
    s32 tileRow;
    s32 columnInTile;
    u8* texture;
    u8* luminance;
    u8* cb;
    u8* cr;
    s32 column;
    s32 width;
    s32 xEnd;
    s32 yEnd;
    s32 tileWidth;
    s32 red;
    s32 green;
    s32 blue;
    s32 height;
    TMCCJPEGDecState* state;
    s32 chromaSkip;
    s32 greenOffset;
    s32 cbValue;
    s32 blueOffset;
    s8 crValue;
    s32 value;
    s32 redOffset;

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
                    columnInTile = column & 3;
                    output[columnInTile + ((((column >> 2) << 1) + tileRow) << 4)] = (u8)red + 0x10000 - 0x100;
                    output[columnInTile + ((((column >> 2) << 1) + (tileRow + 1)) << 4)] = ((green & 255) << 8) + (blue & 255);
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
    s32 rowSkip;
    u16* output;
    s32 tileRow;
    s32 columnInTile;
    u8* texture;
    u8* luminance;
    u8* cb;
    u8* cr;
    TMCCJPEGDecState* state;
    s8 crValue;
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
        output = (u16*)(texture + ((row & 3) << 3));
        tileRow = (row >> 2) * tileWidth;
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
            columnInTile = column & 3;
            output[columnInTile + ((((column >> 2) << 1) + tileRow) << 4)] =
                (u8)red + 0x10000 - 0x100;
            output[columnInTile + ((((column >> 2) << 1) + (tileRow + 1)) << 4)] =
                ((green & 255) << 8) + (blue & 255);
        }
        luminance += rowSkip;
        cb += rowSkip;
        cr += rowSkip;
    }
}

static void TMCJPEGDEC_converterYUV444toRGBA8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 rowSkip;
    u16* output;
    s32 tileRow;
    s32 columnInTile;
    u8* texture;
    u8* luminance;
    u8* cb;
    u8* cr;
    s32 column;
    s32 xEnd;
    s32 yEnd;
    s32 tileWidth;
    s32 red;
    s32 green;
    s32 blue;
    s32 width;
    s32 height;
    s32 cbValue;
    s8 crValue;
    s32 value;
    TMCCJPEGDecState* state;

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
            if ((red | green | blue) >> 8) {
                blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                green = green > 255 ? 255 : green < 0 ? 0 : green;
                red = red > 255 ? 255 : red < 0 ? 0 : red;
            }
            columnInTile = column & 3;
            output[columnInTile + ((((column >> 2) << 1) + tileRow) << 4)] = (u8)red + 0x10000 - 0x100;
            output[columnInTile + ((((column >> 2) << 1) + (tileRow + 1)) << 4)] = ((green & 255) << 8) + (blue & 255);
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
