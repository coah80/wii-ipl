#include <revolution/net.h>
#include <revolution/os.h>

int NCDiGetEnabledConfigList(u32* wireless, u32* wired, u32* other);
int GetStartupErrorCode(int error, int connection);

static int FirstConfig(u32 configs) {
    int index = 0;
    u32 mask = 1;
    for (; index < 32; ++index) {
        if (configs & mask) return index;
        mask <<= 1;
    }
    return -1;
}

int NETiGetConnectionTypeFromConfigList(u32 wireless, u32 wired, u32 other);
int NETiGetConnectionTypeFromConfigList(u32 wireless, u32 wired, u32 other) {
    int connection = 99;
    if (wireless != 0) {
        if (wired == 0 && other == 0) connection = FirstConfig(wireless) + 20;
    } else if (wired != 0) {
        if (other == 0) connection = FirstConfig(wired) + 30;
    } else if (other != 0) {
        connection = FirstConfig(other) + 40;
    }
    return connection;
}

#pragma dont_inline on // MWCC must preserve the startup-error helper call boundaries.
int NETGetStartupErrorCode(int error) {
    u32 other, wired, wireless;
    int connection = 99;
    if (NCDiGetEnabledConfigList(&wireless, &wired, &other) >= 0)
        connection = NETiGetConnectionTypeFromConfigList(wireless, wired, other);
    if (connection < 0) {
        error = (int)0x80000000;
        connection = 99;
    }
    return GetStartupErrorCode(error, connection) - connection;
}

#pragma dont_inline reset
int NETGetStartupErrorCodeEx(int error, int connection) {
    return GetStartupErrorCode(error, connection) - connection;
}

int GetStartupErrorCode(int error, int connection) {
    if (error >= 0) return 0;
    switch (error) {
    case -45: return -50200;
    case -28: return -50300;
    case -62: return -50400;
    case -111: return -52700;
    case -121:
        if (connection >= 20 && connection < 30) return -51400;
        return -51000;
    case -39:
    case -48:
    case -76:
    case -112:
        if (connection >= 20 && connection < 30) return -51400;
        return -51300;
    case -100:
    case -101:
    case -102: return -52000;
    case (int)0x80000000: return -50100;
    default:
        OSReport("Unknown SOStartup Error: %d\n", error);
        return -50100;
    }
}
