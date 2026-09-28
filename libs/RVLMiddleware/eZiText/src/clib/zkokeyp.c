#include <zi8clib/zierror.h>

extern ziU16 Zi8GetTableCount(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);
extern ziU32 Zi8GetTableAddress(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);

ziU32 Zi8_8148302C(ziU16 key, ziU8* table ZI_NEED_WORK) {
    ziU32 value;
    ziU16 count;
    ziU32 i;

    count = Zi8GetTableCount(ZI8_LANG_KO, 9, ZI_WORK);
    for (i = 0; (ziU16)i < count; i++) {
        value = (ziU16)(((ziU16)table[((i & 0xFFFF) << 3) + (i & 0xFFFF) + 7] << 8) |
                       table[((i & 0xFFFF) << 3) + (i & 0xFFFF) + 8]);
        if (key == value) {
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
    ziS32 entry;
    ziS32 tableA;
    ziS32 tableB;
    ziU16 tableCount;
    ziU8 matched;
    ziU32 j;
    ziS32 i;
    ziU8 candidateIndex;
    union {
        ziU32 words[13];
        ziU8 bytes[52];
    } local;

    matched = 0;
    local.words[0] = 0;
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
                param->candidates[i] = param->candidates[(ziU32)*remaining + i];
            }
            *count = *count - (ziU8)*remaining;
            *remaining = 0;
        }
        return 1;
    } else if (param->elementCount <= 9) {
        tableA = Zi8GetTableAddress(param->language, 9, ZI_WORK);
        tableB = Zi8GetTableAddress(param->language, 10, ZI_WORK);
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
                entry = (i << 3) + tableA + i;
                j = 0;
                if (param->elementCount > 1) {
                    for (j = 0; (j & 0xFF) < (ziU32)(param->elementCount >> 1); j++) {
                        if (local.bytes[j & 0xFF] != *((ziU8*)entry + (j & 0xFF))) {
                            matches = ZI8_FALSE;
                            break;
                        }
                    }
                }
                if (matches && (param->elementCount & 1) != 0 &&
                    ((local.bytes[j & 0xFF] & 0xF0) != (*((ziU8*)entry + (j & 0xFF)) & 0xF0))) {
                    matches = ZI8_FALSE;
                }
                if (matches) {
                    for (candidateIndex = 0; candidateIndex < *count; candidateIndex++) {
                        if (param->candidates[candidateIndex] ==
                            (ziU16)((*((ziU8*)entry + 7) << 8) | *((ziU8*)entry + 8))) {
                            matched++;
                            param->candidates[candidateIndex] =
                                param->candidates[candidateIndex] & 0x7FFF;
                            break;
                        }
                    }
                }
                i++;
            }
            if ((ziU16)matched >= *remaining) {
                matched = *count;
                *count = 0;
                for (i = 0; i < matched; i++) {
                    if ((param->candidates[i] & 0x8000) == 0) {
                        param->candidates[i] = param->candidates[i] | 0x8000;
                        if (*remaining == 0) {
                            if (*count != i) {
                                param->candidates[*count] = param->candidates[i];
                            }
                            *count = *count + 1;
                        } else {
                            *remaining = *remaining - 1;
                            Zi8_81483308(param, param->candidates[i], inserted, ZI_WORK);
                        }
                    }
                }
                *remaining = 0;
            } else {
                for (i = 0; i < *count; i++) {
                    if ((param->candidates[i] & 0x8000) == 0) {
                        param->candidates[i] = param->candidates[i] | 0x8000;
                        Zi8_81483308(param, param->candidates[i], inserted, ZI_WORK);
                    }
                }
                *remaining = *remaining - (ziU16)matched;
                *count = 0;
            }
        }
    } else {
        *count = 0;
        return 0;
    }

    return 0;
}

ziU32 Zi8GetKOcandidates(ziGetParam* param, ziU8* options ZI_NEED_WORK) {
    ziBool bVar1;
    ziU8 bVar2;
    ziS32 iVar4;
    ziU32 uVar6;
    ziU8* pbVar7;
    union {
        ziU32 words[10];
        ziU8 bytes[40];
    } local_28;
    ziU8 local_57;
    ziU8 local_56;
    ziU8 local_55;
    ziU8 local_54;
    ziU8 local_53;
    ziS8 local_52;
    ziU16 local_50;
    ziU16 local_4E;
    ziU16 local_4C;
    ziU16 local_4A;
    ziU16 local_48;
    ziS32 local_44;
    ziS32 local_2C;
    ziS32 local_30;
    ziU32 local_34;
    ziU32 local_38;
    ziU32 local_3C;
    ziU32 local_40;

    local_4E = 0xFFFF;
    local_34 = 0;
    local_28.words[0] = 0;
    local_28.bytes[4] = 0;
    local_52 = 0;
    local_53 = 0;
    local_54 = 0;
    local_55 = 0;
    local_50 = param->firstCandidate;
    local_3C = 0;
    local_40 = 0;
    local_57 = 0;
    Zi8LogError(100, ZI_WORK);
    Zi8_81483264(param, ZI_WORK);
    iVar4 = Zi8GetTableAddress(ZI8_LANG_KO, 9, ZI_WORK);
    local_2C = Zi8GetTableAddress(ZI8_LANG_KO, 10, ZI_WORK);
    if (iVar4 == 0) {
        Zi8ReplaceLastError(0x76C, ZI_WORK);
        uVar6 = 0;
    } else {
        if (local_2C == 0) {
            Zi8ReplaceLastError(0x776, ZI_WORK);
            uVar6 = 0;
            goto LAB_000114C4;
        }
        if (*options == 0) {
            param->letters = 0;
            param->count = 0;
            param->candidates[0] = 0;
        }
        Zi8LogError(100, ZI_WORK);
        if (param->wordCharCount != 0) {
            local_48 = Zi8_8148302C(param->currentWord[0], (ziU8*)iVar4, ZI_WORK);
            if ((local_48 != 0xFFFF) &&
                ((((ziU8*)iVar4)[((ziU32)local_48 * 9) + 4] & 8) != 0)) {
                local_38 = (ziU32)((ziU8*)iVar4)[((ziU32)local_48 * 9) + 6] |
                           ((ziU32)((ziU8*)iVar4)[((ziU32)local_48 * 9) + 4] & 3) << 16 |
                           (ziU32)((ziU8*)iVar4)[((ziU32)local_48 * 9) + 5] << 8;
                local_52 = param->wordCharCount - 1;
                local_53 = 1;
                pbVar7 = (ziU8*)(local_2C + local_38);
LAB_00010D44:
                if (local_52 != 0) {
                    local_48 = Zi8_8148302C(param->currentWord[local_53], (ziU8*)iVar4, ZI_WORK);
                    if (local_48 == (ziU16)((*pbVar7 & 0x1F) << 8 | pbVar7[1])) {
                        local_52 = local_52 - 1;
                        local_53 = local_53 + 1;
                        if ((*pbVar7 & 0x40) == 0) {
                            pbVar7 = pbVar7 + 2;
                            goto LAB_00010D44;
                        }
                        local_52 = param->wordCharCount - 1;
                        local_53 = 1;
                    } else {
                        local_53 = 1;
                        local_52 = param->wordCharCount - 1;
                    }
                }
                if (local_52 == 0) {
                    local_48 = (*pbVar7 & 0x1F) << 8 | pbVar7[1];
                    local_4C = (ziU16)(((ziU8*)((ziU32)local_48 * 9 + (ziU32)local_48 + (ziU32)iVar4))[7] << 8 |
                                       ((ziU8*)((ziU32)local_48 * 9 + (ziU32)local_48 + (ziU32)iVar4))[8]);
                    if (param->wordCharCount == 1) {
                        if (local_48 == local_4E) {
                            for (; (*pbVar7 & 0x40) == 0; pbVar7 = pbVar7 + 2) {
                            }
                            local_52 = param->wordCharCount;
                            goto LAB_00011114;
                        }
                        local_4E = local_48;
                        if (param->elementCount == 0) {
                            if (local_50 == 0) {
                                if (*options != 0) {
                                    local_3C = local_3C + 1;
                                    if ((ziS32)local_3C < *(ziS32*)(options + 0xC)) {
                                        goto LAB_000110E8;
                                    }
                                    uVar6 = *(ziU32*)(options + 0xC);
                                    goto LAB_000114C4;
                                }
                                param->candidates[local_54] = local_4C;
                                local_54 = local_54 + 1;
                                param->count = param->count + 1;
                                bVar2 = param->letters + 1;
                                param->letters = bVar2;
                                if (param->maxCandidates <= bVar2) {
                                    uVar6 = param->letters;
                                    goto LAB_000114C4;
                                }
                            } else {
                                local_50 = local_50 + -1;
                            }
                        } else {
                            param->candidates[local_54] = local_4C;
                            local_54 = local_54 + 1;
                            param->count = param->count + 1;
                            bVar2 = param->letters + 1;
                            param->letters = bVar2;
                            if (param->maxCandidates <= bVar2) {
                                Zi8_814834AC(param, &local_50, &local_54, &local_57, ZI_WORK);
                                param->count = local_54;
                                param->letters = local_54;
                                if (param->maxCandidates <= local_54) {
                                    if (*options == 0) {
                                        uVar6 = local_54;
                                        goto LAB_000114C4;
                                    }
                                    local_3C = local_3C + local_54;
                                    if (*(ziS32*)(options + 0xC) <= (ziS32)local_3C) {
                                        uVar6 = *(ziU32*)(options + 0xC);
                                        goto LAB_000114C4;
                                    }
                                    param->count = 0;
                                    param->letters = 0;
                                    local_54 = 0;
                                }
                            }
                        }
                    } else {
                        for (local_40 = 0;
                             (local_40 < local_54 &&
                              (local_4C != param->candidates[local_40]));
                             local_40 = local_40 + 1) {
                        }
                        if ((local_40 == local_54) &&
                            (Zi8_814833F0(param, local_4C, ZI_WORK) == 0)) {
                            param->candidates[local_54] = local_4C;
                            local_54 = local_54 + 1;
                            param->count = param->count + 1;
                            bVar2 = param->letters + 1;
                            param->letters = bVar2;
                            if (bVar2 < param->maxCandidates) {
                                goto LAB_000110E8;
                            }
                            Zi8_814834AC(param, &local_50, &local_54, &local_57, ZI_WORK);
                            param->count = local_54;
                            param->letters = local_54;
                            if (param->maxCandidates <= local_54) {
                                if (*options == 0) {
                                    uVar6 = local_54;
                                    goto LAB_000114C4;
                                }
                                local_3C = local_3C + local_54;
                                if (*(ziS32*)(options + 0xC) <= (ziS32)local_3C) {
                                    uVar6 = *(ziU32*)(options + 0xC);
                                    goto LAB_000114C4;
                                }
                                param->count = 0;
                                param->letters = 0;
                                local_54 = 0;
                            }
                        }
                    }
                }
LAB_000110E8:
                for (; (*pbVar7 & 0x40) == 0; pbVar7 = pbVar7 + 2) {
                }
                local_52 = param->wordCharCount;
LAB_00011114:
                local_52 = local_52 + -1;
                local_53 = 1;
                pbVar7 = pbVar7 + 2;
                if ((*pbVar7 & 0x80) != 0) {
                    goto LAB_00011124;
                }
                goto LAB_00010D44;
            }
        }
LAB_00011124:
        local_34 = local_3C;
        if (local_54 != 0) {
            Zi8_814834AC(param, &local_50, &local_54, &local_57, ZI_WORK);
            uVar6 = local_34;
            if ((*options != 0) &&
                (local_3C = local_3C + local_54, uVar6 = local_3C,
                 *(ziS32*)(options + 0xC) <= (ziS32)local_3C)) {
                uVar6 = *(ziU32*)(options + 0xC);
                goto LAB_000114C4;
            }
            local_34 = uVar6;
            param->count = local_54;
            param->letters = local_54;
        }
        if (param->elementCount < 10) {
            if ((param->elementCount == 0) || (*options != 0)) {
                local_56 = 1;
            } else {
                local_56 = 0;
            }
            local_4A = Zi8GetTableCount(ZI8_LANG_KO, 9, ZI_WORK);
            Zi8_81483118(param, local_28.bytes);
            do {
                for (local_30 = 0; local_30 < (ziS32)(ziU32)local_4A; local_30 = local_30 + 1) {
                    bVar1 = ZI8_TRUE;
                    local_44 = iVar4 + local_30 * 9;
                    local_55 = 0;
                    if (1 < param->elementCount) {
                        for (local_55 = 0;
                             (ziU32)local_55 < (ziU32)((ziS32)(ziU32)param->elementCount >> 1);
                             local_55 = local_55 + 1) {
                            if (local_28.bytes[local_55] != *(ziU8*)(local_44 + local_55)) {
                                bVar1 = ZI8_FALSE;
                                break;
                            }
                        }
                    }
                    if ((bVar1 && ((param->elementCount & 1) != 0)) &&
                        ((local_28.bytes[local_55] & 0xF0) !=
                         (*(ziU8*)(local_44 + local_55) & 0xF0))) {
                        bVar1 = ZI8_FALSE;
                    }
                    if (bVar1) {
                        bVar2 = local_56;
                        if ((param->elementCount & 1) == 0) {
                            if ((*(ziU8*)(local_44 + local_55) & 0xF0) == 0) {
                                if (local_56 == 0) {
                                    goto LAB_000113B0;
                                }
                                bVar2 = *options;
                            }
                            if (bVar2 == 0) {
                                goto LAB_00011478;
                            }
                        } else {
                            if ((*(ziU8*)(local_44 + local_55) & 0xF) != 0) {
                                goto LAB_000113AC;
                            }
                            if (local_56 != 0) {
                                bVar2 = *options;
                                goto LAB_000113AC;
                            }
                        }
LAB_000113AC:
                        if (bVar2 == 0) {
                            goto LAB_00011478;
                        }
LAB_000113B0:
                        if (local_50 == 0) {
                            if (*options == 0) {
                                param->candidates[local_54] =
                                    (ziU16)((*(ziU8*)(local_30 * 9 + iVar4 + 7) << 8) |
                                            *(ziU8*)(local_30 * 9 + iVar4 + 8));
                                local_54 = local_54 + 1;
                                bVar2 = param->letters + 1;
                                param->letters = bVar2;
                                if (param->maxCandidates <= bVar2) {
                                    uVar6 = param->letters;
                                    goto LAB_000114C4;
                                }
                            } else {
                                local_34 = local_34 + 1;
                                if (*(ziS32*)(options + 0xC) <= (ziS32)local_34) {
                                    uVar6 = *(ziU32*)(options + 0xC);
                                    goto LAB_000114C4;
                                }
                            }
                        } else {
                            local_50 = local_50 + -1;
                        }
                    }
LAB_00011478:
                    ;
                }
                local_56 = local_56 + 1;
            } while (local_56 < 2);
            uVar6 = local_34;
            if (*options == 0) {
                uVar6 = param->letters;
            }
        } else {
            param->letters = 0;
            uVar6 = 0;
        }
    }
LAB_000114C4:
    return uVar6;
}
