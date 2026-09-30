#include <private/fa/pdm.h>
extern void* pf_memset(void*, pf_u8, pf_u32);
PDM_DISK_SET pdm_disk_set;
PDM_DISK_TBL pdm_drv_tbl[26];

pf_s32 pdm_disk_convert_sector_into_block(PDM_DISK* p_disk, pf_u32 start, pf_u32 count, pf_u32 bytes_per_sector, pf_u32* p_start, pf_u32* p_count) {
    pf_u32 ratio;
    pf_s32 err = 0;
    *p_start = start;
    *p_count = count;
    if (bytes_per_sector > 512) {
        ratio = (pf_u16)bytes_per_sector >> 9;
        if (ratio == 2) { *p_start <<= 1; }
        else if (ratio == 4) { *p_start <<= 2; }
        else if (ratio == 8) { *p_start <<= 3; }
        if (ratio == 2) { *p_count <<= 1; }
        else if (ratio == 4) { *p_count <<= 2; }
        else if (ratio == 8) { *p_count <<= 3; }
    } else if (bytes_per_sector < 512) { err = 4; }
    return err;
}
pf_s32 pdm_disk_convert_block_into_sector(PDM_DISK* p_disk, pf_u32 start, pf_u32 count, pf_u32 bytes_per_sector, pf_u32* p_start, pf_u32* p_count) {
    pf_u32 ratio;
    pf_s32 err = 0;
    *p_start = start;
    *p_count = count;
    if (bytes_per_sector > 512) {
        ratio = (pf_u16)bytes_per_sector >> 9;
        if (ratio == 2) { *p_start >>= 1; }
        else if (ratio == 4) { *p_start >>= 2; }
        else if (ratio == 8) { *p_start >>= 3; }
        if (ratio == 2) { *p_count >>= 1; }
        else if (ratio == 4) { *p_count >>= 2; }
        else if (ratio == 8) { *p_count >>= 3; }
    } else if (bytes_per_sector < 512) { err = 4; }
    return err;
}
pf_s32 pdm_disk_init_disk_manager(void) {
    pf_memset(&pdm_disk_set, 0, sizeof(pdm_disk_set));
    return 0;
}
pf_s32 pdm_disk_add_disk(PDM_INIT_DISK* p_init_disk_tbl, PDM_DISK** pp_disk) {
    PDM_DISK_TBL* p_driver;
    pf_u16 disk_no;
    PDM_DISK* p_disk;
    *pp_disk = PF_NULL;
    if (pdm_disk_set.num_allocated_disk >= 26) { return 8; }
    for (disk_no = 0; disk_no < 26; disk_no++) {
        if (!(pdm_disk_set.disk[disk_no].status & 1)) { break; }
    }
    if (disk_no >= 26) { return 8; }
    p_driver = &pdm_drv_tbl[disk_no];
    p_init_disk_tbl->p_func(p_driver, p_init_disk_tbl->ui_ext);
    p_disk = &pdm_disk_set.disk[disk_no];
    p_disk->disk_tbl = *p_driver;
    p_disk->status |= 1;
    pdm_disk_set.num_allocated_disk++;
    *pp_disk = p_disk;
    return 0;
}
pf_s32 pdm_disk_del_disk(PDM_DISK* p_disk) {
    if (p_disk->init_count != 0) { return 16; }
    if (p_disk->mount_count != 0) { return 17; }
    p_disk->status &= ~1;
    pdm_disk_set.num_allocated_disk--;
    return 0;
}
pf_s32 pdm_disk_set_disk(PDM_DISK* p_disk, PDM_PARTITION* p_part) {
    p_disk->p_cur_part = p_part;
    return 0;
}
pf_s32 pdm_disk_get_media_attribute(PDM_DISK* p_disk, PDM_DISK_INFO* p_info) {
    *p_info = p_disk->disk_info;
    return 0;
}
pf_s32 pdm_disk_get_media_bps(PDM_DISK* p_disk, pf_u16* p_bps) {
    *p_bps = p_disk->disk_info.bytes_per_sector;
    return 0;
}
pf_s32 pdm_disk_init(PDM_DISK* p_disk) {
    pf_s32 err;
    if (p_disk->init_count == 0) {
        err = p_disk->disk_tbl.p_func->init(p_disk);
        if (err != 0) { pdm_part_set_driver_error_code(p_disk->p_cur_part, err); return 21; }
    }
    p_disk->init_count++;
    return 0;
}
pf_s32 pdm_disk_mount(PDM_DISK* p_disk) {
    pf_s32 err;
    if (p_disk->mount_count == 0) {
        err = p_disk->disk_tbl.p_func->mount(p_disk);
        if (err != 0) { pdm_part_set_driver_error_code(p_disk->p_cur_part, err); return 21; }
        err = p_disk->disk_tbl.p_func->get_disk_info(p_disk, &p_disk->disk_info);
        if (err != 0) {
            pdm_part_set_driver_error_code(p_disk->p_cur_part, err);
            p_disk->disk_tbl.p_func->unmount(p_disk);
            return 21;
        }
        if (p_disk->disk_info.media_attr & 1) { p_disk->status |= 2; }
        else { p_disk->status &= ~2; }
    }
    p_disk->mount_count++;
    return 0;
}
pf_s32 pdm_disk_format(PDM_DISK* p_disk, const pf_u8* param) {
    pf_s32 err;
    err = p_disk->disk_tbl.p_func->format(p_disk, param);
    if (err != 0) { pdm_part_set_driver_error_code(p_disk->p_cur_part, err); return 21; }
    return 0;
}
pf_s32 pdm_disk_physical_read(PDM_DISK* p_disk, pf_u8* buf, pf_u32 sector, pf_u32 count, pf_u32 bps, pf_u32* p_success) {
    pf_s32 err;
    pf_u32 block;
    pf_u32 num_blocks;
    pf_u32 converted_sector;
    err = pdm_disk_convert_sector_into_block(p_disk, sector, count, bps, &block, &num_blocks);
    if (err != 0) { return err; }
    err = p_disk->disk_tbl.p_func->physical_read(p_disk, buf, block, num_blocks, p_success);
    pdm_disk_convert_block_into_sector(p_disk, block, *p_success, bps, &converted_sector, p_success);
    if (err != 0) { pdm_part_set_driver_error_code(p_disk->p_cur_part, err); return 21; }
    return 0;
}
pf_s32 pdm_disk_physical_write(PDM_DISK* p_disk, const pf_u8* buf, pf_u32 sector, pf_u32 count, pf_u32 bps, pf_u32* p_success) {
    pf_s32 err;
    pf_u32 block;
    pf_u32 num_blocks;
    pf_u32 converted_sector;
    err = pdm_disk_convert_sector_into_block(p_disk, sector, count, bps, &block, &num_blocks);
    if (err != 0) { return err; }
    err = p_disk->disk_tbl.p_func->physical_write(p_disk, buf, block, num_blocks, p_success);
    pdm_disk_convert_block_into_sector(p_disk, block, *p_success, bps, &converted_sector, p_success);
    if (err != 0) { pdm_part_set_driver_error_code(p_disk->p_cur_part, err); return 21; }
    return 0;
}
pf_s32 pdm_disk_unmount(PDM_DISK* p_disk, pf_u32 mode) {
    pf_s32 err = 0;
    if (p_disk->mount_count == 1) {
        err = p_disk->disk_tbl.p_func->unmount(p_disk);
        if (err != 0) { pdm_part_set_driver_error_code(p_disk->p_cur_part, err); err = 21; }
    } else if (p_disk->mount_count == 0) { return 14; }
    if (err == 0 || mode == 1) { p_disk->mount_count--; }
    return err;
}
pf_s32 pdm_disk_finalize(PDM_DISK* p_disk) {
    pf_s32 err;
    if (p_disk->init_count == 1) {
        err = p_disk->disk_tbl.p_func->finalize(p_disk);
        if (err != 0) { pdm_part_set_driver_error_code(p_disk->p_cur_part, err); return 21; }
    } else if (p_disk->init_count == 0) { return 13; }
    p_disk->init_count--;
    return 0;
}
void pdm_disk_notify_media_eject(PDM_DISK* p_disk) {
    p_disk->status &= ~4;
    pdm_part_set_change_media_state(p_disk, 0);
}
void pdm_disk_notify_media_insert(PDM_DISK* p_disk) {
    p_disk->status |= 4;
    pdm_part_set_change_media_state(p_disk, 1);
}
