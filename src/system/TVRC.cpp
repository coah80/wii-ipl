#include "system/TVRC.h"
#include "utility/iplTVRCUtils.h"

#include <decomp.h>

#include <revolution/arc.h>
#include <revolution/wpad.h>

#include <cstdio>
#include <cstring>

#pragma sym on

#pragma push
#pragma section data_type ".sdata"
extern "C" char scTvrcFileHeader[5] = {'T', 'V', 'R', '0', '\0'};
#pragma pop

namespace LibTVRC {
    const char* TVRC_FILE_HEADER = scTvrcFileHeader;
    u32 __tienHoseiNsec = 1100;
    u32 _limitMilli = 400;

    struct TVRCHandle : ARCHandle {
        u8 _padding[4];
    };
    TVRCHandle _database;
    OSAlarm _alarm;

    BOOL _isRepeatActive;
    BOOL _isUseRepeatCode;

    u32 _lastError;
    typedef struct {
        u8 magic[4];  // 0x00
        u32 fileSize;
        char reserved[4];
        f32 carrierFrequencyKHz;
        f32 onTimeRatio;
        u32 unitTimeUs;
        struct {
            u32 offset;
            u32 repeatOffset;
        } commands[TVRC_COMMAND_MAP_MAX];
    } _FileData;
    struct _CommandData {
        u32 flags;
        u32 bitLength;
        u8 bits[1];
    };
    _FileData* _tvrcFile;
    f32 _Hz;
    f32 _onTimeRatio;

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

    u32 _tickT;
    OSTime _tickWait[2];

    void __FTVRCLoop0Handler(OSAlarm *alarm, OSContext *ctx);

    void __FTVRCLoop1Handler(OSAlarm *alarm, OSContext *ctx);
}  // namespace LibTVRC

using namespace LibTVRC;

BOOL TVRCInit(void* pRsrc) {
    if (_isInitialized) {
        _lastError = 0;
        return FALSE;
    }

    if (!ARCInitHandle(pRsrc, &_database)) {
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

    if (!_isInitialized || _database.archiveStartAddr == NULL) {
        return FALSE;
    }
    if (static_cast<ARCHeader*>(_database.archiveStartAddr)->magic != ARC_MAGIC) {
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

    if (!ARCFastOpen(&_database, dirEntry.entryNum, &file)) {
        _lastError = 6;
        return FALSE;
    }
    int fileLen = ARCGetLength(&file);
    if (fileLen > length) {
        _lastError = 7;
        return FALSE;
    }
    memcpy(pFileData, ARCGetStartAddrInMem(&file), fileLen);

    _tvrcFile = static_cast<_FileData*>(pFileData);
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
    if (cmd >= 0 && _isInitialized && _tvrcFile != NULL && _tvrcFile->commands[cmd].offset != 0) {
        result = TRUE;
    }
    return result;
}

static inline const _CommandData* TVRCGetCommandData(const _FileData* file, u32 offset) {
    const u8* command = reinterpret_cast<const u8*>(file);
    command += offset;
    return reinterpret_cast<const _CommandData*>(command);
}

BOOL TVRCSendStartAsync(s32 cmd) {
    if (!_isInitialized || _isActive || _makerID == -1) {
        return FALSE;
    }
    if (!ipl::utility::RangeCheckGELTS32(cmd, 0, TVRC_COMMAND_MAP_MAX)) {
        return FALSE;
    }
    BOOL enabled = OSDisableInterrupts();
    _FileData* file = _tvrcFile;
    memcmp(file, TVRC_FILE_HEADER, 4);
    const u32& offset = file->commands[cmd].offset;
    if (offset != 0) {
        if (!_isUseCustomParams) {
            _Hz = 1000.0f * _tvrcFile->carrierFrequencyKHz;
            _onTimeRatio = _tvrcFile->onTimeRatio;
            _tickT = OSMicrosecondsToTicks(_tvrcFile->unitTimeUs);
        }
        _isUseRepeatCode = _tvrcFile->commands[cmd].repeatOffset != 0;
        const u32& repeatOffset = _tvrcFile->commands[cmd].repeatOffset;
        const _CommandData* data = TVRCGetCommandData(_tvrcFile, offset);
        _bitLength = data->bitLength;
        _bitArray = reinterpret_cast<u32>(data->bits);
        if (_isUseRepeatCode) {
            const _CommandData* repeat = TVRCGetCommandData(file, repeatOffset);
            _repeatBitLength = repeat->bitLength;
            _repeatBitArray = reinterpret_cast<u32>(repeat->bits);
        } else {
            _repeatBitLength = _bitLength;
            _repeatBitArray = _bitArray;
        }
        _tickWait[1] = OSNanosecondsToTicks((OSTime)(1000000000.0 * _onTimeRatio / _Hz - __tienHoseiNsec));
        _tickWait[0] = OSNanosecondsToTicks((OSTime)(1000000000.0 * (1.0 - _onTimeRatio) / _Hz - __tienHoseiNsec));
        if (_tickWait[1] < 10) {
            _tickWait[1] = 10;
        }
        if (_tickWait[0] < 10) {
            _tickWait[0] = 10;
        }
        _isActive = TRUE;
        _isReserveDeactive = FALSE;
        _isOnOff = FALSE;
        _isLastOnOff = FALSE;
        _func0state = 1;
        _loop0count = 0;
        _totalStartTime = OSGetTime();
        OSSetAlarm(&_alarm, OSMicrosecondsToTicks(1000), __FTVRCLoop0Handler);
    }
    OSRestoreInterrupts(enabled);
    return TRUE;
}

void LibTVRC::__FTVRCLoop0Handler(OSAlarm* alarm, OSContext* ctx) {
    if (!_isActive) {
        _func0state = 2;
    }
    if (_func0state == 1) {
        _func0state = 0;
    } else if (_func0state == 0) {
        _loop0count++;
        _isLastOnOff = _isOnOff;
        _func0state = 0;
    } else if (_func0state == 2) {
        if (_isReserveDeactive || OSTicksToMilliseconds(OSGetTime() - _totalStartTime) > _limitMilli) {
            WPADSetSensorBarPower(TRUE);
            _isActive = FALSE;
            return;
        }
        _isRepeatActive = _isUseRepeatCode;
        _bitLength = _repeatBitLength;
        _bitArray = _repeatBitArray;
        _isOnOff = FALSE;
        _isLastOnOff = FALSE;
        _func0state = 0;
        _loop0count = 0;
    }
    _ctCombo = 0;
    while (_loop0count < (int)_bitLength) {
        _isOnOff = (((u8*)_bitArray)[_loop0count / 8] >> (7 - _loop0count % 8)) & 1;
        _ctCombo++;
        if (_isLastOnOff != _isOnOff) {
            _func1state = -1;
            _func0state = 0;
            __FTVRCLoop1Handler(alarm, ctx);
            return;
        }
        _loop0count++;
        _isLastOnOff = _isOnOff;
    }
    _ctCombo++;
    _func1state = -1;
    _func0state = 2;
    __FTVRCLoop1Handler(alarm, ctx);
}

namespace LibTVRC {
    void __FTVRCLoop1Handler(OSAlarm *alarm, OSContext *ctx) {
        if (_ctCombo != 0 && _isActive) {
            if (_func1state == -1) {
                _unitStartTime = OSGetTime();
                _func1state = 0;
            }

            if (_isLastOnOff) {
                _unitLastTime = OSGetTime();

                if (_func1state == 0) {
                    WPADSetSensorBarPower(TRUE);
                    _func1state = 1;
                    OSSetAlarm(&_alarm, _tickWait[1], __FTVRCLoop1Handler);
                    return;
                }

                BOOL active = (int)(_unitLastTime - _unitStartTime) < (int)(_tickT * _ctCombo);
                WPADSetSensorBarPower(FALSE);
                _func1state = 0;
                if (active) {
                    OSSetAlarm(&_alarm, _tickWait[0], __FTVRCLoop1Handler);
                } else {
                    OSSetAlarm(&_alarm, _tickWait[0], __FTVRCLoop0Handler);
                }
            } else {
                WPADSetSensorBarPower(FALSE);
                OSSetAlarm(&_alarm, _tickT * _ctCombo, __FTVRCLoop0Handler);
            }
        }
    }
}  // namespace LibTVRC
