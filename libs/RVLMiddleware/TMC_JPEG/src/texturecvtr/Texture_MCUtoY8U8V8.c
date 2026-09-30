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

            work->pConverterFunc = TMCJPEGDEC_converterYUV411toY8U8V8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV411toY8U8V8edge;
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
            work->pConverterFunc = TMCJPEGDEC_converterYUV422toY8U8V8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV422toY8U8V8edge;
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
            work->pConverterFunc = TMCJPEGDEC_converterYUV420toY8U8V8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV420toY8U8V8edge;
            work->pConvRowPtrs[0] = (void*)ptr;
            work->pConvRowPtrs[1] = (void*)(ptr + mode);
            work->pConvRowPtrs[2] = (void*)(ptr + mode * 16);
            work->pConvRowPtrs[3] = (void*)(ptr + mode * 16 + mode);
            work->pConvRowPtrs[5] = (void*)(ob + 0x104);
            work->pConvRowPtrs[6] = (void*)(ob + 0x144);
            work->pitch = 0x10;
            work->converterFlags = 0;
            break;
        }
        case 3: {
            u8 mode = work->idctMode;
            u8* ptr = ob + 4;
            work->pConverterFunc = TMCJPEGDEC_converterYUV211toY8U8V8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV211toY8U8V8edge;
            work->pConvRowPtrs[0] = (void*)ptr;
            work->pConvRowPtrs[1] = (void*)(ptr + mode * 8);
            work->pConvRowPtrs[5] = (void*)(ob + 0x84);
            work->pConvRowPtrs[6] = (void*)(ob + 0xC4);
            work->pitch = 0x08;
            work->converterFlags = 0;
            break;
        }
        case 4: {
            work->pConverterFunc = TMCJPEGDEC_converterYUV444toY8U8V8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV444toY8U8V8edge;
            work->pConvRowPtrs[0] = (void*)(ob + 4);
            work->pConvRowPtrs[5] = (void*)(ob + 0x44);
            work->pConvRowPtrs[6] = (void*)(ob + 0x84);
            work->pitch = 0x08;
            work->converterFlags = 0;
            break;
        }
        case 5: {
            work->pConverterFunc = TMCJPEGDEC_converterYUV400toY8U8V8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV400toY8U8V8edge;
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
        u32 fw = st->jpegWidth;
        u32 fh = st->jpegHeight;
        u32 ow = st->outputWidth;
        u32 oh = st->outputHeight;
        s32 bw = (s32)(((fw << 29) - (fw >> 31)) * 8 + (fw >> 31));
        s32 bh = (s32)(((fh << 30) - (fh >> 31)) * 4 + (fh >> 31));
        s32 bw2 = (s32)(((ow << 29) - (ow >> 31)) * 8 + (ow >> 31));
        s32 bh2 = (s32)(((oh << 30) - (oh >> 31)) * 4 + (oh >> 31));
        {
            s32 nb = -bw;
            s32 nb2 = -bh;
            s32 nb3 = -bw2;
            s32 nb4 = -bh2;
            bw = ((nb | bw) >> 31) + (fw >> 3);
            bh = ((nb2 | bh) >> 31) + (fh >> 2);
            bw2 = ((nb3 | bw2) >> 31) + (ow >> 3);
            bh2 = ((nb4 | bh2) >> 31) + (oh >> 2);
        }
        st->convWidth = bw << 3;
        st->convHeight = bh << 2;
        st->chromaWidth = bw2 << 3;
        st->chromaHeight = bh2 << 2;
    }
    return 0;
}
static void TMCJPEGDEC_converterYUV411toY8U8V8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* st;
    u32 bw;
    u32 bw2;
    u8* out0;
    u8* out1;
    u8* out2;
    s32 ss;
    s32 step;
    s32 ystep;
    s32 x_end;
    s32 y_end;
    s32 cstep;
    s32 xc;
    s32 xc_end;
    s32 yc;
    s32 yc_end;
    u8* y_row;
    u8* u_row;
    u8* v_row;
    s32 skip;
    s32 cskip;
    s32 stride;
    s32 cstride;
    s32 x_pos;
    s32 xc_pos;
    s32 row_base;
    s32 crow_base;
    u8* oy;
    u8* ou;
    u8* ov;
    s32 xo;
    s32 off;


    st = work->pState;
    y_row = work->convBuf + 4;
    u_row = work->convBuf + 0x104;
    v_row = work->convBuf + 0x144;
    bw = st->convWidth;
    bw2 = st->chromaWidth;
    out0 = (u8*)st->pLumaBuffer;
    out1 = (u8*)st->pCbBuffer;
    out2 = (u8*)st->pCrBuffer;
    ss = st->scaleFactor;
    step = 0x20 / ss;
    ystep = 0x08 / ss;

    x_end = x + step;
    y_end = y + ystep;
    skip = 0x20 - step;
    stride = bw >> 3;

    for (; y < y_end; y++) {
        row_base = (y >> 2) * stride;
        oy = out0 + ((y & 3) << 3);
        for (x_pos = x; x_pos < x_end; x_pos += 4) {
            off = ((x_pos >> 3) + row_base) << 5;
            xo = x_pos & 7;
            oy[off + xo] = y_row[0];
            off = (((x_pos + 1) >> 3) + row_base) << 5;
            xo = (x_pos + 1) & 7;
            oy[off + xo] = y_row[1];
            off = (((x_pos + 2) >> 3) + row_base) << 5;
            xo = (x_pos + 2) & 7;
            oy[off + xo] = y_row[2];
            off = (((x_pos + 3) >> 3) + row_base) << 5;
            xo = (x_pos + 3) & 7;
            oy[off + xo] = y_row[3];
            y_row += 4;
        }
        y_row += skip;
    }

    xc = (u32)x >> 2;
    cstep = 0x08 / ss;
    xc_end = xc + cstep;
    yc = y;
    yc_end = y_end;
    cskip = 8 - cstep;
    cstride = bw2 >> 3;

    for (; yc < yc_end; yc++) {
        crow_base = (yc >> 2) * cstride;
        ou = out1 + ((yc & 3) << 3);
        ov = out2 + ((yc & 3) << 3);
        for (xc_pos = xc; xc_pos < xc_end; xc_pos++) {
            off = ((xc_pos >> 3) + crow_base) << 5;
            xo = xc_pos & 7;
            ou[off + xo] = *u_row++ + 0x80;
            ov[off + xo] = *v_row++ + 0x80;
        }
        u_row += cskip;
        v_row += cskip;
    }
}

static void TMCJPEGDEC_converterYUV411toY8U8V8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* st;
    u32 bw;
    u32 bw2;
    u8* out0;
    u8* out1;
    u8* out2;
    s32 ss;
    s32 step;
    s32 ystep;
    s32 x_end;
    s32 y_end;
    s32 cstep;
    s32 xc;
    s32 xc_end;
    s32 yc;
    s32 yc_end;
    u8* y_row;
    u8* u_row;
    u8* v_row;
    s32 skip;
    s32 cskip;
    s32 stride;
    s32 cstride;
    s32 x_pos;
    s32 xc_pos;
    s32 row_base;
    s32 crow_base;
    u8* oy;
    u8* ou;
    u8* ov;
    s32 xo;
    s32 off;


    st = work->pState;
    y_row = work->convBuf + 4;
    u_row = work->convBuf + 0x104;
    v_row = work->convBuf + 0x144;
    bw = st->convWidth;
    bw2 = st->chromaWidth;
    out0 = (u8*)st->pLumaBuffer;
    out1 = (u8*)st->pCbBuffer;
    out2 = (u8*)st->pCrBuffer;

    if (st->dataSizeX == x) {
        step = st->stepXExt;
    } else {
        step = 0x20 / st->scaleFactor;
    }
    if (st->dataSizeY == y) {
        ystep = st->stepYExt;
    } else {
        ystep = 0x08 / st->scaleFactor;
    }

    x_end = x + step;
    y_end = y + ystep;
    skip = 0x20 - step;
    stride = bw >> 3;

    for (; y < y_end; y++) {
        row_base = (y >> 2) * stride;
        oy = out0 + ((y & 3) << 3);
        for (x_pos = x; x_pos < x_end; x_pos++) {
            off = ((x_pos >> 3) + row_base) << 5;
            xo = x_pos & 7;
            oy[off + xo] = *y_row++;
        }
        y_row += skip;
    }

    xc = (u32)x >> 2;
    cstep = (step + 3) >> 2;
    xc_end = xc + cstep;
    yc = y;
    yc_end = y_end;
    cskip = 8 - cstep;
    cstride = bw2 >> 3;

    for (; yc < yc_end; yc++) {
        crow_base = (yc >> 2) * cstride;
        ou = out1 + ((yc & 3) << 3);
        ov = out2 + ((yc & 3) << 3);
        for (xc_pos = xc; xc_pos < xc_end; xc_pos++) {
            off = ((xc_pos >> 3) + crow_base) << 5;
            xo = xc_pos & 7;
            ou[off + xo] = *u_row++ + 0x80;
            ov[off + xo] = *v_row++ + 0x80;
        }
        u_row += cskip;
        v_row += cskip;
    }
}

static void TMCJPEGDEC_converterYUV422toY8U8V8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* st;
    u32 bw;
    u32 bw2;
    u8* out0;
    u8* out1;
    u8* out2;
    s32 ss;
    s32 step;
    s32 ystep;
    s32 x_end;
    s32 y_end;
    s32 cstep;
    s32 xc;
    s32 xc_end;
    s32 yc;
    s32 yc_end;
    u8* y_row;
    u8* u_row;
    u8* v_row;
    s32 skip;
    s32 cskip;
    s32 stride;
    s32 cstride;
    s32 x_pos;
    s32 xc_pos;
    s32 row_base;
    s32 crow_base;
    u8* oy;
    u8* ou;
    u8* ov;
    s32 xo;
    s32 off;


    st = work->pState;
    y_row = work->convBuf + 4;
    u_row = work->convBuf + 0x84;
    v_row = work->convBuf + 0xC4;
    bw = st->convWidth;
    bw2 = st->chromaWidth;
    out0 = (u8*)st->pLumaBuffer;
    out1 = (u8*)st->pCbBuffer;
    out2 = (u8*)st->pCrBuffer;
    ss = st->scaleFactor;
    step = 0x10 / ss;
    ystep = 0x08 / ss;

    x_end = x + step;
    y_end = y + ystep;
    skip = 0x10 - step;
    stride = bw >> 3;

    for (; y < y_end; y++) {
        row_base = (y >> 2) * stride;
        oy = out0 + ((y & 3) << 3);
        for (x_pos = x; x_pos < x_end; x_pos += 2) {
            oy[(((x_pos >> 3) + row_base) << 5) + (x_pos & 7)] = *y_row++;
            oy[((((x_pos + 1) >> 3) + row_base) << 5) + ((x_pos + 1) & 7)] = *y_row++;
        }
        y_row += skip;
    }

    xc = (u32)x >> 1;
    cstep = 0x08 / ss;
    xc_end = xc + cstep;
    yc = y;
    yc_end = y_end;
    cskip = 8 - cstep;
    cstride = bw2 >> 3;

    for (; yc < yc_end; yc++) {
        crow_base = (yc >> 2) * cstride;
        ou = out1 + ((yc & 3) << 3);
        ov = out2 + ((yc & 3) << 3);
        for (xc_pos = xc; xc_pos < xc_end; xc_pos++) {
            off = ((xc_pos >> 3) + crow_base) << 5;
            xo = xc_pos & 7;
            ou[off + xo] = *u_row++ + 0x80;
            ov[off + xo] = *v_row++ + 0x80;
        }
        u_row += cskip;
        v_row += cskip;
    }
}

static void TMCJPEGDEC_converterYUV422toY8U8V8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* st;
    u32 bw;
    u32 bw2;
    u8* out0;
    u8* out1;
    u8* out2;
    s32 ss;
    s32 step;
    s32 ystep;
    s32 x_end;
    s32 y_end;
    s32 cstep;
    s32 xc;
    s32 xc_end;
    s32 yc;
    s32 yc_end;
    u8* y_row;
    u8* u_row;
    u8* v_row;
    s32 skip;
    s32 cskip;
    s32 stride;
    s32 cstride;
    s32 x_pos;
    s32 xc_pos;
    s32 row_base;
    s32 crow_base;
    u8* oy;
    u8* ou;
    u8* ov;
    s32 xo;
    s32 off;


    st = work->pState;
    y_row = work->convBuf + 4;
    u_row = work->convBuf + 0x84;
    v_row = work->convBuf + 0xC4;
    bw = st->convWidth;
    bw2 = st->chromaWidth;
    out0 = (u8*)st->pLumaBuffer;
    out1 = (u8*)st->pCbBuffer;
    out2 = (u8*)st->pCrBuffer;

    if (st->dataSizeX == x) {
        step = st->stepXExt;
    } else {
        step = 0x10 / st->scaleFactor;
    }
    if (st->dataSizeY == y) {
        ystep = st->stepYExt;
    } else {
        ystep = 0x08 / st->scaleFactor;
    }

    x_end = x + step;
    y_end = y + ystep;
    skip = 0x10 - step;
    stride = bw >> 3;

    for (; y < y_end; y++) {
        row_base = (y >> 2) * stride;
        oy = out0 + ((y & 3) << 3);
        for (x_pos = x; x_pos < x_end; x_pos++) {
            off = ((x_pos >> 3) + row_base) << 5;
            xo = x_pos & 7;
            oy[off + xo] = *y_row++;
        }
        y_row += skip;
    }

    xc = (u32)x >> 1;
    cstep = (step + 1) >> 1;
    xc_end = xc + cstep;
    yc = y;
    yc_end = y_end;
    cskip = 8 - cstep;
    cstride = bw2 >> 3;

    for (; yc < yc_end; yc++) {
        crow_base = (yc >> 2) * cstride;
        ou = out1 + ((yc & 3) << 3);
        ov = out2 + ((yc & 3) << 3);
        for (xc_pos = xc; xc_pos < xc_end; xc_pos++) {
            off = ((xc_pos >> 3) + crow_base) << 5;
            xo = xc_pos & 7;
            ou[off + xo] = *u_row++ + 0x80;
            ov[off + xo] = *v_row++ + 0x80;
        }
        u_row += cskip;
        v_row += cskip;
    }
}

static void TMCJPEGDEC_converterYUV420toY8U8V8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* st;
    u32 bw;
    u32 bw2;
    u8* out0;
    u8* out1;
    u8* out2;
    s32 ss;
    s32 step;
    s32 ystep;
    s32 x_end;
    s32 y_end;
    s32 cstep;
    s32 xc;
    s32 xc_end;
    s32 yc;
    s32 yc_end;
    u8* y_row;
    u8* u_row;
    u8* v_row;
    s32 skip;
    s32 cskip;
    s32 stride;
    s32 cstride;
    s32 x_pos;
    s32 xc_pos;
    s32 row_base;
    s32 crow_base;
    u8* oy;
    u8* ou;
    u8* ov;
    s32 xo;
    s32 off;


    st = work->pState;
    y_row = work->convBuf + 4;
    u_row = work->convBuf + 0x104;
    v_row = work->convBuf + 0x144;
    bw = st->convWidth;
    bw2 = st->chromaWidth;
    out0 = (u8*)st->pLumaBuffer;
    out1 = (u8*)st->pCbBuffer;
    out2 = (u8*)st->pCrBuffer;
    ss = st->scaleFactor;
    step = 0x10 / ss;
    ystep = 0x10 / ss;

    x_end = x + step;
    y_end = y + ystep;
    skip = 0x10 - step;
    stride = bw >> 3;

    for (; y < y_end; y++) {
        row_base = (y >> 2) * stride;
        oy = out0 + ((y & 3) << 3);
        for (x_pos = x; x_pos < x_end; x_pos += 2) {
            off = ((x_pos >> 3) + row_base) << 5;
            xo = x_pos & 7;
            oy[off + xo] = y_row[0];
            off = (((x_pos + 1) >> 3) + row_base) << 5;
            xo = (x_pos + 1) & 7;
            oy[off + xo] = y_row[1];
            y_row += 2;
        }
        y_row += skip;
    }

    xc = (u32)x >> 1;
    cstep = 0x08 / ss;
    xc_end = xc + cstep;
    yc = (u32)y >> 1;
    yc_end = yc + (0x08 / ss);
    cskip = 8 - cstep;
    cstride = bw2 >> 3;

    for (; yc < yc_end; yc++) {
        crow_base = (yc >> 2) * cstride;
        ou = out1 + ((yc & 3) << 3);
        ov = out2 + ((yc & 3) << 3);
        for (xc_pos = xc; xc_pos < xc_end; xc_pos++) {
            off = ((xc_pos >> 3) + crow_base) << 5;
            xo = xc_pos & 7;
            ou[off + xo] = *u_row++ + 0x80;
            ov[off + xo] = *v_row++ + 0x80;
        }
        u_row += cskip;
        v_row += cskip;
    }
}

static void TMCJPEGDEC_converterYUV420toY8U8V8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* st;
    u32 bw;
    u32 bw2;
    u8* out0;
    u8* out1;
    u8* out2;
    s32 ss;
    s32 step;
    s32 ystep;
    s32 x_end;
    s32 y_end;
    s32 cstep;
    s32 xc;
    s32 xc_end;
    s32 yc;
    s32 yc_end;
    u8* y_row;
    u8* u_row;
    u8* v_row;
    s32 skip;
    s32 cskip;
    s32 stride;
    s32 cstride;
    s32 x_pos;
    s32 xc_pos;
    s32 row_base;
    s32 crow_base;
    u8* oy;
    u8* ou;
    u8* ov;
    s32 xo;
    s32 off;


    st = work->pState;
    y_row = work->convBuf + 4;
    u_row = work->convBuf + 0x104;
    v_row = work->convBuf + 0x144;
    bw = st->convWidth;
    bw2 = st->chromaWidth;
    out0 = (u8*)st->pLumaBuffer;
    out1 = (u8*)st->pCbBuffer;
    out2 = (u8*)st->pCrBuffer;

    if (st->dataSizeX == x) {
        step = st->stepXExt;
    } else {
        step = 0x10 / st->scaleFactor;
    }
    if (st->dataSizeY == y) {
        ystep = st->stepYExt;
    } else {
        ystep = 0x10 / st->scaleFactor;
    }

    x_end = x + step;
    y_end = y + ystep;
    skip = 0x10 - step;
    stride = bw >> 3;

    for (; y < y_end; y++) {
        row_base = (y >> 2) * stride;
        oy = out0 + ((y & 3) << 3);
        for (x_pos = x; x_pos < x_end; x_pos++) {
            off = ((x_pos >> 3) + row_base) << 5;
            xo = x_pos & 7;
            oy[off + xo] = *y_row++;
        }
        y_row += skip;
    }

    xc = (u32)x >> 1;
    cstep = (step + 1) >> 1;
    xc_end = xc + cstep;
    yc = (u32)y >> 1;
    yc_end = yc + ((ystep + 1) >> 1);
    cskip = 8 - cstep;
    cstride = bw2 >> 3;

    for (; yc < yc_end; yc++) {
        crow_base = (yc >> 2) * cstride;
        ou = out1 + ((yc & 3) << 3);
        ov = out2 + ((yc & 3) << 3);
        for (xc_pos = xc; xc_pos < xc_end; xc_pos++) {
            off = ((xc_pos >> 3) + crow_base) << 5;
            xo = xc_pos & 7;
            ou[off + xo] = *u_row++ + 0x80;
            ov[off + xo] = *v_row++ + 0x80;
        }
        u_row += cskip;
        v_row += cskip;
    }
}

static void TMCJPEGDEC_converterYUV211toY8U8V8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* st;
    u32 bw;
    u32 bw2;
    u8* out0;
    u8* out1;
    u8* out2;
    s32 ss;
    s32 step;
    s32 ystep;
    s32 x_end;
    s32 y_end;
    s32 cstep;
    s32 xc;
    s32 xc_end;
    s32 yc;
    s32 yc_end;
    u8* y_row;
    u8* u_row;
    u8* v_row;
    s32 skip;
    s32 cskip;
    s32 stride;
    s32 cstride;
    s32 x_pos;
    s32 xc_pos;
    s32 row_base;
    s32 crow_base;
    u8* oy;
    u8* ou;
    u8* ov;
    s32 xo;
    s32 off;


    st = work->pState;
    y_row = work->convBuf + 4;
    u_row = work->convBuf + 0x84;
    v_row = work->convBuf + 0xC4;
    bw = st->convWidth;
    bw2 = st->chromaWidth;
    out0 = (u8*)st->pLumaBuffer;
    out1 = (u8*)st->pCbBuffer;
    out2 = (u8*)st->pCrBuffer;
    ss = st->scaleFactor;
    step = 0x08 / ss;
    ystep = 0x10 / ss;

    x_end = x + step;
    y_end = y + ystep;
    skip = 0x08 - step;
    stride = bw >> 3;

    for (; y < y_end; y++) {
        row_base = (y >> 2) * stride;
        oy = out0 + ((y & 3) << 3);
        for (x_pos = x; x_pos < x_end; x_pos++) {
            off = ((x_pos >> 3) + row_base) << 5;
            xo = x_pos & 7;
            oy[off + xo] = *y_row++;
        }
        y_row += skip;
    }

    cstep = step;
    xc_end = x + cstep;
    yc = (u32)y >> 1;
    yc_end = yc + (0x08 / ss);
    cskip = 8 - cstep;
    cstride = bw2 >> 3;

    for (; yc < yc_end; yc++) {
        crow_base = (yc >> 2) * cstride;
        ou = out1 + ((yc & 3) << 3);
        ov = out2 + ((yc & 3) << 3);
        for (xc_pos = x; xc_pos < xc_end; xc_pos++) {
            off = ((xc_pos >> 3) + crow_base) << 5;
            xo = xc_pos & 7;
            ou[off + xo] = *u_row++ + 0x80;
            ov[off + xo] = *v_row++ + 0x80;
        }
        u_row += cskip;
        v_row += cskip;
    }
}

static void TMCJPEGDEC_converterYUV211toY8U8V8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* st;
    u32 bw;
    u32 bw2;
    u8* out0;
    u8* out1;
    u8* out2;
    s32 ss;
    s32 step;
    s32 ystep;
    s32 x_end;
    s32 y_end;
    s32 cstep;
    s32 xc;
    s32 xc_end;
    s32 yc;
    s32 yc_end;
    u8* y_row;
    u8* u_row;
    u8* v_row;
    s32 skip;
    s32 cskip;
    s32 stride;
    s32 cstride;
    s32 x_pos;
    s32 xc_pos;
    s32 row_base;
    s32 crow_base;
    u8* oy;
    u8* ou;
    u8* ov;
    s32 xo;
    s32 off;


    st = work->pState;
    y_row = work->convBuf + 4;
    u_row = work->convBuf + 0x84;
    v_row = work->convBuf + 0xC4;
    bw = st->convWidth;
    bw2 = st->chromaWidth;
    out0 = (u8*)st->pLumaBuffer;
    out1 = (u8*)st->pCbBuffer;
    out2 = (u8*)st->pCrBuffer;

    if (st->dataSizeX == x) {
        step = st->stepXExt;
    } else {
        step = 0x08 / st->scaleFactor;
    }
    if (st->dataSizeY == y) {
        ystep = st->stepYExt;
    } else {
        ystep = 0x10 / st->scaleFactor;
    }

    x_end = x + step;
    y_end = y + ystep;
    skip = 0x08 - step;
    stride = bw >> 3;

    for (; y < y_end; y++) {
        row_base = (y >> 2) * stride;
        oy = out0 + ((y & 3) << 3);
        for (x_pos = x; x_pos < x_end; x_pos++) {
            off = ((x_pos >> 3) + row_base) << 5;
            xo = x_pos & 7;
            oy[off + xo] = *y_row++;
        }
        y_row += skip;
    }

    cstep = step;
    xc_end = x + cstep;
    yc = (u32)y >> 1;
    yc_end = yc + ((ystep + 1) >> 1);
    cskip = 8 - cstep;
    cstride = bw2 >> 3;

    for (; yc < yc_end; yc++) {
        crow_base = (yc >> 2) * cstride;
        ou = out1 + ((yc & 3) << 3);
        ov = out2 + ((yc & 3) << 3);
        for (xc_pos = x; xc_pos < xc_end; xc_pos++) {
            off = ((xc_pos >> 3) + crow_base) << 5;
            xo = xc_pos & 7;
            ou[off + xo] = *u_row++ + 0x80;
            ov[off + xo] = *v_row++ + 0x80;
        }
        u_row += cskip;
        v_row += cskip;
    }
}

static void TMCJPEGDEC_converterYUV444toY8U8V8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* st;
    u32 bw;
    u8* out0;
    u8* out1;
    u8* out2;
    s32 ss;
    s32 step;
    s32 ystep;
    s32 x_end;
    s32 y_end;
    u8* y_row;
    u8* u_row;
    u8* v_row;
    s32 skip;
    s32 stride;
    s32 x_pos;
    s32 row_base;
    u8* oy;
    u8* ou;
    u8* ov;
    s32 xo;
    s32 off;

    st = work->pState;
    y_row = work->convBuf + 4;
    u_row = work->convBuf + 0x44;
    v_row = work->convBuf + 0x84;
    bw = st->convWidth;
    out0 = (u8*)st->pLumaBuffer;
    out1 = (u8*)st->pCbBuffer;
    out2 = (u8*)st->pCrBuffer;
    ss = st->scaleFactor;
    step = 0x08 / ss;
    ystep = step;

    x_end = x + step;
    y_end = y + ystep;
    skip = 0x08 - step;
    stride = bw >> 3;

    for (; y < y_end; y++) {
        row_base = (y >> 2) * stride;
        oy = out0 + ((y & 3) << 3);
        ou = out1 + ((y & 3) << 3);
        ov = out2 + ((y & 3) << 3);
        for (x_pos = x; x_pos < x_end; x_pos++) {
            off = ((x_pos >> 3) + row_base) << 5;
            xo = x_pos & 7;
            oy[off + xo] = *y_row++;
            ou[off + xo] = *u_row++ + 0x80;
            ov[off + xo] = *v_row++ + 0x80;
        }
        y_row += skip;
        u_row += skip;
        v_row += skip;
    }
}

static void TMCJPEGDEC_converterYUV444toY8U8V8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* st;
    u32 bw;
    u8* out0;
    u8* out1;
    u8* out2;
    s32 ss;
    s32 step;
    s32 ystep;
    s32 x_end;
    s32 y_end;
    u8* y_row;
    u8* u_row;
    u8* v_row;
    s32 skip;
    s32 stride;
    s32 x_pos;
    s32 row_base;
    u8* oy;
    u8* ou;
    u8* ov;
    s32 xo;
    s32 off;

    st = work->pState;
    y_row = work->convBuf + 4;
    u_row = work->convBuf + 0x44;
    v_row = work->convBuf + 0x84;
    bw = st->convWidth;
    out0 = (u8*)st->pLumaBuffer;
    out1 = (u8*)st->pCbBuffer;
    out2 = (u8*)st->pCrBuffer;

    if (st->dataSizeX == x) {
        step = st->stepXExt;
    } else {
        step = 0x08 / st->scaleFactor;
    }
    if (st->dataSizeY == y) {
        ystep = st->stepYExt;
    } else {
        ystep = 0x08 / st->scaleFactor;
    }

    x_end = x + step;
    y_end = y + ystep;
    skip = 0x08 - step;
    stride = bw >> 3;

    for (; y < y_end; y++) {
        row_base = (y >> 2) * stride;
        oy = out0 + ((y & 3) << 3);
        ou = out1 + ((y & 3) << 3);
        ov = out2 + ((y & 3) << 3);
        for (x_pos = x; x_pos < x_end; x_pos++) {
            off = ((x_pos >> 3) + row_base) << 5;
            xo = x_pos & 7;
            oy[off + xo] = *y_row++;
            ou[off + xo] = *u_row++ + 0x80;
            ov[off + xo] = *v_row++ + 0x80;
        }
        y_row += skip;
        u_row += skip;
        v_row += skip;
    }
}

static void TMCJPEGDEC_converterYUV400toY8U8V8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* st;
    u32 bw;
    u8* out0;
    s32 ss;
    s32 step;
    s32 ystep;
    s32 x_end;
    s32 y_end;
    u8* y_row;
    s32 skip;
    s32 stride;
    s32 x_pos;
    s32 row_base;
    u8* oy;
    s32 xo;
    s32 off;

    st = work->pState;
    y_row = work->convBuf + 4;
    bw = st->convWidth;
    out0 = (u8*)st->pLumaBuffer;
    ss = st->scaleFactor;
    step = 0x08 / ss;
    ystep = step;

    x_end = x + step;
    y_end = y + ystep;
    skip = 0x08 - step;
    stride = bw >> 3;

    for (; y < y_end; y++) {
        row_base = (y >> 2) * stride;
        oy = out0 + ((y & 3) << 3);
        for (x_pos = x; x_pos < x_end; x_pos++) {
            off = ((x_pos >> 3) + row_base) << 5;
            xo = x_pos & 7;
            oy[off + xo] = *y_row++;
        }
        y_row += skip;
    }
}

static void TMCJPEGDEC_converterYUV400toY8U8V8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* st;
    u32 bw;
    u8* out0;
    s32 ss;
    s32 step;
    s32 ystep;
    s32 x_end;
    s32 y_end;
    u8* y_row;
    s32 skip;
    s32 stride;
    s32 x_pos;
    s32 row_base;
    u8* oy;
    s32 xo;
    s32 off;

    st = work->pState;
    y_row = work->convBuf + 4;
    bw = st->convWidth;
    out0 = (u8*)st->pLumaBuffer;

    if (st->dataSizeX == x) {
        step = st->stepXExt;
    } else {
        step = 0x08 / st->scaleFactor;
    }
    if (st->dataSizeY == y) {
        ystep = st->stepYExt;
    } else {
        ystep = 0x08 / st->scaleFactor;
    }

    x_end = x + step;
    y_end = y + ystep;
    skip = 0x08 - step;
    stride = bw >> 3;

    for (; y < y_end; y++) {
        row_base = (y >> 2) * stride;
        oy = out0 + ((y & 3) << 3);
        for (x_pos = x; x_pos < x_end; x_pos++) {
            off = ((x_pos >> 3) + row_base) << 5;
            xo = x_pos & 7;
            oy[off + xo] = *y_row++;
        }
        y_row += skip;
    }
}