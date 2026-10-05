#ifndef PRIVATE_CDB_RECORD_H
#define PRIVATE_CDB_RECORD_H

#include <private/cdb/CDBAttr.h>
#include <private/cdb/CDBBridge.h>
#include <revolution/types.h>
#if defined(CDB_RECORD_IMPLEMENTATION) || defined(CDB_SYSTEM_IMPLEMENTATION)
#include <revolution/os.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

typedef struct _CDBRecordFile {
#if defined(CDB_RECORD_IMPLEMENTATION) || defined(CDB_SYSTEM_IMPLEMENTATION)
    OSMutex mutex;
    BOOL used;
#else
    u8 mutexAndUseState[0x1C - 0x00];
#endif
    int allocFlag;  // 0x1C
    CDBAttr attr;              // 0x20
    CDBBridgeFile bridgeFile;  // 0x42C
    u8 reservedBeforeKey[0x438 - 0x434];
    CDBRecordKey key;  // 0x438
#if defined(CDB_RECORD_IMPLEMENTATION) || defined(CDB_SYSTEM_IMPLEMENTATION)
    u32 database;
    u8 reserved[0x480 - 0x46C];
#else
    u8 databaseStateStorage[0x480 - 0x468];
#endif
} CDBRecordFile;

enum {
    CDB_RECORD_ALLOC_READ = (1 << 0),
    CDB_RECORD_ALLOC_WRITE = (1 << 1),
    CDB_RECORD_ALLOC_RW = CDB_RECORD_ALLOC_READ | CDB_RECORD_ALLOC_WRITE
};

/* RECORD POOL */

void CDBRecordPoolInit(void* work);

/* RECORD */

CDBErr CDBRecordAllocate(CDBRecord* record, int flag);
CDBErr CDBRecordFree(CDBRecord* record);

/* RECORD KEY */

BOOL CDBRecordKeyIsValid(CDBRecordKey* recordKey);

void CDBRecordKeyInitByOnlyDate(CDBRecordKey* recordKey, CDBDate epoch);
void CDBRecordKeyInitFromFileName2(CDBRecordKey* recordKey, char* keyString, char* gameCode, char* fileType);
void CDBRecordKeyInit(CDBRecordKey* recordKey, CDBDate epoch, int gameCode, u16 makerCode, int serialNumber, char* fileType, int recordLocation);

void CDBRecordKeyGetKeyStr(CDBRecordKey* recordKey, char* keyString);

void CDBRecordKeySetSerialNumber(CDBRecordKey* recordKey, int serialNum);

void CDBRecordKeyCopy(CDBRecordKey* recordKey, const CDBRecordKey* newRecordKey);

BOOL CDBRecordKeyCompare(CDBRecordKey* recordKey1, CDBRecordKey* recordKey2);
int CDBRecordKeyCompareByDate(CDBRecordKey* recordKey1, CDBRecordKey* recordKey2);

/* RECORD FILE */

CDBErr CDBRecordFileReadAttrBuf(CDBRecord* record);
CDBErr CDBRecordFileWriteAttrBuf(CDBRecord* record);

CDBErr CDBRecordFileCreateBlank(CDBRecord* record);
CDBErr CDBRecordFileCreateAtOnce(CDBRecord* record, void* buffer, u32 size);

CDBErr CDBRecordFileDelete(CDBRecord* record);

CDBErr CDBRecordFileDump(CDBRecord* record, void* buffer, u32 size);

CDBErr CDBRecordFileOpen(CDBRecord* record, char* fileName, int allocFlag);
CDBErr CDBRecordFileClose(CDBRecord* record);

CDBErr CDBRecordFileGetFileSize(CDBRecord* record, u32* fileSize);
CDBErr CDBRecordFileGetDataSize(CDBRecord* record, u32* dataSize);

CDBErr CDBRecordFileWriteData(CDBRecord* record, void* buffer, u32 size);

CDBErr CDBRecordFileReadData(CDBRecord* record, void* buffer, u32 size, u32* readSize);
CDBErr CDBRecordFileReadDataFile(CDBRecord* record, void* buffer, u32 size, u32* readSize);

CDBErr CDBRecordFileSeekData(CDBRecord* record, u32 offset, CDBSeek seek);
CDBErr CDBRecordFileSeekDataFile(CDBRecord* record, u32 offset, CDBSeek seek);

int CDBRecordFileTellData(CDBRecord* record);
int CDBRecordFileTellDataFile(CDBRecord* record);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // PRIVATE_CDB_RECORD_H
