#include <revolution/types.h>

typedef struct PDM_DISK {
    u8 pad_00[0x18];
    u32 num_sectors; // +0x18
    u8 pad_1C[0x8];
} PDM_DISK;

typedef struct PDM_PARTITION PDM_PARTITION;

typedef void (*PDM_PART_CALLBACK)(PDM_PARTITION* p_part);

struct PDM_PARTITION {
    u32 stat;                      // +0x00
    PDM_DISK* p_disk;              // +0x04
    u32 part_no;                   // +0x08
    u32 start_sector;              // +0x0C
    u32 num_sectors;               // +0x10
    s32 driver_error_code;         // +0x14
    u32 field_18;                  // +0x18
    u32 field_1C;                  // +0x1C
    PDM_PART_CALLBACK callback[2]; // +0x20, +0x24
};

typedef struct PDM_DISK_SET {
    u16 num_partition;             // +0x00
    u8 pad_02[0x4E2];              // +0x02
    PDM_PARTITION part_table[0x1A]; // +0x4E4
} PDM_DISK_SET;

extern PDM_DISK_SET pdm_disk_set;

extern s32 pdm_disk_set_disk(PDM_DISK* p_disk, PDM_PARTITION* p_part);
extern s32 pdm_disk_init(PDM_DISK* p_disk);
extern s32 pdm_disk_mount(PDM_DISK* p_disk);
extern s32 pdm_disk_unmount(PDM_DISK* p_disk, u32 force);
extern s32 pdm_disk_format(PDM_DISK* p_disk, u8* param);
extern s32 pdm_disk_finalize(PDM_DISK* p_disk);
extern s32 pdm_disk_get_media_bps(PDM_DISK* p_disk, u16* p_bps);
extern s32 pdm_disk_get_media_attribute(PDM_DISK* p_disk);
extern s32 pdm_disk_physical_read(PDM_DISK* p_disk, u8* buf, u32 sector, u32 num_sector, u16 bps, u32* p_num_success);
extern s32 pdm_disk_physical_write(PDM_DISK* p_disk, const u8* buf, u32 sector, u32 num_sector, u16 bps, u32* p_num_success);

s32 pdm_part_is_master_boot_sector(const u8* p_sector, u32 num_sector, u32* p_is_mbr) {
    u32 sector_num[4];
    u32 start_sector[4];
    u32* p_num;
    u32* p_start;
    const u8* pe;
    s16 i;

    *p_is_mbr = 0;
    if (p_sector[0x1FE] != 0x55 || p_sector[0x1FF] != 0xAA) {
        return 2;
    }

    pe = p_sector;
    p_start = start_sector;
    p_num = sector_num;
    for (i = 0; i < 4; i++) {
        *p_start = 0;
        *p_start = (pe[0x1C9] * 0x1000000 + pe[0x1C7] * 0x100) + (pe[0x1C8] * 0x10000 + pe[0x1C6]);
        *p_num = (pe[0x1CD] * 0x1000000 + pe[0x1CB] * 0x100) + (pe[0x1CC] * 0x10000 + pe[0x1CA]);
        if (*p_start != 0 && *p_num != 0) {
            if (i == 0) {
                *p_is_mbr = 1;
            }
        } else {
            if (i == 0) {
                return 2;
            }
        }
        p_num++;
        pe += 0x10;
        p_start++;
    }

    p_num = sector_num;
    p_start = start_sector;
    for (i = 0; i < 4; i++) {
        if (*p_start + *p_num > num_sector) {
            if (i == 0) {
                *p_is_mbr = 0;
            }
            return 2;
        }
        p_start++;
        p_num++;
    }
    return 0;
}

s32 pdm_part_is_boot_sector(const u8* p_sector) {
    u16 bps;
    s32 is_boot;

    is_boot = 1;
    if (!((p_sector[0] == 0xEB && p_sector[2] == 0x90) || p_sector[0] == 0xE9)) {
        is_boot = 0;
    }
    if (!(p_sector[0x1FE] == 0x55 && p_sector[0x1FF] == 0xAA)) {
        is_boot = 0;
    }
    if ((u32)&p_sector[0xB] & 1) {
        bps = p_sector[0xB] | p_sector[0xC] << 8;
    } else {
        u16 tmp;
        tmp = *(u16*)&p_sector[0xC];
        bps = ((tmp >> 8) & 0xFF) | ((tmp << 8) & 0xFF00);
    }
    if (bps != 0x200 && bps != 0x400 && bps != 0x800 && bps != 0x1000) {
        is_boot = 0;
    }
    if (p_sector[0xD] != 1 && p_sector[0xD] != 2 && p_sector[0xD] != 4 && p_sector[0xD] != 8 &&
        p_sector[0xD] != 0x10 && p_sector[0xD] != 0x20 && p_sector[0xD] != 0x40 && p_sector[0xD] != 0x80) {
        is_boot = 0;
    }
    if (p_sector[0x15] != 0xF0 && p_sector[0x15] != 0xF8 && p_sector[0x15] != 0xF9 && p_sector[0x15] != 0xFA &&
        p_sector[0x15] != 0xFB && p_sector[0x15] != 0xFC && p_sector[0x15] != 0xFD && p_sector[0x15] != 0xFE &&
        p_sector[0x15] != 0xFF) {
        is_boot = 0;
    }
    return is_boot;
}

s32 pdm_part_get_start_sector(PDM_PARTITION* p_part) {
    u8 buf[0x200] ATTRIBUTE_ALIGN(32);
    u32 num_success;
    u32 is_mbr;
    u32 start_sector[4];
    u32 sector_num[4];
    u32 rel_sector;
    u32 rel_num;
    u32 rel_start;
    u32 rel_cnt;
    u32 base;
    u32 part_no;
    u32 cnt;
    u16 i;
    u16 j;
    s32 err;

    cnt = 0;
    p_part->start_sector = 0;
    part_no = p_part->part_no;
    p_part->num_sectors = p_part->p_disk->num_sectors;

    err = pdm_disk_physical_read(p_part->p_disk, buf, 0, 1, 0x200, &num_success);
    if (err != 0) {
        return err;
    }

    pdm_part_is_master_boot_sector(buf, p_part->p_disk->num_sectors, &is_mbr);
    if (is_mbr != 0) {
        start_sector[0] = buf[0x1C6] + buf[0x1C7] * 0x100 + buf[0x1C8] * 0x10000 + buf[0x1C9] * 0x1000000;
        sector_num[0] = buf[0x1CA] + buf[0x1CB] * 0x100 + buf[0x1CC] * 0x10000 + buf[0x1CD] * 0x1000000;
        start_sector[1] = buf[0x1D6] + buf[0x1D7] * 0x100 + buf[0x1D8] * 0x10000 + buf[0x1D9] * 0x1000000;
        sector_num[1] = buf[0x1DA] + buf[0x1DB] * 0x100 + buf[0x1DC] * 0x10000 + buf[0x1DD] * 0x1000000;
        start_sector[2] = buf[0x1E6] + buf[0x1E7] * 0x100 + buf[0x1E8] * 0x10000 + buf[0x1E9] * 0x1000000;
        sector_num[2] = buf[0x1EA] + buf[0x1EB] * 0x100 + buf[0x1EC] * 0x10000 + buf[0x1ED] * 0x1000000;
        start_sector[3] = buf[0x1F6] + buf[0x1F7] * 0x100 + buf[0x1F8] * 0x10000 + buf[0x1F9] * 0x1000000;
        sector_num[3] = buf[0x1FA] + buf[0x1FB] * 0x100 + buf[0x1FC] * 0x10000 + buf[0x1FD] * 0x1000000;

        for (i = 0; i < 4; i++) {
            rel_start = start_sector[i];
            rel_cnt = sector_num[i];
            if (rel_start == 0 || rel_cnt == 0) {
                return 7;
            }
            err = pdm_disk_physical_read(p_part->p_disk, buf, rel_start, 1, 0x200, &num_success);
            if (err != 0) {
                return err;
            }
            pdm_part_is_master_boot_sector(buf, p_part->p_disk->num_sectors, &is_mbr);
            if (is_mbr != 0) {
                base = start_sector[i];
                rel_sector = base;
                for (j = 0; j < 2; j++) {
                    if (j == 0) {
                        rel_sector = rel_sector + (buf[0x1C8] * 0x10000 + buf[0x1C6]) +
                                     (buf[0x1C9] * 0x1000000 + buf[0x1C7] * 0x100);
                        rel_num = buf[0x1CC] * 0x10000 + buf[0x1CA] + buf[0x1CD] * 0x1000000 + buf[0x1CB] * 0x100;
                        err = pdm_disk_physical_read(p_part->p_disk, buf, rel_sector, 1, 0x200, &num_success);
                        if (err != 0) {
                            return err;
                        }
                        if (part_no == cnt) {
                            p_part->start_sector = rel_sector;
                            p_part->num_sectors = rel_num;
                            return 0;
                        }
                        cnt++;
                    } else {
                        rel_sector = base + (buf[0x1D8] * 0x10000 + buf[0x1D6]) +
                                     (buf[0x1D9] * 0x1000000 + buf[0x1D7] * 0x100);
                        rel_num = buf[0x1DC] * 0x10000 + buf[0x1DA] + buf[0x1DD] * 0x1000000 + buf[0x1DB] * 0x100;
                        if (rel_sector == 0 || rel_num == 0) {
                            break;
                        }
                        err = pdm_disk_physical_read(p_part->p_disk, buf, rel_sector, 1, 0x200, &num_success);
                        if (err != 0) {
                            return err;
                        }
                        pdm_part_is_master_boot_sector(buf, p_part->p_disk->num_sectors, &is_mbr);
                        if (is_mbr == 0) {
                            break;
                        }
                        j = 0;
                    }
                }
            } else {
                if (part_no == cnt) {
                    p_part->start_sector = rel_start;
                    p_part->num_sectors = rel_cnt;
                    return 0;
                }
                cnt++;
            }
        }
    } else {
        if (part_no >= 2) {
            return 7;
        }
        p_part->start_sector = 0;
        p_part->num_sectors = p_part->p_disk->num_sectors;
    }
    return 0;
}

u32 pdm_part_chg_ltop(PDM_PARTITION* p_part, u32 lsector, u16 lbps) {
    u16 bps;
    u32 offset;
    u32 shift;

    pdm_disk_get_media_bps(p_part->p_disk, &bps);
    if (lbps == bps) {
        return lsector + p_part->start_sector;
    }
    offset = p_part->start_sector;
    shift = bps >> 9;
    if (shift == 2) {
        offset <<= 1;
    } else if (shift == 4) {
        offset <<= 2;
    } else if (shift == 8) {
        offset <<= 3;
    }
    shift = lbps >> 9;
    if (shift == 2) {
        offset >>= 1;
    } else if (shift == 4) {
        offset >>= 2;
    } else if (shift == 8) {
        offset >>= 3;
    }
    return lsector + offset;
}

s32 pdm_part_get_partition(PDM_DISK* p_disk, u32 part_no, PDM_PARTITION** pp_part) {
    PDM_PARTITION* p_part;
    u16 i;
    s32 err;

    *pp_part = NULL;
    if (pdm_disk_set.num_partition >= 0x1A) {
        return 0xA;
    }
    for (i = 0; i < 0x1A; i++) {
        if (!(pdm_disk_set.part_table[i].stat & 1)) {
            break;
        }
    }
    if (i == 0x1A) {
        return 0xA;
    }
    err = pdm_disk_set_disk(p_disk, &pdm_disk_set.part_table[i]);
    if (err != 0) {
        return err;
    }
    pdm_disk_set.num_partition += 1;
    pdm_disk_set.part_table[i].stat |= 1;
    pdm_disk_set.part_table[i].p_disk = p_disk;
    pdm_disk_set.part_table[i].part_no = part_no;
    *pp_part = &pdm_disk_set.part_table[i];
    return 0;
}

s32 pdm_part_release_partition(PDM_PARTITION* p_part) {
    p_part->stat &= ~1;
    pdm_disk_set.num_partition -= 1;
    return 0;
}

s32 pdm_part_is_attached_partition(PDM_PARTITION* p_part) {
    return (p_part->stat & 4) >> 2;
}

void pdm_part_set_driver_error_code(PDM_PARTITION* p_part, s32 error_code) {
    p_part->driver_error_code = error_code;
}

s32 pdm_part_get_driver_error_code(PDM_PARTITION* p_part) {
    return p_part->driver_error_code;
}

s32 pdm_part_get_media_attribute(PDM_PARTITION* p_part) {
    s32 err;

    err = pdm_disk_get_media_attribute(p_part->p_disk);
    if (err != 0) {
        return err;
    }
    return 0;
}

s32 pdm_part_init(PDM_PARTITION* p_part) {
    s32 err;

    if ((p_part->stat & 4) == 0) {
        err = pdm_disk_set_disk(p_part->p_disk, p_part);
        if (err != 0) {
            return err;
        }
        err = pdm_disk_init(p_part->p_disk);
        if (err != 0) {
            return err;
        }
    } else {
        return 0xB;
    }
    p_part->stat |= 4;
    return 0;
}

s32 pdm_part_mount(PDM_PARTITION* p_part) {
    s32 err;

    if ((p_part->stat & 8) == 0) {
        err = pdm_disk_set_disk(p_part->p_disk, p_part);
        if (err != 0) {
            return err;
        }
        err = pdm_disk_mount(p_part->p_disk);
        if (err != 0) {
            return err;
        }
        err = pdm_part_get_start_sector(p_part);
        if (err != 0) {
            pdm_disk_unmount(p_part->p_disk, 0);
            return err;
        }
    } else {
        return 0xC;
    }
    p_part->stat = (p_part->stat & ~2) | 8;
    return 0;
}

s32 pdm_part_format(PDM_PARTITION* p_part, u8* param) {
    s32 err;

    err = pdm_disk_set_disk(p_part->p_disk, p_part);
    if (err != 0) {
        return err;
    }
    err = pdm_disk_format(p_part->p_disk, param);
    if (err != 0) {
        return err;
    }
    return 0;
}

s32 pdm_part_logical_read(PDM_PARTITION* p_part, u8* buf, u32 lsector, u32 num_sector, u16 lbps, u32* p_num_success) {
    s32 err;

    if ((p_part->stat & 8) != 8 || (p_part->stat & 2) == 2) {
        return 0xF;
    }
    err = pdm_disk_set_disk(p_part->p_disk, p_part);
    if (err != 0) {
        return err;
    }
    if (p_part->num_sectors <= lsector) {
        return 0x12;
    }
    if (p_part->num_sectors < lsector + num_sector) {
        num_sector -= lsector + num_sector - p_part->num_sectors;
    }
    err = pdm_disk_physical_read(p_part->p_disk, buf, pdm_part_chg_ltop(p_part, lsector, lbps), num_sector, lbps, p_num_success);
    if (err != 0) {
        return err;
    }
    return 0;
}

s32 pdm_part_logical_write(PDM_PARTITION* p_part, const u8* buf, u32 lsector, u32 num_sector, u16 lbps, u32* p_num_success) {
    s32 err;

    if ((p_part->stat & 8) != 8 || (p_part->stat & 2) == 2) {
        return 0xF;
    }
    err = pdm_disk_set_disk(p_part->p_disk, p_part);
    if (err != 0) {
        return err;
    }
    if (p_part->num_sectors <= lsector) {
        return 0x12;
    }
    if (p_part->num_sectors < lsector + num_sector) {
        num_sector -= lsector + num_sector - p_part->num_sectors;
    }
    err = pdm_disk_physical_write(p_part->p_disk, buf, pdm_part_chg_ltop(p_part, lsector, lbps), num_sector, lbps, p_num_success);
    if (err != 0) {
        return err;
    }
    return 0;
}

s32 pdm_part_unmount(PDM_PARTITION* p_part, u32 force) {
    s32 err;
    s32 err2;

    err = 0;
    if ((p_part->stat & 8) != 0) {
        err2 = pdm_disk_set_disk(p_part->p_disk, p_part);
        if (err2 != 0) {
            return err2;
        }
        err2 = pdm_disk_unmount(p_part->p_disk, force);
        if (err2 != 0) {
            err = err2;
        }
    } else {
        err = 0xE;
    }
    if (err == 0 || force == 1) {
        p_part->stat &= ~2;
        p_part->stat &= ~8;
    }
    return err;
}

s32 pdm_part_finalize(PDM_PARTITION* p_part) {
    s32 err;

    if ((p_part->stat & 4) != 0) {
        err = pdm_disk_set_disk(p_part->p_disk, p_part);
        if (err != 0) {
            return err;
        }
        err = pdm_disk_finalize(p_part->p_disk);
        if (err != 0) {
            return err;
        }
    } else {
        return 0xD;
    }
    p_part->stat &= ~4;
    return 0;
}

s32 pdm_part_register_callback(PDM_PARTITION* p_part, PDM_PART_CALLBACK* callback) {
    p_part->callback[0] = callback[0];
    p_part->callback[1] = callback[1];
    return 0;
}

s32 pdm_part_unregister_callback(PDM_PARTITION* p_part) {
    p_part->callback[0] = NULL;
    p_part->callback[1] = NULL;
    return 0;
}

void pdm_part_set_change_media_state(PDM_DISK* p_disk, s32 state) {
    PDM_PARTITION* p_part;
    u16 i;

    for (i = 0; i < 0x1A; i++) {
        p_part = &pdm_disk_set.part_table[i];
        if (!(pdm_disk_set.part_table[i].stat & 1)) {
            continue;
        }
        if (pdm_disk_set.part_table[i].p_disk != p_disk) {
            continue;
        }
        pdm_disk_set.part_table[i].stat |= 2;
        if (state == 0) {
            if (pdm_disk_set.part_table[i].callback[1] != NULL) {
                pdm_disk_set.part_table[i].callback[1](p_part);
            }
        } else {
            if (pdm_disk_set.part_table[i].callback[0] != NULL) {
                pdm_disk_set.part_table[i].callback[0](p_part);
            }
        }
    }
}
