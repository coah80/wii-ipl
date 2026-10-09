#include <zi8clib/zierror.h>

extern ziU16 Zi8GetTableCount(ziU8 lang, ziU8 tableIdx ZI_NEED_WORK);
extern ziU8 Zi8getKeyLayout(ziU8 lang, ziU16 key, ziWChar* layout, ziU8 mode ZI_NEED_WORK);
extern ziChar Zi8ConvertWC2UC(ziWChar ch, ziU8 language ZI_NEED_WORK);
extern ziU32 Zi8AlphaGetCandidates(ziGetParam* param, ziPtr sw ZI_NEED_WORK);
extern ziU8 Zi8SyllablesROMdata(ziWChar* keys, ziU8 keyCount, ziU8 lang, ziWChar* output,
                                ziU16 a, ziU8 b, ziU8* cntOut, ziU8 c ZI_NEED_WORK);

typedef struct _ziSwParam {
    ziU8 countOnly;      // 0x00 - same layout as ZiCandidateOptions
    ziU8 maxWordLength;  // 0x01
    ziU8 lookupMode;     // 0x02
    ziU8 suffixOnly;     // 0x03
    ziU8 controls[8];    // 0x04
    ziS32 maxCount;      // 0x0C - signed view of ZiCandidateOptions.maxCount
    ziU16 capacity;      // 0x10
    ziU8 minWordLength;  // 0x12
    ziU8 flags;          // 0x13
} ziSwParam;

ziU32 Zi8GetSyllablesCandidates(ziGetParam* param, ziSwParam* sw ZI_NEED_WORK) {
    ziWChar syllableBuffer[0x40];
    ziWChar keyLayout[0x32];
    ziS32 remainingCapacity;
    ziS32 syllableLength;
    ziS32 remainingSkip;
    ziS32 candidateCount;
    ziWChar* nextCharacter;
    ziU16 error;
    ziU8 allowHyphen;
    ziU8 needKeyFallback;
    ziU8 nextMatch;
    ziU8 reverseOrder;
    ziU8 matchedLength;
    ziWChar* output;
    ziU8* encodedOutput;
    ziS32 index;

    remainingSkip = param->firstCandidate;
    candidateCount = 0;
    encodedOutput = 0;
    nextCharacter = 0;
    allowHyphen = 1;
    needKeyFallback = 1;
    nextMatch = 0;
    reverseOrder = 0;
    matchedLength = 0;
    error = 0x64;

    if (param->currentWord != 0 && param->wordCharCount != 0 &&
        param->currentWord[param->wordCharCount - 1] != 0x20) {
        reverseOrder = 1;
    }

    if (param->elementCount == 0 || (param->elementCount == 1 && reverseOrder == 0)) {
        candidateCount = Zi8AlphaGetCandidates(param, sw, ZI_WORK);
        goto end;
    }

    if (sw->countOnly != 0 || (param->getOptions & 0xFD) != 0x81) {
        output = syllableBuffer;
        remainingCapacity = 0x40;
    } else {
        output = param->candidates;
        remainingCapacity = sw->capacity - 1;
    }
    if ((param->getOptions & 0xFD) == 0x80) {
        encodedOutput = (ziU8*)param->candidates;
        remainingCapacity = sw->capacity - 1;
    }

    if (remainingCapacity <= param->elementCount) {
        error = 0x168;
        goto end;
    }

    if ((Zi8GetTableCount(param->language, 0x1F, ZI_WORK) & 8) != 0) {
        allowHyphen = 0;
    }

    if (param->elements[0] == 0xEFF1 && param->elementCount > 1 && allowHyphen != 0) {
        syllableBuffer[0] = 0x2D;
    } else {
        Zi8getKeyLayout(param->language, param->elements[0], syllableBuffer, 1, ZI_WORK);
    }
    output[0] = syllableBuffer[0];
    Zi8SyllablesROMdata(param->elements, param->elementCount, param->language, output,
                        (ziU16)remainingCapacity, 0, &matchedLength, reverseOrder, ZI_WORK);
    if (matchedLength != 0) {
        syllableLength = matchedLength;
    } else {
        syllableLength = 1;
    }

    if (syllableLength != param->elementCount) {
        if (remainingSkip != 0) {
            remainingSkip--;
        } else if (sw->countOnly != 0) {
            if (++candidateCount >= sw->maxCount) goto end;
        } else {
            for (index = syllableLength; index < param->elementCount; index += matchedLength) {
                if (param->elements[index] == 0xEFF1 && param->elementCount - index > 1 && allowHyphen != 0) {
                    keyLayout[0] = 0x2D;
                } else {
                    Zi8getKeyLayout(param->language, param->elements[index], keyLayout, 1, ZI_WORK);
                }
                output[index] = keyLayout[0];
                Zi8SyllablesROMdata(param->elements + index, param->elementCount - index, param->language,
                                    output + index, (ziU16)remainingCapacity, 0, &matchedLength, 1, ZI_WORK);
                if (matchedLength == 0) {
                    matchedLength = 1;
                }
            }
            if (encodedOutput != 0) {
                for (index = 0; index < param->elementCount; index++) {
                    encodedOutput[index] = Zi8ConvertWC2UC(output[index], param->language, ZI_WORK);
                }
                encodedOutput[index++] = 0;
                encodedOutput[index] = 0;
                encodedOutput += index;
            } else {
                output[index++] = 0;
                output[index] = 0;
                output += index;
            }
            remainingCapacity -= index;
            if (++candidateCount >= param->maxCandidates) goto end;
            /* MWCC needs the forward capacity branch before the common exit. */
            if (remainingCapacity > param->elementCount) goto search_syllables;
            goto end;
        }
    }

search_syllables:
    for (; syllableLength >= 1; syllableLength--) {
        nextMatch = 0;
        goto match_syllable;
syllable_found:
        nextMatch = 1;
        if (syllableLength == 1) {
            needKeyFallback = 0;
        }
        if (output[0] >= 0xEFF1 && output[0] <= 0xF010) {
            continue;
        }
emit_syllable:
        if (remainingSkip != 0) {
            remainingSkip--;
        } else if (sw->countOnly != 0) {
            if (++candidateCount >= sw->maxCount) goto end;
        } else {
            if (encodedOutput != 0) {
                for (index = 0; index < syllableLength; index++) {
                    encodedOutput[index] = Zi8ConvertWC2UC(output[index], param->language, ZI_WORK);
                }
                encodedOutput[index++] = 0;
                encodedOutput[index] = 0;
                encodedOutput += index;
            } else {
                index = syllableLength;
                output[index++] = 0;
                output[index] = 0;
                output += index;
            }
            remainingCapacity -= index;
            if (++candidateCount >= param->maxCandidates) goto end;
            if (remainingCapacity <= syllableLength) goto end;
        }
next_syllable:
        if (nextCharacter != 0) {
            if (*nextCharacter == 0) goto end;
            output[0] = *nextCharacter++;
            goto emit_syllable;
        }
match_syllable:
        if (Zi8SyllablesROMdata(param->elements, (ziU8)syllableLength, param->language, output,
                                (ziU16)remainingCapacity, nextMatch, 0, reverseOrder, ZI_WORK) != 0) {
            goto syllable_found;
        }
    }
    if (needKeyFallback != 0) {
        if (param->elements[0] == 0xEFF1 && param->elementCount > 1 && allowHyphen != 0) {
            keyLayout[0] = 0x2D;
            keyLayout[1] = 0;
            Zi8getKeyLayout(param->language, param->elements[0], &keyLayout[1], 1, ZI_WORK);
            for (index = 1; keyLayout[index] != 0; index++) {
                if (keyLayout[index] == 0x2D) break;
            }
            while (keyLayout[index] != 0) {
                keyLayout[index] = keyLayout[index + 1];
                index++;
            }
        } else {
            Zi8getKeyLayout(param->language, param->elements[0], keyLayout, 1, ZI_WORK);
        }
        syllableLength = 1;
        nextCharacter = keyLayout;
        goto next_syllable;
    }

end:
    if (sw->countOnly != 0) {
        param->letters = 0;
    } else {
        param->letters = (ziU8)candidateCount;
    }
    Zi8LogError(error, ZI_WORK);
    return candidateCount;
}
