#define PF_FA_STR_LAYOUT
#include <private/fa/pf_volume.h>
#include <private/vf/PrFILE2/dskmng/pdm_bpb.h>
extern pf_bool pdm_part_is_boot_sector(pf_u8*);

static inline pf_u16 read_boot_u16(pf_u8* buf, pf_u32 offset) {
    if ((pf_u32)&buf[offset] & 1) {
        return (buf[offset + 1] << 8) | buf[offset];
    }
    return PF_SWAP_16(*(pf_u16*)&buf[(offset + 1) & ~1]);
}

void pdm_bpb_CalcBPBFields(PF_VOLUME* p_vol) {
    pf_u32 num_data_sectors;
    pf_u16 val;
    p_vol->bpb.log2_bytes_per_sector = 0;
    val = p_vol->bpb.bytes_per_sector;
    while (val >>= 1) { p_vol->bpb.log2_bytes_per_sector++; }
    p_vol->bpb.log2_sectors_per_cluster = 0;
    val = p_vol->bpb.sectors_per_cluster;
    while (val >>= 1) { p_vol->bpb.log2_sectors_per_cluster++; }
    p_vol->bpb.num_root_dir_sectors = ((p_vol->bpb.num_root_dir_entries << 5) + (p_vol->bpb.bytes_per_sector - 1)) >> p_vol->bpb.log2_bytes_per_sector;
    p_vol->bpb.first_data_sector = (p_vol->bpb.num_FATs * p_vol->bpb.sectors_per_FAT) + (p_vol->bpb.num_root_dir_sectors + p_vol->bpb.num_reserved_sectors);
    num_data_sectors = p_vol->bpb.total_sectors - p_vol->bpb.first_data_sector;
    p_vol->bpb.num_clusters = num_data_sectors >> p_vol->bpb.log2_sectors_per_cluster;
    if (p_vol->bpb.num_clusters < 0xFF5) {
        p_vol->bpb.fat_type = FAT_12;
        p_vol->bpb.first_root_dir_sector = p_vol->bpb.num_reserved_sectors + p_vol->bpb.num_FATs * p_vol->bpb.sectors_per_FAT;
    } else if (p_vol->bpb.num_clusters < 0xFFF5) {
        p_vol->bpb.fat_type = FAT_16;
        p_vol->bpb.first_root_dir_sector = p_vol->bpb.num_reserved_sectors + p_vol->bpb.num_FATs * p_vol->bpb.sectors_per_FAT;
    } else {
        p_vol->bpb.fat_type = FAT_32;
        p_vol->bpb.first_root_dir_sector = 0;
    }
}

pf_s32 pdm_bpb_InitVolumeWithBootSector(PF_VOLUME* p_vol, pf_u8* buf) {
    pf_u32 total_sectors;
    pf_s32 err = 0;
    pf_u32 fat_sectors;
    pf_u32 version;
    if (!pdm_part_is_boot_sector(buf)) {
        err = 3;
    } else {
        p_vol->bpb.bytes_per_sector = read_boot_u16(buf, 11);
        p_vol->bpb.sectors_per_cluster = buf[13];
        p_vol->bpb.num_reserved_sectors = read_boot_u16(buf, 14);
        p_vol->bpb.num_FATs = buf[16];
        p_vol->bpb.num_root_dir_entries = read_boot_u16(buf, 17);
        p_vol->bpb.media = buf[21];
        total_sectors = read_boot_u16(buf, 19);
        p_vol->bpb.total_sectors = total_sectors == 0 ? PF_SWAP_32(*(pf_u32*)&buf[32]) : total_sectors;
        fat_sectors = read_boot_u16(buf, 22);
        p_vol->bpb.sectors_per_FAT = fat_sectors == 0 ? PF_SWAP_32(*(pf_u32*)&buf[36]) : fat_sectors;
        pdm_bpb_CalcBPBFields(p_vol);
        switch (p_vol->bpb.fat_type) {
            case FAT_12:
            case FAT_16:
                if (fat_sectors == 0) { err = 4; }
                break;
            case FAT_32:
                if (total_sectors != 0 || fat_sectors != 0) { err = 4; }
                version = read_boot_u16(buf, 42);
                p_vol->bpb.ext_flags = read_boot_u16(buf, 40);
                p_vol->bpb.root_dir_cluster = PF_SWAP_32(*(pf_u32*)&buf[44]);
                p_vol->bpb.fs_info_sector = read_boot_u16(buf, 48);
                p_vol->bpb.backup_boot_sector = read_boot_u16(buf, 50);
                p_vol->bpb.first_root_dir_sector = p_vol->bpb.first_data_sector + ((p_vol->bpb.root_dir_cluster - 2) << p_vol->bpb.log2_sectors_per_cluster);
                if (version != 0) { err = 4; }
                break;
            default:
                err = 4;
                break;
        }
        if (p_vol->bpb.ext_flags & 0x80) {
            p_vol->bpb.num_active_FATs = 1;
            p_vol->bpb.active_FAT_sector = p_vol->bpb.num_reserved_sectors + ((p_vol->bpb.ext_flags & 7) * p_vol->bpb.sectors_per_FAT);
        } else {
            p_vol->bpb.num_active_FATs = p_vol->bpb.num_FATs;
            p_vol->bpb.active_FAT_sector = p_vol->bpb.num_reserved_sectors;
        }
    }
    return err;
}

pf_s32 pdm_bpb_InitVolumeWithFSINFOSector(PF_VOLUME* p_vol, pf_u8* buf, pf_u32* p_free_count, pf_u32* p_next_free) {
    pf_u32 free_count;
    pf_u32 next_free;
    *p_free_count = -1;
    *p_next_free = -1;
    if (PF_SWAP_32(*(pf_u32*)&buf[0]) == 0x41615252 && PF_SWAP_32(*(pf_u32*)&buf[484]) == 0x61417272 && PF_SWAP_32(*(pf_u32*)&buf[508]) == 0xAA550000) {
        free_count = PF_SWAP_32(*(pf_u32*)&buf[488]);
        next_free = PF_SWAP_32(*(pf_u32*)&buf[492]);
        if (free_count >= 2 && free_count < p_vol->bpb.num_clusters + 2) { *p_free_count = free_count; }
        if (next_free >= 2 && next_free < p_vol->bpb.num_clusters + 2) { *p_next_free = next_free; }
    }
    return 0;
}
