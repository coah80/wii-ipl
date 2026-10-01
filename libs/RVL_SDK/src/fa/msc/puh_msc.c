#include <private/fa/puh_msc.h>

s32 uhg_msc_memid_8169971C;
static s32 st_uhs_msc_tskid;
static s32 st_uhs_msc_msgid;
static s32 st_uhs_msc_status;
static s32 _uhf_msc_api_send_message(UHF_MSC_PARAMETERS* parameters, u32 command);

s32 usbh_msc_read10(UHF_MSC_DEVICE* device, u32 sector, u16 count, void* buffer, void* sense) {
    UHF_MSC_PARAMETERS parameters = {0};
    if (st_uhs_msc_status != 1) {
        return -3;
    }
    parameters.device = device;
    parameters.sector = sector;
    parameters.block_count = count;
    parameters.buffer = buffer;
    parameters.sense = sense;
    return _uhf_msc_api_send_message(&parameters, 0x1010a00);
}

s32 usbh_msc_write10(UHF_MSC_DEVICE* device, u32 sector, u16 count, void* buffer, void* sense) {
    UHF_MSC_PARAMETERS parameters = {0};
    if (st_uhs_msc_status != 1) {
        return -3;
    }
    parameters.device = device;
    parameters.sector = sector;
    parameters.block_count = count;
    parameters.buffer = buffer;
    parameters.sense = sense;
    return _uhf_msc_api_send_message(&parameters, 0x1010b00);
}

s32 usbh_msc_set_thread_priority(s32 priority) {
    s32 error;
    if (st_uhs_msc_tskid != 0) {
        error = uhf_ker_set_priority(st_uhs_msc_tskid, priority);
        if (error != 0) {
            return error;
        }
    }
    return 0;
}

static s32 _uhf_msc_api_send_message(UHF_MSC_PARAMETERS* parameters, u32 command) {
    s32 result = 0;
    s32 semaphore;
    UHF_MSC_MESSAGE* message;
    message = uhf_ker_get_memory_block(uhg_msc_memid_8169971C, sizeof(UHF_MSC_MESSAGE), 4);
    if (message == NULL) {
        return -12;
    }
    semaphore = uhf_ker_create_sem(0, 0);
    if (semaphore <= 0) {
        uhf_ker_release_memory_block(uhg_msc_memid_8169971C, message);
        return -12;
    }
    message->command = command;
    message->semaphore = semaphore;
    message->result = &result;
    message->parameters = *parameters;
    if (uhf_ker_send_message(st_uhs_msc_msgid, message, 0) != 0) {
        uhf_ker_release_memory_block(uhg_msc_memid_8169971C, message);
        uhf_ker_delete_sem(semaphore);
        return -12;
    }
    if (uhf_ker_get_sem(semaphore) != 0) {
        uhf_ker_delete_sem(semaphore);
        return -12;
    }
    if (uhf_ker_delete_sem(semaphore) != 0) {
        return -12;
    }
    return result;
}

s32 uhf_msc_get_message_id(void) {
    return st_uhs_msc_msgid;
}
