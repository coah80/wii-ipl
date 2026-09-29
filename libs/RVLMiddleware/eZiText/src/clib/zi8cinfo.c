#include <zi8clib/zitypes.h>
#include <zi8clib/zierror.h>

extern ziU8 Zi8GetFormatVersion(ziU8 arg ZI_NEED_WORK);
extern ziU32 Zi8GetTableAddress(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);
extern ziU16 Zi8GetTableCount(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);
extern ziU16 Zi8GetPCode(ziU8* tbl, ziU8* row);
typedef struct { ziU8 b[0xC]; } ziE12;
extern ziU16 Zi8Uni2Ptr(ziU16 ch, ziE12* buf ZI_NEED_WORK);
extern ziU8 ZiCharInfo2(ziWChar w, ziWChar* buf, ziU8 maxSize, ziU8 hetMode, ziWChar* other, ziU8 flag ZI_NEED_WORK);

static const ziU8 zi8CJTable[0x19] = {
    0x01, 0x02, 0x03, 0x05, 0x06, 0x07, 0x09, 0x0A, 0x0B, 0x0D, 0x0E, 0x0F, 0x11,
    0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x19, 0x1A, 0x1B, 0x1D, 0x1E, 0x1F
};

ziU8 Zi8GetCJInfo(ziU8* p, ziWChar* out, ziU8 arg ZI_NEED_WORK) {
    ziS32 code;
    ziS32 i;
    ziS32 j;
    ziS32 m;
    ziS32 cnt;

    ZI_WORK->unk_0x16 = (ziU8)(Zi8GetFormatVersion(1, ZI_WORK) & 2);
    if (ZI_WORK->unk_0x16 == 0) {
        Zi8LogError(0x8FC, ZI_WORK);
        return 0;
    }
    if (arg < 6) {
        Zi8LogError(0x322, ZI_WORK);
        return 0;
    }
    cnt = p[0] & 7;
    code = p[0] | (p[1] << 8) | (p[2] << 16) | ((ziS32)p[3] << 24);
    code >>= 3;
    for (i = 0; i < cnt; i++) {
        m = code & 0x1F;
        code >>= 5;
        for (j = 0; j < 0x19; j++) {
            if (zi8CJTable[j] == m) {
                break;
            }
        }
        if (j >= 0x19) {
            Zi8LogError(0x26D, ZI_WORK);
            return 0;
        }
        out[i] = (ziWChar)(j + 0x41);
    }
    out[i] = 0;
    Zi8LogError(0x64, ZI_WORK);
    return (ziU8)i;
}

ziU8 Zi8GetPInfo(ziWChar w, ziWChar* out, ziU8 arg ZI_NEED_WORK) {
    ziU8 n;
    ziU16 fE;
    ziU16 fC;
    ziU16 fA;

    n = 0;
    if (arg < 8) {
        Zi8ReplaceLastError(0x322, ZI_WORK);
        return 0;
    }
    if (w == 0) {
        Zi8LogError(0x276, ZI_WORK);
        return 0;
    }

    fE = ((ziU16)w >> 9) & 0x3F;
    fC = ((ziU16)w >> 3) & 0x3F;
    fA = w & 7;

    if (fE != 1) {
        switch (fE) {
        case 0x3C:
            out[n] = 0xF362;
            break;
        case 0x3F:
            out[n] = 0xF370;
            break;
        case 0x02:
            out[n] = 0xF364;
            break;
        case 0x05:
            out[n] = 0xF374;
            break;
        case 0x34:
            out[n] = 0xF367;
            break;
        case 0x37:
            out[n] = 0xF36B;
            break;
        case 0x06:
            out[n] = 0xF36A;
            break;
        case 0x09:
            out[n] = 0xF371;
            break;
        case 0x1C:
            out[n] = 0xF37A;
            break;
        case 0x18:
            out[n] = 0xF363;
            break;
        case 0x0A:
            out[n] = 0xF378;
            break;
        case 0x0C:
            out[n] = 0xF36D;
            break;
        case 0x38:
            out[n] = 0xF366;
            break;
        case 0x26:
            out[n] = 0xF36E;
            break;
        case 0x2B:
            out[n] = 0xF36C;
            break;
        case 0x3B:
            out[n] = 0xF368;
            break;
        case 0x1A:
            out[n] = 0xF373;
            break;
        case 0x2C:
            out[n] = 0xF372;
            break;
        case 0x11:
            out[n] = 0xF377;
            break;
        case 0x0D:
            out[n] = 0xF379;
            break;
        case 0x1D:
            out[n++] = 0xF37A;
            out[n] = 0xF368;
            break;
        case 0x19:
            out[n++] = 0xF363;
            out[n] = 0xF368;
            break;
        case 0x1B:
            out[n++] = 0xF373;
            out[n] = 0xF368;
            break;
        default:
            Zi8LogError(0x277, ZI_WORK);
            return 0;
        }
        n++;
    }

    if (fC != 0) {
        switch (fC) {
        case 1:
            out[n++] = 0xF369;
            out[n++] = 0xF361;
            out[n] = 0xF36F;
            break;
        case 2:
            out[n++] = 0xF369;
            out[n++] = 0xF361;
            out[n] = 0xF36E;
            break;
        case 3:
            out[n++] = 0xF369;
            out[n++] = 0xF361;
            out[n++] = 0xF36E;
            out[n] = 0xF367;
            break;
        case 4:
            out[n++] = 0xF369;
            out[n] = 0xF361;
            break;
        case 8:
            out[n] = 0xF369;
            break;
        case 9:
            out[n++] = 0xF369;
            out[n] = 0xF365;
            break;
        case 0xB:
            out[n++] = 0xF369;
            out[n] = 0xF375;
            break;
        case 0xC:
            out[n++] = 0xF369;
            out[n] = 0xF36E;
            break;
        case 0xD:
            out[n++] = 0xF369;
            out[n++] = 0xF36E;
            out[n] = 0xF367;
            break;
        case 0xF:
            out[n++] = 0xF369;
            out[n++] = 0xF36F;
            out[n++] = 0xF36E;
            out[n] = 0xF367;
            break;
        case 0x10:
            out[n++] = 0xF375;
            out[n++] = 0xF361;
            out[n] = 0xF36E;
            break;
        case 0x11:
            out[n++] = 0xF375;
            out[n++] = 0xF361;
            out[n++] = 0xF36E;
            out[n] = 0xF367;
            break;
        case 0x13:
            out[n++] = 0xF375;
            out[n++] = 0xF361;
            out[n] = 0xF369;
            break;
        case 0x17:
            out[n++] = 0xF375;
            out[n] = 0xF361;
            break;
        case 0x18:
            out[n] = 0xF375;
            break;
        case 0x1C:
            out[n++] = 0xF375;
            out[n] = 0xF36E;
            break;
        case 0x1D:
            out[n++] = 0xF375;
            out[n] = 0xF369;
            break;
        case 0x1E:
            out[n++] = 0xF375;
            out[n] = 0xF36F;
            break;
        case 0x1F:
            if (fE == 0x26 || fE == 0x2B) {
                out[n++] = 0xF376;
                out[n] = 0xF365;
            } else {
                out[n++] = 0xF375;
                out[n] = 0xF365;
            }
            break;
        case 0x20:
            out[n++] = 0xF361;
            out[n] = 0xF36E;
            break;
        case 0x21:
            out[n++] = 0xF361;
            out[n++] = 0xF36E;
            out[n] = 0xF367;
            break;
        case 0x23:
            out[n] = 0xF361;
            break;
        case 0x25:
            out[n++] = 0xF361;
            out[n] = 0xF369;
            break;
        case 0x26:
            out[n++] = 0xF361;
            out[n] = 0xF36F;
            break;
        case 0x28:
            out[n++] = 0xF36F;
            out[n++] = 0xF36E;
            out[n] = 0xF367;
            break;
        case 0x2A:
            out[n++] = 0xF36F;
            out[n] = 0xF375;
            break;
        case 0x2B:
            out[n] = 0xF36F;
            break;
        case 0x30:
            out[n++] = 0xF365;
            out[n] = 0xF36E;
            break;
        case 0x31:
            out[n++] = 0xF365;
            out[n++] = 0xF36E;
            out[n] = 0xF367;
            break;
        case 0x33:
            out[n++] = 0xF365;
            out[n] = 0xF372;
            break;
        case 0x34:
            out[n] = 0xF365;
            break;
        case 0x35:
            out[n++] = 0xF365;
            out[n] = 0xF369;
            break;
        case 0x38:
            out[n] = 0xF376;
            break;
        case 0x39:
            out[n++] = 0xF376;
            out[n++] = 0xF361;
            out[n] = 0xF36E;
            break;
        default:
            Zi8LogError(0x278, ZI_WORK);
            return 0;
        }
        n++;
    }

    switch (fA) {
    case 1:
        out[n++] = 0xF331;
        break;
    case 2:
        out[n++] = 0xF332;
        break;
    case 3:
        out[n++] = 0xF333;
        break;
    case 4:
        out[n++] = 0xF334;
        break;
    case 5:
        out[n++] = 0xF335;
        break;
    default:
        break;
    }

    out[n] = 0;
    Zi8LogError(0x64, ZI_WORK);
    return n;
}

ziU8 Zi8GetZInfo(ziWChar w, ziWChar* out, ziU8 arg ZI_NEED_WORK) {
    ziU8 n;
    ziU16 fE;
    ziU16 fC;
    ziU16 fA;

    n = 0;
    if (arg < 5) {
        Zi8ReplaceLastError(0x322, ZI_WORK);
        return 0;
    }
    if (w == 0) {
        Zi8LogError(0x280, ZI_WORK);
        return 0;
    }

    fE = ((ziU16)w >> 9) & 0x3F;
    fC = ((ziU16)w >> 3) & 0x3F;
    fA = w & 7;

    switch (fE) {
    case 0x3C:
        out[n++] = 0xF305;
        break;
    case 0x19:
        out[n++] = 0xF314;
        break;
    case 0x18:
        out[n++] = 0xF318;
        break;
    case 0x02:
        out[n++] = 0xF309;
        break;
    case 0x38:
        out[n++] = 0xF308;
        break;
    case 0x34:
        out[n++] = 0xF30D;
        break;
    case 0x3B:
        out[n++] = 0xF30F;
        break;
    case 0x06:
        out[n++] = 0xF310;
        break;
    case 0x37:
        out[n++] = 0xF30E;
        break;
    case 0x2B:
        out[n++] = 0xF30C;
        break;
    case 0x0C:
        out[n++] = 0xF307;
        break;
    case 0x26:
        out[n++] = 0xF30B;
        break;
    case 0x3F:
        out[n++] = 0xF306;
        break;
    case 0x09:
        out[n++] = 0xF311;
        break;
    case 0x2C:
        out[n++] = 0xF316;
        break;
    case 0x1B:
        out[n++] = 0xF315;
        break;
    case 0x1A:
        out[n++] = 0xF319;
        break;
    case 0x05:
        out[n++] = 0xF30A;
        break;
    case 0x0A:
        out[n++] = 0xF312;
        break;
    case 0x1D:
        out[n++] = 0xF313;
        break;
    case 0x1C:
        out[n++] = 0xF317;
        break;
    default:
        Zi8LogError(0x281, ZI_WORK);
        return 0;
    }

    switch (fC) {
    case 0:
        if (fE != 0x0C && fE != 0x26) {
            return 0;
        }
        break;
    case 0x11:
        out[n++] = 0xF327;
        out[n++] = 0xF31A;
        break;
    case 0x17:
        out[n++] = 0xF327;
        break;
    case 0x12:
        out[n++] = 0xF327;
        out[n++] = 0xF31B;
        break;
    case 0x1A:
        out[n++] = 0xF327;
        out[n++] = 0xF320;
        break;
    case 0x15:
        out[n++] = 0xF327;
        out[n++] = 0xF31D;
        break;
    case 0x1B:
        out[n++] = 0xF327;
        out[n++] = 0xF321;
        break;
    case 0x1C:
        out[n++] = 0xF327;
        out[n++] = 0xF322;
        break;
    case 0x1E:
        out[n++] = 0xF327;
        out[n++] = 0xF323;
        break;
    case 0x1D:
        out[n++] = 0xF327;
        out[n++] = 0xF324;
        break;
    case 0x1F:
        out[n++] = 0xF327;
        out[n++] = 0xF325;
        break;
    case 0x3F:
        out[n++] = 0xF329;
        out[n++] = 0xF325;
        break;
    case 0x37:
        out[n++] = 0xF329;
        break;
    case 0x27:
        out[n++] = 0xF328;
        break;
    case 0x25:
    case 0x35:
        out[n++] = 0xF329;
        out[n++] = 0xF31D;
        break;
    case 0x3C:
        out[n++] = 0xF329;
        out[n++] = 0xF322;
        break;
    case 0x2C:
        out[n++] = 0xF328;
        out[n++] = 0xF322;
        break;
    case 0x3E:
        out[n++] = 0xF329;
        out[n++] = 0xF323;
        break;
    case 0x2E:
        out[n++] = 0xF328;
        out[n++] = 0xF323;
        break;
    case 0x21:
        out[n++] = 0xF328;
        out[n++] = 0xF31A;
        break;
    case 0x22:
        out[n++] = 0xF328;
        out[n++] = 0xF31B;
        break;
    case 0x28:
        out[n++] = 0xF328;
        out[n++] = 0xF31E;
        break;
    case 0x29:
        out[n++] = 0xF328;
        out[n++] = 0xF31F;
        break;
    case 0x2D:
        out[n++] = 0xF328;
        out[n++] = 0xF324;
        break;
    case 0x2F:
        out[n++] = 0xF328;
        out[n++] = 0xF325;
        break;
    case 1:
        out[n++] = 0xF31A;
        break;
    case 2:
        out[n++] = 0xF31B;
        break;
    case 3:
        out[n++] = 0xF31C;
        break;
    case 4:
        out[n++] = 0xF326;
        break;
    case 8:
        out[n++] = 0xF31E;
        break;
    case 0x18:
        out[n++] = 0xF327;
        out[n++] = 0xF31E;
        break;
    case 9:
        out[n++] = 0xF31F;
        break;
    case 0x0A:
        out[n++] = 0xF320;
        break;
    case 0x0B:
        out[n++] = 0xF321;
        break;
    case 0x0C:
        out[n++] = 0xF322;
        break;
    case 0x0E:
        out[n++] = 0xF323;
        break;
    case 0x0D:
        out[n++] = 0xF324;
        break;
    case 0x0F:
        out[n++] = 0xF325;
        break;
    case 7:
        break;
    default:
        Zi8LogError(0x282, ZI_WORK);
        return 0;
    }

    switch (fA) {
    case 1:
        out[n++] = 0xF331;
        break;
    case 2:
        out[n++] = 0xF332;
        break;
    case 3:
        out[n++] = 0xF333;
        break;
    case 4:
        out[n++] = 0xF334;
        break;
    case 5:
        out[n++] = 0xF335;
        break;
    default:
        break;
    }

    out[n] = 0;
    Zi8LogError(0x64, ZI_WORK);
    return n;
}

ziU16 zi8StrokeCode(ziU32 code ZI_NEED_WORK) {
    switch (code) {
    case 0:
        return 0xEF02;
    case 1:
        return 0xEF04;
    case 2:
        return 0xEF01;
    case 3:
        return 0xEF07;
    case 4:
        return 0xEF06;
    case 5:
        return 0xEF03;
    case 6:
        return 0xEF05;
    case 7:
        return 0xEF08;
    case 8:
        return 0xEF02;
    case 11:
        return 0xEF07;
    default:
        Zi8LogError(0x14A, ZI_WORK);
        return 0;
    }
}

ziU8 Zi8GetSInfo(ziU8* p, ziU8* p2, ziWChar* out, ziU8 arg ZI_NEED_WORK) {
    ziU8 n;
    ziS32 i;
    ziS32 cnt;

    n = 0;
    Zi8LogError(0x64, ZI_WORK);
    if (arg <= 0x17) {
        Zi8ReplaceLastError(0x322, ZI_WORK);
        return 0;
    }

    for (i = 0; i < 4; i++) {
        if (i != 0) {
            out[n] = zi8StrokeCode((ziS32)(p[i] & 0xF0) >> 4, ZI_WORK);
            if (out[n++] == 0) {
            undo:
                out[--n] = 0;
                return n;
            }
        }
        out[n] = zi8StrokeCode(p[i] & 0xF, ZI_WORK);
        if (out[n++] == 0) {
            goto undo;
        }
    }

    out[n] = zi8StrokeCode(*p2 & 0xF, ZI_WORK);
    if (out[n++] == 0) {
        goto undo;
    }

    cnt = (ziS32)(*p2++ & 0xE0) >> 4;
    for (i = 0; i < cnt; i++) {
        out[n] = zi8StrokeCode((ziS32)(p2[i] & 0xF0) >> 4, ZI_WORK);
        if (out[n++] == 0) {
            goto undo;
        }
        out[n] = zi8StrokeCode(p2[i] & 0xF, ZI_WORK);
        if (out[n++] == 0) {
            goto undo;
        }
    }

    out[n] = 0;
    return n;
}

ziU16 Zi81KeyPYinfo(ziU16 w ZI_NEED_WORK) {
    switch (w) {
    case 0xF361:
        return 0xEFF2;
    case 0xF362:
        return 0xEFF2;
    case 0xF363:
        return 0xEFF2;
    case 0xF364:
        return 0xEFF3;
    case 0xF365:
        return 0xEFF3;
    case 0xF366:
        return 0xEFF3;
    case 0xF367:
        return 0xEFF4;
    case 0xF368:
        return 0xEFF4;
    case 0xF369:
        return 0xEFF4;
    case 0xF36A:
        return 0xEFF5;
    case 0xF36B:
        return 0xEFF5;
    case 0xF36C:
        return 0xEFF5;
    case 0xF36D:
        return 0xEFF6;
    case 0xF36E:
        return 0xEFF6;
    case 0xF36F:
        return 0xEFF6;
    case 0xF370:
        return 0xEFF7;
    case 0xF371:
        return 0xEFF7;
    case 0xF372:
        return 0xEFF7;
    case 0xF373:
        return 0xEFF7;
    case 0xF374:
        return 0xEF08;
    case 0xF375:
        return 0xEF08;
    case 0xF376:
        return 0xEF08;
    case 0xF377:
        return 0xEF07;
    case 0xF378:
        return 0xEF07;
    case 0xF379:
        return 0xEF07;
    case 0xF37A:
        return 0xEF07;
    case 0xF331:
        return 0xEFF1;
    case 0xF332:
        return 0xEFF2;
    case 0xF333:
        return 0xEFF3;
    case 0xF334:
        return 0xEFF4;
    case 0xF335:
        return 0xEFF5;
    default:
        Zi8LogError(0x14B, ZI_WORK);
        return w;
    }
}

ziU16 Zi81KeyZYinfo(ziU16 w ZI_NEED_WORK) {
    switch (w) {
    case 0xF305:
        return 0xEFF1;
    case 0xF306:
        return 0xEFF1;
    case 0xF307:
        return 0xEFF1;
    case 0xF308:
        return 0xEFF1;
    case 0xF309:
        return 0xEFF2;
    case 0xF30A:
        return 0xEFF2;
    case 0xF30B:
        return 0xEFF2;
    case 0xF30C:
        return 0xEFF2;
    case 0xF30D:
        return 0xEFF3;
    case 0xF30E:
        return 0xEFF3;
    case 0xF30F:
        return 0xEFF3;
    case 0xF310:
        return 0xEFF4;
    case 0xF311:
        return 0xEFF4;
    case 0xF312:
        return 0xEFF4;
    case 0xF313:
        return 0xEFF5;
    case 0xF314:
        return 0xEFF5;
    case 0xF315:
        return 0xEFF5;
    case 0xF316:
        return 0xEFF5;
    case 0xF317:
        return 0xEFF6;
    case 0xF318:
        return 0xEFF6;
    case 0xF319:
        return 0xEFF6;
    case 0xF31A:
        return 0xEFF7;
    case 0xF31B:
        return 0xEFF7;
    case 0xF31C:
        return 0xEFF7;
    case 0xF31D:
        return 0xEFF7;
    case 0xF31E:
        return 0xEF08;
    case 0xF31F:
        return 0xEF08;
    case 0xF320:
        return 0xEF08;
    case 0xF321:
        return 0xEF08;
    case 0xF322:
        return 0xEF07;
    case 0xF323:
        return 0xEF07;
    case 0xF324:
        return 0xEF07;
    case 0xF325:
        return 0xEF07;
    case 0xF326:
        return 0xEF07;
    case 0xF327:
        return 0xEF06;
    case 0xF328:
        return 0xEF06;
    case 0xF329:
        return 0xEF06;
    case 0xF331:
        return 0xEFF1;
    case 0xF332:
        return 0xEFF2;
    case 0xF333:
        return 0xEFF3;
    case 0xF334:
        return 0xEFF4;
    case 0xF335:
        return 0xEFF5;
    default:
        Zi8LogError(0x14C, ZI_WORK);
        return w;
    }
}

ziU8 Zi8GetCharInfo(ziWChar w, ziWChar* buf, ziU8 maxSize, ziU8 hetMode ZI_NEED_WORK) {
    return ZiCharInfo2(w, buf, maxSize, hetMode, 0, (ziU8)0, ZI_WORK);
}

ziU8 ZiCharInfo2(ziWChar w, ziWChar* buf, ziU8 maxSize, ziU8 hetMode, ziWChar* other, ziU8 flag ZI_NEED_WORK) {
    ziE12 ctx;
    ziE12* ctxP;
    ziU8* tbl;
    ziU8* tbl2;
    ziU8* tbl5;
    ziU16 tblCount;
    ziU16 cnt5;
    ziU16 v;
    ziU16 c;
    ziU16 i;
    ziU8 ok;
    ziU8 hi;
    ziU8 lo;
    ziU16 j;
    ziS32 k;
    ziU8 ret;
    ziU16 py;

    ctxP = &ctx;
    tbl2 = ZI8_NULL;
    if (buf == ZI8_NULL || maxSize == 0) {
        Zi8LogError(0x12C, ZI_WORK);
        return 0;
    }

    if ((hetMode & 0x80) != 0) {
        hetMode &= 0x7F;
        if (Zi8GetFormatVersion(1, ZI_WORK) >= 4) {
            tblCount = Zi8GetTableCount(1, 0x19, ZI_WORK);
            tbl = (ziU8*)Zi8GetTableAddress(1, 0x19, ZI_WORK);
        } else {
            tblCount = 0;
            tbl = ZI8_NULL;
        }
        if (hetMode == 1) {
            tbl2 = (ziU8*)Zi8GetTableAddress(1, 3, ZI_WORK);
        } else {
            tbl2 = (ziU8*)Zi8GetTableAddress(1, 4, ZI_WORK);
        }
        if (hetMode == 1 || hetMode == 2) {
            if (tblCount <= (ziU32)Zi8GetTableCount(1, 8, ZI_WORK)) {
                hi = (ziU8)((w >> 8) & 0xFF);
                lo = (ziU8)w;
                i = 0;
                goto cond;
            head:
                if (hi != tbl[0]) {
                    goto incr;
                }
                if (lo != tbl[1]) {
                    goto incr;
                }
                v = (ziU16)((((tbl[2] & 0x1F) << 8) | tbl[3]) << 1);
                c = (ziU16)(tbl2[v] + ((ziU16)(((ziU32)tbl[2] >> 5) & 7)) + ((ziU16)(((ziU16)tbl2[v + 1]) << 8)));
                if (hetMode == 1) {
                    ret = Zi8GetPInfo(c, buf, maxSize, ZI_WORK);
                } else {
                    ret = Zi8GetZInfo(c, buf, maxSize, ZI_WORK);
                }
                goto done;
            }
        }
    }
    goto uni;
done:
    if (hetMode == 0x11) {
        for (k = 0; k < (ziU8)ret; k++) {
            switch (buf[k]) {
            case 0xEF03:
            case 0xEF05:
            case 0xEF06:
            case 0xEF08:
                buf[k] = 0xEF0A;
                break;
            default:
                break;
            }
        }
    }
    Zi8LogError(0x64, ZI_WORK);
    return ret;
incr:
    i++;
    tbl += 4;
cond:
    if (i < tblCount) {
        goto head;
    }
uni:
    v = Zi8Uni2Ptr((ziU16)w, ctxP, ZI_WORK);
    if (v == 0xFFFF) {
        ret = 0;
        goto done;
    }
    tbl = (ziU8*)Zi8GetTableAddress(1, 1, ZI_WORK);
    tbl += ((ziU32)(ctxP->b[9] & 0xF) << 16) | (ctxP->b[0xB] | (ctxP->b[0xA] << 8));
    ZI_WORK->unk_0x16 = (ziU8)(Zi8GetFormatVersion(1, ZI_WORK) & 2);
    if (ZI_WORK->unk_0x16 != 0 && hetMode != 7 && hetMode != 0xA && hetMode != 8 && hetMode != 9) {
        switch (tbl[0] & 7) {
        case 2:
            tbl += 2;
            break;
        case 3:
        case 4:
            tbl += 3;
            break;
        case 5:
            tbl += 4;
            break;
        default:
            tbl += 1;
            break;
        }
    }

    switch (hetMode) {
    case 7:
    case 8:
    case 9:
    case 0xA:
        ret = Zi8GetCJInfo(tbl, buf, maxSize, ZI_WORK);
        if ((hetMode == 9 || hetMode == 0xA) && (ziU8)ret > 2) {
            buf[1] = buf[(ziU8)ret - 1];
            buf[2] = 0;
            ret = 2;
        }
        break;
    case 0:
    case 0x10:
    case 0x11:
        ret = Zi8GetSInfo(ctxP->b, tbl, buf, maxSize, ZI_WORK);
        break;
    case 1:
    case 3:
        tbl2 = (ziU8*)Zi8GetTableAddress(1, 3, ZI_WORK);
        c = Zi8GetPCode(tbl2, ctxP->b);
        ret = Zi8GetPInfo(c, buf, maxSize, ZI_WORK);
        break;
    case 2:
    case 4:
        tbl2 = (ziU8*)Zi8GetTableAddress(1, 4, ZI_WORK);
        c = Zi8GetPCode(tbl2, ctxP->b);
        ret = Zi8GetZInfo(c, buf, maxSize, ZI_WORK);
        break;
    default:
        ret = 0;
        break;
    }

    if (flag != 0 && (ctxP->b[0] & 0x80) != 0 && (hetMode == 3 || hetMode == 4)) {
        tbl5 = (ziU8*)Zi8GetTableAddress(1, 5, ZI_WORK);
        cnt5 = Zi8GetTableCount(1, 5, ZI_WORK);
        while (cnt5 != 0) {
            if (v == (((ziU16)tbl5[1] << 8) | (ziU16)tbl5[0])) {
                break;
            }
            cnt5--;
            tbl5 += 4;
        }
        for (;;) {
            if ((ziU8)ret >= flag) {
                ok = 1;
                for (j = 0; j < (ziU8)ret; j++) {
                    if (j == flag) {
                        break;
                    }
                    if (hetMode == 3) {
                        if (other[j] != Zi81KeyPYinfo(buf[j], ZI_WORK)) {
                            ok = 0;
                            break;
                        }
                    } else {
                        if (other[j] != Zi81KeyZYinfo(buf[j], ZI_WORK)) {
                            ok = 0;
                            break;
                        }
                    }
                }
                if (ok != 0) {
                    goto done;
                }
            }
            if (cnt5 == 0) {
                break;
            }
            if (v != (((ziU16)tbl5[1] << 8) | (ziU16)tbl5[0])) {
                break;
            }
            c = (ziU16)(((ziU16)tbl5[2] | ((ziU16)(tbl5[3] & 1) << 8)) << 1);
            c = (ziU16)(tbl2[c] + (((ziU16)tbl5[3] & 0xF0) >> 4) + (((ziU16)tbl2[c + 1]) << 8));
            cnt5--;
            tbl5 += 4;
            if (hetMode == 3) {
                ret = Zi8GetPInfo(c, buf, maxSize, ZI_WORK);
            } else {
                ret = Zi8GetZInfo(c, buf, maxSize, ZI_WORK);
            }
        }
    }
}

ziU8 Zi8GetCharInfo2(ziWChar w, ziWChar* buf, ziU8 maxSize, ziU8 hetMode,
                     ziWChar* elements, ziU8 elementCount ZI_NEED_WORK) {
    ziU8 ret;
    ziU8 save;

    save = ZI_WORK->unk_0x18;
    ret = ZiCharInfo2(w, buf, maxSize, hetMode, elements, elementCount, ZI_WORK);
    if ((ziU8)ret == 0) {
        if ((save & 0x80) != 0 || (save & 0x40) != 0 || (save & 1) != 0) {
            ZI_WORK->unk_0x18 = 6;
        } else {
            ZI_WORK->unk_0x18 = 1;
        }
        ret = ZiCharInfo2(w, buf, maxSize, hetMode, elements, elementCount, ZI_WORK);
        ZI_WORK->unk_0x18 = save;
    }
    return ret;
}
