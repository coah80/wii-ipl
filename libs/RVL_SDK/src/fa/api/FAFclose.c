#include <revolution/fa.h>

extern s32 pfstub_fclose(FAFILE* stream);

FAError FAFclose(FAFILE* stream) {
    s32 error = pfstub_fclose(stream);
    return (-error | error) >> 31;
}
