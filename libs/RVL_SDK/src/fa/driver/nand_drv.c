#include <private/fa/pdm.h>
#include <revolution/nand.h>
#include <revolution/types.h>
extern void* pf_memset(void*, u8, u32);
extern void* pf_memcpy(void*, const void*, u32);
extern s32 pf_strcmp(const char*, const char*);
extern char* pf_strcpy(char*, const char*);
extern u32 pf_strlen(const char*);
extern void pdm_disk_notify_media_insert(PDM_DISK*);
typedef struct NAND_DISK_INFO {
    PDM_DISK* disk;
    char path[80];
    u32 file_size;
    NANDFileInfo file;
    u32 flags;
    u32 reserved_sectors;
    s32 last_error;
} NAND_DISK_INFO;
typedef struct NAND_SEMAPHORE { s32 count; s32 maximum; void* object; } NAND_SEMAPHORE;
extern s32 pfk_create_semaphore(NAND_SEMAPHORE*);
extern void pfk_get_semaphore(s32);
extern void pfk_release_semaphore(s32);
char NAND_Org_Path[64];
NAND_DISK_INFO nanddisk_info[23];
NAND_SEMAPHORE csem;
NAND_SEMAPHORE osem;
s32 Nanddisk_Internal_Info_Init;
s32 NAND_Init;
s32 fa_nanad_semid;

static inline s32 find_disk(PDM_DISK* disk, NAND_DISK_INFO** result) {
    NAND_DISK_INFO* info;
    u16 index;
    for (index = 0; index < 23; index++) {
        info = &nanddisk_info[index];
        if (info->disk == disk) { *result = info; break; }
    }
    return index == 23 ? -22 : 0;
}
static inline s32 set_disk_error(PDM_DISK* disk, s32 error) {
    u16 index;
    for (index = 0; index < 23; index++) {
        if (nanddisk_info[index].disk == disk) { nanddisk_info[index].last_error = error; break; }
    }
    return index == 23 ? -22 : 0;
}
static inline void store_disk_error(PDM_DISK* disk, s32 error) {
    u16 index;
    for (index = 0; index < 23; index++) {
        if (nanddisk_info[index].disk == disk) { nanddisk_info[index].last_error = error; break; }
    }
}
static inline NAND_DISK_INFO* find_unmounted_disk(PDM_DISK* disk) {
    u16 index;
    NAND_DISK_INFO* info;
    for (index = 0; index < 23; index++) {
        info = &nanddisk_info[index];
        if (info->disk == disk) { if (!(info->flags & 2)) { return info; } }
    }
    for (index = 0; index < 23; index++) {
        info = &nanddisk_info[index];
        if (info->disk == 0) { if (info->path[0] != 0) { return info; } }
    }
    return 0;
}
static inline u16 read_u16(u8* buf, u32 offset) {
    if ((u32)&buf[offset] & 1) { return (buf[offset + 1] << 8) | buf[offset]; }
    return PF_SWAP_16(*(u16*)&buf[(offset + 1) & ~1]);
}
static inline void write_u16(u8* buf, u32 offset, u16 value) {
    if ((u32)&buf[offset] & 1) { buf[offset] = value; buf[offset + 1] = value >> 8; }
    else { *(u16*)&buf[(offset + 1) & ~1] = PF_SWAP_16(value); }
}
static inline void write_u32(u8* buf, u32 offset, u32 value) {
    if ((u32)&buf[offset] & 3) { buf[offset] = value; buf[offset + 1] = value >> 8; buf[offset + 2] = value >> 16; buf[offset + 3] = value >> 24; }
    else { *(u32*)&buf[offset] = PF_SWAP_32(value); }
}
static s32 fa_nanddrv_CreateNANDFileForDsk(NAND_DISK_INFO*);
static s32 fa_nanddrv_ParseCreateNANDFile(NAND_DISK_INFO*);
static s32 fa_nanddrv_VerifyBPB(u8*, u32*);
static s32 fa_nanddrv_BuildUpFSInfoSector(u8*);
static s32 fa_nanddrv_BuildUpBootSector(NAND_DISK_INFO*, u8*, PDM_FAT_TYPE*, u32);
static s32 fa_nanddrv_physical_read(u32, u8*, u32, u32, u32*, PDM_DISK*);
static s32 fa_nanddrv_physical_write(u32, const u8*, u32, u32, u32*, PDM_DISK*);

static s32 fa_nanddrv_RelateNANDFileToDsk(PDM_DISK* disk, NAND_DISK_INFO* info, s32 format) {
    s32 error = NANDChangeDir(NAND_Org_Path);
    if (error != 0) { return error; }
    if (info->flags & 4) { error = 0; }
    else { error = NANDOpen(info->path, &info->file, 3); }
    if (format) { error = -12; }
    switch (error) {
    case -12:
        error = fa_nanddrv_CreateNANDFileForDsk(info);
        if (error == 0) { info->disk = disk; }
        break;
    case 0:
        info->disk = disk;
        error = 0;
        break;
    }
    return error;
}
static s32 fa_nanddrv_CreateNANDFileForDsk(NAND_DISK_INFO* info) {
    u8 zeros[512] __attribute__((aligned(32)));
    u8 boot[512] __attribute__((aligned(32)));
    u8 fsinfo[512] __attribute__((aligned(32)));
    PDM_FAT_TYPE type;
    u32 clusters;
    s32 error;
    u32 remaining;
    error = fa_nanddrv_ParseCreateNANDFile(info);
    if (error != 0) { return error; }
    pf_memset(boot, 0, 512);
    clusters = 0;
    fa_nanddrv_BuildUpBootSector(info, boot, &type, 0);
    if (type != fa_nanddrv_VerifyBPB(boot, &clusters)) { fa_nanddrv_BuildUpBootSector(info, boot, &type, clusters); }
    error = NANDWrite(&info->file, boot, 512);
    if (error < 0) { NANDClose(&info->file); NANDDelete(info->path); return error; }
    remaining = info->file_size - 512;
    if (type == PDM_FAT_32) {
        fa_nanddrv_BuildUpFSInfoSector(fsinfo);
        error = NANDWrite(&info->file, fsinfo, 512);
        if (error < 0) { NANDClose(&info->file); NANDDelete(info->path); return error; }
        remaining -= 512;
    }
    pf_memset(zeros, 0, 512);
    for (; remaining >= 512; remaining -= 512) {
        error = NANDWrite(&info->file, zeros, 512);
        if (error < 0) { NANDClose(&info->file); NANDDelete(info->path); return error; }
    }
    if (remaining) {
        error = NANDWrite(&info->file, zeros, remaining);
        if (error < 0) { NANDClose(&info->file); NANDDelete(info->path); return error; }
    }
    return 0;
}
static s32 fa_nanddrv_ParseCreateNANDFile(NAND_DISK_INFO* info) {
    u16 length = 0;
    char* path;
    u16 position = 0;
    char name[16];
    char* next;
    s32 error;
    if (info->flags & 4) { return 0; }
    path = info->path;
    pf_memset(name, 0, 16);
    next = name;
    for (;;) {
        switch (*path) {
        case '/':
            if (length == 0) {
                if (position == 0) { error = NANDChangeDir("/"); if (error != 0) { return error; } }
                path++;
                break;
            }
            if (path[1] == 0) {
                if (length > 12) { return -20; }
                error = NANDCreate(name, 0x30, 0);
                if (error == 0 || error == -6) {
                    NANDOpen(name, &info->file, 3);
                    error = NANDChangeDir(NAND_Org_Path);
                }
                return error;
            }
            if (length > 11) { return -20; }
            if (pf_strcmp(name, "..") != 0) { error = NANDCreateDir(name, 0x30, 0); }
            else { error = 0; }
            if (error == 0 || error == -6 || error == -1) {
                error = NANDChangeDir(name);
                if (error != 0) { return error; }
                else { goto success; }
            } else {
                return error;
            }
        success:
            path++;
            pf_memset(name, 0, 16);
            next = name;
            length = 0;
            break;
        case 0:
            if (length > 12) { return -20; }
            error = NANDCreate(name, 0x30, 0);
            if (error == 0 || error == -6) {
                NANDOpen(name, &info->file, 3);
                error = NANDChangeDir(NAND_Org_Path);
            }
            return error;
        }
        *next = *path;
        length++;
        position++;
        path++;
        next++;
    }
}
static s32 fa_nanddrv_VerifyBPB(u8* buf, u32* clusters) {
    u8 sector_log = 0;
    u8 cluster_log;
    u16 value = 512;
    u32 root;
    u32 fat;
    u32 total;
    u16 root_sectors;
    PDM_FAT_TYPE result;
    u32 first;
    while ((value >>= 1) != 0) { sector_log++; }
    cluster_log = 0;
    value = 1;
    while ((value >>= 1) != 0) { cluster_log++; }
    if ((u32)&buf[17] & 1) { root = (buf[18] << 8) | buf[17]; }
    else { root = PF_SWAP_16(*(u16*)&buf[18]) << 5; }
    root_sectors = (s32)(root + 511) >> sector_log;
    fat = read_u16(buf, 22);
    if (fat == 0) { fat = PF_SWAP_32(*(u32*)&buf[36]); }
    first = root_sectors + fat * 2 + 1;
    if ((u32)&buf[19] & 1) { total = (buf[20] << 8) | buf[19]; }
    else { total = PF_SWAP_16(*(u16*)&buf[20]); }
    if (total == 0) { total = PF_SWAP_32(*(u32*)&buf[32]); }
    *clusters = total - first;
    total = (u32)(total - first) >> cluster_log;
    if (total < 4085) { return 0; }
    result = PDM_FAT_32;
    if ((u32)total < 65525) { result = PDM_FAT_16; }
    return result;
}
#pragma dont_inline on
static s32 fa_nanddrv_BuildUpFSInfoSector(u8* buf) {
    pf_memset(buf, 0, 512);
    if ((u32)&buf[0] & 3) { buf[0] = 0x52; buf[1] = 0x52; buf[2] = 0x61; buf[3] = 0x41; }
    else { *(u32*)&buf[0] = 0x52526141; }
    if ((u32)&buf[484] & 3) { buf[484] = 0x72; buf[485] = 0x72; buf[486] = 0x41; buf[487] = 0x61; }
    else { *(u32*)&buf[484] = 0x72724161; }
    if ((u32)&buf[488] & 3) { buf[488] = 0xFF; buf[489] = 0xFF; buf[490] = 0xFF; buf[491] = 0xFF; }
    else { *(u32*)&buf[488] = 0xFFFFFFFF; }
    if ((u32)&buf[492] & 3) { buf[492] = 0xFF; buf[493] = 0xFF; buf[494] = 0xFF; buf[495] = 0xFF; }
    else { *(u32*)&buf[492] = 0xFFFFFFFF; }
    if ((u32)&buf[508] & 3) { buf[508] = 0x00; buf[509] = 0x00; buf[510] = 0x55; buf[511] = 0xAA; }
    else { *(u32*)&buf[508] = 0x000055AA; }
    return 0;
}
#pragma dont_inline reset
static s32 fa_nanddrv_BuildUpBootSector(NAND_DISK_INFO* info, u8* buf, PDM_FAT_TYPE* type, u32 clusters) {
    u32 total;
    u32 fat_sectors;
    PDM_FAT_TYPE fat_type;
    total = clusters ? clusters : info->file_size >> 9;
    if (total < 4085) { fat_type = PDM_FAT_12; fat_sectors = (((total * 3) >> 1) + 511) >> 9; }
    else if (total < 65525) { fat_type = PDM_FAT_16; fat_sectors = (total * 2 + 511) >> 9; }
    else { fat_type = PDM_FAT_32; fat_sectors = (total * 4 + 511) >> 9; }
    pf_memset(buf, 0, 512);
    buf[0] = 0xEB; buf[2] = 0x90; buf[510] = 0x55; buf[511] = 0xAA;
    write_u16(buf, 24, 63);
    write_u16(buf, 26, 255);
    write_u16(buf, 11, 512);
    buf[13] = 1;
    write_u16(buf, 14, 1);
    buf[16] = 2;
    write_u16(buf, 17, 128);
    buf[21] = 0xF0;
    if (total < 65536) { write_u16(buf, 19, total); write_u32(buf, 32, 0); }
    else { write_u16(buf, 19, 0); write_u32(buf, 32, total); }
    if (fat_type == PDM_FAT_32) {
        write_u16(buf, 17, 0);
        write_u32(buf, 36, fat_sectors);
        write_u16(buf, 40, 0); write_u16(buf, 42, 0);
        write_u32(buf, 44, 2); write_u16(buf, 48, 1);
        buf[65] = 0; buf[66] = 0x29;
        if ((u32)&buf[67] & 3) { buf[67] = 0x34; buf[68] = 0x12; buf[69] = 0; buf[70] = 0; }
        else { *(u32*)&buf[76] = 0x34120000; }
    } else {
        write_u16(buf, 17, 128); write_u16(buf, 22, fat_sectors);
        buf[37] = 0; buf[38] = 0x29;
        if ((u32)&buf[39] & 3) { buf[39] = 0x34; buf[40] = 0x12; buf[41] = 0; buf[42] = 0; }
        else { *(u32*)&buf[48] = 0x34120000; }
    }
    *type = fat_type;
    return 0;
}
s32 fa_nanddrv_init(PDM_DISK* disk) {
    if (disk == 0) { return -20; }
    if (NAND_Init == 0) {
        if (NANDInit() != 0) { return -21; }
        if (NANDGetCurrentDir(NAND_Org_Path) != 0) { return -21; }
        NAND_Init++;
    }
    pdm_disk_notify_media_insert(disk);
    return 0;
}
s32 fa_nanddrv_mount(PDM_DISK* disk) {
    NAND_DISK_INFO* info;
    NAND_DISK_INFO* mounted;
    s32 error;
    pfk_get_semaphore(fa_nanad_semid);
    if (disk == 0) { pfk_release_semaphore(fa_nanad_semid); return -20; }
    if (find_disk(disk, &mounted) == 0 && (mounted->flags & 2)) { pfk_release_semaphore(fa_nanad_semid); return -21; }
    info = find_unmounted_disk(disk);
    if (info == 0) { pfk_release_semaphore(fa_nanad_semid); return -22; }
    if (info->disk != 0) { error = 0; }
    else { error = fa_nanddrv_RelateNANDFileToDsk(disk, info, 0); }
    if (error == 0) { info->flags |= 2; }
    pfk_release_semaphore(fa_nanad_semid);
    return error;
}
s32 fa_nanddrv_format(PDM_DISK* disk, const u8* param) {
    NAND_DISK_INFO* info = 0;
    s32 error;
    pfk_get_semaphore(fa_nanad_semid);
    if (disk == 0) { pfk_release_semaphore(fa_nanad_semid); return -20; }
    if (find_disk(disk, &info) != 0) { pfk_release_semaphore(fa_nanad_semid); return -20; }
    info->flags |= 4;
    error = fa_nanddrv_RelateNANDFileToDsk(disk, info, 1);
    info->flags &= ~4;
    pfk_release_semaphore(fa_nanad_semid);
    return error;
}
s32 fa_nanddrv_pread(PDM_DISK* disk, u8* buf, u32 block, u32 count, u32* success) {
    s32 error;
    pfk_get_semaphore(fa_nanad_semid);
    *success = 0;
    if (disk == 0) { pfk_release_semaphore(fa_nanad_semid); return -20; }
    if (buf == 0) { pfk_release_semaphore(fa_nanad_semid); return -20; }
    error = fa_nanddrv_physical_read(count, buf, block, 512, success, disk);
    if (error != 0) { pfk_release_semaphore(fa_nanad_semid); return error; }
    pfk_release_semaphore(fa_nanad_semid);
    return 0;
}
s32 fa_nanddrv_pwrite(PDM_DISK* disk, const u8* buf, u32 block, u32 count, u32* success) {
    s32 error;
    pfk_get_semaphore(fa_nanad_semid);
    *success = 0;
    if (disk == 0) { pfk_release_semaphore(fa_nanad_semid); return -20; }
    if (buf == 0) { pfk_release_semaphore(fa_nanad_semid); return -20; }
    error = fa_nanddrv_physical_write(count, buf, block, 512, success, disk);
    if (error != 0) { pfk_release_semaphore(fa_nanad_semid); return error; }
    pfk_release_semaphore(fa_nanad_semid);
    return 0;
}
s32 fa_nanddrv_unmount(PDM_DISK* disk) {
    NAND_DISK_INFO* info = 0;
    u32 position;
    s32 error;
    s32 result;
    pfk_get_semaphore(fa_nanad_semid);
    if (disk == 0) { pfk_release_semaphore(fa_nanad_semid); return -20; }
    error = set_disk_error(disk, 0);
    if (error == 0) {
        if (find_disk(disk, &info) != 0) { pfk_release_semaphore(fa_nanad_semid); return -20; }
        info->flags &= ~2;
        error = NANDTell(&info->file, &position);
        if (error != 0) { result = error; goto flush_done; }
        error = NANDClose(&info->file);
        if (error < 0) { result = error; goto flush_done; }
        error = NANDOpen(info->path, &info->file, 3);
        if (error < 0) { result = error; goto flush_done; }
        error = NANDSeek(&info->file, position, 0);
        result = error < 0 ? error : 0;
flush_done:
        error = result;
        if (error < 0) { set_disk_error(disk, error); pfk_release_semaphore(fa_nanad_semid); return error; }
    }
    pfk_release_semaphore(fa_nanad_semid);
    return error;
}
s32 fa_nanddrv_finalize(PDM_DISK* disk) {
    NAND_DISK_INFO* info;
    s32 error = 0;
    u16 index;
    pfk_get_semaphore(fa_nanad_semid);
    if (disk == 0) { pfk_release_semaphore(fa_nanad_semid); return -20; }
    for (index = 0; index < 23; index++) {
        info = &nanddisk_info[index];
        if (info->disk == disk) {
            error = NANDClose(&info->file);
            pf_memset(info, 0, sizeof(*info));
            break;
        }
    }
    pfk_release_semaphore(fa_nanad_semid);
    if (error != 0) { return -20; }
    return index == 23 ? -22 : 0;
}
s32 fa_nanddrv_get_disk_info(PDM_DISK* disk, PDM_DISK_INFO* disk_info) {
    NAND_DISK_INFO* info = 0;
    pfk_get_semaphore(fa_nanad_semid);
    if (disk == 0 || disk_info == 0) { pfk_release_semaphore(fa_nanad_semid); return -20; }
    if (find_disk(disk, &info) != 0) { pfk_release_semaphore(fa_nanad_semid); return -20; }
    disk_info->total_sectors = info->file_size >> 9;
    disk_info->cylinders = disk_info->total_sectors / 255 / 63 / 512;
    disk_info->heads = 255;
    disk_info->sectors_per_track = 63;
    disk_info->bytes_per_sector = 512;
    disk_info->media_attr = 0;
    disk_info->format_param = 0;
    pfk_release_semaphore(fa_nanad_semid);
    return 0;
}
const PDM_FUNCTBL fa_nand_func = {
    fa_nanddrv_init, fa_nanddrv_finalize, fa_nanddrv_mount, fa_nanddrv_unmount,
    fa_nanddrv_format, fa_nanddrv_pread, fa_nanddrv_pwrite, fa_nanddrv_get_disk_info
};
s32 fa_nanddrv_init_drv_tbl(PDM_DISK_TBL* table, u32 extension) {
    table->ui_ext = extension;
    table->p_func = (PDM_FUNCTBL*)&fa_nand_func;
    return 0;
}
s32 fa_nanddrv_NotifyNANDFile(const char* path, u32 size) {
    u16 index;
    if (pf_strlen(path) >= 76) { return -20; }
    if (Nanddisk_Internal_Info_Init == 0) {
        pf_memset(nanddisk_info, 0, sizeof(nanddisk_info));
        Nanddisk_Internal_Info_Init++;
        csem.count = 1;
        csem.maximum = 1;
        csem.object = &osem;
        fa_nanad_semid = pfk_create_semaphore(&csem);
        if (fa_nanad_semid == 0) { return -21; }
    }
    for (index = 0; index < 23; index++) {
        if (pf_strcmp(nanddisk_info[index].path, path) == 0) { return 0; }
        if (nanddisk_info[index].disk == 0) {
            pf_strcpy(nanddisk_info[index].path, path);
            nanddisk_info[index].file_size = size;
            break;
        }
    }
    return index == 23 ? -22 : 0;
}
static s32 fa_nanddrv_physical_read(u32 count, u8* buf, u32 block, u32 bps, u32* success, PDM_DISK* disk) {
    u32 file_size;
    u32 wanted;
    u32 remaining;
    s32 error;
    NAND_DISK_INFO* info = 0;
    u16 index;
    u32 offset;
    u32 position;
    u8 work[512] __attribute__((aligned(32)));
    for (index = 0; index < 23; index++) {
        if (nanddisk_info[index].disk == disk) { info = &nanddisk_info[index]; break; }
    }
    if ((index == 23 ? -22 : 0) != 0) { return -20; }
    remaining = count * bps;
    file_size = info->file_size;
    wanted = block * bps;
    if (NANDTell(&info->file, &position) != 0 || position != wanted) { error = NANDSeek(&info->file, wanted, 0); }
    else { error = 0; }
    if (error >= 0) {
        if (wanted + remaining > file_size) {
            remaining = file_size - wanted;
            offset = 0;
            while (remaining >= 512) {
                error = NANDRead(&info->file, work, 512);
                if (error < 0) { return -22; }
                pf_memcpy(buf + offset, work, error);
                offset += error; remaining -= error;
            }
            if (remaining) {
                error = NANDRead(&info->file, work, remaining);
                if (error < 0) { return -22; }
                pf_memcpy(buf + offset, work, error);
            }
            return -22;
        }
        offset = 0;
        while (remaining >= 512) {
            error = NANDRead(&info->file, work, 512);
            if (error < 0) { store_disk_error(disk, error); return error; }
            pf_memcpy(buf + offset, work, error);
            offset += error; remaining -= error;
        }
        if (remaining) {
            error = NANDRead(&info->file, work, remaining);
            if (error < 0) { store_disk_error(disk, error); return error; }
            pf_memcpy(buf + offset, work, error);
        }
        *success = count;
        return 0;
    }
    store_disk_error(disk, error);
    return error;
}
static s32 fa_nanddrv_physical_write(u32 count, const u8* buf, u32 block, u32 bps, u32* success, PDM_DISK* disk) {
    u32 file_size;
    u32 wanted;
    u32 remaining;
    s32 error;
    u16 index;
    u32 offset;
    u32 position;
    NAND_DISK_INFO* info = 0;
    u8 work[512] __attribute__((aligned(32)));
    for (index = 0; index < 23; index++) {
        if (nanddisk_info[index].disk == disk) { info = &nanddisk_info[index]; break; }
    }
    if ((index == 23 ? -22 : 0) != 0) { return -20; }
    remaining = count * bps;
    file_size = info->file_size;
    wanted = block * bps;
    if (NANDTell(&info->file, &position) != 0 || position != wanted) { error = NANDSeek(&info->file, wanted, 0); }
    else { error = 0; }
    if (error >= 0) {
        if (wanted + remaining > file_size) {
            remaining = file_size - wanted;
            offset = 0;
            while (remaining >= 512) {
                pf_memcpy(work, buf + offset, 512);
                error = NANDWrite(&info->file, work, 512);
                if (error < 0) { return -22; }
                remaining -= error; offset += error;
            }
            if (remaining) {
                pf_memcpy(work, buf + offset, remaining);
                error = NANDWrite(&info->file, work, remaining);
            }
            return -22;
        }
        offset = 0;
        while (remaining >= 512) {
            pf_memcpy(work, buf + offset, 512);
            error = NANDWrite(&info->file, work, 512);
            if (error < 0) { store_disk_error(disk, error); return error; }
            remaining -= error; offset += error;
        }
        if (remaining) {
            pf_memcpy(work, buf + offset, remaining);
            error = NANDWrite(&info->file, work, remaining);
            if (error < 0) { store_disk_error(disk, error); return error; }
        }
        *success = count;
        return 0;
    }
    store_disk_error(disk, error);
    return error;
}
