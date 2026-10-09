#include <zi8clib/zitypes.h>

ziU16 Zi8MatchAltSound(ziU8* elements, ziU16 count, ziU8* table, ziU16 ordinal,
                       ziU32 mask, ziU16 target, ziU8 flags ZI_NEED_WORK) {
    ziU8 ordinalHigh;
    ziU8 ordinalLow;
    ziS32 recordIndex;
    ziS32 searchIndex;
    ziS32 midpoint;
    ziU16 phoneticOffset;
    ziU16 phoneticCode;

    ordinalHigh = (ziU8)(ordinal >> 8);
    ordinalLow = (ziU8)ordinal;
    flags = (ziU8)(flags >> 3);
    if (count == 0) {
        return 0;
    }
    searchIndex = 0;
    recordIndex = count - 1;
    if ((elements + recordIndex * 4)[1] == ordinalHigh && (elements + recordIndex * 4)[0] == ordinalLow) {
        searchIndex = recordIndex;
    } else {
        if ((elements + searchIndex * 4)[1] != ordinalHigh || (elements + searchIndex * 4)[0] != ordinalLow) {
            goto search;
        }
    }
up:
    recordIndex = searchIndex;
    do {
        if (((elements + recordIndex * 4)[3] & 0xE) == 0 ||
            ((elements + recordIndex * 4)[3] & flags) != 0) {
            phoneticOffset = (ziU16)(((ziU16)(elements + recordIndex * 4)[2] |
                           (((ziU16)(elements + recordIndex * 4)[3] & 1) << 8)) << 1);
            phoneticCode = (ziU16)((((ziU16)(elements + recordIndex * 4)[3] & 0xF0) >> 4) |
                        (table[phoneticOffset] | ((ziU16)table[phoneticOffset + 1] << 8)));
            if (target == (phoneticCode & (ziU16)mask)) {
                return phoneticCode;
            }
        }
        recordIndex++;
        if (recordIndex >= count) {
            break;
        }
    } while ((elements + recordIndex * 4)[1] == ordinalHigh && (elements + recordIndex * 4)[0] == ordinalLow);
    recordIndex = searchIndex;
    while (--recordIndex >= 0 && (elements + recordIndex * 4)[1] == ordinalHigh && (elements + recordIndex * 4)[0] == ordinalLow) {
        if (((elements + recordIndex * 4)[3] & 0xE) == 0 ||
            ((elements + recordIndex * 4)[3] & flags) != 0) {
            phoneticOffset = (ziU16)(((ziU16)(elements + recordIndex * 4)[2] |
                           (((ziU16)(elements + recordIndex * 4)[3] & 1) << 8)) << 1);
            phoneticCode = (ziU16)((((ziU16)(elements + recordIndex * 4)[3] & 0xF0) >> 4) |
                        (table[phoneticOffset] | ((ziU16)table[phoneticOffset + 1] << 8)));
            if (target == (phoneticCode & (ziU16)mask)) {
                return phoneticCode;
            }
        }
    }
    return 0;
search:
    if ((elements + searchIndex * 4)[1] == ordinalHigh && (elements + searchIndex * 4)[0] == ordinalLow) {
        goto up;
    }
    if ((((ziU16)(elements + searchIndex * 4)[1] << 8) | (ziU16)(elements + searchIndex * 4)[0]) > ordinal) {
        return 0;
    }
    midpoint = (searchIndex + recordIndex) / 2;
    if (midpoint == searchIndex) {
        return 0;
    }
    if ((((ziU16)(elements + midpoint * 4)[1] << 8) | (ziU16)(elements + midpoint * 4)[0]) >= ordinal) {
        recordIndex = midpoint;
    } else {
        searchIndex = midpoint;
        goto search;
    }
hi_check:
    if ((elements + recordIndex * 4)[1] == ordinalHigh && (elements + recordIndex * 4)[0] == ordinalLow) {
        searchIndex = recordIndex;
        goto up;
    }
    if ((((ziU16)(elements + recordIndex * 4)[1] << 8) | (ziU16)(elements + recordIndex * 4)[0]) < ordinal) {
        return 0;
    }
    midpoint = (searchIndex + recordIndex) / 2;
    if (midpoint == searchIndex) {
        return 0;
    }
    if ((((ziU16)(elements + midpoint * 4)[1] << 8) | (ziU16)(elements + midpoint * 4)[0]) >= ordinal) {
        recordIndex = midpoint;
        goto hi_check;
    }
    searchIndex = midpoint;
    goto search;
}
