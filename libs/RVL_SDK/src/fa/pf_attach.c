#include <private/vf/PrFILE2/pf_types.h>
#include <private/vf/PrFILE2/driver/pf_driver.h>

typedef struct PFATTACH_NOTIFY {
    pf_u8 driver_state[0x50];
    void* callback_data;
} PFATTACH_NOTIFY;
typedef struct PFATTACH_GLOBAL {
    pf_u8 volume_state[0x40];
    pf_s32 last_error;
} PFATTACH_GLOBAL;
extern PFATTACH_GLOBAL pf_vol_set;
extern pf_s32 PFVOL_attach(PF_DRV_TBL*, PFATTACH_NOTIFY*, void*);
extern pf_s32 PFAPI_convertReturnValue(pf_s32);

pf_int32 pf2_attach(PF_DRV_TBL** drv_tbl, PFATTACH_NOTIFY* notify) {
    pf_s32 err;
    if (drv_tbl == PF_NULL || !*drv_tbl) {
        err = 10;
        pf_vol_set.last_error = 10;
    } else {
        for (; *drv_tbl != PF_NULL; drv_tbl++) {
            if (notify != PF_NULL) err = PFVOL_attach(*drv_tbl, notify, notify->callback_data);
            else err = PFVOL_attach(*drv_tbl, PF_NULL, PF_NULL);
            if (err != 0) return PFAPI_convertReturnValue(err);
        }
    }
    return PFAPI_convertReturnValue(err);
}
