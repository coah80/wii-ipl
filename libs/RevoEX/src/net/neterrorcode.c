#include <revolution.h>
#include <revolution/net.h>

extern s32 NCDiGetEnabledConfigList(u32* list0, u32* list1, u32* list2);

s32 GetStartupErrorCode(s32 err, s32 type);

s32 NETiGetConnectionTypeFromConfigList(u32 config0, u32 config1, u32 config2) {
    s32 i;
    u32 mask;
    s32 ret = 0x63;

    if (config0 != 0) {
        if (config1 == 0 && config2 == 0) {
            for (i = 0, mask = 1; i < 32; i++, mask <<= 1) {
                if (config0 & mask) {
                    goto find0;
                }
            }
            i = -1;
        find0:
            ret = i + 0x14;
            goto end;
        }
    } else if (config1 != 0) {
        if (config2 == 0) {
            for (i = 0, mask = 1; i < 32; i++, mask <<= 1) {
                if (config1 & mask) {
                    goto find1;
                }
            }
            i = -1;
        find1:
            ret = i + 0x1e;
            goto end;
        }
    } else if (config2 != 0) {
        for (i = 0, mask = 1; i < 32; i++, mask <<= 1) {
            if (config2 & mask) {
                goto find2;
            }
        }
        i = -1;
    find2:
        ret = i + 0x28;
    }

end:
    return ret;
}

int NETGetStartupErrorCode(int err) {
    u32 config[3];
    s32 type = 0x63;

    if (NCDiGetEnabledConfigList(&config[0], &config[1], &config[2]) >= 0) {
        type = NETiGetConnectionTypeFromConfigList(config[0], config[1], config[2]);
    }

    if (type < 0) {
        err = (s32)0x80000000;
        type = 0x63;
    }

    return GetStartupErrorCode(err, type) - type;
}

int NETGetStartupErrorCodeEx(int err, int type) {
    return GetStartupErrorCode(err, type) - type;
}

s32 GetStartupErrorCode(s32 err, s32 type) {
    if (err >= 0) {
        return 0;
    }

    switch (err) {
    case -0x2D:
        return 0xFFFF3BE8;
    case -0x1C:
        return 0xFFFF3B84;
    case -0x3E:
        return 0xFFFF3B20;
    case -0x6F:
        return 0xFFFF3224;
    case -0x79:
        if (type >= 0x14 && type < 0x1E) {
            return 0xFFFF3738;
        }
        return 0xFFFF38C8;
    case -0x70:
    case -0x4C:
    case -0x30:
    case -0x27:
        if (type >= 0x14 && type < 0x1E) {
            return 0xFFFF3738;
        }
        return 0xFFFF379C;
    case -0x66:
    case -0x65:
    case -0x64:
        return 0xFFFF34E0;
    case (s32)0x80000000:
        return 0xFFFF3C4C;
    default:
        OSReport("Unknown SOStartup Error: %d\n", err);
        return 0xFFFF3C4C;
    }
}
