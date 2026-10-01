#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>
#include <zi8clib/zconvert.h>
#include <zi8clib/zmtkey.h>

typedef struct ziUserWord {
    ziU8 size, language, length, priority;
    ziU8 text[1];
} ziUserWord;
typedef struct ziUserDictionary {
    ziU16 flags, end, current, boundary;
    ziU8 entries[1];
} ziUserDictionary;
void Zi8Memset(ziPtr, ziU32, ziU32);

ziBool Zi8_81480224(ziUserWord* word ZI_NEED_WORK) {
    ziU8 length;
    ziU8 position;
    ziUwdNode* previous;
    ziUwdNode* current;
    ziUwdNode* added;
    ziUserWord* candidate;
    if (ZI_WORK->uwdCount >= 32) {
        Zi8LogError(0x19D, __zi8_work_data);
        return 0;
    }
    if (word == 0) {
        Zi8LogError(0x19F, __zi8_work_data);
        return 0;
    }
    length = word->length;
    if (length == 0) {
        Zi8LogError(0x193, __zi8_work_data);
        return 0;
    }
    if (length > 63) {
        Zi8LogError(0x194, __zi8_work_data);
        return 0;
    }
    previous = 0;
    current = ZI_WORK->uwdList;
    while (current != 0) {
        candidate = (ziUserWord*)current->word;
        if (ZI_WORK->unk_0x12E == 1 && word->priority > candidate->priority) break;
        if (candidate->length == length) {
            position = 0;
            while (position < length) {
                if (candidate->text[position] != word->text[position]) break;
                position++;
            }
            if (position == length) {
                Zi8LogError(100, __zi8_work_data);
                return 0;
            }
        }
        previous = current;
        current = current->next;
    }
    length = ZI_WORK->uwdCount++;
    added = &ZI_WORK->uwdNodes[length];
    if (previous == 0) {
        ZI_WORK->uwdList = added;
        added->next = current;
    } else {
        previous->next = added;
        added->next = current;
    }
    added->word = (ziU8*)word;
    Zi8LogError(100, __zi8_work_data);
    return 1;
}
ziUserWord* Zi8_814803F4(ziPtr __zi8_work_data) {
    ziUserWord* word;
    if (ZI_WORK->uwdCount != 0) {
        ZI_WORK->uwdCount--;
        word = (ziUserWord*)ZI_WORK->uwdList->word;
        ZI_WORK->uwdList = ZI_WORK->uwdList->next;
        Zi8LogError(100, __zi8_work_data);
        return word;
    }
    Zi8LogError(0x19E, __zi8_work_data);
    return 0;
}
void Zi8_8148047C(ziPtr __zi8_work_data) {
    Zi8Memset(ZI_WORK->uwdNodes, 0, sizeof(ZI_WORK->uwdNodes));
    ZI_WORK->uwdCount = 0;
    ZI_WORK->uwdList = 0;
}
ziU8 Zi8MatchUWDdata(ziWChar* pattern, ziU8 length, ziWChar* currentWord, ziU16 currentLength, ziU8 language, ziWChar* output, ziU16 capacity, ziU8 complete, ziU8 continuation ZI_NEED_WORK) {
    ziWChar folded;
    int fallback = 0;
    int visited = 0;
    int prefixLength;
    int position, previousOffset;
    ziU32 size;
    ziU8 entryLanguage;
    ziU32 entryLength;
    ziU8* cursor;
    ziU8* begin;
    ziU8* boundary;
    ziU8* end;
    ziUserWord* candidate;
    ziUserWord* previous;
    ziUserWord* result;
    ziUserDictionary* dictionary;
    int firstSegment;
    Zi8LogError(100, __zi8_work_data);
    if (!(ZI_WORK->unk_0x138 <= 2 && ZI_WORK->unk_0x138 != 0 && ZI_WORK->unk_0x130[ZI_WORK->unk_0x138 - 1] != 0)) {
        Zi8ReplaceLastError(0x19C, __zi8_work_data);
        return 0;
    }
    dictionary = ZI_WORK->unk_0x130[ZI_WORK->unk_0x138 - 1];
    if (continuation != 0) {
        result = Zi8_814803F4(__zi8_work_data);
        entryLength = 0;
        if (result != 0) {
            entryLanguage = result->language;
            entryLength = result->length;
            if (entryLength >= capacity) {
                Zi8_8148047C(__zi8_work_data);
                return 0;
            }
            for (position = 0; position < (ziS32)entryLength; position++) output[position] = Zi8ConvertUC2WC(result->text[position], entryLanguage, __zi8_work_data);
        }
        return entryLength;
    }
    {
        Zi8_8148047C(__zi8_work_data);
        ZI_WORK->unk_0x13C = 0;
        if (currentWord == 0 || currentLength == 0 || currentWord[currentLength - 1] != 0x20) ZI_WORK->unk_0x140 = 0;
        else {
            prefixLength = 0;
            for (position = currentLength - 2; currentWord[position] != 0x20 && position >= 0; position--) prefixLength++;
            position++;
            if (prefixLength == 0 || prefixLength > 63) ZI_WORK->unk_0x140 = 0;
            else {
                ZI_WORK->unk_0x140 = 1;
                ZI_WORK->unk_0x141[0] = prefixLength + 5;
                ZI_WORK->unk_0x141[prefixLength + 4] = prefixLength + 5;
                ZI_WORK->unk_0x141[1] = language;
                ZI_WORK->unk_0x141[2] = prefixLength;
                previousOffset = 4;
                for (; prefixLength > 0; prefixLength--, position++) {
                    folded = currentWord[position];
                    ZI_WORK->unk_0x141[previousOffset] = Zi8ConvertWC2UC(folded, language, __zi8_work_data);
                    ZI_WORK->unk_0x184[previousOffset] = 0;
                    if (ZI_WORK->unk_0x1F != 0) {
                        if (!Zi8ChangeCharCase(1, &folded, language, __zi8_work_data)) Zi8ChangeCharCase(0, &folded, language, __zi8_work_data);
                        ZI_WORK->unk_0x184[previousOffset] = Zi8ConvertWC2UC(folded, language, __zi8_work_data);
                    }
                    if (ZI_WORK->unk_0x141[previousOffset++] == 0) {
                        ZI_WORK->unk_0x140 = 0;
                        break;
                    }
                }
            }
        }
        if (ZI_WORK->unk_0x140 == 0 && length == 0) return 0;
rescan:
        begin = dictionary->entries + dictionary->current;
        boundary = (ziU8*)dictionary + dictionary->boundary + 7;
        end = (ziU8*)dictionary + dictionary->end + 7;
        cursor = begin;
        if (begin < boundary) firstSegment = 1;
        else firstSegment = 0;
        while (firstSegment ? cursor < boundary : cursor < end) {
            size = *cursor;
            candidate = (ziUserWord*)cursor;
            position = visited++;
            if ((ziS32)ZI_WORK->unk_0x13C <= position && (size & 0xC0) == 0) {
                previous = (ziUserWord*)(cursor + size);
                if ((ziU8*)previous > end) previous = (ziUserWord*)(cursor + ((ziU8*)dictionary - end) + 7);
                entryLanguage = candidate->language;
                entryLength = candidate->length;
                if (entryLanguage == language && length <= entryLength && entryLength < capacity && (complete == 0 || entryLength == length) && (complete != 0 || entryLength != length)) {
                    for (position = 0; position < length; position++) {
                        if (pattern[position] < 0xEFF1 || pattern[position] > 0xF010) {
                            folded = Zi8ConvertUC2WC(candidate->text[position], language, __zi8_work_data);
                            if (folded != pattern[position] && (!ZI_WORK->unk_0x1F || !Zi8ChangeCharCase(0, &folded, language, __zi8_work_data) || folded != pattern[position])) goto next;
                        } else if (pattern[position] != Zi8ConvertUC2Key(candidate->text[position], language, __zi8_work_data)) goto next;
                    }
                    if (ZI_WORK->unk_0x140 != 0) {
                        if (ZI_WORK->unk_0x141[0] != previous->size || ZI_WORK->unk_0x141[1] != previous->language || ZI_WORK->unk_0x141[2] != previous->length) goto next;
                        for (position = 4; position < ZI_WORK->unk_0x141[2] + 4; position++) {
                            if (ZI_WORK->unk_0x141[position] != ((ziU8*)previous)[position] && ZI_WORK->unk_0x184[position] != ((ziU8*)previous)[position]) goto next;
                        }
                    }
                    Zi8_81480224(candidate, __zi8_work_data);
                }
            }
next:
            cursor += size;
            if (end < cursor) {
                if (firstSegment) break;
                firstSegment = 1;
                cursor = dictionary->entries + (cursor - end - 1);
            }
        }
        if (ZI_WORK->unk_0x140 != 0 && length != 0) {
            ZI_WORK->unk_0x140 = 0;
            visited = 0;
            goto rescan;
        }
        if (complete == 1 && length != 0 && continuation == 0) {
            complete = 0;
            fallback = 1;
            visited = 0;
            goto rescan;
        }
    }
    result = Zi8_814803F4(__zi8_work_data);
    entryLength = 0;
    if (result != 0) {
        entryLanguage = result->language;
        entryLength = result->length;
        if (entryLength >= capacity) {
            Zi8_8148047C(__zi8_work_data);
            return 0;
        }
        for (position = 0; position < (ziS32)entryLength; position++) output[position] = Zi8ConvertUC2WC(result->text[position], entryLanguage, __zi8_work_data);
    }
    return entryLength;
}
