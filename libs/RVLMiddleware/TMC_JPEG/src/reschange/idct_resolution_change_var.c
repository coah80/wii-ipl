#include <tmc_jpeg_internal.h>

static u8 clampU8(s32 v) {
    s32 ok;
    ok = 0;
    if (v < 256 && v > -1) {
        ok = 1;
    }
    return (ok) ? v : ((v < 0) ? 0 : 255);
}

static s8 clampS8(s32 v) {
    return (v < 128 && v > -129) ? (s8)v : (v > 0) ? 127 : -128;
}

void TMCJPEGDEC_IdctBlock4x4(s32* block, u8* conv_row_ptr, u16 pitch, s32 zigzag) {
    s32 bd;
    s32 c;
    s32 a;
    s32 cd;
    s32 oddrot;
    s32 evsum;
    s32 rot;
    s32 d;
    s32 b;

    s32* sp;
    s32* dp;

    s32 tmp[64];
    s32 i;


    sp = block + 24;
    dp = tmp + 24;

    for (i = 0; i < 4; i++) {
        s32 a, b, c, d;
        s32 odddiff, bd, evsum, cd, rot, oddrot;
        a = sp[0];
        b = sp[1];
        c = sp[2];
        d = sp[3];
        odddiff = b - d;
        bd = b + d;
        evsum = a + c;
        cd = a - c;
        rot = (odddiff * 0xB5) >> 8;
        oddrot = rot + bd;
        dp[0] = evsum + oddrot;
        dp[1] = cd + rot;
        dp[2] = cd - rot;
        dp[3] = evsum - oddrot;
        sp -= 8;
        dp -= 8;
    }

    {
        u32 idx = 3;
        s32* column = tmp + 3;

        for (i = 0; i < 4; i++) {
            u8* bp = conv_row_ptr + idx;

            a = column[0] + 0x40000;
            b = column[8];
            d = column[24];
            c = column[16];

            evsum = a + c;
            cd = a - c;

            rot = ((b - d) * 0xB5) >> 8;
            bd = b + d;
            oddrot = rot + bd;

            bp[0] = clampU8((evsum + oddrot) >> 11);
            bp[pitch] = clampU8((cd + rot) >> 11);
            bp[pitch * 2] = clampU8((cd - rot) >> 11);
            bp[pitch * 4 - pitch] = clampU8((evsum - oddrot) >> 11);

            column--;
            idx -= 1;
        }
    }
}

void TMCJPEGDEC_IdctBlock2x2(s32* block, u8* conv_row_ptr, u16 pitch, s32 zigzag) {
    u8* bp;
    s32 a0b;
    s32 a0, a1;
    s32 b0, b1;
    s32 even_sum, even_diff, odd_sum, rot;
    bp = conv_row_ptr;
    a0 = block[0];
    a0b = a0 + 0x40000;
    a1 = block[1];
    b0 = block[8];
    b1 = block[9];
    even_sum = a0b + a1;
    even_diff = a0b - a1;
    odd_sum = b0 + b1;
    rot = b0 - b1;
    bp[0] = (u8)clampU8((even_sum + odd_sum) >> 11);
    bp[pitch] = (u8)clampU8((even_sum - odd_sum) >> 11);
    bp[1] = (u8)clampU8((even_diff + rot) >> 11);
    (bp + pitch)[1] = (u8)clampU8((even_diff - rot) >> 11);
}

void TMCJPEGDEC_IdctBlock1x1(s32* block, u8* conv_row_ptr, u16 pitch, s32 zigzag) {
    s32 in = block[0];
    conv_row_ptr[0] = clampU8((in >> 11) + 0x80);
}

void TMCJPEGDEC_IdctBlock4x4_Col(s32* sp, u8* conv_row_ptr, u16 pitch, s32 zigzag) {
    s32 tmp[64];
    s32* src = sp + 24;
    s32* dst = tmp + 24;
    s32 i;
    s32 a, b, c, d;
    s32 evsum, evdiff, oddsum, odddiff, rot, oddrot;

    for (i = 0; i < 4; i++) {
        a = src[0];
        b = src[1];
        c = src[2];
        d = src[3];
        odddiff = b - d;
        oddsum = b + d;
        evsum = a + c;
        evdiff = a - c;
        rot = (odddiff * 0xB5) >> 8;
        oddrot = rot + oddsum;
        dst[0] = evsum + oddrot;
        dst[1] = evdiff + rot;
        dst[2] = evdiff - rot;
        dst[3] = evsum - oddrot;
        src -= 8;
        dst -= 8;
    }

    src = tmp + 3;
    for (i = 3; i >= 0; i--) {
        s32 evdiff;
        s32 a;
        s32 c;
        s32 b;
        s32 evsum;
        s32 d;
        s32 oddsum;
        s32 odddiff;
        s32 rot;
        s32 oddrot;
        u8* out = conv_row_ptr + i;
        a = src[0];
        b = src[8];
        c = src[16];
        d = src[24];

        odddiff = b - d;
        oddsum = d + b;
        evsum = a + c;
        evdiff = a - c;
        rot = odddiff * 0xB5 >> 8;
        oddrot = oddsum + rot;

        out[0] = (u8)clampS8((evsum + oddrot) >> 11);
        out[8] = (u8)clampS8((evdiff + rot) >> 11);
        out[16] = (u8)clampS8((evdiff - rot) >> 11);
        out[24] = (u8)clampS8((evsum - oddrot) >> 11);

        src--;
    }
}

void TMCJPEGDEC_IdctBlock2x2_Col(s32* block, u8* conv_row_ptr, u16 pitch, s32 zigzag) {
    s32 a0, a1;
    s32 b0, b1;
    s32 even_sum, even_diff, odd_sum, rot;

    a0 = block[0];
    a1 = block[1];
    b0 = block[8];
    b1 = block[9];

    even_sum = a0 + a1;
    even_diff = a0 - a1;
    odd_sum = b0 + b1;
    rot = b0 - b1;

    conv_row_ptr[0] = (u8)clampS8((even_sum + odd_sum) >> 11);
    conv_row_ptr[8] = (u8)clampS8((even_sum - odd_sum) >> 11);
    conv_row_ptr[1] = (u8)clampS8((even_diff + rot) >> 11);
    conv_row_ptr[9] = (u8)clampS8((even_diff - rot) >> 11);
}

void TMCJPEGDEC_IdctBlock1x1_Col(s32* block, u8* conv_row_ptr, u16 pitch, s32 zigzag) {
    s32 in = block[0];
    conv_row_ptr[0] = clampS8(in >> 11);
}
