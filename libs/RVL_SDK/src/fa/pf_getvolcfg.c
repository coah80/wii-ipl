#include <revolution/fa.h>

extern s32 PFVOL_getvolcfg(s8 drive, u32* config);
extern s32 PFAPI_convertReturnValue(s32 error);

s32 pf2_getvolcfg(s8 drive, u32* config) {
    return PFAPI_convertReturnValue(PFVOL_getvolcfg(drive, config));
}
