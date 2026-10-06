#include <private/os.h>
#include <revolution/os.h>
#include <revolution/nwc24/NWC24Err.h>

NWC24Err NWC24iPrepareShutdown(void) NO_INLINE;
s32 NWC24SuspendScheduler(void) NO_INLINE;
s32 NWC24ResumeScheduler(void) NO_INLINE;

#include <private/nwc24.h>
#include <revolution/nwc24.h>

static s32 nwc24ShtFd = -1;
static s32 nwc24ShtRetryRest;
static OSShutdownFunctionInfo ShutdownFuncInfo;

static NWC24Err CheckCallingStatus(const char* callerName) NO_INLINE;
BOOL NWC24Shutdown_(BOOL final, u32 event) NO_INLINE;
NWC24Err NWC24iRequestShutdown(u32 event, s32* result) NO_INLINE;
NWC24Err NWC24iSetRtcCounter_(s32 rtc, BOOL save) NO_INLINE;

void __OSInitNet() {
    NWC24Err ret;
    OSIOSRev iosRev;

    __OSGetIOSRev(&iosRev);

    if (iosRev.major <= 4 || iosRev.major == 9) {
        return;
    }

    ret = NWC24iPrepareShutdown();

    if (ret != NWC24_OK) {
        if (ret < NWC24_OK) {
            OSReport("Failed to register network shutdown function. %d\n", ret);
        }
        ret = NWC24SuspendScheduler();
        if (ret < NWC24_OK) {
            OSReport("Failed to suspend the WiiConnect24 scheduler. %d\n", ret);
        }
    }

    if (!__OSInIPL) {
        ret = NWC24iSynchronizeRtcCounter(FALSE);
        if (ret != NWC24_OK) {
            OSReport("Failed to synchronize time with network resource managers. %d\n", ret);
        }
    }
}

s32 __OSSyncTimeWithNetRM() {
    return NWC24iSynchronizeRtcCounter(FALSE);
}

static NWC24Err CheckCallingStatus(const char* callerName) NO_INLINE {
    if (OSGetCurrentThread() == 0) {
        return NWC24_ERR_FATAL;
    }

    return NWC24_OK;
}

DECL_WEAK NWC24Err NWC24iPrepareShutdown(void) NO_INLINE {
    NWC24Err result = NWC24_OK;

    ShutdownFuncInfo.func = NWC24Shutdown_;
    ShutdownFuncInfo.priority = 110;
    OSRegisterShutdownFunction(&ShutdownFuncInfo);

    if (nwc24ShtFd < 0) {
        result = NWC24iOpenResourceManager("NWC24iPrepareShutdown", "/dev/net/kd/request", &nwc24ShtFd, 1);
    }

    nwc24ShtRetryRest = 5;

    if (result == NWC24_OK) {
        result = 1;
    }

    return result;
}

DECL_WEAK s32 NWC24SuspendScheduler(void) NO_INLINE {
    static u8 susResult[0x20] ALIGN32;
    NWC24Err result;
    NWC24Err closeResult;
    s32 fd;

    result = CheckCallingStatus("NWC24SuspendScheduler");
    if (result < NWC24_OK) {
        return result;
    }

    result = NWC24iOpenResourceManager("NWC24SuspendScheduler", "/dev/net/kd/request", &fd, 0);
    if (result >= NWC24_OK) {
        result = NWC24iIoctlResourceManager("NWC24SuspendScheduler", fd, NWC24_IOCTL_SUSPEND_SCHEDULER, NULL, 0, susResult, sizeof(susResult));
        if (result >= NWC24_OK) {
            result = *(NWC24Err*)susResult;
        }

        closeResult = NWC24iCloseResourceManager("NWC24SuspendScheduler", fd);
        if (closeResult < NWC24_OK) {
            result = closeResult;
        }
    }

    return result;
}

DECL_WEAK s32 NWC24ResumeScheduler(void) NO_INLINE {
    static u8 resResult[0x20] ALIGN32;
    NWC24Err result;
    NWC24Err closeResult;
    s32 fd;

    result = CheckCallingStatus("NWC24ResumeScheduler");
    if (result < NWC24_OK) {
        return result;
    }

    result = NWC24iOpenResourceManager("NWC24ResumeScheduler", "/dev/net/kd/request", &fd, 0);
    if (result >= NWC24_OK) {
        result = NWC24iIoctlResourceManager("NWC24ResumeScheduler", fd, NWC24_IOCTL_RESUME_SCHEDULER, NULL, 0, resResult, sizeof(resResult));
        if (result >= NWC24_OK) {
            result = *(NWC24Err*)resResult;
        }

        closeResult = NWC24iCloseResourceManager("NWC24ResumeScheduler", fd);
        if (closeResult < NWC24_OK) {
            result = closeResult;
        }
    }

    return result;
}

NWC24Err NWC24iRequestShutdown(u32 event, s32* result) NO_INLINE {
    static u32 shtBuffer[8] ALIGN32;
    static u32 shtResult[8] ALIGN32;

    shtBuffer[0] = event;
    return NWC24iIoctlResourceManagerAsync("NWC24iRequestShutdown", nwc24ShtFd, NWC24_IOCTL_SHUTDOWN, shtBuffer, sizeof(shtBuffer), shtResult,
                                           sizeof(shtResult), result);
}

BOOL NWC24Shutdown_(BOOL final, u32 event) NO_INLINE {
    static BOOL shuttingdown;
    static s32 result;

    if (final) {
        return TRUE;
    }

    if (shuttingdown) {
        if (NWC24iIsAsyncRequestPending()) {
            return FALSE;
        }

        if (result >= 0) {
            return TRUE;
        }

        if (nwc24ShtRetryRest > 0) {
            shuttingdown = FALSE;
            nwc24ShtRetryRest--;
        } else {
            OSReport("NWC24Shutdown_: Give up!\n");
            return TRUE;
        }
    } else if (NWC24iRequestShutdown(event, &result) >= NWC24_OK) {
        shuttingdown = TRUE;
    }

    return FALSE;
}

static u32 nwc24TimeCommonBuffer[8] ALIGN32;
static u32 nwc24TimeCommonResult[8] ALIGN32;

NWC24Err NWC24iSetRtcCounter_(s32 rtc, BOOL save) NO_INLINE {
    NWC24Err result;
    NWC24Err closeResult;
    s32 fd;

    result = CheckCallingStatus("NWC24iSetRtcCounter_");
    if (result < NWC24_OK) {
        return result;
    }

    result = NWC24iOpenResourceManager("NWC24iSetRtcCounter_", "/dev/net/kd/time", &fd, 0);
    if (result >= NWC24_OK) {
        nwc24TimeCommonBuffer[0] = rtc;
        nwc24TimeCommonBuffer[1] = save;

        result = NWC24iIoctlResourceManager("NWC24iSetRtcCounter_", fd, NWC24_IOCTL_SET_RTC_COUNTER, nwc24TimeCommonBuffer,
                                            sizeof(nwc24TimeCommonBuffer), nwc24TimeCommonResult, sizeof(nwc24TimeCommonResult));
        if (result >= NWC24_OK) {
            result = *(s32*)nwc24TimeCommonResult;
        }

        closeResult = NWC24iCloseResourceManager("NWC24iSetRtcCounter_", fd);
        if (result >= NWC24_OK) {
            result = closeResult;
        }
    }

    return result;
}
