#include <private/fa/pf_system.h>
#include <private/vf/PrFILE2/fatfs/pf_entry.h>

typedef struct PFFILELOCK_SFD {
    pf_u8 descriptor[0x3c];
    PF_DIR_ENT dir_entry;
    pf_u16 lock_mode;
    pf_u16 lock_count;
    pf_u32 writer_count;
    void* owner;
    pf_s32 resource;
    OSSemaphore semaphore;
} PFFILELOCK_SFD;
typedef struct PFFILELOCK_FILE {
    pf_u32 stat;
    pf_u32 open_mode;
    PFFILELOCK_SFD* p_sfd;
} PFFILELOCK_FILE;
typedef struct PFFILELOCK_SEMAPHORE_PARAM {
    pf_u32 initial_count;
    pf_u32 max_count;
    OSSemaphore* semaphore;
} PFFILELOCK_SEMAPHORE_PARAM;
extern pf_s32 pfk_create_semaphore(PFFILELOCK_SEMAPHORE_PARAM*);
extern pf_s32 pfk_get_semaphore(pf_s32);
extern pf_s32 pfk_release_semaphore(pf_s32);
extern pf_s32 pfk_delete_semaphore(pf_s32);

void PF_InitLockFile(void) {
    pf_sys_set.flock_count = 0;
}
pf_s32 PF_LockFile(PFFILELOCK_FILE* p_file) {
    pf_s32 result = -1;
    PFFILELOCK_SEMAPHORE_PARAM param;
    if (p_file->p_sfd->lock_count == 0 && p_file->p_sfd->resource == 0) {
        if (pf_sys_set.flock_count < -1U) {
            param.initial_count = 1;
            param.max_count = 1;
            param.semaphore = &p_file->p_sfd->semaphore;
            p_file->p_sfd->resource = pfk_create_semaphore(&param);
            result = 0;
            ++pf_sys_set.flock_count;
        } else result = -1;
    }
    pfk_get_semaphore(p_file->p_sfd->resource);
    return result;
}
pf_s32 PF_UnLockFile(PFFILELOCK_FILE* p_file) {
    pfk_release_semaphore(p_file->p_sfd->resource);
    if (p_file->p_sfd->lock_count == 0 && p_file->p_sfd->writer_count == 0 && pf_sys_set.flock_count != 0) {
        pfk_delete_semaphore(p_file->p_sfd->resource);
        p_file->p_sfd->resource = 0;
        --pf_sys_set.flock_count;
    }
    return 0;
}
