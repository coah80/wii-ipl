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
    u32 decodedOffset;
    u8 value;
    char* input;
    char* output;
    NWC24Err result;
    int valid;

    decodedOffset = 0;
    value = 0;
    result = NWC24_OK;

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
            input++;
            encodedOffset++;
            valid = 1;
            if (*input == ' ' || *input == '\t') {
                char* scan = input + 1;
                u32 scanLen = 1;
                while (encodedOffset + scanLen + 1 < encodedSize) {
                    if (*scan == '\r' && scan[1] == '\n') {
                        input = scan;
                        encodedOffset += scanLen;
                        break;
                    }
                    if (*scan != ' ' && *scan != '\t') {
                        break;
                    }
                    scan++;
                    scanLen++;
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
                } else {
                    valid = 0;
                }
                low = Util_xtoi(input[1]);
                if (low >= 0) {
                    value = (value | (low & 0x0F)) & 0xFF;
                } else {
                    valid = 0;
                }
                input += 2;
                if (valid) {
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

static inline NWC24Err AppendBounded(char* encoded, u32 encodedCapacity, u32 needed, const char* str, u32 strLen) {
    NWC24Err result;
    if (Mail_strlen(encoded) + needed < encodedCapacity) {
        Mail_strncat(encoded, str, strLen);
        result = NWC24_OK;
    } else {
        result = NWC24_ERR_OVERFLOW;
    }
    return result;
}

static NWC24Err EncodeWord(char* encoded, u32 encodedCapacity, u32* encodedSize, char* charset, u32 charsetSize, char encoding, u8* decoded,
                           u32 decodedSize, u32* decodedSizeOut) {
    NWC24Err result;
    BOOL encodeOverflow = FALSE;

    if (decodedSizeOut != NULL) {
        *decodedSizeOut = 0;
    }
    if (encodedCapacity == 0) {
        if (decodedSizeOut != NULL) {
            *decodedSizeOut = 0;
        }
        return NWC24_ERR_INVALID_VALUE;
    }
    *encoded = '\0';
    if (encodedSize != NULL) {
        *encodedSize = 1;
    }
    result = AppendBounded(encoded, encodedCapacity, 2, "=?", 2);
    if (result != NWC24_OK) {
        *encoded = '\0';
        goto done;
    }
    if (charset != NULL) {
        result = AppendBounded(encoded, encodedCapacity, charsetSize, charset, Mail_strlen(charset));
    } else {
        result = NWC24_ERR_INVALID_VALUE;
    }
    if (result != NWC24_OK) {
        *encoded = '\0';
        goto done;
    }
    result = AppendBounded(encoded, encodedCapacity, 2, "?", 1);
    if (result != NWC24_OK) {
        *encoded = '\0';
        goto done;
    }
    {
        char value[1];
        value[0] = encoding;
        if (encoding == 'B' || encoding == 'b' || encoding == 'Q' || encoding == 'q') {
            result = AppendBounded(encoded, encodedCapacity, 1, value, 1);
        } else {
            result = NWC24_ERR_INVALID_VALUE;
        }
        if (result != NWC24_OK) {
            *encoded = '\0';
            goto done;
        }
    }
    result = AppendBounded(encoded, encodedCapacity, 2, "?", 1);
    if (result != NWC24_OK) {
        *encoded = '\0';
        goto done;
    }
    result = ConcatEncodedText(encoded, encodedCapacity, encodedSize, encoding, decoded, decodedSize, decodedSizeOut);
    if (result != NWC24_OK && result != NWC24_ERR_OVERFLOW) {
        *encoded = '\0';
        *decodedSizeOut = 1;
        goto done;
    }
    if (result == NWC24_ERR_OVERFLOW) {
        encodeOverflow = TRUE;
    }
    result = AppendBounded(encoded, encodedCapacity, 2, "?=", 2);
    if (result != NWC24_OK) {
        *encoded = '\0';
        *decodedSizeOut = 1;
        goto done;
    }
    *encodedSize = Mail_strlen(encoded) + 1;
    if (result == NWC24_OK) {
        if (encodeOverflow) {
            result = NWC24_ERR_OVERFLOW;
        }
    }

done:
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

static NWC24Err ExtractCharset(char* charset, u32 charsetCapacity, u32* charsetSize, char* encoded, u32 encodedSize) NO_INLINE;
static NWC24Err ExtractEncodedText(char* decoded, u32 decodedCapacity, u32* decodedSize, char encoding, char* encoded, u32 encodedSize,
                                   u32* encodedSizeOut);

static BOOL CopyWithoutLinearWhiteSpaces(char* output, int* outputSize, char* input, int inputSize) {
    u32 outputOffset = 0;
    BOOL afterNewline = FALSE;
    s32 capacity;

    if (output == NULL || outputSize == NULL || *outputSize == 0) {
        return FALSE;
    }
    capacity = *outputSize;
    if (input == NULL) {
        *output = '\0';
        *outputSize = 1;
        return TRUE;
    }
    while (outputOffset < capacity - 1U && inputSize != 0 && *input != '\0') {
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
    u32 markerLength = Mail_strlen(marker);
    s32 offset;
    for (offset = 0; offset <= size; offset++) {
        char* pos = input + offset;
        if (Mail_strncmp(pos, marker, markerLength) == 0)
            return input + offset;
    }
    return NULL;
}

static NWC24Err DecodeWord(char* charsetData, u32 charsetCapacity, char* decoded, u32 decodedCapacity, u32* decodedSize, char* encoded,
                           u32 encodedSize, u32* encodedSizeOut) {
    char* encodedWordPosition;
    u32 encodedLength;
    u32 consumedSize;
    u32 decodedLength;
    NWC24Err result;

    if (encodedSizeOut != NULL) {
        *encodedSizeOut = 0;
    }
    if (decodedCapacity == 0) {
        if (encodedSizeOut != NULL)
            *encodedSizeOut = 0;
        return NWC24_ERR_INVALID_VALUE;
    }
    *decoded = '\0';
    if (decodedSize != NULL) {
        *decodedSize = 1;
    }
    if (encodedSizeOut != NULL) {
        *encodedSizeOut = 0;
    }
    encodedWordPosition = FindMarker((char*)encoded, encodedSize, "=?");
    if (encodedWordPosition == (char*)encoded) {
        result = ExtractCharset(charsetData, charsetCapacity, &consumedSize, (char*)encoded, encodedSize);
        if (result != NWC24_OK) {
            return result;
        }
        encodedLength = consumedSize;
        {
            const char* marker = "?";
            u32 markerLength = Mail_strlen(marker);
            u32 offset;
            char* delimiter = NULL;
            char* current;
            for (offset = 0; offset <= encodedSize - consumedSize; offset++) {
                current = (char*)encodedWordPosition + consumedSize + offset;
                if (Mail_strncmp((char*)current, marker, markerLength) == 0) {
                    delimiter = current;
                    break;
                }
            }
            if (delimiter == 0) {
                return NWC24_ERR_INVALID_VALUE;
            }
            {
                char encoding = delimiter[1];
                consumedSize = 2;
                encodedLength += consumedSize;
                result = ExtractEncodedText(decoded, decodedCapacity, &decodedLength, encoding, encoded + encodedLength, encodedSize - encodedLength,
                                            &consumedSize);
                if (result != NWC24_OK) {
                    return result;
                }
                encodedLength += consumedSize;
            }
        }
    } else {
        u32 localSize = decodedCapacity;
        if (encodedWordPosition == NULL) {
            encodedLength = STD_strnlen(encoded, encodedSize);
        } else {
            encodedLength = encodedWordPosition - (char*)encoded;
        }
        if (!CopyWithoutLinearWhiteSpaces(decoded, (int*)&localSize, encoded, encodedLength)) {
            *decodedSize = localSize;
            if (encodedSizeOut != NULL) {
                *encodedSizeOut = encodedLength;
            }
            return NWC24_ERR_OVERFLOW;
        }
        decodedLength = localSize;
        if (encodedWordPosition != NULL) {
            BOOL whitespaceOnly = TRUE;
            u32 offset;
            for (offset = 0; offset < localSize && decoded[offset] != '\0'; offset++) {
                char value = decoded[offset];
                if (value != ' ' && value != '\t' && value != '\r' && value != '\n') {
                    whitespaceOnly = FALSE;
                }
            }
            if (whitespaceOnly) {
                *decoded = '\0';
                decodedLength = 1;
            }
        }
    }
    if (decodedSize != NULL) {
        *decodedSize = decodedLength;
    }
    if (encodedSizeOut != NULL) {
        *encodedSizeOut = encodedLength;
    }
    return result;
}

NWC24Err NWC24DecodeMIMEHeaderFieldBody(u8* charsetData, u32 charsetDataSize, u8* decoded, u32 decodedCapacity, u32* decodedSize, u8* encoded,
                                        u32 encodedSize) {
    int result = 0;
    u8* output;
    u32 inputSize;
    u32 capacity;
    u8* input;

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
    inputSize = encodedSize;
    capacity = decodedCapacity;
    output = decoded;
    input = encoded;
    while ((s32)inputSize > 0 && (s32)capacity > 0 && *input != '\0') {
        u32 copiedSize = 0;
        u32 consumedSize;
        result =
            DecodeWord((char*)charsetData, charsetDataSize, (char*)output, capacity, &copiedSize, (char*)input, inputSize, &consumedSize);
        if (copiedSize == 0) {
            break;
        }
        copiedSize--;
        output += copiedSize;
        capacity -= copiedSize;
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
    end = FindMarker(start + 2, encodedSize - (u32)(start + 2 - encoded), "?");
    if (end == NULL) {
        return NWC24_ERR_NOT_SUPPORTED;
    }
    charsetLength = (u32)(end - (start + 2));
    if (charsetLength < charsetCapacity) {
        Mail_strncpy(charset, start + 2, charsetLength);
        charset[charsetLength] = '\0';
    } else {
        return NWC24_ERR_OVERFLOW;
    }
    *charsetSize = charsetLength + 2;
    return NWC24_OK;
}

static NWC24Err ExtractEncodedText(char* decoded, u32 decodedCapacity, u32* decodedSize, char encoding, char* encoded, u32 encodedSize,
                                   u32* encodedSizeOut) {
    char* start;
    char* end;
    int length;
    NWC24Err result;

    if (encoded == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }
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
    end = FindMarker(start + 1, encodedSize - (u32)(start + 1 - encoded), "?=");
    if (end == NULL) {
        return NWC24_ERR_NOT_SUPPORTED;
    }
    length = (u32)(end - (start + 1));
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
    if (end != NULL) {
        *encodedSizeOut = (u32)(end - encoded) + 2;
    }
    return result;
}
