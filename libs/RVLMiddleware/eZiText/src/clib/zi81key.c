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
extern ziU8 Zi8IsDupWordW();
extern ziU8 Zi8GetFormatVersion(ziU8,ziPtr);
extern ziU16 Zi8Uni2Ord(ziWChar,ziPtr);
extern ziU16 Zi8GetPCode(ziU8 *,ziU8 *);
extern int Zi8MatchOEMdata();
extern int Zi8MatchPUDdata();
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
  ziU16 initialIndex;
  ziU16 finalIndex;
  ziU16 tone;
  Zi8UInt length;

  length = 0;
  initialIndex = (ziU16)(((key & 0xffff) >> 9) & 0x3f);
  finalIndex = (ziU16)(((key & 0xffff) >> 3) & 0x3f);
  tone = (ziU16)(key & 7);
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

Zi8UInt Zi8IsMatch1Key(ziU16 *input,Zi8UInt inputLength,Zi8UInt key,ziU8 requireFull,ziU8 usePinyin,Zi8UInt tone)
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
  if (((tone & 0xff) == 0) && ((inputLength & 0xff) > (spellingLength & 0xff))) {
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

Zi8UInt MatchAltSound1Key(ziU16 *spelling,Zi8UInt spellingLength,Zi8UInt requireFull,Zi8AltSoundRecord *records,Zi8UInt recordCount,const ziU8 *phoneticTableBase,Zi8UInt key,Zi8UInt usePinyin,ziU8 tone,ziU8 modifierFlags,Zi8OneKeyWork *context)
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
        if ((context->phoneticFilter == '\0') ||
            (context->phoneticEnabled[(ziU16)phoneticOffset] != '\0')) {
          phoneticOffset = (ziU16)(phoneticOffset << 1);
          phoneticCode = (ziU16)(((records[recordIndex].flags & 0xf0) >> 4) |
                                  CONCAT11_LOW_FIRST(phoneticTableBase[phoneticOffset],
                                                     phoneticTableBase[phoneticOffset + 1]));
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
      if ((context->phoneticFilter == '\0') ||
          (context->phoneticEnabled[(ziU16)phoneticOffset] != '\0')) {
        phoneticOffset = (ziU16)(phoneticOffset << 1);
        phoneticCode = (ziU16)(((records[recordIndex].flags & 0xf0) >> 4) |
                                CONCAT11_LOW_FIRST(phoneticTableBase[phoneticOffset],
                                                   phoneticTableBase[phoneticOffset + 1]));
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
    while (true) {
      if ((keyHigh == records[searchIndex].keyHigh) &&
          (keyLow == records[searchIndex].keyLow)) {
        recordIndex = searchIndex;
        goto PROCESS;
      }
      if ((int)CONCAT11(records[searchIndex].keyHigh,
                        records[searchIndex].keyLow) <= (int)(key & 0xffff)) {
        midpoint = ((int)searchIndex + recordIndex) / 2;
        if (midpoint == (int)searchIndex) {
          return 0;
        }
        if ((int)CONCAT11(records[midpoint].keyHigh,
                          records[midpoint].keyLow) < (int)(key & 0xffff)) {
          searchIndex = midpoint;
        } else {
          recordIndex = midpoint;
          for (;;) {
            if ((keyHigh == records[recordIndex].keyHigh) &&
                (keyLow == records[recordIndex].keyLow)) {
              searchIndex = recordIndex;
              goto PROCESS;
            }
            if ((int)CONCAT11(records[recordIndex].keyHigh,
                              records[recordIndex].keyLow) >= (int)(key & 0xffff)) {
              midpoint = ((int)searchIndex + recordIndex) / 2;
              if (midpoint == (int)searchIndex) {
                return 0;
              }
              if ((int)CONCAT11(records[midpoint].keyHigh,
                                records[midpoint].keyLow) < (int)(key & 0xffff)) {
                searchIndex = midpoint;
                break;
              }
              recordIndex = midpoint;
            } else {
              return 0;
            }
          }
        }
      } else {
        return 0;
      }
    }

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
  ziBool exactLength;
  ziU8 optionsMask;
  ziU8 mode;
  ziU8 savedSearchCount;
  ziU8 savedSearchFlags;
  ziU8 *savedSearchOrder;
  ziU16 phoneticIndex;
  ziU16 phoneticCode;
  ziU8 usePinyin;
  ziU8 languageMask;
  ziU16 tableCount;
  int characterIndex;
  ziU8 duplicate;
  ziU16 expansionCount;
  ziU16 firstElement;
  ziU8 inputLength;
  ziU8 entryLength;
  ziU8 characterSet;
  ziU8 candidateCount;
  ziU16 remaining;
  ziU16 spellingLength;
  ziU16 spellingIndex;
  ziU16 *output;
  ziU8 *phoneticTable;
  ziU8 *spellingEntry;
  Zi8UInt totalCandidates;
  ziU16 spellingBuffer [8];
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
    totalCandidates = 0;
    goto returnSpelling;
  }
  if (((params->subLanguage & 0x80) != 0) || ((params->subLanguage & 0x40) != 0)) {
    characterSet = 1;
  }
  else if ((params->subLanguage & 8) != 0) {
    characterSet = 4;
  }
  else if (((params->subLanguage & 0x20) != 0) || ((params->subLanguage & 0x10) != 0)) {
    characterSet = 2;
  }
  else {
    characterSet = params->subLanguage;
  }
  languageMask = characterSet << 4;
  remaining = params->firstCandidate;
  if (options->countOnly == '\0') {
    output = params->candidates;
  }
  else {
    output = spellingBuffer;
  }
  tableCount = Zi8GetTableCount(1,0xc,work);
  if (((((((languageMask & 0x10) == 0) || (params->getMode != '\x03')) ||
        ((params->context & 0x10) == 0)) ||
       (characterIndex = ZiIsSupportedPhonetic(0x7c,work), characterIndex == 0)) &&
      ((((languageMask & 0x10) == 0 || (params->getMode != '\x0f')) ||
       (characterIndex = ZiIsSupportedPhonetic(0x7b,work), characterIndex == 0)))) &&
     (((((languageMask & 0x20) == 0 || (params->getMode != '\x04')) ||
       (((params->context & 0x10) == 0 ||
        (characterIndex = ZiIsSupportedPhonetic(0x7d,work), characterIndex == 0)))) && (tableCount == 0))))
  goto finishSpelling;
  mode = params->getMode;
  if (mode == 4) {
    phoneticTable = (ziU8 *)Zi8GetTableAddress(1,4,work);
    Zi8GetTableCount(1,4,work);
    usePinyin = false;
prepareInput:
    inputLength = params->elementCount;
    while ((inputLength != 0 && ((ziS16)params->elements[(inputLength - 1)] == -0x10f7))) {
      inputLength = inputLength - 1;
    }
    exactLength = inputLength != 0;
    firstElement = params->elements[0];
    if ((((inputLength == 1) && ((optionsMask & 0x81) == 0x80)) && (0xeff0 < firstElement)) && (firstElement < 0xf011)) {
      if (usePinyin) {
        if (firstElement == 0xeff2) {
          spellingBuffer[0] = 0xf361;
        }
        expansionCount = (unsigned long long)(firstElement == 0xeff2);
        if (firstElement == 0xeff2) {
          spellingBuffer[1] = 0xf362;
          expansionCount = 3;
          spellingBuffer[2] = 0xf363;
        }
        if (firstElement == 0xeff3) {
          characterIndex = (int)expansionCount;
          spellingBuffer[expansionCount] = 0xf364;
          spellingBuffer[characterIndex + 1] = 0xf365;
          expansionCount = expansionCount + 3;
          spellingBuffer[characterIndex + 2] = 0xf366;
        }
        if (firstElement == 0xeff4) {
          characterIndex = (int)expansionCount;
          spellingBuffer[expansionCount] = 0xf367;
          spellingBuffer[characterIndex + 1] = 0xf368;
          expansionCount = expansionCount + 3;
          spellingBuffer[characterIndex + 2] = 0xf369;
        }
        if (firstElement == 0xeff5) {
          characterIndex = (int)expansionCount;
          spellingBuffer[expansionCount] = 0xf36a;
          spellingBuffer[characterIndex + 1] = 0xf36b;
          expansionCount = expansionCount + 3;
          spellingBuffer[characterIndex + 2] = 0xf36c;
        }
        if (firstElement == 0xeff6) {
          characterIndex = (int)expansionCount;
          spellingBuffer[expansionCount] = 0xf36d;
          spellingBuffer[characterIndex + 1] = 0xf36e;
          expansionCount = expansionCount + 3;
          spellingBuffer[characterIndex + 2] = 0xf36f;
        }
        if (firstElement == 0xeff7) {
          characterIndex = (int)expansionCount;
          spellingBuffer[expansionCount] = 0xf370;
          spellingBuffer[characterIndex + 1] = 0xf371;
          spellingBuffer[characterIndex + 2] = 0xf372;
          expansionCount = expansionCount + 4;
          spellingBuffer[characterIndex + 3] = 0xf373;
        }
        if (firstElement == 0xeff8) {
          characterIndex = (int)expansionCount;
          spellingBuffer[expansionCount] = 0xf374;
          spellingBuffer[characterIndex + 1] = 0xf375;
          expansionCount = expansionCount + 3;
          spellingBuffer[characterIndex + 2] = 0xf376;
        }
        if (firstElement == 0xeff9) {
          characterIndex = (int)expansionCount;
          spellingBuffer[expansionCount] = 0xf377;
          spellingBuffer[characterIndex + 1] = 0xf378;
          spellingBuffer[characterIndex + 2] = 0xf379;
          expansionCount = expansionCount + 4;
          spellingBuffer[characterIndex + 3] = 0xf37a;
        }
      }
      else {
        if (firstElement == 0xeff1) {
          spellingBuffer[0] = 0xf305;
        }
        expansionCount = (unsigned long long)(firstElement == 0xeff1);
        if (firstElement == 0xeff1) {
          spellingBuffer[1] = 0xf306;
          spellingBuffer[2] = 0xf307;
          expansionCount = 4;
          spellingBuffer[3] = 0xf308;
        }
        if (firstElement == 0xeff2) {
          characterIndex = (int)expansionCount;
          spellingBuffer[expansionCount] = 0xf309;
          spellingBuffer[characterIndex + 1] = 0xf30a;
          spellingBuffer[characterIndex + 2] = 0xf30b;
          expansionCount = expansionCount + 4;
          spellingBuffer[characterIndex + 3] = 0xf30c;
        }
        if (firstElement == 0xeff3) {
          characterIndex = (int)expansionCount;
          spellingBuffer[expansionCount] = 0xf30d;
          spellingBuffer[characterIndex + 1] = 0xf30e;
          expansionCount = expansionCount + 3;
          spellingBuffer[characterIndex + 2] = 0xf30f;
        }
        if (firstElement == 0xeff4) {
          characterIndex = (int)expansionCount;
          spellingBuffer[expansionCount] = 0xf310;
          spellingBuffer[characterIndex + 1] = 0xf311;
          expansionCount = expansionCount + 3;
          spellingBuffer[characterIndex + 2] = 0xf312;
        }
        if (firstElement == 0xeff5) {
          characterIndex = (int)expansionCount;
          spellingBuffer[expansionCount] = 0xf313;
          spellingBuffer[characterIndex + 1] = 0xf314;
          spellingBuffer[characterIndex + 2] = 0xf315;
          expansionCount = expansionCount + 4;
          spellingBuffer[characterIndex + 3] = 0xf316;
        }
        if (firstElement == 0xeff6) {
          characterIndex = (int)expansionCount;
          spellingBuffer[expansionCount] = 0xf317;
          spellingBuffer[characterIndex + 1] = 0xf318;
          expansionCount = expansionCount + 3;
          spellingBuffer[characterIndex + 2] = 0xf319;
        }
        if (firstElement == 0xeff7) {
          characterIndex = (int)expansionCount;
          spellingBuffer[expansionCount] = 0xf31a;
          spellingBuffer[characterIndex + 1] = 0xf31b;
          spellingBuffer[characterIndex + 2] = 0xf31c;
          expansionCount = expansionCount + 4;
          spellingBuffer[characterIndex + 3] = 0xf31d;
        }
        if (firstElement == 0xeff8) {
          characterIndex = (int)expansionCount;
          spellingBuffer[expansionCount] = 0xf31e;
          spellingBuffer[characterIndex + 1] = 0xf31f;
          spellingBuffer[characterIndex + 2] = 0xf320;
          expansionCount = expansionCount + 4;
          spellingBuffer[characterIndex + 3] = 0xf321;
        }
        if (firstElement == 0xeff9) {
          characterIndex = (int)expansionCount;
          spellingBuffer[expansionCount] = 0xf322;
          spellingBuffer[characterIndex + 1] = 0xf323;
          spellingBuffer[characterIndex + 2] = 0xf324;
          spellingBuffer[characterIndex + 3] = 0xf325;
          expansionCount = expansionCount + 5;
          spellingBuffer[characterIndex + 4] = 0xf326;
        }
        if (firstElement == 0xeffa) {
          characterIndex = (int)expansionCount;
          spellingBuffer[expansionCount] = 0xf327;
          spellingBuffer[characterIndex + 1] = 0xf328;
          expansionCount = expansionCount + 3;
          spellingBuffer[characterIndex + 2] = 0xf329;
        }
      }
      for (spellingIndex = 0; spellingIndex < expansionCount; spellingIndex = spellingIndex + 1) {
        if (remaining == 0) {
          totalCandidates = totalCandidates + 1;
          if (options->countOnly == '\0') {
            *output = spellingBuffer[spellingIndex];
            output[1] = 0;
            output = output + 2;
            candidateCount = candidateCount + 1;
          }
          else if (options->maxCount <= (int)totalCandidates) break;
          if (params->maxCandidates <= candidateCount) break;
        }
        else {
          remaining = remaining + -1;
        }
      }
    }
    else {
      if ((((((languageMask & 0x10) != 0) && (params->getMode == '\x03')) &&
           (((params->context & 0x10) != 0 &&
            (characterIndex = ZiIsSupportedPhonetic(0x7c,work), characterIndex != 0)))) ||
          ((((languageMask & 0x10) != 0 && (params->getMode == '\x0f')) &&
           (characterIndex = ZiIsSupportedPhonetic(0x7b,work), characterIndex != 0)))) ||
         (((((languageMask & 0x20) != 0 && (params->getMode == '\x04')) &&
           ((params->context & 0x10) != 0)) &&
          (characterIndex = ZiIsSupportedPhonetic(0x7d,work), characterIndex != 0)))) {
        savedSearchOrder = work->searchOrder;
        savedSearchCount = work->searchOrderCount;
        usePinyin = false;
        savedSearchFlags = work->searchFlags;
        Zi8Memset(&searchParams,0,0x2c);
        searchParams.getMode = 0;
        searchParams.subLanguage = 0x80;
        searchParams.context = 1;
        searchParams.getOptions = 0x81;
        if (((params->getOptions & 0x10) != 0) || ((params->getOptions & 0xe) == 2)) {
          searchParams.getOptions = 0x83;
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
            duplicate = Zi8LangSupported(0x77,work);
            if (duplicate == '\0') {
              duplicate = Zi8LangSupported(0x78,work);
              if (duplicate != '\0') {
                searchParams.language = ZI8_LANG_PYS;
              }
            }
            else {
              searchParams.language = ZI8_LANG_PYP;
            }
          }
          if (((params->context & 0xf) == 1) || ((params->context & 0xf) == 5)) {
            duplicate = Zi8LangSupported(0x78,work);
            if (duplicate == '\0') {
              duplicate = Zi8LangSupported(0x77,work);
              if (duplicate != '\0') {
                searchParams.subLanguage = ZI8_LANG_PYP;
              }
            }
            else {
              searchParams.subLanguage = ZI8_LANG_PYS;
            }
          }
          if ((searchParams.language == ZI8_LANG_PY2) && (searchParams.subLanguage != 0x80)) {
            searchParams.language = searchParams.subLanguage;
            searchParams.subLanguage = 0x80;
          }
          for (tableCount = 0; tableCount < params->elementCount; tableCount = tableCount + 1) {
            if ((ziS16)params->elements[(Zi8UInt)tableCount] == -0xca0) {
              params->elements[(Zi8UInt)tableCount] = 0x27;
              usePinyin = true;
            }
          }
        }
        else {
          searchParams.language = ZI8_LANG_ZY2;
          if (((params->context & 0xf) == 1) || ((params->context & 0xf) == 3)) {
            duplicate = Zi8LangSupported(0x79,work);
            if (duplicate == '\0') {
              duplicate = Zi8LangSupported(0x7a,work);
              if (duplicate != '\0') {
                searchParams.language = ZI8_LANG_ZYS;
              }
            }
            else {
              searchParams.language = ZI8_LANG_ZYP;
            }
          }
          if (((params->context & 0xf) == 1) || ((params->context & 0xf) == 5)) {
            duplicate = Zi8LangSupported(0x7a,work);
            if (duplicate == '\0') {
              duplicate = Zi8LangSupported(0x79,work);
              if (duplicate != '\0') {
                searchParams.subLanguage = ZI8_LANG_ZYP;
              }
            }
            else {
              searchParams.subLanguage = ZI8_LANG_ZYS;
            }
          }
          if ((searchParams.language == ZI8_LANG_ZY2) && (searchParams.subLanguage != 0x80)) {
            searchParams.language = searchParams.subLanguage;
            searchParams.subLanguage = 0x80;
          }
          for (tableCount = 0; tableCount < params->elementCount; tableCount = tableCount + 1) {
            if ((ziS16)params->elements[(Zi8UInt)tableCount] == 0x27) {
              params->elements[(Zi8UInt)tableCount] = 0xf360;
              usePinyin = true;
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
        totalCandidates = _Zi8GetCandidates(&searchParams,work);
        totalCandidates = totalCandidates & 0xff;
        work->spellingSearch = 0;
        work->searchFlags = savedSearchFlags;
        work->searchOrder = savedSearchOrder;
        work->searchOrderCount = savedSearchCount;
        params->count = searchParams.count;
        work->spellingOnly = 0;
        if (usePinyin) {
          if (params->getMode == '\x03') {
            for (tableCount = 0; tableCount < params->elementCount; tableCount = tableCount + 1) {
              if ((ziS16)params->elements[(Zi8UInt)tableCount] == 0x27) {
                params->elements[(Zi8UInt)tableCount] = 0xf360;
              }
            }
          }
          else {
            for (tableCount = 0; tableCount < params->elementCount; tableCount = tableCount + 1) {
              if ((ziS16)params->elements[(Zi8UInt)tableCount] == -0xca0) {
                params->elements[(Zi8UInt)tableCount] = 0x27;
              }
            }
          }
        }
        if ((options->countOnly == '\0') && (params->getMode == '\x03')) {
          for (tableCount = 0; tableCount < params->count; tableCount = tableCount + 1) {
            while (*output != 0) {
              if (*output == 0x27) {
                *output = 0xf360;
                output = output + 1;
              }
              else {
                *output = *output | 0xf300;
                output = output + 1;
              }
            }
            output = output + 1;
          }
        }
        Zi8LogError(100,work);
        goto returnSpelling;
      }
      if (params->getMode == '\x0f') {
        Zi8LogError(1000,work);
        totalCandidates = 0;
        goto returnSpelling;
      }
      Zi8InitDupWordBuf(work);
      while (tableCount != 0) {
        spellingEntry = (ziU8 *)Zi8GetTableAddress(1,0xc,work);
        for (firstElement = 0; firstElement < tableCount; firstElement = firstElement + 1) {
          if ((*spellingEntry & languageMask) != 0) {
            if (usePinyin) {
              entryLength = *spellingEntry;
            }
            else {
              entryLength = spellingEntry[1];
            }
            entryLength = entryLength & 0xf;
            if (exactLength) {
              if (entryLength == inputLength) {
appendSpelling:
                phoneticIndex = (spellingEntry[1] & 0xf0) << 4 | (ziU16)spellingEntry[2];
                phoneticCode = CONCAT11(phoneticTable[(Zi8UInt)phoneticIndex * 2 + 1],
                                 phoneticTable[(Zi8UInt)phoneticIndex * 2]);
                if (usePinyin) {
                  Zi8SpellingPY(output,phoneticCode,0);
                }
                else {
                  Zi8SpellingZY(output,phoneticCode,0);
                }
                for (spellingIndex = 0;
                    (spellingIndex < inputLength &&
                    ((0xf304 < params->elements[(Zi8UInt)spellingIndex] ||
                     (output[spellingIndex] == params->elements[(Zi8UInt)spellingIndex]))
                    )); spellingIndex = spellingIndex + 1) {
                }
                if ((inputLength == 0) || (inputLength <= spellingIndex)) {
                  if (usePinyin) {
                    spellingLength = Zi8GetPInfo(phoneticCode,output,8,work);
                  }
                  else {
                    spellingLength = Zi8GetZInfo(phoneticCode,output,8,work);
                  }
                  spellingLength = spellingLength & 0xff;
                  if (spellingLength != 0) {
                    for (spellingIndex = 0;
                        (spellingIndex < inputLength &&
                        ((params->elements[(Zi8UInt)spellingIndex] < 0xf305 ||
                         (output[spellingIndex] ==
                          params->elements[(Zi8UInt)spellingIndex]))));
                        spellingIndex = spellingIndex + 1) {
                    }
                    if ((inputLength == 0) || (inputLength <= spellingIndex)) {
                      if ((ziU8)options->maxSpellingLength < spellingLength) {
                        spellingLength = (ziU16)(ziU8)options->maxSpellingLength;
                        output[spellingLength] = 0;
                      }
                      if (((((params->getOptions & 0x10) != 0) ||
                           ((params->getOptions & 0xe) == 2)) ||
                          (params->elementCount < work->maxWordLength)) &&
                         ((params->elementCount != '\0' && (params->elementCount < spellingLength)))
                         ) {
                        spellingLength = (ziU16)params->elementCount;
                        output[spellingLength] = 0;
                      }
                      duplicate = Zi8IsDupWordW(output,spellingLength,work);
                      if (duplicate == '\0') {
                        if (remaining == 0) {
                          totalCandidates = totalCandidates + 1;
                          if (options->countOnly == '\0') {
                            output = output + spellingLength + 1;
                            candidateCount = candidateCount + 1;
                          }
                          else if (options->maxCount <= (int)totalCandidates) goto finishSpelling;
                          if (params->maxCandidates <= candidateCount) goto finishSpelling;
                        }
                        else {
                          remaining = remaining + -1;
                        }
                      }
                    }
                  }
                }
              }
            }
            else if ((inputLength == 0) || (inputLength < entryLength)) goto appendSpelling;
          }
          spellingEntry = spellingEntry + 3;
        }
        if (!exactLength) break;
        exactLength = false;
      }
    }
  }
  else if (mode < 4) {
    if (2 < mode) {
preparePinyinSpelling:
      phoneticTable = (ziU8 *)Zi8GetTableAddress(1,3,work);
      Zi8GetTableCount(1,3,work);
      usePinyin = true;
      goto prepareInput;
    }
  }
  else if (mode == 0xf) goto preparePinyinSpelling;
finishSpelling:
  params->count = candidateCount;
  Zi8LogError(100,work);
returnSpelling:
  return totalCandidates;
}

int Zi8Get1KeyPressCandidates(Zi8OneKeyParam *params,Zi8OneKeyOptions *options,Zi8OneKeyWork *work)
{
  ziU8 entryFlags;
  ziU8 emitWords;
  ziU8 trackDuplicates;
  ziU8 matchFull;
  ziU8 includeTone;
  ziU8 requireFull;
  ziU8 prefixSearch;
  ziU8 mode;
  ziU8 result;
  Zi8UInt wordIndex;
  int index;
  ziU16 contextCharacter;
  ziU16 character;
  ziU8 optionsMask;
  ziU8 *recordCursor;
  Zi8UInt phoneticIndex;
  ziU8 contextRemaining;
  ziU8 contextIndex;
  ziU8 entryRemaining;
  ziU8 nibble;
  ziU8 wordLength;
  ziU8 phoneticLength;
  ziU8 candidateCount;
  ziU8 keyIndex;
  ziU8 elementIndex;
  ziU8 tone;
  ziU8 inputLimit;
  ziU8 inputLength;
  ziU8 characterSet;
  ziU8 languageMask;
  ziU16 unicodeCharacter;
  ziU16 userCharacter;
  ziU16 userOrdinal;
  ziU16 userCount;
  ziU16 phraseOrdinal;
  ziU16 ordinalIndex;
  ziU16 phoneticCount;
  ziU16 phraseCharacter;
  ziU16 firstOrdinal;
  ziU16 phoneticCode;
  ziU16 characterMask;
  ziU16 candidateCharacter;
  ziU16 candidateOrdinal;
  ziU16 tableIndex;
  ziU16 previousCharacter;
  ziU16 tableCursor;
  ziU16 ordinal;
  ziU16 remaining;
  ziU16 phoneticMask;
  ziU16 ordinalCount;
  ziU16 alternateCount;
  int duplicateIndex;
  ziU8 *userEntries;
  ziU8 *entryCursor;
  ziU16 *currentWord;
  ziU8 *phraseEntries;
  int outputLimit;
  int outputIndex;
  ziU16 *output;
  int totalCandidates;
  ziU8 keyMasks [8];
  ziU8 *phraseTable;
  ziU8 *phoneticTable;
  ziU8 *characterSetTable;
  ziU8 *ordinalTable;
  ziU8 *alternateTable;
  ziU8 *syllableTable;
  ziU16 spelling [8];
  ziU16 wordBuffer [64];

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
  optionsMask = optionsMask & ~0x10;
  optionsMask = optionsMask & ~0x20;
  optionsMask = optionsMask & ~0x40;
  if (((params->subLanguage & 0x80) == 0) && ((params->subLanguage & 0x40) == 0)) {
    if ((params->subLanguage & 8) == 0) {
      if (((params->subLanguage & 0x20) != 0) || ((params->subLanguage & 0x10) != 0)) {
        languageMask = 2;
      }
    }
    else {
      languageMask = 4;
    }
  }
  else {
    languageMask = 1;
  }
  if (languageMask == 0) {
    languageMask = params->subLanguage;
  }
  else {
    mode = Zi8GetFormatVersion(1,work);
    if (mode < 4) {
      characterSetTable = 0;
    }
    else {
      characterSetTable = (ziU8 *)Zi8GetTableAddress(1,0x15,work);
    }
    if (characterSetTable != 0) {
      characterSet = params->subLanguage;
    }
    if (languageMask != 3) {
      if (languageMask < 3) {
        if (languageMask == 1) {
          if (((params->subLanguage & 0x40) != 0) ||
             (wordIndex = Zi8GetZHCharSet(work), (wordIndex & 1) != 0)) {
            characterSetTable = 0;
          }
        }
        else if ((languageMask != 0) &&
                (((params->subLanguage & 0x10) != 0 ||
                 (wordIndex = Zi8GetZHCharSet(work), (wordIndex & 0x10) != 0)))) {
          characterSetTable = 0;
        }
      }
      else if ((languageMask < 5) && ((params->subLanguage & 0x10) != 0)) {
        characterSetTable = 0;
      }
    }
  }
  languageMask = languageMask << 4;
  remaining = params->firstCandidate;
  params->count = 0;
  params->letters = 0;
  inputLength = params->elementCount;
  if (inputLength != 0) {
    do {
      if (params->elements[(inputLength - 1)] != 0xef09) {
        break;
      }
      inputLength = inputLength - 1;
    } while (inputLength != 0);
  }
  index = inputLength;
  if (inputLength != 0) {
    inputLimit = index++;
  }
  else {
    inputLimit = 0;
  }
  for (keyIndex = 0; keyIndex < 4; keyIndex = keyIndex + 1) {
    keyMasks[keyIndex + 4] = 0;
    keyMasks[keyIndex] = 0;
  }
  for (keyIndex = 1; (index < (int)(Zi8UInt)inputLength && ((Zi8UInt)((int)(Zi8UInt)keyIndex >> 1) < 4));
      keyIndex = keyIndex + 1) {
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
    default:
      nibble = 0;
      break;
    case 0xef0a:
      nibble = 4;
    }
    if ((keyIndex & 1) == 0) {
      keyMasks[((int)(Zi8UInt)keyIndex >> 1) + 4] =
           keyMasks[((int)(Zi8UInt)keyIndex >> 1) + 4] | nibble << 4;
      if (params->elements[index] == 0xef0b) {
        keyMasks[(int)(Zi8UInt)keyIndex >> 1] = keyMasks[(int)(Zi8UInt)keyIndex >> 1] | 0x80;
      }
      else if (params->elements[index] == 0xef0a) {
        keyMasks[(int)(Zi8UInt)keyIndex >> 1] = keyMasks[(int)(Zi8UInt)keyIndex >> 1] | 0x40;
      }
      else if (params->elements[index] != 0xef00) {
        keyMasks[(int)(Zi8UInt)keyIndex >> 1] = keyMasks[(int)(Zi8UInt)keyIndex >> 1] | 0x70;
      }
    }
    else {
      keyMasks[((int)(Zi8UInt)keyIndex >> 1) + 4] =
           keyMasks[((int)(Zi8UInt)keyIndex >> 1) + 4] | nibble;
      if (params->elements[index] == 0xef0b) {
        keyMasks[(int)(Zi8UInt)keyIndex >> 1] = keyMasks[(int)(Zi8UInt)keyIndex >> 1] | 8;
      }
      else if (params->elements[index] == 0xef0a) {
        keyMasks[(int)(Zi8UInt)keyIndex >> 1] = keyMasks[(int)(Zi8UInt)keyIndex >> 1] | 4;
      }
      else if (params->elements[index] != 0xef00) {
        keyMasks[(int)(Zi8UInt)keyIndex >> 1] = keyMasks[(int)(Zi8UInt)keyIndex >> 1] | 7;
      }
    }
    index = index + 1;
  }
  keyIndex--;
  syllableTable = (ziU8 *)Zi8GetTableAddress(1,0,work);
  ordinalCount = Zi8GetTableCount(1,0,work);
  alternateTable = (ziU8 *)Zi8GetTableAddress(1,5,work);
  phoneticMask = Zi8GetTableCount(1,5,work);
  if ((((params->context & 0x40) != 0) &&
      (result = Zi8GetFormatVersion(1,work), result != '\0')) &&
     (characterMask = Zi8GetTableCount(1,0xf,work), characterMask != 0)) {
    ordinalCount = characterMask;
  }
  if (((params->context & 0x80) != 0) && (params->scratch != 0)) {
    Zi8Memset(params->scratch,0,(int)(ordinalCount + 7) >> 3);
    trackDuplicates = true;
  }
  if ((params->context & 0x10) != 0) {
    if (output == 0) goto finishCandidates;
    Zi8InitDupWordBuf(work);
    emitWords = true;
  }
  mode = params->getMode;
  if (mode == 4) {
    phoneticTable = (ziU8 *)Zi8GetTableAddress(1,4,work);
    alternateCount = Zi8GetTableCount(1,4,work);
    tone = 0;
  }
  else {
    if ((3 < mode) || (mode < 3)) goto finishCandidates;
    phoneticTable = (ziU8 *)Zi8GetTableAddress(1,3,work);
    alternateCount = Zi8GetTableCount(1,3,work);
    tone = 1;
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
  for (index = 0; index < (int)(Zi8UInt)inputLimit; index = index + 1) {
    spelling[index] = params->elements[index];
  }
  work->phoneticFilter = 0;
  if (inputLimit != 0) {
    entryFlags = false;
    work->phoneticFilter = 1;
    Zi8Memset(work->phoneticEnabled,0,0x200);
    for (phoneticIndex = 0; index = (int)phoneticIndex, index < (int)(Zi8UInt)alternateCount; phoneticIndex = phoneticIndex + 1) {
      phoneticCode = CONCAT11(phoneticTable[(int)(phoneticIndex << 1) + 1],
                          phoneticTable[(int)(phoneticIndex << 1)]);
      result = Zi8IsMatch1Key(spelling,inputLimit,phoneticCode,0,tone,0);
      if (result == '\0') {
        work->phoneticEnabled[index] = 0;
      }
      else {
        work->phoneticEnabled[index] = 1;
        entryFlags = true;
      }
    }
    if (!entryFlags) goto finishCandidates;
  }
  if ((((options->countOnly == '\0') || (optionsMask == 5)) &&
      ((optionsMask != 5 || ((ziS8)params->wordCharCount != '\0')))) &&
     (((ziS8)params->wordCharCount == '\0' ||
      (result = Zi8IsCharacter(params->currentWord[0],work), result != '\0')))) {
    phoneticLength = 0;
nextOEMword:
    do {
      do {
        do {
          result = Zi8MatchOEMdata(params->currentWord,params->wordCharCount,1
                                   ,wordBuffer,0x40,0,phoneticLength,work);
          if (result == '\0') goto searchUserWords;
          phoneticLength = 1;
          candidateCharacter = wordBuffer[params->wordCharCount];
        } while ((candidateCharacter == previousCharacter) ||
                (result = Zi8IsCharacter(candidateCharacter,work), result == '\0'));
        previousCharacter = candidateCharacter;
        candidateOrdinal = Zi8Uni2Ord(candidateCharacter,work);
        phraseTable = syllableTable + (Zi8UInt)candidateOrdinal * 0xc;
        entryFlags = false;
        if (keyIndex != 1) {
          for (index = 0; index < 4; index = index + 1) {
            if (keyMasks[index + 4] != (keyMasks[index] & phraseTable[index])) {
              entryFlags = true;
              break;
            }
          }
        }
      } while (entryFlags);
      character = Zi8GetPCode(phoneticTable,phraseTable);
      elementIndex = Zi8IsMatch1Key(spelling,inputLimit,character,matchFull,tone,includeTone);
      if (((elementIndex == '\0') && (requireFull == 0)) && ((*phraseTable & 0x80) != 0)) {
        elementIndex = MatchAltSound1Key(spelling,inputLimit,matchFull,(Zi8AltSoundRecord *)alternateTable,phoneticMask,phoneticTable,candidateOrdinal,
                                      tone,includeTone,languageMask,work);
      }
    } while (elementIndex == '\0');
    if (emitWords) {
      wordLength = 0;
      for (wordIndex = (Zi8UInt)params->wordCharCount; wordBuffer[wordIndex] != 0; wordIndex = wordIndex + 1) {
        wordLength = wordLength + 1;
      }
      if ((prefixSearch != 0) || ((ziS8)params->elementCount != '\0')) {
        wordLength = 1;
      }
      result = Zi8IsDupWordW(wordBuffer + params->wordCharCount,wordLength,work);
      if (result != '\0') goto nextOEMword;
      wordBuffer[(Zi8UInt)params->wordCharCount + (Zi8UInt)wordLength] = 0;
    }
    else {
      if ((trackDuplicates) &&
         (result = Zi8SetFindCand(params->scratch,candidateOrdinal,work), result != '\0')
         ) goto nextOEMword;
      for (index = 0;
          (index < (int)(Zi8UInt)candidateCount && (candidateCharacter != output[index]));
          index = index + 1) {
      }
      if (index < (int)(Zi8UInt)candidateCount) goto nextOEMword;
    }
    if (optionsMask == 5) {
      totalCandidates = totalCandidates + 1;
      if (options->maxCount <= totalCandidates) goto finishCandidates;
    }
    else if (remaining == 0) {
      totalCandidates = totalCandidates + 1;
      candidateCount = candidateCount + 1;
      if (emitWords) {
        for (wordIndex = (Zi8UInt)params->wordCharCount; wordBuffer[wordIndex] != 0; wordIndex = wordIndex + 1) {
          output[outputIndex] = wordBuffer[wordIndex];
          outputIndex = outputIndex + 1;
        }
        output[outputIndex] = 0x20;
      }
      else {
        output[outputIndex] = candidateCharacter;
      }
      outputIndex = outputIndex + 1;
      if ((params->maxCandidates <= candidateCount) || (outputLimit < outputIndex)) goto finishOEMwords;
    }
    else {
      remaining = remaining + -1;
    }
    goto nextOEMword;
  }
searchUserWords:
  if ((((options->countOnly == '\0') || (optionsMask == 5)) && ((ziS8)params->wordCharCount != '\0')) &&
     (result = Zi8IsCharacter(params->currentWord[0],work), result != '\0')) {
    phoneticLength = 0;
nextUserWord:
    do {
      do {
        do {
          wordIndex = Zi8MatchPUDdata(params->currentWord,params->wordCharCount,1,
                                  wordBuffer,0x40,0,phoneticLength,work);
          if ((wordIndex & 0xff) == 0) goto searchPhrases;
          phoneticLength = 1;
          wordBuffer[wordIndex & 0xff] = 0;
          candidateCharacter = wordBuffer[params->wordCharCount];
        } while (candidateCharacter == previousCharacter);
        previousCharacter = candidateCharacter;
        candidateOrdinal = Zi8Uni2Ord(candidateCharacter,work);
        phraseTable = syllableTable + (Zi8UInt)candidateOrdinal * 0xc;
        entryFlags = false;
        if (keyIndex != 1) {
          for (index = 0; index < 4; index = index + 1) {
            if (keyMasks[index + 4] != (keyMasks[index] & phraseTable[index])) {
              entryFlags = true;
              break;
            }
          }
        }
      } while (entryFlags);
      character = Zi8GetPCode(phoneticTable,phraseTable);
      elementIndex = Zi8IsMatch1Key(spelling,inputLimit,character,matchFull,tone,includeTone);
      if (((elementIndex == '\0') && (requireFull == 0)) && ((*phraseTable & 0x80) != 0)) {
        elementIndex = MatchAltSound1Key(spelling,inputLimit,matchFull,(Zi8AltSoundRecord *)alternateTable,phoneticMask,phoneticTable,candidateOrdinal,
                                      tone,includeTone,languageMask,work);
      }
    } while (elementIndex == '\0');
    if (emitWords) {
      wordLength = 0;
      for (wordIndex = (Zi8UInt)params->wordCharCount; wordBuffer[wordIndex] != 0; wordIndex = wordIndex + 1) {
        wordLength = wordLength + 1;
      }
      if ((prefixSearch != 0) || ((ziS8)params->elementCount != '\0')) {
        wordLength = 1;
      }
      result = Zi8IsDupWordW(wordBuffer + params->wordCharCount,wordLength,work);
      if (result != '\0') goto nextUserWord;
      wordBuffer[(Zi8UInt)params->wordCharCount + (Zi8UInt)wordLength] = 0;
    }
    else {
      if ((trackDuplicates) &&
         (result = Zi8SetFindCand(params->scratch,candidateOrdinal,work), result != '\0')
         ) goto nextUserWord;
      for (index = 0;
          (index < (int)(Zi8UInt)candidateCount && (candidateCharacter != output[index]));
          index = index + 1) {
      }
      if (index < (int)(Zi8UInt)candidateCount) goto nextUserWord;
    }
    if (optionsMask == 5) {
      totalCandidates = totalCandidates + 1;
      if (options->maxCount <= totalCandidates) goto finishCandidates;
    }
    else if (remaining == 0) {
      totalCandidates = totalCandidates + 1;
      candidateCount = candidateCount + 1;
      if (emitWords) {
        for (wordIndex = (Zi8UInt)params->wordCharCount; wordBuffer[wordIndex] != 0; wordIndex = wordIndex + 1) {
          output[outputIndex] = wordBuffer[wordIndex];
          outputIndex = outputIndex + 1;
        }
        output[outputIndex] = 0x20;
      }
      else {
        output[outputIndex] = candidateCharacter;
      }
      outputIndex = outputIndex + 1;
      if ((params->maxCandidates <= candidateCount) || (outputLimit < outputIndex)) goto finishUserWords;
    }
    else {
      remaining = remaining + -1;
    }
    goto nextUserWord;
  }
searchPhrases:
  if ((((options->countOnly == '\0') || (optionsMask == 5)) && (tableCursor == 0)) &&
     (((ziS8)params->wordCharCount != '\0' &&
      (result = Zi8IsCharacter(params->currentWord[0],work), result != '\0')))) {
    firstOrdinal = Zi8Uni2Ord(params->currentWord[0],work);
    if (firstOrdinal != 0xffff) {
      phraseTable = syllableTable + (Zi8UInt)firstOrdinal * 0xc;
      index = Zi8GetTableAddress(1,1,work);
      phraseEntries = (ziU8 *)(index + ((phraseTable[9] & 0xf) << 0x10 | (Zi8UInt)((Zi8PhraseRecord *)phraseTable)->phraseOffset));
      if ((ziS8)work->phraseEnabled != '\0') {
        mode = *phraseEntries & 7;
        if (mode == 5) {
          phraseEntries = phraseEntries + 4;
        }
        else if (mode < 5) {
          if (mode == 2) {
            phraseEntries = phraseEntries + 2;
          }
          else {
            if (mode < 2) goto skipPhraseHeader;
            phraseEntries = phraseEntries + 3;
          }
        }
        else {
skipPhraseHeader:
          phraseEntries = phraseEntries + 1;
        }
      }
      if ((*phraseEntries & 0x80) == 0) {
        entryRemaining = 0x80;
      }
      else {
        entryRemaining = 0;
        phraseEntries = phraseEntries + ((int)(*phraseEntries & 0x7f) >> 4) + 1;
      }
      while ((entryRemaining & 0x80) == 0) {
        recordCursor = phraseEntries + 1;
        entryRemaining = *phraseEntries;
        contextIndex = entryRemaining & 0xf;
        phraseEntries = recordCursor;
        if ((entryRemaining & languageMask) == 0) {
          for (; contextIndex != 0; contextIndex = contextIndex - 1) {
            for (phraseEntries = phraseEntries + 1; (*phraseEntries & 0x80) == 0; phraseEntries = phraseEntries + 2) {
            }
            phraseEntries = phraseEntries + 1;
          }
        }
        for (; contextIndex != 0; contextIndex = contextIndex - 1) {
          phoneticCount = 0;
          currentWord = params->currentWord;
          contextRemaining = params->wordCharCount;
          do {
            contextRemaining = contextRemaining + -1;
            if (contextRemaining == '\0') break;
            recordCursor = phraseEntries + 1;
            phoneticCount = CONCAT11(*recordCursor,*phraseEntries);
            phraseEntries = phraseEntries + 2;
            if ((*recordCursor & 0x80) != 0) break;
            contextCharacter = Zi8Ord2Uni(phoneticCount,work);
            currentWord = currentWord + 1;
          } while (*currentWord == contextCharacter);
          if (contextRemaining == '\0') {
            phoneticCount = CONCAT11(phraseEntries[1],*phraseEntries);
            entryCursor = phraseEntries;
            recordCursor = phraseEntries + 2;
            if (characterSetTable != 0) {
              index = 0;
              while( true ) {
                phraseCharacter = CONCAT11(phraseEntries[index + 1],phraseEntries[index]);
                if ((characterSet & characterSetTable[phraseCharacter & 0x7fff]) == 0) break;
                if ((phraseEntries[index + 1] & 0x80) != 0) goto finishPhraseContext;
                index = index + 2;
              }
              phraseCharacter = 0;
finishPhraseContext:
              phraseEntries = recordCursor;
              if ((phraseCharacter & 0x8000) == 0) goto nextPhrase;
            }
            phraseCharacter = phoneticCount & 0x7fff;
            phraseEntries = recordCursor;
            firstOrdinal = Zi8Ord2Uni(phraseCharacter,work);
            phraseTable = syllableTable + (Zi8UInt)phraseCharacter * 0xc;
            if (keyIndex != 1) {
              for (index = 0; index < 4; index = index + 1) {
                if (keyMasks[index + 4] != (keyMasks[index] & phraseTable[index])) goto nextPhrase;
              }
            }
            entryFlags = false;
            if (((ziS8)work->phoneticFilter != '\0') &&
               (tableIndex = (ziU16)phraseTable[8] << 1 | (ziU16)((int)(phraseTable[9] & 0x80) >> 7),
               work->phoneticEnabled[(Zi8UInt)tableIndex] == '\0')) {
              entryFlags = true;
            }
            if (entryFlags) {
              elementIndex = '\0';
            }
            else {
              character = Zi8GetPCode(phoneticTable,phraseTable);
              elementIndex = Zi8IsMatch1Key(spelling,inputLimit,character,matchFull,tone,includeTone);
            }
            if (((elementIndex == '\0') && (requireFull == 0)) && ((*phraseTable & 0x80) != 0)) {
              elementIndex = MatchAltSound1Key(spelling,inputLimit,matchFull,(Zi8AltSoundRecord *)alternateTable,phoneticMask,phoneticTable,
                                            phraseCharacter,tone,includeTone,languageMask,work);
            }
            if (elementIndex != '\0') {
              if (emitWords) {
                wordLength = 0;
                do {
                  phraseCharacter = CONCAT11(entryCursor[1],*entryCursor);
                  entryCursor = entryCursor + 2;
                  character = Zi8Ord2Uni(phraseCharacter & 0x7fff,work);
                  wordIndex = (Zi8UInt)wordLength;
                  wordLength = wordLength + 1;
                  output[(outputIndex + wordIndex)] = character;
                } while ((phraseCharacter & 0x8000) == 0);
                if ((prefixSearch != 0) || ((ziS8)params->elementCount != '\0')) {
                  wordLength = 1;
                }
                result = Zi8IsDupWordW(output + outputIndex,wordLength,work);
                if (result == '\0') {
                  output[(outputIndex + (Zi8UInt)wordLength)] = 0;
                  goto appendPhrase;
                }
              }
              else if ((!trackDuplicates) ||
                      (result = Zi8SetFindCand(params->scratch,phraseCharacter,work),
                      result == '\0')) {
                for (index = 0; index < (int)(Zi8UInt)candidateCount; index = index + 1) {
                  if (firstOrdinal == output[index]) goto nextPhrase;
                }
appendPhrase:
                if (optionsMask == 5) {
                  totalCandidates = totalCandidates + 1;
                  if (options->maxCount <= totalCandidates) goto finishCandidates;
                }
                else if (remaining == 0) {
                  totalCandidates = totalCandidates + 1;
                  candidateCount = candidateCount + 1;
                  if (emitWords) {
                    outputIndex = outputIndex + (Zi8UInt)wordLength;
                    output[outputIndex] = 0x20;
                  }
                  else {
                    output[outputIndex] = firstOrdinal;
                  }
                  outputIndex = outputIndex + 1;
                  if ((params->maxCandidates <= candidateCount) || (outputLimit < outputIndex)) {
                    params->wordCandidates = candidateCount;
                    goto finishCandidates;
                  }
                }
                else {
                  remaining = remaining + -1;
                }
              }
            }
          }
nextPhrase:
          if ((phoneticCount & 0x8000) == 0) {
            for (phraseEntries = phraseEntries + 1; (*phraseEntries & 0x80) == 0; phraseEntries = phraseEntries + 2) {
            }
            phraseEntries = phraseEntries + 1;
          }
        }
      }
      goto finishPhrases;
    }
  }
  else {
finishPhrases:
    if ((ziS8)params->wordCharCount != '\0') {
      params->wordCandidates = candidateCount;
    }
  }
  if ((options->countOnly == '\0') && (tableCursor != 0)) {
    for (ordinalIndex = 0; ordinalIndex < tableCursor; ordinalIndex = ordinalIndex + 1) {
      ordinal = (ziU16)ordinalTable[(Zi8UInt)ordinalIndex * 2] * 0x100 +
                 (ziU16)ordinalTable[(Zi8UInt)ordinalIndex * 2 + 1];
      phraseTable = syllableTable + (Zi8UInt)ordinal * 0xc;
      if (((*phraseTable & languageMask) != 0) &&
         ((characterSetTable == 0 || ((characterSet & characterSetTable[(Zi8UInt)ordinal]) != 0)))) {
        if (keyIndex != 1) {
          for (index = 0;
              (index < 4 && (keyMasks[index + 4] == (keyMasks[index] & phraseTable[index])));
              index = index + 1) {
          }
          if (index < 4) goto nextSortedOrdinal;
        }
        entryFlags = false;
        if (((ziS8)work->phoneticFilter != '\0') &&
           (tableIndex = (ziU16)phraseTable[8] << 1 | (ziU16)((int)(phraseTable[9] & 0x80) >> 7),
           work->phoneticEnabled[(Zi8UInt)tableIndex] == '\0')) {
          entryFlags = true;
        }
        if (entryFlags) {
          elementIndex = '\0';
        }
        else {
          character = Zi8GetPCode(phoneticTable,phraseTable);
          elementIndex = Zi8IsMatch1Key(spelling,inputLimit,character,matchFull,tone,includeTone);
        }
        if (((elementIndex == '\0') && (requireFull == 0)) && ((syllableTable[(Zi8UInt)ordinal * 0xc] & 0x80) != 0))
        {
          elementIndex = MatchAltSound1Key(spelling,inputLimit,matchFull,(Zi8AltSoundRecord *)alternateTable,phoneticMask,phoneticTable,ordinal,
                                        tone,includeTone,languageMask,work);
        }
        if (elementIndex != '\0') {
          if (emitWords) {
            ordinal = Zi8Ord2Uni(ordinal,work);
            result = Zi8IsDupWordW(&ordinal,1,work);
            if (result == '\0') {
appendSortedOrdinal:
              if (remaining == 0) {
                totalCandidates = totalCandidates + 1;
                if (options->countOnly == '\0') {
                  candidateCount = candidateCount + 1;
                  output[outputIndex] = ordinal;
                  index = outputIndex + 1;
                  if (emitWords) {
                    output[(outputIndex + 1)] = 0x20;
                    index = outputIndex + 2;
                  }
                }
                else {
                  index = outputIndex;
                  if (options->maxCount <= totalCandidates) goto finishCandidates;
                }
                outputIndex = index;
                if ((params->maxCandidates <= candidateCount) || (outputLimit < outputIndex))
                goto finishCandidates;
              }
              else {
                remaining = remaining + -1;
              }
            }
          }
          else if ((!trackDuplicates) ||
                  (result = Zi8SetFindCand(params->scratch,ordinal,work),
                  result == '\0')) {
            ordinal = Zi8Ord2Uni(ordinal,work);
            for (index = 0;
                (index < (int)(Zi8UInt)candidateCount && (ordinal != output[index]));
                index = index + 1) {
            }
            if ((int)(Zi8UInt)candidateCount <= index) goto appendSortedOrdinal;
          }
        }
      }
nextSortedOrdinal:
    ;
    }
  }
  if ((options->countOnly == '\0') && (result = Zi8GetZHuwdPtr(&userEntries,&userCount,work), result != '\0'))
  {
    for (phraseOrdinal = 0; phraseOrdinal < userCount; phraseOrdinal = phraseOrdinal + 1) {
      if (((ziS8)params->elementCount == '\0') || ((userEntries[1] & 0x80) != 0)) {
        userOrdinal = (userEntries[1] & 0x7f) << 8 | (ziU16)userEntries[2];
        phraseTable = syllableTable + (Zi8UInt)userOrdinal * 0xc;
        if (((*phraseTable & languageMask) != 0) &&
           ((characterSetTable == 0 || ((characterSet & characterSetTable[(Zi8UInt)userOrdinal]) != 0)))) {
          if (keyIndex != 1) {
            entryFlags = false;
            for (duplicateIndex = 0; duplicateIndex < 4; duplicateIndex = duplicateIndex + 1) {
              if (keyMasks[duplicateIndex + 4] != (keyMasks[duplicateIndex] & phraseTable[duplicateIndex])) {
                entryFlags = true;
                break;
              }
            }
            if (entryFlags) goto nextUserOrdinal;
          }
          character = Zi8GetPCode(phoneticTable,phraseTable);
          elementIndex = Zi8IsMatch1Key(spelling,inputLimit,character,matchFull,tone,includeTone);
          if (((elementIndex == '\0') && (requireFull == 0)) && ((*phraseTable & 0x80) != 0)) {
            elementIndex = MatchAltSound1Key(spelling,inputLimit,matchFull,(Zi8AltSoundRecord *)alternateTable,phoneticMask,phoneticTable,userOrdinal,
                                          tone,includeTone,languageMask,work);
          }
          if (elementIndex != '\0') {
            if (emitWords) {
              userCharacter = Zi8Ord2Uni(userOrdinal,work);
              result = Zi8IsDupWordW(&userCharacter,1,work);
              if (result == '\0') {
appendUserOrdinal:
                if (remaining == 0) {
                  totalCandidates = totalCandidates + 1;
                  candidateCount = candidateCount + 1;
                  output[outputIndex] = userCharacter;
                  index = outputIndex + 1;
                  if (emitWords) {
                    output[(outputIndex + 1)] = 0x20;
                    index = outputIndex + 2;
                  }
                  outputIndex = index;
                  if ((params->maxCandidates <= candidateCount) || (outputLimit < outputIndex))
                  goto finishCandidates;
                }
                else {
                  remaining = remaining + -1;
                }
              }
            }
            else if ((!trackDuplicates) ||
                    (result = Zi8SetFindCand(params->scratch,userOrdinal,work),
                    result == '\0')) {
              userCharacter = Zi8Ord2Uni(userOrdinal,work);
              for (duplicateIndex = 0;
                  (duplicateIndex < (int)(Zi8UInt)candidateCount &&
                  (userCharacter != output[duplicateIndex])); duplicateIndex = duplicateIndex + 1) {
              }
              if ((int)(Zi8UInt)candidateCount <= duplicateIndex) goto appendUserOrdinal;
            }
          }
        }
      }
nextUserOrdinal:
      userEntries = userEntries + 3;
    }
  }
  phraseTable = syllableTable;
  previousCharacter = 0;
  for (ordinal = 0; ordinal < ordinalCount; ordinal = ordinal + 1) {
    if (((*phraseTable & languageMask) != 0) &&
       ((characterSetTable == 0 || ((characterSet & characterSetTable[(Zi8UInt)ordinal]) != 0)))) {
      if (keyIndex != 1) {
        for (index = 0; (index < 4 && (keyMasks[index + 4] == (keyMasks[index] & phraseTable[index])));
            index = index + 1) {
        }
        if (index < 4) goto nextOrdinal;
      }
      entryFlags = false;
      if (((ziS8)work->phoneticFilter != '\0') &&
         (tableIndex = (ziU16)phraseTable[8] << 1 | (ziU16)((int)(phraseTable[9] & 0x80) >> 7),
         work->phoneticEnabled[(Zi8UInt)tableIndex] == '\0')) {
        entryFlags = true;
      }
      if (entryFlags) {
        elementIndex = '\0';
      }
      else {
        character = Zi8GetPCode(phoneticTable,phraseTable);
        elementIndex = Zi8IsMatch1Key(spelling,inputLimit,character,matchFull,tone,includeTone);
      }
      if (((elementIndex == '\0') && (requireFull == 0)) && ((*phraseTable & 0x80) != 0)) {
        elementIndex = MatchAltSound1Key(spelling,inputLimit,matchFull,(Zi8AltSoundRecord *)alternateTable,phoneticMask,phoneticTable,ordinal,
                                      tone,includeTone,languageMask,work);
      }
      if ((elementIndex != '\0') &&
         (unicodeCharacter = (ziU16)phraseTable[6] * 0x100 + (ziU16)phraseTable[7], unicodeCharacter != previousCharacter)) {
        previousCharacter = unicodeCharacter;
        if (emitWords) {
          result = Zi8IsDupWordW(&unicodeCharacter,1,work);
          if (result == '\0') {
appendOrdinal:
            if (remaining == 0) {
              totalCandidates = totalCandidates + 1;
              if (options->countOnly == '\0') {
                candidateCount = candidateCount + 1;
                output[outputIndex] = unicodeCharacter;
                index = outputIndex + 1;
                if (emitWords) {
                  output[(outputIndex + 1)] = 0x20;
                  index = outputIndex + 2;
                }
              }
              else {
                index = outputIndex;
                if (options->maxCount <= totalCandidates) break;
              }
              outputIndex = index;
              if ((params->maxCandidates <= candidateCount) || (outputLimit < outputIndex)) break;
            }
            else {
              remaining = remaining + -1;
            }
          }
        }
        else if ((!trackDuplicates) ||
                (result = Zi8SetFindCand(params->scratch,ordinal,work),
                result == '\0')) {
          for (index = 0;
              (index < (int)(Zi8UInt)candidateCount && (unicodeCharacter != output[index]));
              index = index + 1) {
          }
          if ((int)(Zi8UInt)candidateCount <= index) goto appendOrdinal;
        }
      }
    }
nextOrdinal:
    phraseTable = phraseTable + 0xc;
  }
finishCandidates:
  if ((emitWords) && (outputIndex != 0)) {
    output[outputIndex] = 0;
    outputIndex = outputIndex + 1;
  }
  params->count = candidateCount;
  Zi8LogError(100,work);
  return totalCandidates;
finishOEMwords:
  params->wordCandidates = candidateCount;
  goto finishCandidates;
finishUserWords:
  params->wordCandidates = candidateCount;
  goto finishCandidates;
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
