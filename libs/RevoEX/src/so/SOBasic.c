#include <revolution/os.h>
#include <revolution/soex.h>

#include <private/ios.h>
#include <private/os/OSTime.h>

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

typedef struct SOSysWork {
    SOAlloc allocFunc;
    SOFree freeFunc;
    s32 rmState;
    s32 rmFd;
    u32 unk10;
    s32 allocCount;
} SOSysWork;

enum {
    SO_SUCCESS = 0,
    SO_EFATAL = (s32)0x80000000,
    SO_EINVAL = -28,
    SO_ENOMEM = -49,
};

enum {
    NET_SO_SOCKET = 0xF,
};

typedef struct NETSoSocket {
    int af;
    int type;
    int protocol;
} NETSoSocket;

void* SOiAlloc(u32 name, s32 size);
void SOiFree(u32 name, void* ptr, s32 size);
int SOiPrepare(const char* funcName, s32* pRmId);
int SOiConclude(const char* funcName, int result);
int SOiPrepareTempRm(const char* funcName, s32* pRmId, int* pIsTempRm);
int SOiConcludeTempRm(const char* funcName, int result, int isTempRm);
SOSysWork* SOiGetSysWork(void);
int SOiIsInitialized(void);
int SOiIsBufferAddrCheck(void);

const char* __SOCKETVersion =
    "<< RVL_SDK - SOCKET \trelease build: Dec 12 2008 03:06:17 (0x4199_60831) >>";
static int soSocketRegistered[2];

static int RecvFrom(const char* funcName, int s, void* buf, int len, int flags, SOSockAddr* addr);
static int SendTo(const char* funcName, int s, const void* buf, int len, int flags,
                  const SOSockAddr* addr);

int SOSocket(int pf, int type, int protocol) {
    s32 rmId;
    NETSoSocket* soc;
    int result;

    if (!soSocketRegistered[0]) {
        OSRegisterVersion(__SOCKETVersion);
        soSocketRegistered[0] = 1;
    }

    if ((result = SOiPrepare(NULL, &rmId)) == SO_SUCCESS) {
        if (pf == 0x17) {
            result = -5;
        } else {
            soc = (NETSoSocket*)SOiAlloc(0xC, 0x20);
            if (soc == NULL) {
                result = SO_ENOMEM;
            } else {
                soc->af = pf;
                soc->type = type;
                soc->protocol = protocol;
                result = IOS_Ioctl(rmId, NET_SO_SOCKET, soc, 0xC, NULL, 0);
                SOiFree(0xC, soc, 0x20);
            }
        }
        result = SOiConclude(NULL, result);
    }
    return result;
}

int SOClose(int s) {
    s32 rmId;
    int result;
    u32* buf;

    if ((result = SOiPrepare(NULL, &rmId)) == SO_SUCCESS) {
        buf = (u32*)SOiAlloc(0xC, 0x20);
        if (buf == NULL) {
            result = SO_ENOMEM;
        } else {
            buf[0] = s;
            result = IOS_Ioctl(rmId, 3, buf, 4, NULL, 0);
            SOiFree(0xC, buf, 0x20);
        }
        result = SOiConclude(NULL, result);
    }
    return result;
}

int SOBind(int s, SOSockAddr* addr) {
    s32 rmId;
    int result;
    u8* buf;

    if ((result = SOiPrepare(NULL, &rmId)) == SO_SUCCESS) {
        if (addr == NULL || addr->len > 8 || addr->len < 8) {
            result = SO_EINVAL;
        } else {
            buf = (u8*)SOiAlloc(0xC, 0x40);
            if (buf == NULL) {
                result = SO_ENOMEM;
            } else {
                ((u32*)buf)[0] = s;
                ((u32*)buf)[1] = 1;
                memcpy(buf + 8, addr, addr->len);
                result = IOS_Ioctl(rmId, 2, buf, 0x24, NULL, 0);
                SOiFree(0xC, buf, 0x40);
            }
        }
        result = SOiConclude(NULL, result);
    }
    return result;
}

int SOConnect(int s, SOSockAddr* addr) {
    s32 rmId;
    int result;
    u8* buf;

    if ((result = SOiPrepare(NULL, &rmId)) == SO_SUCCESS) {
        if (addr == NULL || addr->len > 8 || addr->len < 8) {
            result = SO_EINVAL;
        } else {
            buf = (u8*)SOiAlloc(0xC, 0x40);
            if (buf == NULL) {
                result = SO_ENOMEM;
            } else {
                ((u32*)buf)[0] = s;
                ((u32*)buf)[1] = 1;
                memcpy(buf + 8, addr, addr->len);
                result = IOS_Ioctl(rmId, 4, buf, 0x24, NULL, 0);
                SOiFree(0xC, buf, 0x40);
            }
        }
        result = SOiConclude(NULL, result);
    }
    return result;
}

int SOGetSockName(int s, SOSockAddr* addr) {
    s32 rmId;
    u32 size;
    int result;
    u8* buf;
    SOSockAddr* out;

    if ((result = SOiPrepare(NULL, &rmId)) == SO_SUCCESS) {
        if (addr == NULL || addr->len > 8 || addr->len < 8) {
            result = SO_EINVAL;
        } else {
            size = (addr->len + 0x3F) & ~0x1F;
            buf = (u8*)SOiAlloc(0xC, size);
            if (buf == NULL) {
                result = SO_ENOMEM;
            } else {
                out = (SOSockAddr*)(buf + 0x20);
                ((u32*)buf)[0] = s;
                memcpy(out, addr, addr->len);
                result = IOS_Ioctl(rmId, 7, buf, 4, out, addr->len);
                if (result >= 0) {
                    memcpy(addr, out, out->len);
                }
                SOiFree(0xC, buf, size);
            }
        }
        result = SOiConclude(NULL, result);
    }
    return result;
}

int SORecvFrom(int s, void* buf, int len, int flags, SOSockAddr* sockAddr) {
    return RecvFrom(NULL, s, buf, len, flags, sockAddr);
}

int SORecv(int s, void* buf, int len, int flags) {
    return RecvFrom(NULL, s, buf, len, flags, NULL);
}

int SORead(int s, void* buf, int len) {
    return RecvFrom(NULL, s, buf, len, 0, NULL);
}

int SOSendTo(int s, const void* buf, int len, int flags, const SOSockAddr* sockAddr) {
    return SendTo(NULL, s, buf, len, flags, sockAddr);
}

int SOSend(int s, void* buf, int len, int flags) {
    return SendTo(NULL, s, buf, len, flags, NULL);
}

int SOFcntl(int s, int cmd, ...) {
    s32 rmId;
    int result;
    va_list ap;
    int arg;
    u32* buf;

    va_start(ap, cmd);
    arg = va_arg(ap, int);
    va_end(ap);

    if ((result = SOiPrepare(NULL, &rmId)) == SO_SUCCESS) {
        buf = (u32*)SOiAlloc(0xC, 0x20);
        if (buf == NULL) {
            result = SO_ENOMEM;
        } else {
            buf[0] = s;
            buf[1] = cmd;
            buf[2] = arg;
            result = IOS_Ioctl(rmId, 5, buf, 0xC, NULL, 0);
            SOiFree(0xC, buf, 0x20);
        }
        result = SOiConclude(NULL, result);
    }
    return result;
}

int SOShutdown(int s, int how) {
    s32 rmId;
    int result;
    u32* buf;

    if ((result = SOiPrepare(NULL, &rmId)) == SO_SUCCESS) {
        buf = (u32*)SOiAlloc(0xC, 0x20);
        if (buf == NULL) {
            result = SO_ENOMEM;
        } else {
            buf[0] = s;
            buf[1] = how;
            result = IOS_Ioctl(rmId, 0xE, buf, 8, NULL, 0);
            SOiFree(0xC, buf, 0x20);
        }
        result = SOiConclude(NULL, result);
    }
    return result;
}

int SOPoll(SOPollFD* fds, int nfds, OSTime timeout) {
    s32 rmId;
    u32 size;
    int len;
    int result;
    u8* buf;
    SOPollFD* pfd;

    if ((result = SOiPrepare(NULL, &rmId)) == SO_SUCCESS) {
        if (fds == NULL) {
            result = SO_EINVAL;
        } else {
            len = nfds * sizeof(SOPollFD);
            size = (len + 0x3F) & ~0x1F;
            buf = (u8*)SOiAlloc(0xC, size);
            if (buf == NULL) {
                result = SO_ENOMEM;
            } else {
                pfd = (SOPollFD*)(buf + 0x20);
                if (timeout <= -1) {
                    memcpy(buf, &timeout, sizeof(timeout));
                } else {
                    *(OSTime*)buf = timeout / (OS_TIMER_CLOCK / 1000);
                }
                memcpy(pfd, fds, len);
                result = IOS_Ioctl(rmId, 0xB, buf, 8, pfd, len);
                if (result >= 0) {
                    memcpy(fds, pfd, len);
                }
                SOiFree(0xC, buf, size);
            }
        }
        result = SOiConclude(NULL, result);
    }
    return result;
}

int SOInetAtoN(const char* cp, SOInAddr* inp) {
    s32 rmId;
    int isTempRm;
    int result;
    u8* in;
    u32 size;
    u8* buf;

    if ((result = SOiPrepareTempRm(NULL, &rmId, &isTempRm)) == SO_SUCCESS) {
        if (cp == NULL) {
            result = SO_EINVAL;
        } else {
            size = (strlen(cp) + 0x40) & ~0x1F;
            buf = (u8*)SOiAlloc(0xC, size);
            if (buf == NULL) {
                result = SO_ENOMEM;
            } else {
                in = buf + 0x20;
                if (cp != NULL) {
                    strcpy((char*)in, cp);
                }
                result = IOS_Ioctl(rmId, 0x15, in, strlen(cp), buf, 4);
                if (result >= 0 && inp != NULL) {
                    memcpy(inp, buf, 4);
                }
                SOiFree(0xC, buf, size);
            }
        }
        result = SOiConcludeTempRm(NULL, result, isTempRm);
    }
    return result;
}

char* SOInetNtoA(SOInAddr in) {
    static char ascii[40];
    sprintf(ascii, "%d.%d.%d.%d", ((u8*)&in)[0], ((u8*)&in)[1], ((u8*)&in)[2],
            ((u8*)&in)[3]);
    return ascii;
}

int SOInetPtoN(int af, const char* src, void* dst) {
    s32 rmId;
    int isTempRm;
    u32 size;
    int result;
    int addrLen;
    u8* buf;

    if ((result = SOiPrepareTempRm(NULL, &rmId, &isTempRm)) == SO_SUCCESS) {
        switch (af) {
        default:
            addrLen = 0;
            break;
        case SO_PF_INET:
            addrLen = 4;
            break;
        }
        if (addrLen == 0) {
            result = -5;
        } else if (src == NULL) {
            result = SO_EINVAL;
        } else {
            size = (strlen(src) + 0x40) & ~0x1F;
            buf = (u8*)SOiAlloc(0xC, size);
            if (buf == NULL) {
                result = SO_ENOMEM;
            } else {
                strcpy((char*)buf + 0x20, src);
                ((u32*)buf)[0] = af;
                memset(buf + 4, 0, addrLen);
                result =
                    IOS_Ioctl(rmId, 0x16, (void*)src, strlen(src) + 1, buf, 0x14);
                if (result >= 0 && dst != NULL) {
                    memcpy(dst, buf + 4, addrLen);
                }
                SOiFree(0xC, buf, size);
            }
        }
        result = SOiConcludeTempRm(NULL, result, isTempRm);
    }
    return result;
}

u32 SONtoHl(u32 netlong) { return netlong; }

u16 SONtoHs(u16 netshort) { return netshort; }

u32 SOHtoNl(u32 hostlong) { return hostlong; }

u16 SOHtoNs(u16 hostshort) { return hostshort; }

static int RecvFrom(const char* funcName, int s, void* buf, int len, int flags,
                    SOSockAddr* addr) {
    s32 rmId;
    int result;
    int aligned;
    u8* databuf;
    u8* vec;
    u8* addrbuf;
    u32 vecsize;
    int mem1;
    u32 bufsize;
    u8 retlen;
    u8 cplen;

    if (len > 0x8000) {
        len = 0x8000;
    }

    if ((result = SOiPrepare(funcName, &rmId)) == SO_SUCCESS) {
        if (addr != NULL && (addr->len > 8 || addr->len < 8)) {
            result = SO_EINVAL;
        } else if (len < 0 || (len > 0 && buf == NULL)) {
            result = SO_EINVAL;
        } else {
            aligned = 1;
            if (len != 0) {
                int ok;
                int bufOk;
                int memOk;
                ok = 0;
                bufOk = (((u32)buf & 0x1F) == 0) && (len % 32 == 0);
                if (bufOk != 0) {
                    memOk = 1;
                    if (SOiIsBufferAddrCheck()) {
                        int in = ((u32)buf & 0x1FFFFFFF) >= 0x10000000 &&
                                 ((u32)buf & 0x1FFFFFFF) < 0x18000000;
                        if (!in) {
                            memOk = 0;
                        }
                    }
                    if (memOk != 0) {
                        ok = 1;
                    }
                }
                if (ok == 0) {
                    aligned = 0;
                }
            }

            vecsize = (((addr == NULL) ? 0 : addr->len) + 0x5F) & ~0x1F;
            vec = (u8*)SOiAlloc(0xC, vecsize);
            if (aligned == 0) {
                bufsize = (len + 0x1F) & ~0x1F;
                databuf = (u8*)SOiAlloc(0xD, bufsize);
            } else {
                databuf = (u8*)buf;
            }
            if (vec == NULL || databuf == NULL) {
                result = SO_ENOMEM;
            } else {
                ((u32*)vec)[0x8] = s;
                ((u32*)vec)[0x9] = flags;
                addrbuf = vec + 0x40;
                ((IOSIoVector*)vec)[0].base = vec + 0x20;
                ((IOSIoVector*)vec)[0].length = 8;
                ((IOSIoVector*)vec)[1].base = databuf;
                ((IOSIoVector*)vec)[1].length = len;
                if (addr == NULL) {
                    ((IOSIoVector*)vec)[2].base = NULL;
                    ((IOSIoVector*)vec)[2].length = 0;
                    result = IOS_Ioctlv(rmId, 0xC, 1, 2, (IOSIoVector*)vec);
                } else {
                    memcpy(addrbuf, addr, addr->len);
                    ((IOSIoVector*)vec)[2].base = addrbuf;
                    ((IOSIoVector*)vec)[2].length = addr->len;
                    result = IOS_Ioctlv(rmId, 0xC, 1, 2, (IOSIoVector*)vec);
                    if (result >= 0) {
                        cplen = addr->len;
                        retlen = addrbuf[0];
                        if (cplen > retlen) {
                            cplen = retlen;
                        }
                        memcpy(addr, addrbuf, cplen);
                    }
                }
                if (result >= 0 && aligned == 0) {
                    memcpy(buf, databuf, len);
                }
            }
            if (aligned == 0) {
                SOiFree(0xD, databuf, (len + 0x1F) & ~0x1F);
            }
            SOiFree(0xC, vec, vecsize);
        }
        result = SOiConclude(funcName, result);
    }
    return result;
}

static int SendTo(const char* funcName, int s, const void* buf, int len, int flags,
                  const SOSockAddr* addr) {
    s32 rmId;
    u8* vec;
    int result;
    int aligned;
    u8* databuf;
    u32 bufsize;
    u8* hdr;

    if ((result = SOiPrepare(funcName, &rmId)) == SO_SUCCESS) {
        if (addr != NULL && (addr->len > 8 || addr->len < 8)) {
            result = SO_EINVAL;
        } else if (len < 0 || (len > 0 && buf == NULL)) {
            result = SO_EINVAL;
        } else {
            aligned = 1;
            if (len != 0) {
                int ok;
                int bufOk;
                int memOk;
                ok = 0;
                bufOk = (((u32)buf & 0x1F) == 0) && (len % 32 == 0);
                if (bufOk != 0) {
                    memOk = 1;
                    if (SOiIsBufferAddrCheck()) {
                        int in = ((u32)buf & 0x1FFFFFFF) >= 0x10000000 &&
                                 ((u32)buf & 0x1FFFFFFF) < 0x18000000;
                        if (!in) {
                            memOk = 0;
                        }
                    }
                    if (memOk != 0) {
                        ok = 1;
                    }
                }
                if (ok == 0) {
                    aligned = 0;
                }
            }

            vec = (u8*)SOiAlloc(0xC, 0x60);
            if (aligned == 0) {
                bufsize = (len + 0x1F) & ~0x1F;
                databuf = (u8*)SOiAlloc(0xE, bufsize);
            } else {
                databuf = (u8*)buf;
            }

            if (vec == NULL || databuf == NULL) {
                result = SO_ENOMEM;
            } else {
                hdr = vec + 0x20;
                ((u32*)vec)[0x8] = s;
                ((u32*)vec)[0x9] = flags;
                if (addr == NULL) {
                    ((u32*)hdr)[2] = 0;
                } else {
                    ((u32*)hdr)[2] = 1;
                    memcpy(hdr + 0xC, addr, addr->len);
                }
                if (aligned == 0) {
                    memcpy(databuf, buf, len);
                }
                ((IOSIoVector*)vec)[0].base = databuf;
                ((IOSIoVector*)vec)[0].length = len;
                ((IOSIoVector*)vec)[1].base = hdr;
                ((IOSIoVector*)vec)[1].length = 0x28;
                result = IOS_Ioctlv(rmId, 0xD, 2, 0, (IOSIoVector*)vec);
            }
            if (aligned == 0) {
                SOiFree(0xE, databuf, bufsize);
            }
            SOiFree(0xC, vec, 0x60);
        }
        result = SOiConclude(funcName, result);
    }
    return result;
}
