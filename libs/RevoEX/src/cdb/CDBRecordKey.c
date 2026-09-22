#include <private/cdb.h>
#include <revolution/cdb.h>

#include <stdio.h>

typedef struct _CDBRecordKeyArray {
    CDBRecordKey* records;
    int capacity;
    int size;
    int reverse;
} CDBRecordKeyArray;

BOOL CDBRecordKeyIsValid(CDBRecordKey* recordKey) {
    u32 keyLength;
    if (recordKey == NULL) {
        return FALSE;
    }

    keyLength = strlen(recordKey->keyString);
    if (keyLength >= CDB_RECORD_KEY_STRLEN_LEN) {
        if (recordKey->keyStrStruct.pad0 == '_' && recordKey->keyStrStruct.pad1 == '_' && recordKey->keyStrStruct.pad2 == '_' &&
            recordKey->keyStrStruct.pad3 == '.') {
            if (recordKey->location >= CDB_FS_LOCATION_NAND && recordKey->location <= CDB_FS_LOCATION_4) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

void CDBRecordKeyInit(CDBRecordKey* recordKey, CDBDate epoch, int gameCode, u16 makerCode, int serialNumber, char* fileType, int unk) {
    struct {
        char mcStr[4];
        char typeStr[8];
        char gcStr[8];
    } strings;

    u32 typeLength;

    CDBConvMCValueToMCStr(makerCode, strings.mcStr);
    CDBConvGCValueToGCStr(gameCode, strings.gcStr);

    recordKey->wiiId = CDBGetWiiId();
    recordKey->location = unk;

    typeLength = strlen(fileType);
    strcpy(strings.typeStr, fileType);
    CDBToLower(((char*)strings.typeStr), typeLength);

    sprintf(recordKey->keyString, "%010u_%s_%s_%03d.%s", epoch, strings.gcStr, strings.mcStr, serialNumber, strings.typeStr);
}

void CDBRecordKeySetSerialNumber(CDBRecordKey* recordKey, int serialNum) {
    char serialNumStr[16];
    sprintf(serialNumStr, "%03d", serialNum);
    memcpy(CDBKeyStrSerialNumber(recordKey->keyString), serialNumStr, CDB_KEYSTR_SERIAL_NUMBER_SIZE);
}

void CDBRecordKeyInitByOnlyDate(CDBRecordKey* recordKey, CDBDate epoch) {
    sprintf(recordKey->keyString, "%010u", epoch);
}

void CDBRecordKeyInitFromFileName2(CDBRecordKey* recordKey, char* keyString, char* gameCode, char* fileType) {
    int serialNum;
    CDBDate epoch;

    // TODO
    sscanf(keyString, "%X", &epoch);
    sscanf(&keyString[9], "%d", &serialNum);

    sprintf(recordKey->keyString, "%010u_%s_%03d.%s", epoch, gameCode, serialNum, fileType);

    recordKey->wiiId = CDBGetWiiId();
    recordKey->location = CDB_FS_LOCATION_SD;
}

void CDBRecordKeyCopy(CDBRecordKey* recordKey, const CDBRecordKey* newRecordKey) {
    strcpy(recordKey->keyString, newRecordKey->keyString);
    recordKey->wiiId = newRecordKey->wiiId;
    recordKey->location = newRecordKey->location;
}

BOOL CDBRecordKeyCompare(CDBRecordKey* recordKey1, CDBRecordKey* recordKey2) {
    int result = strcmp(recordKey1->keyString, recordKey2->keyString);
    if (result != 0) {
        return result;
    }

    if (recordKey1->location == recordKey2->location) {
        return 0;
    }

    return recordKey1->location < recordKey2->location ? 1 : -1;
}

int CDBRecordKeyCompareByDate(CDBRecordKey* recordKey1, CDBRecordKey* recordKey2) {
    char keyString1[32];
    char keyString2[32];

    CDBConvKeyStrToEpochStr(recordKey1->keyString, keyString1);
    CDBConvKeyStrToEpochStr(recordKey2->keyString, keyString2);
    return strcmp(keyString2, keyString1);
}

void CDBRecordKeyGetKeyStr(CDBRecordKey* recordKey, char* keyString) {
    strcpy(keyString, recordKey->keyString);
}

void CDBRecordKeyArrayInit(CDBRecordKeyArray* recordArray, CDBRecordKey* records, int capacity) {
    recordArray->size = 0;
    recordArray->reverse = 1;
    recordArray->capacity = capacity;
    recordArray->records = records;
}

void CDBRecordKeyArraySetReverse(CDBRecordKeyArray* recordArray) {
    recordArray->reverse = -1;
}

int CDBRecordKeyArraySize(CDBRecordKeyArray* recordArray) {
    return recordArray->size;
}

CDBRecordKey* CDBRecordKeyArrayAt(CDBRecordKeyArray* recordArray, int index) {
    return (CDBRecordKey*)((char*)recordArray->records + index * sizeof(CDBRecordKey));
}

BOOL CDBRecordKeyArrayEmpty(CDBRecordKeyArray* recordArray) {
    return recordArray->size == 0;
}

BOOL CDBRecordKeyArrayFull(CDBRecordKeyArray* recordArray) {
    return recordArray->capacity <= recordArray->size;
}

CDBRecordKey* CDBRecordKeyArrayEnd(CDBRecordKeyArray* recordArray) {
    return recordArray->records + recordArray->size;
}

#pragma dont_inline on

int CDBRecordKeyArrayDicInsertR(CDBRecordKeyArray* recordArray, CDBRecordKey* recordKey, int first, int last) {
    int index;
    int result;

    if (first == last || first == last - 1) {
        result = CDBRecordKeyCompare(recordKey, recordArray->records + first);
        if (result < 0) {
            return first;
        }

        result = CDBRecordKeyCompare(recordKey, recordArray->records + last);
        if (result >= 0) {
            last++;
        }
        return last;
    }

    index = first + (last - first) / 2;
    result = CDBRecordKeyCompare(recordKey, recordArray->records + index);
    if (result < 0) {
        return CDBRecordKeyArrayDicInsertR(recordArray, recordKey, first, index);
    }
    if (result > 0) {
        return CDBRecordKeyArrayDicInsertR(recordArray, recordKey, index, last);
    }

    return index;
}

CDBRecordKey* CDBRecordKeyArrayDicInsert(CDBRecordKeyArray* recordArray, CDBRecordKey* recordKey) {
    int size = recordArray->size;
    int index;
    int moveCount;
    CDBRecordKey* record;

    if (size == 0) {
        if (size < recordArray->capacity) {
            record = recordArray->records + size;
            CDBRecordKeyCopy(record, recordKey);
            recordArray->size++;
        }
        return recordKey;
    }

    if (recordArray->capacity <= size) {
        if (recordArray->reverse == 1) {
            if (size != 0) {
                record = recordArray->records + (size - 1);
            } else {
                record = recordArray->records;
            }
            if (CDBRecordKeyCompare(record, recordKey) < 0) {
                return record;
            }

            recordArray->size--;
            index = CDBRecordKeyArrayDicInsertR(recordArray, recordKey, 0, recordArray->size - 1);
            moveCount = (recordArray->size - index) * sizeof(CDBRecordKey);
            if (recordArray->capacity <= recordArray->size) {
                moveCount -= sizeof(CDBRecordKey);
            }
            if (moveCount > 0) {
                memmove((CDBRecordKey*)((char*)recordArray->records + (index + 1) * sizeof(CDBRecordKey)),
                        (CDBRecordKey*)((char*)recordArray->records + index * sizeof(CDBRecordKey)),
                        moveCount);
            }
            CDBRecordKeyCopy((CDBRecordKey*)((char*)recordArray->records + index * sizeof(CDBRecordKey)), recordKey);
            if (recordArray->size < recordArray->capacity) {
                recordArray->size++;
            }
            return (CDBRecordKey*)((char*)recordArray->records + index * sizeof(CDBRecordKey));
        }

        record = recordArray->records;
        if (CDBRecordKeyCompare(recordKey, record) < 0) {
            return record;
        }

        recordArray->size--;
        if (recordArray->size >= 0 && recordArray->capacity - 1 >= 0) {
            memmove(recordArray->records, recordArray->records + 1, recordArray->size * sizeof(CDBRecordKey));
        }
        index = CDBRecordKeyArrayDicInsertR(recordArray, recordKey, 0, recordArray->size - 1);
        moveCount = (recordArray->size - index) * sizeof(CDBRecordKey);
        if (recordArray->capacity <= recordArray->size) {
            moveCount -= sizeof(CDBRecordKey);
        }
        if (moveCount > 0) {
            memmove((CDBRecordKey*)((char*)recordArray->records + (index + 1) * sizeof(CDBRecordKey)),
                    (CDBRecordKey*)((char*)recordArray->records + index * sizeof(CDBRecordKey)),
                    moveCount);
        }
        CDBRecordKeyCopy((CDBRecordKey*)((char*)recordArray->records + index * sizeof(CDBRecordKey)), recordKey);
        if (recordArray->size < recordArray->capacity) {
            recordArray->size++;
        }
        return (CDBRecordKey*)((char*)recordArray->records + index * sizeof(CDBRecordKey));
    }

    index = CDBRecordKeyArrayDicInsertR(recordArray, recordKey, 0, size - 1);
    moveCount = (recordArray->size - index) * sizeof(CDBRecordKey);
    if (recordArray->capacity <= recordArray->size) {
        moveCount -= sizeof(CDBRecordKey);
    }
    if (moveCount > 0) {
        memmove((CDBRecordKey*)((char*)recordArray->records + (index + 1) * sizeof(CDBRecordKey)),
                (CDBRecordKey*)((char*)recordArray->records + index * sizeof(CDBRecordKey)),
                moveCount);
    }
    CDBRecordKeyCopy((CDBRecordKey*)((char*)recordArray->records + index * sizeof(CDBRecordKey)), recordKey);
    if (recordArray->size < recordArray->capacity) {
        recordArray->size++;
    }
    return (CDBRecordKey*)((char*)recordArray->records + index * sizeof(CDBRecordKey));
}

int CDBRecordKeyArrayDicFindR(CDBRecordKeyArray* recordArray, CDBRecordKey* recordKey, int first, int last) {
    int index;
    int result;

    if (first == last || first == last - 1) {
        result = CDBRecordKeyCompare(recordKey, recordArray->records + first);
        if (result == 0) {
            return first;
        }

        result = CDBRecordKeyCompare(recordKey, recordArray->records + last);
        if (result != 0) {
            return -1;
        }

        return last;
    }

    index = first + (last - first) / 2;
    result = CDBRecordKeyCompare(recordKey, recordArray->records + index);
    if (result < 0) {
        return CDBRecordKeyArrayDicFindR(recordArray, recordKey, first, index);
    }
    if (result > 0) {
        return CDBRecordKeyArrayDicFindR(recordArray, recordKey, index, last);
    }

    return index;
}

#pragma dont_inline reset

CDBRecordKey* CDBRecordKeyArrayDicFind(CDBRecordKeyArray* recordArray, CDBRecordKey* recordKey) {
    int size = recordArray->size;
    int index;

    if (size == 0) {
        return recordArray->records + size;
    }

    index = CDBRecordKeyArrayDicFindR(recordArray, recordKey, 0, size - 1);
    if (index != -1) {
        return recordArray->records + index;
    }

    return recordArray->records + recordArray->size;
}
