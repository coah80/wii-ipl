#include <revolution/fa.h>

extern s32 pfstub_fstat(const char* fileName, FAFileStat* stat);

FAError FAFstat(const char* fileName, FAFileStat* stat) {
    s32 error = pfstub_fstat(fileName, stat);
    return (-error | error) >> 31;
}
