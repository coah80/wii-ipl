#include <revolution/fa.h>

extern FAFILE* pfstub_fopen(const char* fileName, const char* mode);

FAFILE* FAFopen(const char* fileName, const char* mode) {
    FAFILE* result = pfstub_fopen(fileName, mode);
    if (result == NULL) {
        result = NULL;
    }
    return result;
}
