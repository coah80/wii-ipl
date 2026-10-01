#include <stddef.h>
#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>

__declspec(section ".sdata2") ziU8 ziWordFormat0 = 1;
__declspec(section ".sdata2") ziU8 ziWordFormat1 = 5;
__declspec(section ".sdata2") ziU8 ziWordFormat2 = 0;
__declspec(section ".sdata2") ziU8 ziWordFormat3 = 0;
__declspec(section ".sdata2") ziU8 ziWordFormat4 = 0;
__declspec(section ".sdata2") ziU8 ziWordFormat5 = 0;
__declspec(section ".sdata2") ziU8 ziWordFormat6 = 0;
__declspec(section ".sdata2") ziU8 ziWordFormat7 = 0;

typedef struct ziSearchState {
    ziU32 flags;
    ziWChar* word;
    ziU32 length;
    ziU32 position;
    ziU32 capacity;
    ziU32 options;
} ziSearchState;
typedef struct ziUserKeys {
    ziWChar* upper[32];
    ziWChar* lower[32];
} ziUserKeys;
typedef struct ziChineseEntry {
    ziU8 data[9];
    ziU8 offsetHigh;
    ziU8 offsetLow[2];
} ziChineseEntry;

ziU8 Zi8GetCandidatesOrCount(ziGetParam*, ziSearchState* ZI_NEED_WORK);
ziU8 Zi8GetFormatVersion(ziU8 ZI_NEED_WORK);
ziPtr Zi8GetTableAddress(ziU8, ziU8 ZI_NEED_WORK);
ziU16 Zi8Uni2Ord(ziWChar ZI_NEED_WORK);

ziBool Zi8IsWordW(ziWChar* word, ziU8 language ZI_NEED_WORK) {
    int count = 0;
    int offset = 0;
    ziU8 group = 0;
    ziU8 remaining = 0;
    ziU16 value = 0;
    ziWChar* cursor;
    ziSearchState search;
    ziGetParam request;
    ziWChar ordinals[65];
    int length;
    int unmatched;
    ziChineseEntry* entry;
    ziU8* data;
    ziU8 formats[8];
    ziU32 savedFormats;
    ziU8 savedCount;
    formats[0] = ziWordFormat0;
    formats[1] = ziWordFormat1;
    formats[2] = ziWordFormat2;
    formats[3] = ziWordFormat3;
    formats[4] = ziWordFormat4;
    formats[5] = ziWordFormat5;
    formats[6] = ziWordFormat6;
    formats[7] = ziWordFormat7;
    savedFormats = ZI_WORK->unk_0x1410;
    savedCount = ZI_WORK->unk_0x1418;
    search.flags = 0;
    search.word = 0;
    search.length = 0;
    search.position = 0;
    search.capacity = 0;
    search.options = 0;
    Zi8LogError(100, __zi8_work_data);
    if (word == 0 || *word == 0) {
        Zi8ReplaceLastError(300, __zi8_work_data);
        return 0;
    }
    if (language != 1) {
        for (length = 0; word[length] != 0; length++) {
            if (word[length] >= 0xEFF1 || length == 64) return 0;
        }
        ((ziU8*)&search.length)[0] = length;
        ((ziU8*)&search.flags)[2] = 1;
        ((ziU16*)&search.capacity)[0] = 64;
        search.word = word;
        request.language = language;
        request.getMode = 0;
        request.subLanguage = 7;
        request.context = 1;
        request.getOptions = 0x81;
        request.elements = word;
        request.elementCount = length;
        request.currentWord = 0;
        request.wordCharCount = 0;
        request.candidates = ordinals;
        request.maxCandidates = 1;
        request.firstCandidate = 0;
        ZI_WORK->unk_0x1410 = (ziU32)formats;
        if (ZI_WORK->unk_0x1C[0] == 2) {
            ZI_WORK->unk_0x1418 = 0;
            if (ZI_WORK->unk_0x09 & 1) formats[ZI_WORK->unk_0x1418++] = 1;
            if (ZI_WORK->unk_0x09 & 4) formats[ZI_WORK->unk_0x1418++] = 2;
            if (ZI_WORK->unk_0x09 & 2) formats[ZI_WORK->unk_0x1418++] = 3;
            if (ZI_WORK->unk_0x09 & 8) formats[ZI_WORK->unk_0x1418++] = 4;
            if (ZI_WORK->unk_0x09 & 1) formats[ZI_WORK->unk_0x1418++] = 5;
            if (ZI_WORK->unk_0x09 & 4) formats[ZI_WORK->unk_0x1418++] = 6;
            if (ZI_WORK->unk_0x09 & 2) formats[ZI_WORK->unk_0x1418++] = 7;
            if (ZI_WORK->unk_0x09 & 8) formats[ZI_WORK->unk_0x1418++] = 8;
        } else if (ZI_WORK->unk_0x1C[0] == 0) ZI_WORK->unk_0x1418 = 1;
        else ZI_WORK->unk_0x1418 = 2;
        count = Zi8GetCandidatesOrCount(&request, &search, __zi8_work_data);
        ZI_WORK->unk_0x1410 = savedFormats;
        ZI_WORK->unk_0x1418 = savedCount;
        if (count != 0) return 1;
    }
    if (language == 1) {
        length = 0;
        do {
            ordinals[length] = Zi8Uni2Ord(word[length], __zi8_work_data);
            if (ordinals[length] == 0xFFFF) return 0;
            length++;
            if (length == 64) return 0;
        } while (word[length] != 0);
        {
                if (length == 1) return 1;
                count = --length;
                ordinals[count] |= 0x8000;
                ZI_WORK->unk_0x16 = Zi8GetFormatVersion(1, __zi8_work_data) & 2;
                entry = (ziChineseEntry*)Zi8GetTableAddress(1, 0, __zi8_work_data) + ordinals[0];
                data = (ziU8*)Zi8GetTableAddress(1, 1, __zi8_work_data) + ((entry->offsetHigh & 15) << 16 | ((entry->offsetLow[0] << 8) | entry->offsetLow[1]));
                if (ZI_WORK->unk_0x16 != 0) {
                    switch (*data & 7) {
                    case 2:
                        offset = 2;
                        break;
                    case 3:
                    case 4:
                        offset = 3;
                        break;
                    case 5:
                        offset = 4;
                        break;
                    default:
                        offset = 1;
                        break;
                    }
                    data += offset;
                }
                if ((*data & 0x80) == 0) return 0;
                group = 0;
                data += ((*data & 0x7F) >> 4) + 1;
                while ((group & 0x80) == 0) {
                    group = *data++;
                    for (remaining = group & 15; remaining != 0; remaining--) {
                        unmatched = count;
                        cursor = ordinals;
                        while (unmatched > 0) {
                            value = data[0] | (data[1] << 8);
                            data += 2;
                            cursor++;
                            if (value != *cursor) break;
                            unmatched--;
                            if (value & 0x8000) break;
                        }
                        if (unmatched == 0) return 1;
                        if (!(value & 0x8000)) {
                            data++;
                            while (!(*data & 0x80)) data += 2;
                            data++;
                        }
                    }
                }
                Zi8LogError(0x2BD, __zi8_work_data);
                return 0;
        }
    } else Zi8ReplaceLastError(0x26C, __zi8_work_data);
    return 0;
}
ziWChar Zi8ConvertUC2UserKey(ziChar character, ziU8 language ZI_NEED_WORK) {
    ziUserKeys* keys;
    ziU16 key;
    ziWChar* cursor;
    if (character == 0 || language > 0x82 || (keys = ZI_WORK->userKeys[language]) == 0) return 0;
    for (key = 0; key < 32; key++) {
        for (cursor = keys->lower[key]; cursor != 0 && *cursor != 0; cursor++) {
            if ((ziU16)*cursor == (ziU16)character) goto found;
        }
        for (cursor = keys->upper[key]; cursor != 0 && *cursor != 0; cursor++) {
            if ((ziU16)*cursor == (ziU16)character) goto found;
        }
    }
found:
    if (key >= 32) return 0;
    if (key == 0) return 0xEFFA;
    if (key >= 1 && key <= 9) return key + 0xEFF0;
    if (key <= 31) return key + 0xEFF1;
    return 0;
}
