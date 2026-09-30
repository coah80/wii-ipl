#include <revolution/fa.h>

extern s32 pfstub_fseek(FAFILE* stream, s32 offset, int origin);

FAError FAFseek(FAFILE* stream, s32 offset, int origin) {
    s32 error = pfstub_fseek(stream, offset, origin);
    return (-error | error) >> 31;
}
