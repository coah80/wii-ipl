#include <revolution/ncd.h>
#include <revolution/os.h>

static void SleepStart(OSAlarm* alarm, OSContext* context) {
    OSResumeThread((OSThread*)alarm->tag);
}

void NCDSleep(OSTime tick) {
    OSAlarm alarm;
    s32 level;
    OSThread* thread;

    level = OSDisableInterrupts();
    thread = OSGetCurrentThread();

    if (thread == NULL) {
        OSRestoreInterrupts(level);
        return;
    }

    OSCreateAlarm(&alarm);
    OSSetAlarmTag(&alarm, (u32)thread);
    OSSetAlarm(&alarm, tick, SleepStart);
    OSSuspendThread(thread);
    OSCancelAlarm(&alarm);
    OSRestoreInterrupts(level);
}
