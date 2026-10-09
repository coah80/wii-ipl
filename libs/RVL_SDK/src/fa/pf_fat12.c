#define PF_FA_STR_LAYOUT
#define VFiPFCACHE_ReadFATPage PFCACHE_ReadFATPage
#define VFiPFCACHE_UpdateModifiedSector PFCACHE_UpdateModifiedSector
#define VFiPFFAT12_ReadFATEntry PFFAT12_ReadFATEntry
#define VFiPFFAT12_ReadFATEntryPage PFFAT12_ReadFATEntryPage
#define VFiPFFAT12_WriteFATEntry PFFAT12_WriteFATEntry
#define VFiPFFAT12_WriteFATEntryPage PFFAT12_WriteFATEntryPage
#define VFiPFFAT_UpdateFATEntry PFFAT_UpdateFATEntry
#define VFiPFSEC_ReadFAT PFSEC_ReadFAT
#define VFiPFSEC_WriteFAT PFSEC_WriteFAT
#include <private/fa/pf_volume.h>
#include <private/vf/PrFILE2/fatfs/pf_fat.h>
#include <private/vf/PrFILE2/fatfs/pf_fat12.h>

#include <private/vf/PrFILE2/fatfs/pf_sector.h>
#include <private/vf/PrFILE2/fatfs/pf_volume.h>

#include <private/vf/PrFILE2/common/pf_code.h>

pf_s32 VFiPFFAT12_ReadFATEntry(PF_VOLUME* p_vol, pf_u16 cluster, pf_u32* p_value) {
    pf_u16 fat_sector;
    pf_s32 err;
    pf_u16 fat_offset;
    pf_u16 offset_in_sector;
    pf_u16 word;
    pf_u8 buf[sizeof(pf_u16)];
    pf_u32 current_fat;
    pf_s32 result;

    fat_offset = cluster + (cluster >> 1);
    fat_sector = p_vol->bpb.active_FAT_sector + (fat_offset >> p_vol->bpb.log2_bytes_per_sector);
    offset_in_sector = fat_offset & (p_vol->bpb.bytes_per_sector - 1);
    if ((p_vol->bpb.ext_flags & 0x80) != 0) {
        current_fat = p_vol->bpb.ext_flags & (0x01 | 0x02 | 0x04);
    } else {
        current_fat = 1;
    }

    do {
        if (offset_in_sector < (p_vol->bpb.bytes_per_sector - 1)) {
            err = VFiPFSEC_ReadFAT(p_vol, &buf[0], (pf_u32)fat_sector, offset_in_sector, 2);
        } else {
            err = VFiPFSEC_ReadFAT(p_vol, &buf[0], (pf_u32)fat_sector, offset_in_sector, 1);
            if (err == 0) {
                err = VFiPFSEC_ReadFAT(p_vol, &buf[1], fat_sector + 1, 0U, 1);
            }
        }
        if (err == 0x1000 && p_vol->p_callback != PF_NULL) {
            result = ((PF_VOLUME_CB)p_vol->p_callback)(p_vol->last_driver_error);
            if (result == 0) {
                continue;
            }
            if (result == 1 && p_vol->bpb.num_active_FATs >= 2 && current_fat < p_vol->bpb.num_active_FATs) {
                current_fat++;
                fat_sector += (pf_u16)p_vol->bpb.sectors_per_FAT;
                continue;
            }
        }
        if (err != 0) {
            *p_value = -1;
            return err;
        }
    } while (err != 0);

    word = PF_SWAP_16(*(pf_u16*)buf);
    if ((cluster & 0x01) != 0) {
        *p_value = (word >> 4);
    } else {
        *p_value = word & 0xFFF;
    }
    return 0;
}

pf_s32 VFiPFFAT12_WriteFATEntry(PF_VOLUME* p_vol, pf_u16 cluster, pf_u16 value) {
    pf_s32 err;
    pf_u16 fat_offset;
    pf_u16 fat_sector;
    pf_u16 offset_in_sector;
    pf_u16 fat_sector2;
    pf_u16 offset_in_sector2;
    pf_u16 word;
    pf_u16 current_fat;
    pf_s32 result;
    pf_u8 buf[sizeof(pf_u16)];

    fat_offset = cluster + (cluster >> 1);
    fat_sector = p_vol->bpb.active_FAT_sector + (fat_offset >> p_vol->bpb.log2_bytes_per_sector);
    offset_in_sector = fat_offset & (p_vol->bpb.bytes_per_sector - 1);
    if ((cluster & 0x01) != 0) {
        err = VFiPFSEC_ReadFAT(p_vol, &buf[0], fat_sector, offset_in_sector, 1);
        if (err != 0) {
            return err;
        }
        word = (pf_u16)((value << 4) + (buf[0] & 0xF));
    } else {
        fat_sector2 = p_vol->bpb.active_FAT_sector + ((fat_offset + 1) >> p_vol->bpb.log2_bytes_per_sector);
        offset_in_sector2 = (fat_offset + 1) & (p_vol->bpb.bytes_per_sector - 1);
        err = VFiPFSEC_ReadFAT(p_vol, &buf[0], fat_sector2, offset_in_sector2, 1);
        if (err != 0) {
            return err;
        }
        word = (pf_u16)buf[0] << 8;
        word = (word & 0xF000) + (pf_u16)(value & 0xFFF);
    }
    *(pf_u16*)buf = PF_SWAP_16(word);
    result = 0;
    for (current_fat = 0; current_fat < p_vol->bpb.num_active_FATs; current_fat++) {
        if (offset_in_sector < (p_vol->bpb.bytes_per_sector - 1)) {
            err = VFiPFSEC_WriteFAT(p_vol, &buf[0], fat_sector, offset_in_sector, 2);
            if (err != 0 && result == 0) { result = err; }
        } else {
            err = VFiPFSEC_WriteFAT(p_vol, &buf[0], fat_sector, offset_in_sector, 1U);
            if (err != 0 && result == 0) { result = err; }
            err = VFiPFSEC_WriteFAT(p_vol, &buf[1], fat_sector + 1, 0U, 1);
            if (err != 0 && result == 0) { result = err; }
        }
        fat_sector += p_vol->bpb.sectors_per_FAT;
    }
    return result;
}

pf_s32 PFFAT12_WriteFATEntryWithBuf(PF_VOLUME* p_vol, pf_s16 cluster, pf_u16 value, PF_CACHE_PAGE* p_page) {
    pf_u32 next_sector;
    pf_u32 offset_in_sector;
    pf_u16 current_fat;
    pf_s32 fat_offset;
    pf_u32 fat_sector;
    pf_s32 result;
    pf_s32 err;
    fat_offset = (pf_u16)(cluster + (cluster >> 1));
    fat_sector = (pf_u16)(p_vol->bpb.active_FAT_sector + (fat_offset >> p_vol->bpb.log2_bytes_per_sector));
    offset_in_sector = fat_offset & (p_vol->bpb.bytes_per_sector - 1);
    err = 0;
    result = 0;
#define FLUSH_FAT_BUFFER() \
    for (current_fat = 0; current_fat < p_vol->bpb.num_active_FATs; current_fat++) { \
        err = VFiPFSEC_WriteFAT(p_vol, p_page->p_buf, p_page->sector + current_fat * p_vol->bpb.sectors_per_FAT, 0, p_vol->bpb.bytes_per_sector); \
        if (err != 0 && result == 0) { result = err; } \
    }
    if (p_page->sector != fat_sector) {
        FLUSH_FAT_BUFFER();
        err = VFiPFSEC_ReadFAT(p_vol, p_page->p_buf, fat_sector, 0, p_vol->bpb.bytes_per_sector);
        if (err != 0) { return err; }
        p_page->sector = fat_sector;
    }
    if (cluster & 1) {
        p_page->p_buf[(pf_u16)offset_in_sector] = (p_page->p_buf[(pf_u16)offset_in_sector] & 0xF) | ((value << 4) & 0xF0);
        if ((pf_u16)offset_in_sector == (pf_u32)(p_vol->bpb.bytes_per_sector - 1)) {
            FLUSH_FAT_BUFFER();
            next_sector = fat_sector + 1;
            err = VFiPFSEC_ReadFAT(p_vol, p_page->p_buf, next_sector, 0, p_vol->bpb.bytes_per_sector);
            if (err != 0) { return err; }
            p_page->sector = next_sector;
            p_page->p_buf[0] = value >> 4;
        } else {
            p_page->p_buf[(pf_u16)offset_in_sector + 1] = value >> 4;
        }
    } else {
        p_page->p_buf[(pf_u16)offset_in_sector] = value;
        if ((pf_u16)offset_in_sector == (pf_u32)(p_vol->bpb.bytes_per_sector - 1)) {
            FLUSH_FAT_BUFFER();
            next_sector = fat_sector + 1;
            err = VFiPFSEC_ReadFAT(p_vol, p_page->p_buf, next_sector, 0, p_vol->bpb.bytes_per_sector);
            if (err != 0) { return err; }
            p_page->sector = next_sector;
            p_page->p_buf[0] = (p_page->p_buf[0] & 0xF0) | ((pf_u8)(value >> 8));
        } else {
            p_page->p_buf[(pf_u16)offset_in_sector + 1] = (p_page->p_buf[(pf_u16)offset_in_sector + 1] & 0xF0) | ((pf_u8)(value >> 8));
        }
    }
    if (err != 0) { result = err; }
    return result;
#undef FLUSH_FAT_BUFFER
}

static inline pf_s32 ReadFAT12WordWithBuf(PF_VOLUME* p_vol, pf_u32 offset, pf_u32* p_value, PF_CACHE_PAGE* p_page) {
    pf_u32 current_fat;
    pf_u32 sector;
    pf_s32 err;
    pf_s32 result;

#define LOAD_FAT_SECTOR(next_sector) \
    if (p_page->sector != sector + (next_sector)) { \
        if (p_page->option == 1) { \
            for (err = 0; (pf_u16)err < p_vol->bpb.num_active_FATs; err++) { \
                VFiPFSEC_WriteFAT(p_vol, p_page->p_buf, p_page->sector + (pf_u16)err * p_vol->bpb.sectors_per_FAT, 0, p_vol->bpb.bytes_per_sector); \
            } \
        } \
        err = VFiPFSEC_ReadFAT(p_vol, p_page->p_buf, sector + (next_sector), 0, p_vol->bpb.bytes_per_sector); \
        if (err != 0) { continue; } \
        p_page->sector = sector + (next_sector); \
    }

    sector = p_vol->bpb.active_FAT_sector + (offset >> p_vol->bpb.log2_bytes_per_sector) & 0xFFFF;
    if ((p_vol->bpb.ext_flags & 0x80) != 0) {
        current_fat = p_vol->bpb.ext_flags & (0x01 | 0x02 | 0x04);
    } else {
        current_fat = 1;
    }
    err = 0;
    while (PF_TRUE) {
        if (err == 0x1000 && p_vol->p_callback != PF_NULL) {
            result = ((PF_VOLUME_CB)p_vol->p_callback)(p_vol->last_driver_error);
            if (result == 0) {
                err = 0;
                continue;
            }
            if (result == 1 && p_vol->bpb.num_active_FATs >= 2 && current_fat < p_vol->bpb.num_active_FATs) {
                current_fat++;
                sector += p_vol->bpb.sectors_per_FAT;
                err = 0;
                continue;
            }
        } else {
            LOAD_FAT_SECTOR(0);
            offset &= p_vol->bpb.bytes_per_sector - 1;
            if (offset == (p_vol->bpb.bytes_per_sector - 1)) {
                *p_value = p_page->p_buf[offset];
                if (p_page->option == 1) {
                    for (err = 0; (pf_u16)err < p_vol->bpb.num_active_FATs; err++) {
                        VFiPFSEC_WriteFAT(p_vol, p_page->p_buf, p_page->sector + (pf_u16)err * p_vol->bpb.sectors_per_FAT, 0, p_vol->bpb.bytes_per_sector);
                    }
                }
                err = VFiPFSEC_ReadFAT(p_vol, p_page->p_buf, sector + 1, 0, p_vol->bpb.bytes_per_sector);
                if (err != 0) { continue; }
                p_page->sector = sector + 1;
                *p_value += (pf_u16)(*p_page->p_buf) << 8;
            } else {
                *p_value = ((pf_u16)p_page->p_buf[offset + 1] << 8) + p_page->p_buf[offset];
            }
        }
        break;
    }
    return err;

#undef LOAD_FAT_SECTOR
}

pf_s32 PFFAT12_ReadFATEntryWithBuf(PF_VOLUME* p_vol, pf_u16 cluster, pf_u32* p_value,
                                 PF_CACHE_PAGE* p_page) {
    pf_s32 err;

    err = ReadFAT12WordWithBuf(p_vol, (pf_u16)(cluster + (cluster >> 1)), p_value, p_page);
    if (err != 0) {
        *p_value = -1;
        return err;
    }
    if ((cluster & 0x01) != 0) {
        *p_value = *p_value >> 4;
    } else {
        *p_value &= 0xFFF;
    }
    return 0;
}
