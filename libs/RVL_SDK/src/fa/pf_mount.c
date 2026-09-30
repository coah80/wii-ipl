#include <private/vf/PrFILE2/pf_types.h>

extern pf_s32 PFVOL_mount(pf_s8 drv_char);
extern pf_s32 PFAPI_convertReturnValue(pf_s32 err);

pf_int32 pf2_mount(pf_ch8 drive) {
    pf_s32 err = PFVOL_mount(drive);
    err = PFAPI_convertReturnValue(err);
    return err;
}
