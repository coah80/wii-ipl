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

extern s32 PFVOL_setvol(s8 drive, PF_API_STRING* label);

s32 pf2_setvol(s8 drive, const char* label) {
    PF_API_STRING label_string;
    s32 error = PFSTR_InitStr(&label_string, (const s8*)label, 1);
    if (error == 0) {
        error = PFVOL_setvol(drive, &label_string);
    } else {
        pf_vol_set.last_error = error;
    }
    return PFAPI_convertReturnValue(error);
}
