#include <revolution/types.h>

s32 PFWAPI_ParseOpenModeString(const unsigned short* mode_str) {
    s32 open_mode = 0;
    u32 i = 0;

    if (mode_str == NULL) {
        open_mode = 10;
        return open_mode;
    }

    switch (mode_str[i++]) {
        case 'r': {
            open_mode = 2;
            break;
        }
        case 'w': {
            open_mode = 1;
            break;
        }
        case 'a': {
            open_mode = 4;
            break;
        }
        default: {
            return 0;
        }
    }

    if (mode_str[i] == 'b') {
        i++;
    }
    switch (mode_str[i++]) {
        case 0: {
            return open_mode;
        }
        case 't':
        default: {
            return 0;
        }
        case '+': {
            switch (mode_str[i]) {
                case 0: {
                    return open_mode | 8;
                }
                default: {
                    return 0;
                }
            }
        }
    }
    return 0;
}
