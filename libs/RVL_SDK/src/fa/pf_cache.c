#include <private/vf/PrFILE2/fatfs/pf_cache.h>

typedef struct PFCACHE_BPB {
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
} PFCACHE_BPB;

struct PF_VOLUME {
    PFCACHE_BPB bpb;
    pf_u32 num_free_clusters;
    pf_u32 last_free_cluster;
    pf_u8 file_and_directory_state[0x1624 - 0x40];
    PF_SECTOR_CACHE cache;
};

enum { FAT_32 = 2 };

extern void* pf_memcpy(void* dest, const void* src, pf_u32 size);
extern void* pf_memset(void* dest, pf_s32 value, pf_u32 size);
extern pf_s32 PFDRV_lread(PF_VOLUME* p_vol, pf_u8* buffer, pf_u32 sector, pf_u32 num_sector, pf_u32* p_num_success);
extern pf_s32 PFDRV_lwrite(PF_VOLUME* p_vol, const pf_u8* buffer, pf_u32 sector, pf_u32 num_sector, pf_u32* p_num_success);
pf_s32 PFCACHE_FlushAllCaches(PF_VOLUME* p_vol);

#pragma dont_inline on
pf_s32 PFCACHE_InitPageList(PF_VOLUME* p_vol, PF_CACHE_PAGE** pp_head, PF_CACHE_PAGE* pages, PF_CACHE_BUFFER* buffers, pf_u32 num,
    pf_u32 size, pf_bool is_fat) {
    pf_u32 i;
    pf_u32 bps_per_buf;
    *pp_head = pages;
    bps_per_buf = (p_vol->bpb.bytes_per_sector >> 9) * size;
    if ((num / bps_per_buf) == 0) {
        return 30;
    }
    if ((num / bps_per_buf) == 1) {
        pages->p_prev = pages;
        pages->p_next = pages;
        pages->buffer = *buffers;
        pages->p_buf = *buffers;
        pages->p_mod_sbuf = PF_NULL;
        pages->p_mod_ebuf = PF_NULL;
        pages->size = size;
        pages->sector = 0xFFFFFFFF;
        pages->option = 0;
        pages->signature = PF_NULL;
        pages->stat &= ~(0x01 | 0x02);
        if (is_fat) {
            pages->stat |= 0x04;
        } else {
            pages->stat &= ~0x04;
        }
        return 0;
    }
    pages->p_prev = &pages[(num - (num % bps_per_buf)) - bps_per_buf];
    pages->p_next = &pages[bps_per_buf];
    pages->buffer = *buffers;
    pages->p_buf = *buffers;
    pages->p_mod_sbuf = PF_NULL;
    pages->p_mod_ebuf = PF_NULL;
    pages->size = size;
    pages->sector = 0xFFFFFFFF;
    pages->option = 0;
    pages->signature = PF_NULL;
    pages->stat &= ~(0x01 | 0x02);
    if (is_fat) {
        pages->stat |= 0x04;
    } else {
        pages->stat &= ~0x04;
    }
    for (i = bps_per_buf; i < (num - (num % bps_per_buf) - bps_per_buf); i += bps_per_buf) {
        pages[i].p_prev = &pages[i - bps_per_buf];
        pages[i].p_next = &pages[i + bps_per_buf];
        pages[i].buffer = buffers[i];
        pages[i].p_buf = buffers[i];
        pages[i].p_mod_sbuf = PF_NULL;
        pages[i].p_mod_ebuf = PF_NULL;
        pages[i].size = size;
        pages[i].sector = 0xFFFFFFFF;
        pages[i].option = 0;
        pages[i].signature = PF_NULL;
        pages[i].stat &= ~(0x01 | 0x02);
        if (is_fat) {
            pages[i].stat |= 0x04;
        } else {
            pages[i].stat &= ~0x04;
        }
    }
    pages[(num - (num % bps_per_buf)) - bps_per_buf].p_prev = &pages[((num - (num % bps_per_buf)) - bps_per_buf) - bps_per_buf];
    pages[(num - (num % bps_per_buf)) - bps_per_buf].p_next = pages;
    pages[(num - (num % bps_per_buf)) - bps_per_buf].buffer = buffers[(num - (num % bps_per_buf)) - bps_per_buf];
    pages[(num - (num % bps_per_buf)) - bps_per_buf].p_buf = buffers[(num - (num % bps_per_buf)) - bps_per_buf];
    pages[(num - (num % bps_per_buf)) - bps_per_buf].p_mod_sbuf = PF_NULL;
    pages[(num - (num % bps_per_buf)) - bps_per_buf].p_mod_ebuf = PF_NULL;
    pages[(num - (num % bps_per_buf)) - bps_per_buf].size = size;
    pages[(num - (num % bps_per_buf)) - bps_per_buf].sector = 0xFFFFFFFF;
    pages[(num - (num % bps_per_buf)) - bps_per_buf].option = 0;
    pages[(num - (num % bps_per_buf)) - bps_per_buf].signature = PF_NULL;
    pages[(num - (num % bps_per_buf)) - bps_per_buf].stat &= ~(0x01 | 0x02);
    if (is_fat) {
        pages[(num - (num % bps_per_buf)) - bps_per_buf].stat |= 0x04;
    } else {
        pages[(num - (num % bps_per_buf)) - bps_per_buf].stat &= ~0x04;
    }
    return 0;
}

#pragma dont_inline reset

#pragma dont_inline on
PF_CACHE_PAGE* PFCACHE_SearchForPage(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_head, pf_u32 sector) {
    PF_CACHE_PAGE* p_page;
    if (sector == 0xFFFFFFFF) {
        return PF_NULL;
    }
    if ((p_head->stat & 1) == 0) {
        return PF_NULL;
    }
    if (p_head->sector <= sector && p_head->sector + p_head->size - 1 >= sector) {
        p_head->p_buf = &p_head->buffer[(sector - p_head->sector) << p_vol->bpb.log2_bytes_per_sector];
        return p_head;
    }
    for (p_page = p_head->p_next; p_page != p_head; p_page = p_page->p_next) {
        if ((p_page->stat & 1) == 0) {
            return PF_NULL;
        }
        if (p_page->sector <= sector && p_page->sector + p_page->size - 1 >= sector) {
            p_page->p_buf = &p_page->buffer[(sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector];
            return p_page;
        }
    }
    return PF_NULL;
}

#pragma dont_inline reset

#pragma dont_inline on
pf_bool PFCACHE_SearchForFreePage(PF_CACHE_PAGE* p_head, PF_CACHE_PAGE** pp_page) {
    PF_CACHE_PAGE* p_page;
    for (p_page = p_head->p_prev; p_page != p_head; p_page = p_page->p_prev) {
        if ((p_page->stat & 1) == 0) {
            *pp_page = p_page;
            return PF_TRUE;
        }
        if (p_page->sector != 0xFFFFFFFF) {
            *pp_page = p_page;
            return PF_FALSE;
        }
    }
    if ((p_page->stat & 1) == 0) {
        *pp_page = p_page;
        return PF_TRUE;
    }
    if (p_page->sector != 0xFFFFFFFF) {
        *pp_page = p_page;
        return PF_FALSE;
    }
    *pp_page = PF_NULL;
    return PF_FALSE;
}

#pragma dont_inline reset

#pragma dont_inline on
pf_s32 PFCACHE_FlushPageIfNeeded(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_page) {
    pf_s32 err;
    pf_u32 num_success;
    pf_u32 size;
    if (p_page != PF_NULL && (p_page->stat & 0x02) != 0 && p_page->sector != 0xFFFFFFFF) {
        if (p_page->p_mod_sbuf == PF_NULL) {
            size = p_page->size;
            err = PFDRV_lwrite(p_vol, p_page->buffer, p_page->sector, size, &num_success);
        } else {
            size = (((pf_u32)p_page->p_mod_ebuf >> p_vol->bpb.log2_bytes_per_sector) -
                ((pf_u32)p_page->p_mod_sbuf >> p_vol->bpb.log2_bytes_per_sector)) + 1;
            err = PFDRV_lwrite(p_vol, p_page->p_mod_sbuf,
                p_page->sector + ((pf_u32)(p_page->p_mod_sbuf - p_page->buffer) >> p_vol->bpb.log2_bytes_per_sector),
                size, &num_success);
        }
        if (err != 0) {
            return err;
        }
        if (num_success != size) {
            return 17;
        }
        p_page->p_mod_sbuf = NULL;
        p_page->p_mod_ebuf = NULL;
        p_page->stat &= ~2;
    }
    return 0;
}

#pragma dont_inline reset

#pragma dont_inline on
pf_s32 PFCACHE_DoAllocatePage(PF_VOLUME* p_vol, PF_CACHE_PAGE** pp_head, pf_u32 sector, PF_CACHE_PAGE** pp_page, pf_bool* p_is_hit) {
    pf_s32 err;
    *pp_page = PFCACHE_SearchForPage(p_vol, *pp_head, sector);
    if (*pp_page != PF_NULL) {
        *p_is_hit = PF_TRUE;
    } else {
        *p_is_hit = PF_FALSE;
        if (PFCACHE_SearchForFreePage(*pp_head, pp_page) == 0) {
            if (*pp_page == 0) {
                *pp_page = PF_NULL;
                return 30;
            }
            err = PFCACHE_FlushPageIfNeeded(p_vol, *pp_page);
            if (err != 0) {
                *pp_page = PF_NULL;
                return err;
            }
            (*pp_page)->p_mod_sbuf = NULL;
            (*pp_page)->p_mod_ebuf = NULL;
        }
        if (sector != 0xFFFFFFFF) {
            if (((*pp_page)->stat & 0x04) != 0) {
                (*pp_page)->sector = sector - (sector % (*pp_page)->size);
                (*pp_page)->p_buf = &(*pp_page)->buffer[(sector % (*pp_page)->size) << p_vol->bpb.log2_bytes_per_sector];
            } else {
                if (p_vol->bpb.fat_type == FAT_32 && (sector < p_vol->bpb.first_data_sector || sector >= p_vol->bpb.total_sectors)) {
                    if (sector == p_vol->bpb.fs_info_sector) {
                        (*pp_page)->size = 1;
                    }
                }
                (*pp_page)->sector = sector - (sector % (*pp_page)->size);
                (*pp_page)->p_buf = &(*pp_page)->buffer[(sector % (*pp_page)->size) << p_vol->bpb.log2_bytes_per_sector];
            }
        } else {
            (*pp_page)->sector = sector;
            (*pp_page)->p_buf = (*pp_page)->buffer;
        }
        (*pp_page)->stat |= 0x01;
    }
    {
        PF_CACHE_PAGE* p_page = *pp_page;
        if (p_page != *pp_head) {
            if (p_page == (*pp_head)->p_prev) {
                *pp_head = p_page;
            } else {
                p_page->p_prev->p_next = p_page->p_next;
                p_page->p_next->p_prev = p_page->p_prev;
                p_page->p_next = *pp_head;
                p_page->p_prev = (*pp_head)->p_prev;
                p_page->p_next->p_prev = p_page;
                p_page->p_prev->p_next = p_page;
                *pp_head = p_page;
            }
        }
    }
    return 0;
}

#pragma dont_inline reset

#pragma dont_inline on
pf_s32 PFCACHE_DoReadPage(PF_VOLUME* p_vol, PF_CACHE_PAGE** pp_head, pf_u32 sector, PF_CACHE_PAGE** pp_page, pf_bool set_sig) {
    pf_u32 num_success;
    pf_bool is_hit;
    pf_s32 err;
    err = PFCACHE_DoAllocatePage(p_vol, pp_head, sector, pp_page, &is_hit);
    if (err != 0) {
        return err;
    }
    if (!is_hit) {
        err = PFDRV_lread(p_vol, (*pp_page)->buffer, (*pp_page)->sector, (*pp_page)->size, &num_success);
        if (err != 0) {
            {
                PF_CACHE_PAGE* p_page = *pp_page;
                p_page->stat &= ~3;
                p_page->p_mod_sbuf = NULL;
                p_page->p_mod_ebuf = NULL;
                p_page->sector = 0xFFFFFFFF;
                p_page->signature = PF_NULL;
                if (p_page == *pp_head) {
                    *pp_head = p_page->p_next;
                } else if (p_page != (*pp_head)->p_prev) {
                    p_page->p_prev->p_next = p_page->p_next;
                    p_page->p_next->p_prev = p_page->p_prev;
                    p_page->p_next = *pp_head;
                    p_page->p_prev = (*pp_head)->p_prev;
                    p_page->p_next->p_prev = p_page;
                    p_page->p_prev->p_next = p_page;
                }
            }
            return err;
        }
        if (num_success != (*pp_page)->size && p_vol->bpb.total_sectors != ((*pp_page)->sector + num_success)) {
            {
                PF_CACHE_PAGE* p_page = *pp_page;
                p_page->stat &= ~3;
                p_page->p_mod_sbuf = NULL;
                p_page->p_mod_ebuf = NULL;
                p_page->sector = 0xFFFFFFFF;
                p_page->signature = PF_NULL;
                if (p_page == *pp_head) {
                    *pp_head = p_page->p_next;
                } else if (p_page != (*pp_head)->p_prev) {
                    p_page->p_prev->p_next = p_page->p_next;
                    p_page->p_next->p_prev = p_page->p_prev;
                    p_page->p_next = *pp_head;
                    p_page->p_prev = (*pp_head)->p_prev;
                    p_page->p_next->p_prev = p_page;
                    p_page->p_prev->p_next = p_page;
                }
            }
            return 17;
        }
        (*pp_page)->stat &= ~2;
        (*pp_page)->p_mod_sbuf = NULL;
        (*pp_page)->p_mod_ebuf = NULL;
        if (set_sig) {
            (*pp_page)->signature = p_vol->cache.signature;
        } else {
            (*pp_page)->signature = PF_NULL;
        }
    }
    return 0;
}

#pragma dont_inline reset

#pragma dont_inline on
pf_s32 PFCACHE_DoReadPageAndFlushIfNeeded(PF_VOLUME* p_vol, PF_CACHE_PAGE** pp_head, pf_u32 sector, PF_CACHE_PAGE** pp_page,
    pf_bool set_sig) {
    pf_u32 num_success;
    pf_bool is_hit;
    pf_s32 err;
    err = PFCACHE_DoAllocatePage(p_vol, pp_head, sector, pp_page, &is_hit);
    if (err != 0) {
        return err;
    }
    if (!is_hit) {
        err = PFDRV_lread(p_vol, (*pp_page)->buffer, (*pp_page)->sector, (*pp_page)->size, &num_success);
        if (err != 0) {
            {
                PF_CACHE_PAGE* p_page = *pp_page;
                p_page->stat &= ~3;
                p_page->p_mod_sbuf = NULL;
                p_page->p_mod_ebuf = NULL;
                p_page->sector = 0xFFFFFFFF;
                p_page->signature = PF_NULL;
                if (p_page == *pp_head) {
                    *pp_head = p_page->p_next;
                } else if (p_page != (*pp_head)->p_prev) {
                    p_page->p_prev->p_next = p_page->p_next;
                    p_page->p_next->p_prev = p_page->p_prev;
                    p_page->p_next = *pp_head;
                    p_page->p_prev = (*pp_head)->p_prev;
                    p_page->p_next->p_prev = p_page;
                    p_page->p_prev->p_next = p_page;
                }
            }
            return err;
        }
        if (num_success != (*pp_page)->size && p_vol->bpb.total_sectors != ((*pp_page)->sector + num_success)) {
            {
                PF_CACHE_PAGE* p_page = *pp_page;
                p_page->stat &= ~3;
                p_page->p_mod_sbuf = NULL;
                p_page->p_mod_ebuf = NULL;
                p_page->sector = 0xFFFFFFFF;
                p_page->signature = PF_NULL;
                if (p_page == *pp_head) {
                    *pp_head = p_page->p_next;
                } else if (p_page != (*pp_head)->p_prev) {
                    p_page->p_prev->p_next = p_page->p_next;
                    p_page->p_next->p_prev = p_page->p_prev;
                    p_page->p_next = *pp_head;
                    p_page->p_prev = (*pp_head)->p_prev;
                    p_page->p_next->p_prev = p_page;
                    p_page->p_prev->p_next = p_page;
                }
            }
            return 17;
        }
        (*pp_page)->stat &= ~2;
        (*pp_page)->p_mod_sbuf = NULL;
        (*pp_page)->p_mod_ebuf = NULL;
        if (set_sig) {
            (*pp_page)->signature = p_vol->cache.signature;
        } else {
            (*pp_page)->signature = PF_NULL;
        }
    } else if (set_sig && ((*pp_page)->stat & 0x02) != 0 && (p_vol->cache.mode & 0x02) != 0 && (*pp_page)->signature != p_vol->cache.signature) {
        err = PFCACHE_FlushPageIfNeeded(p_vol, *pp_page);
        if (err != 0) {
            *pp_page = PF_NULL;
            return err;
        }
    }
    return 0;
}

#pragma dont_inline reset

#pragma dont_inline on
pf_s32 PFCACHE_DoReadNumSector(PF_VOLUME* p_vol, PF_CACHE_PAGE** pp_head, pf_u8* p_buf, pf_u32 sector, pf_u32 num_sector,
    pf_u32* p_num_success) {
    PF_CACHE_PAGE* p_page;
    pf_s32 err;
    pf_u32 num_rest_sector;
    pf_u32 num_success_sector;
    *p_num_success = 0;
    err = PFDRV_lread(p_vol, p_buf, sector, num_sector, p_num_success);
    if (err != 0) {
        return err;
    }
    p_page = PF_NULL;
    num_rest_sector = *p_num_success;
    num_success_sector = *p_num_success;
    do {
        if (p_page == PF_NULL) {
            p_page = *pp_head;
        } else {
            p_page = p_page->p_next;
            if (p_page == *pp_head) {
                p_page = PF_NULL;
                goto found_page;
            }
        }
        for (; (p_page->stat & 1) != 0; p_page = p_page->p_next) {
            if (p_page->sector != 0xFFFFFFFF) {
                p_page->p_buf = p_page->buffer;
                goto found_page;
            }
        }
        p_page = PF_NULL;
    found_page:
        if (p_page != PF_NULL && p_page->sector != 0xFFFFFFFF) {
            if (p_page->sector <= sector && p_page->sector + p_page->size >= sector + num_success_sector) {
                pf_memcpy(p_buf, &p_page->buffer[(sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector],
                    num_success_sector << p_vol->bpb.log2_bytes_per_sector);
                num_rest_sector -= num_success_sector;
            } else if (p_page->sector >= sector && p_page->sector + p_page->size <= sector + num_success_sector) {
                pf_memcpy(&p_buf[(p_page->sector - sector) << p_vol->bpb.log2_bytes_per_sector], p_page->buffer,
                    p_page->size << p_vol->bpb.log2_bytes_per_sector);
                num_rest_sector -= p_page->size;
            } else if (p_page->sector > sector && p_page->sector < sector + num_success_sector &&
                p_page->sector + p_page->size >= sector + num_success_sector) {
                pf_memcpy(&p_buf[(p_page->sector - sector) << p_vol->bpb.log2_bytes_per_sector], p_page->buffer,
                    (p_page->size - (p_page->sector + p_page->size - (sector + num_success_sector))) << p_vol->bpb.log2_bytes_per_sector);
                num_rest_sector -= p_page->size - ((p_page->sector + p_page->size) - (sector + num_success_sector));
            } else if (p_page->sector < sector && (p_page->sector + p_page->size) > sector &&
                (p_page->sector + p_page->size) <= (sector + num_success_sector)) {
                pf_memcpy(p_buf, &p_page->buffer[(sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector],
                    (p_page->size - (sector - p_page->sector)) << p_vol->bpb.log2_bytes_per_sector);
                num_rest_sector -= p_page->size - (sector - p_page->sector);
            }
        }
    } while (p_page != PF_NULL && num_rest_sector != 0);
    if (*p_num_success != num_sector && p_vol->bpb.total_sectors != (sector + *p_num_success)) {
        return 17;
    }
    return 0;
}

#pragma dont_inline reset

#pragma dont_inline on
pf_s32 PFCACHE_DoWritePage(PF_VOLUME* p_vol, PF_CACHE_PAGE** pp_head, PF_CACHE_PAGE* p_page, pf_bool set_sig) {
    pf_s32 err;
    if (p_page != *pp_head) {
        if (p_page == (*pp_head)->p_prev) {
            *pp_head = p_page;
        } else {
            p_page->p_prev->p_next = p_page->p_next;
            p_page->p_next->p_prev = p_page->p_prev;
            p_page->p_next = *pp_head;
            p_page->p_prev = (*pp_head)->p_prev;
            p_page->p_next->p_prev = p_page;
            p_page->p_prev->p_next = p_page;
            *pp_head = p_page;
        }
    }
    p_page->stat |= 2;
    if (p_page->p_mod_sbuf == PF_NULL) {
        p_page->p_mod_sbuf = p_page->p_buf;
        p_page->p_mod_ebuf = p_page->p_buf;
    } else if (p_page->p_buf < p_page->p_mod_sbuf) {
        p_page->p_mod_sbuf = p_page->p_buf;
    } else if (p_page->p_buf > p_page->p_mod_ebuf) {
        p_page->p_mod_ebuf = p_page->p_buf;
    }
    if (set_sig) {
        p_page->signature = p_vol->cache.signature;
    } else {
        p_page->signature = PF_NULL;
    }
    if ((p_vol->cache.mode & 0x01) != 0 || ((p_vol->cache.mode & 0x04) != 0 && (p_page->stat & 0x04) != 0)) {
        err = PFCACHE_FlushPageIfNeeded(p_vol, p_page);
        if (err != 0) {
            return err;
        }
    }
    return 0;
}

#pragma dont_inline reset

#pragma dont_inline on
pf_s32 PFCACHE_DoWriteSector(PF_VOLUME* p_vol, PF_CACHE_PAGE** pp_head, const pf_u8* p_buf, pf_u32 sector) {
    PF_CACHE_PAGE* p_page;
    pf_u32 num_success;
    pf_s32 err;
    p_page = PFCACHE_SearchForPage(p_vol, *pp_head, sector);
    if (p_page != PF_NULL) {
        pf_memcpy(p_page->p_buf, (pf_u8*)p_buf, p_vol->bpb.bytes_per_sector);
        p_page->stat |= 2;
        if (p_page->p_mod_sbuf == PF_NULL) {
            p_page->p_mod_sbuf = p_page->p_buf;
            p_page->p_mod_ebuf = p_page->p_buf;
        } else if (p_page->p_buf < p_page->p_mod_sbuf) {
            p_page->p_mod_sbuf = p_page->p_buf;
        } else if (p_page->p_buf > p_page->p_mod_ebuf) {
            p_page->p_mod_ebuf = p_page->p_buf;
        }
        err = PFCACHE_FlushPageIfNeeded(p_vol, p_page);
        if (err != 0) {
            return err;
        }
    } else {
        err = PFDRV_lwrite(p_vol, p_buf, sector, 1, &num_success);
        if (err != 0) {
            return err;
        }
        if (num_success != 1) {
            return 17;
        }
    }
    return 0;
}

#pragma dont_inline reset

#pragma dont_inline on
pf_s32 PFCACHE_DoWriteNumSectorAndFreeIfNeeded(PF_VOLUME* p_vol, PF_CACHE_PAGE** pp_head, const pf_u8* p_buf, pf_u32 sector,
    pf_u32 num_sector, pf_u32* p_num_success) {
    PF_CACHE_PAGE* p_page = PF_NULL;
    pf_s32 err;
    pf_u32 num_rest_sector = num_sector;
    pf_u8* p_sbuf;
    pf_u8* p_ebuf;
    pf_u32 num_overlap;
    pf_u32 last_sector;
    *p_num_success = 0;
    do {
        if (p_page == PF_NULL) {
            p_page = *pp_head;
        } else {
            p_page = p_page->p_next;
            if (p_page == *pp_head) {
                p_page = PF_NULL;
                goto found_page;
            }
        }
        for (; (p_page->stat & 1) != 0; p_page = p_page->p_next) {
            if (p_page->sector != 0xFFFFFFFF) {
                p_page->p_buf = p_page->buffer;
                goto found_page;
            }
        }
        p_page = PF_NULL;
    found_page:
        if (p_page != PF_NULL && p_page->sector != 0xFFFFFFFF) {
            if (p_page->sector <= sector && (p_page->sector + p_page->size) >= (sector + num_sector)) {
                pf_memcpy(&p_page->buffer[(sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector], (pf_u8*)p_buf,
                    num_sector << p_vol->bpb.log2_bytes_per_sector);
                *p_num_success += num_rest_sector;
                num_rest_sector = 0;
                p_page->stat |= 2;
                p_sbuf = &p_page->buffer[(sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector];
                p_ebuf = &(&p_page->buffer[(sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector])[(num_sector - 1)
                    << p_vol->bpb.log2_bytes_per_sector];
                if (p_page->p_mod_sbuf == NULL) {
                    p_page->p_mod_sbuf = p_sbuf;
                    p_page->p_mod_ebuf = p_ebuf;
                } else if (p_sbuf < p_page->p_mod_sbuf) {
                    p_page->p_mod_sbuf = p_sbuf;
                } else if (p_page->p_mod_ebuf < p_ebuf) {
                    p_page->p_mod_ebuf = p_ebuf;
                }
            } else if (p_page->sector >= sector && (p_page->sector + p_page->size) <= (sector + num_sector)) {
                pf_memcpy(p_page->buffer, (pf_u8*)&p_buf[(p_page->sector - sector) << p_vol->bpb.log2_bytes_per_sector],
                    p_page->size << p_vol->bpb.log2_bytes_per_sector);
                num_rest_sector -= p_page->size;
                *p_num_success += p_page->size;
                p_page->stat |= 2;
                p_page->p_mod_sbuf = p_page->buffer;
                p_page->p_mod_ebuf = &p_page->buffer[(p_page->size - 1) << p_vol->bpb.log2_bytes_per_sector];
            } else if (p_page->sector > sector && p_page->sector < (sector + num_sector) &&
                (p_page->sector + p_page->size) >= (sector + num_sector)) {
                pf_memcpy(p_page->buffer, (pf_u8*)&p_buf[(p_page->sector - sector) << p_vol->bpb.log2_bytes_per_sector],
                    (sector + num_sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector);
                num_overlap = sector + num_sector - p_page->sector;
                last_sector = p_page->sector + num_overlap - 1;
                *p_num_success += num_overlap;
                num_rest_sector -= num_overlap;
                p_page->stat |= 2;
                p_ebuf = &p_page->buffer[(last_sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector];
                p_page->p_mod_sbuf = p_page->buffer;
                if (p_page->p_mod_ebuf == NULL || p_page->p_mod_ebuf < p_ebuf) {
                    p_page->p_mod_ebuf = p_ebuf;
                }
            } else if (p_page->sector < sector && (p_page->sector + p_page->size) > sector &&
                (p_page->sector + p_page->size) <= (sector + num_sector)) {
                pf_memcpy(&p_page->buffer[(sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector], (pf_u8*)p_buf,
                    (p_page->size - (sector - p_page->sector)) << p_vol->bpb.log2_bytes_per_sector);
                num_rest_sector -= p_page->size - (sector - p_page->sector);
                *p_num_success += p_page->size - (sector - p_page->sector);
                p_page->stat |= 2;
                p_sbuf = &p_page->buffer[(p_page->size - (sector - p_page->sector) - 1) << p_vol->bpb.log2_bytes_per_sector];
                if (p_page->p_mod_sbuf == NULL || p_sbuf < p_page->p_mod_sbuf) {
                    p_page->p_mod_sbuf = p_sbuf;
                }
                p_page->p_mod_ebuf = &p_page->buffer[(p_page->size - 1) << p_vol->bpb.log2_bytes_per_sector];
            }
        }
    } while (p_page != PF_NULL && num_rest_sector != 0);
    if (num_rest_sector != 0) {
        err = PFDRV_lwrite(p_vol, p_buf, sector, num_sector, p_num_success);
        if (err != 0) {
            return err;
        }
    }
    return 0;
}

#pragma dont_inline reset

#pragma dont_inline on
pf_s32 PFCACHE_DoFlushCache(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_head) {
    PF_CACHE_PAGE* p_page;
    pf_s32 err;
    pf_s32 first_err;
    first_err = 0;
    p_page = p_head;
    if ((p_page->stat & 0x01) == 0) {
        return 0;
    }
    if ((p_vol->cache.mode & 1) != 0 || ((p_vol->cache.mode & 4) != 0 && (p_page->stat & 4) != 0)) {
        return 0;
    }
    do {
        if ((p_page->stat & 0x01) == 0) {
            break;
        }
        err = PFCACHE_FlushPageIfNeeded(p_vol, p_page);
        if (err != 0 && first_err == 0) {
            first_err = err;
        }
        p_page = p_page->p_next;
    } while (p_page != p_head);
    return first_err;
}

#pragma dont_inline reset

void PFCACHE_SetCache(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_cache_page, PF_CACHE_BUFFER* p_cache_buf, pf_u16 num_fat_pages, pf_u16 num_data_pages) {
    p_vol->cache.pages = p_cache_page;
    p_vol->cache.buffers = p_cache_buf;
    p_vol->cache.num_fat_pages = num_fat_pages;
    p_vol->cache.num_data_pages = num_data_pages;
}

void PFCACHE_SetFATBufferSize(PF_VOLUME* p_vol, pf_u32 size) {
    if (size != 0) {
        p_vol->cache.fat_buff_size = size;
    }
}

void PFCACHE_SetDataBufferSize(PF_VOLUME* p_vol, pf_u32 size) {
    if (size != 0) {
        p_vol->cache.data_buff_size = size;
    }
}

pf_s32 PFCACHE_InitCaches(PF_VOLUME* p_vol) {
    pf_s32 err;
    p_vol->cache.mode &= ~0x01;
    p_vol->cache.mode |= 0x02;
    p_vol->cache.mode &= ~0x04;
    pf_memset(p_vol->cache.buffers, 0, (p_vol->cache.num_fat_pages + p_vol->cache.num_data_pages) << 9);
    err = PFCACHE_InitPageList(p_vol, &p_vol->cache.p_current_fat, p_vol->cache.pages, p_vol->cache.buffers, p_vol->cache.num_fat_pages,
        p_vol->cache.fat_buff_size, PF_TRUE);
    if (err != 0) {
        return err;
    }
    err = PFCACHE_InitPageList(p_vol, &p_vol->cache.p_current_data, &p_vol->cache.pages[p_vol->cache.num_fat_pages],
        (PF_CACHE_BUFFER*)p_vol->cache.buffers[p_vol->cache.num_fat_pages], p_vol->cache.num_data_pages,
        p_vol->cache.data_buff_size, PF_FALSE);
    if (err != 0) {
        return err;
    }
    return 0;
}

pf_s32 PFCACHE_SetWriteThroughMode(PF_VOLUME* p_vol) {
    pf_s32 err = PFCACHE_FlushAllCaches(p_vol);
    if (err != 0) {
        return err;
    }
    p_vol->cache.mode |= 1;
    return 0;
}

pf_s32 PFCACHE_SetWriteBackMode(PF_VOLUME* p_vol) {
    p_vol->cache.mode &= ~1;
    return 0;
}

pf_s32 PFCACHE_AllocateFATPage(PF_VOLUME* p_vol, pf_u32 sector, PF_CACHE_PAGE** pp_page, pf_bool* p_is_hit) {
    pf_s32 err;
    if (p_vol->cache.p_current_fat == 0) {
        p_vol->cache.pages->buffer = *p_vol->cache.buffers;
        p_vol->cache.pages->p_buf = *p_vol->cache.buffers;
        *pp_page = p_vol->cache.pages;
        return 0;
    }
    err = PFCACHE_DoAllocatePage(p_vol, &p_vol->cache.p_current_fat, sector, pp_page, p_is_hit);
    if (err != 0) {
        return err;
    }
    return 0;
}

pf_s32 PFCACHE_AllocateDataPage(PF_VOLUME* p_vol, pf_u32 sector, PF_CACHE_PAGE** pp_page, pf_bool* p_is_hit) {
    pf_s32 err;
    if (p_vol->cache.p_current_data == 0) {
        p_vol->cache.pages->buffer = *p_vol->cache.buffers;
        p_vol->cache.pages->p_buf = *p_vol->cache.buffers;
        *pp_page = p_vol->cache.pages;
        return 0;
    }
    err = PFCACHE_DoAllocatePage(p_vol, &p_vol->cache.p_current_data, sector, pp_page, p_is_hit);
    if (err != 0) {
        return err;
    }
    return 0;
}

void PFCACHE_FreeFATPage(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_page) {
    if (p_vol->cache.p_current_fat != 0) {
        p_page->p_mod_sbuf = NULL;
        p_page->stat &= ~3;
        p_page->p_mod_ebuf = NULL;
        p_page->sector = 0xFFFFFFFF;
        p_page->signature = PF_NULL;
        if (p_page == p_vol->cache.p_current_fat) {
            p_vol->cache.p_current_fat = p_page->p_next;
        } else if (p_page != (p_vol->cache.p_current_fat)->p_prev) {
            p_page->p_prev->p_next = p_page->p_next;
            p_page->p_next->p_prev = p_page->p_prev;
            p_page->p_next = p_vol->cache.p_current_fat;
            p_page->p_prev = (p_vol->cache.p_current_fat)->p_prev;
            p_page->p_next->p_prev = p_page;
            p_page->p_prev->p_next = p_page;
        }
    }
}

void PFCACHE_FreeDataPage(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_page) {
    if (p_vol->cache.p_current_data != 0) {
        p_page->p_mod_sbuf = NULL;
        p_page->stat &= ~3;
        p_page->p_mod_ebuf = NULL;
        p_page->sector = 0xFFFFFFFF;
        p_page->signature = PF_NULL;
        if (p_page == p_vol->cache.p_current_data) {
            p_vol->cache.p_current_data = p_page->p_next;
        } else if (p_page != (p_vol->cache.p_current_data)->p_prev) {
            p_page->p_prev->p_next = p_page->p_next;
            p_page->p_next->p_prev = p_page->p_prev;
            p_page->p_next = p_vol->cache.p_current_data;
            p_page->p_prev = (p_vol->cache.p_current_data)->p_prev;
            p_page->p_next->p_prev = p_page;
            p_page->p_prev->p_next = p_page;
        }
    }
}

pf_s32 PFCACHE_ReadFATPage(PF_VOLUME* p_vol, pf_u32 sector, PF_CACHE_PAGE** pp_page) {
    pf_s32 err;
    err = PFCACHE_DoReadPage(p_vol, &p_vol->cache.p_current_fat, sector, pp_page, 0U);
    if (err != 0) {
        return err;
    }
    return 0;
}

pf_s32 PFCACHE_ReadDataPage(PF_VOLUME* p_vol, pf_u32 sector, PF_CACHE_PAGE** pp_page, pf_bool set_sig) {
    pf_s32 err;
    err = PFCACHE_DoReadPage(p_vol, &p_vol->cache.p_current_data, sector, pp_page, set_sig);
    if (err != 0) {
        return err;
    }
    return 0;
}

pf_s32 PFCACHE_ReadDataPageAndFlushIfNeeded(PF_VOLUME* p_vol, pf_u32 sector, PF_CACHE_PAGE** pp_page, pf_bool set_sig) {
    pf_s32 err;
    err = PFCACHE_DoReadPageAndFlushIfNeeded(p_vol, &p_vol->cache.p_current_data, sector, pp_page, set_sig);
    if (err != 0) {
        return err;
    }
    return 0;
}

pf_s32 PFCACHE_ReadDataNumSector(PF_VOLUME* p_vol, pf_u8* p_buf, pf_u32 sector, pf_u32 num_sector, pf_u32* p_num_success) {
    pf_s32 err;
    if (sector >= p_vol->bpb.total_sectors) {
        return 16;
    }
    err = PFCACHE_DoReadNumSector(p_vol, &p_vol->cache.p_current_data, p_buf, sector, num_sector, p_num_success);
    if (err != 0) {
        return err;
    }
    return 0;
}

pf_s32 PFCACHE_WriteFATPage(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_page) {
    pf_s32 err;
    err = PFCACHE_DoWritePage(p_vol, &p_vol->cache.p_current_fat, p_page, 0);
    if (err != 0) {
        return err;
    }
    return 0;
}

pf_s32 PFCACHE_WriteDataPage(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_page, pf_bool set_sig) {
    pf_s32 err;
    err = PFCACHE_DoWritePage(p_vol, &p_vol->cache.p_current_data, p_page, set_sig);
    if (err != 0) {
        return err;
    }
    return 0;
}

pf_s32 PFCACHE_WriteFATSectorAndFreeIfNeeded(PF_VOLUME* p_vol, const pf_u8* p_buf, pf_u32 sector) {
    pf_s32 err;
    if (sector >= p_vol->bpb.total_sectors) {
        return 16;
    }
    err = PFCACHE_DoWriteSector(p_vol, &p_vol->cache.p_current_fat, p_buf, sector);
    if (err != 0) {
        return err;
    }
    return 0;
}

pf_s32 PFCACHE_WriteDataNumSectorAndFreeIfNeeded(PF_VOLUME* p_vol, const pf_u8* p_buf, pf_u32 sector, pf_u32 num_sector, pf_u32* p_num_success) {
    pf_s32 err;
    if (sector >= p_vol->bpb.total_sectors) {
        return 16;
    }
    err = PFCACHE_DoWriteNumSectorAndFreeIfNeeded(p_vol, &p_vol->cache.p_current_data, p_buf, sector, num_sector, p_num_success);
    if (err != 0) {
        return err;
    }
    return 0;
}

PF_CACHE_PAGE* PFCACHE_SearchDataCache(PF_VOLUME* p_vol, pf_u32 sector) {
    return PFCACHE_SearchForPage(p_vol, p_vol->cache.p_current_data, sector);
}

pf_s32 PFCACHE_FlushFATCache(PF_VOLUME* p_vol) {
    pf_s32 err;
    err = PFCACHE_DoFlushCache(p_vol, p_vol->cache.p_current_fat);
    if (err != 0) {
        return err;
    }
    return 0;
}

pf_s32 PFCACHE_FlushDataCache(PF_VOLUME* p_vol) {
    pf_s32 err;
    err = PFCACHE_DoFlushCache(p_vol, p_vol->cache.p_current_data);
    if (err != 0) {
        return err;
    }
    return 0;
}

pf_s32 PFCACHE_FlushDataCacheSpecific(PF_VOLUME* p_vol, void* signature) {
    pf_s32 err = 0;
    PF_CACHE_PAGE* p_head;
    PF_CACHE_PAGE* p_page;
    if ((p_vol->cache.mode & 7) != 0) {
        p_head = p_vol->cache.p_current_data;
        p_page = p_head;
        if (p_page->signature == PF_NULL || p_page->signature == signature) {
            err = PFCACHE_FlushPageIfNeeded(p_vol, p_page);
            if (err != 0) {
                return err;
            }
        }
        for (p_page = p_page->p_next; p_page != p_head; p_page = p_page->p_next) {
            if (p_page->signature == PF_NULL || p_page->signature == signature) {
                err = PFCACHE_FlushPageIfNeeded(p_vol, p_page);
                if (err != 0) {
                    return err;
                }
                continue;
            }
        }
    }
    return err;
}

pf_s32 PFCACHE_FlushAllCaches(PF_VOLUME* p_vol) {
    pf_s32 err;
    err = PFCACHE_DoFlushCache(p_vol, p_vol->cache.p_current_fat);
    if (err != 0) {
        return err;
    }
    err = PFCACHE_DoFlushCache(p_vol, p_vol->cache.p_current_data);
    if (err != 0) {
        return err;
    }
    return 0;
}

void PFCACHE_FreeAllCaches(PF_VOLUME* p_vol) {
    while ((p_vol->cache.p_current_fat->stat & 0x01) != 0) {
        {
            PF_CACHE_PAGE* p_page = p_vol->cache.p_current_fat;
            if (p_vol->cache.p_current_fat != 0) {
                p_page->stat &= ~3;
                p_page->p_mod_sbuf = NULL;
                p_page->p_mod_ebuf = NULL;
                p_page->sector = 0xFFFFFFFF;
                p_page->signature = PF_NULL;
                if (p_page == p_vol->cache.p_current_fat) {
                    p_vol->cache.p_current_fat = p_page->p_next;
                } else if (p_page != (p_vol->cache.p_current_fat)->p_prev) {
                    p_page->p_prev->p_next = p_page->p_next;
                    p_page->p_next->p_prev = p_page->p_prev;
                    p_page->p_next = p_vol->cache.p_current_fat;
                    p_page->p_prev = (p_vol->cache.p_current_fat)->p_prev;
                    p_page->p_next->p_prev = p_page;
                    p_page->p_prev->p_next = p_page;
                }
            }
        }
    }
    while ((p_vol->cache.p_current_data->stat & 0x01) != 0) {
        {
            PF_CACHE_PAGE* p_page = p_vol->cache.p_current_data;
            if (p_vol->cache.p_current_data != 0) {
                p_page->stat &= ~3;
                p_page->p_mod_sbuf = NULL;
                p_page->p_mod_ebuf = NULL;
                p_page->sector = 0xFFFFFFFF;
                p_page->signature = PF_NULL;
                if (p_page == p_vol->cache.p_current_data) {
                    p_vol->cache.p_current_data = p_page->p_next;
                } else if (p_page != (p_vol->cache.p_current_data)->p_prev) {
                    p_page->p_prev->p_next = p_page->p_next;
                    p_page->p_next->p_prev = p_page->p_prev;
                    p_page->p_next = p_vol->cache.p_current_data;
                    p_page->p_prev = (p_vol->cache.p_current_data)->p_prev;
                    p_page->p_next->p_prev = p_page;
                    p_page->p_prev->p_next = p_page;
                }
            }
        }
    }
}
