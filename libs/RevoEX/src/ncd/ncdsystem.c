#include <private/ipc.h>
#include <private/ios.h>
#include <private/nwc24/NWC24Schedule.h>
#include <revolution/ncd.h>
#include <revolution/os.h>

#include <string.h>

#define NCD_IPC_HEAP_SIZE 0x1B60
#define NCD_MAX_PROFILE 3

static u32 ncdInitialized;
static NCDConfig* ncdCommonBuffer;

struct NCDMutex {
    OSMutex mutex;
    u8 padding[8];
} ncdMutex;
s32 ncdCommonResult[8] ATTRIBUTE_ALIGN(32);
IOSIoVector ncdCommonVector[4] ATTRIBUTE_ALIGN(32);

const char* __NCDVersion = "<< RVL_SDK - NCD \trelease build: Dec 12 2008 03:06:03 (0x4199_60831) >>";
const char* __NCDUnofficialVersion = "<< RVL_SDK - NCD \trelease build: Dec 12 2008 03:06:03 (0x4199_60831) UNOFFICIAL >>";

static void LockRight(void);
static NCDErr ExecConfigCommand(const char* name, NCDConfig* config, u32 command);
NCDErr NCDiGetWirelessMacAddress(u8* macAddr);

NCDErr NCDReadConfig(NCDConfig* config) {
    if (config == NULL) {
        return -3;
    }

    return ExecConfigCommand("NCDReadConfig", config, 5);
}

NCDErr NCDWriteConfig(const NCDConfig* config) {
    BOOL enabled;

    enabled = OSDisableInterrupts();
    if (!(ncdInitialized & 2)) {
        OSRegisterVersion(__NCDUnofficialVersion);
        ncdInitialized |= 2;
    }
    OSRestoreInterrupts(enabled);

    if (config == NULL) {
        return -3;
    }

    return ExecConfigCommand("NCDWriteConfig", (NCDConfig*)config, 6);
}

NCDErr NCDSetIfConfig(NCDIfConfig* ifConfig) {
    union {
        BOOL enabled;
        NCDConfig* config;
    } state;
    NCDErr lockErr;
    NCDProfile* profile;
    NCDErr result;
    s32 i;
    u32 count;

    state.enabled = OSDisableInterrupts();
    if (!(ncdInitialized & 2)) {
        OSRegisterVersion(__NCDUnofficialVersion);
        ncdInitialized |= 2;
    }
    OSRestoreInterrupts(state.enabled);


    if (ifConfig == NULL) {
        return -3;
    }
    if (!OSGetCurrentThread()) {
        return -5;
    }

    LockRight();
    lockErr = NWC24iLockSocket();
    if (lockErr == 0) {
        result = ExecConfigCommand("NCDSetIfConfig", NULL, 3);
        if (result == 0) {
            state.config = ncdCommonBuffer;

            if (ifConfig->selectedMedia != 1 && ifConfig->selectedMedia != 2) {
                state.config->selectedMedia = 0;
            } else {
                state.config->selectedMedia = ifConfig->selectedMedia;
                profile = state.config->profiles;
                i = 0;
                state.config->linkTimeout = ifConfig->linkTimeout;
                count = 0;
                for (; i < NCD_MAX_PROFILE; i++, profile++) {
                    if (state.config->profiles[i].flags & 0x80) {
                        switch (ifConfig->selectedMedia) {
                        case 1:
                            state.config->profiles[i].flags &= ~1;
                            memcpy(&profile->netif, &ifConfig->netif, 0x15c);
                            break;
                        case 2:
                            state.config->profiles[i].flags |= 1;
                            memcpy(&profile->netif, &ifConfig->netif, 4);
                            break;
                        }
                        count++;
                    }
                }

                if (count == 0) {
                    state.config->profiles[0].flags |= 0x80;
                    switch (ifConfig->selectedMedia) {
                    case 1:
                        state.config->profiles[0].flags &= ~1;
                        memcpy(&state.config->profiles[0].netif.wireless, &ifConfig->netif, 0x15c);
                        break;
                    case 2:
                        state.config->profiles[0].flags |= 1;
                        memcpy(&state.config->profiles[0].netif.wired, &ifConfig->netif, 4);
                        break;
                    }
                    memset(&state.config->profiles[0].adjust, 0, 0xc);
                    state.config->profiles[0].flags |= 6;
                    memset(&state.config->profiles[0].ip, 0, 0x14);
                    state.config->profiles[0].flags &= ~0x10;
                    memset(&state.config->profiles[0].proxy, 0, 0x79c);
                }
            }
            result = ExecConfigCommand("NCDSetIfConfig", NULL, 4);
        }
        NWC24iUnlockSocket();
    } else if (lockErr == -0x16) {
        result = -4;
    } else if (lockErr == -0x1d) {
        result = -8;
    } else {
        result = -2;
    }
    OSUnlockMutex((OSMutex*)&ncdMutex);
    return result;
}

NCDErr NCDSetIpConfig(NCDIpConfig* ipConfig) {
    NCDErr err;
    BOOL enabled;
    s32 i;
    u32 count;
    NCDConfig* config;

    enabled = OSDisableInterrupts();
    if (!(ncdInitialized & 2)) {
        OSRegisterVersion(__NCDUnofficialVersion);
        ncdInitialized |= 2;
    }
    OSRestoreInterrupts(enabled);

    if (ipConfig == NULL) {
        return -3;
    }
    if (!OSGetCurrentThread()) {
        return -5;
    }

    LockRight();
    err = NWC24iLockSocket();
    if (err == 0) {
        err = ExecConfigCommand("NCDSetIpConfig", NULL, 3);
        if (err == 0) {
            i = 0;
            count = 0;
            config = ncdCommonBuffer;
            for (; i < NCD_MAX_PROFILE; i++) {
                if (config->profiles[i].flags & 0x80) {
                    NCDProfile* profile = &config->profiles[i];

                    memcpy(&profile->adjust, &ipConfig->adjust, 0xc);
                    if (ipConfig->useDhcp == 1) {
                        config->profiles[i].flags |= 6;
                        memcpy(&profile->ip, &ipConfig->ip, 0x14);
                    } else {
                        config->profiles[i].flags &= ~6;
                        memcpy(&profile->ip, &ipConfig->ip, 0x14);
                    }
                    if (ipConfig->useProxy == 1) {
                        config->profiles[i].flags |= 0x10;
                        memcpy(&profile->proxy, &ipConfig->proxy, 0x79c);
                    } else {
                        config->profiles[i].flags &= ~0x10;
                        memset(&profile->proxy, 0, 0x79c);
                    }
                    count++;
                }
            }

            if (count == 0) {
                NCDProfile* profile = config->profiles;
                profile->flags |= 0x80;
                memcpy(&profile->adjust, &ipConfig->adjust, 0xc);
                if (ipConfig->useDhcp == 1) {
                    profile->flags |= 6;
                    memcpy(&profile->ip, &ipConfig->ip, 0x14);
                } else {
                    profile->flags &= ~6;
                    memcpy(&profile->ip, &ipConfig->ip, 0x14);
                }
                if (ipConfig->useProxy == 1) {
                    profile->flags |= 0x10;
                    memcpy(&profile->proxy, &ipConfig->proxy, 0x79c);
                } else {
                    profile->flags &= ~0x10;
                    memset(&profile->proxy, 0, 0x79c);
                }
                profile->flags = profile->flags & ~1;
                memset(&profile->netif, 0, 0x15c);
            }
            err = ExecConfigCommand("NCDSetIpConfig", NULL, 4);
        }
        NWC24iUnlockSocket();
    } else if (err == -0x16) {
        err = -4;
    } else if (err == -0x1d) {
        err = -8;
    } else {
        err = -2;
    }
    OSUnlockMutex((OSMutex*)&ncdMutex);
    return err;
}

NCDErr NCDGetCurrentIpConfig(NCDIpConfig* ipConfig) {
    NCDErr err = 0;
    NCDConfig* config;
    s32 idx;

    if (ipConfig == NULL) {
        return -3;
    }

    LockRight();
    err = ExecConfigCommand("NCDGetCurrentIpConfig", 0, 3);
    if (err == 0) {
        config = ncdCommonBuffer;
        idx = ncdCommonResult[1];

        if (idx < 0 || idx >= NCD_MAX_PROFILE) {
            err = -7;
        } else {
            memcpy(&ipConfig->adjust, &config->profiles[idx].adjust, 0xc);

            if (config->profiles[idx].flags & 0x6) {
                ipConfig->useDhcp = TRUE;
                memcpy(&ipConfig->ip, &config->profiles[idx].ip, 0x14);
            } else {
                ipConfig->useDhcp = FALSE;
                memcpy(&ipConfig->ip, &config->profiles[idx].ip, 0x14);
            }

            if (config->profiles[idx].flags & 0x10) {
                ipConfig->useProxy = TRUE;
                memcpy(&ipConfig->proxy, &config->profiles[idx].proxy, 0x79c);
            } else {
                ipConfig->useProxy = FALSE;
                memset(&ipConfig->proxy, 0, 0x79c);
            }
        }
    }

    OSUnlockMutex((OSMutex*)&ncdMutex);
    return err;
}

NCDErr NCDGetLinkStatus(void) {
    NCDErr err;
    s32 fd;

    if (!OSGetCurrentThread()) {
        return -5;
    }

    LockRight();
    fd = IOS_Open("/dev/net/ncd/manage", 0);
    if (fd < 0) {
        if (fd == -6) {
            err = -8;
        } else {
            err = -2;
        }
    } else {
        ncdCommonVector[0].base = (u8*)ncdCommonResult;
        ncdCommonVector[0].length = sizeof(ncdCommonResult);
        if (IOS_Ioctlv(fd, 7, 0, 1, ncdCommonVector) < 0) {
            err = -2;
        } else {
            err = ncdCommonResult[0];
            if (err == 0) {
                err = ncdCommonResult[1];
                err = err >= 0 ? err : -1;
            }
        }
        if (IOS_Close(fd) < 0) {
            err = -1;
        }
    }
    OSUnlockMutex((OSMutex*)&ncdMutex);
    return err;
}

BOOL NCDIsInterfaceDecided(void) {
    NCDErr err = NCDGetLinkStatus();

    switch (err) {
    case 3:
    case 4:
    case 5:
        return TRUE;
    default:
        return FALSE;
    }
}

NCDErr NCDGetWirelessMacAddress(u8* macAddr) {
    return NCDiGetWirelessMacAddress(macAddr);
}

NCDErr NCDiGetWirelessMacAddress(u8* macAddr) {
    NCDErr err = 0;
    s32 fd;

    if (macAddr == NULL) {
        return -3;
    }
    if (!OSGetCurrentThread()) {
        return -5;
    }

    LockRight();
    fd = IOS_Open("/dev/net/ncd/manage", 0);
    if (fd < 0) {
        if (fd == -6) {
            err = -8;
        } else {
            err = -2;
        }
    } else {
        ncdCommonVector[0].base = (u8*)ncdCommonResult;
        ncdCommonVector[0].length = sizeof(ncdCommonResult);
        ncdCommonVector[1].base = (u8*)ncdCommonBuffer;
        ncdCommonVector[1].length = NCD_MAC_ADDRESS_LENGTH;
        if (IOS_Ioctlv(fd, 8, 0, 2, ncdCommonVector) < 0) {
            err = -2;
        } else {
            err = ncdCommonResult[0];
            if (err == 0) {
                memcpy(macAddr, ncdCommonBuffer, NCD_MAC_ADDRESS_LENGTH);
            }
        }
        if (IOS_Close(fd) < 0) {
            err = -1;
        }
    }
    OSUnlockMutex((OSMutex*)&ncdMutex);
    return err;
}

NCDErr NCDLockWirelessDriver(void) {
    NCDErr err;
    s32 fd;

    if (!OSGetCurrentThread()) {
        return -5;
    }

    LockRight();
    fd = IOS_Open("/dev/net/ncd/manage", 0);
    if (fd < 0) {
        if (fd == -6) {
            err = -8;
        } else {
            err = -2;
        }
    } else {
        ncdCommonVector[0].base = (u8*)ncdCommonResult;
        ncdCommonVector[0].length = sizeof(ncdCommonResult);
        if (IOS_Ioctlv(fd, 1, 0, 1, ncdCommonVector) < 0) {
            err = -2;
        } else {
            err = ncdCommonResult[0];
            if (err == 0) {
                err = ncdCommonResult[1];
                err = err > 0 ? err : -1;
            }
        }
        if (IOS_Close(fd) < 0) {
            err = -1;
        }
    }
    OSUnlockMutex((OSMutex*)&ncdMutex);
    return err;
}

NCDErr NCDUnlockWirelessDriver(s32 id) {
    NCDErr err;
    s32 fd;

    if (id <= 0) {
        return -3;
    }
    if (!OSGetCurrentThread()) {
        return -5;
    }

    LockRight();
    fd = IOS_Open("/dev/net/ncd/manage", 0);
    if (fd < 0) {
        if (fd == -6) {
            err = -8;
        } else {
            err = -2;
        }
    } else {
        ncdCommonVector[0].base = (u8*)ncdCommonBuffer;
        ncdCommonVector[0].length = 4;
        ncdCommonVector[1].base = (u8*)ncdCommonResult;
        ncdCommonVector[1].length = sizeof(ncdCommonResult);
        ncdCommonBuffer->version = id;
        if (IOS_Ioctlv(fd, 2, 1, 1, ncdCommonVector) < 0) {
            err = -2;
        } else {
            err = ncdCommonResult[0];
        }
        if (IOS_Close(fd) < 0) {
            err = -1;
        }
    }
    OSUnlockMutex((OSMutex*)&ncdMutex);
    return err;
}

s32 NCDRestoreConfig(void) {
    NCDErr err;

    if (!OSGetCurrentThread()) {
        return -5;
    }

    LockRight();
    err = NWC24iLockSocket();
    if (err == 0) {
        err = ExecConfigCommand("NCDRestoreConfig", NULL, 5);
        if (err == 0) {
            err = ExecConfigCommand("NCDRestoreConfig", NULL, 4);
        }
        NWC24iUnlockSocket();
    } else if (err == -0x16) {
        err = -4;
    } else if (err == -0x1d) {
        err = -8;
    } else {
        err = -2;
    }
    OSUnlockMutex((OSMutex*)&ncdMutex);
    return err;
}

NCDErr NCDiGetEnabledConfigList(u32* list0, u32* list1, u32* list2) {
    NCDErr err;
    u32 mask0 = 0;
    u32 mask1 = 0;
    u32 mask2 = 0;
    u8 flags;
    u32 i;

    LockRight();
    err = ExecConfigCommand("NCDiGetEnabledConfigList", NULL, 3);
    if (err == 0) {
        for (i = 0; i < NCD_MAX_PROFILE; i++) {
            NCDProfile* profile = &ncdCommonBuffer->profiles[i];

            flags = profile->flags;

            if (flags & 0x80) {
                if (flags & 1) {
                    mask0 |= 1 << i;
                } else {
                    if (profile->netif.wireless.configMethod != 1) {
                        mask1 |= 1 << i;
                    }
                    if (ncdCommonBuffer->profiles[i].netif.wireless.configMethod == 1) {
                        mask2 |= 1 << i;
                    }
                }
            }
        }
    }
    OSUnlockMutex((OSMutex*)&ncdMutex);

    if (list0 != NULL) {
        *list0 = mask0;
    }
    if (list1 != NULL) {
        *list1 = mask1;
    }
    if (list2 != NULL) {
        *list2 = mask2;
    }
    return err;
}

static NCDErr ExecConfigCommand(const char* name, NCDConfig* config, u32 command) {
    NCDErr err = 0;
    s32 fd;

    if (!OSGetCurrentThread()) {
        return -5;
    }

    LockRight();
    fd = IOS_Open("/dev/net/ncd/manage", 0);
    if (fd < 0) {
        if (fd == -6) {
            err = -8;
        } else {
            err = -2;
        }
    } else {
        ncdCommonVector[0].base = (u8*)ncdCommonBuffer;
        ncdCommonVector[0].length = sizeof(NCDConfig);
        ncdCommonVector[1].base = (u8*)ncdCommonResult;
        ncdCommonVector[1].length = sizeof(ncdCommonResult);

        switch (command) {
        case 3:
        case 5:
            if (IOS_Ioctlv(fd, command, 0, 2, ncdCommonVector) < 0) {
                err = -2;
            } else {
                err = ncdCommonResult[0];
                if (err == 0 && config != NULL) {
                    memcpy(config, ncdCommonBuffer, sizeof(NCDConfig));
                }
            }
            break;
        case 4:
        case 6:
            if (config != NULL) {
                memcpy(ncdCommonBuffer, config, sizeof(NCDConfig));
            }
            if (IOS_Ioctlv(fd, command, 1, 1, ncdCommonVector) < 0) {
                err = -2;
            } else {
                err = ncdCommonResult[0];
            }
            break;
        }
        if (IOS_Close(fd) < 0) {
            err = -1;
        }
    }
    OSUnlockMutex((OSMutex*)&ncdMutex);
    return err;
}

static void LockRight(void) {
    BOOL enabled;
    void* lo;

    enabled = OSDisableInterrupts();
    if (!(ncdInitialized & 1)) {
        OSRegisterVersion(__NCDVersion);
        OSInitMutex((OSMutex*)&ncdMutex);
        lo = (void*)OSRoundUp32B(IPCGetBufferLo());
        if ((u32)IPCGetBufferHi() - (u32)lo < NCD_IPC_HEAP_SIZE) {
            OSPanic("ncdsystem.c", 0x5B1, "Could not reserve heap for NCD library from IPC arena");
        }
        IPCSetBufferLo((u8*)lo + NCD_IPC_HEAP_SIZE);
        ncdCommonBuffer = (NCDConfig*)lo;
        memset(ncdCommonBuffer, 0, NCD_IPC_HEAP_SIZE);
        memset(ncdCommonResult, 0, sizeof(ncdCommonResult));
        memset(ncdCommonVector, 0, sizeof(ncdCommonVector));
        ncdInitialized |= 1;
    }
    OSRestoreInterrupts(enabled);
    OSLockMutex((OSMutex*)&ncdMutex);
}
