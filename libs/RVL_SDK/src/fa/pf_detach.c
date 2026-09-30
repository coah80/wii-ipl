#define PF_FA_STR_LAYOUT
#define VFiPFAPI_convertReturnValue PFAPI_convertReturnValue
#define VFiPFVOL_detach PFVOL_detach
#include <private/vf/PrFILE2/standard/pf_detach.h>

#include <private/vf/PrFILE2/fatfs/pf_volume.h>
#include <private/vf/PrFILE2/standard/pf_api_util.h>

pf_int32 pf2_detach(pf_ch8 drive) {
    pf_s32 err = VFiPFVOL_detach(drive);
    err = VFiPFAPI_convertReturnValue(err);
    return err;
}
