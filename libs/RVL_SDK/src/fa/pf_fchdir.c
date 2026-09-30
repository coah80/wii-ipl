#include <revolution/fa.h>

extern s32 PFDIR_fchdir(FADIR* directory);
extern s32 PFAPI_convertReturnValue(s32 error);

s32 pf2_fchdir(FADIR* directory) {
    return PFAPI_convertReturnValue(PFDIR_fchdir(directory));
}
