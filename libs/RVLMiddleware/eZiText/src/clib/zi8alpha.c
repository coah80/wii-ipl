#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>

extern void Zi8LogError(ziU16 code, ziPtr __zi8_work_data);
extern ziU8 Zi8IsWordW(ziWChar* w, ziU8 len, ziPtr __zi8_work_data);
extern ziU8 Zi8IsWordW2(ziWChar* w, ziU8 len, ziPtr __zi8_work_data);
extern ziU16 Zi8ConvertWC2Key(ziWChar ch, ziU8 lang, ziPtr __zi8_work_data);
extern ziU8 Zi8ChangeCharCase(ziU8 dir, ziWChar* buf, ziU8 lang, ziPtr __zi8_work_data);

typedef struct {
    ziU8 k[6];
    ziU16 a;
    ziU16 b;
} zi8ExclPair;

const zi8ExclPair IT_EXCLUDE_PAIRS[] = {
    { "l", 'i', 0 },     { "all", 'i', 0 },    { "dell", 'i', 0 },
    { "dall", 'i', 0 },  { "nell", 'i', 0 },   { "sull", 'i', 0 },
    { "d", 'i', 0 },     { "quest", 'i', 0 },  { "quell", 'i', 0 },
    { "bell", 'i', 0 },  { "brav", 'i', 0 },   { "buon", 'i', 0 },
    { "sant", 'i', 0 },  { "gl", 0, 1 },       { "agl", 0, 1 },
    { "degl", 0, 1 },    { "dagl", 0, 1 },     { "negl", 0, 1 },
    { "sugl", 0, 1 },    { "m", 0, 1 },        { "t", 0, 1 },
    { "s", 0, 1 },       { "c", 0, 1 },        { "v", 0, 1 },
    { "un", 'a', 0x100 },
    { { 0, 0, 0, 0, 0, 0 }, 0, 0 },
};

static const zi8ExclPair lbl_81617EA4[] = {
    { "d", 0, 1 }, { "l", 0, 1 }, { "m", 0, 1 },
    { "t", 0, 1 }, { "s", 0, 1 }, { "n", 0, 1 },
    { { 0, 0, 0, 0, 0, 0 }, 0, 0 },
};

ziS32 Zi8SetParentalControls(ziU8 a, ziPtr __zi8_work_data) {
    Zi8LogError(0x2C9, __zi8_work_data);
    return 0;
}

ziU8 Zi8IsWordW2(ziWChar* w, ziU8 len, ziPtr __zi8_work_data) {
    ziU8 b;
    ziU8 ret;

    b = ZI_WORK->unk_0x1983;
    ret = Zi8IsWordW(w, len, ZI_WORK);
    ZI_WORK->unk_0x1983 = b;
    return ret;
}

ziS32 Zi8SetHighlightedWordW(ziWChar* w, ziU8 a, ziU8 b, ziPtr __zi8_work_data) {
    ziS32 i;
    ziS32 j;

    i = 0;
    while (w[i] != 0) {
        i++;
    }
    if (i >= 0x40) {
        Zi8LogError(0x131, __zi8_work_data);
        return 0;
    }
    if (i == 1 && w[0] >= 0xEFF1 && w[0] <= 0xF010) {
        Zi8LogError(0x640, __zi8_work_data);
        return 0;
    }
    ZI_WORK->unk_0x1879 = 1;
    if (ZI_WORK->unk_0x18FC == 0 || ZI_WORK->unk_0x1984 == 0) {
        ZI_WORK->unk_0x1C[0] = 1;
        if (ZI_WORK->unk_0x18FC == 0) {
            if (ZI_WORK->unk_0x1878 == 0 || i == ZI_WORK->unk_0x1878) {
                ZI_WORK->unk_0x1C[0] = 2;
                if (Zi8IsWordW2(w, a, __zi8_work_data) != 0) {
                    ZI_WORK->unk_0x1879 = a;
                } else {
                    if (b != a && b != 7 && Zi8IsWordW2(w, b, __zi8_work_data) != 0) {
                        ZI_WORK->unk_0x1879 = b;
                    }
                }
            }
        } else {
            j = 0;
            while (j < ZI_WORK->unk_0x1980) {
                if (ZI_WORK->unk_0x18FE[j] != w[j]) {
                    break;
                }
                j++;
            }
            if (ZI_WORK->unk_0x1878 == 0 || i == ZI_WORK->unk_0x1878) {
                if (j == ZI_WORK->unk_0x1980) {
                    if (Zi8IsWordW2(&w[j], ZI_WORK->unk_0x1983, __zi8_work_data) != 0) {
                        ZI_WORK->unk_0x1879 = ZI_WORK->unk_0x1983;
                    }
                }
            }
        }
        ZI_WORK->unk_0x1C[0] = 0;
    }
    for (j = 0; j <= i; j++) {
        ZI_WORK->unk_0x187A[j] = w[j];
    }
    Zi8LogError(0x64, __zi8_work_data);
    return 1;
}

static void ZiprocessHighlightedW(ziU8 a, ziPtr __zi8_work_data) {
    ziS32 i;
    ziS32 j;
    ziS32 k;

    i = 0;
    while (ZI_WORK->unk_0x187A[i] != 0) {
        i++;
    }
    if (i + 1 != a) {
        return;
    }
    if (i == ZI_WORK->unk_0x1878 && ZI_WORK->unk_0x1877 != 0) {
        ZI_WORK->unk_0x1876 = (ziU8)i;
        for (j = 0; j < i; j++) {
            ZI_WORK->unk_0x18FE[j] = ZI_WORK->unk_0x187A[j];
        }
    }
    if (ZI_WORK->unk_0x18FC == 0) {
        if ((ZI_WORK->unk_0x1878 == 0 || i == ZI_WORK->unk_0x1878) &&
            ZI_WORK->unk_0x1879 > 1) {
            for (j = 0; j < i; j++) {
                ZI_WORK->unk_0x18FE[j] = ZI_WORK->unk_0x187A[j];
            }
            ZI_WORK->unk_0x1980 = (ziU8)j;
            ZI_WORK->unk_0x1983 = ZI_WORK->unk_0x1879;
        }
    } else {
        if (ZI_WORK->unk_0x1984 == 0 && ZI_WORK->unk_0x1879 > 1) {
            j = 0;
            k = ZI_WORK->unk_0x1980;
            while (k < i) {
                ZI_WORK->unk_0x1988[j++] = ZI_WORK->unk_0x187A[k++];
            }
            ZI_WORK->unk_0x1A0A = (ziU8)j;
        }
    }
    if (i == 1 && ZI_WORK->unk_0x1A90 != 0) {
        if (ZI_WORK->unk_0x187A[0] >= 0xEFF1 && ZI_WORK->unk_0x187A[0] <= 0xF010) {
            ZI_WORK->unk_0x1A90 = 0;
        } else {
            ZI_WORK->unk_0x1A90 = ZI_WORK->unk_0x187A[0];
        }
    }
    if (i == ZI_WORK->unk_0x1B14 &&
        Zi8ConvertWC2Key(ZI_WORK->unk_0x187A[i - 1], ZI_WORK->unk_0x1983,
                         __zi8_work_data) != 0xEFF1) {
        for (j = 0; j <= i; j++) {
            ZI_WORK->unk_0x1A92[j] = ZI_WORK->unk_0x187A[j];
        }
        ZI_WORK->unk_0x1A92[j] = 0;
    }
    ZI_WORK->unk_0x1879 = 0;
}

ziU8 Zi8IsVowel(ziU8 a, ziU16 c) {
    switch (a) {
    case 0x58:
        switch (c) {
        case 0x61:
        case 0x65:
        case 0x68:
        case 0x69:
        case 0x6F:
        case 0x75:
        case 0xE0:
        case 0xE8:
        case 0xE9:
        case 0xED:
        case 0xEF:
        case 0xF2:
        case 0xF3:
        case 0xFA:
        case 0xFC:
            goto ret1;
        default:
            return 0;
        }
    case 0x2F:
    case 0x04:
    case 0x3F:
    case 0x40:
        switch (c & 0xFFDF) {
        case 0x41:
        case 0x45:
        case 0x48:
        case 0x49:
        case 0x4F:
        case 0x55:
        case 0xC0:
        case 0xC8:
        case 0xC9:
        case 0xCC:
        case 0xD2:
        case 0xD9:
            goto ret1;
        case 0x59:
        case 0xC2:
        case 0xC6:
        case 0xCA:
        case 0xCB:
        case 0xCE:
        case 0xCF:
        case 0xD4:
        case 0xDB:
            if (a != 0x2F) {
                goto ret1;
            }
            return 0;
        default:
            if (a != 0x2F) {
                goto chk;
            }
            return 0;
chk:
            switch (c) {
            case 0xFF:
            case 0x152:
            case 0x153:
            case 0x178:
                goto ret1;
            default:
                goto ret0;
            }
        }
    default:
        goto ret1;
    }
ret0:
    return 0;
ret1:
    return 1;
}

ziS32 Zi8ITspecialExclusion(ziWChar* w, ziS32 len) {
    ziS32 i;
    const zi8ExclPair* p;
    ziWChar* s;

    s = w - len;
    len = len - 1;
    p = IT_EXCLUDE_PAIRS;
    while (p->a != 0) {
        i = 0;
        while (i < len) {
            if (s[i] != p->k[i]) {
                break;
            }
            i++;
        }
        if (i >= len && p->k[i] == 0) {
            if (Zi8IsVowel(0x2F, w[0]) == 0) {
                return 1;
            }
            return 0;
        }
        p++;
    }
    return 0;
}

ziS32 Zi8_814659E8(ziWChar* w, ziS32 len) {
    ziS32 i;
    const zi8ExclPair* p;
    ziWChar* s;

    s = w - len;
    len = len - 1;
    p = IT_EXCLUDE_PAIRS;
    while (p->a != 0) {
        i = 0;
        while (i < len) {
            if (s[i] != p->k[i]) {
                break;
            }
            i++;
        }
        if (i >= len && p->k[i] == 0) {
            if (Zi8IsVowel(0x58, w[0]) == 0) {
                return 1;
            }
            return 0;
        }
        p++;
    }
    return 0;
}

ziS32 Zi8IsAlphaPunct(ziWChar c) {
    if (c == 0xEFF1 || (c >= 0x21 && c <= 0x40) || (c >= 0x5B && c <= 0x60) ||
        (c >= 0x7B && c <= 0x7E)) {
        return 1;
    }
    return 0;
}

static ziS32 ZiIsLetterHyphen(ziWChar c, ziPtr __zi8_work_data) {
    if (c == ZI_WORK->unk_0x1874 || c == 0x2D || c == 0x2E || c == 0x40) {
        return 1;
    }
    return 0;
}

void Zi8ChangeWordCase(ziWChar* w, ziU8 lang, ziPtr __zi8_work_data) {
    ziS32 dir;

    dir = 0;
    if (ZI_WORK->unk_0x1C[2] == 3) {
        Zi8ChangeCharCase(1, w++, lang, __zi8_work_data);
    } else {
        if (ZI_WORK->unk_0x1C[2] == 1) {
            dir = 1;
        }
    }
    while (*w != 0) {
        Zi8ChangeCharCase(dir, w++, lang, __zi8_work_data);
    }
}
