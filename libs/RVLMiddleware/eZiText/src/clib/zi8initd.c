#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>

extern ziPtr Zi8Memset(ziPtr destination, ziU32 value, ziS32 count);
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
    ZI_WORK->initializationState = 1;
    ZI_WORK->dictionaryFlags = 1;
    ZI_WORK->maxWordLength = 0xFF;
    ZI_WORK->maxCandidateCount = 0x64;
    *(ziU16*)&ZI_WORK->targetCount = 0xFFFF;
    ZI_WORK->separator = 0x20;
    ZI_WORK->searchModes[2] = 0;
    ZI_WORK->koAltTables = 0;
    ZI_WORK->candidateStateByteA = 0;
    ZI_WORK->candidateStateWordC = 0;
    ZI_WORK->candidateStateWordA = 0;
    ZI_WORK->candidateStateWordB = 0;
    ZI_WORK->candidateStateByteB = 0;
    ZI_WORK->candidateStateByteC = 0;
    ZI_WORK->initializationWordB = 0;
    ZI_WORK->initializationWordA = 0;
    ZI_WORK->langEntries = langEntries;
    if (ZI_WORK->langEntries == ZI8_NULL) {
        Zi8LogError(0x578, ZI_WORK);
        return 0;
    }
    if (ZI_WORK->langEntries->language == ZI8_LANG_NONE) {
        Zi8LogError(0x582, ZI_WORK);
        return 0;
    }
    ZI_WORK->letterHyphen = 0x2D;
    ZI_WORK->language = ZI8_LANG_NONE;
    ZI_WORK->searchModes[3] = 0;
    ZI_WORK->capacity = 0x100;
    Zi8SetLatinSearchOrder(0, 0, ZI_WORK);
    ZADP_Zi8SetPDremoveOpt(1, ZI_WORK);
    ZI_WORK->zhPudMinPrefix = 5;
    ZI_WORK->cangjieEnabled = Zi8GetFormatVersion(ZI8_LANG_ZH, ZI_WORK) & 2;
    ZI_WORK->pyFuzzy.bits.msb = 1;
    ZI_WORK->zyFuzzy.bits.msb = 1;
    zyFuzzy = ZI_WORK->zyFuzzy.word;
    pzyFuzzy = &zyFuzzy;
    Zi8ZHsetZYfuzzyPairs(pzyFuzzy, ZI_WORK);
    pyFuzzy = ZI_WORK->pyFuzzy.word;
    ppyFuzzy = &pyFuzzy;
    Zi8ZHsetPYfuzzyPairs(ppyFuzzy, ZI_WORK);
    Zi8SetParentalControls(2, ZI_WORK);
    Zi8LogError(0x64, ZI_WORK);
    return 1;
}

ziU8 Zi8IsZicorpSignature(ziU16* p, ziU16 len ZI_NEED_WORK) {
    if (len > 6 && p[0] == 0x7A && p[1] == 0x69 && p[2] == 0x63 &&
        p[3] == 0x6F && p[4] == 0x72 && p[5] == 0x70) {
        return 1;
    }
    if (len > 6 && p[0] == 0x39 && p[1] == 0x34 && p[2] == 0x32 &&
        p[3] == 0x36 && p[4] == 0x37 && p[5] == 0x37) {
        return 1;
    }
    return 0;
}
