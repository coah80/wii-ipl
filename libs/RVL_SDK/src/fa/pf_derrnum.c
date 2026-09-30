#include <revolution/fa.h>

extern s32 PFVOL_derrnum(s8 drive);
extern s32 PFAPI_convertDriverError(s32 error);

s32 pf2_derrnum(s8 drive) {
    return PFAPI_convertDriverError(PFVOL_derrnum(drive));
}
