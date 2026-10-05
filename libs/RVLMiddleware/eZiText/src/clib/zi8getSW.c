#include <zi8clib/zierror.h>

extern ziU16 Zi8GetTableCount(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);
extern ziU8 Zi8getKeyLayout(ziU8 lang, ziU16 key, ziWChar* layout, ziU8 mode ZI_NEED_WORK);
extern ziChar Zi8ConvertWC2UC(ziWChar ch, ziU8 language ZI_NEED_WORK);
extern ziU32 Zi8AlphaGetCandidates(ziGetParam* param, ziPtr sw ZI_NEED_WORK);
extern ziU8 Zi8SyllablesROMdata(ziWChar* keys, ziU8 count, ziU8 lang, ziWChar* out,
                                ziU16 a, ziU8 b, ziU8* cntOut, ziU8 c ZI_NEED_WORK);

typedef struct _ziSwParam {
    ziU8 countOnly;      // 0x00 - same layout as ZiCandidateOptions
    ziU8 maxWordLength;  // 0x01
    ziU8 lookupMode;     // 0x02
    ziU8 suffixOnly;     // 0x03
    ziU8 controls[8];    // 0x04
    ziS32 maxCount;      // 0x0C - signed view of ZiCandidateOptions.maxCount
    ziU16 capacity;      // 0x10
    ziU8 minWordLength;  // 0x12
    ziU8 flags;          // 0x13
} ziSwParam;

ziU32 Zi8GetSyllablesCandidates(ziGetParam* param, ziSwParam* sw ZI_NEED_WORK) {
    ziWChar buf[0x40];
    ziWChar buf2[0x32];
    ziS32 rem;
    ziS32 cur;
    ziS32 firstCand;
    ziS32 count;
    ziWChar* pNext;
    ziU16 err;
    ziU8 flag14;
    ziU8 flag13;
    ziU8 flag12;
    ziU8 flag11;
    ziU8 sylCnt;
    ziWChar* out;
    ziU8* u28;
    ziS32 i;

    firstCand = param->firstCandidate;
    count = 0;
    u28 = 0;
    pNext = 0;
    flag14 = 1;
    flag13 = 1;
    flag12 = 0;
    flag11 = 0;
    sylCnt = 0;
    err = 0x64;

    if (param->currentWord != 0 && param->wordCharCount != 0 &&
        param->currentWord[param->wordCharCount - 1] != 0x20) {
        flag11 = 1;
    }

    if (param->elementCount == 0 || (param->elementCount == 1 && flag11 == 0)) {
        count = Zi8AlphaGetCandidates(param, sw, ZI_WORK);
        goto end;
    }

    if (sw->countOnly != 0 || (param->getOptions & 0xFD) != 0x81) {
        out = buf;
        rem = 0x40;
    } else {
        out = param->candidates;
        rem = sw->capacity - 1;
    }
    if ((param->getOptions & 0xFD) == 0x80) {
        u28 = (ziU8*)param->candidates;
        rem = sw->capacity - 1;
    }

    if (rem <= param->elementCount) {
        err = 0x168;
        goto end;
    }

    if ((Zi8GetTableCount(param->language, 0x1F, ZI_WORK) & 8) != 0) {
        flag14 = 0;
    }

    if (param->elements[0] == 0xEFF1 && param->elementCount > 1 && flag14 != 0) {
        buf[0] = 0x2D;
    } else {
        Zi8getKeyLayout(param->language, param->elements[0], buf, 1, ZI_WORK);
    }
    out[0] = buf[0];
    Zi8SyllablesROMdata(param->elements, param->elementCount, param->language, out,
                        (ziU16)rem, 0, &sylCnt, flag11, ZI_WORK);
    if (sylCnt != 0) {
        cur = sylCnt;
    } else {
        cur = 1;
    }

    if (cur == param->elementCount) goto L5dc;
    if (firstCand != 0) {
        firstCand--;
        goto L5dc;
    }
    if (sw->countOnly != 0) {
        if (++count >= sw->maxCount) goto end;
        goto L5dc;
    }

    for (i = cur; i < param->elementCount; i += sylCnt) {
        if (param->elements[i] == 0xEFF1 && param->elementCount - i > 1 && flag14 != 0) {
            buf2[0] = 0x2D;
        } else {
            Zi8getKeyLayout(param->language, param->elements[i], buf2, 1, ZI_WORK);
        }
        out[i] = buf2[0];
        Zi8SyllablesROMdata(param->elements + i, param->elementCount - i, param->language,
                            out + i, (ziU16)rem, 0, &sylCnt, 1, ZI_WORK);
        if (sylCnt == 0) {
            sylCnt = 1;
        }
    }
    if (u28 != 0) {
        for (i = 0; i < param->elementCount; i++) {
            u28[i] = Zi8ConvertWC2UC(out[i], param->language, ZI_WORK);
        }
        u28[i++] = 0;
        u28[i] = 0;
        u28 += i;
    } else {
        out[i++] = 0;
        out[i] = 0;
        out += i;
    }
    rem -= i;
    if (++count >= param->maxCandidates) goto end;
    if (rem > param->elementCount) goto L5dc;
    goto end;

L5dc:
    while (cur >= 1) {
        flag12 = 0;
        goto rom;
found:
        flag12 = 1;
        if (cur == 1) {
            flag13 = 0;
        }
L464:
        if (out[0] >= 0xEFF1 && out[0] <= 0xF010) {
            goto dec;
        }
L464b:
        if (firstCand != 0) {
            firstCand--;
            goto L560;
        }
        if (sw->countOnly != 0) {
            if (++count >= sw->maxCount) goto end;
            goto L560;
        }
        if (u28 != 0) {
            for (i = 0; i < cur; i++) {
                u28[i] = Zi8ConvertWC2UC(out[i], param->language, ZI_WORK);
            }
            u28[i++] = 0;
            u28[i] = 0;
            u28 += i;
        } else {
            i = cur;
            out[i++] = 0;
            out[i] = 0;
            out += i;
        }
        rem -= i;
        if (++count >= param->maxCandidates) goto end;
        if (rem <= cur) goto end;
L560:
        if (pNext != 0) {
            if (*pNext == 0) goto end;
            out[0] = *pNext++;
            goto L464b;
        }
rom:
        if (Zi8SyllablesROMdata(param->elements, (ziU8)cur, param->language, out,
                                (ziU16)rem, flag12, 0, flag11, ZI_WORK) != 0) {
            goto found;
        }
dec:
        cur--;
    }
    if (flag13 == 0) goto end;

    if (param->elements[0] == 0xEFF1 && param->elementCount > 1 && flag14 != 0) {
        buf2[0] = 0x2D;
        buf2[1] = 0;
        Zi8getKeyLayout(param->language, param->elements[0], &buf2[1], 1, ZI_WORK);
        for (i = 1; buf2[i] != 0; i++) {
            if (buf2[i] == 0x2D) break;
        }
        while (buf2[i] != 0) {
            buf2[i] = buf2[i + 1];
            i++;
        }
    } else {
        Zi8getKeyLayout(param->language, param->elements[0], buf2, 1, ZI_WORK);
    }
    cur = 1;
    pNext = buf2;
    goto L560;

end:
    if (sw->countOnly != 0) {
        param->letters = 0;
    } else {
        param->letters = (ziU8)count;
    }
    Zi8LogError(err, ZI_WORK);
    return count;
}
