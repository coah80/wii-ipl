#include "system/odh.h"
#include <revolution/os/OSError.h>

extern "C" void _savegpr_24();
extern "C" void _restgpr_24();
extern "C" void cdj_c_initializeCompressOdh__9CArGBAOdhFP16SArCDJ_OdhMasterPUsUcPUcPUcUl();
extern "C" void cdj_c_compressLoop__9CArGBAOdhFP16SArCDJ_OdhMaster();
extern "C" void cdj_c_colorConv__9CArGBAOdhFP16SArCDJ_OdhMasterPUci();

enum {
    ODH_FORMAT_RGB565 = 0,
    ODH_FORMAT_RGBA8,
    ODH_FORMAT_Y8U8V8,
};

enum {
    ODH_ERROR_SUCCESS = 0,
    ODH_ERROR_80000001 = 0x80000001,
    ODH_ERROR_80000002 = 0x80000002,
    ODH_ERROR_80000003 = 0x80000003,
    ODH_ERROR_80000004 = 0x80000004,
    ODH_ERROR_80000005 = 0x80000005,
};

struct SArCDJ_OdhMaster {
    u16 field0;
    u16 field2;
    u8 field4;
    u8 padding[0xB];
    u32 bitBuffer;
    u32 bitCount;
    u32 outputPos;
    u32 remaining;
    u8 padding2[0x210];
    u8* data;
    u8 padding3[0x24C];
};

static const u32 gArDc_luminance_huffTable[] = {
    0x00018002, 0x00030000, 0xC003C004, 0x80050001, 0x00020003, 0x00040005,
    0x80010006, 0x80010007, 0x80010008, 0x80010009, 0x8001000A, 0x8001000B,
};

static const u32 gArDc_chrominance_huffTable[] = {
    0x0001C002, 0x80030000, 0x00010002, 0x80010003, 0x80010004, 0x80010005,
    0x80010006, 0x80010007, 0x80010008, 0x80010009, 0x8001000A, 0x8001000B,
};

struct HufftreeData {
    const u32* tables[4];
    char messages[0x1BB];
};

HufftreeData hufftreePtr = {
    {
        gArDc_luminance_huffTable,
        gArDc_luminance_huffTable,
        gArDc_chrominance_huffTable,
        gArDc_luminance_huffTable,
    },
    "decompressGbaOdh : source size error\n\0"
    "decompressGbaOdh : destination buffer over\n\0"
    "decompressGbaOdh : INITIALIZE ERROR %08x\n\0"
    "decompressGbaOdh : DECOMPRESSING ERROR %08x\n\0"
    "decompressGbaOdh : COLOR DECONVERSION ERROR %08x\n\0"
    "compressGbaOdh : INITIALIZE ERROR %08x\n\0"
    "compressGbaOdh : COLOR CONVERSION ERROR %08x\n\0"
    "compressGbaOdh : COMPRESS OVER AND RETRY %d q=%d, %08x\n\0"
    "compressGbaOdh : INITIALIZE ERROR2 %08x\n\0"
    "compressGbaOdh : COMPRESSING ERROR %08x\n",
};

class CArGBAOdh {
  public:
    s32 decompressGbaOdh(u8* src, int srcSize, u8* dest, int destSize, u8* work, int unk, int format);
    s32 compressGbaOdh(u8* src, u8* dest, int width, int height, int quality, u32 sizeLimit, u8* work, int format);
    s32 cdj_c_initializeCompressOdh(SArCDJ_OdhMaster* master, u16* dimensions, u8 quality, u8* work, u8* dest, u32 sizeLimit);
    s32 cdj_c_compressLoop(SArCDJ_OdhMaster* master);
    s32 cdj_c_flashBuffer(SArCDJ_OdhMaster* master);
    void cdj_c_makeHeader(SArCDJ_OdhMaster* master, u32 size);
    s32 cdj_c_colorConv(SArCDJ_OdhMaster* master, u8* src, int format);
    s32 cdj_d_initializeDecompressOdh(SArCDJ_OdhMaster* master, u8* work, u8* src);
    s32 cdj_d_decompressLoop(SArCDJ_OdhMaster* master, int srcSize, int workSize);
    s32 cdj_d_colorDeconv(SArCDJ_OdhMaster* master, u8* dest, int format);

  private:
    s32 ScaleLimit(s32 scale);
};

int ODHEncodeRGB565(u8* src, u8* dest, int width, int height, u32 sizeLimit, int quality, u8* work) {
    CArGBAOdh odh;
    return odh.compressGbaOdh(src, dest, width, height, quality, sizeLimit, work, ODH_FORMAT_RGB565);
}

int ODHEncodeRGBA8(u8* src, u8* dest, int width, int height, u32 sizeLimit, int quality, u8* work) {
    CArGBAOdh odh;
    return odh.compressGbaOdh(src, dest, width, height, quality, sizeLimit, work, ODH_FORMAT_RGBA8);
}

int ODHEncodeY8U8V8(u8* src, u8* dest, int width, int height, u32 sizeLimit, int quality, u8* work) {
    CArGBAOdh odh;
    return odh.compressGbaOdh(src, dest, width, height, quality, sizeLimit, work, ODH_FORMAT_Y8U8V8);
}

int ODHDecodeRGB565(u8* src, int srcSize, u8* dest, int destSize, u8* work, int unk) {
    CArGBAOdh odh;
    int result = odh.decompressGbaOdh(src, srcSize, dest, destSize, work, unk, ODH_FORMAT_RGB565);
    return result;
}

int ODHDecodeRGBA8(u8* src, int srcSize, u8* dest, int destSize, u8* work, int unk) {
    CArGBAOdh odh;
    int result = odh.decompressGbaOdh(src, srcSize, dest, destSize, work, unk, ODH_FORMAT_RGBA8);
    return result;
}

int ODHDecodeY8U8V8(u8* src, int srcSize, u8* dest, int destSize, u8* work, int unk) {
    CArGBAOdh odh;
    int result = odh.decompressGbaOdh(src, srcSize, dest, destSize, work, unk, ODH_FORMAT_Y8U8V8);
    return result;
}

int ODHGetWidth(u8* data) {
    return (((u32*)data)[1] & 0x7FF) + 7 & 0x7F8;
}

int ODHGetHeight(u8* data) {
    return (((u32*)data)[1] >> 11 & 0x7FF) + 7 & 0x7F8;
}

s32 CArGBAOdh::decompressGbaOdh(u8* src, int srcSize, u8* dest, int destSize, u8* work, int unk, int format) {
    SArCDJ_OdhMaster master;
    const char* messages = (const char*)&hufftreePtr;
    int width;
    int height;
    int outputSize;

    if (srcSize <= 0x10) {
        OSReport(messages + 0x10);
        return 0;
    }

    width = (((u32*)src)[1] & 0x7FF) + 7 & 0x7F8;
    height = (((u32*)src)[1] >> 11 & 0x7FF) + 7 & 0x7F8;

    if (format == ODH_FORMAT_RGB565) {
        outputSize = width * height * 2;
    } else if (format == ODH_FORMAT_RGBA8) {
        outputSize = width * height * 4;
    } else {
        outputSize = width * height * 3;
    }

    if (destSize == 0) {
        destSize = outputSize;
    }
    if (unk == 0) {
        unk = width * height * 3;
    }
    if (outputSize > destSize) {
        OSReport(messages + 0x36);
        return 0;
    }

    s32 result = cdj_d_initializeDecompressOdh(&master, work, src);
    if (result != 0) {
        OSReport(messages + 0x62, result);
        return 0;
    }

    result = cdj_d_decompressLoop(&master, srcSize, unk);
    if (result != 0) {
        OSReport(messages + 0x8C, result);
        return 0;
    }

    result = cdj_d_colorDeconv(&master, dest, format);
    if (result != 0) {
        OSReport(messages + 0xB9, result);
        return 0;
    }

    return height << 16 | width;
}

asm s32 CArGBAOdh::compressGbaOdh(u8* src, u8* dest, int width, int height, int quality, u32 sizeLimit, u8* work, int format) {
    nofralloc
    stwu r1, -0x4b0(r1)
    mflr r0
    stw r0, 0x4b4(r1)
    addi r11, r1, 0x4b0
    bl _savegpr_24
    cmpwi r9, 0
    lis r31, hufftreePtr@ha
    lwz r29, 0x4b8(r1)
    mr r24, r3
    mr r30, r4
    mr r25, r5
    mr r26, r8
    mr r27, r9
    mr r28, r10
    addi r31, r31, hufftreePtr@l
    bne compressGbaOdh_L1
    mullw r0, r6, r7
    slwi r27, r0, 1
compressGbaOdh_L1:
    sth r6, 8(r1)
    clrlwi r6, r8, 0x18
    mr r3, r24
    mr r8, r25
    sth r7, 0xa(r1)
    mr r7, r28
    mr r9, r27
    addi r4, r1, 0xc
    addi r5, r1, 8
    bl cdj_c_initializeCompressOdh__9CArGBAOdhFP16SArCDJ_OdhMasterPUsUcPUcPUcUl
    cmpwi r3, 0
    beq compressGbaOdh_L2
    mr r4, r3
    addi r3, r31, 0xeb
    crclr 4*cr1+eq
    bl OSReport
    li r3, 0
    b compressGbaOdh_L8
compressGbaOdh_L2:
    mr r3, r24
    mr r5, r30
    mr r6, r29
    addi r4, r1, 0xc
    bl cdj_c_colorConv__9CArGBAOdhFP16SArCDJ_OdhMasterPUci
    cmpwi r3, 0
    beq compressGbaOdh_L3
    mr r4, r3
    addi r3, r31, 0x113
    crclr 4*cr1+eq
    bl OSReport
    li r3, 0
    b compressGbaOdh_L8
compressGbaOdh_L3:
    mr r3, r24
    addi r4, r1, 0xc
    bl cdj_c_compressLoop__9CArGBAOdhFP16SArCDJ_OdhMaster
    mr r30, r3
    li r29, 1
    b compressGbaOdh_L6
compressGbaOdh_L4:
    lbz r5, 0x10(r1)
    mr r4, r29
    mr r6, r30
    addi r3, r31, 0x141
    crclr 4*cr1+eq
    addi r29, r29, 1
    bl OSReport
    addic. r26, r26, -5
    ble compressGbaOdh_L7
    mr r3, r24
    mr r7, r28
    mr r8, r25
    mr r9, r27
    addi r4, r1, 0xc
    addi r5, r1, 8
    clrlwi r6, r26, 0x18
    bl cdj_c_initializeCompressOdh__9CArGBAOdhFP16SArCDJ_OdhMasterPUsUcPUcPUcUl
    cmpwi r3, 0
    beq compressGbaOdh_L5
    mr r4, r3
    addi r3, r31, 0x179
    crclr 4*cr1+eq
    bl OSReport
    li r3, 0
    b compressGbaOdh_L8
compressGbaOdh_L5:
    mr r3, r24
    addi r4, r1, 0xc
    bl cdj_c_compressLoop__9CArGBAOdhFP16SArCDJ_OdhMaster
    mr r30, r3
    b compressGbaOdh_L6
compressGbaOdh_L7:
    mr r4, r30
    addi r3, r31, 0x1a2
    crclr 4*cr1+eq
    bl OSReport
    li r3, 0
    b compressGbaOdh_L8
compressGbaOdh_L6:
    addis r0, r30, -0x8000
    cmplwi r0, 4
    beq compressGbaOdh_L4
    mr r3, r30
compressGbaOdh_L8:
    addi r11, r1, 0x4b0
    bl _restgpr_24
    lwz r0, 0x4b4(r1)
    mtlr r0
    addi r1, r1, 0x4b0
    blr
}

s32 CArGBAOdh::cdj_c_flashBuffer(SArCDJ_OdhMaster* master) {
    master->bitBuffer |= 0x7F << (master->bitCount -= 7);

    while (master->bitCount <= 0x18) {
        if (master->remaining == 0) {
            return ODH_ERROR_80000004;
        }

        master->data[master->outputPos - master->remaining] = master->bitBuffer >> 24;
        master->remaining--;
        master->bitCount += 8;
        master->bitBuffer <<= 8;
    }

    while ((master->outputPos - master->remaining) & 3) {
        master->data[master->outputPos - master->remaining] = 0xFF;
        master->remaining--;
    }

    return ODH_ERROR_SUCCESS;
}

void CArGBAOdh::cdj_c_makeHeader(SArCDJ_OdhMaster* master, u32 size) {
    master->data[0] = 'A';
    master->data[1] = 'J';
    master->data[2] = 'P';
    master->data[3] = 'G';
    *(u32*)&master->data[4] = master->field0 | (u32)master->field2 << 11 | (u32)master->field4 << 24;
    *(u32*)&master->data[8] = size;
    *(u32*)&master->data[12] = 0;
}

s32 CArGBAOdh::ScaleLimit(s32 scale) {
    s32 newScale = scale;

    if (newScale < 0) {
        newScale = 0;
    } else if (scale > 255) {
        newScale = 255;
    }

    return newScale;
}
