#include <revolution/fa.h>

extern s32 PFFILE_flock(FAFILE* stream, s32 mode);
extern s32 PFAPI_convertReturnValue(s32 error);

FAError pf2_flock(FAFILE* stream, s32 mode) {
    s32 error;
    mode |= 8;
    error = PFFILE_flock(stream, mode);
    error = PFAPI_convertReturnValue(error);
    return error;
}
