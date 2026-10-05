#define CDB_DATABASE_IMPLEMENTATION
#include <private/cdb.h>
#include <revolution/cdb.h>
#include <stdlib.h>
#include <revolution/os.h>

extern u16 CDBGetMakerCode();
extern u32 CDBGetInitialCode();
extern void CDBLock();
extern CDBErr CDBDatabaseAllocate(CDBDatabase* database, u32 flags);
extern void CDBUnlock();
extern CDBErr CDBDatabaseFree(CDBDatabase* database);
extern CDBErr CDBRecordCreateAtOnce(CDBRecord* record, CDBDatabase* database, const char* desc, char* fileType, CDBDate epoch, int gameCode, u16 makerCode, void* buffer, u32 size);
extern void CDBRecordInitDescriptor(CDBRecord* record, CDBDatabase* database, CDBRecordKey* key);
extern BOOL CDBRecordIsExistFile(CDBRecord* record);
extern CDBErr CDBRecordOpenReadOnly(CDBRecord* record);
typedef struct {
    CDBRecordKey* records;
    int capacity;
    int size;
    int reverse;
} CDBRecordKeyArray;
typedef struct {
    u32 used;
    CDBRecordKey records[0x400];
} CDBDatabaseSearchBuffer;
extern void CDBRecordKeyArrayInit(CDBRecordKeyArray* array, CDBRecordKey* records, int capacity);
extern void CDBRecordKeyArraySetReverse(CDBRecordKeyArray* array);
extern int CDBRecordKeyArraySize(CDBRecordKeyArray* array);
extern CDBRecordKey* CDBRecordKeyArrayAt(CDBRecordKeyArray* array, int index);
extern BOOL CDBRecordKeyArrayEmpty(CDBRecordKeyArray* array);
extern BOOL CDBRecordKeyArrayFull(CDBRecordKeyArray* array);
extern CDBRecordKey* CDBRecordKeyArrayEnd(CDBRecordKeyArray* array);
extern CDBRecordKey* CDBRecordKeyArrayDicFind(CDBRecordKeyArray* array, CDBRecordKey* key);
extern CDBRecordKey* CDBRecordKeyArrayDicInsert(CDBRecordKeyArray* array, CDBRecordKey* key);
extern void CDBFSFindFirstRoot();
extern CDBErr CDBFSDeleteDir();
extern void CDBFSFindNext();
extern void CDBFSFindClose();
extern BOOL CDBFindDataIsDirectory();
extern char* CDBFindDataGetName();
extern BOOL CDBFindDataIsEnd();
typedef struct {
    int* values;
    int capacity;
    int size;
    int direction;
} CDBIntArray;
extern void CDBIntArrayInit(CDBIntArray* array, int* values, int capacity);
extern void CDBIntArraySetReverse(CDBIntArray* array);
extern BOOL CDBIntArrayFull(CDBIntArray* array);
extern int* CDBIntArrayDicInsert(CDBIntArray* array, int* value);
extern int* CDBIntArrayDicFind(CDBIntArray* array, int* value);
extern int* CDBIntArrayEnd(CDBIntArray* array);
extern BOOL CDBIntArrayEmpty(CDBIntArray* array);
extern int* CDBIntArrayAt(CDBIntArray* array, int index);
extern int CDBIntArraySize(CDBIntArray* array);
extern int CDBIntCompare(const int* left, const int* right);
extern void CDBIntCopy(int* destination, const int* value);
extern void __div2i();
extern void _savegpr_14();
extern void _savegpr_17();
extern void _savegpr_18();
extern void _savegpr_19();
extern void _savegpr_21();
extern void _savegpr_22();
extern void _savegpr_23();
extern void _savegpr_24();
extern void _savegpr_25();
extern void _savegpr_26();
extern void _restgpr_14();
extern void _restgpr_17();
extern void _restgpr_18();
extern void _restgpr_19();
extern void _restgpr_21();
extern void _restgpr_22();
extern void _restgpr_23();
extern void _restgpr_24();
extern void _restgpr_25();
extern void _restgpr_26();
extern int atoi();
#pragma section sdata_type ".sdata"
typedef struct {
    char path[256];
    CDBFindData find;
} CDBDirectoryWork;
typedef struct {
    CDBDirectoryWork record;
    CDBDirectoryWork code;
    CDBDirectoryWork type;
    CDBDirectoryWork minute;
    CDBDirectoryWork hour;
    CDBDirectoryWork day;
    CDBDirectoryWork month;
    CDBFindData year;
} CDBSearchWork;

extern CDBSearchWork* CDBDatabaseWorkBuf;
extern char scCdbMsg_DatabaseClosed[];
extern char scCdbMsg_CantCreateRecordClosed[];
extern char scCdbMsg_CantCreateRecordReadonly[];
extern char scCdbMsg_InvalidKey[];
extern char scCdbMsg_FileNotFound[];
extern char scCdbMsg_CantCleanupDirsClosed[];
extern char scCdbMsg_CantCleanupDirsReadonly[];

extern CDBErr CDBDatabaseInit();
extern CDBErr CDBDatabaseOpen();
extern CDBErr CDBDatabaseClose();
extern CDBErr CDBDatabasePrivateCreateRecordAtOnce();
extern CDBErr CDBDatabaseCreateRecordAtOnce(CDBDatabase* database, CDBRecord* record, const char* typeStr, const char* fileTypeStr, u8* recordData, u32 recordDataSize);
extern CDBErr CDBDatabaseCreateRecordAtOnceEx();
extern CDBErr CDBDatabasePrivateCreateRecordAtOnceEx();
extern CDBErr CDBDatabasePrivateCreateRecordAtOnceEx_(CDBDatabase* database, CDBRecord* record, const char* typeStr, const char* fileTypeStr, int year, int month, int day, int hour, int min, int sec, u8* recordData, u32 recordDataSize, char* makerCode, char* gameCode);
extern CDBErr CDBDatabaseCreateRecordImAtOnce_(CDBDatabase* database, CDBRecord* record, const char* typeStr, const char* fileTypeStr, OSTime time, u32 gameCode, u16 makerCode, void* recordData, u32 recordDataSize);
extern CDBErr CDBDatabaseFindByKey();
typedef struct {
    CDBDate beginDate;
    CDBDate endDate;
    u16 makerCode;
    u32 gameCode;
    char* type;
    CDBSearchDirection direction;
    CDBSearchRecordCB* callback;
    void* callbackArg;
    BOOL keepSearching;
    BOOL openRecord;
    u64 wiiId;
} CDBSearchConditions;
extern CDBErr CDBDatabaseSearchConditionsIsMatch();
extern CDBErr CDBDatabaseSearchCallCallback();
extern CDBErr CDBDatabaseSearchRecordLayer();
extern CDBErr CDBDatabaseSearchMinuteLayer();
extern CDBErr CDBDatabaseSearchHourLayer();
extern CDBErr CDBDatabaseSearchDayLayer();
extern CDBErr CDBDatabaseSearchMonthLayer();
extern CDBErr CDBDatabaseSearchYearLayer(CDBDatabase* database, CDBSearchConditions* conditions, CDBRecordLocation recordLocation);
extern CDBErr CDBDatabaseSearch();
extern CDBErr CDBDatabaseSearch_(CDBDatabase* database, CDBDate beginDate, CDBDate endDate, CDBSearchDirection searchDirection, char* makerCodeStr, char* gameCodeStr, char* type, CDBRecordLocation recordLocation, BOOL openRecord, CDBSearchRecordCB searchRecordCB, void* searchRecordArg, u64* wiiId);
typedef struct {
    u32 used;
    u8 state[0xC00C];
    u32 flags;
    CDBDatabase* database;
} CDBDatabaseState;
extern void CDBDatabaseInstanceInit(CDBDatabaseState* instance, u32 flags, CDBDatabase* database);
extern BOOL CDBDatabaseInstanceIsUsed();
extern BOOL CDBIsSDAvailable();
extern CDBErr CDBMountSD();
extern CDBErr CDBUnmountSDForce();
extern CDBErr CDBDatabaseCleanUpEmptyDirectoriesRecord();
extern CDBErr CDBDatabaseCleanUpEmptyDirectoriesType();
extern CDBErr CDBDatabaseCleanUpEmptyDirectoriesCode();
extern CDBErr CDBDatabaseCleanUpEmptyDirectoriesMinute();
extern CDBErr CDBDatabaseCleanUpEmptyDirectoriesHour();
extern CDBErr CDBDatabaseCleanUpEmptyDirectoriesDay();
extern CDBErr CDBDatabaseCleanUpEmptyDirectoriesMonth();
extern CDBErr CDBDatabaseCleanUpEmptyDirectories();

CDBErr CDBDatabaseInit(CDBDatabase* database) {
    database->makerCode = CDBGetMakerCode();
    database->gameCode = CDBGetInitialCode();
    database->instance = NULL;
    return CDB_ERROR_OK;
}

CDBErr CDBDatabaseOpen(CDBDatabase* database) {
    CDBErr result, status;
    CDBLock();
    status = CDBDatabaseAllocate(database, 3);
    result = CDB_ERROR_OK;
    if (status != CDB_ERROR_OK) result = status;
    CDBUnlock();
    return result;
}

CDBErr CDBDatabaseClose(CDBDatabase* database) {
    CDBErr result;
    CDBErr status;
    CDBDatabaseState* instance;

    CDBLock();
    instance = database->instance;
    if (instance == NULL || instance->flags == 0) {
        CDBReportError(scCdbMsg_DatabaseClosed);
        result = CDB_ERROR_27;
    } else {
        status = CDBDatabaseFree(database);
        if (status != CDB_ERROR_OK) {
            result = status;
        } else {
            instance->flags = 0;
            result = CDB_ERROR_OK;
        }
    }
    CDBUnlock();
    return result;
}

CDBErr CDBDatabasePrivateCreateRecordAtOnce(CDBDatabase* database, CDBRecord* record, const char* typeStr, const char* fileTypeStr, u8* recordData, u32 recordDataSize, char* makerCodeStr, char* gameCodeStr) {
    CDBErr result;
    u16 makerCode;
    u32 gameCode;
    CDBLock();
    if (!CDBIsGameCodeStr(gameCodeStr)) {
        result = CDB_ERROR_4;
    } else if (!CDBIsMakerCodeStr(makerCodeStr)) {
        result = CDB_ERROR_3;
    } else {
        u16 makerValue;
        u32 gameValue;
        OSTime time;
        CDBConvMCStrToMCValue(makerCodeStr, &makerValue);
        CDBConvGCStrToGCValue(gameCodeStr, &gameValue);
        makerCode = makerValue;
        gameCode = gameValue;
        time = OSGetTime();
        CDBLock();
        result = CDBDatabaseCreateRecordImAtOnce_(database, record, typeStr, fileTypeStr, time, gameCode, makerCode, recordData, recordDataSize);
        CDBUnlock();
    }
    CDBUnlock();
    return result;
}

CDBErr CDBDatabaseCreateRecordAtOnce(CDBDatabase* database, CDBRecord* record, const char* typeStr, const char* fileTypeStr, u8* recordData, u32 recordDataSize) {
    OSTime time;
    u32 gameCode;
    u16 makerCode;
    CDBErr result;

    makerCode = database->makerCode;
    gameCode = database->gameCode;
    time = OSGetTime();
    CDBLock();
    result = CDBDatabaseCreateRecordImAtOnce_(database, record, typeStr, fileTypeStr, time, gameCode, makerCode, recordData, recordDataSize);
    CDBUnlock();
    return result;
}

CDBErr CDBDatabaseCreateRecordAtOnceEx(CDBDatabase* database, CDBRecord* record, const char* typeStr, const char* fileTypeStr, u8* recordData, u32 recordDataSize, int year, int month, int day, int hour, int min, int sec) {
    u32 gameCode;
    u16 makerCode;
    CDBErr result;
    OSTime time;
    OSCalendarTime cal;

    cal.year = year;
    cal.mon = month;
    cal.mday = day;
    cal.hour = hour;
    cal.min = min;
    cal.sec = sec;
    cal.msec = 0;
    cal.usec = 0;
    time = OSCalendarTimeToTicks(&cal);
    makerCode = database->makerCode;
    gameCode = database->gameCode;
    CDBLock();
    result = CDBDatabaseCreateRecordImAtOnce_(database, record, typeStr, fileTypeStr, time, gameCode, makerCode, recordData, recordDataSize);
    CDBUnlock();
    return result;
}

CDBErr CDBDatabasePrivateCreateRecordAtOnceEx(CDBDatabase* database, CDBRecord* record, const char* typeStr, const char* fileTypeStr, int year, int month, int day, int hour, int min, int sec, u8* recordData, u32 recordDataSize, char* makerCode, char* gameCode) {
    CDBErr result;
    CDBLock();
    result = CDBDatabasePrivateCreateRecordAtOnceEx_(database, record, typeStr, fileTypeStr, year, month, day, hour, min, sec, recordData, recordDataSize, makerCode, gameCode);
    CDBUnlock();
    return result;
}

CDBErr CDBDatabasePrivateCreateRecordAtOnceEx_(CDBDatabase* database, CDBRecord* record, const char* typeStr, const char* fileTypeStr, int year, int month, int day, int hour, int min, int sec, u8* recordData, u32 recordDataSize, char* makerCode, char* gameCode) {
    u32 gameCodeVal;
    u32 gameValue;
    u16 makerCodeVal;
    u16 makerValue;
    CDBErr result;
    OSTime time;
    OSCalendarTime cal;

    if (!CDBIsGameCodeStr(gameCode)) {
        return CDB_ERROR_4;
    }
    if (!CDBIsMakerCodeStr(makerCode)) {
        return CDB_ERROR_3;
    }
    CDBConvMCStrToMCValue(makerCode, &makerValue);
    CDBConvGCStrToGCValue(gameCode, &gameValue);
    cal.year = year;
    cal.mon = month;
    cal.mday = day;
    cal.hour = hour;
    cal.min = min;
    cal.sec = sec;
    cal.msec = 0;
    cal.usec = 0;
    time = OSCalendarTimeToTicks(&cal);
    makerCodeVal = makerValue;
    gameCodeVal = gameValue;
    CDBLock();
    result = CDBDatabaseCreateRecordImAtOnce_(database, record, typeStr, fileTypeStr, time, gameCodeVal, makerCodeVal, recordData, recordDataSize);
    CDBUnlock();
    return result;
}

CDBErr CDBDatabaseCreateRecordImAtOnce_(CDBDatabase* database, CDBRecord* record, const char* typeStr, const char* fileTypeStr, OSTime time, u32 gameCode, u16 makerCode, void* recordData, u32 recordDataSize) {
    CDBDatabaseState* instance;
    int flags;
    CDBDate date;

    instance = database->instance;
    if (instance == NULL) {
        CDBReportError(scCdbMsg_CantCreateRecordClosed);
        return CDB_ERROR_27;
    }

    flags = instance->flags;
    if ((flags & 2) == 0) {
        if (flags == 0) {
            CDBReportError(scCdbMsg_CantCreateRecordClosed);
            return CDB_ERROR_27;
        }
        CDBReportError(scCdbMsg_CantCreateRecordReadonly);
        return CDB_ERROR_26;
    }

    date = time / (OS_BUS_CLOCK / 4);
    CDBClampCDBDate(&date);
    return CDBRecordCreateAtOnce(record, database, typeStr, (char*)fileTypeStr, date, gameCode, makerCode, recordData, recordDataSize);
}

CDBErr CDBDatabaseFindByKey(CDBDatabase* database, CDBRecord* record, CDBRecordKey* recordKey) {
    CDBErr result;

    CDBLock();
    if (!CDBRecordKeyIsValid(recordKey)) {
        CDBReportError(scCdbMsg_InvalidKey);
        result = CDB_ERROR_5;
    } else {
        CDBRecordInitDescriptor(record, database, recordKey);
        if (!CDBRecordIsExistFile(record)) {
            CDBReportError(scCdbMsg_FileNotFound, recordKey->keyString);
            result = CDB_ERROR_CANNOT_OPEN_FILE;
        } else {
            result = CDB_ERROR_OK;
        }
    }
    CDBUnlock();
    return result;
}

CDBErr CDBDatabaseSearchConditionsIsMatch(CDBSearchConditions* conditions, char* key) {
    struct {
        u16 makerCode;
        u32 gameCode;
        CDBDate date;
        char type[8];
    } decoded;
    CDBConvKeyStrToEpochValue(key, &decoded.date);
    if (conditions->beginDate > decoded.date || decoded.date > conditions->endDate) return CDB_ERROR_OK;
    if (conditions->makerCode != 0xFFFF) {
        CDBConvKeyStrToMakerCode(key, (u32*)&decoded.makerCode);
        if (conditions->makerCode != decoded.makerCode) return CDB_ERROR_OK;
    }
    if (conditions->gameCode != 0xFFFFFFFF) {
        CDBConvKeyStrToGameCode(key, &decoded.gameCode);
        if (conditions->gameCode != decoded.gameCode) return CDB_ERROR_OK;
    }
    if (conditions->type != NULL) {
        CDBConvKeyStrToType(key, decoded.type);
        if (CDBCompareTypeStr(conditions->type, decoded.type)) return CDB_ERROR_OK;
    }
    return CDB_ERROR_1;
}

CDBErr CDBDatabaseSearchCallCallback(CDBDatabase* database, CDBSearchConditions* conditions, CDBRecord* record) {
    CDBDatabaseState* instance;
    u32 flags;
    CDBErr result;

    CDBLock();
    instance = database->instance;
    if (instance != NULL) {
        flags = instance->flags;
    } else {
        flags = 0;
    }
    CDBUnlock();

    if (CDBDatabaseSearchConditionsIsMatch(conditions, record->key.keyString)) {
        if (conditions->openRecord) {
            if (flags & 2) {
                result = CDBRecordOpen(record);
            } else {
                result = CDBRecordOpenReadOnly(record);
            }
            if (result == CDB_ERROR_32) {
                return CDB_ERROR_OK;
            }
        } else {
            result = CDB_ERROR_OK;
        }
        if (result == CDB_ERROR_OK) {
            conditions->keepSearching = conditions->callback(conditions->callbackArg, record);
            if (record->file != NULL) {
                CDBRecordClose(record);
            }
        } else {
            return result;
        }
    }
    return CDB_ERROR_OK;
}

CDBErr CDBDatabaseSearchRecordLayer(CDBDatabase* database, CDBSearchConditions* conditions, char* year, char* month, char* day, char* hour, char* minute, CDBRecordLocation recordLocation) {
    CDBDatabaseSearchBuffer* instance = database->instance;
    CDBFindData* recordFind = &CDBDatabaseWorkBuf->record.find;
    CDBFindData* codeFind = &CDBDatabaseWorkBuf->code.find;
    CDBFindData* typeFind = &CDBDatabaseWorkBuf->type.find;
    CDBDate begin = CDBConvDirStrToCDBDate(year, month, day, hour, minute);
    BOOL finished;
    CDBDate end = begin + 59;
    char* recordPath = CDBDatabaseWorkBuf->record.path;
    char* codePath = CDBDatabaseWorkBuf->code.path;
    char* typePath = CDBDatabaseWorkBuf->type.path;
    CDBRecordKey key;
    CDBRecordKey lastKey;
    CDBRecord record;
    CDBRecordKeyArray keys;
    CDBDate date;
    u32 flags;
    int i;
    CDBErr result;

    if (conditions->callback == NULL) {
        return CDB_ERROR_1;
    }
    CDBRecordKeyInitByOnlyDate(&lastKey, 0);
    CDBRecordKeyArrayInit(&keys, instance->records, 0x400);
    if (conditions->direction == CDB_SEARCH_DIRECTION_LEFT) {
        CDBRecordKeyArraySetReverse(&keys);
        CDBRecordKeyInitByOnlyDate(&lastKey, -1);
    }
    CDBLock();
    if (database->instance != NULL) {
        flags = ((CDBDatabaseState*)database->instance)->flags;
    } else {
        flags = 0;
    }
    CDBUnlock();
    if (flags == 0) {
        return CDB_ERROR_27;
    }
    finished = FALSE;
    while (!finished) {
        finished = TRUE;
        keys.size = 0;
        if (recordLocation & CDB_RECORD_LOCATION_NAND) {
            CDBConvMinuteStrToFullPath(codePath, year, month, day, hour, minute, CDB_FS_LOCATION_NAND, NULL);
            CDBFSFindFirst(codeFind, codePath, CDB_FS_LOCATION_NAND);
            while (!CDBFindDataIsEnd(codeFind)) {
                if (CDBFindDataIsDirectory(codeFind) && CDBFSIsMCGCDirNameOnSD(CDBFindDataGetName(codeFind))) {
                    CDBConvCodeStrToFullPath(typePath, year, month, day, hour, minute, CDBFindDataGetName(codeFind), CDB_FS_LOCATION_NAND, NULL);
                    CDBFSFindFirst(typeFind, typePath, CDB_FS_LOCATION_NAND);
                    while (!CDBFindDataIsEnd(typeFind)) {
                        if (CDBFindDataIsDirectory(typeFind) && CDBFSIsTypeDirNameOnSD(CDBFindDataGetName(typeFind))) {
                            CDBConvTypeStrToFullPath(recordPath, year, month, day, hour, minute, CDBFindDataGetName(codeFind), CDBFindDataGetName(typeFind), CDB_FS_LOCATION_NAND, NULL);
                            CDBFSFindFirst(recordFind, recordPath, CDB_FS_LOCATION_NAND);
                            while (!CDBFindDataIsEnd(recordFind)) {
                                if (!CDBFindDataIsDirectory(recordFind) && CDBFSIsCDBFileOnSD(CDBFindDataGetName(recordFind))) {
                                    CDBRecordKeyInitFromFileName2(&key, CDBFindDataGetName(recordFind), CDBFindDataGetName(codeFind), CDBFindDataGetName(typeFind));
                                    if (keys.reverse * CDBRecordKeyCompare(&key, &lastKey) > 0) {
                                        CDBRecordKey* found = CDBRecordKeyArrayDicFind(&keys, &key);
                                        if (found == CDBRecordKeyArrayEnd(&keys)) {
                                            if (CDBRecordKeyArrayFull(&keys)) {
                                                finished = FALSE;
                                            }
                                            key.location = CDB_FS_LOCATION_NAND;
                                            CDBRecordKeyArrayDicInsert(&keys, &key);
                                        }
                                    }
                                }
                                CDBFSFindNext(recordFind);
                            }
                            CDBFSFindClose(recordFind);
                        }
                        CDBFSFindNext(typeFind);
                    }
                    CDBFSFindClose(typeFind);
                }
                CDBFSFindNext(codeFind);
            }
            CDBFSFindClose(codeFind);
        }
        if (recordLocation & CDB_RECORD_LOCATION_SD) {
            CDBConvMinuteStrToFullPath(codePath, year, month, day, hour, minute, CDB_FS_LOCATION_SD, &conditions->wiiId);
            CDBFSFindFirst(codeFind, codePath, CDB_FS_LOCATION_SD);
            while (!CDBFindDataIsEnd(codeFind)) {
                if (CDBFindDataIsDirectory(codeFind) && CDBFSIsMCGCDirNameOnSD(CDBFindDataGetName(codeFind))) {
                    CDBConvCodeStrToFullPath(typePath, year, month, day, hour, minute, CDBFindDataGetName(codeFind), CDB_FS_LOCATION_SD, &conditions->wiiId);
                    CDBFSFindFirst(typeFind, typePath, CDB_FS_LOCATION_SD);
                    while (!CDBFindDataIsEnd(typeFind)) {
                        if (CDBFindDataIsDirectory(typeFind) && CDBFSIsTypeDirNameOnSD(CDBFindDataGetName(typeFind))) {
                            CDBConvTypeStrToFullPath(recordPath, year, month, day, hour, minute, CDBFindDataGetName(codeFind), CDBFindDataGetName(typeFind), CDB_FS_LOCATION_SD, &conditions->wiiId);
                            CDBFSFindFirst(recordFind, recordPath, CDB_FS_LOCATION_SD);
                            while (!CDBFindDataIsEnd(recordFind)) {
                                if (!CDBFindDataIsDirectory(recordFind) && CDBFSIsCDBFileOnSD(CDBFindDataGetName(recordFind))) {
                                    CDBRecordKeyInitFromFileName2(&key, CDBFindDataGetName(recordFind), CDBFindDataGetName(codeFind), CDBFindDataGetName(typeFind));
                                    CDBConvKeyStrToEpochValue(key.keyString, &date);
                                    if (begin <= date && date <= end && keys.reverse * CDBRecordKeyCompare(&key, &lastKey) > 0) {
                                        CDBRecordKey* found = CDBRecordKeyArrayDicFind(&keys, &key);
                                        if (found == CDBRecordKeyArrayEnd(&keys)) {
                                            if (CDBRecordKeyArrayFull(&keys)) {
                                                finished = FALSE;
                                            }
                                            key.location = CDB_FS_LOCATION_SD;
                                            CDBRecordKeyArrayDicInsert(&keys, &key);
                                        }
                                    }
                                }
                                CDBFSFindNext(recordFind);
                            }
                            CDBFSFindClose(recordFind);
                        }
                        CDBFSFindNext(typeFind);
                    }
                    CDBFSFindClose(typeFind);
                }
                CDBFSFindNext(codeFind);
            }
            CDBFSFindClose(codeFind);
        }
        if (CDBRecordKeyArrayEmpty(&keys)) {
            break;
        }
        if (conditions->direction == CDB_SEARCH_DIRECTION_RIGHT) {
            for (i = 0; i < CDBRecordKeyArraySize(&keys); i++) {
                CDBRecordKey* current = CDBRecordKeyArrayAt(&keys, i);
                CDBRecordInitDescriptor(&record, database, current);
                result = CDBDatabaseSearchCallCallback(database, conditions, &record);
                if (result != CDB_ERROR_OK) {
                    return result;
                }
                CDBRecordKeyCopy(&lastKey, current);
                if (!conditions->keepSearching) {
                    return CDB_ERROR_OK;
                }
            }
        } else {
            for (i = CDBRecordKeyArraySize(&keys) - 1; i >= 0; i--) {
                CDBRecordKey* current = CDBRecordKeyArrayAt(&keys, i);
                CDBRecordInitDescriptor(&record, database, current);
                result = CDBDatabaseSearchCallCallback(database, conditions, &record);
                if (result != CDB_ERROR_OK) {
                    return result;
                }
                CDBRecordKeyCopy(&lastKey, current);
                if (!conditions->keepSearching) {
                    return CDB_ERROR_OK;
                }
            }
        }
    }
    return CDB_ERROR_OK;
}

CDBErr CDBDatabaseSearchMinuteLayer(CDBDatabase* database, CDBSearchConditions* conditions, char* year, char* month, char* day, char* hour, CDBRecordLocation recordLocation) {
    CDBFindData* find = &CDBDatabaseWorkBuf->minute.find;
    char* path = CDBDatabaseWorkBuf->minute.path;
    BOOL finished;
    int yearValue = atoi(year);
    int monthValue = atoi(month);
    int values[60];
    char name[32];
    CDBIntArray array;
    int value;
    int last;
    int index;
    CDBErr result;

    last = -1;
    CDBIntArrayInit(&array, values, 60);
    if (conditions->direction == CDB_SEARCH_DIRECTION_LEFT) {
        CDBIntArraySetReverse(&array);
        last = 60;
    }
    finished = FALSE;
    while (!finished) {
        array.size = 0;
        finished = TRUE;
        if (recordLocation & CDB_RECORD_LOCATION_NAND) {
            CDBConvHourStrToFullPath(path, year, month, day, hour, CDB_FS_LOCATION_NAND, NULL);
            CDBFSFindFirst(find, path, CDB_FS_LOCATION_NAND);
            while (!CDBFindDataIsEnd(find)) {
                if (CDBFindDataIsDirectory(find) && CDBFSIsMinuteDirName(CDBFindDataGetName(find))) {
                    value = atoi(CDBFindDataGetName(find));
                    if (array.direction * CDBIntCompare(&value, &last) > 0) {
                        if (CDBIntArrayFull(&array)) {
                            finished = FALSE;
                        }
                        CDBIntArrayDicInsert(&array, &value);
                    }
                }
                CDBFSFindNext(find);
            }
            CDBFSFindClose(find);
        }
        if (recordLocation & CDB_RECORD_LOCATION_SD) {
            CDBConvHourStrToFullPath(path, year, month, day, hour, CDB_FS_LOCATION_SD, &conditions->wiiId);
            CDBFSFindFirst(find, path, CDB_FS_LOCATION_SD);
            while (!CDBFindDataIsEnd(find)) {
                if (CDBFindDataIsDirectory(find) && CDBFSIsMinuteDirName(CDBFindDataGetName(find))) {
                    value = atoi(CDBFindDataGetName(find));
                    if (array.direction * CDBIntCompare(&value, &last) > 0) {
                        int* found = CDBIntArrayDicFind(&array, &value);
                        if (found == CDBIntArrayEnd(&array)) {
                            if (CDBIntArrayFull(&array)) {
                                finished = FALSE;
                            }
                            CDBIntArrayDicInsert(&array, &value);
                        }
                    }
                }
                CDBFSFindNext(find);
            }
            CDBFSFindClose(find);
        }
        if (CDBIntArrayEmpty(&array)) {
            break;
        }
        if (conditions->direction == CDB_SEARCH_DIRECTION_RIGHT) {
            int* current;
            int index;
            for (index = 0; index < CDBIntArraySize(&array); index++) {
                current = CDBIntArrayAt(&array, index);
                CDBConvMinuteValueToMinuteStr(name, *current);
                result = CDBDatabaseSearchRecordLayer(database, conditions, year, month, day, hour, name, recordLocation);
                if (result != CDB_ERROR_OK) {
                    return result;
                }
                if (!conditions->keepSearching) {
                    return CDB_ERROR_OK;
                }
                CDBIntCopy(&last, current);
            }
        } else {
            for (index = CDBIntArraySize(&array) - 1; index >= 0; index--) {
                int* current = CDBIntArrayAt(&array, index);
                CDBConvMinuteValueToMinuteStr(name, *current);
                result = CDBDatabaseSearchRecordLayer(database, conditions, year, month, day, hour, name, recordLocation);
                if (result != CDB_ERROR_OK) {
                    return result;
                }
                if (!conditions->keepSearching) {
                    return CDB_ERROR_OK;
                }
                CDBIntCopy(&last, current);
            }
        }
    }
    return CDB_ERROR_OK;
}


CDBErr CDBDatabaseSearchHourLayer(CDBDatabase* database, CDBSearchConditions* conditions, char* year, char* month, char* day, CDBRecordLocation recordLocation) {
    CDBFindData* find = &CDBDatabaseWorkBuf->hour.find;
    char* path = CDBDatabaseWorkBuf->hour.path;
    BOOL finished;
    int yearValue = atoi(year);
    int monthValue = atoi(month);
    int values[12];
    char name[32];
    CDBIntArray array;
    int value;
    int last;
    int index;
    CDBErr result;

    last = -1;
    CDBIntArrayInit(&array, values, 12);
    if (conditions->direction == CDB_SEARCH_DIRECTION_LEFT) {
        CDBIntArraySetReverse(&array);
        last = 24;
    }
    finished = FALSE;
    while (!finished) {
        array.size = 0;
        finished = TRUE;
        if (recordLocation & CDB_RECORD_LOCATION_NAND) {
            CDBConvDayStrToFullPath(path, year, month, day, CDB_FS_LOCATION_NAND, NULL);
            CDBFSFindFirst(find, path, CDB_FS_LOCATION_NAND);
            while (!CDBFindDataIsEnd(find)) {
                if (CDBFindDataIsDirectory(find) && CDBFSIsHourDirName(CDBFindDataGetName(find))) {
                    value = atoi(CDBFindDataGetName(find));
                    if (array.direction * CDBIntCompare(&value, &last) > 0) {
                        if (CDBIntArrayFull(&array)) {
                            finished = FALSE;
                        }
                        CDBIntArrayDicInsert(&array, &value);
                    }
                }
                CDBFSFindNext(find);
            }
            CDBFSFindClose(find);
        }
        if (recordLocation & CDB_RECORD_LOCATION_SD) {
            CDBConvDayStrToFullPath(path, year, month, day, CDB_FS_LOCATION_SD, &conditions->wiiId);
            CDBFSFindFirst(find, path, CDB_FS_LOCATION_SD);
            while (!CDBFindDataIsEnd(find)) {
                if (CDBFindDataIsDirectory(find) && CDBFSIsHourDirName(CDBFindDataGetName(find))) {
                    value = atoi(CDBFindDataGetName(find));
                    if (array.direction * CDBIntCompare(&value, &last) > 0) {
                        int* found = CDBIntArrayDicFind(&array, &value);
                        if (found == CDBIntArrayEnd(&array)) {
                            if (CDBIntArrayFull(&array)) {
                                finished = FALSE;
                            }
                            CDBIntArrayDicInsert(&array, &value);
                        }
                    }
                }
                CDBFSFindNext(find);
            }
            CDBFSFindClose(find);
        }
        if (CDBIntArrayEmpty(&array)) {
            break;
        }
        if (conditions->direction == CDB_SEARCH_DIRECTION_RIGHT) {
            int* current;
            int index;
            for (index = 0; index < CDBIntArraySize(&array); index++) {
                current = CDBIntArrayAt(&array, index);
                CDBConvHourValueToHourStr(name, *current);
                result = CDBDatabaseSearchMinuteLayer(database, conditions, year, month, day, name, recordLocation);
                if (result != CDB_ERROR_OK) {
                    return result;
                }
                if (!conditions->keepSearching) {
                    return CDB_ERROR_OK;
                }
                CDBIntCopy(&last, current);
            }
        } else {
            for (index = CDBIntArraySize(&array) - 1; index >= 0; index--) {
                int* current = CDBIntArrayAt(&array, index);
                CDBConvHourValueToHourStr(name, *current);
                result = CDBDatabaseSearchMinuteLayer(database, conditions, year, month, day, name, recordLocation);
                if (result != CDB_ERROR_OK) {
                    return result;
                }
                if (!conditions->keepSearching) {
                    return CDB_ERROR_OK;
                }
                CDBIntCopy(&last, current);
            }
        }
    }
    return CDB_ERROR_OK;
}


CDBErr CDBDatabaseSearchDayLayer(CDBDatabase* database, CDBSearchConditions* conditions, char* year, char* month, CDBRecordLocation recordLocation) {
    int index;
    int* current;
    int* found;
    CDBFindData* find = &CDBDatabaseWorkBuf->day.find;
    char* path = CDBDatabaseWorkBuf->day.path;
    BOOL finished;
    int yearValue = atoi(year);
    int monthValue = atoi(month);
    int values[31];
    char name[32];
    CDBIntArray array;
    int value;
    int last;
    CDBErr result;

    last = 0;
    CDBIntArrayInit(&array, values, 31);
    if (conditions->direction == CDB_SEARCH_DIRECTION_LEFT) {
        CDBIntArraySetReverse(&array);
        last = 32;
    }
    finished = FALSE;
    while (!finished) {
        array.size = 0;
        finished = TRUE;
        if (recordLocation & CDB_RECORD_LOCATION_NAND) {
            CDBConvMonthStrToFullPath(path, year, month, CDB_FS_LOCATION_NAND, NULL);
            CDBFSFindFirst(find, path, CDB_FS_LOCATION_NAND);
            while (!CDBFindDataIsEnd(find)) {
                if (CDBFindDataIsDirectory(find) && CDBFSIsDayDirName(CDBFindDataGetName(find))) {
                    value = atoi(CDBFindDataGetName(find));
                    if (array.direction * CDBIntCompare(&value, &last) > 0) {
                        if (CDBIntArrayFull(&array)) {
                            finished = FALSE;
                        }
                        CDBIntArrayDicInsert(&array, &value);
                    }
                }
                CDBFSFindNext(find);
            }
            CDBFSFindClose(find);
        }
        if (recordLocation & CDB_RECORD_LOCATION_SD) {
            CDBConvMonthStrToFullPath(path, year, month, CDB_FS_LOCATION_SD, &conditions->wiiId);
            CDBFSFindFirst(find, path, CDB_FS_LOCATION_SD);
            while (!CDBFindDataIsEnd(find)) {
                if (CDBFindDataIsDirectory(find) && CDBFSIsDayDirName(CDBFindDataGetName(find))) {
                    value = atoi(CDBFindDataGetName(find));
                    if (array.direction * CDBIntCompare(&value, &last) > 0) {
                        found = CDBIntArrayDicFind(&array, &value);
                        if (found == CDBIntArrayEnd(&array)) {
                            if (CDBIntArrayFull(&array)) {
                                finished = FALSE;
                            }
                            CDBIntArrayDicInsert(&array, &value);
                        }
                    }
                }
                CDBFSFindNext(find);
            }
            CDBFSFindClose(find);
        }
        if (CDBIntArrayEmpty(&array)) {
            break;
        }
        if (conditions->direction == CDB_SEARCH_DIRECTION_RIGHT) {
            int index;
            int* current;
            for (index = 0; index < CDBIntArraySize(&array); index++) {
                current = CDBIntArrayAt(&array, index);
                if (CDBMakeCDBDateDayEnd(yearValue, monthValue, *current) >= conditions->beginDate && conditions->endDate >= CDBMakeCDBDateDayBegin(yearValue, monthValue, *current)) {
                    CDBConvDayValueToDayStr(name, *current);
                    result = CDBDatabaseSearchHourLayer(database, conditions, year, month, name, recordLocation);
                    if (result != CDB_ERROR_OK) {
                        return result;
                    }
                    if (!conditions->keepSearching) {
                        return CDB_ERROR_OK;
                    }
                }
                CDBIntCopy(&last, current);
            }
        } else {
            for (index = CDBIntArraySize(&array) - 1; index >= 0; index--) {
                current = CDBIntArrayAt(&array, index);
                if (CDBMakeCDBDateDayEnd(yearValue, monthValue, *current) >= conditions->beginDate && conditions->endDate >= CDBMakeCDBDateDayBegin(yearValue, monthValue, *current)) {
                    CDBConvDayValueToDayStr(name, *current);
                    result = CDBDatabaseSearchHourLayer(database, conditions, year, month, name, recordLocation);
                    if (result != CDB_ERROR_OK) {
                        return result;
                    }
                    if (!conditions->keepSearching) {
                        return CDB_ERROR_OK;
                    }
                }
                CDBIntCopy(&last, current);
            }
        }
    }
    return CDB_ERROR_OK;
}


CDBErr CDBDatabaseSearchMonthLayer(CDBDatabase* database, CDBSearchConditions* conditions, char* year, CDBRecordLocation recordLocation) {
    int index;
    int* current;
    int* found;
    CDBFindData* find = &CDBDatabaseWorkBuf->month.find;
    char* path = CDBDatabaseWorkBuf->month.path;
    BOOL finished;
    int yearValue = atoi(year);
    int values[12];
    char name[32];
    CDBIntArray array;
    int value;
    int last;
    CDBErr result;

    last = -1;
    CDBIntArrayInit(&array, values, 12);
    if (conditions->direction == CDB_SEARCH_DIRECTION_LEFT) {
        CDBIntArraySetReverse(&array);
        last = 12;
    }
    finished = FALSE;
    while (!finished) {
        array.size = 0;
        finished = TRUE;
        if (recordLocation & CDB_RECORD_LOCATION_NAND) {
            CDBConvYearStrToFullPath(path, year, CDB_FS_LOCATION_NAND, NULL);
            CDBFSFindFirst(find, path, CDB_FS_LOCATION_NAND);
            while (!CDBFindDataIsEnd(find)) {
                if (CDBFindDataIsDirectory(find) && CDBFSIsMonthDirName(CDBFindDataGetName(find))) {
                    value = atoi(CDBFindDataGetName(find));
                    if (array.direction * CDBIntCompare(&value, &last) > 0) {
                        if (CDBIntArrayFull(&array)) {
                            finished = FALSE;
                        }
                        CDBIntArrayDicInsert(&array, &value);
                    }
                }
                CDBFSFindNext(find);
            }
            CDBFSFindClose(find);
        }
        if (recordLocation & CDB_RECORD_LOCATION_SD) {
            CDBConvYearStrToFullPath(path, year, CDB_FS_LOCATION_SD, &conditions->wiiId);
            CDBFSFindFirst(find, path, CDB_FS_LOCATION_SD);
            while (!CDBFindDataIsEnd(find)) {
                if (CDBFindDataIsDirectory(find) && CDBFSIsMonthDirName(CDBFindDataGetName(find))) {
                    value = atoi(CDBFindDataGetName(find));
                    if (array.direction * CDBIntCompare(&value, &last) > 0) {
                        found = CDBIntArrayDicFind(&array, &value);
                        if (found == CDBIntArrayEnd(&array)) {
                            if (CDBIntArrayFull(&array)) {
                                finished = FALSE;
                            }
                            CDBIntArrayDicInsert(&array, &value);
                        }
                    }
                }
                CDBFSFindNext(find);
            }
            CDBFSFindClose(find);
        }
        if (CDBIntArrayEmpty(&array)) {
            break;
        }
        if (conditions->direction == CDB_SEARCH_DIRECTION_RIGHT) {
            int index;
            int* current;
            for (index = 0; index < CDBIntArraySize(&array); index++) {
                current = CDBIntArrayAt(&array, index);
                if (CDBMakeCDBDateMonthEnd(yearValue, *current) >= conditions->beginDate && conditions->endDate >= CDBMakeCDBDateMonthBegin(yearValue, *current)) {
                    CDBConvMonthValueToMonthStr(name, *current);
                    result = CDBDatabaseSearchDayLayer(database, conditions, year, name, recordLocation);
                    if (result != CDB_ERROR_OK) {
                        return result;
                    }
                    if (!conditions->keepSearching) {
                        return CDB_ERROR_OK;
                    }
                }
                CDBIntCopy(&last, current);
            }
        } else {
            for (index = CDBIntArraySize(&array) - 1; index >= 0; index--) {
                current = CDBIntArrayAt(&array, index);
                if (CDBMakeCDBDateMonthEnd(yearValue, *current) >= conditions->beginDate && conditions->endDate >= CDBMakeCDBDateMonthBegin(yearValue, *current)) {
                    CDBConvMonthValueToMonthStr(name, *current);
                    result = CDBDatabaseSearchDayLayer(database, conditions, year, name, recordLocation);
                    if (result != CDB_ERROR_OK) {
                        return result;
                    }
                    if (!conditions->keepSearching) {
                        return CDB_ERROR_OK;
                    }
                }
                CDBIntCopy(&last, current);
            }
        }
    }
    return CDB_ERROR_OK;
}


CDBErr CDBDatabaseSearchYearLayer(CDBDatabase* database, CDBSearchConditions* conditions, CDBRecordLocation recordLocation) {
    int index;
    int* current;
    int* found;
    CDBFindData* find = &CDBDatabaseWorkBuf->year;
    BOOL finished;
    char name[32];
    int values[8];
    CDBIntArray array;
    int value;
    int last;
    CDBErr result;

    if (((u32)database & (u32)conditions) == 0) {
        return CDB_ERROR_1;
    }
    last = 0;
    CDBIntArrayInit(&array, values, 8);
    if (conditions->direction == CDB_SEARCH_DIRECTION_LEFT) {
        CDBIntArraySetReverse(&array);
        last = 9999;
    }
    finished = FALSE;
    while (!finished) {
        array.size = 0;
        finished = TRUE;
        if (recordLocation & CDB_RECORD_LOCATION_NAND) {
            CDBFSFindFirstRoot(find, CDB_FS_LOCATION_NAND);
            while (!CDBFindDataIsEnd(find)) {
                if (CDBFindDataIsDirectory(find) && CDBFSIsYearDirName(CDBFindDataGetName(find))) {
                    value = atoi(CDBFindDataGetName(find));
                    if (array.direction * CDBIntCompare(&value, &last) > 0) {
                        if (CDBIntArrayFull(&array)) {
                            finished = FALSE;
                        }
                        CDBIntArrayDicInsert(&array, &value);
                    }
                }
                CDBFSFindNext(find);
            }
            CDBFSFindClose(find);
        }
        if (recordLocation & CDB_RECORD_LOCATION_SD) {
            CDBFSFindFirstRootEx(find, CDB_FS_LOCATION_SD, &conditions->wiiId);
            while (!CDBFindDataIsEnd(find)) {
                if (CDBFindDataIsDirectory(find) && CDBFSIsYearDirName(CDBFindDataGetName(find))) {
                    value = atoi(CDBFindDataGetName(find));
                    if (array.direction * CDBIntCompare(&value, &last) > 0) {
                        found = CDBIntArrayDicFind(&array, &value);
                        if (found == CDBIntArrayEnd(&array)) {
                            if (CDBIntArrayFull(&array)) {
                                finished = FALSE;
                            }
                            CDBIntArrayDicInsert(&array, &value);
                        }
                    }
                }
                CDBFSFindNext(find);
            }
            CDBFSFindClose(find);
        }
        if (CDBIntArrayEmpty(&array)) {
            break;
        }
        if (conditions->direction == CDB_SEARCH_DIRECTION_RIGHT) {
            int index;
            int* current;
            for (index = 0; index < CDBIntArraySize(&array); index++) {
                current = CDBIntArrayAt(&array, index);
                if (CDBMakeCDBDateYearEnd(*current) >= conditions->beginDate && conditions->endDate >= CDBMakeCDBDateYearBegin(*current)) {
                    CDBConvYearValueToYearStr(name, *current);
                    result = CDBDatabaseSearchMonthLayer(database, conditions, name, recordLocation);
                    if (result != CDB_ERROR_OK) {
                        return result;
                    }
                    if (!conditions->keepSearching) {
                        return CDB_ERROR_OK;
                    }
                }
                CDBIntCopy(&last, current);
            }
        } else {
            for (index = CDBIntArraySize(&array) - 1; index >= 0; index--) {
                current = CDBIntArrayAt(&array, index);
                if (CDBMakeCDBDateYearEnd(*current) >= conditions->beginDate && conditions->endDate >= CDBMakeCDBDateYearBegin(*current)) {
                    CDBConvYearValueToYearStr(name, *current);
                    result = CDBDatabaseSearchMonthLayer(database, conditions, name, recordLocation);
                    if (result != CDB_ERROR_OK) {
                        return result;
                    }
                    if (!conditions->keepSearching) {
                        return CDB_ERROR_OK;
                    }
                }
                CDBIntCopy(&last, current);
            }
        }
    }
    return CDB_ERROR_OK;
}


CDBErr CDBDatabaseSearch(CDBDatabase* database, CDBDate beginDate, CDBDate endDate, CDBSearchDirection searchDirection, char* makerCode, char* gameCode, int unk7, CDBRecordLocation recordLocation, int unk9, CDBSearchRecordCB searchRecordCB, void* searchRecordArg) {
    CDBErr result;
    CDBLock();
    result = CDBDatabaseSearch_(database, beginDate, endDate, searchDirection, makerCode, gameCode, (char*)unk7, recordLocation, unk9, searchRecordCB, searchRecordArg, NULL);
    CDBUnlock();
    return result;
}

CDBErr CDBDatabaseSearch_(CDBDatabase* database, CDBDate beginDate, CDBDate endDate, CDBSearchDirection searchDirection, char* makerCodeStr, char* gameCodeStr, char* type, CDBRecordLocation recordLocation, BOOL openRecord, CDBSearchRecordCB searchRecordCB, void* searchRecordArg, u64* wiiId) {
    CDBSearchConditions conditions;

    if (beginDate < endDate) {
        conditions.beginDate = beginDate;
        conditions.endDate = endDate;
    } else {
        conditions.beginDate = endDate;
        conditions.endDate = beginDate;
    }
    conditions.direction = searchDirection;
    CDBConvMCStrToMCValue(makerCodeStr, &conditions.makerCode);
    CDBConvGCStrToGCValue(gameCodeStr, &conditions.gameCode);
    conditions.type = type;
    conditions.callback = searchRecordCB;
    conditions.callbackArg = searchRecordArg;
    conditions.keepSearching = TRUE;
    conditions.openRecord = openRecord;
    if (wiiId == NULL) {
        conditions.wiiId = 0;
    } else {
        conditions.wiiId = *wiiId;
    }
    return CDBDatabaseSearchYearLayer(database, &conditions, recordLocation);
}


void CDBDatabaseInstanceInit(CDBDatabaseState* instance, u32 flags, CDBDatabase* database) {
    instance->used = 1;
    instance->flags = flags;
    instance->database = database;
}

BOOL CDBDatabaseInstanceIsUsed(CDBDatabaseState* instance) {
    return instance->used;
}

BOOL CDBIsSDAvailable() {
    BOOL available = FALSE;
    if (CDBFSSDIsMounted() && !CDBFSSDIsEjected()) available = TRUE;
    return available;
}

CDBErr CDBMountSD() {
    return CDBFSSDMount();
}

CDBErr CDBUnmountSDForce() {
    CDBErr status = CDBFSSDUnmount();
    CDBErr result = CDB_ERROR_OK;
    if (status != CDB_ERROR_OK) result = status;
    return result;
}

CDBErr CDBDatabaseCleanUpEmptyDirectoriesRecord(char* year, char* month, char* day, char* hour, char* minute, char* code, char* type, int* parentCount, CDBLocation location, u64* wiiId) {
    int count = 0;
    char path[256];
    CDBFindData* find = &CDBDatabaseWorkBuf->record.find;
    CDBErr result;
    CDBConvTypeStrToFullPath(path, year, month, day, hour, minute, code, type, location, wiiId);
    CDBFSFindFirst(find, path, location);
    while (!CDBFindDataIsEnd(find)) {
        count++;
        if (CDBFindDataIsDirectory(find)) CDBFSIsMinuteDirName(CDBFindDataGetName(find));
        CDBFSFindNext(find);
    }
    CDBFSFindClose(find);
    if (count == 2) {
        result = CDBFSDeleteDir(path, location);
        if (result != CDB_ERROR_OK) return result;
        --*parentCount;
    }
    return CDB_ERROR_OK;
}

CDBErr CDBDatabaseCleanUpEmptyDirectoriesType(char* year, char* month, char* day, char* hour, char* minute, char* code, int* parentCount, CDBLocation location, u64* wiiId) {
    int count = 0;
    char path[256];
    CDBFindData* find = &CDBDatabaseWorkBuf->type.find;
    CDBErr result;
    CDBConvCodeStrToFullPath(path, year, month, day, hour, minute, code, location, wiiId);
    CDBFSFindFirst(find, path, location);
    while (!CDBFindDataIsEnd(find)) {
        count++;
        if (CDBFindDataIsDirectory(find) && CDBFSIsTypeDirName(CDBFindDataGetName(find))) {
            result = CDBDatabaseCleanUpEmptyDirectoriesRecord(year, month, day, hour, minute, code, CDBFindDataGetName(find), &count, location, wiiId);
            if (result != CDB_ERROR_OK) return result;
        }
        CDBFSFindNext(find);
    }
    CDBFSFindClose(find);
    if (count == 2) {
        result = CDBFSDeleteDir(path, location);
        if (result != CDB_ERROR_OK) return result;
        --*parentCount;
    }
    return CDB_ERROR_OK;
}

CDBErr CDBDatabaseCleanUpEmptyDirectoriesCode(char* year, char* month, char* day, char* hour, char* minute, int* parentCount, CDBLocation location, u64* wiiId) {
    int count = 0;
    char path[256];
    CDBFindData* find = &CDBDatabaseWorkBuf->code.find;
    CDBErr result;
    CDBConvMinuteStrToFullPath(path, year, month, day, hour, minute, location, wiiId);
    CDBFSFindFirst(find, path, location);
    while (!CDBFindDataIsEnd(find)) {
        count++;
        if (CDBFindDataIsDirectory(find) && CDBFSIsCodeDirName(CDBFindDataGetName(find))) {
            result = CDBDatabaseCleanUpEmptyDirectoriesType(year, month, day, hour, minute, CDBFindDataGetName(find), &count, location, wiiId);
            if (result != CDB_ERROR_OK) return result;
        }
        CDBFSFindNext(find);
    }
    CDBFSFindClose(find);
    if (count == 2) {
        result = CDBFSDeleteDir(path, location);
        if (result != CDB_ERROR_OK) return result;
        --*parentCount;
    }
    return CDB_ERROR_OK;
}

CDBErr CDBDatabaseCleanUpEmptyDirectoriesMinute(char* year, char* month, char* day, char* hour, int* parentCount, CDBLocation location, u64* wiiId) {
    int count = 0;
    char path[256];
    CDBFindData* find = &CDBDatabaseWorkBuf->minute.find;
    CDBErr result;
    CDBConvHourStrToFullPath(path, year, month, day, hour, location, wiiId);
    CDBFSFindFirst(find, path, location);
    while (!CDBFindDataIsEnd(find)) {
        count++;
        if (CDBFindDataIsDirectory(find) && CDBFSIsMinuteDirName(CDBFindDataGetName(find))) {
            result = CDBDatabaseCleanUpEmptyDirectoriesCode(year, month, day, hour, CDBFindDataGetName(find), &count, location, wiiId);
            if (result != CDB_ERROR_OK) return result;
        }
        CDBFSFindNext(find);
    }
    CDBFSFindClose(find);
    if (count == 2) {
        result = CDBFSDeleteDir(path, location);
        if (result != CDB_ERROR_OK) return result;
        --*parentCount;
    }
    return CDB_ERROR_OK;
}

CDBErr CDBDatabaseCleanUpEmptyDirectoriesHour(char* year, char* month, char* day, int* parentCount, CDBLocation location, u64* wiiId) {
    int count = 0;
    char path[256];
    CDBFindData* find = &CDBDatabaseWorkBuf->hour.find;
    CDBErr result;
    CDBConvDayStrToFullPath(path, year, month, day, location, wiiId);
    CDBFSFindFirst(find, path, location);
    while (!CDBFindDataIsEnd(find)) {
        count++;
        if (CDBFindDataIsDirectory(find) && CDBFSIsHourDirName(CDBFindDataGetName(find))) {
            result = CDBDatabaseCleanUpEmptyDirectoriesMinute(year, month, day, CDBFindDataGetName(find), &count, location, wiiId);
            if (result != CDB_ERROR_OK) return result;
        }
        CDBFSFindNext(find);
    }
    CDBFSFindClose(find);
    if (count == 2) {
        result = CDBFSDeleteDir(path, location);
        if (result != CDB_ERROR_OK) return result;
        --*parentCount;
    }
    return CDB_ERROR_OK;
}

CDBErr CDBDatabaseCleanUpEmptyDirectoriesDay(char* year, char* month, int* parentCount, CDBLocation location, u64* wiiId) {
    int count = 0;
    char path[256];
    CDBFindData* find = &CDBDatabaseWorkBuf->day.find;
    CDBErr result;
    CDBConvMonthStrToFullPath(path, year, month, location, wiiId);
    CDBFSFindFirst(find, path, location);
    while (!CDBFindDataIsEnd(find)) {
        count++;
        if (CDBFindDataIsDirectory(find) && CDBFSIsDayDirName(CDBFindDataGetName(find))) {
            result = CDBDatabaseCleanUpEmptyDirectoriesHour(year, month, CDBFindDataGetName(find), &count, location, wiiId);
            if (result != CDB_ERROR_OK) return result;
        }
        CDBFSFindNext(find);
    }
    CDBFSFindClose(find);
    if (count == 2) {
        result = CDBFSDeleteDir(path, location);
        if (result != CDB_ERROR_OK) return result;
        --*parentCount;
    }
    return CDB_ERROR_OK;
}

CDBErr CDBDatabaseCleanUpEmptyDirectoriesMonth(char* year, CDBLocation location, u64* wiiId) {
    int count = 0;
    char path[256];
    CDBFindData* find = &CDBDatabaseWorkBuf->month.find;
    CDBErr result;
    CDBConvYearStrToFullPath(path, year, location, wiiId);
    CDBFSFindFirst(find, path, location);
    while (!CDBFindDataIsEnd(find)) {
        count++;
        if (CDBFindDataIsDirectory(find) && CDBFSIsMonthDirName(CDBFindDataGetName(find))) {
            result = CDBDatabaseCleanUpEmptyDirectoriesDay(year, CDBFindDataGetName(find), &count, location, wiiId);
            if (result != CDB_ERROR_OK) return result;
        }
        CDBFSFindNext(find);
    }
    CDBFSFindClose(find);
    if (count == 2) {
        result = CDBFSDeleteDir(path, location);
        if (result != CDB_ERROR_OK) return result;
    }
    return CDB_ERROR_OK;
}

CDBErr CDBDatabaseCleanUpEmptyDirectories(CDBDatabase* database, CDBRecordLocation recordLocation) {
    CDBDatabase* db;
    CDBFindData* find;
    int flags;
    CDBDatabaseState* instance;
    CDBErr result;
    BOOL sdAvailable;

    db = database;
    find = &CDBDatabaseWorkBuf->year;
    if (db == NULL) {
        return CDB_ERROR_1;
    }

    CDBLock();
    instance = db->instance;
    if (instance != NULL) {
        flags = instance->flags;
    } else {
        flags = 0;
    }
    CDBUnlock();

    if (flags == 0) {
        CDBReportError(scCdbMsg_CantCleanupDirsClosed);
        return CDB_ERROR_27;
    }
    if (flags == 1) {
        CDBReportError(scCdbMsg_CantCleanupDirsReadonly);
        return CDB_ERROR_26;
    }

    if ((recordLocation & 1) != 0) {
        CDBFSFindFirstRoot(find, 1);
        while (CDBFindDataIsEnd(find) == 0) {
            if (CDBFindDataIsDirectory(find) != 0) {
                if (CDBFSIsYearDirName(CDBFindDataGetName(find)) != 0) {
                    result = CDBDatabaseCleanUpEmptyDirectoriesMonth(CDBFindDataGetName(find), 1, NULL);
                    if (result != CDB_ERROR_OK) {
                        return result;
                    }
                }
            }
            CDBFSFindNext(find);
        }
        CDBFSFindClose(find);
    }

    CDBVFSync();
    sdAvailable = 0;
    if (CDBFSSDIsMounted() != 0) {
        if (CDBFSSDIsEjected() == 0) {
            sdAvailable = 1;
        }
    }
    if (sdAvailable != 0) {
        if ((recordLocation & 2) != 0) {
            CDBFSFindFirstRoot(find, 2);
            while (CDBFindDataIsEnd(find) == 0) {
                if (CDBFindDataIsDirectory(find) != 0) {
                    if (CDBFSIsYearDirName(CDBFindDataGetName(find)) != 0) {
                        result = CDBDatabaseCleanUpEmptyDirectoriesMonth(CDBFindDataGetName(find), 2, NULL);
                        if (result != CDB_ERROR_OK) {
                            return result;
                        }
                    }
                }
                CDBFSFindNext(find);
            }
            CDBFSFindClose(find);
        }
    }

    CDBVFSync();
    return CDB_ERROR_OK;
}

#pragma section data_type ".data"
#pragma align 8
extern char scCdbMsg_DatabaseClosed[] = "CDBDatabaseClose database is closed\n";
#pragma align 8
extern char scCdbMsg_CantCreateRecordClosed[] = "can't create record; database is closed\n";
#pragma align 8
extern char scCdbMsg_CantCreateRecordReadonly[] = "can't create record; database is readonly\n";
#pragma align 8
extern char scCdbMsg_InvalidKey[] = "invalid key\n";
#pragma align 8
extern char scCdbMsg_FileNotFound[] = "file not found : %s\n";
#pragma align 8
extern char scCdbMsg_CantCleanupDirsClosed[] = "can't execute CDBDatabaseCleanUpEmptyDirectories; database is closed\n";
#pragma align 8
extern char scCdbMsg_CantCleanupDirsReadonly[] = "can't execute CDBDatabaseCleanUpEmptyDirectories; database is readonly\n";
