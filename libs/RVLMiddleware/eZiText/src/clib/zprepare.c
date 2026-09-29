#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>

extern ziU32 Zi8GetTableAddress(ziU8, ziU8 ZI_NEED_WORK);
extern ziU16 Zi8GetTableCount(ziU8, ziU8 ZI_NEED_WORK);
extern ziBool Zi8IsComponent(ziWChar ZI_NEED_WORK);
extern void Zi8Memset(ziPtr, ziU32, ziU32);
extern void Zi8Memcpy(ziPtr, ziPtr, ziU32);
extern ziU8 Zi8GetPyPhonetic(ziWChar*, ziU8, ziWChar*, ziWChar*, ziU8*, ziWChar*, ziWChar* ZI_NEED_WORK);
extern ziU8 Zi8GetBpmfPhonetic(ziWChar*, ziU8, ziU16*, ziU16*, ziU16*, ziU16* ZI_NEED_WORK);

ziU16 Zi8PrepareMatch(ziGetParam* prm, ziMatchParam* out, ziU8 flag ZI_NEED_WORK)
{
    ziU8 len8;
    ziU8 m;
    ziU8 minLen;
    ziU8 c2;
    ziU8 cnt;
    ziU8 n;
    ziU8 flag2;
    ziU16 v10;
    ziU16 v12;
    ziU16 v14;
    ziU16 v16;
    ziU16 v18;
    ziU16 v1a;
    ziU16 j2;
    ziU16 v1e;
    ziU16 v20;
    ziU16 v22;
    ziU16 tN;
    ziWChar x;
    ziWChar* ptr;
    ziU8* t;
    ziU8 buf30[4];
    ziU8 buf34[4];
    ziU8* t2;
    ziU8* t6;
    ziU8 arr40[0xC];
    ziU8 arr4c[0xC];
    ziU8 ret;
    ziU8 i;

    c2 = 0;
    minLen = 0x20;
    Zi8Memset(out, 0, 0x1ee);
    flag2 = 0;
    ret = 0;
    cnt = 0;
    n = prm->elementCount;

    while (n != 0) {
        if (prm->elements[n - 1] != 0xef09) {
            break;
        }
        n--;
    }
    out->count = n;

    for (i = 0; i < n; i++) {
        if (prm->elements[i] != 0xef00) {
            out->count = 0;
            goto L_main;
        }
    }

L_main:
    if (n != 0) {
        out->comp = x = prm->elements[0];
        if (Zi8IsComponent(x, ZI_WORK) != 0) {
            cnt++;
            flag2 = 1;

            t6 = (ziU8*)Zi8GetTableAddress(1, 2, ZI_WORK);
            t2 = (ziU8*)Zi8GetTableAddress(1, 6, ZI_WORK);
            t2 += ((ziS32)x - 0xef10) * 2;
            out->field22 = (ziU16)(((t2[1] & 0x3f) << 8) + t2[0]);
            t6 += out->field22 * 8;

            switch (t6[0] & 0xf) {
            case 1:
                out->comp = 0xef04;
                break;
            case 2:
                out->comp = 0xef01;
                break;
            case 3:
            case 11:
                out->comp = 0xef07;
                break;
            case 4:
                out->comp = 0xef06;
                break;
            case 5:
                out->comp = 0xef03;
                break;
            case 6:
                out->comp = 0xef05;
                break;
            case 7:
                out->comp = 0xef08;
                break;
            case 8:
                out->comp = 0xef02;
                break;
            default:
                break;
            }

            for (i = 0; i < (t6[5] >> 1) + 1; i++) {
                if (i < 4) {
                    out->arrD[i] = t6[i];
                    out->arr1[i] = 0xff;
                }
            }
            if (i != 0 && (t6[5] & 1) == 0) {
                i--;
                out->arrD[i] &= 0xf0;
                out->arr1[i] &= 0xf0;
            }
            ret = t6[5] + 1;
            if (ret > 8) {
                ret++;
            }
        }
    }

    out->arr1[0] &= 0xf;
    out->arrD[0] &= 0xf;

    if (flag == 0) {
        m = 0;
        if ((prm->subLanguage & 0x80) || (prm->subLanguage & 0x40)) {
            m = 1;
        } else if (prm->subLanguage & 0x08) {
            m = 4;
        } else if ((prm->subLanguage & 0x20) || (prm->subLanguage & 0x10)) {
            m = 2;
        }
        if (m == 0) {
            m = prm->subLanguage;
        }
        switch (m) {
        case 1:
        case 2:
        case 4:
            out->arr1[0] |= m << 4;
            out->arrD[0] |= m << 4;
            break;
        }
    }

    if (ret == 0) {
        ret = 1;
    }

    if (prm->getMode != 0 && prm->getMode != 0x10 && prm->getMode != 5) {
        goto L_phonetic;
    }

    Zi8Memcpy(arr4c, out->arr1, 0xc);
    Zi8Memcpy(arr40, out->arrD, 0xc);

    for (;;) {
    while (cnt < n) {
        x = prm->elements[cnt++];
        switch (x) {
        case 0xef02:
            c2 = 0;
            break;
        case 0xef04:
            c2 = 1;
            break;
        case 0xef01:
            c2 = 2;
            break;
        case 0xef07:
            c2 = 3;
            break;
        case 0xef06:
            c2 = 4;
            break;
        case 0xef03:
            c2 = 5;
            break;
        case 0xef05:
            c2 = 6;
            break;
        case 0xef08:
            c2 = 7;
            break;
        case 0xef0b:
            c2 = 8;
            break;
        case 0xef0a:
            c2 = 4;
            break;
        case 0xf360:
            c2 = 0xff;
            break;
        case 0xef09:
        default:
            c2 = 0;
            break;
        }

        if (c2 == 0xff) {
            break;
        }
        if (ret > 0x17) {
            out->length = 0x18;
            return 0;
        }
        if (ret == 8) {
            ret++;
        }
        if (ret & 1) {
            arr40[ret >> 1] |= c2;
            if (x == 0xef0b) {
                arr4c[ret >> 1] |= 8;
            } else if (x == 0xef0a) {
                arr4c[ret >> 1] |= 4;
            } else if (x != 0xef00) {
                arr4c[ret >> 1] |= 7;
            }
        } else {
            arr40[ret >> 1] |= c2 << 4;
            if (x == 0xef0b) {
                arr4c[ret >> 1] |= 0x80;
            } else if (x == 0xef0a) {
                arr4c[ret >> 1] |= 0x40;
            } else if (x != 0xef00) {
                arr4c[ret >> 1] |= 0x70;
            }
        }
        ret++;
    }

    len8 = ret;
    for (i = 0; i < 4; i++) {
        buf34[i] = arr4c[i];
        buf30[i] = arr40[i];
    }
    if (ret > 1 && ret < 8) {
        i = ret >> 1;
        if (ret & 1) {
            buf34[i] |= 0xf;
            buf30[i] |= 0xf;
        } else {
            buf34[i] |= 0xf0;
            buf30[i] |= 0xf0;
        }
    }

    if (out->nSeg == 0) {
        Zi8Memcpy(out->arr1, arr4c, 0xc);
        Zi8Memcpy(out->arrD, arr40, 0xc);
        Zi8Memcpy(out->arr19, buf34, 4);
        Zi8Memcpy(out->arr1D, buf30, 4);
        out->length = len8;
    }
    Zi8Memcpy(out->segs1 + out->nSeg * 0xc, arr4c, 0xc);
    Zi8Memcpy(out->segsD + out->nSeg * 0xc, arr40, 0xc);
    out->nSeg++;

    if (c2 == 0xff && cnt < n && out->nSeg < 0x10) {
        Zi8Memset(arr4c, 0, 0xc);
        Zi8Memset(arr40, 0, 0xc);
        arr4c[0] = out->arr1[0] & 0xf0;
        arr40[0] = out->arrD[0] & 0xf0;
        ret = 1;
        continue;
    }
    return 1;
    }

L_phonetic:
    out->length = ret;
    if (n == 0) {
        return 1;
    }

    if (prm->getMode == 1 || prm->getMode == 0xc) {
        t = (ziU8*)Zi8GetTableAddress(1, 3, ZI_WORK);
        tN = Zi8GetTableCount(1, 3, ZI_WORK);
    } else {
        t = (ziU8*)Zi8GetTableAddress(1, 4, ZI_WORK);
        tN = Zi8GetTableCount(1, 4, ZI_WORK);
    }

    if (prm->getMode == 1 || prm->getMode == 0xc) {
        out->nCand = Zi8GetPyPhonetic(prm->elements, n, out->phon, out->phon2,
                                      &prm->count, &out->first, &out->first2, ZI_WORK);
        goto L_tailchk;
    }

    v1a = 0;
    v18 = 0;
    v16 = 0;
    v14 = 0;
    v12 = 0;
    v10 = 0;
    ptr = prm->elements;
    out->nCand = 0;
    prm->count = prm->elementCount;
    j2 = 1;

    for (i = 0; i < n; i++, j2++) {
        c2 = Zi8GetBpmfPhonetic(ptr, (ziU8)j2, &v1a, &v18, &v16, &v14, ZI_WORK);
        if (c2 != 0) {
            v12 = v16;
            v10 = v14;
            goto L_store;
        }
        if (i == 0) {
            goto L_reset;
        }
        if (j2 > 1 && ptr[j2 - 2] == 0xf360 && ptr[j2 - 1] == 0xf360) {
            goto L_reset;
        }
        out->nCand++;
        if (out->nCand == 0x10) {
            goto L_reset;
        }
        goto L_tail2;

    L_reset:
        v1a = 0xffff;
        v18 = 0xffff;
        v16 = 0xffff;
        v14 = 0xffff;
        out->nCand = 0;
        break;

    L_tail2:
        if (ptr[j2 - 1] == 0xf360) {
            out->nCand--;
            v1a = v16 = v12;
            v18 = v14 = v10;
            goto L_store;
        }
        if (out->nCand == 1) {
            prm->count = j2 - 1;
        }
        ptr = ptr + j2 - 1;
        j2 = 0;
        i--;
        continue;

    L_store:
        out->phon[out->nCand] = v1a;
        out->phon2[out->nCand] = v18;
        if (out->nCand == 0) {
            out->first = v16;
            out->first2 = v14;
        }
    }

    if (n != 0) {
        out->phon[out->nCand] = v1a;
        out->phon2[out->nCand] = v18;
        if (out->nCand == 0) {
            out->first = v16;
            out->first2 = v14;
        }
        out->nCand++;
    }

L_tailchk:
    if ((prm->context & minLen) != 0) {
        if (out->nCand > 1 || prm->count != n) {
            out->phon[0] = 0xffff;
            out->phon2[0] = 0xffff;
            out->nCand = 0;
        }
    }

    if (!(prm->getOptions & 0x20)) {
        if (!(out->phon[0] == 0xffff && out->phon2[0] == 0xffff)) {
            if (out->nCand > 1) {
                v22 = out->phon[out->nCand - 1] & 0xe000;
                v20 = out->phon2[out->nCand - 1] & 0xe000;
            } else {
                v22 = out->phon[0] & 0xe000;
                v20 = out->phon2[0] & 0xe000;
            }
            for (j2 = 0; j2 < tN; j2++) {
                v1e = t[j2 * 2] | (t[j2 * 2 + 1] << 8);
                if (v20 == (v1e & v22)) {
                    break;
                }
            }
            if (j2 == tN) {
                out->phon[0] = 0xffff;
                out->phon2[0] = 0xffff;
            }
        }
    }
    return 1;
}
