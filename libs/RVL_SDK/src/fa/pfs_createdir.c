#include <revolution/fa/pf_stub.h>

s32 pfstub_createdir(const char* path, s32 mode, FADta* data) {
    PF_STUB_MESSAGE message;

    message.operation = 65;
    message.object = path;
    message.value = mode;
    message.data = data;
    message.callback = NULL;
    if (pfstub_com_massage(&message) == -1) {
        return -1;
    }
    return message.result.status;
}
