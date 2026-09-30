#include <revolution/fa.h>

typedef struct PF_API_STRING {
    const s8* head;
    const s8* tail;
    const s8* current;
    u32 code_mode;
} PF_API_STRING;

typedef struct PF_API_VOLUME_SET {
    u8 reserved[0x40];
    s32 last_error;
} PF_API_VOLUME_SET;

extern PF_API_VOLUME_SET pf_vol_set;
extern s32 PFSTR_InitStr(PF_API_STRING* string, const s8* text, u32 mode);
extern s32 PFAPI_convertReturnValue(s32 error);

extern s32 PFFILE_cdelete(PF_API_STRING* path, u32 position, u32 count, u32* completed);

u32 pf2_w_cdelete(const u16* path, u32 position, u32 count) {
    PF_API_STRING path_string;
    u32 completed = 0;
    s32 error;

    error = PFSTR_InitStr(&path_string, (const s8*)path, 2);
    if (error == 0) {
        error = PFFILE_cdelete(&path_string, position, count, &completed);
    } else {
        pf_vol_set.last_error = error;
    }
    return completed;
}
