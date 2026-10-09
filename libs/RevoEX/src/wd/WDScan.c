#include <revolution/wd.h>

#include <private/ipc/types.h>
#include <private/wd.h>

#include <revolution/ncd.h>
#include <revolution/os.h>

#include <string.h>

const u8 scRsnOui0 = 0;
const u8 scRsnOui1 = 0x0F;
const u8 scRsnOui2 = 0xAC;
const u8 scRsnOuiPad = 0;
const u8 scWpaOui0 = 0;
const u8 scWpaOui1 = 0x50;
const u8 scWpaOui2 = 0xF2;
const u8 scWpaOuiPad = 0;
/* MWCC places the WPA search bytes in .sdata. */
#pragma push
#pragma section sconst_type ".sdata"
const u8 scWpaFindOui0 = 0;
const u8 scWpaFindOui1 = 0x50;
const u8 scWpaFindOui2 = 0xF2;
const u8 scWpaFindOuiPad0 = 0;
const u8 scWpaFindOuiPad1 = 0;
const u8 scWpaFindOuiPad2 = 0;
const u8 scWpaFindOuiPad3 = 0;
const u8 scWpaFindOuiPad4 = 0;
#pragma pop

/* MWCC must load the OUI bytes from memory instead of folding their values. */
#define scRsnOui0 (*((volatile const u8*)&scRsnOui0))
#define scRsnOui1 (*((volatile const u8*)&scRsnOui1))
#define scRsnOui2 (*((volatile const u8*)&scRsnOui2))
#define scWpaOui0 (*((volatile const u8*)&scWpaOui0))
#define scWpaOui1 (*((volatile const u8*)&scWpaOui1))
#define scWpaOui2 (*((volatile const u8*)&scWpaOui2))
#define scWpaFindOui0 (*((volatile const u8*)&scWpaFindOui0))
#define scWpaFindOui1 (*((volatile const u8*)&scWpaFindOui1))
#define scWpaFindOui2 (*((volatile const u8*)&scWpaFindOui2))

#define WAIT_FOR_OPERATION(...)                                                                                                                      \
    do {                                                                                                                                             \
        while ((__VA_ARGS__)) {                                                                                                                      \
            OSSleepTicks(OSMillisecondsToTicks(10));                                                                                                 \
        }                                                                                                                                            \
    } while (FALSE)

static inline s32 GetResultWD(s32 result) {
    switch (result) {
        case WD_INTERNAL_ERR_OK: {
            return WD_ERR_OK;
        }
        case WD_INTERNAL_ERR_BAD_ARGUMENTS: {
            return WD_ERR_BAD_ARGUMENTS;
        }
        case WD_INTERNAL_ERR_IPC_ERROR: {
            return WD_ERR_FATAL;
        }
        case WD_INTERNAL_ERR_WL_ERROR: {
            return WD_ERR_WL_ERROR;
        }
        case WD_INTERNAL_ERR_4: {
            return WD_ERR_7;
        }
        case WD_INTERNAL_ERR_ALLOC_FAILED: {
            return WD_ERR_FATAL;
        }
        case WD_INTERNAL_ERR_ALREADY_INITIALIZED: {
            return WD_ERR_6;
        }
        case IPC_RESULT_NOEXISTS: {
            return WD_ERR_5;
        }
        default: {
            return WD_ERR_FATAL;
        }
    }
}

static inline s32 GetResultNCD(s32 result) {
    switch (result) {
        case -4: {
            return WD_ERR_6;
        }
        case -5: {
            return WD_ERR_4;
        }
        case -8: {
            return WD_ERR_5;
        }
        default: {
            return WD_ERR_FATAL;
        }
    }
}

s32 WDCheckEnableChannel(u16* enableChannel) {
    s32 id;
    s32 result;
    s32 infoResult;

    if (enableChannel != NULL) {
        *enableChannel = 0;
    }

    id = NCDLockWirelessDriver();
    if (id > 0) {
        result = WD_Startup(3);
        if (result == WD_INTERNAL_ERR_OK) {
            WD_Info info;
            infoResult = WD_GetInfo(&info);
            if (infoResult == WD_INTERNAL_ERR_OK && enableChannel != NULL) {
                *enableChannel = info.enableChannel;
            }
            WAIT_FOR_OPERATION(WD_Cleanup());
        }

        WAIT_FOR_OPERATION(NCDUnlockWirelessDriver(id));
    } else {
        return GetResultNCD(id);
    }
    if (result == WD_ERR_OK) {
        return GetResultWD(infoResult);
    } else {
        return GetResultWD(result);
    }
}

s32 WDScanOnce(u8* scanBuffer, u32 scanBufferLen, WDScanParam* param) {
    s32 id;
    s32 result;
    s32 scanResult;

    id = NCDLockWirelessDriver();
    if (id > 0) {
        result = WD_Startup(3);
        if (result == WD_INTERNAL_ERR_OK) {
            memset(scanBuffer, 0, scanBufferLen);
            scanResult = WD_Scan(param, scanBuffer, scanBufferLen);
            WAIT_FOR_OPERATION(WD_Cleanup());
        }

        WAIT_FOR_OPERATION(NCDUnlockWirelessDriver(id));
    } else {
        return GetResultNCD(id);
    }
    if (result == WD_ERR_OK) {
        return GetResultWD(scanResult);
    } else {
        return GetResultWD(result);
    }
}

s32 WDGetPrivacyMode(WDBssDesc* bssDesc) {
    WDVendorInfoElement* ieData;
    u32 ieLength = 0;
    u8 readIE[8];
    s32 result;

    if (WDFindInformationElement((WDInfoElement**)&ieData, &ieLength, bssDesc, 0x30)) {
        u8 data[WD_VENDOR_LENGTH];

        data[0] = scRsnOui0;
        data[1] = scRsnOui1;
        data[2] = scRsnOui2;
        memcpy(readIE, ieData, sizeof(WDVendorInfoElement) + 2);
        if (memcmp(&readIE[2], data, WD_VENDOR_LENGTH) == 0) {
            switch (readIE[5]) {
                case 1:
                    return WD_PRIVACY_MODE_DS_COMMUNICATION;
                case 2:
                    return WD_PRIVACY_MODE_7;
                case 3:
                    break;
                case 4:
                    return WD_PRIVACY_MODE_5;
                case 5:
                    return WD_PRIVACY_MODE_2;
                default:
                    break;
            }
        }
    }

    {
        u8 data[WD_VENDOR_LENGTH];
        u8 findData[WD_VENDOR_LENGTH];

        findData[0] = scWpaFindOui0;
        findData[1] = scWpaFindOui1;
        findData[2] = scWpaFindOui2;
        if (WDiFindVendorSpecificIE(&ieData, &ieLength, bssDesc, 0xDD, findData, 1)) {
            data[0] = scWpaOui0;
            data[1] = scWpaOui1;
            data[2] = scWpaOui2;

            memcpy(readIE, ieData, sizeof(WDVendorInfoElement));
            if (memcmp(&readIE[2], data, WD_VENDOR_LENGTH) == 0) {
                switch (readIE[5]) {
                    case 1:
                        return WD_PRIVACY_MODE_DS_COMMUNICATION;
                    case 2:
                        return WD_PRIVACY_MODE_4;
                    case 3:
                        break;
                    case 4:
                        return WD_PRIVACY_MODE_6;
                    case 5:
                        return WD_PRIVACY_MODE_2;
                    default:
                        break;
                }
            }
        }
    }

    if (bssDesc != NULL && (bssDesc->capabilities & 0x10) == 0x10) {
        result = WD_PRIVACY_MODE_8;
    } else {
        result = WD_PRIVACY_MODE_NONE;
    }
    return result;
}

BOOL WDFindInformationElement(WDInfoElement** outIE, u32* outIELength, WDBssDesc* bssDesc, int id) {
    BOOL found = FALSE;

    if (bssDesc != NULL) {
        int offset;
        u8* ptr = (u8*)(bssDesc + 1);
        WDInfoElement* infoElement;

        for (offset = 0; offset < bssDesc->ieLength; offset = (infoElement->length + offset) + sizeof(WDInfoElement)) {
            infoElement = (WDInfoElement*)(ptr + offset);
            if (infoElement->id == id) {
                break;
            }
        }
        if (offset < bssDesc->ieLength) {
            if (outIE != NULL) {
                *outIE = infoElement + 1;
            }
            if (outIELength != NULL) {
                *outIELength = infoElement->length;
            }
            found = TRUE;
        }
    }
    if (!found) {
        if (outIE != NULL) {
            *outIE = NULL;
        }
        if (outIELength != NULL) {
            *outIELength = 0;
        }
    }
    return found;
}

BOOL WDiFindVendorSpecificIE(WDVendorInfoElement** outIE, u32* outIELength, WDBssDesc* bssDesc, int id, u8* data, u8 mode) {
    u32* lengthResult = outIELength;
    WDVendorInfoElement** elementResult = outIE;
    int length;
    BOOL found = FALSE;

    if (bssDesc != NULL) {
        s32 offset;
        u8* ptr = (u8*)(bssDesc + 1);
        WDVendorInfoElement* infoElement = (WDVendorInfoElement*)ptr;

        length = bssDesc->ieLength;

        for (offset = 0; offset < length; offset += infoElement->length + 2) {
            infoElement = (WDVendorInfoElement*)(ptr + offset);
            if (infoElement->id == (u32)id) {
                u8 elementMode = infoElement->mode;
                if (memcmp(infoElement->data, data, WD_VENDOR_LENGTH) == 0 && elementMode == mode) {
                    break;
                }
            }
        }
        if (offset < length) {
            if (elementResult != NULL) {
                *elementResult = infoElement + 1;
            }
            if (lengthResult != NULL) {
                *lengthResult = infoElement->length - (sizeof(WDVendorInfoElement) - sizeof(WDInfoElement));
            }
            found = TRUE;
        }
    }
    if (!found) {
        if (elementResult != NULL) {
            *elementResult = NULL;
        }
        if (lengthResult != NULL) {
            *lengthResult = 0;
        }
    }
    return found;
}
