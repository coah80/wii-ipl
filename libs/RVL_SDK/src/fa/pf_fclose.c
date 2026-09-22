#include <revolution/fa.h>

extern s32 PFFILE_fclose(FAFILE* stream);
extern s32 PFAPI_convertReturnValue(s32 error);

FAError pf2_fclose(FAFILE* stream) {
    s32 error = PFFILE_fclose(stream);
    error = PFAPI_convertReturnValue(error);
    return error;
}
