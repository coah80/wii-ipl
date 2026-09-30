#include <revolution/fa.h>

extern s32 PFVOL_setupfsi(s8 drive, u16 mode);
extern s32 PFAPI_convertReturnValue(s32 error);

s32 pf2_setupfsi(s32 drive, u32 mode) {
    return PFAPI_convertReturnValue(PFVOL_setupfsi(drive, mode));
}
