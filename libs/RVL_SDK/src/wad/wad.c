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
    u32 magic;
    u32 fileSize;
    u8 flags[3];
    char name[0x40];
    u8 reserved_0x4b[5];
    u8 iv[0x10];
    u8 reserved_0x60[0x20];
} WADFileHeader;

typedef struct WADBootImportParts {
    s32 headerInfo[2];
    u32 certificateSize;
    void* certificates;
    u32 crlSize;
    void* crls;
    u32 ticketSize;
    void* ticket;
    u32 titleMetaSize;
    void* titleMeta;
} WADBootImportParts;

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
                             u32* contentDataSize, u32* totalSize);
static s32 _WADCheckContents(ESTmdView* titleMeta, ESContentMask* contentMask);
static void _WADRandPad(void* buffer, u32 size);
static s32 _WADVerifySavedataZD(WADSaveDataHeader* header, WADStream* stream,
                                MEMAllocator* allocator, u32 offset);
static void _WADCleanTmpDir(MEMAllocator* allocator);
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
    s32 fd = args->fd;
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
        while (transfer->ready[bufferIndex] == 0) {
            OSWaitCond(&transfer->signalCond[bufferIndex], mutex);
        }
        result = ES_ImportContentData(fd, transfer->buffers[bufferIndex], size);
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

s32 WADImportEx(char* path, MEMAllocator* allocator, WADLocation location, u32 offset, u32 flags,
                WADProcessCallback processCallback) {
    WADImportWorkspace workspace ALIGN32;
    WADSaveDataHeader wadHeader ALIGN32;
    WADFileHeader backupHeader ALIGN32;
    WADImportTransfer transfer;
    WADImportLoopArgs threadArgs;
    OSThread importThread;
    NANDFileInfo backupFile;
    NANDStatus fileStatus;
    NANDStatus updatedFileStatus;
    ESContentId* installedContentIds = 0;
    ESTitleMeta* installedTitleMeta = 0;
    ESContentMeta* matchingContents = 0;
    ESHash* sharedContentHashes = 0;
    void* firstBuffer = 0;
    void* secondBuffer = 0;
    WADThreadStack* threadStack = 0;
    void* wadHeaderBuffer = &wadHeader;
    void* fileHeaderBuffer = &backupHeader;
    u8 transferId[0x20] ALIGN32;
    u32 fileOffset = 0;
    u32 importedBytes = 0;
    u32 installedContentCount = 0;
    u32 installedTmdSize = 0;
    u32 sharedContentCount = 0;
    u32 contentCount = 0;
    u32 contentIndex;
    u32 listIndex;
    u32 sizeRemaining;
    u32 transferIdValue;
    s32 result = 0;
    s32 streamOpened = FALSE;
    s32 backupFileOpened = FALSE;
    s32 titleImportStarted = FALSE;
    s32 contentImportStarted = FALSE;
    s32 threadCreated = FALSE;
    s32 contentFd = 0;
    s32 importExistingTitle = TRUE;
    s32 existingTmdAvailable = FALSE;
    s32 fileReadResult;
    u32 importedContentCount = 0;
    u32 bufferIndex = 0;
    u32 callbackTotal = 0;
    u32 installedContentIndex = 0;
    u32 sharedContentIndex;
    u32 contentFileOffset;
    u32 pathFileIndex;
    s32 matchFound;
    s32 listResult;
    s32 titleVersion;
    u32 contentSize;
    u32 chunkSize;
    u32 readSize;
    u32 bootSize;
    u32 alignedSize;
    u32 callbackDone;
    u32 currentTitleId;
    u32 currentTitleVersion;
    u32 currentContentId;
    u32 importedFileCount;
    u32 savedataFileIndex;
    s32 importResult;
    u32 threadPriority;
    const char* functionName = "WADImportEx";

    memset(&workspace.unpackInfo, 0, sizeof(WADUnpackInfo));
    memset(&transfer, 0, sizeof(transfer));
    if ((path == 0) || (allocator == 0) || (allocator->heap == 0)) {
        result = -3000;
        goto cleanup;
    }
    if ((offset & 0x3F) != 0) {
        result = -3007;
        goto cleanup;
    }
    if (processCallback != 0) {
        processCallback(0, 0, FALSE);
    }
    result = WADOpenStream(location, path, &workspace.stream, 0, 0);
    streamOpened = TRUE;
    if (result != 0) {
        goto cleanup;
    }
    result = WADReadStream(&workspace.stream, &wadHeaderBuffer, sizeof(wadHeader), offset);
    if (result != sizeof(wadHeader)) {
        result = -3005;
        goto cleanup;
    }
    result = _WADUnpack(&wadHeader, &workspace.stream, &workspace.unpackInfo, allocator, offset,
                        flags, 0);
    if (result != 0) {
        goto cleanup;
    }
    importedBytes = workspace.unpackInfo.contentOffset;
    callbackTotal = workspace.unpackInfo.contentSize + workspace.unpackInfo.fileListSize;
    if (((flags & 8) != 0) && (workspace.unpackInfo.titleMeta != 0)) {
        if (workspace.unpackInfo.headerInfo != 2) {
            result = -3001;
            goto cleanup;
        }
        result = ES_GetTicketViews(workspace.unpackInfo.titleMeta->head.titleId, 0,
                                   &installedContentCount);
        if (result != 0) {
            goto cleanup;
        }
        if (installedContentCount == 0) {
            result = -1028;
            goto cleanup;
        }
    }
    if ((workspace.unpackInfo.titleMeta != 0) &&
        (((workspace.unpackInfo.size_0x18 == 1) &&
          (workspace.unpackInfo.size_0x0c == 1)) ||
         (workspace.unpackInfo.headerInfo == 3))) {
        bootSize = (workspace.unpackInfo.titleMetaSize + 0x0F) & ~0x0F;
        alignedSize = (bootSize + 0x1F) & ~0x1F;
        firstBuffer = _WADMemAlloc(allocator, alignedSize);
        if (firstBuffer == 0) {
            result = -3003;
            goto cleanup;
        }
        result = WADReadStream(&workspace.stream, &firstBuffer, alignedSize,
                               offset + importedBytes);
        if ((u32)result != alignedSize) {
            result = -3005;
            goto cleanup;
        }
        result = ES_ImportBoot(workspace.unpackInfo.buffer_0x34,
                               workspace.unpackInfo.buffer_0x14,
                               workspace.unpackInfo.size_0x0c,
                               workspace.unpackInfo.titleMeta,
                               workspace.unpackInfo.sectionSize,
                               workspace.unpackInfo.buffer_0x14,
                               workspace.unpackInfo.size_0x0c,
                               workspace.unpackInfo.buffer_0x24,
                               workspace.unpackInfo.size_0x1c, firstBuffer,
                               workspace.unpackInfo.titleMetaSize);
        goto cleanup;
    }
    if ((workspace.unpackInfo.titleMeta != 0) &&
        (workspace.unpackInfo.buffer_0x34 != 0)) {
        result = ES_ImportTicket(workspace.unpackInfo.buffer_0x34,
                                 workspace.unpackInfo.buffer_0x14,
                                 workspace.unpackInfo.size_0x0c,
                                 workspace.unpackInfo.buffer_0x24,
                                 workspace.unpackInfo.size_0x1c, 0);
        if (result != 0) {
            goto cleanup;
        }
    }
    if (processCallback != 0) {
        processCallback(0, callbackTotal, FALSE);
    }
    if (workspace.unpackInfo.titleMeta != 0) {
        if (workspace.unpackInfo.cidxMode == 0) {
            contentCount = workspace.unpackInfo.titleMeta->head.numContents;
        } else {
            contentCount = _WADGetCidxCount(workspace.unpackInfo.contentIndex);
            if (workspace.unpackInfo.titleMeta->head.numContents < contentCount) {
                result = -3001;
                goto cleanup;
            }
        }
        result = ES_ListTmdContentsOnCard(workspace.unpackInfo.titleMeta,
                                          workspace.unpackInfo.sectionSize, 0,
                                          &installedContentCount);
        if ((result == 0) && (installedContentCount != 0)) {
            installedContentIds = _WADMemAlloc(allocator, installedContentCount * sizeof(ESContentId));
            if (installedContentIds == 0) {
                result = -3003;
                goto cleanup;
            }
            result = ES_ListTmdContentsOnCard(workspace.unpackInfo.titleMeta,
                                              workspace.unpackInfo.sectionSize,
                                              installedContentIds, &installedContentCount);
            if ((result == 0) &&
                (ES_GetTmd(workspace.unpackInfo.titleMeta->head.titleId, 0,
                           &installedTmdSize) == 0)) {
                alignedSize = (installedTmdSize + 0x1F) & ~0x1F;
                installedTitleMeta = _WADMemAlloc(allocator, alignedSize);
                if (installedTitleMeta == 0) {
                    result = -3003;
                    goto cleanup;
                }
                result = ES_GetTmd(workspace.unpackInfo.titleMeta->head.titleId,
                                   installedTitleMeta, &installedTmdSize);
                if (result == 0) {
                    importExistingTitle = FALSE;
                }
            }
        }
        if (!importExistingTitle && (installedContentCount != 0)) {
            matchingContents = _WADMemAlloc(allocator, installedContentCount * sizeof(ESContentMeta));
            if (matchingContents == 0) {
                result = -3003;
                goto cleanup;
            }
            installedContentIndex = 0;
            for (listIndex = 0; listIndex < installedContentCount; listIndex++) {
                for (contentIndex = 0;
                     contentIndex < installedTitleMeta->head.numContents; contentIndex++) {
                    if (installedContentIds[listIndex] ==
                        installedTitleMeta->contents[contentIndex].cid) {
                        memcpy(&matchingContents[installedContentIndex],
                               &installedTitleMeta->contents[contentIndex], sizeof(ESContentMeta));
                        installedContentIndex++;
                    }
                }
            }
        }
        result = ES_ListSharedContents(&sharedContentCount, 0);
        if (result == 0) {
            alignedSize = (sharedContentCount * sizeof(ESHash) + 0x1F) & ~0x1F;
            sharedContentHashes = _WADMemAlloc(allocator, alignedSize);
            if ((sharedContentHashes == 0) && (sharedContentCount != 0)) {
                result = -3003;
                goto cleanup;
            }
            result = ES_ListSharedContents(&sharedContentCount, sharedContentHashes);
            if ((result != 0) && (sharedContentHashes != 0)) {
                _WADMemFree(allocator, sharedContentHashes);
                sharedContentHashes = 0;
            }
        }
        result = ES_ImportTitleInit(workspace.unpackInfo.titleMeta,
                                    workspace.unpackInfo.sectionSize,
                                    workspace.unpackInfo.buffer_0x14,
                                    workspace.unpackInfo.size_0x0c,
                                    workspace.unpackInfo.buffer_0x24,
                                    workspace.unpackInfo.size_0x1c,
                                    workspace.unpackInfo.headerInfo, 1);
        if (result != 0) {
            goto cleanup;
        }
        titleImportStarted = TRUE;
        if ((flags & 2) == 0) {
            for (contentIndex = 0; contentIndex < contentCount; contentIndex++) {
                ESContentMeta* content;
                s32 titleMetaIndex = contentIndex;
                matchFound = FALSE;
                if (workspace.unpackInfo.cidxMode != 0) {
                    titleMetaIndex = _WADGetCidx(workspace.unpackInfo.contentIndex, contentIndex);
                    if ((titleMetaIndex < 0) ||
                        ((s32)workspace.unpackInfo.titleMeta->head.numContents <= titleMetaIndex)) {
                        result = -3001;
                        goto cleanup;
                    }
                }
                content = &workspace.unpackInfo.titleMeta->contents[titleMetaIndex];
                if (!importExistingTitle) {
                    for (listIndex = 0; listIndex < installedContentCount; listIndex++) {
                        ESContentMeta* installedContent = &matchingContents[listIndex];
                        if ((content->cid == installedContent->cid) &&
                            (memcmp(content->hash, installedContent->hash, sizeof(ESHash)) == 0) &&
                            (content->type == installedContent->type)) {
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
                if (matchFound) {
                    importedBytes += (content->size + 0x0F) & ~0x0F;
                    if (processCallback != 0) {
                        processCallback(importedBytes - workspace.unpackInfo.contentOffset,
                                        callbackTotal, FALSE);
                    }
                } else {
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
                    contentFd = ES_ImportContentBegin(
                        workspace.unpackInfo.titleMeta->head.titleId, content->cid);
                    result = contentFd;
                    if (contentFd < 0) {
                        goto cleanup;
                    }
                    contentImportStarted = TRUE;
                    sizeRemaining = (content->size + 0x0F) & ~0x0F;
                    WAD_815C4A2C(&transfer, firstBuffer, secondBuffer, 0x10000);
                    threadArgs.fd = contentFd;
                    threadArgs.transfer = &transfer;
                    threadArgs.size = sizeRemaining;
                    threadPriority = OSGetThreadPriority(OSGetCurrentThread());
                    threadCreated = OSCreateThread(&importThread,
                                                   (void* (*)(void*))WAD_815BFFA8,
                                                   &threadArgs,
                                                   &threadStack->bytes[sizeof(threadStack->bytes)],
                                                   sizeof(threadStack->bytes),
                                                   threadPriority, 0);
                    if (!threadCreated) {
                        result = -3009;
                        goto cleanup;
                    }
                    OSResumeThread(&importThread);
                    transfer.error = 0;
                    bufferIndex = 0;
                    while ((sizeRemaining != 0) && (transfer.error == 0)) {
                        chunkSize = sizeRemaining;
                        if (transfer.chunkSize < chunkSize) {
                            chunkSize = transfer.chunkSize;
                        }
                        OSLockMutex(&transfer.mutex[bufferIndex]);
                        while ((transfer.ready[bufferIndex] != 0) &&
                               (transfer.error == 0)) {
                            OSWaitCond(&transfer.waitCond[bufferIndex],
                                       &transfer.mutex[bufferIndex]);
                        }
                        if (transfer.error != 0) {
                            break;
                        }
                        readSize = (chunkSize + 0x1F) & ~0x1F;
                        result = WADReadStream(&workspace.stream,
                                               &transfer.buffers[bufferIndex], readSize,
                                               offset + importedBytes);
                        if ((u32)result != readSize) {
                            OSLockMutex(&transfer.mutex[bufferIndex ^ 1]);
                            OSCancelThread(&importThread);
                            OSJoinThread(&importThread, 0);
                            OSUnlockMutex(&transfer.mutex[bufferIndex ^ 1]);
                            OSUnlockMutex(&transfer.mutex[bufferIndex]);
                            result = -3005;
                            goto cleanup;
                        }
                        transfer.ready[bufferIndex] = chunkSize;
                        OSUnlockMutex(&transfer.mutex[bufferIndex]);
                        OSSignalCond(&transfer.signalCond[bufferIndex]);
                        importedBytes += chunkSize;
                        sizeRemaining -= chunkSize;
                        if (processCallback != 0) {
                            processCallback(importedBytes - workspace.unpackInfo.contentOffset,
                                            callbackTotal, FALSE);
                        }
                        bufferIndex ^= 1;
                    }
                    if (threadCreated) {
                        importResult = OSJoinThread(&importThread, (void**)&result);
                        if (!importResult) {
                            result = -3009;
                            goto cleanup;
                        }
                        threadCreated = FALSE;
                    }
                    if ((result != 0) || (transfer.error != 0)) {
                        goto cleanup;
                    }
                    result = ES_ImportContentEnd(contentFd);
                    if (result != 0) {
                        goto cleanup;
                    }
                    contentImportStarted = FALSE;
                }
                if (workspace.unpackInfo.type == 2) {
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
    if (((flags & 2) != 0) || (workspace.unpackInfo.fileListSize == 0) ||
        (workspace.unpackInfo.fileCount == 0)) {
        goto cleanup;
    }
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
    fileOffset = workspace.unpackInfo.fileOffset;
    if (((wadHeader.magic & 0xFFFFFF00) == 0x525A4400) &&
        (wadHeader.fileSize == 0x10000)) {
        result = _WADVerifySavedataZD(&wadHeader, &workspace.stream, allocator,
                                      offset + workspace.unpackInfo.fileOffset);
        goto cleanup;
    }
    for (pathFileIndex = 0; pathFileIndex < workspace.unpackInfo.fileCount; pathFileIndex++) {
        result = WADReadStream(&workspace.stream, &fileHeaderBuffer, sizeof(backupHeader),
                               offset + fileOffset);
        if (result != sizeof(backupHeader)) {
            result = -3005;
            goto cleanup;
        }
        fileOffset = (fileOffset + 0xBF) & ~0x3F;
        if (backupHeader.magic != 0x3ADF17E) {
            result = -3000;
            goto cleanup;
        }
        result = 0;
        if (_WADCanImportFile(&backupHeader, transferIdValue,
                              workspace.unpackInfo.fileNames, transferId) == 0) {
            if ((backupHeader.flags[2] == 1) && (backupHeader.fileSize != 0)) {
                fileOffset = (fileOffset + backupHeader.fileSize + 0x3F) &
                             ~0x3F;
            }
            continue;
        }
        if (backupHeader.flags[2] == 1) {
            result = NANDPrivateCreate(backupHeader.name, backupHeader.flags[0] | 0x20,
                                       backupHeader.flags[1]);
            if (result != 0) {
                goto cleanup;
            }
            if (backupHeader.fileSize != 0) {
                result = NANDPrivateOpen(backupHeader.name, &backupFile, 2);
                if (result != 0) {
                    goto cleanup;
                }
                backupFileOpened = TRUE;
                sizeRemaining = backupHeader.fileSize;
                while (sizeRemaining != 0) {
                    chunkSize = sizeRemaining;
                    if (chunkSize > 0x10000) {
                        chunkSize = 0x10000;
                    }
                    result = WADReadStream(&workspace.stream, &firstBuffer,
                                           (chunkSize + 0x1F) & ~0x1F,
                                           offset + fileOffset);
                    readSize = (chunkSize + 0x1F) & ~0x1F;
                    if ((u32)result != readSize) {
                        result = -3005;
                        goto cleanup;
                    }
                    result = ES_Decrypt(6, backupHeader.iv,
                                        firstBuffer, readSize, secondBuffer);
                    if (result != 0) {
                        goto cleanup;
                    }
                    result = NANDWrite(&backupFile, secondBuffer, chunkSize);
                    if ((u32)result != chunkSize) {
                        result = -3006;
                        goto cleanup;
                    }
                    importedBytes += chunkSize;
                    sizeRemaining -= chunkSize;
                    if (processCallback != 0) {
                        processCallback(workspace.unpackInfo.fileListSize +
                                            importedBytes - workspace.unpackInfo.fileOffset,
                                        callbackTotal, FALSE);
                    }
                    fileOffset += chunkSize;
                }
                result = NANDClose(&backupFile);
                if (result != 0) {
                    goto cleanup;
                }
                backupFileOpened = FALSE;
            }
            if ((backupHeader.flags[0] & 0x20) == 0) {
                result = NANDPrivateGetStatus(backupHeader.name, &fileStatus);
                if (result != 0) {
                    goto cleanup;
                }
                updatedFileStatus = fileStatus;
                updatedFileStatus.permission = backupHeader.flags[0];
                updatedFileStatus.attribute = backupHeader.flags[1];
                result = NANDPrivateSetStatus(backupHeader.name, &updatedFileStatus);
                if (result != 0) {
                    goto cleanup;
                }
            }
        } else if (backupHeader.flags[2] == 2) {
            result = NANDPrivateCreateDir(backupHeader.name,
                                          backupHeader.flags[0] | 0x20,
                                          backupHeader.flags[1]);
            if (result != -6) {
                if (result != 0) {
                    goto cleanup;
                }
            } else {
                result = NANDPrivateGetStatus(backupHeader.name, &fileStatus);
                if (result != 0) {
                    goto cleanup;
                }
                if ((fileStatus.permission & 0x20) == 0) {
                    fileStatus.permission = backupHeader.flags[0] | 0x20;
                    fileStatus.attribute = backupHeader.flags[1];
                    result = NANDPrivateSetStatus(backupHeader.name, &fileStatus);
                    if (result != 0) {
                        goto cleanup;
                    }
                }
            }
        }
        fileOffset = (fileOffset + 0x3F) & ~0x3F;
        if ((backupHeader.fileSize == 0) && (processCallback != 0)) {
            processCallback(workspace.unpackInfo.fileListSize +
                                importedBytes - workspace.unpackInfo.fileOffset,
                            callbackTotal, FALSE);
        }
        fileOffset += backupHeader.fileSize;
        fileOffset = (fileOffset + 0x3F) & ~0x3F;
    }
    fileOffset = workspace.unpackInfo.fileOffset;
    for (savedataFileIndex = 0; savedataFileIndex < workspace.unpackInfo.fileCount;
         savedataFileIndex++) {
        fileReadResult = WADReadStream(&workspace.stream, &fileHeaderBuffer,
                                       sizeof(backupHeader),
                                       offset + fileOffset);
        if (fileReadResult != sizeof(backupHeader)) {
            result = -3005;
            break;
        }
        result = 0;
        fileOffset = (fileOffset + 0xBF) & ~0x3F;
        if ((_WADCanImportFile(&backupHeader, transferIdValue,
                               workspace.unpackInfo.fileNames, transferId) != 0) &&
            (((result = NANDPrivateGetStatus(backupHeader.name, &fileStatus)) !=
                  0) ||
             ((backupHeader.flags[0] & 0x20) == 0 &&
              ((fileStatus.permission = backupHeader.flags[0]),
               (result = NANDPrivateSetStatus(backupHeader.name, &fileStatus)) !=
                   0)))) {
            break;
        }
        fileOffset = (fileOffset + backupHeader.fileSize + 0x3F) & ~0x3F;
    }

cleanup:
    _WADFreeMemory(&workspace.unpackInfo, allocator);
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
        WADCloseStream(&workspace.stream);
    }
    if (contentImportStarted) {
        ES_ImportContentEnd(contentFd);
        OSReport("%s:%d Cancel importing the content.\n", functionName, 0x8DF);
    }
    if (titleImportStarted) {
        ES_ImportTitleCancel();
        _WADCleanTmpDir(allocator);
        OSReport("%s:%d Cancel importing the title.\n", functionName, 0x8E6);
    }
    if (processCallback != 0) {
        if (importedBytes == 0) {
            processCallback(0, 0, TRUE);
        } else if ((callbackTotal == 0) || (workspace.unpackInfo.fileCount == 0)) {
            processCallback(importedBytes - workspace.unpackInfo.contentOffset, callbackTotal,
                            TRUE);
        } else {
            processCallback(workspace.unpackInfo.fileListSize +
                                importedBytes - workspace.unpackInfo.fileOffset,
                            callbackTotal, TRUE);
        }
    }
    return result;
}

static s32 WAD_815C1288(WADExportLoopArgs* args) {
    s32 result;
    u32 remaining;
    u32 bufferIndex;
    ESFd fd;
    WADImportTransfer* transfer;
    u32 size;
    OSMutex* mutex;

    fd = args->fd;
    result = 0;
    remaining = args->size;
    bufferIndex = 0;
    transfer = args->transfer;

    while ((remaining != 0) && (result == 0)) {
        size = remaining;

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

s32 WADBackupEx(u64 titleId, u32 ticketId, MEMAllocator* allocator, char* path, u32* sizeOut,
                WADLocation location, u32 offset, WADProcessCallback processCallback) {
    WADBackupTitleMetaBuffer* titleMetaBuffer = 0;
    ESTmdView* titleMeta = 0;
    WADBackupFileHeader* files = 0;
    WADStream stream ALIGN32;
    WADImportTransfer transfer;
    WADExportLoopArgs threadArgs;
    OSThread exportThread;
    NANDFileInfo savedFile ALIGN32;
    WADBackupHeaderBlock headerBlock ALIGN32;
    ESContentMask existingContentMask ALIGN32;
    ESContentId installedContentIds[520] ALIGN32;
    u8 hashContext[0xC0] ALIGN32;
    u8 digest[0x40] ALIGN32;
    u8 signature[0x40] ALIGN32;
    u8 deviceCertificate[0x180] ALIGN32;
    ESCertSignature signerCertificate ALIGN32;
    u8 encryptionIv[0x10] ALIGN32;
    void* outputBuffer = 0;
    void* encryptionBuffer = 0;
    WADThreadStack* threadStack = 0;
    u32 flags = ticketId;
    u32 titleMetaSize = 0;
    u32 contentDataSize = 0;
    u32 fileDataSize = 0;
    u32 fileCount = 0;
    u32 installedContentCount = 0;
    u32 currentContentCount = 0;
    u32 fileIndex;
    u32 contentIndex;
    u32 importedSize = 0;
    u32 paddedSize;
    u32 transferId = 0;
    u32 totalSize;
    u32 priority;
    u32 sizeRemaining;
    u32 bufferIndex;
    u32 chunkSize;
    u32 readSize;
    s32 result = 0;
    s32 streamOpened = FALSE;
    s32 titleExportStarted = FALSE;
    s32 contentExportStarted = FALSE;
    s32 threadCreated = FALSE;
    s32 fileOpened = FALSE;
    s32 fileFd;
    u32 callbackDone = 0;

    if (flags == 0) {
        flags = 0x0F;
    }
    memset(&transfer, 0, sizeof(transfer));
    memset(&headerBlock, 0, sizeof(headerBlock));
    memset(&existingContentMask, 0, sizeof(existingContentMask));
    memset(encryptionIv, 0, sizeof(encryptionIv));
    if (((flags & 3) == 0) || ((u32)(titleId >> 32) == 1) ||
        (allocator == 0) || (sizeOut == 0)) {
        result = -3000;
        goto cleanup;
    }
    if ((offset & 0x3F) != 0) {
        result = -3007;
        goto cleanup;
    }
    if (processCallback != 0) {
        processCallback(0, 0, FALSE);
    }
    if (((flags & 1) != 0) || ((flags & 0x20) != 0)) {
        result = ES_GetTmdView(titleId, 0, &titleMetaSize);
        if (result != 0) {
            goto cleanup;
        }
        titleMetaBuffer = _WADMemAlloc(allocator, sizeof(WADBackupTitleMetaBuffer));
        if (titleMetaBuffer == 0) {
            result = -3003;
            goto cleanup;
        }
        titleMeta = &titleMetaBuffer->view;
        result = ES_GetTmdView(titleId, titleMeta, &titleMetaSize);
        if (result != 0) {
            goto cleanup;
        }
    }
    if ((flags & 1) != 0) {
        result = ES_ListTitleContentsOnCard(titleId, 0, &installedContentCount);
        if (result == -106) {
            result = -3002;
            goto cleanup;
        }
        if ((result != 0) || (installedContentCount == 0)) {
            result = -3002;
            goto cleanup;
        }
        result = ES_ListTitleContentsOnCard(titleId, installedContentIds,
                                            &installedContentCount);
        if (result != 0) {
            goto cleanup;
        }
        result = _WADCheckContents(titleMeta, &existingContentMask);
        if (result != 0) {
            goto cleanup;
        }
    }
    if ((flags & 2) != 0) {
        char currentDirectory[NAND_MAX_PATH] ALIGN32;
        result = NANDGetCurrentDir(currentDirectory);
        if (result != 0) {
            goto cleanup;
        }
        result = _WADBackupGetFiles(0, flags, allocator, &fileCount, 0);
        if (result != 0) {
            goto cleanup;
        }
        if (fileCount != 0) {
            files = _WADMemAlloc(allocator, fileCount * sizeof(WADBackupFileHeader));
            if (files == 0) {
                result = -3003;
                goto cleanup;
            }
            result = _WADBackupGetFiles(0, flags, allocator, &fileCount, files);
            if (result != 0) {
                goto cleanup;
            }
        }
    }
    result = _WADBackupGetSize(flags, titleMeta, &existingContentMask, fileCount, files,
                               &titleMetaSize, &contentDataSize, &fileDataSize);
    if (result != 0) {
        goto cleanup;
    }
    if ((contentDataSize == 0) && (fileDataSize == 0)) {
        result = -3002;
        goto cleanup;
    }
    totalSize = titleMetaSize + contentDataSize + fileDataSize + 0x340;
    if (path == 0) {
        *sizeOut = totalSize;
        result = 0;
        goto cleanup;
    }
    outputBuffer = _WADMemAlloc(allocator, 0x10000);
    if (outputBuffer == 0) {
        result = -3003;
        goto cleanup;
    }
    if (processCallback != 0) {
        processCallback(0, contentDataSize + fileDataSize, FALSE);
    }
    result = WADOpenStream(location, path, &stream, 1, offset);
    streamOpened = TRUE;
    if (result != 0) {
        goto cleanup;
    }
    headerBlock.header.hdrSize = sizeof(WADBackupHeader);
    headerBlock.header.wadType[0] = 'B';
    headerBlock.header.wadType[1] = 'k';
    headerBlock.header.wadVersion = 1;
    headerBlock.header.numFiles = fileCount;
    headerBlock.header.fileSize = fileDataSize;
    headerBlock.header.tmdSize = titleMetaSize;
    headerBlock.header.contentSize = contentDataSize;
    headerBlock.header.backupAreaLen = titleMetaSize + contentDataSize + fileDataSize;
    headerBlock.header.titleId = titleId;
    result = ES_GetDeviceId(&headerBlock.header.deviceId);
    if (result != 0) {
        goto cleanup;
    }
    if ((flags & 1) != 0) {
        headerBlock.header.cidx = existingContentMask;
    }
    result = WADWriteStream(&stream, &headerBlock, sizeof(headerBlock));
    if (result != sizeof(headerBlock)) {
        result = -3006;
        goto cleanup;
    }
    importedSize = sizeof(headerBlock);
    result = SHA1Reset(hashContext);
    if (result != 0) {
        goto cleanup;
    }
    result = SHA1Input(hashContext, &headerBlock, sizeof(headerBlock));
    if (result != 0) {
        goto cleanup;
    }
    srand(ticketId);
    if (((flags & 1) != 0) || ((flags & 0x20) != 0)) {
        result = ES_ExportTitleInit(titleId, headerBlock.header.deviceId, 0, (void*)2, 0, 0, 0,
                                    0, 0, 0, 0);
        if (result != 0) {
            goto cleanup;
        }
        titleExportStarted = TRUE;
        paddedSize = (titleMetaSize + 0x3F) & ~0x3F;
        _WADRandPad(&titleMetaBuffer->data[titleMetaSize],
                    paddedSize - titleMetaSize);
        result = SHA1Input(hashContext, titleMeta, paddedSize);
        if (result != 0) {
            goto cleanup;
        }
        result = WADWriteStream(&stream, titleMeta, paddedSize);
        if ((u32)result != paddedSize) {
            result = -3006;
            goto cleanup;
        }
        importedSize += paddedSize;
    }
    if ((flags & 1) != 0) {
        encryptionBuffer = _WADMemAlloc(allocator, 0x10000);
        if (encryptionBuffer == 0) {
            result = -3003;
            goto cleanup;
        }
        threadStack = _WADMemAlloc(allocator, sizeof(WADThreadStack));
        if (threadStack == 0) {
            result = -3003;
            goto cleanup;
        }
        currentContentCount = _WADGetCidxCount(&existingContentMask);
        for (contentIndex = 0; contentIndex < currentContentCount; contentIndex++) {
            s32 tmdIndex = _WADGetCidx(&existingContentMask, contentIndex);
            ESContentMeta* content;
            if ((tmdIndex < 0) || (titleMeta->head.numContents <= tmdIndex)) {
                result = -3009;
                goto cleanup;
            }
            content = (ESContentMeta*)&titleMeta->contents[tmdIndex];
            fileFd = ES_ExportContentBegin(titleId, content->cid);
            result = fileFd;
            if (fileFd < 0) {
                goto cleanup;
            }
            contentExportStarted = TRUE;
            sizeRemaining = (content->size + 0x0F) & ~0x0F;
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
            sizeRemaining = (sizeRemaining + 0x3F) & ~0x3F;
            bufferIndex = 0;
            while ((sizeRemaining != 0) && (transfer.error == 0)) {
                chunkSize = sizeRemaining;
                if (transfer.chunkSize < chunkSize) {
                    chunkSize = transfer.chunkSize;
                }
                OSLockMutex(&transfer.mutex[bufferIndex]);
                while ((transfer.ready[bufferIndex] == 0) && (transfer.error == 0)) {
                    OSWaitCond(&transfer.waitCond[bufferIndex], &transfer.mutex[bufferIndex]);
                }
                if (transfer.error != 0) {
                    break;
                }
                readSize = (chunkSize + 0x3F) & ~0x3F;
                if (readSize > chunkSize) {
                    _WADRandPad((u8*)transfer.buffers[bufferIndex] + chunkSize,
                                readSize - chunkSize);
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
                OSSignalCond(&transfer.signalCond[bufferIndex]);
                importedSize += chunkSize;
                sizeRemaining -= chunkSize;
                if (processCallback != 0) {
                    processCallback(importedSize, contentDataSize + fileDataSize, FALSE);
                }
                bufferIndex ^= 1;
            }
            if (threadCreated) {
                result = OSJoinThread(&exportThread, (void**)&fileFd);
                threadCreated = FALSE;
                if (result == 0) {
                    result = -3009;
                    goto cleanup;
                }
            }
            if (fileFd < 0) {
                result = fileFd;
                goto cleanup;
            }
            result = ES_ExportContentEnd(fileFd);
            contentExportStarted = FALSE;
            if (result != 0) {
                goto cleanup;
            }
        }
    }
    if (titleExportStarted) {
        result = ES_ExportTitleDone();
        titleExportStarted = FALSE;
        if (result != 0) {
            goto cleanup;
        }
    }
    if ((flags & 2) != 0) {
        for (fileIndex = 0; fileIndex < fileCount; fileIndex++) {
            WADBackupFileHeader* file = &files[fileIndex];
            s32 filePosition = WADSeekStream(&stream, 0, 1);
            size_t nameLength = strlen(file->path);
            _WADRandPad(file->path + nameLength + 1,
                        0x75 - (nameLength + 1));
            result = SHA1Input(hashContext, file, sizeof(WADBackupHeaderBlock));
            if (result != 0) {
                goto cleanup;
            }
            result = WADWriteStream(&stream, file, sizeof(WADBackupHeaderBlock));
            if (result != sizeof(WADBackupHeaderBlock)) {
                result = -3006;
                goto cleanup;
            }
            importedSize += sizeof(WADBackupHeaderBlock);
            if (processCallback != 0) {
                processCallback(importedSize, contentDataSize + fileDataSize, FALSE);
            }
            if ((file->flags[2] == 1) && (file->fileSize != 0)) {
                result = NANDPrivateOpen(file->path, &savedFile, 1);
                if (result != 0) {
                    goto cleanup;
                }
                fileOpened = TRUE;
                sizeRemaining = (file->fileSize + 0x1F) & ~0x1F;
                while (sizeRemaining != 0) {
                    chunkSize = sizeRemaining;
                    if (chunkSize > 0x10000) {
                        chunkSize = 0x10000;
                    }
                    readSize = NANDRead(&savedFile, outputBuffer, chunkSize);
                    if (((readSize + 0x1F) & ~0x1F) != chunkSize) {
                        result = -3005;
                        goto cleanup;
                    }
                    result = ES_Encrypt(6, encryptionIv, outputBuffer, chunkSize,
                                        encryptionBuffer);
                    if (result != 0) {
                        goto cleanup;
                    }
                    result = SHA1Input(hashContext, encryptionBuffer, chunkSize);
                    if (result != 0) {
                        goto cleanup;
                    }
                    result = WADWriteStream(&stream, encryptionBuffer, chunkSize);
                    if ((u32)result != chunkSize) {
                        result = -3006;
                        goto cleanup;
                    }
                    importedSize += chunkSize;
                    sizeRemaining -= chunkSize;
                    if (processCallback != 0) {
                        processCallback(importedSize, contentDataSize + fileDataSize, FALSE);
                    }
                }
                result = NANDClose(&savedFile);
                fileOpened = FALSE;
                if (result != 0) {
                    goto cleanup;
                }
                paddedSize = (file->fileSize + 0x3F) & ~0x3F;
                if (paddedSize > file->fileSize) {
                    _WADRandPad(encryptionBuffer, paddedSize - file->fileSize);
                    result = SHA1Input(hashContext, encryptionBuffer,
                                       paddedSize - file->fileSize);
                    if (result != 0) {
                        goto cleanup;
                    }
                    result = WADWriteStream(&stream, encryptionBuffer,
                                            paddedSize - file->fileSize);
                    if ((u32)result != paddedSize - file->fileSize) {
                        result = -3006;
                        goto cleanup;
                    }
                    importedSize += paddedSize - file->fileSize;
                }
            }
            if (filePosition < 0) {
                result = filePosition;
                goto cleanup;
            }
        }
    }
    result = WADSeekStream(&stream, 0, 1);
    if (result < 0) {
        goto cleanup;
    }
    if ((u32)result != offset + totalSize - 0x340) {
        result = -3006;
        goto cleanup;
    }
    result = SHA1Result(hashContext, digest);
    if (result != 0) {
        goto cleanup;
    }
    result = ES_Sign(digest, 0x14, signature, &signerCertificate);
    if (result != 0) {
        goto cleanup;
    }
    result = ES_GetDeviceCert(deviceCertificate);
    if (result != 0) {
        goto cleanup;
    }
    result = WADWriteStream(&stream, signature, sizeof(signature));
    if (result != sizeof(signature)) {
        result = -3006;
        goto cleanup;
    }
    result = WADWriteStream(&stream, deviceCertificate, sizeof(deviceCertificate));
    if (result != sizeof(deviceCertificate)) {
        result = -3006;
        goto cleanup;
    }
    result = WADWriteStream(&stream, &signerCertificate, sizeof(signerCertificate));
    if (result != sizeof(signerCertificate)) {
        result = -3006;
        goto cleanup;
    }
    if (WADSeekStream(&stream, offset, 0) != (s32)offset) {
        result = -3006;
        goto cleanup;
    }
    result = WADWriteStream(&stream, &headerBlock, sizeof(headerBlock));
    if (result != sizeof(headerBlock)) {
        result = -3006;
        goto cleanup;
    }
    *sizeOut = totalSize;
    result = 0;

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
    if (threadStack != 0) {
        _WADMemFree(allocator, threadStack);
    }
    if (files != 0) {
        _WADMemFree(allocator, files);
    }
    if (fileOpened) {
        NANDClose(&savedFile);
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
    if ((processCallback != 0) && (sizeOut != 0)) {
        processCallback(importedSize, contentDataSize + fileDataSize, TRUE);
    }
    return result;
}

static s32 _WADCheckContents(ESTmdView* titleMeta, ESContentMask* contentMask) {
    ESContentId installedContentIds[512] ALIGN32;
    u32 installedContentCount;
    u32 contentIndex;
    s32 result;

    if (ES_ListTitleContentsOnCard(titleMeta->head.titleId, 0, &installedContentCount) == -106) {
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
                    if ((installedIndex == installedContentCount) &&
                        ((titleMeta->contents[contentIndex].type & 0x4000) == 0)) {
                        result = -3002;
                        goto done;
                    }
                    result = 0;
                }
            }
        }
    }
done:
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
    u32 nextIndex;

    for (bitIndex = 0; bitIndex < 0x200; bitIndex += 4) {
        if ((contentMask->data[(s32)bitIndex >> 3] & (1 << (bitIndex & 7))) != 0) {
            remaining--;
        }
        if (remaining == 0) {
            return bitIndex;
        }
        nextIndex = bitIndex + 1;
        if ((contentMask->data[(s32)nextIndex >> 3] & (1 << (nextIndex & 7))) != 0) {
            remaining--;
        }
        if (remaining == 0) {
            return nextIndex;
        }
        nextIndex = bitIndex + 2;
        if ((contentMask->data[(s32)nextIndex >> 3] & (1 << (nextIndex & 7))) != 0) {
            remaining--;
        }
        if (remaining == 0) {
            return nextIndex;
        }
        nextIndex = bitIndex + 3;
        if ((contentMask->data[(s32)nextIndex >> 3] & (1 << (nextIndex & 7))) != 0) {
            remaining--;
        }
        if (remaining == 0) {
            return nextIndex;
        }
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

static s32 _WADBackupGetFiles(const char* directoryPath, u32 flags, MEMAllocator* allocator,
                              u32* fileCount, WADBackupFileHeader* files) {
    char currentDirectory[NAND_MAX_PATH] ALIGN32;
    char fullDirectoryPath[NAND_MAX_PATH] ALIGN32;
    char fullFilePath[NAND_MAX_PATH] ALIGN32;
    char* names = 0;
    char* nameList = 0;
    u32 nameCount = 0;
    u32 nameIndex;
    u32 totalFiles = 0;
    u32 childFileCount;
    u8 fileType;
    NANDFileInfo fileInfo;
    NANDStatus status;
    s32 result;

    if ((allocator == 0) || (fileCount == 0)) {
        return -3000;
    }
    result = NANDGetCurrentDir(currentDirectory);
    if (result != 0) {
        return result;
    }
    if (directoryPath == 0) {
        directoryPath = "";
    }
    if (directoryPath[0] == '\0') {
        strncpy(fullDirectoryPath, currentDirectory, sizeof(fullDirectoryPath));
    } else if (directoryPath[0] == '/') {
        strncpy(fullDirectoryPath, directoryPath, sizeof(fullDirectoryPath));
    } else {
        snprintf(fullDirectoryPath, sizeof(fullDirectoryPath), "%s/%s", currentDirectory,
                 directoryPath);
    }
    result = NANDPrivateReadDir(fullDirectoryPath, 0, &nameCount);
    if (result == -1) {
        *fileCount = 0;
        return 0;
    }
    if (result != 0) {
        return result;
    }
    if (nameCount != 0) {
        nameList = _WADMemAlloc(allocator, nameCount * 0x40);
        if (nameList == 0) {
            return -3003;
        }
        names = nameList;
        result = NANDPrivateReadDir(fullDirectoryPath, nameList, &nameCount);
        if (result != 0) {
            goto cleanup;
        }
        for (nameIndex = 0; nameIndex < nameCount; nameIndex++) {
            char* name = names;
            WADBackupFileHeader* file = 0;
            u32 fileSize = 0;
            BOOL closeFile = FALSE;

            if ((flags & 4) != 0) {
                if (directoryPath[0] == '\0') {
                    snprintf(fullFilePath, sizeof(fullFilePath), "/%s", name);
                } else {
                    snprintf(fullFilePath, sizeof(fullFilePath), "%s/%s", directoryPath, name);
                }
            } else if (directoryPath[0] == '\0') {
                snprintf(fullFilePath, sizeof(fullFilePath), "%s/%s", currentDirectory, name);
            } else if (directoryPath[0] == '/') {
                snprintf(fullFilePath, sizeof(fullFilePath), "%s/%s", directoryPath, name);
            } else {
                snprintf(fullFilePath, sizeof(fullFilePath), "%s/%s/%s", currentDirectory,
                         directoryPath, name);
            }
            result = NANDPrivateGetType(fullFilePath, &fileType);
            if (result != 0) {
                break;
            }
            if ((fileType == 2) && ((flags & 8) == 0)) {
                goto nextName;
            }
            if (fileType == 1) {
                result = NANDPrivateOpen(fullFilePath, &fileInfo, 1);
                if (result != 0) {
                    break;
                }
                closeFile = TRUE;
                result = NANDGetLength(&fileInfo, &fileSize);
                if (result != 0) {
                    NANDClose(&fileInfo);
                    break;
                }
                result = NANDClose(&fileInfo);
                closeFile = FALSE;
                if (result != 0) {
                    break;
                }
            } else if (fileType != 2) {
                goto nextName;
            }
            result = NANDPrivateGetStatus(fullFilePath, &status);
            if (result != 0) {
                break;
            }
            if (files != 0) {
                file = &files[totalFiles];
                file->magic = 0x3ADF17E;
                file->fileSize = fileSize;
                file->flags[0] = status.permission;
                file->flags[1] = status.attribute;
                file->flags[2] = fileType;
                strncpy(file->path, fullFilePath, 0x40);
            }
            totalFiles++;
            if (fileType == 2) {
                childFileCount = 0;
                result = _WADBackupGetFiles(fullFilePath, flags, allocator, &childFileCount,
                                            files == 0 ? 0 : &files[totalFiles]);
                if (result != 0) {
                    break;
                }
                totalFiles += childFileCount;
            }

nextName:
            names += strlen(names) + 1;
            if (closeFile) {
                NANDClose(&fileInfo);
            }
        }
    }
    if (result == 0) {
        *fileCount = totalFiles;
    }

cleanup:
    if (nameList != 0) {
        _WADMemFree(allocator, nameList);
    }
    return result;
}

static s32 _WADBackupGetSize(u32 flags, ESTmdView* titleMeta, ESContentMask* contentMask,
                             u32 fileCount, WADBackupFileHeader* files, u32* titleMetaSize,
                             u32* contentDataSize, u32* fileDataSize) {
    u32 titleSize = 0;
    u32 contentSize = 0;
    u32 filesSize = 0;
    u32 selectedCount;
    u32 contentIndex;
    u32 fileIndex;
    s32 result = 0;

    if (titleMeta == 0) {
        if (titleMetaSize != 0) {
            *titleMetaSize = 0;
        }
    } else if (((flags & 1) != 0) || ((flags & 0x20) != 0)) {
        result = ES_GetTmdSizeFromView(titleMeta, &titleSize);
        if (result != 0) {
            return result;
        }
        titleSize = (titleSize + 0x3F) & ~0x3F;
    }
    if (((flags & 1) != 0) && (titleMeta != 0)) {
        selectedCount = _WADGetCidxCount(contentMask);
        for (contentIndex = 0; contentIndex < selectedCount; contentIndex++) {
            s32 tmdIndex = _WADGetCidx(contentMask, contentIndex);
            if ((tmdIndex < 0) || (titleMeta->head.numContents <= tmdIndex)) {
                return -3009;
            }
            contentSize += (titleMeta->contents[tmdIndex].size + 0x3F) & ~0x3F;
        }
    }
    if ((fileCount != 0) && (files != 0)) {
        for (fileIndex = 0; fileIndex < fileCount; fileIndex++) {
            filesSize += 0x80 + ((files[fileIndex].fileSize + 0x3F) & ~0x3F);
        }
    }
    if (titleMetaSize != 0) {
        *titleMetaSize = titleSize;
    }
    if (contentDataSize != 0) {
        *contentDataSize = contentSize;
    }
    if (fileDataSize != 0) {
        *fileDataSize = filesSize;
    }
    return result;
}
#pragma dont_inline reset

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
                OSReport("%s: Memory Allocator must return 64B aligned memBlocks\n", "_WADMemAlloc");
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
    u32* words = buffer;
    u32 wordCount = size >> 2;
    u32 remainder = size & 3;
    u32 wordIndex;

    for (wordIndex = 0; wordIndex < wordCount; wordIndex++) {
        u32 first = rand();
        u32 second = rand();
        u32 third = rand();
        words[wordIndex] = (third & 3) | (second << 17) | (first << 2);
    }
    if (remainder != 0) {
        u32 first = rand();
        u32 second = rand();
        u32 third = rand();
        u32 randomWord = (third & 3) | (second << 17) | (first << 2);
        u8* tail = (u8*)&words[wordCount];
        u8* randomBytes = (u8*)&randomWord;
        u32 byteIndex;

        for (byteIndex = 0; byteIndex < remainder; byteIndex++) {
            tail[byteIndex] = randomBytes[byteIndex];
        }
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

s32 WADOpenStream(WADLocation location, const char* path, WADStream* stream, u32 write,
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

size_t WADReadStream(WADStream* stream, void** buffer, size_t size, s32 offset) {
    size_t result;
    u32 alignedSize;
    s32 location;

    if ((s32)size <= 0) {
        result = 0;
    } else if ((stream == 0) || (buffer == 0)) {
        result = -3000;
    } else {
        alignedSize = (size + WAD_READ_ALIGNMENT - 1) & ~(WAD_READ_ALIGNMENT - 1);
        if (size == alignedSize) {
            location = stream->location;
            if (location != WAD_LOCATION_SD_CARD) {
                if (location < WAD_LOCATION_SD_CARD) {
                    if (location != WAD_LOCATION_DVD) {
                        if (location > 0) {
                            result = NANDSeek(&stream->handle.nand, offset, 0);
                            if ((s32)result < 0) {
                                return result;
                            }
                            return NANDRead(&stream->handle.nand, *buffer, alignedSize);
                        }
                        if (location >= 0) {
                            memcpy(*buffer, (u8*)stream->handle.memoryBase + offset, size);
                            return size;
                        }
                    } else {
                        return DVDReadPrio(&stream->handle.dvd, *buffer, alignedSize, offset, 2);
                    }
                } else {
                    if (location != WAD_LOCATION_CNT_NAND) {
                        if (location < WAD_LOCATION_CNT_NAND) {
                            return contentReadDVD(&stream->handle.contentDvd, *buffer, alignedSize,
                                                  offset);
                        }
                    } else {
                        return contentReadNAND(&stream->handle.contentNand, *buffer, alignedSize,
                                               offset);
                    }
                }
                result = -3000;
            } else if (stream->handle.fa == 0) {
                result = -3000;
            } else {
                result = FAFseek(stream->handle.fa, offset, 0);
                if (result == 0) {
                    result = FAFread(*buffer, 1, size, stream->handle.fa);
                }
            }
        } else {
            result = -3000;
        }
    }
    return result;
}

void WADCloseStream(WADStream* stream) {
    if (stream == 0) {
        return;
    }
    if (stream->location != WAD_LOCATION_SD_CARD) {
        if (stream->location < WAD_LOCATION_SD_CARD) {
            if (stream->location != WAD_LOCATION_DVD) {
                if (stream->location < WAD_LOCATION_DVD) {
                    return;
                }
                NANDClose(&stream->handle.nand);
                return;
            }
            DVDClose(&stream->handle.dvd);
            return;
        }
        if (stream->location != WAD_LOCATION_CNT_NAND) {
            if (stream->location > WAD_LOCATION_CNT_NAND) {
                return;
            }
            contentCloseDVD(&stream->handle.contentDvd);
            return;
        }
        contentCloseNAND(&stream->handle.contentNand);
        return;
    }
    if (stream->handle.fa != 0) {
        FAFclose(stream->handle.fa);
    }
}

s32 WADWriteStream(WADStream* stream, void* buffer, u32 size) {
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

s32 WADSeekStream(WADStream* stream, u32 offset, s32 origin) {
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

static s32 _WADVerifySavedataZD(WADSaveDataHeader* header, WADStream* stream,
                                MEMAllocator* allocator, u32 offset) {
    WADFileHeader* fileHeader = 0;
    void* encryptedData = 0;
    void* decryptedData = 0;
    NANDFileInfo fileInfo;
    s32 fileOpened = FALSE;
    s32 result;

    if (header->saveType != 1) {
        return -3009;
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
    if (strcmp(fileHeader->name, "zeldaTp.dat") != 0) {
        result = -3009;
        goto cleanup;
    }
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
    if ((result == 0) && (NANDPrivateOpen(fileHeader->name, &fileInfo, 2) == 0)) {
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

static void _WADCleanTmpDir(MEMAllocator* allocator) {
    char* names = 0;
    char* name;
    char filePath[NAND_MAX_PATH] ALIGN32;
    u32 fileCount = 0;
    u32 fileIndex;
    s32 result;

    result = NANDPrivateReadDir("/tmp", 0, &fileCount);
    if ((result == 0) && (fileCount != 0)) {
        names = MEMAllocFromAllocator(allocator, fileCount * 0x41);
        if ((names != 0) && (NANDPrivateReadDir("/tmp", names, &fileCount) == 0)) {
            name = names;
            for (fileIndex = 0; fileIndex < fileCount; fileIndex++) {
                char* extension = strrchr(name, '.');
                if ((extension != 0) && (strncmp(extension + 1, "tmp", 3) == 0)) {
                    snprintf(filePath, sizeof(filePath), "/tmp/%s", name);
                    NANDPrivateDelete(filePath);
                    OSReport("%s:%d remove %s", "WADImportEx", 0x1777, filePath);
                }
                name += strlen(name) + 1;
            }
        }
    }
    if (names != 0) {
        MEMFreeToAllocator(allocator, names);
    }
}

s32 WADImportDVDForBS(const char* path, void* buffer, u32 bufferSize) {
    DVDFileInfo fileInfo;
    WADBootImportParts parts;
    WADHeader* header;
    ESTitleMeta* titleMeta;
    u8* readBuffer = buffer;
    void* applicationData;
    u32 paddedFileSize;
    u32 sectionOffset;
    u32 applicationSize;
    BOOL fileOpened = FALSE;
    s32 result;

    if ((path == 0) || (buffer == 0)) {
        result = -3000;
        goto cleanup;
    }
    if (!DVDOpen(path, &fileInfo)) {
        return -3004;
    }
    fileOpened = TRUE;
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
    result = WAD_815C2F44(header, parts.headerInfo);
    if (result != 2) {
        OSReport("%s:%d Format should be iRD format: %s\n", "WADImportDVDForBS", 0x17D2,
                 path);
        result = -3000;
        goto cleanup;
    }
    if (parts.headerInfo[0] == 3) {
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
            parts.titleMeta = readBuffer + sectionOffset;
            sectionOffset += (header->tmdSize + 0x3F) & ~0x3F;
        }
        titleMeta = parts.titleMeta;
        applicationSize = ((u32)titleMeta->contents[0].size + 0xF) & ~0xF;
        applicationData = readBuffer + sectionOffset;
        if ((titleMeta == 0) || (titleMeta->head.titleId != ES_TITLE_ID(1, 1))) {
            OSReport("%s:%d This function only works for boot2 import.\n", "WADImportDVDForBS",
                     0x180D);
            result = -3000;
        } else {
            result = ES_ImportBoot(parts.ticket, parts.certificates, parts.certificateSize,
                                   parts.titleMeta, parts.titleMetaSize, parts.certificates,
                                   parts.certificateSize, parts.crls, parts.crlSize, applicationData,
                                   applicationSize);
            if (result != 0) {
                OSReport("%s: Import Boot Failed: %d\n", "WADImportDVDForBS", result);
            } else {
                OSReport("%s: Import Boot Successful\n", "WADImportDVDForBS");
            }
        }
    } else {
        OSReport("%s:%d This function only works for boot2 import.\n", "WADImportDVDForBS",
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
    WADBootImportParts parts;
    DVDFileInfo fileInfo;
    u8* readBuffer = buffer;
    u8* contentBuffer;
    ESTitleMeta* titleMeta;
    ESContentMeta* contentMeta;
    u32 sectionOffset;
    u32 remainingBufferSize;
    u32 contentCount;
    u32 contentIndex;
    s32 contentFd;
    s32 result = 0;
    s32 readResult;
    BOOL fileOpened = FALSE;

    if ((path == 0) || (buffer == 0)) {
        result = -3000;
        goto cleanup;
    }
    if (!DVDOpen(path, &fileInfo)) {
        return -3004;
    }
    fileOpened = TRUE;
    if (buffer == 0) {
        result = -3003;
        goto cleanup;
    }
    if (((s32)readBuffer % 0x40) != 0) {
        readBuffer += 0x20;
        bufferSize -= 0x20;
    }
    readResult = DVDReadPrio(&fileInfo, &header, sizeof(header), 0, 2);
    if (readResult != sizeof(header)) {
        result = -3005;
        goto cleanup;
    }

    memset(&parts, 0, sizeof(parts));
    result = WAD_815C2F44(&header, parts.headerInfo);
    if (result != 2) {
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
    titleMeta = parts.titleMeta;
    remainingBufferSize = bufferSize - sectionOffset;
    contentBuffer = readBuffer + sectionOffset;
    if (sectionOffset > bufferSize) {
        result = -3003;
        goto cleanup;
    }
    readResult = DVDReadPrio(&fileInfo, readBuffer, sectionOffset, 0, 2);
    if (readResult != sectionOffset) {
        result = -3005;
        goto cleanup;
    }
    if (parts.headerInfo[0] == 3) {
        result = -3001;
        goto cleanup;
    }
    if (parts.ticket != 0) {
        result = ES_ImportTicket(parts.ticket, parts.certificates,
                                 parts.certificateSize, parts.crls,
                                 parts.crlSize, 1);
        if (result != 0) {
            goto cleanup;
        }
    }
    if (titleMeta == 0) {
        goto cleanup;
    }
    if (parts.headerInfo[1] >= 1) {
        contentCount = _WADGetCidxCount((ESContentMask*)parts.headerInfo);
        if (contentCount > titleMeta->head.numContents) {
            goto cleanup;
        }
    } else {
        contentCount = titleMeta->head.numContents;
    }

    result = ES_ImportTitleInit(parts.titleMeta, parts.titleMetaSize,
                                parts.certificates, parts.certificateSize,
                                parts.crls, parts.crlSize,
                                parts.headerInfo[0], 1);
    if (result != 0) {
        ES_ImportTitleCancel();
        goto cleanup;
    }

    contentIndex = 0;
    while (contentIndex < contentCount) {
        s32 titleContentIndex;
        u32 remainingContentSize;

        if (parts.headerInfo[1] >= 1) {
            titleContentIndex = _WADGetCidx((ESContentMask*)parts.headerInfo,
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
        contentFd = ES_ImportContentBegin(titleMeta->head.titleId, contentMeta->cid);
        if (contentFd < 0) {
            result = contentFd;
            ES_ImportContentEnd(contentFd);
            ES_ImportTitleCancel();
            goto cleanup;
        }

        remainingContentSize = ((u32)contentMeta->size + 0xF) & ~0xF;
        while (remainingContentSize != 0) {
            u32 chunkSize = remainingContentSize;
            u32 readSize;

            if (chunkSize > remainingBufferSize) {
                chunkSize = remainingBufferSize;
            }
            readSize = (chunkSize + 0x1F) & ~0x1F;
            readResult = DVDReadPrio(&fileInfo, contentBuffer, readSize, sectionOffset, 2);
            if ((u32)readResult != readSize) {
                result = -3005;
                ES_ImportContentEnd(contentFd);
                ES_ImportTitleCancel();
                goto cleanup;
            }
            sectionOffset += readResult;
            result = ES_ImportContentData(contentFd, contentBuffer, chunkSize);
            if (result < 0) {
                ES_ImportContentEnd(contentFd);
                ES_ImportTitleCancel();
                goto cleanup;
            }
            remainingContentSize -= chunkSize;
        }
        sectionOffset = (sectionOffset + 0x3F) & ~0x3F;
        result = ES_ImportContentEnd(contentFd);
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
