#include <revolution/types.h>
#include <private/fa/fa_local.h>

/* pf_cache.c */
s32 PFCACHE_FlushFATCache(PF_VOLUME* p_vol);
s32 PFCACHE_FlushDataCacheSpecific(PF_VOLUME* p_vol, u32 mode);
s32 PFCACHE_AllocateDataPage(PF_VOLUME* p_vol, s32 sector, void** pp_page, u32* p_arg);
s32 PFCACHE_FreeDataPage(PF_VOLUME* p_vol, void* p_page);

/* pf_cluster.c */
s32 PFCLUSTER_UpdateLastAccessCluster(PF_FILE* p_file, u32 sector);
s32 PFCLUSTER_AppendCluster(PF_FILE* p_file, u32 size, u32* p_size_appended);
s32 PFCLUSTER_GetAppendSize(PF_FILE* p_file, u32* p_cluster, u32* p_offset, u32* p_size);
s32 PFFILE_p_finfo(PF_FILE* p_file, PF_INFO* p_finfo, PF_FILE_HINT hint, PF_CURSOR cursor) {
    s32 err;
    PF_VOLUME* p_vol;
    u32 cluster_size;

    p_file->p_sfd->ffd.p_hint = (PF_FAT_HINT*)&p_file->hint;
    p_vol = p_file == NULL ? NULL : p_file->p_sfd->dir_entry.p_vol;
    p_finfo->file_size = p_file->p_sfd->dir_entry.file_size;
    p_finfo->io_pointer = p_file->cursor.position;
    cluster_size = (u32)p_vol->bpb.bytes_per_sector << p_vol->bpb.log2_sectors_per_cluster;
    if (p_file->p_sfd->dir_entry.start_cluster != 0) {
        err = PFCLUSTER_GetAppendSize(p_file, &p_finfo->allocated_size, NULL, NULL);
        if (err != 0) {
            return err;
        }
        p_finfo->empty_size = p_finfo->allocated_size +
            (p_finfo->file_size % cluster_size != 0 ? cluster_size - p_finfo->file_size % cluster_size : 0);
    } else {
        p_finfo->allocated_size = 0;
        p_finfo->empty_size = 0;
    }
    p_finfo->lock_mode = p_file->p_sfd->lock.mode & 3;
    p_finfo->lock_owner = p_file->p_sfd->lock.owner;
    p_finfo->lock_count = p_file->lock_count;
    p_finfo->lock_tcount = p_file->p_sfd->lock.wcount;
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
    PF_SFD* p_sfd = p_file->p_sfd;

    if ((mode & 3) != 0) {
        u16 lmode = p_sfd->lock.mode;
        if ((lmode & 3) != 0 && (mode & 8) != 0) {
            if ((mode & 1) != 0) {
                if ((lmode & 2) != 0) {
                    return 39;
                }
                if ((mode & 2) != 0 && (lmode & 1) != 0) {
                    return 39;
                }
                if (p_sfd->lock.owner != NULL && p_sfd->lock.owner != p_file) {
                    return 39;
                }
            }
        }
        if ((mode & 1) != 0) {
            if (p_sfd->lock.count == 0) {
                p_sfd->lock.wcount++;
                PF_LockFile(p_file, NULL);
                p_sfd->lock.wcount--;
                p_sfd->lock.mode = 1;
                p_sfd->lock.owner = NULL;
            } else {
                if ((p_sfd->lock.mode & 2) == 0) {
                    goto lock_count;
                }
                if (p_sfd->lock.owner == p_file) {
                    goto lock_count;
                }
                p_sfd->lock.wcount++;
                PF_LockFile(p_file, p_file);
                p_sfd->lock.wcount--;
                p_sfd->lock.mode = 2;
                p_sfd->lock.owner = p_file;
            }
        }
    lock_count:
        p_sfd->lock.count++;
        p_file->lock_count++;
    } else {
        if (p_file->lock_count == 0 || p_sfd->lock.count == 0) {
            return 39;
        }
        if ((p_sfd->lock.mode & 2) != 0 && p_sfd->lock.owner != p_file) {
            return 39;
        }
        p_file->lock_count--;
        p_sfd->lock.count--;
        if (p_sfd->lock.count == 0) {
            u16 lmode = p_sfd->lock.mode;
            PF_UnLockFile(p_file);
            if ((lmode & 2) != 0) {
                p_sfd->lock.owner = NULL;
            }
            p_sfd->lock.mode &= ~3;
        }
    }
    return err;
}

s32 PFFILE_FsexecOpenFile(PF_DIR_ENT* p_ent, PF_ENT_ITER* p_iter, u32 mode, PF_FILE** pp_file) {
    PF_SFD* p_sfd;
    PF_FILE* p_file = NULL;
    PF_VOLUME* p_vol = p_ent->p_vol;
    u32 i;
    u16 wk_time;

    *pp_file = NULL;
    if ((p_ent->attr & 0x10) != 0) {
        return 0x17;
    }
    if ((p_ent->attr & 0x01) != 0) {
        if ((mode & 1) != 0) {
            return 0x0A;
        }
        if ((mode & 4) != 0) {
            return 0x0A;
        }
        if ((mode & 8) != 0) {
            return 0x0A;
        }
    }
    if ((mode & 1) != 0) {
        if (PFFILE_IsOpened(p_ent)) {
            return 8;
        }
    }
    if ((mode & 1) != 0) {
        if (p_ent->start_cluster >= 2 && p_ent->start_cluster != -1 && p_ent->file_size != 0) {
            PFFAT_FreeChain(&p_iter->ffd, p_ent->start_cluster, -1, p_ent->file_size);
        }
        p_ent->file_size = 0;
        p_ent->start_cluster = 0;
        PFENT_getcurrentDateTimeForEnt(&p_ent->modify_date, &p_ent->modify_time);
        p_ent->access_date = p_ent->modify_date;
    } else {
        PFENT_getcurrentDateTimeForEnt(&p_ent->access_date, &wk_time);
    }
    p_sfd = PFFILE_GetSFD(p_vol, p_ent);
    if (p_sfd == NULL) {
        return 0x15;
    }
    for (i = 0; i < 5; i++) {
        if ((p_vol->dir_handle[i].stat & 0x01) == 0) {
            p_file = (PF_FILE*)&p_vol->dir_handle[i];
            break;
        }
    }
    if (p_file == NULL) {
        return 0x16;
    }
    p_file->p_sfd = p_sfd;
    p_file->stat = 0x00000001;
    p_file->open_mode = mode;
    p_file->last_error = 0;
    p_file->lock_count = 0;
    PFFAT_InitHint((PF_FAT_HINT*)&p_file->hint);
    p_file->cursor.sector = -1;
    p_file->cursor.position = 0;
    p_file->cursor.file_sector_index = p_file->cursor.position >> p_vol->bpb.log2_bytes_per_sector;
    p_file->cursor.offset_in_sector = p_file->cursor.position & (p_vol->bpb.bytes_per_sector - 1);
    if ((mode & 1) != 0) {
        p_file->p_sfd->stat |= 4;
    }
    if ((p_file->open_mode & 4) != 0) {
        PFFILE_Cursor_MoveToEnd(p_file);
    }
    *pp_file = p_file;
    return 0;
}

s32 PFFILE_IsOpened(PF_DIR_ENT* p_ent) {
    PF_VOLUME* p_vol = p_ent->p_vol;
    u32 i;

    for (i = 0; i < 5; i++) {
        if ((p_vol->file_handle[i].stat & 0x01) != 0 && (p_vol->file_handle[i].stat & 0x02) != 0 &&
            p_vol->file_handle[i].dir_entry.p_vol == p_vol &&
            p_vol->file_handle[i].dir_entry.entry_sector == p_ent->entry_sector &&
            p_vol->file_handle[i].dir_entry.entry_offset == p_ent->entry_offset) {
            return 1;
        }
    }
    return 0;
}

void PFFILE_FinalizeAllFiles(PF_VOLUME* p_vol) {
    u32 i;

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

s32 PFFILE_fopen(PF_STR* p_path_str, u32 mode, PF_FILE** pp_file) {
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
    return p_file->cursor.position >= p_file->p_sfd->dir_entry.file_size;
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
        p_file->p_sfd->ffd.cluster_link.buffer = NULL;
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
    p_vol->cache_signature = p_file;
    if ((p_vol->buffer_mode & 0x02) != 0) {
        err = PFCACHE_FlushFATCache(p_vol);
        if (err != 0) {
            pf_vol_set.last_error = err;
            p_file->p_sfd->ffd.p_vol->last_error = err;
            p_file->last_error = err;
            p_vol->cache_signature = NULL;
            return err;
        }
    }
    err = PFENT_getcurrentDateTimeForEnt(&p_file->p_sfd->dir_entry.access_date, &wk_time);
    if (err == 0) {
        err = PFENT_updateEntry(&p_file->p_sfd->dir_entry, 1);
    }
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_file->p_sfd->ffd.p_vol->last_error = err;
        p_file->last_error = err;
    } else {
        err = PFCACHE_FlushDataCacheSpecific(p_vol, (u32)p_file);
        if (err != 0) {
            pf_vol_set.last_error = err;
            p_file->p_sfd->ffd.p_vol->last_error = err;
            p_file->last_error = err;
        }
    }
    p_vol->cache_signature = NULL;
    return err;
}

s32 PFFILE_fappend(PF_FILE* p_file, u32 size, u32* p_size_appended) {
    PF_VOLUME* p_vol;
    s32 err;
    u32 size_appended = 0;
    u16 wk_time;

    *p_size_appended = 0;
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
    err = PFFILE_p_fappend(p_file, size, &size_appended);
    *p_size_appended = size_appended;
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_file->p_sfd->ffd.p_vol->last_error = err;
        p_file->last_error = err;
        p_vol->cache_signature = NULL;
        return err;
    }
    p_vol->cache_signature = NULL;
    PFENT_getcurrentDateTimeForEnt(&p_file->p_sfd->dir_entry.access_date, &wk_time);
    return 0;
}

s32 PFFILE_fadjust(PF_FILE* p_file) {
    PF_VOLUME* p_vol;
    s32 err;
    u32 save_pos;
    u32 save_sector;
    u32 save_fsi;
    u32 save_off;
    u32 save_hint0;
    u32 save_hint1;
    u32 save_hint2;
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
    save_pos = p_file->cursor.position;
    save_sector = p_file->cursor.sector;
    save_fsi = p_file->cursor.file_sector_index;
    save_off = p_file->cursor.offset_in_sector;
    save_hint0 = p_file->hint.chain_index;
    save_hint1 = p_file->hint.cluster;
    save_hint2 = p_file->hint.start_cluster;
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
    p_file->cursor.position = save_pos;
    p_file->cursor.sector = save_sector;
    p_file->cursor.file_sector_index = save_fsi;
    p_file->cursor.offset_in_sector = save_off;
    p_file->hint.chain_index = save_hint0;
    p_file->hint.cluster = save_hint1;
    p_file->hint.start_cluster = save_hint2;
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
    hint = p_file->hint;
    cursor = p_file->cursor;
    err = PFFILE_p_finfo(p_file, p_finfo, hint, cursor);
    p_file->hint = hint;
    p_file->cursor = cursor;
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
        return err;
    }
    err = PFCACHE_FlushFATCache(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    err = PFCACHE_FlushDataCacheSpecific(p_vol, 0);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
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
        if (err == 0) {
            err = PFCACHE_FlushFATCache(p_vol);
            if (err == 0) {
                err = PFCACHE_FlushDataCacheSpecific(p_vol, 0);
            }
        }
        if (err != 0) {
            pf_vol_set.last_error = err;
            p_vol->last_error = err;
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
        if (err == 0) {
            err = PFCACHE_FlushDataCacheSpecific(p_vol, 0);
            if (err == 0) {
                err = PFCACHE_FlushFATCache(p_vol);
            }
        }
        if (err != 0) {
            pf_vol_set.last_error = err;
            p_vol->last_error = err;
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
        if (err == 0) {
            err = PFCACHE_FlushDataCacheSpecific(p_vol, 0);
            if (err == 0) {
                err = PFCACHE_FlushFATCache(p_vol);
            }
        }
        if (err != 0) {
            pf_vol_set.last_error = err;
            p_vol->last_error = err;
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
