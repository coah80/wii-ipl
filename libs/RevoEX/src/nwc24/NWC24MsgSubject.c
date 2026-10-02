#define NWC24_MSG_SUBJECT
#include <private/enc.h>
#include <private/nwc24.h>
#include <revolution/enc.h>
#include <revolution/nwc24.h>

#include <string.h>

static char CharsetUsAscii[] = "us-ascii";
static char CharsetIso2022Jp[] = "iso-2022-jp";
static char CharsetUtf8[] = "utf-8";
static char CharsetEucKr[] = "euc-kr";
static char CharsetGb2312[] = "gb2312";
static const char* JapaneseCharsets[] = {CharsetUsAscii, CharsetIso2022Jp, CharsetUtf8};
static const char* ChineseCharsets[] = {CharsetUsAscii, CharsetGb2312};
static char CharsetIso88591[] = "iso-8859-1";
static char CharsetWindows1252[] = "windows-1252";
static char CharsetIso88592[] = "iso-8859-2";
static char CharsetIso88597[] = "iso-8859-7";
static char CharsetIso885910[] = "iso-8859-10";
char CharsetIso88593[] = "iso-8859-3";
static const char* WesternCharsets[] = {CharsetUsAscii,  CharsetIso88591,  CharsetWindows1252, CharsetIso88592,
                                        CharsetIso88597, CharsetIso885910, CharsetIso88593,    CharsetUtf8};
static const char* KoreanCharsets[] = {CharsetUsAscii, CharsetEucKr, CharsetUtf8};
static char DefaultCharsetJp[] = "iso-2022-jp";
static char DefaultCharsetKr[] = "euc-kr";

NWC24Err NWC24iGetDefaultCharset(char* charset, u32 charsetSize, NWC24EncodingRegion region);
NWC24Err NWC24iConvertToInternalEncoding(u16* dst, u32* dstSize, const u8* src, u32* srcSize, char* charset, u32 charsetSize,
                                         NWC24EncodingRegion region, u16 alternative);
NWC24Err NWC24iConvertFromInternalEncoding(u8* dst, u32* dstSize, const u16* src, u32* srcSize, char* charset, u32 charsetSize,
                                           NWC24EncodingRegion region, u16 alternative);
NWC24Err NWC24iDetectEncodingToSend(char* charset, u32 charsetSize, const u16* subject, u32 subjectSize, const u16* text, u32 textSize,
                                    NWC24EncodingRegion region);
NWC24Err NWC24iDetectBreakPoint(u32* breakPoint, NWC24Charset charset, const u8* text, u32 textSize, u32 maxSize);
NWC24Err NWC24iSetMsgSubjectPlain(NWC24MsgObj* msg, const u16* subject, u32 subjectSize, NWC24EncodingRegion region, u16 alternative, u8* work,
                                  u32 workSize, NWC24Charset charset, char* charsetName);
NWC24Err NWC24iSetMsgSubjectQP(NWC24MsgObj* msg, const u16* subject, u32 subjectSize, NWC24EncodingRegion region, u16 alternative, u8* work,
                               u32 workSize, NWC24Charset charset, char* charsetName);
NWC24Err NWC24iSetMsgSubjectBase64(NWC24MsgObj* msg, const u16* subject, u32 subjectSize, NWC24EncodingRegion region, u16 alternative, u8* work,
                                   u32 workSize, NWC24Charset charset, char* charsetName);

NWC24Err NWC24ReadMsgSubjectPublic(const NWC24MsgObj* msg, u16* subject, u32* subjectSize, NWC24EncodingRegion region, u16 alternative, u8* work,
                                   u32 workSize) {
    BOOL truncated;
    u8* decodedData;
    u32 decodedCapacity;
    u32 originalSize;
    u32 subjectDataSize;
    u32 workHalf;
    u32 decodedSize;
    char* charsetBuffer;
    NWC24Err result;
    u32 i;

    if (subjectSize == NULL) {
        result = NWC24_ERR_INVALID_VALUE;
    } else {
        originalSize = *subjectSize;
        *subjectSize = 0;
        truncated = FALSE;
        if (work == NULL) {
            result = NWC24_ERR_INVALID_VALUE;
        } else {
            workHalf = workSize >> 1;
            decodedData = work + workHalf;
            decodedCapacity = workSize - workHalf;
            result = NWC24GetMsgSubjectSize(msg, &subjectDataSize);
            switch (result) {
                case NWC24_OK:
                    if (subjectDataSize > workHalf) {
                        subjectDataSize = workHalf;
                        truncated = TRUE;
                    }
                    result = NWC24ReadMsgSubject(msg, (char*)work, subjectDataSize);
                    if (result != NWC24_OK) {
                        if (result == NWC24_ERR_OVERFLOW) {
                            truncated = TRUE;
                        } else {
                            goto done;
                        }
                    }
                    charsetBuffer = NWC24WorkP->stringWork;
                    result =
                        NWC24DecodeMIMEHeaderFieldBody((u8*)charsetBuffer, 0x40, decodedData, decodedCapacity, &decodedSize, work, subjectDataSize);
                    if (result != NWC24_OK) {
                        if (result == NWC24_ERR_OVERFLOW) {
                            truncated = TRUE;
                        } else {
                            goto done;
                        }
                    }
                    *subjectSize = originalSize;
                    result =
                        NWC24iConvertToInternalEncoding(subject, subjectSize, decodedData, &decodedSize, charsetBuffer, 0x40, region, alternative);
                    if ((result == NWC24_OK) || (result == NWC24_ERR_OVERFLOW)) {
                        for (i = 0; (i < *subjectSize) && (subject[i] != 0); i++) {
                            if ((subject[i] == 0x0D) || (subject[i] == 0x0A)) {
                                subject[i] = 0x20;
                            }
                        }
                        if ((result == NWC24_OK) && truncated) {
                            result = NWC24_ERR_OVERFLOW;
                        }
                    }
                    break;
                default:
                    goto done;
            }
        }
    }

done:
    return result;
}

NWC24Err NWC24ReadMsgTextPublic(const NWC24MsgObj* msg, u16* text, u32* textSize, NWC24EncodingRegion region, u16 alternative, u8* work,
                                u32 workSize) {
    char* charsetBuffer;
    BOOL truncated;
    u32 originalSize;
    u32 textDataSize;
    NWC24Err result;

    if (textSize == NULL) {
        result = NWC24_ERR_INVALID_VALUE;
    } else {
        originalSize = *textSize;
        *textSize = 0;
        truncated = FALSE;
        if (work == NULL) {
            result = NWC24_ERR_INVALID_VALUE;
        } else {
            result = NWC24GetMsgTextSize(msg, &textDataSize);
            switch (result) {
                case NWC24_OK:
                    if (textDataSize > workSize) {
                        textDataSize = workSize;
                        truncated = TRUE;
                    }
                    charsetBuffer = NWC24WorkP->stringWork + 0x20;
                    result = NWC24ReadMsgTextEx(msg, (char*)work, textDataSize, charsetBuffer, 0x40);
                    if (result != NWC24_OK) {
                        if (result != NWC24_ERR_OVERFLOW) {
                            goto done;
                        }
                        truncated = TRUE;
                    }

                    *textSize = originalSize;
                    result = NWC24iConvertToInternalEncoding(text, textSize, work, &textDataSize, charsetBuffer, 0x40, region, alternative);
                    if ((result == NWC24_OK) && truncated) {
                        result = NWC24_ERR_OVERFLOW;
                    }
                    break;
                default:
                    goto done;
            }
        }
    }

done:
    return result;
}

NWC24Err NWC24SetMsgSubjectPublic(NWC24MsgObj* msg, const u16* subject, u32 subjectSize, NWC24EncodingRegion region, u16 alternative, u8* work,
                                  u32 workSize) {
    NWC24MsgObjPrivate* privateMsg = (NWC24MsgObjPrivate*)msg;
    NWC24Work* nwcWork;
    NWC24Charset charset;
    NWC24Err result;

    if (((privateMsg->type & 0x100) == 0) || ((privateMsg->type & 0x200) != 0)) {
        result = NWC24_ERR_PROTECTED;
        goto done;
    }
    if ((subject == NULL) || (*subject == 0)) {
        result = NWC24_ERR_NULL;
        goto done;
    }
    if (subject[subjectSize] != 0) {
        result = NWC24_ERR_STRING_END;
        goto done;
    }
    if (work == NULL) {
        result = NWC24_ERR_INVALID_VALUE;
        goto done;
    }

    nwcWork = NWC24WorkP;
    result = NWC24iDetectEncodingToSend(nwcWork->stringWork, 0x40, subject, subjectSize, NULL, 0, region);
    switch (result) {
        case NWC24_OK:
            break;
        default:
            goto done;
    }
    if (NWC24ParseCharsetStr(&charset, nwcWork->stringWork) != NWC24_OK) {
        charset = 0;
    }
    if (charset == 0) {
        result = NWC24iSetMsgSubjectPlain(msg, subject, subjectSize, region, alternative, work, workSize, charset, nwcWork->stringWork);
        goto done;
    }
    switch (region) {
        case 0:
            result = 2;
            break;
        case 1:
        case 2:
            result = 3;
            break;
        case 3:
        case 4:
            result = 2;
            break;
        default:
            result = 2;
            break;
    }
    if (result == 3) {
        result = NWC24iSetMsgSubjectQP(msg, subject, subjectSize, region, alternative, work, workSize, charset, nwcWork->stringWork);
    } else {
        result = NWC24iSetMsgSubjectBase64(msg, subject, subjectSize, region, alternative, work, workSize, charset, nwcWork->stringWork);
    }

done:
    return result;
}

NWC24Err NWC24SetMsgSubjectAndTextPublic(NWC24MsgObj* msg, const u16* subject, u32 subjectSize, const u16* text, u32 textSize,
                                         NWC24EncodingRegion region, u16 alternative, u8* work, u32 workSize) {
    NWC24MsgObjPrivate* privateMsg = (NWC24MsgObjPrivate*)msg;
    NWC24Work* nwcWork;
    u32 textSourceSize;
    u32 textWorkSize;
    BOOL is7Bit;
    NWC24Charset charset;
    u32 subjectWorkSize;
    u8* subjectWork;
    NWC24Err result;

    if (((privateMsg->type & 0x100) == 0) || ((privateMsg->type & 0x200) != 0)) {
        result = NWC24_ERR_PROTECTED;
        goto done;
    }
    if ((subject == NULL) || (*subject == 0)) {
        result = NWC24_ERR_NULL;
        goto done;
    }
    if ((text == NULL) || (textSize == 0)) {
        NWC24Data_Init(&privateMsg->text);
        result = NWC24SetMsgSubjectPublic(msg, subject, subjectSize, region, alternative, work, workSize);
        goto done;
    }
    if ((text[textSize] != 0) || (subject[subjectSize] != 0)) {
        result = NWC24_ERR_STRING_END;
        goto done;
    }
    if (work == NULL) {
        result = NWC24_ERR_INVALID_VALUE;
        goto done;
    }

    nwcWork = NWC24WorkP;
    result = NWC24iDetectEncodingToSend(nwcWork->stringWork, 0x40, subject, subjectSize, text, textSize, region);
    switch (result) {
        case NWC24_OK:
            break;
        default:
            goto done;
    }
    if (NWC24ParseCharsetStr(&charset, nwcWork->stringWork) != NWC24_OK) {
        charset = 0;
    }
    textWorkSize = (workSize * textSize) / (textSize + subjectSize * 4);
    subjectWorkSize = workSize - textWorkSize;
    subjectWork = work + textWorkSize;
    textSourceSize = textSize;
    result = NWC24iConvertFromInternalEncoding(work, &textWorkSize, text, &textSourceSize, nwcWork->stringWork, 0x40, region, alternative);
    switch (result) {
        case NWC24_OK:
            break;
        default:
            goto done;
    }

    result = ENCIs7BitEncoding(&is7Bit, nwcWork->stringWork);
    if (!is7Bit || (result != ENC_OK)) {
        switch (region) {
            case 0:
                result = 2;
                break;
            case 1:
            case 2:
                result = 3;
                break;
            case 3:
            case 4:
                result = 2;
                break;
            default:
                result = 2;
                break;
        }
    } else {
        result = 0;
    }
    result = NWC24SetMsgText(msg, (char*)work, textWorkSize - 1, charset, result);
    switch (result) {
        case NWC24_OK:
            break;
        default:
            goto done;
    }
    if (charset == 0) {
        result = NWC24iSetMsgSubjectPlain(msg, subject, subjectSize, region, alternative, subjectWork, subjectWorkSize, charset, nwcWork->stringWork);
        goto done;
    }
    switch (region) {
        case 0:
            result = 2;
            break;
        case 1:
        case 2:
            result = 3;
            break;
        case 3:
        case 4:
            result = 2;
            break;
        default:
            result = 2;
            break;
    }
    if (result == 3) {
        result = NWC24iSetMsgSubjectQP(msg, subject, subjectSize, region, alternative, subjectWork, subjectWorkSize, charset, nwcWork->stringWork);
    } else {
        result =
            NWC24iSetMsgSubjectBase64(msg, subject, subjectSize, region, alternative, subjectWork, subjectWorkSize, charset, nwcWork->stringWork);
    }

done:
    return result;
}

NWC24Err NWC24iGetDefaultCharset(char* charset, u32 charsetSize, NWC24EncodingRegion region) {
    NWC24Err result = NWC24_OK;

    switch (region) {
        case 0:
            strncpy(charset, DefaultCharsetJp, charsetSize - 1);
            charset[charsetSize - 1] = 0;
            goto done;
        case 1:
            strncpy(charset, "iso-8859-1", charsetSize - 1);
            charset[charsetSize - 1] = 0;
            goto done;
        case 2:
            strncpy(charset, "iso-8859-1", charsetSize - 1);
            charset[charsetSize - 1] = 0;
            goto done;
        case 3:
            strncpy(charset, DefaultCharsetKr, charsetSize - 1);
            charset[charsetSize - 1] = 0;
            goto done;
        case 4:
            strncpy(charset, "gb2312", charsetSize - 1);
            charset[charsetSize - 1] = 0;
            goto done;
        default:
            strncpy(charset, "iso-8859-1", charsetSize - 1);
            charset[charsetSize - 1] = 0;
            result = NWC24_ERR_INVALID_VALUE;
    }

done:
    return result;
}

NWC24Err NWC24iConvertToInternalEncoding(u16* dst, u32* dstSize, const u8* src, u32* srcSize, char* charset, u32 charsetSize,
                                         NWC24EncodingRegion region, u16 alternative) {
    ENCContext context;
    u32 dstBytes;
    u32 convertedBytes;
    NWC24Err result;

    dstBytes = *dstSize * 2;
    *dstSize = 0;
    if (dstBytes < 2) {
        result = NWC24_ERR_OVERFLOW;
        goto done;
    }
    if (charset[0] == '\0') {
        result = NWC24iGetDefaultCharset(charset, charsetSize, region);
        switch (result) {
            case NWC24_OK:
                break;
            default:
                goto done;
        }
    }
    result = ENCInitContext(&context);
    if ((result == ENC_OK) && ((result = ENCSetExternalEncoding(&context, charset)) == ENC_OK) &&
        ((result = ENCSetBreakType(&context, ENC_BR_LF)) == ENC_OK) &&
        ((alternative == 0) || ((result = ENCSetAlternativeCharacter(&context, alternative, alternative)) == ENC_OK))) {
        convertedBytes = dstBytes - 2;
        result = ENCConvertToInternalEncoding(&context, dst, (s32*)&convertedBytes, src, (s32*)srcSize);
        dst[convertedBytes >> 1] = 0;
        *dstSize = (convertedBytes >> 1) + 1;
    }
    if (result == ENC_ERR_NO_MAP_RULE) {
        goto invalidCharacter;
    }
    if (result < ENC_ERR_NO_MAP_RULE) {
        if (result == ENC_ERR_INVALID_FORMAT) {
            goto invalidCharacter;
        }
        if (result >= ENC_ERR_INVALID_FORMAT) {
            goto invalidValue;
        }
        if (result >= ENC_ERR_NOT_LOADED) {
            goto notSupported;
        }
    } else {
        if (result == ENC_OK) {
            goto success;
        }
        if (result >= ENC_OK) {
            goto fatal;
        }
        goto overflow;
    }
    goto fatal;

success:
    result = ENC_OK;
    goto done;

invalidValue:
    result = NWC24_ERR_INVALID_VALUE;
    goto done;

overflow:
    result = NWC24_ERR_OVERFLOW;
    goto done;

invalidCharacter:
    result = NWC24_ERR_INVALID_CHAR;
    goto done;

notSupported:
    result = NWC24_ERR_NOT_SUPPORTED;
    goto done;

fatal:
    result = NWC24_ERR_FATAL;

done:
    return result;
}

NWC24Err NWC24iConvertFromInternalEncoding(u8* dst, u32* dstSize, const u16* src, u32* srcSize, char* charset, u32 charsetSize,
                                           NWC24EncodingRegion region, u16 alternative) {
    ENCContext context;
    u32 outputCapacity;
    u32 outputBytes;
    u32 inputBytes;
    NWC24Err result;

    outputCapacity = *dstSize;
    *dstSize = 0;
    if (outputCapacity < 1) {
        result = NWC24_ERR_OVERFLOW;
        goto done;
    }
    if (charset[0] == '\0') {
        result = NWC24iGetDefaultCharset(charset, charsetSize, region);
        switch (result) {
            case NWC24_OK:
                break;
            default:
                goto done;
        }
    }
    result = ENCInitContext(&context);
    if ((result == ENC_OK) && ((result = ENCSetExternalEncoding(&context, charset)) == ENC_OK) &&
        ((result = ENCSetBreakType(&context, ENC_BR_CRLF)) == ENC_OK) &&
        ((alternative == 0) || ((result = ENCSetAlternativeCharacter(&context, alternative, alternative)) == ENC_OK))) {
        outputBytes = outputCapacity - 1;
        inputBytes = *srcSize << 1;
        result = ENCConvertFromInternalEncoding(&context, dst, (s32*)&outputBytes, src, (s32*)&inputBytes);
        dst[outputBytes] = 0;
        *srcSize = inputBytes >> 1;
        *dstSize = outputBytes + 1;
    }
    if (result == ENC_ERR_NO_MAP_RULE) {
        goto invalidCharacter;
    }
    if (result < ENC_ERR_NO_MAP_RULE) {
        if (result == ENC_ERR_INVALID_FORMAT) {
            goto invalidCharacter;
        }
        if (result >= ENC_ERR_INVALID_FORMAT) {
            goto invalidValue;
        }
        if (result >= ENC_ERR_NOT_LOADED) {
            goto notSupported;
        }
        goto fatal;
    }
    if (result == ENC_OK) {
        goto success;
    }
    if (result >= ENC_OK) {
        goto fatal;
    }
    goto overflow;

success:
    result = ENC_OK;
    goto done;

invalidValue:
    result = NWC24_ERR_INVALID_VALUE;
    goto done;

overflow:
    result = NWC24_ERR_OVERFLOW;
    goto done;

invalidCharacter:
    result = NWC24_ERR_INVALID_CHAR;
    goto done;

notSupported:
    result = NWC24_ERR_NOT_SUPPORTED;
    goto done;

fatal:
    result = NWC24_ERR_FATAL;

done:
    return result;
}

NWC24Err NWC24iDetectEncodingToSend(char* charset, u32 charsetSize, const u16* subject, u32 subjectSize, const u16* text, u32 textSize,
                                    NWC24EncodingRegion region) {
    int endIndex;
    u32 subjectBytes;
    u32 textBytes;
    int startIndex;
    int lastIndex;
    int index;
    const char** names;
    int numNames;
    int result;

    index = 0;
    startIndex = 0;
    lastIndex = -1;
    switch (region) {
        case 0:
            names = JapaneseCharsets;
            numNames = 3;
            break;
        case 1:
        case 2:
            names = WesternCharsets;
            numNames = 8;
            break;
        case 3:
            names = KoreanCharsets;
            numNames = 3;
            break;
        case 4:
            names = ChineseCharsets;
            numNames = 2;
            break;
        default:
            names = WesternCharsets;
            numNames = 8;
            break;
    }
    subjectBytes = subjectSize << 1;
    textBytes = textSize << 1;
    endIndex = numNames - 1;
    while (index < endIndex) {
        result = ENCCheckEncoding(&index, names + startIndex, endIndex - startIndex, subject, subjectBytes);
        if (result != ENC_OK) {
            return NWC24_ERR_NOT_SUPPORTED;
        }
        if (index == ENC_CHECK_ENCODING_NOT_FOUND) {
            index = numNames - 1;
            break;
        }
        startIndex += index;
        if ((text == NULL) || (lastIndex == startIndex)) {
            index = startIndex;
            break;
        }
        result = ENCCheckEncoding(&index, names + startIndex, endIndex - startIndex, text, textBytes);
        if (result != ENC_OK) {
            return NWC24_ERR_NOT_SUPPORTED;
        }
        if (index == ENC_CHECK_ENCODING_NOT_FOUND) {
            index = numNames - 1;
            break;
        }
        lastIndex = startIndex + index;
        if (lastIndex == startIndex) {
            index = lastIndex;
            break;
        }
        startIndex = lastIndex;
    }
    strncpy(charset, names[index], charsetSize - 1);
    charset[charsetSize - 1] = '\0';
    return NWC24_OK;
}

NWC24Err NWC24iDetectBreakPoint(u32* breakPoint, NWC24Charset charset, const u8* text, u32 textSize, u32 maxSize) {
    const u8* ptr;
    BOOL byteEncoding;
    u32 i;
    u32 lastBreak;

    i = 0;
    lastBreak = 0;
    if ((breakPoint == NULL) || (text == NULL)) {
        return NWC24_ERR_INVALID_VALUE;
    }
    if (charset == 0) {
        byteEncoding = TRUE;
    } else if (charset == NWC24_UTF_8) {
        byteEncoding = FALSE;
    } else if (((charset & 0xFFFF0000) == 0x00080000) || (charset == NWC24_WINDOWS_1252)) {
        byteEncoding = TRUE;
    } else {
        return NWC24_ERR_NOT_SUPPORTED;
    }
    if (textSize <= maxSize) {
        *breakPoint = textSize;
        return NWC24_OK;
    }
    ptr = text;
    while ((i < maxSize) && (*text != 0)) {
        if (*ptr == 0x20) {
            lastBreak = i;
        }
        i++;
        ptr++;
    }
    if (lastBreak != 0) {
        *breakPoint = lastBreak;
        return NWC24_OK;
    }
    if (byteEncoding) {
        *breakPoint = maxSize;
        return NWC24_OK;
    }
    {
        u32 utf8Index = 0;
        ptr = text;
        while (utf8Index < maxSize && *text != 0) {
            if (((u32)*ptr & 0xC0) != 0x80U)
                lastBreak = utf8Index;
            utf8Index++;
            ptr++;
        }
    }
    *breakPoint = lastBreak;
    return NWC24_OK;
}

NWC24Err NWC24iSetMsgSubjectPlain(NWC24MsgObj* msg, const u16* subject, u32 subjectSize, NWC24EncodingRegion region, u16 alternative, u8* work,
                                  u32 workSize, NWC24Charset charset, char* charsetName) {
    u32 workHalf;
    u32 secondSize;
    u32 sourceOffset;
    u8* second;
    u32 subjectLength;
    u32 lineLength;
    s32 copied;
    u32 i;
    NWC24Err result;

    secondSize = workSize - (workSize >> 1);
    second = work + (workSize >> 1);
    subjectLength = subjectSize;
    lineLength = 0;
    workHalf = workSize >> 1;
    result = NWC24iConvertFromInternalEncoding(work, &workHalf, subject, &subjectLength, charsetName, 0x40, region, alternative);
    switch (result) {
        default:
            goto done;
        case NWC24_OK:
            subjectLength = workHalf - 1;
            for (i = 0; i < workHalf; i++) {
                if ((work[i] == '\n') || (work[i] == '\r')) {
                    work[i] = ' ';
                }
            }
            NWC24iDetectBreakPoint(&lineLength, charset, work, subjectLength, 0x3F);
            if (lineLength == subjectLength) {
                result = NWC24SetMsgSubject(msg, (char*)work, subjectLength);
            } else {
                workHalf = secondSize;
                sourceOffset = lineLength;
                if (workHalf <= sourceOffset) {
                    result = NWC24_ERR_OVERFLOW;
                    goto done;
                }
                copied = NWC24iStrLCpy((char*)second, (char*)work, lineLength + 1);
                for (; sourceOffset < subjectLength; sourceOffset += lineLength) {
                    if (workHalf - copied < 3) {
                        result = NWC24_ERR_OVERFLOW;
                        goto done;
                    }
                    second[copied++] = '\r';
                    second[copied++] = '\n';
                    if (work[sourceOffset] != ' ') {
                        second[copied] = ' ';
                        copied++;
                    }
                    NWC24iDetectBreakPoint(&lineLength, charset, work + sourceOffset, subjectLength - sourceOffset, 0x47);
                    if (workHalf - copied <= lineLength) {
                        result = NWC24_ERR_OVERFLOW;
                        goto done;
                    }
                    copied += NWC24iStrLCpy((char*)second + copied, (char*)work + sourceOffset, lineLength + 1);
                }
                second[copied] = 0;
                result = NWC24SetMsgSubject(msg, (char*)second, copied);
            }
    }

done:
    return result;
}

NWC24Err NWC24iSetMsgSubjectQP(NWC24MsgObj* msg, const u16* subject, u32 subjectSize, NWC24EncodingRegion region, u16 alternative, u8* work,
                               u32 workSize, NWC24Charset charset, char* charsetName) {
    u32 workHalf;
    u32 sourceOffset;
    u32 secondSize;
    u8* second;
    u32 subjectLength;
    u32 lineLength;
    u32 outputLength;
    u32 total;
    u32 combinedLength;
    u32 i;
    u32 charsetLength;
    NWC24Err result;

    secondSize = workSize - (workSize >> 1);
    second = work + (workSize >> 1);
    subjectLength = subjectSize;
    lineLength = 0;
    workHalf = workSize >> 1;
    result = NWC24iConvertFromInternalEncoding(work, &workHalf, subject, &subjectLength, charsetName, 0x40, region, alternative);
    switch (result) {
        default:
            goto done;
        case NWC24_OK:
            subjectLength = workHalf - 1;
            for (i = 0; i < workHalf; i++) {
                if ((work[i] == '\n') || (work[i] == '\r')) {
                    work[i] = ' ';
                }
            }
            charsetLength = strlen(charsetName);
            NWC24iDetectBreakPoint(&lineLength, charset, work, subjectLength, (0x38 - charsetLength) / 3);
            result = NWC24EncodeWord(second, secondSize, &outputLength, charsetName, 0x40, 'Q', work, lineLength);
            switch (result) {
                default:
                    goto done;
                case NWC24_OK:
                    sourceOffset = lineLength;
                    if (lineLength == subjectLength) {
                        result = NWC24SetMsgSubject(msg, (char*)second, outputLength - 1);
                    } else {
                        charsetLength = (0x40 - strlen(charsetName)) / 3;
                        total = outputLength - 1;
                        workHalf = secondSize;
                        for (; sourceOffset < subjectLength;) {
                            if (workHalf - total < 3) {
                                result = NWC24_ERR_OVERFLOW;
                                goto done;
                            }
                            second[total++] = '\r';
                            second[total++] = '\n';
                            second[total++] = ' ';
                            NWC24iDetectBreakPoint(&lineLength, charset, work + sourceOffset, subjectLength - sourceOffset, charsetLength);
                            result = NWC24EncodeWord(second + total, workHalf - total, &outputLength, charsetName, 0x40, 'Q', work + sourceOffset,
                                                     lineLength);
                            switch (result) {
                                case NWC24_OK:
                                    break;
                                default:
                                    goto done;
                            }
                            combinedLength = total + outputLength;
                            sourceOffset += lineLength;
                            total = combinedLength - 1;
                        }
                        result = NWC24SetMsgSubject(msg, (char*)second, total);
                    }
            }
    }

done:
    return result;
}

NWC24Err NWC24iSetMsgSubjectBase64(NWC24MsgObj* msg, const u16* subject, u32 subjectSize, NWC24EncodingRegion region, u16 alternative, u8* work,
                                   u32 workSize, NWC24Charset charset, char* charsetName) {
    u32 workHalf;
    u32 secondSize;
    u8* second;
    u32 subjectLength;
    u32 lineLength;
    u32 sourceOffset;
    u32 outputLength;
    u32 total;
    u32 charsetLength;
    NWC24Err result;

    workHalf = workSize >> 1;
    second = work + workHalf;
    secondSize = workSize - workHalf;
    charsetLength = strlen(charsetName);
    lineLength = ((0x36 - charsetLength) * 3) >> 2;
    if (lineLength > workHalf) {
        result = NWC24_ERR_OVERFLOW;
    } else {
        workHalf = lineLength + 1;
        subjectLength = subjectSize;
        result = NWC24iConvertFromInternalEncoding(work, &workHalf, subject, &subjectLength, charsetName, 0x40, region, alternative);
        switch (result) { case NWC24_OK: case NWC24_ERR_OVERFLOW: break; default: goto done; }
        result = NWC24EncodeWord(second, secondSize, &outputLength, charsetName, 0x40, 'B', work, workHalf - 1);
        switch (result) { case NWC24_OK: break; default: goto done; }
        {
            sourceOffset = subjectLength;
            if (sourceOffset == subjectSize) {
                result = NWC24SetMsgSubject(msg, (char*)second, outputLength - 1);
            } else {
                charsetLength = strlen(charsetName);
                lineLength = (((0x3E - charsetLength) * 3) >> 2) + 1;
                total = outputLength - 1;
                for (; sourceOffset < subjectSize;) {
                    subjectLength = subjectSize - sourceOffset;
                    workHalf = lineLength;
                    if (secondSize - total < 3) {
                        result = NWC24_ERR_OVERFLOW;
                        goto done;
                    }
                    second[total++] = '\r';
                    second[total++] = '\n';
                    second[total++] = ' ';
                    result = NWC24iConvertFromInternalEncoding(work, &workHalf, subject + sourceOffset, &subjectLength, charsetName, 0x40, region,
                                                               alternative);
                    switch (result) { case NWC24_OK: case NWC24_ERR_OVERFLOW: break; default: goto done; }
                    result = NWC24EncodeWord(second + total, secondSize - total, &outputLength, charsetName, 0x40, 'B', work, workHalf - 1);
                    switch (result) { case NWC24_OK: break; default: goto done; }
                    sourceOffset += subjectLength;
                    total = total + outputLength - 1;
                }
                result = NWC24SetMsgSubject(msg, (char*)second, total);
            }
        }
    }

done:
    return result;
}
