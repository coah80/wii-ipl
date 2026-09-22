#include <revolution/fa.h>

extern s32 PFVOL_errnum(void);
extern s32 PFAPI_convertError(s32 error);

FAError pf2_errnum() {
    s32 error = PFVOL_errnum();
    error = PFAPI_convertError(error);
    return error;
}
