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

typedef struct PFDIR_VOLUME_DIRS {
    pf_u8 volume_state[0xE3C];
    PFDIR_SDD sdds[3];
    PFDIR_DIR udds[3];
} PFDIR_VOLUME_DIRS;

extern pf_s32 PFENT_ITER_MoveTo(PF_ENT_ITER* iter, pf_u32 index, pf_u32 may_allocate);
extern pf_s32 PFENT_ITER_Advance(PF_ENT_ITER* iter, pf_u32 may_allocate);
extern pf_s32 PFENT_ITER_IsAtLogicalEnd(PF_ENT_ITER* iter);
extern pf_s32 PFENT_ITER_GetEntryOfPath(PF_ENT_ITER* iter, PF_DIR_ENT* entry, PF_VOLUME* volume, PF_STR* path,
                                        pf_u32 no_look_last_token);
extern pf_s32 PFENT_GetRootDir(PF_VOLUME* volume, PF_DIR_ENT* entry);
extern pf_s32 PFVOL_GetCurrentDir(PF_VOLUME* volume, PF_DIR_ENT* entry);
extern pf_s32 PFFAT_InitFFD(PFDIR_FFD* ffd, PFDIR_FAT_HINT* hint, PF_VOLUME* volume, pf_u32* start_cluster);
extern void PFFAT_InitHint(PFDIR_FAT_HINT* hint);
extern pf_s32 PFSTR_StrNCmp(PF_STR* path, const pf_s8* text, pf_u32 target, pf_s16 offset, pf_u16 count);
extern pf_u16 PFSTR_StrNumChar(PF_STR* path, pf_u32 code_mode);
extern void PFSTR_MoveStrPos(PF_STR* path, pf_s16 count);
extern pf_s32 PFSTR_InitStr(PFDIR_STR* path, const pf_s8* text, pf_u32 code_mode);
extern void PFSTR_SetLocalStr(PFDIR_STR* path, pf_u32 is_local);
extern pf_s32 PFENT_findEntryPos(PFDIR_FFD* ffd, PF_DIR_ENT* entry, pf_u32 start, PFDIR_STR* pattern,
                                 pf_u8 attr_required, pf_u32 skip, pf_u32* logical_position,
                                 pf_u32* entry_position);
extern pf_s8* pf_strcpy(pf_s8* destination, const pf_s8* source);
extern pf_s32 PFPATH_transformFromUnicodeToNormal(pf_s8* destination, const pf_u16* source);

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
        if ((volume_dirs->sdds[i].stat & 1) == 0) {
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

pf_s32 PFDIR_DoFsexecOpenDir(PF_DIR_ENT* entry, pf_u32 flags, PFDIR_DIR** opened_dir) {
    PFDIR_VOLUME_DIRS* volume_dirs = (PFDIR_VOLUME_DIRS*)entry->p_vol;
    PFDIR_SDD* sdd;
    PFDIR_DIR* dir;
    pf_s32 i;

    *opened_dir = 0;
    if ((entry->attr & 0x10) == 0) {
        return 0x14;
    }
    sdd = PFDIR_GetSDD(entry->p_vol, entry);
    if (sdd == 0) {
        return 0x15;
    }
    dir = volume_dirs->udds;
    for (i = 0; i < 3; i++, dir++) {
        if ((dir->stat & 1) == 0) {
            break;
        }
    }
    if (i == 3) {
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

pf_s32 PFDIR_p_opendir(PF_VOLUME* volume, PF_STR* path, PFDIR_DIR** opened_dir) {
    PF_ENT_ITER iter;
    PF_DIR_ENT entry;
    PFDIR_VOLUME_DIRS* volume_dirs = (PFDIR_VOLUME_DIRS*)volume;
    PFDIR_SDD* sdd;
    PFDIR_DIR* dir;
    pf_s32 error;
    pf_s32 i;

    error = PFSTR_StrNCmp(path, (const pf_s8*)"\\", 1, 0, 1);
    if (error == 0 || PFSTR_StrNCmp(path, (const pf_s8*)"/", 1, 0, 1) == 0) {
        if (PFSTR_StrNCmp(path, (const pf_s8*)"", 1, 1, 1) == 0) {
            error = PFENT_GetRootDir(volume, &entry);
            if (error != 0) {
                return error;
            }
            goto open_directory;
        }
    }
    if (PFSTR_StrNumChar(path, 1) == 2 && PFSTR_StrNCmp(path, (const pf_s8*)":", 1, 1, 1) == 0) {
        error = PFVOL_GetCurrentDir(volume, &entry);
        if (error != 0) {
            return error;
        }
        goto open_directory;
    }
    if (PFSTR_StrNumChar(path, 1) == 3 && PFSTR_StrNCmp(path, (const pf_s8*)":", 1, 1, 1) == 0 &&
        (PFSTR_StrNCmp(path, (const pf_s8*)"\\", 1, 2, 1) == 0 ||
         PFSTR_StrNCmp(path, (const pf_s8*)"/", 1, 2, 1) == 0)) {
        error = PFENT_GetRootDir(volume, &entry);
        if (error != 0) {
            return error;
        }
        goto open_directory;
    }
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

open_directory:
    sdd = PFDIR_GetSDD(volume, &entry);
    if (sdd == 0) {
        return 0x15;
    }
    dir = volume_dirs->udds;
    for (i = 0; i < 3; i++, dir++) {
        if ((dir->stat & 1) == 0) {
            break;
        }
    }
    if (i == 3) {
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
    } else {
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
    err = VFiPFENT_GetParentEntryOfPath(&parent_entry, p_vol, &full_path);
    if (err != 0) {
        return err;
    }
    if ((parent_entry.attr & 0x10) == 0) {
        err = 0x14;
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

pf_s32 PFDIR_p_chdir(PF_VOLUME* p_vol, PF_STR* p_path_str) {
    pf_s32 err;
    PF_ENT_ITER iter;
    PF_DIR_ENT entry_dir;

    if (((VFiPFSTR_StrNCmp(p_path_str, (pf_s8*)"\\", 1U, 0, 1U) == 0) || (VFiPFSTR_StrNCmp(p_path_str, (pf_s8*)"/", 1U, 0, 1U) == 0)) &&
        (VFiPFSTR_StrNCmp(p_path_str, (pf_s8*)"\0", 1U, 1, 1U) == 0)) {
        err = VFiPFENT_GetRootDir(p_vol, &entry_dir);
        if (err != 0) {
            return err;
        }
        err = VFiPFVOL_SetCurrentDir(p_vol, &entry_dir);
        if (err != 0) {
            return err;
        }

        return 0;
    }
    if ((VFiPFSTR_StrNumChar(p_path_str, 1U) == 2) && (VFiPFSTR_StrNCmp(p_path_str, (pf_s8*)":", 1U, 1, 1U) == 0)) {
        return 0;
    }
    if ((VFiPFSTR_StrNumChar(p_path_str, 1U) == 3) && (VFiPFSTR_StrNCmp(p_path_str, (pf_s8*)":", 1U, 1, 1U) == 0) &&
        ((VFiPFSTR_StrNCmp(p_path_str, (pf_s8*)"\\", 1U, 2, 1U) == 0) || (VFiPFSTR_StrNCmp(p_path_str, (pf_s8*)"/", 1U, 2, 1U) == 0))) {
        err = VFiPFENT_GetRootDir(p_vol, &entry_dir);
        if (err != 0) {
            return err;
        }
        err = VFiPFVOL_SetCurrentDir(p_vol, &entry_dir);
        if (err != 0) {
            return err;
        }

        return 0;
    }
    if ((VFiPFSTR_StrNCmp(p_path_str, (pf_s8*)":", 1U, 1, 1U) == 0) &&
        ((VFiPFSTR_StrNCmp(p_path_str, (pf_s8*)"\\", 1U, 2, 1U) == 0) || (VFiPFSTR_StrNCmp(p_path_str, (pf_s8*)"/", 1U, 2, 1U) == 0))) {
        VFiPFSTR_MoveStrPos(p_path_str, 2);
    }
    err = PFENT_ITER_GetEntryOfPath(&iter, &entry_dir, p_vol, p_path_str, 0);
    if (err != 0) {
        return err;
    }
    if ((entry_dir.attr & 0x10) == 0) {
        return 0x14;
    }
    err = VFiPFVOL_SetCurrentDir(p_vol, &entry_dir);
    if (err != 0) {
        return err;
    }

    return 0;
}
