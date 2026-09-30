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
    u32 last_free_cluster;
    u8 gap_0040[0xD0C];
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
    s8 drv_char;
    u8 drive_state;
    u16 fsi_flag;
    u16 reserved_1f92;
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

extern PFVOL_SET pf_vol_set;
extern PFVOL_VOLUME* PFVOL_GetVolumeFromDrvChar(s8 drive);

s32 PFVOL_iswriteprotected(s8 drive, u32* protected_status) {
    PFVOL_VOLUME* volume = PFVOL_GetVolumeFromDrvChar(drive);
    if (!(volume->flags & 8)) {
        pf_vol_set.last_error = 9;
        volume->last_error = 9;
        return 9;
    }
    if (volume->flags & 2) {
        *protected_status = 1;
    } else {
        *protected_status = 0;
    }
    return 0;
}
