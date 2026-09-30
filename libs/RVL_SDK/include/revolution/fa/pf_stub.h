#ifndef FA_PF_STUB_H
#define FA_PF_STUB_H

#include <revolution/fa.h>

typedef union PF_STUB_RESULT {
    s32 status;
    u32 count;
    void* stream;
} PF_STUB_RESULT;

typedef struct PF_STUB_MESSAGE {
    s32 task_id;
    s32 operation;
    s8 drive;
    u32 value;
    u32 count;
    const void* object;
    const void* data;
    void* context;
    u32 options;
    s32 semaphore;
    PF_STUB_RESULT* result_address;
    FADisk* disk;
    FAPartition* partition;
    void (*callback)(s32, void*);
    void* callback_context;
    PF_STUB_RESULT result;
} PF_STUB_MESSAGE;

extern s32 pfstub_com_massage(PF_STUB_MESSAGE* message);

#endif
