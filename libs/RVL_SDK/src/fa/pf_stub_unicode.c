#include <revolution/fa/pf_stub.h>

extern void* pf2_w_create(const void*, u32);
extern void* pf2_w_fopen(const void*, const void*);
extern s32 pf2_w_remove(const void*);
extern s32 pf2_w_rename(const void*, const void*);
extern s32 pf2_w_mkdir(const void*);
extern s32 pf2_w_rmdir(const void*);
extern s32 pf2_w_chdir(const void*);
extern s32 pf2_w_fstat(const void*, const void*);
extern s32 pf2_w_chmod(const void*, u32);
extern s32 pf2_w_chdmod(const void*, u32);
extern s32 pf2_w_fconcat(const void*, const void*);
extern s32 pf2_w_fsfirst(const void*, u32, const void*);
extern s32 pf2_w_fsnext(const void*);
extern s32 pf2_w_fsexec(const void*, u32, s32);
extern s32 pf2_w_combine(const void*, const void*);
extern s32 pf2_w_divide(const void*, const void*, u32);
extern s32 pf2_w_xdivide(const void*, const void*, u32);
extern s32 pf2_w_move(const void*, const void*);
extern s32 pf2_w_cinsert(const void*, u32, u32);
extern s32 pf2_w_insert(const void*, u32);
extern s32 pf2_w_cdelete(const void*, u32, u32);
extern s32 pf2_w_cut(const void*, u32);
extern void* pf2_w_opendir(const void*);
extern s32 pf2_w_createdir(const void*, u32, const void*);

void pfstub_call_function_unicode(PF_STUB_MESSAGE* message) {
    switch (message->operation) {
        case 100:
            message->result.stream = pf2_w_create(message->object,message->value);
            break;
        case 0x65:
            message->result.stream = pf2_w_fopen(message->object,message->data);
            break;
        case 0x66:
            message->result.status = pf2_w_remove(message->object);
            break;
        case 0x67:
            message->result.status = pf2_w_rename(message->object,message->data);
            break;
        case 0x75:
            message->result.status = pf2_w_move(message->object,message->data);
            break;
        case 0x68:
            message->result.status = pf2_w_mkdir(message->object);
            break;
        case 0x7b:
            message->result.status = pf2_w_createdir(message->object,message->value, message->data);
            break;
        case 0x69:
            message->result.status = pf2_w_rmdir(message->object);
            break;
        case 0x6a:
            message->result.status = pf2_w_chdir(message->object);
            break;
        case 0x6b:
            message->result.status = pf2_w_fstat(message->object,message->data);
            break;
        case 0x6c:
            message->result.status = pf2_w_chmod(message->object,message->value);
            break;
        case 0x6d:
            message->result.status = pf2_w_chdmod(message->object,message->value);
            break;
        case 0x6e:
            message->result.status = pf2_w_fconcat(message->object,message->data);
            break;
        case 0x6f:
            message->result.status = pf2_w_fsfirst(message->object,(u8)message->value, message->data);
            break;
        case 0x70:
            message->result.status = pf2_w_fsnext(message->object);
            break;
        case 0x71:
            message->result.status = pf2_w_fsexec(message->object,message->value, (u8)message->drive);
            break;
        case 0x72:
            message->result.status = pf2_w_combine(message->object,message->data);
            break;
        case 0x73:
            message->result.status = pf2_w_divide(message->object,message->data, message->value);
            break;
        case 0x74:
            message->result.status = pf2_w_xdivide(message->object,message->data, message->value);
            break;
        case 0x76:
            message->result.status = pf2_w_cinsert(message->object,message->value, message->count);
            break;
        case 0x77:
            message->result.status = pf2_w_insert(message->object,message->value);
            break;
        case 0x78:
            message->result.status = pf2_w_cdelete(message->object,message->value, message->count);
            break;
        case 0x79:
            message->result.status = pf2_w_cut(message->object,message->value);
            break;
        case 0x7a:
            message->result.stream = pf2_w_opendir(message->object);
            break;
        default:
            message->result.status = -1;
            break;
    }
}
