#include <revolution/types.h>

typedef struct UHF_MSC_SENSE {
    u8 key;
    u8 code;
    u8 qualifier;
} UHF_MSC_SENSE;

s32 __uhf_msc_cmd_check_sense(const UHF_MSC_SENSE* sense) {
    s32 code = (sense->key << 16) | (sense->code << 8) | sense->qualifier;
    switch (code) {
        case 0x0:
            return 0;
        case 0x11701:
            return 1;
        case 0x11800:
            return 2;
        case 0x20401:
            return 3;
        case 0x20402:
            return 4;
        case 0x20404:
            return 5;
        case 0x204ff:
            return 6;
        case 0x20600:
            return 7;
        case 0x20800:
            return 8;
        case 0x20801:
            return 9;
        case 0x20880:
            return 10;
        case 0x23a00:
            return 11;
        case 0x25400:
            return 12;
        case 0x28000:
            return 13;
        case 0x2ffff:
            return 14;
        case 0x30200:
            return 15;
        case 0x30300:
            return 16;
        case 0x31000:
            return 17;
        case 0x31100:
            return 18;
        case 0x31200:
            return 19;
        case 0x31300:
            return 20;
        case 0x31400:
            return 21;
        case 0x33001:
            return 22;
        case 0x33101:
            return 23;
        case 0x51a00:
            return 25;
        case 0x52000:
            return 26;
        case 0x52100:
            return 27;
        case 0x52400:
            return 28;
        case 0x52500:
            return 29;
        case 0x52600:
            return 30;
        case 0x52601:
            return 31;
        case 0x52602:
            return 32;
        case 0x53900:
            return 33;
        case 0x62800:
            return 34;
        case 0x62900:
            return 35;
        case 0x62f00:
            return 36;
        case 0x72700:
            return 37;
        case 0xb4e00:
            return 38;
        default:
            if ((u32)((sense->key << 8) | sense->code) == 0x0440) {
                return 24;
            }
            return 39;
    }
}
