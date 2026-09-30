#include <private/vf/PrFILE2/pf_types.h>

typedef struct PFDRV_BPB {
    pf_u16 bytes_per_sector;   // 0x00
    pf_u8 pad_02[0x12];        // 0x02
    pf_u16 fs_info_sector;     // 0x14
    pf_u8 pad_16[0x6];         // 0x16
    pf_s32 fat_type;           // 0x1C
    pf_u8 tail[0x38 - 0x20];   // 0x20
} PFDRV_BPB;

typedef struct PFDRV_VOLUME {
    PFDRV_BPB bpb;                            // 0x00
    pf_u32 num_free_clusters;                 // 0x38
    pf_u32 last_free_cluster;                 // 0x3C
    pf_u8 file_and_dir_state[0x1648 - 0x40];  // 0x40
    pf_s8 label[12];                          // 0x1648
    pf_u8 tail_1654[0x1F84 - 0x1654];         // 0x1654
    pf_s32 last_driver_error;                 // 0x1F84
    pf_u32 reserved_1f88;                     // 0x1F88
    pf_u16 flags;                             // 0x1F8C
    pf_u16 options;                           // 0x1F8E
    pf_u16 fsi_flag;                          // 0x1F90
    pf_u16 cluster_link_flags;                // 0x1F92
    pf_u16 cluster_link_interval;             // 0x1F94
    pf_u32* cluster_link_buffer;              // 0x1F98
    pf_u32 cluster_link_capacity;             // 0x1F9C
    void* driver_partition;                   // 0x1FA0
    pf_u8 gap_1fa4[4];                        // 0x1FA4
    const pf_u8* format_options;              // 0x1FA8
} PFDRV_VOLUME;

typedef struct PFDRV_VOLUME_SET {
    pf_u8 state_prefix[0x40];              // 0x00
    pf_s32 last_error;                     // 0x40
    pf_s32 last_driver_error;              // 0x44
    pf_u8 tail_48[0x88 - 0x48];            // 0x48
    PFDRV_VOLUME volumes[26];              // 0x88
} PFDRV_VOLUME_SET;

extern PFDRV_VOLUME_SET pf_vol_set;

typedef struct PFDRV_CACHE_PAGE {
    pf_u16 stat;
    pf_u16 option;
    pf_u8* buffer;
    pf_u8* p_buf;
    pf_u8* p_mod_sbuf;
    pf_u8* p_mod_ebuf;
    pf_u32 size;
    pf_u32 sector;
    void* signature;
    struct PFDRV_CACHE_PAGE* p_next;
    struct PFDRV_CACHE_PAGE* p_prev;
} PFDRV_CACHE_PAGE;

typedef struct PFDRV_PART_FUNC {
    void (*insert)(void* partition);
    void (*eject)(void* partition);
} PFDRV_PART_FUNC;

typedef struct PFDRV_MEDIA_INFO {
    pf_u32 total_sectors;       // 0x00
    pf_u16 cylinders;           // 0x04
    pf_u8 heads;                // 0x06
    pf_u8 sectors_per_track;    // 0x07
    pf_u16 bytes_per_sector;    // 0x08
    pf_u16 reserved_0a;         // 0x0A
    pf_u32 media_attr;          // 0x0C
    const pf_u8* format_param;  // 0x10
} PFDRV_MEDIA_INFO;

typedef struct PFDRV_VOLUME_INFO {
    pf_s8 label[12];  // 0x00
    pf_u8 tail[8];    // 0x0C
} PFDRV_VOLUME_INFO;

enum {
    FAT_32 = 2
};

extern void* pf_memcpy(void* dst, const void* src, pf_u32 length);

extern pf_s32 PFCACHE_AllocateDataPage(PFDRV_VOLUME* volume, pf_u32 sector, PFDRV_CACHE_PAGE** p_page, pf_u32* option);
extern void PFCACHE_FreeDataPage(PFDRV_VOLUME* volume, PFDRV_CACHE_PAGE* p_page);

extern pf_s32 pdm_part_logical_read(void* partition, pf_u8* buffer, pf_u32 sector, pf_u32 num_sector, pf_u16 bps,
                                    pf_u32* p_num_success);
extern pf_s32 pdm_part_logical_write(void* partition, const pf_u8* buffer, pf_u32 sector, pf_u32 num_sector, pf_u16 bps,
                                     pf_u32* p_num_success);
extern pf_s32 pdm_part_register_callback(void* partition, const PFDRV_PART_FUNC* func);
extern pf_s32 pdm_part_unregister_callback(void* partition);
extern pf_s32 pdm_part_init(void* partition);
extern pf_s32 pdm_part_finalize(void* partition);
extern pf_s32 pdm_part_mount(void* partition);
extern pf_s32 pdm_part_unmount(void* partition, pf_u32 mode);
extern pf_s32 pdm_part_get_media_attribute(void* partition, PFDRV_MEDIA_INFO* info);
extern pf_s32 pdm_part_get_driver_error_code(void* partition);
extern pf_s32 pdm_part_format(void* partition, const pf_u8* format_param);
extern pf_s32 pdm_bpb_InitVolumeWithBootSector(PFDRV_VOLUME* volume, const pf_u8* buf);
extern pf_s32 pdm_bpb_InitVolumeWithFSINFOSector(PFDRV_VOLUME* volume, const pf_u8* buf, pf_u32* p_num_free_clusters,
                                               pf_u32* p_last_free_cluster);

void PFDRV_LoadVolumeLabelFromBuf(PFDRV_VOLUME* volume, const pf_u8* buf) {
    pf_memcpy(volume->label, buf, 0xB);
    volume->label[0xB] = 0;
}

void PFDRV_StoreVolumeLabelToBuf(PFDRV_VOLUME_INFO* volume_info, PFDRV_VOLUME* volume) {
    pf_memcpy(volume_info->label, volume->label, 0xB);
    volume_info->label[0xB] = 0;
}

pf_s32 PFDRV_StoreVolumeLabelToBPB(PFDRV_VOLUME* volume, const pf_s8* label) {
    PFDRV_CACHE_PAGE* p_page;
    pf_u32 option;
    pf_u32 num_sector;
    pf_s32 err;
    pf_s32 result;

    err = PFCACHE_AllocateDataPage(volume, -1, &p_page, &option);
    if (err != 0) {
        return err;
    }

    err = pdm_part_logical_read(volume->driver_partition, p_page->p_buf, 0, 1, volume->bpb.bytes_per_sector, &num_sector);
    if (err != 0) {
        if (err == 0x15) {
            result = pdm_part_get_driver_error_code(volume->driver_partition);
            pf_vol_set.last_driver_error = result;
            volume->last_driver_error = result;
            result = 0x1000;
        } else {
            result = -1;
        }
    } else {
        result = 0;
    }
    if (result != 0) {
        PFCACHE_FreeDataPage(volume, p_page);
        return result;
    }

    if (num_sector != 1) {
        PFCACHE_FreeDataPage(volume, p_page);
        return 0x11;
    }

    if (volume->bpb.fat_type == FAT_32) {
        pf_memcpy(p_page->p_buf + 0x47, label, 0xB);
    } else {
        pf_memcpy(p_page->p_buf + 0x2B, label, 0xB);
    }

    err = pdm_part_logical_write(volume->driver_partition, p_page->p_buf, 0, 1, volume->bpb.bytes_per_sector,
                                 &num_sector);
    if (err != 0) {
        if (err == 0x15) {
            result = pdm_part_get_driver_error_code(volume->driver_partition);
            pf_vol_set.last_driver_error = result;
            volume->last_driver_error = result;
            result = 0x1000;
        } else {
            result = -1;
        }
    } else {
        result = 0;
    }
    PFCACHE_FreeDataPage(volume, p_page);
    if (result != 0) {
        return result;
    }

    if (num_sector != 1) {
        return 0x11;
    }

    pf_memcpy(volume->label, label, 0xB);
    volume->label[0xB] = 0;
    return 0;
}

void PFDRV_MediaEject(void* partition) {
    PFDRV_VOLUME* p_vol;
    pf_u32 i;

    p_vol = pf_vol_set.volumes;
    for (i = 0; i < 26; p_vol++, i++) {
        if (p_vol->driver_partition == partition) {
            if ((p_vol->flags & 0x08) != 0) {
                p_vol->flags |= 0x20;
            }
            p_vol->flags &= ~0x0C;
        }
    }
}

void PFDRV_MediaInsert(void* partition) {
    PFDRV_VOLUME* p_vol;
    pf_u32 i;

    p_vol = pf_vol_set.volumes;
    for (i = 0; i < 26; p_vol++, i++) {
        if (p_vol->driver_partition == partition) {
            p_vol->flags |= 0x14;
        }
    }
}

pf_s32 PFDRV_IsInserted(PFDRV_VOLUME* volume) {
    return (volume->flags >> 2) & 1;
}

pf_s32 PFDRV_IsMountRequested(PFDRV_VOLUME* volume) {
    return (volume->flags >> 4) & 1;
}

void PFDRV_ClearMountRequested(PFDRV_VOLUME* volume) {
    volume->flags &= ~0x10;
}

pf_s32 PFDRV_IsUnmountRequested(PFDRV_VOLUME* volume) {
    return (volume->flags >> 5) & 1;
}

void PFDRV_ClearUnmountRequested(PFDRV_VOLUME* volume) {
    volume->flags &= ~0x20;
}

pf_s32 PFDRV_init(PFDRV_VOLUME* volume) {
    PFDRV_PART_FUNC func;
    pf_s32 err;

    func.insert = PFDRV_MediaInsert;
    func.eject = PFDRV_MediaEject;

    err = pdm_part_register_callback(volume->driver_partition, &func);
    if (err != 0) {
        return -1;
    }

    err = pdm_part_init(volume->driver_partition);
    if (err != 0) {
        pdm_part_unregister_callback(volume->driver_partition);
        if (err == 0x15) {
            err = pdm_part_get_driver_error_code(volume->driver_partition);
            pf_vol_set.last_driver_error = err;
            volume->last_driver_error = err;
            return 0x1000;
        }
        return -1;
    }

    return 0;
}

pf_s32 PFDRV_finalize(PFDRV_VOLUME* volume) {
    pf_s32 err;

    err = pdm_part_unregister_callback(volume->driver_partition);
    if (err != 0) {
        return -1;
    }

    err = pdm_part_finalize(volume->driver_partition);
    if (err != 0) {
        if (err == 0x15) {
            err = pdm_part_get_driver_error_code(volume->driver_partition);
            pf_vol_set.last_driver_error = err;
            volume->last_driver_error = err;
            return 0x1000;
        }
        return -1;
    }

    return 0;
}

pf_s32 PFDRV_mount(PFDRV_VOLUME* volume) {
    PFDRV_MEDIA_INFO info;
    pf_u32 option;
    PFDRV_CACHE_PAGE* p_page;
    pf_u32 num_sector;
    pf_s32 err;

    err = pdm_part_mount(volume->driver_partition);
    if (err != 0) {
        if (err == 0x15) {
            err = pdm_part_get_driver_error_code(volume->driver_partition);
            pf_vol_set.last_driver_error = err;
            volume->last_driver_error = err;
            return 0x1000;
        }
        return -1;
    }

    err = pdm_part_get_media_attribute(volume->driver_partition, &info);
    if (err != 0) {
        pdm_part_unmount(volume->driver_partition, 0);
        return -1;
    }

    if ((info.media_attr & 0x01) != 0) {
        volume->flags |= 0x02;
    } else {
        volume->flags &= ~0x02;
    }
    if ((info.media_attr & 0x02) != 0) {
        const pf_u8* format_param = info.format_param;
        volume->flags |= 0x40;
        volume->format_options = format_param;
    }
    if ((info.media_attr & 0x08) != 0) {
        volume->flags |= 0x80;
    }

    PFCACHE_AllocateDataPage(volume, -1, &p_page, &option);

    err = pdm_part_logical_read(volume->driver_partition, p_page->buffer, 0, 1, 0x200, &num_sector);
    if (err != 0) {
        if (err == 0x15) {
            err = pdm_part_get_driver_error_code(volume->driver_partition);
            pf_vol_set.last_driver_error = err;
            volume->last_driver_error = err;
            err = 0x1000;
        } else {
            err = -1;
        }
        PFCACHE_FreeDataPage(volume, p_page);
        pdm_part_unmount(volume->driver_partition, 0);
        return err;
    }

    err = pdm_bpb_InitVolumeWithBootSector(volume, p_page->buffer);
    if (err != 0) {
        PFCACHE_FreeDataPage(volume, p_page);
        pdm_part_unmount(volume->driver_partition, 0);
        return 7;
    }

    volume->num_free_clusters = -1;
    volume->last_free_cluster = -1;

    if (volume->bpb.fat_type == FAT_32) {
        err = pdm_part_logical_read(volume->driver_partition, p_page->buffer, volume->bpb.fs_info_sector, 1, 0x200,
                                    &num_sector);
        if (err != 0) {
            if (err == 0x15) {
                err = pdm_part_get_driver_error_code(volume->driver_partition);
                pf_vol_set.last_driver_error = err;
                volume->last_driver_error = err;
                err = 0x1000;
            } else {
                err = -1;
            }
            PFCACHE_FreeDataPage(volume, p_page);
            pdm_part_unmount(volume->driver_partition, 0);
            return err;
        }

        err = pdm_bpb_InitVolumeWithFSINFOSector(volume, p_page->buffer, &volume->num_free_clusters,
                                               &volume->last_free_cluster);
        if (err != 0) {
            PFCACHE_FreeDataPage(volume, p_page);
            pdm_part_unmount(volume->driver_partition, 0);
            return -1;
        }
    }

    PFCACHE_FreeDataPage(volume, p_page);
    return 0;
}

pf_s32 PFDRV_unmount(PFDRV_VOLUME* volume, pf_u32 mode) {
    pf_s32 err;

    err = pdm_part_unmount(volume->driver_partition, mode == 1);
    if (err != 0) {
        if (err == 0x15) {
            err = pdm_part_get_driver_error_code(volume->driver_partition);
            pf_vol_set.last_driver_error = err;
            volume->last_driver_error = err;
            return 0x1000;
        }
        return -1;
    }

    return 0;
}

pf_s32 PFDRV_format(PFDRV_VOLUME* volume, const pf_u8* format_options) {
    pf_s32 err;

    err = pdm_part_format(volume->driver_partition, format_options);
    if (err != 0) {
        if (err == 0x15) {
            err = pdm_part_get_driver_error_code(volume->driver_partition);
            pf_vol_set.last_driver_error = err;
            volume->last_driver_error = err;
            return 0x1000;
        }
        return -1;
    }

    return 0;
}

pf_s32 PFDRV_lread(PFDRV_VOLUME* volume, pf_u8* buffer, pf_u32 sector, pf_u32 num_sector, pf_u32* p_num_success) {
    pf_s32 err;

    err = pdm_part_logical_read(volume->driver_partition, buffer, sector, num_sector, volume->bpb.bytes_per_sector,
                                p_num_success);
    if (err != 0) {
        if (err == 0x15) {
            err = pdm_part_get_driver_error_code(volume->driver_partition);
            pf_vol_set.last_driver_error = err;
            volume->last_driver_error = err;
            return 0x1000;
        }
        return -1;
    }

    return 0;
}

pf_s32 PFDRV_lwrite(PFDRV_VOLUME* volume, const pf_u8* buffer, pf_u32 sector, pf_u32 num_sector, pf_u32* p_num_success) {
    pf_s32 err;

    err = pdm_part_logical_write(volume->driver_partition, buffer, sector, num_sector, volume->bpb.bytes_per_sector,
                                 p_num_success);
    if (err != 0) {
        if (err == 0x15) {
            err = pdm_part_get_driver_error_code(volume->driver_partition);
            pf_vol_set.last_driver_error = err;
            volume->last_driver_error = err;
            return 0x1000;
        }
        return -1;
    }

    return 0;
}
