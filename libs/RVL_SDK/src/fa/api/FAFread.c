#include <revolution/fa.h>

extern size_t pfstub_fread(void* buffer, size_t size, size_t count, FAFILE* stream);

size_t FAFread(void* buffer, size_t size, size_t count, FAFILE* stream) {
    return pfstub_fread(buffer, size, count, stream);
}
