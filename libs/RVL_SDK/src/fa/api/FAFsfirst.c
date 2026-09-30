#include <revolution/fa.h>

extern s32 pfstub_fsfirst(const char* dirName, u8 attr, FADta* dta);

FAError FAFsfirst(const char* dirName, u8 attr, FADta* dta) {
    s32 error = pfstub_fsfirst(dirName, attr, dta);
    return (-error | error) >> 31;
}
