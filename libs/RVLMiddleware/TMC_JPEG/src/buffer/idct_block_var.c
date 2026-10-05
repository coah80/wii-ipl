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
    s32* workspaceCursor;
    s32 evenBaseSum;
    s32 evenRotation;
    s32 column;
    s32 evenOutput3;
    s32 coefficient2;
    s32 coefficient1;
    s32 coefficient4;
    s32 coefficient5;
    s32 coefficient6;
    s32 coefficient7;
    s32 oddOutput0;
    s32 m;
    s32 evenBaseDifference;
    s32 processedCoefficients;
    s32 z;
    s32 evenOutput1;
    s32 oddOutput3;
    s32 oddLowRotation;
    s32 oddHighRotation;
    s32 evenRotationSum;
    s32 r;
    s32 oddOutput1;
    s32 oddSumRotation;
    s32 oddSumDifference;
    s32 oddDifferenceSum;
    s32 columnsRemaining;
    s32 oddOutput2;
    s32 evenOutput0;
    s32 evenOutput2;
    s32 coefficient3;

    r = (zigzag >> 4) * 8;
    workspaceCursor = workspace;
    processedCoefficients = 0;
    {
        for (; processedCoefficients < r; processedCoefficients += 8) {
            u32 acBits;
            coefficient4 = block[4];
            coefficient6 = block[6];
            coefficient2 = block[2];
            coefficient1 = block[1];
            coefficient7 = block[7];
            coefficient5 = block[5];
            coefficient3 = block[3];

            acBits = (u32)coefficient4;
            acBits |= (u32)coefficient6;
            acBits |= (u32)coefficient2;
            acBits |= (u32)coefficient1;
            acBits |= (u32)coefficient7;
            acBits |= (u32)coefficient5;
            acBits |= (u32)coefficient3;
            if (acBits == 0) {
                s32 sample = block[0];
                workspaceCursor[7] = sample;
                workspaceCursor[6] = sample;
                workspaceCursor[5] = sample;
                workspaceCursor[4] = sample;
                workspaceCursor[3] = sample;
                workspaceCursor[2] = sample;
                workspaceCursor[1] = sample;
                workspaceCursor[0] = sample;
            } else {
                s32 oddLowSum;
                s32 oddHighSum;
                s32 oddLowDifference;
                s32 oddHighDifference;
                s32 dcValue;
                
                evenRotation = coefficient2 - coefficient6;
                oddLowSum = coefficient5 + coefficient3;
                oddLowDifference = coefficient5 - coefficient3;
                oddHighSum = coefficient1 + coefficient7;
                oddHighDifference = coefficient1 - coefficient7;
                evenRotationSum = coefficient6 + coefficient2;
                evenRotation = evenRotation * 0xB5 >> 8;
                oddSumDifference = oddHighSum - oddLowSum;
                oddDifferenceSum = oddLowDifference + oddHighDifference;
                dcValue = block[0];
                evenBaseDifference = dcValue - coefficient4;
                oddSumRotation = oddSumDifference * 0xB5 >> 8;
                evenBaseSum = dcValue + coefficient4;
                evenRotationSum = evenRotation + evenRotationSum;
                evenOutput1 = evenBaseDifference + evenRotation;
                z = oddDifferenceSum * 0x62 >> 8;
                evenOutput0 = evenBaseSum + evenRotationSum;
                evenOutput3 = evenBaseSum - evenRotationSum;
                oddHighRotation = oddHighDifference * 0x14E >> 8;
                evenOutput2 = evenBaseDifference - evenRotation;
                m = oddHighRotation - z;
                oddLowSum += m;
                oddOutput0 = oddHighSum + oddLowSum;
                oddOutput1 = oddSumRotation + m;
                workspaceCursor[0] = evenOutput0 + oddOutput0;
                oddLowRotation = oddLowDifference * 0x8B;
                workspaceCursor[7] = evenOutput0 - oddOutput0;
                oddLowRotation >>= 8;
                workspaceCursor[1] = evenOutput1 + oddOutput1;
                oddOutput3 = z + oddLowRotation;
                oddOutput2 = oddOutput3 + oddSumRotation;
                workspaceCursor[6] = evenOutput1 - oddOutput1;
                workspaceCursor[2] = evenOutput2 + oddOutput2;
                workspaceCursor[5] = evenOutput2 - oddOutput2;
                workspaceCursor[3] = evenOutput3 + oddOutput3;
                workspaceCursor[4] = evenOutput3 - oddOutput3;
            }
            block += 8;
            workspaceCursor += 8;
        }
    }

    workspaceCursor = workspace + processedCoefficients;
    for (; processedCoefficients <= 0x38; processedCoefficients += 8) {
        memset(workspaceCursor, 0, 0x20);
        workspaceCursor += 8;
    }

    r = pitch * 8 - pitch;
    z = pitch * 4;
    m = pitch * 2;
    workspaceCursor = workspace + 7;
    for (columnsRemaining = 8, column = 7; columnsRemaining > 0; columnsRemaining--, column--) {
        u32 acBits;
        u8* output;

        coefficient4 = workspaceCursor[0x20];
        coefficient6 = workspaceCursor[0x30];
        coefficient2 = workspaceCursor[0x10];
        coefficient1 = workspaceCursor[8];
        coefficient7 = workspaceCursor[0x38];
        coefficient5 = workspaceCursor[0x28];
        coefficient3 = workspaceCursor[0x18];

        acBits = (u32)coefficient4;
            acBits |= (u32)coefficient6;
            acBits |= (u32)coefficient2;
            acBits |= (u32)coefficient1;
            acBits |= (u32)coefficient7;
            acBits |= (u32)coefficient5;
            acBits |= (u32)coefficient3;
        output = conv_row_ptr + column;
        if (acBits == 0) {
            u8 sample = clampU8((*workspaceCursor >> 11) + 0x80);
            output[r] = sample;
            output[pitch * 6] = sample;
            output[z + pitch] = sample;
            output[z] = sample;
            output[z - pitch] = sample;
            output[m] = sample;
            output[pitch] = sample;
            output[0] = sample;
        } else {
            s32 oddLowSum;
            s32 oddHighSum;
            s32 dcValue;
            
            evenRotation = coefficient2 - coefficient6;
            oddLowSum = coefficient5 + coefficient3;
            coefficient5 = coefficient5 - coefficient3;
            oddHighSum = coefficient1 + coefficient7;
            coefficient1 = coefficient1 - coefficient7;
            evenRotationSum = coefficient6 + coefficient2;
            coefficient2 = evenRotation * 0xB5 >> 8;
            oddSumDifference = oddHighSum - oddLowSum;
            oddDifferenceSum = coefficient5 + coefficient1;
            dcValue = *workspaceCursor + 0x40000;
            evenBaseDifference = dcValue - coefficient4;
            oddSumRotation = oddSumDifference * 0xB5 >> 8;
            evenBaseSum = dcValue + coefficient4;
            evenRotationSum = coefficient2 + evenRotationSum;
            evenOutput1 = evenBaseDifference + coefficient2;
            oddDifferenceSum = oddDifferenceSum * 0x62 >> 8;
            evenOutput0 = evenBaseSum + evenRotationSum;
            evenOutput3 = evenBaseSum - evenRotationSum;
            oddHighRotation = coefficient1 * 0x14E >> 8;
            evenOutput2 = evenBaseDifference - coefficient2;
            oddHighRotation = oddHighRotation - oddDifferenceSum;
            oddLowSum += oddHighRotation;
            oddOutput0 = oddHighSum + oddLowSum;
            oddOutput1 = oddSumRotation + oddHighRotation;
            oddLowRotation = coefficient5 * 0x8B >> 8;
            oddOutput3 = oddDifferenceSum + oddLowRotation;
            oddOutput2 = oddOutput3 + oddSumRotation;
            output[0] = scalingClampU8(evenOutput0 + oddOutput0);
            output[r] = scalingClampU8(evenOutput0 - oddOutput0);
            output[pitch] = scalingClampU8(evenOutput1 + oddOutput1);
            output[pitch * 6] = scalingClampU8(evenOutput1 - oddOutput1);
            output[m] = scalingClampU8(evenOutput2 + oddOutput2);
            output[z + pitch] = scalingClampU8(evenOutput2 - oddOutput2);
            output[z - pitch] = scalingClampU8(evenOutput3 + oddOutput3);
            output[z] = scalingClampU8(evenOutput3 - oddOutput3);
        }
        workspaceCursor--;
    }
}

void TMCJPEGDEC_IdctBlock_Col(s32* block, u8* conv_row_ptr, u16 pitch, s32 zigzag) {
    s32 workspace[64];
    s32* workspaceCursor;
    s32 evenBaseDifference;
    s32 columnsRemaining;
    s32 evenBaseSum;
    s32 coefficient1;
    s32 coefficient2;
    s32 coefficient3;
    s32 coefficient4;
    s32 coefficient5;
    s32 coefficient6;
    s32 coefficient7;
    s32 v;
    s32 rowCoefficientCount;
    s32 processedCoefficients;
    s32 column;
    s32 m;
    s32 n;
    s32 oddOutput1;
    s32 oddSumRotation;
    s32 oddOutput2;
    s32 evenOutput2;
    s32 u;
    s32 evenOutput0;
    s32 oddOutput3;
    s32 rotation45;
    s32 z;
    s32 oddSumDifference;
    s32 oddDifferenceSum;
    s32 oddHighRotation;
    s32 oddLowRotation;
    s32 evenOutput3;

    if (zigzag == 0x11) {
        s32 sample;
        sample = clampS8(block[0] >> 11);
        memset(conv_row_ptr, (s8)sample, 0x40);
        return;
    }

    rowCoefficientCount = (zigzag >> 4) * 8;
    if ((zigzag & 0xF) > 2) {
        goto fullRowTransform;
    }

    workspaceCursor = workspace;
    processedCoefficients = 0;
    for (; processedCoefficients < rowCoefficientCount; processedCoefficients += 8) {
        s32 dcValue;
        s32 oddCoefficient;

        oddCoefficient = block[1];
        dcValue = block[0];
        rotation45 = oddCoefficient * 0xB5 >> 8;
        v = oddCoefficient * 0x62 >> 8;
        u = v + rotation45;
        z = (oddCoefficient * 0x14E >> 8) - v;
        m = oddCoefficient + z;
        n = rotation45 + z;
        workspaceCursor[0] = dcValue + m;
        workspaceCursor[7] = dcValue - m;
        workspaceCursor[1] = dcValue + n;
        workspaceCursor[6] = dcValue - n;
        workspaceCursor[2] = dcValue + u;
        workspaceCursor[5] = dcValue - u;
        workspaceCursor[3] = dcValue + v;
        workspaceCursor[4] = dcValue - v;
        workspaceCursor += 8;
        block += 8;
    }
    workspaceCursor = workspace + processedCoefficients;
    for (; processedCoefficients <= 0x38; processedCoefficients += 8) {
        memset(workspaceCursor, 0, 0x20);
        workspaceCursor += 8;
    }
    goto columnTransform;

fullRowTransform:
    workspaceCursor = workspace;
    processedCoefficients = 0;
    for (; processedCoefficients < rowCoefficientCount; processedCoefficients += 8) {
            u32 acBits;
            coefficient4 = block[4];
            coefficient6 = block[6];
            coefficient2 = block[2];
            coefficient1 = block[1];
            coefficient7 = block[7];
            coefficient5 = block[5];
            coefficient3 = block[3];

            acBits = (u32)coefficient4;
            acBits |= (u32)coefficient6;
            acBits |= (u32)coefficient2;
            acBits |= (u32)coefficient1;
            acBits |= (u32)coefficient7;
            acBits |= (u32)coefficient5;
            acBits |= (u32)coefficient3;
            if (acBits == 0) {
                s32 sample;
                sample = block[0];
                workspaceCursor[7] = sample;
                workspaceCursor[6] = sample;
                workspaceCursor[5] = sample;
                workspaceCursor[4] = sample;
                workspaceCursor[3] = sample;
                workspaceCursor[2] = sample;
                workspaceCursor[1] = sample;
                workspaceCursor[0] = sample;
            } else {
                s32 oddLowSum;
                s32 oddLowDifference;
                s32 oddHighSum;
                s32 oddHighDifference;
                s32 dcValue;
                
                rotation45 = coefficient2 - coefficient6;
                oddLowSum = coefficient5 + coefficient3;
                oddLowDifference = coefficient5 - coefficient3;
                oddHighSum = coefficient1 + coefficient7;
                oddHighDifference = coefficient1 - coefficient7;
                u = coefficient6 + coefficient2;
                rotation45 = rotation45 * 0xB5 >> 8;
                oddSumDifference = oddHighSum - oddLowSum;
                oddDifferenceSum = oddLowDifference + oddHighDifference;
                dcValue = block[0];
                evenBaseDifference = dcValue - coefficient4;
                oddSumRotation = oddSumDifference * 0xB5 >> 8;
                evenBaseSum = dcValue + coefficient4;
                u = rotation45 + u;
                v = evenBaseDifference + rotation45;
                z = oddDifferenceSum * 0x62 >> 8;
                evenOutput0 = evenBaseSum + u;
                evenOutput3 = evenBaseSum - u;
                oddHighRotation = oddHighDifference * 0x14E >> 8;
                evenOutput2 = evenBaseDifference - rotation45;
                m = oddHighRotation - z;
                oddLowSum += m;
                n = oddHighSum + oddLowSum;
                oddOutput1 = oddSumRotation + m;
                workspaceCursor[0] = evenOutput0 + n;
                oddLowRotation = oddLowDifference * 0x8B;
                workspaceCursor[7] = evenOutput0 - n;
                oddLowRotation >>= 8;
                workspaceCursor[1] = v + oddOutput1;
                oddOutput3 = z + oddLowRotation;
                oddOutput2 = oddOutput3 + oddSumRotation;
                workspaceCursor[6] = v - oddOutput1;
                workspaceCursor[2] = evenOutput2 + oddOutput2;
                workspaceCursor[5] = evenOutput2 - oddOutput2;
                workspaceCursor[3] = evenOutput3 + oddOutput3;
                workspaceCursor[4] = evenOutput3 - oddOutput3;
            }
            block += 8;
            workspaceCursor += 8;
    }

    workspaceCursor = workspace + processedCoefficients;
    for (; processedCoefficients <= 0x38; processedCoefficients += 8) {
        memset(workspaceCursor, 0, 0x20);
        workspaceCursor += 8;
    }

columnTransform:

    workspaceCursor = workspace + 7;
    for (columnsRemaining = 8, column = 7; columnsRemaining > 0; columnsRemaining--, column--) {
        u32 acBits;
        u8* output;
        coefficient4 = workspaceCursor[0x20];
        output = conv_row_ptr + column;
        coefficient6 = workspaceCursor[0x30];
        coefficient2 = workspaceCursor[0x10];
        coefficient1 = workspaceCursor[8];
        coefficient7 = workspaceCursor[0x38];
        coefficient5 = workspaceCursor[0x28];
        coefficient3 = workspaceCursor[0x18];

        acBits = (u32)coefficient4;
        acBits |= (u32)coefficient6;
        acBits |= (u32)coefficient2;
        acBits |= (u32)coefficient1;
        acBits |= (u32)coefficient7;
        acBits |= (u32)coefficient5;
        acBits |= (u32)coefficient3;
        if (acBits == 0) {
            s32 sample;
            sample = clampS8(*workspaceCursor >> 11);
            output[56] = (u8)sample;
            output[48] = (u8)sample;
            output[40] = (u8)sample;
            output[32] = (u8)sample;
            output[24] = (u8)sample;
            output[16] = (u8)sample;
            output[8] = (u8)sample;
            output[0] = (u8)sample;
        } else {
            s32 oddLowSum;
            s32 oddLowDifference;
            s32 oddHighSum;
            s32 oddHighDifference;
            s32 dcValue;
            
            rotation45 = coefficient2 - coefficient6;
            oddLowSum = coefficient5 + coefficient3;
            oddLowDifference = coefficient5 - coefficient3;
            oddHighSum = coefficient1 + coefficient7;
            oddHighDifference = coefficient1 - coefficient7;
            u = coefficient6 + coefficient2;
            rotation45 = rotation45 * 0xB5 >> 8;
            oddSumDifference = oddHighSum - oddLowSum;
            oddDifferenceSum = oddLowDifference + oddHighDifference;
            dcValue = *workspaceCursor;
            evenBaseDifference = dcValue - coefficient4;
            oddSumRotation = oddSumDifference * 0xB5 >> 8;
            evenBaseSum = dcValue + coefficient4;
            u = rotation45 + u;
            v = evenBaseDifference + rotation45;
            z = oddDifferenceSum * 0x62 >> 8;
            evenOutput0 = evenBaseSum + u;
            evenOutput3 = evenBaseSum - u;
            oddHighRotation = oddHighDifference * 0x14E >> 8;
            evenOutput2 = evenBaseDifference - rotation45;
            m = oddHighRotation - z;
            oddLowSum += m;
            n = oddHighSum + oddLowSum;
            oddOutput1 = oddSumRotation + m;
            oddLowRotation = oddLowDifference * 0x8B >> 8;
            oddOutput3 = z + oddLowRotation;
            oddOutput2 = oddOutput3 + oddSumRotation;
            output[0] = (u8)clampS8((evenOutput0 + n) >> 11);
            output[56] = (u8)clampS8((evenOutput0 - n) >> 11);
            output[8] = (u8)clampS8((v + oddOutput1) >> 11);
            output[48] = (u8)clampS8((v - oddOutput1) >> 11);
            output[16] = (u8)clampS8((evenOutput2 + oddOutput2) >> 11);
            output[40] = (u8)clampS8((evenOutput2 - oddOutput2) >> 11);
            output[24] = (u8)clampS8((evenOutput3 + oddOutput3) >> 11);
            output[32] = (u8)clampS8((evenOutput3 - oddOutput3) >> 11);
        }
        workspaceCursor--;
    }
}
