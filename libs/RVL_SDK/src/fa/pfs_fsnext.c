#include <revolution/fa/pf_stub.h>

s32 pfstub_fsnext(FADta* data) {
    PF_STUB_MESSAGE message;

    message.operation = 29;
    message.object = data;
    message.callback = NULL;
    if (pfstub_com_massage(&message) == -1) {
        return -1;
    }
    return message.result.status;
}
