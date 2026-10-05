#include <string.h>
#include <tmc_jpeg.h>
#include <tmc_jpeg_internal.h>

enum TMCExifFormat {
    TMC_EXIF_LITTLE_ENDIAN = 0x4949,
    TMC_EXIF_BIG_ENDIAN = 0x4D4D,
    TMC_EXIF_TIFF_MAGIC = 42,
    TMC_EXIF_TYPE_SHORT = 3,
    TMC_EXIF_TYPE_LONG = 4,
    TMC_EXIF_COMPRESSION_JPEG = 6
};

enum TMCExifTag {
    TMC_EXIF_TAG_COMPRESSION = 0x0103,
    TMC_EXIF_TAG_STRIP_OFFSETS = 0x0111,
    TMC_EXIF_TAG_ORIENTATION = 0x0112,
    TMC_EXIF_TAG_X_RESOLUTION = 0x011A,
    TMC_EXIF_TAG_Y_RESOLUTION = 0x011B,
    TMC_EXIF_TAG_PLANAR_CONFIGURATION = 0x011C,
    TMC_EXIF_TAG_RESOLUTION_UNIT = 0x0128,
    TMC_EXIF_TAG_TRANSFER_FUNCTION = 0x012D,
    TMC_EXIF_TAG_DATE_TIME = 0x0132,
    TMC_EXIF_TAG_JPEG_INTERCHANGE_FORMAT = 0x0201,
    TMC_EXIF_TAG_JPEG_INTERCHANGE_FORMAT_LENGTH = 0x0202,
    TMC_EXIF_TAG_YCBCR_POSITIONING = 0x0213,
    TMC_EXIF_TAG_EXIF_IFD = 0x8769,
    TMC_EXIF_TAG_EXIF_VERSION = 0x9000,
    TMC_EXIF_TAG_COMPONENTS_CONFIGURATION = 0x9101,
    TMC_EXIF_TAG_FLASHPIX_VERSION = 0xA000,
    TMC_EXIF_TAG_COLOR_SPACE = 0xA001,
    TMC_EXIF_TAG_PIXEL_X_DIMENSION = 0xA002,
    TMC_EXIF_TAG_PIXEL_Y_DIMENSION = 0xA003,
};

typedef struct {
    u8 tag[2];
    u8 type[2];
    u8 count[4];
    u8 value[4];
} TMCExifEntry;

static s32 TMCJPEGDEC_exif_parse(const u8* data, u32 size, TMCCJPEGDecExifData* pInfo);
static void TMCJPEGDEC_IFD0_tag_parse(TMCCJPEGDecExifData* pInfo, u16 byteOrder, TMCExifEntry* entry);
static void TMCJPEGDEC_IFD1_tag_parse(TMCCJPEGDecExifData* pInfo, u16 byteOrder, const TMCExifEntry* entry);
static s32 TMCJPEGDEC_ThumbnailCheck(TMCCJPEGDecInitParam* param, TMCCJPEGDecExifInfo* info, u32 totalSize);

static u16 readU16(const u8* p, u16 byteOrder) {
    u32 raw = p[1] << 8 | p[0];
    if (byteOrder == TMC_EXIF_LITTLE_ENDIAN) {
        return raw;
    }
    return raw >> 8 & 0xFF | (raw & 0xFF) << 8;
}

static u16 readExifU16(const u8* data, u16 byteOrder) {
    u16 value = data[0] | data[1] << 8;
    if (byteOrder == TMC_EXIF_LITTLE_ENDIAN) {
        return (u16)value;
    }
    return value >> 8 & 255 | (value & 255) << 8;
}

static u32 readU32(const u8* p, u16 byteOrder) {
    u32 raw = p[1] << 8 | p[0] | p[2] << 16 | p[3] << 24;
    if (byteOrder == TMC_EXIF_LITTLE_ENDIAN) {
        return raw;
    }
    return (raw >> 24) | ((raw >> 8) & 0xFF00) | ((raw & 0xFF00) << 8) | ((raw & 0xFF) << 24);
}

s32 TMCCJPEGDecGetOffsetEXIF(u32* pOffset, u32* pSize, TMCCJPEGDecInitParam* pParam) {
    TMCCJPEGDecWork* work;
    u16 segSize;
    u32 dataSize;
    u16 marker;
    s32 result;
    u8 sig[4];

    dataSize = pParam->dataSize;
    work = pParam->pBuf1;

    if (work == NULL) {
        return -1;
    }

    memset(work, 0, sizeof(TMCCJPEGDecWork));

    result = TMCJPEGDEC_init_ptr_buff(work, &pParam->pBuf2);
    if (result < 0) {
        return result;
    }

    {
        u16 soi;

        result = TMCJPEGDEC_get_wbyte(&soi, work);
        if (result < 0) {
            return result;
        }

        if (soi != TMC_JPEG_MARKER_SOI) {
            return -0x20;
        }
    }

    for (;;) {
        result = TMCJPEGDEC_get_wbyte(&marker, work);
        if (result < 0) {
            return result;
        }

        if (marker == TMC_JPEG_MARKER_APP1) {
            result = TMCJPEGDEC_get_wbyte(&segSize, work);
            if (result < 0) {
                return result;
            }

            if (segSize < 2) {
                return -0x45;
            }

            result = TMCJPEGDEC_get_sbyte(sig, 4, work);
            if (result < 0) {
                return result;
            }

            if (sig[0] == 'E' && sig[1] == 'x' && sig[2] == 'i' && sig[3] == 'f') {
                *pOffset = dataSize - work->remaining - TMCJPEGDEC_chk_possible_size(work) - 8;
                *pSize = segSize + 2;
                return 0;
            }

            return -0x45;
        }

        result = TMCJPEGDEC_get_wbyte(&segSize, work);
        if (result < 0) {
            return result;
        }

        if (segSize < 2) {
            return -0x45;
        }

        segSize -= 2;

        if (marker >= TMC_JPEG_MARKER_APP0 && marker <= TMC_JPEG_MARKER_APP15) {
            result = TMCJPEGDEC_move_ptr(segSize, work);
            if (result < 0) {
                return result;
            }
            continue;
        }

        switch (marker) {
            case TMC_JPEG_MARKER_SOF0:
            case TMC_JPEG_MARKER_SOF2:
            case TMC_JPEG_MARKER_DHT:
            case TMC_JPEG_MARKER_DQT:
            case TMC_JPEG_MARKER_DNL:
            case TMC_JPEG_MARKER_DRI:
            case TMC_JPEG_MARKER_COM:
                result = TMCJPEGDEC_move_ptr(segSize, work);
                if (result < 0) {
                    return result;
                }
                break;
            case TMC_JPEG_MARKER_SOS:
                return -2;
            case TMC_JPEG_MARKER_EOI:
                return -2;
            default:
                return -0x2F;
        }
    }
}

s32 TMCCJPEGDecGetInfoEXIF(TMCCJPEGDecExifInfo* pInfo, TMCCJPEGDecInitParam* pParam) {
    TMCCJPEGDecWork* work;
    u32 segSize;
    u16 segSizeP2;
    u16 exifSize;
    s32 result;

    work = pParam->pBuf1;
    if (work == NULL) {
        return -1;
    }

    memset(pInfo, 0, sizeof(TMCCJPEGDecExifInfo));
    memset(work, 0, sizeof(TMCCJPEGDecWork));

    // TODO: this seems wrong. wrong parameter type?
    work->pState = (TMCCJPEGDecState*)pInfo;
    pInfo->pWorkBuf = work;

    if (readU16(pParam->pBuf2, TMC_EXIF_BIG_ENDIAN) != TMC_JPEG_MARKER_APP1) {
        return -0x45;
    }

    segSize = readU16((const u8*)pParam->pBuf2 + 2, TMC_EXIF_BIG_ENDIAN);
    if (segSize < 2) {
        return -0x45;
    }

    segSizeP2 = segSize + 2;
    exifSize = segSize - 8;
    result = TMCJPEGDEC_exif_parse((const u8*)pParam->pBuf2 + 10, exifSize, &pInfo->exifData);
    if (result < 0) {
        return result;
    }

    if (pParam->unk_0x24 == 0) {
        return 0;
    }

    if (pParam->unk_0x24 == 1) {
        result = TMCJPEGDEC_ThumbnailCheck(pParam, pInfo, segSizeP2);
        if (result < 0) {
            return result;
        }
    } else {
        return -1;
    }

    result = TMCJPEGDEC_init_buff_thumbnail((TMCCJPEGDecWork*)&pInfo->exifData, (u8*)work, (u8*)&pParam->pBuf2);
    if (result < 0) {
        return result;
    }

    result = TMCJPEGDEC_HeaderAnalyze(work);
    if (result < 0) {
        goto _error;
    }

    result = TMCJPEGDEC_Decompscan(work);
    if (result < 0) {
        goto _error;
    }

    if (work->scanCount != 0) {
        goto _error;
    }

    result = TMCJPEGDEC_Setsize(work);
    if (result < 0) {
        goto _error;
    }

    switch (pInfo->converterType) {
        case TMCC_JPEG_OUTPUT_RGB565:
            result = TMCJPEGDEC_set_converterRGB565(work);
            if (result < 0) {
                goto _error;
            }
            break;
        case TMCC_JPEG_OUTPUT_RGBA8:
            result = TMCJPEGDEC_set_converterRGBA8(work);
            if (result < 0) {
                goto _error;
            }
            break;
        case TMCC_JPEG_OUTPUT_Y8U8V8:
            result = TMCJPEGDEC_set_converterY8U8V8(work);
            if (result < 0) {
                goto _error;
            }
            break;
    }

    pInfo->position = TMCJPEGDEC_get_position(work);
    return pInfo->state;

_error:
    if (result < 0) {
        return result;
    }
    return -2;
}

static s32 TMCJPEGDEC_exif_parse(const u8* entries, u32 size, TMCCJPEGDecExifData* pInfo) {
    u16 byteOrder;
    u32 ifdOffset;
    const u8* data = entries;
    const u8* exifEntries;
    u32 exifCount;
    u16 exifIndex;
    const u8* ifd1Entries;
    u32 ifd1Count;
    u16 ifd1Index;
    u16 remaining;
    u16 index;
    u32 count;

    pInfo->thumbnailData = (u8*)data;
    pInfo->dataEnd = (u8*)data + size;
    pInfo->nextIfdOffset = 0;
    if (size < 8) {
        return -161;
    }
    byteOrder = data[0] | data[1] << 8;
    if (byteOrder != TMC_EXIF_BIG_ENDIAN && byteOrder != TMC_EXIF_LITTLE_ENDIAN) {
        return -161;
    }
    if (readExifU16(data + 2, byteOrder) != TMC_EXIF_TIFF_MAGIC) {
        return -161;
    }
    ifdOffset = readU32(data + 4, byteOrder);
    if (size < ifdOffset) {
        return -161;
    }
    {
        entries = data + ifdOffset;
        remaining = size - (u16)ifdOffset;
        if (remaining < 2) {
            return -161;
        }
        count = readExifU16(entries, byteOrder);
        entries += 2;
        remaining -= 2;
        if (remaining < (s32)count * 12) {
            return -161;
        }
        for (index = 0; index < count; index++) {
            TMCJPEGDEC_IFD0_tag_parse(pInfo, byteOrder, (TMCExifEntry*)entries);
            entries += sizeof(TMCExifEntry);
        }
        remaining -= (s32)count * 12;
        if (remaining < 4) {
            return -161;
        }
        ifdOffset = readU32(entries, byteOrder);
    }
    if (ifdOffset == 0) {
        return 0;
    }
    if (size < ifdOffset) {
        return -161;
    }
    {
        ifd1Entries = data + ifdOffset;
        remaining = size - (u16)ifdOffset;
        if (remaining < 2) {
            return -161;
        }
        ifd1Count = readExifU16(ifd1Entries, byteOrder);
        ifd1Entries += 2;
        remaining -= 2;
        if (remaining < (s32)ifd1Count * 12) {
            return -161;
        }
        for (ifd1Index = 0; ifd1Index < ifd1Count; ifd1Index++) {
            TMCJPEGDEC_IFD1_tag_parse(pInfo, byteOrder, (const TMCExifEntry*)ifd1Entries);
            ifd1Entries += sizeof(TMCExifEntry);
        }
    }
    ifdOffset = pInfo->nextIfdOffset;
    if (size < ifdOffset) {
        return -161;
    }
    {
        exifEntries = data + ifdOffset;
        remaining = size - (u16)ifdOffset;
        if (remaining < 2) {
            return -161;
        }
        exifCount = readExifU16(exifEntries, byteOrder);
        exifEntries += 2;
        remaining -= 2;
        if (remaining < (s32)exifCount * 12) {
            return -161;
        }
        for (exifIndex = 0; exifIndex < exifCount; exifIndex++) {
            TMCJPEGDEC_IFD0_tag_parse(pInfo, byteOrder, (TMCExifEntry*)exifEntries);
            exifEntries += sizeof(TMCExifEntry);
        }
    }
    return 0;
}

static void TMCJPEGDEC_IFD0_tag_parse(TMCCJPEGDecExifData* pInfo, u16 byteOrder, TMCExifEntry* entry) {
    s32 tag;
    u32 type;

    tag = readExifU16(entry->tag, byteOrder);
    type = readExifU16(entry->type, byteOrder);

    switch (tag) {
        case TMC_EXIF_TAG_COMPRESSION:
        case TMC_EXIF_TAG_STRIP_OFFSETS:
        case TMC_EXIF_TAG_JPEG_INTERCHANGE_FORMAT:
        case TMC_EXIF_TAG_JPEG_INTERCHANGE_FORMAT_LENGTH: {
            break;
        }
        case TMC_EXIF_TAG_ORIENTATION: {
            pInfo->orientation = readU16(entry->value, byteOrder);
            return;
        }
        case TMC_EXIF_TAG_X_RESOLUTION: {
            u32 offset = readU32(entry->value, byteOrder);
            const u8* p = pInfo->thumbnailData + offset;
            if (pInfo->thumbnailData > p) {
                return;
            }
            if (p > pInfo->dataEnd - sizeof(u32)) {
                return;
            }
            pInfo->xResNum = readU32(p, byteOrder);
            p = pInfo->thumbnailData + (offset + sizeof(u32));
            if (pInfo->thumbnailData > p) {
                return;
            }
            if (p > pInfo->dataEnd - sizeof(u32)) {
                return;
            }
            pInfo->xResDen = readU32(p, byteOrder);
            return;
        }
        case TMC_EXIF_TAG_Y_RESOLUTION: {
            u32 offset = readU32(entry->value, byteOrder);
            const u8* p = pInfo->thumbnailData + offset;
            if (pInfo->thumbnailData > p) {
                return;
            }
            if (p > pInfo->dataEnd - sizeof(u32)) {
                return;
            }
            pInfo->yResNum = readU32(p, byteOrder);
            p = pInfo->thumbnailData + (offset + sizeof(u32));
            if (pInfo->thumbnailData > p) {
                return;
            }
            if (p > pInfo->dataEnd - sizeof(u32)) {
                return;
            }
            pInfo->yResDen = readU32(p, byteOrder);
            return;
        }
        case TMC_EXIF_TAG_RESOLUTION_UNIT: {
            pInfo->resUnit = readU16(entry->value, byteOrder);
            return;
        }
        case TMC_EXIF_TAG_TRANSFER_FUNCTION: {
            u32 offset = readU32(entry->value, byteOrder);
            u32 channel;
            u32 index;
            for (channel = 0; channel < 3; channel++) {
                for (index = 0; index < 256; index++) {
                    const u8* p = pInfo->thumbnailData + offset;
                    if (pInfo->thumbnailData > p) {
                        break;
                    }
                    if (p > pInfo->dataEnd - sizeof(u16)) {
                        break;
                    }
                    pInfo->transferFunc[channel][index] = readU16(p, byteOrder);
                    offset += sizeof(u16);
                }
            }
            return;
        }
        case TMC_EXIF_TAG_DATE_TIME: {
            u32 offset = readU32(entry->value, byteOrder);
            const u8* p = pInfo->thumbnailData + offset;
            if (pInfo->thumbnailData > p) {
                return;
            }
            if (p > pInfo->dataEnd - sizeof(pInfo->dateTime)) {
                return;
            }
            {
                u32 index;
                for (index = 0; index < sizeof(pInfo->dateTime); index++) {
                    pInfo->dateTime[index] = p[index];
                }
            }
            return;
        }
        case TMC_EXIF_TAG_YCBCR_POSITIONING: {
            pInfo->yCbCrPos = readU16(entry->value, byteOrder);
            return;
        }
        case TMC_EXIF_TAG_EXIF_IFD: {
            pInfo->nextIfdOffset = readU32(entry->value, byteOrder);
            return;
        }
        case TMC_EXIF_TAG_EXIF_VERSION: {
            pInfo->exifVer[0] = entry->value[0];
            pInfo->exifVer[1] = entry->value[1];
            pInfo->exifVer[2] = entry->value[2];
            pInfo->exifVer[3] = entry->value[3];
            return;
        }
        case TMC_EXIF_TAG_COMPONENTS_CONFIGURATION: {
            pInfo->flashVer[0] = entry->value[0];
            pInfo->flashVer[1] = entry->value[1];
            pInfo->flashVer[2] = entry->value[2];
            pInfo->flashVer[3] = entry->value[3];
            return;
        }
        case TMC_EXIF_TAG_FLASHPIX_VERSION: {
            pInfo->flashPixVer[0] = entry->value[0];
            pInfo->flashPixVer[1] = entry->value[1];
            pInfo->flashPixVer[2] = entry->value[2];
            pInfo->flashPixVer[3] = entry->value[3];
            return;
        }
        case TMC_EXIF_TAG_COLOR_SPACE: {
            pInfo->colorSpace = readU16(entry->value, byteOrder);
            return;
        }
        case TMC_EXIF_TAG_PIXEL_X_DIMENSION: {
            if (type == TMC_EXIF_TYPE_SHORT) {
                pInfo->pixelXDim = readU16(entry->value, byteOrder);
            } else if (type == TMC_EXIF_TYPE_LONG) {
                pInfo->pixelXDim = readU32(entry->value, byteOrder);
            }
            return;
        }

        case TMC_EXIF_TAG_PIXEL_Y_DIMENSION: {
            if (type == TMC_EXIF_TYPE_SHORT) {
                pInfo->pixelYDim = readU16(entry->value, byteOrder);
            } else if (type == TMC_EXIF_TYPE_LONG) {
                pInfo->pixelYDim = readU32(entry->value, byteOrder);
            }
            return;
        }
    }
}

static void TMCJPEGDEC_IFD1_tag_parse(TMCCJPEGDecExifData* pInfo, u16 byteOrder, const TMCExifEntry* entry) {
    s32 tag = readU16(entry->tag, byteOrder);

    switch (tag) {
        case TMC_EXIF_TAG_DATE_TIME:
        case TMC_EXIF_TAG_STRIP_OFFSETS:
        case TMC_EXIF_TAG_ORIENTATION:
        case TMC_EXIF_TAG_TRANSFER_FUNCTION:
        case TMC_EXIF_TAG_YCBCR_POSITIONING:
        case TMC_EXIF_TAG_EXIF_IFD:
        case TMC_EXIF_TAG_EXIF_VERSION:
        case TMC_EXIF_TAG_COMPONENTS_CONFIGURATION:
        case TMC_EXIF_TAG_PLANAR_CONFIGURATION:
        case TMC_EXIF_TAG_FLASHPIX_VERSION:
        case TMC_EXIF_TAG_COLOR_SPACE:
        case TMC_EXIF_TAG_PIXEL_X_DIMENSION:
        case TMC_EXIF_TAG_PIXEL_Y_DIMENSION: {
            break;
        }
        case TMC_EXIF_TAG_X_RESOLUTION: {
            u32 offset;
            const u8* p;
            offset = readU32(entry->value, byteOrder);
            p = pInfo->thumbnailData + offset;
            if (pInfo->thumbnailData > p) {
                return;
            }
            if (p > pInfo->dataEnd - sizeof(u32)) {
                return;
            }
            pInfo->xResNumIfd1 = readU32(p, byteOrder);
            p = pInfo->thumbnailData + (offset + sizeof(u32));
            if (pInfo->thumbnailData > p) {
                return;
            }
            if (p > pInfo->dataEnd - sizeof(u32)) {
                return;
            }
            pInfo->xResDenIfd1 = readU32(p, byteOrder);
            return;
        }
        case TMC_EXIF_TAG_Y_RESOLUTION: {
            u32 offset;
            const u8* p;
            offset = readU32(entry->value, byteOrder);
            p = pInfo->thumbnailData + offset;
            if (pInfo->thumbnailData > p) {
                return;
            }
            if (p > pInfo->dataEnd - sizeof(u32)) {
                return;
            }
            pInfo->planarConfigIfd1 = readU32(p, byteOrder);
            p = pInfo->thumbnailData + (offset + sizeof(u32));
            if (pInfo->thumbnailData > p) {
                return;
            }
            if (p > pInfo->dataEnd - sizeof(u32)) {
                return;
            }
            pInfo->yResDenIfd1 = readU32(p, byteOrder);
            return;
        }
        case TMC_EXIF_TAG_RESOLUTION_UNIT: {
            pInfo->resUnitIfd1 = readU16(entry->value, byteOrder);
            return;
        }
        case TMC_EXIF_TAG_COMPRESSION: {
            pInfo->compressionIfd1 = readU16(entry->value, byteOrder);
            return;
        }
        case TMC_EXIF_TAG_JPEG_INTERCHANGE_FORMAT: {
            pInfo->thumbnailOffset = readU32(entry->value, byteOrder);
            return;
        }
        case TMC_EXIF_TAG_JPEG_INTERCHANGE_FORMAT_LENGTH: {
            pInfo->thumbnailLength = readU32(entry->value, byteOrder);
            return;
        }
    }
}

static s32 TMCJPEGDEC_ThumbnailCheck(TMCCJPEGDecInitParam* param, TMCCJPEGDecExifInfo* info, u32 totalSize) {
    s32 total;
    s32 length;
    s32 tmp;

    total = (s32)info->exifData.thumbnailOffset;
    if (total == 0) {
        return -0xA0;
    }

    length = (s32)info->exifData.thumbnailLength;
    if (length == 0) {
        return -0xA0;
    }

    if (info->exifData.compressionIfd1 != TMC_EXIF_COMPRESSION_JPEG) {
        return -0xA0;
    }

    tmp = (s32)info->exifData.thumbnailData - (s32)param->pBuf2;
    total = length + total + tmp;

    if ((u32)total > param->buf2Size) {
        return -0xF1;
    }

    if ((u32)total > totalSize) {
        return -0xF1;
    }

    info->exifFlags = 1;

    if (param->unk_0x24 != 1) {
        return -1;
    }

    info->thumbFlag = 0;

    if (param->unk_0x2C != TMCC_JPEG_OUTPUT_RGB565 && param->unk_0x2C != TMCC_JPEG_OUTPUT_RGBA8 &&
        param->unk_0x2C != TMCC_JPEG_OUTPUT_Y8U8V8) {
        return -1;
    }

    info->converterType = param->unk_0x2C;
    return 0;
}
