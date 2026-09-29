#include <zi8clib/zi8space.h>
#include <zi8clib/zierror.h>
#include <zi8clib/zitypes.h>

extern ziU8 Zi8GetPyPhonetic(ziWChar* src, ziU8 i, ziWChar* a, ziWChar* b, ziU8* c,
                             ziU16* d, ziU16* e ZI_NEED_WORK);
extern ziU8 Zi8GetBpmfPhonetic(ziWChar* src, ziU8 i, ziWChar* a, ziWChar* b,
                               ziU16* d, ziU16* e ZI_NEED_WORK);

ziU8 Zi8ZHaddSpace(ziWChar* src, ziU8 count, ziWChar* dst,
                   ziU16 maxLen ZI_NEED_WORK) {
    ziWChar candBuf[0x10];
    ziWChar pyBuf[0x10];
    ziU16 m;
    ziU16 vE;
    ziU16 vC;
    ziU8 n;
    ziU8 flag;
    ziU8 v9;
    ziU8 isPy;
    int i;
    int k;
    ziWChar* psrc;
    ziWChar* pdst;

    psrc = src;
    n = count;
    pdst = dst;
    m = maxLen;

    if (n == 0) {
        Zi8LogError(0x137, ZI_WORK);
        return 0;
    }

    if ((psrc[0] >= 0xF361 && psrc[0] <= 0xF37A) ||
        (psrc[0] >= 0xF341 && psrc[0] <= 0xF35A)) {
        isPy = 1;
    } else if (psrc[0] >= 0xF305 && psrc[0] <= 0xF329) {
        isPy = 0;
    } else {
        goto fail;
    }

    i = 2;
    while (i <= n) {
        if (isPy) {
            flag = Zi8GetPyPhonetic(psrc, i, candBuf, pyBuf, &v9, &vE, &vC, ZI_WORK);
            if (i == v9) {
                i++;
                continue;
            }
        } else {
            if ((psrc[i - 1] == 0xF360 && psrc[i - 2] != 0xF360) ||
                Zi8GetBpmfPhonetic(psrc, i, candBuf, pyBuf, &vE, &vC, ZI_WORK) !=
                    0) {
                i++;
                continue;
            }
        }

        if (i-- >= m - 1) {
            goto fail;
        }
        m -= i + 1;
        for (k = 0; k < i; k++) {
            pdst[k] = psrc[k];
        }
        if (pdst[k - 1] != 0xF360 &&
            (pdst[k - 1] < 0xF331 || pdst[k - 1] > 0xF335)) {
            pdst[k++] = ZI_WORK->unk_0x1A;
        }
        psrc += i;
        n -= i;
        pdst += k;
        i = 2;
    }

    if (i-- > m) {
        goto fail;
    }
    for (k = 0; k < i; k++) {
        pdst[k] = psrc[k];
    }
    pdst[k] = 0;
    Zi8LogError(0x64, ZI_WORK);
    return 1;

fail:
    if ((ziU8)count >= (ziU16)maxLen) {
        count = (ziU8)(maxLen - 1);
    }
    for (i = 0; i < count; i++) {
        dst[i] = src[i];
    }
    dst[i] = 0;
    Zi8LogError(0x64, ZI_WORK);
    return 1;
}
