#include <revolution/fa.h>

extern s32 pfstub_set_stub_priority(s32 priority);
extern s32 usbh_msc_set_thread_priority(s32 priority);

FAError FASetThreadPriority(s32 priority) {
    s32 error = pfstub_set_stub_priority(priority);
    if (error != 0) {
        return error == -2 ? -2 : -1;
    }
    error = usbh_msc_set_thread_priority(priority);
    return (-error | error) >> 31;
}
