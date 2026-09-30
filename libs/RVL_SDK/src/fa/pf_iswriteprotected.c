#include <revolution/fa.h>

extern s32 PFVOL_iswriteprotected(s8 drive, u32* protected_status);
extern s32 PFAPI_convertReturnValue(s32 error);

s32 pf2_iswriteprotected(s8 drive) {
    u32 protected_status = 0;
    s32 error = PFVOL_iswriteprotected(drive, &protected_status);
    if (error == 0) {
        return protected_status;
    }
    return PFAPI_convertReturnValue(error);
}
