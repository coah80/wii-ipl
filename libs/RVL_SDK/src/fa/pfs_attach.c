#include <revolution/fa/pf_stub.h>

s32 pfstub_attach(FADrvTbl* drives, u32 mode) {
    PF_STUB_MESSAGE message;

    message.operation = 27;
    message.object = drives;
    message.callback = NULL;
    message.data = (void*)mode;
    if (pfstub_com_massage(&message) == -1) {
        return -1;
    }
    return message.result.status;
}
