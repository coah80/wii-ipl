#ifndef PRIVATE_VI_H
#define PRIVATE_VI_H

#include <revolution/vi.h>

#ifdef __cplusplus
extern "C" {
#endif

void __VISetRGBModeImm();
#ifdef VI_MATCHING_SOURCE
BOOL __VIResetRFIdle();
BOOL __VIResetSIIdle();
#else
void __VIResetRFIdle();
void __VIResetSIIdle();
#endif

void __VIGetCurrentPosition(s16* x, s16* y);

void __VIInit(VITVMode mode);
void __VIInit3in1(VITVMode mode);

#ifdef __cplusplus
}
#endif

#endif  // PRIVATE_VI_H
