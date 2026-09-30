#include <revolution/fa/pf_stub.h>

s32 pfstub_format(s8 drive, u32 mode) {
    PF_STUB_MESSAGE message;

    message.operation = 15;
    message.drive = drive;
    message.object = (void*)mode;
    message.callback = NULL;
    if (pfstub_com_massage(&message) == -1) {
        return -1;
    }
    return message.result.status;
}
