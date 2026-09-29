#include <private/es.h>
#include <private/nand.h>
#include <private/os.h>
#include <revolution/cnt.h>
#include <revolution/dvd.h>
#include <revolution/fa.h>
#include <revolution/nand.h>
#include <revolution/os.h>
#include <revolution/wad.h>

typedef union WADStreamHandle {
    DVDFileInfo dvd;
    NANDFileInfo nand;
    CNTFileInfoDVD contentDvd;
    CNTFileInfoNAND contentNand;
    FAFILE* fa;
    void* memoryBase;
} WADStreamHandle;

typedef struct __attribute__((aligned(32))) WADStream {
    WADLocation location;
    WADStreamHandle handle;
} WADStream;

typedef union WADTitleMetadata {
    ESTitleMetaHeader tmd;
    ESTitleId backupTitleId;
    u8 bytes[0x80];
} WADTitleMetadata;

typedef struct WADBroadOnHeader {
    u32 headerSize;
    u32 contentOffset;
    u32 certSize;
    u32 crlSize;
    u32 ticketSize;
    u32 titleMetaSize;
    u32 contentSize;
    u32 fileListSize;
} WADBroadOnHeader;

typedef struct WADUnpackInfo {
    s32 type;
    s32 headerInfo;
    u16 cidxMode;
    u8 reserved_0x0a[2];
    u32 size_0x0c;
    u32 offset_0x10;
    void* buffer_0x14;
    u32 size_0x18;
    u32 size_0x1c;
    u32 offset_0x20;
    void* buffer_0x24;
    u32 size_0x28;
    u32 size_0x2c;
    u32 offset_0x30;
    void* buffer_0x34;
    u32 size_0x38;
    u32 sectionSize;
    u32 sectionOffset;
    ESTitleMeta* titleMeta;
    u32 titleMetaSize;
    u32 contentSize;
    u32 contentOffset;
    u32 metaSize;
    u32 metaOffset;
    u32 fileListSize;
    u32 fileOffset;
    u32 fileCount;
    void* contentIndex;
    void* fileNames;
} WADUnpackInfo;

typedef struct WADFileHeader {
    u32 headerSize;
    u32 fileSize;
    u8 flags[3];
    char name[0x75];
} WADFileHeader;

typedef struct WADFileEntry {
    u32 fileSize;
    u8 flags[4];
    char name[0x40];
} WADFileEntry;

typedef struct WADBackupSignature {
    u8 header[0x40];
    u8 firstCertificate[0x180];
    u8 secondCertificate[0x180];
} WADBackupSignature;

typedef struct WADVerificationCertificateBundle {
    u8 caProduction[0x400];
    u8 msProduction[0x240];
    u8 caDevelopment[0x400];
    u8 msDevelopment[0x240];
    u8 firstCertificate[0x180];
    u8 secondCertificate[0x180];
} WADVerificationCertificateBundle;

typedef struct WADVerificationWorkspace {
    void* readBuffer[16];
    u8 digest[0x40];
    u8 hashContext[0xC0];
} WADVerificationWorkspace;

#pragma pack(push, 4)
typedef struct WADFileMetadataView {
    u8 reserved_0x00[0x18C];
    ESTitleId titleId;
    u8 reserved_0x194[0x48];
    u16 titleVersion;
} WADFileMetadataView;
#pragma pack(pop)

typedef struct __attribute__((aligned(32))) WADImportWorkspace {
    u8 transferId[0x20];
    WADFileHeader fileHeader;
    u8 wadHeader[0x80];
    WADUnpackInfo unpackInfo;
    WADStream stream;
} WADImportWorkspace;

typedef struct WADImportTransfer {
    s32 error;
    u32 chunkSize;
    BOOL ready[2];
    void* buffers[2];
    OSMutex mutex[2];
    OSCond waitCond[2];
    OSCond signalCond[2];
} WADImportTransfer;

typedef struct WADImportLoopArgs {
    s32 fd;
    u32 size;
    WADImportTransfer* transfer;
} WADImportLoopArgs;

typedef WADImportLoopArgs WADExportLoopArgs;

typedef struct WADHashThreadArgs {
    void* context;
    u32 size;
    WADImportTransfer* transfer;
} WADHashThreadArgs;

#define WAD_STREAM_ALIGNMENT 0x40
#define WAD_READ_ALIGNMENT 0x20
#define WAD_ALIGN32(value) (((value) + WAD_READ_ALIGNMENT - 1) & ~(WAD_READ_ALIGNMENT - 1))

static s32 WADOpenStream(WADLocation location, const char* path, WADStream* stream, u32, u32);
static s32 WADReadStream(WADStream* stream, void** buffer, u32 size, u32 offset);
static void WADCloseStream(WADStream* stream);
static s32 WADWriteStream(WADStream* stream, void* buffer, u32 size);
static s32 WADSeekStream(WADStream* stream, u32 offset, s32 origin);
static s32 WAD_815C2F44(WADHeader* header, s32* headerInfo);
static s32 _WADGetTitleVer(WADHeader* header, ESTitleId* titleId, u16* titleVersion, s32 type,
                           s32 headerInfo);
static s32 _WADUnpackIRD(WADHeader* header, WADStream* stream, WADUnpackInfo* info,
                         MEMAllocator* allocator, u32 offset, u32 mode);
static s32 _WADUnpackBroadOn(WADBroadOnHeader* header, WADStream* stream, WADUnpackInfo* info,
                             MEMAllocator* allocator, u32 offset, u32 mode);
static s32 _WADUnpackBackup(WADHeader* header, WADStream* stream, WADUnpackInfo* info,
                            MEMAllocator* allocator, u32 offset, u32 flags);
static s32 _WADUnpack(void* header, WADStream* stream, WADUnpackInfo* info, MEMAllocator* allocator,
                      u32 offset, u32 flags, u32 mode);
static s32 _WADHash(WADStream* stream, u32 offset, u32 size, void* context, void* buffer,
                    u32 chunkSize, void* secondBuffer, void* threadStack, u32 threadStackSize);
static void WAD_815C4A2C(WADImportTransfer* transfer, void* firstBuffer, void* secondBuffer,
                         u32 chunkSize);
s32 WADVerify(WADStream* stream, MEMAllocator* allocator, u32 offset, u32 size);
s32 _WADGetCidxCount(const ESContentMask* contentMask);
static s32 _WADGetCidx(const ESContentMask* contentMask, u32 contentNumber);
static s32 _WADGetTransferId(void* transferId);
static void* _WADMemAlloc(MEMAllocator* allocator, u32 size);
static void _WADMemFree(MEMAllocator* allocator, void* buffer);
static s32 _WADCanImportFile(const WADFileHeader* fileHeader, u32 transferId, const void* fileNames,
                             const void* transferIdBuffer);
static void _WADFreeMemory(WADUnpackInfo* info, MEMAllocator* allocator);
static s32 WAD_815BFFA8(WADImportLoopArgs* args);
u32 _WADIsTerminated(const char* text, u32 maxLength);

extern s32 ES_GetBoot2Version(u32* version);

s32 WADGetTitleVersionEx(char* path, ESTitleId* titleId, u16* titleVersion, WADLocation location, u32 offset) {
    BOOL streamOpened;
    WADStream stream ALIGN32;
    u8 headerBytes[0x20] ALIGN32;
    WADTitleMetadata metadata ALIGN32;
    s32 headerInfo;
    WADTitleMetadata* metadataBuffer = &metadata;
    WADHeader* headerBuffer = (WADHeader*)headerBytes;
    s32 result;
    u32 titleDataOffset;
    s32 type;

    streamOpened = FALSE;
    titleDataOffset = 0;
    if (path == 0) {
        result = -3000;
    } else if ((offset & 0x3F) != 0) {
        result = -3007;
    } else {
        result = WADOpenStream(location, path, &stream, 0, 0);
        streamOpened = TRUE;
        if (result == 0) {
            result = WADReadStream(&stream, (void**)&headerBuffer, 0x20, offset);
            if (result != 0x20) {
                result = -3005;
                goto done;
            }
            type = WAD_815C2F44(headerBuffer, &headerInfo);
            if (type == 0) {
                result = -3001;
                goto done;
            }
            if (((type == 2) && (headerBuffer->tmdSize == 0)) ||
                ((type == 1) && (headerBuffer->ticketSize == 0))) {
                result = -3002;
                if (headerInfo == 2) {
                    titleDataOffset = 0x60;
                } else {
                    goto done;
                }
            }

            if (titleDataOffset == 0) {
                result = _WADGetTitleVer(headerBuffer, 0, 0, type, headerInfo);
                if (result == 0) {
                    result = -3002;
                    goto done;
                }
                titleDataOffset = result + 0x180;
                result = WADReadStream(&stream, (void**)&metadataBuffer, 0x80,
                                       offset + titleDataOffset);
                if ((u32)result != 0x80) {
                    result = -3005;
                    goto done;
                }
                result = 0;
                if (titleId != 0) {
                    titleId[0] = metadataBuffer->tmd.titleId;
                }
                if (titleVersion != 0) {
                    *titleVersion = metadataBuffer->tmd.titleVersion;
                }
            } else {
                result = WADReadStream(&stream, (void**)&metadataBuffer, 0x20,
                                       offset + titleDataOffset);
                if (result != 0x20) {
                    result = -3005;
                    goto done;
                }
                result = 0;
                if (titleId != 0) {
                    *titleId = metadataBuffer->backupTitleId;
                }
            }
        }
    }

done:
    if (streamOpened) {
        WADCloseStream(&stream);
    }
    return result;
}

s32 WADCheckImport(ESTitleId titleId, u32 titleVersion) {
    u16 installedVersion;
    s32 result;

    if (__OSInIPL && (titleId == 0x0001000248414141ULL) && (titleVersion == 0xFF00)) {
        return 0;
    }

    result = WADGetInstalledVersion(titleId, &installedVersion);
    if (result == -3002) {
        return 1;
    }
    if (result == 0) {
        if (__OSInIPL) {
            if (titleVersion > installedVersion) {
                return 1;
            }
        } else if (titleVersion >= installedVersion) {
            return 1;
        }
    }
    return 0;
}

s32 WADGetInstalledVersion(ESTitleId titleId, u16* version) {
    u32 tmdSize;
    u32 installedVersion;
    ESTmdView tmdView __attribute__((aligned(32)));
    ESTmdView* viewBuffer = &tmdView;
    s32 result;

    if (version == 0) {
        return -3000;
    }
    if (titleId == 0x0000000100000001ULL) {
        result = ES_GetBoot2Version(&installedVersion);
        if (result == 0) {
            *version = installedVersion;
        }
        return result;
    }

    result = ES_GetTmdView(titleId, 0, &tmdSize);
    if (result == -106) {
        return -3002;
    }
    if (result != 0) {
        return result;
    }
    if (tmdSize > sizeof(ESTmdView)) {
        return -3000;
    }
    result = ES_GetTmdView(titleId, viewBuffer, &tmdSize);
    if (result == 0) {
        *version = viewBuffer->head.titleVersion;
    }
    return result;
}

s32 WADImportGetBlocks(char* path, MEMAllocator* allocator, WADLocation location, u32 offset, u32 flags,
                       WADBlocks* blocks, u32* fileListOut) {
    WADImportWorkspace workspace ALIGN32;
    void* wadHeader = workspace.wadHeader;
    s32 result;
    u32 fileOffset;
    void* allocatedFiles;
    BOOL streamOpened;
    u32 transferId;
    u32 contentCount;
    ESTitleMeta* titleMeta;
    ESContentMeta* contentMeta;
    u32 index;

    streamOpened = FALSE;
    fileOffset = 0;
    allocatedFiles = 0;
    memset(&workspace.unpackInfo, 0, sizeof(WADUnpackInfo));
    if (fileListOut != 0) {
        *fileListOut = 0;
    }
    if ((allocator == 0) || (allocator->heap == 0) || (path == 0) || (blocks == 0)) {
        result = -3000;
    } else if ((offset & 0x3F) != 0) {
        result = -3007;
    } else {
        result = WADOpenStream(location, path, &workspace.stream, 0, 0);
        streamOpened = TRUE;
        if (result == 0) {
            result = WADReadStream(&workspace.stream, &wadHeader, 0x80, offset);
            if (result != 0x80) {
                result = -3005;
            } else {
                result = _WADUnpack(wadHeader, &workspace.stream, &workspace.unpackInfo, allocator,
                                    offset, flags & ~4, 1);
                if (result == 0) {
                    memset(blocks, 0, sizeof(WADBlocks));
                    titleMeta = workspace.unpackInfo.titleMeta;
                    if (titleMeta != 0) {
                        if ((flags & 4) == 0) {
                            blocks->unkBlocks += (workspace.unpackInfo.sectionSize + 0x3FFF) >> 14;
                            blocks->unkInodes = 1;
                        }
                        if (workspace.unpackInfo.cidxMode < 1) {
                            contentCount = titleMeta->head.numContents;
                        } else {
                            contentCount = _WADGetCidxCount(workspace.unpackInfo.contentIndex);
                            if (contentCount > titleMeta->head.numContents) {
                                result = -3001;
                                goto cleanup;
                            }
                        }
                        contentMeta = titleMeta->contents;
                        for (index = 0; index < contentCount; index++) {
                            if (workspace.unpackInfo.cidxMode >= 1) {
                                s32 selectedIndex = _WADGetCidx(workspace.unpackInfo.contentIndex, index);
                                if ((selectedIndex < 0) ||
                                    (titleMeta->head.numContents <= selectedIndex)) {
                                    result = -3001;
                                    goto cleanup;
                                }
                                contentMeta = titleMeta->contents + selectedIndex;
                                result = 0;
                            }
                            if ((contentMeta->type & 0x8000) == 0) {
                                blocks->privateInodes++;
                                blocks->privateBlocks += ((u32)contentMeta->size + 0x3FFF) >> 14;
                            } else {
                                blocks->sharedInodes++;
                                blocks->sharedBlocks += ((u32)contentMeta->size + 0x3FFF) >> 14;
                            }
                            contentMeta++;
                        }
                    }
                    if ((workspace.unpackInfo.fileListSize != 0) &&
                        (workspace.unpackInfo.fileCount != 0)) {
                        transferId = _WADGetTransferId(workspace.transferId);
                        if ((fileListOut == 0) ||
                            ((allocatedFiles = _WADMemAlloc(allocator,
                                                           workspace.unpackInfo.fileCount * 0x48)) != 0)) {
                            fileOffset = workspace.unpackInfo.fileOffset;
                            for (index = 0; index < workspace.unpackInfo.fileCount; index++) {
                                WADFileHeader* fileHeader = &workspace.fileHeader;
                                result = WADReadStream(&workspace.stream, (void**)&fileHeader, 0x80,
                                                       offset + fileOffset);
                                if (result != 0x80) {
                                    result = -3005;
                                    goto cleanup;
                                }
                                result = 0;
                                if (_WADCanImportFile(fileHeader, transferId,
                                                      workspace.unpackInfo.fileNames,
                                                      workspace.transferId) != 0) {
                                    blocks->fileBlocks += (fileHeader->fileSize + 0x3FFF) >> 14;
                                    if (fileListOut != 0) {
                                        WADFileEntry* fileEntries = allocatedFiles;
                                        fileEntries += blocks->fileInodes;
                                        fileEntries->fileSize = fileHeader->fileSize;
                                        fileEntries->flags[0] = fileHeader->flags[0];
                                        fileEntries->flags[1] = fileHeader->flags[1];
                                        fileEntries->flags[2] = fileHeader->flags[2];
                                        fileEntries->flags[3] = 0;
                                        strncpy(fileEntries->name, fileHeader->name, 0x40);
                                    }
                                    blocks->fileInodes++;
                                }
                                fileOffset = ((fileOffset + WAD_STREAM_ALIGNMENT - 1) &
                                              ~(WAD_STREAM_ALIGNMENT - 1)) + fileHeader->fileSize;
                                fileOffset = (fileOffset + WAD_STREAM_ALIGNMENT - 1) &
                                             ~(WAD_STREAM_ALIGNMENT - 1);
                            }
                            if (fileListOut != 0) {
                                *fileListOut = (u32)allocatedFiles;
                            }
                        } else {
                            result = -3003;
                        }
                    }
                }
            }
        }
    }

cleanup:
    _WADFreeMemory(&workspace.unpackInfo, allocator);
    if ((fileListOut != 0) && (result != 0)) {
        if (allocatedFiles != 0) {
            _WADMemFree(allocator, allocatedFiles);
        }
        *fileListOut = 0;
    }
    if (streamOpened) {
        WADCloseStream(&workspace.stream);
    }
    return result;
}

static s32 WAD_815BFFA8(WADImportLoopArgs* args) {
    WADImportTransfer* transfer = args->transfer;
    u32 remaining = args->size;
    s32 result = 0;
    u32 bufferIndex = 0;

    while ((remaining != 0) && (result == 0)) {
        u32 size = remaining;
        OSMutex* mutex;

        if (transfer->chunkSize < remaining) {
            size = transfer->chunkSize;
        }
        mutex = &transfer->mutex[bufferIndex];
        OSLockMutex(mutex);
        while (transfer->ready[bufferIndex] == 0) {
            OSWaitCond(&transfer->waitCond[bufferIndex], mutex);
        }
        result = ES_ImportContentData(args->fd, transfer->buffers[bufferIndex], size);
        transfer->ready[bufferIndex] = 0;
        if (result != 0) {
            transfer->error = 1;
        }
        OSUnlockMutex(mutex);
        OSSignalCond(&transfer->signalCond[bufferIndex]);
        remaining -= size;
        bufferIndex ^= 1;
    }
    return result;
}

s32 WAD_815C1288(WADExportLoopArgs* args) {
    ESFd fd = args->fd;
    s32 result = 0;
    u32 remaining = args->size;
    u32 bufferIndex = 0;
    WADImportTransfer* transfer = args->transfer;

    while ((remaining != 0) && (result == 0)) {
        u32 size = remaining;
        OSMutex* mutex;

        if (remaining > transfer->chunkSize) {
            size = transfer->chunkSize;
        }
        mutex = &transfer->mutex[bufferIndex];
        OSLockMutex(mutex);
        while (transfer->ready[bufferIndex] != 0) {
            OSWaitCond(&transfer->waitCond[bufferIndex], mutex);
        }
        result = ES_ExportContentData(fd, transfer->buffers[bufferIndex], size);
        transfer->ready[bufferIndex] = size;
        if (result != 0) {
            transfer->error = 1;
        }
        OSUnlockMutex(mutex);
        OSSignalCond(&transfer->signalCond[bufferIndex]);
        remaining -= size;
        bufferIndex ^= 1;
    }
    return result;
}

s32 _WADGetCidxCount(const ESContentMask* contentMask) {
    s32 count = 0;
    u32 bitIndex = 0;
    u32 groupIndex;

    for (groupIndex = 0; groupIndex < 0x80; groupIndex++) {
        if ((contentMask->data[bitIndex >> 3] & (1 << (bitIndex & 7))) != 0) {
            count++;
        }
        if ((contentMask->data[(bitIndex + 1) >> 3] & (1 << ((bitIndex + 1) & 7))) != 0) {
            count++;
        }
        if ((contentMask->data[(bitIndex + 2) >> 3] & (1 << ((bitIndex + 2) & 7))) != 0) {
            count++;
        }
        if ((contentMask->data[(bitIndex + 3) >> 3] & (1 << ((bitIndex + 3) & 7))) != 0) {
            count++;
        }
        bitIndex += 4;
    }
    return count;
}

static s32 _WADGetCidx(const ESContentMask* contentMask, u32 contentNumber) {
    u32 remaining = contentNumber + 1;
    u32 bitIndex = 0;
    u32 groupIndex;
    u32 nextIndex;

    for (groupIndex = 0; groupIndex < 0x80; groupIndex++) {
        if ((contentMask->data[(s32)bitIndex >> 3] & (1 << (bitIndex & 7))) != 0) {
            remaining--;
        }
        if (remaining == 0) {
            return bitIndex;
        }
        nextIndex = ++bitIndex;
        if ((contentMask->data[(s32)nextIndex >> 3] & (1 << (nextIndex & 7))) != 0) {
            remaining--;
        }
        if (remaining == 0) {
            return nextIndex;
        }
        nextIndex = ++bitIndex;
        if ((contentMask->data[(s32)nextIndex >> 3] & (1 << (nextIndex & 7))) != 0) {
            remaining--;
        }
        if (remaining == 0) {
            return nextIndex;
        }
        nextIndex = ++bitIndex;
        if ((contentMask->data[(s32)nextIndex >> 3] & (1 << (nextIndex & 7))) != 0) {
            remaining--;
        }
        if (remaining == 0) {
            return nextIndex;
        }
        bitIndex++;
    }
    return -1;
}

#pragma dont_inline on
static s32 _WADGetTransferId(void* transferId) {
    NANDFileInfo fileInfo;
    BOOL valid;
    s32 result;

    valid = FALSE;
    result = NANDPrivateOpen("/shared2/succession/transfer.id", &fileInfo, 1);
    if (result == 0) {
        valid = TRUE;
        result = NANDRead(&fileInfo, transferId, 0x20);
        if (result != 0x20) {
            valid = FALSE;
        }
        NANDClose(&fileInfo);
    }
    return valid;
}

static s32 _WADCanImportFile(const WADFileHeader* fileHeader, u32 transferId, const void* fileNames,
                             const void* transferIdBuffer) {
    s32 result;

    result = strncmp(fileHeader->name, "nocopy", 6);
    if (result == 0) {
        return FALSE;
    }
    result = strncmp(fileHeader->name, "notransfer", 10);
    if (result == 0) {
        if ((transferId == 0) || (fileNames == 0) || (transferIdBuffer == 0)) {
            return FALSE;
        }
        result = memcmp(fileNames, transferIdBuffer, 6);
        return result == 0;
    }
    return TRUE;
}
#pragma dont_inline reset

#pragma dont_inline on
static void* _WADMemAlloc(MEMAllocator* allocator, u32 size) {
    s32 allocationKind;
    u32 heapType;
    void* buffer;

    if ((allocator == 0) || (allocator->heap == 0)) {
        return 0;
    }
    heapType = ((MEMiHeapHead*)allocator->heap)->magic;
    if (heapType == 0x46524D48) {
        allocationKind = 1;
    } else {
        if (heapType < 0x46524D48) {
            if (heapType == 0x45585048) {
                allocationKind = 0;
                goto allocate;
            }
        } else if (heapType == 0x554E5448) {
            allocationKind = 2;
            goto allocate;
        }
        allocationKind = 3;
    }

allocate:
    if (allocationKind == 1) {
        return MEMAllocFromFrmHeapEx(allocator->heap, size, 0x40);
    }
    if (allocationKind == 0) {
        return MEMAllocFromExpHeapEx(allocator->heap, size, 0x40);
    }
    buffer = MEMAllocFromAllocator(allocator, size);
    if (((u32)buffer & 0x3F) != 0) {
        OSReport("%s: Memory Allocator must return 64B aligned memBlocks\n", "_WADMemAlloc");
        MEMFreeToAllocator(allocator, buffer);
        return 0;
    }
    return buffer;
}

static void _WADMemFree(MEMAllocator* allocator, void* buffer) {
    if (allocator != 0) {
        if (allocator->heap != 0) {
            if (buffer != 0) {
                MEMFreeToAllocator(allocator, buffer);
            }
        }
    }
}
#pragma dont_inline reset

static void _WADFreeMemory(WADUnpackInfo* info, MEMAllocator* allocator) {
    if ((info->size_0x18 != 0) && (info->buffer_0x14 != 0)) {
        _WADMemFree(allocator, info->buffer_0x14);
        info->buffer_0x14 = 0;
    }
    if ((info->size_0x28 != 0) && (info->buffer_0x24 != 0)) {
        _WADMemFree(allocator, info->buffer_0x24);
        info->buffer_0x24 = 0;
    }
    if ((info->size_0x38 != 0) && (info->buffer_0x34 != 0)) {
        _WADMemFree(allocator, info->buffer_0x34);
        info->buffer_0x34 = 0;
    }
    if ((info->titleMetaSize != 0) && (info->titleMeta != 0)) {
        _WADMemFree(allocator, info->titleMeta);
        info->titleMeta = 0;
    }
}

typedef struct WADContentPath {
    const char* name;
    void* handle;
} WADContentPath;

typedef union WADFileInfoView {
    FAFileInfo info;
    struct {
        u32 unknown;
        u32 fileSize;
        u8 reserved[0x18];
    } fields;
} WADFileInfoView;

static s32 WADOpenStream(WADLocation location, const char* path, WADStream* stream, u32 write,
                         u32 offset) {
    s32 result;

    stream->location = location;
    if (location == WAD_LOCATION_SD_CARD) {
        if (write == 0) {
            stream->handle.fa = FAFopen(path, "r");
        } else {
            stream->handle.fa = FAFopen(path, "r+");
            if (stream->handle.fa == 0) {
                stream->handle.fa = FACreate(path, 0);
            }
            if (stream->handle.fa == 0) {
                return -3004;
            }
            if ((offset != 0) && (WADSeekStream(stream, offset, 0) != offset)) {
                return -3004;
            }
        }
        return stream->handle.fa == 0 ? -3004 : 0;
    }
    if (location < WAD_LOCATION_SD_CARD) {
        if (location == WAD_LOCATION_DVD) {
            if (write != 0) {
                return -3004;
            }
            return DVDOpen(path, &stream->handle.dvd) ? 0 : -3004;
        }
        if (location == WAD_LOCATION_NAND) {
            if (write == 0) {
                return NANDPrivateOpen(path, &stream->handle.nand, 1) == 0 ? 0 : -3004;
            }
            result = NANDPrivateOpen(path, &stream->handle.nand, 3);
            if (result == -12) {
                result = NANDPrivateCreate(path, 0x3F, 0);
                if (result != 0) {
                    return -3004;
                }
                result = NANDPrivateOpen(path, &stream->handle.nand, 3);
            }
            if (result != 0) {
                return -3004;
            }
            result = NANDSeek(&stream->handle.nand, offset, 0);
            if (result == -8) {
                u8 zeroes[0x4000] ALIGN32;
                u32 fileSize;

                fileSize = NANDSeek(&stream->handle.nand, 0, 2);
                if (offset <= fileSize) {
                    return -3004;
                }
                memset(zeroes, 0, sizeof(zeroes));
                fileSize = offset - fileSize;
                while (fileSize != 0) {
                    u32 writeSize = fileSize;
                    if (writeSize > sizeof(zeroes)) {
                        writeSize = sizeof(zeroes);
                    }
                    if (NANDWrite(&stream->handle.nand, zeroes, writeSize) != writeSize) {
                        return -3004;
                    }
                    fileSize -= writeSize;
                }
                result = NANDSeek(&stream->handle.nand, offset, 0);
            }
            return result == offset ? 0 : -3004;
        }
        if ((s32)location >= 0) {
            if ((((u32)path + offset) & 0x3F) != 0) {
                return -3007;
            }
            stream->handle.memoryBase = (void*)((u32)path + offset);
            return 0;
        }
    } else if (location == WAD_LOCATION_CNT_NAND) {
        WADContentPath* contentPath = (WADContentPath*)path;
        if (write != 0) {
            return -3004;
        }
        return contentOpenNAND(contentPath->handle, contentPath->name,
                               &stream->handle.contentNand) == 0
                   ? 0
                   : -3004;
    } else if (location < WAD_LOCATION_CNT_NAND) {
        WADContentPath* contentPath = (WADContentPath*)path;
        if (write != 0) {
            return -3004;
        }
        return contentOpenDVD(contentPath->handle, contentPath->name,
                              &stream->handle.contentDvd) == 0
                   ? 0
                   : -3004;
    }
    return -3000;
}

static s32 WADReadStream(WADStream* stream, void** buffer, u32 size, u32 offset) {
    s32 result;
    u32 alignedSize;

    if ((s32)size <= 0) {
        result = 0;
    } else if ((stream == 0) || (buffer == 0)) {
        result = -3000;
    } else {
        alignedSize = (size + WAD_READ_ALIGNMENT - 1) & ~(WAD_READ_ALIGNMENT - 1);
        if (size == alignedSize) {
            if (stream->location == WAD_LOCATION_SD_CARD) {
                if (stream->handle.fa == 0) {
                    result = -3000;
                } else {
                    result = FAFseek(stream->handle.fa, offset, 0);
                    if (result == 0) {
                        result = FAFread(*buffer, 1, size, stream->handle.fa);
                    }
                }
            } else if (stream->location < WAD_LOCATION_SD_CARD) {
                if (stream->location == WAD_LOCATION_DVD) {
                    return DVDReadPrio(&stream->handle.dvd, *buffer, alignedSize, offset, 2);
                }
                if (stream->location > WAD_LOCATION_DVD) {
                    result = NANDSeek(&stream->handle.nand, offset, 0);
                    if (result < 0) {
                        return result;
                    }
                    return NANDRead(&stream->handle.nand, *buffer, alignedSize);
                }
                if (stream->location >= 0) {
                    memcpy(*buffer, (u8*)stream->handle.memoryBase + offset, size);
                    return size;
                }
                result = -3000;
            } else if (stream->location == WAD_LOCATION_CNT_NAND) {
                return contentReadNAND(&stream->handle.contentNand, *buffer, alignedSize, offset);
            } else if (stream->location < WAD_LOCATION_CNT_NAND) {
                return contentReadDVD(&stream->handle.contentDvd, *buffer, alignedSize, offset);
            } else {
                result = -3000;
            }
        } else {
            result = -3000;
        }
    }
    return result;
}

static void WADCloseStream(WADStream* stream) {
    if (stream == 0) {
        return;
    }
    if (stream->location == WAD_LOCATION_SD_CARD) {
        if (stream->handle.fa == 0) {
            return;
        }
        FAFclose(stream->handle.fa);
        return;
    }
    if (stream->location < WAD_LOCATION_SD_CARD) {
        if (stream->location == WAD_LOCATION_DVD) {
            DVDClose(&stream->handle.dvd);
            return;
        }
        if (stream->location < WAD_LOCATION_DVD) {
            return;
        }
        if (stream->location > WAD_LOCATION_DVD) {
            NANDClose(&stream->handle.nand);
        }
        return;
    }
    if (stream->location == WAD_LOCATION_CNT_NAND) {
        contentCloseNAND(&stream->handle.contentNand);
        return;
    }
    if (stream->location >= WAD_LOCATION_CNT_NAND) {
        return;
    }
    contentCloseDVD(&stream->handle.contentDvd);
}

static s32 WADWriteStream(WADStream* stream, void* buffer, u32 size) {
    if ((stream == 0) || (buffer == 0)) {
        return -3000;
    }
    if (stream->location == WAD_LOCATION_NAND) {
        return NANDWrite(&stream->handle.nand, buffer, size);
    }
    if (stream->location == WAD_LOCATION_DVD - 1) {
        memcpy(stream->handle.memoryBase, buffer, size);
        return size;
    }
    if ((stream->location > WAD_LOCATION_NAND) &&
        (stream->location < WAD_LOCATION_CNT_DVD)) {
        if (stream->handle.fa == 0) {
            return -3000;
        }
        return FAFwrite(buffer, 1, size, stream->handle.fa);
    }
    return -3000;
}

static s32 WADSeekStream(WADStream* stream, u32 offset, s32 origin) {
    s32 result;

    if ((stream == 0) || (origin < 0) || (origin > 2)) {
        return -3000;
    }
    if (stream->location == WAD_LOCATION_SD_CARD) {
        WADFileInfoView info;
        if (stream->handle.fa == 0) {
            return -3000;
        }
        result = FAFseek(stream->handle.fa, offset, origin);
        if ((result == 0) && (FAFinfo(stream->handle.fa, &info.info) == 0)) {
            result = info.fields.fileSize;
        }
        return result;
    }
    if (stream->location < WAD_LOCATION_SD_CARD) {
        if (stream->location > WAD_LOCATION_DVD) {
            return NANDSeek(&stream->handle.nand, offset, origin);
        }
    } else if (stream->location == WAD_LOCATION_CNT_NAND) {
        return contentSeekNAND(&stream->handle.contentNand, offset, origin);
    } else if (stream->location < WAD_LOCATION_CNT_NAND) {
        return contentSeekDVD(&stream->handle.contentDvd, offset, origin);
    }
    return -3000;
}

static s32 _WADGetTitleVer(WADHeader* header, ESTitleId* titleId, u16* titleVersion, s32 type,
                           s32 headerInfo) {
    s32 titleDataOffset = 0;

    if (type == 2) {
        if (header->tmdSize == 0) {
            return 0;
        }
        if ((headerInfo == 0) || (headerInfo == 1) || (headerInfo == 3)) {
            titleDataOffset = header->wadVersion == 1 ? 0x80 : 0x40;
            titleDataOffset += (header->certSize + 0x3F) & ~0x3F;
            titleDataOffset += (header->crlSize + 0x3F) & ~0x3F;
            titleDataOffset += (header->ticketSize + 0x3F) & ~0x3F;
        } else if (headerInfo == 2) {
            titleDataOffset = 0x80;
        }
    } else if (type == 1) {
        if (header->ticketSize == 0) {
            return 0;
        }
        titleDataOffset = header->certSize + 0x20;
        titleDataOffset += header->crlSize;
    }

    {
        WADFileMetadataView* metadata = (WADFileMetadataView*)((u8*)header + titleDataOffset);
        if (titleId != 0) {
            *titleId = metadata->titleId;
        }
        if (titleVersion != 0) {
            *titleVersion = metadata->titleVersion;
        }
    }
    return titleDataOffset;
}

static s32 WAD_815C2F44(WADHeader* header, s32* headerInfo) {
    u8 firstTypeByte;
    u8 secondTypeByte;

    if (header == 0) {
        return 0;
    }
    firstTypeByte = header->wadType[0];
    secondTypeByte = header->wadType[1];
    if ((firstTypeByte == 'I') && (secondTypeByte == 's')) {
        if (headerInfo != 0) {
            *headerInfo = 0;
        }
        return 2;
    }
    if ((firstTypeByte == 'X') && (secondTypeByte == 'p')) {
        if (headerInfo != 0) {
            *headerInfo = 1;
        }
        return 2;
    }
    if ((firstTypeByte == 'B') && (secondTypeByte == 'k')) {
        if (headerInfo != 0) {
            *headerInfo = 2;
        }
        return 2;
    }
    if ((firstTypeByte == 'i') && (secondTypeByte == 'b')) {
        if (headerInfo != 0) {
            *headerInfo = 3;
        }
        return 2;
    }
    if (header->hdrSize == 0x20) {
        if (headerInfo != 0) {
            *headerInfo = 0;
        }
        return 1;
    }
    return 0;
}

#pragma dont_inline on
static s32 _WADUnpack(void* header, WADStream* stream, WADUnpackInfo* info, MEMAllocator* allocator,
                      u32 offset, u32 flags, u32 mode) {
    s32 result;
    s32 type;

    if ((header == 0) || (info == 0)) {
        result = -3000;
    } else {
        memset(info, 0, 0x70);
        type = WAD_815C2F44(header, &info->headerInfo);
        info->type = type;
        if (type == 2) {
            if (info->headerInfo != 2) {
                result = _WADUnpackIRD(header, stream, info, allocator, offset, mode);
            } else {
                result = _WADUnpackBackup(header, stream, info, allocator, offset, flags);
            }
        } else if (type == 1) {
            result = _WADUnpackBroadOn((WADBroadOnHeader*)header, stream, info, allocator, offset,
                                       mode);
        } else {
            result = -3001;
        }
    }
    return result;
}
#pragma dont_inline reset

static s32 _WADUnpackIRD(WADHeader* header, WADStream* stream, WADUnpackInfo* info,
                         MEMAllocator* allocator, u32 offset, u32 mode) {
    u16 wadVersion = header->wadVersion;
    s32 sectionSize;
    u32 sectionOffset;
    s32 alignedSize;
    s32 bytesRead;

    if ((wadVersion != 0) && (wadVersion != 1)) {
        return -3001;
    }
    if ((header->ticketSize == 0) && (header->tmdSize == 0)) {
        return -3001;
    }
    if ((wadVersion == 0) && (header->hdrSize != 0x20)) {
        return -3001;
    }
    if ((wadVersion == 1) && (header->hdrSize != 0x60)) {
        return -3001;
    }

    info->cidxMode = wadVersion;
    if (wadVersion >= 1) {
        info->contentIndex = &((WADBackupHeader*)header)->cidx;
    }
    sectionOffset = (header->hdrSize + 0x3F) & ~0x3F;

    sectionSize = header->certSize;
    if (sectionSize != 0) {
        info->size_0x0c = sectionSize;
        info->offset_0x10 = sectionOffset;
        if (mode == 0) {
            alignedSize = WAD_ALIGN32(sectionSize);
            info->buffer_0x14 = _WADMemAlloc(allocator, alignedSize);
            if (info->buffer_0x14 == 0) {
                return -3003;
            }
            info->size_0x18 = 1;
            bytesRead = WADReadStream(stream, &info->buffer_0x14, alignedSize,
                                      offset + info->offset_0x10);
            if (bytesRead != alignedSize) {
                return -3005;
            }
        }
        sectionOffset += (header->certSize + 0x3F) & ~0x3F;
    }
    sectionSize = header->crlSize;
    if (sectionSize != 0) {
        info->size_0x1c = sectionSize;
        info->offset_0x20 = sectionOffset;
        if (mode == 0) {
            alignedSize = WAD_ALIGN32(sectionSize);
            info->buffer_0x24 = _WADMemAlloc(allocator, alignedSize);
            if (info->buffer_0x24 == 0) {
                return -3003;
            }
            info->size_0x28 = 1;
            bytesRead = WADReadStream(stream, &info->buffer_0x24, alignedSize,
                                      offset + info->offset_0x20);
            if (bytesRead != alignedSize) {
                return -3005;
            }
        }
        sectionOffset += (header->crlSize + 0x3F) & ~0x3F;
    }
    sectionSize = header->ticketSize;
    if (sectionSize != 0) {
        info->size_0x2c = sectionSize;
        info->offset_0x30 = sectionOffset;
        if (mode == 0) {
            alignedSize = WAD_ALIGN32(sectionSize);
            info->buffer_0x34 = _WADMemAlloc(allocator, alignedSize);
            if (info->buffer_0x34 == 0) {
                return -3003;
            }
            info->size_0x38 = 1;
            bytesRead = WADReadStream(stream, &info->buffer_0x34, alignedSize,
                                      offset + info->offset_0x30);
            if (bytesRead != alignedSize) {
                return -3005;
            }
        }
        sectionOffset += (header->ticketSize + 0x3F) & ~0x3F;
    }
    sectionSize = header->tmdSize;
    if (sectionSize != 0) {
        info->sectionSize = sectionSize;
        info->sectionOffset = sectionOffset;
        alignedSize = WAD_ALIGN32(sectionSize);
        info->titleMeta = _WADMemAlloc(allocator, alignedSize);
        if (info->titleMeta == 0) {
            return -3003;
        }
        info->titleMetaSize = 1;
        bytesRead = WADReadStream(stream, (void**)&info->titleMeta, alignedSize,
                                  offset + info->sectionOffset);
        if (bytesRead != alignedSize) {
            return -3005;
        }
        sectionOffset += (header->tmdSize + 0x3F) & ~0x3F;
    }
    if (header->contentSize != 0) {
        info->contentSize = header->contentSize;
        info->contentOffset = sectionOffset;
        sectionOffset += (header->contentSize + 0x3F) & ~0x3F;
    }
    if (header->metaSize != 0) {
        info->metaSize = header->metaSize;
        info->metaOffset = sectionOffset;
    }
    return 0;
}

static s32 _WADUnpackBroadOn(WADBroadOnHeader* header, WADStream* stream, WADUnpackInfo* info,
                             MEMAllocator* allocator, u32 offset, u32 mode) {
    u32 currentOffset;
    s32 sectionSize;
    s32 alignedSize;
    s32 bytesRead;

    if ((header->crlSize == 0) && (header->ticketSize == 0)) {
        return -3001;
    }

    currentOffset = header->headerSize;
    sectionSize = header->certSize;
    if (sectionSize != 0) {
        info->size_0x0c = sectionSize;
        info->offset_0x10 = currentOffset;
        if (mode == 0) {
            alignedSize = WAD_ALIGN32(sectionSize);
            info->buffer_0x14 = _WADMemAlloc(allocator, alignedSize);
            if (info->buffer_0x14 == 0) {
                return -3003;
            }
            info->size_0x18 = 1;
            bytesRead = WADReadStream(stream, &info->buffer_0x14, alignedSize,
                                      offset + info->offset_0x10);
            if (bytesRead != alignedSize) {
                return -3005;
            }
        }
        currentOffset += header->certSize;
    }

    sectionSize = header->crlSize;
    if (sectionSize != 0) {
        info->size_0x2c = sectionSize;
        info->offset_0x30 = currentOffset;
        if (mode == 0) {
            alignedSize = WAD_ALIGN32(sectionSize);
            info->buffer_0x34 = _WADMemAlloc(allocator, alignedSize);
            if (info->buffer_0x34 == 0) {
                return -3003;
            }
            info->size_0x38 = 1;
            bytesRead = WADReadStream(stream, &info->buffer_0x34, alignedSize,
                                      offset + info->offset_0x30);
            if (bytesRead != alignedSize) {
                return -3005;
            }
        }
        currentOffset += header->crlSize;
    }

    sectionSize = header->ticketSize;
    if (sectionSize != 0) {
        info->sectionSize = sectionSize;
        info->sectionOffset = currentOffset;
        alignedSize = WAD_ALIGN32(sectionSize);
        info->titleMeta = _WADMemAlloc(allocator, alignedSize);
        if (info->titleMeta == 0) {
            return -3003;
        }
        info->titleMetaSize = 1;
        bytesRead = WADReadStream(stream, (void**)&info->titleMeta, alignedSize,
                                  offset + info->sectionOffset);
        if (bytesRead != alignedSize) {
            return -3005;
        }
        currentOffset += header->ticketSize;
    }

    sectionSize = header->titleMetaSize;
    if (sectionSize != 0) {
        info->metaSize = sectionSize;
        info->metaOffset = currentOffset;
        currentOffset += header->titleMetaSize;
    }

    sectionSize = header->fileListSize;
    if (sectionSize != 0) {
        info->size_0x1c = sectionSize;
        info->offset_0x20 = currentOffset;
        if (mode == 0) {
            alignedSize = WAD_ALIGN32(sectionSize);
            info->buffer_0x24 = _WADMemAlloc(allocator, alignedSize);
            if (info->buffer_0x24 == 0) {
                return -3003;
            }
            info->size_0x28 = 1;
            bytesRead = WADReadStream(stream, &info->buffer_0x24, alignedSize,
                                      offset + info->offset_0x20);
            if (bytesRead != alignedSize) {
                return -3005;
            }
        }
    }

    info->contentOffset = header->contentOffset;
    return 0;
}

static s32 _WADUnpackBackup(WADHeader* header, WADStream* stream, WADUnpackInfo* info,
                            MEMAllocator* allocator, u32 offset, u32 flags) {
    WADBackupHeader* backupHeader = (WADBackupHeader*)header;
    ESDeviceId currentDeviceId;
    s32 result;
    u32 sectionOffset;
    u32 alignedSize;

    if (backupHeader->wadVersion != 1) {
        return -3001;
    }
    if (backupHeader->hdrSize != sizeof(WADBackupHeader)) {
        return -3001;
    }
    if (backupHeader->contentSize != 0) {
        result = ES_GetDeviceId(&currentDeviceId);
        if (result != 0) {
            return result;
        }
        if (currentDeviceId != backupHeader->deviceId) {
            return -3008;
        }
    }

    info->cidxMode = backupHeader->wadVersion;
    if (backupHeader->wadVersion >= 1) {
        info->contentIndex = &backupHeader->cidx;
    }
    info->fileNames = backupHeader->deviceMac;
    sectionOffset = (backupHeader->hdrSize + WAD_STREAM_ALIGNMENT - 1) &
                    ~(WAD_STREAM_ALIGNMENT - 1);

    if (backupHeader->tmdSize != 0) {
        if ((flags & 4) == 0) {
            info->sectionSize = backupHeader->tmdSize;
            info->sectionOffset = sectionOffset;
            alignedSize = WAD_ALIGN32(backupHeader->tmdSize);
            info->titleMeta = _WADMemAlloc(allocator, alignedSize);
            if (info->titleMeta == 0) {
                return -3003;
            }
            info->titleMetaSize = 1;
            result = WADReadStream(stream, (void**)&info->titleMeta, alignedSize,
                                   offset + info->sectionOffset);
            if (result != alignedSize) {
                return -3005;
            }
            result = 0;
        }
        sectionOffset += (backupHeader->tmdSize + WAD_STREAM_ALIGNMENT - 1) &
                         ~(WAD_STREAM_ALIGNMENT - 1);
        if ((flags & 2) != 0) {
            return 0;
        }
    }

    if (backupHeader->contentSize != 0) {
        info->contentSize = backupHeader->contentSize;
        info->contentOffset = sectionOffset;
        sectionOffset += (backupHeader->contentSize + WAD_STREAM_ALIGNMENT - 1) &
                         ~(WAD_STREAM_ALIGNMENT - 1);
    }
    if (backupHeader->fileSize != 0) {
        info->fileListSize = backupHeader->fileSize;
        info->fileOffset = sectionOffset;
        info->fileCount = backupHeader->numFiles;
        if ((flags & 1) == 0) {
            result = WADVerify(stream, allocator, offset, backupHeader->backupAreaLen);
            if (result != 0) {
                return result;
            }
        }
    }
    return 0;
}

typedef struct WADSaveDataRecord {
    u8 reserved_0x00[0x4E];
    char fileName[8];
    u8 reserved_0x56[2];
    char bannerName[8];
    u8 reserved_0x60[0x12];
    char saveName[8];
    u8 reserved_0x7A[0x14];
    char titleName[8];
    u8 reserved_0x96[0x11E];
    char description[0x11];
    char subtitle[0x11];
    u8 reserved_0x1D6[0x8BE];
} WADSaveDataRecord;

typedef struct WADSaveDataFile {
    u8 reserved_0x00[8];
    WADSaveDataRecord primary[3];
    u8 reserved_0x1FC4[0x44];
    WADSaveDataRecord secondary[3];
} WADSaveDataFile;

s32 WADCheckSavedataZD(const WADSaveDataFile* saveData) {
    s32 result = FALSE;
    u32 index;
    const WADSaveDataRecord* record;

    record = saveData->primary;
    index = 0;
    do {
        if (!_WADIsTerminated(record->fileName, 8)) {
            goto done;
        }
        if (!_WADIsTerminated(record->bannerName, 8)) {
            goto done;
        }
        if (!_WADIsTerminated(record->saveName, 8)) {
            goto done;
        }
        if (!_WADIsTerminated(record->titleName, 8)) {
            goto done;
        }
        if (!_WADIsTerminated(record->description, 0x11)) {
            goto done;
        }
        if (!_WADIsTerminated(record->subtitle, 0x11)) {
            goto done;
        }
        index++;
        record++;
    } while (index < 3);
    record = saveData->secondary;
    for (index = 0; index < 3; index++, record++) {
        if (!_WADIsTerminated(record->fileName, 8)) {
            goto done;
        }
        if (!_WADIsTerminated(record->bannerName, 8)) {
            goto done;
        }
        if (!_WADIsTerminated(record->saveName, 8)) {
            goto done;
        }
        if (!_WADIsTerminated(record->titleName, 8)) {
            goto done;
        }
        if (!_WADIsTerminated(record->description, 0x11)) {
            goto done;
        }
        if (!_WADIsTerminated(record->subtitle, 0x11)) {
            goto done;
        }
    }
    result = TRUE;
done:
    return result;
}

extern const u8 ca_ppki[];
extern const u8 ms_ppki[];
extern const u8 ca_dpki[];
extern const u8 ms_dpki[];
extern s32 SHA1Reset(void* context);
extern s32 SHA1Result(void* context, void* digest);

static s32 WAD_815C43E0(WADHashThreadArgs* args) {
    void* context;
    s32 result;
    u32 remaining;
    u32 bufferIndex;
    WADImportTransfer* transfer;

    context = args->context;
    result = 0;
    remaining = args->size;
    bufferIndex = 0;
    transfer = args->transfer;

    while ((remaining != 0) && (result == 0)) {
        u32 size = remaining;
        OSMutex* mutex;

        if (remaining > transfer->chunkSize) {
            size = transfer->chunkSize;
        }
        mutex = &transfer->mutex[bufferIndex];
        OSLockMutex(mutex);
        while (transfer->ready[bufferIndex] == 0) {
            OSWaitCond(&transfer->signalCond[bufferIndex], mutex);
        }
        result = SHA1Input(context, transfer->buffers[bufferIndex], size);
        transfer->ready[bufferIndex] = 0;
        if (result != 0) {
            transfer->error = 1;
        }
        OSUnlockMutex(mutex);
        OSSignalCond(&transfer->waitCond[bufferIndex]);
        remaining -= size;
        bufferIndex ^= 1;
    }
    return result;
}

static s32 _WADHash(WADStream* stream, u32 offset, u32 size, void* context, void* buffer,
                    u32 chunkSize, void* secondBuffer, void* threadStack, u32 threadStackSize) {
    s32 result = 0;

    if ((stream == 0) || (context == 0) || (buffer == 0)) {
        return -3000;
    }
    if (size != WAD_ALIGN32(size)) {
        return -3000;
    }
    if (((u32)buffer & 0x1F) != 0) {
        return -3007;
    }
    if (chunkSize != WAD_ALIGN32(chunkSize)) {
        return -3000;
    }
    if ((secondBuffer == 0) || (threadStack == 0)) {
        u32 completed = 0;

        while (size != 0) {
            void* readBuffer = buffer;
            u32 readSize = size;

            if (chunkSize < size) {
                readSize = chunkSize;
            }
            result = WADReadStream(stream, &readBuffer, readSize, offset + completed);
            if ((u32)result != readSize) {
                result = -3005;
                break;
            }
            result = SHA1Input(context, readBuffer, readSize);
            if (result != 0) {
                break;
            }
            completed += readSize;
            size -= readSize;
        }
    } else {
        WADImportTransfer transfer;
        WADHashThreadArgs args;
        OSThread thread;
        s32 threadResult = 0;
        u32 completed = 0;
        u32 bufferIndex = 0;
        BOOL readFailed = FALSE;

        WAD_815C4A2C(&transfer, buffer, secondBuffer, chunkSize);
        args.context = context;
        args.size = size;
        args.transfer = &transfer;
        if (!OSCreateThread(&thread, (void* (*)(void*))WAD_815C43E0, &args,
                            (u8*)threadStack + threadStackSize, threadStackSize,
                            OSGetThreadPriority(OSGetCurrentThread()), 0)) {
            return -3009;
        }
        OSResumeThread(&thread);
        while ((size != 0) && (transfer.error == 0)) {
            void* readBuffer;
            u32 readSize = size;
            OSMutex* mutex = &transfer.mutex[bufferIndex];

            if (chunkSize < size) {
                readSize = chunkSize;
            }
            OSLockMutex(mutex);
            while ((transfer.ready[bufferIndex] != 0) && (transfer.error == 0)) {
                OSWaitCond(&transfer.waitCond[bufferIndex], mutex);
            }
            if (transfer.error != 0) {
                OSUnlockMutex(mutex);
                break;
            }
            readBuffer = transfer.buffers[bufferIndex];
            result = WADReadStream(stream, &readBuffer, readSize, offset + completed);
            if ((u32)result != readSize) {
                OSMutex* otherMutex = &transfer.mutex[bufferIndex ^ 1];

                OSLockMutex(otherMutex);
                OSCancelThread(&thread);
                OSJoinThread(&thread, 0);
                OSUnlockMutex(otherMutex);
                OSUnlockMutex(mutex);
                result = -3005;
                readFailed = TRUE;
                break;
            }
            transfer.ready[bufferIndex] = readSize;
            OSUnlockMutex(mutex);
            OSSignalCond(&transfer.signalCond[bufferIndex]);
            completed += readSize;
            size -= readSize;
            bufferIndex ^= 1;
        }
        if (!readFailed) {
            if (!OSJoinThread(&thread, &threadResult)) {
                result = -3009;
            } else {
                result = threadResult;
            }
        }
    }
    return result;
}

s32 WADVerify(WADStream* stream, MEMAllocator* allocator, u32 offset, u32 size) {
    WADVerificationWorkspace workspace ALIGN64;
    void* verificationBuffer = 0;
    WADBackupSignature* backupSignature;
    WADVerificationCertificateBundle* certificateBundle;
    s32 result;

    workspace.readBuffer[0] = 0;
    if (size != WAD_ALIGN32(size)) {
        result = -3000;
    } else if (size <= 0x340) {
        result = -3000;
    } else {
        workspace.readBuffer[0] = _WADMemAlloc(allocator, 0x8000);
        if (workspace.readBuffer[0] == 0) {
            result = -3003;
        } else if (((u32)workspace.readBuffer[0] & 0x3F) != 0) {
            result = -3007;
        } else {
            u32 hashSize = size - 0x340;

            SHA1Reset(workspace.hashContext);
            result = _WADHash(stream, offset, hashSize, workspace.hashContext,
                              workspace.readBuffer[0], 0x8000, 0, 0, 0x1000);
            if (result == 0) {
                result = SHA1Result(workspace.hashContext, workspace.digest);
                if (result == 0) {
                    result = WADReadStream(stream, workspace.readBuffer, 0x340,
                                           offset + hashSize);
                    if (result == 0x340) {
                        verificationBuffer = _WADMemAlloc(allocator, 0xF80);
                        if (verificationBuffer == 0) {
                            result = -3003;
                        } else {
                            backupSignature = workspace.readBuffer[0];
                            certificateBundle = verificationBuffer;
                            memcpy(certificateBundle->caProduction, ca_ppki, 0x400);
                            memcpy(certificateBundle->msProduction, ms_ppki, 0x240);
                            memcpy(certificateBundle->caDevelopment, ca_dpki, 0x400);
                            memcpy(certificateBundle->msDevelopment, ms_dpki, 0x240);
                            memcpy(certificateBundle->firstCertificate,
                                   backupSignature->firstCertificate, 0x180);
                            memcpy(certificateBundle->secondCertificate,
                                   backupSignature->secondCertificate, 0x180);
                            result = ES_VerifySign(workspace.digest, 0x14,
                                                   workspace.readBuffer[0], verificationBuffer,
                                                   0xF80);
                        }
                    } else {
                        result = -3005;
                    }
                }
            }
        }
    }

    if (workspace.readBuffer[0] != 0) {
        _WADMemFree(allocator, workspace.readBuffer[0]);
    }
    if (verificationBuffer != 0) {
        _WADMemFree(allocator, verificationBuffer);
    }
    return result;
}

static void WAD_815C4A2C(WADImportTransfer* transfer, void* firstBuffer, void* secondBuffer,
                         u32 chunkSize) {
    transfer->chunkSize = chunkSize;
    transfer->error = 0;
    transfer->ready[1] = 0;
    transfer->ready[0] = 0;
    transfer->buffers[0] = firstBuffer;
    transfer->buffers[1] = secondBuffer;
    OSInitMutex(&transfer->mutex[0]);
    OSInitMutex(&transfer->mutex[1]);
    OSInitCond(&transfer->waitCond[0]);
    OSInitCond(&transfer->waitCond[1]);
    OSInitCond(&transfer->signalCond[0]);
    OSInitCond(&transfer->signalCond[1]);
}

#pragma dont_inline on
static u32 _WADIsTerminated(const char* text, u32 maxLength) {
    u32 index;

    for (index = 0; index < maxLength; index++) {
        if (text[index] == '\0') {
            return TRUE;
        }
    }
    return FALSE;
}
#pragma dont_inline reset
