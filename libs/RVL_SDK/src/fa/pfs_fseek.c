#include <revolution/fa/pf_stub.h>

s32 pfstub_fseek(FAFILE* stream, s32 offset, s32 origin) {
    PF_STUB_MESSAGE message;

    message.operation = 5;
    message.object = stream;
    message.value = offset;
    message.count = origin;
    message.callback = NULL;
    if (pfstub_com_massage(&message) == -1) {
        return -1;
    }
    return message.result.status;
}
