#include <revolution/types.h>

typedef struct PFVOL_VOLUME PFVOL_VOLUME;

typedef struct PFVOL_BPB {
    u16 bytes_per_sector;
    u16 num_reserved_sectors;
    u16 num_root_dir_entries;
    u8 sectors_per_cluster;
    u8 num_FATs;
    u32 total_sectors;
    u32 sectors_per_FAT;
    u32 root_dir_cluster;
    u16 fs_info_sector;
    u16 backup_boot_sector;
    u16 ext_flags;
    u8 media;
    u8 pad_1b;
    s32 fat_type;
    u8 log2_bytes_per_sector;
    u8 log2_sectors_per_cluster;
    u8 num_active_FATs;
    u8 pad_23;
    u16 num_root_dir_sectors;
    u16 pad_26;
    u32 active_FAT_sector;
    u32 first_root_dir_sector;
    u32 first_data_sector;
    u32 num_clusters;
} PFVOL_BPB;

typedef struct PFVOL_DIR_ENTRY {
    u16 long_name[261];
    u8 num_entry_LFNs;
    u8 ordinal;
    u8 check_sum;
    u8 pad_20d;
    s8 short_name[13];
    u8 small_letter_flag;
    u8 attr;
    u8 create_time_ms;
    u16 create_time;
    u16 create_date;
    u16 access_date;
    u16 modify_time;
    u16 modify_date;
    u32 file_size;
    PFVOL_VOLUME* volume;
    u32 path_len;
    u32 start_cluster;
    u32 entry_sector;
    u16 entry_offset;
} PFVOL_DIR_ENTRY;

typedef struct PFVOL_FAT_HINT {
    u32 chain_index;
    u32 cluster;
    u32 previous_cluster;
    u32 reserved;
} PFVOL_FAT_HINT;

typedef struct PFVOL_LAST_CLUSTER {
    u32 num_last_cluster;
    u32 max_chain_index;
} PFVOL_LAST_CLUSTER;

typedef struct PFVOL_FAT_LAST_ACCESS {
    u32 chain_index;
    u32 cluster;
} PFVOL_FAT_LAST_ACCESS;

typedef struct PFVOL_CLUSTER_LINK {
    u32* buffer;
    u16 interval;
    u16 interval_offset;
    u32 position;
    u32 max_count;
    u32 save_index;
} PFVOL_CLUSTER_LINK;

typedef struct PFVOL_FFD {
    u32 start_cluster;
    u32 flags;
    u32* p_start_cluster;
    PFVOL_LAST_CLUSTER last_cluster;
    PFVOL_FAT_LAST_ACCESS last_access;
    PFVOL_CLUSTER_LINK cluster_link;
    PFVOL_FAT_HINT* hint;
    PFVOL_VOLUME* volume;
} PFVOL_FFD;

typedef struct PFVOL_STR {
    const char* head;
    const char* tail;
    const char* current;
    u32 code_mode;
} PFVOL_STR;

typedef struct PFVOL_CURRENT_DIR {
    u32 stat;
    s32 context_id;
    PFVOL_DIR_ENTRY directory;
} PFVOL_CURRENT_DIR;

typedef struct PFVOL_CURRENT_VOLUME {
    u32 stat;
    s32 context_id;
    PFVOL_VOLUME* volume;
} PFVOL_CURRENT_VOLUME;

typedef struct PFVOL_CONTEXT {
    u32 stat;
    s32 context_id;
} PFVOL_CONTEXT;

typedef struct PFVOL_VOLUME_INFO {
    s8 label[12];
    u8 attr;
    u8 reserved_0d[3];
    u32 time;
    u32 date;
} PFVOL_VOLUME_INFO;

typedef struct PFVOL_CHARCODE {
    s32 (*oem2unicode)(const s8*, u16*);
    s32 (*unicode2oem)(const u16*, s8*);
    s32 (*oem_char_width)(const s8*);
    s32 (*is_oem_mb_char)(s8, s32);
    s32 (*unicode_char_width)(const u16*);
    s32 (*is_unicode_mb_char)(u16, s32);
} PFVOL_CHARCODE;

typedef struct PFVOL_CACHE_SETTING {
    void* pages;
    void* buffers;
    u16 num_fat_pages;
    u16 num_data_pages;
    u32 num_fat_buf_size;
    u32 num_data_buf_size;
} PFVOL_CACHE_SETTING;

typedef struct PFVOL_DRIVER {
    void* partition;
    PFVOL_CACHE_SETTING* cache;
    s8 drive;
    u8 stat;
    u8 pad_0a[2];
} PFVOL_DRIVER;

typedef struct PFVOL_OPEN_SFD {
    u8 gap_0000[0x3C];
    PFVOL_DIR_ENTRY directory_entry;
} PFVOL_OPEN_SFD;

typedef struct PFVOL_OPEN_FILE {
    u32 stat;
    u32 reserved;
    PFVOL_OPEN_SFD* stream;
    u8 gap_000C[0x24];
} PFVOL_OPEN_FILE;

typedef struct PFVOL_CLUSTER_SETTING {
    u32* buffer;
    u32 max_count;
    u16 interval;
    u16 reserved;
} PFVOL_CLUSTER_SETTING;

struct PFVOL_VOLUME {
    PFVOL_BPB bpb;
    u32 num_free_clusters;
    u8 gap_003C[0xD10];
    PFVOL_OPEN_FILE files[5];
    u8 gap_0E3C[0x7E0];
    u32 num_open_files;
    u32 num_open_dirs;
    u32 cache_flags;
    u16 num_fat_pages;
    u16 num_data_pages;
    u8 gap_162C[0x10];
    u32 num_fat_buf_size;
    u32 num_data_buf_size;
    u8 gap_1644[4];
    s8 label[12];
    PFVOL_CURRENT_DIR current_dir[4];
    u32 file_buffer_count;
    void* file_buffers;
    void* current_file_buffer;
    u32 last_error;
    u32 last_driver_error;
    u32 reserved_1f88;
    u16 flags;
    u16 options;
    u16 fsi_flag;
    u16 cluster_link_flags;
    u16 cluster_link_interval;
    u32* cluster_link_buffer;
    u32 cluster_link_capacity;
    void* driver_partition;
    u8 gap_1fa4[4];
    const u8* format_options;
};

typedef struct PFVOL_SET {
    u32 flags;
    u32 reserved_004;
    PFVOL_VOLUME* current_volume;
    PFVOL_CURRENT_VOLUME context_volume[3];
    s32 num_attached_drives;
    s32 num_mounted_volumes;
    u32 config;
    void* user_data;
    s32 last_error;
    s32 last_driver_error;
    PFVOL_CHARCODE codeset;
    u32 setting;
    u8 gap_0064[0x0C];
    PFVOL_CONTEXT context[3];
    PFVOL_VOLUME volumes[26];
} PFVOL_SET;

PFVOL_SET pf_vol_set;

extern s32 PFDRV_mount(PFVOL_VOLUME* volume);
extern s32 PFDRV_unmount(PFVOL_VOLUME* volume, u32 mode);
extern s32 PFDRV_format(PFVOL_VOLUME* volume, const u8* format_options);
extern s32 PFDRV_IsInserted(PFVOL_VOLUME* volume);
extern s32 PFDRV_IsUnmountRequested(PFVOL_VOLUME* volume);
extern s32 PFDRV_IsMountRequested(PFVOL_VOLUME* volume);
extern void PFDRV_ClearMountRequested(PFVOL_VOLUME* volume);
extern void PFDRV_ClearUnmountRequested(PFVOL_VOLUME* volume);
extern s32 PFCACHE_InitCaches(PFVOL_VOLUME* volume);
extern s32 PFCACHE_FlushAllCaches(PFVOL_VOLUME* volume);
extern void PFCACHE_FreeAllCaches(PFVOL_VOLUME* volume);
extern s32 PFENT_GetRootDir(PFVOL_VOLUME* volume, PFVOL_DIR_ENTRY* entry);
extern s32 PFENT_MakeRootDir(PFVOL_VOLUME* volume);
extern s32 PFFAT_InitFATRegion(PFVOL_VOLUME* volume);
extern s32 PFSYS_GetCurrentContextID(s32* context_id);
extern void PFFILE_FinalizeAllFiles(PFVOL_VOLUME* volume);
extern void PFDIR_FinalizeAllDirs(PFVOL_VOLUME* volume);
extern s32 PFFAT_RefreshFSINFO(PFVOL_VOLUME* volume);
extern s32 PFFAT_CountFreeClusters(PFVOL_VOLUME* volume, u32* free_clusters);
extern s32 PFFAT_InitFFD(PFVOL_FFD* ffd, PFVOL_FAT_HINT* hint, PFVOL_VOLUME* volume, u32* start_cluster);
extern s32 PFSTR_InitStr(PFVOL_STR* path, const char* text, u32 code_mode);
extern void PFSTR_SetLocalStr(PFVOL_STR* path, const char* path_component);
extern s32 PFSTR_StrLen(const s8* text);
extern s32 PFSTR_ToUpperNStr(const s8* text, u32 max_len, s8* out);
extern s32 PFENT_findEntryPos(PFVOL_FFD* ffd, PFVOL_DIR_ENTRY* entry, u32 start, PFVOL_STR* path,
                              u8 attr_required, u32 skip, u32* logical_position, u32* entry_position);
extern s32 PFENT_allocateEntry(PFVOL_DIR_ENTRY* entry, u8 num_entries, PFVOL_FFD* ffd, u32* prev_cluster,
                               PFVOL_STR* path);
extern u8 PFENT_getcurrentDateTimeForEnt(u16* date, u16* time);
extern s32 PFENT_updateEntry(PFVOL_DIR_ENTRY* entry, u32 clear_archive);
extern void* pf_memcpy(void* dst, const void* src, u32 size);
extern s8* pf_strcpy(s8* dst, const s8* src);
extern s32 PFDRV_StoreVolumeLabelToBuf(PFVOL_VOLUME_INFO* volume_info, PFVOL_VOLUME* volume);
extern s32 PFDRV_StoreVolumeLabelToBPB(PFVOL_VOLUME* volume, const s8* label);
extern s32 PFSEC_WriteData(PFVOL_VOLUME* volume, const void* buffer, u32 sector, u16 offset, u32 count,
                           u32* processed, u32 flags);
extern s32 PFCACHE_FlushFATCache(PFVOL_VOLUME* volume);
extern s32 PFCACHE_FlushDataCacheSpecific(PFVOL_VOLUME* volume, u32 sector);
extern s32 PFCACHE_FlushDataCache(PFVOL_VOLUME* volume);
extern s32 PFCACHE_SetWriteBackMode(PFVOL_VOLUME* volume);
extern s32 PFCACHE_SetWriteThroughMode(PFVOL_VOLUME* volume);
extern s32 PFCACHE_SetCache(PFVOL_VOLUME* volume, void* pages, void* buffers, u16 num_fat_pages,
                            u16 num_data_pages);
extern s32 PFCACHE_SetFATBufferSize(PFVOL_VOLUME* volume, u32 size);
extern s32 PFCACHE_SetDataBufferSize(PFVOL_VOLUME* volume, u32 size);
extern s32 PFDRV_init(PFVOL_VOLUME* volume);
extern s32 PFDRV_finalize(PFVOL_VOLUME* volume);
extern s32 fa_nanddrv_NotifyNANDFile(s32 command, void* callback_data);
extern s32 PFVOL_DoMountVolume(PFVOL_VOLUME* volume);
extern s32 PFVOL_p_unmount(PFVOL_VOLUME* volume, u32 mode);
extern s32 PFVOL_p_format(PFVOL_VOLUME* volume, const u8* format_options);
extern s32 PFVOL_p_setvol(PFVOL_VOLUME* volume, const s8* label);
extern s32 PFVOL_p_getvol(PFVOL_VOLUME* volume, PFVOL_VOLUME_INFO* volume_info);
extern s32 PFVOL_p_rmvvol(PFVOL_VOLUME* volume);
extern s16 pf_toupper(s32 value);
extern void PF_InitLockFile(void);
extern s32 PFCODE_CP932_OEM2Unicode(const s8* source, u16* destination);
extern s32 PFCODE_CP932_Unicode2OEM(const u16* source, s8* destination);
extern s32 PFCODE_CP932_OEMCharWidth(const s8* source);
extern s32 PFCODE_CP932_isOEMMBchar(s8 value, s32 mode);
extern s32 PFCODE_CP932_UnicodeCharWidth(const u16* source);
extern s32 PFCODE_CP932_isUnicodeMBchar(u16 value, s32 mode);
extern void* pf_memset(void* dst, int value, u32 size);
extern s32 pf_memcmp(const void* left, const void* right, u32 size);

s32 PFVOL_DoMountVolume(PFVOL_VOLUME* volume) {
    s32 error;
    s32 context_id;
    u32 i;
    u32 context_registered;

    volume->last_error = 0;
    volume->last_driver_error = 0;
    error = PFDRV_mount(volume);
    if (error != 0) {
        return error;
    }
    if (volume->bpb.bytes_per_sector == 0 || (volume->bpb.bytes_per_sector & 0x01FF) != 0) {
        return 15;
    }
    if ((volume->bpb.bytes_per_sector >> 9) > volume->num_fat_pages ||
        ((volume->bpb.bytes_per_sector >> 9) << 1) > volume->num_data_pages) {
        return 30;
    }
    error = PFCACHE_InitCaches(volume);
    if (error != 0) {
        return error;
    }
    volume->flags |= 8;
    if ((volume->flags & 8) == 0) {
        return 9;
    }
    error = PFSYS_GetCurrentContextID(&context_id);
    volume->current_dir[0].stat |= 1;
    context_registered = 0;
    for (i = 0; i < 3; i++) {
        pf_vol_set.context[i].stat &= 1;
        if (pf_vol_set.context[i].stat != 0 && pf_vol_set.context[i].context_id == context_id) {
            context_registered = 1;
            break;
        }
    }
    if (context_registered != 0) {
        volume->current_dir[0].stat |= 1;
        volume->current_dir[0].context_id = context_id;
    }
    for (i = 0; i < 4; i++) {
        error = PFENT_GetRootDir(volume, &volume->current_dir[i].directory);
        if (error != 0) {
            break;
        }
    }
    if (error == 0 && (volume->flags & 0x40) != 0) {
        error = PFDRV_format(volume, volume->format_options);
        if (error == 0 && (volume->flags & 0x80) == 0) {
            error = PFFAT_InitFATRegion(volume);
            if (error == 0) {
                error = PFENT_MakeRootDir(volume);
            }
        }
    }
    if (error != 0) {
        volume->flags &= ~8;
    }
    return error;
}

s32 PFVOL_p_unmount(PFVOL_VOLUME* volume, u32 mode) {
    s32 error;
    s32 prior_error = 0;

    if ((volume->flags & 8) == 0) {
        return 9;
    }
    PFFILE_FinalizeAllFiles(volume);
    PFDIR_FinalizeAllDirs(volume);
    error = PFCACHE_FlushAllCaches(volume);
    if (error != 0) {
        prior_error = error;
    }
    if (error == 0 || (mode & 1) != 0) {
        PFCACHE_FreeAllCaches(volume);
        error = PFDRV_unmount(volume, mode);
        if (error != 0) {
            goto unmount_done;
        }
        if ((volume->flags & 8) != 0) {
            volume->current_dir[0].stat = 0;
            volume->current_dir[1].stat = 0;
            volume->current_dir[2].stat = 0;
            volume->current_dir[3].stat = 0;
        }
        error = 0;
        volume->flags &= ~8;
unmount_done:
        if (error != 0 && prior_error == 0) {
            prior_error = error;
        }
    }
    if (prior_error == 0 || (mode & 1) != 0) {
        PFDRV_ClearMountRequested(volume);
        PFDRV_ClearUnmountRequested(volume);
        pf_vol_set.num_mounted_volumes--;
    }
    return prior_error;
}

s32 PFVOL_p_format(PFVOL_VOLUME* volume, const u8* format_options) {
    s32 error;
    u32 free_clusters;

    if (volume == 0) {
        return 10;
    }
    if ((volume->flags & 2) != 0) {
        return 11;
    }
    error = PFDRV_format(volume, format_options);
    if (error != 0) {
        return error;
    }
    if ((volume->flags & 8) != 0) {
        PFCACHE_FreeAllCaches(volume);
        error = PFVOL_p_unmount(volume, 0);
        if (error != 0) {
            return error;
        }
    }
    if ((volume->flags & 8) == 0) {
        error = PFVOL_DoMountVolume(volume);
        if (error != 0) {
            goto mount_done;
        }
        volume->fsi_flag &= ~7;
        PFDRV_ClearUnmountRequested(volume);
        pf_vol_set.num_mounted_volumes++;
    }
    PFDRV_ClearMountRequested(volume);
    error = 0;
mount_done:
    if (error == 0) {
        if ((volume->flags & 2) != 0) {
            error = 11;
        } else if ((volume->flags & 0x80) == 0) {
            error = PFFAT_InitFATRegion(volume);
            if (error == 0) {
                error = PFENT_MakeRootDir(volume);
                if (error == 0) {
                    if (volume->bpb.fat_type != 2) {
                        volume->fsi_flag &= ~3;
                    }
                    if ((volume->bpb.fat_type != 2 || (volume->fsi_flag & 2) == 0) ||
                        (error = PFFAT_RefreshFSINFO(volume)) == 0) {
                        error = 0;
                    }
                }
            }
        } else {
            if (volume->bpb.fat_type == 2 && (volume->fsi_flag & 2) != 0) {
                volume->fsi_flag |= 4;
                PFFAT_RefreshFSINFO(volume);
            } else {
                volume->fsi_flag &= ~4;
                if (volume->bpb.fat_type != 2) {
                    volume->fsi_flag &= ~7;
                }
                error = PFFAT_CountFreeClusters(volume, &free_clusters);
                if (error != 0) {
                    return error;
                }
            }
            error = 0;
        }
    }
    return error;
}

s32 PFVOL_p_setvol(PFVOL_VOLUME* volume, const s8* label) {
    PFVOL_FFD ffd;
    PFVOL_FAT_HINT hint;
    PFVOL_STR path;
    PFVOL_DIR_ENTRY root_entry;
    PFVOL_DIR_ENTRY entry;
    u32 logical_position;
    u32 entry_position;
    u32 previous_cluster[2];
    s32 error;

    error = PFENT_GetRootDir(volume, &root_entry);
    if (error == 0) {
        PFFAT_InitFFD(&ffd, &hint, volume, &root_entry.start_cluster);
        PFSTR_InitStr(&path, "*", 1);
        PFSTR_SetLocalStr(&path, 0);
        error = PFENT_findEntryPos(&ffd, &entry, 0, &path, 8, 0, &logical_position, &entry_position);
        if (error != 0 && error != 3) {
            return error;
        }
        {
            if (entry_position != 999999) {
                if (entry.start_cluster == 1) {
                    entry.start_cluster = 0;
                }
            } else {
                PFSTR_InitStr(&path, "", 1);
                PFSTR_SetLocalStr(&path, 0);
                error = PFENT_allocateEntry(&entry, 1, &ffd, previous_cluster, &path);
                if (error != 0) {
                    return error;
                }
                entry.long_name[0] = 0;
                entry.start_cluster = 0;
                entry.file_size = 0;
                entry.volume = volume;
                entry.small_letter_flag = 0;
                entry.attr = 8;
                entry.path_len = 3;
                entry.create_date = 0;
                entry.create_time = 0;
                entry.access_date = 0;
                entry.create_time_ms = 0;
            }
            pf_memcpy(entry.short_name, label, 12);
            PFENT_getcurrentDateTimeForEnt(&entry.modify_date, &entry.modify_time);
            error = PFENT_updateEntry(&entry, 0);
        }
    } else {
        return error;
    }
    return error;
}

s32 PFVOL_p_getvol(PFVOL_VOLUME* volume, PFVOL_VOLUME_INFO* volume_info) {
    PFVOL_FFD ffd;
    PFVOL_FAT_HINT hint;
    PFVOL_STR path;
    PFVOL_DIR_ENTRY root_entry;
    PFVOL_DIR_ENTRY entry;
    u32 logical_position;
    u32 entry_position;
    s32 error;

    error = PFENT_GetRootDir(volume, &root_entry);
    if (error != 0) {
        return error;
    }
    PFFAT_InitFFD(&ffd, &hint, volume, &root_entry.start_cluster);
    PFSTR_InitStr(&path, "*", 1);
    PFSTR_SetLocalStr(&path, "*");
    error = PFENT_findEntryPos(&ffd, &entry, 0, &path, 8, 0, &logical_position, &entry_position);
    if (error != 0 && error != 3) {
        return error;
    }
    if (entry_position != 999999) {
        volume_info->time = entry.modify_date;
        volume_info->date = entry.modify_time;
        volume_info->attr = entry.attr;
        pf_strcpy(volume_info->label, entry.short_name);
    } else {
        volume_info->time = 0;
        volume_info->date = 0;
        volume_info->attr = 8;
        PFDRV_StoreVolumeLabelToBuf(volume_info, volume);
    }
    return 0;
}

s32 PFVOL_p_rmvvol(PFVOL_VOLUME* volume) {
    PFVOL_FFD ffd;
    PFVOL_FAT_HINT hint;
    PFVOL_STR path;
    PFVOL_DIR_ENTRY root_entry;
    PFVOL_DIR_ENTRY entry;
    u32 logical_position;
    u32 entry_position;
    u32 processed;
    u8 deleted = 0xE5;
    s32 error;

    error = PFENT_GetRootDir(volume, &root_entry);
    if (error != 0) {
        return error;
    }
    PFFAT_InitFFD(&ffd, &hint, volume, &root_entry.start_cluster);
    PFSTR_InitStr(&path, "*", 1);
    PFSTR_SetLocalStr(&path, "*");
    error = PFENT_findEntryPos(&ffd, &entry, 0, &path, 8, 0, &logical_position, &entry_position);
    if (error != 0 && error != 3) {
        return error;
    }
    if (entry_position != 999999) {
        error = PFSEC_WriteData(volume, &deleted, entry.entry_sector, entry.entry_offset, 1, &processed, 0);
        if (error != 0) {
            return error;
        }
        if (processed != 1) {
            return 17;
        }
    }
    return 0;
}

s32 PFVOL_InitModule(u32 config, void* user_data) {
    s32 i;

    if ((config & 0x10000) != 0) {
        pf_vol_set.config |= 0x10000;
    } else {
        pf_vol_set.config &= ~0x10000;
    }
    pf_vol_set.current_volume = &pf_vol_set.volumes[0];
    pf_vol_set.context_volume[0].volume = &pf_vol_set.volumes[0];
    pf_vol_set.context_volume[1].volume = &pf_vol_set.volumes[0];
    pf_vol_set.context_volume[2].volume = &pf_vol_set.volumes[0];
    pf_vol_set.flags |= 1;
    pf_vol_set.num_attached_drives = 0;
    pf_vol_set.num_mounted_volumes = 0;
    if ((config & 0x10000) != 0) {
        pf_vol_set.config |= 0x10000;
    } else {
        pf_vol_set.config &= ~0x10000;
    }
    pf_vol_set.user_data = user_data;
    pf_vol_set.last_error = 0;
    pf_vol_set.last_driver_error = 0;
    pf_vol_set.setting = 1;
    pf_vol_set.codeset.oem2unicode = PFCODE_CP932_OEM2Unicode;
    pf_vol_set.codeset.unicode2oem = PFCODE_CP932_Unicode2OEM;
    pf_vol_set.codeset.oem_char_width = PFCODE_CP932_OEMCharWidth;
    pf_vol_set.codeset.is_oem_mb_char = PFCODE_CP932_isOEMMBchar;
    pf_vol_set.codeset.unicode_char_width = PFCODE_CP932_UnicodeCharWidth;
    pf_vol_set.codeset.is_unicode_mb_char = PFCODE_CP932_isUnicodeMBchar;
    for (i = 0; i < 26; i++) {
        pf_memset(&pf_vol_set.volumes[i], 0, 0x1FAC);
    }
    PF_InitLockFile();
    return 0;
}

#define PFVOL_CLEAR_CURRENT_DIRS(volume) \
    do { \
        (volume)->current_dir[0].stat = 0; \
        (volume)->current_dir[1].stat = 0; \
        (volume)->current_dir[2].stat = 0; \
        (volume)->current_dir[3].stat = 0; \
    } while (0)

#define PFVOL_UPDATE_DRIVER_REQUESTS(volume, result) \
    do { \
        if (PFDRV_IsInserted(volume) == 0) { \
            if (PFDRV_IsUnmountRequested(volume) != 0 && ((volume)->flags & 8) == 0) { \
                PFFILE_FinalizeAllFiles(volume); \
                PFDIR_FinalizeAllDirs(volume); \
                (result) = PFDRV_unmount(volume, 1); \
                if ((result) == 0) { \
                    if (((volume)->flags & 8) != 0) { \
                        PFVOL_CLEAR_CURRENT_DIRS(volume); \
                    } \
                    (volume)->flags &= ~8; \
                } \
                PFDRV_ClearUnmountRequested(volume); \
                pf_vol_set.num_mounted_volumes--; \
            } \
            if (PFDRV_IsMountRequested(volume) != 0) { \
                PFDRV_ClearMountRequested(volume); \
            } \
            (result) = 0; \
        } else { \
            if (PFDRV_IsUnmountRequested(volume) != 0 && ((volume)->flags & 8) == 0) { \
                PFFILE_FinalizeAllFiles(volume); \
                PFDIR_FinalizeAllDirs(volume); \
                (result) = PFDRV_unmount(volume, 1); \
                if ((result) == 0) { \
                    if (((volume)->flags & 8) != 0) { \
                        PFVOL_CLEAR_CURRENT_DIRS(volume); \
                    } \
                    (volume)->flags &= ~8; \
                } \
                PFDRV_ClearUnmountRequested(volume); \
                pf_vol_set.num_mounted_volumes--; \
            } \
            if (PFDRV_IsMountRequested(volume) != 0) { \
                if (((volume)->flags & 8) == 0) { \
                    (result) = PFVOL_DoMountVolume(volume); \
                    if ((result) == 0) { \
                        (volume)->fsi_flag &= ~7; \
                        PFDRV_ClearUnmountRequested(volume); \
                        pf_vol_set.num_mounted_volumes++; \
                    } \
                } \
                if (((volume)->flags & 8) != 0 || (result) == 0) { \
                    PFDRV_ClearMountRequested(volume); \
                    (result) = 0; \
                } \
            } else { \
                (result) = 0; \
            } \
        } \
    } while (0)

s32 PFVOL_CheckForRead(PFVOL_VOLUME* volume) {
    s32 error;

    if (PFDRV_IsUnmountRequested(volume) != 0 && (volume->flags & 8) == 0) {
        PFFILE_FinalizeAllFiles(volume);
        PFDIR_FinalizeAllDirs(volume);
        error = PFDRV_unmount(volume, 1);
        if (error == 0) {
            if ((volume->flags & 8) != 0) {
                PFVOL_CLEAR_CURRENT_DIRS(volume);
            }
            volume->flags &= ~8;
        }
        PFDRV_ClearUnmountRequested(volume);
        pf_vol_set.num_mounted_volumes--;
    }
    if (PFDRV_IsInserted(volume) == 0) {
        if (PFDRV_IsMountRequested(volume) != 0) {
            PFDRV_ClearMountRequested(volume);
        }
    } else if (PFDRV_IsMountRequested(volume) != 0) {
        if ((volume->flags & 8) == 0) {
            error = PFVOL_DoMountVolume(volume);
            if (error != 0) {
                goto check_result;
            }
            volume->fsi_flag &= ~7;
            PFDRV_ClearUnmountRequested(volume);
            pf_vol_set.num_mounted_volumes++;
        }
        PFDRV_ClearMountRequested(volume);
        error = 0;
    }
    error = 0;
check_result:
    if (error == 0) {
        error = (((volume->flags >> 3) & 1) - 1) & 9;
    }
    return error;
}

s32 PFVOL_CheckForWrite(PFVOL_VOLUME* volume) {
    s32 error = 0;

    if (PFDRV_IsInserted(volume) == 0) {
        if (PFDRV_IsUnmountRequested(volume) != 0 && (volume->flags & 8) == 0) {
            PFFILE_FinalizeAllFiles(volume);
            PFDIR_FinalizeAllDirs(volume);
            error = PFDRV_unmount(volume, 1);
            if (error == 0) {
                if ((volume->flags & 8) != 0) {
                    PFVOL_CLEAR_CURRENT_DIRS(volume);
                }
                volume->flags &= ~8;
            }
            PFDRV_ClearUnmountRequested(volume);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(volume) != 0) {
            PFDRV_ClearMountRequested(volume);
        }
    } else {
        if (PFDRV_IsUnmountRequested(volume) != 0 && (volume->flags & 8) == 0) {
            PFFILE_FinalizeAllFiles(volume);
            PFDIR_FinalizeAllDirs(volume);
            error = PFDRV_unmount(volume, 1);
            if (error == 0) {
                if ((volume->flags & 8) != 0) {
                    PFVOL_CLEAR_CURRENT_DIRS(volume);
                }
                volume->flags &= ~8;
            }
            PFDRV_ClearUnmountRequested(volume);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(volume) != 0) {
            if ((volume->flags & 8) == 0) {
                error = PFVOL_DoMountVolume(volume);
                if (error == 0) {
                    volume->fsi_flag &= ~7;
                    PFDRV_ClearUnmountRequested(volume);
                    pf_vol_set.num_mounted_volumes++;
                    PFDRV_ClearMountRequested(volume);
                    error = 0;
                }
            } else {
                PFDRV_ClearMountRequested(volume);
                error = 0;
            }
            if (error != 0) {
                return error;
            }
        }
    }
    if ((volume->flags & 8) == 0) {
        return 9;
    }
    if ((volume->flags & 2) != 0) {
        return 11;
    }
    return 0;
}

s32 PFVOL_CheckCurrentDir(PFVOL_VOLUME* volume, u32 start_cluster) {
    s32 context_id;
    u32 current_dir_index;
    s32 result = 0;

    if ((volume->flags & 8) == 0) {
        return 9;
    }
    PFSYS_GetCurrentContextID(&context_id);
    for (current_dir_index = 1; current_dir_index < 4; current_dir_index++) {
        if ((volume->current_dir[current_dir_index].stat & 1) != 0 &&
            volume->current_dir[current_dir_index].context_id == context_id) {
            break;
        }
    }
    if (current_dir_index == 4) {
        current_dir_index = 0;
    }
    if (start_cluster == volume->current_dir[current_dir_index].directory.start_cluster) {
        result = -1;
    }
    return result;
}

s32 PFVOL_SetCurrentDir(PFVOL_VOLUME* volume, PFVOL_DIR_ENTRY* directory) {
    s32 context_id;
    u32 current_dir_index;
    u32 context_index;
    s32 context_registered = 0;

    if ((volume->flags & 8) == 0) {
        return 9;
    }
    PFSYS_GetCurrentContextID(&context_id);
    for (current_dir_index = 1; current_dir_index < 4; current_dir_index++) {
        if ((volume->current_dir[current_dir_index].stat & 1) != 0 &&
            volume->current_dir[current_dir_index].context_id == context_id) {
            volume->current_dir[current_dir_index].directory = *directory;
            break;
        }
    }
    if (current_dir_index == 4) {
        if (((pf_vol_set.context[0].stat &= 1) != 0 &&
             context_id == pf_vol_set.context[0].context_id) ||
            ((pf_vol_set.context[1].stat &= 1) != 0 &&
             context_id == pf_vol_set.context[1].context_id) ||
            ((pf_vol_set.context[2].stat &= 1) != 0 &&
             context_id == pf_vol_set.context[2].context_id)) {
            context_registered = 1;
        } else {
            context_registered = 0;
        }
        if (context_registered != 0) {
            for (current_dir_index = 1; current_dir_index < 4; current_dir_index++) {
                if ((volume->current_dir[current_dir_index].stat & 1) == 0) {
                    volume->current_dir[current_dir_index].stat |= 1;
                    volume->current_dir[current_dir_index].context_id = context_id;
                    volume->current_dir[current_dir_index].directory = *directory;
                    break;
                }
            }
        }
    }
    volume->current_dir[0].directory = *directory;
    return 0;
}

s32 PFVOL_GetCurrentDir(PFVOL_VOLUME* volume, PFVOL_DIR_ENTRY* directory) {
    s32 context_id;
    u32 current_dir_index;
    u32 context_index;
    s32 context_registered = 0;

    if ((volume->flags & 8) == 0) {
        return 9;
    }
    PFSYS_GetCurrentContextID(&context_id);
    for (current_dir_index = 1; current_dir_index < 4; current_dir_index++) {
        if ((volume->current_dir[current_dir_index].stat & 1) != 0 &&
            volume->current_dir[current_dir_index].context_id == context_id) {
            *directory = volume->current_dir[current_dir_index].directory;
            break;
        }
    }
    if (current_dir_index == 4) {
        if (((pf_vol_set.context[0].stat &= 1) != 0 &&
             context_id == pf_vol_set.context[0].context_id) ||
            ((pf_vol_set.context[1].stat &= 1) != 0 &&
             context_id == pf_vol_set.context[1].context_id) ||
            ((pf_vol_set.context[2].stat &= 1) != 0 &&
             context_id == pf_vol_set.context[2].context_id)) {
            context_registered = 1;
        } else {
            context_registered = 0;
        }
        if (context_registered != 0) {
            for (current_dir_index = 1; current_dir_index < 4; current_dir_index++) {
                if ((volume->current_dir[current_dir_index].stat & 1) == 0) {
                    volume->current_dir[current_dir_index].stat |= 1;
                    volume->current_dir[current_dir_index].context_id = context_id;
                    *directory = volume->current_dir[current_dir_index].directory;
                    break;
                }
            }
        } else {
            *directory = volume->current_dir[0].directory;
        }
    }
    return 0;
}

void PFVOL_SetCurrentVolume(PFVOL_VOLUME* volume) {
    s32 context_id;
    u32 context_index;
    s32 context_registered;

    PFSYS_GetCurrentContextID(&context_id);
    context_registered = 0;
    for (context_index = 1; context_index < 4; context_index++) {
        if ((pf_vol_set.context_volume[context_index - 1].stat & 1) != 0 &&
            pf_vol_set.context_volume[context_index - 1].context_id == context_id) {
            pf_vol_set.context_volume[context_index - 1].volume = volume;
            break;
        }
    }
    if (context_index == 4) {
        for (context_index = 1; context_index < 4; context_index++) {
            pf_vol_set.context[context_index - 1].stat &= 1;
            if (pf_vol_set.context[context_index - 1].stat != 0 &&
                pf_vol_set.context[context_index - 1].context_id == context_id) {
                context_registered = 1;
                break;
            }
        }
        if (context_registered != 0) {
            for (context_index = 1; context_index < 4; context_index++) {
                if ((pf_vol_set.context_volume[context_index - 1].stat & 1) == 0) {
                    pf_vol_set.context_volume[context_index - 1].stat |= 1;
                    pf_vol_set.context_volume[context_index - 1].context_id = context_id;
                    pf_vol_set.context_volume[context_index - 1].volume = volume;
                    break;
                }
            }
        }
    }
    pf_vol_set.current_volume = volume;
}

PFVOL_VOLUME* PFVOL_GetCurrentVolume(void) {
    s32 context_id;
    u32 context_index;
    s32 context_registered;
    PFVOL_VOLUME* volume = 0;

    PFSYS_GetCurrentContextID(&context_id);
    context_registered = 0;
    for (context_index = 1; context_index < 4; context_index++) {
        if ((pf_vol_set.context_volume[context_index - 1].stat & 1) != 0 &&
            pf_vol_set.context_volume[context_index - 1].context_id == context_id) {
            volume = pf_vol_set.context_volume[context_index - 1].volume;
            break;
        }
    }
    if (context_index == 4) {
        for (context_index = 1; context_index < 4; context_index++) {
            pf_vol_set.context[context_index - 1].stat &= 1;
            if (pf_vol_set.context[context_index - 1].stat != 0 &&
                pf_vol_set.context[context_index - 1].context_id == context_id) {
                context_registered = 1;
                break;
            }
        }
        if (context_registered != 0) {
            for (context_index = 1; context_index < 4; context_index++) {
                if ((pf_vol_set.context_volume[context_index - 1].stat & 1) == 0) {
                    pf_vol_set.context_volume[context_index - 1].stat |= 1;
                    pf_vol_set.context_volume[context_index - 1].context_id = context_id;
                    volume = pf_vol_set.context_volume[context_index - 1].volume;
                    break;
                }
            }
        } else {
            volume = pf_vol_set.current_volume;
        }
    }
    return volume;
}

PFVOL_VOLUME* PFVOL_GetVolumeFromDrvChar(s8 drive) {
    s16 volume_index;

    volume_index = pf_toupper(drive) - 'A';
    if (volume_index < 0 || volume_index >= 26) {
        return 0;
    }
    return &pf_vol_set.volumes[volume_index];
}

s32 PFVOL_derrnum(s8 drive) {
    s16 volume_index;
    PFVOL_VOLUME* volume;

    volume_index = pf_toupper(drive) - 'A';
    if (volume_index < 0 || volume_index >= 26) {
        volume = 0;
    } else {
        volume = &pf_vol_set.volumes[volume_index];
    }
    return volume->last_driver_error;
}

s32 PFVOL_errnum(void) {
    return pf_vol_set.last_error;
}

void PFVOL_setvol(s8 drive, const s8* label) {
    s16 volume_index;
    PFVOL_VOLUME* volume;
    u16 label_length;
    s32 error;
    s8 upper_label[12];

    volume_index = pf_toupper(drive) - 'A';
    if (volume_index < 0 || volume_index >= 26) {
        volume = 0;
    } else {
        volume = &pf_vol_set.volumes[volume_index];
    }
    label_length = PFSTR_StrLen(label);
    error = PFDRV_IsInserted(volume);
    if (error != 0) {
        if (PFDRV_IsUnmountRequested(volume) != 0 && (volume->flags & 8) == 0) {
            PFFILE_FinalizeAllFiles(volume);
            PFDIR_FinalizeAllDirs(volume);
            error = PFDRV_unmount(volume, 1);
            if (error == 0) {
                if ((volume->flags & 8) != 0) {
                    PFVOL_CLEAR_CURRENT_DIRS(volume);
                }
                volume->flags &= ~8;
            }
            PFDRV_ClearUnmountRequested(volume);
            pf_vol_set.num_mounted_volumes--;
        }
        error = PFDRV_IsMountRequested(volume);
        if (error != 0) {
            if ((volume->flags & 8) == 0) {
                error = PFVOL_DoMountVolume(volume);
                if (error == 0) {
                    volume->fsi_flag &= ~7;
                    PFDRV_ClearUnmountRequested(volume);
                    pf_vol_set.num_mounted_volumes++;
                    PFDRV_ClearMountRequested(volume);
                    error = 0;
                }
            } else {
                PFDRV_ClearMountRequested(volume);
                error = 0;
            }
            if (error != 0) {
                goto save_error;
            }
        }
    } else {
        if (PFDRV_IsUnmountRequested(volume) != 0 && (volume->flags & 8) == 0) {
            PFFILE_FinalizeAllFiles(volume);
            PFDIR_FinalizeAllDirs(volume);
            error = PFDRV_unmount(volume, 1);
            if (error == 0) {
                if ((volume->flags & 8) != 0) {
                    PFVOL_CLEAR_CURRENT_DIRS(volume);
                }
                volume->flags &= ~8;
            }
            PFDRV_ClearUnmountRequested(volume);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(volume) != 0) {
            PFDRV_ClearMountRequested(volume);
        }
    }
    error = 0;
    if ((volume->flags & 8) == 0) {
        error = 9;
    } else if ((volume->flags & 2) != 0) {
        error = 11;
    }
    if (error != 0) {
        goto save_error;
    }
    PFSTR_ToUpperNStr(label, 11, upper_label);
    if (label_length < 11) {
        upper_label[label_length] = 0;
    }
    error = PFVOL_p_setvol(volume, upper_label);
    if (error != 0) {
        goto save_error;
    }
    error = PFCACHE_FlushFATCache(volume);
    if (error != 0) {
        goto save_error;
    }
    error = PFCACHE_FlushDataCacheSpecific(volume, 0);
    if (error != 0) {
        goto save_error;
    }
    error = PFDRV_StoreVolumeLabelToBPB(volume, upper_label);
    if (error != 0) {
        goto save_error;
    }
    return;

save_error:
    pf_vol_set.last_error = error;
    volume->last_error = error;
    return;
}

s32 PFVOL_getvol(s8 drive, PFVOL_VOLUME_INFO* volume_info) {
    s16 volume_index;
    PFVOL_VOLUME* volume;
    s32 error;

    volume_index = pf_toupper(drive) - 'A';
    if (volume_index < 0 || volume_index >= 26) {
        volume = 0;
    } else {
        volume = &pf_vol_set.volumes[volume_index];
    }
    if (pf_memcmp(volume->label, "NO NAME    ", 11) == 0) {
        pf_vol_set.last_error = 3;
        volume->last_error = 3;
        return 3;
    }
    if (PFDRV_IsInserted(volume) != 0) {
        if (PFDRV_IsUnmountRequested(volume) != 0 && (volume->flags & 8) == 0) {
            PFFILE_FinalizeAllFiles(volume);
            PFDIR_FinalizeAllDirs(volume);
            error = PFDRV_unmount(volume, 1);
            if (error == 0) {
                if ((volume->flags & 8) != 0) {
                    PFVOL_CLEAR_CURRENT_DIRS(volume);
                }
                volume->flags &= ~8;
            }
            PFDRV_ClearUnmountRequested(volume);
            pf_vol_set.num_mounted_volumes--;
        }
        error = PFDRV_IsMountRequested(volume);
        if (error != 0) {
            if ((volume->flags & 8) == 0) {
                error = PFVOL_DoMountVolume(volume);
                if (error == 0) {
                    volume->fsi_flag &= ~7;
                    PFDRV_ClearUnmountRequested(volume);
                    pf_vol_set.num_mounted_volumes++;
                    PFDRV_ClearMountRequested(volume);
                    error = 0;
                }
            } else {
                PFDRV_ClearMountRequested(volume);
                error = 0;
            }
            if (error != 0) {
                goto save_error;
            }
        }
    } else {
        if (PFDRV_IsUnmountRequested(volume) != 0 && (volume->flags & 8) == 0) {
            PFFILE_FinalizeAllFiles(volume);
            PFDIR_FinalizeAllDirs(volume);
            error = PFDRV_unmount(volume, 1);
            if (error == 0) {
                if ((volume->flags & 8) != 0) {
                    PFVOL_CLEAR_CURRENT_DIRS(volume);
                }
                volume->flags &= ~8;
            }
            PFDRV_ClearUnmountRequested(volume);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(volume) != 0) {
            PFDRV_ClearMountRequested(volume);
        }
    }
    error = 0;
    if ((volume->flags & 8) == 0) {
        error = 9;
    }
    if (error != 0) {
        goto save_error;
    }
    error = PFVOL_p_getvol(volume, volume_info);
    if (error != 0) {
        goto save_error;
    }
    return 0;

save_error:
    pf_vol_set.last_error = error;
    volume->last_error = error;
    return error;
}

s32 PFVOL_rmvvol(s8 drive) {
    s16 volume_index;
    PFVOL_VOLUME* volume;
    s32 error;

    volume_index = pf_toupper(drive) - 'A';
    if (volume_index < 0 || volume_index >= 26) {
        volume = 0;
    } else {
        volume = &pf_vol_set.volumes[volume_index];
    }
    if (pf_memcmp(volume->label, "NO NAME    ", 11) == 0) {
        pf_vol_set.last_error = 3;
        volume->last_error = 3;
        return 3;
    }
    if (PFDRV_IsInserted(volume) != 0) {
        if (PFDRV_IsUnmountRequested(volume) != 0 && (volume->flags & 8) == 0) {
            PFFILE_FinalizeAllFiles(volume);
            PFDIR_FinalizeAllDirs(volume);
            error = PFDRV_unmount(volume, 1);
            if (error == 0) {
                if ((volume->flags & 8) != 0) {
                    PFVOL_CLEAR_CURRENT_DIRS(volume);
                }
                volume->flags &= ~8;
            }
            PFDRV_ClearUnmountRequested(volume);
            pf_vol_set.num_mounted_volumes--;
        }
        error = PFDRV_IsMountRequested(volume);
        if (error != 0) {
            if ((volume->flags & 8) == 0) {
                error = PFVOL_DoMountVolume(volume);
                if (error == 0) {
                    volume->fsi_flag &= ~7;
                    PFDRV_ClearUnmountRequested(volume);
                    pf_vol_set.num_mounted_volumes++;
                    PFDRV_ClearMountRequested(volume);
                    error = 0;
                }
            } else {
                PFDRV_ClearMountRequested(volume);
                error = 0;
            }
            if (error != 0) {
                goto save_error;
            }
        }
    } else {
        if (PFDRV_IsUnmountRequested(volume) != 0 && (volume->flags & 8) == 0) {
            PFFILE_FinalizeAllFiles(volume);
            PFDIR_FinalizeAllDirs(volume);
            error = PFDRV_unmount(volume, 1);
            if (error == 0) {
                if ((volume->flags & 8) != 0) {
                    PFVOL_CLEAR_CURRENT_DIRS(volume);
                }
                volume->flags &= ~8;
            }
            PFDRV_ClearUnmountRequested(volume);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(volume) != 0) {
            PFDRV_ClearMountRequested(volume);
        }
    }
    error = 0;
    if ((volume->flags & 8) == 0) {
        error = 9;
    } else if ((volume->flags & 2) != 0) {
        error = 11;
    }
    if (error != 0) {
        goto save_error;
    }
    error = PFDRV_StoreVolumeLabelToBPB(volume, (const s8*)"NO NAME    ");
    if (error != 0) {
        goto save_error;
    }
    error = PFVOL_p_rmvvol(volume);
    if (error != 0) {
        goto save_error;
    }
    error = PFCACHE_FlushDataCacheSpecific(volume, 0);
    if (error != 0) {
        goto save_error;
    }
    return 0;

save_error:
    pf_vol_set.last_error = error;
    volume->last_error = error;
    return error;
}

s32 PFVOL_getdev(s8 drive, u32* device_info) {
    s16 volume_index;
    PFVOL_VOLUME* volume;
    s32 error;

    volume_index = pf_toupper(drive) - 'A';
    if (volume_index < 0 || volume_index >= 26) {
        volume = 0;
    } else {
        volume = &pf_vol_set.volumes[volume_index];
    }
    if (PFDRV_IsInserted(volume) != 0) {
        if (PFDRV_IsUnmountRequested(volume) != 0 && (volume->flags & 8) == 0) {
            PFFILE_FinalizeAllFiles(volume);
            PFDIR_FinalizeAllDirs(volume);
            error = PFDRV_unmount(volume, 1);
            if (error == 0) {
                if ((volume->flags & 8) != 0) {
                    PFVOL_CLEAR_CURRENT_DIRS(volume);
                }
                volume->flags &= ~8;
            }
            PFDRV_ClearUnmountRequested(volume);
            pf_vol_set.num_mounted_volumes--;
        }
        error = PFDRV_IsMountRequested(volume);
        if (error != 0) {
            if ((volume->flags & 8) == 0) {
                error = PFVOL_DoMountVolume(volume);
                if (error == 0) {
                    volume->fsi_flag &= ~7;
                    PFDRV_ClearUnmountRequested(volume);
                    pf_vol_set.num_mounted_volumes++;
                    PFDRV_ClearMountRequested(volume);
                    error = 0;
                }
            } else {
                PFDRV_ClearMountRequested(volume);
                error = 0;
            }
            if (error != 0) {
                goto save_error;
            }
        }
    } else {
        if (PFDRV_IsUnmountRequested(volume) != 0 && (volume->flags & 8) == 0) {
            PFFILE_FinalizeAllFiles(volume);
            PFDIR_FinalizeAllDirs(volume);
            error = PFDRV_unmount(volume, 1);
            if (error == 0) {
                if ((volume->flags & 8) != 0) {
                    PFVOL_CLEAR_CURRENT_DIRS(volume);
                }
                volume->flags &= ~8;
            }
            PFDRV_ClearUnmountRequested(volume);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(volume) != 0) {
            PFDRV_ClearMountRequested(volume);
        }
    }
    error = 0;
    if ((volume->flags & 8) == 0) {
        error = 9;
    }
    if (error != 0) {
        goto save_error;
    }
    device_info[2] = volume->bpb.bytes_per_sector;
    device_info[3] = volume->bpb.sectors_per_cluster;
    device_info[0] = volume->bpb.num_clusters;
    error = PFFAT_CountFreeClusters(volume, &device_info[1]);
    if (error != 0) {
        goto save_error;
    }
    return 0;

save_error:
    pf_vol_set.last_error = error;
    volume->last_error = error;
    return error;
}

s32 PFVOL_buffering(s8 drive, u32 mode) {
    s16 volume_index;
    PFVOL_VOLUME* volume;
    s32 error;

    volume_index = pf_toupper(drive) - 'A';
    if (volume_index < 0 || volume_index >= 26) {
        volume = 0;
    } else {
        volume = &pf_vol_set.volumes[volume_index];
    }
    if (PFDRV_IsInserted(volume) != 0) {
        if (PFDRV_IsUnmountRequested(volume) != 0 && (volume->flags & 8) == 0) {
            PFFILE_FinalizeAllFiles(volume);
            PFDIR_FinalizeAllDirs(volume);
            error = PFDRV_unmount(volume, 1);
            if (error == 0) {
                if ((volume->flags & 8) != 0) {
                    PFVOL_CLEAR_CURRENT_DIRS(volume);
                }
                volume->flags &= ~8;
            }
            PFDRV_ClearUnmountRequested(volume);
            pf_vol_set.num_mounted_volumes--;
        }
        error = PFDRV_IsMountRequested(volume);
        if (error != 0) {
            if ((volume->flags & 8) == 0) {
                error = PFVOL_DoMountVolume(volume);
                if (error == 0) {
                    volume->fsi_flag &= ~7;
                    PFDRV_ClearUnmountRequested(volume);
                    pf_vol_set.num_mounted_volumes++;
                    PFDRV_ClearMountRequested(volume);
                    error = 0;
                }
            } else {
                PFDRV_ClearMountRequested(volume);
                error = 0;
            }
            if (error != 0) {
                goto save_error;
            }
        }
    } else {
        if (PFDRV_IsUnmountRequested(volume) != 0 && (volume->flags & 8) == 0) {
            PFFILE_FinalizeAllFiles(volume);
            PFDIR_FinalizeAllDirs(volume);
            error = PFDRV_unmount(volume, 1);
            if (error == 0) {
                if ((volume->flags & 8) != 0) {
                    PFVOL_CLEAR_CURRENT_DIRS(volume);
                }
                volume->flags &= ~8;
            }
            PFDRV_ClearUnmountRequested(volume);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(volume) != 0) {
            PFDRV_ClearMountRequested(volume);
        }
    }
    error = 0;
    if ((volume->flags & 8) == 0) {
        error = 9;
    } else if ((volume->flags & 2) != 0) {
        error = 11;
    }
    if (error == 0) {
        if ((mode & 4) == 0 || (volume->cache_flags & 1) != 0) {
            error = 0;
        } else {
            error = PFCACHE_FlushFATCache(volume);
            if (error != 0) {
                goto save_error;
            }
        }
        if (error == 0) {
            if ((mode & 1) == 0) {
                error = PFCACHE_SetWriteBackMode(volume);
            } else {
                error = PFCACHE_SetWriteThroughMode(volume);
            }
            if (error != 0) {
                goto save_error;
            }
            if ((mode & 4) != 0) {
                volume->cache_flags |= 4;
            } else {
                volume->cache_flags &= ~4;
            }
            if ((mode & 2) != 0) {
                volume->cache_flags |= 2;
            } else {
                volume->cache_flags &= ~2;
            }
        }
    } else {
        goto save_error;
    }
    return 0;

save_error:
    pf_vol_set.last_error = error;
    volume->last_error = error;
    return error;
}

s32 PFVOL_attach(PFVOL_DRIVER* driver, s32 notify_command, void* callback_data) {
    PFVOL_CACHE_SETTING* cache;
    PFVOL_VOLUME* volume;
    s32 volume_index;
    s32 error;

    cache = driver->cache;
    if (cache->num_fat_buf_size == 0) {
        cache->num_fat_buf_size = 1;
    }
    if (cache->num_data_buf_size == 0) {
        cache->num_data_buf_size = 1;
    }
    driver->drive = 0;
    driver->stat = 0;
    if (notify_command != 0 && fa_nanddrv_NotifyNANDFile(notify_command, callback_data) != 0) {
        pf_vol_set.last_error = 17;
        return 17;
    }
    volume_index = 0;
    volume = pf_vol_set.volumes;
    while (volume_index < 26) {
        if ((volume->flags & 1) == 0) {
            break;
        }
        volume++;
        volume_index++;
        if ((volume->flags & 1) == 0) {
            break;
        }
        volume++;
        volume_index++;
    }
    if (volume_index < 0 || volume_index >= 26 || pf_vol_set.num_attached_drives < 0 ||
        pf_vol_set.num_attached_drives >= 26) {
        pf_vol_set.last_error = 4;
        return 4;
    }
    volume->last_error = -1;
    volume->last_driver_error = -1;
    pf_memset(volume, 0, 0x1FAC);
    volume->driver_partition = driver->partition;
    volume->options = volume_index + 'A';
    volume->file_buffer_count = 1;
    volume->current_file_buffer = &volume->file_buffers;
    error = PFDRV_init(volume);
    if (error == 0) {
        PFCACHE_SetCache(volume, cache->pages, cache->buffers, cache->num_fat_pages,
                         cache->num_data_pages);
        PFCACHE_SetFATBufferSize(volume, cache->num_fat_buf_size);
        PFCACHE_SetDataBufferSize(volume, cache->num_data_buf_size);
    }
    if (error != 0) {
        pf_vol_set.last_error = error;
        return error;
    }
    volume->flags |= 1;
    driver->stat |= 1;
    volume->options = volume_index + 'A';
    driver->drive = volume_index + 'A';
    pf_vol_set.num_attached_drives++;
    if (PFDRV_IsInserted(volume) == 0) {
        return 0;
    }
    driver->stat |= 0x10;
    if ((volume->flags & 8) == 0) {
        error = PFVOL_DoMountVolume(volume);
        if (error == 0) {
            volume->fsi_flag &= ~7;
            PFDRV_ClearUnmountRequested(volume);
            pf_vol_set.num_mounted_volumes++;
        }
    }
    if (error == 0) {
        PFDRV_ClearMountRequested(volume);
        driver->stat |= 2;
        return 0;
    }
    pf_vol_set.last_error = error;
    volume->last_error = error;
    return 0;
}

s32 PFVOL_detach(s8 drive) {
    s16 volume_index;
    PFVOL_VOLUME* volume;
    s32 error;

    volume_index = pf_toupper(drive) - 'A';
    if (volume_index < 0 || volume_index >= 26) {
        volume = 0;
    } else {
        volume = &pf_vol_set.volumes[volume_index];
    }
    if ((volume->flags & 8) != 0) {
        error = 10;
        pf_vol_set.last_error = error;
        volume->last_error = error;
    } else if ((volume->flags & 1) == 0) {
        error = 10;
        pf_vol_set.last_error = error;
        volume->last_error = error;
    } else {
        error = PFDRV_finalize(volume);
        if (error == 0) {
            volume->flags &= ~1;
            pf_vol_set.num_attached_drives--;
        } else {
            pf_vol_set.last_error = error;
            volume->last_error = error;
        }
    }
    return error;
}

s32 PFVOL_format(s8 drive, const u8* format_options) {
    s16 volume_index;
    PFVOL_VOLUME* volume;
    s32 error;
    u8 mount_requested;

    volume_index = pf_toupper(drive) - 'A';
    if (volume_index < 0 || volume_index >= 26) {
        volume = 0;
    } else {
        volume = &pf_vol_set.volumes[volume_index];
    }
    if ((volume->flags & 1) == 0) {
        error = 10;
        goto save_error;
    }
    if (PFDRV_IsInserted(volume) == 0) {
        error = 9;
        goto save_error;
    }
    mount_requested = PFDRV_IsMountRequested(volume) != 0;
    if (mount_requested != 0) {
        PFDRV_ClearMountRequested(volume);
    }
    if (PFDRV_IsInserted(volume) != 0) {
        if (PFDRV_IsUnmountRequested(volume) != 0 && (volume->flags & 8) == 0) {
            PFFILE_FinalizeAllFiles(volume);
            PFDIR_FinalizeAllDirs(volume);
            error = PFDRV_unmount(volume, 1);
            if (error == 0) {
                if ((volume->flags & 8) != 0) {
                    PFVOL_CLEAR_CURRENT_DIRS(volume);
                }
                volume->flags &= ~8;
            }
            PFDRV_ClearUnmountRequested(volume);
            pf_vol_set.num_mounted_volumes--;
        }
        error = PFDRV_IsMountRequested(volume);
        if (error != 0) {
            if ((volume->flags & 8) == 0) {
                error = PFVOL_DoMountVolume(volume);
                if (error == 0) {
                    volume->fsi_flag &= ~7;
                    PFDRV_ClearUnmountRequested(volume);
                    pf_vol_set.num_mounted_volumes++;
                    PFDRV_ClearMountRequested(volume);
                    error = 0;
                }
            } else {
                PFDRV_ClearMountRequested(volume);
                error = 0;
            }
            if (error != 0) {
                goto after_mount;
            }
        }
    } else {
        if (PFDRV_IsUnmountRequested(volume) != 0 && (volume->flags & 8) == 0) {
            PFFILE_FinalizeAllFiles(volume);
            PFDIR_FinalizeAllDirs(volume);
            error = PFDRV_unmount(volume, 1);
            if (error == 0) {
                if ((volume->flags & 8) != 0) {
                    PFVOL_CLEAR_CURRENT_DIRS(volume);
                }
                volume->flags &= ~8;
            }
            PFDRV_ClearUnmountRequested(volume);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(volume) != 0) {
            PFDRV_ClearMountRequested(volume);
        }
    }
    error = 0;
after_mount:
    if (error == 0) {
        if (volume->num_open_files != 0) {
            PFFILE_FinalizeAllFiles(volume);
            PFCACHE_FreeAllCaches(volume);
        }
        if (volume->num_open_dirs != 0) {
            PFDIR_FinalizeAllDirs(volume);
        }
        error = PFVOL_p_format(volume, format_options);
        if (error == 0) {
            volume->fsi_flag |= 4;
            volume->num_free_clusters = volume->bpb.num_clusters - (volume->bpb.fat_type == 2);
            return 0;
        }
    }
    if (mount_requested) {
        volume->flags |= 0x10;
    }
    if (error != 0) {
        pf_vol_set.last_error = error;
        volume->last_error = error;
    }
    return error;

save_error:
    pf_vol_set.last_error = error;
    volume->last_error = error;
    return error;
}

s32 PFVOL_mount(s8 drive) {
    s16 volume_index;
    PFVOL_VOLUME* volume;
    s32 error;

    volume_index = pf_toupper(drive) - 'A';
    if (volume_index < 0 || volume_index >= 26) {
        volume = 0;
    } else {
        volume = &pf_vol_set.volumes[volume_index];
    }
    PFVOL_UPDATE_DRIVER_REQUESTS(volume, error);
    if (error == 0) {
        if (PFDRV_IsInserted(volume) != 0) {
            if ((volume->flags & 8) == 0) {
                error = PFVOL_DoMountVolume(volume);
                if (error == 0) {
                    volume->fsi_flag &= ~7;
                    PFDRV_ClearUnmountRequested(volume);
                    pf_vol_set.num_mounted_volumes++;
                    PFDRV_ClearMountRequested(volume);
                }
            }
        } else {
            error = 9;
        }
    }
    if (error != 0) {
        pf_vol_set.last_error = error;
        volume->last_error = error;
    }
    return error;
}

s32 PFVOL_unmount(s8 drive, u32 mode) {
    s16 volume_index;
    PFVOL_VOLUME* volume;
    s32 error;
    s32 prior_error = 0;
    s32 result;

    volume_index = pf_toupper(drive) - 'A';
    if (volume_index < 0 || volume_index >= 26) {
        volume = 0;
    } else {
        volume = &pf_vol_set.volumes[volume_index];
    }
    if ((volume->flags & 1) == 0) {
        pf_vol_set.last_error = 10;
        return 10;
    }
    PFDRV_ClearMountRequested(volume);
    PFVOL_UPDATE_DRIVER_REQUESTS(volume, error);
    if (error != 0) {
        pf_vol_set.last_error = error;
        volume->last_error = error;
        return error;
    }
    if ((volume->flags & 8) == 0) {
        return 0;
    }
    if (volume->num_open_files != 0 || volume->num_open_dirs != 0) {
        prior_error = 1;
        pf_vol_set.last_error = 19;
        volume->last_error = 19;
        if ((mode & 1) == 0) {
            return 19;
        }
    }
    error = PFVOL_p_unmount(volume, mode);
    result = prior_error;
    if (error != 0 && prior_error == 0) {
        pf_vol_set.last_error = error;
        volume->last_error = error;
        result = 1;
        if ((mode & 1) == 0) {
            result = error;
        }
    }
    return result;
}

s32 PFVOL_setupfsi(s8 drive, u32 mode) {
    s16 volume_index;
    PFVOL_VOLUME* volume;
    s32 error;
    u16 prior_fsi_flags;
    u32 free_clusters;

    volume_index = pf_toupper(drive) - 'A';
    if (volume_index < 0 || volume_index >= 26) {
        volume = 0;
    } else {
        volume = &pf_vol_set.volumes[volume_index];
    }
    PFVOL_UPDATE_DRIVER_REQUESTS(volume, error);
    if (error == 0 && (volume->flags & 8) == 0) {
        error = 9;
    }
    if (error == 0) {
        if (volume->bpb.fat_type == 2) {
            if ((mode & 1) == 1) {
                volume->fsi_flag |= 5;
            } else if ((mode & 2) == 2) {
                volume->fsi_flag &= ~1;
            }
            if ((mode & 4) == 4) {
                volume->fsi_flag |= 2;
                if ((volume->fsi_flag & 4) == 0) {
                    PFFAT_CountFreeClusters(volume, &free_clusters);
                }
            } else if ((mode & 8) == 8) {
                volume->fsi_flag &= ~2;
            }
        } else {
            error = 12;
        }
    }
    if (error != 0) {
        pf_vol_set.last_error = error;
        volume->last_error = error;
    }
    return error;
}

s32 PFVOL_setclstlink(s8 drive, s32 mode, PFVOL_CLUSTER_SETTING* setting) {
    s16 volume_index;
    PFVOL_VOLUME* volume;
    s32 error;

    volume_index = pf_toupper(drive) - 'A';
    if (volume_index < 0 || volume_index >= 26) {
        volume = 0;
    } else {
        volume = &pf_vol_set.volumes[volume_index];
    }
    if (volume->num_open_files != 0) {
        pf_vol_set.last_error = 19;
        volume->last_error = 19;
        return 19;
    }
    PFVOL_UPDATE_DRIVER_REQUESTS(volume, error);
    if (error == 0) {
        if ((volume->flags & 8) == 0) {
            error = 9;
        } else if ((volume->flags & 2) != 0) {
            error = 11;
        }
    }
    if (error == 0) {
        if (mode == 1) {
            if (setting->buffer == 0) {
                pf_vol_set.last_error = 10;
                volume->last_error = 10;
                return 10;
            } else {
                volume->cluster_link_flags |= 1;
                volume->cluster_link_buffer = setting->buffer;
                pf_memset(setting->buffer, 0, setting->max_count * 0x14);
                volume->cluster_link_interval = setting->interval;
                volume->cluster_link_capacity = setting->max_count;
            }
        } else {
            volume->cluster_link_flags &= ~1;
            volume->cluster_link_buffer = 0;
            volume->cluster_link_interval = 0;
            volume->cluster_link_capacity = 0;
        }
    }
    if (error != 0) {
        pf_vol_set.last_error = error;
        volume->last_error = error;
        return error;
    }
    return 0;
}

s32 PFVOL_sync(s8 drive, s32 mode) {
    s16 volume_index;
    PFVOL_VOLUME* volume;
    PFVOL_OPEN_FILE* file;
    s32 error;
    u32 file_index;

    volume_index = pf_toupper(drive) - 'A';
    if (volume_index < 0 || volume_index >= 26) {
        volume = 0;
    } else {
        volume = &pf_vol_set.volumes[volume_index];
    }
    PFVOL_UPDATE_DRIVER_REQUESTS(volume, error);
    if (error == 0) {
        if ((volume->flags & 8) == 0) {
            error = 9;
        } else if ((volume->flags & 2) != 0) {
            error = 11;
        }
    }
    if (error == 0) {
        error = PFCACHE_FlushFATCache(volume);
        if (error == 0) {
            file_index = 0;
            do {
                file = &volume->files[file_index];
                if ((file->stat & 1) != 0) {
                    error = PFENT_updateEntry(&file->stream->directory_entry, 1);
                    if (error != 0) {
                        pf_vol_set.last_error = error;
                        volume->last_error = error;
                        return error;
                    }
                }
                file_index++;
            } while (file_index < 5);
            error = PFCACHE_FlushDataCache(volume);
            if (error == 0 && mode == 1) {
                PFCACHE_FreeAllCaches(volume);
            }
        }
    }
    if (error != 0) {
        pf_vol_set.last_error = error;
        volume->last_error = error;
    }
    return error;
}

void PFVOL_settailbuf(s8 drive, u32 count, void* buffer) {
    s16 volume_index;
    PFVOL_VOLUME* volume;
    s32 error;

    volume_index = pf_toupper(drive) - 'A';
    if (volume_index < 0 || volume_index >= 26) {
        volume = 0;
    } else {
        volume = &pf_vol_set.volumes[volume_index];
    }
    PFVOL_UPDATE_DRIVER_REQUESTS(volume, error);
    if (error == 0 && (volume->flags & 8) == 0) {
        error = 9;
    }
    if (error == 0) {
        volume->file_buffer_count = count;
        volume->current_file_buffer = buffer;
    } else {
        pf_vol_set.last_error = error;
        volume->last_error = error;
    }
}

s32 PFVOL_setvolcfg(s8 drive, u32* config) {
    s16 volume_index;
    PFVOL_VOLUME* volume;
    s32 error;

    if (drive == -1) {
        if ((config[0] & 0x10000) != 0) {
            pf_vol_set.config |= 0x10000;
        } else if ((config[0] & 0x20000) != 0) {
            pf_vol_set.config &= ~0x10000;
        }
        return 0;
    }
    volume_index = pf_toupper(drive) - 'A';
    if (volume_index < 0 || volume_index >= 26) {
        volume = 0;
    } else {
        volume = &pf_vol_set.volumes[volume_index];
    }
    if (config[2] == 0) {
        config[2] = 1;
    }
    if (config[3] == 0) {
        config[3] = 1;
    }
    PFVOL_UPDATE_DRIVER_REQUESTS(volume, error);
    if (volume->num_open_files != 0 || volume->num_open_dirs != 0) {
        pf_vol_set.last_error = 19;
        volume->last_error = 19;
        return 19;
    }
    if ((config[0] & 1) != 0 || (config[0] & 2) != 0) {
        PFCACHE_FlushAllCaches(volume);
        PFCACHE_FreeAllCaches(volume);
        if ((config[0] & 1) != 0) {
            if (config[2] != volume->num_fat_buf_size) {
                PFCACHE_SetFATBufferSize(volume, config[2]);
                config[0] &= ~1;
            }
        }
        if ((config[0] & 2) != 0) {
            if (config[3] != volume->num_data_buf_size) {
                PFCACHE_SetDataBufferSize(volume, config[3]);
                config[0] &= ~2;
            }
        }
        PFCACHE_InitCaches(volume);
    }
    if ((config[1] & 1) != 0) {
        volume->reserved_1f88 |= 1;
    } else if ((config[1] & 2) != 0) {
        volume->reserved_1f88 &= ~1;
    }
    return 0;

}

s32 PFVOL_getvolcfg(s8 drive, u32* config) {
    s16 volume_index;
    PFVOL_VOLUME* volume;
    s32 error;

    if (drive == -1) {
        config[0] = pf_vol_set.config;
        if ((pf_vol_set.config & 0x10000) == 0) {
            config[0] |= 0x20000;
        }
        config[1] = 0;
        config[2] = 0;
        config[3] = 0;
        return 0;
    }
    volume_index = pf_toupper(drive) - 'A';
    if (volume_index < 0 || volume_index >= 26) {
        volume = 0;
    } else {
        volume = &pf_vol_set.volumes[volume_index];
    }
    PFVOL_UPDATE_DRIVER_REQUESTS(volume, error);
    config[0] = 0;
    config[1] = volume->reserved_1f88;
    if ((volume->reserved_1f88 & 1) == 0) {
        config[1] |= 2;
    }
    config[2] = volume->num_fat_buf_size;
    config[3] = volume->num_data_buf_size;
    return 0;
}

s32 PFVOL_setcode(const PFVOL_CHARCODE* code_set) {
    if (pf_vol_set.num_attached_drives > 0) {
        pf_vol_set.last_error = 36;
        return 36;
    }
    pf_vol_set.codeset.oem2unicode = code_set->oem2unicode;
    pf_vol_set.codeset.unicode2oem = code_set->unicode2oem;
    pf_vol_set.codeset.oem_char_width = code_set->oem_char_width;
    pf_vol_set.codeset.is_oem_mb_char = code_set->is_oem_mb_char;
    pf_vol_set.codeset.unicode_char_width = code_set->unicode_char_width;
    pf_vol_set.codeset.is_unicode_mb_char = code_set->is_unicode_mb_char;
    return 0;
}

s32 PFVOL_regctx(void) {
    PFVOL_CONTEXT* context;
    s32 context_id;
    s32 error;
    u32 context_index;
    u32 free_context_index = 0;

    error = PFSYS_GetCurrentContextID(&context_id);
    if (error != 0) {
        pf_vol_set.last_error = 26;
        return 26;
    }
    context = pf_vol_set.context;
    for (context_index = 1; context_index <= 3; context_index++) {
        if ((context->stat & 1) != 0) {
            if (context->context_id == context_id) {
                return 0;
            }
        } else if (free_context_index == 0) {
            free_context_index = context_index;
        }
        context++;
    }
    if (free_context_index == 0) {
        pf_vol_set.last_error = 26;
        return 26;
    }
    context = &pf_vol_set.context[free_context_index - 1];
    context->stat = 1;
    context->context_id = context_id;
    return 0;
}

s32 PFVOL_unregctx(void) {
    s32 context_id;
    s32 error;
    u32 context_index;
    u32 volume_index;
    u32 current_dir_index;
    u32 current_volume_index;
    s32 found = 0;

    error = PFSYS_GetCurrentContextID(&context_id);
    if (error != 0) {
        pf_vol_set.last_error = 26;
        return 26;
    }
    for (context_index = 0; context_index < 3; context_index++) {
        if ((pf_vol_set.context[context_index].stat & 1) != 0 &&
            pf_vol_set.context[context_index].context_id == context_id) {
            pf_vol_set.context[context_index].stat &= ~1;
            found = 1;
            for (current_volume_index = 0; current_volume_index < 3; current_volume_index++) {
                if ((pf_vol_set.context_volume[current_volume_index].stat & 1) != 0 &&
                    pf_vol_set.context_volume[current_volume_index].context_id == context_id) {
                    pf_vol_set.context_volume[current_volume_index].stat &= ~1;
                }
            }
            for (volume_index = 0; volume_index < 26; volume_index++) {
                for (current_dir_index = 1; current_dir_index < 4; current_dir_index++) {
                    if ((pf_vol_set.volumes[volume_index].current_dir[current_dir_index].stat & 1) != 0 &&
                        pf_vol_set.volumes[volume_index].current_dir[current_dir_index].context_id == context_id) {
                        pf_vol_set.volumes[volume_index].current_dir[current_dir_index].stat &= ~1;
                        break;
                    }
                }
            }
            break;
        }
    }
    if (found == 0) {
        pf_vol_set.last_error = 26;
        return 26;
    }
    return 0;
}

s32 PFVOL_setencode(u32 mode) {
    pf_vol_set.setting = pf_vol_set.setting & ~3 | mode;
    return 0;
}
