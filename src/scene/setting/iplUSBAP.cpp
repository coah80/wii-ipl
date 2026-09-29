extern "C" {
#include <private/wd.h>
}

#include <revolution/os.h>
#include <revolution/wd.h>

#include <string.h>

#define USBAP_STACK_SIZE 0x1000
#define USBAP_NICKNAME_LEN 0x14
#define USBAP_MAC_TABLE_MAX 0x14
#define USBAP_MAC_LENGTH 6
#define USBAP_SSID "NWCUSBAP"
#define USBAP_SSID_LENGTH 8

typedef void (*USBAPCallback)(int result);

static OSThread usbapThread;
static u8 usbapStack[USBAP_STACK_SIZE];
static OSMessageQueue usbapMessageQ;
static u16 usbapNickname[12];

static OSMessage usbapMsg;
static USBAPCallback usbapCallback;
static s32 usbapUseNickname;
static u16 usbapEnableChannel;
static u8* usbapScanBuffer;
static u8* usbapMacTable;
u8* gUSBAPResult;

extern "C" void* DoRegistration(void* param);

extern "C" int USBAPStartRegistration(void* unused1, void* unused2,
    u32 priority, s32 useNickname, const u16* nickname,
    USBAPCallback callback, u8* scanBuffer, u8* macTable) {
    s32 level;

    level = OSDisableInterrupts();
    usbapScanBuffer = scanBuffer;
    usbapMacTable = macTable;

    if (usbapThread.state != 0 && !OSIsThreadTerminated(&usbapThread)) {
        OSRestoreInterrupts(level);
        return 0;
    }

    if (priority > 0x1F || nickname == NULL || callback == NULL) {
        OSRestoreInterrupts(level);
        return 0;
    }

    usbapUseNickname = useNickname;
    usbapCallback = callback;
    memcpy(usbapNickname, nickname, USBAP_NICKNAME_LEN);

    OSInitMessageQueue(&usbapMessageQ, &usbapMsg, 1);

    if (OSCreateThread(&usbapThread, DoRegistration, NULL,
            usbapStack + sizeof(usbapStack), sizeof(usbapStack), priority, 1)
        == 1)
    {
        OSRestoreInterrupts(level);
        while (OSResumeThread(&usbapThread) > 1) {
        }
        return 1;
    }

    OSRestoreInterrupts(level);
    return 0;
}

extern "C" int USBAPCancelRegistration(void) {
    return OSSendMessage(&usbapMessageQ, NULL, 0);
}

extern "C" int USBAPIsThreadTerminated(void) {
    return OSIsThreadTerminated(&usbapThread);
}

extern "C" void* DoRegistration(void* param) {
    OSMessage msg;
    WDScanParam req;
    s32 ret;
    s32 result;
    BOOL found;
    BOOL empty;
    u16 count;
    s32 i;
    s32 j;
    s32 joff;
    WDBssDesc* entry;

    if (WDCheckEnableChannel(&usbapEnableChannel) != 0) {
        ret = 0;
        if (usbapCallback != NULL) {
            usbapCallback(0);
        }
    }
    else {
        for (;;) {
            OSYieldThread();

            if (OSReceiveMessage(&usbapMessageQ, &msg, 0) == TRUE) {
                ret = 0;
                if (usbapCallback != NULL) {
                    usbapCallback(0);
                }
                break;
            }

            result = 0;

            req.channelBit = usbapEnableChannel;
            req.maxChannelTime = 0x64;
            memset(req.bssid, 0xFF, WD_BSSID_LENGTH);
            req.type = 0;
            req.ssidLength = 0x20;
            memcpy(req.ssid, USBAP_SSID, USBAP_SSID_LENGTH);
            req.ssid[8] = 0;
            req.ssid[9] = 1;

            if (usbapUseNickname == 1) {
                req.ssid[9] |= 2;
            }
            req.ssid[10] = 1;
            req.ssid[11] = 0;
            memcpy(&req.ssid[12], usbapNickname, USBAP_NICKNAME_LEN);

            memset(&req.ssidMask[0], 0, 8);
            memset(&req.ssidMask[8], 0xFF, 0x18);

            if (WDScanOnce(usbapScanBuffer, 0x800, &req) == 0) {
                found = 0;
                empty = 0;
                count = *(u16*)usbapScanBuffer;
                entry = (WDBssDesc*)(usbapScanBuffer + 2);

                for (i = 0; i < count; i++) {
                    if (entry->ssidLength == 0x20
                        && strncmp((char*)entry->ssid, USBAP_SSID,
                                USBAP_SSID_LENGTH)
                            == 0)
                    {
                        for (j = 0, joff = 0; j < USBAP_MAC_TABLE_MAX;
                            j++, joff += USBAP_MAC_LENGTH)
                        {
                            if (memcmp(entry->bssid,
                                    &usbapMacTable[1 + joff],
                                    USBAP_MAC_LENGTH)
                                == 0)
                            {
                                break;
                            }
                        }

                        if (j == USBAP_MAC_TABLE_MAX) {
                            if (entry->ssid[9] == 1) {
                                memcpy(&usbapMacTable[1 + usbapMacTable[0]
                                        * USBAP_MAC_LENGTH],
                                    entry->bssid, USBAP_MAC_LENGTH);
                                usbapMacTable[0]++;
                                found = 1;
                            }
                            else if (entry->ssid[9] == 0) {
                                empty = 1;
                            }
                        }
                    }

                    entry = (WDBssDesc*)((u8*)entry + entry->length * 2);
                }

                if (found) {
                    result = empty ? 2 : 1;
                }
            }

            if (result != 0) {
                ret = result == 1;
                if (usbapCallback != NULL) {
                    usbapCallback(ret);
                }
                break;
            }
        }
    }

    return (void*)(u32)ret;
}
