#include <revolution/fa.h>

extern s32 PFVOL_setencode(u32 mode);
extern s32 PFAPI_convertReturnValue(s32 error);

s32 pf2_setencode(u32 mode) {
    return PFAPI_convertReturnValue(PFVOL_setencode(mode));
}
