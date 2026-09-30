#include <stddef.h>
#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>
#include <zi8clib/zconvert.h>
#include <zi8clib/zmtkey.h>

ziU8 Zi8AttachOEMdata(ziU8 (*match)(ziU16, ziWChar*, ziU8, ziPtr), ziU16 count, ziPtr data ZI_NEED_WORK) {
    ZI_WORK->oemMatch = match;
    ZI_WORK->oemLen = count;
    ZI_WORK->oemData = data;
    Zi8LogError(100, __zi8_work_data);
    return 1;
}
ziU8 Zi8DetachOEMdata(ziU8 id ZI_NEED_WORK) {
    Zi8LogError(100, __zi8_work_data);
    if (id != 1 || ZI_WORK->oemMatch == 0) return 0;
    {
        ZI_WORK->oemMatch = 0;
        ZI_WORK->oemLen = 0;
        return 1;
    }
    return 0;
}
ziU8 Zi8MatchOEMdata(ziWChar* pattern, ziU8 length, ziU8 language, ziWChar* word, ziU16 capacity, ziBool complete, ziBool continuation ZI_NEED_WORK) {
    ziWChar folded;
    ziU8 fallback = 0;
    ziU32 index;
    ziU32 position;
    if (!continuation) ZI_WORK->oemIdx = 0;
    index = ZI_WORK->oemIdx;
    if ((ziS32)index >= ZI_WORK->oemLen || ZI_WORK->oemMatch == 0) goto noMatch;
    capacity--;
    if (length >= capacity) goto noMatch;
    word[capacity] = 0;
    word[length] = complete ? 1 : 0;
    for (;;) {
        if ((ziS32)index >= ZI_WORK->oemLen || !ZI_WORK->oemMatch(index, word, capacity, ZI_WORK->oemData)) {
            if (length != 1 || !complete || continuation) goto noMatch;
            complete = 0;
            fallback = 1;
            index = 0;
            continue;
        }
        position = 0;
        if ((complete && word[length] == 0) || (!complete && word[length] != 0)) {
            for (; (ziS32)position < length; position++) {
                if (pattern[position] < 0xEFF1 || pattern[position] > 0xF37F) {
                    if (word[position] != pattern[position]) {
                        if (!ZI_WORK->unk_0x1F || language == 1) break;
                        folded = pattern[position];
                        if (!Zi8ChangeCharCase(1, &folded, language, __zi8_work_data) || folded != word[position]) break;
                    }
                } else if (pattern[position] != Zi8ConvertWC2Key(word[position], language, __zi8_work_data)) break;
            }
        }
        if ((ziS32)position >= length) {
            if (fallback) {
                *word = *pattern;
                return 1;
            }
            ZI_WORK->oemIdx = index + 1;
            while (word[position] != 0) position++;
            return position;
        }
        word[length] = complete ? 1 : 0;
        index++;
    }
noMatch:
    return 0;
}
