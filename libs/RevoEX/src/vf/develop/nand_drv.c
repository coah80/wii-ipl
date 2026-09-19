#include <private/vf/develop/nand_drv.h>

#include <private/vf/develop/d_common.h>
#include <private/vf/develop/d_vf_sys.h>

#include <private/vf/PrFILE2/common/pf_clib.h>

#include <private/vf/PrFILE2/dskmng/pdm_dskmng.h>

#include <private/vf/PrFILE2/pr_unsorted.h>

#include <private/nand.h>
#include <revolution/nand.h>

#include <revolution/os.h>

#include <stdio.h>

static s32 nanddrv_init(PDM_DISK* p_disk);
static s32 nanddrv_mount(PDM_DISK* p_disk);
static s32 nanddrv_format(PDM_DISK* p_disk, const u8* param);
static s32 nanddrv_pread(PDM_DISK* p_disk, u8* p_buf, u32 block, u32 num_blocks, u32* p_num_success);
static s32 nanddrv_pwrite(PDM_DISK* p_disk, const u8* p_buf, u32 block, u32 num_blocks, u32* p_num_success);
static s32 nanddrv_unmount(PDM_DISK* p_disk);
static s32 nanddrv_finalize(PDM_DISK* p_disk);
static s32 nanddrv_get_disk_info(PDM_DISK* p_disk, PDM_DISK_INFO* p_disk_info);

static s32 nanddrv_physical_read(u32 num_blocks, u8* buf, u32 block, u32 bps, u32* p_num_success, PDM_DISK* p_disk);
static s32 nanddrv_physical_write(u32 num_blocks, const u8* buf, u32 block, u32 bps, u32* p_num_success, PDM_DISK* p_disk);

// clang-format off
static const PDM_FUNCTBL l_nand_func = {
    nanddrv_init,
    nanddrv_finalize,
    nanddrv_mount,
    nanddrv_unmount,
    nanddrv_format,
    nanddrv_pread,
    nanddrv_pwrite,
    nanddrv_get_disk_info
};
// clang-format on

typedef s32 (*VFi_NANDCreate)(const char*, u8, u8);
typedef s32 (*VFi_NANDOpen)(const char*, NANDFileInfo*, u8);
typedef s32 (*VFi_NANDCreateDir)(const char*, u8, u8);
typedef s32 (*VFi_NANDDelete)(const char*);

static struct {
    VFi_NANDCreate create;        // 0x00
    VFi_NANDOpen open;            // 0x04
    VFi_NANDCreateDir createDir;  // 0x08
    VFi_NANDDelete delete;        // 0x0C
} l_nandFunc[PF_DRIVE_COUNT];

int VF_nand_retry_max;
int VF_nand_sleep_msec;

#ifdef DEBUG
#define VFi_NANDPrint(...) printf(__VA_ARGS__)
#define VFi_NANDPanic(line, ...) OSPanic(__FILE__, line, __VA_ARGS__)
#else
#define VFi_NANDPrint(...)
#define VFi_NANDPanic(msg, line)
#endif  // DEBUG

static void _PrintBusyErrorSub(s32 error, const char* i_funcName) {
    if (error == NAND_RESULT_BUSY) {
        VFi_NANDPrint("## VF_NANDError NAND_RESULT_BUSY occured. %s\n", i_funcName);
        return;
    }
    if (error == NAND_RESULT_ALLOC_FAILED) {
        VFi_NANDPrint("## VF_NANDError NAND_RESULT_ALLOC_FAILED occured. %s\n", i_funcName);
        return;
    }
    if (error < NAND_RESULT_OK && error != NAND_RESULT_NOEXISTS) {
        VFi_NANDPrint("VF internal error %d --- %s %d (call from %s)\n", error, __FILE__, 175, i_funcName);
    }
}

#ifdef DEBUG
#define VFi_NANDPrintError(error) _PrintBusyErrorSub(error, __func__)
#else
#define VFi_NANDPrintError(error)
#endif  // DEBUG

static void _SleepAfewMiliSec() {
    OSSleepMilliseconds(VF_nand_sleep_msec);
}

#define VFi_NANDFunction(...)                                                                                                                        \
                                                                                                                                                     \
    s32 challenge = VF_nand_retry_max;                                                                                                               \
    s32 error = NAND_RESULT_OK;                                                                                                                      \
    while (challenge-- > 0) {                                                                                                                        \
        error = (__VA_ARGS__);                                                                                                                       \
        VFi_NANDPrintError(error);                                                                                                                   \
        if (error != NAND_RESULT_BUSY && error != NAND_RESULT_ALLOC_FAILED) {                                                                        \
            return error;                                                                                                                            \
        }                                                                                                                                            \
        _SleepAfewMiliSec();                                                                                                                         \
    }                                                                                                                                                \
    return error;

s32 VFi_NandCreate(const char* path, u8 perm, u8 attr) {
    VFi_NANDFunction(NANDCreate(path, perm, attr));
}

s32 VFi_NandPrivateCreate(const char* path, u8 perm, u8 attr) {
    VFi_NANDFunction(NANDPrivateCreate(path, perm, attr));
}

s32 VFi_NandDelete(const char* path) {
    VFi_NANDFunction(NANDDelete(path));
}

s32 VFi_NandPrivateDelete(const char* path) {
    VFi_NANDFunction(NANDPrivateDelete(path));
}

s32 VFi_NandClose(NANDFileInfo* info) {
    VFi_NANDFunction(NANDClose(info));
}

s32 VFi_NandOpen(const char* path, NANDFileInfo* info, u8 accType) {
    VFi_NANDFunction(NANDOpen(path, info, accType));
}

s32 VFi_NandPrivateOpen(const char* path, NANDFileInfo* info, u8 accType) {
    VFi_NANDFunction(NANDPrivateOpen(path, info, accType));
}

s32 VFi_NandWrite(NANDFileInfo* info, void* buf, u32 length) {
    VFi_NANDFunction(NANDWrite(info, buf, length));
}

s32 VFi_NandRead(NANDFileInfo* info, void* buf, u32 length) {
    VFi_NANDFunction(NANDRead(info, buf, length));
}

s32 VFi_NandCreateDir(const char* path, u8 perm, u8 attr) {
    VFi_NANDFunction(NANDCreateDir(path, perm, attr));
}

s32 VFi_NandPrivateCreateDir(const char* path, u8 perm, u8 attr) {
    VFi_NANDFunction(NANDPrivateCreateDir(path, perm, attr));
}

s32 VFi_NandSeek(NANDFileInfo* info, s32 offset, s32 whence) {
    VFi_NANDFunction(NANDSeek(info, offset, whence));
}

s32 VFi_NandGetLength(NANDFileInfo* info, u32* length) {
    VFi_NANDFunction(NANDGetLength(info, length));
}

static u8 _MakePermitForRVL(u8 i_perm) {
    u8 perm = 0;
    if ((i_perm & 1) != 0) {
        perm |= 0x10;
    }
    if ((i_perm & 2) != 0) {
        perm |= 0x20;
    }
    if ((i_perm & 4) != 0) {
        perm |= 4;
    }
    if ((i_perm & 8) != 0) {
        perm |= 8;
    }
    if ((i_perm & 0x10) != 0) {
        perm |= 1;
    }
    if ((i_perm & 0x20) != 0) {
        perm |= 2;
    }
    return perm;
}

s32 VFi_NandCreateSp(const char* path, u8 i_perm, u8 attr, u32 i_handleIdx) {
    u8 perm = _MakePermitForRVL(i_perm);
    if (i_handleIdx < PF_DRIVE_COUNT) {
        VFi_NANDCreate tmpCreate;
        tmpCreate = l_nandFunc[i_handleIdx].create;
        if (tmpCreate != NULL) {
            return tmpCreate(path, perm, attr);
        }
        return VFi_NandCreate(path, perm, attr);
    }
    if (i_handleIdx == -10) {
        return VFi_NandCreate(path, perm, attr);
    }
    return VFi_NandPrivateCreate(path, perm, attr);
}

s32 VFi_NandOpenSp(const char* path, void* info, u8 accType, u32 i_handleIdx) {
    NANDFileInfo* info_p = info;
    if (i_handleIdx < PF_DRIVE_COUNT) {
        VFi_NANDOpen tmpOpen = l_nandFunc[i_handleIdx].open;
        if (tmpOpen != NULL) {
            return tmpOpen(path, info_p, accType);
        }
        return VFi_NandOpen(path, info_p, accType);
    }
    if (i_handleIdx == -10) {
        return VFi_NandOpen(path, info_p, accType);
    }
    return VFi_NandPrivateOpen(path, info_p, accType);
}

s32 VFi_NandDeleteSp(const char* path, u32 i_handleIdx) {
    if (i_handleIdx < PF_DRIVE_COUNT) {
        VFi_NANDDelete tmpDelete = l_nandFunc[i_handleIdx].delete;
        if (tmpDelete != NULL) {
            return tmpDelete(path);
        }
        return VFi_NandDelete(path);
    }
    if (i_handleIdx == -10) {
        return VFi_NandDelete(path);
    }
    return VFi_NandPrivateDelete(path);
}

void VFi_NandSetNANDFuncNormal(u32 i_handleIdx) {
    if (i_handleIdx < PF_DRIVE_COUNT) {
        l_nandFunc[i_handleIdx].create = VFi_NandCreate;
        l_nandFunc[i_handleIdx].open = VFi_NandOpen;
        l_nandFunc[i_handleIdx].createDir = VFi_NandCreateDir;
        l_nandFunc[i_handleIdx].delete = VFi_NandDelete;
    }
}

void VFi_NandSetNANDFuncEx(u32 i_handleIdx) {
    if (i_handleIdx < PF_DRIVE_COUNT) {
        l_nandFunc[i_handleIdx].create = VFi_NandPrivateCreate;
        l_nandFunc[i_handleIdx].open = VFi_NandPrivateOpen;
        l_nandFunc[i_handleIdx].createDir = VFi_NandPrivateCreateDir;
        l_nandFunc[i_handleIdx].delete = VFi_NandPrivateDelete;
    }
}

static s32 _CreateNANDFileWithDir(const char* i_path_p, u8 i_perm, u32 i_handleIdx) {
    s32 nandErr = 0;
    nandErr = VFi_NandCreateSp(i_path_p, i_perm, 0, i_handleIdx);
    return (s16)nandErr;
}

static s32 A32_NANDRead(NANDFileInfo* i_fileInfo_p, void* i_buf, u32 i_size) {
    u8 work[32] ALIGN64;
    s32 NANDError = NAND_RESULT_OK;
    void* p_2nd;
    void* p_3rd;
    u32 size_1st;
    u32 size_2nd;
    u32 size_3rd;

    if ((i_size & 31) != 0) {
        VFi_NANDPrint("VF internal error [A32_NANDRead] %s %d\n", __FILE__, 1082);
        return NAND_RESULT_OK;
    }
    dCommon_DevideBuff32(i_buf, i_size, &size_1st, &p_2nd, &size_2nd, &p_3rd, &size_3rd);
    if (size_1st == 0) {
        NANDError = VFi_NandRead(i_fileInfo_p, i_buf, i_size);
        if (NANDError < NAND_RESULT_OK) {
            return NANDError;
        }
    } else {
        NANDError = VFi_NandRead(i_fileInfo_p, &work, 32);
        if (NANDError < NAND_RESULT_OK) {
            return NANDError;
        }
        VFipf_memcpy(i_buf, &work, size_1st);
        NANDError = VFi_NandSeek(i_fileInfo_p, -size_3rd, NAND_SEEK_CUR);
        if (NANDError < NAND_RESULT_OK) {
            return NANDError;
        }
        if (size_2nd != 0) {
            NANDError = VFi_NandRead(i_fileInfo_p, p_2nd, size_2nd);
            if (NANDError < NAND_RESULT_OK) {
                return NANDError;
            }
        }
        if (size_3rd != 0) {
            NANDError = VFi_NandRead(i_fileInfo_p, &work, 32);
            if (NANDError < NAND_RESULT_OK) {
                return NANDError;
            }
            VFipf_memcpy(p_3rd, &work, size_3rd);
        }
    }
    return i_size;
}

static s32 A32_NANDWrite(NANDFileInfo* i_fileInfo_p, void* i_buf, u32 i_size, PDM_DISK* p_disk) {
    u8 work[32] ALIGN64;
    s32 NANDError = NAND_RESULT_OK;
    void* p_2nd;
    void* p_3rd;
    u32 size_1st;
    u32 size_2nd;
    u32 size_3rd;
    u32 handleIdx = dCommon_getHandleIdxFromDisk(p_disk);
    VFSys_handle* handle_p = VFSysGetHandleP(handleIdx);

    (void)handle_p;  // unused

    if ((i_size & 31) != 0) {
        VFi_NANDPrint("VF internal error [A32_NANDWrite] %s %d\n", __FILE__, 1189);
        return NAND_RESULT_OK;
    }
    dCommon_DevideBuff32(i_buf, i_size, &size_1st, &p_2nd, &size_2nd, &p_3rd, &size_3rd);
    if (size_1st == 0) {
        NANDError = VFi_NandWrite(i_fileInfo_p, i_buf, i_size);
        if (NANDError < NAND_RESULT_OK) {
            return NANDError;
        }
    } else {
        VFipf_memcpy(&work, i_buf, size_1st);
        NANDError = VFi_NandWrite(i_fileInfo_p, &work, size_1st);
        if (NANDError < NAND_RESULT_OK) {
            return NANDError;
        }
        NANDError = VFi_NandWrite(i_fileInfo_p, p_2nd, size_2nd + size_3rd);
        if (NANDError < NAND_RESULT_OK) {
            return NANDError;
        }
    }
    return i_size;
}

static s32 _CreatePrfFile(u32 i_fileSize, char* i_fullpath_p, u16 i_version, u8 i_perm, u32 i_handleIdx) {
    u8 work[512] ALIGN64;
    s32 nandError = NAND_RESULT_OK;
    NANDFileInfo fileInfo;
    u32 restSize = i_fileSize;

    if ((i_fileSize & 31) != 0) {
        VFi_NANDPanic(1284, "VFF size は32の倍数にしてください。");  // "VF size should be a multiple by 32"
        return NAND_RESULT_INVALID;
    }

    nandError = _CreateNANDFileWithDir(i_fullpath_p, i_perm, i_handleIdx);
    if (nandError != NAND_RESULT_OK) {
        return (s16)nandError;
    }

    nandError = VFi_NandOpenSp(i_fullpath_p, &fileInfo, NAND_ACCESS_WRITE, i_handleIdx);
    if (nandError != NAND_RESULT_OK) {
        return (s16)nandError;
    }

    dCommon_CopyPrfFileHeader(&work, i_fileSize, i_version, 0);
    nandError = VFi_NandWrite(&fileInfo, &work, 32);
    restSize -= 0x20;

    if (nandError < NAND_RESULT_OK) {
        VFi_NandClose(&fileInfo);
        VFi_NandDeleteSp(i_fullpath_p, i_handleIdx);
        return nandError;
    }
    VFipf_memset(&work, 0, 0x200);

    for (; restSize >= 0x200; restSize -= 0x200) {
        nandError = VFi_NandWrite(&fileInfo, &work, 0x200);
        if (nandError < NAND_RESULT_OK) {
            VFi_NandClose(&fileInfo);
            VFi_NandDeleteSp(i_fullpath_p, i_handleIdx);
            return nandError;
        }
    }
    if (restSize != 0) {
        nandError = VFi_NandWrite(&fileInfo, &work, restSize);
        if (nandError < NAND_RESULT_OK) {
            VFi_NandClose(&fileInfo);
            VFi_NandDeleteSp(i_fullpath_p, i_handleIdx);
            return nandError;
        }
    }
    VFi_NandClose(&fileInfo);
    return NAND_RESULT_OK;
}

s32 NAND_CreatePrfFileEx(u32 i_fileSize, char* i_fullpath_p, u16 i_version) {
    return _CreatePrfFile(i_fileSize, i_fullpath_p, i_version, 0x3FU, -0xBU);
}

s32 VFi_NandFlushNANDFromHandleIdx(s32 i_handleIdx, BOOL i_setLastDeviceError) {
    s32 NANDError = NAND_RESULT_OK;
    VFSys_drive* drive_p = VFSysGetDriveP(i_handleIdx);
    VFSys_handle* handle_p = VFSysGetHandleP(i_handleIdx);

    if (handle_p != NULL && handle_p->device_p != NULL && handle_p->device_p->sync_mode == 1) {
        return NAND_RESULT_OK;
    }
    if (drive_p != NULL) {
        const char* sys_name_p = (const char*)drive_p->pf_filename;
        NANDFileInfo* fileInfo_p = drive_p->file_p;
        NANDError = VFi_NandClose(fileInfo_p);
        if (NANDError < NAND_RESULT_OK) {
            if (i_setLastDeviceError) {
                dCommon_setLastDeviceErrorToDisk2(i_handleIdx, NANDError);
            }
            return NANDError;
        }
        NANDError = VFi_NandOpenSp(sys_name_p, fileInfo_p, NAND_ACCESS_RW, i_handleIdx);
        if (NANDError < NAND_RESULT_OK) {
            if (i_setLastDeviceError) {
                dCommon_setLastDeviceErrorToDisk2(i_handleIdx, NANDError);
            }
            return NANDError;
        }
    }
    return NAND_RESULT_OK;
}

#ifdef __MWERKS__
extern void _savegpr_23();
extern void _restgpr_23();
static asm s32 _MountPrfFile(register PDM_DISK* p_disk, register char* i_fullpath_p) {
    nofralloc

    clrlwi r11, r1, 26
    mr r12, r1
    subfic r11, r11, -0xc0
    stwux r1, r1, r11
    mflr r0
    mr r11, r12
    stw r0, 0x4(r12)
    bl _savegpr_23
    mr r26, r3
    mr r27, r4
    bl VFSysPDMDisk2DriveP
    mr r23, r3
    mr r3, r26
    bl dCommon_getHandleIdxFromDisk
    cmpwi r23, 0x0
    mr r31, r3
    bne _MountPrfFile_L_814D7C0C
    li r3, -0x14
    b _MountPrfFile_L_814D824C
    _MountPrfFile_L_814D7C0C:
    cmplwi r3, 0x1a
    lwz r28, 0x0(r23)
    bge _MountPrfFile_L_814D7CD8
    lis r4, l_nandFunc@ha
    slwi r0, r3, 4
    addi r4, r4, l_nandFunc@l
    add r3, r4, r0
    lwz r12, 0x4(r3)
    cmpwi r12, 0x0
    beq _MountPrfFile_L_814D7C50
    mr r3, r27
    mr r4, r28
    li r5, 0x1
    mtctr r12
    bctrl
    mr r29, r3
    b _MountPrfFile_L_814D7DF0
    _MountPrfFile_L_814D7C50:
    lis r3, 0x1062
    lwz r30, VF_nand_retry_max(r0)
    addi r25, r3, 0x4dd3
    li r29, 0x0
    lis r24, 0x8000
    li r23, 0x0
    b _MountPrfFile_L_814D7CC8
    _MountPrfFile_L_814D7C6C:
    mr r3, r27
    mr r4, r28
    li r5, 0x1
    bl NANDOpen
    cmpwi r3, -0x3
    mr r29, r3
    beq _MountPrfFile_L_814D7C94
    cmpwi r3, -0x2
    beq _MountPrfFile_L_814D7C94
    b _MountPrfFile_L_814D7DF0
    _MountPrfFile_L_814D7C94:
    lwz r0, 0xf8(r24)
    lwz r6, VF_nand_sleep_msec(r0)
    srwi r0, r0, 2
    mulhwu r3, r25, r0
    srawi r0, r6, 31
    mullw r4, r23, r6
    srwi r5, r3, 6
    mulhwu r3, r5, r6
    mullw r0, r5, r0
    add r3, r3, r4
    mullw r4, r5, r6
    add r3, r3, r0
    bl OSSleepTicks
    _MountPrfFile_L_814D7CC8:
    cmpwi r30, 0x0
    subi r30, r30, 0x1
    bgt _MountPrfFile_L_814D7C6C
    b _MountPrfFile_L_814D7DF0
    _MountPrfFile_L_814D7CD8:
    addis r0, r3, 0x1
    cmplwi r0, 0xfff6
    bne _MountPrfFile_L_814D7D6C
    lis r3, 0x1062
    lwz r30, VF_nand_retry_max(r0)
    addi r25, r3, 0x4dd3
    li r29, 0x0
    lis r24, 0x8000
    li r23, 0x0
    b _MountPrfFile_L_814D7D5C
    _MountPrfFile_L_814D7D00:
    mr r3, r27
    mr r4, r28
    li r5, 0x1
    bl NANDOpen
    cmpwi r3, -0x3
    mr r29, r3
    beq _MountPrfFile_L_814D7D28
    cmpwi r3, -0x2
    beq _MountPrfFile_L_814D7D28
    b _MountPrfFile_L_814D7DF0
    _MountPrfFile_L_814D7D28:
    lwz r0, 0xf8(r24)
    lwz r6, VF_nand_sleep_msec(r0)
    srwi r0, r0, 2
    mulhwu r3, r25, r0
    srawi r0, r6, 31
    mullw r4, r23, r6
    srwi r5, r3, 6
    mulhwu r3, r5, r6
    mullw r0, r5, r0
    add r3, r3, r4
    mullw r4, r5, r6
    add r3, r3, r0
    bl OSSleepTicks
    _MountPrfFile_L_814D7D5C:
    cmpwi r30, 0x0
    subi r30, r30, 0x1
    bgt _MountPrfFile_L_814D7D00
    b _MountPrfFile_L_814D7DF0
    _MountPrfFile_L_814D7D6C:
    lis r3, 0x1062
    lwz r30, VF_nand_retry_max(r0)
    addi r23, r3, 0x4dd3
    li r29, 0x0
    lis r25, 0x8000
    li r24, 0x0
    b _MountPrfFile_L_814D7DE4
    _MountPrfFile_L_814D7D88:
    mr r3, r27
    mr r4, r28
    li r5, 0x1
    bl NANDPrivateOpen
    cmpwi r3, -0x3
    mr r29, r3
    beq _MountPrfFile_L_814D7DB0
    cmpwi r3, -0x2
    beq _MountPrfFile_L_814D7DB0
    b _MountPrfFile_L_814D7DF0
    _MountPrfFile_L_814D7DB0:
    lwz r0, 0xf8(r25)
    lwz r6, VF_nand_sleep_msec(r0)
    srwi r0, r0, 2
    mulhwu r3, r23, r0
    srawi r0, r6, 31
    mullw r4, r24, r6
    srwi r5, r3, 6
    mulhwu r3, r5, r6
    mullw r0, r5, r0
    add r3, r3, r4
    mullw r4, r5, r6
    add r3, r3, r0
    bl OSSleepTicks
    _MountPrfFile_L_814D7DE4:
    cmpwi r30, 0x0
    subi r30, r30, 0x1
    bgt _MountPrfFile_L_814D7D88
    _MountPrfFile_L_814D7DF0:
    cmpwi r29, 0x0
    bne _MountPrfFile_L_814D8038
    addi r3, r1, 0x40
    li r4, 0x0
    li r5, 0x20
    bl VFipf_memset
    mr r3, r28
    addi r4, r1, 0x40
    li r5, 0x20
    bl A32_NANDRead
    cmpwi r3, 0x0
    mr r30, r3
    bge _MountPrfFile_L_814D7EAC
    lis r3, 0x1062
    lwz r29, VF_nand_retry_max(r0)
    addi r27, r3, 0x4dd3
    lis r25, 0x8000
    li r24, 0x0
    b _MountPrfFile_L_814D7E8C
    _MountPrfFile_L_814D7E3C:
    mr r3, r28
    bl NANDClose
    cmpwi r3, -0x3
    beq _MountPrfFile_L_814D7E58
    cmpwi r3, -0x2
    beq _MountPrfFile_L_814D7E58
    b _MountPrfFile_L_814D7E98
    _MountPrfFile_L_814D7E58:
    lwz r0, 0xf8(r25)
    lwz r6, VF_nand_sleep_msec(r0)
    srwi r0, r0, 2
    mulhwu r3, r27, r0
    srawi r0, r6, 31
    mullw r4, r24, r6
    srwi r5, r3, 6
    mulhwu r3, r5, r6
    mullw r0, r5, r0
    add r3, r3, r4
    mullw r4, r5, r6
    add r3, r3, r0
    bl OSSleepTicks
    _MountPrfFile_L_814D7E8C:
    cmpwi r29, 0x0
    subi r29, r29, 0x1
    bgt _MountPrfFile_L_814D7E3C
    _MountPrfFile_L_814D7E98:
    mr r3, r26
    mr r4, r30
    bl dCommon_setLastDeviceErrorToDisk
    mr r3, r30
    b _MountPrfFile_L_814D824C
    _MountPrfFile_L_814D7EAC:
    addi r3, r1, 0x40
    bl dCommon_PrintSignature
    addi r3, r1, 0x40
    bl dCommon_IsPrfFile
    cmpwi r3, 0x0
    bne _MountPrfFile_L_814D7F40
    lis r3, 0x1062
    lwz r23, VF_nand_retry_max(r0)
    addi r26, r3, 0x4dd3
    lis r25, 0x8000
    li r24, 0x0
    b _MountPrfFile_L_814D7F2C
    _MountPrfFile_L_814D7EDC:
    mr r3, r28
    bl NANDClose
    cmpwi r3, -0x3
    beq _MountPrfFile_L_814D7EF8
    cmpwi r3, -0x2
    beq _MountPrfFile_L_814D7EF8
    b _MountPrfFile_L_814D7F38
    _MountPrfFile_L_814D7EF8:
    lwz r0, 0xf8(r25)
    lwz r6, VF_nand_sleep_msec(r0)
    srwi r0, r0, 2
    mulhwu r3, r26, r0
    srawi r0, r6, 31
    mullw r4, r24, r6
    srwi r5, r3, 6
    mulhwu r3, r5, r6
    mullw r0, r5, r0
    add r3, r3, r4
    mullw r4, r5, r6
    add r3, r3, r0
    bl OSSleepTicks
    _MountPrfFile_L_814D7F2C:
    cmpwi r23, 0x0
    subi r23, r23, 0x1
    bgt _MountPrfFile_L_814D7EDC
    _MountPrfFile_L_814D7F38:
    li r3, -0x1
    b _MountPrfFile_L_814D824C
    _MountPrfFile_L_814D7F40:
    lbz r0, 0x49(r1)
    mr r3, r26
    lbz r6, 0x4a(r1)
    lbz r5, 0x4b(r1)
    slwi r0, r0, 16
    lbz r4, 0x48(r1)
    rlwimi r5, r6, 8, 16, 23
    rlwimi r0, r4, 24, 0, 7
    or r4, r5, r0
    bl dCommon_setFileSizeToDisk
    mr r3, r26
    bl dCommon_getFileSizeFromDisk
    subi r0, r3, 0x1f
    li r3, 0x0
    srwi r4, r0, 9
    li r5, 0x1
    li r6, 0x200
    bl dCommon_GetNiceFatType
    mr r23, r3
    mr r3, r26
    mr r4, r23
    bl dCommon_setFatTypeToDisk
    mr r3, r23
    bl dCommon_GetReservedSecFromFatType
    mr r4, r3
    mr r3, r26
    bl dCommon_setResvSecNumToDisk
    mr r3, r23
    bl dCommon_GetRootEntNumFromFatType
    mr r4, r3
    mr r3, r26
    bl dCommon_setRootEntNumToDisk
    lis r3, 0x1062
    lwz r29, VF_nand_retry_max(r0)
    addi r30, r3, 0x4dd3
    lis r25, 0x8000
    li r24, 0x0
    b _MountPrfFile_L_814D8028
    _MountPrfFile_L_814D7FD8:
    mr r3, r28
    bl NANDClose
    cmpwi r3, -0x3
    beq _MountPrfFile_L_814D7FF4
    cmpwi r3, -0x2
    beq _MountPrfFile_L_814D7FF4
    b _MountPrfFile_L_814D804C
    _MountPrfFile_L_814D7FF4:
    lwz r0, 0xf8(r25)
    lwz r6, VF_nand_sleep_msec(r0)
    srwi r0, r0, 2
    mulhwu r3, r30, r0
    srawi r0, r6, 31
    mullw r4, r24, r6
    srwi r5, r3, 6
    mulhwu r3, r5, r6
    mullw r0, r5, r0
    add r3, r3, r4
    mullw r4, r5, r6
    add r3, r3, r0
    bl OSSleepTicks
    _MountPrfFile_L_814D8028:
    cmpwi r29, 0x0
    subi r29, r29, 0x1
    bgt _MountPrfFile_L_814D7FD8
    b _MountPrfFile_L_814D804C
    _MountPrfFile_L_814D8038:
    mr r3, r26
    mr r4, r29
    bl dCommon_setLastDeviceErrorToDisk
    mr r3, r29
    b _MountPrfFile_L_814D824C
    _MountPrfFile_L_814D804C:
    cmplwi r31, 0x1a
    bge _MountPrfFile_L_814D8114
    lis r3, l_nandFunc@ha
    slwi r0, r31, 4
    addi r3, r3, l_nandFunc@l
    add r3, r3, r0
    lwz r12, 0x4(r3)
    cmpwi r12, 0x0
    beq _MountPrfFile_L_814D808C
    mr r3, r27
    mr r4, r28
    li r5, 0x3
    mtctr r12
    bctrl
    mr r30, r3
    b _MountPrfFile_L_814D822C
    _MountPrfFile_L_814D808C:
    lis r3, 0x1062
    lwz r29, VF_nand_retry_max(r0)
    addi r31, r3, 0x4dd3
    li r30, 0x0
    lis r25, 0x8000
    li r24, 0x0
    b _MountPrfFile_L_814D8104
    _MountPrfFile_L_814D80A8:
    mr r3, r27
    mr r4, r28
    li r5, 0x3
    bl NANDOpen
    cmpwi r3, -0x3
    mr r30, r3
    beq _MountPrfFile_L_814D80D0
    cmpwi r3, -0x2
    beq _MountPrfFile_L_814D80D0
    b _MountPrfFile_L_814D822C
    _MountPrfFile_L_814D80D0:
    lwz r0, 0xf8(r25)
    lwz r6, VF_nand_sleep_msec(r0)
    srwi r0, r0, 2
    mulhwu r3, r31, r0
    srawi r0, r6, 31
    mullw r4, r24, r6
    srwi r5, r3, 6
    mulhwu r3, r5, r6
    mullw r0, r5, r0
    add r3, r3, r4
    mullw r4, r5, r6
    add r3, r3, r0
    bl OSSleepTicks
    _MountPrfFile_L_814D8104:
    cmpwi r29, 0x0
    subi r29, r29, 0x1
    bgt _MountPrfFile_L_814D80A8
    b _MountPrfFile_L_814D822C
    _MountPrfFile_L_814D8114:
    addis r0, r31, 0x1
    cmplwi r0, 0xfff6
    bne _MountPrfFile_L_814D81A8
    lis r3, 0x1062
    lwz r29, VF_nand_retry_max(r0)
    addi r31, r3, 0x4dd3
    li r30, 0x0
    lis r25, 0x8000
    li r24, 0x0
    b _MountPrfFile_L_814D8198
    _MountPrfFile_L_814D813C:
    mr r3, r27
    mr r4, r28
    li r5, 0x3
    bl NANDOpen
    cmpwi r3, -0x3
    mr r30, r3
    beq _MountPrfFile_L_814D8164
    cmpwi r3, -0x2
    beq _MountPrfFile_L_814D8164
    b _MountPrfFile_L_814D822C
    _MountPrfFile_L_814D8164:
    lwz r0, 0xf8(r25)
    lwz r6, VF_nand_sleep_msec(r0)
    srwi r0, r0, 2
    mulhwu r3, r31, r0
    srawi r0, r6, 31
    mullw r4, r24, r6
    srwi r5, r3, 6
    mulhwu r3, r5, r6
    mullw r0, r5, r0
    add r3, r3, r4
    mullw r4, r5, r6
    add r3, r3, r0
    bl OSSleepTicks
    _MountPrfFile_L_814D8198:
    cmpwi r29, 0x0
    subi r29, r29, 0x1
    bgt _MountPrfFile_L_814D813C
    b _MountPrfFile_L_814D822C
    _MountPrfFile_L_814D81A8:
    lis r3, 0x1062
    lwz r29, VF_nand_retry_max(r0)
    addi r24, r3, 0x4dd3
    li r30, 0x0
    lis r25, 0x8000
    li r31, 0x0
    b _MountPrfFile_L_814D8220
    _MountPrfFile_L_814D81C4:
    mr r3, r27
    mr r4, r28
    li r5, 0x3
    bl NANDPrivateOpen
    cmpwi r3, -0x3
    mr r30, r3
    beq _MountPrfFile_L_814D81EC
    cmpwi r3, -0x2
    beq _MountPrfFile_L_814D81EC
    b _MountPrfFile_L_814D822C
    _MountPrfFile_L_814D81EC:
    lwz r0, 0xf8(r25)
    lwz r6, VF_nand_sleep_msec(r0)
    srwi r0, r0, 2
    mulhwu r3, r24, r0
    srawi r0, r6, 31
    mullw r4, r31, r6
    srwi r5, r3, 6
    mulhwu r3, r5, r6
    mullw r0, r5, r0
    add r3, r3, r4
    mullw r4, r5, r6
    add r3, r3, r0
    bl OSSleepTicks
    _MountPrfFile_L_814D8220:
    cmpwi r29, 0x0
    subi r29, r29, 0x1
    bgt _MountPrfFile_L_814D81C4
    _MountPrfFile_L_814D822C:
    cmpwi r30, 0x0
    bne _MountPrfFile_L_814D823C
    li r3, 0x0
    b _MountPrfFile_L_814D824C
    _MountPrfFile_L_814D823C:
    mr r3, r26
    mr r4, r30
    bl dCommon_setLastDeviceErrorToDisk
    mr r3, r30
    _MountPrfFile_L_814D824C:
    lwz r10, 0x0(r1)
    mr r11, r10
    bl _restgpr_23
    lwz r0, 0x4(r10)
    mtlr r0
    mr r1, r10
    blr
}
#else
static s32 _MountPrfFile(PDM_DISK* p_disk, char* i_fullpath_p) {
    PR_BINHEADER header ALIGN64;
    VFSys_drive* drive_p = VFSysPDMDisk2DriveP(p_disk);
    NANDFileInfo* fileInfo_p = NULL;
    s32 nandError = NAND_RESULT_OK;
    u32 handleIdx = dCommon_getHandleIdxFromDisk(p_disk);

    if (drive_p == NULL) {
        return -20;
    }
    fileInfo_p = drive_p->file_p;
    nandError = VFi_NandOpenSp(i_fullpath_p, fileInfo_p, NAND_ACCESS_READ, handleIdx);
    if (nandError == 0) {
        VFipf_memset(&header, 0, 32);
        nandError = A32_NANDRead(fileInfo_p, &header, 32);
        if (nandError < NAND_RESULT_OK) {
            VFi_NandClose(fileInfo_p);
            dCommon_setLastDeviceErrorToDisk(p_disk, nandError);
            return nandError;
        }
        dCommon_PrintSignature(&header);
        if (!dCommon_IsPrfFile(&header)) {
            VFi_NandClose(fileInfo_p);
            return -1;
        } else {
            u32 fileSize;
            u32 dataSize;
            u32 SPU;
            u32 fatType;

            dCommon_setFileSizeToDisk(p_disk,
                                      ((header.fileSize[0] << 24) | (header.fileSize[1] << 16) | (header.fileSize[2] << 8) | (header.fileSize[3])));
            fileSize = dCommon_getFileSizeFromDisk(p_disk);
            dataSize = (fileSize - 0x20);
            SPU = ((dataSize + 1) >> 9);
            fatType = dCommon_GetNiceFatType(NULL, SPU, 1, 0x200);
            dCommon_setFatTypeToDisk(p_disk, fatType);
            dCommon_setResvSecNumToDisk(p_disk, dCommon_GetReservedSecFromFatType(fatType));
            dCommon_setRootEntNumToDisk(p_disk, dCommon_GetRootEntNumFromFatType(fatType));
            VFi_NandClose(fileInfo_p);
        }
    } else {
        dCommon_setLastDeviceErrorToDisk(p_disk, nandError);
        return nandError;
    }

    nandError = VFi_NandOpenSp(i_fullpath_p, fileInfo_p, 3U, handleIdx);
    if (nandError == NAND_RESULT_OK) {
        return 0;
    } else {
        dCommon_setLastDeviceErrorToDisk(p_disk, nandError);
        return nandError;
    }
}
#endif

static u16 _UnmountPrfFile(PDM_DISK* p_disk) {
    VFSys_drive* drive_p = VFSysPDMDisk2DriveP(p_disk);

    if (drive_p != NULL) {
        s32 nandError = NAND_RESULT_OK;
        NANDFileInfo* fileInfo_p = drive_p->file_p;
        nandError = VFi_NandClose(fileInfo_p);
        if (nandError == NAND_RESULT_OK) {
            return NAND_RESULT_OK;
        }
        dCommon_setLastDeviceErrorToDisk(p_disk, nandError);
    }
    return -1;
}

static s32 nanddrv_BuildUpFSInfoSector(u8* buf) {
    if (dCommon_MakeFsInfoSec(buf, 0x200) == 0) {
        return 0;
    }
    return -21;
}

static s32 nanddrv_BuildUpBootSector(PDM_DISK* p_disk, u8* buf, PDM_FAT_TYPE* type) {
    PDM_DISK* realDisk_p = &VFipdm_disk_set.disk[PDM_DISK_GET_NO(p_disk)];
    u32 drvSPU = realDisk_p->disk_info.total_sectors;

    dCommon_MakeBootSector(buf, type, drvSPU, 1, 0x200, 0xEBU, 0x90U, 0x3FU, dCommon_getResvSecNumFromDisk(p_disk),
                           dCommon_getRootEntNumFromDisk(p_disk), 0xF0);
    dCommon_setFatTypeToDisk(p_disk, *type);
    return 0;
}

static s32 nanddrv_init(PDM_DISK* p_disk) {
    if (p_disk == NULL) {
        return -20;
    }
    dCommon_setFatTypeToDisk(p_disk, 1);
    VFipdm_disk_notify_media_insert(p_disk);
    return 0;
}

static s32 nanddrv_mount(PDM_DISK* p_disk) {
    VFSys_drive* drive_p = NULL;
    s32 nandError = NAND_RESULT_OK;

    if (p_disk == NULL) {
        return -20;
    }
    drive_p = VFSysPDMDisk2DriveP(p_disk);
    if (drive_p == NULL) {
        return -20;
    }
    nandError = _MountPrfFile(p_disk, (char*)drive_p->pf_filename);
    if (nandError == 0) {
        return 0;
    }
    return nandError;
}

static s32 nanddrv_format(PDM_DISK* p_disk, const u8* param) {
#ifdef DEBUG
    if (p_disk == NULL) {
        return -20;
    }
    return 0;
#else
    if (p_disk) {
        return 0;
    }
    return -20;
#endif
}

static s32 nanddrv_pread(PDM_DISK* p_disk, u8* p_buf, u32 block, u32 num_blocks, u32* p_num_success) {
    *p_num_success = 0;
    if (p_disk == NULL || p_buf == NULL || num_blocks == 0 || p_num_success == NULL) {
        return -20;
    }
    return nanddrv_physical_read(num_blocks, p_buf, block, 0x200, p_num_success, p_disk);
}

static s32 nanddrv_pwrite(PDM_DISK* p_disk, const u8* p_buf, u32 block, u32 num_blocks, u32* p_num_success) {
    *p_num_success = 0;
    if (p_disk == NULL || p_buf == NULL || num_blocks == 0 || p_num_success == NULL) {
        return -20;
    }
    return nanddrv_physical_write(num_blocks, p_buf, block, 0x200, p_num_success, p_disk);
}

static s32 nanddrv_unmount(PDM_DISK* p_disk) {
    u16 nandError = NAND_RESULT_OK;
    if (p_disk == NULL) {
        return -20;
    }
    nandError = _UnmountPrfFile(p_disk);
    if (nandError == 0) {
        return 0;
    }
    return nandError;
}

static s32 nanddrv_finalize(PDM_DISK* p_disk) {
    if (p_disk == NULL) {
        return -20;
    }
    dCommon_setFatTypeToDisk(p_disk, 1);
    return 0;
}

static s32 nanddrv_get_disk_info(PDM_DISK* p_disk, PDM_DISK_INFO* p_disk_info) {
    u32 fileSize;
    u32 dataSize;

    if (p_disk == NULL || p_disk_info == NULL) {
        return -20;
    }
    fileSize = dCommon_getFileSizeFromDisk(p_disk);
    dataSize = fileSize - 0x20;
    p_disk_info->total_sectors = (dataSize + 1) >> 9;
    p_disk_info->cylinders = p_disk_info->total_sectors / 0xFF / 0x3F / 0x200;
    p_disk_info->heads = 0xFF;
    p_disk_info->sectors_per_track = 0x3F;
    p_disk_info->bytes_per_sector = 0x200;
    p_disk_info->media_attr = 0;
    p_disk_info->format_param = NULL;
    return 0;
}

s32 VFi_nanddrv_init_drv_tbl(PDM_DISK_TBL* p_disk_tbl, u32 ui_ext) {
    p_disk_tbl->p_func = (PDM_FUNCTBL*)&l_nand_func;
    p_disk_tbl->ui_ext = ui_ext;
    return 0;
}

static s32 nanddrv_physical_read(u32 num_blocks, u8* buf, u32 block, u32 bps, u32* p_num_success, PDM_DISK* p_disk) {
    u32 fileSize = dCommon_getFileSizeFromDisk(p_disk);
    u32 size;
    s32 err;
    u32 offset;
    s32 nandError = NAND_RESULT_OK;
    VFSys_drive* drive_p = VFSysPDMDisk2DriveP(p_disk);
    NANDFileInfo* fileInfo_p = NULL;

    if (drive_p == NULL) {
        return -20;
    }
    fileInfo_p = drive_p->file_p;
    if (dCommon_ReadDummyBPB(num_blocks, (u8*)buf, block, p_num_success, p_disk, &err, nanddrv_BuildUpBootSector, nanddrv_BuildUpFSInfoSector) == 0) {
        return err;
    }
    size = num_blocks * bps;
    offset = dCommon_GetPhysicalOffset(block, bps, dCommon_getResvSecNumFromDisk(p_disk));
    nandError = VFi_NandSeek(fileInfo_p, (s32)offset, NAND_SEEK_BEG);
    if (nandError == offset) {
        if ((offset + size) > fileSize) {
            return -22;
        }
        nandError = A32_NANDRead(fileInfo_p, (u8*)buf, size);
        if (nandError == size) {
            *p_num_success = num_blocks;
            return 0;
        }
    } else {
        VFi_NANDPrint("VF internal error (seek failed) %s %d\n", __FILE__, 2120);
    }
    dCommon_setLastDeviceErrorToDisk(p_disk, nandError);
    return nandError;
}

static s32 nanddrv_physical_write(u32 num_blocks, const u8* buf, u32 block, u32 bps, u32* p_num_success, PDM_DISK* p_disk) {
    u32 fileSize = dCommon_getFileSizeFromDisk(p_disk);
    u32 size;
    u32 offset;
    s32 nandError = NAND_RESULT_OK;
    VFSys_drive* drive_p = VFSysPDMDisk2DriveP(p_disk);
    NANDFileInfo* fileInfo_p = NULL;
    s32 err = 0;

    if (drive_p == NULL) {
        return -20;
    }
    fileInfo_p = drive_p->file_p;
    if (dCommon_WriteDummyBPB(num_blocks, block, p_num_success, p_disk, &err) == 0) {
        return err;
    }
    size = num_blocks * bps;
    offset = dCommon_GetPhysicalOffset(block, bps, dCommon_getResvSecNumFromDisk(p_disk));
    nandError = VFi_NandSeek(fileInfo_p, offset, NAND_SEEK_BEG);
    if (nandError == offset) {
        if ((offset + size) > fileSize) {
            return -22;
        }
        nandError = A32_NANDWrite(fileInfo_p, (u8*)buf, size, p_disk);
        if (nandError == size) {
            *p_num_success = num_blocks;
            return 0;
        }
    } else {
        VFi_NANDPrint("VF internal error (seek failed) %s %d\n", __FILE__, 2234);
    }
    dCommon_setLastDeviceErrorToDisk(p_disk, nandError);
    return nandError;
}
