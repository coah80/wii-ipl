#include <revolution/fa/pf_stub.h>

FAFILE* pfstub_fopen(const char* path, const char* mode) {
    PF_STUB_MESSAGE message;

    message.operation = 1;
    message.object = path;
    message.data = mode;
    message.callback = NULL;
    if (pfstub_com_massage(&message) == -1) {
        return NULL;
    }
    return message.result.stream;
}
