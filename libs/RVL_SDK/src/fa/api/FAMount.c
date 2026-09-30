#include <revolution/fa.h>

extern s32 pfstub_mount(s8 drive);

FAError FAMount(s8 drive) {
    s32 error = pfstub_mount(drive);
    return (-error | error) >> 31;
}
