#include <revolution/fa/pf_stub.h>

s32 pfstub_devinf(s8 drive, FADevInf* info) {
    PF_STUB_MESSAGE message;

    message.operation = 20;
    message.drive = drive;
    message.object = info;
    message.callback = NULL;
    if (pfstub_com_massage(&message) == -1) {
        return -1;
    }
    return message.result.status;
}
