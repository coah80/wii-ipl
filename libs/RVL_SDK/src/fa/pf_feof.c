#include <revolution/fa.h>

extern s32 PFFILE_feof(FAFILE* stream);
extern s32 PFAPI_convertReturnValue4feof(s32 error);

FAError pf2_feof(FAFILE* stream) {
    s32 error = PFFILE_feof(stream);
    error = PFAPI_convertReturnValue4feof(error);
    return error;
}
