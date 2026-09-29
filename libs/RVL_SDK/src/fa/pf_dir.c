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
    pf_u8 cache_state[0x20];
    void* cache_signature;
    pf_u8 volume_tail[0x1F80 - 0x1648];
    pf_s32 last_error;
} PFDIR_VOLUME_DIRS;

typedef struct PFDIR_GLOBAL_STATE {
    pf_u8 state_prefix[0x40];
    pf_s32 last_error;
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

    for (i = 0; remaining != 0; i++, free_candidate++, remaining--) {
        if ((volume_dirs->sdds[i].stat & 1) == 0 || (volume_dirs->sdds[i].stat & 2) == 0) {
            if (first_free_sdd == 0) {
                first_free_sdd = free_candidate;
            }
        } else if (entry->p_vol == volume_dirs->sdds[i].dir_entry.p_vol &&
                   entry->entry_sector == volume_dirs->sdds[i].dir_entry.entry_sector &&
                   entry->entry_offset == volume_dirs->sdds[i].dir_entry.entry_offset) {
            return &volume_dirs->sdds[i];
        }
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

pf_s32 PFDIR_DoFsexecOpenDir(PF_DIR_ENT* entry, PF_ENT_ITER* iter, PFDIR_DIR** opened_dir) {
    PFDIR_VOLUME_DIRS* volume_dirs = (PFDIR_VOLUME_DIRS*)entry->p_vol;
    PFDIR_SDD* sdd;
    PFDIR_DIR* dir;
    PFDIR_DIR* scan_dir;
    pf_s32 i;

    *opened_dir = 0;
    if ((entry->attr & 0x10) == 0) {
        return 0x14;
    }
    sdd = PFDIR_GetSDD((PF_VOLUME*)volume_dirs, entry);
    if (sdd == 0) {
        return 0x15;
    }
    scan_dir = volume_dirs->udds;
    for (i = 0; i < 3; i++, scan_dir++) {
        if ((scan_dir->stat & 1) == 0) {
            dir = &volume_dirs->udds[i];
            goto directory_available;
        }
    }
    dir = 0;
directory_available:
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
    PFDIR_SDD* sdd;
    PFDIR_DIR* dir;
    pf_s32 i;
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
        if (error != 0) {
            return error;
        }
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
    for (i = 0; i < 3; i++) {
        if ((((PFDIR_VOLUME_DIRS*)volume)->udds[i].stat & 1) == 0) {
            dir = &((PFDIR_VOLUME_DIRS*)volume)->udds[i];
            goto directory_available;
        }
    }
    dir = 0;
directory_available:
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

pf_s32 PFDIR_p_mkdir(PF_VOLUME* p_vol, PF_STR* p_path, pf_u32 option, PF_DTA* p_dta) {
    pf_s32 err;
    PF_STR full_path;
    PF_STR dirname;
    pf_u16 dirname_len;
    PF_DIR_ENT entry;
    PF_DIR_ENT parent_entry;
    PF_ENT_ITER parent_iter;
    PF_FFD ffd;
    pf_u32 pos;
    PF_FAT_HINT fat_hint;
    pf_u32 prev_chain[2];
    pf_u32 new_sector;

    (void)option;

    err = 0;
    new_sector = 0;

    err = VFiPFPATH_SplitPath(p_path, &full_path, &dirname);
    if (err != 0) {
        return err;
    }
    err = PFENT_ITER_GetEntryOfPath(&parent_iter, &parent_entry, p_vol,
                                    (PFDIR_STR*)&full_path, 1);
    if (err != 0) {
        return err;
    }
    if ((parent_entry.attr & 0x10) == 0) {
        return 0x14;
    }
    if (p_dta != PF_NULL) {
        p_dta->parent_start_cluster = parent_entry.start_cluster;
    }
    VFiPFFAT_InitFFD(&ffd, &fat_hint, p_vol, &parent_entry.start_cluster);
    err = VFiPFENT_findEntry(&ffd, &entry, 0U, &dirname, 0x77U, PF_NULL, PF_NULL);
    if (err == 0) {
        return 8;
    }
    if (err != 3) {
        return err;
    }
    dirname_len = VFiPFSTR_StrNumChar(&dirname, 1U);
    if ((dirname_len > 0xFFU) || ((dirname_len + parent_entry.path_len) > 0x103U)) {
        return 2;
    }
    err = VFiPFENT_InitENT(&entry, &dirname, 0x10U, 1U, &parent_entry, p_vol);
    if (err == 0) {
        VFiPFFAT_InitFFD(&ffd, &fat_hint, p_vol, &parent_entry.start_cluster);
        err = VFiPFENT_allocateEntry(&entry, (entry.num_entry_LFNs + 1), &ffd, prev_chain, PF_NULL, 0x77U, &pos);
        if (err == 0) {
            entry.start_cluster = 0;
            VFiPFFAT_InitFFD(&ffd, &fat_hint, p_vol, &entry.start_cluster);
            err = VFiPFFAT_GetSectorSpecified(&ffd, 0U, 1U, &new_sector);
            if (new_sector == -1U) {
                err = 6;
            }
            if (err == 0) {
                err = VFiPFENT_FillVoidEntryToSectors(p_vol, new_sector, p_vol->bpb.sectors_per_cluster, 1U, &entry, &parent_entry);
                if (err == 0) {
                    if ((entry.long_name[0] != 0) && ((VFipf_vol_set.setting & 2) == 2)) {
                        VFiPFPATH_AdjustExtShortName(&entry.short_name[0], pos);
                        entry.check_sum = VFiPFENT_CalcCheckSum(&entry);
                    }
                    err = VFiPFENT_UpdateEntry(&entry, prev_chain, 0U);
                }
                if (err != 0) {
                    VFiPFFAT_FreeChain(&ffd, entry.start_cluster, -1U, -1U);
                } else if (p_dta != PF_NULL) {
                    p_dta->p_file = PF_NULL;
                    p_dta->p_dir = PF_NULL;
                    p_dta->p_vol = p_vol;
                    p_dta->parent_pos = pos + 1;
                    p_dta->num_entry_LFNs = entry.num_entry_LFNs;
                    p_dta->attr = entry.attr;
                    p_dta->Time = entry.modify_time;
                    p_dta->Date = entry.modify_date;
                    p_dta->FileSize = entry.file_size;
                    p_dta->Attribute = entry.attr;
                    if (VFiPFSTR_GetCodeMode(&dirname) == 1) {
                        VFiPFPATH_SetSearchPattern(p_dta->reg_exp, PF_NULL, &dirname);
                        p_dta->status |= 1;
                    } else {
                        VFiPFPATH_SetSearchPattern(p_dta->reg_exp, ((PF_DTAW*)p_dta)->reg_expW, &dirname);
                        p_dta->status |= 2;
                    }
                    VFipf_strcpy(p_dta->FileName, &entry.short_name[0]);
                    if ((p_dta->status & 2) == 2) {
                        VFiPFPATH_transformInUnicode(((PF_DTAW*)p_dta)->FileNameW, p_dta->FileName);
                    }
                    if (entry.long_name[0] == 0) {
                        p_dta->ordinal = 0;
                        p_dta->check_sum = 0;
                        p_dta->LongName[0] = 0;
                        if ((p_dta->status & 2) == 2) {
                            ((PF_DTAW*)p_dta)->LongNameW[0] = 0;
                        }
                    } else {
                        p_dta->ordinal = 1;
                        p_dta->check_sum = entry.check_sum;
                        if ((VFipf_vol_set.setting & 2) == 2) {
                            VFipf_vol_set.setting &= 0xFFFFFFFC;
                            VFipf_vol_set.setting |= 1;
                            VFiPFPATH_transformFromUnicodeToNormal(p_dta->LongName, entry.long_name);
                            VFipf_vol_set.setting &= 0xFFFFFFFC;
                            VFipf_vol_set.setting |= 2;
                        } else {
                            VFiPFPATH_transformFromUnicodeToNormal(p_dta->LongName, entry.long_name);
                        }
                        if ((p_dta->status & 2) == 2) {
                            VFipf_w_strcpy(((PF_DTAW*)p_dta)->LongNameW, entry.long_name);
                        }
                    }
                }
            }
        }
    }

exit:
    return err;
}

pf_s32 PFDIR_p_chdir(PF_VOLUME* p_vol, PFDIR_STR* p_path_str) {
    pf_s32 err;
    PF_ENT_ITER iter;
    PF_DIR_ENT entry_dir;

    if (((PFSTR_StrNCmp(p_path_str, (pf_s8*)"\\", 1U, 0, 1U) == 0) || (PFSTR_StrNCmp(p_path_str, (pf_s8*)"/", 1U, 0, 1U) == 0)) &&
        (PFSTR_StrNCmp(p_path_str, (pf_s8*)"\0", 1U, 1, 1U) == 0)) {
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

pf_s32 PFDIR_p_chmod(PF_VOLUME* volume, PFDIR_STR* path, pf_u8 attributes) {
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
    if (((entry.attr & 0x10) == 0 && (attributes & 0x10) != 0) ||
        ((entry.attr & 0x10) != 0 && (attributes & 0x10) == 0)) {
        return 10;
    }
    if ((attributes & 0x40) != 0) {
        attributes &= (pf_u8)~0x40;
    }
    if ((entry.attr & 0x10) == 0) {
        if (PFFILE_IsOpened(&entry) != 0) {
            return 0x13;
        }
    } else {
        volume_dirs = (PFDIR_VOLUME_DIRS*)volume;
        for (i = 0; i < 3; i++) {
            PFDIR_SDD* sdd = &volume_dirs->sdds[i];
            if ((sdd->stat & 1) != 0 && (sdd->stat & 2) != 0 &&
                entry.p_vol == sdd->dir_entry.p_vol &&
                entry.entry_sector == sdd->dir_entry.entry_sector &&
                entry.entry_offset == sdd->dir_entry.entry_offset) {
                return 0x13;
            }
        }
        if ((attributes & 4) != 0 && (attributes & 0xF) != 0xF) {
            return 10;
        }
        attributes |= 0x10;
    }
    create_time_ms = PFENT_getcurrentDateTimeForEnt(&date, &time);
    entry.modify_date = date;
    entry.modify_time = time;
    entry.create_time_ms = create_time_ms;
    entry.attr = attributes;
    return PFENT_updateEntry(&entry, 0);
}

pf_s32 PFDIR_p_rmdir(PF_VOLUME* volume, PFDIR_STR* path) {
    PFDIR_VOLUME_DIRS* volume_dirs;
    PFDIR_FAT_HINT hint;
    PFDIR_FFD ffd;
    PF_ENT_ITER iter;
    PF_ENT_ITER directory_iter;
    PF_DIR_ENT entry;
    pf_u32 is_empty;
    pf_u32 i;
    pf_s32 error;

    error = PFENT_ITER_GetEntryOfPath(&iter, &entry, volume, path, 0);
    if (error != 0) {
        return error;
    }
    if ((entry.attr & 0x10) == 0 || (entry.attr & 1) != 0) {
        return 0x14;
    }
    if (entry.start_cluster == 1 ||
        (volume->bpb.fat_type == FAT_32 && entry.start_cluster == volume->bpb.root_dir_cluster)) {
        return 0x1C;
    }
    volume_dirs = (PFDIR_VOLUME_DIRS*)volume;
    for (i = 0; i < 3; i++) {
        PFDIR_SDD* sdd = &volume_dirs->sdds[i];
        if ((sdd->stat & 3) == 3 && entry.p_vol == sdd->dir_entry.p_vol &&
            entry.entry_sector == sdd->dir_entry.entry_sector &&
            entry.entry_offset == sdd->dir_entry.entry_offset) {
            return 0x13;
        }
    }
    error = PFVOL_CheckCurrentDir(volume, entry.start_cluster);
    if (error != 0) {
        return 0x1C;
    }
    PFFAT_InitFFD(&ffd, &hint, volume, &entry.start_cluster);
    directory_iter.ffd = ffd;
    error = PFENT_ITER_IteratorInitialize(&directory_iter, 0);
    if (error != 0) {
        return error;
    }
    is_empty = 0;
    error = PFDIR_CheckDirIsEmpty(&directory_iter, &is_empty);
    if (error != 0) {
        return error;
    }
    if (is_empty == 0) {
        return 0x1D;
    }
    error = PFENT_RemoveEntry(&entry, &iter);
    if (error != 0) {
        return error;
    }
    return PFFAT_FreeChain(&iter.ffd, entry.start_cluster, -1U, -1U);
}

pf_s32 PFDIR_p_fstat(PF_VOLUME* volume, PFDIR_STR* path, PFDIR_FILE_STAT* file_stat) {
    PF_ENT_ITER iter;
    PF_DIR_ENT entry;
    PFDIR_VOLUME_DIRS* volume_dirs = (PFDIR_VOLUME_DIRS*)volume;
    pf_u32 index;
    pf_s32 error;

    error = PFENT_ITER_GetEntryOfPath(&iter, &entry, volume, path, 0);
    if (error != 0) {
        return error;
    }
    if (volume_dirs->num_opened_files != 0) {
        for (index = 0; index < 5; index++) {
            PFDIR_SFD* sfd = &volume_dirs->sfds[index];
            if ((sfd->stat & 1) != 0 && (sfd->stat & 2) != 0 &&
                entry.p_vol == sfd->dir_entry.p_vol &&
                entry.entry_sector == sfd->dir_entry.entry_sector &&
                entry.entry_offset == sfd->dir_entry.entry_offset) {
                file_stat->file_size = sfd->dir_entry.file_size;
                file_stat->access_date = sfd->dir_entry.access_date;
                file_stat->modify_time = sfd->dir_entry.modify_time;
                file_stat->modify_date = sfd->dir_entry.modify_date;
                file_stat->create_time = sfd->dir_entry.create_time;
                file_stat->create_date = sfd->dir_entry.create_date;
                file_stat->small_letter_flag = sfd->dir_entry.small_letter_flag;
                file_stat->attributes = sfd->dir_entry.attr;
                break;
            }
        }
    }
    if (volume_dirs->num_opened_files == 0 || index == 5) {
        file_stat->file_size = (entry.attr & 0x10) == 0 ? entry.file_size : 0;
        file_stat->access_date = entry.access_date;
        file_stat->modify_time = entry.modify_time;
        file_stat->modify_date = entry.modify_date;
        file_stat->create_time = entry.create_time;
        file_stat->create_date = entry.create_date;
        file_stat->small_letter_flag = entry.small_letter_flag;
        file_stat->attributes = entry.attr;
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
extern pf_s32 PFPATH_parseShortName(PF_DIR_ENT* entry, const pf_s8* name);
extern pf_s32 PFENT_ITER_GetLFNEntryName(PF_ENT_ITER* iter);
extern void PFPATH_getLongNameformShortName(pf_s8* short_name, pf_s8* long_name, pf_u8 small_letter_flag);
extern pf_s32 PFFILE_FsexecOpenFile(PF_DIR_ENT* entry, PF_ENT_ITER* iter, pf_u32 mode, PF_DTA* data);
extern pf_s32 PFPATH_cmpName(const pf_s8* short_name, PFDIR_STR* pattern, pf_u32 short_search);
extern pf_s32 PFPATH_cmpNameUni(const pf_u16* name, PFDIR_STR* pattern);

pf_s32 PFDIR_p_rename(PF_VOLUME* volume, PF_STR* old_path, PF_STR* new_path) {
    PF_ENT_ITER source_iter;
    PF_ENT_ITER destination_iter;
    PF_DIR_ENT source_entry;
    PF_DIR_ENT source_parent;
    PF_DIR_ENT destination_parent;
    PF_DIR_ENT existing_entry;
    PFDIR_STR source_directory;
    PFDIR_STR source_name;
    PFDIR_STR destination_directory;
    PFDIR_STR destination_name;
    pf_s8 normalized_name[512];
    const pf_s8* name;
    pf_u32 entry_position;
    pf_s32 error;

    error = PFPATH_SplitPath((PFDIR_STR*)old_path, &source_directory, &source_name);
    if (error != 0) {
        return error;
    }
    if (PFSTR_GetCodeMode(&source_name) == 2) {
        if (PFSTR_StrNumChar(&source_name, 1) > 0xFF) {
            return 1;
        }
        error = PFPATH_transformFromUnicodeToNormal(
            normalized_name, (const pf_u16*)PFSTR_GetStrPos(&source_name, 1));
        if (error != 0) {
            return error;
        }
        PFSTR_SetLocalStr(&source_name, (pf_u32)normalized_name);
    }
    error = PFENT_ITER_GetEntryOfPath(&source_iter, &source_parent, volume,
                                      &source_directory, 1);
    if (error != 0) {
        return error;
    }
    PFFAT_InitFFD(&source_iter.ffd, 0, volume, &source_parent.start_cluster);
    error = PFENT_ITER_IteratorInitialize(&source_iter, 0);
    if (error != 0) {
        return error;
    }
    error = PFENT_ITER_FindEntry(&source_iter, &source_entry, &source_name, 0x7F, 0,
                                 &entry_position);
    if (error != 0) {
        return error;
    }
    if (entry_position == 0) {
        return 3;
    }
    if ((source_entry.attr & 0x10) != 0) {
        return 3;
    }
    if ((source_entry.attr & 1) != 0) {
        return 0x18;
    }
    if (PFSTR_StrNCmp((PFDIR_STR*)new_path, (const pf_s8*)":", 1, 1, 1) == 0 &&
        PFPATH_GetVolumeFromPath(new_path) != volume) {
        return 0x1F;
    }
    error = PFPATH_SplitPath((PFDIR_STR*)new_path, &destination_directory,
                             &destination_name);
    if (error != 0) {
        return error;
    }
    error = PFENT_ITER_GetEntryOfPath(&destination_iter, &destination_parent, volume,
                                      &destination_directory, 1);
    if (error != 0) {
        return error;
    }
    if ((destination_parent.attr & 0x10) == 0) {
        return 0x14;
    }
    if (source_iter.ffd.start_cluster != destination_parent.start_cluster) {
        return 0x1F;
    }
    if (PFSTR_GetCodeMode(&destination_name) == 2) {
        if (PFSTR_StrNumChar(&destination_name, 1) > 0xFF) {
            return 1;
        }
        error = PFPATH_transformFromUnicodeToNormal(
            normalized_name, (const pf_u16*)PFSTR_GetStrPos(&destination_name, 1));
        if (error != 0) {
            return error;
        }
        PFSTR_SetLocalStr(&destination_name, (pf_u32)normalized_name);
    }
    name = PFSTR_GetStrPos(&destination_name, 1);
    error = PFENT_ITER_FindEntry(&destination_iter, &existing_entry, &destination_name,
                                 0x7F, 0, &entry_position);
    if (error == 0) {
        return 8;
    }
    if (error != 3) {
        return error;
    }
    error = PFPATH_parseShortName(&source_entry, name);
    if (error != 0) {
        return error;
    }
    source_entry.long_name[0] = 0;
    return PFENT_updateEntry(&source_entry, 1);
}

pf_s32 PFDIR_p_move(PF_VOLUME* volume, PF_STR* old_path, PF_STR* new_path) {
    PF_ENT_ITER source_iter;
    PF_ENT_ITER destination_iter;
    PF_DIR_ENT source_entry;
    PF_DIR_ENT destination_entry;
    PF_DIR_ENT existing_entry;
    PFDIR_STR destination_directory;
    PFDIR_STR destination_name;
    PFDIR_VOLUME_DIRS* volume_dirs;
    pf_s8 normalized_name[512];
    pf_u32 entry_position;
    pf_u32 index;
    pf_s32 error;

    error = PFENT_ITER_GetEntryOfPath(&source_iter, &source_entry, volume,
                                      (PFDIR_STR*)old_path, 0);
    if (error != 0) {
        return error;
    }
    if (PFPATH_GetVolumeFromPath(new_path) != volume) {
        return 0x1F;
    }
    error = PFPATH_SplitPath((PFDIR_STR*)new_path, &destination_directory,
                             &destination_name);
    if (error != 0) {
        return error;
    }
    if (PFSTR_GetCodeMode(&destination_name) == 2) {
        if (PFSTR_StrNumChar(&destination_name, 1) > 0xFF) {
            return 1;
        }
        error = PFPATH_transformFromUnicodeToNormal(
            normalized_name, (const pf_u16*)PFSTR_GetStrPos(&destination_name, 1));
        if (error != 0) {
            return error;
        }
        PFSTR_SetLocalStr(&destination_name, (pf_u32)normalized_name);
    }
    error = PFENT_ITER_GetEntryOfPath(&destination_iter, &destination_entry, volume,
                                      &destination_directory, 1);
    if (error != 0) {
        return error;
    }
    if ((destination_entry.attr & 0x10) == 0) {
        return 0x14;
    }
    if ((source_entry.attr & 1) != 0) {
        return 0x18;
    }
    volume_dirs = (PFDIR_VOLUME_DIRS*)volume;
    if ((source_entry.attr & 0x10) != 0) {
        if (PFVOL_CheckCurrentDir(volume, source_entry.start_cluster) != 0 ||
            source_entry.start_cluster == 1 ||
            (volume->bpb.fat_type == FAT_32 &&
             source_entry.start_cluster == volume->bpb.root_dir_cluster)) {
            return 0x1C;
        }
        for (index = 0; index < 3; index++) {
            PFDIR_SDD* sdd = &volume_dirs->sdds[index];
            if ((sdd->stat & 1) != 0 && (sdd->stat & 2) != 0 &&
                sdd->dir_entry.p_vol == source_entry.p_vol &&
                sdd->dir_entry.entry_sector == source_entry.entry_sector &&
                sdd->dir_entry.entry_offset == source_entry.entry_offset) {
                return 0x13;
            }
        }
    } else if (PFFILE_IsOpened(&source_entry) != 0) {
        return 0x13;
    }
    PFFAT_InitFFD(&destination_iter.ffd, 0, volume, &destination_entry.start_cluster);
    error = PFENT_ITER_IteratorInitialize(&destination_iter, 0);
    if (error != 0) {
        return error;
    }
    error = PFENT_ITER_FindEntry(&destination_iter, &existing_entry, &destination_name,
                                 0x7F, 0, &entry_position);
    if (error == 0) {
        if (source_entry.entry_sector == existing_entry.entry_sector &&
            source_entry.entry_offset == existing_entry.entry_offset) {
            return 0;
        }
        return 8;
    }
    if (error != 3) {
        return error;
    }
    if (source_iter.ffd.start_cluster != destination_entry.start_cluster) {
        return 0x1F;
    }
    return PFDIR_p_rename(volume, old_path, new_path);
}

pf_s32 PFDIR_p_fsexec_remove(PF_DTA* data, PF_DIR_ENT* entry, PF_ENT_ITER* iter) {
    PFDIR_VOLUME_DIRS* volume_dirs = (PFDIR_VOLUME_DIRS*)entry->p_vol;
    PFDIR_FAT_HINT hint;
    PF_ENT_ITER directory_iter;
    pf_u32 is_empty;
    pf_u32 index;
    pf_u32 start_cluster = entry->start_cluster;
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
        for (index = 0; index < 3; index++) {
            PFDIR_SDD* sdd = &volume_dirs->sdds[index];
            if ((sdd->stat & 1) != 0 && (sdd->stat & 2) != 0 &&
                sdd->dir_entry.p_vol == entry->p_vol &&
                sdd->dir_entry.entry_sector == entry->entry_sector &&
                sdd->dir_entry.entry_offset == entry->entry_offset) {
                return 0x13;
            }
        }
        directory_iter = *iter;
        PFFAT_InitFFD(&directory_iter.ffd, &hint, entry->p_vol, &entry->start_cluster);
        error = PFENT_ITER_IteratorInitialize(&directory_iter, 0);
        if (error != 0) {
            return error;
        }
        is_empty = 0;
        error = PFDIR_CheckDirIsEmpty(&directory_iter, &is_empty);
        if (error != 0) {
            return error;
        }
        if (is_empty == 0) {
            return 0x1D;
        }
    } else if (PFFILE_IsOpened(entry) != 0) {
        return 0x13;
    }
    entry->num_entry_LFNs = data->num_entry_LFNs;
    entry->ordinal = data->ordinal;
    entry->check_sum = data->check_sum;
    error = PFENT_RemoveEntry(entry, iter);
    if (error != 0) {
        return error;
    }
    return PFFAT_FreeChain(&iter->ffd, start_cluster, -1U, -1U);
}

pf_s32 PFDIR_p_fsexec_chmod(PF_DTA* data, PF_DIR_ENT* entry, pf_u32 attributes, pf_u32 mode) {
    PFDIR_VOLUME_DIRS* volume_dirs = (PFDIR_VOLUME_DIRS*)entry->p_vol;
    pf_u16 date;
    pf_u16 time;
    pf_u8 create_time_ms;
    pf_u32 index;
    pf_s32 error;

    if ((attributes & 0x40) != 0) {
        attributes &= ~0x40;
    }
    if ((entry->attr & 0x10) == 0) {
        if ((attributes & 0x10) != 0) {
            return 10;
        }
        if (PFFILE_IsOpened(entry) != 0) {
            return 0x13;
        }
        entry->attr = attributes;
    } else {
        if ((attributes & 4) != 0) {
            return 10;
        }
        for (index = 0; index < 3; index++) {
            PFDIR_SDD* sdd = &volume_dirs->sdds[index];
            if ((sdd->stat & 1) != 0 && (sdd->stat & 2) != 0 &&
                sdd->dir_entry.p_vol == entry->p_vol &&
                sdd->dir_entry.entry_sector == entry->entry_sector &&
                sdd->dir_entry.entry_offset == entry->entry_offset) {
                return 0x13;
            }
        }
        entry->attr = attributes | 0x10;
    }
    create_time_ms = PFENT_getcurrentDateTimeForEnt(&date, &time);
    entry->modify_date = date;
    entry->modify_time = time;
    entry->create_time_ms = create_time_ms;
    error = PFENT_updateEntry(entry, 0);
    if (error != 0) {
        return error;
    }
    if ((mode & 0x80000000) == 0) {
        data->Attribute = entry->attr;
    }
    return PFCACHE_FlushDataCacheSpecific(entry->p_vol, 0);
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
    PFDIR_FFD ffd;
    PFDIR_FAT_HINT hint;
    PF_ENT_ITER iter;
    PF_DIR_ENT entry;
    PFDIR_STR pattern;
    pf_u32 logical_position;
    pf_u32 entry_position;
    pf_u32 start_position;
    pf_u32 code_mode;
    const pf_s8* name;
    pf_s32 error;

    if ((flags & 0x26) == 0 && (flags & 1) == 0) {
        return 10;
    }
    if ((flags & 0x26) != 0 || (flags & 1) != 0 || ((flags & 0x10) != 0 && mode != 2)) {
        error = PFVOL_CheckForWrite(data->p_vol);
        if (error != 0) {
            return error;
        }
    }
    start_position = data->parent_pos - 1;
    if ((flags & 0x80000000) == 0) {
        start_position -= data->num_entry_LFNs;
    }
    PFFAT_InitFFD(&ffd, &hint, data->p_vol, &data->parent_start_cluster);
    iter.p_vol = data->p_vol;
    iter.ffd = ffd;
    error = PFENT_ITER_IteratorInitialize(&iter, start_position);
    if (error != 0) {
        return error;
    }
    if ((data->status & 1) != 0) {
        code_mode = 1;
        name = data->FileName;
    } else {
        code_mode = 2;
        if ((VFipf_vol_set.setting & 2) != 0) {
            name = (const pf_s8*)((PF_DTAW*)data)->LongNameW;
        } else {
            name = (const pf_s8*)((PF_DTAW*)data)->FileNameW;
        }
    }
    error = PFSTR_InitStr(&pattern, name, code_mode);
    if (error != 0) {
        return error;
    }
    if ((VFipf_vol_set.setting & 2) != 0) {
        PFSTR_SetLocalStr(&pattern, (pf_u32)data->LongName);
    } else {
        PFSTR_SetLocalStr(&pattern, (pf_u32)data->FileName);
    }
    error = PFENT_findEntryPos(&ffd, &entry, start_position, &pattern, 0x7F, 0,
                               &logical_position, &entry_position);
    if (error != 0) {
        return error;
    }
    if ((flags & 0x80000000) == 0) {
        if ((data->status & 2) != 0) {
            if (PFPATH_cmpNameUni(entry.long_name, &pattern) != 0) {
                return 3;
            }
        } else if (PFPATH_cmpName(entry.short_name, &pattern, 1) != 0) {
            return 3;
        }
    }
    if (entry.short_name[0] == '.' &&
        ((entry.short_name[1] == ' ' && entry.short_name[2] == ' ') || entry.short_name[1] == '.')) {
        return 0x1C;
    }
    error = PFENT_ITER_MoveTo(&iter, entry_position, 0);
    if (error != 0) {
        return error;
    }
    if ((flags & 6) != 0) {
        return PFDIR_p_fsexec_chmod(data, &entry, flags, mode);
    }
    if ((flags & 1) != 0) {
        return PFDIR_p_fsexec_remove(data, &entry, &iter);
    }
    if ((flags & 0x10) != 0) {
        return PFDIR_p_fsexec_fopen(data, &entry, &iter, flags, mode);
    }
    if ((flags & 0x20) != 0) {
        return PFDIR_p_fsexec_opendir(data, &entry, &iter, flags);
    }
    return 10;
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

void PFDIR_opendir(PF_STR* path, PFDIR_DIR** dir) {
    PF_VOLUME* volume = PFPATH_GetVolumeFromPath(path);
    PFDIR_VOLUME_DIRS* volume_dirs = (PFDIR_VOLUME_DIRS*)volume;
    pf_s32 error = PFVOL_CheckForRead(volume);

    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        return;
    }
    error = PFDIR_p_opendir(volume, (PFDIR_STR*)path, dir);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
    } else {
        ((PFDIR_VOLUME_DIRS*)volume)->num_opened_directories++;
    }
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
        return error;
    }
    PFVOL_SetCurrentVolume(volume);
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
    error = PFVOL_SetCurrentDir(volume, &dir->p_sdd->dir_entry);
    if (error != 0) {
        pf_vol_set.last_error = error;
        ((PFDIR_VOLUME_DIRS*)volume)->last_error = error;
        return error;
    }
    PFVOL_SetCurrentVolume(volume);
    return 0;
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
    error = PFDIR_p_chmod(volume, (PFDIR_STR*)path, attributes | 0x10);
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
    pf_u32 index;
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
    PFSTR_SetLocalStr(&pattern, 0);
    if (entry_position < 0xF423F) {
        if (data->parent_pos > 0xF423E) {
            return 10;
        }
        ffd.start_cluster = data->parent_start_cluster;
        PFFAT_InitFFD(&ffd, &hint, data->p_vol, &ffd.start_cluster);
        error = PFENT_findEntryPos(&ffd, &entry, data->parent_pos, &pattern, data->attr, 0,
                                   &logical_position, &entry_position);
        if (error != 0) {
            return error;
        }
        data->parent_pos = entry_position + 1;
        if (entry_position == 0xF423F) {
            return 3;
        }
    }
    pf_strcpy(data->FileName, entry.short_name);
    if ((data->status & 2) == 2) {
        PFPATH_transformInUnicode(((PF_DTAW*)data)->FileNameW, data->FileName);
    }
    if (entry.long_name[0] == 0) {
        data->LongName[0] = 0;
        if ((data->status & 2) == 2) {
            ((PF_DTAW*)data)->LongNameW[0] = 0;
        }
    } else {
        if ((VFipf_vol_set.setting & 2) == 2) {
            VFipf_vol_set.setting &= 0xFFFFFFFC;
            VFipf_vol_set.setting |= 1;
            PFPATH_transformFromUnicodeToNormal(data->LongName, entry.long_name);
            VFipf_vol_set.setting &= 0xFFFFFFFC;
            VFipf_vol_set.setting |= 2;
        } else {
            PFPATH_transformFromUnicodeToNormal(data->LongName, entry.long_name);
        }
        if ((data->status & 2) == 2) {
            pf_w_strcpy(((PF_DTAW*)data)->LongNameW, entry.long_name);
        }
    }
    if (((PFDIR_VOLUME_DIRS*)data->p_vol)->num_opened_files != 0) {
        PFDIR_SFD* sfd = ((PFDIR_VOLUME_DIRS*)data->p_vol)->sfds;
        for (index = 0; index < 5; index++) {
            if ((sfd->stat & 1) != 0 && (sfd->stat & 2) != 0 &&
                sfd->dir_entry.p_vol == entry.p_vol &&
                sfd->dir_entry.entry_sector == entry.entry_sector &&
                sfd->dir_entry.entry_offset == entry.entry_offset) {
                data->FileSize = sfd->dir_entry.file_size;
                data->Time = sfd->dir_entry.modify_time;
                data->Date = sfd->dir_entry.modify_date;
                data->Attribute = sfd->dir_entry.attr;
                data->num_entry_LFNs = sfd->dir_entry.num_entry_LFNs;
                data->ordinal = sfd->dir_entry.ordinal;
                data->check_sum = sfd->dir_entry.check_sum;
                break;
            }
            sfd++;
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
