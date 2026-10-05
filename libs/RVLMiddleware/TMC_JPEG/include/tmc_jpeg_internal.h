#ifndef TMC_JPEG_INTERNAL_H
#define TMC_JPEG_INTERNAL_H

#include <revolution/types.h>

#include <tmc_jpeg.h>

enum TMCCJPEGOutputFormat {
    TMCC_JPEG_OUTPUT_RGB565 = 0,
    TMCC_JPEG_OUTPUT_RGBA8 = 1,
    TMCC_JPEG_OUTPUT_Y8U8V8 = 2
};

enum TMCJpegMarker {
    TMC_JPEG_MARKER_SOF0 = 0xFFC0,
    TMC_JPEG_MARKER_SOF2 = 0xFFC2,
    TMC_JPEG_MARKER_DHT = 0xFFC4,
    TMC_JPEG_MARKER_RST0 = 0xFFD0,
    TMC_JPEG_MARKER_RST7 = 0xFFD7,
    TMC_JPEG_MARKER_SOI = 0xFFD8,
    TMC_JPEG_MARKER_EOI = 0xFFD9,
    TMC_JPEG_MARKER_SOS = 0xFFDA,
    TMC_JPEG_MARKER_DQT = 0xFFDB,
    TMC_JPEG_MARKER_DNL = 0xFFDC,
    TMC_JPEG_MARKER_DRI = 0xFFDD,
    TMC_JPEG_MARKER_APP0 = 0xFFE0,
    TMC_JPEG_MARKER_APP1 = 0xFFE1,
    TMC_JPEG_MARKER_APP15 = 0xFFEF,
    TMC_JPEG_MARKER_COM = 0xFFFE,
    TMC_JPEG_MARKER_PREFIX = 0xFF00,
    TMC_JPEG_MARKER_FILL = 0xFFFF,
};

typedef s32(TMCDecodeFunc)(s32* block, u8* conv_row_ptr, u32* dcPredictRowPtr, TMCCJPEGDecWork* work);
typedef void(TMCIdctFunc)(s32* block, u8* conv_row_ptr, u16 pitch, s32 zigzag);
typedef void(TMCConverterFunc)(TMCCJPEGDecWork*, s32 x, s32 y);

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    u32 coefficients[4][64];
    u8 zigzagData[64];
    u16* pDCFast;
    u32* pDCHuffTbl;
    u8* pDCHuffSym;
    u32 reservedDC;
    u16* pACFast;
    u32* pACHuffTbl;
    u8* pACHuffSym;
    u32 reservedAC;
    u16 huffDecTblDC0[0x200];
    u16 huffDecTblDC1[0x200];
    u16 huffDecTblAC0[0x200];
    u16 huffDecTblAC1[0x200];
    u32 valPtrDC0[17];
    u32 valPtrDC1[17];
    u32 valPtrAC0[17];
    u32 valPtrAC1[17];
    u8 maxCodeDC0[0x10];
    u8 maxCodeDC1[0x10];
    u8 maxCodeAC0[0x100];
    u8 maxCodeAC1[0x100];
    u8 quantTblFlag[4];
    u8 dcTblFlag[2];
    u8 acTblFlag[2];
} TMCJpegTableInfo;

typedef struct {
    u16 frameWidth;     // 0x00
    u16 frameHeight;    // 0x02
    u32 mcuCount;       // 0x04
    u32 mcuRemCount;    // 0x08
    u8 componentCount;  // 0x0C
    u8 mcuXCount;       // 0x0D
    u8 mcuXRem;         // 0x0E
    u8 mcuYRem;         // 0x0F
    u16 mcuYCount;      // 0x10
    u16 mcuXCount2;     // 0x12
    u32 mcuTotal;  // 0x14
    u8 remX;  // 0x18
    u8 remY;  // 0x19
    u8 compCount;         // 0x1A
    u8 scanCompCount;     // 0x1B
    u8 blockCount[4];     // 0x1C
    u8 hSampFactor[4];    // 0x20
    u8 vSampFactor[4];    // 0x24
    u8 maxHSamp;          // 0x28
    u8 maxVSamp;          // 0x29
    u16 restartInterval;  // 0x2A
    u8 scanCount;         // 0x2C
    u8 alignmentPadding[0x03];
} TMCJpegFrameInfo;

typedef struct {
    u8 map[4];
    u32 dcPredict[4];
    u8 id[4];
    u8 quantTable[4];
    u8 dcTable[4];
    u8 acTable[4];
} TMCFrameComponents;

struct TMCCJPEGDecWork_t {
    u32 bitBuf;                   // 0x00
    s32 bitCount;                 // 0x04
    u8* pBufStart;                // 0x08
    u8* pBufCur;                  // 0x0C
    u8* pBufEnd;                  // 0x10
    u8* pBufMark;                 // 0x14
    u8* pBufOrg;                  // 0x18
    u32 bufLen;                   // 0x1C
    s32 remaining;                // 0x20
    TMCCReadCallback* pCallback;  // 0x24
    void* pCbCtx;                 // 0x28
    TMCFrameComponents components;
    u16 restartCnt;               // 0x50
    u16 rstMarkerIdx;             // 0x52
    u32 mcuPos;                   // 0x54
    TMCJpegTableInfo tables;
    // Section below is likely a nested struct
    u16 frameWidth;     // 0x17F0
    u16 frameHeight;    // 0x17F2
    u32 mcuCount;       // 0x17F4
    u32 mcuRemCount;    // 0x17F8
    u8 componentCount;  // 0x17FC
    u8 mcuXCount;       // 0x17FD
    u8 mcuXRem;         // 0x17FE
    u8 mcuYRem;         // 0x17FF
    u16 mcuYCount;      // 0x1800
    u16 mcuXCount2;     // 0x1802
    u32 mcuTotal;  // 0x1804
    u8 remX;  // 0x1808
    u8 remY;  // 0x1809
    u8 compCount;         // 0x180A
    u8 scanCompCount;     // 0x180B
    u8 blockCount[4];     // 0x180C
    u8 hSampFactor[4];    // 0x1810
    u8 vSampFactor[4];    // 0x1814
    u8 maxHSamp;          // 0x1818
    u8 maxVSamp;          // 0x1819
    u16 restartInterval;  // 0x181A
    u8 scanCount;         // 0x181C
    u8 framePadding[0x03];
    TMCIdctFunc* idctPtr;                  // 0x1820
    TMCIdctFunc* idctLumiPtr;              // 0x1824
    TMCDecodeFunc* decodePtr;              // 0x1828
    TMCConverterFunc* pConverterFunc;      // 0x182C
    TMCConverterFunc* pConverterFuncEdge;  // 0x1830
    u32 blockSize;                         // 0x1834
    u32 blockSizeMul;                      // 0x1838
    u8* pConvRowPtrs[7];                   // 0x183C
    u8 convBuf[0x184];                     // 0x1858
    u8 idctMode;                           // 0x19DC
    u8 pitchPadding;
    u16 pitch;          // 0x19DE
    u8 converterFlags;  // 0x19E0
    u8 statePadding[0x03];
    TMCCJPEGDecState* pState;  // 0x19E4
};

s32 TMCJPEGDEC_init_ptr_buff(TMCCJPEGDecWork* work, void* param);
s32 TMCJPEGDEC_get_byte(u8* dst, TMCCJPEGDecWork* work);
s32 TMCJPEGDEC_get_wbyte(u16* dst, TMCCJPEGDecWork* work);
s32 TMCJPEGDEC_get_sbyte(u8* dst, u32 count, TMCCJPEGDecWork* work);
s32 TMCJPEGDEC_move_ptr(s32 offset, TMCCJPEGDecWork* work);
s32 TMCJPEGDEC_load_buff(TMCCJPEGDecWork* work);
s32 TMCJPEGDEC_get_position(TMCCJPEGDecWork* work);
s32 TMCJPEGDEC_chk_possible_size(TMCCJPEGDecWork* work);

s32 TMCJPEGDEC_init_buff_thumbnail(TMCCJPEGDecWork* work, u8* dst, u8* src);
s32 TMCJPEGDEC_init_buff(TMCCJPEGDecWork* work);
s32 TMCJPEGDEC_rewind_ptr(TMCCJPEGDecWork* work);

typedef struct {
    u32* huffTable;  // 0x00
    u32* valptr;      // 0x04
    u32* maxCode;    // 0x08
    u8 count;        // 0x0C
} TMCHuffParam;

s32 TMCJPEGDEC_make_huffdec(const u8* dht_spec, u8* tbl, TMCHuffParam* hp);
void TMCJPEGDEC_set_HuffmanTable(TMCHuffParam* tbl, s32 tblType, s32 tblID, TMCJpegTableInfo* work);

s32 TMCJPEGDEC_decompmcu(u32 maxMCU, u32 mcuCount, TMCCJPEGDecWork* work, void* buf);
s32 TMCJPEGDEC_imagestart(TMCCJPEGDecWork* work);
s32 TMCJPEGDEC_imageend(TMCCJPEGDecWork* work);
s32 TMCJPEGDEC_scanstart(TMCCJPEGDecWork* work);
s32 TMCJPEGDEC_scan_varinit(TMCCJPEGDecWork* work);
s32 TMCJPEGDEC_restart_interval(TMCCJPEGDecWork* work, u32 maxMCU, u32 mcuCount);
s32 TMCJPEGDEC_err_restart(TMCCJPEGDecWork* work);
void TMCJPEGDEC_set_entropytbl(TMCJpegTableInfo* work, s32 idx, u8 data);

s32 TMCJPEGDEC_Decompscan(TMCCJPEGDecWork* work);
s32 TMCJPEGDEC_Setsize(TMCCJPEGDecWork* work);
s32 TMCJPEGDEC_HeaderAnalyze(TMCCJPEGDecWork* work);

void TMCJPEGDEC_IdctBlock_Lumi(s32* block, u8* conv_row_ptr, u16 pitch, s32 zigzag);
void TMCJPEGDEC_IdctBlock_Col(s32* block, u8* conv_row_ptr, u16 pitch, s32 zigzag);

s32 TMCJPEGDEC_decode_iquant(s32* block, u8* conv_row_ptr, u32* dc_predict_row_ptr, TMCCJPEGDecWork* work);
s32 TMCJPEGDEC_decode_iquant_rc(s32* block, u8* conv_row_ptr, u32* dc_predict_row_ptr, TMCCJPEGDecWork* work);
s32 TMCJPEGDEC_vl_decode_rc(u32* huff_tbl, u8* huff_sym, TMCCJPEGDecWork* work);

void TMCJPEGDEC_IdctBlock4x4(s32* block, u8* conv_row_ptr, u16 pitch, s32 zigzag);
void TMCJPEGDEC_IdctBlock2x2(s32* block, u8* conv_row_ptr, u16 pitch, s32 zigzag);
void TMCJPEGDEC_IdctBlock1x1(s32* block, u8* conv_row_ptr, u16 pitch, s32 zigzag);
void TMCJPEGDEC_IdctBlock4x4_Col(s32* block, u8* conv_row_ptr, u16 pitch, s32 zigzag);
void TMCJPEGDEC_IdctBlock2x2_Col(s32* block, u8* conv_row_ptr, u16 pitch, s32 zigzag);
void TMCJPEGDEC_IdctBlock1x1_Col(s32* block, u8* conv_row_ptr, u16 pitch, s32 zigzag);

s32 TMCJPEGDEC_set_converterY8U8V8(TMCCJPEGDecWork* work);
s32 TMCJPEGDEC_set_converterRGB565(TMCCJPEGDecWork* work);
s32 TMCJPEGDEC_set_converterRGBA8(TMCCJPEGDecWork* work);

extern const u8 TMCJPEGDEC_SampleH_N[6][4];
extern const u8 TMCJPEGDEC_SampleV_N[6][4];
extern const u8 TMCJPEGDEC_Zigzag_data[64];
extern const u32 TMCJPEGDEC_Zigzag_loop[64];
#ifdef TMC_JPEG_FRAME_PARSER
extern const u8 TMCJPEGDEC_SampleComps[];
#else
extern const u8 TMCJPEGDEC_SampleComps[6];
#endif

#ifdef __cplusplus
}
#endif

#endif  // TMC_JPEG_INTERNAL_H
