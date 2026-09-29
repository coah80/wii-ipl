#include <private/nwc24.h>
#include <revolution/nwc24.h>

#include <revolution/enc.h>
#include <string.h>

enum {
    MSG_OBJ_INITIALIZED = (1 << 8),
    MSG_OBJ_DELIVERING = (1 << 9),
};

#define NWC24i_CHARSET_WORK_SIZE 0x40
#define NWC24i_WORD_LINE_SIZE 0x3f
#define NWC24i_WORD_LINE_SIZE_QP 0x47

static NWC24Err NWC24iGetDefaultCharset(char* charset, u32 size,
                                      NWC24EncodingRegion region);
static NWC24Err NWC24iConvertToInternalEncoding(u16* dst, u32* dstSize,
                                              const u8* src, s32* srcSize,
                                              char* charset, u32 charsetSize,
                                              NWC24EncodingRegion region,
                                              u16 alt);
static NWC24Err NWC24iConvertFromInternalEncoding(u8* dst, u32* dstSize,
                                                const u16* src, s32* srcSize,
                                                char* charset, u32 charsetSize,
                                                NWC24EncodingRegion region,
                                                u16 alt);
static NWC24Err NWC24iDetectEncodingToSend(char* charset, u32 charsetSize,
                                           const u16* src1, u32 src1Len,
                                           const u16* src2, u32 src2Len,
                                           NWC24EncodingRegion region);
static NWC24Err NWC24iDetectBreakPoint(u32* pos, NWC24Charset charset,
                                     const u8* str, u32 size, u32 limit);
static NWC24Err NWC24iSetMsgSubjectPlain(NWC24MsgObj* msg, const u16* subject,
                                       u32 subjectLen,
                                       NWC24EncodingRegion encRegion, u16 unk,
                                       u8* work, u32 workSize, u32 charset,
                                       char* charsetName);
static NWC24Err NWC24iSetMsgSubjectQP(NWC24MsgObj* msg, const u16* subject,
                                    u32 subjectLen,
                                    NWC24EncodingRegion encRegion, u16 unk,
                                    u8* work, u32 workSize, u32 charset,
                                    char* charsetName);
static NWC24Err NWC24iSetMsgSubjectBase64(NWC24MsgObj* msg, const u16* subject,
                                        u32 subjectLen,
                                        NWC24EncodingRegion encRegion, u16 unk,
                                        u8* work, u32 workSize, u32 charset,
                                        char* charsetName);

static const char* sEncNamesJpn[3] = {
    "us-ascii", "iso-2022-jp", "utf-8",
};

static const char* sEncNamesWest[8] = {
    "us-ascii",   "iso-8859-1", "windows-1252", "iso-8859-2",
    "iso-8859-7", "iso-8859-10", "iso-8859-3",  "utf-8",
};

static const char* sEncNamesKor[3] = {
    "us-ascii", "euc-kr", "utf-8",
};

static const char* sEncNamesChn[2] = {
    "us-ascii", "gb2312",
};

NWC24Err NWC24ReadMsgSubjectPublic(const NWC24MsgObj* msg, u16* subject,
                                   u32* subjectLen,
                                   NWC24EncodingRegion encRegion, u16 unk,
                                   u8* work, u32 workSize) {
    NWC24Err result;
    NWC24Err readResult;
    BOOL overflow;
    u32 saved;
    u32 half;
    u32 quota;
    u8* buf;
    u32 size;
    u32 written;
    u32 i;
    u16* p;
    u16 c;

    if (subjectLen == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    saved = *subjectLen;
    *subjectLen = 0;
    overflow = FALSE;

    if (work == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    half = workSize / 2;
    buf = work + half;
    quota = workSize - half;

    result = NWC24GetMsgSubjectSize(msg, &size);
    if (result != NWC24_OK) {
        return result;
    }

    if (size > half) {
        size = half;
        overflow = TRUE;
    }

    result = NWC24ReadMsgSubject(msg, (char*)work, size);
    if (result != NWC24_OK) {
        if (result != NWC24_ERR_OVERFLOW) {
            return result;
        }
        overflow = TRUE;
    }

    result = NWC24DecodeMIMEHeaderFieldBody((u8*)NWC24WorkP, NWC24i_CHARSET_WORK_SIZE,
                                          buf, quota, &written, work, size);
    if (result != NWC24_OK) {
        if (result != NWC24_ERR_OVERFLOW) {
            return result;
        }
        overflow = TRUE;
    }

    *subjectLen = saved;
    result = NWC24iConvertToInternalEncoding(subject, subjectLen, buf,
                                           (s32*)&written,
                                           (char*)NWC24WorkP,
                                           NWC24i_CHARSET_WORK_SIZE, encRegion,
                                           unk);
    if (result != NWC24_OK && result != NWC24_ERR_OVERFLOW) {
        return result;
    }

    for (i = 0, p = subject; i < *subjectLen && (c = *p) != 0; i++, p++) {
        if (c == '\r' || c == '\n') {
            *p = ' ';
        }
    }

    if (result != NWC24_OK) {
        return result;
    }

    if (overflow) {
        return NWC24_ERR_OVERFLOW;
    }

    return NWC24_OK;
}

NWC24Err NWC24ReadMsgTextPublic(const NWC24MsgObj* msg, u16* text, u32* textLen,
                                NWC24EncodingRegion encRegion, u16 unk,
                                u8* work, u32 workSize) {
    NWC24Err result;
    u32 size;
    u32 saved;
    BOOL overflow;
    char* charsetBuf;

    if (textLen == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    saved = *textLen;
    *textLen = 0;
    overflow = FALSE;

    if (work == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    result = NWC24GetMsgTextSize(msg, &size);
    if (result != NWC24_OK) {
        return result;
    }

    if (size > workSize) {
        size = workSize;
        overflow = TRUE;
    }

    result = NWC24ReadMsgTextEx(msg, (char*)work, size,
                                charsetBuf = (char*)NWC24WorkP + 0x20,
                                NWC24i_CHARSET_WORK_SIZE, (NWC24Charset*)work,
                                (NWC24Encoding*)workSize);
    if (result != NWC24_OK) {
        if (result != NWC24_ERR_OVERFLOW) {
            return result;
        }
        overflow = TRUE;
    }

    *textLen = saved;
    result = NWC24iConvertToInternalEncoding(text, textLen, work,
                                           (s32*)&size, charsetBuf,
                                           NWC24i_CHARSET_WORK_SIZE, encRegion,
                                           unk);
    if (result != NWC24_OK) {
        return result;
    }

    if (overflow) {
        result = NWC24_ERR_OVERFLOW;
    }

    return result;
}

NWC24Err NWC24SetMsgSubjectPublic(NWC24MsgObj* msg, const u16* subject,
                                  u32 subjectLen, NWC24EncodingRegion encRegion,
                                  u16 unk, u8* work, u32 workSize) {
    NWC24Err result;
    volatile u32 charset;
    NWC24Encoding encoding;
    char* charsetName;
    u32 type;

    type = msg->data[1];
    if (!(type & MSG_OBJ_INITIALIZED) || (type & MSG_OBJ_DELIVERING)) {
        return NWC24_ERR_PROTECTED;
    }

    if (subject == NULL || subject[0] == 0) {
        return NWC24_ERR_NULL;
    }

    if (subject[subjectLen] != 0) {
        return NWC24_ERR_STRING_END;
    }

    if (work == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    charsetName = (char*)NWC24WorkP;
    result = NWC24iDetectEncodingToSend(charsetName,
                                        NWC24i_CHARSET_WORK_SIZE, subject,
                                        subjectLen, NULL, 0, encRegion);
    if (result != NWC24_OK) {
        return result;
    }

    result = NWC24ParseCharsetStr((NWC24Charset*)&charset, charsetName);
    if (result != NWC24_OK) {
        charset = 0;
    }

    if (charset == 0) {
        return NWC24iSetMsgSubjectPlain(msg, subject, subjectLen, encRegion,
                                        unk, work, workSize, charset,
                                        charsetName);
    }

    switch (encRegion) {
    case NWC24_ENCODING_REGION_JPN:
        encoding = 2;
        break;
    case NWC24_ENCODING_REGION_USA:
    case NWC24_ENCODING_REGION_EUR:
        encoding = 3;
        break;
    case NWC24_ENCODING_REGION_KOR:
    case NWC24_ENCODING_REGION_CHN:
        encoding = 2;
        break;
    default:
        encoding = 2;
        break;
    }

    if (encoding == NWC24_ENC_QUOTED_PRINTABLE) {
        return NWC24iSetMsgSubjectQP(msg, subject, subjectLen, encRegion, unk,
                                     work, workSize, charset,
                                     charsetName);
    }

    return NWC24iSetMsgSubjectBase64(msg, subject, subjectLen, encRegion, unk,
                                     work, workSize, charset,
                                     charsetName);
}

NWC24Err NWC24SetMsgSubjectAndTextPublic(NWC24MsgObj* msg, const u16* subject,
                                         u32 subjectLen, const u16* text,
                                         u32 textLen,
                                         NWC24EncodingRegion encRegion, u16 unk,
                                         u8* work, u32 workSize) {
    char* charsetName;
    NWC24Err result;
    u32 quota;
    s32 convSize;
    volatile u32 charset;
    BOOL is7Bit;
    NWC24Encoding encoding;
    u32 subjQuota;
    u8* subjWork;
    u32 type;

    type = msg->data[1];
    if (!(type & MSG_OBJ_INITIALIZED) || (type & MSG_OBJ_DELIVERING)) {
        return NWC24_ERR_PROTECTED;
    }

    if (subject == NULL || subject[0] == 0) {
        return NWC24_ERR_NULL;
    }

    if (text == NULL || textLen == 0) {
        NWC24Data_Init(&((NWC24MsgObjPrivate*)msg)->text);
        return NWC24SetMsgSubjectPublic(msg, subject, subjectLen, encRegion,
                                        unk, work, workSize);
    }

    if (text[textLen] != 0 || subject[subjectLen] != 0) {
        return NWC24_ERR_STRING_END;
    }

    if (work == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    charsetName = (char*)NWC24WorkP;
    result = NWC24iDetectEncodingToSend(charsetName, NWC24i_CHARSET_WORK_SIZE,
                                        subject, subjectLen, text, textLen,
                                        encRegion);
    if (result != NWC24_OK) {
        return result;
    }

    result = NWC24ParseCharsetStr((NWC24Charset*)&charset, charsetName);
    if (result != NWC24_OK) {
        charset = 0;
    }

    convSize = textLen;
    quota = (workSize * textLen) / (textLen + subjectLen * 4);
    subjQuota = workSize - quota;
    subjWork = work + quota;

    result = NWC24iConvertFromInternalEncoding(work, &quota, text, &convSize,
                                               charsetName,
                                               NWC24i_CHARSET_WORK_SIZE,
                                               encRegion, unk);
    if (result != NWC24_OK) {
        return result;
    }

    result = ENCIs7BitEncoding(&is7Bit, charsetName);
    if (is7Bit && result == 0) {
        encoding = NWC24_ENC_7BIT;
    } else {
        switch (encRegion) {
        case NWC24_ENCODING_REGION_JPN:
            encoding = NWC24_ENC_BASE64;
            break;
        case NWC24_ENCODING_REGION_USA:
        case NWC24_ENCODING_REGION_EUR:
            encoding = NWC24_ENC_QUOTED_PRINTABLE;
            break;
        case NWC24_ENCODING_REGION_KOR:
        case NWC24_ENCODING_REGION_CHN:
            encoding = NWC24_ENC_BASE64;
            break;
        default:
            encoding = NWC24_ENC_BASE64;
            break;
        }
    }

    result = NWC24SetMsgText(msg, (const char*)work, quota - 1, charset,
                           encoding);
    if (result != NWC24_OK) {
        return result;
    }

    if (charset == 0) {
        return NWC24iSetMsgSubjectPlain(msg, subject, subjectLen, encRegion,
                                        unk, subjWork, subjQuota, charset,
                                        charsetName);
    }

    switch (encRegion) {
    case NWC24_ENCODING_REGION_JPN:
        encoding = NWC24_ENC_BASE64;
        break;
    case NWC24_ENCODING_REGION_USA:
    case NWC24_ENCODING_REGION_EUR:
        encoding = NWC24_ENC_QUOTED_PRINTABLE;
        break;
    case NWC24_ENCODING_REGION_KOR:
    case NWC24_ENCODING_REGION_CHN:
        encoding = NWC24_ENC_BASE64;
        break;
    default:
        encoding = NWC24_ENC_BASE64;
        break;
    }

    if (encoding == NWC24_ENC_QUOTED_PRINTABLE) {
        return NWC24iSetMsgSubjectQP(msg, subject, subjectLen, encRegion, unk,
                                     subjWork, subjQuota, charset,
                                     charsetName);
    }

    return NWC24iSetMsgSubjectBase64(msg, subject, subjectLen, encRegion, unk,
                                     subjWork, subjQuota, charset,
                                     charsetName);
}

#pragma dont_inline on
static NWC24Err NWC24iGetDefaultCharset(char* charset, u32 size,
                                      NWC24EncodingRegion region) {
    NWC24Err result = NWC24_OK;

    switch (region) {
    case NWC24_ENCODING_REGION_JPN:
        strncpy(charset, "iso-2022-jp", size - 1);
        charset[size - 1] = 0;
        break;
    case NWC24_ENCODING_REGION_USA:
        strncpy(charset, "iso-8859-1", size - 1);
        charset[size - 1] = 0;
        break;
    case NWC24_ENCODING_REGION_EUR:
        strncpy(charset, "iso-8859-1", size - 1);
        charset[size - 1] = 0;
        break;
    case NWC24_ENCODING_REGION_KOR:
        strncpy(charset, "euc-kr", size - 1);
        charset[size - 1] = 0;
        break;
    case NWC24_ENCODING_REGION_CHN:
        strncpy(charset, "gb2312", size - 1);
        charset[size - 1] = 0;
        break;
    default:
        strncpy(charset, "iso-8859-1", size - 1);
        charset[size - 1] = 0;
        result = NWC24_ERR_INVALID_VALUE;
        break;
    }
    return result;
}
#pragma dont_inline reset

static NWC24Err NWC24iConvertToInternalEncoding(u16* dst, u32* dstSize,
                                              const u8* src, s32* srcSize,
                                              char* charset, u32 charsetSize,
                                              NWC24EncodingRegion region,
                                              u16 alt);
static NWC24Err NWC24iConvertFromInternalEncoding(u8* dst, u32* dstSize,
                                                const u16* src, s32* srcSize,
                                                char* charset, u32 charsetSize,
                                                NWC24EncodingRegion region,
                                                u16 alt);
static NWC24Err NWC24iDetectEncodingToSend(char* charset, u32 charsetSize,
                                           const u16* src1, u32 src1Len,
                                           const u16* src2, u32 src2Len,
                                           NWC24EncodingRegion region);
static NWC24Err NWC24iDetectBreakPoint(u32* pos, NWC24Charset charset,
                                     const u8* str, u32 size, u32 limit);
static NWC24Err NWC24iConvertToInternalEncoding(u16* dst, u32* dstSize,
                                              const u8* src, s32* srcSize,
                                              char* charset, u32 charsetSize,
                                              NWC24EncodingRegion region,
                                              u16 alt) {
    ENCContext ctx;
    NWC24Err result;
    s32 encErr;
    u32 byteSize;
    u32 cap;

    cap = *dstSize * 2;
    *dstSize = 0;
    if (cap < 2) {
        return NWC24_ERR_OVERFLOW;
    }

    if (*charset == '\0') {
        result = NWC24iGetDefaultCharset(charset, charsetSize, region);
        if (result != NWC24_OK) {
            return result;
        }
    }

    do {
        encErr = ENCInitContext(&ctx);
        if (encErr != 0) {
            break;
        }
        encErr = ENCSetExternalEncoding(&ctx, charset);
        if (encErr != 0) {
            break;
        }
        encErr = ENCSetBreakType(&ctx, 3);
        if (encErr != 0) {
            break;
        }
        if (alt != 0) {
            encErr = ENCSetAlternativeCharacter(&ctx, alt, alt);
            if (encErr != 0) {
                break;
            }
        }
        byteSize = cap - 2;
        encErr = ENCConvertToInternalEncoding(&ctx, dst, (s32*)&byteSize,
                                              src, srcSize);
        dst[(byteSize & ~1u) / 2] = 0;
        *dstSize = byteSize / 2 + 1;
    } while (0);

    switch (encErr) {
    case 0:
        result = NWC24_OK;
        break;
    case -3:
        result = NWC24_ERR_INVALID_VALUE;
        break;
    case -1:
        result = NWC24_ERR_OVERFLOW;
        break;
    case -2:
    case -4:
        result = NWC24_ERR_INVALID_CHAR;
        break;
    case -5:
    case -6:
    case -7:
        result = NWC24_ERR_NOT_SUPPORTED;
        break;
    default:
        result = NWC24_ERR_FATAL;
        break;
    }
    return result;
}

static NWC24Err NWC24iConvertFromInternalEncoding(u8* dst, u32* dstSize,
                                                const u16* src, s32* srcSize,
                                                char* charset, u32 charsetSize,
                                                NWC24EncodingRegion region,
                                                u16 alt) {
    ENCContext ctx;
    NWC24Err result;
    s32 encErr;
    u32 cap;
    u32 dstCap;
    u32 srcBytes;

    cap = *dstSize;
    *dstSize = 0;
    if (cap < 1) {
        return NWC24_ERR_OVERFLOW;
    }

    if (*charset == '\0') {
        result = NWC24iGetDefaultCharset(charset, charsetSize, region);
        if (result != NWC24_OK) {
            return result;
        }
    }

    do {
        encErr = ENCInitContext(&ctx);
        if (encErr != 0) {
            break;
        }
        encErr = ENCSetExternalEncoding(&ctx, charset);
        if (encErr != 0) {
            break;
        }
        encErr = ENCSetBreakType(&ctx, 1);
        if (encErr != 0) {
            break;
        }
        if (alt != 0) {
            encErr = ENCSetAlternativeCharacter(&ctx, alt, alt);
            if (encErr != 0) {
                break;
            }
        }
        dstCap = cap - 1;
        srcBytes = *srcSize * 2;
        encErr = ENCConvertFromInternalEncoding(&ctx, dst, (s32*)&dstCap,
                                                src, (s32*)&srcBytes);
        dst[dstCap] = 0;
        *srcSize = srcBytes / 2;
        *dstSize = dstCap + 1;
    } while (0);

    switch (encErr) {
    case 0:
        result = NWC24_OK;
        break;
    case -3:
        result = NWC24_ERR_INVALID_VALUE;
        break;
    case -1:
        result = NWC24_ERR_OVERFLOW;
        break;
    case -2:
    case -4:
        result = NWC24_ERR_INVALID_CHAR;
        break;
    case -5:
    case -6:
    case -7:
        result = NWC24_ERR_NOT_SUPPORTED;
        break;
    default:
        result = NWC24_ERR_FATAL;
        break;
    }
    return result;
}

static NWC24Err NWC24iDetectEncodingToSend(char* charset, u32 charsetSize,
                                         const u16* src1, u32 src1Len,
                                         const u16* src2, u32 src2Len,
                                         NWC24EncodingRegion region) {
    const char** names;
    int numNames;
    int found;
    int i;
    int prev;
    s32 err;
    u32 src1Bytes;
    u32 src2Bytes;

    found = 0;
    i = 0;
    prev = -1;

    switch (region) {
    case NWC24_ENCODING_REGION_JPN:
        names = (const char**)sEncNamesJpn;
        numNames = 3;
        break;
    case NWC24_ENCODING_REGION_USA:
    case NWC24_ENCODING_REGION_EUR:
        names = (const char**)sEncNamesWest;
        numNames = 8;
        break;
    case NWC24_ENCODING_REGION_KOR:
        names = (const char**)sEncNamesKor;
        numNames = 3;
        break;
    case NWC24_ENCODING_REGION_CHN:
        names = (const char**)sEncNamesChn;
        numNames = 2;
        break;
    default:
        names = (const char**)sEncNamesWest;
        numNames = 8;
        break;
    }

    src1Bytes = src1Len * 2;
    src2Bytes = src2Len * 2;

    while (found < numNames - 1) {
        err = ENCCheckEncoding(&found, names + i, numNames - 1 - i,
                             (u16*)src1, src1Bytes);
        if (err != 0) {
            return NWC24_ERR_NOT_SUPPORTED;
        }
        if (found == -1) {
            found = numNames - 1;
            break;
        }
        i += found;
        if (src2 == NULL || prev == i) {
            found = i;
            break;
        }
        err = ENCCheckEncoding(&found, names + i, numNames - 1 - i,
                             (u16*)src2, src2Bytes);
        if (err != 0) {
            return NWC24_ERR_NOT_SUPPORTED;
        }
        if (found == -1) {
            found = numNames - 1;
            break;
        }
        prev = i + found;
        if (prev == i) {
            found = prev;
            break;
        }
        i = prev;
    }

    strncpy(charset, names[found], charsetSize - 1);
    charset[charsetSize - 1] = 0;
    return NWC24_OK;
}

static NWC24Err NWC24iDetectBreakPoint(u32* pos, NWC24Charset charset,
                                     const u8* str, u32 size, u32 limit) {
    const u8* p;
    u32 flag;
    u32 i = 0;
    u32 last = 0;
    u32 j;

    if (pos == NULL || str == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (charset == 0) {
        flag = 1;
    } else if (charset == 0x10008) {
        flag = 0;
    } else if ((charset & 0xffff0000u) == 0x80000 ||
               charset == 0xf1252) {
        flag = 1;
    } else {
        return NWC24_ERR_NOT_SUPPORTED;
    }

    if (size <= limit) {
        *pos = size;
        return NWC24_OK;
    }

    for (p = str; i < limit && *str != '\0'; i++, p++) {
        if (*p == ' ') {
            last = i;
        }
    }

    if (last != 0) {
        *pos = last;
        return NWC24_OK;
    }

    if (flag != 0) {
        *pos = limit;
        return NWC24_OK;
    }

    for (j = 0, p = str; j < limit && *str != '\0'; j++, p++) {
        if ((*p & 0xc0u) != 0x80u) {
            last = j;
        }
    }
    *pos = last;
    return NWC24_OK;
}

static NWC24Err NWC24iSetMsgSubjectPlain(NWC24MsgObj* msg, const u16* subject,
                                       u32 subjectLen,
                                       NWC24EncodingRegion encRegion, u16 unk,
                                       u8* work, u32 workSize, u32 charset,
                                       char* charsetName) {
    u32 halfSize;
    u32 srcLen;
    u32 srcPos;
    u32 cap;
    u8* buf2;
    u32 bufLen;
    u8* p;
    u32 i;
    NWC24Err result;
    u32 pos;

    srcLen = subjectLen;
    halfSize = workSize / 2;
    pos = 0;
    cap = workSize - halfSize;
    buf2 = work + halfSize;

    result = NWC24iConvertFromInternalEncoding(work, &halfSize, subject,
                                               (s32*)&srcLen, charsetName,
                                               NWC24i_CHARSET_WORK_SIZE,
                                               encRegion, unk);
    if (result != NWC24_OK) {
        return result;
    }

    srcLen = halfSize - 1;
    for (p = work, i = 0; i < halfSize; p++, i++) {
        if (*p == '\n' || *p == '\r') {
            *p = ' ';
        }
    }

    NWC24iDetectBreakPoint(&pos, charset, work, srcLen,
                           NWC24i_WORD_LINE_SIZE);
    if (pos == srcLen) {
        return NWC24SetMsgSubject(msg, (const char*)work, srcLen);
    }

    halfSize = cap;
    if (cap <= pos) {
        return NWC24_ERR_OVERFLOW;
    }

    srcPos = pos;
    bufLen = NWC24iStrLCpy((char*)buf2, (const char*)work, pos + 1);
    while (srcPos < srcLen) {
        if (halfSize - bufLen < 3) {
            return NWC24_ERR_OVERFLOW;
        }
        buf2[bufLen++] = '\r';
        buf2[bufLen++] = '\n';
        if (work[srcPos] != ' ') {
            buf2[bufLen++] = ' ';
        }
        NWC24iDetectBreakPoint(&pos, charset, work + srcPos,
                               srcLen - srcPos, 0x47);
        if (halfSize - bufLen <= pos) {
            return NWC24_ERR_OVERFLOW;
        }
        bufLen += NWC24iStrLCpy((char*)buf2 + bufLen,
                                (const char*)work + srcPos, pos + 1);
        srcPos += pos;
    }
    buf2[bufLen] = 0;
    return NWC24SetMsgSubject(msg, (const char*)buf2, bufLen);
}

static NWC24Err NWC24iSetMsgSubjectQP(NWC24MsgObj* msg, const u16* subject,
                                    u32 subjectLen,
                                    NWC24EncodingRegion encRegion, u16 unk,
                                    u8* work, u32 workSize, u32 charset,
                                    char* charsetName) {
    u32 halfSize;
    u32 srcLen;
    u32 pos;
    u32 cap;
    u8* buf2;
    u32 bufLen;
    u32 srcPos;
    u32 encLen;
    u8* p;
    u32 i;
    NWC24Err result;
    u32 limit;

    srcLen = subjectLen;
    halfSize = workSize / 2;
    cap = workSize - halfSize;
    buf2 = work + halfSize;
    pos = 0;

    result = NWC24iConvertFromInternalEncoding(work, &halfSize, subject,
                                               (s32*)&srcLen, charsetName,
                                               NWC24i_CHARSET_WORK_SIZE,
                                               encRegion, unk);
    if (result != NWC24_OK) {
        return result;
    }

    srcLen = halfSize - 1;
    for (p = work, i = 0; i < halfSize; p++, i++) {
        if (*p == '\n' || *p == '\r') {
            *p = ' ';
        }
    }

    limit = (0x38 - strlen(charsetName)) / 3;
    NWC24iDetectBreakPoint(&pos, charset, work, srcLen, limit);
    result = NWC24EncodeWord(buf2, cap, &encLen, charsetName,
                             NWC24i_CHARSET_WORK_SIZE, 'Q', work, pos);
    if (result != NWC24_OK) {
        return result;
    }

    srcPos = pos;
    if (srcPos == srcLen) {
        return NWC24SetMsgSubject(msg, (const char*)buf2, encLen - 1);
    }

    limit = (0x40 - strlen(charsetName)) / 3;
    halfSize = cap;
    bufLen = encLen - 1;

    while (srcPos < srcLen) {
        if (halfSize - bufLen < 3) {
            return NWC24_ERR_OVERFLOW;
        }
        buf2[bufLen++] = '\r';
        buf2[bufLen++] = '\n';
        buf2[bufLen++] = ' ';

        NWC24iDetectBreakPoint(&pos, charset, work + srcPos,
                               srcLen - srcPos, limit);
        result = NWC24EncodeWord(buf2 + bufLen, halfSize - bufLen, &encLen,
                                 charsetName, NWC24i_CHARSET_WORK_SIZE, 'Q',
                                 work + srcPos, pos);
        if (result != NWC24_OK) {
            return result;
        }
        bufLen += encLen - 1;
        srcPos += pos;
    }

    return NWC24SetMsgSubject(msg, (const char*)buf2, bufLen);
}

static NWC24Err NWC24iSetMsgSubjectBase64(NWC24MsgObj* msg, const u16* subject,
                                        u32 subjectLen,
                                        NWC24EncodingRegion encRegion,
                                        u16 unk, u8* work, u32 workSize,
                                        u32 charset, char* charsetName) {
    u32 encLen;
    u32 srcLen;
    u32 convert;
    u32 halfSize;
    u32 cap;
    u8* buf2;
    u32 bufLen;
    u32 srcPos;
    u32 chunk;
    NWC24Err result;

    halfSize = workSize / 2;
    buf2 = work + halfSize;
    cap = workSize - halfSize;

    chunk = (0x36 - strlen(charsetName)) * 3 / 4;
    if (chunk > halfSize) {
        return NWC24_ERR_OVERFLOW;
    }

    srcLen = subjectLen;
    convert = chunk + 1;
    result = NWC24iConvertFromInternalEncoding(work, &convert, subject,
                                               (s32*)&srcLen, charsetName,
                                               NWC24i_CHARSET_WORK_SIZE,
                                               encRegion, unk);
    if (result != NWC24_OK && result != NWC24_ERR_OVERFLOW) {
        return result;
    }

    result = NWC24EncodeWord(buf2, cap, &encLen, charsetName,
                             NWC24i_CHARSET_WORK_SIZE, 'B', work, convert - 1);
    if (result != NWC24_OK) {
        return result;
    }

    srcPos = srcLen;
    if (srcPos == subjectLen) {
        return NWC24SetMsgSubject(msg, (const char*)buf2, encLen - 1);
    }

    chunk = (0x3e - strlen(charsetName)) * 3 / 4 + 1;
    bufLen = encLen - 1;

    while (srcPos < subjectLen) {
        if (cap - bufLen < 3) {
            return NWC24_ERR_OVERFLOW;
        }
        srcLen = subjectLen - srcPos;
        convert = chunk;
        buf2[bufLen++] = '\r';
        buf2[bufLen++] = '\n';
        buf2[bufLen++] = ' ';

        result = NWC24iConvertFromInternalEncoding(work, &convert,
                                                   subject + srcPos,
                                                   (s32*)&srcLen, charsetName,
                                                   NWC24i_CHARSET_WORK_SIZE,
                                                   encRegion, unk);
        if (result != NWC24_OK && result != NWC24_ERR_OVERFLOW) {
            return result;
        }

        result = NWC24EncodeWord(buf2 + bufLen, cap - bufLen, &encLen,
                                 charsetName, NWC24i_CHARSET_WORK_SIZE, 'B',
                                 work, convert - 1);
        if (result != NWC24_OK) {
            return result;
        }
        bufLen += encLen - 1;
        srcPos += srcLen;
    }

    return NWC24SetMsgSubject(msg, (const char*)buf2, bufLen);
}
