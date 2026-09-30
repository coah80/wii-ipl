#include <revolution/fa/pf_stub.h>

s32 pfstub_fsfirst(const char* path, u32 attributes, FADta* data) {
    PF_STUB_MESSAGE message;

    message.operation = 28;
    message.object = path;
    message.value = attributes;
    message.data = data;
    message.callback = NULL;
    if (pfstub_com_massage(&message) == -1) {
        return -1;
    }
    return message.result.status;
}
