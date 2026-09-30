#include <private/vf/PrFILE2/fatfs/pf_entry.h>

typedef struct PFENTRY_FAT_HINT {
    pf_u32 chain_index;
    pf_u32 cluster;
    pf_u32 previous_cluster;
} PFENTRY_FAT_HINT;

typedef struct PFENTRY_FFD {
    pf_u32 start_cluster;
    pf_u32 current_start_cluster;
    pf_u32* p_start_cluster;
    PF_LAST_CLUSTER last_cluster;
    PF_FAT_LAST_ACCESS last_access_cluster;
    PF_CLUSTER_LINK cluster_link;
    PFENTRY_FAT_HINT* p_hint;
    PF_VOLUME* p_vol;
} PFENTRY_FFD;

typedef struct PFENTRY_ENT_ITER {
    pf_u32 index;
    PF_VOLUME* p_vol;
    PFENTRY_FFD ffd;
    pf_u32 file_sector_index;
    pf_u32 sector;
    pf_u16 offset;
    pf_u16 offset_mask;
    pf_u8 buf[32];
    pf_u8 log2_entries_per_sector;
} PFENTRY_ENT_ITER;

typedef struct PFENTRY_BPB {
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
} PFENTRY_BPB;

struct PF_VOLUME {
    PFENTRY_BPB bpb;
    pf_u32 num_free_clusters;
    pf_u32 last_free_cluster;
    pf_u8 file_and_directory_state[0x1f74 - 0x40];
    struct {
        pf_u32 tracker_size;
        pf_u32 tracker_max;
        pf_u32* tracker_bits;
    } tail_entry;
};

typedef struct PFENTRY_CONTEXT_VOLUME {
    pf_u32 stat;
    pf_s32 context_id;
    PF_VOLUME* p_vol;
} PFENTRY_CONTEXT_VOLUME;

typedef struct PFENTRY_VOLUME_SET {
    pf_u32 flags;
    pf_u32 reserved;
    PF_VOLUME* current_volume;
    PFENTRY_CONTEXT_VOLUME context_volumes[3];
    pf_s32 num_attached;
    pf_s32 num_mounted;
    pf_u32 config;
    void* user_data;
    pf_s32 last_error;
    pf_s32 last_driver_error;
    void (*code_callbacks[6])(void);
    pf_u32 setting;
} PFENTRY_VOLUME_SET;

typedef struct PFENTRY_SYS_DATE { pf_u32 sys_year, sys_month, sys_day; } PFENTRY_SYS_DATE;
typedef struct PFENTRY_SYS_TIME { pf_u32 sys_hour, sys_min, sys_sec, sys_ms; } PFENTRY_SYS_TIME;

extern PFENTRY_VOLUME_SET pf_vol_set;
void* pf_memcpy(void* dst, void* src, pf_u32 length);
void* pf_memset(void* dst, pf_s32 c, pf_u32 length);
void PF_LE16_TO_U16_STR(pf_u8* sSrc, pf_u32 num);
pf_s32 PFPATH_cmpNameUni(const pf_u16* p_name, PF_STR* sPattern);
pf_s32 PFPATH_cmpName(const pf_s8* sShort, PF_STR* p_pattern, pf_bool is_short_search);
pf_s32 PFPATH_cmpTailSFN(const pf_s8* sfn_name, const pf_s8* pattern);
pf_s32 PFPATH_putShortName(pf_u8* pDirEntry, const pf_s8* short_name, pf_u8 attr);
pf_s32 PFPATH_getShortName(pf_s8* short_name, const pf_u8* pDirEntry, pf_u8 attr);
void PFPATH_getLongNameformShortName(pf_s8* short_name, pf_s8* long_name, pf_u8 flag);
pf_s32 PFPATH_transformInUnicode(pf_u16* sDestStr, const pf_s8* sSrcStr);
pf_s32 PFPATH_parseShortNameNumeric(pf_s8* p_char, pf_u32 count);
pf_u32 PFPATH_CheckExtShortNameSignature(PF_STR* p_str);
pf_bool PFPATH_GetExtShortNameIndex(PF_STR* p_str, pf_u32* p_index);
pf_s32 PFSEC_WriteData(PF_VOLUME* p_vol, const pf_u8* p_buf, pf_u32 sector, pf_u16 offset, pf_u32 size, pf_u32* p_success_size, pf_bool set_sig);
pf_s32 PFCACHE_AllocateDataPage(PF_VOLUME*, pf_u32, PF_CACHE_PAGE**, pf_bool*);
void PFCACHE_FreeDataPage(PF_VOLUME*, PF_CACHE_PAGE*);
pf_s32 PFCACHE_FlushDataCacheSpecific(PF_VOLUME*, void*);
pf_s32 PFFAT_InitFFD(PFENTRY_FFD*, PFENTRY_FAT_HINT*, PF_VOLUME*, pf_u32*);
pf_s32 PFFAT_GetSectorSpecified(PFENTRY_FFD*, pf_u32, pf_u32, pf_u32*);
pf_s32 PFFAT_MakeRootDir(PF_VOLUME*);
pf_s32 PFENT_ITER_IteratorInitialize(PFENTRY_ENT_ITER*, pf_u32);
pf_s32 PFENT_ITER_Advance(PFENTRY_ENT_ITER*, pf_u32);
pf_s32 PFENT_ITER_Retreat(PFENTRY_ENT_ITER*, pf_u32);
pf_bool PFENT_ITER_IsAtLogicalEnd(PFENTRY_ENT_ITER*);
void PFDRV_LoadVolumeLabelFromBuf(PF_VOLUME*, const pf_u8*);
void PFSYS_TimeStamp(PFENTRY_SYS_DATE*, PFENTRY_SYS_TIME*);
void PFENT_LoadShortNameFromBuf(PF_DIR_ENT*, const pf_u8*);
pf_u8 PFENT_CalcCheckSum(PF_DIR_ENT*);
void PFENT_loadEntryNumericFieldsFromBuf(PF_DIR_ENT*, const pf_u8*);
pf_s32 PFENT_LoadLFNEntryFieldsFromBuf(PF_DIR_ENT*, const pf_u8*);

static void PFENT_storeShortNameToBuf(pf_u8* buf, const PF_DIR_ENT* p_ent) {
    PFPATH_putShortName(buf, p_ent->short_name, p_ent->attr);

    if (*buf == 0xE5) {
        *buf = 5;
    }
}
pf_s32 PFENT_compareEntry(PF_DIR_ENT* p_ent, const pf_u8* buf, PF_STR* p_pattern, pf_s32 attr,
    pf_u32 attr_required, pf_u32 attr_forbidden, pf_u32* p_lpos) {
    pf_s32 is_match = 1;
    pf_u32 is_valid = 1;
    if ((attr & 15) == 15) {
        is_match = 1;
    } else {
        if (attr == 0) attr = 0x40;
        if (attr_required & 0x80) {
            attr_required &= 0x7f;
            attr_forbidden &= 0x7f;
            if ((attr_required && (pf_s32)(attr_required & attr) != (pf_s32)attr_required) ||
                (attr_forbidden && (pf_s32)(attr_forbidden & attr) == (pf_s32)attr_forbidden)) is_valid = 0;
        } else if (attr_required != 0x7f && (pf_u32)attr != attr_required &&
            (!(attr & attr_required) || (attr & attr_forbidden))) is_valid = 0;
        if (is_valid == 0) {
            is_match = 1;
        } else {
            if (attr & 8) {
                p_ent->num_entry_LFNs = 0;
                p_ent->long_name[0] = 0;
            }
            PFENT_LoadShortNameFromBuf(p_ent, buf);
            if (p_ent->num_entry_LFNs && p_ent->ordinal == 1 && p_ent->check_sum == PFENT_CalcCheckSum(p_ent)) {
                is_match = PFPATH_cmpNameUni(p_ent->long_name, p_pattern) != 0;
            }
            if (is_match == 1) {
                if ((pf_vol_set.setting & 2) == 2 && !(attr & 8)) {
                    if (PFPATH_cmpName(p_ent->short_name, p_pattern, 0) == 0) is_match = 0;
                } else {
                    if (PFPATH_cmpName(p_ent->short_name, p_pattern, 1) == 0) is_match = 0;
                }
            }
            if (is_match == 1) ++*p_lpos;
        }
    }
    return is_match;
}

pf_s32 PFENT_getEntry(PF_DIR_ENT* p_ent, PFENTRY_ENT_ITER* p_iter, PF_STR* p_pattern,
    pf_u32 attr_required, pf_u32 attr_forbidden, pf_u32* p_lpos) {
    pf_s32 err;
    pf_u8 attr = p_iter->buf[11];
    if (PFENT_compareEntry(p_ent, p_iter->buf, p_pattern, attr, attr_required, attr_forbidden, p_lpos) == 1) {
        if ((attr & 15) == 15) {
            err = PFENT_LoadLFNEntryFieldsFromBuf(p_ent, p_iter->buf);
            if (err != 0) {
                p_ent->num_entry_LFNs = 0;
                p_ent->long_name[0] = 0;
            }
        } else {
            p_ent->num_entry_LFNs = 0;
            p_ent->long_name[0] = 0;
        }
        return -1;
    }
    if (p_ent->num_entry_LFNs == 0 && (p_iter->buf[12] & 0x18)) {
        pf_s8 filename[13];
        pf_s32 length;
        PFPATH_getLongNameformShortName(p_ent->short_name, filename, p_iter->buf[12]);
        length = PFPATH_transformInUnicode(p_ent->long_name, filename);
        p_ent->num_entry_LFNs = length / 13 + ((length % 13) != 0);
        p_ent->check_sum = PFENT_CalcCheckSum(p_ent);
        p_ent->ordinal = 1;
    }
    PFENT_loadEntryNumericFieldsFromBuf(p_ent, p_iter->buf);
    p_ent->entry_sector = p_iter->sector;
    p_ent->entry_offset = p_iter->offset;
    if ((p_ent->attr & 0x10) && p_ent->start_cluster == 0) p_ent->start_cluster = 1;
    return 0;
}
pf_s32 PFENT_searchEmptyTailSFN(PFENTRY_FFD* p_ffd, pf_u32 tail_index, const pf_s8* pattern, pf_u32* p_tail_bit) {
    PFENTRY_ENT_ITER iter;
    pf_u8 attr;
    pf_s32 err = 0;
    pf_u32 bit_pos;
    pf_u32 sfn_taillen;
    pf_u32 sfn_baselen;
    pf_u32 i;
    pf_s8 sfnbuf[13];
    pf_s8 patbuf[13];
    PF_VOLUME* p_vol = p_ffd->p_vol;

    pf_memset(p_tail_bit, 0, p_vol->tail_entry.tracker_size * 4);
    iter.ffd = *p_ffd;

    for (err = PFENT_ITER_IteratorInitialize(&iter, 0); PFENT_ITER_IsAtLogicalEnd(&iter) == PF_FALSE;
         err = PFENT_ITER_Advance(&iter, PF_FALSE)) {
        if (err != 0) {
            return err;
        }
        if (*iter.buf == 0) {
            break;
        }
        if (*iter.buf != 0xE5) {
            attr = iter.buf[11];
            if (((attr & (0x01 | 0x02 | 0x04 | 0x08)) != (0x01 | 0x02 | 0x04 | 0x08)) && ((attr & 8) == 0)) {
                PFPATH_getShortName((pf_s8*)&sfnbuf, (pf_u8*)&iter.buf, 0);
                for (sfn_taillen = 1; (sfnbuf[sfn_taillen] != 0x7E) && (sfnbuf[sfn_taillen] != 0) && (sfn_taillen < 7U); sfn_taillen++) {
                }

                if (sfn_taillen < 7 && sfnbuf[sfn_taillen] == 0x7E) {
                    for (sfn_baselen = sfn_taillen + 1; sfnbuf[sfn_baselen] >= 0x30 && sfnbuf[sfn_baselen] <= 0x39; sfn_baselen++) {
                    }

                    if (sfnbuf[sfn_baselen] == '.' || sfnbuf[sfn_baselen] == 0) {
                        i = (sfn_baselen - sfn_taillen) - 1;
                        bit_pos = 0;
                        for (; i != 0; i--) {
                            bit_pos *= 10;
                            bit_pos += (sfnbuf[sfn_baselen - i]) - 0x30;
                        }

                        pf_strcpy((pf_s8*)&patbuf, pattern);
                        PFPATH_parseShortNameNumeric((pf_s8*)&patbuf, bit_pos);
                        if (PFPATH_cmpTailSFN((pf_s8*)&sfnbuf, (pf_s8*)&patbuf) == 0 && bit_pos >= tail_index &&
                            bit_pos < (tail_index + (p_vol->tail_entry.tracker_size << 5))) {
                            bit_pos -= tail_index;
                            p_tail_bit[bit_pos >> 5] |= 1 << bit_pos;
                        }
                    }
                }
            }
        }
    }

    return 0;
}

pf_s32 PFENT_findEmptyTailSFN(PF_DIR_ENT* p_ent_containig_dir, const pf_s8* name, pf_u32* p_tails) {
    PFENTRY_FFD ffd;
    PFENTRY_FAT_HINT hint;
    pf_s32 err;
    pf_u32 num;
    PF_VOLUME* p_vol = p_ent_containig_dir->p_vol;
    pf_u32 track_num;

    *p_tails = 1;
    PFFAT_InitFFD(&ffd, &hint, p_ent_containig_dir->p_vol, &p_ent_containig_dir->start_cluster);

    for (num = 1; num <= (1000000 - 1); num += p_vol->tail_entry.tracker_size << 5) {
        err = PFENT_searchEmptyTailSFN(&ffd, num, name, p_vol->tail_entry.tracker_bits);
        if (err != 0) {
            return err;
        }

        for (track_num = 0; track_num < p_vol->tail_entry.tracker_size; track_num += 1) {
            if (p_vol->tail_entry.tracker_bits[track_num] != -1) {
                for (; (p_vol->tail_entry.tracker_bits[track_num] & 1) != 0; p_vol->tail_entry.tracker_bits[track_num] >>= 1, (*p_tails)++) {
                }
                num = 1000000;
                break;
            } else {
                *p_tails += 0x20;
            }
        }
    }
    return 0;
}

pf_u8 PFENT_CalcCheckSum(PF_DIR_ENT* p_ent) {
    pf_u16 i;
    pf_u8 sum;
    pf_u8 buf[13];

    PFPATH_putShortName((pf_u8*)buf, p_ent->short_name, 0);

    sum = 0;
    for (i = 0; i < 11; i++) {
        sum = ((sum & 1) != 0 ? 0x80 : 0) + (sum >> 1) + buf[i];
    }
    return sum;
}

void PFENT_LoadShortNameFromBuf(PF_DIR_ENT* p_ent, const pf_u8* buf) {
    PFPATH_getShortName(p_ent->short_name, buf, buf[11]);
    if (p_ent->short_name[0] == 5) {
        p_ent->short_name[0] = -0x1B;
    }
}

void PFENT_loadEntryNumericFieldsFromBuf(PF_DIR_ENT* p_ent, const pf_u8* buf) {
    p_ent->attr = buf[0xB];
    p_ent->small_letter_flag = buf[0xC];
    p_ent->create_time_ms = buf[0xD];
    p_ent->create_time = PF_SWAP_16(*(pf_u16*)&buf[0xE]);
    p_ent->create_date = PF_SWAP_16(*(pf_u16*)&buf[0x10]);
    p_ent->access_date = PF_SWAP_16(*(pf_u16*)&buf[0x12]);
    p_ent->modify_time = PF_SWAP_16(*(pf_u16*)&buf[0x16]);
    p_ent->modify_date = PF_SWAP_16(*(pf_u16*)&buf[0x18]);
    p_ent->file_size = PF_SWAP_32(*(pf_u32*)&buf[0x1C]);
    p_ent->start_cluster = ((pf_u16)PF_SWAP_16(*(pf_u16*)&buf[0x14]) << 16) | (pf_u16)(PF_SWAP_16(*(pf_u16*)&buf[0x1A]));
}

void PFENT_StoreEntryNumericFieldsToBuf(pf_u8* buf, const PF_DIR_ENT* p_ent) {
    buf[0x0B] = p_ent->attr;
    buf[0x0C] = p_ent->small_letter_flag;
    buf[0x0D] = p_ent->create_time_ms;
    *(pf_u16*)&buf[0x0E] = PF_SWAP_16(p_ent->create_time);
    *(pf_u16*)&buf[0x10] = PF_SWAP_16(p_ent->create_date);
    *(pf_u16*)&buf[0x12] = PF_SWAP_16(p_ent->access_date);
    *(pf_u16*)&buf[0x16] = PF_SWAP_16(p_ent->modify_time);
    *(pf_u16*)&buf[0x18] = PF_SWAP_16(p_ent->modify_date);
    *(pf_u16*)&buf[0x14] = PF_SWAP_16((pf_u16)(p_ent->start_cluster >> 16));
    *(pf_u16*)&buf[0x1A] = PF_SWAP_16((pf_u16)(p_ent->start_cluster));
    *(pf_u32*)&buf[0x1C] = PF_SWAP_32(p_ent->file_size);
}

pf_s32 PFENT_LoadLFNEntryFieldsFromBuf(PF_DIR_ENT* p_ent, const pf_u8* buf) {
    pf_u8 ordinal;
    pf_u8 check_sum;
    pf_u32 is_last_LFN_ent;
    pf_u8* p;
    pf_u16* q;
    pf_u16* q_after;

    ordinal = buf[0];
    check_sum = buf[13];
    if ((ordinal & ~0x40U) > 0x14U) {
        p_ent->ordinal = 0;
        p_ent->check_sum = 0;
        p_ent->num_entry_LFNs = 0;
        return 33;
    }
    if ((buf[0] & 0x40) != 0) {
        ordinal &= ~0x40;
        p_ent->num_entry_LFNs = 0;
        is_last_LFN_ent = 1;
    } else {
        is_last_LFN_ent = 0;
        if (p_ent->num_entry_LFNs == 0) return 33;
        if (ordinal != p_ent->ordinal - 1 || check_sum != p_ent->check_sum) {
            p_ent->ordinal = 0;
            p_ent->check_sum = 0;
            p_ent->num_entry_LFNs = 0;
            return 33;
        }
    }
    p_ent->ordinal = ordinal;
    p_ent->check_sum = check_sum;
    p = (pf_u8*)p_ent->long_name;
    p += (ordinal - 1) * 0x1A;
    pf_memcpy(&p[0x0], (pf_s8*)&buf[0x1], 10);
    pf_memcpy(&p[10], (pf_s8*)&buf[0xE], 0xC);
    pf_memcpy(&p[0x16], (pf_s8*)&buf[0x1C], 4U);
    PF_LE16_TO_U16_STR(&p[0x0], 10);
    PF_LE16_TO_U16_STR(&p[10], 0xC);
    PF_LE16_TO_U16_STR(&p[0x16], 4U);
    if (is_last_LFN_ent != 0) {
        ((pf_u16*)p)[13] = 0;
        q = (pf_u16*)p;
        q_after = (pf_u16*)&p[0x1A];
        for (; q < q_after; q++) {
            if (*q == 0) {
                q++;
                break;
            }
        }

        for (; q < q_after; q++) {
            if (*q != 0xFFFF) {
                p_ent->num_entry_LFNs = 0;
                return 33;
            }
        }
    }
    p_ent->num_entry_LFNs++;
    return 0;
}

void PFENT_storeLFNEntryFieldsToBuf(pf_u8* buf, PF_DIR_ENT* p_ent, pf_u8 ord, pf_u8 sum, pf_bool is_last) {
    pf_u8* p_seg;
    pf_u16* p;
    pf_u16* p_after;

    if (is_last) {
        *buf = ord | 0x40;
    } else {
        *buf = ord;
    }
    buf[0xB] = (0x01 | 0x02 | 0x04 | 0x08);
    buf[0xD] = sum;
    buf[0xC] = 0;
    *(pf_u16*)&buf[0x1A] = 0;
    p_seg = (pf_u8*)p_ent->long_name;
    p_seg += (ord - 1) * 0x1A;
    if (is_last != 0) {
        p = (pf_u16*)p_seg;
        p_after = (pf_u16*)&p_seg[0x1A];
        for (; p < p_after; p++) {
            if (*p == 0x0000) {
                p++;
                break;
            }
        }

        for (; p < p_after; p++) {
            *p = 0xFFFF;
        }
    }
    pf_memcpy(&buf[1], p_seg, 10);
    pf_memcpy(&buf[0xE], &p_seg[10], 0xC);
    pf_memcpy(&buf[0x1C], &p_seg[0x16], 4);
    PF_LE16_TO_U16_STR(&buf[1], 10);
    PF_LE16_TO_U16_STR(&buf[0xE], 0xC);
    PF_LE16_TO_U16_STR(&buf[0x1C], 4);
}

pf_s32 PFENT_findEntryPos(PFENTRY_FFD* p_ffd, PF_DIR_ENT* p_ent, pf_u32 index_search_from, PF_STR* p_pattern,
    pf_u32 attr_required, pf_u32 attr_forbidden, pf_u32* p_lpos, pf_u32* p_ppos) {
    pf_s32 err;
    PFENTRY_ENT_ITER iter;
    pf_u32 lpos;
    pf_bool is_extsfn = 0;
    *p_lpos = 0;
    *p_ppos = 0;
    p_ent->num_entry_LFNs = 0;
    p_ent->ordinal = 0;
    p_ent->check_sum = 0;
    p_ent->long_name[0] = 0;
    lpos = 0;
    if ((pf_vol_set.setting & 2) == 2) is_extsfn = PFPATH_GetExtShortNameIndex(p_pattern, &index_search_from);
    iter.ffd = *p_ffd;
    if (is_extsfn == 1) {
        err = PFENT_ITER_IteratorInitialize(&iter, index_search_from - 1);
        {
            if (err != 0) {
                *p_lpos = 999999;
                *p_ppos = 999999;
                return err;
            }
            if (PFENT_getEntry(p_ent, &iter, p_pattern, attr_required, attr_forbidden, &lpos) == 0) {
                *p_lpos = 999999;
                *p_ppos = 999999;
                return 3;
            }
            if (iter.buf[0] & 0x40) {
                err = PFENT_ITER_IteratorInitialize(&iter, index_search_from);
                if (err != 0) {
                    *p_lpos = 999999;
                    *p_ppos = 999999;
                    return err;
                }
                if (PFENT_getEntry(p_ent, &iter, p_pattern, attr_required, attr_forbidden, &lpos) == 0) {
                    p_ent->p_vol = p_ffd->p_vol;
                    *p_lpos = lpos;
                    *p_ppos = iter.index;
                    return 0;
                }
            }
        }
    } else {
        for (err = PFENT_ITER_IteratorInitialize(&iter, index_search_from); !PFENT_ITER_IsAtLogicalEnd(&iter); err = PFENT_ITER_Advance(&iter, 0)) {
            if (err != 0) {
                *p_lpos = 999999;
                *p_ppos = 999999;
                return err;
            }
            if (iter.buf[0] == 0) break;
            if (iter.buf[0] == 0xe5) {
                p_ent->num_entry_LFNs = 0;
                p_ent->long_name[0] = 0;
            } else if (PFENT_getEntry(p_ent, &iter, p_pattern, attr_required, attr_forbidden, &lpos) == 0) {
                p_ent->p_vol = p_ffd->p_vol;
                *p_lpos = lpos;
                *p_ppos = iter.index;
                return 0;
            }
        }
    }
    *p_lpos = 999999;
    *p_ppos = 999999;
    return 3;
}

pf_s32 PFENT_findEntry(PFENTRY_FFD* p_ffd, PF_DIR_ENT* p_ent, pf_u32 index_search_from, PF_STR* p_pattern,
    pf_u32 attr_required, pf_u32 attr_forbidden) {
    pf_u32 lpos;
    pf_u32 ppos;
    return PFENT_findEntryPos(p_ffd, p_ent, index_search_from, p_pattern, attr_required, attr_forbidden, &lpos, &ppos);
}

pf_s32 PFENT_allocateEntryPos(PF_DIR_ENT* p_ent, pf_u32 num_entries, PFENTRY_FFD* p_ffd, pf_u32* p_prev_chain,
    PF_STR* p_filename, pf_u32* p_pos) {
    pf_s32 err;
    PFENTRY_ENT_ITER iter;
    PF_DIR_ENT current_ent;
    PF_VOLUME* p_vol;
    pf_u32 next_sector;
    pf_u32 logical_scratch;
    pf_u32 saved_sector;
    pf_u16 saved_offset;
    pf_u32 current_sector;
    pf_u32 previous_sector0;
    pf_u32 previous_sector1;
    pf_bool is_found;
    pf_u32 num_free_entries;
    pf_u32 logical_position;
    if ((pf_vol_set.setting & 2) == 2 && PFPATH_CheckExtShortNameSignature(p_filename) == 1) return 1;
    p_vol = p_ffd->p_vol;
    saved_sector = -1U;
    p_prev_chain[0] = p_prev_chain[1] = saved_sector;
    num_free_entries = 0;
    logical_position = 0;
    saved_offset = 0;
    current_sector = -1U;
    previous_sector1 = -1U;
    previous_sector0 = -1U;
    is_found = 0;
    iter.sector = 0;
    iter.index = 0;
    iter.ffd = *p_ffd;
    for (err = PFENT_ITER_IteratorInitialize(&iter, 0);; err = PFENT_ITER_Advance(&iter, 1)) {
        if (err != 0) {
            if (err == 16) break;
            return err;
        }
        if (iter.sector == -1U) break;
        if (is_found == 0 && num_free_entries == 0) {
            saved_offset = iter.offset;
            saved_sector = iter.sector;
            current_sector = iter.sector;
        }
        if (is_found == 0) {
            if (iter.buf[0] == 0 || iter.buf[0] == 0xe5) {
                if (current_sector != iter.sector) {
                    pf_bool is_first = previous_sector0 == -1U;
                    if (is_first) previous_sector0 = iter.sector;
                    if (!is_first) previous_sector1 = iter.sector;
                    current_sector = iter.sector;
                }
                ++num_free_entries;
            } else {
                num_free_entries = 0;
                previous_sector0 = -1U;
                previous_sector1 = -1U;
            }
        }
        if (num_free_entries >= num_entries) {
            if (is_found == 0) {
                logical_position = iter.index;
                is_found = 1;
            }
            if (iter.buf[0] == 0) break;
        }
        if (iter.buf[0] != 0 && iter.buf[0] != 0xe5 && PFENT_getEntry(&current_ent, &iter, p_filename, 0x7f, 0, &logical_scratch) == 0) {
            *p_ent = current_ent;
            p_ent->p_vol = p_ffd->p_vol;
            return 8;
        }
        if (iter.offset + 32 == p_vol->bpb.bytes_per_sector) {
            err = PFFAT_GetSectorSpecified(p_ffd, iter.file_sector_index + 1, 0, &next_sector);
            if (err != 0) return err;
            if (next_sector == -1U && is_found == 1) break;
        }
    }
    if (is_found == 0) return 5;
    p_prev_chain[0] = previous_sector0;
    p_prev_chain[1] = previous_sector1;
    p_ent->entry_sector = saved_sector;
    p_ent->entry_offset = saved_offset;
    *p_pos = logical_position;
    return 0;
}

pf_s32 PFENT_allocateEntry(PF_DIR_ENT* p_ent, pf_u32 num_entries, PFENTRY_FFD* p_ffd, pf_u32* p_prev_chain, PF_STR* p_filename) {
    pf_u32 position;
    return PFENT_allocateEntryPos(p_ent, num_entries, p_ffd, p_prev_chain, p_filename, &position);
}

pf_s32 PFENT_GetRootDir(PF_VOLUME* p_vol, PF_DIR_ENT* p_ent) {
    p_ent->long_name[0] = 0x5C;
    p_ent->long_name[1] = 0;
    p_ent->num_entry_LFNs = 0;
    p_ent->ordinal = 0;
    p_ent->check_sum = 0;
    p_ent->short_name[0] = 0x5C;
    p_ent->short_name[1] = 0;
    p_ent->small_letter_flag = 0;
    p_ent->attr = 0x10;
    p_ent->create_time_ms = 0;
    p_ent->create_time = 0;
    p_ent->create_date = 0;
    p_ent->access_date = 0;
    p_ent->modify_time = 0;
    p_ent->modify_date = 0;
    p_ent->file_size = 0;
    p_ent->p_vol = p_vol;
    p_ent->path_len = 3;
    p_ent->start_cluster = 1;
    p_ent->entry_sector = -1;
    p_ent->entry_offset = 0;
    return 0;
}
pf_s32 PFENT_MakeRootDir(PF_VOLUME* p_vol) {
    PF_CACHE_PAGE* p_page;
    pf_u32 sector;
    pf_u32 success_size;
    pf_bool hit;
    pf_s32 err;
    switch (p_vol->bpb.fat_type) {
    case FAT_32:
        PFFAT_MakeRootDir(p_vol);
        break;
    case FAT_12:
    case FAT_16:
        err = PFCACHE_AllocateDataPage(p_vol, -1U, &p_page, &hit);
        if (err != 0) return err;
        pf_memset(p_page->p_buf, 0, p_vol->bpb.bytes_per_sector);
        for (sector = p_vol->bpb.first_root_dir_sector; sector < p_vol->bpb.first_data_sector; ++sector) {
            err = PFSEC_WriteData(p_vol, p_page->p_buf, sector, 0, p_vol->bpb.bytes_per_sector, &success_size, 0);
            if (err != 0) {
                PFCACHE_FreeDataPage(p_vol, p_page);
                return err;
            }
            if (success_size != p_vol->bpb.bytes_per_sector) {
                PFCACHE_FreeDataPage(p_vol, p_page);
                return 17;
            }
        }
        PFCACHE_FreeDataPage(p_vol, p_page);
        break;
    default:
        return 7;
    }
    {
        static pf_u8 default_volume_label[16] = "NO NAME    ";
        PFDRV_LoadVolumeLabelFromBuf(p_vol, default_volume_label);
    }
    return 0;
}

pf_s32 PFENT_updateEntry(PF_DIR_ENT* p_ent, pf_u32 flag) {
    PF_VOLUME* p_vol;
    pf_u32 success_size;
    pf_u8 buf[32];
    pf_s32 err;

    p_vol = p_ent->p_vol;
    if (p_ent->start_cluster == 1) {
        return 0xE;
    }
    if (flag == 1) {
        p_ent->attr |= (pf_u8)0x20;
    }
    PFENT_storeShortNameToBuf(buf, p_ent);
    PFENT_StoreEntryNumericFieldsToBuf(buf, p_ent);
    err = PFSEC_WriteData(p_vol, buf, p_ent->entry_sector, p_ent->entry_offset, 32, &success_size, 0U);
    if (err != 0) {
        return err;
    }
    if (success_size != 0x20) {
        return 0x11;
    }

    return 0;
}
pf_s32 PFENT_AdjustSFN(PF_DIR_ENT* p_ent, pf_s8* p_short_name) {
    pf_u32 i = 0;
    pf_u32 tail_num;
    pf_s32 err = 0;

    for (i = 1; (p_short_name[i] != 0x7E) && (p_short_name[i] != 0) && (i < 7U); i++) {
    }
    if ((i < 7U) && (p_short_name[i] == 0x7E)) {
        for (i++; (p_short_name[i] >= 0x30) && (p_short_name[i] <= 0x39); i++) {
        }
        if ((p_short_name[i] == '.') || (p_short_name[i] == 0)) {
            err = PFENT_findEmptyTailSFN(p_ent, p_short_name, &tail_num);
            if (err != 0) {
                return err;
            }
            if (tail_num != 1) {
                PFPATH_parseShortNameNumeric(p_short_name, tail_num);
            }
        }
    }

    return 0;
}
pf_u8 PFENT_getcurrentDateTimeForEnt(pf_u16* p_date, pf_u16* p_time) {
    PFENTRY_SYS_DATE sys_date;
    PFENTRY_SYS_TIME sys_time;

    PFSYS_TimeStamp(&sys_date, &sys_time);
    *p_date = ((sys_date.sys_day & 0x1F) | ((sys_date.sys_month << 5) & 0x1E0)) | (((sys_date.sys_year - 0x7BC) << 9) & 0xFE00);
    *p_time = (((sys_time.sys_sec >> 1) & 0x1F) | ((sys_time.sys_min << 5) & 0x7E0)) | ((sys_time.sys_hour << 0xB) & 0xF800);

    return sys_time.sys_ms;
}
pf_s32 PFENT_RemoveEntry(PF_DIR_ENT* p_ent, PFENTRY_ENT_ITER* p_iter) {
    pf_u32 success_size;
    pf_s32 err = 0;
    pf_u32 entry_sector;
    pf_u16 entry_offset;
    pf_u32 i;
    PF_VOLUME* p_vol = PF_NULL;
    pf_u8 dir_fb_free[8] = {0xE5};
    pf_u8 del = dir_fb_free[0];

    p_vol = p_ent->p_vol;
    entry_sector = p_ent->entry_sector;
    entry_offset = p_ent->entry_offset;
    if ((p_ent->num_entry_LFNs != 0) && ((p_ent->small_letter_flag & 0x18) == 0)) {
        for (i = 1; i <= p_ent->num_entry_LFNs; i++) {
            err = PFENT_ITER_Retreat(p_iter, 0);
            if (err != 0) {
                return err;
            }
            entry_sector = p_iter->sector;
            entry_offset = p_iter->offset;
            err = PFSEC_WriteData(p_vol, &del, entry_sector, entry_offset, 1, &success_size, 0);
            if (err != 0) {
                return err;
            }
            if (success_size != 1) {
                return 17;
            }
        }
    }
    err = PFSEC_WriteData(p_vol, &del, p_ent->entry_sector, p_ent->entry_offset, 1, &success_size, 0);
    if (err != 0) {
        return err;
    }
    if (success_size != 1) {
        return 17;
    }
    err = PFCACHE_FlushDataCacheSpecific(p_vol, PF_NULL);
    if (err != 0) {
        return err;
    }
    return 0;
}
