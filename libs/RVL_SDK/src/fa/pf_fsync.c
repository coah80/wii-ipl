#include <revolution/fa.h>

extern s32 PFFILE_fsync(FAFILE* stream);
extern s32 PFAPI_convertReturnValue(s32 error);

FAError pf2_fsync(FAFILE* stream) {
    s32 error = PFFILE_fsync(stream);
    error = PFAPI_convertReturnValue(error);
    return error;
}
