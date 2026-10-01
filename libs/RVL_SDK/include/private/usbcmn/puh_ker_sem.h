#ifndef PFILE_USB_HELPER_SEM_H
#define PFILE_USB_HELPER_SEM_H

#include <revolution/types.h>

s32 uhf_ker_create_sem(u32 initCount, int flags);
s32 uhf_ker_delete_sem(int sem);

s32 uhf_ker_get_sem(int sem);

#endif  // PFILE_USB_HELPER_SEM_H
