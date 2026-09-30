#include <revolution/fa.h>

extern s32 pfstub_errnum(void);

FAError FAErrnum(void) {
    s32 error = pfstub_errnum();
    if (error == 5) {
        return 5;
    }
    return error == 0 ? 0 : error;
}
