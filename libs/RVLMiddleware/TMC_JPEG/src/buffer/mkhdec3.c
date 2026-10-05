#include <tmc_jpeg_internal.h>

extern void* memcpy(void* dest, const void* src, unsigned long size);
extern void* memset(void* dest, int value, unsigned long size);

s32 TMCJPEGDEC_make_huffdec(const u8* dht, u8* tb, TMCHuffParam* hp) {
    typedef struct {
        u16 length;
        u16 symbol;
    } TMCHuffEntry;
    u32 huffCount[256];
    u32 huffVal[256];
    TMCHuffEntry* huffTable;
    TMCHuffEntry* valptr;
    u8* symbols;
    s32 count;
    {
        const u8* bits;
        u32* sizes;
        s32 index;
        s32 bitLength;
        s32 remaining;

        sizes = huffCount;
        bitLength = 1;
        remaining = 1;
        bits = dht + 1;
        huffTable = (TMCHuffEntry*)hp->huffTable;
        valptr = (TMCHuffEntry*)hp->valptr;
        symbols = (u8*)hp->maxCode;
        count = hp->count;
        index = 0;

        for (;;) {
            if (remaining > *bits) {
                bitLength++;
                remaining = 1;
                bits++;
                if (bitLength > 16) {
                    huffCount[index] = 0;
                    break;
                }
            } else {
                *sizes++ = bitLength;
                index++;
                if (index > count) {
                    return -0x40;
                }
                remaining++;
            }
        }
    }

    {
        u32* sizes = huffCount;
        s32 index;
        u16 code;
        u8 size;

        code = 0;
        index = 0;
        size = huffCount[0];
        while (*sizes != 0) {
            while (size == (u8)*sizes) {
                sizes++;
                huffVal[index++] = code;
                code++;
            }
            if (code >= (1 << size)) {
                return -0x40;
            }
            code <<= 1;
            size++;
        }

    }

    memset(valptr, 0, 0x44);
    {
        s32 index;
        for (index = 0; index < count; index++) {
            u32 length = huffCount[index];
            if (length <= 16) {
                valptr[length].symbol = index;
                valptr[length].length = huffVal[index];
            }
        }

    }
    {
        u32* codes;
        s32 step;
        s32 index;
        s32 bitLength;
        s32 entry;
        s32 left;
        s32 base;
        codes = huffVal;
        index = 0;
        for (bitLength = 1; bitLength <= 8; bitLength++) {
            s32 shift = 8 - bitLength;
            entry = 1;
            step = entry << shift;
            while (entry <= dht[bitLength]) {
                base = *codes << shift;
                for (left = step; left > 0; left--) {
                    huffTable[base].length = bitLength;
                    huffTable[base].symbol = tb[index];
                    base++;
                }
                entry++;
                codes++;
                index++;
            }
        }
    }
    memcpy(symbols, tb, count);
    return 0;
}



void TMCJPEGDEC_set_HuffmanTable(TMCHuffParam* tbl, s32 tblType, s32 tblID, TMCUnknownInfo* info) {
    TMCCJPEGDecWork* work = (TMCCJPEGDecWork*)info;
    void* hufftable;
    void* maxcode;
    void* valptr;

    if (tblType == 0) {
        switch (tblID) {
            case 0: {
                hufftable = &work->zigzagData[8];
                maxcode = work->maxCodeDC0;
                tbl->huffTable = hufftable;
                tbl->maxCode = maxcode;
                tbl->valptr = work->valPtrDC0;
                work->huffTblInitFlag[0] = 1;
                memset(hufftable, 0, 0x400);
                memset(work->maxCodeDC0, 0, 0x10);
                memset(work->valPtrDC0, 0, 0x44);
                break;
            }
            case 1: {
                hufftable = work->huffDecTblDC1;
                maxcode = work->maxCodeDC1;
                valptr = work->valPtrDC1;
                tbl->huffTable = hufftable;
                tbl->maxCode = maxcode;
                tbl->valptr = valptr;
                work->huffTblInitFlag[1] = 1;
                memset(hufftable, 0, 0x400);
                memset(work->maxCodeDC1, 0, 0x10);
                memset(work->valPtrDC1, 0, 0x44);
                break;
            }
        }
    } else {
        switch (tblID) {
            case 0: {
                hufftable = work->huffDecTblAC0;
                maxcode = work->maxCodeAC0;
                valptr = work->valPtrAC0;
                tbl->huffTable = hufftable;
                tbl->maxCode = maxcode;
                tbl->valptr = valptr;
                work->huffTblInitFlag[2] = 1;
                memset(hufftable, 0, 0x400);
                memset(work->maxCodeAC0, 0, 0x100);
                memset(work->valPtrAC0, 0, 0x44);
                break;
            }
            case 1: {
                hufftable = work->huffDecTblAC1;
                maxcode = work->maxCodeAC1;
                valptr = work->valPtrAC1;
                tbl->huffTable = hufftable;
                tbl->maxCode = maxcode;
                tbl->valptr = valptr;
                work->huffTblInitFlag[3] = 1;
                memset(hufftable, 0, 0x400);
                memset(work->maxCodeAC1, 0, 0x100);
                memset(work->valPtrAC1, 0, 0x44);
                break;
            }
        }
    }
}
