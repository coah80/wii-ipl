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

            work->pConverterFunc = TMCJPEGDEC_converterYUV411toRGB565;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV411toRGB565edge;
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
            work->pConverterFunc = TMCJPEGDEC_converterYUV422toRGB565;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV422toRGB565edge;
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
            work->pConverterFunc = TMCJPEGDEC_converterYUV420toRGB565;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV420toRGB565edge;
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
            work->pConverterFunc = TMCJPEGDEC_converterYUV211toRGB565;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV211toRGB565edge;
            work->pConvRowPtrs[0] = (void*)ptr;
            work->pConvRowPtrs[1] = (void*)(ptr + mode * 8);
            work->pConvRowPtrs[5] = (void*)(ptr + 0x84);
            work->pConvRowPtrs[6] = (void*)(ptr + 0xC4);
            work->pitch = 0x08;
            work->converterFlags = 0;
            break;
        }
        case 4: {
            work->pConverterFunc = TMCJPEGDEC_converterYUV400toRGB565;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV400toRGB565edge;
            work->pConvRowPtrs[0] = (void*)(ob + 4);
            work->pitch = 0x08;
            work->converterFlags = 0;
            break;
        }
        case 5: {
            work->pConverterFunc = TMCJPEGDEC_converterYUV444toRGB565;
            work->pConverterFuncEdge = TMCJPEGDEC_converterYUV444toRGB565edge;
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

static s32 clampU8_565(s32 v) {
    if (v > 0xFF) {
        return 0xFF;
    } else {
        s32 t = v >> 31;
        v &= ~t;
        return v;
    }
}

static void TMCJPEGDEC_converterYUV411toRGB565(TMCCJPEGDecWork* work, s32 x, s32 y) {
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
    s32 xo;
    u16 px;

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
    stride = bw >> 2;

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
                    rr = clampU8_565(rr);
                    gg = clampU8_565(gg);
                    bb = clampU8_565(bb);
                }
                xo = x_pos & 3;
                off = (((x_pos >> 2) + row_base) << 4) + xo;
                px = ((bb & 0xF8) >> 3) + ((rr & 0xF8) << 8) + ((gg & 0xF8) << 3);
                ((u16*)ob)[off] = px;

                yv = y_row[1];
                rr = yv + ra;
                gg = yv + ga;
                bb = yv + ba;
                if ((rr | gg | bb) >> 8) {
                    rr = clampU8_565(rr);
                    gg = clampU8_565(gg);
                    bb = clampU8_565(bb);
                }
                xo = (x_pos + 1) & 3;
                off = ((((x_pos + 1) >> 2) + row_base) << 4) + xo;
                px = ((bb & 0xF8) >> 3) + ((rr & 0xF8) << 8) + ((gg & 0xF8) << 3);
                ((u16*)ob)[off] = px;

                yv = y_row[2];
                rr = yv + ra;
                gg = yv + ga;
                bb = yv + ba;
                if ((rr | gg | bb) >> 8) {
                    rr = clampU8_565(rr);
                    gg = clampU8_565(gg);
                    bb = clampU8_565(bb);
                }
                xo = (x_pos + 2) & 3;
                off = ((((x_pos + 2) >> 2) + row_base) << 4) + xo;
                px = ((bb & 0xF8) >> 3) + ((rr & 0xF8) << 8) + ((gg & 0xF8) << 3);
                ((u16*)ob)[off] = px;

                yv = y_row[3];
                rr = yv + ra;
                gg = yv + ga;
                bb = yv + ba;
                if ((rr | gg | bb) >> 8) {
                    rr = clampU8_565(rr);
                    gg = clampU8_565(gg);
                    bb = clampU8_565(bb);
                }
                xo = (x_pos + 3) & 3;
                off = ((((x_pos + 3) >> 2) + row_base) << 4) + xo;
                px = ((bb & 0xF8) >> 3) + ((rr & 0xF8) << 8) + ((gg & 0xF8) << 3);
                ((u16*)ob)[off] = px;

                y_row += 4;

            }

        y_row += skip;
        cb_row += cskip;
        cr_row += cskip;
        y++;
    }
}

static void TMCJPEGDEC_converterYUV411toRGB565edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
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
    s32 xo;
    u16 px;

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
    stride = bw >> 2;

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
                rr = clampU8_565(rr);
                gg = clampU8_565(gg);
                bb = clampU8_565(bb);
            }
            xo = x_pos & 3;
            off = (((x_pos >> 2) + row_base) << 4) + xo;
            px = ((bb & 0xF8) >> 3) + ((rr & 0xF8) << 8) + ((gg & 0xF8) << 3);
            ((u16*)ob)[off] = px;
        }

        y_row += skip;
        cb_row += cskip;
        cr_row += cskip;
        y++;
    }
}


static void TMCJPEGDEC_converterYUV422toRGB565(TMCCJPEGDecWork* work, s32 x, s32 y) {
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
    s32 xo;
    u16 px;

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
    stride = bw >> 2;

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
                    rr = clampU8_565(rr);
                    gg = clampU8_565(gg);
                    bb = clampU8_565(bb);
                }
                xo = x_pos & 3;
                off = (((x_pos >> 2) + row_base) << 4) + xo;
                px = ((bb & 0xF8) >> 3) + ((rr & 0xF8) << 8) + ((gg & 0xF8) << 3);
                ((u16*)ob)[off] = px;

                yv = y_row[1];
                rr = yv + ra;
                gg = yv + ga;
                bb = yv + ba;
                if ((rr | gg | bb) >> 8) {
                    rr = clampU8_565(rr);
                    gg = clampU8_565(gg);
                    bb = clampU8_565(bb);
                }
                xo = (x_pos + 1) & 3;
                off = ((((x_pos + 1) >> 2) + row_base) << 4) + xo;
                px = ((bb & 0xF8) >> 3) + ((rr & 0xF8) << 8) + ((gg & 0xF8) << 3);
                ((u16*)ob)[off] = px;

                y_row += 2;

            }

        y_row += skip;
        cb_row += cskip;
        cr_row += cskip;
        y++;
    }
}

static void TMCJPEGDEC_converterYUV422toRGB565edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
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
    s32 xo;
    u16 px;

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
    stride = bw >> 2;

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
                rr = clampU8_565(rr);
                gg = clampU8_565(gg);
                bb = clampU8_565(bb);
            }
            xo = x_pos & 3;
            off = (((x_pos >> 2) + row_base) << 4) + xo;
            px = ((bb & 0xF8) >> 3) + ((rr & 0xF8) << 8) + ((gg & 0xF8) << 3);
            ((u16*)ob)[off] = px;
        }

        y_row += skip;
        cb_row += cskip;
        cr_row += cskip;
        y++;
    }
}


static void TMCJPEGDEC_converterYUV420toRGB565(TMCCJPEGDecWork* work, s32 x, s32 y) {
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
    s32 xo;
    u16 px;

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
    stride = bw >> 2;

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
                    rr = clampU8_565(rr);
                    gg = clampU8_565(gg);
                    bb = clampU8_565(bb);
                }
                xo = x_pos & 3;
                off = (((x_pos >> 2) + row_base) << 4) + xo;
                px = ((bb & 0xF8) >> 3) + ((rr & 0xF8) << 8) + ((gg & 0xF8) << 3);
                ((u16*)ob)[off] = px;

                yv = y_row[1];
                rr = yv + ra;
                gg = yv + ga;
                bb = yv + ba;
                if ((rr | gg | bb) >> 8) {
                    rr = clampU8_565(rr);
                    gg = clampU8_565(gg);
                    bb = clampU8_565(bb);
                }
                xo = (x_pos + 1) & 3;
                off = ((((x_pos + 1) >> 2) + row_base) << 4) + xo;
                px = ((bb & 0xF8) >> 3) + ((rr & 0xF8) << 8) + ((gg & 0xF8) << 3);
                ((u16*)ob)[off] = px;

                y_row += 2;

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

static void TMCJPEGDEC_converterYUV420toRGB565edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
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
    s32 xo;
    u16 px;

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
    stride = bw >> 2;

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
                rr = clampU8_565(rr);
                gg = clampU8_565(gg);
                bb = clampU8_565(bb);
            }
            xo = x_pos & 3;
            off = (((x_pos >> 2) + row_base) << 4) + xo;
            px = ((bb & 0xF8) >> 3) + ((rr & 0xF8) << 8) + ((gg & 0xF8) << 3);
            ((u16*)ob)[off] = px;
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


static void TMCJPEGDEC_converterYUV211toRGB565(TMCCJPEGDecWork* work, s32 x, s32 y) {
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
    s32 xo;
    u16 px;

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
    stride = bw >> 2;

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
                    rr = clampU8_565(rr);
                    gg = clampU8_565(gg);
                    bb = clampU8_565(bb);
                }
                xo = x_pos & 3;
                off = (((x_pos >> 2) + row_base) << 4) + xo;
                px = ((bb & 0xF8) >> 3) + ((rr & 0xF8) << 8) + ((gg & 0xF8) << 3);
                ((u16*)ob)[off] = px;
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

static void TMCJPEGDEC_converterYUV211toRGB565edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
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
    s32 xo;
    u16 px;

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
    stride = bw >> 2;

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
                rr = clampU8_565(rr);
                gg = clampU8_565(gg);
                bb = clampU8_565(bb);
            }
            xo = x_pos & 3;
            off = (((x_pos >> 2) + row_base) << 4) + xo;
            px = ((bb & 0xF8) >> 3) + ((rr & 0xF8) << 8) + ((gg & 0xF8) << 3);
            ((u16*)ob)[off] = px;
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


static void TMCJPEGDEC_converterYUV444toRGB565(TMCCJPEGDecWork* work, s32 x, s32 y) {
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
    s32 xo;
    u16 px;

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
    stride = bw >> 2;

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
                    rr = clampU8_565(rr);
                    gg = clampU8_565(gg);
                    bb = clampU8_565(bb);
                }
                xo = x_pos & 3;
                off = (((x_pos >> 2) + row_base) << 4) + xo;
                px = ((bb & 0xF8) >> 3) + ((rr & 0xF8) << 8) + ((gg & 0xF8) << 3);
                ((u16*)ob)[off] = px;
            }

        y_row += skip;
        cb_row += skip;
        cr_row += skip;
        y++;
    }
}

static void TMCJPEGDEC_converterYUV444toRGB565edge(TMCCJPEGDecWork* work, s32 x, s32 y) {
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
    s32 xo;
    u16 px;

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
    stride = bw >> 2;

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
                rr = clampU8_565(rr);
                gg = clampU8_565(gg);
                bb = clampU8_565(bb);
            }
            xo = x_pos & 3;
            off = (((x_pos >> 2) + row_base) << 4) + xo;
            px = ((bb & 0xF8) >> 3) + ((rr & 0xF8) << 8) + ((gg & 0xF8) << 3);
            ((u16*)ob)[off] = px;
        }

        y_row += skip;
        cb_row += skip;
        cr_row += skip;
        y++;
    }
}


static void TMCJPEGDEC_converterYUV400toRGB565(TMCCJPEGDecWork* work, s32 x, s32 y) {
    s32 column;
    s32 tileRow;
    TMCCJPEGDecState* state = work->pState;
    u8* texture = state->pTexBuffer;
    u8* luminance = work->convBuf + 4;
    u32 tileWidth = state->convWidth >> 2;
    s32 width = 8 / state->scaleFactor;
    s32 height = 8 / state->scaleFactor;
    {
        s32 xEnd = x + width;
        s32 yEnd = y + height;
        s32 row;
        width = 8 - width;
        for (row = y; row < yEnd; row++) {
            u16* output;
            tileRow = (row >> 2) * tileWidth;
            output = (u16*)(texture + ((row & 3) << 3));
            for (column = x; column < xEnd; column += 1) {
                s32 value = *luminance++;
                s32 green, blue;
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
    s32 xo;
    u16 px;

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
    stride = bw >> 2;

    while (y < y_end) {
        row_base = (y >> 2) * stride;
        ob = out + ((y & 3) << 3);

        for (x_pos = x; x_pos < x_end; x_pos++) {
            cb = *y_row++;
            if ((cb >> 8) != 0) {
                rr = clampU8_565(cb);
                gg = clampU8_565(cb);
                bb = clampU8_565(cb);
            } else {
                rr = cb;
                gg = cb;
                bb = cb;
            }
            xo = x_pos & 3;
            off = (((x_pos >> 2) + row_base) << 4) + xo;
            px = ((bb & 0xF8) >> 3) + ((rr & 0xF8) << 8) + ((gg & 0xF8) << 3);
            ((u16*)ob)[off] = px;
        }

        y_row += skip;
        y++;
    }
}

