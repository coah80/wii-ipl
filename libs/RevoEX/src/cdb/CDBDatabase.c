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
extern void CDBRecordCreateAtOnce();
extern void CDBRecordInitDescriptor(CDBRecord* record, CDBDatabase* database, CDBRecordKey* key);
extern BOOL CDBRecordIsExistFile(CDBRecord* record);
extern void CDBRecordOpenReadOnly();
extern void CDBRecordKeyArrayInit();
extern void CDBRecordKeyArraySetReverse();
extern void CDBRecordKeyArraySize();
extern void CDBRecordKeyArrayAt();
extern void CDBRecordKeyArrayEmpty();
extern void CDBRecordKeyArrayFull();
extern void CDBRecordKeyArrayEnd();
extern void CDBRecordKeyArrayDicFind();
extern void CDBRecordKeyArrayDicInsert();
extern void CDBFSFindFirstRoot();
extern CDBErr CDBFSDeleteDir();
extern void CDBFSFindNext();
extern void CDBFSFindClose();
extern BOOL CDBFindDataIsDirectory();
extern char* CDBFindDataGetName();
extern BOOL CDBFindDataIsEnd();
extern void CDBIntArrayInit();
extern void CDBIntArraySetReverse();
extern void CDBIntArrayFull();
extern void CDBIntArrayDicInsert();
extern void CDBIntArrayDicFind();
extern void CDBIntArrayEnd();
extern void CDBIntArrayEmpty();
extern void CDBIntArrayAt();
extern void CDBIntArraySize();
extern void CDBIntCompare();
extern void CDBIntCopy();
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
extern char lbl_8166B528[];
extern char lbl_8166B550[];
extern char lbl_8166B57C[];
extern char lbl_8166B5A8[];
extern char lbl_8166B5B8[];
extern char lbl_8166B5D0[];
extern char lbl_8166B618[];

extern CDBErr CDBDatabaseInit();
extern CDBErr CDBDatabaseOpen();
extern CDBErr CDBDatabaseClose();
extern CDBErr CDBDatabasePrivateCreateRecordAtOnce();
extern CDBErr CDBDatabaseCreateRecordAtOnce();
extern CDBErr CDBDatabaseCreateRecordAtOnceEx();
extern CDBErr CDBDatabasePrivateCreateRecordAtOnceEx();
extern CDBErr CDBDatabasePrivateCreateRecordAtOnceEx_();
extern CDBErr CDBDatabaseCreateRecordImAtOnce_();
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
extern CDBErr CDBDatabaseSearchYearLayer();
extern CDBErr CDBDatabaseSearch();
extern CDBErr CDBDatabaseSearch_();
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
        CDBReportError(lbl_8166B528);
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

asm CDBErr CDBDatabaseCreateRecordAtOnce(CDBDatabase* database, CDBRecord* record, const char* typeStr, const char* fileTypeStr, u8* recordData, u32 recordDataSize) {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    addi r11, r1, 0x40
    bl _savegpr_22
    lhz r28, 0x0(r3)
    mr r22, r3
    lwz r29, 0x4(r3)
    mr r23, r4
    mr r24, r5
    mr r25, r6
    mr r26, r7
    mr r27, r8
    bl OSGetTime
    mr r30, r4
    mr r31, r3
    bl CDBLock
    stw r26, 0x8(r1)
    mr r3, r22
    mr r4, r23
    mr r5, r24
    stw r27, 0xc(r1)
    mr r6, r25
    mr r8, r30
    mr r7, r31
    mr r9, r29
    mr r10, r28
    bl CDBDatabaseCreateRecordImAtOnce_
    mr r28, r3
    bl CDBUnlock
    addi r11, r1, 0x40
    mr r3, r28
    bl _restgpr_22
    lwz r0, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
#endif
}

asm CDBErr CDBDatabaseCreateRecordAtOnceEx(CDBDatabase* database, CDBRecord* record, const char* typeStr, const char* fileTypeStr, u8* recordData, u32 recordDataSize, int year, int month, int day, int hour, int min, int sec) {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    addi r11, r1, 0x60
    bl _savegpr_22
    lwz r28, 0x68(r1)
    mr r23, r4
    li r0, 0x0
    lwz r12, 0x6c(r1)
    lwz r11, 0x70(r1)
    mr r22, r3
    lwz r4, 0x74(r1)
    mr r24, r5
    stw r9, 0x24(r1)
    mr r25, r6
    mr r26, r7
    mr r27, r8
    stw r10, 0x20(r1)
    addi r3, r1, 0x10
    stw r28, 0x1c(r1)
    stw r12, 0x18(r1)
    stw r11, 0x14(r1)
    stw r4, 0x10(r1)
    stw r0, 0x30(r1)
    stw r0, 0x34(r1)
    bl OSCalendarTimeToTicks
    lhz r30, 0x0(r22)
    mr r28, r4
    lwz r31, 0x4(r22)
    mr r29, r3
    bl CDBLock
    stw r26, 0x8(r1)
    mr r3, r22
    mr r4, r23
    mr r5, r24
    stw r27, 0xc(r1)
    mr r6, r25
    mr r8, r28
    mr r7, r29
    mr r9, r31
    mr r10, r30
    bl CDBDatabaseCreateRecordImAtOnce_
    mr r30, r3
    bl CDBUnlock
    addi r11, r1, 0x60
    mr r3, r30
    bl _restgpr_22
    lwz r0, 0x64(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
#endif
}

CDBErr CDBDatabasePrivateCreateRecordAtOnceEx(CDBDatabase* database, CDBRecord* record, const char* typeStr, const char* fileTypeStr, int year, int month, int day, int hour, int min, int sec, u8* recordData, u32 recordDataSize, char* makerCode, char* gameCode) {
    CDBErr result;
    CDBLock();
    result = CDBDatabasePrivateCreateRecordAtOnceEx_(database, record, typeStr, fileTypeStr, year, month, day, hour, min, sec, recordData, recordDataSize, makerCode, gameCode);
    CDBUnlock();
    return result;
}

asm CDBErr CDBDatabasePrivateCreateRecordAtOnceEx_() {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x80(r1)
    mflr r0
    stw r0, 0x84(r1)
    addi r11, r1, 0x80
    bl _savegpr_18
    lwz r24, 0x9c(r1)
    mr r28, r3
    lwz r27, 0x88(r1)
    mr r29, r4
    lwz r26, 0x8c(r1)
    mr r30, r5
    lwz r22, 0x90(r1)
    mr r31, r6
    lwz r23, 0x94(r1)
    mr r18, r7
    lwz r25, 0x98(r1)
    mr r19, r8
    mr r20, r9
    mr r21, r10
    mr r3, r24
    bl CDBIsGameCodeStr
    cmpwi r3, 0x0
    bne L_81487844
    li r3, 0x4
    b L_814878EC
    L_81487844:
    mr r3, r25
    bl CDBIsMakerCodeStr
    cmpwi r3, 0x0
    bne L_8148785C
    li r3, 0x3
    b L_814878EC
    L_8148785C:
    mr r3, r25
    addi r4, r1, 0x10
    bl CDBConvMCStrToMCValue
    mr r3, r24
    addi r4, r1, 0x14
    bl CDBConvGCStrToGCValue
    li r0, 0x0
    stw r18, 0x2c(r1)
    addi r3, r1, 0x18
    stw r19, 0x28(r1)
    stw r20, 0x24(r1)
    stw r21, 0x20(r1)
    stw r27, 0x1c(r1)
    stw r26, 0x18(r1)
    stw r0, 0x38(r1)
    stw r0, 0x3c(r1)
    bl OSCalendarTimeToTicks
    lhz r26, 0x10(r1)
    mr r24, r4
    lwz r27, 0x14(r1)
    mr r25, r3
    bl CDBLock
    stw r22, 0x8(r1)
    mr r3, r28
    mr r4, r29
    mr r5, r30
    stw r23, 0xc(r1)
    mr r6, r31
    mr r8, r24
    mr r7, r25
    mr r9, r27
    mr r10, r26
    bl CDBDatabaseCreateRecordImAtOnce_
    mr r26, r3
    bl CDBUnlock
    mr r3, r26
    L_814878EC:
    addi r11, r1, 0x80
    bl _restgpr_18
    lwz r0, 0x84(r1)
    mtlr r0
    addi r1, r1, 0x80
    blr
#endif
}

asm CDBErr CDBDatabaseCreateRecordImAtOnce_() {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    addi r11, r1, 0x40
    bl _savegpr_24
    lwz r11, 0x8(r3)
    mr r24, r3
    lwz r30, 0x48(r1)
    mr r25, r4
    cmpwi r11, 0x0
    lwz r31, 0x4c(r1)
    mr r26, r5
    mr r27, r6
    mr r28, r9
    mr r29, r10
    bne L_81487974
    li r3, 0x2
    bl CDBIsPrintDebugMessage
    cmpwi r3, 0x0
    beq L_8148796C
    li r3, 0x2
    bl CDBReport_
    lis r3, lbl_8166B550@ha
    addi r3, r3, lbl_8166B550@l
    crclr 4*cr1+eq
    bl OSReport
    L_8148796C:
    li r3, 0x1b
    b L_81487A3C
    L_81487974:
    addis r3, r11, 0x1
    lwz r3, -0x3ff0(r3)
    rlwinm. r0, r3, 0, 30, 30
    bne L_814879EC
    cmpwi r3, 0x0
    bne L_814879BC
    li r3, 0x2
    bl CDBIsPrintDebugMessage
    cmpwi r3, 0x0
    beq L_814879B4
    li r3, 0x2
    bl CDBReport_
    lis r3, lbl_8166B550@ha
    addi r3, r3, lbl_8166B550@l
    crclr 4*cr1+eq
    bl OSReport
    L_814879B4:
    li r3, 0x1b
    b L_81487A3C
    L_814879BC:
    li r3, 0x2
    bl CDBIsPrintDebugMessage
    cmpwi r3, 0x0
    beq L_814879E4
    li r3, 0x2
    bl CDBReport_
    lis r3, lbl_8166B57C@ha
    addi r3, r3, lbl_8166B57C@l
    crclr 4*cr1+eq
    bl OSReport
    L_814879E4:
    li r3, 0x1a
    b L_81487A3C
    L_814879EC:
    lis r4, 0x8000
    mr r3, r7
    lwz r0, 0xf8(r4)
    mr r4, r8
    li r5, 0x0
    srwi r6, r0, 2
    bl __div2i
    stw r4, 0x10(r1)
    addi r3, r1, 0x10
    bl CDBClampCDBDate
    stw r31, 0x8(r1)
    mr r3, r25
    mr r4, r24
    mr r5, r26
    lwz r7, 0x10(r1)
    mr r6, r27
    mr r8, r28
    mr r9, r29
    mr r10, r30
    bl CDBRecordCreateAtOnce
    L_81487A3C:
    addi r11, r1, 0x40
    bl _restgpr_24
    lwz r0, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
#endif
}

CDBErr CDBDatabaseFindByKey(CDBDatabase* database, CDBRecord* record, CDBRecordKey* recordKey) {
    CDBErr result;

    CDBLock();
    if (!CDBRecordKeyIsValid(recordKey)) {
        CDBReportError(lbl_8166B5A8);
        result = CDB_ERROR_5;
    } else {
        CDBRecordInitDescriptor(record, database, recordKey);
        if (!CDBRecordIsExistFile(record)) {
            CDBReportError(lbl_8166B5B8, recordKey->keyString);
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

asm CDBErr CDBDatabaseSearchCallCallback() {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    stw r30, 0x18(r1)
    mr r30, r5
    stw r29, 0x14(r1)
    mr r29, r4
    bl CDBLock
    lwz r3, 0x8(r31)
    cmpwi r3, 0x0
    beq L_81487C78
    addis r3, r3, 0x1
    lwz r31, -0x3ff0(r3)
    b L_81487C7C
    L_81487C78:
    li r31, 0x0
    L_81487C7C:
    bl CDBUnlock
    mr r3, r29
    addi r4, r30, 0x8
    bl CDBDatabaseSearchConditionsIsMatch
    cmpwi r3, 0x0
    beq L_81487D0C
    lwz r0, 0x24(r29)
    cmpwi r0, 0x0
    beq L_81487CCC
    rlwinm. r0, r31, 0, 30, 30
    beq L_81487CB4
    mr r3, r30
    bl CDBRecordOpen
    b L_81487CBC
    L_81487CB4:
    mr r3, r30
    bl CDBRecordOpenReadOnly
    L_81487CBC:
    cmpwi r3, 0x20
    bne L_81487CD0
    li r3, 0x0
    b L_81487D10
    L_81487CCC:
    li r3, 0x0
    L_81487CD0:
    cmpwi r3, 0x0
    bne L_81487D10
    lwz r12, 0x18(r29)
    mr r4, r30
    lwz r3, 0x1c(r29)
    mtctr r12
    bctrl
    stw r3, 0x20(r29)
    lwz r0, 0x38(r30)
    cmpwi r0, 0x0
    beq L_81487D0C
    mr r3, r30
    bl CDBRecordClose
    b L_81487D0C
    b L_81487D10
    L_81487D0C:
    li r3, 0x0
    L_81487D10:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
#endif
}

asm CDBErr CDBDatabaseSearchRecordLayer() {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x120(r1)
    mflr r0
    stw r0, 0x124(r1)
    addi r11, r1, 0x120
    bl _savegpr_14
    lwz r11, CDBDatabaseWorkBuf(r0)
    mr r20, r5
    mr r22, r7
    mr r24, r9
    mr r21, r6
    mr r23, r8
    mr r19, r4
    lwz r14, 0x8(r3)
    stw r3, 0x10(r1)
    mr r15, r10
    mr r3, r20
    mr r4, r21
    mr r5, r22
    mr r6, r23
    mr r7, r24
    addi r30, r11, 0x100
    addi r29, r11, 0xa94
    addi r28, r11, 0x1428
    bl CDBConvDirStrToCDBDate
    lwz r0, 0x18(r19)
    mr r31, r3
    lwz r25, CDBDatabaseWorkBuf(r0)
    addi r26, r3, 0x3b
    cmpwi r0, 0x0
    addi r0, r25, 0x994
    stw r0, 0xcc(r1)
    addi r0, r25, 0x1328
    stw r0, 0xc8(r1)
    bne L_81487DBC
    li r3, 0x1
    b L_81488410
    L_81487DBC:
    addi r3, r1, 0x68
    li r4, 0x0
    bl CDBRecordKeyInitByOnlyDate
    addi r3, r1, 0x18
    addi r4, r14, 0x8
    li r5, 0x400
    bl CDBRecordKeyArrayInit
    lwz r0, 0x14(r19)
    cmpwi r0, 0x0
    bne L_81487DF8
    addi r3, r1, 0x18
    bl CDBRecordKeyArraySetReverse
    addi r3, r1, 0x68
    li r4, -0x1
    bl CDBRecordKeyInitByOnlyDate
    L_81487DF8:
    bl CDBLock
    lwz r3, 0x10(r1)
    lwz r3, 0x8(r3)
    cmpwi r3, 0x0
    beq L_81487E18
    addis r3, r3, 0x1
    lwz r14, -0x3ff0(r3)
    b L_81487E1C
    L_81487E18:
    li r14, 0x0
    L_81487E1C:
    bl CDBUnlock
    cmpwi r14, 0x0
    bne L_81487E30
    li r3, 0x1b
    b L_81488410
    L_81487E30:
    clrlwi r0, r15, 31
    li r27, 0x0
    stw r0, 0xd4(r1)
    rlwinm r0, r15, 0, 30, 30
    li r18, 0x2
    li r15, 0x1
    stw r0, 0xd0(r1)
    li r14, 0x0
    b L_81488404
    L_81487E54:
    lwz r0, 0xd4(r1)
    li r27, 0x1
    stw r14, 0x20(r1)
    cmpwi r0, 0x0
    beq L_81488094
    lwz r3, 0xcc(r1)
    mr r4, r20
    mr r5, r21
    mr r6, r22
    mr r7, r23
    mr r8, r24
    li r9, 0x1
    li r10, 0x0
    bl CDBConvMinuteStrToFullPath
    lwz r4, 0xcc(r1)
    mr r3, r29
    li r5, 0x1
    bl CDBFSFindFirst
    b L_8148807C
    L_81487EA0:
    mr r3, r29
    bl CDBFindDataIsDirectory
    cmpwi r3, 0x0
    beq L_81488074
    mr r3, r29
    bl CDBFindDataGetName
    bl CDBFSIsMCGCDirNameOnSD
    cmpwi r3, 0x0
    beq L_81488074
    mr r3, r29
    bl CDBFindDataGetName
    mr r9, r3
    stw r14, 0x8(r1)
    lwz r3, 0xc8(r1)
    mr r4, r20
    mr r5, r21
    mr r6, r22
    mr r7, r23
    mr r8, r24
    li r10, 0x1
    bl CDBConvCodeStrToFullPath
    lwz r4, 0xc8(r1)
    mr r3, r28
    li r5, 0x1
    bl CDBFSFindFirst
    b L_8148805C
    L_81487F08:
    mr r3, r28
    bl CDBFindDataIsDirectory
    cmpwi r3, 0x0
    beq L_81488054
    mr r3, r28
    bl CDBFindDataGetName
    bl CDBFSIsTypeDirNameOnSD
    cmpwi r3, 0x0
    beq L_81488054
    mr r3, r28
    bl CDBFindDataGetName
    mr r16, r3
    mr r3, r29
    bl CDBFindDataGetName
    stw r15, 0x8(r1)
    mr r9, r3
    mr r3, r25
    mr r4, r20
    stw r14, 0xc(r1)
    mr r5, r21
    mr r6, r22
    mr r7, r23
    mr r8, r24
    mr r10, r16
    bl CDBConvTypeStrToFullPath
    mr r3, r30
    mr r4, r25
    li r5, 0x1
    bl CDBFSFindFirst
    b L_8148803C
    L_81487F80:
    mr r3, r30
    bl CDBFindDataIsDirectory
    cmpwi r3, 0x0
    bne L_81488034
    mr r3, r30
    bl CDBFindDataGetName
    bl CDBFSIsCDBFileOnSD
    cmpwi r3, 0x0
    beq L_81488034
    mr r3, r28
    bl CDBFindDataGetName
    mr r17, r3
    mr r3, r29
    bl CDBFindDataGetName
    mr r16, r3
    mr r3, r30
    bl CDBFindDataGetName
    mr r4, r3
    mr r5, r16
    mr r6, r17
    addi r3, r1, 0x98
    bl CDBRecordKeyInitFromFileName2
    addi r3, r1, 0x98
    addi r4, r1, 0x68
    bl CDBRecordKeyCompare
    lwz r0, 0x24(r1)
    mullw. r0, r0, r3
    ble L_81488034
    addi r3, r1, 0x18
    addi r4, r1, 0x98
    bl CDBRecordKeyArrayDicFind
    mr r16, r3
    addi r3, r1, 0x18
    bl CDBRecordKeyArrayEnd
    cmplw r16, r3
    bne L_81488034
    addi r3, r1, 0x18
    bl CDBRecordKeyArrayFull
    cmpwi r3, 0x0
    beq L_81488024
    li r27, 0x0
    L_81488024:
    stw r15, 0xc0(r1)
    addi r3, r1, 0x18
    addi r4, r1, 0x98
    bl CDBRecordKeyArrayDicInsert
    L_81488034:
    mr r3, r30
    bl CDBFSFindNext
    L_8148803C:
    mr r3, r30
    bl CDBFindDataIsEnd
    cmpwi r3, 0x0
    beq L_81487F80
    mr r3, r30
    bl CDBFSFindClose
    L_81488054:
    mr r3, r28
    bl CDBFSFindNext
    L_8148805C:
    mr r3, r28
    bl CDBFindDataIsEnd
    cmpwi r3, 0x0
    beq L_81487F08
    mr r3, r28
    bl CDBFSFindClose
    L_81488074:
    mr r3, r29
    bl CDBFSFindNext
    L_8148807C:
    mr r3, r29
    bl CDBFindDataIsEnd
    cmpwi r3, 0x0
    beq L_81487EA0
    mr r3, r29
    bl CDBFSFindClose
    L_81488094:
    lwz r0, 0xd0(r1)
    cmpwi r0, 0x0
    beq L_814882F4
    lwz r3, 0xcc(r1)
    mr r4, r20
    mr r5, r21
    mr r6, r22
    mr r7, r23
    mr r8, r24
    addi r10, r19, 0x28
    li r9, 0x2
    bl CDBConvMinuteStrToFullPath
    lwz r4, 0xcc(r1)
    mr r3, r29
    li r5, 0x2
    bl CDBFSFindFirst
    b L_814882DC
    L_814880D8:
    mr r3, r29
    bl CDBFindDataIsDirectory
    cmpwi r3, 0x0
    beq L_814882D4
    mr r3, r29
    bl CDBFindDataGetName
    bl CDBFSIsMCGCDirNameOnSD
    cmpwi r3, 0x0
    beq L_814882D4
    mr r3, r29
    bl CDBFindDataGetName
    addi r0, r19, 0x28
    mr r9, r3
    stw r0, 0x8(r1)
    mr r4, r20
    lwz r3, 0xc8(r1)
    mr r5, r21
    mr r6, r22
    mr r7, r23
    mr r8, r24
    li r10, 0x2
    bl CDBConvCodeStrToFullPath
    lwz r4, 0xc8(r1)
    mr r3, r28
    li r5, 0x2
    bl CDBFSFindFirst
    b L_814882BC
    L_81488144:
    mr r3, r28
    bl CDBFindDataIsDirectory
    cmpwi r3, 0x0
    beq L_814882B4
    mr r3, r28
    bl CDBFindDataGetName
    bl CDBFSIsTypeDirNameOnSD
    cmpwi r3, 0x0
    beq L_814882B4
    mr r3, r28
    bl CDBFindDataGetName
    mr r16, r3
    mr r3, r29
    bl CDBFindDataGetName
    stw r18, 0x8(r1)
    addi r0, r19, 0x28
    mr r9, r3
    mr r3, r25
    stw r0, 0xc(r1)
    mr r4, r20
    mr r5, r21
    mr r6, r22
    mr r7, r23
    mr r8, r24
    mr r10, r16
    bl CDBConvTypeStrToFullPath
    mr r3, r30
    mr r4, r25
    li r5, 0x2
    bl CDBFSFindFirst
    b L_8148829C
    L_814881C0:
    mr r3, r30
    bl CDBFindDataIsDirectory
    cmpwi r3, 0x0
    bne L_81488294
    mr r3, r30
    bl CDBFindDataGetName
    bl CDBFSIsCDBFileOnSD
    cmpwi r3, 0x0
    beq L_81488294
    mr r3, r28
    bl CDBFindDataGetName
    mr r16, r3
    mr r3, r29
    bl CDBFindDataGetName
    mr r17, r3
    mr r3, r30
    bl CDBFindDataGetName
    mr r4, r3
    mr r5, r17
    mr r6, r16
    addi r3, r1, 0x98
    bl CDBRecordKeyInitFromFileName2
    addi r3, r1, 0x98
    addi r4, r1, 0x14
    bl CDBConvKeyStrToEpochValue
    lwz r0, 0x14(r1)
    cmplw r31, r0
    bgt L_81488294
    cmplw r0, r26
    bgt L_81488294
    addi r3, r1, 0x98
    addi r4, r1, 0x68
    bl CDBRecordKeyCompare
    lwz r0, 0x24(r1)
    mullw. r0, r0, r3
    ble L_81488294
    addi r3, r1, 0x18
    addi r4, r1, 0x98
    bl CDBRecordKeyArrayDicFind
    mr r16, r3
    addi r3, r1, 0x18
    bl CDBRecordKeyArrayEnd
    cmplw r16, r3
    bne L_81488294
    addi r3, r1, 0x18
    bl CDBRecordKeyArrayFull
    cmpwi r3, 0x0
    beq L_81488284
    li r27, 0x0
    L_81488284:
    stw r18, 0xc0(r1)
    addi r3, r1, 0x18
    addi r4, r1, 0x98
    bl CDBRecordKeyArrayDicInsert
    L_81488294:
    mr r3, r30
    bl CDBFSFindNext
    L_8148829C:
    mr r3, r30
    bl CDBFindDataIsEnd
    cmpwi r3, 0x0
    beq L_814881C0
    mr r3, r30
    bl CDBFSFindClose
    L_814882B4:
    mr r3, r28
    bl CDBFSFindNext
    L_814882BC:
    mr r3, r28
    bl CDBFindDataIsEnd
    cmpwi r3, 0x0
    beq L_81488144
    mr r3, r28
    bl CDBFSFindClose
    L_814882D4:
    mr r3, r29
    bl CDBFSFindNext
    L_814882DC:
    mr r3, r29
    bl CDBFindDataIsEnd
    cmpwi r3, 0x0
    beq L_814880D8
    mr r3, r29
    bl CDBFSFindClose
    L_814882F4:
    addi r3, r1, 0x18
    bl CDBRecordKeyArrayEmpty
    cmpwi r3, 0x0
    bne L_8148840C
    lwz r0, 0x14(r19)
    cmpwi r0, 0x1
    bne L_8148838C
    li r16, 0x0
    b L_81488378
    L_81488318:
    mr r4, r16
    addi r3, r1, 0x18
    bl CDBRecordKeyArrayAt
    mr r17, r3
    lwz r4, 0x10(r1)
    mr r5, r17
    addi r3, r1, 0x28
    bl CDBRecordInitDescriptor
    lwz r3, 0x10(r1)
    mr r4, r19
    addi r5, r1, 0x28
    bl CDBDatabaseSearchCallCallback
    cmpwi r3, 0x0
    beq L_81488354
    b L_81488410
    L_81488354:
    mr r4, r17
    addi r3, r1, 0x68
    bl CDBRecordKeyCopy
    lwz r0, 0x20(r19)
    cmpwi r0, 0x0
    bne L_81488374
    li r3, 0x0
    b L_81488410
    L_81488374:
    addi r16, r16, 0x1
    L_81488378:
    addi r3, r1, 0x18
    bl CDBRecordKeyArraySize
    cmpw r16, r3
    blt L_81488318
    b L_81488404
    L_8148838C:
    addi r3, r1, 0x18
    bl CDBRecordKeyArraySize
    subi r16, r3, 0x1
    b L_814883FC
    L_8148839C:
    mr r4, r16
    addi r3, r1, 0x18
    bl CDBRecordKeyArrayAt
    mr r17, r3
    lwz r4, 0x10(r1)
    mr r5, r17
    addi r3, r1, 0x28
    bl CDBRecordInitDescriptor
    lwz r3, 0x10(r1)
    mr r4, r19
    addi r5, r1, 0x28
    bl CDBDatabaseSearchCallCallback
    cmpwi r3, 0x0
    beq L_814883D8
    b L_81488410
    L_814883D8:
    mr r4, r17
    addi r3, r1, 0x68
    bl CDBRecordKeyCopy
    lwz r0, 0x20(r19)
    cmpwi r0, 0x0
    bne L_814883F8
    li r3, 0x0
    b L_81488410
    L_814883F8:
    subi r16, r16, 0x1
    L_814883FC:
    cmpwi r16, 0x0
    bge L_8148839C
    L_81488404:
    cmpwi r27, 0x0
    beq L_81487E54
    L_8148840C:
    li r3, 0x0
    L_81488410:
    addi r11, r1, 0x120
    bl _restgpr_14
    lwz r0, 0x124(r1)
    mtlr r0
    addi r1, r1, 0x120
    blr
#endif
}

asm CDBErr CDBDatabaseSearchMinuteLayer() {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x170(r1)
    mflr r0
    stw r0, 0x174(r1)
    addi r11, r1, 0x170
    bl _savegpr_17
    lwz r10, CDBDatabaseWorkBuf(r0)
    mr r21, r5
    mr r19, r3
    mr r20, r4
    mr r22, r6
    mr r23, r7
    mr r24, r8
    mr r25, r9
    mr r3, r21
    addi r28, r10, 0x1dbc
    addi r27, r10, 0x1cbc
    bl atoi
    mr r3, r22
    bl atoi
    li r0, -0x1
    addi r3, r1, 0x10
    stw r0, 0x8(r1)
    addi r4, r1, 0x40
    li r5, 0x3c
    bl CDBIntArrayInit
    lwz r0, 0x14(r20)
    cmpwi r0, 0x0
    bne L_814884A8
    addi r3, r1, 0x10
    bl CDBIntArraySetReverse
    li r0, 0x3c
    stw r0, 0x8(r1)
    L_814884A8:
    clrlwi r30, r25, 31
    rlwinm r29, r25, 0, 30, 30
    li r26, 0x0
    li r31, 0x0
    b L_814887A4
    L_814884BC:
    cmpwi r30, 0x0
    stw r31, 0x18(r1)
    li r26, 0x1
    beq L_8148858C
    mr r3, r27
    mr r4, r21
    mr r5, r22
    mr r6, r23
    mr r7, r24
    li r8, 0x1
    li r9, 0x0
    bl CDBConvHourStrToFullPath
    mr r3, r28
    mr r4, r27
    li r5, 0x1
    bl CDBFSFindFirst
    b L_81488574
    L_81488500:
    mr r3, r28
    bl CDBFindDataIsDirectory
    cmpwi r3, 0x0
    beq L_8148856C
    mr r3, r28
    bl CDBFindDataGetName
    bl CDBFSIsMinuteDirName
    cmpwi r3, 0x0
    beq L_8148856C
    mr r3, r28
    bl CDBFindDataGetName
    bl atoi
    stw r3, 0xc(r1)
    addi r3, r1, 0xc
    addi r4, r1, 0x8
    bl CDBIntCompare
    lwz r0, 0x1c(r1)
    mullw. r0, r0, r3
    ble L_8148856C
    addi r3, r1, 0x10
    bl CDBIntArrayFull
    cmpwi r3, 0x0
    beq L_81488560
    li r26, 0x0
    L_81488560:
    addi r3, r1, 0x10
    addi r4, r1, 0xc
    bl CDBIntArrayDicInsert
    L_8148856C:
    mr r3, r28
    bl CDBFSFindNext
    L_81488574:
    mr r3, r28
    bl CDBFindDataIsEnd
    cmpwi r3, 0x0
    beq L_81488500
    mr r3, r28
    bl CDBFSFindClose
    L_8148858C:
    cmpwi r29, 0x0
    beq L_81488674
    mr r3, r27
    mr r4, r21
    mr r5, r22
    mr r6, r23
    mr r7, r24
    addi r9, r20, 0x28
    li r8, 0x2
    bl CDBConvHourStrToFullPath
    mr r3, r28
    mr r4, r27
    li r5, 0x2
    bl CDBFSFindFirst
    b L_8148865C
    L_814885C8:
    mr r3, r28
    bl CDBFindDataIsDirectory
    cmpwi r3, 0x0
    beq L_81488654
    mr r3, r28
    bl CDBFindDataGetName
    bl CDBFSIsMinuteDirName
    cmpwi r3, 0x0
    beq L_81488654
    mr r3, r28
    bl CDBFindDataGetName
    bl atoi
    stw r3, 0xc(r1)
    addi r3, r1, 0xc
    addi r4, r1, 0x8
    bl CDBIntCompare
    lwz r0, 0x1c(r1)
    mullw. r0, r0, r3
    ble L_81488654
    addi r3, r1, 0x10
    addi r4, r1, 0xc
    bl CDBIntArrayDicFind
    mr r18, r3
    addi r3, r1, 0x10
    bl CDBIntArrayEnd
    cmplw r18, r3
    bne L_81488654
    addi r3, r1, 0x10
    bl CDBIntArrayFull
    cmpwi r3, 0x0
    beq L_81488648
    li r26, 0x0
    L_81488648:
    addi r3, r1, 0x10
    addi r4, r1, 0xc
    bl CDBIntArrayDicInsert
    L_81488654:
    mr r3, r28
    bl CDBFSFindNext
    L_8148865C:
    mr r3, r28
    bl CDBFindDataIsEnd
    cmpwi r3, 0x0
    beq L_814885C8
    mr r3, r28
    bl CDBFSFindClose
    L_81488674:
    addi r3, r1, 0x10
    bl CDBIntArrayEmpty
    cmpwi r3, 0x0
    bne L_814887AC
    lwz r0, 0x14(r20)
    cmpwi r0, 0x1
    bne L_8148871C
    li r17, 0x0
    b L_81488708
    L_81488698:
    mr r4, r17
    addi r3, r1, 0x10
    bl CDBIntArrayAt
    mr r18, r3
    addi r3, r1, 0x20
    lwz r4, 0x0(r18)
    bl CDBConvMinuteValueToMinuteStr
    mr r3, r19
    mr r4, r20
    mr r5, r21
    mr r6, r22
    mr r7, r23
    mr r8, r24
    mr r10, r25
    addi r9, r1, 0x20
    bl CDBDatabaseSearchRecordLayer
    cmpwi r3, 0x0
    beq L_814886E4
    b L_814887B0
    L_814886E4:
    lwz r0, 0x20(r20)
    cmpwi r0, 0x0
    bne L_814886F8
    li r3, 0x0
    b L_814887B0
    L_814886F8:
    mr r4, r18
    addi r3, r1, 0x8
    bl CDBIntCopy
    addi r17, r17, 0x1
    L_81488708:
    addi r3, r1, 0x10
    bl CDBIntArraySize
    cmpw r17, r3
    blt L_81488698
    b L_814887A4
    L_8148871C:
    addi r3, r1, 0x10
    bl CDBIntArraySize
    subi r18, r3, 0x1
    b L_8148879C
    L_8148872C:
    mr r4, r18
    addi r3, r1, 0x10
    bl CDBIntArrayAt
    mr r17, r3
    addi r3, r1, 0x20
    lwz r4, 0x0(r17)
    bl CDBConvMinuteValueToMinuteStr
    mr r3, r19
    mr r4, r20
    mr r5, r21
    mr r6, r22
    mr r7, r23
    mr r8, r24
    mr r10, r25
    addi r9, r1, 0x20
    bl CDBDatabaseSearchRecordLayer
    cmpwi r3, 0x0
    beq L_81488778
    b L_814887B0
    L_81488778:
    lwz r0, 0x20(r20)
    cmpwi r0, 0x0
    bne L_8148878C
    li r3, 0x0
    b L_814887B0
    L_8148878C:
    mr r4, r17
    addi r3, r1, 0x8
    bl CDBIntCopy
    subi r18, r18, 0x1
    L_8148879C:
    cmpwi r18, 0x0
    bge L_8148872C
    L_814887A4:
    cmpwi r26, 0x0
    beq L_814884BC
    L_814887AC:
    li r3, 0x0
    L_814887B0:
    addi r11, r1, 0x170
    bl _restgpr_17
    lwz r0, 0x174(r1)
    mtlr r0
    addi r1, r1, 0x170
    blr
#endif
}

asm CDBErr CDBDatabaseSearchHourLayer() {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0xb0(r1)
    mflr r0
    stw r0, 0xb4(r1)
    addi r11, r1, 0xb0
    bl _savegpr_18
    lwz r9, CDBDatabaseWorkBuf(r0)
    mr r22, r5
    mr r20, r3
    mr r21, r4
    mr r23, r6
    mr r24, r7
    mr r25, r8
    mr r3, r22
    addi r28, r9, 0x2750
    addi r27, r9, 0x2650
    bl atoi
    mr r3, r23
    bl atoi
    li r0, -0x1
    addi r3, r1, 0x10
    stw r0, 0x8(r1)
    addi r4, r1, 0x40
    li r5, 0xc
    bl CDBIntArrayInit
    lwz r0, 0x14(r21)
    cmpwi r0, 0x0
    bne L_81488844
    addi r3, r1, 0x10
    bl CDBIntArraySetReverse
    li r0, 0x18
    stw r0, 0x8(r1)
    L_81488844:
    clrlwi r30, r25, 31
    rlwinm r29, r25, 0, 30, 30
    li r26, 0x0
    li r31, 0x0
    b L_81488B30
    L_81488858:
    cmpwi r30, 0x0
    stw r31, 0x18(r1)
    li r26, 0x1
    beq L_81488924
    mr r3, r27
    mr r4, r22
    mr r5, r23
    mr r6, r24
    li r7, 0x1
    li r8, 0x0
    bl CDBConvDayStrToFullPath
    mr r3, r28
    mr r4, r27
    li r5, 0x1
    bl CDBFSFindFirst
    b L_8148890C
    L_81488898:
    mr r3, r28
    bl CDBFindDataIsDirectory
    cmpwi r3, 0x0
    beq L_81488904
    mr r3, r28
    bl CDBFindDataGetName
    bl CDBFSIsHourDirName
    cmpwi r3, 0x0
    beq L_81488904
    mr r3, r28
    bl CDBFindDataGetName
    bl atoi
    stw r3, 0xc(r1)
    addi r3, r1, 0xc
    addi r4, r1, 0x8
    bl CDBIntCompare
    lwz r0, 0x1c(r1)
    mullw. r0, r0, r3
    ble L_81488904
    addi r3, r1, 0x10
    bl CDBIntArrayFull
    cmpwi r3, 0x0
    beq L_814888F8
    li r26, 0x0
    L_814888F8:
    addi r3, r1, 0x10
    addi r4, r1, 0xc
    bl CDBIntArrayDicInsert
    L_81488904:
    mr r3, r28
    bl CDBFSFindNext
    L_8148890C:
    mr r3, r28
    bl CDBFindDataIsEnd
    cmpwi r3, 0x0
    beq L_81488898
    mr r3, r28
    bl CDBFSFindClose
    L_81488924:
    cmpwi r29, 0x0
    beq L_81488A08
    mr r3, r27
    mr r4, r22
    mr r5, r23
    mr r6, r24
    addi r8, r21, 0x28
    li r7, 0x2
    bl CDBConvDayStrToFullPath
    mr r3, r28
    mr r4, r27
    li r5, 0x2
    bl CDBFSFindFirst
    b L_814889F0
    L_8148895C:
    mr r3, r28
    bl CDBFindDataIsDirectory
    cmpwi r3, 0x0
    beq L_814889E8
    mr r3, r28
    bl CDBFindDataGetName
    bl CDBFSIsHourDirName
    cmpwi r3, 0x0
    beq L_814889E8
    mr r3, r28
    bl CDBFindDataGetName
    bl atoi
    stw r3, 0xc(r1)
    addi r3, r1, 0xc
    addi r4, r1, 0x8
    bl CDBIntCompare
    lwz r0, 0x1c(r1)
    mullw. r0, r0, r3
    ble L_814889E8
    addi r3, r1, 0x10
    addi r4, r1, 0xc
    bl CDBIntArrayDicFind
    mr r19, r3
    addi r3, r1, 0x10
    bl CDBIntArrayEnd
    cmplw r19, r3
    bne L_814889E8
    addi r3, r1, 0x10
    bl CDBIntArrayFull
    cmpwi r3, 0x0
    beq L_814889DC
    li r26, 0x0
    L_814889DC:
    addi r3, r1, 0x10
    addi r4, r1, 0xc
    bl CDBIntArrayDicInsert
    L_814889E8:
    mr r3, r28
    bl CDBFSFindNext
    L_814889F0:
    mr r3, r28
    bl CDBFindDataIsEnd
    cmpwi r3, 0x0
    beq L_8148895C
    mr r3, r28
    bl CDBFSFindClose
    L_81488A08:
    addi r3, r1, 0x10
    bl CDBIntArrayEmpty
    cmpwi r3, 0x0
    bne L_81488B38
    lwz r0, 0x14(r21)
    cmpwi r0, 0x1
    bne L_81488AAC
    li r18, 0x0
    b L_81488A98
    L_81488A2C:
    mr r4, r18
    addi r3, r1, 0x10
    bl CDBIntArrayAt
    mr r19, r3
    addi r3, r1, 0x20
    lwz r4, 0x0(r19)
    bl CDBConvHourValueToHourStr
    mr r3, r20
    mr r4, r21
    mr r5, r22
    mr r6, r23
    mr r7, r24
    mr r9, r25
    addi r8, r1, 0x20
    bl CDBDatabaseSearchMinuteLayer
    cmpwi r3, 0x0
    beq L_81488A74
    b L_81488B3C
    L_81488A74:
    lwz r0, 0x20(r21)
    cmpwi r0, 0x0
    bne L_81488A88
    li r3, 0x0
    b L_81488B3C
    L_81488A88:
    mr r4, r19
    addi r3, r1, 0x8
    bl CDBIntCopy
    addi r18, r18, 0x1
    L_81488A98:
    addi r3, r1, 0x10
    bl CDBIntArraySize
    cmpw r18, r3
    blt L_81488A2C
    b L_81488B30
    L_81488AAC:
    addi r3, r1, 0x10
    bl CDBIntArraySize
    subi r19, r3, 0x1
    b L_81488B28
    L_81488ABC:
    mr r4, r19
    addi r3, r1, 0x10
    bl CDBIntArrayAt
    mr r18, r3
    addi r3, r1, 0x20
    lwz r4, 0x0(r18)
    bl CDBConvHourValueToHourStr
    mr r3, r20
    mr r4, r21
    mr r5, r22
    mr r6, r23
    mr r7, r24
    mr r9, r25
    addi r8, r1, 0x20
    bl CDBDatabaseSearchMinuteLayer
    cmpwi r3, 0x0
    beq L_81488B04
    b L_81488B3C
    L_81488B04:
    lwz r0, 0x20(r21)
    cmpwi r0, 0x0
    bne L_81488B18
    li r3, 0x0
    b L_81488B3C
    L_81488B18:
    mr r4, r18
    addi r3, r1, 0x8
    bl CDBIntCopy
    subi r19, r19, 0x1
    L_81488B28:
    cmpwi r19, 0x0
    bge L_81488ABC
    L_81488B30:
    cmpwi r26, 0x0
    beq L_81488858
    L_81488B38:
    li r3, 0x0
    L_81488B3C:
    addi r11, r1, 0xb0
    bl _restgpr_18
    lwz r0, 0xb4(r1)
    mtlr r0
    addi r1, r1, 0xb0
    blr
#endif
}

asm CDBErr CDBDatabaseSearchDayLayer() {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x100(r1)
    mflr r0
    stw r0, 0x104(r1)
    addi r11, r1, 0x100
    bl _savegpr_17
    lwz r8, CDBDatabaseWorkBuf(r0)
    mr r19, r5
    mr r17, r3
    mr r18, r4
    mr r20, r6
    mr r21, r7
    mr r3, r19
    addi r26, r8, 0x30e4
    addi r25, r8, 0x2fe4
    bl atoi
    mr r23, r3
    mr r3, r20
    bl atoi
    li r0, 0x0
    mr r22, r3
    stw r0, 0x8(r1)
    addi r3, r1, 0x10
    addi r4, r1, 0x40
    li r5, 0x1f
    bl CDBIntArrayInit
    lwz r0, 0x14(r18)
    cmpwi r0, 0x0
    bne L_81488BD4
    addi r3, r1, 0x10
    bl CDBIntArraySetReverse
    li r0, 0x20
    stw r0, 0x8(r1)
    L_81488BD4:
    clrlwi r30, r21, 31
    rlwinm r29, r21, 0, 30, 30
    li r24, 0x0
    li r31, 0x0
    b L_81488F20
    L_81488BE8:
    cmpwi r30, 0x0
    stw r31, 0x18(r1)
    li r24, 0x1
    beq L_81488CB0
    mr r3, r25
    mr r4, r19
    mr r5, r20
    li r6, 0x1
    li r7, 0x0
    bl CDBConvMonthStrToFullPath
    mr r3, r26
    mr r4, r25
    li r5, 0x1
    bl CDBFSFindFirst
    b L_81488C98
    L_81488C24:
    mr r3, r26
    bl CDBFindDataIsDirectory
    cmpwi r3, 0x0
    beq L_81488C90
    mr r3, r26
    bl CDBFindDataGetName
    bl CDBFSIsDayDirName
    cmpwi r3, 0x0
    beq L_81488C90
    mr r3, r26
    bl CDBFindDataGetName
    bl atoi
    stw r3, 0xc(r1)
    addi r3, r1, 0xc
    addi r4, r1, 0x8
    bl CDBIntCompare
    lwz r0, 0x1c(r1)
    mullw. r0, r0, r3
    ble L_81488C90
    addi r3, r1, 0x10
    bl CDBIntArrayFull
    cmpwi r3, 0x0
    beq L_81488C84
    li r24, 0x0
    L_81488C84:
    addi r3, r1, 0x10
    addi r4, r1, 0xc
    bl CDBIntArrayDicInsert
    L_81488C90:
    mr r3, r26
    bl CDBFSFindNext
    L_81488C98:
    mr r3, r26
    bl CDBFindDataIsEnd
    cmpwi r3, 0x0
    beq L_81488C24
    mr r3, r26
    bl CDBFSFindClose
    L_81488CB0:
    cmpwi r29, 0x0
    beq L_81488D90
    mr r3, r25
    mr r4, r19
    mr r5, r20
    addi r7, r18, 0x28
    li r6, 0x2
    bl CDBConvMonthStrToFullPath
    mr r3, r26
    mr r4, r25
    li r5, 0x2
    bl CDBFSFindFirst
    b L_81488D78
    L_81488CE4:
    mr r3, r26
    bl CDBFindDataIsDirectory
    cmpwi r3, 0x0
    beq L_81488D70
    mr r3, r26
    bl CDBFindDataGetName
    bl CDBFSIsDayDirName
    cmpwi r3, 0x0
    beq L_81488D70
    mr r3, r26
    bl CDBFindDataGetName
    bl atoi
    stw r3, 0xc(r1)
    addi r3, r1, 0xc
    addi r4, r1, 0x8
    bl CDBIntCompare
    lwz r0, 0x1c(r1)
    mullw. r0, r0, r3
    ble L_81488D70
    addi r3, r1, 0x10
    addi r4, r1, 0xc
    bl CDBIntArrayDicFind
    mr r27, r3
    addi r3, r1, 0x10
    bl CDBIntArrayEnd
    cmplw r27, r3
    bne L_81488D70
    addi r3, r1, 0x10
    bl CDBIntArrayFull
    cmpwi r3, 0x0
    beq L_81488D64
    li r24, 0x0
    L_81488D64:
    addi r3, r1, 0x10
    addi r4, r1, 0xc
    bl CDBIntArrayDicInsert
    L_81488D70:
    mr r3, r26
    bl CDBFSFindNext
    L_81488D78:
    mr r3, r26
    bl CDBFindDataIsEnd
    cmpwi r3, 0x0
    beq L_81488CE4
    mr r3, r26
    bl CDBFSFindClose
    L_81488D90:
    addi r3, r1, 0x10
    bl CDBIntArrayEmpty
    cmpwi r3, 0x0
    bne L_81488F28
    lwz r0, 0x14(r18)
    cmpwi r0, 0x1
    bne L_81488E68
    li r27, 0x0
    b L_81488E54
    L_81488DB4:
    mr r4, r27
    addi r3, r1, 0x10
    bl CDBIntArrayAt
    mr r28, r3
    mr r3, r23
    lwz r5, 0x0(r28)
    mr r4, r22
    bl CDBMakeCDBDateDayEnd
    lwz r0, 0x0(r18)
    cmplw r3, r0
    blt L_81488E44
    lwz r5, 0x0(r28)
    mr r3, r23
    mr r4, r22
    bl CDBMakeCDBDateDayBegin
    lwz r0, 0x4(r18)
    cmplw r0, r3
    blt L_81488E44
    lwz r4, 0x0(r28)
    addi r3, r1, 0x20
    bl CDBConvDayValueToDayStr
    mr r3, r17
    mr r4, r18
    mr r5, r19
    mr r6, r20
    mr r8, r21
    addi r7, r1, 0x20
    bl CDBDatabaseSearchHourLayer
    cmpwi r3, 0x0
    beq L_81488E30
    b L_81488F2C
    L_81488E30:
    lwz r0, 0x20(r18)
    cmpwi r0, 0x0
    bne L_81488E44
    li r3, 0x0
    b L_81488F2C
    L_81488E44:
    mr r4, r28
    addi r3, r1, 0x8
    bl CDBIntCopy
    addi r27, r27, 0x1
    L_81488E54:
    addi r3, r1, 0x10
    bl CDBIntArraySize
    cmpw r27, r3
    blt L_81488DB4
    b L_81488F20
    L_81488E68:
    addi r3, r1, 0x10
    bl CDBIntArraySize
    subi r28, r3, 0x1
    b L_81488F18
    L_81488E78:
    mr r4, r28
    addi r3, r1, 0x10
    bl CDBIntArrayAt
    mr r27, r3
    mr r3, r23
    lwz r5, 0x0(r27)
    mr r4, r22
    bl CDBMakeCDBDateDayEnd
    lwz r0, 0x0(r18)
    cmplw r3, r0
    blt L_81488F08
    lwz r5, 0x0(r27)
    mr r3, r23
    mr r4, r22
    bl CDBMakeCDBDateDayBegin
    lwz r0, 0x4(r18)
    cmplw r0, r3
    blt L_81488F08
    lwz r4, 0x0(r27)
    addi r3, r1, 0x20
    bl CDBConvDayValueToDayStr
    mr r3, r17
    mr r4, r18
    mr r5, r19
    mr r6, r20
    mr r8, r21
    addi r7, r1, 0x20
    bl CDBDatabaseSearchHourLayer
    cmpwi r3, 0x0
    beq L_81488EF4
    b L_81488F2C
    L_81488EF4:
    lwz r0, 0x20(r18)
    cmpwi r0, 0x0
    bne L_81488F08
    li r3, 0x0
    b L_81488F2C
    L_81488F08:
    mr r4, r27
    addi r3, r1, 0x8
    bl CDBIntCopy
    subi r28, r28, 0x1
    L_81488F18:
    cmpwi r28, 0x0
    bge L_81488E78
    L_81488F20:
    cmpwi r24, 0x0
    beq L_81488BE8
    L_81488F28:
    li r3, 0x0
    L_81488F2C:
    addi r11, r1, 0x100
    bl _restgpr_17
    lwz r0, 0x104(r1)
    mtlr r0
    addi r1, r1, 0x100
    blr
#endif
}

asm CDBErr CDBDatabaseSearchMonthLayer() {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0xb0(r1)
    mflr r0
    stw r0, 0xb4(r1)
    addi r11, r1, 0xb0
    bl _savegpr_19
    lwz r7, CDBDatabaseWorkBuf(r0)
    mr r23, r5
    mr r21, r3
    mr r22, r4
    mr r24, r6
    mr r3, r23
    addi r28, r7, 0x3a78
    addi r27, r7, 0x3978
    bl atoi
    li r0, -0x1
    mr r25, r3
    stw r0, 0x8(r1)
    addi r3, r1, 0x10
    addi r4, r1, 0x40
    li r5, 0xc
    bl CDBIntArrayInit
    lwz r0, 0x14(r22)
    cmpwi r0, 0x0
    bne L_81488FB4
    addi r3, r1, 0x10
    bl CDBIntArraySetReverse
    li r0, 0xc
    stw r0, 0x8(r1)
    L_81488FB4:
    clrlwi r30, r24, 31
    rlwinm r29, r24, 0, 30, 30
    li r26, 0x0
    li r31, 0x0
    b L_814892E0
    L_81488FC8:
    cmpwi r30, 0x0
    stw r31, 0x18(r1)
    li r26, 0x1
    beq L_8148908C
    mr r3, r27
    mr r4, r23
    li r5, 0x1
    li r6, 0x0
    bl CDBConvYearStrToFullPath
    mr r3, r28
    mr r4, r27
    li r5, 0x1
    bl CDBFSFindFirst
    b L_81489074
    L_81489000:
    mr r3, r28
    bl CDBFindDataIsDirectory
    cmpwi r3, 0x0
    beq L_8148906C
    mr r3, r28
    bl CDBFindDataGetName
    bl CDBFSIsMonthDirName
    cmpwi r3, 0x0
    beq L_8148906C
    mr r3, r28
    bl CDBFindDataGetName
    bl atoi
    stw r3, 0xc(r1)
    addi r3, r1, 0xc
    addi r4, r1, 0x8
    bl CDBIntCompare
    lwz r0, 0x1c(r1)
    mullw. r0, r0, r3
    ble L_8148906C
    addi r3, r1, 0x10
    bl CDBIntArrayFull
    cmpwi r3, 0x0
    beq L_81489060
    li r26, 0x0
    L_81489060:
    addi r3, r1, 0x10
    addi r4, r1, 0xc
    bl CDBIntArrayDicInsert
    L_8148906C:
    mr r3, r28
    bl CDBFSFindNext
    L_81489074:
    mr r3, r28
    bl CDBFindDataIsEnd
    cmpwi r3, 0x0
    beq L_81489000
    mr r3, r28
    bl CDBFSFindClose
    L_8148908C:
    cmpwi r29, 0x0
    beq L_81489168
    mr r3, r27
    mr r4, r23
    addi r6, r22, 0x28
    li r5, 0x2
    bl CDBConvYearStrToFullPath
    mr r3, r28
    mr r4, r27
    li r5, 0x2
    bl CDBFSFindFirst
    b L_81489150
    L_814890BC:
    mr r3, r28
    bl CDBFindDataIsDirectory
    cmpwi r3, 0x0
    beq L_81489148
    mr r3, r28
    bl CDBFindDataGetName
    bl CDBFSIsMonthDirName
    cmpwi r3, 0x0
    beq L_81489148
    mr r3, r28
    bl CDBFindDataGetName
    bl atoi
    stw r3, 0xc(r1)
    addi r3, r1, 0xc
    addi r4, r1, 0x8
    bl CDBIntCompare
    lwz r0, 0x1c(r1)
    mullw. r0, r0, r3
    ble L_81489148
    addi r3, r1, 0x10
    addi r4, r1, 0xc
    bl CDBIntArrayDicFind
    mr r20, r3
    addi r3, r1, 0x10
    bl CDBIntArrayEnd
    cmplw r20, r3
    bne L_81489148
    addi r3, r1, 0x10
    bl CDBIntArrayFull
    cmpwi r3, 0x0
    beq L_8148913C
    li r26, 0x0
    L_8148913C:
    addi r3, r1, 0x10
    addi r4, r1, 0xc
    bl CDBIntArrayDicInsert
    L_81489148:
    mr r3, r28
    bl CDBFSFindNext
    L_81489150:
    mr r3, r28
    bl CDBFindDataIsEnd
    cmpwi r3, 0x0
    beq L_814890BC
    mr r3, r28
    bl CDBFSFindClose
    L_81489168:
    addi r3, r1, 0x10
    bl CDBIntArrayEmpty
    cmpwi r3, 0x0
    bne L_814892E8
    lwz r0, 0x14(r22)
    cmpwi r0, 0x1
    bne L_81489234
    li r19, 0x0
    b L_81489220
    L_8148918C:
    mr r4, r19
    addi r3, r1, 0x10
    bl CDBIntArrayAt
    mr r20, r3
    mr r3, r25
    lwz r4, 0x0(r20)
    bl CDBMakeCDBDateMonthEnd
    lwz r0, 0x0(r22)
    cmplw r3, r0
    blt L_81489210
    lwz r4, 0x0(r20)
    mr r3, r25
    bl CDBMakeCDBDateMonthBegin
    lwz r0, 0x4(r22)
    cmplw r0, r3
    blt L_81489210
    lwz r4, 0x0(r20)
    addi r3, r1, 0x20
    bl CDBConvMonthValueToMonthStr
    mr r3, r21
    mr r4, r22
    mr r5, r23
    mr r7, r24
    addi r6, r1, 0x20
    bl CDBDatabaseSearchDayLayer
    cmpwi r3, 0x0
    beq L_814891FC
    b L_814892EC
    L_814891FC:
    lwz r0, 0x20(r22)
    cmpwi r0, 0x0
    bne L_81489210
    li r3, 0x0
    b L_814892EC
    L_81489210:
    mr r4, r20
    addi r3, r1, 0x8
    bl CDBIntCopy
    addi r19, r19, 0x1
    L_81489220:
    addi r3, r1, 0x10
    bl CDBIntArraySize
    cmpw r19, r3
    blt L_8148918C
    b L_814892E0
    L_81489234:
    addi r3, r1, 0x10
    bl CDBIntArraySize
    subi r20, r3, 0x1
    b L_814892D8
    L_81489244:
    mr r4, r20
    addi r3, r1, 0x10
    bl CDBIntArrayAt
    mr r19, r3
    mr r3, r25
    lwz r4, 0x0(r19)
    bl CDBMakeCDBDateMonthEnd
    lwz r0, 0x0(r22)
    cmplw r3, r0
    blt L_814892C8
    lwz r4, 0x0(r19)
    mr r3, r25
    bl CDBMakeCDBDateMonthBegin
    lwz r0, 0x4(r22)
    cmplw r0, r3
    blt L_814892C8
    lwz r4, 0x0(r19)
    addi r3, r1, 0x20
    bl CDBConvMonthValueToMonthStr
    mr r3, r21
    mr r4, r22
    mr r5, r23
    mr r7, r24
    addi r6, r1, 0x20
    bl CDBDatabaseSearchDayLayer
    cmpwi r3, 0x0
    beq L_814892B4
    b L_814892EC
    L_814892B4:
    lwz r0, 0x20(r22)
    cmpwi r0, 0x0
    bne L_814892C8
    li r3, 0x0
    b L_814892EC
    L_814892C8:
    mr r4, r19
    addi r3, r1, 0x8
    bl CDBIntCopy
    subi r20, r20, 0x1
    L_814892D8:
    cmpwi r20, 0x0
    bge L_81489244
    L_814892E0:
    cmpwi r26, 0x0
    beq L_81488FC8
    L_814892E8:
    li r3, 0x0
    L_814892EC:
    addi r11, r1, 0xb0
    bl _restgpr_19
    lwz r0, 0xb4(r1)
    mtlr r0
    addi r1, r1, 0xb0
    blr
#endif
}

asm CDBErr CDBDatabaseSearchYearLayer() {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x90(r1)
    mflr r0
    stw r0, 0x94(r1)
    addi r11, r1, 0x90
    bl _savegpr_22
    lwz r6, CDBDatabaseWorkBuf(r0)
    and. r0, r3, r4
    mr r24, r3
    mr r25, r4
    mr r26, r5
    addi r28, r6, 0x430c
    bne L_8148933C
    li r3, 0x1
    b L_81489664
    L_8148933C:
    li r0, 0x0
    addi r3, r1, 0x10
    stw r0, 0x8(r1)
    addi r4, r1, 0x20
    li r5, 0x8
    bl CDBIntArrayInit
    lwz r0, 0x14(r25)
    cmpwi r0, 0x0
    bne L_81489370
    addi r3, r1, 0x10
    bl CDBIntArraySetReverse
    li r0, 0x270f
    stw r0, 0x8(r1)
    L_81489370:
    clrlwi r30, r26, 31
    rlwinm r29, r26, 0, 30, 30
    li r27, 0x0
    li r31, 0x0
    b L_81489658
    L_81489384:
    cmpwi r30, 0x0
    stw r31, 0x18(r1)
    li r27, 0x1
    beq L_81489430
    mr r3, r28
    li r4, 0x1
    bl CDBFSFindFirstRoot
    b L_81489418
    L_814893A4:
    mr r3, r28
    bl CDBFindDataIsDirectory
    cmpwi r3, 0x0
    beq L_81489410
    mr r3, r28
    bl CDBFindDataGetName
    bl CDBFSIsYearDirName
    cmpwi r3, 0x0
    beq L_81489410
    mr r3, r28
    bl CDBFindDataGetName
    bl atoi
    stw r3, 0xc(r1)
    addi r3, r1, 0xc
    addi r4, r1, 0x8
    bl CDBIntCompare
    lwz r0, 0x1c(r1)
    mullw. r0, r0, r3
    ble L_81489410
    addi r3, r1, 0x10
    bl CDBIntArrayFull
    cmpwi r3, 0x0
    beq L_81489404
    li r27, 0x0
    L_81489404:
    addi r3, r1, 0x10
    addi r4, r1, 0xc
    bl CDBIntArrayDicInsert
    L_81489410:
    mr r3, r28
    bl CDBFSFindNext
    L_81489418:
    mr r3, r28
    bl CDBFindDataIsEnd
    cmpwi r3, 0x0
    beq L_814893A4
    mr r3, r28
    bl CDBFSFindClose
    L_81489430:
    cmpwi r29, 0x0
    beq L_814894F8
    mr r3, r28
    addi r5, r25, 0x28
    li r4, 0x2
    bl CDBFSFindFirstRootEx
    b L_814894E0
    L_8148944C:
    mr r3, r28
    bl CDBFindDataIsDirectory
    cmpwi r3, 0x0
    beq L_814894D8
    mr r3, r28
    bl CDBFindDataGetName
    bl CDBFSIsYearDirName
    cmpwi r3, 0x0
    beq L_814894D8
    mr r3, r28
    bl CDBFindDataGetName
    bl atoi
    stw r3, 0xc(r1)
    addi r3, r1, 0xc
    addi r4, r1, 0x8
    bl CDBIntCompare
    lwz r0, 0x1c(r1)
    mullw. r0, r0, r3
    ble L_814894D8
    addi r3, r1, 0x10
    addi r4, r1, 0xc
    bl CDBIntArrayDicFind
    mr r23, r3
    addi r3, r1, 0x10
    bl CDBIntArrayEnd
    cmplw r23, r3
    bne L_814894D8
    addi r3, r1, 0x10
    bl CDBIntArrayFull
    cmpwi r3, 0x0
    beq L_814894CC
    li r27, 0x0
    L_814894CC:
    addi r3, r1, 0x10
    addi r4, r1, 0xc
    bl CDBIntArrayDicInsert
    L_814894D8:
    mr r3, r28
    bl CDBFSFindNext
    L_814894E0:
    mr r3, r28
    bl CDBFindDataIsEnd
    cmpwi r3, 0x0
    beq L_8148944C
    mr r3, r28
    bl CDBFSFindClose
    L_814894F8:
    addi r3, r1, 0x10
    bl CDBIntArrayEmpty
    cmpwi r3, 0x0
    bne L_81489660
    lwz r0, 0x14(r25)
    cmpwi r0, 0x1
    bne L_814895B8
    li r22, 0x0
    b L_814895A4
    L_8148951C:
    mr r4, r22
    addi r3, r1, 0x10
    bl CDBIntArrayAt
    mr r23, r3
    lwz r3, 0x0(r3)
    bl CDBMakeCDBDateYearEnd
    lwz r0, 0x0(r25)
    cmplw r3, r0
    blt L_81489594
    lwz r3, 0x0(r23)
    bl CDBMakeCDBDateYearBegin
    lwz r0, 0x4(r25)
    cmplw r0, r3
    blt L_81489594
    lwz r4, 0x0(r23)
    addi r3, r1, 0x40
    bl CDBConvYearValueToYearStr
    mr r3, r24
    mr r4, r25
    mr r6, r26
    addi r5, r1, 0x40
    bl CDBDatabaseSearchMonthLayer
    cmpwi r3, 0x0
    beq L_81489580
    b L_81489664
    L_81489580:
    lwz r0, 0x20(r25)
    cmpwi r0, 0x0
    bne L_81489594
    li r3, 0x0
    b L_81489664
    L_81489594:
    mr r4, r23
    addi r3, r1, 0x8
    bl CDBIntCopy
    addi r22, r22, 0x1
    L_814895A4:
    addi r3, r1, 0x10
    bl CDBIntArraySize
    cmpw r22, r3
    blt L_8148951C
    b L_81489658
    L_814895B8:
    addi r3, r1, 0x10
    bl CDBIntArraySize
    subi r23, r3, 0x1
    b L_81489650
    L_814895C8:
    mr r4, r23
    addi r3, r1, 0x10
    bl CDBIntArrayAt
    mr r22, r3
    lwz r3, 0x0(r3)
    bl CDBMakeCDBDateYearEnd
    lwz r0, 0x0(r25)
    cmplw r3, r0
    blt L_81489640
    lwz r3, 0x0(r22)
    bl CDBMakeCDBDateYearBegin
    lwz r0, 0x4(r25)
    cmplw r0, r3
    blt L_81489640
    lwz r4, 0x0(r22)
    addi r3, r1, 0x40
    bl CDBConvYearValueToYearStr
    mr r3, r24
    mr r4, r25
    mr r6, r26
    addi r5, r1, 0x40
    bl CDBDatabaseSearchMonthLayer
    cmpwi r3, 0x0
    beq L_8148962C
    b L_81489664
    L_8148962C:
    lwz r0, 0x20(r25)
    cmpwi r0, 0x0
    bne L_81489640
    li r3, 0x0
    b L_81489664
    L_81489640:
    mr r4, r22
    addi r3, r1, 0x8
    bl CDBIntCopy
    subi r23, r23, 0x1
    L_81489650:
    cmpwi r23, 0x0
    bge L_814895C8
    L_81489658:
    cmpwi r27, 0x0
    beq L_81489384
    L_81489660:
    li r3, 0x0
    L_81489664:
    addi r11, r1, 0x90
    bl _restgpr_22
    lwz r0, 0x94(r1)
    mtlr r0
    addi r1, r1, 0x90
    blr
#endif
}

CDBErr CDBDatabaseSearch(CDBDatabase* database, CDBDate beginDate, CDBDate endDate, CDBSearchDirection searchDirection, char* makerCode, char* gameCode, int unk7, CDBRecordLocation recordLocation, int unk9, CDBSearchRecordCB searchRecordCB, void* searchRecordArg) {
    CDBErr result;
    CDBLock();
    result = CDBDatabaseSearch_(database, beginDate, endDate, searchDirection, makerCode, gameCode, unk7, recordLocation, unk9, searchRecordCB, searchRecordArg, NULL);
    CDBUnlock();
    return result;
}

asm CDBErr CDBDatabaseSearch_() {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    addi r11, r1, 0x60
    bl _savegpr_24
    cmplw r4, r5
    lwz r28, 0x68(r1)
    lwz r29, 0x6c(r1)
    mr r24, r3
    lwz r30, 0x70(r1)
    mr r25, r8
    lwz r31, 0x74(r1)
    mr r26, r9
    mr r27, r10
    bge L_81489764
    stw r4, 0x8(r1)
    stw r5, 0xc(r1)
    b L_8148976C
    L_81489764:
    stw r5, 0x8(r1)
    stw r4, 0xc(r1)
    L_8148976C:
    stw r6, 0x1c(r1)
    mr r3, r7
    addi r4, r1, 0x10
    bl CDBConvMCStrToMCValue
    mr r3, r25
    addi r4, r1, 0x14
    bl CDBConvGCStrToGCValue
    li r0, 0x1
    cmpwi r31, 0x0
    stw r26, 0x18(r1)
    stw r29, 0x20(r1)
    stw r30, 0x24(r1)
    stw r0, 0x28(r1)
    stw r28, 0x2c(r1)
    bne L_814897B8
    li r0, 0x0
    stw r0, 0x34(r1)
    stw r0, 0x30(r1)
    b L_814897C8
    L_814897B8:
    lwz r0, 0x0(r31)
    lwz r3, 0x4(r31)
    stw r3, 0x34(r1)
    stw r0, 0x30(r1)
    L_814897C8:
    mr r3, r24
    mr r5, r27
    addi r4, r1, 0x8
    bl CDBDatabaseSearchYearLayer
    addi r11, r1, 0x60
    bl _restgpr_24
    lwz r0, 0x64(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
#endif
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
        CDBReportError(lbl_8166B5D0);
        return CDB_ERROR_27;
    }
    if (flags == 1) {
        CDBReportError(lbl_8166B618);
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
extern char lbl_8166B528[] = "CDBDatabaseClose database is closed\n";
#pragma align 8
extern char lbl_8166B550[] = "can't create record; database is closed\n";
#pragma align 8
extern char lbl_8166B57C[] = "can't create record; database is readonly\n";
#pragma align 8
extern char lbl_8166B5A8[] = "invalid key\n";
#pragma align 8
extern char lbl_8166B5B8[] = "file not found : %s\n";
#pragma align 8
extern char lbl_8166B5D0[] = "can't execute CDBDatabaseCleanUpEmptyDirectories; database is closed\n";
#pragma align 8
extern char lbl_8166B618[] = "can't execute CDBDatabaseCleanUpEmptyDirectories; database is readonly\n";
