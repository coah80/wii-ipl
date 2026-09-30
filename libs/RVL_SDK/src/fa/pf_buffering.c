#include <revolution/fa.h>

extern s32 PFVOL_buffering(s8 drive, u8 mode);
extern s32 PFAPI_convertReturnValue(s32 error);

s32 pf2_buffering(s32 drive, u32 mode) {
    return PFAPI_convertReturnValue(PFVOL_buffering(drive, mode));
}
