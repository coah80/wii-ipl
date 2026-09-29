#include <private/nwc24.h>

#include <revolution/nwc24.h>

#include <revolution/os.h>
#include <revolution/sc.h>
#include <revolution/verdefs.h>

#include <stdlib.h>

SDKDefineVersion(NWC24, "Dec 12 2008", "03:06:06");

#define NWC24_SYSTEM_ERROR_CODE_BASE -0x900

static OSShutdownFunctionInfo ShutdownFuncInfo;
static u32 shtBuffer[8];
static u32 shtResult[8];

s32 nwc24ShtFd = -1;

static s32 nwc24ShtRetryRest;
static BOOL shuttingdown;

NWC24Err NWC24EnableLedNotification(BOOL enableLed) {
    SCIdleModeInfo idle;
    u8 led = 0;
    u32 status;

    if (enableLed != FALSE) {
        do {
            status = SCCheckStatus();
            if (status == SC_STATUS_FATAL) {
                return NWC24_ERR_FATAL;
            }
        } while (status == SC_STATUS_BUSY);

        SCGetIdleMode(&idle);
        led = idle.led;
    }

    __OSSetIdleLEDMode(led);
    return NWC24_OK;
}

NWC24Err NWC24iPrepareShutdown(void) {
    SCIdleModeInfo idle;
    NWC24Err result = NWC24_OK;
    u32 status;

    NWC24iRegister();

    ShutdownFuncInfo.func = NWC24Shutdown;
    ShutdownFuncInfo.priority = 0x6E;
    OSRegisterShutdownFunction(&ShutdownFuncInfo);

    if (nwc24ShtFd < 0) {
        result = NWC24OpenResourceManager("/dev/net/kd/request", &nwc24ShtFd, 1);
    }

    nwc24ShtRetryRest = 5;

    for (;;) {
        status = SCCheckStatus();
        if (status == SC_STATUS_FATAL) {
            break;
        }
        if (status != SC_STATUS_BUSY) {
            SCGetIdleMode(&idle);
            __OSSetIdleLEDMode(idle.led);
            break;
        }
    }

    if (OSGetAppType() == 0x40) {
        NWC24iSetScriptMode(1);
    }

    return result;
}

BOOL NWC24Shutdown(BOOL final, u32 event) {
    static long result;

    if (final != FALSE) {
        return TRUE;
    }

    if (shuttingdown != FALSE) {
        if (NWC24IsAsyncRequestPending() != FALSE) {
            return FALSE;
        }

        if (result >= 0) {
            return TRUE;
        }

        if (nwc24ShtRetryRest > 0) {
            s32 rest = nwc24ShtRetryRest - 1;
            shuttingdown = FALSE;
            nwc24ShtRetryRest = rest;
        } else {
            return TRUE;
        }
    } else {
        shtBuffer[0] = event;
        if (NWC24iIoctlResourceManagerAsync("NWC24iRequestShutdown", nwc24ShtFd, NWC24_IOCTL_SHUTDOWN, shtBuffer, sizeof(shtBuffer),
                                          shtResult, sizeof(shtResult), &result) >= 0) {
            shuttingdown = TRUE;
        }
    }

    return FALSE;
}

NWC24Err NWC24DoDailyTasks(void* work) {
    SCIdleModeInfo idle;
    NWC24Err result = NWC24_OK;
    u32 status;
    u32 i = 0;
    u64 elapsed = i * 100;

    if ((u32)(rand() + OSGetTick()) % 10 != 0) {
        return NWC24_OK;
    }

    if (NWC24IsMsgLibOpened() != FALSE) {
        return NWC24_ERR_LIB_OPENED;
    }

    for (;;) {
        status = SCCheckStatus();
        if (status == SC_STATUS_FATAL) {
            return NWC24_ERR_FATAL;
        }
        OSSleepTicks((u64)100 * (OS_TIMER_CLOCK / 1000) + (elapsed << 32));

        if (status == SC_STATUS_OK) {
            break;
        }
    }

    if (SCGetIdleMode(&idle) == FALSE) {
        return NWC24_ERR_NOT_FOUND;
    }

    status = SCGetNetContentRestrictions() & 2;

    if (idle.standby != 0) {
        return result;
    }

    if (status != 0) {
        result = NWC24AdjustUniversalTime();
    } else {
        result = NWC24OpenLib(work);
        if (result >= 0) {
            result = NWC24iMBoxSetLastUIDL(1, "");
            NWC24CloseLib();
        }
    }

    return result;
}
