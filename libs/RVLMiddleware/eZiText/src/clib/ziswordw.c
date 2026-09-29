#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>

typedef struct {
    ziU16 unk0;
    ziU8 mode;
    ziU8 unk3;
    ziWChar* word;
    ziU8 wordLen;
    ziU8 unk9[3];
    ziU32 unkC;
    ziU16 maxLen;
    ziU16 unk12;
    ziU32 unk14;
} Zi8CandParam;

extern void Zi8Memset(ziPtr p, ziU32 v, ziU32 len);
extern ziS32 Zi8GetCandidatesOrCount(ziGetParam* gp, Zi8CandParam* sp ZI_NEED_WORK);
extern ziU16 Zi8Uni2Ord(ziU16 ch ZI_NEED_WORK);
extern ziU16 Zi8GetFormatVersion(ziU8 lang ZI_NEED_WORK);
extern ziU32 Zi8GetTableAddress(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);

ziBool Zi8IsWordW(ziWChar* word, ziU8 language,
                  struct __zi8_work_data_s* work) {
    ziU32 t1 = 0;
    ziU32 t2 = 0;
    ziU8* p;
    ziWChar* wp;
    ziU8 packed = 0;
    ziU8 rem = 0;
    ziU16 wc = 0;
    ziU8 buf[8] = {1, 5, 0, 0, 0, 0, 0, 0};
    ziGetParam gp;
    ziU32 bak32 = work->unk_0x1410;
    ziU8 bak8 = work->unk_0x1418;
    Zi8CandParam sp = {0};
    ziWChar wbuf[0x40];
    ziS32 i;
    ziU8* q;
    ziS32 v;
    ziS32 cnt;
    ziWChar* wp2;

    Zi8LogError(0x64, work);

    if (word == ZI8_NULL || *word == 0) {
        Zi8ReplaceLastError(0x12C, work);
        return 0;
    }

    if (language != 1) {
        i = 0;
        while (word[i] != 0) {
            if (word[i] >= 0xEFF1 || i == 0x40) {
                return 0;
            }
            i++;
        }
        sp.wordLen = (ziU8)i;
        sp.mode = 1;
        sp.word = word;
        sp.maxLen = 0x40;
        gp.language = language;
        gp.getMode = 0;
        gp.subLanguage = 7;
        gp.context = 1;
        gp.getOptions = 0x81;
        gp.elements = word;
        gp.elementCount = (ziU8)i;
        gp.currentWord = ZI8_NULL;
        gp.wordCharCount = 0;
        gp.candidates = wbuf;
        gp.maxCandidates = 1;
        gp.firstCandidate = 0;
        work->unk_0x1410 = (ziU32)buf;
        if (work->unk_0x1C[0] == 2) {
            work->unk_0x1418 = 0;
            if ((work->unk_0x09 & 1) != 0) {
                buf[work->unk_0x1418++] = 1;
            }
            if ((work->unk_0x09 & 4) != 0) {
                buf[work->unk_0x1418++] = 2;
            }
            if ((work->unk_0x09 & 2) != 0) {
                buf[work->unk_0x1418++] = 3;
            }
            if ((work->unk_0x09 & 8) != 0) {
                buf[work->unk_0x1418++] = 4;
            }
            if ((work->unk_0x09 & 1) != 0) {
                buf[work->unk_0x1418++] = 5;
            }
            if ((work->unk_0x09 & 4) != 0) {
                buf[work->unk_0x1418++] = 6;
            }
            if ((work->unk_0x09 & 2) != 0) {
                buf[work->unk_0x1418++] = 7;
            }
            if ((work->unk_0x09 & 8) != 0) {
                buf[work->unk_0x1418++] = 8;
            }
        } else if (work->unk_0x1C[0] != 0) {
            work->unk_0x1418 = 2;
        } else {
            work->unk_0x1418 = 1;
        }
        i = Zi8GetCandidatesOrCount(&gp, &sp, work);
        work->unk_0x1410 = bak32;
        work->unk_0x1418 = bak8;
        if (i != 0) {
            return 1;
        }
    }

    if (language != 1) {
        Zi8ReplaceLastError(0x26C, work);
        return 0;
    }

    i = 0;
    while (word[i] != 0) {
        wbuf[i] = Zi8Uni2Ord(word[i], work);
        if (wbuf[i] == 0xFFFF) {
            return 0;
        }
        i++;
        if (i == 0x40) {
            return 0;
        }
    }
    if (i-- == 1) {
        return 1;
    }
    wbuf[i] |= 0x8000;
    work->unk_0x16 = (ziU8)(Zi8GetFormatVersion(1, work) & 2);
    t1 = Zi8GetTableAddress(1, 0, work);
    p = (ziU8*)t1 + wbuf[0] * 0xC;
    t2 = Zi8GetTableAddress(1, 1, work);
    t2 = t2 +
        (((ziU32)(p[9] & 0xF) << 16) | ((ziU32)(p[0xB] | (p[0xA] << 8))));
    q = (ziU8*)t2;
    if (work->unk_0x16 != 0) {
        switch (*q & 7) {
        case 2:
            cnt = 2;
            break;
        case 3:
        case 4:
            cnt = 3;
            break;
        case 5:
            cnt = 4;
            break;
        default:
            cnt = 1;
            break;
        }
        q += cnt;
    }
    if ((*q & 0x80) != 0) {
        packed = 0;
        q += ((*q & 0x7F) >> 4) + 1;
        goto tail;
    }
    return 0;
more:
    packed = *q++;

    rem = (ziU8)(packed & 0xF);
    while (rem != 0) {
        cnt = i;
        wp = wbuf;
        while (cnt > 0) {
            wc = (ziWChar)(((ziU16)q[1] << 8) | q[0]);
            q += 2;
            if (wc != *++wp) {
                break;
            }
            cnt--;
            if ((wc & 0x8000) != 0) {
                break;
            }
        }
        if (cnt == 0) {
            return 1;
        }
        if ((wc & 0x8000) == 0) {
            q++;
            while ((*q & 0x80) == 0) {
                q += 2;
            }
            q++;
        }
        rem--;
    }
tail:
    if ((packed & 0x80) == 0) {
        goto more;
    }
    Zi8LogError(0x2BD, work);
    return 0;
}

typedef struct {
    ziWChar* a[0x20];
    ziWChar* b[0x20];
} Zi8UserTbl;

ziU16 Zi8ConvertUC2UserKey(ziU16 ch, ziU8 language, ziPtr workData) {
    Zi8UserTbl* t;
    ziWChar* p;
    ziU16 i;

    if ((ziU8)ch == 0 || language > 0x82 ||
        (t = ((struct __zi8_work_data_s*)workData)->userKeys[language]) ==
            ZI8_NULL) {
        return 0;
    }
    {
        i = 0;
        while ((ziU16)i < 0x20) {
            p = t->b[i];
            while (p != ZI8_NULL && *p != 0) {
                if (*p == (ziWChar)(ziU8)ch) {
                    goto found;
                }
                p++;
            }
            p = t->a[i];
            while (p != ZI8_NULL && *p != 0) {
                if (*p == (ziWChar)(ziU8)ch) {
                    goto found;
                }
                p++;
            }
            i++;
        }
    found:
        if ((ziU16)i >= 0x20) {
            return 0;
        }
        if (i == 0) {
            return 0xEFFA;
        }
        if (i >= 1 && i <= 9) {
            return (ziU16)(i + 0xEFF0);
        }
        if ((ziU16)i <= 0x1F) {
            return (ziU16)(i + 0xEFF1);
        }
    }
    return 0;
}
