#include <revolution/wd.h>

#include <private/ipc/types.h>
#include <private/wd.h>

#include <revolution/ncd.h>
#include <revolution/os.h>

#include <string.h>

extern volatile const u8 lbl_81695060;
extern volatile const u8 lbl_81695061;
extern volatile const u8 lbl_81695062;
extern volatile const u8 lbl_81695064;
extern volatile const u8 lbl_81695065;
extern volatile const u8 lbl_81695066;
extern volatile u8 lbl_81697D70;
extern volatile u8 lbl_81697D71;
extern volatile u8 lbl_81697D72;
extern void _savegpr_21();
extern void _restgpr_21();

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

    if (enableChannel != NULL) {
        *enableChannel = 0;
    }

    id = NCDLockWirelessDriver();
    if (id <= 0) {
        goto ncd_err;
    } else {
        s32 result = WD_Startup(3);
        s32 result2;
        if (result == WD_INTERNAL_ERR_OK) {
            WD_Info info;
            result2 = WD_GetInfo(&info);
            if (result2 == WD_INTERNAL_ERR_OK && enableChannel != NULL) {
                *enableChannel = info.enableChannel;
            }
            WAIT_FOR_OPERATION(WD_Cleanup());
        }

        WAIT_FOR_OPERATION(NCDUnlockWirelessDriver(id));
        goto wd_err;

    ncd_err:
        return GetResultNCD(id);

    wd_err:
        if (result == WD_ERR_OK) {
            return GetResultWD(result2);
        } else {
            return GetResultWD(result);
        }
    }
}

s32 WDScanOnce(u8* scanBuffer, u32 scanBufferLen, WDScanParam* param) {
    s32 id;

    id = NCDLockWirelessDriver();
    if (id <= 0) {
        goto ncd_err;
    } else {
        s32 result = WD_Startup(3);
        s32 result2;
        if (result == WD_INTERNAL_ERR_OK) {
            memset(scanBuffer, 0, scanBufferLen);
            result2 = WD_Scan(param, scanBuffer, scanBufferLen);
            WAIT_FOR_OPERATION(WD_Cleanup());
        }

        WAIT_FOR_OPERATION(NCDUnlockWirelessDriver(id));
        goto wd_err;

    ncd_err:
        return GetResultNCD(id);

    wd_err:
        if (result == WD_ERR_OK) {
            return GetResultWD(result2);
        } else {
            return GetResultWD(result);
        }
    }
}

s32 WDGetPrivacyMode(WDBssDesc* bssDesc) {
    WDVendorInfoElement* ieData;
    u32 ieLength = 0;
    u8 readIE[8];
    s32 result;

    if (WDFindInformationElement((WDInfoElement**)&ieData, &ieLength, bssDesc, 0x30)) {
        u8 data[WD_VENDOR_LENGTH];

        data[0] = lbl_81695060;
        data[1] = lbl_81695061;
        data[2] = lbl_81695062;
        memcpy(readIE, ieData, sizeof(WDVendorInfoElement) + 2);
        if (memcmp(&readIE[2], data, WD_VENDOR_LENGTH) == 0) {
            if ((s32)readIE[5] == 3) {
                goto privacy_second;
            }
            if ((s32)readIE[5] >= 3) {
                goto privacy_rsn_high;
            }
            if ((s32)readIE[5] == 1) {
                goto privacy_rsn_mode1;
            }
            if ((s32)readIE[5] >= 1) {
                goto privacy_rsn_mode7;
            }
            goto privacy_second;
        privacy_rsn_high:
            if ((s32)readIE[5] == 5) {
                goto privacy_rsn_mode2;
            }
            if ((s32)readIE[5] >= 5) {
                goto privacy_second;
            }
            goto privacy_rsn_mode5;
        }
    }
    goto privacy_second;

privacy_rsn_mode1:
    return WD_PRIVACY_MODE_DS_COMMUNICATION;
privacy_rsn_mode7:
    return WD_PRIVACY_MODE_7;
privacy_rsn_mode5:
    return WD_PRIVACY_MODE_5;
privacy_rsn_mode2:
    return WD_PRIVACY_MODE_2;

privacy_second: {
        u8 data[WD_VENDOR_LENGTH];
        u8 findData[WD_VENDOR_LENGTH];

        findData[0] = lbl_81697D70;
        findData[1] = lbl_81697D71;
        findData[2] = lbl_81697D72;
        if (!WDiFindVendorSpecificIE(&ieData, &ieLength, bssDesc, 0xDD, findData, 1)) {
            goto privacy_fallback;
        }
        data[0] = lbl_81695064;
        data[1] = lbl_81695065;
        data[2] = lbl_81695066;

        {
            memcpy(readIE, ieData, sizeof(WDVendorInfoElement));
            if (memcmp(&readIE[2], data, WD_VENDOR_LENGTH) != 0) {
                goto privacy_fallback;
            }
            if ((s32)readIE[5] == 3) {
                    goto privacy_fallback;
                }
                if ((s32)readIE[5] >= 3) {
                    goto privacy_wpa_high;
                }
                if ((s32)readIE[5] == 1) {
                    goto privacy_wpa_mode1;
                }
                if ((s32)readIE[5] >= 1) {
                    goto privacy_wpa_mode4;
                }
                goto privacy_fallback;
            privacy_wpa_high:
                if ((s32)readIE[5] == 5) {
                    goto privacy_wpa_mode2;
                }
                if ((s32)readIE[5] >= 5) {
                    goto privacy_fallback;
                }
                goto privacy_wpa_mode6;
        }
    }

privacy_wpa_mode1:
    return WD_PRIVACY_MODE_DS_COMMUNICATION;
privacy_wpa_mode4:
    return WD_PRIVACY_MODE_4;
privacy_wpa_mode6:
    return WD_PRIVACY_MODE_6;
privacy_wpa_mode2:
    return WD_PRIVACY_MODE_2;

privacy_fallback:
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
            infoElement = (WDInfoElement*)((u8*)ptr + offset);
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

asm BOOL WDiFindVendorSpecificIE(WDVendorInfoElement** outIE, u32* outIELength, WDBssDesc* bssDesc, int id, u8* data, u8 mode) {
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    addi r11, r1, 0x40
    bl _savegpr_21
    cmpwi r5, 0
    mr r30, r3
    mr r31, r4
    mr r21, r6
    mr r22, r7
    mr r23, r8
    li r28, 0
    beq WDiFindVendorSpecificIE_done
    addi r26, r5, 0x3e
    lhz r29, 0x3c(r5)
    mr r25, r26
    li r27, 0
    b WDiFindVendorSpecificIE_loop_check
WDiFindVendorSpecificIE_loop:
    lbzx r0, r26, r27
    add r25, r26, r27
    cmplw r0, r21
    bne WDiFindVendorSpecificIE_next
    lbz r24, 5(r25)
    mr r4, r22
    addi r3, r25, 2
    li r5, 3
    bl memcmp
    cmpwi r3, 0
    bne WDiFindVendorSpecificIE_next
    cmplw r24, r23
    beq WDiFindVendorSpecificIE_found
WDiFindVendorSpecificIE_next:
    lbz r0, 1(r25)
    add r3, r0, r27
    addi r27, r3, 2
WDiFindVendorSpecificIE_loop_check:
    cmpw r27, r29
    blt WDiFindVendorSpecificIE_loop
WDiFindVendorSpecificIE_found:
    cmpw r27, r29
    bge WDiFindVendorSpecificIE_done
    cmpwi r30, 0
    beq WDiFindVendorSpecificIE_no_out
    addi r0, r25, 6
    stw r0, 0(r30)
WDiFindVendorSpecificIE_no_out:
    cmpwi r31, 0
    beq WDiFindVendorSpecificIE_set_found
    lbz r3, 1(r25)
    addi r0, r3, -4
    stw r0, 0(r31)
WDiFindVendorSpecificIE_set_found:
    li r28, 1
WDiFindVendorSpecificIE_done:
    cmpwi r28, 0
    bne WDiFindVendorSpecificIE_return
    cmpwi r30, 0
    beq WDiFindVendorSpecificIE_no_out_null
    li r0, 0
    stw r0, 0(r30)
WDiFindVendorSpecificIE_no_out_null:
    cmpwi r31, 0
    beq WDiFindVendorSpecificIE_return
    li r0, 0
    stw r0, 0(r31)
WDiFindVendorSpecificIE_return:
    addi r11, r1, 0x40
    mr r3, r28
    bl _restgpr_21
    lwz r0, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}
