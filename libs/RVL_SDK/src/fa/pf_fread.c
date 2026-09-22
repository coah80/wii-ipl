#include <revolution/fa.h>

extern s32 PFFILE_fread(void* buffer, size_t size, size_t count, FAFILE* stream, size_t* countRead);

size_t pf2_fread(void* buffer, size_t size, size_t count, FAFILE* stream) {
    size_t countRead;
    PFFILE_fread(buffer, size, count, stream, &countRead);
    return countRead;
}
