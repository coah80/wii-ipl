#include "system/odh.h"

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
};

class CArGBAOdh {
  public:
    s32 decompressGbaOdh(u8* src, int srcSize, u8* dest, int destSize, u8* work, int unk, int format);
    s32 compressGbaOdh(u8* src, u8* dest, int width, int height, int quality, u32 sizeLimit, u8* work, int format);
    s32 cdj_c_flashBuffer(SArCDJ_OdhMaster* master);
    void cdj_c_makeHeader(SArCDJ_OdhMaster* master, u32 size);

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
