#include <string.h>
#include <tmc_jpeg.h>
#include <tmc_jpeg_internal.h>

static s32 TMCJPEGDEC_exif_parse(const u8* data, u32 size, TMCCJPEGDecExifData* pInfo);
static void TMCJPEGDEC_IFD0_tag_parse(TMCCJPEGDecExifData* pInfo, u16 byteOrder, const u8* entry);
static void TMCJPEGDEC_IFD1_tag_parse(TMCCJPEGDecExifData* pInfo, u16 byteOrder, const u8* entry);
static s32 TMCJPEGDEC_ThumbnailCheck(TMCCJPEGDecInitParam* param, TMCCJPEGDecExifInfo* info, u32 totalSize);

static u16 readU16(const u8* p, u16 byteOrder) {
    u32 raw = p[1] << 8 | p[0];
    if (byteOrder == 0x4949) {
        return (u16)raw;
    }
    return (u16)(raw >> 8 & 0xFF | (raw & 0xFF) << 8);
}

static u16 readExifU16(const u8* data, u16 byteOrder) {
    u32 value = data[0] | data[1] << 8;
    if (byteOrder == 0x4949) {
        return (u16)value;
    }
    return (u16)(value >> 8 & 255 | (value & 255) << 8);
}

static u32 readU32(const u8* p, u16 byteOrder) {
    u32 raw = p[1] << 8 | p[0] | p[2] << 16 | p[3] << 24;
    if (byteOrder == 0x4949) {
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

    memset(work, 0, 0x19E8);

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

        if (soi != 0xFFD8) {
            return -0x20;
        }
    }

    for (;;) {
        result = TMCJPEGDEC_get_wbyte(&marker, work);
        if (result < 0) {
            return result;
        }

        if (marker == 0xFFE1) {
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

            if (sig[0] == 0x45 && sig[1] == 0x78 && sig[2] == 0x69 && sig[3] == 0x66) {
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

        if (marker >= 0xFFE0 && marker <= 0xFFEF) {
            result = TMCJPEGDEC_move_ptr(segSize, work);
            if (result < 0) {
                return result;
            }
            continue;
        }

        switch (marker) {
            case 0xFFC0:
            case 0xFFC2:
            case 0xFFC4:
            case 0xFFDB:
            case 0xFFDC:
            case 0xFFDD:
            case 0xFFFE:
                result = TMCJPEGDEC_move_ptr(segSize, work);
                if (result < 0) {
                    return result;
                }
                break;
            case 0xFFDA:
                return -2;
            case 0xFFD9:
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

    memset(pInfo, 0, 0x6D4);
    memset(work, 0, 0x19E8);

    // TODO: this seems wrong. wrong parameter type?
    work->pState = (TMCCJPEGDecState*)pInfo;
    pInfo->pWorkBuf = work;

    if (readU16(pParam->pBuf2, 0x4D4D) != 0xFFE1) {
        return -0x45;
    }

    segSize = readU16((const u8*)pParam->pBuf2 + 2, 0x4D4D);
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

    result = TMCJPEGDEC_init_buff_thumbnail((TMCCJPEGDecWork*)&pInfo->exifData, (u8*)work, (u8*)pParam + 0x10);
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
        case 0:
            result = TMCJPEGDEC_set_converterRGB565(work);
            if (result < 0) {
                goto _error;
            }
            break;
        case 1:
            result = TMCJPEGDEC_set_converterRGBA8(work);
            if (result < 0) {
                goto _error;
            }
            break;
        case 2:
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

static s32 TMCJPEGDEC_exif_parse(const u8* data, u32 size, TMCCJPEGDecExifData* pInfo) {
    u16 byteOrder;
    u32 ifdOffset;
    pInfo->thumbnailData = (u8*)data;
    pInfo->dataEnd = (u8*)data + size;
    pInfo->nextIfdOffset = 0;
    if (size < 8) {
        return -161;
    }
    byteOrder = data[0] | data[1] << 8;
    if (byteOrder != 0x4D4D && byteOrder != 0x4949) {
        return -161;
    }
    if (readExifU16(data + 2, byteOrder) != 42) {
        return -161;
    }
    ifdOffset = readU32(data + 4, byteOrder);
    if (size < ifdOffset) {
        return -161;
    }
    {
        const u8* entries = data + ifdOffset;
        u16 remaining = size - (u16)ifdOffset;
        u16 count;
        s32 entriesSize;
        u16 index;
        if (remaining < 2) {
            return -161;
        }
        count = readExifU16(entries, byteOrder);
        entriesSize = count * 12;
        entries += 2;
        remaining -= 2;
        if (remaining < entriesSize) {
            return -161;
        }
        for (index = 0; index < count; index++) {
            TMCJPEGDEC_IFD0_tag_parse(pInfo, byteOrder, entries);
            entries += 12;
        }
        remaining -= entriesSize;
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
        const u8* entries = data + ifdOffset;
        u16 remaining = size - (u16)ifdOffset;
        u16 count;
        s32 entriesSize;
        u16 index;
        if (remaining < 2) {
            return -161;
        }
        count = readExifU16(entries, byteOrder);
        entriesSize = count * 12;
        entries += 2;
        remaining -= 2;
        if (remaining < entriesSize) {
            return -161;
        }
        for (index = 0; index < count; index++) {
            TMCJPEGDEC_IFD1_tag_parse(pInfo, byteOrder, entries);
            entries += 12;
        }
    }
    ifdOffset = pInfo->nextIfdOffset;
    if (size < ifdOffset) {
        return -161;
    }
    {
        const u8* entries = data + ifdOffset;
        u16 remaining = size - (u16)ifdOffset;
        u16 count;
        s32 entriesSize;
        u16 index;
        if (remaining < 2) {
            return -161;
        }
        count = readExifU16(entries, byteOrder);
        entriesSize = count * 12;
        entries += 2;
        remaining -= 2;
        if (remaining < entriesSize) {
            return -161;
        }
        for (index = 0; index < count; index++) {
            TMCJPEGDEC_IFD0_tag_parse(pInfo, byteOrder, entries);
            entries += 12;
        }
    }
    return 0;
}

static void TMCJPEGDEC_IFD0_tag_parse(TMCCJPEGDecExifData* pInfo, u16 byteOrder, const u8* entry) {
    u16 tag;
    u16 type;

    tag = readU16(entry, byteOrder);
    type = readU16(entry + 2, byteOrder);

    switch (tag) {
        case 0x0103:
        case 0x0111:
        case 0x0201:
        case 0x0202: {
            return;
        }
        case 0x0112: {
            pInfo->orientation = readU16(entry + 8, byteOrder);
            return;
        }
        case 0x011A: {
            u32 offset = readU32(entry + 8, byteOrder);
            const u8* p = pInfo->thumbnailData + offset;
            if (pInfo->thumbnailData > p) {
                return;
            }
            if (p > pInfo->dataEnd - 4) {
                return;
            }
            pInfo->xResNum = readU32(p, byteOrder);
            p = (const u8*)(pInfo->thumbnailData + offset + 4);
            if (pInfo->thumbnailData > p) {
                return;
            }
            if (p > pInfo->dataEnd - 4) {
                return;
            }
            pInfo->xResDen = readU32(p, byteOrder);
            return;
        }
        case 0x011B: {
            u32 offset = readU32(entry + 8, byteOrder);
            const u8* p = pInfo->thumbnailData + offset;
            if (pInfo->thumbnailData > p) {
                return;
            }
            if (p > pInfo->dataEnd - 4) {
                return;
            }
            pInfo->yResNum = readU32(p, byteOrder);
            p = (const u8*)(pInfo->thumbnailData + offset + 4);
            if (pInfo->thumbnailData > p) {
                return;
            }
            if (p > pInfo->dataEnd - 4) {
                return;
            }
            pInfo->yResDen = readU32(p, byteOrder);
            return;
        }
        case 0x0128: {
            pInfo->resUnit = readU16(entry + 8, byteOrder);
            return;
        }
        case 0x012D: {
            u32 offset = readU32(entry + 8, byteOrder);
            u32 channel;
            u32 index;
            for (channel = 0; channel < 3; channel++) {
                for (index = 0; index < 256; index++) {
                    const u8* p = pInfo->thumbnailData + offset;
                    if (pInfo->thumbnailData > p) {
                        break;
                    }
                    if (p > pInfo->dataEnd - 2) {
                        break;
                    }
                    pInfo->transferFunc[channel][index] = readU16(p, byteOrder);
                    offset += 2;
                }
            }
            return;
        }
        case 0x0132: {
            u32 offset = readU32(entry + 8, byteOrder);
            const u8* p = pInfo->thumbnailData + offset;
            if (pInfo->thumbnailData > p) {
                return;
            }
            if (p > pInfo->dataEnd - 20) {
                return;
            }
            {
                u32 index;
                for (index = 0; index < 20; index++) {
                    pInfo->dateTime[index] = p[index];
                }
            }
            return;
        }
        case 0x0213: {
            pInfo->yCbCrPos = readU16(entry + 8, byteOrder);
            return;
        }
        case 0x8769: {
            pInfo->nextIfdOffset = readU32(entry + 8, byteOrder);
            return;
        }
        case 0x9000: {
            pInfo->exifVer[0] = entry[8];
            pInfo->exifVer[1] = entry[9];
            pInfo->exifVer[2] = entry[10];
            pInfo->exifVer[3] = entry[11];
            return;
        }
        case 0x9101: {
            pInfo->flashVer[0] = entry[8];
            pInfo->flashVer[1] = entry[9];
            pInfo->flashVer[2] = entry[10];
            pInfo->flashVer[3] = entry[11];
            return;
        }
        case 0xA000: {
            pInfo->flashPixVer[0] = entry[8];
            pInfo->flashPixVer[1] = entry[9];
            pInfo->flashPixVer[2] = entry[10];
            pInfo->flashPixVer[3] = entry[11];
            return;
        }
        case 0xA001: {
            pInfo->colorSpace = readU16(entry + 8, byteOrder);
            return;
        }
        case 0xA002: {
            u32 offset = readU32(entry + 8, byteOrder);
            if (type == 4) {
                pInfo->pixelXDim = offset;
            } else if (type == 3) {
                pInfo->pixelXDim = readU16(entry + 8, byteOrder);
            }
            return;
        }

        case 0xA003: {
            u32 offset = readU32(entry + 8, byteOrder);
            if (type == 4) {
                pInfo->pixelYDim = offset;
            } else if (type == 3) {
                pInfo->pixelYDim = readU16(entry + 8, byteOrder);
            }
            return;
        }
    }
}

static void TMCJPEGDEC_IFD1_tag_parse(TMCCJPEGDecExifData* pInfo, u16 byteOrder, const u8* entry) {
    s32 tag = readU16(entry, byteOrder);

    switch (tag) {
        case 0x0132:
        case 0x0111:
        case 0x0112:
        case 0x012D:
        case 0x0213:
        case 0x8769:
        case 0x9000:
        case 0x9101:
        case 0xA003: {
            return;
        }
        case 0x011A: {
            u32 offset;
            const u8* p;
            offset = readU32(entry + 8, byteOrder);
            p = pInfo->thumbnailData + offset;
            if (pInfo->thumbnailData > p) {
                return;
            }
            if (p > pInfo->dataEnd - 4) {
                return;
            }
            pInfo->xResNumIfd1 = readU32(p, byteOrder);
            p = (const u8*)(pInfo->thumbnailData + offset + 4);
            if (pInfo->thumbnailData > p) {
                return;
            }
            if (p > pInfo->dataEnd - 4) {
                return;
            }
            pInfo->xResDenIfd1 = readU32(p, byteOrder);
            return;
        }
        case 0x011B: {
            u32 offset;
            const u8* p;
            offset = readU32(entry + 8, byteOrder);
            p = pInfo->thumbnailData + offset;
            if (pInfo->thumbnailData > p) {
                return;
            }
            if (p > pInfo->dataEnd - 4) {
                return;
            }
            pInfo->planarConfigIfd1 = readU32(p, byteOrder);
            p = (const u8*)(pInfo->thumbnailData + offset + 4);
            if (pInfo->thumbnailData > p) {
                return;
            }
            if (p > pInfo->dataEnd - 4) {
                return;
            }
            pInfo->yResDenIfd1 = readU32(p, byteOrder);
            return;
        }
        case 0x0128: {
            pInfo->resUnitIfd1 = readU16(entry + 8, byteOrder);
            return;
        }
        case 0x0103: {
            pInfo->compressionIfd1 = readU16(entry + 8, byteOrder);
            return;
        }
        case 0x0201: {
            pInfo->thumbnailOffset = readU32(entry + 8, byteOrder);
            return;
        }
        case 0x0202: {
            pInfo->thumbnailLength = readU32(entry + 8, byteOrder);
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

    if (info->exifData.compressionIfd1 != 6) {
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

    if (param->unk_0x2C != 0 && param->unk_0x2C != 1 && param->unk_0x2C != 2) {
        return -1;
    }

    info->converterType = param->unk_0x2C;
    return 0;
}
