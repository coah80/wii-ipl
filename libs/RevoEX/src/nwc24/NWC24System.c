#include <private/nwc24.h>
#include <private/os/OSStateTM.h>
#include <revolution/os.h>
#include <revolution/sc.h>
#include <stdlib.h>

static s32 nwc24ShtFd = -1;
static s32 nwc24ShtRetryRest = 0;
static OSShutdownFunctionInfo ShutdownFuncInfo;
BOOL NWC24Shutdown(BOOL final, u32 event);
NWC24Err NWC24iMBoxSetLastUIDL(u32 type, const char* uidl);

NWC24Err NWC24EnableLedNotification(BOOL enable) {
    u8 led = 0;
    SCIdleModeInfo idleMode;
    u32 status;
    if (enable) {
        do {
            status = SCCheckStatus();
            if (status == 2)
                return NWC24_ERR_FATAL;
        } while (status == 1);
        SCGetIdleMode(&idleMode);
        led = idleMode.led;
    }
    __OSSetIdleLEDMode(led);
    return NWC24_OK;
}

NWC24Err NWC24iPrepareShutdown(void) {
    NWC24Err result = NWC24_OK;
    SCIdleModeInfo idleMode;
    u32 status;
    NWC24iRegister();
    ShutdownFuncInfo.func = NWC24Shutdown;
    ShutdownFuncInfo.priority = 110;
    OSRegisterShutdownFunction(&ShutdownFuncInfo);
    if (nwc24ShtFd < 0)
        result = NWC24OpenResourceManager("/dev/net/kd/request", &nwc24ShtFd, 1);
    nwc24ShtRetryRest = 5;
    do {
        status = SCCheckStatus();
        if (status == 2)
            goto ready;
    } while (status == 1);
    SCGetIdleMode(&idleMode);
    __OSSetIdleLEDMode(idleMode.led);
ready:
    if (OSGetAppType() == 0x40)
        NWC24iSetScriptMode(1);
    return result;
}

static inline NWC24Err NWC24iRequestShutdown(u32 event, NWC24Err* result) {
    static u32 shtBuffer[8] ALIGN32;
    static u32 shtResult[8] ALIGN32;
    shtBuffer[0] = event;
    return NWC24IoctlResourceManagerAsync(nwc24ShtFd, NWC24_IOCTL_SHUTDOWN, shtBuffer, sizeof(shtBuffer), shtResult, sizeof(shtResult), (s32*)result);
}

BOOL NWC24Shutdown(BOOL final, u32 event) {
    static BOOL shuttingdown = FALSE;
    static NWC24Err result = NWC24_OK;
    if (final)
        return TRUE;
    if (shuttingdown) {
        if (NWC24IsAsyncRequestPending())
            return FALSE;
        if (result >= 0)
            return TRUE;
        if (nwc24ShtRetryRest > 0) {
            shuttingdown = FALSE;
            nwc24ShtRetryRest--;
        } else
            return TRUE;
    } else if (NWC24iRequestShutdown(event, &result) >= 0)
        shuttingdown = TRUE;
    return FALSE;
}

NWC24Err NWC24DoDailyTasks(void* work) {
    NWC24Err result = NWC24_OK;
    SCIdleModeInfo idleMode;
    u32 status;
    u32 restrictions;
    u32 tick = OSGetTick();
    u32 randomValue = rand();
    if ((randomValue + tick) % 10 != 0)
        return NWC24_OK;
    if (NWC24IsMsgLibOpened())
        return NWC24_ERR_LIB_OPENED;
    do {
        status = SCCheckStatus();
        if (status == 2)
            return NWC24_ERR_FATAL;
        OSSleepTicks(OSMillisecondsToTicks((OSTime)100));
    } while (status != 0);
    if (!SCGetIdleMode(&idleMode))
        return NWC24_ERR_NOT_FOUND;
    restrictions = SCGetNetContentRestrictions() & 2;
    if (idleMode.standby == 0) {
        if (restrictions == 0) {
            result = NWC24OpenLib(work);
            if (result >= 0) {
                result = NWC24iMBoxSetLastUIDL(NWC24_MBOX_TYPE_RECV, "");
                NWC24CloseLib();
            }
        } else
            result = NWC24AdjustUniversalTime();
    }
    return result;
}
