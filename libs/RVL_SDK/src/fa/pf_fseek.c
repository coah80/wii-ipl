#define PF_FA_STR_LAYOUT
#define VFiPFAPI_convertReturnValue PFAPI_convertReturnValue
#define VFiPFFILE_fseek PFFILE_fseek
#include <private/vf/PrFILE2/standard/pf_fseek.h>

#include <private/vf/PrFILE2/fatfs/pf_volume.h>
#include <private/vf/PrFILE2/standard/pf_api_util.h>

pf_int32 pf2_fseek(PF_FILE* pFile, pf_s32 lOffset, pf_int32 nOrigin) {
    pf_s32 err = VFiPFFILE_fseek(pFile, lOffset, nOrigin);
    err = VFiPFAPI_convertReturnValue(err);
    return err;
}
