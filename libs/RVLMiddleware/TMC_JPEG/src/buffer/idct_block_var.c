#include <string.h>
#include <tmc_jpeg_internal.h>

static s32 clampU8(s32 v) {
    s32 ok;
    ok = 0;
    if (v < 256 && v > -1) {
        ok = 1;
    }
    return ok ? v : (v < 0 ? 0 : 255);
}

static s32 clampS8(s32 v) {
    s32 inRange = 0;
    if (v < 128 && v > -129) {
        inRange = 1;
    }
    return inRange ? v : (v > 0) ? 127 : -128;
}

static s32 scalingClampU8(s32 value) {
    if ((value >> 19) == 0) {
        return value >> 11;
    }
    return value < 0 ? 0 : 255;
}

void TMCJPEGDEC_IdctBlock_Lumi(s32* block, u8* conv_row_ptr, u16 pitch, s32 zigzag) {
    s32 tmp[64];
    s32* dst;
    s32 done;
    s32 iter;
    s32 i;
    s32 e;
    s32 b2;
    s32 b3;
    s32 b4;
    s32 b5;
    s32 b6;
    s32 b7;
    s32 v;
    s32 m;
    s32 a;
    s32 d;
    s32 z;
    s32 o;
    s32 p;
    s32 p_part;
    s32 t;
    s32 u;
    s32 r;
    s32 n;
    s32 y;
    s32 x_factor;
    s32 z_factor;
    s32 m_part;
    s32 q;
    s32 w;
    s32 x;
    s32 b1;

    r = (zigzag >> 4) * 8;
    dst = tmp;
    done = 0;
    {
        for (; done < r; done += 8) {
            u32 ac;
            b4 = block[4];
            b6 = block[6];
            b2 = block[2];
            b1 = block[1];
            b7 = block[7];
            b5 = block[5];
            b3 = block[3];

            ac = (u32)b4;
            ac |= (u32)b6;
            ac |= (u32)b2;
            ac |= (u32)b1;
            ac |= (u32)b7;
            ac |= (u32)b5;
            ac |= (u32)b3;
            if (ac == 0) {
                s32 val = block[0];
                dst[7] = val;
                dst[6] = val;
                dst[5] = val;
                dst[4] = val;
                dst[3] = val;
                dst[2] = val;
                dst[1] = val;
                dst[0] = val;
            } else {
                s32 oddLowSum;
                s32 oddHighSum;
                s32 oddLowDifference;
                s32 oddHighDifference;
                s32 dcValue;
                
                t = b2 - b6;
                oddLowSum = b5 + b3;
                oddLowDifference = b5 - b3;
                oddHighSum = b1 + b7;
                oddHighDifference = b1 - b7;
                u = b6 + b2;
                t = t * 0xB5 >> 8;
                x_factor = oddHighSum - oddLowSum;
                z_factor = oddLowDifference + oddHighDifference;
                dcValue = block[0];
                a = dcValue - b4;
                x = x_factor * 0xB5 >> 8;
                d = dcValue + b4;
                u = t + u;
                v = a + t;
                z = z_factor * 0x62 >> 8;
                w = d + u;
                y = d - u;
                m_part = oddHighDifference * 0x14E >> 8;
                e = a - t;
                m = m_part - z;
                oddLowSum += m;
                n = oddHighSum + oddLowSum;
                o = x + m;
                dst[0] = w + n;
                p_part = oddLowDifference * 0x8B;
                dst[7] = w - n;
                p_part >>= 8;
                dst[1] = v + o;
                p = z + p_part;
                q = p + x;
                dst[6] = v - o;
                dst[2] = e + q;
                dst[5] = e - q;
                dst[3] = y + p;
                dst[4] = y - p;
            }
            block += 8;
            dst += 8;
        }
    }

    dst = tmp + done;
    for (; done <= 0x38; done += 8) {
        memset(dst, 0, 0x20);
        dst += 8;
    }

    r = pitch * 8 - pitch;
    z = pitch * 4;
    m = pitch * 2;
    dst = tmp + 7;
    for (iter = 8, i = 7; iter > 0; iter--, i--) {
        u32 ac;
        u8* out;

        b4 = dst[0x20];
        b6 = dst[0x30];
        b2 = dst[0x10];
        b1 = dst[8];
        b7 = dst[0x38];
        b5 = dst[0x28];
        b3 = dst[0x18];

        ac = (u32)b4;
            ac |= (u32)b6;
            ac |= (u32)b2;
            ac |= (u32)b1;
            ac |= (u32)b7;
            ac |= (u32)b5;
            ac |= (u32)b3;
        out = conv_row_ptr + i;
        if (ac == 0) {
            u8 val = clampU8((*dst >> 11) + 0x80);
            out[r] = val;
            out[pitch * 6] = val;
            out[z + pitch] = val;
            out[z] = val;
            out[z - pitch] = val;
            out[m] = val;
            out[pitch] = val;
            out[0] = val;
        } else {
            s32 oddLowSum;
            s32 oddHighSum;
            s32 dcValue;
            
            t = b2 - b6;
            oddLowSum = b5 + b3;
            b5 = b5 - b3;
            oddHighSum = b1 + b7;
            b1 = b1 - b7;
            u = b6 + b2;
            b2 = t * 0xB5 >> 8;
            x_factor = oddHighSum - oddLowSum;
            z_factor = b5 + b1;
            dcValue = *dst + 0x40000;
            a = dcValue - b4;
            x = x_factor * 0xB5 >> 8;
            d = dcValue + b4;
            u = b2 + u;
            v = a + b2;
            z_factor = z_factor * 0x62 >> 8;
            w = d + u;
            y = d - u;
            m_part = b1 * 0x14E >> 8;
            e = a - b2;
            m_part = m_part - z_factor;
            oddLowSum += m_part;
            n = oddHighSum + oddLowSum;
            o = x + m_part;
            p_part = b5 * 0x8B >> 8;
            p = z_factor + p_part;
            q = p + x;
            out[0] = scalingClampU8(w + n);
            out[r] = scalingClampU8(w - n);
            out[pitch] = scalingClampU8(v + o);
            out[pitch * 6] = scalingClampU8(v - o);
            out[m] = scalingClampU8(e + q);
            out[z + pitch] = scalingClampU8(e - q);
            out[z - pitch] = scalingClampU8(y + p);
            out[z] = scalingClampU8(y - p);
        }
        dst--;
    }
}

void TMCJPEGDEC_IdctBlock_Col(s32* block, u8* conv_row_ptr, u16 pitch, s32 zigzag) {
    s32 tmp[64];
    s32* dst;
    s32 done;
    s32 iter;
    s32 d;
    s32 b1;
    s32 b2;
    s32 b3;
    s32 b4;
    s32 b5;
    s32 b6;
    s32 b7;
    s32 v;
    s32 r;
    s32 a;
    s32 i;
    s32 m;
    s32 n;
    s32 o;
    s32 x;
    s32 q;
    s32 y;
    s32 u;
    s32 w;
    s32 p;
    s32 t;
    s32 z;
    s32 x_factor;
    s32 z_factor;
    s32 m_part;
    s32 p_part;
    s32 e;

    if (zigzag == 0x11) {
        s32 val;
        val = clampS8(block[0] >> 11);
        memset(conv_row_ptr, (s8)val, 0x40);
        return;
    }

    r = (zigzag >> 4) * 8;
    if ((zigzag & 0xF) > 2) {
        goto mode_gt_2;
    }

    dst = tmp;
    done = 0;
    for (; done < r; done += 8) {
        s32 dcValue;
        s32 oddCoefficient;

        oddCoefficient = block[1];
        dcValue = block[0];
        t = oddCoefficient * 0xB5 >> 8;
        v = oddCoefficient * 0x62 >> 8;
        u = v + t;
        z = (oddCoefficient * 0x14E >> 8) - v;
        m = oddCoefficient + z;
        n = t + z;
        dst[0] = dcValue + m;
        dst[7] = dcValue - m;
        dst[1] = dcValue + n;
        dst[6] = dcValue - n;
        dst[2] = dcValue + u;
        dst[5] = dcValue - u;
        dst[3] = dcValue + v;
        dst[4] = dcValue - v;
        dst += 8;
        block += 8;
    }
    dst = tmp + done;
    for (; done <= 0x38; done += 8) {
        memset(dst, 0, 0x20);
        dst += 8;
    }
    goto epilogue;

mode_gt_2:
    dst = tmp;
    done = 0;
    for (; done < r; done += 8) {
            u32 ac;
            b4 = block[4];
            b6 = block[6];
            b2 = block[2];
            b1 = block[1];
            b7 = block[7];
            b5 = block[5];
            b3 = block[3];

            ac = (u32)b4;
            ac |= (u32)b6;
            ac |= (u32)b2;
            ac |= (u32)b1;
            ac |= (u32)b7;
            ac |= (u32)b5;
            ac |= (u32)b3;
            if (ac == 0) {
                s32 val;
                val = block[0];
                dst[7] = val;
                dst[6] = val;
                dst[5] = val;
                dst[4] = val;
                dst[3] = val;
                dst[2] = val;
                dst[1] = val;
                dst[0] = val;
            } else {
                s32 oddLowSum;
                s32 oddLowDifference;
                s32 oddHighSum;
                s32 oddHighDifference;
                s32 dcValue;
                
                t = b2 - b6;
                oddLowSum = b5 + b3;
                oddLowDifference = b5 - b3;
                oddHighSum = b1 + b7;
                oddHighDifference = b1 - b7;
                u = b6 + b2;
                t = t * 0xB5 >> 8;
                x_factor = oddHighSum - oddLowSum;
                z_factor = oddLowDifference + oddHighDifference;
                dcValue = block[0];
                a = dcValue - b4;
                x = x_factor * 0xB5 >> 8;
                d = dcValue + b4;
                u = t + u;
                v = a + t;
                z = z_factor * 0x62 >> 8;
                w = d + u;
                y = d - u;
                m_part = oddHighDifference * 0x14E >> 8;
                e = a - t;
                m = m_part - z;
                oddLowSum += m;
                n = oddHighSum + oddLowSum;
                o = x + m;
                dst[0] = w + n;
                p_part = oddLowDifference * 0x8B;
                dst[7] = w - n;
                p_part >>= 8;
                dst[1] = v + o;
                p = z + p_part;
                q = p + x;
                dst[6] = v - o;
                dst[2] = e + q;
                dst[5] = e - q;
                dst[3] = y + p;
                dst[4] = y - p;
            }
            block += 8;
            dst += 8;
    }

    dst = tmp + done;
    for (; done <= 0x38; done += 8) {
        memset(dst, 0, 0x20);
        dst += 8;
    }

epilogue:

    dst = tmp + 7;
    for (iter = 8, i = 7; iter > 0; iter--, i--) {
        u32 ac;
        u8* output;
        b4 = dst[0x20];
        output = conv_row_ptr + i;
        b6 = dst[0x30];
        b2 = dst[0x10];
        b1 = dst[8];
        b7 = dst[0x38];
        b5 = dst[0x28];
        b3 = dst[0x18];

        ac = (u32)b4;
        ac |= (u32)b6;
        ac |= (u32)b2;
        ac |= (u32)b1;
        ac |= (u32)b7;
        ac |= (u32)b5;
        ac |= (u32)b3;
        if (ac == 0) {
            s32 val;
            val = clampS8(*dst >> 11);
            output[56] = (u8)val;
            output[48] = (u8)val;
            output[40] = (u8)val;
            output[32] = (u8)val;
            output[24] = (u8)val;
            output[16] = (u8)val;
            output[8] = (u8)val;
            output[0] = (u8)val;
        } else {
            s32 oddLowSum;
            s32 oddLowDifference;
            s32 oddHighSum;
            s32 oddHighDifference;
            s32 dcValue;
            
            t = b2 - b6;
            oddLowSum = b5 + b3;
            oddLowDifference = b5 - b3;
            oddHighSum = b1 + b7;
            oddHighDifference = b1 - b7;
            u = b6 + b2;
            t = t * 0xB5 >> 8;
            x_factor = oddHighSum - oddLowSum;
            z_factor = oddLowDifference + oddHighDifference;
            dcValue = *dst;
            a = dcValue - b4;
            x = x_factor * 0xB5 >> 8;
            d = dcValue + b4;
            u = t + u;
            v = a + t;
            z = z_factor * 0x62 >> 8;
            w = d + u;
            y = d - u;
            m_part = oddHighDifference * 0x14E >> 8;
            e = a - t;
            m = m_part - z;
            oddLowSum += m;
            n = oddHighSum + oddLowSum;
            o = x + m;
            p_part = oddLowDifference * 0x8B >> 8;
            p = z + p_part;
            q = p + x;
            output[0] = (u8)clampS8((w + n) >> 11);
            output[56] = (u8)clampS8((w - n) >> 11);
            output[8] = (u8)clampS8((v + o) >> 11);
            output[48] = (u8)clampS8((v - o) >> 11);
            output[16] = (u8)clampS8((e + q) >> 11);
            output[40] = (u8)clampS8((e - q) >> 11);
            output[24] = (u8)clampS8((y + p) >> 11);
            output[32] = (u8)clampS8((y - p) >> 11);
        }
        dst--;
    }
}
