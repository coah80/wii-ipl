#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>
#include <zi8clib/zi8cgetc.h>
#include <zi8clib/zi8space.h>

typedef struct _ziCandParam {
    ziU8 unk_0x00;
    ziU8 unk_0x01;
    ziU8 unk_0x02;
    ziU8 unk_0x03;
    ziU32 unk_0x04;
    ziU32 unk_0x08;
    ziU32 unk_0x0C;
    ziU16 unk_0x10;
    ziU8 unk_0x12;
    ziU8 unk_0x13;
    ziU32 unk_0x14;
} ziCandParam;

extern ziU16 Zi8Ord2Ord(ziU16 ord ZI_NEED_WORK);
extern ziU32 Zi8WCharCount(ziWChar* str ZI_NEED_WORK);

static const ziU16 ziTones[4] = { 0x02CA, 0x02C7, 0x02CB, 0x02D9 };
static const ziU16 ziPuncts[4] = { 0xFF0C, 0x3002, 0xFF1F, 0xFF01 };
static ziU16 zi8tones[4];

static ziU8 Zi8SetFindCand(ziU8* table, ziU16 ch ZI_NEED_WORK) {
    ziU8 old;

    ch = Zi8Ord2Ord(ch, ZI_WORK);
    old = (ziU8)((1 << (ch % 8)) & table[ch / 8]);
    table[ch / 8] |= 1 << (ch % 8);
    return old;
}

static ziWChar* ZiGetNextPhonetic(ziWChar* p, ziWChar* end, ziPtr __zi8_work_data) {
    while (*p != 0 && *p != ZI_WORK->unk_0x1A && *p != 0xF360 && p < end) {
        p++;
    }
    if (*p == 0) {
        goto ret0;
    }
    if (p != end) {
        goto body;
    }
ret0:
    return ZI8_NULL;
body:
    p++;
    if (*p == 0) {
        goto ret0b;
    }
    if (p != end) {
        goto retp;
    }
ret0b:
    return ZI8_NULL;
retp:
    return p;
}

static ziS32 ZiPartialMatch(ziWChar* p, ziWChar* pend, ziWChar* q, ziWChar* qend, ziU16 n,
                            ziPtr __zi8_work_data) {
    if (p == pend) {
        goto ret1;
    }
    if (q == qend) {
        goto ret1;
    }
    if (*p == 0) {
        goto ret1;
    }
    if (*q != 0) {
        goto pchk;
    }
ret1:
    return 1;
qchk:
    if (*q == ZI_WORK->unk_0x1A) {
        goto ret1b;
    }
    if (*q == 0xF360) {
        goto ret1b;
    }
cmp:
    if (*p == *q) {
        goto adv;
    }
    return 0;
adv:
    p++;
    q++;
    if (p == pend) {
        goto ret1c;
    }
    if (q == qend) {
        goto ret1c;
    }
    if (*p == 0) {
        goto ret1c;
    }
    if (*q != 0) {
        goto pchk;
    }
ret1c:
    return 1;
pchk:
    if (*p == ZI_WORK->unk_0x1A) {
        goto ret1b;
    }
    if (*p != 0xF360) {
        goto qchk;
    }
ret1b:
    return 1;
}

static ziS32 ZiMatchZHSpelling(ziPtr p0, ziWChar* str1, ziWChar* str2, ziU8 cnt, ziU16 n,
                               ziPtr __zi8_work_data) {
    ziWChar bufB[0x40];
    ziWChar bufA[0x40];
    ziS32 ret;
    ziU32 c;
    ziS32 i;
    ziWChar* q;
    ziWChar* s;

    ret = 1;
    c = Zi8WCharCount(str1, ZI_WORK);
    if (str1 == ZI8_NULL || cnt == 0) {
        goto out1;
    }
    goto chk;
out1:
    return ret;
chk:
    for (i = 0; i < cnt; i++) {
        if (str1[i] == 0 || str1[i] != str2[i]) {
            ret = 0;
            break;
        }
    }
    if (ret != 0) {
        goto out;
    }
    bufB[0] = 0;
    bufA[0] = 0;
    if (Zi8ZHaddSpace(str2, cnt, bufB, 0x40, ZI_WORK) == 0) {
        return 0;
    }
    if (Zi8ZHaddSpace(str1, (ziU8)c, bufA, 0x40, ZI_WORK) == 0) {
        return 0;
    }
    q = bufB;
    s = bufA;
    while (n != 0) {
        s = ZiGetNextPhonetic(s, bufA + 0x40, ZI_WORK);
        if (s == ZI8_NULL) {
            return 0;
        }
        n--;
    }
    ret = 1;
    while (q != ZI8_NULL && s != ZI8_NULL) {
        if (ZiPartialMatch(q, bufB + 0x40, s, bufA + 0x40, n, ZI_WORK) == 0) {
            return 0;
        }
        q = ZiGetNextPhonetic(q, bufB + 0x40, ZI_WORK);
        s = ZiGetNextPhonetic(s, bufA + 0x40, ZI_WORK);
    }
out:
    return ret;
}

static ziS32 zi8InternalGetZH(ziGetParam* prm, ziCandParam* cand, ziPtr __zi8_work_data) {
    return 0;
}

static ziS32 Zi8NewMatchPhonetic(ziPtr p0 ZI_NEED_WORK) {
    return 0;
}

ziU8 Zi8GetElementCount(ziWChar* pElements, ziU8 elementCount, ziU8 charCount ZI_NEED_WORK) {
    struct {
        ziU16 old;
    } tmp;
    ziWChar buf[0x80];
    ziU8 i;
    ziU8 j;
    ziU8 k;
    ziU8 n;

    tmp.old = ZI_WORK->unk_0x1A;
    if (elementCount <= 1 || charCount == 0) {
        return elementCount;
    }
    for (i = 0; i < elementCount; i++) {
        if (pElements[i] == 0x3B) {
            continue;
        }
        if (pElements[i] < 0x61 || pElements[i] > 0x7A) {
            break;
        }
    }
    if (i == elementCount) {
        return elementCount;
    }
    ZI_WORK->unk_0x1A = 0xF360;
    Zi8ZHaddSpace(pElements, elementCount, buf, 0x100, ZI_WORK);
    ZI_WORK->unk_0x1A = tmp.old;
    n = 0;
    j = n;
    k = j;
    while (charCount != 0 && j < elementCount) {
        if (buf[k] == 0xF360) {
            charCount--;
            if (pElements[j] != 0xF360) {
                goto kinc;
            }
            goto tail;
        }
        if (buf[k] >= 0xF331 && buf[k] <= 0xF335) {
            charCount--;
            if (pElements[j + 1] == 0xF360) {
                goto inner;
            }
            goto tail;
        }
        goto tail;
inner:
        k++;
        j++;
        n++;
tail:
        j++;
        n++;
kinc:
        k++;
    }
    return n;
}

ziS32 Zi8GetChineseCandidates(ziGetParam* prm, ziCandParam* cand ZI_NEED_WORK) {
    ziGetParam tmp;
    ziS32 i;
    ziU8 cand_0;
    ziU32 cand_c;

    if (prm->firstCandidate != 0 || prm->elementCount <= 1) {
        goto def;
    }
    goto body;
def:
    return zi8InternalGetZH(prm, cand, ZI_WORK);
body:
    switch (prm->getMode) {
    case 0x10:
        if (prm->elements[prm->elementCount - 1] == 0xF360) {
            goto def;
        }
        i = prm->elementCount - 2;
        while (i > 0) {
            if (prm->elements[i] == 0xF360) {
                break;
            }
            i--;
        }
        if (i++ <= 0) {
            goto def;
        }
        break;
    case 0x0C:
    case 0x0D:
        switch (prm->elements[prm->elementCount - 1]) {
        case 0xF331:
        case 0xF332:
        case 0xF333:
        case 0xF334:
        case 0xF335:
        case 0xF360:
            break;
        default:
            goto def;
        }
        for (i = 1; i < 0x40; i++) {
            if (Zi8GetElementCount(prm->elements, prm->elementCount, (ziU8)i, ZI_WORK) >=
                prm->elementCount) {
                break;
            }
        }
        if (i-- == 1) {
            goto def;
        }
        i = Zi8GetElementCount(prm->elements, prm->elementCount, (ziU8)i, ZI_WORK);
        break;
    default:
        goto def;
    }
    tmp = *prm;
    cand_0 = cand->unk_0x00;
    cand_c = cand->unk_0x0C;
    tmp.elements = prm->elements + i;
    tmp.elementCount = (ziU8)(tmp.elementCount - i);
    cand_0 = cand->unk_0x00;
    cand->unk_0x00 = 1;
    cand_c = cand->unk_0x0C;
    cand->unk_0x0C = 1;
    i = zi8InternalGetZH(&tmp, cand, ZI_WORK);
    cand->unk_0x00 = cand_0;
    cand->unk_0x0C = cand_c;
    if (i == 0) {
        Zi8LogError(0x1388, ZI_WORK);
        return 0;
    }
    return zi8InternalGetZH(prm, cand, ZI_WORK);
}
