#include <revolution/fa.h>

extern s32 pfstub_unmount(s8 drive, u32 force);

FAError FAUnmount(s8 drive, u32 force) {
    s32 error = pfstub_unmount(drive, force);
    if (error == -1) {
        error = -1;
    } else if (error == 1) {
        error = 1;
    } else if (error == 0) {
        error = 0;
    } else {
        error = -1;
    }
    return error;
}
