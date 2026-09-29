#include <private/vf/PrFILE2/fatfs/pf_dir.h>

struct PF_ENT_ITER {
    pf_u32 index;
    PF_VOLUME* p_vol;
    pf_u32 iterator_flags;
    PF_FFD ffd;
    pf_u32 file_sector_index;
    pf_u32 sector;
    pf_u16 offset;
    pf_u16 offset_mask;
    pf_u8 buf[32];
    pf_u8 log2_entries_per_sector;
};

extern pf_s32 PFENT_ITER_MoveTo(PF_ENT_ITER* iter, pf_u32 index, pf_u32 may_allocate);
extern pf_s32 PFENT_ITER_Advance(PF_ENT_ITER* iter, pf_u32 may_allocate);
extern pf_s32 PFENT_ITER_IsAtLogicalEnd(PF_ENT_ITER* iter);

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
