#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>

extern ziU16 Zi8GetTableCount(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);
extern ziU32 Zi8GetTableSize(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);
extern ziU32 Zi8GetTableAddress(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);
extern ziU16 Zi8ConvertWC2Key(ziWChar ch, ziU8 language ZI_NEED_WORK);
extern ziU8* ZiDAWGGetGraph(ziU8* arg);
extern ziU32 ZiDAWGGetGraphInfo(ziPtr work, ziU8* hdr, ziWChar* key);
extern ziU8* ZiDAWGGetChild(ziU8* node);
extern ziU8* ZiDAWGGetSibling(ziU8* node);
extern ziU8 ZiDAWGgetEOWattribute(ziU8* node);
extern ziU32 ZiDAWGgetCHARattribute(ziU8* graph, ziU8* node ZI_NEED_WORK);

static ziU8 Zi8MatchROMdata0(ziWChar* keys, ziU8 count, ziU8 lang, ziWChar* out,
                             ziU16 maxLen, ziU8 flag8, ziU8 flag9, ziU8 g,
                             ziU8 t2, ziU8 flagX, ziU8* cnt, zi8DawgCtx* ctx,
                             ziU8* out2 ZI_NEED_WORK);
static ziU8 Zi8MatchROMdata1(ziWChar* keys, ziU8 count, ziU8 lang, ziWChar* out,
                             ziU16 maxLen, ziU8 flag8, ziU8 flag9, ziU8 grpIdx,
                             ziU8* grp, ziU8 x ZI_NEED_WORK);
static ziU8 Zi8MatchROMdata2(ziWChar* keys, ziU8 count, ziU8 lang, ziWChar* out,
                             ziU16 maxLen, ziU8 flag8, ziU8 flag9, ziU8 g,
                             ziU8* grp, ziU8 x ZI_NEED_WORK);

ziU8* NextDawgGroup(ziU8* ptr, ziU8 lang ZI_NEED_WORK) {
    if (Zi8GetTableSize(lang, 0x1C, ZI_WORK) == 0) goto Lerr;
    if (ptr == ZI8_NULL) {
        ptr = (ziU8*)Zi8GetTableAddress(lang, 0x1C, ZI_WORK);
        if (ptr == ZI8_NULL) {
            Zi8LogError(0x962, ZI_WORK);
            return ZI8_NULL;
        }
        if (ZI_WORK->unk_0x141D == 0) {
            return ptr;
        }
    }
    while (ptr[0] != 0xFF || ptr[1] != 0xFF) {
        ptr++;
    }
    ptr += 2;
    if (ptr[0] == 0xFF) {
        Zi8LogError(0x963, ZI_WORK);
        return ZI8_NULL;
    }
    return ptr;
Lerr:
    Zi8LogError(0x961, ZI_WORK);
    return ZI8_NULL;
}

static ziU8 Zi8MatchROMdata0(ziWChar* keys, ziU8 count, ziU8 lang, ziWChar* out,
                             ziU16 maxLen, ziU8 flag8, ziU8 flag9, ziU8 g,
                             ziU8 t2, ziU8 flagX, ziU8* cnt, zi8DawgCtx* ctx,
                             ziU8* out2 ZI_NEED_WORK) {
    zi8DawgRec* recs;
    zi8DawgRec* rec;
    ziU8* tbl;
    ziU8* tbl2;
    ziWChar buf[2];
    ziU32 tmp;
    ziU16 size;
    ziU16 flag16;
    ziU8 ret;
    ziU16 i;
    ziU8* hdr;
    ziWChar c;
    ziU8 r;

    ret = 0;
    recs = ctx->recs;
    if (lang != ctx->lang || g != ctx->key) {
        recs[0].key = 0;
    }
    if (count == 1 && flag8 != 0 && g == 0xE) goto ret;
    if (flag9 != 0) {
        if (recs[ctx->cnt - 1].node == (ziU8*)ctx->unk_0x338) goto ret;
        for (i = 0; i < count; i++) {
            if (recs[i].key != keys[i] &&
                (ziWChar)recs[i].attr != keys[i]) {
                goto ret;
            }
        }
        if (flag8 == 1) {
            flagX = 0;
        }
        goto L478;
    }
    {
        if (ZI_WORK->unk_0x141E != 0 && g == 0xC &&
            Zi8GetTableSize(lang, ZI_WORK->unk_0x141E, ZI_WORK) != 0) {
            tbl = (ziU8*)Zi8GetTableAddress(lang, ZI_WORK->unk_0x141E, ZI_WORK);
            t2 = ZI_WORK->unk_0x141E + 1;
        } else {
            if (Zi8GetTableSize(lang, g, ZI_WORK) == 0) {
                Zi8LogError(0x961, ZI_WORK);
                goto ret;
            }
            tbl = (ziU8*)Zi8GetTableAddress(lang, g, ZI_WORK);
        }
        ctx->table = tbl;
        ctx->cap = (ziU16)((((ziU16)ctx->table[2] << 8) + ctx->table[3]) / 3);
        ctx->p08 = ctx->table + 4;
        ctx->p0C = ctx->table + 4 + ctx->cap * 2;
        ctx->lang = lang;
        ctx->key = g;
        for (i = 0; i < count && recs[i].key == keys[i]; i++);
        if (i >= 2) {
            recs[0].node = recs[i - 1].back;
            goto Lcnt;
        }
        size = (ziU16)Zi8GetTableSize(lang, t2, ZI_WORK);
        if (size != 0 && ZI_WORK->userKeys[lang] == 0) {
            for (i = 0; i < (count < 2 ? count : 2); i++) {
                buf[i] = Zi8ConvertWC2Key(keys[i], lang, ZI_WORK);
                if (buf[i] == 0) {
                    buf[i] = keys[i];
                }
            }
            buf[i] = 0;
            tbl2 = (ziU8*)Zi8GetTableAddress(lang, t2, ZI_WORK);
            ctx->p14 = tbl2 + 2;
            hdr = ctx->cap * 2 + tbl2 + 2;
            recs[0].node = (ziU8*)ZiDAWGGetGraphInfo(ctx, hdr, buf);
        } else {
            recs[0].node = ZiDAWGGetGraph((ziU8*)ctx);
            ctx->unk_0x338 = 0;
            ctx->p14 = ZI8_NULL;
        }
        recs[0].key = 0;
        if (recs[0].node == (ziU8*)0) goto ret;
Lcnt:
        ctx->cnt = 1;
        out2[1] = count;
        out2[0] = 0;
        if (flag8 == 1) {
            out2[0] = 1;
            flagX = 0;
        } else if (flag8 == 0 && flagX == 0) {
            out2[1]++;
        }
    }
L478:
    flag16 = 1;
    rec = recs + (ctx->cnt - 1);
    goto Lcheck;
Lloop:
    if ((ziU16)maxLen < ctx->cnt) goto ret;
    rec->attr = ZiDAWGgetCHARattribute((ziU8*)ctx, rec->node, ZI_WORK);
    if (ctx->cnt <= count) {
        if (ctx->p14 == ZI8_NULL) {
            tmp = Zi8ConvertWC2Key((ziWChar)rec->attr, lang, ZI_WORK);
        } else {
            tmp = ((ziU16) * (ctx->p14 + (rec->attr >> 0x18) * 2) << 8) +
                  ctx->p14[(rec->attr >> 0x18) * 2 + 1];
        }
        c = (ziWChar)tmp;
        if (c != keys[ctx->cnt - 1] &&
            (ziWChar)rec->attr != keys[ctx->cnt - 1]) {
            goto L7c8;
        }
        if (rec->key != keys[ctx->cnt - 1]) {
            rec->key = keys[ctx->cnt - 1];
            rec->back = recs[0].node;
            recs[ctx->cnt].key = 0;
        }
        if (cnt != ZI8_NULL && *cnt < ctx->cnt) {
            if (ZiDAWGgetEOWattribute(rec->node) != 0) {
                *cnt = (ziU8)ctx->cnt;
                for (i = 0; i < ctx->cnt; i++) {
                    out[i] = (ziWChar)recs[i].attr;
                }
            }
        }
    }
    if (ctx->cnt >= count && ctx->cnt >= out2[1]) {
        if (out2[0] != 0 && ctx->cnt > out2[1]) goto L7c8;
        if (flagX == 0) {
            if (ZiDAWGgetEOWattribute(rec->node) == 0) goto L6fc;
        }
        for (i = 0; i < ctx->cnt; i++) {
            out[i] = (ziWChar)recs[i].attr;
        }
        ret = (ziU8)ctx->cnt;
        flag16 = 0;
        if (flagX != 0) goto L7c8;
    }
L6fc:
    if (out2[0] != 0 && ctx->cnt >= out2[1]) goto L7c8;
    recs[ctx->cnt].node = ZiDAWGGetChild(recs[ctx->cnt - 1].node);
    if (recs[ctx->cnt].node == (ziU8*)0) goto L7c8;
    ctx->cnt++;
    if (ZI_WORK->unk_0x141F < ctx->cnt) {
        ZI_WORK->unk_0x141F = (ziU8)ctx->cnt;
    }
    goto L7d4;
L7c8:
    while (ctx->cnt != 0) {
        recs[ctx->cnt - 1].node = ZiDAWGGetSibling(recs[ctx->cnt - 1].node);
        if (recs[ctx->cnt - 1].node != (ziU8*)0) goto L7d4;
        ctx->cnt--;
    }
L7d4:
    rec = recs + (ctx->cnt - 1);
Lcheck:
    if (flag16 != 0 && ctx->cnt != 0 &&
        rec->node != (ziU8*)ctx->unk_0x338) {
        goto Lloop;
    }
ret:
    return ret;
}

static ziU8 Zi8MatchROMdata1(ziWChar* keys, ziU8 count, ziU8 lang, ziWChar* out,
                             ziU16 maxLen, ziU8 flag8, ziU8 flag9, ziU8 grpIdx,
                             ziU8* grp, ziU8 x ZI_NEED_WORK) {
    ziU8 ret = 0;
    ziU8* p;

    if (flag9 == 0) {
        ZI_WORK->unk_0x1764 = grp;
        if (ZI_WORK->unk_0x1764 == ZI8_NULL) {
            if (Zi8GetTableSize(lang, 0xB, ZI_WORK) != 0) {
                p = (ziU8*)Zi8GetTableAddress(lang, 0xB, ZI_WORK);
                ZI_WORK->unk_0x1764 = p;
            }
        }
        if (ZI_WORK->unk_0x1764 != ZI8_NULL) {
            while (ZI_WORK->unk_0x1764[0] != 0xFF && grpIdx != 0) {
                do {
                    ZI_WORK->unk_0x1764 += 2;
                } while (ZI_WORK->unk_0x1764[0] != 0xFF);
                ZI_WORK->unk_0x1764 += 1;
                grpIdx--;
            }
        }
    }
    if (ZI_WORK->unk_0x1764 == ZI8_NULL) {
        ret = Zi8MatchROMdata0(keys, count, lang, out, maxLen, flag8, flag9, 0,
                               1, x, ZI8_NULL, &ZI_WORK->dawgCtx,
                               ZI_WORK->unk_0x1760, ZI_WORK);
        goto Lret;
    }
    while (ZI_WORK->unk_0x1764[0] != 0xFF) {
        ret = Zi8MatchROMdata0(keys, count, lang, out, maxLen, flag8, flag9,
                               ZI_WORK->unk_0x1764[0], ZI_WORK->unk_0x1764[1],
                               x, ZI8_NULL, &ZI_WORK->dawgCtx,
                               ZI_WORK->unk_0x1760, ZI_WORK);
        if (ret != 0) goto Lret;
        ZI_WORK->unk_0x1764 += 2;
        flag9 = 0;
    }
Lret:
    return ret;
}

static ziU8 Zi8MatchROMdata2(ziWChar* keys, ziU8 count, ziU8 lang, ziWChar* out,
                             ziU16 maxLen, ziU8 flag8, ziU8 flag9, ziU8 g,
                             ziU8* grp, ziU8 x ZI_NEED_WORK) {
    ziU8 ret = 0;
    ziU8 n;
    ziS32 c;

    if (g != 0) return 0;
    if (flag9 == 0) {
        ZI_WORK->unk_0x1768 = 0;
        ZI_WORK->unk_0x17EA = 0;
        if (grp != ZI8_NULL && grp[0] == 0xC && lang == 0xA &&
            ZI_WORK->unk_0x141C != 0) {
            ZI_WORK->unk_0x141E = 0x10;
        } else {
            ZI_WORK->unk_0x141E = 0;
        }
    }
Lbec:
    ZI_WORK->unk_0x141F = 1;
    ret = Zi8MatchROMdata1(keys + ZI_WORK->unk_0x17EA,
                           (ziU8)(count - ZI_WORK->unk_0x17EA), lang,
                           ZI_WORK->unk_0x17F4 + ZI_WORK->unk_0x17EA, maxLen,
                           flag8, flag9, ZI_WORK->unk_0x1768, grp, x, ZI_WORK);
    if (ret != 0) {
        n = (ziU8)(ZI_WORK->unk_0x17EA + ret);
        while (n != 0) {
            out[n - 1] = ZI_WORK->unk_0x17F4[n - 1];
            n--;
        }
        ret = (ziU8)(ret + ZI_WORK->unk_0x17EA);
        goto Lret;
    }
    if (flag9 != 0) goto Lret;
    if (count == 1) goto Lret;
    if (flag8 == 1 && ZI_WORK->unk_0x1768 == 0) {
        if (Zi8MatchROMdata1(keys + ZI_WORK->unk_0x17EA,
                             (ziU8)(count - ZI_WORK->unk_0x17EA), lang,
                             ZI_WORK->unk_0x17F4 + ZI_WORK->unk_0x17EA, maxLen,
                             0, flag9, ZI_WORK->unk_0x1768, grp, x,
                             ZI_WORK) != 0) {
            goto Lret;
        }
    }
    if ((Zi8GetTableCount(lang, 0x1F, ZI_WORK) & 2) == 0) {
        for (n = 0; n < count; n++) {
            if (keys[n] == 0xEFF1) goto Lret;
        }
    }
    if (ZI_WORK->unk_0x141F > maxLen) goto Lret;
    n = ZI_WORK->unk_0x141F;
    while (n != 0) {
        ret = Zi8MatchROMdata1(keys + ZI_WORK->unk_0x17EA, n, lang,
                               ZI_WORK->unk_0x17F4 + ZI_WORK->unk_0x17EA,
                               maxLen, 1, 0, ZI_WORK->unk_0x1768, grp, x,
                               ZI_WORK);
        if (ret != 0) {
            ZI_WORK->unk_0x17EA += ret;
            if (ZI_WORK->unk_0x17EA == count) {
                return 0;
            }
            ZI_WORK->unk_0x1768++;
            flag9 = 0;
            ZI_WORK->unk_0x141E = 0;
            if (ZI_WORK->dawgCtx.key == 0 && lang == 0xA) {
                for (n = 0; n < ZI_WORK->unk_0x17EA; n++) {
                    c = ZI_WORK->unk_0x17F4[n];
                    switch (c) {
                    case 0x61:
                    case 0x6F:
                    case 0x75:
                        ZI_WORK->unk_0x141E = 0x10;
                        goto Lbec;
                    }
                }
            }
            goto Lbec;
        }
        n--;
    }
Lret:
    return ret;
}

ziU8 Zi8MatchROMdata(ziWChar* keys, ziU8 count, ziU8 lang, ziWChar* out,
                     ziU16 maxLen, ziU8 flag8, ziU8 flag9, ziU8 g, ziU8 x
                     ZI_NEED_WORK) {
    ziU8 ret = 0;
    ziS32 tsize = 0;

    if ((ziS32)maxLen < (ziS32)count) {
        Zi8LogError(0x321, ZI_WORK);
        goto Lret;
    }
    if (flag9 == 2) {
        Zi8LogError(0x64, ZI_WORK);
        goto Lret;
    }
    if (flag9 == 0) {
        ZI_WORK->unk_0x17EC = 0;
        ZI_WORK->unk_0x17F0 = NextDawgGroup(ZI8_NULL, lang, ZI_WORK);
    } else {
        if (ZI_WORK->unk_0x17EC != 0) {
            Zi8LogError(0x64, ZI_WORK);
            goto Lret;
        }
    }
    tsize = Zi8GetTableSize(lang, 0x1C, ZI_WORK);
    if (tsize == 0) {
        ret = Zi8MatchROMdata2(keys, count, lang, out, maxLen, flag8, flag9, g,
                               ZI8_NULL, x, ZI_WORK);
        goto La0;
    }
    while (ZI_WORK->unk_0x17F0 != ZI8_NULL) {
        ret = Zi8MatchROMdata2(keys, count, lang, out, maxLen, flag8, flag9, g,
                               ZI_WORK->unk_0x17F0, x, ZI_WORK);
        if (ret != 0) break;
        flag9 = 0;
        if (count <= 1 && lang == 0x36) break;
        ZI_WORK->unk_0x17F0 =
            NextDawgGroup(ZI_WORK->unk_0x17F0, lang, ZI_WORK);
    }
La0:
    if (ret != 0) goto Lerr;
    if (flag9 != 0) goto Lerr;
    if (flag8 != 1) goto Lerr;
    if (count != 1) goto Lerr;
    if (maxLen < 1) goto Lerr;
    flag8 = 0;
    ZI_WORK->unk_0x17EC = 1;
    if (tsize != 0) {
        ZI_WORK->unk_0x17F0 = NextDawgGroup(ZI8_NULL, lang, ZI_WORK);
        while (ZI_WORK->unk_0x17F0 != ZI8_NULL) {
            if (Zi8MatchROMdata2(keys, count, lang, out, maxLen, flag8, flag9,
                                 g, ZI_WORK->unk_0x17F0, x, ZI_WORK) != 0) {
                out[0] = keys[0];
                ret = 1;
                goto Lerr;
            }
            ZI_WORK->unk_0x17F0 =
                NextDawgGroup(ZI_WORK->unk_0x17F0, lang, ZI_WORK);
        }
        goto Lerr;
    }
    if (Zi8MatchROMdata2(keys, count, lang, out, maxLen, flag8, flag9, g,
                         ZI8_NULL, x, ZI_WORK) != 0) {
        out[0] = keys[0];
        ret = 1;
    }
Lerr:
    Zi8LogError(0x64, ZI_WORK);
Lret:
    return ret;
}

ziU8 Zi8SyllablesROMdata(ziWChar* keys, ziU8 count, ziU8 lang, ziWChar* out,
                         ziU16 a, ziU8 b, ziU8* cntOut, ziU8 c ZI_NEED_WORK) {
    ziU8 t1;
    ziU8 t2;

    t1 = 0x1A;
    t2 = 0x1B;
    if (cntOut != ZI8_NULL) {
        *cntOut = 0;
    }
    if (c != 0) {
        t1 = 0x18;
        t2 = 0x19;
    }
    if (Zi8GetTableSize(lang, t1, ZI_WORK) == 0) {
        if (t1 == 0x1A) {
            t1 = 0x18;
            t2 = 0x19;
        } else {
            t1 = 0x1A;
            t2 = 0x1B;
        }
    }
    return Zi8MatchROMdata0(keys, count, lang, out, a, 1, b, t1, t2, 0, cntOut,
                            &ZI_WORK->dawgCtx, ZI_WORK->unk_0x1760, ZI_WORK);
}
