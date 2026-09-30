#include <revolution/fa.h>

extern s32 pfstub_remove(const char* fileName);

FAError FARemove(const char* fileName) {
    s32 error = pfstub_remove(fileName);
    return (-error | error) >> 31;
}
