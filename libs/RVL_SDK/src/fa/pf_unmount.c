#define PF_FA_STR_LAYOUT
#define VFiPFAPI_convertReturnValue4unmount PFAPI_convertReturnValue4unmount
#define VFiPFVOL_unmount PFVOL_unmount
#include <private/vf/PrFILE2/standard/pf_unmount.h>

#include <private/vf/PrFILE2/fatfs/pf_volume.h>
#include <private/vf/PrFILE2/standard/pf_api_util.h>

pf_int32 pf2_unmount(pf_ch8 drive, pf_u32 mode) {
    pf_s32 err = VFiPFVOL_unmount(drive, mode);
    err = VFiPFAPI_convertReturnValue4unmount(err);
    return err;
}
