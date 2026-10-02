#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>

extern ziU16 Zi8GetTableCount(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);
extern ziU32 Zi8GetTableAddress(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);

typedef struct { ziU8 b[0xC]; } ziE12;

#define WORKP ((struct __zi8_work_data_s*)__zi8_work_data)

ziU16 Zi8Uni2Ptr(ziU16 ch, ziE12* buf ZI_NEED_WORK) {
    ziU8 hi;
    ziU8 lo;
    ziU16 count;
    ziU32 table;
    ziU32 table2;
    ziU16 i;
    ziU8* e;
    ziU8* p;

    hi = (ziU8)(((ziU16)ch >> 8) & 0xFF);
    lo = (ziU8)ch;
    count = Zi8GetTableCount(1, 0, __zi8_work_data);
    table = Zi8GetTableAddress(1, 0, __zi8_work_data);
    table2 = Zi8GetTableAddress(1, 1, __zi8_work_data);
    if (buf == ZI8_NULL) {
        for (i = 0; i < 0x40; i++) {
            if (ch == WORKP->unk_0x20[i]) {
                i = WORKP->unk_0xA0[i];
                e = (ziU8*)table + i * 0xC;
                if (i >= count) {
                    break;
                }
                if (hi != e[6] || lo != e[7]) {
                    break;
                }
                p = (ziU8*)(table2 +
                            (((e[9] & 0xF) << 16) |
                             (e[0xB] | (e[0xA] << 8))));
                if (WORKP->cangjieEnabled != 0) {
                    switch (p[0] & 7) {
                    case 2:
                        p += 2;
                        break;
                    case 3:
                    case 4:
                        p += 3;
                        break;
                    case 5:
                        p += 4;
                        break;
                    default:
                        p += 1;
                        break;
                    }
                }
                if ((p[0] & 0x80) == 0) {
                    break;
                }
                if (buf != ZI8_NULL) {
                    *buf = *(ziE12*)e;
                }
                return i;
            }
        }
    }
    e = (ziU8*)table;
    if (WORKP->unicodeMap != ZI8_NULL && WORKP->unicodeMapSubLang == WORKP->subLanguage) {
        if ((ziU16)ch >= WORKP->unicodeRange1Min && (ziU16)ch <= WORKP->unicodeRange1Max) {
            i = (ziU16)(ch - WORKP->unicodeRange1Min);
            goto map;
        }
        if ((ziU16)ch >= WORKP->unicodeRange2Min && (ziU16)ch <= WORKP->unicodeRange2Max) {
            i = (ziU16)(WORKP->unicodeRange1Max + (ch - WORKP->unicodeRange2Min) -
                        WORKP->unicodeRange1Min + 1);
            goto map;
        }
        return 0xFFFF;
    map:
        i = WORKP->unicodeMap[i];
        if (i != 0xFFFF) {
            e = (ziU8*)table + i * 0xC;
            if (hi == e[6] && lo == e[7]) {
                if (buf != ZI8_NULL) {
                    *buf = *(ziE12*)e;
                }
                return i;
            }
        }
        return 0xFFFF;
    }
    i = 0;
    while (i < count) {
        if (lo == e[7] && hi == e[6]) {
            if (buf != ZI8_NULL) {
                *buf = *(ziE12*)e;
            }
            return i;
        }
        e += 0xC;
        i++;
    }
    return 0xFFFF;
}

ziU16 Zi8Uni2Ord(ziU16 ch ZI_NEED_WORK) {
    return Zi8Uni2Ptr(ch, ZI8_NULL, __zi8_work_data);
}

ziU16 Zi8Ord2Uni(ziU16 ord ZI_NEED_WORK) {
    ziU8* p;

    if ((ziU16)ord >= Zi8GetTableCount(1, 0, __zi8_work_data)) {
        Zi8LogError(0x132, __zi8_work_data);
        return 0;
    }
    p = (ziU8*)Zi8GetTableAddress(1, 0, __zi8_work_data);
    p += ord * 0xC;
    Zi8LogError(0x64, __zi8_work_data);
    return (ziU16)(((ziU16)p[6] << 8) + p[7]);
}

ziU16 Zi8Ord2Ord(ziU16 ord ZI_NEED_WORK) {
    ziU32 table;
    ziU16 count;
    ziU8* p;

    count = Zi8GetTableCount(1, 0, __zi8_work_data);
    table = Zi8GetTableAddress(1, 0, __zi8_work_data);
    if (ord == 0 || (ziU16)ord >= count) {
        Zi8LogError(0x132, __zi8_work_data);
        return ord;
    }
    p = (ziU8*)table + (ord - 1) * 0xC;
    while (ord != 0) {
        if (p[6] != p[0x12] || p[7] != p[0x13]) {
            break;
        }
        p -= 0xC;
        ord--;
    }
    Zi8LogError(0x64, __zi8_work_data);
    return ord;
}
