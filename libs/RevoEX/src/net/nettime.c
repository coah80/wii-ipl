#include <revolution/net.h>

#include <private/nwc24.h>
#include <private/os.h>

#include <revolution/NWC24.h>
#include <revolution/OS.h>

NWC24Err NWC24iEpochSecondsToDate(NWC24Date* date, OSTime time);
NWC24Err NWC24iDateToOSCalendarTime(OSCalendarTime* cal, const NWC24Date* date);

BOOL NETGetUniversalCalendar(OSCalendarTime* pTime) {
    static s64 whenCached = 0;
    NWC24Date date;
    s64 universalTime;

    if (whenCached == 0 ||
        whenCached + OSSecondsToTicks(60) < __OSGetSystemTime()) {

        NWC24iSynchronizeRtcCounter(FALSE);
        whenCached = __OSGetSystemTime();
    }

    if (NWC24iGetUniversalTime(&universalTime) >= 0 &&
        NWC24iEpochSecondsToDate(&date, universalTime) >= 0 &&
        NWC24iDateToOSCalendarTime(pTime, &date) >= 0) {

        return TRUE;
    }

    OSTicksToCalendarTime(OSGetTime(), pTime);
    return FALSE;
}
