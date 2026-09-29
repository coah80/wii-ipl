#include <private/nwc24.h>
#include <revolution/nwc24.h>

static const char* MIMEEncStr =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

// Length of the alphabet portion of the encoding string.
// This does not include the padding character (=).
#define ALPHABET_LEN 64

#define MAX_OCTETS 4
#define DEFAULT_LINE_LEN 75

#define NWC24_BASE64_TABLE_SIZE 256

static NWC24Err Base64Encode(char* pData, s32 dataSize, u32* pDataRead,
                             char* pText, s32 textSize, u32* pTextWritten) {
    NWC24Err result = NWC24_OK;
    s32 textIdx;
    s32 dataIdx = 0;
    BOOL hasThird;
    BOOL hasSecond;
    u32 combined;

    for (textIdx = 0; dataIdx < dataSize; dataIdx += 3) {
        if (textIdx + 3 >= textSize) {
            result = NWC24_ERR_OVERFLOW;
            break;
        }

        hasThird = FALSE;
        hasSecond = FALSE;

        combined = (u8)pData[dataIdx];
        combined <<= 8;

        if (dataIdx + 1 < dataSize) {
            hasSecond = TRUE;
            combined |= (u8)pData[dataIdx + 1];
        }

        combined <<= 8;

        if (dataIdx + 2 < dataSize) {
            hasThird = TRUE;
            combined |= (u8)pData[dataIdx + 2];
        }

        // clang-format off
        pText[textIdx + 0] = MIMEEncStr[combined >> 18 & (ALPHABET_LEN - 1)];
        pText[textIdx + 1] = MIMEEncStr[combined >> 12 & (ALPHABET_LEN - 1)];
        pText[textIdx + 2] = MIMEEncStr[hasSecond ? (combined >> 6 & (ALPHABET_LEN - 1)) : ALPHABET_LEN];
        pText[textIdx + 3] = MIMEEncStr[hasThird  ? (combined & (ALPHABET_LEN - 1)) : ALPHABET_LEN];
        // clang-format on

        textIdx += 4;
    }

    *pTextWritten = textIdx;

    if (pDataRead != NULL) {
        textIdx = dataSize;

        if (dataSize < dataIdx) {
            dataIdx = dataSize;
        }

        *pDataRead = dataIdx;
    }

    return result;
}

NWC24Err NWC24Base64Encode(u8* decoded, int decodedSize, u8* encoded,
                           int encodedSize, u32* stringSize) {
    return Base64Encode((char*)decoded, decodedSize, NULL, (char*)encoded,
                        encodedSize, stringSize);
}

NWC24Err NWC24Base64Decode(u8* encoded, int encodedSize, u8* decoded,
                           int decodedSize, u32* stringSize) {
    s32 bits = 0;
    s32 acc = 0;
    u32 written = 0;
    u8* table = nwc24Work->base64Work;
    int i;

    for (i = 0; i < encodedSize; i++) {
        s32 value = (s8)table[encoded[i]];
        if (value < 0 || value >= 0x40) {
            continue;
        }

        bits += 6;
        acc <<= 6;
        acc |= value;

        if (bits >= 8) {
            if (written >= (u32)decodedSize) {
                *stringSize = decodedSize;
                return NWC24_ERR_OVERFLOW;
            }

            bits -= 8;
            written++;
            *decoded++ = acc >> bits;
        }
    }

    *stringSize = written;
    return NWC24_OK;
}

void NWC24InitBase64Table(u8* table) {
    s8* pTable = (s8*)table;
    int i;
    for (i = 0; i < NWC24_BASE64_TABLE_SIZE; i++) {
        pTable[i] = 0xFF;
    }

    for (i = 'A'; i <= 'Z'; i++) {
        table[i] = 0 + i - 'A';
    }

    for (i = 'a'; i <= 'z'; i++) {
        table[i] = 26 + i - 'a';
    }

    for (i = '0'; i <= '9'; i++) {
        table[i] = 26 + 26 + i - '0';
    }

    table['+'] = 26 + 26 + 10;
    table['/'] = 26 + 26 + 10 + 1;
}

static NWC24Err QEncode(u8* pText, u32 textSize, u32* pTextWritten, u8* pData,
                        u32 dataSize, u32* pDataRead, s32 maxLineLength) {
    u8* pWritePtr;
    u32 textWritten;
    u32 dataIdx;
    NWC24Err result;
    s32 lineLength;
    u8 octets[MAX_OCTETS];
    BOOL lineBreak;
    s32 emitCount;
    s32 bytesRead;
    s16 currentByte;
    s32 i;

    result = NWC24_OK;

    if (pText == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (pData == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (dataSize <= 0) {
        return NWC24_ERR_OVERFLOW;
    }

    if (pDataRead != NULL) {
        *pDataRead = 0;
    }

    if (pTextWritten != NULL) {
        *pTextWritten = 0;
    }

    pWritePtr = pText;
    lineLength = 0;
    textWritten = 0;
    dataIdx = 0;

    while (dataIdx < dataSize) {
        currentByte = *pData;
        lineBreak = FALSE;

        if ((char)currentByte >= '!' && (char)currentByte <= '~' &&
            (char)currentByte != '=') {

            bytesRead = 1;
            emitCount = 1;
            octets[0] = *pData;

        } else if (dataIdx + 1 < dataSize && (char)currentByte == '\r' &&
                   (char)pData[1] == '\n') {

            bytesRead = 2;
            emitCount = 1;
            octets[0] = *pData;
            octets[1] = pData[1];

        } else {
            octets[0] = '=';

            if ((*pData >> 4) >= 10) {
                octets[1] = (*pData >> 4) % 10 + 'A';
            } else {
                octets[1] = (*pData >> 4) % 10 + '0';
            }

            if ((*pData & 0x0F) >= 10) {
                octets[2] = (*pData & 0x0F) % 10 + 'A';
            } else {
                octets[2] = (*pData & 0x0F) % 10 + '0';
            }

            bytesRead = 1;
            emitCount = 3;
        }

        if (maxLineLength == 0 && lineLength + emitCount >= DEFAULT_LINE_LEN) {
            lineBreak = TRUE;
            emitCount += 3;
        }

        if (textWritten + emitCount >= textSize) {
            result = NWC24_ERR_OVERFLOW;
            break;
        }

        textWritten += emitCount;

        if (lineBreak) {
            pWritePtr[0] = '=';
            pWritePtr[1] = '\r';
            pWritePtr[2] = '\n';

            pWritePtr += 3;
            emitCount -= 3;

            lineLength = 0;
        }

        lineLength += emitCount;

        for (i = 0; i < emitCount; i++) {
            *(pWritePtr++) = octets[i];
        }

        dataIdx += bytesRead;
        pData += bytesRead;
    }

    if (pDataRead != NULL) {
        *pDataRead = dataIdx;
    }

    if (pTextWritten != NULL) {
        *pTextWritten = textWritten;
    }

    return result;
}

static NWC24Err QDecode(u8* pText, u32 textSize, u32* pTextWritten, u8* pData,
                        u32 dataSize, u32* pDataRead, s32 foldUnderscore) {
    u32 dataIdx;
    u32 textWritten;
    u8 byte;
    u8* pRead;
    u8* pWrite;
    NWC24Err result;
    BOOL valid;

    textWritten = 0;
    byte = 0;
    result = NWC24_OK;

    if (pText == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (pData == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (textSize <= 0) {
        return NWC24_ERR_OVERFLOW;
    }

    if (pTextWritten != NULL) {
        *pTextWritten = 0;
    }

    if (pDataRead != NULL) {
        *pDataRead = 0;
    }

    pRead = pData;
    pWrite = pText;
    dataIdx = 0;

    while (dataIdx < dataSize) {
        if (textWritten >= textSize) {
            result = NWC24_ERR_OVERFLOW;
            break;
        }

        if (foldUnderscore != 0 && (char)*pRead == '_') {
            *pWrite++ = ' ';
            pRead++;
            textWritten++;
        } else if ((char)*pRead == '=' && dataIdx + 2 < dataSize) {
            u8* s;
            u32 skip;

            valid = TRUE;
            pRead++;
            dataIdx++;

            if ((char)*pRead == ' ' || (char)*pRead == '\t') {
                s = pRead + 1;
                skip = 1;

                while (dataIdx + skip + 1 < dataSize) {
                    u8 c = *s;

                    if ((char)c == '\r' && (char)s[1] == '\n') {
                        pRead = s;
                        dataIdx += skip;
                        break;
                    } else if ((char)c == ' ' || (char)c == '\t') {
                        s++;
                        skip++;
                    } else {
                        break;
                    }
                }
            }

            if ((char)*pRead == '\r' && (char)pRead[1] == '\n') {
                pRead += 2;
                dataIdx++;
            } else {
                s32 upper = Util_xtoi((char)*pRead);
                if (upper >= 0) {
                    byte = upper << 4;
                }
                if (upper < 0) {
                    valid = FALSE;
                }

                {
                    s32 lower = Util_xtoi((char)pRead[1]);
                    if (lower >= 0) {
                        byte = (byte | (lower & 0xF)) & 0xFF;
                    }
                    if (lower < 0) {
                        valid = FALSE;
                    }
                }

                pRead += 2;

                if (valid) {
                    *pWrite++ = byte;
                    textWritten++;
                }
                dataIdx++;
            }
        } else {
            *pWrite++ = *pRead++;
            textWritten++;
        }

        dataIdx++;
    }

    if (pTextWritten != NULL) {
        *pTextWritten = textWritten;
    }

    if (pDataRead != NULL) {
        *pDataRead = dataIdx;
    }

    return result;
}

NWC24Err NWC24EncodeQuotedPrintable(char* encData, u32 encDataSize,
                                    u32* encodedSize, u8* decData,
                                    u32 decDataSize, u32* decodedSize) {
    return QEncode((u8*)encData, encDataSize, encodedSize, decData,
                   decDataSize, decodedSize, 0);
}

NWC24Err NWC24DecodeQuotedPrintable(char* decData, u32 decDataSize,
                                    u32* decodedSize, u8* encData,
                                    u32 encDataSize, u32* encodedSize) {
    return QDecode((u8*)decData, decDataSize, decodedSize, encData,
                   encDataSize, encodedSize, 0);
}

static NWC24Err ConcatEncodedText(u8* pText, u32 textSize, u32* pTextWritten,
                                  char encoding, u8* pData, u32 dataSize,
                                  u32* pDataRead);
static BOOL CopyWithoutLinearWhiteSpaces(u8* pText, u32* pTextSize,
                                         u8* pData, u32 dataSize);
static NWC24Err DecodeWord(u8* pCharset, u32 charsetSize, u8* pText,
                           u32 textSize, u32* pTextWritten, u8* pData,
                           u32 dataSize, u32* pDataRead);
static NWC24Err ExtractCharset(char* pCharset, u32 charsetSize,
                               u32* pCharsetLen, u8* pText, u32 textSize);
static NWC24Err ExtractEncodedText(u8* pText, u32 textSize, u32* pTextWritten,
                                   char encoding, u8* pData, u32 dataSize,
                                   u32* pDataRead);

static NWC24Err EncodeWord(u8* pText, u32 textSize, u32* pTextWritten,
                           char* charset, u32 charsetSize, char encoding,
                           u8* pData, u32 dataSize, u32* pNumWords) {
    NWC24Err err;
    BOOL incomplete = FALSE;
    char encBuf[1];

    if (pNumWords != NULL) {
        *pNumWords = 0;
    }

    if (textSize == 0) {
        if (pNumWords != NULL) {
            *pNumWords = 0;
        }
        return NWC24_ERR_INVALID_VALUE;
    }

    pText[0] = '\0';
    if (pTextWritten != NULL) {
        *pTextWritten = 1;
    }

    if (Mail_strlen((char*)pText) + 2 < textSize) {
        Mail_strncat((char*)pText, "=?", 2);
    } else {
        err = NWC24_ERR_OVERFLOW;
        goto check1;
    }
    err = NWC24_OK;
check1:
    if (err != NWC24_OK) {
        pText[0] = '\0';
        return err;
    }

    if (charset == NULL) {
        err = NWC24_ERR_INVALID_VALUE;
        goto check2;
    }
    if (Mail_strlen((char*)pText) + charsetSize < textSize) {
        Mail_strncat((char*)pText, charset, Mail_strlen(charset));
    } else {
        err = NWC24_ERR_OVERFLOW;
        goto check2;
    }
    err = NWC24_OK;
check2:
    if (err != NWC24_OK) {
        pText[0] = '\0';
        return err;
    }

    if (Mail_strlen((char*)pText) + 2 < textSize) {
        Mail_strncat((char*)pText, "?", 1);
    } else {
        err = NWC24_ERR_OVERFLOW;
        goto check3;
    }
    err = NWC24_OK;
check3:
    if (err != NWC24_OK) {
        pText[0] = '\0';
        return err;
    }

    encBuf[0] = encoding;
    if (encoding != 'B' && encoding != 'b' && encoding != 'Q' &&
        encoding != 'q') {
        err = NWC24_ERR_INVALID_VALUE;
        goto check4;
    }
    if (Mail_strlen((char*)pText) + 1 < textSize) {
        Mail_strncat((char*)pText, encBuf, 1);
    } else {
        err = NWC24_ERR_OVERFLOW;
        goto check4;
    }
    err = NWC24_OK;
check4:
    if (err != NWC24_OK) {
        pText[0] = '\0';
        return err;
    }

    if (Mail_strlen((char*)pText) + 2 < textSize) {
        Mail_strncat((char*)pText, "?", 1);
    } else {
        err = NWC24_ERR_OVERFLOW;
        goto check5;
    }
    err = NWC24_OK;
check5:
    if (err != NWC24_OK) {
        pText[0] = '\0';
        return err;
    }

    err = ConcatEncodedText(pText, textSize, pTextWritten, encoding, pData,
                            dataSize, pNumWords);
    if (err != NWC24_OK && err != NWC24_ERR_OVERFLOW) {
        pText[0] = '\0';
        *pNumWords = 1;
        return err;
    }
    if (err == NWC24_ERR_OVERFLOW) {
        incomplete = TRUE;
    }

    if (Mail_strlen((char*)pText) + 2 < textSize) {
        Mail_strncat((char*)pText, "?=", 2);
    } else {
        err = NWC24_ERR_OVERFLOW;
        goto check6;
    }
    err = NWC24_OK;
check6:
    if (err != NWC24_OK) {
        pText[0] = '\0';
        *pNumWords = 1;
        return err;
    }

    *pTextWritten = Mail_strlen((char*)pText) + 1;
    if (err == NWC24_OK && incomplete) {
        err = NWC24_ERR_OVERFLOW;
    }

    return err;
}

NWC24Err NWC24EncodeWord(u8* encData, u32 encDataSize, u32* encodedSize,
                         char* charset, u32 charsetSize, char encoding,
                         u8* decData, u32 decDataSize) {
    NWC24Err err;

    if (encodedSize == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (encData == NULL || encDataSize == 0) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (charset == NULL || charsetSize == 0) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if ((s8)encoding == 0) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (decData == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    encData[0] = '\0';
    *encodedSize = 1;

    err = EncodeWord(encData, encDataSize, encodedSize, charset, charsetSize,
                     encoding, decData, decDataSize, NULL);
    if (err == NWC24_OK || err == NWC24_ERR_OVERFLOW) {
        encData[*encodedSize - 1] = '\0';
    }

    return err;
}

static BOOL CopyWithoutLinearWhiteSpaces(u8* pText, u32* pTextSize,
                                         u8* pData, u32 dataSize) {
    u8 c;
    BOOL afterNewLine = FALSE;
    u32 textWritten = 0;
    u32 capacity;

    if (pText == NULL || pTextSize == NULL || *pTextSize == 0) {
        return FALSE;
    }

    if (pData == NULL) {
        pText[0] = '\0';
        *pTextSize = 1;
        return TRUE;
    }

    capacity = *pTextSize - 1;

    while (textWritten < capacity && dataSize > 0 &&
           (c = *pData, (char)c != '\0')) {
        switch ((char)c) {
        case '\r':
        case '\n':
            if (!afterNewLine) {
                *pText++ = ' ';
                textWritten++;
            }
            afterNewLine = TRUE;
            break;
        case ' ':
        case '\t':
            if (!afterNewLine) {
                *pText++ = c;
                textWritten++;
            }
            break;
        default:
            *pText++ = c;
            afterNewLine = FALSE;
            textWritten++;
            break;
        }

        pData++;
        dataSize--;
    }

    *pText = '\0';
    *pTextSize = textWritten + 1;

    return dataSize == 0 || (char)*pData == '\0';
}

static NWC24Err DecodeWord(u8* pCharset, u32 charsetSize, u8* pText,
                           u32 textSize, u32* pTextWritten, u8* pData,
                           u32 dataSize, u32* pDataRead) {
    u8* mark;
    u32 consumed;
    u32 copied;
    u32 textLen;
    u32 size;
    NWC24Err err;
    u32 i;
    u32 markLen;
    const char* markStr;
    const char* qStr;
    u8* charsetEnd;
    u32 remaining;
    u32 qLen;
    u8* found;
    char encoding;
    char c;
    BOOL allSpace;

    if (pDataRead != NULL) {
        *pDataRead = 0;
    }

    if (textSize == 0) {
        if (pDataRead != NULL) {
            *pDataRead = 0;
        }
        return NWC24_ERR_INVALID_VALUE;
    }

    pText[0] = '\0';
    if (pTextWritten != NULL) {
        *pTextWritten = 1;
    }
    if (pDataRead != NULL) {
        *pDataRead = 0;
    }

    markStr = "=?";
    markLen = Mail_strlen(markStr);
    mark = NULL;
    for (i = 0; i <= dataSize; i++) {
        mark = pData + i;
        if (Mail_strncmp((char*)mark, markStr, markLen) == 0) {
            break;
        }
    }

    if (mark == pData) {
        err = ExtractCharset((char*)pCharset, charsetSize, &copied, mark,
                             dataSize);
        if (err != NWC24_OK) {
            return err;
        }

        consumed = copied;
        qStr = "?";
        qLen = Mail_strlen(qStr);
        charsetEnd = mark + consumed;
        remaining = dataSize - consumed;

        for (i = 0; i <= remaining; i++) {
            if (Mail_strncmp((char*)(charsetEnd + i), qStr, qLen) == 0) {
                found = charsetEnd + i;
                goto found2;
            }
        }
        found = NULL;
found2:

        if (found == NULL) {
            err = NWC24_ERR_INVALID_VALUE;
        } else {
            encoding = (char)found[1];
            copied = 2;
            err = NWC24_OK;
        }
        if (err != NWC24_OK) {
            return err;
        }

        consumed += copied;
        err = ExtractEncodedText(pText, textSize, &textLen, encoding,
                                 mark + consumed, dataSize - consumed,
                                 &copied);
        if (err != NWC24_OK) {
            return err;
        }
        consumed += copied;
    } else {
        if (mark != NULL) {
            consumed = mark - pData;
        } else {
            consumed = STD_strnlen((char*)pData, dataSize);
        }

        size = textSize;
        if (!CopyWithoutLinearWhiteSpaces(pText, &size, pData, consumed)) {
            *pTextWritten = size;
            if (pDataRead != NULL) {
                *pDataRead = consumed;
            }
            return NWC24_ERR_OVERFLOW;
        }

        textLen = size;
        if (mark != NULL) {
            allSpace = TRUE;
            for (i = 0; i < textLen && (c = (char)pText[i]) != '\0'; i++) {
                if (c != ' ' && c != '\t' && c != '\r' && c != '\n') {
                    allSpace = FALSE;
                }
            }
            if (allSpace) {
                pText[0] = '\0';
                textLen = 1;
            }
        }
    }

    *pTextWritten = textLen;
    if (pDataRead != NULL) {
        *pDataRead = consumed;
    }

    return NWC24_OK;
}

NWC24Err NWC24DecodeMIMEHeaderFieldBody(u8* charsetData, u32 charsetDataSize,
                                        u8* decData, u32 decDataSize,
                                        u32* decodedSize, u8* encData,
                                        u32 encDataSize) {
    NWC24Err err = NWC24_OK;
    u8* pRead;
    s32 readLeft;
    u8* pWrite;
    s32 writeLeft;
    u32 decLen;
    u32 encLen;

    if (decodedSize == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (charsetData == NULL || charsetDataSize == 0) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (decData == NULL || decDataSize == 0) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (encData == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    decData[0] = '\0';
    pRead = encData;
    readLeft = encDataSize;
    pWrite = decData;
    charsetData[0] = '\0';
    writeLeft = decDataSize;
    *decodedSize = 1;

    while (readLeft > 0 && writeLeft > 0 && (char)*pRead != '\0') {
        decLen = 0;
        err = DecodeWord(charsetData, charsetDataSize, pWrite, writeLeft,
                         &decLen, pRead, readLeft, &encLen);

        if (decLen == 0) {
            break;
        }
        decLen--;
        pWrite += decLen;
        writeLeft -= decLen;
        *decodedSize += decLen;
        pRead += encLen;
        readLeft -= encLen;

        if (err != NWC24_OK) {
            break;
        }
    }

    if (err == NWC24_OK && readLeft > 0 && (char)*pRead != '\0') {
        err = NWC24_ERR_OVERFLOW;
    }

    decData[*decodedSize - 1] = '\0';
    return err;
}

static NWC24Err ConcatEncodedText(u8* pText, u32 textSize, u32* pTextWritten,
                                  char encoding, u8* pData, u32 dataSize,
                                  u32* pDataRead) {
    NWC24Err err;
    u32 curLen;
    s32 avail;

    curLen = Mail_strlen((char*)pText);
    avail = textSize - curLen - 2;

    err = NWC24_OK;
    if (avail > 0) {
        if (encoding == 'B' || encoding == 'b') {
            err = Base64Encode((char*)pData, dataSize, pDataRead,
                               (char*)pText + curLen, avail - 1, pTextWritten);
        } else if (encoding == 'Q' || encoding == 'q') {
            err = QEncode(pText + curLen, avail - 1, pTextWritten, pData,
                          dataSize, pDataRead, 1);
        } else {
            err = NWC24_ERR_NOT_SUPPORTED;
        }

        if (err == NWC24_OK || err == NWC24_ERR_OVERFLOW) {
            pText[curLen + *pTextWritten] = '\0';
            *pTextWritten += 1;
        }
    } else {
        err = NWC24_ERR_OVERFLOW;
    }

    return err;
}

static NWC24Err ExtractCharset(char* pCharset, u32 charsetSize,
                               u32* pCharsetLen, u8* pText, u32 textSize) {
    const char* markStr;
    const char* qStr;
    u8* mark;
    u8* q;
    u8* end;
    u32 markLen;
    u32 qLen;
    u32 i;
    u32 offset;
    u32 remaining;
    u32 charsetLen;

    if (pCharset == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    markStr = "=?";
    markLen = Mail_strlen(markStr);
    for (i = 0; i <= textSize; i++) {
        mark = pText + i;
        if (Mail_strncmp((char*)mark, markStr, markLen) == 0) {
            goto found;
        }
    }
    mark = NULL;
found:
    if (mark == NULL) {
        return NWC24_ERR_NOT_SUPPORTED;
    }

    qStr = "?";
    qLen = Mail_strlen(qStr);
    q = mark + 2;
    offset = q - pText;
    remaining = textSize - offset;
    for (i = 0; i <= remaining; i++, q++) {
        if (Mail_strncmp((char*)q, qStr, qLen) == 0) {
            end = mark + i + 2;
            goto found2;
        }
    }
    end = NULL;
found2:
    if (end == NULL) {
        return NWC24_ERR_NOT_SUPPORTED;
    }

    charsetLen = end - (mark + 2);
    if (charsetLen >= charsetSize) {
        return NWC24_ERR_OVERFLOW;
    }
    Mail_strncpy(pCharset, (char*)(mark + 2), charsetLen);
    pCharset[charsetLen] = '\0';
    *pCharsetLen = charsetLen + 2;

    return NWC24_OK;
}


static NWC24Err ExtractEncodedText(u8* pText, u32 textSize, u32* pTextWritten,
                                   char encoding, u8* pData, u32 dataSize,
                                   u32* pDataRead) {
    u8* mark;
    u8* end;
    u32 markLen;
    u32 textLen;
    u32 i;
    NWC24Err err;

    if (pData == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (pTextWritten == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    *pTextWritten = 0;

    if (pDataRead == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    *pDataRead = 0;

    markLen = Mail_strlen("?");
    for (i = 0, mark = NULL; i <= dataSize; i++) {
        u8* p = pData + i;
        if (Mail_strncmp((char*)p, "?", markLen) == 0) {
            mark = p;
            break;
        }
    }

    if (mark == NULL) {
        return NWC24_ERR_NOT_SUPPORTED;
    }

    {
        u32 endLen = Mail_strlen("?=");
        u32 remaining = dataSize - (mark + 1 - pData);

        for (i = 0, end = NULL; i <= remaining; i++) {
            if (Mail_strncmp((char*)(mark + i + 1), "?=", endLen) == 0) {
                end = mark + i + 1;
                break;
            }
        }
    }

    if (end == NULL) {
        return NWC24_ERR_NOT_SUPPORTED;
    }

    textLen = end - (mark + 1);

    if (encoding == 'B' || encoding == 'b') {
        err = NWC24Base64Decode(mark + 1, textLen, pText, textSize - 1,
                                pTextWritten);
        if (err == NWC24_OK || err == NWC24_ERR_OVERFLOW) {
            pText[*pTextWritten] = '\0';
            *pTextWritten += 1;
        }
    } else if (encoding == 'Q' || encoding == 'q') {
        err = QDecode(pText, textSize - 1, pTextWritten, mark + 1, textLen,
                      NULL, 1);
        if (err == NWC24_OK || err == NWC24_ERR_OVERFLOW) {
            pText[*pTextWritten] = '\0';
            *pTextWritten += 1;
        }
    } else {
        return NWC24_ERR_NOT_SUPPORTED;
    }

    if (end != NULL) {
        *pDataRead = (end - pData) + 2;
    }

    return err;
}
