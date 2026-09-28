#include <revolution/types.h>
#include <revolution/os.h>
#include <revolution/sdi.h>
#include <string.h>

typedef struct PDM_DISK PDM_DISK;

typedef struct {
    u32 field_00;  // +0x00
    u16 field_04;  // +0x04
    u8 field_06;   // +0x06
    u8 field_07;   // +0x07
    u16 field_08;  // +0x08
    u16 field_0A;  // +0x0A
    u32 field_0C;  // +0x0C
    u32 field_10;  // +0x10
} PDM_DISK_INFO;

struct SDDRV_INFO {
    u32 flags;          // +0x00
    u32 bps;            // +0x04
    SDDev* dev;         // +0x08
    PDM_DISK* p_disk;   // +0x0C
    u32 inserted;       // +0x10
    u32 reset_done;     // +0x14
    s8 drv_char;        // +0x18
    u8 pad_19[3];
    u32 field_1C;       // +0x1C
};

struct SDDRV_INFO g_pfd_sddrv_info;
SDDev g_pfd_sddev;
static u8 g_pfd_sddev_pad[0x18];
u8 g_pfd_sddrv_buf[0x200];

static void* g_attach_func;
static void* g_detach_func;
static u32 g_event;

extern void pdm_disk_notify_media_insert(PDM_DISK* p_disk);
extern void pdm_disk_notify_media_eject(PDM_DISK* p_disk);
extern s32 pfd_get_media_drv_char(PDM_DISK* p_disk, u8* p_drv_char, s32 n);
extern void* pf_memcpy(void* dst, const void* src, u32 len);
extern void* pf_memset(void* dst, s32 c, u32 len);
extern s32 pf_strcmp(const char* s1, const char* s2);

s32 pfd_sddrv_init(PDM_DISK* p_disk);
s32 pfd_sddrv_mount(PDM_DISK* p_disk);
s32 pfd_sddrv_format(PDM_DISK* p_disk, const u8* param);
s32 pfd_sddrv_pread(PDM_DISK* p_disk, u8* p_buf, u32 block, u32 num_blocks, u32* p_num_success);
s32 pfd_sddrv_pwrite(PDM_DISK* p_disk, const u8* p_buf, u32 block, u32 num_blocks, u32* p_num_success);
s32 pfd_sddrv_unmount(PDM_DISK* p_disk);
s32 pfd_sddrv_finalize(PDM_DISK* p_disk);
s32 pfd_sddrv_get_disk_info(PDM_DISK* p_disk, PDM_DISK_INFO* p_disk_info);
static s32 pfd_sddrv_physical_read(u32 num_blocks, u8* buf, u32 block, u32 bps, u32* p_num_success);
s32 pfd_sddrv_physical_write(u32 num_blocks, const u8* buf, u32 block, u32 bps, u32* p_num_success);
s32 pfd_sddrv_get_total_sectors(u32* p_total_sectors, u16* p_bps);
s32 pfd_sddrv_full_format(void);

typedef s32 (*PF_DRV_FUNC)();

static const PF_DRV_FUNC pfd_sddrv_func[8] = {
    (PF_DRV_FUNC)pfd_sddrv_init,          (PF_DRV_FUNC)pfd_sddrv_finalize,
    (PF_DRV_FUNC)pfd_sddrv_mount,         (PF_DRV_FUNC)pfd_sddrv_unmount,
    (PF_DRV_FUNC)pfd_sddrv_format,        (PF_DRV_FUNC)pfd_sddrv_pread,
    (PF_DRV_FUNC)pfd_sddrv_pwrite,        (PF_DRV_FUNC)pfd_sddrv_get_disk_info,
};

typedef struct {
    u32 cap_lo;   // +0x00
    u32 cap_hi;   // +0x04
    u32 field_08; // +0x08
    u32 field_0C; // +0x0C
    u32 field_10; // +0x10
    u8 field_14;  // +0x14
    u8 pad_15[3];
} SDDRV_SIZE_DEPEND;

static const SDDRV_SIZE_DEPEND sddrv_size_depend_tbl[14] = {
    {0x0,      0x1000,   0x10,   0x2,  0x10, 0x10, {0, 0, 0}},
    {0x1000,   0x4000,   0x10,   0x2,  0x20, 0x10, {0, 0, 0}},
    {0x4000,   0x8000,   0x20,   0x2,  0x20, 0x20, {0, 0, 0}},
    {0x8000,   0x10000,  0x20,   0x4,  0x20, 0x20, {0, 0, 0}},
    {0x10000,  0x20000,  0x20,   0x8,  0x20, 0x20, {0, 0, 0}},
    {0x20000,  0x40000,  0x40,   0x8,  0x20, 0x20, {0, 0, 0}},
    {0x40000,  0x80000,  0x40,   0x10, 0x20, 0x20, {0, 0, 0}},
    {0x80000,  0xFC000,  0x80,   0x10, 0x3F, 0x20, {0, 0, 0}},
    {0xFC000,  0x1F8000, 0x80,   0x20, 0x3F, 0x20, {0, 0, 0}},
    {0x1F8000, 0x200000, 0x80,   0x40, 0x3F, 0x20, {0, 0, 0}},
    {0x200000, 0x3F0000, 0x80,   0x40, 0x3F, 0x40, {0, 0, 0}},
    {0x3F0000, 0x400000, 0x80,   0x80, 0x3F, 0x40, {0, 0, 0}},
    {0x400000, 0x7E0000, 0x2000, 0x80, 0x3F, 0x40, {0, 0, 0}},
    {0x7E0000, 0x4000000,0x2000, 0xFF, 0x3F, 0x40, {0, 0, 0}},
};

typedef struct {
    u32 f8;
    u32 fC;
    u32 f10;
    u8 f14;
    u8 pad_15[3];
} SDDRV_FIELDS;

s32 pfd_st_inter_callback(u32 status, void* data) {
    struct SDDRV_INFO* info = &g_pfd_sddrv_info;
    u8 drv_char;

    if ((s32)(status & 1) != 1) {
        return 0;
    }
    if (g_pfd_sddrv_info.dev != NULL) {
        g_event = 2;
        if (ISD_RegisterDeviceIntrHandler((SDDev*)*(u32*)&info->dev, pfd_st_inter_callback, &g_event) != 0) {
            OSReport("ERR:Failed to regist intr handler. pfd_st_inter_callback()\n");
        }
    }
    if (info->p_disk != NULL) {
        if (info->drv_char == 0) {
            if ((u8)pfd_get_media_drv_char(info->p_disk, &drv_char, 1) == 1) {
                info->drv_char = drv_char;
            }
        }
        pdm_disk_notify_media_insert(info->p_disk);
        if (info->drv_char != 0) {
            if (g_attach_func != NULL) {
                ((void (*)(s8))g_attach_func)(info->drv_char);
            }
        }
    }
    info->inserted = 1;
    info->reset_done = 1;
    return 0;
}

s32 pfd_st_removal_callback(u32 status, void* data) {
    struct SDDRV_INFO* info = &g_pfd_sddrv_info;
    u8 drv_char;

    if ((s32)(status & 2) != 2) {
        return 0;
    }
    info->inserted = 0;
    if (g_pfd_sddrv_info.dev != NULL) {
        g_event = 1;
        if (ISD_RegisterDeviceIntrHandler(info->dev, pfd_st_removal_callback, &g_event) != 0) {
            OSReport("ERR:Failed to regist intr handler. pfd_st_removal_callback()\n");
        }
    }
    if (info->p_disk != NULL) {
        if (info->drv_char == 0) {
            if ((u8)pfd_get_media_drv_char(info->p_disk, &drv_char, 1) == 1) {
                info->drv_char = drv_char;
            }
        }
        pdm_disk_notify_media_eject(info->p_disk);
        if (info->drv_char != 0) {
            if (g_detach_func != NULL) {
                ((void (*)(s8))g_detach_func)(info->drv_char);
            }
        }
    }
    return 0;
}

s32 pfd_sddrv_init(PDM_DISK* p_disk) {
    s32 ret;
    SDDev* dev;
    u32 status;

    if (p_disk == NULL) {
        return -0x1e;
    }
    if ((g_pfd_sddrv_info.flags & 1) != 0) {
        OSReport("INFO SD Card driver is already initialize. pfd_sddrv_init()\n");
        if (p_disk != g_pfd_sddrv_info.p_disk) {
            return -0x2c;
        }
        return 0;
    }
    if ((g_pfd_sddrv_info.flags & 4) == 0) {
        g_pfd_sddrv_info.bps = 0x200;
        pf_memset(&g_pfd_sddev, 0, 0x28);
        ret = ISD_InitCard();
        if (ret != 0) {
            OSReport("ERR:Failed to init SD Card Driver in pfd_sddrv_init()\n");
            return -0x28;
        }
        g_pfd_sddrv_info.flags |= 4;
    }
    pf_memset(&g_pfd_sddev, 0, 0x28);
    dev = &g_pfd_sddev;
    ret = ISD_MountCard(0, &dev);
    if (ret != 0) {
        OSReport("ERR SD card can not mount [ret = 0x%x]. pfd_sddrv_init()\n", ret);
        return -0x29;
    }
    ret = ISD_GetDeviceStatus(dev, &status);
    if (ret != 0) {
        OSReport("ERR Failed to get sd card status. [ret = 0x%x]\n", ret);
        return 0x15;
    }
    if ((status & 1) != 0) {
        g_pfd_sddrv_info.inserted = 1;
    }
    g_pfd_sddrv_info.dev = dev;
    if (g_pfd_sddrv_info.inserted != 0) {
        g_event = 2;
        ret = ISD_RegisterDeviceIntrHandler(dev, pfd_st_inter_callback, &g_event);
        if (ret != 0) {
            OSReport("ERR:Failed to regist intr handler1 [ret = 0x%x] pfd_sddrv_init()\n", ret);
            ISD_UnmountCard(dev);
            g_pfd_sddrv_info.dev = NULL;
            return -0x2a;
        }
    } else {
        g_event = 1;
        ret = ISD_RegisterDeviceIntrHandler(dev, pfd_st_removal_callback, &g_event);
        if (ret != 0) {
            OSReport("ERR:Failed to regist intr handler1 [ret = 0x%x] pfd_sddrv_init()\n", ret);
            ISD_UnmountCard(dev);
            g_pfd_sddrv_info.dev = NULL;
            return -0x2a;
        }
    }
    g_pfd_sddrv_info.p_disk = p_disk;
    g_pfd_sddrv_info.flags |= 1;
    return 0;
}

s32 pfd_sddrv_mount(PDM_DISK* p_disk) {
    s32 ret;
    u32 i;
    u32 reg;
    u32 cid[4];
    u16 rca;

    if (p_disk == NULL) {
        return -0x1e;
    }
    if (g_pfd_sddrv_info.inserted == 0) {
        return -0x21;
    }
    if ((g_pfd_sddrv_info.flags & 2) != 0) {
        OSReport("INFO sdcard alrady mounted. pfd_sddrv_mount()\n");
        return 0;
    }
    for (i = 0; i < 5; i++) {
        if (g_pfd_sddrv_info.inserted == 0) {
            return -0x21;
        }
        ret = ISD_ResetDevice(g_pfd_sddrv_info.dev);
        if (ret == 0) {
            g_pfd_sddrv_info.reset_done = 0;
            break;
        }
        OSReport("ERROR Failed to SD Card Reset [ret = 0x%x]. pfd_sddrv_mount()\n", ret);
    }
    if (i == 5) {
        return -0x26;
    }
    if (g_pfd_sddrv_info.reset_done != 0) {
        return -0x21;
    }
    reg = 0;
    ret = ISD_ReadCardRegister(g_pfd_sddrv_info.dev, 0x29, &reg, 4);
    if (ret != 0) {
        OSReport("ERR Failed to read OCR reg. pfd_sddrv_mount()\n");
        return -0x2b;
    }
    pf_memset(cid, 0, 0x10);
    ret = ISD_ReadCardRegister(g_pfd_sddrv_info.dev, 0xa, cid, 0x10);
    if (ret != 0) {
        OSReport("ERR Failed to read CID reg. pfd_sddrv_mount()\n");
        return -0x2b;
    }
    rca = 0;
    ret = ISD_ReadCardRegister(g_pfd_sddrv_info.dev, 3, (u32*)&rca, 2);
    if (ret != 0) {
        OSReport("ERR Failed to read RCA reg. pfd_sddrv_mount()\n");
        return -0x2b;
    }
    g_pfd_sddrv_info.flags |= 2;
    return 0;
}

s32 pfd_sddrv_format(PDM_DISK* p_disk, const u8* param) {
    s32 ret;

    if (p_disk == NULL) {
        return -0x1e;
    }
    if (g_pfd_sddrv_info.inserted == 0) {
        return -0x21;
    }
    ret = 0;
    if (param != NULL && pf_strcmp((const char*)param, "FULL_FORMAT") == 0) {
        ret = pfd_sddrv_full_format();
        if (ret != 0) {
            OSReport("ERR Failed to full format. pfd_sddrv_full_format()\n");
            return ret;
        }
    }
    return 0;
}

s32 pfd_sddrv_pread(PDM_DISK* p_disk, u8* p_buf, u32 block, u32 num_blocks, u32* p_num_success) {
    if (p_disk == NULL || p_buf == NULL || p_num_success == NULL) {
        return -0x1e;
    }
    return pfd_sddrv_physical_read(num_blocks, p_buf, block, g_pfd_sddrv_info.bps, p_num_success);
}

s32 pfd_sddrv_pwrite(PDM_DISK* p_disk, const u8* p_buf, u32 block, u32 num_blocks, u32* p_num_success) {
    if (p_disk == NULL || p_buf == NULL || p_num_success == NULL) {
        return -0x1e;
    }
    return pfd_sddrv_physical_write(num_blocks, p_buf, block, g_pfd_sddrv_info.bps, p_num_success);
}

s32 pfd_sddrv_unmount(PDM_DISK* p_disk) {
    if (p_disk == NULL) {
        return -0x1e;
    }
    if ((g_pfd_sddrv_info.flags & 2) != 0) {
        g_pfd_sddrv_info.flags &= ~2;
    }
    return 0;
}

s32 pfd_sddrv_finalize(PDM_DISK* p_disk) {
    s32 ret;

    if (p_disk == NULL) {
        return -0x1e;
    }
    if ((g_pfd_sddrv_info.flags & 2) != 0) {
        g_pfd_sddrv_info.flags &= ~2;
    }
    if ((g_pfd_sddrv_info.flags & 1) != 0) {
        ret = ISD_UnregisterDeviceIntrHandler(g_pfd_sddrv_info.dev);
        if (ret != 0) {
            OSReport("WARNING Faild to UnregisterDeviceIntrHandler sd card [ret = %d]\n", ret);
        }
        ret = ISD_UnmountCard(g_pfd_sddrv_info.dev);
        if (ret != 0) {
            OSReport("WARNING Faild to unmount sd card [ret = %d]\n", ret);
        }
        g_pfd_sddrv_info.dev = NULL;
    }
    g_pfd_sddrv_info.flags &= ~1;
    g_pfd_sddrv_info.inserted = 0;
    g_pfd_sddrv_info.p_disk = NULL;
    g_pfd_sddrv_info.drv_char = 0;
    return 0;
}

s32 pfd_sddrv_get_disk_info(PDM_DISK* p_disk, PDM_DISK_INFO* p_disk_info) {
    u32 status;
    s32 ret;

    if (p_disk == NULL || p_disk_info == NULL) {
        return -0x1e;
    }
    if ((g_pfd_sddrv_info.flags & 2) == 0) {
        return -0x2d;
    }
    if (g_pfd_sddrv_info.reset_done != 0) {
        return -0x2d;
    }
    if (g_pfd_sddrv_info.inserted == 0) {
        return -0x21;
    }
    ret = ISD_GetDeviceStatus(g_pfd_sddrv_info.dev, &status);
    if (ret != 0) {
        OSReport("ERR Failed to get sd card status. [ret = 0x%x]\n", ret);
        return -0x27;
    }
    if ((status & 1) == 0) {
        OSReport("INFO Card not inserted! in pfd_sddrv_get_disk_info()\n");
        return -0x21;
    }
    if ((status & 2) != 0) {
        OSReport("INFO Card removed! in pfd_sddrv_get_disk_info()\n");
        return -0x21;
    }
    if ((status & 0x10000) == 0 && (status & 0x100000) == 0) {
        OSReport("INFO SD card type is not memory. in pfd_sddrv_get_disk_info()\n");
        return -0x23;
    }
    p_disk_info->field_0C = 4;
    if ((status & 4) != 0) {
        p_disk_info->field_0C |= 1;
    }
    ret = pfd_sddrv_get_total_sectors((u32*)p_disk_info, &p_disk_info->field_08);
    if (ret != 0) {
        OSReport("ERR Failed to read master boot sector. pfd_sddrv_get_disk_info()\n");
        return ret;
    }
    p_disk_info->field_04 = 0;
    p_disk_info->field_06 = 0;
    p_disk_info->field_07 = 0;
    p_disk_info->field_10 = 0;
    return 0;
}

s32 pfd_sddrv_init_drv_tbl(PF_DRV_FUNC* p_disk_tbl, u32 ui_ext) {
    p_disk_tbl[1] = (PF_DRV_FUNC)ui_ext;
    p_disk_tbl[0] = (PF_DRV_FUNC)pfd_sddrv_func;
    return 0;
}

s32 pfd_sddrv_registar_callback(void* attach_func, void* detach_func) {
    g_attach_func = attach_func;
    g_detach_func = detach_func;
    return 0;
}

s32 pfd_sddrv_is_media_insert(void) {
    u8 drv_char;

    if ((g_pfd_sddrv_info.flags & 1) == 0) {
        return 0;
    }
    if (g_pfd_sddrv_info.drv_char == 0) {
        if ((u8)pfd_get_media_drv_char(g_pfd_sddrv_info.p_disk, &drv_char, 1) == 1) {
            g_pfd_sddrv_info.drv_char = drv_char;
        }
    }
    if (g_pfd_sddrv_info.inserted != 0) {
        pdm_disk_notify_media_insert(g_pfd_sddrv_info.p_disk);
        return 1;
    }
    return 0;
}

static s32 pfd_sddrv_physical_read(u32 num_blocks, u8* buf, u32 block, u32 bps, u32* p_num_success) {
    u32 i;
    s32 ret;

    if ((g_pfd_sddrv_info.flags & 2) == 0) {
        *p_num_success = 0;
        return -0x2d;
    }
    if (g_pfd_sddrv_info.reset_done != 0) {
        return -0x2d;
    }
    if (num_blocks == 0) {
        *p_num_success = 0;
        return -0x1e;
    }
    *p_num_success = -1;
    if (((u32)buf & 0x1F) == 0) {
        if (g_pfd_sddrv_info.inserted == 0) {
            *p_num_success = 0;
            return -0x21;
        }
        if (num_blocks == 1) {
            ret = ISD_ReadBlock(g_pfd_sddrv_info.dev, block, buf, num_blocks);
            if (ret != 0) {
                OSReport("INFO Failed to read SD card1 [ret = 0x%x] pfd_sddrv_physical_read()\n", ret);
                *p_num_success = 0;
                return -0x25;
            }
        } else {
            ret = ISD_ReadMultiBlock(g_pfd_sddrv_info.dev, block, buf, num_blocks);
            if (ret != 0) {
                OSReport("INFO Failed to read SD card2 [ret = 0x%x] pfd_sddrv_physical_read()\n", ret);
                *p_num_success = 0;
                return -0x25;
            }
        }
    } else {
        for (i = 0; i < num_blocks; i++) {
            if (g_pfd_sddrv_info.inserted == 0) {
                if (i != 0) {
                    *p_num_success = i;
                    return 0;
                }
                *p_num_success = 0;
                return -0x21;
            }
            ret = ISD_ReadBlock(g_pfd_sddrv_info.dev, block, g_pfd_sddrv_buf, 1);
            if (ret != 0) {
                OSReport("INFO Failed to read SD card3 [ret = 0x%x] pfd_sddrv_physical_read()\n", ret);
                if (i != 0) {
                    *p_num_success = i;
                    return 0;
                }
                *p_num_success = 0;
                return -0x25;
            }
            pf_memcpy(buf, g_pfd_sddrv_buf, bps);
            buf += bps;
            block++;
        }
    }
    *p_num_success = num_blocks;
    return 0;
}

s32 pfd_sddrv_physical_write(u32 num_blocks, const u8* buf, u32 block, u32 bps, u32* p_num_success) {
    u32 i;
    s32 ret;

    if ((g_pfd_sddrv_info.flags & 2) == 0) {
        *p_num_success = 0;
        return -0x2d;
    }
    if (g_pfd_sddrv_info.reset_done != 0) {
        return -0x2d;
    }
    if (num_blocks == 0) {
        *p_num_success = 0;
        return -0x1e;
    }
    *p_num_success = -1;
    if (((u32)buf & 0x1F) == 0) {
        if (g_pfd_sddrv_info.inserted == 0) {
            *p_num_success = 0;
            return -0x21;
        }
        if (num_blocks == 1) {
            ret = ISD_WriteBlock(g_pfd_sddrv_info.dev, block, (u8*)buf, num_blocks);
            if (ret != 0) {
                OSReport("INFO Failed to write SD card1 [ret = 0x%x] pfd_sddrv_physical_write()\n", ret);
                *p_num_success = 0;
                return -0x24;
            }
        } else {
            ret = ISD_WriteMultiBlock(g_pfd_sddrv_info.dev, block, (u8*)buf, num_blocks);
            if (ret != 0) {
                OSReport("INFO Failed to write SD card2 [ret = 0x%x] pfd_sddrv_physical_write()\n", ret);
                *p_num_success = 0;
                return -0x24;
            }
        }
    } else {
        for (i = 0; i < num_blocks; i++) {
            if (g_pfd_sddrv_info.inserted == 0) {
                if (i != 0) {
                    *p_num_success = i;
                    return 0;
                }
                *p_num_success = 0;
                return -0x21;
            }
            pf_memcpy(g_pfd_sddrv_buf, buf, bps);
            ret = ISD_WriteBlock(g_pfd_sddrv_info.dev, block, g_pfd_sddrv_buf, 1);
            if (ret != 0) {
                OSReport("INFO Failed to write SD card3 [ret = 0x%x] pfd_sddrv_physical_write()\n", ret);
                if (i != 0) {
                    *p_num_success = i;
                    return 0;
                }
                *p_num_success = 0;
                return -0x24;
            }
            buf += bps;
            block++;
        }
    }
    *p_num_success = num_blocks;
    return 0;
}

s32 pfd_sddrv_get_total_sectors(u32* p_total_sectors, u16* p_bps) {
    u32 csd[4];
    s32 ret;
    u32 c_size;
    u32 c_size_mult;
    u32 read_bl_len;
    u32 mult;
    u32 bl;

    if (g_pfd_sddrv_info.inserted == 0) {
        return -0x21;
    }
    pf_memset(csd, 0, 0x10);
    ret = ISD_ReadCardRegister(g_pfd_sddrv_info.dev, 9, csd, 0x10);
    if (ret != 0) {
        OSReport("ERR Failed to read CSD reg. pfd_sddrv_get_total_sectors()\n");
        return -0x2b;
    }
    if ((csd[3] & 0x400000) == 0) {
        c_size_mult = ((csd[1] >> 7) & 7) + 2;
        mult = 1 << c_size_mult;
        c_size = (csd[1] >> 0x16) | ((csd[2] & 3) << 0xA);
        read_bl_len = (csd[2] >> 8) & 0xF;
        if (read_bl_len < 9) {
            bl = 9;
        } else {
            bl = read_bl_len;
        }
        if (bl > 0xB) {
            bl = 0xB;
        }
        bl = (u16)(bl - 9);
        bl = (u16)(1 << bl);
        *p_total_sectors = (c_size + 1) * mult * bl;
    } else {
        *p_total_sectors = (((csd[1] >> 8) & 0x3FFFFF) + 1) << 0xA;
    }
    *p_bps = 0x200;
    return 0;
}

typedef struct {
    u32 field_00;  // +0x00
    u32 field_04;  // +0x04
    u8 field_08;   // +0x08
    u8 pad_09[3];
    u32 field_0C;  // +0x0C
    u32 field_10;  // +0x10
    u32 field_14;  // +0x14
    u32 field_18;  // +0x18
    u32 field_1C;  // +0x1C
} SDDRV_MBR_BPB;


static s32 pfd_sddrv_store_bpb_buf(SDDRV_MBR_BPB* p, u8* buf);
static s32 pfd_sddrv_store_mbr_buf(SDDRV_MBR_BPB* p, u8* buf);
static s32 pfd_sddrv_store_fat32_bpb_buf(SDDRV_MBR_BPB* p, u8* buf);
static s32 pfd_sddrv_store_fat32_mbr_buf(SDDRV_MBR_BPB* p, u8* buf);
static s32 pfd_sddrv_store_fat32_fsi_buf(u8* buf);

s32 pfd_sddrv_calc_mbr_bpb(SDDRV_MBR_BPB* p) {
    const SDDRV_SIZE_DEPEND* p_tbl;
    SDDRV_FIELDS v;
    u32 total;
    u32 fat_sz;
    u32 bpe;
    u32 fat_area;
    u32 rem;
    u32 span;
    u32 clusters;
    u32 n;
    u32 acc;
    u32 new_fat;
    u32 data;
    u32 r0;
    s32 i;
    s32 retry;
    s32 err;
    OSCalendarTime cal;
    u32 date;
    u32 time_v;

    if (p == NULL) {
        return -0x1e;
    }
    pf_memset(&v, 0, 0x10);
    p_tbl = sddrv_size_depend_tbl;
    total = p->field_1C;
    for (i = 0; i < 14; i++) {
        if (p_tbl->cap_lo < total) {
            if (p_tbl->cap_hi >= total) { v.f8 = sddrv_size_depend_tbl[i].field_08; v.fC = sddrv_size_depend_tbl[i].field_0C; v.f10 = sddrv_size_depend_tbl[i].field_10; v.f14 = sddrv_size_depend_tbl[i].field_14; break; }
        }
        p_tbl++;
    }
    err = (i == 14) ? -0x1e : 0;
    if (err != 0) {
        OSReport("ERR Failed to get values with total sectors. pfd_sddrv_get_value_with_total_sectors()\n");
        return err;
    }
    retry = 0;
    p->field_08 = v.f14;
    total = p->field_1C;
    clusters = total / v.f14;
    if (clusters < 0x1005) {
        bpe = 0xC;
    } else if (clusters < 0xFFF5) {
        bpe = 0x10;
    } else {
        return -0x1f;
    }
    if (total % v.f14 != 0) {
        clusters++;
    }
    clusters = clusters * bpe;
    fat_sz = clusters >> 0xC;
    if ((clusters & 0xFFF) != 0) {
        fat_sz++;
    }
compute:
    fat_area = fat_sz * 2 + 0x21;
    acc = v.f8;
    n = 1;
    while ((rem = acc - fat_area) <= 0) {
        acc += v.f8;
        n++;
    }
    span = n * v.f8;
loop_top:
    if (retry == 0 && rem != v.f8) {
        rem += v.f8;
    }
    data = total - rem - fat_area;
    retry = 0;
    clusters = data / v.f14 + 1;
    if (clusters >= 0xFE5 && clusters < 0x1005) {
        span += v.f8;
        rem = span - fat_area;
        goto loop_top;
    }
    r0 = clusters - 1;
    new_fat = (r0 * bpe + 2) >> 0xC;
    if (((r0 * bpe + 2) & 0xFFF) != 0) {
        new_fat++;
    }
    if (new_fat <= fat_sz) {
        if (new_fat == fat_sz) {
            goto done;
        }
        fat_sz = new_fat;
        goto compute;
    }
    rem += v.f8;
    retry = 1;
    goto loop_top;
done:
    total = p->field_1C;
    fat_area = fat_sz * 2 + 0x21;
    r0 = (u32)p->field_08;
    data = total - rem;
    p->field_0C = fat_sz;
    clusters = (data - fat_area) / r0;
    p->field_00 = rem;
    p->field_04 = data;
    r0 = clusters + 1;
    if (r0 < 0xFF5) {
        p->field_14 = 0;
    } else if (r0 >= 0xFFF5) {
        return -0x1f;
    } else {
        p->field_14 = 1;
    }
    OSTicksToCalendarTime(OSGetTime(), &cal);
    date = (cal.mday & 0x1F) | (cal.mon << 5) | ((cal.year - 0x76C) << 9);
    time_v = (cal.sec & 0x1F) | (cal.min << 5) | (cal.hour << 0xB);
    p->field_10 = (date << 0x10) + time_v;
    return 0;
}

#define SDDRV_LE16(p, off, v)                                   \
    if (((u32)((p) + (off)) & 1) != 0) {                        \
        (p)[off] = (u8)(v);                                     \
        (p)[(off) + 1] = (u8)((v) >> 8);                        \
    } else {                                                    \
        *(u16*)((p) + (off)) = (((v) & 0xFF) << 8) | (((v) & 0xFF00) >> 8); \
    }

static s32 pfd_sddrv_store_bpb_buf(SDDRV_MBR_BPB* p, u8* buf) {
    SDDRV_FIELDS v;
    u32 total;
    u32 r30;
    u32 r29;
    s32 i;
    s32 err;
    const SDDRV_SIZE_DEPEND* p_tbl;
    const char* s;

    if (p == NULL) {
        return -0x1e;
    }
    pf_memset(&v, 0, 0x10);
    p_tbl = sddrv_size_depend_tbl;
    total = p->field_1C;
    for (i = 0; i < 14; i++) {
        if (p_tbl->cap_lo < total) {
            if (p_tbl->cap_hi >= total) { v.f8 = sddrv_size_depend_tbl[i].field_08; v.fC = sddrv_size_depend_tbl[i].field_0C; v.f10 = sddrv_size_depend_tbl[i].field_10; v.f14 = sddrv_size_depend_tbl[i].field_14; break; }
        }
        p_tbl++;
    }
    err = (i == 14) ? -0x1e : 0;
    if (err != 0) {
        OSReport("ERR Failed to get values with total sectors. pfd_sddrv_get_value_with_total_sectors()\n");
        return err;
    }
    r29 = p->field_04;
    if (r29 != 0 && r29 < 0x10000) {
        r30 = (u16)r29;
        r29 = 0;
        goto ok;
    }
    if (r29 < 0x10000) {
        goto fail;
    }
    r30 = 0;
    goto ok;
fail:
    return -0x1e;
ok:
    pf_memset(buf, 0, 0x200);
    if (buf + 3 != NULL && (s = "        ") != NULL) {
        buf[3] = "        "[0];
        buf[4] = s[1];
        buf[5] = s[2];
        buf[6] = s[3];
        buf[7] = s[4];
        buf[8] = s[5];
        buf[9] = s[6];
        buf[10] = s[7];
    }
    if (buf + 0x2b != NULL && (s = "NO NAME    ") != NULL) {
        buf[0x2b] = s[0];
        buf[0x2c] = s[1];
        buf[0x2d] = s[2];
        buf[0x2e] = s[3];
        buf[0x2f] = s[4];
        buf[0x30] = s[5];
        buf[0x31] = s[6];
        buf[0x32] = s[7];
        buf[0x33] = s[8];
        buf[0x34] = s[9];
        buf[0x35] = s[10];
    }
    if (p->field_14 == 0) {
        if (buf + 0x36 != NULL && (s = "FAT12   ") != NULL) {
            buf[0x36] = "FAT12   "[0];
            buf[0x37] = s[1];
            buf[0x38] = s[2];
            buf[0x39] = s[3];
            buf[0x3a] = s[4];
            buf[0x3b] = s[5];
            buf[0x3c] = s[6];
            buf[0x3d] = s[7];
        }
    } else {
        if (buf + 0x36 != NULL && (s = "FAT16   ") != NULL) {
            buf[0x36] = "FAT16   "[0];
            buf[0x37] = s[1];
            buf[0x38] = s[2];
            buf[0x39] = s[3];
            buf[0x3a] = s[4];
            buf[0x3b] = s[5];
            buf[0x3c] = s[6];
            buf[0x3d] = s[7];
        }
    }
    buf[0] = 0xeb;
    buf[1] = 0;
    buf[2] = 0x90;
    if (((u32)(buf + 0xb) & 1) != 0) {
        buf[0xb] = 0;
        buf[0xc] = 2;
    } else {
        *(u16*)(buf + 0xc) = 2;
    }
    buf[0xd] = p->field_08;
    if (((u32)(buf + 0xe) & 1) != 0) {
        buf[0xe] = 1;
        buf[0xf] = 0;
    } else {
        *(u16*)(buf + 0xe) = 0x100;
    }
    buf[0x10] = 2;
    if (((u32)(buf + 0x11) & 1) != 0) {
        buf[0x11] = 0;
        buf[0x12] = 2;
    } else {
        *(u16*)(buf + 0x12) = 2;
    }
    if (((u32)(buf + 0x13) & 1) != 0) {
        buf[0x13] = (u8)r30;
        buf[0x14] = (u8)(r30 >> 8);
    } else {
        __sthbrx(r30, buf + 0x14, 0);
    }
    buf[0x15] = 0xf8;
    SDDRV_LE16(buf, 0x16, p->field_0C);
    SDDRV_LE16(buf, 0x18, v.f10);
    SDDRV_LE16(buf, 0x1a, v.fC);
    if (((u32)(buf + 0x1c) & 3) != 0) {
        buf[0x1c] = (u8)p->field_00;
        buf[0x1d] = (u8)(p->field_00 >> 8);
        buf[0x1e] = (u8)(p->field_00 >> 0x10);
        buf[0x1f] = (u8)(p->field_00 >> 0x18);
    } else {
        *(u32*)(buf + 0x1c) = ((p->field_00 >> 0x18) | ((p->field_00 >> 8) & 0xFF00) | ((p->field_00 << 8) & 0xFF0000) | (p->field_00 << 0x18));
    }
    if (((u32)(buf + 0x20) & 3) != 0) {
        buf[0x20] = (u8)r29;
        buf[0x21] = (u8)(r29 >> 8);
        buf[0x22] = (u8)(r29 >> 0x10);
        buf[0x23] = (u8)(r29 >> 0x18);
    } else {
        *(u32*)(buf + 0x20) = ((r29 >> 0x18) | ((r29 >> 8) & 0xFF00) | ((r29 << 8) & 0xFF0000) | (r29 << 0x18));
    }
    buf[0x24] = 0x80;
    buf[0x26] = 0x29;
    if (((u32)(buf + 0x27) & 3) != 0) {
        buf[0x27] = (u8)p->field_10;
        buf[0x28] = (u8)(p->field_10 >> 8);
        buf[0x29] = (u8)(p->field_10 >> 0x10);
        buf[0x2a] = (u8)(p->field_10 >> 0x18);
    } else {
        *(u32*)(buf + 0x30) = ((p->field_10 >> 0x18) | ((p->field_10 >> 8) & 0xFF00) | ((p->field_10 << 8) & 0xFF0000) | (p->field_10 << 0x18));
    }
    buf[0x1fe] = 0x55;
    buf[0x1ff] = 0xaa;
    return 0;
}

static s32 pfd_sddrv_store_mbr_buf(SDDRV_MBR_BPB* p, u8* buf) {
    SDDRV_FIELDS v;
    u32 total;
    u16 cyl1;
    u16 sec1;
    u16 cyl2;
    u16 sec2;
    u8 head1;
    u8 head2;
    u8 type;
    u32 end;
    u32 hps;
    s32 i;
    s32 err;
    const SDDRV_SIZE_DEPEND* p_tbl;

    if (p == NULL || buf == NULL) {
        return -0x1e;
    }
    pf_memset(&v, 0, 0x10);
    p_tbl = sddrv_size_depend_tbl;
    total = p->field_1C;
    for (i = 0; i < 14; i++) {
        if (p_tbl->cap_lo < total) {
            if (p_tbl->cap_hi >= total) { v.f8 = sddrv_size_depend_tbl[i].field_08; v.fC = sddrv_size_depend_tbl[i].field_0C; v.f10 = sddrv_size_depend_tbl[i].field_10; v.f14 = sddrv_size_depend_tbl[i].field_14; break; }
        }
        p_tbl++;
    }
    err = (i == 14) ? -0x1e : 0;
    if (err != 0) {
        OSReport("ERR Failed to get values with total sectors. pfd_sddrv_get_value_with_total_sectors()\n");
        return err;
    }
    hps = v.fC * v.f10;
    end = p->field_1C - 1;
    cyl2 = (u16)(end / hps);
    cyl1 = (u16)(p->field_00 / hps);
    sec1 = (u16)((p->field_00 % v.f10) + 1);
    sec2 = (u16)((end % v.f10) + 1);
    head2 = (u8)((end - (end / hps) * hps) / v.f10);
    head1 = (u8)((p->field_00 - (p->field_00 / hps) * hps) / v.f10);
    if (p->field_04 == 0) {
        return -0x1e;
    }
    if (p->field_04 != 0 && p->field_04 < 0x7FA8) {
        type = 1;
    } else if (p->field_04 >= 0x7FA8 && p->field_04 < 0x10000) {
        type = 4;
    } else {
        type = 6;
    }
    pf_memset(buf, 0, 0x200);
    buf[0x1be] = 0;
    buf[0x1bf] = head1;
    SDDRV_LE16(buf, 0x1c0, ((cyl1 & 0xFF) << 8) | (sec1 & 0x3F) | ((cyl1 & 0x300) >> 2));
    buf[0x1c2] = type;
    buf[0x1c3] = head2;
    SDDRV_LE16(buf, 0x1c4, ((cyl2 & 0xFF) << 8) | (sec2 & 0x3F) | ((cyl2 & 0x300) >> 2));
    if (((u32)(buf + 0x1c6) & 3) != 0) {
        buf[0x1c6] = (u8)p->field_00;
        buf[0x1c7] = (u8)(p->field_00 >> 8);
        buf[0x1c8] = (u8)(p->field_00 >> 0x10);
        buf[0x1c9] = (u8)(p->field_00 >> 0x18);
    } else {
        *(u32*)(buf + 0x1cc) = ((p->field_00 >> 0x18) | ((p->field_00 >> 8) & 0xFF00) | ((p->field_00 << 8) & 0xFF0000) | (p->field_00 << 0x18));
    }
    if (((u32)(buf + 0x1ca) & 3) != 0) {
        buf[0x1ca] = (u8)p->field_04;
        buf[0x1cb] = (u8)(p->field_04 >> 8);
        buf[0x1cc] = (u8)(p->field_04 >> 0x10);
        buf[0x1cd] = (u8)(p->field_04 >> 0x18);
    } else {
        *(u32*)(buf + 0x1d0) = ((p->field_04 >> 0x18) | ((p->field_04 >> 8) & 0xFF00) | ((p->field_04 << 8) & 0xFF0000) | (p->field_04 << 0x18));
    }
    buf[0x1fe] = 0x55;
    buf[0x1ff] = 0xaa;
    return 0;
}

s32 pfd_sddrv_build_mbr_bpb(u32 total_sectors) {
    SDDRV_MBR_BPB mbp;
    s32 ret;
    u32 lba;

    pf_memset(&mbp, 0, 0x20);
    mbp.field_1C = total_sectors;
    ret = pfd_sddrv_calc_mbr_bpb(&mbp);
    if (ret != 0) {
        OSReport("ERR Failed to calculate MBR and BPB values. pfd_sddrv_calc_mbr_bpb()\n");
        return ret;
    }
    ret = pfd_sddrv_store_bpb_buf(&mbp, g_pfd_sddrv_buf);
    lba = mbp.field_00;
    if (ret != 0) {
        OSReport("ERR Failed to store BPB values to buf. pfd_sddrv_store_bpb_buf()\n");
        return ret;
    }
    if (g_pfd_sddrv_info.inserted == 0) {
        return -0x21;
    }
    if (g_pfd_sddrv_info.reset_done != 0) {
        return -0x21;
    }
    ret = ISD_WriteBlock(g_pfd_sddrv_info.dev, lba, g_pfd_sddrv_buf, 1);
    if (ret != 0) {
        OSReport("ERR Failed to write BPB fields. ISD_WriteBlock()\n");
        return -0x24;
    }
    ret = pfd_sddrv_store_mbr_buf(&mbp, g_pfd_sddrv_buf);
    if (ret != 0) {
        OSReport("ERR Failed to store MBR values to buf. pfd_sddrv_store_mbr_buf()\n");
        return ret;
    }
    if (g_pfd_sddrv_info.inserted == 0) {
        return -0x21;
    }
    if (g_pfd_sddrv_info.reset_done != 0) {
        return -0x21;
    }
    ret = ISD_WriteBlock(g_pfd_sddrv_info.dev, 0, g_pfd_sddrv_buf, 1);
    if (ret != 0) {
        OSReport("ERR Failed to write MBR fields. ISD_WriteBlock()\n");
        return -0x24;
    }
    return 0;
}

static s32 pfd_sddrv_calc_fat32_mbr_bpb(SDDRV_MBR_BPB* p) {
    const SDDRV_SIZE_DEPEND* p_tbl;
    SDDRV_FIELDS v;
    u32 total;
    u32 total2;
    u32 fat_sz;
    u32 fat_sz2;
    u32 clusters;
    u32 nc;
    u32 nf;
    u32 span;
    u32 fat_area;
    u32 acc2;
    s32 i;
    s32 err;
    OSCalendarTime cal;
    u32 date;
    u32 time_v;

    if (p == NULL) {
        return -0x1e;
    }
    pf_memset(&v, 0, 0x10);
    p_tbl = sddrv_size_depend_tbl;
    total = p->field_1C;
    for (i = 0; i < 14; i++) {
        if (p_tbl->cap_lo < total) {
            if (p_tbl->cap_hi >= total) { v.f8 = sddrv_size_depend_tbl[i].field_08; v.fC = sddrv_size_depend_tbl[i].field_0C; v.f10 = sddrv_size_depend_tbl[i].field_10; v.f14 = sddrv_size_depend_tbl[i].field_14; break; }
        }
        p_tbl++;
    }
    err = (i == 14) ? -0x1e : 0;
    if (err != 0) {
        OSReport("ERR Failed to get values with total sectors. pfd_sddrv_get_value_with_total_sectors()\n");
        return err;
    }
    p->field_08 = v.f14;
    total = p->field_1C;
    clusters = total / v.f14;
    nf = clusters >> 7;
    if (((clusters << 5) & 0x7E0) != 0) {
        nf++;
    }
    fat_sz = nf;
    fat_sz2 = nf * 2;
    total2 = total - 0x2000;
    while (fat_sz != 0) {
        span = 0x2000;
        fat_area = span - fat_sz2;
        while (fat_area <= 0) {
            span += 0x2000;
            fat_area += 0x2000;
        }
        if (fat_area < 9) {
            fat_area += 0x2000;
        }
        acc2 = fat_area + fat_sz2;
        for (;;) {
            nc = (total2 - acc2) / v.f14 + 2;
            nf = nc >> 7;
            if (((nc << 5) & 0x7E0) != 0) {
                nf++;
            }
            if (nf <= fat_sz) {
                break;
            }
            fat_area += 0x2000;
            acc2 += 0x2000;
        }
        if (nf == fat_sz) {
            break;
        }
        fat_sz2 -= 2;
        fat_sz--;
    }
    if (fat_sz == 0) {
        return -0x1f;
    }
    p->field_0C = fat_sz;
    p->field_18 = fat_area;
    p->field_00 = 0x2000;
    p->field_04 = p->field_1C - 0x2000;
    OSTicksToCalendarTime(OSGetTime(), &cal);
    date = (cal.mday & 0x1F) | ((cal.mon << 5) & 0x1E0) | (((cal.year - 0x76C) << 9) & 0xFE00);
    time_v = (cal.sec & 0x1F) | ((cal.min << 5) & 0x7E0) | ((cal.hour << 0xB) & 0xF800);
    p->field_10 = (date << 0x10) + time_v;
    return 0;
}

static s32 pfd_sddrv_store_fat32_mbr_buf(SDDRV_MBR_BPB* p, u8* buf) {
    SDDRV_FIELDS v;
    u32 total;
    u16 cyl1;
    u16 sec1;
    u16 cyl2;
    u16 sec2;
    u8 head1;
    u8 head2;
    u8 type;
    u32 end;
    u32 hps;
    s32 i;
    s32 err;
    const SDDRV_SIZE_DEPEND* p_tbl;

    if (p == NULL || buf == NULL) {
        return -0x1e;
    }
    pf_memset(&v, 0, 0x10);
    p_tbl = sddrv_size_depend_tbl;
    total = p->field_1C;
    for (i = 0; i < 14; i++) {
        if (p_tbl->cap_lo < total) {
            if (p_tbl->cap_hi >= total) { v.f8 = sddrv_size_depend_tbl[i].field_08; v.fC = sddrv_size_depend_tbl[i].field_0C; v.f10 = sddrv_size_depend_tbl[i].field_10; v.f14 = sddrv_size_depend_tbl[i].field_14; break; }
        }
        p_tbl++;
    }
    err = (i == 14) ? -0x1e : 0;
    if (err != 0) {
        OSReport("ERR Failed to get values with total sectors. pfd_sddrv_get_value_with_total_sectors()\n");
        return err;
    }
    if (p->field_04 == 0) {
        return -0x1e;
    }
    hps = v.fC * v.f10;
    if (p->field_00 > 0xFB0400) {
        head1 = 0xFE;
        sec1 = 0x3F;
        cyl1 = 0x3FF;
    } else {
        sec1 = (u16)(p->field_00 - (p->field_00 / v.f10) * v.f10 + 1);
        cyl1 = (u16)(p->field_00 / hps);
        head1 = (u8)((p->field_00 - cyl1 * hps) / v.f10);
    }
    if (p->field_1C > 0xFB0400) {
        head2 = 0xFE;
        sec2 = 0x3F;
        cyl2 = 0x3FF;
        type = 0xC;
    } else {
        end = p->field_1C - 1;
        sec2 = (u16)(end - (end / v.f10) * v.f10 + 1);
        cyl2 = (u16)(end / hps);
        head2 = (u8)((end - cyl2 * hps) / v.f10);
        type = 0xB;
    }
    pf_memset(buf, 0, 0x200);
    buf[0x1be] = 0;
    buf[0x1bf] = head1;
    SDDRV_LE16(buf, 0x1c0, ((cyl1 & 0xFF) << 8) | (sec1 & 0x3F) | ((cyl1 & 0x300) >> 2));
    buf[0x1c2] = type;
    buf[0x1c3] = head2;
    SDDRV_LE16(buf, 0x1c4, ((cyl2 & 0xFF) << 8) | (sec2 & 0x3F) | ((cyl2 & 0x300) >> 2));
    if (((u32)(buf + 0x1c6) & 3) != 0) {
        u32 v = p->field_00;
        buf[0x1c6] = (u8)v;
        buf[0x1c7] = (u8)(v >> 8);
        buf[0x1c8] = (u8)(v >> 0x10);
        buf[0x1c9] = (u8)(v >> 0x18);
    } else {
        u32 v = p->field_00;
        *(u32*)(buf + 0x1cc) = ((v >> 0x18) | ((v >> 8) & 0xFF00) | ((v << 8) & 0xFF0000) | (v << 0x18));
    }
    if (((u32)(buf + 0x1ca) & 3) != 0) {
        u32 v = p->field_04;
        buf[0x1ca] = (u8)v;
        buf[0x1cb] = (u8)(v >> 8);
        buf[0x1cc] = (u8)(v >> 0x10);
        buf[0x1cd] = (u8)(v >> 0x18);
    } else {
        u32 v = p->field_04;
        *(u32*)(buf + 0x1d0) = ((v >> 0x18) | ((v >> 8) & 0xFF00) | ((v << 8) & 0xFF0000) | (v << 0x18));
    }
    buf[0x1fe] = 0x55;
    buf[0x1ff] = 0xaa;
    return 0;
}

static s32 pfd_sddrv_store_fat32_fsi_buf(u8* buf) {
    pf_memset(buf, 0, 0x200);
    if (((u32)buf & 3) != 0) {
        buf[0] = 0x52;
        buf[1] = 0x52;
        buf[2] = 0x61;
        buf[3] = 0x41;
    } else {
        *(u32*)buf = 0x52526141;
    }
    if (((u32)(buf + 0x1e4) & 3) != 0) {
        buf[0x1e4] = 0x72;
        buf[0x1e5] = 0x72;
        buf[0x1e6] = 0x41;
        buf[0x1e7] = 0x61;
    } else {
        *(u32*)(buf + 0x1e4) = 0x72724161;
    }
    if (((u32)(buf + 0x1e8) & 3) != 0) {
        buf[0x1e8] = 0xff;
        buf[0x1e9] = 0xff;
        buf[0x1ea] = 0xff;
        buf[0x1eb] = 0xff;
    } else {
        *(u32*)(buf + 0x1e8) = 0xFFFFFFFF;
    }
    if (((u32)(buf + 0x1ec) & 3) != 0) {
        buf[0x1ec] = 0xff;
        buf[0x1ed] = 0xff;
        buf[0x1ee] = 0xff;
        buf[0x1ef] = 0xff;
    } else {
        *(u32*)(buf + 0x1ec) = 0xFFFFFFFF;
    }
    if (((u32)(buf + 0x1fc) & 3) != 0) {
        buf[0x1fc] = 0;
        buf[0x1fd] = 0;
        buf[0x1fe] = 0x55;
        buf[0x1ff] = 0xaa;
    } else {
        *(u32*)(buf + 0x1fc) = 0x000055AA;
    }
    return 0;
}

static s32 pfd_sddrv_store_fat32_bpb_buf(SDDRV_MBR_BPB* p, u8* buf) {
    SDDRV_FIELDS v;
    u32 total;
    s32 i;
    s32 err;
    const SDDRV_SIZE_DEPEND* p_tbl;

    if (p == NULL || buf == NULL) {
        return -0x1e;
    }
    pf_memset(&v, 0, 0x10);
    p_tbl = sddrv_size_depend_tbl;
    total = p->field_1C;
    for (i = 0; i < 14; i++) {
        if (p_tbl->cap_lo < total) {
            if (p_tbl->cap_hi >= total) { v.f8 = sddrv_size_depend_tbl[i].field_08; v.fC = sddrv_size_depend_tbl[i].field_0C; v.f10 = sddrv_size_depend_tbl[i].field_10; v.f14 = sddrv_size_depend_tbl[i].field_14; break; }
        }
        p_tbl++;
    }
    err = (i == 14) ? -0x1e : 0;
    if (err != 0) {
        OSReport("ERR Failed to get values with total sectors. pfd_sddrv_get_value_with_total_sectors()\n");
        return err;
    }
    pf_memset(buf, 0, 0x200);
    if (buf + 3 != NULL && "        " != NULL) {
        buf[3] = "        "[0];
        buf[4] = "        "[1];
        buf[5] = "        "[2];
        buf[6] = "        "[3];
        buf[7] = "        "[4];
        buf[8] = "        "[5];
        buf[9] = "        "[6];
        buf[10] = "        "[7];
    }
    if (buf + 0x47 != NULL && "NO NAME    " != NULL) {
        buf[0x47] = "NO NAME    "[0];
        buf[0x48] = "NO NAME    "[1];
        buf[0x49] = "NO NAME    "[2];
        buf[0x4a] = "NO NAME    "[3];
        buf[0x4b] = "NO NAME    "[4];
        buf[0x4c] = "NO NAME    "[5];
        buf[0x4d] = "NO NAME    "[6];
        buf[0x4e] = "NO NAME    "[7];
        buf[0x4f] = "NO NAME    "[8];
        buf[0x50] = "NO NAME    "[9];
        buf[0x51] = "NO NAME    "[10];
    }
    if (buf + 0x52 != NULL && "FAT32   " != NULL) {
        buf[0x52] = "FAT32   "[0];
        buf[0x53] = "FAT32   "[1];
        buf[0x54] = "FAT32   "[2];
        buf[0x55] = "FAT32   "[3];
        buf[0x56] = "FAT32   "[4];
        buf[0x57] = "FAT32   "[5];
        buf[0x58] = "FAT32   "[6];
        buf[0x59] = "FAT32   "[7];
    }
    buf[0] = 0xeb;
    buf[1] = 0;
    buf[2] = 0x90;
    if (((u32)(buf + 0xb) & 1) != 0) {
        buf[0xb] = 0;
        buf[0xc] = 2;
    } else {
        *(u16*)(buf + 0xc) = 2;
    }
    buf[0xd] = p->field_08;
    if (((u32)(buf + 0xe) & 1) != 0) {
        buf[0xe] = (u8)p->field_18;
        buf[0xf] = (u8)(p->field_18 >> 8);
    } else {
        __sthbrx(p->field_18, buf + 0xe, 0);
    }
    buf[0x10] = 2;
    if (((u32)(buf + 0x11) & 1) != 0) {
        buf[0x11] = 0;
        buf[0x12] = 0;
    } else {
        *(u16*)(buf + 0x12) = 0;
    }
    if (((u32)(buf + 0x13) & 1) != 0) {
        buf[0x13] = 0;
        buf[0x14] = 0;
    } else {
        *(u16*)(buf + 0x14) = 0;
    }
    buf[0x15] = 0xf8;
    if (((u32)(buf + 0x16) & 1) != 0) {
        buf[0x16] = 0;
        buf[0x17] = 0;
    } else {
        *(u16*)(buf + 0x16) = 0;
    }
    SDDRV_LE16(buf, 0x18, v.f10);
    SDDRV_LE16(buf, 0x1a, v.fC);
    if (((u32)(buf + 0x1c) & 3) != 0) {
        buf[0x1c] = (u8)p->field_00;
        buf[0x1d] = (u8)(p->field_00 >> 8);
        buf[0x1e] = (u8)(p->field_00 >> 0x10);
        buf[0x1f] = (u8)(p->field_00 >> 0x18);
    } else {
        *(u32*)(buf + 0x1c) = ((p->field_00 >> 0x18) | ((p->field_00 >> 8) & 0xFF00) | ((p->field_00 << 8) & 0xFF0000) | (p->field_00 << 0x18));
    }
    if (((u32)(buf + 0x20) & 3) != 0) {
        u32 v = p->field_04;
        buf[0x20] = (u8)v;
        buf[0x21] = (u8)(v >> 8);
        buf[0x22] = (u8)(v >> 0x10);
        buf[0x23] = (u8)(v >> 0x18);
    } else {
        u32 v = p->field_04;
        *(u32*)(buf + 0x20) = ((v >> 0x18) | ((v >> 8) & 0xFF00) | ((v << 8) & 0xFF0000) | (v << 0x18));
    }
    if (((u32)(buf + 0x24) & 3) != 0) {
        u32 v = p->field_0C;
        buf[0x24] = (u8)v;
        buf[0x25] = (u8)(v >> 8);
        buf[0x26] = (u8)(v >> 0x10);
        buf[0x27] = (u8)(v >> 0x18);
    } else {
        u32 v = p->field_0C;
        *(u32*)(buf + 0x24) = ((v >> 0x18) | ((v >> 8) & 0xFF00) | ((v << 8) & 0xFF0000) | (v << 0x18));
    }
    if (((u32)(buf + 0x28) & 1) != 0) {
        buf[0x28] = 0;
        buf[0x29] = 0;
    } else {
        *(u16*)(buf + 0x28) = 0;
    }
    if (((u32)(buf + 0x2a) & 1) != 0) {
        buf[0x2a] = 0;
        buf[0x2b] = 0;
    } else {
        *(u16*)(buf + 0x2a) = 0;
    }
    if (((u32)(buf + 0x2c) & 3) != 0) {
        buf[0x2c] = 2;
        buf[0x2d] = 0;
        buf[0x2e] = 0;
        buf[0x2f] = 0;
    } else {
        *(u32*)(buf + 0x2c) = 0x2000000;
    }
    if (((u32)(buf + 0x30) & 1) != 0) {
        buf[0x30] = 1;
        buf[0x31] = 0;
    } else {
        *(u16*)(buf + 0x30) = 0x100;
    }
    if (((u32)(buf + 0x32) & 1) != 0) {
        buf[0x32] = 6;
        buf[0x33] = 0;
    } else {
        *(u16*)(buf + 0x32) = 0x600;
    }
    buf[0x40] = 0x80;
    buf[0x42] = 0x29;
    if (((u32)(buf + 0x43) & 3) != 0) {
        u32 v = p->field_10;
        buf[0x43] = (u8)v;
        buf[0x44] = (u8)(v >> 8);
        buf[0x45] = (u8)(v >> 0x10);
        buf[0x46] = (u8)(v >> 0x18);
    } else {
        u32 v = p->field_10;
        *(u32*)(buf + 0x4c) = ((v >> 0x18) | ((v >> 8) & 0xFF00) | ((v << 8) & 0xFF0000) | (v << 0x18));
    }
    buf[0x1fe] = 0x55;
    buf[0x1ff] = 0xaa;
    return 0;
}

s32 pfd_sddrv_build_fat32_mbr_bpb(u32 total_sectors) {
    SDDRV_MBR_BPB mbp;
    s32 ret;

    pf_memset(&mbp, 0, 0x20);
    mbp.field_1C = total_sectors;
    ret = pfd_sddrv_calc_fat32_mbr_bpb(&mbp);
    if (ret != 0) {
        OSReport("ERR Failed to calculate MBR and BPB values. pfd_sddrv_calc_fat32_mbr_bpb()\n");
        return ret;
    }
    ret = pfd_sddrv_store_fat32_bpb_buf(&mbp, g_pfd_sddrv_buf);
    if (ret != 0) {
        OSReport("ERR Failed to store BPB values to buf. pfd_sddrv_store_fat32_bpb_buf()\n");
        return ret;
    }
    if (g_pfd_sddrv_info.inserted == 0) {
        return -0x21;
    }
    if (g_pfd_sddrv_info.reset_done != 0) {
        return -0x21;
    }
    ret = ISD_WriteBlock(g_pfd_sddrv_info.dev, mbp.field_00, g_pfd_sddrv_buf, 1);
    if (ret != 0) {
        OSReport("ERR Failed to write BPB fields. ISD_WriteBlock()\n");
        return -0x24;
    }
    ret = ISD_WriteBlock(g_pfd_sddrv_info.dev, mbp.field_00 + 6, g_pfd_sddrv_buf, 1);
    if (ret != 0) {
        OSReport("ERR Failed to write BPB fields. ISD_WriteBlock()\n");
        return -0x24;
    }
    ret = pfd_sddrv_store_fat32_fsi_buf(g_pfd_sddrv_buf);
    if (ret != 0) {
        OSReport("ERR Failed to store FSInfo values to buf. pfd_sddrv_store_fat32_fsi_buf()\n");
        return ret;
    }
    if (g_pfd_sddrv_info.inserted == 0) {
        return -0x21;
    }
    if (g_pfd_sddrv_info.reset_done != 0) {
        return -0x21;
    }
    ret = ISD_WriteBlock(g_pfd_sddrv_info.dev, mbp.field_00 + 1, g_pfd_sddrv_buf, 1);
    if (ret != 0) {
        OSReport("ERR Failed to write BPB fields. ISD_WriteBlock()\n");
        return -0x24;
    }
    ret = ISD_WriteBlock(g_pfd_sddrv_info.dev, mbp.field_00 + 7, g_pfd_sddrv_buf, 1);
    if (ret != 0) {
        OSReport("ERR Failed to write BPB fields. ISD_WriteBlock()\n");
        return -0x24;
    }
    pf_memset(g_pfd_sddrv_buf, 0, 0x200);
    if (((u32)(g_pfd_sddrv_buf + 0x1fe) & 1) != 0) {
        g_pfd_sddrv_buf[0x1fe] = 0x55;
        g_pfd_sddrv_buf[0x1ff] = 0xaa;
    } else {
        *(u16*)(g_pfd_sddrv_buf + 0x1fe) = 0x55AA;
    }
    if (g_pfd_sddrv_info.inserted == 0) {
        return -0x21;
    }
    if (g_pfd_sddrv_info.reset_done != 0) {
        return -0x21;
    }
    ret = ISD_WriteBlock(g_pfd_sddrv_info.dev, mbp.field_00 + 2, g_pfd_sddrv_buf, 1);
    if (ret != 0) {
        OSReport("ERR Failed to write BPB fields. ISD_WriteBlock()\n");
        return -0x24;
    }
    ret = ISD_WriteBlock(g_pfd_sddrv_info.dev, mbp.field_00 + 8, g_pfd_sddrv_buf, 1);
    if (ret != 0) {
        OSReport("ERR Failed to write BPB fields. ISD_WriteBlock()\n");
        return -0x24;
    }
    ret = pfd_sddrv_store_fat32_mbr_buf(&mbp, g_pfd_sddrv_buf);
    if (ret != 0) {
        OSReport("ERR Failed to store MBR values to buf. pfd_sddrv_store_mbr_buf()\n");
        return ret;
    }
    if (g_pfd_sddrv_info.inserted == 0) {
        return -0x21;
    }
    if (g_pfd_sddrv_info.reset_done != 0) {
        return -0x21;
    }
    ret = ISD_WriteBlock(g_pfd_sddrv_info.dev, 0, g_pfd_sddrv_buf, 1);
    if (ret != 0) {
        OSReport("ERR Failed to write MBR fields. ISD_WriteBlock()\n");
        return -0x24;
    }
    return 0;
}

s32 pfd_sddrv_full_format(void) {
    u32 status;
    u32 total_sectors;
    u16 bps;
    s32 ret;
    s32 ret2;
    u32 i;
    u32 type;

    i = 0;
    if (g_pfd_sddrv_info.inserted == 0) {
        return -0x21;
    }
    for (;;) {
        ret2 = ISD_ResetDevice(g_pfd_sddrv_info.dev);
        if (ret2 == 0) {
            g_pfd_sddrv_info.reset_done = 0;
            break;
        }
        OSReport("ERROR Failed to SD Card Reset [ret = 0x%x]. pfd_sddrv_full_format()\n", ret2);
        i++;
        if (i >= 5) {
            break;
        }
    }
    if (i == 5) {
        return -0x26;
    }
    if (g_pfd_sddrv_info.reset_done != 0) {
        return -0x21;
    }
    ret = ISD_GetDeviceStatus(g_pfd_sddrv_info.dev, &status);
    if (ret != 0) {
        OSReport("ERR Failed to get sd card status. [ret = 0x%x]\n", ret);
        return -0x27;
    }
    if ((status & 4) != 0) {
        return -0x20;
    }
    ret = pfd_sddrv_get_total_sectors(&total_sectors, &bps);
    if (ret != 0) {
        OSReport("ERR Failed to get total sectors. pfd_sddrv_get_total_sectors()\n", ret);
        return ret;
    }
    type = status & 0x10000;
    if (type != 0) {
        if ((status & 0x100000) != 0) {
            goto fat32;
        }
        if (total_sectors > 0x400000) {
            return -0x22;
        }
        ret = pfd_sddrv_build_mbr_bpb(total_sectors);
    } else {
fat32:
        if (type == 0 || (status & 0x100000) == 0) {
            return -0x1f;
        }
        if (total_sectors > 0x4000000) {
            return -0x22;
        }
        ret = pfd_sddrv_build_fat32_mbr_bpb(total_sectors);
    }
    if (ret != 0) {
        OSReport("ERR Failed to build up and write MBR and BPB fields.\n");
        return ret;
    }
    return 0;
}
