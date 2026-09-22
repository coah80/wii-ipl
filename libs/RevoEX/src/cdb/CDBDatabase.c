#include <private/cdb.h>
#include <revolution/cdb.h>
#include <stdlib.h>

extern void CDBGetMakerCode();
extern void CDBGetInitialCode();
extern void CDBLock();
extern void CDBDatabaseAllocate();
extern void CDBUnlock();
extern void CDBDatabaseFree();
extern void CDBRecordCreateAtOnce();
extern void CDBRecordInitDescriptor();
extern void CDBRecordIsExistFile();
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
extern void CDBFSDeleteDir();
extern void CDBFSFindNext();
extern void CDBFSFindClose();
extern void CDBFindDataIsDirectory();
extern void CDBFindDataGetName();
extern void CDBFindDataIsEnd();
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
extern u32 lbl_81698D8C;
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
extern CDBErr CDBDatabaseInstanceInit();
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

asm CDBErr CDBDatabaseInit(CDBDatabase* database) {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    bl CDBGetMakerCode
    sth r3, 0x0(r31)
    bl CDBGetInitialCode
    li r0, 0x0
    stw r3, 0x4(r31)
    li r3, 0x0
    stw r0, 0x8(r31)
    lwz r31, 0xc(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
#endif
}

asm CDBErr CDBDatabaseOpen(CDBDatabase* database) {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    bl CDBLock
    mr r3, r31
    li r4, 0x3
    bl CDBDatabaseAllocate
    cmpwi r3, 0x0
    li r31, 0x0
    beq L_81487418
    mr r31, r3
    L_81487418:
    bl CDBUnlock
    mr r3, r31
    lwz r31, 0xc(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
#endif
}

asm CDBErr CDBDatabaseClose(CDBDatabase* database) {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    stw r30, 0x8(r1)
    mr r30, r3
    bl CDBLock
    lwz r31, 0x8(r30)
    cmpwi r31, 0x0
    beq L_8148746C
    addis r3, r31, 0x1
    lwz r0, -0x3ff0(r3)
    cmpwi r0, 0x0
    bne L_8148749C
    L_8148746C:
    li r3, 0x2
    bl CDBIsPrintDebugMessage
    cmpwi r3, 0x0
    beq L_81487494
    li r3, 0x2
    bl CDBReport_
    lis r3, lbl_8166B528@ha
    addi r3, r3, lbl_8166B528@l
    crclr 4*cr1+eq
    bl OSReport
    L_81487494:
    li r31, 0x1b
    b L_814874C4
    L_8148749C:
    mr r3, r30
    bl CDBDatabaseFree
    cmpwi r3, 0x0
    beq L_814874B4
    mr r31, r3
    b L_814874C4
    L_814874B4:
    addis r3, r31, 0x1
    li r0, 0x0
    stw r0, -0x3ff0(r3)
    li r31, 0x0
    L_814874C4:
    bl CDBUnlock
    mr r3, r31
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
#endif
}

asm CDBErr CDBDatabasePrivateCreateRecordAtOnce(CDBDatabase* database, CDBRecord* record, const char* typeStr, const char* fileTypeStr, u8* recordData, u32 recordDataSize, char* makerCodeStr, char* gameCodeStr) {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    addi r11, r1, 0x40
    bl _savegpr_22
    mr r22, r3
    mr r23, r4
    mr r24, r5
    mr r25, r6
    mr r26, r7
    mr r27, r8
    mr r29, r9
    mr r28, r10
    bl CDBLock
    mr r3, r28
    bl CDBIsGameCodeStr
    cmpwi r3, 0x0
    bne L_81487534
    li r31, 0x4
    b L_814875B0
    L_81487534:
    mr r3, r29
    bl CDBIsMakerCodeStr
    cmpwi r3, 0x0
    bne L_8148754C
    li r31, 0x3
    b L_814875B0
    L_8148754C:
    mr r3, r29
    addi r4, r1, 0x10
    bl CDBConvMCStrToMCValue
    mr r3, r28
    addi r4, r1, 0x14
    bl CDBConvGCStrToGCValue
    lhz r31, 0x10(r1)
    lwz r30, 0x14(r1)
    bl OSGetTime
    mr r28, r4
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
    mr r9, r30
    mr r10, r31
    bl CDBDatabaseCreateRecordImAtOnce_
    mr r31, r3
    bl CDBUnlock
    L_814875B0:
    bl CDBUnlock
    addi r11, r1, 0x40
    mr r3, r31
    bl _restgpr_22
    lwz r0, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
#endif
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

asm CDBErr CDBDatabasePrivateCreateRecordAtOnceEx(CDBDatabase* database, CDBRecord* record, const char* typeStr, const char* fileTypeStr, int year, int month, int day, int hour, int min, int sec, u8* recordData, u32 recordDataSize, char* makerCode, char* gameCode) {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    addi r11, r1, 0x60
    bl _savegpr_18
    lwz r26, 0x68(r1)
    mr r18, r3
    lwz r27, 0x6c(r1)
    mr r19, r4
    lwz r28, 0x70(r1)
    mr r20, r5
    lwz r29, 0x74(r1)
    mr r21, r6
    lwz r30, 0x78(r1)
    mr r22, r7
    lwz r31, 0x7c(r1)
    mr r23, r8
    mr r24, r9
    mr r25, r10
    bl CDBLock
    stw r26, 0x8(r1)
    mr r3, r18
    mr r4, r19
    mr r5, r20
    stw r27, 0xc(r1)
    mr r6, r21
    mr r7, r22
    mr r8, r23
    stw r28, 0x10(r1)
    mr r9, r24
    mr r10, r25
    stw r29, 0x14(r1)
    stw r30, 0x18(r1)
    stw r31, 0x1c(r1)
    bl CDBDatabasePrivateCreateRecordAtOnceEx_
    mr r31, r3
    bl CDBUnlock
    addi r11, r1, 0x60
    mr r3, r31
    bl _restgpr_18
    lwz r0, 0x64(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
#endif
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

asm CDBErr CDBDatabaseFindByKey() {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r5
    stw r30, 0x18(r1)
    mr r30, r4
    stw r29, 0x14(r1)
    mr r29, r3
    bl CDBLock
    mr r3, r31
    bl CDBRecordKeyIsValid
    cmpwi r3, 0x0
    bne L_81487ABC
    li r3, 0x2
    bl CDBIsPrintDebugMessage
    cmpwi r3, 0x0
    beq L_81487AB4
    li r3, 0x2
    bl CDBReport_
    lis r3, lbl_8166B5A8@ha
    addi r3, r3, lbl_8166B5A8@l
    crclr 4*cr1+eq
    bl OSReport
    L_81487AB4:
    li r31, 0x5
    b L_81487B14
    L_81487ABC:
    mr r3, r30
    mr r4, r29
    mr r5, r31
    bl CDBRecordInitDescriptor
    mr r3, r30
    bl CDBRecordIsExistFile
    cmpwi r3, 0x0
    bne L_81487B10
    li r3, 0x2
    bl CDBIsPrintDebugMessage
    cmpwi r3, 0x0
    beq L_81487B08
    li r3, 0x2
    bl CDBReport_
    lis r3, lbl_8166B5B8@ha
    mr r4, r31
    addi r3, r3, lbl_8166B5B8@l
    crclr 4*cr1+eq
    bl OSReport
    L_81487B08:
    li r31, 0x23
    b L_81487B14
    L_81487B10:
    li r31, 0x0
    L_81487B14:
    bl CDBUnlock
    mr r3, r31
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
#endif
}

asm CDBErr CDBDatabaseSearchConditionsIsMatch() {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    mr r31, r4
    addi r4, r1, 0x10
    stw r30, 0x28(r1)
    mr r30, r3
    mr r3, r31
    bl CDBConvKeyStrToEpochValue
    lwz r3, 0x10(r1)
    lwz r0, 0x0(r30)
    cmplw r0, r3
    bgt L_81487B7C
    lwz r0, 0x4(r30)
    cmplw r3, r0
    ble L_81487B84
    L_81487B7C:
    li r3, 0x0
    b L_81487C20
    L_81487B84:
    lhz r0, 0x8(r30)
    cmplwi r0, 0xffff
    beq L_81487BB4
    mr r3, r31
    addi r4, r1, 0x8
    bl CDBConvKeyStrToMakerCode
    lhz r3, 0x8(r30)
    lhz r0, 0x8(r1)
    cmplw r3, r0
    beq L_81487BB4
    li r3, 0x0
    b L_81487C20
    L_81487BB4:
    lwz r3, 0xc(r30)
    addis r0, r3, 0x1
    cmplwi r0, 0xffff
    beq L_81487BE8
    mr r3, r31
    addi r4, r1, 0xc
    bl CDBConvKeyStrToGameCode
    lwz r3, 0xc(r30)
    lwz r0, 0xc(r1)
    cmplw r3, r0
    beq L_81487BE8
    li r3, 0x0
    b L_81487C20
    L_81487BE8:
    lwz r0, 0x10(r30)
    cmpwi r0, 0x0
    beq L_81487C1C
    mr r3, r31
    addi r4, r1, 0x14
    bl CDBConvKeyStrToType
    lwz r3, 0x10(r30)
    addi r4, r1, 0x14
    bl CDBCompareTypeStr
    cmpwi r3, 0x0
    beq L_81487C1C
    li r3, 0x0
    b L_81487C20
    L_81487C1C:
    li r3, 0x1
    L_81487C20:
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
#endif
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
    lwz r11, lbl_81698D8C(r0)
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
    lwz r25, lbl_81698D8C(r0)
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
    lwz r10, lbl_81698D8C(r0)
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
    lwz r9, lbl_81698D8C(r0)
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
    lwz r8, lbl_81698D8C(r0)
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
    lwz r7, lbl_81698D8C(r0)
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
    lwz r6, lbl_81698D8C(r0)
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

asm CDBErr CDBDatabaseSearch(CDBDatabase* database, CDBDate beginDate, CDBDate endDate, CDBSearchDirection searchDirection, char* makerCode, char* gameCode, int unk7, CDBRecordLocation recordLocation, int unk9, CDBSearchRecordCB searchRecordCB, void* searchRecordArg) {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    addi r11, r1, 0x50
    bl _savegpr_21
    lwz r29, 0x58(r1)
    mr r21, r3
    lwz r30, 0x5c(r1)
    mr r22, r4
    lwz r31, 0x60(r1)
    mr r23, r5
    mr r24, r6
    mr r25, r7
    mr r26, r8
    mr r27, r9
    mr r28, r10
    bl CDBLock
    stw r29, 0x8(r1)
    li r0, 0x0
    mr r3, r21
    mr r4, r22
    stw r30, 0xc(r1)
    mr r5, r23
    mr r6, r24
    mr r7, r25
    stw r31, 0x10(r1)
    mr r8, r26
    mr r9, r27
    mr r10, r28
    stw r0, 0x14(r1)
    bl CDBDatabaseSearch_
    mr r31, r3
    bl CDBUnlock
    addi r11, r1, 0x50
    mr r3, r31
    bl _restgpr_21
    lwz r0, 0x54(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
#endif
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

asm CDBErr CDBDatabaseInstanceInit() {
#ifdef __MWERKS__
    nofralloc
    addis r6, r3, 0x1
    li r0, 0x1
    stw r0, 0x0(r3)
    stw r4, -0x3ff0(r6)
    stw r5, -0x3fec(r6)
    blr
#endif
}

asm BOOL CDBDatabaseInstanceIsUsed() {
#ifdef __MWERKS__
    nofralloc
    lwz r3, 0x0(r3)
    blr
#endif
}

asm BOOL CDBIsSDAvailable() {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    li r31, 0x0
    bl CDBFSSDIsMounted
    cmpwi r3, 0x0
    beq L_81489840
    bl CDBFSSDIsEjected
    cmpwi r3, 0x0
    bne L_81489840
    li r31, 0x1
    L_81489840:
    mr r3, r31
    lwz r31, 0xc(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
#endif
}

asm CDBErr CDBMountSD() {
#ifdef __MWERKS__
    nofralloc
    b CDBFSSDMount
#endif
}

asm CDBErr CDBUnmountSDForce() {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    bl CDBFSSDUnmount
    cmpwi r3, 0x0
    li r0, 0x0
    beq L_8148987C
    mr r0, r3
    L_8148987C:
    mr r3, r0
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
#endif
}

asm CDBErr CDBDatabaseCleanUpEmptyDirectoriesRecord() {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x130(r1)
    mflr r0
    stw r0, 0x134(r1)
    addi r11, r1, 0x130
    bl _savegpr_25
    lwz r11, lbl_81698D8C(r0)
    mr r25, r4
    lwz r29, 0x138(r1)
    mr r26, r5
    lwz r0, 0x13c(r1)
    mr r27, r6
    stw r29, 0x8(r1)
    mr r31, r7
    mr r30, r8
    mr r12, r9
    mr r28, r10
    mr r4, r3
    mr r8, r31
    mr r9, r30
    stw r0, 0xc(r1)
    mr r5, r25
    mr r6, r26
    mr r7, r27
    mr r10, r12
    addi r30, r11, 0x100
    addi r3, r1, 0x10
    li r31, 0x0
    bl CDBConvTypeStrToFullPath
    mr r3, r30
    mr r5, r29
    addi r4, r1, 0x10
    bl CDBFSFindFirst
    b L_8148993C
    L_81489914:
    mr r3, r30
    addi r31, r31, 0x1
    bl CDBFindDataIsDirectory
    cmpwi r3, 0x0
    beq L_81489934
    mr r3, r30
    bl CDBFindDataGetName
    bl CDBFSIsMinuteDirName
    L_81489934:
    mr r3, r30
    bl CDBFSFindNext
    L_8148993C:
    mr r3, r30
    bl CDBFindDataIsEnd
    cmpwi r3, 0x0
    beq L_81489914
    mr r3, r30
    bl CDBFSFindClose
    cmpwi r31, 0x2
    bne L_81489980
    mr r4, r29
    addi r3, r1, 0x10
    bl CDBFSDeleteDir
    cmpwi r3, 0x0
    beq L_81489974
    b L_81489984
    L_81489974:
    lwz r3, 0x0(r28)
    subi r0, r3, 0x1
    stw r0, 0x0(r28)
    L_81489980:
    li r3, 0x0
    L_81489984:
    addi r11, r1, 0x130
    bl _restgpr_25
    lwz r0, 0x134(r1)
    mtlr r0
    addi r1, r1, 0x130
    blr
#endif
}

asm CDBErr CDBDatabaseCleanUpEmptyDirectoriesType() {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x140(r1)
    mflr r0
    stw r0, 0x144(r1)
    addi r11, r1, 0x140
    bl _savegpr_22
    li r0, 0x0
    lwz r11, lbl_81698D8C(r0)
    stw r0, 0x10(r1)
    mr r22, r3
    lwz r30, 0x148(r1)
    mr r23, r4
    mr r24, r5
    mr r25, r6
    mr r26, r7
    mr r27, r8
    mr r28, r9
    stw r30, 0x8(r1)
    mr r29, r10
    mr r4, r22
    mr r5, r23
    mr r6, r24
    mr r7, r25
    mr r8, r26
    mr r9, r27
    addi r31, r11, 0x1428
    addi r3, r1, 0x18
    bl CDBConvCodeStrToFullPath
    mr r3, r31
    mr r5, r29
    addi r4, r1, 0x18
    bl CDBFSFindFirst
    b L_81489A94
    L_81489A1C:
    lwz r4, 0x10(r1)
    mr r3, r31
    addi r0, r4, 0x1
    stw r0, 0x10(r1)
    bl CDBFindDataIsDirectory
    cmpwi r3, 0x0
    beq L_81489A8C
    mr r3, r31
    bl CDBFindDataGetName
    bl CDBFSIsTypeDirName
    cmpwi r3, 0x0
    beq L_81489A8C
    mr r3, r31
    bl CDBFindDataGetName
    stw r29, 0x8(r1)
    mr r9, r3
    mr r3, r22
    mr r4, r23
    stw r30, 0xc(r1)
    mr r5, r24
    mr r6, r25
    mr r7, r26
    mr r8, r27
    addi r10, r1, 0x10
    bl CDBDatabaseCleanUpEmptyDirectoriesRecord
    cmpwi r3, 0x0
    beq L_81489A8C
    b L_81489AE0
    L_81489A8C:
    mr r3, r31
    bl CDBFSFindNext
    L_81489A94:
    mr r3, r31
    bl CDBFindDataIsEnd
    cmpwi r3, 0x0
    beq L_81489A1C
    mr r3, r31
    bl CDBFSFindClose
    lwz r0, 0x10(r1)
    cmpwi r0, 0x2
    bne L_81489ADC
    mr r4, r29
    addi r3, r1, 0x18
    bl CDBFSDeleteDir
    cmpwi r3, 0x0
    beq L_81489AD0
    b L_81489AE0
    L_81489AD0:
    lwz r3, 0x0(r28)
    subi r0, r3, 0x1
    stw r0, 0x0(r28)
    L_81489ADC:
    li r3, 0x0
    L_81489AE0:
    addi r11, r1, 0x140
    bl _restgpr_22
    lwz r0, 0x144(r1)
    mtlr r0
    addi r1, r1, 0x140
    blr
#endif
}

asm CDBErr CDBDatabaseCleanUpEmptyDirectoriesCode() {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x140(r1)
    mflr r0
    stw r0, 0x144(r1)
    addi r11, r1, 0x140
    bl _savegpr_23
    lwz r11, lbl_81698D8C(r0)
    li r0, 0x0
    mr r23, r3
    mr r24, r4
    mr r25, r5
    mr r26, r6
    mr r27, r7
    mr r28, r8
    stw r0, 0x10(r1)
    mr r29, r9
    mr r30, r10
    mr r4, r23
    mr r5, r24
    mr r6, r25
    mr r7, r26
    mr r8, r27
    addi r31, r11, 0xa94
    addi r3, r1, 0x18
    bl CDBConvMinuteStrToFullPath
    mr r3, r31
    mr r5, r29
    addi r4, r1, 0x18
    bl CDBFSFindFirst
    b L_81489BE0
    L_81489B6C:
    lwz r4, 0x10(r1)
    mr r3, r31
    addi r0, r4, 0x1
    stw r0, 0x10(r1)
    bl CDBFindDataIsDirectory
    cmpwi r3, 0x0
    beq L_81489BD8
    mr r3, r31
    bl CDBFindDataGetName
    bl CDBFSIsCodeDirName
    cmpwi r3, 0x0
    beq L_81489BD8
    mr r3, r31
    bl CDBFindDataGetName
    stw r30, 0x8(r1)
    mr r8, r3
    mr r3, r23
    mr r4, r24
    mr r5, r25
    mr r6, r26
    mr r7, r27
    mr r10, r29
    addi r9, r1, 0x10
    bl CDBDatabaseCleanUpEmptyDirectoriesType
    cmpwi r3, 0x0
    beq L_81489BD8
    b L_81489C2C
    L_81489BD8:
    mr r3, r31
    bl CDBFSFindNext
    L_81489BE0:
    mr r3, r31
    bl CDBFindDataIsEnd
    cmpwi r3, 0x0
    beq L_81489B6C
    mr r3, r31
    bl CDBFSFindClose
    lwz r0, 0x10(r1)
    cmpwi r0, 0x2
    bne L_81489C28
    mr r4, r29
    addi r3, r1, 0x18
    bl CDBFSDeleteDir
    cmpwi r3, 0x0
    beq L_81489C1C
    b L_81489C2C
    L_81489C1C:
    lwz r3, 0x0(r28)
    subi r0, r3, 0x1
    stw r0, 0x0(r28)
    L_81489C28:
    li r3, 0x0
    L_81489C2C:
    addi r11, r1, 0x140
    bl _restgpr_23
    lwz r0, 0x144(r1)
    mtlr r0
    addi r1, r1, 0x140
    blr
#endif
}

asm CDBErr CDBDatabaseCleanUpEmptyDirectoriesMinute() {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x130(r1)
    mflr r0
    stw r0, 0x134(r1)
    addi r11, r1, 0x130
    bl _savegpr_24
    lwz r10, lbl_81698D8C(r0)
    li r0, 0x0
    mr r24, r3
    mr r25, r4
    mr r26, r5
    mr r27, r6
    mr r28, r7
    stw r0, 0x8(r1)
    mr r29, r8
    mr r30, r9
    mr r4, r24
    mr r5, r25
    mr r6, r26
    mr r7, r27
    addi r31, r10, 0x1dbc
    addi r3, r1, 0x10
    bl CDBConvHourStrToFullPath
    mr r3, r31
    mr r5, r29
    addi r4, r1, 0x10
    bl CDBFSFindFirst
    b L_81489D20
    L_81489CB0:
    lwz r4, 0x8(r1)
    mr r3, r31
    addi r0, r4, 0x1
    stw r0, 0x8(r1)
    bl CDBFindDataIsDirectory
    cmpwi r3, 0x0
    beq L_81489D18
    mr r3, r31
    bl CDBFindDataGetName
    bl CDBFSIsMinuteDirName
    cmpwi r3, 0x0
    beq L_81489D18
    mr r3, r31
    bl CDBFindDataGetName
    mr r7, r3
    mr r3, r24
    mr r4, r25
    mr r5, r26
    mr r6, r27
    mr r9, r29
    mr r10, r30
    addi r8, r1, 0x8
    bl CDBDatabaseCleanUpEmptyDirectoriesCode
    cmpwi r3, 0x0
    beq L_81489D18
    b L_81489D6C
    L_81489D18:
    mr r3, r31
    bl CDBFSFindNext
    L_81489D20:
    mr r3, r31
    bl CDBFindDataIsEnd
    cmpwi r3, 0x0
    beq L_81489CB0
    mr r3, r31
    bl CDBFSFindClose
    lwz r0, 0x8(r1)
    cmpwi r0, 0x2
    bne L_81489D68
    mr r4, r29
    addi r3, r1, 0x10
    bl CDBFSDeleteDir
    cmpwi r3, 0x0
    beq L_81489D5C
    b L_81489D6C
    L_81489D5C:
    lwz r3, 0x0(r28)
    subi r0, r3, 0x1
    stw r0, 0x0(r28)
    L_81489D68:
    li r3, 0x0
    L_81489D6C:
    addi r11, r1, 0x130
    bl _restgpr_24
    lwz r0, 0x134(r1)
    mtlr r0
    addi r1, r1, 0x130
    blr
#endif
}

asm CDBErr CDBDatabaseCleanUpEmptyDirectoriesHour() {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x130(r1)
    mflr r0
    stw r0, 0x134(r1)
    addi r11, r1, 0x130
    bl _savegpr_25
    lwz r9, lbl_81698D8C(r0)
    li r0, 0x0
    mr r25, r3
    mr r26, r4
    mr r27, r5
    mr r28, r6
    stw r0, 0x8(r1)
    mr r29, r7
    mr r30, r8
    mr r4, r25
    mr r5, r26
    mr r6, r27
    addi r31, r9, 0x2750
    addi r3, r1, 0x10
    bl CDBConvDayStrToFullPath
    mr r3, r31
    mr r5, r29
    addi r4, r1, 0x10
    bl CDBFSFindFirst
    b L_81489E54
    L_81489DE8:
    lwz r4, 0x8(r1)
    mr r3, r31
    addi r0, r4, 0x1
    stw r0, 0x8(r1)
    bl CDBFindDataIsDirectory
    cmpwi r3, 0x0
    beq L_81489E4C
    mr r3, r31
    bl CDBFindDataGetName
    bl CDBFSIsHourDirName
    cmpwi r3, 0x0
    beq L_81489E4C
    mr r3, r31
    bl CDBFindDataGetName
    mr r6, r3
    mr r3, r25
    mr r4, r26
    mr r5, r27
    mr r8, r29
    mr r9, r30
    addi r7, r1, 0x8
    bl CDBDatabaseCleanUpEmptyDirectoriesMinute
    cmpwi r3, 0x0
    beq L_81489E4C
    b L_81489EA0
    L_81489E4C:
    mr r3, r31
    bl CDBFSFindNext
    L_81489E54:
    mr r3, r31
    bl CDBFindDataIsEnd
    cmpwi r3, 0x0
    beq L_81489DE8
    mr r3, r31
    bl CDBFSFindClose
    lwz r0, 0x8(r1)
    cmpwi r0, 0x2
    bne L_81489E9C
    mr r4, r29
    addi r3, r1, 0x10
    bl CDBFSDeleteDir
    cmpwi r3, 0x0
    beq L_81489E90
    b L_81489EA0
    L_81489E90:
    lwz r3, 0x0(r28)
    subi r0, r3, 0x1
    stw r0, 0x0(r28)
    L_81489E9C:
    li r3, 0x0
    L_81489EA0:
    addi r11, r1, 0x130
    bl _restgpr_25
    lwz r0, 0x134(r1)
    mtlr r0
    addi r1, r1, 0x130
    blr
#endif
}

asm CDBErr CDBDatabaseCleanUpEmptyDirectoriesDay() {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x130(r1)
    mflr r0
    stw r0, 0x134(r1)
    addi r11, r1, 0x130
    bl _savegpr_26
    lwz r8, lbl_81698D8C(r0)
    li r0, 0x0
    mr r26, r3
    mr r27, r4
    mr r28, r5
    stw r0, 0x8(r1)
    mr r29, r6
    mr r30, r7
    mr r4, r26
    mr r5, r27
    addi r31, r8, 0x30e4
    addi r3, r1, 0x10
    bl CDBConvMonthStrToFullPath
    mr r3, r31
    mr r5, r29
    addi r4, r1, 0x10
    bl CDBFSFindFirst
    b L_81489F7C
    L_81489F14:
    lwz r4, 0x8(r1)
    mr r3, r31
    addi r0, r4, 0x1
    stw r0, 0x8(r1)
    bl CDBFindDataIsDirectory
    cmpwi r3, 0x0
    beq L_81489F74
    mr r3, r31
    bl CDBFindDataGetName
    bl CDBFSIsDayDirName
    cmpwi r3, 0x0
    beq L_81489F74
    mr r3, r31
    bl CDBFindDataGetName
    mr r5, r3
    mr r3, r26
    mr r4, r27
    mr r7, r29
    mr r8, r30
    addi r6, r1, 0x8
    bl CDBDatabaseCleanUpEmptyDirectoriesHour
    cmpwi r3, 0x0
    beq L_81489F74
    b L_81489FC8
    L_81489F74:
    mr r3, r31
    bl CDBFSFindNext
    L_81489F7C:
    mr r3, r31
    bl CDBFindDataIsEnd
    cmpwi r3, 0x0
    beq L_81489F14
    mr r3, r31
    bl CDBFSFindClose
    lwz r0, 0x8(r1)
    cmpwi r0, 0x2
    bne L_81489FC4
    mr r4, r29
    addi r3, r1, 0x10
    bl CDBFSDeleteDir
    cmpwi r3, 0x0
    beq L_81489FB8
    b L_81489FC8
    L_81489FB8:
    lwz r3, 0x0(r28)
    subi r0, r3, 0x1
    stw r0, 0x0(r28)
    L_81489FC4:
    li r3, 0x0
    L_81489FC8:
    addi r11, r1, 0x130
    bl _restgpr_26
    lwz r0, 0x134(r1)
    mtlr r0
    addi r1, r1, 0x130
    blr
#endif
}

asm CDBErr CDBDatabaseCleanUpEmptyDirectoriesMonth() {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x120(r1)
    mflr r0
    stw r0, 0x124(r1)
    li r0, 0x0
    stw r31, 0x11c(r1)
    stw r30, 0x118(r1)
    mr r30, r5
    mr r6, r30
    stw r29, 0x114(r1)
    mr r29, r4
    mr r5, r29
    stw r28, 0x110(r1)
    mr r28, r3
    mr r4, r28
    addi r3, r1, 0x10
    lwz r7, lbl_81698D8C(r0)
    stw r0, 0x8(r1)
    addi r31, r7, 0x3a78
    bl CDBConvYearStrToFullPath
    mr r3, r31
    mr r5, r29
    addi r4, r1, 0x10
    bl CDBFSFindFirst
    b L_8148A0A4
    L_8148A040:
    lwz r4, 0x8(r1)
    mr r3, r31
    addi r0, r4, 0x1
    stw r0, 0x8(r1)
    bl CDBFindDataIsDirectory
    cmpwi r3, 0x0
    beq L_8148A09C
    mr r3, r31
    bl CDBFindDataGetName
    bl CDBFSIsMonthDirName
    cmpwi r3, 0x0
    beq L_8148A09C
    mr r3, r31
    bl CDBFindDataGetName
    mr r4, r3
    mr r3, r28
    mr r6, r29
    mr r7, r30
    addi r5, r1, 0x8
    bl CDBDatabaseCleanUpEmptyDirectoriesDay
    cmpwi r3, 0x0
    beq L_8148A09C
    b L_8148A0E4
    L_8148A09C:
    mr r3, r31
    bl CDBFSFindNext
    L_8148A0A4:
    mr r3, r31
    bl CDBFindDataIsEnd
    cmpwi r3, 0x0
    beq L_8148A040
    mr r3, r31
    bl CDBFSFindClose
    lwz r0, 0x8(r1)
    cmpwi r0, 0x2
    bne L_8148A0E0
    mr r4, r29
    addi r3, r1, 0x10
    bl CDBFSDeleteDir
    cmpwi r3, 0x0
    beq L_8148A0E0
    b L_8148A0E4
    L_8148A0E0:
    li r3, 0x0
    L_8148A0E4:
    lwz r0, 0x124(r1)
    lwz r31, 0x11c(r1)
    lwz r30, 0x118(r1)
    lwz r29, 0x114(r1)
    lwz r28, 0x110(r1)
    mtlr r0
    addi r1, r1, 0x120
    blr
#endif
}

asm CDBErr CDBDatabaseCleanUpEmptyDirectories(CDBDatabase* database, CDBRecordLocation recordLocation) {
#ifdef __MWERKS__
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    cmpwi r3, 0x0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    mr r29, r4
    lwz r5, lbl_81698D8C(r0)
    addi r30, r5, 0x430c
    bne L_8148A13C
    li r3, 0x1
    b L_8148A2FC
    L_8148A13C:
    bl CDBLock
    lwz r3, 0x8(r31)
    cmpwi r3, 0x0
    beq L_8148A158
    addis r3, r3, 0x1
    lwz r31, -0x3ff0(r3)
    b L_8148A15C
    L_8148A158:
    li r31, 0x0
    L_8148A15C:
    bl CDBUnlock
    cmpwi r31, 0x0
    bne L_8148A198
    li r3, 0x2
    bl CDBIsPrintDebugMessage
    cmpwi r3, 0x0
    beq L_8148A190
    li r3, 0x2
    bl CDBReport_
    lis r3, lbl_8166B5D0@ha
    addi r3, r3, lbl_8166B5D0@l
    crclr 4*cr1+eq
    bl OSReport
    L_8148A190:
    li r3, 0x1b
    b L_8148A2FC
    L_8148A198:
    cmpwi r31, 0x1
    bne L_8148A1D0
    li r3, 0x2
    bl CDBIsPrintDebugMessage
    cmpwi r3, 0x0
    beq L_8148A1C8
    li r3, 0x2
    bl CDBReport_
    lis r3, lbl_8166B618@ha
    addi r3, r3, lbl_8166B618@l
    crclr 4*cr1+eq
    bl OSReport
    L_8148A1C8:
    li r3, 0x1a
    b L_8148A2FC
    L_8148A1D0:
    clrlwi. r0, r29, 31
    beq L_8148A24C
    mr r3, r30
    li r4, 0x1
    bl CDBFSFindFirstRoot
    b L_8148A234
    L_8148A1E8:
    mr r3, r30
    bl CDBFindDataIsDirectory
    cmpwi r3, 0x0
    beq L_8148A22C
    mr r3, r30
    bl CDBFindDataGetName
    bl CDBFSIsYearDirName
    cmpwi r3, 0x0
    beq L_8148A22C
    mr r3, r30
    bl CDBFindDataGetName
    li r4, 0x1
    li r5, 0x0
    bl CDBDatabaseCleanUpEmptyDirectoriesMonth
    cmpwi r3, 0x0
    beq L_8148A22C
    b L_8148A2FC
    L_8148A22C:
    mr r3, r30
    bl CDBFSFindNext
    L_8148A234:
    mr r3, r30
    bl CDBFindDataIsEnd
    cmpwi r3, 0x0
    beq L_8148A1E8
    mr r3, r30
    bl CDBFSFindClose
    L_8148A24C:
    bl CDBVFSync
    li r31, 0x0
    bl CDBFSSDIsMounted
    cmpwi r3, 0x0
    beq L_8148A270
    bl CDBFSSDIsEjected
    cmpwi r3, 0x0
    bne L_8148A270
    li r31, 0x1
    L_8148A270:
    cmpwi r31, 0x0
    beq L_8148A2F4
    rlwinm. r0, r29, 0, 30, 30
    beq L_8148A2F4
    mr r3, r30
    li r4, 0x2
    bl CDBFSFindFirstRoot
    b L_8148A2DC
    L_8148A290:
    mr r3, r30
    bl CDBFindDataIsDirectory
    cmpwi r3, 0x0
    beq L_8148A2D4
    mr r3, r30
    bl CDBFindDataGetName
    bl CDBFSIsYearDirName
    cmpwi r3, 0x0
    beq L_8148A2D4
    mr r3, r30
    bl CDBFindDataGetName
    li r4, 0x2
    li r5, 0x0
    bl CDBDatabaseCleanUpEmptyDirectoriesMonth
    cmpwi r3, 0x0
    beq L_8148A2D4
    b L_8148A2FC
    L_8148A2D4:
    mr r3, r30
    bl CDBFSFindNext
    L_8148A2DC:
    mr r3, r30
    bl CDBFindDataIsEnd
    cmpwi r3, 0x0
    beq L_8148A290
    mr r3, r30
    bl CDBFSFindClose
    L_8148A2F4:
    bl CDBVFSync
    li r3, 0x0
    L_8148A2FC:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
#endif
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
