#include <zi8clib/zi8cgetc.h>
#include <zi8clib/zi8space.h>
#include <zi8clib/zierror.h>

typedef unsigned int Zi8UInt;

extern Zi8UInt Zi8Ord2Ord(ziU16 ordinal, ziPtr work);
extern ziU32 Zi8WCharCount(ziWChar* word, ziPtr work);

static Zi8UInt Zi8SetFindCand(ziU8* foundCandidates, Zi8UInt ordinal, ziPtr work) {
    Zi8UInt found;
    ordinal = Zi8Ord2Ord(ordinal, work);
    found = (ziU8)((1 << ((int)(ordinal & 0xffff) % 8)) &
                  foundCandidates[(int)(ordinal & 0xffff) / 8]);
    foundCandidates[(int)(ordinal & 0xffff) / 8] |=
        1 << ((int)(ordinal & 0xffff) % 8);
    return found;
}

ziWChar* ZiGetNextPhonetic(ziWChar* spelling, ziWChar* end ZI_NEED_WORK) {
    while (*spelling && *spelling != ZI_WORK->separator && *spelling != 0xF360 && spelling < end) {
        ++spelling;
    }
    if (!*spelling || spelling == end) {
        return ZI8_NULL;
    }
    ++spelling;
    if (!*spelling || spelling == end) {
        return ZI8_NULL;
    }
    return spelling;
}

int ZiPartialMatch(ziWChar* spelling, ziWChar* spellingEnd,
                   ziWChar* candidate, ziWChar* candidateEnd,
                   ziU16 phoneticIndex ZI_NEED_WORK) {
    if (spelling == spellingEnd || candidate == candidateEnd || !*spelling || !*candidate) {
        return 1;
    }
    while (*spelling != ZI_WORK->separator && *spelling != 0xF360) {
        if (*candidate == ZI_WORK->separator || *candidate == 0xF360) {
            break;
        }
        if (*spelling != *candidate) {
            return 0;
        }
        ++spelling;
        ++candidate;
        if (spelling == spellingEnd || candidate == candidateEnd || !*spelling || !*candidate) {
            return 1;
        }
    }
    return 1;
}

int ZiMatchZHSpelling(ziPtr dictionary, ziWChar* candidate, ziWChar* spelling,
                      ziU8 spellingLength, ziU16 phoneticIndex ZI_NEED_WORK) {
    ziWChar* candidateCursor;
    ziWChar* spellingCursor;
    int index;
    int matches;
    int candidateLength;
    ziWChar spacedSpelling[64];
    ziWChar spacedCandidate[64];
    matches = 1;
    candidateLength = Zi8WCharCount(candidate, __zi8_work_data);
    if (!candidate || !spellingLength) {
        return matches;
    }
    for (index = 0; index < spellingLength; ++index) {
        if (!candidate[index] || candidate[index] != spelling[index]) {
            matches = 0;
            break;
        }
    }
    if (!matches) {
        spacedSpelling[0] = 0;
        spacedCandidate[0] = 0;
        if (!Zi8ZHaddSpace(spelling, spellingLength, spacedSpelling, 64, __zi8_work_data)) {
            return 0;
        }
        if (!Zi8ZHaddSpace(candidate, candidateLength, spacedCandidate, 64, __zi8_work_data)) {
            return 0;
        }
        spellingCursor = spacedSpelling;
        candidateCursor = spacedCandidate;
        while (phoneticIndex) {
            candidateCursor = ZiGetNextPhonetic(candidateCursor, spacedCandidate + 64, __zi8_work_data);
            if (!candidateCursor) {
                return 0;
            }
            --phoneticIndex;
        }
        matches = 1;
        while (spellingCursor && candidateCursor) {
            if (!ZiPartialMatch(spellingCursor, spacedSpelling + 64,
                                candidateCursor, spacedCandidate + 64,
                                phoneticIndex, __zi8_work_data)) {
                return 0;
            }
            spellingCursor = ZiGetNextPhonetic(spellingCursor, spacedSpelling + 64, __zi8_work_data);
            candidateCursor = ZiGetNextPhonetic(candidateCursor, spacedCandidate + 64, __zi8_work_data);
        }
    }
    return matches;
}
typedef struct {
    ziU8 countOnly;
    ziU8 maxWordLength;
    ziU8 lookupMode;
    ziU8 dictionaryMode;
    ziWChar* dictionary;
    ziU32 dictionaryFlags;
    int maxResults;
    ziU16 capacity;
    ziU8 minimumLength;
    ziU8 candidateMode;
} ZiChineseOptions;

typedef struct {
    ziU8 settings[12];
    ziU16 maxOrdinalCount;
    ziU8 settingsTail[12];
    ziWChar separator;
    ziU8 state[4];
    ziWChar duplicateCharacters[64];
    ziWChar duplicateOrdinals[64];
    ziU8 duplicateIndex;
} ZiChineseWork;

typedef struct {
    ziU8 flags;
    ziU8 phonetics[11];
} ZiChineseRecord;

extern ziPtr Zi8GetTableAddress(ziU8 language, ziU8 table, ziPtr work);
extern ziU16 Zi8GetTableCount(ziU8 language, ziU8 table, ziPtr work);
extern ziU8 Zi8IsDupWChar(ziWChar character, ziPtr work);
extern ziU8 Zi8IsDupWordW(ziWChar* word, ziU8 length, ziPtr work);
extern ziWChar Zi8Ord2Uni(ziU16 ordinal, ziPtr work);
extern ziU8 Zi8MatchPhonetic(ziU8* phonetics, ZiChineseRecord* records,
                            ziPtr indexTable, ziU16 indexCount, ziPtr dictionary,
                            ZiChineseRecord* record, ziU16* mask, ziU16* match,
                            ziU16* length, ZiChineseRecord** matchedRecord,
                            int* matchedIndex, ziU8 wordMode, ziU8 partial,
                            ziU8 oneCharacter, ziU16 excludedMask,
                            ziU16 excludedMatch, ziU8 charset, ziU8 options,
                            ziU16 ordinal, ziU16* tone, ziU8 spellingOnly,
                            ziPtr work);

typedef union {
    Zi8UInt bits;
    ziU8 bytes[4];
} ZiChinesePattern;

extern ziU8 Zi8GetFormatVersion(ziU8 language, ziPtr work);
extern ziU8 Zi8GetZHCharSet(ziPtr work);
extern int Zi8PrepareMatch(ziGetParam* request, ziMatchParam* match, ziU8 mode, ziPtr work);
extern const ziU8 zi8CangjieCodes[25];
extern const ziWChar ziPuncts[4];
extern const ziWChar ziTones[4];
const ziWChar zi8tones[4];
extern ziU8 Zi8GetZHuwdPtr(ziU8** entries, ziU16* count, ziPtr work);
extern ziBool Zi8IsComponent(ziWChar character, ziPtr work);
extern ziBool Zi8IsCharacter(ziWChar character, ziPtr work);
extern ziU8 Zi8MatchOEMdata(ziWChar* currentWord, ziU8 length, ziU8 language,
                           ziWChar* output, ziU16 capacity, ziU8 mode, ziU8 next, ziPtr work);
extern ziU16 Zi8Uni2Ord(ziWChar character, ziPtr work);
extern int Zi8GetPCode(ziU8* table, ziU8* record);
extern ziU16 Zi8MatchAltSound(ziPtr table, ziU16 count, ziPtr phonetics,
                             ziU16 ordinal, ziU16 mask, ziU16 value, ziU8 flags, ziPtr work);
extern ziU32 Zi8SecMatchChar(ziPtr record, ziU8* dictionary, ziMatchParam* match, ziU16* code, ziPtr work);
extern ziBool Zi8PriMatchNextChar(ziU8* record, ziU8 mask0, ziU8 value0, ziU8 mask1, ziU8 value1, ziU8 mask2, ziU8 value2, ziU8 mask3, ziU8 value3, ziU16* count, ziU8** result, ziU16* code, ziPtr work);
extern ziBool Zi8ExactMatchNextChar(ziU8* record, ziU8 mask0, ziU8 value0, ziU8 mask1, ziU8 value1, ziU8 mask2, ziU8 value2, ziU8 mask3, ziU8 value3, ziU16* count, ziU8** result, ziU16* code, ziPtr work);
extern ziBool Zi8PriMatchNextComp(ziU8* component, ziU8 mask0, ziU8 value0, ziU8 mask1, ziU8 value1, ziU8 mask2, ziU8 value2, ziU8 mask3, ziU8 value3, ziU16* count, ziU8** result, ziPtr work);
extern ziBool Zi8SecMatchComp(ziPtr component, ziMatchParam* match, ziPtr dictionary, ziPtr work);
extern void Zi8InitDupWordBuf(ziPtr work);
extern ziU8 Zi8MatchPUDdata_ZHS(ziWChar* word, ziU8 length, ziU8 language, ziWChar* spelling, ziU16 spellingCapacity, ziWChar* candidate, ziU16 candidateCapacity, ziU8 mode, ziU8 next, ziPtr work);
extern ziPtr Zi8Memcpy(ziPtr destination, ziPtr source, ziS32 length);
extern void Zi8Memset(ziPtr destination, int value, ziU32 size);

static int Zi8NewMatchPhonetic(ziGetParam* request, ZiChineseRecord* records,
                              ziPtr indexTable, ziU16 indexCount, ziPtr dictionary,
                              ZiChineseOptions* options, ziU16 mask, ziU16 match, ziU16 excludedMask,
                              ziU16 excludedMatch, ziU8 charset, ziU16 recordCount,
                              ziU16* skipCount, int* resultCount, ziU8* candidateCount,
                              int* outputCount, ziU8 wordMode, ziU8 useFoundCandidates,
                              ziU8 pinyin, ziU8* charsetTable, ziU8* charsetEntry,
                              ziU8 charsetFilter, ziWChar* output, ziPtr work);

static int zi8InternalGetZH(ziGetParam* request, ZiChineseOptions* options, ziPtr work) {
    ziMatchParam match = {0};
    ziWChar currentSpelling[64];
    ziWChar countOutput[64];
    ziWChar candidateWord[64];
    ZiChinesePattern phraseMasks[6];
    ZiChinesePattern phraseValues[6];
    ziU16 seenOrdinals[8];
    ziU8 matchMode;
    int index;
    ziWChar* currentWord;
    ziU8* userEntries;
    ziU16 ordinalIndex;
    ziU16 tableIndex;
    ziU16 phraseOrdinal;
    ziU16 userIndex;
    ziU16 userCount;
    ziU8 charset;
    ziU8 charsetFilter;
    int phase;
    int outputIndex;
    ziU16 candidateOrdinal;
    ziU16 alternateCharacter;
    ziU16 character;
    ziU16 relatedOrdinal;
    ziU16 isFirstCandidate;
    ziU16 duplicateIndex;
    ziU16 previousOrdinal;
    ziU16 ordinalCount;
    ziU16 remainingOrdinals;
    ziU16 firstOrdinal;
    ziU16 rangeIndex;
    ziU16 rangeCount;
    ziU16 phoneticMask;
    ziU16 phoneticMatch;
    ziU16 candidateCount;
    ziU16 recordCount;
    ziU16 componentCount;
    ziU16 alternateCount;
    ziU16 componentIndex;
    ziU8 componentFrequency;
    ziU8 groupHeader;
    ziU8 groupCount;
    ziU8 remainingWordLength;
    ziU8 recordFrequency;
    ziU8 emittedCount;
    ziU8 seenCount;
    ziU8 emittedWords;
    ziU8* record;
    ziU8* componentCursor;
    ziU8* componentTable;
    ziU8* componentOrdinals;
    ziU8* phoneticTable;
    ziU8* records;
    ziU8* alternateTable;
    ziU8* charsetTable;
    ziU8* componentCharsetTable;
    ziU8* ordinalTable;
    ziU8* phoneticGroups;
    ziU8* phraseTable;
    ziU8* frequencyTable;
    int totalResults;
    ziU8 switchedPhonetic;
    ziU8 candidateStatus;
    ziU8 phoneticRetry;
    ziU8 phoneticInput;
    ziU8 matchComponent;
    ziU8 exactLength;
    ziU8 trackDuplicates;
    ziU8 emitWords;
    ziU8 firstPhoneticPass;
    ziU8 exactPhrase;
    ziU8 singleCharacterPass;
    int outputLimit;
    ziU8* charsetEntry;
    ziU8 filteringMode;
    ziU16 skipCount;
    ziWChar* elements;
    ziU8 getOptions;
    ziWChar* output;
    ziU8 wordLength;
    ziU8 getMode;
    ziU8 requireFull;
    ziU8 prefixSearch;
    ziU8 wordMode;
    ziU8 resultFallback;
    ziU8* phraseEntry;
    ziU8 prefixLookup;
    ziU8 savedPudCount;
    ziU8 wordSearchPhase;
    ziU16 singleCharacterCount;
    ziU8 lastCharHigh;
    ziU8 lastCharLow;
    ziU8* relatedRecord;
    ziU8* alternateCursor;
    ziU8* frequencyCursor;
    ziU8 firstValue;
    ziU8 secondValue;
    ziU8 firstMask;
    ziU8 secondMask;
    ziU8 phoneticGroupWildcard;
    ziU8* alternateEntry;
    ziU8* frequencyEntry;

    charset = 0;
    charsetFilter = 0;
    phase = 0;
    outputIndex = 0;
    candidateOrdinal = 0;
    alternateCharacter = 0;
    character = 0;
    relatedOrdinal = 0;
    isFirstCandidate = 0;
    duplicateIndex = 0;
    previousOrdinal = 0;
    ordinalCount = 0;
    remainingOrdinals = 0;
    firstOrdinal = 0;
    rangeIndex = 0;
    rangeCount = 0;
    phoneticMask = 0;
    phoneticMatch = 0;
    candidateCount = 0;
    recordCount = 0;
    componentCount = 0;
    alternateCount = 0;
    componentIndex = 0;
    componentFrequency = 0;
    groupHeader = 0;
    groupCount = 0;
    remainingWordLength = 0;
    recordFrequency = 0;
    emittedCount = 0;
    seenCount = 0;
    emittedWords = 0;
    record = 0;
    componentCursor = 0;
    componentTable = 0;
    componentOrdinals = 0;
    phoneticTable = 0;
    records = 0;
    alternateTable = 0;
    charsetTable = 0;
    componentCharsetTable = 0;
    ordinalTable = 0;
    phoneticGroups = 0;
    phraseTable = 0;
    frequencyTable = 0;
    totalResults = 0;
    switchedPhonetic = 0;
    candidateStatus = 0;
    phoneticRetry = 0;
    phoneticInput = 0;
    matchComponent = 0;
    exactLength = 0;
    trackDuplicates = 0;
    emitWords = 0;
    firstPhoneticPass = 1;
    exactPhrase = 1;
    singleCharacterPass = 1;
    outputLimit = options->capacity - 64;
    charsetEntry = 0;
    filteringMode = 0;
    skipCount = request->firstCandidate;
    elements = request->elements;
    getOptions = request->getOptions;
    output = request->candidates;
    wordLength = request->wordCharCount;
    getMode = request->getMode;
    requireFull = getOptions & 0x40;
    prefixSearch = getOptions & 0x10;
    wordMode = getOptions & 0x20;
    resultFallback = 1;
    phraseEntry = 0;
    phraseMasks[5].bits = phraseMasks[4].bits = phraseMasks[3].bits =
        phraseMasks[2].bits = phraseMasks[1].bits = phraseMasks[0].bits = 0;
    phraseValues[5].bits = phraseValues[4].bits = phraseValues[3].bits =
        phraseValues[2].bits = phraseValues[1].bits = phraseValues[0].bits = 0;
    prefixLookup = 1;
    savedPudCount = 0;
    wordSearchPhase = 0;
    if (options->countOnly) {
        output = countOutput;
    }
    if (getMode == 16) {
        getMode = 0;
    } else if (getMode == 12) {
        getMode = 1;
    } else if (getMode == 13) {
        getMode = 2;
    } else if (getMode == 3 || getMode == 15 || getMode == 4) {
        if (request->elementCount) goto engine_finish;
        if (getMode == 4) getMode = 2;
        else getMode = 1;
    }
    if (Zi8GetFormatVersion(1, work) >= 8 && Zi8GetTableCount(1, 31, work)) {
        filteringMode = 1;
    }
    requireFull = getOptions & 0x40;
    prefixSearch = getOptions & 0x10;
    wordMode = getOptions & 0x20;
    getOptions &= ~0x10;
    getOptions &= ~0x20;
    getOptions &= ~0x40;
    if ((request->subLanguage & 0x80) || (request->subLanguage & 0x40)) {
        charset = 1;
    } else if (request->subLanguage & 8) {
        charset = 4;
    } else if ((request->subLanguage & 0x20) || (request->subLanguage & 0x10)) {
        charset = 2;
    }
    if (charset) {
        if (Zi8GetFormatVersion(1, work) >= 4) rangeIndex = Zi8GetTableCount(1, 21, work);
        else rangeIndex = 0;
        if (rangeIndex) charsetFilter = request->subLanguage;
        switch (charset) {
        case 1:
            if ((request->subLanguage & 0x40) || (Zi8GetZHCharSet(work) & 1)) rangeIndex = 0;
            break;
        case 2:
            if ((request->subLanguage & 0x10) || (Zi8GetZHCharSet(work) & 0x10)) rangeIndex = 0;
            break;
        case 4:
            if (request->subLanguage & 0x10) rangeIndex = 0;
            break;
        }
        if (rangeIndex) {
            rangeIndex = Zi8GetTableCount(1, 27, work);
            if (rangeIndex) componentCharsetTable = (ziU8*)Zi8GetTableAddress(1, 27, work);
            charsetTable = (ziU8*)Zi8GetTableAddress(1, 21, work);
        }
    } else {
        charset = request->subLanguage;
    }
    charset <<= 4;
    skipCount = request->firstCandidate;
    request->letters = 0;
    request->count = 0;
    request->unk_0x20 = 0;
    if (getMode != 7 && getMode != 10 && getMode != 8 && getMode != 9) {
        Zi8PrepareMatch(request, &match, 0, work);
    } else {
        if (!((struct __zi8_work_data_s*)work)->cangjieEnabled || request->elementCount > 6) {
            resultFallback = 0;
            goto engine_finish;
        }
        if (!request->elementCount) {
            getMode = 7;
        } else if ((request->elementCount == 1 || (request->elementCount == 2 && elements[1] == ' ')) &&
                   (getMode == 8 || getMode == 10)) {
            getMode = 7;
        } else if (getMode == 8 || getMode == 10 || getMode == 9) {
            phraseMasks[0].bytes[0] = phraseValues[0].bytes[0] = 0xFF;
            if (request->elementCount > 3 ||
                (request->elementCount > 2 && elements[2] != ' ')) {
                if (getMode == 9) {
                    resultFallback = 0;
                    goto engine_finish;
                }
                getMode = 7;
            } else {
                if (getMode == 10) getMode = 9;
                for (index = 0; index < 6; ++index) {
                    match.arr1[index] = match.arrD[index] = 0;
                }
                if (elements[0] >= 'A' && elements[0] <= 'Y') {
                    match.arr1[0] = 31;
                    match.arrD[0] = zi8CangjieCodes[elements[0] - 'A'];
                } else if (elements[0] >= 0xEFF2 && elements[0] <= 0xEFF9) {
                    match.arr1[0] = 28;
                    match.arrD[0] = (elements[0] - 0xEFF2) << 2;
                }
                if (request->elementCount > 1 && elements[1] != ' ') {
                    if (elements[1] >= 'A' && elements[1] <= 'Y') {
                        match.arr1[1] = 31;
                        match.arrD[1] = zi8CangjieCodes[elements[1] - 'A'];
                    } else if (elements[1] >= 0xEFF2 && elements[1] <= 0xEFF9) {
                        match.arr1[1] = 28;
                        match.arrD[1] = (elements[1] - 0xEFF2) << 2;
                    }
                    phraseMasks[1].bytes[0] = phraseValues[1].bytes[0] = 0xFF;
                    totalResults = (match.arr1[0] << 3) | (match.arr1[1] << 8) | 7;
                    phraseMasks[2].bytes[0] = totalResults;
                    phraseMasks[2].bytes[1] = (totalResults >> 8) & 0xff;
                    totalResults = (match.arrD[0] << 3) | (match.arrD[1] << 8) | 2;
                    phraseValues[2].bytes[0] = totalResults;
                    phraseValues[2].bytes[1] = (totalResults >> 8) & 0xff;
                    totalResults = (match.arr1[0] << 3) | (match.arr1[1] << 13) | 7;
                    phraseMasks[3].bytes[0] = totalResults;
                    phraseMasks[3].bytes[1] = (totalResults >> 8) & 0xff;
                    phraseMasks[3].bytes[2] = (totalResults >> 16) & 0xff;
                    totalResults = (match.arrD[0] << 3) | (match.arrD[1] << 13) | 3;
                    phraseValues[3].bytes[0] = totalResults;
                    phraseValues[3].bytes[1] = (totalResults >> 8) & 0xff;
                    phraseValues[3].bytes[2] = (totalResults >> 16) & 0xff;
                    totalResults = (match.arr1[0] << 3) | (match.arr1[1] << 18) | 7;
                    phraseMasks[4].bytes[0] = totalResults;
                    phraseMasks[4].bytes[1] = (totalResults >> 8) & 0xff;
                    phraseMasks[4].bytes[2] = (totalResults >> 16) & 0xff;
                    phraseMasks[4].bytes[3] = (Zi8UInt)totalResults >> 24;
                    totalResults = (match.arrD[0] << 3) | (match.arrD[1] << 18) | 4;
                    phraseValues[4].bytes[0] = totalResults;
                    phraseValues[4].bytes[1] = (totalResults >> 8) & 0xff;
                    phraseValues[4].bytes[2] = (totalResults >> 16) & 0xff;
                    phraseValues[4].bytes[3] = (Zi8UInt)totalResults >> 24;
                    totalResults = (match.arr1[0] << 3) | (match.arr1[1] << 23) | 7;
                    phraseMasks[5].bytes[0] = totalResults;
                    phraseMasks[5].bytes[1] = (totalResults >> 8) & 0xff;
                    phraseMasks[5].bytes[2] = (totalResults >> 16) & 0xff;
                    phraseMasks[5].bytes[3] = (Zi8UInt)totalResults >> 24;
                    totalResults = (match.arrD[0] << 3) | (match.arrD[1] << 23) | 5;
                    phraseValues[5].bytes[0] = totalResults;
                    phraseValues[5].bytes[1] = (totalResults >> 8) & 0xff;
                    phraseValues[5].bytes[2] = (totalResults >> 16) & 0xff;
                    phraseValues[5].bytes[3] = (Zi8UInt)totalResults >> 24;
                } else {
                    if (request->elementCount > 1) {
                        match.arr1[5] = 7;
                        match.arrD[5] = 1;
                    }
                    totalResults = (match.arr1[0] << 3) | match.arr1[5];
                    phraseMasks[1].bytes[0] = phraseMasks[2].bytes[0] =
                        phraseMasks[3].bytes[0] = phraseMasks[4].bytes[0] =
                        phraseMasks[5].bytes[0] = totalResults;
                    totalResults = (match.arrD[0] << 3) | match.arrD[5];
                    phraseValues[1].bytes[0] = phraseValues[2].bytes[0] =
                        phraseValues[3].bytes[0] = phraseValues[4].bytes[0] =
                        phraseValues[5].bytes[0] = totalResults;
                }
            }
        }
        for (index = 0; index < 6; ++index) {
            match.arr1[index] = match.arrD[index] = 0;
        }
        for (index = 0; index < request->elementCount; ++index) {
            if (elements[index] >= 'A' && elements[index] <= 'Y') {
                match.arr1[index] = 31;
                match.arrD[index] = zi8CangjieCodes[elements[index] - 'A'];
            } else if (elements[index] != '*') {
                if (elements[index] >= 0xEFF2 && elements[index] <= 0xEFF9) {
                    match.arr1[index] = 28;
                    match.arrD[index] = (elements[index] - 0xEFF2) << 2;
                }
                if (elements[index] == ' ') {
                    match.arr1[5] = 7;
                    match.arrD[5] = index;
                    if (!index || index + 1 != request->elementCount) {
                        resultFallback = 0;
                        goto engine_finish;
                    }
                    break;
                }
            }
        }
        if (index >= 6) {
            resultFallback = 0;
            goto engine_finish;
        }
        if (index) match.length = index;
        else match.length = 1;
        totalResults = match.arr1[5] | ((match.arr1[4] << 23) |
            ((match.arr1[3] << 18) | ((match.arr1[2] << 13) |
             ((match.arr1[0] << 3) | (match.arr1[1] << 8)))));
        match.arr19[0] = totalResults;
        match.arr19[1] = (totalResults >> 8) & 0xff;
        match.arr19[2] = (totalResults >> 16) & 0xff;
        match.arr19[3] = (Zi8UInt)totalResults >> 24;
        totalResults = match.arrD[5] | ((match.arrD[4] << 23) |
            ((match.arrD[3] << 18) | ((match.arrD[2] << 13) |
             ((match.arrD[0] << 3) | (match.arrD[1] << 8)))));
        match.arr1D[0] = totalResults;
        match.arr1D[1] = (totalResults >> 8) & 0xff;
        match.arr1D[2] = (totalResults >> 16) & 0xff;
        match.arr1D[3] = (Zi8UInt)totalResults >> 24;
    }
    totalResults = 0;
    if ((getMode == 1 || getMode == 2) && match.phon[0] == 0xFFFF && match.phon2[0] == 0xFFFF &&
        (getMode != 2 || request->elementCount != 1 || elements[0] < 0xF305 || elements[0] > 0xF329)) {
        match.nCand = 0;
        goto engine_finish;
    }
    if (match.length > 23) goto engine_finish;
    if (wordMode && (getMode == 1 || getMode == 2)) {
        wordMode = 0;
        for (index = 0; index < match.nCand; ++index) {
            ordinalIndex = 0;
            if (getMode == 1) {
                switch ((int)match.phon2[index] >> 9) {
                case 24: case 25:
                    if (((ziFuzzyPYPairs*)&((struct __zi8_work_data_s*)work)->pyFuzzy.word)->cANDch) ordinalIndex = 0xFDFF;
                    break;
                case 26: case 27:
                    if (((ziFuzzyPYPairs*)&((struct __zi8_work_data_s*)work)->pyFuzzy.word)->sANDsh) ordinalIndex = 0xFDFF;
                    break;
                case 28: case 29:
                    if (((ziFuzzyPYPairs*)&((struct __zi8_work_data_s*)work)->pyFuzzy.word)->zANDzh) ordinalIndex = 0xFDFF;
                    break;
                case 56: case 59:
                    if (((ziFuzzyPYPairs*)&((struct __zi8_work_data_s*)work)->pyFuzzy.word)->fANDh) ordinalIndex = 0xF9FF;
                    break;
                case 38:
                    if (((ziFuzzyPYPairs*)&((struct __zi8_work_data_s*)work)->pyFuzzy.word)->nANDl) ordinalIndex = 0xE5FF;
                    break;
                case 43:
                    if (((ziFuzzyPYPairs*)&((struct __zi8_work_data_s*)work)->pyFuzzy.word)->nANDl && ((ziFuzzyPYPairs*)&((struct __zi8_work_data_s*)work)->pyFuzzy.word)->lANDr) ordinalIndex = 0xE1FF;
                    else if (((ziFuzzyPYPairs*)&((struct __zi8_work_data_s*)work)->pyFuzzy.word)->lANDr) ordinalIndex = 0xF1FF;
                    else if (((ziFuzzyPYPairs*)&((struct __zi8_work_data_s*)work)->pyFuzzy.word)->nANDl) ordinalIndex = 0xE5FF;
                    break;
                case 44:
                    if (((ziFuzzyPYPairs*)&((struct __zi8_work_data_s*)work)->pyFuzzy.word)->lANDr) ordinalIndex = 0xF1FF;
                    break;
                }
            } else {
                switch ((int)match.phon2[index] >> 9) {
                case 24: case 25:
                    if (((ziFuzzyZYPairs*)&((struct __zi8_work_data_s*)work)->unk_0x1B2C.word)->cANDch) ordinalIndex = 0xFDFF;
                    break;
                case 26: case 27:
                    if (((ziFuzzyZYPairs*)&((struct __zi8_work_data_s*)work)->unk_0x1B2C.word)->sANDsh) ordinalIndex = 0xFDFF;
                    break;
                case 28: case 29:
                    if (((ziFuzzyZYPairs*)&((struct __zi8_work_data_s*)work)->unk_0x1B2C.word)->zANDzh) ordinalIndex = 0xFDFF;
                    break;
                case 56: case 59:
                    if (((ziFuzzyZYPairs*)&((struct __zi8_work_data_s*)work)->unk_0x1B2C.word)->fANDh) ordinalIndex = 0xF9FF;
                    break;
                case 52: case 55:
                    if (((ziFuzzyZYPairs*)&((struct __zi8_work_data_s*)work)->unk_0x1B2C.word)->bANDp) ordinalIndex = 0xF9FF;
                    break;
                case 60: case 63:
                    if (((ziFuzzyZYPairs*)&((struct __zi8_work_data_s*)work)->unk_0x1B2C.word)->gANDk) ordinalIndex = 0xF9FF;
                    break;
                case 38:
                    if (((ziFuzzyZYPairs*)&((struct __zi8_work_data_s*)work)->unk_0x1B2C.word)->nANDl && ((ziFuzzyZYPairs*)&((struct __zi8_work_data_s*)work)->unk_0x1B2C.word)->rANDn) ordinalIndex = 0xE1FF;
                    else if (((ziFuzzyZYPairs*)&((struct __zi8_work_data_s*)work)->unk_0x1B2C.word)->nANDl) ordinalIndex = 0xE5FF;
                    else if (((ziFuzzyZYPairs*)&((struct __zi8_work_data_s*)work)->unk_0x1B2C.word)->rANDn) ordinalIndex = 0xE3FF;
                    break;
                case 43:
                    if (((ziFuzzyZYPairs*)&((struct __zi8_work_data_s*)work)->unk_0x1B2C.word)->nANDl && ((ziFuzzyZYPairs*)&((struct __zi8_work_data_s*)work)->unk_0x1B2C.word)->lANDr) ordinalIndex = 0xE1FF;
                    else if (((ziFuzzyZYPairs*)&((struct __zi8_work_data_s*)work)->unk_0x1B2C.word)->lANDr) ordinalIndex = 0xF1FF;
                    else if (((ziFuzzyZYPairs*)&((struct __zi8_work_data_s*)work)->unk_0x1B2C.word)->nANDl) ordinalIndex = 0xE5FF;
                    break;
                case 44:
                    if (((ziFuzzyZYPairs*)&((struct __zi8_work_data_s*)work)->unk_0x1B2C.word)->rANDn && ((ziFuzzyZYPairs*)&((struct __zi8_work_data_s*)work)->unk_0x1B2C.word)->lANDr) ordinalIndex = 0xE1FF;
                    else if (((ziFuzzyZYPairs*)&((struct __zi8_work_data_s*)work)->unk_0x1B2C.word)->rANDn) ordinalIndex = 0xE3FF;
                    else if (((ziFuzzyZYPairs*)&((struct __zi8_work_data_s*)work)->unk_0x1B2C.word)->lANDr) ordinalIndex = 0xF1FF;
                    break;
                }
            }
            if (ordinalIndex) {
                wordMode = 1;
                match.phon2[index] &= ordinalIndex;
                match.phon[index] &= ordinalIndex;
                if (!index) {
                    match.first &= ordinalIndex;
                    match.first2 &= ordinalIndex;
                }
            }
            ordinalIndex = 0;
            if (getMode == 1) {
                switch (match.phon2[index] & 0x1F0) {
                case 0x10: case 0x80: case 0x100:
                    if (((ziFuzzyPYPairs*)&((struct __zi8_work_data_s*)work)->pyFuzzy.word)->anANDang) ordinalIndex = 0xFFF7;
                    break;
                case 0x180:
                    if (((ziFuzzyPYPairs*)&((struct __zi8_work_data_s*)work)->pyFuzzy.word)->enANDeng) ordinalIndex = 0xFFF7;
                    break;
                case 0x60:
                    if (((ziFuzzyPYPairs*)&((struct __zi8_work_data_s*)work)->pyFuzzy.word)->inANDing) ordinalIndex = 0xFFF7;
                    break;
                }
            } else {
                switch (match.phon2[index] & 0x1F0) {
                case 0x60: case 0xE0: case 0x160:
                    if (((ziFuzzyZYPairs*)&((struct __zi8_work_data_s*)work)->unk_0x1B2C.word)->anANDang) ordinalIndex = 0xFFF7;
                    break;
                case 0x70:
                    if (((ziFuzzyZYPairs*)&((struct __zi8_work_data_s*)work)->unk_0x1B2C.word)->enANDeng) ordinalIndex = 0xFFF7;
                    break;
                }
            }
            if (ordinalIndex) {
                wordMode = 1;
                match.phon2[index] &= ordinalIndex;
                match.phon[index] &= ordinalIndex;
                if (!index) {
                    match.first &= ordinalIndex;
                    match.first2 &= ordinalIndex;
                }
            }
        }
        if (request->elementCount) {
            if (getMode == 1) {
                phoneticTable = (ziU8*)Zi8GetTableAddress(1, 3, work);
                ordinalIndex = Zi8GetTableCount(1, 3, work);
            } else {
                phoneticTable = (ziU8*)Zi8GetTableAddress(1, 4, work);
                ordinalIndex = Zi8GetTableCount(1, 4, work);
            }
            rangeIndex = match.phon[match.nCand - 1] & 0xFFF8;
            rangeCount = match.phon2[match.nCand - 1] & 0xFFF8;
            for (index = 0; index < ordinalIndex; ++index) {
                phraseOrdinal = phoneticTable[index * 2] | ((ziU16)phoneticTable[index * 2 + 1] << 8);
                if (rangeCount == (phraseOrdinal & rangeIndex)) break;
            }
            if (index == ordinalIndex) goto engine_finish;
        }
    }
    if ((options->countOnly || getOptions == 2 || !request->elementCount || elements[0] == 0xEF09) &&
        getOptions != 1) firstPhoneticPass = 0;
    if (getMode == 5) {
        firstPhoneticPass = 1;
        if (match.nSeg > 1) goto engine_finish;
    }
    if (getMode == 0 && request->elementCount) {
        if (!(request->context & 0x10) &&
            (elements[request->elementCount - 1] == 0xF360 || match.nSeg > 1)) goto engine_finish;
        if (match.nSeg > 1) {
            firstPhoneticPass = 0;
            for (rangeIndex = 1; rangeIndex < match.nSeg; ++rangeIndex) {
                for (rangeCount = 4; rangeCount < 12; ++rangeCount) {
                    if (match.segs1[rangeIndex][rangeCount]) goto engine_finish;
                }
            }
        }
    }
    if (request->context & 0x10) {
        if (!output) {
            Zi8LogError(0x162, work);
            return 0;
        }
        emitWords = 1;
        if (request->count) request->count = request->elementCount;
    }
    if (!options->candidateMode) Zi8InitDupWordBuf(work);
    records = (ziU8*)Zi8GetTableAddress(1, 0, work);
    recordCount = Zi8GetTableCount(1, 0, work);
    phraseTable = (ziU8*)Zi8GetTableAddress(1, 1, work);
    if (getMode == 2 || getMode == 1) {
        alternateTable = (ziU8*)Zi8GetTableAddress(1, 5, work);
        alternateCount = Zi8GetTableCount(1, 5, work);
    }
    if ((request->context & 0x40) && Zi8GetFormatVersion(1, work) >= 1) {
        singleCharacterCount = Zi8GetTableCount(1, 15, work);
        if (singleCharacterCount) recordCount = singleCharacterCount;
    }
    if ((request->context & 0x80) && request->scratch) {
        Zi8Memset(request->scratch, 0, (recordCount + 7) / 8);
        trackDuplicates = 1;
    }
    switch (getMode) {
    case 1:
        phoneticTable = (ziU8*)Zi8GetTableAddress(1, 3, work);
        if (Zi8GetFormatVersion(1, work) >= 1 && match.nCand == 1 &&
            Zi8GetTableCount(1, 13, work) && Zi8GetTableCount(1, 14, work)) exactLength = 1;
        break;
    case 2:
        phoneticTable = (ziU8*)Zi8GetTableAddress(1, 4, work);
        if (Zi8GetFormatVersion(1, work) >= 1 && match.nCand == 1 &&
            Zi8GetTableCount(1, 13, work) && Zi8GetTableCount(1, 14, work)) exactLength = 1;
        break;
    case 0: case 5:
        if (!componentTable) {
            componentCount = Zi8GetTableCount(1, 7, work);
            componentOrdinals = (ziU8*)Zi8GetTableAddress(1, 7, work);
            componentTable = componentCursor = (ziU8*)Zi8GetTableAddress(1, 2, work);
            componentCursor += 8;
            --componentCount;
            componentIndex = componentCount;
            alternateCharacter = 0;
            phoneticRetry = 1;
        }
        break;
    }
    if (request->context & 2) {
        ordinalTable = (ziU8*)Zi8GetTableAddress(1, 8, work);
        ordinalCount = Zi8GetTableCount(1, 8, work);
    } else if (request->context & 4) {
        ordinalTable = (ziU8*)Zi8GetTableAddress(1, 9, work);
        ordinalCount = Zi8GetTableCount(1, 9, work);
    }
    if (match.nSeg > 1) {
        ordinalTable = 0;
        ordinalCount = 0;
    }
    if (ordinalCount > ((ZiChineseWork*)work)->maxOrdinalCount) {
        ordinalCount = ((ZiChineseWork*)work)->maxOrdinalCount;
    }
    if (!ordinalCount && getMode == 0 && request->elementCount == 1 && elements[0] == 0xEF00) {
        for (index = 0; index < sizeof(ziPuncts) / sizeof(ziPuncts[0]); ++index) {
            character = ziPuncts[index];
            if (!emitWords) {
                for (rangeIndex = 0; rangeIndex < emittedCount; ++rangeIndex) {
                    if (character == output[rangeIndex]) break;
                }
                if (rangeIndex < emittedCount) continue;
            } else if (Zi8IsDupWordW(&character, 1, work)) continue;
            if (skipCount) {
                --skipCount;
            } else {
                ++totalResults;
                if (!options->countOnly) {
                    if (emitWords) {
                        ++emittedCount;
                        output[outputIndex++] = character;
                        output[outputIndex++] = ' ';
                        if (outputIndex > outputLimit) goto engine_finish;
                    } else output[emittedCount++] = character;
                    if (emittedCount >= request->maxCandidates) goto engine_finish;
                } else if (totalResults >= options->maxResults) goto engine_finish;
            }
        }
    }
engine_search:
    if ((options->countOnly && getOptions != 5) ||
        (request->elementCount && Zi8IsComponent(elements[0], work)) ||
        (request->wordCharCount && !Zi8IsCharacter(request->currentWord[0], work)) ||
        getMode == 5 || ((getMode == 1 || getMode == 2) && match.nCand > 1) ||
        (!request->wordCharCount && !request->elementCount)) goto pud_search;
    matchMode = 0;
    while (Zi8MatchOEMdata(request->currentWord, request->wordCharCount, 1,
                          currentSpelling, 32, 0, matchMode, work)) {
        matchMode = 1;
        character = currentSpelling[request->wordCharCount];
        if (!Zi8IsCharacter(character, work) || (!emitWords && character == previousOrdinal)) continue;
        previousOrdinal = character;
        candidateOrdinal = Zi8Uni2Ord(character, work);
        if (candidateOrdinal == 0xFFFF) continue;
        record = records + candidateOrdinal * 12;
        candidateStatus = 0;
        switch (getMode) {
        case 7: case 8:
            phraseEntry = phraseTable + ((record[9] & 15) << 16 | (record[11] | record[10] << 8));
            if ((phraseEntry[0] & 7) >= match.length &&
                match.arr1D[0] == (match.arr19[0] & phraseEntry[0]) &&
                match.arr1D[1] == (match.arr19[1] & phraseEntry[1]) &&
                match.arr1D[2] == (match.arr19[2] & phraseEntry[2]) &&
                match.arr1D[3] == (match.arr19[3] & phraseEntry[3])) {
                candidateStatus = 1;
                break;
            }
            if (getMode == 7) break;
        case 9:
            phraseEntry = phraseTable + ((record[9] & 15) << 16 | (record[11] | record[10] << 8));
            index = phraseEntry[0] & 7;
            if ((phraseEntry[0] & phraseMasks[index].bytes[0]) == phraseValues[index].bytes[0] &&
                (phraseEntry[1] & phraseMasks[index].bytes[1]) == phraseValues[index].bytes[1] &&
                (phraseEntry[2] & phraseMasks[index].bytes[2]) == phraseValues[index].bytes[2] &&
                (phraseEntry[3] & phraseMasks[index].bytes[3]) == phraseValues[index].bytes[3]) candidateStatus = 1;
            break;
        case 0:
            if (match.arrD[0] == (record[0] & match.arr1[0]) &&
                (match.count || (match.arrD[3] == (record[3] & match.arr1[3]) &&
                                match.arrD[2] == (record[2] & match.arr1[2]) &&
                                match.arrD[1] == (record[1] & match.arr1[1]))) &&
                (ziU8)Zi8SecMatchChar(record, componentTable, &match, 0, work)) candidateStatus = 1;
            if (candidateStatus && getMode == 0 && match.nSeg > 1) {
                emittedWords = 0;
                for (index = request->wordCharCount; currentSpelling[index];) {
                    ++index;
                    ++emittedWords;
                }
                if (match.nSeg > emittedWords) candidateStatus = 0;
                else {
                    for (index = 1; index < match.nSeg; ++index) {
                        character = currentSpelling[request->wordCharCount + index];
                        candidateOrdinal = Zi8Uni2Ord(character, work);
                        if (candidateOrdinal == 0xFFFF) break;
                        record = records + candidateOrdinal * 12;
                        if (match.segsD[index][0] != (record[0] & match.segs1[index][0]) ||
                            match.segsD[index][1] != (record[1] & match.segs1[index][1]) ||
                            match.segsD[index][2] != (record[2] & match.segs1[index][2]) ||
                            match.segsD[index][3] != (record[3] & match.segs1[index][3])) break;
                    }
                    if (index < match.nSeg) candidateStatus = 0;
                }
            }
            break;
        case 1: case 2:
            candidateStatus = (match.phon[0] & (ziU16)Zi8GetPCode(phoneticTable, record)) == match.phon2[0];
            if (!candidateStatus && (record[0] & 0x80) && !requireFull &&
                Zi8MatchAltSound(alternateTable, alternateCount, phoneticTable, candidateOrdinal,
                                 match.phon[0], match.phon2[0], charset, work)) candidateStatus = 1;
            if (candidateStatus && match.nCand > 1) {
                emittedWords = 0;
                for (index = request->wordCharCount; currentSpelling[index];) {
                    ++index;
                    ++emittedWords;
                }
                if (match.nCand > emittedWords) candidateStatus = 0;
                else {
                    for (index = 1; index < match.nCand; ++index) {
                        character = currentSpelling[request->wordCharCount + index];
                        candidateOrdinal = Zi8Uni2Ord(character, work);
                        if (candidateOrdinal == 0xFFFF) break;
                        record = records + candidateOrdinal * 12;
                        candidateStatus = (match.phon[index] & (ziU16)Zi8GetPCode(phoneticTable, record)) == match.phon2[index];
                        if (!candidateStatus && (record[0] & 0x80) && !requireFull &&
                            Zi8MatchAltSound(alternateTable, alternateCount, phoneticTable, candidateOrdinal,
                                             match.phon[index], match.phon2[index], charset, work)) candidateStatus = 1;
                        if (!candidateStatus) break;
                    }
                    if (index < match.nCand) candidateStatus = 0;
                }
            }
            break;
        }
        if (!candidateStatus) continue;
        if (!emitWords) {
            if (trackDuplicates) {
                if ((ziU8)Zi8SetFindCand(request->scratch, candidateOrdinal, work)) continue;
            } else if (Zi8IsDupWChar(candidateOrdinal, work)) continue;
        } else {
            emittedWords = 0;
            for (index = request->wordCharCount; currentSpelling[index];) {
                ++index;
                ++emittedWords;
            }
            if (request->elementCount) {
                if ((getMode == 1 || getMode == 2) && match.nCand) {
                    if (prefixSearch) emittedWords = match.nCand;
                } else if (getMode == 0 && match.nSeg > 1) {
                    if (prefixSearch) emittedWords = match.nSeg;
                } else emittedWords = 1;
            } else if (prefixSearch) emittedWords = 1;
            currentSpelling[request->wordCharCount + emittedWords] = 0;
            if (Zi8IsDupWordW(currentSpelling + request->wordCharCount, emittedWords, work)) continue;
        }
        if (skipCount) { --skipCount; continue; }
        ++totalResults;
        if (getOptions == 5) {
            if (totalResults >= options->maxResults) goto engine_finish;
            continue;
        }
        if (emitWords) {
            ++emittedCount;
            for (index = request->wordCharCount; currentSpelling[index]; ++index) {
                output[outputIndex++] = currentSpelling[index];
            }
            output[outputIndex++] = ' ';
            if (outputIndex > outputLimit) {
                request->letters = emittedCount;
                request->unk_0x20 = emittedCount;
                goto engine_finish;
            }
        } else output[emittedCount++] = character;
        if (emittedCount >= request->maxCandidates) {
            request->letters = emittedCount;
            request->unk_0x20 = emittedCount;
            goto engine_finish;
        }
    }
pud_search:
    if (((struct __zi8_work_data_s*)work)->unk_0x12D) {
        savedPudCount = ((struct __zi8_work_data_s*)work)->pudCount;
        wordSearchPhase = 1;
        ((struct __zi8_work_data_s*)work)->pudCount = ((struct __zi8_work_data_s*)work)->unk_0x12D;
    }
pud_start:
    if (((options->countOnly && getOptions != 5) || !wordLength || getMode == 5 ||
         (request->elementCount && Zi8IsComponent(elements[0], work)) ||
         !Zi8IsCharacter(request->currentWord[0], work)) &&
        (getMode != 2 || request->elementCount <= 1) &&
        (getMode != 0 || match.nSeg <= 1) &&
        ((getMode != 1 && getMode != 2) || match.nCand <= 1)) goto pud_restore;
    matchMode = 0;
    goto pud_next;
pud_candidate:
    matchMode = 1;
    currentSpelling[index] = 0;
    if (!request->elementCount || (getMode == 0 && request->elementCount == 1 && elements[0] == 0xEF00)) {
        character = currentSpelling[wordLength];
        switch (character) {
        case 0xFF0C: case 0xFF01: case 0x3002: case 0xFF1F:
            candidateStatus = 1;
            candidateOrdinal = 0xFFFF;
            goto pud_accept;
        }
    }
    if (getMode == 2 && index >= request->elementCount + wordLength) {
        rangeIndex = 0;
        rangeCount = wordLength;
        while (rangeIndex < request->elementCount) {
            if (!((currentSpelling[rangeCount] == 0x2C9 && elements[rangeIndex] == 0xF331) ||
                (currentSpelling[rangeCount] == 0x2CA && elements[rangeIndex] == 0xF332) ||
                (currentSpelling[rangeCount] == 0x2C7 && elements[rangeIndex] == 0xF333) ||
                (currentSpelling[rangeCount] == 0x2CB && elements[rangeIndex] == 0xF334) ||
                (currentSpelling[rangeCount] == 0x2D9 && elements[rangeIndex] == 0xF335) ||
                currentSpelling[rangeCount] == elements[rangeIndex] - 0xC200)) break;
            ++rangeCount;
            ++rangeIndex;
        }
        if (rangeIndex == request->elementCount) {
            if (!(request->context & 0x10)) request->count = request->elementCount;
            candidateStatus = 1;
            character = currentSpelling[wordLength];
            candidateOrdinal = 0xFFFF;
            goto pud_accept;
        }
        if (match.nCand == 1) goto pud_next;
    }
    if ((getMode == 1 || getMode == 2) && match.nCand > 1) {
        if (match.nCand > index - wordLength) goto pud_next;
        for (index = 1; index < match.nCand; ++index) {
            character = currentSpelling[wordLength + index];
            candidateOrdinal = Zi8Uni2Ord(character, work);
            if (candidateOrdinal == 0xFFFF) break;
            record = records + candidateOrdinal * 12;
            candidateStatus = (match.phon[index] & (ziU16)Zi8GetPCode(phoneticTable, record)) == match.phon2[index];
            if (!candidateStatus && (record[0] & 0x80) && !requireFull &&
                Zi8MatchAltSound(alternateTable, alternateCount, phoneticTable, candidateOrdinal,
                                 match.phon[index], match.phon2[index], charset, work)) candidateStatus = 1;
            if (!candidateStatus) break;
        }
        if (index < match.nCand) goto pud_next;
    }
    if (getMode == 0 && match.nSeg > 1) {
        if (match.nSeg > index - wordLength) goto pud_next;
        for (index = 1; index < match.nSeg; ++index) {
            character = currentSpelling[wordLength + index];
            candidateOrdinal = Zi8Uni2Ord(character, work);
            if (candidateOrdinal == 0xFFFF) break;
            record = records + candidateOrdinal * 12;
            if (match.segsD[index][0] != (record[0] & match.segs1[index][0]) ||
                match.segsD[index][1] != (record[1] & match.segs1[index][1]) ||
                match.segsD[index][2] != (record[2] & match.segs1[index][2]) ||
                match.segsD[index][3] != (record[3] & match.segs1[index][3])) break;
        }
        if (index < match.nSeg) goto pud_next;
    }
    character = currentSpelling[wordLength];
    candidateOrdinal = Zi8Uni2Ord(character, work);
    if (candidateOrdinal == 0xFFFF) goto pud_next;
    record = records + candidateOrdinal * 12;
    candidateStatus = 0;
    switch (getMode) {
    case 7: case 8:
        phraseEntry = phraseTable + ((record[9] & 15) << 16 | (record[11] | record[10] << 8));
        if ((phraseEntry[0] & 7) >= match.length &&
            match.arr1D[0] == (match.arr19[0] & phraseEntry[0]) &&
            match.arr1D[1] == (match.arr19[1] & phraseEntry[1]) &&
            match.arr1D[2] == (match.arr19[2] & phraseEntry[2]) &&
            match.arr1D[3] == (match.arr19[3] & phraseEntry[3])) {
            candidateStatus = 1;
            break;
        }
        if (getMode == 7) break;
    case 9:
        phraseEntry = phraseTable + ((record[9] & 15) << 16 | (record[11] | record[10] << 8));
        index = phraseEntry[0] & 7;
        if ((phraseEntry[0] & phraseMasks[index].bytes[0]) == phraseValues[index].bytes[0] &&
            (phraseEntry[1] & phraseMasks[index].bytes[1]) == phraseValues[index].bytes[1] &&
            (phraseEntry[2] & phraseMasks[index].bytes[2]) == phraseValues[index].bytes[2] &&
            (phraseEntry[3] & phraseMasks[index].bytes[3]) == phraseValues[index].bytes[3]) candidateStatus = 1;
        break;
    case 0:
        if (match.arrD[0] == (record[0] & match.arr1[0]) &&
            (match.count || (match.arrD[3] == (record[3] & match.arr1[3]) &&
                            match.arrD[2] == (record[2] & match.arr1[2]) &&
                            match.arrD[1] == (record[1] & match.arr1[1]))) &&
            (ziU8)Zi8SecMatchChar(record, componentTable, &match, 0, work)) candidateStatus = 1;
        break;
    case 1: case 2:
        candidateStatus = (match.phon[0] & (ziU16)Zi8GetPCode(phoneticTable, record)) == match.phon2[0];
        if (!candidateStatus && (record[0] & 0x80) && !requireFull &&
            Zi8MatchAltSound(alternateTable, alternateCount, phoneticTable, candidateOrdinal,
                             match.phon[0], match.phon2[0], charset, work)) candidateStatus = 1;
        break;
    }
    if (!candidateStatus) goto pud_next;
pud_accept:
    if (!emitWords) {
        if (character == previousOrdinal) goto pud_next;
        previousOrdinal = character;
        if (candidateOrdinal == 0xFFFF) goto pud_charset;
        if (trackDuplicates) {
            if ((ziU8)Zi8SetFindCand(request->scratch, candidateOrdinal, work)) goto pud_next;
        } else if (Zi8IsDupWChar(candidateOrdinal, work)) goto pud_next;
    } else {
        emittedWords = 0;
        for (index = wordLength; currentSpelling[index];) {
            ++index;
            ++emittedWords;
        }
        if (request->elementCount) {
            if ((getMode == 1 || getMode == 2) && match.nCand) emittedWords = match.nCand;
            else if (getMode == 0 && match.nSeg > 1) emittedWords = match.nSeg;
            else emittedWords = 1;
        } else if (prefixSearch) emittedWords = 1;
        currentSpelling[wordLength + emittedWords] = 0;
        if (Zi8IsDupWordW(currentSpelling + wordLength, emittedWords, work)) goto pud_next;
    }
pud_charset:
    if (charsetTable && wordSearchPhase) {
        index = wordLength;
        while (currentSpelling[index]) {
            rangeIndex = Zi8Uni2Ord(currentSpelling[index], work);
            if (rangeIndex == 0xFFFF) break;
            charsetEntry = charsetTable + rangeIndex;
            if (!(charsetEntry[0] & charsetFilter)) break;
            ++index;
        }
        if (currentSpelling[index]) goto pud_next;
    }
    if (skipCount) --skipCount;
    else {
        if (!candidateWord[0] || ZiMatchZHSpelling(currentSpelling, candidateWord, request->elements,
                                                 request->elementCount, wordLength, work)) {
            ++totalResults;
            if (getOptions == 5) {
                if (totalResults >= options->maxResults) goto engine_finish;
            } else {
                if (emitWords) {
                    ++emittedCount;
                    for (index = wordLength; currentSpelling[index]; ++index) {
                        output[outputIndex++] = currentSpelling[index];
                    }
                    output[outputIndex++] = ' ';
                    if (outputIndex > outputLimit) {
                        request->letters = emittedCount;
                        request->unk_0x20 = emittedCount;
                        goto engine_finish;
                    }
                } else output[emittedCount++] = character;
                if (emittedCount >= request->maxCandidates) {
                    request->letters = emittedCount;
                    request->unk_0x20 = emittedCount;
                    goto engine_finish;
                }
            }
        }
    }
pud_next:
    if ((index = Zi8MatchPUDdata_ZHS(request->currentWord, wordLength, 1, currentSpelling, 32,
                                     candidateWord, 64, 0, matchMode, work)) != 0) goto pud_candidate;
pud_restore:
    if (wordSearchPhase == 1) {
        ((struct __zi8_work_data_s*)work)->pudCount = savedPudCount;
        wordSearchPhase = 0;
        goto pud_start;
    }
    if (wordSearchPhase == 2) {
        ((struct __zi8_work_data_s*)work)->pudCount = savedPudCount;
        wordSearchPhase = 3;
        goto pud_start;
    }
    if (wordSearchPhase == 3) goto dictionary_search;
    if ((!options->countOnly || getOptions == 5) && !ordinalCount &&
        request->wordCharCount && getMode != 5 &&
        (!request->elementCount || !Zi8IsComponent(elements[0], work))) {
        if (!filteringMode) goto context_word_lookup;
        filteringMode = 4;
        goto filtered_search;
    }
    goto context_results_done;
context_word_filter:
    filteringMode = 1;
context_word_lookup:
    ordinalIndex = Zi8Uni2Ord(request->currentWord[0], work);
    if (ordinalIndex == 0xFFFF) goto context_results_done;
    record = records + ordinalIndex * 12;
    phoneticGroups = phraseTable + ((record[9] & 15) << 16 | (record[11] | record[10] << 8));
    if (((struct __zi8_work_data_s*)work)->cangjieEnabled) {
        switch (phoneticGroups[0] & 7) {
        case 2: phoneticGroups += 2; break;
        case 3: case 4: phoneticGroups += 3; break;
        case 5: phoneticGroups += 4; break;
        default: ++phoneticGroups; break;
        }
    }
    if (phoneticGroups[0] & 0x80) {
        groupHeader = 0;
        phoneticGroups += ((phoneticGroups[0] & 0x7F) >> 4) + 1;
    } else groupHeader = 0x80;
    while (!(groupHeader & 0x80)) {
        groupHeader = *phoneticGroups++;
        groupCount = groupHeader & 15;
        if (!(groupHeader & charset)) {
            for (; groupCount; --groupCount) {
                for (++phoneticGroups; !(*phoneticGroups & 0x80); phoneticGroups += 2) {}
                ++phoneticGroups;
            }
        }
        for (; groupCount; --groupCount) {
            remainingWordLength = request->wordCharCount - 1;
            currentWord = request->currentWord;
            for (; remainingWordLength; --remainingWordLength) {
                candidateOrdinal = (ziU16)phoneticGroups[1] << 8 | phoneticGroups[0];
                phoneticGroups += 2;
                if (candidateOrdinal & 0x8000) break;
                if (*++currentWord != Zi8Ord2Uni(candidateOrdinal, work)) break;
            }
            if (remainingWordLength) goto context_phrase_next;
            candidateOrdinal = (ziU16)phoneticGroups[1] << 8 | phoneticGroups[0];
            frequencyTable = phoneticGroups;
            phoneticGroups += 2;
            character = candidateOrdinal & 0x7FFF;
            candidateStatus = 1;
            if (request->elementCount) {
                candidateStatus = 0;
                record = records + character * 12;
                isFirstCandidate = ((ziU16)record[6] << 8) + record[7];
                switch (getMode) {
                case 7: case 8:
                    phraseEntry = phraseTable + ((record[9] & 15) << 16 | (record[11] | record[10] << 8));
                    if ((phraseEntry[0] & 7) >= match.length &&
                        match.arr1D[0] == (match.arr19[0] & phraseEntry[0]) &&
                        match.arr1D[1] == (match.arr19[1] & phraseEntry[1]) &&
                        match.arr1D[2] == (match.arr19[2] & phraseEntry[2]) &&
                        match.arr1D[3] == (match.arr19[3] & phraseEntry[3])) {
                        candidateStatus = 1;
                        break;
                    }
                    if (getMode == 7) break;
                case 9:
                    phraseEntry = phraseTable + ((record[9] & 15) << 16 | (record[11] | record[10] << 8));
                    index = phraseEntry[0] & 7;
                    if ((phraseEntry[0] & phraseMasks[index].bytes[0]) == phraseValues[index].bytes[0] &&
                        (phraseEntry[1] & phraseMasks[index].bytes[1]) == phraseValues[index].bytes[1] &&
                        (phraseEntry[2] & phraseMasks[index].bytes[2]) == phraseValues[index].bytes[2] &&
                        (phraseEntry[3] & phraseMasks[index].bytes[3]) == phraseValues[index].bytes[3]) candidateStatus = 1;
                    break;
                case 0:
                    if (match.arrD[0] == (record[0] & match.arr1[0]) &&
                        (match.count || (match.arrD[3] == (record[3] & match.arr1[3]) &&
                                        match.arrD[2] == (record[2] & match.arr1[2]) &&
                                        match.arrD[1] == (record[1] & match.arr1[1]))) &&
                        (ziU8)Zi8SecMatchChar(record, componentTable, &match, 0, work)) candidateStatus = 1;
                    if (candidateStatus && match.nSeg >= 2) {
                        duplicateIndex = 0;
                        relatedOrdinal = character;
                        while (candidateStatus) {
                            record = records + relatedOrdinal * 12;
                            if (match.segsD[duplicateIndex][0] != (record[0] & match.segs1[duplicateIndex][0]) ||
                                match.segsD[duplicateIndex][1] != (record[1] & match.segs1[duplicateIndex][1]) ||
                                match.segsD[duplicateIndex][2] != (record[2] & match.segs1[duplicateIndex][2]) ||
                                match.segsD[duplicateIndex][3] != (record[3] & match.segs1[duplicateIndex][3])) {
                                candidateStatus = 0;
                                break;
                            }
                            if (++duplicateIndex >= match.nSeg) break;
                            if (candidateOrdinal & 0x8000) { candidateStatus = 0; break; }
                            candidateOrdinal = (ziU16)phoneticGroups[1] << 8 | phoneticGroups[0];
                            phoneticGroups += 2;
                            relatedOrdinal = candidateOrdinal & 0x7FFF;
                        }
                    }
                    break;
                case 1: case 2:
                    duplicateIndex = 0;
                    relatedOrdinal = character;
                    while (1) {
                        record = records + relatedOrdinal * 12;
                        candidateStatus = (match.phon[duplicateIndex] & (ziU16)Zi8GetPCode(phoneticTable, record)) == match.phon2[duplicateIndex];
                        if (!candidateStatus && (record[0] & 0x80) && !requireFull && !filteringMode &&
                            Zi8MatchAltSound(alternateTable, alternateCount, phoneticTable, relatedOrdinal,
                                             match.phon[duplicateIndex], match.phon2[duplicateIndex], charset, work)) candidateStatus = 1;
                        if (!candidateStatus) break;
                        if (++duplicateIndex >= match.nCand) break;
                        if (candidateOrdinal & 0x8000) { candidateStatus = 0; break; }
                        candidateOrdinal = (ziU16)phoneticGroups[1] << 8 | phoneticGroups[0];
                        phoneticGroups += 2;
                        relatedOrdinal = candidateOrdinal & 0x7FFF;
                    }
                    break;
                }
            } else isFirstCandidate = Zi8Ord2Uni(character, work);
            if (!emitWords && isFirstCandidate == previousOrdinal) goto context_phrase_next;
            previousOrdinal = isFirstCandidate;
            if (!candidateStatus) goto context_phrase_next;
            ((ZiChineseWork*)work)->duplicateOrdinals[((ZiChineseWork*)work)->duplicateIndex] = character;
            ((ZiChineseWork*)work)->duplicateCharacters[((ZiChineseWork*)work)->duplicateIndex] = isFirstCandidate;
            if (charsetTable) {
                index = 0;
                while (1) {
                    isFirstCandidate = (ziU16)frequencyTable[index * 2 + 1] << 8 | frequencyTable[index * 2];
                    charsetEntry = charsetTable + (isFirstCandidate & 0x7FFF);
                    if (!(charsetEntry[0] & charsetFilter)) { isFirstCandidate = 0; break; }
                    if (isFirstCandidate & 0x8000) break;
                    ++index;
                }
                if (!(isFirstCandidate & 0x8000)) goto context_phrase_next;
            }
            if (!emitWords) {
                if (trackDuplicates) {
                    if ((ziU8)Zi8SetFindCand(request->scratch, character, work)) goto context_phrase_next;
                } else if (Zi8IsDupWChar(character, work)) goto context_phrase_next;
            } else {
                emittedWords = 0;
                do {
                    character = (ziU16)frequencyTable[1] << 8 | frequencyTable[0];
                    frequencyTable += 2;
                    output[outputIndex + emittedWords++] = Zi8Ord2Uni(character & 0x7FFF, work);
                } while (!(character & 0x8000));
                if (request->elementCount) {
                    if ((getMode == 1 || getMode == 2) && match.nCand) emittedWords = match.nCand;
                    else if (getMode == 0 && match.nSeg > 1) emittedWords = match.nSeg;
                    else emittedWords = 1;
                } else if (prefixSearch) emittedWords = 1;
                if (Zi8IsDupWordW(output + outputIndex, emittedWords, work)) goto context_phrase_next;
            }
            if (skipCount) --skipCount;
            else {
                ++totalResults;
                if (getOptions == 5) {
                    if (totalResults >= options->maxResults) goto engine_finish;
                } else {
                    if (++((ZiChineseWork*)work)->duplicateIndex >= 64) ((ZiChineseWork*)work)->duplicateIndex = 0;
                    if (emitWords) {
                        ++emittedCount;
                        outputIndex += emittedWords;
                        output[outputIndex++] = ' ';
                        if (outputIndex > outputLimit) {
                            request->letters = emittedCount;
                            request->unk_0x20 = emittedCount;
                            goto engine_finish;
                        }
                    } else output[emittedCount++] = previousOrdinal;
                    if (emittedCount >= request->maxCandidates) {
                        request->letters = emittedCount;
                        request->unk_0x20 = emittedCount;
                        goto engine_finish;
                    }
                }
            }
context_phrase_next:
            if (!(candidateOrdinal & 0x8000)) {
                for (++phoneticGroups; !(phoneticGroups[0] & 0x80); phoneticGroups += 2) {}
                ++phoneticGroups;
            }
        }
    }
context_results_done:
    if (request->wordCharCount) request->unk_0x20 = emittedCount;
    if (getOptions == 5) goto engine_finish;
    if ((wordLength && (getMode == 1 || getMode == 2) && match.nCand > 1) ||
        (wordLength && getMode == 0 && match.nSeg > 1)) {
        wordLength = 0;
        savedPudCount = ((struct __zi8_work_data_s*)work)->pudCount;
        wordSearchPhase = 2;
        ((struct __zi8_work_data_s*)work)->pudCount = ((struct __zi8_work_data_s*)work)->unk_0x12D;
        goto pud_start;
    }
dictionary_search:
    if (!request->elementCount && !options->countOnly && request->wordCharCount &&
        Zi8GetFormatVersion(1, work) >= 8) {
        lastCharHigh = (request->currentWord[request->wordCharCount - 1] >> 8) & 0xFF;
        lastCharLow = request->currentWord[request->wordCharCount - 1];
        phoneticGroups = Zi8GetTableAddress(1, 28, work);
        rangeCount = Zi8GetTableCount(1, 28, work);
        rangeIndex = 0;
        while (rangeIndex < rangeCount) {
            if (lastCharHigh == phoneticGroups[0] && lastCharLow == phoneticGroups[1]) {
                rangeIndex = 0;
                while (rangeIndex < 4) {
                    character = ((ziU16)phoneticGroups[2] << 8) + phoneticGroups[3];
                    if (!character) goto numeric_setup;
                    if (!emitWords) {
                        for (index = 0; index < emittedCount; ++index) {
                            if (character == output[index]) break;
                        }
                        if (index < emittedCount) goto prediction_next;
                    } else if (Zi8IsDupWordW(&character, 1, work)) goto prediction_next;
                    if (skipCount) --skipCount;
                    else {
                        ++totalResults;
                        if (emitWords) {
                            ++emittedCount;
                            output[outputIndex++] = character;
                            output[outputIndex++] = ' ';
                            if (outputIndex > outputLimit) goto engine_finish;
                        } else output[emittedCount++] = character;
                        if (emittedCount >= request->maxCandidates) goto engine_finish;
                    }
prediction_next:
                    ++rangeIndex;
                    phoneticGroups += 2;
                }
                goto numeric_setup;
            }
            ++rangeIndex;
            phoneticGroups += 10;
        }
    }
numeric_setup:
    if (!options->countOnly && !ordinalCount && match.nCand <= 1 && match.nSeg <= 1 &&
        request->wordCharCount && Zi8GetFormatVersion(1, work) >= 8) {
        ordinalCount = Zi8GetTableCount(1, 29, work);
        ordinalIndex = request->currentWord[request->wordCharCount - 1];
        if (ordinalCount && (ordinalIndex < '0' || ordinalIndex > '9')) {
            switch (ordinalIndex) {
            case 0x4E00: case 0x4E03: case 0x4E09: case 0x4E5D: case 0x4E8C: case 0x4E94:
            case 0x516B: case 0x516D: case 0x5341: case 0x56DB: case 0x96F6: break;
            default: ordinalCount = 0; break;
            }
        }
        if (ordinalCount) ordinalTable = Zi8GetTableAddress(1, 29, work);
    }
    if (!request->elementCount && (getMode == 7 || getMode == 8 || getMode == 9)) {
        resultFallback = 0;
        match.length = 0;
    }
candidate_dictionary_search:
    if (!options->countOnly && ordinalCount && (getMode == 7 || getMode == 8 || getMode == 9)) {
        for (ordinalIndex = 0; ordinalIndex < ordinalCount; ++ordinalIndex) {
            candidateOrdinal = ((ziU16)ordinalTable[ordinalIndex * 2] << 8) + ordinalTable[ordinalIndex * 2 + 1];
            record = records + candidateOrdinal * 12;
            if (!(record[0] & charset)) continue;
            phraseEntry = phraseTable + ((record[9] & 15) << 16 | (record[11] | record[10] << 8));
            candidateStatus = 0;
            if (getMode == 8 || getMode == 9) {
                index = phraseEntry[0] & 7;
                if ((phraseEntry[0] & phraseMasks[index].bytes[0]) == phraseValues[index].bytes[0] &&
                    (phraseEntry[1] & phraseMasks[index].bytes[1]) == phraseValues[index].bytes[1] &&
                    (phraseEntry[2] & phraseMasks[index].bytes[2]) == phraseValues[index].bytes[2] &&
                    (phraseEntry[3] & phraseMasks[index].bytes[3]) == phraseValues[index].bytes[3]) {
                    if ((resultFallback && index == match.length) || (!resultFallback && index > match.length)) {
                        candidateStatus = 1;
                    } else if (getMode == 9) continue;
                } else if (getMode == 9) continue;
            }
            if (!candidateStatus && !((phraseEntry[0] & 7) >= match.length &&
                match.arr1D[0] == (match.arr19[0] & phraseEntry[0]) &&
                match.arr1D[1] == (match.arr19[1] & phraseEntry[1]) &&
                match.arr1D[2] == (match.arr19[2] & phraseEntry[2]) &&
                match.arr1D[3] == (match.arr19[3] & phraseEntry[3]) &&
                ((resultFallback && (phraseEntry[0] & 7) == match.length) || (!resultFallback && (phraseEntry[0] & 7) > match.length)))) continue;
            if (charsetTable) {
                charsetEntry = charsetTable + candidateOrdinal;
                if (!(charsetEntry[0] & charsetFilter)) continue;
            }
            character = Zi8Ord2Uni(candidateOrdinal, work);
            ((ZiChineseWork*)work)->duplicateOrdinals[((ZiChineseWork*)work)->duplicateIndex] = candidateOrdinal;
            ((ZiChineseWork*)work)->duplicateCharacters[((ZiChineseWork*)work)->duplicateIndex] = character;
            if (!emitWords) {
                if (trackDuplicates) {
                    if ((ziU8)Zi8SetFindCand(request->scratch, candidateOrdinal, work)) continue;
                } else if (Zi8IsDupWChar(candidateOrdinal, work)) continue;
            } else if (Zi8IsDupWordW(&character, 1, work)) continue;
            if (skipCount) --skipCount;
            else {
                if (++((ZiChineseWork*)work)->duplicateIndex >= 64) ((ZiChineseWork*)work)->duplicateIndex = 0;
                ++totalResults;
                if (emitWords) {
                    ++emittedCount;
                    output[outputIndex++] = character;
                    output[outputIndex++] = ' ';
                    if (outputIndex > outputLimit) goto engine_finish;
                } else output[emittedCount++] = character;
                if (emittedCount >= request->maxCandidates) goto engine_finish;
            }
        }
    }
    record = records;
    candidateCount = recordCount;
    if (match.length > 1 && match.nSeg < 2 && !options->countOnly && phoneticRetry && getMode != 5) {
        phase = 0;
character_range_start:
        record = records;
        candidateCount = recordCount;
        firstOrdinal = 0;
        rangeIndex = Zi8GetTableCount(1, 16, work);
        if (Zi8GetFormatVersion(1, work) >= 4 && rangeIndex && elements[0] != 0xEF00) {
            phoneticGroups = Zi8GetTableAddress(1, 16, work);
            rangeIndex = 0;
            rangeCount = 0;
            switch (phase) {
            case 0:
                rangeIndex = 0;
                rangeCount = 2;
                phase = 1;
                break;
            case 1:
                switch (match.comp) {
                case 0xEF01: rangeIndex = 8; rangeCount = 10; break;
                case 0xEF02: rangeIndex = 12; rangeCount = 14; break;
                case 0xEF04: rangeIndex = 16; rangeCount = 18; break;
                case 0xEF07: rangeIndex = 20; rangeCount = 22; break;
                case 0xEF05: rangeIndex = 24; rangeCount = 26; break;
                case 0xEF06: rangeIndex = 28; rangeCount = 30; break;
                case 0xEF08: rangeIndex = 32; rangeCount = 34; break;
                case 0xEF03: rangeIndex = 36; rangeCount = 38; break;
                case 0xEF0A: rangeIndex = 24; rangeCount = 4; break;
                case 0xEF0B: rangeIndex = 20; rangeCount = 14; break;
                }
                if (request->context & 0x40) phase = 0xFF;
                else phase = 2;
                break;
            case 2: rangeIndex = 4; rangeCount = 6; phase = 0xFF; break;
            }
            firstOrdinal = phoneticGroups[rangeIndex] | (ziU16)phoneticGroups[rangeIndex + 1] << 8;
            record += firstOrdinal * 12;
            candidateCount = (phoneticGroups[rangeCount] | (ziU16)phoneticGroups[rangeCount + 1] << 8) - firstOrdinal;
        } else phase = 0xFF;
        remainingOrdinals = candidateCount;
        while (1) {
            if (match.count) {
                if (!candidateCount--) goto character_range_done;
                if (match.arr1D[0] != (record[0] & match.arr19[0])) goto character_range_next;
                if ((ziU8)Zi8SecMatchChar(record, componentTable, &match, &candidateOrdinal, work) == 2) goto character_range_accept;
            } else {
                if (!Zi8ExactMatchNextChar(record, match.arr19[0], match.arr1D[0], match.arr19[1], match.arr1D[1],
                                         match.arr19[2], match.arr1D[2], match.arr19[3], match.arr1D[3],
                                         &candidateCount, &record, &candidateOrdinal, work)) goto character_range_done;
                if ((!match.field22 && match.length < 8) ||
                    (ziU8)Zi8SecMatchChar(record, componentTable, &match, &candidateOrdinal, work) == 2) goto character_range_accept;
            }
character_range_next:
            record += 12;
            continue;
character_range_accept:
            ordinalIndex = remainingOrdinals - candidateCount + firstOrdinal - 1;
            ((ZiChineseWork*)work)->duplicateOrdinals[((ZiChineseWork*)work)->duplicateIndex] = ordinalIndex;
            ((ZiChineseWork*)work)->duplicateCharacters[((ZiChineseWork*)work)->duplicateIndex] = candidateOrdinal;
            if (charsetTable) {
                charsetEntry = charsetTable + ordinalIndex;
                if (!(charsetEntry[0] & charsetFilter)) goto character_range_next;
            }
            if (candidateOrdinal == previousOrdinal) goto character_range_next;
            if (emitWords) {
                if (Zi8IsDupWordW(&candidateOrdinal, 1, work)) goto character_range_next;
            } else if (trackDuplicates) {
                if ((ziU8)Zi8SetFindCand(request->scratch, ordinalIndex, work)) goto character_range_next;
            } else if (Zi8IsDupWChar(ordinalIndex, work)) goto character_range_next;
            previousOrdinal = candidateOrdinal;
            if (skipCount) {
                --skipCount;
                if (seenCount < 5) seenOrdinals[seenCount++] = candidateOrdinal;
                goto character_range_next;
            }
            if (emitWords) {
                ++emittedCount;
                output[outputIndex++] = candidateOrdinal;
                output[outputIndex++] = ' ';
                if (outputIndex > outputLimit) goto engine_finish;
            } else {
                for (duplicateIndex = 0; duplicateIndex < emittedCount; ++duplicateIndex) {
                    if (candidateOrdinal == output[duplicateIndex]) break;
                }
                if (duplicateIndex < emittedCount) goto character_range_next;
                output[emittedCount++] = candidateOrdinal;
            }
            if (++((ZiChineseWork*)work)->duplicateIndex >= 64) ((ZiChineseWork*)work)->duplicateIndex = 0;
            ++totalResults;
            if (emittedCount >= request->maxCandidates) goto engine_finish;
            record += 12;
        }
character_range_done:
        if (phase != 0xFF) goto character_range_start;
    }
    if (!options->countOnly && phoneticRetry && ordinalCount && getMode != 5) {
        tableIndex = 0;
        while (tableIndex < ordinalCount) {
            phraseOrdinal = ((ziU16)ordinalTable[tableIndex * 2] << 8) + ordinalTable[tableIndex * 2 + 1];
            record = records + phraseOrdinal * 12;
            candidateCount = 1;
            if (exactPhrase) {
                if (!Zi8PriMatchNextChar(record, match.arr1[0], match.arrD[0], match.arr1[1], match.arrD[1],
                                        match.arr1[2], match.arrD[2], match.arr1[3], match.arrD[3],
                                        &candidateCount, &record, &candidateOrdinal, work) ||
                    !(ziU8)Zi8SecMatchChar(record, componentTable, &match, &candidateOrdinal, work)) { ++tableIndex; continue; }
                ((ZiChineseWork*)work)->duplicateOrdinals[((ZiChineseWork*)work)->duplicateIndex] = phraseOrdinal;
                ((ZiChineseWork*)work)->duplicateCharacters[((ZiChineseWork*)work)->duplicateIndex] = candidateOrdinal;
                if (charsetTable) {
                    charsetEntry = charsetTable + phraseOrdinal;
                    if (!(charsetEntry[0] & charsetFilter)) { ++tableIndex; continue; }
                }
                if (emitWords) {
                    if (Zi8IsDupWordW(&candidateOrdinal, 1, work)) { ++tableIndex; continue; }
                } else if (trackDuplicates) {
                    if ((ziU8)Zi8SetFindCand(request->scratch, phraseOrdinal, work)) { ++tableIndex; continue; }
                } else if (Zi8IsDupWChar(phraseOrdinal, work)) { ++tableIndex; continue; }

                recordFrequency = (record[4] & 0xFC) >> 2;
                exactPhrase = 0;
            }
            if (seenCount) {
                for (duplicateIndex = 0; duplicateIndex < seenCount; ++duplicateIndex) {
                    if (candidateOrdinal == seenOrdinals[duplicateIndex]) break;
                }
                if (duplicateIndex < seenCount) { exactPhrase = 1; ++tableIndex; continue; }
            }
            if (candidateOrdinal != previousOrdinal) {
                previousOrdinal = candidateOrdinal;
                if (!skipCount) {
                    ++totalResults;
                    if (++((ZiChineseWork*)work)->duplicateIndex >= 64) ((ZiChineseWork*)work)->duplicateIndex = 0;
                    if (!options->countOnly) {
                        if (emitWords) {
                            ++emittedCount;
                            output[outputIndex++] = candidateOrdinal;
                            output[outputIndex++] = ' ';
                            if (outputIndex > outputLimit) goto engine_finish;
                        } else output[emittedCount++] = candidateOrdinal;
                        if (emittedCount >= request->maxCandidates) goto engine_finish;
                    } else if (totalResults >= options->maxResults) goto engine_finish;
                } else --skipCount;
            }
ordinal_done:
            exactPhrase = 1;
            ++tableIndex;
        }
        exactPhrase = 1;
    }
    if (!options->countOnly && !phoneticRetry && ordinalCount &&
        getMode != 7 && getMode != 8 && getMode != 9 && match.nCand <= 1) {
        if (match.first == match.phon[0] && match.first2 == match.phon2[0]) switchedPhonetic = 0;
        else {
            switchedPhonetic = 1;
            phoneticMask = match.phon[0];
            phoneticMatch = match.phon2[0];
            match.phon[0] = match.first;
            match.phon2[0] = match.first2;
            match.first = phoneticMask;
            match.first2 = phoneticMatch;
        }
        phoneticMask = 0;
        phoneticMatch = 0x10;
phonetic_ordinal_search:
        for (tableIndex = 0; tableIndex < ordinalCount; ++tableIndex) {
            phraseOrdinal = ((ziU16)ordinalTable[tableIndex * 2] << 8) + ordinalTable[tableIndex * 2 + 1];
            record = records + phraseOrdinal * 12;
            candidateCount = 0;
            phoneticGroups = 0;
            if (!Zi8MatchPhonetic(phoneticTable, (ZiChineseRecord*)records, alternateTable, alternateCount,
                                 phraseTable, (ZiChineseRecord*)record, match.phon, match.phon2,
                                 &candidateCount, (ZiChineseRecord**)&record, (int*)&phoneticGroups,
                                 0, 1, match.nCand, phoneticMask, phoneticMatch, charset, requireFull,
                                 phraseOrdinal, &candidateOrdinal, 0, work)) continue;
            if (charsetTable) {
                charsetEntry = charsetTable + phraseOrdinal;
                if (!(charsetEntry[0] & charsetFilter)) continue;
            }
            if (candidateOrdinal == previousOrdinal) continue;
            previousOrdinal = candidateOrdinal;
            ((ZiChineseWork*)work)->duplicateOrdinals[((ZiChineseWork*)work)->duplicateIndex] = phraseOrdinal;
            ((ZiChineseWork*)work)->duplicateCharacters[((ZiChineseWork*)work)->duplicateIndex] = candidateOrdinal;
            if (!emitWords) {
                if (trackDuplicates) {
                    if ((ziU8)Zi8SetFindCand(request->scratch, phraseOrdinal, work)) continue;
                } else if (Zi8IsDupWChar(phraseOrdinal, work)) continue;
            } else if (Zi8IsDupWordW(&candidateOrdinal, 1, work)) continue;

            if (skipCount) --skipCount;
            else {
                ++totalResults;
                if (!options->countOnly) {
                    if (++((ZiChineseWork*)work)->duplicateIndex >= 64) ((ZiChineseWork*)work)->duplicateIndex = 0;
                    if (emitWords) {
                        ++emittedCount;
                        output[outputIndex++] = candidateOrdinal;
                        output[outputIndex++] = ' ';
                        if (outputIndex > outputLimit) goto engine_finish;
                    } else output[emittedCount++] = candidateOrdinal;
                    if (emittedCount >= request->maxCandidates) goto engine_finish;
                } else if (totalResults >= options->maxResults) goto engine_finish;
            }
        }
        if (switchedPhonetic) {
            switchedPhonetic = 0;
            phoneticMask = match.phon[0];
            phoneticMatch = match.phon2[0];
            match.phon[0] = match.first;
            match.phon2[0] = match.first2;
            match.first = phoneticMask;
            match.first2 = phoneticMatch;
            phoneticInput = 1;
        }
    }
tone_candidates:
    if (getMode == 2 && getOptions != 6 && !request->elementCount && request->wordCharCount &&
        request->currentWord[request->wordCharCount - 1] >= 0x3105 &&
        request->currentWord[request->wordCharCount - 1] <= 0x3129) {
        for (index = 0; index < sizeof(ziTones) / sizeof(ziTones[0]); ++index) {
            character = ziTones[index];
            if (!emitWords) {
                for (rangeIndex = 0; rangeIndex < emittedCount; ++rangeIndex) {
                    if (character == output[rangeIndex]) break;
                }
                if (rangeIndex < emittedCount) continue;
            } else if (Zi8IsDupWordW(&character, 1, work)) continue;
            if (skipCount) --skipCount;
            else {
                ++totalResults;
                if (!options->countOnly) {
                    if (emitWords) {
                        ++emittedCount;
                        output[outputIndex++] = character;
                        output[outputIndex++] = ' ';
                        if (outputIndex > outputLimit) goto engine_finish;
                    } else output[emittedCount++] = character;
                    if (emittedCount >= request->maxCandidates) goto engine_finish;
                } else if (totalResults >= options->maxResults) goto engine_finish;
            }
        }
    }
    if (getMode == 2 && request->elementCount == 1 && elements[0] >= 0xF305 && elements[0] <= 0xF329) {
        character = elements[0] - 0xC200;
        if (getOptions != 6) {
            for (index = 0; character; character = zi8tones[index++]) {
                if (!emitWords) {
                    for (rangeIndex = 0; rangeIndex < emittedCount; ++rangeIndex) {
                        if (character == output[rangeIndex]) break;
                    }
                    if (rangeIndex < emittedCount) {
                        if (elements[0] != 0xF305) break;
                        continue;
                    }
                } else if (Zi8IsDupWordW(&character, 1, work)) {
                    if (elements[0] != 0xF305) break;
                    continue;
                }
                if (skipCount) --skipCount;
                else {
                    ++totalResults;
                    if (!options->countOnly) {
                        if (emitWords) {
                            ++emittedCount;
                            output[outputIndex++] = character;
                            output[outputIndex++] = ' ';
                            if (outputIndex > outputLimit) goto engine_finish;
                        } else output[emittedCount++] = character;
                        if (emittedCount >= request->maxCandidates) goto engine_finish;
                    } else if (totalResults >= options->maxResults) goto engine_finish;
                }
                if (elements[0] != 0xF305) break;
            }
        }
        character = 0x8A92;
        if (!emitWords) {
            for (rangeIndex = 0; rangeIndex < emittedCount; ++rangeIndex) {
                if (character == output[rangeIndex]) break;
            }
            if (rangeIndex < emittedCount) character = 0;
        } else if (Zi8IsDupWordW(&character, 1, work)) character = 0;
        if (character) {
            ordinalIndex = Zi8Uni2Ord(character, work);
            if (ordinalIndex != 0xFFFF) {
                record = records + ordinalIndex * 12;
                if (record[0] & charset) {
                    if (charsetTable) {
                        charsetEntry = charsetTable + ordinalIndex;
                        if (!(charsetEntry[0] & charsetFilter)) character = 0;
                    }
                } else character = 0;
            } else character = 0;
        }
        if (elements[0] == 0xF31D && character) {
            if (skipCount) --skipCount;
            else {
                ++totalResults;
                if (!options->countOnly) {
                    if (emitWords) {
                        ++emittedCount;
                        output[outputIndex++] = character;
                        output[outputIndex++] = ' ';
                        if (outputIndex > outputLimit) goto engine_finish;
                    } else output[emittedCount++] = character;
                    if (emittedCount >= request->maxCandidates) goto engine_finish;
                } else if (totalResults >= options->maxResults) goto engine_finish;
            }
        }
    }
user_character_search:
    if (((struct __zi8_work_data_s*)work)->unk_0x12C && (getMode != 0 || !firstPhoneticPass) &&
        !options->countOnly && (match.nCand <= 1 || (getMode != 1 && getMode != 2)) &&
        Zi8GetZHuwdPtr(&userEntries, &userCount, work) && (getMode != 0 || match.nSeg <= 1)) {
        userIndex = 0;
        while (userIndex < userCount) {
            candidateOrdinal = (ziU16)(userEntries[1] & 0x7F) << 8 | userEntries[2];
            record = records + candidateOrdinal * 12;
            if (!(record[0] & charset)) goto user_character_next;
            character = ((ziU16)record[6] << 8) + record[7];
            candidateStatus = 0;
            switch (getMode) {
            case 7: case 8:
                phraseEntry = phraseTable + ((record[9] & 15) << 16 | (record[11] | record[10] << 8));
                if ((phraseEntry[0] & 7) >= match.length &&
                    match.arr1D[0] == (match.arr19[0] & phraseEntry[0]) &&
                    match.arr1D[1] == (match.arr19[1] & phraseEntry[1]) &&
                    match.arr1D[2] == (match.arr19[2] & phraseEntry[2]) &&
                    match.arr1D[3] == (match.arr19[3] & phraseEntry[3]) &&
                    ((resultFallback && (phraseEntry[0] & 7) == match.length) || (!resultFallback && (phraseEntry[0] & 7) > match.length))) {
                    candidateStatus = 1;
                    break;
                }
                if (getMode != 8) break;
            case 9:
                phraseEntry = phraseTable + ((record[9] & 15) << 16 | (record[11] | record[10] << 8));
                index = phraseEntry[0] & 7;
                if ((phraseEntry[0] & phraseMasks[index].bytes[0]) == phraseValues[index].bytes[0] &&
                    (phraseEntry[1] & phraseMasks[index].bytes[1]) == phraseValues[index].bytes[1] &&
                    (phraseEntry[2] & phraseMasks[index].bytes[2]) == phraseValues[index].bytes[2] &&
                    (phraseEntry[3] & phraseMasks[index].bytes[3]) == phraseValues[index].bytes[3] &&
                    ((resultFallback && index == match.length) || (!resultFallback && index > match.length))) candidateStatus = 1;
                break;
            case 0:
                if (match.arrD[0] == (record[0] & match.arr1[0]) &&
                    (match.count || (match.arrD[3] == (record[3] & match.arr1[3]) &&
                                    match.arrD[2] == (record[2] & match.arr1[2]) &&
                                    match.arrD[1] == (record[1] & match.arr1[1]))) &&
                    (ziU8)Zi8SecMatchChar(record, componentTable, &match, 0, work)) candidateStatus = 1;
                break;
            case 1: case 2:
                if (request->elementCount && !(userEntries[1] & 0x80)) candidateStatus = 0;
                else {
                    candidateStatus = (match.first & (ziU16)Zi8GetPCode(phoneticTable, record)) == match.first2;
                    if (!candidateStatus && (record[0] & 0x80) && !requireFull &&
                        Zi8MatchAltSound(alternateTable, alternateCount, phoneticTable, candidateOrdinal,
                                         match.first, match.first2, charset, work)) candidateStatus = 1;
                }
                break;
            }
            if (!candidateStatus) goto user_character_next;
            if (charsetTable) {
                charsetEntry = charsetTable + candidateOrdinal;
                if (!(charsetEntry[0] & charsetFilter)) goto user_character_next;
            }
            ((ZiChineseWork*)work)->duplicateOrdinals[((ZiChineseWork*)work)->duplicateIndex] = candidateOrdinal;
            ((ZiChineseWork*)work)->duplicateCharacters[((ZiChineseWork*)work)->duplicateIndex] = character;
            if (!emitWords) {
                if (trackDuplicates) {
                    if ((ziU8)Zi8SetFindCand(request->scratch, candidateOrdinal, work)) goto user_character_next;
                } else if (Zi8IsDupWChar(candidateOrdinal, work)) goto user_character_next;
            } else if (Zi8IsDupWordW(&character, 1, work)) goto user_character_next;
            if (skipCount) --skipCount;
            else {
                if (++((ZiChineseWork*)work)->duplicateIndex >= 64) ((ZiChineseWork*)work)->duplicateIndex = 0;
                ++totalResults;
                if (emitWords) {
                    ++emittedCount;
                    output[outputIndex++] = character;
                    output[outputIndex++] = ' ';
                    if (outputIndex > outputLimit) goto engine_finish;
                } else output[emittedCount++] = character;
                if (emittedCount >= request->maxCandidates) goto engine_finish;
            }
user_character_next:
            ++userIndex;
            userEntries += 3;
        }
    }
    if (!prefixLookup) goto phonetic_alt_continue;
    if (getMode == 7 || getMode == 8 || getMode == 9) {
        record = records;
        ordinalIndex = 0;
        while (ordinalIndex < recordCount) {
            if (!(record[0] & charset)) goto global_character_next;
            if (charsetTable) {
                charsetEntry = charsetTable + ordinalIndex;
                if (!(charsetEntry[0] & charsetFilter)) goto global_character_next;
            }
            character = ((ziU16)record[6] << 8) + record[7];
            ((ZiChineseWork*)work)->duplicateOrdinals[((ZiChineseWork*)work)->duplicateIndex] = ordinalIndex;
            ((ZiChineseWork*)work)->duplicateCharacters[((ZiChineseWork*)work)->duplicateIndex] = character;
            if (character == previousOrdinal) goto global_character_next;
            previousOrdinal = character;
            candidateStatus = 0;
            phraseEntry = phraseTable + ((record[9] & 15) << 16 | (record[11] | record[10] << 8));
            if (getMode != 7) {
                index = phraseEntry[0] & 7;
                if ((phraseEntry[0] & phraseMasks[index].bytes[0]) == phraseValues[index].bytes[0] &&
                    (phraseEntry[1] & phraseMasks[index].bytes[1]) == phraseValues[index].bytes[1] &&
                    (phraseEntry[2] & phraseMasks[index].bytes[2]) == phraseValues[index].bytes[2] &&
                    (phraseEntry[3] & phraseMasks[index].bytes[3]) == phraseValues[index].bytes[3]) {
                    if ((resultFallback && index == match.length) || (!resultFallback && index > match.length)) {
                        candidateStatus = 1;
                    } else if (getMode == 9) goto global_character_next;
                } else if (getMode == 9) goto global_character_next;
            }
            if (!candidateStatus && !((phraseEntry[0] & 7) >= match.length &&
                match.arr1D[0] == (match.arr19[0] & phraseEntry[0]) &&
                match.arr1D[1] == (match.arr19[1] & phraseEntry[1]) &&
                match.arr1D[2] == (match.arr19[2] & phraseEntry[2]) &&
                match.arr1D[3] == (match.arr19[3] & phraseEntry[3]) &&
                ((resultFallback && (phraseEntry[0] & 7) == match.length) || (!resultFallback && (phraseEntry[0] & 7) > match.length)))) goto global_character_next;
            if (!emitWords) {
                if (trackDuplicates) {
                    if ((ziU8)Zi8SetFindCand(request->scratch, ordinalIndex, work)) goto global_character_next;
                } else if (Zi8IsDupWChar(ordinalIndex, work)) goto global_character_next;
            } else if (Zi8IsDupWordW(&character, 1, work)) goto global_character_next;

            if (skipCount) --skipCount;
            else {
                ++totalResults;
                if (options->countOnly) {
                    if (totalResults >= options->maxResults) goto engine_finish;
                } else {
                    if (++((ZiChineseWork*)work)->duplicateIndex >= 64) ((ZiChineseWork*)work)->duplicateIndex = 0;
                    if (emitWords) {
                        ++emittedCount;
                        output[outputIndex++] = character;
                        output[outputIndex++] = ' ';
                        if (outputIndex > outputLimit) goto engine_finish;
                    } else output[emittedCount++] = character;
                    if (emittedCount >= request->maxCandidates) goto engine_finish;
                }
            }
global_character_next:
            ++ordinalIndex;
            record += 12;
        }
        goto engine_finish;
    }
character_pass_done:
    record = records;
    candidateCount = recordCount;
    phase = 0;
    if (phoneticRetry && match.nSeg > 1) switchedPhonetic = 1;
component_phase:
    firstOrdinal = 0;
    if (!phoneticRetry) goto component_retry;
    if (!filteringMode || match.nSeg <= 1) goto cangjie_components;
    filteringMode = 5;
    goto filtered_search;
cangjie_filtered_done:
    filteringMode = 1;
cangjie_components:
    record = records;
    candidateCount = recordCount;
    if (match.length > 1 && Zi8GetFormatVersion(1, work) >= 4 &&
        Zi8GetTableCount(1, 16, work) && elements[0] != 0xEF00 && getMode != 5) {
        rangeIndex = 0;
        rangeCount = 0;
        phoneticGroups = Zi8GetTableAddress(1, 16, work);
        switch (phase) {
        case 0: rangeIndex = 0; rangeCount = 2; phase = 1; break;
        case 1:
            switch (match.comp) {
            case 0xEF01: rangeIndex = 8; rangeCount = 10; break;
            case 0xEF02: rangeIndex = 12; rangeCount = 14; break;
            case 0xEF04: rangeIndex = 16; rangeCount = 18; break;
            case 0xEF07: rangeIndex = 20; rangeCount = 22; break;
            case 0xEF05: rangeIndex = 24; rangeCount = 26; break;
            case 0xEF06: rangeIndex = 28; rangeCount = 30; break;
            case 0xEF08: rangeIndex = 32; rangeCount = 34; break;
            case 0xEF03: rangeIndex = 36; rangeCount = 38; break;
            case 0xEF0A: rangeIndex = 24; rangeCount = 4; break;
            case 0xEF0B: rangeIndex = 20; rangeCount = 14; break;
            }
            if (request->context & 0x40) phase = 0xFF;
            else phase = 2;
            break;
        case 2: rangeIndex = 4; rangeCount = 6; phase = 0xFF; break;
        }
        firstOrdinal = phoneticGroups[rangeIndex] | (ziU16)phoneticGroups[rangeIndex + 1] << 8;
        record += firstOrdinal * 12;
        candidateCount = (phoneticGroups[rangeCount] | (ziU16)phoneticGroups[rangeCount + 1] << 8) - firstOrdinal;
    } else phase = 0xFF;
component_retry:
    remainingOrdinals = candidateCount;
    while (phoneticRetry && match.nSeg > 1) {
        if (!Zi8PriMatchNextChar(record, match.arr1[0], match.arrD[0], match.arr1[1], match.arrD[1],
                                match.arr1[2], match.arrD[2], match.arr1[3], match.arrD[3],
                                &candidateCount, &record, &candidateOrdinal, work)) {
            if (phase != 0xFF) goto component_phase;
            if (switchedPhonetic) {
                switchedPhonetic = 0;
                record = records;
                candidateCount = recordCount;
                phase = 0;
                goto component_phase;
            }
            if (!emitWords || request->getMode != 16 || match.nSeg <= 1) goto engine_finish;
            prefixSearch = 1;
            --match.nSeg;
            goto character_pass_done;
        }
        if (!(ziU8)Zi8SecMatchChar(record, componentTable, &match, &candidateOrdinal, work)) goto component_record_next;
        ordinalIndex = remainingOrdinals - candidateCount + firstOrdinal - 1;
        if (charsetTable) charsetEntry = charsetTable + ordinalIndex;
        if (charsetTable && !(charsetEntry[0] & charsetFilter)) goto component_record_next;
        currentSpelling[0] = ((ZiChineseWork*)work)->duplicateCharacters[((ZiChineseWork*)work)->duplicateIndex] = candidateOrdinal;
        ((ZiChineseWork*)work)->duplicateOrdinals[((ZiChineseWork*)work)->duplicateIndex] = ordinalIndex;
        relatedRecord = records + ordinalIndex * 12;
        phoneticGroups = phraseTable + ((relatedRecord[9] & 15) << 16 | (relatedRecord[11] | relatedRecord[10] << 8));
        if (((struct __zi8_work_data_s*)work)->cangjieEnabled) {
            switch (phoneticGroups[0] & 7) {
            case 2: phoneticGroups += 2; break;
            case 3: case 4: phoneticGroups += 3; break;
            case 5: phoneticGroups += 4; break;
            default: ++phoneticGroups; break;
            }
        }
        if (phoneticGroups[0] & 0x80) {
            groupHeader = 0;
            phoneticGroups += ((phoneticGroups[0] & 0x7F) >> 4) + 1;
        } else groupHeader = 0x80;
        while (!(groupHeader & 0x80)) {
            groupHeader = *phoneticGroups++;
            groupCount = groupHeader & 15;
            if (!(groupHeader & charset)) {
                for (; groupCount; --groupCount) {
                    for (++phoneticGroups; !(phoneticGroups[0] & 0x80); phoneticGroups += 2) {}
                    ++phoneticGroups;
                }
            }
            for (; groupCount; --groupCount) {
                candidateOrdinal = (ziU16)phoneticGroups[1] << 8 | phoneticGroups[0];
                frequencyTable = phoneticGroups;
                phoneticGroups += 2;
                duplicateIndex = 1;
component_phrase_word:
                relatedRecord = records + (candidateOrdinal & 0x7FFF) * 12;
                if (duplicateIndex < match.nSeg &&
                    (match.segsD[duplicateIndex][0] != (relatedRecord[0] & match.segs1[duplicateIndex][0]) ||
                     match.segsD[duplicateIndex][1] != (relatedRecord[1] & match.segs1[duplicateIndex][1]) ||
                     match.segsD[duplicateIndex][2] != (relatedRecord[2] & match.segs1[duplicateIndex][2]) ||
                     match.segsD[duplicateIndex][3] != (relatedRecord[3] & match.segs1[duplicateIndex][3]))) goto component_phrase_next;
                currentSpelling[duplicateIndex] = ((ziU16)relatedRecord[6] << 8) + relatedRecord[7];
                if (++duplicateIndex >= match.nSeg) {
                    if (switchedPhonetic) {
                        if (!(candidateOrdinal & 0x8000)) goto component_phrase_next;
                        goto component_phrase_charset;
                    }
                    if (duplicateIndex == match.nSeg && (candidateOrdinal & 0x8000)) goto component_phrase_next;
                    if (prefixSearch) goto component_phrase_charset;
                } else if (candidateOrdinal & 0x8000) goto component_phrase_next;
                if (candidateOrdinal & 0x8000) goto component_phrase_charset;
                candidateOrdinal = (ziU16)phoneticGroups[1] << 8 | phoneticGroups[0];
                phoneticGroups += 2;
                goto component_phrase_word;
component_phrase_charset:
                if (charsetTable) {
                    index = 0;
                    while (1) {
                        isFirstCandidate = (ziU16)frequencyTable[index * 2 + 1] << 8 | frequencyTable[index * 2];
                        charsetEntry = charsetTable + (isFirstCandidate & 0x7FFF);
                        if (!(charsetEntry[0] & charsetFilter)) { isFirstCandidate = 0; break; }
                        if (isFirstCandidate & 0x8000) break;
                        ++index;
                    }
                    if (!(isFirstCandidate & 0x8000)) goto component_phrase_next;
                }
                if (Zi8IsDupWordW(currentSpelling, duplicateIndex, work)) goto component_phrase_next;
                if (skipCount) --skipCount;
                else {
                    ++totalResults;
                    if (options->countOnly) {
                        if (totalResults >= options->maxResults) goto engine_finish;
                    } else {
                        if (++((ZiChineseWork*)work)->duplicateIndex >= 64) ((ZiChineseWork*)work)->duplicateIndex = 0;
                        currentSpelling[duplicateIndex++] = ' ';
                        if (outputIndex + duplicateIndex >= outputLimit) goto engine_finish;
                        Zi8Memcpy(output + outputIndex, currentSpelling, duplicateIndex * 2);
                        outputIndex += duplicateIndex;
                        if (++emittedCount >= request->maxCandidates) goto engine_finish;
                    }
                }
component_phrase_next:
                if (!(candidateOrdinal & 0x8000)) {
                    for (++phoneticGroups; !(phoneticGroups[0] & 0x80); phoneticGroups += 2) {}
                    ++phoneticGroups;
                }
            }
        }
component_record_next:
        record += 12;
    }
    if (getMode == 5) { candidateOrdinal = 0; recordFrequency = 0; }
    while (phoneticRetry) {
        if (getMode != 5) {
            while (exactPhrase) {
                while (match.count) {
                    if (!candidateCount--) goto frequency_range_retry;
                    if (match.arrD[0] == (record[0] & match.arr1[0]) &&
                        (ziU8)Zi8SecMatchChar(record, componentTable, &match, &candidateOrdinal, work)) goto frequency_accept;
                    record += 12;
                }
                if (!Zi8PriMatchNextChar(record, match.arr1[0], match.arrD[0], match.arr1[1], match.arrD[1],
                                        match.arr1[2], match.arrD[2], match.arr1[3], match.arrD[3],
                                        &candidateCount, &record, &candidateOrdinal, work)) {
frequency_range_retry:
                    if (phase != 0xFF) goto component_phase;
                    candidateOrdinal = 0;
                    recordFrequency = 0;
                    exactPhrase = 0;
                    continue;
                }
                if (!(ziU8)Zi8SecMatchChar(record, componentTable, &match, &candidateOrdinal, work)) {
                    record += 12;
                    continue;
                }
frequency_accept:
                ordinalIndex = remainingOrdinals - candidateCount + firstOrdinal - 1;
                if (charsetTable) charsetEntry = charsetTable + ordinalIndex;
                if (charsetTable && !(charsetEntry[0] & charsetFilter)) goto frequency_record_next;
                ((ZiChineseWork*)work)->duplicateOrdinals[((ZiChineseWork*)work)->duplicateIndex] = ordinalIndex;
                ((ZiChineseWork*)work)->duplicateCharacters[((ZiChineseWork*)work)->duplicateIndex] = candidateOrdinal;
                if (emitWords) {
                    if (!Zi8IsDupWordW(&candidateOrdinal, 1, work)) {
                        exactPhrase = 0;
                        recordFrequency = (record[4] & 0xFC) >> 2;
                    }
                } else {
                    if (trackDuplicates) {
                        if ((ziU8)Zi8SetFindCand(request->scratch, ordinalIndex, work)) {
                            record += 12;
                            continue;
                        }
                    } else if (Zi8IsDupWChar(ordinalIndex, work)) {
                        record += 12;
                        continue;
                    }
                    exactPhrase = 0;
                    recordFrequency = (record[4] & 0xFC) >> 2;
                }
frequency_record_next:
                record += 12;
            }
        }
        while (firstPhoneticPass) {
            if (!Zi8PriMatchNextComp(componentCursor, match.arr1[0], match.arrD[0], match.arr1[1], match.arrD[1],
                                    match.arr1[2], match.arrD[2], match.arr1[3], match.arrD[3],
                                    &componentIndex, &componentCursor, work)) {
                alternateCharacter = 0;
                componentFrequency = 0;
                firstPhoneticPass = 0;
            } else {
                if (Zi8SecMatchComp(componentCursor, &match, componentTable, work) &&
                    (!componentCharsetTable || (charsetFilter & componentCharsetTable[componentCount - componentIndex]))) {
                    ordinalIndex = (ziU16)(componentCount - componentIndex) * 2;
                    alternateCharacter = (ziU16)componentOrdinals[ordinalIndex + 1] << 8 | componentOrdinals[ordinalIndex];
                    firstPhoneticPass = 0;
                    componentFrequency = (componentCursor[6] & 0xFC) >> 2;
                }
                componentCursor += 8;
            }
        }
        if (alternateCharacter && componentFrequency >= recordFrequency) {
            if (!skipCount) {
                ++totalResults;
                if (emitWords) {
                    ++emittedCount;
                    output[outputIndex++] = alternateCharacter;
                    output[outputIndex++] = ' ';
                    if (outputIndex > outputLimit) goto frequency_candidates_done;
                } else output[emittedCount++] = alternateCharacter;
                if (emittedCount >= request->maxCandidates) goto frequency_candidates_done;
            } else --skipCount;
            alternateCharacter = 0;
            firstPhoneticPass = 1;
        } else {
            if (!candidateOrdinal) break;
            if (seenCount) {
                for (duplicateIndex = 0; duplicateIndex < seenCount; ++duplicateIndex) {
                    if (candidateOrdinal == seenOrdinals[duplicateIndex]) break;
                }
                if (duplicateIndex < seenCount) {
                    candidateOrdinal = 0;
                    exactPhrase = 1;
                    continue;
                }
            }
            if (candidateOrdinal != previousOrdinal) {
                previousOrdinal = candidateOrdinal;
                if (!skipCount) {
                    ++totalResults;
                    if (!options->countOnly) {
                        if (++((ZiChineseWork*)work)->duplicateIndex >= 64) ((ZiChineseWork*)work)->duplicateIndex = 0;
                        if (emitWords) {
                            ++emittedCount;
                            output[outputIndex++] = candidateOrdinal;
                            output[outputIndex++] = ' ';
                            if (outputIndex > outputLimit) goto engine_finish;
                        } else output[emittedCount++] = candidateOrdinal;
                        if (emittedCount >= request->maxCandidates) goto engine_finish;
                    } else if (totalResults >= options->maxResults) goto engine_finish;
                } else --skipCount;
            }
            candidateOrdinal = 0;
            exactPhrase = 1;
        }
    }
frequency_candidates_done:
    if (phoneticRetry) {
        if (!emitWords && emittedCount < request->maxCandidates && getMode != 5) {
            for (duplicateIndex = 0; duplicateIndex < emittedCount; ++duplicateIndex) {
                if (Zi8IsComponent(output[duplicateIndex], work)) {
                    output[duplicateIndex--] = output[--emittedCount];
                    --totalResults;
                }
            }
        }
        goto engine_finish;
    }
    if (!matchComponent) {
        if (options->countOnly || match.nCand > 1 ||
            (match.first == match.phon[0] && match.first2 == match.phon2[0])) switchedPhonetic = 0;
        else {
            switchedPhonetic = 1;
            ordinalIndex = match.phon[0];
            match.phon[0] = match.first;
            match.first = ordinalIndex;
            ordinalIndex = match.phon2[0];
            match.phon2[0] = match.first2;
            match.first2 = ordinalIndex;
        }
        phoneticMask = 0;
        phoneticMatch = 0x10;
    }
    if (filteringMode && singleCharacterPass && match.nCand == 2) {
        filteringMode = 3;
        goto filtered_search;
phonetic_filtered_done:
        filteringMode = 1;
    }
phonetic_main:
    if (Zi8GetFormatVersion(1, work) >= 4) rangeCount = Zi8GetTableCount(1, 23, work);
    else rangeCount = 0;
    if (rangeCount && match.nCand == 2 && emitWords) {
        frequencyCursor = Zi8GetTableAddress(1, 24, work);
        frequencyEntry = frequencyCursor;
        duplicateIndex = Zi8GetTableCount(1, 24, work);
        if (!duplicateIndex) isFirstCandidate = 1;
        else {
            rangeCount = 0;
            isFirstCandidate = 0;
        }
        if ((match.phon2[0] & 7) || (match.phon2[1] & 7)) isFirstCandidate = 1;
        if ((match.phon2[0] & 0x7E00) != 0x200) {
            firstValue = (match.phon2[0] >> 9) & 0x3F | 0x80;
            firstMask = (match.phon[0] >> 9) & 0x3F | 0x80;
            if (match.phon[0] & 0x1F8) isFirstCandidate = 1;
        } else {
            firstValue = (match.phon2[0] >> 3) & 0x3F;
            firstMask = (match.phon[0] >> 3) & 0x3F | 0x80;
        }
        if ((match.phon2[1] & 0x7E00) != 0x200) {
            secondValue = (match.phon2[1] >> 9) & 0x3F | 0x80;
            secondMask = (match.phon[1] >> 9) & 0x3F | 0x80;
            if (match.phon[1] & 0x1F8) isFirstCandidate = 1;
        } else {
            secondValue = (match.phon2[1] >> 3) & 0x3F;
            secondMask = (match.phon[1] >> 3) & 0x3F | 0x80;
        }
        rangeIndex = ordinalIndex = 0;
        while (ordinalIndex <= duplicateIndex) {
            frequencyEntry = frequencyCursor;
            phoneticGroupWildcard = 0;
            if (duplicateIndex) {
                rangeIndex = rangeCount;
                rangeCount = rangeCount + frequencyEntry[0];
                if (getMode == 1) {
                    if ((frequencyEntry[1] && firstValue != (frequencyEntry[1] & firstMask)) ||
                        (frequencyEntry[2] && secondValue != (frequencyEntry[2] & secondMask))) goto phonetic_group_next;
                    if (!frequencyEntry[1] || !frequencyEntry[2]) phoneticGroupWildcard = 1;
                } else {
                    if ((frequencyEntry[3] && firstValue != (frequencyEntry[3] & firstMask)) ||
                        (frequencyEntry[4] && secondValue != (frequencyEntry[4] & secondMask))) goto phonetic_group_next;
                    if (!frequencyEntry[3] || !frequencyEntry[4]) phoneticGroupWildcard = 1;
                }
            }
            alternateCursor = (ziU8*)Zi8GetTableAddress(1, 23, work);
            alternateCursor += rangeIndex * 4;
            alternateEntry = alternateCursor;
            index = rangeIndex;
            while (index < rangeCount) {
                alternateEntry = alternateCursor;
                if (!(((alternateEntry[0] & 0x80) && (charset & 0x10)) ||
                      ((alternateEntry[2] & 0x80) && (charset & 0x60)))) goto phonetic_pair_next;
                character = (ziU16)(alternateEntry[0] & 0x7F) << 8 | alternateEntry[1];
                relatedOrdinal = (ziU16)(alternateEntry[2] & 0x7F) << 8 | alternateEntry[3];
                if (charsetTable) {
                    charsetEntry = charsetTable + character;
                    if (!(charsetEntry[0] & charsetFilter)) goto phonetic_pair_next;
                    charsetEntry = charsetTable + relatedOrdinal;
                    if (!(charsetEntry[0] & charsetFilter)) goto phonetic_pair_next;
                } else {
                    record = records + character * 12;
                    if (!(record[0] & charset)) goto phonetic_pair_next;
                    record = records + relatedOrdinal * 12;
                    if (!(record[0] & charset)) goto phonetic_pair_next;
                }
                if (isFirstCandidate || phoneticGroupWildcard) {
                    record = records + character * 12;
                    candidateStatus = (Zi8GetPCode(phoneticTable, record) & match.phon[0]) == match.phon2[0];
                    if (!candidateStatus && (record[0] & 0x80) && !requireFull &&
                        Zi8MatchAltSound(alternateTable, alternateCount, phoneticTable, character,
                                         match.phon[0], match.phon2[0], charset, work)) candidateStatus = 1;
                    if (!candidateStatus) goto phonetic_pair_next;
                    record = records + relatedOrdinal * 12;
                    candidateStatus = (Zi8GetPCode(phoneticTable, record) & match.phon[1]) == match.phon2[1];
                    if (!candidateStatus && (record[0] & 0x80) && !requireFull &&
                        Zi8MatchAltSound(alternateTable, alternateCount, phoneticTable, relatedOrdinal,
                                         match.phon[1], match.phon2[1], charset, work)) candidateStatus = 1;
                    if (!candidateStatus) goto phonetic_pair_next;
                }
                output[outputIndex] = Zi8Ord2Uni(character, work);
                output[outputIndex + 1] = Zi8Ord2Uni(relatedOrdinal, work);
                output[outputIndex + 2] = ' ';
                if (!Zi8IsDupWordW(output + outputIndex, 2, work)) {
                    if (skipCount) --skipCount;
                    else {
                        ++totalResults;
                        if (!options->countOnly) {
                            ((ZiChineseWork*)work)->duplicateOrdinals[((ZiChineseWork*)work)->duplicateIndex] = character;
                            ((ZiChineseWork*)work)->duplicateCharacters[((ZiChineseWork*)work)->duplicateIndex] = output[outputIndex];
                            if (++((ZiChineseWork*)work)->duplicateIndex >= 64) ((ZiChineseWork*)work)->duplicateIndex = 0;
                            outputIndex += 3;
                            ++emittedCount;
                            if (emittedCount >= request->maxCandidates || outputIndex > outputLimit) goto engine_finish;
                        } else if (totalResults >= options->maxResults) goto engine_finish;
                    }
                }
phonetic_pair_next:
                ++index;
                alternateCursor += 4;
            }
phonetic_group_next:
            ++ordinalIndex;
            frequencyCursor += 5;
        }
    }
phonetic_candidates:
    if (exactLength && !wordMode) {
        if (!(ziU8)Zi8NewMatchPhonetic(request, (ZiChineseRecord*)records, alternateTable, alternateCount, phraseTable,
                                options, match.phon[0], match.phon2[0], phoneticMask, phoneticMatch, charset,
                                recordCount, &skipCount, &totalResults, &emittedCount, &outputIndex,
                                emitWords, trackDuplicates, getMode == 1, charsetTable, charsetEntry,
                                charsetFilter, output, work)) goto engine_finish;
        goto phonetic_tail;
    }
phonetic_component_done:
    if (filteringMode && match.nCand > 1 && (!singleCharacterPass || match.nCand != 2)) {
        filteringMode = 2;
        goto filtered_search;
ordinals_filtered_done:
        filteringMode = 1;
    }
phonetic_ordinals:
    record = records;
    candidateCount = recordCount;
    phoneticGroups = 0;
    while (emittedCount < request->maxCandidates && candidateCount) {
        if (!Zi8MatchPhonetic(phoneticTable, (ZiChineseRecord*)records, alternateTable, alternateCount,
                            phraseTable, (ZiChineseRecord*)record, match.phon, match.phon2,
                            &candidateCount, (ZiChineseRecord**)&record, (int*)&phoneticGroups,
                            emitWords, singleCharacterPass, match.nCand, phoneticMask, phoneticMatch, charset,
                            requireFull, recordCount, &candidateOrdinal, filteringMode, work)) break;
        ordinalIndex = recordCount - candidateCount - 1;
        ((ZiChineseWork*)work)->duplicateOrdinals[((ZiChineseWork*)work)->duplicateIndex] = ordinalIndex;
        ((ZiChineseWork*)work)->duplicateCharacters[((ZiChineseWork*)work)->duplicateIndex] = candidateOrdinal;
        if (!emitWords || match.nCand <= 1) frequencyTable = phoneticGroups = 0;
        else {
            frequencyTable = phoneticGroups;
            record -= 12;
            ++candidateCount;
        }
        if (charsetTable) {
            charsetEntry = charsetTable + ordinalIndex;
            if (!(charsetEntry[0] & charsetFilter)) goto phonetic_record_next;
        }
        if (charsetTable && frequencyTable) {
            index = 0;
            while (1) {
                isFirstCandidate = (ziU16)frequencyTable[index * 2 + 1] << 8 | frequencyTable[index * 2];
                charsetEntry = charsetTable + (isFirstCandidate & 0x7FFF);
                if (!(charsetEntry[0] & charsetFilter)) { isFirstCandidate = 0; break; }
                if (isFirstCandidate & 0x8000) break;
                ++index;
            }
            if (!(isFirstCandidate & 0x8000)) goto phonetic_record_next;
        }
        if (!emitWords) {
            if (candidateOrdinal == previousOrdinal) goto phonetic_record_next;
            previousOrdinal = candidateOrdinal;
            if (trackDuplicates) {
                if ((ziU8)Zi8SetFindCand(request->scratch, ordinalIndex, work)) goto phonetic_record_next;
            } else if (Zi8IsDupWChar(ordinalIndex, work)) goto phonetic_record_next;
        } else {
            emittedWords = 0;
            output[outputIndex + emittedWords++] = candidateOrdinal;
            if (match.nCand > 1) {
                do {
                    character = (ziU16)frequencyTable[1] << 8 | frequencyTable[0];
                    frequencyTable += 2;
                    output[outputIndex + emittedWords++] = Zi8Ord2Uni(character & 0x7FFF, work);
                } while (!(character & 0x8000));
            }
            if (prefixSearch) {
                if (request->elementCount) emittedWords = match.nCand;
                else emittedWords = 1;
            }
            if (Zi8IsDupWordW(output + outputIndex, emittedWords, work)) goto phonetic_record_next;
        }
        if (skipCount) --skipCount;
        else {
            ++totalResults;
            if (!options->countOnly) {
                if (++((ZiChineseWork*)work)->duplicateIndex >= 64) ((ZiChineseWork*)work)->duplicateIndex = 0;
                if (emitWords) {
                    ++emittedCount;
                    outputIndex += emittedWords;
                    output[outputIndex++] = ' ';
                    if (emittedCount >= request->maxCandidates || outputIndex > outputLimit) goto engine_finish;
                } else output[emittedCount++] = candidateOrdinal;
            } else if (totalResults >= options->maxResults) goto engine_finish;
        }
phonetic_record_next:
        record += 12;
    }
    if (emitWords && request->getMode != 12 && request->getMode != 13 && match.nCand > 1 && singleCharacterPass) {
        singleCharacterPass = 0;
        goto phonetic_component_done;
    }
    if (emitWords && (request->getMode == 12 || request->getMode == 13) && match.nCand > 1 && singleCharacterPass) {
        --match.nCand;
        goto phonetic_component_done;
    }
phonetic_tail:
    if (!switchedPhonetic || emittedCount >= request->maxCandidates) goto engine_finish;
    if (prefixLookup) {
        prefixLookup = 0;
        goto user_character_search;
    }
phonetic_alt_continue:
    switchedPhonetic = 0;
    record = records;
    candidateCount = recordCount;
    phoneticMask = match.phon[0];
    phoneticMatch = match.phon2[0];
    match.phon[0] = match.first;
    match.phon2[0] = match.first2;
    match.first = phoneticMask;
    match.first2 = phoneticMatch;
    if (phoneticInput) {
        phoneticInput = 0;
        matchComponent = 1;
        goto phonetic_ordinal_search;
    }
    goto phonetic_candidates;
engine_finish:
    if (resultFallback && request->elementCount && (getMode == 7 || getMode == 8 || getMode == 9) &&
        ((options->countOnly && totalResults < options->maxResults) || (!options->countOnly && emittedCount < request->maxCandidates))) {
        resultFallback = 0;
        goto candidate_dictionary_search;
    }
    if (getMode == 9 && request->getMode == 10 &&
        (request->elementCount != 3 || elements[2] != ' ') &&
        ((options->countOnly && totalResults < options->maxResults) || (!options->countOnly && emittedCount < request->maxCandidates))) {
        getMode = 7;
        goto candidate_dictionary_search;
    }
    if (emitWords && outputIndex) output[outputIndex++] = 0;
    request->letters = emittedCount;
    if (!totalResults && !request->firstCandidate && getMode == 1 && match.nCand > 1 &&
        (match.phon2[match.nCand - 1] & 0xFFF8) == 0x7600) {
        match.phon[match.nCand - 1] = (match.phon[match.nCand - 1] & 7) + 0x7FF8;
        match.phon2[match.nCand - 1] = (match.phon2[match.nCand - 1] & 7) + 0x398;
        singleCharacterPass = 1;
        goto engine_search;
    }
    if (savedPudCount) ((struct __zi8_work_data_s*)work)->pudCount = savedPudCount;
    Zi8LogError(100, work);
    return totalResults;
filtered_search:
    userIndex = Zi8GetTableCount(1, 31, work);
    frequencyTable = Zi8GetTableAddress(1, 31, work);
    for (; userIndex; --userIndex) {
        index = frequencyTable[0] & 15;
        if (!(*frequencyTable++ & charset)) goto filtered_next;
        rangeIndex = 0;
        if (filteringMode == 4) {
            rangeIndex = request->wordCharCount;
            if (index <= rangeIndex) goto filtered_next;
            if (request->elementCount) {
                switch (getMode) {
                case 0:
                    if (index < rangeIndex + match.nSeg) goto filtered_next;
                    break;
                case 1:
                case 2:
                    if (index < rangeIndex + match.nCand) goto filtered_next;
                    break;
                }
            }
            rangeCount = 0;
            currentWord = request->currentWord;
            for (; rangeCount < rangeIndex; ++rangeCount) {
                character = frequencyTable[rangeCount * 2] + ((ziU16)frequencyTable[rangeCount * 2 + 1] << 8);
                record = records + character * 12;
                candidateOrdinal = ((ziU16)record[6] << 8) + record[7];
                if (candidateOrdinal != *currentWord++) goto filtered_next;
            }
        } else if (filteringMode == 2 || filteringMode == 3) {
            if (index < match.nCand || (singleCharacterPass && index != match.nCand) ||
                (!singleCharacterPass && index <= match.nCand)) goto filtered_next;
        } else if (filteringMode == 5) {
            if (index < match.nSeg || (singleCharacterPass && index != match.nSeg) ||
                (!singleCharacterPass && index <= match.nSeg)) goto filtered_next;
        }
        ordinalIndex = frequencyTable[rangeIndex * 2] + ((ziU16)frequencyTable[rangeIndex * 2 + 1] << 8);
        record = records + ordinalIndex * 12;
        candidateOrdinal = ((ziU16)record[6] << 8) + record[7];
        if (request->elementCount) {
            switch (getMode) {
            case 7:
            case 8:
                phraseEntry = phraseTable + ((record[9] & 15) << 16 | (record[11] | record[10] << 8));
                if ((phraseEntry[0] & 7) >= match.length &&
                    match.arr1D[0] == (match.arr19[0] & phraseEntry[0]) &&
                    match.arr1D[1] == (match.arr19[1] & phraseEntry[1]) &&
                    match.arr1D[2] == (match.arr19[2] & phraseEntry[2]) &&
                    match.arr1D[3] == (match.arr19[3] & phraseEntry[3])) goto filtered_accept;
                if (getMode == 7) goto filtered_next;
            case 9:
                phraseEntry = phraseTable + ((record[9] & 15) << 16 | (record[11] | record[10] << 8));
                rangeCount = phraseEntry[0] & 7;
                if ((phraseEntry[0] & phraseMasks[rangeCount].bytes[0]) != phraseValues[rangeCount].bytes[0] ||
                    (phraseEntry[1] & phraseMasks[rangeCount].bytes[1]) != phraseValues[rangeCount].bytes[1] ||
                    (phraseEntry[2] & phraseMasks[rangeCount].bytes[2]) != phraseValues[rangeCount].bytes[2] ||
                    (phraseEntry[3] & phraseMasks[rangeCount].bytes[3]) != phraseValues[rangeCount].bytes[3]) goto filtered_next;
                break;
            case 0:
                if (match.arrD[0] != (record[0] & match.arr1[0]) ||
                    (!match.count && (match.arrD[3] != (record[3] & match.arr1[3]) ||
                                     match.arrD[2] != (record[2] & match.arr1[2]) ||
                                     match.arrD[1] != (record[1] & match.arr1[1]))) ||
                    !(ziU8)Zi8SecMatchChar(record, componentTable, &match, 0, work)) goto filtered_next;
                for (rangeCount = 1; rangeCount < match.nSeg; ++rangeCount) {
                    record = (ziU8*)((ZiChineseRecord*)records + (ziU16)frequencyTable[(rangeIndex + rangeCount) * 2] +
                                     ((ziU16)frequencyTable[(rangeIndex + rangeCount) * 2 + 1] << 8));
                    if (match.segsD[rangeCount][0] != (record[0] & match.segs1[rangeCount][0]) ||
                        match.segsD[rangeCount][1] != (record[1] & match.segs1[rangeCount][1]) ||
                        match.segsD[rangeCount][2] != (record[2] & match.segs1[rangeCount][2]) ||
                        match.segsD[rangeCount][3] != (record[3] & match.segs1[rangeCount][3])) goto filtered_next;
                }
                break;
            case 1:
            case 2:
                phoneticGroups = frequencyTable + (index + rangeIndex) * 2;
                rangeCount = 0;
                while (rangeCount < match.nCand) {
                    if (match.phon2[rangeCount] !=
                        (match.phon[rangeCount] & ((ziU16)phoneticGroups[0] + ((ziU16)phoneticGroups[1] << 8)))) goto filtered_next;
                    ++rangeCount;
                    phoneticGroups += 2;
                }
                break;
            }
        }
filtered_accept:
        ((ZiChineseWork*)work)->duplicateOrdinals[((ZiChineseWork*)work)->duplicateIndex] = ordinalIndex;
        ((ZiChineseWork*)work)->duplicateCharacters[((ZiChineseWork*)work)->duplicateIndex] = candidateOrdinal;
        if (charsetTable) {
            for (rangeCount = rangeIndex; rangeCount < index; ++rangeCount) {
                character = frequencyTable[rangeCount * 2] + ((ziU16)frequencyTable[rangeCount * 2 + 1] << 8);
                charsetEntry = charsetTable + character;
                if (!(charsetEntry[0] & charsetFilter)) goto filtered_next;
            }
        }
        if (!emitWords) {
            if (candidateOrdinal == previousOrdinal) goto filtered_next;
            previousOrdinal = candidateOrdinal;
            if (trackDuplicates) {
                if ((ziU8)Zi8SetFindCand(request->scratch, ordinalIndex, work)) goto filtered_next;
            } else if (Zi8IsDupWChar(ordinalIndex, work)) goto filtered_next;
            rangeCount = 1;
        } else {
            for (rangeCount = 0; rangeCount < index - rangeIndex; ++rangeCount) {
                character = frequencyTable[(rangeCount + rangeIndex) * 2] +
                            ((ziU16)frequencyTable[(rangeCount + rangeIndex) * 2 + 1] << 8);
                record = records + character * 12;
                output[outputIndex + rangeCount] = ((ziU16)record[6] << 8) + record[7];
            }
            if (prefixSearch || filteringMode == 4) {
                if (!request->elementCount) rangeCount = 1;
                else if (filteringMode == 4) {
                    if ((getMode == 1 || getMode == 2) && match.nCand) rangeCount = match.nCand;
                    else if (getMode == 0 && match.nSeg > 1) rangeCount = match.nSeg;
                    else rangeCount = 1;
                } else if (filteringMode == 5) rangeCount = match.nSeg;
                else rangeCount = match.nCand;
            }
            if (Zi8IsDupWordW(output + outputIndex, rangeCount, work)) goto filtered_next;
        }
        if (skipCount) --skipCount;
        else {
            ++totalResults;
            if (filteringMode == 4 && getOptions == 5) {
                if (totalResults >= options->maxResults) goto engine_finish;
            } else if (!options->countOnly) {
                if (++((ZiChineseWork*)work)->duplicateIndex >= 64) ((ZiChineseWork*)work)->duplicateIndex = 0;
                if (filteringMode == 4) request->unk_0x20 = emittedCount + 1;
                if (emitWords) {
                    ++emittedCount;
                    outputIndex += rangeCount;
                    output[outputIndex++] = ' ';
                    if (outputIndex > outputLimit) goto engine_finish;
                } else output[emittedCount++] = candidateOrdinal;
                if (emittedCount >= request->maxCandidates) goto engine_finish;
            } else if (totalResults >= options->maxResults) goto engine_finish;
        }
filtered_next:
        frequencyTable += index * 4;
    }
    switch (filteringMode) {
    case 4: goto context_word_filter;
    case 2: goto ordinals_filtered_done;
    case 3: goto phonetic_filtered_done;
    case 5: goto cangjie_filtered_done;
    }
    goto engine_finish;

}

static int Zi8NewMatchPhonetic(ziGetParam* request, ZiChineseRecord* records,
                              ziPtr indexTable, ziU16 indexCount, ziPtr dictionary,
                              ZiChineseOptions* options, ziU16 mask, ziU16 match, ziU16 excludedMask,
                              ziU16 excludedMatch, ziU8 charset, ziU16 recordCount,
                              ziU16* skipCount, int* resultCount, ziU8* candidateCount,
                              int* outputCount, ziU8 wordMode, ziU8 useFoundCandidates,
                              ziU8 pinyin, ziU8* charsetTable, ziU8* charsetEntry,
                              ziU8 charsetFilter, ziWChar* output, ziPtr work) {
    ziU16* phoneticOffsets;
    ziU16* ordinalTable;
    ziU8* phonetics;
    int totalResults;
    int emittedCharacters;
    ZiChineseRecord* matchedRecord;
    ziU8* phoneticGroups;
    ziU8* candidateGroups;
    int matchedIndex;
    int capacity;
    ziU8* groupCandidates;
    ziU16 phoneticCount;
    ziU16 phoneticIndex;
    ziU16 candidateIndex;
    ziU16 character;
    ziU16 rangeBegin;
    ziU16 rangeEnd;
    ziU16 previousCharacter;
    ziU16 remainingSkip;
    ziU16 filteredMask;
    ziU16 filteredMatch;
    ziU16 matchedLength;
    ziU16 groupCount;
    ziU16 matchedTone;
    ziU16 groupOffset;
    ziU16 groupSize;
    ziU8 emittedCount;
    ziU8 stopAfterTone;

    previousCharacter = 0;
    remainingSkip = *skipCount;
    totalResults = *resultCount;
    emittedCount = *candidateCount;
    emittedCharacters = *outputCount;
    stopAfterTone = 0;
    phoneticGroups = ZI8_NULL;
    candidateGroups = ZI8_NULL;
    capacity = options->capacity - 64;
    Zi8LogError(100, work);
    if ((mask & 7) == 7) {
        stopAfterTone = match & 7;
    }
    phoneticOffsets = Zi8GetTableAddress(1, 13, work);
    ordinalTable = Zi8GetTableAddress(1, 14, work);
    if (pinyin) {
        phonetics = Zi8GetTableAddress(1, 3, work);
        phoneticCount = Zi8GetTableCount(1, 3, work);
        phoneticGroups = Zi8GetTableAddress(1, 17, work);
        groupCount = Zi8GetTableCount(1, 17, work);
        candidateGroups = Zi8GetTableAddress(1, 18, work);
    } else {
        phonetics = Zi8GetTableAddress(1, 4, work);
        phoneticCount = Zi8GetTableCount(1, 4, work);
        phoneticGroups = Zi8GetTableAddress(1, 19, work);
        groupCount = Zi8GetTableCount(1, 19, work);
        candidateGroups = Zi8GetTableAddress(1, 20, work);
    }

    if (groupCount) {
        groupOffset = 0;
        filteredMask = mask | 7;
        filteredMatch = match;
        for (phoneticIndex = 0; phoneticIndex < groupCount; ++phoneticIndex) {
            character = phoneticGroups[0] | (ziU16)phoneticGroups[1] << 8;
            groupSize = phoneticGroups[2] | (ziU16)phoneticGroups[3] << 8;
            if (excludedMatch == (character & excludedMask) ||
                filteredMatch != (character & filteredMask)) {
                groupOffset += groupSize;
                phoneticGroups += 4;
                continue;
            }
            groupCandidates = candidateGroups + groupOffset * 2;
            candidateIndex = 0;
            while (candidateIndex < groupSize) {
                character = groupCandidates[0] | (ziU16)groupCandidates[1] << 8;
                if (!(charset & records[character].flags)) {
                    goto next_group_candidate;
                }
                if (charsetTable) {
                    charsetEntry = charsetTable + character;
                    if (!(*charsetEntry & charsetFilter)) {
                        goto next_group_candidate;
                    }
                }
                if (!wordMode) {
                    if (useFoundCandidates) {
                        if ((ziU8)Zi8SetFindCand(request->scratch, character, work)) {
                            goto next_group_candidate;
                        }
                    } else if (Zi8IsDupWChar(character, work)) {
                        goto next_group_candidate;
                    }
                }
                ((ZiChineseWork*)work)->duplicateOrdinals[((ZiChineseWork*)work)->duplicateIndex] = character;
                character = Zi8Ord2Uni(character, work);
                ((ZiChineseWork*)work)->duplicateCharacters[((ZiChineseWork*)work)->duplicateIndex] = character;
                if (character == previousCharacter) {
                    goto next_group_candidate;
                }
                previousCharacter = character;
                if (wordMode && Zi8IsDupWordW(&character, 1, work)) {
                    goto next_group_candidate;
                }
                if (remainingSkip) {
                    --remainingSkip;
                    goto next_group_candidate;
                }
                ++totalResults;
                if (!options->countOnly) {
                    if (++((ZiChineseWork*)work)->duplicateIndex >= 64) {
                        ((ZiChineseWork*)work)->duplicateIndex = 0;
                    }
                    if (wordMode) {
                        ++emittedCount;
                        output[emittedCharacters++] = character;
                        output[emittedCharacters++] = 0x20;
                        if (emittedCharacters > capacity) {
                            *skipCount = remainingSkip;
                            *resultCount = totalResults;
                            *candidateCount = emittedCount;
                            *outputCount = emittedCharacters;
                            Zi8ReplaceLastError(0xB54, work);
                            return 0;
                        }
                    } else {
                        output[emittedCount++] = character;
                    }
                    if (emittedCount >= request->maxCandidates) {
                        *skipCount = remainingSkip;
                        *resultCount = totalResults;
                        *candidateCount = emittedCount;
                        *outputCount = emittedCharacters;
                        Zi8ReplaceLastError(0xB55, work);
                        return 0;
                    }
                } else if (totalResults >= options->maxResults) {
                    *skipCount = remainingSkip;
                    *resultCount = totalResults;
                    *candidateCount = emittedCount;
                    *outputCount = emittedCharacters;
                    Zi8ReplaceLastError(0xB56, work);
                    return 0;
                }
next_group_candidate:
                ++candidateIndex;
                groupCandidates += 2;
            }
            if (stopAfterTone) {
                break;
            }
            groupOffset += groupSize;
            phoneticGroups += 4;
        }
    }
    filteredMask = mask & 0xFFF8;
    filteredMatch = match & 0xFFF8;
    for (phoneticIndex = 1; phoneticIndex < phoneticCount; ++phoneticIndex) {
        character = phonetics[phoneticIndex * 2] | (ziU16)phonetics[phoneticIndex * 2 + 1] << 8;
        if (filteredMatch != (character & filteredMask) ||
            excludedMatch == (character & excludedMask)) {
            continue;
        }
        rangeBegin = phoneticOffsets[phoneticIndex];
        rangeEnd = phoneticOffsets[phoneticIndex + 1];
        rangeBegin = ((ziU8)rangeBegin << 8) | ((rangeBegin >> 8) & 0xFF);
        rangeEnd = ((ziU8)rangeEnd << 8) | ((rangeEnd >> 8) & 0xFF);
        for (candidateIndex = rangeBegin; candidateIndex < rangeEnd; ++candidateIndex) {
            character = ordinalTable[candidateIndex];
            character = ((ziU8)character << 8) | ((character >> 8) & 0xFF);
            if (character >= recordCount || !(charset & records[character].flags)) {
                continue;
            }
            if (charsetTable) {
                charsetEntry = charsetTable + character;
                if (!(*charsetEntry & charsetFilter)) {
                    continue;
                }
            }
            if (stopAfterTone) {
                matchedRecord = records + character;
                matchedLength = 0;
                matchedIndex = 0;
                if (!Zi8MatchPhonetic(phonetics, records, indexTable, indexCount,
                                      dictionary, matchedRecord, &mask, &match,
                                      &matchedLength, &matchedRecord, &matchedIndex,
                                      wordMode, 1, 1, excludedMask, excludedMatch,
                                      charset, request->getOptions & 0x40, character,
                                      &matchedTone, 0, work)) {
                    continue;
                }
            }
            if (!wordMode) {
                if (useFoundCandidates) {
                    if ((ziU8)Zi8SetFindCand(request->scratch, character, work)) {
                        continue;
                    }
                } else if (Zi8IsDupWChar(character, work)) {
                    continue;
                }
            }
            ((ZiChineseWork*)work)->duplicateOrdinals[((ZiChineseWork*)work)->duplicateIndex] = character;
            character = Zi8Ord2Uni(character, work);
            ((ZiChineseWork*)work)->duplicateCharacters[((ZiChineseWork*)work)->duplicateIndex] = character;
            if (character == previousCharacter) {
                continue;
            }
            previousCharacter = character;
            if (wordMode && Zi8IsDupWordW(&character, 1, work)) {
                continue;
            }
            if (remainingSkip) {
                --remainingSkip;
                continue;
            }
            ++totalResults;
            if (!options->countOnly) {
                if (++((ZiChineseWork*)work)->duplicateIndex >= 64) {
                    ((ZiChineseWork*)work)->duplicateIndex = 0;
                }
                if (wordMode) {
                    ++emittedCount;
                    output[emittedCharacters++] = character;
                    output[emittedCharacters++] = 0x20;
                    if (emittedCharacters > capacity) {
                        *skipCount = remainingSkip;
                        *resultCount = totalResults;
                        *candidateCount = emittedCount;
                        *outputCount = emittedCharacters;
                        Zi8ReplaceLastError(0xB54, work);
                        return 0;
                    }
                } else {
                    output[emittedCount++] = character;
                }
                if (emittedCount >= request->maxCandidates) {
                    *skipCount = remainingSkip;
                    *resultCount = totalResults;
                    *candidateCount = emittedCount;
                    *outputCount = emittedCharacters;
                    Zi8ReplaceLastError(0xB55, work);
                    return 0;
                }
            } else if (totalResults >= options->maxResults) {
                *skipCount = remainingSkip;
                *resultCount = totalResults;
                *candidateCount = emittedCount;
                *outputCount = emittedCharacters;
                Zi8ReplaceLastError(0xB56, work);
                return 0;
            }
        }
    }
    *skipCount = remainingSkip;
    *resultCount = totalResults;
    *candidateCount = emittedCount;
    *outputCount = emittedCharacters;
    return 1;
}

ziU8 Zi8GetElementCount(ziWChar* elements, ziU8 elementCount, ziU8 charCount ZI_NEED_WORK) {
    ziU8 spacedIndex;
    ziU8 elementIndex;
    ziU8 count;
    ziWChar spacedElements[256];
    struct { ziWChar separator; } savedState;
    savedState.separator = ZI_WORK->separator;
    if (elementCount <= 1 || !charCount) {
        return elementCount;
    }
    for (spacedIndex = 0; spacedIndex < elementCount; ++spacedIndex) {
        if (elements[spacedIndex] != ';' &&
            (elements[spacedIndex] < 'a' || elements[spacedIndex] > 'z')) {
            break;
        }
    }
    if (spacedIndex == elementCount) {
        return elementCount;
    }
    ZI_WORK->separator = 0xF360;
    Zi8ZHaddSpace(elements, elementCount, spacedElements, 256, __zi8_work_data);
    ZI_WORK->separator = savedState.separator;
    spacedIndex = elementIndex = count = 0;
    while (charCount && elementIndex < elementCount) {
        if (spacedElements[spacedIndex] == 0xF360) {
            --charCount;
            if (elements[elementIndex] != 0xF360) {
                goto next_spaced_element;
            }
        } else if (spacedElements[spacedIndex] >= 0xF331 && spacedElements[spacedIndex] <= 0xF335) {
            --charCount;
            if (elements[elementIndex + 1] == 0xF360) {
                ++spacedIndex;
                ++elementIndex;
                ++count;
            }
        }
        ++elementIndex;
        ++count;
next_spaced_element:
        ++spacedIndex;
    }
    return count;
}


int Zi8GetChineseCandidates(ziGetParam* request, ZiChineseOptions* options, ziPtr work) {
    ziU8 savedCountOnly;
    int savedMaxResults;
    int length;
    ziGetParam suffixRequest;
    if (request->firstCandidate || request->elementCount <= 1) {
get_candidates:
        return zi8InternalGetZH(request, options, work);
    }
    switch (request->getMode) {
        case 16:
            if (request->elements[request->elementCount - 1] == 0xF360) {
                goto get_candidates;
            }
            for (length = request->elementCount - 2; length > 0; --length) {
                if (request->elements[length] == 0xF360) {
                    break;
                }
            }
            if (length++ <= 0) {
                goto get_candidates;
            }
            break;
        case 12:
        case 13:
            switch (request->elements[request->elementCount - 1]) {
                case 0xF331:
                case 0xF332:
                case 0xF333:
                case 0xF334:
                case 0xF335:
                case 0xF360:
                    break;
                default:
                    goto get_candidates;
            }
            for (length = 1; length < 64; ++length) {
                if (Zi8GetElementCount(request->elements, request->elementCount, length, work) >= request->elementCount) {
                    break;
                }
            }
            if (length-- == 1) {
                goto get_candidates;
            }
            length = Zi8GetElementCount(request->elements, request->elementCount, length, work);
            break;
        default:
            goto get_candidates;
    }
    suffixRequest = *request;
    savedCountOnly = options->countOnly;
    savedMaxResults = options->maxResults;
    suffixRequest.elements = request->elements + length;
    suffixRequest.elementCount = (ziU8)(suffixRequest.elementCount - length);
    savedCountOnly = options->countOnly;
    options->countOnly = 1;
    savedMaxResults = options->maxResults;
    options->maxResults = 1;
    length = zi8InternalGetZH(&suffixRequest, options, work);
    options->countOnly = savedCountOnly;
    options->maxResults = savedMaxResults;
    if (!length) {
        Zi8LogError(0x1388, work);
        return 0;
    }
    return zi8InternalGetZH(request, options, work);
}

const ziWChar ziTones[4] = {0x02CA, 0x02C7, 0x02CB, 0x02D9};
const ziWChar ziPuncts[4] = {0xFF0C, 0x3002, 0xFF1F, 0xFF01};
