#include <private/vf/PrFILE2/fatfs/pf_cache.h>
#include <private/vf/PrFILE2/pf_types.h>
#include <revolution/types.h>

enum {
    FAT_12 = 0,
    FAT_16 = 1,
    FAT_32 = 2,
    FAT_MAX = 3
};

typedef struct PFFAT_BPB {
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
    u8 reserved_1b;
    s32 fat_type;
    u8 log2_bytes_per_sector;
    u8 log2_sectors_per_cluster;
    u8 num_active_FATs;
    u8 reserved_23;
    u16 num_root_dir_sectors;
    u16 reserved_26;
    u32 active_FAT_sector;
    u32 first_root_dir_sector;
    u32 first_data_sector;
    u32 num_clusters;
} PFFAT_BPB;

typedef s32 (*PFFAT_ErrorCallback)(s32 error);

struct PF_VOLUME {
    PFFAT_BPB bpb;
    u32 num_free_clusters;
    u32 last_free_cluster;
    u8 volume_state[0x1F80 - 0x40];
    s32 last_error;
    s32 last_driver_error;
    u32 reserved_1f88;
    u16 flags;
    u16 options;
    u16 fsi_flag;
    u16 cluster_link_flags;
    u16 cluster_link_interval;
    u32* cluster_link_buffer;
    u32 cluster_link_capacity;
    void* driver_partition;
    PFFAT_ErrorCallback error_callback;
    const u8* format_options;
};

typedef struct PFFAT_LAST_CLUSTER {
    u32 num_last_cluster;
    u32 max_chain_index;
} PFFAT_LAST_CLUSTER;

typedef struct PFFAT_FAT_LAST_ACCESS {
    u32 chain_index;
    u32 cluster;
} PFFAT_FAT_LAST_ACCESS;

typedef struct PFFAT_CLUSTER_LINK {
    u32* buffer;
    u16 interval;
    u16 interval_offset;
    u32 position;
    u32 max_count;
    u32 save_index;
} PFFAT_CLUSTER_LINK;

typedef struct PFFAT_HINT {
    u32 chain_index;
    u32 cluster;
    u32 previous_cluster;
} PFFAT_HINT;

typedef struct PFFAT_FFD {
    u32 start_cluster;
    u32 flags;
    u32* p_start_cluster;
    PFFAT_LAST_CLUSTER last_cluster;
    PFFAT_FAT_LAST_ACCESS last_access_cluster;
    PFFAT_CLUSTER_LINK cluster_link;
    PFFAT_HINT* p_hint;
    PF_VOLUME* p_vol;
} PFFAT_FFD;

const u32 fat_special_values[FAT_MAX*5+1] = {
    0xFF7, 0xFF8, 0xFFF, 0xF00, 0xFFF,
    0xFFF7, 0xFFF8, 0xFFFF, 0xFF00, 0xFFFF,
    0xFFFFFF7, 0xFFFFFF8, 0xFFFFFFF, 0xFFFFF00, 0xFFFFFFF, 0
};


extern s32 PFSEC_ReadFAT(PF_VOLUME* volume, u8* buffer, u32 sector, u16 offset,
                         u16 size);
extern s32 PFCACHE_AllocateDataPage(PF_VOLUME* volume, u32 sector,
                                    PF_CACHE_PAGE** page, s32* alreadyAllocated);
extern s32 PFCACHE_AllocateFATPage(PF_VOLUME* volume, u32 sector,
                                   PF_CACHE_PAGE** page, s32* alreadyAllocated);
extern void PFCACHE_FreeDataPage(PF_VOLUME* volume, PF_CACHE_PAGE* page);
extern void PFCACHE_FreeFATPage(PF_VOLUME* volume, PF_CACHE_PAGE* page);
extern s32 PFCACHE_WriteFATSectorAndFreeIfNeeded(PF_VOLUME* volume,
                                                 u8* buffer,
                                                 u32 sector);
extern s32 PFFAT12_ReadFATEntryWithBuf(PF_VOLUME* volume, u16 cluster,
                                       u32* value, PF_CACHE_PAGE* page);
extern s32 PFFAT12_ReadFATEntry(PF_VOLUME* volume, u16 cluster, u32* value);
extern s32 PFFAT16_ReadFATEntryWithBuf(PF_VOLUME* volume, u32 cluster,
                                       u32* value, PF_CACHE_PAGE* page);
extern s32 PFFAT16_ReadFATEntry(PF_VOLUME* volume, u32 cluster, u32* value);
extern s32 PFFAT32_ReadFATEntryWithBuf(PF_VOLUME* volume, u32 cluster,
                                       u32* value, PF_CACHE_PAGE* page);
extern s32 PFFAT32_ReadFATEntry(PF_VOLUME* volume, u32 cluster, u32* value);
extern s32 PFFAT12_WriteFATEntry(PF_VOLUME* volume, u16 cluster, u16 value);
extern s32 PFFAT16_WriteFATEntry(PF_VOLUME* volume, u32 cluster, u32 value);
extern s32 PFFAT32_WriteFATEntry(PF_VOLUME* volume, u32 cluster, u32 value);
extern s32 PFFAT12_WriteFATEntryWithBuf(PF_VOLUME* volume, u16 cluster,
                                        u16 value, PF_CACHE_PAGE* page);
extern s32 PFFAT16_WriteFATEntryWithBuf(PF_VOLUME* volume, u32 cluster,
                                        u32 value, PF_CACHE_PAGE* page);
extern s32 PFFAT32_WriteFATEntryWithBuf(PF_VOLUME* volume, u32 cluster,
                                        u32 value, PF_CACHE_PAGE* page);
extern s32 PFSEC_ReadData(PF_VOLUME* volume, u8* buffer, u32 sector,
                          u16 offset, u16 size, u32* completedBytes,
                          u32 numSectors);
extern s32 PFSEC_WriteData(PF_VOLUME* volume, u8* buffer, u32 sector,
                           u16 offset, u16 size, u32* completedBytes,
                           u32 numSectors);
extern s32 PFSEC_WriteFAT(PF_VOLUME* volume, u8* buffer, u32 sector,
                          u16 offset, u16 size);
extern s32 PFFAT_RefreshFSINFO(PF_VOLUME* volume);
extern s32 PFCACHE_FlushFATCache(PF_VOLUME* volume);
extern void* pf_memset(void* destination, s32 value, u32 size);

s32 PFFAT_FreeChain(PFFAT_FFD* file, u32 startCluster, u32 chainIndex,
                    u32 size);

s32 PFFAT_ReadFATSector(PF_VOLUME* volume, PF_CACHE_PAGE* page, u32 cluster)
{
    u32 offset;
    s32 error;
    u32 currentFAT;
    s32 callbackResult;

    switch (volume->bpb.fat_type) {
    case FAT_12:
        offset = (u16)(cluster + (cluster >> 1));
        break;
    case FAT_16:
        offset = cluster * sizeof(u16);
        break;
    case FAT_32:
        offset = cluster * sizeof(u32);
        break;
    default:
        return 15;
    }

    page->sector = (u16)(volume->bpb.active_FAT_sector +
                         (offset >> volume->bpb.log2_bytes_per_sector));
    if ((volume->bpb.ext_flags & 0x80) != 0) {
        currentFAT = volume->bpb.ext_flags & 7;
    } else {
        currentFAT = 1;
    }
    for (;;) {
        error = PFSEC_ReadFAT(volume, page->p_buf, page->sector, 0,
                              volume->bpb.bytes_per_sector);
        if (error == 0x1000 && volume->error_callback != 0) {
            callbackResult = volume->error_callback(volume->last_driver_error);
            if (callbackResult == 0) {
                goto retry;
            }
            if (callbackResult == 1 && volume->bpb.num_active_FATs >= 2 &&
                currentFAT < volume->bpb.num_active_FATs) {
                currentFAT++;
                page->sector += volume->bpb.sectors_per_FAT;
                goto retry;
            }
        }
        if (error != 0) {
            return error;
        }
    retry:
        if (error != 0) {
            continue;
        }
        return error;
    }
}

s32 PFFAT_SearchForNumFreeClusters(PF_VOLUME* volume, u32 startCluster,
                                   u32 endCluster, u32 requestedClusters,
                                   u32* firstFreeCluster, u32* lastFreeCluster)
{
    u32 upperBoundCluster;
    u32 fatEntry;
    u32 successCount;
    u32 savedStartCluster;
    u32 savedSuccessCount;
    s32 error;
    u32 searchWrapped = 0;
    u32 originalStartCluster = 0;
    s32 alreadyAllocated;
    PF_CACHE_PAGE* page;
    s32 fatType;
    PF_CACHE_PAGE* entryPage;

    *firstFreeCluster = -1;
    *lastFreeCluster = -1;

    successCount = 0;
    savedStartCluster = -1;
    savedSuccessCount = 0;
    upperBoundCluster = volume->bpb.num_clusters + 2;

    if (startCluster < 2 || startCluster >= upperBoundCluster) {
        startCluster = 2;
    }
    if (endCluster < 2 || endCluster >= upperBoundCluster) {
        endCluster = upperBoundCluster - 1;
    }
    originalStartCluster = startCluster;
    error = PFCACHE_AllocateDataPage(volume, -1, &page, &alreadyAllocated);
    if (error != 0) {
        return error;
    }
    error = PFFAT_ReadFATSector(volume, page, startCluster);
    if (error != 0) {
        PFCACHE_FreeDataPage(volume, page);
        return error;
    }
    page->option = 0;

    while (startCluster <= endCluster) {
        if (upperBoundCluster <= startCluster) {
            startCluster = 2;
        }
        fatType = volume->bpb.fat_type;
        entryPage = page;
        switch (fatType) {
        case FAT_12:
            error = PFFAT12_ReadFATEntryWithBuf(volume, (u16)startCluster,
                                                &fatEntry, entryPage);
            break;
        case FAT_16:
            error = PFFAT16_ReadFATEntryWithBuf(volume, startCluster, &fatEntry,
                                                entryPage);
            break;
        case FAT_32:
            error = PFFAT32_ReadFATEntryWithBuf(volume, startCluster, &fatEntry,
                                                entryPage);
            break;
        default:
            error = 15;
            break;
        }
        if (error != 0) {
            return error;
        }

        if (fatEntry == 0) {
            if (*firstFreeCluster == -1) {
                *firstFreeCluster = startCluster;
            }
            successCount++;
            if (successCount >= requestedClusters) {
                *lastFreeCluster = startCluster;
                PFCACHE_FreeDataPage(volume, page);
                return 0;
            }
        } else {
            if (savedSuccessCount < successCount) {
                savedStartCluster = *firstFreeCluster;
                savedSuccessCount = successCount;
            }
            *firstFreeCluster = -1;
            successCount = 0;
        }

        startCluster++;
        if (searchWrapped == 0 && successCount == 0 && startCluster > 2 &&
            startCluster == endCluster) {
            endCluster = originalStartCluster;
            startCluster = 2;
            searchWrapped = 1;
        }
    }

    if (savedSuccessCount < successCount) {
        savedStartCluster = *firstFreeCluster;
        savedSuccessCount = successCount;
    }
    if (savedSuccessCount != 0) {
        *firstFreeCluster = savedStartCluster;
        *lastFreeCluster = (*firstFreeCluster + savedSuccessCount) - 1;
    }
    PFCACHE_FreeDataPage(volume, page);
    return 0;
}

s32 PFFAT_ResetCluster(PF_VOLUME* volume, u32 cluster)
{
    PF_CACHE_PAGE* page;
    s32 alreadyAllocated;
    u32 completedBytes;
    u32 currentSector;
    u32 firstSector;
    s32 error;

    error = PFCACHE_AllocateDataPage(volume, -1, &page, &alreadyAllocated);
    if (error != 0) {
        return error;
    }
    firstSector = volume->bpb.first_data_sector +
                  ((cluster - 2) << volume->bpb.log2_sectors_per_cluster);
    cluster = 0;
    while (cluster < volume->bpb.sectors_per_cluster) {
        currentSector = firstSector + cluster;
        error = PFSEC_ReadData(volume, page->p_buf, currentSector, 0,
                               volume->bpb.bytes_per_sector, &completedBytes, 1);
        if (error != 0 || completedBytes != volume->bpb.bytes_per_sector) {
            break;
        }
        pf_memset(page->p_buf, 0, volume->bpb.bytes_per_sector);
        error = PFSEC_WriteData(volume, page->p_buf, currentSector, 0,
                                volume->bpb.bytes_per_sector, &completedBytes, 1);
        if (error != 0 || completedBytes != volume->bpb.bytes_per_sector) {
            break;
        }
        cluster++;
    }
    PFCACHE_FreeDataPage(volume, page);
    return 0;
}

s32 PFFAT_FindClusterLink(PFFAT_FFD* file, u32 chainIndex, u32* cluster,
                          u32* found)
{
    u32 position;
    u32 offset;
    u32 currentCluster;
    u32 nextCluster;
    s32 error;

    nextCluster = -1;
    *found = 0;
    if (file->cluster_link.position == 0) {
        return 0;
    }
    if (file->cluster_link.save_index >= chainIndex) {
        position = chainIndex / (file->cluster_link.interval + 1);
        offset = chainIndex -
                 position * (file->cluster_link.interval + 1);
        if (offset == 0) {
            *cluster = file->cluster_link.buffer[position];
            *found = 1;
        } else {
            currentCluster = file->cluster_link.buffer[position];
            for (; offset > 0; offset--) {
                switch (file->p_vol->bpb.fat_type) {
                case FAT_12:
                    error = PFFAT12_ReadFATEntry(file->p_vol,
                                                  (u16)currentCluster,
                                                  &nextCluster);
                    break;
                case FAT_16:
                    error = PFFAT16_ReadFATEntry(file->p_vol, currentCluster,
                                                  &nextCluster);
                    break;
                case FAT_32:
                    error = PFFAT32_ReadFATEntry(file->p_vol, currentCluster,
                                                  &nextCluster);
                    break;
                default:
                    nextCluster = -1;
                    error = 15;
                    break;
                }
                if (error != 0) {
                    return error;
                }
                if (nextCluster == 0) {
                    return 13;
                }
                currentCluster = nextCluster;
            }

            if (nextCluster == 0) {
                return 13;
            }
            if (nextCluster == fat_special_values[file->p_vol->bpb.fat_type*5+2]) {
                return 0;
            }
            *cluster = nextCluster;
            *found = 1;
        }
    } else {
        return 0;
    }
    return 0;
}

s32 PFFAT_FindClusterLinkWithBuf(PFFAT_FFD* file, u32 chainIndex,
                                 u32* cluster, u32* found,
                                 PF_CACHE_PAGE* page)
{
    u32 currentCluster;
    u32 nextCluster = -1;
    u32 position;
    u32 offset;
    s32 error;

    *found = 0;
    if (file->cluster_link.position == 0) {
        return 0;
    }
    if (file->cluster_link.save_index >= chainIndex) {
        position = chainIndex / (file->cluster_link.interval + 1);
        offset = chainIndex % (file->cluster_link.interval + 1);
        if (offset == 0) {
            *cluster = file->cluster_link.buffer[position];
            *found = 1;
        } else {
            currentCluster = file->cluster_link.buffer[position];
            for (; offset > 0; offset--) {
                switch (file->p_vol->bpb.fat_type) {
                case FAT_12:
                    error = PFFAT12_ReadFATEntryWithBuf(file->p_vol,
                                                        (u16)currentCluster,
                                                        &nextCluster, page);
                    break;
                case FAT_16:
                    error = PFFAT16_ReadFATEntryWithBuf(file->p_vol,
                                                        currentCluster,
                                                        &nextCluster, page);
                    break;
                case FAT_32:
                    error = PFFAT32_ReadFATEntryWithBuf(file->p_vol,
                                                        currentCluster,
                                                        &nextCluster, page);
                    break;
                default:
                    error = 15;
                    break;
                }
                if (error != 0) {
                    return error;
                }
                if (nextCluster == 0) {
                    return 13;
                }
                currentCluster = nextCluster;
            }

            if (nextCluster == 0) {
                return 13;
            }
            if (nextCluster == fat_special_values[file->p_vol->bpb.fat_type*5+2]) {
                return 0;
            }
            *cluster = nextCluster;
            *found = 1;
        }
    } else {
        return 0;
    }
    return 0;
}

s32 PFFAT_ReadCluster(PFFAT_FFD* file, u32 cluster, u32 chainIndex,
                      u32* nextCluster, u32* checkClusterLink)
{
    s32 error;
    u32 value;

    *nextCluster = -1;
    if (file->cluster_link.buffer != 0 && *checkClusterLink == 1) {
        error = PFFAT_FindClusterLink(file, chainIndex, nextCluster,
                                      checkClusterLink);
        if (error != 0) {
            return error;
        }
    }
    if (file->cluster_link.buffer == 0 || *checkClusterLink == 0) {
        switch (file->p_vol->bpb.fat_type) {
        case FAT_12:
            error = PFFAT12_ReadFATEntry(file->p_vol, (u16)cluster,
                                         nextCluster);
            break;
        case FAT_16:
            error = PFFAT16_ReadFATEntry(file->p_vol, cluster, nextCluster);
            break;
        case FAT_32:
            error = PFFAT32_ReadFATEntry(file->p_vol, cluster, nextCluster);
            break;
        default:
            *nextCluster = -1;
            error = 15;
            break;
        }
        if (error != 0) {
            return error;
        }
        value = *nextCluster;
        if (value == 0) {
            return 13;
        }
        if (value == -1) {
            return 6;
        }
        if (file->cluster_link.buffer != 0 &&
        value != fat_special_values[file->p_vol->bpb.fat_type*5+2]) {
        if (file->cluster_link.max_count > file->cluster_link.position &&
            file->cluster_link.max_count != 0) {
            if (chainIndex == file->cluster_link.position *
                                  (file->cluster_link.interval + 1)) {
                file->cluster_link.interval_offset = 0;
                file->cluster_link.buffer[file->cluster_link.position] =
                    value;
                file->cluster_link.position++;
            } else {
                file->cluster_link.interval_offset++;
            }
            file->cluster_link.save_index = chainIndex;
        }
    }
    }
    return 0;
}

s32 PFFAT_ReadClusterWithBuf(PFFAT_FFD* file, u32 cluster, u32 chainIndex,
                             u32* nextCluster, u32* checkClusterLink,
                             PF_CACHE_PAGE* page)
{
    s32 error;
    u32 value;

    *nextCluster = -1;
    if (file->cluster_link.buffer != 0 && *checkClusterLink == 1) {
        error = PFFAT_FindClusterLinkWithBuf(file, chainIndex, nextCluster,
                                             checkClusterLink, page);
        if (error != 0) {
            return error;
        }
    }
    if (file->cluster_link.buffer == 0 || *checkClusterLink == 0) {
        switch (file->p_vol->bpb.fat_type) {
        case FAT_12:
            error = PFFAT12_ReadFATEntryWithBuf(file->p_vol, (u16)cluster,
                                                nextCluster, page);
            break;
        case FAT_16:
            error = PFFAT16_ReadFATEntryWithBuf(file->p_vol, cluster,
                                                nextCluster, page);
            break;
        case FAT_32:
            error = PFFAT32_ReadFATEntryWithBuf(file->p_vol, cluster,
                                                nextCluster, page);
            break;
        default:
            error = 15;
            break;
        }
        if (error != 0) {
            return error;
        }
        value = *nextCluster;
        if (value == 0) {
            return 13;
        }
        if (value == -1) {
            return 6;
        }
        if (file->cluster_link.buffer != 0 &&
        value != fat_special_values[file->p_vol->bpb.fat_type*5+2]) {
        if (file->cluster_link.max_count > file->cluster_link.position &&
            file->cluster_link.max_count != 0) {
            if (chainIndex == file->cluster_link.position *
                                  (file->cluster_link.interval + 1)) {
                file->cluster_link.interval_offset = 0;
                file->cluster_link.buffer[file->cluster_link.position] =
                    value;
                file->cluster_link.position++;
            } else {
                file->cluster_link.interval_offset++;
            }
            file->cluster_link.save_index = chainIndex;
        }
    }
    }
    return 0;
}

s32 PFFAT_WriteCluster(PFFAT_FFD* file, u32 cluster, u32 chainIndex,
                       u32 nextCluster, u32 useClusterLink)
{
    u32 accessCluster;
    u32 position;
    u32 divisor;
    u32* linkBuffer;
    u32 precedingIndex;
    s32 error;

    switch (file->p_vol->bpb.fat_type) {
    case FAT_12:
        if (nextCluster > 0xFFF) {
            error = 16;
            break;
        }
        error = PFFAT12_WriteFATEntry(file->p_vol, (u16)cluster,
                                      (u16)nextCluster);
        break;
    case FAT_16:
        if (nextCluster > 0xFFFF) {
            error = 16;
            break;
        }
        error = PFFAT16_WriteFATEntry(file->p_vol, cluster, nextCluster);
        break;
    case FAT_32:
        if (nextCluster > 0x0FFFFFFF) {
            error = 16;
            break;
        }
        error = PFFAT32_WriteFATEntry(file->p_vol, cluster, nextCluster);
        break;
    default:
        error = 15;
        break;
    }
    if (error != 0) {
        return error;
    }
    linkBuffer = file->cluster_link.buffer;
    if (linkBuffer != 0 && useClusterLink == 1) {
        if (nextCluster == 0) {
            divisor = file->cluster_link.interval + 1;
            position = chainIndex / divisor;

            if (file->cluster_link.max_count >= position) {
                if (chainIndex % divisor == 0) {
                    linkBuffer[position] = 0;
                }
                if (file->cluster_link.save_index >= chainIndex) {
                    precedingIndex = chainIndex - 1;
                    file->cluster_link.position =
                        precedingIndex / (file->cluster_link.interval + 1);
                    file->cluster_link.interval_offset =
                        precedingIndex % (file->cluster_link.interval + 1);
                    file->cluster_link.save_index = precedingIndex;
                }
            }
        } else if (cluster !=
                   fat_special_values[file->p_vol->bpb.fat_type*5+2]) {
            error = PFFAT_FindClusterLink(file, chainIndex, &accessCluster,
                                          &useClusterLink);
            if (error != 0) {
                return error;
            }
            if (useClusterLink == 0) {
                if (file->cluster_link.max_count >
                        file->cluster_link.position &&
                    file->cluster_link.max_count != 0) {
                    if (chainIndex == file->cluster_link.position *
                                          (file->cluster_link.interval + 1)) {
                        file->cluster_link.interval_offset = 0;
                        file->cluster_link.buffer[file->cluster_link.position] =
                            cluster;
                        file->cluster_link.position++;
                    } else {
                        file->cluster_link.interval_offset++;
                    }
                    file->cluster_link.save_index = chainIndex;
                }
            }
        }
    }
    return 0;
}

s32 PFFAT_WriteClusterWithBuf(PFFAT_FFD* file, u32 cluster, u32 chainIndex,
                              u32 nextCluster, u32 useClusterLink,
                              PF_CACHE_PAGE* page)
{
    u32 accessCluster;
    u32 position;
    u32 divisor;
    u32* linkBuffer;
    u32 precedingIndex;
    s32 error;

    switch (file->p_vol->bpb.fat_type) {
    case FAT_12:
        if (nextCluster > 0xFFF) {
            error = 16;
            break;
        }
        error = PFFAT12_WriteFATEntryWithBuf(file->p_vol, (u16)cluster,
                                             (u16)nextCluster, page);
        break;
    case FAT_16:
        if (nextCluster > 0xFFFF) {
            error = 16;
            break;
        }
        error = PFFAT16_WriteFATEntryWithBuf(file->p_vol, cluster, nextCluster,
                                             page);
        break;
    case FAT_32:
        if (nextCluster > 0x0FFFFFFF) {
            error = 16;
            break;
        }
        error = PFFAT32_WriteFATEntryWithBuf(file->p_vol, cluster, nextCluster,
                                             page);
        break;
    default:
        error = 15;
        break;
    }
    if (error != 0) {
        return error;
    }
    linkBuffer = file->cluster_link.buffer;
    if (linkBuffer != 0 && useClusterLink == 1) {
        if (nextCluster == 0) {
            divisor = file->cluster_link.interval + 1;
            position = chainIndex / divisor;

            if (file->cluster_link.max_count >= position) {
                if (chainIndex % divisor == 0) {
                    linkBuffer[position] = 0;
                }
                if (file->cluster_link.save_index >= chainIndex) {
                    precedingIndex = chainIndex - 1;
                    file->cluster_link.position =
                        precedingIndex / (file->cluster_link.interval + 1);
                    file->cluster_link.interval_offset =
                        precedingIndex % (file->cluster_link.interval + 1);
                    file->cluster_link.save_index = precedingIndex;
                }
            }
        } else if (cluster !=
                   fat_special_values[file->p_vol->bpb.fat_type*5+2]) {
            error = PFFAT_FindClusterLinkWithBuf(
                file, chainIndex, &accessCluster, &useClusterLink, page);
            if (error != 0) {
                return error;
            }
            if (useClusterLink == 0) {
                if (file->cluster_link.max_count >
                        file->cluster_link.position &&
                    file->cluster_link.max_count != 0) {
                    if (chainIndex == file->cluster_link.position *
                                          (file->cluster_link.interval + 1)) {
                        file->cluster_link.interval_offset = 0;
                        file->cluster_link.buffer[file->cluster_link.position] =
                            cluster;
                        file->cluster_link.position++;
                    } else {
                        file->cluster_link.interval_offset++;
                    }
                    file->cluster_link.save_index = chainIndex;
                }
            }
        }
    }
    return 0;
}

static s32 PFFAT_WriteFATCopies(PF_VOLUME* volume, PF_CACHE_PAGE* page) {
    u16 fatIndex;
    u32 sector;
    s32 firstError;

    sector = page->sector;
    firstError = 0;
    for (fatIndex = 0; fatIndex < volume->bpb.num_active_FATs; fatIndex++) {
        s32 error = PFSEC_WriteFAT(volume, page->p_buf, sector, 0, volume->bpb.bytes_per_sector);
        if (error != 0 && firstError == 0) firstError = error;
        sector += volume->bpb.sectors_per_FAT;
    }
    return firstError;
}

s32 PFFAT_DoAllocateChain(PFFAT_FFD* file, u32 chainLength, u32 chainIndex,
                          u32* firstAllocatedCluster,
                          u32* lastAllocatedCluster, s32 resetClusters)
{
    PF_VOLUME* volume;
    u32 eoc2;
    u32 firstFreeCluster;
    u32 lastFreeCluster;
    u32 cluster;
    u32 firstFlushError;
    s32 alreadyAllocated;
    s32 error;
    PF_CACHE_PAGE* page;

    volume = file->p_vol;
    eoc2 = fat_special_values[volume->bpb.fat_type*5+2];
    *firstAllocatedCluster = -1;
    *lastAllocatedCluster = -1;
    lastFreeCluster = -1;
    error = PFFAT_SearchForNumFreeClusters(
        volume, volume->last_free_cluster, -1, chainLength, &firstFreeCluster,
        &lastFreeCluster);
    if (error != 0) {
        return error;
    }
    if (firstFreeCluster == -1) {
        return 0;
    }
    if (resetClusters != 0) {
        error = PFFAT_ResetCluster(volume, firstFreeCluster);
        if (error != 0) {
            return error;
        }
    }
    error = PFCACHE_AllocateDataPage(volume, -1, &page, &alreadyAllocated);
    if (error != 0) {
        return error;
    }
    error = PFFAT_ReadFATSector(volume, page, firstFreeCluster);
    if (error != 0) {
        PFCACHE_FreeDataPage(volume, page);
        return error;
    }
    page->option = 0;
    cluster = firstFreeCluster;
    for (; cluster < lastFreeCluster; cluster++) {
        error = PFFAT_WriteClusterWithBuf(file, cluster, chainIndex,
                                          cluster + 1, 1, page);
        if (error != 0) {
            PFCACHE_FreeDataPage(volume, page);
            return error;
        }
        if ((volume->fsi_flag & 4) != 0 && volume->num_free_clusters != -1 &&
            volume->num_free_clusters != 0 &&
            (volume->bpb.fat_type != FAT_32 ||
             lastFreeCluster != volume->bpb.root_dir_cluster)) {
            volume->num_free_clusters--;
        }
        if (*firstAllocatedCluster == -1) {
            *firstAllocatedCluster = cluster;
        }
        *lastAllocatedCluster = cluster;
        chainIndex++;
    }
    if (lastFreeCluster != -1) {
        error = PFFAT_WriteClusterWithBuf(file, lastFreeCluster, chainIndex,
                                          eoc2, 1, page);
        if (error != 0) {
            PFCACHE_FreeDataPage(volume, page);
            return error;
        }
        if (*firstAllocatedCluster == -1) {
            *firstAllocatedCluster = cluster;
        }
        *lastAllocatedCluster = cluster;
        if (volume->num_free_clusters != -1 && volume->num_free_clusters != 0 &&
            (volume->bpb.fat_type != FAT_32 ||
             lastFreeCluster != volume->bpb.root_dir_cluster)) {
            volume->num_free_clusters--;
        }
    }
    volume->last_free_cluster = lastFreeCluster + 1;
    file->last_cluster.num_last_cluster = lastFreeCluster;
    file->last_cluster.max_chain_index = chainIndex;
    *lastAllocatedCluster = lastFreeCluster;

    firstFlushError = PFFAT_WriteFATCopies(volume, page);
    if (firstFlushError != 0) {
        PFCACHE_FreeDataPage(volume, page);
        return firstFlushError;
    }
    PFCACHE_FreeDataPage(volume, page);
    if (volume->bpb.fat_type == FAT_32 && (volume->fsi_flag & 2) != 0) {
        error = PFFAT_RefreshFSINFO(volume);
        if (error != 0) {
            volume->num_free_clusters = -1;
            volume->fsi_flag &= ~4;
        }
    }
    return 0;
}

s32 PFFAT_GetClusterInChain(PFFAT_FFD* file, u32 chainIndex, u32 mode,
                            u32 numClusters, u32* locateStart,
                            u32* locateEnd)
{
    u32 badCluster;
    u32 eoc1;
    u32 currentCluster;
    u32 nextCluster;
    u32 traceCount;
    u32 appendCount;
    u32 searchIndex;
    u32* chainStartPointer;
    u32 chainStart;
    s32 alreadyAllocated;
    u32 checkClusterLink;
    PF_CACHE_PAGE* page;
    s32 error;

    badCluster = fat_special_values[file->p_vol->bpb.fat_type*5+0];
    eoc1 = fat_special_values[file->p_vol->bpb.fat_type*5+1];
    *locateEnd = -1;
    *locateStart = -1;

    if (file->last_access_cluster.chain_index != 0 &&
        file->last_access_cluster.chain_index <= chainIndex) {
        chainStart = file->last_access_cluster.cluster;
        chainStartPointer = &chainStart;
        traceCount = chainIndex - file->last_access_cluster.chain_index;
        searchIndex = file->last_access_cluster.chain_index + 1;
    } else {
        chainStartPointer = file->p_start_cluster;
        traceCount = chainIndex;
        searchIndex = 1;
    }
    currentCluster = *chainStartPointer;
    nextCluster = *chainStartPointer;

    if (mode == 2) {
        if (traceCount != 0 && numClusters != 0) {
            traceCount += numClusters - 1;
        } else {
            traceCount = numClusters;
        }
        appendCount = traceCount;
        if (file->last_cluster.num_last_cluster != 0) {
            traceCount = 0;
            appendCount = file->last_cluster.max_chain_index + numClusters -
                          chainIndex;
            currentCluster = file->last_cluster.num_last_cluster;
            nextCluster = fat_special_values[file->p_vol->bpb.fat_type*5+2];
            searchIndex = file->last_cluster.max_chain_index + 1;
        }
    } else {
        if (mode == 1 && currentCluster == 0) {
            traceCount++;
        }
        appendCount = traceCount;
    }

    if (traceCount != 0) {
        error = PFCACHE_AllocateDataPage(file->p_vol, -1, &page,
                                         &alreadyAllocated);
        if (error != 0) {
            return error;
        }
        error = PFFAT_ReadFATSector(file->p_vol, page, currentCluster);
        if (error != 0) {
            PFCACHE_FreeDataPage(file->p_vol, page);
            return error;
        }
        page->option = 0;
        checkClusterLink = 1;
        while (traceCount-- != 0 && currentCluster < badCluster) {
            if (currentCluster != 0) {
                error = PFFAT_ReadClusterWithBuf(
                    file, currentCluster, searchIndex, &nextCluster,
                    &checkClusterLink, page);
                if (error != 0 && nextCluster != -1) {
                    PFCACHE_FreeDataPage(file->p_vol, page);
                    return error;
                }
            } else {
                nextCluster =
                    fat_special_values[file->p_vol->bpb.fat_type*5+2];
                searchIndex--;
            }
            if ((nextCluster < 2 ||
                 nextCluster >= file->p_vol->bpb.num_clusters + 2) &&
                nextCluster < eoc1) {
                PFCACHE_FreeDataPage(file->p_vol, page);
                return 14;
            }
            if (mode != 0 && nextCluster >= eoc1) {
                break;
            }
            currentCluster = nextCluster;
            searchIndex++;
        }
        appendCount = traceCount;
        PFCACHE_FreeDataPage(file->p_vol, page);
    }

    if (mode != 0 && nextCluster >= eoc1) {
        *locateStart = 0;
        error = PFFAT_DoAllocateChain(file, ++appendCount, searchIndex,
                                      locateStart, &nextCluster, 0);
        if (error != 0) {
            if (*locateStart != -1) {
                PFFAT_FreeChain(file, *locateStart, searchIndex, -1);
            }
            *locateStart = -1;
            nextCluster = -1;
        } else {
            error = 0;
        }
        if (error != 0) {
            return error;
        }
        if (nextCluster == -1) {
            return 6;
        }
        if (*chainStartPointer == 0) {
            *chainStartPointer = *locateStart;
        } else {
            error = PFFAT_WriteCluster(file, currentCluster, searchIndex - 1,
                                       *locateStart, 1);
            if (error != 0) {
                return error;
            }
        }
        currentCluster = nextCluster;
    }
    *locateEnd = currentCluster;
    return 0;
}

s32 PFFAT_GetClusterContinuousSectorInChain(PFFAT_FFD* file,
                                            u32 initialCluster,
                                            u32 chainIndex, u32 size,
                                            u32* numSectors)
{
    PF_VOLUME* volume;
    u32 cluster;
    u32 nextCluster;
    u32 checkClusterLink;
    s32 error;

    volume = file->p_vol;
    cluster = initialCluster;
    nextCluster = -1;
    checkClusterLink = 1;
    while (nextCluster != 0) {
        error = PFFAT_ReadCluster(file, cluster, chainIndex, &nextCluster,
                                  &checkClusterLink);
        if (error != 0) {
            return error;
        }
        if (cluster + 1 != nextCluster) {
            if (nextCluster ==
                fat_special_values[volume->bpb.fat_type*5+2]) {
                file->last_cluster.num_last_cluster = cluster;
                file->last_cluster.max_chain_index = chainIndex - 1;
            }
            break;
        }
        file->p_hint->chain_index = file->p_hint->chain_index + 1;
        file->p_hint->cluster = nextCluster;
        *numSectors += volume->bpb.sectors_per_cluster;
        if ((*numSectors << volume->bpb.log2_bytes_per_sector) >= size) {
            break;
        }
        cluster = nextCluster;
        chainIndex++;
    }
    return 0;
}

s32 PFFAT_GetClusterAllocatedInChain(PFFAT_FFD* file, u32 initialCluster,
                                     u32 chainIndex, u32 size,
                                     u32* numClusters)
{
    PF_VOLUME* volume;
    u32 cluster;
    u32 nextCluster;
    u32 totalSize;
    u32 checkClusterLink;
    s32 error;

    volume = file->p_vol;
    nextCluster = -1;
    cluster = initialCluster;
    checkClusterLink = 1;
    totalSize = 0;
    while (nextCluster != 0) {
        totalSize += volume->bpb.bytes_per_sector *
                     volume->bpb.sectors_per_cluster;
        (*numClusters)++;
        if (totalSize >= size) {
            break;
        }
        error = PFFAT_ReadCluster(file, cluster, chainIndex, &nextCluster,
                                  &checkClusterLink);
        if (error != 0) {
            return error;
        }
        if (nextCluster ==
            fat_special_values[volume->bpb.fat_type*5+2]) {
            file->last_cluster.num_last_cluster = cluster;
            file->last_cluster.max_chain_index = chainIndex - 1;
            break;
        }
        cluster = nextCluster;
        chainIndex++;
    }
    return 0;
}

static inline s32 find_cluster_in_chain(PFFAT_FFD* file, u32 index, u32 mode, u32 count, u32 useFirst, u32* cluster) {
    u32 firstCluster;
    u32 lastCluster;
    u32 candidate;
    s32 error = PFFAT_GetClusterInChain(file, index, mode, count, &firstCluster, &lastCluster);
    if (error != 0) { return error; }
    candidate = useFirst ? firstCluster : lastCluster;
    if (candidate >= 2 && candidate < file->p_vol->bpb.num_clusters + 2) { *cluster = candidate; }
    return 0;
}

s32 PFFAT_GetClusterSpecified(PFFAT_FFD* file, u32 chainIndex,
                              u32 mayAllocate, u32* cluster)
{
    PFFAT_HINT* hint;
    u32 fatType;
    u32 found;
    u32 locateStart;
    u32 locateEnd;
    s32 error;

    fatType = file->p_vol->bpb.fat_type;
    hint = file->p_hint;
    if (*file->p_start_cluster == 0 && mayAllocate == 0) {
        *cluster = -1;
        return 0;
    }
    if (*file->p_start_cluster == 1) {
        if (fatType <= FAT_16) {
            *cluster = -1;
            return 0;
        }
        *file->p_start_cluster = file->p_vol->bpb.root_dir_cluster;
    }
    if (file->cluster_link.buffer != 0 && mayAllocate == 0) {
        error = PFFAT_FindClusterLink(file, chainIndex, cluster, &found);
        if (error != 0) {
            return error;
        }
        if (found == 1) {
            hint->previous_cluster = file->start_cluster;
            hint->chain_index = chainIndex;
            hint->cluster = *cluster;
            return 0;
        }
    }
    *cluster = -1;
    error = find_cluster_in_chain(file, chainIndex, mayAllocate != 0, 0, 0, cluster);
    if (error != 0) {
        return error;
    }
    if (*cluster == -1) {
        return 0;
    }
    hint->previous_cluster = file->start_cluster;
    hint->chain_index = chainIndex;
    hint->cluster = *cluster;
    return 0;
}

s32 PFFAT_GetClusterAllocated(PFFAT_FFD* file, u32 chainIndex,
                              u32 numClusters, u32* cluster)
{
    u32* start;
    PF_VOLUME* vol;
    PFFAT_HINT* hint;
    u32 fatType;
    u32 locateStart;
    u32 locateEnd;
    s32 error;

    start = file->p_start_cluster;
    vol = file->p_vol;
    fatType = vol->bpb.fat_type;
    hint = file->p_hint;
    if (*start == 1) {
        if (fatType <= FAT_16) {
            *cluster = -1;
            return 0;
        }
        *start = vol->bpb.root_dir_cluster;
    }
    *cluster = -1;
    error = find_cluster_in_chain(file, chainIndex, 2, numClusters, 1, cluster);
    if (error != 0) {
        return error;
    }
    if (*cluster == -1) {
        return 0;
    }
    hint->previous_cluster = file->start_cluster;
    hint->chain_index = chainIndex;
    hint->cluster = *cluster;
    return 0;
}

static s32 PFFAT_GetSectorInRootDirRegion(PF_VOLUME* volume,
                                          u32 sectorOffset, u32* sector)
{
    if (sectorOffset >= volume->bpb.num_root_dir_sectors) {
        *sector = -1;
        return 0;
    }
    *sector = volume->bpb.first_root_dir_sector + sectorOffset;
    return 0;
}

s32 PFFAT_GetSector(PFFAT_FFD* file, u32 fileSectorIndex, u32 mode,
                    u32 size, u32* sector)
{
    PF_VOLUME* volume;
    u32 fatType;
    u32 chainIndex;
    u32 cluster;
    u32 numClusters;
    u32 numSectors;
    s32 error;

    volume = file->p_vol;
    fatType = volume->bpb.fat_type;
    if (*file->p_start_cluster == 1 && fatType <= FAT_16) {
        error = PFFAT_GetSectorInRootDirRegion(volume, fileSectorIndex, sector);
        if (error != 0) {
            return error;
        }
        return 0;
    }
    chainIndex = fileSectorIndex >> volume->bpb.log2_sectors_per_cluster;
    if (mode == 2) {
        numClusters = size / volume->bpb.bytes_per_sector;
        numSectors = numClusters + (size % volume->bpb.bytes_per_sector != 0);
        numClusters = numSectors / volume->bpb.sectors_per_cluster;
        numClusters = numClusters + (numSectors % volume->bpb.sectors_per_cluster != 0);
        error = PFFAT_GetClusterAllocated(file, chainIndex, numClusters,
                                          &cluster);
        if (error != 0) {
            return error;
        }
    } else {
        error = PFFAT_GetClusterSpecified(file, chainIndex, mode, &cluster);
        if (error != 0) {
            return error;
        }
    }
    if (cluster == -1) {
        *sector = -1;
        return 0;
    }
    *sector = volume->bpb.first_data_sector +
              ((cluster - 2) << volume->bpb.log2_sectors_per_cluster) +
              (fileSectorIndex & (volume->bpb.sectors_per_cluster - 1));
    return 0;
}

s32 PFFAT_GetSectorSpecified(PFFAT_FFD* file, u32 fileSectorIndex,
                             u32 clusterIndex, u32* sector)
{
    s32 error;

    error = PFFAT_GetSector(file, fileSectorIndex, clusterIndex != 0, 0,
                            sector);
    switch (error) {
    case 0:
        error = 0;
        break;
    default:
        break;
    }
    return error;
}

s32 PFFAT_GetSectorAllocated(PFFAT_FFD* file, u32 fileSectorIndex,
                             u32 size, u32* sector)
{
    s32 error;

    error = PFFAT_GetSector(file, fileSectorIndex, 2, size, sector);
    return error & (-error | error) >> 31;
}

s32 PFFAT_getContinuousSector(PFFAT_FFD* file, u32 fileSectorIndex,
                              u32 size, u32* sector, u32* numSectors)
{
    PF_VOLUME* volume;
    u32 chainIndex;
    u32 cluster;
    s32 error;

    volume = file->p_vol;
    cluster = -1;
    if (*sector != -1) {
        cluster = ((*sector - volume->bpb.first_data_sector) >>
                   volume->bpb.log2_sectors_per_cluster) + 2;
    } else {
        error = PFFAT_GetSector(file, fileSectorIndex, 0, 0, sector);
        error &= (-error | error) >> 31;
        if (error != 0) {
            return error;
        }
        if (*sector != -1) {
            cluster = ((*sector - volume->bpb.first_data_sector) >>
                       volume->bpb.log2_sectors_per_cluster) + 2;
        }
    }
    if (*sector != -1) {
        *numSectors =
            (volume->bpb.first_data_sector +
             ((cluster - 1) << volume->bpb.log2_sectors_per_cluster)) -
            *sector;
    } else {
        *numSectors = 0;
    }
    if (*sector != -1 &&
        (*numSectors << volume->bpb.log2_bytes_per_sector) < size) {
        chainIndex = fileSectorIndex >>
                     volume->bpb.log2_sectors_per_cluster;
        error = PFFAT_GetClusterContinuousSectorInChain(
            file, cluster, chainIndex + 1, size, numSectors);
        if (error != 0) {
            return error;
        }
    }
    return 0;
}

s32 PFFAT_CountAllocatedClusters(PFFAT_FFD* file, u32 size,
                                 u32* numAllocatedClusters)
{
    u32 cluster;
    u32 totalSize;
    u32 chainIndex;
    u32 bytesPerCluster;
    s32 error;

    *numAllocatedClusters = 0;
    if (*file->p_start_cluster < 2) {
        return 0;
    }
    if (file->last_cluster.num_last_cluster != 0) {
        totalSize = (file->last_cluster.max_chain_index + 1)
                    << (file->p_vol->bpb.log2_bytes_per_sector +
                        file->p_vol->bpb.log2_sectors_per_cluster);
        if (totalSize > size) {
            totalSize = size;
        }
        *numAllocatedClusters = file->last_cluster.max_chain_index + 1;
        return 0;
    }
    if (file->p_hint->cluster != 0) {
        bytesPerCluster = file->p_vol->bpb.bytes_per_sector *
                          file->p_vol->bpb.sectors_per_cluster;
        if (size <= (file->p_hint->chain_index + 1) *
                        bytesPerCluster) {
            *numAllocatedClusters = file->p_hint->chain_index + 1;
            return 0;
        }
        *numAllocatedClusters = file->p_hint->chain_index;
        cluster = file->p_hint->cluster;
        chainIndex = file->p_hint->chain_index + 1;
        size -= file->p_hint->chain_index *
                (file->p_vol->bpb.bytes_per_sector * file->p_vol->bpb.sectors_per_cluster);
    } else {
        cluster = *file->p_start_cluster;
        chainIndex = 1;
    }
    error = PFFAT_GetClusterAllocatedInChain(file, cluster, chainIndex, size,
                                             numAllocatedClusters);
    if (error != 0) {
        return error;
    }
    return 0;
}

s32 PFFAT_CountFreeClusters(PF_VOLUME* volume, u32* numFreeClusters)
{
    u32 freeCluster;
    u32 nextCluster;
    s32 alreadyAllocated;
    PF_CACHE_PAGE* page;
    s32 error;
    PF_CACHE_PAGE* currentPage;

    if ((volume->fsi_flag & 4) != 0 && volume->num_free_clusters != -1) {
        *numFreeClusters = volume->num_free_clusters;
        return 0;
    }
    *numFreeClusters = 0;
    freeCluster = 2;
    error = PFCACHE_AllocateDataPage(volume, -1, &page,
                                     &alreadyAllocated);
    if (error != 0) {
        return error;
    }
    error = PFFAT_ReadFATSector(volume, page, freeCluster);
    if (error != 0) {
        PFCACHE_FreeDataPage(volume, page);
        return error;
    }
    page->option = 0;
    for (; freeCluster >= 2 &&
           freeCluster < volume->bpb.num_clusters + 2; freeCluster++) {
        currentPage = page;
        switch (volume->bpb.fat_type) {
        case FAT_12:
            error = PFFAT12_ReadFATEntryWithBuf(volume, freeCluster,
                                                &nextCluster, currentPage);
            break;
        case FAT_16:
            error = PFFAT16_ReadFATEntryWithBuf(volume, freeCluster,
                                                &nextCluster, currentPage);
            break;
        case FAT_32:
            error = PFFAT32_ReadFATEntryWithBuf(volume, freeCluster,
                                                &nextCluster, currentPage);
            break;
        default:
            error = 15;
            break;
        }
        if (error != 0) {
            PFCACHE_FreeDataPage(volume, page);
            return error;
        }
        if (nextCluster == 0) {
            (*numFreeClusters)++;
        }
    }
    PFCACHE_FreeDataPage(volume, page);
    volume->fsi_flag |= 4;
    volume->num_free_clusters = *numFreeClusters;
    if (volume->bpb.fat_type == FAT_32 && (volume->fsi_flag & 2) != 0) {
        error = PFFAT_RefreshFSINFO(volume);
        if (error != 0) {
            volume->num_free_clusters = -1;
            volume->fsi_flag &= ~4;
        }
    }
    return 0;
}

s32 PFFAT_FreeChain(PFFAT_FFD* file, u32 startCluster, u32 chainIndex,
                    u32 size)
{
    PF_VOLUME* volume;
    u32 eoc1;
    u32 nextCluster;
    u32 fileSize;
    u32 clusterSize;
    s32 alreadyAllocated;
    PF_CACHE_PAGE* page;
    PF_CACHE_PAGE* currentPage;
    s32 error;

    volume = file->p_vol;
    if (startCluster == 0) {
        return 0;
    }
    eoc1 = fat_special_values[volume->bpb.fat_type*5+1];
    if (size != 0) {
        fileSize = size;
        clusterSize = volume->bpb.bytes_per_sector
                      << volume->bpb.log2_sectors_per_cluster;
    } else {
        return 0;
    }
    error = PFCACHE_AllocateDataPage(volume, -1, &page,
                                     &alreadyAllocated);
    if (error != 0) {
        return error;
    }
    error = PFFAT_ReadFATSector(volume, page, startCluster);
    if (error != 0) {
        PFCACHE_FreeDataPage(volume, page);
        return error;
    }
    page->option = 1;
    nextCluster = startCluster;
    while (startCluster < eoc1) {
        if (size != 0 && fileSize == 0) {
            break;
        }
        currentPage = page;
        switch (volume->bpb.fat_type) {
        case FAT_12:
            error = PFFAT12_ReadFATEntryWithBuf(volume, startCluster,
                                                &nextCluster, currentPage);
            break;
        case FAT_16:
            error = PFFAT16_ReadFATEntryWithBuf(volume, startCluster,
                                                &nextCluster, currentPage);
            break;
        case FAT_32:
            error = PFFAT32_ReadFATEntryWithBuf(volume, startCluster,
                                                &nextCluster, currentPage);
            break;
        default:
            error = 15;
            break;
        }
        if (error != 0) {
            PFCACHE_FreeDataPage(volume, page);
            return error;
        }
        if (nextCluster == 0) {
            s32 firstFlushError;
            PF_CACHE_PAGE* flushPage;
            u16 fatIndex;
            u32 fatSector;

            firstFlushError = 0;
            flushPage = page;
            fatSector = flushPage->sector;
            for (fatIndex = 0; fatIndex < volume->bpb.num_active_FATs;
                 fatIndex++) {
                error = PFSEC_WriteFAT(volume, flushPage->p_buf, fatSector, 0,
                                       volume->bpb.bytes_per_sector);
                if (error != 0 && firstFlushError == 0) {
                    firstFlushError = error;
                }
                fatSector += volume->bpb.sectors_per_FAT;
            }
            if (firstFlushError != 0) {
                PFCACHE_FreeDataPage(volume, page);
                return firstFlushError;
            }
            PFCACHE_FreeDataPage(volume, page);
            return 0;
        }
        if (chainIndex != -1) {
            error = PFFAT_WriteClusterWithBuf(file, startCluster, chainIndex,
                                              0, 1, page);
            chainIndex++;
        } else {
            s32 entryError;
            currentPage = page;
            switch (volume->bpb.fat_type) {
            case FAT_12:
                entryError = PFFAT12_WriteFATEntryWithBuf(
                    volume, (u16)startCluster, 0, currentPage);
                break;
            case FAT_16:
                entryError = PFFAT16_WriteFATEntryWithBuf(volume, startCluster, 0,
                                                     currentPage);
                break;
            case FAT_32:
                entryError = PFFAT32_WriteFATEntryWithBuf(volume, startCluster, 0,
                                                     currentPage);
                break;
            default:
                entryError = 15;
                break;
            }
            error = entryError;
        }
        if (error != 0) {
            PFCACHE_FreeDataPage(volume, page);
            return error;
        }
        if (size != 0 && fileSize != 0) {
            if (fileSize <= clusterSize) {
                fileSize = 0;
            } else {
                fileSize -= clusterSize;
            }
        }
        if (volume->num_free_clusters != -1) {
            volume->num_free_clusters++;
        }
        startCluster = nextCluster;
    }
    {
        s32 firstFlushError;
        PF_CACHE_PAGE* flushPage;
        u16 fatIndex;
        u32 fatSector;

        firstFlushError = 0;
        flushPage = page;
        fatSector = flushPage->sector;
        for (fatIndex = 0; fatIndex < volume->bpb.num_active_FATs;
             fatIndex++) {
            error = PFSEC_WriteFAT(volume, flushPage->p_buf, fatSector, 0,
                                   volume->bpb.bytes_per_sector);
            if (error != 0 && firstFlushError == 0) {
                firstFlushError = error;
            }
            fatSector += volume->bpb.sectors_per_FAT;
        }
        if (firstFlushError != 0) {
            PFCACHE_FreeDataPage(volume, page);
            return firstFlushError;
        }
    }
    PFCACHE_FreeDataPage(volume, page);
    if (volume->bpb.fat_type == FAT_32 && (volume->fsi_flag & 2) != 0) {
        error = PFFAT_RefreshFSINFO(volume);
        if (error != 0) {
            volume->num_free_clusters = -1;
            volume->fsi_flag &= ~4;
        }
    }
    return 0;
}

s32 PFFAT_getBeforeChain(PF_VOLUME* volume, u32 startCluster,
                         u32 activeCluster, u32* cluster)
{
    u32 eoc1;
    u32 nextCluster;
    PF_CACHE_PAGE* page;
    PF_CACHE_PAGE* currentPage;
    s32 alreadyAllocated;
    s32 error;

    eoc1 = fat_special_values[volume->bpb.fat_type*5+1];
    *cluster = -1;
    error = PFCACHE_AllocateDataPage(volume, -1, &page,
                                     &alreadyAllocated);
    if (error != 0) {
        return error;
    }
    page->option = 0;
    while (startCluster < eoc1) {
        currentPage = page;
        switch (volume->bpb.fat_type) {
        case FAT_12:
            error = PFFAT12_ReadFATEntryWithBuf(volume, startCluster,
                                                &nextCluster, currentPage);
            break;
        case FAT_16:
            error = PFFAT16_ReadFATEntryWithBuf(volume, startCluster,
                                                &nextCluster, currentPage);
            break;
        case FAT_32:
            error = PFFAT32_ReadFATEntryWithBuf(volume, startCluster,
                                                &nextCluster, currentPage);
            break;
        default:
            error = 15;
            break;
        }
        if (error != 0) {
            PFCACHE_FreeDataPage(volume, page);
            return error;
        }
        if (activeCluster == nextCluster) {
            *cluster = startCluster;
            return 0;
        }
        startCluster--;
        if ((startCluster < 2 ||
             startCluster >= volume->bpb.num_clusters + 2) &&
            startCluster < eoc1) {
            *cluster = activeCluster;
            return 0;
        }
    }
    PFCACHE_FreeDataPage(volume, page);
    return 13;
}

s32 PFFAT_InitFATRegion(PF_VOLUME* volume)
{
    PF_CACHE_PAGE* page;
    u32 sector;
    u32 fatValue;
    s32 alreadyAllocated;
    s32 error;

    error = PFCACHE_AllocateFATPage(volume, -1, &page, &alreadyAllocated);
    if (error != 0) {
        return error;
    }
    pf_memset(page->p_buf, 0, volume->bpb.bytes_per_sector);
    sector = volume->bpb.num_reserved_sectors;
    while (sector < volume->bpb.first_root_dir_sector) {
        error = PFCACHE_WriteFATSectorAndFreeIfNeeded(volume, page->p_buf,
                                                      sector);
        if (error != 0) {
            PFCACHE_FreeFATPage(volume, page);
            return error;
        }
        sector++;
    }
    PFCACHE_FreeFATPage(volume, page);
    fatValue = volume->bpb.media |
               fat_special_values[volume->bpb.fat_type*5+3];
    switch (volume->bpb.fat_type) {
    case FAT_12:
        if (fatValue > 0xFFF) {
            error = 16;
        } else {
            error = PFFAT12_WriteFATEntry(volume, 0, (u16)fatValue);
        }
        break;
    case FAT_16:
        if (fatValue > 0xFFFF) {
            error = 16;
        } else {
            error = PFFAT16_WriteFATEntry(volume, 0, fatValue);
        }
        break;
    case FAT_32:
        if (fatValue > 0x0FFFFFFF) {
            error = 16;
        } else {
            error = PFFAT32_WriteFATEntry(volume, 0, fatValue);
        }
        break;
    default:
        error = 15;
        break;
    }
    if (error != 0) {
        return error;
    }
    fatValue = fat_special_values[volume->bpb.fat_type*5+4];
    switch (volume->bpb.fat_type) {
    case FAT_12:
        if (fatValue > 0xFFF) {
            error = 16;
        } else {
            error = PFFAT12_WriteFATEntry(volume, 1, (u16)fatValue);
        }
        break;
    case FAT_16:
        if (fatValue > 0xFFFF) {
            error = 16;
        } else {
            error = PFFAT16_WriteFATEntry(volume, 1, fatValue);
        }
        break;
    case FAT_32:
        if (fatValue > 0x0FFFFFFF) {
            error = 16;
        } else {
            error = PFFAT32_WriteFATEntry(volume, 1, fatValue);
        }
        break;
    default:
        error = 15;
        break;
    }
    if (error != 0) {
        return error;
    }
    error = PFCACHE_FlushFATCache(volume);
    return error & (-error | error) >> 31;
}

s32 PFFAT_MakeRootDir(PF_VOLUME* volume)
{
    u32 fatValue;
    u32 sector;
    u32 sectorOffset;
    u32 completedBytes;
    s32 alreadyAllocated;
    PF_CACHE_PAGE* page;
    u32 rootCluster;
    s32 error;

    rootCluster = volume->bpb.root_dir_cluster;
    fatValue = fat_special_values[volume->bpb.fat_type*5+2];
    switch (volume->bpb.fat_type) {
    case FAT_12:
        if (fatValue > 0xFFF) {
            error = 16;
        } else {
            error = PFFAT12_WriteFATEntry(
                volume, rootCluster, (u16)fatValue);
        }
        break;
    case FAT_16:
        if (fatValue > 0xFFFF) {
            error = 16;
        } else {
            error = PFFAT16_WriteFATEntry(
                volume, rootCluster, fatValue);
        }
        break;
    case FAT_32:
        if (fatValue > 0x0FFFFFFF) {
            error = 16;
        } else {
            error = PFFAT32_WriteFATEntry(
                volume, rootCluster, fatValue);
        }
        break;
    default:
        error = 15;
        break;
    }
    if (error != 0) {
        return error;
    }
    error = PFCACHE_FlushFATCache(volume);
    if (error != 0) {
        return error;
    }
    error = PFCACHE_AllocateDataPage(volume, -1, &page, &alreadyAllocated);
    if (error != 0) {
        return error;
    }
    pf_memset(page->p_buf, 0, volume->bpb.bytes_per_sector);
    sector = volume->bpb.first_data_sector +
             ((volume->bpb.root_dir_cluster - 2)
              << volume->bpb.log2_sectors_per_cluster);
    for (sectorOffset = 0;
         sectorOffset < volume->bpb.sectors_per_cluster; sectorOffset++) {
        error = PFSEC_WriteData(volume, page->p_buf, sector + sectorOffset,
                                0, volume->bpb.bytes_per_sector,
                                &completedBytes, 0);
        if (error != 0) {
            PFCACHE_FreeDataPage(volume, page);
            return error;
        }
        if (completedBytes != volume->bpb.bytes_per_sector) {
            PFCACHE_FreeDataPage(volume, page);
            return 17;
        }
    }
    PFCACHE_FreeDataPage(volume, page);
    return 0;
}

typedef struct PFFAT_FSINFO {
    u8 reserved[0x1E8];
    union {
        u32 word;
        u8 bytes[4];
    } num_free_clusters;
} PFFAT_FSINFO;

s32 PFFAT_RefreshFSINFO(PF_VOLUME* volume)
{
    PF_CACHE_PAGE* page;
    s32 alreadyAllocated;
    u32 completedBytes;
    s32 error;
    s32 error2;

    error = 0;
    if ((volume->fsi_flag & 4) != 0) {
        error2 = PFCACHE_AllocateDataPage(volume, -1, &page,
                                          &alreadyAllocated);
        if (error2 != 0) {
            return error2;
        } else {
            error = PFSEC_ReadData(
                volume, page->p_buf, volume->bpb.fs_info_sector, 0,
                volume->bpb.bytes_per_sector, &completedBytes, 0);
            if (error == 0 &&
                completedBytes != volume->bpb.bytes_per_sector) {
                error = 17;
            }
            if (error == 0) {
                PFFAT_FSINFO* info;
                u8* freeClusterBytes;
                info = (PFFAT_FSINFO*)page->p_buf;
                freeClusterBytes = info->num_free_clusters.bytes;
                if (((u32)freeClusterBytes & 3) != 0) {
                    freeClusterBytes[0] = (u8)volume->num_free_clusters;
                    ((PFFAT_FSINFO*)page->p_buf)->num_free_clusters.bytes[1] =
                        (u8)(volume->num_free_clusters >> 8);
                    ((PFFAT_FSINFO*)page->p_buf)->num_free_clusters.bytes[2] =
                        (u8)(volume->num_free_clusters >> 16);
                    ((PFFAT_FSINFO*)page->p_buf)->num_free_clusters.bytes[3] =
                        (u8)(volume->num_free_clusters >> 24);
                } else {
                    u32 freeClusters = volume->num_free_clusters;
                    u32 upperBytes = (freeClusters << 24) | ((freeClusters << 8) & 0x00FF0000);
                    u32 lowerBytes = (freeClusters >> 24) | ((freeClusters >> 8) & 0xFF00);
                    info->num_free_clusters.word = upperBytes | lowerBytes;
                }
                error = PFSEC_WriteData(
                    volume, page->p_buf, volume->bpb.fs_info_sector, 0,
                    volume->bpb.bytes_per_sector, &completedBytes, 0);
                if (error == 0 &&
                    completedBytes != volume->bpb.bytes_per_sector) {
                    error = 17;
                }
            }
            PFCACHE_FreeDataPage(volume, page);
        }
    }
finished:
    return error;
}

void PFFAT_InitHint(PFFAT_HINT* hint)
{
    hint->chain_index = 0;
    hint->cluster = 0;
    hint->previous_cluster = 0;
}

s32 PFFAT_TraceClustersChain(PFFAT_FFD* file, u32 startCluster, u32 size,
                             u32* targetCluster, u32* nextClusterOutput)
{
    u32 count;
    u32 nextCluster;
    u32 checkClusterLink;
    u32 clusterSize;
    u32 chainIndex;
    u32 clusterCount;
    u32 savedCluster;
    PF_VOLUME* volume;
    s32 error;

    savedCluster = startCluster;
    *targetCluster = 0;
    *nextClusterOutput = 0;
    if (*file->p_start_cluster < 2) {
        return 0;
    }
    if (startCluster < 2) {
        return 0;
    }
    if (size == 0) {
        return 0;
    }
    volume = file->p_vol;
    if (size == -1 && file->last_cluster.num_last_cluster != 0) {
        *targetCluster = file->last_cluster.num_last_cluster;
        *nextClusterOutput = fat_special_values[volume->bpb.fat_type*5+2];
        return 0;
    }
    clusterSize = volume->bpb.bytes_per_sector *
                  volume->bpb.sectors_per_cluster;
    clusterCount = size / clusterSize;
    if (size % clusterSize != 0) {
        clusterCount++;
    }
    if (*file->p_start_cluster == startCluster) {
        chainIndex = 1;
    } else {
        chainIndex = file->p_hint->chain_index + 1;
    }
    nextCluster = -1;
    checkClusterLink = 1;
    for (count = 0; count < clusterCount; count++) {
        error = PFFAT_ReadCluster(file, startCluster, chainIndex,
                                  &nextCluster, &checkClusterLink);
        if (error != 0) {
            return error;
        }
        savedCluster = startCluster;
        if (nextCluster ==
            fat_special_values[volume->bpb.fat_type*5+2]) {
            file->last_cluster.num_last_cluster = startCluster;
            file->last_cluster.max_chain_index = chainIndex - 1;
            break;
        }
        startCluster = nextCluster;
        chainIndex++;
    }
    file->p_hint->chain_index = chainIndex - 1;
    *targetCluster = savedCluster;
    *nextClusterOutput = nextCluster;
    return 0;
}

s32 PFFAT_WriteValueToSpecifiedCluster(PF_VOLUME* volume, u32 cluster,
                                       u32 value)
{
    s32 error;

    switch (volume->bpb.fat_type) {
    case FAT_12:
        if (value > 0xFFF) {
            error = 16;
        } else {
            error = PFFAT12_WriteFATEntry(volume, (u16)cluster,
                                          (u16)value);
        }
        break;
    case FAT_16:
        if (value > 0xFFFF) {
            error = 16;
        } else {
            error = PFFAT16_WriteFATEntry(volume, cluster, value);
        }
        break;
    case FAT_32:
        if (value > 0x0FFFFFFF) {
            error = 16;
        } else {
            error = PFFAT32_WriteFATEntry(volume, cluster, value);
        }
        break;
    default:
        error = 15;
        break;
    }
    return error & (-error | error) >> 31;
}

s32 PFFAT_ReadValueToSpecifiedCluster(PF_VOLUME* volume, u32 cluster,
                                      u32* value)
{
    s32 error;

    switch (volume->bpb.fat_type) {
    case FAT_12:
        error = PFFAT12_ReadFATEntry(volume, (u16)cluster, value);
        break;
    case FAT_16:
        error = PFFAT16_ReadFATEntry(volume, cluster, value);
        break;
    case FAT_32:
        error = PFFAT32_ReadFATEntry(volume, cluster, value);
        break;
    default:
        *value = -1;
        error = 15;
        break;
    }
    return error & (-error | error) >> 31;
}

s32 PFFAT_AllocateNumClusters(PFFAT_FFD* file, u32 allocateSize,
                              u32* firstAllocatedCluster,
                              u32* lastAllocatedCluster, u32* allocatedSize)
{
    u32 allocatedClusters;
    s32 error;
    u32 clusterSize;
    u32 numClusters;
    PF_VOLUME* volume;

    volume = file->p_vol;
    clusterSize = volume->bpb.bytes_per_sector
                  << volume->bpb.log2_sectors_per_cluster;
    numClusters = allocateSize / clusterSize;
    if (allocateSize % clusterSize != 0) {
        numClusters++;
    }
    error = PFFAT_DoAllocateChain(file, numClusters, 1,
                                  firstAllocatedCluster,
                                  lastAllocatedCluster, 0);
    if (error != 0) {
        if (*firstAllocatedCluster != -1) {
            PFFAT_FreeChain(file, *firstAllocatedCluster, 1, -1);
        }
        *firstAllocatedCluster = -1;
        *lastAllocatedCluster = -1;
    } else {
        error = 0;
    }
    if (error != 0) {
        return error;
    }
    if (*firstAllocatedCluster == -1 || *lastAllocatedCluster == -1) {
        *allocatedSize = 0;
        return 0;
    }
    allocatedClusters = (*lastAllocatedCluster - *firstAllocatedCluster) + 1;
    if (numClusters == allocatedClusters) {
        *allocatedSize = allocateSize;
    } else {
        *allocatedSize = allocatedClusters * clusterSize;
    }
    return 0;
}

s32 PFFAT_ResetFFD(PFFAT_FFD* file, u32* startCluster)
{
    PFFAT_HINT* hint;

    hint = file->p_hint;
    file->p_start_cluster = startCluster;
    file->start_cluster = 1;
    if (hint != 0) {
        hint->previous_cluster = 0;
    }
    file->last_access_cluster.cluster = 0;
    file->last_access_cluster.chain_index = 0;
    file->last_cluster.num_last_cluster = 0;
    file->last_cluster.max_chain_index = 0;
    file->cluster_link.buffer = 0;
    return 0;
}

s32 PFFAT_InitFFD(PFFAT_FFD* file, PFFAT_HINT* hint, PF_VOLUME* volume,
                  u32* startCluster)
{
    file->p_hint = hint;
    file->p_vol = volume;
    file->p_start_cluster = startCluster;
    file->start_cluster = 1;
    if (hint != 0) {
        hint->previous_cluster = 0;
    }
    file->last_access_cluster.cluster = 0;
    file->last_access_cluster.chain_index = 0;
    file->last_cluster.num_last_cluster = 0;
    file->last_cluster.max_chain_index = 0;
    file->cluster_link.buffer = 0;
    return 0;
}

s32 PFFAT_FinalizeFFD(PFFAT_FFD* file)
{
    file->cluster_link.buffer = 0;
    return 0;
}

u32 PFFAT_GetValueOfEOC2(PF_VOLUME* volume)
{
    return fat_special_values[volume->bpb.fat_type*5+2];
}
