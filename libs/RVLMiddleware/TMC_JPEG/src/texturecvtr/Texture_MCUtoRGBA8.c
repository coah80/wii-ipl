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

            work->pConverterFunc = TMCJPEGDEC_converterYUV411toRGBA8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV411toRGBA8edge;
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
            work->pConverterFunc = TMCJPEGDEC_converterYUV422toRGBA8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV422toRGBA8edge;
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
            work->pConverterFunc = TMCJPEGDEC_converterYUV420toRGBA8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV420toRGBA8edge;
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
            work->pConverterFunc = TMCJPEGDEC_converterYUV211toRGBA8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV211toRGBA8edge;
            work->pConvRowPtrs[0] = (void*)ptr;
            work->pConvRowPtrs[1] = (void*)(ptr + mode * 8);
            work->pConvRowPtrs[5] = (void*)(ptr + 0x84);
            work->pConvRowPtrs[6] = (void*)(ptr + 0xC4);
            work->pitch = 0x08;
            work->converterFlags = 0;
            break;
        }
        case 4: {
            work->pConverterFunc = TMCJPEGDEC_converterYUV400toRGBA8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV400toRGBA8edge;
            work->pConvRowPtrs[0] = (void*)(ob + 4);
            work->pitch = 0x08;
            work->converterFlags = 0;
            break;
        }
        case 5: {
            work->pConverterFunc = TMCJPEGDEC_converterYUV444toRGBA8;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV444toRGBA8edge;
            work->pConvRowPtrs[0] = (void*)(ob + 4);
            work->pConvRowPtrs[5] = (void*)(ob + 0x44);
            work->pConvRowPtrs[6] = (void*)(ob + 0x84);
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

static s32 clampU8_A8(s32 v) {
    if (v > 0xFF) {
        return 0xFF;
    } else {
        s32 t = v >> 31;
        v &= ~t;
        return v;
    }
}

static void TMCJPEGDEC_converterYUV411toRGBA8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* st;
    u8* y_row;
    u8* cb_row;
    u8* cr_row;
    u32 bw;
    u8* out;
    s32 ss;
    s32 step;
    s32 x_end;
    s32 y_end;
    s32 skip;
    s32 cskip;
    s32 stride;
    s32 x_pos;
    s32 row_base;
    u8* ob;
    s32 cb;
    s32 cr;
    s32 ra;
    s32 ga;
    s32 ba;
    s32 rr;
    s32 gg;
    s32 bb;
    s32 yv;
    s32 off;
    s32 off2;
    s32 xo;
    u16 px;
    u16 px2;

    st = work->pState;
    y_row = work->convBuf + 4;
    cb_row = work->convBuf + 0x104;
    cr_row = work->convBuf + 0x144;
    bw = st->convWidth;
    out = (u8*)st->pTexBuffer;
    ss = st->scaleFactor;
    step = 0x20 / ss;
    x_end = x + step;
    y_end = y + (0x08 / ss);
    skip = 0x20 - step;
    cskip = skip >> 2;
    stride = (bw >> 1) & 0x7FFFFFFE;

    while (y < y_end) {
        row_base = (y >> 2) * stride;
        ob = out + ((y & 3) << 3);
        x_pos = x;

        for (x_pos = x; x_pos < x_end; x_pos += 4) {
                cb = (s8)*cb_row++;
                cr = (s8)*cr_row++;
                ra = (cr * 0x167) >> 8;
                ga = -((cb * 0x58) + (cr * 0xB7)) >> 8;
                ba = (cb * 0x1C6) >> 8;

                yv = y_row[0];
                rr = yv + ra;
                gg = yv + ga;
                bb = yv + ba;
                if ((rr | gg | bb) >> 8) {
                    rr = clampU8_A8(rr);
                    gg = clampU8_A8(gg);
                    bb = clampU8_A8(bb);
                }
                off = (((x_pos >> 2) << 1) + row_base) << 4;

                xo = x_pos & 3;

                px2 = ((gg & 0xFF) << 8) + (rr & 0xFF);

                off2 = ((((x_pos >> 2) << 1) + 1 + row_base) << 4);

                px = (bb & 0xFF) + 0xFF00;

                ((u16*)ob)[off + xo] = px;

                ((u16*)ob)[off2 + xo] = px2;

                yv = y_row[1];
                y_row += 2;
                rr = yv + ra;
                gg = yv + ga;
                bb = yv + ba;
                if ((rr | gg | bb) >> 8) {
                    rr = clampU8_A8(rr);
                    gg = clampU8_A8(gg);
                    bb = clampU8_A8(bb);
                }
                off = ((((x_pos + 1) >> 2) << 1) + row_base) << 4;

                xo = (x_pos + 1) & 3;

                px2 = ((gg & 0xFF) << 8) + (rr & 0xFF);

                off2 = (((((x_pos + 1) >> 2) << 1) + 1 + row_base) << 4);

                px = (bb & 0xFF) + 0xFF00;

                ((u16*)ob)[off + xo] = px;

                ((u16*)ob)[off2 + xo] = px2;

                yv = y_row[2];
                rr = yv + ra;
                gg = yv + ga;
                bb = yv + ba;
                if ((rr | gg | bb) >> 8) {
                    rr = clampU8_A8(rr);
                    gg = clampU8_A8(gg);
                    bb = clampU8_A8(bb);
                }
                off = ((((x_pos + 2) >> 2) << 1) + row_base) << 4;

                xo = (x_pos + 2) & 3;

                px2 = ((gg & 0xFF) << 8) + (rr & 0xFF);

                off2 = (((((x_pos + 2) >> 2) << 1) + 1 + row_base) << 4);

                px = (bb & 0xFF) + 0xFF00;

                ((u16*)ob)[off + xo] = px;

                ((u16*)ob)[off2 + xo] = px2;

                yv = y_row[3];
                rr = yv + ra;
                gg = yv + ga;
                bb = yv + ba;
                if ((rr | gg | bb) >> 8) {
                    rr = clampU8_A8(rr);
                    gg = clampU8_A8(gg);
                    bb = clampU8_A8(bb);
                }
                off = ((((x_pos + 3) >> 2) << 1) + row_base) << 4;

                xo = (x_pos + 3) & 3;

                px2 = ((gg & 0xFF) << 8) + (rr & 0xFF);

                off2 = (((((x_pos + 3) >> 2) << 1) + 1 + row_base) << 4);

                px = (bb & 0xFF) + 0xFF00;

                ((u16*)ob)[off + xo] = px;

                ((u16*)ob)[off2 + xo] = px2;

                y_row += 4;

            }

        y_row += skip;
        cb_row += cskip;
        cr_row += cskip;
        y++;
    }
}

static void TMCJPEGDEC_converterYUV411toRGBA8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* st;
    u8* y_row;
    u8* cb_row;
    u8* cr_row;
    u32 bw;
    u8* out;
    s32 step;
    s32 step_v;
    s32 x_end;
    s32 y_end;
    s32 skip;
    s32 cskip;
    s32 cback;
    s32 stride;
    s32 x_pos;
    s32 row_base;
    u8* ob;
    s32 cb;
    s32 cr;
    s32 ra;
    s32 ga;
    s32 ba;
    s32 rr;
    s32 gg;
    s32 bb;
    s32 yv;
    s32 off;
    s32 off2;
    s32 xo;
    u16 px;
    u16 px2;

    st = work->pState;
    y_row = work->convBuf + 4;
    cb_row = work->convBuf + 0x104;
    cr_row = work->convBuf + 0x144;
    bw = st->convWidth;
    out = (u8*)st->pTexBuffer;

    if (st->dataSizeX == x) {
        step = st->stepXExt;
    } else {
        step = 0x20 / st->scaleFactor;
    }
    if (st->dataSizeY == y) {
        step_v = st->stepYExt;
    } else {
        step_v = 0x08 / st->scaleFactor;
    }

    x_end = x + step;
    y_end = y + step_v;
    skip = 0x20 - step;
    cskip = skip >> 2;
    stride = (bw >> 1) & 0x7FFFFFFE;

    while (y < y_end) {
        row_base = (y >> 2) * stride;
        ob = out + ((y & 3) << 3);

        for (x_pos = x; x_pos < x_end; x_pos++) {
            if ((x_pos & 3) == 0) {
                cr = (s8)*cr_row++;
                cb = (s8)*cb_row++;
                ra = (cr * 0x167) >> 8;
                ga = -((cb * 0x58) + (cr * 0xB7)) >> 8;
                ba = (cb * 0x1C6) >> 8;
            }
            yv = *y_row++;
            rr = yv + ra;
            gg = yv + ga;
            bb = yv + ba;
            if ((rr | gg | bb) >> 8) {
                rr = clampU8_A8(rr);
                gg = clampU8_A8(gg);
                bb = clampU8_A8(bb);
            }
            off = (((x_pos >> 2) << 1) + row_base) << 4;
                off2 = ((((x_pos >> 2) << 1) + 1 + row_base) << 4);
            xo = x_pos & 3;
            px = (bb & 0xFF) + 0xFF00;
            px2 = ((gg & 0xFF) << 8) + (rr & 0xFF);
            ((u16*)ob)[off + xo] = px;
            ((u16*)ob)[off2 + xo] = px2;
        }

        y_row += skip;
        cb_row += cskip;
        cr_row += cskip;
        y++;
    }
}


static void TMCJPEGDEC_converterYUV422toRGBA8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* st;
    u8* y_row;
    u8* cb_row;
    u8* cr_row;
    u32 bw;
    u8* out;
    s32 ss;
    s32 step;
    s32 x_end;
    s32 y_end;
    s32 skip;
    s32 cskip;
    s32 cback;
    s32 stride;
    s32 x_pos;
    s32 row_base;
    u8* ob;
    s32 cb;
    s32 cr;
    s32 ra;
    s32 ga;
    s32 ba;
    s32 rr;
    s32 gg;
    s32 bb;
    s32 yv;
    s32 off;
    s32 off2;
    s32 xo;
    u16 px;
    u16 px2;

    st = work->pState;
    y_row = work->convBuf + 4;
    cb_row = work->convBuf + 0x84;
    cr_row = work->convBuf + 0xC4;
    bw = st->convWidth;
    out = (u8*)st->pTexBuffer;
    ss = st->scaleFactor;
    step = 0x10 / ss;
    x_end = x + step;
    y_end = y + (0x08 / ss);
    skip = 0x10 - step;
    cskip = skip >> 1;
    cback = (step + 1) >> 1;
    stride = (bw >> 1) & 0x7FFFFFFE;

    while (y < y_end) {
        row_base = (y >> 2) * stride;
        ob = out + ((y & 3) << 3);
        x_pos = x;

        for (x_pos = x; x_pos < x_end; x_pos += 2) {
                cb = (s8)*cb_row++;
                cr = (s8)*cr_row++;
                ra = (cr * 0x167) >> 8;
                ga = -((cb * 0x58) + (cr * 0xB7)) >> 8;
                ba = (cb * 0x1C6) >> 8;

                yv = y_row[0];
                rr = yv + ra;
                gg = yv + ga;
                bb = yv + ba;
                if ((rr | gg | bb) >> 8) {
                    rr = clampU8_A8(rr);
                    gg = clampU8_A8(gg);
                    bb = clampU8_A8(bb);
                }
                off = (((x_pos >> 2) << 1) + row_base) << 4;

                xo = x_pos & 3;

                px2 = ((gg & 0xFF) << 8) + (rr & 0xFF);

                off2 = ((((x_pos >> 2) << 1) + 1 + row_base) << 4);

                px = (bb & 0xFF) + 0xFF00;

                ((u16*)ob)[off + xo] = px;

                ((u16*)ob)[off2 + xo] = px2;

                yv = y_row[1];
                y_row += 2;
                rr = yv + ra;
                gg = yv + ga;
                bb = yv + ba;
                if ((rr | gg | bb) >> 8) {
                    rr = clampU8_A8(rr);
                    gg = clampU8_A8(gg);
                    bb = clampU8_A8(bb);
                }
                off = ((((x_pos + 1) >> 2) << 1) + row_base) << 4;

                xo = (x_pos + 1) & 3;

                px2 = ((gg & 0xFF) << 8) + (rr & 0xFF);

                off2 = (((((x_pos + 1) >> 2) << 1) + 1 + row_base) << 4);

                px = (bb & 0xFF) + 0xFF00;

                ((u16*)ob)[off + xo] = px;

                ((u16*)ob)[off2 + xo] = px2;

            }

        y_row += skip;
        cb_row += cskip;
        cr_row += cskip;
        y++;
    }
}

static void TMCJPEGDEC_converterYUV422toRGBA8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* st;
    u8* y_row;
    u8* cb_row;
    u8* cr_row;
    u32 bw;
    u8* out;
    s32 step;
    s32 step_v;
    s32 x_end;
    s32 y_end;
    s32 skip;
    s32 cskip;
    s32 cback;
    s32 stride;
    s32 x_pos;
    s32 row_base;
    u8* ob;
    s32 cb;
    s32 cr;
    s32 ra;
    s32 ga;
    s32 ba;
    s32 rr;
    s32 gg;
    s32 bb;
    s32 yv;
    s32 off;
    s32 off2;
    s32 xo;
    u16 px;
    u16 px2;

    st = work->pState;
    y_row = work->convBuf + 4;
    cb_row = work->convBuf + 0x84;
    cr_row = work->convBuf + 0xC4;
    bw = st->convWidth;
    out = (u8*)st->pTexBuffer;

    if (st->dataSizeX == x) {
        step = st->stepXExt;
    } else {
        step = 0x10 / st->scaleFactor;
    }
    if (st->dataSizeY == y) {
        step_v = st->stepYExt;
    } else {
        step_v = 0x08 / st->scaleFactor;
    }

    x_end = x + step;
    y_end = y + step_v;
    skip = 0x10 - step;
    cskip = skip >> 1;
    stride = (bw >> 1) & 0x7FFFFFFE;

    while (y < y_end) {
        row_base = (y >> 2) * stride;
        ob = out + ((y & 3) << 3);

        for (x_pos = x; x_pos < x_end; x_pos++) {
            if ((x_pos & 1) == 0) {
                cr = (s8)*cr_row++;
                cb = (s8)*cb_row++;
                ra = (cr * 0x167) >> 8;
                ga = -((cb * 0x58) + (cr * 0xB7)) >> 8;
                ba = (cb * 0x1C6) >> 8;
            }
            yv = *y_row++;
            rr = yv + ra;
            gg = yv + ga;
            bb = yv + ba;
            if ((rr | gg | bb) >> 8) {
                rr = clampU8_A8(rr);
                gg = clampU8_A8(gg);
                bb = clampU8_A8(bb);
            }
            off = (((x_pos >> 2) << 1) + row_base) << 4;
                off2 = ((((x_pos >> 2) << 1) + 1 + row_base) << 4);
            xo = x_pos & 3;
            px = (bb & 0xFF) + 0xFF00;
            px2 = ((gg & 0xFF) << 8) + (rr & 0xFF);
            ((u16*)ob)[off + xo] = px;
            ((u16*)ob)[off2 + xo] = px2;
        }

        y_row += skip;
        cb_row += cskip;
        cr_row += cskip;
        y++;
    }
}


static void TMCJPEGDEC_converterYUV420toRGBA8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* st;
    u8* y_row;
    u8* cb_row;
    u8* cr_row;
    u32 bw;
    u8* out;
    s32 ss;
    s32 step;
    s32 x_end;
    s32 y_end;
    s32 skip;
    s32 cskip;
    s32 cback;
    s32 stride;
    s32 x_pos;
    s32 row_base;
    u8* ob;
    s32 cb;
    s32 cr;
    s32 ra;
    s32 ga;
    s32 ba;
    s32 rr;
    s32 gg;
    s32 bb;
    s32 yv;
    s32 off;
    s32 off2;
    s32 xo;
    u16 px;
    u16 px2;

    st = work->pState;
    y_row = work->convBuf + 4;
    cb_row = work->convBuf + 0x104;
    cr_row = work->convBuf + 0x144;
    bw = st->convWidth;
    out = (u8*)st->pTexBuffer;
    ss = st->scaleFactor;
    step = 0x10 / ss;
    x_end = x + step;
    y_end = y + (0x10 / ss);
    skip = 0x10 - step;
    cskip = skip >> 1;
    cback = (step + 1) >> 1;
    stride = (bw >> 1) & 0x7FFFFFFE;

    while (y < y_end) {
        row_base = (y >> 2) * stride;
        ob = out + ((y & 3) << 3);
        x_pos = x;

        for (x_pos = x; x_pos < x_end; x_pos += 2) {
                cb = (s8)*cb_row++;
                cr = (s8)*cr_row++;
                ra = (cr * 0x167) >> 8;
                ga = -((cb * 0x58) + (cr * 0xB7)) >> 8;
                ba = (cb * 0x1C6) >> 8;

                yv = y_row[0];
                rr = yv + ra;
                gg = yv + ga;
                bb = yv + ba;
                if ((rr | gg | bb) >> 8) {
                    rr = clampU8_A8(rr);
                    gg = clampU8_A8(gg);
                    bb = clampU8_A8(bb);
                }
                off = (((x_pos >> 2) << 1) + row_base) << 4;

                xo = x_pos & 3;

                px2 = ((gg & 0xFF) << 8) + (rr & 0xFF);

                off2 = ((((x_pos >> 2) << 1) + 1 + row_base) << 4);

                px = (bb & 0xFF) + 0xFF00;

                ((u16*)ob)[off + xo] = px;

                ((u16*)ob)[off2 + xo] = px2;

                yv = y_row[1];
                y_row += 2;
                rr = yv + ra;
                gg = yv + ga;
                bb = yv + ba;
                if ((rr | gg | bb) >> 8) {
                    rr = clampU8_A8(rr);
                    gg = clampU8_A8(gg);
                    bb = clampU8_A8(bb);
                }
                off = ((((x_pos + 1) >> 2) << 1) + row_base) << 4;

                xo = (x_pos + 1) & 3;

                px2 = ((gg & 0xFF) << 8) + (rr & 0xFF);

                off2 = (((((x_pos + 1) >> 2) << 1) + 1 + row_base) << 4);

                px = (bb & 0xFF) + 0xFF00;

                ((u16*)ob)[off + xo] = px;

                ((u16*)ob)[off2 + xo] = px2;

            }

        y_row += skip;
        if (y & 1) {
            cb_row += cskip;
            cr_row += cskip;
        } else {
            cb_row -= cback;
            cr_row -= cback;
        }
        y++;
    }
}

static void TMCJPEGDEC_converterYUV420toRGBA8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* st;
    u8* y_row;
    u8* cb_row;
    u8* cr_row;
    u32 bw;
    u8* out;
    s32 step;
    s32 step_v;
    s32 x_end;
    s32 y_end;
    s32 skip;
    s32 cskip;
    s32 cback;
    s32 stride;
    s32 x_pos;
    s32 row_base;
    u8* ob;
    s32 cb;
    s32 cr;
    s32 ra;
    s32 ga;
    s32 ba;
    s32 rr;
    s32 gg;
    s32 bb;
    s32 yv;
    s32 off;
    s32 off2;
    s32 xo;
    u16 px;
    u16 px2;

    st = work->pState;
    y_row = work->convBuf + 4;
    cb_row = work->convBuf + 0x104;
    cr_row = work->convBuf + 0x144;
    bw = st->convWidth;
    out = (u8*)st->pTexBuffer;

    if (st->dataSizeX == x) {
        step = st->stepXExt;
    } else {
        step = 0x10 / st->scaleFactor;
    }
    if (st->dataSizeY == y) {
        step_v = st->stepYExt;
    } else {
        step_v = 0x10 / st->scaleFactor;
    }

    x_end = x + step;
    y_end = y + step_v;
    skip = 0x10 - step;
    cskip = skip >> 1;
    cback = (step + 1) >> 1;
    stride = (bw >> 1) & 0x7FFFFFFE;

    while (y < y_end) {
        row_base = (y >> 2) * stride;
        ob = out + ((y & 3) << 3);

        for (x_pos = x; x_pos < x_end; x_pos++) {
            if ((x_pos & 1) == 0) {
                cr = (s8)*cr_row++;
                cb = (s8)*cb_row++;
                ra = (cr * 0x167) >> 8;
                ga = -((cb * 0x58) + (cr * 0xB7)) >> 8;
                ba = (cb * 0x1C6) >> 8;
            }
            yv = *y_row++;
            rr = yv + ra;
            gg = yv + ga;
            bb = yv + ba;
            if ((rr | gg | bb) >> 8) {
                rr = clampU8_A8(rr);
                gg = clampU8_A8(gg);
                bb = clampU8_A8(bb);
            }
            off = (((x_pos >> 2) << 1) + row_base) << 4;
                off2 = ((((x_pos >> 2) << 1) + 1 + row_base) << 4);
            xo = x_pos & 3;
            px = (bb & 0xFF) + 0xFF00;
            px2 = ((gg & 0xFF) << 8) + (rr & 0xFF);
            ((u16*)ob)[off + xo] = px;
            ((u16*)ob)[off2 + xo] = px2;
        }

        y_row += skip;
        if ((y & 1) != 0) {
            cb_row += cskip;
            cr_row += cskip;
        } else {
            cb_row -= cback;
            cr_row -= cback;
        }
        y++;
    }
}


static void TMCJPEGDEC_converterYUV211toRGBA8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* st;
    u8* y_row;
    u8* cb_row;
    u8* cr_row;
    u32 bw;
    u8* out;
    s32 ss;
    s32 step;
    s32 x_end;
    s32 y_end;
    s32 skip;
    s32 stride;
    s32 x_pos;
    s32 row_base;
    u8* ob;
    s32 cb;
    s32 cr;
    s32 ra;
    s32 ga;
    s32 ba;
    s32 rr;
    s32 gg;
    s32 bb;
    s32 yv;
    s32 off;
    s32 off2;
    s32 xo;
    u16 px;
    u16 px2;

    st = work->pState;
    y_row = work->convBuf + 4;
    cb_row = work->convBuf + 0x84;
    cr_row = work->convBuf + 0xC4;
    bw = st->convWidth;
    out = (u8*)st->pTexBuffer;
    ss = st->scaleFactor;
    step = 0x08 / ss;
    x_end = x + step;
    y_end = y + (0x10 / ss);
    skip = 0x08 - step;
    stride = (bw >> 1) & 0x7FFFFFFE;

    while (y < y_end) {
        row_base = (y >> 2) * stride;
        ob = out + ((y & 3) << 3);
        for (x_pos = x; x_pos < x_end; x_pos++) {
                cb = (s8)*cb_row++;
                cr = (s8)*cr_row++;
                yv = y_row[0];
                y_row++;
                ra = (cr * 0x167) >> 8;
                ga = -((cb * 0x58) + (cr * 0xB7)) >> 8;
                ba = (cb * 0x1C6) >> 8;
                rr = yv + ra;
                gg = yv + ga;
                bb = yv + ba;
                if ((rr | gg | bb) >> 8) {
                    rr = clampU8_A8(rr);
                    gg = clampU8_A8(gg);
                    bb = clampU8_A8(bb);
                }
                off = (((x_pos >> 2) << 1) + row_base) << 4;

                xo = x_pos & 3;

                px2 = ((gg & 0xFF) << 8) + (rr & 0xFF);

                off2 = ((((x_pos >> 2) << 1) + 1 + row_base) << 4);

                px = (bb & 0xFF) + 0xFF00;

                ((u16*)ob)[off + xo] = px;

                ((u16*)ob)[off2 + xo] = px2;
            }

        y_row += skip;
        if (y & 1) {
            cb_row += skip;
            cr_row += skip;
        } else {
            cb_row -= step;
            cr_row -= step;
        }
        y++;
    }
}

static void TMCJPEGDEC_converterYUV211toRGBA8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* st;
    u8* y_row;
    u8* cb_row;
    u8* cr_row;
    u32 bw;
    u8* out;
    s32 step;
    s32 step_v;
    s32 x_end;
    s32 y_end;
    s32 skip;
    s32 cskip;
    s32 cback;
    s32 stride;
    s32 x_pos;
    s32 row_base;
    u8* ob;
    s32 cb;
    s32 cr;
    s32 ra;
    s32 ga;
    s32 ba;
    s32 rr;
    s32 gg;
    s32 bb;
    s32 yv;
    s32 off;
    s32 off2;
    s32 xo;
    u16 px;
    u16 px2;

    st = work->pState;
    y_row = work->convBuf + 4;
    cb_row = work->convBuf + 0x84;
    cr_row = work->convBuf + 0xC4;
    bw = st->convWidth;
    out = (u8*)st->pTexBuffer;

    if (st->dataSizeX == x) {
        step = st->stepXExt;
    } else {
        step = 0x08 / st->scaleFactor;
    }
    if (st->dataSizeY == y) {
        step_v = st->stepYExt;
    } else {
        step_v = 0x10 / st->scaleFactor;
    }

    x_end = x + step;
    y_end = y + step_v;
    skip = 0x08 - step;
    stride = (bw >> 1) & 0x7FFFFFFE;

    while (y < y_end) {
        row_base = (y >> 2) * stride;
        ob = out + ((y & 3) << 3);

        for (x_pos = x; x_pos < x_end; x_pos++) {
            cb = (s8)*cb_row++;
            cr = (s8)*cr_row++;
            ra = (cr * 0x167) >> 8;
            ga = -((cb * 0x58) + (cr * 0xB7)) >> 8;
            ba = (cb * 0x1C6) >> 8;
            yv = *y_row++;
            rr = yv + ra;
            gg = yv + ga;
            bb = yv + ba;
            if ((rr | gg | bb) >> 8) {
                rr = clampU8_A8(rr);
                gg = clampU8_A8(gg);
                bb = clampU8_A8(bb);
            }
            off = (((x_pos >> 2) << 1) + row_base) << 4;
                off2 = ((((x_pos >> 2) << 1) + 1 + row_base) << 4);
            xo = x_pos & 3;
            px = (bb & 0xFF) + 0xFF00;
            px2 = ((gg & 0xFF) << 8) + (rr & 0xFF);
            ((u16*)ob)[off + xo] = px;
            ((u16*)ob)[off2 + xo] = px2;
        }

        y_row += skip;
        if ((y & 1) != 0) {
            cb_row += skip;
            cr_row += skip;
        } else {
            cb_row -= step;
            cr_row -= step;
        }
        y++;
    }
}


static void TMCJPEGDEC_converterYUV444toRGBA8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* st;
    u8* y_row;
    u8* cb_row;
    u8* cr_row;
    u32 bw;
    u8* out;
    s32 ss;
    s32 step;
    s32 x_end;
    s32 y_end;
    s32 skip;
    s32 stride;
    s32 x_pos;
    s32 row_base;
    u8* ob;
    s32 cb;
    s32 cr;
    s32 ra;
    s32 ga;
    s32 ba;
    s32 rr;
    s32 gg;
    s32 bb;
    s32 yv;
    s32 off;
    s32 off2;
    s32 xo;
    u16 px;
    u16 px2;

    st = work->pState;
    y_row = work->convBuf + 4;
    cb_row = work->convBuf + 0x44;
    cr_row = work->convBuf + 0x84;
    bw = st->convWidth;
    out = (u8*)st->pTexBuffer;
    ss = st->scaleFactor;
    step = 0x08 / ss;
    x_end = x + step;
    y_end = y + (0x08 / ss);
    skip = 0x08 - step;
    stride = (bw >> 1) & 0x7FFFFFFE;

    while (y < y_end) {
        row_base = (y >> 2) * stride;
        ob = out + ((y & 3) << 3);
        for (x_pos = x; x_pos < x_end; x_pos++) {
                cb = (s8)*cb_row++;
                cr = (s8)*cr_row++;
                yv = y_row[0];
                y_row++;
                ra = (cr * 0x167) >> 8;
                ga = -((cb * 0x58) + (cr * 0xB7)) >> 8;
                ba = (cb * 0x1C6) >> 8;
                rr = yv + ra;
                gg = yv + ga;
                bb = yv + ba;
                if ((rr | gg | bb) >> 8) {
                    rr = clampU8_A8(rr);
                    gg = clampU8_A8(gg);
                    bb = clampU8_A8(bb);
                }
                off = (((x_pos >> 2) << 1) + row_base) << 4;

                xo = x_pos & 3;

                px2 = ((gg & 0xFF) << 8) + (rr & 0xFF);

                off2 = ((((x_pos >> 2) << 1) + 1 + row_base) << 4);

                px = (bb & 0xFF) + 0xFF00;

                ((u16*)ob)[off + xo] = px;

                ((u16*)ob)[off2 + xo] = px2;
            }

        y_row += skip;
        cb_row += skip;
        cr_row += skip;
        y++;
    }
}

static void TMCJPEGDEC_converterYUV444toRGBA8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* st;
    u8* y_row;
    u8* cb_row;
    u8* cr_row;
    u32 bw;
    u8* out;
    s32 step;
    s32 step_v;
    s32 x_end;
    s32 y_end;
    s32 skip;
    s32 cskip;
    s32 cback;
    s32 stride;
    s32 x_pos;
    s32 row_base;
    u8* ob;
    s32 cb;
    s32 cr;
    s32 ra;
    s32 ga;
    s32 ba;
    s32 rr;
    s32 gg;
    s32 bb;
    s32 yv;
    s32 off;
    s32 off2;
    s32 xo;
    u16 px;
    u16 px2;

    st = work->pState;
    y_row = work->convBuf + 4;
    cb_row = work->convBuf + 0x44;
    cr_row = work->convBuf + 0x84;
    bw = st->convWidth;
    out = (u8*)st->pTexBuffer;

    if (st->dataSizeX == x) {
        step = st->stepXExt;
    } else {
        step = 0x08 / st->scaleFactor;
    }
    if (st->dataSizeY == y) {
        step_v = st->stepYExt;
    } else {
        step_v = 0x08 / st->scaleFactor;
    }

    x_end = x + step;
    y_end = y + step_v;
    skip = 0x08 - step;
    stride = (bw >> 1) & 0x7FFFFFFE;

    while (y < y_end) {
        row_base = (y >> 2) * stride;
        ob = out + ((y & 3) << 3);

        for (x_pos = x; x_pos < x_end; x_pos++) {
            cb = (s8)*cb_row++;
            cr = (s8)*cr_row++;
            ra = (cr * 0x167) >> 8;
            ga = -((cb * 0x58) + (cr * 0xB7)) >> 8;
            ba = (cb * 0x1C6) >> 8;
            yv = *y_row++;
            rr = yv + ra;
            gg = yv + ga;
            bb = yv + ba;
            if ((rr | gg | bb) >> 8) {
                rr = clampU8_A8(rr);
                gg = clampU8_A8(gg);
                bb = clampU8_A8(bb);
            }
            off = (((x_pos >> 2) << 1) + row_base) << 4;
                off2 = ((((x_pos >> 2) << 1) + 1 + row_base) << 4);
            xo = x_pos & 3;
            px = (bb & 0xFF) + 0xFF00;
            px2 = ((gg & 0xFF) << 8) + (rr & 0xFF);
            ((u16*)ob)[off + xo] = px;
            ((u16*)ob)[off2 + xo] = px2;
        }

        y_row += skip;
        cb_row += skip;
        cr_row += skip;
        y++;
    }
}


static void TMCJPEGDEC_converterYUV400toRGBA8(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* st;
    u8* cb_row;
    u32 bw;
    u8* out;
    s32 ss;
    s32 step;
    s32 x_end;
    s32 y_end;
    s32 skip;
    s32 stride;
    s32 x_pos;
    s32 row_base;
    u8* ob;
    s32 cb;
    s32 rr;
    s32 gg;
    s32 bb;
    s32 off;
    s32 off2;
    s32 xo;
    u16 px;
    u16 px2;

    st = work->pState;
    cb_row = work->convBuf + 4;
    bw = st->convWidth;
    out = (u8*)st->pTexBuffer;
    ss = st->scaleFactor;
    step = 0x08 / ss;
    x_end = x + step;
    y_end = y + step;
    skip = 0x08 - step;
    stride = (bw >> 1) & 0x7FFFFFFE;

    while (y < y_end) {
        row_base = (y >> 2) * stride;
        ob = out + ((y & 3) << 3);
        x_pos = x;

        for (x_pos = x; x_pos < x_end; x_pos++) {
                cb = *cb_row++;
                if ((cb >> 8) != 0) {
                    rr = clampU8_A8(cb);
                    gg = clampU8_A8(cb);
                    bb = clampU8_A8(cb);
                } else {
                    rr = cb;
                    gg = cb;
                    bb = cb;
                }
                off = (((x_pos >> 2) << 1) + row_base) << 4;

                xo = x_pos & 3;

                px2 = ((gg & 0xFF) << 8) + (rr & 0xFF);

                off2 = ((((x_pos >> 2) << 1) + 1 + row_base) << 4);

                px = (bb & 0xFF) + 0xFF00;

                ((u16*)ob)[off + xo] = px;

                ((u16*)ob)[off2 + xo] = px2;
            }

        cb_row += skip;
        y++;
    }
}

static void TMCJPEGDEC_converterYUV400toRGBA8edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
    TMCCJPEGDecState* st;
    u8* y_row;
    u8* cb_row;
    u8* cr_row;
    u32 bw;
    u8* out;
    s32 step;
    s32 step_v;
    s32 x_end;
    s32 y_end;
    s32 skip;
    s32 cskip;
    s32 cback;
    s32 stride;
    s32 x_pos;
    s32 row_base;
    u8* ob;
    s32 cb;
    s32 cr;
    s32 ra;
    s32 ga;
    s32 ba;
    s32 rr;
    s32 gg;
    s32 bb;
    s32 yv;
    s32 off;
    s32 off2;
    s32 xo;
    u16 px;
    u16 px2;

    st = work->pState;
    y_row = work->convBuf + 4;
    bw = st->convWidth;
    out = (u8*)st->pTexBuffer;

    if (st->dataSizeX == x) {
        step = st->stepXExt;
    } else {
        step = 0x08 / st->scaleFactor;
    }
    if (st->dataSizeY == y) {
        step_v = st->stepYExt;
    } else {
        step_v = 0x08 / st->scaleFactor;
    }

    x_end = x + step;
    y_end = y + step_v;
    skip = 0x08 - step;
    stride = (bw >> 1) & 0x7FFFFFFE;

    while (y < y_end) {
        row_base = (y >> 2) * stride;
        ob = out + ((y & 3) << 3);

        for (x_pos = x; x_pos < x_end; x_pos++) {
            cb = *y_row++;
            if ((cb >> 8) != 0) {
                rr = clampU8_A8(cb);
                gg = clampU8_A8(cb);
                bb = clampU8_A8(cb);
            } else {
                rr = cb;
                gg = cb;
                bb = cb;
            }
            off = (((x_pos >> 2) << 1) + row_base) << 4;
                off2 = ((((x_pos >> 2) << 1) + 1 + row_base) << 4);
            xo = x_pos & 3;
            px = (bb & 0xFF) + 0xFF00;
            px2 = ((gg & 0xFF) << 8) + (rr & 0xFF);
            ((u16*)ob)[off + xo] = px;
            ((u16*)ob)[off2 + xo] = px2;
        }

        y_row += skip;
        y++;
    }
}

