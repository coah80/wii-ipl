#include <zi8clib/zierror.h>

extern ziU16 Zi8GetTableCount(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);
extern ziU32 Zi8GetTableAddress(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);

typedef struct {
    ziU8 keyBytes[5];
    ziU8 childHigh;
    ziU8 childLow;
    ziU8 characterHigh;
    ziU8 characterLow;
} ZiKoreanKeyEntry;

ziU32 Zi8_8148302C(ziU16 key, ziU8* table ZI_NEED_WORK) {
    ziU32 value;
    ziU16 count;
    ziU32 i;

    count = Zi8GetTableCount(ZI8_LANG_KO, 9, ZI_WORK);
    for (i = 0; (ziU16)i < count; i++) {
        value = (ziU16)(((ziU16)table[((i & 0xFFFF) << 3) + (i & 0xFFFF) + 7] << 8) |
                       table[((i & 0xFFFF) << 3) + (i & 0xFFFF) + 8]);
        if (value == key) {
            Zi8LogError(0x64, ZI_WORK);
            return i;
        }
    }

    Zi8LogError(0x96A, ZI_WORK);
    return 0xFFFF;
}

void Zi8_81483118(ziGetParam* param, ziU8* output) {
    ziU8 i;

    for (i = 0; i < 5; i++) {
        output[i] = 0;
    }

    switch (param->elementCount) {
    case 9:
        output[4] |= (ziU8)((param->elements[8] & 0xF) << 4);
    case 8:
        output[3] = param->elements[7] & 0xF;
    case 7:
        output[3] |= (ziU8)((param->elements[6] & 0xF) << 4);
    case 6:
        output[2] = param->elements[5] & 0xF;
    case 5:
        output[2] |= (ziU8)((param->elements[4] & 0xF) << 4);
    case 4:
        output[1] = param->elements[3] & 0xF;
    case 3:
        output[1] |= (ziU8)((param->elements[2] & 0xF) << 4);
    case 2:
        output[0] = param->elements[1] & 0xF;
    case 1:
        output[0] |= (ziU8)((param->elements[0] & 0xF) << 4);
    case 0:
        break;
    }
}

ziU32 Zi8_81483264(const ziGetParam* param ZI_NEED_WORK) {
    ziU8 i;

    if (param->scratch == ZI8_NULL) {
        Zi8LogError(0x164, ZI_WORK);
        return 1;
    }

    for (i = 0; i < param->maxCandidates; i++) {
        ((ziU16*)param->scratch)[i] = 0;
    }

    Zi8LogError(0x64, ZI_WORK);
    return 0;
}

ziU32 Zi8_81483308(ziGetParam* param, ziU16 key, ziU8* count ZI_NEED_WORK) {
    ziU8 i;

    Zi8LogError(0x64, ZI_WORK);
    if (param->scratch == ZI8_NULL) {
        Zi8ReplaceLastError(0x164, ZI_WORK);
        return 1;
    }

    for (i = 0; i < param->maxCandidates; i++) {
        if (key == ((ziU16*)param->scratch)[i]) {
            return 1;
        }
    }

    ((ziU16*)param->scratch)[*count] = key;
    if (++*count >= param->maxCandidates) {
        *count = 0;
    }
    return 0;
}

ziBool Zi8_814833F0(const ziGetParam* param, ziU16 key ZI_NEED_WORK) {
    ziU8 i;

    Zi8LogError(0x64, ZI_WORK);
    if (param->scratch == ZI8_NULL) {
        Zi8ReplaceLastError(0x164, ZI_WORK);
        return 0;
    }

    for (i = 0; i < param->maxCandidates; i++) {
        if (key == ((ziU16*)param->scratch)[i]) {
            return 1;
        }
    }

    return 0;
}

ziU32 Zi8_814834AC(ziGetParam* param, ziU16* remaining, ziU8* count,
                   ziU8* inserted ZI_NEED_WORK) {
    ziBool matches;
    ZiKoreanKeyEntry* entry;
    ziU8* tableA;
    ziU8* tableB;
    ziU16 tableCount;
    ziU8 matched;
    ziU32 j;
    ziS32 i;
    ziS32 candidate;
    ziU8 candidateIndex;
    union {
        ziU32 firstWord;
        ziU8 bytes[5];
    } local;

    j = 0;
    candidateIndex = 0;
    matched = 0;
    local.firstWord = 0;
    local.bytes[4] = 0;
    Zi8LogError(0x64, ZI_WORK);
    if (param->elementCount == 0) {
        if (*remaining >= *count) {
            for (i = 0; i < *count; i++) {
                Zi8_81483308(param, param->candidates[i], inserted, ZI_WORK);
            }
            *remaining = *remaining - *count;
            *count = 0;
        } else {
            for (i = 0; i < *remaining; i++) {
                Zi8_81483308(param, param->candidates[i], inserted, ZI_WORK);
            }
            for (i = 0; i < ((ziS32)*count - (ziS32)*remaining); i++) {
                param->candidates[i] = param->candidates[*remaining + i];
            }
            *count = *count - (ziU8)*remaining;
            *remaining = 0;
        }
        return 1;
    } else if (param->elementCount <= 9) {
        tableA = (ziU8*)Zi8GetTableAddress(param->language, 9, ZI_WORK);
        tableB = (ziU8*)Zi8GetTableAddress(param->language, 10, ZI_WORK);
        if (tableA == 0) {
            Zi8ReplaceLastError(0x76C, ZI_WORK);
            return 0;
        } else if (tableB == 0) {
            Zi8ReplaceLastError(0x776, ZI_WORK);
            return 0;
        } else {
            tableCount = Zi8GetTableCount(ZI8_LANG_KO, 9, ZI_WORK);
            Zi8_81483118(param, local.bytes);
            i = 0;
            while (i < tableCount && matched < *count) {
                matches = ZI8_TRUE;
                entry = (ZiKoreanKeyEntry*)&tableA[(i << 3) + i];
                j = 0;
                if (param->elementCount > 1) {
                    for (j = 0; (j & 0xFF) < (int)param->elementCount / 2; j++) {
                        if (local.bytes[j & 0xFF] != entry->keyBytes[j & 0xFF]) {
                            matches = ZI8_FALSE;
                            break;
                        }
                    }
                }
                if (matches && (param->elementCount % 2) != 0 &&
                    ((local.bytes[j & 0xFF] & 0xF0) != (entry->keyBytes[j & 0xFF] & 0xF0))) {
                    matches = ZI8_FALSE;
                }
                if (matches) {
                    for (candidateIndex = 0; candidateIndex < *count; candidateIndex++) {
                        if (param->candidates[candidateIndex] ==
                            (((ziU16)((ZiKoreanKeyEntry*)tableA)[i].characterHigh << 8) | (ziU16)((ZiKoreanKeyEntry*)tableA)[i].characterLow)) {
                            matched++;
                            param->candidates[candidateIndex] =
                                param->candidates[candidateIndex] & 0x7FFF;
                            break;
                        }
                    }
                }
                i++;
            }
            if (matched >= *remaining) {
                matched = *count;
                *count = 0;
                for (candidate = 0; candidate < matched; candidate++) {
                    if ((param->candidates[candidate] & 0x8000) == 0) {
                        param->candidates[candidate] = param->candidates[candidate] | 0x8000;
                        if (*remaining != 0) {
                            *remaining = *remaining - 1;
                            Zi8_81483308(param, param->candidates[candidate], inserted, ZI_WORK);
                        } else {
                            if (*count != candidate) {
                                param->candidates[*count] = param->candidates[candidate];
                            }
                            *count = *count + 1;
                        }
                    }
                }
                *remaining = 0;
            } else {
                for (candidate = 0; candidate < *count; candidate++) {
                    if ((param->candidates[candidate] & 0x8000) == 0) {
                        param->candidates[candidate] = param->candidates[candidate] | 0x8000;
                        Zi8_81483308(param, param->candidates[candidate], inserted, ZI_WORK);
                    }
                }
                *remaining = *remaining - (ziU8)matched;
                *count = 0;
            }
        }
    } else {
        *count = 0;
        return 0;
    }

    return 0;
}

typedef struct {
    ziU8 countOnly;
    ziU8 maxWordLength;
    ziU8 lookupMode;
    ziU8 suffixOnly;
    ziU8 controls[8];
    ziU32 maxCount;
    ziU16 capacity;
    ziU8 minWordLength;
    ziU8 flags;
    ziU16 candidateCapacity;
    ziU8 checkOnly;
    ziU8 reserved;
} ZiKoreanCandidateOptions;

ziU32 Zi8GetKOcandidates(ziGetParam* param, ZiKoreanCandidateOptions* options ZI_NEED_WORK) {
    ziBool matches;
    ziU8 letterCount;
    ziU8* keyTable;
    ziU32 result;
    ziU8* wordNode;
    union {
        ziU32 firstWord;
        ziU8 bytes[5];
    } packedKeys;
    ziU8 inserted;
    ziU8 matchPass;
    ziU8 keyByte;
    ziU8 candidateCount;
    ziU8 wordIndex;
    ziS8 remainingLetters;
    ziU16 remainingCandidates;
    ziU16 previousIndex;
    ziU16 character;
    ziU16 tableCount;
    ziU16 keyIndex;
    ZiKoreanKeyEntry* entry;
    ziU8* wordTable;
    ziS32 tableIndex;
    ziU32 resultCount;
    ziU32 wordOffset;
    ziU32 prefixCount;
    ziU32 candidateIndex;

    previousIndex = 0xFFFF;
    resultCount = 0;
    packedKeys.firstWord = 0;
    packedKeys.bytes[4] = 0;
    remainingLetters = 0;
    wordIndex = 0;
    candidateCount = 0;
    keyByte = 0;
    remainingCandidates = param->firstCandidate;
    prefixCount = 0;
    candidateIndex = 0;
    inserted = 0;
    Zi8LogError(100, ZI_WORK);
    Zi8_81483264(param, ZI_WORK);
    keyTable = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 9, ZI_WORK);
    wordTable = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 10, ZI_WORK);
    if (keyTable == 0) {
        Zi8ReplaceLastError(0x76C, ZI_WORK);
        return 0;
    } else {
        if (wordTable == 0) {
            Zi8ReplaceLastError(0x776, ZI_WORK);
            return 0;
        }
        if (options->countOnly == 0) {
            param->letters = 0;
            param->count = 0;
            param->candidates[0] = 0;
        }
        Zi8LogError(100, ZI_WORK);
        if (param->wordCharCount != 0) {
            keyIndex = Zi8_8148302C(param->currentWord[0], (ziU8*)keyTable, ZI_WORK);
            if ((keyIndex != 0xFFFF) &&
                ((((ZiKoreanKeyEntry*)&keyTable[(keyIndex << 3) + keyIndex])->keyBytes[4] & 8) != 0)) {
                wordOffset = (ziU32)((ZiKoreanKeyEntry*)&keyTable[(keyIndex << 3) + keyIndex])->childLow |
                           ((ziU32)((ZiKoreanKeyEntry*)&keyTable[(keyIndex << 3) + keyIndex])->keyBytes[4] & 3) << 16 |
                           (ziU32)((ZiKoreanKeyEntry*)&keyTable[(keyIndex << 3) + keyIndex])->childHigh << 8;
                remainingLetters = param->wordCharCount - 1;
                wordIndex = 1;
                wordNode = wordTable + wordOffset;
match_word:
                if (remainingLetters != 0) {
                    keyIndex = Zi8_8148302C(param->currentWord[wordIndex], (ziU8*)keyTable, ZI_WORK);
                    if (keyIndex == (ziU16)((*wordNode & 0x1F) << 8 | wordNode[1])) {
                        remainingLetters = remainingLetters - 1;
                        wordIndex = wordIndex + 1;
                        if ((*wordNode & 0x40) == 0) {
                            wordNode = wordNode + 2;
                            goto match_word;
                        }
                        remainingLetters = param->wordCharCount - 1;
                        wordIndex = 1;
                    } else {
                        wordIndex = 1;
                        remainingLetters = param->wordCharCount - 1;
                    }
                }
                if (remainingLetters == 0) {
                    keyIndex = (*wordNode & 0x1F) << 8 | wordNode[1];
                    character = (ziU16)(((ZiKoreanKeyEntry*)&keyTable[(keyIndex << 3) + keyIndex])->characterHigh << 8 |
                                       ((ZiKoreanKeyEntry*)&keyTable[(keyIndex << 3) + keyIndex])->characterLow);
                    if (param->wordCharCount == 1) {
                        if (keyIndex == previousIndex) {
                            for (; (*wordNode & 0x40) == 0; wordNode = wordNode + 2) {
                            }
                            remainingLetters = param->wordCharCount;
                            goto next_word;
                        }
                        previousIndex = keyIndex;
                        if (param->elementCount == 0) {
                            if (remainingCandidates == 0) {
                                if (options->countOnly != 0) {
                                    prefixCount = prefixCount + 1;
                                    if ((ziS32)prefixCount < (ziS32)options->maxCount) {
                                        goto skip_word;
                                    }
                                    return options->maxCount;
                                }
                                param->candidates[candidateCount] = character;
                                candidateCount = candidateCount + 1;
                                param->count = param->count + 1;
                                letterCount = param->letters + 1;
                                param->letters = letterCount;
                                if (param->maxCandidates <= letterCount) {
                                    return param->letters;
                                }
                            } else {
                                remainingCandidates = remainingCandidates + -1;
                            }
                        } else {
                            param->candidates[candidateCount] = character;
                            candidateCount = candidateCount + 1;
                            param->count = param->count + 1;
                            letterCount = param->letters + 1;
                            param->letters = letterCount;
                            if (param->maxCandidates <= letterCount) {
                                Zi8_814834AC(param, &remainingCandidates, &candidateCount, &inserted, ZI_WORK);
                                param->count = candidateCount;
                                param->letters = candidateCount;
                                if (param->maxCandidates <= candidateCount) {
                                    if (options->countOnly == 0) {
                                        return candidateCount;
                                    }
                                    prefixCount = prefixCount + candidateCount;
                                    if ((ziS32)options->maxCount <= (ziS32)prefixCount) {
                                        return options->maxCount;
                                    }
                                    param->count = 0;
                                    param->letters = 0;
                                    candidateCount = 0;
                                }
                            }
                        }
                    } else {
                        for (candidateIndex = 0;
                             (candidateIndex < candidateCount &&
                              (character != param->candidates[candidateIndex]));
                             candidateIndex = candidateIndex + 1) {
                        }
                        if ((candidateIndex == candidateCount) &&
                            (Zi8_814833F0(param, character, ZI_WORK) == 0)) {
                            param->candidates[candidateCount] = character;
                            candidateCount = candidateCount + 1;
                            param->count = param->count + 1;
                            letterCount = param->letters + 1;
                            param->letters = letterCount;
                            if (letterCount < param->maxCandidates) {
                                goto skip_word;
                            }
                            Zi8_814834AC(param, &remainingCandidates, &candidateCount, &inserted, ZI_WORK);
                            param->count = candidateCount;
                            param->letters = candidateCount;
                            if (param->maxCandidates <= candidateCount) {
                                if (options->countOnly == 0) {
                                    return candidateCount;
                                }
                                prefixCount = prefixCount + candidateCount;
                                if ((ziS32)options->maxCount <= (ziS32)prefixCount) {
                                    return options->maxCount;
                                }
                                param->count = 0;
                                param->letters = 0;
                                candidateCount = 0;
                            }
                        }
                    }
                }
skip_word:
                for (; (*wordNode & 0x40) == 0; wordNode = wordNode + 2) {
                }
                remainingLetters = param->wordCharCount;
next_word:
                remainingLetters = remainingLetters + -1;
                wordIndex = 1;
                wordNode = wordNode + 2;
                if ((*wordNode & 0x80) != 0) {
                    goto search_table;
                }
                goto match_word;
            }
        }
search_table:
        resultCount = prefixCount;
        if (candidateCount != 0) {
            Zi8_814834AC(param, &remainingCandidates, &candidateCount, &inserted, ZI_WORK);
            result = resultCount;
            if ((options->countOnly != 0) &&
                (prefixCount = prefixCount + candidateCount, result = prefixCount,
                 (ziS32)options->maxCount <= (ziS32)prefixCount)) {
                return options->maxCount;
            }
            resultCount = result;
            param->count = candidateCount;
            param->letters = candidateCount;
        }
        if (param->elementCount < 10) {
            if ((param->elementCount == 0) || (options->countOnly != 0)) {
                matchPass = 1;
            } else {
                matchPass = 0;
            }
            tableCount = Zi8GetTableCount(ZI8_LANG_KO, 9, ZI_WORK);
            Zi8_81483118(param, packedKeys.bytes);
            do {
                for (tableIndex = 0; tableIndex < (ziS32)(ziU32)tableCount; tableIndex = tableIndex + 1) {
                    matches = ZI8_TRUE;
                    entry = (ZiKoreanKeyEntry*)&keyTable[(tableIndex << 3) + tableIndex];
                    keyByte = 0;
                    if (1 < param->elementCount) {
                        for (keyByte = 0;
                             (ziU32)keyByte < (int)param->elementCount / 2;
                             keyByte = keyByte + 1) {
                            if (packedKeys.bytes[keyByte] != entry->keyBytes[keyByte]) {
                                matches = ZI8_FALSE;
                                break;
                            }
                        }
                    }
                    if ((matches && ((param->elementCount % 2) != 0)) &&
                        ((packedKeys.bytes[keyByte] & 0xF0) !=
                         (entry->keyBytes[keyByte] & 0xF0))) {
                        matches = ZI8_FALSE;
                    }
                    if (matches) {
                        letterCount = matchPass;
                        if ((param->elementCount % 2) == 0) {
                            if ((entry->keyBytes[keyByte] & 0xF0) == 0) {
                                if (matchPass == 0) {
                                    goto add_candidate;
                                }
                                letterCount = options->countOnly;
                            }
                            if (letterCount == 0) {
                                goto next_entry;
                            }
                        } else {
                            if ((entry->keyBytes[keyByte] & 0xF) != 0) {
                                goto check_pass;
                            }
                            if (matchPass != 0) {
                                letterCount = options->countOnly;
                                goto check_pass;
                            }
                        }
check_pass:
                        if (letterCount == 0) {
                            goto next_entry;
                        }
add_candidate:
                        if (remainingCandidates == 0) {
                            if (options->countOnly == 0) {
                                param->candidates[candidateCount] =
                                    (ziU16)((((ZiKoreanKeyEntry*)&keyTable[(tableIndex << 3) + tableIndex])->characterHigh << 8) |
                                            ((ZiKoreanKeyEntry*)&keyTable[(tableIndex << 3) + tableIndex])->characterLow);
                                candidateCount = candidateCount + 1;
                                letterCount = param->letters + 1;
                                param->letters = letterCount;
                                if (param->maxCandidates <= letterCount) {
                                    return param->letters;
                                }
                            } else {
                                resultCount = resultCount + 1;
                                if ((ziS32)options->maxCount <= (ziS32)resultCount) {
                                    return options->maxCount;
                                }
                            }
                        } else {
                            remainingCandidates = remainingCandidates + -1;
                        }
                    }
next_entry:
                    ;
                }
                matchPass = matchPass + 1;
            } while (matchPass < 2);
            result = resultCount;
            if (options->countOnly == 0) {
                result = param->letters;
            }
        } else {
            param->letters = 0;
            return 0;
        }
    }
finish_candidates:
    return result;
}
