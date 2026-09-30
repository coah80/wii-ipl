#define PF_FA_STR_LAYOUT
#define VFiPFAPI_convertReturnValue PFAPI_convertReturnValue
#define VFiPFDIR_rmdir PFDIR_rmdir
#define VFiPFSTR_InitStr PFSTR_InitStr
#include <private/vf/PrFILE2/standard/pf_rmdir.h>

typedef struct PFAPI_GLOBAL_STATE {
    pf_u8 volume_state[0x40];
    pf_s32 last_error;
} PFAPI_GLOBAL_STATE;
extern PFAPI_GLOBAL_STATE pf_vol_set;


#include <private/vf/PrFILE2/fatfs/pf_dir.h>
#include <private/vf/PrFILE2/standard/pf_api_util.h>

#include <private/vf/PrFILE2/common/pf_str.h>

pf_int32 pf2_rmdir(const pf_ch8* sPath) {
    pf_s32 err;
    PF_STR path_str;

    err = VFiPFSTR_InitStr(&path_str, (pf_s8*)sPath, 1U);
    if (err == 0) {
        err = VFiPFDIR_rmdir(&path_str);
    } else {
        pf_vol_set.last_error = err;
    }
    err = VFiPFAPI_convertReturnValue(err);
    return err;
}
