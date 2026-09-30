#include <revolution/os.h>

static void SleepStart(OSAlarm* alarm, OSContext* context) {
    OSResumeThread((OSThread*)alarm->tag);
}

void NCDSleep(OSTime ticks) {
    OSAlarm alarm;
    BOOL enabled=OSDisableInterrupts();
    OSThread* thread=OSGetCurrentThread();
    if(!thread) { OSRestoreInterrupts(enabled); return; }
    OSCreateAlarm(&alarm);
    OSSetAlarmTag(&alarm,(u32)thread);
    OSSetAlarm(&alarm,ticks,SleepStart);
    OSSuspendThread(thread);
    OSCancelAlarm(&alarm);
    OSRestoreInterrupts(enabled);
}
