#include <zi8clib/zi8is.h>
#include <zi8clib/zierror.h>

extern ziU8 Zi8LangSupported(ziU8 lang ZI_NEED_WORK);
extern ziU16 Zi8GetTableCount(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);
extern ziU32 Zi8GetTableAddress(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);
extern ziU8 _Zi8GetCandidates(ziGetParam* getParam ZI_NEED_WORK);
extern ziPtr Zi8Memset(ziPtr destination, ziU32 value, ziS32 count);

ziU8 Zi8GetZHCharSet(ziPtr __zi8_work_data) {
    ziU8 charSet = 0;
    ziU8 bak;
    ziU16 v0;
    ziU16 v1;
    ziU16 v2;
    ziU32 addr;
    ziU8* p;
    ziWChar candBuf[0x10];
    ziGetParam getParam;

    Zi8LogError(0x64, __zi8_work_data);
    if (Zi8LangSupported(ZI8_LANG_ZH, __zi8_work_data) == 0) {
        Zi8ReplaceLastError(0x26C, __zi8_work_data);
        return 0;
    }
    if (Zi8GetTableCount(ZI8_LANG_ZH, 10, __zi8_work_data) != 0) {
        bak = ZI_WORK->subLanguage;
        ZI_WORK->subLanguage = 1;
        addr = Zi8GetTableAddress(ZI8_LANG_ZH, 10, __zi8_work_data);
        p = (ziU8*)addr;
        v0 = (ziU16)((ziU16)p[0] | ((ziU16)p[1] << 8));
        ZI_WORK->subLanguage = 0;
        addr = Zi8GetTableAddress(ZI8_LANG_ZH, 10, __zi8_work_data);
        p = (ziU8*)addr;
        v1 = (ziU16)((ziU16)p[2] | ((ziU16)p[3] << 8));
        v2 = (ziU16)((ziU16)p[4] | ((ziU16)p[5] << 8));
        ZI_WORK->subLanguage = bak;
        if (v0 != 0) {
            if (v0 > 0x4E20) {
                charSet |= 8;
            } else {
                charSet |= 1;
            }
        }
        if (v1 != 0) {
            if (v1 > 0x2710) {
                charSet |= 2;
            } else {
                charSet |= 0x10;
            }
        }
        if (v2 != 0) {
            charSet |= 4;
        }
        return charSet;
    }

    Zi8Memset(&getParam, 0, 0x2C);
    getParam.language = ZI8_LANG_ZH;
    getParam.context = 1;
    getParam.getOptions = 0;
    getParam.candidates = candBuf;
    getParam.maxCandidates = 1;
    getParam.subLanguage = 1;
retry:
    getParam.getMode = 0;
    if (_Zi8GetCandidates(&getParam, __zi8_work_data) != 0) {
        charSet |= getParam.subLanguage;
        goto next;
    }
    getParam.getMode = 1;
    if (_Zi8GetCandidates(&getParam, __zi8_work_data) != 0) {
        charSet |= getParam.subLanguage;
        goto next;
    }
    getParam.getMode = 2;
    if (_Zi8GetCandidates(&getParam, __zi8_work_data) != 0) {
        charSet |= getParam.subLanguage;
    }
next:
    if (getParam.subLanguage == 1) {
        getParam.subLanguage = 4;
        goto retry;
    }
    if (getParam.subLanguage == 4) {
        getParam.subLanguage = 2;
        goto retry;
    }
    return charSet;
}

ziBool Zi8IsComponent(ziWChar ch ZI_NEED_WORK) {
    if (ch >= 0xEF10 && ch < 0xF305) {
        return 1;
    }
    return 0;
}

ziBool Zi8IsCharacter(ziWChar ch ZI_NEED_WORK) {
    ziU16 count;
    ziU8 hi;
    ziU8 lo;

    ziU32 addr;
    ziU8* table;
    ziU16 i;

    if (ch >= 0x3105 && ch <= 0x3129) {
        return 1;
    }
    switch (ch) {
    case 0x2C7:
    case 0x2C9:
    case 0x2CA:
    case 0x2CB:
    case 0x2D9:
        return 1;
    }
    switch (ch) {
    case 0x3002:
    case 0xFF01:
    case 0xFF0C:
    case 0xFF1F:
        return 1;
    }
    hi = (ziU8)((ch >> 8) & 0xFF);
    lo = (ziU8)ch;
    count = Zi8GetTableCount(ZI8_LANG_ZH, 0, ZI_WORK);
    addr = Zi8GetTableAddress(ZI8_LANG_ZH, 0, ZI_WORK);
    table = (ziU8*)addr;
    for (i = 0; i < count; i++) {
        if (table[6] == hi && table[7] == lo) {
            return 1;
        }
        table += 0xC;
    }
    return 0;
}
