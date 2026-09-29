#include <revolution/types.h>
#include <private/fa/fa_local.h>

/* pf_fat.c */
void PFFAT_InitFFD(PF_FFD* p_ffd, PF_FAT_HINT* p_hint, PF_VOLUME* p_vol, u32* p_start_cluster);
void PFFAT_InitHint(PF_FAT_HINT* p_hint);
s32 PFFAT_FreeChain(PF_FFD* p_ffd, u32 start_cluster, u32 chain_index, u32 size);

/* pf_entry.c / pf_entry_iterator.c */
static s8 dir_mark = '\\';
static s8 dir_mark_move = '/';


s32 PFDIR_p_fsnext(PF_DTA* p_dta);
s32 PFDIR_p_readdir(PF_UDD* p_udd, PF_DIRENT* p_dirent);
s32 PFDIR_p_opendir(PF_VOLUME* p_vol, PF_STR* p_path_str, PF_UDD** pp_udd);
s32 PFDIR_p_fsexec(PF_DTA* p_dta, u32 mode, u32 arg);
s32 PFENT_ITER_FindCluster(PF_FFD* p_ffd, u32 cluster, u32* p_next);
s32 PFENT_ITER_Retreat(PF_ENT_ITER* p_iter, u32 num);
s32 PFENT_ITER_FindDirEntryFromCluster(PF_ENT_ITER* p_iter, PF_DIR_ENT* p_ent, u32 cluster, u32* p_pos);
s32 PFCACHE_FlushDataCache(PF_VOLUME* p_vol);

/* pf_clib.c */

s32 PFENT_ITER_MoveTo(PF_ENT_ITER* p_iter, u32 num_entry, u32 mode);
s32 PFENT_ITER_Advance(PF_ENT_ITER* p_iter, u32 mode);
u32 PFENT_ITER_IsAtLogicalEnd(PF_ENT_ITER* p_iter);
s32 PFENT_RemoveEntry(PF_DIR_ENT* p_ent, PF_ENT_ITER* p_iter);
s32 PFENT_ITER_IteratorInitialize(PF_ENT_ITER* p_iter, u32 mode);
s32 PFENT_ITER_GetEntryOfPath(PF_ENT_ITER* p_iter, PF_DIR_ENT* p_ent, PF_VOLUME* p_vol, PF_STR* p_path,
                              u32 mode);
s32 PFENT_ITER_GetEntryOfPattern(PF_ENT_ITER* p_iter, PF_DIR_ENT* p_ent, PF_VOLUME* p_vol, PF_STR* p_pattern);

/* pf_volume.c */
s32 PFVOL_CheckForRead(PF_VOLUME* p_vol);
s32 PFVOL_CheckForWrite(PF_VOLUME* p_vol);
s32 PFVOL_CheckCurrentDir(PF_VOLUME* p_vol, u32 cluster);
s32 PFVOL_SetCurrentDir(PF_VOLUME* p_vol, const PF_DIR_ENT* p_ent);
void PFVOL_SetCurrentVolume(PF_VOLUME* p_vol);

/* pf_cache.c */
s32 PFCACHE_FlushFATCache(PF_VOLUME* p_vol);
s32 PFCACHE_FlushDataCacheSpecific(PF_VOLUME* p_vol, u32 mode);

s32 PFENT_GetRootDir(PF_VOLUME* p_vol, PF_DIR_ENT* p_ent);
s32 PFVOL_GetCurrentDir(PF_VOLUME* p_vol, PF_DIR_ENT* p_ent);

s32 PFENT_findEntry(PF_FFD* p_ffd, PF_DIR_ENT* p_ent, u32 index_from, PF_STR* p_pattern, u32 attr, u32 flag);
s32 PFENT_ITER_IteratorInitialize(PF_ENT_ITER* p_iter, u32 num);
s32 PFENT_ITER_FindEntry(PF_ENT_ITER* p_iter, PF_DIR_ENT* p_ent, PF_STR* p_pattern, u32 attr, u32 arg5, u32* p_pos);
s32 PFFAT_ResetFFD(PF_FFD* p_ffd, u32* p_start_cluster);
s32 PFFAT_GetSectorSpecified(PF_FFD* p_ffd, u32 index, u32 num, u32* p_sector);
s32 PFENT_AdjustSFN(PF_DIR_ENT* p_ent, s8* short_name);
u8 PFENT_getcurrentDateTimeForEnt(u16* p_date, u16* p_time);
s32 PFENT_allocateEntryPos(PF_DIR_ENT* p_ent, u32 num_entry, PF_FFD* p_ffd, u32* p_pos_arr, PF_STR* p_pattern, u32* p_pos);
s32 PFCACHE_AllocateDataPage(PF_VOLUME* p_vol, s32 arg2, void** pp_page, u32* p_arg);
s32 PFCACHE_FreeDataPage(PF_VOLUME* p_vol, void* p_page);
void PFENT_StoreEntryNumericFieldsToBuf(u8* p_buf, PF_DIR_ENT* p_ent);
s32 PFSEC_WriteData(PF_VOLUME* p_vol, u8* p_buf, u32 sector, u32 offset, u32 size, u32* p_written, u32 arg7);
u32 PFENT_CalcCheckSum(PF_DIR_ENT* p_ent);
void PFENT_storeLFNEntryFieldsToBuf(u8* p_buf, PF_DIR_ENT* p_ent, u8 ordinal, u8 check_sum, u32 is_last);
s32 PFENT_updateEntry(PF_DIR_ENT* p_ent, u32 arg2);
void* pf_memcpy(void* dst, const void* src, u32 len);
void* pf_memset(void* dst, u8 c, u32 size);

s32 PFFILE_IsOpened(PF_DIR_ENT* p_ent);
void PFFILE_GetOpenedFile(PF_DIR_ENT* p_ent, PF_DIR_ENT** pp_ent);
s32 PFSTR_InitStr(PF_STR* p_str, const s8* name, u32 code_mode);
void PFFAT_FinalizeFFD(PF_FFD* p_ffd);
s32 PFDIR_CheckDirIsEmpty(PF_ENT_ITER* p_iter, u32* p_is_empty) {
    s32 err;
    u8 attr;

    u32 num_entry;

    if (*p_iter->ffd.p_start_cluster == 1 ||
        (p_iter->ffd.p_vol->bpb.fat_type == FAT_32 &&
         *p_iter->ffd.p_start_cluster == p_iter->ffd.p_vol->bpb.root_dir_cluster)) {
        num_entry = 0;
    } else {
        num_entry = 2;
    }
    *p_is_empty = 1;
    err = PFENT_ITER_MoveTo(p_iter, num_entry, 0);

    while (PFENT_ITER_IsAtLogicalEnd(p_iter) == 0) {
        if (err != 0) {
            return err == 0xD ? 0 : err;
        }
        if (p_iter->buf[0] != 0xE5) {
            attr = p_iter->buf[0xB];
            if (((attr & 0xF) != 0xF) && ((attr & 8) == 0)) {
                if (p_iter->buf[0] == 0) {
                    *p_is_empty = 1;
                } else {
                    *p_is_empty = 0;
                }
                break;
            }
        }
        err = PFENT_ITER_Advance(p_iter, 0);
    }
    return 0;
}

PF_SDD* PFDIR_GetSDD(PF_VOLUME* p_vol, PF_DIR_ENT* p_ent) {
    PF_SDD* p_sdd;
    s32 i;

    p_sdd = NULL;
    for (i = 0; i < 3; i++) {
        if ((p_vol->sdds[i].stat & 1) == 0) {
            if (p_sdd == NULL) {
                p_sdd = &p_vol->sdds[i];
            }
        } else if (((p_vol->sdds[i].stat & 1) == 0) || (p_vol->sdds[i].stat != 0)) {
            if ((p_vol->sdds[i].dir_entry.p_vol == p_ent->p_vol) &&
                (p_vol->sdds[i].dir_entry.entry_sector == p_ent->entry_sector) &&
                (p_vol->sdds[i].dir_entry.entry_offset == p_ent->entry_offset)) {
                return &p_vol->sdds[i];
            }
        }
    }

    if (p_sdd == NULL) {
        return NULL;
    }
    p_sdd->stat = 3;
    p_sdd->num_handlers = 0;
    p_sdd->dir_entry = *p_ent;
    PFFAT_InitFFD(&p_sdd->ffd, NULL, p_ent->p_vol, &p_sdd->dir_entry.start_cluster);
    return p_sdd;
}

s32 PFDIR_DoFsexecOpenDir(PF_DIR_ENT* p_ent, PF_ENT_ITER* p_iter, PF_UDD** pp_udd) {
    PF_VOLUME* p_vol;
    PF_SDD* p_sdd;
    PF_UDD* p_udd;
    s32 i;

    p_vol = p_ent->p_vol;
    *pp_udd = NULL;
    if ((p_ent->attr & 0x10) == 0) {
        return 0x14;
    }
    p_sdd = PFDIR_GetSDD(p_vol, p_ent);
    if (p_sdd == NULL) {
        return 0x15;
    }
    p_udd = NULL;
    for (i = 0; i < 3; i++) {
        if ((p_vol->udds[i].stat & 1) == 0) {
            p_udd = &p_vol->udds[i];
            break;
        }
    }
    if (p_udd == NULL) {
        return 0x16;
    }
    p_udd->p_sdd = p_sdd;
    p_udd->stat = 1;
    PFFAT_InitHint((PF_FAT_HINT*)&p_udd->hint);
    p_udd->field_14 = 0;
    p_udd->field_18 = 0;
    p_udd->field_1C = 0;
    p_sdd->num_handlers++;
    *pp_udd = p_udd;
    return 0;
}

s32 PFDIR_p_opendir(PF_VOLUME* p_vol, PF_STR* p_path_str, PF_UDD** pp_udd) {
    s32 err;
    PF_DIR_ENT ent;
    PF_ENT_ITER iter;

    if ((PFSTR_StrNCmp(p_path_str, (const s8*)"\\", 1, 0, 1) == 0 ||
         PFSTR_StrNCmp(p_path_str, (const s8*)"/", 1, 0, 1) == 0) &&
        PFSTR_StrNCmp(p_path_str, (const s8*)"\0", 1, 1, 1) == 0) {
        err = PFENT_GetRootDir(p_vol, &ent);
        if (err != 0) {
            return err;
        }
    } else if (PFSTR_StrNumChar(p_path_str, 1) == 2 &&
               PFSTR_StrNCmp(p_path_str, (const s8*)":", 1, 1, 1) == 0) {
        PFVOL_GetCurrentDir(p_vol, &ent);
    } else if (PFSTR_StrNumChar(p_path_str, 1) == 3 &&
               PFSTR_StrNCmp(p_path_str, (const s8*)":", 1, 1, 1) == 0 &&
               (PFSTR_StrNCmp(p_path_str, (const s8*)"\\", 1, 2, 1) == 0 ||
                PFSTR_StrNCmp(p_path_str, (const s8*)"/", 1, 2, 1) == 0)) {
        err = PFENT_GetRootDir(p_vol, &ent);
        if (err != 0) {
            return err;
        }
    } else {
        if (PFSTR_StrNCmp(p_path_str, (const s8*)":", 1, 1, 1) == 0 &&
            (PFSTR_StrNCmp(p_path_str, (const s8*)"\\", 1, 2, 1) == 0 ||
             PFSTR_StrNCmp(p_path_str, (const s8*)"/", 1, 2, 1) == 0)) {
            PFSTR_MoveStrPos(p_path_str, 2);
        }
        err = PFENT_ITER_GetEntryOfPath(&iter, &ent, p_vol, p_path_str, 0);
        if (err != 0) {
            return err;
        }
        if ((ent.attr & 0x10) == 0) {
            return 1;
        }
    }
    {
        PF_SDD* p_sdd;
        PF_UDD* p_udd;
        s32 i;

        p_sdd = PFDIR_GetSDD(p_vol, &ent);
        if (p_sdd == NULL) {
            return 0x15;
        }
        p_udd = NULL;
        for (i = 0; i < 3; i++) {
            if ((p_vol->udds[i].stat & 1) == 0) {
                p_udd = &p_vol->udds[i];
                break;
            }
        }
        if (p_udd == NULL) {
            return 0x16;
        }
        p_udd->p_sdd = p_sdd;
        p_udd->stat = 1;
        PFFAT_InitHint((PF_FAT_HINT*)&p_udd->hint);
        p_udd->field_14 = 0;
        p_udd->field_18 = 0;
        p_udd->field_1C = 0;
        p_sdd->num_handlers++;
        *pp_udd = p_udd;
    }
    return 0;
}

s32 PFDIR_p_readdir(PF_UDD* p_udd, PF_DIRENT* p_dirent) {
    PF_FFD ffd;
    PF_FAT_HINT hint;
    PF_DIR_ENT ent;
    PF_STR pattern;
    u32 remaining;
    u32 logical_position;
    u32 entry_position;
    s32 err;

    PFFAT_InitFFD(&ffd, &hint, p_udd->p_sdd->ffd.p_vol, &p_udd->p_sdd->dir_entry.start_cluster);
    remaining = p_udd->field_1C;
    if (p_udd->field_18 <= remaining) {
        remaining -= p_udd->field_18;
    } else if (p_udd->field_18 > remaining) {
        p_udd->field_14 = 0;
        p_udd->field_18 = 0;
    }
    do {
        PFSTR_InitStr(&pattern, (const s8*)"*", 1);
        PFSTR_SetLocalStr(&pattern, NULL);
        err = PFENT_findEntryPos(&ffd, &ent, p_udd->field_14, &pattern, 0x7F, 0,
                               &logical_position, &entry_position);
        if (err != 0) {
            return err;
        }
        p_udd->field_14 = entry_position + 1;
        p_udd->field_18++;
    } while (remaining-- != 0);
    p_udd->field_1C = p_udd->field_18;
    pf_strcpy(p_dirent->name, ent.short_name);
    if (ent.long_name[0] != 0) {
        PFPATH_transformFromUnicodeToNormal(p_dirent->lname, ent.long_name);
    } else {
        p_dirent->lname[0] = 0;
    }
    return 0;
}



s32 PFDIR_p_mkdir(PF_VOLUME* p_vol, PF_STR* p_path_str, u32 option, PF_DTA* p_dta) {
    s32 err;
    PF_STR dir_str;
    PF_STR file_str;
    PF_DIR_ENT ent;
    PF_DIR_ENT new_ent;
    PF_ENT_ITER iter;
    PF_FFD ffd;
    PF_FAT_HINT hint;
    PF_STR pattern;
    u16* pw;
    u8 buf[0x24];
    u32 pos_arr[4];
    u32 pos;
    u32 pos2;
    u32 found;
    u32 sector;
    void* p_page;
    u32 arg;
    u32 lfn_len;
    u32 num_lfn;
    u32 cluster;
    u8 check_sum;
    u32 written;
    u8* p_buf;
    u32 i;

    (void)option;

    sector = 0;
    err = PFPATH_SplitPath(p_path_str, &dir_str, &file_str);
    if (err != 0) {
        return err;
    }
    err = PFENT_ITER_GetEntryOfPath(&iter, &ent, p_vol, &dir_str, 1);
    if (err != 0) {
        return err;
    }
    if ((ent.attr & 0x10) == 0) {
        return 0x14;
    }
    lfn_len = PFSTR_StrNumChar(&file_str, 1);
    if ((u16)lfn_len + ent.path_len > 0x103) {
        return 2;
    }
    if ((u16)lfn_len > 0xFF) {
        return 1;
    }
    if (PFSTR_GetCodeMode(&file_str) == 2) {
        PFPATH_transformFromUnicodeToNormal((s8*)buf, (u16*)PFSTR_GetStrPos(&file_str, 1));
    }
    PFSTR_SetLocalStr(&file_str, (const s8*)buf);
    if (p_dta != NULL) {
        p_dta->file = NULL;
        p_dta->dir = NULL;
        p_dta->parent_start_cluster = ent.start_cluster;
        p_dta->vol = ent.p_vol;
        p_dta->attr = 0x10;
        if (PFSTR_GetCodeMode(&file_str) == 1) {
            PFPATH_SetSearchPattern(p_dta->reg_exp, NULL, &file_str);
            p_dta->status |= 1;
        } else {
            PFPATH_SetSearchPattern(p_dta->reg_exp, p_dta->reg_expW, &file_str);
            p_dta->status |= 2;
        }
    }
    PFFAT_InitFFD(&ffd, &hint, p_vol, &ent.start_cluster);
    iter.ffd = ffd;
    PFFAT_ResetFFD(&iter.ffd, &ent.start_cluster);
    err = PFENT_ITER_IteratorInitialize(&iter, 0);
    if (err != 0) {
        return err;
    }
    err = PFENT_ITER_FindEntry(&iter, &new_ent, &file_str, 0x10, 0, &found);
    if (err != 0) {
        return err;
    }
    if (found != 0) {
        return 8;
    }
    err = PFPATH_parseShortName(new_ent.short_name, &file_str);
    if (err != 0 && new_ent.short_name[0] == 0) {
        return 1;
    }
    if (err != 0) {
        err = PFENT_AdjustSFN(&ent, new_ent.short_name);
        if (err != 0) {
            return err;
        }
        if (PFSTR_GetCodeMode(&file_str) == 1) {
            lfn_len = (u16)PFPATH_transformInUnicode(new_ent.long_name, PFSTR_GetStrPos(&file_str, 1));
        } else {
            pf_w_strcpy(new_ent.long_name, (u16*)PFSTR_GetStrPos(&file_str, 1));
        }
    } else {
        new_ent.long_name[0] = 0;
    }
    new_ent.entry_sector = 0;
    new_ent.file_size = 0;
    new_ent.p_vol = p_vol;
    new_ent.small_letter_flag = 0;
    new_ent.attr = 0x10;
    new_ent.create_time_ms = PFENT_getcurrentDateTimeForEnt(&new_ent.create_date, &new_ent.create_time);
    new_ent.access_date = new_ent.create_date;
    new_ent.modify_time = new_ent.create_time;
    new_ent.modify_date = new_ent.create_date;
    if (new_ent.long_name[0] != 0 && (new_ent.small_letter_flag & 0x18) == 0) {
        num_lfn = (u32)(u16)lfn_len / 13 + ((u32)(u16)lfn_len % 13 != 0);
        err = PFENT_allocateEntryPos(&new_ent, (u8)(num_lfn + 1), &ffd, pos_arr, &file_str, &pos);
        if (err != 0) {
            return err;
        }
        if ((pf_vol_set.setting & 2) == 2) {
            PFPATH_AdjustExtShortName(new_ent.short_name, pos);
        }
    } else {
        err = PFENT_allocateEntryPos(&new_ent, 1, &ffd, pos_arr, &file_str, &pos);
        if (err != 0) {
            return err;
        }
    }
    PFFAT_ResetFFD(&ffd, &new_ent.start_cluster);
    err = PFFAT_GetSectorSpecified(&ffd, 0, 1, &sector);
    if (err != 0) {
        return err;
    }
    if (sector == -1u) {
        return 6;
    }
    cluster = ffd.p_hint->cluster;
    if (p_vol->bpb.fat_type == FAT_32 && *ffd.p_start_cluster == p_vol->bpb.root_dir_cluster &&
        new_ent.entry_offset == 0 && cluster == p_vol->bpb.root_dir_cluster) {
        iter.ffd = ffd;
        err = PFENT_ITER_IteratorInitialize(&iter, num_lfn);
        if (err != 0) {
            return err;
        }
        if (iter.buf[0] == 0) {
            *ffd.p_start_cluster = 0;
            ffd.p_hint->cluster = 0;
            cluster = p_vol->bpb.root_dir_cluster + 1;
            err = PFFAT_GetSectorSpecified(&ffd, 0, 1, &sector);
            if (err != 0) {
                return err;
            }
        }
    }
    err = PFCACHE_AllocateDataPage(p_vol, -1, &p_page, &arg);
    if (err != 0) {
        return err;
    }
    pf_memset(*(u8**)((u8*)p_page + 8), 0, p_vol->bpb.bytes_per_sector);
    i = p_vol->bpb.sectors_per_cluster;
    do {
        if (i == 1) {
            p_buf = *(u8**)((u8*)p_page + 8);
            p_buf[0] = 0x2E;
            p_buf[1] = 0x20;
            p_buf[2] = 0x20;
            p_buf[3] = 0x20;
            p_buf[4] = 0x20;
            p_buf[5] = 0x20;
            p_buf[6] = 0x20;
            p_buf[7] = 0x20;
            p_buf[8] = 0x20;
            p_buf[9] = 0x20;
            p_buf[0xA] = 0x20;
            PFENT_StoreEntryNumericFieldsToBuf(p_buf, &new_ent);
            p_buf[0x20] = 0x2E;
            p_buf[0x21] = 0x2E;
            p_buf[0x22] = 0x20;
            p_buf[0x23] = 0x20;
            p_buf[0x24] = 0x20;
            p_buf[0x25] = 0x20;
            p_buf[0x26] = 0x20;
            p_buf[0x27] = 0x20;
            p_buf[0x28] = 0x20;
            p_buf[0x29] = 0x20;
            p_buf[0x2A] = 0x20;
            if (new_ent.entry_sector == -1u) {
                new_ent.start_cluster = 0;
            } else {
                new_ent.start_cluster = ent.start_cluster;
            }
            PFENT_StoreEntryNumericFieldsToBuf(p_buf + 0x20, &new_ent);
        }
        err = PFSEC_WriteData(p_vol, *(u8**)((u8*)p_page + 8), sector + i - 1, 0,
                              p_vol->bpb.bytes_per_sector, &written, 0);
        if (err != 0) {
            break;
        }
        if (written != p_vol->bpb.bytes_per_sector) {
            err = 0x11;
            break;
        }
        i--;
    } while (i != 0);
    PFCACHE_FreeDataPage(p_vol, p_page);
    if (err != 0) {
        return err;
    }
    new_ent.num_entry_LFNs = num_lfn;
    check_sum = PFENT_CalcCheckSum(&new_ent);
    if ((new_ent.small_letter_flag & 0x18) == 0) {
        u8 ordinal;
        u32* p_pos;
        pos2 = new_ent.entry_sector;
        for (ordinal = num_lfn, p_pos = pos_arr; ordinal >= 1; ordinal--) {
            PFENT_storeLFNEntryFieldsToBuf(buf, &new_ent, ordinal, check_sum, ordinal == num_lfn);
            err = PFSEC_WriteData(p_vol, buf, pos2, new_ent.entry_offset, 0x20, &written, 0);
            if (err != 0) {
                return err;
            }
            if (written != 0x20) {
                return 0x11;
            }
            new_ent.entry_offset += 0x20;
            if (new_ent.entry_offset >= p_vol->bpb.bytes_per_sector) {
                new_ent.entry_offset = 0;
                pos2 = *p_pos++;
            }
        }
        new_ent.entry_sector = pos2;
    }
    new_ent.start_cluster = cluster;
    err = PFENT_updateEntry(&new_ent, 0);
    if (err != 0) {
        return err;
    }
    if (p_dta != NULL) {
        p_dta->parent_pos = pos + 1;
        pf_strcpy(p_dta->file_name, new_ent.short_name);
        if ((p_dta->status & 2) == 2) {
            PFPATH_transformInUnicode(p_dta->file_nameW, p_dta->file_name);
        }
        if (new_ent.long_name[0] != 0) {
            if ((pf_vol_set.setting & 2) == 2) {
                pf_vol_set.setting &= ~3u;
                pf_vol_set.setting |= 1;
                PFPATH_transformFromUnicodeToNormal(p_dta->long_name, new_ent.long_name);
                pf_vol_set.setting &= ~3u;
                pf_vol_set.setting |= 2;
            } else {
                PFPATH_transformFromUnicodeToNormal(p_dta->long_name, new_ent.long_name);
            }
            if ((p_dta->status & 2) == 2) {
                pf_w_strcpy(p_dta->long_nameW, new_ent.long_name);
            }
            p_dta->check_sum = check_sum;
            p_dta->ordinal = 1;
        } else {
            p_dta->long_name[0] = 0;
            if ((p_dta->status & 2) == 2) {
                p_dta->long_nameW[0] = 0;
            }
            p_dta->ordinal = 0;
            p_dta->check_sum = 0;
        }
        p_dta->file_size = new_ent.file_size;
        p_dta->time = new_ent.modify_time;
        p_dta->date = new_ent.modify_date;
        p_dta->attribute = new_ent.attr;
        p_dta->num_entry_LFNs = new_ent.num_entry_LFNs;
    }
    return 0;
}

s32 PFDIR_p_chdir(PF_VOLUME* p_vol, PF_STR* p_path_str) {
    s32 err;
    PF_DIR_ENT ent;
    PF_ENT_ITER iter;

    if ((PFSTR_StrNCmp(p_path_str, (const s8*)"\\", 1, 0, 1) == 0 ||
         PFSTR_StrNCmp(p_path_str, (const s8*)"/", 1, 0, 1) == 0) &&
        PFSTR_StrNCmp(p_path_str, (const s8*)"\0", 1, 1, 1) == 0) {
        err = PFENT_GetRootDir(p_vol, &ent);
        if (err != 0) {
            return err;
        }
        err = PFVOL_SetCurrentDir(p_vol, &ent);
        return err != 0 ? err : 0;
    }
    if (PFSTR_StrNumChar(p_path_str, 1) == 2 &&
        PFSTR_StrNCmp(p_path_str, (const s8*)":", 1, 1, 1) == 0) {
        return 0;
    }
    if (PFSTR_StrNumChar(p_path_str, 1) == 3 &&
        PFSTR_StrNCmp(p_path_str, (const s8*)":", 1, 1, 1) == 0 &&
        (PFSTR_StrNCmp(p_path_str, (const s8*)"\\", 1, 2, 1) == 0 ||
         PFSTR_StrNCmp(p_path_str, (const s8*)"/", 1, 2, 1) == 0)) {
        err = PFENT_GetRootDir(p_vol, &ent);
        if (err != 0) {
            return err;
        }
        err = PFVOL_SetCurrentDir(p_vol, &ent);
        return err != 0 ? err : 0;
    }
    if (PFSTR_StrNCmp(p_path_str, (const s8*)":", 1, 1, 1) == 0 &&
        (PFSTR_StrNCmp(p_path_str, (const s8*)"\\", 1, 2, 1) == 0 ||
         PFSTR_StrNCmp(p_path_str, (const s8*)"/", 1, 2, 1) == 0)) {
        PFSTR_MoveStrPos(p_path_str, 2);
    }
    err = PFENT_ITER_GetEntryOfPath(&iter, &ent, p_vol, p_path_str, 0);
    if (err != 0) {
        return err;
    }
    if ((ent.attr & 0x10) == 0) {
        return 0x14;
    }
    err = PFVOL_SetCurrentDir(p_vol, &ent);
    return err != 0 ? err : 0;
}

static u32 PFDIR_IsOpened(PF_DIR_ENT* p_ent) {
    PF_VOLUME* p_vol;
    s32 i;

    p_vol = p_ent->p_vol;
    {
        PF_SDD* p_sdd = p_vol->sdds;
        for (i = 0; i < 3; i++, p_sdd++) {
            if (((p_sdd->stat & 1) != 0) && ((p_sdd->stat & 2) != 0) &&
                (p_vol == p_sdd->dir_entry.p_vol) &&
                (p_ent->entry_sector == p_sdd->dir_entry.entry_sector) &&
                (p_ent->entry_offset == p_sdd->dir_entry.entry_offset)) {
                return 1;
            }
        }
    }
    return 0;
}

s32 PFDIR_p_chmod(PF_VOLUME* p_vol, PF_STR* p_path_str, u8 attr) {
    PF_STR dir_str;
    PF_STR file_str;
    PF_DIR_ENT ent;
    PF_ENT_ITER iter;
    s32 err;
    u16 dummy_time;
    u32 is_dir;

    err = PFPATH_SplitPath(p_path_str, &dir_str, &file_str);
    if (err != 0) {
        return err;
    }
    err = PFENT_ITER_GetEntryOfPath(&iter, &ent, p_vol, p_path_str, 0);
    if (err != 0) {
        return err;
    }
    is_dir = ent.attr & 0x10;
    if (((is_dir != 0) && ((attr & 0x10) == 0)) || ((is_dir == 0) && ((attr & 0x10) != 0))) {
        return 0xA;
    }
    if ((attr & 0x40) != 0) {
        attr &= ~0x40;
    }
    if (is_dir != 0) {
        if (PFDIR_IsOpened(&ent) != 0) {
            return 0x13;
        }
        if (((attr & 0x20) != 0) && ((attr & 0xF) != 0xF)) {
            return 0xA;
        }
        ent.attr = attr | 0x10;
    } else {
        if (PFFILE_IsOpened(&ent) != 0) {
            return 0x13;
        }
        ent.attr = attr;
    }
    PFENT_getcurrentDateTimeForEnt(&ent.access_date, &dummy_time);
    if ((ent.file_size == 0) && ((ent.attr & 0x10) == 0)) {
        ent.start_cluster = 0;
    }
    err = PFENT_updateEntry(&ent, 0);
    return err != 0 ? err : 0;
}

s32 PFDIR_p_rmdir(PF_VOLUME* p_vol, PF_STR* p_path_str) {
    PF_STR dir_str;
    PF_STR file_str;
    PF_DIR_ENT entry;
    PF_ENT_ITER iter;
    PF_ENT_ITER iter2;
    PF_FFD ffd;
    PF_FAT_HINT hint;
    PF_FAT_HINT hint2;
    u32 is_empty;
    s32 err;

    err = PFPATH_SplitPath(p_path_str, &dir_str, &file_str);
    if (err != 0) {
        return err;
    }
    err = PFENT_ITER_GetEntryOfPath(&iter, &entry, p_vol, p_path_str, 0);
    if (err != 0) {
        return err;
    }
    iter2 = iter;
    hint = *iter.ffd.p_hint;
    if (((entry.attr & 0x10) == 0) || ((entry.attr & 1) != 0)) {
        return 0x14;
    }
    if (PFDIR_IsOpened(&entry) != 0) {
        return 0x13;
    }
    if ((PFVOL_CheckCurrentDir(p_vol, entry.start_cluster) != 0) || (entry.start_cluster == 1) ||
        ((p_vol->bpb.fat_type == FAT_32) && (entry.start_cluster == p_vol->bpb.root_dir_cluster))) {
        return 0x1C;
    }
    PFFAT_InitFFD(&ffd, &hint2, p_vol, &entry.start_cluster);
    iter.ffd = ffd;
    err = PFENT_ITER_IteratorInitialize(&iter, 0);
    if (err != 0) {
        return err;
    }
    err = PFDIR_CheckDirIsEmpty(&iter, &is_empty);
    if (err != 0) {
        return err;
    }
    if (is_empty == 0) {
        return 0x1D;
    }
    iter = iter2;
    iter.ffd.p_hint = &hint;
    err = PFENT_RemoveEntry(&entry, &iter);
    if (err != 0) {
        return err;
    }
    err = PFFAT_FreeChain(&iter.ffd, entry.start_cluster, -1, -1);
    return err != 0 ? err : 0;
}

s32 PFDIR_p_fstat(PF_VOLUME* p_vol, PF_STR* p_path_str, PF_FSTAT* p_stat) {
    PF_ENT_ITER iter;
    PF_DIR_ENT ent;
    s32 err;
    s32 i;

    err = PFENT_ITER_GetEntryOfPath(&iter, &ent, p_vol, p_path_str, 0);
    if (err != 0) {
        return err;
    }
    i = 0;
    if (p_vol->num_open_files != 0) {
        for (i = 0; i < 5; i++) {
            if (((p_vol->file_handle[i].stat & 1) != 0) && ((p_vol->file_handle[i].stat & 2) != 0) &&
                (p_vol == p_vol->file_handle[i].dir_entry.p_vol) &&
                (ent.entry_sector == p_vol->file_handle[i].dir_entry.entry_sector) &&
                (ent.entry_offset == p_vol->file_handle[i].dir_entry.entry_offset)) {
                p_stat->file_size = p_vol->file_handle[i].dir_entry.file_size;
                p_stat->attr = p_vol->file_handle[i].dir_entry.attr;
                p_stat->modify_time = p_vol->file_handle[i].dir_entry.modify_time;
                p_stat->modify_date = p_vol->file_handle[i].dir_entry.modify_date;
                p_stat->create_time = p_vol->file_handle[i].dir_entry.create_time;
                p_stat->create_date = p_vol->file_handle[i].dir_entry.create_date;
                p_stat->access_date = p_vol->file_handle[i].dir_entry.access_date;
                p_stat->create_time_ms = p_vol->file_handle[i].dir_entry.create_time_ms;
                break;
            }
        }
    }
    if ((p_vol->num_open_files == 0) || (i == 5)) {
        if ((ent.attr & 0x10) != 0) {
            p_stat->file_size = 0;
        } else {
            p_stat->file_size = ent.file_size;
        }
        p_stat->attr = ent.attr;
        p_stat->modify_time = ent.modify_time;
        p_stat->modify_date = ent.modify_date;
        p_stat->create_time = ent.create_time;
        p_stat->create_date = ent.create_date;
        p_stat->access_date = ent.access_date;
        p_stat->create_time_ms = ent.create_time_ms;
    }
    return 0;
}

s32 PFDIR_p_rename(PF_VOLUME* p_vol, PF_STR* p_path_str, PF_STR* p_new_path_str) {
    PF_STR sDir;
    PF_STR sFile;
    PF_STR sNewDir;
    PF_STR sNewFile;
    PF_DIR_ENT entry_dir;
    PF_DIR_ENT entry_dir2;
    PF_DIR_ENT entry;
    PF_DIR_ENT new_ent;
    PF_ENT_ITER iter;
    PF_ENT_ITER iter2;
    PF_FFD ffd;
    PF_FAT_HINT hint;
    PF_FAT_HINT hint2;
    s8 buf[0x200];
    s8 buf2[0x24];
    u32 pos_arr[4];
    u32 pos;
    u32 pos2;
    u32 ppos;
    u32 start_cluster;
    u32 num_lfn;
    u32 lfn_len;
    u32 written;
    u8 ordinal;
    u32 i;
    s32 err;
    s32 err2;
    u8* p_buf;
    u32* p_pos;
    u32 is_current;
    u16 time_var;
    PF_VOLUME* p_ent_vol;
    PF_DIR_ENT* p_ent2;

    buf[0] = dir_mark;
    err = 0;
    err2 = 0;
    num_lfn = 0;
    ordinal = 0;
    err = PFPATH_SplitPath(p_path_str, &sDir, &sFile);
    if (err != 0) {
        return err;
    }
    if (PFSTR_GetCodeMode(&sFile) == 2) {
        if ((s32)(u16)PFSTR_StrNumChar(&sFile, 1) > 0xFF) {
            return 1;
        }
        PFPATH_transformFromUnicodeToNormal(buf, (u16*)PFSTR_GetStrPos(&sFile, 1));
        PFSTR_SetLocalStr(&sFile, buf);
    }
    err = PFENT_ITER_GetEntryOfPath(&iter, &entry_dir, p_vol, p_path_str, 1);
    if (err != 0) {
        return err;
    }
    PFFAT_InitFFD(&iter.ffd, &hint, p_vol, &iter.ffd.field_04);
    iter.ffd.field_04 = entry_dir.start_cluster;
    err = PFENT_ITER_IteratorInitialize(&iter, 0);
    if (err != 0) {
        return err;
    }
    err = PFENT_ITER_FindEntry(&iter, &entry, &sFile, 0x7F, 0, &pos);
    if (err != 0) {
        return err;
    }
    if (pos == 0) {
        return 3;
    }
    if ((entry.attr & 8) != 0) {
        return 3;
    }
    if ((entry.attr & 1) != 0) {
        return 0x18;
    }
    if ((PFSTR_StrNCmp(p_new_path_str, (const s8*)"/", 1, 1, 1) == 0) &&
        (PFPATH_GetVolumeFromPath(p_new_path_str) != p_vol)) {
        return 0x1F;
    }
    err = PFPATH_SplitPath(p_new_path_str, &sNewDir, &sNewFile);
    if (err != 0) {
        return err;
    }
    if (PFSTR_GetCodeMode(&sNewFile) == 2) {
        if ((s32)(u16)PFSTR_StrNumChar(&sNewFile, 1) > 0xFF) {
            return 1;
        }
        PFPATH_transformFromUnicodeToNormal(buf, (u16*)PFSTR_GetStrPos(&sNewFile, 1));
        PFSTR_SetLocalStr(&sNewFile, buf);
    }
    if (PFSTR_GetCodeMode(&sNewFile) == 1) {
        err = pf_strcmp(PFSTR_GetStrPos(&sNewFile, 1), PFSTR_GetStrPos(&sFile, 1));
    } else {
        err = pf_w_strcmp((u16*)PFSTR_GetStrPos(&sNewFile, 1), (u16*)PFSTR_GetStrPos(&sFile, 1));
    }
    if (err != 0) {
        err = PFENT_ITER_GetEntryOfPath(&iter2, &entry_dir2, p_vol, p_new_path_str, 1);
        if (err != 0) {
            return err;
        }
        if (entry_dir2.start_cluster != entry_dir.start_cluster) {
            return 0x20;
        }
    }
    start_cluster = entry_dir.start_cluster;
    PFFAT_InitFFD(&ffd, &hint2, p_vol, &start_cluster);
    err = PFENT_findEntry(&ffd, &new_ent, 0, &sNewFile, 0x7F, 0);
    if (err != 0) {
        if (err != 3) {
            return err;
        }
    } else {
        return 8;
    }
    if ((entry.attr & 0x10) == 0) {
        if (PFFILE_IsOpened(&entry) != 0) {
            return 0x13;
        }
    } else {
        if (PFDIR_IsOpened(&entry) != 0) {
            return 0x13;
        }
    }
    p_ent_vol = entry.p_vol;
    is_current = 0;
    for (i = 0; i < 4; i++) {
        if (pf_vol_set.current_vol[i].p_vol == p_ent_vol) {
            PF_VOLUME* p_v = pf_vol_set.current_vol[i].p_vol;
            for (pos2 = 0; pos2 < 4; pos2++) {
                if (((p_v->current_dir[pos2].stat & 1) != 0) &&
                    (p_v->current_dir[pos2].directory.start_cluster == entry.start_cluster)) {
                    is_current = 1;
                }
            }
        }
    }
    if (is_current != 0) {
        return 0x1C;
    }
    if (PFSTR_StrNCmp(&sFile, (const s8*)"..", 1, 0, 2) == 0) {
        return 0x1C;
    }
    if (PFSTR_StrNCmp(&sFile, (const s8*)".", 1, 0, 1) == 0) {
        return 0x1C;
    }
    start_cluster = entry.start_cluster;
    err = PFPATH_StrNumChar(&sNewFile, 1);
    if ((u32)(u16)err + entry_dir.path_len > 0x103) {
        return 1;
    }
    if (((entry.attr & 0x10) == 0) && ((u16)err > 0xFF)) {
        return 1;
    }
    new_ent = entry;
    err2 = PFPATH_parseShortName(buf2, &sNewFile);
    if (buf2[0] == 0) {
        return 2;
    }
    if (err2 == 0 && entry.long_name[0] == 0) {
        new_ent.long_name[0] = 0;
        new_ent.small_letter_flag = 0;
        PFENT_getcurrentDateTimeForEnt(&new_ent.access_date, &time_var);
        err = PFENT_updateEntry(&new_ent, 1);
        return err != 0 ? err : 0;
    }
    if (entry.long_name[0] != 0 && (entry.small_letter_flag & 0x18) == 0) {
        ordinal = 1;
        for (i = 1; i <= entry.num_entry_LFNs; i++) {
            err = PFENT_ITER_Retreat(&iter, 0);
            if (err != 0) {
                return err;
            }
            err = PFSEC_WriteData(p_vol, (u8*)buf, iter.field_44, (u16)iter.field_48, 1, &written, 0);
            if (err != 0) {
                return err;
            }
            if (written != 1) {
                return 0x11;
            }
            ordinal++;
        }
        err = PFSEC_WriteData(p_vol, (u8*)buf, entry.entry_sector, entry.entry_offset, 1, &written, 0);
        if (err != 0) {
            return err;
        }
        if (written != 1) {
            return 0x11;
        }
        if ((p_vol->buffer_mode & 0x20) != 0) {
            err = PFCACHE_FlushDataCache(p_vol);
            if (err != 0) {
                return err;
            }
        }
    }
    if (err2 != 0) {
        err = PFENT_AdjustSFN(&entry_dir, buf2);
        if (err != 0) {
            return err;
        }
        if (PFSTR_GetCodeMode(&sNewFile) == 1) {
            lfn_len = PFPATH_transformInUnicode(new_ent.long_name, PFSTR_GetStrPos(&sNewFile, 1));
        } else {
            pf_w_strcpy(new_ent.long_name, (u16*)PFSTR_GetStrPos(&sNewFile, 1));
        }
        num_lfn = lfn_len / 13 + (lfn_len % 13 != 0);
        new_ent.num_entry_LFNs = num_lfn;
    } else {
        new_ent.num_entry_LFNs = 0;
    }
    new_ent.small_letter_flag = 0;
    PFFAT_InitFFD(&ffd, &hint2, p_vol, &entry_dir.start_cluster);
    err = PFENT_allocateEntryPos(&new_ent, (u8)(num_lfn + 1), &ffd, pos_arr, &sNewFile, &pos2);
    err2 = err;
    if (err != 0) {
        if (entry.num_entry_LFNs != 0 && (entry.small_letter_flag & 0x18) == 0) {
            entry.entry_offset += (entry.num_entry_LFNs * 0x20);
            new_ent.entry_sector = start_cluster;
        }
        return err;
    }
    if ((pf_vol_set.setting & 2) == 2) {
        PFPATH_AdjustExtShortName(buf2, pos2);
    }
    new_ent.check_sum = PFENT_CalcCheckSum(&new_ent);
    PFENT_getcurrentDateTimeForEnt(&new_ent.access_date, &time_var);
    p_ent2 = &new_ent;
    if (new_ent.num_entry_LFNs != 0 && (new_ent.small_letter_flag & 0x18) == 0) {
        ppos = new_ent.entry_sector;
        p_pos = pos_arr;
        for (ordinal = 1; ordinal <= new_ent.num_entry_LFNs; ordinal++) {
            PFENT_storeLFNEntryFieldsToBuf((u8*)buf2, &new_ent, ordinal, new_ent.check_sum, ordinal == new_ent.num_entry_LFNs);
            err = PFSEC_WriteData(p_vol, (u8*)buf2, ppos, new_ent.entry_offset, 0x20, &written, 0);
            if (err != 0) {
                return err;
            }
            if (written != 0x20) {
                return 0x11;
            }
            new_ent.entry_offset += 0x20;
            if (new_ent.entry_offset >= p_vol->bpb.bytes_per_sector) {
                new_ent.entry_offset = 0;
                ppos = *p_pos++;
            }
        }
        new_ent.entry_sector = ppos;
    }
    err = PFENT_updateEntry(&new_ent, 1);
    return err != 0 ? err : 0;
}

s32 PFDIR_p_move(PF_VOLUME* p_vol, PF_STR* p_path_str, PF_STR* p_new_path_str) {
    PF_STR sDir;
    PF_STR sFile;
    PF_STR sNewDir;
    PF_STR sNewFile;
    PF_STR sDotDot;
    PF_DIR_ENT entry;
    PF_DIR_ENT entry_dir;
    PF_DIR_ENT ent2;
    PF_DIR_ENT new_ent;
    PF_ENT_ITER iter;
    PF_ENT_ITER iter2;
    PF_FAT_HINT hint;
    PF_FAT_HINT hint2;
    s8 buf[0x200];
    s8 buf2[0x24];
    u32 pos_arr[4];
    u32 pos;
    u32 pos2;
    u32 ppos;
    u32 start_cluster;
    u32 num_lfn;
    u32 lfn_len;
    u32 written;
    u8 ordinal;
    u32 i;
    s32 err;
    s32 err2;
    u32 is_current;
    u16 time_var;
    PF_VOLUME* p_ent_vol;
    PF_DIR_ENT* p_ent;
    u32* p_pos;
    u32 j;

    buf[0] = dir_mark_move;
    err = 0;
    num_lfn = 0;
    err = PFENT_ITER_GetEntryOfPath(&iter, &entry, p_vol, p_path_str, 0);
    if (err != 0) {
        return err;
    }
    if (PFPATH_GetVolumeFromPath(p_new_path_str) != p_vol) {
        return 0x1F;
    }
    err = PFPATH_SplitPath(p_new_path_str, &sNewDir, &sNewFile);
    if (err != 0) {
        return err;
    }
    if (PFSTR_GetCodeMode(&sNewFile) == 2) {
        if ((s32)(u16)PFSTR_StrNumChar(&sNewFile, 1) > 0xFF) {
            return 1;
        }
        PFPATH_transformFromUnicodeToNormal(buf, (u16*)PFSTR_GetStrPos(&sNewFile, 1));
        PFSTR_SetLocalStr(&sNewFile, buf);
    }
    err = PFENT_ITER_GetEntryOfPath(&iter2, &entry_dir, p_vol, p_new_path_str, 1);
    if (err != 0) {
        return err;
    }
    ent2.start_cluster = entry_dir.start_cluster;
    PFFAT_InitFFD(&iter2.ffd, &hint, p_vol, &ent2.start_cluster);
    err = PFENT_findEntry(&iter2.ffd, &ent2, 0, &sNewFile, 0x7F, 0);
    if (err == 0) {
        if (ent2.entry_sector == entry.entry_sector && ent2.entry_offset == entry.entry_offset) {
            return 0;
        }
        return 8;
    } else if (err != 3) {
        return err;
    }
    if ((entry.attr & 0x10) == 0) {
        if (PFFILE_IsOpened(&entry) != 0) {
            return 0x13;
        }
    } else {
        if (PFDIR_IsOpened(&entry) != 0) {
            return 0x13;
        }
    }
    start_cluster = entry.start_cluster;
    for (i = 0; i < 5; i++) {
        PF_SFD* p_sfd_f = &p_vol->file_handle[i];
        if ((p_sfd_f->stat & 1) == 0 || (p_sfd_f->stat & 2) == 0) {
            continue;
        }
        if (p_sfd_f->dir_entry.p_vol == p_vol &&
            p_sfd_f->dir_entry.entry_sector == (u32)(p_vol->bpb.first_data_sector + ((start_cluster - 2) << p_vol->bpb.log2_sectors_per_cluster))) {
            return 0x13;
        }
    }
    p_ent_vol = entry.p_vol;
    is_current = 0;
    for (i = 0; i < 4; i++) {
        if (pf_vol_set.current_vol[i].p_vol == p_ent_vol) {
            PF_VOLUME* p_v = pf_vol_set.current_vol[i].p_vol;
            for (j = 0; j < 4; j++) {
                if (((p_v->current_dir[j].stat & 1) != 0) &&
                    (p_v->current_dir[j].directory.start_cluster == entry.start_cluster)) {
                    is_current = 1;
                }
            }
        }
    }
    if (is_current != 0) {
        return 0x1C;
    }
    err = PFPATH_SplitPath(p_path_str, &sDir, &sFile);
    if (err != 0) {
        return err;
    }
    if (PFSTR_StrNCmp(&sFile, (const s8*)"..", 1, 0, 2) == 0) {
        return 0xA;
    }
    if (PFSTR_StrNCmp(&sFile, (const s8*)".", 1, 0, 1) == 0) {
        return 0xA;
    }
    ent2.start_cluster = entry_dir.start_cluster;
    while (ent2.start_cluster != 1 && ent2.start_cluster != 0) {
        PFFAT_InitFFD(&iter2.ffd, &hint, p_vol, &ent2.start_cluster);
        PFSTR_InitStr(&sDotDot, (const s8*)"..", 1);
        PFSTR_SetLocalStr(&sDotDot, NULL);
        err = PFENT_findEntry(&iter2.ffd, &ent2, 0, &sDotDot, 0x7F, 0);
        if (err != 0) {
            return err;
        }
        if (ent2.start_cluster == 1 || ent2.start_cluster == 0) {
            break;
        }
        PFFAT_ResetFFD(&iter2.ffd, &ent2.start_cluster);
        err = PFENT_ITER_IteratorInitialize(&iter2, 0);
        if (err != 0) {
            return err;
        }
        err = PFENT_ITER_FindDirEntryFromCluster(&iter2, &ent2, ent2.start_cluster, &pos);
        if (err != 0) {
            return err;
        }
        if (ent2.start_cluster == entry.start_cluster) {
            return 0xA;
        }
    }
    lfn_len = (u16)PFSTR_StrNumChar(&sNewFile, 1);
    if (lfn_len + entry_dir.path_len > 0x103) {
        return 1;
    }
    if (((entry.attr & 0x10) == 0) && (lfn_len > 0xFF)) {
        return 1;
    }
    pf_memcpy(&new_ent, &entry, 0x240);
    err2 = PFPATH_parseShortName(buf2, &sNewFile);
    if (buf2[0] == 0) {
        return 2;
    }
    if (entry.long_name[0] != 0 && (entry.small_letter_flag & 0x18) == 0) {
        ordinal = 1;
        new_ent.long_name[0] = 0;
        for (i = 1; i <= entry.num_entry_LFNs; i++) {
            err = PFENT_ITER_Retreat(&iter, 0);
            if (err != 0) {
                return err;
            }
            err = PFSEC_WriteData(p_vol, (u8*)buf, iter.field_44, (u16)iter.field_48, 1, &written, 0);
            if (err != 0) {
                return err;
            }
            if (written != 1) {
                return 0x11;
            }
            ordinal++;
        }
        err = PFSEC_WriteData(p_vol, (u8*)buf, entry.entry_sector, entry.entry_offset, 1, &written, 0);
        if (err != 0) {
            return err;
        }
        if (written != 1) {
            return 0x11;
        }
        if ((p_vol->buffer_mode & 0x20) != 0) {
            err = PFCACHE_FlushDataCache(p_vol);
            if (err != 0) {
                return err;
            }
        }
    }
    if (err2 != 0) {
        err = PFENT_AdjustSFN(&entry_dir, buf2);
        if (err != 0) {
            return err;
        }
        if (PFSTR_GetCodeMode(&sNewFile) == 1) {
            lfn_len = PFPATH_transformInUnicode(new_ent.long_name, PFSTR_GetStrPos(&sNewFile, 1));
        } else {
            pf_w_strcpy(new_ent.long_name, (u16*)PFSTR_GetStrPos(&sNewFile, 1));
        }
        num_lfn = lfn_len / 13 + (lfn_len % 13 != 0);
        new_ent.num_entry_LFNs = num_lfn;
    } else {
        new_ent.num_entry_LFNs = 0;
    }
    new_ent.small_letter_flag = 0;
    PFFAT_InitFFD(&iter2.ffd, &hint2, p_vol, &entry_dir.start_cluster);
    err = PFENT_allocateEntryPos(&new_ent, (u8)(num_lfn + 1), &iter2.ffd, pos_arr, &sNewFile, &pos2);
    err2 = err;
    if (err != 0) {
        if (entry.num_entry_LFNs != 0 && (entry.small_letter_flag & 0x18) == 0) {
            entry.entry_offset += (entry.num_entry_LFNs * 0x20);
            p_ent = &entry;
            goto write_back;
        }
        return err;
    }
    if ((pf_vol_set.setting & 2) == 2) {
        PFPATH_AdjustExtShortName(buf2, pos2);
    }
    new_ent.check_sum = PFENT_CalcCheckSum(&new_ent);
    PFENT_getcurrentDateTimeForEnt(&new_ent.access_date, &time_var);
    p_ent = &new_ent;
    if ((entry.attr & 0x10) != 0) {
        PFFAT_InitFFD(&iter.ffd, &hint2, p_vol, &entry.start_cluster);
        PFSTR_InitStr(&sDotDot, (const s8*)"..", 1);
        PFSTR_SetLocalStr(&sDotDot, NULL);
        err = PFENT_findEntry(&iter.ffd, &entry, 0, &sDotDot, 0x7F, 0);
        if (err != 0) {
            return err;
        }
        if (entry_dir.start_cluster == 1 || entry_dir.start_cluster == 0) {
            entry.start_cluster = 0;
        } else if (entry_dir.start_cluster == 2 && p_vol->bpb.fat_type != 2) {
            entry.start_cluster = 0;
        } else {
            entry.start_cluster = entry_dir.start_cluster;
        }
        err = PFENT_updateEntry(&entry, 1);
        if (err != 0) {
            return err;
        }
        if ((p_vol->buffer_mode & 0x20) != 0) {
            err = PFCACHE_FlushDataCache(p_vol);
            if (err != 0) {
                return err;
            }
        }
    }
write_back:
    if (p_ent->num_entry_LFNs != 0 && (p_ent->small_letter_flag & 0x18) == 0) {
        ppos = p_ent->entry_sector;
        p_pos = pos_arr;
        ordinal = 1;
        while (ordinal <= p_ent->num_entry_LFNs) {
            PFENT_storeLFNEntryFieldsToBuf((u8*)buf, p_ent, ordinal, p_ent->check_sum,
                                           ordinal == p_ent->num_entry_LFNs);
            err = PFSEC_WriteData(p_vol, (u8*)buf, ppos, p_ent->entry_offset, 0x20, &written, 0);
            if (err != 0) {
                return err;
            }
            if (written != 0x20) {
                return 0x11;
            }
            p_ent->entry_offset += 0x20;
            if (p_ent->entry_offset >= p_vol->bpb.bytes_per_sector) {
                p_ent->entry_offset = 0;
                ppos = *p_pos++;
            }
            ordinal++;
        }
        p_ent->entry_sector = ppos;
    }
    err = PFENT_updateEntry(p_ent, 1);
    return err != 0 ? err : 0;
}



s32 PFDIR_p_fsnext(PF_DTA* p_dta) {
    s32 err;
    PF_FFD ffd;
    PF_FAT_HINT fat_hint;
    PF_DIR_ENT ent;
    s32 i;
    u32 ppos;
    u32 pos;
    PF_STR pattern;
    u32 code_mode;

    ppos = 0;
    pos = 0;
    if ((p_dta->status & 1) == 1) {
        code_mode = 1;
        err = PFSTR_InitStr(&pattern, p_dta->reg_exp, code_mode);
    } else {
        code_mode = 2;
        err = PFSTR_InitStr(&pattern, (s8*)p_dta->reg_expW, code_mode);
    }
    if (err != 0) {
        return err;
    }
    if (code_mode == 1) {
        PFSTR_SetLocalStr(&pattern, p_dta->reg_exp);
    }
    while (ppos < 0xF423F) {
        if (p_dta->parent_pos >= 0xF423F) {
            return 0xA;
        }
        ent.start_cluster = p_dta->parent_start_cluster;
        PFFAT_InitFFD(&ffd, &fat_hint, p_dta->vol, &ent.start_cluster);
        err = PFENT_findEntryPos(&ffd, &ent, p_dta->parent_pos, &pattern, p_dta->attr, NULL, &ppos, &pos);
        if (err != 0) {
            return err;
        }
        p_dta->parent_pos = pos + 1;
        if (pos == 0xF423F) {
            return 3;
        }
        break;
    }
    pf_strcpy(p_dta->file_name, ent.short_name);
    if ((p_dta->status & 2) == 2) {
        PFPATH_transformInUnicode(p_dta->file_nameW, p_dta->file_name);
    }
    if (ent.long_name[0] != 0) {
        if ((pf_vol_set.setting & 2) == 2) {
            pf_vol_set.setting &= ~3u;
            pf_vol_set.setting |= 1;
            PFPATH_transformFromUnicodeToNormal(p_dta->long_name, ent.long_name);
            pf_vol_set.setting &= ~3u;
            pf_vol_set.setting |= 2;
        } else {
            PFPATH_transformFromUnicodeToNormal(p_dta->long_name, ent.long_name);
        }
        if ((p_dta->status & 2) == 2) {
            pf_w_strcpy(p_dta->long_nameW, ent.long_name);
        }
    } else {
        p_dta->long_name[0] = 0;
        if ((p_dta->status & 2) == 2) {
            p_dta->long_nameW[0] = 0;
        }
    }
    i = 0;
    if (p_dta->vol->num_open_files != 0) {
        for (i = 0; i < 5; i++) {
            if (((p_dta->vol->file_handle[i].stat & 1) != 0) && ((p_dta->vol->file_handle[i].stat & 2) != 0) &&
                (p_dta->vol == p_dta->vol->file_handle[i].dir_entry.p_vol) &&
                (ent.entry_sector == p_dta->vol->file_handle[i].dir_entry.entry_sector) &&
                (ent.entry_offset == p_dta->vol->file_handle[i].dir_entry.entry_offset)) {
                p_dta->file_size = p_dta->vol->file_handle[i].dir_entry.file_size;
                p_dta->time = p_dta->vol->file_handle[i].dir_entry.modify_time;
                p_dta->date = p_dta->vol->file_handle[i].dir_entry.modify_date;
                p_dta->attribute = p_dta->vol->file_handle[i].dir_entry.attr;
                p_dta->num_entry_LFNs = p_dta->vol->file_handle[i].dir_entry.num_entry_LFNs;
                p_dta->ordinal = p_dta->vol->file_handle[i].dir_entry.ordinal;
                p_dta->check_sum = p_dta->vol->file_handle[i].dir_entry.check_sum;
                break;
            }
        }
    }
    if ((p_dta->vol->num_open_files == 0) || (i == 5)) {
        p_dta->file_size = ent.file_size;
        p_dta->time = ent.modify_time;
        p_dta->date = ent.modify_date;
        p_dta->attribute = ent.attr;
        p_dta->num_entry_LFNs = ent.num_entry_LFNs;
        p_dta->ordinal = ent.ordinal;
        p_dta->check_sum = ent.check_sum;
    }
    return 0;
}

s32 PFDIR_p_fsfirst(PF_VOLUME* p_vol, PF_STR* p_path_str, u8 attr, PF_DTA* p_dta) {
    PF_STR sDir;
    PF_STR sPattern;
    PF_DIR_ENT ent;
    PF_ENT_ITER iter;
    s32 err;

    err = PFPATH_SplitPathPattern(p_path_str, &sDir, &sPattern);
    if (err != 0) {
        return err;
    }
    err = PFENT_ITER_GetEntryOfPattern(&iter, &ent, p_vol, &sDir);
    if (err != 0) {
        return err;
    }
    if ((ent.attr & 0x10) == 0) {
        return 0x14;
    }
    p_dta->parent_start_cluster = ent.start_cluster;
    p_dta->parent_pos = 0;
    p_dta->vol = ent.p_vol;
    p_dta->attr = attr;
    p_dta->status = 0;
    if (PFSTR_GetCodeMode(&sPattern) == 1) {
        PFPATH_SetSearchPattern(p_dta->reg_exp, NULL, &sPattern);
        p_dta->status |= 1;
    } else {
        PFPATH_SetSearchPattern(p_dta->reg_exp, p_dta->reg_expW, &sPattern);
        p_dta->status |= 2;
    }
    return PFDIR_p_fsnext(p_dta);
}

s32 PFENT_ITER_GetLFNEntryName(PF_ENT_ITER* p_iter);
s32 PFFILE_FsexecOpenFile(PF_DIR_ENT* p_ent, PF_ENT_ITER* p_iter, u32 mode, PF_DTA* p_dta);

s32 PFDIR_p_fsexec_chmod(PF_DTA* p_dta, PF_DIR_ENT* p_ent, u32 mode, u32 arg) {
    u8 attr;
    u16 time_var;
    s32 err;

    attr = (u8)(arg & 0xFBFF);
    if ((arg & 0x40) != 0) {
        if ((p_ent->attr & 0x10) != 0) {
            if ((attr & 8) != 0) {
                return 0xA;
            }
            if (PFDIR_IsOpened(p_ent) != 0) {
                return 0x13;
            }
            p_ent->attr = attr | 0x10;
        } else {
            if ((attr & 0x10) != 0) {
                return 0xA;
            }
            if (PFFILE_IsOpened(p_ent) != 0) {
                return 0x13;
            }
            p_ent->attr = attr;
        }
    }
    PFENT_getcurrentDateTimeForEnt(&p_ent->access_date, &time_var);
    err = PFENT_updateEntry(p_ent, 0);
    if (err != 0) {
        return err;
    }
    if ((mode & 1) == 0) {
        p_dta->attribute = p_ent->attr;
        err = PFCACHE_FlushDataCacheSpecific(p_ent->p_vol, 0);
        if (err != 0) {
            return err;
        }
    }
    return 0;
}


s32 PFDIR_p_fsexec_remove(PF_DTA* p_dta, PF_DIR_ENT* p_ent, PF_ENT_ITER* p_iter) {
    PF_ENT_ITER iter_save;
    PF_FAT_HINT hint_save;
    u32 is_empty;
    u32 pos;
    s32 err;
    u32 start_cluster;
    s32 chain_arg;

    if ((p_ent->attr & 1) != 0) {
        return 0x18;
    }
    if ((p_ent->attr & 0x10) != 0) {
        if (PFVOL_CheckCurrentDir(p_ent->p_vol, p_ent->start_cluster) != 0 ||
            p_ent->start_cluster == 1 ||
            (p_ent->p_vol->bpb.fat_type == 2 &&
             p_ent->start_cluster == p_ent->p_vol->bpb.root_dir_cluster)) {
            return 0x1C;
        }
        if (PFDIR_IsOpened(p_ent) != 0) {
            return 0x13;
        }
        iter_save = *p_iter;
        hint_save = *p_iter->ffd.p_hint;
        PFFAT_ResetFFD(&p_iter->ffd, &p_ent->start_cluster);
        err = PFENT_ITER_IteratorInitialize(p_iter, 0);
        if (err != 0) {
            return err;
        }
        err = PFDIR_CheckDirIsEmpty(p_iter, &is_empty);
        if (err != 0) {
            return err;
        }
        if (is_empty == 0) {
            return 0x1D;
        }
        *p_iter = iter_save;
        p_iter->ffd.p_hint = &hint_save;
        chain_arg = -1;
    } else {
        if (PFFILE_IsOpened(p_ent) != 0) {
            return 0x13;
        }
        chain_arg = p_ent->file_size;
    }
    start_cluster = p_ent->start_cluster;
    p_ent->num_entry_LFNs = p_dta->num_entry_LFNs;
    p_ent->ordinal = p_dta->ordinal;
    p_ent->check_sum = p_dta->check_sum;
    err = PFENT_RemoveEntry(p_ent, p_iter);
    if (err != 0) {
        return err;
    }
    err = PFFAT_FreeChain(&p_iter->ffd, start_cluster, -1, chain_arg);
    return err != 0 ? err : 0;
}

s32 PFDIR_p_fsexec_fopen(PF_DTA* p_dta, PF_DIR_ENT* p_ent, PF_ENT_ITER* p_iter, u32 flags, u32 mode) {
    s8 long_name[13];
    s32 err;

    if ((flags & 0x80000000) != 0) {
        p_ent->num_entry_LFNs = p_dta->num_entry_LFNs;
        p_ent->ordinal = p_dta->ordinal;
        p_ent->check_sum = p_dta->check_sum;
        if ((p_iter->buf[0xC] & 0x18) != 0) {
            PFPATH_getLongNameformShortName(p_ent->short_name, long_name, p_iter->buf[0xC]);
            PFPATH_transformInUnicode(p_ent->long_name, long_name);
        } else {
            err = PFENT_ITER_GetLFNEntryName(p_iter);
            if (err != 0) {
                return err;
            }
        }
    }
    err = PFFILE_FsexecOpenFile(p_ent, p_iter, mode, p_dta);
    if (err != 0) {
        return err;
    }
    err = 0;
    p_dta->vol->num_open_files++;
    return err;
}


s32 PFDIR_p_fsexec_opendir(PF_DTA* p_dta, PF_DIR_ENT* p_ent, PF_ENT_ITER* p_iter, u32 flags) {
    s8 long_name[13];
    s32 err;

    if ((flags & 0x80000000) != 0) {
        p_ent->num_entry_LFNs = p_dta->num_entry_LFNs;
        p_ent->ordinal = p_dta->ordinal;
        p_ent->check_sum = p_dta->check_sum;
        if ((p_iter->buf[0xC] & 0x18) != 0) {
            PFPATH_getLongNameformShortName(p_ent->short_name, long_name, p_iter->buf[0xC]);
            PFPATH_transformInUnicode(p_ent->long_name, long_name);
        } else {
            err = PFENT_ITER_GetLFNEntryName(p_iter);
            if (err != 0) {
                return err;
            }
        }
    }
    err = PFDIR_DoFsexecOpenDir(p_ent, p_iter, (PF_UDD**)&p_dta->dir);
    if (err != 0) {
        return err;
    }
    err = 0;
    p_dta->vol->num_open_dirs++;
    return err;
}


s32 PFDIR_p_fsexec_chmod(PF_DTA* p_dta, PF_DIR_ENT* p_ent, u32 mode, u32 arg);
s32 PFDIR_p_fsexec_remove(PF_DTA* p_dta, PF_DIR_ENT* p_ent, PF_ENT_ITER* p_iter);
s32 PFDIR_p_fsexec_fopen(PF_DTA* p_dta, PF_DIR_ENT* p_ent, PF_ENT_ITER* p_iter, u32 mode, u32 arg);
s32 PFDIR_p_fsexec_opendir(PF_DTA* p_dta, PF_DIR_ENT* p_ent, PF_ENT_ITER* p_iter, u32 mode);
s32 PFENT_ITER_FindEntryNoPathCheck(PF_ENT_ITER* p_iter, PF_DIR_ENT* p_ent, PF_STR* p_pattern,
                                    u32 attr, u32 flag, u32* p_pos);
s32 PFENT_ITER_GetEntryOfIter(PF_ENT_ITER* p_iter, PF_DIR_ENT* p_ent);

s32 PFDIR_p_fsexec(PF_DTA* p_dta, u32 mode, u32 arg) {
    PF_FFD ffd;
    PF_FAT_HINT hint;
    PF_ENT_ITER iter;
    PF_DIR_ENT ent;
    PF_STR sPattern;
    PF_STR sPattern2;
    s8 buf[0x104];
    s8 dot_buf[11];
    u32 dst_cluster;
    u32 pos;
    u32 mode_6;
    u32 mode_1;
    s32 err;
    s32 result;

    mode_6 = mode & 6;
    if (mode_6 == 0 && (mode & 1) == 0 && (mode & 0x10) == 0 && (mode & 0x20) == 0) {
        return 0xA;
    }
    if (mode_6 == 0) {
        if ((mode & 1) == 0 && (mode & 0x10) != 0 && arg != 2) {
            err = PFVOL_CheckForWrite(p_dta->vol);
            if (err != 0) {
                return err;
            }
        }
    }
    buf[0] = 0;
    dst_cluster = p_dta->parent_start_cluster;
    PFFAT_InitFFD(&ffd, &hint, p_dta->vol, &dst_cluster);
    iter.ffd = ffd;
    mode_1 = mode & 1;
    err = PFENT_ITER_IteratorInitialize(&iter,
                                        p_dta->parent_pos - 1 - (mode_1 ? 0 : p_dta->num_entry_LFNs));
    if (err != 0) {
        return err;
    }
    if (mode_1 == 0) {
        if ((p_dta->status & 1) == 1) {
            err = PFSTR_InitStr(&sPattern, p_dta->file_name, 1);
        } else {
            if ((pf_vol_set.setting & 2) == 2) {
                err = PFSTR_InitStr(&sPattern, (const s8*)p_dta->long_nameW, 2);
            } else {
                err = PFSTR_InitStr(&sPattern, (const s8*)p_dta->file_nameW, 2);
            }
        }
        if (err != 0) {
            return err;
        }
        if ((pf_vol_set.setting & 2) == 2) {
            PFSTR_SetLocalStr(&sPattern, p_dta->long_name);
        } else {
            PFSTR_SetLocalStr(&sPattern, p_dta->file_name);
        }
        err = PFENT_ITER_FindEntryNoPathCheck(&iter, &ent, &sPattern, 0x7F, 0, &pos);
        if (err != 0) {
            return err;
        }
        if ((p_dta->status & 2) == 2) {
            if ((pf_vol_set.setting & 2) != 2) {
                err = PFPATH_cmpName(ent.short_name, &sPattern, 1);
                if (err != 0) {
                    return 3;
                }
            }
        } else {
            err = PFSTR_InitStr(&sPattern2, p_dta->long_name, 1);
            if (err != 0) {
                return err;
            }
            PFSTR_SetLocalStr(&sPattern2, p_dta->long_name);
            err = PFPATH_cmpNameUni(ent.long_name, &sPattern2);
            if (err != 0) {
                return 3;
            }
        }
        if (iter.buf[0] == 0) {
            return 3;
        }
        if (iter.buf[0] == 0xE5) {
            return 3;
        }
        if ((mode & 0x20) == 0) {
            if ((iter.buf[0xB] & 0x18) != 0) {
                return 3;
            }
        }
        if ((mode & 0x20) != 0) {
            if ((iter.buf[0xB] & 0x10) != 0 && (iter.buf[0xB] & 8) != 0) {
                return 0x14;
            }
        }
        err = PFENT_ITER_GetEntryOfIter(&iter, &ent);
        if (err != 0) {
            return err;
        }
        dot_buf[0] = '.';
        dot_buf[1] = ' ';
        dot_buf[2] = ' ';
        dot_buf[3] = ' ';
        dot_buf[4] = ' ';
        dot_buf[5] = ' ';
        dot_buf[6] = ' ';
        dot_buf[7] = ' ';
        dot_buf[8] = ' ';
        dot_buf[9] = ' ';
        dot_buf[10] = ' ';
        if (pf_strncmp(ent.short_name, dot_buf, 1) == 0) {
            return 0x1C;
        }
        dot_buf[0] = '.';
        dot_buf[1] = '.';
        dot_buf[2] = ' ';
        dot_buf[3] = ' ';
        dot_buf[4] = ' ';
        dot_buf[5] = ' ';
        dot_buf[6] = ' ';
        dot_buf[7] = ' ';
        dot_buf[8] = ' ';
        dot_buf[9] = ' ';
        dot_buf[10] = ' ';
        if (pf_strncmp(ent.short_name, dot_buf, 2) == 0) {
            return 0x1C;
        }
    }
    if (mode_6 != 0) {
        result = PFDIR_p_fsexec_chmod(p_dta, &ent, mode, arg);
    } else if ((mode & 1) != 0) {
        result = PFDIR_p_fsexec_remove(p_dta, &ent, &iter);
    } else if ((mode & 0x10) != 0) {
        result = PFDIR_p_fsexec_fopen(p_dta, &ent, &iter, mode, arg);
    } else if ((mode & 0x20) != 0) {
        result = PFDIR_p_fsexec_opendir(p_dta, &ent, &iter, mode);
    }
    return result;
}


s32 PFDIR_p_seekdir(PF_UDD* p_udd, u32 pos);

void PFDIR_FinalizeAllDirs(PF_VOLUME* p_vol) {
    u16 i;

    for (i = 0; i < 3; i++) {
        p_vol->sdds[i].stat = 0;
        PFFAT_FinalizeFFD(&p_vol->sdds[i].ffd);
    }
    for (i = 0; i < 3; i++) {
        p_vol->udds[i].stat &= ~1;
    }
    p_vol->num_open_dirs = 0;
}


s32 PFDIR_fsfirst(PF_STR* p_path_str, u8 attr, PF_DTA* p_dta) {
    PF_VOLUME* p_vol = PFPATH_GetVolumeFromPath(p_path_str);
    s32 err = PFVOL_CheckForRead(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    err = PFDIR_p_fsfirst(p_vol, p_path_str, attr, p_dta);
    if (err != 0) {
        p_dta->vol = NULL;
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
    }
    return err;
}

s32 PFDIR_fsnext(PF_DTA* p_dta) {
    PF_VOLUME* p_vol = p_dta->vol;
    s32 err = PFVOL_CheckForRead(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    err = PFDIR_p_fsnext(p_dta);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
    }
    return err;
}

s32 PFDIR_fsexec(PF_DTA* p_dta, u32 mode, u32 arg) {
    PF_VOLUME* p_vol = p_dta->vol;
    s32 err = PFVOL_CheckForRead(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    p_vol->cache_signature = NULL;
    err = PFDIR_p_fsexec(p_dta, mode, arg);
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
    p_vol->cache_signature = NULL;
    return err;
}

s32 PFDIR_fstat(PF_STR* p_path_str, PF_FSTAT* p_stat) {
    PF_VOLUME* p_vol = PFPATH_GetVolumeFromPath(p_path_str);
    s32 err = PFVOL_CheckForRead(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    err = PFDIR_p_fstat(p_vol, p_path_str, p_stat);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
    }
    return err;
}

s32 PFDIR_rename(PF_STR* p_old_path, PF_STR* p_new_path) {
    PF_VOLUME* p_vol = PFPATH_GetVolumeFromPath(p_old_path);
    s32 err = PFVOL_CheckForWrite(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    p_vol->cache_signature = NULL;
    err = PFDIR_p_rename(p_vol, p_old_path, p_new_path);
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

s32 PFDIR_move(PF_STR* p_old_path, PF_STR* p_new_path) {
    PF_VOLUME* p_vol = PFPATH_GetVolumeFromPath(p_old_path);
    s32 err = PFVOL_CheckForWrite(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    p_vol->cache_signature = NULL;
    err = PFDIR_p_move(p_vol, p_old_path, p_new_path);
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

s32 PFDIR_opendir(PF_STR* p_path_str, PF_UDD** pp_udd) {
    PF_VOLUME* p_vol = PFPATH_GetVolumeFromPath(p_path_str);
    s32 err = PFVOL_CheckForRead(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    err = PFDIR_p_opendir(p_vol, p_path_str, pp_udd);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
    } else {
        p_vol->num_open_dirs++;
    }
    return err;
}

s32 PFDIR_closedir(PF_UDD* p_udd) {
    PF_VOLUME* p_vol;
    s32 err;

    if (p_udd == NULL) {
        p_vol = NULL;
    } else {
        p_vol = p_udd->p_sdd->dir_entry.p_vol;
    }
    err = PFVOL_CheckForWrite(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    if ((p_udd->p_sdd->stat & 1) == 0 || (p_udd->p_sdd->stat & 2) == 0) {
        pf_vol_set.last_error = 0xA;
        p_vol->last_error = 0xA;
        return 0xA;
    }
    if (--p_udd->p_sdd->num_handlers == 0) {
        p_udd->p_sdd->stat &= ~1;
    }
    p_udd->stat &= ~1;
    p_vol->num_open_dirs--;
    return 0;
}

s32 PFDIR_readdir(PF_UDD* p_udd, PF_DIRENT* p_dirent) {
    PF_VOLUME* p_vol;
    s32 err;

    if (p_udd == NULL) {
        p_vol = NULL;
    } else {
        p_vol = p_udd->p_sdd->dir_entry.p_vol;
    }
    err = PFVOL_CheckForWrite(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    if ((p_udd->p_sdd->stat & 1) == 0 || (p_udd->p_sdd->stat & 2) == 0) {
        pf_vol_set.last_error = 0xA;
        p_vol->last_error = 0xA;
        return 0xA;
    }
    err = PFDIR_p_readdir(p_udd, p_dirent);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
    }
    return err;
}

s32 PFDIR_telldir(PF_UDD* p_udd, u32* p_pos) {
    PF_VOLUME* p_vol;
    s32 err;

    if (p_udd == NULL) {
        p_vol = NULL;
    } else {
        p_vol = p_udd->p_sdd->dir_entry.p_vol;
    }
    err = PFVOL_CheckForWrite(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    if ((p_udd->p_sdd->stat & 1) == 0 || (p_udd->p_sdd->stat & 2) == 0) {
        pf_vol_set.last_error = 0xA;
        p_vol->last_error = 0xA;
        return 0xA;
    }
    if (p_udd->field_1C != 0) {
        *p_pos = p_udd->field_1C;
    } else {
        *p_pos = p_udd->field_18;
    }
    return err;
}

s32 PFDIR_seekdir(PF_UDD* p_udd, u32 pos) {
    PF_VOLUME* p_vol;
    s32 err;

    if (p_udd == NULL) {
        p_vol = NULL;
    } else {
        p_vol = p_udd->p_sdd->dir_entry.p_vol;
    }
    err = PFVOL_CheckForWrite(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    if ((p_udd->p_sdd->stat & 1) == 0 || (p_udd->p_sdd->stat & 2) == 0) {
        pf_vol_set.last_error = 0xA;
        p_vol->last_error = 0xA;
        return 0xA;
    }
    p_udd->field_1C = pos;
    return err;
}

s32 PFDIR_rmdir(PF_STR* p_path_str) {
    PF_VOLUME* p_vol = PFPATH_GetVolumeFromPath(p_path_str);
    s32 err = PFVOL_CheckForWrite(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    p_vol->cache_signature = NULL;
    err = PFDIR_p_rmdir(p_vol, p_path_str);
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
    p_vol->cache_signature = NULL;
    return err;
}

s32 PFDIR_mkdir(PF_STR* p_path_str) {
    PF_VOLUME* p_vol = PFPATH_GetVolumeFromPath(p_path_str);
    s32 err = PFVOL_CheckForWrite(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    p_vol->cache_signature = NULL;
    err = PFDIR_p_mkdir(p_vol, p_path_str, 0, NULL);
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

void PFDIR_createdir(PF_STR* p_path_str, u32 option, PF_DTA* p_dta) {
    PF_VOLUME* p_vol = PFPATH_GetVolumeFromPath(p_path_str);
    s32 err = PFVOL_CheckForWrite(p_vol);

    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return;
    }
    p_vol->cache_signature = NULL;
    err = PFDIR_p_mkdir(p_vol, p_path_str, option, p_dta);
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
}


s32 PFDIR_chdir(PF_STR* p_path_str) {
    PF_VOLUME* p_vol = PFPATH_GetVolumeFromPath(p_path_str);
    s32 err = PFVOL_CheckForRead(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    err = PFDIR_p_chdir(p_vol, p_path_str);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
    } else {
        PFVOL_SetCurrentVolume(p_vol);
    }
    return err;
}

s32 PFDIR_fchdir(PF_UDD* p_udd) {
    PF_VOLUME* p_vol;
    s32 err;

    if (p_udd == NULL) {
        p_vol = NULL;
    } else {
        p_vol = p_udd->p_sdd->dir_entry.p_vol;
    }
    err = PFVOL_CheckForRead(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    if ((p_udd->p_sdd->stat & 1) == 0 || (p_udd->p_sdd->stat & 2) == 0) {
        pf_vol_set.last_error = 0xA;
        p_vol->last_error = 0xA;
        return 0xA;
    }
    err = PFVOL_SetCurrentDir(p_vol, &p_udd->p_sdd->dir_entry);
    err = err != 0 ? err : 0;
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
    } else {
        PFVOL_SetCurrentVolume(p_vol);
    }
    return err;
}

s32 PFDIR_chmod(PF_STR* p_path_str, u8 attr) {
    PF_VOLUME* p_vol = PFPATH_GetVolumeFromPath(p_path_str);
    s32 err = PFVOL_CheckForWrite(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    p_vol->cache_signature = NULL;
    err = PFDIR_p_chmod(p_vol, p_path_str, attr);
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

s32 PFDIR_chdmod(PF_STR* p_path_str, u8 attr) {
    PF_VOLUME* p_vol = PFPATH_GetVolumeFromPath(p_path_str);
    s32 err = PFVOL_CheckForWrite(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    p_vol->cache_signature = NULL;
    err = PFDIR_p_chmod(p_vol, p_path_str, (u8)(attr | 0x10));
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
