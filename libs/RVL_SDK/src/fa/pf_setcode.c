#include <revolution/fa.h>

extern s32 PFVOL_setcode(const void* code_set);
extern s32 PFAPI_convertReturnValue(s32 error);

s32 pf2_setcode(const void* code_set) {
    return PFAPI_convertReturnValue(PFVOL_setcode(code_set));
}
