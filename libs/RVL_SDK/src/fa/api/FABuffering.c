#include <revolution/fa.h>

extern s32 pfstub_buffering(s8 drive, s32 mode);

FAError FABuffering(s8 drive, s32 mode) {
    s32 error = pfstub_buffering(drive, mode);
    return (-error | error) >> 31;
}
