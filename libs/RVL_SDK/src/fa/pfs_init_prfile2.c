#include <revolution/fa.h>

extern s32 pf2_init_prfile2(s32 config, void* parameter);

s32 pfstub_init_prfile2(s32 config, void* parameter) {
    return pf2_init_prfile2(config, parameter);
}
