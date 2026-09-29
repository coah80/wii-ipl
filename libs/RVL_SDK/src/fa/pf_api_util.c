#include <revolution/fa/types.h>
#include <revolution/types.h>

static s32 pf_error_to_api_error[] = {FA_ERR_SUCCESS,  FA_ERR_EINVAL,   FA_ERR_EINVAL,   FA_ERR_ENOENT, FA_ERR_EBUSY,   FA_ERR_ENOTEMPTY, FA_ERR_ENOSPC,
                                      FA_ERR_ENOEXEC,  FA_ERR_EEXIST,   FA_ERR_ENOEXEC,  FA_ERR_EINVAL, FA_ERR_EWRTPROTECT, FA_ERR_ENOSYS,    FA_ERR_ENOEXEC,
                                      FA_ERR_ENOEXEC,  FA_ERR_ENOEXEC,  FA_ERR_EACCES,   FA_ERR_EIO,    FA_ERR_ENOEXEC, FA_ERR_EACCES,    FA_ERR_ENOENT,
                                      FA_ERR_ENFILE,   FA_ERR_EMFILE,   FA_ERR_EISDIR,   FA_ERR_EACCES, FA_ERR_EPERM,   FA_ERR_ENOEXEC,   FA_ERR_ENOEXEC,
                                      FA_ERR_ENOEXEC,  FA_ERR_ENOEXEC,  FA_ERR_ENOMEM,   FA_ERR_EINVAL, FA_ERR_EINVAL,  FA_ERR_ENOEXEC,   FA_ERR_ENOENT,
                                      FA_ERR_ENOEXEC,  FA_ERR_ENOEXEC,  FA_ERR_EFBIG,    FA_ERR_EBADF,  FA_ERR_ENOLCK};

s32 PFAPI_ParseOpenModeString(const char* mode_str) {
    s32 open_mode = 0;
    u32 i = 0;

    if (mode_str == NULL) {
        open_mode = 10;
        return open_mode;
    }

    switch (mode_str[i++]) {
        case 'r': {
            open_mode = 2;
            break;
        }
        case 'w': {
            open_mode = 1;
            break;
        }
        case 'a': {
            open_mode = 4;
            break;
        }
        default: {
            return 0;
        }
    }

    if (mode_str[i] == 'b') {
        i++;
    }
    switch (mode_str[i++]) {
        case 0: {
            return open_mode;
        }
        case 't':
        default: {
            return 0;
        }
        case '+': {
            switch (mode_str[i]) {
                case 0: {
                    return open_mode | 8;
                }
                default: {
                    return 0;
                }
            }
        }
    }
    return 0;
}

s32 PFAPI_convertError(s32 err) {
    if (err == 0) {
        return 0;
    }
    if (err == -1) {
        return -1;
    }
    if (err > 0 && err < 0xA0) {
        return pf_error_to_api_error[err];
    }
    if (err == 0x1000) {
        err = FA_ERR_EIO;
    }
    return err;
}

s32 PFAPI_convertDriverError(s32 err) {
    if (err == 0) {
        return 0;
    }
    if (err <= 0) {
        return err;
    }
    if ((u32)err < 0xA0) {
        err = 1;
    }
    return err;
}

s32 PFAPI_convertReturnValue(s32 err) {
    if (err == 0) {
        return 0;
    }
    return -1;
}

s32 PFAPI_convertReturnValue4feof(s32 err) {
    if (err == 1) {
        return 1;
    }
    if (err == 0) {
        return 0;
    }
    return -1;
}

void* PFAPI_convertReturnValue2NULL(s32 err, void* p_stream) {
    void* ret;
    if (err) {
        ret = NULL;
    } else {
        ret = p_stream;
    }
    return ret;
}

s32 PFAPI_convertReturnValue4unmount(s32 err) {
    if (err == 0) {
        return 0;
    }
    if (err == 1) {
        return 1;
    }
    return -1;
}
