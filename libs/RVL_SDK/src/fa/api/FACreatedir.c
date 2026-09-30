#include <revolution/fa.h>

extern s32 pfstub_createdir(const char* dirName, s32 mode, FADta* dta);

s32 FACreatedir(const char* dirName, s32 mode, FADta* dta) {
    s32 result = pfstub_createdir(dirName, mode, dta);
    return (-result | result) >> 31;
}
