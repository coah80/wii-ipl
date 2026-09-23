#include <revolution/fa.h>

extern s32 pfstub_finfo(FAFILE* stream, FAFileInfo* info);

FAError FAFinfo(FAFILE* stream, FAFileInfo* info) {
    s32 error = pfstub_finfo(stream, info);
    return (-error | error) >> 31;
}
