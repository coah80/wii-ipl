#include <private/os.h>
#include <revolution/os.h>

#include <private/pad.h>

#include <private/dvd.h>
#include <private/vi.h>

#include <private/hollywood.h>

static OSShutdownFunctionQueue ShutdownFunctionQueue;
vBOOL __OSIsReturnToIdle;

#define ENQUEUE_INFO(info, queue)                                                                                                                    \
    {                                                                                                                                                \
        OSShutdownFunctionInfo* __prev = (queue)->tail;                                                                                              \
        if (__prev == 0) {                                                                                                                           \
            (queue)->head = (info);                                                                                                                  \
        } else {                                                                                                                                     \
            __prev->next = (info);                                                                                                                   \
        }                                                                                                                                            \
        (info)->prev = __prev;                                                                                                                       \
        (info)->next = 0;                                                                                                                            \
        (queue)->tail = (info);                                                                                                                      \
    }

#define DEQUEUE_INFO(info, queue)                                                                                                                    \
    {                                                                                                                                                \
        OSShutdownFunctionInfo* __next = (info)->next;                                                                                               \
        OSShutdownFunctionInfo* __prev = (info)->prev;                                                                                               \
        if (__next == 0) {                                                                                                                           \
            (queue)->tail = __prev;                                                                                                                  \
        } else {                                                                                                                                     \
            __next->prev = __prev;                                                                                                                   \
        }                                                                                                                                            \
        if (__prev == 0) {                                                                                                                           \
            (queue)->head = __next;                                                                                                                  \
        } else {                                                                                                                                     \
            __prev->next = __next;                                                                                                                   \
        }                                                                                                                                            \
    }

#define ENQUEUE_INFO_PRIO(info, queue)                                                                                                               \
    {                                                                                                                                                \
        OSShutdownFunctionInfo* __prev;                                                                                                              \
        OSShutdownFunctionInfo* __next;                                                                                                              \
        for (__next = (queue)->head; __next && (__next->priority <= (info)->priority); __next = __next->next)                                        \
            ;                                                                                                                                        \
                                                                                                                                                     \
        if (__next == 0) {                                                                                                                           \
            ENQUEUE_INFO(info, queue);                                                                                                               \
        } else {                                                                                                                                     \
            (info)->next = __next;                                                                                                                   \
            __prev = __next->prev;                                                                                                                   \
            __next->prev = (info);                                                                                                                   \
            (info)->prev = __prev;                                                                                                                   \
            if (__prev == 0) {                                                                                                                       \
                (queue)->head = (info);                                                                                                              \
            } else {                                                                                                                                 \
                __prev->next = (info);                                                                                                               \
            }                                                                                                                                        \
        }                                                                                                                                            \
    }

// They're used but pooled first.
static char resetSource[] = "OSReset.c";
static char hotResetFailure[] = "__OSHotReset(): Falied to reset system.\n";

void __OSReturnToMenu(u8 menuMode) {
    OSStateFlags state;

    __OSStopPlayRecord();
    __OSUnRegisterStateEvent();
    __DVDPrepareReset();
    __OSReadStateFlags(&state);
    state.discState = __OSGetDiscState(state.discState);
    state.shutdownType = OS_STATE_FLAGS_SHUTDOWN_RETURN_MENU;
    state.menuMode = menuMode;
    __OSClearRTCFlags();
    __OSWriteStateFlags(&state);
    OSDisableScheduler();
    __OSShutdownDevices(OS_SHUTDOWN_RETURN_MENU);
    OSEnableScheduler();
    __OSLaunchMenu();
    OSDisableScheduler();
    __VISetRGBModeImm();
    __OSHotResetForError();
}

DECL_WEAK void OSReturnToMenu(void) {
    __OSReturnToMenu(OS_STATE_FLAGS_MENUMODE_MENU);
    OSPanic(resetSource, __LINE__, "OSReturnToMenu(): Falied to boot system menu.\n");
}

void OSReturnToDataManager(void) {
    __OSReturnToMenu(OS_STATE_FLAGS_MENUMODE_DATA_MANAGER);
    OSPanic(resetSource, __LINE__, "OSReturnToDataManager(): Falied to boot system menu.\n");
}

enum {
    LAUNCH_ARG_MENU = 0,
    LAUNCH_ARG_SETTING,
};

static void KillThreads() {
    OSThread* thread;
    OSThread* next;

    for (thread = __OSActiveThreadQueue.head; thread; thread = next) {
        next = thread->linkActive.next;

        switch (thread->state) {
            case OS_THREAD_STATE_READY:
            case OS_THREAD_STATE_WAITING: {
                OSCancelThread(thread);
                break;
            }
            default: {
                break;
            }
        }
    }
}

void OSRegisterShutdownFunction(OSShutdownFunctionInfo* info) {
    ENQUEUE_INFO_PRIO(info, &ShutdownFunctionQueue);
}

BOOL __OSCallShutdownFunctions(BOOL final, u32 event) {
    OSShutdownFunctionInfo* info;
    BOOL err;
    u32 priority = 0;

    err = FALSE;
    info = ShutdownFunctionQueue.head;
    while (info) {
        if (err && priority != info->priority) {
            break;
        }

        err |= !info->func(final, event);
        priority = info->priority;
        info = info->next;
    }
    err |= !__OSSyncSram();
    return err ? FALSE : TRUE;
}

void __OSShutdownDevices(u32 event) {
    BOOL rc, disableRecalibration, doRecal;

    switch (event) {
        case 0:
        case OS_SHUTDOWN_RETURN_MENU:
        case OS_SHUTDOWN_LAUNCH: {
            doRecal = FALSE;
            break;
        }
        case OS_SHUTDOWN_STANDBY:
        case 1:
        case OS_SHUTDOWN_RESTART:
        case 3:
        default: {
            doRecal = TRUE;
            break;
        }
    }

    __OSStopAudioSystem();

    if (!doRecal) {
        disableRecalibration = __PADDisableRecalibration(TRUE);
    }

    while (!__OSCallShutdownFunctions(FALSE, event)) {
    }
    while (!__OSSyncSram()) {
    }

    OSDisableInterrupts();
    rc = __OSCallShutdownFunctions(TRUE, event);
    LCDisable();

    if (!doRecal) {
        __PADDisableRecalibration(disableRecalibration);
    }

    KillThreads();
}

// what the hell
u8 __OSGetDiscState(u8 out) {
    u32 flags;

    if (__DVDGetCoverStatus() != DVD_COVER_CLOSED) {
        return 3;
    } else if (out == 1) {
        if (!__OSGetRTCFlags(&flags) || flags == 0) {
            goto status_1;
        }
    status_2:
        return 2;
    } else {
        goto status_2;
    status_1:
        return 1;
    }
}

void OSReturnToSetting(u8 setting) {
    char* url;
    switch (setting) {
        case OS_SETTING_CALENDAR: {
            url = "Calendar/Calendar_index.html";
            break;
        }
        case OS_SETTING_DISPLAY: {
            url = "Display/Display_index.html";
            break;
        }
        case OS_SETTING_SOUND: {
            url = "Sound/Sound_index.html";
            break;
        }
        case OS_SETTING_PARENTAL_CONTROL: {
            url = "Parental_Control/Parental_Control_index.html";
            break;
        }
        case OS_SETTING_INTERNET: {
            url = "Internet/Internet_index.html";
            break;
        }
        case OS_SETTING_WIICONNECT24: {
            url = "WiiConnect24/Wiiconnect24_index.html";
            break;
        }
        case OS_SETTING_UPDATE: {
            url = "Update/Update_index.html";
            break;
        }
        default: {
            OSReport("OSReturnToSetting(): You can't specify %d.  \n", setting);
            OSPanic(resetSource, 910, "");
        }
    }

    __OSReturnToMenul(LAUNCH_ARG_SETTING, url, NULL);
}

void __OSReturnToMenuForError() {
    OSStateFlags state;

    __OSReadStateFlags(&state);
    state.discState = OS_STATE_FLAGS_DISC_CHANGED;
    state.shutdownType = OS_STATE_FLAGS_SHUTDOWN_RETURN_MENU;
    __OSClearRTCFlags();
    __OSWriteStateFlags(&state);

    __OSLaunchMenu();

    OSDisableScheduler();
    __VISetRGBModeImm();
    __OSHotResetForError();

    OSPanic(resetSource, 949, "__OSReturnToMenu(): Falied to boot system menu.\n");
}

void __OSHotResetForError() {
    if (__OSInNandBoot || __OSInReboot) {
        __OSInitSTM();
    }
    __OSHotReset();
    OSPanic(resetSource, 973, hotResetFailure);
}

u32 OSGetResetCode() {
    u32 code;
    if (__OSRebootParams.valid) {
        code = ((1 << 31) | __OSRebootParams.restartCode);
    } else {
        code = (PI_READ_REG(PI_RESET_REQUEST) & 0xFFFFFFF8) >> 3;
    }
    return code;
}

void OSResetSystem(int reset, u32 resetCode, int forceMenu) {
    OSPanic(resetSource, __LINE__, "OSResetSystem() is obsoleted. It doesn't work any longer.\n");
}

u32 OSSetBootDol(u32 dolOffset) {
    OSPanic(resetSource, __LINE__, "OSSetBootDol() is obsoleted. It doesn't work any longer.\n");
    return 0;
}
