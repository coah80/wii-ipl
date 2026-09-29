#include <revolution/os.h>
#include <revolution/soex.h>

#include <private/ios.h>

#include <string.h>

enum {
    SO_SUCCESS = 0,
    SO_EINVAL = -28,
    SO_ENOMEM = -49,
};

void* SOiAlloc(u32 name, s32 size);
void SOiFree(u32 name, void* ptr, s32 size);
int SOiPrepare(const char* funcName, s32* pRmId);
int SOiConclude(const char* funcName, int result);
int SOiPrepareTempRm(const char* funcName, s32* pRmId, int* pIsTempRm);
int SOiConcludeTempRm(const char* funcName, int result, int isTempRm);

int SOGetSockOpt(int s, int level, int optname, void* optval, int* optlen) {
    s32 rmId;
    int result;
    s32* buf;

    if ((result = SOiPrepare(NULL, &rmId)) == SO_SUCCESS) {
        buf = (s32*)SOiAlloc(0xC, 0x20);
        if (buf == NULL) {
            result = SO_ENOMEM;
        } else {
            buf[0] = s;
            buf[1] = level;
            buf[2] = optname;
            result = IOS_Ioctl(rmId, 8, NULL, 0, buf, 0x18);
            if (result >= 0 && optlen != NULL) {
                if (*optlen >= buf[3]) {
                    if (optval != NULL) {
                        memcpy(optval, buf + 4, buf[3]);
                    }
                    *optlen = buf[3];
                } else {
                    *optlen = buf[3];
                    result = SO_EINVAL;
                }
            }
            SOiFree(0xC, buf, 0x20);
        }
        result = SOiConclude(NULL, result);
    }
    return result;
}

int SOSetSockOpt(int s, int level, int optname, const void* optval, int optlen) {
    s32 rmId;
    int result;
    s32* buf;

    if ((result = SOiPrepare(NULL, &rmId)) == SO_SUCCESS) {
        if (optlen < 0 || optlen > 0x14) {
            result = SO_EINVAL;
        } else {
            buf = (s32*)SOiAlloc(0xC, 0x40);
            if (buf == NULL) {
                result = SO_ENOMEM;
            } else {
                buf[0] = s;
                buf[1] = level;
                buf[2] = optname;
                buf[3] = optlen;
                if (optval != NULL) {
                    memcpy(buf + 4, optval, optlen);
                } else {
                    memset(buf + 4, 0, optlen);
                }
                result = IOS_Ioctl(rmId, 9, buf, 0x24, NULL, 0);
                SOiFree(0xC, buf, 0x40);
            }
        }
        result = SOiConclude(NULL, result);
    }
    return result;
}

int SOGetInterfaceOpt(void* unk, int level, int optname, void* optval,
                      int* optlen) {
    s32 rmId;
    int isTempRm;
    int result;
    u8* buf;
    u32 size;
    u8* p;
    s32* outlen;
    u8* data;
    s32 len;

    if ((result = SOiPrepareTempRm(NULL, &rmId, &isTempRm)) == SO_SUCCESS) {
        if (optname == 0x1001 || optname == 0x1002) {
            result = SO_EINVAL;
        } else {
            size = (((optlen == NULL || *optlen < 0) ? 0 : *optlen) + 0x7F) &
                   ~0x1F;
            buf = (u8*)SOiAlloc(0xC, size);
            if (buf == NULL) {
                result = SO_ENOMEM;
            } else {
                ((u32*)buf)[8] = level;
                p = buf + 0x20;
                outlen = (s32*)(p + 0x20);
                data = (u8*)(outlen + 8);
                *outlen =
                    (optlen == NULL || *optlen < 0) ? 0 : *optlen;
                ((u32*)buf)[9] = optname;
                ((IOSIoVector*)buf)[0].base = p;
                ((IOSIoVector*)buf)[0].length = 8;
                ((IOSIoVector*)buf)[1].base = data;
                ((IOSIoVector*)buf)[1].length =
                    (optlen == NULL || *optlen < 0) ? 0 : *optlen;
                ((IOSIoVector*)buf)[2].base = (u8*)outlen;
                ((IOSIoVector*)buf)[2].length = 4;
                result =
                    IOS_Ioctlv(rmId, 0x1C, 1, 2, (IOSIoVector*)buf);
                if (result >= 0 && optlen != NULL) {
                    if (*optlen >= *outlen) {
                        if (optval != NULL) {
                            memcpy(optval, data, *outlen);
                        }
                        *optlen = *outlen;
                    } else {
                        *optlen = *outlen;
                        result = SO_EINVAL;
                    }
                }
                SOiFree(0xC, buf, size);
            }
        }
        result = SOiConcludeTempRm(NULL, result, isTempRm);
    }
    return result;
}

int SOSetInterfaceOpt(void* unk, int level, int optname, const void* optval,
                      int optlen) {
    s32 rmId;
    int isTempRm;
    u32 size;
    int result;
    u8* buf;

    if ((result = SOiPrepareTempRm(NULL, &rmId, &isTempRm)) == SO_SUCCESS) {
        if (optname == 0x1001 || optname == 0x1002 || optlen < 0) {
            result = SO_EINVAL;
        } else {
            size = (optlen + 0x5F) & ~0x1F;
            buf = (u8*)SOiAlloc(0xC, size);
            if (buf == NULL) {
                result = SO_ENOMEM;
            } else {
                ((u32*)buf)[8] = level;
                ((u32*)buf)[9] = optname;
                if (optval != NULL) {
                    memcpy(buf + 0x40, optval, optlen);
                } else {
                    memset(buf + 0x40, 0, optlen);
                }
                ((IOSIoVector*)buf)[0].base = buf + 0x20;
                ((IOSIoVector*)buf)[0].length = 8;
                ((IOSIoVector*)buf)[1].base = buf + 0x40;
                ((IOSIoVector*)buf)[1].length = optlen;
                result =
                    IOS_Ioctlv(rmId, 0x1D, 2, 0, (IOSIoVector*)buf);
                SOiFree(0xC, buf, size);
            }
        }
        result = SOiConcludeTempRm(NULL, result, isTempRm);
    }
    return result;
}
