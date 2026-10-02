#if defined(VERSION_43U)
#pragma function_align 32
#else
#pragma function_align 8
#endif

#include <TRK_Hollywood_Revolution.h>

#pragma force_active on

// clang-format off
asm DSIOResult TRKAccessFile(MessageCommandID cmd, unsigned int handle, int* count, unsigned char* buffer) {
#ifdef __MWERKS__
    nofralloc
    twi 31, r0, 0
    blr
#endif
}

#pragma function_align 8

asm DSIOResult TRKOpenFile() {
#ifdef __MWERKS__
    nofralloc
    twi 31, r0, 0
    blr
#endif
}

asm DSIOResult TRKCloseFile() {
#ifdef __MWERKS__
    nofralloc
    twi 31, r0, 0
    blr
#endif
}

asm DSIOResult TRKPositionFile() {
#ifdef __MWERKS__
    nofralloc
    twi 31, r0, 0
    blr
#endif
}
// clang-format on
