#include <private/fa/pf_kernel.h>

s32 pfk_create_task(PFK_TASK_CONFIG* config) {
    if (config == NULL) {
        OSReport("prfile2:ERR pfk_create_task() invalid param\n");
        return 0;
    }
    if (!OSCreateThread(config->thread, config->entry, config->argument,
                        (u8*)config->stack + config->stack_size, config->stack_size,
                        config->priority, 0)) {
        OSReport("prfile2:ERR pfk_create_task() failed to create thread\n");
        return 0;
    }
    return (s32)config->thread;
}

s32 pfk_start_task(s32 task_id) {
    if (task_id == 0) {
        OSReport("prfile2:ERR pfk_start_task() invalid tsk_id\n");
        return -2;
    }
    if (OSIsThreadSuspended((OSThread*)task_id) == TRUE) {
        OSResumeThread((OSThread*)task_id);
    }
    return 0;
}

s32 pfk_get_task_id(s32* task_id) {
    OSThread* thread;
    if (task_id == NULL) {
        OSReport("prfile2:ERR pfk_get_task_id() invalid param\n");
        return -2;
    }
    thread = OSGetCurrentThread();
    if (thread == NULL) {
        OSReport("INFO failed to OSGetCurrentThread\n");
        *task_id = 0;
        return -3;
    }
    *task_id = (s32)thread;
    return 0;
}

s32 pfk_set_task_priority(s32 task_id, s32 priority) {
    if (priority < 0 || priority > 31) {
        return -2;
    }
    return OSSetThreadPriority((OSThread*)task_id, priority) == TRUE ? 0 : -3;
}

s32 pfk_create_mailbox(PFK_MAILBOX_CONFIG* config) {
    if (config == NULL || config->queue == NULL || config->messages == NULL) {
        OSReport("prfile2:ERR pfk_create_mailbox() Invalid Param\n");
        return 0;
    }
    OSInitMessageQueue(config->queue, config->messages, config->count);
    return (s32)config->queue;
}

s32 pfk_receive_message(s32 mailbox, OSMessage* message) {
    if (mailbox == 0) {
        OSReport("prfile2:ERR pfk_receive_message() Invalid Param\n");
        return -2;
    }
    if (!OSReceiveMessage((OSMessageQueue*)mailbox, message, OS_MESSAGE_BLOCK)) {
        OSReport("prfile2:ERR pfk_receive_message() Faile to OSReceiveMessage()\n");
        return -3;
    }
    return 0;
}

s32 pfk_send_message(s32 mailbox, OSMessage message) {
    if (mailbox == 0 || message == NULL) {
        OSReport("prfile2:ERR pfk_send_message() Invalid Param\n");
        return -2;
    }
    if (!OSSendMessage((OSMessageQueue*)mailbox, message, 0)) {
        OSReport("prfile2:ERR pfk_send_message() Failed to pfk_send_message()\n");
        return -3;
    }
    return 0;
}

s32 pfk_create_semaphore(PFK_SEMAPHORE_CONFIG* config) {
    u32 count;
    if (config == NULL || config->semaphore == NULL || config->initial_count > config->maximum_count) {
        OSReport("prfile2:ERR pfk_create_semaphore() Invalid Param\n");
        return 0;
    }
    OSInitSemaphore(config->semaphore, config->maximum_count);
    for (count = config->maximum_count - config->initial_count; count != 0; count--) {
        OSWaitSemaphore(config->semaphore);
    }
    return (s32)config->semaphore;
}

s32 pfk_delete_semaphore(s32 semaphore) {
    if (semaphore == 0) {
        OSReport("prfile2:ERR pfk_delete_semaphore() Invalid Param\n");
        return -2;
    }
    return 0;
}

s32 pfk_get_semaphore(s32 semaphore) {
    if (semaphore == 0) {
        OSReport("prfile2:ERR pfk_get_semaphore() Invalid Param\n");
        return -2;
    }
    OSWaitSemaphore((OSSemaphore*)semaphore);
    return 0;
}

s32 pfk_release_semaphore(s32 semaphore) {
    if (semaphore == 0) {
        OSReport("prfile2:ERR pfk_release_semaphore() Invalid Param\n");
        return -2;
    }
    OSSignalSemaphore((OSSemaphore*)semaphore);
    return 0;
}
