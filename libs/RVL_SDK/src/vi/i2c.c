#include <revolution/os.h>
#include <private/os/OSTime.h>
#include <private/bus.h>

static int __i2c_ident_flag = 1;
static u32 __i2c_ident_first;

#define I2C_OUT 0xCD8000C0
#define I2C_DIR 0xCD8000C4
#define I2C_IN 0xCD8000C8

static inline void delay(void) {
    OSTime start = __OSGetSystemTime();
    while (OSTicksToMicroseconds(__OSGetSystemTime() - start) < 2) {}
}

static inline void setData(int high) {
    if (high) {
        if (__i2c_ident_flag == 0) {
            BUSWrite32(I2C_OUT, BUSRead32(I2C_OUT) & ~0x8000);
        } else {
            BUSWrite32(I2C_OUT, (BUSRead32(I2C_OUT) & ~0x8000) | 0x8000);
        }
    } else {
        if (__i2c_ident_flag == 0) {
            BUSWrite32(I2C_OUT, (BUSRead32(I2C_OUT) & ~0x8000) | 0x8000);
        } else {
            BUSWrite32(I2C_OUT, BUSRead32(I2C_OUT) & ~0x8000);
        }
    }
}

static int sendSlaveAddr(u8 address) {
    int bit;
    if (__i2c_ident_flag == 0) {
        BUSWrite32(I2C_OUT, (BUSRead32(I2C_OUT) & ~0x8000) | 0x8000);
    } else {
        BUSWrite32(I2C_OUT, BUSRead32(I2C_OUT) & ~0x8000);
    }
    delay();
    BUSWrite32(I2C_OUT, BUSRead32(I2C_OUT) & ~0x4000);
    for (bit = 0; bit < 8; bit++) {
        setData(address & 0x80);
        delay();
        BUSWrite32(I2C_OUT, (BUSRead32(I2C_OUT) & ~0x4000) | 0x4000);
        delay();
        BUSWrite32(I2C_OUT, BUSRead32(I2C_OUT) & ~0x4000);
        address = (address & 0x7F) << 1;
    }
    BUSWrite32(I2C_DIR, (BUSRead32(I2C_DIR) & ~0x8000) | 0x4000);
    delay();
    BUSWrite32(I2C_OUT, (BUSRead32(I2C_OUT) & ~0x4000) | 0x4000);
    delay();
    if ((u32)__i2c_ident_flag == 1) {
        if ((BUSRead32(I2C_IN) >> 15) & 1) {
            return 0;
        }
    }
    setData(0);
    BUSWrite32(I2C_DIR, (BUSRead32(I2C_DIR) & ~0x8000) | 0xC000);
    BUSWrite32(I2C_OUT, BUSRead32(I2C_OUT) & ~0x4000);
    return 1;
}

int __VISendI2CData(u8 address, u8* data, int length) {
    int enabled;
    if (__i2c_ident_first == 0) {
        __i2c_ident_flag = 1;
        __i2c_ident_first = 1;
    }
    enabled = OSDisableInterrupts();
    BUSWrite32(I2C_DIR, (BUSRead32(I2C_DIR) & ~0x8000) | 0xC000);
    BUSWrite32(I2C_OUT, (BUSRead32(I2C_OUT) & ~0x4000) | 0x4000);
    setData(1);
    delay();
    delay();
    if (!sendSlaveAddr(address)) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    BUSWrite32(I2C_DIR, (BUSRead32(I2C_DIR) & ~0x8000) | 0xC000);
    while (length != 0) {
        int bit;
        u8 value = *data++;
        for (bit = 0; bit < 8; bit++) {
            setData(value & 0x80);
            delay();
            BUSWrite32(I2C_OUT, (BUSRead32(I2C_OUT) & ~0x4000) | 0x4000);
            delay();
            BUSWrite32(I2C_OUT, BUSRead32(I2C_OUT) & ~0x4000);
            value = (value & 0x7F) << 1;
        }
        BUSWrite32(I2C_DIR, (BUSRead32(I2C_DIR) & ~0x8000) | 0x4000);
        delay();
        BUSWrite32(I2C_OUT, (BUSRead32(I2C_OUT) & ~0x4000) | 0x4000);
        delay();
        if ((u32)__i2c_ident_flag == 1) {
            if ((BUSRead32(I2C_IN) >> 15) & 1) {
                OSRestoreInterrupts(enabled);
                return 0;
            }
        }
        setData(0);
        BUSWrite32(I2C_DIR, (BUSRead32(I2C_DIR) & ~0x8000) | 0xC000);
        BUSWrite32(I2C_OUT, BUSRead32(I2C_OUT) & ~0x4000);
        length--;
    }
    BUSWrite32(I2C_DIR, (BUSRead32(I2C_DIR) & ~0x8000) | 0xC000);
    setData(0);
    delay();
    BUSWrite32(I2C_OUT, (BUSRead32(I2C_OUT) & ~0x4000) | 0x4000);
    delay();
    setData(1);
    OSRestoreInterrupts(enabled);
    return 1;
}
