#include <string.h>
#include <tmc_jpeg_internal.h>

static s32 clampU8(s32 value) {
    s32 inRange;
    inRange = 0;
    if (value < 256 && value > -1) {
        inRange = 1;
    }
    if (inRange) {
        return value;
    }
    if (value < 0) {
        return 0;
    }
    return 255;
}

static s32 clampS8(s32 value) {
    s32 inRange = 0;
    if (value < 128 && value > -129) {
        inRange = 1;
    }
    return inRange ? value : (value > 0) ? 127 : -128;
}

static s32 scalingClampU8(s32 value) {
    if ((value >> 19) == 0) {
        return value >> 11;
    }
    return value < 0 ? 0 : 255;
}

void TMCJPEGDEC_IdctBlock_Lumi(s32* block, u8* conv_row_ptr, u16 pitch, s32 zigzag) {
    s32 workspace[64];
    s32 pitch4;
    s32* dst;
    s32* src;
    s32 pitch7;
    s32 rowCount;
    s32 pitch6;
    s32 pitch5;
    s32 pitch3;
    s32 pitch2;
    s32 processed;
    s32 column;

    rowCount = (zigzag >> 4) * 8;
    dst = workspace;
    for (processed = 0; processed < rowCount; processed += 8) {
        s32 c1;
        s32 c2;
        int acBits;
        s32 c7;
        s32 c5;
        s32 c4;
        s32 c3;
        s32 c6;
        c4 = block[4];
        c6 = block[6];
        c2 = block[2];
        c1 = block[1];
        c7 = block[7];
        c5 = block[5];
        c3 = block[3];
        acBits = c4 | c6;
        acBits = c2 | acBits;
        acBits = c1 | acBits;
        acBits = c7 | acBits;
        acBits = c5 | acBits;
        acBits = c3 | acBits;
        if (acBits == 0) {
            s32 dc = block[0];
            dst[7] = dc;
            dst[6] = dc;
            dst[5] = dc;
            dst[4] = dc;
            dst[3] = dc;
            dst[2] = dc;
            dst[1] = dc;
            dst[0] = dc;
        } else {
            s32 dc;
            s32 evenSum;
            s32 oddSumRotation;
            s32 oddOutput0;
            s32 evenRotationSum;
            s32 evenRotation;
            s32 oddLowDifference;
            s32 oddDifferenceRotation;
            s32 evenOutput3;
            s32 oddOutput1;
            s32 oddHighSum;
            s32 oddOutput2;
            s32 evenBaseSum;
            s32 evenOutput0;
            s32 oddDifferenceSum;
            s32 evenOutput2;
            s32 oddMix;
            s32 oddLowRotation;
            s32 oddOutput3;
            s32 evenOutput1;
            s32 oddHighRotation;
            s32 oddLowSum;
            s32 oddSumDifference;
            s32 evenBaseDifference;
            s32 oddHighDifference;
            oddHighSum = c1 + c7;
            dc = block[0];
            evenSum = c6 + c2;
            oddLowDifference = c5 - c3;
            oddHighDifference = c1 - c7;
            evenRotation = c2 - c6;
            c2 = evenRotation * 0xB5 >> 8;
            evenBaseDifference = dc - c4;
            oddLowSum = c5 + c3;
            oddSumDifference = oddHighSum - oddLowSum;
            oddSumRotation = oddSumDifference * 0xB5 >> 8;
            oddDifferenceSum = oddLowDifference + oddHighDifference;
            oddDifferenceRotation = oddDifferenceSum * 0x62 >> 8;
            oddLowRotation = oddLowDifference * 0x8B;
            oddHighRotation = oddHighDifference * 0x14E >> 8;
            evenRotationSum = c2 + evenSum;
            evenOutput1 = evenBaseDifference + c2;
            oddLowRotation >>= 8;
            evenBaseSum = dc + c4;
            oddMix = oddHighRotation - oddDifferenceRotation;
            evenOutput2 = evenBaseDifference - c2;
            oddOutput1 = oddSumRotation + oddMix;
            evenOutput3 = evenBaseSum - evenRotationSum;
            oddLowSum += oddMix;
            evenOutput0 = evenBaseSum + evenRotationSum;
            oddOutput0 = oddHighSum + oddLowSum;
            oddOutput3 = oddDifferenceRotation + oddLowRotation;
            oddOutput2 = oddOutput3 + oddSumRotation;
            dst[0] = evenOutput0 + oddOutput0;
            dst[7] = evenOutput0 - oddOutput0;
            dst[1] = evenOutput1 + oddOutput1;
            dst[6] = evenOutput1 - oddOutput1;
            dst[2] = evenOutput2 + oddOutput2;
            dst[5] = evenOutput2 - oddOutput2;
            dst[3] = evenOutput3 + oddOutput3;
            dst[4] = evenOutput3 - oddOutput3;
        }
        block += 8;
        dst += 8;
    }

    dst = workspace + processed;
    for (; processed <= 56; processed += 8) {
        memset(dst, 0, 32);
        dst += 8;
    }

    src = workspace + 7;
    pitch4 = pitch * 4;
    pitch5 = pitch4 + pitch;
    pitch3 = pitch4 - pitch;
    pitch2 = pitch * 2;
    pitch6 = pitch * 6;
    pitch7 = pitch * 8 - pitch;
    for (column = 7; column >= 0; column--) {
        s32 c1;
        s32 c2;
        s32 c5;
        s32 c3;
        s32 c6;
        s32 c4;
        s32 c7;
        int acBits;
        u8* output;
        c4 = src[32];
        c6 = src[48];
        c2 = src[16];
        c1 = src[8];
        c7 = src[56];
        c5 = src[40];
        c3 = src[24];
        acBits = c4 | c6;
        acBits = c2 | acBits;
        acBits = c1 | acBits;
        acBits = c7 | acBits;
        acBits = c5 | acBits;
        acBits = c3 | acBits;
        output = conv_row_ptr + column;
        if (acBits == 0) {
            u8 sample = clampU8((*src >> 11) + 0x80);
            output[pitch7] = sample;
            output[pitch6] = sample;
            output[pitch5] = sample;
            output[pitch4] = sample;
            output[pitch3] = sample;
            output[pitch2] = sample;
            output[pitch] = sample;
            output[0] = sample;
        } else {
            s32 oddDifferenceSum;
            s32 oddSumRotation;
            s32 evenBaseSum;
            s32 evenOutput2;
            s32 dc;
            s32 evenBaseDifference;
            s32 evenOutput0;
            s32 evenOutput1;
            s32 evenOutput3;
            s32 oddHighRotation;
            s32 oddMix;
            s32 oddHighDifference;
            s32 oddLowSum;
            s32 oddLowRotation;
            s32 evenRotation;
            s32 oddLowDifference;
            s32 oddSumDifference;
            s32 oddHighSum;
            s32 evenRotationSum;
            s32 oddOutput0;
            s32 evenSum;
            s32 oddOutput2;
            s32 oddDifferenceRotation;
            s32 oddOutput1;
            s32 oddOutput3;
            evenSum = c6 + c2;
            evenRotation = c2 - c6;
            oddLowSum = c5 + c3;
            oddHighDifference = c1 - c7;
            oddLowDifference = c5 - c3;
            oddHighSum = c1 + c7;
            c2 = evenRotation * 0xB5 >> 8;
            dc = *src + 0x40000;
            oddDifferenceSum = oddLowDifference + oddHighDifference;
            oddSumDifference = oddHighSum - oddLowSum;
            oddSumRotation = oddSumDifference * 0xB5 >> 8;
            evenBaseSum = dc + c4;
            oddDifferenceRotation = oddDifferenceSum * 0x62 >> 8;
            oddHighRotation = oddHighDifference * 0x14E >> 8;
            evenRotationSum = c2 + evenSum;
            oddMix = oddHighRotation - oddDifferenceRotation;
            oddLowSum += oddMix;
            evenOutput0 = evenBaseSum + evenRotationSum;
            evenBaseDifference = dc - c4;
            evenOutput3 = evenBaseSum - evenRotationSum;
            evenOutput1 = evenBaseDifference + c2;
            oddOutput0 = oddHighSum + oddLowSum;
            oddLowRotation = oddLowDifference * 0x8B >> 8;
            oddOutput3 = oddDifferenceRotation + oddLowRotation;
            evenOutput2 = evenBaseDifference - c2;
            oddOutput2 = oddOutput3 + oddSumRotation;
            oddOutput1 = oddSumRotation + oddMix;
            output[0] = scalingClampU8(evenOutput0 + oddOutput0);
            output[pitch7] = scalingClampU8(evenOutput0 - oddOutput0);
            output[pitch] = scalingClampU8(evenOutput1 + oddOutput1);
            output[pitch6] = scalingClampU8(evenOutput1 - oddOutput1);
            output[pitch2] = scalingClampU8(evenOutput2 + oddOutput2);
            output[pitch5] = scalingClampU8(evenOutput2 - oddOutput2);
            output[pitch3] = scalingClampU8(evenOutput3 + oddOutput3);
            output[pitch4] = scalingClampU8(evenOutput3 - oddOutput3);
        }
        src--;
    }
}

void TMCJPEGDEC_IdctBlock_Col(s32* block, u8* conv_row_ptr, u16 pitch, s32 zigzag) {
    s32 workspace[64];
    s32* src;
    s32 column;
    s32 rowCount;
    s32 processed;
    s32* dst;

    if (zigzag == 0x11) {
        s32 dc = block[0];
        s32 sample = clampS8(dc >> 11);
        memset(conv_row_ptr, (s8)sample, 64);
        return;
    }

    rowCount = (zigzag >> 4) * 8;
    if ((zigzag & 0xF) <= 2) {
        dst = workspace;
        for (processed = 0; processed < rowCount; processed += 8) {
            s32 mid;
            s32 odd;
            s32 outer;
            s32 dc;
            s32 inner;
            s32 rotation;
            s32 lowRotation;
            s32 mix;
            odd = block[1];
            rotation = odd * 0xB5 >> 8;
            lowRotation = odd * 0x62 >> 8;
            dc = block[0];
            mix = (odd * 0x14E >> 8) - lowRotation;
            outer = odd + mix;
            dst[0] = dc + outer;
            inner = rotation + mix;
            dst[7] = dc - outer;
            dst[1] = dc + inner;
            mid = lowRotation + rotation;
            dst[6] = dc - inner;
            dst[2] = dc + mid;
            dst[5] = dc - mid;
            dst[3] = dc + lowRotation;
            dst[4] = dc - lowRotation;
            dst += 8;
            block += 8;
        }
        dst = workspace + processed;
        for (; processed <= 56; processed += 8) {
            memset(dst, 0, 32);
            dst += 8;
        }
    } else {
        dst = workspace;
        for (processed = 0; processed < rowCount; processed += 8) {
            s32 c2;
            s32 c7;
            s32 c3;
            s32 c5;
            s32 c1;
            s32 c6;
            int acBits;
            s32 c4;
            c4 = block[4];
            c6 = block[6];
            c2 = block[2];
            c1 = block[1];
            c7 = block[7];
            c5 = block[5];
            c3 = block[3];
            acBits = c4 | c6;
            acBits = c2 | acBits;
            acBits = c1 | acBits;
            acBits = c7 | acBits;
            acBits = c5 | acBits;
            acBits = c3 | acBits;
            if (acBits == 0) {
                s32 dc = block[0];
                dst[7] = dc;
                dst[6] = dc;
                dst[5] = dc;
                dst[4] = dc;
                dst[3] = dc;
                dst[2] = dc;
                dst[1] = dc;
                dst[0] = dc;
            } else {
                s32 evenBaseDifference;
                s32 oddOutput3;
                s32 oddMix;
                s32 evenOutput1;
                s32 evenOutput2;
                s32 oddDifferenceRotation;
                s32 oddLowRotation;
                s32 oddDifferenceSum;
                s32 evenSum;
                s32 oddLowSum;
                s32 dc;
                s32 oddSumDifference;
                s32 oddLowDifference;
                s32 evenBaseSum;
                s32 oddSumRotation;
                s32 evenRotationSum;
                s32 evenRotation;
                s32 evenOutput0;
                s32 oddOutput1;
                s32 oddHighDifference;
                s32 oddOutput0;
                s32 evenOutput3;
                s32 oddHighSum;
                s32 oddOutput2;
                s32 oddHighRotation;
                oddHighDifference = c1 - c7;
                oddLowSum = c5 + c3;
                evenSum = c6 + c2;
                oddHighSum = c1 + c7;
                evenRotation = c2 - c6;
                dc = block[0];
                evenBaseDifference = dc - c4;
                c2 = evenRotation * 0xB5 >> 8;
                oddSumDifference = oddHighSum - oddLowSum;
                oddLowDifference = c5 - c3;
                oddSumRotation = oddSumDifference * 0xB5 >> 8;
                evenBaseSum = dc + c4;
                oddHighRotation = oddHighDifference * 0x14E >> 8;
                oddDifferenceSum = oddLowDifference + oddHighDifference;
                oddDifferenceRotation = oddDifferenceSum * 0x62 >> 8;
                evenRotationSum = c2 + evenSum;
                oddMix = oddHighRotation - oddDifferenceRotation;
                oddOutput1 = oddSumRotation + oddMix;
                evenOutput1 = evenBaseDifference + c2;
                oddLowRotation = oddLowDifference * 0x8B;
                oddLowSum += oddMix;
                evenOutput3 = evenBaseSum - evenRotationSum;
                evenOutput0 = evenBaseSum + evenRotationSum;
                oddLowRotation >>= 8;
                oddOutput3 = oddDifferenceRotation + oddLowRotation;
                evenOutput2 = evenBaseDifference - c2;
                oddOutput0 = oddHighSum + oddLowSum;
                dst[0] = evenOutput0 + oddOutput0;
                dst[7] = evenOutput0 - oddOutput0;
                dst[1] = evenOutput1 + oddOutput1;
                oddOutput2 = oddOutput3 + oddSumRotation;
                dst[6] = evenOutput1 - oddOutput1;
                dst[2] = evenOutput2 + oddOutput2;
                dst[5] = evenOutput2 - oddOutput2;
                dst[3] = evenOutput3 + oddOutput3;
                dst[4] = evenOutput3 - oddOutput3;
            }
            block += 8;
            dst += 8;
        }
        dst = workspace + processed;
        for (; processed <= 56; processed += 8) {
            memset(dst, 0, 32);
            dst += 8;
        }
    }

    src = workspace + 7;
    for (column = 7; column >= 0; column--) {
        s32 c1;
        s32 c3;
        int acBits;
        s32 c7;
        s32 c2;
        s32 c5;
        u8* output;
        s32 c6;
        s32 c4;
        c4 = src[32];
        output = conv_row_ptr + column;
        c6 = src[48];
        c2 = src[16];
        c1 = src[8];
        c7 = src[56];
        c5 = src[40];
        c3 = src[24];
        acBits = c4 | c6;
        acBits = c2 | acBits;
        acBits = c1 | acBits;
        acBits = c7 | acBits;
        acBits = c5 | acBits;
        acBits = c3 | acBits;
        if (acBits == 0) {
            s32 sample = clampS8(*src >> 11);
            output[56] = (u8)sample;
            output[48] = (u8)sample;
            output[40] = (u8)sample;
            output[32] = (u8)sample;
            output[24] = (u8)sample;
            output[16] = (u8)sample;
            output[8] = (u8)sample;
            output[0] = (u8)sample;
        } else {
            s32 evenSum;
            s32 evenOutput2;
            s32 oddOutput0;
            s32 oddMix;
            s32 evenBaseSum;
            s32 oddHighRotation;
            s32 evenRotationSum;
            s32 oddSumDifference;
            s32 evenOutput1;
            s32 oddHighSum;
            s32 evenOutput0;
            s32 oddOutput1;
            s32 oddDifferenceSum;
            s32 oddLowSum;
            s32 oddOutput3;
            s32 evenBaseDifference;
            s32 oddHighDifference;
            s32 oddOutput2;
            s32 dc;
            s32 oddLowDifference;
            s32 evenOutput3;
            s32 oddDifferenceRotation;
            s32 oddLowRotation;
            s32 evenRotation;
            s32 oddSumRotation;
            oddHighSum = c1 + c7;
            evenRotation = c2 - c6;
            oddLowSum = c5 + c3;
            oddSumDifference = oddHighSum - oddLowSum;
            evenSum = c6 + c2;
            oddLowDifference = c5 - c3;
            c2 = evenRotation * 0xB5 >> 8;
            oddHighDifference = c1 - c7;
            dc = *src;
            evenRotationSum = c2 + evenSum;
            oddSumRotation = oddSumDifference * 0xB5 >> 8;
            oddDifferenceSum = oddLowDifference + oddHighDifference;
            oddDifferenceRotation = oddDifferenceSum * 0x62 >> 8;
            evenBaseDifference = dc - c4;
            evenBaseSum = dc + c4;
            oddHighRotation = oddHighDifference * 0x14E >> 8;
            oddMix = oddHighRotation - oddDifferenceRotation;
            evenOutput3 = evenBaseSum - evenRotationSum;
            evenOutput1 = evenBaseDifference + c2;
            evenOutput2 = evenBaseDifference - c2;
            evenOutput0 = evenBaseSum + evenRotationSum;
            oddLowRotation = oddLowDifference * 0x8B >> 8;
            oddOutput3 = oddDifferenceRotation + oddLowRotation;
            oddLowSum += oddMix;
            oddOutput1 = oddSumRotation + oddMix;
            oddOutput0 = oddHighSum + oddLowSum;
            oddOutput2 = oddOutput3 + oddSumRotation;
            output[0] = (u8)clampS8((evenOutput0 + oddOutput0) >> 11);
            output[56] = (u8)clampS8((evenOutput0 - oddOutput0) >> 11);
            output[8] = (u8)clampS8((evenOutput1 + oddOutput1) >> 11);
            output[48] = (u8)clampS8((evenOutput1 - oddOutput1) >> 11);
            output[16] = (u8)clampS8((evenOutput2 + oddOutput2) >> 11);
            output[40] = (u8)clampS8((evenOutput2 - oddOutput2) >> 11);
            output[24] = (u8)clampS8((evenOutput3 + oddOutput3) >> 11);
            output[32] = (u8)clampS8((evenOutput3 - oddOutput3) >> 11);
        }
        src--;
    }
}

