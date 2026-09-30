#include <revolution/fa/pf_stub.h>

FAFILE* pfstub_create(const char* path, int mode) {
    PF_STUB_MESSAGE message;

    message.operation = 0;
    message.object = path;
    message.value = mode;
    message.callback = NULL;
    if (pfstub_com_massage(&message) == -1) {
        return NULL;
    }
    return message.result.stream;
}
