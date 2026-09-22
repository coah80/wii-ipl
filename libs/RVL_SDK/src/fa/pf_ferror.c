#include <revolution/fa.h>

extern s32 PFFILE_ferror(FAFILE* stream);
extern s32 PFAPI_convertError(s32 error);

FAError pf2_ferror(FAFILE* stream) {
    s32 error = PFFILE_ferror(stream);
    error = PFAPI_convertError(error);
    return error;
}
