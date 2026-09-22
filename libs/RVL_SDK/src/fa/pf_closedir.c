typedef int s32;

extern s32 PFDIR_closedir(void* dir);
extern s32 PFAPI_convertReturnValue(s32 err);

s32 pf2_closedir(void* dir) {
    s32 err = PFDIR_closedir(dir);
    err = PFAPI_convertReturnValue(err);
    return err;
}
