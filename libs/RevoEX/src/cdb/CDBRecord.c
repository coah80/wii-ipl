#define CDB_RECORD_IMPLEMENTATION
#include <private/cdb.h>
#include <revolution/cdb.h>

#include <revolution/net/NETDigest.h>
#include <revolution/os.h>

#include <stddef.h>
#include <string.h>

typedef struct {
    u8 state[0xC010];
    u32 openFlags;
} CDBRecordDatabaseState;

typedef struct {
    u8 buf[0xD0];
} NETHMACContext;

typedef struct {
    u8 buf[0x120];
} NETAESContext;

extern CDBErr CDBCryptBufAllocate(CDBCryptBuf** cryptBuf);
extern CDBErr CDBCryptBufFree(CDBCryptBuf** cryptBuf);
extern void CDBLock(void);
extern void CDBUnlock(void);
extern BOOL CDBRecordBelongedDBOpenedAsRW(CDBRecord* record);
extern void CDBGetWiiIdKey(char* wiiIdKey);
extern void CDBCopyWiiIdKey(char* wiiIdKey1, char* wiiIdKey2);
extern void CDBGetDeviceKey(char* devKey);
extern BOOL CDBFSIsExistFile(const char* fileName, CDBLocation location);
extern const void* NETGetSHA1Interface(void);
extern void NETHMACInit(NETHMACContext* context, const void* interface, const void* key, u32 keyLength);
extern void NETHMACUpdate(NETHMACContext* context, const void* data, u32 length);
extern void NETHMACGetDigest(NETHMACContext* context, void* digest);
extern BOOL NETAESCreate(NETAESContext* context, const void* key, u32 keyLength, const void* iv);
extern void NETAESDelete(NETAESContext* context);
extern BOOL NETAESEncrypt(NETAESContext* context, void* dst, const void* src, u32 length);
extern BOOL NETAESDecrypt(NETAESContext* context, void* dst, const void* src, u32 length);

static u8 s_cdbCryptBuffer[0x40] ALIGN32;
static u8 s_cdbCryptBufferResult[0x40] ALIGN32;
static const u8 s_cdbCryptKey[0x10] = {0};

CDBErr CDBRecordOpen_(CDBRecord* record);
CDBErr CDBRecordOpenReadOnly_(CDBRecord* record);
CDBErr CDBRecordClose_(CDBRecord* record);
CDBErr CDBRecordWrite_(CDBRecord* record, void* buffer, u32 size);
CDBErr CDBRecordRemove_(CDBRecord* record);
CDBErr CDBRecordBackupToSD_(CDBRecord* record);
CDBErr CDBRecordUpdateModifiedDate(CDBRecord* record);
CDBErr CDBRecordEncrypt(CDBRecord* record, void* buffer, CDBRecordKey* key, u32 size, u32* encryptedSize);
CDBErr CDBRecordDecrypt(CDBRecord* record, void* buffer, u32 size, u32* dataSize, CDBRecordKey* key);

void CDBRecordInstanceInit(CDBRecordFile* recordFile, CDBRecord* record, int type) {
    OSLockMutex((OSMutex*)recordFile);
    recordFile->used = 1;
    OSUnlockMutex((OSMutex*)recordFile);
    recordFile->allocFlag = type;
    recordFile->database = record->database;
    CDBAttrInit(&recordFile->attr);
    CDBRecordKeyCopy(&recordFile->key, &record->key);
}

BOOL CDBRecordInstanceIsUsed(CDBRecordFile* recordFile) {
    BOOL used;
    OSLockMutex((OSMutex*)recordFile);
    used = recordFile->used;
    OSUnlockMutex((OSMutex*)recordFile);
    return used;
}

void CDBRecordInitDescriptor(CDBRecord* record, CDBDatabase* database, CDBRecordKey* key) {
    CDBLock();
    record->database = (u32)database;
    CDBRecordKeyCopy(&record->key, key);
    record->cryptBuf = NULL;
    record->file = NULL;
    CDBUnlock();
}

CDBErr CDBRecordCreateAtOnce(CDBRecord* record, CDBDatabase* database, const char* desc, char* fileType, CDBDate epoch, int gameCode, u16 makerCode,
                             void* buffer, u32 size) {
    CDBRecordKey key;
    CDBAttr attr;
    CDBErr err;

    if (strlen(fileType) >= 6) {
        return CDB_ERROR_19;
    }
    if (size < CDB_RECORD_BUFFER_SIZE) {
        return CDB_ERROR_20;
    }

    CDBRecordKeyInit(&key, epoch, gameCode, makerCode, 0, fileType, CDB_FS_LOCATION_NAND);
    CDBLock();
    record->database = (u32)database;
    CDBRecordKeyCopy(&record->key, &key);
    record->cryptBuf = NULL;
    record->file = NULL;
    CDBUnlock();

    err = CDBAttrCreateOnNAND(&attr, desc, epoch);
    if (err != CDB_ERROR_OK) {
        return err;
    }
    err = CDBAttrSetModifiedCount(&attr, 1);
    if (err != CDB_ERROR_OK) {
        return err;
    }
    memcpy(buffer, &attr, CDB_RECORD_BUFFER_SIZE);
    return CDBRecordFileCreateAtOnce(record, buffer, size);
}

CDBErr CDBRecordOpen(CDBRecord* record) {
    CDBErr err;
    CDBLock();
    err = CDBRecordOpen_(record);
    CDBUnlock();
    return err;
}

CDBErr CDBRecordOpen_(CDBRecord* record) {
    char fullPath[256];
    CDBCryptBuf* cryptBuf;
    CDBErr err;
    CDBDatabase* database;
    CDBRecordDatabaseState* instance;

    database = (CDBDatabase*)record->database;
    instance = database->instance;
    record->cryptBuf = NULL;
    if (instance == NULL) {
        CDBReportError("(CDB) error : can't open the record; the database is closed\n");
        return CDB_ERROR_27;
    }
    if ((instance->openFlags & 2) == 0) {
        CDBReportError("can't open the record; the database is READONLY\n");
        return CDB_ERROR_26;
    }

    CDBConvKeyToFullPath(&record->key, fullPath);
    err = CDBRecordFileOpen(record, fullPath, CDB_RECORD_ALLOC_RW);
    if (err != CDB_ERROR_OK) {
        return err;
    }

    err = CDBRecordFileReadAttrBuf(record);
    if (err != CDB_ERROR_OK) {
        return err;
    }

    if (record->key.location == CDB_FS_LOCATION_SD) {
        err = CDBCryptBufAllocate((CDBCryptBuf**)&record->cryptBuf);
        if (err != CDB_ERROR_OK) {
            return err;
        }

        cryptBuf = (CDBCryptBuf*)record->cryptBuf;
        if (record == NULL || !CDBRecordKeyIsValid(&record->key)) {
            err = CDB_ERROR_1;
        } else if (record->key.location != CDB_FS_LOCATION_SD) {
            err = CDB_ERROR_2;
        } else {
            if (CDBFSSDIsMounted()) {
                err = CDBRecordDecrypt(record, cryptBuf, 0x3EC00, &cryptBuf->size, NULL);
            } else {
                err = CDB_ERROR_SD_IS_NOT_MOUNTED;
            }
        }

        if (err != CDB_ERROR_OK) {
            CDBCryptBufFree((CDBCryptBuf**)&record->cryptBuf);
            return err;
        }
        cryptBuf->offset = sizeof(CDBAttrBuf);
    }
    return CDB_ERROR_OK;
}

CDBErr CDBRecordOpenReadOnly(CDBRecord* record) {
    CDBErr err;
    CDBLock();
    err = CDBRecordOpenReadOnly_(record);
    CDBUnlock();
    return err;
}

CDBErr CDBRecordOpenReadOnly_(CDBRecord* record) {
    char fullPath[260];
    CDBErr err;
    CDBErr result;
    CDBCryptBuf* cryptBuf;

    record->cryptBuf = NULL;
    if (!CDBRecordKeyIsValid(&record->key)) {
        CDBReportError("invalid key\n");
        return CDB_ERROR_5;
    }

    CDBConvKeyToFullPath(&record->key, fullPath);
    err = CDBRecordFileOpen(record, fullPath, CDB_RECORD_ALLOC_READ);
    if (err != CDB_ERROR_OK) {
        return err;
    }

    err = CDBRecordFileReadAttrBuf(record);
    if (err != CDB_ERROR_OK) {
        return err;
    }

    if (record->key.location == CDB_FS_LOCATION_SD) {
        err = CDBCryptBufAllocate((CDBCryptBuf**)&record->cryptBuf);
        if (err != CDB_ERROR_OK) {
            return err;
        }

        cryptBuf = (CDBCryptBuf*)record->cryptBuf;
        if (record == NULL || !CDBRecordKeyIsValid(&record->key)) {
            result = CDB_ERROR_1;
        } else if (record->key.location != CDB_FS_LOCATION_SD) {
            result = CDB_ERROR_2;
        } else {
            if (CDBFSSDIsMounted()) {
                result = CDBRecordDecrypt(record, cryptBuf, 0x3EC00, &cryptBuf->size, NULL);
            } else {
                result = CDB_ERROR_SD_IS_NOT_MOUNTED;
            }
        }

        if (result != CDB_ERROR_OK) {
            CDBCryptBufFree((CDBCryptBuf**)&record->cryptBuf);
            return result;
        }
        cryptBuf->offset = sizeof(CDBAttrBuf);
    }
    return CDB_ERROR_OK;
}

CDBErr CDBRecordClose(CDBRecord* record) {
    CDBErr err;
    CDBLock();
    err = CDBRecordClose_(record);
    CDBUnlock();
    return err;
}

CDBErr CDBRecordClose_(CDBRecord* record) {
    CDBRecordFile* recordFile;
    CDBErr err;

    recordFile = record->file;
    if (record->cryptBuf != NULL) {
        err = CDBCryptBufFree((CDBCryptBuf**)&record->cryptBuf);
        if (err != CDB_ERROR_OK) {
            return err;
        }
    }
    if (recordFile == NULL) {
        return CDB_ERROR_27;
    }
    err = CDBRecordFileWriteAttrBuf(record);
    if (err != CDB_ERROR_OK && err != CDB_ERROR_SD_EJECTED && err != CDB_ERROR_VF_ERROR) {
        return err;
    }
    err = CDBRecordFileClose(record);
    if (err != CDB_ERROR_OK) {
        return err;
    }
    if (record->key.location == CDB_FS_LOCATION_NAND) {
        err = CDBVFSync();
        if (err != CDB_ERROR_OK) {
            return err;
        }
    }
    return CDB_ERROR_OK;
}

CDBErr CDBRecordWrite(CDBRecord* record, void* buffer, u32 size) {
    CDBErr err;
    CDBLock();
    err = CDBRecordWrite_(record, buffer, size);
    CDBUnlock();
    return err;
}

CDBErr CDBRecordWrite_(CDBRecord* record, void* buffer, u32 size) {
    CDBRecordFile* recordFile;
    CDBDatabase* database;
    CDBErr err;
    CDBErr result;
    CDBRecordDatabaseState* instance;

    database = (CDBDatabase*)record->database;
    instance = database->instance;
    recordFile = record->file;
    if (record->key.location == CDB_FS_LOCATION_SD) {
        return CDB_ERROR_ACCESS_DENIED;
    }
    if ((instance->openFlags & 2) == 0) {
        CDBReportError("can't write data in the record; the database is opened as READONLY\n");
        return CDB_ERROR_26;
    }
    if (!CDBRecordBelongedDBOpenedAsRW(record)) {
        CDBReportError("can't write data in the record; permission denied\n");
        return CDB_ERROR_ACCESS_DENIED;
    }
    if (recordFile == NULL) {
        CDBReportError("can't write data in the record; the record is closed\n");
        return CDB_ERROR_27;
    }
    if ((recordFile->allocFlag & 2) == 0) {
        CDBReportError("can't write data in the record; the record is opened as READONLY\n");
        return CDB_ERROR_27;
    }
    err = CDBRecordFileWriteData(record, buffer, size);
    if (err != CDB_ERROR_OK) {
        return err;
    }
    err = CDBRecordUpdateModifiedDate(record);
    result = CDB_ERROR_OK;
    if (err != CDB_ERROR_OK) {
        result = err;
    }
    return result;
}

CDBErr CDBRecordRead(CDBRecord* record, void* buffer, u32 size, u32* readSize) {
    CDBErr err;
    CDBLock();
    if (record->file == NULL) {
        CDBReportError("can't read data in the record; the record is closed\n");
        err = CDB_ERROR_27;
    } else {
        err = CDBRecordFileReadData(record, buffer, size, readSize);
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordSeek(CDBRecord* record, s32 offset, CDBSeek seek) {
    CDBErr err;
    CDBLock();
    if (record->file == NULL) {
        err = CDB_ERROR_27;
    } else {
        switch (seek) {
            case CDB_SEEK_CUR: {
                err = CDBRecordFileSeekData(record, offset, CDB_SEEK_CUR);
                break;
            }
            case CDB_SEEK_BEGIN: {
                err = CDBRecordFileSeekData(record, offset, CDB_SEEK_BEGIN);
                break;
            }
            case CDB_SEEK_END: {
                err = CDBRecordFileSeekData(record, offset, CDB_SEEK_END);
                break;
            }
            default:
                err = CDB_ERROR_1;
                break;
        }
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordGetFileSize(CDBRecord* record, u32* size) {
    CDBErr err;
    CDBLock();
    if ((s32)record->file == 0) {
        CDBReportError("can't get file size of the record ; the record is closed\n");
        err = CDB_ERROR_27;
    } else {
        err = CDBRecordFileGetFileSize(record, size);
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordGetDataSize(CDBRecord* record, u32* size) {
    CDBErr err;
    CDBLock();
    if (record->file == NULL) {
        CDBReportError("can't get data size of the record ; the record is closed\n");
        err = CDB_ERROR_27;
    } else {
        err = CDBRecordFileGetDataSize(record, size);
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordReduceFileSize(CDBRecord* record, u32 newFileSize) {
    CDBRecordFile* recordFile;
    CDBErr err;
    u32 fileSize;

    recordFile = record->file;
    if (recordFile == NULL) {
        CDBReportError("can't reduce file size of the record ; the record is closed\n");
        return CDB_ERROR_27;
    }
    if ((recordFile->allocFlag & 2) == 0) {
        CDBReportError("can't reduce file size of the record ; the record is opened as READONLY\n");
        return CDB_ERROR_27;
    }
    CDBAttrGetFileSize(&recordFile->attr, &fileSize);
    if (newFileSize > fileSize) {
        CDBReportError("can't reduce file size of the record ; file size must be over %d bytes\n", fileSize);
        return CDB_ERROR_26;
    }
    CDBAttrSetFileSize(&recordFile->attr, newFileSize);
    recordFile->attr.dirty = TRUE;
    err = CDBRecordFileWriteAttrBuf(record);
    if (err != CDB_ERROR_OK) {
        return err;
    }
    return CDB_ERROR_OK;
}

CDBErr CDBRecordReduceDataSize(CDBRecord* record, u32 newDataSize) {
    CDBRecordFile* recordFile;
    CDBErr err = CDB_ERROR_OK;
    u32 dataSize;

    recordFile = record->file;
    if (recordFile == NULL) {
        CDBReportError("can't reduce data size of the record ; the record is closed\n");
        return CDB_ERROR_27;
    }
    if ((recordFile->allocFlag & 2) == 0) {
        CDBReportError("can't reduce data size of the record ; the record is opened as READONLY\n");
        return CDB_ERROR_27;
    }
    if (!CDBRecordBelongedDBOpenedAsRW(record)) {
        CDBReportError("can't reduce data size of the record; permission denied\n");
        return CDB_ERROR_ACCESS_DENIED;
    }
    err = CDBRecordFileGetDataSize(record, &dataSize);
    if (err != CDB_ERROR_OK) {
        return err;
    }
    if (newDataSize < dataSize) {
        CDBAttrSetFileSize(&recordFile->attr, newDataSize);
        recordFile->attr.dirty = TRUE;
    }
    err = CDBRecordFileWriteAttrBuf(record);
    if (err != CDB_ERROR_OK) {
        return err;
    }
    return CDB_ERROR_OK;
}

CDBErr CDBRecordRemove(CDBRecord* record) {
    CDBErr err;
    CDBLock();
    err = CDBRecordRemove_(record);
    CDBUnlock();
    return err;
}

CDBErr CDBRecordRemove_(CDBRecord* record) {
    CDBErr err;
    CDBErr result;
    if (record->file != NULL) {
        CDBReportError("can't remove the record ; the record is opened\n");
        return CDB_ERROR_28;
    }
    if (!CDBRecordBelongedDBOpenedAsRW(record)) {
        CDBReportError("can't remove the record ; permission denied\n");
        return CDB_ERROR_ACCESS_DENIED;
    }
    err = CDBRecordFileDelete(record);
    if (err != CDB_ERROR_OK) {
        return err;
    }
    err = CDBVFSync();
    result = CDB_ERROR_OK;
    if (err != CDB_ERROR_OK) {
        result = err;
    }
    return result;
}

void CDBRecordGetTypeForce(CDBRecord* record, char* type) {
    CDBLock();
    CDBConvKeyStrToType(record->key.keyString, type);
    CDBUnlock();
}

CDBErr CDBRecordSetFileType(CDBRecord* record, const char* fileType) {
    CDBRecordDatabaseState* instance;
    CDBRecordFile* recordFile;
    CDBErr err;

    instance = ((CDBDatabase*)record->database)->instance;
    recordFile = record->file;
    if ((instance->openFlags & 2) == 0) {
        CDBReportError("can't set file type of the record; the database is opened as READONLY\n");
        return CDB_ERROR_26;
    }
    if (recordFile == NULL) {
        CDBReportError("can't set file type of the record ; the record is closed\n");
        return CDB_ERROR_27;
    }
    if ((recordFile->allocFlag & 2) == 0) {
        CDBReportError("can't set file type of the record ; the record is opened as READONLY\n");
        return CDB_ERROR_27;
    }
    if (record->key.location != CDB_FS_LOCATION_NAND) {
        CDBReportError("can't set file type of the record ; the record must exsist on NAND\n");
        return CDB_ERROR_26;
    }
    CDBLock();
    strcpy(CDBKeyStrType(record->key.keyString), fileType);
    CDBAttrSetKeyStr(&recordFile->attr, &record->key);
    err = CDBRecordFileWriteAttrBuf(record);
    CDBUnlock();
    return err;
}

CDBErr CDBRecordGetFileType(CDBRecord* record, char* fileType) {
    CDBErr err = CDB_ERROR_OK;
    CDBLock();
    if (record->file == NULL) {
        CDBReportError("can't get file type of the record ; the record is closed\n");
        err = CDB_ERROR_27;
    } else {
        CDBConvKeyStrToType(record->key.keyString, fileType);
    }
    CDBUnlock();
    return err;
}

void CDBRecordGetGameCodeForce(CDBRecord* record, char* gameCode) {
    u32 value;
    CDBLock();
    CDBConvKeyStrToGameCode(record->key.keyString, &value);
    CDBConvGCValueToGCStr(value, gameCode);
    CDBUnlock();
}

CDBErr CDBRecordGetGameCode(CDBRecord* record, u32* gameCode) {
    CDBErr err = CDB_ERROR_OK;
    CDBLock();
    if (record->file == NULL) {
        CDBReportError("can't get game code of the record ; the record is closed\n");
        err = CDB_ERROR_27;
    } else {
        CDBConvKeyStrToGameCode(record->key.keyString, gameCode);
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordGetMakerCode(CDBRecord* record, u32* makerCode) {
    CDBErr err = CDB_ERROR_OK;
    CDBLock();
    if (record->file == NULL) {
        CDBReportError("can't get maker code of the record ; the record is closed\n");
        err = CDB_ERROR_27;
    } else {
        CDBConvKeyStrToMakerCode(record->key.keyString, makerCode);
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordGetModifiedTime(CDBRecord* record, u32* modifiedTime) {
    CDBErr err = CDB_ERROR_OK;
    CDBLock();
    if (record->file == NULL) {
        CDBReportError("can't get modified time of the record; the record is closed\n");
        err = CDB_ERROR_27;
    } else {
        *modifiedTime = ((CDBRecordFile*)record->file)->attr.buf.lastModifiedDate;
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordGetModifiedCount(CDBRecord* record, u32* modifiedCount) {
    CDBErr err = CDB_ERROR_OK;
    CDBLock();
    if (record->file == NULL) {
        CDBReportError("can't get modified count of the record; the record is closed\n");
        err = CDB_ERROR_27;
    } else {
        CDBAttrGetModifiedCount(&((CDBRecordFile*)record->file)->attr, modifiedCount);
    }
    CDBUnlock();
    return err;
}

void CDBRecordGetKeyForce(CDBRecord* record, CDBRecordKey* key) {
    CDBLock();
    CDBRecordKeyCopy(key, &record->key);
    CDBUnlock();
}

CDBErr CDBRecordSetName(CDBRecord* record, const char* name, const char* keyword) {
    CDBRecordDatabaseState* instance;
    CDBRecordFile* recordFile;
    CDBErr err;

    instance = ((CDBDatabase*)record->database)->instance;
    recordFile = record->file;
    if ((instance->openFlags & 2) == 0) {
        CDBReportError("can't set a name of the record; the database is opened as READONLY\n");
        return CDB_ERROR_26;
    }
    if (!CDBRecordBelongedDBOpenedAsRW(record)) {
        CDBReportError("can't add keyword to the record; permission denied\n");
        return CDB_ERROR_ACCESS_DENIED;
    }
    if (recordFile == NULL) {
        CDBReportError("can't set a name of the record; the record is closed\n");
        return CDB_ERROR_27;
    }
    if ((recordFile->allocFlag & 2) == 0) {
        CDBReportError("can't set a name of the record; the record is opened as READONLY\n");
        return CDB_ERROR_27;
    }
    CDBLock();
    strncpy(recordFile->attr.buf.desc, name, CDB_ATTR_BUF_MAX_DESC_LEN);
    recordFile->attr.buf.descLength = strlen(name);
    recordFile->attr.dirty = TRUE;
    err = CDBRecordFileWriteAttrBuf(record);
    CDBUnlock();
    return err;
}

CDBErr CDBRecordGetKeyword(CDBRecord* record, char* keyword) {
    CDBErr err = CDB_ERROR_OK;
    CDBLock();
    if (record->file == NULL) {
        CDBReportError("can't get keyword from the record; the record is closed\n");
        err = CDB_ERROR_27;
    } else {
        strcpy(keyword, ((CDBRecordFile*)record->file)->attr.buf.desc);
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordGetKey(CDBRecord* record, CDBRecordKey* key) {
    CDBErr err = CDB_ERROR_OK;
    CDBLock();
    if (record->file == NULL) {
        CDBReportError("can't get key from the record; the record is closed\n");
        err = CDB_ERROR_27;
    } else {
        CDBRecordKeyCopy(key, &record->key);
    }
    CDBUnlock();
    return err;
}

void CDBRecordGetCalendarTimeForce(CDBRecord* record, int* year, int* month, int* day, int* hour, int* min, int* sec) {
    char epochString[64];
    CDBDate epoch;
    CDBLock();
    CDBConvKeyStrToEpochStr(record->key.keyString, epochString);
    CDBConvEpochStrToEpochValue(epochString, &epoch);
    CDBConvEpochValueToDate(epoch, year, month, day, hour, min, sec);
    CDBUnlock();
}

CDBErr CDBRecordGetCalendarTime(CDBRecord* record, int* year, int* month, int* day, int* hour, int* min, int* sec) {
    char epochString[64];
    CDBDate epoch;
    CDBErr err = CDB_ERROR_OK;
    CDBLock();
    if (record->file == NULL) {
        CDBReportError("can't get calender time from the record; the record is closed\n");
        err = CDB_ERROR_27;
    } else {
        CDBConvKeyStrToEpochStr(record->key.keyString, epochString);
        CDBConvEpochStrToEpochValue(epochString, &epoch);
        CDBConvEpochValueToDate(epoch, year, month, day, hour, min, sec);
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordGetId(CDBRecord* record, CDBId* id) {
    CDBErr err = CDB_ERROR_OK;
    CDBRecordFile* recordFile;
    char epochString[64];

    CDBLock();
    recordFile = record->file;
    if (recordFile == NULL) {
        CDBReportError("can't get CDBId of the record ; the record is closed\n");
        err = CDB_ERROR_27;
        goto get_id_done;
    } else {
        CDBLock();
        if (record->file == NULL) {
            CDBReportError("can't get maker code of the record ; the record is closed\n");
            err = CDB_ERROR_27;
        } else {
            CDBLock();
            CDBConvKeyStrToEpochStr(record->key.keyString, epochString);
            CDBConvEpochStrToEpochValue(epochString, &id->num);
            CDBUnlock();
            err = CDB_ERROR_OK;
        }
        CDBUnlock();
    }
    switch (err) {
        case CDB_ERROR_OK:
            err = CDBAttrGetIDNumber(&recordFile->attr, (CDBId*)&id->modifiedCount);
            err = CDB_ERROR_OK;
            break;
        default:
            break;
    }
get_id_done:
    CDBUnlock();
    return err;
}

BOOL CDBRecordIsExistFile(CDBRecord* record) {
    char fullPath[256];
    CDBConvKeyToFullPath(&record->key, fullPath);
    return CDBFSIsExistFile(fullPath, record->key.location);
}

CDBErr CDBRecordUpdateModifiedDate(CDBRecord* record) {
    s64 ticks;
    u32 modifiedDate;
    u32 modifiedCount;
    CDBRecordFile* recordFile;
    CDBErr err;

    ticks = OSGetTime();
    modifiedDate = ticks / (OS_BUS_CLOCK / 4);
    recordFile = record->file;
    if ((((CDBRecordDatabaseState*)((CDBDatabase*)record->database)->instance)->openFlags & 2) == 0) {
        CDBReportError("can't set modified time of the record; the database is opened as READONLY\n");
        return CDB_ERROR_26;
    }
    if (recordFile == NULL) {
        CDBReportError("can't set modified time of the record ; the record is closed\n");
        return CDB_ERROR_27;
    }
    err = CDBAttrSetModifiedDate(&recordFile->attr, modifiedDate);
    if (err != CDB_ERROR_OK) {
        return err;
    }
    err = CDBAttrGetModifiedCount(&recordFile->attr, &modifiedCount);
    if (err != CDB_ERROR_OK) {
        return err;
    }
    modifiedCount++;
    err = CDBAttrSetModifiedCount(&recordFile->attr, modifiedCount);
    if (err != CDB_ERROR_OK) {
        return err;
    }
    return CDB_ERROR_OK;
}

CDBErr CDBRecordDuplicate(CDBRecord* record, CDBRecord* newRecord) {
    CDBRecordFile* recordFile;
    CDBErr err;

    if (record->key.location != CDB_FS_LOCATION_NAND && record->key.location != CDB_FS_LOCATION_SD) {
        OSPanic(__FILE__, __LINE__, "CDBRecordDuplicate invalud location\n");
        return CDB_ERROR_1;
    }
    recordFile = record->file;
    if (recordFile == NULL) {
        return CDB_ERROR_27;
    }
    CDBLock();
    CDBRecordKeyCopy(&newRecord->key, &record->key);
    newRecord->file = NULL;
    newRecord->database = record->database;
    err = CDBRecordFileCreateBlank(newRecord);
    CDBUnlock();
    return err;
}

CDBErr CDBRecordBackupToSD(CDBRecord* record) {
    CDBErr err;
    CDBLock();
    err = CDBRecordBackupToSD_(record);
    CDBUnlock();
    return err;
}

CDBErr CDBRecordBackupToSD_(CDBRecord* record) {
    CDBRecordFile* recordFile;
    CDBCryptBuf* cryptBuf;
    CDBRecord localRecord;
    CDBErr err;
    u32 encryptedSize;

    localRecord.cryptBuf = NULL;
    recordFile = NULL;

    if (record == NULL || !CDBRecordKeyIsValid(&record->key)) {
        return CDB_ERROR_1;
    }
    if (record->key.location != CDB_FS_LOCATION_NAND) {
        return CDB_ERROR_2;
    }
    if (!CDBFSSDIsMounted()) {
        return CDB_ERROR_SD_IS_NOT_MOUNTED;
    }
    err = CDBCryptBufAllocate((CDBCryptBuf**)&localRecord.cryptBuf);
    if (err != CDB_ERROR_OK) {
        CDBLock();
        CDBRecordClose_(&localRecord);
        CDBUnlock();
        return err;
    }
    cryptBuf = localRecord.cryptBuf;
    CDBRecordKeyCopy(&localRecord.key, &record->key);
    localRecord.file = NULL;
    localRecord.key.location = CDB_FS_LOCATION_SD;
    localRecord.database = record->database;
    err = CDBRecordFileCreateBlank(&localRecord);
    if (err != CDB_ERROR_OK) {
        CDBLock();
        CDBRecordClose_(&localRecord);
        CDBUnlock();
        return err;
    }
    err = CDBRecordEncrypt(record, cryptBuf, &localRecord.key, 0x3EC00, &encryptedSize);
    if (err != CDB_ERROR_OK) {
        CDBLock();
        CDBRecordClose_(&localRecord);
        CDBUnlock();
        CDBRecordFileDelete(&localRecord);
        return err;
    }
    err = CDBRecordFileDump(&localRecord, cryptBuf, encryptedSize);
    if (err != CDB_ERROR_OK) {
        CDBLock();
        CDBRecordClose_(&localRecord);
        CDBUnlock();
        return err;
    }
    CDBLock();
    err = CDBRecordClose_(record);
    CDBUnlock();
    if (err != CDB_ERROR_OK) {
        CDBLock();
        CDBRecordClose_(&localRecord);
        CDBUnlock();
        return err;
    }
    CDBLock();
    err = CDBRecordRemove_(record);
    CDBUnlock();
    if (err != CDB_ERROR_OK) {
        CDBLock();
        CDBRecordClose_(&localRecord);
        CDBUnlock();
        return err;
    }
    CDBLock();
    recordFile = localRecord.file;
    CDBRecordKeyCopy(&record->key, &localRecord.key);
    record->database = localRecord.database;
    record->file = localRecord.file;
    record->cryptBuf = localRecord.cryptBuf;
    CDBRecordKeyCopy(&recordFile->key, &localRecord.key);
    CDBUnlock();
    return CDB_ERROR_OK;
}

CDBErr CDBCryptBuffer(void* buffer, u32 size, void* iv, u32* processedSize, BOOL encrypt) {
    NETAESContext context ATTRIBUTE_ALIGN(64);
    u32 offset;
    u32 length;

    if (processedSize) {
        *processedSize = 0;
    }
    if (!NETAESCreate(&context, s_cdbCryptKey, 16, iv)) {
        CDBReportError("NETAESCreate\n");
        return CDB_ERROR_14;
    }
    offset = 0;
    while (offset < size) {
        if (processedSize) {
            *processedSize += 64;
        }
        if (offset + 64 < size) {
            length = 64;
        } else {
            length = size - offset;
            memset(s_cdbCryptBuffer, 0, 64);
        }
        memcpy(s_cdbCryptBuffer, (u8*)buffer + offset, length);
        if (encrypt) {
            if (!NETAESEncrypt(&context, s_cdbCryptBufferResult, s_cdbCryptBuffer, 64)) {
                CDBReportError("NETAESEncrypt\n");
                NETAESDelete(&context);
                return CDB_ERROR_14;
            }
        } else {
            if (!NETAESDecrypt(&context, s_cdbCryptBufferResult, s_cdbCryptBuffer, 64)) {
                CDBReportError("NETAESDecrypt\n");
                NETAESDelete(&context);
                return CDB_ERROR_14;
            }
        }
        memcpy((u8*)buffer + offset, s_cdbCryptBufferResult, 64);
        offset += 64;
    }
    NETAESDelete(&context);
    return CDB_ERROR_OK;
}

static inline int getRecordFileAllocFlag(const CDBRecordFile* file) {
    return file->allocFlag;
}

static inline CDBErr setRecordCurrentWiiId(CDBRecord* record) {
    CDBRecordFile* file = record->file;
    if ((s32)file == 0) {
        return CDB_ERROR_27;
    } else if (getRecordFileAllocFlag(file) == CDB_RECORD_ALLOC_READ) {
        return CDB_ERROR_26;
    } else {
        CDBAttrSetWiiId(&file->attr, CDBGetWiiId());
        return CDB_ERROR_OK;
    }
}

CDBErr CDBRecordEncrypt(CDBRecord* record, void* buffer, CDBRecordKey* key, u32 size, u32* encryptedSize) {
    int fileOffset;
    CDBRecordFile* recordFile;
    CDBErr err;
    u32 dataSize;
    u32 fileSize;
    u32 cryptSize;
    u32 authenticatedSize;
    u8 iv[0x10];
    u8 wiiIdKey[0x40] ATTRIBUTE_ALIGN(64);
    u8 digest[0x14] ATTRIBUTE_ALIGN(64);
    CDBAttrSignature signature ATTRIBUTE_ALIGN(64);
    NETHMACContext hmac ATTRIBUTE_ALIGN(64);

    recordFile = record->file;
    memset(wiiIdKey, 0, sizeof(wiiIdKey));
    memset(&signature, 0, sizeof(signature));
    memset(buffer, 0, size);
    if ((s32)recordFile == 0) {
        return CDB_ERROR_27;
    }
    if (getRecordFileAllocFlag(recordFile) == CDB_RECORD_ALLOC_READ) {
        return CDB_ERROR_26;
    }
    if ((s32)buffer == 0) {
        return CDB_ERROR_1;
    }
    if (setRecordCurrentWiiId(record) != CDB_ERROR_OK) {
        return CDB_ERROR_OK;
    }
    {
        CDBErr result;
        if ((s32)record->file == 0) {
            result = CDB_ERROR_27;
        } else if (getRecordFileAllocFlag((CDBRecordFile*)record->file) == CDB_RECORD_ALLOC_READ) {
            result = CDB_ERROR_26;
        } else {
            CDBAttrInitIV(&((CDBRecordFile*)record->file)->attr);
            result = CDB_ERROR_OK;
        }
        if (result != CDB_ERROR_OK) {
            return CDB_ERROR_OK;
        }
    }
    {
        CDBErr result;
        if ((s32)record->file == 0) {
            result = CDB_ERROR_27;
        } else if (getRecordFileAllocFlag((CDBRecordFile*)record->file) == CDB_RECORD_ALLOC_READ) {
            result = CDB_ERROR_26;
        } else {
            CDBAttrSetKeyStr(&((CDBRecordFile*)record->file)->attr, key);
            result = CDB_ERROR_OK;
        }
        if (result != CDB_ERROR_OK) {
            return CDB_ERROR_OK;
        }
    }
    err = CDBRecordGetFileSize(record, &fileSize);
    CDBAttrSetFileSize(&recordFile->attr, fileSize);
    if (err != CDB_ERROR_OK) {
        return CDB_ERROR_OK;
    }
    CDBLock();
    if ((s32)record->file == 0) {
        CDBReportError("can't get data size of the record ; the record is closed\n");
        err = CDB_ERROR_27;
    } else {
        err = CDBRecordFileGetDataSize(record, &dataSize);
    }
    CDBUnlock();
    if (err != CDB_ERROR_OK) {
        return CDB_ERROR_OK;
    }
    if (size < dataSize + CDB_RECORD_BUFFER_SIZE) {
        return CDB_ERROR_20;
    }
    memcpy(buffer, &recordFile->attr, CDB_RECORD_BUFFER_SIZE);
    CDBLock();
    if ((s32)record->file == 0) {
        err = CDB_ERROR_27;
    } else {
        int position = CDBRecordFileTellData(record);
        if (position < 0) {
            err = CDB_ERROR_CANNOT_OPEN_FILE;
        } else {
            fileOffset = position;
            err = CDB_ERROR_OK;
        }
    }
    CDBUnlock();
    if (err != CDB_ERROR_OK) {
        return CDB_ERROR_OK;
    }
    CDBLock();
    if ((s32)record->file == 0) {
        err = CDB_ERROR_27;
    } else {
        err = CDBRecordFileSeekData(record, 0, CDB_SEEK_BEGIN);
    }
    CDBUnlock();
    if (err != CDB_ERROR_OK) {
        return CDB_ERROR_OK;
    }
    CDBLock();
    if ((s32)record->file == 0) {
        CDBReportError("can't read data in the record; the record is closed\n");
        err = CDB_ERROR_27;
    } else {
        err = CDBRecordFileReadData(record, (u8*)buffer + CDB_RECORD_BUFFER_SIZE, size - CDB_RECORD_BUFFER_SIZE, &dataSize);
    }
    CDBUnlock();
    if (err != CDB_ERROR_OK) {
        return CDB_ERROR_OK;
    }
    CDBLock();
    if ((s32)record->file == 0) {
        err = CDB_ERROR_27;
    } else {
        err = CDBRecordFileSeekData(record, fileOffset, CDB_SEEK_BEGIN);
    }
    CDBUnlock();
    if (err != CDB_ERROR_OK) {
        return CDB_ERROR_OK;
    }
    CDBAttrGetIV(&recordFile->attr, iv);
    err = CDBCryptBuffer((u8*)buffer + CDB_RECORD_BUFFER_SIZE, dataSize, iv, &cryptSize, TRUE);
    if (err != CDB_ERROR_OK) {
        return err;
    }
    CDBGetWiiIdKey((char*)wiiIdKey);
    CDBGetDeviceKey((char*)&wiiIdKey[12]);
    CDBAttrClearSignature((CDBAttr*)buffer);
    authenticatedSize = cryptSize + CDB_RECORD_BUFFER_SIZE;
    NETHMACInit(&hmac, NETGetSHA1Interface(), wiiIdKey, 0x40);
    NETHMACUpdate(&hmac, buffer, authenticatedSize);
    NETHMACGetDigest(&hmac, digest);
    memcpy(((CDBAttrBuf*)buffer)->signature.sha1Hmac, digest, sizeof(digest));
    if (encryptedSize != 0) {
        *encryptedSize = cryptSize + CDB_RECORD_BUFFER_SIZE;
    }
    return CDB_ERROR_OK;
}

CDBErr CDBRecordDecrypt(CDBRecord* record, void* buffer, u32 size, u32* dataSize, CDBRecordKey* key) {
    CDBErr status;
    s32 fileOffset;
    CDBRecordFile* recordFile;
    u32 fileDataSize;
    u32 fileSize;
    u8 iv[16];
    u8 wiiIdKey[64] ATTRIBUTE_ALIGN(16);
    u8 digest[20] ATTRIBUTE_ALIGN(64);
    CDBRecordKey comparisonKey;
    NETHMACContext hmac;
    CDBAttrSignature signature;

    recordFile = record->file;
    memset(wiiIdKey, 0, sizeof(wiiIdKey));
    memset(&signature, 0, sizeof(signature));
    memset(buffer, 0, size);
    if ((s32)recordFile == 0) {
        return CDB_ERROR_27;
    }
    if ((s32)buffer == 0) {
        return CDB_ERROR_1;
    }
    {
        CDBLock();
        if ((s32)record->file == 0) {
            CDBReportError("can't get data size of the record ; the record is closed\n");
            status = CDB_ERROR_27;
        } else {
            status = CDBRecordFileGetDataSize(record, &fileDataSize);
        }
        CDBUnlock();
        if (status != CDB_ERROR_OK) {
            return CDB_ERROR_OK;
        }
    }
    if (size < fileDataSize + CDB_RECORD_BUFFER_SIZE) {
        if (fileDataSize > 0x3E800) {
            return CDB_ERROR_32;
        }
        return CDB_ERROR_20;
    }
    if ((fileDataSize & 0x3F) != 0) {
        return CDB_ERROR_32;
    }
    {
        CDBErr err;
        err = CDBRecordFileReadAttrBuf(record);
        if (err != CDB_ERROR_OK) {
            return CDB_ERROR_32;
        }
    }
    memcpy(buffer, &recordFile->attr, CDB_RECORD_BUFFER_SIZE);
    {
        CDBErr err;
        int offset;
        if ((s32)record->file == 0) {
            err = CDB_ERROR_27;
        } else {
            offset = CDBRecordFileTellDataFile(record);
            if (offset < 0) {
                err = CDB_ERROR_CANNOT_OPEN_FILE;
            } else {
                fileOffset = offset;
                err = CDB_ERROR_OK;
            }
        }
        if (err != CDB_ERROR_OK) {
            return err;
        }
    }
    {
        CDBErr err;
        if ((s32)record->file == 0) {
            err = CDB_ERROR_27;
        } else {
            err = CDBRecordFileSeekDataFile(record, 0, CDB_SEEK_BEGIN);
        }
        if (err != CDB_ERROR_OK) {
            return err;
        }
    }
    {
        CDBErr err;
        err = CDBRecordFileReadDataFile(record, (u8*)buffer + CDB_RECORD_BUFFER_SIZE, size - CDB_RECORD_BUFFER_SIZE, &fileDataSize);
        if (err != CDB_ERROR_OK) {
            return err;
        }
    }
    {
        CDBErr err;
        if ((s32)record->file == 0) {
            err = CDB_ERROR_27;
        } else {
            err = CDBRecordFileSeekDataFile(record, fileOffset, CDB_SEEK_BEGIN);
        }
        if (err != CDB_ERROR_OK) {
            return err;
        }
    }
    CDBAttrGetSignature((CDBAttr*)buffer, &signature);
    CDBAttrClearSignature((CDBAttr*)buffer);
    if ((s32)key == 0) {
        CDBGetWiiIdKey((char*)wiiIdKey);
    } else {
        CDBCopyWiiIdKey((char*)wiiIdKey, (char*)key);
    }
    CDBGetDeviceKey((char*)&wiiIdKey[12]);
    status = fileDataSize + CDB_RECORD_BUFFER_SIZE;
    NETHMACInit(&hmac, NETGetSHA1Interface(), wiiIdKey, 0x40);
    NETHMACUpdate(&hmac, buffer, status);
    NETHMACGetDigest(&hmac, digest);
    if (memcmp(digest, signature.sha1Hmac, 0x14) != 0) {
        return CDB_ERROR_32;
    }
    CDBAttrGetKeyStr((CDBAttr*)buffer, comparisonKey.keyString);
    if (CDBRecordKeyCompareByDate(&comparisonKey, &record->key) != 0) {
        if (CDBIsPrintDebugMessage(3)) {
            CDBReport_(3);
            OSReport("ファイル名の改竄を検出\n");
        }
        return CDB_ERROR_32;
    }
    CDBAttrGetIV(&recordFile->attr, iv);
    {
        CDBErr err;
        err = CDBCryptBuffer((u8*)buffer + CDB_RECORD_BUFFER_SIZE, fileDataSize, iv, NULL, FALSE);
        if (err != CDB_ERROR_OK) {
            return err;
        }
    }
    if (dataSize != 0) {
        CDBAttrGetFileSize((CDBAttr*)buffer, &fileSize);
        *dataSize = fileSize;
    }
    return CDB_ERROR_OK;
}

CDBErr CDBRecordPrivateChangeOwner(CDBRecord* record, u64 newWiiId) {
    CDBRecordFile* recordFile;
    char fullPath[256];
    char newPath[256];
    CDBErr err;
    u64 preWiiId;
    u64 recordWiiId;

    CDBReportError("CDBRecordPrivateChangeOwner\n");

    recordFile = record->file;
    if (recordFile == NULL) {
        return CDB_ERROR_27;
    }
    preWiiId = CDBGetWiiId();
    recordWiiId = record->key.wiiId;
    OSReport(" i_pre-wiiid  = %lX\n", preWiiId);
    OSReport(" record-wiiid = %lX\n", recordWiiId);
    CDBConvKeyToFullPath(&record->key, fullPath);
    record->key.wiiId = newWiiId;
    CDBConvKeyToFullPath(&record->key, newPath);
    OSReport("path =%s\n", fullPath);
    OSReport("path2=%s\n", newPath);
    CDBLock();
    err = CDBAttrSetWiiId(&recordFile->attr, newWiiId);
    CDBUnlock();
    return err;
}
