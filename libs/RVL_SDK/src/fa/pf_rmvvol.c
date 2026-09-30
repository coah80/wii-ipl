#include <revolution/fa.h>

extern s32 PFVOL_rmvvol(s8 drive);
extern s32 PFAPI_convertReturnValue(s32 error);

s32 pf2_rmvvol(s8 drive) {
    return PFAPI_convertReturnValue(PFVOL_rmvvol(drive));
}
