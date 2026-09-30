#include <revolution/fa.h>

extern s32 pfstub_format(s8 drive, u32 mode);

FAError FAFormat(s8 drive, u32 mode) {
    s32 error = pfstub_format(drive, mode);
    return (-error | error) >> 31;
}
