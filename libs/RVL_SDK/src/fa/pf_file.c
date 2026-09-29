#include <revolution/types.h>
#include <private/fa/fa_local.h>

/* pf_fat.c */
void PFFAT_InitFFD(PF_FFD* p_ffd, PF_FAT_HINT* p_hint, PF_VOLUME* p_vol, u32* p_start_cluster);
void PFFAT_InitHint(PF_FAT_HINT* p_hint);
s32 PFFAT_FreeChain(PF_FFD* p_ffd, u32 start_cluster, u32 chain_index, u32 size);
s32 PFFAT_GetSectorSpecified(PF_FFD* p_ffd, u32 index, u32 num, u32* p_sector);
s32 PFFAT_getContinuousSector(PF_FFD* p_ffd, u32 index, u32 num, u32* p_sector, u32* p_num_sector);
s32 PFFAT_CountAllocatedClusters(PF_FFD* p_ffd, u32 size, u32* p_num_alloc_clusters);
void PFFAT_FinalizeFFD(PF_FFD* p_ffd);

/* pf_entry.c / pf_entry_iterator.c */
s32 PFENT_InitENT(PF_DIR_ENT* p_ent, PF_STR* p_fname, u32 attr, u32 arg4, PF_DIR_ENT* p_parent_ent, PF_VOLUME* p_vol);
s32 PFENT_ITER_GetEntryOfPath(PF_ENT_ITER* p_iter, PF_DIR_ENT* p_ent, PF_VOLUME* p_vol, PF_STR* p_path, u32 arg5);
s32 PFENT_UpdateEntry(PF_DIR_ENT* p_ent, u32 arg2, u32 arg3);
s32 PFENT_UpdateSFNEntry(PF_DIR_ENT* p_ent, u32 arg2);
s32 PFENT_updateEntry(PF_DIR_ENT* p_ent, u32 arg2);
s32 PFENT_RemoveEntry(PF_DIR_ENT* p_ent, PF_ENT_ITER* p_iter);
s32 PFENT_allocateEntry(PF_DIR_ENT* p_ent, u32 num_entries, PF_FFD* p_ffd, u32* p_prev_chain, PF_STR* p_pattern, u32* p_pos);
s32 PFENT_findEntry(PF_FFD* p_ffd, PF_DIR_ENT* p_ent, u32 index_from, PF_STR* p_pattern, u32 attr, u32 flag);
u32 PFENT_CalcCheckSum(PF_DIR_ENT* p_ent);
u8 PFENT_getcurrentDateTimeForEnt(u16* p_date, u16* p_time);
s32 PFENT_GetParentEntryOfPath(PF_DIR_ENT* p_ent, PF_VOLUME* p_vol, PF_STR* p_path);

/* pf_cache.c */
s32 PFCACHE_FlushFATCache(PF_VOLUME* p_vol);
s32 PFCACHE_FlushDataCacheSpecific(PF_VOLUME* p_vol, u32 mode);
s32 PFCACHE_AllocateDataPage(PF_VOLUME* p_vol, s32 sector, void** pp_page, u32* p_arg);
s32 PFCACHE_FreeDataPage(PF_VOLUME* p_vol, void* p_page);

/* pf_cluster.c */
s32 PFCLUSTER_UpdateLastAccessCluster(PF_FILE* p_file, u32 sector);
s32 PFCLUSTER_AppendCluster(PF_FILE* p_file, u32 size, u32* p_size_appended);
s32 PFCLUSTER_GetAppendSize(PF_FILE* p_file, u32* p_size);
s32 PFCLUSTER_AdjustCluster(PF_FILE* p_file);
void PFCLUSTER_InitLastAccessCluster(PF_FAT_LAST_ACCESS* p_lac);
void PFCLUSTER_SetLastAccessCluster(PF_FAT_LAST_ACCESS* p_lac);
s32 PFCLUSTER_CombineFiles(PF_ENT_ITER* p_iter, PF_ENT_ITER* p_iter2, PF_DIR_ENT* p_ent, PF_DIR_ENT* p_ent2);
s32 PFCLUSTER_DivideFile(PF_ENT_ITER* p_iter, PF_ENT_ITER* p_iter2, PF_DIR_ENT* p_ent, PF_DIR_ENT* p_ent2, u32 pos);
s32 PFCLUSTER_InsertCluster(PF_ENT_ITER* p_iter, PF_DIR_ENT* p_ent, u32 pos, u32 size, u32* p_size_inserted);
s32 PFCLUSTER_DeleteCluster(PF_ENT_ITER* p_iter, PF_DIR_ENT* p_ent, u32 pos, u32 size, u32* p_size_deleted);

/* pf_str.c */
s32 PFSTR_SetLocalStr(PF_STR* p_str, const s8* s);

/* pf_sector.c */
s32 PFSEC_ReadData(PF_VOLUME* p_vol, u8* p_buf, u32 sector, u16 offset, u32 size, u32* p_success_size, u32 set_sig);
s32 PFSEC_ReadDataSector(PF_VOLUME* p_vol, u8* p_buf, u32 sector, u32 size, u32* p_success_size, u32 set_sig);
s32 PFSEC_WriteData(PF_VOLUME* p_vol, u8* p_buf, u32 sector, u32 offset, u32 size, u32* p_written, u32 arg7);
s32 PFSEC_WriteDataSector(PF_VOLUME* p_vol, u8* p_buf, u32 sector, u32 size, u32* p_success_size, u32 is_append, u32 set_sig);


/* pf_volume.c / pf_driver.c */
s32 PFVOL_CheckForRead(PF_VOLUME* p_vol);
s32 PFVOL_CheckForWrite(PF_VOLUME* p_vol);
s32 PFDRV_IsWProtected(PF_VOLUME* p_vol);

/* pf_filelock.c */
s32 PF_LockFile(PF_FILE* p_file, PF_FILE* p_owner);
s32 PF_UnLockFile(PF_FILE* p_file);

/* pf_clib.c */
void* pf_memset(void* s, s32 c, u32 n);
void* pf_memcpy(void* d, const void* s, u32 n);

/* forward decls */
s32 PFFILE_IsOpened(PF_DIR_ENT* p_ent);
void PFFILE_Cursor_MoveToEnd(PF_FILE* p_file);
PF_SFD* PFFILE_GetSFD(PF_VOLUME* p_vol, PF_DIR_ENT* p_ent);
s32 PFFILE_createEmptyFile(PF_VOLUME* p_vol, PF_DIR_ENT* p_ent, PF_STR* p_fname);
s32 PFFILE_p_remove(PF_VOLUME* p_vol, PF_STR* p_path_str);
s32 PFFILE_p_fopen(PF_VOLUME* p_vol, PF_STR* p_path_str, s32 mode, PF_FILE** pp_file);
s32 PFFILE_p_fread(PF_VOLUME* p_vol, u8* p_buf, u32 size, u32 count, PF_FILE* p_file, u32* p_count_read);
s32 PFFILE_p_fwrite(PF_VOLUME* p_vol, u8* p_buf, u32 size, u32 count, PF_FILE* p_file, u32* p_count_written);
s32 PFFILE_p_fappend(PF_FILE* p_file, u32 size, u32* p_size_appended);
s32 PFFILE_p_finfo(PF_FILE* p_file, PF_INFO* p_info);

static void PFFILE_Cursor_Recalc(PF_FILE* p_file) {
    PF_VOLUME* p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;

    p_file->cursor.file_sector_index = p_file->cursor.position >> p_vol->bpb.log2_bytes_per_sector;
    p_file->cursor.offset_in_sector = p_file->cursor.position & (p_vol->bpb.bytes_per_sector - 1);
}

static void PFFILE_Cursor_SetPosition(PF_FILE* p_file, u32 pos) {
    PF_VOLUME* p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    u32 pre_sec_off =
        (p_file->cursor.position >> p_vol->bpb.log2_bytes_per_sector) + ((p_file->cursor.position & (p_vol->bpb.bytes_per_sector - 1)) != 0 ? 1 : 0);
    u32 post_sec_off = (pos >> p_vol->bpb.log2_bytes_per_sector) + ((pos & (p_vol->bpb.bytes_per_sector - 1)) != 0 ? 1 : 0);

    if (pre_sec_off != post_sec_off) {
        p_file->cursor.sector = -1;
    }
    p_file->cursor.position = pos;
    PFFILE_Cursor_Recalc(p_file);
}

u32 PFFILE_Cursor_AdvanceToRead(PF_FILE* p_file, u32 n, u32 sector) {
    u32 res = 1;
    PF_VOLUME* p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    u32 wk_sector = sector + ((p_file->cursor.offset_in_sector + n) >> p_vol->bpb.log2_bytes_per_sector);

    if ((p_file->cursor.position + n) < p_file->p_sfd->dir_entry.file_size) {
        if (((p_vol->bpb.bytes_per_sector - 1) & (p_file->cursor.offset_in_sector + n)) != 0) {
            p_file->cursor.sector = sector + ((p_file->cursor.offset_in_sector + n) >> p_vol->bpb.log2_bytes_per_sector);
        } else {
            p_file->cursor.sector = -1;
        }
        p_file->cursor.position += n;
    } else if (p_file->p_sfd->dir_entry.file_size == 0) {
        p_file->cursor.sector = -1;
        p_file->cursor.position = 0;
        if (n != 0) {
            res = 0;
        }
    } else {
        p_file->cursor.sector = -1;
        p_file->cursor.position = p_file->p_sfd->dir_entry.file_size;
        res = 0;
    }
    PFFILE_Cursor_Recalc(p_file);
    PFCLUSTER_UpdateLastAccessCluster(p_file, wk_sector);
    return res;
}

static u32 PFFILE_Cursor_AdvanceToWrite(PF_FILE* p_file, u32 n, u32 sector) {
    u32 res = 1;
    PF_VOLUME* p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    u32 wk_sector = sector + ((p_file->cursor.offset_in_sector + n) >> p_vol->bpb.log2_bytes_per_sector);

    if (((p_vol->bpb.bytes_per_sector - 1) & (p_file->cursor.offset_in_sector + n)) != 0) {
        p_file->cursor.sector = sector + ((p_file->cursor.offset_in_sector + n) >> p_vol->bpb.log2_bytes_per_sector);
    } else {
        p_file->cursor.sector = -1;
    }
    p_file->cursor.position += n;
    if (p_file->cursor.position > p_file->p_sfd->dir_entry.file_size) {
        p_file->p_sfd->dir_entry.file_size = p_file->cursor.position;
    }
    PFFILE_Cursor_Recalc(p_file);
    PFCLUSTER_UpdateLastAccessCluster(p_file, wk_sector);
    return res;
}

static void PFFILE_Cursor_Initialize(PF_FILE* p_file) {
    p_file->cursor.sector = -1;
    p_file->cursor.position = 0;
    PFFILE_Cursor_Recalc(p_file);
}

s32 PFFILE_Cursor_ReadHeadSector(PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_read) {
    s32 err;
    u32 max_readable_size;
    u32 success_size;
    PF_VOLUME* p_vol;

    *p_size_read = 0;
    if (p_file->cursor.offset_in_sector == 0) {
        return 0;
    }
    p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    max_readable_size = p_vol->bpb.bytes_per_sector - p_file->cursor.offset_in_sector;
    if (size > max_readable_size) {
        size = max_readable_size;
    }
    if (p_file->cursor.position + size > p_file->p_sfd->dir_entry.file_size) {
        size = p_file->p_sfd->dir_entry.file_size - p_file->cursor.position;
        if (size < max_readable_size) {
            return 0;
        }
    }
    if (p_file->cursor.sector == -1) {
        err = PFFAT_GetSectorSpecified(&p_file->p_sfd->ffd, p_file->cursor.file_sector_index, 0, &p_file->cursor.sector);
        if (err != 0) {
            return err;
        }
        if (p_file->cursor.sector == -1) {
            PFFILE_Cursor_MoveToEnd(p_file);
            return 0x1C;
        }
        if (p_file->cursor.position + size > p_file->p_sfd->dir_entry.file_size) {
            PFFILE_Cursor_MoveToEnd(p_file);
            return 0x1B;
        }
    }
    err = PFSEC_ReadData(p_vol, p_buf, p_file->cursor.sector, p_file->cursor.offset_in_sector, size, &success_size, 1);
    if (err != 0 && success_size == 0) {
        return err;
    }
    *p_size_read = success_size;
    PFFILE_Cursor_AdvanceToRead(p_file, success_size, p_file->cursor.sector);
    if (success_size != size) {
        return err;
    }
    return 0;
}


s32 PFFILE_Cursor_ReadBodySectors(PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_read) {
    s32 err;
    u32 success_size;
    u32 num_sector;
    PF_VOLUME* p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;

    *p_size_read = 0;
    num_sector = 0;
    err = PFFAT_getContinuousSector(&p_file->p_sfd->ffd, p_file->cursor.file_sector_index, size, &p_file->cursor.sector, &num_sector);
    if (err != 0) {
        return err;
    }
    if (p_file->cursor.sector == -1) {
        PFFILE_Cursor_MoveToEnd(p_file);
        return 0x1C;
    }
    if (size > (num_sector << p_vol->bpb.log2_bytes_per_sector)) {
        size = num_sector << p_vol->bpb.log2_bytes_per_sector;
    }
    if (p_file->cursor.position + size > p_file->p_sfd->dir_entry.file_size) {
        size = p_file->p_sfd->dir_entry.file_size - p_file->cursor.position;
        size -= size & (p_vol->bpb.bytes_per_sector - 1);
        if (size < p_vol->bpb.bytes_per_sector) {
            return 0;
        }
    }
    err = PFSEC_ReadData(p_vol, p_buf, p_file->cursor.sector, p_file->cursor.offset_in_sector, size, &success_size, 1);
    if (err != 0 && success_size == 0) {
        return err;
    }
    *p_size_read = success_size;
    PFFILE_Cursor_AdvanceToRead(p_file, success_size, p_file->cursor.sector);
    if (success_size != size - (size & (p_vol->bpb.bytes_per_sector - 1))) {
        return err;
    }
    return 0;
}


s32 PFFILE_Cursor_ReadTailSector(PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_read) {
    s32 err;
    u32 success_size;
    PF_VOLUME* p_vol;

    *p_size_read = 0;
    p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    if (size == 0) {
        return 0;
    }
    if (p_file->cursor.position + size > p_file->p_sfd->dir_entry.file_size) {
        size = p_file->p_sfd->dir_entry.file_size - p_file->cursor.position;
        if (size == 0) {
            return 0;
        }
    }
    if (p_file->cursor.sector == -1) {
        err = PFFAT_GetSectorSpecified(&p_file->p_sfd->ffd, p_file->cursor.file_sector_index, 0, &p_file->cursor.sector);
        if (err != 0) {
            return err;
        }
        if (p_file->cursor.sector == -1) {
            PFFILE_Cursor_MoveToEnd(p_file);
            return 0x1C;
        }
        if (p_file->cursor.position + size > p_file->p_sfd->dir_entry.file_size) {
            PFFILE_Cursor_MoveToEnd(p_file);
            return 0x1B;
        }
    }
    err = PFSEC_ReadData(p_vol, p_buf, p_file->cursor.sector, p_file->cursor.offset_in_sector, size, &success_size, 1);
    if (err != 0 && success_size == 0) {
        return err;
    }
    *p_size_read = success_size;
    PFFILE_Cursor_AdvanceToRead(p_file, success_size, p_file->cursor.sector);
    if (success_size != size) {
        return err;
    }
    return 0;
}


s32 PFFILE_Cursor_Read(PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_read) {
    s32 err;
    PF_VOLUME* p_vol;
    u32 size_read;

    p_file->p_sfd->ffd.p_hint = (PF_FAT_HINT*)&p_file->hint;
    *p_size_read = 0;
    err = PFFILE_Cursor_ReadHeadSector(p_file, p_buf, size, &size_read);
    *p_size_read += size_read;
    if (err != 0) {
        return err;
    }
    if (size_read >= size) {
        return 0;
    }
    size -= size_read;
    p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    while (size >= p_vol->bpb.bytes_per_sector) {
        err = PFFILE_Cursor_ReadBodySectors(p_file, p_buf + *p_size_read, size, &size_read);
        *p_size_read += size_read;
        if (err != 0) {
            return err;
        }
        if (size_read == 0) {
            break;
        }
        size -= size_read;
    }
    err = PFFILE_Cursor_ReadTailSector(p_file, p_buf + *p_size_read, size, &size_read);
    *p_size_read += size_read;
    if (err != 0) {
        return err;
    }
    return 0;
}


s32 PFFILE_Cursor_WriteHeadSector(PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_write) {
    s32 err;
    u32 success_size;
    u32 max_size;
    PF_VOLUME* p_vol;

    *p_size_write = 0;
    if (p_file->cursor.offset_in_sector == 0) {
        return 0;
    }
    p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    max_size = p_vol->bpb.bytes_per_sector - p_file->cursor.offset_in_sector;
    if (size > max_size) {
        size = max_size;
    }
    if (p_file->cursor.sector == -1) {
        err = PFFAT_GetSectorSpecified(&p_file->p_sfd->ffd, p_file->cursor.file_sector_index, 0, &p_file->cursor.sector);
        if (err != 0) {
            return err;
        }
        if (p_file->cursor.sector == -1) {
            PFFILE_Cursor_MoveToEnd(p_file);
            return 0x1C;
        }
    }
    err = PFSEC_WriteData(p_vol, p_buf, p_file->cursor.sector, p_file->cursor.offset_in_sector, size, &success_size, 1);
    if (err != 0 && success_size == 0) {
        return err;
    }
    *p_size_write = success_size;
    PFFILE_Cursor_AdvanceToWrite(p_file, success_size, p_file->cursor.sector);
    if (success_size != size) {
        return err;
    }
    return 0;
}


s32 PFFILE_Cursor_WriteBodySectors(PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_write) {
    s32 err;
    u32 success_size;
    u32 num_sector;
    PF_VOLUME* p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;

    *p_size_write = 0;
    num_sector = 0;
    err = PFFAT_getContinuousSector(&p_file->p_sfd->ffd, p_file->cursor.file_sector_index, size, &p_file->cursor.sector, &num_sector);
    if (err != 0) {
        return err;
    }
    if (p_file->cursor.sector == -1) {
        PFFILE_Cursor_MoveToEnd(p_file);
        return 0x1C;
    }
    p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    if (size > (num_sector << p_vol->bpb.log2_bytes_per_sector)) {
        size = num_sector << p_vol->bpb.log2_bytes_per_sector;
    }
    err = PFSEC_WriteData(p_vol, p_buf, p_file->cursor.sector, p_file->cursor.offset_in_sector, size, &success_size, 1);
    if (err != 0 && success_size == 0) {
        return err;
    }
    *p_size_write = success_size;
    PFFILE_Cursor_AdvanceToWrite(p_file, success_size, p_file->cursor.sector);
    if (success_size != size - (size & (p_vol->bpb.bytes_per_sector - 1))) {
        return err;
    }
    return 0;
}


s32 PFFILE_Cursor_WriteTailSector(PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_write) {
    s32 err;
    u32 success_size;
    PF_VOLUME* p_vol;

    *p_size_write = 0;
    if (size == 0) {
        return 0;
    }
    p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    if (size > p_vol->bpb.bytes_per_sector - p_file->cursor.offset_in_sector || size > p_vol->bpb.bytes_per_sector) {
        return 0x1A;
    }
    if (p_file->cursor.sector == -1) {
        err = PFFAT_GetSectorSpecified(&p_file->p_sfd->ffd, p_file->cursor.file_sector_index, 0, &p_file->cursor.sector);
        if (err != 0) {
            return err;
        }
        if (p_file->cursor.sector == -1) {
            PFFILE_Cursor_MoveToEnd(p_file);
            return 0x1C;
        }
    }
    err = PFSEC_WriteData(p_vol, p_buf, p_file->cursor.sector, p_file->cursor.offset_in_sector, size, &success_size, 1);
    if (err != 0 && success_size == 0) {
        return err;
    }
    *p_size_write = success_size;
    PFFILE_Cursor_AdvanceToWrite(p_file, success_size, p_file->cursor.sector);
    if (success_size != size) {
        return err;
    }
    return 0;
}



s32 PFFILE_Cursor_Write(PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_write) {
    s32 err;
    PF_VOLUME* p_vol;
    u32 wk;
    u32 size_request;
    u32 num_cluster;
    u32 appended;

    p_file->p_sfd->ffd.p_hint = (PF_FAT_HINT*)&p_file->hint;
    *p_size_write = 0;
    if (size > 0U - 1 - p_file->cursor.position) {
        size = 0U - 1 - p_file->cursor.position;
        pf_vol_set.last_error = 0x25;
        p_file->p_sfd->ffd.p_vol->last_error = 0x25;
        p_file->last_error = 0x25;
    }
    err = PFFILE_Cursor_WriteHeadSector(p_file, p_buf, size, &wk);
    *p_size_write += wk;
    if (err != 0) {
        return err;
    }
    if (wk >= size) {
        return 0;
    }
    size -= wk;
    PFFAT_CountAllocatedClusters(&p_file->p_sfd->ffd, p_file->cursor.position + size, &num_cluster);
    p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    size_request = p_file->cursor.position + size > num_cluster << (p_vol->bpb.log2_bytes_per_sector + p_vol->bpb.log2_sectors_per_cluster)
        ? (p_file->cursor.position + size) - (num_cluster << (p_vol->bpb.log2_bytes_per_sector + p_vol->bpb.log2_sectors_per_cluster)) : 0;
    appended = 0;
    while (size_request != 0 || size >= p_vol->bpb.bytes_per_sector) {
        if (size_request != 0) {
            err = PFCLUSTER_AppendCluster(p_file, size_request, &appended);
            if (err != 0 && size == size_request) {
                return err;
            }
            if (appended == 0) {
                size_request = 0;
            }
            size_request -= appended;
        }
        if (size >= size_request + appended && size >= p_vol->bpb.bytes_per_sector) {
            err = PFFILE_Cursor_WriteBodySectors(p_file, p_buf + *p_size_write, size, &wk);
            *p_size_write += wk;
            if (err != 0) {
                return err;
            }
            if (wk == 0) {
                return 0;
            }
            size -= wk;
        }
    }
    err = PFFILE_Cursor_WriteTailSector(p_file, p_buf + *p_size_write, size, &wk);
    *p_size_write += wk;
    return err != 0 ? err : 0;
}




/* these were supposed to be static, right? */

void PFFILE_Cursor_MoveToEnd(PF_FILE* p_file) {
    p_file->cursor.position = p_file->p_sfd->dir_entry.file_size;
    PFFILE_Cursor_Recalc(p_file);
}

void PFFILE_Cursor_MoveToClusterEnd(PF_FILE* p_file, u32 size) {
    u32 num_cluster;
    PF_VOLUME* p_vol;
    u32 shift;

    p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    PFFAT_CountAllocatedClusters(&p_file->p_sfd->ffd, size, &num_cluster);
    shift = p_vol->bpb.log2_bytes_per_sector + p_vol->bpb.log2_sectors_per_cluster;
    if (num_cluster > (u32)-1 >> shift) {
        p_file->cursor.position = -1;
        PFFILE_Cursor_Recalc(p_file);
    } else {
        p_file->cursor.position = num_cluster << shift;
        PFFILE_Cursor_Recalc(p_file);
    }
}

static void PFFILE_InitSFD(PF_SFD* p_sfd, PF_DIR_ENT* p_dir_entry) {
    p_sfd = p_sfd;
    p_dir_entry = p_dir_entry;
    p_sfd->stat = 0x00000003;
    p_sfd->num_handlers = 0;
    p_sfd->dir_entry = *p_dir_entry;
    p_sfd->lock.mode = 0;
    p_sfd->lock.count = 0;
    p_sfd->lock.wcount = 0;
    p_sfd->lock.owner = NULL;
    p_sfd->lock.resource = 0;
    PFFAT_InitFFD(&p_sfd->ffd, NULL, p_dir_entry->p_vol, &p_sfd->dir_entry.start_cluster);
}

static void PFFILE_FinalizeSFD(PF_SFD* p_sfd) {
    p_sfd->stat &= ~0x7;
    PFFAT_FinalizeFFD(&p_sfd->ffd);
}

static void PFFILE_InitUFD(PF_FILE* p_file, s32 open_mode) {
    p_file->stat = 1;
    p_file->open_mode = open_mode;
    p_file->last_error = 0;
    p_file->lock_count = 0;
    PFFAT_InitHint((PF_FAT_HINT*)&p_file->hint);
    PFFILE_Cursor_Initialize(p_file);
}

static void PFFILE_FinalizeUFD(PF_FILE* p_file) {
    p_file->stat &= ~0x01;
}

PF_SFD* PFFILE_GetSFD(PF_VOLUME* p_vol, PF_DIR_ENT* p_ent) {
    u32 i;
    u32 sfd_num;
    u32 stat;
    PF_SFD* p_first_free_SFD;

    sfd_num = 0;
    p_first_free_SFD = NULL;
    for (i = 0; i < 5; i++) {
        stat = p_vol->file_handle[i].stat;
        if ((stat & 0x01) == 0 || ((stat & 0x01) != 0 && stat == 0)) {
            if (p_first_free_SFD == NULL) {
                p_first_free_SFD = &p_vol->file_handle[i];
                sfd_num = i;
            }
            continue;
        }
        if (p_ent->p_vol == p_vol->file_handle[i].dir_entry.p_vol && p_ent->entry_sector == p_vol->file_handle[i].dir_entry.entry_sector &&
            p_ent->entry_offset == p_vol->file_handle[i].dir_entry.entry_offset) {
            return &p_vol->file_handle[i];
        }
    }

    if (p_first_free_SFD == NULL) {
        return NULL;
    }
    PFFILE_InitSFD(p_first_free_SFD, p_ent);
    if ((p_vol->clst_flag & 0x01) != 0) {
        p_first_free_SFD->ffd.cluster_link.buffer = &p_vol->clst_buffer[sfd_num * p_vol->clst_link_max];
        pf_memset(p_first_free_SFD->ffd.cluster_link.buffer, 0, p_vol->clst_link_max * 4);
        p_first_free_SFD->ffd.cluster_link.max_count = p_vol->clst_link_max;
        p_first_free_SFD->ffd.cluster_link.interval = p_vol->clst_interval;
        p_first_free_SFD->ffd.cluster_link.interval_offset = 0;
        p_first_free_SFD->ffd.cluster_link.position = 0;
        p_first_free_SFD->ffd.cluster_link.save_index = 0;
        if (p_ent->file_size != 0 && p_first_free_SFD->ffd.cluster_link.max_count != 0) {
            *p_first_free_SFD->ffd.cluster_link.buffer = p_ent->start_cluster;
            p_first_free_SFD->ffd.cluster_link.position += 1;
        }
    }
    return p_first_free_SFD;
}

static s32 PFFILE_ReleaseSFD(PF_SFD* p_sfd) {
    p_sfd->num_handlers--;
    if (p_sfd->num_handlers == 0) {
        p_sfd->stat &= ~0x01;
        p_sfd->ffd.cluster_link.buffer = NULL;
    }
    return 0;
}

static PF_FILE* PFFILE_GetFreeUFD(PF_VOLUME* p_vol) {
    u32 i;

    for (i = 0; i < 5; i++) {
        if ((p_vol->dir_handle[i].stat & 0x01) == 0) {
            return (PF_FILE*)&p_vol->dir_handle[i];
        }
    }
    return NULL;
}

static s32 PFFILE_ReleaseUFD(PF_FILE* p_file) {
    p_file->stat &= ~0x01;
    return 0;
}

u32 PFFILE_CheckUFD(PF_FILE* p_file) {
    u32 is_valid = 1;
    if ((u32)&pf_vol_set > (u32)p_file || (u32)&pf_vol_set + sizeof(pf_vol_set) < (u32)p_file ||
        (p_file->stat & 0x20000000) != 0x20000000U) {
        is_valid = 0;
    }
    return is_valid;
}

s32 PFFILE_createEmptyFile(PF_VOLUME* p_vol, PF_DIR_ENT* p_ent, PF_STR* p_fname) {
    PF_DIR_ENT wk_ent;
    PF_FFD ffd;
    PF_FAT_HINT hint;
    u32 prev_chain[2];
    u32 pos;
    s32 err;
    s32 namelength;
    u8 num_lfn;
    u32 check_sum;
    u32 ordinal;
    u32* p_pos;
    u32 sector;
    u8 buf[0x20];

    wk_ent = *p_ent;
    namelength = PFSTR_StrNumChar(p_fname, 1);
    if (namelength + wk_ent.path_len > 0x103) {
        return 1;
    }
    if (namelength > 0xFF) {
        return 1;
    }
    PFFAT_InitFFD(&ffd, &hint, p_vol, &wk_ent.start_cluster);
    if (p_vol->num_open_files >= 5) {
        return 0x15;
    }
    err = PFPATH_parseShortName(p_ent->short_name, p_fname);
    if (err != 0 && p_ent->short_name[0] == 0) {
        return 1;
    }
    if (err != 0) {
        err = PFENT_AdjustSFN(&wk_ent, p_ent->short_name);
        if (err != 0) {
            return err;
        }
        if (PFSTR_GetCodeMode(p_fname) == 1) {
            PFPATH_transformInUnicode(p_ent->long_name, (s8*)PFSTR_GetStrPos(p_fname, 1));
        } else {
            pf_w_strcpy(p_ent->long_name, (u16*)PFSTR_GetStrPos(p_fname, 1));
        }
    } else {
        p_ent->long_name[0] = 0;
    }
    if (p_vol->bpb.fat_type == 2) {
        p_ent->start_cluster = 1;
    } else {
        p_ent->start_cluster = 0;
    }
    p_ent->file_size = 0;
    p_ent->p_vol = p_vol;
    p_ent->small_letter_flag = 0;
    p_ent->attr = 0x20;
    p_ent->create_time_ms = PFENT_getcurrentDateTimeForEnt(&p_ent->create_date, &p_ent->create_time);
    p_ent->access_date = p_ent->create_date;
    p_ent->modify_time = p_ent->create_time;
    p_ent->modify_date = p_ent->create_date;
    if (p_ent->long_name[0] != 0 && (p_ent->small_letter_flag & 0x18) == 0) {
        num_lfn = (u8)(namelength / 13 + (namelength % 13 != 0));
        err = PFENT_allocateEntryPos(p_ent, (u8)(num_lfn + 1), &ffd, prev_chain, p_fname, &pos);
        if (err != 0) {
            return err;
        }
        if ((pf_vol_set.setting & 2) == 2) {
            PFPATH_AdjustExtShortName(p_ent->short_name, pos);
        }
        p_ent->num_entry_LFNs = num_lfn;
        sector = p_ent->entry_sector;
        check_sum = PFENT_CalcCheckSum(p_ent);
        ordinal = num_lfn;
        p_pos = prev_chain;
        while (ordinal >= 1) {
            u32 written;
            PFENT_storeLFNEntryFieldsToBuf(buf, p_ent, (u8)ordinal, (u8)check_sum, ordinal == num_lfn);
            err = PFSEC_WriteData(p_vol, buf, sector, p_ent->entry_offset, 0x20, &written, 0);
            if (err != 0) {
                return err;
            }
            if (written != 0x20) {
                return 0x11;
            }
            p_ent->entry_offset += 0x20;
            if (p_ent->entry_offset >= p_vol->bpb.bytes_per_sector) {
                p_ent->entry_offset = 0;
                sector = *p_pos++;
            }
            ordinal--;
        }
        p_ent->entry_sector = sector;
    } else {
        err = PFENT_allocateEntry(p_ent, 1, &ffd, prev_chain, p_fname, &pos);
        if (err != 0) {
            return err;
        }
    }
    if (p_ent->start_cluster == 1) {
        p_ent->start_cluster = 0;
    }
    err = PFENT_updateEntry(p_ent, 1);
    return err;
}


static void PFFILE_EmptyFile(PF_FFD* p_ffd, PF_DIR_ENT* p_ent) {
    if (p_ent->start_cluster >= 2 && p_ent->start_cluster != -1 && p_ent->file_size != 0) {
        PFFAT_FreeChain(p_ffd, p_ent->start_cluster, -1, p_ent->file_size);
    }
    p_ent->start_cluster = 0;
    p_ent->file_size = 0;
    PFENT_getcurrentDateTimeForEnt(&p_ent->modify_date, &p_ent->modify_time);
    p_ent->access_date = p_ent->modify_date;
}

s32 PFFILE_p_remove(PF_VOLUME* p_vol, PF_STR* p_path_str) {
    PF_STR dir_str;
    PF_STR file_str;
    PF_ENT_ITER iter;
    PF_DIR_ENT ent;
    PF_FAT_HINT hint;
    u32 start_cluster;
    s32 err;

    err = PFPATH_SplitPath(p_path_str, &dir_str, &file_str);
    if (err != 0) {
        return err;
    }
    err = PFENT_ITER_GetEntryOfPath(&iter, &ent, p_vol, p_path_str, 0);
    if (err != 0) {
        return err;
    }
    hint = *iter.ffd.p_hint;
    if ((ent.attr & 0x19) != 0) {
        return 0x0B;
    }
    if (PFFILE_IsOpened(&ent) != 0) {
        return 0x13;
    }
    iter.ffd.p_hint = &hint;
    start_cluster = ent.start_cluster;
    err = PFENT_RemoveEntry(&ent, &iter);
    if (err != 0) {
        return err;
    }
    return PFFAT_FreeChain(&iter.ffd, start_cluster, -1, ent.file_size);
}


s32 PFFILE_p_fopen(PF_VOLUME* p_vol, PF_STR* p_path_str, s32 mode, PF_FILE** pp_file) {
    s32 err;
    PF_DIR_ENT ent;
    PF_ENT_ITER iter;
    PF_SFD* p_sfd;
    PF_FILE* p_file;
    u16 access_time;
    PF_STR file_str;
    PF_STR dir_str;
    PF_FFD ffd;
    PF_FAT_HINT hint;
    s8 buf[0x200];

    *pp_file = NULL;
    err = PFPATH_SplitPath(p_path_str, &dir_str, &file_str);
    if (err != 0) {
        return 1;
    }
    err = PFENT_ITER_GetEntryOfPath(&iter, &ent, p_vol, p_path_str, 1);
    if (err != 0) {
        return err;
    }
    if ((ent.attr & 0x10) == 0) {
        return 1;
    }
    if (PFSTR_GetCodeMode(&file_str) == 2) {
        if ((s32)PFSTR_StrNumChar(&file_str, 1) > 0xFF) {
            return 1;
        }
        PFPATH_transformFromUnicodeToNormal(buf, (const u16*)PFSTR_GetStrPos(&file_str, 1));
    }
    PFSTR_SetLocalStr(&file_str, buf);
    if ((mode & 2) != 0) {
        PFFAT_InitFFD(&ffd, &hint, ent.p_vol, &ent.start_cluster);
        err = PFENT_findEntry(&ffd, &ent, 0, &file_str, 0x7f, 0);
        if (err != 0) {
            return 3;
        }
        if ((mode & 8) != 0 && (ent.attr & 1) != 0) {
            return 0x0A;
        }
        if ((ent.attr & 0x10) != 0) {
            return 0x17;
        }
        PFENT_getcurrentDateTimeForEnt(&ent.access_date, &access_time);
    } else {
        err = PFFILE_createEmptyFile(p_vol, &ent, &file_str);
        if (err == 8) {
            if ((mode & 0x10) != 0) {
                return 8;
            }
            if ((mode & 1) != 0 && PFFILE_IsOpened(&ent) != 0) {
                return 8;
            }
            if ((ent.attr & 1) != 0 && ((mode & 1) != 0 || (mode & 4) != 0 || (mode & 8) != 0)) {
                return 0x0A;
            }
            if ((ent.attr & 0x10) != 0) {
                return 0x17;
            }
            if ((mode & 1) != 0) {
                if (ent.start_cluster >= 2 && ent.start_cluster != -1 && ent.file_size != 0) {
                    PFFAT_FreeChain(&iter.ffd, ent.start_cluster, -1, ent.file_size);
                }
                ent.start_cluster = 0;
                ent.file_size = 0;
                PFENT_getcurrentDateTimeForEnt(&ent.modify_date, &ent.modify_time);
                ent.access_date = ent.modify_date;
            } else {
                PFENT_getcurrentDateTimeForEnt(&ent.access_date, &access_time);
            }
        } else if (err != 0) {
            return err;
        }
    }
    p_vol = ent.p_vol;
    p_sfd = PFFILE_GetSFD(p_vol, &ent);
    if (p_sfd == NULL) {
        return 0x15;
    }
    p_file = PFFILE_GetFreeUFD(p_vol);
    if (p_file == NULL) {
        return 0x16;
    }
    p_file->p_sfd = p_sfd;
    PFFILE_InitUFD(p_file, mode);
    if ((mode & 1) != 0) {
        p_file->p_sfd->stat |= 4;
    }
    if ((p_file->open_mode & 4) != 0) {
        PFFILE_Cursor_MoveToEnd(p_file);
    }
    p_sfd->num_handlers += 1;
    *pp_file = p_file;
    return 0;
}


#pragma dont_inline on
s32 PFFILE_p_fread(PF_VOLUME* p_vol, u8* p_buf, u32 size, u32 count, PF_FILE* p_file, u32* p_count_read) {
    s32 err;
    u32 size_read = 0;

    *p_count_read = 0;
    if ((p_file->open_mode & 0x8) == 0 && ((p_file->open_mode & 1) != 0 || (p_file->open_mode & 4) != 0)) {
        return 0x0A;
    }
    if ((p_file->p_sfd->lock.mode & 3) != 0 && p_file->lock_count == 0) {
        return 0x19;
    }
    if (p_file->cursor.position >= p_file->p_sfd->dir_entry.file_size) {
        return 0x1C;
    }
    err = PFFILE_Cursor_Read(p_file, p_buf, size * count, &size_read);
    *p_count_read = size_read / size;
    return err != 0 ? err : 0;
}


#pragma dont_inline reset
s32 PFFILE_p_fwrite(PF_VOLUME* p_vol, u8* p_buf, u32 size, u32 count, PF_FILE* p_file, u32* p_count_written) {
    s32 err;
    u32 size_write = 0;
    u32 padding;
    void* p_page;
    u32 arg;

    *p_count_written = 0;
    if ((p_file->open_mode & 0x8) == 0 && (p_file->open_mode & 0x2) != 0) {
        return 0x0A;
    }
    if ((p_file->p_sfd->lock.mode & 3) != 0 && ((p_file->p_sfd->lock.mode & 1) != 0 ||
        ((p_file->p_sfd->lock.mode & 2) != 0 && p_file->lock_count == 0))) {
        return 0x19;
    }
    if ((p_file->open_mode & 4) != 0) {
        p_file->cursor.position = p_file->p_sfd->dir_entry.file_size;
        p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
        p_file->cursor.file_sector_index = p_file->cursor.position >> p_vol->bpb.log2_bytes_per_sector;
        p_file->cursor.offset_in_sector = p_file->cursor.position & (p_vol->bpb.bytes_per_sector - 1);
    }
    if (p_file->cursor.position > p_file->p_sfd->dir_entry.file_size) {
        padding = p_file->cursor.position - p_file->p_sfd->dir_entry.file_size;
        p_file->cursor.position = p_file->p_sfd->dir_entry.file_size;
        p_file->cursor.file_sector_index = p_file->cursor.position >> p_vol->bpb.log2_bytes_per_sector;
        p_file->cursor.offset_in_sector = p_file->cursor.position & (p_vol->bpb.bytes_per_sector - 1);
        err = PFCACHE_AllocateDataPage(p_vol, -1, &p_page, &arg);
        if (err != 0) {
            return err;
        }
        memset(*(u8**)((u8*)p_page + 8), 0, p_vol->bpb.bytes_per_sector);
        while (padding != 0) {
            if (padding > *(u16*)p_page) {
                err = PFFILE_Cursor_Write(p_file, *(u8**)((u8*)p_page + 8), *(u16*)p_page, &size_write);
                if (err != 0) {
                    return err;
                }
                padding -= *(u16*)p_page;
            } else {
                err = PFFILE_Cursor_Write(p_file, *(u8**)((u8*)p_page + 8), padding, &size_write);
                if (err != 0) {
                    return err;
                }
                break;
            }
        }
        PFCACHE_FreeDataPage(p_vol, p_page);
    }
    err = PFFILE_Cursor_Write(p_file, p_buf, size * count, &size_write);
    *p_count_written = size_write / size;
    if (err != 0) {
        return err;
    }
    return 0;
}


s32 PFFILE_p_fappend(PF_FILE* p_file, u32 size, u32* p_size_appended) {
    s32 err;
    u32 wk;

    *p_size_appended = 0;
    if ((p_file->open_mode & 0x08) == 0 && (p_file->open_mode & 0x02) != 0) {
        return 0x0A;
    }
    if ((p_file->p_sfd->lock.mode & 0x03) != 0 &&
        ((p_file->p_sfd->lock.mode & 0x01) != 0 ||
         ((p_file->p_sfd->lock.mode & 0x02) != 0 && p_file->lock_count == 0))) {
        return 0x19;
    }
    p_file->p_sfd->ffd.p_hint = (PF_FAT_HINT*)&p_file->hint;
    if (size > 0U - 1 - p_file->cursor.position) {
        size = 0U - 1 - p_file->cursor.position;
        err = 0x25;
        pf_vol_set.last_error = err;
        p_file->p_sfd->ffd.p_vol->last_error = err;
        p_file->last_error = err;
    }
    err = PFCLUSTER_AppendCluster(p_file, size, &wk);
    *p_size_appended = wk;
    return err != 0 ? err : 0;
}

s32 PFFILE_p_finfo(PF_FILE* p_file, PF_INFO* p_info) {
    PF_VOLUME* p_vol;
    u32 cluster_size;
    u32 rem;
    s32 err;

    p_file->p_sfd->ffd.p_hint = (PF_FAT_HINT*)&p_file->hint;
    p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    p_info->file_size = p_file->p_sfd->dir_entry.file_size;
    p_info->io_pointer = p_file->cursor.position;
    cluster_size = p_vol->bpb.bytes_per_sector << p_vol->bpb.log2_sectors_per_cluster;
    if (p_file->p_sfd->dir_entry.start_cluster != 0) {
        err = PFCLUSTER_GetAppendSize(p_file, &p_info->allocated_size);
        if (err != 0) {
            return err;
        }
        rem = p_file->p_sfd->dir_entry.file_size - (p_file->p_sfd->dir_entry.file_size / cluster_size) * cluster_size;
        p_info->empty_size = p_info->allocated_size + (rem != 0 ? cluster_size - rem : 0);
    } else {
        p_info->allocated_size = 0;
        p_info->empty_size = 0;
    }
    p_info->lock_mode = p_file->p_sfd->lock.mode & 3;
    p_info->lock_owner = p_file->p_sfd->lock.owner;
    p_info->lock_count = p_file->lock_count;
    p_info->lock_tcount = p_file->p_sfd->lock.count;
    return 0;
}



s32 PFFILE_p_combine(PF_VOLUME* p_vol, PF_STR* p_path_str, PF_STR* p_src_str) {
    s32 err;
    PF_ENT_ITER iter;
    PF_ENT_ITER iter2;
    PF_ENT_ITER iter3;
    PF_DIR_ENT dir_ent;
    PF_DIR_ENT dir_ent2;
    PF_FAT_HINT hint;
    PF_FAT_HINT hint2;

    err = PFENT_ITER_GetEntryOfPath(&iter, &dir_ent, p_vol, p_path_str, 0);
    if (err != 0) {
        return err;
    }
    err = PFENT_ITER_GetEntryOfPath(&iter2, &dir_ent2, p_vol, p_src_str, 0);
    if (err != 0) {
        return err;
    }
    if ((dir_ent.attr & 0x10) != 0 || (dir_ent2.attr & 0x10) != 0) {
        return 0x17;
    }
    if ((dir_ent.attr & 0x01) != 0 || (dir_ent2.attr & 0x01) != 0) {
        return 0x18;
    }
    if (PFFILE_IsOpened(&dir_ent) || PFFILE_IsOpened(&dir_ent2)) {
        return 0x13;
    }
    if (dir_ent.entry_sector == dir_ent2.entry_sector && dir_ent.entry_offset == dir_ent2.entry_offset) {
        return 0x0A;
    }
    if ((0xFFFFFFFF - dir_ent.file_size) < dir_ent2.file_size) {
        return 0x25;
    }
    PFFAT_InitHint(&hint);
    PFFAT_InitFFD(&iter.ffd, &hint, p_vol, &dir_ent.start_cluster);
    PFFAT_InitHint(&hint2);
    PFFAT_InitFFD(&iter2.ffd, &hint2, p_vol, &dir_ent2.start_cluster);
    pf_memcpy(&iter3, &iter2, sizeof(PF_ENT_ITER));
    err = PFENT_RemoveEntry(&dir_ent2, &iter2);
    if (err != 0) {
        return err;
    }
    err = PFCLUSTER_CombineFiles(&iter, &iter3, &dir_ent, &dir_ent2);
    if (err != 0) {
        return err;
    }
    PFENT_getcurrentDateTimeForEnt(&dir_ent.modify_date, &dir_ent.modify_time);
    dir_ent.access_date = dir_ent.modify_date;
    err = PFENT_updateEntry(&dir_ent, 1);
    return err != 0 ? err : 0;
}

s32 PFFILE_p_divide(PF_VOLUME* p_vol, PF_STR* p_path_str, PF_STR* p_dst_str, u32 pos) {
    s32 err;
    PF_ENT_ITER iter;
    PF_ENT_ITER iter2;
    PF_DIR_ENT dir_ent;
    PF_DIR_ENT dir_ent2;
    PF_DIR_ENT dir_ent3;
    PF_STR dir_str;
    PF_STR file_str;
    s8 buf[0x200];
    PF_FAT_HINT hint;
    PF_FAT_HINT hint2;
    u32 file_size;
    u32 start_cluster;

    err = PFENT_ITER_GetEntryOfPath(&iter, &dir_ent, p_vol, p_path_str, 0);
    if (err != 0) {
        return err;
    }
    if ((dir_ent.attr & 0x10) != 0) {
        return 0x17;
    }
    if ((dir_ent.attr & 0x01) != 0) {
        return 0x18;
    }
    if (PFFILE_IsOpened(&dir_ent)) {
        return 0x13;
    }
    if (dir_ent.file_size == 0) {
        return 0x0A;
    }
    if (dir_ent.file_size < pos) {
        return 0x0A;
    }
    err = PFPATH_SplitPath(p_dst_str, &dir_str, &file_str);
    if (err != 0) {
        return 1;
    }
    if (PFSTR_GetCodeMode(&file_str) == 2) {
        if ((s32)(u16)PFSTR_StrNumChar(&file_str, 1) > 0xFF) {
            return 1;
        }
        PFPATH_transformFromUnicodeToNormal(buf, (const u16*)PFSTR_GetStrPos(&file_str, 1));
    }
    PFSTR_SetLocalStr(&file_str, buf);
    err = PFENT_ITER_GetEntryOfPath(&iter2, &dir_ent2, p_vol, p_dst_str, 1);
    if (err != 0) {
        return err;
    }
    if ((dir_ent2.attr & 0x10) == 0) {
        return 1;
    }
    err = PFFILE_createEmptyFile(p_vol, &dir_ent2, &file_str);
    if (err != 0) {
        return err;
    }
    PFFAT_InitHint(&hint);
    PFFAT_InitFFD(&iter.ffd, &hint, p_vol, &dir_ent.start_cluster);
    PFFAT_InitHint(&hint2);
    PFFAT_InitFFD(&iter2.ffd, &hint2, p_vol, &dir_ent2.start_cluster);
    pf_memcpy(&dir_ent3, &dir_ent, sizeof(PF_DIR_ENT));
    file_size = dir_ent.file_size;
    start_cluster = dir_ent.start_cluster;
    PFENT_getcurrentDateTimeForEnt(&dir_ent.modify_date, &dir_ent.modify_time);
    dir_ent.access_date = dir_ent.modify_date;
    if (pos == 0) {
        dir_ent.start_cluster = 0;
    }
    dir_ent.file_size = pos;
    err = PFENT_updateEntry(&dir_ent, 1);
    if (err != 0) {
        return err;
    }
    if ((p_vol->buffer_mode & 0x04) != 0) {
        err = PFCACHE_FlushDataCacheSpecific(p_vol, 0);
        if (err != 0) {
            return err;
        }
    }
    err = PFCLUSTER_DivideFile(&iter, &iter2, &dir_ent3, &dir_ent2, pos);
    if (err != 0) {
        PFCACHE_FlushFATCache(p_vol);
        dir_ent.file_size = file_size;
        dir_ent.start_cluster = start_cluster;
        PFENT_updateEntry(&dir_ent, 1);
        PFENT_ITER_GetEntryOfPath(&iter2, &dir_ent2, p_vol, p_dst_str, 0);
        PFENT_RemoveEntry(&dir_ent2, &iter2);
        return err;
    }
    dir_ent2.modify_date = dir_ent.modify_date;
    dir_ent2.modify_time = dir_ent.modify_time;
    dir_ent2.access_date = dir_ent.access_date;
    dir_ent2.attr = dir_ent.attr;
    err = PFENT_updateEntry(&dir_ent2, 1);
    return err != 0 ? err : 0;
}

s32 PFFILE_p_cinsert(PF_VOLUME* p_vol, PF_STR* p_path_str, u32 pos, u32 size, u32* p_size_inserted) {
    s32 err;
    PF_ENT_ITER iter;
    PF_DIR_ENT dir_ent;
    PF_FAT_HINT hint;
    u32 num_clusters;

    err = PFENT_ITER_GetEntryOfPath(&iter, &dir_ent, p_vol, p_path_str, 0);
    if (err != 0) {
        return err;
    }
    if ((dir_ent.attr & 0x10) != 0) {
        return 0x17;
    }
    if ((dir_ent.attr & 0x01) != 0) {
        return 0x18;
    }
    if (PFFILE_IsOpened(&dir_ent)) {
        return 0x13;
    }
    num_clusters = dir_ent.file_size /
                   (p_vol->bpb.bytes_per_sector << p_vol->bpb.log2_sectors_per_cluster);
    if (dir_ent.file_size % (p_vol->bpb.bytes_per_sector << p_vol->bpb.log2_sectors_per_cluster) != 0) {
        num_clusters++;
    }
    if (num_clusters < pos) {
        return 0x0A;
    }
    PFFAT_InitHint(&hint);
    PFFAT_InitFFD(&iter.ffd, &hint, p_vol, &dir_ent.start_cluster);
    err = PFCLUSTER_InsertCluster(&iter, &dir_ent, pos, size, p_size_inserted);
    if (err != 0) {
        return err;
    }
    PFENT_getcurrentDateTimeForEnt(&dir_ent.modify_date, &dir_ent.modify_time);
    dir_ent.access_date = dir_ent.modify_date;
    err = PFENT_updateEntry(&dir_ent, 1);
    return err != 0 ? err : 0;
}

s32 PFFILE_p_cdelete(PF_VOLUME* p_vol, PF_STR* p_path_str, u32 pos, u32 size, u32* p_size_deleted) {
    s32 err;
    PF_ENT_ITER iter;
    PF_DIR_ENT dir_ent;
    PF_FAT_HINT hint;
    u32 num_clusters;

    err = PFENT_ITER_GetEntryOfPath(&iter, &dir_ent, p_vol, p_path_str, 0);
    if (err != 0) {
        return err;
    }
    if ((dir_ent.attr & 0x10) != 0) {
        return 0x17;
    }
    if ((dir_ent.attr & 0x01) != 0) {
        return 0x18;
    }
    if (PFFILE_IsOpened(&dir_ent)) {
        return 0x13;
    }
    if (dir_ent.file_size == 0) {
        return 0x0A;
    }
    num_clusters = dir_ent.file_size /
                   (p_vol->bpb.bytes_per_sector << p_vol->bpb.log2_sectors_per_cluster);
    if (dir_ent.file_size % (p_vol->bpb.bytes_per_sector << p_vol->bpb.log2_sectors_per_cluster) != 0) {
        num_clusters++;
    }
    if (num_clusters <= pos) {
        return 0x0A;
    }
    PFFAT_InitHint(&hint);
    PFFAT_InitFFD(&iter.ffd, &hint, p_vol, &dir_ent.start_cluster);
    err = PFCLUSTER_DeleteCluster(&iter, &dir_ent, pos, size, p_size_deleted);
    return err != 0 ? err : 0;
}

s32 PFFILE_p_flock(PF_FILE* p_file, u32 mode) {
    s32 err = 0;

    if ((mode & 3) != 0) {
        u16 lmode = p_file->p_sfd->lock.mode;
        if ((lmode & 3) != 0 && (mode & 8) != 0) {
            if (((mode & 1) != 0 && (lmode & 2) != 0) ||
                ((mode & 2) != 0 && (lmode & 1) != 0) ||
                (p_file->p_sfd->lock.owner != NULL && p_file->p_sfd->lock.owner != p_file)) {
                return 39;
            }
        }
        if ((mode & 1) != 0) {
            if (p_file->p_sfd->lock.count == 0 || (lmode & 2) != 0) {
                p_file->p_sfd->lock.wcount++;
                PF_LockFile(p_file, NULL);
                p_file->p_sfd->lock.wcount--;
                p_file->p_sfd->lock.mode = 1;
                p_file->p_sfd->lock.owner = NULL;
            }
        } else {
            if (p_file->p_sfd->lock.owner != p_file) {
                p_file->p_sfd->lock.wcount++;
                PF_LockFile(p_file, p_file);
                p_file->p_sfd->lock.wcount--;
                p_file->p_sfd->lock.mode = 2;
                p_file->p_sfd->lock.owner = p_file;
            }
        }
        p_file->p_sfd->lock.count++;
        p_file->lock_count++;
    } else {
        if (p_file->lock_count == 0 || p_file->p_sfd->lock.count == 0) {
            return 39;
        }
        if ((p_file->p_sfd->lock.mode & 2) != 0 && p_file->p_sfd->lock.owner != p_file) {
            return 39;
        }
        p_file->lock_count--;
        p_file->p_sfd->lock.count--;
        if (p_file->p_sfd->lock.count == 0) {
            PF_UnLockFile(p_file);
            if ((p_file->p_sfd->lock.mode & 2) != 0) {
                p_file->p_sfd->lock.owner = NULL;
            }
            p_file->p_sfd->lock.mode &= ~3;
        }
    }
    return err;
}

s32 PFFILE_FsexecOpenFile(PF_DIR_ENT* p_ent, PF_ENT_ITER* p_iter, u32 mode, PF_FILE** pp_file) {
    PF_SFD* p_sfd;
    PF_FILE* p_file = NULL;
    PF_VOLUME* p_vol = p_ent->p_vol;
    u16 wk_time;

    *pp_file = NULL;
    if ((p_ent->attr & 0x10) != 0) {
        return 0x17;
    }
    if ((p_ent->attr & 0x01) != 0 && ((mode & 1) != 0 || (mode & 4) != 0 || (mode & 8) != 0)) {
        return 0x0A;
    }
    if ((mode & 1) != 0) {
        if (PFFILE_IsOpened(p_ent) != 0) {
            return 8;
        }
    }
    if ((mode & 1) != 0) {
        if (p_ent->start_cluster >= 2 && p_ent->start_cluster != -1 && p_ent->file_size != 0) {
            PFFAT_FreeChain(&p_iter->ffd, p_ent->start_cluster, -1, p_ent->file_size);
        }
        p_ent->start_cluster = 0;
        p_ent->file_size = 0;
        PFENT_getcurrentDateTimeForEnt(&p_ent->modify_date, &p_ent->modify_time);
        p_ent->access_date = p_ent->modify_date;
    } else {
        PFENT_getcurrentDateTimeForEnt(&p_ent->access_date, &wk_time);
    }
    p_sfd = PFFILE_GetSFD(p_vol, p_ent);
    if (p_sfd == NULL) {
        return 0x15;
    }
    p_file = PFFILE_GetFreeUFD(p_vol);
    if (p_file == NULL) {
        return 0x16;
    }
    p_file->p_sfd = p_sfd;
    PFFILE_InitUFD(p_file, mode);
    if ((mode & 1) != 0) {
        p_file->p_sfd->stat |= 4;
    }
    if ((p_file->open_mode & 4) != 0) {
        PFFILE_Cursor_MoveToEnd(p_file);
    }
    p_sfd->num_handlers += 1;
    *pp_file = p_file;
    return 0;
}


s32 PFFILE_IsOpened(PF_DIR_ENT* p_ent) {
    PF_VOLUME* p_vol = p_ent->p_vol;
    PF_SFD* p_sfd = p_vol->file_handle;
    u32 i;

    for (i = 0; i < 5; i++, p_sfd++) {
        if ((p_sfd->stat & 0x01) != 0 && (p_sfd->stat & 0x02) != 0 &&
            p_vol == p_sfd->dir_entry.p_vol &&
            p_ent->entry_sector == p_sfd->dir_entry.entry_sector &&
            p_ent->entry_offset == p_sfd->dir_entry.entry_offset) {
            return 1;
        }
    }
    return 0;
}

void PFFILE_FinalizeAllFiles(PF_VOLUME* p_vol) {
    u16 i;

    for (i = 0; i < 5; i++) {
        p_vol->file_handle[i].stat = 0;
        PFFAT_FinalizeFFD(&p_vol->file_handle[i].ffd);
    }
    for (i = 0; i < 5; i++) {
        p_vol->dir_handle[i].stat &= ~3;
    }
    p_vol->num_open_files = 0;
}

s32 PFFILE_remove(PF_STR* p_path_str) {
    PF_VOLUME* p_vol;
    s32 err;

    p_vol = PFPATH_GetVolumeFromPath(p_path_str);
    err = PFVOL_CheckForWrite(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    p_vol->cache_signature = NULL;
    err = PFFILE_p_remove(p_vol, p_path_str);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    err = PFCACHE_FlushFATCache(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    return err;
}

s32 PFFILE_ferror(PF_FILE* p_file) {
    PF_VOLUME* p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    s32 err;

    err = PFVOL_CheckForRead(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return -1;
    }
    if ((p_file->p_sfd->stat & 0x01) == 0 || (p_file->p_sfd->stat & 0x02) == 0) {
        pf_vol_set.last_error = 0x26;
        p_vol->last_error = 0x26;
        return -1;
    }
    return p_file->last_error;
}

s32 PFFILE_fopen(PF_STR* p_path_str, s32 mode, PF_FILE** pp_file) {
    PF_VOLUME* p_vol;
    s32 err;

    *pp_file = NULL;
    p_vol = PFPATH_GetVolumeFromPath(p_path_str);
    err = PFVOL_CheckForWrite(p_vol);
    if (err != 0) {
        if (err != 0x0B || mode != 2) {
            pf_vol_set.last_error = err;
            p_vol->last_error = err;
            return err;
        }
    }
    err = PFFILE_p_fopen(p_vol, p_path_str, mode, pp_file);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    p_vol->num_open_files++;
    return err;
}

s32 PFFILE_fclose(PF_FILE* p_file) {
    PF_VOLUME* p_vol;
    s32 err;
    s32 result = 0;

    p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    err = PFVOL_CheckForWrite(p_vol);
    if (err != 0 && (err != 0x0B || (s32)p_file->open_mode != 2)) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    if ((p_file->p_sfd->stat & 0x01) == 0 || (p_file->p_sfd->stat & 0x02) == 0) {
        pf_vol_set.last_error = 0x0A;
        p_vol->last_error = 0x0A;
        return 0x0A;
    }
    p_vol->cache_signature = p_file;
    if ((p_file->p_sfd->num_handlers - 1) <= 0 && (p_file->p_sfd->dir_entry.attr & 0x19) == 0 && (err & 0x0B) == 0 &&
        ((p_file->p_sfd->stat & 0x04) != 0 || (p_vol->file_config & 0x01) != 1)) {
        result = PFENT_updateEntry(&p_file->p_sfd->dir_entry, 1);
    }
    if (p_file->lock_count != 0) {
        if ((p_file->p_sfd->lock.mode & 0x01) != 0) {
            p_file->p_sfd->lock.count -= p_file->lock_count;
            p_file->lock_count = 0;
            if (p_file->p_sfd->lock.count == 0) {
                PF_UnLockFile(p_file);
            }
            p_file->p_sfd->lock.mode &= (u16)~0x03;
        } else if (p_file->p_sfd->lock.owner != p_file) {
            result = 0x19;
        } else {
            p_file->p_sfd->lock.count = 0;
            p_file->lock_count = 0;
            p_file->p_sfd->lock.owner = NULL;
            PF_UnLockFile(p_file);
            p_file->p_sfd->lock.mode &= (u16)~0x03;
        }
    }
    if (result != 0) {
        pf_vol_set.last_error = result;
        p_file->p_sfd->ffd.p_vol->last_error = result;
        p_file->last_error = result;
    } else {
        if ((p_vol->buffer_mode & 0x02) != 0) {
            result = PFCACHE_FlushFATCache(p_vol);
            if (result != 0) {
                pf_vol_set.last_error = result;
                p_file->p_sfd->ffd.p_vol->last_error = result;
                p_file->last_error = result;
            } else {
                result = PFCACHE_FlushDataCacheSpecific(p_vol, (u32)p_file);
                if (result != 0) {
                    pf_vol_set.last_error = result;
                    p_file->p_sfd->ffd.p_vol->last_error = result;
                    p_file->last_error = result;
                }
            }
        }
        if (result == 0) {
            if (--p_file->p_sfd->num_handlers == 0) {
                p_file->p_sfd->stat &= ~0x01;
                p_file->p_sfd->ffd.cluster_link.buffer = NULL;
            }
            p_file->stat &= ~0x01;
            p_vol->num_open_files--;
        }
    }
    p_vol->cache_signature = NULL;
    return result;
}

s32 PFFILE_fread(u8* p_buf, u32 size, u32 count, PF_FILE* p_file, u32* p_count_read) {
    PF_VOLUME* p_vol;
    s32 err;
    u32 wk;

    *p_count_read = 0;
    p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    err = PFVOL_CheckForRead(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    if ((p_file->p_sfd->stat & 0x01) == 0 || (p_file->p_sfd->stat & 0x02) == 0) {
        pf_vol_set.last_error = 0x26;
        p_vol->last_error = 0x26;
        return 0x26;
    }
    p_vol->cache_signature = p_file;
    err = PFFILE_p_fread(p_vol, p_buf, size, count, p_file, &wk);
    *p_count_read = wk;
    p_vol->cache_signature = NULL;
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_file->p_sfd->ffd.p_vol->last_error = err;
        p_file->last_error = err;
    }
    return err;
}

s32 PFFILE_fwrite(u8* p_buf, u32 size, u32 count, PF_FILE* p_file, u32* p_count_written) {
    PF_VOLUME* p_vol;
    s32 err;
    u32 wk;

    *p_count_written = 0;
    p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    err = PFVOL_CheckForWrite(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    if ((p_file->p_sfd->stat & 0x01) == 0 || (p_file->p_sfd->stat & 0x02) == 0) {
        pf_vol_set.last_error = 0x26;
        p_vol->last_error = 0x26;
        return 0x26;
    }
    p_vol->cache_signature = p_file;
    err = PFFILE_p_fwrite(p_vol, p_buf, size, count, p_file, &wk);
    *p_count_written = wk;
    p_vol->cache_signature = NULL;
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_file->p_sfd->ffd.p_vol->last_error = err;
        p_file->last_error = err;
    }
    if (wk != 0) {
        PFENT_getcurrentDateTimeForEnt(&p_file->p_sfd->dir_entry.modify_date, &p_file->p_sfd->dir_entry.modify_time);
        p_file->p_sfd->dir_entry.access_date = p_file->p_sfd->dir_entry.modify_date;
        p_file->p_sfd->stat |= 4;
    }
    return err;
}

s32 PFFILE_feof(PF_FILE* p_file) {
    PF_VOLUME* p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    s32 err;

    err = PFVOL_CheckForRead(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    if ((p_file->p_sfd->stat & 0x01) == 0 || (p_file->p_sfd->stat & 0x02) == 0) {
        pf_vol_set.last_error = 0x26;
        p_vol->last_error = 0x26;
        return 0x26;
    }
    if (p_file->cursor.position >= p_file->p_sfd->dir_entry.file_size) {
        err = 1;
    }
    return err;
}

s32 PFFILE_fseek(PF_FILE* p_file, s32 lOffset, s32 nOrigin) {
    PF_VOLUME* p_vol;
    s32 err;
    u32 pos;

    p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    err = PFVOL_CheckForRead(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    if ((p_file->p_sfd->stat & 0x01) == 0 || (p_file->p_sfd->stat & 0x02) == 0) {
        pf_vol_set.last_error = 0x26;
        p_vol->last_error = 0x26;
        return 0x26;
    }
    switch (nOrigin) {
        case 1: {
            pos = p_file->cursor.position;
            break;
        }
        case 0: {
            pos = 0;
            break;
        }
        case 2: {
            pos = p_file->p_sfd->dir_entry.file_size;
            break;
        }
        default: {
            pf_vol_set.last_error = 0xA;
            p_file->p_sfd->ffd.p_vol->last_error = 0xA;
            p_file->last_error = 0xA;
            return 0xA;
        }
    }
    if ((u32)lOffset & 0x80000000) {
        if (pos < (u32)(~lOffset & 0x7fffffff) + 1) {
            pf_vol_set.last_error = 0xA;
            p_file->p_sfd->ffd.p_vol->last_error = 0xA;
            p_file->last_error = 0xA;
            return 0xA;
        }
        pos = pos - ((u32)(~lOffset & 0x7fffffff) + 1);
    } else {
        if ((u32)lOffset > 0U - 1 - pos) {
            pf_vol_set.last_error = 0x25;
            p_file->p_sfd->ffd.p_vol->last_error = 0x25;
            p_file->last_error = 0x25;
            return 0x25;
        }
        pos = pos + lOffset;
    }
    p_file->cursor.sector = -1;
    p_file->cursor.position = 0;
    p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    p_file->cursor.file_sector_index = p_file->cursor.position >> p_vol->bpb.log2_bytes_per_sector;
    p_file->cursor.offset_in_sector = (u16)(p_file->cursor.position & (p_vol->bpb.bytes_per_sector - 1));
    p_file->cursor.position = pos;
    p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    p_file->cursor.file_sector_index = p_file->cursor.position >> p_vol->bpb.log2_bytes_per_sector;
    p_file->cursor.offset_in_sector = (u16)(p_file->cursor.position & (p_vol->bpb.bytes_per_sector - 1));
    return err;
}

s32 PFFILE_fsetclstlink(PF_FILE* p_file, u32 mode, PF_CLUSTER_LINK* p_link) {
    PF_VOLUME* p_vol;
    s32 err;

    p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    err = PFVOL_CheckForRead(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    if (mode == 1) {
        p_file->p_sfd->ffd.cluster_link.buffer = p_link->buffer;
        pf_memset(p_link->buffer, 0, p_link->max_count * 4);
        p_file->p_sfd->ffd.cluster_link.max_count = p_link->max_count;
        p_file->p_sfd->ffd.cluster_link.interval = p_link->interval;
        p_file->p_sfd->ffd.cluster_link.interval_offset = 0;
        p_file->p_sfd->ffd.cluster_link.position = 0;
        p_file->p_sfd->ffd.cluster_link.save_index = 0;
        if (p_file->p_sfd->dir_entry.file_size != 0 && p_file->p_sfd->ffd.cluster_link.max_count != 0) {
            p_file->p_sfd->ffd.cluster_link.buffer[0] = *p_file->p_sfd->ffd.p_start_cluster;
            p_file->p_sfd->ffd.cluster_link.position += 1;
        }
        if (p_file->p_sfd->ffd.p_hint != NULL) {
            p_file->p_sfd->ffd.p_hint->chain_index = 0;
            p_file->p_sfd->ffd.p_hint->cluster = 0;
            p_file->p_sfd->ffd.p_hint->start_cluster = 0;
        }
        p_file->p_sfd->ffd.last_cluster.num_last_cluster = 0;
        p_file->p_sfd->ffd.last_cluster.max_chain_index = 0;
        p_file->p_sfd->ffd.last_access_cluster.chain_index = 0;
        p_file->p_sfd->ffd.last_access_cluster.cluster = 0;
    } else {
        p_file->p_sfd->ffd.cluster_link.buffer = NULL;
    }
    return err;
}

s32 PFFILE_fsync(PF_FILE* p_file) {
    PF_VOLUME* p_vol;
    s32 err;
    u16 wk_time;

    p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    err = PFVOL_CheckForWrite(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    if ((p_file->p_sfd->stat & 0x01) == 0 || (p_file->p_sfd->stat & 0x02) == 0) {
        pf_vol_set.last_error = 0x26;
        p_vol->last_error = 0x26;
        return 0x26;
    }
    err = PFCACHE_FlushFATCache(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_file->p_sfd->ffd.p_vol->last_error = err;
        p_file->last_error = err;
        return err;
    }
    PFENT_getcurrentDateTimeForEnt(&p_file->p_sfd->dir_entry.access_date, &wk_time);
    err = PFENT_updateEntry(&p_file->p_sfd->dir_entry, 1);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_file->p_sfd->ffd.p_vol->last_error = err;
        p_file->last_error = err;
        return err;
    }
    err = PFCACHE_FlushDataCacheSpecific(p_vol, (u32)p_file);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_file->p_sfd->ffd.p_vol->last_error = err;
        p_file->last_error = err;
        return err;
    }
    return err;
}

s32 PFFILE_fappend(PF_FILE* p_file, u32 size, u32* p_size_appended) {
    PF_VOLUME* p_vol;
    s32 err;
    u32 size_appended;
    u16 wk_time;

    *p_size_appended = 0;
    p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    err = PFVOL_CheckForWrite(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_file->p_sfd->ffd.p_vol->last_error = err;
        p_file->last_error = err;
        return err;
    }
    if ((p_file->p_sfd->stat & 0x01) == 0 || (p_file->p_sfd->stat & 0x02) == 0) {
        pf_vol_set.last_error = 0x26;
        p_vol->last_error = 0x26;
        return 0x26;
    }
    p_vol->cache_signature = p_file;
    err = PFFILE_p_fappend(p_file, size, &size_appended);
    *p_size_appended = size_appended;
    p_vol->cache_signature = NULL;
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_file->p_sfd->ffd.p_vol->last_error = err;
        p_file->last_error = err;
        return err;
    }
    PFENT_getcurrentDateTimeForEnt(&p_file->p_sfd->dir_entry.access_date, &wk_time);
    return 0;
}

s32 PFFILE_fadjust(PF_FILE* p_file) {
    PF_VOLUME* p_vol;
    s32 err;
    PF_FILE_HINT hint;
    PF_CURSOR cursor;
    u16 wk_time;

    p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    err = PFVOL_CheckForWrite(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_file->p_sfd->ffd.p_vol->last_error = err;
        p_file->last_error = err;
        return err;
    }
    if ((p_file->p_sfd->stat & 0x01) == 0 || (p_file->p_sfd->stat & 0x02) == 0) {
        pf_vol_set.last_error = 0x26;
        p_vol->last_error = 0x26;
        return 0x26;
    }
    p_vol->cache_signature = p_file;
    cursor = p_file->cursor;
    hint = p_file->hint;
    if ((p_file->open_mode & 0x08) == 0 && (p_file->open_mode & 0x02) != 0) {
        err = 0x0A;
    } else {
        if ((p_file->p_sfd->lock.mode & 0x3) != 0 &&
            ((p_file->p_sfd->lock.mode & 0x01) != 0 ||
             ((p_file->p_sfd->lock.mode & 0x02) != 0 && p_file->lock_count == 0))) {
            err = 0x19;
        } else {
            err = PFCLUSTER_AdjustCluster(p_file);
            err = err != 0 ? err : 0;
        }
    }
    p_file->cursor = cursor;
    p_file->hint = hint;
    p_vol->cache_signature = NULL;
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_file->p_sfd->ffd.p_vol->last_error = err;
        p_file->last_error = err;
        return err;
    }
    PFENT_getcurrentDateTimeForEnt(&p_file->p_sfd->dir_entry.access_date, &wk_time);
    return 0;
}

s32 PFFILE_finfo(PF_FILE* p_file, PF_INFO* p_finfo) {
    PF_VOLUME* p_vol;
    s32 err;
    PF_FILE_HINT hint;
    PF_CURSOR cursor;

    p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    err = PFVOL_CheckForRead(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_file->p_sfd->ffd.p_vol->last_error = err;
        p_file->last_error = err;
        return err;
    }
    if ((p_file->p_sfd->stat & 0x01) == 0 || (p_file->p_sfd->stat & 0x02) == 0) {
        pf_vol_set.last_error = 0x26;
        p_vol->last_error = 0x26;
        return 0x26;
    }
    p_vol->cache_signature = p_file;
    cursor = p_file->cursor;
    hint = p_file->hint;
    err = PFFILE_p_finfo(p_file, p_finfo);
    p_file->cursor = cursor;
    p_file->hint = hint;
    p_vol->cache_signature = NULL;
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_file->p_sfd->ffd.p_vol->last_error = err;
        p_file->last_error = err;
        return err;
    }
    return 0;
}

s32 PFFILE_combine(PF_STR* p_path_str1, PF_STR* p_path_str2) {
    PF_VOLUME* p_vol;
    PF_VOLUME* p_vol2;
    s32 err;

    p_vol = PFPATH_GetVolumeFromPath(p_path_str1);
    p_vol2 = PFPATH_GetVolumeFromPath(p_path_str2);
    if (p_vol != p_vol2) {
        pf_vol_set.last_error = 0x0A;
        return 0x0A;
    }
    err = PFVOL_CheckForWrite(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    p_vol->cache_signature = NULL;
    err = PFFILE_p_combine(p_vol, p_path_str1, p_path_str2);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
    } else {
        err = PFCACHE_FlushFATCache(p_vol);
        if (err != 0) {
            pf_vol_set.last_error = err;
            p_vol->last_error = err;
        } else {
            err = PFCACHE_FlushDataCacheSpecific(p_vol, 0);
            if (err != 0) {
                pf_vol_set.last_error = err;
                p_vol->last_error = err;
            }
        }
    }
    p_vol->cache_signature = NULL;
    return err;
}

s32 PFFILE_divide(PF_STR* p_path_str, PF_STR* p_path_str2, u32 pos) {
    PF_VOLUME* p_vol;
    s32 err;

    p_vol = PFPATH_GetVolumeFromPath(p_path_str);
    if (p_vol != PFPATH_GetVolumeFromPath(p_path_str2)) {
        pf_vol_set.last_error = 0x1F;
        return 0x1F;
    }
    err = PFVOL_CheckForWrite(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
    } else {
        p_vol->cache_signature = NULL;
        err = PFFILE_p_divide(p_vol, p_path_str, p_path_str2, pos);
        if (err != 0) {
            pf_vol_set.last_error = err;
            p_vol->last_error = err;
        } else {
            err = PFCACHE_FlushDataCacheSpecific(p_vol, 0);
            if (err != 0) {
                pf_vol_set.last_error = err;
                p_vol->last_error = err;
            } else {
                err = PFCACHE_FlushFATCache(p_vol);
                if (err != 0) {
                    pf_vol_set.last_error = err;
                    p_vol->last_error = err;
                }
            }
        }
        p_vol->cache_signature = NULL;
    }
    return err;
}
s32 PFFILE_cinsert(PF_STR* p_path_str, u32 pos, u32 size, u32* p_size_inserted) {
    PF_VOLUME* p_vol;
    s32 err;

    *p_size_inserted = 0;
    p_vol = PFPATH_GetVolumeFromPath(p_path_str);
    err = PFVOL_CheckForWrite(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
    } else {
        p_vol->cache_signature = NULL;
        err = PFFILE_p_cinsert(p_vol, p_path_str, pos, size, p_size_inserted);
        if (err != 0) {
            pf_vol_set.last_error = err;
            p_vol->last_error = err;
        } else {
            err = PFCACHE_FlushDataCacheSpecific(p_vol, 0);
            if (err != 0) {
                pf_vol_set.last_error = err;
                p_vol->last_error = err;
            } else {
                err = PFCACHE_FlushFATCache(p_vol);
                if (err != 0) {
                    pf_vol_set.last_error = err;
                    p_vol->last_error = err;
                }
            }
        }
        p_vol->cache_signature = NULL;
    }
    return err;
}

s32 PFFILE_cdelete(PF_STR* p_path_str, u32 pos, u32 size, u32* p_size_deleted) {
    PF_VOLUME* p_vol;
    s32 err;

    *p_size_deleted = 0;
    p_vol = PFPATH_GetVolumeFromPath(p_path_str);
    err = PFVOL_CheckForWrite(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
    } else {
        p_vol->cache_signature = NULL;
        err = PFFILE_p_cdelete(p_vol, p_path_str, pos, size, p_size_deleted);
        if (err != 0) {
            pf_vol_set.last_error = err;
            p_vol->last_error = err;
        } else {
            err = PFCACHE_FlushDataCacheSpecific(p_vol, 0);
            if (err != 0) {
                pf_vol_set.last_error = err;
                p_vol->last_error = err;
            } else {
                err = PFCACHE_FlushFATCache(p_vol);
                if (err != 0) {
                    pf_vol_set.last_error = err;
                    p_vol->last_error = err;
                }
            }
        }
        p_vol->cache_signature = NULL;
    }
    return err;
}

s32 PFFILE_flock(PF_FILE* p_file, u32 mode) {
    PF_VOLUME* p_vol;
    s32 err;

    p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    err = PFVOL_CheckForRead(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    if ((p_file->p_sfd->stat & 0x01) == 0 || (p_file->p_sfd->stat & 0x02) == 0) {
        pf_vol_set.last_error = 0x26;
        p_vol->last_error = 0x26;
        return 0x26;
    }
    err = PFFILE_p_flock(p_file, mode);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    return err;
}
