#include <private/vf/PrFILE2/fatfs/pf_entry.h>

typedef struct PFITER_FAT_HINT {
    pf_u32 chain_index;
    pf_u32 cluster;
    pf_u32 previous_cluster;
} PFITER_FAT_HINT;

typedef struct PFITER_FFD {
    pf_u32 start_cluster;
    pf_u32 current_start_cluster;
    pf_u32* p_start_cluster;
    PF_LAST_CLUSTER last_cluster;
    PF_FAT_LAST_ACCESS last_access_cluster;
    PF_CLUSTER_LINK cluster_link;
    PFITER_FAT_HINT* p_hint;
    PF_VOLUME* p_vol;
} PFITER_FFD;

typedef struct PFITER_ENT_ITER {
    pf_u32 index;
    PF_VOLUME* p_vol;
    PFITER_FFD ffd;
    pf_u32 file_sector_index;
    pf_u32 sector;
    pf_u16 offset;
    pf_u16 offset_mask;
    pf_u8 buf[32];
    pf_u8 log2_entries_per_sector;
} PFITER_ENT_ITER;

typedef struct PFITER_BPB {
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
} PFITER_BPB;

struct PF_VOLUME {
    PFITER_BPB bpb;
};

typedef struct PFITER_CONTEXT_VOLUME {
    pf_u32 stat;
    pf_s32 context_id;
    PF_VOLUME* p_vol;
} PFITER_CONTEXT_VOLUME;

typedef struct PFITER_VOLUME_SET {
    pf_u32 flags;
    pf_u32 reserved;
    PF_VOLUME* current_volume;
    PFITER_CONTEXT_VOLUME context_volumes[3];
    pf_s32 num_attached;
    pf_s32 num_mounted;
    pf_u32 config;
    void* user_data;
    pf_s32 last_error;
    pf_s32 last_driver_error;
    void (*code_callbacks[6])(void);
    pf_u32 setting;
} PFITER_VOLUME_SET;

extern PFITER_VOLUME_SET pf_vol_set;
pf_s8* PFSTR_GetStrPos(PF_STR*, pf_u32);
pf_u32 PFSTR_GetCodeMode(PF_STR* p_str);
void PFSTR_MoveStrPos(PF_STR* p_str, pf_s16 num_char);
pf_u16 PFSTR_StrLen(PF_STR* p_str);
pf_u16 PFSTR_StrNumChar(PF_STR* p_str, pf_u32 target);
pf_s32 PFSTR_StrCmp(const PF_STR* p_str, const pf_s8* s);
pf_s32 PFSTR_StrNCmp(PF_STR* p_str, const pf_s8* s, pf_u32 target, pf_s16 offset, pf_u16 num);
void* pf_memcpy(void* dst, void* src, pf_u32 length);
void* pf_memset(void* dst, pf_s32 c, pf_u32 length);
pf_s32 pf_strncmp(const pf_s8* s1, const pf_s8* s2, pf_u32 length);
pf_u8 PFENT_CalcCheckSum(PF_DIR_ENT* p_ent);
void PFENT_LoadShortNameFromBuf(PF_DIR_ENT* p_ent, const pf_u8* buf);
void PFENT_loadEntryNumericFieldsFromBuf(PF_DIR_ENT* p_ent, const pf_u8* buf);
pf_s32 PFENT_LoadLFNEntryFieldsFromBuf(PF_DIR_ENT* p_ent, const pf_u8* buf);
pf_s32 PFENT_GetRootDir(PF_VOLUME* p_vol, PF_DIR_ENT* p_ent);
pf_s32 PFFAT_GetSectorSpecified(PFITER_FFD* p_ffd, pf_u32 file_sector_index, pf_u32 may_allocate, pf_u32* p_sector);
pf_s32 PFFAT_getBeforeChain(PF_VOLUME* p_vol, pf_u32 start_cluster, pf_u32 lActive, pf_u32* p_cluster);
pf_s32 PFFAT_ResetFFD(PFITER_FFD* p_ffd, pf_u32* p_start_cluster);
pf_s32 PFFAT_InitFFD(PFITER_FFD* p_ffd, PFITER_FAT_HINT* p_hint, PF_VOLUME* p_vol, pf_u32* p_start_cluster);
void PFPATH_InitTokenOfPath(PF_STR* p_str, pf_s8* path, pf_u32 code_mode);
pf_s32 PFPATH_GetNextTokenOfPath(PF_STR* p_str, pf_bool wildcard);
pf_bool PFPATH_MatchFileNameWithPattern(const pf_s8* file_name, PF_STR* p_pattern, pf_bool is_long_name);
void PFPATH_getLongNameformShortName(pf_s8* short_name, pf_s8* long_name, pf_u8 flag);
pf_u32 PFPATH_GetLengthFromShortname(const pf_s8* sSrc);
pf_u32 PFPATH_GetLengthFromUnicode(const pf_u16* sSrc);
pf_s32 PFPATH_transformInUnicode(pf_u16* sDestStr, const pf_s8* sSrcStr);
pf_bool PFPATH_GetExtShortNameIndex(PF_STR* p_str, pf_u32* p_index);
pf_s32 PFSEC_ReadData(PF_VOLUME* p_vol, pf_u8* p_buf, pf_u32 sector, pf_u16 offset, pf_u32 size, pf_u32* p_success_size, pf_bool set_sig);
pf_s32 PFSEC_WriteData(PF_VOLUME* p_vol, const pf_u8* p_buf, pf_u32 sector, pf_u16 offset, pf_u32 size, pf_u32* p_success_size, pf_bool set_sig);
pf_s32 PFVOL_GetCurrentDir(PF_VOLUME*, PF_DIR_ENT*);
pf_s32 PFCACHE_AllocateDataPage(PF_VOLUME*, pf_u32, PF_CACHE_PAGE**, pf_bool*);
pf_s32 PFCACHE_FreeDataPage(PF_VOLUME*, PF_CACHE_PAGE*);
pf_s32 PFENT_RecalcEntryIterator(PFITER_ENT_ITER*, pf_u32);
pf_s32 PFENT_ITER_IteratorInitialize(PFITER_ENT_ITER*, pf_u32);
pf_bool PFENT_ITER_IsAtLogicalEnd(PFITER_ENT_ITER*);
pf_s32 PFENT_ITER_MoveTo(PFITER_ENT_ITER*, pf_u32, pf_u32);
pf_s32 PFENT_ITER_Advance(PFITER_ENT_ITER*, pf_u32);
pf_s32 PFENT_ITER_Retreat(PFITER_ENT_ITER*, pf_u32);
pf_s32 PFENT_ITER_FindDirEntryFromCluster(PFITER_ENT_ITER*, PF_DIR_ENT*, pf_u32, pf_bool*);

#pragma dont_inline on
pf_s32 PFENT_RecalcEntryIterator(PFITER_ENT_ITER* p_iter, pf_u32 may_allocate) {
    pf_u32 file_sector_index;
    pf_u32 previous_fsindex;
    pf_u32 sector_count;
    pf_s32 err;
    PF_CACHE_PAGE* page;
    pf_u32 success_size;
    pf_bool hit;
    file_sector_index = p_iter->index >> p_iter->log2_entries_per_sector;
    previous_fsindex = p_iter->file_sector_index;
    if (file_sector_index != p_iter->file_sector_index) {
        p_iter->file_sector_index = file_sector_index;
        err = PFFAT_GetSectorSpecified(&p_iter->ffd, file_sector_index, 0, &p_iter->sector);
        if (err != 0) return err;
        if (p_iter->sector == -1U && may_allocate != 0) {
            err = PFFAT_GetSectorSpecified(&p_iter->ffd, file_sector_index, 1, &p_iter->sector);
            if (err != 0) return err;
            if (p_iter->sector != -1U && previous_fsindex != -1U) {
                err = PFCACHE_AllocateDataPage(p_iter->p_vol, -1U, &page, &hit);
                if (err != 0) return err;
                pf_memset(page->p_buf, 0, p_iter->p_vol->bpb.bytes_per_sector);
                for (sector_count = 0; sector_count < p_iter->p_vol->bpb.sectors_per_cluster; ++sector_count) {
                    err = PFSEC_WriteData(p_iter->p_vol, page->p_buf, p_iter->sector + sector_count, 0,
                        p_iter->p_vol->bpb.bytes_per_sector, &success_size, 0);
                    if (err != 0) {
                        PFCACHE_FreeDataPage(p_iter->p_vol, page);
                        return err;
                    }
                    if (success_size != p_iter->p_vol->bpb.bytes_per_sector) {
                        PFCACHE_FreeDataPage(p_iter->p_vol, page);
                        return 17;
                    }
                }
                PFCACHE_FreeDataPage(p_iter->p_vol, page);
            }
        }
    }
    p_iter->offset = (p_iter->index & p_iter->offset_mask) * 32;
    return 0;
}
#pragma dont_inline reset

static inline pf_s32 PFENT_ITER_LoadEntry(PFITER_ENT_ITER* p_iter) {
    pf_u32 success_size;
    pf_s32 err;

    if (p_iter->sector == -1) {
        return 16;
    }
    err = PFSEC_ReadData(p_iter->p_vol, p_iter->buf, p_iter->sector, p_iter->offset, 0x20U, &success_size, 0U);
    if (success_size != 0x20) {
        return 17;
    }
    return err;
}

static inline pf_s32 PFENT_ITER_DoMoveTo(PFITER_ENT_ITER* p_iter, pf_u32 index, pf_u32 may_allocate) {
    pf_u32 prev_index = p_iter->index;
    pf_s32 err;

    p_iter->index = index;
    err = PFENT_RecalcEntryIterator(p_iter, may_allocate);
    if (err != 0) {
        p_iter->index = prev_index;
        PFENT_RecalcEntryIterator(p_iter, 0U);
        return err;
    }
    err = PFENT_ITER_LoadEntry(p_iter);
    if (err != 0) {
        return err;
    }
    return 0;
}

static inline void PFENT_ITER_MakeLongFileName(PFITER_ENT_ITER* p_iter, PF_DIR_ENT* p_ent) {
    pf_s32 lengthName;
    signed char filename[13];

    lengthName = 0;
    PFPATH_getLongNameformShortName(p_ent->short_name, filename, p_iter->buf[0xC]);
    lengthName = PFPATH_transformInUnicode(p_ent->long_name, filename);
    p_ent->num_entry_LFNs = ((lengthName % 13) ? 1 : 0) + (lengthName / 13);
    p_ent->check_sum = PFENT_CalcCheckSum(p_ent);
    p_ent->ordinal = 1;
}

static inline pf_s32 InitializeIterator(PFITER_ENT_ITER* p_iter, pf_u32 index) {
    p_iter->p_vol = p_iter->ffd.p_vol;
    p_iter->log2_entries_per_sector = p_iter->p_vol->bpb.log2_bytes_per_sector - 5;
    p_iter->offset_mask = (1 << p_iter->log2_entries_per_sector) - 1;
    p_iter->file_sector_index = -1U;
    return PFENT_ITER_DoMoveTo(p_iter, index, 0);
}

static inline pf_s32 AdvanceIterator(PFITER_ENT_ITER* p_iter, pf_u32 may_allocate) {
    pf_s32 err = PFENT_ITER_DoMoveTo(p_iter, p_iter->index + 1, may_allocate);
    if (err != 0) return err;
    return 0;
}

static inline void LoadNumericEntry(PFITER_ENT_ITER* p_iter, PF_DIR_ENT* p_ent) {
    PFENT_loadEntryNumericFieldsFromBuf(p_ent, p_iter->buf);
    p_ent->entry_sector = p_iter->sector;
    p_ent->entry_offset = p_iter->offset;
    p_ent->p_vol = p_iter->ffd.p_vol;
    if ((p_ent->attr & 0x10) && p_ent->start_cluster == 0) p_ent->start_cluster = 1;
}

pf_s32 PFENT_ITER_DoFindEntry(PFITER_ENT_ITER* p_iter, PF_DIR_ENT* p_ent, PF_STR* p_pattern,
    pf_u32 attr_required, pf_u32 attr_forbidden, pf_bool* p_is_found) {
    pf_s32 err = 0;
    pf_u32 index_search_from;
    pf_u32 is_extsfn = 0;
    *p_is_found = 0;
    if (PFSTR_StrCmp(p_pattern, (pf_s8*)"..") == 0 && (p_ent->attr & 0x10) && p_ent->start_cluster == 1) return 2;
    if (PFSTR_StrCmp(p_pattern, (pf_s8*)".") == 0) {
        *p_is_found = 1;
        return 0;
    }
    p_ent->num_entry_LFNs = 0;
    p_ent->ordinal = 0;
    p_ent->check_sum = 0;
    p_ent->long_name[0] = 0;
    if ((pf_vol_set.setting & 2) == 2) is_extsfn = PFPATH_GetExtShortNameIndex(p_pattern, &index_search_from);
    if (is_extsfn == 1) {
        for (err = InitializeIterator(p_iter, index_search_from - 1);; err = PFENT_ITER_Retreat(p_iter, 0)) {
            pf_s32 attr;
            if (err != 0) return err;
            if ((p_iter->buf[11] & 15) == 15) {
                if (PFENT_LoadLFNEntryFieldsFromBuf(p_ent, p_iter->buf) != 0) return 3;
                if (!(p_iter->buf[0] & 0x40)) continue;
            } else return 0;
            err = InitializeIterator(p_iter, index_search_from);
            if (err != 0) return err;
            attr = p_iter->buf[11];
            if (attr == 0) attr = 0x40;
            if (attr_required & 0x80) {
                attr_required &= 0x7f;
                attr_forbidden &= 0x7f;
                if ((attr_required && (pf_s32)(attr_required & attr) != (pf_s32)attr_required) ||
                    (attr_forbidden && (pf_s32)(attr_forbidden & attr) == (pf_s32)attr_forbidden)) err = -1;
            } else if (attr_required != 0x7f && attr != attr_required &&
                (!(attr & attr_required) || (attr & attr_forbidden))) err = -1;
            if (err == -1) return 0;
            if (attr & 8) return 3;
            PFENT_LoadShortNameFromBuf(p_ent, p_iter->buf);
            if (PFPATH_MatchFileNameWithPattern(p_ent->short_name, p_pattern, 0)) {
                LoadNumericEntry(p_iter, p_ent);
                *p_is_found = 1;
                return 0;
            }
            goto finish;
        }
    }
    for (; PFENT_ITER_IsAtLogicalEnd(p_iter) == PF_FALSE; err = AdvanceIterator(p_iter, 0)) {
        pf_s32 attr;
        if (err != 0) return err;
        if (p_iter->buf[0] == 0) break;
        if (p_iter->buf[0] == 0xe5) {
            p_ent->num_entry_LFNs = 0;
            p_ent->long_name[0] = 0;
            continue;
        }
        attr = p_iter->buf[11];
        if ((attr & 15) == 15) {
            if (PFENT_LoadLFNEntryFieldsFromBuf(p_ent, p_iter->buf) != 0) {
                p_ent->num_entry_LFNs = 0;
                p_ent->long_name[0] = 0;
            }
            continue;
        }
        if (attr == 0) attr = 0x40;
        if (attr_required & 0x80) {
            attr_required &= 0x7f;
            attr_forbidden &= 0x7f;
            if ((attr_required && (pf_s32)(attr_required & attr) != (pf_s32)attr_required) ||
                (attr_forbidden && (pf_s32)(attr_forbidden & attr) == (pf_s32)attr_forbidden)) err = -1;
        } else if ((pf_u8)attr_required != 0x7f && (pf_u32)attr != (pf_u8)attr_required &&
            (!(attr & (pf_u8)attr_required) || (attr & (pf_u8)attr_forbidden))) err = -1;
        if (err == -1) {
            p_ent->num_entry_LFNs = 0;
            p_ent->long_name[0] = 0;
            continue;
        }
        if (attr & 8) {
            p_ent->num_entry_LFNs = 0;
            p_ent->long_name[0] = 0;
        }
        PFENT_LoadShortNameFromBuf(p_ent, p_iter->buf);
        if (p_ent->num_entry_LFNs && p_ent->ordinal == 1 && p_ent->check_sum == PFENT_CalcCheckSum(p_ent) &&
            PFPATH_MatchFileNameWithPattern((pf_s8*)p_ent->long_name, p_pattern, 1)) {
            LoadNumericEntry(p_iter, p_ent);
            *p_is_found = 1;
            return 0;
        }
        if (PFPATH_MatchFileNameWithPattern(p_ent->short_name, p_pattern, 0)) {
            if (p_iter->buf[12] & 0x18) PFENT_ITER_MakeLongFileName(p_iter, p_ent);
            LoadNumericEntry(p_iter, p_ent);
            *p_is_found = 1;
            return 0;
        }
        p_ent->num_entry_LFNs = 0;
        p_ent->long_name[0] = 0;
    }
finish:
    return 0;
}

pf_s32 PFENT_ITER_DoGetEntry(PFITER_ENT_ITER* p_iter, PF_DIR_ENT* p_ent, PF_VOLUME* p_vol, PF_STR* p_path, pf_bool wildcard,
                                       pf_bool no_look_last_token) {
    pf_s8* p;
    PF_STR token;
    pf_bool is_found;
    PFITER_FAT_HINT hint;
    pf_u32 start_cluster;
    PF_DIR_ENT current_ent;
    pf_s32 err;
    pf_u32 code_mode;

    if (PFSTR_StrNCmp(p_path, (pf_s8*)":", 1, 1, 1) == 0) {
        PFSTR_MoveStrPos(p_path, 2);
    }
    if ((PFSTR_StrNCmp(p_path, (pf_s8*)"\\", 1, 0, 1) == 0 || PFSTR_StrNCmp(p_path, (pf_s8*)"/", 1, 0, 1) == 0)) {
        err = PFENT_GetRootDir(p_vol, p_ent);
        if (err != 0) {
            return err;
        }
        if (PFSTR_StrNumChar(p_path, 1) == 1 && (PFSTR_StrNCmp(p_path, (pf_s8*)"\0", 2, 0, 1) == 0)) {
            return 0;
        }
    } else {
        err = PFVOL_GetCurrentDir(p_vol, p_ent);
        if (err != 0) {
            return err;
        }
    }
    p = PFSTR_GetStrPos(p_path, 1);
    PFFAT_InitFFD(&p_iter->ffd, &hint, p_vol, &p_iter->ffd.current_start_cluster);
    p_iter->ffd.current_start_cluster = p_ent->start_cluster;
    code_mode = PFSTR_GetCodeMode(p_path);
    PFPATH_InitTokenOfPath(&token, p, code_mode);

    for (err = PFPATH_GetNextTokenOfPath(&token, wildcard); token.p_head != 0; err = PFPATH_GetNextTokenOfPath(&token, wildcard)) {
        if (err != 0) {
            return err;
        }
        if (no_look_last_token != 0 && (PFSTR_StrNCmp(&token, (pf_s8*)"\0", 2, 0, 1) == 0)) {
            break;
        }

        if ((p_ent->attr & 0x10) == 0) {
            return 2;
        }
        if (PFSTR_StrLen(&token) == 0) {
            return 2;
        }
        p_iter->ffd.current_start_cluster = p_ent->start_cluster;
        PFFAT_ResetFFD(&p_iter->ffd, &p_iter->ffd.current_start_cluster);
        err = InitializeIterator(p_iter, 0);
        if (err != 0) {
            return err;
        }
        start_cluster = *p_iter->ffd.p_start_cluster;
        err = PFENT_ITER_DoFindEntry(p_iter, p_ent, &token, 0x7F, 0, &is_found);
        if (err != 0) {
            return err;
        }
        if (!is_found) {
            err = PFPATH_GetNextTokenOfPath(&token, wildcard);
            if (err != 0) {
                return err;
            }
            return (token.p_head == PF_NULL) + 2;
        }
        if (!wildcard) {
            if ((p_ent->attr & 0x10) != 0 && p_ent->start_cluster == 1) {
                p_ent->path_len = 3;
                continue;
            }
            if ((p_ent->attr & 0x10) != 0 && p_ent->short_name[0] == '.' && p_ent->short_name[1] == '.') {
                PFFAT_ResetFFD(&p_iter->ffd, &p_ent->start_cluster);
                err = InitializeIterator(p_iter, 0);
                if (err != 0) {
                    return err;
                }
                current_ent.attr = p_ent->attr;
                current_ent.start_cluster = p_ent->start_cluster;
                err = PFENT_ITER_FindDirEntryFromCluster(p_iter, &current_ent, start_cluster, &is_found);
                if (err != 0) {
                    return err;
                }
                if (is_found == 0) {
                    return 2;
                }
                if (current_ent.num_entry_LFNs != 0) {
                    p_ent->path_len -= PFPATH_GetLengthFromUnicode(current_ent.long_name);
                } else {
                    p_ent->path_len -= PFPATH_GetLengthFromShortname(&current_ent.short_name[0]);
                }
                p_ent->path_len--;
                continue;
            }
            if ((p_ent->attr & 0x10) == 0 || p_ent->short_name[0] != '.') {
                p_ent->path_len = (PFSTR_StrNumChar(&token, 1) + 1) + p_ent->path_len;
                if ((PFSTR_StrNCmp(&token, (pf_s8*)"\0", 2, 0, 1) != 0)) {
                    p_ent->path_len -= PFSTR_StrNumChar(&token, 2);
                }
            }
            continue;
        }
    }

    return 0;
}

pf_s32 PFENT_ITER_IteratorInitialize(PFITER_ENT_ITER* p_iter, pf_u32 index_start_from) {
    pf_s32 err;

    p_iter->p_vol = p_iter->ffd.p_vol;
    p_iter->log2_entries_per_sector = p_iter->p_vol->bpb.log2_bytes_per_sector - 5;
    p_iter->offset_mask = (1 << p_iter->log2_entries_per_sector) - 1;
    p_iter->file_sector_index = -1;
    err = PFENT_ITER_DoMoveTo(p_iter, index_start_from, 0U);
    return err;
}

pf_bool PFENT_ITER_IsAtLogicalEnd(PFITER_ENT_ITER* p_iter) {
    pf_s32 err;
    pf_u32 save_index;
    pf_u32 save_fsindex;

    if (p_iter->sector == -1U || p_iter->buf[0] == 0 || p_iter->index >= (1000000 - 1)) {
        save_index = p_iter->index;
        save_fsindex = p_iter->file_sector_index;
        p_iter->index = (p_iter->file_sector_index + 1) << p_iter->log2_entries_per_sector;
        err = PFENT_RecalcEntryIterator(p_iter, PF_FALSE);
        if (err != 0) {
            p_iter->index = save_index;
            p_iter->file_sector_index = save_fsindex;
            return PF_TRUE;
        }
        if (p_iter->sector != -1) {
            err = PFENT_ITER_LoadEntry(p_iter);
            if (err != 0) {
                return PF_TRUE;
            }
            return PF_FALSE;
        }
        return PF_TRUE;
    }
    return PF_FALSE;
}

pf_s32 PFENT_ITER_MoveTo(PFITER_ENT_ITER* p_iter, pf_u32 index, pf_u32 may_allocate) {
    pf_s32 err;

    if (p_iter->index != index || p_iter->sector != -1U || may_allocate == PF_FALSE) {
        err = PFENT_ITER_DoMoveTo(p_iter, index, may_allocate);
        if (err != 0) {
            return err;
        }
    }
    return 0;
}

pf_s32 PFENT_ITER_Advance(PFITER_ENT_ITER* p_iter, pf_u32 may_allocate) {
    return PFENT_ITER_MoveTo(p_iter, p_iter->index + 1, may_allocate);
}

pf_s32 PFENT_ITER_FindCluster(PF_DIR_ENT* p_ent, pf_u32 cluster, pf_bool* p_is_found) {
    PFITER_FAT_HINT hint;
    pf_u32 entries_per_sector;
    pf_u32 current_cluster;
    PFITER_ENT_ITER iter;
    pf_u32 sector_index;
    pf_s32 err;
    *p_is_found = 0;
    if (p_ent->entry_sector < p_ent->p_vol->bpb.first_data_sector) return 0;
    current_cluster = (p_ent->entry_sector - p_ent->p_vol->bpb.first_data_sector) >> p_ent->p_vol->bpb.log2_sectors_per_cluster;
    sector_index = (p_ent->p_vol->bpb.sectors_per_cluster - 1) & (p_ent->entry_sector - p_ent->p_vol->bpb.first_data_sector);
    if (current_cluster == cluster) {
        *p_is_found = 1;
        return 0;
    }
    iter.ffd.p_start_cluster = &current_cluster;
    iter.ffd.p_hint = &hint;
    iter.ffd.p_vol = p_ent->p_vol;
    iter.ffd.start_cluster = 1;
    iter.ffd.cluster_link.buffer = PF_NULL;
    iter.log2_entries_per_sector = p_ent->p_vol->bpb.log2_bytes_per_sector - 5;
    iter.file_sector_index = sector_index;
    entries_per_sector = 1 << iter.log2_entries_per_sector;
    iter.offset_mask = entries_per_sector - 1;
    iter.p_vol = p_ent->p_vol;
    iter.sector = p_ent->entry_sector;
    iter.offset = p_ent->entry_offset;
    iter.index = ((pf_u32)p_ent->entry_offset >> 5) + sector_index * entries_per_sector;
    hint.chain_index = 0;
    hint.cluster = current_cluster;
    hint.previous_cluster = 1;
    if (iter.index < 2) {
        hint.chain_index = 1;
        iter.file_sector_index += p_ent->p_vol->bpb.sectors_per_cluster;
        iter.index += entries_per_sector << p_ent->p_vol->bpb.log2_sectors_per_cluster;
    }
    while (iter.index != 0) {
        err = PFENT_ITER_LoadEntry(&iter);
        if (err != 0) return err;
        if (pf_strncmp((pf_s8*)iter.buf, (pf_s8*)"..", 2) == 0) break;
        err = PFENT_ITER_Retreat(&iter, 0);
        if (err != 0) return err;
        if (current_cluster == cluster) {
            *p_is_found = 1;
            return 0;
        }
        if (current_cluster <= 2) return 0;
        if (iter.index < 1) {
            ++hint.chain_index;
            iter.file_sector_index += p_ent->p_vol->bpb.sectors_per_cluster;
            iter.index += (1 << iter.log2_entries_per_sector) << p_ent->p_vol->bpb.log2_sectors_per_cluster;
        }
    }
    current_cluster = (PF_SWAP_16(*(pf_u16*)&iter.buf[20]) << 16) | PF_SWAP_16(*(pf_u16*)&iter.buf[26]);
    hint.chain_index = 0;
    iter.file_sector_index = 0;
    hint.cluster = current_cluster;
    iter.sector = p_ent->p_vol->bpb.first_data_sector + ((current_cluster - 2) << p_ent->p_vol->bpb.log2_sectors_per_cluster);
    iter.offset = 32;
    iter.index = 1;
    while (current_cluster > 2) {
        err = PFENT_ITER_LoadEntry(&iter);
        if (err != 0) return err;
        if (pf_strncmp((pf_s8*)iter.buf, (pf_s8*)"..", 2) == 0) {
            if (current_cluster == cluster) {
                *p_is_found = 1;
                return 0;
            }
            current_cluster = (PF_SWAP_16(*(pf_u16*)&iter.buf[20]) << 16) | PF_SWAP_16(*(pf_u16*)&iter.buf[26]);
            hint.cluster = current_cluster;
            iter.sector = p_ent->p_vol->bpb.first_data_sector + ((current_cluster - 2) << p_ent->p_vol->bpb.log2_sectors_per_cluster);
        } else return 0;
    }
    return 0;
}

pf_s32 PFENT_ITER_Retreat(PFITER_ENT_ITER* p_iter, pf_u32 may_allocate) {
    pf_u32 before_cluster;
    pf_u32 cur_cluster;
    pf_s32 err;

    if (p_iter->index == 0) {
        return 0;
    }
    if (p_iter->file_sector_index != ((p_iter->index - 1) >> p_iter->log2_entries_per_sector)) {
        cur_cluster = ((p_iter->sector - p_iter->p_vol->bpb.first_data_sector) >> p_iter->p_vol->bpb.log2_sectors_per_cluster) + 2;
        if ((p_iter->file_sector_index % p_iter->p_vol->bpb.sectors_per_cluster) == 0 || p_iter->p_vol->bpb.sectors_per_cluster == 1) {
            if (p_iter->p_vol->bpb.fat_type == FAT_32 ||
                (*p_iter->ffd.p_start_cluster > 1 && p_iter->p_vol->bpb.first_data_sector <= p_iter->sector)) {
                err = PFFAT_getBeforeChain(p_iter->p_vol, cur_cluster, cur_cluster, &before_cluster);
                if (err != 0) {
                    return err;
                }
                if (before_cluster == -1) {
                    return 14;
                }
            } else {
                before_cluster = *p_iter->ffd.p_start_cluster;
            }
        } else {
            before_cluster = cur_cluster;
        }
        p_iter->index--;
        p_iter->file_sector_index--;
        if (p_iter->p_vol->bpb.fat_type == FAT_32 || *p_iter->ffd.p_start_cluster > 1 && p_iter->p_vol->bpb.first_data_sector <= p_iter->sector) {
            p_iter->sector = (p_iter->p_vol->bpb.first_data_sector + ((before_cluster - 2) << p_iter->p_vol->bpb.log2_sectors_per_cluster)) +
                             (p_iter->file_sector_index & (p_iter->p_vol->bpb.sectors_per_cluster - 1));
        } else {
            p_iter->sector--;
        }
        p_iter->offset = (p_iter->index & p_iter->offset_mask) * 0x20;
        return 0;
    }
    return PFENT_ITER_MoveTo(p_iter, p_iter->index - 1, may_allocate);
}

pf_s32 PFENT_ITER_FindDirEntryFromCluster(PFITER_ENT_ITER* p_iter, PF_DIR_ENT* p_ent, pf_u32 cluster, pf_bool* p_is_found) {
    pf_u8 attr;
    pf_s32 err = 0;

    *p_is_found = PF_FALSE;
    p_ent->num_entry_LFNs = 0;
    p_ent->ordinal = 0;
    p_ent->check_sum = 0;
    if ((p_ent->attr & 0x10) && p_ent->start_cluster == 1) return 2;
    for (; PFENT_ITER_IsAtLogicalEnd(p_iter) == PF_FALSE; err = AdvanceIterator(p_iter, PF_FALSE)) {
        if (err != 0) {
            return err;
        }
        if (p_iter->buf[0] == 0xE5) {
            p_ent->num_entry_LFNs = 0;
            p_ent->long_name[0] = 0;
            continue;
        }
        attr = p_iter->buf[0xB];
        if ((attr & (0x01 | 0x02 | 0x04 | 0x08)) == (0x01 | 0x02 | 0x04 | 0x08)) {
            err = PFENT_LoadLFNEntryFieldsFromBuf(p_ent, p_iter->buf);
            if (err != 0) {
                p_ent->num_entry_LFNs = 0;
                p_ent->long_name[0] = 0;
            }
            continue;
        }
        if ((attr & 0x08) != 0) {
            p_ent->num_entry_LFNs = 0;
            p_ent->long_name[0] = 0;
            continue;
        }
        if ((attr & 0x10) == 0) {
            p_ent->num_entry_LFNs = 0;
            p_ent->long_name[0] = 0;
            continue;
        }
        PFENT_LoadShortNameFromBuf(p_ent, p_iter->buf);
        if (p_ent->num_entry_LFNs != 0 && p_ent->ordinal == 1 && p_ent->check_sum == PFENT_CalcCheckSum(p_ent)) {
            PFENT_loadEntryNumericFieldsFromBuf(p_ent, p_iter->buf);
            p_ent->entry_sector = p_iter->sector;
            p_ent->entry_offset = p_iter->offset;
            p_ent->p_vol = p_iter->ffd.p_vol;
            if ((p_ent->attr & 0x10) != 0 && p_ent->start_cluster != cluster) {
                p_ent->num_entry_LFNs = 0;
                p_ent->long_name[0] = 0;
                continue;
            }
            if ((p_ent->attr & 0x10) != 0 && p_ent->start_cluster == 0) {
                p_ent->start_cluster = 1;
            }
            *p_is_found = 1;
        }
        if ((p_iter->buf[0xC] & (0x10 | 0x08)) != 0) {
            PFENT_ITER_MakeLongFileName(p_iter, p_ent);
        }
        PFENT_loadEntryNumericFieldsFromBuf(p_ent, p_iter->buf);
        p_ent->entry_sector = p_iter->sector;
        p_ent->entry_offset = p_iter->offset;
        p_ent->p_vol = p_iter->ffd.p_vol;

        if ((p_ent->attr & 0x10) && p_ent->start_cluster != cluster) {
            p_ent->num_entry_LFNs = 0;
            p_ent->long_name[0] = 0;
            *p_is_found = 0;
            continue;
        }
        if ((p_ent->attr & 0x10) && p_ent->start_cluster == 0) p_ent->start_cluster = 1;
        *p_is_found = 1;
        return 0;
    }

    return 0;
}

pf_s32 PFENT_ITER_FindEntry(PFITER_ENT_ITER* p_iter, PF_DIR_ENT* p_ent, PF_STR* p_pattern,
    pf_u32 attr_required, pf_u32 attr_forbidden, pf_bool* p_is_found) {
    pf_s32 err;
    *p_is_found = 0;
    if (attr_required & attr_forbidden) return 10;
    if (PFSTR_StrNCmp(p_pattern, (pf_s8*)":", 1, 1, 1) == 0) PFSTR_MoveStrPos(p_pattern, 2);
    if (PFSTR_StrNCmp(p_pattern, (pf_s8*)"\\", 1, 0, 1) == 0 || PFSTR_StrNCmp(p_pattern, (pf_s8*)"/", 1, 0, 1) == 0) {
        err = PFENT_GetRootDir(p_iter->p_vol, p_ent);
        if (err != 0) return err;
        if (PFSTR_StrNumChar(p_pattern, 1) == 1 && PFSTR_StrNCmp(p_pattern, (pf_s8*)"\0", 2, 0, 1) == 0) return 0;
    } else {
        err = PFVOL_GetCurrentDir(p_iter->p_vol, p_ent);
        if (err != 0) return err;
    }
    err = PFENT_ITER_DoFindEntry(p_iter, p_ent, p_pattern, attr_required, attr_forbidden, p_is_found);
    if (err != 0) return err;
    return 0;
}

pf_s32 PFENT_ITER_FindEntryNoPathCheck(PFITER_ENT_ITER* p_iter, PF_DIR_ENT* p_ent, PF_STR* p_pattern,
    pf_u32 attr_required, pf_u32 attr_forbidden, pf_bool* p_is_found) {
    pf_s32 err;
    *p_is_found = 0;
    if (attr_required & attr_forbidden) return 10;
    err = PFENT_ITER_DoFindEntry(p_iter, p_ent, p_pattern, attr_required, attr_forbidden, p_is_found);
    if (err != 0) return err;
    return 0;
}

pf_s32 PFENT_ITER_GetEntryOfPath(PFITER_ENT_ITER* p_iter, PF_DIR_ENT* p_ent, PF_VOLUME* p_vol, PF_STR* p_path, pf_u32 no_look_last_token) {
    return PFENT_ITER_DoGetEntry(p_iter, p_ent, p_vol, p_path, 0, no_look_last_token);
}

pf_s32 PFENT_ITER_GetEntryOfPattern(PFITER_ENT_ITER* p_iter, PF_DIR_ENT* p_ent, PF_VOLUME* p_vol, PF_STR* p_path) {
    return PFENT_ITER_DoGetEntry(p_iter, p_ent, p_vol, p_path, 1, 1);
}

pf_s32 PFENT_ITER_GetEntryOfIter(PFITER_ENT_ITER* p_iter, PF_DIR_ENT* p_ent) {
    PFENT_LoadShortNameFromBuf(p_ent, p_iter->buf);
    PFENT_loadEntryNumericFieldsFromBuf(p_ent, p_iter->buf);
    p_ent->entry_sector = p_iter->sector;
    p_ent->entry_offset = p_iter->offset;
    p_ent->p_vol = p_iter->p_vol;
    return 0;
}

pf_s32 PFENT_ITER_GetLFNEntryName(PFITER_ENT_ITER* p_iter, PF_DIR_ENT* p_ent) {
    pf_u32 i;
    pf_s32 err;
    if (p_ent->num_entry_LFNs != 0 && !(p_ent->small_letter_flag & 0x18)) {
        for (i = 0; i < p_ent->num_entry_LFNs; ++i) {
            pf_u16* destination;
            err = PFENT_ITER_Retreat(p_iter, 0);
            if (err != 0) return err;
            err = PFENT_ITER_LoadEntry(p_iter);
            if (err != 0) return err;
            destination = &p_ent->long_name[(i * 26U) / 2U];
            pf_memcpy(destination, &p_iter->buf[1], 10);
            pf_memcpy(destination + 5, &p_iter->buf[14], 12);
            pf_memcpy(destination + 11, &p_iter->buf[28], 4);
        }
        p_ent->long_name[(p_ent->num_entry_LFNs * 26U) / 2U] = 0;
    }
    return 0;
}
