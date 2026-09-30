#include <revolution/fa/pf_stub.h>

extern void* pf2_create(const void*, u32);
extern void* pf2_fopen(const void*, const void*);
extern s32 pf2_fclose(const void*);
extern s32 pf2_fread(const void*, u32, u32, const void*);
extern s32 pf2_fwrite(const void*, u32, u32, const void*);
extern s32 pf2_fseek(const void*, u32, u32);
extern s32 pf2_remove(const void*);
extern s32 pf2_rename(const void*, const void*);
extern s32 pf2_mkdir(const void*);
extern s32 pf2_rmdir(const void*);
extern s32 pf2_chdir(const void*);
extern s32 pf2_fstat(const void*, const void*);
extern s32 pf2_chmod(const void*, u32);
extern s32 pf2_mount(s8);
extern s32 pf2_format(s8, const void*);
extern s32 pf2_buffering(s8, u32);
extern s32 pf2_ferror(const void*);
extern s32 pf2_feof(const void*);
extern s32 pf2_errnum(void);
extern s32 pf2_devinf(s8, const void*);
extern s32 pf2_setvol(s8, const void*);
extern s32 pf2_getvol(s8, const void*);
extern s32 pf2_rmvvol(s8);
extern s32 pf2_chdmod(const void*, u32);
extern s32 pf2_fconcat(const void*, const void*);
extern s32 pf2_attach(const void*, const void*);
extern s32 pf2_fsfirst(const void*, u32, const void*);
extern s32 pf2_fsnext(const void*);
extern s32 pf2_setupfsi(s8, u32);
extern s32 pf2_setclstlink(s8, u32, const void*);
extern s32 pf2_fsetclstlink(const void*, u32, const void*);
extern s32 pf2_sync(s8, u32);
extern s32 pf2_fsync(const void*);
extern s32 pf2_fappend(const void*, u32);
extern s32 pf2_settailbuf(s8, u32, const void*);
extern s32 pf2_derrnum(s8);
extern s32 pf2_fsexec(const void*, u32, s32);
extern s32 pf2_unmount(s8, u32);
extern s32 pf2_combine(const void*, const void*);
extern s32 pf2_detach(s8);
extern s32 pf2_divide(const void*, const void*, u32);
extern s32 pf2_xdivide(const void*, const void*, u32);
extern s32 pf2_fadjust(const void*);
extern s32 pf2_finfo(const void*, const void*);
extern s32 pf2_move(const void*, const void*);
extern s32 pf2_cinsert(const void*, u32, u32);
extern s32 pf2_insert(const void*, u32);
extern s32 pf2_cdelete(const void*, u32, u32);
extern s32 pf2_cut(const void*, u32);
extern s32 pf2_setvolcfg(s8, const void*);
extern s32 pf2_getvolcfg(s8, const void*);
extern s32 pf2_setcode(const void*);
extern void* pf2_opendir(const void*);
extern s32 pf2_closedir(const void*);
extern s32 pf2_readdir(const void*, const void*);
extern s32 pf2_telldir(const void*, const void*);
extern s32 pf2_seekdir(const void*, u32);
extern s32 pf2_rewinddir(const void*);
extern s32 pf2_fchdir(const void*);
extern s32 pf2_regctx(void);
extern s32 pf2_unregctx(void);
extern s32 pf2_flock(const void*, u32);
extern s32 pf2_setencode(u32);
extern s32 pf2_createdir(const void*, u32, const void*);
extern s32 pf2_iswriteprotected(s8);

void pfstub_call_function_standard(PF_STUB_MESSAGE* message) {
    switch (message->operation) {
        case 0:
            message->result.stream = pf2_create(message->object,message->value);
            break;
        case 1:
            message->result.stream = pf2_fopen(message->object,message->data);
            break;
        case 2:
            message->result.status = pf2_fclose(message->object);
            break;
        case 3:
            message->result.status = pf2_fread(message->object,message->value, message->count,message->data);
            break;
        case 4:
            message->result.status = pf2_fwrite(message->object,message->value, message->count,message->data);
            break;
        case 5:
            message->result.status = pf2_fseek(message->object,message->value, message->count);
            break;
        case 7:
            message->result.status = pf2_remove(message->object);
            break;
        case 8:
            message->result.status = pf2_rename(message->object,message->data);
            break;
        case 0x2e:
            message->result.status = pf2_move(message->object,message->data);
            break;
        case 9:
            message->result.status = pf2_mkdir(message->object);
            break;
        case 0x41:
            message->result.status = pf2_createdir(message->object,message->value, message->data);
            break;
        case 10:
            message->result.status = pf2_rmdir(message->object);
            break;
        case 0xb:
            message->result.status = pf2_chdir(message->object);
            break;
        case 0xc:
            message->result.status = pf2_fstat(message->object,message->data);
            break;
        case 0xd:
            message->result.status = pf2_chmod(message->object,message->value);
            break;
        case 0xe:
            message->result.status = pf2_mount(message->drive);
            break;
        case 0x27:
            message->result.status = pf2_unmount(message->drive,message->value);
            break;
        case 0xf:
            message->result.status = pf2_format(message->drive,message->object);
            break;
        case 0x10:
            message->result.status = pf2_buffering(message->drive,message->value);
            break;
        case 0x11:
            message->result.status = pf2_ferror(message->object);
            break;
        case 0x12:
            message->result.status = pf2_feof(message->object);
            break;
        case 0x13:
            message->result.status = pf2_errnum();
            break;
        case 0x14:
            message->result.status = pf2_devinf(message->drive,message->object);
            break;
        case 0x15:
            message->result.status = pf2_setvol(message->drive,message->object);
            break;
        case 0x16:
            message->result.status = pf2_getvol(message->drive,message->object);
            break;
        case 0x17:
            message->result.status = pf2_rmvvol(message->drive);
            break;
        case 0x18:
            message->result.status = pf2_chdmod(message->object,message->value);
            break;
        case 0x19:
            message->result.status = pf2_fconcat(message->object,message->data);
            break;
        case 0x1b:
            message->result.status = pf2_attach(message->object,message->data);
            break;
        case 0x29:
            message->result.status = pf2_detach(message->drive);
            break;
        case 0x1c:
            message->result.status = pf2_fsfirst(message->object,(u8)message->value, message->data);
            break;
        case 0x1d:
            message->result.status = pf2_fsnext(message->object);
            break;
        case 0x26:
            message->result.status = pf2_fsexec(message->object,message->value, (u8)message->drive);
            break;
        case 0x1e:
            message->result.status = pf2_setupfsi(message->drive,(s16)message->value);
            break;
        case 0x1f:
            message->result.status = pf2_setclstlink(message->drive,message->value, message->object);
            break;
        case 0x20:
            message->result.status = pf2_fsetclstlink(message->object,message->value, message->data);
            break;
        case 0x21:
            message->result.status = pf2_sync(message->drive,message->value);
            break;
        case 0x22:
            message->result.status = pf2_fsync(message->object);
            break;
        case 0x23:
            message->result.status = pf2_fappend(message->object,message->value);
            break;
        case 0x2c:
            message->result.status = pf2_fadjust(message->object);
            break;
        case 0x2d:
            message->result.status = pf2_finfo(message->object,message->data);
            break;
        case 0x24:
            message->result.status = pf2_settailbuf(message->drive,message->value, message->object);
            break;
        case 0x25:
            message->result.status = pf2_derrnum(message->drive);
            break;
        case 0x28:
            message->result.status = pf2_combine(message->object,message->data);
            break;
        case 0x2a:
            message->result.status = pf2_divide(message->object,message->data, message->value);
            break;
        case 0x2b:
            message->result.status = pf2_xdivide(message->object,message->data, message->value);
            break;
        case 0x2f:
            message->result.status = pf2_cinsert(message->object,message->value, message->count);
            break;
        case 0x30:
            message->result.status = pf2_insert(message->object,message->value);
            break;
        case 0x31:
            message->result.status = pf2_cdelete(message->object,message->value, message->count);
            break;
        case 0x32:
            message->result.status = pf2_cut(message->object,message->value);
            break;
        case 0x33:
            message->result.status = pf2_setvolcfg(message->drive,message->object);
            break;
        case 0x34:
            message->result.status = pf2_getvolcfg(message->drive,message->object);
            break;
        case 0x35:
            message->result.status = pf2_setcode(message->object);
            break;
        case 0x36:
            message->result.stream = pf2_opendir(message->object);
            break;
        case 0x37:
            message->result.status = pf2_closedir(message->object);
            break;
        case 0x38:
            message->result.status = pf2_readdir(message->object,message->data);
            break;
        case 0x39:
            message->result.status = pf2_telldir(message->object,message->data);
            break;
        case 0x3a:
            message->result.status = pf2_seekdir(message->object,message->value);
            break;
        case 0x3b:
            message->result.status = pf2_rewinddir(message->object);
            break;
        case 0x3c:
            message->result.status = pf2_fchdir(message->object);
            break;
        case 0x3d:
            message->result.status = pf2_regctx();
            break;
        case 0x3e:
            message->result.status = pf2_unregctx();
            break;
        case 0x3f:
            message->result.status = pf2_flock(message->object,message->value);
            break;
        case 0x40:
            message->result.status = pf2_setencode(message->value);
            break;
        case 0x50:
            message->result.status = pf2_iswriteprotected(message->drive);
            break;
        case 6:
            break;
        default:
            message->result.status = -1;
            break;
    }
}
