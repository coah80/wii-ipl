#define PF_FA_STR_LAYOUT
#define VFiPFAPI_convertReturnValue PFAPI_convertReturnValue
#define VFiPFFILE_finfo PFFILE_finfo
#include <private/vf/PrFILE2/standard/pf_finfo.h>

#include <private/vf/PrFILE2/fatfs/pf_volume.h>
#include <private/vf/PrFILE2/standard/pf_api_util.h>

pf_int32 pf2_finfo(PF_FILE* p_file, PF_INFO* p_info) {
    pf_s32 err = VFiPFFILE_finfo(p_file, p_info);
    err = VFiPFAPI_convertReturnValue(err);
    return err;
}
