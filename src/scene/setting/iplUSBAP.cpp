#include <revolution/os.h>
#include <revolution/wd.h>
#include <string.h>

static OSThread usbapThread;
static u8 usbapStack[4096];
static OSMessageQueue usbapMessageQ;
static wchar_t usbapNickname[12];
static OSMessage registrationMessage;
static void (*registrationCallback)(int);
static s32 registrationMode;
static u16 enabledChannels;
static u8* scanBuffer;
// Registration buffer: a count byte followed by twenty MAC addresses.
static u8* registeredAccessPoints;

static inline int FindRegisteredAddress(const u8* registered, const u8* address) {
    int index;
    for (index = 0; index < 20; ++index) {
        if (memcmp(address, &registered[index * WD_BSSID_LENGTH + 1], WD_BSSID_LENGTH) == 0) break;
    }
    return index;
}

extern "C" {
static void* DoRegistration(void*);
}

extern "C" BOOL USBAPStartRegistration(void*, void*, u32 priority, u32 mode,
                                      void* nickname, void (*callback)(int),
                                      u16* buffer, u8* accessPoints) {
    BOOL interrupts = OSDisableInterrupts();
    scanBuffer = (u8*)buffer;
    registeredAccessPoints = accessPoints;
    if (usbapThread.state != 0 && !OSIsThreadTerminated(&usbapThread)) {
        OSRestoreInterrupts(interrupts);
        return FALSE;
    }
    if (priority > 31 || nickname == NULL || callback == NULL) {
        OSRestoreInterrupts(interrupts);
        return FALSE;
    }
    registrationMode = mode;
    registrationCallback = callback;
    memcpy(usbapNickname, nickname, 20);
    OSInitMessageQueue(&usbapMessageQ, &registrationMessage, 1);
    if (OSCreateThread(&usbapThread, DoRegistration, NULL, usbapStack + sizeof(usbapStack),
                       sizeof(usbapStack), priority, OS_THREAD_ATTR_DETACH) == TRUE) {
        OSRestoreInterrupts(interrupts);
        while (OSResumeThread(&usbapThread) > 1) {
        }
        return TRUE;
    }
    OSRestoreInterrupts(interrupts);
    return FALSE;
}

extern "C" BOOL USBAPCancelRegistration() {
    return OSSendMessage(&usbapMessageQ, NULL, 0);
}

extern "C" BOOL USBAPIsThreadTerminated() {
    return OSIsThreadTerminated(&usbapThread);
}

struct USBAPSSID {
    u8 prefix[8];
    u8 reserved;
    u8 flags;
    u8 version;
    u8 status;
    wchar_t nickname[10];
};

struct USBAPScan {
    u16 channelBit;
    u16 maxChannelTime;
    u8 bssid[6];
    u16 type;
    u16 ssidLength;
    USBAPSSID ssid;
    u8 ssidMask[32];
};

static void* DoRegistration(void*) {
    int failed, found, index;
    s32 count;
    WDBssDesc* accessPoint;
    int result;
    int address;
    const u8* registered;
    BOOL success;
    if (WDCheckEnableChannel(&enabledChannels) != 0) {
        success = FALSE;
        if (registrationCallback != NULL) {
            registrationCallback(FALSE);
        }
        goto complete;
    }
    do {
        OSMessage message;
        OSYieldThread();
        if (OSReceiveMessage(&usbapMessageQ, &message, 0) == TRUE) {
            success = FALSE;
            if (registrationCallback != NULL) {
                registrationCallback(FALSE);
            }
            goto complete;
        }
        USBAPScan scan;
        scan.channelBit = enabledChannels;
        scan.maxChannelTime = 100;
        result = 0;
        memset(scan.bssid, 255, 6);
        scan.type = 0;
        scan.ssidLength = 32;
        memcpy(scan.ssid.prefix, "NWCUSBAP", 8);
        scan.ssid.reserved = 0;
        scan.ssid.flags = 1;
        if (registrationMode == 1) {
            scan.ssid.flags |= 2;
        }
        scan.ssid.version = 1;
        scan.ssid.status = 0;
        memcpy(scan.ssid.nickname, usbapNickname, 20);
        memset(scan.ssidMask, 0, 8);
        memset(&scan.ssidMask[8], 255, 24);
        if (WDScanOnce(scanBuffer, 2048, (WDScanParam*)&scan) == 0) {
            count = *(u16*)scanBuffer;
            accessPoint = (WDBssDesc*)&scanBuffer[2];
            found = 0;
            failed = 0;
            for (index = 0; index < count; ++index) {
                if (accessPoint->ssidLength == 32 && strncmp((char*)accessPoint->ssid, "NWCUSBAP", 8) == 0) {
                    registered = registeredAccessPoints;
                    address = FindRegisteredAddress(registered, accessPoint->bssid);
                    if (address == 20) {
                        USBAPSSID* response = (USBAPSSID*)accessPoint->ssid;
                        if (response->flags == 1) {
                            memcpy(&registeredAccessPoints[registeredAccessPoints[0] * WD_BSSID_LENGTH + 1], accessPoint->bssid, WD_BSSID_LENGTH);
                            found = 1;
                            ++registeredAccessPoints[0];
                        } else if (response->flags == 0) {
                            failed = 1;
                        }
                    }
                }
                accessPoint = (WDBssDesc*)((u16*)accessPoint + accessPoint->length);
            }
            if (found) {
                result = (failed != 0) + 1;
            }
        }
    } while (result == 0);
    success = result == 1;
    if (registrationCallback != NULL) {
        registrationCallback(success);
    }
complete:
    return (void*)success;
}
