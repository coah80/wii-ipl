#ifndef FA_PF_KERNEL_H
#define FA_PF_KERNEL_H

#include <revolution/os.h>

typedef struct PFK_TASK_CONFIG {
    void* (*entry)(void*);
    void* argument;
    u32 stack_size;
    void* stack;
    s32 priority;
    OSThread* thread;
} PFK_TASK_CONFIG;

typedef struct PFK_MAILBOX_CONFIG {
    OSMessageQueue* queue;
    OSMessage* messages;
    s32 count;
} PFK_MAILBOX_CONFIG;

typedef struct PFK_SEMAPHORE_CONFIG {
    u32 initial_count;
    u32 maximum_count;
    OSSemaphore* semaphore;
} PFK_SEMAPHORE_CONFIG;

s32 pfk_create_task(PFK_TASK_CONFIG* config);
s32 pfk_start_task(s32 task_id);
s32 pfk_get_task_id(s32* task_id);
s32 pfk_set_task_priority(s32 task_id, s32 priority);
s32 pfk_create_mailbox(PFK_MAILBOX_CONFIG* config);
s32 pfk_receive_message(s32 mailbox, OSMessage* message);
s32 pfk_send_message(s32 mailbox, OSMessage message);
s32 pfk_create_semaphore(PFK_SEMAPHORE_CONFIG* config);
s32 pfk_delete_semaphore(s32 semaphore);
s32 pfk_get_semaphore(s32 semaphore);
s32 pfk_release_semaphore(s32 semaphore);

#endif
