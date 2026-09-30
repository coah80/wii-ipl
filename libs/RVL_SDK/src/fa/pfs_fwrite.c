#include <revolution/fa/pf_stub.h>

u32 pfstub_fwrite(void* buffer, u32 size, u32 count, FAFILE* stream) {
    PF_STUB_MESSAGE message;

    message.operation = 4;
    message.object = buffer;
    message.value = size;
    message.count = count;
    message.data = stream;
    message.callback = NULL;
    if (pfstub_com_massage(&message) == -1) {
        return 0;
    }
    return message.result.count;
}
