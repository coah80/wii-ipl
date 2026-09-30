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
    struct {
        ziBool matches;
        ziU8 candidateIndex;
        ziU16 tableCount;
        ziS32 compactIndex;
        ZiKoreanKeyEntry* entry;
        ziU8* tableB;
        ziU8* tableA;
        union {
            ziU32 firstWord;
            ziU8 bytes[5];
        } keys;
    } filter;
    ziU32 j;
    ziS32 i;
    ziS32 candidate;
    ziU8 matched;

    j = 0;
    filter.candidateIndex = 0;
    matched = 0;
    filter.keys.bytes[4] = filter.keys.firstWord = 0;
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

        filter.tableA = (ziU8*)Zi8GetTableAddress(param->language, 9, ZI_WORK);
        filter.tableB = (ziU8*)Zi8GetTableAddress(param->language, 10, ZI_WORK);
        if (filter.tableA == 0) {
            Zi8ReplaceLastError(0x76C, ZI_WORK);
            return 0;
        } else if (filter.tableB == 0) {
            Zi8ReplaceLastError(0x776, ZI_WORK);
            return 0;
        } else {
            filter.tableCount = Zi8GetTableCount(ZI8_LANG_KO, 9, ZI_WORK);
            Zi8_81483118(param, filter.keys.bytes);
            i = 0;
            while (i < filter.tableCount && matched < *count) {
                filter.matches = ZI8_TRUE;
                filter.entry = (ZiKoreanKeyEntry*)&filter.tableA[(i << 3) + i];
                j = 0;
                if (param->elementCount > 1) {
                    for (j = 0; (int)(j & 0xFF) < (int)param->elementCount / 2; j++) {
                        if (filter.keys.bytes[j & 0xFF] != filter.entry->keyBytes[j & 0xFF]) {
                            filter.matches = ZI8_FALSE;
                            break;
                        }
                    }
                }
                if (filter.matches && (param->elementCount % 2) != 0 &&
                    ((filter.keys.bytes[j & 0xFF] & 0xF0) != (filter.entry->keyBytes[j & 0xFF] & 0xF0))) {
                    filter.matches = ZI8_FALSE;
                }
                if (filter.matches) {
                    for (filter.candidateIndex = 0; filter.candidateIndex < *count; filter.candidateIndex++) {
                        if (param->candidates[filter.candidateIndex] ==
                            (((ziU16)((ZiKoreanKeyEntry*)filter.tableA)[i].characterHigh << 8) | (ziU16)((ZiKoreanKeyEntry*)filter.tableA)[i].characterLow)) {
                            matched++;
                            param->candidates[filter.candidateIndex] &= 0x7FFF;
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
                for (filter.compactIndex = 0; filter.compactIndex < *count; filter.compactIndex++) {
                    if ((param->candidates[filter.compactIndex] & 0x8000) == 0) {
                        param->candidates[filter.compactIndex] |= 0x8000;
                        Zi8_81483308(param, param->candidates[filter.compactIndex], inserted, ZI_WORK);
                    }
                }
                *remaining -= (ziU8)matched;
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
    struct {
        ziBool matches;
        ziU8 inserted;
        ziU8 matchPass;
        ziU8 keyByte;
        ziU8 candidateCount;
        ziU8 wordIndex;
        ziU8 remainingLetters;
        ziU16 remainingCandidates;
        ziU16 previousIndex;
        ziU16 character;
        ziU16 tableCount;
        ziU16 keyIndex;
        ZiKoreanKeyEntry* entry;
        ziS32 candidateIndex;
        ziS32 prefixCount;
        ziU32 wordOffset;
        ziS32 resultCount;
        ziS32 tableIndex;
        ziU8* wordTable;
        union {
            ziU32 firstWord;
            ziU8 bytes[5];
        } packedKeys;
    } search;
    ziU8* keyTable;
    ziU8* wordNode;

    search.previousIndex = 0xFFFF;
    search.resultCount = 0;
    search.packedKeys.bytes[4] = 0;
    search.packedKeys.firstWord = 0;
    search.remainingLetters = 0;
    search.wordIndex = 0;
    search.candidateCount = 0;
    search.keyByte = 0;
    search.remainingCandidates = param->firstCandidate;
    search.prefixCount = 0;
    search.candidateIndex = 0;
    search.inserted = 0;
    Zi8LogError(100, ZI_WORK);
    Zi8_81483264(param, ZI_WORK);
    keyTable = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 9, ZI_WORK);
    search.wordTable = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 10, ZI_WORK);
    if (keyTable == 0) {
        Zi8ReplaceLastError(0x76C, ZI_WORK);
        return 0;
    } else {
        if (search.wordTable == 0) {
            Zi8ReplaceLastError(0x776, ZI_WORK);
            return 0;
        }
        if (options->countOnly == 0) {
            param->letters = 0;
            param->unk_0x20 = 0;
            param->candidates[0] = 0;
        }
        Zi8LogError(100, ZI_WORK);
        if (param->wordCharCount != 0) {
            if (((search.keyIndex = Zi8_8148302C(param->currentWord[0], keyTable, ZI_WORK)) != 0xFFFF) &&
                ((((ZiKoreanKeyEntry*)(((search.keyIndex << 3) + search.keyIndex) + keyTable))->keyBytes[4] & 8) != 0)) {
                search.wordOffset = ((ZiKoreanKeyEntry*)(((search.keyIndex << 3) + search.keyIndex) + keyTable))->childLow |
                    ((((ZiKoreanKeyEntry*)(((search.keyIndex << 3) + search.keyIndex) + keyTable))->keyBytes[4] & 3) << 16 |
                     ((ZiKoreanKeyEntry*)(((search.keyIndex << 3) + search.keyIndex) + keyTable))->childHigh << 8);
                search.remainingLetters = param->wordCharCount - 1;
                search.wordIndex = 1;
                wordNode = search.wordTable + search.wordOffset;
match_word:
                while (search.remainingLetters != 0) {
                    search.keyIndex = Zi8_8148302C(param->currentWord[search.wordIndex], (ziU8*)keyTable, ZI_WORK);
                    if (search.keyIndex == (ziU16)((*wordNode & 0x1F) << 8 | wordNode[1])) {
                        --search.remainingLetters;
                        ++search.wordIndex;
                        if ((*wordNode & 0x40) != 0) {
                            search.remainingLetters = param->wordCharCount - 1;
                            search.wordIndex = 1;
                            break;
                        }
                        wordNode += 2;
                    } else {
                        search.wordIndex = 1;
                        search.remainingLetters = param->wordCharCount - 1;
                        break;
                    }
                }
                if (search.remainingLetters == 0) {
                    search.keyIndex = (*wordNode & 0x1F) << 8 | wordNode[1];
                    search.character = (ziU16)(((ZiKoreanKeyEntry*)(((search.keyIndex << 3) + search.keyIndex) + keyTable))->characterHigh << 8 |
                                       ((ZiKoreanKeyEntry*)(((search.keyIndex << 3) + search.keyIndex) + keyTable))->characterLow);
                    if (param->wordCharCount == 1) {
                        if (search.keyIndex == search.previousIndex) {
                            for (; (*wordNode & 0x40) == 0; wordNode = wordNode + 2) {
                            }
                            wordNode += 2;
                            search.remainingLetters = param->wordCharCount - 1;
                            search.wordIndex = 1;
                            goto next_word;
                        }
                        search.previousIndex = search.keyIndex;
                        if (param->elementCount == 0) {
                            if (search.remainingCandidates == 0) {
                                if (options->countOnly != 0) {
                                    ++search.prefixCount;
                                    if ((ziS32)search.prefixCount < (ziS32)options->maxCount) {
                                        goto skip_word;
                                    }
                                    return options->maxCount;
                                }
                                param->candidates[search.candidateCount] = search.character;
                                ++search.candidateCount;
                                ++param->unk_0x20;
                                if (++param->letters >= param->maxCandidates) {
                                    return param->letters;
                                }
                            } else {
                                --search.remainingCandidates;
                            }
                        } else {
                            param->candidates[search.candidateCount] = search.character;
                            ++search.candidateCount;
                            ++param->unk_0x20;
                            if (++param->letters >= param->maxCandidates) {
                                Zi8_814834AC(param, &search.remainingCandidates, &search.candidateCount, &search.inserted, ZI_WORK);
                                param->unk_0x20 = search.candidateCount;
                                param->letters = search.candidateCount;
                                if (param->maxCandidates <= search.candidateCount) {
                                    if (options->countOnly == 0) {
                                        return search.candidateCount;
                                    }
                                    search.prefixCount += search.candidateCount;
                                    if ((ziS32)options->maxCount <= (ziS32)search.prefixCount) {
                                        return options->maxCount;
                                    }
                                    param->unk_0x20 = 0;
                                    param->letters = 0;
                                    search.candidateCount = 0;
                                }
                            }
                        }
                    } else {
                        for (search.candidateIndex = 0;
                             (search.candidateIndex < search.candidateCount &&
                              (search.character != param->candidates[search.candidateIndex]));
                             search.candidateIndex = search.candidateIndex + 1) {
                        }
                        if ((search.candidateIndex == search.candidateCount) &&
                            (Zi8_814833F0(param, search.character, ZI_WORK) == 0)) {
                            param->candidates[search.candidateCount] = search.character;
                            ++search.candidateCount;
                            ++param->unk_0x20;
                            if (++param->letters < param->maxCandidates) {
                                goto skip_word;
                            }
                            Zi8_814834AC(param, &search.remainingCandidates, &search.candidateCount, &search.inserted, ZI_WORK);
                            param->unk_0x20 = search.candidateCount;
                            param->letters = search.candidateCount;
                            if (param->maxCandidates <= search.candidateCount) {
                                if (options->countOnly == 0) {
                                    return search.candidateCount;
                                }
                                search.prefixCount += search.candidateCount;
                                if ((ziS32)options->maxCount <= (ziS32)search.prefixCount) {
                                    return options->maxCount;
                                }
                                param->unk_0x20 = 0;
                                param->letters = 0;
                                search.candidateCount = 0;
                            }
                        }
                    }
                }
skip_word:
                for (; (*wordNode & 0x40) == 0; wordNode = wordNode + 2) {
                }
                wordNode += 2;
                search.remainingLetters = param->wordCharCount - 1;
                search.wordIndex = 1;
next_word:
                if ((*wordNode & 0x80) != 0) {
                    goto search_table;
                }
                goto match_word;
            }
        }
search_table:
        search.resultCount = search.prefixCount;
        if (search.candidateCount != 0) {
            Zi8_814834AC(param, &search.remainingCandidates, &search.candidateCount, &search.inserted, ZI_WORK);
            if (options->countOnly != 0) {
                search.prefixCount += search.candidateCount;
                if (search.prefixCount >= (ziS32)options->maxCount) return options->maxCount;
                search.resultCount = search.prefixCount;
            }
            param->unk_0x20 = search.candidateCount;
            param->letters = search.candidateCount;
        }
        if (param->elementCount < 10) {
            if ((param->elementCount == 0) || (options->countOnly != 0)) {
                search.matchPass = 1;
            } else {
                search.matchPass = 0;
            }
            search.tableCount = Zi8GetTableCount(ZI8_LANG_KO, 9, ZI_WORK);
            Zi8_81483118(param, search.packedKeys.bytes);
            do {
                for (search.tableIndex = 0; search.tableIndex < search.tableCount; search.tableIndex = search.tableIndex + 1) {
                    search.matches = ZI8_TRUE;
                    search.entry = (ZiKoreanKeyEntry*)(((search.tableIndex << 3) + search.tableIndex) + keyTable);
                    search.keyByte = 0;
                    if (1 < param->elementCount) {
                        for (search.keyByte = 0;
                             (ziU32)search.keyByte < (int)param->elementCount / 2;
                             search.keyByte = search.keyByte + 1) {
                            if (search.packedKeys.bytes[search.keyByte] != search.entry->keyBytes[search.keyByte]) {
                                search.matches = ZI8_FALSE;
                                break;
                            }
                        }
                    }
                    if ((search.matches && ((param->elementCount % 2) != 0)) &&
                        ((search.packedKeys.bytes[search.keyByte] & 0xF0) !=
                         (search.entry->keyBytes[search.keyByte] & 0xF0))) {
                        search.matches = ZI8_FALSE;
                    }
                    if (search.matches) {
                        if (param->elementCount % 2 != 0) {
                            if ((search.entry->keyBytes[search.keyByte] & 0xF) != 0) {
                                if (search.matchPass == 0) goto next_entry;
                            } else if (search.matchPass != 0 && options->countOnly == 0) {
                                goto next_entry;
                            }
                        } else {
                            if ((search.entry->keyBytes[search.keyByte] & 0xF0) != 0) {
                                if (search.matchPass == 0) goto next_entry;
                            } else if (search.matchPass != 0 && options->countOnly == 0) {
                                goto next_entry;
                            }
                        }
                        if (search.remainingCandidates != 0) {
                            --search.remainingCandidates;
                        } else if (options->countOnly != 0) {
                            if (++search.resultCount >= (ziS32)options->maxCount) return options->maxCount;
                        } else {
                            param->candidates[search.candidateCount++] =
                                (ziU16)((ziU16)((ZiKoreanKeyEntry*)(((search.tableIndex << 3) + search.tableIndex) + keyTable))->characterHigh << 8 |
                                        ((ZiKoreanKeyEntry*)(((search.tableIndex << 3) + search.tableIndex) + keyTable))->characterLow);
                            if (++param->letters >= param->maxCandidates) return param->letters;
                        }
                    }
next_entry:
                    ;
                }
                } while (++search.matchPass < 2);
        } else {
            param->letters = 0;
        }
        if (options->countOnly != 0) return search.resultCount;
        return param->letters;
    }
    return 0;
}
