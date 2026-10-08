#include <zi8clib/zierror.h>
#include <zi8clib/zitypes.h>

extern ziU32 Zi8GetTableAddress(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);

const ziU8 Zi8PinyinInitials[0x1C] = {
    0x00, 0x3C, 0x98, 0x02, 0x00, 0x38, 0x34, 0x3B, 0x00, 0x06, 0x37, 0x2B,
    0x0C, 0x26, 0x00, 0x3F, 0x09, 0x2C, 0x9A, 0x05, 0x00, 0x00, 0x11, 0x0A,
    0x0D, 0x9C, 0x00, 0x00
};
const ziU8 Zi8BpmfInitials[0x24] = {
    0x3C, 0x3F, 0x0C, 0x38, 0x02, 0x05, 0x26, 0x2B, 0x34, 0x37, 0x3B, 0x06,
    0x09, 0x0A, 0x1D, 0x19, 0x1B, 0x2C, 0x1C, 0x18, 0x1A, 0x01, 0x02, 0x03,
    0x05, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0E, 0x0D, 0x0F, 0x04, 0x00, 0x00
};
const ziU8 Zi8PinyinFinals[0x36][8] = {
    {0x0F, 0xFF, 0x00, 0x00, 0x3C, 0x28, 0x00, 0x00},
    {0x0F, 0x00, 0x00, 0x00, 0x3F, 0x2B, 0x00, 0x00},
    {0x0F, 0x0E, 0xFF, 0x00, 0x3F, 0x28, 0x00, 0x00},
    {0x0F, 0x0E, 0x07, 0x00, 0x3F, 0x28, 0x00, 0x00},
    {0x0F, 0x15, 0x00, 0x00, 0x3F, 0x2A, 0x00, 0x00},
    {0x09, 0xFF, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00},
    {0x09, 0x00, 0x00, 0x00, 0x3F, 0x08, 0x00, 0x00},
    {0x09, 0x01, 0xFF, 0x00, 0x38, 0x00, 0x00, 0x00},
    {0x09, 0x01, 0x00, 0x00, 0x3F, 0x04, 0x00, 0x00},
    {0x09, 0x01, 0x0F, 0x00, 0x3F, 0x01, 0x00, 0x00},
    {0x09, 0x01, 0x0E, 0xFF, 0x3E, 0x02, 0x00, 0x00},
    {0x09, 0x01, 0x0E, 0x00, 0x3F, 0x02, 0x00, 0x00},
    {0x09, 0x01, 0x0E, 0x07, 0x3F, 0x03, 0x00, 0x00},
    {0x09, 0x05, 0x00, 0x00, 0x3F, 0x09, 0x00, 0x00},
    {0x09, 0x15, 0x00, 0x00, 0x3F, 0x0B, 0x00, 0x00},
    {0x09, 0x0E, 0xFF, 0x00, 0x3E, 0x0C, 0x00, 0x00},
    {0x09, 0x0E, 0x00, 0x00, 0x3F, 0x0C, 0x00, 0x00},
    {0x09, 0x0E, 0x07, 0x00, 0x3F, 0x0D, 0x00, 0x00},
    {0x09, 0x0F, 0xFF, 0x00, 0x3E, 0x0E, 0x00, 0x00},
    {0x09, 0x0F, 0x15, 0x00, 0x3F, 0x0E, 0x00, 0x00},
    {0x09, 0x0F, 0x0E, 0xFF, 0x3F, 0x0F, 0x00, 0x00},
    {0x09, 0x0F, 0x0E, 0x07, 0x3F, 0x0F, 0x00, 0x00},
    {0x15, 0xFF, 0x00, 0x00, 0x30, 0x10, 0x00, 0x00},
    {0x15, 0x00, 0x00, 0x00, 0x3F, 0x18, 0x00, 0x00},
    {0x15, 0x01, 0xFF, 0x00, 0x38, 0x10, 0x00, 0x00},
    {0x15, 0x01, 0x00, 0x00, 0x3F, 0x17, 0x00, 0x00},
    {0x15, 0x01, 0x0E, 0xFF, 0x3E, 0x10, 0x00, 0x00},
    {0x15, 0x01, 0x0E, 0x00, 0x3F, 0x10, 0x00, 0x00},
    {0x15, 0x01, 0x0E, 0x07, 0x3F, 0x11, 0x00, 0x00},
    {0x15, 0x01, 0x09, 0x00, 0x3F, 0x13, 0x00, 0x00},
    {0x15, 0x0E, 0x00, 0x00, 0x3F, 0x1C, 0x00, 0x00},
    {0x15, 0x09, 0x00, 0x00, 0x3F, 0x1D, 0x00, 0x00},
    {0x15, 0x0F, 0x00, 0x00, 0x3F, 0x1E, 0x00, 0x00},
    {0x15, 0x05, 0x00, 0x00, 0x3F, 0x1F, 0x00, 0x00},
    {0x01, 0xFF, 0x00, 0x00, 0x38, 0x20, 0x00, 0x00},
    {0x01, 0x00, 0x00, 0x00, 0x3F, 0x23, 0x00, 0x00},
    {0x01, 0x0E, 0xFF, 0x00, 0x3E, 0x20, 0x00, 0x00},
    {0x01, 0x0E, 0x00, 0x00, 0x3F, 0x20, 0x00, 0x00},
    {0x01, 0x0E, 0x07, 0x00, 0x3F, 0x21, 0x00, 0x00},
    {0x01, 0x09, 0x00, 0x00, 0x3F, 0x25, 0x00, 0x00},
    {0x01, 0x0F, 0x00, 0x00, 0x3F, 0x26, 0x00, 0x00},
    {0x05, 0xFF, 0x00, 0x00, 0x38, 0x30, 0x00, 0x00},
    {0x05, 0x00, 0x00, 0x00, 0x3F, 0x34, 0x00, 0x00},
    {0x05, 0x0E, 0xFF, 0x00, 0x3E, 0x30, 0x00, 0x00},
    {0x05, 0x0E, 0x00, 0x00, 0x3F, 0x30, 0x00, 0x00},
    {0x05, 0x0E, 0x07, 0x00, 0x3F, 0x31, 0x00, 0x00},
    {0x05, 0x09, 0x00, 0x00, 0x3F, 0x35, 0x00, 0x00},
    {0x05, 0x12, 0x00, 0x00, 0x3F, 0x33, 0x00, 0x00},
    {0x16, 0xFF, 0x00, 0x00, 0x3C, 0x38, 0x00, 0x00},
    {0x16, 0x00, 0x00, 0x00, 0x3F, 0x38, 0x00, 0x00},
    {0x16, 0x01, 0xFF, 0x00, 0x3F, 0x39, 0x00, 0x00},
    {0x16, 0x01, 0x0E, 0x00, 0x3F, 0x39, 0x00, 0x00},
    {0x16, 0x05, 0x00, 0x00, 0x3F, 0x1F, 0x00, 0x00},
    {0x16, 0x0E, 0x00, 0x00, 0x3F, 0x3B, 0x00, 0x00}
};
const ziU8 nodeHeaderTable[0x20] = {
    0x00, 0x10, 0x00, 0x01, 0x00, 0x03, 0x00, 0x14, 0x00, 0x05, 0x00, 0x07,
    0x00, 0x1C, 0x00, 0x0D, 0x00, 0x0F, 0x00, 0x11, 0x00, 0x13, 0x00, 0x15,
    0x00, 0x17, 0x00, 0x1D, 0x00, 0x1F, 0x00, 0x35
};

ziBool Zi8PriMatchNextChar(ziU8* node, ziU8 firstByteMask, ziU8 firstByteValue, ziU8 secondByteMask, ziU8 secondByteValue, ziU8 thirdByteMask, ziU8 thirdByteValue, ziU8 fourthByteMask, ziU8 fourthByteValue, ziU16* count, ziU8** result, ziU16* code ZI_NEED_WORK) {
    ziU16 remaining = *count;
    while (remaining-- != 0) {
        if ((firstByteValue == (node[0] & firstByteMask)) && (fourthByteValue == (node[3] & fourthByteMask)) && (thirdByteValue == (node[2] & thirdByteMask)) && (secondByteValue == (node[1] & secondByteMask))) {
            *result = node;
            *code = ((ziU16)node[6] << 8) + (ziU16)node[7];
            *count = remaining;
            Zi8LogError(0x64, ZI_WORK);
            return 1;
        }
        node += 0xC;
    }
    Zi8LogError(0x12E, ZI_WORK);
    return 0;
}

ziBool Zi8ExactMatchNextChar(ziU8* node, ziU8 firstByteMask, ziU8 firstByteValue, ziU8 secondByteMask, ziU8 secondByteValue, ziU8 thirdByteMask, ziU8 thirdByteValue, ziU8 fourthByteMask, ziU8 fourthByteValue, ziU16* count, ziU8** result, ziU16* code ZI_NEED_WORK) {
    ziU16 remaining = *count;
    ziU8* current = node;
    while (remaining-- != 0) {
        if ((firstByteValue == (current[0] & firstByteMask)) && (fourthByteValue == (current[3] & fourthByteMask)) && (thirdByteValue == (current[2] & thirdByteMask)) && (secondByteValue == (current[1] & secondByteMask))) {
            *result = current;
            *code = ((ziU16)current[6] << 8) + (ziU16)current[7];
            *count = remaining;
            Zi8LogError(0x64, ZI_WORK);
            return 1;
        }
        current += 0xC;
    }
    Zi8LogError(0x12E, ZI_WORK);
    return 0;
}

ziU32 Zi8SecMatchChar(ziU8* nodeAddress, ziU8* dictionaryAddress, ziMatchParam* match, ziU16* code ZI_NEED_WORK) {
    ziBool isPartial = 0;
    ziU16 matchCode;
    ziU8* data;
    ziU8 value;
    ziU16 targetCode;
    ziU8 dataIndex;
    ziU8 remaining;

    if (match->componentIndex != 0) {
        targetCode = match->componentIndex;
        matchCode = ((ziU16)(nodeAddress[4] & 3) << 8) | nodeAddress[5];
        value = 0;
        while (value++ < 6) {
            if (targetCode == matchCode) {
                break;
            }
            matchCode = ((ziU16)(*(dictionaryAddress + matchCode * 8 + 6) & 3) << 8) | *(dictionaryAddress + matchCode * 8 + 7);
            if (matchCode == 0) {
                break;
            }
        }
        if (targetCode != matchCode) {
            return 0;
        }
    }

    data = (ziU8*)Zi8GetTableAddress(ZI8_LANG_ZH, 1, ZI_WORK);
    data += nodeAddress[0xB] + (nodeAddress[0xA] << 8) + ((nodeAddress[9] & 0xF) << 16);
    if (ZI_WORK->cangjieEnabled != 0) {
        switch (data[0] & 7) {
        case 2:
            data += 2;
            break;
        case 3:
        case 4:
            data += 3;
            break;
        case 5:
            data += 4;
            break;
        default:
            data++;
            break;
        }
    }

    value = data[0];
    value = (value >> 4) & 7;
    if (value * 2 + 10 < match->length) {
        return 0;
    }
    if (match->length < 9) {
        if (match->length == 8) {
            if ((data[0] & 0xF) == 0xF) {
                isPartial = 1;
            }
        } else if ((match->length & 1) != 0) {
            if ((nodeAddress[match->length >> 1] & 0xF) == 0xF) {
                isPartial = 1;
            }
        } else {
            if ((nodeAddress[match->length >> 1] & 0xF0) == 0xF0) {
                isPartial = 1;
            }
        }
        if (match->length > 2) {
            if ((match->length & 1) != 0) {
                if (((nodeAddress[(match->length - 1) >> 1] & 0xF0) == 0) || ((nodeAddress[(match->length - 1) >> 1] & 0xF0) == 0xF0)) {
                    return 0;
                }
            } else {
                if (((nodeAddress[(match->length - 1) >> 1] & 0xF) == 0) || ((nodeAddress[(match->length - 1) >> 1] & 0xF) == 0xF)) {
                    return 0;
                }
            }
        }
        if (code != 0) {
            *code = ((ziU16)nodeAddress[6] << 8) + (ziU16)nodeAddress[7];
        }
        if (isPartial) {
            return 2;
        }
        return 1;
    }

    if ((match->length & 1) != 0) {
        if (((data[((match->length - 1) >> 1) - 4] & 0xF0) == 0) || ((data[((match->length - 1) >> 1) - 4] & 0xF0) == 0xF0)) {
            return 0;
        }
    } else {
        if (((data[((match->length - 1) >> 1) - 4] & 0xF) == 0) || ((data[((match->length - 1) >> 1) - 4] & 0xF) == 0xF)) {
            return 0;
        }
    }

    dataIndex = 4;
    remaining = ((match->length + 1) >> 1) - 4;
    if ((value + 1) < remaining) {
        return 0;
    }
    if ((match->length & 1) != 0) {
        if ((data[(match->length >> 1) - 4] & 0xF) == 0xF) {
            isPartial = 1;
        }
    } else {
        if ((data[(match->length >> 1) - 4] & 0xF0) == 0xF0) {
            isPartial = 1;
        }
    }
    if (match->count == 0) {
        while (remaining != 0) {
            if ((data[0] & match->recordMasks[dataIndex]) != match->recordValues[dataIndex]) {
                return 0;
            }
            dataIndex++;
            remaining--;
            data++;
        }
    }
    if (code != 0) {
        *code = ((ziU16)nodeAddress[6] << 8) + (ziU16)nodeAddress[7];
    }
    if (isPartial) {
        return 2;
    }
    return 1;
}

ziBool Zi8PriMatchNextComp(ziU8* node, ziU8 firstByteMask, ziU8 firstByteValue, ziU8 secondByteMask, ziU8 secondByteValue, ziU8 thirdByteMask, ziU8 thirdByteValue, ziU8 fourthByteMask, ziU8 fourthByteValue, ziU16* count, ziU8** result ZI_NEED_WORK) {
    ziU16 remaining = *count;
    while (remaining-- != 0) {
        if ((firstByteValue == (node[0] & firstByteMask)) && (secondByteValue == (node[1] & secondByteMask)) && (thirdByteValue == (node[2] & thirdByteMask)) && (fourthByteValue == (node[3] & fourthByteMask))) {
            *result = node;
            *count = remaining;
            Zi8LogError(0x64, ZI_WORK);
            return 1;
        }
        node += 8;
    }
    Zi8LogError(0x12E, ZI_WORK);
    return 0;
}

ziBool Zi8SecMatchComp(ziU8* nodeAddress, ziMatchParam* matchAddress, ziU8* dictionaryAddress ZI_NEED_WORK) {
    int chainIndex;
    ziU16 matchCode;
    ziU16 targetCode;

    if (matchAddress->componentIndex != 0) {
        targetCode = matchAddress->componentIndex;
        matchCode = ((ziU16)(nodeAddress[6] & 3) << 8) | nodeAddress[7];
        chainIndex = 0;
        while (chainIndex++ < 6) {
            if (targetCode == matchCode) {
                break;
            }
            matchCode = ((ziU16)(*(dictionaryAddress + matchCode * 8 + 6) & 3) << 8) | *(dictionaryAddress + matchCode * 8 + 7);
            if (matchCode == 0) {
                break;
            }
        }
        if (targetCode != matchCode) {
            return 0;
        }
    }
    if (matchAddress->length > 8) {
        if (nodeAddress[5] < (matchAddress->length - 2)) {
            return 0;
        }
    } else if (nodeAddress[5] < (matchAddress->length - 1)) {
        return 0;
    }
    return 1;
}

extern ziU16 Zi8MatchAltSound(ziPtr soundTable, ziU16 soundCode, ziPtr pCodeTable, ziU16 index, ziU16 mask, ziU16 value, ziU8 flag ZI_NEED_WORK);
ziU16 Zi8GetPCode(ziU8* table, ziU8* node);

ziBool Zi8MatchPhonetic(ziU8* pCodeTable, ziU8* dictionary, ziPtr soundTable, ziU16 soundCode, ziU32 tableAddress, ziU8* node, ziU16* masks, ziU16* values, ziU16* count, ziU8** resultNode, ziU8** stringOffset, ziU8 partialMode, ziU8 strictMode, ziU8 numParts, ziU16 partMask, ziU16 partValue, ziU8 flag, ziU8 altMode, ziU16 initialCode, ziU16* resultCode, ziU8 lastMode ZI_NEED_WORK) {
    ziU16 code;
    ziU16 remaining;
    ziU16 soundIndex;
    ziU16 dictionaryIndex;
    ziU8 matchedParts;
    ziU8 nextCode;
    ziU8 partCount;
    ziU8 partIndex;
    ziBool hasString;
    ziU8* sound;
    typedef struct {
        ziU8 header;
        ziU8 content[11];
    } DictionaryNode;

    if (*stringOffset != 0) {
        hasString = 1;
    } else {
        hasString = 0;
    }
    if (*count != 0) {
        remaining = *count;
    } else {
        remaining = 1;
    }
    matchedParts = 0;
    if ((lastMode != 0) && (numParts > 1)) {
        altMode = 1;
    }
    while (remaining-- != 0) {
        if ((node[0] & flag) != 0) goto decode_node;
next_node:
        node += 0xC;
        continue;
decode_node:
        code = Zi8GetPCode(pCodeTable, node);
        if ((*values != (code & *masks)) && (altMode == 0) && ((node[0] & 0x80) != 0)) {
            if (*count != 0) {
                soundIndex = (initialCode - remaining) - 1;
            } else {
                soundIndex = initialCode;
            }
            code = Zi8MatchAltSound(soundTable, soundCode, pCodeTable, soundIndex, *masks, *values, flag, ZI_WORK);
        }
        goto check_code;
match_code:
        if (partValue == (code & partMask)) goto next_node;
        matchedParts = 1;
        if (*count != 0) {
            soundIndex = (initialCode - remaining) - 1;
        } else {
            soundIndex = initialCode;
        }
        sound = (ziU8*)(tableAddress + ((node[9] & 0xF) * 0x10000 + (node[0xB] + node[0xA] * 0x100)));
        if (ZI_WORK->cangjieEnabled != 0) {
            switch (sound[0] & 7) {
            case 2:
                sound += 2;
                break;
            case 3:
            case 4:
                sound += 3;
                break;
            case 5:
                sound += 4;
                break;
            default:
                sound++;
                break;
            }
        }
        if ((sound[0] & 0x80) != 0) {
            sound += ((sound[0] & 0x7F) >> 4) + 1;
        } else if (numParts > 1) {
            goto next_node;
        }
        if (((ziU8)matchedParts == numParts) || (numParts == 0)) {
            *resultNode = node;
            *resultCode = ((ziU16)node[6] << 8) + node[7];
            *count = remaining;
            return 1;
        }
next_group:
        {
            nextCode = *sound++;
            partCount = nextCode & 0xF;
            if ((nextCode & flag) == 0) {
                for (; partCount != 0; partCount--) {
                    for (sound++; (*sound & 0x80) == 0; sound += 2) {
                    }
                    sound++;
                }
            }
            for (; partCount != 0; partCount--) {
                partIndex = 1;
                if (hasString && (sound > *stringOffset)) {
                    hasString = 0;
                }
                if (!hasString) {
                    *stringOffset = sound;
                }
                do {
                    dictionaryIndex = sound[0] | ((ziU16)sound[1] << 8);
                    sound += 2;
                    if (hasString) {
                        goto phonetic_skip;
                    }
                    code = Zi8GetPCode(pCodeTable, dictionary + (dictionaryIndex & 0x7FFF) * sizeof(DictionaryNode));
                    if (((code & masks[partIndex]) != values[partIndex]) && (altMode == 0) && (dictionary[(dictionaryIndex & 0x7FFF) * sizeof(DictionaryNode)] & 0x80) != 0) {
                        code = Zi8MatchAltSound(soundTable, soundCode, pCodeTable, dictionaryIndex & 0x7FFF, masks[partIndex], values[partIndex], flag, ZI_WORK);
                    }
                    if ((code & masks[partIndex]) == values[partIndex]) {
                        goto phonetic_matched;
                    }
phonetic_skip:
                    if ((dictionaryIndex & 0x8000) == 0) {
                        sound++;
                        while ((*sound & 0x80) == 0) {
                            sound += 2;
                        }
                        sound++;
                    }
                    break;
phonetic_matched:
                    if (++partIndex == numParts) {
                        if (partialMode != 0) {
                            if (strictMode == 0 && (dictionaryIndex & 0x8000) != 0) goto phonetic_skip;
                            if (strictMode != 0 && (dictionaryIndex & 0x8000) == 0) goto phonetic_skip;
                        }
                        *resultNode = node;
                        *resultCode = ((ziU16)node[6] << 8) + node[7];
                        *count = remaining;
                        return 1;
                    }
                } while ((dictionaryIndex & 0x8000) == 0);
            }
        }
        if ((nextCode & 0x80) != 0) goto next_node;
        goto next_group;
check_code:
        if (*values == (code & *masks)) goto match_code;
        goto next_node;
    }
    return 0;
}

ziBool Zi8GetPyFinal(ziU8* pinyin, ziU8* initial, ziU8* final);

ziU8 Zi8GetPyPhonetic(ziWChar* text, ziU8 count, ziU16* initial, ziU16* final, ziU8* resultCount, ziU16* bestInitial, ziU16* bestFinal ZI_NEED_WORK) {
    ziU8 pyInitial;
    ziU8 pyFinal;
    ziU8 convertedCount;
    ziU8 result;
    ziBool partial;
    ziBool alternateInitial;
    ziU8 outputIndex;
    ziU8 index;
    ziU16 value;
    ziWChar converted[256];
    ziU8 pinyin[12];
    ziWChar* current;

    current = converted;
    alternateInitial = 0;
    result = 0;
    *resultCount = 0;
    if (count == 0) {
        Zi8LogError(0x135, ZI_WORK);
        return 0;
    }
    index = 0;
    convertedCount = index;
    for (; index < count; index++) {
        if (((text[index] >= 0xF341) && (text[index] <= 0xF35A)) || ((text[index] >= 0x41) && (text[index] <= 0x5A))) {
            if ((convertedCount != 0) && (current[convertedCount - 1] != 0xF360) && (current[convertedCount - 1] != 0x27)) {
                current[convertedCount++] = 0x27;
            }
            current[convertedCount++] = (text[index] & 0xFF) + 0x20;
        } else {
            current[convertedCount++] = text[index];
        }
    }

    count = convertedCount;
    outputIndex = 0;
    *bestInitial = 0;
    *bestFinal = 0;
    while (count != 0) {
        initial[outputIndex] = 0;
        final[outputIndex] = 0;
        value = *current;
        if (value < 0x61) {
            goto check_pinyin_extension;
        }
        if (value <= 0x7A) {
            goto pinyin_ascii;
        }
check_pinyin_extension:
        if (value < 0xF361) {
            goto invalid_pinyin;
        }
        if (value <= 0xF37A) goto pinyin_extension;
invalid_pinyin:
        *bestInitial = *bestFinal = initial[0] = final[0] = 0xFFFF;
        return 1;
pinyin_extension:
        value -= 0xF361;
        goto pinyin_initial;
pinyin_ascii:
        value -= 0x61;
pinyin_initial:
        convertedCount = Zi8PinyinInitials[value];
        if (convertedCount != 0) {
            if (outputIndex == 0) {
                *resultCount += 1;
            }
            result++;
            initial[outputIndex] = 0x7E00;
            final[outputIndex] = (ziU16)(convertedCount & 0x7f) << 9;
            *bestInitial = initial[0];
            *bestFinal = final[0];
            count--;
            if (count == 0) {
                break;
            }
            current += 1;
            if ((convertedCount & 0x80) != 0) {
                if (alternateInitial) {
                    initial[outputIndex] &= 0xfdff;
                    final[outputIndex] &= 0xfdff;
                }
                value = *current;
                if (value != 0x68 && value != 0xF368) goto scan_final;
                if (outputIndex == 0) {
                    *resultCount += 1;
                }
                final[outputIndex] += 0x200;
                *bestInitial = initial[0];
                *bestFinal = final[0];
                count--;
                if (count == 0) {
                    break;
                }
                current += 1;
            }
        } else if ((*current == 0xF369) || (*current == 0x69)) {
            goto invalid_pinyin;
        }
scan_final:
        partial = 0;
        for (index = 0; index < 4; index++) {
            pinyin[index] = 0;
        }
        index = 0;
        while (index < 4) {
            value = *current;
            if ((value == 0x27) || (value == 0xF360) || (value == 0x20)) {
                if (index != 0) {
                    partial = 1;
                }
                goto finish_final;
            }
            if ((value >= 0xF331) && (value < 0xF336)) {
                if (index != 0) {
                    partial = 1;
                }
                goto finish_final;
            }
            if ((value < 0x61) || (value > 0x7A)) {
                if (value < 0xF361) {
                    goto finish_final;
                }
                value -= 0xF361;
                if (value > 0x19) {
                    if (outputIndex == 0) {
                        *resultCount += 1;
                    }
                    goto finish_final;
                }
            } else {
                value -= 0x61;
            }
            pinyin[index] = (ziU8)value + 1;
            if (!Zi8GetPyFinal(pinyin, &pyInitial, &pyFinal)) goto try_final_extension;
            if (outputIndex == 0) {
                *resultCount += 1;
            }
            current++;
            index++;
            count--;
            if (count == 0) {
                goto finish_final;
            }
            continue;
try_final_extension:

            if (index < 3) {
                pinyin[index + 1] = 0xFF;
                if (Zi8GetPyFinal(pinyin, &pyInitial, &pyFinal)) {
                    if (outputIndex == 0) {
                        *resultCount += 1;
                    }
                    pinyin[index + 1] = 0;
                    current++;
                    index++;
                    count--;
                    if (count == 0) break;
                } else {
                    pinyin[index + 1] = 0;
                    pinyin[index] = 0;
                    partial = 1;
                    break;
                }
            } else {
                pinyin[index] = 0;
                partial = 1;
                break;
            }
        }

finish_final:
        if ((index > 3) && (count != 0) && (((value = *current) == 0x27) || (value == 0xF360) || (value == 0x20))) {
            if (outputIndex == 0) {
                *resultCount += 1;
            }
            current++;
            count--;
        }
        if (index > 3) {
            partial = 1;
        }
        if (partial && alternateInitial == 0) {
            if (Zi8GetPyFinal(pinyin, &pyInitial, &pyFinal)) {
                if (convertedCount == 0) {
                    result++;
                    initial[outputIndex] = 0x7E00;
                    final[outputIndex] = 0x200;
                }
                initial[outputIndex] |= (ziU16)pyInitial << 3;
                final[outputIndex] |= (ziU16)pyFinal << 3;
                *bestInitial = initial[0];
                *bestFinal = final[0];
            } else {
                if ((index != 0) && (count != 0)) {
                    goto invalid_pinyin;
                }
            }
        } else {
            pinyin[index] = 0xFF;
            if (Zi8GetPyFinal(pinyin, &pyInitial, &pyFinal)) {
                if (convertedCount == 0) {
                    result++;
                    initial[outputIndex] = 0x7E00;
                    final[outputIndex] = 0x200;
                }
                initial[outputIndex] |= (ziU16)pyInitial << 3;
                final[outputIndex] |= (ziU16)pyFinal << 3;
                *bestInitial = initial[0];
                *bestFinal = final[0];
                if ((outputIndex == 0) && (count == 0)) {
                    pinyin[index] = 0;
                    if (Zi8GetPyFinal(pinyin, &pyInitial, &pyFinal)) {
                        if (convertedCount == 0) {
                            *bestInitial = 0x7E00;
                            *bestFinal = 0x200;
                        }
                        *bestInitial |= (ziU16)pyInitial << 3;
                        *bestFinal |= (ziU16)pyFinal << 3;
                    }
                }
            } else {
                pinyin[index] = 0;
                if (Zi8GetPyFinal(pinyin, &pyInitial, &pyFinal)) {
                    if (convertedCount == 0) {
                        result++;
                        initial[outputIndex] = 0x7E00;
                        final[outputIndex] = 0x200;
                    }
                    initial[outputIndex] |= (ziU16)pyInitial << 3;
                    final[outputIndex] |= (ziU16)pyFinal << 3;
                    *bestInitial = initial[0];
                    *bestFinal = final[0];
                }
            }
        }
        if (count != 0) {
            value = *current;
            if ((value == 0x27) || (value == 0xF360) || (value == 0x20)) {
                current++;
                count--;
                if (outputIndex == 0) {
                    *resultCount = *resultCount + 1;
                }
            } else if ((value >= 0xF331) && ((value -= 0xF331) <= 4)) {
                value++;
                initial[outputIndex] |= 7;
                final[outputIndex] |= value;
                *bestInitial = initial[0];
                *bestFinal = final[0];
                count--;
                current++;
                if (outputIndex == 0) {
                    *resultCount = *resultCount + 1;
                }
                if ((count != 0) && (((value = *current) == 0x27) || (value == 0xF360) || (value == 0x20))) {
                    count--;
                    current++;
                    if (outputIndex == 0) {
                        *resultCount = *resultCount + 1;
                    }
                }
            }
        }
        if (++outputIndex > 0xf) break;
    }
    if ((result > 1) && (text[*resultCount - 1] >= 0xF341) && (text[*resultCount - 1] <= 0xF35A)) {
        *resultCount -= 1;
    }
    return result;

}

ziBool Zi8GetPyFinal(ziU8* pinyin, ziU8* initial, ziU8* final) {
    ziU8 index = 0;
    ziU8 row;
    row = 0;
    goto check_row;
scan_row:
    while (index < 4) {
        if (pinyin[index] != Zi8PinyinFinals[row][index]) {
            break;
        }
        index++;
    }
    if (index < 4) {
        goto next_row;
    }
    *initial = Zi8PinyinFinals[row][4];
    *final = Zi8PinyinFinals[row][5];
    return 1;
next_row:
    row++;
    index = 0;
check_row:
    if (row < 0x36) {
        goto scan_row;
    }
    return 0;
}

ziU8 Zi8GetBpmfPhonetic(ziWChar* text, ziU8 count, ziU16* initial, ziU16* final, ziU16* bestInitial, ziU16* bestFinal ZI_NEED_WORK) {
    ziU16 value;
    ziU8 resultCount = 0;

    Zi8LogError(0x64, ZI_WORK);
    if (count == 0) {
        Zi8ReplaceLastError(0x135, ZI_WORK);
        return 0;
    }
    value = text[0];
    if (value < 0xF305) {
        Zi8ReplaceLastError(0x154, ZI_WORK);
        return 0;
    }
    value -= 0xF305;
    if (value >= 0x25) {
        Zi8ReplaceLastError(0x154, ZI_WORK);
        return 0;
    }
    if (value < 0x15) {
        *initial = 0x7E00;
        *final = ((ziU16)Zi8BpmfInitials[value] & 0x7F) << 9;
        resultCount++;
        if (--count == 0) {
            *bestInitial = *initial;
            *bestFinal = *final;
            if ((value >= 0xE) && (value <= 0x14)) {
                *bestInitial |= 0x1F8;
                *bestFinal |= 0x38;
            }
            return resultCount;
        }
        text++;
        if (*text == 0xF360) {
            resultCount++;
            if (--count == 0) {
                return resultCount;
            }
            Zi8ReplaceLastError(0x156, ZI_WORK);
            return 0;
        }
    } else {
        *initial = 0x7E00;
        *final = 0x200;
    }

    value = *text - 0xF305;
    switch ((ziS32)value) {
    case 0x22:
        goto bpmf_value_22;
    case 0x23:
        goto bpmf_value_23;
    case 0x24:
        goto bpmf_value_24;
    default:
        goto set_bpmf_initial;
    }
bpmf_value_22:
    *final |= 0x80;
    *initial |= 0x180;
    resultCount++;
    if (--count == 0) {
        *bestInitial = *initial | 0x78;
        *bestFinal = *final | 0x38;
        return resultCount;
    }
    text++;
    goto after_bpmf_initial;
bpmf_value_23:
    *final |= 0x100;
    *initial |= 0x180;
    resultCount++;
    if (--count == 0) {
        *bestInitial = *initial | 0x78;
        *bestFinal = *final | 0x38;
        return resultCount;
    }
    text++;
    goto after_bpmf_initial;
bpmf_value_24:
    *final |= 0x180;
    *initial |= 0x180;
    resultCount++;
    if (--count == 0) {
        *bestInitial = *initial | 0x78;
        *bestFinal = *final | 0x38;
        return resultCount;
    }
    text++;
    goto after_bpmf_initial;
set_bpmf_initial:
    if ((*text < 0xF331) || (*text > 0xF335)) {
        *initial |= 0x180;
    }
after_bpmf_initial:

    value = *text - 0xF305;
    if ((value > 0x14) && (value < 0x22)) {
        *final |= (ziU16)Zi8BpmfInitials[value] << 3;
        *initial |= 0x78;
        resultCount++;
        if (--count == 0) {
            *bestInitial = *initial;
            *bestFinal = *final;
            return resultCount;
        }
        text++;
    } else if ((*text < 0xF331) || (*text > 0xF335) || ((*initial & 0x180) == 0x180)) {
        *final |= 0x38;
        *initial |= 0x78;
    }

    value = *text;
    if (value < 0xF331) {
        Zi8ReplaceLastError(0x155, ZI_WORK);
        return 0;
    }
    value -= 0xF330;
    if (value > 5) {
        Zi8ReplaceLastError(0x155, ZI_WORK);
        return 0;
    }
    *initial |= 7;
    *final |= value;
    *bestInitial = *initial;
    *bestFinal = *final;
    resultCount++;
    if (--count != 0) {
        Zi8ReplaceLastError(0x157, ZI_WORK);
        return 0;
    }
    return resultCount;
}

ziU16 Zi8GetPCode(ziU8* table, ziU8* node) {
    ziU16 index = ((ziU16)node[8] << 2) | (((ziU16)node[9] & 0x80) >> 6);
    return ((((ziU16)node[9] >> 4) & 7) | (ziU16)table[index] | ((ziU16)table[index + 1] << 8));
}
