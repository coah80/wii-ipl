#include <private/usbcmn/puh_ker_tsk.h>

#include <revolution/os.h>

#define MAX_PUH_TSK 2

static struct {
    struct {
        OSThread* thread;  // 0x00
        u8 stack[0x33C];  // 0x04
    } entries[MAX_PUH_TSK];  // 0x00
    u32 pad_0x680;
    u32 pad_0x684;
    u32 pad_0x688;
    u32 pad_0x68C;
} st_uhs_ker_tsk_mng;

s32 uhf_ker_set_priority(int tsk, int priority) {
    if (tsk == 0 || tsk > MAX_PUH_TSK) {
        return -5;
    }

    if (priority < 0 || priority > 31) {
        return -5;
    }

    if (st_uhs_ker_tsk_mng.entries[tsk - 1].thread == NULL) {
        return -1;
    }

    return OSSetThreadPriority(st_uhs_ker_tsk_mng.entries[tsk - 1].thread, priority) ? 0 : -20;
}
