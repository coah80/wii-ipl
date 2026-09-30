#define PF_FA_STR_LAYOUT
#define VFiPFAPI_convertReturnValue PFAPI_convertReturnValue
#define VFiPFDIR_fsfirst PFDIR_fsfirst
#define VFiPFSTR_InitStr PFSTR_InitStr
#include <private/vf/PrFILE2/standard/pf_fsfirst.h>

typedef struct PFAPI_GLOBAL_STATE {
    pf_u8 volume_state[0x40];
    pf_s32 last_error;
} PFAPI_GLOBAL_STATE;
extern PFAPI_GLOBAL_STATE pf_vol_set;


#include <private/vf/PrFILE2/fatfs/pf_volume.h>
#include <private/vf/PrFILE2/standard/pf_api_util.h>

pf_int32 pf2_fsfirst(const pf_ch8* path, pf_u8 attrs, PF_DTA* p_dta) {
    pf_s32 err;
    PF_STR path_str;

    err = VFiPFSTR_InitStr(&path_str, (pf_s8*)path, 1U);
    if (err == 0) {
        err = VFiPFDIR_fsfirst(&path_str, attrs, p_dta);
    } else {
        pf_vol_set.last_error = err;
    }
    err = VFiPFAPI_convertReturnValue(err);

    return err;
}
