#include <revolution/fa/pf_stub.h>

s32 pfstub_fstat(const char* path, FAFileStat* stat) {
    PF_STUB_MESSAGE message;

    message.operation = 12;
    message.object = path;
    message.data = stat;
    message.callback = NULL;
    if (pfstub_com_massage(&message) == -1) {
        return -1;
    }
    return message.result.status;
}
