#include <revolution/fa/pf_stub.h>

s32 pfstub_unmount(s8 drive, u32 force) {
    PF_STUB_MESSAGE message;

    message.operation = 39;
    message.drive = drive;
    message.value = force;
    message.callback = NULL;
    if (pfstub_com_massage(&message) == -1) {
        return -1;
    }
    return message.result.status;
}
