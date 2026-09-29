#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>

extern ziU32 Zi8GetTableAddress(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);
extern ziU16 Zi8MatchAltSound(ziU8* elements, ziU16 count, ziU8* table, ziU16 ch,
                              ziU32 mask, ziU16 target, ziU8 flags ZI_NEED_WORK);

ziU8 Zi8GetPyFinal(ziU8* s, ziU8* o1, ziU8* o2);
ziU16 Zi8GetPCode(ziU8* table, ziU8* p);

static const ziU8 Zi8PinyinInitials[0x1C] = {
    0x00, 0x3c, 0x98, 0x02, 0x00, 0x38, 0x34, 0x3b,
    0x00, 0x06, 0x37, 0x2b, 0x0c, 0x26, 0x00, 0x3f,
    0x09, 0x2c, 0x9a, 0x05, 0x00, 0x00, 0x11, 0x0a,
    0x0d, 0x9c, 0x00, 0x00
};

static const ziU8 Zi8BpmfInitials[0x24] = {
    0x3c, 0x3f, 0x0c, 0x38, 0x02, 0x05, 0x26, 0x2b,
    0x34, 0x37, 0x3b, 0x06, 0x09, 0x0a, 0x1d, 0x19,
    0x1b, 0x2c, 0x1c, 0x18, 0x1a, 0x01, 0x02, 0x03,
    0x05, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0e, 0x0d,
    0x0f, 0x04, 0x00, 0x00
};

static const ziU8 Zi8PinyinFinals[0x36][8] = {
    {0x0f, 0xff, 0x00, 0x00, 0x3c, 0x28, 0x00, 0x00},
    {0x0f, 0x00, 0x00, 0x00, 0x3f, 0x2b, 0x00, 0x00},
    {0x0f, 0x0e, 0xff, 0x00, 0x3f, 0x28, 0x00, 0x00},
    {0x0f, 0x0e, 0x07, 0x00, 0x3f, 0x28, 0x00, 0x00},
    {0x0f, 0x15, 0x00, 0x00, 0x3f, 0x2a, 0x00, 0x00},
    {0x09, 0xff, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00},
    {0x09, 0x00, 0x00, 0x00, 0x3f, 0x08, 0x00, 0x00},
    {0x09, 0x01, 0xff, 0x00, 0x38, 0x00, 0x00, 0x00},
    {0x09, 0x01, 0x00, 0x00, 0x3f, 0x04, 0x00, 0x00},
    {0x09, 0x01, 0x0f, 0x00, 0x3f, 0x01, 0x00, 0x00},
    {0x09, 0x01, 0x0e, 0xff, 0x3e, 0x02, 0x00, 0x00},
    {0x09, 0x01, 0x0e, 0x00, 0x3f, 0x02, 0x00, 0x00},
    {0x09, 0x01, 0x0e, 0x07, 0x3f, 0x03, 0x00, 0x00},
    {0x09, 0x05, 0x00, 0x00, 0x3f, 0x09, 0x00, 0x00},
    {0x09, 0x15, 0x00, 0x00, 0x3f, 0x0b, 0x00, 0x00},
    {0x09, 0x0e, 0xff, 0x00, 0x3e, 0x0c, 0x00, 0x00},
    {0x09, 0x0e, 0x00, 0x00, 0x3f, 0x0c, 0x00, 0x00},
    {0x09, 0x0e, 0x07, 0x00, 0x3f, 0x0d, 0x00, 0x00},
    {0x09, 0x0f, 0xff, 0x00, 0x3e, 0x0e, 0x00, 0x00},
    {0x09, 0x0f, 0x15, 0x00, 0x3f, 0x0e, 0x00, 0x00},
    {0x09, 0x0f, 0x0e, 0xff, 0x3f, 0x0f, 0x00, 0x00},
    {0x09, 0x0f, 0x0e, 0x07, 0x3f, 0x0f, 0x00, 0x00},
    {0x15, 0xff, 0x00, 0x00, 0x30, 0x10, 0x00, 0x00},
    {0x15, 0x00, 0x00, 0x00, 0x3f, 0x18, 0x00, 0x00},
    {0x15, 0x01, 0xff, 0x00, 0x38, 0x10, 0x00, 0x00},
    {0x15, 0x01, 0x00, 0x00, 0x3f, 0x17, 0x00, 0x00},
    {0x15, 0x01, 0x0e, 0xff, 0x3e, 0x10, 0x00, 0x00},
    {0x15, 0x01, 0x0e, 0x00, 0x3f, 0x10, 0x00, 0x00},
    {0x15, 0x01, 0x0e, 0x07, 0x3f, 0x11, 0x00, 0x00},
    {0x15, 0x01, 0x09, 0x00, 0x3f, 0x13, 0x00, 0x00},
    {0x15, 0x0e, 0x00, 0x00, 0x3f, 0x1c, 0x00, 0x00},
    {0x15, 0x09, 0x00, 0x00, 0x3f, 0x1d, 0x00, 0x00},
    {0x15, 0x0f, 0x00, 0x00, 0x3f, 0x1e, 0x00, 0x00},
    {0x15, 0x05, 0x00, 0x00, 0x3f, 0x1f, 0x00, 0x00},
    {0x01, 0xff, 0x00, 0x00, 0x38, 0x20, 0x00, 0x00},
    {0x01, 0x00, 0x00, 0x00, 0x3f, 0x23, 0x00, 0x00},
    {0x01, 0x0e, 0xff, 0x00, 0x3e, 0x20, 0x00, 0x00},
    {0x01, 0x0e, 0x00, 0x00, 0x3f, 0x20, 0x00, 0x00},
    {0x01, 0x0e, 0x07, 0x00, 0x3f, 0x21, 0x00, 0x00},
    {0x01, 0x09, 0x00, 0x00, 0x3f, 0x25, 0x00, 0x00},
    {0x01, 0x0f, 0x00, 0x00, 0x3f, 0x26, 0x00, 0x00},
    {0x05, 0xff, 0x00, 0x00, 0x38, 0x30, 0x00, 0x00},
    {0x05, 0x00, 0x00, 0x00, 0x3f, 0x34, 0x00, 0x00},
    {0x05, 0x0e, 0xff, 0x00, 0x3e, 0x30, 0x00, 0x00},
    {0x05, 0x0e, 0x00, 0x00, 0x3f, 0x30, 0x00, 0x00},
    {0x05, 0x0e, 0x07, 0x00, 0x3f, 0x31, 0x00, 0x00},
    {0x05, 0x09, 0x00, 0x00, 0x3f, 0x35, 0x00, 0x00},
    {0x05, 0x12, 0x00, 0x00, 0x3f, 0x33, 0x00, 0x00},
    {0x16, 0xff, 0x00, 0x00, 0x3c, 0x38, 0x00, 0x00},
    {0x16, 0x00, 0x00, 0x00, 0x3f, 0x38, 0x00, 0x00},
    {0x16, 0x01, 0xff, 0x00, 0x3f, 0x39, 0x00, 0x00},
    {0x16, 0x01, 0x0e, 0x00, 0x3f, 0x39, 0x00, 0x00},
    {0x16, 0x05, 0x00, 0x00, 0x3f, 0x1f, 0x00, 0x00},
    {0x16, 0x0e, 0x00, 0x00, 0x3f, 0x3b, 0x00, 0x00}
};

const ziU16 zi8PyFinalIdx[0x10] = {
    0x0010, 0x0001, 0x0003, 0x0014, 0x0005, 0x0007, 0x001c, 0x000d,
    0x000f, 0x0011, 0x0013, 0x0015, 0x0017, 0x001d, 0x001f, 0x0035
};

ziU8 Zi8PriMatchNextChar(ziU8* p, ziU8 m0, ziU8 v0, ziU8 m1, ziU8 v1, ziU8 m2,
                         ziU8 v2, ziU8 m3, ziU8 v3, ziU16* count, ziU8** match,
                         ziU16* index ZI_NEED_WORK) {
    ziU16 n;

    n = *count;
    while (n-- != 0) {
        if ((p[0] & m0) == v0 && (p[3] & m3) == v3 && (p[2] & m2) == v2 &&
            (p[1] & m1) == v1) {
            *match = p;
            *index = (ziU16)(((ziU8)p[6] << 8) + p[7]);
            *count = n;
            Zi8LogError(0x64, ZI_WORK);
            return 1;
        }
        p += 0xC;
    }
    Zi8LogError(0x12E, ZI_WORK);
    return 0;
}

ziU8 Zi8ExactMatchNextChar(ziU8* p, ziU8 m0, ziU8 v0, ziU8 m1, ziU8 v1, ziU8 m2,
                           ziU8 v2, ziU8 m3, ziU8 v3, ziU16* count, ziU8** match,
                           ziU16* index ZI_NEED_WORK) {
    ziU8* q;
    ziU16 n;

    n = *count;
    q = p;
    while (n-- != 0) {
        if ((q[0] & m0) == v0 && (q[3] & m3) == v3 && (q[2] & m2) == v2 &&
            (q[1] & m1) == v1) {
            *match = q;
            *index = (ziU16)(((ziU8)q[6] << 8) + q[7]);
            *count = n;
            Zi8LogError(0x64, ZI_WORK);
            return 1;
        }
        q += 0xC;
    }
    Zi8LogError(0x12E, ZI_WORK);
    return 0;
}

ziU8 Zi8SecMatchChar(ziU8* p, ziU8* table, ziMatchParam* prm, ziU16* out ZI_NEED_WORK) {
    ziU16 f22;
    ziU16 idx;
    ziU8 i;
    ziU8* e;
    ziU8 m;
    ziU8 n;
    ziU8 flag;

    flag = 0;
    if (prm->field22 != 0) {
        f22 = prm->field22;
        idx = (ziU16)(((ziU8)(p[4] & 3) << 8) | p[5]);
        i = 0;
        while (i++ < 6) {
            if ((ziU16)f22 == idx) {
                break;
            }
            idx = (ziU16)(((ziU8)(*(table + idx * 8 + 6) & 3) << 8) |
                         *(table + idx * 8 + 7));
            if (idx == 0) {
                break;
            }
        }
        if ((ziU16)f22 != idx) {
            return 0;
        }
    }

    e = (ziU8*)Zi8GetTableAddress(1, 1, ZI_WORK);
    e += ((ziU32)(p[9] & 0xF) << 16) + p[0xB] + (p[0xA] << 8);

    if (ZI_WORK->unk_0x16 != 0) {
        switch (*e & 7) {
            case 2:
                e += 2;
                break;
            case 3:
            case 4:
                e += 3;
                break;
            case 5:
                e += 4;
                break;
            default:
                e += 1;
                break;
        }
    }

    i = *e;
    i = (ziU8)((i >> 4) & 7);
    if (i * 2 + 0xA < (ziS32)prm->length) {
        return 0;
    }

    if (prm->length < 9) {
        if (prm->length == 8) {
            if ((*e & 0xF) == 0xF) {
                flag = 1;
            }
        } else if ((prm->length & 1) != 0) {
            if ((p[(ziS32)prm->length >> 1] & 0xF) == 0xF) {
                flag = 1;
            }
        } else {
            if ((p[(ziS32)prm->length >> 1] & 0xF0) == 0xF0) {
                flag = 1;
            }
        }

        if (prm->length > 2) {
            if ((prm->length & 1) != 0) {
                if ((p[((ziS32)prm->length - 1) >> 1] & 0xF0) == 0 ||
                    (p[((ziS32)prm->length - 1) >> 1] & 0xF0) == 0xF0) {
                    return 0;
                }
            } else {
                if ((p[((ziS32)prm->length - 1) >> 1] & 0xF) == 0 ||
                    (p[((ziS32)prm->length - 1) >> 1] & 0xF) == 0xF) {
                    return 0;
                }
            }
        }

        if (out != 0) {
            *out = (ziU16)(((ziU16)p[6] << 8) + p[7]);
        }
        if (flag != 0) {
            return 2;
        }
        return 1;
    }

    if ((prm->length & 1) != 0) {
        if ((*(((ziS32)prm->length - 1 >> 1) + e - 4) & 0xF0) == 0 ||
            (*(((ziS32)prm->length - 1 >> 1) + e - 4) & 0xF0) == 0xF0) {
            return 0;
        }
    } else {
        if ((*(((ziS32)prm->length - 1 >> 1) + e - 4) & 0xF) == 0 ||
            (*(((ziS32)prm->length - 1 >> 1) + e - 4) & 0xF) == 0xF) {
            return 0;
        }
    }

    m = 4;
    n = (ziU8)((((ziS32)prm->length + 1) >> 1) - 4);
    if (i + 1 < (ziS32)n) {
        return 0;
    }

    if ((prm->length & 1) != 0) {
        if ((*(((ziS32)prm->length >> 1) + e - 4) & 0xF) == 0xF) {
            flag = 1;
        }
    } else {
        if ((*(((ziS32)prm->length >> 1) + e - 4) & 0xF0) == 0xF0) {
            flag = 1;
        }
    }

    if (prm->count == 0) {
        while (n != 0) {
            if ((*e & prm->arr1[m]) != prm->arrD[m]) {
                return 0;
            }
            m++;
            n--;
            e++;
        }
    }

    if (out != 0) {
        *out = (ziU16)(((ziU16)p[6] << 8) + p[7]);
    }
    if (flag != 0) {
        return 2;
    }
    return 1;
}

ziU8 Zi8PriMatchNextComp(ziU8* p, ziU8 m0, ziU8 v0, ziU8 m1, ziU8 v1, ziU8 m2,
                         ziU8 v2, ziU8 m3, ziU8 v3, ziU16* count,
                         ziU8** match ZI_NEED_WORK) {
    ziU16 n;

    n = *count;
    while (n-- != 0) {
        if ((p[0] & m0) == v0 && (p[1] & m1) == v1 && (p[2] & m2) == v2 &&
            (p[3] & m3) == v3) {
            *match = p;
            *count = n;
            Zi8LogError(0x64, ZI_WORK);
            return 1;
        }
        p += 8;
    }
    Zi8LogError(0x12E, ZI_WORK);
    return 0;
}

ziU8 Zi8SecMatchComp(ziU8* p, ziMatchParam* prm, ziU8* table) {
    ziU16 f22;
    ziU16 idx;
    ziS32 i;

    if (prm->field22 != 0) {
        f22 = prm->field22;
        idx = (ziU16)(((ziU8)(p[6] & 3) << 8) | p[7]);
        i = 0;
        while (i++ < 6) {
            if ((ziU16)f22 == idx) {
                break;
            }
            idx = (ziU16)(((ziU8)(table[idx * 8 + 6] & 3) << 8) |
                         table[idx * 8 + 7]);
            if (idx == 0) {
                break;
            }
        }
        if ((ziU16)f22 != idx) {
            return 0;
        }
    }

    if (prm->length > 8) {
        if (p[5] < (ziS32)(prm->length - 2)) {
            return 0;
        }
    } else {
        if (p[5] < (ziS32)(prm->length - 1)) {
            return 0;
        }
    }
    return 1;
}

ziU8 Zi8MatchPhonetic(ziU8* tblA, ziU8* tblB, ziU8* elements, ziU16 count16,
                      ziU8* tblC, ziU8* row, ziU16* masks, ziU16* vals,
                      ziU16* countP, ziU8** out, ziU32* limit, ziU8 a4, ziU8 a5,
                      ziU8 len, ziU16 m5, ziU16 v5, ziU8 mask, ziU8 flag,
                      ziU16 total, ziU16* out2, ziU8 aC ZI_NEED_WORK) {
    ziU8 limf;
    ziU16 n;
    ziU16 pos;
    ziU8 hits;
    ziU8 cnt;
    ziU8 cnt2;
    ziU8 cur;
    ziU16 w16;
    ziU16 res;
    ziU8* e;

    limf = (*limit != 0) ? 1 : 0;
    n = (*countP != 0) ? *countP : 1;
    hits = 0;
    if (aC != 0 && (ziU8)len > 1) {
        flag = 1;
    }

    while (n-- != 0) {
        if ((row[0] & mask) == 0) {
            row += 0xC;
            continue;
        }
        res = Zi8GetPCode(tblA, row);
        if ((ziU16)vals[0] != (ziU16)(res & masks[0]) && flag == 0 &&
            (row[0] & 0x80) != 0) {
            if (*countP != 0) {
                pos = (ziU16)(total - n - 1);
            } else {
                pos = total;
            }
            res = Zi8MatchAltSound(elements, count16, tblA, pos, masks[0],
                                   vals[0], mask, ZI_WORK);
        }
        if ((ziU16)vals[0] != (ziU16)(res & masks[0])) {
            row += 0xC;
            continue;
        }
        if ((ziU16)v5 == (ziU16)(res & m5)) {
            row += 0xC;
            continue;
        }
        hits = 1;
        if (*countP != 0) {
            pos = (ziU16)(total - n - 1);
        } else {
            pos = total;
        }
        e = tblC + (row[0xA] << 8) + row[0xB] + ((ziU32)(row[9] & 0xF) << 16);
        if (ZI_WORK->unk_0x16 != 0) {
            switch (*e & 7) {
                case 5:
                    e += 4;
                    break;
                case 2:
                    e += 2;
                    break;
                case 3:
                case 4:
                    e += 3;
                    break;
                default:
                    e += 1;
                    break;
            }
        }
        if ((*e & 0x80) != 0) {
            e += ((*e & 0x7F) >> 4) + 1;
        } else {
            if ((ziU8)len > 1) {
                row += 0xC;
                continue;
            }
        }
        do {
            if ((ziU8)hits == (ziU8)len || (ziU8)len == 0) {
                goto done;
            }
            cur = *e++;
            cnt = (ziU8)(cur & 0xF);
            if ((cur & mask) == 0) {
                while (cnt != 0) {
                    e++;
                    while ((*e & 0x80) == 0) {
                        e += 2;
                    }
                    e++;
                    cnt--;
                }
            }
            while (cnt != 0) {
                cnt2 = 1;
                for (;;) {
                    if (limf != 0 && e > (ziU8*)*limit) {
                        limf = 0;
                    }
                    if (limf == 0) {
                        *limit = (ziU32)e;
                    }
                    w16 = (ziU16)(e[0] | (e[1] << 8));
                    e += 2;
                    if (limf == 0) {
                        res = Zi8GetPCode(tblA,
                                          tblB + (w16 & 0x7FFF) * 0xC);
                        if ((ziU16)(res & masks[cnt2]) != vals[cnt2] &&
                            flag == 0 &&
                            (tblB[(w16 & 0x7FFF) * 0xC] & 0x80) != 0) {
                            res = Zi8MatchAltSound(elements, count16, tblA,
                                                   (ziU16)(w16 & 0x7FFF),
                                                   masks[cnt2], vals[cnt2],
                                                   mask, ZI_WORK);
                        }
                    }
                    if ((ziU16)(res & masks[cnt2]) == vals[cnt2]) {
                        cnt2++;
                        if ((ziU8)cnt2 == (ziU8)len) {
                            if (a4 == 0 ||
                                ((a5 != 0) == ((w16 & 0x8000) != 0))) {
                                goto done;
                            }
                            goto skipw;
                        }
                        if ((w16 & 0x8000) == 0) {
                            continue;
                        }
                        break;
                    }
                skipw:
                    if ((w16 & 0x8000) == 0) {
                        e++;
                        while ((*e & 0x80) == 0) {
                            e += 2;
                        }
                        e++;
                    }
                    break;
                }
                cnt--;
            }
        } while ((cur & 0x80) == 0);
        row += 0xC;
    }
    return 0;

done:
    *out = row;
    *out2 = (ziU16)((row[6] << 8) + row[7]);
    *countP = n;
    return 1;
}

ziU8 Zi8GetPyPhonetic(ziWChar* in, ziU8 len, ziWChar* a, ziWChar* b, ziU8* nSyl,
                      ziU16* d, ziU16* e ZI_NEED_WORK) {
    ziWChar buf[0x100];
    ziWChar* p;
    ziWChar c;
    ziU8 x;
    ziU8 y;
    ziU8 flagC;
    ziU8 flagD;
    ziU8 len2;
    ziU8 i;
    ziU8 j;
    ziU8 buf2[4];
    ziU8 f11;
    ziU8 f10;

    p = buf;
    flagC = 0;
    y = 0;
    *nSyl = 0;
    if (len == 0) {
        Zi8LogError(0x135, ZI_WORK);
        return 0;
    }
    i = 0;
    len2 = 0;
    for (i = 0; (ziU8)i < len; i++) {
        c = in[i];
        if ((c >= 0xF341 && c <= 0xF35A) || (c >= 0x41 && c <= 0x5A)) {
            if (len2 != 0 && p[len2 - 1] != 0xF360 && p[len2 - 1] != 0x27) {
                p[len2] = 0x27;
                len2 += 1;
            }
            p[len2] = (ziWChar)((ziU8)c + 0x20);
            len2 += 1;
        } else {
            p[len2] = c;
            len2 += 1;
        }
    }
    len = len2;
    j = 0;
    *d = 0;
    *e = 0;

    while ((ziU8)j <= 0xF && len != 0) {
        a[j] = 0;
        b[j] = 0;
        c = *p;
        if (c >= 0x61 && c <= 0x7A) {
            c -= 0x61;
        } else if (c >= 0xF361 && c <= 0xF37A) {
            c -= 0xF361;
        } else {
fail:
            *b = *a = *e = *d = 0xFFFF;
            return 1;
        }
        x = Zi8PinyinInitials[c];
        if (x != 0) {
            if (j == 0) {
                *nSyl = (ziU8)(*nSyl + 1);
            }
            y++;
            a[j] = 0x7E00;
            b[j] = (ziWChar)((x & 0x7F) << 9);
            *d = *a;
            *e = *b;
            len--;
            if (len == 0) {
                goto out;
            }
            p++;
            if ((x & 0x80) != 0) {
                if (flagC != 0) {
                    a[j] &= 0xFDFF;
                    b[j] &= 0xFDFF;
                }
                c = *p;
                if (c == 0x68 || c == 0xF368) {
                    if (j == 0) {
                        *nSyl = (ziU8)(*nSyl + 1);
                    }
                    b[j] += 0x200;
                    *d = *a;
                    *e = *b;
                    len--;
                    if (len == 0) {
                        goto out;
                    }
                    p++;
                }
            }
        } else {
            if (*p == 0xF369 || *p == 0x69) {
                goto fail;
            }
        }
        flagD = 0;
        for (i = 0; (ziU8)i < 4; i++) {
            buf2[i] = 0;
        }
        i = 0;
        while ((ziU8)i < 4) {
            c = *p;
            if (c == 0x27 || c == 0xF360 || c == 0x20) {
                if (i != 0) {
                    flagD = 1;
                }
                break;
            }
            if (c >= 0xF331 && c < 0xF336) {
                if (i != 0) {
                    flagD = 1;
                }
                break;
            }
            if (!(c >= 0x61 && c <= 0x7A)) {
                if (c < 0xF361) {
                    break;
                }
                c -= 0xF361;
                if (c > 0x19) {
                    if (j == 0) {
                        *nSyl = (ziU8)(*nSyl + 1);
                    }
                    break;
                }
            } else {
                c -= 0x61;
            }
            buf2[i] = (ziU8)((ziU16)c + 1);
            if (Zi8GetPyFinal(buf2, &f11, &f10) != 0) {
                if (j == 0) {
                    *nSyl = (ziU8)(*nSyl + 1);
                }
                p++;
                i++;
                len--;
                if (len == 0) {
                    break;
                }
                continue;
            }
            if (i < 3) {
                buf2[i + 1] = 0xFF;
                if (Zi8GetPyFinal(buf2, &f11, &f10) != 0) {
                    if (j == 0) {
                        *nSyl = (ziU8)(*nSyl + 1);
                    }
                    buf2[i + 1] = 0;
                    p++;
                    i++;
                    len--;
                    if (len == 0) {
                        break;
                    }
                    continue;
                }
                buf2[i + 1] = 0;
                buf2[i] = 0;
                flagD = 1;
                break;
            }
            buf2[i] = 0;
            flagD = 1;
            break;
        }
        if ((ziU8)i > 3 && len != 0) {
            c = *p;
            if (c == 0x27 || c == 0xF360 || c == 0x20) {
                if (j == 0) {
                    *nSyl = (ziU8)(*nSyl + 1);
                }
                p++;
                len--;
            }
        }
        if ((ziU8)i > 3) {
            flagD = 1;
        }
        if (flagD != 0 && flagC == 0) {
            if (Zi8GetPyFinal(buf2, &f11, &f10) != 0) {
                if (x == 0) {
                    y++;
                    a[j] = 0x7E00;
                    b[j] = 0x200;
                }
                a[j] |= (ziWChar)(f11 << 3);
                b[j] |= (ziWChar)(f10 << 3);
                *d = *a;
                *e = *b;
                goto tail;
            }
            if (i == 0) {
                goto tail;
            }
            if (len != 0) {
                goto fail;
            }
            goto tail;
        }
        buf2[i] = 0xFF;
        if (Zi8GetPyFinal(buf2, &f11, &f10) != 0) {
            if (x == 0) {
                y++;
                a[j] = 0x7E00;
                b[j] = 0x200;
            }
            a[j] |= (ziWChar)(f11 << 3);
            b[j] |= (ziWChar)(f10 << 3);
            *d = *a;
            *e = *b;
            if (j == 0 && len == 0) {
                buf2[i] = 0;
                if (Zi8GetPyFinal(buf2, &f11, &f10) != 0) {
                    if (x == 0) {
                        *d = 0x7E00;
                        *e = 0x200;
                    }
                    *d |= (ziU16)(f11 << 3);
                    *e |= (ziU16)(f10 << 3);
                }
            }
            goto tail;
        }
        buf2[i] = 0;
        if (Zi8GetPyFinal(buf2, &f11, &f10) != 0) {
            if (x == 0) {
                y++;
                a[j] = 0x7E00;
                b[j] = 0x200;
            }
            a[j] |= (ziWChar)(f11 << 3);
            b[j] |= (ziWChar)(f10 << 3);
            *d = *a;
            *e = *b;
            goto tail;
        }
tail:
        if (len == 0) {
            goto out;
        }
        c = *p;
        if (c == 0x27 || c == 0xF360 || c == 0x20) {
            p++;
            len--;
            if (j == 0) {
                *nSyl = (ziU8)(*nSyl + 1);
            }
            goto out;
        }
        if (c < 0xF331) {
            goto out;
        }
        c -= 0xF331;
        if (c > 4) {
            goto out;
        }
        c++;
        a[j] |= 7;
        b[j] |= c;
        *d = *a;
        *e = *b;
        len--;
        p++;
        if (j == 0) {
            *nSyl = (ziU8)(*nSyl + 1);
        }
        if (len == 0) {
            goto out;
        }
        c = *p;
        if (c == 0x27 || c == 0xF360 || c == 0x20) {
            len--;
            p++;
            if (j == 0) {
                *nSyl = (ziU8)(*nSyl + 1);
            }
        }
out:
        j++;
    }

    if ((ziU8)y > 1) {
        c = in[*nSyl - 1];
        if (c >= 0xF341 && c <= 0xF35A) {
            *nSyl = (ziU8)(*nSyl - 1);
        }
    }
    return y;
}

ziU8 Zi8GetPyFinal(ziU8* s, ziU8* o1, ziU8* o2) {
    ziU8 i;
    ziU8 j;

    i = 0;
    j = 0;
    while ((ziU8)j < 0x36) {
        while ((ziU8)i < 4 && s[i] == Zi8PinyinFinals[j][i]) {
            i++;
        }
        if ((ziU8)i >= 4) {
            *o1 = Zi8PinyinFinals[j][4];
            *o2 = Zi8PinyinFinals[j][5];
            return 1;
        }
        j++;
        i = 0;
    }
    return 0;
}

ziU8 Zi8GetBpmfPhonetic(ziWChar* in, ziU8 count, ziU16* a, ziU16* b, ziU16* d,
                        ziU16* e ZI_NEED_WORK) {
    ziU16 c;
    ziU16 idx;
    ziU8 n;

    n = 0;
    Zi8LogError(0x64, ZI_WORK);
    if (count == 0) {
        Zi8ReplaceLastError(0x135, ZI_WORK);
        return 0;
    }
    c = *in;
    if (c < 0xF305) {
        Zi8ReplaceLastError(0x154, ZI_WORK);
        return 0;
    }
    idx = c - 0xF305;
    if (idx >= 0x25) {
        Zi8ReplaceLastError(0x154, ZI_WORK);
        return 0;
    }
    if (idx < 0x15) {
        *a = 0x7E00;
        *b = (ziU16)((Zi8BpmfInitials[idx] & 0x7F) << 9);
        n++;
        count--;
        if (count == 0) {
            *d = *a;
            *e = *b;
            if (idx >= 0xE && idx <= 0x14) {
                *d |= 0x1F8;
                *e |= 0x38;
            }
            return n;
        }
        in++;
        if (*in == 0xF360) {
            n++;
            count--;
            if (count == 0) {
                return n;
            }
            Zi8ReplaceLastError(0x156, ZI_WORK);
            return 0;
        }
    } else {
        *a = 0x7E00;
        *b = 0x200;
    }

    c = *in;
    idx = c - 0xF305;
    switch (idx) {
        case 0x22:
            *b |= 0x80;
            *a |= 0x180;
            n++;
            count--;
            if (count == 0) {
                *d = *a | 0x78;
                *e = *b | 0x38;
                return n;
            }
            in++;
            break;
        case 0x23:
            *b |= 0x100;
            *a |= 0x180;
            n++;
            count--;
            if (count == 0) {
                *d = *a | 0x78;
                *e = *b | 0x38;
                return n;
            }
            in++;
            break;
        case 0x24:
            *b |= 0x180;
            *a |= 0x180;
            n++;
            count--;
            if (count == 0) {
                *d = *a | 0x78;
                *e = *b | 0x38;
                return n;
            }
            in++;
            break;
        default:
            if (*in < 0xF331 || *in > 0xF335) {
                *a |= 0x180;
            }
            break;
    }

    c = *in;
    idx = c - 0xF305;
    if (idx <= 0x14 || idx >= 0x22) {
        if (*in < 0xF331 || *in > 0xF335 || (*a & 0x180) == 0x180) {
            *b |= 0x38;
            *a |= 0x78;
        }
    } else {
        *b |= Zi8BpmfInitials[idx] << 3;
        *a |= 0x78;
        n++;
        count--;
        if (count == 0) {
            *d = *a;
            *e = *b;
            return n;
        }
        in++;
    }

    c = *in;
    if (c < 0xF331) {
        Zi8ReplaceLastError(0x155, ZI_WORK);
        return 0;
    }
    idx = c - 0xF331;
    if (idx > 5) {
        Zi8ReplaceLastError(0x155, ZI_WORK);
        return 0;
    }
    *a |= 7;
    *b |= idx;
    *d = *a;
    *e = *b;
    n++;
    count--;
    if (count != 0) {
        Zi8ReplaceLastError(0x157, ZI_WORK);
        return 0;
    }
    return n;
}

ziU16 Zi8GetPCode(ziU8* table, ziU8* p) {
    ziU16 idx;

    idx = (ziU16)(((ziU16)p[8] << 2) | (((ziU16)p[9] & 0x80) >> 6));
    return (ziU16)((((ziU16)p[9] >> 4) & 7) | table[idx] |
                   ((ziU16)table[idx + 1] << 8));
}
