#include <revolution/fa.h>

extern s32 PFDIR_fsexec(FADta* data, u32 flags, u32 mode);
extern s32 PFAPI_convertReturnValue(s32 error);

s32 pf2_w_fsexec(FADta* data, u32 flags, u32 mode) {
    return PFAPI_convertReturnValue(PFDIR_fsexec(data, flags, mode));
}
