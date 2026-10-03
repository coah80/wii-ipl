#include <stddef.h>
#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>
#include <zi8clib/zconvert.h>
#include <zi8clib/zmtkey.h>

typedef struct ziPudSection {
    ziU8 flags;
    ziU8 language;
    ziU8 offset[2];
    ziU8 count[2];
    ziU8 reserved[2];
} ziPudSection;
typedef struct ziPudHeader {
    ziU8 format[3];
    ziU8 languageCount;
    ziU8 options[4];
    ziPudSection sections[1];
} ziPudHeader;
ziU8 Zi8_8147FD7C(ziWChar*, ziU8, ziU8, ziWChar*, ziU16, ziU8, ziU8 ZI_NEED_WORK);

ziU32 ZiIsPhoneticChar(ziWChar character) {
    if ((character < 0xF305 || character > 0xF329) && (character < 0xF361 || character > 0xF37A)) return 0;
    return 1;
}
int ZiGetZHWordSize(ziWChar* word, int size) {
    int bytes;
    ziWChar* cursor;
    bytes = 0;
    for (bytes = 0; bytes < size;) {
        cursor = word;
        if (ZiIsPhoneticChar(*cursor)) return bytes;
        bytes += 2;
        word++;
    }
    return bytes;
}
void Zi8CopyZHSpelling(ziU8* source, ziWChar* output, ziU16 capacity, int size, int start) {
    int offset;
    ziU8* cursor;
    if (output != 0 && capacity != 0) {
        *output = 0;
        if (size > start) {
            for (offset = 0; offset < size - start && offset < (int)((ziU32)capacity << 1); offset += 2) {
                cursor = source + start + offset;
                *output++ = *(ziWChar*)cursor;
            }
            *output = 0;
        }
    }
}
ziU8 ZADP_Zi8SetPDremoveOpt(ziU8 option, struct __zi8_work_data_s* __zi8_work_data) {
    ziU8 previous;
    previous = __zi8_work_data->pdRemoveOpt;
    __zi8_work_data->pdRemoveOpt = option;
    Zi8LogError(100, __zi8_work_data);
    return previous;
}
ziU8 Zi8MatchPUDdata_ZHS(ziWChar* pattern, ziU8 length, ziU8 language, ziWChar* output, ziU16 capacity, ziWChar* spelling, ziU16 spellingCapacity, ziU8 complete, ziU8 continuation ZI_NEED_WORK) {
    int fallback = 0;
    ziU8* bytePattern;
    ziWChar folded;
    ziPudSection* section;
    int wordSize;
    int copied;
    ziU8* word;
    int index;
    ziU32 entrySize;
    ziPudHeader* table;
    ziU8* byteOutput;
    if (!(ZI_WORK->pudCount <= 16 && ZI_WORK->pudCount != 0 && ZI_WORK->pudTable[ZI_WORK->pudCount - 1] != 0)) {
        Zi8LogError(0x4B0, __zi8_work_data);
        return 0;
    }
    if (language == 1) {
        length *= 2;
    }
    if (continuation == 0) {
        table = (ziPudHeader*)ZI_WORK->pudTable[ZI_WORK->pudCount - 1];
        section = table->sections;
        index = 0;
        while (index < table->languageCount) {
            if (section->language == language) break;
            section++;
            index++;
        }
        if (index >= table->languageCount) {
            Zi8LogError(0x4F6, __zi8_work_data);
            return 0;
        }
        ZI_WORK->unk_0x314 = ((ziU16)section->count[0] << 8) + (ziU16)section->count[1];
        ZI_WORK->unk_0x310 = (ziU32)table + (((ziU16)section->offset[0] << 8) + (ziU16)section->offset[1]);
        ZI_WORK->unk_0x318 = 0;
    }
    for (;;) {
        word = (ziU8*)ZI_WORK->unk_0x310;
        if (word == 0) {
            Zi8LogError(0x4B3, __zi8_work_data);
            return 0;
        }
        while ((ziS32)ZI_WORK->unk_0x318 < (ziS32)ZI_WORK->unk_0x314) {
            wordSize = *word++;
            entrySize = wordSize;
            if (language == 1) {
                if (ZI_WORK->zhPudMinPrefix > *word) goto next;
                wordSize--;
                entrySize--;
                word++;
                wordSize = ZiGetZHWordSize((ziWChar*)word, entrySize);
            } else if (ZI_WORK->unk_0x31E != 0 && complete != 0 && length < wordSize && word[length] == 0x20) goto matchText;
            if ((ziS32)length > (ziS32)wordSize || (complete != 0 && wordSize != length) || (complete == 0 && wordSize == length)) {
next:
                ZI_WORK->unk_0x318++;
                word += entrySize;
            } else {
                if (language == 1) {
                    bytePattern = (ziU8*)pattern;
                    for (index = 0; index < length; index++) {
                        if (word[index] != bytePattern[index]) goto next;
                    }
                    goto matched;
                }
matchText:
                for (index = 0; index < length; index++) {
                    if (pattern[index] >= 0xEFF1 && pattern[index] <= 0xF37F) {
                        if (pattern[index] != Zi8ConvertUC2Key(word[index], language, __zi8_work_data)) goto next;
                    } else {
                        folded = Zi8ConvertUC2WC(word[index], language, __zi8_work_data);
                        if (folded != pattern[index] && (!ZI_WORK->ignoreCase || !Zi8ChangeCharCase(0, &folded, language, __zi8_work_data) || folded != pattern[index])) goto next;
                    }
                }
matched:
                if (fallback) {
                    ZI_WORK->unk_0x310 = 0;
                    ZI_WORK->unk_0x318 = 0;
                    ZI_WORK->unk_0x314 = 0;
                    if (*pattern >= 0xEFF1) *output = *pattern;
                    else *output = Zi8ConvertWC2Key(*pattern, language, __zi8_work_data);
                    return 1;
                }
                if (language == 1) {
                    byteOutput = (ziU8*)output;
                    for (index = copied = 0; index < (ziS32)wordSize && copied < capacity; copied++) {
                        byteOutput[index] = word[index];
                        index++;
                        byteOutput[index] = word[index];
                        index++;
                    }
                    Zi8CopyZHSpelling(word, spelling, spellingCapacity, entrySize, wordSize);
                } else {
                    for (copied = 0; copied < wordSize && copied < capacity; copied++) {
                        output[copied] = Zi8ConvertUC2WC(word[copied], language, __zi8_work_data);
                        if (ZI_WORK->unk_0x31E != 0 && copied >= length && output[copied] == 0x20) {
                            if (complete != 0 || copied >= length) break;
                            goto next;
                        }
                    }
                }
                ZI_WORK->unk_0x318++;
                ZI_WORK->unk_0x310 = (ziU32)(word + entrySize);
                Zi8LogError(100, __zi8_work_data);
                return (ziU8)copied;
            }
        }
        if (length == 1 && complete != 0 && continuation == 0) {
            complete = 0;
            fallback = 1;
            ZI_WORK->unk_0x318 = 0;
        } else {
            ZI_WORK->unk_0x310 = 0;
            ZI_WORK->unk_0x318 = 0;
            ZI_WORK->unk_0x314 = 0;
            return 0;
        }
    }
}
ziU8 Zi8MatchPUDdata(ziWChar* pattern, ziU8 length, ziU8 language, ziWChar* output, ziU16 capacity, ziU8 complete, ziU8 continuation, struct __zi8_work_data_s* __zi8_work_data) {
    ziU8 result;
    if (continuation == 0) __zi8_work_data->pudCount = 1;
    for (;;) {
        result = Zi8_8147FD7C(pattern, length, language, output, capacity, complete, continuation, __zi8_work_data);
        if (result != 0) break;
        if (++__zi8_work_data->pudCount <= 16) {
            continuation = 0;
        } else {
            __zi8_work_data->pudCount = 1;
            break;
        }
    }
    return result;
}
ziU8 Zi8_8147FD7C(ziWChar* pattern, ziU8 length, ziU8 language, ziWChar* output, ziU16 capacity, ziU8 complete, ziU8 continuation ZI_NEED_WORK) {
    return Zi8MatchPUDdata_ZHS(pattern, length, language, output, capacity, 0, 0, complete, continuation, __zi8_work_data);
}
