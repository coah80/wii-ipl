#define PF_FA_STR_LAYOUT
#define VFiPFAPI_convertReturnValue PFAPI_convertReturnValue
#define VFiPFFATFS_initializeFATFS PFFATFS_initializeFATFS
#define VFiPFSYS_initializeSYS PFSYS_initializeSYS
#include <private/vf/PrFILE2/standard/pf_init_prfile2.h>

#include <private/vf/PrFILE2/fatfs/pf_fatfs.h>
#include <private/vf/PrFILE2/standard/pf_api_util.h>
#include <private/vf/PrFILE2/system/pf_system.h>


pf_int32 pf2_init_prfile2(pf_s32 config, void* param) {
    pf_s32 err = VFiPFFATFS_initializeFATFS(config, param);
    if (err == 0) {
        VFiPFSYS_initializeSYS();
    }
    err = VFiPFAPI_convertReturnValue(err);
    return err;
}
