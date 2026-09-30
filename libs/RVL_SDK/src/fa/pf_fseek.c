#include <revolution/fa.h>

extern s32 PFFILE_fseek(FAFILE* stream, s32 offset, int origin);
extern s32 PFAPI_convertReturnValue(s32 err);

FAError pf2_fseek(FAFILE* stream, s32 offset, int origin) {
    s32 err = PFFILE_fseek(stream, offset, origin);
    err = PFAPI_convertReturnValue(err);
    return err;
}
