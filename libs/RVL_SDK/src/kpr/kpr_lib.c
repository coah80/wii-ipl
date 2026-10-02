#include <revolution/kpr.h>
#include <revolution/os.h>

struct KPRDeadKey {
    u16 accent;
    u16 base;
    u16 composed;
};

const struct KPRDeadKey kprDeadKeyMap[] = {
    {0x0300, 0x0300, 0x0060},
    {0x0300, 0x0041, 0x00C0},
    {0x0300, 0x0045, 0x00C8},
    {0x0300, 0x0049, 0x00CC},
    {0x0300, 0x004F, 0x00D2},
    {0x0300, 0x0055, 0x00D9},
    {0x0300, 0x0061, 0x00E0},
    {0x0300, 0x0065, 0x00E8},
    {0x0300, 0x0069, 0x00EC},
    {0x0300, 0x006F, 0x00F2},
    {0x0300, 0x0075, 0x00F9},
    {0x0301, 0x0301, 0x00B4},
    {0x0301, 0x0041, 0x00C1},
    {0x0301, 0x0045, 0x00C9},
    {0x0301, 0x0049, 0x00CD},
    {0x0301, 0x004F, 0x00D3},
    {0x0301, 0x0055, 0x00DA},
    {0x0301, 0x0059, 0x00DD},
    {0x0301, 0x0061, 0x00E1},
    {0x0301, 0x0065, 0x00E9},
    {0x0301, 0x0069, 0x00ED},
    {0x0301, 0x006F, 0x00F3},
    {0x0301, 0x0075, 0x00FA},
    {0x0301, 0x0079, 0x00FD},
    {0x0302, 0x0302, 0x005E},
    {0x0302, 0x0041, 0x00C2},
    {0x0302, 0x0045, 0x00CA},
    {0x0302, 0x0049, 0x00CE},
    {0x0302, 0x004F, 0x00D4},
    {0x0302, 0x0055, 0x00DB},
    {0x0302, 0x0061, 0x00E2},
    {0x0302, 0x0065, 0x00EA},
    {0x0302, 0x0069, 0x00EE},
    {0x0302, 0x006F, 0x00F4},
    {0x0302, 0x0075, 0x00FB},
    {0x0303, 0x0303, 0x007E},
    {0x0303, 0x0041, 0x00C3},
    {0x0303, 0x004E, 0x00D1},
    {0x0303, 0x004F, 0x00D5},
    {0x0303, 0x0061, 0x00E3},
    {0x0303, 0x006E, 0x00F1},
    {0x0303, 0x006F, 0x00F5},
    {0x0308, 0x0308, 0x00A8},
    {0x0308, 0x0041, 0x00C4},
    {0x0308, 0x0045, 0x00CB},
    {0x0308, 0x0049, 0x00CF},
    {0x0308, 0x004F, 0x00D6},
    {0x0308, 0x0055, 0x00DC},
    {0x0308, 0x0059, 0x0178},
    {0x0308, 0x0061, 0x00E4},
    {0x0308, 0x0065, 0x00EB},
    {0x0308, 0x0069, 0x00EF},
    {0x0308, 0x006F, 0x00F6},
    {0x0308, 0x0075, 0x00FC},
    {0x0308, 0x0079, 0x00FF},
    {0x0327, 0x0327, 0x00B8},
    {0x0327, 0x0043, 0x00C7},
    {0x0327, 0x0063, 0x00E7},
    {0x030D, 0x030D, 0x0027},
    {0x030D, 0x0041, 0x00C1},
    {0x030D, 0x0045, 0x00C9},
    {0x030D, 0x0049, 0x00CD},
    {0x030D, 0x004F, 0x00D3},
    {0x030D, 0x0055, 0x00DA},
    {0x030D, 0x0059, 0x00DD},
    {0x030D, 0x0043, 0x00C7},
    {0x030D, 0x0061, 0x00E1},
    {0x030D, 0x0065, 0x00E9},
    {0x030D, 0x0069, 0x00ED},
    {0x030D, 0x006F, 0x00F3},
    {0x030D, 0x0075, 0x00FA},
    {0x030D, 0x0079, 0x00FD},
    {0x030D, 0x0063, 0x00E7},
    {0x030E, 0x030E, 0x0022},
    {0x030E, 0x0041, 0x00C4},
    {0x030E, 0x0045, 0x00CB},
    {0x030E, 0x0049, 0x00CF},
    {0x030E, 0x004F, 0x00D6},
    {0x030E, 0x0055, 0x00DC},
    {0x030E, 0x0059, 0x0178},
    {0x030E, 0x0061, 0x00E4},
    {0x030E, 0x0065, 0x00EB},
    {0x030E, 0x0069, 0x00EF},
    {0x030E, 0x006F, 0x00F6},
    {0x030E, 0x0075, 0x00FC},
    {0x030E, 0x0079, 0x00FF},
    {0x0344, 0x0344, 0x0385},
    {0x0344, 0x03B9, 0x0390},
    {0x0344, 0x03C5, 0x03B0},
    {0x0308, 0x0399, 0x03AA},
    {0x0308, 0x03A5, 0x03AB},
    {0x0308, 0x03B9, 0x03CA},
    {0x0308, 0x03C5, 0x03CB},
    {0x0301, 0x0391, 0x0386},
    {0x0301, 0x0395, 0x0388},
    {0x0301, 0x0397, 0x0389},
    {0x0301, 0x0399, 0x038A},
    {0x0301, 0x039F, 0x038C},
    {0x0301, 0x03A5, 0x038E},
    {0x0301, 0x03A9, 0x038F},
    {0x0301, 0x03B1, 0x03AC},
    {0x0301, 0x03B5, 0x03AD},
    {0x0301, 0x03B7, 0x03AE},
    {0x0301, 0x03B9, 0x03AF},
    {0x0301, 0x03BF, 0x03CC},
    {0x0301, 0x03C5, 0x03CD},
    {0x0301, 0x03C9, 0x03CE},
    {0x0000, 0x0000, 0x0000},
};

const u16 kprLookupTable1252[] = {
    0x20AC, 0x0000, 0x201A, 0x0192, 0x201E, 0x2026, 0x2020, 0x2021,
    0x02C6, 0x2030, 0x0160, 0x2039, 0x0152, 0x0000, 0x017D, 0x0000,
    0x0000, 0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014,
    0x02DC, 0x2122, 0x0161, 0x203A, 0x0153, 0x0000, 0x017E, 0x0178,
};

const u16 kprLookupTable437[] = {
    0x00C7, 0x00FC, 0x00E9, 0x00E2, 0x00E4, 0x00E0, 0x00E5, 0x00E7,
    0x00EA, 0x00EB, 0x00E8, 0x00EF, 0x00EE, 0x00EC, 0x00C4, 0x00C5,
    0x00C9, 0x00E6, 0x00C6, 0x00F4, 0x00F6, 0x00F2, 0x00FB, 0x00F9,
    0x00FF, 0x00D6, 0x00DC, 0x00A2, 0x00A3, 0x00A5, 0x20A7, 0x0192,
    0x00E1, 0x00ED, 0x00F3, 0x00FA, 0x00F1, 0x00D1, 0x00AA, 0x00BA,
    0x00BF, 0x2310, 0x00AC, 0x00BD, 0x00BC, 0x00A1, 0x00AB, 0x00BB,
    0x2591, 0x2592, 0x2593, 0x2502, 0x2524, 0x2561, 0x2562, 0x2556,
    0x2555, 0x2563, 0x2551, 0x2557, 0x255D, 0x255C, 0x255B, 0x2510,
    0x2514, 0x2534, 0x252C, 0x251C, 0x2500, 0x253C, 0x255E, 0x255F,
    0x255A, 0x2554, 0x2569, 0x2566, 0x2560, 0x2550, 0x256C, 0x2567,
    0x2568, 0x2564, 0x2565, 0x2559, 0x2558, 0x2552, 0x2553, 0x256B,
    0x256A, 0x2518, 0x250C, 0x2588, 0x2584, 0x258C, 0x2590, 0x2580,
    0x03B1, 0x00DF, 0x0393, 0x03C0, 0x03A3, 0x03C3, 0x00B5, 0x03C4,
    0x03A6, 0x0398, 0x03A9, 0x03B4, 0x221E, 0x03C6, 0x03B5, 0x2229,
    0x2261, 0x00B1, 0x2265, 0x2264, 0x2320, 0x2321, 0x00F7, 0x2248,
    0x00B0, 0x2219, 0x00B7, 0x221A, 0x207F, 0x00B2, 0x25A0, 0x00A0,
};

static void (*kprProcDeadKeysFP)(KPRQueue* queue) = NULL;
static void (*kprProcRomajiFP)(KPRQueue* queue) = NULL;
const char* __KPRVersion = "<< RVL_SDK - KPR \trelease build: Apr 20 2010 11:21:44 (0x4199_60831) >>";

void KPRProcessDeadKeys(KPRQueue* queue);
BOOL KPRProcessAltKeypad(KPRQueue* queue, u16 character);

void KPRInitRegionUS(void) {
    kprProcDeadKeysFP = KPRProcessDeadKeys;
}

void KPRInitQueue(KPRQueue* queue) {
    static union { u64 align; u8 flag; } once;
    if (!once.flag) {
        OSRegisterVersion(__KPRVersion);
        once.flag = TRUE;
    }
    queue->mode = KPR_MODE_ALT_KEYPAD;
    queue->oCount = 0;
    queue->iCount = 0;
    queue->altVal = 0;
}

void KPRClearQueue(KPRQueue* queue) {
    queue->oCount = 0;
    queue->iCount = 0;
    queue->altVal = 0;
}

void KPRSetMode(KPRQueue* queue, KPRMode mode) {
    queue->mode = mode;
    queue->oCount = 0;
    queue->iCount = 0;
    queue->altVal = 0;
}

u8 KPRPutChar(KPRQueue* queue, u16 character) {
    BOOL interrupts;
    if (queue->oCount + queue->iCount + 1 >= 5) {
        OSPanic("kpr_lib.c", 215, "KPRPutChar: Overflow");
    }
    interrupts = OSDisableInterrupts();
    if (!(queue->mode & KPR_MODE_ALT_KEYPAD) || !KPRProcessAltKeypad(queue, character)) {
        queue->text[queue->oCount + queue->iCount] = character;
        ++queue->iCount;
        if (queue->mode & KPR_MODE_DEADKEY) {
            kprProcDeadKeysFP(queue);
        } else if ((queue->mode & KPR_MODE_JP_ROMAJI_KATAKANA) || (queue->mode & KPR_MODE_JP_ROMAJI_HIRAGANA)) {
            kprProcRomajiFP(queue);
        } else {
            queue->oCount = queue->iCount;
            queue->iCount = 0;
        }
        if (character == 0xFFFF) {
            --queue->oCount;
        }
    }
    OSRestoreInterrupts(interrupts);
    return queue->oCount;
}

u16 KPRGetChar(KPRQueue* queue) {
    BOOL interrupts;
    u16 character;
    u16* source;
    u32 index;
    if (!queue->oCount) {
        return 0;
    }
    interrupts = OSDisableInterrupts();
    character = queue->text[0];
    source = &queue->text[1];
    for (index = 1; index < queue->iCount + queue->oCount; ++index) {
        source[-1] = *source;
        ++source;
    }
    --queue->oCount;
    OSRestoreInterrupts(interrupts);
    return character;
}

u8 KPRLookAhead(KPRQueue* queue, u16* destination, u32 capacity) {
    BOOL interrupts;
    u8 index;
    if (destination == NULL || capacity == 0) {
        return queue->iCount + queue->oCount;
    }
    interrupts = OSDisableInterrupts();
    for (index = 0; index < queue->iCount + queue->oCount && index < capacity; ++index) {
        destination[index] = queue->text[index];
    }
    if (index < capacity) {
        destination[index] = 0;
    }
    OSRestoreInterrupts(interrupts);
    return queue->iCount + queue->oCount;
}

static inline u32 KPRConvertAltValue(u32 value, u32 leadingZero) {
    if (value >= 128 && value <= 255) {
        if (leadingZero) {
            if (value < 160) {
                value = kprLookupTable1252[value - 128];
            }
        } else {
            value = kprLookupTable437[value - 128];
        }
    } else if (value > 255) {
        u32 converted = 32;
        if (value <= 0x6666666) {
            converted = (u8)value;
        }
        value = converted;
    }
    return value;
}

BOOL KPRProcessAltKeypad(KPRQueue* queue, u16 character) {
    if (queue->altVal != 0) {
        u32 accumulator = queue->altVal & 0x7FFFFFFF;
        u32 value;
        u32 leadingZero = queue->altVal & 0x80000000;
        queue->altVal = accumulator;
        if (character >= 0xF130 && character <= 0xF139) {
            if (accumulator > 0x6666666) {
                return TRUE;
            }
            queue->altVal = leadingZero | (character - 0xF130 + accumulator * 10);
            return TRUE;
        }
        value = queue->altVal;
        value = KPRConvertAltValue(value, leadingZero);
        {
            u16* destination;
            int index = queue->oCount + queue->iCount;
            destination = &queue->text[index];
            for (; index > queue->oCount; --index, --destination) {
                *destination = destination[-1];
            }
        }
        queue->text[queue->oCount] = value;
        queue->altVal = 0;
        ++queue->oCount;
        return character == 0;
    }
    if (character >= 0xF130 && character <= 0xF139) {
        if (character == 0xF130) {
            queue->altVal = 0x80000000;
        } else {
            queue->altVal = character - 0xF130;
        }
        return TRUE;
    }
    if (character == 0) {
        return TRUE;
    }
    return FALSE;
}

void KPRProcessDeadKeys(KPRQueue* queue) {
    int index;
    int firstFallback;
    u32 secondFallback;
    if (queue->iCount == 1) {
        for (index = 0; index < 107; ++index) {
            if (queue->text[queue->oCount] == kprDeadKeyMap[index].accent) {
                return;
            }
        }
        ++queue->oCount;
        queue->iCount = 0;
        return;
    }
    secondFallback = 107;
    for (index = 0; index < 107; ++index) {
        if (queue->text[queue->oCount] == kprDeadKeyMap[index].accent && queue->text[queue->oCount + 1] == kprDeadKeyMap[index].base) {
            queue->text[queue->oCount] = kprDeadKeyMap[index].composed;
            queue->iCount = 0;
            ++queue->oCount;
            return;
        }
        if (queue->text[queue->oCount] == kprDeadKeyMap[index].accent && queue->text[queue->oCount] == kprDeadKeyMap[index].base) {
            firstFallback = index;
        }
        if (queue->text[queue->oCount + 1] == kprDeadKeyMap[index].accent && queue->text[queue->oCount + 1] == kprDeadKeyMap[index].base) {
            secondFallback = index;
        }
    }
    queue->text[queue->oCount] = kprDeadKeyMap[firstFallback].composed;
    if (secondFallback < 107) {
        queue->text[queue->oCount + 1] = kprDeadKeyMap[secondFallback].composed;
    }
    queue->iCount = 0;
    queue->oCount += 2;
    return;
}
