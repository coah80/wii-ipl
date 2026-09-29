#ifndef IPL_SCENE_SETTING_AOSS_H
#define IPL_SCENE_SETTING_AOSS_H

#include <revolution/ncd/NCDTypes.h>
#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AOSSInitInput {
    u16 flags;
    u8 mode;
    u8 reserved;
    u16 ssidLength;
    u8 ssid[0x100];
    s16 options[5];
    u8 optionData[6];
    u8 status;
    u8 result[0x154];
} AOSSInitInput;

int AOSSi_Init(AOSSInitInput* input);
int AOSS_Init_old(AOSSInitInput* input);
void* AOSSi_Alloc(u32 size);
void AOSSi_Free(void* block);

#ifdef __cplusplus
}
#endif

#endif
