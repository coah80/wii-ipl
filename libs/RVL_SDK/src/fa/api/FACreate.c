#include <revolution/fa.h>

extern FAFILE* pfstub_create(const char* fileName, int mode);

FAFILE* FACreate(const char* fileName, int mode) {
    FAFILE* result = pfstub_create(fileName, mode);
    if (result == NULL) {
        result = NULL;
    }
    return result;
}
