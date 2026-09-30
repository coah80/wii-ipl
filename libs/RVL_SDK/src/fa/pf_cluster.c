#include <private/vf/PrFILE2/fatfs/pf_entry.h>

typedef struct PFCLUSTER_FAT_HINT {
    pf_u32 chain_index;
    pf_u32 cluster;
    pf_u32 previous_cluster;
} PFCLUSTER_FAT_HINT;

typedef struct PFCLUSTER_FFD {
    pf_u32 start_cluster;
    pf_u32 current_start_cluster;
    pf_u32* p_start_cluster;
    PF_LAST_CLUSTER last_cluster;
    PF_FAT_LAST_ACCESS last_access_cluster;
    PF_CLUSTER_LINK cluster_link;
    PFCLUSTER_FAT_HINT* p_hint;
    PF_VOLUME* p_vol;
} PFCLUSTER_FFD;

typedef struct PFCLUSTER_ENT_ITER {
    pf_u32 index;
    PF_VOLUME* p_vol;
    PFCLUSTER_FFD ffd;
    pf_u32 file_sector_index;
    pf_u32 sector;
    pf_u16 offset;
    pf_u16 offset_mask;
    pf_u8 buf[32];
    pf_u8 log2_entries_per_sector;
} PFCLUSTER_ENT_ITER;

typedef struct PFCLUSTER_BPB {
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
    pf_s32 fat_type;
    pf_u8 log2_bytes_per_sector;
    pf_u8 log2_sectors_per_cluster;
    pf_u8 num_active_FATs;
    pf_u16 num_root_dir_sectors;
    pf_u32 active_FAT_sector;
    pf_u32 first_root_dir_sector;
    pf_u32 first_data_sector;
    pf_u32 num_clusters;
} PFCLUSTER_BPB;

struct PF_VOLUME {
    PFCLUSTER_BPB bpb;
    pf_u32 num_free_clusters;
    pf_u32 last_free_cluster;
    pf_u8 file_and_directory_state[0x1624 - 0x40];
    pf_u32 cache_mode;
    pf_u8 cache_and_driver_state[0x1f90 - 0x1628];
    pf_u16 fsi_flag;
};

typedef struct PFCLUSTER_CURSOR {
    pf_u32 position;
    pf_u32 sector;
    pf_u32 file_sector_index;
    pf_u16 offset_in_sector;
    pf_u16 reserved;
} PFCLUSTER_CURSOR;

typedef struct PFCLUSTER_SFD {
    pf_u32 stat;
    PFCLUSTER_FFD ffd;
    PF_DIR_ENT dir_entry;
} PFCLUSTER_SFD;

typedef struct PFCLUSTER_FILE {
    pf_u32 stat;
    pf_u32 open_mode;
    PFCLUSTER_SFD* p_sfd;
    PFCLUSTER_FAT_HINT hint;
    pf_s32 last_error;
    PFCLUSTER_CURSOR cursor;
} PFCLUSTER_FILE;

extern pf_s32 PFFILE_Cursor_MoveToClusterEnd(PFCLUSTER_FILE*, pf_u32);
extern pf_s32 PFFILE_Cursor_MoveToEnd(PFCLUSTER_FILE*);
extern pf_s32 PFFAT_GetSectorAllocated(PFCLUSTER_FFD*, pf_u32, pf_u32, pf_u32*);
extern pf_s32 PFFAT_getContinuousSector(PFCLUSTER_FFD*, pf_u32, pf_u32, pf_u32*, pf_u32*);
extern pf_s32 PFFAT_TraceClustersChain(PFCLUSTER_FFD*, pf_u32, pf_u32, pf_u32*, pf_u32*);
extern pf_u32 PFFAT_GetValueOfEOC2(PF_VOLUME*);
extern pf_s32 PFFAT_WriteValueToSpecifiedCluster(PF_VOLUME*, pf_u32, pf_u32);
extern pf_s32 PFFAT_ReadValueToSpecifiedCluster(PF_VOLUME*, pf_u32, pf_u32*);
extern pf_s32 PFFAT_FreeChain(PFCLUSTER_FFD*, pf_u32, pf_u32, pf_u32);
extern pf_s32 PFFAT_AllocateNumClusters(PFCLUSTER_FFD*, pf_u32, pf_u32*, pf_u32*, pf_u32*);
extern pf_s32 PFENT_updateEntry(PF_DIR_ENT*, pf_u32);
extern pf_u8 PFENT_getcurrentDateTimeForEnt(pf_u16*, pf_u16*);
extern pf_s32 PFCACHE_FlushDataCacheSpecific(PF_VOLUME*, void*);
extern pf_s32 PFCACHE_AllocateDataPage(PF_VOLUME*, pf_u32, PF_CACHE_PAGE**, pf_bool*);
extern void PFCACHE_FreeDataPage(PF_VOLUME*, PF_CACHE_PAGE*);
extern pf_s32 PFSEC_ReadData(PF_VOLUME*, pf_u8*, pf_u32, pf_u16, pf_u32, pf_u32*, pf_bool);
extern pf_s32 PFSEC_WriteData(PF_VOLUME*, const pf_u8*, pf_u32, pf_u16, pf_u32, pf_u32*, pf_bool);



void PFCLUSTER_UpdateLastAccessCluster(PFCLUSTER_FILE* p_file, pf_u32 sector) {
    PF_VOLUME* p_vol;

    if (p_file->cursor.position == 0) {
        p_file->p_sfd->ffd.last_access_cluster.cluster = 0;
        p_file->p_sfd->ffd.last_access_cluster.chain_index = 0;
        return;
    }

    p_vol = p_file == PF_NULL ? PF_NULL : p_file->p_sfd->dir_entry.p_vol;
    if ((p_file->cursor.position & (p_vol->bpb.bytes_per_sector - 1)) == 0 &&
        (p_file->cursor.file_sector_index & (p_vol->bpb.sectors_per_cluster - 1)) == 0) {
        if (p_file->cursor.file_sector_index != 0) {
            p_file->p_sfd->ffd.last_access_cluster.chain_index = (p_file->cursor.file_sector_index - 1) >> p_vol->bpb.log2_sectors_per_cluster;
            p_file->p_sfd->ffd.last_access_cluster.cluster = (((sector - 1) - p_vol->bpb.first_data_sector) >> p_vol->bpb.log2_sectors_per_cluster) + 2;
        }
    } else {
        p_file->p_sfd->ffd.last_access_cluster.chain_index = p_file->cursor.file_sector_index >> p_vol->bpb.log2_sectors_per_cluster;
        p_file->p_sfd->ffd.last_access_cluster.cluster = ((sector - p_vol->bpb.first_data_sector) >> p_vol->bpb.log2_sectors_per_cluster) + 2;
    }
}

pf_s32 PFCLUSTER_AppendCluster(PFCLUSTER_FILE* p_file, pf_u32 byte, pf_bool* p_success) {
    pf_s32 err;
    PF_VOLUME* p_vol;
    pf_u32 sector;
    pf_u32 num_sector;
    pf_u32 max_appendable_size;
    PFCLUSTER_CURSOR save_cursor;
    PFCLUSTER_FAT_HINT save_hint;

    *p_success = 0;
    if ((p_file->p_sfd->stat & 0x01) == 0 || (p_file->p_sfd->stat & 0x02) == 0) {
        return 38;
    }

    p_vol = p_file == PF_NULL ? PF_NULL : p_file->p_sfd->dir_entry.p_vol;

    save_cursor = p_file->cursor;
    save_hint = p_file->hint;

    p_file->p_sfd->ffd.p_hint = &p_file->hint;
    sector = 0xFFFFFFFF;
    if ((p_vol->fsi_flag & 0x04) != 0 && p_vol->num_free_clusters != -1 && p_vol->num_free_clusters == 0) {
        return 6;
    }
    PFFILE_Cursor_MoveToClusterEnd(p_file, p_file->p_sfd->dir_entry.file_size + byte);
    if (p_file->cursor.position == -1) {
        *p_success = 0;
        return 37;
    }
    err = PFFAT_GetSectorAllocated(&p_file->p_sfd->ffd, p_file->cursor.file_sector_index, byte, &sector);
    if (err != 0) {
        p_file->cursor = save_cursor;
        p_file->hint = save_hint;
        return err;
    }
    num_sector = 0;
    err = PFFAT_getContinuousSector(&p_file->p_sfd->ffd, p_file->cursor.file_sector_index, byte, &sector, &num_sector);
    p_file->cursor = save_cursor;
    p_file->hint = save_hint;
    if (err != 0) return err;
    if (sector == -1U) {
        PFFILE_Cursor_MoveToEnd(p_file);
        return 28;
    }
    max_appendable_size = num_sector << p_vol->bpb.log2_bytes_per_sector;
    if (byte < max_appendable_size) {
        max_appendable_size = byte;
    }
    *p_success = max_appendable_size;
    return 0;
}

pf_s32 PFCLUSTER_AdjustCluster(PFCLUSTER_FILE* p_file) {
    PF_VOLUME* p_vol;
    pf_u32 num_cluster;
    pf_u32 file_end_cluster;
    pf_u32 spare_cluster;
    pf_u32 sig_eoc;
    pf_u32 chain_index;
    pf_s32 err;

    if (((p_file->p_sfd->stat & 1) == 0) || ((p_file->p_sfd->stat & 2) == 0)) {
        return 0x26;
    }
    p_vol = p_file == PF_NULL ? PF_NULL : p_file->p_sfd->dir_entry.p_vol;

    p_file->p_sfd->ffd.p_hint = &p_file->hint;
    chain_index = -1U;
    if (p_file->p_sfd->ffd.last_cluster.max_chain_index != 0) {
        num_cluster = ((p_file->p_sfd->dir_entry.file_size & ((p_vol->bpb.bytes_per_sector << p_vol->bpb.log2_sectors_per_cluster) - 1)) ? 1 : 0) +
                      (p_file->p_sfd->dir_entry.file_size >> (p_vol->bpb.log2_bytes_per_sector + p_vol->bpb.log2_sectors_per_cluster));

        if ((p_file->p_sfd->ffd.last_cluster.max_chain_index + 1) == num_cluster) {
            return 0;
        }
    }
    if (p_file->p_sfd->dir_entry.file_size != 0) {
        err = PFFAT_TraceClustersChain(&p_file->p_sfd->ffd, p_file->p_sfd->dir_entry.start_cluster, p_file->p_sfd->dir_entry.file_size,
                                          &file_end_cluster, &spare_cluster);
        if (err != 0) {
            return err;
        }
    } else {
        file_end_cluster = 0;
        spare_cluster = p_file->p_sfd->dir_entry.start_cluster;
    }
    if (spare_cluster != 0) {
        sig_eoc = PFFAT_GetValueOfEOC2(p_vol);
        if (spare_cluster != sig_eoc) {
            if (file_end_cluster != 0) {
                err = PFFAT_WriteValueToSpecifiedCluster(p_vol, file_end_cluster, sig_eoc);
                if (err != 0) {
                    return err;
                }
                p_file->p_sfd->ffd.last_cluster.num_last_cluster = file_end_cluster;
                p_file->p_sfd->ffd.last_cluster.max_chain_index =
                    ((p_file->p_sfd->dir_entry.file_size >> (p_vol->bpb.log2_bytes_per_sector + p_vol->bpb.log2_sectors_per_cluster)) +
                     ((p_file->p_sfd->dir_entry.file_size & ((p_vol->bpb.bytes_per_sector << p_vol->bpb.log2_sectors_per_cluster) - 1)) ? 1 : 0)) -
                    1;
                chain_index = p_file->p_sfd->ffd.last_cluster.max_chain_index + 1;

            } else {
                p_file->p_sfd->dir_entry.start_cluster = 0;
                *p_file->p_sfd->ffd.p_start_cluster = 0;
                p_file->p_sfd->ffd.last_cluster.num_last_cluster = 0;
                p_file->p_sfd->ffd.last_cluster.max_chain_index = 0;
                err = PFENT_updateEntry(&p_file->p_sfd->dir_entry, 1U);
                if (err != 0) {
                    return err;
                }
                if ((p_vol->cache_mode & 4) != 0) {
                    err = PFCACHE_FlushDataCacheSpecific(p_vol, p_file);
                    if (err != 0) {
                        return err;
                    }
                }
            }
            err = PFFAT_FreeChain(&p_file->p_sfd->ffd, spare_cluster, chain_index, -1U);
            if (err != 0) {
                return err;
            }
        }
    }

    return 0;
}

pf_s32 PFCLUSTER_GetAppendSize(PFCLUSTER_FILE* p_file, pf_u32* p_size) {
    PF_VOLUME* p_vol;
    pf_u32 cluster_size;
    pf_u32 file_cluster_size;
    pf_u32 total_allocated_size;
    pf_u32 file_end_cluster;
    pf_u32 spare_cluster;
    pf_u32 next_cluster;
    pf_u32 num_append_cluster;
    pf_u32 sig_eoc;
    pf_s32 err;

    *p_size = 0;
    if ((p_file->p_sfd->stat & 0x01) == 0 || (p_file->p_sfd->stat & 0x02) == 0) {
        return 38;
    }

    p_vol = p_file == PF_NULL ? PF_NULL : p_file->p_sfd->dir_entry.p_vol;

    cluster_size = p_vol->bpb.bytes_per_sector << p_vol->bpb.log2_sectors_per_cluster;
    if (p_file->p_sfd->dir_entry.start_cluster != 0) {
        file_cluster_size =
            p_file->p_sfd->dir_entry.file_size +
            ((p_file->p_sfd->dir_entry.file_size % cluster_size) != 0 ? cluster_size - (p_file->p_sfd->dir_entry.file_size % cluster_size) : 0);
        if (p_file->p_sfd->ffd.last_cluster.max_chain_index != 0) {
            total_allocated_size = (p_file->p_sfd->ffd.last_cluster.max_chain_index + 1) * cluster_size;

        } else {
            if (p_file->p_sfd->dir_entry.file_size != 0) {
                err = PFFAT_TraceClustersChain(&p_file->p_sfd->ffd, p_file->p_sfd->dir_entry.start_cluster, p_file->p_sfd->dir_entry.file_size,
                                                  &file_end_cluster, &spare_cluster);
                if (err != 0) {
                    return err;
                }
            } else {
                spare_cluster = p_file->p_sfd->dir_entry.start_cluster;
            }

            sig_eoc = PFFAT_GetValueOfEOC2(p_vol);
            num_append_cluster = 0;
            for (; spare_cluster != sig_eoc; spare_cluster = next_cluster) {
                num_append_cluster++;
                err = PFFAT_ReadValueToSpecifiedCluster(p_vol, spare_cluster, &next_cluster);
                if (err != 0) {
                    return err;
                }
            }

            total_allocated_size = file_cluster_size + (num_append_cluster * cluster_size);
        }
        *p_size = total_allocated_size - file_cluster_size;
    }

    return 0;
}

pf_s32 PFCLUSTER_CombineFiles(PFCLUSTER_ENT_ITER* p_first_iter, PFCLUSTER_ENT_ITER* p_second_iter,
    PF_DIR_ENT* p_first_entry, PF_DIR_ENT* p_second_entry) {
    pf_s32 err;
    pf_u32 end_cluster;
    pf_u32 spare_cluster;
    pf_u32 cluster_size;
    pf_u32 first_used_clusters;
    pf_u32 second_used_clusters;
    pf_u32 first_spare_clusters;
    pf_u32 second_spare_clusters;
    pf_u32 excess_clusters;
    pf_u32 first_end_cluster;
    pf_u32 first_spare_cluster;
    pf_u32 second_spare_cluster;
    pf_u32 sig_eoc;
    PF_VOLUME* p_vol;

    p_vol = p_first_entry->p_vol;
    first_used_clusters = 0;
    second_used_clusters = 0;
    first_spare_clusters = 0;
    second_spare_clusters = 0;
    first_spare_cluster = 0;
    err = PFFAT_TraceClustersChain(&p_first_iter->ffd, *p_first_iter->ffd.p_start_cluster,
        p_first_entry->file_size, &end_cluster, &spare_cluster);
    if (err != 0) return err;
    cluster_size = p_vol->bpb.bytes_per_sector << p_vol->bpb.log2_sectors_per_cluster;
    first_end_cluster = end_cluster;
    if (p_first_entry->file_size != 0) {
        first_used_clusters = p_first_entry->file_size / cluster_size;
        if (p_first_entry->file_size % cluster_size != 0) ++first_used_clusters;
    }
    sig_eoc = PFFAT_GetValueOfEOC2(p_vol);
    if (spare_cluster != sig_eoc) {
        if (p_first_entry->file_size != 0 && spare_cluster != 0) first_spare_cluster = spare_cluster;
        else first_spare_cluster = *p_first_iter->ffd.p_start_cluster;
        err = PFFAT_TraceClustersChain(&p_first_iter->ffd, first_spare_cluster, -1U, &end_cluster, &spare_cluster);
        if (err != 0) return err;
        if (*p_first_iter->ffd.p_start_cluster != 0) {
            first_spare_clusters = p_first_iter->ffd.last_cluster.max_chain_index + 1 - first_used_clusters;
        }
    }
    err = PFFAT_TraceClustersChain(&p_second_iter->ffd, *p_second_iter->ffd.p_start_cluster,
        p_second_entry->file_size, &end_cluster, &spare_cluster);
    if (err != 0) return err;
    if (p_second_entry->file_size != 0) {
        second_used_clusters = p_second_entry->file_size / cluster_size;
        if (p_second_entry->file_size % cluster_size != 0) ++second_used_clusters;
    }
    second_spare_cluster = spare_cluster;
    if (second_spare_cluster != sig_eoc) {
        if (p_second_entry->file_size != 0 && spare_cluster != 0) {
            second_spare_cluster = spare_cluster;
        } else second_spare_cluster = *p_second_iter->ffd.p_start_cluster;
        err = PFFAT_TraceClustersChain(&p_second_iter->ffd, second_spare_cluster, -1U, &end_cluster, &spare_cluster);
        if (err != 0) return err;
        if (*p_second_iter->ffd.p_start_cluster != 0) {
            second_spare_clusters = p_second_iter->ffd.last_cluster.max_chain_index + 1 - second_used_clusters;
        }
        if (-1U / cluster_size + 1 < (second_used_clusters + second_spare_clusters) + first_used_clusters) {
            excess_clusters = (second_used_clusters + second_spare_clusters) + first_used_clusters - (-1U / cluster_size + 1);
            err = PFFAT_TraceClustersChain(&p_second_iter->ffd, second_spare_cluster,
                cluster_size * ((p_second_iter->ffd.last_cluster.max_chain_index + 1 - excess_clusters) - second_used_clusters),
                &end_cluster, &spare_cluster);
            if (err != 0) return err;
            err = PFFAT_WriteValueToSpecifiedCluster(p_vol, end_cluster, sig_eoc);
            if (err != 0) return err;
            err = PFFAT_FreeChain(&p_second_iter->ffd, spare_cluster, -1U, excess_clusters * cluster_size);
            if (err != 0) return err;
            if (p_second_entry->file_size == 0 && second_spare_clusters == excess_clusters) {
                *p_second_iter->ffd.p_start_cluster = 0;
                p_second_entry->start_cluster = 0;
            }
        }
    }
    if (first_spare_clusters != 0) {
        err = PFFAT_FreeChain(&p_first_iter->ffd, first_spare_cluster, -1U, first_spare_clusters * cluster_size);
        if (err != 0) return err;
        if (p_first_entry->file_size == 0) {
            *p_first_iter->ffd.p_start_cluster = 0;
            p_first_entry->start_cluster = 0;
        }
    }
    if (*p_first_iter->ffd.p_start_cluster != 0 && *p_second_iter->ffd.p_start_cluster != 0) {
        err = PFFAT_WriteValueToSpecifiedCluster(p_vol, first_end_cluster, *p_second_iter->ffd.p_start_cluster);
        if (err != 0) return err;
    } else if (*p_first_iter->ffd.p_start_cluster == 0 && *p_second_iter->ffd.p_start_cluster != 0) {
        p_first_entry->start_cluster = p_second_entry->start_cluster;
    }
    p_first_entry->file_size = p_second_entry->file_size + first_used_clusters * cluster_size;
    return 0;
}
pf_s32 PFCLUSTER_DivideFile(PFCLUSTER_ENT_ITER* p_source_iter, PFCLUSTER_ENT_ITER* p_dest_iter,
    PF_DIR_ENT* p_source_entry, PF_DIR_ENT* p_dest_entry, pf_u32 split_size) {
    pf_s32 err;
    pf_u32 source_end;
    pf_u32 success_size;
    pf_u32 allocated_start;
    pf_u32 allocated_end;
    pf_u32 dest_cluster;
    PF_CACHE_PAGE* p_page;
    pf_bool cache_hit;
    pf_u32 source_sector;
    pf_u32 dest_sector;
    pf_u32 sector_index;
    pf_u32 cluster_size;
    pf_u32 last_cluster;
    pf_u32 allocated_size;
    pf_u32 dest_first;
    pf_u32 remaining;
    PF_VOLUME* p_vol;
    pf_u32 saved_next;
    pf_u32 sig_eoc;

    allocated_start = 0;
    p_vol = p_source_entry->p_vol;
    dest_first = 0;
    last_cluster = 0;
    remaining = 0;

    if (split_size == 0) {
        dest_cluster = p_source_entry->start_cluster;
    } else {
        err = PFFAT_TraceClustersChain(&p_source_iter->ffd, *p_source_iter->ffd.p_start_cluster,
            split_size, &source_end, &dest_cluster);
        if (err != 0) return err;
        saved_next = dest_cluster;
        sig_eoc = PFFAT_GetValueOfEOC2(p_vol);
        err = PFFAT_WriteValueToSpecifiedCluster(p_vol, source_end, sig_eoc);
        if (err != 0) return err;
        if (split_size == p_source_entry->file_size) {
            if (dest_cluster == sig_eoc) dest_cluster = 0;
        } else {
            cluster_size = p_vol->bpb.bytes_per_sector << p_vol->bpb.log2_sectors_per_cluster;
            remaining = split_size % cluster_size;
            if (remaining != 0) {
                for (allocated_size = 0; allocated_size < cluster_size; ) {
                    err = PFFAT_AllocateNumClusters(&p_dest_iter->ffd, cluster_size,
                        &allocated_start, &allocated_end, &success_size);
                    if (err != 0) {
                        PFFAT_WriteValueToSpecifiedCluster(p_vol, source_end, saved_next);
                        return err;
                    }
                    if (success_size == 0) break;
                    if (allocated_size == 0) {
                        dest_first = allocated_start;
                    } else {
                        err = PFFAT_WriteValueToSpecifiedCluster(p_vol, last_cluster, allocated_start);
                        if (err != 0) {
                            PFFAT_FreeChain(&p_dest_iter->ffd, dest_first, -1U, allocated_size);
                            PFFAT_WriteValueToSpecifiedCluster(p_vol, source_end, saved_next);
                            return err;
                        }
                    }
                    allocated_size += success_size;
                    last_cluster = allocated_end;
                }
                if (cluster_size != allocated_size) {
                    if (allocated_size != 0) {
                        err = PFFAT_FreeChain(&p_dest_iter->ffd, dest_first, -1U, allocated_size);
                        if (err != 0) {
                            PFFAT_WriteValueToSpecifiedCluster(p_vol, source_end, saved_next);
                            return err;
                        }
                    }
                    PFFAT_FreeChain(&p_dest_iter->ffd, dest_first, -1U, allocated_size);
                    PFFAT_WriteValueToSpecifiedCluster(p_vol, source_end, saved_next);
                    return 6;
                }
                err = PFFAT_WriteValueToSpecifiedCluster(p_vol, last_cluster, dest_cluster);
                if (err != 0) {
                    PFFAT_FreeChain(&p_dest_iter->ffd, dest_first, -1U, allocated_size);
                    PFFAT_WriteValueToSpecifiedCluster(p_vol, source_end, saved_next);
                    return err;
                }
                dest_cluster = dest_first;
                source_sector = p_vol->bpb.first_data_sector + ((source_end - 2) << p_vol->bpb.log2_sectors_per_cluster);
                dest_sector = p_vol->bpb.first_data_sector + ((allocated_start - 2) << p_vol->bpb.log2_sectors_per_cluster);
                err = PFCACHE_AllocateDataPage(p_vol, -1U, &p_page, &cache_hit);
                if (err != 0) {
                    PFFAT_FreeChain(&p_dest_iter->ffd, dest_first, -1U, allocated_size);
                    PFFAT_WriteValueToSpecifiedCluster(p_vol, source_end, saved_next);
                    return err;
                }
                for (sector_index = 0; sector_index < p_vol->bpb.sectors_per_cluster; ++sector_index) {
                    err = PFSEC_ReadData(p_vol, p_page->p_buf, source_sector, 0,
                        p_vol->bpb.bytes_per_sector, &success_size, 0);
                    if (err != 0) {
                        PFFAT_FreeChain(&p_dest_iter->ffd, dest_first, -1U, allocated_size);
                        PFFAT_WriteValueToSpecifiedCluster(p_vol, source_end, saved_next);
                        return err;
                    }
                    if (success_size != p_vol->bpb.bytes_per_sector) {
                        PFFAT_FreeChain(&p_dest_iter->ffd, dest_first, -1U, allocated_size);
                        PFFAT_WriteValueToSpecifiedCluster(p_vol, source_end, saved_next);
                        return 17;
                    }
                    err = PFSEC_WriteData(p_vol, p_page->p_buf, dest_sector, 0,
                        p_vol->bpb.bytes_per_sector, &success_size, 0);
                    if (err != 0) {
                        PFFAT_FreeChain(&p_dest_iter->ffd, dest_first, -1U, allocated_size);
                        PFFAT_WriteValueToSpecifiedCluster(p_vol, source_end, saved_next);
                        return err;
                    }
                    if (success_size != p_vol->bpb.bytes_per_sector) {
                        PFFAT_FreeChain(&p_dest_iter->ffd, dest_first, -1U, allocated_size);
                        PFFAT_WriteValueToSpecifiedCluster(p_vol, source_end, saved_next);
                        return 17;
                    }
                    ++source_sector;
                    ++dest_sector;
                }
                PFCACHE_FreeDataPage(p_vol, p_page);
            }
        }
    }
    p_dest_entry->start_cluster = dest_cluster;
    p_dest_entry->file_size = p_source_entry->file_size - split_size + remaining;
    return 0;
}

pf_s32 PFCLUSTER_InsertCluster(PFCLUSTER_ENT_ITER* p_iter, PF_DIR_ENT* p_ent,
    pf_u32 cluster_index, pf_u32 num_clusters, pf_u32* p_inserted_clusters) {
    pf_s32 err;
    pf_u32 previous_cluster;
    pf_u32 next_cluster;
    pf_u32 success_size;
    pf_u32 allocated_start;
    pf_u32 allocated_end;
    pf_u32 cluster_size;
    pf_u32 allocated_size;
    pf_u32 first_cluster;
    pf_u32 last_cluster;
    pf_u32 requested_size;
    pf_u32 file_clusters;
    pf_u32 remainder;
    pf_u32 extra_size;
    PF_VOLUME* p_vol;

    p_vol = p_ent->p_vol;
    cluster_size = p_vol->bpb.bytes_per_sector << p_vol->bpb.log2_sectors_per_cluster;
    first_cluster = 0;
    last_cluster = 0;
    err = PFFAT_TraceClustersChain(&p_iter->ffd, *p_iter->ffd.p_start_cluster,
        cluster_index * cluster_size, &previous_cluster, &next_cluster);
    if (err != 0) return err;
    file_clusters = p_ent->file_size / cluster_size;
    if (p_ent->file_size % cluster_size != 0) ++file_clusters;
    if (-1U / cluster_size + 1 < file_clusters + num_clusters) {
        num_clusters = file_clusters + num_clusters - (-1U / cluster_size + 1);
    }
    requested_size = num_clusters * cluster_size;
    for (allocated_size = 0; allocated_size < requested_size; ) {
        err = PFFAT_AllocateNumClusters(&p_iter->ffd, requested_size, &allocated_start, &allocated_end, &success_size);
        if (err != 0) return err;
        if (success_size == 0) {
            if (allocated_size != 0) break;
            return 6;
        }
        if (allocated_size == 0) first_cluster = allocated_start;
        else {
            err = PFFAT_WriteValueToSpecifiedCluster(p_vol, last_cluster, allocated_start);
            if (err != 0) return err;
        }
        allocated_size += success_size;
        last_cluster = allocated_end;
    }
    if (next_cluster == 0) {
        next_cluster = p_ent->start_cluster != 0 ? p_ent->start_cluster : PFFAT_GetValueOfEOC2(p_vol);
    }
    err = PFFAT_WriteValueToSpecifiedCluster(p_vol, last_cluster, next_cluster);
    if (err != 0) return err;
    if (cluster_index != 0) {
        err = PFFAT_WriteValueToSpecifiedCluster(p_vol, previous_cluster, first_cluster);
        if (err != 0) return err;
    } else p_ent->start_cluster = first_cluster;
    file_clusters = p_ent->file_size / cluster_size;
    remainder = p_ent->file_size % cluster_size;
    if (remainder != 0) ++file_clusters;
    extra_size = 0;
    if (cluster_index == file_clusters && remainder != 0) extra_size = cluster_size - remainder;
    p_ent->file_size += allocated_size + extra_size;
    *p_inserted_clusters = allocated_size / cluster_size;
    return 0;
}

pf_s32 PFCLUSTER_DeleteCluster(PFCLUSTER_ENT_ITER* p_iter, PF_DIR_ENT* p_ent,
    pf_u32 cluster_index, pf_u32 num_clusters, pf_u32* p_deleted_clusters) {
    pf_s32 err;
    pf_u32 previous_cluster;
    pf_u32 next_cluster;
    pf_u32 first_deleted_cluster;
    pf_u32 last_deleted_cluster;
    PF_VOLUME* p_vol;
    pf_u32 cluster_size;
    pf_u32 byte_position;

    p_vol = p_ent->p_vol;
    cluster_size = p_vol->bpb.bytes_per_sector << p_vol->bpb.log2_sectors_per_cluster;
    byte_position = cluster_index * cluster_size;
    err = PFFAT_TraceClustersChain(&p_iter->ffd, *p_iter->ffd.p_start_cluster,
        byte_position, &previous_cluster, &first_deleted_cluster);
    if (err != 0) return err;
    if (cluster_index == 0) first_deleted_cluster = p_ent->start_cluster;
    num_clusters = num_clusters * cluster_size;
    if (num_clusters > p_ent->file_size - byte_position) num_clusters = p_ent->file_size - byte_position;
    err = PFFAT_TraceClustersChain(&p_iter->ffd, first_deleted_cluster, num_clusters, &last_deleted_cluster, &next_cluster);
    if (err != 0) return err;
    if (cluster_index == 0) {
        if (next_cluster == PFFAT_GetValueOfEOC2(p_vol)) next_cluster = 0;
        p_ent->start_cluster = next_cluster;
    }
    p_ent->file_size -= num_clusters;
    PFENT_getcurrentDateTimeForEnt(&p_ent->modify_date, &p_ent->modify_time);
    p_ent->access_date = p_ent->modify_date;
    err = PFENT_updateEntry(p_ent, 1);
    if (err != 0) return err;
    if (p_vol->cache_mode & 4) {
        err = PFCACHE_FlushDataCacheSpecific(p_vol, PF_NULL);
        if (err != 0) return err;
    }
    err = PFFAT_FreeChain(&p_iter->ffd, first_deleted_cluster, -1U, num_clusters);
    if (err != 0) return err;
    if (cluster_index != 0) {
        err = PFFAT_WriteValueToSpecifiedCluster(p_vol, previous_cluster, next_cluster);
        if (err != 0) return err;
    }
    *p_deleted_clusters = num_clusters / cluster_size;
    if (num_clusters % cluster_size != 0) ++*p_deleted_clusters;
    return 0;
}
