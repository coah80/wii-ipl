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
    return value < 0 ? 0 : 255;
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

static s32 clampLumaDc(s32 coefficient) {
    return clampU8((coefficient >> 11) + 0x80);
}

void TMCJPEGDEC_IdctBlock_Lumi(s32* block, u8* conv_row_ptr, u16 pitch, s32 zigzag) {
    s32 pitch2;
    s32* dst;
    s32 rowOddOutput1;
    int columnAcBits;
    s32 column;
    s32 rowEvenOutput0;
    s32 columnC6;
    s32 columnC4;
    s32 columnOddSumRotation;
    s32 rowDc;
    s32 rowEvenOutput1;
    s32 columnC1;
    s32 columnEvenBaseDifference;
    s32 columnEvenOutput0;
    s32 columnC2;
    s32 columnScaledEvenRotation;
    s32 columnEvenOutput1;
    s32 columnC5;
    s32 rowC4;
    s32 rowOddSumRotation;
    s32 columnEvenOutput3;
    s32 columnOddLowSum;
    s32 columnOddLowDifference;
    s32 columnOddHighSum;
    s32 columnC7;
    s32 columnC3;
    s32 columnEvenBaseSum;
    s32 rowEvenBaseDifference;
    s32 rowEvenOutput2;
    s32 rowOddOutput0;
    s32 rowC1;
    s32 columnOddHighDifference;
    s32 columnDc;
    s32 columnOddDifferenceRotation;
    s32 columnOddOutput1;
    s32 rowScaledEvenRotation;
    s32 columnEvenOutput2;
    s32 columnOddMix;
    int rowAcBits;
    s32 columnEvenRotationSum;
    s32 rowEvenBaseSum;
    s32 rowC2;
    s32 rowEvenRotationSum;
    s32 rowEvenOutput3;
    s32 rowOddLowDifference;
    s32 columnOddOutput0;
    u8* columnOutput;
    s32 pitch4;
    s32* src;
    s32 rowC3;
    s32 rowOddHighDifference;
    s32 rowOddHighSum;
    s32 rowOddOutput3;
    s32 pitch7;
    s32 pitch6;
    s32 rowC6;
    s32 columnOddOutput2;
    u8 columnSample;
    s32 processed;
    s32 rowOddLowSum;
    s32 rowOddDifferenceRotation;
    s32 columnOddOutput3;
    s32 rowC5;
    s32 rowOddMix;
    s32 rowSampleDc;
    s32 rowOddOutput2;
    s32 rowC7;
    s32 rowCount;
    s32 pitch5;
    s32 pitch3;
    s32 workspace[64];
    s32 rowEvenSum;
    s32 rowOddLowRotation;
    s32 rowEvenRotation;
    s32 rowOddDifferenceSum;
    s32 rowOddHighRotation;
    s32 rowOddSumDifference;
    s32 columnOddDifferenceSum;
    s32 columnOddHighRotation;
    s32 columnOddLowRotation;
    s32 columnEvenRotation;
    s32 columnOddSumDifference;
    int columnEvenSum;

    rowCount = (zigzag >> 4) * 8;
    dst = workspace;
    for (processed = 0; processed < rowCount; processed += 8) {
        rowC4 = block[4];
        rowC6 = block[6];
        rowC2 = block[2];
        rowC1 = block[1];
        rowC7 = block[7];
        rowC5 = block[5];
        rowC3 = block[3];
        rowAcBits = rowC4 | rowC6;
        rowAcBits = rowC2 | rowAcBits;
        rowAcBits = rowC1 | rowAcBits;
        rowAcBits = rowC7 | rowAcBits;
        rowAcBits = rowC5 | rowAcBits;
        rowAcBits = rowC3 | rowAcBits;
        if (rowAcBits == 0) {
            rowSampleDc = block[0];
            dst[7] = rowSampleDc;
            dst[6] = rowSampleDc;
            dst[5] = rowSampleDc;
            dst[4] = rowSampleDc;
            dst[3] = rowSampleDc;
            dst[2] = rowSampleDc;
            dst[1] = rowSampleDc;
            dst[0] = rowSampleDc;
        } else {
            rowDc = block[0];
            rowEvenRotation = rowC2 - rowC6;
            rowEvenSum = rowC2 + rowC6;
            rowEvenBaseSum = rowDc + rowC4;
            rowEvenBaseDifference = rowDc - rowC4;
            rowScaledEvenRotation = rowEvenRotation * 0xB5 >> 8;
            rowEvenRotationSum = rowScaledEvenRotation + rowEvenSum;
            rowEvenOutput0 = rowEvenBaseSum + rowEvenRotationSum;
            rowEvenOutput1 = rowEvenBaseDifference + rowScaledEvenRotation;
            rowEvenOutput2 = rowEvenBaseDifference - rowScaledEvenRotation;
            rowEvenOutput3 = rowEvenBaseSum - rowEvenRotationSum;
            rowOddHighSum = rowC1 + rowC7;
            rowOddHighDifference = rowC1 - rowC7;
            rowOddLowSum = rowC5 + rowC3;
            rowOddLowDifference = rowC5 - rowC3;
            rowOddSumDifference = rowOddHighSum - rowOddLowSum;
            rowOddDifferenceSum = rowOddLowDifference + rowOddHighDifference;
            rowOddSumRotation = rowOddSumDifference * 0xB5 >> 8;
            rowOddDifferenceRotation = rowOddDifferenceSum * 0x62 >> 8;
            rowOddHighRotation = rowOddHighDifference * 0x14E >> 8;
            rowOddLowRotation = rowOddLowDifference * 0x8B >> 8;
            rowOddMix = rowOddHighRotation - rowOddDifferenceRotation;
            rowOddLowSum += rowOddMix;
            rowOddOutput0 = rowOddHighSum + rowOddLowSum;
            rowOddOutput1 = rowOddSumRotation + rowOddMix;
            rowOddOutput3 = rowOddDifferenceRotation + rowOddLowRotation;
            rowOddOutput2 = rowOddOutput3 + rowOddSumRotation;
            dst[0] = rowEvenOutput0 + rowOddOutput0;
            dst[7] = rowEvenOutput0 - rowOddOutput0;
            dst[1] = rowEvenOutput1 + rowOddOutput1;
            dst[6] = rowEvenOutput1 - rowOddOutput1;
            dst[2] = rowEvenOutput2 + rowOddOutput2;
            dst[5] = rowEvenOutput2 - rowOddOutput2;
            dst[3] = rowEvenOutput3 + rowOddOutput3;
            dst[4] = rowEvenOutput3 - rowOddOutput3;
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
        columnC4 = src[32];
        columnC6 = src[48];
        columnC2 = src[16];
        columnC1 = src[8];
        columnC7 = src[56];
        columnC5 = src[40];
        columnC3 = src[24];
        columnAcBits = columnC4 | columnC6;
        columnAcBits = columnC2 | columnAcBits;
        columnAcBits = columnC1 | columnAcBits;
        columnAcBits = columnC7 | columnAcBits;
        columnAcBits = columnC5 | columnAcBits;
        columnAcBits = columnC3 | columnAcBits;
        columnOutput = conv_row_ptr + column;
        if (columnAcBits == 0) {
            columnSample = clampLumaDc(*src);
            columnOutput[pitch7] = columnSample;
            columnOutput[pitch6] = columnSample;
            columnOutput[pitch5] = columnSample;
            columnOutput[pitch4] = columnSample;
            columnOutput[pitch3] = columnSample;
            columnOutput[pitch2] = columnSample;
            columnOutput[pitch] = columnSample;
            columnOutput[0] = columnSample;
        } else {
            columnEvenSum = columnC6 + columnC2;
            columnEvenRotation = columnC2 - columnC6;
            columnOddLowSum = columnC5 + columnC3;
            columnOddHighDifference = columnC1 - columnC7;
            columnOddLowDifference = columnC5 - columnC3;
            columnOddHighSum = columnC1 + columnC7;
            columnScaledEvenRotation = columnEvenRotation * 0xB5 >> 8;
            columnDc = *src + 0x40000;
            columnOddDifferenceSum = columnOddLowDifference + columnOddHighDifference;
            columnOddSumDifference = columnOddHighSum - columnOddLowSum;
            columnOddSumRotation = columnOddSumDifference * 0xB5 >> 8;
            columnEvenBaseSum = columnDc + columnC4;
            columnOddDifferenceRotation = columnOddDifferenceSum * 0x62 >> 8;
            columnOddHighRotation = columnOddHighDifference * 0x14E >> 8;
            columnEvenRotationSum = columnScaledEvenRotation + columnEvenSum;
            columnOddMix = columnOddHighRotation - columnOddDifferenceRotation;
            columnOddLowSum += columnOddMix;
            columnEvenOutput0 = columnEvenBaseSum + columnEvenRotationSum;
            columnEvenBaseDifference = columnDc - columnC4;
            columnEvenOutput3 = columnEvenBaseSum - columnEvenRotationSum;
            columnEvenOutput1 = columnEvenBaseDifference + columnScaledEvenRotation;
            columnOddOutput0 = columnOddHighSum + columnOddLowSum;
            columnOddLowRotation = columnOddLowDifference * 0x8B >> 8;
            columnOddOutput3 = columnOddDifferenceRotation + columnOddLowRotation;
            columnEvenOutput2 = columnEvenBaseDifference - columnScaledEvenRotation;
            columnOddOutput2 = columnOddOutput3 + columnOddSumRotation;
            columnOddOutput1 = columnOddSumRotation + columnOddMix;
            columnOutput[0] = scalingClampU8(columnEvenOutput0 + columnOddOutput0);
            columnOutput[pitch7] = scalingClampU8(columnEvenOutput0 - columnOddOutput0);
            columnOutput[pitch] = scalingClampU8(columnEvenOutput1 + columnOddOutput1);
            columnOutput[pitch6] = scalingClampU8(columnEvenOutput1 - columnOddOutput1);
            columnOutput[pitch2] = scalingClampU8(columnEvenOutput2 + columnOddOutput2);
            columnOutput[pitch5] = scalingClampU8(columnEvenOutput2 - columnOddOutput2);
            columnOutput[pitch3] = scalingClampU8(columnEvenOutput3 + columnOddOutput3);
            columnOutput[pitch4] = scalingClampU8(columnEvenOutput3 - columnOddOutput3);
        }
        src--;
    }
}


static s32 clampChromaDc(s32 value) {
    return clampS8(value >> 11);
}

void TMCJPEGDEC_IdctBlock_Col(s32* block, u8* conv_row_ptr, u16 pitch, s32 zigzag) {
    s32 rowCount;
    s32 columnOddSumRotation;
    s32 rowOddOutput1;
    s32 columnC1;
    int rowAcBits;
    s32 columnEvenBaseDifference;
    s32 columnC7;
    s32 rowDc;
    s32 rowOddSumRotation;
    s32 rowEvenBaseSum;
    s32 columnOddDifferenceRotation;
    s32 columnEvenRotationSum;
    s32* dst;
    s32 columnOddOutput2;
    s32 sparseDc;
    s32 rowOddDifferenceRotation;
    s32 columnOddOutput1;
    s32 rowOddOutput2;
    s32 columnDc;
    s32 columnEvenBaseSum;
    s32* src;
    s32 rowOuter;
    s32 processed;
    s32 columnC6;
    s32 rowOdd;
    s32 column;
    s32 columnOddOutput3;
    s32 rowSampleDc;
    s32 rowOddOutput0;
    s32 rowC3;
    s32 columnScaledEvenRotation;
    s32 rowRotation;
    s32 rowEvenOutput2;
    s32 rowC2;
    s32 rowEvenBaseDifference;
    s32 columnC5;
    s32 rowEvenRotationSum;
    s32 columnOddOutput0;
    s32 rowC1;
    int columnAcBits;
    s32 columnC4;
    s32 columnOddMix;
    s32 columnOddLowSum;
    s32 rowEvenOutput1;
    s32 rowLowRotation;
    s32 columnC3;
    s32 rowOddHighDifference;
    s32 rowC5;
    s32 columnEvenOutput0;
    s32 rowEvenOutput0;
    s32 rowOddMix;
    s32 rowEvenOutput3;
    s32 rowC4;
    s32 rowInner;
    s32 rowC6;
    s32 columnEvenOutput1;
    s32 rowScaledEvenRotation;
    s32 rowOddLowDifference;
    s32 rowC7;
    s32 rowOddOutput3;
    s32 columnEvenOutput3;
    s32 rowMid;
    s32 columnOddHighDifference;
    s32 columnEvenOutput2;
    s32 columnC2;
    s32 columnOddLowDifference;
    s32 columnOddHighSum;
    s32 rowOddHighSum;
    s32 rowOddLowSum;
    u8* columnOutput;
    s32 columnOddLowRotation;
    s32 rowEvenSum;
    s32 flatDc;
    s32 columnEvenRotation;
    s32 rowOddDifferenceSum;
    s32 rowOddSumDifference;
    s32 columnSample;
    s32 columnOddDifferenceSum;
    int columnEvenSum;
    s32 rowOddHighRotation;
    s32 workspace[64];
    s32 rowOddLowRotation;
    s32 rowSample;
    s32 rowEvenRotation;
    s32 columnOddHighRotation;
    s32 columnOddSumDifference;
    s32 rowMix;

    if (zigzag == 0x11) {
        flatDc = block[0];
        rowSample = clampS8(flatDc >> 11);
        memset(conv_row_ptr, (s8)rowSample, 64);
        return;
    }

    rowCount = (zigzag >> 4) * 8;
    if ((zigzag & 0xF) <= 2) {
        dst = workspace;
        for (processed = 0; processed < rowCount; processed += 8) {
            rowOdd = block[1];
            rowRotation = rowOdd * 0xB5 >> 8;
            rowLowRotation = rowOdd * 0x62 >> 8;
            sparseDc = block[0];
            rowMix = (rowOdd * 0x14E >> 8) - rowLowRotation;
            rowOuter = rowOdd + rowMix;
            dst[0] = sparseDc + rowOuter;
            rowInner = rowRotation + rowMix;
            dst[7] = sparseDc - rowOuter;
            dst[1] = sparseDc + rowInner;
            rowMid = rowLowRotation + rowRotation;
            dst[6] = sparseDc - rowInner;
            dst[2] = sparseDc + rowMid;
            dst[5] = sparseDc - rowMid;
            dst[3] = sparseDc + rowLowRotation;
            dst[4] = sparseDc - rowLowRotation;
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
            rowC4 = block[4];
            rowC6 = block[6];
            rowC2 = block[2];
            rowC1 = block[1];
            rowC7 = block[7];
            rowC5 = block[5];
            rowC3 = block[3];
            rowAcBits = rowC4 | rowC6;
            rowAcBits = rowC2 | rowAcBits;
            rowAcBits = rowC1 | rowAcBits;
            rowAcBits = rowC7 | rowAcBits;
            rowAcBits = rowC5 | rowAcBits;
            rowAcBits = rowC3 | rowAcBits;
            if (rowAcBits == 0) {
                rowSampleDc = block[0];
                dst[7] = rowSampleDc;
                dst[6] = rowSampleDc;
                dst[5] = rowSampleDc;
                dst[4] = rowSampleDc;
                dst[3] = rowSampleDc;
                dst[2] = rowSampleDc;
                dst[1] = rowSampleDc;
                dst[0] = rowSampleDc;
            } else {
                rowDc = block[0];
                rowEvenRotation = rowC2 - rowC6;
                rowEvenSum = rowC2 + rowC6;
                rowEvenBaseSum = rowDc + rowC4;
                rowEvenBaseDifference = rowDc - rowC4;
                rowScaledEvenRotation = rowEvenRotation * 0xB5 >> 8;
                rowEvenRotationSum = rowScaledEvenRotation + rowEvenSum;
                rowEvenOutput0 = rowEvenBaseSum + rowEvenRotationSum;
                rowEvenOutput1 = rowEvenBaseDifference + rowScaledEvenRotation;
                rowEvenOutput2 = rowEvenBaseDifference - rowScaledEvenRotation;
                rowEvenOutput3 = rowEvenBaseSum - rowEvenRotationSum;
                rowOddHighSum = rowC1 + rowC7;
                rowOddHighDifference = rowC1 - rowC7;
                rowOddLowSum = rowC5 + rowC3;
                rowOddLowDifference = rowC5 - rowC3;
                rowOddSumDifference = rowOddHighSum - rowOddLowSum;
                rowOddDifferenceSum = rowOddLowDifference + rowOddHighDifference;
                rowOddSumRotation = rowOddSumDifference * 0xB5 >> 8;
                rowOddDifferenceRotation = rowOddDifferenceSum * 0x62 >> 8;
                rowOddHighRotation = rowOddHighDifference * 0x14E >> 8;
                rowOddLowRotation = rowOddLowDifference * 0x8B >> 8;
                rowOddMix = rowOddHighRotation - rowOddDifferenceRotation;
                rowOddLowSum += rowOddMix;
                rowOddOutput0 = rowOddHighSum + rowOddLowSum;
                rowOddOutput1 = rowOddSumRotation + rowOddMix;
                rowOddOutput3 = rowOddDifferenceRotation + rowOddLowRotation;
                rowOddOutput2 = rowOddOutput3 + rowOddSumRotation;
                dst[0] = rowEvenOutput0 + rowOddOutput0;
                dst[7] = rowEvenOutput0 - rowOddOutput0;
                dst[1] = rowEvenOutput1 + rowOddOutput1;
                dst[6] = rowEvenOutput1 - rowOddOutput1;
                dst[2] = rowEvenOutput2 + rowOddOutput2;
                dst[5] = rowEvenOutput2 - rowOddOutput2;
                dst[3] = rowEvenOutput3 + rowOddOutput3;
                dst[4] = rowEvenOutput3 - rowOddOutput3;
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
        columnC4 = src[32];
        columnOutput = conv_row_ptr + column;
        columnC6 = src[48];
        columnC2 = src[16];
        columnC1 = src[8];
        columnC7 = src[56];
        columnC5 = src[40];
        columnC3 = src[24];
        columnAcBits = columnC4 | columnC6;
        columnAcBits = columnC2 | columnAcBits;
        columnAcBits = columnC1 | columnAcBits;
        columnAcBits = columnC7 | columnAcBits;
        columnAcBits = columnC5 | columnAcBits;
        columnAcBits = columnC3 | columnAcBits;
        if (columnAcBits == 0) {
            columnSample = clampChromaDc(*src);
            columnOutput[56] = (u8)columnSample;
            columnOutput[48] = (u8)columnSample;
            columnOutput[40] = (u8)columnSample;
            columnOutput[32] = (u8)columnSample;
            columnOutput[24] = (u8)columnSample;
            columnOutput[16] = (u8)columnSample;
            columnOutput[8] = (u8)columnSample;
            columnOutput[0] = (u8)columnSample;
        } else {
            columnOddHighSum = columnC1 + columnC7;
            columnEvenRotation = columnC2 - columnC6;
            columnOddLowSum = columnC5 + columnC3;
            columnOddSumDifference = columnOddHighSum - columnOddLowSum;
            columnEvenSum = columnC6 + columnC2;
            columnOddLowDifference = columnC5 - columnC3;
            columnScaledEvenRotation = columnEvenRotation * 0xB5 >> 8;
            columnOddHighDifference = columnC1 - columnC7;
            columnDc = *src;
            columnEvenRotationSum = columnScaledEvenRotation + columnEvenSum;
            columnOddSumRotation = columnOddSumDifference * 0xB5 >> 8;
            columnOddDifferenceSum = columnOddLowDifference + columnOddHighDifference;
            columnOddDifferenceRotation = columnOddDifferenceSum * 0x62 >> 8;
            columnEvenBaseDifference = columnDc - columnC4;
            columnEvenBaseSum = columnDc + columnC4;
            columnOddHighRotation = columnOddHighDifference * 0x14E >> 8;
            columnOddMix = columnOddHighRotation - columnOddDifferenceRotation;
            columnEvenOutput3 = columnEvenBaseSum - columnEvenRotationSum;
            columnEvenOutput1 = columnEvenBaseDifference + columnScaledEvenRotation;
            columnEvenOutput2 = columnEvenBaseDifference - columnScaledEvenRotation;
            columnEvenOutput0 = columnEvenBaseSum + columnEvenRotationSum;
            columnOddLowRotation = columnOddLowDifference * 0x8B >> 8;
            columnOddOutput3 = columnOddDifferenceRotation + columnOddLowRotation;
            columnOddLowSum += columnOddMix;
            columnOddOutput1 = columnOddSumRotation + columnOddMix;
            columnOddOutput0 = columnOddHighSum + columnOddLowSum;
            columnOddOutput2 = columnOddOutput3 + columnOddSumRotation;
            columnOutput[0] = (u8)clampS8((columnEvenOutput0 + columnOddOutput0) >> 11);
            columnOutput[56] = (u8)clampS8((columnEvenOutput0 - columnOddOutput0) >> 11);
            columnOutput[8] = (u8)clampS8((columnEvenOutput1 + columnOddOutput1) >> 11);
            columnOutput[48] = (u8)clampS8((columnEvenOutput1 - columnOddOutput1) >> 11);
            columnOutput[16] = (u8)clampS8((columnEvenOutput2 + columnOddOutput2) >> 11);
            columnOutput[40] = (u8)clampS8((columnEvenOutput2 - columnOddOutput2) >> 11);
            columnOutput[24] = (u8)clampS8((columnEvenOutput3 + columnOddOutput3) >> 11);
            columnOutput[32] = (u8)clampS8((columnEvenOutput3 - columnOddOutput3) >> 11);
        }
        src--;
    }
}

