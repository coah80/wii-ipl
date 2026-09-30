#include <revolution/fa.h>

typedef struct FADirEnt FADirEnt;

extern s32 PFDIR_readdir(FADIR* dir, FADirEnt* result);
extern s32 PFAPI_convertReturnValue(s32 err);

FAError pf2_readdir(FADIR* dir, FADirEnt* result) {
    s32 err = PFDIR_readdir(dir, result);
    err = PFAPI_convertReturnValue(err);
    return err;
}
