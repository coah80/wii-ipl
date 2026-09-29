#include <revolution/types.h>
#include <private/fa/fa_local.h>

#define PF_DRIVE_COUNT 26
#define PF_CONTEXT_COUNT 4
#define PF_DIR_HANDLE_COUNT 5

typedef struct PF_DEV_INF {
    u32 num_clusters;           // 0x00
    u32 num_free_clusters;      // 0x04
    u32 bytes_per_sector;       // 0x08
    u32 sectors_per_cluster;    // 0x0C
} PF_DEV_INF;

typedef struct PF_VOL_INF {
    s8 label[12];    // 0x00
    u8 attr;         // 0x0C
    u8 pad_D[3];
    u32 modify_date; // 0x10
    u32 modify_time; // 0x14
} PF_VOL_INF;

typedef struct PF_VOL_CFG {
    u32 flags;            // 0x00
    u32 file_config;      // 0x04
    u32 fat_buffer_size;  // 0x08
    u32 data_buffer_size; // 0x0C
} PF_VOL_CFG;

typedef struct PF_CLSTLNK_CFG {
    u32* buffer;   // 0x00
    u32 count;     // 0x04
    u16 interval;  // 0x08
    u16 pad_a;
} PF_CLSTLNK_CFG;

typedef struct PF_CACHE_CFG {
    void* fat_pages;        // 0x00
    void* data_pages;       // 0x04
    u16 num_fat_pages;      // 0x08
    u16 num_data_pages;     // 0x0A
    u32 fat_buffer_size;    // 0x0C
    u32 data_buffer_size;   // 0x10
} PF_CACHE_CFG;

typedef struct PF_DRV_TBL {
    void* p_part;              // 0x00
    PF_CACHE_CFG* p_cache_cfg; // 0x04
    s8 drv_char;               // 0x08
    u8 flags;                  // 0x09
    u8 pad_a[2];
} PF_DRV_TBL;

PF_VOLUME_SET pf_vol_set;

extern const u8 pf_vol_dummy_e5[8];

/* pf_drv.c */
s32 PFDRV_init(PF_VOLUME* p_vol);
s32 PFDRV_finalize(PF_VOLUME* p_vol);
s32 PFDRV_mount(PF_VOLUME* p_vol);
s32 PFDRV_unmount(PF_VOLUME* p_vol, u32 mode);
s32 PFDRV_format(PF_VOLUME* p_vol, const u8* param);
s32 PFDRV_IsInserted(PF_VOLUME* p_vol);
s32 PFDRV_IsDetected(PF_VOLUME* p_vol);
s32 PFDRV_IsWProtected(PF_VOLUME* p_vol);
s32 PFDRV_IsMountRequested(PF_VOLUME* p_vol);
s32 PFDRV_IsUnmountRequested(PF_VOLUME* p_vol);
s32 PFDRV_ClearMountRequested(PF_VOLUME* p_vol);
s32 PFDRV_ClearUnmountRequested(PF_VOLUME* p_vol);
s32 PFDRV_StoreVolumeLabelToBPB(PF_VOLUME* p_vol, const s8* label);
s32 PFDRV_StoreVolumeLabelToBuf(s8* buf, PF_VOLUME* p_vol);
void PFDRV_SetEncode(u32 code);

/* pf_cache.c */
s32 PFCACHE_InitCaches(PF_VOLUME* p_vol);
s32 PFCACHE_FreeAllCaches(PF_VOLUME* p_vol);
s32 PFCACHE_FlushAllCaches(PF_VOLUME* p_vol);
s32 PFCACHE_FlushFATCache(PF_VOLUME* p_vol);
s32 PFCACHE_FlushDataCache(PF_VOLUME* p_vol);
s32 PFCACHE_FlushDataCacheSpecific(PF_VOLUME* p_vol, u32 mode);
s32 PFCACHE_SetWriteThroughMode(PF_VOLUME* p_vol);
s32 PFCACHE_SetWriteBackMode(PF_VOLUME* p_vol);
void PFCACHE_SetCache(PF_VOLUME* p_vol, void* fat_pages, void* data_pages, u32 num_fat_pages,
                      u32 num_data_pages);
s32 PFCACHE_SetFATBufferSize(PF_VOLUME* p_vol, u32 size);
s32 PFCACHE_SetDataBufferSize(PF_VOLUME* p_vol, u32 size);

/* pf_fat.c */
s32 PFFAT_InitFATRegion(PF_VOLUME* p_vol);
s32 PFFAT_RefreshFSINFO(PF_VOLUME* p_vol);
s32 PFFAT_CountFreeClusters(PF_VOLUME* p_vol, u32* p_num_free);
s32 PFFAT_InitFFD(PF_FFD* p_ffd, PF_FAT_HINT* p_hint, PF_VOLUME* p_vol, u32* p_start_cluster);

/* pf_entry.c */
s32 PFENT_GetRootDir(PF_VOLUME* p_vol, PF_DIR_ENT* p_ent);
s32 PFENT_MakeRootDir(PF_VOLUME* p_vol);
s32 PFENT_findEntryPos(PF_FFD* p_ffd, PF_DIR_ENT* p_ent, u32 index_from, PF_STR* p_pattern,
                       u8 attr_required, u32 flag, u32* p_lpos, u32* p_ppos);
s32 PFENT_allocateEntry(PF_DIR_ENT* p_ent, u32 num_entries, PF_FFD* p_ffd, u32* p_prev_chain,
                        PF_STR* p_filename);
s32 PFENT_updateEntry(PF_DIR_ENT* p_ent, u32 is_set_arch);
u8 PFENT_getcurrentDateTimeForEnt(u16* p_date, u16* p_time);

/* pf_file.c / pf_dir.c */
s32 PFFILE_FinalizeAllFiles(PF_VOLUME* p_vol);
s32 PFDIR_FinalizeAllDirs(PF_VOLUME* p_vol);

/* pf_str.c */
s32 PFSTR_SetLocalStr(PF_STR* p_str, const s8* s);

/* pf_sector.c */
s32 PFSEC_WriteData(PF_VOLUME* p_vol, u8* buf, u32 sector, u32 offset, u32 count, u32* p_written,
                    u32 flag);

/* pf_sys.c */
s32 PFSYS_GetCurrentContextID(s32* p_context_id);

/* pf_clib.c */
s32 pf_memcmp(const s8* s1, const s8* s2, u32 n);
void* pf_memcpy(void* dst, const void* src, u32 n);
void* pf_memset(void* dst, s32 c, u32 n);
s8* pf_strcpy(s8* dst, const s8* src);
s32 pf_toupper(s32 c);

/* pf_lockfile.c */
void PF_InitLockFile(void);

/* charcodes */
extern PF_CHARCODE pf_charcode_sjis;
extern PF_CHARCODE pf_charcode_1252;
s32 PFCODE_CP932_OEM2Unicode(const s8* src, u16* dst);
s32 PFCODE_CP932_Unicode2OEM(const u16* src, s8* dst);
s32 PFCODE_CP932_OEMCharWidth(const s8* src);
u32 PFCODE_CP932_isOEMMBchar(s8 c, u32 mode);
s32 PFCODE_CP932_UnicodeCharWidth(const u16* src);
u32 PFCODE_CP932_isUnicodeMBchar(u16 c, u32 mode);

/* fa_nanddrv */
s32 fa_nanddrv_NotifyNANDFile(s32 arg0, u32 arg1);

s32 PFVOL_DoMountVolume(PF_VOLUME* p_vol);
s32 PFVOL_p_unmount(PF_VOLUME* p_vol, u32 mode);
s32 PFVOL_p_format(PF_VOLUME* p_vol, const u8* param);
s32 PFVOL_p_setvol(PF_VOLUME* p_vol, const s8* label);
s32 PFVOL_p_getvol(PF_VOLUME* p_vol, PF_VOL_INF* p_vinf);
s32 PFVOL_p_rmvvol(PF_VOLUME* p_vol);

static u32 PFVOL_CheckContextRegistered(s32 context_id);
static u32 PFVOL_CheckContextRegistered(s32 context_id) {
    u32 is_registered;
    PF_CONTEXT* p_ctx = pf_vol_set.context;
    if ((p_ctx[0].stat &= 1) != 0 && p_ctx[0].context_id == context_id) {
        is_registered = 1;
    } else if ((p_ctx[1].stat &= 1) != 0 && p_ctx[1].context_id == context_id) {
        is_registered = 1;
    } else if ((p_ctx[2].stat &= 1) != 0 && p_ctx[2].context_id == context_id) {
        is_registered = 1;
    } else {
        is_registered = 0;
    }
    return is_registered;
}

s32 PFVOL_DoMountVolume(PF_VOLUME* p_vol) {
    s32 err;
    s32 context_id;
    s32 cache_sectors;
    s32 i;
    PF_DIR_ENT* p_dir;

    p_vol->last_error = 0;
    p_vol->last_driver_error = 0;
    err = PFDRV_mount(p_vol);
    if (err != 0) {
        goto end;
    }
    if (p_vol->bpb.bytes_per_sector == 0 || (p_vol->bpb.bytes_per_sector & 0x1FF) != 0) {
        err = 0xF;
        goto end;
    }
    cache_sectors = p_vol->bpb.bytes_per_sector >> 9;
    if (cache_sectors > p_vol->cache_max_fat || cache_sectors * 2 > p_vol->cache_max_data) {
        err = 0x1E;
        goto end;
    }
    err = PFCACHE_InitCaches(p_vol);
    if (err != 0) {
        goto end;
    }
    p_vol->flags |= 0x08;
    if ((p_vol->flags & 0x08) == 0) {
        err = 9;
        goto check;
    }
    PFSYS_GetCurrentContextID(&context_id);
    p_vol->current_dir[0].stat |= 1;
    if (PFVOL_CheckContextRegistered(context_id) != 0) {
        p_vol->current_dir[1].stat |= 1;
        p_vol->current_dir[1].context_id = context_id;
    }
    p_dir = &p_vol->current_dir[0].directory;
    for (i = 0; (u32)i < 4; i++) {
        err = PFENT_GetRootDir(p_vol, p_dir);
        if (err != 0) {
            goto check;
        }
        p_dir++;
    }
    err = 0;
check:
    if (err == 0 && (p_vol->flags & 0x40) != 0) {
        err = PFDRV_format(p_vol, p_vol->format_param);
        if (err == 0 && (p_vol->flags & 0x80) == 0) {
            err = PFFAT_InitFATRegion(p_vol);
            if (err == 0) {
                err = PFENT_MakeRootDir(p_vol);
            }
        }
    }
end:
    if (err != 0) {
        p_vol->flags &= ~0x08;
    }
    return err;
}

s32 PFVOL_p_unmount(PF_VOLUME* p_vol, u32 mode) {
    s32 err = 0;
    s32 err2;
    if ((p_vol->flags & 0x08) == 0) {
        return 9;
    }
    PFFILE_FinalizeAllFiles(p_vol);
    PFDIR_FinalizeAllDirs(p_vol);
    err2 = PFCACHE_FlushAllCaches(p_vol);
    if (err2 != 0) {
        err = err2;
    }
    if (err2 == 0 || (mode & 1) != 0) {
        PFCACHE_FreeAllCaches(p_vol);
        err2 = PFDRV_unmount(p_vol, mode);
        if (err2 == 0) {
            if ((p_vol->flags & 0x08) != 0) {
                p_vol->current_dir[0].stat = 0;
                p_vol->current_dir[1].stat = 0;
                p_vol->current_dir[2].stat = 0;
                p_vol->current_dir[3].stat = 0;
            }
            p_vol->flags &= ~0x08;
        }
        if (err2 != 0 && err == 0) {
            err = err2;
        }
    }
    if (err == 0 || (mode & 1) != 0) {
        PFDRV_ClearMountRequested(p_vol);
        PFDRV_ClearUnmountRequested(p_vol);
        pf_vol_set.num_mounted_volumes--;
    }
    return err;
}

s32 PFVOL_p_format(PF_VOLUME* p_vol, const u8* param) {
    s32 err;
    u32 num_free;
    if (p_vol == NULL) {
        return 0xA;
    }
    if ((p_vol->flags & 0x02) != 0) {
        return 0xB;
    }
    err = PFDRV_format(p_vol, param);
    if (err != 0) {
        return err;
    }
    if ((p_vol->flags & 0x08) != 0) {
        PFCACHE_FreeAllCaches(p_vol);
        err = PFVOL_p_unmount(p_vol, 0);
        if (err != 0) {
            return err;
        }
    }
    if ((p_vol->flags & 0x08) == 0) {
        err = PFVOL_DoMountVolume(p_vol);
        if (err != 0) {
            goto end;
        }
        p_vol->fsi_flag &= ~0x07;
        PFDRV_ClearUnmountRequested(p_vol);
        pf_vol_set.num_mounted_volumes++;
    }
    PFDRV_ClearMountRequested(p_vol);
    err = 0;
end:
    if (err != 0) {
        return err;
    }
    if ((p_vol->flags & 0x02) != 0) {
        return 0xB;
    }
    if ((p_vol->flags & 0x80) != 0) {
        if (p_vol->bpb.fat_type == FAT_32 && (p_vol->fsi_flag & 0x02) != 0) {
            p_vol->fsi_flag |= 0x04;
            PFFAT_RefreshFSINFO(p_vol);
        } else {
            p_vol->fsi_flag &= ~0x04;
            if (p_vol->bpb.fat_type != FAT_32) {
                p_vol->fsi_flag &= ~0x03;
            }
            err = PFFAT_CountFreeClusters(p_vol, &num_free);
            if (err != 0) {
                return err;
            }
        }
    } else {
        err = PFFAT_InitFATRegion(p_vol);
        if (err != 0) {
            return err;
        }
        err = PFENT_MakeRootDir(p_vol);
        if (err != 0) {
            return err;
        }
        if (p_vol->bpb.fat_type != FAT_32) {
            p_vol->fsi_flag &= ~0x03;
        }
        if (p_vol->bpb.fat_type == FAT_32 && (p_vol->fsi_flag & 0x02) != 0) {
            err = PFFAT_RefreshFSINFO(p_vol);
            if (err != 0) {
                return err;
            }
        }
    }
    return 0;
}

s32 PFVOL_p_setvol(PF_VOLUME* p_vol, const s8* label) {
    s32 err;
    u32 start_cluster;
    u32 pos;
    u32 ppos;
    PF_STR pattern;
    PF_FAT_HINT hint;
    PF_FFD ffd;
    PF_DIR_ENT ent;
    PF_DIR_ENT root;
    err = PFENT_GetRootDir(p_vol, &root);
    if (err != 0) {
        return err;
    }
    PFFAT_InitFFD(&ffd, &hint, p_vol, &start_cluster);
    PFSTR_InitStr(&pattern, (const s8*)"*", 1);
    PFSTR_SetLocalStr(&pattern, NULL);
    err = PFENT_findEntryPos(&ffd, &ent, 0, &pattern, 8, 0, &pos, &ppos);
    if (err != 0 && err != 3) {
        return err;
    }
    if (ppos == 0xF423F) {
        goto do_alloc;
    }
    if (ent.start_cluster == 1) {
        ent.start_cluster = 0;
    }
    goto alloc_done;
do_alloc:
    {
        PFSTR_InitStr(&pattern, (const s8*)"\0\0\0", 1);
        PFSTR_SetLocalStr(&pattern, NULL);
        err = PFENT_allocateEntry(&ent, 1, &ffd, &pos, &pattern);
        if (err != 0) {
            return err;
        }
        *(u16*)&ent.long_name[0] = 0;
        ent.start_cluster = 0;
        ent.file_size = 0;
        ent.p_vol = p_vol;
        ent.small_letter_flag = 0;
        ent.attr = 8;
        ent.path_len = 3;
        ent.create_date = 0;
        ent.create_time = 0;
        ent.access_date = 0;
        ent.create_time_ms = 0;
    }
alloc_done:
    pf_memcpy(ent.short_name, label, 0xC);
    PFENT_getcurrentDateTimeForEnt(&ent.modify_date, &ent.modify_time);
    err = PFENT_updateEntry(&ent, 0);
    return err;
}

s32 PFVOL_p_getvol(PF_VOLUME* p_vol, PF_VOL_INF* p_vinf) {
    s32 err;
    u32 start_cluster;
    u32 pos;
    u32 ppos;
    PF_STR pattern;
    PF_FAT_HINT hint;
    PF_FFD ffd;
    PF_DIR_ENT ent;
    PF_DIR_ENT root;
    err = PFENT_GetRootDir(p_vol, &root);
    if (err != 0) {
        return err;
    }
    PFFAT_InitFFD(&ffd, &hint, p_vol, &start_cluster);
    PFSTR_InitStr(&pattern, (const s8*)"*", 1);
    PFSTR_SetLocalStr(&pattern, (const s8*)"*");
    err = PFENT_findEntryPos(&ffd, &ent, 0, &pattern, 8, 0, &pos, &ppos);
    if (err != 0 && err != 3) {
        return err;
    }
    if (ppos != 0xF423F) {
        p_vinf->modify_date = ent.modify_date;
        p_vinf->modify_time = ent.modify_time;
        p_vinf->attr = ent.attr;
        pf_strcpy(p_vinf->label, ent.short_name);
    } else {
        p_vinf->modify_date = 0;
        p_vinf->modify_time = 0;
        p_vinf->attr = 8;
        PFDRV_StoreVolumeLabelToBuf(p_vinf->label, p_vol);
    }
    return 0;
}

s32 PFVOL_p_rmvvol(PF_VOLUME* p_vol) {
    u8 del_code = *((const u8*)pf_vol_dummy_e5);
    u32 pos;
    u32 ppos;
    u32 written;
    PF_FAT_HINT hint;
    PF_STR pattern;
    PF_FFD ffd;
    PF_DIR_ENT root;
    PF_DIR_ENT ent;
    s32 err;
    err = PFENT_GetRootDir(p_vol, &root);
    if (err != 0) {
        return err;
    }
    PFFAT_InitFFD(&ffd, &hint, p_vol, &root.start_cluster);
    PFSTR_InitStr(&pattern, (const s8*)"*", 1);
    PFSTR_SetLocalStr(&pattern, (const s8*)"*");
    err = PFENT_findEntryPos(&ffd, &ent, 0, &pattern, 8, 0, &pos, &ppos);
    if (err != 0 && err != 3) {
        return err;
    }
    if (ppos != 0xF423F) {
        err = PFSEC_WriteData(p_vol, &del_code, ent.entry_sector, ent.entry_offset, 1, &written, 0);
        if (err != 0) {
            return err;
        }
        if (written != 1) {
            return 0x11;
        }
    }
    return 0;
}

s32 PFVOL_InitModule(u32 flag, u32 param) {
    s32 i;
    PF_VOLUME* p_vol;
    u32 stat;
    if ((flag & 0x10000) != 0) {
        pf_vol_set.config |= 0x10000;
    } else {
        pf_vol_set.config &= ~0x10000;
    }
    stat = pf_vol_set.current_vol[0].stat | 1;
    pf_vol_set.current_vol[0].p_vol = &pf_vol_set.volumes[0];
    pf_vol_set.current_vol[1].p_vol = &pf_vol_set.volumes[0];
    pf_vol_set.current_vol[2].p_vol = &pf_vol_set.volumes[0];
    pf_vol_set.current_vol[3].p_vol = &pf_vol_set.volumes[0];
    pf_vol_set.current_vol[0].stat = stat;
    pf_vol_set.num_attached_volumes = 0;
    pf_vol_set.num_mounted_volumes = 0;
    if ((flag & 0x10000) != 0) {
        pf_vol_set.config |= 0x10000;
    } else {
        pf_vol_set.config &= ~0x10000;
    }
    pf_vol_set.pad_3C = param;
    pf_vol_set.last_error = 0;
    pf_vol_set.last_driver_error = 0;
    pf_vol_set.setting = 1;
    pf_vol_set.codeset.oem2unicode = PFCODE_CP932_OEM2Unicode;
    pf_vol_set.codeset.unicode2oem = PFCODE_CP932_Unicode2OEM;
    pf_vol_set.codeset.oem_char_width = PFCODE_CP932_OEMCharWidth;
    pf_vol_set.codeset.is_oem_mb_char = PFCODE_CP932_isOEMMBchar;
    pf_vol_set.codeset.unicode_char_width = PFCODE_CP932_UnicodeCharWidth;
    pf_vol_set.codeset.is_unicode_mb_char = PFCODE_CP932_isUnicodeMBchar;
    p_vol = &pf_vol_set.volumes[0];
    for (i = 0; i < 26; i++) {
        pf_memset(p_vol, 0, sizeof(PF_VOLUME));
        p_vol++;
    }
    PF_InitLockFile();
    return 0;
}

s32 PFVOL_CheckForRead(PF_VOLUME* p_vol) {
    s32 err = 0;
    if (PFDRV_IsInserted(p_vol) != 0) {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(p_vol) != 0) {
            if ((p_vol->flags & 0x08) == 0) {
                err = PFVOL_DoMountVolume(p_vol);
                if (err == 0) {
                    goto mount_ok;
                }
                goto mount_done;
            }
            goto mount_clear;
mount_ok:
            p_vol->fsi_flag &= ~0x07;
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes++;
mount_clear:
            PFDRV_ClearMountRequested(p_vol);
            err = 0;
mount_done:
            if (err == 0) {
                goto merge;
            }
            goto err_test;
        }
    } else {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(p_vol) != 0) {
            PFDRV_ClearMountRequested(p_vol);
        }
    }
merge:
    err = 0;
err_test:
    if (err != 0) {
        return err;
    }
    return (p_vol->flags & 0x08) != 0 ? 0 : 9;
}

s32 PFVOL_CheckForWrite(PF_VOLUME* p_vol) {
    s32 err = 0;
    if (PFDRV_IsInserted(p_vol) != 0) {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(p_vol) != 0) {
            if ((p_vol->flags & 0x08) == 0) {
                err = PFVOL_DoMountVolume(p_vol);
                if (err == 0) {
                    goto mount_ok;
                }
                goto mount_done;
            }
            goto mount_clear;
mount_ok:
            p_vol->fsi_flag &= ~0x07;
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes++;
mount_clear:
            PFDRV_ClearMountRequested(p_vol);
            err = 0;
mount_done:
            if (err == 0) {
                goto merge;
            }
            goto err_test;
        }
    } else {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(p_vol) != 0) {
            PFDRV_ClearMountRequested(p_vol);
        }
    }
merge:
    err = 0;
err_test:
    if (err != 0) {
        return err;
    }
    if ((p_vol->flags & 0x08) == 0) {
        goto ret9;
    }
    err = -(s32)((p_vol->flags >> 1) & 0x01) & 0x0B;
    goto ret;
ret9:
    err = 9;
ret:
    return err;
}

s32 PFVOL_CheckCurrentDir(PF_VOLUME* p_vol, u32 cluster) {
    s32 context_id;
    s32 ret = 0;
    u32 i;
    if ((p_vol->flags & 0x08) == 0) {
        return 9;
    }
    PFSYS_GetCurrentContextID(&context_id);
    for (i = 1; i < 4; i++) {
        if ((p_vol->current_dir[i].stat & 1) != 0 && p_vol->current_dir[i].context_id == context_id) {
            break;
        }
    }
    if (i == 4) {
        i = 0;
    }
    if (cluster == p_vol->current_dir[i].directory.start_cluster) {
        ret = -1;
    }
    return ret;
}

s32 PFVOL_SetCurrentDir(PF_VOLUME* p_vol, const PF_DIR_ENT* p_ent) {
    s32 context_id;
    u32 i;
    if ((p_vol->flags & 0x08) == 0) {
        return 9;
    }
    PFSYS_GetCurrentContextID(&context_id);
    for (i = 1; i < 4; i++) {
        if ((p_vol->current_dir[i].stat & 1) != 0 && p_vol->current_dir[i].context_id == context_id) {
            p_vol->current_dir[i].directory = *p_ent;
            break;
        }
    }
    if (i == 4) {
        if (PFVOL_CheckContextRegistered(context_id) != 0) {
            for (i = 1; i < 4; i++) {
                if ((p_vol->current_dir[i].stat & 1) == 0) {
                    p_vol->current_dir[i].stat |= 1;
                    p_vol->current_dir[i].context_id = context_id;
                    p_vol->current_dir[i].directory = *p_ent;
                    break;
                }
            }
        }
    }
    p_vol->current_dir[0].directory = *p_ent;
    return 0;
}

s32 PFVOL_GetCurrentDir(PF_VOLUME* p_vol, PF_DIR_ENT* p_ent) {
    s32 context_id;
    u32 i;
    if ((p_vol->flags & 0x08) == 0) {
        return 9;
    }
    PFSYS_GetCurrentContextID(&context_id);
    for (i = 1; i < 4; i++) {
        if ((p_vol->current_dir[i].stat & 1) != 0 && p_vol->current_dir[i].context_id == context_id) {
            *p_ent = p_vol->current_dir[i].directory;
            goto end;
        }
    }
    if (i == 4) {
        if (PFVOL_CheckContextRegistered(context_id) != 0) {
            for (i = 1; i < 4; i++) {
                if ((p_vol->current_dir[i].stat & 1) == 0) {
                    p_vol->current_dir[i].stat |= 1;
                    p_vol->current_dir[i].context_id = context_id;
                    *p_ent = p_vol->current_dir[i].directory;
                    goto end;
                }
            }
        } else {
            *p_ent = p_vol->current_dir[0].directory;
        }
    }
end:
    return 0;
}

s32 PFVOL_SetCurrentVolume(PF_VOLUME* p_vol) {
    s32 context_id;
    u32 i;
    PFSYS_GetCurrentContextID(&context_id);
    for (i = 1; i < 4; i++) {
        if ((pf_vol_set.current_vol[i].stat & 1) != 0 && pf_vol_set.current_vol[i].context_id == context_id) {
            pf_vol_set.current_vol[i].p_vol = p_vol;
            goto end;
        }
    }
    if (i == 4) {
        if (PFVOL_CheckContextRegistered(context_id) != 0) {
            for (i = 1; i < 4; i++) {
                if ((pf_vol_set.current_vol[i].stat & 1) == 0) {
                    pf_vol_set.current_vol[i].stat |= 1;
                    pf_vol_set.current_vol[i].context_id = context_id;
                    pf_vol_set.current_vol[i].p_vol = p_vol;
                    goto end;
                }
            }
        }
    }
end:
    pf_vol_set.current_vol[0].p_vol = p_vol;
    return 0;
}

PF_VOLUME* PFVOL_GetCurrentVolume(void) {
    s32 context_id;
    PF_VOLUME* p_vol = NULL;
    u32 i;
    PFSYS_GetCurrentContextID(&context_id);
    for (i = 1; i < 4; i++) {
        if ((pf_vol_set.current_vol[i].stat & 1) != 0 && pf_vol_set.current_vol[i].context_id == context_id) {
            p_vol = pf_vol_set.current_vol[i].p_vol;
            goto end;
        }
    }
    if (i == 4) {
        if (PFVOL_CheckContextRegistered(context_id) != 0) {
            for (i = 1; i < 4; i++) {
                if ((pf_vol_set.current_vol[i].stat & 1) == 0) {
                    pf_vol_set.current_vol[i].stat |= 1;
                    pf_vol_set.current_vol[i].context_id = context_id;
                    p_vol = pf_vol_set.current_vol[i].p_vol;
                    goto end;
                }
            }
        } else {
            p_vol = pf_vol_set.current_vol[0].p_vol;
        }
    }
end:
    return p_vol;
}

PF_VOLUME* PFVOL_GetVolumeFromDrvChar(s8 drv_char) {
    s16 index = pf_toupper(drv_char) - 'A';
    if (index < 0 || index >= 0x1A) {
        return NULL;
    }
    return &pf_vol_set.volumes[index];
}

s32 PFVOL_derrnum(s8 drv_char) {
    PF_VOLUME* p_vol = PFVOL_GetVolumeFromDrvChar(drv_char);
    return p_vol->last_driver_error;
}

s32 PFVOL_errnum(void) {
    return pf_vol_set.last_error;
}

s32 PFVOL_setvol(s8 drv_char, PF_STR* p_label) {
    PF_VOLUME* p_vol;
    s32 err;
    u16 len;
    s8 label[12];

    p_vol = PFVOL_GetVolumeFromDrvChar(drv_char);
    len = PFSTR_StrLen(p_label);

    if (PFDRV_IsInserted(p_vol) != 0) {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        err = PFDRV_IsMountRequested(p_vol);
        if (err != 0) {
            if ((p_vol->flags & 0x08) == 0) {
                err = PFVOL_DoMountVolume(p_vol);
                if (err == 0) {
                    goto mount_ok;
                }
                goto mount_done;
            }
            goto mount_clear;
mount_ok:
            p_vol->fsi_flag &= ~0x07;
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes++;
mount_clear:
            PFDRV_ClearMountRequested(p_vol);
            err = 0;
mount_done:
            if (err == 0) {
                goto merge;
            }
            goto err_test;
        }
    } else {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(p_vol) != 0) {
            PFDRV_ClearMountRequested(p_vol);
        }
    }
merge:
    err = 0;
err_test:
    if (err == 0) {
        if ((p_vol->flags & 0x08) == 0) {
            err = 9;
        } else {
            err = -(s32)((p_vol->flags >> 1) & 0x01) & 0x0B;
        }
    }
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }

    PFSTR_ToUpperNStr(p_label, 0xB, label);
    if (len < 0xB) {
        label[len] = 0;
    }
    err = PFVOL_p_setvol(p_vol, label);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    err = PFCACHE_FlushFATCache(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        goto recheck;
    }
    err = PFCACHE_FlushDataCacheSpecific(p_vol, 0);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
    }
recheck:
    if (err != 0) {
        return err;
    }
    err = PFDRV_StoreVolumeLabelToBPB(p_vol, label);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
    }
    return err;
}

s32 PFVOL_getvol(s8 drv_char, PF_VOL_INF* p_vinf) {
    PF_VOLUME* p_vol;
    s32 err;

    p_vol = PFVOL_GetVolumeFromDrvChar(drv_char);

    if (pf_memcmp(p_vol->label, (const s8*)(const s8*)"NO NAME    ", 0xB) == 0) {
        pf_vol_set.last_error = 3;
        p_vol->last_error = 3;
        return 3;
    }

    if (PFDRV_IsInserted(p_vol) != 0) {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        err = PFDRV_IsMountRequested(p_vol);
        if (err != 0) {
            if ((p_vol->flags & 0x08) == 0) {
                err = PFVOL_DoMountVolume(p_vol);
                if (err == 0) {
                    goto mount_ok;
                }
                goto mount_done;
            }
            goto mount_clear;
mount_ok:
            p_vol->fsi_flag &= ~0x07;
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes++;
mount_clear:
            PFDRV_ClearMountRequested(p_vol);
            err = 0;
mount_done:
            if (err == 0) {
                goto merge;
            }
            goto err_test;
        }
    } else {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(p_vol) != 0) {
            PFDRV_ClearMountRequested(p_vol);
        }
    }
merge:
    err = 0;
err_test:
    if (err == 0) {
        err = (p_vol->flags & 0x08) != 0 ? 0 : 9;
    }
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    err = PFVOL_p_getvol(p_vol, p_vinf);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    return 0;
}

s32 PFVOL_rmvvol(s8 drv_char) {
    PF_VOLUME* p_vol;
    s32 err;

    p_vol = PFVOL_GetVolumeFromDrvChar(drv_char);

    if (pf_memcmp(p_vol->label, (const s8*)(const s8*)"NO NAME    ", 0xB) == 0) {
        pf_vol_set.last_error = 3;
        p_vol->last_error = 3;
        return 3;
    }

    if (PFDRV_IsInserted(p_vol) != 0) {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        err = PFDRV_IsMountRequested(p_vol);
        if (err != 0) {
            if ((p_vol->flags & 0x08) == 0) {
                err = PFVOL_DoMountVolume(p_vol);
                if (err == 0) {
                    goto mount_ok;
                }
                goto mount_done;
            }
            goto mount_clear;
mount_ok:
            p_vol->fsi_flag &= ~0x07;
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes++;
mount_clear:
            PFDRV_ClearMountRequested(p_vol);
            err = 0;
mount_done:
            if (err == 0) {
                goto merge;
            }
            goto err_test;
        }
    } else {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(p_vol) != 0) {
            PFDRV_ClearMountRequested(p_vol);
        }
    }
merge:
    err = 0;
err_test:
    if (err == 0) {
        if ((p_vol->flags & 0x08) == 0) {
            err = 9;
        } else {
            err = -(s32)((p_vol->flags >> 1) & 0x01) & 0x0B;
        }
    }
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    err = PFDRV_StoreVolumeLabelToBPB(p_vol, (const s8*)(const s8*)"NO NAME    ");
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    err = PFVOL_p_rmvvol(p_vol);
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

s32 PFVOL_getdev(s8 drv_char, PF_DEV_INF* p_inf) {
    PF_VOLUME* p_vol;
    s32 err;

    p_vol = PFVOL_GetVolumeFromDrvChar(drv_char);

    if (PFDRV_IsInserted(p_vol) != 0) {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        err = PFDRV_IsMountRequested(p_vol);
        if (err != 0) {
            if ((p_vol->flags & 0x08) == 0) {
                err = PFVOL_DoMountVolume(p_vol);
                if (err == 0) {
                    goto mount_ok;
                }
                goto mount_done;
            }
            goto mount_clear;
mount_ok:
            p_vol->fsi_flag &= ~0x07;
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes++;
mount_clear:
            PFDRV_ClearMountRequested(p_vol);
            err = 0;
mount_done:
            if (err == 0) {
                goto merge;
            }
            goto err_test;
        }
    } else {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(p_vol) != 0) {
            PFDRV_ClearMountRequested(p_vol);
        }
    }
merge:
    err = 0;
err_test:
    if (err == 0) {
        err = (p_vol->flags & 0x08) != 0 ? 0 : 9;
    }
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    p_inf->bytes_per_sector = p_vol->bpb.bytes_per_sector;
    p_inf->sectors_per_cluster = p_vol->bpb.sectors_per_cluster;
    p_inf->num_clusters = p_vol->bpb.num_clusters;
    err = PFFAT_CountFreeClusters(p_vol, &p_inf->num_free_clusters);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    return 0;
}

s32 PFVOL_buffering(s8 drv_char, u32 mode) {
    PF_VOLUME* p_vol;
    s32 err;
    u32 flag;

    p_vol = PFVOL_GetVolumeFromDrvChar(drv_char);

    if (PFDRV_IsInserted(p_vol) != 0) {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        err = PFDRV_IsMountRequested(p_vol);
        if (err != 0) {
            if ((p_vol->flags & 0x08) == 0) {
                err = PFVOL_DoMountVolume(p_vol);
                if (err == 0) {
                    goto mount_ok;
                }
                goto mount_done;
            }
            goto mount_clear;
mount_ok:
            p_vol->fsi_flag &= ~0x07;
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes++;
mount_clear:
            PFDRV_ClearMountRequested(p_vol);
            err = 0;
mount_done:
            if (err == 0) {
                goto merge;
            }
            goto err_test;
        }
    } else {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(p_vol) != 0) {
            PFDRV_ClearMountRequested(p_vol);
        }
    }
merge:
    err = 0;
err_test:
    if (err == 0) {
        if ((p_vol->flags & 0x08) == 0) {
            err = 9;
        } else {
            err = -(s32)((p_vol->flags >> 1) & 0x01) & 0x0B;
        }
    }
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    flag = mode & 4;
    if (flag != 0 && (p_vol->buffer_mode & 1) == 0) {
        err = PFCACHE_FlushFATCache(p_vol);
        if (err != 0) {
            pf_vol_set.last_error = err;
            p_vol->last_error = err;
            return err;
        }
    }
    if ((mode & 1) != 0) {
        err = PFCACHE_SetWriteThroughMode(p_vol);
        if (err != 0) {
            pf_vol_set.last_error = err;
            p_vol->last_error = err;
            return err;
        }
    } else {
        err = PFCACHE_SetWriteBackMode(p_vol);
        if (err != 0) {
            pf_vol_set.last_error = err;
            p_vol->last_error = err;
            return err;
        }
    }
    if ((mode & 2) != 0) {
        p_vol->buffer_mode |= 2;
    } else {
        p_vol->buffer_mode &= ~2;
    }
    if (flag != 0) {
        p_vol->buffer_mode |= 4;
    } else {
        p_vol->buffer_mode &= ~4;
    }
    return 0;
}

s32 PFVOL_attach(PF_DRV_TBL* p_tbl, s32 notify, u32 notify_param) {
    PF_VOLUME* p_vol;
    s32 err;
    s32 i;

    if (p_tbl->p_cache_cfg->fat_buffer_size == 0) {
        p_tbl->p_cache_cfg->fat_buffer_size = 1;
    }
    if (p_tbl->p_cache_cfg->data_buffer_size == 0) {
        p_tbl->p_cache_cfg->data_buffer_size = 1;
    }
    p_tbl->flags = 0;
    p_tbl->drv_char = 0;
    if (notify != 0) {
        err = fa_nanddrv_NotifyNANDFile(notify, notify_param);
        if (err != 0) {
            pf_vol_set.last_error = 0x11;
            return 0x11;
        }
    }
    for (i = 0; i < 26; i++) {
        p_vol = &pf_vol_set.volumes[i];
        if ((p_vol->flags & 1) == 0) {
            break;
        }
    }
    if (i < 0 || i >= 26 || pf_vol_set.num_attached_volumes < 0 || pf_vol_set.num_attached_volumes >= 26) {
        pf_vol_set.last_error = 4;
        return 4;
    }
    p_vol->num_free_clusters = -1;
    p_vol->last_free_cluster = -1;
    pf_memset(p_vol, 0, sizeof(PF_VOLUME));
    p_vol->p_part = p_tbl->p_part;
    p_vol->drv_char = 'A' + (s16)i;
    p_vol->tail_size = 1;
    p_vol->p_tail_buf = (u32*)p_vol->tail_area;
    err = PFDRV_init(p_vol);
    if (err == 0) {
        PFCACHE_SetCache(p_vol, p_tbl->p_cache_cfg->fat_pages, p_tbl->p_cache_cfg->data_pages,
                         p_tbl->p_cache_cfg->num_fat_pages, p_tbl->p_cache_cfg->num_data_pages);
        PFCACHE_SetFATBufferSize(p_vol, p_tbl->p_cache_cfg->fat_buffer_size);
        PFCACHE_SetDataBufferSize(p_vol, p_tbl->p_cache_cfg->data_buffer_size);
    }
    if (err != 0) {
        pf_vol_set.last_error = err;
        return err;
    }
    p_vol->flags |= 1;
    p_tbl->flags |= 1;
    p_vol->drv_char = 'A' + i;
    p_tbl->drv_char = 'A' + i;
    pf_vol_set.num_attached_volumes++;
    err = PFDRV_IsInserted(p_vol);
    if (err != 0) {
        p_tbl->flags |= 0x10;
        if ((p_vol->flags & 0x08) == 0) {
            err = PFVOL_DoMountVolume(p_vol);
            if (err != 0) {
                goto check;
            }
            p_vol->fsi_flag &= ~0x07;
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes++;
        }
        PFDRV_ClearMountRequested(p_vol);
        err = 0;
check:
        if (err != 0) {
            pf_vol_set.last_error = err;
            p_vol->last_error = err;
        } else {
            p_tbl->flags |= 2;
        }
    }
    return 0;
}

s32 PFVOL_detach(s8 drv_char) {
    PF_VOLUME* p_vol;
    s32 err;

    p_vol = PFVOL_GetVolumeFromDrvChar(drv_char);

    if ((p_vol->flags & 0x08) != 0) {
        pf_vol_set.last_error = 0xA;
        p_vol->last_error = 0xA;
        return 0xA;
    }
    if ((p_vol->flags & 0x01) == 0) {
        pf_vol_set.last_error = 0xA;
        p_vol->last_error = 0xA;
        return 0xA;
    }
    err = PFDRV_finalize(p_vol);
    err = (err != 0) ? err : 0;
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    p_vol->flags &= ~0x03;
    pf_vol_set.num_attached_volumes--;
    return 0;
}

s32 PFVOL_format(s8 drv_char, const u8* param) {
    PF_VOLUME* p_vol;
    s32 err;
    s32 has_mount_req = 0;

    p_vol = PFVOL_GetVolumeFromDrvChar(drv_char);

    if ((p_vol->flags & 0x01) == 0) {
        pf_vol_set.last_error = 0xA;
        p_vol->last_error = 0xA;
        return 0xA;
    }
    if (PFDRV_IsInserted(p_vol) == 0) {
        pf_vol_set.last_error = 9;
        p_vol->last_error = 9;
        return 9;
    }
    if (PFDRV_IsMountRequested(p_vol) != 0) {
        PFDRV_ClearMountRequested(p_vol);
        has_mount_req = 1;
    }
    if (PFDRV_IsInserted(p_vol) != 0) {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        err = PFDRV_IsMountRequested(p_vol);
        if (err != 0) {
            if ((p_vol->flags & 0x08) == 0) {
                err = PFVOL_DoMountVolume(p_vol);
                if (err != 0) {
                    goto mount_done;
                } else {
                    goto mount_ok;
                }
            }
            goto mount_clear;
mount_ok:
            p_vol->fsi_flag &= ~0x07;
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes++;
mount_clear:
            PFDRV_ClearMountRequested(p_vol);
            err = 0;
mount_done:
            if (err == 0) {
                goto mount_skip;
            }
            goto check;
mount_skip:;
        }
    } else {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(p_vol) != 0) {
            PFDRV_ClearMountRequested(p_vol);
        }
    }
    err = 0;
check:
    if (err != 0) {
        if (has_mount_req != 0) {
            p_vol->flags |= 0x10;
        }
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    if (p_vol->num_open_files != 0) {
        PFFILE_FinalizeAllFiles(p_vol);
        PFCACHE_FreeAllCaches(p_vol);
    }
    if (p_vol->num_open_dirs != 0) {
        PFDIR_FinalizeAllDirs(p_vol);
    }
    err = PFVOL_p_format(p_vol, param);
    if (err != 0) {
        if (has_mount_req != 0) {
            p_vol->flags |= 0x10;
        }
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    p_vol->fsi_flag |= 4;
    if (p_vol->bpb.fat_type == FAT_32) {
        p_vol->num_free_clusters = p_vol->bpb.num_clusters - 1;
    } else {
        p_vol->num_free_clusters = p_vol->bpb.num_clusters;
    }
    return 0;
}

s32 PFVOL_mount(s8 drv_char) {
    PF_VOLUME* p_vol;
    s32 err;

    p_vol = PFVOL_GetVolumeFromDrvChar(drv_char);

    if (PFDRV_IsInserted(p_vol) != 0) {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        err = PFDRV_IsMountRequested(p_vol);
        if (err != 0) {
            if ((p_vol->flags & 0x08) == 0) {
                err = PFVOL_DoMountVolume(p_vol);
                if (err == 0) {
                    goto mount_ok;
                }
                goto mount_done;
            }
            goto mount_clear;
mount_ok:
            p_vol->fsi_flag &= ~0x07;
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes++;
mount_clear:
            PFDRV_ClearMountRequested(p_vol);
            err = 0;
mount_done:
            if (err == 0) {
                goto merge;
            }
            goto err_test;
        }
    } else {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(p_vol) != 0) {
            PFDRV_ClearMountRequested(p_vol);
        }
    }
merge:
    err = 0;
err_test:
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    if (PFDRV_IsInserted(p_vol) == 0) {
        pf_vol_set.last_error = 9;
        p_vol->last_error = 9;
        return 9;
    }
    if ((p_vol->flags & 0x08) != 0) {
        return 0;
    }
    if ((p_vol->flags & 0x08) == 0) {
        err = PFVOL_DoMountVolume(p_vol);
        if (err == 0) {
            goto mount_ok2;
        }
        goto mount_done2;
    }
    goto mount_clear2;
mount_ok2:
    p_vol->fsi_flag &= ~0x07;
    PFDRV_ClearUnmountRequested(p_vol);
    pf_vol_set.num_mounted_volumes++;
mount_clear2:
    PFDRV_ClearMountRequested(p_vol);
    err = 0;
mount_done2:
    if (err == 0) {
        goto mount_ret;
    }
    pf_vol_set.last_error = err;
    p_vol->last_error = err;
    return err;
mount_ret:
    return 0;
}

s32 PFVOL_unmount(s8 drv_char, u32 mode) {
    PF_VOLUME* p_vol;
    s32 err;
    s32 ret = 0;

    p_vol = PFVOL_GetVolumeFromDrvChar(drv_char);

    if ((p_vol->flags & 0x01) == 0) {
        pf_vol_set.last_error = 0xA;
        return 0xA;
    }
    PFDRV_ClearMountRequested(p_vol);
    if (PFDRV_IsInserted(p_vol) != 0) {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        err = PFDRV_IsMountRequested(p_vol);
        if (err != 0) {
            if ((p_vol->flags & 0x08) == 0) {
                err = PFVOL_DoMountVolume(p_vol);
                if (err == 0) {
                    goto mount_ok;
                }
                goto mount_done;
            }
            goto mount_clear;
mount_ok:
            p_vol->fsi_flag &= ~0x07;
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes++;
mount_clear:
            PFDRV_ClearMountRequested(p_vol);
            err = 0;
mount_done:
            if (err == 0) {
                goto merge;
            }
            goto err_test;
        }
    } else {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(p_vol) != 0) {
            PFDRV_ClearMountRequested(p_vol);
        }
    }
merge:
    err = 0;
err_test:
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    if ((p_vol->flags & 0x08) == 0) {
        return 0;
    }
    if (p_vol->num_open_files != 0 || p_vol->num_open_dirs != 0) {
        ret = 1;
        pf_vol_set.last_error = 0x13;
        p_vol->last_error = 0x13;
        if ((mode & 1) == 0) {
            return 0x13;
        }
    }
    err = PFVOL_p_unmount(p_vol, mode);
    if (err != 0) {
        if (ret == 0) {
            pf_vol_set.last_error = err;
            p_vol->last_error = err;
            ret = 1;
            if ((mode & 1) == 0) {
                ret = err;
            }
        }
    }
    return ret;
}

s32 PFVOL_setupfsi(s8 drv_char, s32 mode) {
    PF_VOLUME* p_vol;
    s32 err;
    u32 num_free;

    p_vol = PFVOL_GetVolumeFromDrvChar(drv_char);

    if (PFDRV_IsInserted(p_vol) != 0) {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        err = PFDRV_IsMountRequested(p_vol);
        if (err != 0) {
            if ((p_vol->flags & 0x08) == 0) {
                err = PFVOL_DoMountVolume(p_vol);
                if (err == 0) {
                    goto mount_ok;
                }
                goto mount_done;
            }
            goto mount_clear;
mount_ok:
            p_vol->fsi_flag &= ~0x07;
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes++;
mount_clear:
            PFDRV_ClearMountRequested(p_vol);
            err = 0;
mount_done:
            if (err == 0) {
                goto merge;
            }
            goto err_test;
        }
    } else {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(p_vol) != 0) {
            PFDRV_ClearMountRequested(p_vol);
        }
    }
merge:
    err = 0;
err_test:
    if (err == 0) {
        err = (p_vol->flags & 0x08) != 0 ? 0 : 9;
    }
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    if (p_vol->bpb.fat_type != FAT_32) {
        pf_vol_set.last_error = 0xC;
        p_vol->last_error = 0xC;
        return 0xC;
    }
    if ((mode & 1) == 1) {
        p_vol->fsi_flag |= 5;
    } else if ((mode & 2) == 2) {
        p_vol->fsi_flag &= ~1;
    }
    if ((mode & 4) == 4) {
        p_vol->fsi_flag |= 2;
        if ((p_vol->fsi_flag & 4) == 0) {
            PFFAT_CountFreeClusters(p_vol, &num_free);
        }
    } else if ((mode & 8) == 8) {
        p_vol->fsi_flag &= ~2;
    }
    return 0;
}

s32 PFVOL_setclstlink(s8 drv_char, u32 flag, PF_CLSTLNK_CFG* p_cfg) {
    PF_VOLUME* p_vol;
    s32 err;

    p_vol = PFVOL_GetVolumeFromDrvChar(drv_char);

    if (p_vol->num_open_files != 0) {
        pf_vol_set.last_error = 0x13;
        p_vol->last_error = 0x13;
        return 0x13;
    }

    if (PFDRV_IsInserted(p_vol) != 0) {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        err = PFDRV_IsMountRequested(p_vol);
        if (err != 0) {
            if ((p_vol->flags & 0x08) == 0) {
                err = PFVOL_DoMountVolume(p_vol);
                if (err == 0) {
                    goto mount_ok;
                }
                goto mount_done;
            }
            goto mount_clear;
mount_ok:
            p_vol->fsi_flag &= ~0x07;
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes++;
mount_clear:
            PFDRV_ClearMountRequested(p_vol);
            err = 0;
mount_done:
            if (err == 0) {
                goto merge;
            }
            goto err_test;
        }
    } else {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(p_vol) != 0) {
            PFDRV_ClearMountRequested(p_vol);
        }
    }
merge:
    err = 0;
err_test:
    if (err == 0) {
        err = (p_vol->flags & 0x08) != 0 ? 0 : 9;
    }
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    if (flag == 1) {
        if (p_cfg->buffer == NULL) {
            pf_vol_set.last_error = 0xA;
            p_vol->last_error = 0xA;
            return 0xA;
        }
        p_vol->clst_flag |= 1;
        p_vol->clst_buf = p_cfg->buffer;
        pf_memset(p_cfg->buffer, 0, p_cfg->count * 0x14);
        p_vol->clst_interval = p_cfg->interval;
        p_vol->clst_count = p_cfg->count;
    } else {
        p_vol->clst_flag &= ~1;
        p_vol->clst_buf = NULL;
        p_vol->clst_interval = 0;
        p_vol->clst_count = 0;
    }
    return err;
}

s32 PFVOL_sync(s8 drv_char, u32 mode) {
    PF_VOLUME* p_vol;
    s32 err;
    u16 i;

    p_vol = PFVOL_GetVolumeFromDrvChar(drv_char);

    if (PFDRV_IsInserted(p_vol) != 0) {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        err = PFDRV_IsMountRequested(p_vol);
        if (err != 0) {
            if ((p_vol->flags & 0x08) == 0) {
                err = PFVOL_DoMountVolume(p_vol);
                if (err == 0) {
                    goto mount_ok;
                }
                goto mount_done;
            }
            goto mount_clear;
mount_ok:
            p_vol->fsi_flag &= ~0x07;
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes++;
mount_clear:
            PFDRV_ClearMountRequested(p_vol);
            err = 0;
mount_done:
            if (err == 0) {
                goto merge;
            }
            goto err_test;
        }
    } else {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(p_vol) != 0) {
            PFDRV_ClearMountRequested(p_vol);
        }
    }
merge:
    err = 0;
err_test:
    if (err == 0) {
        if ((p_vol->flags & 0x08) == 0) {
            err = 9;
        } else {
            err = -(s32)((p_vol->flags >> 1) & 0x01) & 0x0B;
        }
    }
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
    for (i = 0; i < 5; i++) {
        if ((p_vol->dir_handle[i].stat & 1) != 0) {
            err = PFENT_updateEntry(&p_vol->dir_handle[i].p_sdd->dir_entry, 1);
            if (err != 0) {
                pf_vol_set.last_error = err;
                p_vol->last_error = err;
                return err;
            }
        }
    }
    err = PFCACHE_FlushDataCache(p_vol);
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    if (mode == 1) {
        PFCACHE_FreeAllCaches(p_vol);
    }
    return err;
}

s32 PFVOL_settailbuf(s8 drv_char, u32 tail_size, u32* p_buf) {
    PF_VOLUME* p_vol;
    s32 err;

    p_vol = PFVOL_GetVolumeFromDrvChar(drv_char);

    if (PFDRV_IsInserted(p_vol) != 0) {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        err = PFDRV_IsMountRequested(p_vol);
        if (err != 0) {
            if ((p_vol->flags & 0x08) == 0) {
                err = PFVOL_DoMountVolume(p_vol);
                if (err == 0) {
                    goto mount_ok;
                }
                goto mount_done;
            }
            goto mount_clear;
mount_ok:
            p_vol->fsi_flag &= ~0x07;
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes++;
mount_clear:
            PFDRV_ClearMountRequested(p_vol);
            err = 0;
mount_done:
            if (err == 0) {
                goto merge;
            }
            goto err_test;
        }
    } else {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(p_vol) != 0) {
            PFDRV_ClearMountRequested(p_vol);
        }
    }
merge:
    err = 0;
err_test:
    if (err == 0) {
        err = (p_vol->flags & 0x08) != 0 ? 0 : 9;
    }
    if (err != 0) {
        pf_vol_set.last_error = err;
        p_vol->last_error = err;
        return err;
    }
    p_vol->tail_size = tail_size;
    p_vol->p_tail_buf = p_buf;
    return err;
}

s32 PFVOL_setvolcfg(s8 drv_char, PF_VOL_CFG* p_cfg) {
    PF_VOLUME* p_vol;
    s32 err;
    u32 flags;

    if (drv_char == -1) {
        if ((p_cfg->flags & 0x10000) != 0) {
            pf_vol_set.config |= 0x10000;
        } else if ((p_cfg->flags & 0x20000) != 0) {
            pf_vol_set.config &= ~0x10000;
        }
        goto end;
    }

    p_vol = PFVOL_GetVolumeFromDrvChar(drv_char);

    if (p_cfg->fat_buffer_size == 0) {
        p_cfg->fat_buffer_size = 1;
    }
    if (p_cfg->data_buffer_size == 0) {
        p_cfg->data_buffer_size = 1;
    }

    if (PFDRV_IsInserted(p_vol) != 0) {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(p_vol) != 0) {
            if ((p_vol->flags & 0x08) == 0) {
                err = PFVOL_DoMountVolume(p_vol);
                if (err != 0) {
                    goto check;
                }
                p_vol->fsi_flag &= ~0x07;
                PFDRV_ClearUnmountRequested(p_vol);
                pf_vol_set.num_mounted_volumes++;
            }
            PFDRV_ClearMountRequested(p_vol);
        }
    } else {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(p_vol) != 0) {
            PFDRV_ClearMountRequested(p_vol);
        }
    }
check:
    if (p_vol->num_open_files != 0 || p_vol->num_open_dirs != 0) {
        pf_vol_set.last_error = 0x13;
        p_vol->last_error = 0x13;
        return 0x13;
    }
    flags = p_cfg->flags;
    if ((flags & 1) != 0 || (flags & 2) != 0) {
        PFCACHE_FlushAllCaches(p_vol);
        PFCACHE_FreeAllCaches(p_vol);
        if ((p_cfg->flags & 1) != 0) {
            if (p_cfg->fat_buffer_size != p_vol->fat_buffer_size) {
                PFCACHE_SetFATBufferSize(p_vol, p_cfg->fat_buffer_size);
                p_cfg->flags &= ~1;
            }
        }
        if ((p_cfg->flags & 2) != 0) {
            if (p_cfg->data_buffer_size != p_vol->data_buffer_size) {
                PFCACHE_SetDataBufferSize(p_vol, p_cfg->data_buffer_size);
                p_cfg->flags &= ~2;
            }
        }
    }
    PFCACHE_InitCaches(p_vol);
    if ((p_cfg->file_config & 1) != 0) {
        p_vol->file_config |= 1;
    } else if ((p_cfg->file_config & 2) != 0) {
        p_vol->file_config &= ~1;
    }
end:
    return 0;
}

s32 PFVOL_getvolcfg(s8 drv_char, PF_VOL_CFG* p_cfg) {
    PF_VOLUME* p_vol;
    s32 err;

    if (drv_char == -1) {
        p_cfg->flags = pf_vol_set.config;
        if ((pf_vol_set.config & 0x10000) == 0) {
            p_cfg->flags = pf_vol_set.config | 0x20000;
        }
        p_cfg->file_config = 0;
        p_cfg->fat_buffer_size = 0;
        p_cfg->data_buffer_size = 0;
        return 0;
    }

    p_vol = PFVOL_GetVolumeFromDrvChar(drv_char);

    if (PFDRV_IsInserted(p_vol) != 0) {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        err = PFDRV_IsMountRequested(p_vol);
        if (err != 0) {
            if ((p_vol->flags & 0x08) == 0) {
                err = PFVOL_DoMountVolume(p_vol);
                if (err != 0) {
                    goto check;
                }
                p_vol->fsi_flag &= ~0x07;
                PFDRV_ClearUnmountRequested(p_vol);
                pf_vol_set.num_mounted_volumes++;
            }
            PFDRV_ClearMountRequested(p_vol);
            goto check;
        }
    } else {
        if (PFDRV_IsUnmountRequested(p_vol) != 0 && (p_vol->flags & 0x08) == 0) {
            PFFILE_FinalizeAllFiles(p_vol);
            PFDIR_FinalizeAllDirs(p_vol);
            if (PFDRV_unmount(p_vol, 1) == 0) {
                if ((p_vol->flags & 0x08) != 0) {
                    p_vol->current_dir[0].stat = 0;
                    p_vol->current_dir[1].stat = 0;
                    p_vol->current_dir[2].stat = 0;
                    p_vol->current_dir[3].stat = 0;
                }
                p_vol->flags &= ~0x08;
            }
            PFDRV_ClearUnmountRequested(p_vol);
            pf_vol_set.num_mounted_volumes--;
        }
        if (PFDRV_IsMountRequested(p_vol) != 0) {
            PFDRV_ClearMountRequested(p_vol);
        }
    }
check:
    p_cfg->flags = 0;
    p_cfg->file_config = p_vol->file_config;
    if ((p_vol->file_config & 1) != 1) {
        p_cfg->file_config |= 2;
    }
    p_cfg->fat_buffer_size = p_vol->fat_buffer_size;
    p_cfg->data_buffer_size = p_vol->data_buffer_size;
    return 0;
}

s32 PFVOL_setcode(PF_CHARCODE* p_codeset) {
    if (pf_vol_set.num_mounted_volumes > 0) {
        pf_vol_set.last_error = 0x24;
        return 0x24;
    }
    pf_vol_set.codeset.oem2unicode = p_codeset->oem2unicode;
    pf_vol_set.codeset.unicode2oem = p_codeset->unicode2oem;
    pf_vol_set.codeset.oem_char_width = p_codeset->oem_char_width;
    pf_vol_set.codeset.is_oem_mb_char = p_codeset->is_oem_mb_char;
    pf_vol_set.codeset.unicode_char_width = p_codeset->unicode_char_width;
    pf_vol_set.codeset.is_unicode_mb_char = p_codeset->is_unicode_mb_char;
    return 0;
}

s32 PFVOL_regctx(void) {
    s32 context_id;
    s32 err;
    u32 free;
    u32 i;
    u32 used;

    err = PFSYS_GetCurrentContextID(&context_id);
    if (err != 0) {
        pf_vol_set.last_error = 0x1A;
        return 0x1A;
    }
    free = 0;
    for (i = 1; i < 4; i++) {
        used = pf_vol_set.context[i - 1].stat & 1;
        if (used != 0 && pf_vol_set.context[i - 1].context_id == context_id) {
            goto done;
        }
        if (used == 0 && free == 0) {
            free = i;
        }
    }
done:
    if (i == 4) {
        if (free != 0) {
            pf_vol_set.context[free - 1].stat = 1;
            pf_vol_set.context[free - 1].context_id = context_id;
        } else {
            pf_vol_set.last_error = 0x1A;
            return 0x1A;
        }
    }
    return err;
}

s32 PFVOL_unregctx(void) {
    s32 context_id;
    s32 err;
    u32 i;
    u32 j;
    u32 k;
    err = PFSYS_GetCurrentContextID(&context_id);
    if (err != 0) {
        pf_vol_set.last_error = 0x1A;
        return 0x1A;
    }
    for (i = 1; i < 4; i++) {
        if ((pf_vol_set.context[i - 1].stat & 1) != 0 &&
            pf_vol_set.context[i - 1].context_id == context_id) {
            pf_vol_set.context[i - 1].stat &= ~1;
            for (j = 1; j < 4; j++) {
                if ((pf_vol_set.current_vol[j].stat & 1) != 0 &&
                    pf_vol_set.current_vol[j].context_id == context_id) {
                    pf_vol_set.current_vol[j].stat &= ~1;
                    break;
                }
            }
            for (k = 0; k < 26; k++) {
                for (j = 1; j < 4; j++) {
                    if ((pf_vol_set.volumes[k].current_dir[j].stat & 1) != 0 &&
                        pf_vol_set.volumes[k].current_dir[j].context_id == context_id) {
                        pf_vol_set.volumes[k].current_dir[j].stat &= ~1;
                        break;
                    }
                }
            }
            break;
        }
    }
    if (i == 4) {
        pf_vol_set.last_error = 0x1A;
        return 0x1A;
    }
    return err;
}

s32 PFVOL_setencode(u32 code) {
    pf_vol_set.setting = (pf_vol_set.setting & ~0x03) | code;
    return 0;
}

const u8 pf_vol_dummy_e5[8] = {0xE5};
