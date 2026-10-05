#ifndef REVOLUTION_CX_STREAMING_UNCOMPRESS_H
#define REVOLUTION_CX_STREAMING_UNCOMPRESS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <revolution/types.h>

typedef s32 CXStreamingResult;
#define CX_STREAMING_ERR_OK 0
#define CX_STREAMING_ERR_BAD_FILE_TYPE -1
#define CX_STREAMING_ERR_BUFFER_TOO_SMALL -2
#define CX_STREAMING_ERR_BUFFER_TOO_LARGE -3
#define CX_STREAMING_ERR_BAD_FILE_SIZE -4
#define CX_STREAMING_ERR_BAD_FILE_TABLE -5

typedef struct CXUncompContextRL {
    u8* outData;   // 0x00
    int outDataLen;  // 0x04
    u32 size;      // 0x08
    u16 length;    // 0x0C
    u8 flags;      // 0x0E
    u8 hdrLen;     // 0x0F
} CXUncompContextRL;

typedef struct CXUncompContextLZ {
    u8* outData;   // 0x00
    int outDataLen;  // 0x04
    u32 size;      // 0x08
    int length;           // 0x0C
    u8 lengthBytesLeft;   // 0x10
    u8 flags;             // 0x11
    u8 flagsLeft;         // 0x12
    u8 hdrLen;            // 0x13
    u8 lzType;            // 0x14
    u8 padding[3];
} CXUncompContextLZ;

typedef union CXHuffmanDecodeTableEntry {
    volatile u8 raw;
    struct {
        u8 leafR : 1;      // 10000000
        u8 leafL : 1;      // 01000000
        u8 idxOffset : 6;  // 00111111
    };
} CXHuffmanDecodeTableEntry;

typedef struct CXUncompContextHuffman {
    u32* outData;                                      // 0x00
    int outDataLen;                                    // 0x04
    u32 size;                                          // 0x08
    CXHuffmanDecodeTableEntry* decodeTable;            // 0x0C
    u32 bits;                                          // 0x10
    u32 wordBuffer;                                    // 0x14
    s16 decodeTableSize;                               // 0x18
    u8 bitsLeft;                                       // 0x1A
    u8 wordBits;                                       // 0x1B
    u8 depth;                                          // 0x1C
    u8 hdrLen;                                         // 0x1D
    u8 padding[2];                                     // 0x1E
    CXHuffmanDecodeTableEntry decodeTableData[0x200];  // 0x20
} CXUncompContextHuffman;

void CXInitUncompContextRL(CXUncompContextRL* context, u8* data);
void CXInitUncompContextLZ(CXUncompContextLZ* context, u8* data);
void CXInitUncompContextHuffman(CXUncompContextHuffman* context, u8* data);

CXStreamingResult CXReadUncompRL(CXUncompContextRL* context, const void* src, u32 size);
CXStreamingResult CXReadUncompLZ(CXUncompContextLZ* context, const void* src, u32 size);
CXStreamingResult CXReadUncompHuffman(CXUncompContextHuffman* context, const void* src, u32 size);

#ifdef __cplusplus
}
#endif

#endif  // REVOLUTION_CX_STREAMING_UNCOMPRESS_H
