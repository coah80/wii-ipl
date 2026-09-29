#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>

extern ziU16 Zi8GetTableCount(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);
extern ziU32 Zi8GetTableAddress(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);

static ziU8 Zi8_814813FC(ziU16 key, ziU8* pOut, ziU16* pIdx ZI_NEED_WORK);
static ziU8 Zi8_81481E6C(ziU16* out, ziWChar* keys, ziU8 sel, ziU16 n
                         ZI_NEED_WORK);

static ziU8 Zi8_814813FC(ziU16 key, ziU8* pOut, ziU16* pIdx ZI_NEED_WORK) {
    ziU16 i;
    ziU8* tbl;

    tbl = (ziU8*)Zi8GetTableAddress(0x12, 5, ZI_WORK);
    for (i = 0; tbl[i] != 0; i++) {
        if (key == tbl[i]) {
            *pIdx = i;
            *pOut = tbl[i];
            Zi8LogError(0x64, ZI_WORK);
            return 1;
        }
    }
    Zi8LogError(0x2A8, ZI_WORK);
    return 0;
}

ziU8 Zi8GetKoreanCandidates(ziGetParam* prm, ziU8* p2 ZI_NEED_WORK) {
    ziWChar buf[0x64];
    ziU8* t4;
    ziU8* t1;
    ziU8* t2;
    ziU8* t31;
    ziU16 v1a;
    ziU16 v18;
    ziU16 v16;
    ziU16 v14;
    ziU16 v12;
    ziU16 ve;
    ziU16 v10;
    ziU16 j;
    ziU16 i;
    ziWChar wc;
    ziU8 i8;
    ziU8 j8;
    ziU8 v9;
    ziU8 v8;
    ziU8 n;

    v12 = 0;
    n = 0;
    v8 = 0xFF;
    ve = prm->firstCandidate;
    prm->unk_0x20 = prm->count = prm->letters = 0;
    if (p2 != ZI8_NULL && p2[0] != 0) {
        Zi8LogError(0x7D0, ZI_WORK);
        return 0;
    }
    if (prm->elementCount == 0 || prm->elementCount > 0x64) {
        Zi8LogError(0x64, ZI_WORK);
        return 0;
    }
    t4 = (ziU8*)Zi8GetTableAddress(0x12, 4, ZI_WORK);
    t1 = (ziU8*)Zi8GetTableAddress(0x12, 1, ZI_WORK);
    t2 = (ziU8*)Zi8GetTableAddress(0x12, 2, ZI_WORK);
    t31 = (ziU8*)Zi8GetTableAddress(0x12, 0x31, ZI_WORK);
    v1a = Zi8GetTableCount(0x12, 0, ZI_WORK);
    v18 = Zi8GetTableCount(0x12, 3, ZI_WORK);
    v16 = Zi8GetTableCount(0x12, 6, ZI_WORK);
    v14 = Zi8GetTableCount(0x12, 0x31, ZI_WORK);
    for (i8 = 0; i8 < prm->elementCount; i8++) {
        wc = prm->elements[i8];
        if (wc >= 0x61 && wc <= 0x7A) {
            buf[i8] = t1[(wc - 0x61) * 2];
        } else if (wc >= 0x41 && wc <= 0x5A) {
            buf[i8] = t1[(wc - 0x41) * 2 + 1];
        } else {
            j8 = 0;
            while (*(t2 + j8 * 3) != 0) {
                if (wc == *(t2 + j8 * 3)) break;
                j8++;
            }
            if (*(t2 + j8 * 3) == 0) {
                Zi8LogError(0x161, ZI_WORK);
                return 0;
            }
            buf[i8] = (*(t2 + j8 * 3 + 1) << 8) | *(t2 + j8 * 3 + 2);
        }
    }
    n = 0;
    i = 0;
    goto Lchk;
Lloop:
    if (Zi8_814813FC(buf[i], &v8, &v10, ZI_WORK) != 0) {
        v9 = Zi8_81481E6C(&v12, buf + i + 1, v8, (ziU16)(i8 - i - 1), ZI_WORK);
        if (ZI_WORK->unk_0x1B30 == 1) {
            switch (v8) {
            case 1:
                t4 = (ziU8*)Zi8GetTableAddress(0x12, 0x1E, ZI_WORK);
                break;
            case 2:
                t4 = (ziU8*)Zi8GetTableAddress(0x12, 0x1F, ZI_WORK);
                break;
            case 4:
                t4 = (ziU8*)Zi8GetTableAddress(0x12, 0x20, ZI_WORK);
                break;
            case 7:
                t4 = (ziU8*)Zi8GetTableAddress(0x12, 0x21, ZI_WORK);
                break;
            case 8:
                t4 = (ziU8*)Zi8GetTableAddress(0x12, 0x22, ZI_WORK);
                break;
            case 9:
                t4 = (ziU8*)Zi8GetTableAddress(0x12, 0x23, ZI_WORK);
                break;
            case 17:
                t4 = (ziU8*)Zi8GetTableAddress(0x12, 0x24, ZI_WORK);
                break;
            case 19:
                t4 = (ziU8*)Zi8GetTableAddress(0x12, 0x25, ZI_WORK);
                break;
            case 20:
                t4 = (ziU8*)Zi8GetTableAddress(0x12, 0x26, ZI_WORK);
                break;
            case 21:
                t4 = (ziU8*)Zi8GetTableAddress(0x12, 0x27, ZI_WORK);
                break;
            case 22:
                t4 = (ziU8*)Zi8GetTableAddress(0x12, 0x28, ZI_WORK);
                break;
            case 23:
                t4 = (ziU8*)Zi8GetTableAddress(0x12, 0x29, ZI_WORK);
                break;
            case 24:
                t4 = (ziU8*)Zi8GetTableAddress(0x12, 0x2A, ZI_WORK);
                break;
            case 25:
                t4 = (ziU8*)Zi8GetTableAddress(0x12, 0x2B, ZI_WORK);
                break;
            case 26:
                t4 = (ziU8*)Zi8GetTableAddress(0x12, 0x2C, ZI_WORK);
                break;
            case 27:
                t4 = (ziU8*)Zi8GetTableAddress(0x12, 0x2D, ZI_WORK);
                break;
            case 28:
                t4 = (ziU8*)Zi8GetTableAddress(0x12, 0x2E, ZI_WORK);
                break;
            case 29:
                t4 = (ziU8*)Zi8GetTableAddress(0x12, 0x2F, ZI_WORK);
                break;
            case 30:
                t4 = (ziU8*)Zi8GetTableAddress(0x12, 0x30, ZI_WORK);
                break;
            }
        }
    } else {
        v9 = 0;
    }
    if (v9 != 0) {
        if (v16 == 0) {
            v12 = (ziU16)(v12 + v10 * v18);
        }
        if (ve != 0) {
            ve--;
        } else {
            prm->candidates[n] = (ziWChar)(((ziU16)t4[v12 * 2] << 8) |
                                           t4[v12 * 2 + 1]);
            if (v16 != 0 && ZI_WORK->unk_0x1B30 == 0) {
                prm->candidates[n] =
                    (ziWChar)(prm->candidates[n] + v10 * v18);
            }
            n++;
        }
        if (i == 0) {
            prm->count = v9 + 1;
        }
        i += v9;
    } else {
        if (ve != 0) {
            for (j = 0; j < v14; j++) {
                if (t31[j * 3] == buf[i] && t31[j * 3 + 1] == buf[i + 1]) {
                    break;
                }
            }
            if (j == v14) {
                ve--;
            }
            if (i == 0) {
                prm->count = 1;
            }
        } else {
            for (j = 0; j < v14; j++) {
                if (t31[j * 3] == buf[i] && t31[j * 3 + 1] == buf[i + 1]) {
                    if (i == 0) {
                        prm->count = 1;
                    }
                    prm->candidates[n] =
                        (ziWChar)(v1a + t31[j * 3 + 2]);
                    n++;
                    i++;
                    break;
                }
            }
            if (j == v14) {
                prm->candidates[n] = buf[i];
                if (buf[i] < 0xFF) {
                    if (i == 0) {
                        prm->count = 1;
                    }
                    prm->candidates[n] =
                        (ziWChar)(prm->candidates[n] + v1a);
                    n++;
                }
            }
        }
    }
    if (n < prm->maxCandidates) {
        i++;
    }
Lchk:
    if (i < i8 && n < prm->maxCandidates) {
        goto Lloop;
    }
    prm->letters = n;
    Zi8LogError(0x64, ZI_WORK);
    return n;
}

static ziU8 Zi8_81481E6C(ziU16* out, ziWChar* keys, ziU8 sel, ziU16 n
                         ZI_NEED_WORK) {
    ziU8 v9;
    ziU16 j1;
    ziU16 j2;
    ziU16 j3;
    ziU16 j4;
    ziU16 v14;
    ziU16 v16;
    ziWChar cur;
    ziU16 cnt;
    ziU8* tbl;

    cur = keys[0];
    v9 = 0xFF;
    if (ZI_WORK->unk_0x1B30 == 0) {
        tbl = (ziU8*)Zi8GetTableAddress(0x12, 3, ZI_WORK);
        cnt = Zi8GetTableCount(0x12, 3, ZI_WORK);
    } else {
        switch (sel) {
        case 1:
            tbl = (ziU8*)Zi8GetTableAddress(0x12, 0xB, ZI_WORK);
            cnt = Zi8GetTableCount(0x12, 0xB, ZI_WORK);
            break;
        case 2:
            tbl = (ziU8*)Zi8GetTableAddress(0x12, 0xC, ZI_WORK);
            cnt = Zi8GetTableCount(0x12, 0xC, ZI_WORK);
            break;
        case 4:
            tbl = (ziU8*)Zi8GetTableAddress(0x12, 0xD, ZI_WORK);
            cnt = Zi8GetTableCount(0x12, 0xD, ZI_WORK);
            break;
        case 7:
            tbl = (ziU8*)Zi8GetTableAddress(0x12, 0xE, ZI_WORK);
            cnt = Zi8GetTableCount(0x12, 0xE, ZI_WORK);
            break;
        case 8:
            tbl = (ziU8*)Zi8GetTableAddress(0x12, 0xF, ZI_WORK);
            cnt = Zi8GetTableCount(0x12, 0xF, ZI_WORK);
            break;
        case 9:
            tbl = (ziU8*)Zi8GetTableAddress(0x12, 0x10, ZI_WORK);
            cnt = Zi8GetTableCount(0x12, 0x10, ZI_WORK);
            break;
        case 17:
            tbl = (ziU8*)Zi8GetTableAddress(0x12, 0x11, ZI_WORK);
            cnt = Zi8GetTableCount(0x12, 0x11, ZI_WORK);
            break;
        case 19:
            tbl = (ziU8*)Zi8GetTableAddress(0x12, 0x12, ZI_WORK);
            cnt = Zi8GetTableCount(0x12, 0x12, ZI_WORK);
            break;
        case 20:
            tbl = (ziU8*)Zi8GetTableAddress(0x12, 0x13, ZI_WORK);
            cnt = Zi8GetTableCount(0x12, 0x13, ZI_WORK);
            break;
        case 21:
            tbl = (ziU8*)Zi8GetTableAddress(0x12, 0x14, ZI_WORK);
            cnt = Zi8GetTableCount(0x12, 0x14, ZI_WORK);
            break;
        case 22:
            tbl = (ziU8*)Zi8GetTableAddress(0x12, 0x15, ZI_WORK);
            cnt = Zi8GetTableCount(0x12, 0x15, ZI_WORK);
            break;
        case 23:
            tbl = (ziU8*)Zi8GetTableAddress(0x12, 0x16, ZI_WORK);
            cnt = Zi8GetTableCount(0x12, 0x16, ZI_WORK);
            break;
        case 24:
            tbl = (ziU8*)Zi8GetTableAddress(0x12, 0x17, ZI_WORK);
            cnt = Zi8GetTableCount(0x12, 0x17, ZI_WORK);
            break;
        case 25:
            tbl = (ziU8*)Zi8GetTableAddress(0x12, 0x18, ZI_WORK);
            cnt = Zi8GetTableCount(0x12, 0x18, ZI_WORK);
            break;
        case 26:
            tbl = (ziU8*)Zi8GetTableAddress(0x12, 0x19, ZI_WORK);
            cnt = Zi8GetTableCount(0x12, 0x19, ZI_WORK);
            break;
        case 27:
            tbl = (ziU8*)Zi8GetTableAddress(0x12, 0x1A, ZI_WORK);
            cnt = Zi8GetTableCount(0x12, 0x1A, ZI_WORK);
            break;
        case 28:
            tbl = (ziU8*)Zi8GetTableAddress(0x12, 0x1B, ZI_WORK);
            cnt = Zi8GetTableCount(0x12, 0x1B, ZI_WORK);
            break;
        case 29:
            tbl = (ziU8*)Zi8GetTableAddress(0x12, 0x1C, ZI_WORK);
            cnt = Zi8GetTableCount(0x12, 0x1C, ZI_WORK);
            break;
        case 30:
            tbl = (ziU8*)Zi8GetTableAddress(0x12, 0x1D, ZI_WORK);
            cnt = Zi8GetTableCount(0x12, 0x1D, ZI_WORK);
            break;
        }
    }
    *out = 0;
    if (n >= 1 && cur < 0xFF) goto L1;
    return 0;
L1:
    j4 = *out;
    for (; j4 < cnt; j4++) {
        if (tbl[j4 * 4] >= cur) break;
    }
    if (j4 < cnt && cur == tbl[j4 * 4]) goto L1a;
    return 0;
L1a:
    if (n >= 2 && (cur = keys[1]) < 0xFF) goto L2;
    *out = j4;
    return 1;
L2:
    j3 = j4;
    for (; j3 < cnt; j3++) {
        if (*(tbl + j3 * 4 + 1) >= cur) break;
    }
    if (j3 < cnt && cur == *(tbl + j3 * 4 + 1) && keys[0] == tbl[j3 * 4])
        goto L2a;
    *out = j4;
    return 1;
L2a:
    if (n >= 3 && (cur = keys[2]) < 0xFF) goto L3;
    *out = j3;
    return 2;
L3:
    j2 = j3;
    for (; j2 < cnt; j2++) {
        if (*(tbl + j2 * 4 + 2) >= cur) break;
    }
    if (j2 < cnt && cur == *(tbl + j2 * 4 + 2) &&
        keys[1] == *(tbl + j2 * 4 + 1) && keys[0] == tbl[j2 * 4])
        goto L3a;
    if (Zi8_814813FC(keys[1], &v9, &v16, ZI_WORK) != 0 &&
        Zi8_81481E6C(&v14, keys + 2, v9, 1, ZI_WORK) != 0) {
        *out = j4;
        return 1;
    }
    *out = j3;
    return 2;
L3a:
    if (n >= 4 && (cur = keys[3]) < 0xFF) goto L4;
    *out = j2;
    return 3;
L4:
    j1 = j2;
    for (; j1 < cnt; j1++) {
        if (*(tbl + j1 * 4 + 3) >= cur) break;
    }
    if (j1 < cnt && cur == *(tbl + j1 * 4 + 3) &&
        keys[2] == *(tbl + j1 * 4 + 2) && keys[1] == *(tbl + j1 * 4 + 1) &&
        keys[0] == tbl[j1 * 4])
        goto L4a;
    if (Zi8_814813FC(keys[2], &v9, &v16, ZI_WORK) != 0 &&
        Zi8_81481E6C(&v14, keys + 3, v9, 1, ZI_WORK) != 0) {
        *out = j3;
        return 2;
    }
    *out = j2;
    return 3;
L4a:
    if (n >= 5 && (cur = keys[4]) < 0xFF) goto L5;
    *out = j1;
    return 4;
L5:
    if (Zi8_814813FC(keys[3], &v9, &v16, ZI_WORK) != 0 &&
        Zi8_81481E6C(&v14, keys + 4, v9, 1, ZI_WORK) != 0) {
        *out = j2;
        return 3;
    }
    *out = j1;
    return 4;
}
