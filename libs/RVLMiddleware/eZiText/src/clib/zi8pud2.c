#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>

extern ziU8 Zi8ConvertUC2Key(ziU8 ch, ziU8 lang ZI_NEED_WORK);
extern ziU16 Zi8ConvertUC2WC(ziU8 ch, ziU8 lang ZI_NEED_WORK);
extern ziU16 Zi8ConvertWC2Key(ziWChar ch, ziU8 lang ZI_NEED_WORK);
extern ziU8 Zi8ChangeCharCase(ziU8 dir, ziWChar* buf, ziU8 lang ZI_NEED_WORK);

static ziU8 Zi8_8147FD7C(ziU32 a0, ziU8 a1, ziU8 a2, ziU32 a3, ziU16 a4,
                         ziU8 a5, ziU8 a6 ZI_NEED_WORK);

ziS32 ZiIsPhoneticChar(ziWChar ch) {
    if ((ziU16)ch >= 0xF305 && (ziU16)ch <= 0xF329) {
        goto ret1;
    }
    if ((ziU16)ch >= 0xF361 && (ziU16)ch <= 0xF37A) {
        goto ret1;
    }
    return 0;
ret1:
    return 1;
}

ziS32 ZiGetZHWordSize(ziWChar* s, ziS32 len) {
    ziWChar* t;
    ziS32 i = 0;

    i = 0;
    while (i < len) {
        t = s;
        if (ZiIsPhoneticChar(*t)) {
            return i;
        }
        i += 2;
        s++;
    }
    return i;
}

void Zi8CopyZHSpelling(ziWChar* src, ziWChar* dst, ziU16 cnt, ziS32 start,
                       ziS32 end) {
    ziS32 i;
    ziWChar* p;

    if (dst == ZI8_NULL) {
        return;
    }
    if (cnt == 0) {
        return;
    }
    *dst = 0;
    if (start <= end) {
        return;
    }
    i = 0;
    while (i < start - end && i < (ziU16)cnt * 2) {
        p = (ziWChar*)((ziU8*)src + end + i);
        *dst = *p;
        dst++;
        i += 2;
    }
    *dst = 0;
}

ziU8 ZADP_Zi8SetPDremoveOpt(ziU8 opt, struct __zi8_work_data_s* work) {
    ziU8 old = work->pdRemoveOpt;
    work->pdRemoveOpt = opt;
    Zi8LogError(0x64, work);
    return old;
}

ziU8 Zi8MatchPUDdata_ZHS(ziWChar* w, ziU8 len, ziU8 lang, ziWChar* out,
                         ziU16 lim, ziWChar* arg5, ziU16 arg6, ziU8 a7,
                         ziU8 a8 ZI_NEED_WORK) {
    ziU8* p;
    ziS32 i;
    ziS32 b0;
    ziS32 r27;
    ziS32 r30;
    struct __zi8_work_data_s* work = ZI_WORK;
    ziU32 flagZ;
    ziU8* wb;
    ziU32 sz;
    ziU32 t;
    ziU8* outp;
    ziWChar wc;

    flagZ = 0;
    if (work->pudCount > 0x10 || work->pudCount == 0 ||
        work->pudTable[work->pudCount - 1] == 0) {
        Zi8LogError(0x4B0, work);
        return 0;
    }
    if (lang == 1) {
        len <<= 1;
    }
    if (a8 == 0) {
        t = work->pudTable[work->pudCount - 1];
        p = (ziU8*)t + 8;
        i = 0;
        while (i < ((ziU8*)t)[3]) {
            if (p[1] == lang) {
                goto found;
            }
            p += 8;
            i++;
        }
        if (i >= ((ziU8*)t)[3]) {
            Zi8LogError(0x4F6, work);
            return 0;
        }
    found:
        work->unk_0x314 = ((ziU16)p[4] << 8) + (ziU16)p[5];
        work->unk_0x310 = t + ((ziU16)p[2] << 8) + (ziU16)p[3];
        work->unk_0x318 = 0;
    }
loop_head:
    p = (ziU8*)work->unk_0x310;
    if (p == ZI8_NULL) {
        Zi8LogError(0x4B3, work);
        return 0;
    }
    goto check;
body:
    b0 = (ziU8)*p;
    p++;
    sz = b0;
    if (lang == 1) {
        if ((ziU8)work->unk_0x17 > *p) {
            goto miss;
        }
        b0--;
        sz--;
        p++;
        b0 = ZiGetZHWordSize((ziWChar*)p, sz);
    } else {
        if (work->unk_0x31E != 0 && a7 != 0 && (ziU8)len < b0 &&
            p[len] == 0x20) {
            goto cmp454;
        }
    }
    if ((ziU8)len > b0) {
        goto miss;
    }
    if (a7 != 0 && b0 != (ziU8)len) {
        goto miss;
    }
    if (a7 != 0 || b0 != (ziU8)len) {
        goto cmp410;
    }
miss:
    work->unk_0x318++;
    p += sz;
    goto tail;
cmp410:
    if (lang == 1) {
        wb = (ziU8*)w;
        i = 0;
        while (i < len) {
            if (p[i] != wb[i]) {
                goto miss;
            }
            i++;
        }
        goto matched;
    }
cmp454:
    for (i = 0; i < len; i++) {
        if ((ziU16)w[i] >= 0xEFF1 && (ziU16)w[i] <= 0xF37F) {
            if (Zi8ConvertUC2Key(p[i], lang, work) != w[i]) {
                goto miss;
            }
        } else {
            wc = Zi8ConvertUC2WC(p[i], lang, work);
            if (wc == w[i]) {
                goto next454;
            }
            if (work->unk_0x1F == 0) {
                goto miss;
            }
            if (Zi8ChangeCharCase(0, &wc, lang, work) == 0) {
                goto miss;
            }
            if (wc != w[i]) {
                goto miss;
            }
        }
    next454:;
    }
matched:
    if (flagZ != 0) {
        work->unk_0x310 = ZI8_NULL;
        work->unk_0x318 = 0;
        work->unk_0x314 = 0;
        if ((ziU16)w[0] >= 0xEFF1) {
            out[0] = w[0];
        } else {
            out[0] = Zi8ConvertWC2Key(w[0], lang, work);
        }
        return 1;
    }
    if (lang == 1) {
        outp = (ziU8*)out;
        r27 = 0;
        r30 = 0;
        while (r30 < b0 && r27 < (ziU16)lim) {
            outp[r30] = p[r30];
            r30++;
            outp[r30] = p[r30];
            r30++;
            r27++;
        }
        Zi8CopyZHSpelling((ziWChar*)p, arg5, arg6, sz, b0);
    } else {
        r27 = 0;
        while (r27 < b0 && r27 < (ziU16)lim) {
            out[r27] = Zi8ConvertUC2WC(p[r27], lang, work);
            if (work->unk_0x31E != 0 && r27 >= (ziU8)len &&
                out[r27] == 0x20) {
                if (a7 != 0) {
                    goto done;
                }
                if (r27 < (ziU8)len) {
                    goto miss;
                }
                goto done;
            }
            r27++;
        }
    }
done:
    work->unk_0x318++;
    work->unk_0x310 = (ziU32)(p + sz);
    Zi8LogError(0x64, work);
    return (ziU8)r27;
check:
tail:
    if (work->unk_0x318 < work->unk_0x314) {
        goto body;
    }
    if (len == 1 && a7 != 0 && a8 == 0) {
        a7 = 0;
        flagZ = 1;
        work->unk_0x318 = 0;
        goto loop_head;
    }
    work->unk_0x310 = ZI8_NULL;
    work->unk_0x318 = 0;
    work->unk_0x314 = 0;
    return 0;
}

ziU8 Zi8MatchPUDdata(ziU32 a0, ziU8 a1, ziU8 a2, ziU32 a3, ziU16 a4, ziU8 a5,
                     ziU8 flag, struct __zi8_work_data_s* work) {
    ziU8 res;

    if (flag == 0) {
        work->pudCount = 1;
    }
retry:
    res = Zi8_8147FD7C(a0, a1, a2, a3, a4, a5, flag, work);
    if (res == 0) {
        if ((ziU8)++work->pudCount <= 0x10) {
            flag = 0;
            goto retry;
        }
        work->pudCount = 1;
    }
    return res;
}

ziU8 Zi8_8147FD7C(ziU32 a0, ziU8 a1, ziU8 a2, ziU32 a3, ziU16 a4, ziU8 a5,
                  ziU8 a6 ZI_NEED_WORK) {
    return Zi8MatchPUDdata_ZHS((ziWChar*)a0, a1, a2, (ziWChar*)a3, a4,
                               (ziWChar*)0, 0, a5, a6, __zi8_work_data);
}
