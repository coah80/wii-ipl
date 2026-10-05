#ifndef ZI8_CLIB_TYPES_H
#define ZI8_CLIB_TYPES_H

typedef unsigned char ziU8;
typedef unsigned short ziU16;
typedef unsigned long ziU32;

typedef signed char ziS8;
typedef signed short ziS16;
typedef signed long ziS32;

typedef unsigned char ziChar;
typedef unsigned short ziWChar;
typedef unsigned char ziBool;
typedef void* ziPtr;

#define ZI8_FALSE 0
#define ZI8_TRUE 1

#define ZI8_NULL 0

#ifndef ZI8_LANGS_DEFINED
#define ZI8_LANGS_DEFINED
#define ZI8_LANG_NONE 0
#define ZI8_LANG_ZH 1
#define ZI8_LANG_PY 2
#define ZI8_LANG_DE 5
#define ZI8_LANG_SV 9
#define ZI8_LANG_FI 10
#define ZI8_LANG_NO 11
#define ZI8_LANG_DA 12
#define ZI8_LANG_NL 13
#define ZI8_LANG_EL 14
#define ZI8_LANG_TR 15
#define ZI8_LANG_JP 16
#define ZI8_LANG_KO 18
#define ZI8_LANG_AR 19
#define ZI8_LANG_IN 20
#define ZI8_LANG_MS 21
#define ZI8_LANG_PL 22
#define ZI8_LANG_CS 23
#define ZI8_LANG_IW 24
#define ZI8_LANG_VI 25
#define ZI8_LANG_SK 26
#define ZI8_LANG_EU 27
#define ZI8_LANG_BN 28
#define ZI8_LANG_HR 29
#define ZI8_LANG_CH 30
#define ZI8_LANG_ET 31
#define ZI8_LANG_HI 32
#define ZI8_LANG_HU 33
#define ZI8_LANG_LV 34
#define ZI8_LANG_LT 35
#define ZI8_LANG_FA 36
#define ZI8_LANG_PA 37
#define ZI8_LANG_RO 38
#define ZI8_LANG_RU 39
#define ZI8_LANG_SL 41
#define ZI8_LANG_TH 42
#define ZI8_LANG_UR 43
#define ZI8_LANG_UK 44
#define ZI8_LANG_TL 45
#define ZI8_LANG_IT 47
#define ZI8_LANG_IS 48
#define ZI8_LANG_BG 49
#define ZI8_LANG_MR 53
#define ZI8_LANG_SW 54
#define ZI8_LANG_GU 55
#define ZI8_LANG_KN 56
#define ZI8_LANG_TA 57
#define ZI8_LANG_ENUK 58
#define ZI8_LANG_ENAM 59
#define ZI8_LANG_ENPRC 60
#define ZI8_LANG_ENTW 61
#define ZI8_LANG_ENHK 62
#define ZI8_LANG_FREU 63
#define ZI8_LANG_FRCA 64
#define ZI8_LANG_ESSA 65
#define ZI8_LANG_ESEU 66
#define ZI8_LANG_PTEU 67
#define ZI8_LANG_PTBZ 68
#define ZI8_LANG_SRLA 69
#define ZI8_LANG_SRCY 70
#define ZI8_LANG_KM 71
#define ZI8_LANG_TE 72
#define ZI8_LANG_ML 73
#define ZI8_LANG_SI 74
#define ZI8_LANG_AF 75
#define ZI8_LANG_ST 76
#define ZI8_LANG_XH 77
#define ZI8_LANG_ZU 78
#define ZI8_LANG_SQ 79
#define ZI8_LANG_MK 80
#define ZI8_LANG_AZ 81
#define ZI8_LANG_KK 82
#define ZI8_LANG_UZ 83
#define ZI8_LANG_HA 84
#define ZI8_LANG_IG 85
#define ZI8_LANG_YO 86
#define ZI8_LANG_PYP 119
#define ZI8_LANG_PYS 120
#define ZI8_LANG_ZYP 121
#define ZI8_LANG_ZYS 122
#define ZI8_LANG_SP2 123
#define ZI8_LANG_PY2 124
#define ZI8_LANG_ZY2 125
#define ZI8_LANG_ZHP 126
#define ZI8_LANG_ARB 127
#define ZI8_LANG_MAX 128
#endif  // ZI8_LANGS_DEFINED

typedef struct ziFuzzyPYPairs {
    int ziDefault : 1;

    int cANDch : 1;
    int sANDsh : 1;
    int zANDzh : 1;

    int anANDang : 1;
    int enANDeng : 1;
    int inANDing : 1;

    int nANDl : 1;
    int lANDr : 1;
    int fANDh : 1;
} ziFuzzyPYPairs;

typedef struct ziFuzzyZYPairs {
    int ziDefault : 1;

    int cANDch : 1;
    int sANDsh : 1;
    int zANDzh : 1;

    int anANDang : 1;
    int enANDeng : 1;

    int nANDl : 1;
    int lANDr : 1;
    int fANDh : 1;

    int rANDn : 1;
    int bANDp : 1;
    int gANDk : 1;
    int dANDt : 1;

    int reserved : 20;
} ziFuzzyZYPairs;

typedef struct _ziGetParam {
    ziU8 language;     // 0x00
    ziU8 getMode;      // 0x01
    ziU8 subLanguage;  // 0x02
    ziU8 context;      // 0x03
    ziU8 getOptions;   // 0x04

    ziWChar* elements;  // 0x08
    ziU8 elementCount;  // 0x0C

    ziWChar* currentWord;  // 0x10
    ziU8 wordCharCount;    // 0x14

    ziWChar* candidates;     // 0x18
    ziU8 maxCandidates;      // 0x1C
    ziWChar firstCandidate;  // 0x1E
    ziU8 count;              // 0x20  (EZTXGetParam.count)

    ziU8 letters;     // 0x21
    ziU8 completion;  // 0x22  (EZTXGetParam.completion)
    ziU8* scratch;    // 0x24
    ziU32 reserved;   // 0x28
} ziGetParam;

typedef struct _ziLanguageEntry {
    ziU8 language;    // 0x00
    ziU8* tableData;  // 0x04
} ziLanguageEntry;

typedef struct _zi8DawgRec {
    ziU8* node;
    ziU32 attr;
    ziU16 key;
    ziU8 reserved[2];
    ziU8* back;
} zi8DawgRec;

typedef struct _zi8DawgCtx {
    ziU8 lang;       // 0x00
    ziU8 key;        // 0x01
    ziU16 cnt;       // 0x02
    ziU16 cap;       // 0x04
    ziU8 reserved[2];
    ziU8* characters;       // 0x08
    ziU8* characterFlags;       // 0x0C
    ziU8* table;     // 0x10
    ziU8* keyCodes;       // 0x14
    zi8DawgRec recs[0x32];  // 0x18
    ziU32 endNode; // 0x338
} zi8DawgCtx;

typedef struct _ziUwdNode {
    struct _ziUwdNode* next;
    ziU8* word;
} ziUwdNode;

struct __zi8_work_data_s {
    ziU8 getcPhase;  // 0x00
    ziU8 countOnly;  // 0x01
    ziU8 reservedAlignment[2];
    ziLanguageEntry* langEntries;  // 0x04
    ziU8 initializationState;
    ziU8 dictionaryFlags;
    ziU8 maxWordLength;
    ziU8 reservedSettings;
    ziU32 targetCount;  // 0x0C
    ziU32 maxCandidateCount;
    ziU16 errorCode;
    ziU8 cangjieEnabled;  // 0x16
    ziU8 zhPudMinPrefix;
    ziU8 subLanguage;  // 0x18
    ziU8 reservedSubLanguage;
    ziU16 separator;  // 0x1A
    ziU8 searchModes[3];
    ziU8 ignoreCase;
    ziU16 duplicateCharacters[0x40];
    ziU16 duplicateOrdinalCache[0x42];
    ziU16* zhUwdPointers[1];
    ziU8* reservedUwdPointer;
    ziU8 uwdPtrCount;  // 0x12C
    ziU8 zhPudCount;
    ziU8 uwdPrioritySort;  // 0x12E
    ziU8 reservedUwdState;
    ziPtr uwdDicts[2];  // 0x130
    ziU8 uwdDictCount;  // 0x138
    ziU8 reservedUwdAlignment[3];
    ziU32 uwdSkipCount;
    ziU8 uwdContextEnabled;
    ziU8 uwdContextRecord[0x43];
    ziU8 uwdContextAlternateCase[0x43];
    ziU8 uwdCount;         // 0x1C7
    ziUwdNode uwdNodes[0x20];  // 0x1C8
    ziUwdNode* uwdList;    // 0x2C8
    ziU32 pudTable[0x10];  // 0x2CC
    ziU8 pudCount;         // 0x30C
    ziU8 reservedPudAlignment[3];
    ziU32 pudWordAddress;
    ziU32 pudWordCount;
    ziU32 pudWordIndex;
    ziU8 pdRemoveOpt;      // 0x31C
    ziU8 reservedPudState;
    ziU8 pudStopAtSpace;
    ziU8 reservedOemAlignment;
    ziU8 (*oemMatch)(ziU16 idx, ziWChar* buf, ziU8 len, ziPtr data); //0x320
    ziU16 oemLen;  //0x324
    ziU8 reservedOemLengthAlignment[2];
    ziU32 oemIdx;  //0x328
    ziPtr oemData; //0x32C
    ziU8 reservedOemState[8];
    ziU32 candidateBufferHead;
    ziU8 candidateBufferTail[0x1FC];
    ziU8 language;  // 0x538
    ziU8 duplicateCount;
    ziU8 duplicateWordOrder[0x40];
    ziWChar duplicateBuffer[0x641];
    ziPtr customKeyMap;
    ziPtr userKeys[0x83];  // 0x1200
    ziU8 wordLengthSettings[4];
    ziU32 formats;  // 0x1410
    ziU8 dictionaryCountStorage[4];
    ziU8 formatCount;
    ziU8 reservedFormatAlignment;
    ziU16 capacity;  // 0x141A
    ziU8 forceAltGraph;  // 0x141C  (lang FI + group 0xC -> graphTableId 0x10)
    ziU8 advanceGroup;  // 0x141D  (nonzero: skip first dawg group)
    ziU8 graphTableId;  // 0x141E
    ziU8 maxCnt;  // 0x141F
    ziU8 reservedDawgAlignment[4];
    zi8DawgCtx dawgCtx;    // 0x1424
    ziU8 dawgSearchState[4];    // 0x1760
    ziU8* groupPtr;       // 0x1764
    ziU8 dawgGroupIndex;
    ziU8 reservedDawgStorage[0x81];
    ziU16 matchOffset;  // 0x17EA
    ziU8 dawgFallbackUsed;
    ziU8 reservedDawgGroupAlignment[3];
    ziU8* dawgGroup;  // 0x17F0
    ziWChar dawgWord[0x40];  // 0x17F4..0x1874
    ziU16 letterHyphen;
    ziU8 prefixLength;
    ziU8 prefixEnabled;
    ziU8 requiredLength;
    ziU8 highlightedLanguage;
    ziWChar highlightedWord[0x41];
    ziU8 suffixMode;
    ziU8 suffixState;
    ziWChar prefix[0x41];
    ziU8 prefixCount;
    ziU8 previousPrefixCount;
    ziU8 prefixElementCount;
    ziU8 wordLanguage;
    ziU8 suffixLocked;
    ziU8 previousSuffixCount;
    ziU8 suffixElementCount;
    ziU8 suffixStatus;
    ziWChar suffix[0x41];
    ziU8 suffixCount;
    ziU8 alternatePrefixState[0x85];
    ziWChar singleCharacter;
    ziWChar rememberedWord[0x41];
    ziU8 rememberedCount;
    ziU8 wordSearchState[3];
    ziU16* unicodeMap;     // 0x1B18
    ziU16 unicodeRange1Min; // 0x1B1C
    ziU16 unicodeRange1Max; // 0x1B1E
    ziU16 unicodeRange2Min; // 0x1B20
    ziU16 unicodeRange2Max; // 0x1B22
    ziU8 unicodeMapSubLang; // 0x1B24
    ziU8 reservedUnicodeAlignment[3];
    union {
        ziU32 word;
        struct {
            ziU32 msb : 1;
        } bits;
    } pyFuzzy;  // 0x1B28
    union {
        ziU32 word;
        struct {
            ziU32 msb : 1;
        } bits;
    } zyFuzzy;
    ziU8 koAltTables;  // 0x1B30
    ziU8 reservedKoreanAlignment;
    ziU16 candidateStateWordA;
    ziU16 candidateStateWordB;
    ziU16 candidateStateWordC;
    ziU16 initializationWordA;
    ziU8 candidateStateByteA;
    ziU8 candidateStateByteB;
    ziU8 candidateStateByteC;
    ziU8 candidateStateByteD;
    ziU8 reservedCandidateStateA;
    ziU8 reservedCandidateStateB;
    ziU16 initializationWordB;
    ziU8 reservedTail[2];
};

typedef struct ziMatchParam {
    ziU8 count;          // 0x00
    ziU8 recordMasks[0xC];      // 0x01
    ziU8 recordValues[0xC];      // 0x0D
    ziU8 prefixMasks[4];       // 0x19
    ziU8 prefixValues[4];       // 0x1D
    ziU8 pad_0x21;       // 0x21
    ziU16 componentIndex;       // 0x22
    ziU8 length;         // 0x24
    ziU8 nCand;          // 0x25
    ziWChar phon[0x10];  // 0x26
    ziWChar phon2[0x10]; // 0x46
    ziWChar first;       // 0x66
    ziWChar first2;      // 0x68
    ziWChar comp;        // 0x6A
    ziU8 nSeg;           // 0x6C
    ziU8 segmentMasks[16][12];  // 0x6D
    ziU8 segmentValues[16][12];  // 0x12D
    ziU8 pad_0x1ED;      // 0x1ED
} ziMatchParam;

#define ZI_WORK ((struct __zi8_work_data_s*)__zi8_work_data)
#define ZI_NEED_WORK , ziPtr __zi8_work_data

#endif  // ZI8_CLIB_TYPES_H
