#include <revolution/fa.h>

extern s32 pfstub_fsnext(FADta* dta);

FAError FAFsnext(FADta* dta) {
    s32 error = pfstub_fsnext(dta);
    return (-error | error) >> 31;
}
