#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>

extern ziU16 Zi8Ord2Ord(ziU16 ord ZI_NEED_WORK);
extern ziU8 Zi8LangSupported(ziU8 lang ZI_NEED_WORK);


static const ziWChar zi8ZYinitialSpelling[64] = {
    0x0000, 0x0000, 0xEFF2, 0x0000, 0x0000, 0xEFF2, 0xEFF4, 0x0000,
    0x0000, 0xEFF4, 0xEFF4, 0x0000, 0xEFF1, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0xEFF6, 0xEFF5, 0xEFF6, 0xEFF5, 0xEFF6, 0xEFF5, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xEFF2, 0x0000,
    0x0000, 0x0000, 0x0000, 0xEFF2, 0xEFF5, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0xEFF3, 0x0000, 0x0000, 0xEFF3,
    0xEFF1, 0x0000, 0x0000, 0xEFF3, 0xEFF1, 0x0000, 0x0000, 0xEFF1,
};
static const ziWChar zi8ZYfinalSpelling[64][2] = {
    {0x0000, 0x0000}, {0xEFF7, 0x0000}, {0xEFF7, 0x0000}, {0xEFF7, 0x0000},
    {0xEFF9, 0x0000}, {0x0000, 0x0000}, {0x0000, 0x0000}, {0x0000, 0x0000},
    {0xEFF8, 0x0000}, {0xEFF8, 0x0000}, {0xEFF8, 0x0000}, {0xEFF8, 0x0000},
    {0xEFF9, 0x0000}, {0xEFF9, 0x0000}, {0xEFF9, 0x0000}, {0xEFF9, 0x0000},
    {0x0000, 0x0000}, {0xEFFA, 0xEFF7}, {0xEFFA, 0xEFF7}, {0x0000, 0x0000},
    {0x0000, 0x0000}, {0xEFFA, 0xEFF7}, {0x0000, 0x0000}, {0xEFFA, 0x0000},
    {0xEFFA, 0xEFF8}, {0x0000, 0x0000}, {0xEFFA, 0xEFF8}, {0xEFFA, 0xEFF8},
    {0xEFFA, 0xEFF9}, {0xEFFA, 0xEFF9}, {0xEFFA, 0xEFF9}, {0xEFFA, 0xEFF9},
    {0x0000, 0x0000}, {0xEFFA, 0xEFF7}, {0xEFFA, 0xEFF7}, {0x0000, 0x0000},
    {0x0000, 0x0000}, {0xEFFA, 0xEFF7}, {0x0000, 0x0000}, {0xEFFA, 0x0000},
    {0xEFFA, 0xEFF8}, {0xEFFA, 0xEFF8}, {0x0000, 0x0000}, {0x0000, 0x0000},
    {0xEFFA, 0xEFF9}, {0xEFFA, 0xEFF9}, {0xEFFA, 0xEFF9}, {0xEFFA, 0xEFF9},
    {0x0000, 0x0000}, {0x0000, 0x0000}, {0x0000, 0x0000}, {0x0000, 0x0000},
    {0x0000, 0x0000}, {0xEFFA, 0xEFF7}, {0x0000, 0x0000}, {0xEFFA, 0x0000},
    {0x0000, 0x0000}, {0x0000, 0x0000}, {0x0000, 0x0000}, {0x0000, 0x0000},
    {0xEFFA, 0xEFF9}, {0x0000, 0x0000}, {0xEFFA, 0xEFF9}, {0xEFFA, 0xEFF9},
};
static const ziWChar zi8PYinitialSpelling[64][2] = {
    {0x0000, 0x0000}, {0x0000, 0x0000}, {0xEFF3, 0x0000}, {0x0000, 0x0000},
    {0x0000, 0x0000}, {0xEFF8, 0x0000}, {0xEFF5, 0x0000}, {0x0000, 0x0000},
    {0x0000, 0x0000}, {0xEFF7, 0x0000}, {0xEFF9, 0x0000}, {0x0000, 0x0000},
    {0xEFF6, 0x0000}, {0xEFF9, 0x0000}, {0x0000, 0x0000}, {0x0000, 0x0000},
    {0x0000, 0x0000}, {0xEFF9, 0x0000}, {0x0000, 0x0000}, {0x0000, 0x0000},
    {0x0000, 0x0000}, {0x0000, 0x0000}, {0x0000, 0x0000}, {0x0000, 0x0000},
    {0xEFF2, 0x0000}, {0xEFF2, 0xEFF4}, {0xEFF7, 0x0000}, {0xEFF7, 0xEFF4},
    {0xEFF9, 0x0000}, {0xEFF9, 0xEFF4}, {0x0000, 0x0000}, {0x0000, 0x0000},
    {0x0000, 0x0000}, {0x0000, 0x0000}, {0x0000, 0x0000}, {0x0000, 0x0000},
    {0x0000, 0x0000}, {0x0000, 0x0000}, {0xEFF6, 0x0000}, {0x0000, 0x0000},
    {0x0000, 0x0000}, {0x0000, 0x0000}, {0x0000, 0x0000}, {0xEFF5, 0x0000},
    {0xEFF7, 0x0000}, {0x0000, 0x0000}, {0x0000, 0x0000}, {0x0000, 0x0000},
    {0x0000, 0x0000}, {0x0000, 0x0000}, {0x0000, 0x0000}, {0x0000, 0x0000},
    {0xEFF4, 0x0000}, {0x0000, 0x0000}, {0x0000, 0x0000}, {0xEFF5, 0x0000},
    {0xEFF3, 0x0000}, {0x0000, 0x0000}, {0x0000, 0x0000}, {0xEFF4, 0x0000},
    {0xEFF2, 0x0000}, {0x0000, 0x0000}, {0x0000, 0x0000}, {0xEFF7, 0x0000},
};
static const ziWChar zi8PYfinalSpelling[64][4] = {
    {0x0000, 0x0000, 0x0000, 0x0000}, {0xEFF4, 0xEFF2, 0xEFF6, 0x0000},
    {0xEFF4, 0xEFF2, 0xEFF6, 0x0000}, {0xEFF4, 0xEFF2, 0xEFF6, 0xEFF4},
    {0xEFF4, 0xEFF2, 0x0000, 0x0000}, {0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000}, {0x0000, 0x0000, 0x0000, 0x0000},
    {0xEFF4, 0x0000, 0x0000, 0x0000}, {0xEFF4, 0xEFF3, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000}, {0xEFF4, 0xEFF8, 0x0000, 0x0000},
    {0xEFF4, 0xEFF6, 0x0000, 0x0000}, {0xEFF4, 0xEFF6, 0xEFF4, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000}, {0xEFF4, 0xEFF6, 0xEFF6, 0xEFF4},
    {0xEFF8, 0xEFF2, 0xEFF6, 0x0000}, {0xEFF8, 0xEFF2, 0xEFF6, 0xEFF4},
    {0x0000, 0x0000, 0x0000, 0x0000}, {0xEFF8, 0xEFF2, 0xEFF4, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000}, {0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000}, {0xEFF8, 0xEFF2, 0x0000, 0x0000},
    {0xEFF8, 0x0000, 0x0000, 0x0000}, {0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000}, {0x0000, 0x0000, 0x0000, 0x0000},
    {0xEFF8, 0xEFF6, 0x0000, 0x0000}, {0xEFF8, 0xEFF4, 0x0000, 0x0000},
    {0xEFF8, 0xEFF6, 0x0000, 0x0000}, {0xEFF8, 0xEFF3, 0x0000, 0x0000},
    {0xEFF2, 0xEFF6, 0x0000, 0x0000}, {0xEFF2, 0xEFF6, 0xEFF4, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000}, {0xEFF2, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000}, {0xEFF2, 0xEFF4, 0x0000, 0x0000},
    {0xEFF2, 0xEFF6, 0x0000, 0x0000}, {0x0000, 0x0000, 0x0000, 0x0000},
    {0xEFF6, 0xEFF6, 0xEFF4, 0x0000}, {0x0000, 0x0000, 0x0000, 0x0000},
    {0xEFF6, 0xEFF8, 0x0000, 0x0000}, {0xEFF6, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000}, {0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000}, {0x0000, 0x0000, 0x0000, 0x0000},
    {0xEFF3, 0xEFF6, 0x0000, 0x0000}, {0xEFF3, 0xEFF6, 0xEFF4, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000}, {0xEFF3, 0xEFF7, 0x0000, 0x0000},
    {0xEFF3, 0x0000, 0x0000, 0x0000}, {0xEFF3, 0xEFF4, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000}, {0x0000, 0x0000, 0x0000, 0x0000},
    {0xEFF8, 0x0000, 0x0000, 0x0000}, {0xEFF8, 0xEFF2, 0xEFF6, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000}, {0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000}, {0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000}, {0x0000, 0x0000, 0x0000, 0x0000},
};

static ziU8 Zi8SpellingZY(ziWChar* dst, ziU16 key, ziU8 flag) {
    ziU8 n;
    ziU16 iIdx;
    ziU16 fIdx;
    ziU16 tone;

    n = 0;
    iIdx = (key >> 9) & 0x3F;
    fIdx = (key >> 3) & 0x3F;
    tone = key & 7;
    if ((dst[0] = zi8ZYinitialSpelling[iIdx]) != 0) {
        n = 1;
    }
    dst[n] = zi8ZYfinalSpelling[fIdx][0];
    dst[n + 1] = zi8ZYfinalSpelling[fIdx][1];
    dst[n + 2] = 0;
    dst[n + 3] = 0;
    while (dst[n] != 0) {
        n++;
    }
    if (flag != 0) {
        switch (tone) {
        case 1:
            dst[n++] = 0xEFF1;
            break;
        case 2:
            dst[n++] = 0xEFF2;
            break;
        case 3:
            dst[n++] = 0xEFF3;
            break;
        case 4:
            dst[n++] = 0xEFF4;
            break;
        case 5:
            dst[n++] = 0xEFF5;
            break;
        }
    }
    return n;
}

static ziU8 Zi8SpellingPY(ziWChar* dst, ziU16 key, ziU8 flag) {
    ziU8 n;
    ziU16 iIdx;
    ziU16 fIdx;
    ziU16 tone;

    n = 0;
    iIdx = (key >> 9) & 0x3F;
    fIdx = (key >> 3) & 0x3F;
    tone = key & 7;
    dst[0] = zi8PYinitialSpelling[iIdx][0];
    dst[1] = zi8PYinitialSpelling[iIdx][1];
    dst[2] = 0;
    while (dst[n] != 0) {
        n++;
    }
    dst[n] = zi8PYfinalSpelling[fIdx][0];
    dst[n + 1] = zi8PYfinalSpelling[fIdx][1];
    dst[n + 2] = zi8PYfinalSpelling[fIdx][2];
    dst[n + 3] = zi8PYfinalSpelling[fIdx][3];
    dst[n + 4] = 0;
    dst[n + 5] = 0;
    while (dst[n] != 0) {
        n++;
    }
    if (flag != 0) {
        switch (tone) {
        case 1:
            dst[n++] = 0xEFF1;
            break;
        case 2:
            dst[n++] = 0xEFF2;
            break;
        case 3:
            dst[n++] = 0xEFF3;
            break;
        case 4:
            dst[n++] = 0xEFF4;
            break;
        case 5:
            dst[n++] = 0xEFF5;
            break;
        }
    }
    return n;
}

ziBool Zi8IsMatch1Key(ziWChar* word, ziU8 count, ziU16 key, ziU8 exact, ziU8 isPY, ziU8 tone) {
    ziWChar buf[0x10];
    ziU8 n;
    ziS32 c;

    if (key == 0) {
        return ZI8_FALSE;
    }
    if (count == 0) {
        return ZI8_TRUE;
    }
    if (isPY != 0) {
        n = Zi8SpellingPY(buf, key, tone);
    } else {
        n = Zi8SpellingZY(buf, key, tone);
    }
    if (exact != 0) {
        if (count != n) {
            return ZI8_FALSE;
        }
    }
    if (tone == 0) {
        if (count > n) {
            c = word[count - 1];
            if (c < 0xEFF6 && c >= 0xEFF1) {
                count = count - 1;
            }
        }
    }
    if (count > n) {
        return ZI8_FALSE;
    }
    for (n = 0; n < count; n++) {
        if (buf[n] != word[n]) {
            return ZI8_FALSE;
        }
    }
    return ZI8_TRUE;
}

ziBool MatchAltSound1Key(ziWChar* word, ziU8 count, ziU8 arg5, ziU8* table, ziU16 tableCount,
                         ziU8* map, ziU16 key, ziU8 arg8, ziU8 arg9, ziU8 arg10, ziPtr work) {
    ziU8 hi;
    ziU8 lo;
    ziS32 first;
    ziS32 last;
    ziS32 mid;
    ziS32 i;
    ziU16 v;
    ziWChar ent;
    ziU8 f;

    Zi8LogError(0x64, work);
    hi = (ziU8)((ziU16)key >> 8);
    lo = (ziU8)key;
    arg10 = (ziU8)(arg10 >> 3);
    if (tableCount == 0) {
        Zi8ReplaceLastError(0x964, work);
        return ZI8_FALSE;
    }
    first = 0;
    i = tableCount - 1;
    if (table[i * 4 + 1] == hi && table[i * 4] == lo) {
        first = i;
    } else {
        if (table[first * 4 + 1] != hi || table[first * 4] != lo) {
            last = tableCount - 1;
            for (;;) {
                if (table[first * 4 + 1] == hi && table[first * 4] == lo) {
                    break;
                }
                v = (ziU16)(((ziU16)table[first * 4 + 1] << 8) | table[first * 4]);
                if (v > key) {
                    return ZI8_FALSE;
                }
                mid = (first + last) / 2;
                if (mid == first) {
                    return ZI8_FALSE;
                }
                v = (ziU16)(((ziU16)table[mid * 4 + 1] << 8) | table[mid * 4]);
                if (v >= key) {
                    last = mid;
                } else {
                    first = mid;
                    continue;
                }
                if (table[last * 4 + 1] == hi && table[last * 4] == lo) {
                    first = last;
                    break;
                }
                v = (ziU16)(((ziU16)table[last * 4 + 1] << 8) | table[last * 4]);
                if (v < key) {
                    return ZI8_FALSE;
                }
                mid = (first + last) / 2;
                if (mid == first) {
                    return ZI8_FALSE;
                }
                v = (ziU16)(((ziU16)table[mid * 4 + 1] << 8) | table[mid * 4]);
                if (v >= key) {
                    last = mid;
                } else {
                    first = mid;
                }
            }
        }
    }
    for (i = first; i < tableCount && table[i * 4 + 1] == hi && table[i * 4] == lo; i++) {
        f = table[i * 4 + 3];
        if (((f >> 1) & 7) == 0 || (f & arg10) != 0) {
            v = (ziU16)(table[i * 4 + 2] | ((ziU16)(f & 1) << 8));
            if (*(ziU8*)((ziU8*)work + 0x11FA) == 0 ||
                *(ziU8*)((ziU8*)work + 0xFFA + v) != 0) {
                v = (ziU16)(v << 1);
                ent = (ziWChar)(map[v] | ((ziU16)map[v + 1] << 8) | ((f & 0xF0) >> 4));
                if (Zi8IsMatch1Key(word, count, ent, arg5, arg8, arg9) != 0) {
                    return ZI8_TRUE;
                }
            }
        }
    }
    for (i = first - 1; i >= 0 && table[i * 4 + 1] == hi && table[i * 4] == lo; i--) {
        f = table[i * 4 + 3];
        if (((f >> 1) & 7) == 0 || (f & arg10) != 0) {
            v = (ziU16)(table[i * 4 + 2] | ((ziU16)(f & 1) << 8));
            if (*(ziU8*)((ziU8*)work + 0x11FA) == 0 ||
                *(ziU8*)((ziU8*)work + 0xFFA + v) != 0) {
                v = (ziU16)(v << 1);
                ent = (ziWChar)(map[v] | ((ziU16)map[v + 1] << 8) | ((f & 0xF0) >> 4));
                if (Zi8IsMatch1Key(word, count, ent, arg5, arg8, arg9) != 0) {
                    return ZI8_TRUE;
                }
            }
        }
    }
    return ZI8_FALSE;
}

static ziU8 Zi8SetFindCand(ziU8* table, ziU16 ch ZI_NEED_WORK) {
    ziU8 old;

    ch = Zi8Ord2Ord(ch, ZI_WORK);
    old = (ziU8)((1 << (ch % 8)) & table[ch / 8]);
    table[ch / 8] |= 1 << (ch % 8);
    return old;
}

static ziBool ZiIsSupportedPhonetic(ziU8 lang ZI_NEED_WORK) {
    if (Zi8LangSupported(lang, ZI_WORK) != 0) {
        return ZI8_TRUE;
    }
    switch (lang) {
    case 0x77:
    case 0x78:
    case 0x7C:
        if (Zi8LangSupported(0x77, ZI_WORK) != 0 ||
            Zi8LangSupported(0x78, ZI_WORK) != 0 ||
            Zi8LangSupported(0x7C, ZI_WORK) != 0) {
            return ZI8_TRUE;
        }
        /* fallthrough */
    case 0x79:
    case 0x7A:
    case 0x7D:
        if (Zi8LangSupported(0x79, ZI_WORK) != 0 ||
            Zi8LangSupported(0x7A, ZI_WORK) != 0 ||
            Zi8LangSupported(0x7D, ZI_WORK) != 0) {
            return ZI8_TRUE;
        }
        break;
    }
    return ZI8_FALSE;
}

