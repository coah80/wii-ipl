#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>
#include <zi8clib/zmtkey.h>
#include <zi8clib/zconvert.h>

extern ziU16 Zi8GetTableCount(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);
extern ziU32 Zi8GetTableAddress(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);

static ziU8 Zi8_81484484(ziU16 key, ziU16* out ZI_NEED_WORK) {
    if (key == 0xEFFA) {
        *out = 0;
    } else if (key >= 0xEFF1 && key <= 0xEFF9) {
        *out = key - 0xEFF0;
    } else if (key >= 0xEFFB && key <= 0xF010) {
        *out = key - 0xEFF1;
    } else {
        return 0;
    }

    return 1;
}

static ziU8 ziNumKeysWithChars(ziU8 lang ZI_NEED_WORK) {
    ziU16 count;
    ziU8* table;
    ziU32 sum;
    ziU32 i;

    count = Zi8GetTableCount(lang, 0x1E, ZI_WORK);
    table = (ziU8*)Zi8GetTableAddress(lang, 0x1E, ZI_WORK);
    if (count == 0) {
        return 0xC;
    }

    for (i = (sum = 0); (ziU16)i < 0x20; i++) {
        sum += table[(ziU16)i];
    }

    if ((ziU16)count >= (ziU16)sum * 4 + 0x20) {
        return 0x20;
    }
    return 0xC;
}

static ziU8 Zi8getKeyLayout(ziU8 lang, ziU16 key, ziWChar* layout,
                            ziU8 mode ZI_NEED_WORK) {
    ziS32 table = 0;
    ziU16 count;
    ziU8 keyCount;
    ziU16 cnt;
    ziU16 i;
    ziU32* keyMap;
    ziWChar* chars;

    keyCount = ziNumKeysWithChars(lang, ZI_WORK);
    Zi8LogError(0x64, ZI_WORK);
    *layout = 0;
    if (ZI_WORK->userKeys[lang] != 0) {
        keyMap = (ziU32*)ZI_WORK->userKeys[lang];

        if (Zi8_81484484(key, &key, ZI_WORK) == 0) {
            return 0;
        }
        chars = (ziWChar*)(&keyMap[key])[0x20];
        for (i = 0; chars[(ziU16)i] != 0; i++) {
            layout[(ziU16)i] = chars[(ziU16)i];
        }
        layout[(ziU16)i] = 0;
        return 1;
    }

    if (mode != 1) {
        count = Zi8GetTableCount(lang, 0x1D, ZI_WORK);
        if (count != 0) {
            table = Zi8GetTableAddress(lang, 0x1D, ZI_WORK);
        } else {
            goto d30;
        }
        goto d38;
    }
d30:
    count = Zi8GetTableCount(lang, 0x1E, ZI_WORK);
    if (count != 0) {
        table = Zi8GetTableAddress(lang, 0x1E, ZI_WORK);
    }
d38:
    if (table == 0) {
        Zi8ReplaceLastError(0x962, ZI_WORK);
        return 0;
    }

    if (Zi8_81484484(key, &key, ZI_WORK) == 0 || key >= keyCount) {
        Zi8ReplaceLastError(0x12C, ZI_WORK);
        return 0;
    }

    for (i = (count = 0); (ziU16)i < key; i++) {
        count += ((ziU8*)table)[(ziU16)i];
    }
    if ((cnt = (ziU16)(ziU8)((ziU8*)table)[key]) == 0) {
        return 0;
    }

    table += keyCount + (ziU16)count * 2;
    for (i = 0; (ziU16)i < cnt; i++) {
        layout[(ziU16)i] = ((ziU8*)table)[(ziU16)i * 2] | ((ziU16)((ziU8*)table)[(ziU16)i * 2 + 1] << 8);
    }
    layout[(ziU16)i] = 0;
    return 1;
}

ziBool Zi8ChangeCharCase(ziBool upper, ziWChar* ch, ziU8 language ZI_NEED_WORK) {
    ziPtr* pTab = 0;
    ziU8* pKeys = 0;
    ziWChar* from;
    ziWChar* to;
    ziU32 i;
    ziU16 acc;
    ziU16 cnt;
    ziS16 dir;
    ziU16 key;
    ziS32 j;
    ziU8 done = 0;
    ziU8 keyCount = 0x20;

    Zi8LogError(0x64, ZI_WORK);
    if (ZI_WORK->userKeys[language] != 0) {
        pTab = (ziPtr*)ZI_WORK->userKeys[language];
    } else if (ZI_WORK->unk_0x11FC != 0) {
        pTab = (ziPtr*)ZI_WORK->unk_0x11FC;
    } else {
        cnt = Zi8GetTableCount(language, 0x1E, ZI_WORK);
        if (cnt != 0) {
            pKeys = (ziU8*)Zi8GetTableAddress(language, 0x1E, ZI_WORK);
            keyCount = ziNumKeysWithChars(language, ZI_WORK);
        } else {
            Zi8ReplaceLastError(0x138D, ZI_WORK);
            return 0;
        }
    }

    if (pTab != 0) {
        for (j = 0; done == 0 && j < keyCount; j++) {
            if (upper != 0) {
                from = (ziWChar*)(&pTab[j])[0x20];
                to = (ziWChar*)pTab[j];
            } else {
                from = (ziWChar*)pTab[j];
                to = (ziWChar*)(&pTab[j])[0x20];
            }
            if (from != 0 && to != 0) {
                for (i = 0; (ziU16)from[i] != 0; i++) {
                    if (*ch == (ziU16)from[i]) {
                        *ch = (ziU16)to[i];
                        done = 1;
                        break;
                    }
                }
            }
        }
    } else {
        if (pKeys != 0) {
            acc = 0;
            for (j = 0; j < keyCount; j++) {
                acc += pKeys[j];
            }
            pKeys += keyCount;
            dir = 1;
            if (upper == 0) {
                pKeys += acc * 2;
                dir = -1;
            }
            for (j = 0; j < acc; j++) {
                cnt = (ziU16)(pKeys[j * 2] | ((ziU16)pKeys[j * 2 + 1] << 8));
                if (cnt == *ch) {
                    pKeys += dir * (acc * 2);
                    *ch = (ziU16)(pKeys[j * 2] | ((ziU16)pKeys[j * 2 + 1] << 8));
                    done = 1;
                    break;
                }
            }
        }
    }

    if (done == 0) {
        key = 0;
        if (upper != 0) {
            if ((*ch >= 0x61 && *ch <= 0x7A) || (*ch >= 0xF1 && *ch <= 0xF6) ||
                (*ch >= 0xF8 && *ch <= 0xFE) || (*ch >= 0xE0 && *ch <= 0xEF)) {
                key = *ch - 0x20;
            } else if (*ch == 0xFF) {
                key = 0x178;
            }
        } else {
            if ((*ch >= 0x41 && *ch <= 0x5A) || (*ch >= 0xD1 && *ch <= 0xD6) ||
                (*ch >= 0xD8 && *ch <= 0xDE) || (*ch >= 0xC0 && *ch <= 0xCF)) {
                key = *ch + 0x20;
            } else if (*ch == 0x178) {
                key = 0xFF;
            }
        }

        if (key != 0) {
            if (Zi8ConvertWC2UC(key, language, ZI_WORK) != 0) {
                *ch = key;
                done = 1;
            }
        }
    }

    return done;
}
