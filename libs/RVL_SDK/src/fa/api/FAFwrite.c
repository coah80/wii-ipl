#include <revolution/fa.h>

extern size_t pfstub_fwrite(void* buffer, size_t size, size_t count, FAFILE* stream);

size_t FAFwrite(void* buffer, size_t size, size_t count, FAFILE* stream) {
    return pfstub_fwrite(buffer, size, count, stream);
}
