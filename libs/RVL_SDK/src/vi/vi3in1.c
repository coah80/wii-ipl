#include <private/vi.h>
#include <revolution/os.h>
#include <revolution/vi.h>

static u16 gammaSet[31][17] = {
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0030, 0x0397, 0x3b49, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x1000, 0x1000, 0x1000, 0x1080, 0x1b80, 0xeb00},
    {0x0000, 0x0028, 0x005a, 0x02db, 0x0d8d, 0x3049, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x1000, 0x1040, 0x1100, 0x1880, 0x4200, 0xeb00},
    {0x0000, 0x007a, 0x023c, 0x076d, 0x129c, 0x2724, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x1000, 0x10c0, 0x1580, 0x2900, 0x6200, 0xeb00},
    {0x004e, 0x0199, 0x052d, 0x0b24, 0x1429, 0x20a4, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x1040, 0x12c0, 0x1dc0, 0x3b00, 0x78c0, 0xeb00},
    {0x00ec, 0x03d7, 0x0800, 0x0d9e, 0x143e, 0x1bdb, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x10c0, 0x16c0, 0x27c0, 0x4b80, 0x8980, 0xeb00},
    {0x0276, 0x0666, 0x0a96, 0x0ef3, 0x13ac, 0x1849, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x1200, 0x1c00, 0x3280, 0x59c0, 0x9600, 0xeb00},
    {0x04ec, 0x08f5, 0x0c96, 0x0fcf, 0x12c6, 0x1580, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x1400, 0x2200, 0x3cc0, 0x6640, 0x9fc0, 0xeb00},
    {0x0800, 0x0bae, 0x0e00, 0x1030, 0x11cb, 0x1349, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x1680, 0x28c0, 0x4680, 0x7100, 0xa780, 0xeb00},
    {0x0bb1, 0x0e14, 0x0f2d, 0x1018, 0x10e5, 0x1180, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x1980, 0x2f80, 0x4fc0, 0x7a00, 0xadc0, 0xeb00},
    {0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1020, 0x4060, 0x80a0, 0xeb00, 0x1000, 0x2000, 0x4000, 0x6000, 0x8000, 0xa000, 0xeb00},
    {0x14ec, 0x11c2, 0x1078, 0x0fb6, 0x0f2f, 0x0eb6, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x2100, 0x3cc0, 0x5fc0, 0x8900, 0xb780, 0xeb00},
    {0x19d8, 0x1333, 0x10d2, 0x0f6d, 0x0e5e, 0x0da4, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x2500, 0x4300, 0x66c0, 0x8f40, 0xbb40, 0xeb00},
    {0x1ec4, 0x147a, 0x110f, 0x0f0c, 0x0da1, 0x0cb6, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x2900, 0x4900, 0x6d40, 0x94c0, 0xbe80, 0xeb00},
    {0x2400, 0x1570, 0x110f, 0x0eaa, 0x0d0f, 0x0bdb, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x2d40, 0x4ec0, 0x7300, 0x9980, 0xc180, 0xeb00},
    {0x293b, 0x163d, 0x110f, 0x0e30, 0x0c7d, 0x0b24, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x3180, 0x5440, 0x7880, 0x9dc0, 0xc400, 0xeb00},
    {0x2e27, 0x170a, 0x10d2, 0x0de7, 0x0beb, 0x0a80, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x3580, 0x5980, 0x7d40, 0xa1c0, 0xc640, 0xeb00},
    {0x3362, 0x175c, 0x10d2, 0x0d6d, 0x0b6d, 0x09ed, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x39c0, 0x5e40, 0x8200, 0xa540, 0xc840, 0xeb00},
    {0x384e, 0x17ae, 0x10b4, 0x0d0c, 0x0af0, 0x096d, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x3dc0, 0x62c0, 0x8640, 0xa880, 0xca00, 0xeb00},
    {0x3d3b, 0x1800, 0x105a, 0x0cc3, 0x0a72, 0x0900, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x41c0, 0x6740, 0x8a00, 0xab80, 0xcb80, 0xeb00},
    {0x41d8, 0x1828, 0x103c, 0x0c49, 0x0a1f, 0x0892, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x4580, 0x6b40, 0x8dc0, 0xae00, 0xcd00, 0xeb00},
    {0x4676, 0x1851, 0x0fe1, 0x0c00, 0x09b6, 0x0836, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x4940, 0x6f40, 0x9100, 0xb080, 0xce40, 0xeb00},
    {0x4ac4, 0x187a, 0x0fa5, 0x0b9e, 0x0963, 0x07db, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x4cc0, 0x7300, 0x9440, 0xb2c0, 0xcf80, 0xeb00},
    {0x4f13, 0x1851, 0x0f69, 0x0b6d, 0x090f, 0x0780, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x5040, 0x7640, 0x9700, 0xb500, 0xd0c0, 0xeb00},
    {0x5313, 0x187a, 0x0f0f, 0x0b24, 0x08bc, 0x0736, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x5380, 0x79c0, 0x99c0, 0xb700, 0xd1c0, 0xeb00},
    {0x5713, 0x1851, 0x0ef0, 0x0ac3, 0x087d, 0x06ed, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x56c0, 0x7cc0, 0x9c80, 0xb8c0, 0xd2c0, 0xeb00},
    {0x5b13, 0x1828, 0x0e96, 0x0a92, 0x0829, 0x06b6, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x5a00, 0x7fc0, 0x9ec0, 0xba80, 0xd380, 0xeb00},
    {0x5ec4, 0x1800, 0x0e78, 0x0a30, 0x0800, 0x066d, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x5d00, 0x8280, 0xa140, 0xbc00, 0xd480, 0xeb00},
    {0x6276, 0x17d7, 0x0e1e, 0x0a00, 0x07c1, 0x0636, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x6000, 0x8540, 0xa340, 0xbd80, 0xd540, 0xeb00},
    {0x65d8, 0x17ae, 0x0de1, 0x09cf, 0x0782, 0x0600, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x62c0, 0x87c0, 0xa540, 0xbf00, 0xd600, 0xeb00},
    {0x693b, 0x1785, 0x0da5, 0x0986, 0x0743, 0x05db, 0x101d, 0x3658, 0x82b3, 0xeb00, 0x1000, 0x6580, 0x8a40, 0xa740, 0xc040, 0xd680, 0xeb00}
};

static u8 VINtscACPType1[0x1a] = {
    0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1b, 0x1b, 0x24, 0x07, 0xf8,
    0x00, 0x00, 0x0f, 0x0f, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static u8 VINtscACPType2[0x1a] = {
    0x3e, 0x1d, 0x11, 0x25, 0x11, 0x01, 0x07, 0x00, 0x1b, 0x1b, 0x24, 0x07, 0xf8,
    0x00, 0x00, 0x0f, 0x0f, 0x60, 0x01, 0x0a, 0x00, 0x05, 0x04, 0x03, 0xff, 0x00
};

static u8 VINtscACPType3[0x1a] = {
    0x3e, 0x17, 0x15, 0x21, 0x15, 0x05, 0x05, 0x02, 0x1b, 0x1b, 0x24, 0x07, 0xf8,
    0x00, 0x00, 0x0f, 0x0f, 0x60, 0x01, 0x0a, 0x00, 0x05, 0x04, 0x03, 0xff, 0x00
};

static u8 VIPalACPType1[0x1a] = {
    0x36, 0x1a, 0x22, 0x2a, 0x22, 0x05, 0x02, 0x00, 0x1c, 0x3d, 0x14, 0x03, 0xfe,
    0x01, 0x54, 0xfe, 0x7e, 0x60, 0x00, 0x08, 0x00, 0x04, 0x07, 0x01, 0x55, 0x01
};

static u8 VIPalACPType2[0x1a] = {
    0x36, 0x1a, 0x22, 0x2a, 0x22, 0x05, 0x02, 0x00, 0x1c, 0x3d, 0x14, 0x03, 0xfe,
    0x01, 0x54, 0xfe, 0x7e, 0x60, 0x00, 0x08, 0x00, 0x04, 0x07, 0x01, 0x55, 0x01
};

static u8 VIPalACPType3[0x1a] = {
    0x36, 0x1a, 0x22, 0x2a, 0x22, 0x05, 0x02, 0x00, 0x1c, 0x3d, 0x14, 0x03, 0xfe,
    0x01, 0x54, 0xfe, 0x7e, 0x60, 0x00, 0x08, 0x00, 0x04, 0x07, 0x01, 0x55, 0x01
};

static u8 VIEurgb60ACPType1[0x1a] = {
    0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1b, 0x1b, 0x24, 0x07, 0xf8,
    0x00, 0x00, 0x1e, 0x1e, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
};

static u8 VIEurgb60ACPType2[0x1a] = {
    0x36, 0x1d, 0x11, 0x25, 0x11, 0x01, 0x07, 0x00, 0x1b, 0x1b, 0x24, 0x07, 0xf8,
    0x00, 0x00, 0x1e, 0x1e, 0x60, 0x01, 0x0a, 0x00, 0x05, 0x04, 0x03, 0xff, 0x01
};

static u8 VIEurgb60ACPType3[0x1a] = {
    0x36, 0x17, 0x15, 0x21, 0x15, 0x05, 0x05, 0x02, 0x1b, 0x1b, 0x24, 0x07, 0xf8,
    0x00, 0x00, 0x1e, 0x1e, 0x60, 0x01, 0x0a, 0x00, 0x05, 0x04, 0x03, 0xff, 0x01
};

static u8 VIMpalACPType1[0x1a] = {
    0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1b, 0x1b, 0x24, 0x07, 0xf8,
    0x00, 0x00, 0x0f, 0x0f, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static u8 VIMpalACPType2[0x1a] = {
    0x36, 0x1d, 0x11, 0x25, 0x11, 0x01, 0x07, 0x00, 0x1b, 0x1b, 0x24, 0x07, 0xf8,
    0x00, 0x00, 0x0f, 0x0f, 0x60, 0x01, 0x0a, 0x00, 0x05, 0x04, 0x03, 0xff, 0x00
};

static u8 VIMpalACPType3[0x1a] = {
    0x36, 0x17, 0x15, 0x21, 0x15, 0x05, 0x05, 0x02, 0x1b, 0x1b, 0x24, 0x07, 0xf8,
    0x00, 0x00, 0x0f, 0x0f, 0x60, 0x01, 0x0a, 0x00, 0x05, 0x04, 0x03, 0xff, 0x00
};

u8 VIProgressiveACPType[0x1a] = {
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


void __VISendI2CData(u8 dev, u8* data, u8 length);
void WaitMicroTime(u32 time);
void __VISetYUVSEL(u8 value);
void __VISetGammaImm(u16* gamma);
void __VISetRevolutionMode(void);
void __VISetRevolutionModeSimple(void);
void VISetMacrovision(s32 type);

static inline void VICopyACP(u8* destination, const u8* source) {
    u32 index;
    destination[0] = 0x40;
    for (index = 0; index < 0x1a; index++) {
        destination[index + 1] = source[index];
    }
}

#define COPY_ACP(dst, src) VICopyACP((dst), (src))

static u8 __wd0 = 0xff;
static u8 __wd1 = 0xff;
static u8 __wd2 = 0xff;
static u8 __gp1 = 0xff;
static u8 __gp2 = 0xff;
static u8 __gp3 = 0xff;
static u8 __gp4 = 0xff;
static u8 __cc1 = 0xff;
static u8 __cc2 = 0xff;
static u8 __cc3 = 0xff;
static u8 __cc4 = 0xff;
static u32 __tvType = 0xff;
static u8 __filter = 0xff;
u8 VIZeroACPType[0x1a];
static s32 Vdac_Flag_Region;
static s32 __type;
static s32 __gamma;
static s32 __level;
volatile u32 Vdac_Flag_Changed;

static void __VISetCCSEL(u8 flag) {
    u8 data[2];

    data[0] = 0x6a;
    data[1] = TRUE;
    __VISendI2CData(0xe0, data, sizeof(data));
    WaitMicroTime(2);
}

static void __VISetOverSampling(u8 flag) {
    u8 data[2];

    data[0] = 0x65;
    data[1] = TRUE;
    __VISendI2CData(0xe0, data, sizeof(data));
    WaitMicroTime(2);
}

void __VISetVolume(u8 wd0, u8 wd1) {
    u8 data[3];

    data[0] = 0x71;
    data[1] = wd0;
    data[2] = wd1;
    __VISendI2CData(0xe0, data, 3);
    WaitMicroTime(2);
}

// MWCC needs the separate region-store blocks in this dispatch.
void __VISetYUVSEL(u8 value) {
    s32 region = *(s32*)0x800000cc;
    u8 data[2];

    if (region != 2) {
        if (region < 2) {
            if (region == 0) {
                goto region0;
            }
            if (region >= 0) {
                goto region2;
            }
        } else {
            switch (region) {
            case 5:
                goto region2;
            default:
                goto regionDefault;
            }
        }
        goto regionDefault;
    }
    goto region1;
region2:
    Vdac_Flag_Region = 2;
    goto send;
region1:
    Vdac_Flag_Region = 1;
    goto send;
region0:
    Vdac_Flag_Region = 0;
    goto send;
regionDefault:
    Vdac_Flag_Region = 0;
    goto send;
send:
    data[0] = 1;
    data[1] = (value << 5) | Vdac_Flag_Region;
    __VISendI2CData(0xe0, data, 2);
    WaitMicroTime(2);
}

void __VISetFilter4EURGB60(u8 value) {
    u8 data[2];

    data[0] = 0x6e;
    data[1] = value;
    __VISendI2CData(0xe0, data, 2);
    WaitMicroTime(2);
}

void __VISetCGMS(void) {
    u8 data[3];

    data[0] = 5;
    data[1] = (__wd1 & 0xf) << 2 | __wd0 & 3;
    data[2] = __wd2;
    __VISendI2CData(0xe0, data, 3);
    WaitMicroTime(2);
}

void __VISetWSS(void) {
    u8 data[3];

    data[0] = 8;
    data[1] = (__gp2 & 0xf) << 4 | __gp1 & 0xf;
    data[2] = (__gp4 & 7) << 3 | __gp3 & 7;
    __VISendI2CData(0xe0, data, 3);
    WaitMicroTime(2);
}

void __VISetClosedCaption(void) {
    u8 data[5];

    data[0] = 0x7a;
    data[1] = __cc1 & 0x7f;
    data[2] = __cc2 & 0x7f;
    data[3] = __cc3 & 0x7f;
    data[4] = __cc4 & 0x7f;
    __VISendI2CData(0xe0, data, 5);
    WaitMicroTime(2);
}

typedef const u8* __VIMacrovisionImm;
static void __VISetMacrovisionImm(__VIMacrovisionImm macrovisionImm)
{
    u8 data[0x1a + 1];
    u8 i;

    data[0] = 0x40;
    for (i = 1; i < sizeof(data); i++) {
        data[i] = macrovisionImm[i - 1];
    }
    __VISendI2CData(0xe0, data, sizeof(data));
    WaitMicroTime(2);
}

void __VISetMacrovision(void) {
    switch (__type) {
    case 2:
        switch (__tvType) {
        case 0: {
            __VISetMacrovisionImm(VINtscACPType1);
            break;
        }
        case 1: {
            __VISetMacrovisionImm(VIPalACPType1);
            break;
        }
        case 2: {
            __VISetMacrovisionImm(VIMpalACPType1);
            break;
        }
        case 5: {
            __VISetMacrovisionImm(VIEurgb60ACPType1);
            break;
        }
        }
        break;
    case 3:
        switch (__tvType) {
        case 0: {
            __VISetMacrovisionImm(VINtscACPType2);
            break;
        }
        case 1: {
            __VISetMacrovisionImm(VIPalACPType2);
            break;
        }
        case 2: {
            __VISetMacrovisionImm(VIMpalACPType2);
            break;
        }
        case 5: {
            __VISetMacrovisionImm(VIEurgb60ACPType2);
            break;
        }
        }
        break;
    case 4:
        switch (__tvType) {
        case 0: {
            __VISetMacrovisionImm(VINtscACPType3);
            break;
        }
        case 1: {
            __VISetMacrovisionImm(VIPalACPType3);
            break;
        }
        case 2: {
            __VISetMacrovisionImm(VIMpalACPType3);
            break;
        }
        case 5: {
            __VISetMacrovisionImm(VIEurgb60ACPType3);
            break;
        }
        }
        break;
    case 1: {
        __VISetMacrovisionImm(VIZeroACPType);
        break;
    }
    }
}

void VISetCGMS(u8 wd0, u8 wd1, u8 wd2) {
    if (__wd0 != wd0 || __wd1 != wd1 || __wd2 != wd2) {
        __wd0 = wd0;
        __wd1 = wd1;
        __wd2 = wd2;
        Vdac_Flag_Changed |= 1;
    }
}

void VISetMacrovision(s32 type) {
    u32 tvFormat;
    u8 mode = 0;
    u8 volume = 0;
    u8 wd0 = __wd0;
    u8 wd1 = __wd1;
    u8 wd2 = __wd2;

    switch (type) {
        case 1:
            mode = 0;
            volume = 0;
            break;
        case 2:
            mode = 2;
            volume = 3;
            wd1 = 0;
            break;
        case 3:
            mode = 1;
            volume = 3;
            wd1 = 0;
            break;
        case 4:
            mode = 3;
            volume = 3;
            wd1 = 0;
            break;
        default:
            break;
    }
    wd2 = wd2 & 0xF0;
    wd2 = (wd2 | (mode << 2)) | volume;
    VISetCGMS(wd0, wd1, wd2);

    tvFormat = VIGetTvFormat();
    if ((__type != type) || (__tvType != tvFormat)) {
        __type = type;
        __tvType = tvFormat;
        Vdac_Flag_Changed |= 8;
    }
}

void __VISetGammaImm(u16* gamma) {
    u8 data[0x23];

    data[0] = 0x10;
    data[1] = ((u32)gamma[0] << 16) >> 24;
    data[2] = gamma[0];
    data[3] = ((u32)gamma[1] << 16) >> 24;
    data[4] = gamma[1];
    data[5] = ((u32)gamma[2] << 16) >> 24;
    data[6] = gamma[2];
    data[7] = ((u32)gamma[3] << 16) >> 24;
    data[8] = gamma[3];
    data[9] = ((u32)gamma[4] << 16) >> 24;
    data[10] = gamma[4];
    data[11] = ((u32)gamma[5] << 16) >> 24;
    data[12] = gamma[5];
    data[13] = ((u8*)gamma)[12];
    data[14] = ((u8*)gamma)[13];
    data[15] = ((u8*)gamma)[14];
    data[16] = ((u8*)gamma)[15];
    data[17] = ((u8*)gamma)[16];
    data[18] = ((u8*)gamma)[17];
    data[19] = ((u8*)gamma)[18];
    data[20] = ((u32)gamma[10] << 16) >> 24;
    data[21] = gamma[10] & 0xc0;
    data[22] = ((u32)gamma[11] << 16) >> 24;
    data[23] = gamma[11] & 0xc0;
    data[24] = ((u32)gamma[12] << 16) >> 24;
    data[25] = gamma[12] & 0xc0;
    data[26] = ((u32)gamma[13] << 16) >> 24;
    data[27] = gamma[13] & 0xc0;
    data[28] = ((u32)gamma[14] << 16) >> 24;
    data[29] = gamma[14] & 0xc0;
    data[30] = ((u32)gamma[15] << 16) >> 24;
    data[31] = gamma[15] & 0xc0;
    data[32] = ((u32)gamma[16] << 16) >> 24;
    data[33] = gamma[16] & 0xc0;
    __VISendI2CData(0xe0, data, 0x22);
    WaitMicroTime(2);
}
void __VISetGamma(void) {
    __VISetGammaImm(gammaSet[__gamma]);
}

void __VISetTrapFilter(void) {
    u8 data[2];

    data[0] = 3;
    if (__filter == 1) {
        data[1] = 0;
    } else {
        data[1] = 1;
    }
    __VISendI2CData(0xe0, data, 2);
    WaitMicroTime(2);
}

void VISetTrapFilter(BOOL filter) {
    if (__filter == (u32)filter) {
        return;
    }
    __filter = filter;
    Vdac_Flag_Changed |= 0x20;
}

void __VISetRGBOverDrive(void) {
    u8 data[2];

    if (Vdac_Flag_Region == 3) {
        data[0] = 10;
        data[1] = __level << 1 | 1;
        __VISendI2CData(0xe0, data, 2);
        WaitMicroTime(2);
    } else {
        data[0] = 10;
        data[1] = 0;
        __VISendI2CData(0xe0, data, 2);
        WaitMicroTime(2);
    }
}

void VISetRGBModeImm(void) {
    Vdac_Flag_Changed |= 0x80;
}

void __VISetRGBModeImm(void) {
    u8 data[2];

    Vdac_Flag_Region = 3;
    data[0] = 1;
    data[1] = 3;
    __VISendI2CData(0xe0, data, 2);
    WaitMicroTime(2);
}

void __VISetRevolutionMode(void) {
    u8 resetCommand[2];
    u8 powerCommand[2];
    u8 clockCommand[2];
    u8 outputCommand[2];
    u8 volumeCommand[3];
    u8 syncCommand[2];
    u8 enableCommand[2];

    resetCommand[0] = 4;
    resetCommand[1] = 0;
    __VISendI2CData(0xe0, resetCommand, 2);
    WaitMicroTime(2);
    powerCommand[0] = 0x6a;
    powerCommand[1] = 1;
    __VISendI2CData(0xe0, powerCommand, 2);
    WaitMicroTime(2);
    clockCommand[0] = 0x65;
    clockCommand[1] = 1;
    __VISendI2CData(0xe0, clockCommand, 2);
    WaitMicroTime(2);
    __VISetYUVSEL(VIGetDTVStatus());
    outputCommand[0] = 0;
    outputCommand[1] = 0;
    __VISendI2CData(0xe0, outputCommand, 2);
    WaitMicroTime(2);
    volumeCommand[0] = 0x71;
    volumeCommand[1] = 0x8e;
    volumeCommand[2] = 0x8e;
    __VISendI2CData(0xe0, volumeCommand, 3);
    WaitMicroTime(2);
    syncCommand[0] = 2;
    syncCommand[1] = 7;
    __VISendI2CData(0xe0, syncCommand, 2);
    WaitMicroTime(2);
    if ((__wd0 != 0) || (__wd1 != 0) || (__wd2 != 0)) {
        __wd0 = 0;
        __wd1 = 0;
        __wd2 = 0;
        Vdac_Flag_Changed |= 1;
    }
    if ((__gp1 != 0) || (__gp2 != 0) || (__gp3 != 0) || (__gp4 != 0)) {
        __gp1 = 0;
        __gp2 = 0;
        __gp3 = 0;
        __gp4 = 0;
        Vdac_Flag_Changed |= 2;
    }
    if ((__cc1 != 0) || (__cc2 != 0) || (__cc3 != 0) || (__cc4 != 0)) {
        __cc1 = 0;
        __cc2 = 0;
        __cc3 = 0;
        __cc4 = 0;
        Vdac_Flag_Changed |= 4;
    }
    VISetMacrovision(1);
    if (__filter != 0) {
        __filter = 0;
        Vdac_Flag_Changed |= 0x20;
    }
    if (__level != 0) {
        __level = 0;
        Vdac_Flag_Changed |= 0x40;
    }
    if (__gamma != 10) {
        __gamma = 10;
        Vdac_Flag_Changed |= 0x10;
    }
    VIFlush();
    VIWaitForRetrace();
    enableCommand[0] = 4;
    enableCommand[1] = 1;
    __VISendI2CData(0xe0, enableCommand, 2);
    WaitMicroTime(2);
}

void __VISetTiming(s32 timing) {
    u8 data[2];

    data[0] = 0;
    data[1] = (u8)timing;
    __VISendI2CData(0xe0, data, sizeof(data));
    WaitMicroTime(2);
}

void __VISetVBICtrl(u8 arg0, u8 arg1, u8 arg2) {
    u8 data[2];

    data[0] = 2;
    data[1] = (~arg2 & 1) | (((~arg1 & 1) << 2) | ((~arg0 & 1) << 1));
    __VISendI2CData(0xe0, data, sizeof(data));
    WaitMicroTime(2);
}

void __VISetCGMSClear(void) {
    __wd0 = 0;
    __wd1 = 0;
    __wd2 = 0;
    __VISetCGMS();
}

void VISetWSS(u8 gp1, u8 gp2, u8 gp3, u8 gp4) {
    if (__gp1 != gp1 || __gp2 != gp2 || __gp3 != gp3 || __gp4 != gp4) {
        __gp1 = gp1;
        __gp2 = gp2;
        __gp3 = gp3;
        __gp4 = gp4;
        Vdac_Flag_Changed |= 2;
    }
}

void VISetClosedCaption(u8 cc1, u8 cc2, u8 cc3, u8 cc4) {
    if (__cc1 != cc1 || __cc2 != cc2 || __cc3 != cc3 || __cc4 != cc4) {
        __cc1 = cc1;
        __cc2 = cc2;
        __cc3 = cc3;
        __cc4 = cc4;
        Vdac_Flag_Changed |= 4;
    }
}

void VISetRGBOverDrive(s32 level) {
    if (__level != level) {
        __level = level;
        Vdac_Flag_Changed |= 0x40;
    }
}

void __VISetTrapFilterImm(u8 flag) {
    u8 data[2];

    data[0] = 3;
    if (flag == TRUE) {
        data[1] = 0;
    } else {
        data[1] = 1;
    }
    __VISendI2CData(0xe0, data, sizeof(data));
    WaitMicroTime(2);
}

void __VISetRevolutionModeSimple(void) {
    u32 dtvStatus;

    __VISetCCSEL(TRUE);
    __VISetOverSampling(TRUE);
    dtvStatus = VIGetDTVStatus();
    __VISetYUVSEL(dtvStatus);
    __VISetTiming(0);
    __VISetVolume(142, 142);
    __VISetVBICtrl(0, 0, 0);
    __VISetCGMSClear();
    VISetWSS(0, 0, 0, 0);
    __VISetWSS();
    VISetClosedCaption(0, 0, 0, 0);
    __VISetClosedCaption();
    __VISetMacrovisionImm(VIZeroACPType);
    VISetRGBOverDrive(0);
    __VISetRGBOverDrive();
    __VISetTrapFilterImm(0);
    __VISetGammaImm(gammaSet[10]);
}

void __VIInit3in1(VITVMode mode) {
    u8 data[2];
    s32 value = (u32)mode >> 2;
    u32 flag;

    switch (value) {
        case 0:
            flag = 0;
            break;
        case 2:
            flag = 1;
            break;
        case 1:
        case 5:
            flag = 2;
            break;
        default:
            flag = 0;
            break;
    }
    Vdac_Flag_Region = flag;
    data[0] = 1;
    data[1] = flag;
    __VISendI2CData(0xe0, data, 2);
    WaitMicroTime(2);
    __VISetRevolutionMode();
}
