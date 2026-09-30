#include <private/fa/pf_system.h>

typedef struct PFSYS_DATE { u32 sys_year, sys_month, sys_day; } PFSYS_DATE;
typedef struct PFSYS_TIME { u32 sys_hour, sys_min, sys_sec, sys_ms; } PFSYS_TIME;
typedef struct PFSYS_VOLUME_SET {
    u8 volume_state[0x64];
    s32 context_id;
} PFSYS_VOLUME_SET;
extern PFSYS_VOLUME_SET pf_vol_set;
extern void pfstub_init_stub(void);
PFSYS_SYSTEM_SET pf_sys_set;

void PFSYS_initializeSYS(void) {
    pfstub_init_stub();
}
s32 PFSYS_GetCurrentContextID(s32* context_id) {
    *context_id = pf_vol_set.context_id;
    return 0;
}
void PFSYS_TimeStamp(PFSYS_DATE* sdate, PFSYS_TIME* stime) {
    OSCalendarTime calendar;
    OSTicksToCalendarTime(OSGetTime(), &calendar);
    sdate->sys_year = calendar.year;
    sdate->sys_month = calendar.mon + 1;
    sdate->sys_day = calendar.mday;
    stime->sys_hour = calendar.hour;
    stime->sys_min = calendar.min;
    stime->sys_sec = calendar.sec;
    stime->sys_ms = 1;
}
