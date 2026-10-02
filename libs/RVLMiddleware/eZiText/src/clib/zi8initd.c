#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>

extern void Zi8Memset(ziPtr p, ziU32 v, ziU32 len);
extern void Zi8SetLatinSearchOrder(ziU32 a, ziU8 b ZI_NEED_WORK);
extern void ZADP_Zi8SetPDremoveOpt(ziU8 a ZI_NEED_WORK);
extern ziU16 Zi8GetFormatVersion(ziU8 a ZI_NEED_WORK);
extern void Zi8ZHsetZYfuzzyPairs(ziU32* a ZI_NEED_WORK);
extern void Zi8ZHsetPYfuzzyPairs(ziU32* a ZI_NEED_WORK);
extern void Zi8SetParentalControls(ziU8 a ZI_NEED_WORK);

ziU8 Zi8InitializeDynamic(ziLanguageEntry* langEntries ZI_NEED_WORK) {
    ziU32 zyFuzzy;
    ziU32 pyFuzzy;
    ziU32* pzyFuzzy;
    ziU32* ppyFuzzy;

    Zi8Memset(__zi8_work_data, 0, 0x1B44);
    ZI_WORK->unk_0x08 = 1;
    ZI_WORK->unk_0x09 = 1;
    ZI_WORK->unk_0x0A = 0xFF;
    ZI_WORK->unk_0x10 = 0x64;
    *(ziU16*)&ZI_WORK->unk_0x0C = 0xFFFF;
    ZI_WORK->unk_0x1A = 0x20;
    ZI_WORK->unk_0x1C[2] = 0;
    ZI_WORK->unk_0x1B30 = 0;
    ZI_WORK->unk_0x1B3A = 0;
    ZI_WORK->unk_0x1B36 = 0;
    ZI_WORK->unk_0x1B32 = 0;
    ZI_WORK->unk_0x1B34 = 0;
    ZI_WORK->unk_0x1B3B = 0;
    ZI_WORK->unk_0x1B3C = 0;
    ZI_WORK->unk_0x1B40 = 0;
    ZI_WORK->unk_0x1B38 = 0;
    ZI_WORK->langEntries = langEntries;
    if (ZI_WORK->langEntries == ZI8_NULL) {
        Zi8LogError(0x578, ZI_WORK);
        return 0;
    }
    if (ZI_WORK->langEntries->language == 0) {
        Zi8LogError(0x582, ZI_WORK);
        return 0;
    }
    ZI_WORK->unk_0x1874 = 0x2D;
    ZI_WORK->language = 0;
    ZI_WORK->unk_0x1C[3] = 0;
    ZI_WORK->unk_0x141A = 0x100;
    Zi8SetLatinSearchOrder(0, 0, ZI_WORK);
    ZADP_Zi8SetPDremoveOpt(1, ZI_WORK);
    ZI_WORK->unk_0x17 = 5;
    ZI_WORK->unk_0x16 = Zi8GetFormatVersion(1, ZI_WORK) & 2;
    ZI_WORK->unk_0x1B28.bits.msb = 1;
    ZI_WORK->unk_0x1B2C.bits.msb = 1;
    zyFuzzy = ZI_WORK->unk_0x1B2C.word;
    pzyFuzzy = &zyFuzzy;
    Zi8ZHsetZYfuzzyPairs(pzyFuzzy, ZI_WORK);
    pyFuzzy = ZI_WORK->unk_0x1B28.word;
    ppyFuzzy = &pyFuzzy;
    Zi8ZHsetPYfuzzyPairs(ppyFuzzy, ZI_WORK);
    Zi8SetParentalControls(2, ZI_WORK);
    Zi8LogError(0x64, ZI_WORK);
    return 1;
}

ziU8 Zi8IsZicorpSignature(ziU16* p, ziU16 len) {
    if ((ziU16)len > 6 && p[0] == 0x7A && p[1] == 0x69 && p[2] == 0x63 &&
        p[3] == 0x6F && p[4] == 0x72 && p[5] == 0x70) {
        return 1;
    }
    if ((ziU16)len > 6 && p[0] == 0x39 && p[1] == 0x34 && p[2] == 0x32 &&
        p[3] == 0x36 && p[4] == 0x37 && p[5] == 0x37) {
        return 1;
    }
    return 0;
}
