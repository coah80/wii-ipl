#include <revolution/fa.h>

extern s32 PFFILE_fsetclstlink(FAFILE* file, u32 mode, void* setting);
extern s32 PFAPI_convertReturnValue(s32 error);

s32 pf2_fsetclstlink(FAFILE* file, u32 mode, void* setting) {
    return PFAPI_convertReturnValue(PFFILE_fsetclstlink(file, mode, setting));
}
