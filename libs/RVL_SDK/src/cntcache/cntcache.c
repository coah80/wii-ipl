#include <revolution/os.h>
#include <revolution/verdefs.h>
#include <private/nand.h>
#include <revolution/nand.h>
#include <private/es.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CNTCACHE_FILE "/shared2/cntcache.txt"
#define CNTCACHE_TMP_FILE "/tmp/cntcache.txt"
#define CNTCACHE_DIR "/shared2"
#define CNTCACHE_READ_SIZE 0x400
#define CNTCACHE_LINE_SIZE 0x40
#define CNTCACHE_RESULT_IO_ERROR (-5299)

SDKDefineVersion(CNTCACHE, "Apr 20 2010", "14:15:28");

OSMutex _CNTCACHEMutex;
long long _CNTCACHEUnused816997A8;
int _CNTCACHEUnused816997A4;
BOOL _CNTCACHEInitialized;

s32 CNTCACHEClear(void);
BOOL _CNTCACHEIsTitleRemovable(ESTitleId titleId);
void _CNTCACHEDeleteTitle();
void _CNTCACHEDeleteContent();


void CNTCACHEInit(int cacheValue, int cacheHighWord) {
    if (!_CNTCACHEInitialized) {
        BOOL old;

        OSRegisterVersion(__CNTCACHEVersion);

        OSInitMutex(&_CNTCACHEMutex);
        ES_InitLib();

        old = OSDisableInterrupts();
        _CNTCACHEInitialized = TRUE;
        OSRestoreInterrupts(old);
    }
    CNTCACHEClear();

    _CNTCACHEUnused816997A4 = cacheValue;
    *((int*)&_CNTCACHEUnused816997A8) = cacheHighWord;
}

static s32 ReadCacheFile(char* buf, u32 bufSize, u32* length) {
    NANDFileInfo info;
    s32 result;

    *length = 0;
    result = NANDPrivateOpen(CNTCACHE_FILE, &info, NAND_ACCESS_READ);
    if (result == NAND_RESULT_NOEXISTS) {
        return NAND_RESULT_OK;
    }
    if (result != NAND_RESULT_OK) {
        return result;
    }

    result = NANDGetLength(&info, length);
    if (result == NAND_RESULT_OK && *length > bufSize) {
        result = NAND_RESULT_MAXBLOCKS;
    }
    if (result == NAND_RESULT_OK && NANDRead(&info, buf, OSRoundUp32B(*length)) != *length) {
        result = CNTCACHE_RESULT_IO_ERROR;
    }
    NANDClose(&info);
    return result;
}

static s32 WriteCacheFile(const char* buf, u32 length);

s32 CNTCACHEAddDeleteTitle(ESTitleId titleId) {
    char buf[CNTCACHE_READ_SIZE + CNTCACHE_LINE_SIZE] ALIGN32;
    u32 length;
    s32 result;

    OSLockMutex(&_CNTCACHEMutex);
    result = ReadCacheFile(buf, CNTCACHE_READ_SIZE, &length);
    if (result == NAND_RESULT_OK) {
        strcpy(buf + length, "DeleteTitle ");
        length += strlen(buf + length);
        length += sprintf(buf + length, "%016llx ", titleId);
        buf[length++] = '\n';
        result = WriteCacheFile(buf, length);
    }
    OSUnlockMutex(&_CNTCACHEMutex);
    return result;
}

static s32 WriteCacheFile(const char* buf, u32 length) {
    NANDFileInfo info;
    s32 result;

    NANDPrivateDelete(CNTCACHE_TMP_FILE);
    result = NANDPrivateCreate(CNTCACHE_TMP_FILE, NAND_PERM_USER | NAND_PERM_GROUP, 0);
    if (result != NAND_RESULT_OK) {
        return result;
    }

    result = NANDPrivateOpen(CNTCACHE_TMP_FILE, &info, NAND_ACCESS_WRITE);
    if (result != NAND_RESULT_OK) {
        return result;
    }
    if (NANDWrite(&info, buf, length) != length) {
        result = CNTCACHE_RESULT_IO_ERROR;
    }
    NANDClose(&info);
    if (result != NAND_RESULT_OK) {
        return result;
    }

    return NANDPrivateMove(CNTCACHE_TMP_FILE, CNTCACHE_DIR);
}

s32 CNTCACHEAddDeleteContent(ESTitleId titleId, const char* indices) {
    char buf[CNTCACHE_READ_SIZE + CNTCACHE_LINE_SIZE] ALIGN32;
    u32 length;
    s32 result;

    if (strlen(indices) > CNTCACHE_LINE_SIZE / 2) {
        return NAND_RESULT_INVALID;
    }

    OSLockMutex(&_CNTCACHEMutex);
    result = ReadCacheFile(buf, CNTCACHE_READ_SIZE, &length);
    if (result == NAND_RESULT_OK) {
        strcpy(buf + length, "DeleteContent ");
        length += strlen(buf + length);
        length += sprintf(buf + length, "%016llx ", titleId);
        strcpy(buf + length, indices);
        length += strlen(buf + length);
        buf[length++] = '\n';
        result = WriteCacheFile(buf, length);
    }
    OSUnlockMutex(&_CNTCACHEMutex);
    return result;
}

static char* FindLineEnd(char* str, u32 length) {
    u32 i;

    for (i = 0; i < length; i++) {
        if (*str == '\n') {
            return str;
        }
        str++;
    }
    return NULL;
}

static inline BOOL DeleteCacheFile(const char* path) {
    if (NANDPrivateDelete(path) != NAND_RESULT_OK) {
        return FALSE;
    }
    return TRUE;
}

s32 CNTCACHEClear(void) {
    NANDFileInfo info;
    char* command;
    s32 result;
    BOOL locked = FALSE;
    BOOL opened = FALSE;
    u32 fileLength;
    u32 offset;
    s32 readLength;
    char* line;
    char* lineEnd;
    u32 lineLength;
    u8 buf[CNTCACHE_READ_SIZE] ALIGN32;

    OSLockMutex(&_CNTCACHEMutex);
    locked = TRUE;

    result = NANDPrivateOpen(CNTCACHE_FILE, &info, NAND_ACCESS_RW);
    if (result == NAND_RESULT_NOEXISTS) {
        result = NAND_RESULT_OK;
        goto end;
    }
    switch (result) {
    case NAND_RESULT_OK:
        opened = TRUE;
        break;
    default:
        goto close;
    }

    result = NANDGetLength(&info, &fileLength);
    switch (result) {
    case NAND_RESULT_OK:
        break;
    default:
        goto close;
    }

    offset = 0;
    while (fileLength != 0) {
        readLength = fileLength > sizeof(buf) ? sizeof(buf) : fileLength;
        line = (char*)buf;
        result = NANDRead(&info, buf, OSRoundUp32B(readLength));
        if (result != readLength) {
            result = CNTCACHE_RESULT_IO_ERROR;
            goto close;
        }
        result = NAND_RESULT_OK;

        lineEnd = FindLineEnd(line, readLength);
        if (!lineEnd) {
            result = NAND_RESULT_OK;
            goto close;
        }

        while (readLength > 0) {
            *lineEnd = '\0';
            lineLength = lineEnd - line;
            command = strtok(line, " \n");
            if (command) {
                if (strcmp(command, "DeleteTitle") == 0) {
                    _CNTCACHEDeleteTitle();
                } else if (strcmp(command, "DeleteContent") == 0) {
                    _CNTCACHEDeleteContent();
                }
            }

            lineLength++;
            line += lineLength;
            fileLength -= lineLength;
            readLength -= lineLength;
            offset += lineLength;

            lineEnd = FindLineEnd(line, readLength);
            if (!lineEnd) {
                break;
            }
        }

        if (fileLength != 0) {
            result = NANDSeek(&info, offset, NAND_SEEK_BEG);
            if (result != offset) {
                result = CNTCACHE_RESULT_IO_ERROR;
                goto close;
            }
            result = NAND_RESULT_OK;
        }
    }

close:
    NANDClose(&info);
    opened = FALSE;
    DeleteCacheFile(CNTCACHE_FILE);
    DeleteCacheFile(CNTCACHE_TMP_FILE);

end:
    if (opened) {
        NANDClose(&info);
    }
    if (locked) {
        OSUnlockMutex(&_CNTCACHEMutex);
    }
    return result;
}

void _CNTCACHEDeleteTitle() {
    char* token;

    for (token = strtok(NULL, " \n"); token != NULL; token = strtok(NULL, " \n")) {
        ESTitleId titleId;
        int removable;

        errno = 0;
        titleId = strtoull(token, NULL, 16);
        if (errno != 0 || (u32)ES_TITLE_TYPE(titleId) == 1) {
            continue;
        }

        removable = _CNTCACHEIsTitleRemovable(titleId);
        if (removable == 1) {
            ES_DeleteTitle(titleId);
        } else if (removable == 0) {
            ES_DeleteTitleContent(titleId);
        }
    }
}

static s32 GetSaveDataUsage(ESTitleId titleId) {
    s32 ret = -1;
    char nandPath[64] ALIGN32;
    u32 usedBlocks = 1;
    u32 usedINodes = 1;

    snprintf(nandPath, (int)sizeof(nandPath), "/title/%08x/%08x/data", NANDTitleIdHi(titleId), NANDTitleIdLo(titleId));
    ret = NANDSecretGetUsage(nandPath, &usedBlocks, &usedINodes);

    if (ret == NAND_RESULT_NOEXISTS) {
        ret = 2;
    } else if (ret >= NAND_RESULT_OK) {
        if (usedINodes == 1 && usedBlocks == 0) {
            ret = 1;
        } else {
            ret = 0;
        }
    }
    return ret;
}

BOOL _CNTCACHEIsTitleRemovable(ESTitleId titleId) {
    u8 tmdBuf[OSRoundUp32B(sizeof(ESTmdView))] ALIGN32;
    u32 tmdSize;
    ESTmdView* tmd;
    s32 ret;

    ret = GetSaveDataUsage(titleId);
    if (ret == 1) {
        tmd = (ESTmdView*)tmdBuf;
        ret = ES_GetTmdView(titleId, NULL, &tmdSize);
        if (ret != ES_ERR_OK) {
            return ret;
        }
        if (tmdSize > sizeof(tmdBuf)) {
            return ES_ERR_MEMORY_ERROR;
        }
        ret = ES_GetTmdView(titleId, tmd, &tmdSize);
        if (ret != ES_ERR_OK) {
            return ret;
        }

        if (((tmd->head.titleVersion >> 8) & 0xFF) == 0) {
            ret = 1;
        } else {
            ret = 0;
        }
    }

    return ret;
}

void _CNTCACHEDeleteContent() {
    u8 buf[OSRoundUp32B(sizeof(ESTmdView))] ALIGN32;
    u32 numOnCard;
    u32 size;
    ESTitleId titleId;
    ESTmdView* tmd;
    ESError result;
    char* token;

    token = strtok(NULL, " \n");
    errno = 0;
    titleId = strtoull(token, NULL, 16);
    if (errno == 0 && NANDTitleIdHi(titleId) == 0x00010005) {
        tmd = (ESTmdView*)buf;
        result = ES_GetTmdView(titleId, NULL, &size);
        if (result == ES_ERR_DONT_EXISTS) {
            return;
        }
        if (result == ES_ERR_OK && ES_GetTmdView(titleId, tmd, &size) == ES_ERR_OK) {
            if ((tmd->head.titleType & 8) && (tmd->head.titleType & 0x10)) {
                token = strtok(NULL, " \n");
                while (token) {
                    u32 index;
                    u32 i;

                    errno = 0;
                    index = strtoul(token, NULL, 10);
                    if (errno == 0 && index <= 510) {
                        for (i = 0; i < tmd->head.numContents; i++) {
                            if (index == tmd->contents[i].index) {
                                if (!(tmd->contents[i].type & 0x8000) &&
                                    ES_DeleteContent(titleId, tmd->contents[i].cid) == ES_ERR_OK &&
                                    ES_ListTitleContentsOnCard(titleId, NULL, &numOnCard) == ES_ERR_OK &&
                                    numOnCard == 0 && GetSaveDataUsage(titleId) == 1) {
                                    ES_DeleteTitle(titleId);
                                }
                                break;
                            }
                        }
                    }
                    token = strtok(NULL, " \n");
                }
            }
            memset(buf, 0, OSRoundUp32B(size));
        }
    }
}
