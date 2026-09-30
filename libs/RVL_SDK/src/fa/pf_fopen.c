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
extern s32 PFAPI_ParseOpenModeString(const char* mode_str);
extern s32 PFSTR_InitStr(PFF2_STR* path, const s8* text, u32 code_mode);
extern s32 PFFILE_fopen(PFF2_STR* path, s32 mode, FAFILE** result);
extern FAFILE* PFAPI_convertReturnValue2NULL(s32 err, FAFILE* p_stream);

FAFILE* pf2_fopen(const char* path, const char* mode) {
    u32 open_mode;
    FAFILE* p_file;
    PFF2_STR path_str;
    s32 err;

    open_mode = PFAPI_ParseOpenModeString(mode);
    if (open_mode == 0) {
        pf_vol_set.last_error = 10;
        p_file = NULL;
    } else {
        err = PFSTR_InitStr(&path_str, (const s8*)path, 1);
        if (err == 0) {
            err = PFFILE_fopen(&path_str, open_mode, &p_file);
        } else {
            pf_vol_set.last_error = err;
        }
        p_file = PFAPI_convertReturnValue2NULL(err, p_file);
    }
    return p_file;
}
