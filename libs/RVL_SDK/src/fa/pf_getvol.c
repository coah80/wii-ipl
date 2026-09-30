#include <revolution/fa.h>

extern s32 PFVOL_getvol(s8 drive, void* volume_info);
extern s32 PFAPI_convertReturnValue(s32 error);

s32 pf2_getvol(s8 drive, void* volume_info) {
    return PFAPI_convertReturnValue(PFVOL_getvol(drive, volume_info));
}
