// Matching build uses pdm_partition.s (retail extract); keep C for reference.
#include <private/fa/pdm.h>
#include <revolution/types.h>
#define MBR_WORD(buf, offset) (((pf_u32)(buf)[(offset) + 3] << 24) + ((pf_u32)(buf)[(offset) + 2] << 16) + ((pf_u32)(buf)[(offset) + 1] << 8) + (buf)[offset])
static inline pf_u16 read_boot_u16(pf_u8* buf, pf_u32 offset) {
    if ((pf_u32)&buf[offset] & 1) { return (buf[offset + 1] << 8) | buf[offset]; }
    return PF_SWAP_16(*(pf_u16*)&buf[(offset + 1) & ~1]);
}

pf_s32 pdm_part_is_master_boot_sector(pf_u8* buf, pf_u32 total, pf_bool* p_is_mbr) {
    pf_s16 index;
    pf_u32 start[4];
    pf_u32 count[4];
    pf_u32* p_start;
    pf_u32* p_count;
    *p_is_mbr = 0;
    if (buf[510] != 0x55 || buf[511] != 0xAA) { return 2; }
    p_start = start;
    p_count = count;
    for (index = 0; index < 4; index++) {
        *p_start = 0;
        *p_start = (((pf_u32)buf[456] << 16) + buf[454]) + (((pf_u32)buf[457] << 24) + ((pf_u32)buf[455] << 8));
        *p_count = (((pf_u32)buf[460] << 16) + buf[458]) + (((pf_u32)buf[461] << 24) + ((pf_u32)buf[459] << 8));
        if (*p_start != 0 && *p_count != 0) {
            if (index == 0) { *p_is_mbr = 1; }
        } else {
            if (index == 0) { return 2; }
        }
        p_start++;
        p_count++;
        buf += 16;
    }
    p_start = start;
    p_count = count;
    for (index = 0; index < 4; index++) {
        if (*p_start + *p_count > total) {
            if (index == 0) { *p_is_mbr = 0; }
            return 2;
        }
        p_start++;
        p_count++;
    }
    return 0;
}
pf_bool pdm_part_is_boot_sector(pf_u8* buf) {
    pf_u16 byte_per_sector;
    pf_u16 sector_per_cluster;
    pf_u8 media;
    pf_bool is_boot;

    is_boot = PF_TRUE;
    if ((buf[0x00] != 0xEB || buf[0x2] != 0x90) && buf[0x0] != 0xE9) {
        is_boot = PF_FALSE;
    }
    if (buf[0x1FE] != 0x55 || buf[0x1FF] != 0xAA) {
        is_boot = PF_FALSE;
    }
    byte_per_sector = read_boot_u16(buf, 0xB);
    if (byte_per_sector != 0x200 && byte_per_sector != 0x400 && byte_per_sector != 0x800 && byte_per_sector != 0x1000) {
        is_boot = PF_FALSE;
    }
    sector_per_cluster = buf[0xD];
    if (sector_per_cluster != 1 && sector_per_cluster != 2 && sector_per_cluster != 4 && sector_per_cluster != 8 && sector_per_cluster != 0x10 &&
        sector_per_cluster != 0x20 && sector_per_cluster != 0x40 && sector_per_cluster != 0x80) {
        is_boot = PF_FALSE;
    }
    media = buf[0x15];
    if (media != 0xF0 && media != 0xF8 && media != 0xF9 && media != 0xFA && media != 0xFB && media != 0xFC && media != 0xFD && media != 0xFE &&
        media != 0xFF) {
        is_boot = PF_FALSE;
    }
    return is_boot;
}

pf_s32 pdm_part_get_start_sector(PDM_PARTITION* p_part) {
    pf_u32 part_index = 0;
    pf_u32 requested = p_part->part_id;
    pf_u32 start[4];
    pf_u32 count[4];
    pf_u16 index;
    pf_u16 extended_index;
    pf_u32 base;
    pf_u32 sector;
    pf_u32 length;
    pf_bool is_mbr;
    pf_u32 success;
    pf_s32 err;
    pf_u8 buf[512] __attribute__((aligned(32)));
    p_part->start_sector = 0;
    p_part->total_sector = p_part->p_disk->disk_info.total_sectors;
    err = pdm_disk_physical_read(p_part->p_disk, buf, 0, 1, 512, &success);
    if (err != 0) { return err; }
    pdm_part_is_master_boot_sector(buf, p_part->p_disk->disk_info.total_sectors, &is_mbr);
    if (is_mbr) {
        start[0] = MBR_WORD(buf, 454);
        start[1] = MBR_WORD(buf, 470);
        start[2] = MBR_WORD(buf, 486);
        start[3] = MBR_WORD(buf, 502);
        count[0] = MBR_WORD(buf, 458);
        count[1] = MBR_WORD(buf, 474);
        count[2] = MBR_WORD(buf, 490);
        count[3] = MBR_WORD(buf, 506);
        part_index = 0;
        for (index = 0; index < 4; index++) {
            sector = start[index];
            length = count[index];
            if (sector == 0 || length == 0) { return 7; }
            err = pdm_disk_physical_read(p_part->p_disk, buf, sector, 1, 512, &success);
            if (err != 0) { return err; }
            pdm_part_is_master_boot_sector(buf, p_part->p_disk->disk_info.total_sectors, &is_mbr);
            if (is_mbr) {
                base = start[index];
                sector = base;
                for (extended_index = 0; extended_index < 2; extended_index++) {
                    if (extended_index == 0) {
                        sector = sector + MBR_WORD(buf, 454);
                        length = MBR_WORD(buf, 458);
                        err = pdm_disk_physical_read(p_part->p_disk, buf, sector, 1, 512, &success);
                        if (err != 0) { return err; }
                        if (requested == part_index) { p_part->start_sector = sector; p_part->total_sector = length; return 0; }
                        part_index++;
                    } else {
                        sector = base + MBR_WORD(buf, 470);
                        length = MBR_WORD(buf, 474);
                        if (sector == 0 || length == 0) { break; }
                        err = pdm_disk_physical_read(p_part->p_disk, buf, sector, 1, 512, &success);
                        if (err != 0) { return err; }
                        pdm_part_is_master_boot_sector(buf, p_part->p_disk->disk_info.total_sectors, &is_mbr);
                        if (!is_mbr) { break; }
                        extended_index = 0;
                    }
                }
            } else {
                if (requested == part_index) { p_part->start_sector = sector; p_part->total_sector = length; break; }
                part_index++;
            }
        }
    } else {
        if (requested >= 2) { return 7; }
        p_part->start_sector = part_index;
        p_part->total_sector = p_part->p_disk->disk_info.total_sectors;
    }
    return 0;
}
pf_u32 pdm_part_chg_ltop(PDM_PARTITION* p_part, pf_u32 sector, pf_u32 bps) {
    pf_u16 media_bps;
    pf_u32 ratio;
    pf_u32 start;
    pdm_disk_get_media_bps(p_part->p_disk, &media_bps);
    if (bps == media_bps) { return sector + p_part->start_sector; }
    start = p_part->start_sector;
    ratio = media_bps >> 9;
    if (ratio == 2) { start <<= 1; }
    else if (ratio == 4) { start <<= 2; }
    else if (ratio == 8) { start <<= 3; }
    ratio = (pf_u16)bps >> 9;
    if (ratio == 2) { start >>= 1; }
    else if (ratio == 4) { start >>= 2; }
    else if (ratio == 8) { start >>= 3; }
    return sector + start;
}
pf_s32 pdm_part_get_partition(PDM_DISK* p_disk, pf_u32 id, PDM_PARTITION** pp_part) {
    pf_s32 err;
    pf_u16 index;
    *pp_part = PF_NULL;
    if (pdm_disk_set.num_partition >= 26) { return 10; }
    for (index = 0; index < 26; index++) {
        if (!(pdm_disk_set.partition[index].status & 1)) { break; }
    }
    if (index == 26) { return 10; }
    err = pdm_disk_set_disk(p_disk, &pdm_disk_set.partition[index]);
    if (err != 0) { return err; }
    pdm_disk_set.num_partition++;
    pdm_disk_set.partition[index].status |= 1;
    pdm_disk_set.partition[index].p_disk = p_disk;
    pdm_disk_set.partition[index].part_id = id;
    *pp_part = &pdm_disk_set.partition[index];
    return 0;
}
pf_s32 pdm_part_release_partition(PDM_PARTITION* p_part) {
    p_part->status &= ~1;
    pdm_disk_set.num_partition--;
    return 0;
}
pf_bool pdm_part_is_attached_partition(PDM_PARTITION* p_part) { return (p_part->status >> 2) & 1; }
void pdm_part_set_driver_error_code(PDM_PARTITION* p_part, pf_s32 err) { p_part->driver_last_error = err; }
pf_s32 pdm_part_get_driver_error_code(PDM_PARTITION* p_part) { return p_part->driver_last_error; }
pf_s32 pdm_part_get_media_attribute(PDM_PARTITION* p_part, PDM_DISK_INFO* p_info) {
    pf_s32 err = pdm_disk_get_media_attribute(p_part->p_disk, p_info);
    if (err != 0) { return err; }
    return 0;
}
pf_s32 pdm_part_init(PDM_PARTITION* p_part) {
    pf_s32 err;
    if (!(p_part->status & 4)) {
        err = pdm_disk_set_disk(p_part->p_disk, p_part);
        if (err != 0) { return err; }
        err = pdm_disk_init(p_part->p_disk);
        if (err != 0) { return err; }
    } else { return 11; }
    p_part->status |= 4;
    return 0;
}
pf_s32 pdm_part_mount(PDM_PARTITION* p_part) {
    pf_s32 err;
    if (!(p_part->status & 8)) {
        err = pdm_disk_set_disk(p_part->p_disk, p_part);
        if (err != 0) { return err; }
        err = pdm_disk_mount(p_part->p_disk);
        if (err != 0) { return err; }
        err = pdm_part_get_start_sector(p_part);
        if (err != 0) { pdm_disk_unmount(p_part->p_disk, 0); return err; }
    } else { return 12; }
    p_part->status &= ~2;
    p_part->status |= 8;
    return 0;
}
pf_s32 pdm_part_format(PDM_PARTITION* p_part, const pf_u8* param) {
    pf_s32 err;
    err = pdm_disk_set_disk(p_part->p_disk, p_part);
    if (err != 0) { return err; }
    err = pdm_disk_format(p_part->p_disk, param);
    if (err != 0) { return err; }
    return 0;
}
pf_s32 pdm_part_logical_read(PDM_PARTITION* p_part, pf_u8* buf, pf_u32 sector, pf_u32 count, pf_u32 bps, pf_u32* p_success) {
    pf_s32 err;
    pf_u32 physical_sector;
    if ((p_part->status & 8) != 8 || (p_part->status & 2) == 2) { return 15; }
    err = pdm_disk_set_disk(p_part->p_disk, p_part);
    if (err != 0) { return err; }
    if (p_part->total_sector <= sector) { return 18; }
    if (p_part->total_sector < sector + count) { count -= (sector + count) - p_part->total_sector; }
    physical_sector = pdm_part_chg_ltop(p_part, sector, bps);
    err = pdm_disk_physical_read(p_part->p_disk, buf, physical_sector, count, bps, p_success);
    if (err != 0) { return err; }
    return 0;
}
pf_s32 pdm_part_logical_write(PDM_PARTITION* p_part, const pf_u8* buf, pf_u32 sector, pf_u32 count, pf_u32 bps, pf_u32* p_success) {
    pf_s32 err;
    pf_u32 physical_sector;
    if ((p_part->status & 8) != 8 || (p_part->status & 2) == 2) { return 15; }
    err = pdm_disk_set_disk(p_part->p_disk, p_part);
    if (err != 0) { return err; }
    if (p_part->total_sector <= sector) { return 18; }
    if (p_part->total_sector < sector + count) { count -= (sector + count) - p_part->total_sector; }
    physical_sector = pdm_part_chg_ltop(p_part, sector, bps);
    err = pdm_disk_physical_write(p_part->p_disk, buf, physical_sector, count, bps, p_success);
    if (err != 0) { return err; }
    return 0;
}
pf_s32 pdm_part_unmount(PDM_PARTITION* p_part, pf_u32 mode) {
    pf_s32 err;
    pf_s32 result = 0;
    if (p_part->status & 8) {
        err = pdm_disk_set_disk(p_part->p_disk, p_part);
        if (err != 0) { return err; }
        err = pdm_disk_unmount(p_part->p_disk, mode);
        if (err != 0) { result = err; }
    } else { result = 14; }
    if (result == 0 || mode == 1) { p_part->status &= ~2; p_part->status &= ~8; }
    return result;
}
pf_s32 pdm_part_finalize(PDM_PARTITION* p_part) {
    pf_s32 err;
    if (p_part->status & 4) {
        err = pdm_disk_set_disk(p_part->p_disk, p_part);
        if (err != 0) { return err; }
        err = pdm_disk_finalize(p_part->p_disk);
        if (err != 0) { return err; }
    } else { return 13; }
    p_part->status &= ~4;
    return 0;
}
pf_s32 pdm_part_register_callback(PDM_PARTITION* p_part, PDM_CALLBACK* callbacks) {
    p_part->callbacks.insert = callbacks->insert;
    p_part->callbacks.eject = callbacks->eject;
    return 0;
}
pf_s32 pdm_part_unregister_callback(PDM_PARTITION* p_part) {
    p_part->callbacks.insert = PF_NULL;
    p_part->callbacks.eject = PF_NULL;
    return 0;
}
void pdm_part_set_change_media_state(PDM_DISK* p_disk, pf_bool is_inserted) {
    pf_u16 index;
    for (index = 0; index < 26; index++) {
        if ((pdm_disk_set.partition[index].status & 1) && pdm_disk_set.partition[index].p_disk == p_disk) {
            PDM_PARTITION* p_part = &pdm_disk_set.partition[index];
            p_part->status |= 2;
            if (is_inserted == 0 && pdm_disk_set.partition[index].callbacks.eject != PF_NULL) {
                pdm_disk_set.partition[index].callbacks.eject(p_part);
            } else if (pdm_disk_set.partition[index].callbacks.insert != PF_NULL) {
                pdm_disk_set.partition[index].callbacks.insert(p_part);
            }
        }
    }
}
