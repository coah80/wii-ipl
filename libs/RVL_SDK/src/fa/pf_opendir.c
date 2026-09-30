#include <revolution/fa.h>

typedef struct PFF2_STR {
    const s8* p_head;
    const s8* p_tail;
    const s8* p_current;
    u32 code_mode;
} PFF2_STR;

typedef struct PFF2_VOL_SET {
    u8 reserved[0x40];
    s32 last_error;
} PFF2_VOL_SET;

extern PFF2_VOL_SET pf_vol_set;
extern s32 PFSTR_InitStr(PFF2_STR* path, const s8* text, u32 code_mode);
extern s32 PFDIR_opendir(PFF2_STR* path, FADIR** result);
extern FAFILE* PFAPI_convertReturnValue2NULL(s32 err, FAFILE* p_stream);

FADIR* pf2_opendir(const char* path) {
    FADIR* p_dir;
    PFF2_STR path_str;
    s32 err;

    err = PFSTR_InitStr(&path_str, (const s8*)path, 1);
    if (err == 0) {
        err = PFDIR_opendir(&path_str, &p_dir);
    } else {
        pf_vol_set.last_error = err;
    }
    p_dir = PFAPI_convertReturnValue2NULL(err, p_dir);
    return p_dir;
}
