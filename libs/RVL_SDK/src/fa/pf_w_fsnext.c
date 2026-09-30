#include <revolution/fa.h>

extern s32 PFDIR_fsnext(FADta* data);
extern s32 PFAPI_convertReturnValue(s32 error);

s32 pf2_w_fsnext(FADta* data) {
    return PFAPI_convertReturnValue(PFDIR_fsnext(data));
}
