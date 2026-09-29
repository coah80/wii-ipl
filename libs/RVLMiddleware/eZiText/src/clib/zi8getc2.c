#include <zi8clib/zi8getc2.h>
#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>

extern ziU16 Zi8GetTableCount(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);
extern ziU32 Zi8GetTableAddress(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);
extern ziU16 Zi8GetFormatVersion(ziU8 lang ZI_NEED_WORK);
extern ziU16 Zi8GetVersion(ziPtr __zi8_work_data);
extern ziU16 Zi8GetOEMID(ziPtr __zi8_work_data);
extern ziU16 Zi8GetBuildID(ziPtr __zi8_work_data);
extern void Zi8LogError(ziU16 code, ziPtr __zi8_work_data);
extern void Zi8ReplaceLastError(ziU16 code, ziPtr __zi8_work_data);
extern void Zi8Memset(ziPtr dst, ziU32 val, ziS32 size);
extern void Zi8Memcpy(ziPtr dst, ziPtr src, ziS32 size);

typedef struct {
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

extern ziS32 Zi8GetCandidatesOrCount(ziGetParam* prm, ziCandParam* cand ZI_NEED_WORK);
extern ziU8 Zi8LangSupported(ziU8 lang ZI_NEED_WORK);
extern ziS32 Zi8GetKOcandidates(ziGetParam* prm, ziCandParam* cand ZI_NEED_WORK);
extern ziS32 Zi8GetKoreanCandidates(ziGetParam* prm, ziCandParam* cand ZI_NEED_WORK);
extern ziS32 Zi8Punctuation(ziGetParam* prm, ziCandParam* cand ZI_NEED_WORK);
extern ziBool Zi8IsCharacter(ziWChar c ZI_NEED_WORK);
extern ziU8 Zi8GetCharInfo(ziWChar c, ziWChar* buf, ziU8 size, ziU8 flag ZI_NEED_WORK);
extern ziS32 Zi8GetChineseCandidates(ziGetParam* prm, ziCandParam* cand ZI_NEED_WORK);
extern ziS32 Zi8Get1KeyPressSpelling(ziGetParam* prm, ziCandParam* cand ZI_NEED_WORK);
extern ziS32 Zi8Get1KeyPressCandidates(ziGetParam* prm, ziCandParam* cand ZI_NEED_WORK);
extern ziS32 Zi8GetSyllablesCandidates(ziGetParam* prm, ziCandParam* cand ZI_NEED_WORK);
extern ziS32 Zi8AlphaGetCandidates(ziGetParam* prm, ziCandParam* cand ZI_NEED_WORK);

static const ziU32 Zi8PYdefaultFuzzyPairs[2] = {
    0x7E000000, 0
};

#pragma push
#pragma section data_type ".sdata2"
static ziU32 Zi8ZYdefaultFuzzyPairs[2];
#pragma pop

static const ziU8 Zi8SOdefaultArray[0x10] = { 1, 4, 3, 2, 1, 8, 7, 6, 5 };

ziBool Zi8ZHsetPYfuzzyPairs(ziFuzzyPYPairs pairsList ZI_NEED_WORK) {
    if (pairsList.ziDefault) {
        ZI_WORK->unk_0x1B28.word = *(const ziU32*)&Zi8PYdefaultFuzzyPairs;
    } else {
        ZI_WORK->unk_0x1B28.word = *(ziU32*)&pairsList;
    }
    return ZI8_TRUE;
}

ziBool Zi8ZHsetZYfuzzyPairs(ziFuzzyZYPairs pairsList ZI_NEED_WORK) {
    if (pairsList.ziDefault) {
        ZI_WORK->unk_0x1B2C.word = Zi8ZYdefaultFuzzyPairs[0];
    } else {
        ZI_WORK->unk_0x1B2C.word = *(ziU32*)&pairsList;
    }
    return ZI8_TRUE;
}

ziBool Zi8SetLatinSearchOrder(ziU8* searchArray, ziU8 searchSize ZI_NEED_WORK) {
    if (searchArray == ZI8_NULL || searchArray[0] == 0) {
        ZI_WORK->unk_0x1410 = (ziU32)Zi8SOdefaultArray;
        ZI_WORK->unk_0x1418 = 9;
    } else {
        ZI_WORK->unk_0x1410 = (ziU32)searchArray;
        ZI_WORK->unk_0x1418 = searchSize;
    }
    return ZI8_TRUE;
}

ziU16 Zi8GetGlobalDataSize() {
    return 0x1B44;
}

static ziU16 Zi8GetDataSignature(ziU8* buf, ziU16 maxLen, ziU8 sel ZI_NEED_WORK) {
    ziU16 idx;
    ziU8* tbl;

    if (sel == 1) {
        if (Zi8GetFormatVersion(1, ZI_WORK) < 8) {
            Zi8LogError(0x26F, ZI_WORK);
            return 0;
        }
        idx = 0x1E;
    } else {
        idx = 3;
    }
    tbl = (ziU8*)Zi8GetTableAddress(sel, idx, ZI_WORK);
    idx = Zi8GetTableCount(sel, idx, ZI_WORK);
    if (idx == 0 || idx > maxLen) {
        Zi8LogError(0x961, ZI_WORK);
        return 0;
    }
    Zi8Memcpy(buf, tbl, idx);
    buf[idx] = 0;
    Zi8LogError(0x64, ZI_WORK);
    return idx;
}

static ziU16 Zi8GetEngineSignature(ziU8* buf ZI_NEED_WORK) {
    ziU16 i = 0;
    ziU16 v;
    ziU16 lo[1];

    buf[i++] = 'v';
    v = (ziU16)((Zi8GetVersion(ZI_WORK) & 0xFF00) >> 8);
    lo[0] = (ziU8)((ziU16)Zi8GetVersion(ZI_WORK) & 0xFF);
    buf[i++] = (ziU8)(v / 10 + '0');
    buf[i++] = (ziU8)(v % 10 + '0');
    buf[i++] = (ziU8)(lo[0] / 10 + '0');
    buf[i++] = (ziU8)(lo[0] % 10 + '0');
    buf[i++] = 'o';
    v = Zi8GetOEMID(ZI_WORK);
    buf[i++] = (ziU8)(v / 100 + '0');
    buf[i++] = (ziU8)(v % 100 / 10 + '0');
    buf[i++] = (ziU8)(v % 100 % 10 + '0');
    buf[i++] = 'b';
    v = Zi8GetBuildID(ZI_WORK);
    buf[i++] = (ziU8)(v / 100 + '0');
    buf[i++] = (ziU8)(v % 100 / 10 + '0');
    buf[i++] = (ziU8)(v % 100 % 10 + '0');
    buf[i] = 0;
    return i;
}

static ziBool Zi8AlphaSignature(ziGetParam* prm, ziU8 flag ZI_NEED_WORK) {
    ziU8 buf[0x20];
    ziU8 buf2[0x20];
    ziU8* p1;
    ziU8* p2;
    ziU16 len1[1];
    ziU16 len2;
    ziU16 n;
    ziU8* src;
    ziWChar* out;

    out = prm->candidates;
    p1 = ZI8_NULL;
    p2 = ZI8_NULL;
    len1[0] = 0;
    len2 = 0;
    Zi8LogError(0x64, ZI_WORK);
    prm->letters = 0;
    n = Zi8GetDataSignature(buf, 0x20, prm->language, ZI_WORK);
    if (n != 0 && prm->elementCount <= n) {
        p1 = buf;
        p2 = buf2;
        len1[0] = n;
    } else {
        p1 = buf2;
    }
    n = Zi8GetEngineSignature(buf2, ZI_WORK);
    if (n < prm->elementCount) {
        if (len1[0] != 0) {
            p2 = ZI8_NULL;
            n = 1;
        } else {
            Zi8ReplaceLastError(0x1F4, ZI_WORK);
            return ZI8_FALSE;
        }
    } else {
        if (len1[0] != 0) {
            len2 = n;
            n = 2;
        } else {
            len1[0] = n;
            n = 1;
        }
    }
    if (prm->firstCandidate >= n) {
        Zi8ReplaceLastError(0x1F5, ZI_WORK);
        return ZI8_FALSE;
    }
    n = n - prm->firstCandidate;
    if (flag != 0) {
        prm->letters = n;
        ZI_WORK->unk_0x0A = 0xFF;
        return ZI8_TRUE;
    }
    if (prm->maxCandidates < n) {
        n = prm->maxCandidates;
    }
    prm->letters = n;
    if ((prm->getOptions & 0x80) == 0) {
        ZI_WORK->unk_0x538 = prm->language;
        prm->candidates[0] = 0xFFF0;
        out = (ziWChar*)&ZI_WORK->unk_0x338;
    }
    if (prm->firstCandidate != 0) {
        src = p2;
        n = len2;
    } else {
        src = p1;
        n = len1[0];
    }
    if (n > ZI_WORK->unk_0x0A) {
        n = ZI_WORK->unk_0x0A;
    }
    if (prm->elementCount < ZI_WORK->unk_0x140C[0] ||
        (prm->getOptions & 0x7E) == 2) {
        if (n > prm->elementCount) {
            n = prm->elementCount;
        }
    }
    while (n-- != 0) {
        *out++ = *src++;
    }
    *out++ = 0;
    if (prm->letters == 2) {
        src = p2;
        n = len2;
        if (n > ZI_WORK->unk_0x0A) {
            n = ZI_WORK->unk_0x0A;
        }
        if (prm->elementCount < ZI_WORK->unk_0x140C[0] ||
            (prm->getOptions & 0x7E) == 2) {
            if (n > prm->elementCount) {
                n = prm->elementCount;
            }
        }
        while (n-- != 0) {
            *out++ = *src++;
        }
        *out++ = 0;
    }
    *out++ = 0;
    ZI_WORK->unk_0x0A = 0xFF;
    return ZI8_TRUE;
}

static ziBool Zi8ZhSignature(ziGetParam* prm, ziU8 flag ZI_NEED_WORK) {
    ziU8 buf1[0x20];
    ziU8 buf2[0x20];
    ziU8* src;
    ziWChar* out;
    ziU16 len1;
    ziU16 len2;
    ziU16 n;
    ziU16 used;

    out = prm->candidates;
    src = ZI8_NULL;
    Zi8LogError(0x64, ZI_WORK);
    prm->letters = 0;
    len1 = Zi8GetDataSignature(buf1, 0x20, prm->language, ZI_WORK);
    len2 = Zi8GetEngineSignature(buf2, ZI_WORK);
    if ((prm->context & 0x10) != 0) {
        n = 0;
        if (len1 != 0) {
            n++;
        }
        if (len2 != 0) {
            n++;
        }
    } else {
        n = (ziU16)(len1 + len2);
    }
    if (prm->firstCandidate >= n) {
        Zi8ReplaceLastError(0x1F6, ZI_WORK);
        return ZI8_FALSE;
    }
    n = (ziU16)(n - prm->firstCandidate);
    if (flag != 0) {
        prm->letters = (ziU8)n;
        ZI_WORK->unk_0x0A = 0xFF;
        return ZI8_TRUE;
    }
    if (prm->maxCandidates < n) {
        n = prm->maxCandidates;
    }
    prm->letters = (ziU8)n;
    if ((prm->context & 0x10) != 0) {
        if (prm->firstCandidate == 0 && len1 != 0) {
            goto UseDataSig;
        }
        if (!(prm->firstCandidate != 0 && len1 == 0)) {
            goto UseEngSig;
        }
        Zi8ReplaceLastError(0x1F4, ZI_WORK);
        return ZI8_FALSE;
UseEngSig:
        src = buf2;
        n = len2;
        goto CopySig;
UseDataSig:
        src = buf1;
        n = len1;
CopySig:
        while (n-- != 0) {
            *out++ = *src++;
        }
        *out++ = 0x20;
        if (prm->letters == 2) {
            src = buf2;
            n = len2;
            while (n-- != 0) {
                *out++ = *src++;
            }
            *out++ = 0x20;
        }
    } else {
        used = 0;
        if (len1 != 0) {
            if (prm->firstCandidate >= len1) {
                n = 0;
            } else {
                n = (ziU16)(len1 - prm->firstCandidate);
                src = buf1 + prm->firstCandidate;
            }
            if (prm->letters < n) {
                n = prm->letters;
            }
            used = n;
            while (n-- != 0) {
                *out++ = *src++;
            }
        }
        src = buf2;
        if (prm->firstCandidate >= len1) {
            n = (ziU16)(len1 + (len2 - prm->firstCandidate));
            src += len2 - n;
        } else {
            n = len2;
        }
        if (prm->letters - used < n) {
            n = prm->letters - used;
        }
        while (n-- != 0) {
            *out++ = *src++;
        }
    }
    return ZI8_TRUE;
}

ziBool _Zi8GetCandidates(ziGetParam* prm ZI_NEED_WORK) {
    ziCandParam cand = { 0 };

    cand.unk_0x10 = ZI_WORK->unk_0x141A;
    return Zi8GetCandidatesOrCount(prm, &cand, ZI_WORK);
}

ziBool _Zi8CheckCandidates(ziGetParam* prm ZI_NEED_WORK) {
    ziCandParam cand = { 0 };

    cand.unk_0x10 = ZI_WORK->unk_0x141A;
    cand.unk_0x13 = 1;
    return Zi8GetCandidatesOrCount(prm, &cand, ZI_WORK);
}

ziS32 Zi8GetCandidatesOrCount(ziGetParam* prm, ziCandParam* cand ZI_NEED_WORK) {
    ziS32 ret;
    ziU16 err = 0;
    ziU8 savedOpt;
    ziU8 restore;
    ziU8 n;
    ziU8 savedCount;
    ziU8 savedMode;
    ziU8 i;
    ziWChar* savedElements;
    ziWChar* savedScratch;
    ziWChar c;
    ziWChar savedCh;
    ziWChar buf[0x10];

    savedOpt = 0;
    savedScratch = ZI8_NULL;
    restore = 0;

    if (cand->unk_0x02 == 0) {
        if (ZI_WORK->unk_0x00 == 9 && prm->elementCount != 0) {
            if (prm->elements[prm->elementCount - 1] == 0xEFF8 &&
                Zi8AlphaSignature(prm, cand->unk_0x00, ZI_WORK)) {
                goto Done;
            }
            if (prm->elements[prm->elementCount - 1] == 0xEF04 &&
                Zi8ZhSignature(prm, cand->unk_0x00, ZI_WORK)) {
Done:
                ret = prm->letters;
                if (cand->unk_0x00 != 0) {
                    prm->letters = 0;
                }
                Zi8LogError(0x64, ZI_WORK);
                return ret;
            }
        }
        if (prm->elementCount == 1 && prm->firstCandidate == 0) {
            switch (prm->language) {
            case 1:
                if (ZI_WORK->unk_0x00 != 0 && ZI_WORK->unk_0x01 != cand->unk_0x00) {
                    break;
                }
                switch (ZI_WORK->unk_0x00) {
                case 0:
                    if (prm->elements[0] == 0xEF04) {
                        ZI_WORK->unk_0x01 = cand->unk_0x00;
                        ZI_WORK->unk_0x00 = 1;
                    }
                    break;
                case 2:
                case 4:
                case 6:
                    if (prm->elements[0] == 0xEF04) {
                        ZI_WORK->unk_0x00++;
                    } else {
                        ZI_WORK->unk_0x00 = 0;
                    }
                    break;
                case 1:
                case 3:
                case 5:
                case 7:
                    if (prm->elements[0] == 0xEF01) {
                        ZI_WORK->unk_0x00++;
                    } else {
                        ZI_WORK->unk_0x00 = 0;
                    }
                    break;
                case 8:
                case 9:
                    if (prm->elements[0] == 0xEF04 && Zi8ZhSignature(prm, cand->unk_0x00, ZI_WORK)) {
                        ZI_WORK->unk_0x00 = 9;
                        ret = prm->letters;
                        if (cand->unk_0x00 != 0) {
                            prm->letters = 0;
                        }
                        Zi8LogError(0x64, ZI_WORK);
                        return ret;
                    }
                default:
                    ZI_WORK->unk_0x00 = 0;
                    break;
                }
                if (ZI_WORK->unk_0x00 == 0 && prm->elements[0] == 0xEF04) {
                    ZI_WORK->unk_0x00 = 1;
                }
                break;
            case 0x10:
            case 0x12:
            case 0x77: case 0x78: case 0x79: case 0x7A:
            case 0x7B: case 0x7C: case 0x7D:
                break;
            default:
                if (ZI_WORK->unk_0x00 != 0 && ZI_WORK->unk_0x01 != cand->unk_0x00) {
                    break;
                }
                switch (ZI_WORK->unk_0x00) {
                case 0:
                    if (prm->elements[0] == 0xEFF2) {
                        ZI_WORK->unk_0x01 = cand->unk_0x00;
                        ZI_WORK->unk_0x00 = 1;
                    }
                    break;
                case 1:
                    if (prm->elements[0] == 0xEFF3) {
                        ZI_WORK->unk_0x00 = 2;
                    } else {
                        ZI_WORK->unk_0x00 = 0;
                    }
                    break;
                case 2:
                    if (prm->elements[0] == 0xEFF5) {
                        ZI_WORK->unk_0x00 = 3;
                    } else {
                        ZI_WORK->unk_0x00 = 0;
                    }
                    break;
                case 3:
                    if (prm->elements[0] == 0xEFF7) {
                        ZI_WORK->unk_0x00 = 4;
                    } else {
                        ZI_WORK->unk_0x00 = 0;
                    }
                    break;
                case 4:
                    if (prm->elements[0] == 0xEFF8) {
                        ZI_WORK->unk_0x00 = 5;
                    } else {
                        ZI_WORK->unk_0x00 = 0;
                    }
                    break;
                case 5:
                    if (prm->elements[0] == 0xEFF9) {
                        ZI_WORK->unk_0x00 = 6;
                    } else {
                        ZI_WORK->unk_0x00 = 0;
                    }
                    break;
                case 6:
                    if (prm->elements[0] == 0xEFF2) {
                        ZI_WORK->unk_0x00 = 7;
                    } else {
                        ZI_WORK->unk_0x00 = 0;
                    }
                    break;
                case 7:
                    if (prm->elements[0] == 0xEFF5) {
                        ZI_WORK->unk_0x00 = 8;
                    } else {
                        ZI_WORK->unk_0x00 = 0;
                    }
                    break;
                case 8:
                case 9:
                    if (prm->elements[0] == 0xEFF8 && Zi8AlphaSignature(prm, cand->unk_0x00, ZI_WORK)) {
                        ZI_WORK->unk_0x00 = 9;
                        ret = prm->letters;
                        if (cand->unk_0x00 != 0) {
                            prm->letters = 0;
                        }
                        Zi8LogError(0x64, ZI_WORK);
                        return ret;
                    }
                default:
                    ZI_WORK->unk_0x00 = 0;
                    break;
                }
                if (ZI_WORK->unk_0x00 == 0 && prm->elements[0] == 0xEFF2) {
                    ZI_WORK->unk_0x00 = 1;
                }
                break;
            }
        } else if (prm->elementCount > 1) {
            ZI_WORK->unk_0x00 = 0;
        }
    }
    ZI_WORK->unk_0x18 = prm->subLanguage;
    ZI_WORK->unk_0x16 = (ziU8)(Zi8GetFormatVersion(1, ZI_WORK) & 2);
    cand->unk_0x0C = ZI_WORK->unk_0x10;
    cand->unk_0x01 = ZI_WORK->unk_0x0A;
    ZI_WORK->unk_0x0A = 0xFF;
    if (!Zi8LangSupported(prm->language, ZI_WORK)) {
        Zi8LogError(0x163, ZI_WORK);
        return 0;
    }
    if (prm->language == 0x10) {
        err = 0x2C1;
        ret = 0;
    } else if (prm->language == 0x12) {
        if (prm->elementCount == 0 || prm->elements[0] >= 0xEFF1) {
            ret = Zi8GetKOcandidates(prm, cand, ZI_WORK);
        } else {
            ret = Zi8GetKoreanCandidates(prm, cand, ZI_WORK);
        }
    } else if (prm->language == 1 && (prm->context & 8) != 0) {
        ret = Zi8Punctuation(prm, cand, ZI_WORK);
        err = 0x64;
    } else if (prm->language == 1 && (prm->getOptions & 0xBF) == 4 &&
               prm->elementCount != 0 && Zi8IsCharacter(prm->elements[0], ZI_WORK)) {
        n = Zi8GetCharInfo(prm->elements[0], buf, 0x10, 1, ZI_WORK);
        if (n == 0) {
            prm->letters = prm->count = prm->unk_0x20 = 0;
            ret = 0;
            err = 0x384;
        } else {
            c = buf[n - 1];
            if (c >= 0xF331 && c <= 0xF335) {
                buf[n - 1] = 0xF360;
            }
            savedElements = prm->elements;
            prm->elements = buf;
            savedCount = prm->elementCount;
            prm->elementCount = n;
            savedMode = prm->getMode;
            prm->getMode = 1;
            ret = Zi8GetChineseCandidates(prm, cand, ZI_WORK);
            prm->elements = savedElements;
            prm->elementCount = savedCount;
            prm->getMode = savedMode;
            prm->count = 1;
        }
    } else if (prm->language == 1 && prm->getMode == 0xF) {
        err = 0x2D0;
        ret = 0;
    } else if (prm->language == 1 && (prm->getMode == 3 || prm->getMode == 4)) {
        if ((prm->getOptions & 0x80) != 0) {
            ret = Zi8Get1KeyPressSpelling(prm, cand, ZI_WORK);
        } else if (prm->elementCount == 0) {
            ret = Zi8GetChineseCandidates(prm, cand, ZI_WORK);
        } else {
            ret = Zi8Get1KeyPressCandidates(prm, cand, ZI_WORK);
        }
    } else if (prm->language == 1 &&
               (prm->getMode == 7 || prm->getMode == 8 || prm->getMode == 0xA || prm->getMode == 9)) {
        if (ZI_WORK->unk_0x16 != 0) {
            ret = Zi8GetChineseCandidates(prm, cand, ZI_WORK);
        } else {
            err = 0x708;
            ret = 0;
        }
    } else if (prm->language == 1 && (prm->getMode == 0xB || prm->getMode == 0xE)) {
        err = 0x2EE;
        ret = 0;
    } else if (prm->language == 1) {
        ret = Zi8GetChineseCandidates(prm, cand, ZI_WORK);
        if (ret == 0 && (prm->getOptions & 0x20) == 0 && prm->getMode == 1 && prm->elementCount != 0 &&
            (prm->elements[prm->elementCount - 1] == 0xF37A ||
             prm->elements[prm->elementCount - 1] == 0xF363 ||
             prm->elements[prm->elementCount - 1] == 0xF373)) {
            savedCh = prm->elements[prm->elementCount];
            prm->elements[prm->elementCount++] = 0xF368;
            ret = Zi8GetChineseCandidates(prm, cand, ZI_WORK);
            prm->elements[--prm->elementCount] = savedCh;
        }
    } else {
        ZI_WORK->unk_0x538 = prm->language;
        if ((prm->getOptions & 0x80) == 0) {
            restore = 1;
            savedOpt = prm->getOptions;
            savedScratch = prm->candidates;
            prm->getOptions = prm->getOptions | 0x81;
            prm->candidates = (ziWChar*)&ZI_WORK->unk_0x338;
            cand->unk_0x10 = 0x100;
        }
        if (prm->getMode == 2) {
            if ((Zi8GetTableCount(prm->language, 0x1F, ZI_WORK) & 0x200) != 0) {
                ret = Zi8GetSyllablesCandidates(prm, cand, ZI_WORK);
            } else {
                err = 0x44C;
                ret = 0;
            }
        } else {
            ret = Zi8AlphaGetCandidates(prm, cand, ZI_WORK);
        }
    }
    if (restore != 0) {
        prm->getOptions = savedOpt;
        prm->candidates = savedScratch;
        for (i = 0; i < prm->letters; i++) {
            prm->candidates[i] = (ziWChar)(0xFFF0 + i);
        }
    }
    if (err != 0) {
        Zi8LogError(err, ZI_WORK);
    }
    return ret;
}

void Zi8InitDupWordBuf(ziPtr __zi8_work_data) {
    ZI_WORK->unk_0x539 = 0;
}

ziBool Zi8IsDupWChar(ziWChar c, ziPtr __zi8_work_data) {
    ziS32 i;
    ziBool found;
    ziWChar* buf = (ziWChar*)&ZI_WORK->unk_0x57A;

    found = ZI8_FALSE;
    if (ZI_WORK->unk_0x539 == 0) {
        buf[0] = 2;
        buf[1] = c;
        ZI_WORK->unk_0x539 = 1;
        Zi8LogError(0x8FD, ZI_WORK);
        return ZI8_FALSE;
    }
    for (i = ZI_WORK->unk_0x539; i != 0; i--) {
        if (c == buf[i]) {
            found = ZI8_TRUE;
            break;
        }
    }
    ZI_WORK->unk_0x539++;
    buf[buf[0]++] = c;
    if (buf[0] > 0x64) {
        buf[0] = 2;
        buf[1] = c;
        ZI_WORK->unk_0x539 = 1;
    }
    Zi8LogError(0x64, ZI_WORK);
    return found;
}

ziBool Zi8IsDupWordW(ziWChar* word, ziU8 len ZI_NEED_WORK) {
    register ziBool found;
    ziS32 i;
    ziS32 j;
    ziS32 idx;

    found = ZI8_FALSE;
    if (word == ZI8_NULL || len == 0) {
        Zi8LogError(0x12C, ZI_WORK);
        return ZI8_FALSE;
    }
    if (len > 0x14) {
        word += len - 0x14;
        len = 0x14;
    }
    for (i = 0; i < ZI_WORK->unk_0x539; i++) {
        idx = ZI_WORK->unk_0x53A[i];
        for (j = 0; j < len; j++) {
            if (word[j] != ((ziWChar(*)[0x15])ZI_WORK->unk_0x57A)[idx][j]) {
                break;
            }
        }
        if (j >= len && ((ziWChar(*)[0x15])ZI_WORK->unk_0x57A)[idx][j] == 0) {
            found = ZI8_TRUE;
            break;
        }
    }
    if (found == ZI8_FALSE) {
        if (ZI_WORK->unk_0x539 < 0x40) {
            idx = ZI_WORK->unk_0x53A[ZI_WORK->unk_0x539] = ZI_WORK->unk_0x539;
            ZI_WORK->unk_0x539++;
        } else {
            idx = ZI_WORK->unk_0x53A[0];
            for (i = 1; i < ZI_WORK->unk_0x539; i++) {
                ZI_WORK->unk_0x53A[i - 1] = ZI_WORK->unk_0x53A[i];
            }
            ZI_WORK->unk_0x53A[i - 1] = idx;
        }
    } else {
        idx = ZI_WORK->unk_0x53A[i];
        for (; i < ZI_WORK->unk_0x539 - 1; i++) {
            ZI_WORK->unk_0x53A[i] = ZI_WORK->unk_0x53A[i + 1];
        }
        ZI_WORK->unk_0x53A[i] = idx;
    }
    for (j = 0; j < len; j++) {
        ((ziWChar(*)[0x15])ZI_WORK->unk_0x57A)[idx][j] = word[j];
    }
    ((ziWChar(*)[0x15])ZI_WORK->unk_0x57A)[idx][j] = 0;
    Zi8LogError(0x64, ZI_WORK);
    return found;
}

void Zi8Memset(ziPtr dst, ziU32 val, ziS32 size) {
    ziS32 i;

    for (i = 0; i < size; i++) {
        ((ziU8*)dst)[i] = (ziU8)val;
    }
}

void Zi8Memcpy(ziPtr dst, ziPtr src, ziS32 size) {
    ziS32 i;

    for (i = 0; i < size; i++) {
        ((ziU8*)dst)[i] = ((ziU8*)src)[i];
    }
}

ziBool Zi8SetMaxWordLength(ziU8 length ZI_NEED_WORK) {
    ZI_WORK->unk_0x0A = length;
    return ZI8_TRUE;
}
