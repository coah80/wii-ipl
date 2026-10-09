#include <stddef.h>
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

ziU16 Zi8_8148302C(ziU16 key, ziU8* table ZI_NEED_WORK) {
    ziU16 count;
    ziU16 value;
    ziU16 i;

    count = Zi8GetTableCount(ZI8_LANG_KO, 9, ZI_WORK);
    for (i = 0; i < count; i++) {
        value = (ziU16)(((ziU16)table[(i << 3) + i + 7] << 8) |
                       table[(i << 3) + i + 8]);
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

ziU32 Zi8_814833F0(const ziGetParam* param, ziU16 key ZI_NEED_WORK) {
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
    ziU8* tableA;
    ziU8* tableB;
    ZiKoreanKeyEntry* entry;
    ziS32 compactIndex;
    ziU16 tableCount;
    ziU32 j = 0;
    ziU8 candidateIndex = 0;
    ziU8 matched = 0;
    ziBool matches;
    ziU8 keys[5] = {0};
    ziS32 i;
    ziS32 candidate;

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
            *count -= *remaining;
            *remaining = 0;
        }
        return 1;
    }
    if (param->elementCount > 9) {
        *count = 0;
        return 0;
    }

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
            Zi8_81483118(param, keys);
            i = 0;
            while (i < tableCount && matched < *count) {
                matches = ZI8_TRUE;
                entry = (ZiKoreanKeyEntry*)&tableA[(i << 3) + i];
                j = 0;
                if (param->elementCount > 1) {
                    for (j = 0; (int)(j & 0xFF) < (int)param->elementCount / 2; j++) {
                        if (keys[j & 0xFF] != entry->keyBytes[j & 0xFF]) {
                            matches = ZI8_FALSE;
                            break;
                        }
                    }
                }
                if (matches && (param->elementCount % 2) != 0 &&
                    ((keys[j & 0xFF] & 0xF0) != (entry->keyBytes[j & 0xFF] & 0xF0))) {
                    matches = ZI8_FALSE;
                }
                if (matches) {
                    for (candidateIndex = 0; candidateIndex < *count; candidateIndex++) {
                        if (param->candidates[candidateIndex] ==
                            (((ziU16)tableA[i * sizeof(ZiKoreanKeyEntry) + offsetof(ZiKoreanKeyEntry, characterHigh)] << 8) |
                             (ziU16)tableA[i * sizeof(ZiKoreanKeyEntry) + offsetof(ZiKoreanKeyEntry, characterLow)])) {
                            matched++;
                            param->candidates[candidateIndex] &= 0x7FFF;
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
                        param->candidates[candidate] |= 0x8000;
                        if (*remaining != 0) {
                            --*remaining;
                            Zi8_81483308(param, param->candidates[candidate], inserted, ZI_WORK);
                        } else {
                            if (*count != candidate) {
                                param->candidates[*count] = param->candidates[candidate];
                            }
                            ++*count;
                        }
                    }
                }
                *remaining = 0;
            } else {
                for (compactIndex = 0; compactIndex < *count; compactIndex++) {
                    if ((param->candidates[compactIndex] & 0x8000) == 0) {
                        param->candidates[compactIndex] |= 0x8000;
                        Zi8_81483308(param, param->candidates[compactIndex], inserted, ZI_WORK);
                    }
                }
                *remaining = *remaining - matched;
                *count = 0;
            }
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
    ziU8* wordTable;
    ziS32 tableIndex;
    ziS32 resultCount;
    ziU32 wordOffset;
    ziS32 prefixCount;
    ziS32 candidateIndex;
    ZiKoreanKeyEntry* entry;
    ziU16 keyIndex;
    ziU16 tableCount;
    ziU16 character;
    ziU16 previousIndex;
    ziU16 remainingCandidates;
    ziU8 remainingLetters;
    ziU8 wordIndex;
    ziU8 candidateCount;
    ziU8 keyByte;
    ziU8 matchPass;
    ziU8 inserted;
    ziBool matches;
    ziU8* keyTable;
    ziU8* wordNode;

    previousIndex = 0xFFFF;
    resultCount = 0;
    {
        ziU8 packedKeys[5] = {0};

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
                {
                    if (((keyIndex = Zi8_8148302C(param->currentWord[0], keyTable, ZI_WORK)) != 0xFFFF) &&
                        ((keyTable[(keyIndex << 3) + keyIndex + offsetof(ZiKoreanKeyEntry, keyBytes[4])] & 8) != 0)) {
                        wordOffset = keyTable[(keyIndex << 3) + keyIndex + offsetof(ZiKoreanKeyEntry, childLow)] |
                            ((keyTable[(keyIndex << 3) + keyIndex + offsetof(ZiKoreanKeyEntry, keyBytes[4])] & 3) << 16 |
                             keyTable[(keyIndex << 3) + keyIndex + offsetof(ZiKoreanKeyEntry, childHigh)] << 8);
                        remainingLetters = param->wordCharCount - 1;
                        wordIndex = 1;
                        wordNode = wordTable + wordOffset;
match_word:
                        while (remainingLetters != 0) {
                            keyIndex = Zi8_8148302C(param->currentWord[wordIndex], keyTable, ZI_WORK);
                            if (keyIndex == (((ziU16)*wordNode & 0x1F) << 8 | (ziU16)wordNode[1])) {
                                --remainingLetters;
                                ++wordIndex;
                                if ((*wordNode & 0x40) != 0) {
                                    remainingLetters = param->wordCharCount - 1;
                                    wordIndex = 1;
                                    break;
                                }
                                wordNode += 2;
                            } else {
                                wordIndex = 1;
                                remainingLetters = param->wordCharCount - 1;
                                break;
                            }
                        }
                        if (remainingLetters == 0) {
                            keyIndex = ((ziU16)*wordNode & 0x1F) << 8 | (ziU16)wordNode[1];
                            character = (ziU16)((ziU16)keyTable[(keyIndex << 3) + keyIndex + offsetof(ZiKoreanKeyEntry, characterHigh)] << 8 |
                                keyTable[(keyIndex << 3) + keyIndex + offsetof(ZiKoreanKeyEntry, characterLow)]);
                            if (param->wordCharCount == 1) {
                                if (keyIndex == previousIndex) {
                                    for (; (*wordNode & 0x40) == 0; wordNode = wordNode + 2) {
                                    }
                                    wordNode += 2;
                                    remainingLetters = param->wordCharCount - 1;
                                    wordIndex = 1;
                                    goto next_word;
                                }
                                previousIndex = keyIndex;
                                if (param->elementCount == 0) {
                                    if (remainingCandidates != 0) {
                                        --remainingCandidates;
                                    } else {
                                        if (options->countOnly != 0) {
                                            if (++prefixCount < (ziS32)options->maxCount) {
                                                goto skip_word;
                                            }
                                            return options->maxCount;
                                        }
                                        param->candidates[candidateCount++] = character;
                                        ++param->count;
                                        if (++param->letters >= param->maxCandidates) {
                                            return param->letters;
                                        }
                                    }
                                } else {
                                    param->candidates[candidateCount++] = character;
                                    ++param->count;
                                    if (++param->letters >= param->maxCandidates) {
                                        Zi8_814834AC(param, &remainingCandidates, &candidateCount, &inserted, ZI_WORK);
                                        param->count = candidateCount;
                                        param->letters = candidateCount;
                                        if (candidateCount < param->maxCandidates) goto skip_word;
                                        if (options->countOnly != 0) {
                                            if ((prefixCount += candidateCount) >= (ziS32)options->maxCount) return options->maxCount;
                                            param->count = 0;
                                            param->letters = 0;
                                            candidateCount = 0;
                                        } else {
                                            return candidateCount;
                                        }
                                    }
                                }
                            } else {
                                for (candidateIndex = 0; candidateIndex < candidateCount; candidateIndex++) {
                                    if (character == param->candidates[candidateIndex]) break;
                                }
                                if ((candidateIndex == candidateCount) &&
                                    (Zi8_814833F0(param, character, ZI_WORK) == 0)) {
                                    param->candidates[candidateCount++] = character;
                                    ++param->count;
                                    if (++param->letters >= param->maxCandidates) {
                                        Zi8_814834AC(param, &remainingCandidates, &candidateCount, &inserted, ZI_WORK);
                                        param->count = candidateCount;
                                        param->letters = candidateCount;
                                        if (candidateCount >= param->maxCandidates) {
                                            if (options->countOnly != 0) {
                                                if ((prefixCount += candidateCount) >= (ziS32)options->maxCount) return options->maxCount;
                                                param->count = 0;
                                                param->letters = 0;
                                                candidateCount = 0;
                                            } else {
                                                return candidateCount;
                                            }
                                        }
                                    }
                                }
                            }
                        }
skip_word:
                        for (; (*wordNode & 0x40) == 0; wordNode = wordNode + 2) {
                        }
                        wordNode += 2;
                        remainingLetters = param->wordCharCount - 1;
                        wordIndex = 1;
next_word:
                        if ((*wordNode & 0x80) == 0) {
                            goto match_word;
                        }
                    }
                }
                resultCount = prefixCount;
                if (candidateCount != 0) {
                    Zi8_814834AC(param, &remainingCandidates, &candidateCount, &inserted, ZI_WORK);
                    if (options->countOnly != 0) {
                        if ((prefixCount += candidateCount) >= (ziS32)options->maxCount) return options->maxCount;
                        resultCount = prefixCount;
                    }
                    param->count = candidateCount;
                    param->letters = candidateCount;
                }
            }
            if (param->elementCount > 9) {
                param->letters = 0;
                return 0;
            }
            {
                if (param->elementCount != 0 && options->countOnly == 0) {
                    matchPass = 0;
                } else {
                    matchPass = 1;
                }
                tableCount = Zi8GetTableCount(ZI8_LANG_KO, 9, ZI_WORK);
                Zi8_81483118(param, packedKeys);
                do {
                    for (tableIndex = 0; tableIndex < tableCount; tableIndex = tableIndex + 1) {
                        matches = ZI8_TRUE;
                        entry = (ZiKoreanKeyEntry*)(((tableIndex << 3) + tableIndex) + keyTable);
                        keyByte = 0;
                        if (1 < param->elementCount) {
                            for (keyByte = 0;
                                (ziS32)keyByte < (int)param->elementCount / 2;
                                keyByte++) {
                                if (packedKeys[keyByte] != entry->keyBytes[keyByte]) {
                                    matches = ZI8_FALSE;
                                    break;
                                }
                            }
                        }
                        if ((matches && ((param->elementCount % 2) != 0)) &&
                            ((packedKeys[keyByte] & 0xF0) !=
                            (entry->keyBytes[keyByte] & 0xF0))) {
                            matches = ZI8_FALSE;
                        }
                        if (matches) {
                            if (param->elementCount % 2 != 0) {
                                if ((entry->keyBytes[keyByte] & 0xF) != 0) {
                                    if (matchPass == 0) goto next_entry;
                                } else if (matchPass != 0 && options->countOnly == 0) {
                                    goto next_entry;
                                }
                            } else {
                                if ((entry->keyBytes[keyByte] & 0xF0) != 0) {
                                    if (matchPass == 0) goto next_entry;
                                } else if (matchPass != 0 && options->countOnly == 0) {
                                    goto next_entry;
                                }
                            }
                            if (remainingCandidates != 0) {
                                --remainingCandidates;
                            } else if (options->countOnly != 0) {
                                if (++resultCount >= (ziS32)options->maxCount) return options->maxCount;
                            } else {
                            param->candidates[candidateCount++] =
                                (ziU16)((ziU16)keyTable[(tableIndex << 3) + tableIndex + offsetof(ZiKoreanKeyEntry, characterHigh)] << 8 |
                                    keyTable[(tableIndex << 3) + tableIndex + offsetof(ZiKoreanKeyEntry, characterLow)]);
                                if (++param->letters >= param->maxCandidates) return param->letters;
                            }
                        }
next_entry:
                        ;
                    }
                } while (++matchPass < 2);
            }
            if (options->countOnly != 0) return resultCount;
            return param->letters;
        }
        return 0;
    }
}
