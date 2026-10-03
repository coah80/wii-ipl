#include <zi8clib/zitypes.h>

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
} ZiCandidateOptions;

const ziWChar Zi8PunctTable[40] = {
    0xFF0C, 0x3002, 0x3001, 0xFF1A, 0xFF1F, 0xFF01, 0x3005, 0x2026,
    0x2015, 0xFF1B, 0xFF0E, 0x30FB, 0x201C, 0x201D, 0xFF08, 0xFF09,
    0x300C, 0x300D, 0xFF10, 0xFF11, 0xFF12, 0xFF13, 0xFF14, 0xFF15,
    0xFF16, 0xFF17, 0xFF18, 0xFF19, 0xFF0F, 0xFF05, 0xFFE5, 0xFF04,
    0xFFE1, 0x20AC, 0x203B, 0xFF20, 0x0000,
};

ziU32 Zi8Punctuation(ziGetParam* param, ziPtr options ZI_NEED_WORK) {
    ziS32 limit = ((ZiCandidateOptions*)options)->capacity - 1;
    ziS32 count = 0;
    ziU8 i = 0;
    ziU16 fc = param->firstCandidate;
    ziU16 j = 0;

    for (;;) {
        if (Zi8PunctTable[j] == 0) {
            break;
        }
        if (fc == 0) {
            count++;
            if (((ZiCandidateOptions*)options)->countOnly == 0) {
                param->candidates[i++] = Zi8PunctTable[j];
                if ((param->context & 0x10) != 0) {
                    param->candidates[i++] = 0x20;
                    if ((ziU8)i >= limit) {
                        break;
                    }
                }
                if (count >= param->maxCandidates) {
                    break;
                }
            } else {
                if (count >= (ziS32)((ZiCandidateOptions*)options)->maxCount) {
                    return count;
                }
            }
        } else {
            fc--;
        }
        j++;
    }
    if (((ZiCandidateOptions*)options)->countOnly == 0) {
        param->letters = count;
    }
    return count;
}
