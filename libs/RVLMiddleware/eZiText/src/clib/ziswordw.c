#include <stddef.h>
#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>

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

ziU32 Zi8GetCandidatesOrCount(ziGetParam*, ziSearchState* ZI_NEED_WORK);
ziU8 Zi8GetFormatVersion(ziU8 ZI_NEED_WORK);
ziPtr Zi8GetTableAddress(ziU8, ziU8 ZI_NEED_WORK);
ziU16 Zi8Uni2Ord(ziWChar ZI_NEED_WORK);

ziBool Zi8IsWordW(ziWChar* word, ziU8 language ZI_NEED_WORK) {
    ziChineseEntry* table = 0;
    ziU8* baseData = 0;
    ziU8 group = 0;
    ziU8 remaining = 0;
    ziU16 value = 0;
    ziGetParam request;
    ziWChar ordinals[65];
    int count;
    int countLeft;
    ziChineseEntry* entry;
    ziWChar* cursor;
    ziU8* data;
    ziU8 formats[8] = {1, 5, 0, 0, 0, 0, 0, 0};
    ziU32 savedFormats = ZI_WORK->unk_0x1410;
    ziU8 savedCount = ZI_WORK->unk_0x1418;
    ziSearchState search = {0};
    Zi8LogError(100, __zi8_work_data);
    if (word == 0 || *word == 0) {
        Zi8ReplaceLastError(300, __zi8_work_data);
        return 0;
    }
    if (language != 1) {
        for (count = 0; word[count] != 0; count++) {
            if (word[count] >= 0xEFF1 || count == 64) return 0;
        }
        ((ziU8*)&search.length)[0] = count;
        ((ziU8*)&search.flags)[2] = 1;
        search.word = word;
        ((ziU16*)&search.capacity)[0] = 64;
        request.language = language;
        request.getMode = 0;
        request.subLanguage = 7;
        request.context = 1;
        request.getOptions = 0x81;
        request.elements = word;
        request.elementCount = count;
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
        } else if (ZI_WORK->unk_0x1C[0] != 0) ZI_WORK->unk_0x1418 = 2;
        else ZI_WORK->unk_0x1418 = 1;
        count = Zi8GetCandidatesOrCount(&request, &search, __zi8_work_data);
        ZI_WORK->unk_0x1410 = savedFormats;
        ZI_WORK->unk_0x1418 = savedCount;
        if (count != 0) return 1;
    }
    if (language != 1) {
        Zi8ReplaceLastError(0x26C, __zi8_work_data);
        return 0;
    }
    {
        count = 0;
        while (word[count] != 0) {
            ordinals[count] = Zi8Uni2Ord(word[count], __zi8_work_data);
            if (ordinals[count] == 0xFFFF) return 0;
            count++;
            if (count == 64) return 0;
        }
        {
                if (count-- == 1) return 1;
                ordinals[count] |= 0x8000;
                ZI_WORK->cangjieEnabled = Zi8GetFormatVersion(1, __zi8_work_data) & 2;
                table = (ziChineseEntry*)Zi8GetTableAddress(1, 0, __zi8_work_data);
                entry = table + ordinals[0];
                baseData = (ziU8*)Zi8GetTableAddress(1, 1, __zi8_work_data);
                baseData += ((entry->offsetHigh & 15) << 16 | (entry->offsetLow[1] | (entry->offsetLow[0] << 8)));
                data = baseData;
                if (ZI_WORK->cangjieEnabled != 0) {
                    switch (*data & 7) {
                    case 2:
                        countLeft = 2;
                        break;
                    case 3:
                    case 4:
                        countLeft = 3;
                        break;
                    case 5:
                        countLeft = 4;
                        break;
                    default:
                        countLeft = 1;
                        break;
                    }
                    data += countLeft;
                }
                if ((*data & 0x80) != 0) {
                    group = 0;
                    data += ((*data & 0x7F) >> 4) + 1;
                } else return 0;
                while ((group & 0x80) == 0) {
                    group = *data++;
                    for (remaining = group & 15; remaining != 0; remaining--) {
                        countLeft = count;
                        cursor = ordinals;
                        while (countLeft > 0) {
                            value = (data[1] << 8) | data[0];
                            data += 2;
                            cursor++;
                            if (value != *cursor) break;
                            countLeft--;
                            if (value & 0x8000) break;
                        }
                        if (countLeft == 0) return 1;
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
    }
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
