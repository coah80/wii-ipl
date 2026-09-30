#include <revolution/fa.h>

extern s32 PFDIR_seekdir(FADIR* directory, u32 position);
extern s32 PFAPI_convertReturnValue(s32 error);

s32 pf2_seekdir(FADIR* directory, u32 position) {
    return PFAPI_convertReturnValue(PFDIR_seekdir(directory, position));
}
