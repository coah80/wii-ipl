#include <private/cdb.h>
#include <private/cdb/CDBAttr.h>
#include <private/cdb/CDBConv.h>
#include <private/cdb/CDBCrypt.h>
#include <private/cdb/CDBFileSystem.h>
#include <private/cdb/CDBRecord.h>
#include <private/cdb/CDBReport.h>
#include <revolution/cdb.h>
#include <revolution/net/NETDigest.h>
#include <revolution/os.h>

#include <string.h>

typedef struct {
    u32 used;            // 0x00
    u8 padding[0xC00C];  // 0x04
    u32 flags;           // 0xC010
    u32 unk;             // 0xC014
} CDBDatabaseInstanceWork;

typedef struct {
    u8 buf[0xD0];
} NETHMACContext;

typedef struct {
    u8 buf[0x140];
} NETAesContext;

extern void CDBLock(void);
extern void CDBUnlock(void);
extern BOOL CDBRecordBelongedDBOpenedAsRW(CDBRecord* record);
extern CDBErr CDBCryptBufAllocate(CDBCryptBuf* cryptBuf);
extern CDBErr CDBCryptBufFree(CDBCryptBuf* cryptBuf);
extern void CDBGetWiiIdKey(char* wiiIdKey);
extern void CDBCopyWiiIdKey(char* wiiIdKey1, char* wiiIdKey2);
extern void CDBGetDeviceKey(char* devKey);
extern BOOL CDBFSIsExistFile(const char* fileName, CDBLocation location);

extern const void* NETGetSHA1Interface(void);
extern void NETHMACInit(NETHMACContext* ctx, const void* interface, const void* key, u32 keyLen);
extern void NETHMACUpdate(NETHMACContext* ctx, const void* data, u32 len);
extern void NETHMACGetDigest(NETHMACContext* ctx, void* digest);

extern int NETAESCreate(NETAesContext* ctx, const void* key, u32 keyLen, const void* iv);
extern int NETAESEncrypt(NETAesContext* ctx, void* dst, const void* src, u32 len);
extern int NETAESDecrypt(NETAesContext* ctx, void* dst, const void* src, u32 len);
extern void NETAESDelete(NETAesContext* ctx);

static u8 s_workBuf[0x40] ATTRIBUTE_ALIGN(32);
static u8 s_cryptBuf[0x40];

static const u8 s_aesKey[16] = {0};

CDBErr CDBRecordOpen_(CDBRecord* record);
CDBErr CDBRecordOpenReadOnly_(CDBRecord* record);
CDBErr CDBRecordClose_(CDBRecord* record);
CDBErr CDBRecordWrite_(CDBRecord* record, void* buffer, u32 length);
CDBErr CDBRecordRemove_(CDBRecord* record);
CDBErr CDBRecordSetName_(CDBRecord* record, char* name);
CDBErr CDBRecordUpdateModifiedDate(CDBRecord* record);
CDBErr CDBRecordBackupToSD_(CDBRecord* record);
CDBErr CDBRecordEncrypt(CDBRecord* record, u8* buffer, CDBRecordKey* key, u32 size, u32* cryptFileSize);
CDBErr CDBRecordDecrypt(CDBRecord* record, u8* buffer, u32 size, u32* fileSize, char* wiiIdKey);

void CDBRecordInstanceInit(void* instance, CDBRecord* record, int flag) {
    OSLockMutex(&((CDBRecordFile*)instance)->mutex);
    ((CDBRecordFile*)instance)->used = TRUE;
    OSUnlockMutex(&((CDBRecordFile*)instance)->mutex);

    ((CDBRecordFile*)instance)->unk_0x1C = flag;
    ((CDBRecordFile*)instance)->unk_0x468 = record->unk_0x00;
    CDBAttrInit(&((CDBRecordFile*)instance)->attr);
    CDBRecordKeyCopy(&((CDBRecordFile*)instance)->key, &record->key);
}

BOOL CDBRecordInstanceIsUsed(void* instance) {
    BOOL used;

    OSLockMutex(&((CDBRecordFile*)instance)->mutex);
    used = ((CDBRecordFile*)instance)->used;
    OSUnlockMutex(&((CDBRecordFile*)instance)->mutex);
    return used;
}

void CDBRecordInitDescriptor(CDBRecord* record, CDBDatabase* database, CDBRecordKey* key) {
    CDBLock();
    record->unk_0x00 = (u32)database;
    CDBRecordKeyCopy(&record->key, key);
    record->cryptBuf = NULL;
    record->file = NULL;
    CDBUnlock();
}

CDBErr CDBRecordCreateAtOnce(CDBRecord* record, CDBDatabase* database, char* typeStr, char* fileTypeStr, CDBDate lastModifiedDate,
                             u32 gameCode, u16 makerCode, u8* recordData, u32 recordDataSize) {
    CDBErr err;
    CDBRecordKey key;
    CDBAttr attr;

    if (strlen(fileTypeStr) >= 6) {
        return CDB_ERROR_19;
    }
    if (recordDataSize < CDB_RECORD_BUFFER_SIZE) {
        return CDB_ERROR_20;
    }

    CDBRecordKeyInit(&key, lastModifiedDate, gameCode, makerCode, 0, fileTypeStr, 1);

    CDBLock();
    record->unk_0x00 = (u32)database;
    CDBRecordKeyCopy(&record->key, &key);
    record->cryptBuf = NULL;
    record->file = NULL;
    CDBUnlock();

    err = CDBAttrCreateOnNAND(&attr, typeStr, lastModifiedDate);
    if (err != CDB_ERROR_OK) {
        return err;
    }
    err = CDBAttrSetModifiedCount(&attr, 1);
    if (err != CDB_ERROR_OK) {
        return err;
    }
    memcpy(recordData, &attr, CDB_RECORD_BUFFER_SIZE);
    return CDBRecordFileCreateAtOnce(record, recordData, recordDataSize);
}

CDBErr CDBRecordOpen(CDBRecord* record) {
    CDBErr err;

    CDBLock();
    err = CDBRecordOpen_(record);
    CDBUnlock();
    return err;
}

CDBErr CDBRecordOpen_(CDBRecord* record) {
    CDBErr err;
    CDBDatabaseInstanceWork* instance;
    CDBCryptBuf* cryptBuf;
    char fullPath[256];

    instance = (CDBDatabaseInstanceWork*)((CDBDatabase*)record->unk_0x00)->instance;
    record->cryptBuf = NULL;

    if (instance == NULL) {
        CDBReportError("(CDB) error : can't open the record; the database is closed\n");
        return CDB_ERROR_27;
    }
    if (!(instance->flags & CDB_RECORD_ALLOC_WRITE)) {
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
        err = CDBCryptBufAllocate((CDBCryptBuf*)&record->cryptBuf);
        if (err != CDB_ERROR_OK) {
            return err;
        }
        cryptBuf = (CDBCryptBuf*)record->cryptBuf;
        if (record == NULL || !CDBRecordKeyIsValid(&record->key)) {
            err = CDB_ERROR_1;
        }
        else if (record->key.location != CDB_FS_LOCATION_SD) {
            err = CDB_ERROR_2;
        }
        else if (CDBFSSDIsMounted()) {
            err = CDBRecordDecrypt(record, (u8*)cryptBuf, 0x3EC00, &cryptBuf->unk_0x3EC00, NULL);
        }
        else {
            err = CDB_ERROR_SD_IS_NOT_MOUNTED;
        }
        if (err != CDB_ERROR_OK) {
            CDBCryptBufFree((CDBCryptBuf*)&record->cryptBuf);
            return err;
        }
        cryptBuf->unk_0x3EC04 = CDB_RECORD_BUFFER_SIZE;
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
    CDBErr err;
    CDBCryptBuf* cryptBuf;
    char fullPath[256];

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
        err = CDBCryptBufAllocate((CDBCryptBuf*)&record->cryptBuf);
        if (err != CDB_ERROR_OK) {
            return err;
        }
        cryptBuf = (CDBCryptBuf*)record->cryptBuf;
        if (record == NULL || !CDBRecordKeyIsValid(&record->key)) {
            err = CDB_ERROR_1;
        }
        else if (record->key.location != CDB_FS_LOCATION_SD) {
            err = CDB_ERROR_2;
        }
        else if (CDBFSSDIsMounted()) {
            err = CDBRecordDecrypt(record, (u8*)cryptBuf, 0x3EC00, &cryptBuf->unk_0x3EC00, NULL);
        }
        else {
            err = CDB_ERROR_SD_IS_NOT_MOUNTED;
        }
        if (err != CDB_ERROR_OK) {
            CDBCryptBufFree((CDBCryptBuf*)&record->cryptBuf);
            return err;
        }
        cryptBuf->unk_0x3EC04 = CDB_RECORD_BUFFER_SIZE;
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
    CDBErr err;
    CDBRecordFile* file = (CDBRecordFile*)record->file;

    if (record->cryptBuf != NULL) {
        err = CDBCryptBufFree((CDBCryptBuf*)&record->cryptBuf);
        if (err != CDB_ERROR_OK) {
            return err;
        }
    }
    if (file == NULL) {
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

CDBErr CDBRecordWrite(CDBRecord* record, void* buffer, u32 length) {
    CDBErr err;

    CDBLock();
    err = CDBRecordWrite_(record, buffer, length);
    CDBUnlock();
    return err;
}

CDBErr CDBRecordWrite_(CDBRecord* record, void* buffer, u32 length) {
    CDBErr err;
    CDBRecordFile* file = (CDBRecordFile*)record->file;
    CDBDatabaseInstanceWork* instance = (CDBDatabaseInstanceWork*)((CDBDatabase*)record->unk_0x00)->instance;

    if (record->key.location == CDB_FS_LOCATION_SD) {
        return CDB_ERROR_ACCESS_DENIED;
    }
    if (!(instance->flags & CDB_RECORD_ALLOC_WRITE)) {
        CDBReportError("can't write data in the record; the database is opened as READONLY\n");
        return CDB_ERROR_26;
    }
    if (!CDBRecordBelongedDBOpenedAsRW(record)) {
        CDBReportError("can't write data in the record; permission denied\n");
        return CDB_ERROR_ACCESS_DENIED;
    }
    if (file == NULL) {
        CDBReportError("can't write data in the record; the record is closed\n");
        return CDB_ERROR_27;
    }
    if (!(file->unk_0x1C & CDB_RECORD_ALLOC_WRITE)) {
        CDBReportError("can't write data in the record; the record is opened as READONLY\n");
        return CDB_ERROR_27;
    }
    err = CDBRecordFileWriteData(record, buffer, length);
    if (err != CDB_ERROR_OK) {
        return err;
    }
    err = CDBRecordUpdateModifiedDate(record);
    if (err != CDB_ERROR_OK) {
        return err;
    }
    return CDB_ERROR_OK;
}

CDBErr CDBRecordRead(CDBRecord* record, void* buffer, u32 length, u32* readSize) {
    CDBErr err;

    CDBLock();
    if (record->file == NULL) {
        CDBReportError("can't read data in the record; the record is closed\n");
        err = CDB_ERROR_27;
    }
    else {
        err = CDBRecordFileReadData(record, buffer, length, readSize);
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordSeek(CDBRecord* record, s32 offset, CDBSeek seekOrigin) {
    CDBErr err;

    CDBLock();
    if (record->file == NULL) {
        err = CDB_ERROR_27;
    }
    else {
        switch (seekOrigin) {
            case CDB_SEEK_CUR:
                err = CDBRecordFileSeekData(record, offset, CDB_SEEK_CUR);
                break;
            case CDB_SEEK_BEGIN:
                err = CDBRecordFileSeekData(record, offset, CDB_SEEK_BEGIN);
                break;
            case CDB_SEEK_END:
                err = CDBRecordFileSeekData(record, offset, CDB_SEEK_END);
                break;
            default:
                err = CDB_ERROR_1;
                break;
        }
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordGetFileSize(CDBRecord* record, u32* fileSize) {
    CDBErr err;

    CDBLock();
    if (record->file == NULL) {
        CDBReportError("can't get file size of the record ; the record is closed\n");
        err = CDB_ERROR_27;
    }
    else {
        err = CDBRecordFileGetFileSize(record, fileSize);
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordGetDataSize(CDBRecord* record, u32* recordSize) {
    CDBErr err;

    CDBLock();
    if (record->file == NULL) {
        CDBReportError("can't get data size of the record ; the record is closed\n");
        err = CDB_ERROR_27;
    }
    else {
        err = CDBRecordFileGetDataSize(record, recordSize);
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordReduceFileSize(CDBRecord* record, u32 fileSize) {
    CDBErr err = CDB_ERROR_OK;
    CDBRecordFile* file = (CDBRecordFile*)record->file;

    CDBLock();
    if (file == NULL) {
        CDBReportError("can't reduce file size of the record ; the record is closed\n");
        err = CDB_ERROR_27;
    }
    else if (file->unk_0x1C == CDB_RECORD_ALLOC_READ) {
        CDBReportError("can't reduce file size of the record ; the record is opened as READONLY\n");
        err = CDB_ERROR_26;
    }
    else if (fileSize <= CDB_RECORD_BUFFER_SIZE) {
        CDBReportError("can't reduce file size of the record ; file size must be over %d bytes\n", CDB_RECORD_BUFFER_SIZE);
        err = CDB_ERROR_20;
    }
    else {
        CDBAttrSetFileSize(&file->attr, fileSize);
        err = CDBRecordFileWriteAttrBuf(record);
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordReduceDataSize(CDBRecord* record, u32 dataSize) {
    CDBErr err = CDB_ERROR_OK;
    CDBRecordFile* file = (CDBRecordFile*)record->file;

    CDBLock();
    if (file == NULL) {
        CDBReportError("can't reduce data size of the record ; the record is closed\n");
        err = CDB_ERROR_27;
    }
    else if (file->unk_0x1C == CDB_RECORD_ALLOC_READ) {
        CDBReportError("can't reduce data size of the record ; the record is opened as READONLY\n");
        err = CDB_ERROR_26;
    }
    else if (!CDBRecordBelongedDBOpenedAsRW(record)) {
        CDBReportError("can't reduce data size of the record; permission denied\n");
        err = CDB_ERROR_ACCESS_DENIED;
    }
    CDBUnlock();
    return err;
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
    if (err != CDB_ERROR_OK) {
        return err;
    }
    return CDB_ERROR_OK;
}

CDBErr CDBRecordSetFileType(CDBRecord* record, char* fileType) {
    CDBErr err = CDB_ERROR_OK;
    CDBRecordFile* file = (CDBRecordFile*)record->file;
    CDBDatabaseInstanceWork* instance = (CDBDatabaseInstanceWork*)((CDBDatabase*)record->unk_0x00)->instance;

    CDBLock();
    if (!(instance->flags & CDB_RECORD_ALLOC_WRITE)) {
        CDBReportError("can't set file type of the record; the database is opened as READONLY\n");
        err = CDB_ERROR_26;
    }
    else if (file == NULL) {
        CDBReportError("can't set file type of the record ; the record is closed\n");
        err = CDB_ERROR_27;
    }
    else if (file->unk_0x1C == CDB_RECORD_ALLOC_READ) {
        CDBReportError("can't set file type of the record ; the record is opened as READONLY\n");
        err = CDB_ERROR_26;
    }
    else if (record->key.location != CDB_FS_LOCATION_NAND) {
        CDBReportError("can't set file type of the record ; the record must exsist on NAND\n");
        err = CDB_ERROR_2;
    }
    else {
        memcpy(CDBKeyStrType(file->key.keyString), fileType, CDB_KEYSTR_TYPE_SIZE);
        memcpy(CDBKeyStrType(file->attr.buf.keyString), fileType, CDB_KEYSTR_TYPE_SIZE);
        err = CDBRecordFileWriteAttrBuf(record);
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordGetFileType(CDBRecord* record, char* fileType) {
    CDBErr err = CDB_ERROR_OK;
    CDBRecordFile* file = (CDBRecordFile*)record->file;

    CDBLock();
    if (file == NULL) {
        CDBReportError("can't get file type of the record ; the record is closed\n");
        err = CDB_ERROR_27;
    }
    else {
        CDBConvKeyStrToType(file->key.keyString, fileType);
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordGetGameCode(CDBRecord* record, char* gcStr) {
    CDBErr err = CDB_ERROR_OK;
    CDBRecordFile* file = (CDBRecordFile*)record->file;
    u32 gameCode;

    CDBLock();
    if (file == NULL) {
        CDBReportError("can't get game code of the record ; the record is closed\n");
        err = CDB_ERROR_27;
    }
    else {
        CDBConvKeyStrToGameCode(file->key.keyString, &gameCode);
        CDBConvGCValueToGCStr(gameCode, gcStr);
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordGetMakerCode(CDBRecord* record, char* makerCode) {
    CDBErr err = CDB_ERROR_OK;
    CDBRecordFile* file = (CDBRecordFile*)record->file;

    CDBLock();
    if (file == NULL) {
        CDBReportError("can't get maker code of the record ; the record is closed\n");
        err = CDB_ERROR_27;
    }
    else {
        memcpy(makerCode, CDBKeyStrMakerCode(file->key.keyString), CDB_KEYSTR_MAKER_CODE_SIZE);
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordGetModifiedTime(CDBRecord* record, int* year, int* month, int* day, int* hour, int* min, int* sec) {
    CDBErr err = CDB_ERROR_OK;
    CDBRecordFile* file = (CDBRecordFile*)record->file;

    CDBLock();
    if (file == NULL) {
        CDBReportError("can't get modified time of the record; the record is closed\n");
        err = CDB_ERROR_27;
    }
    else {
        CDBConvEpochValueToDate(file->attr.buf.lastModifiedDate, year, month, day, hour, min, sec);
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordGetModifiedCount(CDBRecord* record, u32* modifiedCount) {
    CDBErr err = CDB_ERROR_OK;
    CDBRecordFile* file = (CDBRecordFile*)record->file;

    CDBLock();
    if (file == NULL) {
        CDBReportError("can't get modified count of the record; the record is closed\n");
        err = CDB_ERROR_27;
    }
    else {
        err = CDBAttrGetModifiedCount(&file->attr, modifiedCount);
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordSetName(CDBRecord* record, char* name) {
    CDBErr err = CDB_ERROR_OK;
    CDBDatabaseInstanceWork* instance = (CDBDatabaseInstanceWork*)((CDBDatabase*)record->unk_0x00)->instance;

    CDBLock();
    if (!(instance->flags & CDB_RECORD_ALLOC_WRITE)) {
        CDBReportError("can't set a name of the record; the database is opened as READONLY\n");
        err = CDB_ERROR_26;
    }
    else {
        err = CDBRecordSetName_(record, name);
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordAddKeyword(CDBRecord* record, char* keyword) {
    CDBErr err = CDB_ERROR_OK;

    CDBLock();
    if (!CDBRecordBelongedDBOpenedAsRW(record)) {
        CDBReportError("can't add keyword to the record; permission denied\n");
        err = CDB_ERROR_ACCESS_DENIED;
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordSetName_(CDBRecord* record, char* name) {
    CDBErr err = CDB_ERROR_OK;
    CDBRecordFile* file = (CDBRecordFile*)record->file;

    CDBLock();
    if (file == NULL) {
        CDBReportError("can't set a name of the record; the record is closed\n");
        err = CDB_ERROR_27;
    }
    else if (file->unk_0x1C == CDB_RECORD_ALLOC_READ) {
        CDBReportError("can't set a name of the record; the record is opened as READONLY\n");
        err = CDB_ERROR_26;
    }
    else {
        file->attr.buf.descLength = strlen(name);
        memcpy(file->attr.buf.desc, name, file->attr.buf.descLength);
        err = CDBRecordFileWriteAttrBuf(record);
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordGetKeyword(CDBRecord* record, char* keyword) {
    CDBErr err = CDB_ERROR_OK;
    CDBRecordFile* file = (CDBRecordFile*)record->file;

    CDBLock();
    if (file == NULL) {
        CDBReportError("can't get keyword from the record; the record is closed\n");
        err = CDB_ERROR_27;
    }
    else {
        memcpy(keyword, file->attr.buf.desc, file->attr.buf.descLength);
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordGetKey(CDBRecord* record, CDBRecordKey* recordKey) {
    CDBErr err = CDB_ERROR_OK;
    CDBRecordFile* file = (CDBRecordFile*)record->file;

    CDBLock();
    if (file == NULL) {
        CDBReportError("can't get key from the record; the record is closed\n");
        err = CDB_ERROR_27;
    }
    else {
        CDBRecordKeyCopy(recordKey, &file->key);
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordGetCalenderTime(CDBRecord* record, int* year, int* month, int* day, int* hour, int* min, int* sec) {
    CDBErr err = CDB_ERROR_OK;
    CDBRecordFile* file = (CDBRecordFile*)record->file;
    CDBDate epoch;
    char epochStr[0x40];

    CDBLock();
    if (file == NULL) {
        CDBReportError("can't get calender time from the record; the record is closed\n");
        err = CDB_ERROR_27;
    }
    else {
        CDBConvKeyStrToEpochStr(file->key.keyString, epochStr);
        CDBConvEpochStrToEpochValue(epochStr, &epoch);
        CDBConvEpochValueToDate(epoch, year, month, day, hour, min, sec);
    }
    CDBUnlock();
    return err;
}

CDBErr CDBRecordGetTypeForce(CDBRecord* record, char* type) {
    CDBLock();
    CDBConvKeyStrToType(record->key.keyString, type);
    CDBUnlock();
}

CDBErr CDBRecordGetGameCodeForce(CDBRecord* record, char* gcStr) {
    u32 gameCode;

    CDBLock();
    CDBConvKeyStrToGameCode(record->key.keyString, &gameCode);
    CDBConvGCValueToGCStr(gameCode, gcStr);
    CDBUnlock();
}

CDBErr CDBRecordGetKeyForce(CDBRecord* record, CDBRecordKey* recordKey) {
    CDBLock();
    CDBRecordKeyCopy(recordKey, &record->key);
    CDBUnlock();
}

CDBErr CDBRecordGetCalendarTimeForce(CDBRecord* record, int* year, int* month, int* day, int* hour, int* min, int* sec) {
    CDBDate epoch;
    char epochStr[0x40];

    CDBLock();
    CDBConvKeyStrToEpochStr(record->key.keyString, epochStr);
    CDBConvEpochStrToEpochValue(epochStr, &epoch);
    CDBConvEpochValueToDate(epoch, year, month, day, hour, min, sec);
    CDBUnlock();
}

CDBErr CDBRecordGetId(CDBRecord* record, CDBId* id) {
    CDBErr err;
    CDBRecordFile* file;
    char epochStr[0x40];

    CDBLock();
    file = (CDBRecordFile*)record->file;
    if (file == NULL) {
        CDBReportError("can't get CDBId of the record ; the record is closed\n");
        err = CDB_ERROR_27;
    }
    else {
        CDBLock();
        if (record->file == NULL) {
            CDBReportError("can't get maker code of the record ; the record is closed\n");
            err = CDB_ERROR_27;
        }
        else {
            CDBLock();
            CDBConvKeyStrToEpochStr(record->key.keyString, epochStr);
            CDBConvEpochStrToEpochValue(epochStr, (CDBDate*)id);
            CDBUnlock();
            err = CDB_ERROR_OK;
        }
        CDBUnlock();
        switch (err) {
        case CDB_ERROR_OK:
            CDBAttrGetIDNumber(&file->attr, (CDBId*)&id->modifiedCount);
            err = CDB_ERROR_OK;
            break;
        }
    }
    CDBUnlock();
    return err;
}

BOOL CDBRecordIsExistFile(CDBRecord* record) {
    char fullPath[256];

    CDBConvKeyToFullPath(&record->key, fullPath);
    return CDBFSIsExistFile(fullPath, record->key.location);
}

CDBErr CDBRecordUpdateModifiedDate(CDBRecord* record) {
    CDBErr err;
    CDBRecordFile* file;
    CDBDatabaseInstanceWork* instance;
    u32 modifiedDate;
    u32 modifiedCount;

    modifiedDate = OSTicksToSeconds(OSGetTime());
    instance = (CDBDatabaseInstanceWork*)((CDBDatabase*)record->unk_0x00)->instance;
    file = (CDBRecordFile*)record->file;
    if (!(instance->flags & CDB_RECORD_ALLOC_WRITE)) {
        CDBReportError("can't set modified time of the record; the database is opened as READONLY\n");
        return CDB_ERROR_26;
    }
    if (file == NULL) {
        CDBReportError("can't set modified time of the record ; the record is closed\n");
        return CDB_ERROR_27;
    }
    err = CDBAttrSetModifiedDate(&file->attr, modifiedDate);
    if (err != CDB_ERROR_OK) {
        return err;
    }
    err = CDBAttrGetModifiedCount(&file->attr, &modifiedCount);
    if (err != CDB_ERROR_OK) {
        return err;
    }
    modifiedCount++;
    err = CDBAttrSetModifiedCount(&file->attr, modifiedCount);
    if (err != CDB_ERROR_OK) {
        return err;
    }
    return CDB_ERROR_OK;
}

CDBErr CDBRecordBackupToSD(CDBRecord* record) {
    CDBErr err;

    CDBLock();
    err = CDBRecordBackupToSD_(record);
    CDBUnlock();
    return err;
}

CDBErr CDBRecordBackupToSD_(CDBRecord* record) {
    CDBErr err;
    CDBRecord sdRecord;
    CDBCryptBuf* cryptBuf;
    CDBRecordFile* file;
    u32 encryptSize;

    sdRecord.cryptBuf = NULL;
    if (record == NULL || !CDBRecordKeyIsValid(&record->key)) {
        return CDB_ERROR_1;
    }
    if (record->key.location != CDB_FS_LOCATION_NAND) {
        return CDB_ERROR_2;
    }
    if (!CDBFSSDIsMounted()) {
        return CDB_ERROR_SD_IS_NOT_MOUNTED;
    }
    err = CDBCryptBufAllocate((CDBCryptBuf*)&sdRecord.cryptBuf);
    if (err != CDB_ERROR_OK) {
        CDBLock();
        CDBRecordClose_(&sdRecord);
        CDBUnlock();
        return err;
    }
    cryptBuf = (CDBCryptBuf*)sdRecord.cryptBuf;

    CDBRecordKeyCopy(&sdRecord.key, &record->key);
    sdRecord.key.location = CDB_FS_LOCATION_SD;
    sdRecord.file = NULL;
    sdRecord.unk_0x00 = record->unk_0x00;

    err = CDBRecordFileCreateBlank(&sdRecord);
    if (err != CDB_ERROR_OK) {
        CDBLock();
        CDBRecordClose_(&sdRecord);
        CDBUnlock();
        return err;
    }
    err = CDBRecordEncrypt(record, (u8*)cryptBuf, &sdRecord.key, 0x3EC00, &encryptSize);
    if (err != CDB_ERROR_OK) {
        CDBLock();
        CDBRecordClose_(&sdRecord);
        CDBUnlock();
        CDBRecordFileDelete(&sdRecord);
        return err;
    }
    err = CDBRecordFileDump(&sdRecord, cryptBuf, encryptSize);
    if (err != CDB_ERROR_OK) {
        CDBLock();
        CDBRecordClose_(&sdRecord);
        CDBUnlock();
        return err;
    }
    CDBLock();
    err = CDBRecordClose_(record);
    CDBUnlock();
    if (err != CDB_ERROR_OK) {
        CDBLock();
        CDBRecordClose_(&sdRecord);
        CDBUnlock();
        return err;
    }
    CDBLock();
    err = CDBRecordRemove_(record);
    CDBUnlock();
    if (err != CDB_ERROR_OK) {
        CDBLock();
        CDBRecordClose_(&sdRecord);
        CDBUnlock();
        return err;
    }
    CDBLock();
    file = (CDBRecordFile*)sdRecord.file;
    CDBRecordKeyCopy(&record->key, &sdRecord.key);
    record->unk_0x00 = sdRecord.unk_0x00;
    record->file = sdRecord.file;
    record->cryptBuf = sdRecord.cryptBuf;
    CDBRecordKeyCopy(&file->key, &sdRecord.key);
    CDBUnlock();
    return CDB_ERROR_OK;
}

CDBErr CDBRecordDuplicate(CDBRecord* record, CDBRecord* duplicate, CDBLocation location) {
    if (location != CDB_FS_LOCATION_NAND && location != CDB_FS_LOCATION_SD) {
        OSReport("CDBRecord.c");
        CDBReportError("CDBRecordDuplicate invalud location\n");
        return CDB_ERROR_1;
    }
    CDBRecordKeyCopy(&duplicate->key, &record->key);
    duplicate->key.location = location;
    duplicate->unk_0x00 = record->unk_0x00;
    duplicate->cryptBuf = NULL;
    duplicate->file = NULL;
    return CDB_ERROR_OK;
}

CDBErr CDBCryptBuffer(u8* buffer, u32 size, u8* iv, u32* cryptSize, BOOL encrypt) {
    NETAesContext aes ATTRIBUTE_ALIGN(64);
    u32 offset;
    u32 cryptLen;

    if (cryptSize != 0) {
        *cryptSize = 0;
    }
    if (!NETAESCreate(&aes, s_aesKey, sizeof(s_aesKey), iv)) {
        CDBReportError("NETAESCreate\n");
        return CDB_ERROR_14;
    }
    for (offset = 0; offset < size; offset += 0x40) {
        if (cryptSize != 0) {
            *cryptSize += 0x40;
        }
        if (offset + 0x40 < size) {
            cryptLen = 0x40;
        }
        else {
            cryptLen = size - offset;
            memset(s_workBuf, 0, 0x40);
        }
        memcpy(s_workBuf, buffer + offset, cryptLen);
        if (encrypt) {
            if (!NETAESEncrypt(&aes, s_cryptBuf, s_workBuf, 0x40)) {
                CDBReportError("NETAESEncrypt\n");
                NETAESDelete(&aes);
                return CDB_ERROR_14;
            }
        }
        else {
            if (!NETAESDecrypt(&aes, s_cryptBuf, s_workBuf, 0x40)) {
                CDBReportError("NETAESDecrypt\n");
                NETAESDelete(&aes);
                return CDB_ERROR_14;
            }
        }
        memcpy(buffer + offset, s_cryptBuf, 0x40);
    }
    NETAESDelete(&aes);
    return CDB_ERROR_OK;
}

CDBErr CDBRecordEncrypt(CDBRecord* record, u8* buffer, CDBRecordKey* key, u32 size, u32* cryptFileSize) {
    CDBErr err;
    CDBRecordFile* file = (CDBRecordFile*)record->file;
    int tell;
    u32 dataSize;
    u32 fileSize;
    u32 cryptSize;
    u8 iv[CDB_ATTR_BUF_KEY_IV_LEN];
    u8 digest[NET_SHA1_DIGEST_SIZE] ATTRIBUTE_ALIGN(64);
    char keyBlob[0x40];
    NETHMACContext ctx;
    CDBAttrSignature signature ATTRIBUTE_ALIGN(64);

    memset(keyBlob, 0, 0x40);
    memset(&signature, 0, sizeof(CDBAttrSignature));
    memset(buffer, 0, size);

    if (file == 0) {
        return CDB_ERROR_27;
    }
    if (file->unk_0x1C == CDB_RECORD_ALLOC_READ) {
        return CDB_ERROR_26;
    }
    if (buffer == 0) {
        return CDB_ERROR_1;
    }

    {
        CDBErr err;
        CDBRecordFile* recordFile = (CDBRecordFile*)record->file;
        if (recordFile == 0) {
            err = CDB_ERROR_27;
        }
        else if (recordFile->unk_0x1C == CDB_RECORD_ALLOC_READ) {
            err = CDB_ERROR_26;
        }
        else {
            CDBAttrSetWiiId(&recordFile->attr, CDBGetWiiId());
            err = CDB_ERROR_OK;
        }
        if (err != CDB_ERROR_OK) {
            return CDB_ERROR_OK;
        }
    }
    {
        CDBErr err;
        CDBRecordFile* recordFile = (CDBRecordFile*)record->file;
        if (recordFile == 0) {
            err = CDB_ERROR_27;
        }
        else if (recordFile->unk_0x1C == CDB_RECORD_ALLOC_READ) {
            err = CDB_ERROR_26;
        }
        else {
            CDBAttrInitIV(&recordFile->attr);
            err = CDB_ERROR_OK;
        }
        if (err != CDB_ERROR_OK) {
            return CDB_ERROR_OK;
        }
    }
    {
        CDBErr err;
        CDBRecordFile* recordFile = (CDBRecordFile*)record->file;
        if (recordFile == 0) {
            err = CDB_ERROR_27;
        }
        else if (recordFile->unk_0x1C == CDB_RECORD_ALLOC_READ) {
            err = CDB_ERROR_26;
        }
        else {
            CDBAttrSetKeyStr(&recordFile->attr, key);
            err = CDB_ERROR_OK;
        }
        if (err != CDB_ERROR_OK) {
            return CDB_ERROR_OK;
        }
    }

    CDBLock();
    if (record->file == 0) {
        CDBReportError("can't get file size of the record ; the record is closed\n");
        err = CDB_ERROR_27;
    }
    else {
        err = CDBRecordFileGetFileSize(record, &fileSize);
    }
    CDBUnlock();
    CDBAttrSetFileSize(&file->attr, fileSize);
    if (err != CDB_ERROR_OK) {
        return CDB_ERROR_OK;
    }

    CDBLock();
    if (record->file == 0) {
        CDBReportError("can't get data size of the record ; the record is closed\n");
        err = CDB_ERROR_27;
    }
    else {
        err = CDBRecordFileGetDataSize(record, &dataSize);
    }
    CDBUnlock();
    if (err != CDB_ERROR_OK) {
        return CDB_ERROR_OK;
    }

    if (size < dataSize + CDB_RECORD_BUFFER_SIZE) {
        return CDB_ERROR_20;
    }
    memcpy(buffer, &file->attr, CDB_RECORD_BUFFER_SIZE);

    CDBLock();
    if (record->file == 0) {
        err = CDB_ERROR_27;
    }
    else {
        {
            int result = CDBRecordFileTellData(record);
            if (result < 0) {
                err = CDB_ERROR_CANNOT_OPEN_FILE;
            }
            else {
                tell = result;
                err = CDB_ERROR_OK;
            }
        }
    }
    CDBUnlock();
    if (err != CDB_ERROR_OK) {
        return CDB_ERROR_OK;
    }

    CDBLock();
    if (record->file == 0) {
        err = CDB_ERROR_27;
    }
    else {
        err = CDBRecordFileSeekData(record, 0, CDB_SEEK_BEGIN);
    }
    CDBUnlock();
    if (err != CDB_ERROR_OK) {
        return CDB_ERROR_OK;
    }

    CDBLock();
    if (record->file == 0) {
        CDBReportError("can't read data in the record; the record is closed\n");
        err = CDB_ERROR_27;
    }
    else {
        err = CDBRecordFileReadData(record, buffer + CDB_RECORD_BUFFER_SIZE, size - CDB_RECORD_BUFFER_SIZE, &dataSize);
    }
    CDBUnlock();
    if (err != CDB_ERROR_OK) {
        return CDB_ERROR_OK;
    }

    CDBLock();
    if (record->file == 0) {
        err = CDB_ERROR_27;
    }
    else {
        err = CDBRecordFileSeekData(record, tell, CDB_SEEK_BEGIN);
    }
    CDBUnlock();
    if (err != CDB_ERROR_OK) {
        return CDB_ERROR_OK;
    }

    CDBAttrGetIV(&file->attr, iv);
    err = CDBCryptBuffer(buffer + CDB_RECORD_BUFFER_SIZE, dataSize, iv, &cryptSize, TRUE);
    if (err != CDB_ERROR_OK) {
        return err;
    }

    CDBGetWiiIdKey(keyBlob);
    CDBGetDeviceKey(keyBlob + 12);
    CDBAttrClearSignature((CDBAttr*)buffer);

    err = cryptSize + CDB_RECORD_BUFFER_SIZE;
    NETHMACInit(&ctx, NETGetSHA1Interface(), keyBlob, 0x40);
    NETHMACUpdate(&ctx, buffer, err);
    NETHMACGetDigest(&ctx, digest);
    memcpy(buffer + offsetof(CDBAttrBuf, signature), digest, NET_SHA1_DIGEST_SIZE);
    if (cryptFileSize != 0) {
        *cryptFileSize = cryptSize + CDB_RECORD_BUFFER_SIZE;
    }
    return CDB_ERROR_OK;
}

CDBErr CDBRecordDecrypt(CDBRecord* record, u8* buffer, u32 size, u32* fileSize, char* wiiIdKey) {
    CDBErr err;
    CDBRecordFile* file = (CDBRecordFile*)record->file;
    u32 dataSize;
    u32 outFileSize;
    u32 realFileSize;
    int tell;
    u8 iv[CDB_ATTR_BUF_KEY_IV_LEN];
    u8 digest[NET_SHA1_DIGEST_SIZE] ATTRIBUTE_ALIGN(64);
    char keyBlob[0x40];
    CDBRecordKey key;
    NETHMACContext ctx;
    CDBAttrSignature signature ATTRIBUTE_ALIGN(64);

    memset(keyBlob, 0, 0x40);
    memset(&signature, 0, sizeof(CDBAttrSignature));
    memset(buffer, 0, size);

    if (file == 0) {
        return CDB_ERROR_27;
    }
    if (buffer == 0) {
        return CDB_ERROR_1;
    }

    CDBLock();
    if (record->file == 0) {
        CDBReportError("can't get data size of the record ; the record is closed\n");
        err = CDB_ERROR_27;
    }
    else {
        err = CDBRecordFileGetDataSize(record, &dataSize);
    }
    CDBUnlock();
    if (err != CDB_ERROR_OK) {
        return CDB_ERROR_OK;
    }

    if (size < dataSize + CDB_RECORD_BUFFER_SIZE) {
        if (dataSize > 0x3E800) {
            return CDB_ERROR_32;
        }
        return CDB_ERROR_20;
    }
    if (dataSize & 0x3F) {
        return CDB_ERROR_32;
    }
    if (CDBRecordFileReadAttrBuf(record) != 0) {
        return CDB_ERROR_32;
    }
    memcpy(buffer, &file->attr, CDB_RECORD_BUFFER_SIZE);

    {
        CDBErr err;
        if (record->file == 0) {
            err = CDB_ERROR_27;
        }
        else {
            int result = CDBRecordFileTellDataFile(record);
            if (result < 0) {
                err = CDB_ERROR_CANNOT_OPEN_FILE;
            }
            else {
                tell = result;
                err = CDB_ERROR_OK;
            }
        }
        if (err != CDB_ERROR_OK) {
            return err;
        }
    }
    {
        CDBErr err;
        if (record->file == 0) {
            err = CDB_ERROR_27;
        }
        else {
            err = CDBRecordFileSeekDataFile(record, 0, CDB_SEEK_BEGIN);
        }
        if (err != CDB_ERROR_OK) {
            return err;
        }
    }

    err = CDBRecordFileReadDataFile(record, buffer + CDB_RECORD_BUFFER_SIZE, size - CDB_RECORD_BUFFER_SIZE, &dataSize);
    if (err != CDB_ERROR_OK) {
        return err;
    }

    {
        CDBErr err;
        if (record->file == 0) {
            err = CDB_ERROR_27;
        }
        else {
            err = CDBRecordFileSeekDataFile(record, tell, CDB_SEEK_BEGIN);
        }
        if (err != CDB_ERROR_OK) {
            return err;
        }
    }

    CDBAttrGetSignature((CDBAttr*)buffer, &signature);
    CDBAttrClearSignature((CDBAttr*)buffer);
    if (wiiIdKey == 0) {
        CDBGetWiiIdKey(keyBlob);
    }
    else {
        CDBCopyWiiIdKey(keyBlob, wiiIdKey);
    }
    CDBGetDeviceKey(keyBlob + 12);

    realFileSize = dataSize + CDB_RECORD_BUFFER_SIZE;
    NETHMACInit(&ctx, NETGetSHA1Interface(), keyBlob, 0x40);
    NETHMACUpdate(&ctx, buffer, realFileSize);
    NETHMACGetDigest(&ctx, digest);
    if (memcmp(digest, &signature, NET_SHA1_DIGEST_SIZE) != 0) {
        return CDB_ERROR_32;
    }

    CDBAttrGetKeyStr((CDBAttr*)buffer, key.keyString);
    if (CDBRecordKeyCompareByDate(&key, &record->key)) {
        CDBReportWarn("ファイル名の改竄を検出\n");
        return CDB_ERROR_32;
    }

    CDBAttrGetIV(&file->attr, iv);
    err = CDBCryptBuffer(buffer + CDB_RECORD_BUFFER_SIZE, dataSize, iv, NULL, FALSE);
    if (err != CDB_ERROR_OK) {
        return err;
    }
    if (fileSize != 0) {
        CDBAttrGetFileSize((CDBAttr*)buffer, &outFileSize);
        *fileSize = outFileSize;
    }
    return CDB_ERROR_OK;
}

void CDBRecordPrivateChangeOwner(CDBRecord* record, u64 wiiId) {
    CDBRecordKey key;
    char fullPath[256];
    char fullPath2[256];

    OSReport("CDBRecordPrivateChangeOwner\n");
    OSReport(" i_pre-wiiid  = %lX\n", record->key.wiiId);
    OSReport(" record-wiiid = %lX\n", wiiId);
    CDBConvKeyToFullPath(&record->key, fullPath);
    OSReport("path =%s\n", fullPath);
    CDBRecordKeyCopy(&key, &record->key);
    key.wiiId = wiiId;
    CDBConvKeyToFullPath(&key, fullPath2);
    OSReport("path2=%s\n", fullPath2);
}

