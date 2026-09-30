#define PF_FA_STR_LAYOUT
#define VFiPFCACHE_ReadFATPage PFCACHE_ReadFATPage
#define VFiPFCACHE_UpdateModifiedSector PFCACHE_UpdateModifiedSector
#define VFiPFFAT16_ReadFATEntry PFFAT16_ReadFATEntry
#define VFiPFFAT16_ReadFATEntryPage PFFAT16_ReadFATEntryPage
#define VFiPFFAT16_WriteFATEntry PFFAT16_WriteFATEntry
#define VFiPFFAT16_WriteFATEntryPage PFFAT16_WriteFATEntryPage
#define VFiPFFAT_UpdateFATEntry PFFAT_UpdateFATEntry
#define VFiPFSEC_ReadFAT PFSEC_ReadFAT
#define VFiPFSEC_WriteFAT PFSEC_WriteFAT
#include <private/fa/pf_volume.h>
#include <private/vf/PrFILE2/fatfs/pf_fat.h>
#include <private/vf/PrFILE2/fatfs/pf_fat16.h>

#include <private/vf/PrFILE2/fatfs/pf_sector.h>
#include <private/vf/PrFILE2/fatfs/pf_volume.h>

pf_s32 VFiPFFAT16_ReadFATEntry(PF_VOLUME* p_vol, pf_u32 cluster, pf_u32* p_value) {
    pf_u32 fat_offset;
    pf_u32 fat_sector;
    pf_u16 offset_in_sector;
    pf_u8 buf[sizeof(pf_u16)];
    pf_s32 err;
    pf_u32 current_fat;
    pf_s32 result;

    fat_offset = cluster * sizeof(pf_u16);
    fat_sector = (pf_u16)(p_vol->bpb.active_FAT_sector + ((cluster * sizeof(pf_u16)) >> p_vol->bpb.log2_bytes_per_sector));
    offset_in_sector = fat_offset & (p_vol->bpb.bytes_per_sector - 1);
    if ((p_vol->bpb.ext_flags & 0x80) != 0) {
        current_fat = p_vol->bpb.ext_flags & (0x01 | 0x02 | 0x04);
    } else {
        current_fat = 1;
    }
    do {
        err = VFiPFSEC_ReadFAT(p_vol, buf, fat_sector, offset_in_sector, 2);
        if (err == 0x1000 && p_vol->p_callback != PF_NULL) {
            result = ((PF_VOLUME_CB)p_vol->p_callback)(p_vol->last_driver_error);
            if (result == 0) {
                continue;
            }
            if (result == 1 && p_vol->bpb.num_active_FATs >= 2 && current_fat < p_vol->bpb.num_active_FATs) {
                current_fat++;
                fat_sector += p_vol->bpb.sectors_per_FAT;
                continue;
            }
        }
        if (err != 0) {
            *p_value = -1;
            return err;
        }
    } while (err != 0);

    *p_value = PF_SWAP_16(*(pf_u16*)buf);
    return 0;
}

pf_s32 VFiPFFAT16_WriteFATEntry(PF_VOLUME* p_vol, pf_u32 cluster, pf_u32 value) {
    pf_s32 err;
    pf_u32 fat_offset;
    pf_u16 fat_sector;
    pf_u16 offset_in_sector;
    pf_u32 current_fat;
    pf_s32 result;
    pf_u8 buf[sizeof(pf_u16)];

    fat_offset = cluster * sizeof(pf_u16);
    fat_sector = p_vol->bpb.active_FAT_sector + ((cluster * sizeof(pf_u16)) >> p_vol->bpb.log2_bytes_per_sector);
    offset_in_sector = fat_offset & (p_vol->bpb.bytes_per_sector - 1);
    *(pf_u16*)buf = PF_SWAP_16(value);
    result = 0;
    for (current_fat = 0; current_fat < p_vol->bpb.num_active_FATs; current_fat++) {
        err = VFiPFSEC_WriteFAT(p_vol, buf, fat_sector, offset_in_sector, 2);
        if (err != 0 && result == 0) {
            result = err;
        }
        fat_sector += p_vol->bpb.sectors_per_FAT;
    }
    return result;
}

pf_s32 PFFAT16_WriteFATEntryWithBuf(PF_VOLUME* p_vol, pf_u32 cluster, pf_u32 value, PF_CACHE_PAGE* p_page) {
    pf_u16 offset_in_sector;
    pf_s32 err;
    pf_u32 fat_offset;
    pf_u16 fat_sector;
    pf_u32 current_fat;
    pf_s32 result;
    fat_offset = cluster * sizeof(pf_u16);
    fat_sector = (pf_u16)(p_vol->bpb.active_FAT_sector + (fat_offset >> p_vol->bpb.log2_bytes_per_sector));
    offset_in_sector = (pf_u16)(fat_offset & (p_vol->bpb.bytes_per_sector - 1));
    err = 0;
    result = 0;
    if (p_page->sector != fat_sector) {
        for (current_fat = 0; current_fat < p_vol->bpb.num_active_FATs; current_fat++) {
            err = VFiPFSEC_WriteFAT(p_vol, p_page->p_buf, p_page->sector + current_fat * p_vol->bpb.sectors_per_FAT, 0, p_vol->bpb.bytes_per_sector);
            if (err != 0 && result == 0) {
                result = err;
            }
        }
        p_page->sector = fat_sector;
        err = VFiPFSEC_ReadFAT(p_vol, p_page->p_buf, fat_sector, 0, p_vol->bpb.bytes_per_sector);
    }
    p_page->p_buf[offset_in_sector] = value;
    (offset_in_sector + p_page->p_buf)[1] = value >> 8;
    if (err != 0) {
        result = err;
    }
    return result;
}

pf_s32 PFFAT16_ReadFATEntryWithBuf(PF_VOLUME* p_vol, pf_u32 cluster, pf_u32* p_value, PF_CACHE_PAGE* p_page) {
    pf_u32 sector;
    pf_s32 err;
    pf_u32 offset;
    pf_u32 current_fat;
    pf_s32 result;

    offset = cluster * sizeof(pf_u16);
    sector = (pf_u16)(p_vol->bpb.active_FAT_sector + (offset >> p_vol->bpb.log2_bytes_per_sector));
    current_fat = 1;
    if ((p_vol->bpb.ext_flags & 0x80) != 0) {
        current_fat = p_vol->bpb.ext_flags & 7;
    }
    if (p_page->sector != sector) {
        if (p_page->option == 1) {
            pf_u16 fat;
            for (fat = 0; fat < p_vol->bpb.num_active_FATs; fat++) {
                VFiPFSEC_WriteFAT(p_vol, p_page->p_buf, p_page->sector + fat * p_vol->bpb.sectors_per_FAT, 0, p_vol->bpb.bytes_per_sector);
            }
        }
        do {
            err = VFiPFSEC_ReadFAT(p_vol, p_page->p_buf, sector, 0, p_vol->bpb.bytes_per_sector);
            if (err != 0x1000 || p_vol->p_callback == PF_NULL) {
                goto block_22;
            }
            result = ((PF_VOLUME_CB)p_vol->p_callback)(p_vol->last_driver_error);
            if (result != 0) {
                if (result == 1 && p_vol->bpb.num_active_FATs >= 2 && current_fat < p_vol->bpb.num_active_FATs) {
                    current_fat++;
                    sector += p_vol->bpb.sectors_per_FAT;
                } else {
                    goto block_22;
                }
            }
            continue;
        block_22:
            if (err != 0) {
                return err;
            }
            p_page->sector = sector;
        } while (err != 0);
    }
    offset &= p_vol->bpb.bytes_per_sector - 1;
    *p_value = PF_SWAP_16(*((pf_u16*)(p_page->p_buf + offset)));

    return 0;
}
