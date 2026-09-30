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

extern s32 PFFILE_fopen(PF_API_STRING* path, s32 mode, FAFILE** file);
extern void* PFAPI_convertReturnValue2NULL(s32 error, void* stream);

FAFILE* pf2_w_create(const u16* path) {
    PF_API_STRING path_string;
    FAFILE* file;
    s32 error;

    error = PFSTR_InitStr(&path_string, (const s8*)path, 2);
    if (error == 0) {
        error = PFFILE_fopen(&path_string, 25, &file);
    } else {
        pf_vol_set.last_error = error;
    }
    return PFAPI_convertReturnValue2NULL(error, file);
}
