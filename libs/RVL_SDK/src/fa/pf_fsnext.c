#include <revolution/fa.h>

extern s32 PFDIR_fsnext(FADta* data);
extern s32 PFAPI_convertReturnValue(s32 err);

FAError pf2_fsnext(FADta* dta) {
    s32 err = PFDIR_fsnext(dta);
    err = PFAPI_convertReturnValue(err);
    return err;
}
