#include <revolution/fa/pf_stub.h>

s32 pfstub_errnum(void) {
    PF_STUB_MESSAGE message;

    message.operation = 19;
    message.callback = NULL;
    if (pfstub_com_massage(&message) == -1) {
        return -1;
    }
    return message.result.status;
}
