#include <revolution/fa/pf_stub.h>
#include <private/fa/pf_system.h>
#include <private/fa/pf_kernel.h>

typedef struct PF_STUB_VOLUME_CONTEXT {
    u8 volume_state[0x64];
    s32 context_id;
} PF_STUB_VOLUME_CONTEXT;

extern PF_STUB_VOLUME_CONTEXT pf_vol_set;
extern FADisk* gOpenDisk[26];
extern FAPartition* gOpenPartition[26];
extern s32 pfd_sddrv_is_media_insert(void);
extern s32 pfd_mscdrv_is_media_insert(FADisk* disk);
extern void pfstub_call_function_standard(PF_STUB_MESSAGE* message);
extern void pfstub_call_function_unicode(PF_STUB_MESSAGE* message);
void* pfstub_entry(void* argument);
s32 pfstub_store_result(PF_STUB_MESSAGE* message);

void pfstub_init_stub(void) {
    PFK_MAILBOX_CONFIG mailbox;
    PFK_TASK_CONFIG task;
    if (pf_sys_set.initialized == 0) {
        mailbox.queue = &pf_sys_set.mailbox;
        mailbox.messages = pf_sys_set.messages;
        mailbox.count = 20;
        pf_sys_set.mailbox_id = pfk_create_mailbox(&mailbox);
        task.entry = pfstub_entry;
        task.argument = NULL;
        task.priority = 16;
        task.stack_size = sizeof(pf_sys_set.task_stack);
        task.stack = pf_sys_set.task_stack;
        task.thread = &pf_sys_set.task;
        pf_sys_set.task_id = pfk_create_task(&task);
        pfk_start_task(pf_sys_set.task_id);
        pf_sys_set.initialized = 1;
    }
}

s32 pfstub_set_stub_priority(s32 priority) {
    if (pf_sys_set.initialized != 1) {
        return -1;
    }
    return pfk_set_task_priority(pf_sys_set.task_id, priority);
}

void* pfstub_entry(void* argument) {
    PF_STUB_MESSAGE* received = NULL;
    PF_STUB_MESSAGE* message;
    for (;;) {
        if (pfk_receive_message(pf_sys_set.mailbox_id, (OSMessage*)&received) != 0) {
            continue;
        }
        message = received;
        if (message == NULL) {
            continue;
        }
        pf_vol_set.context_id = message->task_id;
        if (message->operation >= 0 && message->operation < 100) {
            pfstub_call_function_standard(message);
        } else if (received->operation >= 100 && received->operation < 200) {
            pfstub_call_function_unicode(message);
        } else {
            message->result.status = -1;
        }
        if (message->callback == NULL) {
            pfk_release_semaphore(message->semaphore);
        } else {
            if (message->operation == 27) {
                FADrvTbl* table = message->context;
                s32 index = table->drive - 'A';
                gOpenDisk[index] = message->disk;
                gOpenPartition[index] = message->partition;
                if (message->value == 0) {
                    if (pfd_sddrv_is_media_insert()) {
                        ((FADrvTbl*)message->context)->stat |= 0x10;
                    }
                } else if ((s32)message->value == 1) {
                    if (pfd_mscdrv_is_media_insert(message->disk)) {
                        ((FADrvTbl*)message->context)->stat |= 0x10;
                    }
                }
            }
            message->callback(pfstub_store_result(message), message->callback_context);
        }
    }
}

s32 pfstub_com_massage(PF_STUB_MESSAGE* message) {
    s32 task_id;
    PFK_SEMAPHORE_CONFIG config;
    OSSemaphore semaphore;
    s32 error;
    if (message->callback == NULL) {
        config.initial_count = 0;
        config.maximum_count = 1;
        config.semaphore = &semaphore;
        message->semaphore = pfk_create_semaphore(&config);
    } else {
        message->semaphore = 0;
    }
    if (pfk_get_task_id(&task_id) != 0) {
        return -1;
    }
    message->task_id = task_id;
    if (pfk_send_message(pf_sys_set.mailbox_id, message) != 0) {
        return -1;
    }
    if (message->callback == NULL) {
        error = pfk_get_semaphore(message->semaphore);
        pfk_delete_semaphore(message->semaphore);
        if (error != 0) {
            return -1;
        }
    }
    return 0;
}

s32 pfstub_store_result(PF_STUB_MESSAGE* message) {
    s32 error = 0;
    if (message->result_address != NULL) {
        *message->result_address = message->result;
        switch (message->operation) {
            case 0:
            case 1:
            case 54:
            case 100:
            case 101:
            case 122:
                if (message->result.stream == NULL) {
                    error = -1;
                }
                break;
            case 35:
                if (message->result.status != (s32)message->value) {
                    error = -1;
                }
                break;
            case 3:
            case 4:
                if (message->result.status != (s32)message->count) {
                    error = -1;
                }
                break;
            default:
                break;
        }
    } else {
        error = message->result.status;
    }
    return error;
}
