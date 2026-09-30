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

extern s32 PFDIR_opendir(PF_API_STRING* path, FADIR** directory);
extern void* PFAPI_convertReturnValue2NULL(s32 error, void* stream);

FADIR* pf2_opendir(const char* path) {
    PF_API_STRING path_string;
    FADIR* directory;
    s32 error;

    error = PFSTR_InitStr(&path_string, (const s8*)path, 1);
    if (error == 0) {
        error = PFDIR_opendir(&path_string, &directory);
    } else {
        pf_vol_set.last_error = error;
    }
    return PFAPI_convertReturnValue2NULL(error, directory);
}
