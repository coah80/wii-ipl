#include <zi8clib/zierror.h>

extern ziWChar Zi8ConvertUC2WC(ziU8 ch, ziU8 language ZI_NEED_WORK);
extern ziU16 Zi8ConvertUC2Key(ziU8 ch, ziU8 language ZI_NEED_WORK);
extern ziChar Zi8ConvertWC2UC(ziWChar ch, ziU8 language ZI_NEED_WORK);
extern ziU8 Zi8ChangeCharCase(ziU8 toUpper, ziWChar* ch, ziU8 language ZI_NEED_WORK);
extern void Zi8Memset(ziPtr p, ziU32 v, ziU32 len);
extern void Zi8ReplaceLastError(ziU16 err ZI_NEED_WORK);

static ziU32 Zi8_81480224(ziU8* word ZI_NEED_WORK) {
    ziUwdNode* prev;
    ziUwdNode* node;
    ziU8* nw;
    ziUwdNode* slot;
    ziU8 len;
    ziU8 i;

    if (ZI_WORK->uwdCount >= 0x20) {
        Zi8LogError(0x19d, ZI_WORK);
        return 0;
    }
    if (word == 0) {
        Zi8LogError(0x19f, ZI_WORK);
        return 0;
    }
    len = word[2];
    if (len == 0) {
        Zi8LogError(0x193, ZI_WORK);
        return 0;
    }
    if (len > 0x3F) {
        Zi8LogError(0x194, ZI_WORK);
        return 0;
    }

    prev = 0;
    for (node = ZI_WORK->uwdList; node != 0; node = node->next) {
        nw = node->word;
        if (ZI_WORK->unk_0x12E == 1 && word[3] > nw[3]) {
            break;
        }
        if (nw[2] == len) {
            for (i = 0; i < len; i++) {
                if (nw[4 + i] != word[4 + i]) break;
            }
            if (i == len) {
                Zi8LogError(0x64, ZI_WORK);
                return 0;
            }
        }
        prev = node;
    }

    slot = &ZI_WORK->uwdNodes[ZI_WORK->uwdCount++];
    if (prev == 0) {
        ZI_WORK->uwdList = slot;
        slot->next = node;
    } else {
        prev->next = slot;
        slot->next = node;
    }
    slot->word = word;
    Zi8LogError(0x64, ZI_WORK);
    return 1;
}

static ziU8* Zi8_814803F4(ziPtr __zi8_work_data) {
    ziU8* word;

    if (ZI_WORK->uwdCount != 0) {
        ZI_WORK->uwdCount--;
        word = ZI_WORK->uwdList->word;
        ZI_WORK->uwdList = ZI_WORK->uwdList->next;
        Zi8LogError(0x64, ZI_WORK);
        return word;
    }
    Zi8LogError(0x19e, ZI_WORK);
    return 0;
}

static void Zi8_8148047C(ziPtr __zi8_work_data) {
    Zi8Memset(ZI_WORK->uwdNodes, 0, 0x100);
    ZI_WORK->uwdCount = 0;
    ZI_WORK->uwdList = 0;
}

ziU8 Zi8MatchUWDdata(ziWChar* keys, ziU8 keyLen, ziWChar* word, ziU16 wordLen,
                     ziU8 lang, ziWChar* out, ziU16 maxLen, ziU8 flag8,
                     ziU8 flag9 ZI_NEED_WORK) {
    ziU8* base;
    ziU8* cur;
    ziU8* bound;
    ziU8* lim34;
    ziU8* lim30;
    ziU8* end2c;
    ziU32 flag28;
    ziU32 len24;
    ziS32 v20;
    ziS32 v1c;
    ziS32 len18;
    ziS32 j;
    ziS32 cnt;
    ziU32 flag_c;
    ziWChar wch;
    ziU8* p2;
    ziU8* w;
    ziS32 i;
    ziS32 n28;

    cnt = 0;
    flag_c = 0;
    Zi8LogError(0x64, ZI_WORK);
    if (ZI_WORK->unk_0x138 > 2 || ZI_WORK->unk_0x138 == 0 ||
        ZI_WORK->unk_0x130[ZI_WORK->unk_0x138 - 1] == 0) {
        Zi8ReplaceLastError(0x19c, ZI_WORK);
        return 0;
    }
    base = ZI_WORK->unk_0x130[ZI_WORK->unk_0x138 - 1];

    if (flag9 != 0) {
        w = Zi8_814803F4(ZI_WORK);
        len18 = 0;
        if (w != 0) {
            lang = w[1];
            len18 = w[2];
            if (len18 >= maxLen) {
                Zi8_8148047C(ZI_WORK);
                return 0;
            }
            w += 4;
            for (i = 0; i < len18; i++) {
                out[i] = Zi8ConvertUC2WC(w[i], lang, ZI_WORK);
            }
        }
        return (ziU8)len18;
    }

    Zi8_8148047C(ZI_WORK);
    ZI_WORK->unk_0x13C = 0;

    if (word != 0 && wordLen != 0 && word[wordLen - 1] == 0x20) {
        n28 = 0;
        i = wordLen - 2;
        while (i >= 0) {
            if (word[i] == 0x20) break;
            i--;
            n28++;
        }
        i++;
        if (n28 == 0 || n28 > 0x3F) {
            ZI_WORK->unk_0x140 = 0;
            goto L594;
        }
        ZI_WORK->unk_0x140 = 1;
        ZI_WORK->unk_0x141[0] = (ziU8)(n28 + 5);
        ZI_WORK->unk_0x141[4 + n28] = (ziU8)(n28 + 5);
        ZI_WORK->unk_0x141[1] = lang;
        ZI_WORK->unk_0x141[2] = (ziU8)n28;
        j = 4;
        while (n28 > 0) {
            wch = word[i];
            ZI_WORK->unk_0x141[j] = Zi8ConvertWC2UC(wch, lang, ZI_WORK);
            ZI_WORK->unk_0x184[j] = 0;
            if (ZI_WORK->unk_0x1F != 0) {
                if (Zi8ChangeCharCase(1, &wch, lang, ZI_WORK) == 0) {
                    Zi8ChangeCharCase(0, &wch, lang, ZI_WORK);
                }
                ZI_WORK->unk_0x184[j] = Zi8ConvertWC2UC(wch, lang, ZI_WORK);
            }
            j++;
            if (ZI_WORK->unk_0x141[j - 1] == 0) {
                ZI_WORK->unk_0x140 = 0;
                goto L594;
            }
            n28--;
            i++;
        }
    } else {
        ZI_WORK->unk_0x140 = 0;
    }

L594:
    if (ZI_WORK->unk_0x140 == 0 && keyLen == 0) {
        return 0;
    }

    bound = base + *(ziU16*)(base + 4) + 8;
    cur = bound;
    lim34 = base + *(ziU16*)(base + 6) + 7;
    lim30 = base + *(ziU16*)(base + 2) + 7;
    flag28 = (bound < lim34) ? 1 : 0;

    for (;;) {
L924:
        if (cur < lim34) {
            if (flag28 != 0) goto L628;
        }
        if (cur >= lim30) goto L95c;
        if (flag28 == 0) goto L628;
        goto L95c;

L628:
        len24 = *cur;
        if ((ziS32)(cnt++) < (ziS32)ZI_WORK->unk_0x13C || (*cur & 0xC0) != 0) {
            goto L660;
        }
        end2c = cur + len24;
        if (end2c > lim30) {
            end2c = base + (lim30 - cur) + 7;
        }
        p2 = cur;
        v20 = *p2++;
        v1c = *p2++;
        len18 = *p2++;
        p2++;
        if (v1c != lang) goto L660;
        if ((ziS32)len18 < (ziS32)keyLen) goto L660;
        if ((ziS32)len18 >= (ziS32)maxLen) goto L660;
        if (flag8 != 0) {
            if (len18 != keyLen) goto L660;
        } else {
            if (len18 == keyLen) goto L660;
        }
        for (i = 0; i < keyLen; i++) {
            if (keys[i] >= 0xEFF1 && keys[i] <= 0xF010) {
                if (Zi8ConvertUC2Key(p2[i], lang, ZI_WORK) != keys[i]) goto L660;
            } else {
                wch = Zi8ConvertUC2WC(p2[i], lang, ZI_WORK);
                if (wch != keys[i]) {
                    if (ZI_WORK->unk_0x1F == 0) goto L660;
                    if (Zi8ChangeCharCase(0, &wch, lang, ZI_WORK) == 0) goto L660;
                    if (wch != keys[i]) goto L660;
                }
            }
        }
        if (ZI_WORK->unk_0x140 != 0) {
            if (ZI_WORK->unk_0x141[0] != end2c[0]) goto L660;
            if (ZI_WORK->unk_0x141[1] != end2c[1]) goto L660;
            if (ZI_WORK->unk_0x141[2] != end2c[2]) goto L660;
            for (j = 4; j < ZI_WORK->unk_0x141[2] + 4; j++) {
                if (ZI_WORK->unk_0x141[j] != end2c[j] &&
                    ZI_WORK->unk_0x184[j] != end2c[j]) {
                    goto L660;
                }
            }
        }
        Zi8_81480224(cur, ZI_WORK);
L660:
        cur += len24;
        if (cur <= lim30) goto L924;
        if (flag28 != 0) goto L95c;
        flag28 = 1;
        len24 = cur - lim30 - 1;
        cur = base + len24 + 8;
    }

L95c:
    if (ZI_WORK->unk_0x140 != 0 && keyLen != 0) {
        ZI_WORK->unk_0x140 = 0;
        cnt = 0;
        goto L594;
    }
    if (keyLen == 1 && flag8 != 0 && flag9 == 0) {
        flag8 = 0;
        flag_c = 1;
        cnt = 0;
        goto L594;
    }
    w = Zi8_814803F4(ZI_WORK);
    if (w != 0) {
        lang = w[1];
        len18 = w[2];
        if (len18 >= maxLen) {
            Zi8_8148047C(ZI_WORK);
            return 0;
        }
        w += 4;
        for (i = 0; i < len18; i++) {
            out[i] = Zi8ConvertUC2WC(w[i], lang, ZI_WORK);
        }
        return (ziU8)len18;
    }
    return 0;
}
