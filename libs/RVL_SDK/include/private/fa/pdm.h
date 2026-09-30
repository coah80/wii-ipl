#ifndef PF_FA_PDM_H
#define PF_FA_PDM_H
#include <private/vf/PrFILE2/dskmng/pdm_types.h>
typedef struct PDM_PARTITION PDM_PARTITION;
typedef struct PDM_CALLBACK {
    void (*insert)(PDM_PARTITION*);
    void (*eject)(PDM_PARTITION*);
} PDM_CALLBACK;
struct PDM_PARTITION {
    pf_u32 status;
    PDM_DISK* p_disk;
    pf_u32 part_id;
    pf_u32 start_sector;
    pf_u32 total_sector;
    pf_s32 driver_last_error;
    pf_u32 lock_state[2];
    PDM_CALLBACK callbacks;
};
struct PDM_DISK {
    pf_u32 status;
    PDM_DISK_TBL disk_tbl;
    pf_s16 init_count;
    pf_s16 mount_count;
    PDM_DISK* lock_handle;
    pf_u32 lock_count;
    PDM_DISK_INFO disk_info;
    PDM_PARTITION* p_cur_part;
};
typedef struct PDM_DISK_SET {
    pf_u16 num_partition;
    pf_u16 num_allocated_disk;
    PDM_DISK disk[26];
    PDM_PARTITION partition[26];
} PDM_DISK_SET;
extern PDM_DISK_SET pdm_disk_set;
extern PDM_DISK_TBL pdm_drv_tbl[26];
void pdm_part_set_driver_error_code(PDM_PARTITION*, pf_s32);
void pdm_part_set_change_media_state(PDM_DISK*, pf_bool);
pf_s32 pdm_disk_convert_sector_into_block(PDM_DISK*, pf_u32, pf_u32, pf_u32, pf_u32*, pf_u32*);
pf_s32 pdm_disk_convert_block_into_sector(PDM_DISK*, pf_u32, pf_u32, pf_u32, pf_u32*, pf_u32*);
pf_s32 pdm_disk_add_disk(PDM_INIT_DISK*, PDM_DISK**);
pf_s32 pdm_disk_del_disk(PDM_DISK*);
pf_s32 pdm_disk_set_disk(PDM_DISK*, PDM_PARTITION*);
pf_s32 pdm_disk_get_media_attribute(PDM_DISK*, PDM_DISK_INFO*);
pf_s32 pdm_disk_get_media_bps(PDM_DISK*, pf_u16*);
pf_s32 pdm_disk_init(PDM_DISK*);
pf_s32 pdm_disk_mount(PDM_DISK*);
pf_s32 pdm_disk_format(PDM_DISK*, const pf_u8*);
pf_s32 pdm_disk_physical_read(PDM_DISK*, pf_u8*, pf_u32, pf_u32, pf_u32, pf_u32*);
pf_s32 pdm_disk_physical_write(PDM_DISK*, const pf_u8*, pf_u32, pf_u32, pf_u32, pf_u32*);
pf_s32 pdm_disk_unmount(PDM_DISK*, pf_u32);
pf_s32 pdm_disk_finalize(PDM_DISK*);
#endif
