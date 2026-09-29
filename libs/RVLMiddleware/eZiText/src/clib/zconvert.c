#include <zi8clib/zconvert.h>
#include <zi8clib/zierror.h>
#include <zi8clib/zitypes.h>

extern ziU16 Zi8GetTableCount(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);
extern ziU32 Zi8GetTableAddress(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);
extern ziWChar Zi8ConvertUC2UserKey(ziChar ch, ziU8 language ZI_NEED_WORK);

typedef struct zi8CvrtEntry {
    ziU16 first;
    ziU16 last;
    const ziU8* map;
} zi8CvrtEntry;

const zi8CvrtEntry Zi8CvrtTables[4] = {
    {0, 0, ZI8_NULL},
    {0, 0, ZI8_NULL},
    {0, 0, ZI8_NULL},
    {0, 0, ZI8_NULL},
};

ziWChar Zi8ConvertUC2WC(ziChar ch, ziU8 language ZI_NEED_WORK) {
    ziU16 last;
    ziU32 tableAddr;
    ziU8* p;
    ziU16 first;
    const zi8CvrtEntry* t;
    const ziU8* map;
    if ((ziU8)ch == 0) {
        Zi8LogError(0x133, ZI_WORK);
        return 0;
    }

    if ((ziU16)Zi8GetTableCount(language, 6, ZI_WORK) != 0) {
        tableAddr = Zi8GetTableAddress(language, 6, ZI_WORK);
        if (tableAddr == ZI8_NULL) {
            Zi8LogError(0x6A4, ZI_WORK);
            return 0;
        }

        p = (ziU8*)tableAddr;
        first = (ziU16)(((ziU16)p[0] << 8) | (ziU16)p[1]);
        last = (ziU16)(((ziU16)p[2] << 8) | (ziU16)p[3]);
        if ((ziU8)ch < first || (ziU8)ch > last) {
            Zi8LogError(0x132, ZI_WORK);
            return 0;
        }
        p += ((ziU8)ch - first) * 2 + 8;
        Zi8LogError(0x64, ZI_WORK);
        return (ziWChar)(((ziU16)p[0] << 8) | (ziU16)p[1]);
    } else {
        t = Zi8CvrtTables;
        if (t == ZI8_NULL) {
            Zi8LogError(0x6A4, ZI_WORK);
            return 0;
        }
        if ((ziU8)ch < t->first || (ziU8)ch > t->last) {
            Zi8LogError(0x132, ZI_WORK);
            return 0;
        }
        map = t->map;
        Zi8LogError(0x64, ZI_WORK);
        return *(ziU16*)(map + ((ziU8)ch - t->first) * 2);
    }
}

ziChar Zi8ConvertWC2UC(ziWChar ch, ziU8 language ZI_NEED_WORK) {
    ziU32 tableAddr;
    ziU8* p;
    const zi8CvrtEntry* map;
    ziU16 count;
    ziU16 i;
    ziU16 first;
    ziU16 last;
    ziU16 val;
    const ziU8* m;

    if ((ziU16)ch == 0) {
        Zi8LogError(0x133, ZI_WORK);
        return 0;
    }

    if ((ziU16)Zi8GetTableCount(language, 7, ZI_WORK) != 0) {
        tableAddr = Zi8GetTableAddress(language, 7, ZI_WORK);
        if (tableAddr == ZI8_NULL) {
            Zi8LogError(0x6AE, ZI_WORK);
            return 0;
        }

        p = (ziU8*)tableAddr;
        count = (ziU16)(((ziU16)p[0] << 8) | (ziU16)p[1]);
        p += 8;
        for (i = 0; i < count; i++) {
            first = (ziU16)(((ziU16)p[0] << 8) | (ziU16)p[1]);
            last = (ziU16)(((ziU16)p[2] << 8) | (ziU16)p[3]);
            if ((ziU16)ch < first || (ziU16)ch > last) {
                p += 8;
                continue;
            }
            val = (ziU16)(((ziU16)p[6] << 8) | (ziU16)p[7]);
            if (first == last) {
                Zi8LogError(0x64, ZI_WORK);
                return (ziChar)val;
            }
            Zi8LogError(0x64, ZI_WORK);
            return ((ziU8*)tableAddr)[val + (ziU16)ch - first + 8];
        }
        Zi8LogError(0x6C2, ZI_WORK);
        return 0;
    }

    map = (const zi8CvrtEntry*)Zi8CvrtTables[1].map;
    if (map == ZI8_NULL) {
        Zi8LogError(0x6AE, ZI_WORK);
        return 0;
    }
    count = Zi8CvrtTables[1].first;
    for (i = 0; i < count; i++) {
        if ((ziU16)ch >= map[i].first && (ziU16)ch <= map[i].last) {
            Zi8LogError(0x64, ZI_WORK);
            if (map[i].first == map[i].last) {
                return (ziChar)(ziU32)map[i].map;
            }
            m = map[i].map;
            return m[(ziU16)ch - map[i].first];
        }
    }
    Zi8LogError(0x6C2, ZI_WORK);
    return 0;
}

ziWChar Zi8ConvertUC2Key(ziChar ch, ziU8 language ZI_NEED_WORK) {
    ziU32 tableAddr;
    ziU8* p;
    const zi8CvrtEntry* map;
    ziU16 count;
    ziU16 i;
    ziU16 first;
    ziU16 last;
    ziU16 result;
    const ziU8* m;

    result = 0;

    if ((ziU8)ch == 0) {
        Zi8LogError(0x133, ZI_WORK);
        return 0;
    }

    if (((struct __zi8_work_data_s*)__zi8_work_data)->userKeys[language] !=
        ZI8_NULL) {
        return Zi8ConvertUC2UserKey(ch, language, ZI_WORK);
    }

    if ((ziU16)Zi8GetTableCount(language, 8, ZI_WORK) != 0) {
        tableAddr = Zi8GetTableAddress(language, 8, ZI_WORK);
        if (tableAddr == ZI8_NULL) {
            Zi8LogError(0x6B8, ZI_WORK);
            return 0;
        }

        p = (ziU8*)tableAddr;
        count = (ziU16)(((ziU16)p[0] << 8) | (ziU16)p[1]);
        p += 8;
        for (i = 0; i < count; i++) {
            first = (ziU16)(((ziU16)p[0] << 8) | (ziU16)p[1]);
            last = (ziU16)(((ziU16)p[2] << 8) | (ziU16)p[3]);
            if ((ziU8)ch < first || (ziU8)ch > last) {
                p += 8;
                continue;
            }
            result = (ziU16)(((ziU16)p[6] << 8) | (ziU16)p[7]);
            if (first != last) {
                p = (ziU8*)tableAddr + result + ((ziU8)ch - first) * 2 + 8;
                result = (ziU16)(((ziU16)p[0] << 8) | (ziU16)p[1]);
            }
            break;
        }
    } else {
        map = (const zi8CvrtEntry*)Zi8CvrtTables[2].map;
        if (map == ZI8_NULL) {
            Zi8LogError(0x6B8, ZI_WORK);
            return 0;
        }
        count = Zi8CvrtTables[2].first;
        for (i = 0; i < count; i++) {
            if ((ziU8)ch >= map[i].first && (ziU8)ch <= map[i].last) {
                m = map[i].map;
                if (map[i].first == map[i].last) {
                    result = (ziChar)(ziU32)m;
                } else {
                    result = *(ziU16*)(m + ((ziU8)ch - map[i].first) * 2);
                }
                break;
            }
        }
    }

    if ((ziU16)result == 0) {
        Zi8LogError(0x6C2, ZI_WORK);
        return 0xFFF1;
    }
    Zi8LogError(0x64, ZI_WORK);
    return result;
}

ziWChar Zi8ConvertWC2Key(ziWChar ch, ziU8 language ZI_NEED_WORK) {
    return Zi8ConvertUC2Key((ziChar)Zi8ConvertWC2UC(ch, language, ZI_WORK),
                          language, ZI_WORK);
}
