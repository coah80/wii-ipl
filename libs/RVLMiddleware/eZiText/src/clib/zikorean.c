#include <zi8clib/zierror.h>
#include <zi8clib/zitypes.h>

ziU32 Zi8GetTableAddress(ziU8 lang, ziU8 tableIdx, ziPtr workData);
ziU16 Zi8GetTableCount(ziU8 lang, ziU8 tableIdx, ziPtr workData);

ziU8 Zi8LookupKoreanChar(ziWChar character, ziU8* result, ziU16* index, ziPtr workData) {
    ziU16 i;
    ziU8* table;

    table = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 5, workData);
    i = 0;
    while (table[i] != 0) {
        if (character == table[i]) {
            *index = i;
            *result = table[i];
            Zi8LogError(0x64, workData);
            return 1;
        }
        i++;
    }
    Zi8LogError(0x2A8, workData);
    return 0;
}

ziU8 Zi8MatchKoreanSequence(ziU16* resultIndex, ziU16* input, ziU8 type, ziU16 count, struct __zi8_work_data_s* workData);

ziU32 Zi8GetKoreanCandidates(ziGetParam* params, ziU8* argument,
    struct __zi8_work_data_s* workData) {
    ziU8* table1;
    ziU8* table2;
    ziU8* table31;
    ziU16 tableCount0;
    ziU16 tableCount3;
    ziU16 tableCount6;
    ziU16 tableCount31;
    ziU16 nextIndex;
    ziU16 inputIndex;
    ziU16 currentCandidate;
    ziU16 index;
    ziU8 elementIndex;
    ziU8 matched;
    ziU8 characterIndex;
    ziU16 buffer[100];
    ziU8 result;
    ziU16 currentCharacter;
    ziU8* selectedTable;

    nextIndex = 0;
    result = 0;
    characterIndex = 0xFF;
    currentCandidate = params->firstCandidate;
    params->letters = params->completion = params->count = 0;
    if ((argument != 0) && (*argument != 0)) {
        Zi8LogError(0x7D0, workData);
        return 0;
    }
    if ((params->elementCount == 0) || (params->elementCount > 100)) {
        Zi8LogError(0x64, workData);
        return 0;
    }

    selectedTable = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 4, workData);
    table1 = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 1, workData);
    table2 = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 2, workData);
    table31 = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x31, workData);
    tableCount0 = Zi8GetTableCount(ZI8_LANG_KO, 0, workData);
    tableCount3 = Zi8GetTableCount(ZI8_LANG_KO, 3, workData);
    tableCount6 = Zi8GetTableCount(ZI8_LANG_KO, 6, workData);
    tableCount31 = Zi8GetTableCount(ZI8_LANG_KO, 0x31, workData);

    for (elementIndex = 0; elementIndex < params->elementCount;
        elementIndex++) {
        currentCharacter = params->elements[elementIndex];

        if ((currentCharacter >= 0x61) && (currentCharacter <= 0x7A)) {
            buffer[elementIndex] = table1[(currentCharacter - 0x61) * 2];
        } else if ((currentCharacter >= 0x41) && (currentCharacter <= 0x5A)) {
            buffer[elementIndex] = (table1 + (currentCharacter - 0x41) * 2)[1];
        } else {
            matched = 0;
            for (; table2[matched * 3] != 0; matched++) {
                if (currentCharacter == table2[matched * 3]) break;
            }
            if (table2[matched * 3] != 0) {
                buffer[elementIndex] =
                ((ziU16)(table2 + matched * 3)[1] << 8) |
                (table2 + matched * 3)[2];
            } else {
                Zi8LogError(0x161, workData);
                return 0;
            }
        }
    }

    result = 0;
    for (currentCharacter = 0; currentCharacter < elementIndex; currentCharacter++) {
        if (Zi8LookupKoreanChar(buffer[currentCharacter], &characterIndex,
            &inputIndex, workData) != 0) {
            matched = Zi8MatchKoreanSequence(&nextIndex,
                buffer + currentCharacter + 1,
                characterIndex,
                (elementIndex - currentCharacter) - 1,
                workData);
            if (workData->koAltTables == 1) {
                switch (characterIndex) {
                case 1:
                    selectedTable = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x1E, workData);
                    break;
                case 2:
                    selectedTable = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x1F, workData);
                    break;
                case 4:
                    selectedTable = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x20, workData);
                    break;
                case 7:
                    selectedTable = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x21, workData);
                    break;
                case 8:
                    selectedTable = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x22, workData);
                    break;
                case 9:
                    selectedTable = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x23, workData);
                    break;
                case 0x11:
                    selectedTable = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x24, workData);
                    break;
                case 0x12:
                    selectedTable = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x25, workData);
                    break;
                case 0x13:
                    selectedTable = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x26, workData);
                    break;
                case 0x15:
                    selectedTable = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x27, workData);
                    break;
                case 0x16:
                    selectedTable = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x28, workData);
                    break;
                case 0x17:
                    selectedTable = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x29, workData);
                    break;
                case 0x18:
                    selectedTable = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x2A, workData);
                    break;
                case 0x19:
                    selectedTable = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x2B, workData);
                    break;
                case 0x1A:
                    selectedTable = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x2C, workData);
                    break;
                case 0x1B:
                    selectedTable = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x2D, workData);
                    break;
                case 0x1C:
                    selectedTable = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x2E, workData);
                    break;
                case 0x1D:
                    selectedTable = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x2F, workData);
                    break;
                case 0x1E:
                    selectedTable = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x30, workData);
                    break;
                default:
                    break;
                }
            }
        } else {
            matched = 0;
        }
        if (matched != 0) {
            if (tableCount6 == 0) {
                nextIndex += inputIndex * tableCount3;
            }
            if (currentCandidate != 0) {
                currentCandidate--;
            } else {
                params->candidates[result] =
                ((ziU16)selectedTable[nextIndex * 2] << 8) | (selectedTable + nextIndex * 2)[1];
                if ((tableCount6 != 0) && (workData->koAltTables == 0)) {
                    params->candidates[result] += inputIndex * tableCount3;
                }
                result++;
            }
            if (currentCharacter == 0) {
                params->completion = matched + 1;
            }
            currentCharacter += matched;
        } else {
            if (currentCandidate != 0) {
                index = 0;
                for (; index < tableCount31; index++) {
                    if (table31[index * 3] == buffer[currentCharacter] &&
                        (table31 + index * 3)[1] == buffer[currentCharacter + 1]) break;
                }
                if (index == tableCount31) {
                    currentCandidate--;
                }
                if (currentCharacter == 0) {
                    params->completion = 1;
                }
            } else {
                for (index = 0; index < tableCount31; index++) {
                    if ((table31[(index * 3)] == buffer[currentCharacter]) &&
                        ((table31 + index * 3)[1] == buffer[currentCharacter + 1])) {
                        if (currentCharacter == 0) {
                            params->completion = 1;
                        }
                        params->candidates[result] =
                        tableCount0 + (table31 + index * 3)[2];
                        result++;
                        currentCharacter++;
                        break;
                    }
                }
                if (index == tableCount31) {
                    if ((params->candidates[result] = buffer[currentCharacter]) < 0xFF) {
                        if (currentCharacter == 0) {
                            params->completion = 1;
                        }
                        params->candidates[result] += tableCount0;
                        result++;
                    }
                }
            }
        }
        if (result >= params->maxCandidates) {
            break;
        }
    }
    params->letters = result;
    Zi8LogError(0x64, workData);
    return result;
}

ziU8 Zi8MatchKoreanSequence(ziU16* resultIndex, ziU16* input, ziU8 type, ziU16 count, struct __zi8_work_data_s* workData) {
    ziU16 nestedScratch;
    ziU16 nestedIndexStorage;
    ziU16 index1;
    ziU16 index2;
    ziU16 index3;
    ziU16 index4;
    ziU16 firstCharacter;
    ziU16 tableCount;
    ziU8 mappedCharacter;
    ziU8* table;

    firstCharacter = input[0];
    mappedCharacter = 0xFF;
    if (workData->koAltTables == 0) {
        table = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 3, workData);
        tableCount = Zi8GetTableCount(ZI8_LANG_KO, 3, workData);
    } else {
        switch (type) {
        case 1:
            table = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0xB, workData);
            tableCount = Zi8GetTableCount(ZI8_LANG_KO, 0xB, workData);
            break;
        case 2:
            table = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0xC, workData);
            tableCount = Zi8GetTableCount(ZI8_LANG_KO, 0xC, workData);
            break;
        case 4:
            table = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0xD, workData);
            tableCount = Zi8GetTableCount(ZI8_LANG_KO, 0xD, workData);
            break;
        case 7:
            table = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0xE, workData);
            tableCount = Zi8GetTableCount(ZI8_LANG_KO, 0xE, workData);
            break;
        case 8:
            table = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0xF, workData);
            tableCount = Zi8GetTableCount(ZI8_LANG_KO, 0xF, workData);
            break;
        case 9:
            table = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x10, workData);
            tableCount = Zi8GetTableCount(ZI8_LANG_KO, 0x10, workData);
            break;
        case 0x11:
            table = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x11, workData);
            tableCount = Zi8GetTableCount(ZI8_LANG_KO, 0x11, workData);
            break;
        case 0x12:
            table = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x12, workData);
            tableCount = Zi8GetTableCount(ZI8_LANG_KO, 0x12, workData);
            break;
        case 0x13:
            table = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x13, workData);
            tableCount = Zi8GetTableCount(ZI8_LANG_KO, 0x13, workData);
            break;
        case 0x15:
            table = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x14, workData);
            tableCount = Zi8GetTableCount(ZI8_LANG_KO, 0x14, workData);
            break;
        case 0x16:
            table = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x15, workData);
            tableCount = Zi8GetTableCount(ZI8_LANG_KO, 0x15, workData);
            break;
        case 0x17:
            table = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x16, workData);
            tableCount = Zi8GetTableCount(ZI8_LANG_KO, 0x16, workData);
            break;
        case 0x18:
            table = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x17, workData);
            tableCount = Zi8GetTableCount(ZI8_LANG_KO, 0x17, workData);
            break;
        case 0x19:
            table = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x18, workData);
            tableCount = Zi8GetTableCount(ZI8_LANG_KO, 0x18, workData);
            break;
        case 0x1A:
            table = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x19, workData);
            tableCount = Zi8GetTableCount(ZI8_LANG_KO, 0x19, workData);
            break;
        case 0x1B:
            table = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x1A, workData);
            tableCount = Zi8GetTableCount(ZI8_LANG_KO, 0x1A, workData);
            break;
        case 0x1C:
            table = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x1B, workData);
            tableCount = Zi8GetTableCount(ZI8_LANG_KO, 0x1B, workData);
            break;
        case 0x1D:
            table = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x1C, workData);
            tableCount = Zi8GetTableCount(ZI8_LANG_KO, 0x1C, workData);
            break;
        case 0x1E:
            table = (ziU8*)Zi8GetTableAddress(ZI8_LANG_KO, 0x1D, workData);
            tableCount = Zi8GetTableCount(ZI8_LANG_KO, 0x1D, workData);
            break;
        }
    }
    *resultIndex = 0;
    if ((count < 1) || (firstCharacter >= 0xFF)) {
        return 0;
    }

    index1 = *resultIndex;
    for (; index1 < tableCount; index1++) {
        if (table[index1 * 4] >= firstCharacter) {
            break;
        }
    }
    if ((index1 >= tableCount) || (firstCharacter != table[index1 * 4])) {
        return 0;
    }
    if ((count < 2) || ((firstCharacter = input[1]) >= 0xFF)) {
        *resultIndex = index1;
        return 1;
    }

    index2 = index1;
    for (; index2 < tableCount; index2++) {
        if ((table + index2 * 4)[1] >= firstCharacter) {
            break;
        }
    }
    if ((index2 >= tableCount) || (firstCharacter != (table + index2 * 4)[1]) ||
        (input[0] != table[index2 * 4])) {
        *resultIndex = index1;
        return 1;
    }
    if ((count < 3) || ((firstCharacter = input[2]) >= 0xFF)) {
        *resultIndex = index2;
        return 2;
    }

    index3 = index2;
    for (; index3 < tableCount; index3++) {
        if ((table + index3 * 4)[2] >= firstCharacter) {
            break;
        }
    }
    if ((index3 >= tableCount) || (firstCharacter != (table + index3 * 4)[2]) ||
        (input[1] != (table + index3 * 4)[1]) || (input[0] != table[index3 * 4])) {
        if ((Zi8LookupKoreanChar(input[1], &mappedCharacter, &nestedScratch, workData) != 0) &&
            (Zi8MatchKoreanSequence(&nestedIndexStorage, input + 2, mappedCharacter, 1, workData) != 0)) {
            *resultIndex = index1;
            return 1;
        }
        *resultIndex = index2;
        return 2;
    }
    if ((count < 4) || ((firstCharacter = input[3]) >= 0xFF)) {
        *resultIndex = index3;
        return 3;
    }

    index4 = index3;
    for (; index4 < tableCount; index4++) {
        if ((table + index4 * 4)[3] >= firstCharacter) {
            break;
        }
    }
    if ((index4 >= tableCount) || (firstCharacter != (table + index4 * 4)[3]) ||
        (input[2] != (table + index4 * 4)[2]) || (input[1] != (table + index4 * 4)[1]) ||
        (input[0] != table[index4 * 4])) {
        if ((Zi8LookupKoreanChar(input[2], &mappedCharacter, &nestedScratch, workData) != 0) &&
            (Zi8MatchKoreanSequence(&nestedIndexStorage, input + 3, mappedCharacter, 1, workData) != 0)) {
            *resultIndex = index2;
            return 2;
        }
        *resultIndex = index3;
        return 3;
    }
    if ((count < 5) || ((firstCharacter = input[4]) >= 0xFF)) {
        *resultIndex = index4;
        return 4;
    }
    if ((Zi8LookupKoreanChar(input[3], &mappedCharacter, &nestedScratch, workData) != 0) &&
        (Zi8MatchKoreanSequence(&nestedIndexStorage, input + 4, mappedCharacter, 1, workData) != 0)) {
        *resultIndex = index3;
        return 3;
    }
    *resultIndex = index4;
    return 4;
}
