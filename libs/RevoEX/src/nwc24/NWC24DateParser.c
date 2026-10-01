#include <private/nwc24/NWC24Utils.h>

static const u8 DAYS_OF_MONTH[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static const u16 DAYS_OF_YEAR[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

s32 ConvertDateToDays(u16 year, u8 month, u8 day);
void ConvertDaysToDate(u16* year, u8* month, u8* day, s32 days);

static inline BOOL IsLeapYear(u16 year) {
    BOOL leap = FALSE;
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        leap = TRUE;
    return leap;
}

NWC24Err NWC24iDateToMinutes(s32* minutes, const NWC24Date* date) {
    s32 days;
    s32 minutesInDay;
    NWC24Err result;
    u8 hour;
    u8 minute;

    days = ConvertDateToDays(date->year, date->month, date->day);
    if (days == -1) {
        result = NWC24_ERR_FAILED;
    } else {
        hour = date->hour;
        minute = date->min;
        if (hour > 23 || minute > 59) {
            minutesInDay = -1;
        } else {
            minutesInDay = minute + hour * 60;
        }
        if (minutesInDay == -1 || date->sec > 60) {
            result = NWC24_ERR_FAILED;
        } else {
            result = NWC24_OK;
            *minutes = minutesInDay + days * 1440;
        }
    }

    return result;
}

NWC24Err NWC24iMinutesToDate(NWC24Date* date, s32 minutes) {
    s32 days;

    if (minutes < 0) {
        minutes = 0;
    }

    days = minutes / 1440;
    minutes %= 1440;
    date->hour = minutes / 60;
    date->min = minutes % 60;
    ConvertDaysToDate(&date->year, &date->month, &date->day, days);
    return NWC24_OK;
}

NWC24Err NWC24iEpochSecondsToDate(NWC24Date* date, s64 seconds) {
    s64 elapsedMinutes;
    s32 minutes;
    s32 days;

    if (seconds + 2208988800LL < 0) {
        seconds = -2208988800LL;
    }

    date->sec = (seconds + 2208988800LL) % 60;
    elapsedMinutes = (seconds + 2208988800LL) / 60;
    if ((s32)elapsedMinutes < 0) {
        elapsedMinutes = 0;
    }
    minutes = elapsedMinutes;

    days = minutes / 1440;
    minutes %= 1440;
    date->hour = minutes / 60;
    date->min = minutes % 60;
    ConvertDaysToDate(&date->year, &date->month, &date->day, days);
    return NWC24_OK;
}

NWC24Err NWC24iMinutesToOSCalendarTime(OSCalendarTime* calendar, s32 minutes) {
    s32 days;
    NWC24Date date;
    BOOL isLeapYear;

    if (minutes < 0) {
        minutes = 0;
    }

    days = minutes / 1440;
    minutes %= 1440;

    date.hour = minutes / 60;
    date.min = minutes % 60;
    ConvertDaysToDate(&date.year, &date.month, &date.day, days);
    isLeapYear = 0;

    calendar->year = date.year;
    calendar->mon = date.month - 1;
    calendar->mday = date.day;
    calendar->hour = date.hour;
    calendar->min = date.min;
    calendar->sec = 0;
    calendar->msec = 0;
    calendar->usec = 0;
    calendar->yday = date.day + DAYS_OF_YEAR[date.month - 1] - 1;
    if (((date.year % 4 == 0 && date.year % 100 != 0) || date.year % 400 == 0)) {
        isLeapYear = 1;
    }
    if (isLeapYear && date.month > 2) {
        calendar->yday++;
    }
    calendar->wday = (days + 1) % 7;
    return NWC24_OK;
}

NWC24Err NWC24iDateToOSCalendarTime(OSCalendarTime* calendar, const NWC24Date* date) {
    BOOL isLeapYear;
    s32 days;

    isLeapYear = 0;

    calendar->year = date->year;
    calendar->mon = date->month - 1;
    calendar->mday = date->day;
    calendar->hour = date->hour;
    calendar->min = date->min;
    calendar->sec = date->sec;
    calendar->msec = 0;
    calendar->usec = 0;
    calendar->yday = date->day + DAYS_OF_YEAR[date->month - 1] - 1;
    if (((date->year % 4 == 0 && date->year % 100 != 0) || date->year % 400 == 0)) {
        isLeapYear = 1;
    }
    if (isLeapYear && date->month > 2) {
        calendar->yday++;
    }

    days = ConvertDateToDays(date->year, date->month, date->day);
    calendar->wday = (days + 1) % 7;
    return NWC24_OK;
}

NWC24Err NWC24iIsValidDate(u16 year, u8 month, u8 day) {
    return ConvertDateToDays(year, month, day) == -1 ? NWC24_ERR_INVALID_VALUE : NWC24_OK;
}

s32 ConvertDateToDays(u16 year, u8 month, u8 day) {
    s32 daysOfYear;
    s32 yearOffset;
    s32 centuryLeapDays;
    s32 commonLeapDays;
    BOOL isLeapYear;

    if (year < 1900 || month < 1 || month > 12) {
        return -1;
    }

    if (month == 2) {
        isLeapYear = 0;
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            isLeapYear = 1;
        }
        if (isLeapYear) {
            if (day < 1 || day > 29) {
                return -1;
            }
            goto validDate;
        }
    }
    if (day < 1 || DAYS_OF_MONTH[month - 1] < day) {
        return -1;
    }

validDate:
    daysOfYear = day - 1 + DAYS_OF_YEAR[month - 1];
    if (month >= 3) {
        isLeapYear = 0;
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            isLeapYear = 1;
        }
        if (isLeapYear) {
            daysOfYear++;
        }
    }

    yearOffset = year - 1900;
    centuryLeapDays = (yearOffset + 299) / 400;
    daysOfYear += yearOffset * 365;
    daysOfYear += centuryLeapDays;
    commonLeapDays = (yearOffset - 1) / 4 - (yearOffset - 1) / 100;
    return daysOfYear + commonLeapDays;
}

void ConvertDaysToDate(u16* year, u8* month, u8* day, s32 days) {
    *year = 1900;
    *month = 1;
    *day = 1;
    if (days < 0) {
        return;
    }

    for (;;) {
        u16 currentYear = *year;
        s32 previousDays = days;
        BOOL leapYear = (currentYear % 4 == 0 && currentYear % 100 != 0) || currentYear % 400 == 0;
        days -= 365 + (leapYear != FALSE);
        if (days < 0) {
            days = previousDays;
            break;
        }
        *(volatile u16*)year += 1;
    }

    for (;;) {
        s32 previousDays = days;
        if (*month == 2 && IsLeapYear(*year)) {
            days -= 29;
        } else {
            days -= DAYS_OF_MONTH[*month - 1];
        }
        if (days < 0) {
            *(volatile u8*)day += previousDays;
            return;
        }
        *(volatile u8*)month += 1;
    }
}
