#include <revolution/fa.h>

extern s32 PFVOL_setclstlink(s8 drive, s32 mode, void* setting);
extern s32 PFAPI_convertReturnValue(s32 error);

s32 pf2_setclstlink(s8 drive, s32 mode, void* setting) {
    return PFAPI_convertReturnValue(PFVOL_setclstlink(drive, mode, setting));
}
