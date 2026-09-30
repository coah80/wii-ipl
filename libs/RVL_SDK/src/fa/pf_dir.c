#include <private/vf/PrFILE2/fatfs/pf_dir.h>

#include <private/vf/PrFILE2/fatfs/pf_entry.h>
#include <private/vf/PrFILE2/fatfs/pf_volume.h>
#include <private/vf/PrFILE2/common/pf_clib.h>
#include <private/vf/PrFILE2/common/pf_w_clib.h>
#include <private/vf/PrFILE2/fatfs/pf_path.h>
#include <private/vf/PrFILE2/fatfs/pf_sector.h>

typedef struct PFDIR_FFD {
    pf_u32 start_cluster;
    pf_u32 current_start_cluster;
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

typedef struct PFDIR_CURRENT_DIR {
    pf_u32 stat;
    pf_s32 context_id;
    PF_DIR_ENT directory;
} PFDIR_CURRENT_DIR;

typedef struct PFDIR_DIR_POS {
    pf_u32 cluster;
    pf_u32 sector;
    pf_u16 offset;
    pf_u16 alignment;
} PFDIR_DIR_POS;

typedef struct PFDIR_CUR_VOLUME {
    pf_u32 stat;
    pf_u32 context_id;
    PF_VOLUME* p_vol;
} PFDIR_CUR_VOLUME;

typedef struct PFDIR_VOLUME_DIRS {
    pf_u8 volume_prefix[0x40];
    PFDIR_SFD sfds[5];
    pf_u8 volume_state[0xF0];
    PFDIR_SDD sdds[3];
    PFDIR_DIR udds[3];
    pf_s32 num_opened_files;
    pf_s32 num_opened_directories;
    pf_u32 cache_control;
    pf_u8 cache_state[0x1C];
    void* cache_signature;
    pf_s8 label[12];
    PFDIR_CURRENT_DIR current_dir[4];
    pf_u8 volume_tail[0x1F80 - 0x1F74];
    pf_s32 last_error;
} PFDIR_VOLUME_DIRS;

typedef struct PFDIR_GLOBAL_STATE {
    pf_u8 state_prefix[0x40];
    pf_s32 last_error;
    pf_u8 driver_and_code_state[0x1C];
    pf_u32 setting;
} PFDIR_GLOBAL_STATE;

extern PFDIR_GLOBAL_STATE pf_vol_set;

pf_s8 dir_str_bs[2] = "\\";
pf_s8 dir_str_slash[2] = "/";
#pragma push
#pragma section sconst_type ".sdata"
const pf_u32 dir_str_empty = 0;
#pragma pop
pf_s8 dir_str_colon[2] = ":";
pf_s8 dir_str_star[2] = "*";
pf_s8 dir_str_dotdot[3] = "..";
pf_s8 dir_str_dot[8] = ".";


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
    PFDIR_SDD* free_candidate = volume_dirs->sdds;
    pf_s32 i;
    pf_s32 remaining = 3;

    for (i = 0; remaining != 0; remaining--) {
        if ((volume_dirs->sdds[i].stat & 1) == 0 || ((volume_dirs->sdds[i].stat & 1) != 0 && (!volume_dirs->sdds[i].stat & 2) != 0)) {
            if (first_free_sdd == 0) {
                first_free_sdd = free_candidate;
            }
        } else if (entry->p_vol == volume_dirs->sdds[i].dir_entry.p_vol &&
                   entry->entry_sector == volume_dirs->sdds[i].dir_entry.entry_sector &&
                   entry->entry_offset == volume_dirs->sdds[i].dir_entry.entry_offset) {
            return &volume_dirs->sdds[i];
        }
        i++;
        free_candidate++;
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


    if ((PFSTR_StrNCmp(path, dir_str_bs, 1, 0, 1) == 0 ||
         PFSTR_StrNCmp(path, dir_str_slash, 1, 0, 1) == 0) &&
        PFSTR_StrNCmp(path, (const pf_s8*)&dir_str_empty, 1, 1, 1) == 0) {
        error = PFENT_GetRootDir(volume, &entry);
        if (error != 0) {
            return error;
        }
        goto open_directory;
    } else if (PFSTR_StrNumChar(path, 1) == 2 &&
               PFSTR_StrNCmp(path, dir_str_colon, 1, 1, 1) == 0) {
        error = PFVOL_GetCurrentDir(volume, &entry);
        goto open_directory;
    } else if (PFSTR_StrNumChar(path, 1) == 3 &&
               PFSTR_StrNCmp(path, dir_str_colon, 1, 1, 1) == 0 &&
               (PFSTR_StrNCmp(path, dir_str_bs, 1, 2, 1) == 0 ||
                PFSTR_StrNCmp(path, dir_str_slash, 1, 2, 1) == 0)) {
        error = PFENT_GetRootDir(volume, &entry);
        if (error != 0) {
            return error;
        }
        goto open_directory;
    } else {
        if (PFSTR_StrNCmp(path, dir_str_colon, 1, 1, 1) == 0 &&
            (PFSTR_StrNCmp(path, dir_str_bs, 1, 2, 1) == 0 ||
             PFSTR_StrNCmp(path, dir_str_slash, 1, 2, 1) == 0)) {
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
        PFSTR_InitStr(&pattern, dir_str_star, 1);
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

extern pf_s32 PFENT_findEntry(PFDIR_FFD* ffd, PF_DIR_ENT* entry, pf_u32 start, PFDIR_STR* pattern,
                              pf_u8 attr_required, pf_u8 attr_forbidden);
extern pf_s32 PFFAT_GetSectorSpecified(PFDIR_FFD*, pf_u32, pf_u32, pf_u32*);
extern pf_s32 PFPATH_transformInUnicode(pf_u16*, const pf_s8*);
extern void PFPATH_SetSearchPattern(pf_s8*, pf_u16*, PFDIR_STR*);
extern pf_u16* pf_w_strcpy(pf_u16*, const pf_u16*);

extern pf_s32 PFENT_ITER_IteratorInitialize(PF_ENT_ITER* iter, pf_u32 index);
extern pf_s32 PFENT_ITER_FindEntry(PF_ENT_ITER* iter, PF_DIR_ENT* entry, PFDIR_STR* pattern,
                                   pf_u8 attributes, pf_u32 start, pf_u32* found);
extern pf_s32 PFPATH_parseShortName(pf_s8* short_name, PFDIR_STR* name);
extern pf_s32 PFENT_AdjustSFN(PF_DIR_ENT* entry, pf_s8* short_name);
extern pf_s32 PFENT_allocateEntryPos(PF_DIR_ENT* entry, pf_u8 num_entries, PFDIR_FFD* ffd,
                                     pf_u32* prev_chain, PFDIR_STR* filename, pf_u32* pos);
extern void PFPATH_AdjustExtShortName(pf_s8* short_name, pf_u32 pos);
extern pf_s32 PFCACHE_AllocateDataPage(PF_VOLUME* volume, pf_u32 sector, PF_CACHE_PAGE** page,
                                       pf_bool* flag);
extern void PFCACHE_FreeDataPage(PF_VOLUME* volume, PF_CACHE_PAGE* page);
extern pf_s32 PFSEC_WriteData(PF_VOLUME* volume, const pf_u8* data, pf_u32 sector, pf_u16 offset,
                              pf_u32 size, pf_u32* written, pf_bool flag);
extern void PFENT_StoreEntryNumericFieldsToBuf(pf_u8* buf, PF_DIR_ENT* entry);
extern void PFENT_storeLFNEntryFieldsToBuf(pf_u8* buf, PF_DIR_ENT* entry, pf_u8 ordinal, pf_u8 check_sum,
                                           pf_bool is_last);
extern pf_u8 PFENT_CalcCheckSum(PF_DIR_ENT* entry);
extern void* pf_memset(void* dest, pf_s32 value, pf_u32 size);
extern pf_u32 PFSTR_GetCodeMode(PFDIR_STR* path);
extern const pf_s8* PFSTR_GetStrPos(PFDIR_STR* path, pf_u32 target);

pf_s32 PFDIR_p_mkdir(PF_VOLUME* p_vol, PF_STR* p_path, pf_u32 option, PF_DTA* p_dta) {
    pf_s32 err;
    PF_DIR_ENT parent_entry;
    PF_DIR_ENT entry;
    pf_s8 normalized_name[512];
    PF_ENT_ITER iter;
    PFDIR_FFD ffd;
    pf_u8 lfn_buf[32];
    PFDIR_STR full_path;
    PFDIR_STR dirname;
    PFDIR_FAT_HINT fat_hint;
    pf_u32 prev_chain[2];
    pf_u32 found;
    pf_bool allocate_flag;
    PF_CACHE_PAGE* data_page;
    pf_u32 new_sector;
    pf_u32 written;
    pf_u32 pos;
    pf_u16 filename_len;
    pf_u32 new_cluster;
    pf_u32 num_lfn;
    pf_u32 index;
    pf_u32* chain;
    pf_u32 sector;
    pf_u8 check_sum;
    pf_u32 num_sectors;
    pf_u8* buf;

    (void)option;

    err = 0;
    new_sector = 0;
    err = PFPATH_SplitPath((PFDIR_STR*)p_path, &full_path, &dirname);
    if (err != 0) {
        return err;
    }
    err = PFENT_ITER_GetEntryOfPath(&iter, &parent_entry, p_vol,
                                    (PFDIR_STR*)&full_path, 1);
    if (err != 0) {
        return err;
    }
    if ((parent_entry.attr & 0x10) == 0) {
        return 0x14;
    }
    filename_len = PFSTR_StrNumChar(&dirname, 1);
    if (filename_len + parent_entry.path_len > 0x103) { return 2; }
    if (filename_len > 0xFF) { return 1; }
    if (PFSTR_GetCodeMode(&dirname) == 2) {
        PFPATH_transformFromUnicodeToNormal(
            normalized_name, (const pf_u16*)PFSTR_GetStrPos(&dirname, 1));
    }
    PFSTR_SetLocalStr(&dirname, (pf_u32)normalized_name);
    if (p_dta != PF_NULL) {
        p_dta->p_file = PF_NULL;
        p_dta->p_dir = PF_NULL;
        p_dta->parent_start_cluster = parent_entry.start_cluster;
        p_dta->p_vol = parent_entry.p_vol;
        p_dta->attr = 0x10;
        if (PFSTR_GetCodeMode(&dirname) == 1) {
            PFPATH_SetSearchPattern(p_dta->reg_exp, PF_NULL, &dirname);
            p_dta->status |= 1;
        } else {
            PFPATH_SetSearchPattern(p_dta->reg_exp, ((PF_DTAW*)p_dta)->reg_expW, &dirname);
            p_dta->status |= 2;
        }
    }
    PFFAT_InitFFD(&ffd, &fat_hint, p_vol, &parent_entry.start_cluster);
    iter.ffd = ffd;
    PFFAT_ResetFFD(&iter.ffd, &parent_entry.start_cluster);
    err = PFENT_ITER_IteratorInitialize(&iter, 0);
    if (err != 0) {
        return err;
    }
    err = PFENT_ITER_FindEntry(&iter, &entry, &dirname, 0x10, 0, &found);
    if (err != 0) {
        return err;
    }
    if (found != 0) {
        return 8;
    }
    err = PFPATH_parseShortName(entry.short_name, &dirname);
    if (err != 0 && entry.short_name[0] == 0) {
        return 1;
    }
    if (err != 0) {
        err = PFENT_AdjustSFN(&parent_entry, entry.short_name);
        if (err != 0) {
            return err;
        }
        if (PFSTR_GetCodeMode(&dirname) == 1) {
            filename_len = PFPATH_transformInUnicode(
                entry.long_name, (const pf_s8*)PFSTR_GetStrPos(&dirname, 1));
        } else {
            pf_w_strcpy(entry.long_name, (const pf_u16*)PFSTR_GetStrPos(&dirname, 1));
        }
    } else {
        entry.long_name[0] = 0;
    }
    entry.start_cluster = 0;
    entry.file_size = 0;
    entry.p_vol = p_vol;
    entry.small_letter_flag = 0;
    entry.attr = 0x10;
    entry.create_time_ms = PFENT_getcurrentDateTimeForEnt(&entry.create_date, &entry.create_time);
    entry.access_date = entry.create_date;
    entry.modify_time = entry.create_time;
    entry.modify_date = entry.create_date;
    if (entry.long_name[0] != 0 && (entry.small_letter_flag & 0x18) == 0) {
        num_lfn = (pf_u8)(filename_len / 13U + ((filename_len % 13U) != 0));
        err = PFENT_allocateEntryPos(&entry, (pf_u8)(num_lfn + 1), &ffd, prev_chain, &dirname, &pos);
        if (err != 0) {
            return err;
        }
        if ((pf_vol_set.setting & 2) == 2) {
            PFPATH_AdjustExtShortName(entry.short_name, pos);
        }
    } else {
        err = PFENT_allocateEntryPos(&entry, 1, &ffd, prev_chain, &dirname, &pos);
        if (err != 0) {
            return err;
        }
    }
    PFFAT_ResetFFD(&ffd, &entry.start_cluster);
    err = PFFAT_GetSectorSpecified(&ffd, 0, 1, &new_sector);
    if (err != 0) {
        return err;
    }
    if (new_sector == -1U) {
        return 6;
    }
    new_cluster = ffd.p_hint->cluster;
    if (p_vol->bpb.fat_type == FAT_32 &&
        *iter.ffd.p_start_cluster == p_vol->bpb.root_dir_cluster &&
        entry.entry_offset == 0 &&
        new_cluster == p_vol->bpb.root_dir_cluster) {
        iter.ffd = ffd;
        err = PFENT_ITER_IteratorInitialize(&iter, num_lfn);
        if (err != 0) {
            return err;
        }
        if (iter.buf[0] == 0) {
            PFFAT_ResetFFD(&ffd, &entry.start_cluster);
            *ffd.p_start_cluster = 0;
            ffd.p_hint->cluster = 0;
            new_cluster = p_vol->bpb.root_dir_cluster + 1;
            err = PFFAT_GetSectorSpecified(&ffd, 0, 1, &new_sector);
            if (err != 0) {
                return err;
            }
        }
    }
    err = PFCACHE_AllocateDataPage(p_vol, -1U, &data_page, &allocate_flag);
    if (err != 0) {
        return err;
    }
    pf_memset(data_page->p_buf, 0, p_vol->bpb.bytes_per_sector);
    num_sectors = p_vol->bpb.sectors_per_cluster;
    while (num_sectors != 0) {
        if (num_sectors == 1) {
            buf = data_page->p_buf;
            buf[0] = '.';
            buf[1] = ' ';
            buf[2] = ' ';
            buf[3] = ' ';
            buf[4] = ' ';
            buf[5] = ' ';
            buf[6] = ' ';
            buf[7] = ' ';
            buf[8] = ' ';
            buf[9] = ' ';
            buf[10] = ' ';
            PFENT_StoreEntryNumericFieldsToBuf(data_page->p_buf, &entry);
            buf = data_page->p_buf;
            buf[0x20] = '.';
            buf[0x21] = '.';
            buf[0x22] = ' ';
            buf[0x23] = ' ';
            buf[0x24] = ' ';
            buf[0x25] = ' ';
            buf[0x26] = ' ';
            buf[0x27] = ' ';
            buf[0x28] = ' ';
            buf[0x29] = ' ';
            buf[0x2A] = ' ';
            if (parent_entry.entry_sector == -1U) {
                entry.start_cluster = 0;
            } else {
                entry.start_cluster = parent_entry.start_cluster;
            }
            PFENT_StoreEntryNumericFieldsToBuf(&data_page->p_buf[0x20], &entry);
        }
        err = PFSEC_WriteData(p_vol, data_page->p_buf, new_sector + num_sectors - 1, 0,
                              p_vol->bpb.bytes_per_sector, &written, 0);
        if (err != 0) {
            break;
        }
        if (written != p_vol->bpb.bytes_per_sector) {
            err = 0x11;
            break;
        }
        num_sectors--;
    }
    PFCACHE_FreeDataPage(p_vol, data_page);
    if (err != 0) {
        return err;
    }
    entry.num_entry_LFNs = (pf_u8)num_lfn;
    sector = entry.entry_sector;
    check_sum = PFENT_CalcCheckSum(&entry);
    if ((parent_entry.small_letter_flag & 0x18) == 0) {
        chain = prev_chain;
        for (index = num_lfn; index >= 1; index--) {
            PFENT_storeLFNEntryFieldsToBuf(lfn_buf, &entry, (pf_u8)index, check_sum,
                                           (pf_bool)(index == num_lfn));
            err = PFSEC_WriteData(p_vol, lfn_buf, sector, entry.entry_offset, 0x20, &written, 0);
            if (err != 0) {
                return err;
            }
            if (written != 0x20) {
                return 0x11;
            }
            entry.entry_offset += 0x20;
            if (entry.entry_offset >= p_vol->bpb.bytes_per_sector) {
                entry.entry_offset = 0;
                sector = *chain++;
            }
        }
        entry.entry_sector = sector;
    }
    entry.start_cluster = new_cluster;
    err = PFENT_updateEntry(&entry, 0);
    if (err != 0) {
        return err;
    }
    if (p_dta != PF_NULL) {
        p_dta->parent_pos = pos + 1;
        pf_strcpy(p_dta->FileName, entry.short_name);
        if ((p_dta->status & 2) == 2) {
            PFPATH_transformInUnicode(((PF_DTAW*)p_dta)->FileNameW, p_dta->FileName);
        }
        if (entry.long_name[0] != 0) {
            if ((pf_vol_set.setting & 2) == 2) {
                pf_vol_set.setting &= 0xFFFFFFFC;
                pf_vol_set.setting |= 1;
                PFPATH_transformFromUnicodeToNormal(p_dta->LongName, entry.long_name);
                pf_vol_set.setting &= 0xFFFFFFFC;
                pf_vol_set.setting |= 2;
            } else {
                PFPATH_transformFromUnicodeToNormal(p_dta->LongName, entry.long_name);
            }
            if ((p_dta->status & 2) == 2) {
                pf_w_strcpy(((PF_DTAW*)p_dta)->LongNameW, entry.long_name);
            }
            p_dta->check_sum = check_sum;
            p_dta->ordinal = 1;
        } else {
            p_dta->LongName[0] = 0;
            if ((p_dta->status & 2) == 2) {
                ((PF_DTAW*)p_dta)->LongNameW[0] = 0;
            }
            p_dta->ordinal = 0;
            p_dta->check_sum = 0;
        }
        p_dta->FileSize = entry.file_size;
        p_dta->Time = entry.modify_time;
        p_dta->Date = entry.modify_date;
        p_dta->Attribute = entry.attr;
        p_dta->num_entry_LFNs = entry.num_entry_LFNs;
    }
    return 0;
}

pf_s32 PFDIR_p_chdir(PF_VOLUME* p_vol, PFDIR_STR* p_path_str) {
    pf_s32 err;
    PF_ENT_ITER iter;
    PF_DIR_ENT entry_dir;

    if (((PFSTR_StrNCmp(p_path_str, (pf_s8*)dir_str_bs, 1U, 0, 1U) == 0) || (PFSTR_StrNCmp(p_path_str, (pf_s8*)dir_str_slash, 1U, 0, 1U) == 0)) &&
        (PFSTR_StrNCmp(p_path_str, (const pf_s8*)&dir_str_empty, 1U, 1, 1U) == 0)) {
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
    if ((PFSTR_StrNumChar(p_path_str, 1U) == 2) && (PFSTR_StrNCmp(p_path_str, (pf_s8*)dir_str_colon, 1U, 1, 1U) == 0)) {
        return 0;
    }
    if ((PFSTR_StrNumChar(p_path_str, 1U) == 3) && (PFSTR_StrNCmp(p_path_str, (pf_s8*)dir_str_colon, 1U, 1, 1U) == 0) &&
        ((PFSTR_StrNCmp(p_path_str, (pf_s8*)dir_str_bs, 1U, 2, 1U) == 0) || (PFSTR_StrNCmp(p_path_str, (pf_s8*)dir_str_slash, 1U, 2, 1U) == 0))) {
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
    if ((PFSTR_StrNCmp(p_path_str, (pf_s8*)dir_str_colon, 1U, 1, 1U) == 0) &&
        ((PFSTR_StrNCmp(p_path_str, (pf_s8*)dir_str_bs, 1U, 2, 1U) == 0) || (PFSTR_StrNCmp(p_path_str, (pf_s8*)dir_str_slash, 1U, 2, 1U) == 0))) {
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
    PF_ENT_ITER iter;
    PF_ENT_ITER saved_iter;
    PF_DIR_ENT entry;
    PFDIR_STR directory_path;
    PFDIR_STR filename;
    PFDIR_FAT_HINT hint;
    PFDIR_FAT_HINT saved_hint;
    PFDIR_FFD ffd;
    pf_u32 is_empty;
    pf_u32 i;
    pf_s32 error;

    error = PFPATH_SplitPath(path, &directory_path, &filename);
    if (error != 0) { return error; }
    error = PFENT_ITER_GetEntryOfPath(&iter, &entry, volume, path, 0);
    if (error != 0) {
        return error;
    }
    saved_iter = iter;
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
    {
        pf_u32 start_cluster = entry.start_cluster;
        iter = saved_iter;
        iter.ffd.p_hint = &saved_hint;
        error = PFENT_RemoveEntry(&entry, &iter);
        if (error != 0) {
            return error;
        }
        return release_directory_chain(&iter.ffd, start_cluster, -1U);
    }
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
extern pf_s32 PFENT_ITER_FindDirEntryFromCluster(PF_ENT_ITER* iter, PF_DIR_ENT* entry, pf_u32 cluster, pf_u32* found);
extern pf_s32 PFPATH_SplitPathPattern(PF_STR* path, PFDIR_STR* directory, PFDIR_STR* pattern);
extern pf_s32 PFENT_ITER_GetLFNEntryName(PF_ENT_ITER* iter);
extern void PFPATH_getLongNameformShortName(pf_s8* short_name, pf_s8* long_name, pf_u8 small_letter_flag);
extern pf_s32 PFFILE_FsexecOpenFile(PF_DIR_ENT* entry, PF_ENT_ITER* iter, pf_u32 mode, PF_DTA* data);
extern pf_s32 PFPATH_cmpName(const pf_s8* short_name, PFDIR_STR* pattern, pf_u32 short_search);
extern pf_s32 PFPATH_cmpNameUni(const pf_u16* name, PFDIR_STR* pattern);
extern pf_u8 dir_fb_free[];
extern pf_s32 PFENT_ITER_Retreat(PF_ENT_ITER* iter, pf_u32 may_allocate);
extern pf_s32 PFENT_ITER_FindCluster(PF_DIR_ENT* entry, pf_u32 cluster, pf_bool* found);
extern pf_s32 PFCACHE_FlushDataCache(PF_VOLUME* volume);
extern pf_s32 pf_strcmp(const pf_s8* s1, const pf_s8* s2);
extern pf_s32 pf_w_strcmp(const pf_u16* s1, const pf_u16* s2);
extern void* pf_memcpy(void* dest, const void* src, pf_u32 size);

pf_s32 PFDIR_p_rename(PF_VOLUME* p_vol, PF_STR* p_old, PF_STR* p_new) {
    pf_s32 error;
    pf_s32 err, sfn_err, in_use, len, num_lfn, filename_len, sector, cmp;
    pf_u32 i, j;
    PF_ENT_ITER iter;
    PF_ENT_ITER iter2;
    PFDIR_FAT_HINT hint;
    PFDIR_FAT_HINT hint2;
    PF_DIR_ENT entry;
    PF_DIR_ENT parent;
    PF_DIR_ENT dest_entry;
    PFDIR_STR parent_str;
    PFDIR_STR source_name;
    PFDIR_STR dest_name;
    pf_s8 normalized[512];
    pf_u8 lfn_buf[32];
    pf_u32 prev_chain[16];
    pf_u32 found;
    pf_u32 pos;
    pf_u32 written;
    pf_u16 time;
    pf_u16 lfn0;
    pf_u16 entry_offset;
    PF_DIR_ENT* p_ent;
    pf_u32* p_chain;
    PFDIR_VOLUME_DIRS* vdirs;
    pf_u8 dir_fb_free[1] = {0xE5};
    pf_u8 del;

    lfn0 = 0;
    del = dir_fb_free[0];
    err = PFPATH_SplitPath((PFDIR_STR*)p_old, &parent_str, &source_name);
    if (err != 0) {
        return err;
    }
    if (PFSTR_GetCodeMode(&source_name) == 2) {
        filename_len = PFSTR_StrNumChar(&source_name, 1);
        if (filename_len > 0xFF) {
            return 1;
        }
        PFPATH_transformFromUnicodeToNormal(normalized,
                                            (const pf_u16*)PFSTR_GetStrPos(&source_name, 1));
    }
    PFSTR_SetLocalStr(&source_name, (pf_u32)normalized);
    err = PFENT_ITER_GetEntryOfPath(&iter, &parent, p_vol, (PFDIR_STR*)p_old, 1);
    if (err != 0) {
        return err;
    }
    PFFAT_InitFFD(&iter.ffd, &hint, p_vol, &iter.ffd.current_start_cluster);
    iter.ffd.current_start_cluster = parent.start_cluster;
    err = PFENT_ITER_IteratorInitialize(&iter, 0);
    if (err != 0) {
        return err;
    }
    err = PFENT_ITER_FindEntry(&iter, &entry, &source_name, 0x7F, 0, &found);
    if (err != 0) {
        return err;
    }
    if (found == 0) {
        return 3;
    }
    if ((entry.attr & 8) != 0) {
        return 3;
    }
    if ((entry.attr & 1) != 0) {
        return 0x18;
    }
    if (PFSTR_StrNCmp((PFDIR_STR*)p_new, dir_str_colon, 1, 1, 1) == 0 &&
        PFPATH_GetVolumeFromPath(p_new) != p_vol) {
        return 0x1F;
    }
    err = PFPATH_SplitPath((PFDIR_STR*)p_new, &parent_str, &dest_name);
    if (err != 0) {
        return err;
    }
    if (PFSTR_GetCodeMode(&dest_name) == 2) {
        filename_len = PFSTR_StrNumChar(&dest_name, 1);
        if (filename_len > 0xFF) {
            return 1;
        }
        PFPATH_transformFromUnicodeToNormal(normalized,
                                            (const pf_u16*)PFSTR_GetStrPos(&dest_name, 1));
    }
    PFSTR_SetLocalStr(&dest_name, (pf_u32)normalized);
    if (PFSTR_GetCodeMode(&dest_name) == 1) {
        cmp = pf_strcmp(PFSTR_GetStrPos(&dest_name, 1), PFSTR_GetStrPos(&parent_str, 1));
    } else {
        cmp = pf_w_strcmp((const pf_u16*)PFSTR_GetStrPos(&dest_name, 1),
                          (const pf_u16*)PFSTR_GetStrPos(&parent_str, 1));
    }
    if (cmp != 0) {
        err = PFENT_ITER_GetEntryOfPath(&iter2, &dest_entry, p_vol, (PFDIR_STR*)p_new, 1);
        if (err != 0) {
            return err;
        }
        if (dest_entry.start_cluster != parent.start_cluster) {
            return 0x20;
        }
    }
    dest_entry.start_cluster = parent.start_cluster;
    PFFAT_InitFFD(&iter2.ffd, &hint2, p_vol, &dest_entry.start_cluster);
    err = PFENT_findEntry(&iter2.ffd, &dest_entry, 0, &dest_name, 0x7F, 0);
    if (err == 0) {
        return 8;
    }
    if (err != 0 && err != 3) {
        return err;
    }
    if ((entry.attr & 0x10) == 0) {
        if (PFFILE_IsOpened(&entry) != 0) {
            return 0x13;
        }
    } else {
        vdirs = (PFDIR_VOLUME_DIRS*)entry.p_vol;
        sector = entry.entry_sector;
        entry_offset = entry.entry_offset;
        if ((vdirs->sdds[0].stat & 1) != 0 && (vdirs->sdds[0].stat & 2) != 0 &&
                  entry.p_vol == vdirs->sdds[0].dir_entry.p_vol &&
                  sector == vdirs->sdds[0].dir_entry.entry_sector &&
                  entry_offset == vdirs->sdds[0].dir_entry.entry_offset) {
            in_use = 1;
        } else if ((vdirs->sdds[1].stat & 1) != 0 && (vdirs->sdds[1].stat & 2) != 0 &&
                  entry.p_vol == vdirs->sdds[1].dir_entry.p_vol &&
                  sector == vdirs->sdds[1].dir_entry.entry_sector &&
                  entry_offset == vdirs->sdds[1].dir_entry.entry_offset) {
            in_use = 1;
        } else if ((vdirs->sdds[2].stat & 1) != 0 && (vdirs->sdds[2].stat & 2) != 0 &&
                  entry.p_vol == vdirs->sdds[2].dir_entry.p_vol &&
                  sector == vdirs->sdds[2].dir_entry.entry_sector &&
                  entry_offset == vdirs->sdds[2].dir_entry.entry_offset) {
            in_use = 1;
        } else {
            in_use = 0;
        }
        if (in_use != 0) {
            return 0x13;
        }
        in_use = 0;
        for (i = 0; i < 4; i++) {
            if (((PFDIR_CUR_VOLUME*)&pf_vol_set)[i].p_vol == entry.p_vol) {
                PFDIR_CURRENT_DIR* cd = vdirs->current_dir;
                for (j = 0; j < 4; j++, cd++) {
                    if ((cd->stat & 1) != 0 && cd->directory.start_cluster == entry.start_cluster) {
                        in_use = 1;
                        break;
                    }
                }
            }
        }
        if (in_use != 0) {
            return 0x1C;
        }
        if (PFSTR_StrNCmp(&source_name, dir_str_dotdot, 1, 0, 2) == 0) {
            return 0x1C;
        }
        if (PFSTR_StrNCmp(&source_name, dir_str_dot, 1, 0, 1) == 0) {
            return 0x1C;
        }
        sector = (p_vol->bpb.first_data_sector +
                  ((entry.start_cluster - 2) << p_vol->bpb.log2_sectors_per_cluster));
        for (i = 0; i < 5; i++) {
            if ((vdirs->sfds[i].stat & 1) != 0 && (vdirs->sfds[i].stat & 2) != 0 &&
                p_vol == vdirs->sfds[i].dir_entry.p_vol &&
                sector == vdirs->sfds[i].dir_entry.entry_sector) {
                return 0x13;
            }
            found = 0;
            err = PFENT_ITER_FindCluster(&vdirs->sfds[i].dir_entry, entry.start_cluster, &found);
            if (err != 0) {
                return err;
            }
            if (found != 0) {
                return 0x13;
            }
        }
    }
    filename_len = PFSTR_StrNumChar(&dest_name, 1);
    if (filename_len + parent.path_len > 0x103U) {
        return 1;
    }
    if ((entry.attr & 0x10) == 0 && filename_len > 0xFF) {
        return 1;
    }
    pf_memcpy(&dest_entry, &entry, sizeof(PF_DIR_ENT));
    sfn_err = PFPATH_parseShortName(dest_entry.short_name, &dest_name);
    if ((pf_s8)dest_entry.short_name[0] == 0) {
        return 2;
    }
    if (sfn_err != 0 || entry.num_entry_LFNs != 0) {
    } else {
        dest_entry.long_name[0] = 0;
        dest_entry.num_entry_LFNs = 0;
        PFENT_getcurrentDateTimeForEnt(&dest_entry.access_date, &time);
        err = PFENT_updateEntry(&dest_entry, 1);
        if (err != 0) {
            return err;
        }
        return error;
    }
    if (entry.num_entry_LFNs != 0 && (entry.small_letter_flag & 6) == 0) {
        lfn0 = entry.long_name[0];
        entry.long_name[0] = 0;
        for (i = 1; i <= entry.num_entry_LFNs; i++) {
            err = PFENT_ITER_Retreat(&iter, 0);
            if (err != 0) {
                return err;
            }
            err = PFSEC_WriteData(p_vol, &del, iter.sector, iter.offset, 1, &written, 0);
            if (err != 0) {
                return err;
            }
            if (written != 1) {
                return 0x11;
            }
        }
    }
    err = PFSEC_WriteData(p_vol, &del, entry.entry_sector, entry.entry_offset, 1, &written, 0);
    if (err != 0) {
        return err;
    }
    if (written != 1) {
        return 0x11;
    }
    if ((((PFDIR_VOLUME_DIRS*)p_vol)->cache_control & 4) != 0) {
        err = PFCACHE_FlushDataCache(p_vol);
        if (err != 0) {
            return err;
        }
    }
    if (sfn_err != 0) {
        err = PFENT_AdjustSFN(&parent, dest_entry.short_name);
        if (err != 0) {
            return err;
        }
        if (PFSTR_GetCodeMode(&dest_name) == 1) {
            len = PFPATH_transformInUnicode(dest_entry.long_name,
                                            (const pf_s8*)PFSTR_GetStrPos(&dest_name, 1));
        } else {
            pf_w_strcpy(dest_entry.long_name, (const pf_u16*)PFSTR_GetStrPos(&dest_name, 1));
        }
        dest_entry.num_entry_LFNs = len / 13 + (len % 13 != 0);
    } else {
        dest_entry.num_entry_LFNs = 0;
    }
    dest_entry.small_letter_flag = 0;
    PFFAT_InitFFD(&iter.ffd, &hint2, p_vol, &parent.start_cluster);
    error = PFENT_allocateEntryPos(&dest_entry, (pf_u8)(dest_entry.num_entry_LFNs + 1),
                                   &iter.ffd, prev_chain, &dest_name, &pos);
    if (error != 0) {
        if (entry.num_entry_LFNs != 0 && (entry.small_letter_flag & 6) == 0) {
            entry.long_name[0] = lfn0;
            entry.entry_offset -= (entry.num_entry_LFNs << 5) & 0x1FE0;
        }
        p_ent = &entry;
    } else {
        p_ent = &dest_entry;
        if ((pf_vol_set.setting & 2) == 2) {
            PFPATH_AdjustExtShortName(dest_entry.short_name, pos);
        }
        dest_entry.check_sum = PFENT_CalcCheckSum(&dest_entry);
        PFENT_getcurrentDateTimeForEnt(&dest_entry.access_date, &time);
        if (p_ent->num_entry_LFNs != 0 && (p_ent->small_letter_flag & 6) == 0) {
            sector = p_ent->entry_sector;
            p_chain = prev_chain;
            for (i = p_ent->num_entry_LFNs; i >= 1; i--) {
                PFENT_storeLFNEntryFieldsToBuf(lfn_buf, p_ent, (pf_u8)i, p_ent->check_sum,
                                               p_ent->num_entry_LFNs - i == 0);
                err = PFSEC_WriteData(p_vol, lfn_buf, sector, p_ent->entry_offset,
                                      0x20, &written, 0);
                if (err != 0) {
                    return err;
                }
                if (written != 0x20) {
                    return 0x11;
                }
                p_ent->entry_offset += 0x20;
                if ((pf_u16)p_ent->entry_offset >= p_vol->bpb.bytes_per_sector) {
                    p_ent->entry_offset = 0;
                    sector = *p_chain++;
                }
            }
            p_ent->entry_sector = sector;
        }
    }
    err = PFENT_updateEntry(p_ent, 1);
    if (err != 0) {
        return err;
    }
    return error;
}

pf_s32 PFDIR_p_move(PF_VOLUME* p_vol, PF_STR* p_old, PF_STR* p_new) {
    pf_s32 error;
    pf_s32 err, i, j, sfn_err, in_use, len, filename_len, sector;
    PF_ENT_ITER iter;
    PF_ENT_ITER iter2;
    PFDIR_FAT_HINT hint;
    PFDIR_FAT_HINT hint2;
    PF_DIR_ENT entry;
    PF_DIR_ENT parent;
    PF_DIR_ENT dest_entry;
    PFDIR_DIR_POS dir_pos;
    PFDIR_STR s;
    PFDIR_STR parent_str;
    PFDIR_STR dest_name;
    PFDIR_STR source_name;
    pf_s8 normalized[512];
    pf_u8 lfn_buf[32];
    pf_u32 prev_chain[16];
    pf_u32 found;
    pf_u32 pos;
    pf_u32 written;
    pf_u16 time;
    pf_u16 lfn0;
    pf_u16 entry_offset;
    PF_DIR_ENT* p_ent;
    pf_u32* p_chain;
    PFDIR_VOLUME_DIRS* vdirs;
    pf_u8 dir_fb_free[4] = {0xE5};
    pf_u8 del;

    lfn0 = 0;
    del = dir_fb_free[0];
    err = PFENT_ITER_GetEntryOfPath(&iter2, &entry, p_vol, (PFDIR_STR*)p_old, 0);
    if (err != 0) {
        return err;
    }
    if (PFPATH_GetVolumeFromPath(p_new) != p_vol) {
        return 0x1F;
    }
    err = PFPATH_SplitPath((PFDIR_STR*)p_new, &parent_str, &dest_name);
    if (err != 0) {
        return err;
    }
    if (PFSTR_GetCodeMode(&dest_name) == 2) {
        filename_len = PFSTR_StrNumChar(&dest_name, 1);
        if (filename_len > 0xFF) {
            return 1;
        }
        PFPATH_transformFromUnicodeToNormal(normalized,
                                            (const pf_u16*)PFSTR_GetStrPos(&dest_name, 1));
    }
    PFSTR_SetLocalStr(&dest_name, (pf_u32)normalized);
    err = PFENT_ITER_GetEntryOfPath(&iter, &parent, p_vol, (PFDIR_STR*)p_new, 1);
    if (err != 0) {
        return err;
    }
    dir_pos.cluster = parent.start_cluster;
    PFFAT_InitFFD(&iter.ffd, &hint, p_vol, &dir_pos.cluster);
    err = PFENT_findEntry(&iter.ffd, &dest_entry, 0, &dest_name, 0x7F, 0);
    if (err == 0) {
        if (dir_pos.sector == entry.entry_sector && dir_pos.offset == entry.entry_offset) {
            return 0;
        }
        return 8;
    }
    if (err != 0 && err != 3) {
        return err;
    }
    if ((entry.attr & 0x10) == 0) {
        if (PFFILE_IsOpened(&entry) != 0) {
            return 0x13;
        }
    } else {
        vdirs = (PFDIR_VOLUME_DIRS*)entry.p_vol;
        sector = entry.entry_sector;
        entry_offset = entry.entry_offset;
        if ((vdirs->sdds[0].stat & 1) != 0 && (vdirs->sdds[0].stat & 2) != 0 &&
                  entry.p_vol == vdirs->sdds[0].dir_entry.p_vol &&
                  sector == vdirs->sdds[0].dir_entry.entry_sector &&
                  entry_offset == vdirs->sdds[0].dir_entry.entry_offset) {
            in_use = 1;
        } else if ((vdirs->sdds[1].stat & 1) != 0 && (vdirs->sdds[1].stat & 2) != 0 &&
                  entry.p_vol == vdirs->sdds[1].dir_entry.p_vol &&
                  sector == vdirs->sdds[1].dir_entry.entry_sector &&
                  entry_offset == vdirs->sdds[1].dir_entry.entry_offset) {
            in_use = 1;
        } else if ((vdirs->sdds[2].stat & 1) != 0 && (vdirs->sdds[2].stat & 2) != 0 &&
                  entry.p_vol == vdirs->sdds[2].dir_entry.p_vol &&
                  sector == vdirs->sdds[2].dir_entry.entry_sector &&
                  entry_offset == vdirs->sdds[2].dir_entry.entry_offset) {
            in_use = 1;
        } else {
            in_use = 0;
        }
        if (in_use != 0) {
            return 0x13;
        }
        for (i = 0; i < 4; i++) {
            if (((PFDIR_CUR_VOLUME*)&pf_vol_set)[i].p_vol == entry.p_vol) {
                PFDIR_CURRENT_DIR* cd = vdirs->current_dir;
                in_use = 0;
                for (j = 0; j < 4; j++, cd++) {
                    if ((cd->stat & 1) != 0 && cd->directory.start_cluster == entry.start_cluster) {
                        in_use = 1;
                        break;
                    }
                }
            }
        }
        if (in_use != 0) {
            return 0x1C;
        }
        err = PFPATH_SplitPath((PFDIR_STR*)p_old, &parent_str, &source_name);
        if (err != 0) {
            return err;
        }
        if (PFSTR_StrNCmp(&source_name, dir_str_dotdot, 1, 0, 2) == 0) {
            return 0xA;
        }
        if (PFSTR_StrNCmp(&source_name, dir_str_dot, 1, 0, 1) == 0) {
            return 0xA;
        }
        sector = (p_vol->bpb.first_data_sector +
                  ((entry.start_cluster - 2) << p_vol->bpb.log2_sectors_per_cluster));
        for (i = 0; i < 5; i++) {
            if ((vdirs->sfds[i].stat & 1) != 0 && (vdirs->sfds[i].stat & 2) != 0 &&
                p_vol == vdirs->sfds[i].dir_entry.p_vol &&
                sector == vdirs->sfds[i].dir_entry.entry_sector) {
                return 0x13;
            }
            found = 0;
            err = PFENT_ITER_FindCluster(&vdirs->sfds[i].dir_entry, entry.start_cluster, &found);
            if (err != 0) {
                return err;
            }
            if (found != 0) {
                return 0x13;
            }
        }
        dir_pos.cluster = parent.start_cluster;
        while (1) {
            if (dir_pos.cluster == 1 || dir_pos.cluster == 0) {
                break;
            }
            PFFAT_InitFFD(&iter.ffd, &hint, p_vol, &dir_pos.cluster);
            PFSTR_InitStr(&s, dir_str_dotdot, 1);
            PFSTR_SetLocalStr(&s, 0);
            err = PFENT_findEntry(&iter.ffd, &entry, 0, &s, 0x7F, 0);
            if (err != 0) {
                return err;
            }
            if (dir_pos.cluster == 1 || dir_pos.cluster == 0) {
                break;
            }
            PFFAT_ResetFFD(&iter.ffd, &dir_pos.cluster);
            err = PFENT_ITER_IteratorInitialize(&iter, 0);
            if (err != 0) {
                return err;
            }
            err = PFENT_ITER_FindDirEntryFromCluster(&iter, &entry, dir_pos.cluster, &found);
            if (err == 0) {
                if (dir_pos.cluster == entry.start_cluster) {
                    return 0xA;
                }
            } else if (err != 0) {
                return err;
            }
        }
    }
    filename_len = PFSTR_StrNumChar(&dest_name, 1);
    if (filename_len + parent.path_len > 0x103U) {
        return 1;
    }
    if ((entry.attr & 0x10) == 0 && filename_len > 0xFF) {
        return 1;
    }
    pf_memcpy(&dest_entry, &entry, sizeof(PF_DIR_ENT));
    sfn_err = PFPATH_parseShortName(dest_entry.short_name, &dest_name);
    if ((pf_s8)dest_entry.short_name[0] == 0) {
        return 2;
    }
    if (entry.num_entry_LFNs != 0 && (entry.small_letter_flag & 6) == 0) {
        lfn0 = entry.long_name[0];
        entry.long_name[0] = 0;
        for (i = 1; i <= entry.num_entry_LFNs; i++) {
            err = PFENT_ITER_Retreat(&iter2, 0);
            if (err != 0) {
                return err;
            }
            err = PFSEC_WriteData(p_vol, &del, iter2.sector, iter2.offset, 1, &written, 0);
            if (err != 0) {
                return err;
            }
            if (written != 1) {
                return 0x11;
            }
        }
    }
    err = PFSEC_WriteData(p_vol, &del, entry.entry_sector, entry.entry_offset, 1, &written, 0);
    if (err != 0) {
        return err;
    }
    if (written != 1) {
        return 0x11;
    }
    if ((((PFDIR_VOLUME_DIRS*)p_vol)->cache_control & 4) != 0) {
        err = PFCACHE_FlushDataCache(p_vol);
        if (err != 0) {
            return err;
        }
    }
    if (sfn_err != 0) {
        err = PFENT_AdjustSFN(&parent, dest_entry.short_name);
        if (err != 0) {
            return err;
        }
        if (PFSTR_GetCodeMode(&dest_name) == 1) {
            len = PFPATH_transformInUnicode(dest_entry.long_name,
                                            (const pf_s8*)PFSTR_GetStrPos(&dest_name, 1));
        } else {
            pf_w_strcpy(dest_entry.long_name, (const pf_u16*)PFSTR_GetStrPos(&dest_name, 1));
        }
        dest_entry.num_entry_LFNs = len / 13 + (len % 13 != 0);
    } else {
        dest_entry.num_entry_LFNs = 0;
    }
    dest_entry.small_letter_flag = 0;
    PFFAT_InitFFD(&iter.ffd, &hint2, p_vol, &parent.start_cluster);
    error = PFENT_allocateEntryPos(&dest_entry, (pf_u8)(dest_entry.num_entry_LFNs + 1),
                                   &iter.ffd, prev_chain, &dest_name, &pos);
    if (error != 0) {
        if (entry.num_entry_LFNs != 0 && (entry.small_letter_flag & 6) == 0) {
            entry.long_name[0] = lfn0;
            entry.entry_offset -= (entry.num_entry_LFNs << 5) & 0x1FE0;
        }
        p_ent = &entry;
    } else {
        p_ent = &dest_entry;
        if ((pf_vol_set.setting & 2) == 2) {
            PFPATH_AdjustExtShortName(p_ent->short_name, pos);
        }
        p_ent->check_sum = PFENT_CalcCheckSum(p_ent);
        PFENT_getcurrentDateTimeForEnt(&p_ent->access_date, &time);
        if ((entry.attr & 0x10) != 0) {
            PFFAT_InitFFD(&iter2.ffd, &hint2, p_vol, &entry.start_cluster);
            PFSTR_InitStr(&s, dir_str_dotdot, 1);
            PFSTR_SetLocalStr(&s, 0);
            err = PFENT_findEntry(&iter2.ffd, &entry, 0, &s, 0x7F, 0);
            if (err != 0) {
                return err;
            }
            if (parent.start_cluster == 1 || parent.start_cluster == 0 ||
                (parent.start_cluster == 2 && p_vol->bpb.fat_type == FAT_32)) {
                entry.start_cluster = 0;
            } else {
                entry.start_cluster = parent.start_cluster;
            }
            err = PFENT_updateEntry(&entry, 1);
            if (err != 0) {
                return err;
            }
            if ((((PFDIR_VOLUME_DIRS*)p_vol)->cache_control & 4) != 0) {
                err = PFCACHE_FlushDataCache(p_vol);
                if (err != 0) {
                    return err;
                }
            }
        }
        if (p_ent->num_entry_LFNs != 0 && (p_ent->small_letter_flag & 6) == 0) {
            sector = p_ent->entry_sector;
            p_chain = prev_chain;
            for (i = p_ent->num_entry_LFNs; i >= 1; i--) {
                PFENT_storeLFNEntryFieldsToBuf(lfn_buf, p_ent, (pf_u8)i, p_ent->check_sum,
                                               p_ent->num_entry_LFNs - i == 0);
                err = PFSEC_WriteData(p_vol, lfn_buf, sector, p_ent->entry_offset,
                                      0x20, &written, 0);
                if (err != 0) {
                    return err;
                }
                if (written != 0x20) {
                    return 0x11;
                }
                p_ent->entry_offset += 0x20;
                if ((pf_u16)p_ent->entry_offset >= p_vol->bpb.bytes_per_sector) {
                    p_ent->entry_offset = 0;
                    sector = *p_chain++;
                }
            }
            p_ent->entry_sector = sector;
        }
    }
    err = PFENT_updateEntry(p_ent, 1);
    if (err != 0) {
        return err;
    }
    return error;
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
    PF_ENT_ITER iter;
    PFDIR_FFD ffd;
    PFDIR_FAT_HINT hint;
    PF_DIR_ENT entry;
    pf_s8 dot_name[11];
    PFDIR_STR pattern;
    PFDIR_STR long_name_pattern;
    pf_u32 position;
    pf_u32 start_position;
    pf_u32 write_flags;
    pf_u32 use_buffer;
    pf_s32 error;

    write_flags = flags & 6;
    if (write_flags != 0 || (flags & 1) != 0 || (flags & 0x10) != 0 || (flags & 0x20) != 0) {
    if (write_flags != 0 || (flags & 1) != 0 || ((flags & 0x10) != 0 && mode != 2)) {
        error = PFVOL_CheckForWrite(data->p_vol);
        if (error != 0) {
            return error;
        }
    }
    entry.short_name[0] = 0;
    entry.start_cluster = data->parent_start_cluster;
    PFFAT_InitFFD(&ffd, &hint, data->p_vol, &entry.start_cluster);
    iter.ffd = ffd;
    use_buffer = flags & 0x80000000;
    start_position = data->parent_pos - 1;
    if (use_buffer == 0) {
        start_position -= data->num_entry_LFNs;
    }
    error = PFENT_ITER_IteratorInitialize(&iter, start_position);
    if (error != 0) {
        return error;
    }
    if (use_buffer == 0) {
        if ((data->status & 1) == 1) {
            error = PFSTR_InitStr(&pattern, data->FileName, 1);
        } else if ((pf_vol_set.setting & 2) == 2) {
            error = PFSTR_InitStr(&pattern, (const pf_s8*)((PF_DTAW*)data)->LongNameW, 2);
        } else {
            error = PFSTR_InitStr(&pattern, (const pf_s8*)((PF_DTAW*)data)->FileNameW, 2);
        }
        if (error != 0) {
            return error;
        }
        if ((pf_vol_set.setting & 2) == 2) {
            PFSTR_SetLocalStr(&pattern, (pf_u32)data->LongName);
        } else {
            PFSTR_SetLocalStr(&pattern, (pf_u32)data->FileName);
        }
        error = PFENT_ITER_FindEntryNoPathCheck(&iter, &entry, (PF_STR*)&pattern, 0x7F, 0, &position);
        if (error != 0) {
            return error;
        }
        if (!((data->status & 2) == 2 && (pf_vol_set.setting & 2) == 2)) {
            if (PFPATH_cmpName(entry.short_name, (PFDIR_STR*)&pattern, 1) != 0) {
                return 3;
            }
        }
        error = PFSTR_InitStr(&long_name_pattern, data->LongName, 1);
        if (error != 0) {
            return error;
        }
        PFSTR_SetLocalStr(&long_name_pattern, (pf_u32)data->LongName);
        if (PFPATH_cmpNameUni(entry.long_name, (PFDIR_STR*)&long_name_pattern) != 0) {
            return 3;
        }
    } else {
        if (iter.buf[0] == 0 || iter.buf[0] == 0xE5) {
            return 3;
        }
        if ((flags & 0x20) == 0 && (iter.buf[0xB] & 0x18) != 0) {
            return 3;
        }
        if ((flags & 0x20) != 0 && ((iter.buf[0xB] & 0x10) == 0 || (iter.buf[0xB] & 8) != 0)) {
            return 0x14;
        }
        error = PFENT_ITER_GetEntryOfIter(&iter, &entry);
        if (error != 0) {
            return error;
        }
    }
    dot_name[0] = '.';
    dot_name[1] = ' ';
    dot_name[2] = ' ';
    dot_name[3] = ' ';
    dot_name[4] = ' ';
    dot_name[5] = ' ';
    dot_name[6] = ' ';
    dot_name[7] = ' ';
    dot_name[8] = ' ';
    dot_name[9] = ' ';
    dot_name[10] = ' ';
    if (pf_strncmp(entry.short_name, dot_name, 1) == 0) {
        return 0x1C;
    }
    dot_name[0] = '.';
    dot_name[1] = '.';
    dot_name[2] = ' ';
    dot_name[3] = ' ';
    dot_name[4] = ' ';
    dot_name[5] = ' ';
    dot_name[6] = ' ';
    dot_name[7] = ' ';
    dot_name[8] = ' ';
    dot_name[9] = ' ';
    dot_name[10] = ' ';
    if (pf_strncmp(entry.short_name, dot_name, 2) == 0) {
        return 0x1C;
    }
    if (write_flags != 0) {
        error = PFDIR_p_fsexec_chmod(data, &entry, flags, mode);
    } else if ((flags & 1) != 0) {
        error = PFDIR_p_fsexec_remove(data, &entry, &iter);
    } else if ((flags & 0x10) != 0) {
        error = PFDIR_p_fsexec_fopen(data, &entry, &iter, flags, mode);
    } else if ((flags & 0x20) != 0) {
        error = PFDIR_p_fsexec_opendir(data, &entry, &iter, flags);
    }
    } else {
        return 10;
    }
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
    volume_dirs->cache_signature = 0;
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
    volume_dirs->cache_signature = 0;
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
    volume_dirs->cache_signature = 0;
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
    volume_dirs->cache_signature = 0;
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
    volume_dirs->cache_signature = 0;
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
    volume_dirs->cache_signature = 0;
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
        ((PFDIR_VOLUME_DIRS*)volume)->num_opened_directories++;
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
    volume_dirs->cache_signature = 0;
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
    volume_dirs->cache_signature = 0;
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
    volume_dirs->cache_signature = 0;
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
    volume_dirs->cache_signature = 0;
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
    volume_dirs->cache_signature = 0;
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
    volume_dirs->cache_signature = 0;
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
    volume_dirs->cache_signature = 0;
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
    volume_dirs->cache_signature = 0;
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
    volume_dirs->cache_signature = 0;
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
    volume_dirs->cache_signature = 0;
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
