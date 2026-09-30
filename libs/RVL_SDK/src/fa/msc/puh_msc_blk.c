#include <private/fa/puh_msc.h>
#include <string.h>

UHF_MSC_DEVICE uhg_msc_blk_device_tbl[8];
static u8* st_uhs_msc_blk_buf;
extern void pdm_disk_notify_media_insert(FADisk* disk);
s32 uhf_msc_blk_init(FADisk* disk);
s32 uhf_msc_blk_finalize(FADisk* disk);
s32 uhf_msc_blk_mount(FADisk* disk);
s32 uhf_msc_blk_unmount(FADisk* disk);
s32 uhf_msc_blk_format(FADisk* disk, u8* format);
s32 uhf_msc_blk_pread(FADisk* disk, u8* buffer, u32 sector, u32 blocks, u32* completed);
s32 uhf_msc_blk_pwrite(FADisk* disk, u8* buffer, u32 sector, u32 blocks, u32* completed);
s32 uhf_msc_blk_get_disk_info(FADisk* disk, FADiskInfo* info);
s32 _uhf_msc_blk_send_message(UHF_MSC_PARAMETERS* parameters, u32 command);

FAFuncTbl st_uhs_msc_blk_func = {
    uhf_msc_blk_init,
    uhf_msc_blk_finalize,
    uhf_msc_blk_mount,
    uhf_msc_blk_unmount,
    uhf_msc_blk_format,
    uhf_msc_blk_pread,
    uhf_msc_blk_pwrite,
    uhf_msc_blk_get_disk_info,
};

static inline UHF_MSC_DEVICE* uhf_msc_blk_find_device(FADisk* disk) {
    UHF_MSC_DEVICE* entry = uhg_msc_blk_device_tbl;
    UHF_MSC_DEVICE* device = NULL;
    u32 index;
    for (index = 0; index < 8; entry++, index++) {
        if (entry->disk == disk) {
            device = &uhg_msc_blk_device_tbl[index];
            break;
        }
    }
    return device;
}

s32 usbh_msc_blk_init_drv_tbl(FADiskTbl* table, u32 extension) {
    if (table == NULL) {
        return -1;
    }
    table->uiExt = extension;
    table->pFunc = (FAFuncTbl*)&st_uhs_msc_blk_func;
    return 0;
}

s32 uhf_msc_blk_init(FADisk* disk) {
    UHF_MSC_PARAMETERS parameters = {0};
    parameters.disk = disk;
    return _uhf_msc_blk_send_message(&parameters, 0x1010005);
}

s32 uhf_msc_blk_get_disk_info(FADisk* disk, FADiskInfo* info) {
    UHF_MSC_DEVICE* device;
    if (disk == NULL || info == NULL) {
        return -1;
    }
    device = uhf_msc_blk_find_device(disk);
    if (device == NULL) {
        return -1;
    }
    info->totalSectors = device->total_blocks;
    info->cylinders = 0;
    info->heads = 0;
    info->sectorsPerTrack = 0;
    info->bytesPerSector = device->block_size;
    info->mediaAttr = 0;
    if (device->flags & 0x1000) {
        info->mediaAttr |= 1;
    }
    info->formatParam = NULL;
    return 0;
}

s32 uhf_msc_blk_mount(FADisk* disk) {
    UHF_MSC_DEVICE* device;
    if (disk == NULL) {
        return -1;
    }
    device = uhf_msc_blk_find_device(disk);
    if (device == NULL) {
        return -1;
    }
    return ((device->flags >> 2) & 1) - 1;
}

s32 uhf_msc_blk_pread(FADisk* disk, u8* buffer, u32 sector, u32 blocks, u32* completed) {
    u16 transfer_blocks;
    UHF_MSC_DEVICE* device;
    s32 error;
    u32 block_size;
    u8* transfer_buffer;
    u32 transfer_limit;
    s32 cacheable;
    u8 sense[3] = {0};

    *completed = 0;
    if (disk == NULL || buffer == NULL) {
        return -1;
    }
    if (blocks == 0) {
        return 0;
    }
    device = uhf_msc_blk_find_device(disk);
    if (device == NULL) {
        return -1;
    }
    if (!(device->flags & 4)) {
        return -1;
    }
    block_size = device->block_size;
    if (block_size == 0) {
        return -1;
    }
    if (uhf_ker_check_cacheable(buffer) == 0) {
        transfer_limit = 512 / block_size;
        if (transfer_limit == 0) {
            return -1;
        }
        memset(st_uhs_msc_blk_buf, 0, 512);
        cacheable = 0;
        transfer_buffer = st_uhs_msc_blk_buf;
    } else {
        transfer_limit = 65536 / block_size;
        cacheable = 1;
        transfer_buffer = buffer;
    }
    do {
        transfer_blocks = transfer_limit;
        if (blocks <= transfer_limit) {
            transfer_blocks = blocks;
        }
        error = usbh_msc_read10(device, sector, transfer_blocks, transfer_buffer, sense);
        if (error == 0) {
            if (!cacheable) {
                memcpy(buffer, transfer_buffer, transfer_blocks * block_size);
                buffer += transfer_blocks * block_size;
            } else {
                transfer_buffer += transfer_blocks * block_size;
            }
            blocks -= transfer_blocks;
            sector += transfer_blocks;
            *completed += transfer_blocks;
            if (blocks == 0) {
                break;
            }
        } else {
            if (error == -15) {
                switch (__uhf_msc_cmd_check_sense(sense)) {
                    case 11:
                        break;
                    case 34:
                        if (device->disk != NULL) {
                            pdm_disk_notify_media_insert(device->disk);
                        }
                        break;
                    default:
                        break;
                }
                error = -1;
                break;
            } else {
                error = -1;
                break;
            }
        }
    } while (1);
    return error;
}

s32 uhf_msc_blk_pwrite(FADisk* disk, u8* buffer, u32 sector, u32 blocks, u32* completed) {
    u16 transfer_blocks;
    UHF_MSC_DEVICE* device;
    u32 block_size;
    s32 error;
    u8* transfer_buffer;
    u32 transfer_limit;
    s32 cacheable;
    u8 sense[3] = {0};

    *completed = 0;
    if (disk == NULL || buffer == NULL) {
        return -1;
    }
    if (blocks == 0) {
        return 0;
    }
    device = uhf_msc_blk_find_device(disk);
    if (device == NULL) {
        return -1;
    }
    if (!(device->flags & 4)) {
        return -1;
    }
    block_size = device->block_size;
    if (block_size == 0) {
        return -1;
    }
    if (uhf_ker_check_cacheable(buffer) == 0) {
        transfer_limit = 512 / block_size;
        if (transfer_limit == 0) {
            return -1;
        }
        cacheable = 0;
        transfer_buffer = st_uhs_msc_blk_buf;
    } else {
        transfer_limit = 65536 / block_size;
        cacheable = 1;
        transfer_buffer = buffer;
    }
    do {
        transfer_blocks = transfer_limit;
        if (blocks <= transfer_limit) {
            transfer_blocks = blocks;
        }
        if (!cacheable) {
            memcpy(transfer_buffer, buffer, transfer_blocks * block_size);
        }
        error = usbh_msc_write10(device, sector, transfer_blocks, transfer_buffer, sense);
        if (error == 0) {
            if (!cacheable) {
                buffer += transfer_blocks * block_size;
            }
            if (cacheable) {
                transfer_buffer += transfer_blocks * block_size;
            }
            blocks -= transfer_blocks;
            sector += transfer_blocks;
            *completed += transfer_blocks;
            if (blocks == 0) {
                break;
            }
        } else {
            if (error == -15) {
                switch (__uhf_msc_cmd_check_sense(sense)) {
                    case 11:
                    case 37:
                        break;
                    case 34:
                        if (device->disk != NULL) {
                            pdm_disk_notify_media_insert(device->disk);
                        }
                        break;
                    default:
                        break;
                }
                error = -1;
                break;
            } else {
                error = -1;
                break;
            }
        }
    } while (1);
    return error;
}

s32 uhf_msc_blk_format(FADisk* disk, u8* format) {
    return disk == NULL ? -1 : 0;
}

s32 uhf_msc_blk_finalize(FADisk* disk) {
    UHF_MSC_PARAMETERS parameters = {0};
    parameters.disk = disk;
    return _uhf_msc_blk_send_message(&parameters, 0x1010006);
}

s32 uhf_msc_blk_unmount(FADisk* disk) {
    return disk == NULL ? -1 : 0;
}

s32 uhf_msc_is_media_insert(FADisk* disk) {
    UHF_MSC_DEVICE* device = uhf_msc_blk_find_device(disk);
    if (device == NULL) {
        return 0;
    }
    if (!(device->flags & 4)) {
        return 0;
    }
    pdm_disk_notify_media_insert(disk);
    return 1;
}

s32 _uhf_msc_blk_send_message(UHF_MSC_PARAMETERS* parameters, u32 command) {
    s32 result = 0;
    s32 semaphore;
    UHF_MSC_MESSAGE* message;
    s32 mailbox = uhf_msc_get_message_id();
    message = uhf_ker_get_memory_block(uhg_msc_memid_8169971C, sizeof(UHF_MSC_MESSAGE), 4);
    if (message == NULL) {
        return -1;
    }
    semaphore = uhf_ker_create_sem(0, 0);
    if (semaphore <= 0) {
        uhf_ker_release_memory_block(uhg_msc_memid_8169971C, message);
        return -1;
    }
    message->command = command;
    message->semaphore = semaphore;
    message->result = &result;
    message->parameters = *parameters;
    if (uhf_ker_send_message(mailbox, message, 0) != 0) {
        uhf_ker_release_memory_block(uhg_msc_memid_8169971C, message);
        uhf_ker_delete_sem(semaphore);
        return -1;
    }
    if (uhf_ker_get_sem(semaphore) != 0) {
        uhf_ker_delete_sem(semaphore);
        return -1;
    }
    if (uhf_ker_delete_sem(semaphore) != 0) {
        return -1;
    }
    return result;
}
