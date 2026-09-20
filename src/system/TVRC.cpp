#include "system/TVRC.h"

#include <decomp.h>

#include <revolution/arc.h>
#include <revolution/wpad.h>

#include <cstdio>
#include <cstring>

#pragma sym on

extern "C" const f32 lbl_816945C8 = 1000.0f;
extern "C" const f64 lbl_816945D0 = 1000000000.0;
extern "C" const f64 lbl_816945D8 = 1.0;
extern "C" const f64 lbl_816945E0 = 4503599627370496.0;

extern "C" BOOL _isInitialized__7LibTVRC;
extern "C" BOOL _isActive__7LibTVRC;
extern "C" int _makerID__7LibTVRC;
extern "C" void* _tvrcFile__7LibTVRC;
extern "C" const char* TVRC_FILE_HEADER__7LibTVRC;
extern "C" BOOL _isUseCustomParams__7LibTVRC;
extern "C" f32 _Hz__7LibTVRC;
extern "C" f32 _onTimeRatio__7LibTVRC;
extern "C" u32 _tickT__7LibTVRC;
extern "C" BOOL _isUseRepeatCode__7LibTVRC;
extern "C" u32 _bitLength__7LibTVRC;
extern "C" u32 _bitArray__7LibTVRC;
extern "C" u32 _repeatBitLength__7LibTVRC;
extern "C" u32 _repeatBitArray__7LibTVRC;
extern "C" OSTime _tickWait__7LibTVRC[2];
extern "C" BOOL _isReserveDeactive__7LibTVRC;
extern "C" BOOL _isOnOff__7LibTVRC;
extern "C" BOOL _isLastOnOff__7LibTVRC;
extern "C" int _func0state__7LibTVRC;
extern "C" int _loop0count__7LibTVRC;
extern "C" OSTime _totalStartTime__7LibTVRC;
extern "C" OSAlarm _alarm__7LibTVRC;
extern "C" u32 __tienHoseiNsec__7LibTVRC;

extern "C" void _savegpr_25();
extern "C" void _restgpr_25();
extern "C" void RangeCheckGELTS32__Q23ipl7utilityFlll();
extern "C" void __cvt_dbl_usll();
extern "C" void __div2i();
extern "C" void __FTVRCLoop0Handler__7LibTVRCFP7OSAlarmP9OSContext();

namespace LibTVRC {
    const char* TVRC_FILE_HEADER = "TVR0";
    u32 __tienHoseiNsec = 1100;
    u32 _limitMilli = 400;

    ARCHandle _database ALIGN32;
    OSAlarm _alarm;

    BOOL _isRepeatActive;
    BOOL _isUseRepeatCode;

    u32 _lastError;
    typedef struct {
        u8 magic[4];  // 0x00
        u32 fileSize;
        char unk_0x08[4];
        f32 unk_0x0C;
        f32 unk_0x10;
        u32 unk_0x14;
        struct {
            u32 offset;
            u32 unk_0x04;
        } unk_0x18[TVRC_COMMAND_MAP_MAX - 1 /*?*/];
    } _FileData;
    _FileData* _tvrcFile;
    undefined4 _Hz;
    undefined4 _onTimeRatio;

    int _makerID;
    int _typeNo;

    BOOL _isUseCustomParams;
    BOOL _isInitialized;
    BOOL _isActive;
    BOOL _isReserveDeactive;

    OSTime _unitStartTime;
    OSTime _unitLastTime;
    OSTime _totalStartTime;

    BOOL _isOnOff;
    BOOL _isLastOnOff;

    int _ctCombo;

    int _func0state;
    int _loop0count;

    int _func1state;

    u32 _bitLength;
    u32 _bitArray;
    u32 _repeatBitLength;
    u32 _repeatBitArray;

    OSTime _tickT;
    OSTime _tickWait[2];

    void __FTVRCLoop0Handler(OSAlarm *alarm, OSContext *ctx) {
        return;
    }

    void __FTVRCLoop1Handler(OSAlarm *alarm, OSContext *ctx) {
        if (_ctCombo != 0 && _isActive != 0) {
            if (_func1state == -1) {
                _unitStartTime = OSGetTime();
                _func1state = 0;
            }

            if (_isLastOnOff != 0) {
                _unitLastTime = OSGetTime();

                if (_func1state == 0) {
                    WPADSetSensorBarPower(TRUE);
                    _func1state = 1;
                    OSSetAlarm(&_alarm, _tickWait[1], __FTVRCLoop1Handler);
                    return;
                }

                BOOL active = (int)(_unitLastTime - _unitStartTime) < (int)(*(u32*)&_tickT * _ctCombo);
                WPADSetSensorBarPower(FALSE);
                _func1state = 0;
                if (active) {
                    OSSetAlarm(&_alarm, _tickWait[0], __FTVRCLoop1Handler);
                } else {
                    OSSetAlarm(&_alarm, _tickWait[0], __FTVRCLoop0Handler);
                }
            } else {
                WPADSetSensorBarPower(FALSE);
                OSSetAlarm(&_alarm, *(u32*)&_tickT * _ctCombo, __FTVRCLoop0Handler);
            }
        }
    }
}  // namespace LibTVRC

using namespace LibTVRC;

BOOL TVRCInit(void* pRsrc) {
    if (_isInitialized) {
        _lastError = 0;
        return FALSE;
    }

    if (ARCInitHandle(pRsrc, &_database) == FALSE) {
        _lastError = 4;
        return FALSE;
    }

    _makerID = -1;
    _typeNo = 0;

    OSCreateAlarm(&_alarm);

    _isInitialized = TRUE;

    WPADSetSensorBarPower(TRUE);

    return FALSE;
}

BOOL TVRCSetModelType(int makerID, int typeNo, void* pFileData, int length) {
    ARCDir dir;
    ARCDirEntry dirEntry;
    char dirName[16];

    ARCFileInfo file;

    if (_isInitialized == FALSE || _database.archiveStartAddr == NULL) {
        return FALSE;
    }
    if (((ARCHeader*)_database.archiveStartAddr)->magic != ARC_MAGIC) {
        return FALSE;
    }
    if (makerID == _makerID && typeNo == _typeNo) {
        return TRUE;
    }

    sprintf(dirName, "/%04d", makerID);
    if (!ARCOpenDir(&_database, dirName, &dir)) {
        _lastError = 6;
        return FALSE;
    }
    int curType = typeNo;
    while (ARCReadDir(&dir, &dirEntry)) {
        if (--curType < 0) {
            break;
        }
    }
    ARCCloseDir(&dir);

    if (ARCFastOpen(&_database, dirEntry.entryNum, &file) == FALSE) {
        _lastError = 6;
        return FALSE;
    }
    int fileLen = ARCGetLength(&file);
    if (fileLen > length) {
        _lastError = 7;
        return FALSE;
    }
    memcpy(pFileData, ARCGetStartAddrInMem(&file), fileLen);

    _tvrcFile = (_FileData*)pFileData;
    _makerID = makerID;
    _typeNo = typeNo;
    _database.archiveStartAddr = NULL;

    return TRUE;
}

void TVRCSetRepeatTimeout(u32 value) {
    _limitMilli = value;
}

BOOL TVRCSendStopAsync() {
    if (!_isInitialized || !_isActive) {
        return FALSE;
    } else {
        _isReserveDeactive = TRUE;
        return TRUE;
    }
}

BOOL TVRCIsActive() {
    return _isActive;
}

BOOL TVRCIsValidCommand(int cmd) {
    BOOL result = FALSE;
    if (cmd >= 0 && _isInitialized && _tvrcFile != NULL && _tvrcFile->unk_0x18[cmd].offset != 0) {
        result = TRUE;
    }
    return result;
}

extern "C" asm BOOL TVRCSendStartAsync(s32 cmd) {
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    addi r11, r1, 0x40
    bl _savegpr_25
    lwz r0, _isInitialized__7LibTVRC
    mr r25, r3
    cmpwi r0, 0
    beq TVRCSendStartAsync_done
    lwz r0, _isActive__7LibTVRC
    cmpwi r0, 0
    bne TVRCSendStartAsync_done
    lwz r0, _makerID__7LibTVRC
    cmpwi r0, -1
    bne TVRCSendStartAsync_ready
TVRCSendStartAsync_done:
    li r3, 0
    b TVRCSendStartAsync_exit
TVRCSendStartAsync_ready:
    li r4, 0
    li r5, 8
    bl RangeCheckGELTS32__Q23ipl7utilityFlll
    cmpwi r3, 0
    bne TVRCSendStartAsync_valid
    li r3, 0
    b TVRCSendStartAsync_exit
TVRCSendStartAsync_valid:
    bl OSDisableInterrupts
    lwz r31, _tvrcFile__7LibTVRC
    mr r30, r3
    lwz r4, TVRC_FILE_HEADER__7LibTVRC
    li r5, 4
    mr r3, r31
    bl memcmp
    slwi r7, r25, 3
    add r5, r31, r7
    lwz r0, 0x18(r5)
    cmpwi r0, 0
    beq TVRCSendStartAsync_restore
    lwz r0, _isUseCustomParams__7LibTVRC
    cmpwi r0, 0
    bne TVRCSendStartAsync_custom
    lwz r6, _tvrcFile__7LibTVRC
    lis r3, 2
    lfs f1, lbl_816945C8
    lis r4, 0x8000
    lfs f0, 0xc(r6)
    subi r0, r3, 0x17b8
    fmuls f0, f1, f0
    stfs f0, _Hz__7LibTVRC
    lfs f0, 0x10(r6)
    stfs f0, _onTimeRatio__7LibTVRC
    lwz r3, 0xf8(r4)
    lwz r4, 0x14(r6)
    srwi r3, r3, 2
    divwu r0, r3, r0
    mullw r0, r4, r0
    srwi r0, r0, 3
    stw r0, _tickT__7LibTVRC
TVRCSendStartAsync_custom:
    lwz r6, _tvrcFile__7LibTVRC
    add r4, r6, r7
    lwz r3, 0x1c(r4)
    subic r0, r3, 1
    subfe. r0, r0, r3
    stw r0, _isUseRepeatCode__7LibTVRC
    lwz r0, 0x18(r5)
    add r5, r6, r0
    lwz r3, 4(r5)
    addi r0, r5, 8
    stw r3, _bitLength__7LibTVRC
    stw r0, _bitArray__7LibTVRC
    beq TVRCSendStartAsync_no_repeat
    lwz r0, 0x1c(r4)
    add r4, r31, r0
    lwz r3, 4(r4)
    addi r0, r4, 8
    stw r3, _repeatBitLength__7LibTVRC
    stw r0, _repeatBitArray__7LibTVRC
    b TVRCSendStartAsync_timing
TVRCSendStartAsync_no_repeat:
    stw r3, _repeatBitLength__7LibTVRC
    stw r0, _repeatBitArray__7LibTVRC
TVRCSendStartAsync_timing:
    lfs f1, _onTimeRatio__7LibTVRC
    lis r4, 0x8000
    lfd f0, lbl_816945D0
    lis r27, 0x4330
    lwz r0, 0xf8(r4)
    lis r3, 2
    fmul f1, f0, f1
    lfs f0, _Hz__7LibTVRC
    srwi r4, r0, 2
    subi r0, r3, 0x17b8
    lwz r25, __tienHoseiNsec__7LibTVRC
    divwu r26, r4, r0
    fdiv f2, f1, f0
    stw r27, 8(r1)
    lfd f1, lbl_816945E0
    stw r25, 0xc(r1)
    lfd f0, 8(r1)
    fsub f0, f0, f1
    fsub f1, f2, f0
    bl __cvt_dbl_usll
    li r31, 0
    li r6, 0x1f40
    mulhwu r7, r26, r4
    li r5, 0
    mullw r8, r31, r4
    mullw r0, r26, r3
    add r3, r7, r8
    mullw r4, r26, r4
    add r3, r3, r0
    bl __div2i
    lfs f2, _onTimeRatio__7LibTVRC
    lis r28, _tickWait__7LibTVRC@ha
    lfd f1, lbl_816945D8
    addi r29, r28, _tickWait__7LibTVRC@l
    lfd f0, lbl_816945D0
    fsub f3, f1, f2
    lfs f2, _Hz__7LibTVRC
    stw r25, 0x14(r1)
    lfd f1, lbl_816945E0
    fmul f3, f0, f3
    stw r27, 0x10(r1)
    lfd f0, 0x10(r1)
    stw r4, 0xc(r29)
    fdiv f2, f3, f2
    stw r3, 8(r29)
    fsub f0, f0, f1
    fsub f1, f2, f0
    bl __cvt_dbl_usll
    mulhwu r7, r26, r4
    li r6, 0x1f40
    li r5, 0
    mullw r8, r31, r4
    mullw r0, r26, r3
    add r3, r7, r8
    mullw r4, r26, r4
    add r3, r3, r0
    bl __div2i
    lwz r0, 8(r29)
    li r6, 0xa
    lwz r7, 0xc(r29)
    xoris r5, r31, 0x8000
    stw r4, 4(r29)
    xoris r0, r0, 0x8000
    subfc r4, r6, r7
    subfe r5, r5, r0
    stw r3, _tickWait__7LibTVRC@l(r28)
    subfe r5, r0, r0
    neg. r5, r5
    beq TVRCSendStartAsync_wait0
    stw r6, 0xc(r29)
    stw r31, 8(r29)
TVRCSendStartAsync_wait0:
    lis r8, _tickWait__7LibTVRC@ha
    li r5, 0
    addi r7, r8, _tickWait__7LibTVRC@l
    lwz r0, _tickWait__7LibTVRC@l(r8)
    lwz r3, 4(r7)
    li r6, 0xa
    xoris r0, r0, 0x8000
    xoris r4, r5, 0x8000
    subfc r3, r6, r3
    subfe r4, r4, r0
    subfe r4, r0, r0
    neg. r4, r4
    beq TVRCSendStartAsync_wait1
    stw r6, 4(r7)
    stw r5, _tickWait__7LibTVRC@l(r8)
TVRCSendStartAsync_wait1:
    li r0, 0
    li r3, 1
    stw r3, _isActive__7LibTVRC
    stw r0, _isReserveDeactive__7LibTVRC
    stw r0, _isOnOff__7LibTVRC
    stw r0, _isLastOnOff__7LibTVRC
    stw r3, _func0state__7LibTVRC
    stw r0, _loop0count__7LibTVRC
    bl OSGetTime
    stw r4, _totalStartTime__7LibTVRC+4
    lis r4, 2
    lis r5, 0x8000
    lis r7, __FTVRCLoop0Handler__7LibTVRCFP7OSAlarmP9OSContext@ha
    stw r3, _totalStartTime__7LibTVRC
    subi r0, r4, 0x17b8
    lis r3, _alarm__7LibTVRC@ha
    addi r7, r7, __FTVRCLoop0Handler__7LibTVRCFP7OSAlarmP9OSContext@l
    lwz r4, 0xf8(r5)
    addi r3, r3, _alarm__7LibTVRC@l
    li r5, 0
    srwi r4, r4, 2
    divwu r0, r4, r0
    mulli r0, r0, 0x3e8
    srwi r6, r0, 3
    bl OSSetAlarm
TVRCSendStartAsync_restore:
    mr r3, r30
    bl OSRestoreInterrupts
    li r3, 1
TVRCSendStartAsync_exit:
    addi r11, r1, 0x40
    bl _restgpr_25
    lwz r0, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}
