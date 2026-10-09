#include <stdio.h>
#include <stdlib.h>
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

typedef struct WADStream {
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
    u32 magic;
    u32 fileSize;
    u8 flags[3];
    char name[0x40];
    u8 reserved_0x4b[5];
    u8 iv[0x10];
    u8 reserved_0x60[0x20];
} WADFileHeader;

typedef struct WADImportParts {
    s32 type;
    u16 cidxMode;
    u16 version;
    u32 certificateSize;
    void* certificates;
    u32 crlSize;
    void* crls;
    u32 ticketSize;
    void* ticket;
    u32 titleMetaSize;
    void* titleMeta;
} WADImportParts;

typedef struct WADBackupFileHeader {
    u32 magic;
    u32 fileSize;
    u8 flags[3];
    char path[0x75];
} WADBackupFileHeader;

typedef struct WADSaveDataHeader {
    u32 format;
    u32 flags;
    u32 reserved_0x08;
    u32 saveType;
    u8 reserved_0x10[0x50];
    u32 fileSize;
    u32 magic;
    u8 reserved_0x68[0x18];
} WADSaveDataHeader;

typedef struct WADThreadStack {
    u8 bytes[0x1000];
} WADThreadStack;

typedef struct WADFileEntry {
    u32 fileSize;
    u8 flags[4];
    char name[0x40];
} WADFileEntry;

typedef union WADBackupHeaderBlock {
    WADBackupHeader header;
    u8 bytes[0x80];
} WADBackupHeaderBlock;

typedef union WADBackupTitleMetaBuffer {
    ESTmdView view;
    u8 data[0x4A00];
} WADBackupTitleMetaBuffer;

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

s32 WADOpenStream(WADLocation location, const char* path, WADStream* stream, u32, u32);
size_t WADReadStream(WADStream* stream, void** buffer, size_t size, s32 offset);
void WADCloseStream(WADStream* stream);
s32 WADWriteStream(WADStream* stream, void* buffer, u32 size);
s32 WADSeekStream(WADStream* stream, u32 offset, s32 origin);
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
void WAD_815C4A2C(WADImportTransfer* transfer, void* firstBuffer, void* secondBuffer,
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
static s32 _WADBackupGetFiles(const char* path, u32 flags, MEMAllocator* allocator,
                              u32* fileCount, WADBackupFileHeader* files);
static s32 _WADBackupGetSize(u32 flags, ESTmdView* titleMeta, ESContentMask* contentMask,
                             u32 fileCount, WADBackupFileHeader* files, u32* titleMetaSize,
                             u32* contentDataSize, u32* fileDataSize, u32* totalSize);
static s32 _WADCheckContents(ESTmdView* titleMeta, ESContentMask* contentMask);
static void _WADRandPad(void* buffer, u32 size);
static s32 _WADVerifySavedataZD(WADSaveDataHeader* header, WADStream* stream,
                                MEMAllocator* allocator, u32 offset);
static s32 _WADCleanTmpDir(MEMAllocator* allocator);
u32 _WADIsTerminated(const char* text, u32 maxLength);

extern s32 ES_GetBoot2Version(u32* version);
extern s32 SHA1Reset(void* context);
extern s32 SHA1Input(void* context, const void* data, u32 size);
extern s32 SHA1Result(void* context, void* digest);
extern char* strrchr(const char* string, int character);

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
    if (result == ES_ERR_DONT_EXISTS) {
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
    ESTitleMeta* titleMeta;
    u32 contentCount;
    s32 result;
    BOOL streamOpened;
    u32 index;
    void* secondBuffer;
    void* firstBuffer;
    WADFileEntry* allocatedFiles;
    u32 fileOffset;
    u32 transferId;
    ESContentMeta* contentMeta;
    u32 skipTitleMeta = flags & 4;
    WADFileHeader* fileHeader;

    streamOpened = FALSE;
    secondBuffer = 0;
    firstBuffer = 0;
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
            fileOffset = sizeof(workspace.wadHeader);
            result = WADReadStream(&workspace.stream, &wadHeader, fileOffset, offset);
            if (result != (s32)fileOffset) {
                result = -3005;
            } else {
                result = _WADUnpack(wadHeader, &workspace.stream, &workspace.unpackInfo, allocator,
                                    offset, flags & ~4, 1);
                if (result == 0) {
                    memset(blocks, 0, sizeof(WADBlocks));
                    titleMeta = workspace.unpackInfo.titleMeta;
                    if (titleMeta != 0) {
                        if (skipTitleMeta == 0) {
                            blocks->unkBlocks += (workspace.unpackInfo.sectionSize + 0x3FFF) >> 14;
                            blocks->unkInodes = 1;
                        }
                        if (workspace.unpackInfo.cidxMode >= 1) {
                            contentCount = _WADGetCidxCount(workspace.unpackInfo.contentIndex);
                            if (contentCount > titleMeta->head.numContents) {
                                result = -3001;
                                goto cleanup;
                            }
                            result = 0;
                        } else {
                            contentCount = titleMeta->head.numContents;
                        }
                        for (index = 0; index < contentCount; index++) {
                            if (workspace.unpackInfo.cidxMode >= 1) {
                                s32 selectedIndex = _WADGetCidx(workspace.unpackInfo.contentIndex, index);
                                if ((selectedIndex < 0) ||
                                    (selectedIndex >= titleMeta->head.numContents)) {
                                    result = -3001;
                                    goto cleanup;
                                }
                                contentMeta = titleMeta->contents + selectedIndex;
                                result = 0;
                            } else {
                                contentMeta = titleMeta->contents + index;
                            }
                            if ((contentMeta->type & 0x8000) != 0) {
                                blocks->sharedBlocks += ((u32)contentMeta->size + 0x3FFF) >> 14;
                                blocks->sharedInodes++;
                            } else {
                                blocks->privateBlocks += ((u32)contentMeta->size + 0x3FFF) >> 14;
                                blocks->privateInodes++;
                            }
                        }
                    }
                    if ((workspace.unpackInfo.fileListSize != 0) &&
                        (workspace.unpackInfo.fileCount != 0)) {
                        fileHeader = &workspace.fileHeader;
                        transferId = _WADGetTransferId(workspace.transferId);
                        if (fileListOut != 0) {
                            allocatedFiles = _WADMemAlloc(allocator,
                                                         workspace.unpackInfo.fileCount * sizeof(WADFileEntry));
                            if (allocatedFiles == 0) {
                                result = -3003;
                                goto cleanup;
                            }
                        }
                        fileOffset = workspace.unpackInfo.fileOffset;
                        for (index = 0; index < workspace.unpackInfo.fileCount; index++) {
                            fileHeader = &workspace.fileHeader;
                            result = WADReadStream(&workspace.stream, (void**)&fileHeader, 0x80,
                                                   offset + fileOffset);
                            if ((u32)result != 0x80) {
                                result = -3005;
                                goto cleanup;
                            }
                            fileOffset = (fileOffset + 0xBF) & ~0x3F;
                            result = 0;
                            if (_WADCanImportFile(fileHeader, transferId,
                                                  workspace.unpackInfo.fileNames,
                                                  workspace.transferId) != 0) {
                                blocks->fileBlocks += (fileHeader->fileSize + 0x3FFF) >> 14;
                                if (fileListOut != 0) {
                                    allocatedFiles[blocks->fileInodes].fileSize = fileHeader->fileSize;
                                    allocatedFiles[blocks->fileInodes].flags[0] = fileHeader->flags[0];
                                    allocatedFiles[blocks->fileInodes].flags[1] = fileHeader->flags[1];
                                    allocatedFiles[blocks->fileInodes].flags[2] = fileHeader->flags[2];
                                    allocatedFiles[blocks->fileInodes].flags[3] = 0;
                                    strncpy(allocatedFiles[blocks->fileInodes].name,
                                            fileHeader->name, 0x40);
                                }
                                blocks->fileInodes++;
                            }
                            fileOffset += fileHeader->fileSize;
                            fileOffset = (fileOffset + WAD_STREAM_ALIGNMENT - 1) &
                                         ~(WAD_STREAM_ALIGNMENT - 1);
                        }
                        if (fileListOut != 0) {
                            *fileListOut = (u32)allocatedFiles;
                        }
                    }
                }
            }
        }
    }

cleanup:
    _WADFreeMemory(&workspace.unpackInfo, allocator);
    if (firstBuffer != 0) {
        _WADMemFree(allocator, firstBuffer);
    }
    if (secondBuffer != 0) {
        _WADMemFree(allocator, secondBuffer);
    }
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
    s32 fd = args->fd;
    s32 result = 0;
    u32 remaining = args->size;
    WADImportTransfer* transfer = args->transfer;
    u32 bufferIndex = 0;
    u32 size;

    for (; (remaining != 0) && (result == 0); bufferIndex ^= 1) {
        size = remaining > transfer->chunkSize ? transfer->chunkSize : remaining;
        OSLockMutex(&transfer->mutex[bufferIndex]);
        while (transfer->ready[bufferIndex] == 0) {
            OSWaitCond(&transfer->signalCond[bufferIndex], &transfer->mutex[bufferIndex]);
        }
        result = ES_ImportContentData(fd, transfer->buffers[bufferIndex], size);
        transfer->ready[bufferIndex] = 0;
        if (result != 0) {
            transfer->error = 1;
        }
        OSUnlockMutex(&transfer->mutex[bufferIndex]);
        OSSignalCond(&transfer->waitCond[bufferIndex]);
        remaining -= size;
    }
    return result;
}

s32 WADImportEx(char* path, MEMAllocator* allocator, WADLocation location, u32 offset, u32 flags,
                WADProcessCallback processCallback) {
    u32 chunkSize;
    u32 i;
    u32 transferIdValue;
    u32 fileBytesRemaining;
    u32 size;
    s32 result = 0;
    u32 importedBytes = 0;
    u32 contentCount;
    s32 streamOpened = FALSE;
    s32 backupFileOpened = FALSE;
    s32 importExistingTitle = TRUE;
    WADThreadStack* threadStack = 0;
    s32 contentFd;
    s32 titleImportStarted = FALSE;
    ESTitleMeta* titleMeta;
    void* firstBuffer = 0;
    s32 contentImportStarted = FALSE;
    void* secondBuffer = 0;
    ESTitleMeta* installedTitleMeta = 0;
    ESContentId* installedContentIds = 0;
    ESContentMeta* matchingContents = 0;
    ESHash* sharedContentHashes = 0;
    WADStream stream;
    WADUnpackInfo unpackInfo;
    WADSaveDataHeader wadHeader ALIGN32;
    WADImportTransfer transfer;
    WADFileHeader backupHeader ALIGN32;
    WADImportLoopArgs threadArgs;
    OSThread importThread;
    NANDFileInfo backupFile;
    NANDStatus fileStatus;
    NANDStatus savedataStatus;
    void* wadHeaderBuffer = &wadHeader;
    void* readBuffer = 0;
    u32 installedTmdSize;
    u32 installedContentCount;
    u32 sharedContentCount;
    u32 ticketViewCount;
    WADFileHeader* fileHeaderBuffer;
    u8 transferId[0x20] ALIGN32;
    u32 j;
    u32 listIndex;
    s32 fileReadResult;
    u32 installedContentIndex;
    u32 sharedContentIndex;
    ESContentMeta* content;
    s32 matchFound;
    u32 contentSize;
    u32 readSize;
    u32 alignedSize;
    s32 importResult;
    u32 threadPriority;

    memset(&unpackInfo, 0, sizeof(WADUnpackInfo));
    if ((allocator == 0) || (allocator->heap == 0) || (path == 0)) {
        result = -3000;
        goto cleanup;
    }
    if ((offset & 0x3F) != 0) {
        result = -3007;
        goto cleanup;
    }
    result = 0;
    if (processCallback != 0) {
        processCallback(0, 0, FALSE);
    }
    result = WADOpenStream(location, path, &stream, 0, 0);
    streamOpened = TRUE;
    if (result != 0) {
        goto cleanup;
    }
    size = sizeof(wadHeader);
    result = WADReadStream(&stream, &wadHeaderBuffer, size, offset);
    if (result != (s32)size) {
        result = -3005;
        goto cleanup;
    }
    result = 0;
    result = _WADUnpack(wadHeaderBuffer, &stream, &unpackInfo, allocator, offset,
                        flags, 0);
    if (result != 0) {
        goto cleanup;
    }
    importedBytes = unpackInfo.contentOffset;
    titleMeta = unpackInfo.titleMeta;
    if (((flags & 8) != 0) && (titleMeta != 0)) {
        ticketViewCount = 0;
        if (unpackInfo.headerInfo != 2) {
            result = -3001;
            goto cleanup;
        }
        result = ES_GetTicketViews(titleMeta->head.titleId, 0,
                                   &ticketViewCount);
        if (result != 0) {
            goto cleanup;
        }
        if (ticketViewCount == 0) {
            result = ES_ERR_TICKET_NOT_FOUND;
            goto cleanup;
        }
    }
    if (((titleMeta != 0) && (titleMeta->head.titleId == 0x0000000100000001ULL)) ||
        (unpackInfo.headerInfo == 3)) {
        size = ((u32)titleMeta->contents[0].size + 0x0F) & ~0x0F;
        alignedSize = (size + 0x1F) & ~0x1F;
        firstBuffer = _WADMemAlloc(allocator, alignedSize);
        if (firstBuffer == 0) {
            result = -3003;
            goto cleanup;
        }
        readBuffer = firstBuffer;
        result = WADReadStream(&stream, &readBuffer, (size + 0x1F) & ~0x1F,
                                offset + importedBytes);
        if ((u32)result != ((size + 0x1F) & ~0x1F)) {
            result = -3005;
            goto cleanup;
        }
        result = 0;
        result = ES_ImportBoot(unpackInfo.buffer_0x34,
                               unpackInfo.buffer_0x14,
                               unpackInfo.size_0x0c,
                               unpackInfo.titleMeta,
                               unpackInfo.sectionSize,
                               unpackInfo.buffer_0x14,
                               unpackInfo.size_0x0c,
                               unpackInfo.buffer_0x24,
                               unpackInfo.size_0x1c, readBuffer,
                               size);
        goto cleanup;
    }
    if (unpackInfo.buffer_0x34 != 0) {
        result = ES_ImportTicket(unpackInfo.buffer_0x34,
                                 unpackInfo.buffer_0x14,
                                 unpackInfo.size_0x0c,
                                 unpackInfo.buffer_0x24,
                                 unpackInfo.size_0x1c, unpackInfo.headerInfo);
        if (result != 0) {
            goto cleanup;
        }
    }
    if (processCallback != 0) {
        processCallback(0, unpackInfo.contentSize + unpackInfo.fileListSize, FALSE);
    }
    if (titleMeta != 0) {
        if (unpackInfo.cidxMode >= 1) {
            contentCount = _WADGetCidxCount(unpackInfo.contentIndex);
            if (contentCount > titleMeta->head.numContents) {
                result = -3001;
                goto cleanup;
            }
            result = 0;
        } else {
            contentCount = titleMeta->head.numContents;
        }
        result = ES_ListTmdContentsOnCard(titleMeta,
                                          unpackInfo.sectionSize, 0,
                                          &installedContentCount);
        if ((result == 0) && (installedContentCount != 0)) {
            installedContentIds = _WADMemAlloc(allocator, installedContentCount * sizeof(ESContentId));
            if (installedContentIds == 0) {
                result = -3003;
                goto cleanup;
            }
            result = ES_ListTmdContentsOnCard(titleMeta,
                                              unpackInfo.sectionSize,
                                              installedContentIds, &installedContentCount);
            if ((result == 0) &&
                ((result = ES_GetTmd(titleMeta->head.titleId, 0,
                                    &installedTmdSize)) == 0)) {
                alignedSize = (installedTmdSize + 0x1F) & ~0x1F;
                installedTitleMeta = _WADMemAlloc(allocator, alignedSize);
                if (installedTitleMeta == 0) {
                    result = -3003;
                    goto cleanup;
                }
                result = ES_GetTmd(titleMeta->head.titleId,
                                   installedTitleMeta, &installedTmdSize);
                if (result == 0) {
                    importExistingTitle = FALSE;
                }
            }
        }
        if (!importExistingTitle && (installedContentCount != 0)) {
            installedContentIndex = 0;
            matchingContents = _WADMemAlloc(allocator, installedContentCount * sizeof(ESContentMeta));
            if (matchingContents == 0) {
                result = -3003;
                goto cleanup;
            }
            for (i = 0; i < installedContentCount; i++) {
                for (j = 0;
                     j < installedTitleMeta->head.numContents; j++) {
                    if (installedContentIds[i] ==
                        installedTitleMeta->contents[j].cid) {
                        memcpy(&matchingContents[installedContentIndex],
                               &installedTitleMeta->contents[j], sizeof(ESContentMeta));
                        installedContentIndex++;
                    }
                }
            }
        }
        result = ES_ListSharedContents(&sharedContentCount, 0);
        if (result == 0) {
            alignedSize = (sharedContentCount * sizeof(ESHash) + 0x1F) & ~0x1F;
            sharedContentHashes = _WADMemAlloc(allocator, alignedSize);
            if (sharedContentHashes == 0) {
                result = -3003;
                goto cleanup;
            }
            result = ES_ListSharedContents(&sharedContentCount, sharedContentHashes);
            if ((result != 0) && (sharedContentHashes != 0)) {
                _WADMemFree(allocator, sharedContentHashes);
                sharedContentHashes = 0;
            }
        }
        result = ES_ImportTitleInit(titleMeta,
                                    unpackInfo.sectionSize,
                                    unpackInfo.buffer_0x14,
                                    unpackInfo.size_0x0c,
                                    unpackInfo.buffer_0x24,
                                    unpackInfo.size_0x1c,
                                    unpackInfo.headerInfo, 1);
        if (result != 0) {
            goto cleanup;
        }
        titleImportStarted = TRUE;
        if ((flags & 2) == 0) {
            for (i = 0; i < contentCount; i++) {
                s32 titleMetaIndex;
                matchFound = FALSE;
                if (unpackInfo.cidxMode >= 1) {
                    titleMetaIndex = _WADGetCidx(unpackInfo.contentIndex, i);
                    if ((titleMetaIndex < 0) ||
                        (titleMetaIndex >= (s32)titleMeta->head.numContents)) {
                        result = -3001;
                        goto cleanup;
                    }
                    result = 0;
                    content = &titleMeta->contents[titleMetaIndex];
                } else {
                    content = &titleMeta->contents[i];
                }
                if (!importExistingTitle) {
                    for (listIndex = 0; listIndex < installedContentCount; listIndex++) {
                        if ((content->cid == matchingContents[listIndex].cid) &&
                            (memcmp(content->hash, matchingContents[listIndex].hash, sizeof(ESHash)) == 0) &&
                            (content->type == matchingContents[listIndex].type)) {
                            matchFound = TRUE;
                        }
                    }
                }
                if (((content->type & 0x8000) != 0) &&
                    (sharedContentHashes != 0) && !matchFound) {
                    for (sharedContentIndex = 0; sharedContentIndex < sharedContentCount;
                         sharedContentIndex++) {
                        if (memcmp(content->hash, sharedContentHashes[sharedContentIndex],
                                   sizeof(ESHash)) == 0) {
                            matchFound = TRUE;
                        }
                    }
                }
                if (!matchFound) {
                    if (firstBuffer == 0) {
                        firstBuffer = _WADMemAlloc(allocator, 0x10000);
                        if (firstBuffer == 0) {
                            result = -3003;
                            goto cleanup;
                        }
                    }
                    if (secondBuffer == 0) {
                        secondBuffer = _WADMemAlloc(allocator, 0x10000);
                        if (secondBuffer == 0) {
                            result = -3003;
                            goto cleanup;
                        }
                    }
                    if (threadStack == 0) {
                        threadStack = _WADMemAlloc(allocator, sizeof(WADThreadStack));
                        if (threadStack == 0) {
                            result = -3003;
                            goto cleanup;
                        }
                    }
                    if ((firstBuffer == 0) || (secondBuffer == 0) || (threadStack == 0)) {
                        result = -3003;
                        goto cleanup;
                    }
                    result = 0;
                    contentFd = ES_ImportContentBegin(
                        titleMeta->head.titleId, content->cid);
                    if (contentFd < 0) {
                        result = contentFd;
                        goto cleanup;
                    }
                    result = 0;
                    contentImportStarted = TRUE;
                    size = ((u32)content->size + 0x0F) & ~0x0F;
                    WAD_815C4A2C(&transfer, firstBuffer, secondBuffer, 0x10000);
                    threadArgs.fd = contentFd;
                    threadArgs.transfer = &transfer;
                    threadArgs.size = size;
                    threadPriority = OSGetThreadPriority(OSGetCurrentThread());
                    importResult = OSCreateThread(&importThread,
                                                  (void* (*)(void*))WAD_815BFFA8,
                                                  &threadArgs,
                                                  &threadStack->bytes[sizeof(threadStack->bytes)],
                                                  sizeof(threadStack->bytes),
                                                  threadPriority, 0);
                    if (!importResult) {
                        result = -3009;
                        goto cleanup;
                    }
                    OSResumeThread(&importThread);
                    j = 0;
                    while ((size != 0) && (transfer.error == 0)) {
                        if (size > transfer.chunkSize) {
                            chunkSize = transfer.chunkSize;
                        } else {
                            chunkSize = size;
                        }
                        OSLockMutex(&transfer.mutex[j]);
                        while ((transfer.ready[j] != 0) &&
                               (transfer.error == 0)) {
                            OSWaitCond(&transfer.waitCond[j],
                                       &transfer.mutex[j]);
                        }
                        if (transfer.error != 0) {
                            OSUnlockMutex(&transfer.mutex[j]);
                            break;
                        }
                        readBuffer = transfer.buffers[j];
                        result = WADReadStream(&stream,
                                               &readBuffer, (chunkSize + 0x1F) & ~0x1F,
                                               offset + importedBytes);
                        if ((u32)result != ((chunkSize + 0x1F) & ~0x1F)) {
                            OSLockMutex(&transfer.mutex[j ^ 1]);
                            OSCancelThread(&importThread);
                            OSJoinThread(&importThread, 0);
                            OSUnlockMutex(&transfer.mutex[j ^ 1]);
                            OSUnlockMutex(&transfer.mutex[j]);
                            result = -3005;
                            goto cleanup;
                        }
                        transfer.ready[j] = chunkSize;
                        OSUnlockMutex(&transfer.mutex[j]);
                        OSSignalCond(&transfer.signalCond[j]);
                        importedBytes += chunkSize;
                        size -= chunkSize;
                        if (processCallback != 0) {
                            processCallback(importedBytes - unpackInfo.contentOffset,
                                            unpackInfo.contentSize + unpackInfo.fileListSize, FALSE);
                        }
                        j ^= 1;
                    }
                    if (!OSJoinThread(&importThread, (void**)&result)) {
                        return -3009;
                    }
                    if (result != 0) {
                        goto cleanup;
                    }
                    result = ES_ImportContentEnd(contentFd);
                    if (result != 0) {
                        goto cleanup;
                    }
                    contentImportStarted = FALSE;
                } else {
                    importedBytes += ((u32)content->size + 0x0F) & ~0x0F;
                    if (processCallback != 0) {
                        processCallback(importedBytes - unpackInfo.contentOffset,
                                        unpackInfo.contentSize + unpackInfo.fileListSize, FALSE);
                    }
                }
                if (unpackInfo.type == 2) {
                    importedBytes = (importedBytes + 0x3F) & ~0x3F;
                }
            }
        }
        result = ES_ImportTitleDone();
        if (result != 0) {
            goto cleanup;
        }
        titleImportStarted = FALSE;
    }
    if (((flags & 2) != 0) || (unpackInfo.fileListSize == 0) ||
        (unpackInfo.fileCount == 0)) {
        goto cleanup;
    }
    fileHeaderBuffer = &backupHeader;
    if (firstBuffer == 0) {
        firstBuffer = _WADMemAlloc(allocator, 0x10000);
        if (firstBuffer == 0) {
            result = -3003;
            goto cleanup;
        }
    }
    if (secondBuffer == 0) {
        secondBuffer = _WADMemAlloc(allocator, 0x10000);
        if (secondBuffer == 0) {
            result = -3003;
            goto cleanup;
        }
    }
    transferIdValue = _WADGetTransferId(transferId);
    importedBytes = unpackInfo.fileOffset;
    {
        u32 headerFileSize;
        u32 headerMagic;
        WADSaveDataHeader* savedataHeader;
        savedataHeader = wadHeaderBuffer;
        headerFileSize = savedataHeader->fileSize;
        headerMagic = savedataHeader->magic;
        if (((((u64)headerFileSize << 32) | headerMagic) & 0xFFFFFFFFFFFFFF00ULL) ==
            0x00010000525A4400ULL) {
            result = _WADVerifySavedataZD(savedataHeader, &stream, allocator,
                                          offset + unpackInfo.fileOffset);
            goto cleanup;
        }
    }
    for (i = 0; i < unpackInfo.fileCount; i++) {
        fileHeaderBuffer = &backupHeader;
        result = WADReadStream(&stream, (void**)&fileHeaderBuffer, sizeof(backupHeader),
                               offset + importedBytes);
        if (result != sizeof(backupHeader)) {
            result = -3005;
            goto cleanup;
        }
        result = 0;
        importedBytes = (importedBytes + 0xBF) & ~0x3F;
        if (fileHeaderBuffer->magic != 0x3ADF17E) {
            result = -3000;
            goto cleanup;
        }
        result = 0;
        if (_WADCanImportFile(fileHeaderBuffer, transferIdValue,
                              unpackInfo.fileNames, transferId) == 0) {
            if ((fileHeaderBuffer->flags[2] == NAND_TYPE_FILE) && (fileHeaderBuffer->fileSize != 0)) {
                importedBytes += fileHeaderBuffer->fileSize;
                importedBytes = (importedBytes + 0x3F) & ~0x3F;
            }
            continue;
        }
        if (fileHeaderBuffer->flags[2] == NAND_TYPE_FILE) {
            result = NANDPrivateCreate(fileHeaderBuffer->name, fileHeaderBuffer->flags[0] | NAND_PERM_USER_WRITE,
                                       fileHeaderBuffer->flags[1]);
            if (result != 0) {
                goto cleanup;
            }
            if (fileHeaderBuffer->fileSize != 0) {
                result = NANDPrivateOpen(fileHeaderBuffer->name, &backupFile, NAND_ACCESS_WRITE);
                if (result != 0) {
                    goto cleanup;
                }
                backupFileOpened = TRUE;
                fileBytesRemaining = fileHeaderBuffer->fileSize;
                while (fileBytesRemaining != 0) {
                    if (fileBytesRemaining > 0x10000) {
                        chunkSize = 0x10000;
                    } else {
                        chunkSize = fileBytesRemaining;
                    }
                    readBuffer = firstBuffer;
                    result = WADReadStream(&stream, &readBuffer,
                                           (chunkSize + 0x1F) & ~0x1F,
                                           offset + importedBytes);
                    readSize = (chunkSize + 0x1F) & ~0x1F;
                    if ((u32)result != ((chunkSize + 0x1F) & ~0x1F)) {
                        result = -3005;
                        goto cleanup;
                    }
                    result = 0;
                    result = ES_Decrypt(6, fileHeaderBuffer->iv,
                                        readBuffer, readSize, secondBuffer);
                    if (result != 0) {
                        goto cleanup;
                    }
                    result = NANDWrite(&backupFile, secondBuffer, chunkSize);
                    if ((u32)result != chunkSize) {
                        result = -3006;
                        goto cleanup;
                    }
                    result = 0;
                    importedBytes += chunkSize;
                    fileBytesRemaining -= chunkSize;
                    if (processCallback != 0) {
                        processCallback(unpackInfo.contentSize +
                                            (importedBytes - unpackInfo.fileOffset),
                                        unpackInfo.contentSize + unpackInfo.fileListSize, FALSE);
                    }
                }
                result = NANDClose(&backupFile);
                if (result != 0) {
                    goto cleanup;
                }
                backupFileOpened = FALSE;
            }
            if ((fileHeaderBuffer->flags[0] & NAND_PERM_USER_WRITE) == 0) {
                result = NANDPrivateGetStatus(fileHeaderBuffer->name, &fileStatus);
                if (result != 0) {
                    goto cleanup;
                }
                fileStatus.permission = fileHeaderBuffer->flags[0];
                fileStatus.attribute = fileHeaderBuffer->flags[1];
                result = NANDPrivateSetStatus(fileHeaderBuffer->name, &fileStatus);
                if (result != 0) {
                    goto cleanup;
                }
            }
        } else if (fileHeaderBuffer->flags[2] == NAND_TYPE_DIR) {
            result = NANDPrivateCreateDir(fileHeaderBuffer->name,
                                          fileHeaderBuffer->flags[0] | NAND_PERM_USER_WRITE,
                                          fileHeaderBuffer->flags[1]);
            if (result == NAND_RESULT_EXISTS) {
                result = NANDPrivateGetStatus(fileHeaderBuffer->name, &fileStatus);
                if (result != 0) {
                    goto cleanup;
                }
                if ((fileStatus.permission & NAND_PERM_USER_WRITE) == 0) {
                    fileStatus.permission = fileHeaderBuffer->flags[0] | NAND_PERM_USER_WRITE;
                    fileStatus.attribute = fileHeaderBuffer->flags[1];
                    result = NANDPrivateSetStatus(fileHeaderBuffer->name, &fileStatus);
                    if (result != 0) {
                        goto cleanup;
                    }
                }
            }
            if (result != 0) {
                goto cleanup;
            }
        }
        importedBytes = (importedBytes + 0x3F) & ~0x3F;
        if ((fileHeaderBuffer->fileSize == 0) && (processCallback != 0)) {
            processCallback(unpackInfo.contentSize +
                                (importedBytes - unpackInfo.fileOffset),
                            unpackInfo.contentSize + unpackInfo.fileListSize, FALSE);
        }
    }
    importedBytes = unpackInfo.fileOffset;
    for (i = 0; i < unpackInfo.fileCount;
         i++) {
        fileHeaderBuffer = &backupHeader;
        fileReadResult = WADReadStream(&stream, (void**)&fileHeaderBuffer,
                                       sizeof(backupHeader),
                                       offset + importedBytes);
        if (fileReadResult != sizeof(backupHeader)) {
            result = -3005;
            break;
        }
        result = 0;
        importedBytes = (importedBytes + 0xBF) & ~0x3F;
        if (_WADCanImportFile(fileHeaderBuffer, transferIdValue,
                              unpackInfo.fileNames, transferId) != 0) {
            result = NANDPrivateGetStatus(fileHeaderBuffer->name, &savedataStatus);
            if (result != 0) {
                goto cleanup;
            }
            if ((fileHeaderBuffer->flags[0] & NAND_PERM_USER_WRITE) == 0) {
                savedataStatus.permission = fileHeaderBuffer->flags[0];
                result = NANDPrivateSetStatus(fileHeaderBuffer->name, &savedataStatus);
                if (result != 0) {
                    goto cleanup;
                }
            }
        }
        importedBytes += fileHeaderBuffer->fileSize;
        importedBytes = (importedBytes + 0x3F) & ~0x3F;
    }

cleanup:
    _WADFreeMemory(&unpackInfo, allocator);
    if (firstBuffer != 0) {
        _WADMemFree(allocator, firstBuffer);
    }
    if (secondBuffer != 0) {
        _WADMemFree(allocator, secondBuffer);
    }
    if (installedTitleMeta != 0) {
        _WADMemFree(allocator, installedTitleMeta);
    }
    if (installedContentIds != 0) {
        _WADMemFree(allocator, installedContentIds);
    }
    if (matchingContents != 0) {
        _WADMemFree(allocator, matchingContents);
    }
    if (sharedContentHashes != 0) {
        _WADMemFree(allocator, sharedContentHashes);
    }
    if (threadStack != 0) {
        _WADMemFree(allocator, threadStack);
    }
    if (backupFileOpened) {
        NANDClose(&backupFile);
    }
    if (streamOpened) {
        WADCloseStream(&stream);
    }
    if (contentImportStarted) {
        ES_ImportContentEnd(contentFd);
        OSReport("%s:%d Cancel importing the content.\n", __func__, 0x8DF);
    }
    if (titleImportStarted) {
        ES_ImportTitleCancel();
        _WADCleanTmpDir(allocator);
        OSReport("%s:%d Cancel importing the title.\n", __func__, 0x8E6);
    }
    if (processCallback != 0) {
        if (importedBytes != 0) {
            if ((unpackInfo.fileListSize != 0) && (unpackInfo.fileCount != 0)) {
                processCallback(unpackInfo.contentSize + (importedBytes - unpackInfo.fileOffset),
                                unpackInfo.contentSize + unpackInfo.fileListSize, TRUE);
            } else {
                processCallback(importedBytes - unpackInfo.contentOffset,
                                unpackInfo.contentSize + unpackInfo.fileListSize, TRUE);
            }
        } else {
            processCallback(0, 0, TRUE);
        }
    }
    return result;
}

static inline u32 export_chunk_size(u32 remaining, u32 maximum) {
    u32 size = remaining;
    if (remaining > maximum) {
        size = maximum;
    }
    return size;
}

static s32 WAD_815C1288(WADExportLoopArgs* args) {
    u32 size;
    s32 result;
    ESFd fd;
    u32 remaining;
    WADImportTransfer* transfer;
    u32 bufferIndex;

    fd = args->fd;
    result = 0;
    remaining = args->size;
    bufferIndex = 0;
    transfer = args->transfer;

    for (; (remaining != 0) && (result == 0); bufferIndex ^= 1) {
        size = export_chunk_size(remaining, transfer->chunkSize);
        OSLockMutex(&transfer->mutex[bufferIndex]);
        while (transfer->ready[bufferIndex] != 0) {
            OSWaitCond(&transfer->waitCond[bufferIndex], &transfer->mutex[bufferIndex]);
        }
        result = ES_ExportContentData(fd, transfer->buffers[bufferIndex], size);
        transfer->ready[bufferIndex] = size;
        if (result != 0) {
            transfer->error = 1;
        }
        OSUnlockMutex(&transfer->mutex[bufferIndex]);
        OSSignalCond(&transfer->signalCond[bufferIndex]);
        remaining -= size;
    }
    return result;
}

static inline BOOL _WADIsError(s32 result) {
    return result < 0;
}

s32 WADBackupEx(u64 titleId, u32 flags, MEMAllocator* allocator, char* path, u32* sizeOut,
                WADLocation location, u32 offset, WADProcessCallback processCallback) {
    s32 fileFd;
    WADBackupTitleMetaBuffer* titleMetaBuffer;
    WADBackupFileHeader* files;
    u32 size;
    u32 importedSize;
    void* outputBuffer;
    u32 index;
    void* encryptionBuffer;
    u32 bufferIndex;
    u32 sizeRemaining;
    u32 chunkSize;
    s32 result;
    OSThread exportThread;
    NANDFileInfo savedFile;
    WADStream stream;
    WADBackupHeaderBlock headerBlock ALIGN64;
    WADBackupHeaderBlock* headerBuffer = &headerBlock;
    u8 hashContext[0x60] ALIGN32;
    WADFileHeader fileHeader ALIGN32;
    WADImportTransfer transfer;
    char currentDirectory[NAND_MAX_PATH];
    u8 signature[0x40] ALIGN32;
    ESContentMask existingContentMask ALIGN32;
    u8 digest[0x40] ALIGN32;
    u8 transferMac[0x20] ALIGN32;
    WADExportLoopArgs threadArgs;
    u32 totalSize;
    ESTmdView* titleMeta;
    struct WADExportCertificates {
        ESCertSignature signer;
        u8 device[0x180];
    };
    struct WADExportCertificates* certificates;
    s32 position;
    u32 titleMetaSize;
    u32 titleMetaViewSize;
    u32 contentDataSize;
    u32 fileCount;
    u32 fileDataSize;
    u32 installedContentCount;
    s32 streamResult;
    u32 priority;
    u32 length;
    s32 streamOpened;
    s32 fileOpened;
    WADThreadStack* threadStack;
    s32 titleExportStarted;
    s32 contentExportStarted;
    s32 threadCreated = FALSE;

    titleMetaSize = 0;
    contentDataSize = 0;
    titleMetaBuffer = 0;
    titleMeta = 0;
    files = 0;
    fileCount = 0;
    importedSize = 0;
    outputBuffer = 0;
    encryptionBuffer = 0;
    fileDataSize = 0;
    installedContentCount = 0;
    streamOpened = 0;
    fileOpened = 0;
    threadStack = 0;
    titleExportStarted = 0;
    contentExportStarted = 0;

    if (flags == 0) {
        flags = 0x0F;
    }
    if ((flags & 3) == 0) {
        result = -3000;
        goto cleanup;
    }
    if ((u32)((titleId >> 32) & 0xFFFFFFFFULL) == 1U) {
        result = -3000;
        goto cleanup;
    }
    if ((allocator == 0) || (sizeOut == 0)) {
        result = -3000;
        goto cleanup;
    }
    if ((offset & 0x3F) != 0) {
        result = -3007;
        goto cleanup;
    }
    result = 0;
    if (processCallback != 0) {
        processCallback(0, 0, FALSE);
    }
    if (((flags & 1) != 0) || ((flags & 0x20) != 0)) {
        result = ES_GetTmdView(titleId, 0, &titleMetaViewSize);
        if (result != 0) {
            goto cleanup;
        }
        titleMetaBuffer = _WADMemAlloc(allocator, sizeof(WADBackupTitleMetaBuffer));
        if (titleMetaBuffer == 0) {
            result = -3003;
            goto cleanup;
        }
        if (titleMetaBuffer == 0) {
            result = -3000;
            goto cleanup;
        }
        result = 0;
        titleMeta = &titleMetaBuffer->view;
        result = 0;
        result = ES_GetTmdView(titleId, titleMeta, &titleMetaViewSize);
        if (result != 0) {
            goto cleanup;
        }
    }
    if ((flags & 1) != 0) {
        result = ES_ListTitleContentsOnCard(titleId, 0, &installedContentCount);
        if (result == ES_ERR_DONT_EXISTS) {
            result = -3002;
            goto cleanup;
        }
        result = 0;
        if (installedContentCount == 0) {
            if (!_WADIsError(result)) {
                result = -3002;
            }
            goto cleanup;
        }
        result = 0;
        result = _WADCheckContents(titleMeta, &existingContentMask);
        if (result != 0) {
            goto cleanup;
        }
    }
    if ((flags & 2) != 0) {
        result = NANDGetCurrentDir(currentDirectory);
        if (result != 0) {
            goto cleanup;
        }
        result = _WADBackupGetFiles(0, flags, allocator, &fileCount, 0);
        if (result != 0) {
            goto cleanup;
        }
        if (fileCount == 0) {
            files = 0;
        } else {
            files = _WADMemAlloc(allocator, fileCount * sizeof(WADBackupFileHeader));
            if (files == 0) {
                result = -3003;
                goto cleanup;
            }
            if (files == 0) {
                result = -3003;
                goto cleanup;
            }
            result = 0;
            result = _WADBackupGetFiles(0, flags, allocator, &fileCount, files);
            if (result != 0) {
                goto cleanup;
            }
        }
    }
    result = _WADBackupGetSize(flags, titleMeta, &existingContentMask, fileCount, files,
                               &titleMetaSize, &contentDataSize, &fileDataSize, &totalSize);
    if (result != 0) {
        goto cleanup;
    }
    if ((contentDataSize == 0) && (fileDataSize == 0)) {
        result = -3002;
        goto cleanup;
    }
    result = 0;
    if (path == 0) {
        *sizeOut = totalSize + 0x340;
        goto cleanup;
    }
    outputBuffer = _WADMemAlloc(allocator, 0x10000);
    if (outputBuffer == 0) {
        result = -3003;
        goto cleanup;
    }
    if (outputBuffer == 0) {
        result = -3000;
        goto cleanup;
    }
    result = 0;
    if (processCallback != 0) {
        processCallback(0, contentDataSize + fileDataSize, FALSE);
    }
    result = WADOpenStream(location, path, &stream, 1, offset);
    streamOpened = TRUE;
    if (result != 0) {
        goto cleanup;
    }
    size = sizeof(headerBlock);
    memset(headerBuffer, 0, size);
    streamResult = WADWriteStream(&stream, headerBuffer, size);
    if ((u32)streamResult != size) {
        result = -3006;
        goto cleanup;
    }
    result = 0;
    headerBuffer->header.hdrSize = sizeof(WADBackupHeader);
    headerBuffer->header.wadType[0] = 'B';
    headerBuffer->header.wadType[1] = 'k';
    headerBuffer->header.wadVersion = 1;
    headerBuffer->header.tmdSize = titleMetaSize;
    headerBuffer->header.contentSize = contentDataSize;
    headerBuffer->header.fileSize = fileDataSize;
    headerBuffer->header.numFiles = fileCount;
    headerBuffer->header.backupAreaLen = totalSize + 0x340;
    result = ES_GetDeviceId(&headerBuffer->header.deviceId);
    if (result != 0) {
        goto cleanup;
    }
    if ((flags & 1) != 0) {
        memcpy(&headerBuffer->header.cidx, &existingContentMask, sizeof(existingContentMask));
    }
    if ((flags & 2) != 0) {
        u32 currentTitleLow;
        u32 currentTitleHigh;
        encryptionBuffer = _WADMemAlloc(allocator, 0x10000);
        if (encryptionBuffer == 0) {
            result = -3003;
            goto cleanup;
        }
        if (encryptionBuffer == 0) {
            result = -3003;
            goto cleanup;
        }
        result = 0;
        result = NANDGetCurrentDir(encryptionBuffer);
        if (strncmp(encryptionBuffer, "/title/", 7) == 0) {
            currentTitleHigh = 0;
            currentTitleLow = 0;
            sscanf(encryptionBuffer, "/title/%x/%x", &currentTitleHigh, &currentTitleLow);
            headerBuffer->header.titleId = ((u64)currentTitleHigh << 32) | currentTitleLow;
        }
        if (_WADGetTransferId(transferMac) != 0) {
            memcpy(headerBuffer->header.deviceMac, transferMac, sizeof(headerBuffer->header.deviceMac));
        }
    }
    SHA1Reset(hashContext);
    result = SHA1Input(hashContext, headerBuffer, sizeof(headerBlock));
    if (result != 0) {
        goto cleanup;
    }
    srand(titleId & 0xFFFFFFFFULL);
    if (((flags & 1) != 0) || ((flags & 0x20) != 0)) {
        titleExportStarted = TRUE;
        result = ES_ExportTitleInit(titleId, 0, 0, 0, 0, 0, 0,
                                    2, 0, titleMetaBuffer, titleMetaSize);
        if (result != 0) {
            goto cleanup;
        }
        size = ((titleMetaSize + 0x3F) & ~0x3F) - titleMetaSize;
        if (size != 0) {
            _WADRandPad(&titleMetaBuffer->data[titleMetaSize], size);
        }
        size = (titleMetaSize + 0x3F) & ~0x3F;
        result = SHA1Input(hashContext, titleMetaBuffer, size);
        if (result != 0) {
            goto cleanup;
        }
        streamResult = WADWriteStream(&stream, titleMetaBuffer, size);
        if ((u32)streamResult != size) {
            result = -3006;
            goto cleanup;
        }
        result = 0;
    }
    if ((flags & 1) != 0) {
        if (encryptionBuffer == 0) {
            encryptionBuffer = _WADMemAlloc(allocator, 0x10000);
            if (encryptionBuffer == 0) {
                result = -3003;
                goto cleanup;
            }
            if (encryptionBuffer == 0) {
                result = -3003;
                goto cleanup;
            }
            result = 0;
        }
        threadStack = _WADMemAlloc(allocator, sizeof(WADThreadStack));
        if (threadStack == 0) {
            result = -3003;
            goto cleanup;
        }
        if (threadStack == 0) {
            result = -3003;
            goto cleanup;
        }
        result = 0;
        installedContentCount = _WADGetCidxCount(&existingContentMask);
        for (index = 0; index < installedContentCount; index++) {
            s32 tmdIndex = _WADGetCidx(&existingContentMask, index);
            ESContentMeta* content;
            if ((tmdIndex < 0) || (tmdIndex >= ((ESTitleMeta*)titleMetaBuffer)->head.numContents)) {
                result = -3009;
                goto cleanup;
            }
            content = &((ESTitleMeta*)titleMetaBuffer)->contents[tmdIndex];
            result = 0;
            fileFd = ES_ExportContentBegin(titleId, content->cid);
            if (fileFd < 0) {
                result = fileFd;
                goto cleanup;
            }
            result = 0;
            contentExportStarted = TRUE;
            sizeRemaining = ((u32)content->size + 0x0F) & ~0x0F;
            WAD_815C4A2C(&transfer, outputBuffer, encryptionBuffer, 0x10000);
            threadArgs.fd = fileFd;
            threadArgs.size = sizeRemaining;
            threadArgs.transfer = &transfer;
            priority = OSGetThreadPriority(OSGetCurrentThread());
            threadCreated = OSCreateThread(&exportThread, (void* (*)(void*))WAD_815C1288,
                                           &threadArgs,
                                           &threadStack->bytes[sizeof(threadStack->bytes)],
                                           sizeof(threadStack->bytes),
                                           priority, 0);
            if (!threadCreated) {
                result = -3009;
                goto cleanup;
            }
            OSResumeThread(&exportThread);
            size = ((sizeRemaining + 0x3F) & ~0x3F) - sizeRemaining;
            sizeRemaining += size;
            bufferIndex = 0;
            while ((sizeRemaining != 0) && (transfer.error == 0)) {
                if (sizeRemaining > transfer.chunkSize) {
                    chunkSize = transfer.chunkSize;
                } else {
                    chunkSize = sizeRemaining;
                }
                OSLockMutex(&transfer.mutex[bufferIndex]);
                while ((transfer.ready[bufferIndex] == 0) && (transfer.error == 0)) {
                    OSWaitCond(&transfer.signalCond[bufferIndex], &transfer.mutex[bufferIndex]);
                }
                if (transfer.error != 0) {
                    OSUnlockMutex(&transfer.mutex[bufferIndex]);
                    break;
                }
                if ((chunkSize == sizeRemaining) && (size != 0)) {
                    _WADRandPad((u8*)transfer.buffers[bufferIndex] + transfer.ready[bufferIndex],
                                size);
                }
                result = SHA1Input(hashContext, transfer.buffers[bufferIndex], chunkSize);
                if (result != 0) {
                    goto cleanup;
                }
                result = WADWriteStream(&stream, transfer.buffers[bufferIndex], chunkSize);
                if ((u32)result != chunkSize) {
                    OSLockMutex(&transfer.mutex[bufferIndex ^ 1]);
                    OSCancelThread(&exportThread);
                    OSJoinThread(&exportThread, 0);
                    OSUnlockMutex(&transfer.mutex[bufferIndex ^ 1]);
                    OSUnlockMutex(&transfer.mutex[bufferIndex]);
                    result = -3006;
                    goto cleanup;
                }
                transfer.ready[bufferIndex] = 0;
                OSUnlockMutex(&transfer.mutex[bufferIndex]);
                OSSignalCond(&transfer.waitCond[bufferIndex]);
                importedSize += chunkSize;
                sizeRemaining -= chunkSize;
                if (processCallback != 0) {
                    processCallback(importedSize, contentDataSize + fileDataSize, FALSE);
                }
                bufferIndex ^= 1;
            }
            if (!OSJoinThread(&exportThread, (void**)&result)) {
                return -3009;
            }
            if (result != 0) {
                goto cleanup;
            }
            contentExportStarted = FALSE;
            result = ES_ExportContentEnd(fileFd);
            if (result != 0) {
                goto cleanup;
            }
        }
    }
    if (((flags & 1) != 0) || ((flags & 0x20) != 0)) {
        titleExportStarted = FALSE;
        result = ES_ExportTitleDone();
        if (result != 0) {
            goto cleanup;
        }
    }
    if ((flags & 2) != 0) {
        WADFileHeader* fileHeaderBuffer = &fileHeader;
        for (index = 0; index < fileCount; index++) {
            u32 byteCount;
            position = WADSeekStream(&stream, 0, 1);
            byteCount = strlen(files[index].path) + 1;
            _WADRandPad(files[index].path + byteCount,
                        sizeof(files[index].path) - byteCount);
            memcpy(fileHeaderBuffer, &files[index], sizeof(fileHeader));
            size = sizeof(WADBackupHeaderBlock);
            result = SHA1Input(hashContext, fileHeaderBuffer, size);
            if (result != 0) {
                goto cleanup;
            }
            streamResult = WADWriteStream(&stream, fileHeaderBuffer, size);
            if ((u32)streamResult != size) {
                result = -3006;
                goto file_done;
            }
            result = 0;
            importedSize += sizeof(WADBackupHeaderBlock);
            if (processCallback != 0) {
                processCallback(importedSize, contentDataSize + fileDataSize, FALSE);
            }
            if ((fileHeaderBuffer->flags[2] == NAND_TYPE_FILE) && (fileHeaderBuffer->fileSize != 0)) {
                result = NANDPrivateOpen(fileHeaderBuffer->name, &savedFile, NAND_ACCESS_READ);
                fileOpened = TRUE;
                if (result != 0) {
                    goto file_done;
                }
                byteCount = (fileHeaderBuffer->fileSize + 0x1F) & ~0x1F;
                while (byteCount != 0) {
                    if (byteCount > 0x10000) {
                        size = 0x10000;
                    } else {
                        size = byteCount;
                    }
                    length = NANDRead(&savedFile, encryptionBuffer, size);
                    if (((length + 0x1F) & ~0x1F) != size) {
                        result = -3005;
                        goto file_done;
                    }
                    result = 0;
                    result = ES_Encrypt(6, fileHeaderBuffer->iv, encryptionBuffer, size,
                                        outputBuffer);
                    if (result != 0) {
                        goto file_done;
                    }
                    result = SHA1Input(hashContext, outputBuffer, size);
                    if (result != 0) {
                        goto cleanup;
                    }
                    streamResult = WADWriteStream(&stream, outputBuffer, size);
                    if ((u32)streamResult != size) {
                        result = -3006;
                        goto file_done;
                    }
                    result = 0;
                    importedSize += size;
                    byteCount -= size;
                    if (processCallback != 0) {
                        processCallback(importedSize, contentDataSize + fileDataSize, FALSE);
                    }
                }
                result = NANDClose(&savedFile);
                fileOpened = FALSE;
                if (result != 0) {
                    goto file_done;
                }
                {
                    u32 roundedSize = (fileHeaderBuffer->fileSize + 0x1F) & ~0x1F;
                    size = ((roundedSize + 0x3F) & ~0x3F) - roundedSize;
                }
                if (size != 0) {
                    _WADRandPad(outputBuffer, size);
                    result = SHA1Input(hashContext, outputBuffer,
                                       size);
                    if (result != 0) {
                        goto cleanup;
                    }
                    streamResult = WADWriteStream(&stream, outputBuffer,
                                            size);
                    if ((u32)streamResult != size) {
                        result = -3006;
                        goto file_done;
                    }
                    result = 0;
                    importedSize += size;
                    result = 0;
                    if (processCallback != 0) {
                        processCallback(importedSize, contentDataSize + fileDataSize, FALSE);
                    }
                }
            } else if (fileHeaderBuffer->flags[2] == NAND_TYPE_FILE) {
                byteCount = 0;
            }
file_done:
            if (fileOpened) {
                NANDClose(&savedFile);
            }
            if (result != 0) {
                length = (fileHeaderBuffer->fileSize + 0x3F) & ~0x3F;
                totalSize -= length;
                headerBuffer->header.fileSize -= length;
                headerBuffer->header.numFiles--;
                streamResult = WADSeekStream(&stream, position, 0);
                if (streamResult != position) {
                    result = -3006;
                    goto cleanup;
                }
                result = 0;
            }
        }
    }
    position = WADSeekStream(&stream, 0, 1);
    if (position < 0 || (u32)(position - offset) != totalSize) {
        result = -3006;
        goto cleanup;
    }
    if (headerBuffer->header.backupAreaLen != totalSize + 0x340) {
        result = -3006;
        goto cleanup;
    }
    result = 0;
    result = SHA1Result(hashContext, digest);
    if (result != 0) {
        goto cleanup;
    }
    certificates = (struct WADExportCertificates*)outputBuffer;
    result = ES_Sign(digest, 0x14, signature, (ESCertSignature*)ROUNDUP((u32)&certificates->signer, 64));
    if (result != 0) {
        goto cleanup;
    }
    result = ES_GetDeviceCert((ESCertSignature*)ROUNDUP((u32)certificates->device, 64));
    if (result != 0) {
        goto cleanup;
    }
    streamResult = WADSeekStream(&stream, position, 0);
    if (streamResult != position) {
        result = -3006;
        goto cleanup;
    }
    result = 0;
    streamResult = WADWriteStream(&stream, signature, sizeof(signature));
    if (streamResult != (s32)sizeof(signature)) {
        result = -3006;
        goto cleanup;
    }
    result = 0;
    streamResult = WADWriteStream(&stream, (void*)ROUNDUP((u32)certificates->device, 64), sizeof(certificates->device));
    if (streamResult != (s32)sizeof(certificates->device)) {
        result = -3006;
        goto cleanup;
    }
    result = 0;
    streamResult = WADWriteStream(&stream, (ESCertSignature*)ROUNDUP((u32)&certificates->signer, 64), sizeof(certificates->signer));
    if (streamResult != (s32)sizeof(certificates->signer)) {
        result = -3006;
        goto cleanup;
    }
    result = 0;
    streamResult = WADSeekStream(&stream, offset, 0);
    if ((u32)streamResult != offset) {
        result = -3006;
        goto cleanup;
    }
    result = 0;
    streamResult = WADWriteStream(&stream, headerBuffer, sizeof(headerBlock));
    if ((u32)streamResult != sizeof(headerBlock)) {
        result = -3006;
        goto cleanup;
    }
    result = 0;
    if (sizeOut != 0) {
        *sizeOut = headerBuffer->header.backupAreaLen;
    }

cleanup:
    if (titleMetaBuffer != 0) {
        _WADMemFree(allocator, titleMetaBuffer);
    }
    if (outputBuffer != 0) {
        _WADMemFree(allocator, outputBuffer);
    }
    if (encryptionBuffer != 0) {
        _WADMemFree(allocator, encryptionBuffer);
    }
    if (files != 0) {
        _WADMemFree(allocator, files);
    }
    if (threadStack != 0) {
        _WADMemFree(allocator, threadStack);
    }
    if (streamOpened) {
        WADCloseStream(&stream);
    }
    if (contentExportStarted) {
        ES_ExportContentEnd(fileFd);
    }
    if (titleExportStarted) {
        ES_ExportTitleDone();
    }
    if (processCallback != 0) {
        processCallback(importedSize, contentDataSize + fileDataSize, TRUE);
    }
    return result;
}

static s32 _WADCheckContents(ESTmdView* titleMeta, ESContentMask* contentMask) {
    ESContentId installedContentIds[512] ALIGN32;
    u32 installedContentCount;
    s32 result;
    u32 contentIndex;

    if (ES_ListTitleContentsOnCard(titleMeta->head.titleId, 0, &installedContentCount) == ES_ERR_DONT_EXISTS) {
        result = -3002;
    } else {
        result = ES_ListTitleContentsOnCard(titleMeta->head.titleId, installedContentIds,
                                            &installedContentCount);
        if (result == 0) {
            memset(contentMask, 0, sizeof(*contentMask));
            for (contentIndex = 0; contentIndex < titleMeta->head.numContents; contentIndex++) {
                u32 installedIndex;

                if ((titleMeta->contents[contentIndex].type & 0x8000) == 0) {
                    for (installedIndex = 0; installedIndex < installedContentCount;
                         installedIndex++) {
                        if (installedContentIds[installedIndex] ==
                            titleMeta->contents[contentIndex].cid) {
                            contentMask->data[contentIndex >> 3] |= 1 << (contentIndex & 7);
                            break;
                        }
                    }
                    if (installedIndex == installedContentCount) {
                        if ((titleMeta->contents[contentIndex].type & 0x4000) == 0) {
                            result = -3002;
                            goto done;
                        }
                        result = 0;
                    }
                }
            }
        }
    }
done:
    return result;
}

#pragma dont_inline on
static void* _WADMemAlloc(MEMAllocator* allocator, u32 size) {
    s32 allocationKind;
    u32 heapType;
    void* buffer = 0;

    if ((allocator != 0) && (allocator->heap != 0)) {
        heapType = ((MEMiHeapHead*)allocator->heap)->magic;
        switch (heapType) {
        case 0x45585048:
            allocationKind = 0;
            break;
        case 0x46524D48:
            allocationKind = 1;
            break;
        case 0x554E5448:
            allocationKind = 2;
            break;
        default:
            allocationKind = 3;
            break;
        }

        switch (allocationKind) {
        case 0:
            buffer = MEMAllocFromExpHeapEx(allocator->heap, size, 0x40);
            break;
        case 1:
            buffer = MEMAllocFromFrmHeapEx(allocator->heap, size, 0x40);
            break;
        case 2:
        default:
            buffer = MEMAllocFromAllocator(allocator, size);
            if (((u32)buffer & 0x3F) != 0) {
                OSReport("%s: Memory Allocator must return 64B aligned memBlocks\n", __func__);
                MEMFreeToAllocator(allocator, buffer);
                buffer = 0;
            }
            break;
        }
    }
    return buffer;
}

static void _WADMemFree(MEMAllocator* allocator, void* buffer) {
    if ((allocator == 0) || (allocator->heap == 0) || (buffer == 0)) {
        return;
    }
    MEMFreeToAllocator(allocator, buffer);
}
#pragma dont_inline reset

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

extern const u8 ca_ppki[];
extern const u8 ms_ppki[];
extern const u8 ca_dpki[];
extern const u8 ms_dpki[];
extern s32 SHA1Reset(void* context);
extern s32 SHA1Result(void* context, void* digest);

s32 WADOpenStream(WADLocation location, const char* path, WADStream* stream, u32 write,
                  u32 offset) {
    stream->location = location;

    switch (location) {
    case WAD_LOCATION_CNT_DVD: {
        WADContentPath* contentPath = (WADContentPath*)path;
        s32 result;
        if (write != 0) {
            return -3004;
        } else {
            result = contentOpenDVD(contentPath->handle, contentPath->name,
                                    &stream->handle.contentDvd);
            if (result != 0) {
                return -3004;
            }
        }
        return 0;
    }

    case WAD_LOCATION_CNT_NAND: {
        WADContentPath* contentPath = (WADContentPath*)path;
        s32 result;
        if (write != 0) {
            return -3004;
        } else {
            result = contentOpenNAND(contentPath->handle, contentPath->name,
                                     &stream->handle.contentNand);
            if (result != 0) {
                return -3004;
            }
        }
        return 0;
    }

    case (WADLocation)0:
        if ((((u32)path + offset) & 0x3F) != 0) {
            return -3007;
        }
        stream->handle.memoryBase = (void*)((u32)path + offset);
        return 0;

    case WAD_LOCATION_DVD:
        {
            s32 result;
            if (write != 0) {
                return -3004;
            }
            if (!DVDOpen(path, &stream->handle.dvd)) {
                return -3004;
            }
            return 0;
        }

    case WAD_LOCATION_NAND:
        {
            s32 result;
            if (write != 0) {
                result = NANDPrivateOpen(path, &stream->handle.nand, NAND_ACCESS_RW);
                if (result == NAND_RESULT_NOEXISTS) {
                    result = NANDPrivateCreate(path, 0x3F, 0);
                    if (result != 0) {
                        return -3004;
                    }
                    result = NANDPrivateOpen(path, &stream->handle.nand, NAND_ACCESS_RW);
                }
                if (result != 0) {
                    return -3004;
                }
                result = NANDSeek(&stream->handle.nand, offset, NAND_SEEK_BEG);
                if (result == NAND_RESULT_INVALID) {
                    u8 zeroes[0x4000] ALIGN32;
                    u32 fileSize;

                    fileSize = NANDSeek(&stream->handle.nand, 0, NAND_SEEK_END);
                    if (fileSize >= offset) {
                        return -3004;
                    }
                    memset(zeroes, 0, sizeof(zeroes));
                    fileSize = offset - fileSize;
                    while (fileSize != 0) {
                        u32 writeSize;
                        writeSize = fileSize > sizeof(zeroes) ? sizeof(zeroes) : fileSize;
                        result = NANDWrite(&stream->handle.nand, zeroes, writeSize);
                        if ((u32)result != writeSize) {
                            return -3004;
                        }
                        fileSize -= writeSize;
                    }
                    result = NANDSeek(&stream->handle.nand, offset, NAND_SEEK_BEG);
                }
                return result != offset ? -3004 : 0;
            }
            result = NANDPrivateOpen(path, &stream->handle.nand, NAND_ACCESS_READ);
            return result != 0 ? -3004 : result;
        }

    case WAD_LOCATION_SD_CARD: {
        s32 result;
        if (write != 0) {
            stream->handle.fa = FAFopen(path, "r+");
            if (stream->handle.fa == 0) {
                stream->handle.fa = FACreate(path, 0);
            }
            if (stream->handle.fa == 0) {
                return -3004;
            }
            if (offset != 0) {
                result = WADSeekStream(stream, offset, 0);
                if ((u32)result != offset) {
                    return -3004;
                }
            } else {
                result = 0;
            }
        } else {
            stream->handle.fa = FAFopen(path, "r");
        }
        return stream->handle.fa == 0 ? -3004 : 0;
    }

    default:
        return -3000;
    }
}

size_t WADReadStream(WADStream* stream, void** buffer, size_t size, s32 offset) {
    size_t result;
    u32 alignedSize;

    if ((s32)size <= 0) {
        return 0;
    }
    if ((stream == 0) || (buffer == 0)) {
        return -3000;
    }
    alignedSize = (size + WAD_READ_ALIGNMENT - 1) & ~(WAD_READ_ALIGNMENT - 1);
    if (size != alignedSize) {
        return -3000;
    }

    switch (stream->location) {
    case WAD_LOCATION_CNT_DVD:
        return contentReadDVD(&stream->handle.contentDvd, *buffer, alignedSize, offset);

    case WAD_LOCATION_CNT_NAND:
        return contentReadNAND(&stream->handle.contentNand, *buffer, alignedSize, offset);

    case (WADLocation)0:
        memcpy(*buffer, (u8*)stream->handle.memoryBase + offset, size);
        return size;

    case WAD_LOCATION_DVD:
        return DVDReadPrio(&stream->handle.dvd, *buffer, alignedSize, offset, 2);

    case WAD_LOCATION_NAND:
        result = NANDSeek(&stream->handle.nand, offset, NAND_SEEK_BEG);
        if ((s32)result >= 0) {
            result = NANDRead(&stream->handle.nand, *buffer, alignedSize);
        }
        return result;

    case WAD_LOCATION_SD_CARD:
        if (stream->handle.fa == 0) {
            return -3000;
        }
        result = FAFseek(stream->handle.fa, offset, 0);
        if (result == 0) {
            return FAFread(*buffer, 1, size, stream->handle.fa);
        }
        return result;

    default:
        return -3000;
    }
}

void WADCloseStream(WADStream* stream) {
    if (stream == 0) {
        return;
    }
    switch (stream->location) {
    case WAD_LOCATION_CNT_DVD:
        contentCloseDVD(&stream->handle.contentDvd);
        return;
    case WAD_LOCATION_CNT_NAND:
        contentCloseNAND(&stream->handle.contentNand);
        return;
    case WAD_LOCATION_DVD:
        DVDClose(&stream->handle.dvd);
        return;
    case WAD_LOCATION_NAND:
        NANDClose(&stream->handle.nand);
        return;
    case WAD_LOCATION_SD_CARD:
        if (stream->handle.fa != 0) {
            FAFclose(stream->handle.fa);
        }
        return;
    default:
        return;
    }
}

s32 WADWriteStream(WADStream* stream, void* buffer, u32 size) {
    s32 result = size;
    if (stream == 0 || buffer == 0) {
        result = -3000;
    } else {
        switch (stream->location) {
        case (WADLocation)0:
            memcpy(stream->handle.memoryBase, buffer, size);
            break;
        case WAD_LOCATION_NAND:
            result = NANDWrite(&stream->handle.nand, buffer, size);
            break;
        case WAD_LOCATION_SD_CARD:
            if (stream->handle.fa == 0) {
                result = -3000;
            } else {
                result = FAFwrite(buffer, 1, size, stream->handle.fa);
            }
            break;
            case WAD_LOCATION_DVD:
        case WAD_LOCATION_CNT_DVD:
        case WAD_LOCATION_CNT_NAND:
    default:
            result = -3000;
            break;
        }
    }
    return result;
}

s32 WADSeekStream(WADStream* stream, u32 offset, s32 origin) {
    s32 result;
    WADFileInfoView info;
    if (stream == 0 || origin < 0 || origin > 2) {
        return -3000;
    }
    switch (stream->location) {
    case WAD_LOCATION_CNT_DVD:
        result = contentSeekDVD(&stream->handle.contentDvd, offset, origin);
        break;
    case WAD_LOCATION_CNT_NAND:
        result = contentSeekNAND(&stream->handle.contentNand, offset, origin);
        break;
    case WAD_LOCATION_NAND:
        result = NANDSeek(&stream->handle.nand, offset, origin);
        break;
    case WAD_LOCATION_SD_CARD:
        if (stream->handle.fa == 0) {
            return -3000;
        }
        result = FAFseek(stream->handle.fa, offset, origin);
        if (result != 0) {
            break;
        }
        result = FAFinfo(stream->handle.fa, &info.info);
        if (result == 0) {
            result = info.fields.fileSize;
        }
        break;
    case (WADLocation)0:
    case WAD_LOCATION_DVD:
    default:
        result = -3000;
        break;
    }
    return result;
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
    u32 titleMetaSize;

    if (backupHeader->wadVersion != 1) {
        return -3001;
    }
    if (backupHeader->hdrSize != sizeof(WADBackupHeader)) {
        return -3001;
    }
    /* Skipped metadata retains the incoming header address until an ES call replaces it. */
    result = (s32)header;
    if (backupHeader->contentSize != 0) {
        result = ES_GetDeviceId(&currentDeviceId);
        if (result != 0) {
            goto done;
        }
        if (currentDeviceId != backupHeader->deviceId) {
            return WAD_ERROR_INCORRECT_DEVICE;
        }
    }

    info->cidxMode = backupHeader->wadVersion;
    if (info->cidxMode >= 1) {
        info->contentIndex = &backupHeader->cidx;
    }
    info->fileNames = backupHeader->deviceMac;
    titleMetaSize = backupHeader->tmdSize;
    sectionOffset = (backupHeader->hdrSize + WAD_STREAM_ALIGNMENT - 1) &
                    ~(WAD_STREAM_ALIGNMENT - 1);

    if (titleMetaSize != 0) {
        if ((flags & 4) == 0) {
            info->sectionSize = titleMetaSize;
            info->sectionOffset = sectionOffset;
            alignedSize = WAD_ALIGN32(titleMetaSize);
            info->titleMeta = _WADMemAlloc(allocator, alignedSize);
            if (info->titleMeta == 0) {
                return -3003;
            }
            info->titleMetaSize = 1;
            result = WADReadStream(stream, (void**)&info->titleMeta, alignedSize,
                                   offset + info->sectionOffset);
            if (result != (s32)alignedSize) {
                return -3005;
            }
            result = 0;
        }
        sectionOffset += (backupHeader->tmdSize + WAD_STREAM_ALIGNMENT - 1) &
                         ~(WAD_STREAM_ALIGNMENT - 1);
        if ((flags & 2) != 0) {
            goto done;
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
                goto done;
            }
        }
    }
    result = 0;
done:
    return result;
}

#pragma dont_inline on
s32 _WADGetCidxCount(const ESContentMask* contentMask) {
    u32 bitIndex;
    s32 count = 0;

    for (bitIndex = 0; bitIndex < 512; bitIndex++) {
        if ((contentMask->data[bitIndex >> 3] & (1 << (bitIndex & 7))) != 0) {
            count++;
        }
    }
    return count;
}

static s32 _WADGetCidx(const ESContentMask* contentMask, u32 contentNumber) {
    s32 bitIndex;
    u32 remaining = contentNumber + 1;

    for (bitIndex = 0; bitIndex < 512; bitIndex++) {
        if ((contentMask->data[bitIndex >> 3] & (1 << (bitIndex & 7))) != 0) {
            remaining--;
        }
        if (remaining == 0) {
            return bitIndex;
        }
    }
    return -1;
}

static s32 _WADGetTransferId(void* transferId) {
    NANDFileInfo fileInfo;
    BOOL valid;
    s32 result;

    valid = FALSE;
    result = NANDPrivateOpen("/shared2/succession/transfer.id", &fileInfo, NAND_ACCESS_READ);
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

static s32 _WADBackupGetFiles(const char* directoryPath, u32 flags, MEMAllocator* allocator,
                              u32* fileCount, WADBackupFileHeader* files) {
    s32 result;
    NANDFileInfo fileInfo;
    char fullFilePath[NAND_MAX_PATH];
    char currentDirectory[NAND_MAX_PATH] ALIGN32;
    char noCopyPath[NAND_MAX_PATH];
    char bannerPath[NAND_MAX_PATH];
    NANDStatus status;
    u32 nameCount;
    u32 fileSize;
    u32 childFileCount;
    u8 fileType;
    WADBackupFileHeader* file = 0;
    char* nameList = 0;
    u32 totalFiles = 0;
    s32 nameIndex;
    char* name;
    BOOL absolutePaths = FALSE;

    if (allocator == 0 || fileCount == 0) {
        result = -3000;
        goto cleanup;
    }
    result = NANDGetCurrentDir(currentDirectory);
    if (result != 0) {
        goto cleanup;
    }
    if (directoryPath == 0) {
        directoryPath = ".";
    }
    result = NANDPrivateReadDir(directoryPath, 0, &nameCount);
    if (result == -1) {
        result = 0;
        goto cleanup;
    }
    if (result != 0 || nameCount == 0) {
        goto cleanup;
    }
    nameList = _WADMemAlloc(allocator, nameCount * 0x40);
    if (nameList == 0) {
        result = -3003;
        goto cleanup;
    }
    if (nameList == 0) {
        result = -3003;
        goto cleanup;
    }
    result = NANDPrivateReadDir(directoryPath, nameList, &nameCount);
    if (result != 0) {
        goto cleanup;
    }
    if ((flags & 4) == 0) {
        absolutePaths = TRUE;
    }
    if (files != 0) {
        file = files;
    }
    name = nameList;
    for (nameIndex = 0; nameIndex < nameCount;) {
        BOOL closeFile = FALSE;

        if (absolutePaths) {
            if (strcmp(directoryPath, ".") == 0) {
                snprintf(fullFilePath, sizeof(fullFilePath), "%s/%s", currentDirectory, name);
            } else {
                snprintf(fullFilePath, sizeof(fullFilePath), "%s/%s/%s", currentDirectory,
                         directoryPath, name);
            }
        } else {
            if (strcmp(directoryPath, ".") == 0) {
                snprintf(fullFilePath, sizeof(fullFilePath), "%s", name);
            } else {
                snprintf(fullFilePath, sizeof(fullFilePath), "%s/%s", directoryPath, name);
            }
        }
        result = NANDPrivateGetType(fullFilePath, &fileType);
        if (result != 0) {
            goto nextName;
        }
        if ((flags & 0x10) == 0) {
            if (absolutePaths && strcmp(directoryPath, ".") == 0) {
                snprintf(noCopyPath, sizeof(noCopyPath), "%s/%s", currentDirectory, "nocopy");
                snprintf(bannerPath, sizeof(bannerPath), "%s/%s", currentDirectory, "banner.bin");
                if (strcmp(fullFilePath, noCopyPath) == 0 && fileType == NAND_TYPE_DIR) {
                    goto nextName;
                }
                if (strcmp(fullFilePath, bannerPath) == 0 && fileType == NAND_TYPE_FILE) {
                    goto nextName;
                }
            } else {
                if (strcmp(fullFilePath, "nocopy") == 0 && fileType == NAND_TYPE_DIR) {
                    goto nextName;
                }
                if (strcmp(fullFilePath, "banner.bin") == 0 && fileType == NAND_TYPE_FILE) {
                    goto nextName;
                }
            }
        }
        if (fileType == NAND_TYPE_FILE) {
            result = NANDPrivateOpen(fullFilePath, &fileInfo, NAND_ACCESS_READ);
            closeFile = TRUE;
            if (result != 0) {
                goto nextName;
            }
            result = NANDGetLength(&fileInfo, &fileSize);
            if (result != 0) {
                goto nextName;
            }
            result = NANDClose(&fileInfo);
            closeFile = FALSE;
            if (result != 0) {
                goto nextName;
            }
        } else if (fileType == NAND_TYPE_DIR) {
            if ((flags & 8) == 0) {
                goto nextName;
            }
            fileSize = 0;
            if (files != 0) {
                file->fileSize = 0;
            }
        }
        result = NANDPrivateGetStatus(fullFilePath, &status);
        if (result != 0) {
            goto nextName;
        }
        if (files != 0) {
            file->magic = 0x3ADF17E;
            file->flags[0] = status.permission;
            file->flags[1] = status.attribute;
            file->flags[2] = fileType;
            file->fileSize = fileSize;
            strncpy(file->path, fullFilePath, 0x40);
        }
        totalFiles++;
        if (files != 0) {
            file++;
        }
        if (fileType == NAND_TYPE_DIR) {
            WADBackupFileHeader* children;
            childFileCount = 0;
            children = 0;
            if (files != 0) {
                children = file;
            }
            if (absolutePaths) {
                if (strcmp(directoryPath, ".") == 0) {
                    snprintf(fullFilePath, sizeof(fullFilePath), "%s", name);
                } else {
                    snprintf(fullFilePath, sizeof(fullFilePath), "%s/%s", directoryPath, name);
                }
            }
            result = _WADBackupGetFiles(fullFilePath, flags, allocator, &childFileCount, children);
            if (result != 0) {
                goto nextName;
            }
            if (childFileCount != 0) {
                if (files != 0) {
                    file += childFileCount;
                }
                totalFiles += childFileCount;
            }
        }
nextName:
        nameIndex++;
        name += strlen(name) + 1;
        if (closeFile) {
            NANDClose(&fileInfo);
        }
    }
cleanup:
    if (nameList != 0) {
        _WADMemFree(allocator, nameList);
    }
    if (result == 0 && fileCount != 0) {
        *fileCount = totalFiles;
    }
    return result;
}

static s32 _WADBackupGetSize(u32 flags, ESTmdView* titleMeta, ESContentMask* contentMask,
                             u32 fileCount, WADBackupFileHeader* files, u32* titleMetaSize,
                             u32* contentDataSize, u32* fileDataSize, u32* totalSize) {
    u32 titleSize = 0x80;
    u32 contentSize = 0;
    u32 contentIndex;
    u32 selectedCount;
    u32 filesSize;

    if ((titleMeta != 0) && (titleMetaSize != 0)) {
        if (((flags & 1) != 0) || ((flags & 0x20) != 0)) {
            s32 result = ES_GetTmdSizeFromView(titleMeta, titleMetaSize);
            if (result != 0) {
                return result;
            }
            titleSize += (*titleMetaSize + 0x3F) & ~0x3F;
        }
        if ((flags & 1) != 0) {
            selectedCount = _WADGetCidxCount(contentMask);
            for (contentIndex = 0; contentIndex < selectedCount; contentIndex++) {
                s32 tmdIndex = _WADGetCidx(contentMask, contentIndex);
                if ((tmdIndex < 0) || (tmdIndex >= titleMeta->head.numContents)) {
                    return -3009;
                }
                contentSize += ((u32)titleMeta->contents[tmdIndex].size + 0x3F) & ~0x3F;
            }
        }
    } else if ((titleMeta == 0) && (titleMetaSize != 0)) {
        *titleMetaSize = 0;
    }
    filesSize = 0;
    if (files != 0) {
        for (contentIndex = 0; contentIndex < fileCount; contentIndex++) {
            filesSize += 0x80;
            filesSize += (files[contentIndex].fileSize + 0x3F) & ~0x3F;
        }
    }
    titleSize += contentSize + filesSize;
    if (contentDataSize != 0) {
        *contentDataSize = contentSize;
    }
    if (fileDataSize != 0) {
        *fileDataSize = filesSize;
    }
    if (totalSize != 0) {
        *totalSize = titleSize;
    }
    return 0;
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

static void _WADRandPad(void* buffer, u32 size) {
    u8* words = buffer;
    u32 wordCount;
    u32 remainder;
    u32 wordIndex;

    if (size == 0) {
        return;
    }
    wordCount = size >> 2;
    remainder = size & 3;
    for (wordIndex = 0; wordIndex < wordCount; wordIndex++) {
        *(u32*)words = (((u32)rand() << 17) | ((u32)rand() << 2)) | (rand() & 3);
        words += sizeof(u32);
    }
    if (remainder != 0) {
        u8* tail = words;
        u8* randomBytes;
        u32 byteIndex;

        wordCount = (((u32)rand() << 17) | ((u32)rand() << 2)) | (rand() & 3);
        for (byteIndex = 0; byteIndex < remainder; byteIndex++) {
            randomBytes = (u8*)&wordCount;
            *tail++ = randomBytes[byteIndex];
        }
    }
}

static s32 WAD_815C43E0(WADHashThreadArgs* args) {
    void* context = args->context;
    s32 result = 0;
    u32 remaining = args->size;
    WADImportTransfer* transfer = args->transfer;
    u32 bufferIndex = 0;
    u32 size;

    for (; (remaining != 0) && (result == 0); bufferIndex ^= 1) {
        size = remaining > transfer->chunkSize ? transfer->chunkSize : remaining;
        OSLockMutex(&transfer->mutex[bufferIndex]);
        while (transfer->ready[bufferIndex] == 0) {
            OSWaitCond(&transfer->signalCond[bufferIndex], &transfer->mutex[bufferIndex]);
        }
        result = SHA1Input(context, transfer->buffers[bufferIndex], size);
        transfer->ready[bufferIndex] = 0;
        if (result != 0) {
            transfer->error = 1;
        }
        OSUnlockMutex(&transfer->mutex[bufferIndex]);
        OSSignalCond(&transfer->waitCond[bufferIndex]);
        remaining -= size;
    }
    return result;
}

static s32 _WADHash(WADStream* stream, u32 offset, u32 size, void* context, void* buffer,
                    u32 chunkSize, void* secondBuffer, void* threadStack, u32 threadStackSize) {
    OSMutex* mutex;
    s32 result;
    u32 completed = 0;
    void* readBuffer;
    u32 readSize;

    if (stream == 0 || context == 0 || buffer == 0) {
        result = -3000;
        goto done;
    }
    if (size != WAD_ALIGN32(size)) {
        result = -3000;
        goto done;
    }
    if (((u32)buffer & 0x1F) != 0) {
        result = -3007;
        goto done;
    }
    if (chunkSize != WAD_ALIGN32(chunkSize)) {
        result = -3000;
        goto done;
    }
    result = 0;
    if (!(secondBuffer != 0 && threadStack != 0)) {
        while (size != 0) {
            readSize = size > chunkSize ? chunkSize : size;
            readBuffer = buffer;
            result = WADReadStream(stream, &readBuffer, readSize, offset + completed);
            if ((u32)result != readSize) {
                result = -3005;
                goto done;
            }
            result = 0;
            result = SHA1Input(context, readBuffer, readSize);
            if (result != 0) {
                goto done;
            }
            completed += readSize;
            size -= readSize;
        }
    } else {
        WADImportTransfer transfer;
        WADHashThreadArgs args;
        OSThread thread;
        u32 bufferIndex;

        WAD_815C4A2C(&transfer, buffer, secondBuffer, chunkSize);
        args.context = context;
        args.size = size;
        args.transfer = &transfer;
        if (!OSCreateThread(&thread, (void* (*)(void*))WAD_815C43E0, &args,
                            (u8*)threadStack + threadStackSize, threadStackSize,
                            OSGetThreadPriority(OSGetCurrentThread()), 0)) {
            result = -3009;
            goto done;
        }
        OSResumeThread(&thread);
        bufferIndex = 0;
        while (size != 0 && transfer.error == 0) {
            readSize = size > chunkSize ? chunkSize : size;
            mutex = &transfer.mutex[bufferIndex];
            OSLockMutex(mutex);
            while (transfer.ready[bufferIndex] != 0 && transfer.error == 0) {
                OSWaitCond(&transfer.waitCond[bufferIndex], mutex);
            }
            if (transfer.error != 0) {
                OSUnlockMutex(mutex);
                break;
            }
            readBuffer = transfer.buffers[bufferIndex];
            result = WADReadStream(stream, &readBuffer, readSize, offset + completed);
            if ((u32)result != readSize) {
                OSLockMutex(&transfer.mutex[bufferIndex ^ 1]);
                OSCancelThread(&thread);
                OSJoinThread(&thread, 0);
                OSUnlockMutex(&transfer.mutex[bufferIndex ^ 1]);
                OSUnlockMutex(mutex);
                result = -3005;
                goto done;
            }
            transfer.ready[bufferIndex] = readSize;
            OSUnlockMutex(mutex);
            OSSignalCond(&transfer.signalCond[bufferIndex]);
            completed += readSize;
            size -= readSize;
            bufferIndex ^= 1;
        }
        if (!OSJoinThread(&thread, (void**)&result)) {
            return -3009;
        }
    }
done:
    return result;
}

s32 WADVerify(WADStream* stream, MEMAllocator* allocator, u32 offset, u32 size) {
    void* readBuffer ALIGN64 = 0;
    void* allocatedBuffer = 0;
    void* secondBuffer = 0;
    void* threadStack = 0;
    u8 digest[0x40] ALIGN64;
    u8 hashContext[0x60] ALIGN64;
    u32 signatureOffset;
    void* verificationBuffer = 0;
    WADBackupSignature* backupSignature;
    WADVerificationCertificateBundle* certificateBundle;
    s32 result;

    if (size != WAD_ALIGN32(size)) {
        result = -3000;
    } else if (size <= 0x340) {
        result = -3000;
    } else {
        allocatedBuffer = _WADMemAlloc(allocator, 0x8000);
        if (allocatedBuffer == 0) {
            result = -3003;
        } else if (((u32)allocatedBuffer & 0x3F) != 0) {
            result = -3007;
        } else {
            u32 hashSize = size - 0x340;

            signatureOffset = offset + hashSize;
            SHA1Reset(hashContext);
            result = _WADHash(stream, offset, hashSize, hashContext,
                              allocatedBuffer, 0x8000, secondBuffer, threadStack, 0x1000);
            if (result == 0) {
                result = SHA1Result(hashContext, digest);
                if (result == 0) {
                    readBuffer = allocatedBuffer;
                    if ((s32)WADReadStream(stream, &readBuffer, 0x340, signatureOffset) != 0x340) {
                        result = -3005;
                        goto cleanup;
                    }
                    verificationBuffer = _WADMemAlloc(allocator, 0xF80);
                    if (verificationBuffer == 0) {
                        result = -3003;
                        goto cleanup;
                    }
                    certificateBundle = verificationBuffer;
                    memcpy(certificateBundle->caProduction, ca_ppki, 0x400);
                    memcpy(certificateBundle->msProduction, ms_ppki, 0x240);
                    memcpy(certificateBundle->caDevelopment, ca_dpki, 0x400);
                    memcpy(certificateBundle->msDevelopment, ms_dpki, 0x240);
                    memcpy(certificateBundle->firstCertificate,
                           ((WADBackupSignature*)readBuffer)->firstCertificate, 0x180);
                    memcpy(certificateBundle->secondCertificate,
                           ((WADBackupSignature*)readBuffer)->secondCertificate, 0x180);
                    result = ES_VerifySign(digest, 0x14, readBuffer, verificationBuffer, 0xF80);
                }
            }
        }
    }

cleanup:

    if (allocatedBuffer != 0) {
        _WADMemFree(allocator, allocatedBuffer);
    }
    if (secondBuffer != 0) {
        _WADMemFree(allocator, secondBuffer);
    }
    if (threadStack != 0) {
        _WADMemFree(allocator, threadStack);
    }
    if (verificationBuffer != 0) {
        _WADMemFree(allocator, verificationBuffer);
    }
    return result;
}

#pragma dont_inline on
void WAD_815C4A2C(WADImportTransfer* transfer, void* firstBuffer, void* secondBuffer,
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
#pragma dont_inline reset

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

static s32 _WADVerifySavedataZD(WADSaveDataHeader* header, WADStream* stream,
                                MEMAllocator* allocator, u32 offset) {
    WADFileHeader* fileHeader = 0;
    void* encryptedData = 0;
    void* decryptedData = 0;
    NANDFileInfo fileInfo;
    s32 fileOpened = FALSE;
    s32 result;

    if (header->saveType != 1) {
        result = -3009;
        goto cleanup;
    }
    fileHeader = MEMAllocFromAllocator(allocator, sizeof(WADFileHeader));
    if (fileHeader == 0) {
        result = -3003;
        goto cleanup;
    }
    result = WADReadStream(stream, (void**)&fileHeader, sizeof(WADFileHeader), offset);
    if (result != sizeof(WADFileHeader)) {
        result = -3005;
        goto cleanup;
    }
    if (fileHeader->fileSize < 0x4000) {
        result = -3009;
        goto cleanup;
    }
    encryptedData = MEMAllocFromAllocator(allocator, 0x4000);
    decryptedData = MEMAllocFromAllocator(allocator, 0x4000);
    if ((encryptedData == 0) || (decryptedData == 0)) {
        result = -3003;
        goto cleanup;
    }
    memset(encryptedData, 0, 0x4000);
    memset(decryptedData, 0, 0x4000);
    if (strcmp(fileHeader->name, "zeldaTp.dat") == 0) {
        result = WADReadStream(stream, &encryptedData, 0x4000, offset + 0x80);
        if (result != 0x4000) {
            result = -3005;
            goto cleanup;
        }
        result = ES_Decrypt(6, fileHeader->iv, encryptedData, 0x4000, decryptedData);
        if (result != 0) {
            result = -3005;
            goto cleanup;
        }
        if (WADCheckSavedataZD(decryptedData) == 0) {
            result = -3009;
            goto cleanup;
        }
        result = NANDPrivateCreate(fileHeader->name, 0x34, 0);
        if (result != 0) {
            goto cleanup;
        }
        result = NANDPrivateOpen(fileHeader->name, &fileInfo, NAND_ACCESS_WRITE);
        if (result != 0) {
            goto cleanup;
        }
        fileOpened = TRUE;
        result = NANDWrite(&fileInfo, decryptedData, 0x4000);
        if (result != 0x4000) {
            result = -3006;
        } else {
            result = NANDClose(&fileInfo);
            if (result == 0) {
                fileOpened = FALSE;
            }
        }
    } else {
        result = -3009;
    }

cleanup:
    if (fileHeader != 0) {
        MEMFreeToAllocator(allocator, fileHeader);
    }
    if (encryptedData != 0) {
        MEMFreeToAllocator(allocator, encryptedData);
    }
    if (decryptedData != 0) {
        MEMFreeToAllocator(allocator, decryptedData);
    }
    if (fileOpened) {
        NANDClose(&fileInfo);
    }
    return result;
}

static s32 _WADCleanTmpDir(MEMAllocator* allocator) {
    s32 result;
    u32 fileCount = 0;
    char* names = 0;
    char* name;
    char filePath[NAND_MAX_PATH + 1] = {0};
    u32 fileIndex;

    result = NANDPrivateReadDir("/tmp", 0, &fileCount);
    if ((result == 0) && (fileCount != 0)) {
        names = MEMAllocFromAllocator(allocator, fileCount * 0x41);
        if (names != 0) {
            result = NANDPrivateReadDir("/tmp", names, &fileCount);
            if (result == 0) {
                name = names;
                for (fileIndex = 0; fileIndex < fileCount;) {
                    char* extension = strrchr(name, '.');
                    if ((extension != 0) && (strncmp(extension + 1, "app", 3) == 0)) {
                        sprintf(filePath, "/tmp/%s", name);
                        NANDPrivateDelete(filePath);
                        OSReport("%s:%d remove %s\n", __func__, 0x1777, filePath);
                    }
                    fileIndex++;
                    name += strlen(name) + 1;
                }
            }
        }
    }
    if (names != 0) {
        MEMFreeToAllocator(allocator, names);
    }
    return result;
}

s32 WADImportDVDForBS(const char* path, void* buffer, u32 bufferSize) {
    DVDFileInfo fileInfo;
    WADImportParts parts;
    WADHeader* header;
    u8* readBuffer;
    BOOL fileOpened = FALSE;
    ESTitleMeta* titleMeta = 0;
    void* applicationData;
    u32 paddedFileSize;
    u32 sectionOffset;
    u32 applicationSize;
    s32 result;

    if ((path == 0) || (buffer == 0)) {
        result = -3000;
        goto cleanup;
    }
    if (!DVDOpen(path, &fileInfo)) {
        return -3004;
    }
    fileOpened = TRUE;
    readBuffer = buffer;
    paddedFileSize = (fileInfo.length + 0x1F) & ~0x1F;
    if (paddedFileSize > bufferSize) {
        result = -3003;
        goto cleanup;
    }
    if (((s32)readBuffer % 0x40) != 0) {
        readBuffer += 0x20;
    }
    result = DVDReadPrio(&fileInfo, readBuffer, paddedFileSize, 0, 2);
    if ((u32)result != paddedFileSize) {
        result = -3005;
        goto cleanup;
    }

    memset(&parts, 0, sizeof(parts));
    header = (WADHeader*)readBuffer;
    result = WAD_815C2F44(header, &parts.type);
    if (result != 2) {
        OSReport("%s:%d Format should be iRD format: %s\n", __func__, 0x17D2,
                 path);
        result = -3000;
        goto cleanup;
    }
    if (parts.type == 3) {
        sectionOffset = (header->hdrSize + 0x3F) & ~0x3F;
        if (header->certSize != 0) {
            parts.certificateSize = header->certSize;
            parts.certificates = readBuffer + sectionOffset;
            sectionOffset += (header->certSize + 0x3F) & ~0x3F;
        }
        if (header->crlSize != 0) {
            parts.crlSize = header->crlSize;
            parts.crls = readBuffer + sectionOffset;
            sectionOffset += (header->crlSize + 0x3F) & ~0x3F;
        }
        if (header->ticketSize != 0) {
            parts.ticketSize = header->ticketSize;
            parts.ticket = readBuffer + sectionOffset;
            sectionOffset += (header->ticketSize + 0x3F) & ~0x3F;
        }
        if (header->tmdSize != 0) {
            parts.titleMetaSize = header->tmdSize;
            titleMeta = (ESTitleMeta*)(readBuffer + sectionOffset);
            parts.titleMeta = titleMeta;
            sectionOffset += (header->tmdSize + 0x3F) & ~0x3F;
        }
        applicationSize = ((u32)titleMeta->contents[0].size + 0xF) & ~0xF;
        applicationData = readBuffer + sectionOffset;
        if ((titleMeta != 0) && (titleMeta->head.titleId == ES_TITLE_ID(1, 1))) {
            result = ES_ImportBoot(parts.ticket, parts.certificates, parts.certificateSize,
                                   parts.titleMeta, parts.titleMetaSize, parts.certificates,
                                   parts.certificateSize, parts.crls, parts.crlSize, applicationData,
                                   applicationSize);
            if (result != 0) {
                OSReport("%s: Import Boot Failed: %d\n", __func__, result);
            } else {
                OSReport("%s: Import Boot Successful\n", __func__);
            }
        } else {
            OSReport("%s:%d This function only works for boot2 import.\n", __func__,
                     0x180D);
            result = -3000;
        }
    } else {
        OSReport("%s:%d This function only works for boot2 import.\n", __func__,
                 0x1814);
        result = -3000;
    }

cleanup:
    if (fileOpened) {
        DVDClose(&fileInfo);
    }
    return result;
}

s32 WADImportDVDExForBS(const char* path, void* buffer, u32 bufferSize) {
    WADHeader header ALIGN32;
    DVDFileInfo fileInfo;
    WADImportParts parts;
    BOOL fileOpened = FALSE;
    s32 result;
    u8* contentBuffer;
    u32 contentCount;
    ESTitleMeta* titleMeta;
    u8* readBuffer = buffer;
    u32 contentIndex;
    s32 sectionOffset;
    u32 remainingBufferSize;
    u32 size;
    ESContentMeta* contentMeta;
    s32 value;

    if ((path == 0) || (buffer == 0)) {
        result = -3000;
        goto cleanup;
    }
    result = 0;
    if (!DVDOpen(path, &fileInfo)) {
        return -3004;
    }
    fileOpened = TRUE;
    if (buffer == NULL) {
        result = -3003;
        goto cleanup;
    }
    if (((s32)readBuffer % 0x40) != 0) {
        readBuffer += 0x20;
        bufferSize -= 0x20;
    }
    value = DVDReadPrio(&fileInfo, &header, sizeof(header), 0, 2);
    if (value != sizeof(header)) {
        result = -3005;
        goto cleanup;
    }

    memset(&parts, 0, sizeof(parts));
    if (WAD_815C2F44(&header, &parts.type) != 2) {
        result = -3000;
        goto cleanup;
    }

    sectionOffset = (header.hdrSize + 0x3F) & ~0x3F;
    if (header.certSize != 0) {
        parts.certificateSize = header.certSize;
        parts.certificates = readBuffer + sectionOffset;
        sectionOffset += (header.certSize + 0x3F) & ~0x3F;
    }
    if (header.crlSize != 0) {
        parts.crlSize = header.crlSize;
        parts.crls = readBuffer + sectionOffset;
        sectionOffset += (header.crlSize + 0x3F) & ~0x3F;
    }
    if (header.ticketSize != 0) {
        parts.ticketSize = header.ticketSize;
        parts.ticket = readBuffer + sectionOffset;
        sectionOffset += (header.ticketSize + 0x3F) & ~0x3F;
    }
    if (header.tmdSize != 0) {
        parts.titleMetaSize = header.tmdSize;
        parts.titleMeta = readBuffer + sectionOffset;
        sectionOffset += (header.tmdSize + 0x3F) & ~0x3F;
    }
    if (header.contentSize != 0) {
        size = header.contentSize;
    }
    contentBuffer = readBuffer + sectionOffset;
    remainingBufferSize = bufferSize - sectionOffset;
    if ((u32)sectionOffset > bufferSize) {
        result = -3003;
        goto cleanup;
    }
    value = DVDReadPrio(&fileInfo, readBuffer, sectionOffset, 0, 2);
    if (value != sectionOffset) {
        result = -3005;
        goto cleanup;
    }
    if (parts.type == 3) {
        result = -3001;
        goto cleanup;
    }
    if (parts.ticket != 0) {
        result = ES_ImportTicket(parts.ticket, parts.certificates,
                                 parts.certificateSize, parts.crls,
                                 parts.crlSize, parts.type);
        if (result != 0) {
            goto cleanup;
        }
    }
    titleMeta = parts.titleMeta;
    if (titleMeta == 0) {
        goto cleanup;
    }
    if (parts.cidxMode >= 1) {
        contentCount = _WADGetCidxCount((ESContentMask*)&parts);
        if (contentCount > titleMeta->head.numContents) {
            goto cleanup;
        }
    } else {
        contentCount = titleMeta->head.numContents;
    }

    result = ES_ImportTitleInit(titleMeta, parts.titleMetaSize,
                                parts.certificates, parts.certificateSize,
                                parts.crls, parts.crlSize,
                                parts.type, 1);
    if (result != 0) {
        ES_ImportTitleCancel();
        goto cleanup;
    }

    contentIndex = 0;
    while (contentIndex < contentCount) {
        s32 titleContentIndex;

        if (parts.cidxMode >= 1) {
            titleContentIndex = _WADGetCidx((ESContentMask*)&parts,
                                            contentIndex);
            if ((titleContentIndex < 0) ||
                (titleContentIndex >= titleMeta->head.numContents)) {
                ES_ImportTitleCancel();
                goto cleanup;
            }
            contentMeta = &titleMeta->contents[titleContentIndex];
        } else {
            contentMeta = &titleMeta->contents[contentIndex];
        }
        value = ES_ImportContentBegin(titleMeta->head.titleId, contentMeta->cid);
        if (value < 0) {
            result = value;
            ES_ImportContentEnd(value);
            ES_ImportTitleCancel();
            goto cleanup;
        }

        size = ((u32)contentMeta->size + 0xF) & ~0xF;
        while (size != 0) {
            u32 chunkSize = size > remainingBufferSize ?
                            remainingBufferSize : size;
            u32 readSize;
            s32 readResult;

            readResult = DVDReadPrio(&fileInfo, contentBuffer, (chunkSize + 0x1F) & ~0x1F, sectionOffset, 2);
            readSize = (chunkSize + 0x1F) & ~0x1F;
            if ((u32)readResult != readSize) {
                result = -3005;
                ES_ImportContentEnd(value);
                ES_ImportTitleCancel();
                goto cleanup;
            }
            sectionOffset += readResult;
            result = ES_ImportContentData(value, contentBuffer, chunkSize);
            if (result < 0) {
                ES_ImportContentEnd(value);
                ES_ImportTitleCancel();
                goto cleanup;
            }
            size -= chunkSize;
        }
        sectionOffset = (sectionOffset + 0x3F) & ~0x3F;
        result = ES_ImportContentEnd(value);
        if (result != 0) {
            ES_ImportTitleCancel();
            goto cleanup;
        }
        contentIndex++;
    }

    result = ES_ImportTitleDone();
    if (result != 0) {
        ES_ImportTitleCancel();
    }

cleanup:
    if (fileOpened) {
        DVDClose(&fileInfo);
    }
    return result;
}
