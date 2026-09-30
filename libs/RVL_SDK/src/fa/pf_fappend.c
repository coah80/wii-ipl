#include <revolution/fa.h>

extern s32 PFFILE_fappend(FAFILE* file, u32 size, u32* appended_size);

u32 pf2_fappend(FAFILE* file, u32 size) {
    u32 appended_size;
    PFFILE_fappend(file, size, &appended_size);
    return appended_size;
}
