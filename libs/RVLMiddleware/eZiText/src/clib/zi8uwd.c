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
    ziUwdNode* previous;
    ziUwdNode* current;
    ziUwdNode* added;
    ziUserWord* candidate;
    ziU8 position;
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
        if (ZI_WORK->uwdPrioritySort == 1 && candidate->priority < word->priority) break;
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
    added = &ZI_WORK->uwdNodes[ZI_WORK->uwdCount++];
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
    ziUserDictionary* dictionary;
    ziU8* cursor;
    ziU8* begin;
    ziU8* boundary;
    ziU8* end;
    ziUserWord* previous;
    int firstSegment;
    ziU32 size;
    int headerSize;
    int entryLanguage;
    volatile int entryLength;
    int previousOffset;
    int visited = 0;
    int fallback = 0;
    ziWChar folded;
    ziU8* text;
    int position;
    int prefixLength;
    Zi8LogError(100, __zi8_work_data);
    if (!(ZI_WORK->uwdDictCount <= 2 && ZI_WORK->uwdDictCount != 0 && ZI_WORK->uwdDicts[ZI_WORK->uwdDictCount - 1] != 0)) {
        Zi8ReplaceLastError(0x19C, __zi8_work_data);
        return 0;
    }
    dictionary = ZI_WORK->uwdDicts[ZI_WORK->uwdDictCount - 1];
    if (continuation != 0) {
        text = (ziU8*)Zi8_814803F4(__zi8_work_data);
        entryLength = 0;
        if (text != 0) {
            language = ((ziUserWord*)text)->language;
            entryLength = ((ziUserWord*)text)->length;
            if (entryLength >= capacity) {
                Zi8_8148047C(__zi8_work_data);
                return 0;
            }
            text = ((ziUserWord*)text)->text;
        for (position = 0; position < (ziS32)entryLength; position++) output[position] = Zi8ConvertUC2WC(text[position], language, __zi8_work_data);
        }
        return entryLength;
    }
    {
        Zi8_8148047C(__zi8_work_data);
        ZI_WORK->unk_0x13C = 0;
        if (currentWord == 0 || currentLength == 0 || currentWord[currentLength - 1] != 0x20) ZI_WORK->unk_0x140 = 0;
        else {
            prefixLength = 0;
            for (position = currentLength - 2; position >= 0;) {
                if (currentWord[position] == 0x20) break;
                position--;
                prefixLength++;
            }
            position++;
            if (prefixLength == 0 || prefixLength > 63) ZI_WORK->unk_0x140 = 0;
            else {
                ZI_WORK->unk_0x140 = 1;
                ZI_WORK->unk_0x141[prefixLength + 4] = ZI_WORK->unk_0x141[0] = prefixLength + 5;
                ZI_WORK->unk_0x141[1] = language;
                ZI_WORK->unk_0x141[2] = prefixLength;
                previousOffset = 4;
                while (prefixLength > 0) {
                    folded = currentWord[position];
                    ZI_WORK->unk_0x141[previousOffset] = Zi8ConvertWC2UC(folded, language, __zi8_work_data);
                    ZI_WORK->unk_0x184[previousOffset] = 0;
                    if (ZI_WORK->ignoreCase != 0) {
                        if (!Zi8ChangeCharCase(1, &folded, language, __zi8_work_data)) Zi8ChangeCharCase(0, &folded, language, __zi8_work_data);
                        ZI_WORK->unk_0x184[previousOffset] = Zi8ConvertWC2UC(folded, language, __zi8_work_data);
                    }
                    if (ZI_WORK->unk_0x141[previousOffset++] == 0) {
                        ZI_WORK->unk_0x140 = 0;
                        break;
                    }
                    prefixLength--;
                    position++;
                }
            }
        }
        if (ZI_WORK->unk_0x140 == 0 && length == 0) return 0;
rescan:
        cursor = begin = dictionary->entries + dictionary->current;
        boundary = (ziU8*)dictionary + dictionary->boundary + 7;
        end = (ziU8*)dictionary + dictionary->end + 7;
        if (begin < boundary) firstSegment = 1;
        else firstSegment = 0;
        while ((cursor < boundary && firstSegment) || (cursor < end && !firstSegment)) {
            size = *cursor;
            if ((ziS32)ZI_WORK->unk_0x13C > visited++ || (((ziUserWord*)cursor)->size & 0xC0) != 0) {
next:
                if ((cursor += size) > end) {
                    if (firstSegment) break;
                    firstSegment = 1;
                    size = cursor - end - 1;
                    cursor = dictionary->entries + size;
                }
            } else {
                previous = (ziUserWord*)(cursor + size);
                if ((ziU8*)previous > end) previous = (ziUserWord*)(dictionary->entries + (cursor - end - 1));
                text = cursor;
                headerSize = *text++;
                entryLanguage = *text++;
                entryLength = *text++;
                text++;
                if (entryLanguage == language && entryLength >= length && entryLength < capacity && (complete == 0 || entryLength == length) && (complete != 0 || entryLength != length)) {
                    for (position = 0; position < length; position++) {
                        if (pattern[position] >= 0xEFF1 && pattern[position] <= 0xF010) {
                            if (pattern[position] != Zi8ConvertUC2Key(text[position], language, __zi8_work_data)) goto next;
                        } else {
                            folded = Zi8ConvertUC2WC(text[position], language, __zi8_work_data);
                            if (folded != pattern[position] && (!ZI_WORK->ignoreCase || !Zi8ChangeCharCase(0, &folded, language, __zi8_work_data) || folded != pattern[position])) goto next;
                        }
                    }
                    if (ZI_WORK->unk_0x140 != 0) {
                        if (ZI_WORK->unk_0x141[0] != previous->size || ZI_WORK->unk_0x141[1] != previous->language || ZI_WORK->unk_0x141[2] != previous->length) goto next;
                        prefixLength = 4;
                        position = ZI_WORK->unk_0x141[2] + 4;
                        for (; prefixLength < position; prefixLength++) {
                            if (ZI_WORK->unk_0x141[prefixLength] != ((ziU8*)previous)[prefixLength] && ZI_WORK->unk_0x184[prefixLength] != ((ziU8*)previous)[prefixLength]) goto next;
                        }
                    }
                    Zi8_81480224((ziUserWord*)cursor, __zi8_work_data);
                }
                goto next;
            }
        }
        if (ZI_WORK->unk_0x140 != 0 && length != 0) {
            ZI_WORK->unk_0x140 = 0;
            visited = 0;
            goto rescan;
        }
        if (length == 1 && complete != 0 && continuation == 0) {
            complete = 0;
            fallback = 1;
            visited = 0;
            goto rescan;
        }
    }
    text = (ziU8*)Zi8_814803F4(__zi8_work_data);
    if (text != 0) {
        language = ((ziUserWord*)text)->language;
        entryLength = ((ziUserWord*)text)->length;
        if (entryLength >= capacity) {
            Zi8_8148047C(__zi8_work_data);
            return 0;
        }
        text = ((ziUserWord*)text)->text;
        for (position = 0; position < (ziS32)entryLength; position++) output[position] = Zi8ConvertUC2WC(text[position], language, __zi8_work_data);
        return entryLength;
    }
    return 0;
}
