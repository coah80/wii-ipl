#include <revolution/fa.h>

extern s32 PFDIR_readdir(FADIR* directory, void* result);
extern s32 PFAPI_convertReturnValue(s32 error);

s32 pf2_readdir(FADIR* directory, void* result) {
    return PFAPI_convertReturnValue(PFDIR_readdir(directory, result));
}
