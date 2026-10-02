#include <private/vf/PrFILE2/fatfs/pf_dir.h>

#include <private/vf/PrFILE2/fatfs/pf_entry.h>
#include <private/vf/PrFILE2/fatfs/pf_volume.h>
#include <private/vf/PrFILE2/common/pf_clib.h>
#include <private/vf/PrFILE2/common/pf_w_clib.h>
#include <private/vf/PrFILE2/fatfs/pf_path.h>
#include <private/vf/PrFILE2/fatfs/pf_sector.h>

typedef struct PFDIR_FFD {
    pf_u32 start_cluster;
    pf_u32 flags;
    pf_u32* p_start_cluster;
    PF_LAST_CLUSTER last_cluster;
    PF_FAT_LAST_ACCESS last_access_cluster;
    PF_CLUSTER_LINK cluster_link;
    struct PFDIR_FAT_HINT* p_hint;
    PF_VOLUME* p_vol;
} PFDIR_FFD;

typedef struct PFDIR_FAT_HINT {
    pf_u32 chain_index;
    pf_u32 cluster;
    pf_u32 previous_cluster;
} PFDIR_FAT_HINT;

typedef struct PFDIR_STR {
    const pf_s8* p_head;
    const pf_s8* p_tail;
    const pf_s8* p_current;
    pf_u32 code_mode;
} PFDIR_STR;

struct PF_ENT_ITER {
    pf_u32 index;
    PF_VOLUME* p_vol;
    PFDIR_FFD ffd;
    pf_u32 file_sector_index;
    pf_u32 sector;
    pf_u16 offset;
    pf_u16 offset_mask;
    pf_u8 buf[32];
    pf_u8 log2_entries_per_sector;
};

typedef struct PFDIR_SDD {
    pf_u32 stat;
    pf_u16 num_handlers;
    pf_u16 alignment;
    PFDIR_FFD ffd;
    PF_DIR_ENT dir_entry;
} PFDIR_SDD;

typedef struct PFDIR_SFD {
    pf_u32 stat;
    pf_u16 num_handlers;
    pf_u16 alignment;
    PF_FFD ffd;
    PF_DIR_ENT dir_entry;
    pf_u8 lock_state[0x20];
} PFDIR_SFD;

typedef struct PFDIR_DIR {
    pf_u32 stat;
    PFDIR_SDD* p_sdd;
    PFDIR_FAT_HINT hint;
    pf_u32 current_position;
    pf_u32 next_position;
    pf_u32 end_position;
} PFDIR_DIR;

typedef struct PFDIR_READ_RESULT {
    pf_s8 name[0x200];
    pf_s8 short_name[0x200];
} PFDIR_READ_RESULT;

typedef struct PFDIR_FILE_STAT {
    pf_u32 file_size;
    pf_u16 access_date;
    pf_u16 modify_time;
    pf_u16 modify_date;
    pf_u16 create_time;
    pf_u16 create_date;
    pf_u16 small_letter_flag;
    pf_u8 attributes;
} PFDIR_FILE_STAT;

typedef struct PFDIR_VOLUME_DIRS {
    pf_u8 volume_prefix[0x40];
    PFDIR_SFD sfds[5];
    pf_u8 volume_state[0xF0];
    PFDIR_SDD sdds[3];
    PFDIR_DIR udds[3];
    pf_s32 num_opened_files;
    pf_s32 num_opened_directories;
    PF_SECTOR_CACHE cache;
    pf_s8 label[12];
    PF_CUR_DIR current_dirs[4];
    PF_DIR_TAIL tail_entry;
    pf_s32 last_error;
} PFDIR_VOLUME_DIRS;

typedef struct PFDIR_GLOBAL_STATE {
    union {
        pf_u8 state_prefix[0x40];
        PF_CUR_VOLUME volumes[4];
    } volume_state;
    pf_s32 last_error;
    pf_u8 driver_and_code_state[0x1C];
    pf_u32 setting;
} PFDIR_GLOBAL_STATE;

extern PFDIR_GLOBAL_STATE pf_vol_set;

extern pf_s32 PFENT_ITER_MoveTo(PF_ENT_ITER* iter, pf_u32 index, pf_u32 may_allocate);
extern pf_s32 PFENT_ITER_Advance(PF_ENT_ITER* iter, pf_u32 may_allocate);
extern pf_s32 PFENT_ITER_IsAtLogicalEnd(PF_ENT_ITER* iter);
extern pf_s32 PFENT_ITER_GetEntryOfPath(PF_ENT_ITER* iter, PF_DIR_ENT* entry, PF_VOLUME* volume, PFDIR_STR* path,
                                        pf_u32 no_look_last_token);
extern pf_s32 PFENT_GetRootDir(PF_VOLUME* volume, PF_DIR_ENT* entry);
extern pf_s32 PFVOL_GetCurrentDir(PF_VOLUME* volume, PF_DIR_ENT* entry);
extern pf_s32 PFVOL_SetCurrentDir(PF_VOLUME* volume, PF_DIR_ENT* entry);
extern pf_s32 PFFAT_InitFFD(void* ffd, void* hint, PF_VOLUME* volume, pf_u32* start_cluster);
extern void PFFAT_InitHint(PFDIR_FAT_HINT* hint);
extern pf_s32 PFSTR_StrNCmp(PFDIR_STR* path, const pf_s8* text, pf_u32 target, pf_s16 offset, pf_u16 count);
extern pf_u16 PFSTR_StrNumChar(PFDIR_STR* path, pf_u32 code_mode);
extern void PFSTR_MoveStrPos(PFDIR_STR* path, pf_s16 count);
extern pf_s32 PFSTR_InitStr(PFDIR_STR* path, const pf_s8* text, pf_u32 code_mode);
extern void PFSTR_SetLocalStr(PFDIR_STR* path, pf_u32 is_local);
extern pf_s32 PFENT_findEntryPos(PFDIR_FFD* ffd, PF_DIR_ENT* entry, pf_u32 start, PFDIR_STR* pattern,
                                 pf_u8 attr_required, pf_u32 skip, pf_u32* logical_position,
                                 pf_u32* entry_position);
extern pf_s8* pf_strcpy(pf_s8* destination, const pf_s8* source);
extern pf_s32 PFPATH_transformFromUnicodeToNormal(pf_s8* destination, const pf_u16* source);
extern pf_s32 PFPATH_SplitPath(PFDIR_STR* path, PFDIR_STR* directory, PFDIR_STR* filename);
extern pf_u8 PFENT_getcurrentDateTimeForEnt(pf_u16* date, pf_u16* time);
extern pf_s32 PFENT_updateEntry(PF_DIR_ENT* entry, pf_u32 clear_archive);
extern pf_s32 PFFILE_IsOpened(PF_DIR_ENT* entry);
extern pf_s32 PFVOL_CheckCurrentDir(PF_VOLUME* volume, pf_u32 start_cluster);
extern pf_s32 PFENT_RemoveEntry(PF_DIR_ENT* entry, PF_ENT_ITER* iter);
extern pf_s32 PFFAT_FreeChain(PFDIR_FFD* ffd, pf_u32 start_cluster, pf_u32 chain_index, pf_u32 size);

static inline pf_u32 current_directory_is_open(PF_VOLUME* volume, pf_u32 cluster) {
    pf_u32 index;
    for (index = 0; index < 4; index++) {
        if (pf_vol_set.volume_state.volumes[index].p_vol == volume) {
            PFDIR_VOLUME_DIRS* state = (PFDIR_VOLUME_DIRS*)volume;
            PF_CUR_DIR* directory = state->current_dirs;
            pf_u32 slot;
            for (slot = 0; slot < 4; slot++, directory++) {
                if ((directory->stat & 1) != 0 && directory->directory.start_cluster == cluster) { return 1; }
            }
        }
    }
    return 0;
}

static inline pf_u32 directory_is_open(PF_DIR_ENT* entry) {
    PFDIR_VOLUME_DIRS* volume = (PFDIR_VOLUME_DIRS*)entry->p_vol;
    pf_s32 index;
    PFDIR_SDD* sdd = volume->sdds;
    for (index = 0; index < 3; index++, sdd++) {
        if ((sdd->stat & 1) != 0 && (sdd->stat & 2) != 0 &&
            entry->p_vol == sdd->dir_entry.p_vol &&
            entry->entry_sector == sdd->dir_entry.entry_sector &&
            entry->entry_offset == sdd->dir_entry.entry_offset) { return 1; }
    }
    return 0;
}

extern void PFFAT_ResetFFD(PFDIR_FFD*, pf_u32*);
static inline pf_s32 release_directory_chain(PFDIR_FFD* ffd, pf_u32 cluster, pf_u32 count) {
    pf_s32 error = PFFAT_FreeChain(ffd, cluster, -1U, count);
    if (error != 0) { return error; }
    return 0;
}

pf_s32 PFDIR_CheckDirIsEmpty(PF_ENT_ITER* iter, pf_u32* is_empty) {
    pf_u32 start_cluster = *iter->ffd.p_start_cluster;
    pf_s32 error;

    if (start_cluster == 1 ||
        (iter->ffd.p_vol->bpb.fat_type == FAT_32 &&
         start_cluster == iter->ffd.p_vol->bpb.root_dir_cluster)) {
        error = 0;
    } else {
        error = 2;
    }
    *is_empty = 1;
    error = PFENT_ITER_MoveTo(iter, error, 0);
    while (!PFENT_ITER_IsAtLogicalEnd(iter)) {
        if (error != 0) {
            if (error == 13) {
                return 0;
            }
            return error;
        }
        if (iter->buf[0] != 0xE5) {
            pf_u8 attributes = iter->buf[0xB];
            if ((attributes & 0xF) != 0xF && (attributes & 8) == 0) {
                if (iter->buf[0] == 0) {
                    *is_empty = 1;
                } else {
                    *is_empty = 0;
                }
                break;
            }
        }
        error = PFENT_ITER_Advance(iter, 0);
    }
    return 0;
}

PFDIR_SDD* PFDIR_GetSDD(PF_VOLUME* volume, PF_DIR_ENT* entry) {
    PFDIR_VOLUME_DIRS* volume_dirs = (PFDIR_VOLUME_DIRS*)volume;
    PFDIR_SDD* first_free_sdd = 0;
    pf_s32 i;
    pf_s32 remaining = 3;

    for (i = 0; remaining != 0; remaining--) {
        if ((volume_dirs->sdds[i].stat & 1) == 0 || ((volume_dirs->sdds[i].stat & 1) != 0 && (!volume_dirs->sdds[i].stat & 2) != 0)) {
            if (first_free_sdd == 0) {
                first_free_sdd = &volume_dirs->sdds[i];
            }
        } else if (entry->p_vol == volume_dirs->sdds[i].dir_entry.p_vol &&
                   entry->entry_sector == volume_dirs->sdds[i].dir_entry.entry_sector &&
                   entry->entry_offset == volume_dirs->sdds[i].dir_entry.entry_offset) {
            return &volume_dirs->sdds[i];
        }
        i++;
    }
    if (first_free_sdd == 0) {
        return 0;
    }
    first_free_sdd->stat = 3;
    first_free_sdd->num_handlers = 0;
    first_free_sdd->dir_entry = *entry;
    PFFAT_InitFFD(&first_free_sdd->ffd, 0, entry->p_vol, &first_free_sdd->dir_entry.start_cluster);
    return first_free_sdd;
}

static inline PFDIR_DIR* unused_directory(PF_VOLUME* volume) {
    pf_s32 index;
    for (index = 0; index < 3; index++) {
        if ((((PFDIR_VOLUME_DIRS*)volume)->udds[index].stat & 1) == 0) {
            return &((PFDIR_VOLUME_DIRS*)volume)->udds[index];
        }
    }
    return 0;
}

pf_s32 PFDIR_DoFsexecOpenDir(PF_DIR_ENT* entry, PF_ENT_ITER* iter, PFDIR_DIR** opened_dir) {
    PFDIR_VOLUME_DIRS* volume_dirs = (PFDIR_VOLUME_DIRS*)entry->p_vol;
    pf_s32 i;
    PFDIR_SDD* sdd;
    PFDIR_DIR* dir;

    *opened_dir = 0;
    if ((entry->attr & 0x10) == 0) {
        return 0x14;
    }
    sdd = PFDIR_GetSDD((PF_VOLUME*)volume_dirs, entry);
    if (sdd == 0) {
        return 0x15;
    }
    dir = unused_directory((PF_VOLUME*)volume_dirs);
    if (dir == 0) {
        return 0x16;
    }
    dir->p_sdd = sdd;
    dir->stat = 1;
    PFFAT_InitHint(&dir->hint);
    dir->current_position = 0;
    dir->next_position = 0;
    dir->end_position = 0;
    sdd->num_handlers++;
    *opened_dir = dir;
    return 0;
}

pf_s32 PFDIR_p_opendir(PF_VOLUME* volume, PFDIR_STR* path, PFDIR_DIR** opened_dir) {
    PF_ENT_ITER iter;
    PF_DIR_ENT entry;
    pf_s32 i;
    PFDIR_SDD* sdd;
    PFDIR_DIR* dir;
    pf_s32 error;

    if ((PFSTR_StrNCmp(path, (const pf_s8*)"\\", 1, 0, 1) == 0 ||
         PFSTR_StrNCmp(path, (const pf_s8*)"/", 1, 0, 1) == 0) &&
        PFSTR_StrNCmp(path, (const pf_s8*)"", 1, 1, 1) == 0) {
        error = PFENT_GetRootDir(volume, &entry);
        if (error != 0) {
            return error;
        }
        goto open_directory;
    } else if (PFSTR_StrNumChar(path, 1) == 2 &&
               PFSTR_StrNCmp(path, (const pf_s8*)":", 1, 1, 1) == 0) {
        error = PFVOL_GetCurrentDir(volume, &entry);
        goto open_directory;
    } else if (PFSTR_StrNumChar(path, 1) == 3 &&
               PFSTR_StrNCmp(path, (const pf_s8*)":", 1, 1, 1) == 0 &&
               (PFSTR_StrNCmp(path, (const pf_s8*)"\\", 1, 2, 1) == 0 ||
                PFSTR_StrNCmp(path, (const pf_s8*)"/", 1, 2, 1) == 0)) {
        error = PFENT_GetRootDir(volume, &entry);
        if (error != 0) {
            return error;
        }
        goto open_directory;
    } else {
        if (PFSTR_StrNCmp(path, (const pf_s8*)":", 1, 1, 1) == 0 &&
            (PFSTR_StrNCmp(path, (const pf_s8*)"\\", 1, 2, 1) == 0 ||
             PFSTR_StrNCmp(path, (const pf_s8*)"/", 1, 2, 1) == 0)) {
            PFSTR_MoveStrPos(path, 2);
        }
        error = PFENT_ITER_GetEntryOfPath(&iter, &entry, volume, path, 0);
        if (error != 0) {
            return error;
        }
        if ((entry.attr & 0x10) == 0) {
            return 1;
        }
    }

open_directory:
    sdd = PFDIR_GetSDD(volume, &entry);
    if (sdd == 0) {
        return 0x15;
    }
    dir = unused_directory(volume);
    if (dir == 0) {
        return 0x16;
    }
    dir->p_sdd = sdd;
    dir->stat = 1;
    PFFAT_InitHint(&dir->hint);
    dir->current_position = 0;
    dir->next_position = 0;
    dir->end_position = 0;
    sdd->num_handlers++;
    *opened_dir = dir;
    return 0;
}

pf_s32 PFDIR_p_readdir(PFDIR_DIR* dir, PFDIR_READ_RESULT* result) {
    PFDIR_FFD ffd;
    PFDIR_FAT_HINT hint;
    PF_DIR_ENT entry;
    PFDIR_STR pattern;
    pf_u32 remaining;
    pf_u32 logical_position;
    pf_u32 entry_position;
    pf_s32 error;

    PFFAT_InitFFD(&ffd, &hint, dir->p_sdd->ffd.p_vol, &dir->p_sdd->dir_entry.start_cluster);
    remaining = dir->end_position;
    if (dir->next_position <= remaining) {
        remaining -= dir->next_position;
    } else if (dir->next_position > remaining) {
        dir->current_position = 0;
        dir->next_position = 0;
    }
    do {
        PFSTR_InitStr(&pattern, (const pf_s8*)"*", 1);
        PFSTR_SetLocalStr(&pattern, 0);
        error = PFENT_findEntryPos(&ffd, &entry, dir->current_position, &pattern, 0x7F, 0,
                                   &logical_position, &entry_position);
        if (error != 0) {
            return error;
        }
        dir->current_position = entry_position + 1;
        dir->next_position++;
    } while (remaining-- != 0);
    dir->end_position = dir->next_position;
    pf_strcpy(result->short_name, entry.short_name);
    if (entry.long_name[0] != 0) {
        PFPATH_transformFromUnicodeToNormal(result->name, entry.long_name);
    } else {
        result->name[0] = 0;
    }
    return 0;
}

extern pf_s32 PFENT_findEntry(PFDIR_FFD*, PF_DIR_ENT*, pf_u32, PFDIR_STR*, pf_u8, pf_u32*, pf_u32*);
extern pf_s32 PFFAT_GetSectorSpecified(PFDIR_FFD*, pf_u32, pf_u32, pf_u32*);
extern pf_s32 PFPATH_transformInUnicode(pf_u16*, const pf_s8*);
extern void PFPATH_SetSearchPattern(pf_s8*, pf_u16*, PFDIR_STR*);
extern pf_u16* pf_w_strcpy(pf_u16*, const pf_u16*);

extern pf_s32 PFPATH_parseShortName(pf_s8* name, PFDIR_STR* path);
extern pf_s32 PFENT_AdjustSFN(PF_DIR_ENT* parent, pf_s8* name);
extern pf_s32 PFENT_ITER_FindDirEntryFromCluster(PF_ENT_ITER* iter, PF_DIR_ENT* entry, pf_u32 cluster, pf_u32* found);
extern pf_s32 PFENT_ITER_FindEntryNoPathCheck(PF_ENT_ITER* iter, PF_DIR_ENT* entry, PFDIR_STR* pattern, pf_u8 attributes, pf_u32 start, pf_u32* found);
extern pf_s32 PFENT_ITER_GetEntryOfIter(PF_ENT_ITER* iter, PF_DIR_ENT* entry);
extern pf_s32 pf_strncmp(const pf_s8* left, const pf_s8* right, pf_u32 count);
extern pf_s32 PFENT_ITER_FindCluster(PF_DIR_ENT* entry, pf_u32 cluster, pf_u32* found);
extern pf_s32 PFENT_ITER_Retreat(PF_ENT_ITER* iter, pf_u32 may_allocate);
extern pf_s32 PFENT_allocateEntryPos(PF_DIR_ENT* entry, pf_u8 count, PFDIR_FFD* ffd, pf_u32* chain, PFDIR_STR* filename, pf_u32* position);
extern pf_u8 PFENT_CalcCheckSum(PF_DIR_ENT* entry);
extern void PFENT_storeLFNEntryFieldsToBuf(pf_u8* buffer, PF_DIR_ENT* entry, pf_u8 ordinal, pf_u8 checksum, pf_u32 last);
extern pf_s32 PFSEC_WriteData(PF_VOLUME* volume, const pf_u8* buffer, pf_u32 sector, pf_u16 offset, pf_u32 size, pf_u32* written, pf_u32 direct);
extern pf_s32 PFCACHE_FlushDataCache(PF_VOLUME* volume);
extern pf_u32 PFSTR_GetCodeMode(PFDIR_STR* path);
extern const pf_s8* PFSTR_GetStrPos(PFDIR_STR* path, pf_u32 target);
extern pf_s32 PFFAT_GetSectorSpecified(PFDIR_FFD* ffd, pf_u32 index, pf_u32 allocate, pf_u32* sector);
extern void PFPATH_AdjustExtShortName(pf_s8* name, pf_u32 position);

extern pf_s32 PFCACHE_AllocateDataPage(PF_VOLUME* volume, pf_u32 sector, PF_CACHE_PAGE** page, pf_u32* size);
extern void PFCACHE_FreeDataPage(PF_VOLUME* volume, PF_CACHE_PAGE* page);
static inline void set_dot_entry(pf_u8* buffer) {
    buffer[0] = '.';
    buffer[1] = ' ';
    buffer[2] = ' ';
    buffer[3] = ' ';
    buffer[4] = ' ';
    buffer[5] = ' ';
    buffer[6] = ' ';
    buffer[7] = ' ';
    buffer[8] = ' ';
    buffer[9] = ' ';
    buffer[10] = ' ';
}

static inline void set_dot_dot_entry(pf_u8* buffer) {
    buffer[0] = '.';
    buffer[1] = '.';
    buffer[2] = ' ';
    buffer[3] = ' ';
    buffer[4] = ' ';
    buffer[5] = ' ';
    buffer[6] = ' ';
    buffer[7] = ' ';
    buffer[8] = ' ';
    buffer[9] = ' ';
    buffer[10] = ' ';
}

extern void PFENT_StoreEntryNumericFieldsToBuf(pf_u8* buffer, PF_DIR_ENT* entry);
extern PF_VOLUME* PFPATH_GetVolumeFromPath(PF_STR* path);
extern pf_s32 PFCACHE_FlushDataCacheSpecific(PF_VOLUME* volume, void* entry);
extern pf_s32 PFCACHE_FlushFATCache(PF_VOLUME* volume);
extern pf_s32 PFDIR_p_fsfirst(PF_VOLUME* volume, PF_STR* path, pf_u8 attributes, PF_DTA* data);
extern pf_s32 PFDIR_p_fsnext(PF_DTA* data);
extern pf_s32 PFDIR_p_fsexec(PF_DTA* data, pf_u32 flags, pf_u32 mode);
extern pf_s32 PFDIR_p_fsexec_chmod(PF_DTA* data, PF_DIR_ENT* entry, pf_u32 attributes, pf_u32 mode);
extern pf_s32 PFDIR_p_fsexec_remove(PF_DTA* data, PF_DIR_ENT* entry, PF_ENT_ITER* iter);
extern pf_s32 PFDIR_p_fsexec_fopen(PF_DTA* data, PF_DIR_ENT* entry, PF_ENT_ITER* iter, pf_u32 flags,
                                    pf_u32 mode);
extern pf_s32 PFDIR_p_fsexec_opendir(PF_DTA* data, PF_DIR_ENT* entry, PF_ENT_ITER* iter, pf_u32 flags);
extern void PFFAT_FinalizeFFD(PF_FFD* ffd);
extern pf_s32 PFENT_ITER_GetEntryOfPattern(PF_ENT_ITER* iter, PF_DIR_ENT* entry, PF_VOLUME* volume,
                                           PFDIR_STR* directory);
extern pf_s32 PFENT_ITER_FindEntry(PF_ENT_ITER* iter, PF_DIR_ENT* entry, PFDIR_STR* pattern,
                                   pf_u8 attributes, pf_u32 start, pf_u32* found);
extern pf_s32 PFENT_findEntry(PFDIR_FFD* ffd, PF_DIR_ENT* entry, pf_u32 start, PFDIR_STR* pattern,
                              pf_u8 attributes, pf_u32* logical_position, pf_u32* entry_position);
extern pf_u32 PFSTR_GetCodeMode(PFDIR_STR* path);
extern const pf_s8* PFSTR_GetStrPos(PFDIR_STR* path, pf_u32 target);
extern pf_s32 PFPATH_SplitPathPattern(PF_STR* path, PFDIR_STR* directory, PFDIR_STR* pattern);
extern void PFPATH_SetSearchPattern(pf_s8* ansi_pattern, pf_u16* unicode_pattern, PFDIR_STR* pattern);
extern pf_u16* pf_w_strcpy(pf_u16* destination, const pf_u16* source);
extern pf_s32 PFPATH_transformInUnicode(pf_u16* destination, const pf_s8* source);

extern pf_s32 PFENT_ITER_GetLFNEntryName(PF_ENT_ITER* iter);
extern void PFPATH_getLongNameformShortName(pf_s8* short_name, pf_s8* long_name, pf_u8 small_letter_flag);
extern pf_s32 PFFILE_FsexecOpenFile(PF_DIR_ENT* entry, PF_ENT_ITER* iter, pf_u32 mode, PF_DTA* data);
extern pf_s32 PFPATH_cmpName(const pf_s8* short_name, PFDIR_STR* pattern, pf_u32 short_search);
extern pf_s32 PFPATH_cmpNameUni(const pf_u16* name, PFDIR_STR* pattern);
pf_s32 PFDIR_p_mkdir(PF_VOLUME* volume, PF_STR* path, pf_u32 option, PF_DTA* data) {
    PF_DIR_ENT parent_entry;
    PF_DIR_ENT entry;
    pf_s8 normalized_name[512];
    PF_ENT_ITER iter;
    PFDIR_FFD ffd;
    pf_u8 entry_buffer[32];
    PFDIR_STR directory;
    PFDIR_STR filename;
    PFDIR_FAT_HINT hint;
    pf_u32 previous_chain[2];
    pf_u32 found;
    pf_u32 page_size;
    PF_CACHE_PAGE* page;
    pf_u8 lfn_count = 0;
    pf_u32 sector = 0;
    pf_u32 written;
    pf_u32 position;
    pf_u32 entry_sector;
    pf_u16 filename_length;
    pf_u16 original_offset;
    pf_u8 checksum;
    pf_u32 cluster;
    pf_u32 index;
    pf_u32 lfn_index;
    pf_u32* next_sector;
    pf_s32 error;

    error = PFPATH_SplitPath((PFDIR_STR*)path, &directory, &filename);
    if (error != 0) { return error; }
    error = PFENT_ITER_GetEntryOfPath(&iter, &parent_entry, volume, &directory, 1);
    if (error != 0) { return error; }
    if ((parent_entry.attr & 0x10) == 0) { return 0x14; }
    filename_length = PFSTR_StrNumChar(&filename, 1);
    if (filename_length + parent_entry.path_len > 0x103) { return 2; }
    if (filename_length > 255) { return 1; }
    if (PFSTR_GetCodeMode(&filename) == 2) {
        PFPATH_transformFromUnicodeToNormal(normalized_name,
            (const pf_u16*)PFSTR_GetStrPos(&filename, 1));
    }
    PFSTR_SetLocalStr(&filename, (pf_u32)normalized_name);
    if (data != 0) {
        data->p_file = 0;
        data->p_dir = 0;
        data->parent_start_cluster = parent_entry.start_cluster;
        data->p_vol = parent_entry.p_vol;
        data->attr = 0x10;
        if (PFSTR_GetCodeMode(&filename) == 1) {
            PFPATH_SetSearchPattern(data->reg_exp, 0, &filename);
            data->status |= 1;
        } else {
            PFPATH_SetSearchPattern(data->reg_exp, ((PF_DTAW*)data)->reg_expW, &filename);
            data->status |= 2;
        }
    }
    PFFAT_InitFFD(&ffd, &hint, volume, &parent_entry.start_cluster);
    iter.ffd = ffd;
    PFFAT_ResetFFD(&iter.ffd, &parent_entry.start_cluster);
    error = PFENT_ITER_IteratorInitialize(&iter, 0);
    if (error != 0) { return error; }
    error = PFENT_ITER_FindEntry(&iter, &entry, &filename, 0x10, 0, &found);
    if (error != 0) { return error; }
    if (found != 0) { return 8; }
    error = PFPATH_parseShortName(entry.short_name, &filename);
    if (error != 0 && entry.short_name[0] == 0) { return 1; }
    if (error != 0) {
        error = PFENT_AdjustSFN(&parent_entry, entry.short_name);
        if (error != 0) { return error; }
        if (PFSTR_GetCodeMode(&filename) == 1) {
            filename_length = PFPATH_transformInUnicode(entry.long_name, PFSTR_GetStrPos(&filename, 1));
        } else {
            pf_w_strcpy(entry.long_name, (const pf_u16*)PFSTR_GetStrPos(&filename, 1));
        }
    } else {
        entry.long_name[0] = 0;
    }
    entry.start_cluster = 0;
    entry.file_size = 0;
    entry.p_vol = volume;
    entry.small_letter_flag = 0;
    entry.attr = 0x10;
    entry.create_time_ms = PFENT_getcurrentDateTimeForEnt(&entry.create_date, &entry.create_time);
    entry.access_date = entry.create_date;
    entry.modify_time = entry.create_time;
    entry.modify_date = entry.create_date;
    original_offset = entry.entry_offset;
    if (entry.long_name[0] != 0 && (entry.small_letter_flag & 0x18) == 0) {
        lfn_count = (pf_u32)filename_length / 13 + ((pf_u32)filename_length % 13 != 0);
        error = PFENT_allocateEntryPos(&entry, lfn_count + 1, &ffd, previous_chain, &filename, &position);
        if (error != 0) { return error; }
        if ((pf_vol_set.setting & 2) == 2) { PFPATH_AdjustExtShortName(entry.short_name, position); }
    } else {
        error = PFENT_allocateEntryPos(&entry, 1, &ffd, previous_chain, &filename, &position);
        if (error != 0) { return error; }
    }
    PFFAT_ResetFFD(&ffd, &entry.start_cluster);
    error = PFFAT_GetSectorSpecified(&ffd, 0, 1, &sector);
    if (error != 0) { return error; }
    if (sector == -1U) { return 6; }
    cluster = ffd.p_hint->cluster;
    if (volume->bpb.fat_type == FAT_32 && *iter.ffd.p_start_cluster == volume->bpb.root_dir_cluster &&
        original_offset == 0 && cluster == volume->bpb.root_dir_cluster) {
        iter.ffd = ffd;
        error = PFENT_ITER_IteratorInitialize(&iter, lfn_count);
        if (error != 0) { return error; }
        if (iter.buf[0] == 0) {
            PFFAT_ResetFFD(&ffd, &entry.start_cluster);
            *ffd.p_start_cluster = 0;
            ffd.p_hint->cluster = 0;
            cluster = volume->bpb.root_dir_cluster + 1;
            error = PFFAT_GetSectorSpecified(&ffd, 0, 1, &sector);
            if (error != 0) { return error; }
        }
    }
    error = PFCACHE_AllocateDataPage(volume, -1U, &page, &page_size);
    if (error != 0) { return error; }
    pf_memset(page->p_buf, 0, volume->bpb.bytes_per_sector);
    index = volume->bpb.sectors_per_cluster;
    while (index != 0) {
        if (index == 1) {
            set_dot_entry(page->p_buf);
            PFENT_StoreEntryNumericFieldsToBuf(page->p_buf, &entry);
            set_dot_dot_entry(page->p_buf + 32);
            if (parent_entry.entry_sector == -1U) { entry.start_cluster = 0; }
            else { entry.start_cluster = parent_entry.start_cluster; }
            PFENT_StoreEntryNumericFieldsToBuf(page->p_buf + 32, &entry);
        }
        error = PFSEC_WriteData(volume, page->p_buf, sector + index - 1, 0,
            volume->bpb.bytes_per_sector, &written, 0);
        if (error != 0) { break; }
        if (written != volume->bpb.bytes_per_sector) { error = 0x11; break; }
        index--;
    }
    PFCACHE_FreeDataPage(volume, page);
    if (error != 0) { return error; }
    entry.num_entry_LFNs = lfn_count;
    entry_sector = entry.entry_sector;
    checksum = PFENT_CalcCheckSum(&entry);
    if ((parent_entry.small_letter_flag & 0x18) == 0) {
        next_sector = previous_chain;
        for (lfn_index = lfn_count; lfn_index >= 1; lfn_index--) {
            PFENT_storeLFNEntryFieldsToBuf(entry_buffer, &entry, lfn_index, checksum, lfn_index == lfn_count);
            error = PFSEC_WriteData(volume, entry_buffer, entry_sector, entry.entry_offset, 32, &written, 0);
            if (error != 0) { return error; }
            if (written != 32) { return 0x11; }
            entry.entry_offset += 32;
            if (entry.entry_offset >= volume->bpb.bytes_per_sector) {
                entry.entry_offset = 0;
                entry_sector = *next_sector++;
            }
        }
        entry.entry_sector = entry_sector;
    }
    entry.start_cluster = cluster;
    error = PFENT_updateEntry(&entry, 0);
    if (error != 0) { return error; }
    if (data != 0) {
        data->parent_pos = position + 1;
        pf_strcpy(data->FileName, entry.short_name);
        if ((data->status & 2) == 2) { PFPATH_transformInUnicode(((PF_DTAW*)data)->FileNameW, data->FileName); }
        if (entry.long_name[0] != 0) {
            if ((pf_vol_set.setting & 2) == 2) {
                pf_vol_set.setting = (pf_vol_set.setting & ~3) | 1;
                PFPATH_transformFromUnicodeToNormal(data->LongName, entry.long_name);
                pf_vol_set.setting = (pf_vol_set.setting & ~3) | 2;
            } else { PFPATH_transformFromUnicodeToNormal(data->LongName, entry.long_name); }
            if ((data->status & 2) == 2) { pf_w_strcpy(((PF_DTAW*)data)->LongNameW, entry.long_name); }
            data->check_sum = checksum;
            data->ordinal = 1;
        } else {
            data->LongName[0] = 0;
            if ((data->status & 2) == 2) { ((PF_DTAW*)data)->LongNameW[0] = 0; }
            data->ordinal = 0;
            data->check_sum = 0;
        }
        data->FileSize = entry.file_size;
        data->Time = entry.modify_time;
        data->Date = entry.modify_date;
        data->Attribute = entry.attr;
        data->num_entry_LFNs = entry.num_entry_LFNs;
    }
    return 0;
}


pf_s32 PFDIR_p_chdir(PF_VOLUME* p_vol, PFDIR_STR* p_path_str) {
    pf_s32 err;
    PF_ENT_ITER iter;
    PF_DIR_ENT entry_dir;

    if (((PFSTR_StrNCmp(p_path_str, (pf_s8*)"\\", 1U, 0, 1U) == 0) || (PFSTR_StrNCmp(p_path_str, (pf_s8*)"/", 1U, 0, 1U) == 0)) &&
        (PFSTR_StrNCmp(p_path_str, (pf_s8*)"", 1U, 1, 1U) == 0)) {
        err = PFENT_GetRootDir(p_vol, &entry_dir);
        if (err != 0) {
            return err;
        }
        err = PFVOL_SetCurrentDir(p_vol, &entry_dir);
        if (err != 0) {
            return err;
        }

        return 0;
    }
    if ((PFSTR_StrNumChar(p_path_str, 1U) == 2) && (PFSTR_StrNCmp(p_path_str, (pf_s8*)":", 1U, 1, 1U) == 0)) {
        return 0;
    }
    if ((PFSTR_StrNumChar(p_path_str, 1U) == 3) && (PFSTR_StrNCmp(p_path_str, (pf_s8*)":", 1U, 1, 1U) == 0) &&
        ((PFSTR_StrNCmp(p_path_str, (pf_s8*)"\\", 1U, 2, 1U) == 0) || (PFSTR_StrNCmp(p_path_str, (pf_s8*)"/", 1U, 2, 1U) == 0))) {
        err = PFENT_GetRootDir(p_vol, &entry_dir);
        if (err != 0) {
            return err;
        }
        err = PFVOL_SetCurrentDir(p_vol, &entry_dir);
        if (err != 0) {
            return err;
        }

        return 0;
    }
    if ((PFSTR_StrNCmp(p_path_str, (pf_s8*)":", 1U, 1, 1U) == 0) &&
        ((PFSTR_StrNCmp(p_path_str, (pf_s8*)"\\", 1U, 2, 1U) == 0) || (PFSTR_StrNCmp(p_path_str, (pf_s8*)"/", 1U, 2, 1U) == 0))) {
        PFSTR_MoveStrPos(p_path_str, 2);
    }
    err = PFENT_ITER_GetEntryOfPath(&iter, &entry_dir, p_vol, p_path_str, 0);
    if (err != 0) {
        return err;
    }
    if ((entry_dir.attr & 0x10) == 0) {
        return 0x14;
    }
    err = PFVOL_SetCurrentDir(p_vol, &entry_dir);
    if (err != 0) {
        return err;
    }

    return 0;
}

pf_s32 PFDIR_p_chmod(PF_VOLUME* volume, PFDIR_STR* path, pf_u32 attributes) {
    PFDIR_STR directory_path;
    PFDIR_STR filename;
    PF_ENT_ITER iter;
    PF_DIR_ENT entry;
    PFDIR_VOLUME_DIRS* volume_dirs;
    pf_u16 date;
    pf_u16 time;
    pf_u8 create_time_ms;
    pf_u32 i;
    pf_s32 error;

    error = PFPATH_SplitPath(path, &directory_path, &filename);
    if (error != 0) {
        return error;
    }
    error = PFENT_ITER_GetEntryOfPath(&iter, &entry, volume, path, 0);
    if (error != 0) {
        return error;
    }
    if (((entry.attr & 0x10) != 0 && (attributes & 0x10) == 0) ||
        ((entry.attr & 0x10) == 0 && (attributes & 0x10) != 0)) {
        return 10;
    }
    if ((attributes & 0x40) != 0) {
        attributes = (pf_u8)(attributes & ~0x40);
    }
    if ((entry.attr & 0x10) != 0) {
        volume_dirs = (PFDIR_VOLUME_DIRS*)volume;
        if (directory_is_open(&entry) != 0) { return 0x13; }

        if ((attributes & 4) != 0 && (pf_s32)(attributes & 0xF) != 0xF) {
            return 10;
        }
        attributes |= 0x10;
            entry.attr = attributes;
    } else {
        if (PFFILE_IsOpened(&entry) != 0) {
            return 0x13;
        }
            entry.attr = attributes;
    }
    PFENT_getcurrentDateTimeForEnt(&entry.access_date, &time);
    if (entry.file_size == 0 && (entry.attr & 0x10) == 0) { entry.start_cluster = 0; }
    error = PFENT_updateEntry(&entry, 0);
    if (error != 0) { return error; }
    return 0;
}

pf_s32 PFDIR_p_rmdir(PF_VOLUME* volume, PFDIR_STR* path) {
    PFDIR_STR directory_path;
    PFDIR_STR filename;
    PFDIR_FAT_HINT hint;
    PFDIR_FAT_HINT saved_hint;
    PFDIR_FFD ffd;
    PF_ENT_ITER iter;
    PF_ENT_ITER directory_iter;
    PF_DIR_ENT entry;
    pf_u32 is_empty;
    pf_u32 start_cluster;
    pf_u32 i;
    pf_s32 error;

    error = PFPATH_SplitPath(path, &directory_path, &filename);
    if (error != 0) { return error; }
    error = PFENT_ITER_GetEntryOfPath(&iter, &entry, volume, path, 0);
    if (error != 0) {
        return error;
    }
    directory_iter = iter;
    saved_hint = *iter.ffd.p_hint;
    if ((entry.attr & 0x10) == 0 || (entry.attr & 1) != 0) {
        return 0x14;
    }
    if (directory_is_open(&entry) != 0) { return 0x13; }

    error = PFVOL_CheckCurrentDir(volume, entry.start_cluster);
    if (error != 0 || entry.start_cluster == 1 ||
        (volume->bpb.fat_type == FAT_32 && entry.start_cluster == volume->bpb.root_dir_cluster)) { return 0x1C; }
    PFFAT_InitFFD(&ffd, &hint, volume, &entry.start_cluster);
    iter.ffd = ffd;
    error = PFENT_ITER_IteratorInitialize(&iter, 0);
    if (error != 0) {
        return error;
    }
    error = PFDIR_CheckDirIsEmpty(&iter, &is_empty);
    if (error != 0) {
        return error;
    }
    if (is_empty == 0) {
        return 0x1D;
    }
    start_cluster = entry.start_cluster;
    iter = directory_iter;
    iter.ffd.p_hint = &saved_hint;
    error = PFENT_RemoveEntry(&entry, &iter);
    if (error != 0) {
        return error;
    }
    error = PFFAT_FreeChain(&iter.ffd, start_cluster, -1U, -1U);
    if (error != 0) { return error; }
    return 0;
}

pf_s32 PFDIR_p_fstat(PF_VOLUME* volume, PFDIR_STR* path, PFDIR_FILE_STAT* file_stat) {
    PF_ENT_ITER iter;
    PF_DIR_ENT entry;
    PFDIR_VOLUME_DIRS* volume_dirs = (PFDIR_VOLUME_DIRS*)volume;
    pf_s32 index = 0;
    pf_s32 error;

    error = PFENT_ITER_GetEntryOfPath(&iter, &entry, volume, path, 0);
    if (error != 0) {
        return error;
    }
    if (volume_dirs->num_opened_files != 0) {
        for (index = 0; index < 5; index++) {
            if ((volume_dirs->sfds[index].stat & 1) != 0 && (volume_dirs->sfds[index].stat & 2) != 0 &&
                entry.p_vol == volume_dirs->sfds[index].dir_entry.p_vol &&
                entry.entry_sector == volume_dirs->sfds[index].dir_entry.entry_sector &&
                entry.entry_offset == volume_dirs->sfds[index].dir_entry.entry_offset) {
                file_stat->file_size = volume_dirs->sfds[index].dir_entry.file_size;
                file_stat->attributes = volume_dirs->sfds[index].dir_entry.attr;
                file_stat->modify_time = volume_dirs->sfds[index].dir_entry.modify_time;
                file_stat->modify_date = volume_dirs->sfds[index].dir_entry.modify_date;
                file_stat->access_date = volume_dirs->sfds[index].dir_entry.access_date;
                file_stat->create_time = volume_dirs->sfds[index].dir_entry.create_time;
                file_stat->create_date = volume_dirs->sfds[index].dir_entry.create_date;
                file_stat->small_letter_flag = volume_dirs->sfds[index].dir_entry.create_time_ms;
                break;
            }
        }
    }
    if (volume_dirs->num_opened_files == 0 || index == 5) {
        if ((entry.attr & 0x10) != 0) { file_stat->file_size = 0; }
        else { file_stat->file_size = entry.file_size; }
        file_stat->attributes = entry.attr;
        file_stat->modify_time = entry.modify_time;
        file_stat->modify_date = entry.modify_date;
        file_stat->access_date = entry.access_date;
        file_stat->create_time = entry.create_time;
        file_stat->create_date = entry.create_date;
        file_stat->small_letter_flag = entry.create_time_ms;
    }
    return 0;
}

pf_s32 PFDIR_p_rename(PF_VOLUME* volume, PF_STR* old_path, PF_STR* new_path) {
    PF_DIR_ENT source_entry;
    PF_DIR_ENT destination_entry;
    PF_DIR_ENT source_parent;
    pf_s8 normalized_name[512];
    PF_ENT_ITER source_iter;
    PF_ENT_ITER destination_iter;
    pf_u8 entry_buffer[32];
    PFDIR_STR directory;
    PFDIR_STR source_name;
    PFDIR_STR destination_name;
    PFDIR_FAT_HINT source_hint;
    PFDIR_FAT_HINT destination_hint;
    pf_u32 previous_chain[2];
    pf_u32 written;
    pf_u32 position;
    pf_u32 found;
    pf_u16 time;
    pf_u8 deleted_marker[1] = {0xE5};
    pf_u16 saved_initial_char = 0;
    pf_u32 sector;
    pf_u32* next_sector;
    pf_s32 filename_length;
    pf_s32 parse_error;
    pf_s32 allocation_error = 0;
    pf_s32 error;
    pf_u32 index;
    PF_DIR_ENT* update_entry;

    error = PFPATH_SplitPath((PFDIR_STR*)old_path, &directory, &source_name);
    if (error != 0) { return error; }
    if (PFSTR_GetCodeMode(&source_name) == 2) {
        if ((pf_s32)PFSTR_StrNumChar(&source_name, 1) > 255) { return 1; }
        PFPATH_transformFromUnicodeToNormal(normalized_name,
            (const pf_u16*)PFSTR_GetStrPos(&source_name, 1));
    }
    PFSTR_SetLocalStr(&source_name, (pf_u32)normalized_name);
    error = PFENT_ITER_GetEntryOfPath(&source_iter, &source_parent, volume,
        (PFDIR_STR*)old_path, 1);
    if (error != 0) { return error; }
    PFFAT_InitFFD(&source_iter.ffd, &source_hint, volume, &source_iter.ffd.flags);
    source_iter.ffd.flags = source_parent.start_cluster;
    error = PFENT_ITER_IteratorInitialize(&source_iter, 0);
    if (error != 0) { return error; }
    error = PFENT_ITER_FindEntry(&source_iter, &source_entry, &source_name, 0x7F, 0, &found);
    if (error != 0) { return error; }
    if (found == 0) { return 3; }
    if ((source_entry.attr & 8) != 0) { return 3; }
    if ((source_entry.attr & 1) != 0) { return 0x18; }
    if (PFSTR_StrNCmp((PFDIR_STR*)new_path, (const pf_s8*)":", 1, 1, 1) == 0 &&
        volume != PFPATH_GetVolumeFromPath(new_path)) { return 0x1F; }
    error = PFPATH_SplitPath((PFDIR_STR*)new_path, &directory, &destination_name);
    if (error != 0) { return error; }
    if (PFSTR_GetCodeMode(&destination_name) == 2) {
        if ((pf_s32)PFSTR_StrNumChar(&destination_name, 1) > 255) { return 1; }
        PFPATH_transformFromUnicodeToNormal(normalized_name,
            (const pf_u16*)PFSTR_GetStrPos(&destination_name, 1));
    }
    PFSTR_SetLocalStr(&destination_name, (pf_u32)normalized_name);
    if (PFSTR_GetCodeMode(&destination_name) == 1) {
        const pf_s8* filename = PFSTR_GetStrPos(&destination_name, 1);
        error = pf_strcmp(PFSTR_GetStrPos(&directory, 1), filename);
    } else {
        const pf_u16* filename = (const pf_u16*)PFSTR_GetStrPos(&destination_name, 1);
        error = pf_w_strcmp((const pf_u16*)PFSTR_GetStrPos(&directory, 1), filename);
    }
    if (error != 0) {
        error = PFENT_ITER_GetEntryOfPath(&destination_iter, &destination_entry,
            volume, (PFDIR_STR*)new_path, 1);
        if (error != 0) { return error; }
        if (destination_entry.start_cluster != source_parent.start_cluster) { return 0x20; }
    }
    destination_entry.start_cluster = source_parent.start_cluster;
    PFFAT_InitFFD(&destination_iter.ffd, &destination_hint, volume, &destination_entry.start_cluster);
    error = PFENT_findEntry(&destination_iter.ffd, &destination_entry, 0, &destination_name, 0x7F, 0, 0);
    if (error == 0) { return 8; }
    if (error != 0 && error != 3) { return error; }
    if ((source_entry.attr & 0x10) == 0) {
        if (PFFILE_IsOpened(&source_entry) != 0) { return 0x13; }
    } else {
        if (directory_is_open(&source_entry) != 0) { return 0x13; }
        if (current_directory_is_open(source_entry.p_vol, source_entry.start_cluster) != 0) { return 0x1C; }
        if (PFSTR_StrNCmp(&source_name, (const pf_s8*)"..", 1, 0, 2) == 0) { return 0x1C; }
        if (PFSTR_StrNCmp(&source_name, (const pf_s8*)".\0\0\0\0\0\0", 1, 0, 1) == 0) { return 0x1C; }
        {
            PFDIR_SFD* file = ((PFDIR_VOLUME_DIRS*)volume)->sfds;
            pf_u32 directory_sector = volume->bpb.first_data_sector +
                ((source_entry.start_cluster - 2) << volume->bpb.log2_sectors_per_cluster);
            for (index = 0; index < 5; index++, file++) {
                if ((file->stat & 1) != 0 && (file->stat & 2) != 0) {
                    if (file->dir_entry.p_vol == volume && file->dir_entry.entry_sector == directory_sector) { return 0x13; }
                    found = 0;
                    error = PFENT_ITER_FindCluster(&file->dir_entry, source_entry.start_cluster, &found);
                    if (error != 0) { return error; }
                    if (found != 0) { return 0x13; }
                }
            }
        }
    }
    filename_length = PFSTR_StrNumChar(&destination_name, 1);
    if (filename_length + source_parent.path_len > 0x103) { return 1; }
    if ((source_entry.attr & 0x10) == 0 && filename_length > 255) { return 1; }
    pf_memcpy(&destination_entry, &source_entry, sizeof(PF_DIR_ENT));
    parse_error = PFPATH_parseShortName(destination_entry.short_name, &destination_name);
    if (destination_entry.short_name[0] == 0) { return 2; }
    if (parse_error == 0 && source_entry.num_entry_LFNs == 0) {
        destination_entry.long_name[0] = 0;
        destination_entry.num_entry_LFNs = 0;
        PFENT_getcurrentDateTimeForEnt(&destination_entry.access_date, &time);
        error = PFENT_updateEntry(&destination_entry, 1);
        goto finish_rename;
    }
    if (source_entry.num_entry_LFNs != 0 && (source_entry.small_letter_flag & 0x18) == 0) {
        saved_initial_char = source_entry.long_name[0];
        source_entry.long_name[0] = 0;
        for (index = 1; index <= source_entry.num_entry_LFNs; index++) {
            error = PFENT_ITER_Retreat(&source_iter, 0);
            if (error != 0) { return error; }
            error = PFSEC_WriteData(volume, deleted_marker, source_iter.sector,
                source_iter.offset, 1, &written, 0);
            if (error != 0) { return error; }
            if (written != 1) { return 0x11; }
        }
    }
    error = PFSEC_WriteData(volume, deleted_marker, source_entry.entry_sector,
        source_entry.entry_offset, 1, &written, 0);
    if (error != 0) { return error; }
    if (written != 1) { return 0x11; }
    if ((((PFDIR_VOLUME_DIRS*)volume)->cache.mode & 4) != 0) {
        error = PFCACHE_FlushDataCache(volume);
        if (error != 0) { return error; }
    }
    if (parse_error != 0) {
        error = PFENT_AdjustSFN(&source_parent, destination_entry.short_name);
        if (error != 0) { return error; }
        if (PFSTR_GetCodeMode(&destination_name) == 1) {
            filename_length = PFPATH_transformInUnicode(destination_entry.long_name,
                PFSTR_GetStrPos(&destination_name, 1));
        } else {
            pf_w_strcpy(destination_entry.long_name,
                (const pf_u16*)PFSTR_GetStrPos(&destination_name, 1));
        }
        destination_entry.num_entry_LFNs = filename_length / 13 + (filename_length % 13 != 0);
    } else {
        destination_entry.num_entry_LFNs = 0;
    }
    destination_entry.small_letter_flag = 0;
    PFFAT_InitFFD(&source_iter.ffd, &destination_hint, volume, &source_parent.start_cluster);
    allocation_error = PFENT_allocateEntryPos(&destination_entry, destination_entry.num_entry_LFNs + 1,
        &source_iter.ffd, previous_chain, &destination_name, &position);
    if (allocation_error != 0) {
        if (source_entry.num_entry_LFNs != 0 && (source_entry.small_letter_flag & 0x18) == 0) {
            source_entry.long_name[0] = saved_initial_char;
            source_entry.entry_offset -= (pf_u16)(source_entry.num_entry_LFNs * 32);
        }
        update_entry = &source_entry;
    } else {
        if ((pf_vol_set.setting & 2) == 2) { PFPATH_AdjustExtShortName(destination_entry.short_name, position); }
        destination_entry.check_sum = PFENT_CalcCheckSum(&destination_entry);
        PFENT_getcurrentDateTimeForEnt(&destination_entry.access_date, &time);
        update_entry = &destination_entry;
    }
    index = update_entry->num_entry_LFNs;
    if (index != 0 && (update_entry->small_letter_flag & 0x18) == 0) {
        sector = update_entry->entry_sector;
        next_sector = previous_chain;
        while (index >= 1) {
            PFENT_storeLFNEntryFieldsToBuf(entry_buffer, update_entry, index,
                update_entry->check_sum, index == update_entry->num_entry_LFNs);
            error = PFSEC_WriteData(volume, entry_buffer, sector, update_entry->entry_offset, 32, &written, 0);
            if (error != 0) { return error; }
            if (written != 32) { return 0x11; }
            update_entry->entry_offset += 32;
            if (update_entry->entry_offset >= volume->bpb.bytes_per_sector) {
                update_entry->entry_offset = 0;
                sector = *next_sector++;
            }
            index--;
        }
        update_entry->entry_sector = sector;
    }
    error = PFENT_updateEntry(update_entry, 1);
finish_rename:
    if (error != 0) { allocation_error = error; }
    return allocation_error;
}
pf_s32 PFDIR_p_move(PF_VOLUME* volume, PF_STR* old_path, PF_STR* new_path) {
    PF_DIR_ENT source_entry;
    PF_DIR_ENT destination_entry;
    PF_DIR_ENT destination_parent;
    pf_s8 normalized_name[512];
    PF_ENT_ITER source_iter;
    PF_ENT_ITER destination_iter;
    pf_u8 entry_buffer[32];
    PFDIR_STR directory;
    PFDIR_STR source_name;
    PFDIR_STR destination_name;
    PFDIR_STR parent_name;
    PFDIR_FAT_HINT source_hint;
    PFDIR_FAT_HINT destination_hint;
    pf_u32 previous_chain[2];
    pf_u32 written;
    pf_u32 position;
    pf_u32 found;
    pf_u16 time;
    pf_u8 deleted_marker[4] = {0xE5};
    pf_u16 saved_initial_char = 0;
    pf_u32 sector;
    pf_u32* next_sector;
    pf_s32 filename_length;
    pf_s32 parse_error;
    pf_s32 allocation_error;
    pf_s32 error;
    pf_u32 index;
    pf_u32 lfn_index;
    PF_DIR_ENT* update_entry;

    error = PFENT_ITER_GetEntryOfPath(&source_iter, &source_entry, volume, (PFDIR_STR*)old_path, 0);
    if (error != 0) { return error; }
    if (volume != PFPATH_GetVolumeFromPath(new_path)) { return 0x1F; }
    error = PFPATH_SplitPath((PFDIR_STR*)new_path, &directory, &destination_name);
    if (error != 0) { return error; }
    if (PFSTR_GetCodeMode(&destination_name) == 2) {
        if ((pf_s32)PFSTR_StrNumChar(&destination_name, 1) > 255) { return 1; }
        PFPATH_transformFromUnicodeToNormal(normalized_name,
            (const pf_u16*)PFSTR_GetStrPos(&destination_name, 1));
    }
    PFSTR_SetLocalStr(&destination_name, (pf_u32)normalized_name);
    error = PFENT_ITER_GetEntryOfPath(&destination_iter, &destination_parent, volume, (PFDIR_STR*)new_path, 1);
    if (error != 0) { return error; }
    destination_entry.start_cluster = destination_parent.start_cluster;
    PFFAT_InitFFD(&destination_iter.ffd, &destination_hint, volume, &destination_entry.start_cluster);
    error = PFENT_findEntry(&destination_iter.ffd, &destination_entry, 0, &destination_name, 0x7F, 0, 0);
    if (error == 0) {
        if (destination_entry.entry_sector == source_entry.entry_sector &&
            destination_entry.entry_offset == source_entry.entry_offset) { return 0; }
        return 8;
    }
    if (error != 0 && error != 3) { return error; }
    if ((source_entry.attr & 0x10) == 0) {
        if (PFFILE_IsOpened(&source_entry) != 0) { return 0x13; }
    } else {
        if (directory_is_open(&source_entry) != 0) { return 0x13; }
        if (current_directory_is_open(source_entry.p_vol, source_entry.start_cluster) != 0) { return 0x1C; }
        error = PFPATH_SplitPath((PFDIR_STR*)old_path, &directory, &source_name);
        if (error != 0) { return error; }
        if (PFSTR_StrNCmp(&source_name, (const pf_s8*)"..", 1, 0, 2) == 0) { return 10; }
        if (PFSTR_StrNCmp(&source_name, (const pf_s8*)".\0\0\0\0\0\0", 1, 0, 1) == 0) { return 10; }
        {
            PFDIR_SFD* file = ((PFDIR_VOLUME_DIRS*)volume)->sfds;
            pf_u32 directory_sector = volume->bpb.first_data_sector +
                ((source_entry.start_cluster - 2) << volume->bpb.log2_sectors_per_cluster);
            for (index = 0; index < 5; index++, file++) {
                if ((file->stat & 1) != 0 && (file->stat & 2) != 0) {
                    if (file->dir_entry.p_vol == volume && file->dir_entry.entry_sector == directory_sector) { return 0x13; }
                    found = 0;
                    error = PFENT_ITER_FindCluster(&file->dir_entry, source_entry.start_cluster, &found);
                    if (error != 0) { return error; }
                    if (found != 0) { return 0x13; }
                }
            }
        }
        destination_entry.start_cluster = destination_parent.start_cluster;
        for (;;) {
            pf_u32 parent_cluster;
            if (destination_entry.start_cluster == 1 || destination_entry.start_cluster == 0) { break; }
            PFFAT_InitFFD(&destination_iter.ffd, &destination_hint, volume, &destination_entry.start_cluster);
            PFSTR_InitStr(&parent_name, (const pf_s8*)"..", 1);
            PFSTR_SetLocalStr(&parent_name, 0);
            error = PFENT_findEntry(&destination_iter.ffd, &destination_entry, 0, &parent_name, 0x7F, 0, 0);
            if (error != 0) { return error; }
            parent_cluster = destination_entry.start_cluster;
            if (parent_cluster == 1 || parent_cluster == 0) { break; }
            PFFAT_ResetFFD(&destination_iter.ffd, &destination_entry.start_cluster);
            error = PFENT_ITER_IteratorInitialize(&destination_iter, 0);
            if (error != 0) { return error; }
            error = PFENT_ITER_FindDirEntryFromCluster(&destination_iter, &destination_entry, parent_cluster, &found);
            if (error == 0) {
                if (destination_entry.start_cluster == source_entry.start_cluster) { return 10; }
            } else if (error != 0) { return error; }
        }
    }
    filename_length = PFSTR_StrNumChar(&destination_name, 1);
    if (filename_length + destination_parent.path_len > 0x103) { return 1; }
    if ((source_entry.attr & 0x10) == 0 && filename_length > 255) { return 1; }
    pf_memcpy(&destination_entry, &source_entry, sizeof(PF_DIR_ENT));
    parse_error = PFPATH_parseShortName(destination_entry.short_name, &destination_name);
    if (destination_entry.short_name[0] == 0) { return 2; }
    if (source_entry.num_entry_LFNs != 0 && (source_entry.small_letter_flag & 0x18) == 0) {
        saved_initial_char = source_entry.long_name[0];
        source_entry.long_name[0] = 0;
        for (index = 1; index <= source_entry.num_entry_LFNs; index++) {
            error = PFENT_ITER_Retreat(&source_iter, 0);
            if (error != 0) { return error; }
            error = PFSEC_WriteData(volume, deleted_marker, source_iter.sector,
                source_iter.offset, 1, &written, 0);
            if (error != 0) { return error; }
            if (written != 1) { return 0x11; }
        }
    }
    error = PFSEC_WriteData(volume, deleted_marker, source_entry.entry_sector,
        source_entry.entry_offset, 1, &written, 0);
    if (error != 0) { return error; }
    if (written != 1) { return 0x11; }
    if ((((PFDIR_VOLUME_DIRS*)volume)->cache.mode & 4) != 0) {
        error = PFCACHE_FlushDataCache(volume);
        if (error != 0) { return error; }
    }
    if (parse_error != 0) {
        error = PFENT_AdjustSFN(&destination_parent, destination_entry.short_name);
        if (error != 0) { return error; }
        if (PFSTR_GetCodeMode(&destination_name) == 1) {
            filename_length = PFPATH_transformInUnicode(destination_entry.long_name,
                PFSTR_GetStrPos(&destination_name, 1));
        } else {
            pf_w_strcpy(destination_entry.long_name,
                (const pf_u16*)PFSTR_GetStrPos(&destination_name, 1));
        }
        destination_entry.num_entry_LFNs = filename_length / 13 + (filename_length % 13 != 0);
    } else {
        destination_entry.num_entry_LFNs = 0;
    }
    destination_entry.small_letter_flag = 0;
    PFFAT_InitFFD(&destination_iter.ffd, &source_hint, volume, &destination_parent.start_cluster);
    allocation_error = PFENT_allocateEntryPos(&destination_entry, destination_entry.num_entry_LFNs + 1,
        &destination_iter.ffd, previous_chain, &destination_name, &position);
    if (allocation_error != 0) {
        if (source_entry.num_entry_LFNs != 0 && (source_entry.small_letter_flag & 0x18) == 0) {
            source_entry.long_name[0] = saved_initial_char;
            source_entry.entry_offset -= (source_entry.num_entry_LFNs & 0xff) * 32;
        }
        update_entry = &source_entry;
    } else {
        if ((pf_vol_set.setting & 2) == 2) { PFPATH_AdjustExtShortName(destination_entry.short_name, position); }
        destination_entry.check_sum = PFENT_CalcCheckSum(&destination_entry);
        PFENT_getcurrentDateTimeForEnt(&destination_entry.access_date, &time);
        update_entry = &destination_entry;
        if ((source_entry.attr & 0x10) != 0) {
            PFFAT_InitFFD(&source_iter.ffd, &source_hint, volume, &source_entry.start_cluster);
            PFSTR_InitStr(&parent_name, (const pf_s8*)"..", 1);
            PFSTR_SetLocalStr(&parent_name, 0);
            error = PFENT_findEntry(&source_iter.ffd, &source_entry, 0, &parent_name, 0x7F, 0, 0);
            if (error != 0) { return error; }
            if (destination_parent.start_cluster == 1 || destination_parent.start_cluster == 0 ||
                (destination_parent.start_cluster == 2 && volume->bpb.fat_type == FAT_32)) {
                source_entry.start_cluster = 0;
            } else { source_entry.start_cluster = destination_parent.start_cluster; }
            error = PFENT_updateEntry(&source_entry, 1);
            if (error != 0) { return error; }
            if ((((PFDIR_VOLUME_DIRS*)volume)->cache.mode & 4) != 0) {
                error = PFCACHE_FlushDataCache(volume);
                if (error != 0) { return error; }
            }
        }
    }
    lfn_index = update_entry->num_entry_LFNs;
    if (lfn_index != 0 && (update_entry->small_letter_flag & 0x18) == 0) {
        sector = update_entry->entry_sector;
        next_sector = previous_chain;
        while (lfn_index >= 1) {
            PFENT_storeLFNEntryFieldsToBuf(entry_buffer, update_entry, lfn_index,
                update_entry->check_sum, lfn_index == update_entry->num_entry_LFNs);
            error = PFSEC_WriteData(volume, entry_buffer, sector, update_entry->entry_offset, 32, &written, 0);
            if (error != 0) { return error; }
            if (written != 32) { return 0x11; }
            update_entry->entry_offset += 32;
            if (update_entry->entry_offset >= volume->bpb.bytes_per_sector) {
                update_entry->entry_offset = 0;
                sector = *next_sector++;
            }
            lfn_index--;
        }
        update_entry->entry_sector = sector;
    }
    error = PFENT_updateEntry(update_entry, 1);
    if (error != 0) { allocation_error = error; }
    return allocation_error;
}

pf_s32 PFDIR_p_fsexec_remove(PF_DTA* data, PF_DIR_ENT* entry, PF_ENT_ITER* iter) {
    PFDIR_VOLUME_DIRS* volume_dirs = (PFDIR_VOLUME_DIRS*)entry->p_vol;
    PFDIR_FAT_HINT hint;
    PF_ENT_ITER directory_iter;
    pf_u32 is_empty;
    pf_s32 index = 0;
    pf_u32 start_cluster;
    pf_u32 chain_size;
    pf_s32 error;

    if ((entry->attr & 1) != 0) {
        return 0x18;
    }
    if ((entry->attr & 0x10) != 0) {
        if (PFVOL_CheckCurrentDir(entry->p_vol, entry->start_cluster) != 0 || entry->start_cluster == 1 ||
            (entry->p_vol->bpb.fat_type == FAT_32 &&
             entry->start_cluster == entry->p_vol->bpb.root_dir_cluster)) {
            return 0x1C;
        }
        if (directory_is_open(entry) != 0) { return 0x13; }

        directory_iter = *iter;
        hint = *iter->ffd.p_hint;
        PFFAT_ResetFFD(&iter->ffd, &entry->start_cluster);
        error = PFENT_ITER_IteratorInitialize(iter, 0);
        if (error != 0) {
            return error;
        }
        error = PFDIR_CheckDirIsEmpty(iter, &is_empty);
        if (error != 0) {
            return error;
        }
        if (is_empty == 0) {
            return 0x1D;
        }
        *iter = directory_iter;
        iter->ffd.p_hint = &hint;
        chain_size = -1U;
    } else {
        if (PFFILE_IsOpened(entry) != 0) { return 0x13; }
        chain_size = entry->file_size;
    }
    start_cluster = entry->start_cluster;
    entry->num_entry_LFNs = data->num_entry_LFNs;
    entry->ordinal = data->ordinal;
    entry->check_sum = data->check_sum;
    error = PFENT_RemoveEntry(entry, iter);
    if (error != 0) {
        return error;
    }
    return release_directory_chain(&iter->ffd, start_cluster, chain_size);
}


pf_s32 PFDIR_p_fsexec_chmod(PF_DTA* data, PF_DIR_ENT* entry, pf_u32 mode, pf_u32 attributes) {
    PFDIR_VOLUME_DIRS* volume_dirs = (PFDIR_VOLUME_DIRS*)entry->p_vol;
    pf_u16 date;
    pf_u16 time;
    pf_u8 create_time_ms;
    pf_s32 index = 0;
    pf_s32 error;

    if ((attributes & 0x40) != 0) {
        attributes = (pf_u8)(attributes & ~0x40);
    }
    if ((entry->attr & 0x10) != 0) {
        if ((attributes & 4) != 0) {
            return 10;
        }
        if (directory_is_open(entry) != 0) { return 0x13; }

        entry->attr = attributes | 0x10;
        } else {
        if ((attributes & 0x10) != 0) {
            return 10;
        }
        if (PFFILE_IsOpened(entry) != 0) {
            return 0x13;
        }
        entry->attr = attributes;
        }
    PFENT_getcurrentDateTimeForEnt(&entry->access_date, &time);
    error = PFENT_updateEntry(entry, 0);
    if (error != 0) {
        return error;
    }
    if ((mode & 0x80000000) == 0) {
        data->Attribute = entry->attr;
    }
    error = PFCACHE_FlushDataCacheSpecific(entry->p_vol, 0);
    if (error != 0) { return error; }
    return 0;
}

pf_s32 PFDIR_p_fsexec_fopen(PF_DTA* data, PF_DIR_ENT* entry, PF_ENT_ITER* iter, pf_u32 flags,
                            pf_u32 mode) {
    pf_s8 long_name[13];
    pf_s32 error;

    if ((flags & 0x80000000) != 0) {
        entry->num_entry_LFNs = data->num_entry_LFNs;
        entry->ordinal = data->ordinal;
        entry->check_sum = data->check_sum;
        if ((iter->buf[0xC] & 0x18) != 0) {
            PFPATH_getLongNameformShortName(entry->short_name, long_name, iter->buf[0xC]);
            PFPATH_transformInUnicode(entry->long_name, long_name);
        } else {
            error = PFENT_ITER_GetLFNEntryName(iter);
            if (error != 0) {
                return error;
            }
        }
    }
    error = PFFILE_FsexecOpenFile(entry, iter, mode, data);
    if (error != 0) {
        return error;
    }
    error = 0;
    ((PFDIR_VOLUME_DIRS*)data->p_vol)->num_opened_files++;
    return error;
}

pf_s32 PFDIR_p_fsexec_opendir(PF_DTA* data, PF_DIR_ENT* entry, PF_ENT_ITER* iter, pf_u32 flags) {
    pf_s8 long_name[13];
    pf_s32 error;

    if ((flags & 0x80000000) != 0) {
        entry->num_entry_LFNs = data->num_entry_LFNs;
        entry->ordinal = data->ordinal;
        entry->check_sum = data->check_sum;
        if ((iter->buf[0xC] & 0x18) != 0) {
            PFPATH_getLongNameformShortName(entry->short_name, long_name, iter->buf[0xC]);
            PFPATH_transformInUnicode(entry->long_name, long_name);
        } else {
            error = PFENT_ITER_GetLFNEntryName(iter);
            if (error != 0) {
                return error;
            }
        }
    }
    error = PFDIR_DoFsexecOpenDir(entry, iter, (PFDIR_DIR**)&data->p_dir);
    if (error != 0) {
        return error;
    }
    error = 0;
    ((PFDIR_VOLUME_DIRS*)data->p_vol)->num_opened_directories++;
    return error;
}
pf_s32 PFDIR_p_fsexec(PF_DTA* data, pf_u32 flags, pf_u32 mode) {
    PF_DIR_ENT entry;
    PF_ENT_ITER iter;
    PFDIR_FFD ffd;
    PFDIR_FAT_HINT hint;
    pf_s8 dot_name[11];
    PFDIR_STR pattern;
    PFDIR_STR long_pattern;
    pf_u32 found;
    pf_u32 start_position;
    pf_u32 attr_flags = flags & 6;
    pf_u32 direct;
    pf_s32 error;

    if (attr_flags != 0 || (flags & 1) != 0 || (flags & 0x10) != 0 || (flags & 0x20) != 0) {
        if (attr_flags != 0 || (flags & 1) != 0 || ((flags & 0x10) != 0 && mode != 2)) {
            error = PFVOL_CheckForWrite(data->p_vol);
            if (error != 0) { return error; }
        }
        entry.short_name[0] = 0;
        entry.start_cluster = data->parent_start_cluster;
        PFFAT_InitFFD(&ffd, &hint, data->p_vol, &entry.start_cluster);
        iter.ffd = ffd;
        direct = flags & 0x80000000;
        start_position = data->parent_pos - 1;
        if (direct == 0) { start_position -= data->num_entry_LFNs; }
        error = PFENT_ITER_IteratorInitialize(&iter, start_position);
        if (error != 0) { return error; }
        if (direct == 0) {
            if ((data->status & 1) == 1) {
                error = PFSTR_InitStr(&pattern, data->FileName, 1);
            } else if ((pf_vol_set.setting & 2) == 2) {
                error = PFSTR_InitStr(&pattern, (const pf_s8*)((PF_DTAW*)data)->LongNameW, 2);
            } else {
                error = PFSTR_InitStr(&pattern, (const pf_s8*)((PF_DTAW*)data)->FileNameW, 2);
            }
            if (error != 0) { return error; }
            if ((pf_vol_set.setting & 2) == 2) {
                PFSTR_SetLocalStr(&pattern, (pf_u32)data->LongName);
            } else { PFSTR_SetLocalStr(&pattern, (pf_u32)data->FileName); }
            error = PFENT_ITER_FindEntryNoPathCheck(&iter, &entry, &pattern, 0x7F, 0, &found);
            if (error != 0) { return error; }
            if ((data->status & 2) != 2 || (pf_vol_set.setting & 2) != 2) {
                if (PFPATH_cmpName(entry.short_name, &pattern, 1) != 0) { return 3; }
            }
            error = PFSTR_InitStr(&long_pattern, data->LongName, 1);
            if (error != 0) { return error; }
            PFSTR_SetLocalStr(&long_pattern, (pf_u32)data->LongName);
            if (PFPATH_cmpNameUni(entry.long_name, &long_pattern) != 0) { return 3; }
        } else {
            if (iter.buf[0] == 0 || iter.buf[0] == 0xE5) { return 3; }
            if ((flags & 0x20) == 0 && (iter.buf[11] & 0x18) != 0) { return 3; }
            if ((flags & 0x20) != 0 && ((iter.buf[11] & 0x10) == 0 || (iter.buf[11] & 8) != 0)) { return 0x14; }
            error = PFENT_ITER_GetEntryOfIter(&iter, &entry);
            if (error != 0) { return error; }
        }
        set_dot_entry((pf_u8*)dot_name);
        if (pf_strncmp(entry.short_name, dot_name, 1) == 0) { return 0x1C; }
        set_dot_dot_entry((pf_u8*)dot_name);
        if (pf_strncmp(entry.short_name, dot_name, 2) == 0) { return 0x1C; }
        if (attr_flags != 0) {
            error = PFDIR_p_fsexec_chmod(data, &entry, flags, mode);
        } else if ((flags & 1) != 0) {
            error = PFDIR_p_fsexec_remove(data, &entry, &iter);
        } else if ((flags & 0x10) != 0) {
            error = PFDIR_p_fsexec_fopen(data, &entry, &iter, flags, mode);
        } else {
            if ((flags & 0x20) != 0) { error = PFDIR_p_fsexec_opendir(data, &entry, &iter, flags); }
        }
        goto done;
    }
    return 10;
done:
    return error;
}


void PFDIR_FinalizeAllDirs(PF_VOLUME* volume) {
    PFDIR_VOLUME_DIRS* volume_dirs = (PFDIR_VOLUME_DIRS*)volume;
    pf_u16 index;

    for (index = 0; index < 3; index++) {
        volume_dirs->sdds[index].stat = 0;
        PFFAT_FinalizeFFD((PF_FFD*)&volume_dirs->sdds[index].ffd);
    }
    volume_dirs->udds[0].stat &= ~1;
    volume_dirs->udds[1].stat &= ~1;
    volume_dirs->udds[2].stat &= ~1;
    volume_dirs->num_opened_directories = 0;
}

void PFDIR_fsfirst(PF_STR* path, pf_u8 attributes, PF_DTA* data) {
    PF_VOLUME* volume = PFPATH_GetVolumeFromPath(path);
    pf_s32 error = PFVOL_CheckForRead(volume);

    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        return;
    }
    error = PFDIR_p_fsfirst(volume, path, attributes, data);
    if (error != 0) {
        data->p_vol = 0;
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
    }
}

void PFDIR_fsnext(PF_DTA* data) {
    PF_VOLUME* volume = data->p_vol;
    pf_s32 error = PFVOL_CheckForRead(volume);

    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        return;
    }
    error = PFDIR_p_fsnext(data);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
    }
}

void PFDIR_fsexec(PF_DTA* data, pf_u32 flags, pf_u32 mode) {
    PF_VOLUME* volume = data->p_vol;
    PFDIR_VOLUME_DIRS* volume_dirs = (PFDIR_VOLUME_DIRS*)volume;
    pf_s32 error = PFVOL_CheckForRead(volume);

    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        return;
    }
    volume_dirs->cache.signature = 0;
    error = PFDIR_p_fsexec(data, flags, mode);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
    } else {
        error = PFCACHE_FlushFATCache(volume);
        if (error != 0) {
            pf_vol_set.last_error = error;
            ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        }
    }
    volume_dirs->cache.signature = 0;
}

void PFDIR_fstat(PF_STR* path, PFDIR_FILE_STAT* file_stat) {
    PF_VOLUME* volume = PFPATH_GetVolumeFromPath(path);
    pf_s32 error = PFVOL_CheckForRead(volume);

    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        return;
    }
    error = PFDIR_p_fstat(volume, (PFDIR_STR*)path, file_stat);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
    }
}

void PFDIR_rename(PF_STR* old_path, PF_STR* new_path) {
    PF_VOLUME* volume = PFPATH_GetVolumeFromPath(old_path);
    PFDIR_VOLUME_DIRS* volume_dirs = (PFDIR_VOLUME_DIRS*)volume;
    pf_s32 error = PFVOL_CheckForWrite(volume);

    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        return;
    }
    volume_dirs->cache.signature = 0;
    error = PFDIR_p_rename(volume, old_path, new_path);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
    } else {
        error = PFCACHE_FlushFATCache(volume);
        if (error != 0) {
            pf_vol_set.last_error = error;
            ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        } else {
            error = PFCACHE_FlushDataCacheSpecific(volume, 0);
            if (error != 0) {
                pf_vol_set.last_error = error;
                ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
            }
        }
    }
    volume_dirs->cache.signature = 0;
}

void PFDIR_move(PF_STR* old_path, PF_STR* new_path) {
    PF_VOLUME* volume = PFPATH_GetVolumeFromPath(old_path);
    PFDIR_VOLUME_DIRS* volume_dirs = (PFDIR_VOLUME_DIRS*)volume;
    pf_s32 error = PFVOL_CheckForWrite(volume);

    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        return;
    }
    volume_dirs->cache.signature = 0;
    error = PFDIR_p_move(volume, old_path, new_path);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
    } else {
        error = PFCACHE_FlushFATCache(volume);
        if (error != 0) {
            pf_vol_set.last_error = error;
            ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        } else {
            error = PFCACHE_FlushDataCacheSpecific(volume, 0);
            if (error != 0) {
                pf_vol_set.last_error = error;
                ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
            }
        }
    }
    volume_dirs->cache.signature = 0;
}

pf_s32 PFDIR_opendir(PF_STR* path, PFDIR_DIR** dir) {
    PF_VOLUME* volume = PFPATH_GetVolumeFromPath(path);
    PFDIR_VOLUME_DIRS* volume_dirs = (PFDIR_VOLUME_DIRS*)volume;
    pf_s32 error = PFVOL_CheckForRead(volume);

    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        return error;
    }
    error = PFDIR_p_opendir(volume, (PFDIR_STR*)path, dir);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
    } else {
        ((PFDIR_VOLUME_DIRS*)volume)->num_opened_directories += 1;
    }
    return error;
}

pf_s32 PFDIR_closedir(PFDIR_DIR* dir) {
    PF_VOLUME* volume = dir == 0 ? 0 : dir->p_sdd->dir_entry.p_vol;
    PFDIR_VOLUME_DIRS* volume_dirs = (PFDIR_VOLUME_DIRS*)volume;
    pf_s32 error = PFVOL_CheckForRead(volume);

    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        return error;
    }
    if ((dir->p_sdd->stat & 1) == 0 || (dir->p_sdd->stat & 2) == 0) {
        error = 10;
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        return error;
    }
    if (--dir->p_sdd->num_handlers == 0) {
        dir->p_sdd->stat &= ~1;
    }
    dir->stat &= ~1;
    volume_dirs->num_opened_directories--;
    return 0;
}

pf_s32 PFDIR_readdir(PFDIR_DIR* dir, PFDIR_READ_RESULT* result) {
    PF_VOLUME* volume = dir == 0 ? 0 : dir->p_sdd->dir_entry.p_vol;
    pf_s32 error = PFVOL_CheckForWrite(volume);

    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        return error;
    }
    if ((dir->p_sdd->stat & 1) == 0 || (dir->p_sdd->stat & 2) == 0) {
        error = 10;
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        return error;
    }
    error = PFDIR_p_readdir(dir, result);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
    }
    return error;
}

pf_s32 PFDIR_telldir(PFDIR_DIR* dir, pf_u32* position) {
    PF_VOLUME* volume = dir == 0 ? 0 : dir->p_sdd->dir_entry.p_vol;
    PFDIR_SDD* sdd;
    pf_s32 error = PFVOL_CheckForWrite(volume);

    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
    } else {
        sdd = dir->p_sdd;
        if ((sdd->stat & 1) == 0 || (sdd->stat & 2) == 0) {
            pf_vol_set.last_error = 10;
            ((PFDIR_VOLUME_DIRS*)volume)->last_error = 10;
            error = 10;
        } else if (dir->end_position != 0) {
            *position = dir->end_position;
        } else {
            *position = dir->next_position;
        }
    }
    return error;
}

pf_s32 PFDIR_seekdir(PFDIR_DIR* dir, pf_u32 position) {
    PF_VOLUME* volume = dir == 0 ? 0 : dir->p_sdd->dir_entry.p_vol;
    pf_s32 error = PFVOL_CheckForWrite(volume);

    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
    } else if ((dir->p_sdd->stat & 1) == 0 || (dir->p_sdd->stat & 2) == 0) {
        pf_vol_set.last_error = 10;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = 10;
        error = 10;
    } else {
        dir->end_position = position;
    }
    return error;
}

void PFDIR_rmdir(PF_STR* path) {
    PF_VOLUME* volume = PFPATH_GetVolumeFromPath(path);
    PFDIR_VOLUME_DIRS* volume_dirs = (PFDIR_VOLUME_DIRS*)volume;
    pf_s32 error = PFVOL_CheckForWrite(volume);

    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        return;
    }
    volume_dirs->cache.signature = 0;
    error = PFDIR_p_rmdir(volume, (PFDIR_STR*)path);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
    } else {
        error = PFCACHE_FlushFATCache(volume);
        if (error != 0) {
            pf_vol_set.last_error = error;
            ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        }
    }
    volume_dirs->cache.signature = 0;
}

void PFDIR_mkdir(PF_STR* path) {
    PF_VOLUME* volume = PFPATH_GetVolumeFromPath(path);
    PFDIR_VOLUME_DIRS* volume_dirs = (PFDIR_VOLUME_DIRS*)volume;
    pf_s32 error = PFVOL_CheckForWrite(volume);

    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        return;
    }
    volume_dirs->cache.signature = 0;
    error = PFDIR_p_mkdir(volume, path, 0, 0);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
    } else {
        error = PFCACHE_FlushFATCache(volume);
        if (error != 0) {
            pf_vol_set.last_error = error;
            ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        } else {
            error = PFCACHE_FlushDataCacheSpecific(volume, 0);
            if (error != 0) {
                pf_vol_set.last_error = error;
                ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
            }
        }
    }
    volume_dirs->cache.signature = 0;
}

void PFDIR_createdir(PF_STR* path, pf_u32 option, PF_DTA* data) {
    PF_VOLUME* volume = PFPATH_GetVolumeFromPath(path);
    PFDIR_VOLUME_DIRS* volume_dirs = (PFDIR_VOLUME_DIRS*)volume;
    pf_s32 error = PFVOL_CheckForWrite(volume);

    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        return;
    }
    volume_dirs->cache.signature = 0;
    error = PFDIR_p_mkdir(volume, path, option, data);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
    } else {
        error = PFCACHE_FlushFATCache(volume);
        if (error != 0) {
            pf_vol_set.last_error = error;
            ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        } else {
            error = PFCACHE_FlushDataCacheSpecific(volume, 0);
            if (error != 0) {
                pf_vol_set.last_error = error;
                ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
            }
        }
    }
    volume_dirs->cache.signature = 0;
}

pf_s32 PFDIR_chdir(PF_STR* path) {
    PF_VOLUME* volume = PFPATH_GetVolumeFromPath(path);
    pf_s32 error = PFVOL_CheckForRead(volume);

    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        return error;
    }
    error = PFDIR_p_chdir(volume, (PFDIR_STR*)path);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
    } else {
        PFVOL_SetCurrentVolume(volume);
    }
    return error;
}

static inline pf_s32 set_directory_context(PF_VOLUME* volume, PF_DIR_ENT* entry) {
    pf_s32 error = PFVOL_SetCurrentDir(volume, entry);
    if (error != 0) { return error; }
    return 0;
}

pf_s32 PFDIR_fchdir(PFDIR_DIR* dir) {
    PF_VOLUME* volume = dir == 0 ? 0 : dir->p_sdd->dir_entry.p_vol;
    pf_s32 error = PFVOL_CheckForRead(volume);

    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        return error;
    }
    if ((dir->p_sdd->stat & 1) == 0 || (dir->p_sdd->stat & 2) == 0) {
        error = 10;
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        return error;
    }
    error = set_directory_context(volume, &dir->p_sdd->dir_entry);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
    } else {
        PFVOL_SetCurrentVolume(volume);
    }
    return error;
}

void PFDIR_chmod(PF_STR* path, pf_u8 attributes) {
    PF_VOLUME* volume = PFPATH_GetVolumeFromPath(path);
    PFDIR_VOLUME_DIRS* volume_dirs = (PFDIR_VOLUME_DIRS*)volume;
    pf_s32 error = PFVOL_CheckForWrite(volume);

    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        return;
    }
    volume_dirs->cache.signature = 0;
    error = PFDIR_p_chmod(volume, (PFDIR_STR*)path, attributes);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
    } else {
        error = PFCACHE_FlushFATCache(volume);
        if (error != 0) {
            pf_vol_set.last_error = error;
            ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        } else {
            error = PFCACHE_FlushDataCacheSpecific(volume, 0);
            if (error != 0) {
                pf_vol_set.last_error = error;
                ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
            }
        }
    }
    volume_dirs->cache.signature = 0;
}

void PFDIR_chdmod(PF_STR* path, pf_u8 attributes) {
    PF_VOLUME* volume = PFPATH_GetVolumeFromPath(path);
    PFDIR_VOLUME_DIRS* volume_dirs = (PFDIR_VOLUME_DIRS*)volume;
    pf_s32 error = PFVOL_CheckForWrite(volume);

    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        return;
    }
    volume_dirs->cache.signature = 0;
    error = PFDIR_p_chmod(volume, (PFDIR_STR*)path, (pf_u8)(attributes | 0x10));
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
    } else {
        error = PFCACHE_FlushFATCache(volume);
        if (error != 0) {
            pf_vol_set.last_error = error;
            ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        } else {
            error = PFCACHE_FlushDataCacheSpecific(volume, 0);
            if (error != 0) {
                pf_vol_set.last_error = error;
                ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
            }
        }
    }
    volume_dirs->cache.signature = 0;
}

pf_s32 PFDIR_p_fsnext(PF_DTA* data) {
    PFDIR_FFD ffd;
    PFDIR_FAT_HINT hint;
    PF_DIR_ENT entry;
    PFDIR_STR pattern;
    pf_u32 logical_position = 0;
    pf_u32 entry_position = 0;
    pf_u32 code_mode;
    pf_s32 index = 0;
    pf_s32 error;

    if ((data->status & 1) == 1) {
        code_mode = 1;
        error = PFSTR_InitStr(&pattern, data->reg_exp, code_mode);
    } else {
        code_mode = 2;
        error = PFSTR_InitStr(&pattern, (const pf_s8*)((PF_DTAW*)data)->reg_expW, code_mode);
    }
    if (error != 0) {
        return error;
    }
    PFSTR_SetLocalStr(&pattern, (pf_u32)data->reg_exp);
    while (entry_position < 999999) {
        if (data->parent_pos >= 999999) { return 10; }
        entry.start_cluster = data->parent_start_cluster;
        PFFAT_InitFFD(&ffd, &hint, data->p_vol, &entry.start_cluster);
        error = PFENT_findEntryPos(&ffd, &entry, data->parent_pos, &pattern, data->attr, 0,
                                   &logical_position, &entry_position);
        if (error != 0) { return error; }
        data->parent_pos = entry_position + 1;
        if (entry_position == 999999) { return 3; }
        else { break; }
    }
    pf_strcpy(data->FileName, entry.short_name);
    if ((data->status & 2) == 2) {
        PFPATH_transformInUnicode(((PF_DTAW*)data)->FileNameW, data->FileName);
    }
    if (entry.long_name[0] != 0) {
        if ((pf_vol_set.setting & 2) == 2) {
            pf_vol_set.setting &= 0xFFFFFFFC;
            pf_vol_set.setting |= 1;
            PFPATH_transformFromUnicodeToNormal(data->LongName, entry.long_name);
            pf_vol_set.setting &= 0xFFFFFFFC;
            pf_vol_set.setting |= 2;
        } else {
            PFPATH_transformFromUnicodeToNormal(data->LongName, entry.long_name);
        }
        if ((data->status & 2) == 2) {
            pf_w_strcpy(((PF_DTAW*)data)->LongNameW, entry.long_name);
        }
    } else {
        data->LongName[0] = 0;
        if ((data->status & 2) == 2) {
            ((PF_DTAW*)data)->LongNameW[0] = 0;
        }
    }
    if (((PFDIR_VOLUME_DIRS*)data->p_vol)->num_opened_files != 0) {
        for (index = 0; index < 5; index++) {
            if ((((PFDIR_VOLUME_DIRS*)data->p_vol)->sfds[index].stat & 1) != 0 && (((PFDIR_VOLUME_DIRS*)data->p_vol)->sfds[index].stat & 2) != 0 &&
                entry.p_vol == ((PFDIR_VOLUME_DIRS*)data->p_vol)->sfds[index].dir_entry.p_vol &&
                ((PFDIR_VOLUME_DIRS*)data->p_vol)->sfds[index].dir_entry.entry_sector == entry.entry_sector &&
                ((PFDIR_VOLUME_DIRS*)data->p_vol)->sfds[index].dir_entry.entry_offset == entry.entry_offset) {
                data->FileSize = ((PFDIR_VOLUME_DIRS*)data->p_vol)->sfds[index].dir_entry.file_size;
                data->Time = ((PFDIR_VOLUME_DIRS*)data->p_vol)->sfds[index].dir_entry.modify_time;
                data->Date = ((PFDIR_VOLUME_DIRS*)data->p_vol)->sfds[index].dir_entry.modify_date;
                data->Attribute = ((PFDIR_VOLUME_DIRS*)data->p_vol)->sfds[index].dir_entry.attr;
                data->num_entry_LFNs = ((PFDIR_VOLUME_DIRS*)data->p_vol)->sfds[index].dir_entry.num_entry_LFNs;
                data->ordinal = ((PFDIR_VOLUME_DIRS*)data->p_vol)->sfds[index].dir_entry.ordinal;
                data->check_sum = ((PFDIR_VOLUME_DIRS*)data->p_vol)->sfds[index].dir_entry.check_sum;
                break;
            }
        }
    }
    if (((PFDIR_VOLUME_DIRS*)data->p_vol)->num_opened_files == 0 || index == 5) {
        data->FileSize = entry.file_size;
        data->Time = entry.modify_time;
        data->Date = entry.modify_date;
        data->Attribute = entry.attr;
        data->num_entry_LFNs = entry.num_entry_LFNs;
        data->ordinal = entry.ordinal;
        data->check_sum = entry.check_sum;
    }
    return 0;
}

pf_s32 PFDIR_p_fsfirst(PF_VOLUME* volume, PF_STR* path, pf_u8 attributes, PF_DTA* data) {
    PFDIR_STR directory;
    PFDIR_STR pattern;
    PF_DIR_ENT entry;
    PF_ENT_ITER iter;
    pf_s32 error;

    error = PFPATH_SplitPathPattern(path, &directory, &pattern);
    if (error != 0) {
        return error;
    }
    error = PFENT_ITER_GetEntryOfPattern(&iter, &entry, volume, &directory);
    if (error != 0) {
        return error;
    }
    if ((entry.attr & 0x10) == 0) {
        return 0x14;
    }
    data->parent_start_cluster = entry.start_cluster;
    data->parent_pos = 0;
    data->p_vol = entry.p_vol;
    data->attr = attributes;
    data->status = 0;
    if (PFSTR_GetCodeMode(&pattern) == 1) {
        PFPATH_SetSearchPattern(data->reg_exp, 0, &pattern);
        data->status |= 1;
    } else {
        PFPATH_SetSearchPattern(data->reg_exp, ((PF_DTAW*)data)->reg_expW, &pattern);
        data->status |= 2;
    }
    return PFDIR_p_fsnext(data);
}
