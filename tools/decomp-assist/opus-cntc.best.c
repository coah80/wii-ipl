/*
 * opus-cntc best C for CNTCACHEClear: 47/151 differing, 149/151 instructions
 * (odiff libs/RVL_SDK/src/cntcache/cntcache CNTCACHEClear). Not exact; the retail
 * assembly placeholder stays in cntcache.c.
 *
 * Needed alongside this text (all verified in the trial build):
 * - Replace the scCntCacheStrs/scCntCacheTitleDataFmt/scCntCacheSpaceNl byte arrays with
 *   real literals: SDKDefineVersion(CNTCACHE, "Apr 20 2010", "14:15:28"), " \n",
 *   "/title/%08x/%08x/data". The writer functions below (stripped from the DOL) own
 *   "DeleteTitle ", "%016llx ", "/shared2" and "DeleteContent " and put them before
 *   Clear's literals; with them .data/.sdata bytes are identical to the target.
 * - _CNTCACHEDeleteTitle must be the for/continue form below. The while form has auto-inline
 *   size 15 (= the -inline auto limit) and gets inlined into Clear; the target calls it.
 *   The for/continue form still matches DeleteTitle 0/50 and is not inlined.
 * - ExecuteCacheFile must be `static inline` with `return`s: that is what produces the
 *   target's `beq +8; b close` exits (goto produces `bne close`).
 * - Helper locals declared in reverse (lineLength, line, readLength, offset) give the
 *   target's r23..r26. Clear's own local order has no effect.
 *
 * Remaining: the target has a lone `cmpwi r3,0` after each NANDPrivateDelete. MWCC keeps
 * such a compare when the if-body is a copy between two coalesced variables (micro-test:
 * `r = res; if (g() != 0) { r = res; }`). An empty if-body or ignored return removes it, and
 * `result = result;` keeps only the second one. The caller-side registers (base r30, opened
 * r29, result r28, locked r27, zero r31) are still off, probably because of that missing copy.
 */

#define CNTCACHE_READ_SIZE 0x400
#define CNTCACHE_LINE_SIZE 0x40
#define CNTCACHE_RESULT_READ_ERROR (-5299)

static s32 ReadCacheFile(char* buf, u32 bufSize, u32* length) {
    NANDFileInfo info;
    s32 result;

    *length = 0;
    result = NANDPrivateOpen("/shared2/cntcache.txt", &info, NAND_ACCESS_READ);
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
        result = CNTCACHE_RESULT_READ_ERROR;
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

    NANDPrivateDelete("/tmp/cntcache.txt");
    result = NANDPrivateCreate("/tmp/cntcache.txt", NAND_PERM_USER | NAND_PERM_GROUP, 0);
    if (result != NAND_RESULT_OK) {
        return result;
    }

    result = NANDPrivateOpen("/tmp/cntcache.txt", &info, NAND_ACCESS_WRITE);
    if (result != NAND_RESULT_OK) {
        return result;
    }
    if (NANDWrite(&info, buf, length) != length) {
        result = CNTCACHE_RESULT_READ_ERROR;
    }
    NANDClose(&info);
    if (result != NAND_RESULT_OK) {
        return result;
    }

    return NANDPrivateMove("/tmp/cntcache.txt", "/shared2");
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

static inline s32 ExecuteCacheFile(NANDFileInfo* info, s32 result) {
    u32 fileLength;
    u8 buf[CNTCACHE_READ_SIZE] ALIGN32;
    u32 lineLength;
    char* line;
    s32 readLength;
    u32 offset;
    char* lineEnd;
    char* command;

    if (result != NAND_RESULT_OK) {
        return result;
    }

    result = NANDGetLength(info, &fileLength);
    if (result != NAND_RESULT_OK) {
        return result;
    }

    offset = 0;
    while (fileLength != 0) {
        readLength = fileLength;
        if (readLength > sizeof(buf)) {
            readLength = sizeof(buf);
        }
        line = (char*)buf;
        if (NANDRead(info, buf, OSRoundUp32B(readLength)) != readLength) {
            return CNTCACHE_RESULT_READ_ERROR;
        }
        result = NAND_RESULT_OK;

        lineEnd = FindLineEnd(line, readLength);
        if (!lineEnd) {
            return NAND_RESULT_OK;
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
            if (NANDSeek(info, offset, NAND_SEEK_BEG) != offset) {
                return CNTCACHE_RESULT_READ_ERROR;
            }
            result = NAND_RESULT_OK;
        }
    }
    return result;
}

s32 CNTCACHEClear(void) {
    NANDFileInfo info;
    BOOL opened = FALSE;
    BOOL locked;
    s32 result;

    OSLockMutex(&_CNTCACHEMutex);
    locked = TRUE;

    result = NANDPrivateOpen("/shared2/cntcache.txt", &info, NAND_ACCESS_RW);
    if (result == NAND_RESULT_NOEXISTS) {
        result = NAND_RESULT_OK;
        goto end;
    }
    result = ExecuteCacheFile(&info, result);

    NANDClose(&info);
    opened = FALSE;
    if (NANDPrivateDelete("/shared2/cntcache.txt") != NAND_RESULT_OK) {
    }
    if (NANDPrivateDelete("/tmp/cntcache.txt") != NAND_RESULT_OK) {
    }

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
