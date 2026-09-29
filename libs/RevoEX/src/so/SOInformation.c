#include <revolution/os.h>
#include <revolution/soex.h>

#include <private/ios.h>

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
    SO_EINVAL = -28,
    SO_ENOMEM = -49,
};

void* SOiAlloc(u32 name, s32 size);
void SOiFree(u32 name, void* ptr, s32 size);
int SOiPrepare(const char* funcName, s32* pRmId);
int SOiConclude(const char* funcName, int result);
SOSysWork* SOiGetSysWork(void);
int SOiIsInitialized(void);

s32 SOGetHostID(void) {
    s32 rmId;
    s32 err;
    s32 result = 0;

    if ((err = SOiPrepare(NULL, &rmId)) == SO_SUCCESS) {
        result = IOS_Ioctl(rmId, 0x10, NULL, 0, NULL, 0);
        (void)SOiConclude(NULL, err);
    }
    return result;
}

SOHostEnt* SOGetHostByName(const char* name) {
    s32 rmId;
    SOHostEnt* result = NULL;
    s32 err;

    if (SOiPrepare(NULL, &rmId) == SO_SUCCESS) {
        if (name == NULL) {
            err = SO_EINVAL;
        } else {
                        SOHostEnt* hostEnt = (SOHostEnt*)SOiGetSysWork()->unk10;
            u32 len = strlen(name);
                        u32 size = (len + 0x20) & ~0x1F;
                        char* buf = (char*)SOiAlloc(0xC, size);

            if (buf == NULL) {
                err = SO_ENOMEM;
            } else {
                strcpy(buf, name);
                err = IOS_Ioctl(rmId, 0x11, buf, len + 1, hostEnt, 0x460);
                if (err >= 0) {
                    u8* base = (u8*)hostEnt;
                    s32 delta = (s32)(base + 0x10) - (s32)hostEnt->name;
                    u32* list = (u32*)(base + 0x340);
                    while (*list != 0) {
                        *list += delta;
                        list++;
                    }
                    *(u32*)&hostEnt->aliases += delta;
                    *(u32*)&hostEnt->name += delta;
                    *(u32*)&hostEnt->addrList += delta;
                    result = hostEnt;
                }
                SOiFree(0xC, buf, size);
            }
        }
        (void)SOiConclude(NULL, err);
    }
    return result;
}

int SOGetAddrInfo(const char* nodeName, const char* servName,
                  const SOAddrInfo* hints, SOAddrInfo** res) {
    s32 rmId;
    int result;
    u32 nameLen;
    u32 servLen;
    u32 vecsize;
    u8* vec;
    u8* hostBuf;
    char* nameArea;
    char* servArea;
    SOAddrInfo* hintsArea;
    SOAddrInfo* ai;
    u8* addrData;

    if ((result = SOiPrepare(NULL, &rmId)) == SO_SUCCESS) {
        servLen = (servName == NULL) ? 0 : strlen(nodeName) + 1;
        nameLen = (nodeName == NULL) ? 0 : strlen(nodeName) + 1;
        vecsize = (((nameLen + 0x1F) & ~0x1F) + ((servLen + 0x1F) & ~0x1F) +
                   0x5F) & ~0x1F;
        vec = (u8*)SOiAlloc(0xC, vecsize);
        if (vec == NULL) {
            result = SO_ENOMEM;
        } else {
            hostBuf = (u8*)SOiAlloc(0xA, 0x840);
            if (hostBuf == NULL) {
                SOiFree(0xC, vec, vecsize);
                result = SO_ENOMEM;
            } else {
                nameArea = (char*)(vec + 0x20);
                servArea =
                    nameArea +
                    (((nodeName == NULL) ? 0 : strlen(nodeName) + 1) + 0x1F &
                     ~0x1F);
                hintsArea =
                    (SOAddrInfo*)(servArea +
                                  (((servName == NULL) ? 0 : strlen(nodeName) + 1) +
                                       0x1F &
                                   ~0x1F));

                if (nodeName != NULL) {
                    strcpy(nameArea, nodeName);
                }
                ((u32*)vec)[0] =
                    (u32)((nodeName != NULL) ? nameArea : NULL);
                ((u32*)vec)[1] =
                    (nodeName == NULL) ? 0 : strlen(nodeName);
                if (servName != NULL) {
                    strcpy(servArea, servName);
                }
                ((u32*)vec)[2] =
                    (u32)((servName != NULL) ? servArea : NULL);
                ((u32*)vec)[3] =
                    (servName == NULL) ? 0 : strlen(servName);
                if (hints != NULL) {
                    memcpy(hintsArea, hints, sizeof(SOAddrInfo));
                } else {
                    memset(hintsArea, 0, sizeof(SOAddrInfo));
                }
                if (hintsArea->family == 0) {
                    hintsArea->family = SO_PF_INET;
                }
                if (hintsArea->family == 0x17) {
                    *res = NULL;
                    result = -0x44;
                    SOiFree(0xA, hostBuf, 0x840);
                } else {
                    ((u32*)vec)[4] = (u32)hintsArea;
                    ((u32*)vec)[5] = sizeof(SOAddrInfo);
                    ((u32*)vec)[6] = (u32)hostBuf;
                    ((u32*)vec)[7] = 0x834;
                    result = IOS_Ioctlv(rmId, 0x18, 3, 1, (IOSIoVector*)vec);
                    if (result >= 0) {
                        *res = (SOAddrInfo*)hostBuf;
                        addrData = hostBuf + 0x460;
                        ai = (SOAddrInfo*)hostBuf;
                        while (ai != NULL) {
                            ai->addr = addrData;
                            if (ai->next != NULL) {
                                ai->next = ai + 1;
                            }
                            ai = ai->next;
                            addrData += 0x1C;
                        }
                    } else {
                        *res = NULL;
                        SOiFree(0xA, hostBuf, 0x840);
                    }
                }
                SOiFree(0xC, vec, vecsize);
            }
        }
        result = SOiConclude(NULL, result);
    }
    return result;
}

void SOFreeAddrInfo(SOAddrInfo* head) {
    int enabled = OSDisableInterrupts();
    if (SOiIsInitialized() == 1 && head != NULL) {
        SOiFree(0xA, head, 0x840);
    }
    OSRestoreInterrupts(enabled);
}
