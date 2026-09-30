#include <revolution/fa.h>

extern s32 pfstub_devinf(s8 drive, FADevInf* data);

FAError FAGetdev(s8 drive, FADevInf* data) {
    s32 error = pfstub_devinf(drive, data);
    return (-error | error) >> 31;
}
