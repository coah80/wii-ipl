#include <revolution/fa.h>

extern s32 PFVOL_unregctx(void);
extern s32 PFAPI_convertReturnValue(s32 error);

s32 pf2_unregctx(void) {
    return PFAPI_convertReturnValue(PFVOL_unregctx());
}
