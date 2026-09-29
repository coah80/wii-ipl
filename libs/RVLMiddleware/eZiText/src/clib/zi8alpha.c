#include <zi8clib/zierror.h>
#include <zi8clib/ziswordw.h>
#include <zi8clib/zconvert.h>

typedef struct {
    ziU8 dictionaryState[9];
    ziU8 dictionaryFlags;
    ziU8 dictionarySettings[0x1C - 10];
    ziU8 operation;
    ziU8 context;
    ziU8 caseMode;
    ziU8 normalizeCase;
    ziU8 dictionaryMemory[0x1200 - 0x20];
    ziU8* dictionaries[128];
    ziU8 dictionaryMetadata[12];
    ziU8 exactLengthThreshold;
    ziU8 dictionaryLimits[3];
    ziU8* dictionaryKinds;
    ziU8* dictionaryCounts;
    ziU8 dictionaryCount;
    ziU8 dictionaryModes[3];
    ziU8 dictionaryOrder[2];
    ziU8 candidateState[0x1874 - 0x141E];
    ziWChar letterHyphen;
    ziU8 prefixLength;
    ziU8 prefixEnabled;
    ziU8 requiredLength;
    ziU8 highlightedLanguage;
    ziWChar highlightedWord[65];
    ziU8 suffixMode;
    ziU8 suffixState;
    ziWChar prefix[65];
    ziU8 prefixCount;
    ziU8 previousPrefixCount;
    ziU8 prefixElementCount;
    ziU8 language;
    ziU8 suffixLocked;
    ziU8 previousSuffixCount;
    ziU8 suffixElementCount;
    ziU8 suffixStatus;
    ziWChar suffix[65];
    ziU8 suffixCount;
    ziU8 usePrefixAsElements;
    ziWChar alternatePrefix[65];
    ziU8 alternatePrefixCount;
    ziWChar singleCharacter;
    ziWChar rememberedWord[65];
    ziU8 rememberedCount;
    ziU8 reuseHighlightedWord;
    ziU8 wordState;
} ZiAlphaWork;

typedef struct {
    ziU8 countOnly;
    ziU8 maxWordLength;
    ziU8 lookupMode;
    ziU8 dictionaryMode;
    ziWChar* dictionary;
    ziU32 dictionaryFlags;
    ziU32 maxResults;
    ziU16 capacity;
    ziU8 minWordLength;
    ziU8 candidateMode;
    ziU8 suffixOnly;
    ziU8 shortestWord;
    ziU8 longestWord;
} ZiAlphaOptions;

#undef ZI_NEED_WORK
#define ZI_NEED_WORK , ZiAlphaWork* work

typedef struct {
    ziChar prefix[6];
    ziWChar replacement;
    ziBool changeEnding;
} ZiExclusionPair;

const ZiExclusionPair IT_EXCLUDE_PAIRS[] = {
    {"l", 0x69, 0},
    {"all", 0x69, 0},
    {"dell", 0x69, 0},
    {"dall", 0x69, 0},
    {"nell", 0x69, 0},
    {"sull", 0x69, 0},
    {"d", 0x69, 0},
    {"quest", 0x69, 0},
    {"quell", 0x69, 0},
    {"bell", 0x69, 0},
    {"brav", 0x69, 0},
    {"buon", 0x69, 0},
    {"sant", 0x69, 0},
    {"gl", 0x1, 0},
    {"agl", 0x1, 0},
    {"degl", 0x1, 0},
    {"dagl", 0x1, 0},
    {"negl", 0x1, 0},
    {"sugl", 0x1, 0},
    {"m", 0x1, 0},
    {"t", 0x1, 0},
    {"s", 0x1, 0},
    {"c", 0x1, 0},
    {"v", 0x1, 0},
    {"un", 0x61, 1},
    {"", 0x0, 0},
};

const ZiExclusionPair FrenchExcludePairs[] = {
    {"d", 0x1, 0},
    {"l", 0x1, 0},
    {"m", 0x1, 0},
    {"t", 0x1, 0},
    {"s", 0x1, 0},
    {"n", 0x1, 0},
    {"", 0x0, 0},
};

ziBool Zi8ChangeCharCase(ziU8 upper, ziWChar* character, ziU8 language, ziPtr data);

ziBool Zi8SetParentalControls(ziU8 level ZI_NEED_WORK) {
    Zi8LogError(0x2C9, work);
    return ZI8_FALSE;
}

ziBool Zi8IsWordW2(ziWChar* word, ziU8 language ZI_NEED_WORK) {
    ziU8 savedLanguage = work->language;
    ziBool result = Zi8IsWordW(word, language, work);
    work->language = savedLanguage;
    return result;
}

ziBool Zi8SetHighlightedWordW(ziWChar* word, ziU8 language, ziU8 subLanguage ZI_NEED_WORK) {
    int length = 0;
    int index;
    while (word[length] != 0) ++length;
    if (length >= 64) {
        Zi8LogError(0x131, work);
        return ZI8_FALSE;
    }
    if (length == 1 && word[0] >= 0xEFF1 && word[0] <= 0xF010) {
        Zi8LogError(0x640, work);
        return ZI8_FALSE;
    }
    work->highlightedLanguage = 1;
    if (!work->suffixMode || !work->suffixLocked) {
        work->operation = 1;
        if (!work->suffixMode) {
            if (!work->requiredLength || length == work->requiredLength) {
                work->operation = 2;
                if (Zi8IsWordW2(word, language, work)) {
                    work->highlightedLanguage = language;
                } else if (subLanguage != language && subLanguage != 7 && Zi8IsWordW2(word, subLanguage, work)) {
                    work->highlightedLanguage = subLanguage;
                }
            }
        } else {
            for (index = 0; index < work->prefixCount; ++index) {
                if (work->prefix[index] != word[index]) break;
            }
            if ((!work->requiredLength || length == work->requiredLength) && index == work->prefixCount && Zi8IsWordW2(word + index, work->language, work)) {
                work->highlightedLanguage = work->language;
            }
        }
        work->operation = 0;
    }
    for (index = 0; index <= length; ++index) work->highlightedWord[index] = word[index];
    Zi8LogError(0x64, work);
    return ZI8_TRUE;
}

static void ZiprocessHighlightedW(ziU8 elementCount ZI_NEED_WORK) {
    int length = 0;
    int suffixIndex;
    int index;
    while (work->highlightedWord[length] != 0) ++length;
    if (length + 1 == elementCount) {
        if (length == work->requiredLength && work->prefixEnabled) {
            work->prefixLength = length;
            for (index = 0; index < (int)length; ++index) work->prefix[index] = work->highlightedWord[index];
        }
        if (!work->suffixMode) {
            if ((!work->requiredLength || length == work->requiredLength) && work->highlightedLanguage > 1) {
                for (index = 0; index < (int)length; ++index) work->prefix[index] = work->highlightedWord[index];
                work->prefixCount = index;
                work->language = work->highlightedLanguage;
            }
        } else if (!work->suffixLocked && work->highlightedLanguage > 1) {
            index = 0;
            for (suffixIndex = work->prefixCount; suffixIndex < length;) work->suffix[index++] = work->highlightedWord[suffixIndex++];
            work->suffixCount = index;
        }
        if (length == 1 && work->singleCharacter != 0) {
            if (work->highlightedWord[0] >= 0xEFF1 && work->highlightedWord[0] <= 0xF010) work->singleCharacter = 0;
            else work->singleCharacter = work->highlightedWord[0];
        }
        if (length == work->rememberedCount && Zi8ConvertWC2Key(work->highlightedWord[length - 1], work->language, work) != 0xEFF1) {
            for (index = 0; index <= (int)length; ++index) work->rememberedWord[index] = work->highlightedWord[index];
            work->rememberedWord[index] = 0;
        }
        work->highlightedLanguage = 0;
    }
}

ziBool Zi8IsVowel(ziU8 language, ziWChar character) {
    switch (language) {
    case 4:
    case 47:
    case 63:
    case 64:
        break;
    case 88:
        switch (character) {
        case 'a': case 'e': case 'h': case 'i': case 'o': case 'u':
        case 0xE0: case 0xE8: case 0xE9: case 0xED: case 0xEF:
        case 0xF2: case 0xF3: case 0xFA: case 0xFC:
            goto vowel;
        default:
            return ZI8_FALSE;
        }
    default:
        goto vowel;
    }
    switch (character & 0xFFDF) {
    case 'A': case 'E': case 'H': case 'I': case 'O': case 'U':
    case 0xC0: case 0xC8: case 0xC9: case 0xCC: case 0xD2: case 0xD9:
        goto vowel;
    case 'Y': case 0xC2: case 0xC6: case 0xCA: case 0xCB:
    case 0xCE: case 0xCF: case 0xD4: case 0xDB:
        if (language != 47) goto vowel;
        return ZI8_FALSE;
    }
    if (language == 47) return ZI8_FALSE;
    switch (character) {
    case 0xFF: case 0x152: case 0x153: case 0x178:
        goto vowel;
    default:
        return ZI8_FALSE;
    }
vowel:
    return ZI8_TRUE;
}

ziBool Zi8ITspecialExclusion(ziWChar* ending, ziS32 length, ziU32 candidateLength) {
    ziPtr beginning;
    const ZiExclusionPair* pair;
    int index;
    beginning = ending - length--;
    pair = IT_EXCLUDE_PAIRS;
    for (; pair->replacement != 0; ++pair) {
        for (index = 0; index < length; ++index) {
            if (((ziWChar*)beginning)[index] != pair->prefix[index]) break;
        }
        if (index >= length && pair->prefix[index] == 0) {
            if (!Zi8IsVowel(47, *ending)) return ZI8_TRUE;
            else return ZI8_FALSE;
        }
    }
    return ZI8_FALSE;
}

ziBool Zi8_814659E8(ziWChar* ending, ziS32 length, ziU32 candidateLength) {
    ziPtr beginning;
    const ZiExclusionPair* pair;
    int index;
    beginning = ending - length--;
    pair = FrenchExcludePairs;
    for (; pair->replacement != 0; ++pair) {
        for (index = 0; index < length; ++index) {
            if (((ziWChar*)beginning)[index] != pair->prefix[index]) break;
        }
        if (index >= length && pair->prefix[index] == 0) {
            if (!Zi8IsVowel(88, *ending)) return ZI8_TRUE;
            else return ZI8_FALSE;
        }
    }
    return ZI8_FALSE;
}

ziBool Zi8IsAlphaPunct(ziWChar character) {
    if (character == 0xEFF1 || (character >= 0x21 && character <= 0x40) || (character >= 0x5B && character <= 0x60) || (character >= 0x7B && character <= 0x7E)) return ZI8_TRUE;
    else return ZI8_FALSE;
}

static ziBool ZiIsLetterHyphen(ziWChar character ZI_NEED_WORK) {
    if (character == work->letterHyphen || character == '-' || character == '.' || character == '@') return ZI8_TRUE;
    else return ZI8_FALSE;
}

void Zi8ChangeWordCase(ziWChar* word, ziU8 language, ziPtr work) {
    enum { LOWER_CASE, UPPER_CASE } upper = LOWER_CASE;
    if (((ZiAlphaWork*)work)->caseMode == 3) {
        Zi8ChangeCharCase(1, word++, language, work);
    } else if (((ZiAlphaWork*)work)->caseMode == 1) {
        upper = UPPER_CASE;
    }
    while (*word != 0) Zi8ChangeCharCase(upper, word++, language, work);
}

ziU32 Zi8DeTokenization(ziWChar* word, ziU32 length, ziU16 capacity, ziU16 language);
ziU32 Zi8GetTableAddress(ziU8 language, ziU8 table, ziPtr work);
ziU32 Zi8GetTableCount(ziU8 language, ziU8 table, ziPtr work);
void Zi8InitDupWordBuf(ziPtr work);
ziBool Zi8IsDupWordW(ziWChar* word, ziU8 length, ziPtr work);
ziBool Zi8IsZicorpSignature(ziWChar* word, ziU8 length, ziPtr work);
ziU8 Zi8LangSupported(ziU8 language, ziPtr work);
ziU8 Zi8MatchOEMdata(ziWChar* elements, ziU8 count, ziU8 language, ziWChar* word, ziU16 capacity, ziU8 mode, ziU8 status, ziPtr work);
ziU8 Zi8MatchPUDdata(ziWChar* elements, ziU8 count, ziU8 language, ziWChar* word, ziU16 capacity, ziU8 mode, ziU8 status, ziPtr work);
ziU8 Zi8MatchROMdata(ziWChar* elements, ziU8 count, ziU8 language, ziWChar* word, ziU16 capacity, ziU8 mode, ziU8 status, ziBool reservedMode, ziBool exactLength, ziPtr work);
ziU8 Zi8MatchUWDdata(ziWChar* elements, ziU8 count, ziWChar* currentWord, ziU8 currentLength, ziU8 language, ziWChar* word, ziU16 capacity, ziU8 mode, ziU8 status, ziPtr work);
void Zi8Memset(ziPtr destination, ziU8 value, ziU32 count);
ziU16 Zi8WCharCount(ziWChar* word, ziPtr work);
ziBool Zi8ZHCheckSpelling(ziWChar* word, ziWChar* elements, ziU8 count, ziPtr work);
ziU8 Zi8getKeyLayout(ziU8 language, ziWChar key, ziWChar* characters, ziU8 capacity, ziPtr work);

ziU8 Zi8AlphaGetCandidates(ziGetParam* parameters, ziPtr optionData, ziPtr workData)

{
  int contextEnabled;
  ziU8 characterCount;
  int primaryCompletionAllowed;
  int secondaryCompletionAllowed;
  ziU8 prefixCharacterCount;
  int phoneticInput;
  int phoneticSeparator;
  int vowelRestriction;
  int completionAllowed;
  int secondLanguagePass;
  int punctuationCandidate;
  ziBool retryPunctuation;
  int switchedLanguage;
  int secondaryVowelRestriction;
  ziBool prefixActive;
  ziU16 primaryMatched;
  ziU16 secondaryMatched;
  unsigned int primaryTableFlags;
  ziBool matched;
  unsigned int candidateLength;
  ziU16 character;
  ziS16 key;
  ziU8 encodedCharacter;
  ziU8 outputCharacter;
  ziU16 convertedCharacter;
  int index;
  ziChar* encodedWord;
  ziU8 *encodedCursor;
  ziU16 *wordCursor;
  unsigned int characterIndex;
  ziU8 keyLayoutCount;
  ziU8 outputLanguage;
  ziU8 language;
  ziU8 *keyLayoutCursor;
  ziU8 *keyLayout;
  int candidateCount;
  unsigned int elementCount;
  unsigned int firstCandidate;
  ziU16 *elements;
  ziU16 *punctuationCursor;
  unsigned int wordLength;
  int remainingCapacity;
  unsigned int wordCapacity;
  int exactLengthOnly;
  int dictionaryExact;
  int matchMode;
  unsigned int elementIndex;
  unsigned int dictionaryKind;
  unsigned int dictionaryIndex = 0;
  ziU8 *encodedOutput;
  unsigned int countIndex;
  int alternateSingleCharacter;
  int languagePassCount;
  int apostropheIndex;
  unsigned int prefixCount;
  ziU8 candidateBytes [64];
  unsigned int dictionaryStatus [14];
  ziU16 normalizedElements [64];
  ziWChar punctuationBuffer[48];
  ziU16 candidateWord [64];

  retryPunctuation = ZI8_FALSE;
  primaryMatched = ZI8_FALSE;
  secondaryMatched = ZI8_FALSE;
  prefixActive = ZI8_FALSE;
  prefixCount = 0;
  secondaryVowelRestriction = ZI8_TRUE;
  vowelRestriction = ZI8_FALSE;
  languagePassCount = 2;
  secondLanguagePass = ZI8_FALSE;
  alternateSingleCharacter = 0;
  switchedLanguage = ZI8_FALSE;
  elements = parameters->elements;
  firstCandidate = (unsigned int)parameters->firstCandidate;
  characterCount = parameters->elementCount;
  elementCount = (unsigned int)characterCount;
  punctuationCandidate = ZI8_FALSE;
  dictionaryStatus[0] = 0;
  dictionaryStatus[1] = 0;
  dictionaryStatus[2] = 0;
  dictionaryStatus[3] = 0;
  dictionaryStatus[4] = 0;
  dictionaryStatus[5] = 0;
  dictionaryStatus[6] = 0;
  dictionaryStatus[7] = 0;
  dictionaryStatus[8] = 0;
  dictionaryStatus[9] = 0;
  dictionaryStatus[10] = 0;
  dictionaryStatus[0xb] = 0;
  dictionaryStatus[0xc] = 0;
  dictionaryStatus[0xd] = 0;
  candidateCount = 0;
  language = parameters->language;
  outputLanguage = 0;
  keyLayout = (ziU8 *)0x0;
  phoneticInput = ZI8_FALSE;
  phoneticSeparator = ZI8_FALSE;
  if ((((((language == 0x7c) || (language == 0x7d)) || (language == 0x7b)) ||
       ((language == 0x77 || (language == 0x78)))) || (language == 0x79)) ||
     (language == 0x7a)) {
    phoneticInput = ZI8_TRUE;
    for (elementIndex = 0; (int)elementIndex < (int)elementCount; elementIndex = elementIndex + 1) {
      normalizedElements[elementIndex] = elements[elementIndex];
      if ((elements[elementIndex] < 0xf336) && (0xf330 < elements[elementIndex])) {
        phoneticSeparator = ZI8_TRUE;
        phoneticInput = ZI8_FALSE;
        if ((language == 0x7d) || ((language == 0x79 || (language == 0x7a)))) {
          normalizedElements[elementIndex] = 0xf360;
        }
        else {
          normalizedElements[elementIndex] = 0x27;
        }
      }
    }
    elements = normalizedElements;
  }
  contextEnabled = ((ZiAlphaWork*)workData)->context != '\0';
  if ((((parameters->elementCount != 0) && (((ZiAlphaWork*)workData)->normalizeCase != '\0')) && (!phoneticInput)) && (!phoneticSeparator)) {
    primaryCompletionAllowed = ZI8_FALSE;
    for (elementIndex = 0; (int)elementIndex < (int)(unsigned int)parameters->elementCount; elementIndex = elementIndex + 1) {
      normalizedElements[elementIndex] = parameters->elements[elementIndex];
      if (((parameters->elements[elementIndex] < 0xeff1) ||
          (0xf37f < parameters->elements[elementIndex])) &&
         (matched = Zi8ChangeCharCase(0,normalizedElements + elementIndex,language,workData), matched != '\0'))
      {
        primaryCompletionAllowed = ZI8_TRUE;
      }
    }
    if (primaryCompletionAllowed) {
      elements = normalizedElements;
    }
  }
  if (((((ZiAlphaWork*)workData)->highlightedLanguage != '\0') && (parameters->firstCandidate == 0)) &&
     (((ZiAlphaOptions*)optionData)->lookupMode == '\0')) {
    ZiprocessHighlightedW(parameters->elementCount,workData);
  }
  if (((((ZiAlphaOptions*)optionData)->lookupMode == '\0') && (parameters->elementCount < 2)) && (parameters->firstCandidate == 0)) {
    ((ZiAlphaWork*)workData)->highlightedWord[0] = 0;
  }
  primaryTableFlags = Zi8GetTableCount(parameters->language,0x1f,workData);
  if (((primaryTableFlags & 0x80) != 0) && (parameters->subLanguage == 0x80)) {
    contextEnabled = ZI8_TRUE;
  }
  if (((((ZiAlphaOptions*)optionData)->lookupMode == '\0') && (parameters->subLanguage != 7)) &&
     ((parameters->subLanguage != language &&
      ((((parameters->subLanguage != 0 && (parameters->subLanguage != 1)) && (parameters->subLanguage != 2)) &&
       ((parameters->subLanguage != 0x80 && (matched = Zi8LangSupported(parameters->subLanguage,workData), matched != '\0'))))))))
  {
    if (((parameters->elementCount == 1) && (0xeff0 < *parameters->elements)) &&
       (*parameters->elements < 0xf011)) {
      contextEnabled = ZI8_FALSE;
      matched = Zi8MatchROMdata(parameters->elements,1,language,candidateWord,2,1,0,0,0,
                               workData);
      if (matched == '\0') {
        language = parameters->subLanguage;
      }
      else {
        matched = Zi8MatchROMdata(parameters->elements,1,parameters->subLanguage,candidateWord,2,1,0,0,0,
                                 workData);
        if ((matched != '\0') && (candidateWord[0] != *parameters->elements)) {
          alternateSingleCharacter = 1;
        }
      }
    }
  }
  else {
    languagePassCount = 0;
    if (((ZiAlphaWork*)workData)->language != parameters->language) {
      ((ZiAlphaWork*)workData)->language = 0;
    }
  }
  if ((parameters->elementCount == 1) && (((ZiAlphaOptions*)optionData)->lookupMode == '\0')) {
    if (((parameters->wordCharCount < 3) ||
        (((parameters->currentWord == 0 ||
          (parameters->currentWord[parameters->wordCharCount - 1] != 0x77)) ||
         (parameters->currentWord[parameters->wordCharCount - 2] != 0x77)))) ||
       (parameters->currentWord[parameters->wordCharCount - 3] != 0x77)) {
      ((ZiAlphaWork*)workData)->letterHyphen = 0x2d;
    }
    else {
      ((ZiAlphaWork*)workData)->letterHyphen = 0x2e;
    }
  }
  if (((elementCount != 0) && (((ZiAlphaOptions*)optionData)->lookupMode == '\0')) && (((ZiAlphaOptions*)optionData)->countOnly == '\0')) {
    matched = Zi8IsAlphaPunct(elements[elementCount - 1]);
    if (matched == '\0') {
      ((ZiAlphaWork*)workData)->rememberedCount = characterCount;
    }
    else if (elementCount < ((ZiAlphaWork*)workData)->rememberedCount) {
      ((ZiAlphaWork*)workData)->rememberedCount = characterCount - 1;
    }
  }
  if ((((ZiAlphaWork*)workData)->usePrefixAsElements == '\x01') &&
     (elements = ((ZiAlphaWork*)workData)->prefix, ((ZiAlphaWork*)workData)->prefixCount < parameters->elementCount)) {
    for (primaryTableFlags = (unsigned int)((ZiAlphaWork*)workData)->prefixCount; (int)primaryTableFlags < (int)(unsigned int)parameters->elementCount;
        primaryTableFlags = primaryTableFlags + 1) {
      ((ZiAlphaWork*)workData)->prefix[primaryTableFlags] =
           parameters->elements[primaryTableFlags];
    }
    ((ZiAlphaWork*)workData)->prefix[primaryTableFlags] = 0;
    ((ZiAlphaWork*)workData)->prefixCount = (char)primaryTableFlags;
    elementCount = (unsigned int)((ZiAlphaWork*)workData)->prefixCount;
  }
  primaryTableFlags = Zi8GetTableCount(parameters->language,0x1f,workData);
  primaryCompletionAllowed = (primaryTableFlags & 4) == 0;
  primaryTableFlags = Zi8GetTableCount(parameters->language,0x1f,workData);
  encodedOutput = (ziChar*)parameters->candidates;
  if ((((ZiAlphaOptions*)optionData)->countOnly == '\0') && ((parameters->getOptions & 0xfd) == 0x81)) {
    wordCursor = parameters->candidates;
    wordCapacity = ((ZiAlphaOptions*)optionData)->capacity - 1;
  }
  else {
    wordCursor = candidateWord;
    wordCapacity = 0x3f;
  }
  remainingCapacity = ((ZiAlphaOptions*)optionData)->capacity - 1;
  if ((elementCount < ((ZiAlphaWork*)workData)->exactLengthThreshold) || ((parameters->getOptions & 0x7e) == 2)) {
    exactLengthOnly = 1;
  }
  else {
    exactLengthOnly = 0;
  }
  if (phoneticSeparator) {
    exactLengthOnly = 1;
  }
  if (languagePassCount == 0) {
    secondaryCompletionAllowed = ZI8_FALSE;
    secondaryVowelRestriction = ZI8_FALSE;
  }
  else {
    candidateLength = Zi8GetTableCount(parameters->subLanguage,0x1f,workData);
    secondaryCompletionAllowed = (candidateLength & 4) == 0;
    candidateLength = Zi8GetTableCount(parameters->subLanguage,0x1f,workData);
    if ((candidateLength & 2) != 0) {
      secondaryVowelRestriction = ZI8_FALSE;
    }
  }
  Zi8InitDupWordBuf(workData);
  if ((((((ZiAlphaOptions*)optionData)->lookupMode == '\0') && (!phoneticInput)) && (!phoneticSeparator)) &&
     ((((parameters->getOptions & 0xfd) != 0x80 && (parameters->elementCount != 0)) &&
      ((parameters->elements[parameters->elementCount - 1] != 0xEFF1 &&
       (matched = Zi8IsAlphaPunct(parameters->elements[parameters->elementCount - 1]),
       matched != '\0')))))) {
    for (elementIndex = 0;
        ((int)elementIndex < (int)(parameters->elementCount - 1) &&
        (((ZiAlphaWork*)workData)->highlightedWord[elementIndex] ==
         parameters->elements[elementIndex])); elementIndex = elementIndex + 1) {
      wordCursor[elementIndex] = ((ZiAlphaWork*)workData)->highlightedWord[elementIndex];
    }
    wordCursor[elementIndex] = parameters->elements[elementIndex];
    candidateLength = elementIndex + 1;
    if (parameters->elementCount == 1) {
      ((ZiAlphaWork*)workData)->singleCharacter = *wordCursor;
    }
    if ((candidateLength == parameters->elementCount) && ((firstCandidate == 0 || (((ZiAlphaWork*)workData)->reuseHighlightedWord != '\0')))) {
      for (index = 0; index < (int)(unsigned int)((ZiAlphaWork*)workData)->dictionaryCount; index = index + 1) {
        characterCount = ((ZiAlphaWork*)workData)->dictionaryKinds[index];
        if ((characterCount == 9) || ((characterCount < 9 && (characterCount == 1)))) break;
      }
      if ((firstCandidate == 0) && (((ZiAlphaWork*)workData)->highlightedWord[elementIndex] != 0)) {
        if (((ZiAlphaWork*)workData)->requiredLength < parameters->elementCount) {
          ((ZiAlphaWork*)workData)->reuseHighlightedWord = 0;
        }
      }
      else {
        ((ZiAlphaWork*)workData)->reuseHighlightedWord = 1;
      }
      if (((index < (int)(unsigned int)((ZiAlphaWork*)workData)->dictionaryCount) &&
          (((ZiAlphaWork*)workData)->reuseHighlightedWord != '\0')) &&
         (matched = Zi8IsDupWordW(wordCursor,candidateLength & 0xff,workData), matched == '\0')) {
        if (firstCandidate == 0) {
          candidateCount = 1;
          if (((ZiAlphaOptions*)optionData)->countOnly == '\0') {
            elementIndex = candidateLength;
            if (((ZiAlphaOptions*)optionData)->suffixOnly != '\0') {
              for (elementIndex = 0; (int)(parameters->elementCount + elementIndex) < (int)candidateLength;
                  elementIndex = elementIndex + 1) {
                wordCursor[elementIndex] = wordCursor[elementIndex + parameters->elementCount];
              }
            }
            wordCursor[elementIndex] = 0;
            index = elementIndex + 1;
            if (((ZiAlphaWork*)workData)->caseMode != '\0') {
              if (((ZiAlphaWork*)workData)->suffixMode == '\0') {
                Zi8ChangeWordCase(wordCursor,language,workData);
              }
              else {
                Zi8ChangeWordCase(wordCursor,((ZiAlphaWork*)workData)->language,workData);
              }
            }
            wordCursor = wordCursor + index;
            wordCapacity = wordCapacity - index;
            remainingCapacity = remainingCapacity - index;
            if ((parameters->maxCandidates == 1) || (remainingCapacity <= (int)(unsigned int)parameters->elementCount)) {
finishCandidates:
              ((ZiAlphaWork*)workData)->usePrefixAsElements = 0;
              characterCount = (ziU8)candidateCount;
              if (((ZiAlphaOptions*)optionData)->countOnly == '\0') {
                parameters->letters = characterCount;
              }
              else {
                parameters->letters = 0;
              }
              wordCursor[-prefixCount] = 0;
              if (((((ZiAlphaOptions*)optionData)->countOnly == '\0') && (((ZiAlphaOptions*)optionData)->lookupMode == '\0')) && (parameters->elementCount != 0)) {
                elementIndex = parameters->elementCount - 1;
                if (((primaryCompletionAllowed) || (secondaryCompletionAllowed)) &&
                   ((((ZiAlphaWork*)workData)->prefixEnabled < 2 ||
                    (parameters->elements[elementIndex] == 0xEFF1)))) {
                  index = 0;
                  for (; (-1 < (int)elementIndex &&
                         (parameters->elements[elementIndex] == 0xEFF1));
                      elementIndex = elementIndex + -1) {
                    index = index + 1;
                  }
                  if (index == 0) {
                    if (candidateCount != 0) {
                      ((ZiAlphaWork*)workData)->prefixEnabled = 0;
                      ((ZiAlphaWork*)workData)->requiredLength = 0;
                    }
                  }
                  else {
                    ((ZiAlphaWork*)workData)->prefixEnabled = (char)index;
                  }
                  ((ZiAlphaWork*)workData)->requiredLength = parameters->elementCount;
                }
                if ((parameters->letters != 0) && (parameters->maxCandidates == 1)) {
                  if ((parameters->getOptions & 0x81) == 0x81) {
                    wordCursor = parameters->candidates;
                  }
                  else if (outputLanguage == 0) {
                    wordCursor = (ziU16 *)0x0;
                  }
                  else {
                    encodedWord = (ziChar*)parameters->candidates;
                    wordCursor = candidateWord;
                    for (characterIndex = 0; encodedWord[characterIndex] != '\0'; characterIndex = characterIndex + 1) {
                      convertedCharacter = Zi8ConvertUC2WC(encodedWord[characterIndex],outputLanguage,
                                               workData);
                      wordCursor[characterIndex] = convertedCharacter;
                    }
                    wordCursor[characterIndex] = 0;
                  }
                  if (wordCursor != (ziU16 *)0x0) {
                    Zi8SetHighlightedWordW(wordCursor,parameters->language,parameters->subLanguage,workData);
                  }
                }
              }
              if (((ZiAlphaWork*)workData)->dictionaryCounts != 0) {
                if ((int)dictionaryIndex < (int)(unsigned int)((ZiAlphaWork*)workData)->dictionaryCount) {
                  ((ZiAlphaWork*)workData)->dictionaryCounts[dictionaryIndex] = characterCount;
                }
                else {
                  ((ZiAlphaWork*)workData)->dictionaryCounts[((ZiAlphaWork*)workData)->dictionaryCount - 1] =
                       characterCount;
                }
                countIndex = dictionaryIndex;
                if ((int)(unsigned int)((ZiAlphaWork*)workData)->dictionaryCount <= (int)dictionaryIndex) {
                  countIndex = ((ZiAlphaWork*)workData)->dictionaryCount - 1;
                }
                for (; 0 < (int)countIndex; countIndex = countIndex - 1) {
                  ((ZiAlphaWork*)workData)->dictionaryCounts[countIndex] =
                       ((ZiAlphaWork*)workData)->dictionaryCounts[countIndex] -
                       ((ZiAlphaWork*)workData)->dictionaryCounts[countIndex - 1];
                }
              }
              Zi8LogError(100,workData);
              return candidateCount;
            }
          }
        }
        else {
          firstCandidate = firstCandidate - 1;
        }
      }
    }
  }
  completionAllowed = primaryCompletionAllowed;
  if (((ZiAlphaOptions*)optionData)->lookupMode == '\0') {
    if ((parameters->elementCount < 2) && (parameters->firstCandidate == 0)) {
      ((ZiAlphaWork*)workData)->prefixEnabled = 0;
      ((ZiAlphaWork*)workData)->requiredLength = 0;
      ((ZiAlphaWork*)workData)->previousPrefixCount = 0;
      ((ZiAlphaWork*)workData)->prefixCount = 0;
      ((ZiAlphaWork*)workData)->suffixMode = 0;
      ((ZiAlphaWork*)workData)->suffixLocked = 0;
      ((ZiAlphaWork*)workData)->suffixElementCount = 0;
      ((ZiAlphaWork*)workData)->previousSuffixCount = 0;
      ((ZiAlphaWork*)workData)->usePrefixAsElements = 0;
      ((ZiAlphaWork*)workData)->rememberedCount = 0;
      ((ZiAlphaWork*)workData)->suffixCount = 0;
    }
    if (((((ZiAlphaWork*)workData)->suffixLocked != '\0') && (parameters->elementCount <= ((ZiAlphaWork*)workData)->suffixElementCount)) &&
       (matched = ZiIsLetterHyphen(((ZiAlphaWork*)workData)->suffix[(((ZiAlphaWork*)workData)->suffixCount - 1)],
                                  workData), matched != '\0')) {
      ((ZiAlphaWork*)workData)->suffixCount = ((ZiAlphaWork*)workData)->suffixCount + -1;
      ((ZiAlphaWork*)workData)->suffixElementCount = ((ZiAlphaWork*)workData)->previousSuffixCount;
    }
    if (parameters->elementCount <= ((ZiAlphaWork*)workData)->suffixElementCount) {
      ((ZiAlphaWork*)workData)->suffixLocked = 0;
    }
    if (((ZiAlphaWork*)workData)->suffixMode != '\0') {
      if ((parameters->elementCount <= ((ZiAlphaWork*)workData)->prefixElementCount) &&
         (matched = ZiIsLetterHyphen(((ZiAlphaWork*)workData)->prefix[((ZiAlphaWork*)workData)->prefixCount - 1],
                                    workData), matched != '\0')) {
        ((ZiAlphaWork*)workData)->prefixCount = ((ZiAlphaWork*)workData)->prefixCount + -1;
        ((ZiAlphaWork*)workData)->prefixElementCount = ((ZiAlphaWork*)workData)->previousPrefixCount;
      }
      if ((elementCount == ((ZiAlphaWork*)workData)->prefixCount) &&
         (matched = ZiIsLetterHyphen(((ZiAlphaWork*)workData)->prefix[((ZiAlphaWork*)workData)->prefixCount - 1],
                                    workData), matched != '\0')) {
        ((ZiAlphaWork*)workData)->prefixCount = ((ZiAlphaWork*)workData)->prefixCount + -1;
      }
      if ((elementCount <= ((ZiAlphaWork*)workData)->prefixCount) && (((ZiAlphaOptions*)optionData)->countOnly == '\0')) {
        ((ZiAlphaWork*)workData)->suffixMode = 0;
        ((ZiAlphaWork*)workData)->prefixCount = 0;
      }
    }
    if ((((ZiAlphaWork*)workData)->suffixMode != '\0') && (parameters->elementCount < ((ZiAlphaWork*)workData)->alternatePrefixCount)) {
      ((ZiAlphaWork*)workData)->alternatePrefixCount = 0;
    }
  }
prepareDictionaryOrder:
  ((ZiAlphaWork*)workData)->dictionaryOrder[0] = 0;
  candidateLength = Zi8GetTableCount(language,0x1f,workData);
  if ((candidateLength & 0x20) == 0) {
    ((ZiAlphaWork*)workData)->dictionaryOrder[1] = 0;
  }
  else if ((((parameters->currentWord == 0) || (parameters->wordCharCount == 0)) ||
           (parameters->currentWord[parameters->wordCharCount - 1] == 0x20)) ||
          ((0xfe < parameters->currentWord[parameters->wordCharCount - 1] ||
           (key = Zi8ConvertWC2Key(parameters->currentWord[parameters->wordCharCount - 1],
                                     language,workData), (ziWChar)key == 0xEFF1)))) {
    ((ZiAlphaWork*)workData)->dictionaryOrder[1] = 1;
  }
  else {
    ((ZiAlphaWork*)workData)->dictionaryOrder[1] = 0;
    if ((language == 10) && (parameters->wordCharCount != 0)) {
      elementIndex = (unsigned int)parameters->wordCharCount;
scanFinnishWord:
      while (elementIndex = elementIndex - 1, -1 < (int)elementIndex) {
        character = parameters->currentWord[elementIndex];
        if (character == 0x6f) goto useFinnishVowelOrder;
        if (0x6e < character) goto checkFinnishVowel;
        if (character == 0x61) goto useFinnishVowelOrder;
        if ((character < 0x61) && (character == 0x20)) goto finishFinnishScan;
      }
    }
  }
  goto prepareDictionaries;
checkFinnishVowel:
  if (character == 0x75) {
useFinnishVowelOrder:
    ((ZiAlphaWork*)workData)->dictionaryOrder[0] = 1;
finishFinnishScan:
    elementIndex = 0;
  }
  goto scanFinnishWord;
prepareDictionaries:
  apostropheIndex = 0;
  candidateLength = Zi8GetTableCount(language,0x1f,workData);
  if (((candidateLength & 0x10) != 0) && (2 < parameters->elementCount)) {
    for (index = 0;
        (index < (int)(unsigned int)parameters->elementCount &&
        (parameters->elements[index] < 0xeff1)); index = index + 1) {
      if ((apostropheIndex == 0) && (parameters->elements[index] == 0x27)) {
        apostropheIndex = index;
      }
    }
    if ((int)(unsigned int)parameters->elementCount <= apostropheIndex + 1) {
      apostropheIndex = 0;
    }
    if (apostropheIndex != 0) {
      apostropheIndex = apostropheIndex + 1;
    }
  }
  if ((((completionAllowed) && (languagePassCount != 2)) && (parameters->elementCount == 2)) &&
     ((parameters->elements[1] == 0xEFF1 && (((ZiAlphaWork*)workData)->singleCharacter != 0)))) {
    matched = Zi8getKeyLayout(language,0xeff1,&punctuationBuffer[0],1,workData);
    if (matched == '\0') {
      punctuationBuffer[0] = 0;
    }
  }
  else {
    punctuationBuffer[0] = 0;
  }
  punctuationCursor = &punctuationBuffer[0];
  keyLayoutCount = Zi8GetTableCount(language,4,workData);
  if (((ZiAlphaWork*)workData)->wordState != '\0') {
    keyLayoutCount = 0;
  }
  if (keyLayoutCount != 0) {
    keyLayout = (ziU8 *)Zi8GetTableAddress(language,4,workData);
  }
  for (dictionaryIndex = 0; (int)dictionaryIndex <= (int)(unsigned int)((ZiAlphaWork*)workData)->dictionaryCount;
      dictionaryIndex = dictionaryIndex + 1) {
    if (((ZiAlphaWork*)workData)->dictionaryCounts != 0) {
      if (dictionaryIndex == 0) {
        Zi8Memset(((ZiAlphaWork*)workData)->dictionaryCounts,0,((ZiAlphaWork*)workData)->dictionaryCount);
      }
      else {
        ((ZiAlphaWork*)workData)->dictionaryCounts[dictionaryIndex - 1] = (char)candidateCount;
      }
    }
    if (dictionaryIndex == ((ZiAlphaWork*)workData)->dictionaryCount) {
      if (((ZiAlphaOptions*)optionData)->lookupMode == '\0') {
        dictionaryKind = 10;
        goto selectDictionary;
      }
    }
    else {
      dictionaryKind = (unsigned int)((ZiAlphaWork*)workData)->dictionaryKinds[dictionaryIndex];
      if ((dictionaryKind != 0xc) || (languagePassCount == 2)) {
selectDictionary:
        if ((!secondLanguagePass) ||
           ((dictionaryKind != 10 && (((9 < dictionaryKind || (4 < dictionaryKind)) || (dictionaryKind == 0)))))) {
          dictionaryExact = 1;
          if (dictionaryKind == 4) {
            if ((int)elementCount < (int)(unsigned int)(ziU8)((ZiAlphaOptions*)optionData)->minWordLength) goto finishDictionaryPass;
          }
          else if (dictionaryKind < 4) {
            if (dictionaryKind < 3) {
              if (dictionaryKind == 0) {
selectCompletionDictionary:
                if ((((elementCount == 1) && (prefixCount == 0)) && (0xeff0 < *elements)) &&
                   ((*elements < 0xf011 && (!contextEnabled)))) goto finishDictionaryPass;
                dictionaryExact = 0;
                candidateLength = dictionaryIndex;
                if (languagePassCount == 2) {
                  do {
                    candidateLength = candidateLength + 1;
                    if ((int)(unsigned int)((ZiAlphaWork*)workData)->dictionaryCount <= (int)candidateLength)
                    goto selectLanguagePass;
                  } while (((((ZiAlphaWork*)workData)->dictionaryKinds[candidateLength] != '\x01') &&
                           (((ZiAlphaWork*)workData)->dictionaryKinds[candidateLength] != '\x02')) &&
                          ((((ZiAlphaWork*)workData)->dictionaryKinds[candidateLength] != '\x04' &&
                           (((ZiAlphaWork*)workData)->dictionaryKinds[candidateLength] != '\x03'))));
                  switchedLanguage = ZI8_TRUE;
selectLanguagePass:
                  if ((int)(unsigned int)((ZiAlphaWork*)workData)->dictionaryCount <= (int)candidateLength) {
                    languagePassCount = 1;
                    language = parameters->subLanguage;
                    dictionaryStatus[1] = 0;
                    dictionaryStatus[2] = 0;
                    dictionaryStatus[3] = 0;
                    dictionaryStatus[4] = 0;
                    dictionaryStatus[9] = 0;
                    dictionaryStatus[5] = 0;
                    dictionaryStatus[6] = 0;
                    dictionaryStatus[7] = 0;
                    dictionaryStatus[8] = 0;
                    completionAllowed = secondaryCompletionAllowed;
                    goto prepareDictionaries;
                  }
                }
                if (languagePassCount == 1) {
                  language = parameters->language;
                  completionAllowed = primaryCompletionAllowed;
                }
              }
            }
            else if (((int)elementCount < (int)(unsigned int)(ziU8)((ZiAlphaOptions*)optionData)->minWordLength) || (elementCount == 1))
            goto finishDictionaryPass;
          }
          else if (dictionaryKind == 10) {
            if ((((elementCount != 1) ||
                 (candidateLength = Zi8GetTableCount(language,0x1f,workData), (candidateLength & 0x40) != 0)) ||
                ((*elements < 0xeff1 ||
                 ((0xf010 < *elements ||
                  (matched = Zi8getKeyLayout(language,*elements,(punctuationBuffer + 1),parameters->elementCount,workData
                                           ), matched == '\0')))))) ||
               (((((ZiAlphaWork*)workData)->suffixMode == '\0' &&
                 ((parameters->firstCandidate == 0 && (candidateCount == 0)))) &&
                ((parameters->currentWord == 0 ||
                 ((parameters->wordCharCount == 0 ||
                  (parameters->currentWord[parameters->wordCharCount - 1] == 0x20))))))))
            goto finishDictionaryPass;
            if ((candidateCount == 0) &&
               ((((!punctuationCandidate && (parameters->firstCandidate == firstCandidate)) &&
                 ((parameters->currentWord == 0 ||
                  ((parameters->wordCharCount == 0 ||
                   (parameters->currentWord[parameters->wordCharCount - 1] == 0x20)))))) &&
                (firstCandidate != 0)))) {
              firstCandidate = firstCandidate - 1;
            }
            punctuationCursor = (punctuationBuffer + 1);
            if (((candidateCount == 0) &&
                (((parameters->firstCandidate == 0 || (parameters->firstCandidate == firstCandidate))
                 && (((ZiAlphaWork*)workData)->suffixMode == '\0')))) &&
               (((parameters->currentWord == 0 || (parameters->wordCharCount == 0)) ||
                (parameters->currentWord[parameters->wordCharCount - 1] == 0x20)))) {
              if (parameters->getMode == 1) {
                punctuationBuffer[0] = *elements;
              }
              else {
                punctuationBuffer[0] = 0x3e;
              }
              punctuationCursor = &punctuationBuffer[0];
            }
            punctuationCandidate = ZI8_FALSE;
          }
          else {
            if (((9 < dictionaryKind) || (dictionaryKind < 9)) ||
               ((elementCount != 1 || ((*elements < 0xeff1 || (0xf010 < *elements))))))
            goto selectCompletionDictionary;
            dictionaryKind = 1;
          }
          do {
            wordLength = 0;
            matchMode = dictionaryExact;
            switch(dictionaryKind) {
            case 1:
            case 5:
              goto matchRomDictionary;
            case 2:
            case 6:
              if (elementCount != 0) {
                wordLength = Zi8MatchPUDdata(elements,elementCount & 0xff,language,wordCursor,
                                             wordCapacity & 0xffff,dictionaryExact,
                                             dictionaryStatus[dictionaryKind] & 0xff,workData);
                wordLength = wordLength & 0xff;
              }
              break;
            case 3:
            case 7:
              while( ZI8_TRUE ) {
                wordLength = Zi8MatchUWDdata(elements,elementCount & 0xff,
                                             parameters->currentWord,parameters->wordCharCount,
                                             language,wordCursor,wordCapacity & 0xffff,dictionaryExact,
                                             dictionaryStatus[dictionaryKind] & 0xff,workData);
                wordLength = wordLength & 0xff;
                if (((elementCount != 0) || (wordLength != 1)) || (*wordCursor != 0x20)) break;
                dictionaryStatus[dictionaryKind] = 1;
              }
              break;
            case 4:
            case 8:
              if (elementCount != 0) {
                wordLength = Zi8MatchOEMdata(elements,elementCount & 0xff,language,wordCursor,
                                             wordCapacity & 0xffff,dictionaryExact,
                                             dictionaryStatus[dictionaryKind] & 0xff,workData);
                wordLength = wordLength & 0xff;
              }
              break;
            case 9:
              matchMode = 2;
matchRomDictionary:
              if (elementCount == 0) break;
              if ((((matchMode == 0) && (completionAllowed)) &&
                  ((2 < (int)elementCount &&
                   ((((ZiAlphaWork*)workData)->language == language &&
                    ((unsigned int)((ZiAlphaWork*)workData)->prefixCount == elementCount - 1)))))) &&
                 (elements[elementCount - 1] == 0xeff1)) {
                wordLength = 0;
              }
              else {
                if (alternateSingleCharacter != 2) {
                  wordLength = Zi8MatchROMdata(elements,elementCount & 0xff,language,wordCursor,
                                               wordCapacity & 0xffff,matchMode,
                                               dictionaryStatus[dictionaryKind] & 0xff,0,exactLengthOnly,workData);
                  wordLength = wordLength & 0xff;
                }
                if ((alternateSingleCharacter != 0) && ((wordLength == 0 || (*wordCursor == *elements)))) {
                  if (alternateSingleCharacter == 1) {
                    alternateSingleCharacter = 2;
                    wordLength = Zi8MatchROMdata(elements,elementCount & 0xff,parameters->subLanguage,wordCursor,
                                                 wordCapacity & 0xffff,1,0,0,exactLengthOnly,workData);
                    wordLength = wordLength & 0xff;
                  }
                  else {
                    wordLength = Zi8MatchROMdata(elements,elementCount & 0xff,parameters->subLanguage,wordCursor,
                                                 wordCapacity & 0xffff,1,1,0,exactLengthOnly,workData);
                    wordLength = wordLength & 0xff;
                  }
                }
              }
              if ((dictionaryExact != 0) && ((int)elementCount < (int)wordLength)) {
                wordLength = 0;
              }
              if ((((wordLength == 0) && (*punctuationCursor != 0)) && (dictionaryExact != 0)) &&
                 ((((ZiAlphaWork*)workData)->singleCharacter != 0 && (parameters->elementCount == 2)))) {
                *wordCursor = ((ZiAlphaWork*)workData)->singleCharacter;
                wordCursor[1] = *punctuationCursor;
                punctuationCursor = punctuationCursor + 1;
                wordCursor[2] = 0;
                wordLength = 2;
              }
              if (((apostropheIndex != 0) && (wordLength != 0)) && (elementCount == parameters->elementCount)) {
                if (language == 0x2f) {
                  matched = Zi8ITspecialExclusion
                                     (wordCursor + apostropheIndex,apostropheIndex,wordLength - apostropheIndex);
                  if (matched != '\0') {
                    wordLength = 0;
                  }
                }
                else if (language == 0x58) {
                  matched = Zi8_814659E8(wordCursor + apostropheIndex,apostropheIndex,wordLength - apostropheIndex);
                  if (matched != '\0') {
                    wordLength = 0;
                  }
                }
                else {
                  matched = Zi8IsVowel(language,wordCursor[apostropheIndex]);
                  if (matched == '\0') {
                    wordLength = 0;
                  }
                }
                if (wordLength != 0) goto filterVowelCandidate;
                dictionaryStatus[dictionaryKind] = 1;
                if (0xeff0 < elements[apostropheIndex]) goto retryDictionary;
                goto finishDictionaryPass;
              }
filterVowelCandidate:
              if ((wordLength != 0) && (vowelRestriction)) {
                if ((*wordCursor < 0x30) || (0x39 < *wordCursor)) {
                  if (((elementCount == 1) && (dictionaryKind != 10)) && (0xeff0 < *wordCursor)) {
                    punctuationCandidate = ZI8_TRUE;
                    goto finishDictionaryPass;
                  }
                  if (language == 0x2f) {
                    matched = Zi8ITspecialExclusion(wordCursor,prefixCount,wordLength);
                    if (matched != '\0') {
                      wordLength = 0;
                    }
                  }
                  else if (language == 0x58) {
                    matched = Zi8_814659E8(wordCursor,prefixCount,wordLength);
                    if (matched != '\0') {
                      wordLength = 0;
                    }
                  }
                  else {
                    matched = Zi8IsVowel(language,*wordCursor);
                    if (matched == '\0') {
                      wordLength = 0;
                    }
                  }
                }
                else {
                  wordLength = 0;
                }
                if (wordLength == 0) {
                  dictionaryStatus[dictionaryKind] = 1;
                  goto retryDictionary;
                }
              }
              if (wordLength != 0) {
                if (language == parameters->language) {
                  primaryMatched = ZI8_TRUE;
                }
                else {
                  secondaryMatched = ZI8_TRUE;
                }
              }
              Zi8IsZicorpSignature(wordCursor,wordLength,workData);
              break;
            case 10:
              character = *punctuationCursor;
              *wordCursor = character;
              if (character == 0) {
                wordLength = 0;
              }
              else {
                punctuationCursor = punctuationCursor + 1;
                wordLength = 1;
              }
              break;
            case 0xb:
              if (prefixCount == 0) {
                if (retryPunctuation) {
                  for (index = 0;
                      (index < (int)(parameters->elementCount - 1) &&
                      (wordCursor[index] = ((ZiAlphaWork*)workData)->prefix[index],
                      wordCursor[index] != 0)); index = index + 1) {
                  }
                  if (index < (int)(parameters->elementCount - 1)) {
                    wordLength = 0;
                  }
                  else {
appendPunctuation:
                    character = *punctuationCursor;
                    wordLength = index + 1;
                    wordCursor[index] = character;
                    if (character == 0) {
                      wordLength = 0;
                    }
                    else {
                      punctuationCursor = punctuationCursor + 1;
                    }
                  }
                }
                else {
                  for (index = 0;
                      (index < (int)(unsigned int)((ZiAlphaWork*)workData)->rememberedCount &&
                      (wordCursor[index] = ((ZiAlphaWork*)workData)->rememberedWord[index],
                      wordCursor[index] != 0)); index = index + 1) {
                  }
                  if ((int)(unsigned int)((ZiAlphaWork*)workData)->rememberedCount <= index) goto appendPunctuation;
                  wordLength = 0;
                }
              }
            }
            dictionaryStatus[dictionaryKind] = 1;
            if (wordLength == 0) {
              dictionaryStatus[dictionaryKind] = 2;
              if ((((((((ZiAlphaWork*)workData)->prefixEnabled != '\0') && (!retryPunctuation)) && (parameters->elementCount != 0)) &&
                   (((int)(parameters->elementCount - 1) <= (int)(unsigned int)((ZiAlphaWork*)workData)->requiredLength &&
                    (parameters->elements[parameters->elementCount - 1] == 0xEFF1)))) &&
                  (((((ZiAlphaWork*)workData)->prefixEnabled != '\x01' ||
                    (((ZiAlphaWork*)workData)->requiredLength != parameters->elementCount)) &&
                   (((((ZiAlphaWork*)workData)->prefixLength == '\0' ||
                     ((unsigned int)parameters->elementCount <= ((ZiAlphaWork*)workData)->prefixLength + 1)) && (dictionaryExact != 0)))
                   ))) && ((((completionAllowed && (prefixCount == 0)) && (dictionaryKind != 0xb)) &&
                           ((((int)dictionaryIndex < (int)(unsigned int)((ZiAlphaWork*)workData)->dictionaryCount &&
                             (((ZiAlphaOptions*)optionData)->lookupMode == '\0')) &&
                            (((ZiAlphaWork*)workData)->dictionaries[language] == 0)))))) {
                if (language != ((ZiAlphaWork*)workData)->language) break;
                characterCount = ((ZiAlphaWork*)workData)->dictionaryKinds[dictionaryIndex + 1];
                if ((characterCount == 0xc) || (((characterCount < 0xc && (characterCount < 9)) && (4 < characterCount)))) {
                  matched = Zi8getKeyLayout(language,0xeff1,&punctuationBuffer[0],1,workData);
                  if (matched == '\0') {
                    punctuationBuffer[0] = 0;
                  }
                  punctuationCursor = &punctuationBuffer[0];
                  dictionaryKind = 0xb;
                  retryPunctuation = ZI8_TRUE;
                  goto retryDictionary;
                }
              }
              if ((((((dictionaryExact == 0) || (!completionAllowed)) || (prefixCount != 0)) ||
                   ((dictionaryKind == 0xb ||
                    ((int)(unsigned int)((ZiAlphaWork*)workData)->dictionaryCount <= (int)dictionaryIndex)))) ||
                  (elements == (ziU16 *)0x0)) ||
                 ((((elementCount == 0 || (elements[elementCount - 1] != 0xeff1)) ||
                   (((unsigned int)((ZiAlphaWork*)workData)->rememberedCount != parameters->elementCount - 1 ||
                    (((((ZiAlphaWork*)workData)->rememberedWord[0] == 0 || (((ZiAlphaOptions*)optionData)->lookupMode != '\0')) ||
                     (((ZiAlphaWork*)workData)->dictionaries[language] != 0)))))) ||
                  (languagePassCount == 2)))) break;
              characterCount = ((ZiAlphaWork*)workData)->dictionaryKinds[dictionaryIndex + 1];
              if ((characterCount != 0xc) && (((0xb < characterCount || (8 < characterCount)) || (characterCount < 5)))) break;
              matched = Zi8getKeyLayout(language,0xeff1,&punctuationBuffer[0],1,workData);
              if (matched == '\0') {
                punctuationBuffer[0] = 0;
              }
              punctuationCursor = &punctuationBuffer[0];
              dictionaryKind = 0xb;
            }
            else if ((int)(unsigned int)(ziU8)((ZiAlphaOptions*)optionData)->minWordLength <= (int)wordLength) {
              if (vowelRestriction) {
                if ((*wordCursor < 0x30) || (0x39 < *wordCursor)) {
                  if (language == 0x2f) {
                    matched = Zi8ITspecialExclusion(wordCursor,prefixCount,wordLength);
                  }
                  else {
                    if (language != 0x58) {
                      matched = Zi8IsVowel(language,*wordCursor);
                      if (matched != '\0') goto prepareCandidate;
                      goto retryDictionary;
                    }
                    matched = Zi8_814659E8(wordCursor,prefixCount,wordLength);
                  }
                  if (matched == '\0') goto prepareCandidate;
                }
              }
              else {
prepareCandidate:
                if (((elementCount == 1) && (dictionaryKind != 10)) &&
                   ((0xeff0 < *wordCursor && (*wordCursor < 0xf011)))) {
                  punctuationCandidate = ZI8_TRUE;
                  break;
                }
                wordCursor[wordLength] = 0;
                if (((exactLengthOnly != 0) && (elementCount != 0)) && ((int)elementCount < (int)wordLength))
                {
                  wordLength = elementCount;
                  wordCursor[elementCount] = 0;
                }
                candidateLength = Zi8DeTokenization(wordCursor,wordLength & 0xffff,wordCapacity & 0xffff,
                                           language);
                wordLength = candidateLength & 0xffff;
                if (((phoneticInput) && ((unsigned int)parameters->elementCount < (candidateLength & 0xff))) &&
                   ((wordCursor[wordLength - 1] == 0xf360 || (wordCursor[wordLength - 1] == 0x27)))) {
                  wordLength = wordLength - 1;
                  wordCursor[wordLength] = 0;
                }
                if ((!phoneticSeparator) ||
                   (matched = Zi8ZHCheckSpelling(wordCursor,parameters->elements,parameters->elementCount,
                                             workData), matched != '\0')) {
                  if ((((ZiAlphaWork*)workData)->caseMode != '\0') && ((!phoneticInput && (!phoneticSeparator)))) {
                    Zi8ChangeWordCase(wordCursor + -prefixCount,language,workData);
                  }
                  if ((((ZiAlphaOptions*)optionData)->suffixOnly != '\0') &&
                     ((int)(unsigned int)(ziU8)((ZiAlphaOptions*)optionData)->maxWordLength < (int)(wordLength + prefixCount))) {
                    wordLength = (ziU8)((ZiAlphaOptions*)optionData)->maxWordLength - prefixCount;
                    wordCursor[wordLength] = 0;
                  }
                  if (((int)(unsigned int)(ziU8)((ZiAlphaOptions*)optionData)->maxWordLength < (int)(wordLength + prefixCount)) ||
                     (matched = Zi8IsDupWordW(wordCursor + -prefixCount,wordLength + prefixCount & 0xff,
                                               workData), matched != '\0')) {
                    if ((prefixCount != 0) && ((ziU8)((ZiAlphaOptions*)optionData)->maxWordLength <= prefixCount)) break;
                  }
                  else {
                    matched = (char)wordLength;
                    prefixCharacterCount = (char)prefixCount;
                    if ((((keyLayoutCount == 0) || (((ZiAlphaOptions*)optionData)->lookupMode != '\0')) ||
                        ((int)(wordLength + prefixCount) < 2)) ||
                       (0x40 < (int)(wordLength + prefixCount))) goto emitCandidate;
                    if (dictionaryKind == 5) {
checkKeyLayout:
                      keyLayoutCursor = keyLayout;
                      characterCount = matched + prefixCharacterCount;
                      for (candidateLength = 0; (int)candidateLength < (int)(unsigned int)keyLayoutCount; candidateLength = candidateLength + 1) {
                        if (characterCount <= *keyLayoutCursor) {
                          encodedCursor = keyLayoutCursor + 1;
                          encodedCharacter = *keyLayoutCursor;
                          keyLayoutCursor = encodedCursor;
                          if (characterCount < encodedCharacter) {
                            candidateLength = (unsigned int)keyLayoutCount;
                          }
                          break;
                        }
                        keyLayoutCursor = keyLayoutCursor + *keyLayoutCursor + 1;
                      }
                      if ((int)candidateLength < (int)(unsigned int)keyLayoutCount) {
                        for (elementIndex = 0; (int)elementIndex < (int)(unsigned int)characterCount;
                            elementIndex = elementIndex + 1) {
                          encodedCharacter = Zi8ConvertWC2UC(wordCursor[elementIndex - prefixCount],language,
                                                   workData);
                          candidateBytes[elementIndex] = encodedCharacter;
                        }
                        for (; (int)candidateLength < (int)(unsigned int)keyLayoutCount; candidateLength = candidateLength + 1) {
                          for (elementIndex = 0;
                              ((int)elementIndex < (int)(unsigned int)characterCount &&
                              (candidateBytes[elementIndex] == keyLayoutCursor[elementIndex]));
                              elementIndex = elementIndex + 1) {
                          }
                          if (elementIndex == characterCount) {
                            wordCursor[-prefixCount] = 0;
                            goto retryDictionary;
                          }
                          encodedCursor = keyLayoutCursor + characterCount;
                          keyLayoutCursor = encodedCursor + 1;
                          if (characterCount < *encodedCursor) break;
                        }
                      }
                    }
                    else if (dictionaryKind < 5) {
                      if (dictionaryKind == 1) goto checkKeyLayout;
                    }
                    else if (dictionaryKind == 9) goto checkKeyLayout;
emitCandidate:
                    if (firstCandidate == 0) {
                      if (((ZiAlphaOptions*)optionData)->countOnly == '\0') {
                        if (((ZiAlphaOptions*)optionData)->lookupMode == '\0') {
                          if (((((ZiAlphaWork*)workData)->suffixMode == '\0') && (wordCursor[1] == 0)) &&
                             (candidateCount == 0)) {
                            if ((*wordCursor < 0xeff1) || (0xf010 < *wordCursor)) {
                              ((ZiAlphaWork*)workData)->singleCharacter = *wordCursor;
                            }
                            else {
                              ((ZiAlphaWork*)workData)->singleCharacter = 0;
                            }
                          }
                          if (((dictionaryExact == 0) || (parameters->elementCount != ((ZiAlphaWork*)workData)->rememberedCount))
                             || ((parameters->maxCandidates != 1 &&
                                 ((candidateCount != 0 || (parameters->firstCandidate != 0)))))) {
                            if (((dictionaryExact == 0) && (parameters->elementCount == ((ZiAlphaWork*)workData)->rememberedCount))
                               && ((parameters->maxCandidates == 1 ||
                                   ((candidateCount == 0 && (parameters->firstCandidate == 0)))))) {
                              ((ZiAlphaWork*)workData)->rememberedWord[0] = 0;
                            }
                          }
                          else {
                            for (characterIndex = 0; (int)characterIndex < (int)prefixCount; characterIndex = characterIndex + 1) {
                              ((ZiAlphaWork*)workData)->rememberedWord[characterIndex]
                                   = wordCursor[characterIndex - prefixCount];
                            }
                            for (index = 0; index < (int)wordLength; index = index + 1) {
                              ((ZiAlphaWork*)workData)->rememberedWord[index + prefixCount] =
                                   wordCursor[index];
                            }
                            ((ZiAlphaWork*)workData)->rememberedWord[index + prefixCount] = 0;
                          }
                          if ((((ZiAlphaWork*)workData)->suffixMode == '\0') &&
                             ((((((dictionaryKind == 1 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 1) != 0)) ||
                                 ((dictionaryKind == 3 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 2) != 0)))) ||
                                ((dictionaryKind == 2 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 4) != 0)))) ||
                               ((dictionaryKind == 4 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 8) != 0)))) &&
                              ((parameters->maxCandidates == 1 ||
                               ((candidateCount == 0 && (parameters->firstCandidate == 0)))))))) {
                            for (index = 0; index < (int)wordLength; index = index + 1) {
                              ((ZiAlphaWork*)workData)->prefix[index] = wordCursor[index];
                            }
                            ((ZiAlphaWork*)workData)->prefixCount = matched;
                            ((ZiAlphaWork*)workData)->language = language;
                          }
                          else if ((((ZiAlphaWork*)workData)->suffixLocked == '\0') &&
                                  (((((((dictionaryKind == 1 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 1) != 0)) ||
                                       ((dictionaryKind == 3 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 2) != 0))))
                                      || ((dictionaryKind == 2 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 4) != 0))))
                                     || ((dictionaryKind == 4 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 8) != 0))))
                                    && (((ZiAlphaWork*)workData)->language == language)) &&
                                   ((parameters->maxCandidates == 1 ||
                                    ((candidateCount == 0 && (parameters->firstCandidate == 0)))))))) {
                            if (wordLength == parameters->elementCount) {
                              for (index = 0; index < (int)wordLength; index = index + 1) {
                                ((ZiAlphaWork*)workData)->prefix[index] = wordCursor[index];
                              }
                              ((ZiAlphaWork*)workData)->prefixCount = matched;
                            }
                            else {
                              for (index = 0; index < (int)wordLength; index = index + 1) {
                                ((ZiAlphaWork*)workData)->suffix[index] = wordCursor[index];
                              }
                              ((ZiAlphaWork*)workData)->suffixCount = matched;
                            }
                          }
                          else if ((((ZiAlphaWork*)workData)->suffixMode != '\0') &&
                                  (((((dictionaryKind == 1 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 1) != 0)) ||
                                     ((dictionaryKind == 3 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 2) != 0)))) ||
                                    (((dictionaryKind == 2 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 4) != 0)) ||
                                     ((dictionaryKind == 4 && ((((ZiAlphaWork*)workData)->dictionaryFlags & 8) != 0))))))
                                   && ((((ZiAlphaWork*)workData)->language != language &&
                                       ((parameters->maxCandidates == 1 ||
                                        ((candidateCount == 0 && (parameters->firstCandidate == 0)))))))
                                   ))) {
                            for (index = 0; index < (int)wordLength; index = index + 1) {
                              ((ZiAlphaWork*)workData)->alternatePrefix[index] = wordCursor[index];
                            }
                            ((ZiAlphaWork*)workData)->alternatePrefixCount = (char)index;
                          }
                          wordLength = wordLength + 1;
                          if ((parameters->getOptions & 0xfd) == 0x80) {
                            if (outputLanguage == 0) {
                              outputLanguage = language;
                            }
                            for (index = 0; index < (int)(wordLength + prefixCount);
                                index = index + 1) {
                              outputCharacter = Zi8ConvertWC2UC(wordCursor[index - prefixCount],language,
                                                       workData);
                              encodedOutput[index] = outputCharacter;
                            }
                            encodedOutput[index] = 0;
                            encodedOutput = encodedOutput + index;
                          }
                          else {
                            if (((ZiAlphaOptions*)optionData)->suffixOnly != '\0') {
                              wordCursor = wordCursor + -prefixCount;
                              wordCapacity = wordCapacity + prefixCount;
                              index = wordLength + prefixCount;
                              for (wordLength = 0; (int)(parameters->elementCount + wordLength) < index;
                                  wordLength = wordLength + 1) {
                                wordCursor[wordLength] = wordCursor[wordLength + parameters->elementCount];
                              }
                            }
                            wordCursor[wordLength] = 0;
                            wordCursor = wordCursor + wordLength;
                            wordCapacity = wordCapacity - wordLength;
                          }
                          candidateCount = candidateCount + 1;
                          if ((int)(unsigned int)parameters->maxCandidates <= candidateCount) {
                            prefixCount = 0;
                            goto finishCandidates;
                          }
                          remainingCapacity = remainingCapacity - wordLength;
                          if (remainingCapacity <= (int)elementCount) {
                            prefixCount = 0;
                            goto finishCandidates;
                          }
                          if (prefixCount != 0) {
                            if ((((ZiAlphaOptions*)optionData)->countOnly != '\0') || ((parameters->getOptions & 0xfd) != 0x81)) {
                              wordCursor = candidateWord;
                              wordCapacity = 0x40;
                            }
                            for (index = 0; index < (int)(unsigned int)((ZiAlphaWork*)workData)->prefixCount;
                                index = index + 1) {
                              wordCursor[index] = ((ZiAlphaWork*)workData)->prefix[index];
                            }
                            wordCursor = wordCursor + ((ZiAlphaWork*)workData)->prefixCount;
                            wordCapacity = wordCapacity - ((ZiAlphaWork*)workData)->prefixCount;
                            if (((ZiAlphaWork*)workData)->suffixLocked != '\0') {
                              for (index = 0; index < (int)(unsigned int)((ZiAlphaWork*)workData)->suffixCount;
                                  index = index + 1) {
                                wordCursor[index] = ((ZiAlphaWork*)workData)->suffix[index];
                              }
                              wordCursor = wordCursor + ((ZiAlphaWork*)workData)->suffixCount;
                              wordCapacity = wordCapacity - ((ZiAlphaWork*)workData)->suffixCount;
                            }
                          }
                        }
                        else {
                          for (index = 0;
                              (index <= (int)wordLength &&
                              (wordCursor[index] == ((ZiAlphaOptions*)optionData)->dictionary[index]));
                              index = index + 1) {
                          }
                          if ((((((ZiAlphaWork*)workData)->operation != '\0') || ((int)wordLength <= index))
                              && ((((ZiAlphaWork*)workData)->operation == '\0' ||
                                  ((exactLengthOnly == 0 ||
                                   (candidateLength = Zi8WCharCount(((ZiAlphaOptions*)optionData)->dictionary,workData),
                                   (int)(candidateLength & 0xffff) <= index)))))) &&
                             ((exactLengthOnly != 0 || ((int)wordLength <= index)))) {
                            candidateCount = 1;
                            goto finishCandidates;
                          }
                        }
                      }
                      else {
                        if (((ZiAlphaOptions*)optionData)->suffixOnly != '\0') {
                          if ((int)(wordLength + prefixCount) < (int)(unsigned int)(ziU8)((ZiAlphaOptions*)optionData)->shortestWord) {
                            ((ZiAlphaOptions*)optionData)->shortestWord = matched + prefixCharacterCount;
                          }
                          if ((int)(unsigned int)(ziU8)((ZiAlphaOptions*)optionData)->longestWord < (int)(wordLength + prefixCount)) {
                            ((ZiAlphaOptions*)optionData)->longestWord = matched + prefixCharacterCount;
                          }
                        }
                        candidateCount = candidateCount + 1;
                        if (((ZiAlphaOptions*)optionData)->maxResults <= candidateCount) goto finishCandidates;
                      }
                    }
                    else {
                      firstCandidate = firstCandidate - 1;
                    }
                  }
                }
              }
            }
retryDictionary:;
          } while (dictionaryIndex != 0);
        }
      }
    }
finishDictionaryPass:;
  }
  if ((((candidateCount == 0) && (!punctuationCandidate)) &&
      ((parameters->firstCandidate == 0 &&
       (((parameters->elementCount == 1 &&
         (candidateLength = Zi8GetTableCount(parameters->language,0x1f,workData), (candidateLength & 0x40) == 0)) &&
        (0xeff0 < *parameters->elements)))))) &&
     ((*parameters->elements < 0xf011 &&
      (matched = Zi8getKeyLayout(parameters->language,*parameters->elements,&punctuationBuffer[0],1,workData),
      matched != '\0')))) {
    punctuationCandidate = ZI8_TRUE;
  }
  if (((candidateCount == 0) && (punctuationCandidate)) && (firstCandidate == 0)) {
    candidateCount = 1;
    if ((((ZiAlphaOptions*)optionData)->countOnly == '\0') && ((parameters->getOptions & 0xfd) != 0x81)) {
      *encodedOutput = 0x3e;
      encodedOutput[2] = 0;
      encodedOutput[1] = 0;
    }
    else {
      if (parameters->getMode == 1) {
        *wordCursor = *elements;
      }
      else {
        *wordCursor = 0x3e;
      }
      wordCursor[2] = 0;
      wordCursor[1] = 0;
      wordCursor = wordCursor + 2;
    }
    if (((ZiAlphaOptions*)optionData)->lookupMode == '\0') {
      ((ZiAlphaWork*)workData)->singleCharacter = 0;
    }
  }
  if (languagePassCount == 1) {
    secondLanguagePass = ZI8_TRUE;
    languagePassCount = 0;
    language = parameters->subLanguage;
    dictionaryStatus[9] = 0;
    dictionaryStatus[5] = 0;
    dictionaryStatus[6] = 0;
    dictionaryStatus[7] = 0;
    dictionaryStatus[8] = 0;
    completionAllowed = secondaryCompletionAllowed;
    if (switchedLanguage) {
      secondLanguagePass = ZI8_FALSE;
      dictionaryStatus[1] = 0;
      dictionaryStatus[2] = 0;
      dictionaryStatus[3] = 0;
      dictionaryStatus[4] = 0;
    }
    goto prepareDictionaries;
  }
  language = ((ZiAlphaWork*)workData)->language;
  if (language == 0) {
    language = parameters->language;
  }
  completionAllowed = secondaryCompletionAllowed;
  vowelRestriction = secondaryVowelRestriction;
  if (language == parameters->language) {
    completionAllowed = primaryCompletionAllowed;
    vowelRestriction = (primaryTableFlags & 2) == 0;
  }
  if ((((ZiAlphaOptions*)optionData)->lookupMode != '\0') || ((!vowelRestriction && (!completionAllowed)))) goto finishCandidates;
  if ((completionAllowed) &&
     ((((((ZiAlphaWork*)workData)->suffixMode == '\0' && (2 < (int)elementCount)) &&
       (elements[elementCount - 2] == 0xeff1)) &&
      ((unsigned int)((ZiAlphaWork*)workData)->prefixCount == elementCount - 2)))) {
    ((ZiAlphaWork*)workData)->prefixElementCount = ((ZiAlphaWork*)workData)->prefixCount + '\x01';
    ((ZiAlphaWork*)workData)->suffixMode = 1;
  }
  if ((((ZiAlphaWork*)workData)->suffixMode != '\0') && (!prefixActive)) {
    prefixActive = ZI8_TRUE;
    goto preparePrefix;
  }
  if ((((completionAllowed) && (((ZiAlphaWork*)workData)->suffixMode != '\0')) &&
      ((((ZiAlphaWork*)workData)->suffixLocked == '\0' && (2 < (int)elementCount)))) &&
     (((elements[elementCount - 2] == 0xeff1 &&
       ((unsigned int)((ZiAlphaWork*)workData)->suffixCount == elementCount - 2)) ||
      (((unsigned int)((ZiAlphaWork*)workData)->suffixCount == elementCount - 1 &&
       (matched = Zi8IsAlphaPunct(elements[elementCount - 1]), matched != '\0')))))) {
    if ((((ZiAlphaWork*)workData)->prefixEnabled == '\0') || (elements[elementCount - 1] != 0xeff1)) {
      if ((!primaryMatched) && (!secondaryMatched)) {
        ((ZiAlphaWork*)workData)->suffixLocked = 1;
        ((ZiAlphaWork*)workData)->suffixElementCount = parameters->elementCount - 1;
        if (prefixCount != 0) {
          wordCursor = wordCursor + -prefixCount;
          elements = elements + -prefixCount;
          elementCount = elementCount + prefixCount;
          wordCapacity = wordCapacity + prefixCount;
          prefixCount = 0;
        }
        goto preparePrefix;
      }
      goto tryAlternatePrefix;
    }
checkPrefixPunctuation:
    if ((1 < ((ZiAlphaWork*)workData)->prefixEnabled) &&
       (parameters->elements[parameters->elementCount - 1] != 0xEFF1))
    goto finishCandidates;
    if ((((*elements == 0xeff1) ||
         (matched = ZiIsLetterHyphen(*elements,workData), matched != '\0')) &&
        ((((ZiAlphaWork*)workData)->suffixLocked == '\0' ||
         (matched = ZiIsLetterHyphen(((ZiAlphaWork*)workData)->suffix[(((ZiAlphaWork*)workData)->suffixCount - 1)],
                                    workData), matched == '\0')))) &&
       (((((ZiAlphaWork*)workData)->suffixMode == '\0' ||
         ((((ZiAlphaWork*)workData)->suffixLocked != '\0' ||
          (matched = ZiIsLetterHyphen(((ZiAlphaWork*)workData)->prefix[((ZiAlphaWork*)workData)->prefixCount - 1],
                                     workData), matched == '\0')))) &&
        ((candidateLength = Zi8GetTableCount(language,0x1f,workData), (candidateLength & 8) == 0 &&
         (parameters->elements[parameters->elementCount - 1] != 0xEFF1)))))) {
      if (prefixActive) {
        wordCursor = wordCursor + -prefixCount;
        elements = elements + -prefixCount;
        elementCount = elementCount + prefixCount;
        wordCapacity = wordCapacity + prefixCount;
        prefixCount = 0;
      }
      if (((ZiAlphaWork*)workData)->suffixLocked == '\0') {
        ((ZiAlphaWork*)workData)->previousPrefixCount = ((ZiAlphaWork*)workData)->prefixElementCount;
        ((ZiAlphaWork*)workData)->prefixElementCount = parameters->elementCount;
        if (((ZiAlphaWork*)workData)->suffixMode == '\0') {
          ((ZiAlphaWork*)workData)->suffixMode = 1;
          ((ZiAlphaWork*)workData)->prefixCount = 0;
        }
        if (((((((ZiAlphaWork*)workData)->prefixCount == '\x03') && (((ZiAlphaWork*)workData)->prefix[0] == 0x77)) &&
             (((ZiAlphaWork*)workData)->prefix[1] == 0x77)) && (((ZiAlphaWork*)workData)->prefix[2] == 0x77)) ||
           (candidateLength = Zi8GetTableCount(language,0x1f,workData), (candidateLength & 0x100) != 0)) {
          ((ZiAlphaWork*)workData)->letterHyphen = 0x2e;
        }
        if ((elements[((ZiAlphaWork*)workData)->prefixCount] == 0xeff1) ||
           (matched = Zi8IsAlphaPunct(elements[((ZiAlphaWork*)workData)->prefixCount]), matched == '\0')) {
          characterCount = ((ZiAlphaWork*)workData)->prefixCount;
          ((ZiAlphaWork*)workData)->prefix[characterCount] = ((ZiAlphaWork*)workData)->letterHyphen;
          ((ZiAlphaWork*)workData)->prefixCount = characterCount + 1;
        }
        else {
          characterCount = ((ZiAlphaWork*)workData)->prefixCount;
          ((ZiAlphaWork*)workData)->prefix[characterCount] = elements[((ZiAlphaWork*)workData)->prefixCount]
          ;
          ((ZiAlphaWork*)workData)->prefixCount = characterCount + 1;
        }
        prefixActive = ZI8_TRUE;
      }
      else {
        ((ZiAlphaWork*)workData)->previousSuffixCount = ((ZiAlphaWork*)workData)->suffixElementCount;
        ((ZiAlphaWork*)workData)->suffixElementCount = parameters->elementCount;
        index = (unsigned int)((ZiAlphaWork*)workData)->prefixCount + (unsigned int)((ZiAlphaWork*)workData)->suffixCount;
        if ((elements[index] == 0xeff1) ||
           (matched = Zi8IsAlphaPunct(elements[index]), matched == '\0')) {
          characterCount = ((ZiAlphaWork*)workData)->suffixCount;
          ((ZiAlphaWork*)workData)->suffix[(unsigned int)characterCount] = ((ZiAlphaWork*)workData)->letterHyphen;
          ((ZiAlphaWork*)workData)->suffixCount = characterCount + 1;
        }
        else {
          characterCount = ((ZiAlphaWork*)workData)->suffixCount;
          ((ZiAlphaWork*)workData)->suffix[(unsigned int)characterCount] = elements[index];
          ((ZiAlphaWork*)workData)->suffixCount = characterCount + 1;
        }
        prefixActive = ZI8_TRUE;
      }
      goto preparePrefix;
    }
  }
  else {
tryAlternatePrefix:
    if ((prefixActive) && (1 < ((ZiAlphaWork*)workData)->alternatePrefixCount)) {
      if (language == parameters->language) {
        if (primaryMatched) {
          ((ZiAlphaWork*)workData)->alternatePrefixCount = 0;
        }
      }
      else if (secondaryMatched) {
        ((ZiAlphaWork*)workData)->alternatePrefixCount = 0;
      }
      if (((ZiAlphaWork*)workData)->alternatePrefixCount != '\0') {
        wordCursor = wordCursor + -prefixCount;
        elements = elements + -prefixCount;
        elementCount = elementCount + prefixCount;
        wordCapacity = wordCapacity + prefixCount;
        prefixCount = 0;
        prefixActive = ZI8_FALSE;
        ((ZiAlphaWork*)workData)->suffixMode = 0;
        ((ZiAlphaWork*)workData)->suffixLocked = 0;
        ((ZiAlphaWork*)workData)->suffixCount = 0;
        for (index = 0; index < (int)(unsigned int)((ZiAlphaWork*)workData)->alternatePrefixCount; index = index + 1) {
          ((ZiAlphaWork*)workData)->prefix[index] =
               ((ZiAlphaWork*)workData)->alternatePrefix[index];
        }
        ((ZiAlphaWork*)workData)->prefixCount = (char)index;
        if (((ZiAlphaWork*)workData)->language == parameters->language) {
          ((ZiAlphaWork*)workData)->language = parameters->subLanguage;
        }
        else {
          ((ZiAlphaWork*)workData)->language = parameters->language;
        }
        ((ZiAlphaWork*)workData)->alternatePrefixCount = 0;
      }
    }
    if ((((primaryMatched) && (secondaryMatched)) || (elementCount == 0)) ||
       (((language == parameters->language && (primaryMatched)) || ((language == parameters->subLanguage && (secondaryMatched))))))
    goto finishCandidates;
    if (completionAllowed) goto checkPrefixPunctuation;
  }
  if (((((((vowelRestriction) || (((ZiAlphaWork*)workData)->suffixMode != '\0')) ||
         (((ZiAlphaWork*)workData)->prefixCount == '\0')) ||
        (((int)elementCount < 3 || ((unsigned int)((ZiAlphaWork*)workData)->prefixCount != elementCount - 1)))) ||
       (matched = Zi8IsAlphaPunct(parameters->elements[((ZiAlphaWork*)workData)->prefixCount - 1]),
       matched == '\0')) &&
      (((!vowelRestriction && (((ZiAlphaWork*)workData)->suffixMode == '\0')) &&
       ((1 < parameters->elementCount &&
        (matched = Zi8IsAlphaPunct(parameters->elements[parameters->elementCount - 1]),
        matched == '\0')))))) ||
     ((((((ZiAlphaWork*)workData)->suffixMode != '\0' || (((ZiAlphaWork*)workData)->prefixCount == 0)) ||
       ((int)elementCount < 3)) ||
      (((unsigned int)((ZiAlphaWork*)workData)->prefixCount != elementCount - 1 ||
       (parameters->elements[parameters->elementCount - 1] == 0xEFF1))))))
  goto finishCandidates;
  ((ZiAlphaWork*)workData)->suffixMode = 1;
  ((ZiAlphaWork*)workData)->prefixElementCount = parameters->elementCount;
  prefixActive = ZI8_TRUE;
preparePrefix:
  matched = ((ZiAlphaWork*)workData)->suffixMode;
  character = Zi8GetTableCount(language,0x1f,workData);
  if (((((language == 0x3f) || (language == 4)) ||
       ((language == 0x40 || ((language == 0x58 || (language == 0x2f)))))) && (matched != '\0')
      ) && ((character & 0x10) != 0)) {
    vowelRestriction = ZI8_TRUE;
  }
  else {
    vowelRestriction = ZI8_FALSE;
  }
  if (((ZiAlphaWork*)workData)->suffixMode != '\0') {
    secondLanguagePass = ZI8_FALSE;
    if ((((ZiAlphaOptions*)optionData)->countOnly != '\0') || ((parameters->getOptions & 0xfd) != 0x81)) {
      wordCursor = candidateWord;
      wordCapacity = 0x40;
    }
    for (index = 0; index < 0xe; index = index + 1) {
      dictionaryStatus[index] = 0;
    }
    for (index = 0; index < (int)(unsigned int)((ZiAlphaWork*)workData)->prefixCount; index = index + 1) {
      wordCursor[index] = ((ZiAlphaWork*)workData)->prefix[index];
      if ((elements[index] != wordCursor[index]) &&
         (character = Zi8ConvertWC2Key(wordCursor[index],language,workData),
         elements[index] != character)) goto finishCandidates;
    }
    wordCursor = wordCursor + ((ZiAlphaWork*)workData)->prefixCount;
    elements = elements + ((ZiAlphaWork*)workData)->prefixCount;
    elementCount = elementCount - ((ZiAlphaWork*)workData)->prefixCount;
    wordCapacity = wordCapacity - ((ZiAlphaWork*)workData)->prefixCount;
    prefixCount = (unsigned int)((ZiAlphaWork*)workData)->prefixCount;
    if (((ZiAlphaWork*)workData)->suffixLocked != '\0') {
      for (index = 0; index < (int)(unsigned int)((ZiAlphaWork*)workData)->suffixCount; index = index + 1) {
        wordCursor[index] = ((ZiAlphaWork*)workData)->suffix[index];
        if ((elements[index] != wordCursor[index]) &&
           (character = Zi8ConvertWC2Key(wordCursor[index],language,workData),
           elements[index] != character)) goto finishCandidates;
      }
      wordCursor = wordCursor + ((ZiAlphaWork*)workData)->suffixCount;
      elements = elements + ((ZiAlphaWork*)workData)->suffixCount;
      elementCount = elementCount - ((ZiAlphaWork*)workData)->suffixCount;
      wordCapacity = wordCapacity - ((ZiAlphaWork*)workData)->suffixCount;
      prefixCount = prefixCount + ((ZiAlphaWork*)workData)->suffixCount;
    }
    if ((vowelRestriction) && (wordCursor[-1] != 0x27)) {
      vowelRestriction = ZI8_FALSE;
    }
  }
  goto prepareDictionaryOrder;
}




ziU32 Zi8DeTokenization(ziWChar* word, ziU32 length, ziU16 capacity, ziU16 language) {
    ziU16 index;
    ziBool changed = ZI8_FALSE;
    ziU16 outputCount = 0;
    ziWChar expandedWord[64];
    if (language != 28 && language != 55 && language != 56 && language != 73 && language != 53 && language != 32 && language != 72 && language != 57) return length;
    if (capacity > 64) capacity = 64;
    for (index = 0; (ziU16)index < (ziU16)length && word[index] != 0; ++index) {
        switch (word[index]) {
        case 0xf800:
            expandedWord[outputCount++] = 0xab0;
            expandedWord[outputCount++] = 0xacd;
            changed = ZI8_TRUE;
            break;
        case 0xf801:
            expandedWord[outputCount++] = 0x9b0;
            expandedWord[outputCount++] = 0x9cd;
            changed = ZI8_TRUE;
            break;
        case 0xf802:
            expandedWord[outputCount++] = 0x9cd;
            expandedWord[outputCount++] = 0x9af;
            changed = ZI8_TRUE;
            break;
        case 0xf803:
            expandedWord[outputCount++] = 0x9a4;
            expandedWord[outputCount++] = 0x9cd;
            expandedWord[outputCount++] = 0x200d;
            changed = ZI8_TRUE;
            break;
        case 0xf804:
            expandedWord[outputCount++] = 0x9cd;
            expandedWord[outputCount++] = 0x200c;
            changed = ZI8_TRUE;
            break;
        case 0xf805:
            expandedWord[outputCount++] = 0x9cd;
            expandedWord[outputCount++] = 0x200d;
            changed = ZI8_TRUE;
            break;
        case 0xf806:
            expandedWord[outputCount++] = 0xb95;
            expandedWord[outputCount++] = 0xbcd;
            expandedWord[outputCount++] = 0xbb7;
            changed = ZI8_TRUE;
            break;
        case 0xf807:
            expandedWord[outputCount++] = 0xbb8;
            expandedWord[outputCount++] = 0xbcd;
            expandedWord[outputCount++] = 0xbb0;
            expandedWord[outputCount++] = 0xbc0;
            changed = ZI8_TRUE;
            break;
        case 0xf808:
            expandedWord[outputCount++] = 0x930;
            expandedWord[outputCount++] = 0x94d;
            changed = ZI8_TRUE;
            break;
        case 0xf809:
            expandedWord[outputCount++] = 0x915;
            expandedWord[outputCount++] = 0x94d;
            expandedWord[outputCount++] = 0x937;
            changed = ZI8_TRUE;
            break;
        case 0xf80a:
            expandedWord[outputCount++] = 0x91c;
            expandedWord[outputCount++] = 0x94d;
            expandedWord[outputCount++] = 0x91e;
            changed = ZI8_TRUE;
            break;
        case 0xf80b:
            expandedWord[outputCount++] = 0x931;
            expandedWord[outputCount++] = 0x94d;
            changed = ZI8_TRUE;
            break;
        case 0xf80c:
            expandedWord[outputCount++] = 0x905;
            expandedWord[outputCount++] = 0x945;
            changed = ZI8_TRUE;
            break;
        case 0xf80d:
            expandedWord[outputCount++] = 0xcb0;
            expandedWord[outputCount++] = 0xccd;
            changed = ZI8_TRUE;
            break;
        case 0xf80e:
            expandedWord[outputCount++] = 0xccd;
            expandedWord[outputCount++] = 0x200d;
            changed = ZI8_TRUE;
            break;
        case 0xf80f:
            expandedWord[outputCount++] = 0xccd;
            expandedWord[outputCount++] = 0x200c;
            changed = ZI8_TRUE;
            break;
        case 0xf810:
            expandedWord[outputCount++] = 0xd33;
            expandedWord[outputCount++] = 0xd4d;
            expandedWord[outputCount++] = 0x200d;
            changed = ZI8_TRUE;
            break;
        case 0xf811:
            expandedWord[outputCount++] = 0xd4d;
            expandedWord[outputCount++] = 0x200c;
            changed = ZI8_TRUE;
            break;
        case 0xf812:
            expandedWord[outputCount++] = 0xd23;
            expandedWord[outputCount++] = 0xd4d;
            expandedWord[outputCount++] = 0x200d;
            changed = ZI8_TRUE;
            break;
        case 0xf813:
            expandedWord[outputCount++] = 0xd28;
            expandedWord[outputCount++] = 0xd4d;
            expandedWord[outputCount++] = 0x200d;
            changed = ZI8_TRUE;
            break;
        case 0xf814:
            expandedWord[outputCount++] = 0xd30;
            expandedWord[outputCount++] = 0xd4d;
            expandedWord[outputCount++] = 0x200d;
            changed = ZI8_TRUE;
            break;
        case 0xf815:
            expandedWord[outputCount++] = 0xd32;
            expandedWord[outputCount++] = 0xd4d;
            expandedWord[outputCount++] = 0x200d;
            changed = ZI8_TRUE;
            break;
        case 0xf816:
            expandedWord[outputCount++] = 0xc15;
            expandedWord[outputCount++] = 0xc4d;
            expandedWord[outputCount++] = 0xc37;
            changed = ZI8_TRUE;
            break;
        case 0xf817:
            expandedWord[outputCount++] = 0xc4d;
            expandedWord[outputCount++] = 0x200c;
            changed = ZI8_TRUE;
            break;
        case 0xf818:
            expandedWord[outputCount++] = 0x94d;
            expandedWord[outputCount++] = 0x930;
            changed = ZI8_TRUE;
            break;
        case 0xf819:
            expandedWord[outputCount++] = 0x924;
            expandedWord[outputCount++] = 0x94d;
            expandedWord[outputCount++] = 0x930;
            changed = ZI8_TRUE;
            break;
        case 0xf81a:
            expandedWord[outputCount++] = 0x99c;
            expandedWord[outputCount++] = 0x9bc;
            changed = ZI8_TRUE;
            break;
        case 0xf81b:
            expandedWord[outputCount++] = 0x9cd;
            expandedWord[outputCount++] = 0x9b0;
            changed = ZI8_TRUE;
            break;
        case 0xf81c:
            expandedWord[outputCount++] = 0x9cd;
            expandedWord[outputCount++] = 0x9ac;
            changed = ZI8_TRUE;
            break;
        case 0xf820:
            expandedWord[outputCount++] = 0x936;
            expandedWord[outputCount++] = 0x94d;
            expandedWord[outputCount++] = 0x930;
            changed = ZI8_TRUE;
            break;
        case 0xf90b:
            expandedWord[outputCount++] = 0x930;
            expandedWord[outputCount++] = 0x94d;
            expandedWord[outputCount++] = 0x200d;
            changed = ZI8_TRUE;
            break;
        case 0xf90c:
            expandedWord[outputCount++] = 0x90d;
            changed = ZI8_TRUE;
            break;
        default:
            expandedWord[outputCount++] = word[index];
            break;
        }
        if (outputCount >= capacity) return length;
    }
    if (changed) {
        for (index = 0; index < outputCount; ++index) word[index] = expandedWord[index];
        word[index] = 0;
        return index;
    }
    return length;
}
