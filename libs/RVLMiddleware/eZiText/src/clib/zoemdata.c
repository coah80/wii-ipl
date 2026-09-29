#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>

extern ziU16 Zi8ConvertWC2Key(ziWChar ch, ziU8 mode ZI_NEED_WORK);
extern ziU8 Zi8ChangeCharCase(ziU8 toUpper, ziWChar* ch, ziU8 mode ZI_NEED_WORK);

ziU8 Zi8AttachOEMdata(ziU8 (*pfn)(ziU16, ziWChar*, ziU8, ziPtr), ziU16 len,
                      ziPtr data ZI_NEED_WORK) {
    ZI_WORK->oemMatch = pfn;
    ZI_WORK->oemLen = len;
    ZI_WORK->oemData = data;
    Zi8LogError(0x64, ZI_WORK);
    return 1;
}

ziU8 Zi8DetachOEMdata(ziU8 force ZI_NEED_WORK) {
    Zi8LogError(0x64, ZI_WORK);
    if (force == 1) {
        if (ZI_WORK->oemMatch != ZI8_NULL) {
            goto clear;
        }
    }
    return 0;
clear:
    ZI_WORK->oemMatch = ZI8_NULL;
    ZI_WORK->oemLen = 0;
    return 1;
}

ziU8 Zi8MatchOEMdata(ziWChar* elements, ziU8 elementCount, ziU8 matchCase,
                     ziWChar* candidates, ziU16 maxCandSize, ziU8 unk8,
                     ziU8 unk9 ZI_NEED_WORK) {
    ziS32 flag = 0;
    ziWChar ch;
    ziS32 idx;
    ziS32 j;

    if (unk9 == 0) {
        ZI_WORK->oemIdx = 0;
    }
    idx = ZI_WORK->oemIdx;
    if (idx >= ZI_WORK->oemLen) {
        goto ret0;
    }
    if (ZI_WORK->oemMatch == ZI8_NULL) {
        goto ret0;
    }
    maxCandSize--;
    if (elementCount < maxCandSize) {
        goto pass;
    }
ret0:
    return 0;
pass:
    candidates[maxCandSize] = 0;
    if (unk8 != 0) {
        candidates[elementCount] = 1;
    } else {
        candidates[elementCount] = 0;
    }
    goto call;

next:
    j = 0;
    if (unk8 != 0 && candidates[elementCount] == 0) {
        goto cont;
    }
    if (unk8 != 0) {
        goto done;
    }
    if (candidates[elementCount] == 0) {
        goto done;
    }
cont:
    for (; j < elementCount; j++) {
        if (elements[j] < 0xEFF1 || elements[j] > 0xF37F) {
            goto other;
        }
        if (elements[j] ==
            Zi8ConvertWC2Key(candidates[j], matchCase, ZI_WORK)) {
            continue;
        }
        goto done;
other:
        if (candidates[j] == elements[j]) {
            continue;
        }
        if (ZI_WORK->unk_0x1F == 0) {
            goto done;
        }
        if (matchCase == 1) {
            goto done;
        }
        ch = elements[j];
        if (Zi8ChangeCharCase(1, &ch, matchCase, ZI_WORK) == 0) {
            goto done;
        }
        if (ch != candidates[j]) {
            goto done;
        }
    }
done:
    if (j >= elementCount) {
        goto success;
    }
    if (unk8 != 0) {
        candidates[elementCount] = 1;
    } else {
        candidates[elementCount] = 0;
    }
    idx++;
    if (idx >= ZI_WORK->oemLen) {
        goto tail;
    }
    goto call;
success:
    if (flag != 0) {
        idx = 0;
        candidates[0] = elements[0];
        return 1;
    }
    idx++;
    ZI_WORK->oemIdx = idx;
    while (candidates[j] != 0) {
        j++;
    }
    return (ziU8)j;
call:
    if (idx >= ZI_WORK->oemLen) {
        goto tail;
    }
    if (ZI_WORK->oemMatch((ziU16)idx, candidates, (ziU8)maxCandSize,
                          ZI_WORK->oemData) != 0) {
        goto next;
    }
tail:
    if (elementCount == 1 && unk8 != 0 && unk9 == 0) {
        unk8 = 0;
        flag = 1;
        idx = 0;
        goto call;
    }
    return 0;
}
