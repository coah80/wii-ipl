#include <zi8clib/zi8cgetc.h>
#include <zi8clib/zi8space.h>
#include <zi8clib/zierror.h>

typedef unsigned int Zi8UInt;

extern Zi8UInt Zi8Ord2Ord(ziU16 ordinal, ziPtr work);
extern ziU32 Zi8WCharCount(ziWChar* word, ziPtr work);

static Zi8UInt Zi8SetFindCand(ziU8* foundCandidates, Zi8UInt ordinal, ziPtr work) {
    Zi8UInt found;
    ordinal = Zi8Ord2Ord(ordinal, work);
    found = (ziU8)((1 << ((int)(ordinal & 0xffff) % 8)) &
                  foundCandidates[(int)(ordinal & 0xffff) / 8]);
    foundCandidates[(int)(ordinal & 0xffff) / 8] |=
        1 << ((int)(ordinal & 0xffff) % 8);
    return found;
}

ziWChar* ZiGetNextPhonetic(ziWChar* spelling, ziWChar* end ZI_NEED_WORK) {
    while (*spelling && *spelling != ZI_WORK->unk_0x1A && *spelling != 0xF360 && spelling < end) {
        ++spelling;
    }
    if (!*spelling || spelling == end) {
        return ZI8_NULL;
    }
    ++spelling;
    if (!*spelling || spelling == end) {
        return ZI8_NULL;
    }
    return spelling;
}

int ZiPartialMatch(ziWChar* spelling, ziWChar* spellingEnd,
                   ziWChar* candidate, ziWChar* candidateEnd,
                   ziU16 phoneticIndex ZI_NEED_WORK) {
    if (spelling == spellingEnd || candidate == candidateEnd || !*spelling || !*candidate) {
        return 1;
    }
    while (*spelling != ZI_WORK->unk_0x1A && *spelling != 0xF360) {
        if (*candidate == ZI_WORK->unk_0x1A || *candidate == 0xF360) {
            break;
        }
        if (*spelling != *candidate) {
            return 0;
        }
        ++spelling;
        ++candidate;
        if (spelling == spellingEnd || candidate == candidateEnd || !*spelling || !*candidate) {
            return 1;
        }
    }
    return 1;
}

int ZiMatchZHSpelling(ziPtr dictionary, ziWChar* candidate, ziWChar* spelling,
                      ziU8 spellingLength, ziU16 phoneticIndex ZI_NEED_WORK) {
    ziWChar* candidateCursor;
    ziWChar* spellingCursor;
    int index;
    int matches;
    int candidateLength;
    ziWChar spacedSpelling[64];
    ziWChar spacedCandidate[64];
    matches = 1;
    candidateLength = Zi8WCharCount(candidate, __zi8_work_data);
    if (!candidate || !spellingLength) {
        return matches;
    }
    for (index = 0; index < spellingLength; ++index) {
        if (!candidate[index] || candidate[index] != spelling[index]) {
            matches = 0;
            break;
        }
    }
    if (!matches) {
        spacedSpelling[0] = 0;
        spacedCandidate[0] = 0;
        if (!Zi8ZHaddSpace(spelling, spellingLength, spacedSpelling, 64, __zi8_work_data)) {
            return 0;
        }
        if (!Zi8ZHaddSpace(candidate, candidateLength, spacedCandidate, 64, __zi8_work_data)) {
            return 0;
        }
        spellingCursor = spacedSpelling;
        candidateCursor = spacedCandidate;
        while (phoneticIndex) {
            candidateCursor = ZiGetNextPhonetic(candidateCursor, spacedCandidate + 64, __zi8_work_data);
            if (!candidateCursor) {
                return 0;
            }
            --phoneticIndex;
        }
        matches = 1;
        while (spellingCursor && candidateCursor) {
            if (!ZiPartialMatch(spellingCursor, spacedSpelling + 64,
                                candidateCursor, spacedCandidate + 64,
                                phoneticIndex, __zi8_work_data)) {
                return 0;
            }
            spellingCursor = ZiGetNextPhonetic(spellingCursor, spacedSpelling + 64, __zi8_work_data);
            candidateCursor = ZiGetNextPhonetic(candidateCursor, spacedCandidate + 64, __zi8_work_data);
        }
    }
    return matches;
}
typedef struct {
    ziU8 countOnly;
    ziU8 maxWordLength;
    ziU8 lookupMode;
    ziU8 dictionaryMode;
    ziWChar* dictionary;
    ziU32 dictionaryFlags;
    int maxResults;
    ziU16 capacity;
} ZiChineseOptions;

typedef struct {
    ziU8 settings[0x1A];
    ziWChar separator;
    ziU8 state[4];
    ziWChar duplicateCharacters[64];
    ziWChar duplicateOrdinals[64];
    ziU8 duplicateIndex;
} ZiChineseWork;

typedef struct {
    ziU8 flags;
    ziU8 phonetics[11];
} ZiChineseRecord;

extern ziPtr Zi8GetTableAddress(ziU8 language, ziU8 table, ziPtr work);
extern ziU16 Zi8GetTableCount(ziU8 language, ziU8 table, ziPtr work);
extern ziU8 Zi8IsDupWChar(ziWChar character, ziPtr work);
extern ziU8 Zi8IsDupWordW(ziWChar* word, ziU8 length, ziPtr work);
extern ziWChar Zi8Ord2Uni(ziU16 ordinal, ziPtr work);
extern ziU8 Zi8MatchPhonetic(ziU8* phonetics, ZiChineseRecord* records,
                            ziPtr indexTable, ziU16 indexCount, ziPtr dictionary,
                            ZiChineseRecord* record, ziU16* mask, ziU16* match,
                            ziU16* length, ZiChineseRecord** matchedRecord,
                            int* matchedIndex, ziU8 wordMode, ziU8 partial,
                            ziU8 oneCharacter, ziU16 excludedMask,
                            ziU16 excludedMatch, ziU8 charset, ziU8 options,
                            ziU16 ordinal, ziU16* tone, ziU8 spellingOnly,
                            ziPtr work);

static int Zi8NewMatchPhonetic(ziGetParam* request, ZiChineseRecord* records,
                              ziPtr indexTable, ziU16 indexCount, ziPtr dictionary,
                              ZiChineseOptions* options, ziU16 mask, ziU16 match, ziU16 excludedMask,
                              ziU16 excludedMatch, ziU8 charset, ziU16 recordCount,
                              ziU16* skipCount, int* resultCount, ziU8* candidateCount,
                              int* outputCount, ziU8 wordMode, ziU8 useFoundCandidates,
                              ziU8 pinyin, ziU8* charsetTable, ziU8* charsetEntry,
                              ziU8 charsetFilter, ziWChar* output, ziPtr work) {
    ziU16* phoneticOffsets;
    ziU16* ordinalTable;
    ziU8* phonetics;
    int totalResults;
    int emittedCharacters;
    ZiChineseRecord* matchedRecord;
    ziU8* phoneticGroups;
    ziU8* candidateGroups;
    int matchedIndex;
    int capacity;
    ziU8* groupCandidates;
    ziU16 phoneticCount;
    ziU16 phoneticIndex;
    ziU16 candidateIndex;
    ziU16 character;
    ziU16 rangeBegin;
    ziU16 rangeEnd;
    ziU16 previousCharacter;
    ziU16 remainingSkip;
    ziU16 filteredMask;
    ziU16 filteredMatch;
    ziU16 matchedLength;
    ziU16 groupCount;
    ziU16 matchedTone;
    ziU16 groupOffset;
    ziU16 groupSize;
    ziU8 emittedCount;
    ziU8 stopAfterTone;

    previousCharacter = 0;
    remainingSkip = *skipCount;
    totalResults = *resultCount;
    emittedCount = *candidateCount;
    emittedCharacters = *outputCount;
    stopAfterTone = 0;
    phoneticGroups = ZI8_NULL;
    candidateGroups = ZI8_NULL;
    capacity = options->capacity - 64;
    Zi8LogError(100, work);
    if ((mask & 7) == 7) {
        stopAfterTone = match & 7;
    }
    phoneticOffsets = Zi8GetTableAddress(1, 13, work);
    ordinalTable = Zi8GetTableAddress(1, 14, work);
    if (pinyin) {
        phonetics = Zi8GetTableAddress(1, 3, work);
        phoneticCount = Zi8GetTableCount(1, 3, work);
        phoneticGroups = Zi8GetTableAddress(1, 17, work);
        groupCount = Zi8GetTableCount(1, 17, work);
        candidateGroups = Zi8GetTableAddress(1, 18, work);
    } else {
        phonetics = Zi8GetTableAddress(1, 4, work);
        phoneticCount = Zi8GetTableCount(1, 4, work);
        phoneticGroups = Zi8GetTableAddress(1, 19, work);
        groupCount = Zi8GetTableCount(1, 19, work);
        candidateGroups = Zi8GetTableAddress(1, 20, work);
    }

    if (groupCount) {
        groupOffset = 0;
        filteredMask = mask | 7;
        filteredMatch = match;
        for (phoneticIndex = 0; phoneticIndex < groupCount; ++phoneticIndex) {
            character = phoneticGroups[0] | (ziU16)phoneticGroups[1] << 8;
            groupSize = phoneticGroups[2] | (ziU16)phoneticGroups[3] << 8;
            if (excludedMatch == (character & excludedMask) ||
                filteredMatch != (character & filteredMask)) {
                groupOffset += groupSize;
                phoneticGroups += 4;
                continue;
            }
            groupCandidates = candidateGroups + groupOffset * 2;
            candidateIndex = 0;
            while (candidateIndex < groupSize) {
                character = groupCandidates[0] | (ziU16)groupCandidates[1] << 8;
                if (!(charset & records[character].flags)) {
                    goto next_group_candidate;
                }
                if (charsetTable) {
                    charsetEntry = charsetTable + character;
                    if (!(*charsetEntry & charsetFilter)) {
                        goto next_group_candidate;
                    }
                }
                if (!wordMode) {
                    if (useFoundCandidates) {
                        if ((ziU8)Zi8SetFindCand(request->scratch, character, work)) {
                            goto next_group_candidate;
                        }
                    } else if (Zi8IsDupWChar(character, work)) {
                        goto next_group_candidate;
                    }
                }
                ((ZiChineseWork*)work)->duplicateOrdinals[((ZiChineseWork*)work)->duplicateIndex] = character;
                character = Zi8Ord2Uni(character, work);
                ((ZiChineseWork*)work)->duplicateCharacters[((ZiChineseWork*)work)->duplicateIndex] = character;
                if (character == previousCharacter) {
                    goto next_group_candidate;
                }
                previousCharacter = character;
                if (wordMode && Zi8IsDupWordW(&character, 1, work)) {
                    goto next_group_candidate;
                }
                if (remainingSkip) {
                    --remainingSkip;
                    goto next_group_candidate;
                }
                ++totalResults;
                if (!options->countOnly) {
                    if (++((ZiChineseWork*)work)->duplicateIndex >= 64) {
                        ((ZiChineseWork*)work)->duplicateIndex = 0;
                    }
                    if (wordMode) {
                        ++emittedCount;
                        output[emittedCharacters++] = character;
                        output[emittedCharacters++] = 0x20;
                        if (emittedCharacters > capacity) {
                            *skipCount = remainingSkip;
                            *resultCount = totalResults;
                            *candidateCount = emittedCount;
                            *outputCount = emittedCharacters;
                            Zi8ReplaceLastError(0xB54, work);
                            return 0;
                        }
                    } else {
                        output[emittedCount++] = character;
                    }
                    if (emittedCount >= request->maxCandidates) {
                        *skipCount = remainingSkip;
                        *resultCount = totalResults;
                        *candidateCount = emittedCount;
                        *outputCount = emittedCharacters;
                        Zi8ReplaceLastError(0xB55, work);
                        return 0;
                    }
                } else if (totalResults >= options->maxResults) {
                    *skipCount = remainingSkip;
                    *resultCount = totalResults;
                    *candidateCount = emittedCount;
                    *outputCount = emittedCharacters;
                    Zi8ReplaceLastError(0xB56, work);
                    return 0;
                }
next_group_candidate:
                ++candidateIndex;
                groupCandidates += 2;
            }
            if (stopAfterTone) {
                break;
            }
            groupOffset += groupSize;
            phoneticGroups += 4;
        }
    }
    filteredMask = mask & 0xFFF8;
    filteredMatch = match & 0xFFF8;
    for (phoneticIndex = 1; phoneticIndex < phoneticCount; ++phoneticIndex) {
        character = phonetics[phoneticIndex * 2] | (ziU16)phonetics[phoneticIndex * 2 + 1] << 8;
        if (filteredMatch != (character & filteredMask) ||
            excludedMatch == (character & excludedMask)) {
            continue;
        }
        rangeBegin = phoneticOffsets[phoneticIndex];
        rangeEnd = phoneticOffsets[phoneticIndex + 1];
        rangeBegin = ((ziU8)rangeBegin << 8) | ((rangeBegin >> 8) & 0xFF);
        rangeEnd = ((ziU8)rangeEnd << 8) | ((rangeEnd >> 8) & 0xFF);
        for (candidateIndex = rangeBegin; candidateIndex < rangeEnd; ++candidateIndex) {
            character = ordinalTable[candidateIndex];
            character = ((ziU8)character << 8) | ((character >> 8) & 0xFF);
            if (character >= recordCount || !(charset & records[character].flags)) {
                continue;
            }
            if (charsetTable) {
                charsetEntry = charsetTable + character;
                if (!(*charsetEntry & charsetFilter)) {
                    continue;
                }
            }
            if (stopAfterTone) {
                matchedRecord = records + character;
                matchedLength = 0;
                matchedIndex = 0;
                if (!Zi8MatchPhonetic(phonetics, records, indexTable, indexCount,
                                      dictionary, matchedRecord, &mask, &match,
                                      &matchedLength, &matchedRecord, &matchedIndex,
                                      wordMode, 1, 1, excludedMask, excludedMatch,
                                      charset, request->getOptions & 0x40, character,
                                      &matchedTone, 0, work)) {
                    continue;
                }
            }
            if (!wordMode) {
                if (useFoundCandidates) {
                    if ((ziU8)Zi8SetFindCand(request->scratch, character, work)) {
                        continue;
                    }
                } else if (Zi8IsDupWChar(character, work)) {
                    continue;
                }
            }
            ((ZiChineseWork*)work)->duplicateOrdinals[((ZiChineseWork*)work)->duplicateIndex] = character;
            character = Zi8Ord2Uni(character, work);
            ((ZiChineseWork*)work)->duplicateCharacters[((ZiChineseWork*)work)->duplicateIndex] = character;
            if (character == previousCharacter) {
                continue;
            }
            previousCharacter = character;
            if (wordMode && Zi8IsDupWordW(&character, 1, work)) {
                continue;
            }
            if (remainingSkip) {
                --remainingSkip;
                continue;
            }
            ++totalResults;
            if (!options->countOnly) {
                if (++((ZiChineseWork*)work)->duplicateIndex >= 64) {
                    ((ZiChineseWork*)work)->duplicateIndex = 0;
                }
                if (wordMode) {
                    ++emittedCount;
                    output[emittedCharacters++] = character;
                    output[emittedCharacters++] = 0x20;
                    if (emittedCharacters > capacity) {
                        *skipCount = remainingSkip;
                        *resultCount = totalResults;
                        *candidateCount = emittedCount;
                        *outputCount = emittedCharacters;
                        Zi8ReplaceLastError(0xB54, work);
                        return 0;
                    }
                } else {
                    output[emittedCount++] = character;
                }
                if (emittedCount >= request->maxCandidates) {
                    *skipCount = remainingSkip;
                    *resultCount = totalResults;
                    *candidateCount = emittedCount;
                    *outputCount = emittedCharacters;
                    Zi8ReplaceLastError(0xB55, work);
                    return 0;
                }
            } else if (totalResults >= options->maxResults) {
                *skipCount = remainingSkip;
                *resultCount = totalResults;
                *candidateCount = emittedCount;
                *outputCount = emittedCharacters;
                Zi8ReplaceLastError(0xB56, work);
                return 0;
            }
        }
    }
    *skipCount = remainingSkip;
    *resultCount = totalResults;
    *candidateCount = emittedCount;
    *outputCount = emittedCharacters;
    return 1;
}

ziU8 Zi8GetElementCount(ziWChar* elements, ziU8 elementCount, ziU8 charCount ZI_NEED_WORK) {
    ziU8 spacedIndex;
    ziU8 elementIndex;
    ziU8 count;
    ziWChar spacedElements[256];
    ziWChar savedSeparator = ZI_WORK->unk_0x1A;
    if (elementCount <= 1 || !charCount) {
        return elementCount;
    }
    for (spacedIndex = 0; spacedIndex < elementCount; ++spacedIndex) {
        if (elements[spacedIndex] != ';' &&
            (elements[spacedIndex] < 'a' || elements[spacedIndex] > 'z')) {
            break;
        }
    }
    if (spacedIndex == elementCount) {
        return elementCount;
    }
    ZI_WORK->unk_0x1A = 0xF360;
    Zi8ZHaddSpace(elements, elementCount, spacedElements, 256, __zi8_work_data);
    ZI_WORK->unk_0x1A = savedSeparator;
    spacedIndex = elementIndex = count = 0;
    while (charCount && elementIndex < elementCount) {
        if (spacedElements[spacedIndex] == 0xF360) {
            --charCount;
            if (elements[elementIndex] != 0xF360) {
                goto next_spaced_element;
            }
        } else if (spacedElements[spacedIndex] >= 0xF331 && spacedElements[spacedIndex] <= 0xF335) {
            --charCount;
            if (elements[elementIndex + 1] == 0xF360) {
                ++spacedIndex;
                ++elementIndex;
                ++count;
            }
        }
        ++elementIndex;
        ++count;
next_spaced_element:
        ++spacedIndex;
    }
    return count;
}

extern int zi8InternalGetZH(ziGetParam* request, ZiChineseOptions* options, ziPtr work);

int Zi8GetChineseCandidates(ziGetParam* request, ZiChineseOptions* options, ziPtr work) {
    ziU8 savedCountOnly;
    int savedMaxResults;
    int length;
    ziGetParam suffixRequest;
    if (request->firstCandidate || request->elementCount <= 1) {
get_candidates:
        return zi8InternalGetZH(request, options, work);
    }
    switch (request->getMode) {
        case 16:
            if (request->elements[request->elementCount - 1] == 0xF360) {
                goto get_candidates;
            }
            for (length = request->elementCount - 2; length > 0; --length) {
                if (request->elements[length] == 0xF360) {
                    break;
                }
            }
            if (length++ <= 0) {
                goto get_candidates;
            }
            break;
        case 12:
        case 13:
            switch (request->elements[request->elementCount - 1]) {
                case 0xF331:
                case 0xF332:
                case 0xF333:
                case 0xF334:
                case 0xF335:
                case 0xF360:
                    break;
                default:
                    goto get_candidates;
            }
            for (length = 1; length < 64; ++length) {
                if (Zi8GetElementCount(request->elements, request->elementCount, length, work) >= request->elementCount) {
                    break;
                }
            }
            if (length-- == 1) {
                goto get_candidates;
            }
            length = Zi8GetElementCount(request->elements, request->elementCount, length, work);
            break;
        default:
            goto get_candidates;
    }
    suffixRequest = *request;
    savedCountOnly = options->countOnly;
    savedMaxResults = options->maxResults;
    suffixRequest.elements = request->elements + length;
    suffixRequest.elementCount = (ziU8)(suffixRequest.elementCount - length);
    savedCountOnly = options->countOnly;
    options->countOnly = 1;
    savedMaxResults = options->maxResults;
    options->maxResults = 1;
    length = zi8InternalGetZH(&suffixRequest, options, work);
    options->countOnly = savedCountOnly;
    options->maxResults = savedMaxResults;
    if (!length) {
        Zi8LogError(0x1388, work);
        return 0;
    }
    return zi8InternalGetZH(request, options, work);
}

const ziWChar ziTones[4] = {0x02CA, 0x02C7, 0x02CB, 0x02D9};
const ziWChar ziPuncts[4] = {0xFF0C, 0x3002, 0xFF1F, 0xFF01};
const ziWChar zi8tones[4];
