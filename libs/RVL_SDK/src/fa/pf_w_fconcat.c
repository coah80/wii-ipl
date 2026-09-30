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

extern s32 PFFILE_combine(PF_API_STRING* source, PF_API_STRING* destination);

s32 pf2_w_fconcat(const u16* source, const u16* destination) {
    PF_API_STRING source_string;
    PF_API_STRING destination_string;
    s32 error;

    error = PFSTR_InitStr(&source_string, (const s8*)source, 2);
    error |= PFSTR_InitStr(&destination_string, (const s8*)destination, 2);
    if (error == 0) {
        error = PFFILE_combine(&source_string, &destination_string);
    } else {
        pf_vol_set.last_error = error;
    }
    return PFAPI_convertReturnValue(error);
}
