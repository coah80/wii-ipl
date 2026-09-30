#include <revolution/fa.h>

extern s32 PFVOL_setvolcfg(s8 drive, u32* config);
extern s32 PFAPI_convertReturnValue(s32 error);

s32 pf2_setvolcfg(s8 drive, u32* config) {
    return PFAPI_convertReturnValue(PFVOL_setvolcfg(drive, config));
}
