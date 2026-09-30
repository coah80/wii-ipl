#include <revolution/fa/pf_stub.h>

s32 pfstub_buffering(s8 drive, u32 mode) {
    PF_STUB_MESSAGE message;

    message.operation = 16;
    message.drive = drive;
    message.value = mode;
    message.callback = NULL;
    if (pfstub_com_massage(&message) == -1) {
        return -1;
    }
    return message.result.status;
}
