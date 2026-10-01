#ifndef FA_PUH_MSC_H
#define FA_PUH_MSC_H

#include <revolution/fa/types.h>

typedef struct UHF_MSC_DEVICE {
    FADisk* disk;
    u32 device_id;
    u32 interface_id;
    u32 endpoint_in;
    u32 endpoint_out;
    u32 total_blocks;
    u32 block_size;
    u32 tag;
    u32 lun;
    u32 flags;
    u32 status;
    u32 event;
} UHF_MSC_DEVICE;

typedef struct UHF_MSC_PARAMETERS {
    UHF_MSC_DEVICE* device;
    void* sense;
    u32 timeout;
    void* buffer;
    u32 length;
    u32 sector;
    u16 transfer_flags;
    u16 block_count;
    u32 options;
    u32 result_size;
    FADisk* disk;
} UHF_MSC_PARAMETERS;

typedef struct UHF_MSC_MESSAGE {
    u32 command;
    s32 semaphore;
    s32* result;
    UHF_MSC_PARAMETERS parameters;
    void (*callback)(void*);
    void* context;
} UHF_MSC_MESSAGE;

extern UHF_MSC_DEVICE uhg_msc_blk_device_tbl[8];
extern s32 uhg_msc_memid;
s32 uhf_ker_set_priority(s32 task_id, s32 priority);
void* uhf_ker_get_memory_block(s32 pool, u32 size, u32 alignment);
s32 uhf_ker_release_memory_block(s32 pool, void* block);
s32 uhf_ker_create_sem(u32 initial_count, u32 maximum_count);
s32 uhf_ker_delete_sem(s32 semaphore);
s32 uhf_ker_get_sem(s32 semaphore);
s32 uhf_ker_send_message(s32 mailbox, void* message, u32 flags);
s32 uhf_ker_check_cacheable(void* buffer);
s32 usbh_msc_read10(UHF_MSC_DEVICE* device, u32 sector, u16 count, void* buffer, void* sense);
s32 usbh_msc_write10(UHF_MSC_DEVICE* device, u32 sector, u16 count, void* buffer, void* sense);
s32 uhf_msc_get_message_id(void);
s32 __uhf_msc_cmd_check_sense(const void* sense);

#endif
