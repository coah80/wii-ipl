#include <revolution/fa/pf_stub.h>

s32 pfstub_detach(s8 drive) {
    PF_STUB_MESSAGE message;

    message.operation = 41;
    message.drive = drive;
    message.callback = NULL;
    if (pfstub_com_massage(&message) == -1) {
        return -1;
    }
    return message.result.status;
}
