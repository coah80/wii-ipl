#include <revolution/fa.h>

extern s32 PFFILE_fadjust(FAFILE* file);
extern s32 PFAPI_convertReturnValue(s32 error);

s32 pf2_fadjust(FAFILE* file) {
    return PFAPI_convertReturnValue(PFFILE_fadjust(file));
}
