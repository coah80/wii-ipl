#define PF_FA_STR_LAYOUT
#include <private/vf/PrFILE2/pf_types.h>
#include <private/vf/PrFILE2/common/pf_str.h>

typedef struct PFAPI_GLOBAL_STATE {
    pf_u8 volume_state[0x40];
    pf_s32 last_error;
} PFAPI_GLOBAL_STATE;
extern PFAPI_GLOBAL_STATE pf_vol_set;

extern pf_s32 PFSTR_InitStr(PF_STR* p_str, const pf_s8* s, pf_u32 code_mode);
extern pf_s32 PFDIR_rename(PF_STR* old_path, PF_STR* new_path);
extern pf_s32 PFAPI_convertReturnValue(pf_s32 err);

pf_int32 pf2_rename(const pf_ch8* oldPath, const pf_ch8* newPath) {
    pf_s32 err;
    PF_STR old_str;
    PF_STR new_str;

    err = PFSTR_InitStr(&old_str, (pf_s8*)oldPath, 1U);
    err |= PFSTR_InitStr(&new_str, (pf_s8*)newPath, 1U);
    if (err == 0) {
        err = PFDIR_rename(&old_str, &new_str);
    } else {
        pf_vol_set.last_error = err;
    }
    err = PFAPI_convertReturnValue(err);
    return err;
}
