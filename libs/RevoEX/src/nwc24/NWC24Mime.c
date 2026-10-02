#include <private/nwc24.h>
#include <revolution/nwc24.h>

static const char* MIMEEncStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

static NWC24Err Base64Encode(u8* decoded, int decodedSize, u32* stringSize, u8* encoded, int encodedSize, u32* encodedSizeOut) {
    NWC24Err result = NWC24_OK;
    s32 textIdx;
    s32 dataIdx = 0;
    BOOL hasThird;
    BOOL hasSecond;
    u32 combined;

    for (textIdx = 0; dataIdx < decodedSize; dataIdx += 3) {
        if (textIdx + 3 >= encodedSize) {
            result = NWC24_ERR_OVERFLOW;
            break;
        }

        hasThird = FALSE;
        hasSecond = FALSE;

        combined = (u32)decoded[dataIdx] << 8;

        if (dataIdx + 1 < decodedSize) {
            hasSecond = TRUE;
            combined |= (u8)decoded[dataIdx + 1];
        }

        combined <<= 8;

        if (dataIdx + 2 < decodedSize) {
            hasThird = TRUE;
            combined |= (u8)decoded[dataIdx + 2];
        }

        encoded[textIdx + 0] = MIMEEncStr[combined >> 18 & (64 - 1)];
        encoded[textIdx + 1] = MIMEEncStr[combined >> 12 & (64 - 1)];
        encoded[textIdx + 2] = MIMEEncStr[hasSecond ? (combined >> 6 & (64 - 1)) : 64];
        encoded[textIdx + 3] = MIMEEncStr[hasThird ? (combined & (64 - 1)) : 64];

        textIdx += 4;
    }

    *encodedSizeOut = textIdx;

    if (stringSize != NULL) {
        textIdx = decodedSize;

        if (decodedSize < dataIdx) {
            dataIdx = decodedSize;
        }

        *stringSize = dataIdx;
    }

    return result;
}

NWC24Err NWC24Base64Encode(u8* decoded, int decodedSize, u8* encoded, int encodedSize, u32* stringSize) {
    return Base64Encode(decoded, decodedSize, NULL, encoded, encodedSize, stringSize);
}

NWC24Err NWC24Base64Decode(u8* encoded, int encodedSize, u8* decoded, int decodedSize, u32* stringSize) {
    int bitCount = 0;
    u32 bitBuffer = 0;
    u32 decodedOffset = 0;
    s8* table = (s8*)NWC24WorkP->base64Work;
    BOOL produceOutput;
    int i;

    for (i = 0; i < encodedSize; i++) {
        if ((s32)table[encoded[i]] >= 0) {
            if ((s32)table[encoded[i]] < 0x40) {
                bitCount += 6;
                bitBuffer <<= 6;
                produceOutput = bitCount >= 8;
                bitBuffer |= (u32)table[encoded[i]];
                if (produceOutput) {
                    if (decodedOffset >= (u32)decodedSize) {
                        *stringSize = decodedSize;
                        return NWC24_ERR_OVERFLOW;
                    }
                    bitCount -= 8;
                    *decoded++ = (u8)((s32)bitBuffer >> bitCount);
                    decodedOffset++;
                }
            }
        }
    }
    *stringSize = decodedOffset;
    return NWC24_OK;
}

void NWC24InitBase64Table(u8* table) {
    s8* signedTable = (s8*)table;
    int i;

    for (i = 0; i < 256; i++) {
        signedTable[i] = -1;
    }
    for (i = 'A'; i <= 'Z'; i++) {
        table[i] = i - 'A';
    }
    for (i = 0; i < 26; i++) {
        table['a' + i] = i + 26;
    }
    for (i = 0; i < 10; i++) {
        table['0' + i] = i + 52;
    }
    table['+'] = 62;
    table['/'] = 63;
}

static NWC24Err QEncode(char* encoded, u32 encodedCapacity, u32* encodedSize, u8* decoded, u32 decodedSize, u32* decodedSizeOut, s32 maxLineLength) {
    char* output;
    u32 textWritten;
    u32 dataIdx;
    NWC24Err result;
    s32 lineLength;
    u8 octets[3];
    BOOL lineBreak;
    s32 emitCount;
    s32 bytesRead;
    s16 currentByte;
    s32 i;

    result = NWC24_OK;

    if (encoded == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (decoded == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (decodedSize <= 0) {
        return NWC24_ERR_OVERFLOW;
    }

    if (decodedSizeOut != NULL) {
        *decodedSizeOut = 0;
    }

    if (encodedSize != NULL) {
        *encodedSize = 0;
    }

    output = encoded;
    lineLength = 0;
    textWritten = 0;
    dataIdx = 0;

    while (dataIdx < decodedSize) {
        currentByte = *decoded;
        lineBreak = FALSE;

        if ((char)currentByte >= '!' && (char)currentByte <= '~' && (char)currentByte != '=') {
            bytesRead = 1;
            emitCount = 1;
            octets[0] = *decoded;

        } else if (dataIdx + 1 < decodedSize && (char)currentByte == '\r' && (char)decoded[1] == '\n') {
            bytesRead = 2;
            emitCount = 1;
            octets[0] = *decoded;
            octets[1] = decoded[1];

        } else {
            octets[0] = '=';

            if ((*decoded >> 4) >= 10) {
                octets[1] = (*decoded >> 4) % 10 + 'A';
            } else {
                octets[1] = (*decoded >> 4) % 10 + '0';
            }

            if ((*decoded & 0x0F) >= 10) {
                octets[2] = (*decoded & 0x0F) % 10 + 'A';
            } else {
                octets[2] = (*decoded & 0x0F) % 10 + '0';
            }

            bytesRead = 1;
            emitCount = 3;
        }

        if (maxLineLength == 0 && lineLength + emitCount >= 75) {
            lineBreak = TRUE;
            emitCount += 3;
        }

        if (textWritten + emitCount >= encodedCapacity) {
            result = NWC24_ERR_OVERFLOW;
            break;
        }

        textWritten += emitCount;

        if (lineBreak) {
            output[0] = '=';
            output[1] = '\r';
            output[2] = '\n';

            output += 3;
            emitCount -= 3;

            lineLength = 0;
        }

        lineLength += emitCount;

        for (i = 0; i < emitCount; i++) {
            *(output++) = octets[i];
        }

        dataIdx += bytesRead;
        decoded += bytesRead;
    }

    if (decodedSizeOut != NULL) {
        *decodedSizeOut = dataIdx;
    }

    if (encodedSize != NULL) {
        *encodedSize = textWritten;
    }

    return result;
}

static NWC24Err QDecode(char* decoded, u32 decodedCapacity, u32* decodedSize, char* encoded, u32 encodedSize, u32* encodedSizeOut, int flags) {
    u32 encodedOffset;
    u32 decodedOffset = 0;
    u8 value = 0;
    char* input;
    char* output;
    NWC24Err result = NWC24_OK;

    if (decoded == NULL)
        return NWC24_ERR_INVALID_VALUE;
    if (encoded == NULL)
        return NWC24_ERR_INVALID_VALUE;
    if (decodedCapacity == 0) {
        return NWC24_ERR_OVERFLOW;
    }
    if (decodedSize != NULL) {
        *decodedSize = 0;
    }
    if (encodedSizeOut != NULL) {
        *encodedSizeOut = 0;
    }

    input = encoded;
    output = decoded;
    for (encodedOffset = 0; encodedOffset < encodedSize; encodedOffset++) {
        if (decodedOffset >= decodedCapacity) {
            result = NWC24_ERR_OVERFLOW;
            break;
        }
        if (flags != 0 && *input == '_') {
            *output++ = ' ';
            input++;
            decodedOffset++;
        } else if (*input == '=' && encodedOffset + 2 < encodedSize) {
            BOOL validHex = TRUE;
            input++;
            encodedOffset++;
            if (*input == ' ' || *input == '\t') {
                char* next = input + 1;
                u32 scan = 1;
                while (encodedOffset + scan + 1 < encodedSize) {
                    if (*next == '\r' && next[1] == '\n') {
                        encodedOffset += scan;
                        input = next;
                        break;
                    }
                    if (*next != ' ' && *next != '\t') {
                        break;
                    }
                    next++;
                    scan++;
                }
            }
            if (*input == '\r' && input[1] == '\n') {
                input += 2;
                encodedOffset++;
            } else {
                int high = Util_xtoi(*input);
                int low;
                if (high >= 0) {
                    value = (high & 0x0F) << 4;
                }
                if (high < 0) { validHex = FALSE; }
                low = Util_xtoi(input[1]);
                if (low >= 0) {
                    value |= low & 0x0F;
                }
                if (low < 0) { validHex = FALSE; }
                input += 2;
                if (validHex) {
                    *output++ = (char)value;
                    decodedOffset++;
                }
                encodedOffset++;
            }
        } else {
            *output++ = *input++;
            decodedOffset++;
        }
    }
    if (decodedSize != NULL) {
        *decodedSize = decodedOffset;
    }
    if (encodedSizeOut != NULL) {
        *encodedSizeOut = encodedOffset;
    }
    return result;
}

NWC24Err NWC24EncodeQuotedPrintable(char* encoded, u32 encodedCapacity, u32* encodedSize, u8* decoded, u32 decodedSize, u32* decodedSizeOut) {
    return QEncode(encoded, encodedCapacity, encodedSize, decoded, decodedSize, decodedSizeOut, 0);
}

NWC24Err NWC24DecodeQuotedPrintable(char* decoded, u32 decodedCapacity, u32* decodedSize, u8* encoded, u32 encodedSize, u32* encodedSizeOut) {
    return QDecode(decoded, decodedCapacity, decodedSize, (char*)encoded, encodedSize, encodedSizeOut, 0);
}

static NWC24Err ConcatEncodedText(char* encoded, u32 encodedCapacity, u32* encodedSize, char encoding, u8* decoded, u32 decodedSize,
                                  u32* decodedSizeOut);
static inline NWC24Err AppendWordPrefix(char* encoded, u32 capacity) {
    if (Mail_strlen(encoded) + 2 < capacity) {
        Mail_strncat(encoded, "=?", 2);
    } else { return NWC24_ERR_OVERFLOW; }
    return NWC24_OK;
}

static inline NWC24Err AppendWordSeparator(char* encoded, u32 capacity) {
    if (Mail_strlen(encoded) + 2 < capacity) {
        Mail_strncat(encoded, "?", 1);
    } else { return NWC24_ERR_OVERFLOW; }
    return NWC24_OK;
}

static inline NWC24Err AppendWordSuffix(char* encoded, u32 capacity) {
    if (Mail_strlen(encoded) + 2 < capacity) {
        Mail_strncat(encoded, "?=", 2);
    } else { return NWC24_ERR_OVERFLOW; }
    return NWC24_OK;
}

static inline NWC24Err AppendWordCharset(char* encoded, u32 capacity, char* charset, u32 charsetSize) {
    if (charset == NULL) { return NWC24_ERR_INVALID_VALUE; }
    if (charsetSize + Mail_strlen(encoded) < capacity) {
        u32 length = Mail_strlen(charset);
        Mail_strncat(encoded, charset, length);
    } else { return NWC24_ERR_OVERFLOW; }
    return NWC24_OK;
}

static inline NWC24Err AppendWordEncoding(char* encoded, u32 capacity, char encoding) {
    char encodingText[1];
    encodingText[0] = encoding;
    if (encoding != 'B' && encoding != 'b' && encoding != 'Q' && encoding != 'q') {
        return NWC24_ERR_INVALID_VALUE;
    }
    if (Mail_strlen(encoded) + 1 < capacity) {
        Mail_strncat(encoded, encodingText, 1);
    } else { return NWC24_ERR_OVERFLOW; }
    return NWC24_OK;
}
static NWC24Err EncodeWord(char* encoded, u32 encodedCapacity, u32* encodedSize, char* charset, u32 charsetSize, char encoding, u8* decoded,
                           u32 decodedSize, u32* decodedSizeOut) {
    NWC24Err result;
    BOOL encodeOverflow = FALSE;

    if (decodedSizeOut != NULL) { *decodedSizeOut = 0; }
    if (encodedCapacity == 0) {
        if (decodedSizeOut != NULL) { *decodedSizeOut = 0; }
        return NWC24_ERR_INVALID_VALUE;
    }
    *encoded = '\0';
    if (encodedSize != NULL) { *encodedSize = 1; }

    result = AppendWordPrefix(encoded, encodedCapacity);
    if (result != NWC24_OK) { *encoded = '\0'; return result; }

    result = AppendWordCharset(encoded, encodedCapacity, charset, charsetSize);
    if (result != NWC24_OK) { *encoded = '\0'; return result; }

    result = AppendWordSeparator(encoded, encodedCapacity);
    if (result != NWC24_OK) { *encoded = '\0'; return result; }

    result = AppendWordEncoding(encoded, encodedCapacity, encoding);
    if (result != NWC24_OK) { *encoded = '\0'; return result; }

    result = AppendWordSeparator(encoded, encodedCapacity);
    if (result != NWC24_OK) { *encoded = '\0'; return result; }

    result = ConcatEncodedText(encoded, encodedCapacity, encodedSize, encoding, decoded, decodedSize, decodedSizeOut);
    if (result != NWC24_OK && result != NWC24_ERR_OVERFLOW) {
        *encoded = '\0';
        *decodedSizeOut = 1;
        return result;
    }
    if (result == NWC24_ERR_OVERFLOW) { encodeOverflow = TRUE; }
    result = AppendWordSuffix(encoded, encodedCapacity);
    if (result != NWC24_OK) {
        *encoded = '\0';
        *decodedSizeOut = 1;
        return result;
    }
    *encodedSize = Mail_strlen(encoded) + 1;
    if (result == NWC24_OK && encodeOverflow) { result = NWC24_ERR_OVERFLOW; }
    return result;
}

NWC24Err NWC24EncodeWord(u8* encoded, u32 encodedCapacity, u32* encodedSize, char* charset, u32 charsetSize, char encoding, u8* decoded,
                         u32 decodedSize) {
    NWC24Err result;

    if (encodedSize == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }
    if (encoded == NULL || encodedCapacity == 0) {
        return NWC24_ERR_INVALID_VALUE;
    }
    if (charset == NULL || charsetSize == 0) {
        return NWC24_ERR_INVALID_VALUE;
    }
    if (encoding == '\0') {
        return NWC24_ERR_INVALID_VALUE;
    }
    if (decoded == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    *encoded = 0;
    *encodedSize = 1;
    result = EncodeWord((char*)encoded, encodedCapacity, encodedSize, charset, charsetSize, encoding, decoded, decodedSize, NULL);
    if (result == NWC24_OK || result == NWC24_ERR_OVERFLOW) {
        encoded[*encodedSize - 1] = 0;
    }
    return result;
}

static NWC24Err ExtractCharset(char* charset, u32 charsetCapacity, u32* charsetSize, char* encoded, u32 encodedSize);
static NWC24Err ExtractEncodedText(char* decoded, u32 decodedCapacity, u32* decodedSize, char encoding, char* encoded, u32 encodedSize,
                                   u32* encodedSizeOut);

static BOOL CopyWithoutLinearWhiteSpaces(char* output, int* outputSize, char* input, int inputSize) {
    BOOL afterNewline = FALSE;
    u32 outputOffset = 0;
    s32 capacity;
    u32 limit;

    if (output == NULL || outputSize == NULL || *outputSize == 0) {
        return FALSE;
    }
    capacity = *outputSize;
    if (input == NULL) {
        *output = '\0';
        *outputSize = 1;
        return TRUE;
    }
    limit = capacity - 1U;
    while (outputOffset < limit && inputSize != 0 && *input != '\0') {
        char value = *input;
        switch (value) {
            case '\r':
            case '\n':
                if (!afterNewline) {
                    *output++ = ' ';
                    outputOffset++;
                }
                afterNewline = TRUE;
                break;
            case '\t':
            case ' ':
                if (!afterNewline) {
                    *output++ = value;
                    outputOffset++;
                }
                break;
            default:
                *output = value;
                afterNewline = FALSE;
                output++;
                outputOffset++;
                break;
        }
        input++;
        inputSize--;
    }
    *output = '\0';
    *outputSize = outputOffset + 1;
    return inputSize == 0 || *input == '\0';
}

static inline char* FindMarker(char* input, u32 size, const char* marker) {
    u32 offset;
    u32 markerLength;
    markerLength = Mail_strlen(marker);
    for (offset = 0; offset <= size; offset++) {
        char* current = input + offset;
        if (Mail_strncmp(current, marker, markerLength) == 0)
            return input + offset;
    }
    return NULL;
}
static inline char* FindMarkerAfterPrefix(char* input, u32 size, u32 prefix, const char* marker) {
    char* current;
    u32 offset;
    u32 markerLength;
    markerLength = Mail_strlen(marker);
    current = input + prefix;
    for (offset = 0; offset <= size; offset++) {
        if (Mail_strncmp(current, marker, markerLength) == 0) {
            return input + prefix + offset;
        }
        current++;
    }
    return NULL;
}

static inline char* FindEncodingMarker(char* encoded, u32 size) {
    u32 offset;
    u32 markerLength;
    const char* marker;
    char* current;
    marker = "?";
    markerLength = Mail_strlen(marker);
    current = encoded;
    for (offset = 0; offset <= size; offset++) {
        if (Mail_strncmp(current, marker, markerLength) == 0) {
            return encoded + offset;
        }
        current++;
    }
    return NULL;
}

static inline NWC24Err ExtractWordEncoding(char* encoding, u32* encodingSize, char* encoded, u32 encodedSize) {
    char* delimiter = FindEncodingMarker(encoded, encodedSize);
    if (delimiter == NULL) { return NWC24_ERR_INVALID_VALUE; }
    *encoding = delimiter[1];
    *encodingSize = 2;
    return NWC24_OK;
}
static inline BOOL IsLinearWhitespaceOnly(char* text, u32 size) {
    u32 offset;
    BOOL whitespaceOnly;
    whitespaceOnly = TRUE;
    for (offset = 0; offset < size && text[offset] != '\0'; offset++) {
        char value = text[offset];
        if (value != ' ' && value != '\t' && value != '\r' && value != '\n') {
            whitespaceOnly = FALSE;
        }
    }
    return whitespaceOnly;
}

static NWC24Err DecodeWord(char* charsetData, u32 charsetCapacity, char* decoded, u32 decodedCapacity, u32* decodedSize, char* encoded,
                           u32 encodedSize, u32* encodedSizeOut) {
    char encoding;
    char* encodedWord;
    u32 consumedSize;
    u32 decodedLength;
    int encodedLength;
    NWC24Err result;

    if (encodedSizeOut != NULL) { *encodedSizeOut = 0; }
    if (decodedCapacity == 0) {
        if (encodedSizeOut != NULL) { *encodedSizeOut = 0; }
        return NWC24_ERR_INVALID_VALUE;
    }
    *decoded = '\0';
    if (decodedSize != NULL) { *decodedSize = 1; }
    if (encodedSizeOut != NULL) { *encodedSizeOut = 0; }
    encodedWord = FindMarker(encoded, encodedSize, "=?");
    if (encodedWord == encoded) {
        result = ExtractCharset(charsetData, charsetCapacity, &consumedSize, encodedWord, encodedSize);
        if (result != NWC24_OK) { return result; }
        encodedLength = consumedSize;
        result = ExtractWordEncoding(&encoding, &consumedSize, encodedWord + encodedLength, encodedSize - encodedLength);
        if (result != NWC24_OK) { return result; }
        encodedLength += consumedSize;
        result = ExtractEncodedText(decoded, decodedCapacity, &decodedLength, encoding, encodedWord + encodedLength,
                                    encodedSize - encodedLength, &consumedSize);
        if (result != NWC24_OK) { return result; }
        encodedLength += consumedSize;
    } else {
        u32 localSize;
        if (encodedWord != NULL) {
            encodedLength = encodedWord - encoded;
        } else {
            encodedLength = STD_strnlen(encoded, encodedSize);
        }
        localSize = decodedCapacity;
        if (!CopyWithoutLinearWhiteSpaces(decoded, (int*)&localSize, encoded, encodedLength)) {
            *decodedSize = localSize;
            if (encodedSizeOut != NULL) { *encodedSizeOut = encodedLength; }
            return NWC24_ERR_OVERFLOW;
        }
        decodedLength = localSize;
        if (encodedWord != NULL) {
            if (IsLinearWhitespaceOnly(decoded, localSize)) {
                *decoded = '\0';
                decodedLength = 1;
            }
        }
    }
    *decodedSize = decodedLength;
    if (encodedSizeOut != NULL) { *encodedSizeOut = encodedLength; }
    return NWC24_OK;
}

NWC24Err NWC24DecodeMIMEHeaderFieldBody(u8* charsetData, u32 charsetDataSize, u8* decoded, u32 decodedCapacity, u32* decodedSize, u8* encoded,
                                        u32 encodedSize) {
    int result = 0;
    char* input;
    s32 inputSize;
    u8* output;
    s32 remainingCapacity;

    if (decodedSize == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }
    if (charsetData == NULL || charsetDataSize == 0) {
        return NWC24_ERR_INVALID_VALUE;
    }
    if (decoded == NULL || decodedCapacity == 0) {
        return NWC24_ERR_INVALID_VALUE;
    }
    if (encoded == NULL)
        return NWC24_ERR_INVALID_VALUE;
    *decoded = 0;
    *charsetData = 0;
    *decodedSize = 1;
    input = (char*)encoded;
    inputSize = encodedSize;
    output = decoded;
    remainingCapacity = decodedCapacity;
    while ((s32)inputSize > 0 && remainingCapacity > 0 && *input != '\0') {
        u32 copiedSize = 0;
        u32 consumedSize;
        result =
            DecodeWord((char*)charsetData, charsetDataSize, (char*)output, remainingCapacity, &copiedSize, (char*)input, inputSize, &consumedSize);
        if (copiedSize == 0) {
            break;
        }
        copiedSize--;
        output += copiedSize;
        remainingCapacity -= copiedSize;
        *decodedSize += copiedSize;
        input += consumedSize;
        inputSize -= consumedSize;
        if (result != NWC24_OK) {
            break;
        }
    }
    if (result == NWC24_OK && inputSize > 0 && *input != '\0') {
        result = NWC24_ERR_OVERFLOW;
    }
    decoded[*decodedSize - 1] = '\0';
    return result;
}

static NWC24Err ConcatEncodedText(char* encoded, u32 encodedCapacity, u32* encodedSize, char encoding, u8* decoded, u32 decodedSize,
                                  u32* decodedSizeOut) {
    u32 prefixSize = Mail_strlen(encoded);
    int available = encodedCapacity - prefixSize - 2;
    NWC24Err result;

    if (available > 0) {
        if (encoding == 'B' || encoding == 'b') {
            result = Base64Encode(decoded, decodedSize, decodedSizeOut, (u8*)encoded + prefixSize, (u32)(available - 1), encodedSize);
        } else if (encoding == 'Q' || encoding == 'q') {
            result = QEncode(encoded + prefixSize, (u32)(available - 1), encodedSize, decoded, decodedSize, decodedSizeOut, 1);
        } else {
            result = NWC24_ERR_NOT_SUPPORTED;
        }
        if (result == NWC24_OK || result == NWC24_ERR_OVERFLOW) {
            encoded[prefixSize + *encodedSize] = '\0';
            *encodedSize += 1;
        }
    } else {
        result = NWC24_ERR_OVERFLOW;
    }
    return result;
}



static NWC24Err ExtractCharset(char* charset, u32 charsetCapacity, u32* charsetSize, char* encoded, u32 encodedSize) {
    char* start;
    char* end;
    u32 charsetLength;

    if (charset == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }
    start = FindMarker(encoded, encodedSize, "=?");
    if (start == NULL) {
        return NWC24_ERR_NOT_SUPPORTED;
    }
    end = FindMarkerAfterPrefix(start, encodedSize - (u32)(start + 2 - encoded), 2, "?");
    if (end == NULL) {
        return NWC24_ERR_NOT_SUPPORTED;
    }
    charsetLength = (u32)(end - (start + 2));
    if (charsetLength < charsetCapacity) {
        Mail_strncpy(charset, start + 2, charsetLength);
        charset[charsetLength] = '\0';
    } else { return NWC24_ERR_OVERFLOW; }
    *charsetSize = charsetLength + 2;
    return NWC24_OK;
}
static inline char* FindMarkerOffsetPrefix(char* input, u32 size, u32 prefix, const char* marker) {
    u32 offset;
    u32 markerLength;
    markerLength = Mail_strlen(marker);
    for (offset = 0; offset <= size; offset++) {
        if (Mail_strncmp(input + offset + prefix, marker, markerLength) == 0) {
            return input + prefix + offset;
        }
    }
    return NULL;
}


static NWC24Err ExtractEncodedText(char* decoded, u32 decodedCapacity, u32* decodedSize, char encoding, char* encoded, u32 encodedSize,
                                   u32* encodedSizeOut) {
    char* start;
    char* end;
    int length;
    NWC24Err result;

    if (encoded == NULL) { return NWC24_ERR_INVALID_VALUE; }
    if (decodedSize == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }
    *decodedSize = 0;
    if (encodedSizeOut == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }
    *encodedSizeOut = 0;
    start = FindMarker(encoded, encodedSize, "?");
    if (start == NULL) {
        return NWC24_ERR_NOT_SUPPORTED;
    }
    end = FindMarkerOffsetPrefix(start, encodedSize - (u32)(start + 1 - encoded), 1, "?=");
    if (end == NULL) {
        return NWC24_ERR_NOT_SUPPORTED;
    }
    length = end - (start + 1);
    if (encoding == 'B' || encoding == 'b') {
        result = NWC24Base64Decode((u8*)(start + 1), length, (u8*)decoded, decodedCapacity - 1, decodedSize);
        if (result == NWC24_OK || result == NWC24_ERR_OVERFLOW) {
            decoded[*decodedSize] = '\0';
            *decodedSize += 1;
        }
    } else if (encoding == 'Q' || encoding == 'q') {
        result = QDecode(decoded, decodedCapacity - 1, decodedSize, start + 1, length, NULL, 1);
        if (result == NWC24_OK || result == NWC24_ERR_OVERFLOW) {
            decoded[*decodedSize] = '\0';
            *decodedSize += 1;
        }
    } else {
        return NWC24_ERR_NOT_SUPPORTED;
    }
    if (end != NULL) { *encodedSizeOut = (u32)(end - encoded) + 2; }
    return result;
}
