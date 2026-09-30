#ifndef PF_FA_SYSTEM_LAYOUT_H
#define PF_FA_SYSTEM_LAYOUT_H
#include <revolution/os.h>

typedef struct PFSYS_SYSTEM_SET {
    u32 initialized;
    s32 task_id;
    s32 mailbox_id;
    u8 task_stack[0x2000];
    OSThread task;
    OSMessageQueue mailbox;
    OSMessage messages[20];
    u32 flock_count;
} PFSYS_SYSTEM_SET;

extern PFSYS_SYSTEM_SET pf_sys_set;
#endif
