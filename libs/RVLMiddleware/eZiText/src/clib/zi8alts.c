#include <zi8clib/zitypes.h>

ziU16 Zi8MatchAltSound(ziU8* elements, ziU16 count, ziU8* table, ziU16 ch,
                       ziU32 mask, ziU16 target, ziU8 flags ZI_NEED_WORK) {
    ziU8 hi;
    ziU8 lo;
    ziS32 i;
    ziS32 j;
    ziS32 mid;
    ziU16 off;
    ziU16 w;

    hi = (ziU8)(ch >> 8);
    lo = (ziU8)ch;
    flags = (ziU8)(flags >> 3);
    if (count == 0) {
        return 0;
    }
    j = 0;
    i = count - 1;
    if ((elements + i * 4)[1] == hi && (elements + i * 4)[0] == lo) {
        j = i;
        goto up;
    }
    if ((elements + j * 4)[1] == hi && (elements + j * 4)[0] == lo) {
        goto up;
    }
    goto search;
up:
    i = j;
    do {
        if (((elements + i * 4)[3] & 0xE) == 0 ||
            ((elements + i * 4)[3] & flags) != 0) {
            off = (ziU16)(((ziU16)(elements + i * 4)[2] |
                           (((ziU16)(elements + i * 4)[3] & 1) << 8)) << 1);
            w = (ziU16)((((ziU16)(elements + i * 4)[3] & 0xF0) >> 4) |
                        (table[off] | ((ziU16)table[off + 1] << 8)));
            if (target == (w & (ziU16)mask)) {
                return w;
            }
        }
        i++;
        if (i >= count) {
            break;
        }
    } while ((elements + i * 4)[1] == hi && (elements + i * 4)[0] == lo);
    i = j;
    goto dec;
down_body:
    if (((elements + i * 4)[3] & 0xE) == 0 ||
        ((elements + i * 4)[3] & flags) != 0) {
        off = (ziU16)(((ziU16)(elements + i * 4)[2] |
                       (((ziU16)(elements + i * 4)[3] & 1) << 8)) << 1);
        w = (ziU16)((((ziU16)(elements + i * 4)[3] & 0xF0) >> 4) |
                    (table[off] | ((ziU16)table[off + 1] << 8)));
        if (target == (w & (ziU16)mask)) {
            return w;
        }
    }
dec:
    i--;
    if (i < 0) {
        goto fail;
    }
    if ((elements + i * 4)[1] == hi && (elements + i * 4)[0] == lo) {
        goto down_body;
    }
fail:
    return 0;
search:
    if ((elements + j * 4)[1] == hi && (elements + j * 4)[0] == lo) {
        goto up;
    }
    if ((((ziU16)(elements + j * 4)[1] << 8) | (ziU16)(elements + j * 4)[0]) > ch) {
        return 0;
    }
    mid = (j + i) / 2;
    if (mid == j) {
        return 0;
    }
    if ((((ziU16)(elements + mid * 4)[1] << 8) | (ziU16)(elements + mid * 4)[0]) >= ch) {
        i = mid;
        goto hi_check;
    }
    j = mid;
    goto search;
hi_check:
    if ((elements + i * 4)[1] == hi && (elements + i * 4)[0] == lo) {
        j = i;
        goto up;
    }
    if ((((ziU16)(elements + i * 4)[1] << 8) | (ziU16)(elements + i * 4)[0]) < ch) {
        return 0;
    }
    mid = (j + i) / 2;
    if (mid == j) {
        return 0;
    }
    if ((((ziU16)(elements + mid * 4)[1] << 8) | (ziU16)(elements + mid * 4)[0]) >= ch) {
        i = mid;
        goto hi_check;
    }
    j = mid;
    goto search;
}
