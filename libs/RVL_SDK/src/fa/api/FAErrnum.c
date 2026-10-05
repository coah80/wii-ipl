#include <revolution/fa.h>

extern s32 pfstub_errnum(void);

FAError FAErrnum(void) {
    s32 error = pfstub_errnum();
    if (error == FA_ERR_EIO) {
        return FA_ERR_EIO;
    }
    return error == FA_ERR_SUCCESS ? FA_ERR_SUCCESS : error;
}
