#include <revolution/fa.h>

extern s32 PFDIR_seekdir(FADIR* dir, u32 position);
extern s32 PFAPI_convertReturnValue(s32 err);

FAError pf2_seekdir(FADIR* dir, u32 position) {
    s32 err = PFDIR_seekdir(dir, position);
    err = PFAPI_convertReturnValue(err);
    return err;
}
