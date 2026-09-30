#ifndef PF_FA_VOLUME_LAYOUT_H
#define PF_FA_VOLUME_LAYOUT_H
#define PRFILE2_VFMOD_PF_VOLUME_H
#include <private/vf/PrFILE2/fatfs/pf_entry.h>
#include <private/vf/PrFILE2/driver/pf_driver.h>
#include <private/vf/PrFILE2/fatfs/pf_devinf.h>
typedef struct PF_CHARCODE {
    pf_s32 (*oem2unicode)(const pf_s8*, pf_u16*);          
    pf_s32 (*unicode2oem)(const pf_u16*, pf_s8*);          
    pf_s32 (*oem_char_width)(const pf_s8*);                
    pf_bool (*is_oem_mb_char)(const pf_s8, pf_bool);       
    pf_s32 (*unicode_char_width)(const pf_u16*);           
    pf_bool (*is_unicode_mb_char)(const pf_u16, pf_bool);  
} PF_CHARCODE;

typedef struct PF_BPB {
    pf_u16 bytes_per_sector;         
    pf_u16 num_reserved_sectors;     
    pf_u16 num_root_dir_entries;     
    pf_u8 sectors_per_cluster;       
    pf_u8 num_FATs;                  
    pf_u32 total_sectors;            
    pf_u32 sectors_per_FAT;          
    pf_u32 root_dir_cluster;         
    pf_u16 fs_info_sector;           
    pf_u16 backup_boot_sector;       
    pf_u16 ext_flags;                
    pf_u8 media;                     
    PF_FAT_TYPE fat_type;            
    pf_u8 log2_bytes_per_sector;     
    pf_u8 log2_sectors_per_cluster;  
    pf_u8 num_active_FATs;           
    pf_u16 num_root_dir_sectors;     
    pf_u32 active_FAT_sector;        
    pf_u32 first_root_dir_sector;    
    pf_u32 first_data_sector;        
    pf_u32 num_clusters;             
} PF_BPB;

typedef struct PF_CUR_DIR {
    pf_u32 stat;           
    pf_s32 context_id;     
    PF_DIR_ENT directory;  
} PF_CUR_DIR;


typedef pf_s32 (*PF_VOLUME_CB)(pf_s32);
struct PF_VOLUME {
    PF_BPB bpb;
    pf_u32 num_free_clusters;
    pf_u32 last_free_cluster;
    pf_u8 file_and_directory_state[0x1624 - 0x40];
    PF_SECTOR_CACHE cache;
    pf_s8 label[12];
    PF_CUR_DIR current_dir[4];
    struct {
        pf_u32 tracker_size;
        pf_u32 tracker_max;
        pf_u32* tracker_bits;
    } tail_entry;
    pf_s32 last_error;
    pf_s32 last_driver_error;
    pf_u32 file_config;
    pf_u16 flags;
    pf_s8 drv_char;
    pf_u16 fsi_flag;
    PF_CLUSTER_LINK_VOL cluster_link;
    void* p_part;
    void (*p_callback)();
    const pf_u8* format_param;
};
typedef struct PF_FA_CUR_VOLUME {
    pf_u32 stat;
    pf_s32 context_id;
    PF_VOLUME* p_vol;
} PF_FA_CUR_VOLUME;
typedef struct PF_VOLUME_SET {
    pf_u32 flags;
    pf_u32 reserved;
    PF_VOLUME* current_volume;
    PF_FA_CUR_VOLUME context_volumes[3];
    pf_s32 num_attached_drives;
    pf_s32 num_mounted_volumes;
    pf_u32 config;
    void* param;
    pf_s32 last_error;
    pf_s32 last_driver_error;
    PF_CHARCODE codeset;
    pf_u32 setting;
    pf_s32 context_id;
    pf_u32 context_state[2];
    struct { pf_u32 stat; pf_s32 context_id; } contexts[3];
    PF_VOLUME volumes[26];
} PF_VOLUME_SET;
extern PF_VOLUME_SET pf_vol_set;
#endif
