#include <revolution/types.h>

extern s32 PFVOL_InitModule(u32 config, void* param);

s32 PFFATFS_initializeFATFS(u32 config, void* param) {
    return PFVOL_InitModule(config, param);
}
