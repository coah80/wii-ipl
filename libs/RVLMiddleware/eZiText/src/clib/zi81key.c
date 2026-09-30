#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>
#include <zi8clib/zi8is.h>
#include <zi8clib/zi8getc2.h>

typedef unsigned int Zi8UInt;

typedef struct {
    ziU8 keys[4];
    ziU8 unknown_04[4];
    ziU8 phoneticIndexLow;
    ziU8 flags;
    ziU16 phraseOffset;
} Zi8PhraseRecord;

typedef struct { ziU8 keyLow; ziU8 keyHigh; ziU8 code; ziU8 flags; } Zi8AltSoundRecord;



typedef struct {
    ziU8 language;
    ziU8 getMode;
    ziU8 subLanguage;
    ziU8 context;
    ziU8 getOptions;
    ziWChar* elements;
    ziU8 elementCount;
    ziWChar* currentWord;
    ziU8 wordCharCount;
    ziWChar* candidates;
    ziU8 maxCandidates;
    ziU16 firstCandidate;
    ziU8 wordCandidates;
    ziU8 count;
    ziU8 letters;
    ziU8* scratch;
    ziPtr workspace;
} Zi8OneKeyParam;

typedef struct {
    ziU8 countOnly;
    ziU8 maxSpellingLength;
    ziU8 unknown_02[10];
    ziS32 maxCount;
    ziU16 candidateBufferSize;
} Zi8OneKeyOptions;

typedef struct {
    ziU8 unknown_00[0x16];
    ziU8 phraseEnabled;
    ziU8 unknown_17[6];
    ziU8 spellingSearch;
    ziU8 unknown_1e;
    ziU8 searchFlags;
    ziU8 unknown_20[0xfda];
    ziU8 phoneticEnabled[512];
    ziU8 phoneticFilter;
    ziU8 unknown_11fb[0x211];
    ziU8 maxWordLength;
    ziU8* searchOrder;
    ziU8 unknown_1414[4];
    ziU8 searchOrderCount;
    ziU8 unknown_1419[0x6fd];
    ziU8 spellingOnly;
} Zi8OneKeyWork;

#define true 1
#define false 0
#define CONCAT11(a, b) (((unsigned short)(a) << 8) | (unsigned char)(b))
#define CONCAT11_LOW_FIRST(a, b) ((unsigned char)(a) | ((unsigned short)(b) << 8))

const ziWChar zi8ZYinitialSpelling[64] = {
    0x0000, 0x0000, 0xEFF2, 0x0000, 0x0000, 0xEFF2, 0xEFF4, 0x0000,
    0x0000, 0xEFF4, 0xEFF4, 0x0000, 0xEFF1, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0xEFF6, 0xEFF5, 0xEFF6, 0xEFF5, 0xEFF6, 0xEFF5, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xEFF2, 0x0000,
    0x0000, 0x0000, 0x0000, 0xEFF2, 0xEFF5, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0xEFF3, 0x0000, 0x0000, 0xEFF3,
    0xEFF1, 0x0000, 0x0000, 0xEFF3, 0xEFF1, 0x0000, 0x0000, 0xEFF1,
};

const ziWChar zi8ZYfinalSpelling[64][2] = {
    { 0x0000, 0x0000 },
    { 0xEFF7, 0x0000 },
    { 0xEFF7, 0x0000 },
    { 0xEFF7, 0x0000 },
    { 0xEFF9, 0x0000 },
    { 0x0000, 0x0000 },
    { 0x0000, 0x0000 },
    { 0x0000, 0x0000 },
    { 0xEFF8, 0x0000 },
    { 0xEFF8, 0x0000 },
    { 0xEFF8, 0x0000 },
    { 0xEFF8, 0x0000 },
    { 0xEFF9, 0x0000 },
    { 0xEFF9, 0x0000 },
    { 0xEFF9, 0x0000 },
    { 0xEFF9, 0x0000 },
    { 0x0000, 0x0000 },
    { 0xEFFA, 0xEFF7 },
    { 0xEFFA, 0xEFF7 },
    { 0x0000, 0x0000 },
    { 0x0000, 0x0000 },
    { 0xEFFA, 0xEFF7 },
    { 0x0000, 0x0000 },
    { 0xEFFA, 0x0000 },
    { 0xEFFA, 0xEFF8 },
    { 0x0000, 0x0000 },
    { 0xEFFA, 0xEFF8 },
    { 0xEFFA, 0xEFF8 },
    { 0xEFFA, 0xEFF9 },
    { 0xEFFA, 0xEFF9 },
    { 0xEFFA, 0xEFF9 },
    { 0xEFFA, 0xEFF9 },
    { 0x0000, 0x0000 },
    { 0xEFFA, 0xEFF7 },
    { 0xEFFA, 0xEFF7 },
    { 0x0000, 0x0000 },
    { 0x0000, 0x0000 },
    { 0xEFFA, 0xEFF7 },
    { 0x0000, 0x0000 },
    { 0xEFFA, 0x0000 },
    { 0xEFFA, 0xEFF8 },
    { 0xEFFA, 0xEFF8 },
    { 0x0000, 0x0000 },
    { 0x0000, 0x0000 },
    { 0xEFFA, 0xEFF9 },
    { 0xEFFA, 0xEFF9 },
    { 0xEFFA, 0xEFF9 },
    { 0xEFFA, 0xEFF9 },
    { 0x0000, 0x0000 },
    { 0x0000, 0x0000 },
    { 0x0000, 0x0000 },
    { 0x0000, 0x0000 },
    { 0x0000, 0x0000 },
    { 0xEFFA, 0xEFF7 },
    { 0x0000, 0x0000 },
    { 0xEFFA, 0x0000 },
    { 0x0000, 0x0000 },
    { 0x0000, 0x0000 },
    { 0x0000, 0x0000 },
    { 0x0000, 0x0000 },
    { 0xEFFA, 0xEFF9 },
    { 0x0000, 0x0000 },
    { 0xEFFA, 0xEFF9 },
    { 0xEFFA, 0xEFF9 },
};

const ziWChar zi8PYinitialSpelling[64][2] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0xEFF3, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0xEFF8, 0x0000, 0xEFF5, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0xEFF7, 0x0000, 0xEFF9, 0x0000, 0x0000, 0x0000,
    0xEFF6, 0x0000, 0xEFF9, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0xEFF9, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0xEFF2, 0x0000, 0xEFF2, 0xEFF4, 0xEFF7, 0x0000, 0xEFF7, 0xEFF4,
    0xEFF9, 0x0000, 0xEFF9, 0xEFF4, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0xEFF6, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xEFF5, 0x0000,
    0xEFF7, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0xEFF4, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xEFF5, 0x0000,
    0xEFF3, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xEFF4, 0x0000,
    0xEFF2, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xEFF7, 0x0000,
};

const ziWChar zi8PYfinalSpelling[64][4] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0xEFF4, 0xEFF2, 0xEFF6, 0x0000,
    0xEFF4, 0xEFF2, 0xEFF6, 0x0000, 0xEFF4, 0xEFF2, 0xEFF6, 0xEFF4,
    0xEFF4, 0xEFF2, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0xEFF4, 0x0000, 0x0000, 0x0000, 0xEFF4, 0xEFF3, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0xEFF4, 0xEFF8, 0x0000, 0x0000,
    0xEFF4, 0xEFF6, 0x0000, 0x0000, 0xEFF4, 0xEFF6, 0xEFF4, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0xEFF4, 0xEFF6, 0xEFF6, 0xEFF4,
    0xEFF8, 0xEFF2, 0xEFF6, 0x0000, 0xEFF8, 0xEFF2, 0xEFF6, 0xEFF4,
    0x0000, 0x0000, 0x0000, 0x0000, 0xEFF8, 0xEFF2, 0xEFF4, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0xEFF8, 0xEFF2, 0x0000, 0x0000,
    0xEFF8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0xEFF8, 0xEFF6, 0x0000, 0x0000, 0xEFF8, 0xEFF4, 0x0000, 0x0000,
    0xEFF8, 0xEFF6, 0x0000, 0x0000, 0xEFF8, 0xEFF3, 0x0000, 0x0000,
    0xEFF2, 0xEFF6, 0x0000, 0x0000, 0xEFF2, 0xEFF6, 0xEFF4, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0xEFF2, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0xEFF2, 0xEFF4, 0x0000, 0x0000,
    0xEFF2, 0xEFF6, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0xEFF6, 0xEFF6, 0xEFF4, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0xEFF6, 0xEFF8, 0x0000, 0x0000, 0xEFF6, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0xEFF3, 0xEFF6, 0x0000, 0x0000, 0xEFF3, 0xEFF6, 0xEFF4, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0xEFF3, 0xEFF7, 0x0000, 0x0000,
    0xEFF3, 0x0000, 0x0000, 0x0000, 0xEFF3, 0xEFF4, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0xEFF8, 0x0000, 0x0000, 0x0000, 0xEFF8, 0xEFF2, 0xEFF6, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

const unsigned long long Zi8SOpinyinArray = 0x0303010705000000ULL;

extern Zi8UInt Zi8Ord2Ord(ziU16, ziPtr);
extern ziU8 Zi8LangSupported(ziU8, ziPtr);
extern ziU16 Zi8GetTableCount(ziU8,ziU8,ziPtr);
extern Zi8UInt Zi8GetTableAddress(ziU8,ziU8,ziPtr);
extern void Zi8Memset();
extern int _Zi8GetCandidates();
extern void Zi8InitDupWordBuf();
extern ziU16 Zi8GetPInfo(ziU16,ziWChar *,ziU8,ziPtr);
extern ziU16 Zi8GetZInfo(ziU16,ziWChar *,ziU8,ziPtr);
extern ziBool Zi8IsDupWordW(ziWChar *,ziU8,ziPtr);
extern ziU8 Zi8GetFormatVersion(ziU8,ziPtr);
extern ziU16 Zi8Uni2Ord(ziWChar,ziPtr);
extern ziU16 Zi8GetPCode(ziU8 *,ziU8 *);
extern ziU8 Zi8MatchOEMdata(ziWChar *,ziU8,ziU8,ziWChar *,ziU16,ziU8,ziU8,ziPtr);
extern ziU8 Zi8MatchPUDdata(ziWChar *,ziU8,ziU8,ziWChar *,ziU16,ziU8,ziU8,ziPtr);
extern ziWChar Zi8Ord2Uni(ziU16,ziPtr);
extern Zi8UInt Zi8GetZHuwdPtr(ziU8 **,ziU16 *,ziPtr);
extern int Zi8GetPyPhonetic();
extern ziU8 Zi8GetBpmfPhonetic();
extern int _Zi8CheckCandidates();

Zi8UInt Zi8SpellingZY(ziU16 *output,Zi8UInt key,ziU8 includeTone)
{
  ziU16 initialIndex;
  ziU16 finalIndex;
  ziU16 tone;
  Zi8UInt length;

  length = 0;
  initialIndex = (ziU16)(((key & 0xffff) >> 9) & 0x3f);
  finalIndex = (ziU16)(((key & 0xffff) >> 3) & 0x3f);
  tone = (ziU16)(key & 7);
  if ((output[0] = zi8ZYinitialSpelling[initialIndex]) != 0) {
    length = 1;
  }
  output[length & 0xff] = zi8ZYfinalSpelling[finalIndex][0];
  output[(length & 0xff) + 1] = zi8ZYfinalSpelling[finalIndex][1];
  output[(length & 0xff) + 2] = 0;
  output[(length & 0xff) + 3] = 0;
  while (output[length & 0xff] != 0) {
    length++;
  }
  if (includeTone != '\0') {
    switch (tone) {
    case 1:
      output[(length++) & 0xff] = 0xeff1;
      break;
    case 2:
      output[(length++) & 0xff] = 0xeff2;
      break;
    case 3:
      output[(length++) & 0xff] = 0xeff3;
      break;
    case 4:
      output[(length++) & 0xff] = 0xeff4;
      break;
    case 5:
      output[(length++) & 0xff] = 0xeff5;
      break;
    }
  }
  return length;
}

Zi8UInt Zi8SpellingPY(ziU16 *output,Zi8UInt key,ziU8 includeTone)
{
  ziU16 initialIndex = (ziU16)(((key & 0xffff) >> 9) & 0x3f);
  ziU16 finalIndex = (ziU16)(((key & 0xffff) >> 3) & 0x3f);
  ziU16 tone = (ziU16)(key & 7);
  Zi8UInt length = 0;

  output[0] = zi8PYinitialSpelling[initialIndex][0];
  output[1] = zi8PYinitialSpelling[initialIndex][1];
  output[2] = 0;
  while (output[length & 0xff] != 0) {
    length++;
  }
  output[length & 0xff] = zi8PYfinalSpelling[finalIndex][0];
  output[(length & 0xff) + 1] = zi8PYfinalSpelling[finalIndex][1];
  output[(length & 0xff) + 2] = zi8PYfinalSpelling[finalIndex][2];
  output[(length & 0xff) + 3] = zi8PYfinalSpelling[finalIndex][3];
  output[(length & 0xff) + 4] = 0;
  output[(length & 0xff) + 5] = 0;
  while (output[length & 0xff] != 0) {
    length++;
  }
  if (includeTone != 0) {
    switch (tone) {
    case 1:
      output[(length++) & 0xff] = 0xeff1;
      break;
    case 2:
      output[(length++) & 0xff] = 0xeff2;
      break;
    case 3:
      output[(length++) & 0xff] = 0xeff3;
      break;
    case 4:
      output[(length++) & 0xff] = 0xeff4;
      break;
    case 5:
      output[(length++) & 0xff] = 0xeff5;
      break;
    }
  }
  return length;
}

ziU8 Zi8IsMatch1Key(ziU16 *input,Zi8UInt inputLength,Zi8UInt key,ziU8 requireFull,ziU8 usePinyin,ziU8 tone)
{
  ziU16 spelling[16];
  Zi8UInt spellingLength;

  if ((key & 0xffff) == 0) {
    return 0;
  }
  if ((inputLength & 0xff) == 0) {
    return 1;
  }
  if (usePinyin != 0) {
    spellingLength = Zi8SpellingPY(spelling,key & 0xffff,tone & 0xff);
  } else {
    spellingLength = Zi8SpellingZY(spelling,key & 0xffff,tone & 0xff);
  }
  if ((requireFull != 0) && ((inputLength & 0xff) != (spellingLength & 0xff))) {
    return 0;
  }
  if ((tone == 0) && ((inputLength & 0xff) > (spellingLength & 0xff))) {
    switch (input[(inputLength & 0xff) - 1]) {
    case 0xeff1:
    case 0xeff2:
    case 0xeff3:
    case 0xeff4:
    case 0xeff5:
      inputLength--;
      break;
    }
  }
  if ((inputLength & 0xff) > (spellingLength & 0xff)) {
    return 0;
  }
  for (spellingLength = 0; (spellingLength & 0xff) < (inputLength & 0xff); spellingLength++) {
    if (spelling[spellingLength & 0xff] != input[spellingLength & 0xff]) {
      return 0;
    }
  }
  return 1;
}

ziU8 MatchAltSound1Key(ziU16 *spelling,Zi8UInt spellingLength,Zi8UInt requireFull,Zi8AltSoundRecord *records,Zi8UInt recordCount,const ziU8 *phoneticTableBase,Zi8UInt key,Zi8UInt usePinyin,ziU8 tone,ziU8 modifierFlags,ziPtr context)
{
  int searchIndex;
  ziU8 keyHigh;
  ziU8 keyLow;
  int phoneticOffset;
  ziU16 phoneticCode;
  int midpoint;
  int recordIndex;

  Zi8LogError(100,context);
  keyHigh = (int)(key & 0xffff) >> 8;
  keyLow = key & 0xff;
  modifierFlags = modifierFlags >> 3;
  if ((recordCount & 0xffff) == 0) {
    Zi8ReplaceLastError(0x964,context);
    return 0;
  }
  else {
    searchIndex = 0;
    recordIndex = (recordCount & 0xffff) - 1;
    if ((keyHigh == records[recordIndex].keyHigh) &&
        (keyLow == records[recordIndex].keyLow)) {
      searchIndex = recordIndex;
      goto START_PROCESS;
    }
    if ((keyHigh == records[searchIndex].keyHigh) &&
        (keyLow == records[searchIndex].keyLow)) {
      goto START_PROCESS;
    }
    goto BINARY_SEARCH;
START_PROCESS:
    recordIndex = searchIndex;
PROCESS:
    do {
      if (((records[recordIndex].flags & 0xeU) == 0) ||
          ((modifierFlags & records[recordIndex].flags) != 0)) {
        phoneticOffset = (ziU16)(records[recordIndex].code |
                                  ((ziU16)(records[recordIndex].flags & 1) << 8));
        if ((((Zi8OneKeyWork*)context)->phoneticFilter == '\0') ||
            (((Zi8OneKeyWork*)context)->phoneticEnabled[(ziU16)phoneticOffset] != '\0')) {
          phoneticOffset = (ziU16)(phoneticOffset << 1);
          phoneticCode = (ziU16)(((records[recordIndex].flags & 0xf0) >> 4) |
                                  (phoneticTableBase[(ziU16)phoneticOffset] | ((ziU16)phoneticTableBase[(ziU16)phoneticOffset + 1] << 8)));
          if ((ziU8)Zi8IsMatch1Key(spelling,spellingLength & 0xff,phoneticCode,
                             requireFull & 0xff,usePinyin & 0xff,tone) != '\0') {
            return 1;
          }
        }
      }
      recordIndex = recordIndex + 1;
    } while ((((int)recordIndex < (int)((Zi8UInt)recordCount & 0xffff)) &&
              (keyHigh == records[recordIndex].keyHigh)) &&
             (keyLow == records[recordIndex].keyLow));
    recordIndex = searchIndex;
    goto BACKWARD_TEST;
BACKWARD_PROCESS:
    if (((records[recordIndex].flags & 0xeU) == 0) ||
        ((modifierFlags & records[recordIndex].flags) != 0)) {
      phoneticOffset = (ziU16)(records[recordIndex].code |
                                (((ziU16)records[recordIndex].flags & 1) << 8));
      if ((((Zi8OneKeyWork*)context)->phoneticFilter == '\0') ||
          (((Zi8OneKeyWork*)context)->phoneticEnabled[(ziU16)phoneticOffset] != '\0')) {
        phoneticOffset = (ziU16)(phoneticOffset << 1);
        phoneticCode = (ziU16)(((records[recordIndex].flags & 0xf0) >> 4) |
                                (phoneticTableBase[(ziU16)phoneticOffset] | ((ziU16)phoneticTableBase[(ziU16)phoneticOffset + 1] << 8)));
        if ((ziU8)Zi8IsMatch1Key(spelling,spellingLength & 0xff,phoneticCode,
                           requireFull & 0xff,usePinyin & 0xff,tone) != '\0') {
          return 1;
        }
      }
    }
    goto BACKWARD_TEST;
BACKWARD_TEST:
    recordIndex = recordIndex - 1;
    if ((((int)recordIndex < 0) || (keyHigh != records[recordIndex].keyHigh)) ||
        (keyLow != records[recordIndex].keyLow)) {
      return 0;
    }
    goto BACKWARD_PROCESS;

BINARY_SEARCH:
    if ((keyHigh == records[searchIndex].keyHigh) &&
        (keyLow == records[searchIndex].keyLow)) goto START_PROCESS;
    if (((ziU16)records[searchIndex].keyHigh << 8 | (ziU16)records[searchIndex].keyLow) > (int)(key & 0xffff)) return 0;
    midpoint = (searchIndex + recordIndex) / 2;
    if (midpoint == searchIndex) return 0;
    if (((ziU16)records[midpoint].keyHigh << 8 | (ziU16)records[midpoint].keyLow) >= (int)(key & 0xffff)) {
      recordIndex = midpoint;
    } else {
      searchIndex = midpoint;
      goto BINARY_SEARCH;
    }
BACKWARD_SEARCH:
    if ((keyHigh == records[recordIndex].keyHigh) &&
        (keyLow == records[recordIndex].keyLow)) {
      searchIndex = recordIndex;
      goto START_PROCESS;
    }
    if (((ziU16)records[recordIndex].keyHigh << 8 | (ziU16)records[recordIndex].keyLow) < (int)(key & 0xffff)) return 0;
    midpoint = (searchIndex + recordIndex) / 2;
    if (midpoint == searchIndex) return 0;
    if (((ziU16)records[midpoint].keyHigh << 8 | (ziU16)records[midpoint].keyLow) >= (int)(key & 0xffff)) {
      recordIndex = midpoint;
      goto BACKWARD_SEARCH;
    }
    searchIndex = midpoint;
    goto BINARY_SEARCH;
  }
}
static Zi8UInt Zi8SetFindCand(ziU8 *foundCandidates,Zi8UInt ordinal,ziPtr work)
{
  Zi8UInt result;

  ordinal = Zi8Ord2Ord(ordinal,work);
  result = (ziU8)((1 << ((int)(ordinal & 0xffff) % 8)) &
                  foundCandidates[(int)(ordinal & 0xffff) / 8]);
  foundCandidates[(int)(ordinal & 0xffff) / 8] |=
      1 << ((int)(ordinal & 0xffff) % 8);
  return result;
}

static int ZiIsSupportedPhonetic(ziU8 language,ziPtr work)
{
  if (Zi8LangSupported(language,work) != 0) {
    return 1;
  }
  switch (language) {
    case 0x79:
    case 0x7a:
    case 0x7d:
      goto LAB_group_b;
    case 0x77:
    case 0x78:
    case 0x7c:
      goto LAB_group_a;
    default:
      goto LAB_return_false;
  }
LAB_group_a:
  if ((Zi8LangSupported(0x77,work) != 0) || (Zi8LangSupported(0x78,work) != 0) ||
      (Zi8LangSupported(0x7c,work) != 0)) {
    return 1;
  }
LAB_group_b:
  if ((Zi8LangSupported(0x79,work) == 0) && (Zi8LangSupported(0x7a,work) == 0) &&
      (Zi8LangSupported(0x7d,work) == 0)) {
    goto LAB_return_false;
  }
  return 1;
LAB_return_false:
    return 0;
}

Zi8UInt Zi8Get1KeyPressSpelling(Zi8OneKeyParam *params,Zi8OneKeyOptions *options,Zi8OneKeyWork *work)
{
  ziU8 candidateCount;
  ziBool exactLength;
  ziU8 usePinyin;
  ziU8 languageMask;
  ziU8 entryLength;
  ziU8 inputLength;
  ziU8 optionsMask;
  ziU8 savedSearchCount;
  ziBool convertedInput;
  ziU8 savedSearchFlags;
  ziU16 tableCount;
  ziU16 spellingIndex;
  ziU16 phoneticIndex;
  ziU16 phoneticCount;
  ziU16 remaining;
  ziU16 character;
  ziU16 tableIndex;
  Zi8UInt totalCandidates;
  ziU8 *spellingEntry;
  ziU8 *phoneticTable;
  ziU16 *output;
  ziU8 *savedSearchOrder;
  ziU16 spellingBuffer[8];
  Zi8OneKeyParam searchParams;

  candidateCount = 0;
  totalCandidates = 0;
  optionsMask = params->getOptions;
  params->count = 0;
  params->letters = 0;
  optionsMask = optionsMask & ~0x10;
  optionsMask = optionsMask & ~0x20;
  optionsMask = optionsMask & ~0x40;
  if (options->maxSpellingLength == '\0') {
    params->count = 0;
    Zi8LogError(100,work);
    return 0;
  }
  if (((params->subLanguage & 0x80) != 0) || ((params->subLanguage & 0x40) != 0)) {
    languageMask = 1;
  }
  else if ((params->subLanguage & 8) != 0) {
    languageMask = 4;
  }
  else if (((params->subLanguage & 0x20) != 0) || ((params->subLanguage & 0x10) != 0)) {
    languageMask = 2;
  }
  else {
    languageMask = params->subLanguage;
  }
  languageMask = languageMask << 4;
  remaining = params->firstCandidate;
  if (options->countOnly != 0) {
    output = spellingBuffer;
  } else {
    output = params->candidates;
  }
  tableCount = Zi8GetTableCount(1,0xc,work);
  if (((((((languageMask & 0x10) == 0) || (params->getMode != '\x03')) ||
        ((params->context & 0x10) == 0)) ||
       ZiIsSupportedPhonetic(0x7c,work) == 0) &&
      ((((languageMask & 0x10) == 0 || (params->getMode != '\x0f')) ||
       ZiIsSupportedPhonetic(0x7b,work) == 0))) &&
     (((((languageMask & 0x20) == 0 || (params->getMode != '\x04')) ||
       (((params->context & 0x10) == 0 ||
        ZiIsSupportedPhonetic(0x7d,work) == 0))) && (tableCount == 0))))
  goto finishSpelling;
  switch (params->getMode) {
  case 3:
  case 15:
    phoneticTable = (ziU8 *)Zi8GetTableAddress(1,3,work);
    phoneticCount = Zi8GetTableCount(1,3,work);
    usePinyin = true;
    break;
  case 4:
    phoneticTable = (ziU8 *)Zi8GetTableAddress(1,4,work);
    phoneticCount = Zi8GetTableCount(1,4,work);
    usePinyin = false;
    break;
  default:
    goto finishSpelling;
  }
    inputLength = params->elementCount;
    while (inputLength != 0) {
      if (params->elements[inputLength - 1] != 0xef09) break;
      --inputLength;
    }
    if (inputLength != 0) exactLength = true;
    else exactLength = false;
    character = params->elements[0];
    if ((((inputLength == 1) && ((optionsMask & 0x81) == 0x80)) && (0xeff1 <= character)) && (character <= 0xf010)) {
      tableIndex = 0;
      if (usePinyin) {
        if (character == 0xeff2) {
          spellingBuffer[tableIndex++] = 0xf361;
        }
        if (character == 0xeff2) {
          spellingBuffer[tableIndex++] = 0xf362;
        }
        if (character == 0xeff2) {
          spellingBuffer[tableIndex++] = 0xf363;
        }
        if (character == 0xeff3) {
          spellingBuffer[tableIndex++] = 0xf364;
        }
        if (character == 0xeff3) {
          spellingBuffer[tableIndex++] = 0xf365;
        }
        if (character == 0xeff3) {
          spellingBuffer[tableIndex++] = 0xf366;
        }
        if (character == 0xeff4) {
          spellingBuffer[tableIndex++] = 0xf367;
        }
        if (character == 0xeff4) {
          spellingBuffer[tableIndex++] = 0xf368;
        }
        if (character == 0xeff4) {
          spellingBuffer[tableIndex++] = 0xf369;
        }
        if (character == 0xeff5) {
          spellingBuffer[tableIndex++] = 0xf36a;
        }
        if (character == 0xeff5) {
          spellingBuffer[tableIndex++] = 0xf36b;
        }
        if (character == 0xeff5) {
          spellingBuffer[tableIndex++] = 0xf36c;
        }
        if (character == 0xeff6) {
          spellingBuffer[tableIndex++] = 0xf36d;
        }
        if (character == 0xeff6) {
          spellingBuffer[tableIndex++] = 0xf36e;
        }
        if (character == 0xeff6) {
          spellingBuffer[tableIndex++] = 0xf36f;
        }
        if (character == 0xeff7) {
          spellingBuffer[tableIndex++] = 0xf370;
        }
        if (character == 0xeff7) {
          spellingBuffer[tableIndex++] = 0xf371;
        }
        if (character == 0xeff7) {
          spellingBuffer[tableIndex++] = 0xf372;
        }
        if (character == 0xeff7) {
          spellingBuffer[tableIndex++] = 0xf373;
        }
        if (character == 0xeff8) {
          spellingBuffer[tableIndex++] = 0xf374;
        }
        if (character == 0xeff8) {
          spellingBuffer[tableIndex++] = 0xf375;
        }
        if (character == 0xeff8) {
          spellingBuffer[tableIndex++] = 0xf376;
        }
        if (character == 0xeff9) {
          spellingBuffer[tableIndex++] = 0xf377;
        }
        if (character == 0xeff9) {
          spellingBuffer[tableIndex++] = 0xf378;
        }
        if (character == 0xeff9) {
          spellingBuffer[tableIndex++] = 0xf379;
        }
        if (character == 0xeff9) {
          spellingBuffer[tableIndex++] = 0xf37a;
        }
      } else {
        if (character == 0xeff1) {
          spellingBuffer[tableIndex++] = 0xf305;
        }
        if (character == 0xeff1) {
          spellingBuffer[tableIndex++] = 0xf306;
        }
        if (character == 0xeff1) {
          spellingBuffer[tableIndex++] = 0xf307;
        }
        if (character == 0xeff1) {
          spellingBuffer[tableIndex++] = 0xf308;
        }
        if (character == 0xeff2) {
          spellingBuffer[tableIndex++] = 0xf309;
        }
        if (character == 0xeff2) {
          spellingBuffer[tableIndex++] = 0xf30a;
        }
        if (character == 0xeff2) {
          spellingBuffer[tableIndex++] = 0xf30b;
        }
        if (character == 0xeff2) {
          spellingBuffer[tableIndex++] = 0xf30c;
        }
        if (character == 0xeff3) {
          spellingBuffer[tableIndex++] = 0xf30d;
        }
        if (character == 0xeff3) {
          spellingBuffer[tableIndex++] = 0xf30e;
        }
        if (character == 0xeff3) {
          spellingBuffer[tableIndex++] = 0xf30f;
        }
        if (character == 0xeff4) {
          spellingBuffer[tableIndex++] = 0xf310;
        }
        if (character == 0xeff4) {
          spellingBuffer[tableIndex++] = 0xf311;
        }
        if (character == 0xeff4) {
          spellingBuffer[tableIndex++] = 0xf312;
        }
        if (character == 0xeff5) {
          spellingBuffer[tableIndex++] = 0xf313;
        }
        if (character == 0xeff5) {
          spellingBuffer[tableIndex++] = 0xf314;
        }
        if (character == 0xeff5) {
          spellingBuffer[tableIndex++] = 0xf315;
        }
        if (character == 0xeff5) {
          spellingBuffer[tableIndex++] = 0xf316;
        }
        if (character == 0xeff6) {
          spellingBuffer[tableIndex++] = 0xf317;
        }
        if (character == 0xeff6) {
          spellingBuffer[tableIndex++] = 0xf318;
        }
        if (character == 0xeff6) {
          spellingBuffer[tableIndex++] = 0xf319;
        }
        if (character == 0xeff7) {
          spellingBuffer[tableIndex++] = 0xf31a;
        }
        if (character == 0xeff7) {
          spellingBuffer[tableIndex++] = 0xf31b;
        }
        if (character == 0xeff7) {
          spellingBuffer[tableIndex++] = 0xf31c;
        }
        if (character == 0xeff7) {
          spellingBuffer[tableIndex++] = 0xf31d;
        }
        if (character == 0xeff8) {
          spellingBuffer[tableIndex++] = 0xf31e;
        }
        if (character == 0xeff8) {
          spellingBuffer[tableIndex++] = 0xf31f;
        }
        if (character == 0xeff8) {
          spellingBuffer[tableIndex++] = 0xf320;
        }
        if (character == 0xeff8) {
          spellingBuffer[tableIndex++] = 0xf321;
        }
        if (character == 0xeff9) {
          spellingBuffer[tableIndex++] = 0xf322;
        }
        if (character == 0xeff9) {
          spellingBuffer[tableIndex++] = 0xf323;
        }
        if (character == 0xeff9) {
          spellingBuffer[tableIndex++] = 0xf324;
        }
        if (character == 0xeff9) {
          spellingBuffer[tableIndex++] = 0xf325;
        }
        if (character == 0xeff9) {
          spellingBuffer[tableIndex++] = 0xf326;
        }
        if (character == 0xeffa) {
          spellingBuffer[tableIndex++] = 0xf327;
        }
        if (character == 0xeffa) {
          spellingBuffer[tableIndex++] = 0xf328;
        }
        if (character == 0xeffa) {
          spellingBuffer[tableIndex++] = 0xf329;
        }
      }
      for (spellingIndex = 0; spellingIndex < tableIndex; spellingIndex++) {
        if (remaining != 0) {
          remaining--;
        } else {
          totalCandidates++;
          if (options->countOnly == '\0') {
            *output++ = spellingBuffer[spellingIndex];
            *output++ = 0;
            candidateCount++;
          }
          else if ((int)totalCandidates >= options->maxCount) goto finishSpelling;
          if (candidateCount >= params->maxCandidates) goto finishSpelling;
        }
      }
    }
    else {
      if ((((((languageMask & 0x10) != 0) && (params->getMode == '\x03')) &&
           (((params->context & 0x10) != 0 &&
            ZiIsSupportedPhonetic(0x7c,work) != 0))) ||
          ((((languageMask & 0x10) != 0 && (params->getMode == '\x0f')) &&
           ZiIsSupportedPhonetic(0x7b,work) != 0))) ||
         (((((languageMask & 0x20) != 0 && (params->getMode == '\x04')) &&
           ((params->context & 0x10) != 0)) &&
          ZiIsSupportedPhonetic(0x7d,work) != 0))) {
        savedSearchOrder = work->searchOrder;
        savedSearchCount = work->searchOrderCount;
        convertedInput = false;
        savedSearchFlags = work->searchFlags;
        Zi8Memset(&searchParams,0,0x2c);
        searchParams.getMode = 0;
        searchParams.subLanguage = 0x80;
        searchParams.context = 1;
        searchParams.getOptions = 0x81;
        if (((params->getOptions & 0x10) != 0) || ((params->getOptions & 0xe) == 2)) {
          searchParams.getOptions |= 2;
        }
        searchParams.elements = params->elements;
        searchParams.elementCount = params->elementCount;
        searchParams.candidates = params->candidates;
        searchParams.maxCandidates = params->maxCandidates;
        searchParams.firstCandidate = params->firstCandidate;
        if (params->getMode == '\x0f') {
          searchParams.language = ZI8_LANG_SP2;
        }
        else if (params->getMode == '\x03') {
          searchParams.language = ZI8_LANG_PY2;
          if (((params->context & 0xf) == 1) || ((params->context & 0xf) == 3)) {
            if (Zi8LangSupported(0x77,work) != 0) {
              searchParams.language = ZI8_LANG_PYP;
            } else {
              if (Zi8LangSupported(0x78,work) != 0) {
                searchParams.language = ZI8_LANG_PYS;
              }
            }
          }
          if (((params->context & 0xf) == 1) || ((params->context & 0xf) == 5)) {
            if (Zi8LangSupported(0x78,work) != 0) {
              searchParams.subLanguage = ZI8_LANG_PYS;
            } else {
              if (Zi8LangSupported(0x77,work) != 0) {
                searchParams.subLanguage = ZI8_LANG_PYP;
              }
            }
          }
          if ((searchParams.language == ZI8_LANG_PY2) && (searchParams.subLanguage != 0x80)) {
            searchParams.language = searchParams.subLanguage;
            searchParams.subLanguage = 0x80;
          }
          for (tableIndex = 0; tableIndex < params->elementCount; tableIndex++) {
            if (params->elements[(Zi8UInt)tableIndex] == 0xf360) {
              params->elements[(Zi8UInt)tableIndex] = 0x27;
              convertedInput = true;
            }
          }
        }
        else {
          searchParams.language = ZI8_LANG_ZY2;
          if (((params->context & 0xf) == 1) || ((params->context & 0xf) == 3)) {
            if (Zi8LangSupported(0x79,work) != 0) {
              searchParams.language = ZI8_LANG_ZYP;
            } else {
              if (Zi8LangSupported(0x7a,work) != 0) {
                searchParams.language = ZI8_LANG_ZYS;
              }
            }
          }
          if (((params->context & 0xf) == 1) || ((params->context & 0xf) == 5)) {
            if (Zi8LangSupported(0x7a,work) != 0) {
              searchParams.subLanguage = ZI8_LANG_ZYS;
            } else {
              if (Zi8LangSupported(0x79,work) != 0) {
                searchParams.subLanguage = ZI8_LANG_ZYP;
              }
            }
          }
          if ((searchParams.language == ZI8_LANG_ZY2) && (searchParams.subLanguage != 0x80)) {
            searchParams.language = searchParams.subLanguage;
            searchParams.subLanguage = 0x80;
          }
          for (tableIndex = 0; tableIndex < params->elementCount; tableIndex++) {
            if (params->elements[(Zi8UInt)tableIndex] == 0x27) {
              params->elements[(Zi8UInt)tableIndex] = 0xf360;
              convertedInput = true;
            }
          }
        }
        if (params->elementCount == '\x01') {
          searchParams.subLanguage = 0x80;
          searchParams.getOptions = searchParams.getOptions | 2;
        }
        if ((params->getMode == '\x0f') && ((params->context & 0x10) == 0)) {
          Zi8SetMaxWordLength(2,work);
        }
        work->searchOrder = (ziU8 *)&Zi8SOpinyinArray;
        work->searchOrderCount = 5;
        if ((((params->subLanguage & 7) != 0) || ((params->subLanguage & 0x40) != 0)) ||
           ((params->subLanguage & 0x20) != 0)) {
          work->spellingOnly = 1;
        }
        work->searchFlags = 0;
        work->spellingSearch = 1;
        totalCandidates = (ziU8)_Zi8GetCandidates(&searchParams,work);
        work->spellingSearch = 0;
        work->searchFlags = savedSearchFlags;
        work->searchOrder = savedSearchOrder;
        work->searchOrderCount = savedSearchCount;
        params->count = searchParams.count;
        work->spellingOnly = 0;
        if (convertedInput) {
          if (params->getMode == '\x03') {
            for (tableIndex = 0; tableIndex < params->elementCount; tableIndex++) {
              if (params->elements[(Zi8UInt)tableIndex] == 0x27) {
                params->elements[(Zi8UInt)tableIndex] = 0xf360;
              }
            }
          }
          else {
            for (tableIndex = 0; tableIndex < params->elementCount; tableIndex++) {
              if (params->elements[(Zi8UInt)tableIndex] == 0xf360) {
                params->elements[(Zi8UInt)tableIndex] = 0x27;
              }
            }
          }
        }
        if ((options->countOnly == '\0') && (params->getMode == '\x03')) {
          for (tableIndex = 0; tableIndex < params->count;) {
            while (*output != 0) {
              if (*output != 0x27) {
                *output |= 0xf300;
                output++;
              } else {
                *output++ = 0xf360;
              }
            }
            tableIndex++;
            output++;
          }
        }
        Zi8LogError(100,work);
        return totalCandidates;
      }
      if (params->getMode == '\x0f') {
        Zi8LogError(1000,work);
        return 0;
      }
      Zi8InitDupWordBuf(work);
      for (;;) {
        if (tableCount == 0) break;
        spellingEntry = (ziU8 *)Zi8GetTableAddress(1,0xc,work);
        for (tableIndex = 0; tableIndex < tableCount; tableIndex++) {
          if ((*spellingEntry & languageMask) != 0) {
            if (usePinyin) entryLength = *spellingEntry & 0xf;
            else entryLength = spellingEntry[1] & 0xf;
            if (exactLength) {
              if (entryLength != inputLength) goto nextSpelling;
            } else {
              if (inputLength != 0 && entryLength <= inputLength) goto nextSpelling;
            }
            phoneticIndex = (((ziU16)spellingEntry[1] & 0xf0) << 4) | spellingEntry[2];
            character = phoneticTable[phoneticIndex * 2] |
                        ((ziU16)phoneticTable[phoneticIndex * 2 + 1] << 8);
            if (usePinyin) phoneticIndex = (ziU8)Zi8SpellingPY(output,character,0);
            else phoneticIndex = (ziU8)Zi8SpellingZY(output,character,0);
            for (spellingIndex = 0; spellingIndex < inputLength; spellingIndex++) {
              if (params->elements[spellingIndex] < 0xf305 &&
                  (ziU16)output[spellingIndex] != params->elements[spellingIndex]) break;
            }
            if (inputLength == 0 || spellingIndex >= inputLength) {
              if (usePinyin) phoneticIndex = (ziU8)Zi8GetPInfo(character,output,8,work);
              else phoneticIndex = (ziU8)Zi8GetZInfo(character,output,8,work);
              if (phoneticIndex != 0) {
                for (spellingIndex = 0; spellingIndex < inputLength; spellingIndex++) {
                  if (params->elements[spellingIndex] >= 0xf305 &&
                      (ziU16)output[spellingIndex] != params->elements[spellingIndex]) break;
                }
                if (inputLength == 0 || spellingIndex >= inputLength) {
                  if (phoneticIndex > options->maxSpellingLength) {
                    phoneticIndex = options->maxSpellingLength;
                    output[phoneticIndex] = 0;
                  }
                  if (((params->getOptions & 0x10) != 0 ||
                       (params->getOptions & 0xe) == 2 ||
                       work->maxWordLength > params->elementCount) &&
                      params->elementCount != 0 && phoneticIndex > params->elementCount) {
                    phoneticIndex = params->elementCount;
                    output[phoneticIndex] = 0;
                  }
                  if (Zi8IsDupWordW(output,(ziU8)phoneticIndex,work) == 0) {
                    if (remaining == 0) {
                      totalCandidates++;
                      if (options->countOnly == 0) {
                        output += phoneticIndex + 1;
                        candidateCount++;
                      } else if ((int)totalCandidates >= options->maxCount) goto finishSpelling;
                      if (candidateCount >= params->maxCandidates) goto finishSpelling;
                    } else {
                      remaining--;
                    }
                  }
                }
              }
            }
          }
nextSpelling:
          spellingEntry += 3;
        }
        if (exactLength == false) break;
        exactLength = false;
      }
    }
finishSpelling:
  params->count = candidateCount;
  Zi8LogError(100,work);
  return totalCandidates;
}

int Zi8Get1KeyPressCandidates(Zi8OneKeyParam *params,Zi8OneKeyOptions *options,Zi8OneKeyWork *work)
{
  ziU16 wordBuffer [64];
  ziU16 spelling [8];
  ziU8 *syllableTable;
  ziU8 *alternateTable;
  ziU8 *ordinalTable;
  ziU8 *characterSetTable;
  ziU8 *phoneticTable;
  ziU8 *phraseTable;
  ziU8 keyValues[4];
  ziU8 keyMasks[4];
  int totalCandidates;
  ziU16 *output;
  int outputIndex;
  int outputLimit;
  ziU8 *phraseEntries;
  ziU16 *currentWord;
  ziU8 *entryCursor;
  ziU8 *userEntries;
  int duplicateIndex;
  ziU16 alternateCount;
  ziU16 ordinalCount;
  ziU16 phoneticMask;
  ziU16 remaining;
  ziU16 ordinal;
  ziU16 tableCursor;
  ziU16 previousCharacter;
  ziU16 tableIndex;
  ziU16 candidateOrdinal;
  ziU16 candidateCharacter;
  ziU16 characterMask;
  ziU16 phoneticCode;
  ziU16 firstOrdinal;
  ziU16 phraseCharacter;
  ziU16 phoneticCount;
  ziU16 ordinalIndex;
  ziU16 phraseOrdinal;
  ziU16 userCount;
  ziU16 userOrdinal;
  ziU16 userCharacter;
  ziU16 unicodeCharacter;
  int index;

  ziU8 languageMask;
  ziU8 characterSet;
  ziU8 inputLength;
  ziU8 inputLimit;
  ziU8 tone;
  ziU8 elementIndex;
  ziU8 keyIndex;
  ziU8 candidateCount;
  ziU8 matchFull;
  ziU8 includeTone;
  ziU8 trackDuplicates;
  ziU8 entryFlags;
  ziU8 phoneticLength;
  ziU8 wordLength;
  ziU8 optionsMask;
  ziU8 requireFull;
  ziU8 prefixSearch;
  ziU8 alternateSearch;
  ziU8 emitWords;
  ziU8 nibble;
  ziU8 validPhonetic;
  ziU8 entryRemaining;
  ziU8 contextIndex;
  ziU8 contextRemaining;

  ordinalTable = 0;
  characterSetTable = 0;
  languageMask = 0;
  characterSet = 0;
  tableCursor = 0;
  candidateCount = 0;
  totalCandidates = 0;
  previousCharacter = 0;
  matchFull = 0;
  includeTone = 1;
  trackDuplicates = false;
  wordLength = 0;
  optionsMask = params->getOptions;
  emitWords = false;
  output = params->candidates;
  outputIndex = 0;
  outputLimit = options->candidateBufferSize - 0x40;
  requireFull = optionsMask & 0x40;
  prefixSearch = optionsMask & 0x10;
  alternateSearch = optionsMask & 0x20;
  optionsMask = optionsMask & ~0x10;
  optionsMask = optionsMask & ~0x20;
  optionsMask = optionsMask & ~0x40;
  if ((params->subLanguage & 0x80) != 0 || (params->subLanguage & 0x40) != 0) {
    languageMask = 1;
  } else if ((params->subLanguage & 8) != 0) {
    languageMask = 4;
  } else if ((params->subLanguage & 0x20) != 0 || (params->subLanguage & 0x10) != 0) {
    languageMask = 2;
  }
  if (languageMask != 0) {
    if (Zi8GetFormatVersion(1,work) >= 4) characterSetTable = (ziU8 *)Zi8GetTableAddress(1,0x15,work);
    else characterSetTable = 0;
    if (characterSetTable != 0) characterSet = params->subLanguage;
    switch (languageMask) {
    case 1:
      if ((params->subLanguage & 0x40) != 0 || (Zi8GetZHCharSet(work) & 1) != 0) characterSetTable = 0;
      break;
    case 2:
      if ((params->subLanguage & 0x10) != 0 || (Zi8GetZHCharSet(work) & 0x10) != 0) characterSetTable = 0;
      break;
    case 4:
      if ((params->subLanguage & 0x10) != 0) characterSetTable = 0;
      break;
    default:
      break;
    }
  } else {
    languageMask = params->subLanguage;
  }
  languageMask = languageMask << 4;
  remaining = params->firstCandidate;
  params->count = 0;
  params->letters = 0;
  inputLength = params->elementCount;
  if (inputLength != 0) {
    while (inputLength != 0) {
      if (params->elements[(inputLength - 1)] != 0xef09) {
        break;
      }
      inputLength--;
    }
  }
  index = inputLength;
  if (inputLength != 0) {
    inputLimit = index++;
  }
  else {
    inputLimit = 0;
  }
  for (keyIndex = 0; keyIndex < 4; keyIndex++) {
    keyMasks[keyIndex] = keyValues[keyIndex] = 0;
  }
  for (keyIndex = 1; index < inputLength && (int)keyIndex / 2 < 4;) {
    switch(params->elements[index]) {
    case 0xef02:
      nibble = 0;
      break;
    case 0xef04:
      nibble = 1;
      break;
    case 0xef01:
      nibble = 2;
      break;
    case 0xef07:
      nibble = 3;
      break;
    case 0xef06:
      nibble = 4;
      break;
    case 0xef03:
      nibble = 5;
      break;
    case 0xef05:
      nibble = 6;
      break;
    case 0xef08:
      nibble = 7;
      break;
    case 0xef0b:
      nibble = 8;
      break;
    case 0xef0a:
      nibble = 4;
      break;
    default:
      nibble = 0;
    }
    if ((keyIndex & 1) != 0) {
      keyValues[(keyIndex >> 1)] |= nibble;
      if (params->elements[index] == 0xef0b) {
        keyMasks[keyIndex >> 1] |= 8;
      }
      else if (params->elements[index] == 0xef0a) {
        keyMasks[keyIndex >> 1] |= 4;
      }
      else if (params->elements[index] != 0xef00) {
        keyMasks[keyIndex >> 1] |= 7;
      }
    } else {
      keyValues[(keyIndex >> 1)] |= nibble << 4;
      if (params->elements[index] == 0xef0b) {
        keyMasks[keyIndex >> 1] |= 0x80;
      }
      else if (params->elements[index] == 0xef0a) {
        keyMasks[keyIndex >> 1] |= 0x40;
      }
      else if (params->elements[index] != 0xef00) {
        keyMasks[keyIndex >> 1] |= 0x70;
      }
    }
    keyIndex++;
    index++;
  }
  keyIndex--;
  syllableTable = (ziU8 *)Zi8GetTableAddress(1,0,work);
  ordinalCount = Zi8GetTableCount(1,0,work);
  alternateTable = (ziU8 *)Zi8GetTableAddress(1,5,work);
  phoneticMask = Zi8GetTableCount(1,5,work);
  if ((params->context & 0x40) != 0 && Zi8GetFormatVersion(1,work) >= 1) {
    characterMask = Zi8GetTableCount(1,0xf,work);
    if (characterMask != 0) ordinalCount = characterMask;
  }
  if (((params->context & 0x80) != 0) && (params->scratch != 0)) {
    Zi8Memset(params->scratch,0,(ordinalCount + 7) / 8);
    trackDuplicates = true;
  }
  if ((params->context & 0x10) != 0) {
    if (output == 0) goto finishCandidates;
    Zi8InitDupWordBuf(work);
    emitWords = true;
  }
  switch (params->getMode) {
  case 3:
    phoneticTable = (ziU8 *)Zi8GetTableAddress(1,3,work);
    alternateCount = Zi8GetTableCount(1,3,work);
    tone = 1;
    break;
  case 4:
    phoneticTable = (ziU8 *)Zi8GetTableAddress(1,4,work);
    alternateCount = Zi8GetTableCount(1,4,work);
    tone = 0;
    break;
  default:
    goto finishCandidates;
  }
  if ((params->context & 0xf) == 2) {
    ordinalTable = (ziU8 *)Zi8GetTableAddress(1,8,work);
    tableCursor = Zi8GetTableCount(1,8,work);
  }
  else if ((params->context & 0xf) == 4) {
    ordinalTable = (ziU8 *)Zi8GetTableAddress(1,9,work);
    tableCursor = Zi8GetTableCount(1,9,work);
  }
  if (8 < inputLimit) {
    params->wordCandidates = 0;
    goto finishCandidates;
  }
  for (index = 0; index < (int)(Zi8UInt)inputLimit; index++) {
    spelling[index] = params->elements[index];
  }
  work->phoneticFilter = 0;
  if (inputLimit != 0) {
    validPhonetic = false;
    work->phoneticFilter = 1;
    Zi8Memset(work->phoneticEnabled,0,0x200);
    for (index = 0; index < alternateCount; index++) {
      phoneticCode = phoneticTable[index * 2] | ((ziU16)phoneticTable[index * 2 + 1] << 8);
      if ((ziU8)Zi8IsMatch1Key(spelling,inputLimit,phoneticCode,(ziU8)0,tone,(ziU8)0) != 0) {
        work->phoneticEnabled[index] = 1;
        validPhonetic = true;
      }
      else {
        work->phoneticEnabled[index] = 0;
      }
    }
    if (!validPhonetic) goto finishCandidates;
  }
  if ((((options->countOnly == '\0') || (optionsMask == 5)) &&
      ((optionsMask != 5 || (params->wordCharCount != '\0')))) &&
     ((params->wordCharCount == '\0' ||
      Zi8IsCharacter(params->currentWord[0],work) != 0))) {
    phoneticLength = 0;
    while (Zi8MatchOEMdata(params->currentWord,params->wordCharCount,1,
                           wordBuffer,0x40,0,phoneticLength,work) != 0) {
      phoneticLength = 1;
      candidateCharacter = wordBuffer[params->wordCharCount];
      if (candidateCharacter == previousCharacter) continue;
      if (Zi8IsCharacter(candidateCharacter,work) == 0) continue;
      previousCharacter = candidateCharacter;
      candidateOrdinal = Zi8Uni2Ord(candidateCharacter,work);
      phraseTable = syllableTable + candidateOrdinal * 12;
      entryFlags = false;
      if (keyIndex != 0) {
        for (index = 0; index < 4; index++) {
          if (keyValues[index] != (keyMasks[index] & phraseTable[index])) {
            entryFlags = true;
            break;
          }
        }
      }
      if (entryFlags) continue;
      elementIndex = Zi8IsMatch1Key(spelling,inputLimit,
                       Zi8GetPCode(phoneticTable,phraseTable),matchFull,tone,includeTone);
      if (elementIndex == 0 && requireFull == 0 && (*phraseTable & 0x80) != 0) {
        elementIndex = MatchAltSound1Key(spelling,inputLimit,matchFull,
                        (Zi8AltSoundRecord *)alternateTable,phoneticMask,phoneticTable,
                        candidateOrdinal,tone,includeTone,languageMask,work);
      }
      if (elementIndex == 0) continue;
      if (!emitWords) {
        if (trackDuplicates && Zi8SetFindCand(params->scratch,candidateOrdinal,work) != 0) continue;
        for (index = 0; index < candidateCount; index++) {
          if (candidateCharacter == output[index]) break;
        }
        if (index < candidateCount) continue;
      } else {
        wordLength = 0;
        for (index = params->wordCharCount; wordBuffer[index] != 0;) {
          index++;
          wordLength++;
        }
        if (prefixSearch != 0 || params->elementCount != 0) wordLength = 1;
        if (Zi8IsDupWordW(wordBuffer + params->wordCharCount,wordLength,work) != 0) continue;
        wordBuffer[params->wordCharCount + wordLength] = 0;
      }
      if (optionsMask == 5) {
        totalCandidates++;
        if (totalCandidates >= options->maxCount) goto finishCandidates;
      } else if (remaining == 0) {
        totalCandidates++;
        candidateCount++;
        if (emitWords) {
          for (index = params->wordCharCount; wordBuffer[index] != 0; index++) {
            output[outputIndex++] = wordBuffer[index];
          }
          output[outputIndex++] = 0x20;
        } else {
          output[outputIndex++] = candidateCharacter;
        }
        if (candidateCount >= params->maxCandidates || outputIndex > outputLimit) {
          params->wordCandidates = candidateCount;
          goto finishCandidates;
        }
      } else {
        remaining--;
      }
    }
  }
  if ((((options->countOnly == '\0') || (optionsMask == 5)) && (params->wordCharCount != '\0')) &&
     Zi8IsCharacter(params->currentWord[0],work) != 0) {
    phoneticLength = 0;
    while ((index = Zi8MatchPUDdata(params->currentWord,params->wordCharCount,1,
                                   wordBuffer,0x40,0,phoneticLength,work)) != 0) {
      phoneticLength = 1;
      wordBuffer[index] = 0;
      candidateCharacter = wordBuffer[params->wordCharCount];
      if (candidateCharacter == previousCharacter) continue;
      previousCharacter = candidateCharacter;
      candidateOrdinal = Zi8Uni2Ord(candidateCharacter,work);
      phraseTable = syllableTable + candidateOrdinal * 12;
      entryFlags = false;
      if (keyIndex != 0) {
        for (index = 0; index < 4; index++) {
          if (keyValues[index] != (keyMasks[index] & phraseTable[index])) {
            entryFlags = true;
            break;
          }
        }
      }
      if (entryFlags) continue;
      elementIndex = Zi8IsMatch1Key(spelling,inputLimit,
                       Zi8GetPCode(phoneticTable,phraseTable),matchFull,tone,includeTone);
      if (elementIndex == 0 && requireFull == 0 && (*phraseTable & 0x80) != 0) {
        elementIndex = MatchAltSound1Key(spelling,inputLimit,matchFull,
                        (Zi8AltSoundRecord *)alternateTable,phoneticMask,phoneticTable,
                        candidateOrdinal,tone,includeTone,languageMask,work);
      }
      if (elementIndex == 0) continue;
      if (!emitWords) {
        if (trackDuplicates && Zi8SetFindCand(params->scratch,candidateOrdinal,work) != 0) continue;
        for (index = 0; index < candidateCount; index++) {
          if (candidateCharacter == output[index]) break;
        }
        if (index < candidateCount) continue;
      } else {
        wordLength = 0;
        for (index = params->wordCharCount; wordBuffer[index] != 0;) {
          index++;
          wordLength++;
        }
        if (prefixSearch != 0 || params->elementCount != 0) wordLength = 1;
        if (Zi8IsDupWordW(wordBuffer + params->wordCharCount,wordLength,work) != 0) continue;
        wordBuffer[params->wordCharCount + wordLength] = 0;
      }
      if (optionsMask == 5) {
        totalCandidates++;
        if (totalCandidates >= options->maxCount) goto finishCandidates;
      } else if (remaining == 0) {
        totalCandidates++;
        candidateCount++;
        if (emitWords) {
          for (index = params->wordCharCount; wordBuffer[index] != 0; index++) {
            output[outputIndex++] = wordBuffer[index];
          }
          output[outputIndex++] = 0x20;
        } else {
          output[outputIndex++] = candidateCharacter;
        }
        if (candidateCount >= params->maxCandidates || outputIndex > outputLimit) {
          params->wordCandidates = candidateCount;
          goto finishCandidates;
        }
      } else {
        remaining--;
      }
    }
  }
  if ((((options->countOnly == '\0') || (optionsMask == 5)) && (tableCursor == 0)) &&
     ((params->wordCharCount != '\0' &&
      Zi8IsCharacter(params->currentWord[0],work) != 0))) {
    firstOrdinal = Zi8Uni2Ord(params->currentWord[0],work);
    if (firstOrdinal != 0xffff) {
      phraseTable = syllableTable + (Zi8UInt)firstOrdinal * 0xc;
      phraseEntries = (ziU8 *)Zi8GetTableAddress(1,1,work);
      phraseEntries += ((phraseTable[9] & 0xf) << 16) | (phraseTable[11] | (phraseTable[10] << 8));
      if (work->phraseEnabled != '\0') {
        switch (*phraseEntries & 7) {
        case 2: phraseEntries += 2; break;
        case 3:
        case 4: phraseEntries += 3; break;
        case 5: phraseEntries += 4; break;
        default: phraseEntries++; break;
        }
      }
      if ((*phraseEntries & 0x80) != 0) {
        entryRemaining = 0;
        phraseEntries = phraseEntries + ((int)(*phraseEntries & 0x7f) >> 4) + 1;
      } else {
        entryRemaining = 0x80;
      }
      while ((entryRemaining & 0x80) == 0) {
        entryRemaining = *phraseEntries++;
        contextIndex = entryRemaining & 0xf;
        if ((entryRemaining & languageMask) == 0) {
          for (; contextIndex != 0; contextIndex--) {
            for (phraseEntries++; (*phraseEntries & 0x80) == 0; phraseEntries += 2) {
            }
            phraseEntries++;
          }
        }
        for (; contextIndex != 0; contextIndex--) {
          phoneticCount = 0;
          currentWord = params->currentWord;
          contextRemaining = params->wordCharCount - 1;
          while (contextRemaining != 0) {
            phoneticCount = ((ziU16)phraseEntries[1] << 8) | *phraseEntries;
            phraseEntries += 2;
            if ((phoneticCount & 0x8000) != 0) break;
            if (*++currentWord != Zi8Ord2Uni(phoneticCount,work)) break;
            contextRemaining--;
          }
          if (contextRemaining == 0) {
            phoneticCount = ((ziU16)phraseEntries[1] << 8) | *phraseEntries;
            entryCursor = phraseEntries;
            phraseEntries += 2;
            if (characterSetTable != 0) {
              index = 0;
              while (true) {
                phraseCharacter = ((ziU16)entryCursor[index + 1] << 8) | entryCursor[index];
                if ((characterSet & characterSetTable[phraseCharacter & 0x7fff]) == 0) {
                  phraseCharacter = 0;
                  break;
                }
                if ((phraseCharacter & 0x8000) != 0) break;
                index += 2;
              }
              if ((phraseCharacter & 0x8000) == 0) goto nextPhrase;
            }
            phraseCharacter = phoneticCount & 0x7fff;
                firstOrdinal = Zi8Ord2Uni(phraseCharacter,work);
            phraseTable = syllableTable + (Zi8UInt)phraseCharacter * 0xc;
            if (keyIndex != 0) {
              for (index = 0; index < 4; index++) {
                if (keyValues[index] != (keyMasks[index] & phraseTable[index])) goto nextPhrase;
              }
            }
            entryFlags = false;
            if (work->phoneticFilter != 0) {
              tableIndex = (ziU16)phraseTable[8] << 1 | (((ziU16)phraseTable[9] & 0x80) >> 7);
              if (work->phoneticEnabled[tableIndex] == 0) entryFlags = true;
            }
            if (!entryFlags) {
              elementIndex = Zi8IsMatch1Key(spelling,inputLimit,Zi8GetPCode(phoneticTable,phraseTable),matchFull,tone,includeTone);
            } else {
              elementIndex = 0;
            }
            if (((elementIndex == '\0') && (requireFull == 0)) && ((*phraseTable & 0x80) != 0)) {
              elementIndex = MatchAltSound1Key(spelling,inputLimit,matchFull,(Zi8AltSoundRecord *)alternateTable,phoneticMask,phoneticTable,
                                            phraseCharacter,tone,includeTone,languageMask,work);
            }
            if (elementIndex == 0) goto nextPhrase;
            if (!emitWords) {
              if (trackDuplicates && Zi8SetFindCand(params->scratch,phraseCharacter,work) != 0) goto nextPhrase;
              for (index = 0; index < candidateCount; index++) {
                if (firstOrdinal == output[index]) goto nextPhrase;
              }
            } else {
              wordLength = 0;
              do {
                phraseCharacter = ((ziU16)entryCursor[1] << 8) | *entryCursor;
                entryCursor += 2;
                output[outputIndex + wordLength++] = Zi8Ord2Uni(phraseCharacter & 0x7fff,work);
              } while ((phraseCharacter & 0x8000) == 0);
              if (prefixSearch != 0 || params->elementCount != 0) wordLength = 1;
              if (Zi8IsDupWordW(output + outputIndex,wordLength,work) != 0) goto nextPhrase;
              output[outputIndex + wordLength] = 0;
            }
            if (optionsMask == 5) {
              totalCandidates++;
              if (totalCandidates >= options->maxCount) goto finishCandidates;
            } else if (remaining == 0) {
              totalCandidates++;
              candidateCount++;
              if (emitWords) {
                outputIndex += wordLength;
                output[outputIndex++] = 0x20;
              } else {
                output[outputIndex++] = firstOrdinal;
              }
              if (candidateCount >= params->maxCandidates || outputIndex > outputLimit) {
                params->wordCandidates = candidateCount;
                goto finishCandidates;
              }
            } else {
              remaining--;
            }
          }
nextPhrase:
          if ((phoneticCount & 0x8000) == 0) {
            for (phraseEntries++; (*phraseEntries & 0x80) == 0; phraseEntries = phraseEntries + 2) {
            }
            phraseEntries++;
          }
        }
      }
      goto finishPhrases;
    }
  }
  else {
finishPhrases:
    if (params->wordCharCount != '\0') {
      params->wordCandidates = candidateCount;
    }
  }
  if ((options->countOnly == '\0') && (tableCursor != 0)) {
    for (ordinalIndex = 0; ordinalIndex < tableCursor; ordinalIndex++) {
      ordinal = ((ziU16)ordinalTable[(Zi8UInt)ordinalIndex * 2] << 8) +
                 (ziU16)ordinalTable[(Zi8UInt)ordinalIndex * 2 + 1];
      phraseTable = syllableTable + (Zi8UInt)ordinal * 0xc;
      if (((*phraseTable & languageMask) != 0) &&
         ((characterSetTable == 0 || ((characterSet & characterSetTable[(Zi8UInt)ordinal]) != 0)))) {
        if (keyIndex != 0) {
          for (index = 0; index < 4; index++) {
            if (keyValues[index] != (keyMasks[index] & phraseTable[index])) break;
          }
          if (index < 4) goto nextSortedOrdinal;
        }
        entryFlags = false;
        if (work->phoneticFilter != 0) {
          tableIndex = (ziU16)phraseTable[8] << 1 | (((ziU16)phraseTable[9] & 0x80) >> 7);
          if (work->phoneticEnabled[tableIndex] == 0) entryFlags = true;
        }
        if (!entryFlags) {
          elementIndex = Zi8IsMatch1Key(spelling,inputLimit,Zi8GetPCode(phoneticTable,phraseTable),matchFull,tone,includeTone);
        } else {
          elementIndex = 0;
        }
        if (((elementIndex == '\0') && (requireFull == 0)) && ((syllableTable[(Zi8UInt)ordinal * 0xc] & 0x80) != 0))
        {
          elementIndex = MatchAltSound1Key(spelling,inputLimit,matchFull,(Zi8AltSoundRecord *)alternateTable,phoneticMask,phoneticTable,ordinal,
                                        tone,includeTone,languageMask,work);
        }
        if (elementIndex == 0) goto nextSortedOrdinal;
        if (!emitWords) {
          if (trackDuplicates && Zi8SetFindCand(params->scratch,ordinal,work) != 0) goto nextSortedOrdinal;
          ordinal = Zi8Ord2Uni(ordinal,work);
          for (index = 0; index < candidateCount; index++) {
            if (ordinal == output[index]) break;
          }
          if (index < candidateCount) goto nextSortedOrdinal;
        } else {
          ordinal = Zi8Ord2Uni(ordinal,work);
          if (Zi8IsDupWordW(&ordinal,1,work) != 0) goto nextSortedOrdinal;
        }
        if (remaining == 0) {
          totalCandidates++;
          if (options->countOnly == 0) {
            candidateCount++;
            output[outputIndex++] = ordinal;
            if (emitWords) output[outputIndex++] = 0x20;
          } else {
            if (totalCandidates >= options->maxCount) goto finishCandidates;
          }
          if (candidateCount >= params->maxCandidates || outputIndex > outputLimit) goto finishCandidates;
        } else {
          remaining--;
        }
      }
nextSortedOrdinal:
    ;
    }
  }
  if ((options->countOnly == '\0') && Zi8GetZHuwdPtr(&userEntries,&userCount,work) != 0)
  {
    for (phraseOrdinal = 0; phraseOrdinal < userCount;) {
      if ((params->elementCount == '\0') || ((userEntries[1] & 0x80) != 0)) {
        userOrdinal = (userEntries[1] & 0x7f) << 8 | (ziU16)userEntries[2];
        phraseTable = syllableTable + (Zi8UInt)userOrdinal * 0xc;
        if (((*phraseTable & languageMask) != 0) &&
           ((characterSetTable == 0 || ((characterSet & characterSetTable[(Zi8UInt)userOrdinal]) != 0)))) {
          if (keyIndex != 0) {
            entryFlags = false;
            for (duplicateIndex = 0; duplicateIndex < 4; duplicateIndex++) {
              if (keyValues[duplicateIndex] != (keyMasks[duplicateIndex] & phraseTable[duplicateIndex])) {
                entryFlags = true;
                break;
              }
            }
            if (entryFlags) goto nextUserOrdinal;
          }
                    elementIndex = Zi8IsMatch1Key(spelling,inputLimit,Zi8GetPCode(phoneticTable,phraseTable),matchFull,tone,includeTone);
          if (((elementIndex == '\0') && (requireFull == 0)) && ((*phraseTable & 0x80) != 0)) {
            elementIndex = MatchAltSound1Key(spelling,inputLimit,matchFull,(Zi8AltSoundRecord *)alternateTable,phoneticMask,phoneticTable,userOrdinal,
                                          tone,includeTone,languageMask,work);
          }
          if (elementIndex == 0) goto nextUserOrdinal;
          if (!emitWords) {
            if (trackDuplicates && Zi8SetFindCand(params->scratch,userOrdinal,work) != 0) goto nextUserOrdinal;
            userCharacter = Zi8Ord2Uni(userOrdinal,work);
            for (duplicateIndex = 0; duplicateIndex < candidateCount; duplicateIndex++) {
              if (userCharacter == output[duplicateIndex]) break;
            }
            if (duplicateIndex < candidateCount) goto nextUserOrdinal;
          } else {
            userCharacter = Zi8Ord2Uni(userOrdinal,work);
            if (Zi8IsDupWordW(&userCharacter,1,work) != 0) goto nextUserOrdinal;
          }
          if (remaining == 0) {
            totalCandidates++;
            candidateCount++;
            output[outputIndex++] = userCharacter;
            if (emitWords) output[outputIndex++] = 0x20;
            if (candidateCount >= params->maxCandidates || outputIndex > outputLimit) goto finishCandidates;
          } else {
            remaining--;
          }
        }
      }
nextUserOrdinal:
      phraseOrdinal++;
      userEntries = userEntries + 3;
    }
  }
  phraseTable = syllableTable;
  previousCharacter = 0;
  for (ordinal = 0; ordinal < ordinalCount;) {
    if (((*phraseTable & languageMask) != 0) &&
       ((characterSetTable == 0 || ((characterSet & characterSetTable[(Zi8UInt)ordinal]) != 0)))) {
      if (keyIndex != 0) {
        for (index = 0; index < 4; index++) {
          if (keyValues[index] != (keyMasks[index] & phraseTable[index])) break;
        }
        if (index < 4) goto nextOrdinal;
      }
      entryFlags = false;
      if (work->phoneticFilter != 0) {
        tableIndex = (ziU16)phraseTable[8] << 1 | (((ziU16)phraseTable[9] & 0x80) >> 7);
        if (work->phoneticEnabled[tableIndex] == 0) entryFlags = true;
      }
      if (!entryFlags) {
        elementIndex = Zi8IsMatch1Key(spelling,inputLimit,Zi8GetPCode(phoneticTable,phraseTable),matchFull,tone,includeTone);
      } else {
        elementIndex = 0;
      }
      if (((elementIndex == '\0') && (requireFull == 0)) && ((*phraseTable & 0x80) != 0)) {
        elementIndex = MatchAltSound1Key(spelling,inputLimit,matchFull,(Zi8AltSoundRecord *)alternateTable,phoneticMask,phoneticTable,ordinal,
                                      tone,includeTone,languageMask,work);
      }
      if (elementIndex == 0) goto nextOrdinal;
      unicodeCharacter = ((ziU16)phraseTable[6] << 8) + (ziU16)phraseTable[7];
      if (unicodeCharacter == previousCharacter) goto nextOrdinal;
      previousCharacter = unicodeCharacter;
      if (!emitWords) {
        if (trackDuplicates && Zi8SetFindCand(params->scratch,ordinal,work) != 0) goto nextOrdinal;
        for (index = 0; index < candidateCount; index++) {
          if (unicodeCharacter == output[index]) break;
        }
        if (index < candidateCount) goto nextOrdinal;
      } else {
        if (Zi8IsDupWordW(&unicodeCharacter,1,work) != 0) goto nextOrdinal;
      }
      if (remaining == 0) {
        totalCandidates++;
        if (options->countOnly == 0) {
          candidateCount++;
          output[outputIndex++] = unicodeCharacter;
          if (emitWords) output[outputIndex++] = 0x20;
        } else {
          if (totalCandidates >= options->maxCount) break;
        }
        if (candidateCount >= params->maxCandidates || outputIndex > outputLimit) break;
      } else {
        remaining--;
      }
    }
nextOrdinal:
    ordinal++;
    phraseTable = phraseTable + 0xc;
  }
finishCandidates:
  if ((emitWords) && (outputIndex != 0)) {
    output[outputIndex] = 0;
    outputIndex++;
  }
  params->count = candidateCount;
  Zi8LogError(100,work);
  return totalCandidates;
}

Zi8UInt Zi8ZHCheckSpelling(ziU16 *input,ziU16 *spelling,Zi8UInt inputLength,char *work)
{
  int index;
  ziU8 result;
  ziU8 usePinyin;
  ziU8 phoneticLength;
  ziU8 toneMask;
  ziU16 phoneticCount;
  ziU16 phoneticMask;
  ziU16 phoneticCode;
  ziU8 *toneTable;
  ziU8 *phoneticTable;
  int syllableStart;
  int syllableLength;
  Zi8UInt tableOffset;
  ziU8 candidateBuffer [32];
  ziU8 phoneticCodes [32];
  ziU8 phoneticMasks [32];
  ziU16 convertedSpelling [64];
  Zi8OneKeyParam getParam;
  ziU8 maskLow;
  ziU8 codeLow;
  ziU8 maskHigh;
  ziU8 codeHigh;
  ziU8 flagsClear;

  result = 0;
  toneTable = 0;
  Zi8LogError(100,work);
  if (*input == 0) {
    Zi8ReplaceLastError(0x187,work);
  }
  else {
    if ((*input >= 0xf305) && (*input <= 0xf329)) {
      usePinyin = 0;
    }
    else {
      usePinyin = 1;
    }
    if (Zi8GetFormatVersion(1,work) >= 4) {
      tableOffset = Zi8GetTableCount(1,0x1a,work);
    }
    else {
      tableOffset = 0;
    }
    if (tableOffset != 0) {
      toneTable = (ziU8 *)Zi8GetTableAddress(1,0x1a,work);
    }
    if ((*spelling >= 0xf305) && (*spelling <= 0xf329)) {
      usePinyin = '\0';
      phoneticTable = (ziU8 *)Zi8GetTableAddress(1,4,work);
      phoneticCount = Zi8GetTableCount(1,4,work);
    }
    else {
      usePinyin = '\x01';
      phoneticTable = (ziU8 *)Zi8GetTableAddress(1,3,work);
      phoneticCount = Zi8GetTableCount(1,3,work);
    }
    index = 0;
    syllableStart = index;
    for (; index < (int)(inputLength & 0xff); index = index + 1) {
      switch (spelling[index]) {
      case 0xf331:
        toneMask = 1;
        goto validateTone;
      case 0xf332:
        toneMask = 2;
        goto validateTone;
      case 0xf333:
        toneMask = 4;
        goto validateTone;
      case 0xf334:
        toneMask = 8;
        goto validateTone;
      case 0xf335:
        toneMask = 0x10;
        goto validateTone;
      default:
        goto nextInputCharacter;
      }
validateTone:
      if (toneTable != 0) {
        while( true ) {
          syllableLength = (index - syllableStart) + 1;
          if ((int)syllableLength <= 1) goto returnSpellingCheck;
          if (usePinyin != '\0') {
            Zi8GetPyPhonetic(input + syllableStart,syllableLength & 0xff,phoneticCodes,phoneticMasks,
                             &phoneticLength,&phoneticMask,&phoneticCode,work);
          }
          else {
            phoneticLength = Zi8GetBpmfPhonetic(input + syllableStart,syllableLength & 0xff,phoneticCodes,
                                           phoneticMasks,&phoneticMask,&phoneticCode,work);
            if (phoneticLength == 0) {
              phoneticLength = 1;
            }
          }
          if (syllableLength == phoneticLength) break;
          if (phoneticLength == 0) goto returnSpellingCheck;
          syllableStart = syllableStart + (Zi8UInt)phoneticLength;
        }
        if ((phoneticCode & 0x1f8) != 0) {
          flagsClear = 0;
        } else {
          flagsClear = 1;
        }
        maskLow = (ziU8)phoneticMask;
        maskHigh = (ziU8)(((Zi8UInt)phoneticMask >> 8) & 0xff);
        codeLow = (ziU8)phoneticCode;
        codeHigh = (ziU8)(((Zi8UInt)phoneticCode >> 8) & 0xff);
        tableOffset = (Zi8UInt)(syllableLength = 0);
        for (; (int)syllableLength < (int)(Zi8UInt)phoneticCount;) {
          if ((codeLow == (maskLow & phoneticTable[tableOffset])) &&
             (codeHigh == (maskHigh & phoneticTable[tableOffset + 1]))) {
            if ((toneMask & toneTable[syllableLength]) != 0) break;
            if (!flagsClear) goto returnSpellingCheck;
          }
          syllableLength = syllableLength + 1;
          tableOffset = tableOffset + 2;
        }
      }
      input[index] = spelling[index];
      syllableStart = index + 1;
nextInputCharacter:
    ;
    }
    for (index = 0; input[index] != 0; index = index + 1) {
      if ((input[index] >= 0x61) && (input[index] <= 0x7a)) {
        convertedSpelling[index] = input[index] + 0xf300;
      }
      else {
        if ((input[index] == 0x27) || (input[index] == 0xf360)) {
          if (index < (int)(inputLength & 0xff)) {
            convertedSpelling[index] = input[index] = spelling[index];
          }
          else {
            convertedSpelling[index] = 0xf360;
          }
        }
        else if (input[index] == 0x2c9) {
          convertedSpelling[index] = 0xf331;
        }
        else if (input[index] == 0x2ca) {
          convertedSpelling[index] = 0xf332;
        }
        else if (input[index] == 0x2c7) {
          convertedSpelling[index] = 0xf333;
        }
        else if (input[index] == 0x2cb) {
          convertedSpelling[index] = 0xf334;
        }
        else if (input[index] == 0x2d9) {
          convertedSpelling[index] = 0xf335;
        }
        else {
          convertedSpelling[index] = input[index];
        }
      }
    }
    getParam.language = 1;
    if (usePinyin != '\0') {
      getParam.getMode = 1;
      getParam.subLanguage = 1;
    }
    else {
      getParam.getMode = 2;
      getParam.subLanguage = 2;
    }
    getParam.context = 0x11;
    getParam.getOptions = 0;
    getParam.elements = convertedSpelling;
    getParam.elementCount = (ziU8)index;
    getParam.currentWord = 0;
    getParam.wordCharCount = 0;
    getParam.candidates = (ziWChar *)candidateBuffer;
    getParam.maxCandidates = 1;
    getParam.firstCandidate = 0;
    if ((ziU8)_Zi8CheckCandidates(&getParam,work) != 0) {
      result = 1;
    }
  }
returnSpellingCheck:
  return result;
}
