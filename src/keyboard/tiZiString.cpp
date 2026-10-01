#define TIZISTRING_IMPLEMENTATION
#include "keyboard/tiZiString.h"
#include "keyboard/tiUtil.h"
#include "keyboard/tiCpData.h"
#include <wchar.h>
#include <string.h>

namespace textinput {
namespace tistring {
inline Decolated::~Decolated() {}

struct OEMDictionary {
    s32 count;
    s32 offsets[1];
};

u16 WithZi::ElementBuffer[0x100];
u16 WithZi::CandidatesBuffer[0x300];
u16 WithZi::CandidatedWord[0xa00];
u16 WithZi::LatestWord[0x40];

static const wchar_t kKoreanFinalLetters[12] = {
    L'y', L'u', L'i', L'o', L'p', L'h', L'j', L'k', L'l', L'b', L'n', L'm'
};

static const wchar_t kKoreanLeadingLetters[16] = L"qwertasdfgzxcv";

static bool SearchOEMDictionary(u16, u16*, u8, void*);

static u8 LatinSearchOrder[10] = {3, 3, 2, 1, 4, 7, 6, 5, 8, 0};

static bool SearchOEMDictionary(u16 index, u16* output, u8 maxLength, void* dictionary) {
    OEMDictionary* entries = static_cast<OEMDictionary*>(dictionary);
    if (static_cast<s32>(index) >= entries->count) {
        return false;
    }
    s32 offset = entries->offsets[index];
    u8* dictionaryBytes = static_cast<u8*>(dictionary);
    wchar_t* word = reinterpret_cast<wchar_t*>(dictionaryBytes + offset);
    u32 length = wcslen(word);
    if (static_cast<u32>(maxLength) <= length) {
        return false;
    }
    wcscpy((wchar_t*)output, word);
    return true;
}

void WithZi::ChangeDictionaryLanguage(u8 language) {
    if (mDictionaryLanguage != language) {
        mDictionaryLanguage = language;
        if (mOemDictionaryId != 0) {
            EZTXDetachOEMDict(mOemDictionaryId & 0xff, mpDictionaryWork);
        }
        EZTXLanguageEntry* entry;
        EZTXLanguageEntry* dictionaryTable;
        s32 entryIndex;
        s32 baseIndex;
        u32* dictionaryEntry;
        u32 attached;
        entryIndex = -1;
        baseIndex = 0;
        dictionaryTable = (EZTXLanguageEntry*)mpDictionaries;
        entry = dictionaryTable;
        for (s32 groups = 2; groups != 0; --groups) {
            for (s32 column = 0; column < 6; ++column) {
                if (language == entry->language) entryIndex = baseIndex;
                ++entry;
                ++baseIndex;
            }
        }
        if (entryIndex != -1) {
            dictionaryEntry = reinterpret_cast<u32*>(dictionaryTable[entryIndex].table);
            if (dictionaryEntry == NULL) goto noDictionary;
            attached = EZTXAttachOEMDict(
                (u8*)SearchOEMDictionary, *dictionaryEntry & 0xffff,
                dictionaryEntry, mpDictionaryWork);
            mOemDictionaryId = attached & 0xff;
            goto dictionaryReady;
        noDictionary:
            mOemDictionaryId = 0;
        dictionaryReady:
            ;
        }
    }
}

WithZi::~WithZi() {
    MEMFreeToAllocator(mpAllocator, mpDictionaryWork);
}

void WithZi::create(MEMAllocator* allocator) {
    StringBase::create(allocator);
    void* globalData = MEMAllocFromAllocator(allocator, EZTXGetGlobalDataSize());
    EZTXGetGlobalDataSize();
    mpDictionaryWork = globalData;
    mOemDictionaryId = 0;
    init();
}

void WithZi::init() {
    if (mbDictionaryOpen != 0) {
        mbContextChanged = 0;
        clearCandidates();
        memset(LatestWord, 0, 0x80);
        LatestWord[0] = 0x20;
        if (getPredictLanguage() == 1) {
            update();
        }
    }
}

void WithZi::clearCandidates() {
    if (mbDictionaryOpen != 0) {
        mInputLength = 0;
        mCandidateCount = 0;
        memset(ElementBuffer, 0, 0x1fe);
        memset(CandidatesBuffer, 0, 0x200);
        memset(CandidatesBuffer + 0x100, 0, 0x1fe);
        memset(CandidatesBuffer + 0x200, 0, 0x200);
        memset(CandidatedWord, 0, 0x1400);
        memset(&mSearch, 0, sizeof(mSearch) + sizeof(mSearchState));
        mSearch.language = getPredictLanguage();
        mSearch.subLanguage = 7;
        mSearch.getMode = 0;
        mSearch.context = 1;
        mSearch.getOptions = 0x81;
        mSearch.elements = reinterpret_cast<wchar_t*>(ElementBuffer);
        mSearch.candidates = reinterpret_cast<wchar_t*>(&CandidatesBuffer[0x200]);
        mSearch.maxCandidates = 0x28;
        mSearch.elementCount = 0;
        mSearch.firstCandidate = 0;
        if (getPredictLanguage() == 1) {
            mSearch.getMode = 1;
            mSearch.context = 0x10;
        }
        EZTXGetCandidates(&mSearch, mpDictionaryWork);
    }
}

void WithZi::openDictionary(void* ziDictionary, void* oemDictionary) {
    EZTXInitialize(ziDictionary, mpDictionaryWork);
    mbDictionaryOpen = 1;
    mpDictionaries = static_cast<EZTXLanguageEntry*>(oemDictionary);
    EZTXSetLatinSearchOrder(LatinSearchOrder, 10, mpDictionaryWork);
    mOemDictionaryId = 0;
}

void WithZi::pushBack(wchar_t) {}

void WithZi::popBack() {}

void WithZi::inputChar(wchar_t character) {
    if (hasCandidate()) {
        if (mInputLength != 0) {
            --mInputLength;
            CandidatesBuffer[mInputLength] = 0;
        }
        mwcCandidate = 0;
    }
    CandidatesBuffer[mInputLength] = character;
    u16 index = mInputLength++;
    CandidatesBuffer[(index + 1) & 0xffff] = 0;
    update();
}

void WithZi::setInputting(wchar_t character) {
    if (hasCandidate()) {
        if (mInputLength != 0) {
            --mInputLength;
            CandidatesBuffer[mInputLength] = 0;
        }
        mwcCandidate = 0;
    }
    inputChar(character);
    mwcCandidate = character;
}

void WithZi::backSpace() {
    if (hasCandidate()) {
        if (mInputLength != 0) {
            --mInputLength;
            CandidatesBuffer[mInputLength] = 0;
        }
        mwcCandidate = 0;
    }
    else {
        if (mInputLength != 0) {
            --mInputLength;
            CandidatesBuffer[mInputLength] = 0;
            update();
        }
    }
}

void WithZi::confirm(const wchar_t*) {
    update();
}

bool WithZi::moveCursorRight() {
    return false;
}

bool WithZi::moveCursorLeft() {
    return false;
}

void WithZi::getPredicted(int index, wchar_t* output) {
    const wchar_t* candidate = reinterpret_cast<const wchar_t*>(CandidatedWord + index * 0x40);
    s32 length = 0;
    while (candidate[length] != 0) {
        output[length] = candidate[length];
        ++length;
    }
    output[length] = 0;
}

wchar_t* WithZi::getCurrentSelected() {
    if ((mSelectedCandidate < 0) || (mSelectedCandidate >= 0x28)) {
        return NULL;
    }
    return reinterpret_cast<wchar_t*>(CandidatedWord + mSelectedCandidate * 0x40);
}

u32 WithZi::getCurrentInput(wchar_t* output, u32 maxLength) {
    u16* source;
    wchar_t* destination;
    s32 count = 0;
    if (0x100 < maxLength) {
        maxLength = 0x100;
    }
    source = CandidatesBuffer;
    destination = output;
    u32 index = 0;
    for (index = 0; index < maxLength; index++) {
        wchar_t character = *source;
        *destination = character;
        if (*destination == 0) {
            break;
        }
        if (mLetterMode == LM_2) {
            *destination = util::toWUpper(*destination);
        }
        ++count;
        ++source;
        ++destination;
    }
    if (mLetterMode == LM_0) {
        *output = util::toWUpper(*output);
    }
    return count;
}

wchar_t* WithZi::getCurrentInput() {
    return (wchar_t*)CandidatesBuffer;
}

static inline bool IsKoreanLeadingLetter(wchar_t value) {
    for (s32 index = 0; index < 14; ++index) {
        if (value == kKoreanLeadingLetters[index]) return true;
    }
    return false;
}

void WithZi::partialConfirmForKR() {
    if (mInputLength <= 1) return;
    bool match;
    s32 index;
    const wchar_t* letters;
    wchar_t value = util::toWLower(CandidatesBuffer[mInputLength - 1]);
    letters = kKoreanFinalLetters;
    for (index = 0; index < 12; ++index) {
        if (value == *letters) {
            match = true;
            goto finalLetterChecked;
        }
        ++letters;
    }
    match = false;
finalLetterChecked:
    if (!match) goto keepLastLetter;
    value = util::toWLower(CandidatesBuffer[mInputLength - 2]);
    if (!IsKoreanLeadingLetter(value)) goto keepLastLetter;
    CandidatesBuffer[0] = CandidatesBuffer[mInputLength - 2];
    CandidatesBuffer[1] = CandidatesBuffer[mInputLength - 1];
    mInputLength = 2;
    goto confirmLetters;
keepLastLetter:
    CandidatesBuffer[0] = CandidatesBuffer[mInputLength - 1];
    mInputLength = 1;
confirmLetters:
    CandidatesBuffer[mInputLength] = 0;
    update();
}

void WithZi::update() {
    if (mbDictionaryOpen == 0) {
        return;
    }

    wchar_t* candidateOutput = reinterpret_cast<wchar_t*>(&CandidatesBuffer[0x200]);
    mSelectedCandidate = 0;
    s32 elementCount = static_cast<u16>(setElementBuffer());
    mSearch.language = getPredictLanguage();
    mSearch.subLanguage = 7;
    mSearch.getMode = 0;
    mSearch.context = 1;
    mSearch.getOptions = 0x81;
    mSearch.elements = reinterpret_cast<wchar_t*>(ElementBuffer);
    mSearch.candidates = candidateOutput;
    mSearch.maxCandidates = 0x28;
    mSearch.elementCount = static_cast<u8>(elementCount);
    mSearch.firstCandidate = 0;
    mSearch.currentWord = 0;
    mSearch.wordCharCount = 0;
    mSearch.count = 0;
    mSearch.letters = 0;
    mSearch.completion = 0;
    mSearch.scratch = 0;

    if (getPredictLanguage() == 1) {
        mSearch.getMode = 1;
        mSearch.context = 0x11;
        if (mbKoreanPartialConfirm != 0) {
            mSearch.context |= 0x20;
            mSearch.getOptions |= 0x10;
        }
        mSearch.currentWord = reinterpret_cast<wchar_t*>(LatestWord);
        mSearch.wordCharCount = wcslen((wchar_t*)LatestWord);
    }

    if (elementCount == 0 && mSearch.wordCharCount == 0) {
        init();
    }
    else if (elementCount == 1 &&
             (0xeff1 <= ElementBuffer[0] && ElementBuffer[0] <= 0xeff9) &&
             mpHoldingKey != NULL && getPredictLanguage() != 0x12) {
        CandidatedWord[0] = 0x3e;
        CandidatedWord[1] = 0;
        mCandidateCount = 1;
        u16* output = CandidatedWord + 0x40;
        for (s32 keyIndex = 1; keyIndex < 16; ++keyIndex) {
            u16 candidate = static_cast<keyboard::cellphonetype::PaneNameToCharCode*>(mpHoldingKey)->wc[keyIndex - 1];
            if (candidate != 0) {
                output[0] = candidate;
                output[1] = 0;
                ++mCandidateCount;
            }
            output += 0x40;
        }
        EZTXGetCandidates(&mSearch, mpDictionaryWork);
    }
    else {
        memcpy(&CandidatesBuffer[0x200], CandidatesBuffer, 0x200);
        ChangeDictionaryLanguage(getPredictLanguage());
        u32 count = EZTXGetCandidates(&mSearch, mpDictionaryWork) & 0xff;
        if (getPredictLanguage() == 1 && count == 0x61) {
            mSearch.firstCandidate = 0x61;
            mSearch.candidates = reinterpret_cast<wchar_t*>(&CandidatesBuffer[0x2c2]);
            mSearch.maxCandidates = 199;
            count = EZTXGetCandidates(&mSearch, mpDictionaryWork) & 0xff;
            mSearch.firstCandidate = 0;
            count += 0x61;
            mSearch.candidates = candidateOutput;
        }
        if (static_cast<s32>(count) > 0x28) {
            count = 0x28;
        }
        if (getPredictLanguage() == 1 && mbContextChanged != 0 &&
            (mbContextChanged = 0, mSearch.wordCharCount == 0)) {
            u32 length = mCurrentWordLength;
            u32 wordLength = wcslen((wchar_t*)LatestWord) & 0xff;
            u32 copied;
            u16* source = LatestWord + wordLength - length;
            for (copied = 0; copied < length; ++copied) {
                LatestWord[copied] = source[copied];
            }
            LatestWord[copied] = 0;
            mSearch.wordCharCount = wcslen((wchar_t*)LatestWord);
            count = EZTXGetCandidates(&mSearch, mpDictionaryWork) & 0xff;
        }
        if (count == 0) {
            if (getPredictLanguage() != 1) {
                if (getPredictLanguage() == 0x12) {
                    backSpace();
                    return;
                }
                count = complementsCandidates_(elementCount);
            }
            if (count == 0) return;
        }
        memset(CandidatedWord, 0, 0x1400);
        mCandidateCount = 0;
        if (elementCount != 0 || mSearch.wordCharCount != 0) {
            u16* source = reinterpret_cast<u16*>(mSearch.candidates);
            u16* destination = CandidatedWord;
            for (s32 index = 0; index < static_cast<s32>(count); index++) {
                if (getPredictLanguage() == 1) {
                    s32 length = 0;
                    u16* output = destination;
                    for (; *source != 0x20 && *source != 0; source++) {
                        *output++ = *source;
                        ++length;
                    }
                    ++source;
                    destination[length] = 0;
                } else if (mPredictLanguage == PL_11) {
                    *destination = *source++;
                    destination[1] = 0;
                } else if (getPredictLanguage() == 0x12) {
                    u16* output = destination;
                    while (*source >= 0x100) {
                        *output++ = *source++;
                    }
                } else if (EZTXCopy(reinterpret_cast<wchar_t*>(destination), &mSearch, index & 0xff, mpDictionaryWork) == 0) {
                    goto nextCandidate;
                }
                ++mCandidateCount;
                {
                    s32 position = 0;
                    for (u16* candidate = destination; *candidate != 0; ++candidate) {
                        switch (mLetterMode) {
                        case LM_1:
                            *candidate = util::toWLower(*candidate);
                            break;
                        case LM_2:
                            *candidate = util::toWUpper(*candidate);
                            break;
                        case LM_0:
                            if (position == 0) *candidate = util::toWUpper(*candidate);
                            else *candidate = util::toWLower(*candidate);
                            break;
                        default:
                            break;
                        }
                        ++position;
                    }
                }
nextCandidate:
                destination += 0x40;
            }
        }
    }
}

u32 WithZi::complementsCandidates_(s32) {
    bool useSentinel;
    u16 value;
    u16* scan = ElementBuffer;
    goto scanCheck;
scanBody:
    if (0xeff1 <= value && value <= 0xeff9) {
        useSentinel = true;
        goto scanDone;
    }
    ++scan;
scanCheck:
    value = *scan;
    if (value != 0) goto scanBody;
    useSentinel = false;
scanDone:
    if (useSentinel) {
        CandidatedWord[mInputLength - 1] = 0xfffe;
        CandidatedWord[mInputLength] = 0;
    }
    else {
        u16* character;
        u16* destination;
        u32 length;
        u16* source;
        length = 0;
        destination = CandidatedWord;
        source = ElementBuffer;
        character = source;
        while (*source != 0) {
            s32 mode = mLetterMode;
            if (mode == 2) goto modeTwo;
            if (mode >= 2) goto modeThree;
            if (mode == 0) goto modeZero;
            if (mode >= 0) goto modeOne;
            goto modeDone;
        modeThree:
            if (mode >= 4) goto modeDone;
            goto modeCopy;
        modeOne:
            *destination = util::toWLower(*character);
            goto modeDone;
        modeTwo:
            *destination = util::toWUpper(*character);
            goto modeDone;
        modeZero:
            if (length == 0) {
                *destination = util::toWUpper(*character);
            }
            else {
                *destination = util::toWLower(*character);
            }
            goto modeDone;
        modeCopy:
            *destination = *character;
        modeDone:
            ++source;
            ++character;
            ++destination;
            ++length;
        }
        CandidatedWord[length] = 0;
    }
    mCandidateCount = 1;
    return 0;
}

u32 WithZi::setElementBuffer() {
    u32 count = 0;
    memset(ElementBuffer, 0, 0x1fe);
    memset(&CandidatesBuffer[0x100], 0, 0x1fe);
    u16* elements = ElementBuffer;
    u16* candidates = CandidatesBuffer;
    u16 inputCharacter;
    while ((inputCharacter = candidates[static_cast<u16>(count)]) != 0 && static_cast<u16>(count) < 0xff) {
        u16 index = count;
        elements[index] = inputCharacter;
        if (getPredictLanguage() == 1) {
            s32 character = elements[index];
            if (0x30 <= character && character <= 0x39) elements[index] = character + 0xf300;
            else if ((0x61 <= character && character <= 0x7a) || (0x41 <= character && character <= 0x5a)) elements[index] += 0xf300;
        }
        ++count;
    }
    return count;
}

bool WithZi::isFix() {
    return mInputLength == 0;
}

u8 WithZi::getPredictLanguage() {
    switch (mPredictLanguage) {
    case 0: return 0x3b;
    case 1: return 0x40;
    case 2: return 0x41;
    case 3: return 0x3a;
    case 4: return 5;
    case 5: return 0x3f;
    case 6: return 0x42;
    case 7: return 0x2f;
    case 8: return 0xd;
    case 9: return 1;
    case 10: return 0x12;
    case 11: return 0x12;
    default: return 0x3b;
    }
}

void WithZi::setCurrentWord(const wchar_t* word) {
    if (word == NULL) {
        LatestWord[0] = 0x20;
        LatestWord[1] = 0;
        return;
    }
    wchar_t* currentWord;
    const wchar_t* source;
    u32 length;
    s32 copied;
    mbContextChanged = 1;
    length = 0;
    currentWord = reinterpret_cast<wchar_t*>(LatestWord);
    for (; *currentWord != 0 && *currentWord != 0x20;
         currentWord++, ++length) {
        if (length == 0x3f) {
            LatestWord[length] = 0;
            return;
        }
    }
    copied = 0;
    source = word;
    for (; *source != 0 && length < 0x3f;) {
        LatestWord[length++] = word[copied++];
        ++source;
    }
    LatestWord[length] = 0;
    mCurrentWordLength = copied;
}

void WithZi::EnableKSXFilter(bool) {}

bool WithZi::canBackSpace() {
    return mInputLength != 0;
}

void WithZi::clear() {}

}
}
