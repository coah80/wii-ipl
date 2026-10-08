#define PF_FA_STR_LAYOUT
#include <decomp/utils.h>
#include <revolution/fa/types.h>
#include <private/vf/PrFILE2/fatfs/pf_volume.h>
#include <private/vf/PrFILE2/fatfs/pf_dir.h>
#include <private/vf/PrFILE2/fatfs/pf_path.h>
#include <private/vf/PrFILE2/pf_types.h>

typedef struct PFFILE_FAT_HINT {
    pf_u32 chain_index;
    pf_u32 cluster;
    pf_u32 previous_cluster;
} PFFILE_FAT_HINT;

typedef struct PFFILE_FFD {
    pf_u32 start_cluster;
    pf_u32 flags;
    pf_u32* p_start_cluster;
    PF_LAST_CLUSTER last_cluster;
    PF_FAT_LAST_ACCESS last_access_cluster;
    PF_CLUSTER_LINK cluster_link;
    PF_FAT_HINT* p_hint;
    PF_VOLUME* p_vol;
} PFFILE_FFD;

typedef struct PFFILE_CURSOR {
    pf_u32 position;
    pf_u32 sector;
    pf_u32 file_sector_index;
    pf_u16 offset_in_sector;
    pf_u16 reserved;
} PFFILE_CURSOR;

typedef struct PFFILE_SFD {
    pf_u32 stat;
    PFFILE_FFD ffd;
    PF_DIR_ENT dir_entry;
    PF_LOCK lock;
    pf_u32 lock_state[3];
    pf_u16 handler_count;
    pf_u8 reserved[2];
} PFFILE_SFD;

typedef struct PFFILE_SDD {
    pf_u32 stat;
    pf_u16 num_handlers;
    pf_u16 alignment;
    PFFILE_FFD ffd;
    PF_DIR_ENT dir_entry;
} PFFILE_SDD;

typedef struct PFFILE_FILE PFFILE_FILE;

typedef struct PFFILE_DIR {
    pf_u32 stat;
    PFFILE_SDD* p_sdd;
    PFFILE_FAT_HINT hint;
    pf_u32 current_position;
    pf_u32 next_position;
    pf_u32 end_position;
} PFFILE_DIR;

typedef struct PFFILE_ENT_ITER {
    pf_u32 index;
    PF_VOLUME* p_vol;
    PFFILE_FFD ffd;
    pf_u32 file_sector_index;
    pf_u32 sector;
    pf_u16 offset;
    pf_u16 offset_mask;
    pf_u8 buffer[32];
    pf_u8 log2_entries_per_sector;
} PFFILE_ENT_ITER;

typedef struct PFFILE_CLUSTER_LINK_VOL {
    pf_u16 flag;
    pf_u16 interval;
    pf_u32* buffer;
    pf_u32 link_max;
} PFFILE_CLUSTER_LINK_VOL;

typedef struct PFFILE_CLUSTER_LINK_SETTINGS {
    pf_u32* buffer;
    pf_u32 link_max;
    pf_u16 interval;
    pf_u16 reserved;
} PFFILE_CLUSTER_LINK_SETTINGS;

typedef struct PFFILE_GLOBAL_STATE {
    pf_u8 state_prefix[0x40];
    pf_s32 last_error;
    pf_u8 settings_prefix[0x1C];
    pf_u32 file_settings;
} PFFILE_GLOBAL_STATE;

struct PFFILE_FILE {
    pf_u32 stat;
    pf_u32 open_mode;
    PFFILE_SFD* p_sfd;
    PF_FAT_HINT hint;
    union {
        PF_FAT_HINT last_access;
        struct {
            pf_u32 last_access_chain_index;
            pf_s32 last_error;
        } state;
    } last_access_data;
    PFFILE_CURSOR cursor;
    pf_u16 lock_count;
    pf_u16 state_flags;
};

typedef struct PFFILE_VOLUME_DIRS {
    pf_u8 volume_prefix[0x40];
    PFFILE_SFD sfds[5];
    PFFILE_FILE ufds[5];
    PFFILE_SDD sdds[3];
    PFFILE_DIR udds[3];
    pf_s32 num_opened_files;
    pf_s32 num_opened_directories;
    pf_u32 cache_control;
    pf_u8 cache_state[0x1C];
    void* cache_signature;
    pf_u8 volume_tail[0x1F80 - 0x1648];
    pf_s32 last_error;
    pf_s32 last_driver_error;
    pf_u32 file_config;
    pf_u16 flags;
    pf_u8 drv_char;
    pf_u16 fsi_flag;
    pf_u16 cluster_link_alignment;
    PFFILE_CLUSTER_LINK_VOL cluster_link;
} PFFILE_VOLUME_DIRS;

extern void PFCLUSTER_UpdateLastAccessCluster();
extern pf_s32 PFFAT_GetSectorSpecified(PFFILE_FFD* ffd, pf_u32 file_sector_index, pf_u32 cluster_index,
                                       pf_u32* sector);
extern pf_s32 PFFAT_getContinuousSector(PFFILE_FFD* ffd, pf_u32 file_sector_index, pf_u32 size,
                                         pf_u32* sector, pf_u32* num_sectors);
extern pf_s32 PFSEC_ReadData(PF_VOLUME* volume, pf_u8* buffer, pf_u32 sector, pf_u16 offset,
                             pf_u32 size, pf_u32* size_read, pf_u32 mode);
extern pf_s32 PFSEC_WriteData(PF_VOLUME* volume, const pf_u8* buffer, pf_u32 sector, pf_u16 offset,
                              pf_u32 size, pf_u32* size_written, pf_u32 mode);
extern pf_s32 PFFAT_CountAllocatedClusters(PFFILE_FFD* ffd, pf_u32 position, pf_u32* num_clusters);
extern pf_s32 PFCLUSTER_AppendCluster(PFFILE_FILE* file, pf_u32 size, pf_u32* appended_size);
extern pf_s32 PFCLUSTER_AdjustCluster(PFFILE_FILE* file);
extern pf_s32 PFCLUSTER_GetAppendSize(PFFILE_FILE* file, pf_u32* append_size);
extern pf_s32 PFFAT_InitFFD(PFFILE_FFD* ffd, void* hint, PF_VOLUME* volume, pf_u32* start_cluster);
extern void* pf_memset(void* destination, pf_s32 value, pf_u32 size);
extern pf_u32 PFSTR_StrNumChar(PF_STR* path_string, pf_u32 mode);
extern pf_u32 PFSTR_GetCodeMode(PF_STR* path_string);
extern void* PFSTR_GetStrPos(PF_STR* path_string, pf_u32 mode);
extern pf_s32 PFPATH_parseShortName(pf_s8* short_name, PF_STR* path_string);
extern pf_s32 PFENT_AdjustSFN(PF_DIR_ENT* entry, pf_s8* short_name);
extern void PFPATH_transformInUnicode(PF_DIR_ENT* entry, void* unicode_text);
extern pf_u16* pf_w_strcpy(pf_u16* destination, const pf_u16* source);
extern pf_u8 PFENT_getcurrentDateTimeForEnt(pf_u16* date, pf_u16* time);
extern pf_s32 PFENT_allocateEntry(PF_DIR_ENT* entry, pf_u32 count, PFFILE_FFD* ffd,
                                  pf_u32* previous_sectors, PF_STR* filename);
extern pf_s32 PFENT_allocateEntryPos(PF_DIR_ENT* entry, pf_u32 count, PFFILE_FFD* ffd,
                                     pf_u32* previous_sectors, PF_STR* filename,
                                     pf_u32* position);
extern void PFPATH_AdjustExtShortName(pf_s8* short_name, pf_u32 position);
extern pf_u8 PFENT_CalcCheckSum(PF_DIR_ENT* entry);
extern void PFENT_storeLFNEntryFieldsToBuf(pf_u8* buffer, PF_DIR_ENT* entry, pf_u8 ordinal,
                                           pf_u8 checksum, pf_bool is_last);
extern pf_s32 PFENT_updateEntry(PF_DIR_ENT* entry, pf_u32 update_archive);
extern pf_s32 PFPATH_SplitPath(PF_STR* path, PF_STR* directory, PF_STR* filename);
extern pf_s32 PFENT_ITER_GetEntryOfPath(PFFILE_ENT_ITER* iter, PF_DIR_ENT* entry,
                                        PF_VOLUME* volume, PF_STR* path, pf_u32 no_look_last);
extern pf_s32 PFENT_RemoveEntry(PF_DIR_ENT* entry, PFFILE_ENT_ITER* iter);
extern pf_s32 PFFAT_FreeChain(PFFILE_FFD* ffd, pf_u32 start_cluster, pf_u32 chain_index,
                              pf_u32 size);
extern pf_s32 PFCACHE_AllocateDataPage(PF_VOLUME* volume, pf_u32 sector,
                                       PF_CACHE_PAGE** page, pf_u32* option);
extern void PFCACHE_FreeDataPage(PF_VOLUME* volume, PF_CACHE_PAGE* page);
extern pf_s32 PFENT_findEntry(PFFILE_FFD* ffd, PF_DIR_ENT* entry, pf_u32 start,
                              PF_STR* pattern, pf_u8 attr_required, pf_u32 flags);
extern pf_s32 PFCLUSTER_CombineFiles(PFFILE_ENT_ITER* first_iter,
                                     PFFILE_ENT_ITER* second_iter_copy,
                                     PF_DIR_ENT* first_entry, PF_DIR_ENT* second_entry);
extern pf_s32 PFCLUSTER_InsertCluster(PFFILE_ENT_ITER* iter, PF_DIR_ENT* entry,
                                      pf_u32 cluster_index, pf_u32 count, pf_u32 mode);
extern pf_s32 PFCLUSTER_DeleteCluster(PFFILE_ENT_ITER* iter, PF_DIR_ENT* entry,
                                      pf_u32 cluster_index, pf_u32 count, pf_u32 mode);
extern pf_s32 PFCLUSTER_DivideFile(PFFILE_ENT_ITER* source_iter,
                                   PFFILE_ENT_ITER* destination_iter,
                                   PF_DIR_ENT* source_entry_copy,
                                   PF_DIR_ENT* destination_entry, pf_u32 split_size);
extern void* pf_memcpy(void* destination, const void* source, pf_u32 size);
extern pf_s32 PFCACHE_FlushDataCacheSpecific(PF_VOLUME* volume, void* signature);
extern pf_s32 PFCACHE_FlushFATCache(PF_VOLUME* volume);
extern void PFFAT_InitHint(void* hint);
extern void PFFAT_FinalizeFFD(PFFILE_FFD* ffd);
extern void PFSTR_SetLocalStr(PF_STR* path_string, const pf_s8* converted_path);
extern pf_s32 PFPATH_transformFromUnicodeToNormal(pf_s8* destination, const pf_u16* source);
extern PF_VOLUME* PFPATH_GetVolumeFromPath(PF_STR* path_string);
extern pf_s32 PFVOL_CheckForWrite(PF_VOLUME* volume);
extern pf_s32 PFVOL_CheckForRead(PF_VOLUME* volume);
extern pf_s32 PFDRV_IsWProtected(PF_VOLUME* volume);
extern pf_s32 PF_LockFile(PF_FILE* file, PF_FILE* owner);
extern pf_s32 PF_UnLockFile(PF_FILE* file);
extern pf_bool PFFILE_IsOpened(PF_DIR_ENT* entry);
extern PFFILE_GLOBAL_STATE pf_vol_set;

static void PFFILE_Cursor_Recalc(PFFILE_FILE* file) {
    PF_VOLUME* volume = file == PF_NULL ? PF_NULL : file->p_sfd->dir_entry.p_vol;

    file->cursor.file_sector_index = file->cursor.position >> volume->bpb.log2_bytes_per_sector;
    file->cursor.offset_in_sector = file->cursor.position & (volume->bpb.bytes_per_sector - 1);
}

pf_bool PFFILE_Cursor_AdvanceToRead(PFFILE_FILE* file, pf_u32 size, pf_u32 sector) {
    pf_bool result = PF_TRUE;
    PF_VOLUME* volume = file == PF_NULL ? PF_NULL : file->p_sfd->dir_entry.p_vol;
    pf_u32 next_sector = sector + ((file->cursor.offset_in_sector + size) >> volume->bpb.log2_bytes_per_sector);

    if ((file->cursor.position + size) < file->p_sfd->dir_entry.file_size) {
        if (((volume->bpb.bytes_per_sector - 1) & (file->cursor.offset_in_sector + size)) != 0) {
            file->cursor.sector = sector + ((file->cursor.offset_in_sector + size) >> volume->bpb.log2_bytes_per_sector);
        } else {
            file->cursor.sector = -1;
        }
        file->cursor.position += size;
    } else if (file->p_sfd->dir_entry.file_size == 0) {
        file->cursor.sector = -1;
        file->cursor.position = 0;
        if (size != 0) {
            result = PF_FALSE;
        }
    } else {
        file->cursor.sector = -1;
        file->cursor.position = file->p_sfd->dir_entry.file_size;
        result = PF_FALSE;
    }
    PFFILE_Cursor_Recalc(file);
    PFCLUSTER_UpdateLastAccessCluster(file, next_sector);
    return result;
}

pf_s32 PFFILE_Cursor_ReadHeadSector(PFFILE_FILE* file, pf_u8* buffer, pf_u32 size, pf_u32* size_read) {
    pf_s32 error;
    pf_u32 max_size;
    pf_u32 success_size;
    PF_VOLUME* volume;

    *size_read = 0;
    if (file->cursor.offset_in_sector == 0) {
        return 0;
    }
    volume = file == PF_NULL ? PF_NULL : file->p_sfd->dir_entry.p_vol;
    max_size = volume->bpb.bytes_per_sector - file->cursor.offset_in_sector;
    if (size > max_size) {
        size = max_size;
    }
    if (file->cursor.position + size > file->p_sfd->dir_entry.file_size) {
        size = file->p_sfd->dir_entry.file_size - file->cursor.position;
        if (size < max_size) {
            return 0;
        }
    }
    if (file->cursor.sector == -1) {
        error = PFFAT_GetSectorSpecified(&file->p_sfd->ffd, file->cursor.file_sector_index, 0,
                                         &file->cursor.sector);
        if (error != 0) {
            return error;
        }
        if (file->cursor.sector == -1) {
            file->cursor.position = file->p_sfd->dir_entry.file_size;
            PFFILE_Cursor_Recalc(file);
            return 0x1C;
        }
        if (file->cursor.position + size > file->p_sfd->dir_entry.file_size) {
            file->cursor.position = file->p_sfd->dir_entry.file_size;
            PFFILE_Cursor_Recalc(file);
            return 0x1B;
        }
    }
    error = PFSEC_ReadData(volume, buffer, file->cursor.sector, file->cursor.offset_in_sector, size,
                           &success_size, 1);
    if (error != 0 && success_size == 0) {
        return error;
    }
    *size_read = success_size;
    PFFILE_Cursor_AdvanceToRead(file, success_size, file->cursor.sector);
    if (success_size != size) {
        return error;
    }
    return 0;
}

pf_s32 PFFILE_Cursor_ReadBodySectors(PFFILE_FILE* file, pf_u8* buffer, pf_u32 size,
                                     pf_u32* size_read) {
    pf_s32 error;
    pf_u32 num_sectors;
    pf_u32 max_size;
    pf_u32 success_size;
    PF_VOLUME* volume;

    *size_read = 0;
    volume = file == PF_NULL ? PF_NULL : file->p_sfd->dir_entry.p_vol;
    num_sectors = 0;
    error = PFFAT_getContinuousSector(&file->p_sfd->ffd, file->cursor.file_sector_index, size,
                                      &file->cursor.sector, &num_sectors);
    if (error != 0) {
        return error;
    }
    if (file->cursor.sector == -1) {
        file->cursor.position = file->p_sfd->dir_entry.file_size;
        PFFILE_Cursor_Recalc(file);
        return 0x1C;
    }
    max_size = num_sectors << volume->bpb.log2_bytes_per_sector;
    if (size > max_size) {
        size = max_size;
    }
    if (file->cursor.position + size > file->p_sfd->dir_entry.file_size) {
        size = file->p_sfd->dir_entry.file_size - file->cursor.position;
        size -= size & (volume->bpb.bytes_per_sector - 1);
        if (size < volume->bpb.bytes_per_sector) {
            return 0;
        }
    }
    error = PFSEC_ReadData(volume, buffer, file->cursor.sector, file->cursor.offset_in_sector, size,
                           &success_size, 1);
    if (error != 0 && success_size == 0) {
        return error;
    }
    *size_read = success_size;
    PFFILE_Cursor_AdvanceToRead(file, success_size, file->cursor.sector);
    if (success_size != size - (size & (volume->bpb.bytes_per_sector - 1))) {
        return error;
    }
    return 0;
}

pf_s32 PFFILE_Cursor_ReadTailSector(PFFILE_FILE* file, pf_u8* buffer, pf_u32 size,
                                    pf_u32* size_read) {
    pf_s32 error;
    pf_u32 success_size;
    PF_VOLUME* volume;

    *size_read = 0;
    volume = file == PF_NULL ? PF_NULL : file->p_sfd->dir_entry.p_vol;
    if (size == 0) {
        return 0;
    }
    if (file->cursor.position + size > file->p_sfd->dir_entry.file_size) {
        size = file->p_sfd->dir_entry.file_size - file->cursor.position;
        if (size == 0) {
            return 0;
        }
    }
    if (file->cursor.sector == -1) {
        error = PFFAT_GetSectorSpecified(&file->p_sfd->ffd, file->cursor.file_sector_index, 0,
                                         &file->cursor.sector);
        if (error != 0) {
            return error;
        }
        if (file->cursor.sector == -1) {
            file->cursor.position = file->p_sfd->dir_entry.file_size;
            PFFILE_Cursor_Recalc(file);
            return 0x1C;
        }
        if (file->cursor.position + size > file->p_sfd->dir_entry.file_size) {
            file->cursor.position = file->p_sfd->dir_entry.file_size;
            PFFILE_Cursor_Recalc(file);
            return 0x1B;
        }
    }
    error = PFSEC_ReadData(volume, buffer, file->cursor.sector, file->cursor.offset_in_sector, size,
                           &success_size, 1);
    if (error != 0 && success_size == 0) {
        return error;
    }
    *size_read = success_size;
    PFFILE_Cursor_AdvanceToRead(file, success_size, file->cursor.sector);
    if (success_size != size) {
        return error;
    }
    return 0;
}

pf_s32 PFFILE_Cursor_Read(PFFILE_FILE* file, pf_u8* buffer, pf_u32 size, pf_u32* size_read) {
    pf_s32 error;
    pf_u32 part_size;
    PF_VOLUME* volume;

    file->p_sfd->ffd.p_hint = &file->hint;
    *size_read = 0;
    error = PFFILE_Cursor_ReadHeadSector(file, buffer, size, &part_size);
    *size_read += part_size;
    if (error != 0) {
        return error;
    }
    if (part_size >= size) {
        return 0;
    }
    size -= part_size;
    volume = file == PF_NULL ? PF_NULL : file->p_sfd->dir_entry.p_vol;
    while (size >= volume->bpb.bytes_per_sector) {
        error = PFFILE_Cursor_ReadBodySectors(file, buffer + *size_read, size, &part_size);
        *size_read += part_size;
        if (error != 0) {
            return error;
        }
        if (part_size == 0) {
            break;
        }
        size -= part_size;
    }
    error = PFFILE_Cursor_ReadTailSector(file, buffer + *size_read, size, &part_size);
    *size_read += part_size;
    if (error != 0) {
        return error;
    }
    return 0;
}

static inline void advance_write_cursor(PFFILE_FILE* file, pf_u32 size, pf_u32 sector) {
    PF_VOLUME* volume = file == PF_NULL ? PF_NULL : file->p_sfd->dir_entry.p_vol;
    pf_u32 position = file->cursor.offset_in_sector + size;
    pf_u32 next_sector = sector + (position >> volume->bpb.log2_bytes_per_sector);
    if (((volume->bpb.bytes_per_sector - 1) & position) != 0) { file->cursor.sector = next_sector; }
    else { file->cursor.sector = -1; }
    file->cursor.position += size;
    if (file->cursor.position > file->p_sfd->dir_entry.file_size) {
        file->p_sfd->dir_entry.file_size = file->cursor.position;
    }
    PFFILE_Cursor_Recalc(file);
    PFCLUSTER_UpdateLastAccessCluster(file, next_sector);
}

pf_s32 PFFILE_Cursor_WriteHeadSector(PFFILE_FILE* file, const pf_u8* buffer, pf_u32 size,
                                     pf_u32* size_written) {
    pf_s32 error;
    pf_u32 success_size;
    PF_VOLUME* volume;

    *size_written = 0;
    if (file->cursor.offset_in_sector == 0) {
        return 0;
    }
    volume = file == PF_NULL ? PF_NULL : file->p_sfd->dir_entry.p_vol;
    if (size > volume->bpb.bytes_per_sector - file->cursor.offset_in_sector) {
        size = volume->bpb.bytes_per_sector - file->cursor.offset_in_sector;
    }
    if (file->cursor.sector == -1) {
        error = PFFAT_GetSectorSpecified(&file->p_sfd->ffd, file->cursor.file_sector_index, 0,
                                         &file->cursor.sector);
        if (error != 0) {
            return error;
        }
        if (file->cursor.sector == -1) {
            file->cursor.position = file->p_sfd->dir_entry.file_size;
            PFFILE_Cursor_Recalc(file);
            return 0x1C;
        }
    }
    error = PFSEC_WriteData(volume, buffer, file->cursor.sector, file->cursor.offset_in_sector, size,
                            &success_size, 1);
    if (error != 0 && success_size == 0) {
        return error;
    }
    *size_written = success_size;
    advance_write_cursor(file, success_size, file->cursor.sector);
    if (success_size != size) {
        return error;
    }
    return 0;
}

pf_s32 PFFILE_Cursor_WriteBodySectors(PFFILE_FILE* file, const pf_u8* buffer, pf_u32 size,
                                      pf_u32* size_written) {
    pf_s32 error;
    pf_u32 num_sectors;
    pf_u32 success_size;
    PF_VOLUME* volume;

    *size_written = 0;
    num_sectors = 0;
    error = PFFAT_getContinuousSector(&file->p_sfd->ffd, file->cursor.file_sector_index, size,
                                      &file->cursor.sector, &num_sectors);
    if (error != 0) {
        return error;
    }
    if (file->cursor.sector == -1) {
        file->cursor.position = file->p_sfd->dir_entry.file_size;
        PFFILE_Cursor_Recalc(file);
        return 0x1C;
    }
    volume = file == PF_NULL ? PF_NULL : file->p_sfd->dir_entry.p_vol;
    if (size > (num_sectors << volume->bpb.log2_bytes_per_sector)) {
        size = num_sectors << volume->bpb.log2_bytes_per_sector;
    }
    error = PFSEC_WriteData(volume, buffer, file->cursor.sector, file->cursor.offset_in_sector,
                            size, &success_size, 1);
    if (error != 0 && success_size == 0) {
        return error;
    }
    *size_written = success_size;
    advance_write_cursor(file, success_size, file->cursor.sector);
    if (success_size != size - (size & (volume->bpb.bytes_per_sector - 1))) {
        return error;
    }
    return 0;
}

pf_s32 PFFILE_Cursor_WriteTailSector(PFFILE_FILE* file, const pf_u8* buffer, pf_u32 size,
                                     pf_u32* size_written) {
    pf_s32 error;
    pf_u32 success_size;
    PF_VOLUME* volume;

    *size_written = 0;
    if (size == 0) {
        return 0;
    }
    volume = file == PF_NULL ? PF_NULL : file->p_sfd->dir_entry.p_vol;
    if (size > volume->bpb.bytes_per_sector - file->cursor.offset_in_sector ||
        size > volume->bpb.bytes_per_sector) {
        return 0x1A;
    }
    if (file->cursor.sector == -1) {
        error = PFFAT_GetSectorSpecified(&file->p_sfd->ffd, file->cursor.file_sector_index, 0,
                                         &file->cursor.sector);
        if (error != 0) {
            return error;
        }
        if (file->cursor.sector == -1) {
            file->cursor.position = file->p_sfd->dir_entry.file_size;
            PFFILE_Cursor_Recalc(file);
            return 0x1C;
        }
    }
    error = PFSEC_WriteData(volume, buffer, file->cursor.sector, file->cursor.offset_in_sector, size,
                            &success_size, 1);
    if (error != 0 && success_size == 0) {
        return error;
    }
    *size_written = success_size;
    advance_write_cursor(file, success_size, file->cursor.sector);
    if (success_size != size) {
        return error;
    }
    return 0;
}

pf_s32 PFFILE_Cursor_Write(PFFILE_FILE* file, const pf_u8* buffer, pf_u32 size,
                           pf_u32* size_written) {
    pf_s32 error;
    pf_u32 part_size;
    pf_u32 num_clusters;
    pf_u32 append_size;
    pf_u32 append_needed;
    pf_u32 allocated_end;
    pf_u32 requested_end;
    PF_VOLUME* volume;
    PFFILE_VOLUME_DIRS* volume_dirs;

    file->p_sfd->ffd.p_hint = &file->hint;
    *size_written = 0;
    if (0xFFFFFFFF - file->cursor.position < size) {
        size = 0xFFFFFFFF - file->cursor.position;
        pf_vol_set.last_error = 0x25;
        volume_dirs = (PFFILE_VOLUME_DIRS*)file->p_sfd->ffd.p_vol;
        volume_dirs->last_error = 0x25;
        file->last_access_data.state.last_error = 0x25;
    }
    volume = file == PF_NULL ? PF_NULL : file->p_sfd->dir_entry.p_vol;
    error = PFFILE_Cursor_WriteHeadSector(file, buffer, size, &part_size);
    *size_written += part_size;
    if (error != 0) {
        return error;
    }
    if (part_size >= size) {
        return 0;
    }
    size -= part_size;
    error = PFFAT_CountAllocatedClusters(&file->p_sfd->ffd,
                                         file->cursor.position + size, &num_clusters);
    if (file == PF_NULL) {
        volume = PF_NULL;
    } else {
        volume = file->p_sfd->dir_entry.p_vol;
    }
    allocated_end = num_clusters << (volume->bpb.log2_bytes_per_sector +
                                     volume->bpb.log2_sectors_per_cluster);
    requested_end = file->cursor.position + size;
    if (allocated_end < requested_end) {
        append_needed = requested_end - allocated_end;
    } else {
        append_needed = 0;
    }
    append_size = 0;
    while (append_needed != 0 || size >= volume->bpb.bytes_per_sector) {
        if (append_needed != 0) {
            error = PFCLUSTER_AppendCluster(file, append_needed, &append_size);
            if (error != 0 && size == append_needed) {
                return error;
            }
            if (append_size == 0) {
                append_needed = 0;
            }
            append_needed -= append_size;
        }
        while (size >= append_needed + append_size &&
               size >= volume->bpb.bytes_per_sector) {
            error = PFFILE_Cursor_WriteBodySectors(file, buffer + *size_written, size,
                                                   &part_size);
            *size_written += part_size;
            if (error != 0) {
                return error;
            }
            if (part_size == 0) {
                return 0;
            }
            size -= part_size;
            if (size == 0) {
                break;
            }
        }
    }
    error = PFFILE_Cursor_WriteTailSector(file, buffer + *size_written, size, &part_size);
    *size_written += part_size;
    error = error & ((-error | error) >> 31);
    return error;
}

void PFFILE_Cursor_MoveToEnd(PFFILE_FILE* file) {
    file->cursor.position = file->p_sfd->dir_entry.file_size;
    PFFILE_Cursor_Recalc(file);
}

void PFFILE_Cursor_MoveToClusterEnd(PFFILE_FILE* file, pf_u32 size) {
    PF_VOLUME* volume = file == PF_NULL ? PF_NULL : file->p_sfd->dir_entry.p_vol;
    pf_u32 num_clusters;

    PFFAT_CountAllocatedClusters(&file->p_sfd->ffd, size, &num_clusters);
    if (num_clusters > (0xFFFFFFFF >> (volume->bpb.log2_bytes_per_sector +
                                       volume->bpb.log2_sectors_per_cluster))) {
        file->cursor.position = 0xFFFFFFFF;
        PFFILE_Cursor_Recalc(file);
    } else {
        file->cursor.position = num_clusters << (volume->bpb.log2_bytes_per_sector +
                                                 volume->bpb.log2_sectors_per_cluster);
        PFFILE_Cursor_Recalc(file);
    }
}

PFFILE_SFD* PFFILE_GetSFD(PFFILE_VOLUME_DIRS* volume_dirs, PF_DIR_ENT* entry) {
    pf_u32 first_free_index = 0;
    PFFILE_SFD* first_free_sfd = PF_NULL;
    pf_u32 index;

    for (index = 0; index < 5; index++) {
        if ((volume_dirs->sfds[index].stat & 1) == 0 ||
            ((volume_dirs->sfds[index].stat & 1) != 0 && (!volume_dirs->sfds[index].stat & 2) != 0)) {
            if (first_free_sfd == PF_NULL) {
                first_free_sfd = &volume_dirs->sfds[index];
                first_free_index = index;
            }
        } else if (entry->p_vol == volume_dirs->sfds[index].dir_entry.p_vol &&
                   entry->entry_sector == volume_dirs->sfds[index].dir_entry.entry_sector &&
                   entry->entry_offset == volume_dirs->sfds[index].dir_entry.entry_offset) {
            return &volume_dirs->sfds[index];
        }
    }

    if (first_free_sfd == PF_NULL) {
        return PF_NULL;
    }
    first_free_sfd->stat = 3;
    first_free_sfd->handler_count = 0;
    first_free_sfd->dir_entry = *entry;
    first_free_sfd->lock.mode = 0;
    first_free_sfd->lock.count = 0;
    first_free_sfd->lock.wcount = 0;
    first_free_sfd->lock.owner = PF_NULL;
    first_free_sfd->lock.resource = 0;
    PFFAT_InitFFD(&first_free_sfd->ffd, PF_NULL, entry->p_vol,
                  &first_free_sfd->dir_entry.start_cluster);
    if ((volume_dirs->cluster_link.flag & 1) != 0) {
        pf_u32* link_buffer = volume_dirs->cluster_link.buffer +
                              first_free_index * volume_dirs->cluster_link.link_max;

        first_free_sfd->ffd.cluster_link.buffer = link_buffer;
        pf_memset(link_buffer, 0, volume_dirs->cluster_link.link_max << 2);
        first_free_sfd->ffd.cluster_link.max_count = volume_dirs->cluster_link.link_max;
        first_free_sfd->ffd.cluster_link.interval = volume_dirs->cluster_link.interval;
        first_free_sfd->ffd.cluster_link.interval_offset = 0;
        first_free_sfd->ffd.cluster_link.position = 0;
        first_free_sfd->ffd.cluster_link.save_index = 0;
        if (entry->file_size != 0 && first_free_sfd->ffd.cluster_link.max_count != 0) {
            *first_free_sfd->ffd.cluster_link.buffer = entry->start_cluster;
            first_free_sfd->ffd.cluster_link.position++;
        }
    }
    return first_free_sfd;
}

pf_s32 PFFILE_createEmptyFile(PF_VOLUME* volume, PF_DIR_ENT* entry, PF_STR* filename) {
    PF_DIR_ENT parent_entry = *entry;
    PFFILE_FFD ffd;
    PFFILE_FAT_HINT hint;
    pf_u32 previous_sectors[2];
    pf_u32* previous_sector;
    pf_u32 success_size;
    pf_u32 entry_position;
    pf_s32 num_chars;
    pf_u8 num_entries;
    pf_u8 checksum;
    pf_u32 ordinal;
    pf_u32 sector;
    pf_s32 error;
    pf_u8 short_entry_buffer[13];
    pf_u8 long_entry_buffer[32];

    num_chars = PFSTR_StrNumChar(filename, 1) & 0xFFFF;
    if (num_chars + parent_entry.path_len > 0x103) { return 1; }
    if (num_chars > 0xFF) { return 1; }
    PFFAT_InitFFD(&ffd, &hint, parent_entry.p_vol, &parent_entry.start_cluster);
    if (((PFFILE_VOLUME_DIRS*)volume)->num_opened_files >= 5) {
        return 0x15;
    }
    error = PFPATH_parseShortName(entry->short_name, filename);
    if (error != 0 && entry->short_name[0] == 0) {
        return 1;
    }
    if (error != 0) {
        error = PFENT_AdjustSFN(&parent_entry, entry->short_name);
        if (error != 0) {
            return error;
        }
        if (PFSTR_GetCodeMode(filename) == 1) {
            PFPATH_transformInUnicode(entry, PFSTR_GetStrPos(filename, 1));
        } else {
            pf_w_strcpy(entry->long_name, (const pf_u16*)PFSTR_GetStrPos(filename, 1));
        }
    } else {
        entry->long_name[0] = 0;
    }
    if (volume->bpb.fat_type == FAT_32) { entry->start_cluster = 1; }
    else { entry->start_cluster = 0; }
    entry->file_size = 0;
    entry->p_vol = volume;
    entry->small_letter_flag = 0;
    entry->attr = 0x20;
    entry->create_time_ms = PFENT_getcurrentDateTimeForEnt(&entry->create_date,
                                                           &entry->create_time);
    entry->access_date = entry->create_date;
    entry->modify_time = entry->create_time;
    entry->modify_date = entry->create_date;
    if (entry->long_name[0] != 0 && (entry->small_letter_flag & 0x18) == 0) {
        num_entries = num_chars / 13 + (num_chars % 13 != 0);
        error = PFENT_allocateEntryPos(entry, (num_entries + 1) & 0xFF, &ffd,
                                       previous_sectors, filename, &entry_position);
        if (error != 0) {
            return error;
        }
        if ((pf_vol_set.file_settings & 2) == 2) {
            PFPATH_AdjustExtShortName(entry->short_name, entry_position);
        }
        entry->num_entry_LFNs = num_entries;
        sector = entry->entry_sector;
        checksum = PFENT_CalcCheckSum(entry);
        previous_sector = previous_sectors;
        for (ordinal = num_entries; ordinal >= 1; ordinal--) {
            PFENT_storeLFNEntryFieldsToBuf(long_entry_buffer, entry, ordinal,
                                           checksum, ordinal == num_entries);
            error = PFSEC_WriteData(volume, long_entry_buffer, sector, entry->entry_offset,
                                    0x20, &success_size, 0);
            if (error != 0) {
                return error;
            }
            if (success_size != 0x20) {
                return 0x11;
            }
            entry->entry_offset += 0x20;
            if (entry->entry_offset >= volume->bpb.bytes_per_sector) {
                entry->entry_offset = 0;
                sector = *previous_sector++;
            }
        }
        entry->entry_sector = sector;
    } else {
        error = PFENT_allocateEntry(entry, 1, &ffd, previous_sectors, filename);
        if (error != 0) {
            return error;
        }
    }
    if (entry->start_cluster == 1) {
        entry->start_cluster = 0;
    }
    return PFENT_updateEntry(entry, 1);
}

static inline pf_u32 file_is_open(PF_DIR_ENT* entry) {
    pf_s32 index;
    for (index = 0; index < 5; index++) {
        PFFILE_SFD* sfd = &((PFFILE_VOLUME_DIRS*)entry->p_vol)->sfds[index];
        if ((sfd->stat & 1) != 0 && (sfd->stat & 2) != 0 &&
            entry->p_vol == sfd->dir_entry.p_vol && entry->entry_sector == sfd->dir_entry.entry_sector &&
            entry->entry_offset == sfd->dir_entry.entry_offset) { return 1; }
    }
    return 0;
}

pf_s32 PFFILE_p_remove(PF_VOLUME* volume, PF_STR* path) {
    PF_STR directory;
    PF_STR filename;
    PF_DIR_ENT entry;
    PFFILE_ENT_ITER iter;
    pf_s32 error;
    PFFILE_FAT_HINT hint;
    pf_u32 start_cluster;

    error = PFPATH_SplitPath(path, &directory, &filename);
    if (error != 0) {
        return error;
    }
    error = PFENT_ITER_GetEntryOfPath(&iter, &entry, volume, path, 0);
    if (error != 0) {
        return error;
    }
    hint = *(PFFILE_FAT_HINT*)iter.ffd.p_hint;
    if ((entry.attr & 0x19) != 0) {
        return 0xB;
    }
    if (file_is_open(&entry) != 0) { return 0x13; }
    iter.ffd.p_hint = (PF_FAT_HINT*)&hint;
    start_cluster = entry.start_cluster;
    error = PFENT_RemoveEntry(&entry, &iter);
    if (error != 0) {
        return error;
    }
    return PFFAT_FreeChain(&iter.ffd, start_cluster, 0xFFFFFFFF, entry.file_size);
}

static PFFILE_FILE* PFFILE_GetFreeUFD(PF_VOLUME* volume);

pf_s32 PFFILE_p_fopen(PF_VOLUME* volume, PF_STR* path, pf_u32 open_mode,
                      PFFILE_FILE** result) {
    PF_STR filename;
    PF_STR directory;
    PF_DIR_ENT entry;
    PFFILE_ENT_ITER iter;
    PFFILE_FFD ffd;
    PFFILE_FAT_HINT hint;
    PFFILE_SFD* sfd;
    PFFILE_FILE* file;
    pf_s8 normalized_filename[0x200];
    pf_s32 num_chars;
    pf_u16 access_time;
    pf_s32 error;

    *result = PF_NULL;
    error = PFPATH_SplitPath(path, &directory, &filename);
    if (error != 0) {
        return 1;
    }
    error = PFENT_ITER_GetEntryOfPath(&iter, &entry, volume, path, 1);
    if (error != 0) {
        return error;
    }
    if ((entry.attr & 0x10) == 0) {
        return 1;
    }
    if (PFSTR_GetCodeMode(&filename) == 2) {
        num_chars = PFSTR_StrNumChar(&filename, 1) & 0xFFFF;
        if (num_chars > 0xFF) {
            return 1;
        }
        PFPATH_transformFromUnicodeToNormal(normalized_filename,
                                             (const pf_u16*)PFSTR_GetStrPos(&filename, 1));
    }
    PFSTR_SetLocalStr(&filename, normalized_filename);
    if ((open_mode & 2) != 0) {
        PFFAT_InitFFD(&ffd, &hint, entry.p_vol, &entry.start_cluster);
        error = PFENT_findEntry(&ffd, &entry, 0, &filename, 0x7F, 0);
        if (error != 0) {
            return 3;
        }
        if ((open_mode & 8) != 0 && (entry.attr & 1) != 0) {
            return 0xA;
        }
        if ((entry.attr & 0x10) != 0) {
            return 0x17;
        }
        PFENT_getcurrentDateTimeForEnt(&entry.access_date, &access_time);
    } else {
        error = PFFILE_createEmptyFile(volume, &entry, &filename);
        if (error == 8) {
            if ((open_mode & 0x10) != 0) {
                return 8;
            }
            if ((open_mode & 1) != 0) {
                if (file_is_open(&entry) != 0) { return 8; }
            }
            if ((entry.attr & 1) != 0 &&
                ((open_mode & 1) != 0 || (open_mode & 4) != 0 || (open_mode & 8) != 0)) {
                return 0xA;
            }
            if ((entry.attr & 0x10) != 0) {
                return 0x17;
            }
            if ((open_mode & 1) != 0) {
                if (entry.start_cluster >= 2 && entry.start_cluster != 0xFFFFFFFF &&
                    entry.file_size != 0) {
                    PFFAT_FreeChain(&iter.ffd, entry.start_cluster, 0xFFFFFFFF, entry.file_size);
                }
                entry.start_cluster = 0;
                entry.file_size = 0;
                PFENT_getcurrentDateTimeForEnt(&entry.modify_date, &entry.modify_time);
                entry.access_date = entry.modify_date;
            } else {
                PFENT_getcurrentDateTimeForEnt(&entry.access_date, &access_time);
            }
        } else if (error != 0) {
            return error;
        }
    }
    volume = entry.p_vol;
    sfd = PFFILE_GetSFD((PFFILE_VOLUME_DIRS*)volume, &entry);
    if (sfd == PF_NULL) {
        return 0x15;
    }
    file = PFFILE_GetFreeUFD(volume);
    if (file == PF_NULL) {
        return 0x16;
    }
    file->p_sfd = sfd;
    file->stat = 1;
    file->open_mode = open_mode;
    file->last_access_data.state.last_error = 0;
    file->lock_count = 0;
    PFFAT_InitHint(&file->hint);
    file->cursor.sector = 0xFFFFFFFF;
    file->cursor.position = 0;
    PFFILE_Cursor_Recalc(file);
    if ((open_mode & 1) != 0) {
        file->p_sfd->stat |= 4;
    }
    if ((file->open_mode & 4) != 0) {
        file->cursor.position = file->p_sfd->dir_entry.file_size;
        PFFILE_Cursor_Recalc(file);
    }
    sfd->handler_count++;
    *result = file;
    return 0;
}

pf_s32 PFFILE_p_fread(PF_VOLUME* volume, pf_u8* buffer, pf_u32 size, pf_u32 count,
                      PFFILE_FILE* file, pf_u32* count_read) NO_INLINE {
    pf_u32 bytes_read = 0;
    pf_s32 error;

    *count_read = 0;
    if ((file->open_mode & 8) == 0 &&
        ((file->open_mode & 1) != 0 || (file->open_mode & 4) != 0)) {
        return 0xA;
    }
    if ((file->p_sfd->lock.mode & 3) != 0 && file->lock_count == 0) {
        return 0x19;
    }
    if (file->cursor.position >= file->p_sfd->dir_entry.file_size) {
        return 0x1C;
    }
    error = PFFILE_Cursor_Read(file, buffer, size * count, &bytes_read);
    *count_read = bytes_read / size;
    error &= (-error | error) >> 31;
    return error;
}

pf_s32 PFFILE_p_fwrite(PF_VOLUME* volume, const pf_u8* buffer, pf_u32 size, pf_u32 count,
                       PFFILE_FILE* file, pf_u32* count_written) {
    PF_CACHE_PAGE* page;
    pf_u32 allocation_option;
    pf_u32 bytes_written = 0;
    pf_u32 remaining;
    pf_s32 error;

    *count_written = 0;
    if ((file->open_mode & 8) == 0 && (file->open_mode & 2) != 0) {
        return 0xA;
    }
    if ((file->p_sfd->lock.mode & 3) != 0 &&
        ((file->p_sfd->lock.mode & 1) != 0 ||
         ((file->p_sfd->lock.mode & 2) != 0 && file->lock_count == 0))) {
        return 0x19;
    }
    if ((file->open_mode & 4) != 0) {
        file->cursor.position = file->p_sfd->dir_entry.file_size;
        PFFILE_Cursor_Recalc(file);
    }
    if (file->cursor.position > file->p_sfd->dir_entry.file_size) {
        remaining = file->cursor.position - file->p_sfd->dir_entry.file_size;
        file->cursor.position = file->p_sfd->dir_entry.file_size;
        file->cursor.file_sector_index = file->cursor.position >> volume->bpb.log2_bytes_per_sector;
        file->cursor.offset_in_sector = file->cursor.position & (volume->bpb.bytes_per_sector - 1);
        error = PFCACHE_AllocateDataPage(volume, 0xFFFFFFFF, &page, &allocation_option);
        if (error != 0) {
            return error;
        }
        pf_memset(page->p_buf, 0, volume->bpb.bytes_per_sector);
        while (remaining != 0) {
            if (remaining > volume->bpb.bytes_per_sector) {
                error = PFFILE_Cursor_Write(file, page->p_buf, volume->bpb.bytes_per_sector, &bytes_written);
                if (error != 0) { return error; }
            } else {
                error = PFFILE_Cursor_Write(file, page->p_buf, remaining, &bytes_written);
                if (error != 0) { return error; }
                break;
            }
            remaining -= volume->bpb.bytes_per_sector;
        }
        PFCACHE_FreeDataPage(volume, page);
    }
    error = PFFILE_Cursor_Write(file, buffer, size * count, &bytes_written);
    *count_written = bytes_written / size;
    if (error != 0) { return error; }
    return 0;
}

pf_s32 PFFILE_p_fappend(PFFILE_FILE* file, pf_u32 size, pf_u32* size_appended) {
    pf_u32 max_size;
    pf_u32 appended_size;
    pf_s32 error;

    *size_appended = 0;
    if ((file->open_mode & 8) == 0 && (file->open_mode & 2) != 0) {
        return 0xA;
    }
    if ((file->p_sfd->lock.mode & 3) != 0 &&
        ((file->p_sfd->lock.mode & 1) != 0 ||
         ((file->p_sfd->lock.mode & 2) != 0 && file->lock_count == 0))) {
        return 0x19;
    }
    file->p_sfd->ffd.p_hint = &file->hint;
    max_size = 0xFFFFFFFF - file->cursor.position;
    if (max_size < size) {
        size = max_size;
        pf_vol_set.last_error = 0x25;
        ((PFFILE_VOLUME_DIRS*)file->p_sfd->ffd.p_vol)->last_error = 0x25;
        file->last_access_data.state.last_error = 0x25;
    }
    error = PFCLUSTER_AppendCluster(file, size, &appended_size);
    *size_appended = appended_size;
    if (error != 0) {
        return error;
    }
    return 0;
}

pf_s32 PFFILE_p_finfo(PFFILE_FILE* file, PF_INFO* info) {
    PF_VOLUME* volume;
    pf_u32 cluster_size;
    pf_u32 file_size_remainder;
    pf_u32 file_size;
    pf_s32 error;

    file->p_sfd->ffd.p_hint = &file->hint;
    volume = file == PF_NULL ? PF_NULL : file->p_sfd->dir_entry.p_vol;
    info->file_size = file->p_sfd->dir_entry.file_size;
    info->io_pointer = file->cursor.position;
    cluster_size = volume->bpb.bytes_per_sector << volume->bpb.log2_sectors_per_cluster;
    if (file->p_sfd->dir_entry.start_cluster != 0) {
        error = PFCLUSTER_GetAppendSize(file, &info->allocated_size);
        if (error != 0) {
            return error;
        }
        file_size = file->p_sfd->dir_entry.file_size;
        file_size_remainder = file_size % cluster_size;
        info->empty_size = info->allocated_size +
                           (file_size_remainder != 0
                                ? cluster_size - file_size_remainder
                                : 0);
    } else {
        info->allocated_size = 0;
        info->empty_size = 0;
    }
    info->lock_mode = file->p_sfd->lock.mode & 3;
    info->lock_owner = file->p_sfd->lock.owner;
    info->lock_count = file->lock_count;
    info->lock_tcount = file->p_sfd->lock.count;
    return 0;
}

pf_s32 PFFILE_p_combine(PF_VOLUME* volume, PF_STR* first_path, PF_STR* second_path) {
    PFFILE_ENT_ITER first_iter;
    PFFILE_ENT_ITER second_iter;
    PFFILE_ENT_ITER second_iter_copy;
    PF_DIR_ENT first_entry;
    PF_DIR_ENT second_entry;
    PFFILE_FAT_HINT first_hint;
    PFFILE_FAT_HINT second_hint;
    pf_s32 error;

    error = PFENT_ITER_GetEntryOfPath(&first_iter, &first_entry, volume, first_path, 0);
    if (error != 0) {
        return error;
    }
    error = PFENT_ITER_GetEntryOfPath(&second_iter, &second_entry, volume, second_path, 0);
    if (error != 0) {
        return error;
    }
    if ((first_entry.attr & 0x10) != 0 || (second_entry.attr & 0x10) != 0) {
        return 0x17;
    }
    if ((first_entry.attr & 1) != 0 || (second_entry.attr & 1) != 0) {
        return 0x18;
    }
    if (file_is_open(&first_entry) != 0 || file_is_open(&second_entry) != 0) { return 0x13; }
    if (first_entry.entry_sector == second_entry.entry_sector &&
        first_entry.entry_offset == second_entry.entry_offset) {
        return 0xA;
    }
    if (0xFFFFFFFF - first_entry.file_size < second_entry.file_size) {
        return 0x25;
    }
    PFFAT_InitHint(&first_hint);
    PFFAT_InitFFD(&first_iter.ffd, &first_hint, volume, &first_entry.start_cluster);
    PFFAT_InitHint(&second_hint);
    PFFAT_InitFFD(&second_iter.ffd, &second_hint, volume, &second_entry.start_cluster);
    pf_memcpy(&second_iter_copy, &second_iter, sizeof(second_iter_copy));
    error = PFENT_RemoveEntry(&second_entry, &second_iter);
    if (error != 0) {
        return error;
    }
    error = PFCLUSTER_CombineFiles(&first_iter, &second_iter_copy, &first_entry, &second_entry);
    if (error != 0) {
        return error;
    }
    PFENT_getcurrentDateTimeForEnt(&first_entry.modify_date, &first_entry.modify_time);
    first_entry.access_date = first_entry.modify_date;
    error = PFENT_updateEntry(&first_entry, 1);
    return error & (-error | error) >> 31;
}

pf_s32 PFFILE_p_divide(PF_VOLUME* volume, PF_STR* source_path, PF_STR* destination_path,
                       pf_u32 split_size) {
    PF_STR destination_filename;
    PF_STR destination_directory;
    PF_DIR_ENT source_entry;
    PF_DIR_ENT destination_entry;
    PF_DIR_ENT source_entry_copy;
    PFFILE_ENT_ITER source_iter;
    PFFILE_ENT_ITER destination_iter;
    PFFILE_FAT_HINT source_hint;
    PFFILE_FAT_HINT destination_hint;
    pf_s8 normalized_filename[0x200];
    pf_u32 original_size;
    pf_u32 original_start_cluster;
    pf_s32 error;
    pf_s32 divide_error;

    error = PFENT_ITER_GetEntryOfPath(&source_iter, &source_entry, volume, source_path, 0);
    if (error != 0) {
        return error;
    }
    if ((source_entry.attr & 0x10) != 0) {
        return 0x17;
    }
    if ((source_entry.attr & 1) != 0) {
        return 0x18;
    }
    if (file_is_open(&source_entry) != 0) { return 0x13; }
    if (source_entry.file_size == 0) {
        return 0xA;
    }
    if (source_entry.file_size < split_size) {
        return 0xA;
    }
    error = PFPATH_SplitPath(destination_path, &destination_directory, &destination_filename);
    if (error != 0) {
        return 1;
    }
    if (PFSTR_GetCodeMode(&destination_filename) == 2) {
        if ((pf_s32)(PFSTR_StrNumChar(&destination_filename, 1) & 0xFFFF) > 0xFF) {
            return 1;
        }
        PFPATH_transformFromUnicodeToNormal(
            normalized_filename, (const pf_u16*)PFSTR_GetStrPos(&destination_filename, 1));
    }
    PFSTR_SetLocalStr(&destination_filename, normalized_filename);
    error = PFENT_ITER_GetEntryOfPath(&destination_iter, &destination_entry, volume,
                                      destination_path, 1);
    if (error != 0) {
        return error;
    }
    if ((destination_entry.attr & 0x10) == 0) {
        return 1;
    }
    error = PFFILE_createEmptyFile(volume, &destination_entry, &destination_filename);
    if (error != 0) {
        return error;
    }
    PFFAT_InitHint(&source_hint);
    PFFAT_InitFFD(&source_iter.ffd, &source_hint, volume, &source_entry.start_cluster);
    PFFAT_InitHint(&destination_hint);
    PFFAT_InitFFD(&destination_iter.ffd, &destination_hint, volume, &destination_entry.start_cluster);
    pf_memcpy(&source_entry_copy, &source_entry, sizeof(source_entry_copy));
    original_size = source_entry.file_size;
    original_start_cluster = source_entry.start_cluster;
    PFENT_getcurrentDateTimeForEnt(&source_entry.modify_date, &source_entry.modify_time);
    source_entry.access_date = source_entry.modify_date;
    if (split_size == 0) {
        source_entry.start_cluster = 0;
    }
    source_entry.file_size = split_size;
    error = PFENT_updateEntry(&source_entry, 1);
    if (error != 0) { return error; }
    if ((((PFFILE_VOLUME_DIRS*)volume)->cache_control & 4) != 0) {
        error = PFCACHE_FlushDataCacheSpecific(volume, 0);
        if (error != 0) { return error; }
    }
    error = PFCLUSTER_DivideFile(&source_iter, &destination_iter, &source_entry_copy,
                                 &destination_entry, split_size);
    divide_error = error;
    if (error != 0) {
        PFCACHE_FlushFATCache(volume);
        source_entry.file_size = original_size;
        source_entry.start_cluster = original_start_cluster;
        PFENT_updateEntry(&source_entry, 1);
        PFENT_ITER_GetEntryOfPath(&destination_iter, &destination_entry, volume,
                                  destination_path, 0);
        PFENT_RemoveEntry(&destination_entry, &destination_iter);
        return divide_error;
    }
    destination_entry.modify_date = source_entry.modify_date;
    destination_entry.modify_time = source_entry.modify_time;
    destination_entry.access_date = source_entry.access_date;
    destination_entry.attr = source_entry.attr;
    error = PFENT_updateEntry(&destination_entry, 1);
    return error & (-error | error) >> 31;
}

pf_s32 PFFILE_p_cinsert(PF_VOLUME* volume, PF_STR* path, pf_u32 cluster_index,
                        pf_u32 count, pf_u32 mode) {
    PFFILE_ENT_ITER iter;
    PF_DIR_ENT entry;
    PFFILE_FAT_HINT hint;
    pf_u32 cluster_bytes;
    pf_u32 required_clusters;
    pf_u32 remainder;
    pf_s32 error;

    error = PFENT_ITER_GetEntryOfPath(&iter, &entry, volume, path, 0);
    if (error != 0) {
        return error;
    }
    if ((entry.attr & 0x10) != 0) {
        return 0x17;
    }
    if ((entry.attr & 1) != 0) {
        return 0x18;
    }
    if (PFFILE_IsOpened(&entry)) {
        return 0x13;
    }
    cluster_bytes = volume->bpb.bytes_per_sector << volume->bpb.log2_sectors_per_cluster;
    required_clusters = entry.file_size / cluster_bytes;
    remainder = entry.file_size - required_clusters * cluster_bytes;
    if (remainder != 0) {
        required_clusters++;
    }
    if (required_clusters < cluster_index) {
        return 10;
    }
    PFFAT_InitHint(&hint);
    PFFAT_InitFFD(&iter.ffd, &hint, volume, &entry.start_cluster);
    error = PFCLUSTER_InsertCluster(&iter, &entry, cluster_index, count, mode);
    if (error != 0) {
        return error;
    }
    PFENT_getcurrentDateTimeForEnt(&entry.modify_date, &entry.modify_time);
    entry.access_date = entry.modify_date;
    error = PFENT_updateEntry(&entry, 1);
    return error & (-error | error) >> 31;
}

pf_s32 PFFILE_p_cdelete(PF_VOLUME* volume, PF_STR* path, pf_u32 cluster_index,
                        pf_u32 count, pf_u32 mode) {
    PFFILE_ENT_ITER iter;
    PF_DIR_ENT entry;
    PFFILE_FAT_HINT hint;
    pf_u32 cluster_bytes;
    pf_u32 required_clusters;
    pf_u32 remainder;
    pf_s32 error;

    error = PFENT_ITER_GetEntryOfPath(&iter, &entry, volume, path, 0);
    if (error != 0) {
        return error;
    }
    if ((entry.attr & 0x10) != 0) {
        return 0x17;
    }
    if ((entry.attr & 1) != 0) {
        return 0x18;
    }
    if (PFFILE_IsOpened(&entry)) {
        return 0x13;
    }
    if (entry.file_size == 0) {
        return 10;
    }
    cluster_bytes = volume->bpb.bytes_per_sector << volume->bpb.log2_sectors_per_cluster;
    required_clusters = entry.file_size / cluster_bytes;
    remainder = entry.file_size - required_clusters * cluster_bytes;
    if (remainder != 0) {
        required_clusters++;
    }
    if (required_clusters <= cluster_index) {
        return 10;
    }
    PFFAT_InitHint(&hint);
    PFFAT_InitFFD(&iter.ffd, &hint, volume, &entry.start_cluster);
    error = PFCLUSTER_DeleteCluster(&iter, &entry, cluster_index, count, mode);
    return error & (-error | error) >> 31;
}

pf_s32 PFFILE_p_flock(PFFILE_FILE* file, pf_u32 mode) {
    if ((mode & 3) != 0) {
        if ((file->p_sfd->lock.mode & 3) != 0 && (mode & 8) != 0) {
            if (((mode & 1) != 0 && (file->p_sfd->lock.mode & 2) != 0) ||
                ((mode & 2) != 0 && (file->p_sfd->lock.mode & 1) != 0) ||
                (file->p_sfd->lock.owner != 0 && file->p_sfd->lock.owner != (PF_FILE*)file)) {
                return 0x27;
            }
        }
        if ((mode & 1) != 0) {
            if (file->p_sfd->lock.count == 0 || (file->p_sfd->lock.mode & 2) != 0) {
                file->p_sfd->lock.wcount++;
                PF_LockFile((PF_FILE*)file, 0);
                file->p_sfd->lock.wcount--;
                file->p_sfd->lock.mode = 1;
                file->p_sfd->lock.owner = 0;
            }
        } else if (file->p_sfd->lock.owner != (PF_FILE*)file) {
            file->p_sfd->lock.wcount++;
            PF_LockFile((PF_FILE*)file, (PF_FILE*)file);
            file->p_sfd->lock.wcount--;
            file->p_sfd->lock.mode = 2;
            file->p_sfd->lock.owner = (PF_FILE*)file;
        }
        file->p_sfd->lock.count++;
        file->lock_count++;
        goto complete;
    }
    if (file->lock_count == 0 || file->p_sfd->lock.count == 0) {
        return 0x27;
    }
    if ((file->p_sfd->lock.mode & 2) != 0 && file->p_sfd->lock.owner != (PF_FILE*)file) {
        return 0x27;
    }
    file->lock_count--;
    file->p_sfd->lock.count--;
    if (file->p_sfd->lock.count == 0) {
        PF_UnLockFile((PF_FILE*)file);
        if ((file->p_sfd->lock.mode & 2) != 0) { file->p_sfd->lock.owner = 0; }
        file->p_sfd->lock.mode &= ~3;
    }
complete:
    return 0;
}

static PFFILE_FILE* PFFILE_GetFreeUFD(PF_VOLUME* volume) {
    PFFILE_VOLUME_DIRS* volume_dirs = (PFFILE_VOLUME_DIRS*)volume;
    pf_u32 index;

    for (index = 0; index < 5; index++) {
        if ((volume_dirs->ufds[index].stat & 1) == 0) {
            return &volume_dirs->ufds[index];
        }
    }
    return PF_NULL;
}

pf_s32 PFFILE_FsexecOpenFile(PF_DIR_ENT* entry, PFFILE_ENT_ITER* iter,
                             pf_u32 mode, PF_DTA* data) {
    PF_VOLUME* volume = entry->p_vol;
    PFFILE_SFD* sfd;
    PFFILE_FILE* file;
    pf_u16 access_time;
    pf_u32 start_cluster;

    data->p_file = PF_NULL;
    if ((entry->attr & 0x10) != 0) {
        return 0x17;
    }
    if ((entry->attr & 1) != 0 &&
        ((mode & 1) != 0 || (mode & 4) != 0 || (mode & 8) != 0)) {
        return 10;
    }
    if ((mode & 1) != 0 && PFFILE_IsOpened(entry)) {
        return 8;
    }
    if ((mode & 1) != 0) {
        start_cluster = entry->start_cluster;
        if (start_cluster >= 2 && start_cluster != 0xFFFFFFFF && entry->file_size != 0) {
            PFFAT_FreeChain(&iter->ffd, start_cluster, -1, entry->file_size);
        }
        entry->start_cluster = 0;
        entry->file_size = 0;
        PFENT_getcurrentDateTimeForEnt(&entry->modify_date, &entry->modify_time);
        entry->access_date = entry->modify_date;
    } else {
        PFENT_getcurrentDateTimeForEnt(&entry->access_date, &access_time);
    }
    sfd = PFFILE_GetSFD((PFFILE_VOLUME_DIRS*)volume, entry);
    if (sfd == PF_NULL) {
        return 0x15;
    }
    file = PFFILE_GetFreeUFD(volume);
    if (file == PF_NULL) {
        return 0x16;
    }
    file->p_sfd = sfd;
    file->stat = 1;
    file->open_mode = mode;
    file->last_access_data.state.last_error = 0;
    file->lock_count = 0;
    PFFAT_InitHint(&file->hint);
    file->cursor.sector = 0xFFFFFFFF;
    file->cursor.position = 0;
    PFFILE_Cursor_Recalc(file);
    if ((mode & 1) != 0) {
        file->p_sfd->stat |= 4;
    }
    if ((file->open_mode & 4) != 0) {
        PFFILE_Cursor_MoveToEnd(file);
    }
    sfd->handler_count++;
    data->p_file = (PF_FILE*)file;
    return 0;
}

pf_bool PFFILE_IsOpened(PF_DIR_ENT* entry) {
    PFFILE_VOLUME_DIRS* volume_dirs = (PFFILE_VOLUME_DIRS*)entry->p_vol;
    pf_u32 index;

    for (index = 0; index < 5; index++) {
        PFFILE_SFD* sfd = &volume_dirs->sfds[index];

        if ((sfd->stat & 1) != 0 && (sfd->stat & 2) != 0 &&
            entry->p_vol == sfd->dir_entry.p_vol && entry->entry_sector == sfd->dir_entry.entry_sector &&
            entry->entry_offset == sfd->dir_entry.entry_offset) {
            return PF_TRUE;
        }
    }
    return PF_FALSE;
}

void PFFILE_FinalizeAllFiles(PF_VOLUME* volume) {
    PFFILE_VOLUME_DIRS* volume_dirs = (PFFILE_VOLUME_DIRS*)volume;
    pf_u16 index;

    for (index = 0; index < 5; index++) {
        PFFILE_SFD* sfd = &volume_dirs->sfds[index];

        sfd->stat = 0;
        PFFAT_FinalizeFFD(&sfd->ffd);
    }
    for (index = 0; index < 5; index++) {
        volume_dirs->ufds[index].stat &= ~1U;
    }
    volume_dirs->num_opened_files = 0;
}

pf_s32 PFFILE_remove(PF_STR* path) {
    PF_VOLUME* volume;
    pf_s32 error;

    volume = PFPATH_GetVolumeFromPath(path);
    error = PFVOL_CheckForWrite(volume);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
        return error;
    }
    ((PFFILE_VOLUME_DIRS*)volume)->cache_signature = 0;
    error = PFFILE_p_remove(volume, path);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
        return error;
    }
    error = PFCACHE_FlushFATCache(volume);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
    }
    return error;
}

pf_s32 PFFILE_ferror(PFFILE_FILE* file) {
    PF_VOLUME* volume = file == PF_NULL ? PF_NULL : file->p_sfd->dir_entry.p_vol;
    pf_s32 error;

    error = PFVOL_CheckForRead(volume);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
        return -1;
    }
    if ((file->p_sfd->stat & 1) == 0 || (file->p_sfd->stat & 2) == 0) {
        pf_vol_set.last_error = 0x26;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = 0x26;
        return -1;
    }
    return file->last_access_data.state.last_error;
}

pf_s32 PFFILE_fopen(PF_STR* path, pf_s32 mode, PFFILE_FILE** result) {
    PF_VOLUME* volume;
    pf_s32 error;

    *result = PF_NULL;
    volume = PFPATH_GetVolumeFromPath(path);
    error = PFVOL_CheckForWrite(volume);
    if (error != 0 && (error != 0x0B || mode != 2)) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
        return error;
    }
    error = PFFILE_p_fopen(volume, path, mode, result);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
    } else {
        ((PFFILE_VOLUME_DIRS*)volume)->num_opened_files++;
    }
    return error;
}

pf_s32 PFFILE_fclose(PFFILE_FILE* file) {
    pf_s32 close_error = 0;
    PF_VOLUME* volume = file == PF_NULL ? PF_NULL : file->p_sfd->dir_entry.p_vol;
    PFFILE_VOLUME_DIRS* volume_dirs;
    pf_s32 error;

    error = PFVOL_CheckForWrite(volume);
    if (error != 0 && (error != 0x0B || (pf_s32)file->open_mode != 2)) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
        return error;
    }
    volume_dirs = (PFFILE_VOLUME_DIRS*)volume;
    if ((file->p_sfd->stat & 1) == 0 || (file->p_sfd->stat & 2) == 0) {
        pf_vol_set.last_error = 10;
        volume_dirs->last_error = 10;
        return 10;
    }
    volume_dirs->cache_signature = file;
    if (((pf_s32)file->p_sfd->handler_count - 1) <= 0 &&
        (file->p_sfd->dir_entry.attr & 0x19) == 0 &&
        (error & 0x0B) == 0 &&
        ((file->p_sfd->stat & 4) != 0 || (volume_dirs->file_config & 1) != 1)) {
        close_error = PFENT_updateEntry(&file->p_sfd->dir_entry, 1);
    }
    if (file->lock_count != 0) {
        if ((file->p_sfd->lock.mode & 1) != 0) {
            file->p_sfd->lock.count -= file->lock_count;
            file->lock_count = 0;
            if (file->p_sfd->lock.count == 0) {
                PF_UnLockFile((PF_FILE*)file);
            }
            file->p_sfd->lock.mode &= ~3;
        } else if (file->p_sfd->lock.owner != (PF_FILE*)file) {
            close_error = 0x19;
        } else {
            file->p_sfd->lock.count = 0;
            file->lock_count = 0;
            file->p_sfd->lock.owner = 0;
            PF_UnLockFile((PF_FILE*)file);
            file->p_sfd->lock.mode &= ~3;
        }
    }
    if (close_error != 0) {
        pf_vol_set.last_error = close_error;
        ((PFFILE_VOLUME_DIRS*)file->p_sfd->ffd.p_vol)->last_error = close_error;
        file->last_access_data.state.last_error = close_error;
        goto close_file_complete;
    }
    if ((volume_dirs->cache_control & 2) != 0) {
        close_error = PFCACHE_FlushFATCache(volume);
        if (close_error != 0) {
            pf_vol_set.last_error = close_error;
            ((PFFILE_VOLUME_DIRS*)file->p_sfd->ffd.p_vol)->last_error = close_error;
            file->last_access_data.state.last_error = close_error;
        } else {
            close_error = PFCACHE_FlushDataCacheSpecific(volume, file);
            if (close_error != 0) {
                pf_vol_set.last_error = close_error;
                ((PFFILE_VOLUME_DIRS*)file->p_sfd->ffd.p_vol)->last_error = close_error;
                file->last_access_data.state.last_error = close_error;
            }
        }
    }
    if (close_error == 0) {
        if (--file->p_sfd->handler_count == 0) {
            file->p_sfd->stat &= ~1U;
            file->p_sfd->ffd.cluster_link.buffer = PF_NULL;
        }
        file->stat &= ~1U;
        volume_dirs->num_opened_files--;
    }
close_file_complete:
    volume_dirs->cache_signature = PF_NULL;
    return close_error;
}

pf_s32 PFFILE_fread(pf_u8* buffer, pf_u32 size, pf_u32 count,
                    PFFILE_FILE* file, pf_u32* count_read) {
    PF_VOLUME* volume;
    pf_s32 error;
    pf_u32 completed_count;

    *count_read = 0;
    volume = file == PF_NULL ? PF_NULL : file->p_sfd->dir_entry.p_vol;
    error = PFVOL_CheckForRead(volume);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
        return error;
    }
    if ((file->p_sfd->stat & 1) == 0 || (file->p_sfd->stat & 2) == 0) {
        pf_vol_set.last_error = 0x26;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = 0x26;
        return 0x26;
    }
    ((PFFILE_VOLUME_DIRS*)volume)->cache_signature = file;
    error = PFFILE_p_fread(volume, buffer, size, count, file, &completed_count);
    *count_read = completed_count;
    ((PFFILE_VOLUME_DIRS*)volume)->cache_signature = PF_NULL;
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)file->p_sfd->ffd.p_vol)->last_error = error;
        file->last_access_data.state.last_error = error;
    }
    return error;
}

pf_s32 PFFILE_fwrite(const pf_u8* buffer, pf_u32 size, pf_u32 count,
                     PFFILE_FILE* file, pf_u32* count_written) {
    PF_VOLUME* volume;
    pf_u32 bytes_written;
    pf_s32 error;

    *count_written = 0;
    volume = file == PF_NULL ? PF_NULL : file->p_sfd->dir_entry.p_vol;
    error = PFVOL_CheckForWrite(volume);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
        return error;
    }
    if ((file->p_sfd->stat & 1) == 0 || (file->p_sfd->stat & 2) == 0) {
        pf_vol_set.last_error = 0x26;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = 0x26;
        return 0x26;
    }
    ((PFFILE_VOLUME_DIRS*)volume)->cache_signature = file;
    error = PFFILE_p_fwrite(volume, buffer, size, count, file, &bytes_written);
    *count_written = bytes_written;
    ((PFFILE_VOLUME_DIRS*)volume)->cache_signature = PF_NULL;
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)file->p_sfd->ffd.p_vol)->last_error = error;
        file->last_access_data.state.last_error = error;
    }
    if (bytes_written != 0) {
        PFENT_getcurrentDateTimeForEnt(&file->p_sfd->dir_entry.modify_date,
                                       &file->p_sfd->dir_entry.modify_time);
        file->p_sfd->dir_entry.access_date = file->p_sfd->dir_entry.modify_date;
        file->p_sfd->stat |= 4;
    }
    return error;
}

pf_s32 PFFILE_feof(PFFILE_FILE* file) {
    PF_VOLUME* volume = file == PF_NULL ? PF_NULL : file->p_sfd->dir_entry.p_vol;
    pf_s32 error;

    error = PFVOL_CheckForRead(volume);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
        return error;
    }
    if ((file->p_sfd->stat & 1) == 0 || (file->p_sfd->stat & 2) == 0) {
        pf_vol_set.last_error = 0x26;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = 0x26;
        return 0x26;
    }
    if (file->cursor.position >= file->p_sfd->dir_entry.file_size) {
        error = 1;
    }
    return error;
}

pf_s32 PFFILE_fseek(PFFILE_FILE* file, pf_s32 offset, pf_s32 origin) {
    PF_VOLUME* volume = file == PF_NULL ? PF_NULL : file->p_sfd->dir_entry.p_vol;
    pf_s32 error = 0;
    pf_u32 file_io;
    pf_u32 wk_offset;

    error = PFVOL_CheckForRead(volume);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
        return error;
    }
    if ((file->p_sfd->stat & 1) == 0 || (file->p_sfd->stat & 2) == 0) {
        pf_vol_set.last_error = 0x26;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = 0x26;
        return 0x26;
    }
    switch (origin) {
    case FA_SEEK_ORIGIN_CURRENT:
        file_io = file->cursor.position;
        break;
    case FA_SEEK_ORIGIN_BEGIN:
        file_io = 0;
        break;
    case FA_SEEK_ORIGIN_END:
        file_io = file->p_sfd->dir_entry.file_size;
        break;
    default:
        return file->last_access_data.state.last_error =
            ((PFFILE_VOLUME_DIRS*)file->p_sfd->ffd.p_vol)->last_error =
            pf_vol_set.last_error = 0x0A;
    }
    if (((pf_u32)offset & 0x80000000) != 0) {
        wk_offset = ~((pf_u32)offset | (pf_u32)offset) & 0x7FFFFFFF;
        wk_offset += 1;
        if (file_io < wk_offset) {
            return file->last_access_data.state.last_error =
                ((PFFILE_VOLUME_DIRS*)file->p_sfd->ffd.p_vol)->last_error =
                pf_vol_set.last_error = 0x0A;
        }
        file_io -= wk_offset;
    } else {
        wk_offset = 0xFFFFFFFF - file_io;
        if ((pf_u32)offset > wk_offset) {
            return file->last_access_data.state.last_error =
                ((PFFILE_VOLUME_DIRS*)file->p_sfd->ffd.p_vol)->last_error =
                pf_vol_set.last_error = 0x25;
        }
        file_io += offset;
    }
    file->cursor.sector = 0xFFFFFFFF;
    file->cursor.position = 0;
    PFFILE_Cursor_Recalc(file);
    file->cursor.position = file_io;
    PFFILE_Cursor_Recalc(file);
    return error;
}

pf_s32 PFFILE_fsetclstlink(PFFILE_FILE* file, pf_u32 mode,
                           PFFILE_CLUSTER_LINK_SETTINGS* settings) {
    PF_VOLUME* volume = file == PF_NULL ? PF_NULL : file->p_sfd->dir_entry.p_vol;
    pf_s32 error;

    error = PFVOL_CheckForRead(volume);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
        return error;
    }
    if (mode == 1) {
        file->p_sfd->ffd.cluster_link.buffer = settings->buffer;
        pf_memset(settings->buffer, 0, settings->link_max * 4);
        file->p_sfd->ffd.cluster_link.max_count = settings->link_max;
        file->p_sfd->ffd.cluster_link.interval = settings->interval;
        file->p_sfd->ffd.cluster_link.interval_offset = 0;
        file->p_sfd->ffd.cluster_link.position = 0;
        file->p_sfd->ffd.cluster_link.save_index = 0;
        if (file->p_sfd->dir_entry.file_size != 0 && file->p_sfd->ffd.cluster_link.max_count != 0) {
            file->p_sfd->ffd.cluster_link.buffer[0] = *file->p_sfd->ffd.p_start_cluster;
            file->p_sfd->ffd.cluster_link.position++;
        }
        if (file->p_sfd->ffd.p_hint != PF_NULL) {
            ((PFFILE_FAT_HINT*)file->p_sfd->ffd.p_hint)->chain_index = 0;
            ((PFFILE_FAT_HINT*)file->p_sfd->ffd.p_hint)->cluster = 0;
            ((PFFILE_FAT_HINT*)file->p_sfd->ffd.p_hint)->previous_cluster = 0;
        }
        file->p_sfd->ffd.last_cluster.num_last_cluster = 0;
        file->p_sfd->ffd.last_cluster.max_chain_index = 0;
        file->p_sfd->ffd.last_access_cluster.chain_index = 0;
        file->p_sfd->ffd.last_access_cluster.cluster = 0;
    } else {
        file->p_sfd->ffd.cluster_link.buffer = PF_NULL;
    }
    return error;
}

pf_s32 PFFILE_fsync(PFFILE_FILE* file) {
    PF_VOLUME* volume = file == PF_NULL ? PF_NULL : file->p_sfd->dir_entry.p_vol;
    pf_u16 access_time;
    pf_s32 error;

    error = PFVOL_CheckForWrite(volume);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
        return error;
    }
    if ((file->p_sfd->stat & 1) == 0 || (file->p_sfd->stat & 2) == 0) {
        pf_vol_set.last_error = 0x26;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = 0x26;
        return 0x26;
    }
    error = PFCACHE_FlushFATCache(volume);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)file->p_sfd->ffd.p_vol)->last_error = error;
        file->last_access_data.state.last_error = error;
        return error;
    }
    PFENT_getcurrentDateTimeForEnt(&file->p_sfd->dir_entry.access_date, &access_time);
    error = PFENT_updateEntry(&file->p_sfd->dir_entry, 1);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)file->p_sfd->ffd.p_vol)->last_error = error;
        file->last_access_data.state.last_error = error;
        return error;
    }
    error = PFCACHE_FlushDataCacheSpecific(volume, file);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)file->p_sfd->ffd.p_vol)->last_error = error;
        file->last_access_data.state.last_error = error;
    }
    return error;
}

pf_s32 PFFILE_fappend(PFFILE_FILE* file, pf_u32 size, pf_u32* size_appended) {
    PF_VOLUME* volume;
    pf_u32 appended_size;
    pf_u16 modify_time;
    pf_s32 error;

    *size_appended = 0;
    volume = file == PF_NULL ? PF_NULL : file->p_sfd->dir_entry.p_vol;
    error = PFVOL_CheckForWrite(volume);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)file->p_sfd->ffd.p_vol)->last_error = error;
        file->last_access_data.state.last_error = error;
        return error;
    }
    if ((file->p_sfd->stat & 1) == 0 || (file->p_sfd->stat & 2) == 0) {
        pf_vol_set.last_error = 0x26;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = 0x26;
        return 0x26;
    }
    ((PFFILE_VOLUME_DIRS*)volume)->cache_signature = file;
    error = PFFILE_p_fappend(file, size, &appended_size);
    *size_appended = appended_size;
    ((PFFILE_VOLUME_DIRS*)volume)->cache_signature = PF_NULL;
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)file->p_sfd->ffd.p_vol)->last_error = error;
        file->last_access_data.state.last_error = error;
        return error;
    }
    PFENT_getcurrentDateTimeForEnt(&file->p_sfd->dir_entry.access_date, &modify_time);
    return 0;
}

pf_s32 PFFILE_fadjust(PFFILE_FILE* file) {
    PF_VOLUME* volume = file == PF_NULL ? PF_NULL : file->p_sfd->dir_entry.p_vol;
    PFFILE_CURSOR saved_cursor;
    PFFILE_FAT_HINT saved_hint;
    pf_u16 access_time;
    pf_s32 error;

    error = PFVOL_CheckForWrite(volume);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)file->p_sfd->ffd.p_vol)->last_error = error;
        file->last_access_data.state.last_error = error;
        return error;
    }
    if ((file->p_sfd->stat & 1) == 0 || (file->p_sfd->stat & 2) == 0) {
        pf_vol_set.last_error = 0x26;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = 0x26;
        return 0x26;
    }
    ((PFFILE_VOLUME_DIRS*)volume)->cache_signature = file;
    saved_cursor = file->cursor;
    saved_hint = *(PFFILE_FAT_HINT*)&file->hint;
    if ((file->open_mode & 8) == 0 && (file->open_mode & 2) != 0) {
        error = 0x0A;
    } else if ((file->p_sfd->lock.mode & 3) != 0 &&
               ((file->p_sfd->lock.mode & 1) != 0 ||
                ((file->p_sfd->lock.mode & 2) != 0 && file->lock_count == 0))) {
        error = 0x19;
    } else {
        error = PFCLUSTER_AdjustCluster(file);
        error &= (-error | error) >> 31;
    }
    file->cursor = saved_cursor;
    *(PFFILE_FAT_HINT*)&file->hint = saved_hint;
    ((PFFILE_VOLUME_DIRS*)volume)->cache_signature = PF_NULL;
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)file->p_sfd->ffd.p_vol)->last_error = error;
        file->last_access_data.state.last_error = error;
        return error;
    }
    PFENT_getcurrentDateTimeForEnt(&file->p_sfd->dir_entry.access_date, &access_time);
    return 0;
}

pf_s32 PFFILE_finfo(PFFILE_FILE* file, PF_INFO* info) {
    PF_VOLUME* volume = file == PF_NULL ? PF_NULL : file->p_sfd->dir_entry.p_vol;
    PFFILE_CURSOR saved_cursor;
    PFFILE_FAT_HINT saved_hint;
    pf_s32 error;

    error = PFVOL_CheckForRead(volume);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)file->p_sfd->ffd.p_vol)->last_error = error;
        file->last_access_data.state.last_error = error;
        return error;
    }
    if ((file->p_sfd->stat & 1) == 0 || (file->p_sfd->stat & 2) == 0) {
        pf_vol_set.last_error = 0x26;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = 0x26;
        return 0x26;
    }
    ((PFFILE_VOLUME_DIRS*)volume)->cache_signature = file;
    saved_cursor = file->cursor;
    saved_hint = *(PFFILE_FAT_HINT*)&file->hint;
    error = PFFILE_p_finfo(file, info);
    file->cursor = saved_cursor;
    *(PFFILE_FAT_HINT*)&file->hint = saved_hint;
    ((PFFILE_VOLUME_DIRS*)volume)->cache_signature = PF_NULL;
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)file->p_sfd->ffd.p_vol)->last_error = error;
        file->last_access_data.state.last_error = error;
        return error;
    }
    return 0;
}

pf_s32 PFFILE_combine(PF_STR* first_path, PF_STR* second_path) {
    PF_VOLUME* volume = PFPATH_GetVolumeFromPath(first_path);
    PF_VOLUME* second_volume = PFPATH_GetVolumeFromPath(second_path);
    pf_s32 error;

    if (volume != second_volume) {
        pf_vol_set.last_error = 0x0A;
        return 0x0A;
    }
    error = PFVOL_CheckForWrite(volume);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
        return error;
    }
    ((PFFILE_VOLUME_DIRS*)volume)->cache_signature = PF_NULL;
    error = PFFILE_p_combine(volume, first_path, second_path);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
    } else {
        error = PFCACHE_FlushFATCache(volume);
        if (error != 0) {
            pf_vol_set.last_error = error;
            ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
        } else {
            error = PFCACHE_FlushDataCacheSpecific(volume, PF_NULL);
            if (error != 0) {
                pf_vol_set.last_error = error;
                ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
            }
        }
    }
    ((PFFILE_VOLUME_DIRS*)volume)->cache_signature = PF_NULL;
    return error;
}

pf_s32 PFFILE_divide(PF_STR* source_path, PF_STR* destination_path, pf_u32 split_size) {
    PF_VOLUME* volume = PFPATH_GetVolumeFromPath(source_path);
    PF_VOLUME* destination_volume = PFPATH_GetVolumeFromPath(destination_path);
    pf_s32 error;

    if (volume != destination_volume) {
        pf_vol_set.last_error = 0x1F;
        return 0x1F;
    }
    error = PFVOL_CheckForWrite(volume);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
        return error;
    }
    ((PFFILE_VOLUME_DIRS*)volume)->cache_signature = PF_NULL;
    error = PFFILE_p_divide(volume, source_path, destination_path, split_size);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
    } else {
        error = PFCACHE_FlushFATCache(volume);
        if (error != 0) {
            pf_vol_set.last_error = error;
            ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
        } else {
            error = PFCACHE_FlushDataCacheSpecific(volume, PF_NULL);
            if (error != 0) {
                pf_vol_set.last_error = error;
                ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
            }
        }
    }
    ((PFFILE_VOLUME_DIRS*)volume)->cache_signature = PF_NULL;
    return error;
}

pf_s32 PFFILE_cinsert(PF_STR* path, pf_u32 cluster_index, pf_u32 count,
                      pf_u32* cluster_result) {
    PF_VOLUME* volume;
    pf_s32 error;

    *cluster_result = 0;
    volume = PFPATH_GetVolumeFromPath(path);
    error = PFVOL_CheckForWrite(volume);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
        return error;
    }
    ((PFFILE_VOLUME_DIRS*)volume)->cache_signature = PF_NULL;
    error = PFFILE_p_cinsert(volume, path, cluster_index, count, (pf_u32)cluster_result);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
    } else {
        error = PFCACHE_FlushFATCache(volume);
        if (error != 0) {
            pf_vol_set.last_error = error;
            ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
        } else {
            error = PFCACHE_FlushDataCacheSpecific(volume, PF_NULL);
            if (error != 0) {
                pf_vol_set.last_error = error;
                ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
            }
        }
    }
    ((PFFILE_VOLUME_DIRS*)volume)->cache_signature = PF_NULL;
    return error;
}

pf_s32 PFFILE_cdelete(PF_STR* path, pf_u32 cluster_index, pf_u32 count,
                      pf_u32* cluster_result) {
    PF_VOLUME* volume;
    pf_s32 error;

    *cluster_result = 0;
    volume = PFPATH_GetVolumeFromPath(path);
    error = PFVOL_CheckForWrite(volume);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
        return error;
    }
    ((PFFILE_VOLUME_DIRS*)volume)->cache_signature = PF_NULL;
    error = PFFILE_p_cdelete(volume, path, cluster_index, count, (pf_u32)cluster_result);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
    } else {
        error = PFCACHE_FlushDataCacheSpecific(volume, PF_NULL);
        if (error != 0) {
            pf_vol_set.last_error = error;
            ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
        } else {
            error = PFCACHE_FlushFATCache(volume);
            if (error != 0) {
                pf_vol_set.last_error = error;
                ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
            }
        }
    }
    ((PFFILE_VOLUME_DIRS*)volume)->cache_signature = PF_NULL;
    return error;
}

pf_s32 PFFILE_flock(PFFILE_FILE* file, pf_u32 mode) {
    PF_VOLUME* volume = file == PF_NULL ? PF_NULL : file->p_sfd->dir_entry.p_vol;
    pf_s32 error;

    error = PFVOL_CheckForRead(volume);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
        return error;
    }
    if ((file->p_sfd->stat & 1) == 0 || (file->p_sfd->stat & 2) == 0) {
        pf_vol_set.last_error = 0x26;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = 0x26;
        return 0x26;
    }
    error = PFFILE_p_flock(file, mode);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFFILE_VOLUME_DIRS*)volume)->last_error = error;
    }
    return error;
}
