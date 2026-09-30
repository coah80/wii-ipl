#include <revolution/fa/pf_stub.h>

s32 pfstub_finfo(FAFILE* stream, FAFileInfo* info) {
    PF_STUB_MESSAGE message;

    message.operation = 45;
    message.object = stream;
    message.data = info;
    message.callback = NULL;
    if (pfstub_com_massage(&message) == -1) {
        return -1;
    }
    return message.result.status;
}
