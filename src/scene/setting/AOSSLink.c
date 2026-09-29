#include <string.h>

#include <revolution/types.h>
#include <revolution/os.h>
#include <revolution/soex.h>

void OSSetAlarm();

s32 NCDLockWirelessDriver(void);
s32 NCDUnlockWirelessDriver(s32 id);
s32 NCDSetIpConfig(void* ipConfig);
s32 NCDSetIfConfig(void* ifConfig);
BOOL NCDIsInterfaceDecided(void);

s32 WD_Startup(u32 flags);
s32 WD_Cleanup(void);
s32 WD_Scan(void* params, u8* buffer, u32 bufferLen);
s32 WD_GetInfo(void* info);

static u8 sConf[352];
static u8 sIpConfig[1992];

static void (*AOSSi_callback)(void);
static void (*AOSSi_free)(u32 id, void* ptr, s32 size);
static void* (*AOSSi_alloc)(u32 id, s32 size);
static u32 AOSSi_dns2;
static u32 AOSSi_dns1;
static u32 AOSSi_gateway;
static u32 AOSSi_netmask;
static u32 AOSSi_ipAddr;
static s32 AOSSi_cancel_flag;

static u16 sRateTable[12][2] = {
    {0x0001, 0x0200}, {0x0002, 0x0400}, {0x0004, 0x0B00},
    {0x0008, 0x0C00}, {0x0010, 0x1200}, {0x0020, 0x1600},
    {0x0040, 0x1800}, {0x0080, 0x2400}, {0x0100, 0x3000},
    {0x0200, 0x4800}, {0x0400, 0x6000}, {0x0800, 0x6C00},
};

void AOSSi_Cancel(void) {
    AOSSi_cancel_flag = 1;
}

static void AOSS_813FD17C(OSAlarm* alarm, OSContext* context) {
    OSSendMessage((OSMessageQueue*)alarm->tag, NULL, FALSE);
}

static void AOSS_813FD18C(u32 ms) {
    OSMessage queueBuffer;
    OSMessage message;
    OSMessageQueue queue;
    OSAlarm alarm;

    OSInitMessageQueue(&queue, &queueBuffer, 1);
    OSCreateAlarm(&alarm);
    OSSetAlarmTag(&alarm, (u32)&queue);
    OSSetAlarm(&alarm, *(u32*)0x800000F8 >> 2, 0, ms * (OS_TIMER_CLOCK / 1000), AOSS_813FD17C);
    OSReceiveMessage(&queue, &message, TRUE);
}

typedef struct WD_Info_ {
    u8 MAC[6];
    u16 enableChannel;
    u16 NTRallowedChannel;
    u8 countryCode[4];
    u8 channel;
    u8 initialized;
    u8 version[80];
    u8 unk_0x60[0x30];
} WD_Info;

typedef struct WDScanParam_ {
    u16 channelBit;
    u16 maxChannelTime;
    u8 bssid[6];
    u16 type;
    u16 ssidLength;
    u8 ssid[32];
    u8 ssidMask[32];
} WDScanParam;

typedef struct WDBssDesc_ {
    u16 length;
    u16 rssi;
    u8 bssid[6];
    u16 ssidLength;
    u8 ssid[32];
    u16 capabilities;
    struct {
        u16 basic;
        u16 support;
    } rateSet;
    u16 beaconPeriod;
    u16 dtimPeriod;
    u16 channel;
    u16 cfPeriod;
    u16 cfMaxDuration;
    u16 ieLength;
} WDBssDesc;

void* AOSSi_Alloc(s32 size) {
    if (AOSSi_alloc != NULL) {
        return AOSSi_alloc(0, size);
    }
    return NULL;
}

void AOSSi_Free(void* ptr) {
    if (AOSSi_free != NULL) {
        AOSSi_free(0, ptr, 0);
    }
}

static void AOSS_813FD25C(u8* dst, u32 val) {
    int i;
    for (i = 0; i < 4; i++) {
        dst[i] = val >> ((3 - i) * 8);
    }
}

s32 AOSSi_SetNCDIPAddr(u32 ip, u32 mask, u32 gateway, u32 dns1, u32 dns2) {
    AOSS_813FD25C((u8*)&AOSSi_ipAddr, ip);
    AOSS_813FD25C((u8*)&AOSSi_netmask, mask);
    AOSS_813FD25C((u8*)&AOSSi_gateway, gateway);
    AOSS_813FD25C((u8*)&AOSSi_dns1, dns1);
    AOSS_813FD25C((u8*)&AOSSi_dns2, dns2);
    return 0;
}

s32 AOSSi_InitLocal(void* (*alloc)(u32 id, s32 size),
                    void (*free_)(u32 id, void* ptr, s32 size)) {
    BOOL level;

    if (alloc == NULL || free_ == NULL) {
        return -1;
    }

    level = OSDisableInterrupts();
    AOSSi_alloc = alloc;
    AOSSi_free = free_;
    AOSSi_cancel_flag = 0;
    OSRestoreInterrupts(level);
    return 0;
}

s32 AOSSi_EndLocal(void) {
    BOOL level;

    level = OSDisableInterrupts();
    AOSSi_alloc = NULL;
    AOSSi_free = NULL;
    OSRestoreInterrupts(level);
    return 0;
}

s32 AOSSi_WLANGetBSSList(u32** out) {
    u8 mac[6];
    WDScanParam ATTRIBUTE_ALIGN(32) req;
    WD_Info ATTRIBUTE_ALIGN(32) info;
    u8* buf;
    u32* list;
    u8* src;
    u8* dst;
    int count;
    int i;
    int j;
    int n;
    s32 result = -1;
    int retry = 0;
    int uretry = 0;
    int cretry = 0;
    int rescan = 0;
    s32 lock;
    s32 err;

    if (AOSSi_alloc == 0 || AOSSi_free == 0) {
        return -1;
    }

    lock = NCDLockWirelessDriver();
    if (lock <= 0) {
        return -1;
    }

    for (;;) {
        if (WD_Startup(3) == 0) {
            break;
        }
        if (retry > 10) {
            goto unlock;
        }
        retry++;
        AOSS_813FD18C(10);
    }

    if (WD_GetInfo(&info) == 0) {
        memcpy(mac, info.MAC, 6);
    }

    buf = AOSSi_Alloc(0x3200);
    if (buf == 0) {
        goto cleanup;
    }
    memset(buf, 0, 0x3200);

    req.channelBit = info.enableChannel;
    req.maxChannelTime = 0x28;
    memset(req.bssid, 0xFF, 6);
    req.type = 0;
    req.ssidLength = 0;
    memset(req.ssid, 0, 0x20);
    memset(req.ssidMask, 0xFF, 0x20);

    for (;;) {
        err = WD_Scan(&req, buf, 0x3200);
        if (err != 0 && (u32)(err - 0x80000000) != 0x8004) {
            goto free;
        }

        count = *(u16*)buf;
        if (count == 0) {
            if (AOSSi_cancel_flag == 1) {
                result = -1;
                goto free;
            }
            rescan++;
            if (rescan > 10) {
                list = AOSSi_Alloc(0x58);
                if (list == NULL) {
                    result = -1;
                    goto free;
                }
                list[0] = 0;
                result = 0;
                *out = list;
                goto free;
            }
            AOSS_813FD18C(100);
            continue;
        }
        break;
    }

    list = AOSSi_Alloc((count - 1) * 0x54 + 0x58);
    if (list == NULL) {
        result = -1;
        goto free;
    }
    list[0] = count;

    src = buf + 2;
    dst = (u8*)list;
    for (i = 0; i < count; i++) {
        u32 off = i * 0x54;
        *(u32*)(dst + off + 4) = ((WDBssDesc*)src)->ssidLength;
        memcpy(dst + off + 8, ((WDBssDesc*)src)->ssid, 0x20);
        *(u32*)(dst + off + 0x28) = ((WDBssDesc*)src)->channel;
        memcpy(dst + off + 0x34, ((WDBssDesc*)src)->bssid, 6);

        n = 0;
        for (j = 0; j < 12; j++) {
            if (((WDBssDesc*)src)->rateSet.support & sRateTable[j][0]) {
                dst[off + 0x40 + n] = ((u8*)sRateTable)[j * 4 + 2];
                if (((WDBssDesc*)src)->rateSet.basic & sRateTable[j][0]) {
                    dst[off + 0x40 + n] |= 0x80;
                }
                n++;
            }
        }
        *(u32*)(dst + off + 0x3C) = n;

        *(u32*)(dst + off + 0x50) = ((WDBssDesc*)src)->beaconPeriod;
        if ((((WDBssDesc*)src)->capabilities & 3) == 1) {
            *(u32*)(dst + off + 0x54) = 1;
        }
        else if ((((WDBssDesc*)src)->capabilities & 3) == 2) {
            *(u32*)(dst + off + 0x54) = 2;
        }
        else {
            *(u32*)(dst + off + 0x54) = 0;
        }

        src += ((WDBssDesc*)src)->length * 2;
    }

    *out = list;
    result = 0;

free:
    if (AOSSi_free != NULL) {
        AOSSi_free(0, buf, 0);
    }

cleanup:
    for (;;) {
        if (WD_Cleanup() == 0) {
            break;
        }
        if (cretry > 10) {
            result = -1;
            break;
        }
        cretry++;
        AOSS_813FD18C(10);
    }

unlock:
    for (;;) {
        if (NCDUnlockWirelessDriver(lock) == 0) {
            break;
        }
        if (uretry > 10) {
            result = -1;
            break;
        }
        uretry++;
        AOSS_813FD18C(10);
    }

    return result;
}

s32 AOSSi_WLANConnect(u32* in, u32* out) {
    WD_Info ATTRIBUTE_ALIGN(32) info;
    int count = 0;
    int ret;
    u8* conf = sConf;
    u8* ipcfg;

    memset(conf, 0, 0x15E);
    conf[0] = 1;
    *(u16*)(conf + 2) = 0;
    conf[4] = 0;

    if (in[0x28 / 4] == 0) {
        *(u16*)(conf + 0x2A) = 0;
    }
    if (in[0x28 / 4] == 5) {
        *(u16*)(conf + 0x2A) = 1;
        *(u16*)(conf + 0x2E) = 0;
        memcpy(conf + 0x32, (u8*)in + 0x2C, in[0x28 / 4]);
    }
    else if (in[0x28 / 4] == 0xD) {
        *(u16*)(conf + 0x2A) = 2;
        *(u16*)(conf + 0x2E) = 0;
        memcpy(conf + 0x32, (u8*)in + 0x2C, in[0x28 / 4]);
    }
    else if (in[0x28 / 4] == 0x10) {
        return -1;
    }
    else {
        return -1;
    }

    *(u16*)(conf + 0x26) = in[0] & 0xFF;
    memcpy(conf + 6, (u8*)in + 4, in[0]);

    ipcfg = sIpConfig;
    ret = 0;
    memset(ipcfg, 0, 0x7C4);
    *(u32*)(ipcfg + 0x1C) = 0x514;
    *(u32*)(ipcfg + 0x20) = 0x64;
    *(u32*)(ipcfg + 0x24) = 4;
    *(u32*)(ipcfg + 0) = 0;
    *(u32*)(ipcfg + 4) = 0;
    memcpy(ipcfg + 8, &AOSSi_ipAddr, 4);
    memcpy(ipcfg + 0xC, &AOSSi_netmask, 4);
    memcpy(ipcfg + 0x10, &AOSSi_gateway, 4);
    memcpy(ipcfg + 0x14, &AOSSi_dns1, 4);
    memcpy(ipcfg + 0x18, &AOSSi_dns2, 4);

    if (NCDSetIpConfig(sIpConfig) != 0) {
        ret = -1;
    }
    if (ret == 0 && NCDSetIfConfig(sConf) != 0) {
        ret = -1;
    }

    if (ret == 0) {
        while (!NCDIsInterfaceDecided()) {
            if (AOSSi_cancel_flag == 1) {
                ret = -1;
                break;
            }
            if (count > 0x258) {
                ret = -1;
                break;
            }
            count++;
            AOSS_813FD18C(10);
        }
    }

    if (ret == 0) {
        out[0] = 1;
        if (WD_GetInfo(&info) == 0) {
            out[0x28 / 4] = info.channel;
        }
        {
            u32 len = *(u16*)(conf + 0x26);
            out[4 / 4] = len;
            memcpy((u8*)out + 8, conf + 6, len);
        }
    }
    else {
        out[0] = 0;
    }

    return ret;
}

void AOSSi_Sleep(u32 ms) {
    AOSS_813FD18C(ms);
}

s32 AOSSi_Status(void) {
    if (AOSSi_callback != NULL) {
        AOSSi_callback();
    }
    return 0;
}

void AOSS_SetCallback(void (*callback)(void)) {
    BOOL level;

    level = OSDisableInterrupts();
    AOSSi_callback = callback;
    OSRestoreInterrupts(level);
}
