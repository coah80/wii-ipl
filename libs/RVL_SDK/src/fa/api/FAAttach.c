#include <revolution/fa/types.h>
#include <string.h>

typedef struct FA_NAND_ATTACH {
    char path[80];
    u32 size;
} FA_NAND_ATTACH;

FADisk* gOpenDisk[26];
FAPartition* gOpenPartition[26];
typedef struct FA_DISK_INIT {
    s32 (*initialize)(FADiskTbl*, u32);
    u32 extension;
} FA_DISK_INIT;

extern s32 pfd_sddrv_init_drv_tbl(FADiskTbl* table, u32 extension);
extern s32 usbh_msc_blk_init_drv_tbl(FADiskTbl* table, u32 extension);
extern s32 fa_nanddrv_init_drv_tbl(FADiskTbl* table, u32 extension);

static FA_DISK_INIT diskInitTbl[] = {
    {pfd_sddrv_init_drv_tbl, 0},
    {usbh_msc_blk_init_drv_tbl, 0},
    {fa_nanddrv_init_drv_tbl, 0},
};

static struct {
    FA_DISK_INIT* entries;
    u32 count;
} drvInitFunc = {diskInitTbl, 3};
extern s32 pdm_open_disk(FA_DISK_INIT* table, FADisk** disk);
extern s32 pdm_open_partition(FADisk* disk, u32 index, FAPartition** partition);
extern s32 pfstub_attach(FADrvTbl** drives, const void* nand_data);
extern s32 pfd_sddrv_is_media_insert(void);
extern s32 pfd_mscdrv_is_media_insert(FADisk* disk);

FAError FAAttach(u32 device, char* nand_path, u32 nand_size, FADrvTbl* table) {
    FADisk* disk;
    FADrvTbl* drives[2];
    FA_NAND_ATTACH nand;
    s32 error;
    s32 index;

    if (device >= 4) {
        return -2;
    }
    if (table == NULL) {
        return -2;
    }
    if (device == 2 && nand_path == NULL) {
        return -2;
    }
    if (device == 3 && table->pPart == NULL) {
        return -2;
    }
    if (device <= 2) {
        if (pdm_open_disk(&drvInitFunc.entries[(u8)device], &disk) != 0) {
            return -1;
        }
        if (pdm_open_partition(disk, 0, &table->pPart) != 0) {
            return -1;
        }
    }
    drives[0] = table;
    drives[1] = NULL;
    if (device == 2) {
        memcpy(nand.path, nand_path, 78);
        nand.size = nand_size;
    }
    if (device == 2) {
        error = pfstub_attach(drives, &nand);
    } else {
        error = pfstub_attach(drives, NULL);
    }
    if (error != 0) {
        return -1;
    }
    index = table->drive - 'A';
    if (device <= 2) {
        gOpenDisk[index] = disk;
        gOpenPartition[index] = table->pPart;
        if (device == 0) {
            if (pfd_sddrv_is_media_insert()) {
                drives[0]->stat |= 0x10;
            }
        } else if (device == 1) {
            if (pfd_mscdrv_is_media_insert(disk)) {
                drives[0]->stat |= 0x10;
            }
        }
    } else {
        gOpenDisk[index] = NULL;
        gOpenPartition[index] = NULL;
    }
    return 0;
}
