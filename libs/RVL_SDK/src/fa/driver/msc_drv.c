#include <revolution/fa.h>

static FAEjectCallback g_detach_func;
static FAInsertCallback g_attach_func;

extern s32 uhf_msc_is_media_insert(void);

s32 pfd_mscdrv_registar_callback(FAInsertCallback insert, FAEjectCallback eject) {
    g_attach_func = insert;
    g_detach_func = eject;
    return 0;
}

s32 pfd_mscdrv_is_media_insert(void) {
    return uhf_msc_is_media_insert();
}
