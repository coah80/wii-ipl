#include <revolution/fa/pf_stub.h>

s32 pfstub_fclose(FAFILE* stream) {
    PF_STUB_MESSAGE message;

    message.operation = 2;
    message.object = stream;
    message.callback = NULL;
    if (pfstub_com_massage(&message) == -1) {
        return -1;
    }
    return message.result.status;
}
