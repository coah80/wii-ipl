#include <revolution/types.h>
#include <private/fa/fa_local.h>

#define FAT_MAX 3

typedef s32 (*PF_VOLUME_CB)(s32);

typedef struct PF_CLUSTER_LINK_VOL {
    u16 flag;      // 0x00
    u16 interval;  // 0x02
    u32* buffer;   // 0x04
    u32 link_max;  // 0x08
} PF_CLUSTER_LINK_VOL;

/* pf_cache.c */
s32 PFCACHE_AllocateDataPage(PF_VOLUME* p_vol, u32 sector, PF_CACHE_PAGE** pp_page, u32* p_dummy);
s32 PFCACHE_AllocateFATPage(PF_VOLUME* p_vol, u32 sector, PF_CACHE_PAGE** pp_page, u32* p_dummy);
s32 PFCACHE_FlushFATCache(PF_VOLUME* p_vol);
void PFCACHE_FreeDataPage(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_page);
void PFCACHE_FreeFATPage(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_page);
s32 PFCACHE_WriteFATSectorAndFreeIfNeeded(PF_VOLUME* p_vol, const u8* p_buf, u32 sector);

/* pf_fat12/16/32.c */
s32 PFFAT12_ReadFATEntry(PF_VOLUME* p_vol, u16 cluster, u32* p_value);
s32 PFFAT12_ReadFATEntryWithBuf(PF_VOLUME* p_vol, u16 cluster, u32* p_value, PF_CACHE_PAGE* p_page);
s32 PFFAT12_WriteFATEntry(PF_VOLUME* p_vol, u16 cluster, u16 value);
s32 PFFAT12_WriteFATEntryWithBuf(PF_VOLUME* p_vol, u16 cluster, u16 value, PF_CACHE_PAGE* p_page);
s32 PFFAT16_ReadFATEntry(PF_VOLUME* p_vol, u32 cluster, u32* p_value);
s32 PFFAT16_ReadFATEntryWithBuf(PF_VOLUME* p_vol, u32 cluster, u32* p_value, PF_CACHE_PAGE* p_page);
s32 PFFAT16_WriteFATEntry(PF_VOLUME* p_vol, u32 cluster, u32 value);
s32 PFFAT16_WriteFATEntryWithBuf(PF_VOLUME* p_vol, u32 cluster, u32 value, PF_CACHE_PAGE* p_page);
s32 PFFAT32_ReadFATEntry(PF_VOLUME* p_vol, u32 cluster, u32* p_value);
s32 PFFAT32_ReadFATEntryWithBuf(PF_VOLUME* p_vol, u32 cluster, u32* p_value, PF_CACHE_PAGE* p_page);
s32 PFFAT32_WriteFATEntry(PF_VOLUME* p_vol, u32 cluster, u32 value);
s32 PFFAT32_WriteFATEntryWithBuf(PF_VOLUME* p_vol, u32 cluster, u32 value, PF_CACHE_PAGE* p_page);

/* pf_sector.c */
s32 PFSEC_ReadFAT(PF_VOLUME* p_vol, u8* p_buf, u32 sector, u16 offset, u16 size);
s32 PFSEC_WriteFAT(PF_VOLUME* p_vol, const u8* p_buf, u32 sector, u16 offset, u16 size);
s32 PFSEC_ReadData(PF_VOLUME* p_vol, u8* p_buf, u32 sector, u16 offset, u16 size, u32* p_success_size, u32 set_sig);
s32 PFSEC_WriteData(PF_VOLUME* p_vol, const u8* p_buf, u32 sector, u16 offset, u16 size, u32* p_success_size, u32 is_direct);

/* pf_clib.c */
void* pf_memset(void* dst, s32 c, u32 len);
void* pf_memcpy(void* dst, const void* src, u32 len);

extern PF_VOLUME_SET pf_vol_set;

const struct {
    u32 bad;        // 0x00
    u32 eoc1;       // 0x04
    u32 eoc2;       // 0x08
    u32 fat0_mask;  // 0x0C
    u32 fat1;       // 0x10
} fat_special_values[FAT_MAX] = {
    {0xFF7, 0xFF8, 0xFFF, 0xF00, 0xFFF},
    {0xFFF7, 0xFFF8, 0xFFFF, 0xFF00, 0xFFFF},
    {0xFFFFFF7, 0xFFFFFF8, 0xFFFFFFF, 0xFFFFF00, 0xFFFFFFF},
};

s32 PFFAT_ReadFATSector(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_page, u32 cluster);
static s32 PFFAT_ReadFATEntry(PF_VOLUME* p_vol, u32 cluster, u32* p_value);
static s32 PFFAT_ReadFATEntryWithBuf(PF_VOLUME* p_vol, u32 cluster, u32* p_value, PF_CACHE_PAGE* p_page);
static s32 PFFAT_WriteFATEntry(PF_VOLUME* p_vol, u32 cluster, u32 value);
static s32 PFFAT_WriteFATEntryWithBuf(PF_VOLUME* p_vol, u32 cluster, u32 value, PF_CACHE_PAGE* p_page);
static s32 PFFAT_WriteFATSector(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_page, u32 cluster);
static s32 PFFAT_ReadClusterLink(PF_FFD* p_ffd, u32* p_cluster);
static s32 PFFAT_WriteClusterLink(PF_FFD* p_ffd, u32* p_cluster);
static s32 PFFAT_getNextFreeCluster(PF_FFD* p_ffd, u32* p_free_cluster);
static s32 PFFAT_getFreeClusters(PF_FFD* p_ffd, u32 size, u32* p_first_free_cluster, u32* p_num_free_clusters);
static s32 PFFAT_getLastCluster(PF_FFD* p_ffd);
static s32 PFFAT_SetChainValueToFFD(PF_FFD* p_ffd, u32 chain_index, u32 cluster);
static s32 PFFAT_GetBeforeSector(u32* p_befor_sector, PF_VOLUME* p_vol, u32 current_sector);
static void PFFAT_SetHint(PF_FFD* p_ffd, PF_FAT_HINT* p_hint);
static void PFFAT_SetLastAccess(PF_FFD* p_ffd, PF_FAT_HINT* last_access);
s32 PFFAT_FreeChain(PF_FFD* p_ffd, u32 start_cluster, u32 chain_index, u32 size);
s32 PFFAT_RefreshFSINFO(PF_VOLUME* p_vol);

s32 PFFAT_ReadFATSector(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_page, u32 cluster) {
    s32 err;
    u32 offset;
    u32 current_fat;
    s32 result;

    switch (p_vol->bpb.fat_type) {
        case FAT_12: {
            offset = (u16)(cluster + (cluster >> 1));
            break;
        }
        case FAT_16: {
            offset = cluster * sizeof(u16);
            break;
        }
        case FAT_32: {
            offset = cluster * sizeof(u32);
            break;
        }
        default: {
            return 15;
        }
    }

    p_page->sector = (u16)(p_vol->bpb.active_FAT_sector + (offset >> p_vol->bpb.log2_bytes_per_sector));
    current_fat = 1;
    if ((p_vol->bpb.ext_flags & 0x80) != 0) {
        current_fat = p_vol->bpb.ext_flags & 0x07;
    }
    while (1) {
        err = PFSEC_ReadFAT(p_vol, p_page->p_buf, p_page->sector, 0, p_vol->bpb.bytes_per_sector);
        if (err == 0x1000 && p_vol->p_callback != 0) {
            result = ((PF_VOLUME_CB)p_vol->p_callback)(p_vol->last_driver_error);
            if (result != 0) {
                if (result == 1 && p_vol->bpb.num_active_FATs >= 2 && current_fat < p_vol->bpb.num_active_FATs) {
                    current_fat++;
                    p_page->sector += p_vol->bpb.sectors_per_FAT;
                    goto block_22;
                }
            } else {
                goto block_22;
            }
        }
        if (err != 0) {
            return err;
        }
    block_22:
        if (err == 0) {
            return err;
        }
    }
}
static s32 PFFAT_ReadFATEntry(PF_VOLUME* p_vol, u32 cluster, u32* p_value) {
    switch (p_vol->bpb.fat_type) {
        case FAT_12: {
            return PFFAT12_ReadFATEntry(p_vol, (u16)cluster, p_value);
        }
        case FAT_16: {
            return PFFAT16_ReadFATEntry(p_vol, cluster, p_value);
        }
        case FAT_32: {
            return PFFAT32_ReadFATEntry(p_vol, cluster, p_value);
        }
        default: {
            break;
        }
    }

    *p_value = -1;
    return 15;
}

static s32 PFFAT_ReadFATEntryWithBuf(PF_VOLUME* p_vol, u32 cluster, u32* p_value, PF_CACHE_PAGE* p_page) {
    s32 err;

    switch (p_vol->bpb.fat_type) {
        case FAT_12: {
            err = PFFAT12_ReadFATEntryWithBuf(p_vol, (u16)cluster, p_value, p_page);
            break;
        }
        case FAT_16: {
            err = PFFAT16_ReadFATEntryWithBuf(p_vol, cluster, p_value, p_page);
            break;
        }
        case FAT_32: {
            err = PFFAT32_ReadFATEntryWithBuf(p_vol, cluster, p_value, p_page);
            break;
        }
        default: {
            err = 15;
            break;
        }
    }
    return err;
}

static s32 PFFAT_WriteFATEntry(PF_VOLUME* p_vol, u32 cluster, u32 value) {
    switch (p_vol->bpb.fat_type) {
        case FAT_12: {
            if (value > 0x0FFF) {
                return 16;
            }
            return PFFAT12_WriteFATEntry(p_vol, (u16)cluster, (u16)value);
        }
        case FAT_16: {
            if (value > 0xFFFF) {
                return 16;
            }
            return PFFAT16_WriteFATEntry(p_vol, cluster, value);
        }
        case FAT_32: {
            if (value > 0x0FFFFFFF) {
                return 16;
            }
            return PFFAT32_WriteFATEntry(p_vol, cluster, value);
        }
        default: {
            break;
        }
    }
    return 15;
}

static s32 PFFAT_WriteFATEntryWithBuf(PF_VOLUME* p_vol, u32 cluster, u32 value, PF_CACHE_PAGE* p_page) {
    switch (p_vol->bpb.fat_type) {
        case FAT_12: {
            if (value > 0x0FFF) {
                return 16;
            }
            return PFFAT12_WriteFATEntryWithBuf(p_vol, (u16)cluster, (u16)value, p_page);
        }
        case FAT_16: {
            if (value > 0xFFFF) {
                return 16;
            }
            return PFFAT16_WriteFATEntryWithBuf(p_vol, cluster, value, p_page);
        }
        case FAT_32: {
            if (value > 0x0FFFFFFF) {
                return 16;
            }
            return PFFAT32_WriteFATEntryWithBuf(p_vol, cluster, value, p_page);
        }
        default: {
            break;
        }
    }
    return 15;
}

s32 PFFAT_SearchForNumFreeClusters(PF_VOLUME* p_vol, u32 start_cluster, u32 end_cluster, u32 num_cluster,
                                   u32* p_start_free_cluster, u32* p_last_free_cluster) {
    u32 upper_bound_cluster;
    u32 success_num;
    u32 save_start_cluster;
    u32 save_success_num;
    s32 err;
    u32 search_flg = 0;
    u32 temp_start_cluster = 0;
    u32 fat_entry;
    u32 dummy;
    PF_CACHE_PAGE* p_page;

    *p_start_free_cluster = -1;
    *p_last_free_cluster = -1;

    success_num = 0;
    save_start_cluster = -1;
    save_success_num = 0;
    upper_bound_cluster = p_vol->bpb.num_clusters + 2;

    if (start_cluster < 2 || start_cluster >= (p_vol->bpb.num_clusters + 2)) {
        start_cluster = 2;
    }
    if (end_cluster < 2 || end_cluster >= (p_vol->bpb.num_clusters + 2)) {
        end_cluster = upper_bound_cluster - 1;
    }
    temp_start_cluster = start_cluster;
    err = PFCACHE_AllocateDataPage(p_vol, -1, &p_page, &dummy);
    if (err != 0) {
        return err;
    }
    err = PFFAT_ReadFATSector(p_vol, p_page, start_cluster);
    if (err != 0) {
        PFCACHE_FreeDataPage(p_vol, p_page);
        return err;
    }
    p_page->option = 0;
    while (start_cluster <= end_cluster) {
        if (upper_bound_cluster <= start_cluster) {
            start_cluster = 2;
        }
        err = PFFAT_ReadFATEntryWithBuf(p_vol, start_cluster, &fat_entry, p_page);
        if (err != 0) {
            return err;
        }
        if (fat_entry == 0) {
            if (*p_start_free_cluster == -1) {
                *p_start_free_cluster = start_cluster;
            }
            success_num++;
            if (success_num >= num_cluster) {
                *p_last_free_cluster = start_cluster;
                PFCACHE_FreeDataPage(p_vol, p_page);
                return 0;
            }
        } else {
            if (save_success_num < success_num) {
                save_start_cluster = *p_start_free_cluster;
                save_success_num = success_num;
            }
            *p_start_free_cluster = -1;
            success_num = 0;
        }
        start_cluster++;
        if (search_flg == 0 && success_num == 0 && start_cluster > 2 && start_cluster == end_cluster) {
            end_cluster = temp_start_cluster;
            start_cluster = 2;
            search_flg = 1;
        }
    }
    if (save_success_num < success_num) {
        save_start_cluster = *p_start_free_cluster;
        save_success_num = success_num;
    }
    if (save_success_num != 0) {
        *p_start_free_cluster = save_start_cluster;
        *p_last_free_cluster = save_success_num + save_start_cluster - 1;
    }
    PFCACHE_FreeDataPage(p_vol, p_page);
    return 0;
}

static s32 PFFAT_UpdateClusterLink(PF_FFD* p_ffd, u32 cluster, u32 chain_index) {
    if (p_ffd->cluster_link.max_count > p_ffd->cluster_link.position && p_ffd->cluster_link.max_count != 0) {
        if (chain_index == (p_ffd->cluster_link.position * (p_ffd->cluster_link.interval + 1))) {
            p_ffd->cluster_link.interval_offset = 0;
            p_ffd->cluster_link.buffer[p_ffd->cluster_link.position] = cluster;
            p_ffd->cluster_link.position++;
        } else {
            p_ffd->cluster_link.interval_offset++;
        }
        p_ffd->cluster_link.save_index = chain_index;
    }
    return 0;
}

static s32 PFFAT_ClearClusterLink(PF_FFD* p_ffd, u32 chain_index) {
    u32 position;
    u32 offset;

    position = chain_index / (p_ffd->cluster_link.interval + 1);
    if (p_ffd->cluster_link.max_count >= position) {
        offset = chain_index % (p_ffd->cluster_link.interval + 1);
        if (offset == 0) {
            p_ffd->cluster_link.buffer[position] = 0;
        }
        if (p_ffd->cluster_link.save_index >= chain_index) {
            p_ffd->cluster_link.position = (chain_index - 1) / (p_ffd->cluster_link.interval + 1);
            p_ffd->cluster_link.interval_offset = (chain_index - 1) % (p_ffd->cluster_link.interval + 1);
            p_ffd->cluster_link.save_index = chain_index - 1;
        }
    }
    return 0;
}

s32 PFFAT_FindClusterLink(PF_FFD* p_ffd, u32 chain_index, u32* p_cluster, u32* is_found) {
    u32 current_cluster;
    u32 next_cluster = -1;
    u32 position;
    u32 offset;
    u32 i;
    s32 err;
    PF_CACHE_PAGE* p_page;

    *is_found = 0;
    if (p_ffd->cluster_link.position == 0) {
        return 0;
    }
    if (p_ffd->cluster_link.save_index >= chain_index) {
        position = chain_index / (p_ffd->cluster_link.interval + 1);
        offset = chain_index % (p_ffd->cluster_link.interval + 1);
        if (offset == 0) {
            *p_cluster = p_ffd->cluster_link.buffer[position];
            *is_found = 1;
        } else {
            current_cluster = p_ffd->cluster_link.buffer[position];
            for (i = offset; i != 0; i--) {
                err = PFFAT_ReadFATEntry(p_ffd->p_vol, current_cluster, &next_cluster);
                if (err != 0) {
                    return err;
                }
                if (next_cluster == 0) {
                    return 13;
                }
                current_cluster = next_cluster;
            }

            if (next_cluster == 0) {
                return 13;
            }
            if (next_cluster == fat_special_values[p_ffd->p_vol->bpb.fat_type].eoc2) {
                return 0;
            }
            *p_cluster = next_cluster;
            *is_found = 1;
        }
    } else {
        return 0;
    }
    return 0;
}

s32 PFFAT_FindClusterLinkWithBuf(PF_FFD* p_ffd, u32 chain_index, u32* p_cluster, u32* is_found, PF_CACHE_PAGE* p_page) {
    u32 current_cluster;
    u32 next_cluster = -1;
    u32 position;
    u32 offset;
    u32 i;
    s32 err;

    *is_found = 0;
    if (p_ffd->cluster_link.position == 0) {
        return 0;
    }
    if (p_ffd->cluster_link.save_index < chain_index) {
        goto out1;
    }
    position = chain_index / (p_ffd->cluster_link.interval + 1);
    offset = chain_index % (p_ffd->cluster_link.interval + 1);
    if (offset == 0) {
        *p_cluster = p_ffd->cluster_link.buffer[position];
        *is_found = 1;
        goto out2;
    } else {
        current_cluster = p_ffd->cluster_link.buffer[position];
        for (i = offset; i != 0; i--) {
            err = PFFAT_ReadFATEntryWithBuf(p_ffd->p_vol, current_cluster, &next_cluster, p_page);
            if (err != 0) {
                return err;
            }
            if (next_cluster == 0) {
                return 13;
            }
            current_cluster = next_cluster;
        }

        if (next_cluster == 0) {
            return 13;
        }
        if (next_cluster == fat_special_values[p_ffd->p_vol->bpb.fat_type].eoc2) {
            return 0;
        }
        *p_cluster = next_cluster;
        *is_found = 1;
    }

    // what

    goto out2;

out1:
    return 0;

out2:
    return 0;
}

s32 PFFAT_ResetCluster(PF_VOLUME* p_vol, u32 cluster) {
    s32 err;
    PF_CACHE_PAGE* p_page;
    u32 dummy;
    u32 sector;
    u32 success;
    u32 i;

    err = PFCACHE_AllocateDataPage(p_vol, -1, &p_page, &dummy);
    if (err != 0) {
        return err;
    }
    sector = p_vol->bpb.first_data_sector + ((cluster - 2) << p_vol->bpb.log2_sectors_per_cluster);
    for (i = 0; i < p_vol->bpb.sectors_per_cluster; i++) {
        err = PFSEC_ReadData(p_vol, p_page->p_buf, sector + i, 0, p_vol->bpb.bytes_per_sector, &success, 1);
        if (err != 0) {
            break;
        }
        if (success != p_vol->bpb.bytes_per_sector) {
            break;
        }
        pf_memset(p_page->p_buf, 0, p_vol->bpb.bytes_per_sector);
        err = PFSEC_WriteData(p_vol, p_page->p_buf, sector + i, 0, p_vol->bpb.bytes_per_sector, &success, 1);
        if (err != 0) {
            break;
        }
        if (success != p_vol->bpb.bytes_per_sector) {
            break;
        }
    }
    PFCACHE_FreeDataPage(p_vol, p_page);
    return 0;
}

s32 PFFAT_ReadCluster(PF_FFD* p_ffd, u32 cluster, u32 chain_index, u32* next_cluster, u32* chk_clstlnk) {
    s32 err;

    *next_cluster = -1;
    if (p_ffd->cluster_link.buffer != 0 && *chk_clstlnk == 1) {
        err = PFFAT_FindClusterLink(p_ffd, chain_index, next_cluster, chk_clstlnk);
        if (err != 0) {
            return err;
        }
    }
    if (p_ffd->cluster_link.buffer == 0 || *chk_clstlnk == 0) {
        err = PFFAT_ReadFATEntry(p_ffd->p_vol, cluster, next_cluster);
        if (err != 0) {
            return err;
        }
        if (*next_cluster == 0) {
            return 13;
        }
        if (*next_cluster == -1) {
            return 6;
        }
        if (p_ffd->cluster_link.buffer != 0 && *next_cluster != fat_special_values[p_ffd->p_vol->bpb.fat_type].eoc2) {
            err = PFFAT_UpdateClusterLink(p_ffd, *next_cluster, chain_index);
            if (err != 0) {
                return err;
            }
        }
    }
    return 0;
}

s32 PFFAT_ReadClusterWithBuf(PF_FFD* p_ffd, u32 cluster, u32 chain_index, u32* next_cluster, u32* chk_clstlnk,
                             PF_CACHE_PAGE* p_page) {
    s32 err;

    *next_cluster = -1;
    if (p_ffd->cluster_link.buffer != 0 && *chk_clstlnk == 1) {
        err = PFFAT_FindClusterLinkWithBuf(p_ffd, chain_index, next_cluster, chk_clstlnk, p_page);
        if (err != 0) {
            return err;
        }
    }
    if (p_ffd->cluster_link.buffer == 0 || *chk_clstlnk == 0) {
        err = PFFAT_ReadFATEntryWithBuf(p_ffd->p_vol, cluster, next_cluster, p_page);
        if (err != 0) {
            return err;
        }
        if (*next_cluster == 0) {
            return 13;
        }
        if (*next_cluster == -1) {
            return 6;
        }
        if (p_ffd->cluster_link.buffer != 0 && *next_cluster != fat_special_values[p_ffd->p_vol->bpb.fat_type].eoc2) {
            err = PFFAT_UpdateClusterLink(p_ffd, *next_cluster, chain_index);
            if (err != 0) {
                return err;
            }
        }
    }
    return 0;
}

s32 PFFAT_WriteCluster(PF_FFD* p_ffd, u32 cluster, u32 chain_index, u32 next_cluster, u32 use_clstlnk) {
    s32 err;
    u32 access_cluster;

    err = PFFAT_WriteFATEntry(p_ffd->p_vol, cluster, next_cluster);
    if (err != 0) {
        return err;
    }
    if (p_ffd->cluster_link.buffer != 0 && use_clstlnk == 1) {
        if (next_cluster == 0) {
            PFFAT_ClearClusterLink(p_ffd, chain_index);
        } else {
            if (cluster != fat_special_values[p_ffd->p_vol->bpb.fat_type].eoc2) {
                err = PFFAT_FindClusterLink(p_ffd, chain_index, &access_cluster, &use_clstlnk);
                if (err != 0) {
                    return err;
                }
                if (use_clstlnk == 0) {
                    err = PFFAT_UpdateClusterLink(p_ffd, cluster, chain_index);
                    if (err != 0) {
                        return err;
                    }
                }
            }
        }
    }
    return 0;
}

s32 PFFAT_WriteClusterWithBuf(PF_FFD* p_ffd, u32 cluster, u32 chain_index, u32 next_cluster, u32 use_clstlnk,
                              PF_CACHE_PAGE* p_page) {
    s32 err;
    u32 access_cluster;

    err = PFFAT_WriteFATEntryWithBuf(p_ffd->p_vol, cluster, next_cluster, p_page);
    if (err != 0) {
        return err;
    }
    if (p_ffd->cluster_link.buffer != 0 && use_clstlnk == 1) {
        if (next_cluster == 0) {
            PFFAT_ClearClusterLink(p_ffd, chain_index);
        } else {
            if (cluster != fat_special_values[p_ffd->p_vol->bpb.fat_type].eoc2) {
                err = PFFAT_FindClusterLinkWithBuf(p_ffd, chain_index, &access_cluster, &use_clstlnk, p_page);
                if (err != 0) {
                    return err;
                }
                if (use_clstlnk == 0) {
                    err = PFFAT_UpdateClusterLink(p_ffd, cluster, chain_index);
                    if (err != 0) {
                        return err;
                    }
                }
            }
        }
    }
    return 0;
}

s32 PFFAT_DoAllocateChain(PF_FFD* p_ffd, u32 chain_len, u32 chain_index, u32* p_chain_start, u32* p_last_allocated,
                          u32 reset_flag) {
    PF_VOLUME* p_vol = p_ffd->p_vol;
    u32 eoc2;
    PF_FAT_TYPE fat_type = p_vol->bpb.fat_type;
    u32 first_allocated_cluster;
    u32 last_allocated_cluster;
    u32 start_cluster;
    u32 sector;
    u16 i;
    s32 err;
    s32 fat_err = 0;
    PF_CACHE_PAGE* p_page;
    u32 dummy;

    eoc2 = fat_special_values[fat_type].eoc2;

    *p_chain_start = -1;
    *p_last_allocated = -1;
    last_allocated_cluster = -1;
    err = PFFAT_SearchForNumFreeClusters(p_vol, p_vol->last_free_cluster, -1, chain_len, &first_allocated_cluster,
                                       &last_allocated_cluster);
    if (err != 0) {
        return err;
    }
    if (first_allocated_cluster == -1) {
        return 0;
    }
    if (reset_flag != 0) {
        err = PFFAT_ResetCluster(p_vol, first_allocated_cluster);
        if (err != 0) {
            return err;
        }
    }
    err = PFCACHE_AllocateDataPage(p_vol, -1, &p_page, &dummy);
    if (err != 0) {
        return err;
    }
    err = PFFAT_ReadFATSector(p_vol, p_page, first_allocated_cluster);
    if (err != 0) {
        PFCACHE_FreeDataPage(p_vol, p_page);
        return err;
    }
    p_page->option = 0;

    for (start_cluster = first_allocated_cluster; start_cluster < last_allocated_cluster; start_cluster++) {
        err = PFFAT_WriteClusterWithBuf(p_ffd, start_cluster, chain_index, start_cluster + 1, 1, p_page);
        if (err != 0) {
            PFCACHE_FreeDataPage(p_vol, p_page);
            return err;
        }
        if ((p_vol->fsi_flag & 0x04) != 0 && p_vol->num_free_clusters != -1 && p_vol->num_free_clusters != 0 &&
            (p_vol->bpb.fat_type != FAT_32 || last_allocated_cluster != p_vol->bpb.root_dir_cluster)) {
            p_vol->num_free_clusters--;
        }
        if ((*p_chain_start) == -1) {
            *p_chain_start = start_cluster;
        }
        *p_last_allocated = start_cluster;
        chain_index++;
    }
    if (last_allocated_cluster != -1) {
        err = PFFAT_WriteClusterWithBuf(p_ffd, last_allocated_cluster, chain_index, eoc2, 1, p_page);
        if (err != 0) {
            PFCACHE_FreeDataPage(p_vol, p_page);
            return err;
        }
        if (*p_chain_start == -1) {
            *p_chain_start = start_cluster;
        }
        *p_last_allocated = start_cluster;
        if (p_vol->num_free_clusters != -1 && p_vol->num_free_clusters != 0 &&
            (p_vol->bpb.fat_type != FAT_32 || last_allocated_cluster != p_vol->bpb.root_dir_cluster)) {
            p_vol->num_free_clusters--;
        }
    }
    p_vol->last_free_cluster = last_allocated_cluster + 1;
    p_ffd->last_cluster.num_last_cluster = last_allocated_cluster;
    p_ffd->last_cluster.max_chain_index = chain_index;
    *p_last_allocated = last_allocated_cluster;

    sector = p_page->sector;
    for (i = 0; i < p_vol->bpb.num_active_FATs; i++) {
        err = PFSEC_WriteFAT(p_vol, p_page->p_buf, sector, 0, p_vol->bpb.bytes_per_sector);
        if (err != 0 && fat_err == 0) {
            fat_err = err;
        }
        sector += p_vol->bpb.sectors_per_FAT;
    }
    if (fat_err != 0) {
        PFCACHE_FreeDataPage(p_vol, p_page);
        return fat_err;
    }
    PFCACHE_FreeDataPage(p_vol, p_page);
    if (p_vol->bpb.fat_type == FAT_32 && (p_vol->fsi_flag & 0x02) != 0) {
        err = PFFAT_RefreshFSINFO(p_vol);
        if (err != 0) {
            p_vol->num_free_clusters = -1;
            p_vol->fsi_flag &= ~0x04;
        }
    }
    return 0;
}

static s32 PFFAT_AllocateChain(PF_FFD* p_ffd, u32 chain_len, u32 chain_index, u32* p_chain_start, u32* p_last_allocated,
                               u32 reset_flag) {
    s32 err;

    err = PFFAT_DoAllocateChain(p_ffd, chain_len, chain_index, p_chain_start, p_last_allocated, reset_flag);
    if (err != 0) {
        if (*p_chain_start != -1) {
            PFFAT_FreeChain(p_ffd, *p_chain_start, chain_index, -1);
        }
        *p_chain_start = -1;
        *p_last_allocated = -1;
        return err;
    }
    return 0;
}

// DEBUG NON MATCHING
s32 PFFAT_GetClusterInChain(PF_FFD* p_ffd, u32 chain_index, u32 mode, u32 num_cluster, u32* locate_start,
                            u32* locate_end) {
    u32 bad = fat_special_values[p_ffd->p_vol->bpb.fat_type].bad;
    u32 eoc1 = fat_special_values[p_ffd->p_vol->bpb.fat_type].eoc1;
    u32* p_start;
    u32 start_cluster;
    u32 remaining;
    u32 count;
    u32 index;
    s32 err;
    u32 current_cluster;
    u32 last_access_cluster;
    u32 dummy;
    u32 check_use;
    PF_CACHE_PAGE* p_page;

    *locate_end = -1;
    *locate_start = -1;
    if (p_ffd->last_access_cluster.chain_index != 0 && p_ffd->last_access_cluster.chain_index <= chain_index) {
        last_access_cluster = p_ffd->last_access_cluster.cluster;
        p_start = &last_access_cluster;
        remaining = chain_index - p_ffd->last_access_cluster.chain_index;
        index = p_ffd->last_access_cluster.chain_index + 1;
    } else {
        p_start = p_ffd->p_start_cluster;
        remaining = chain_index;
        index = 1;
    }
    start_cluster = *p_start;
    current_cluster = start_cluster;
    if (mode == 2) {
        if (remaining != 0 && num_cluster != 0) {
            remaining += num_cluster - 1;
        } else {
            remaining = num_cluster;
        }
        count = remaining;
        if (p_ffd->last_cluster.num_last_cluster != 0) {
            start_cluster = p_ffd->last_cluster.num_last_cluster;
            current_cluster = fat_special_values[p_ffd->p_vol->bpb.fat_type].eoc2;
            index = p_ffd->last_cluster.max_chain_index + 1;
            remaining = 0;
            count = p_ffd->last_cluster.max_chain_index + num_cluster - chain_index;
        }
    } else {
        if (mode == 1 && start_cluster == 0) {
            remaining++;
        }
        count = remaining;
    }
    if (remaining != 0) {
        err = PFCACHE_AllocateDataPage(p_ffd->p_vol, -1, &p_page, &dummy);
        if (err != 0) {
            return err;
        }
        err = PFFAT_ReadFATSector(p_ffd->p_vol, p_page, start_cluster);
        if (err != 0) {
            PFCACHE_FreeDataPage(p_ffd->p_vol, p_page);
            return err;
        }
        p_page->option = 0;
        check_use = 1;
        do {
            if (start_cluster != 0) {
                err = PFFAT_ReadClusterWithBuf(p_ffd, start_cluster, index, &current_cluster, &check_use, p_page);
                if (err != 0 && current_cluster != -1) {
                    PFCACHE_FreeDataPage(p_ffd->p_vol, p_page);
                    return err;
                }
            } else {
                index--;
                current_cluster = fat_special_values[p_ffd->p_vol->bpb.fat_type].eoc2;
            }
            if ((current_cluster < 2 || current_cluster >= p_ffd->p_vol->bpb.num_clusters + 2) && current_cluster < eoc1) {
                PFCACHE_FreeDataPage(p_ffd->p_vol, p_page);
                return 14;
            }
            if (mode != 0 && current_cluster >= eoc1) {
                break;
            }
            start_cluster = current_cluster;
            index++;
        } while (remaining-- != 0 && start_cluster < bad);
        count = remaining;
        PFCACHE_FreeDataPage(p_ffd->p_vol, p_page);
    }
    if (mode != 0 && current_cluster >= eoc1) {
        *locate_start = 0;
        err = PFFAT_DoAllocateChain(p_ffd, count + 1, index, locate_start, &current_cluster, 0);
        if (err != 0) {
            if (*locate_start != -1) {
                PFFAT_FreeChain(p_ffd, *locate_start, index, -1);
            }
            *locate_start = -1;
            current_cluster = -1;
        }
        if (err != 0) {
            return err;
        }
        if (current_cluster == -1) {
            return 6;
        }
        if (*p_start == 0) {
            *p_start = *locate_start;
        } else {
            err = PFFAT_WriteCluster(p_ffd, start_cluster, index - 1, *locate_start, 1);
            if (err != 0) {
                return err;
            }
        }
        start_cluster = current_cluster;
    }
    *locate_end = start_cluster;
    return 0;
}

s32 PFFAT_GetClusterContinuousSectorInChain(PF_FFD* p_ffd, u32 initial_cluster, u32 chain_index, u32 size,
                                            u32* p_num_sector) {
    PF_VOLUME* p_vol = p_ffd->p_vol;
    u32 cluster;
    u32 next_cluster;
    u32 check_use;
    s32 err;

    next_cluster = -1;
    cluster = initial_cluster;
    check_use = 1;
    while (next_cluster != 0) {
        err = PFFAT_ReadCluster(p_ffd, cluster, chain_index, &next_cluster, &check_use);
        if (err != 0) {
            return err;
        }
        if ((cluster + 1) != next_cluster) {
            if (next_cluster == fat_special_values[p_vol->bpb.fat_type].eoc2) {
                p_ffd->last_cluster.num_last_cluster = cluster;
                p_ffd->last_cluster.max_chain_index = chain_index - 1;
            }
            break;
        }
        p_ffd->p_hint->chain_index = p_ffd->p_hint->chain_index + 1;
        p_ffd->p_hint->cluster = next_cluster;
        *p_num_sector += p_vol->bpb.sectors_per_cluster;
        if ((*p_num_sector << p_vol->bpb.log2_bytes_per_sector) >= size) {
            break;
        }
        cluster = next_cluster;
        chain_index++;
    }
    return 0;
}

s32 PFFAT_GetClusterAllocatedInChain(PF_FFD* p_ffd, u32 initial_cluster, u32 chain_index, u32 size, u32* p_num_clusters) {
    PF_VOLUME* p_vol = p_ffd->p_vol;
    u32 cluster;
    u32 next_cluster;
    u32 total_size;
    u32 check_use;
    s32 err;

    next_cluster = -1;
    cluster = initial_cluster;
    check_use = 1;
    total_size = 0;
    while (next_cluster != 0) {
        total_size += p_vol->bpb.bytes_per_sector * p_vol->bpb.sectors_per_cluster;
        (*p_num_clusters)++;
        if (total_size >= size) {
            break;
        }
        err = PFFAT_ReadCluster(p_ffd, cluster, chain_index, &next_cluster, &check_use);
        if (err != 0) {
            return err;
        }
        if (next_cluster == fat_special_values[p_vol->bpb.fat_type].eoc2) {
            p_ffd->last_cluster.num_last_cluster = cluster;
            p_ffd->last_cluster.max_chain_index = chain_index - 1;
            break;
        }
        cluster = next_cluster;
        chain_index++;
    }
    return 0;
}

s32 PFFAT_GetClusterSpecified(PF_FFD* p_ffd, u32 chain_index, u32 is_contiguous, u32* p_cluster) {
    PF_VOLUME* p_vol = p_ffd->p_vol;
    PF_FAT_TYPE fat_type = p_vol->bpb.fat_type;
    PF_FAT_HINT* p_hint = p_ffd->p_hint;
    u32 found;
    u32 locate_end;
    u32 locate_start;
    s32 err;

    if (*p_ffd->p_start_cluster == 0 && is_contiguous == 0) {
        *p_cluster = -1;
        return 0;
    }
    if (*p_ffd->p_start_cluster == 1) {
        if ((u32)fat_type <= FAT_16) {
            *p_cluster = -1;
            return 0;
        }
        *p_ffd->p_start_cluster = p_vol->bpb.root_dir_cluster;
    }
    if (p_ffd->cluster_link.buffer != 0 && is_contiguous == 0) {
        err = PFFAT_FindClusterLink(p_ffd, chain_index, p_cluster, &found);
        if (err != 0) {
            return err;
        }
        if (found == 1) {
            p_hint->start_cluster = p_ffd->start_cluster;
            p_hint->chain_index = chain_index;
            p_hint->cluster = *p_cluster;
            return 0;
        }
    }
    *p_cluster = -1;
    err = PFFAT_GetClusterInChain(p_ffd, chain_index, is_contiguous != 0, 0, &locate_start, &locate_end);
    if (err == 0) {
        if (locate_end >= 2 && locate_end < p_ffd->p_vol->bpb.num_clusters + 2) {
            *p_cluster = locate_end;
        }
        err = 0;
    } else {
        goto recheck;
    }
recheck:
    if (err != 0) {
        return err;
    }
    if (*p_cluster == -1) {
        return 0;
    }
    p_hint->start_cluster = p_ffd->start_cluster;
    p_hint->chain_index = chain_index;
    p_hint->cluster = *p_cluster;
    return 0;
}

s32 PFFAT_GetClusterAllocated(PF_FFD* p_ffd, u32 chain_index, u32 num_cluster, u32* p_cluster) {
    PF_VOLUME* p_vol = p_ffd->p_vol;
    PF_FAT_TYPE fat_type = p_vol->bpb.fat_type;
    PF_FAT_HINT* p_hint = p_ffd->p_hint;
    u32 locate_end;
    u32 locate_start;
    s32 err;

    if (*p_ffd->p_start_cluster == 1) {
        if ((u32)fat_type <= FAT_16) {
            *p_cluster = -1;
            return 0;
        }
        *p_ffd->p_start_cluster = p_vol->bpb.root_dir_cluster;
    }
    *p_cluster = -1;
    err = PFFAT_GetClusterInChain(p_ffd, chain_index, 2, num_cluster, &locate_start, &locate_end);
    if (err == 0) {
        if (locate_start >= 2 && locate_start < p_ffd->p_vol->bpb.num_clusters + 2) {
            *p_cluster = locate_start;
        }
        err = 0;
    }
    if (err) {
        return err;
    }
    if (*p_cluster == -1) {
        return 0;
    }
    p_hint->start_cluster = p_ffd->start_cluster;
    p_hint->chain_index = chain_index;
    p_hint->cluster = *p_cluster;
    return 0;
}

s32 PFFAT_GetSector(PF_FFD* p_ffd, u32 chain_index, u32 is_contiguous, u32 num_bytes, u32* p_sector) {
    PF_VOLUME* p_vol = p_ffd->p_vol;
    PF_FAT_TYPE fat_type = p_vol->bpb.fat_type;
    u32 cluster;
    u32 num_clusters;
    u32 chain_cluster;
    s32 err;

    if (*p_ffd->p_start_cluster == 1 && (u32)fat_type <= FAT_16) {
        if (chain_index >= p_vol->bpb.num_root_dir_sectors) {
            *p_sector = -1;
            err = 0;
        } else {
            *p_sector = p_vol->bpb.first_root_dir_sector + chain_index;
            err = 0;
        }
        if (err != 0) {
            return err;
        }
        return 0;
    }
    chain_cluster = chain_index >> p_vol->bpb.log2_sectors_per_cluster;
    if (is_contiguous == 2) {
        num_clusters = num_bytes / p_vol->bpb.bytes_per_sector + (num_bytes % p_vol->bpb.bytes_per_sector != 0);
        num_clusters = num_clusters / p_vol->bpb.sectors_per_cluster +
                       (num_clusters % p_vol->bpb.sectors_per_cluster != 0);
        err = PFFAT_GetClusterAllocated(p_ffd, chain_cluster, num_clusters, &cluster);
        if (err != 0) {
            return err;
        }
    } else {
        err = PFFAT_GetClusterSpecified(p_ffd, chain_cluster, is_contiguous, &cluster);
        if (err != 0) {
            return err;
        }
    }
    if (cluster == -1) {
        *p_sector = -1;
        return 0;
    }
    *p_sector = p_vol->bpb.first_data_sector + ((cluster - 2) << p_vol->bpb.log2_sectors_per_cluster) +
                (chain_index & (p_vol->bpb.sectors_per_cluster - 1));
    return 0;
}

s32 PFFAT_GetSectorSpecified(PF_FFD* p_ffd, u32 chain_index, u32 is_contiguous, u32* p_sector) {
    s32 err;

    err = PFFAT_GetSector(p_ffd, chain_index, is_contiguous != 0, 0, p_sector);
    if (err != 0) {
        return err;
    }
    return 0;
}

s32 PFFAT_GetSectorAllocated(PF_FFD* p_ffd, u32 chain_index, u32 num_bytes, u32* p_sector) {
    s32 err;

    err = PFFAT_GetSector(p_ffd, chain_index, 2, num_bytes, p_sector);
    return (err != 0) ? err : 0;
}

s32 PFFAT_getContinuousSector(PF_FFD* p_ffd, u32 chain_index, u32 size, u32* p_sector, u32* p_num_sector) {
    PF_VOLUME* p_vol = p_ffd->p_vol;
    u32 cluster;
    s32 err;

    cluster = -1;
    if (*p_sector != -1) {
        cluster = ((*p_sector - p_vol->bpb.first_data_sector) >> p_vol->bpb.log2_sectors_per_cluster) + 2;
    } else {
        err = PFFAT_GetSector(p_ffd, chain_index, 0, 0, p_sector);
        err = (err != 0) ? err : 0;
        if (err != 0) {
            return err;
        }
        if (*p_sector != -1) {
            cluster = ((*p_sector - p_vol->bpb.first_data_sector) >> p_vol->bpb.log2_sectors_per_cluster) + 2;
        }
    }
    if (*p_sector != -1) {
        *p_num_sector = ((cluster - 1) << p_vol->bpb.log2_sectors_per_cluster) + p_vol->bpb.first_data_sector - *p_sector;
    } else {
        *p_num_sector = 0;
    }
    if (*p_sector != -1 && (*p_num_sector << p_vol->bpb.log2_bytes_per_sector) < size) {
        err = PFFAT_GetClusterContinuousSectorInChain(p_ffd, cluster,
                                                    (chain_index >> p_vol->bpb.log2_sectors_per_cluster) + 1, size,
                                                    p_num_sector);
        if (err != 0) {
            return err;
        }
    }
    return 0;
}

s32 PFFAT_CountAllocatedClusters(PF_FFD* p_ffd, u32 size, u32* p_num_alloc_clusters) {
    u32 cluster;
    u32 chain_index;
    s32 err;

    *p_num_alloc_clusters = 0;
    cluster = *p_ffd->p_start_cluster;
    if (cluster < 2) {
        return 0;
    }
    if (p_ffd->last_cluster.num_last_cluster != 0) {
        *p_num_alloc_clusters = p_ffd->last_cluster.max_chain_index + 1;
        return 0;
    }
    if (p_ffd->p_hint->cluster != 0) {
        if (size <= (u32)((p_ffd->p_hint->chain_index + 1) *
                          (p_ffd->p_vol->bpb.bytes_per_sector * p_ffd->p_vol->bpb.sectors_per_cluster))) {
            *p_num_alloc_clusters = p_ffd->p_hint->chain_index + 1;
            return 0;
        }
        *p_num_alloc_clusters = p_ffd->p_hint->chain_index;
        cluster = p_ffd->p_hint->cluster;
        chain_index = p_ffd->p_hint->chain_index + 1;
        size -= p_ffd->p_hint->chain_index *
                (p_ffd->p_vol->bpb.bytes_per_sector * p_ffd->p_vol->bpb.sectors_per_cluster);
    } else {
        chain_index = 1;
    }
    err = PFFAT_GetClusterAllocatedInChain(p_ffd, cluster, chain_index, size, p_num_alloc_clusters);
    if (err != 0) {
        return err;
    }
    return 0;
}

s32 PFFAT_CountFreeClusters(PF_VOLUME* p_vol, u32* p_num_free_clusters) {
    u32 next_cluster;
    u32 dummy;
    PF_CACHE_PAGE* p_page;
    u32 free_cluster;
    s32 err;

    if ((p_vol->fsi_flag & 0x04) != 0 && p_vol->num_free_clusters != -1) {
        *p_num_free_clusters = p_vol->num_free_clusters;
        return 0;
    }
    *p_num_free_clusters = 0;
    free_cluster = 2;
    err = PFCACHE_AllocateDataPage(p_vol, -1, &p_page, &dummy);
    if (err != 0) {
        return err;
    }
    err = PFFAT_ReadFATSector(p_vol, p_page, 2);
    if (err != 0) {
        PFCACHE_FreeDataPage(p_vol, p_page);
        return err;
    }
    p_page->option = 0;
    for (; free_cluster >= 2 && free_cluster < (p_vol->bpb.num_clusters + 2); free_cluster++) {
        err = PFFAT_ReadFATEntryWithBuf(p_vol, free_cluster, &next_cluster, p_page);
        if (err != 0) {
            PFCACHE_FreeDataPage(p_vol, p_page);
            return err;
        }
        if (next_cluster == 0) {
            (*p_num_free_clusters)++;
        }
    }
    PFCACHE_FreeDataPage(p_vol, p_page);
    p_vol->fsi_flag |= 0x04;
    p_vol->num_free_clusters = *p_num_free_clusters;
    if (p_vol->bpb.fat_type == FAT_32 && (p_vol->fsi_flag & 0x02) != 0) {
        err = PFFAT_RefreshFSINFO(p_vol);
        if (err != 0) {
            p_vol->num_free_clusters = -1;
            p_vol->fsi_flag &= ~0x04;
        }
    }
    return 0;
}

s32 PFFAT_FreeChain(PF_FFD* p_ffd, u32 start_cluster, u32 chain_index, u32 size) {
    PF_VOLUME* p_vol = p_ffd->p_vol;
    u32 eoc1;
    u32 next_cluster;
    u32 file_size;
    u32 clst_size;
    u32 sector;
    u32 dummy;
    u32 i;
    s32 fat_err;
    s32 err;
    PF_CACHE_PAGE* p_page;

    if (start_cluster == 0) {
        return 0;
    }
    eoc1 = fat_special_values[p_vol->bpb.fat_type].eoc1;
    if (size != 0) {
        file_size = size;
        clst_size = p_vol->bpb.bytes_per_sector << p_vol->bpb.log2_sectors_per_cluster;
    } else {
        return 0;
    }
    err = PFCACHE_AllocateDataPage(p_vol, -1, &p_page, &dummy);
    if (err != 0) {
        return err;
    }
    err = PFFAT_ReadFATSector(p_vol, p_page, start_cluster);
    if (err != 0) {
        PFCACHE_FreeDataPage(p_vol, p_page);
        return err;
    }
    p_page->option = 1;
    next_cluster = start_cluster;
    while (start_cluster < eoc1) {
        if (size != 0 && file_size == 0) {
            break;
        }
        err = PFFAT_ReadFATEntryWithBuf(p_vol, start_cluster, &next_cluster, p_page);
        if (err != 0) {
            PFCACHE_FreeDataPage(p_vol, p_page);
            return err;
        }
        if (next_cluster == 0) {
            PF_CACHE_PAGE* page = p_page;
            err = 0;
            i = 0;
            sector = page->sector;
            for (; (u16)i < p_vol->bpb.num_active_FATs; i++) {
                s32 e = PFSEC_WriteFAT(p_vol, page->p_buf, sector, 0, p_vol->bpb.bytes_per_sector);
                if (e != 0 && err == 0) {
                    err = e;
                }
                sector += p_vol->bpb.sectors_per_FAT;
            }
            if (err != 0) {
                PFCACHE_FreeDataPage(p_vol, p_page);
                return err;
            }
            PFCACHE_FreeDataPage(p_vol, p_page);
            return 0;
        }
        if (chain_index != -1) {
            err = PFFAT_WriteClusterWithBuf(p_ffd, start_cluster, chain_index, 0, 1, p_page);
            chain_index++;
        } else {
            err = PFFAT_WriteFATEntryWithBuf(p_vol, start_cluster, 0, p_page);
        }
        if (err != 0) {
            PFCACHE_FreeDataPage(p_vol, p_page);
            return err;
        }
        if (size != 0 && file_size != 0) {
            file_size = (file_size <= clst_size) ? 0 : (file_size - clst_size);
        }
        if (p_vol->num_free_clusters != -1) {
            p_vol->num_free_clusters++;
        }
        start_cluster = next_cluster;
    }
    {
        PF_CACHE_PAGE* page = p_page;
        err = 0;
        i = 0;
        sector = page->sector;
        for (; (u16)i < p_vol->bpb.num_active_FATs; i++) {
            s32 e = PFSEC_WriteFAT(p_vol, page->p_buf, sector, 0, p_vol->bpb.bytes_per_sector);
            if (e != 0 && err == 0) {
                err = e;
            }
            sector += p_vol->bpb.sectors_per_FAT;
        }
    }
    if (err != 0) {
        PFCACHE_FreeDataPage(p_vol, p_page);
        return err;
    }
    PFCACHE_FreeDataPage(p_vol, p_page);
    if (p_vol->bpb.fat_type == FAT_32 && (p_vol->fsi_flag & 0x02) != 0) {
        err = PFFAT_RefreshFSINFO(p_vol);
        if (err != 0) {
            p_vol->num_free_clusters = -1;
            p_vol->fsi_flag &= ~0x04;
        }
    }
    return 0;
}

s32 PFFAT_getBeforeChain(PF_VOLUME* p_vol, u32 start_cluster, u32 lActive, u32* p_cluster) {
    PF_CACHE_PAGE* p_page;
    u32 eoc1;
    u32 value;
    u32 dummy;
    s32 err;

    eoc1 = fat_special_values[p_vol->bpb.fat_type].eoc1;
    *p_cluster = -1;
    err = PFCACHE_AllocateDataPage(p_vol, -1, &p_page, &dummy);
    if (err != 0) {
        return err;
    }
    p_page->option = 0;
    while (start_cluster < eoc1) {
        err = PFFAT_ReadFATEntryWithBuf(p_vol, start_cluster, &value, p_page);
        if (err != 0) {
            PFCACHE_FreeDataPage(p_vol, p_page);
            return err;
        }
        if (lActive == value) {
            *p_cluster = start_cluster;
            return 0;
        }
        start_cluster--;
        if ((start_cluster < 2 || start_cluster >= (p_vol->bpb.num_clusters + 2)) && start_cluster < eoc1) {
            *p_cluster = lActive;
            return 0;
        }
    }
    PFCACHE_FreeDataPage(p_vol, p_page);
    return 13;
}

s32 PFFAT_GetBeforeSector(u32* p_befor_sector, PF_VOLUME* p_vol, u32 current_sector) {
    s32 err;
    u32 sector_index;
    u32 current_cluster;
    u32 befor_cluster;

    err = 0;
    if (p_befor_sector == 0 || p_vol == 0) {
        return 0xA;
    }
    if (current_sector < p_vol->bpb.first_root_dir_sector) {
        return 0xA;
    }
    if (p_vol->bpb.fat_type != FAT_32 && current_sector < p_vol->bpb.first_data_sector) {
        current_sector--;
        if (current_sector < p_vol->bpb.first_root_dir_sector) {
            err = 0x22;
        }
    } else {
        sector_index = (p_vol->bpb.sectors_per_cluster - 1) & (current_sector - p_vol->bpb.first_data_sector);
        if (sector_index == 0) {
            current_cluster = ((current_sector - p_vol->bpb.first_data_sector) >> p_vol->bpb.log2_sectors_per_cluster) + 2;
            err = PFFAT_getBeforeChain(p_vol, current_cluster, current_cluster, &befor_cluster);
            if (err == 0) {
                if (befor_cluster == -1U) {
                    current_sector = -1U;
                } else {
#ifdef DEBUG
                    current_sector = (p_vol->bpb.sectors_per_cluster + p_vol->bpb.first_data_sector) +
                                     ((befor_cluster - 2) << p_vol->bpb.log2_sectors_per_cluster);
                    current_sector--;
#else
                    current_sector = (p_vol->bpb.sectors_per_cluster + p_vol->bpb.first_data_sector) +
                                     ((befor_cluster - 2) << p_vol->bpb.log2_sectors_per_cluster) - 1;
#endif
                }
            }
        } else {
            current_sector--;
        }
    }
    if (err == 0) {
        *p_befor_sector = current_sector;
    } else {
        *p_befor_sector = -1U;
    }
    return err;
}

s32 PFFAT_InitFATRegion(PF_VOLUME* p_vol) {
    s32 err;
    PF_CACHE_PAGE* p_page;
    u32 sector;
    u32 dummy;

    err = PFCACHE_AllocateFATPage(p_vol, -1, &p_page, &dummy);
    if (err != 0) {
        return err;
    }
    pf_memset(p_page->p_buf, 0, p_vol->bpb.bytes_per_sector);
    for (sector = p_vol->bpb.num_reserved_sectors; sector < p_vol->bpb.first_root_dir_sector; sector++) {
        err = PFCACHE_WriteFATSectorAndFreeIfNeeded(p_vol, p_page->p_buf, sector);
        if (err != 0) {
            PFCACHE_FreeFATPage(p_vol, p_page);
            return err;
        }
    }
    PFCACHE_FreeFATPage(p_vol, p_page);
    err = PFFAT_WriteFATEntry(p_vol, 0, p_vol->bpb.media | fat_special_values[p_vol->bpb.fat_type].fat0_mask);
    if (err != 0) {
        return err;
    }
    err = PFFAT_WriteFATEntry(p_vol, 1, fat_special_values[p_vol->bpb.fat_type].fat1);
    if (err != 0) {
        return err;
    }
    err = PFCACHE_FlushFATCache(p_vol);
    return (err != 0) ? err : 0;
}

s32 PFFAT_MakeRootDir(PF_VOLUME* p_vol) {
    s32 err;
    u32 sector;
    u32 i;
    u32 success;
    u32 dummy;
    PF_CACHE_PAGE* p_page;

    err = PFFAT_WriteFATEntry(p_vol, p_vol->bpb.root_dir_cluster, fat_special_values[p_vol->bpb.fat_type].eoc2);
    if (err != 0) {
        return err;
    }
    err = PFCACHE_FlushFATCache(p_vol);
    if (err != 0) {
        return err;
    }
    err = PFCACHE_AllocateDataPage(p_vol, -1, &p_page, &dummy);
    if (err != 0) {
        return err;
    }
    pf_memset(p_page->p_buf, 0, p_vol->bpb.bytes_per_sector);
    sector = p_vol->bpb.first_data_sector +
             ((p_vol->bpb.root_dir_cluster - 2) << p_vol->bpb.log2_sectors_per_cluster);
    for (i = 0; i < p_vol->bpb.sectors_per_cluster; i++) {
        err = PFSEC_WriteData(p_vol, p_page->p_buf, sector + i, 0, p_vol->bpb.bytes_per_sector, &success, 0);
        if (err != 0) {
            PFCACHE_FreeDataPage(p_vol, p_page);
            return err;
        }
        if (success != p_vol->bpb.bytes_per_sector) {
            PFCACHE_FreeDataPage(p_vol, p_page);
            return 0x11;
        }
    }
    PFCACHE_FreeDataPage(p_vol, p_page);
    return 0;
}

s32 PFFAT_RefreshFSINFO(PF_VOLUME* p_vol) {
    s32 err;
    PF_CACHE_PAGE* p_page;
    u32 dummy;
    u32 success;
    u8* p_buf;

    err = 0;
    if ((p_vol->fsi_flag & 0x04) != 0) {
    err = PFCACHE_AllocateDataPage(p_vol, -1, &p_page, &dummy);
    if (err != 0) {
        return err;
    }
    err = PFSEC_ReadData(p_vol, p_page->p_buf, p_vol->bpb.fs_info_sector, 0, p_vol->bpb.bytes_per_sector, &success, 0);
    if (err == 0 && success != p_vol->bpb.bytes_per_sector) {
        err = 0x11;
    }
    if (err == 0) {
        p_buf = p_page->p_buf;
        if (((u32)(p_page->p_buf + 0x1E8) & 0x3) != 0) {
            *(p_page->p_buf + 0x1E8) = (u8)p_vol->num_free_clusters;
            p_page->p_buf[0x1E9] = (u8)(p_vol->num_free_clusters >> 8);
            p_page->p_buf[0x1EA] = (u8)(p_vol->num_free_clusters >> 16);
            p_page->p_buf[0x1EB] = (u8)(p_vol->num_free_clusters >> 24);
        } else {
            *(u32*)(p_buf + 0x1E8) = ((p_vol->num_free_clusters << 24) |
                                     ((p_vol->num_free_clusters << 8) & 0xFF0000)) |
                                    ((p_vol->num_free_clusters >> 24) |
                                     ((p_vol->num_free_clusters >> 8) & 0xFF00));
        }
        err = PFSEC_WriteData(p_vol, p_page->p_buf, p_vol->bpb.fs_info_sector, 0, p_vol->bpb.bytes_per_sector, &success, 0);
        if (err == 0 && success != p_vol->bpb.bytes_per_sector) {
            err = 0x11;
        }
    }
    PFCACHE_FreeDataPage(p_vol, p_page);
    }
    return err;
}

s32 PFFAT_TraceClustersChain(PF_FFD* p_ffd, u32 start_clst, u32 size, u32* p_target_clst, u32* p_next_clst) {
    PF_VOLUME* p_vol;
    u32 next_cluster;
    u32 chain_index;
    u32 clst_size;
    u32 clst_cnt;
    u32 cnt;
    u32 check_use;
    s32 err;

    *p_target_clst = 0;
    *p_next_clst = 0;
    if (*p_ffd->p_start_cluster < 2) {
        return 0;
    }
    if (start_clst < 2) {
        return 0;
    }
    if (size == 0) {
        return 0;
    }
    p_vol = p_ffd->p_vol;
    if (size == -1 && p_ffd->last_cluster.num_last_cluster != 0) {
        *p_target_clst = p_ffd->last_cluster.num_last_cluster;
        *p_next_clst = fat_special_values[p_vol->bpb.fat_type].eoc2;
        return 0;
    }
    clst_size = p_vol->bpb.bytes_per_sector * p_vol->bpb.sectors_per_cluster;
    clst_cnt = size / clst_size;
    if ((size % clst_size) != 0) {
        clst_cnt++;
    }
    if (*p_ffd->p_start_cluster == start_clst) {
        chain_index = 1;
    } else {
        chain_index = p_ffd->p_hint->chain_index + 1;
    }
    next_cluster = -1;
    check_use = 1;
    for (cnt = 0; cnt < clst_cnt; cnt++) {
        err = PFFAT_ReadCluster(p_ffd, start_clst, chain_index, &next_cluster, &check_use);
        if (err != 0) {
            return err;
        }
        if (next_cluster == fat_special_values[p_vol->bpb.fat_type].eoc2) {
            p_ffd->last_cluster.num_last_cluster = start_clst;
            p_ffd->last_cluster.max_chain_index = chain_index - 1;
            break;
        }
        start_clst = next_cluster;
        chain_index++;
    }
    p_ffd->p_hint->chain_index = chain_index - 1;
    *p_target_clst = start_clst;
    *p_next_clst = next_cluster;
    return 0;
}

s32 PFFAT_WriteValueToSpecifiedCluster(PF_VOLUME* p_vol /* r1+0x8 */, u32 cluster /* r1+0xC */, u32 value /* r1+0x10 */) {
    s32 err;

    err = PFFAT_WriteFATEntry(p_vol, cluster, value);
    if (err != 0) {
        return err;
    }
    return 0;
}

s32 PFFAT_ReadValueToSpecifiedCluster(PF_VOLUME* p_vol, u32 cluster, u32* value) {
    s32 err;

    err = PFFAT_ReadFATEntry(p_vol, cluster, value);
    if (err != 0) {
        return err;
    }
    return 0;
}

s32 PFFAT_AllocateNumClusters(PF_FFD* p_ffd, u32 allocate_size, u32* p_start_allocated, u32* p_last_allocated,
                              u32* p_num_allocate_size) {
    PF_VOLUME* p_vol;
    u32 clst_size;
    s32 err;
    u32 num_cluster;
    u32 get_num_clusters;

    p_vol = p_ffd->p_vol;
    clst_size = p_vol->bpb.bytes_per_sector << p_vol->bpb.log2_sectors_per_cluster;
    num_cluster = allocate_size / clst_size;
    if ((allocate_size - (num_cluster * clst_size)) != 0) {
        num_cluster++;
    }
    err = PFFAT_DoAllocateChain(p_ffd, num_cluster, 1, p_start_allocated, p_last_allocated, 0);
    if (err != 0) {
        if (*p_start_allocated != -1) {
            PFFAT_FreeChain(p_ffd, *p_start_allocated, 1, -1);
        }
        *p_start_allocated = -1;
        *p_last_allocated = -1;
    } else {
        err = 0;
    }
    if (err != 0) {
        return err;
    }
    if ((*p_start_allocated == -1) || (*p_last_allocated == -1)) {
        *p_num_allocate_size = 0;
        return 0;
    }
    get_num_clusters = (*p_last_allocated - *p_start_allocated) + 1;
    if (num_cluster == get_num_clusters) {
        *p_num_allocate_size = allocate_size;
    } else {
        *p_num_allocate_size = get_num_clusters * clst_size;
    }
    return 0;
}

void PFFAT_InitHint(PF_FAT_HINT* p_hint) {
    p_hint->chain_index = 0;
    p_hint->cluster = 0;
    p_hint->start_cluster = 0;
}

static void PFFAT_SetHint(PF_FFD* p_ffd, PF_FAT_HINT* p_hint) {
    p_ffd->p_hint = p_hint;
}

s32 PFFAT_ResetFFD(PF_FFD* p_ffd, u32* p_start_cluster) {
    p_ffd->p_start_cluster = p_start_cluster;
    p_ffd->start_cluster = 1;
    if (p_ffd->p_hint != 0) {
        p_ffd->p_hint->start_cluster = 0;
    }
    p_ffd->last_access_cluster.cluster = 0;
    p_ffd->last_access_cluster.chain_index = 0;
    p_ffd->last_cluster.num_last_cluster = 0;
    p_ffd->last_cluster.max_chain_index = 0;
    p_ffd->cluster_link.buffer = 0;
    return 0;
}

s32 PFFAT_InitFFD(PF_FFD* p_ffd, PF_FAT_HINT* p_hint, PF_VOLUME* p_vol, u32* p_start_cluster) {
    p_ffd->p_hint = p_hint;
    p_ffd->p_vol = p_vol;
    p_ffd->p_start_cluster = p_start_cluster;
    p_ffd->start_cluster = 1;
    if (p_hint != 0) {
        p_hint->start_cluster = 0;
    }
    p_ffd->last_access_cluster.cluster = 0;
    p_ffd->last_access_cluster.chain_index = 0;
    p_ffd->last_cluster.num_last_cluster = 0;
    p_ffd->last_cluster.max_chain_index = 0;
    p_ffd->cluster_link.buffer = 0;
    return 0;
}

s32 PFFAT_FinalizeFFD(PF_FFD* p_ffd) {
    p_ffd->cluster_link.buffer = 0;
    return 0;
}

static void PFFAT_SetLastAccess(PF_FFD* p_ffd, PF_FAT_HINT* last_access) {
    p_ffd->last_access_cluster.cluster = last_access->cluster;
    p_ffd->last_access_cluster.chain_index = last_access->chain_index;
}

u32 PFFAT_GetValueOfEOC2(PF_VOLUME* p_vol) {
    return fat_special_values[p_vol->bpb.fat_type].eoc2;
}
