#include <revolution/fa.h>

extern s32 PFFILE_fwrite(void* buffer, size_t size, size_t count, FAFILE* stream, size_t* countWritten);

size_t pf2_fwrite(void* buffer, size_t size, size_t count, FAFILE* stream) {
    size_t countWritten;
    PFFILE_fwrite(buffer, size, count, stream, &countWritten);
    return countWritten;
}
