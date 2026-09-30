#include <revolution/fa.h>
#include <revolution/os.h>

char lbl_81690A00[] = "<< RVL_SDK - FA \trelease build: Apr 20 2010 11:20:14 (0x4199_60831) >>";
char* __FAVersion[2] = {lbl_81690A00, NULL};
s32 FAInInitializing;
s32 FAFileSysInitialized;
extern s32 FADiskInitialized;
extern s32 pdm_init_diskmanager(s32 config, void* parameter);
extern s32 pfstub_init_prfile2(s32 config, void* parameter);

FAError FAInit(int flag) {
    s32 error;
    if (FAInInitializing == 1) {
        return -1;
    }
    FAInInitializing = 1;
    if (!FADiskInitialized) {
        error = pdm_init_diskmanager(0, NULL);
        FADiskInitialized = error == 0;
        if (error != 0) {
            FAInInitializing = 0;
            return -1;
        }
    }
    if (!FAFileSysInitialized) {
        error = pfstub_init_prfile2(flag, NULL);
        FAFileSysInitialized = error == 0;
        if (error == -1) {
            FAInInitializing = 0;
            return -1;
        }
    }
    FAInInitializing = 0;
    OSRegisterVersion(__FAVersion[0]);
    return 0;
}
