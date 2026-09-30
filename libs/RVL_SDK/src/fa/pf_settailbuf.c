#include <revolution/fa.h>

extern s32 PFVOL_settailbuf(s8 drive, u32 count, void* buffer);
extern s32 PFAPI_convertReturnValue(s32 error);

s32 pf2_settailbuf(s8 drive, u32 count, void* buffer) {
    return PFAPI_convertReturnValue(PFVOL_settailbuf(drive, count, buffer));
}
