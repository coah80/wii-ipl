#include <private/vi.h>
#include <revolution/kbd.h>
#include <revolution/os.h>
#include <revolution/usbkbd.h>
#include <revolution/verdefs.h>

typedef union {
    u32 value;
    struct {
        u32 locks : 26;
        u32 physical : 6;
    } bits;
    struct {
        u32 flags : 26;
        u32 rightAlt : 1;
        u32 leftAlt : 1;
        u32 rightShift : 1;
        u32 leftShift : 1;
        u32 rightControl : 1;
        u32 leftControl : 1;
    } keys;
} KBDModifierState;

typedef struct {
    u8 codeCount;
    u8 flags;
    u16* keyMap;
    u16* modifierMap;
    u8 lockIndex;
    u8 shiftIndex;
    u8 altIndex;
    u8 maxCode;
    u8 keypadMap[8];
    u8 keypadCount;
} KBDKeyMap;

typedef union {
    KBDKeyMap maps[36];
    u8 storage[0x400];
} KBDKeyMapTable;

typedef struct {
    u8 channel;
    u8 code;
    u32 state;
    u32 modifiers;
    u16 translated;
} KBDKeyEventData;

typedef struct {
    u8 channel;
    s32 country;
    u32 flags;
    void* device;
    u8 modifiers;
    u8 reportReserved;
    u8 keys[6];
    KBDKeyEventData events[32];
    u8 writeIndex;
    u8 readIndex;
    u32 lockProcessing;
    u32 modState;
    u8 lockCount[6];
    u16 repeatDelay;
    u16 repeatInterval;
    u8 repeatKey;
    OSAlarm alarm;
    u32 lockState;
} KBDChannel;

typedef struct {
    USBKBDCmdLEDCallback callbackAddress;
    void* callbackArg;
} KBDLEDCallbackData;

const char* __KBDVersion =
    "<< RVL_SDK - KBD \trelease build: Apr 20 2010 11:21:43 (0x4199_60831) >>";

static void (*kbdKeyCallback)(KBDKeyEventData* event);
static USBKBDDetachCallback kbdDevDetachCallback;
static USBKBDAttachCallback kbdDevAttachCallback;
static BOOL kbdInitialized;

KBDKeyMapTable kbdKeyMaps = {0};
typedef struct {
    u32 device;
    u8 leds;
    u32 transfer[4];
    USBKBDCmdLEDCallback callback;
    void* callbackArg;
} KBDLEDCommand;

KBDLEDCommand kbdCmdBuf[12] = {0};
KBDChannel kbdData[4];
KBDLEDCallbackData kbdLCBuf[12];

u16 kbdKeyMapUS_International[500] = {
    0x00FF, 0x0061, 0x0041, 0x00E1, 0x00C1, 0x003F, 0x0062, 0x0042, 0x0000, 0x0000,
    0x003F, 0x0063, 0x0043, 0x00A9, 0x00A2, 0x00FF, 0x0064, 0x0044, 0x00F0, 0x00D0,
    0x00FF, 0x0065, 0x0045, 0x00E9, 0x00C9, 0x003F, 0x0066, 0x0046, 0x0000, 0x0000,
    0x003F, 0x0067, 0x0047, 0x0000, 0x0000, 0x003F, 0x0068, 0x0048, 0x0000, 0x0000,
    0x00FF, 0x0069, 0x0049, 0x00ED, 0x00CD, 0x003F, 0x006A, 0x004A, 0x0000, 0x0000,
    0x003F, 0x006B, 0x004B, 0x0000, 0x0000, 0x00FF, 0x006C, 0x004C, 0x00F8, 0x00D8,
    0x003F, 0x006D, 0x004D, 0x00B5, 0x0000, 0x00FF, 0x006E, 0x004E, 0x00F1, 0x00D1,
    0x00FF, 0x006F, 0x004F, 0x00F3, 0x00D3, 0x00FF, 0x0070, 0x0050, 0x00F6, 0x00D6,
    0x00FF, 0x0071, 0x0051, 0x00E4, 0x00C4, 0x003F, 0x0072, 0x0052, 0x00AE, 0x0000,
    0x003F, 0x0073, 0x0053, 0x00DF, 0x00A7, 0x00FF, 0x0074, 0x0054, 0x00FE, 0x00DE,
    0x00FF, 0x0075, 0x0055, 0x00FA, 0x00DA, 0x003F, 0x0076, 0x0056, 0x0000, 0x0000,
    0x00FF, 0x0077, 0x0057, 0x00E5, 0x00C5, 0x003F, 0x0078, 0x0058, 0x0000, 0x0000,
    0x00FF, 0x0079, 0x0059, 0x00FC, 0x00DC, 0x00FF, 0x007A, 0x005A, 0x00E6, 0x00C6,
    0x0000, 0x0031, 0x0021, 0x00A1, 0x00B9, 0x0000, 0x0032, 0x0040, 0x00B2, 0x0000,
    0x0000, 0x0033, 0x0023, 0x00B3, 0x0000, 0x0000, 0x0034, 0x0024, 0x00A4, 0x00A3,
    0x0000, 0x0035, 0x0025, 0x20AC, 0x0000, 0x0000, 0x0036, 0x0302, 0x00BC, 0x0000,
    0x0000, 0x0037, 0x0026, 0x00BD, 0x0000, 0x0000, 0x0038, 0x002A, 0x00BE, 0x0000,
    0x0000, 0x0039, 0x0028, 0x2018, 0x0000, 0x0000, 0x0030, 0x0029, 0x2019, 0x0000,
    0x0000, 0xF1CD, 0xF1CD, 0xF1CD, 0xF1CD, 0x0000, 0xF1DB, 0xF1DB, 0xF1DB, 0xF1DB,
    0x0000, 0xF1C8, 0xF1C8, 0xF1C8, 0xF1C8, 0x0000, 0xF1C9, 0xF1C9, 0xF1C9, 0xF1C9,
    0x0000, 0x0020, 0x0020, 0x0020, 0x0020, 0x0000, 0x002D, 0x005F, 0x00A5, 0x0000,
    0x0000, 0x003D, 0x002B, 0x00D7, 0x00F7, 0x0000, 0x005B, 0x007B, 0x00AB, 0x0000,
    0x0000, 0x005D, 0x007D, 0x00BB, 0x0000, 0x0000, 0x005C, 0x007C, 0x00AC, 0x00A6,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x003B, 0x003A, 0x00B6, 0x00B0,
    0x0000, 0x030D, 0x030E, 0x00B4, 0x00A8, 0x0000, 0x0300, 0x0303, 0x0000, 0x0000,
    0x00C0, 0x002C, 0x003C, 0x00E7, 0x00C7, 0x0000, 0x002E, 0x003E, 0x0000, 0x0000,
    0x0000, 0x002F, 0x003F, 0x00BF, 0x0000, 0xC000, 0xF008, 0xF008, 0xF008, 0xF008,
    0x0000, 0xF061, 0xF061, 0xF061, 0xF061, 0x0000, 0xF062, 0xF062, 0xF062, 0xF062,
    0x0000, 0xF063, 0xF063, 0xF063, 0xF063, 0x0000, 0xF064, 0xF064, 0xF064, 0xF064,
    0x0000, 0xF065, 0xF065, 0xF065, 0xF065, 0x0000, 0xF066, 0xF066, 0xF066, 0xF066,
    0x0000, 0xF067, 0xF067, 0xF067, 0xF067, 0x0000, 0xF068, 0xF068, 0xF068, 0xF068,
    0x0000, 0xF069, 0xF069, 0xF069, 0xF069, 0x0000, 0xF06A, 0xF06A, 0xF06A, 0xF06A,
    0x0000, 0xF06B, 0xF06B, 0xF06B, 0xF06B, 0x0000, 0xF06C, 0xF06C, 0xF06C, 0xF06C,
    0xC000, 0xF020, 0xF020, 0xF020, 0xF020, 0xC000, 0xF021, 0xF021, 0xF021, 0xF021,
    0xC000, 0xF022, 0xF022, 0xF022, 0xF022, 0x0000, 0xF1B0, 0xF1B0, 0xF1B0, 0xF1B0,
    0x0000, 0xF1B7, 0xF1B7, 0xF1B7, 0xF1B7, 0x0000, 0xF1B9, 0xF1B9, 0xF1B9, 0xF1B9,
    0x0000, 0xF1AE, 0xF1AE, 0xF1AE, 0xF1AE, 0x0000, 0xF1B1, 0xF1B1, 0xF1B1, 0xF1B1,
    0x0000, 0xF1B3, 0xF1B3, 0xF1B3, 0xF1B3, 0x0000, 0xF1B6, 0xF1B6, 0xF1B6, 0xF1B6,
    0x0000, 0xF1B4, 0xF1B4, 0xF1B4, 0xF1B4, 0x0000, 0xF1B2, 0xF1B2, 0xF1B2, 0xF1B2,
    0x0000, 0xF1B8, 0xF1B8, 0xF1B8, 0xF1B8, 0xC000, 0xF007, 0xF007, 0xF007, 0xF007,
    0x0000, 0xF12F, 0xF12F, 0xF12F, 0xF12F, 0x0000, 0xF12A, 0xF12A, 0xF12A, 0xF12A,
    0x0000, 0xF12D, 0xF12D, 0xF12D, 0xF12D, 0x0000, 0xF12B, 0xF12B, 0xF12B, 0xF12B,
    0x0000, 0xF10D, 0xF10D, 0xF10D, 0xF10D, 0x80FF, 0xF171, 0xF131, 0x0000, 0x0000,
    0x80FF, 0xF172, 0xF132, 0x0000, 0x0000, 0x80FF, 0xF173, 0xF133, 0x0000, 0x0000,
    0x80FF, 0xF174, 0xF134, 0x0000, 0x0000, 0x80FF, 0xF175, 0xF135, 0x0000, 0x0000,
    0x80FF, 0xF176, 0xF136, 0x0000, 0x0000, 0x80FF, 0xF177, 0xF137, 0x0000, 0x0000,
    0x80FF, 0xF178, 0xF138, 0x0000, 0x0000, 0x80FF, 0xF179, 0xF139, 0x0000, 0x0000,
    0x80FF, 0xF170, 0xF130, 0x0000, 0x0000, 0x80FF, 0xF16E, 0xF12E, 0x0000, 0x0000,
    0x0000, 0x005C, 0x007C, 0x0000, 0x0000, 0xC000, 0xF02F, 0xF02F, 0xF02F, 0xF02F,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xF13D, 0xF13D, 0xF13D, 0xF13D
};

u16 kbdModifierMapUS_International[40] = {
    0xC000, 0xF000, 0xF000, 0xF000, 0xF000, 0xC000, 0xF001, 0xF001, 0xF001, 0xF001,
    0xC000, 0xF002, 0xF002, 0xF002, 0xF002, 0xC000, 0xF003, 0xF003, 0xF003, 0xF003,
    0xC000, 0xF000, 0xF000, 0xF000, 0xF000, 0xC000, 0xF001, 0xF001, 0xF001, 0xF001,
    0xC000, 0xF005, 0xF005, 0xF005, 0xF005, 0xC000, 0xF003, 0xF003, 0xF003, 0xF003
};

static u16 noRepeatKeys[7] = {0xf006, 0xf008, 0xf007, 0xf021, 0xf020, 0xf022, 0xf02f};

USBKBDErr KBDSetModState(u32 channel, u32 value);
USBKBDErr KBDResetChannel(u32 channel);
u16 KBDTranslateHidCode(u32 keyCode, u32 modifiers, s32 country);

static void kbdAttachHandler(void* device);
static void kbdDetachHandler(void* device);
static void kbdEventHandler(void* device, char* report);
static void kbdRepeatHandler(OSAlarm* alarm, OSContext* context);
static void kbdProcKey(u32 key, u32 state, u32 channel);
static void kbdProcMod(u32 key, u32 state, u32 channel);
static void kbdSendKey(KBDKeyEventData* event);
static void kbd_led_handler(BOOL success, void* callbackArg);

static void kbdAttachHandler(void* device) {
    u32 channel;
    channel = 0;

    for (channel = 0; channel < 4; channel++) {
        if (kbdData[(u8)channel].device == NULL) {
            break;
        }
    }

    if (channel != 4) {
        u8 event[1];

        kbdData[channel].device = device;
        kbdData[channel].flags &= ~1;
        KBDResetChannel(channel);
        VIResetDimmingCount();

        if (kbdDevAttachCallback != NULL) {
            event[0] = (u8)channel;
            kbdDevAttachCallback(event);
        }
    }
}

static void kbdDetachHandler(void* device) {
    u32 channel;
    channel = 0;

    for (channel = 0; channel < 4; channel++) {
        if (device == kbdData[(u8)channel].device) {
            break;
        }
    }

    if (channel != 4) {
        u8 event[1];

        kbdData[channel].device = NULL;
        kbdData[channel].flags |= 1;

        if (kbdDevDetachCallback != NULL) {
            event[0] = (u8)channel;
            kbdDevDetachCallback(event);
        }

        KBDResetChannel(channel);
    }
}

static void kbdEventHandler(void* device, char* report) {
    u32 channel;
    channel = 0;

    for (channel = 0; channel < 4; channel++) {
        if (device == kbdData[(u8)channel].device) {
            break;
        }
    }

    if (channel != 4) {
        KBDChannel* data;
        u8* bytes;
        u8 status;
        data = kbdData;
        data += channel;
        bytes = (u8*)report;
        status = bytes[2];

        if ((u8)(bytes[2] + 0xff) <= 2) {
            OSCancelAlarm(&data->alarm);

            if (bytes[2] == 1) {
                data->flags |= 2;
            } else {
                data->flags |= 4;
            }
        } else {
            s32 i;
            u32 mask;
            data->flags = 0;
            VIResetDimmingCount();


            for (mask = 1, i = 0; i < 8; i++, mask <<= 1) {
                if ((data->modifiers & mask) != 0) {
                    if ((bytes[0] & mask) == 0) {
                        kbdProcKey((u8)(i + 0xe0), 0, channel);
                    }
                } else if ((bytes[0] & mask) != 0) {
                    kbdProcKey((u8)(i + 0xe0), 1, channel);
                }
            }


            for (i = 0; i < 6; i++) {
                u8 key;
                s32 j;
                key = data->keys[(s8)i];
                j = 0;

                if (key != 0) {
                    for (j = 0; j < 6; j++) {
                        if (key == bytes[j + 2]) {
                            break;
                        }
                    }

                    if (j == 6) {
                        kbdProcKey(key, 0, channel);
                        data->keys[(s8)i] = 0;
                    }
                }
            }


            for (i = 0; i < 6; i++) {
                u8 key;
                s32 j;
                key = bytes[(s8)i + 2];
                j = 0;

                if (key != 0) {
                    for (j = 0; j < 6; j++) {
                        if (key == data->keys[j]) {
                            break;
                        }
                    }

                    if (j == 6) {
                        kbdProcKey(key, 1, channel);
                    }
                }
            }

            data->modifiers = bytes[0];
            data->keys[0] = bytes[2];
            data->keys[1] = bytes[3];
            data->keys[2] = bytes[4];
            data->keys[3] = bytes[5];
            data->keys[4] = bytes[6];
            data->keys[5] = bytes[7];
        }
    }
}

static void kbdRepeatHandler(OSAlarm* alarm, OSContext* context) {
    KBDChannel* data;
    data = (KBDChannel*)OSGetAlarmUserData(alarm);

    kbdProcKey(data->repeatKey, 3, data->channel);
}

static inline USBKBDErr kbdGetModState(u32 channel, u32* modifiers) {
    if (!kbdInitialized) {
        return 2;
    }
    if (channel >= 4 || modifiers == NULL) {
        return 4;
    }
    *modifiers = kbdData[channel].modState;
    return 0;
}

static void kbdProcKey(u32 key, u32 pressed, u32 channel) {
    KBDChannel* data;
    KBDKeyMap* map;
    s32 keyCount;
    s32 i;
    u32 j;
    u16 translated;
    OSTime timeout;
    KBDKeyEventData event;
    data = &kbdData[channel];

    event.channel = channel;
    event.state = pressed;
    kbdGetModState(channel, &event.modifiers);
    map = &kbdKeyMaps.maps[data->country];
    keyCount = map->keypadCount;
    for (i = 0; i < keyCount; i++) {
        if (key == map->keypadMap[i * 2]) {
            key = map->keypadMap[i * 2 + 1];
            break;
        }
    }
    event.code = key;
    translated = KBDTranslateHidCode(key, event.modifiers,
                                     data->country);
    event.translated = translated;
    if ((translated == 0xF000) || (translated == 0xF001) ||
        (translated == 0xF002) || (translated == 0xF003) ||
        (translated == 0xF004) || (translated == 0xF005) ||
        (translated == 0xF006) || (translated == 0xF007) ||
        (translated == 0xF008) || (translated == 0xF021)) {
        kbdProcMod(translated, pressed, channel);
        if ((translated != 0xF006) && (translated != 0xF007) &&
            (translated != 0xF008) && (translated != 0xF021)) {
            kbdSendKey(&event);
            return;
        }
    }
    if ((pressed & 1) == 0) {
        if (key == data->repeatKey) {
            OSCancelAlarm(&data->alarm);
        }
        kbdSendKey(&event);
        return;
    }
    OSCancelAlarm(&data->alarm);
    for (j = 0; j < 7; j++) {
        if (translated == noRepeatKeys[j]) {
            break;
        }
    }
    if (j == 7) {
        data->repeatKey = key;
        if (data->repeatDelay != 0) {
            if ((pressed & 2) != 0) {
                timeout = data->repeatInterval * (OS_TIMER_CLOCK / 1000);
            } else {
                timeout = data->repeatDelay * (OS_TIMER_CLOCK / 1000);
            }
            OSSetAlarm(&data->alarm, timeout, kbdRepeatHandler);
        }
    }
    event.translated = translated;
    kbdSendKey(&event);
}

static void kbdProcMod(u32 key, u32 pressed, u32 channel) {
    u32 stateBuf[1];
    KBDModifierState* state;
    s32 delta;
    u8 flags;

    u32 finalState;
    s8 value;
    delta = (pressed & 1) != 0 ? 1 : -1;
    state = (KBDModifierState*)stateBuf;
    state->value = kbdData[channel].modState;
    flags = kbdKeyMaps.maps[kbdData[channel].country].flags;

    kbdGetModState(channel, &state->value);
    switch (key) {
    case 0xF001:
        if (kbdData[channel].lockState != 0) {
            if ((pressed & 1) != 0) {
                state->value ^= 2;
            }
        } else {
            value = kbdData[channel].lockCount[1] + delta;
            kbdData[channel].lockCount[1] = value;
            state->keys.rightControl = (u8)value != 0;
        }
        break;
    case 0xF005:
        if (kbdData[channel].lockState != 0) {
            if ((pressed & 1) != 0) {
                state->value ^= 0x20;
            }
        } else {
            value = kbdData[channel].lockCount[4] + delta;
            kbdData[channel].lockCount[4] = value;
            state->keys.rightAlt = (u8)value != 0;
        }
        break;
    case 0xF000:
        if (kbdData[channel].lockState != 0) {
            if ((pressed & 1) != 0) {
                state->value ^= 1;
            }
        } else {
            value = kbdData[channel].lockCount[0] + delta;
            kbdData[channel].lockCount[0] = value;
            state->keys.leftControl = (u8)value != 0;
        }
        break;
    case 0xF008:
        if (((pressed & 1) != 0) && (kbdData[channel].lockProcessing != 0)) {
            state->value ^= 0x200;
        }
        break;
    case 0xF007:
        if (((pressed & 1) != 0) && (kbdData[channel].lockProcessing != 0)) {
            state->value ^= 0x100;
        }
        break;
    case 0xF006:
        if (((pressed & 1) != 0) && (kbdData[channel].lockProcessing != 0)) {
            u32 oldState;
            u32 lockState;
            oldState = state->value;
            lockState = oldState & 0xC0;
            switch (lockState) {
            case 0:
                if ((flags & 1) == 1) {
                    state->value = oldState | 0x40;
                }
                break;
            case 0x40:
                {
                    state->value = oldState & 0xFFFFFFBF;
                    if ((flags & 4) == 4) {
                        state->value = oldState & 0xFFFFFFBF | 0x80;
                    }
                }
                break;
            case 0x80:
                state->value = oldState & 0xFFFFFF7F;
                break;
            case 0xC0:
                state->value = oldState & 0xFFFFFF3F;
                break;
            }
        }
        break;
    case 0xF002:
        if (kbdData[channel].lockState != 0) {
            if ((pressed & 1) != 0) {
                state->value ^= 4;
            }
        } else {
            value = kbdData[channel].lockCount[2] + delta;
            kbdData[channel].lockCount[2] = value;
            state->keys.leftShift = (u8)value != 0;
        }
        break;
    case 0xF003:
        if (kbdData[channel].lockState != 0) {
            if ((pressed & 1) != 0) {
                state->value ^= 8;
            }
        } else {
            value = kbdData[channel].lockCount[3] + delta;
            kbdData[channel].lockCount[3] = value;
            state->keys.rightShift = (u8)value != 0;
        }
        break;
    case 0xF004:
        if (kbdData[channel].lockState != 0) {
            if ((pressed & 1) != 0) {
                state->value ^= 0x10;
            }
        } else {
            value = kbdData[channel].lockCount[5] + delta;
            kbdData[channel].lockCount[5] = value;
            state->keys.leftAlt = (u8)value != 0;
        }
        break;
    case 0xF021:
        if (((pressed & 1) != 0) && (kbdData[channel].lockProcessing != 0)) {
            state->value ^= 0x400;
        }
        break;
    }
    finalState = state->value | 0x1000;
    KBDSetModState(channel, finalState);
}

static void kbdSendKey(KBDKeyEventData* event) {
    KBDChannel* data;
    u8 head;
    u8 tail;
    u8 next;
    if (kbdKeyCallback != NULL) {
        kbdKeyCallback(event);
    }
    data = &kbdData[event->channel];
    tail = data->readIndex;
    head = data->writeIndex;
    if (head != tail) {
        next = (head + 1) % 0x20;
        if (next == tail) {
            data->events[head].channel = event->channel;
            data->events[data->writeIndex].code = 0xff;
            data->events[data->writeIndex].state = 0;
            data->events[data->writeIndex].modifiers = 0;
            data->events[data->writeIndex].translated = 0;
        } else {
            data->events[head] = *event;
            if (data->readIndex == 0x20) {
                data->readIndex = data->writeIndex;
            }
        }
        data->writeIndex = next;
    }
}

static inline u32 kbdChannelFlags(u32 channel) {
    return kbdData[channel].flags;
}

static void kbd_led_handler(BOOL success, void* callbackArg) {
    u32 index;
    u32 err;
    index = (u32)callbackArg;
    kbdCmdBuf[index].device = 0;
    if (kbdLCBuf[index].callbackAddress == (USBKBDCmdLEDCallback)(u32)kbdCmdBuf[index].device) {
        return;
    }
    switch (success) {
    default:
        err = 7;
        break;
    case TRUE:
        err = 0;
        break;
    }
    kbdLCBuf[index].callbackAddress(err, kbdLCBuf[index].callbackArg);
}

USBKBDErr KBDSetLedsAsync(u32 channel, u32 leds, USBKBDCmdLEDCallback callback, void* callbackArg) {
    s32 index;
    u32 ofs;
    u8 ledBits;
    BOOL interrupts;
    USBKBDErr result;
    if (!kbdInitialized) {
        return 2;
    }
    if (channel >= 4) {
        return 4;
    }
    if ((s32)kbdChannelFlags(channel) == 1 || (s32)kbdChannelFlags(channel) == 4) {
        return 5;
    }
    ledBits = leds;
    interrupts = OSDisableInterrupts();
    for (index = 0, ofs = 0; index < 12; index++, ofs += sizeof(KBDLEDCommand)) {
        if (*(u32*)&((u8*)kbdCmdBuf)[ofs] == 0) {
            *(u32*)&((u8*)kbdCmdBuf)[ofs] = (u32)kbdData[channel].device;
            break;
        }
    }
    OSRestoreInterrupts(interrupts);
    if (index == 12) {
        return 7;
    }
    kbdLCBuf[index].callbackAddress = callback;
    kbdLCBuf[index].callbackArg = callbackArg;
    result = USBKBDSetLEDAsync((u32)kbdData[channel].device, ledBits,
                               (USBKBDCmdLEDAsync*)&kbdCmdBuf[index],
                               kbd_led_handler, (void*)index);
    switch (result) {
    default:
        return 7;
    case 0:
        return 0;
    }
}

USBKBDErr KBDSetLeds(u32 channel, u32 leds) {
    u32 index;
    u32 ofs;
    BOOL interrupts;
    USBKBDErr result;
    u8 ledBits;
    if (!kbdInitialized) {
        return 2;
    }
    if (channel >= 4) {
        return 4;
    }
    if ((s32)kbdChannelFlags(channel) == 1 || (s32)kbdChannelFlags(channel) == 4) {
        return 5;
    }
    ledBits = leds & 0xff;
    interrupts = OSDisableInterrupts();
    index = 0;
    ofs = 0;
    while (index < 12) {
        if (*(u32*)&((u8*)kbdCmdBuf)[ofs] == 0) {
            *(u32*)&((u8*)kbdCmdBuf)[ofs] = (u32)kbdData[channel].device;
            break;
        }
        index++;
        ofs += sizeof(KBDLEDCommand);
    }
    OSRestoreInterrupts(interrupts);
    if (index == 12) {
        return 7;
    }
    result = USBKBDSetLED((u32)kbdData[channel].device, ledBits,
                          (USBKBDCmdLED*)&kbdCmdBuf[index]);
    kbdCmdBuf[index].device = 0;
    switch (result) {
    default:
        return 7;
    case 0:
        return 0;
    }
}

void kbdInitMap(u32 country, u8 codeCount, u8 flags, u16* keyMap, u16* modifierMap,
                u8 lockIndex, u8 shiftIndex, u8 altIndex, u8 maxCode, s32 keypadType) {
    KBDKeyMap* map;
    map = &kbdKeyMaps.maps[country];

    map->codeCount = codeCount;
    map->flags = flags;
    map->keyMap = keyMap;
    map->modifierMap = modifierMap;
    map->lockIndex = lockIndex;
    map->shiftIndex = shiftIndex;
    map->altIndex = altIndex;
    map->maxCode = maxCode;

    switch (keypadType) {
    case 0:
        map->keypadMap[0] = 0x32;
        map->keypadMap[1] = 0x31;
        map->keypadCount = 1;
        break;
    case 1:
        map->keypadMap[0] = 0x31;
        map->keypadMap[1] = 0x32;
        map->keypadMap[2] = 0x94;
        map->keypadMap[3] = 0x35;
        map->keypadCount = 2;
        break;
    case 2:
        map->keypadMap[0] = 0x31;
        map->keypadMap[1] = 0x32;
        map->keypadCount = 1;
        break;
    }
}

void kbdInitMapIntl(void) {
    kbdInitMap(0, 5, 0x30, kbdKeyMapUS_International,
               kbdModifierMapUS_International, 0, 0, 3, 100, 0);
}

USBKBDErr KBDInit(void) {
    USBKBDErr result;
        u32 i;

    if (kbdInitialized) {
        return 3;
    }
        OSRegisterVersion(__KBDVersion);
        kbdInitialized = TRUE;


        for (i = 0; i < 4; i++) {
            KBDChannel* data;
            data = &kbdData[(u8)i];

            data->channel = (u8)i;
            data->country = 0x21;
            data->flags = 1;
            data->device = NULL;
            data->lockProcessing = 1;
            data->repeatDelay = 500;
            data->repeatInterval = 0x21;
            data->lockState = 0;

            OSCreateAlarm(&data->alarm);
            OSSetAlarmUserData(&data->alarm, data);
            KBDResetChannel((u8)i);
        }

        if (USBKBDInitialize(kbdAttachHandler, kbdDetachHandler) != 0) {
            result = 1;
        } else {
            result = USBKBDRegisterEventCallback(kbdEventHandler);
            result = (USBKBDErr)((-(u32)result | (u32)result) >> 31);
        }


    return result;
}

USBKBDAttachCallback KBDSetAttachCallback(USBKBDAttachCallback callback) {
    USBKBDAttachCallback previous = kbdDevAttachCallback;

    kbdDevAttachCallback = callback;
    return previous;
}

USBKBDDetachCallback KBDSetDetachCallback(USBKBDDetachCallback callback) {
    USBKBDDetachCallback previous = kbdDevDetachCallback;

    kbdDevDetachCallback = callback;
    return previous;
}

void (*KBDSetKeyCallback(void (*callback)(KBDKeyEventData* event)))(KBDKeyEventData* event) {
    void (*previous)(KBDKeyEventData* event) = kbdKeyCallback;

    kbdKeyCallback = callback;
    return previous;
}

USBKBDErr KBDResetChannel(u32 channel) {
    if (!kbdInitialized) {
        return 2;
    }

    if (channel >= 4) {
        return 4;
    }
    {
        KBDChannel* data;
        data = &kbdData[channel];

        data->modifiers = 0;
        data->keys[0] = 0;
        data->keys[1] = 0;
        data->keys[2] = 0;
        data->keys[3] = 0;
        data->keys[4] = 0;
        data->keys[5] = 0;
        data->readIndex = 0x20;
        KBDSetModState(channel, 0x1000);
        data->lockCount[0] = 0;
        data->lockCount[1] = 0;
        data->lockCount[2] = 0;
        data->lockCount[3] = 0;
        data->lockCount[4] = 0;
        data->lockCount[5] = 0;
        data->repeatKey = 0;
        OSCancelAlarm(&data->alarm);
        return 0;
    }
}

USBKBDErr KBDSetCountry(u32 channel, s32 country) {
    if (!kbdInitialized) {
        return 2;
    }
    if (channel >= 4) {
        return 4;
    }
    if (country > 0x23) {
        return 4;
    }
    if (kbdKeyMaps.maps[country].codeCount == 0) {
        return 4;
    }
    kbdData[channel].country = country;
    KBDResetChannel(channel);
    return 0;
}

USBKBDErr KBDSetLockProcessing(u32 channel, u32 value) {
    if (!kbdInitialized) {
        return 2;
    }

    if (channel >= 4) {
        return 4;
    }

    kbdData[channel].lockProcessing = value;
    return 0;
}

USBKBDErr KBDSetModState(u32 channel, u32 value) {
    if (!kbdInitialized) {
        return 2;
    }
    if (channel >= 4) {
        return 4;
    }
    if ((value & 0x1000) != 0) {
        kbdData[channel].modState = value & ~0x1000;
    } else {
        BOOL interrupts;
        KBDModifierState* state;
        KBDModifierState oldState;
        KBDModifierState newState;
        interrupts = OSDisableInterrupts();
        state = (KBDModifierState*)&kbdData[channel].modState;
        newState.value = value & 0xfc0;
        oldState = *state;
        newState.bits.physical = oldState.bits.physical;
        *state = newState;
        OSRestoreInterrupts(interrupts);
    }
    return 0;
}

u16 KBDTranslateHidCode(u32 keyCode, u32 modifiers, s32 country) {
    KBDKeyMap* map;
    u16* table;
    u32 keyIndex;
    u16 entry;
    s32 mask;
    s32 offset;
    s32 group;
    u32 shiftFlag;
    u16 activeFlag;

    if (kbdInitialized == FALSE) {
        return 0xFFFF;
    }
    if (country >= 0x24) {
        return 0xFFFF;
    }

    map = &kbdKeyMaps.maps[country];

    if (map->codeCount == 0) {
        return 0;
    }

    if (keyCode < 4) {
        return 0xFFFF;
    }


    if ((s32)keyCode < (s32)map->maxCode + 4) {
        keyIndex = (u8)(keyCode - 4);
        table = map->keyMap;
    } else {
        if (keyCode >= 0xE0 && keyCode <= 0xE7) {
            keyIndex = (u8)(keyCode - 0xe0);
            table = map->modifierMap;
        } else {
            return 0;
        }
    }

    keyIndex = (keyIndex & 0xFF) * map->codeCount;
    entry = table[keyIndex];
    mask = entry & 0xC000;

    if (mask == 0xC000) {
        group = 1;
        offset = 0;
    } else {
        if ((modifiers & 0x20) != 0 || (s32)(modifiers & 5) == 5) {
            group = map->altIndex;
            shiftFlag = 0x40;
        } else if ((modifiers & 0x40) != 0) {
            group = map->lockIndex;
            shiftFlag = 4;
        } else if ((modifiers & 0x80) != 0) {
            group = map->shiftIndex;
            shiftFlag = 0x10;
        } else {
            group = 1;
            shiftFlag = 1;
        }

        if ((modifiers & 0x800) == 0 && (modifiers & 0x1D) != 0) {
            offset = 0;
        } else {
            offset = (modifiers >> 1) & 1;
            shiftFlag <<= offset;
            activeFlag = shiftFlag;

            if (mask == 0 && (entry & activeFlag) != 0) {
                offset = offset ^ ((modifiers >> 9) & 1);
            } else if (mask == 0x8000 && (entry & activeFlag) != 0) {
                u32 numLockShift = 0;
                if ((s32)(modifiers & 0x100) == 0x100 && offset == 0) {
                    numLockShift = 1;
                }
                offset = numLockShift;
            } else {
                if (mask == 0x4000 && group == 1 && (modifiers & 0x200) != 0) {
                    group = map->lockIndex;
                }
            }
        }

        if (offset == 0) {
            if (group == map->altIndex && (map->flags & 0x10) == 0) {
                return 0;
            }
            if (group == map->lockIndex && (map->flags & 1) == 0) {
                return 0;
            }
            if (group == map->shiftIndex && (map->flags & 4) == 0) {
                return 0;
            }
        } else {
            if (group == map->altIndex && (map->flags & 0x20) == 0) {
                return 0;
            }
            if (group == map->lockIndex && (map->flags & 2) == 0) {
                return 0;
            }
            if (group == map->shiftIndex && (map->flags & 8) == 0) {
                return 0;
            }
        }

    }

    return table[keyIndex + (offset + group)];

}
