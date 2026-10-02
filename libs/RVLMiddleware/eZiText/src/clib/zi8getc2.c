#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>
#include <zi8clib/zi8getc2.h>

typedef struct {
    ziU8 countOnly;
    ziU8 maxWordLength;
    ziU8 lookupMode;
    ziU8 suffixOnly;
    ziU8 controls[8];
    ziU32 maxCount;
    ziU16 capacity;
    ziU8 minWordLength;
    ziU8 flags;
    ziU16 candidateCapacity;
    ziU8 checkOnly;
    ziU8 reserved;
} ZiCandidateOptions;

const ziU8 Zi8SOdefaultArray[16] = {1, 4, 3, 2, 1, 8, 7, 6, 5, 0};
const ziFuzzyPYPairs Zi8PYdefaultFuzzyPairs = {0, 1, 1, 1, 1, 1, 1};
const ziFuzzyZYPairs Zi8ZYdefaultFuzzyPairs = {0};

ziU8 Zi8GetFormatVersion(ziU8 language, ziPtr work);
ziU32 Zi8GetTableAddress(ziU8 language, ziU8 table, ziPtr work);
ziU16 Zi8GetTableCount(ziU8 language, ziU8 table, ziPtr work);
ziU16 Zi8GetVersion(ziPtr work);
ziU16 Zi8GetOEMID(ziPtr work);
ziU16 Zi8GetBuildID(ziPtr work);
void Zi8Memcpy(ziU8* destination, ziU8* source, ziS32 count);
ziU32 Zi8GetCandidatesOrCount(ziGetParam* parameters, ZiCandidateOptions* options, ziPtr work);

ziBool Zi8ZHsetPYfuzzyPairs(ziFuzzyPYPairs pairs ZI_NEED_WORK) {
    if (pairs.ziDefault) {
        ZI_WORK->unk_0x1B28.word = *(const ziU32*)&Zi8PYdefaultFuzzyPairs;
    } else {
        ZI_WORK->unk_0x1B28.word = *(ziU32*)&pairs;
    }
    return 1;
}

ziBool Zi8ZHsetZYfuzzyPairs(ziFuzzyZYPairs pairs ZI_NEED_WORK) {
    if (pairs.ziDefault) {
        ZI_WORK->unk_0x1B2C.word = *(const ziU32*)&Zi8ZYdefaultFuzzyPairs;
    } else {
        ZI_WORK->unk_0x1B2C.word = *(ziU32*)&pairs;
    }
    return 1;
}

ziBool Zi8SetLatinSearchOrder(ziU8* searchArray, ziU8 searchSize ZI_NEED_WORK) {
    if (searchArray == 0 || *searchArray == 0) {
        ZI_WORK->formats = (ziU32)Zi8SOdefaultArray;
        ZI_WORK->unk_0x1418 = 9;
    } else {
        ZI_WORK->formats = (ziU32)searchArray;
        ZI_WORK->unk_0x1418 = searchSize;
    }
    return 1;
}

ziU16 Zi8GetGlobalDataSize(void) {
    return sizeof(struct __zi8_work_data_s);
}

static ziU16 Zi8GetDataSignature(ziU8* destination, ziU16 capacity, ziU8 language, ziPtr work) {
    ziU8* signature;
    ziU16 length;
    if (language == 1) {
        if (Zi8GetFormatVersion(1, work) < 8) {
            Zi8LogError(0x26f, work);
            return 0;
        }
        length = 0x1e;
    } else {
        length = 3;
    }
    signature = (ziU8*)Zi8GetTableAddress(language, (ziU8)length, work);
    length = Zi8GetTableCount(language, (ziU8)length, work);
    if (length == 0 || length > capacity) {
        Zi8LogError(0x961, work);
        return 0;
    }
    Zi8Memcpy(destination, signature, length);
    destination[length] = 0;
    Zi8LogError(100, work);
    return length;
}

static ziU16 Zi8GetEngineSignature(ziU8* destination, ziPtr work) {
    ziU16 index = 0;
    struct { ziU16 minor; } version;
    ziU16 number;
    destination[index++] = 'v';
    number = (Zi8GetVersion(work) & 0xff00) >> 8;
    version.minor = Zi8GetVersion(work) & 0xff;
    destination[index++] = (ziU8)(number / 10 + '0');
    destination[index++] = (ziU8)(number % 10 + '0');
    destination[index++] = (ziU8)(version.minor / 10 + '0');
    destination[index++] = (ziU8)(version.minor % 10 + '0');
    destination[index++] = 'o';
    number = Zi8GetOEMID(work);
    destination[index++] = (ziU8)(number / 100 + '0');
    destination[index++] = (ziU8)((number % 100) / 10 + '0');
    destination[index++] = (ziU8)((number % 100) % 10 + '0');
    destination[index++] = 'b';
    number = Zi8GetBuildID(work);
    destination[index++] = (ziU8)(number / 100 + '0');
    destination[index++] = (ziU8)((number % 100) / 10 + '0');
    destination[index++] = (ziU8)((number % 100) % 10 + '0');
    destination[index] = 0;
    return index;
}

static ziBool Zi8AlphaSignature(ziGetParam* parameters, ziBool countOnly ZI_NEED_WORK) {
    ziU16 secondLength;
    struct { ziU16 length; ziU8* second; ziU8* first; } signatures;
    ziU8 dictionary[32];
    ziU8 engine[32];
    ziU16 length;
    ziU8* current;
    ziWChar* output = parameters->candidates;

    signatures.first = 0;
    signatures.second = 0;
    signatures.length = 0;
    secondLength = 0;
    Zi8LogError(100, ZI_WORK);
    parameters->letters = 0;
    length = Zi8GetDataSignature(dictionary, 0x20, parameters->language, ZI_WORK);
    if (length != 0 && parameters->elementCount <= length) {
        signatures.first = dictionary;
        signatures.second = engine;
        signatures.length = length;
    } else {
        signatures.first = engine;
    }
    length = Zi8GetEngineSignature(engine, ZI_WORK);
    if (length < parameters->elementCount) {
        if (signatures.length != 0) {
            signatures.second = 0;
            length = 1;
        } else {
            Zi8ReplaceLastError(500, ZI_WORK);
            return 0;
        }
    } else if (signatures.length != 0) {
        secondLength = length;
        length = 2;
    } else {
        signatures.length = length;
        length = 1;
    }
    if (parameters->firstCandidate >= length) {
        Zi8ReplaceLastError(501, ZI_WORK);
        return 0;
    }
    length = length - parameters->firstCandidate;
    if (countOnly != 0) {
        parameters->letters = length;
        ZI_WORK->unk_0x0A = 0xff;
        return 1;
    }
    if (parameters->maxCandidates < length) length = parameters->maxCandidates;
    parameters->letters = length;
    if ((parameters->getOptions & 0x80) == 0) {
        ZI_WORK->language = parameters->language;
        parameters->candidates[0] = 0xfff0;
        output = (ziWChar*)&ZI_WORK->unk_0x338;
    }
    if (parameters->firstCandidate != 0) {
        current = signatures.second;
        length = secondLength;
    } else {
        current = signatures.first;
        length = signatures.length;
    }
    if (length > ZI_WORK->unk_0x0A) length = ZI_WORK->unk_0x0A;
    if ((parameters->elementCount < ZI_WORK->unk_0x140C[0] ||
         (parameters->getOptions & 0x7e) == 2) && length > parameters->elementCount) {
        length = parameters->elementCount;
    }
    while (length-- != 0) *output++ = (ziU8)*current++;
    *output++ = 0;
    if (parameters->letters == 2) {
        current = signatures.second;
        length = secondLength;
        if (length > ZI_WORK->unk_0x0A) length = ZI_WORK->unk_0x0A;
        if ((parameters->elementCount < ZI_WORK->unk_0x140C[0] ||
             (parameters->getOptions & 0x7e) == 2) && length > parameters->elementCount) {
            length = parameters->elementCount;
        }
        while (length-- != 0) *output++ = (ziU8)*current++;
        *output++ = 0;
    }
    *output++ = 0;
    ZI_WORK->unk_0x0A = 0xff;
    return 1;
}

static ziBool Zi8ZhSignature(ziGetParam* parameters, ziBool countOnly ZI_NEED_WORK) {
    ziWChar* output = parameters->candidates;
    ziU8* current = 0;
    ziU16 copied;
    ziU8 dictionary[32];
    ziU8 engine[32];
    ziU16 dataLength;
    ziU16 engineLength;
    ziU16 length;

    Zi8LogError(100, ZI_WORK);
    parameters->letters = 0;
    dataLength = Zi8GetDataSignature(dictionary, 0x20, parameters->language, ZI_WORK);
    engineLength = Zi8GetEngineSignature(engine, ZI_WORK);
    if ((parameters->context & 0x10) != 0) {
        length = 0;
        if (dataLength != 0) length++;
        if (engineLength != 0) length++;
    } else {
        length = dataLength + engineLength;
    }
    if (parameters->firstCandidate >= length) {
        Zi8ReplaceLastError(502, ZI_WORK);
        return 0;
    }
    length = length - parameters->firstCandidate;
    if (countOnly != 0) {
        parameters->letters = length;
        ZI_WORK->unk_0x0A = 0xff;
        return 1;
    }
    if (parameters->maxCandidates < length) length = parameters->maxCandidates;
    parameters->letters = length;
    if ((parameters->context & 0x10) != 0) {
        if (parameters->firstCandidate != 0 || dataLength == 0) {
            if (parameters->firstCandidate != 0 && dataLength == 0) {
                Zi8ReplaceLastError(500, ZI_WORK);
                return 0;
            }
            current = engine;
            length = engineLength;
        } else {
            current = dictionary;
            length = dataLength;
        }
        while (length-- != 0) *output++ = (ziU8)*current++;
        *output++ = 0x20;
        if (parameters->letters == 2) {
            current = engine;
            length = engineLength;
            while (length-- != 0) *output++ = (ziU8)*current++;
            *output++ = 0x20;
        }
    } else {
        copied = 0;
        if (dataLength != 0) {
            if (parameters->firstCandidate >= dataLength) {
                length = 0;
            } else {
                length = dataLength - parameters->firstCandidate;
                current = dictionary + parameters->firstCandidate;
            }
            if (parameters->letters < length) length = parameters->letters;
            copied = length;
            while (length-- != 0) *output++ = (ziU8)*current++;
        }
        current = engine;
        if (parameters->firstCandidate >= dataLength) {
            length = dataLength + (engineLength - parameters->firstCandidate);
            current += engineLength - length;
        } else {
            length = engineLength;
        }
        if (parameters->letters - copied < length) length = parameters->letters - copied;
        while (length-- != 0) *output++ = (ziU8)*current++;
    }
    return 1;
}

ziU8 _Zi8GetCandidates(ziGetParam* parameters ZI_NEED_WORK) {
    ZiCandidateOptions options = {0};
    options.capacity = ZI_WORK->unk_0x141A;
    return Zi8GetCandidatesOrCount(parameters, &options, ZI_WORK);
}

ziU8 _Zi8CheckCandidates(ziGetParam* parameters ZI_NEED_WORK) {
    ZiCandidateOptions options = {0};
    options.capacity = ZI_WORK->unk_0x141A;
    options.flags = 1;
    return Zi8GetCandidatesOrCount(parameters, &options, ZI_WORK);
}
ziU8 Zi8LangSupported(ziU8 language, ziPtr work);
ziBool Zi8IsCharacter(ziWChar character, ziPtr work);
ziU8 Zi8GetCharInfo(ziWChar character, ziWChar* output, ziU8 capacity, ziU8 type, ziPtr work);
ziU32 Zi8GetKOcandidates(ziGetParam* parameters, ziPtr options, ziPtr work);
ziU32 Zi8GetKoreanCandidates(ziGetParam* parameters, ziPtr options, ziPtr work);
ziU32 Zi8Punctuation(ziGetParam* parameters, ziPtr options, ziPtr work);
ziU32 Zi8GetChineseCandidates(ziGetParam* parameters, ziPtr options, ziPtr work);
ziU32 Zi8Get1KeyPressCandidates(ziGetParam* parameters, ziPtr options, ziPtr work);
ziU32 Zi8Get1KeyPressSpelling(ziGetParam* parameters, ziPtr options, ziPtr work);
ziU32 Zi8GetSyllablesCandidates(ziGetParam* parameters, ziPtr options, ziPtr work);
ziU32 Zi8AlphaGetCandidates(ziGetParam* parameters, ziPtr options, ziPtr work);

ziU32 Zi8GetCandidatesOrCount(ziGetParam* parameters, ZiCandidateOptions* options ZI_NEED_WORK) {

  ziU16 characterInfo[16];
  struct {
    ziU8 savedGetMode;
    ziU8 savedElementCount;
    ziU8 convertedElementCount;
    ziBool restoreCandidates;
    ziU8 savedOptions;
    ziU16 savedCharacter;
    ziU16 lastInfoCharacter;
    ziWChar* savedElements;
    ziWChar* savedCandidates;
  } saved;
  ziU8 outputIndex;
  ziU16 error;
  unsigned int candidateCount;

  error = 0;
  saved.savedOptions = 0;
  saved.savedCandidates = 0;
  saved.restoreCandidates = 0;
  if (options->lookupMode == '\0') {
    if (((ZI_WORK->unk_0x00 == '\t') && (parameters->elementCount != 0)) &&
       (((parameters->elements[parameters->elementCount - 1] == 0xEFF8 &&
         ((ziU8)Zi8AlphaSignature(parameters,options->countOnly,ZI_WORK) != 0)) ||
        ((parameters->elements[parameters->elementCount - 1] == 0xEF04 &&
         ((ziU8)Zi8ZhSignature(parameters,options->countOnly,ZI_WORK) != 0)))))) {
      candidateCount = (unsigned int)parameters->letters;
      if (options->countOnly != '\0') {
        parameters->letters = 0;
      }
      Zi8LogError(100,ZI_WORK);
      return candidateCount;
    }
    if ((parameters->elementCount == 1) && (parameters->firstCandidate == 0)) {
      switch (parameters->language) {
      case 1:
          if ((ZI_WORK->unk_0x00 == '\0') || (ZI_WORK->countOnly == options->countOnly)) {
            switch(ZI_WORK->unk_0x00) {
            case '\0':
              if (parameters->elements[0] == 0xEF04) {
                ZI_WORK->countOnly = options->countOnly;
                ZI_WORK->unk_0x00 = '\x01';
              }
              break;
            case '\x02':
            case '\x04':
            case '\x06':
              if (parameters->elements[0] == 0xEF04) {
                ++ZI_WORK->unk_0x00;
              }
              else {
                ZI_WORK->unk_0x00 = '\0';
              }
              break;
            case '\x01':
            case '\x03':
            case '\x05':
            case '\a':
              if (parameters->elements[0] == 0xEF01) {
                ++ZI_WORK->unk_0x00;
              }
              else {
                ZI_WORK->unk_0x00 = '\0';
              }
              break;
            case '\b':
            case '\t':
              if ((parameters->elements[0] == 0xEF04) &&
                 ((ziU8)Zi8ZhSignature(parameters,options->countOnly,ZI_WORK) != 0)) {
                ZI_WORK->unk_0x00 = '\t';
                candidateCount = (unsigned int)parameters->letters;
                if (options->countOnly != '\0') {
                  parameters->letters = 0;
                }
                Zi8LogError(100,ZI_WORK);
                return candidateCount;
              }
            default:
              ZI_WORK->unk_0x00 = '\0';
            }
            if ((ZI_WORK->unk_0x00 == '\0') && (parameters->elements[0] == 0xEF04)) {
              ZI_WORK->unk_0x00 = '\x01';
            }
          }
        break;
      case 0x10:
      case 0x12:
      case 0x77:
      case 0x78:
      case 0x79:
      case 0x7A:
      case 0x7B:
      case 0x7C:
      case 0x7D:
        break;
      case 0x11:
      default:
          if ((ZI_WORK->unk_0x00 == '\0') || (ZI_WORK->countOnly == options->countOnly)) {
            switch(ZI_WORK->unk_0x00) {
            case '\0':
              if (parameters->elements[0] == 0xEFF2) {
                ZI_WORK->countOnly = options->countOnly;
                ZI_WORK->unk_0x00 = '\x01';
              }
              break;
            case '\x01':
              if (parameters->elements[0] == 0xEFF3) {
                ZI_WORK->unk_0x00 = '\x02';
              }
              else {
                ZI_WORK->unk_0x00 = '\0';
              }
              break;
            case '\x02':
              if (parameters->elements[0] == 0xEFF5) {
                ZI_WORK->unk_0x00 = '\x03';
              }
              else {
                ZI_WORK->unk_0x00 = '\0';
              }
              break;
            case '\x03':
              if (parameters->elements[0] == 0xEFF7) {
                ZI_WORK->unk_0x00 = '\x04';
              }
              else {
                ZI_WORK->unk_0x00 = '\0';
              }
              break;
            case '\x04':
              if (parameters->elements[0] == 0xEFF8) {
                ZI_WORK->unk_0x00 = '\x05';
              }
              else {
                ZI_WORK->unk_0x00 = '\0';
              }
              break;
            case '\x05':
              if (parameters->elements[0] == 0xEFF9) {
                ZI_WORK->unk_0x00 = '\x06';
              }
              else {
                ZI_WORK->unk_0x00 = '\0';
              }
              break;
            case '\x06':
              if (parameters->elements[0] == 0xEFF2) {
                ZI_WORK->unk_0x00 = '\a';
              }
              else {
                ZI_WORK->unk_0x00 = '\0';
              }
              break;
            case '\a':
              if (parameters->elements[0] == 0xEFF5) {
                ZI_WORK->unk_0x00 = '\b';
              }
              else {
                ZI_WORK->unk_0x00 = '\0';
              }
              break;
            case '\b':
            case '\t':
              if ((parameters->elements[0] == 0xEFF8) &&
                 ((ziU8)Zi8AlphaSignature(parameters,options->countOnly,ZI_WORK) != 0)) {
                ZI_WORK->unk_0x00 = '\t';
                candidateCount = (unsigned int)parameters->letters;
                if (options->countOnly != '\0') {
                  parameters->letters = 0;
                }
                Zi8LogError(100,ZI_WORK);
                return candidateCount;
              }
            default:
              ZI_WORK->unk_0x00 = '\0';
            }
            if ((ZI_WORK->unk_0x00 == '\0') && (parameters->elements[0] == 0xEFF2)) {
              ZI_WORK->unk_0x00 = '\x01';
            }
          }
        break;
      }
    }
    else if (1 < parameters->elementCount) {
      ZI_WORK->unk_0x00 = '\0';
    }
  }
  ZI_WORK->subLanguage = parameters->subLanguage;
  ZI_WORK->cangjieEnabled = Zi8GetFormatVersion(1,ZI_WORK) & 2;
  options->maxCount = ZI_WORK->unk_0x10;
  options->maxWordLength = ZI_WORK->unk_0x0A;
  ZI_WORK->unk_0x0A = -1;
  if ((ziU8)Zi8LangSupported(parameters->language,ZI_WORK) == 0) {
    Zi8LogError(0x163,ZI_WORK);
    return 0;
  }
  else {
    if (parameters->language == 0x10) {
      error = 0x2c1;
      candidateCount = 0;
    }
    else if (parameters->language == 0x12) {
      if ((parameters->elementCount == 0) || (parameters->elements[0] >= 0xeff1)) {
        candidateCount = Zi8GetKOcandidates(parameters,options,ZI_WORK);
      }
      else {
        candidateCount = Zi8GetKoreanCandidates(parameters,options,ZI_WORK);
      }
    }
    else if ((parameters->language == 1) && ((parameters->context & 8) != 0)) {
      candidateCount = Zi8Punctuation(parameters,options,ZI_WORK);
      error = 100;
    }
    else if ((parameters->language == 1) &&
            ((((parameters->getOptions & 0xbf) == 4 && (parameters->elementCount != 0)) &&
             ((ziU8)Zi8IsCharacter(parameters->elements[0],ZI_WORK) != 0)))) {
      saved.convertedElementCount = Zi8GetCharInfo(parameters->elements[0],characterInfo,0x10,1,ZI_WORK);
      if (saved.convertedElementCount == 0) {
        parameters->letters = parameters->count = parameters->unk_0x20 = 0;
        candidateCount = 0;
        error = 900;
      }
      else {
        saved.lastInfoCharacter = characterInfo[saved.convertedElementCount - 1];
        if ((saved.lastInfoCharacter >= 0xf331) && (saved.lastInfoCharacter <= 0xf335)) {
          characterInfo[saved.convertedElementCount - 1] = 0xf360;
        }
        saved.savedElements = parameters->elements;
        parameters->elements = characterInfo;
        saved.savedElementCount = parameters->elementCount;
        parameters->elementCount = saved.convertedElementCount;
        saved.savedGetMode = parameters->getMode;
        parameters->getMode = 1;
        candidateCount = Zi8GetChineseCandidates(parameters,options,ZI_WORK);
        parameters->elements = saved.savedElements;
        parameters->elementCount = saved.savedElementCount;
        parameters->getMode = saved.savedGetMode;
        parameters->count = 1;
      }
    }
    else if ((parameters->language == 1) && (parameters->getMode == 0xf)) {
      error = 0x2d0;
      candidateCount = 0;
    }
    else if ((parameters->language == 1) && ((parameters->getMode == 3 || (parameters->getMode == 4)))) {
      if ((parameters->getOptions & 0x80) != 0) {
        candidateCount = Zi8Get1KeyPressSpelling(parameters,options,ZI_WORK);
      } else if (parameters->elementCount == 0) {
        candidateCount = Zi8GetChineseCandidates(parameters,options,ZI_WORK);
      } else {
        candidateCount = Zi8Get1KeyPressCandidates(parameters,options,ZI_WORK);
      }
    }
    else if ((parameters->language == 1) &&
            ((((parameters->getMode == 7 || (parameters->getMode == 8)) || (parameters->getMode == 10)) || (parameters->getMode == 9)))) {
      if (ZI_WORK->cangjieEnabled != '\0') {
        candidateCount = Zi8GetChineseCandidates(parameters,options,ZI_WORK);
      } else {
        error = 0x708;
        candidateCount = 0;
      }
    }
    else if ((parameters->language == 1) && ((parameters->getMode == 0xb || (parameters->getMode == 0xe)))) {
      error = 0x2ee;
      candidateCount = 0;
    }
    else if (parameters->language == 1) {
      candidateCount = Zi8GetChineseCandidates(parameters,options,ZI_WORK);
      if ((((candidateCount == 0) && ((parameters->getOptions & 0x20) == 0)) && ((parameters->getMode == 1 && (parameters->elementCount != 0))))
         && (((parameters->elements[parameters->elementCount - 1] == 0xF37A ||
              (parameters->elements[parameters->elementCount - 1] == 0xF363)) ||
             (parameters->elements[parameters->elementCount - 1] == 0xF373)))) {
        saved.savedCharacter = parameters->elements[parameters->elementCount];
        parameters->elements[parameters->elementCount++] = 0xf368;
        candidateCount = Zi8GetChineseCandidates(parameters,options,ZI_WORK);
        parameters->elements[--parameters->elementCount] = saved.savedCharacter;
      }
    }
    else {
      ZI_WORK->language = parameters->language;
      if ((parameters->getOptions & 0x80) == 0) {
        saved.restoreCandidates = 1;
        saved.savedOptions = parameters->getOptions;
        saved.savedCandidates = parameters->candidates;
        parameters->getOptions |= 0x81;
        parameters->candidates = (ziWChar*)&ZI_WORK->unk_0x338;
        options->capacity = 0x100;
      }
      if (parameters->getMode == 2) {
        if ((Zi8GetTableCount(parameters->language,0x1f,ZI_WORK) & 0x200) != 0) {
          candidateCount = Zi8GetSyllablesCandidates(parameters,options,ZI_WORK);
        } else {
          error = 0x44c;
          candidateCount = 0;
        }
      }
      else {
        candidateCount = Zi8AlphaGetCandidates(parameters,options,ZI_WORK);
      }
    }
    if (saved.restoreCandidates) {
      parameters->getOptions = saved.savedOptions;
      parameters->candidates = saved.savedCandidates;
      for (outputIndex = 0; outputIndex < parameters->letters; outputIndex++) {
        parameters->candidates[outputIndex] = 0xFFF0 + outputIndex;
      }
    }
    if (error != 0) {
      Zi8LogError(error,ZI_WORK);
    }
  }
  return candidateCount;
}

void Zi8InitDupWordBuf(ziPtr __zi8_work_data) {
    ZI_WORK->unk_0x539 = 0;
}

ziBool Zi8IsDupWChar(ziWChar character ZI_NEED_WORK) {
    ziBool duplicate;
    ziU16* buffer;
    unsigned int index;
    duplicate = 0;
    buffer = ZI_WORK->unk_0x57A;
    if (ZI_WORK->unk_0x539 == 0) {
        buffer[0] = 2;
        buffer[1] = character;
        ZI_WORK->unk_0x539 = 1;
        Zi8LogError(0x8fd, ZI_WORK);
        return 0;
    }
    for (index = ZI_WORK->unk_0x539; index != 0; index--) {
        if (character == buffer[index]) {
            duplicate = 1;
            break;
        }
    }
    ZI_WORK->unk_0x539++;
    buffer[(*buffer)++] = character;
    if (*buffer > 100) {
        *buffer = 2;
        buffer[1] = character;
        ZI_WORK->unk_0x539 = 1;
    }
    Zi8LogError(100, ZI_WORK);
    return duplicate;
}

ziBool Zi8IsDupWordW(ziWChar* word, ziU8 length ZI_NEED_WORK) {
    unsigned int slot;
    ziBool duplicate = 0;
    int index;
    int character;
    if (word == 0 || length == 0) {
        Zi8LogError(300, ZI_WORK);
        return 0;
    }
    if (length > 20) {
        word += length - 20;
        length = 20;
    }
    for (index = 0; index < ZI_WORK->unk_0x539; index++) {
        slot = ZI_WORK->unk_0x53A[index];
        for (character = 0; character < length; character++) {
            if (word[character] != ((ziWChar (*)[21])ZI_WORK->unk_0x57A)[slot][character]) break;
        }
        if (character >= length && ((ziWChar (*)[21])ZI_WORK->unk_0x57A)[slot][character] == 0) {
            duplicate = 1;
            break;
        }
    }
    if (!duplicate) {
        if (ZI_WORK->unk_0x539 < 64) {
            slot = ZI_WORK->unk_0x53A[ZI_WORK->unk_0x539] = ZI_WORK->unk_0x539;
            ZI_WORK->unk_0x539++;
        } else {
            slot = ZI_WORK->unk_0x53A[0];
            for (index = 1; index < ZI_WORK->unk_0x539; index++) {
                ZI_WORK->unk_0x53A[index - 1] = ZI_WORK->unk_0x53A[index];
            }
            ZI_WORK->unk_0x53A[index - 1] = slot;
        }
    } else {
        slot = ZI_WORK->unk_0x53A[index];
        for (; index < ZI_WORK->unk_0x539 - 1; index++) {
            ZI_WORK->unk_0x53A[index] = ZI_WORK->unk_0x53A[index + 1];
        }
        ZI_WORK->unk_0x53A[index] = slot;
    }
    for (character = 0; character < length; character++) {
        ((ziWChar (*)[21])ZI_WORK->unk_0x57A)[slot][character] = word[character];
    }
    ((ziWChar (*)[21])ZI_WORK->unk_0x57A)[slot][character] = 0;
    Zi8LogError(100, ZI_WORK);
    return duplicate;
}

void Zi8Memset(ziU8* destination, ziU32 value, ziS32 count) {
    ziS32 index;
    for (index = 0; index < count; index++) destination[index] = (ziU8)value;
}

void Zi8Memcpy(ziU8* destination, ziU8* source, ziS32 count) {
    ziS32 index;
    for (index = 0; index < count; index++) destination[index] = source[index];
}

ziBool Zi8SetMaxWordLength(ziU8 length ZI_NEED_WORK) {
    ZI_WORK->unk_0x0A = length;
    return 1;
}
