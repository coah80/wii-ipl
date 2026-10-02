#include <revolution/os.h>
#include <revolution/ncd.h>
#include <private/wd.h>
#include <string.h>

s32 AOSSi_cancel_flag = 0;
static u8 ipAddress[4] = {0};
static u8 ipNetmask[4] = {0};
static u8 ipGateway[4] = {0};
static u8 primaryDns[4] = {0};
static u8 secondaryDns[4] = {0};
static void* (*allocateMemory)(u32, s32) = NULL;
static void (*releaseMemory)(u32, void*, s32) = NULL;
static void (*statusCallback)(void) = NULL;
static NCDIfConfig AOSSi_NcdIfConfig;
static NCDIpConfig AOSSi_NcdIpConfig;

struct AOSSRate {
    u16 mask;
    u8 value;
    u8 reserved;
};
static struct AOSSRate supportedRates[] = {
    {1, 2, 0}, {2, 4, 0}, {4, 11, 0}, {8, 12, 0},
    {16, 18, 0}, {32, 22, 0}, {64, 24, 0}, {128, 36, 0},
    {256, 48, 0}, {512, 72, 0}, {1024, 96, 0}, {2048, 108, 0}
};
struct AOSSAccessPoint {
    u32 ssidLength;
    u8 ssid[32];
    u32 channel;
    u32 signal;
    u32 privacy;
    u8 bssid[6];
    u16 capabilities;
    u32 rateCount;
    u8 rates[12];
    u32 beaconPeriod;
    u32 mode;
};
struct AOSSAccessPointList {
    u32 count;
    struct AOSSAccessPoint accessPoints[1];
};
struct AOSSConnection {
    u32 ssidLength;
    u8 ssid[32];
    u32 security;
    u32 keyLength;
    u8 key[64];
};
struct AOSSConnectionStatus {
    u32 connected;
    u32 ssidLength;
    u8 ssid[32];
    u32 channel;
};

void AOSSi_Cancel(void) {
    AOSSi_cancel_flag = 1;
}

void AOSSi_SleepAlarmHandler(OSAlarm* alarm, OSContext* context) {
    OSSendMessage((OSMessageQueue*)alarm->tag, NULL, 0);
}

void AOSSi_SleepMs(u32 milliseconds) {
    OSMessage storage;
    OSMessage message;
    OSMessageQueue queue;
    OSAlarm alarm;
    OSInitMessageQueue(&queue, &storage, 1);
    OSCreateAlarm(&alarm);
    OSSetAlarmTag(&alarm, (u32)&queue);
    OSSetAlarm(&alarm, (u32)(milliseconds * (OS_TIMER_CLOCK / 1000)), AOSSi_SleepAlarmHandler);
    OSReceiveMessage(&queue, &message, 1);
}

void* AOSSi_Alloc(u32 size) {
    if (allocateMemory != NULL) {
        return allocateMemory(0, size);
    }
    return NULL;
}

void AOSSi_Free(void* block) {
    if (releaseMemory != NULL) {
        releaseMemory(0, block, 0);
    }
}

void AOSSi_StoreIpv4Octets(u8* destination, u32 address) {
    int index;
    for (index = 0; index < 4; ++index) {
        *destination++ = address >> ((3 - index) * 8);
    }
}

int AOSSi_SetNCDIPAddr(u32 address, u32 netmask, u32 gateway, u32 dns1, u32 dns2) {
    AOSSi_StoreIpv4Octets(ipAddress, address);
    AOSSi_StoreIpv4Octets(ipNetmask, netmask);
    AOSSi_StoreIpv4Octets(ipGateway, gateway);
    AOSSi_StoreIpv4Octets(primaryDns, dns1);
    AOSSi_StoreIpv4Octets(secondaryDns, dns2);
    return 0;
}

int AOSSi_InitLocal(void* (*allocate)(u32, s32), void (*release)(u32, void*, s32)) {
    BOOL interrupts;
    if (allocate == NULL || release == NULL) {
        return -1;
    }
    interrupts = OSDisableInterrupts();
    allocateMemory = allocate;
    releaseMemory = release;
    AOSSi_cancel_flag = 0;
    OSRestoreInterrupts(interrupts);
    return 0;
}

int AOSSi_EndLocal(void) {
    BOOL interrupts = OSDisableInterrupts();
    allocateMemory = NULL;
    releaseMemory = NULL;
    OSRestoreInterrupts(interrupts);
    return 0;
}

int AOSSi_WLANGetBSSList(struct AOSSAccessPointList** output) {
    int result = -1;
    int startupRetries = 0;
    int scanRetries = 0;
    int cleanupRetries = 0;
    int unlockRetries = 0;
    int driver;
    u8* buffer;
    WD_Info info ATTRIBUTE_ALIGN(32);
    WDScanParam scan;
    u8 macAddress[6];
    if (allocateMemory == NULL || releaseMemory == NULL) {
        return -1;
    }
    driver = NCDLockWirelessDriver();
    if (driver <= 0) {
        return -1;
    }
startup:
    if (WD_Startup(3) != 0) {
        if (startupRetries > 10) {
            goto unlock;
        }
        ++startupRetries;
        AOSSi_SleepMs(10);
        goto startup;
    }
    if (WD_GetInfo(&info) == 0) {
        memcpy(macAddress, info.MAC, 6);
    }
    buffer = AOSSi_Alloc(0x3200);
    if (buffer != NULL) {
        memset(buffer, 0, 0x3200);
        scan.channelBit = info.enableChannel;
        scan.maxChannelTime = 40;
        memset(scan.bssid, 255, 6);
        scan.type = 0;
        scan.ssidLength = 0;
        memset(scan.ssid, 0, 32);
        memset(scan.ssidMask, 255, 32);
        while (1) {
            int scanResult = WD_Scan(&scan, buffer, 0x3200);
            int count;
            struct AOSSAccessPointList* list;
            WDBssDesc* descriptor;
            int index;
            if (scanResult != 0 && scanResult != WD_INTERNAL_ERR_4) {
                break;
            }
            count = *(u16*)buffer;
            if (count != 0) {
                list = AOSSi_Alloc(sizeof(*list) + (count - 1) * sizeof(struct AOSSAccessPoint));
                if (list == NULL) {
                    result = -1;
                    break;
                }
                list->count = count;
                descriptor = (WDBssDesc*)&buffer[2];
                for (index = 0; index < count; ++index) {
                    struct AOSSAccessPoint* accessPoint = &list->accessPoints[index];
                    int rate;
                    int rateCount = 0;
                    accessPoint->ssidLength = descriptor->ssidLength;
                    memcpy(accessPoint->ssid, descriptor->ssid, 32);
                    accessPoint->channel = descriptor->channel;
                    memcpy(accessPoint->bssid, descriptor->bssid, 6);
                    for (rate = 0; rate < 12; ++rate) {
                        if (descriptor->rateSet.support & supportedRates[rate].mask) {
                            accessPoint->rates[rateCount] = supportedRates[rate].value;
                            if (descriptor->rateSet.basic & supportedRates[rate].mask) {
                                accessPoint->rates[rateCount] |= 128;
                            }
                            ++rateCount;
                        }
                    }
                    accessPoint->rateCount = rateCount;
                    accessPoint->beaconPeriod = descriptor->beaconPeriod;
                    if ((descriptor->capabilities & 3) == 1) {
                        accessPoint->mode = 1;
                    } else if ((descriptor->capabilities & 3) == 2) {
                        accessPoint->mode = 2;
                    } else {
                        accessPoint->mode = 0;
                    }
                    descriptor = (WDBssDesc*)((u16*)descriptor + descriptor->length);
                }
                *output = list;
                result = 0;
                break;
            }
            if (AOSSi_cancel_flag == 1) {
                result = -1;
                break;
            }
            if (++scanRetries > 10) {
                list = AOSSi_Alloc(sizeof(*list));
                if (list == NULL) {
                    result = -1;
                    break;
                }
                list->count = 0;
                result = 0;
                *output = list;
                break;
            }
            AOSSi_SleepMs(100);
        }
        AOSSi_Free(buffer);
    }
cleanup:
    if (WD_Cleanup() != 0) {
        if (cleanupRetries > 10) {
            result = -1;
            goto unlock;
        }
        ++cleanupRetries;
        AOSSi_SleepMs(10);
        goto cleanup;
    }
unlock:
    if (NCDUnlockWirelessDriver(driver) != 0) {
        if (unlockRetries > 10) {
            result = -1;
            return -1;
        }
        ++unlockRetries;
        AOSSi_SleepMs(10);
        goto unlock;
    }
    return result;
}

int AOSSi_WLANConnect(struct AOSSConnection* connection, struct AOSSConnectionStatus* status) {
    int retries = 0;
    int result = 0;
    WD_Info info ATTRIBUTE_ALIGN(32);
    NCDIfConfig* interfaceConfig = &AOSSi_NcdIfConfig;
    NCDIpConfig* ipConfig;
    memset(interfaceConfig, 0, sizeof(*interfaceConfig));
    interfaceConfig->selectedMedia = 1;
    interfaceConfig->netif.wireless.rateset = 0;
    interfaceConfig->netif.wireless.configMethod = 0;
    if (connection->keyLength == 0) {
        interfaceConfig->netif.wireless.config.manual.privacy.mode = 0;
    }
    if (connection->keyLength == 5) {
        interfaceConfig->netif.wireless.config.manual.privacy.mode = 1;
        interfaceConfig->netif.wireless.config.manual.privacy.wep40.keyId = 0;
        memcpy(interfaceConfig->netif.wireless.config.manual.privacy.wep40.key,
               connection->key, connection->keyLength);
    } else if (connection->keyLength == 13) {
        interfaceConfig->netif.wireless.config.manual.privacy.mode = 2;
        interfaceConfig->netif.wireless.config.manual.privacy.wep104.keyId = 0;
        memcpy(interfaceConfig->netif.wireless.config.manual.privacy.wep104.key,
               connection->key, connection->keyLength);
    } else if (connection->keyLength == 16) {
        return -1;
    } else {
        return -1;
    }
    interfaceConfig->netif.wireless.config.manual.ssidLength = (u8)connection->ssidLength;
    memcpy(interfaceConfig->netif.wireless.config.manual.ssid, connection->ssid, connection->ssidLength);
    ipConfig = &AOSSi_NcdIpConfig;
    memset(ipConfig, 0, sizeof(*ipConfig));
    ipConfig->adjust.maxTransferUnit = 1300;
    ipConfig->adjust.tcpRetransTimeout = 100;
    ipConfig->adjust.dhcpRetransCount = 4;
    ipConfig->useDhcp = 0;
    ipConfig->useProxy = 0;
    memcpy(ipConfig->ip.addr, ipAddress, 4);
    memcpy(ipConfig->ip.netmask, ipNetmask, 4);
    memcpy(ipConfig->ip.gateway, ipGateway, 4);
    memcpy(ipConfig->ip.dns1, primaryDns, 4);
    memcpy(ipConfig->ip.dns2, secondaryDns, 4);
    if (NCDSetIpConfig(ipConfig) != 0) {
        result = -1;
    }
    if (result == 0 && NCDSetIfConfig(&AOSSi_NcdIfConfig) != 0) {
        result = -1;
    }
    if (result == 0) {
        while (!NCDIsInterfaceDecided()) {
            if (AOSSi_cancel_flag == 1) {
                result = -1;
                break;
            }
            if (retries > 600) {
                result = -1;
                break;
            }
            ++retries;
            AOSSi_SleepMs(10);
        }
    }
    if (result == 0) {
        status->connected = 1;
        if (WD_GetInfo(&info) == 0) {
            status->channel = info.channel;
        }
        status->ssidLength = interfaceConfig->netif.wireless.config.manual.ssidLength;
        memcpy(status->ssid, interfaceConfig->netif.wireless.config.manual.ssid,
               interfaceConfig->netif.wireless.config.manual.ssidLength);
    } else {
        status->connected = 0;
    }
    return result;
}

void AOSSi_Sleep(u32 milliseconds) {
    AOSSi_SleepMs(milliseconds);
}

int AOSSi_Status(void) {
    if (statusCallback != NULL) {
        statusCallback();
    }
    return 0;
}

void AOSS_SetCallback(void (*callback)(void)) {
    BOOL interrupts = OSDisableInterrupts();
    statusCallback = callback;
    OSRestoreInterrupts(interrupts);
}
