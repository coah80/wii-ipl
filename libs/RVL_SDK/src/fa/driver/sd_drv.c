#include <stddef.h>
#include <revolution/fa/types.h>
#include <revolution/os.h>
#include <revolution/sdi.h>

typedef struct PFD_SDDRV_INFO {
    u32 flags;
    u32 bytes_per_sector;
    SDDev* device;
    FADisk* disk;
    u32 media_inserted;
    u32 media_ejected;
    s8 drive;
} ATTRIBUTE_ALIGN(8) PFD_SDDRV_INFO;

typedef union PFD_SDDEV_STORAGE {
    SDDev device;
    u32 words[16];
} PFD_SDDEV_STORAGE;

typedef struct PFD_SDDRV_FORMAT_DATA {
    u32 partition_start_sector;
    u32 partition_sector_count;
    u8 sectors_per_cluster;
    u32 sectors_per_fat;
    u32 volume_serial_number;
    u32 fat_type;
    u32 reserved_sectors;
    u32 total_sectors;
} PFD_SDDRV_FORMAT_DATA;

volatile PFD_SDDRV_INFO g_pfd_sddrv_info;
PFD_SDDEV_STORAGE g_pfd_sddev ATTRIBUTE_ALIGN(32);
u8 g_pfd_sddrv_buf[0x200];

static FAInsertCallback g_attach_func = 0;
static FAEjectCallback g_detach_func = 0;
u32 g_event ATTRIBUTE_ALIGN(32);

extern u8 pfd_get_media_drv_char(FADisk*, s8*, u32);
extern void pdm_disk_notify_media_insert(FADisk*);
extern void pdm_disk_notify_media_eject(FADisk*);
extern void* pf_memset(void*, s32, u32);
extern void* pf_memcpy(void*, const void*, u32);
extern s32 pf_strcmp(const char*, const char*);

s32 pfd_st_inter_callback(s32 status, void* data);
s32 pfd_st_removal_callback(s32 status, void* data);
static s32 pfd_sddrv_physical_read(u32 blocks, u8* buffer, u32 sector, u32 bytes_per_sector, u32* blocks_read);
s32 pfd_sddrv_physical_write(u32 blocks, u8* buffer, u32 sector, u32 bytes_per_sector, u32* blocks_written);
s32 pfd_sddrv_init(FADisk* disk);
s32 pfd_sddrv_finalize(FADisk* disk);
s32 pfd_sddrv_mount(FADisk* disk);
s32 pfd_sddrv_unmount(FADisk* disk);
s32 pfd_sddrv_format(FADisk* disk, u8* format_name);
s32 pfd_sddrv_pread(FADisk* disk, u8* buffer, u32 sector, u32 blocks, u32* blocks_read);
s32 pfd_sddrv_pwrite(FADisk* disk, u8* buffer, u32 sector, u32 blocks, u32* blocks_written);
s32 pfd_sddrv_get_disk_info(FADisk* disk, FADiskInfo* disk_info);

const FAFuncTbl pfd_sddrv_func = {
    pfd_sddrv_init,
    pfd_sddrv_finalize,
    pfd_sddrv_mount,
    pfd_sddrv_unmount,
    pfd_sddrv_format,
    pfd_sddrv_pread,
    pfd_sddrv_pwrite,
    pfd_sddrv_get_disk_info,
};

typedef struct PFD_SDDRV_SIZE_DEPEND {
    u32 min_sectors;
    u32 max_sectors;
    u32 reserved_sectors;
    u32 fat_copies;
    u32 root_entries;
    u8 sectors_per_cluster;
} PFD_SDDRV_SIZE_DEPEND;

typedef struct PFD_SDDRV_SIZE_SETTINGS {
    u32 reserved_sectors;
    u32 fat_copies;
    u32 root_entries;
    u8 sectors_per_cluster;
} PFD_SDDRV_SIZE_SETTINGS;

typedef struct PFD_SDDRV_BPB {
    u8 jump[3];
    u8 oem_name[8];
    u8 bytes_per_sector[2];
    u8 sectors_per_cluster;
    u8 reserved_sector_count[2];
    u8 fat_count;
    u8 root_entry_count[2];
    u8 total_sectors_16[2];
    u8 media_descriptor;
    u8 sectors_per_fat_16[2];
    u8 sectors_per_track[2];
    u8 heads[2];
    u8 hidden_sectors[4];
    u8 total_sectors_32[4];
    u8 drive_number;
    u8 reserved;
    u8 extended_signature;
    u8 volume_serial_number[4];
    u8 volume_label[11];
    u8 file_system_type[8];
    u8 boot_code[448];
    u8 signature[2];
} PFD_SDDRV_BPB;

typedef struct PFD_SDDRV_PARTITION_ENTRY {
    u8 boot_indicator;
    u8 start_head;
    u8 start_sector_cylinder[2];
    u8 partition_type;
    u8 end_head;
    u8 end_sector_cylinder[2];
    u8 first_sector[4];
    u8 sector_count[4];
} PFD_SDDRV_PARTITION_ENTRY;

typedef struct PFD_SDDRV_MBR {
    u8 boot_code[446];
    PFD_SDDRV_PARTITION_ENTRY partitions[4];
    u8 signature[2];
} PFD_SDDRV_MBR;

typedef union PFD_SDDRV_U32_BYTES {
    u32 value;
    u8 bytes[4];
} PFD_SDDRV_U32_BYTES;

typedef union PFD_SDDRV_U16_BYTES {
    u16 value;
    u8 bytes[2];
} PFD_SDDRV_U16_BYTES;

#define pfd_sddrv_store_le16(buffer, field, offset, value) \
    do { \
        if (((u32)(field) & 1) != 0) { \
            (field)[0] = (u8)(value); \
            (field)[1] = (u8)((value) >> 8); \
        } else { \
            ((u16*)(buffer))[(offset) / 2 + (offset) % 2] = (((value) & 0xff) << 8) | (((value) & 0xff00) >> 8); \
        } \
    } while (0)

#define pfd_sddrv_store_le32(buffer, field, offset, value) \
    do { \
        if (((u32)(field) & 3) != 0) { \
            (field)[0] = (u8)(value); \
            (field)[1] = (u8)((value) >> 8); \
            (field)[2] = (u8)((value) >> 16); \
            (field)[3] = (u8)((value) >> 24); \
        } else { \
            ((u32*)(buffer))[(offset) / 4 + (offset) % 4] = (((value) & 0xff) << 24 | ((value) & 0xff00) << 8) | \
                            (((value) & 0xff000000) >> 24 | ((value) & 0xff0000) >> 8); \
        } \
    } while (0)

static inline void pfd_sddrv_copy_bytes(u8* destination, const u8* source, u32 size) {
    u32 index;
    if (destination != 0 && source != 0) {
        for (index = 0; index < size; index++) {
            destination[index] = source[index];
        }
    }
}

typedef struct PFD_SDDRV_RESERVED_BOOT_SECTOR {
    u8 boot_code[0x1fe];
    PFD_SDDRV_U16_BYTES signature;
} PFD_SDDRV_RESERVED_BOOT_SECTOR;

typedef struct PFD_SDDRV_FAT32_FSINFO {
    PFD_SDDRV_U32_BYTES lead_signature;
    u8 reserved_04[0x1e0];
    PFD_SDDRV_U32_BYTES structure_signature;
    PFD_SDDRV_U32_BYTES free_cluster_count;
    PFD_SDDRV_U32_BYTES next_free_cluster;
    u8 reserved_1f0[12];
    PFD_SDDRV_U32_BYTES signature_word;
} PFD_SDDRV_FAT32_FSINFO;

typedef struct PFD_SDDRV_FAT32_BPB {
    u8 jump[3];
    u8 oem_name[8];
    u8 bytes_per_sector[2];
    u8 sectors_per_cluster;
    u8 reserved_sector_count[2];
    u8 fat_count;
    u8 root_entry_count[2];
    u8 total_sectors_16[2];
    u8 media_descriptor;
    u8 sectors_per_fat_16[2];
    u8 sectors_per_track[2];
    u8 heads[2];
    u8 hidden_sectors[4];
    u8 total_sectors_32[4];
    u8 sectors_per_fat_32[4];
    u8 ext_flags[2];
    u8 filesystem_version[2];
    u8 root_cluster[4];
    u8 fsinfo_sector[2];
    u8 backup_boot_sector[2];
    u8 reserved_34[12];
    u8 drive_number;
    u8 reserved_41;
    u8 extended_signature;
    u8 volume_serial_number[4];
    u8 volume_label[11];
    u8 filesystem_type[8];
    u8 boot_code[420];
    u8 signature[2];
} PFD_SDDRV_FAT32_BPB;

const PFD_SDDRV_SIZE_DEPEND sddrv_size_depend_tbl[14] = {
    {0x00000000, 0x00001000, 0x00000010, 0x00000002, 0x00000010, 0x10},
    {0x00001000, 0x00004000, 0x00000010, 0x00000002, 0x00000020, 0x10},
    {0x00004000, 0x00008000, 0x00000020, 0x00000002, 0x00000020, 0x20},
    {0x00008000, 0x00010000, 0x00000020, 0x00000004, 0x00000020, 0x20},
    {0x00010000, 0x00020000, 0x00000020, 0x00000008, 0x00000020, 0x20},
    {0x00020000, 0x00040000, 0x00000040, 0x00000008, 0x00000020, 0x20},
    {0x00040000, 0x00080000, 0x00000040, 0x00000010, 0x00000020, 0x20},
    {0x00080000, 0x000fc000, 0x00000080, 0x00000010, 0x0000003f, 0x20},
    {0x000fc000, 0x001f8000, 0x00000080, 0x00000020, 0x0000003f, 0x20},
    {0x001f8000, 0x00200000, 0x00000080, 0x00000040, 0x0000003f, 0x20},
    {0x00200000, 0x003f0000, 0x00000080, 0x00000040, 0x0000003f, 0x40},
    {0x003f0000, 0x00400000, 0x00000080, 0x00000080, 0x0000003f, 0x40},
    {0x00400000, 0x007e0000, 0x00002000, 0x00000080, 0x0000003f, 0x40},
    {0x007e0000, 0x04000000, 0x00002000, 0x000000ff, 0x0000003f, 0x40},
};

static inline void update_media_drive(void) {
    s8 drive;
    if (g_pfd_sddrv_info.drive == 0 && pfd_get_media_drv_char(g_pfd_sddrv_info.disk, &drive, 1) == 1) {
        g_pfd_sddrv_info.drive = drive;
    }
}

static inline void clear_mount_flag(void) {
    g_pfd_sddrv_info.flags &= ~2;
}

s32 pfd_st_inter_callback(s32 status, void* data) {
    s32 result;

    if ((status & 1) != 1) {
        return 0;
    }
    if (g_pfd_sddrv_info.device != 0) {
        g_event = 2;
        result = ISD_RegisterDeviceIntrHandler(g_pfd_sddrv_info.device, (SDDevIntrCallback)pfd_st_removal_callback, &g_event);
        if (result != 0) {
            OSReport("ERR:Failed to regist intr handler. pfd_st_inter_callback()\n");
        }
    }
    if (g_pfd_sddrv_info.disk != 0) {
        update_media_drive();
        pdm_disk_notify_media_insert(g_pfd_sddrv_info.disk);
        if (g_pfd_sddrv_info.drive != 0 && g_attach_func != 0) {
            g_attach_func(g_pfd_sddrv_info.drive);
        }
    }
    g_pfd_sddrv_info.media_inserted = 1;
    g_pfd_sddrv_info.media_ejected = 1;
    return 0;
}

s32 pfd_st_removal_callback(s32 status, void* data) {
    s32 result;

    if ((status & 2) != 2) {
        return 0;
    }
    g_pfd_sddrv_info.media_inserted = 0;
    if (g_pfd_sddrv_info.device != 0) {
        g_event = 1;
        result = ISD_RegisterDeviceIntrHandler(g_pfd_sddrv_info.device, (SDDevIntrCallback)pfd_st_inter_callback, &g_event);
        if (result != 0) {
            OSReport("ERR:Failed to regist intr handler. pfd_st_removal_callback()\n");
        }
    }
    if (g_pfd_sddrv_info.disk != 0) {
        update_media_drive();
        pdm_disk_notify_media_eject(g_pfd_sddrv_info.disk);
        if (g_pfd_sddrv_info.drive != 0 && g_detach_func != 0) {
            g_detach_func(g_pfd_sddrv_info.drive);
        }
    }
    return 0;
}

#pragma push
#pragma ppc_iro_level 0
s32 pfd_sddrv_init(FADisk* disk) {
    s32 sd_result;
    SDDev* device;
    u32 status;

    if (disk == NULL) {
        return -30;
    }
    if ((g_pfd_sddrv_info.flags & 1) != 0) {
        OSReport("INFO SD Card driver is already initialize. pfd_sddrv_init()\n");
        if (disk != g_pfd_sddrv_info.disk) {
            return -44;
        }
        return 0;
    } else {
        if ((g_pfd_sddrv_info.flags & 4) == 0) {
            g_pfd_sddrv_info.bytes_per_sector = 0x200;
            pf_memset(&g_pfd_sddev, 0, 0x28);
            sd_result = ISD_InitCard();
            if (sd_result != 0) {
                OSReport("ERR:Failed to init SD Card Driver in pfd_sddrv_init()\n");
                return -40;
            }
            g_pfd_sddrv_info.flags |= 4;
        }
        pf_memset(&g_pfd_sddev, 0, 0x28);
        device = &g_pfd_sddev.device;
        sd_result = ISD_MountCard(0, &device);
        if (sd_result != 0) {
            OSReport("ERR SD card can not mount [ret = 0x%x]. pfd_sddrv_init()\n", sd_result);
            return -41;
        }
        sd_result = ISD_GetDeviceStatus(device, &status);
        if (sd_result != 0) {
            OSReport("ERR Failed to get sd card status. [ret = 0x%x]\n", sd_result);
            return 21;
        }
        if ((status & 1) != 0) {
            g_pfd_sddrv_info.media_inserted = 1;
        }
        g_pfd_sddrv_info.device = device;
        if (g_pfd_sddrv_info.media_inserted != 0) {
            g_event = 2;
            sd_result = ISD_RegisterDeviceIntrHandler(device, (SDDevIntrCallback)pfd_st_removal_callback, &g_event);
            if (sd_result != 0) {
                OSReport("ERR:Failed to regist intr handler1 [ret = 0x%x] pfd_sddrv_init()\n", sd_result);
                ISD_UnmountCard(device);
                g_pfd_sddrv_info.device = 0;
                return -42;
            }
        } else {
            g_event = 1;
            sd_result = ISD_RegisterDeviceIntrHandler(device, (SDDevIntrCallback)pfd_st_inter_callback, &g_event);
            if (sd_result != 0) {
                OSReport("ERR:Failed to regist intr handler1 [ret = 0x%x] pfd_sddrv_init()\n", sd_result);
                ISD_UnmountCard(device);
                g_pfd_sddrv_info.device = 0;
                return -42;
            }
        }
        g_pfd_sddrv_info.disk = disk;
        g_pfd_sddrv_info.flags |= 1;
    }
    return 0;
}
#pragma pop

s32 pfd_sddrv_mount(FADisk* disk) {
    s32 result;
    u32 attempts;
    u32 ocr;
    u16 rca;
    u8 cid[16];

    if (disk == 0) {
        return -30;
    }
    if (g_pfd_sddrv_info.media_inserted == 0) {
        return -33;
    }
    if ((g_pfd_sddrv_info.flags & 2) != 0) {
        OSReport("INFO sdcard alrady mounted. pfd_sddrv_mount()\n");
        return 0;
    }
    attempts = 0;
    do {
        if (g_pfd_sddrv_info.media_inserted == 0) {
            return -33;
        }
        result = ISD_ResetDevice(g_pfd_sddrv_info.device);
        if (result == 0) {
            g_pfd_sddrv_info.media_ejected = 0;
            break;
        }
        OSReport("ERROR Failed to SD Card Reset [ret = 0x%x]. pfd_sddrv_mount()\n", result);
        attempts++;
    } while (attempts < 5);
    if (attempts == 5) {
        return -38;
    }
    if (g_pfd_sddrv_info.media_ejected != 0) {
        return -33;
    }
    ocr = 0;
    result = ISD_ReadCardRegister(g_pfd_sddrv_info.device, 0x29, &ocr, 4);
    if (result != 0) {
        OSReport("ERR Failed to read OCR reg. pfd_sddrv_mount()\n");
        return -43;
    }
    pf_memset(cid, 0, 0x10);
    result = ISD_ReadCardRegister(g_pfd_sddrv_info.device, 10, (u32*)cid, 0x10);
    if (result != 0) {
        OSReport("ERR Failed to read CID reg. pfd_sddrv_mount()\n");
        return -43;
    }
    rca = 0;
    result = ISD_ReadCardRegister(g_pfd_sddrv_info.device, 3, (u32*)&rca, 2);
    if (result != 0) {
        OSReport("ERR Failed to read RCA reg. pfd_sddrv_mount()\n");
        return -43;
    }
    g_pfd_sddrv_info.flags |= 2;
    return 0;
}

s32 pfd_sddrv_full_format(void);

s32 pfd_sddrv_format(FADisk* disk, u8* format_name) {
    s32 result;

    if (disk == 0) {
        return -30;
    }
    if (g_pfd_sddrv_info.media_inserted == 0) {
        return -33;
    }
    if (format_name != 0) {
        result = pf_strcmp((char*)format_name, "FULL_FORMAT");
        if (result == 0) {
            result = pfd_sddrv_full_format();
            if (result != 0) {
                OSReport("ERR Failed to full format. pfd_sddrv_full_format()\n");
                return result;
            }
        }
    }
    return 0;
}

s32 pfd_sddrv_pread(FADisk* disk, u8* buffer, u32 sector, u32 blocks, u32* blocks_read) {
    if (disk == 0 || buffer == 0 || blocks_read == 0) {
        return -30;
    }
    return pfd_sddrv_physical_read(blocks, buffer, sector, g_pfd_sddrv_info.bytes_per_sector, blocks_read);
}

s32 pfd_sddrv_pwrite(FADisk* disk, u8* buffer, u32 sector, u32 blocks, u32* blocks_written) {
    if (disk == 0 || buffer == 0 || blocks_written == 0) {
        return -30;
    }
    return pfd_sddrv_physical_write(blocks, buffer, sector, g_pfd_sddrv_info.bytes_per_sector, blocks_written);
}

s32 pfd_sddrv_unmount(FADisk* disk) {
    if (disk == 0) {
        return -30;
    }
    if ((g_pfd_sddrv_info.flags & 2) != 0) {
        clear_mount_flag();
    }
    return 0;
}

s32 pfd_sddrv_finalize(FADisk* disk) {
    s32 result;

    if (disk == 0) {
        return -30;
    }
    if ((g_pfd_sddrv_info.flags & 2) != 0) {
        clear_mount_flag();
    }
    if ((g_pfd_sddrv_info.flags & 1) != 0) {
        result = ISD_UnregisterDeviceIntrHandler(g_pfd_sddrv_info.device);
        if (result != 0) {
            OSReport("WARNING Faild to UnregisterDeviceIntrHandler sd card [ret = %d]\n", result);
        }
        result = ISD_UnmountCard(g_pfd_sddrv_info.device);
        if (result != 0) {
            OSReport("WARNING Faild to unmount sd card [ret = %d]\n", result);
        }
        g_pfd_sddrv_info.device = 0;
    }
    g_pfd_sddrv_info.flags = g_pfd_sddrv_info.flags & 0xfffffffe;
    g_pfd_sddrv_info.media_inserted = 0;
    g_pfd_sddrv_info.disk = 0;
    g_pfd_sddrv_info.drive = 0;
    return 0;
}

s32 pfd_sddrv_get_total_sectors(u32* sectors, u16* bytes_per_sector);

s32 pfd_sddrv_get_disk_info(FADisk* disk, FADiskInfo* disk_info) {
    s32 result;
    u32 status;

    if (disk == 0 || disk_info == 0) {
        return -30;
    }
    if ((g_pfd_sddrv_info.flags & 2) == 0) {
        return -45;
    }
    if (g_pfd_sddrv_info.media_ejected != 0) {
        return -45;
    }
    if (g_pfd_sddrv_info.media_inserted == 0) {
        return -33;
    }
    result = ISD_GetDeviceStatus(g_pfd_sddrv_info.device, &status);
    if (result != 0) {
        OSReport("ERR Failed to get sd card status. [ret = 0x%x]\n", result);
        return -39;
    }
    if ((status & 1) == 0) {
        OSReport("INFO Card not inserted! in pfd_sddrv_get_disk_info()\n");
        return -33;
    }
    if ((status & 2) != 0) {
        OSReport("INFO Card removed! in pfd_sddrv_get_disk_info()\n");
        return -33;
    }
    if ((status & 0x10000) == 0 && (status & 0x100000) == 0) {
        OSReport("INFO SD card type is not memory. in pfd_sddrv_get_disk_info()\n");
        return -35;
    }
    disk_info->mediaAttr = 4;
    if ((status & 4) != 0) {
        disk_info->mediaAttr |= 1;
    }
    result = pfd_sddrv_get_total_sectors(&disk_info->totalSectors, &disk_info->bytesPerSector);
    if (result != 0) {
        OSReport("ERR Failed to read master boot sector. pfd_sddrv_get_disk_info()\n");
        return result;
    }
    disk_info->cylinders = 0;
    disk_info->heads = 0;
    disk_info->sectorsPerTrack = 0;
    disk_info->formatParam = 0;
    return 0;
}

s32 pfd_sddrv_init_drv_tbl(FADiskTbl* disk_table, u32 extended) {
    disk_table->uiExt = extended;
    disk_table->pFunc = (FAFuncTbl*)&pfd_sddrv_func;
    return 0;
}

s32 pfd_sddrv_registar_callback(FAInsertCallback attach, FAEjectCallback detach) {
    g_attach_func = attach;
    g_detach_func = detach;
    return 0;
}

s32 pfd_sddrv_is_media_insert(void) {
    s32 result;
    s8 drive;

    if ((g_pfd_sddrv_info.flags & 1) != 0) {
        if (g_pfd_sddrv_info.drive == 0 && pfd_get_media_drv_char(g_pfd_sddrv_info.disk, &drive, 1) == 1) {
            g_pfd_sddrv_info.drive = drive;
        }
        if (g_pfd_sddrv_info.media_inserted != 0) {
            pdm_disk_notify_media_insert(g_pfd_sddrv_info.disk);
            result = 1;
        } else {
            result = 0;
        }
    } else {
        result = 0;
    }
    return result;
}

static s32 pfd_sddrv_physical_read(u32 blocks, u8* buffer, u32 sector, u32 bytes_per_sector, u32* blocks_read) {
    s32 result;
    s32 current_sector;
    u32 completed;
    u8* current_buffer;
    if ((g_pfd_sddrv_info.flags & 2) == 0) {
        *blocks_read = 0;
        return -45;
    }
    if (g_pfd_sddrv_info.media_ejected != 0) {
        return -45;
    }
    if (blocks == 0) {
        *blocks_read = 0;
        return -30;
    }
    *blocks_read = 0xffffffff;
    current_sector = sector;
    if (((u32)buffer & 0x1f) == 0) {
        if (g_pfd_sddrv_info.media_inserted == 0) {
            *blocks_read = 0;
            return -33;
        }
        if (blocks == 1) {
            result = ISD_ReadBlock(g_pfd_sddrv_info.device, current_sector, buffer, blocks);
            if (result != 0) {
                OSReport("INFO Failed to read SD card1 [ret = 0x%x] pfd_sddrv_physical_read()\n", result);
                *blocks_read = 0;
                return -37;
            }
        } else {
            result = ISD_ReadMultiBlock(g_pfd_sddrv_info.device, current_sector, buffer, blocks);
            if (result != 0) {
                OSReport("INFO Failed to read SD card2 [ret = 0x%x] pfd_sddrv_physical_read()\n", result);
                *blocks_read = 0;
                return -37;
            }
        }
    } else {
        for (completed = 0, current_buffer = buffer; completed < blocks; current_buffer += bytes_per_sector, current_sector++, completed++) {
            if (g_pfd_sddrv_info.media_inserted == 0) {
                if (completed != 0) {
                    *blocks_read = completed;
                    return 0;
                }
                *blocks_read = 0;
                return -33;
            }
            result = ISD_ReadBlock(g_pfd_sddrv_info.device, current_sector, g_pfd_sddrv_buf, 1);
            if (result != 0) {
                OSReport("INFO Failed to read SD card3 [ret = 0x%x] pfd_sddrv_physical_read()\n", result);
                if (completed != 0) {
                    *blocks_read = completed;
                    return 0;
                }
                *blocks_read = 0;
                return -37;
            }
            pf_memcpy(current_buffer, g_pfd_sddrv_buf, bytes_per_sector);
        }
    }
    *blocks_read = blocks;
    return 0;
}

s32 pfd_sddrv_physical_write(u32 blocks, u8* buffer, u32 sector, u32 bytes_per_sector, u32* blocks_written) {
    s32 result;
    s32 current_sector;
    u32 completed;
    u8* current_buffer;
    if ((g_pfd_sddrv_info.flags & 2) == 0) {
        *blocks_written = 0;
        return -45;
    }
    if (g_pfd_sddrv_info.media_ejected != 0) {
        return -45;
    }
    if (blocks == 0) {
        *blocks_written = 0;
        return -30;
    }
    *blocks_written = 0xffffffff;
    current_sector = sector;
    if (((u32)buffer & 0x1f) == 0) {
        if (g_pfd_sddrv_info.media_inserted == 0) {
            *blocks_written = 0;
            return -33;
        }
        if (blocks == 1) {
            result = ISD_WriteBlock(g_pfd_sddrv_info.device, current_sector, buffer, blocks);
            if (result != 0) {
                OSReport("INFO Failed to write SD card1 [ret = 0x%x] pfd_sddrv_physical_write()\n", result);
                *blocks_written = 0;
                return -36;
            }
        } else {
            result = ISD_WriteMultiBlock(g_pfd_sddrv_info.device, current_sector, buffer, blocks);
            if (result != 0) {
                OSReport("INFO Failed to write SD card2 [ret = 0x%x] pfd_sddrv_physical_write()\n", result);
                *blocks_written = 0;
                return -36;
            }
        }
    } else {
        for (completed = 0, current_buffer = buffer; completed < blocks; current_buffer += bytes_per_sector, current_sector++, completed++) {
            if (g_pfd_sddrv_info.media_inserted == 0) {
                if (completed != 0) {
                    *blocks_written = completed;
                    return 0;
                }
                *blocks_written = 0;
                return -33;
            }
            pf_memcpy(g_pfd_sddrv_buf, current_buffer, bytes_per_sector);
            result = ISD_WriteBlock(g_pfd_sddrv_info.device, current_sector, g_pfd_sddrv_buf, 1);
            if (result != 0) {
                OSReport("INFO Failed to write SD card3 [ret = 0x%x] pfd_sddrv_physical_write()\n", result);
                if (completed != 0) {
                    *blocks_written = completed;
                    return 0;
                }
                *blocks_written = 0;
                return -36;
            }
        }
    }
    *blocks_written = blocks;
    return 0;
}

s32 pfd_sddrv_get_total_sectors(u32* sectors, u16* bytes_per_sector) {
    s32 result;
    u32 csd[4];
    u32 c_size;
    u32 cluster_blocks;
    u32 read_block_length;
    u16 multiplier;
    u16 minimum_multiplier;
    u16 max_multiplier;
    u16 read_block_size;
    u16 multiplier_factor;

    if (g_pfd_sddrv_info.media_inserted == 0) {
        return -33;
    }
    pf_memset(csd, 0, 0x10);
    result = ISD_ReadCardRegister(g_pfd_sddrv_info.device, 9, csd, 0x10);
    if (result != 0) {
        OSReport("ERR Failed to get CSD Info. pfd_sddrv_get_total_sectors()\n");
        return -43;
    }
    if ((csd[3] & 0x400000) == 0) {
        read_block_length = ((csd[1] >> 7) & 7) + 2;
        read_block_size = 1 << read_block_length;
        c_size = (((csd[2] & 3) << 10 | csd[1] >> 22) + 1);
        cluster_blocks = c_size * read_block_size;
        multiplier = (csd[2] >> 8) & 0xf;
        minimum_multiplier = multiplier >= 9 ? multiplier : 9;
        max_multiplier = minimum_multiplier <= 11 ? minimum_multiplier : 11;
        multiplier_factor = 1;
        max_multiplier = (u16)(max_multiplier - 9);
        multiplier_factor = (u16)(multiplier_factor << max_multiplier);
        *sectors = cluster_blocks * multiplier_factor;
    } else {
        *sectors = ((csd[1] >> 8 & 0x3fffff) + 1) * 0x400;
    }
    *bytes_per_sector = 0x200;
    return 0;
}

static inline u32 pfd_sddrv_encode_serial(s32 year, s32 month, s32 day, s32 hour, s32 minute, s32 second) {
    u32 date;
    u32 time;
    date = (day & 0x1f) | ((month & 0xf) << 5) | (((year - 1900) & 0x7f) << 9);
    time = (second & 0x1f) | ((minute & 0x3f) << 5) | ((hour & 0x1f) << 11);
    return (date << 16) + time;
}

s32 pfd_sddrv_calc_mbr_bpb(PFD_SDDRV_FORMAT_DATA* format_data) {
    PFD_SDDRV_SIZE_SETTINGS settings;
    u32 entry_index;
    u32 requested_sectors;
    const PFD_SDDRV_SIZE_DEPEND* size_entry;
    u32 current_start;
    u32 reserved_sectors;
    u32 total_sectors;
    u32 fat_sectors;
    u32 fat_entry_bits;
    u32 fixed_sectors;
    u32 start_sector;
    u32 next_fat_sectors;
    u32 clusters;
    u32 candidate_fat_sectors;
    u32 reserve_count;
    int moved_start = 0;
    s32 result;
    OSCalendarTime current_time;

    if (format_data == 0) {
        return -30;
    }
    pf_memset(&settings, 0, sizeof(settings));
    requested_sectors = format_data->total_sectors;
    size_entry = sddrv_size_depend_tbl;
    for (entry_index = 0; entry_index < 14; size_entry++, entry_index++) {
        if (size_entry->min_sectors < requested_sectors && size_entry->max_sectors >= requested_sectors) {
            settings.reserved_sectors = sddrv_size_depend_tbl[entry_index].reserved_sectors;
            settings.fat_copies = sddrv_size_depend_tbl[entry_index].fat_copies;
            settings.root_entries = sddrv_size_depend_tbl[entry_index].root_entries;
            settings.sectors_per_cluster = sddrv_size_depend_tbl[entry_index].sectors_per_cluster;
            break;
        }
    }
    result = entry_index == 14 ? -30 : 0;
    if (result != 0) {
        OSReport("ERR Failed to get values with total sectors. pfd_sddrv_get_value_with_total_sectors()\n");
        return result;
    }
    format_data->sectors_per_cluster = settings.sectors_per_cluster;
    total_sectors = format_data->total_sectors;
    clusters = total_sectors / format_data->sectors_per_cluster;
    if (clusters < 0x1005) {
        fat_entry_bits = 12;
    } else if (clusters < 0xfff5) {
        fat_entry_bits = 16;
    } else {
        return -31;
    }
    if (total_sectors % format_data->sectors_per_cluster != 0) {
        clusters++;
    }
    candidate_fat_sectors = clusters * fat_entry_bits;
    fat_sectors = candidate_fat_sectors >> 12;
    if ((candidate_fat_sectors & 0xfff) != 0) {
        fat_sectors++;
    }
    reserved_sectors = settings.reserved_sectors;
    for (;;) {
        fixed_sectors = fat_sectors * 2 + 0x21;
        reserve_count = 1;
        current_start = reserved_sectors;
        for (;;) {
            start_sector = current_start - fixed_sectors;
            if ((s32)start_sector > 0) {
                break;
            }
            current_start += reserved_sectors;
            reserve_count++;
        }
        current_start = reserve_count * reserved_sectors;
        for (;;) {
            if (moved_start == 0 && reserved_sectors != start_sector) {
                start_sector += reserved_sectors;
            }
            moved_start = 0;
            clusters = (total_sectors - start_sector - fixed_sectors) / format_data->sectors_per_cluster + 1;
            if (clusters >= 0xfe5 && clusters < 0x1005) {
                current_start += reserved_sectors;
                start_sector = current_start - fixed_sectors;
                continue;
            }
            candidate_fat_sectors = (clusters - 1) * fat_entry_bits + 2;
            next_fat_sectors = candidate_fat_sectors >> 12;
            if ((candidate_fat_sectors & 0xfff) != 0) {
                next_fat_sectors++;
            }
            if (next_fat_sectors <= fat_sectors) {
                break;
            }
            start_sector += reserved_sectors;
            moved_start = 1;
        }
        if (next_fat_sectors == fat_sectors) {
            break;
        }
        fat_sectors = next_fat_sectors;
    }
    format_data->sectors_per_fat = fat_sectors;
    format_data->partition_start_sector = start_sector;
    format_data->partition_sector_count = format_data->total_sectors - start_sector;
    clusters = (format_data->partition_sector_count - (format_data->sectors_per_fat * 2 + 0x21)) / format_data->sectors_per_cluster + 1;
    if (clusters < 0xff5) {
        format_data->fat_type = 0;
    } else if (clusters >= 0xff5) {
        format_data->fat_type = 1;
    } else {
        return -31;
    }
    OSTicksToCalendarTime(OSGetTime(), &current_time);
    format_data->volume_serial_number = pfd_sddrv_encode_serial(current_time.year, current_time.mon, current_time.mday,
                                                               current_time.hour, current_time.min, current_time.sec);
    return 0;
}


s32 pfd_sddrv_store_bpb_buf(PFD_SDDRV_FORMAT_DATA* format_data, u8* sector_buffer) {
    PFD_SDDRV_SIZE_SETTINGS settings;
    PFD_SDDRV_BPB* boot_sector;
    u32 entry_index;
    u32 requested_sectors;
    const PFD_SDDRV_SIZE_DEPEND* size_entry;
    u16 sectors_16;
    s32 result;
    u32 sectors_32;

    if (format_data == 0) {
        return -30;
    }
    pf_memset(&settings, 0, 0x10);
    requested_sectors = format_data->total_sectors;
    size_entry = sddrv_size_depend_tbl;
    for (entry_index = 0; entry_index < 14; size_entry++, entry_index++) {
        if (size_entry->min_sectors < requested_sectors && size_entry->max_sectors >= requested_sectors) {
            settings.reserved_sectors = sddrv_size_depend_tbl[entry_index].reserved_sectors;
            settings.fat_copies = sddrv_size_depend_tbl[entry_index].fat_copies;
            settings.root_entries = sddrv_size_depend_tbl[entry_index].root_entries;
            settings.sectors_per_cluster = sddrv_size_depend_tbl[entry_index].sectors_per_cluster;
            break;
        }
    }
    result = entry_index == 14 ? -30 : 0;
    if (result != 0) {
        OSReport("ERR Failed to get values with total sectors. pfd_sddrv_get_value_with_total_sectors()\n");
        return result;
    }
    sectors_32 = format_data->partition_sector_count;
    if (sectors_32 != 0 && sectors_32 < 0x10000) {
        sectors_16 = sectors_32;
        sectors_32 = 0;
    } else if (sectors_32 >= 0x10000) {
        sectors_16 = 0;
    } else {
        return -30;
    }
    pf_memset(sector_buffer, 0, 0x200);
    boot_sector = (PFD_SDDRV_BPB*)sector_buffer;
    pfd_sddrv_copy_bytes(boot_sector->oem_name, (const u8*)"        ", 8);
    pfd_sddrv_copy_bytes(boot_sector->volume_label, (const u8*)"NO NAME    ", 11);
    if (format_data->fat_type == 0) {
        pfd_sddrv_copy_bytes(boot_sector->file_system_type, (const u8*)"FAT12   ", 8);
    } else {
        pfd_sddrv_copy_bytes(boot_sector->file_system_type, (const u8*)"FAT16   ", 8);
    }
    boot_sector->jump[0] = 0xeb;
    boot_sector->jump[1] = 0;
    boot_sector->jump[2] = 0x90;
    pfd_sddrv_store_le16(sector_buffer, boot_sector->bytes_per_sector, offsetof(PFD_SDDRV_BPB, bytes_per_sector), 0x200);
    boot_sector->sectors_per_cluster = format_data->sectors_per_cluster;
    pfd_sddrv_store_le16(sector_buffer, boot_sector->reserved_sector_count, offsetof(PFD_SDDRV_BPB, reserved_sector_count), 1);
    boot_sector->fat_count = 2;
    pfd_sddrv_store_le16(sector_buffer, boot_sector->root_entry_count, offsetof(PFD_SDDRV_BPB, root_entry_count), 0x200);
    pfd_sddrv_store_le16(sector_buffer, boot_sector->total_sectors_16, offsetof(PFD_SDDRV_BPB, total_sectors_16), sectors_16);
    boot_sector->media_descriptor = 0xf8;
    pfd_sddrv_store_le16(sector_buffer, boot_sector->sectors_per_fat_16, offsetof(PFD_SDDRV_BPB, sectors_per_fat_16), (u16)format_data->sectors_per_fat);
    pfd_sddrv_store_le16(sector_buffer, boot_sector->sectors_per_track, offsetof(PFD_SDDRV_BPB, sectors_per_track), (u16)settings.root_entries);
    pfd_sddrv_store_le16(sector_buffer, boot_sector->heads, offsetof(PFD_SDDRV_BPB, heads), (u16)settings.fat_copies);
    pfd_sddrv_store_le32(sector_buffer, boot_sector->hidden_sectors, offsetof(PFD_SDDRV_BPB, hidden_sectors), format_data->partition_start_sector);
    pfd_sddrv_store_le32(sector_buffer, boot_sector->total_sectors_32, offsetof(PFD_SDDRV_BPB, total_sectors_32), sectors_32);
    boot_sector->drive_number = 0x80;
    boot_sector->extended_signature = 0x29;
    pfd_sddrv_store_le32(sector_buffer, boot_sector->volume_serial_number, offsetof(PFD_SDDRV_BPB, volume_serial_number), format_data->volume_serial_number);
    boot_sector->signature[0] = 0x55;
    boot_sector->signature[1] = 0xaa;
    return 0;
}

s32 pfd_sddrv_store_mbr_buf(PFD_SDDRV_FORMAT_DATA* format_data, u8* sector_buffer) {
    PFD_SDDRV_SIZE_SETTINGS settings;
    PFD_SDDRV_MBR* master_boot_record;
    PFD_SDDRV_PARTITION_ENTRY* partition;
    u32 entry_index;
    u32 requested_sectors;
    const PFD_SDDRV_SIZE_DEPEND* size_entry;
    s32 result;
    u8 partition_type;
    u8 start_head;
    u16 start_sector;
    u16 start_cylinder;
    u8 end_head;
    u16 end_sector;
    u16 end_cylinder;
    u32 sectors_per_track;
    u32 first_sector;
    u32 sectors_per_cylinder;
    u32 last_sector;
    u32 sector_count;

    if (format_data == 0) {
        return -30;
    }
    pf_memset(&settings, 0, 0x10);
    requested_sectors = format_data->total_sectors;
    size_entry = sddrv_size_depend_tbl;
    for (entry_index = 0; entry_index < 14; size_entry++, entry_index++) {
        if (size_entry->min_sectors < requested_sectors && size_entry->max_sectors >= requested_sectors) {
            settings.reserved_sectors = sddrv_size_depend_tbl[entry_index].reserved_sectors;
            settings.fat_copies = sddrv_size_depend_tbl[entry_index].fat_copies;
            settings.root_entries = sddrv_size_depend_tbl[entry_index].root_entries;
            settings.sectors_per_cluster = sddrv_size_depend_tbl[entry_index].sectors_per_cluster;
            break;
        }
    }
    result = entry_index == 14 ? -30 : 0;
    if (result != 0) {
        OSReport("ERR Failed to get values with total sectors. pfd_sddrv_get_value_with_total_sectors()\n");
        return result;
    }
    sectors_per_track = settings.root_entries;
    sectors_per_cylinder = settings.fat_copies * sectors_per_track;
    first_sector = format_data->partition_start_sector;
    last_sector = format_data->total_sectors - 1;
    sector_count = format_data->partition_sector_count;
    start_cylinder = first_sector / sectors_per_cylinder;
    start_head = (first_sector % sectors_per_cylinder) / sectors_per_track;
    start_sector = first_sector % sectors_per_track + 1;
    end_cylinder = last_sector / sectors_per_cylinder;
    end_head = (last_sector % sectors_per_cylinder) / sectors_per_track;
    end_sector = last_sector % sectors_per_track + 1;
    if (sector_count == 0) {
        return -30;
    }
    if (sector_count != 0 && sector_count < 0x7fa8) {
        partition_type = 1;
    } else if (sector_count >= 0x7fa8 && sector_count < 0x10000) {
        partition_type = 4;
    } else {
        partition_type = 6;
    }
    pf_memset(sector_buffer, 0, 0x200);
    master_boot_record = (PFD_SDDRV_MBR*)sector_buffer;
    partition = &master_boot_record->partitions[0];
    partition->boot_indicator = 0;
    partition->start_head = start_head;
    pfd_sddrv_store_le16(sector_buffer, partition->start_sector_cylinder, offsetof(PFD_SDDRV_MBR, partitions) + offsetof(PFD_SDDRV_PARTITION_ENTRY, start_sector_cylinder),
        ((start_cylinder & 0xff) << 8) + ((start_sector & 0x3f) | ((start_cylinder & 0x300) >> 2)));
    partition->partition_type = partition_type;
    partition->end_head = end_head;
    pfd_sddrv_store_le16(sector_buffer, partition->end_sector_cylinder, offsetof(PFD_SDDRV_MBR, partitions) + offsetof(PFD_SDDRV_PARTITION_ENTRY, end_sector_cylinder),
        ((end_cylinder & 0xff) << 8) + ((end_sector & 0x3f) | ((end_cylinder & 0x300) >> 2)));
    pfd_sddrv_store_le32(sector_buffer, partition->first_sector, offsetof(PFD_SDDRV_MBR, partitions) + offsetof(PFD_SDDRV_PARTITION_ENTRY, first_sector), format_data->partition_start_sector);
    pfd_sddrv_store_le32(sector_buffer, partition->sector_count, offsetof(PFD_SDDRV_MBR, partitions) + offsetof(PFD_SDDRV_PARTITION_ENTRY, sector_count), format_data->partition_sector_count);
    master_boot_record->signature[0] = 0x55;
    master_boot_record->signature[1] = 0xaa;
    return 0;
}

s32 pfd_sddrv_build_mbr_bpb(u32 total_sectors) {
    PFD_SDDRV_FORMAT_DATA format_data;
    s32 result;
    u32 partition_start_sector;

    pf_memset(&format_data, 0, 0x20);
    format_data.total_sectors = total_sectors;
    result = pfd_sddrv_calc_mbr_bpb(&format_data);
    if (result != 0) {
        OSReport("ERR Failed to calculate MBR and BPB values. pfd_sddrv_calc_mbr_bpb()\n");
        return result;
    }
    result = pfd_sddrv_store_bpb_buf(&format_data, g_pfd_sddrv_buf);
    if (result != 0) {
        OSReport("ERR Failed to store BPB values to buf. pfd_sddrv_store_bpb_buf()\n");
        return result;
    }
    partition_start_sector = format_data.partition_start_sector;
    if (g_pfd_sddrv_info.media_inserted == 0) {
        return -33;
    }
    if (g_pfd_sddrv_info.media_ejected != 0) {
        return -33;
    }
    result = ISD_WriteBlock(g_pfd_sddrv_info.device, partition_start_sector, g_pfd_sddrv_buf, 1);
    if (result != 0) {
        OSReport("ERR Failed to write BPB fields. ISD_WriteBlock()\n");
        return -36;
    }
    result = pfd_sddrv_store_mbr_buf(&format_data, g_pfd_sddrv_buf);
    if (result != 0) {
        OSReport("ERR Failed to store MBR values to buf. pfd_sddrv_store_mbr_buf()\n");
        return result;
    }
    if (g_pfd_sddrv_info.media_inserted == 0) {
        return -33;
    }
    if (g_pfd_sddrv_info.media_ejected != 0) {
        return -33;
    }
    result = ISD_WriteBlock(g_pfd_sddrv_info.device, 0, g_pfd_sddrv_buf, 1);
    if (result != 0) {
        OSReport("ERR Failed to write MBR fields. ISD_WriteBlock()\n");
        return -36;
    }
    return 0;
}

s32 pfd_sddrv_calc_fat32_mbr_bpb(PFD_SDDRV_FORMAT_DATA* format_data) {
    u8 sectors_per_cluster;
    u32 fat_sector_count;
    u32 available_sectors;
    u32 fat_sectors;
    u32 cluster_count;
    u32 entry_index;
    u32 requested_sectors;
    const PFD_SDDRV_SIZE_DEPEND* size_entry;
    PFD_SDDRV_SIZE_SETTINGS settings;
    u32 reserved_sectors = 0;
    u32 data_start_sector;
    u32 calculated_fat_sectors;
    u32 attempts;
    s32 result;
    u32 next_data_region;
    u32 total_sectors;
    OSCalendarTime current_time;

    if (format_data == 0) {
        return -30;
    }
    pf_memset(&settings, 0, 0x10);
    requested_sectors = format_data->total_sectors;
    total_sectors = format_data->total_sectors;
    size_entry = sddrv_size_depend_tbl;
    for (entry_index = 0; entry_index < 14; size_entry++, entry_index++) {
        if (size_entry->min_sectors >= requested_sectors) {
            continue;
        }
        if (size_entry->max_sectors < requested_sectors) {
            continue;
        }
        settings.reserved_sectors = sddrv_size_depend_tbl[entry_index].reserved_sectors;
        settings.fat_copies = sddrv_size_depend_tbl[entry_index].fat_copies;
        settings.root_entries = sddrv_size_depend_tbl[entry_index].root_entries;
        settings.sectors_per_cluster = sddrv_size_depend_tbl[entry_index].sectors_per_cluster;
        break;
    }
    result = entry_index == 14 ? -30 : 0;
    if (result != 0) {
        OSReport("ERR Failed to get values with total sectors. pfd_sddrv_get_value_with_total_sectors()\n");
        return result;
    }
    sectors_per_cluster = settings.sectors_per_cluster;
    format_data->sectors_per_cluster = sectors_per_cluster;
    total_sectors = format_data->total_sectors;
    cluster_count = total_sectors / sectors_per_cluster;
    fat_sectors = (cluster_count >> 7) & 0xfffff;
    if ((cluster_count * 32 & 0xfe0) != 0) {
        fat_sectors++;
    }
    fat_sector_count = fat_sectors * 2;
    available_sectors = total_sectors - 0x2000;
    attempts = fat_sectors;
    for (; attempts != 0; attempts--) {
        next_data_region = 0x2000;
        for (;;) {
            reserved_sectors = next_data_region - fat_sector_count;
            if ((s32)reserved_sectors > 0) {
                break;
            }
            next_data_region += 0x2000;
        }
        if (reserved_sectors < 9) {
            reserved_sectors += 0x2000;
        }
        data_start_sector = reserved_sectors + fat_sector_count;
        for (;;) {
            cluster_count = (available_sectors - data_start_sector) / sectors_per_cluster + 2;
            calculated_fat_sectors = (cluster_count >> 7) & 0xfffff;
            if ((cluster_count * 32 & 0xfe0) != 0) {
                calculated_fat_sectors++;
            }
            if (calculated_fat_sectors <= fat_sectors) {
                break;
            }
            reserved_sectors += 0x2000;
            data_start_sector += 0x2000;
        }
        if (calculated_fat_sectors == fat_sectors) {
            break;
        }
        fat_sector_count -= 2;
        fat_sectors--;
    }
    if (fat_sectors == 0) {
        return -31;
    }
    format_data->sectors_per_fat = fat_sectors;
    format_data->reserved_sectors = reserved_sectors;
    format_data->partition_start_sector = 0x2000;
    format_data->partition_sector_count = format_data->total_sectors - 0x2000;
    OSTicksToCalendarTime(OSGetTime(), &current_time);
    format_data->volume_serial_number = pfd_sddrv_encode_serial(current_time.year, current_time.mon, current_time.mday,
                                                               current_time.hour, current_time.min, current_time.sec);
    return 0;
}

s32 pfd_sddrv_store_fat32_mbr_buf(PFD_SDDRV_FORMAT_DATA* format_data, u8* sector_buffer) {
    PFD_SDDRV_SIZE_SETTINGS settings;
    PFD_SDDRV_MBR* master_boot_record;
    PFD_SDDRV_PARTITION_ENTRY* partition;
    u32 entry_index;
    u32 requested_sectors;
    const PFD_SDDRV_SIZE_DEPEND* size_entry;
    s32 result;
    u32 cylinder_size;
    u8 partition_type;
    u8 start_head;
    u16 start_sector;
    u16 start_cylinder;
    u8 end_head;
    u16 end_sector;
    u16 end_cylinder;
    u32 partition_end;

    if (format_data == 0 || sector_buffer == 0) {
        return -30;
    }
    pf_memset(&settings, 0, 0x10);
    requested_sectors = format_data->total_sectors;
    size_entry = sddrv_size_depend_tbl;
    for (entry_index = 0; entry_index < 14; size_entry++, entry_index++) {
        if (size_entry->min_sectors < requested_sectors && size_entry->max_sectors >= requested_sectors) {
            settings.reserved_sectors = sddrv_size_depend_tbl[entry_index].reserved_sectors;
            settings.fat_copies = sddrv_size_depend_tbl[entry_index].fat_copies;
            settings.root_entries = sddrv_size_depend_tbl[entry_index].root_entries;
            settings.sectors_per_cluster = sddrv_size_depend_tbl[entry_index].sectors_per_cluster;
            break;
        }
    }
    result = entry_index == 14 ? -30 : 0;
    if (result != 0) {
        OSReport("ERR Failed to get values with total sectors. pfd_sddrv_get_value_with_total_sectors()\n");
        return result;
    }
    if (format_data->partition_start_sector > 0xfb0400) {
        start_head = 0xfe;
        start_sector = 0x3f;
        start_cylinder = 0x3ff;
    } else {
        start_cylinder = format_data->partition_start_sector / (settings.fat_copies * settings.root_entries);
        start_head = (format_data->partition_start_sector % (settings.fat_copies * settings.root_entries)) / settings.root_entries;
        start_sector = format_data->partition_start_sector % settings.root_entries + 1;
    }
    if (format_data->total_sectors > 0xfb0400) {
        end_head = 0xfe;
        end_sector = 0x3f;
        end_cylinder = 0x3ff;
        partition_type = 0x0c;
    } else {
        partition_end = format_data->total_sectors - 1;
        partition_type = 0x0b;
        end_cylinder = partition_end / (settings.fat_copies * settings.root_entries);
        end_head = (partition_end % (settings.fat_copies * settings.root_entries)) / settings.root_entries;
        end_sector = partition_end % settings.root_entries + 1;
    }
    pf_memset(sector_buffer, 0, 0x200);
    master_boot_record = (PFD_SDDRV_MBR*)sector_buffer;
    partition = &master_boot_record->partitions[0];
    partition->boot_indicator = 0;
    partition->start_head = start_head;
    pfd_sddrv_store_le16(sector_buffer, partition->start_sector_cylinder, offsetof(PFD_SDDRV_MBR, partitions) + offsetof(PFD_SDDRV_PARTITION_ENTRY, start_sector_cylinder),
                         ((start_cylinder & 0xff) << 8) + ((start_sector & 0x3f) | ((start_cylinder & 0x300) >> 2)));
    partition->partition_type = partition_type;
    partition->end_head = end_head;
    pfd_sddrv_store_le16(sector_buffer, partition->end_sector_cylinder, offsetof(PFD_SDDRV_MBR, partitions) + offsetof(PFD_SDDRV_PARTITION_ENTRY, end_sector_cylinder),
                         ((end_cylinder & 0xff) << 8) + ((end_sector & 0x3f) | ((end_cylinder & 0x300) >> 2)));
    pfd_sddrv_store_le32(sector_buffer, partition->first_sector, offsetof(PFD_SDDRV_MBR, partitions) + offsetof(PFD_SDDRV_PARTITION_ENTRY, first_sector), format_data->partition_start_sector);
    pfd_sddrv_store_le32(sector_buffer, partition->sector_count, offsetof(PFD_SDDRV_MBR, partitions) + offsetof(PFD_SDDRV_PARTITION_ENTRY, sector_count), format_data->partition_sector_count);
    master_boot_record->signature[0] = 0x55;
    master_boot_record->signature[1] = 0xaa;
    return 0;
}

s32 pfd_sddrv_store_fat32_fsi_buf(u8* sector_buffer) NO_INLINE {
    PFD_SDDRV_FAT32_FSINFO* fs_info;

    pf_memset(sector_buffer, 0, 0x200);
    fs_info = (PFD_SDDRV_FAT32_FSINFO*)sector_buffer;
    if (((u32)fs_info->lead_signature.bytes & 3) != 0) {
        fs_info->lead_signature.bytes[0] = 0x52;
        fs_info->lead_signature.bytes[1] = 0x52;
        fs_info->lead_signature.bytes[2] = 0x61;
        fs_info->lead_signature.bytes[3] = 0x41;
    } else {
        fs_info->lead_signature.value = 0x52526141;
    }
    if (((u32)fs_info->structure_signature.bytes & 3) != 0) {
        fs_info->structure_signature.bytes[0] = 0x72;
        fs_info->structure_signature.bytes[1] = 0x72;
        fs_info->structure_signature.bytes[2] = 0x41;
        fs_info->structure_signature.bytes[3] = 0x61;
    } else {
        fs_info->structure_signature.value = 0x72724161;
    }
    if (((u32)fs_info->free_cluster_count.bytes & 3) != 0) {
        fs_info->free_cluster_count.bytes[0] = 0xff;
        fs_info->free_cluster_count.bytes[1] = 0xff;
        fs_info->free_cluster_count.bytes[2] = 0xff;
        fs_info->free_cluster_count.bytes[3] = 0xff;
    } else {
        fs_info->free_cluster_count.value = 0xffffffff;
    }
    if (((u32)fs_info->next_free_cluster.bytes & 3) != 0) {
        fs_info->next_free_cluster.bytes[0] = 0xff;
        fs_info->next_free_cluster.bytes[1] = 0xff;
        fs_info->next_free_cluster.bytes[2] = 0xff;
        fs_info->next_free_cluster.bytes[3] = 0xff;
    } else {
        fs_info->next_free_cluster.value = 0xffffffff;
    }
    if (((u32)fs_info->signature_word.bytes & 3) != 0) {
        fs_info->signature_word.bytes[0] = 0;
        fs_info->signature_word.bytes[1] = 0;
        fs_info->signature_word.bytes[2] = 0x55;
        fs_info->signature_word.bytes[3] = 0xaa;
    } else {
        fs_info->signature_word.value = 0x55aa;
    }
    return 0;
}

s32 pfd_sddrv_store_fat32_bpb_buf(PFD_SDDRV_FORMAT_DATA* format_data, u8* sector_buffer) {
    PFD_SDDRV_SIZE_SETTINGS settings;
    PFD_SDDRV_FAT32_BPB* boot_sector;
    u32 entry_index;
    u32 requested_sectors;
    const PFD_SDDRV_SIZE_DEPEND* size_entry;
    s32 result;

    if (format_data == 0 || sector_buffer == 0) {
        return -30;
    }
    pf_memset(&settings, 0, 0x10);
    requested_sectors = format_data->total_sectors;
    size_entry = sddrv_size_depend_tbl;
    for (entry_index = 0; entry_index < 14; size_entry++, entry_index++) {
        if (size_entry->min_sectors < requested_sectors && size_entry->max_sectors >= requested_sectors) {
            settings.reserved_sectors = sddrv_size_depend_tbl[entry_index].reserved_sectors;
            settings.fat_copies = sddrv_size_depend_tbl[entry_index].fat_copies;
            settings.root_entries = sddrv_size_depend_tbl[entry_index].root_entries;
            settings.sectors_per_cluster = sddrv_size_depend_tbl[entry_index].sectors_per_cluster;
            break;
        }
    }
    result = entry_index == 14 ? -30 : 0;
    if (result != 0) {
        OSReport("ERR Failed to get values with total sectors. pfd_sddrv_get_value_with_total_sectors()\n");
        return result;
    }
    pf_memset(sector_buffer, 0, 0x200);
    boot_sector = (PFD_SDDRV_FAT32_BPB*)sector_buffer;
    pfd_sddrv_copy_bytes(boot_sector->oem_name, (const u8*)"        ", 8);
    pfd_sddrv_copy_bytes(boot_sector->volume_label, (const u8*)"NO NAME    ", 11);
    pfd_sddrv_copy_bytes(boot_sector->filesystem_type, (const u8*)"FAT32   ", 8);
    boot_sector->jump[0] = 0xeb;
    boot_sector->jump[1] = 0;
    boot_sector->jump[2] = 0x90;
    pfd_sddrv_store_le16(sector_buffer, boot_sector->bytes_per_sector, offsetof(PFD_SDDRV_FAT32_BPB, bytes_per_sector), 0x200);
    boot_sector->sectors_per_cluster = format_data->sectors_per_cluster;
    pfd_sddrv_store_le16(sector_buffer, boot_sector->reserved_sector_count, offsetof(PFD_SDDRV_FAT32_BPB, reserved_sector_count), format_data->reserved_sectors);
    boot_sector->fat_count = 2;
    pfd_sddrv_store_le16(sector_buffer, boot_sector->root_entry_count, offsetof(PFD_SDDRV_FAT32_BPB, root_entry_count), 0);
    pfd_sddrv_store_le16(sector_buffer, boot_sector->total_sectors_16, offsetof(PFD_SDDRV_FAT32_BPB, total_sectors_16), 0);
    boot_sector->media_descriptor = 0xf8;
    pfd_sddrv_store_le16(sector_buffer, boot_sector->sectors_per_fat_16, offsetof(PFD_SDDRV_FAT32_BPB, sectors_per_fat_16), 0);
    pfd_sddrv_store_le16(sector_buffer, boot_sector->sectors_per_track, offsetof(PFD_SDDRV_FAT32_BPB, sectors_per_track), (u16)settings.root_entries);
    pfd_sddrv_store_le16(sector_buffer, boot_sector->heads, offsetof(PFD_SDDRV_FAT32_BPB, heads), (u16)settings.fat_copies);
    pfd_sddrv_store_le32(sector_buffer, boot_sector->hidden_sectors, offsetof(PFD_SDDRV_FAT32_BPB, hidden_sectors), format_data->partition_start_sector);
    pfd_sddrv_store_le32(sector_buffer, boot_sector->total_sectors_32, offsetof(PFD_SDDRV_FAT32_BPB, total_sectors_32), format_data->partition_sector_count);
    pfd_sddrv_store_le32(sector_buffer, boot_sector->sectors_per_fat_32, offsetof(PFD_SDDRV_FAT32_BPB, sectors_per_fat_32), format_data->sectors_per_fat);
    pfd_sddrv_store_le16(sector_buffer, boot_sector->ext_flags, offsetof(PFD_SDDRV_FAT32_BPB, ext_flags), 0);
    pfd_sddrv_store_le16(sector_buffer, boot_sector->filesystem_version, offsetof(PFD_SDDRV_FAT32_BPB, filesystem_version), 0);
    pfd_sddrv_store_le32(sector_buffer, boot_sector->root_cluster, offsetof(PFD_SDDRV_FAT32_BPB, root_cluster), 2);
    pfd_sddrv_store_le16(sector_buffer, boot_sector->fsinfo_sector, offsetof(PFD_SDDRV_FAT32_BPB, fsinfo_sector), 1);
    pfd_sddrv_store_le16(sector_buffer, boot_sector->backup_boot_sector, offsetof(PFD_SDDRV_FAT32_BPB, backup_boot_sector), 6);
    boot_sector->drive_number = 0x80;
    boot_sector->extended_signature = 0x29;
    pfd_sddrv_store_le32(sector_buffer, boot_sector->volume_serial_number, offsetof(PFD_SDDRV_FAT32_BPB, volume_serial_number), format_data->volume_serial_number);
    boot_sector->signature[0] = 0x55;
    boot_sector->signature[1] = 0xaa;
    return 0;
}

static s32 pfd_sddrv_store_fat32_reserved_buf(u8* sector_buffer) {
    PFD_SDDRV_RESERVED_BOOT_SECTOR* reserved_boot_sector;

    pf_memset(sector_buffer, 0, 0x200);
    reserved_boot_sector = (PFD_SDDRV_RESERVED_BOOT_SECTOR*)sector_buffer;
    if (((u32)reserved_boot_sector->signature.bytes & 1) != 0) {
        reserved_boot_sector->signature.bytes[0] = 0x55;
        reserved_boot_sector->signature.bytes[1] = 0xaa;
    } else {
        reserved_boot_sector->signature.value = 0x55aa;
    }
    return 0;
}

static inline s32 pfd_sddrv_write_sector(u32 sector) {
    return ISD_WriteBlock(g_pfd_sddrv_info.device, sector, g_pfd_sddrv_buf, 1);
}

#pragma push
#pragma ppc_iro_level 0
s32 pfd_sddrv_build_fat32_mbr_bpb(u32 total_sectors) {
    PFD_SDDRV_FORMAT_DATA format_data;
    s32 result;
    pf_memset(&format_data, 0, 0x20);
    format_data.total_sectors = total_sectors;
    result = pfd_sddrv_calc_fat32_mbr_bpb(&format_data);
    if (result != 0) {
        OSReport("ERR Failed to calculate MBR and BPB values. pfd_sddrv_calc_fat32_mbr_bpb()\n");
        return result;
    }
    result = pfd_sddrv_store_fat32_bpb_buf(&format_data, g_pfd_sddrv_buf);
    if (result != 0) {
        OSReport("ERR Failed to store BPB values to buf. pfd_sddrv_store_fat32_bpb_buf()\n");
        return result;
    }
    if (g_pfd_sddrv_info.media_inserted == 0) {
        return -33;
    }
    if (g_pfd_sddrv_info.media_ejected != 0) {
        return -33;
    }
    result = pfd_sddrv_write_sector(format_data.partition_start_sector);
    if (result != 0) {
        OSReport("ERR Failed to write BPB fields. ISD_WriteBlock()\n");
        return -36;
    }
    result = pfd_sddrv_write_sector(format_data.partition_start_sector + 6);
    if (result != 0) {
        OSReport("ERR Failed to write BPB fields. ISD_WriteBlock()\n");
        return -36;
    }
    result = pfd_sddrv_store_fat32_fsi_buf(g_pfd_sddrv_buf);
    if (result != 0) {
        OSReport("ERR Failed to store FSInfo values to buf. pfd_sddrv_store_fat32_fsi_buf()\n");
        return result;
    }
    if (g_pfd_sddrv_info.media_inserted == 0) {
        return -33;
    }
    if (g_pfd_sddrv_info.media_ejected != 0) {
        return -33;
    }
    result = pfd_sddrv_write_sector(format_data.partition_start_sector + 1);
    if (result != 0) {
        OSReport("ERR Failed to write BPB fields. ISD_WriteBlock()\n");
        return -36;
    }
    result = pfd_sddrv_write_sector(format_data.partition_start_sector + 7);
    if (result != 0) {
        OSReport("ERR Failed to write BPB fields. ISD_WriteBlock()\n");
        return -36;
    }
    result = pfd_sddrv_store_fat32_reserved_buf(g_pfd_sddrv_buf);
    if (result != 0) {
        OSReport("ERR Failed to store reserved for boot sector values to buf. ");
        OSReport("pfd_sddrv_store_fat32_reserved_buf()\n");
        return result;
    }
    if (g_pfd_sddrv_info.media_inserted == 0) {
        return -33;
    }
    if (g_pfd_sddrv_info.media_ejected != 0) {
        return -33;
    }
    result = pfd_sddrv_write_sector(format_data.partition_start_sector + 2);
    if (result != 0) {
        OSReport("ERR Failed to write BPB fields. ISD_WriteBlock()\n");
        return -36;
    }
    result = pfd_sddrv_write_sector(format_data.partition_start_sector + 8);
    if (result != 0) {
        OSReport("ERR Failed to write BPB fields. ISD_WriteBlock()\n");
        return -36;
    }
    result = pfd_sddrv_store_fat32_mbr_buf(&format_data, g_pfd_sddrv_buf);
    if (result != 0) {
        OSReport("ERR Failed to store MBR values to buf. pfd_sddrv_store_mbr_buf()\n");
        return result;
    }
    if (g_pfd_sddrv_info.media_inserted == 0) {
        return -33;
    }
    if (g_pfd_sddrv_info.media_ejected != 0) {
        return -33;
    }
    result = pfd_sddrv_write_sector(0);
    if (result != 0) {
        OSReport("ERR Failed to write MBR fields. ISD_WriteBlock()\n");
        return -36;
    }
    return 0;
}
#pragma pop

s32 pfd_sddrv_full_format(void) {
    FADiskInfo geometry;
    u32 status;
    u32 retry_count;
    s32 result;

    retry_count = 0;
    do {
        if (g_pfd_sddrv_info.media_inserted == 0) {
            return -33;
        }
        result = ISD_ResetDevice(g_pfd_sddrv_info.device);
        if (result == 0) {
            g_pfd_sddrv_info.media_ejected = 0;
            break;
        }
        OSReport("ERROR Failed to SD Card Reset [ret = 0x%x]. pfd_sddrv_full_format()\n", result);
        retry_count++;
    } while (retry_count < 5);
    if (retry_count == 5) {
        return -38;
    }
    if (g_pfd_sddrv_info.media_ejected != 0) {
        return -33;
    }
    result = ISD_GetDeviceStatus(g_pfd_sddrv_info.device, &status);
    if (result != 0) {
        OSReport("ERR Failed to get sd card status. [ret = 0x%x]\n", result);
        return -39;
    }
    if ((status & 4) != 0) {
        return -32;
    }
    if (g_pfd_sddrv_info.media_ejected != 0) {
        return -33;
    }
    result = pfd_sddrv_get_total_sectors(&geometry.totalSectors, &geometry.bytesPerSector);
    if (result != 0) {
        OSReport("ERR Failed to get total sectors. pfd_sddrv_get_total_sectors()\n");
        return result;
    }
    if ((status & 0x10000) != 0 && (status & 0x100000) == 0) {
        if (geometry.totalSectors > 0x400000) {
            return -34;
        }
        result = pfd_sddrv_build_mbr_bpb(geometry.totalSectors);
    } else if ((status & 0x10000) != 0 && (status & 0x100000) != 0) {
        if (geometry.totalSectors > 0x4000000) {
            return -34;
        }
        result = pfd_sddrv_build_fat32_mbr_bpb(geometry.totalSectors);
    } else {
        return -31;
    }
    if (result != 0) {
        OSReport("ERR Failed to build up and write MBR and BPB fields.\n");
        return result;
    }
    return 0;
}
