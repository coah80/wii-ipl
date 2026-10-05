#include <revolution/os.h>

#include <private/dvd.h>
#include <revolution/dvd.h>

#include <revolution/esp.h>

#include <private/ios.h>
#include <private/ipc.h>

#include <stdbool.h>

#include <string.h>

#define DVD_LOW_CTX_MAX 4
#define DVD_LOW_CMD_MAX 4

enum {
    DVD_IOCTL_INQUIRY = 0x12,
    DVD_IOCTL_READ_DISK_ID = 0x70,
    DVD_IOCTL_READ = 0x71,
    DVD_IOCTL_PREPARE_COVER_REGISTER = 0x7A,
    DVD_IOCTL_PREPARE_STATUS_REGISTER = 0x95,
    DVD_IOCTL_CLEAR_COVER_INTERRUPT = 0x86,
    DVD_IOCTL_RESET = 0x8A,
    DVD_IOCTL_CLOSE_PARTITION = 0x8C,
    DVD_IOCTL_UNENCRYPTED_READ = 0x8D,
    DVD_IOCTL_SEEK = 0xAB,
    DVD_IOCTL_SET_MAX_ROTATION = 0xDD,
    DVD_IOCTL_REQUEST_ERROR = 0xE0,
    DVD_IOCTL_STOP_MOTOR = 0xE3,
    DVD_IOCTL_AUDIO_BUFFER_CONFIG = 0xE4,
};

enum {
    DVD_IOCTLV_OPEN_PARTITION = 0x8B,
    DVD_IOCTLV_OPEN_PARTITION_WITH_TMD_AND_TICKET = 0x94,
    DVD_IOCTLV_GET_NO_DISC_PARTITION = 0x90,
    DVD_IOCTLV_GET_NO_DISC_BUFFER_SIZE = 0x92,
};

typedef struct DVDVideoPhysical {
    u8 data[2048];
} DVDVideoPhysical;

typedef struct DVDVideoDiscKey {
    u8 data[2048];
} DVDVideoDiscKey;

typedef struct DVDDiskBca {
    u8 optionalInfo[52];
    u8 manufacturerCode[2];
    u8 recorderDeviceCode[2];
    u8 APMRecorderDeviceCode[1];
    u8 discManufactureDate[2];
    u8 discManufactureTime[2];
    u8 discNumber[3];
} DVDDiskBca;

typedef struct DVDLowDriveSer {
    u8 data[12];
    u8 reserved[20];
} DVDLowDriveSer;

typedef struct DVDLowContext {
    DVDLowCallback callback;
    int callbackType;

    bool inUse;

    u32 contextMagic;
    u32 contextNum;

    u32 pad[3];
} DVDLowContext;

typedef struct DVDLowRegValues {
    u32 diImmValue;
    u32 diCoverReg;

    u32 pad[6];
} DVDLowRegValues;

typedef struct DVDLowCommand {
    u8 diCmd;
    u8 pad1[3];
    u32 arg[5];
    u32 pad2[2];
} DVDLowCommand;

#define CONTEXT_MAGIC 0xFEEBDAED

IOSFd DiFD = -1;

static u32 coverRegister[8] ALIGN32;
static u32 statusRegister[8] ALIGN32;
static u32 coverStatus[8] ALIGN32;
static u32 statusRegister[8] ALIGN32;

static DVDLowContext dvdContexts[4] ALIGN32 = {0};
static DVDLowRegValues diRegValCache ALIGN32;
static u32 registerBuf[8] ALIGN32;
static IOSIoVector ioVec[10] ALIGN32;
static s32 lastTicketError[8] ALIGN32;

static u8 breakRequested;
static DVDLowCommand* diCommand;

static char* pathBuf;

static u32 readLength;

static BOOL spinUpValue;
static u8 DVDLowInitCalled;
static u8 dvdContextsInited;

static s32 freeDvdContext;
static int freeCommandBuf;

static bool callbackInProgress;
static bool requestInProgress;

#define IS_ALIGNED(addr) (((u32)(addr) & 0x1F) == 0)

IOSError doTransactionCallback(IOSError ret, void* context) {
    DVDLowContext* dvdContext = context;

    if (dvdContext->contextMagic != CONTEXT_MAGIC) {
        OSReport("(doTransactionCallback) Error - context mangled!\n");
        dvdContext->contextMagic = CONTEXT_MAGIC;
        goto out;
    }

    requestInProgress = false;

    if (dvdContext->callback != NULL) {
        int callbackArg;
        callbackInProgress = TRUE;
        callbackArg = ret;

        if (breakRequested == TRUE) {
            breakRequested = false;
            callbackArg |= DVD_INTTYPE_BR;
        }

        if (callbackArg & DVD_INTTYPE_TC) {
            readLength = 0;
        }

        dvdContext->callback(callbackArg);
        callbackInProgress = false;
    }

out:
    dvdContext->inUse = false;
    return 0;
}

static IOSError doCoverCallback(IOSError ret, void* context) {
    DVDLowContext* dvdContext;

    requestInProgress = false;
    dvdContext = (DVDLowContext*)context;
    if (dvdContext->contextMagic != 0xfeebdaed) {
        OSReport("(doCoverCallback) Error - context mangled!\n");
        dvdContext->contextMagic = 0xfeebdaed;
        goto out;
    }
    if (dvdContext->callback != NULL) {
        s32 callbackArg;
        callbackInProgress = true;
        callbackArg = ret;
        if (breakRequested == true) {
            breakRequested = false;
            callbackArg |= 0x00000008;
        }
        dvdContext->callback((u32)callbackArg);
        callbackInProgress = false;
    }
out:
    dvdContext->inUse = false;

    return 0;
}

IOSError doPrepareCoverRegisterCallback(IOSError ret, void* context) {
    DVDLowContext* dvdContext;

    requestInProgress = false;

    diRegValCache.diCoverReg = registerBuf[0];
    dvdContext = (DVDLowContext*)context;

    if (dvdContext->contextMagic != CONTEXT_MAGIC) {
        OSReport("(doTransactionCallback) Error - context mangled!\n");
        dvdContext->contextMagic = CONTEXT_MAGIC;
    } else {
        if (dvdContext->callback != 0) {
            callbackInProgress = true;

            if (breakRequested == true) {
                breakRequested = false;
                ret |= DVD_INTTYPE_BR;
            }

            dvdContext->callback(ret);
            callbackInProgress = false;
        }
    }

    dvdContext->inUse = false;
    return 0;
}

static void* ddrAllocAligned32(int size) {
    void* low;
    void* high;

    if (!IS_ALIGNED(size)) {
        return 0;
    }

    low = IPCGetBufferLo();
    high = IPCGetBufferHi();

    if (!IS_ALIGNED(low)) {
        low = (void*)(((u32)low + 31) & 0x1F);
    }

    if ((u32)low + size > (u32)high) {
        OSReport("(ddrAllocAligned32) Not enough space to allocate %d bytes\n", size);
    }

    IPCSetBufferLo((void*)((u32)low + size));
    return low;
}

static bool allocateStructures() {
    diCommand = ddrAllocAligned32(sizeof(DVDLowCommand) * 4);
    if (diCommand == 0) {
        OSReport("Allocation of diCommand blocks failed\n");
        return false;
    }

    pathBuf = ddrAllocAligned32(32);
    if (pathBuf == 0) {
        OSReport("Allocation of pathBuf failed\n");
        return false;
    }

    return true;
}

static void initDvdContexts() {
    int i;
    for (i = 0; i < 4; i++) {
        dvdContexts[i].callback = 0;
        dvdContexts[i].callbackType = 0;
        dvdContexts[i].inUse = false;
        dvdContexts[i].contextMagic = CONTEXT_MAGIC;
        dvdContexts[i].contextNum = i;
    }

    freeDvdContext = 0;
}

static inline DVDLowContext* newContext(DVDLowCallback callback, int type) {
    int returnIndex;
    bool use = dvdContexts[freeDvdContext].inUse != 0;

    if (use == true) {
        OSReport("(newContext) ERROR: freeDvdContext.inUse (#%d) is true\n", freeDvdContext);
        OSReport("(newContext) Now spinning in infinite loop\n");
        while (TRUE) {
        }
    }

    if (dvdContexts[freeDvdContext].contextMagic != CONTEXT_MAGIC) {
        OSReport("(newContext) Something overwrote the context magic - spinning \n");
        while (TRUE) {
        }
    }

    dvdContexts[freeDvdContext].callback = callback;
    dvdContexts[freeDvdContext].callbackType = type;
    dvdContexts[freeDvdContext].inUse = true;
    returnIndex = freeDvdContext;
    freeDvdContext++;

    if (freeDvdContext >= DVD_LOW_CTX_MAX) {
        freeDvdContext = 0;
    }

    return dvdContexts + returnIndex;
}

static inline void nextCommandBuf(int* bufNum) {
    if (++(*bufNum) >= DVD_LOW_CMD_MAX) {
        *bufNum = 0;
    }
}

bool DVDLowFinalize() {
    IOSError ret = IOS_Close(DiFD);

    if (ret != IPC_RESULT_OK) {
        OSReport("(DVDLowFinish) Error: IOS_Close failed\n");
        return false;
    }

    DVDLowInitCalled = false;

    return true;
}

bool DVDLowInit() {
    IOSError ret;

    if (!DVDLowInitCalled) {
        DVDLowInitCalled = true;
        ret = IPCCltInit();

        if (ret != IPC_RESULT_OK) {
            OSReport("IPCCltInit returned error: %d\n", ret);
            return false;
        }

        if (!allocateStructures()) {
            return false;
        }

        if (!dvdContextsInited) {
            initDvdContexts();
            dvdContextsInited = true;
        }
    }

    strncpy(pathBuf, "/dev/di", 32);
    DiFD = IOS_Open(pathBuf, IPC_ACCESS_NONE);

    if (DiFD >= 0) {
        return true;
    } else {
        switch (DiFD) {
            case IPC_RESULT_NOEXISTS: {
                OSReport("(DVDLowInit) Error: IOS_Open failed - pathname '/dev/di' does not exist\n");
                return false;
            }
            case IPC_RESULT_ACCESS: {
                OSReport("(DVDLowInit) Error: IOS_Open failed - calling thread lacks permission\n");
                return false;
            }
            case IPC_RESULT_MAX: {
                OSReport("(DVDLowInit) Error: IOS_Open failed - connection limit has been reached\n");
                return false;
            }
            default: {
                OSReport("(DVDLowInit) IOS_Open failed, errorcode = %d\n", DiFD);
                return false;
            }
        }
    }
}

bool DVDLowReadDiskID(DVDDiskID* diskID, DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError ret;

    requestInProgress = true;

    dvdContext = newContext(callback, 1);

    if (diskID == 0) {
        OSReport("@@@@@@ WARNING - Calling DVDLowReadDiskId with NULL ptr\n");
    }

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = DVD_IOCTL_READ_DISK_ID;

    ret = IOS_IoctlAsync(DiFD, DVD_IOCTL_READ_DISK_ID, &diCommand[freeCommandBuf], sizeof(DVDLowCommand), diskID, sizeof(DVDDiskID),
                         doTransactionCallback, dvdContext);
    if (ret != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowReadDiskID) IOS_IoctlAsync returned error: %d\n", ret);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}

bool DVDLowOpenPartition(u32 partitionWordOffset, ESTicket* eTicket, u32 numCertBytes, u8* certificates, ESTitleMeta* tmd, DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError ret;

    if (eTicket != 0 && !IS_ALIGNED(eTicket)) {
        OSReport("(DVDLowOpenPartition) eTicket memory is unaligned\n");
        return false;
    }

    if (certificates != 0 && !IS_ALIGNED(certificates)) {
        OSReport("(DVDLowOpenPartition) certificates memory is unaligned\n");
        return false;
    }

    if (tmd != 0 && !IS_ALIGNED(tmd)) {
        OSReport("(DVDLowOpenPartition) certificates memory is unaligned\n");
        return false;
    }

    requestInProgress = true;

    dvdContext = newContext(callback, 1);

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = DVD_IOCTLV_OPEN_PARTITION;
    diCommand[freeCommandBuf].arg[0] = partitionWordOffset;

    ioVec[0].base = (u8*)&diCommand[freeCommandBuf];
    ioVec[0].length = sizeof(DVDLowCommand);

    ioVec[1].base = (u8*)eTicket;
    if (eTicket == 0) {
        ioVec[1].length = 0;
    } else {
        ioVec[1].length = sizeof(ESTicket);
    }

    ioVec[2].base = certificates;
    if (certificates == 0) {
        ioVec[2].length = 0;
    } else {
        ioVec[2].length = numCertBytes;
    }

    ioVec[3].base = (u8*)tmd;
    ioVec[3].length = sizeof(ESTitleMeta);

    ioVec[4].base = (u8*)&lastTicketError[0];
    ioVec[4].length = sizeof(lastTicketError);

    ret = IOS_IoctlvAsync(DiFD, DVD_IOCTLV_OPEN_PARTITION, 3, 2, ioVec, doTransactionCallback, dvdContext);
    if (ret != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowOpenPartition) IOS_IoctlvAsync returned error: %d\n", ret);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}


bool DVDLowOpenPartitionWithTmdAndTicket(const u32 partitionWordOffset, const ESTicket* const eTicket, const u32 numTmdBytes,
                                         const ESTitleMeta* const tmd, const u32 numCertBytes, const u8* const certificates,
                                         DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError rv;

    if (eTicket != NULL && !(((u32)(eTicket) & 0x1F) == 0)) {
        OSReport("(%s) eTicket memory is unaligned\n", __FUNCTION__);
        return false;
    }
    if (certificates != NULL && !(((u32)(certificates) & 0x1F) == 0)) {
        return false;
    }
    if (tmd == NULL) {
        OSReport("(%s) tmd parameter cannot be NULL\n", __FUNCTION__);
        return false;
    } else if (!(((u32)(tmd) & 0x1F) == 0)) {
        OSReport("(%s) tmd memory is unaligned\n", __FUNCTION__);
        return false;
    }
    if (eTicket == NULL) {
        OSReport("(%s) eTicket parameter cannot be NULL\n", __FUNCTION__);
        return false;
    } else if (!(((u32)(eTicket) & 0x1F) == 0)) {
        OSReport("(%s) eTicket memory is unaligned\n", __FUNCTION__);
        return false;
    }
    requestInProgress = true;
    dvdContext = newContext(callback, 1);

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = 0x93;
    diCommand[freeCommandBuf].arg[0] = partitionWordOffset;
    ioVec[0].base = (u8*)&(diCommand[freeCommandBuf]);
    ioVec[0].length = sizeof(DVDLowCommand);
    ioVec[1].base = (u8*)eTicket;
    ioVec[1].length = sizeof(ESTicket);
    ioVec[2].base = (u8*)tmd;
    ioVec[2].length = numTmdBytes;
    ioVec[3].base = (u8*)certificates;
    if (certificates == NULL) {
        ioVec[3].length = 0;
    } else {
        ioVec[3].length = numCertBytes;
    }
    ioVec[4].base = (u8*)&(lastTicketError[0]);
    ioVec[4].length = sizeof(lastTicketError);

    rv = IOS_IoctlvAsync(DiFD, 0x93, 4, 1, ioVec, doTransactionCallback, dvdContext);

    if (rv != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowOpenPartition) IOS_IoctlvAsync returned error: %d\n", rv);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}

bool DVDLowOpenPartitionWithTmdAndTicketView(u32 partitionWordOffset, ESTicketView* eTicketView, u32 numTmdBytes, ESTitleMeta* tmd, u32 numCertBytes,
                                             u8* certificates, DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError ret;

    if (certificates != 0 && !IS_ALIGNED(certificates)) {
        return false;
    }

    if (tmd == 0) {
        OSReport("(%s) tmd parameter cannot be NULL\n", __FUNCTION__);
        return false;
    } else if (!IS_ALIGNED(tmd)) {
        OSReport("(%s) tmd memory is unaligned\n", __FUNCTION__);
        return false;
    }

    if (eTicketView == 0) {
        OSReport("(%s) eTicketView parameter cannot be NULL\n", __FUNCTION__);
        return false;
    } else if (!IS_ALIGNED(eTicketView)) {
        OSReport("(%s) eTicketView memory is unaligned\n", __FUNCTION__);
        return false;
    }

    requestInProgress = true;

    dvdContext = newContext(callback, 1);

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = DVD_IOCTLV_OPEN_PARTITION_WITH_TMD_AND_TICKET;
    diCommand[freeCommandBuf].arg[0] = partitionWordOffset;

    ioVec[0].base = (u8*)&diCommand[freeCommandBuf];
    ioVec[0].length = sizeof(DVDLowCommand);

    ioVec[1].base = (u8*)eTicketView;
    ioVec[1].length = sizeof(ESTicketView);

    ioVec[2].base = (u8*)tmd;
    ioVec[2].length = numTmdBytes;

    ioVec[3].base = certificates;
    if (certificates == 0) {
        ioVec[3].length = 0;
    } else {
        ioVec[3].length = numCertBytes;
    }

    ioVec[4].base = (u8*)&lastTicketError[0];
    ioVec[4].length = sizeof(lastTicketError);

    ret = IOS_IoctlvAsync(DiFD, DVD_IOCTLV_OPEN_PARTITION_WITH_TMD_AND_TICKET, 4, 1, ioVec, doTransactionCallback, dvdContext);
    if (ret != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowOpenPartition) IOS_IoctlvAsync returned error: %d\n", ret);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}

bool DVDLowGetNoDiscBufferSizes(const u32 partitionWordOffset, u32* numTmdBytes, u32* numCertBytes, DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError ret;

    if (numTmdBytes == 0 || numCertBytes == 0) {
        OSReport("(%s) Error: NULL pointer argument\n", __FUNCTION__);
        return false;
    }

    if (!IS_ALIGNED(numTmdBytes)) {
        OSReport("(%s) numTmdBytes memory is unaligned\n", __FUNCTION__);
        return false;
    }

    if (!IS_ALIGNED(numCertBytes)) {
        OSReport("(%s) certificates memory is unaligned\n", __FUNCTION__);
        return false;
    }

    requestInProgress = true;

    dvdContext = newContext(callback, 1);

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = DVD_IOCTLV_GET_NO_DISC_BUFFER_SIZE;
    diCommand[freeCommandBuf].arg[0] = partitionWordOffset;

    ioVec[0].base = (u8*)&diCommand[freeCommandBuf];
    ioVec[0].length = sizeof(DVDLowCommand);

    ioVec[1].base = (u8*)numTmdBytes;
    ioVec[1].length = 4;

    ioVec[2].base = (u8*)numCertBytes;
    ioVec[2].length = 4;

    ret = IOS_IoctlvAsync(DiFD, DVD_IOCTLV_GET_NO_DISC_BUFFER_SIZE, 1, 2, ioVec, doTransactionCallback, dvdContext);
    if (ret != IPC_RESULT_OK) {
        OSReport("@@@ (%s) IOS_IoctlvAsync returned error: %d\n", __FUNCTION__, ret);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}

bool DVDLowGetNoDiscOpenPartitionParams(const u32 partitionWordOffset, ESTicket* eTicket, u32* numTmdBytes, ESTitleMeta* tmd, u32* numCertBytes,
                                        u8* certificates, u32* dataWordOffset, u8* h3HashPtr, DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError ret;

    if (eTicket == 0 || numTmdBytes == 0 || tmd == 0 || numCertBytes == 0 || certificates == 0 || dataWordOffset == 0 || h3HashPtr == 0) {
        OSReport("(%s) Error: NULL pointer argument\n", __FUNCTION__);
        return false;
    }

    if (!IS_ALIGNED(eTicket) || !IS_ALIGNED(numTmdBytes) || !IS_ALIGNED(tmd) || !IS_ALIGNED(numCertBytes) || !IS_ALIGNED(certificates) ||
        !IS_ALIGNED(dataWordOffset) || !IS_ALIGNED(h3HashPtr)) {
        OSReport("(%s) pointer argument is unaligned\n", __FUNCTION__);
        return false;
    }

    requestInProgress = true;
    dvdContext = newContext(callback, 1);
    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = DVD_IOCTLV_GET_NO_DISC_PARTITION;
    diCommand[freeCommandBuf].arg[0] = partitionWordOffset;

    ioVec[0].base = (u8*)&diCommand[freeCommandBuf];
    ioVec[0].length = sizeof(DVDLowCommand);

    ioVec[1].base = (u8*)numTmdBytes;
    ioVec[1].length = 4;

    ioVec[2].base = (u8*)numCertBytes;
    ioVec[2].length = 4;

    ioVec[3].base = (u8*)eTicket;
    ioVec[3].length = sizeof(ESTicket);

    ioVec[4].base = (u8*)numTmdBytes;
    ioVec[4].length = 4;

    ioVec[5].base = (u8*)tmd;
    ioVec[5].length = *numTmdBytes;

    ioVec[6].base = (u8*)numCertBytes;
    ioVec[6].length = 4;

    ioVec[7].base = certificates;
    ioVec[7].length = *numCertBytes;

    ioVec[8].base = (u8*)dataWordOffset;
    ioVec[8].length = 4;

    ioVec[9].base = h3HashPtr;
    ioVec[9].length = 98304;

    ret = IOS_IoctlvAsync(DiFD, DVD_IOCTLV_GET_NO_DISC_PARTITION, 3, 7, ioVec, doTransactionCallback, dvdContext);
    if (ret != IPC_RESULT_OK) {
        OSReport("@@@ (%s) IOS_IoctlvAsync returned error: %d\n", __FUNCTION__, ret);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}

bool DVDLowNoDiscOpenPartition(const ESTicket* const eTicket, const u32 numTmdBytes, const ESTitleMeta* const tmd, const u32 numCertBytes,
                               const u8* const certificates, const u32 dataWordOffset, const u8* const h3HashPtr, DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError rv;

    if (eTicket == NULL || tmd == NULL || certificates == NULL) {
        OSReport("(%s) Error: NULL pointer argument\n", __FUNCTION__);
        return false;
    }
    if (!(((u32)(eTicket) & 0x1F) == 0) || !(((u32)(tmd) & 0x1F) == 0) || !(((u32)(certificates) & 0x1F) == 0) ||
        !(((u32)(dataWordOffset) & 0x1F) == 0) || !(((u32)(h3HashPtr) & 0x1F) == 0)) {
        OSReport("(%s) pointer argument is unaligned\n", __FUNCTION__);
        return false;
    }
    requestInProgress = true;
    dvdContext = newContext(callback, 1);

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = 0x91;
    diCommand[freeCommandBuf].arg[0] = dataWordOffset;
    ioVec[0].base = (u8*)&(diCommand[freeCommandBuf]);
    ioVec[0].length = sizeof(DVDLowCommand);
    ioVec[1].base = (u8*)eTicket;
    ioVec[1].length = sizeof(ESTicket);
    ioVec[2].base = (u8*)tmd;
    ioVec[2].length = numTmdBytes;
    ioVec[3].base = (u8*)certificates;
    ioVec[3].length = numCertBytes;
    ioVec[4].base = (u8*)h3HashPtr;
    ioVec[4].length = (96 * 1024);
    ioVec[5].base = (u8*)&(lastTicketError[0]);
    ioVec[5].length = sizeof(u32);

    rv = IOS_IoctlvAsync(DiFD, 0x91, 5, 1, ioVec, doTransactionCallback, dvdContext);

    if (rv != IPC_RESULT_OK) {
        OSReport("@@@ (%s) IOS_IoctlvAsync returned error: %d\n", __FUNCTION__, rv);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}

bool DVDLowClosePartition(DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError ret;

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = DVD_IOCTL_CLOSE_PARTITION;

    requestInProgress = true;
    dvdContext = newContext(callback, 1);

    ret = IOS_IoctlAsync(DiFD, DVD_IOCTL_CLOSE_PARTITION, &diCommand[freeCommandBuf], sizeof(DVDLowCommand), 0, 0, doTransactionCallback, dvdContext);
    if (ret != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowClosePartition) IOS_IoctlAsync returned error: %d\n", ret);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}

bool DVDLowUnencryptedRead(void* destAddr, u32 length, u32 wordOffset, DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError ret;

    requestInProgress = true;

    dvdContext = newContext(callback, 1);

    readLength = length;
    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = DVD_IOCTL_UNENCRYPTED_READ;
    diCommand[freeCommandBuf].arg[0] = length;
    diCommand[freeCommandBuf].arg[1] = wordOffset;

    ret = IOS_IoctlAsync(DiFD, DVD_IOCTL_UNENCRYPTED_READ, &diCommand[freeCommandBuf], sizeof(DVDLowCommand), destAddr, length, doTransactionCallback,
                         dvdContext);
    if (ret != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowUnencryptedRead) IOS_IoctlAsync returned error: %d\n", ret);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}

bool DVDLowStopMotor(bool eject, bool saving, DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError ret;

    requestInProgress = true;

    dvdContext = newContext(callback, 1);

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = DVD_IOCTL_STOP_MOTOR;
    diCommand[freeCommandBuf].arg[0] = eject;
    diCommand[freeCommandBuf].arg[1] = saving;

    ret = IOS_IoctlAsync(DiFD, DVD_IOCTL_STOP_MOTOR, &diCommand[freeCommandBuf], sizeof(DVDLowCommand), &diRegValCache, sizeof(DVDLowRegValues),
                         doTransactionCallback, dvdContext);
    if (ret != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowStopMotor) IOS_IoctlAsync returned error: %d\n", ret);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}

bool DVDLowWaitForCoverClose(DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError rv;

    requestInProgress = true;
    dvdContext = newContext(callback, 2);

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = 0x79;

    rv = IOS_IoctlAsync(DiFD, 0x79, &(diCommand[freeCommandBuf]), sizeof(DVDLowCommand), NULL, 0, doCoverCallback, dvdContext);

    if (rv != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowWaitForCoverClose) IOS_IoctlAsync returned error: %d\n", rv);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}
static char inquiryErrorMessage[] = "@@@ (DVDLowInquiry) IOS_IoctlAsync returned error: %d\n";
static char requestErrorMessage[] = "@@@ (DVDLowRequestError) IOS_IoctlAsync returned error: %d\n";
bool DVDLowNotifyReset(void) {
    IOSError rv;

    if (callbackInProgress == true) {
        OSReport("(DVDLowSetSpinupFlag): Synch functions can't be called in callbacks\n");
        return false;
    }

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = 0x7E;

    rv = IOS_Ioctl(DiFD, 0x7E, &(diCommand[freeCommandBuf]), sizeof(DVDLowCommand), NULL, 0);

    if (rv != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowNotifyReset) IOS_IoctlAsync returned error: %d\n", rv);
        return false;
    }

    return true;
}
static char resetErrorMessage[] = "@@@ (DVDLowReset) IOS_IoctlAsync returned error: %d\n";

bool DVDLowInquiry(DVDDriveInfo* info, DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError ret;

    requestInProgress = true;

    dvdContext = newContext(callback, 1);

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = DVD_IOCTL_INQUIRY;

    ret = IOS_IoctlAsync(DiFD, DVD_IOCTL_INQUIRY, &diCommand[freeCommandBuf], sizeof(DVDLowCommand), info, sizeof(DVDDriveInfo),
                         doTransactionCallback, dvdContext);
    if (ret != IPC_RESULT_OK) {
        OSReport(inquiryErrorMessage, ret);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}

bool DVDLowRequestError(DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError ret;

    requestInProgress = true;

    dvdContext = newContext(callback, 1);

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = DVD_IOCTL_REQUEST_ERROR;

    ret = IOS_IoctlAsync(DiFD, DVD_IOCTL_REQUEST_ERROR, &diCommand[freeCommandBuf], sizeof(DVDLowCommand), &diRegValCache, sizeof(DVDLowRegValues),
                         doTransactionCallback, dvdContext);
    if (ret != IPC_RESULT_OK) {
        OSReport(requestErrorMessage, ret);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}

bool DVDLowSetSpinupFlag(u32 spinUp) {
    spinUpValue = spinUp;
    return true;
}

bool DVDLowReset(DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError ret;

    requestInProgress = true;

    dvdContext = newContext(callback, 1);

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = DVD_IOCTL_RESET;
    diCommand[freeCommandBuf].arg[0] = spinUpValue;

    ret = IOS_IoctlAsync(DiFD, DVD_IOCTL_RESET, &diCommand[freeCommandBuf], sizeof(DVDLowCommand), 0, 0, doTransactionCallback, dvdContext);
    if (ret != IPC_RESULT_OK) {
        OSReport(resetErrorMessage, ret);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}

bool DVDLowAudioBufferConfig(BOOL enable, u32 size, DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError ret;

    requestInProgress = true;

    dvdContext = newContext(callback, 1);

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = DVD_IOCTL_AUDIO_BUFFER_CONFIG;
    diCommand[freeCommandBuf].arg[0] = enable;
    diCommand[freeCommandBuf].arg[1] = size;

    ret = IOS_IoctlAsync(DiFD, DVD_IOCTL_AUDIO_BUFFER_CONFIG, &diCommand[freeCommandBuf], sizeof(DVDLowCommand), &diRegValCache,
                         sizeof(DVDLowRegValues), doTransactionCallback, dvdContext);
    if (ret != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowAudioBufferConfig) IOS_IoctlAsync returned error: %d\n", ret);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}

u32 DVDLowGetCoverStatus(void) {
    IOSError rv;

    if (callbackInProgress == true) {
        OSReport("(DVDLowGetCoverStatus): Synch functions can't be called in callbacks\n");
        return false;
    }

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = 0x88;

    rv = IOS_Ioctl(DiFD, 0x88, &(diCommand[freeCommandBuf]), sizeof(DVDLowCommand), coverStatus, sizeof(u32) * 8);

    if (rv != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowGetCoverStatus) IOS_Ioctl returned error: %d\n", rv);
        return 0xdeaddead;
    }

    return coverStatus[0];
}
bool DVDLowReadDvd(u32 strm, u32 retry, void* destAddr, u32 lengthInSectors, u32 lsn, DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError rv;

    requestInProgress = true;
    dvdContext = newContext(callback, 1);

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = 0xD0;
    if (strm == 0) {
        diCommand[freeCommandBuf].arg[0] = 0x0;
    } else {
        diCommand[freeCommandBuf].arg[0] = 0x1;
    }
    if (retry == 0) {
        diCommand[freeCommandBuf].arg[1] = 0x0;
    } else {
        diCommand[freeCommandBuf].arg[1] = 0x1;
    }
    diCommand[freeCommandBuf].arg[2] = lengthInSectors;
    diCommand[freeCommandBuf].arg[3] = lsn;
    readLength = lengthInSectors * 2048;

    rv = IOS_IoctlAsync(DiFD, 0xD0, &(diCommand[freeCommandBuf]), sizeof(DVDLowCommand), destAddr, lengthInSectors * 2048, doTransactionCallback,
                        dvdContext);

    if (rv != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowReadDVD) IOS_IoctlAsync returned error: %d\n", rv);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}
bool DVDLowReadDvdConfig(bool set, u32 type, u32 config, DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError rv;

    requestInProgress = true;
    dvdContext = newContext(callback, 1);

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = 0xD1;
    diCommand[freeCommandBuf].arg[0] = set;
    diCommand[freeCommandBuf].arg[1] = type;
    diCommand[freeCommandBuf].arg[2] = config;

    rv = IOS_IoctlAsync(DiFD, 0xD1, &(diCommand[freeCommandBuf]), sizeof(DVDLowCommand), &diRegValCache, sizeof(DVDLowRegValues), doTransactionCallback,
                        dvdContext);

    if (rv != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowReadDVDConfig) IOS_IoctlAsync returned error: %d\n", rv);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}
bool DVDLowReadDvdCopyright(u32 layer, DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError rv;

    requestInProgress = true;
    dvdContext = newContext(callback, 1);

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = 0x81;
    diCommand[freeCommandBuf].arg[0] = layer;

    rv = IOS_IoctlAsync(DiFD, 0x81, &(diCommand[freeCommandBuf]), sizeof(DVDLowCommand), &diRegValCache, sizeof(DVDLowRegValues), doTransactionCallback,
                        dvdContext);

    if (rv != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowReadDvdCopyright) IOS_IoctlAsync returned error: %d\n", rv);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}
bool DVDLowReadDvdPhysical(DVDVideoPhysical* physical, u32 layer, DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError rv;

    requestInProgress = true;
    dvdContext = newContext(callback, 1);

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = 0x80;
    diCommand[freeCommandBuf].arg[0] = layer;

    rv = IOS_IoctlAsync(DiFD, 0x80, &(diCommand[freeCommandBuf]), sizeof(DVDLowCommand), physical, sizeof(DVDVideoPhysical), doTransactionCallback,
                        dvdContext);

    if (rv != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowReadDvdPhysical) IOS_IoctlAsync returned error: %d\n", rv);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}
bool DVDLowReadDvdDiscKey(DVDVideoDiscKey* diskKey, u32 layer, DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError rv;

    requestInProgress = true;
    dvdContext = newContext(callback, 1);

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = 0x82;
    diCommand[freeCommandBuf].arg[0] = layer;

    rv = IOS_IoctlAsync(DiFD, 0x82, &(diCommand[freeCommandBuf]), sizeof(DVDLowCommand), diskKey, sizeof(DVDVideoDiscKey), doTransactionCallback,
                        dvdContext);

    if (rv != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowReadDvdDiscKey) IOS_IoctlAsync returned error: %d\n", rv);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}
bool DVDLowReportKey(DVDVideoReportKey* reportKey, u32 format, u32 lsn, DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError rv;

    requestInProgress = true;
    dvdContext = newContext(callback, 1);

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = 0xA4;
    diCommand[freeCommandBuf].arg[0] = format >> 16;
    diCommand[freeCommandBuf].arg[1] = lsn;

    rv = IOS_IoctlAsync(DiFD, 0xA4, &diCommand[freeCommandBuf], sizeof(DVDLowCommand), reportKey, sizeof(DVDVideoReportKey), doTransactionCallback,
                        dvdContext);

    if (rv != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowReportKey) IOS_IoctlAsync returned error: %d\n", rv);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}
bool DVDLowOffset(u32 subcmd, u32 offset_4_byte, DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError rv;

    requestInProgress = true;
    dvdContext = newContext(callback, 1);

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = 0xD9;
    if (subcmd == 0) {
        diCommand[freeCommandBuf].arg[0] = 0x0;
    } else {
        diCommand[freeCommandBuf].arg[0] = 0x1;
    }
    diCommand[freeCommandBuf].arg[1] = offset_4_byte;

    rv = IOS_IoctlAsync(DiFD, 0xD9, &(diCommand[freeCommandBuf]), sizeof(DVDLowCommand), &diRegValCache, sizeof(DVDLowRegValues), doTransactionCallback,
                        dvdContext);

    if (rv != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowOffset) IOS_IoctlAsync returned error: %d\n", rv);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}
bool DVDLowStopLaser(DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError rv;

    requestInProgress = true;
    dvdContext = newContext(callback, 1);

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = 0xD2;

    rv = IOS_IoctlAsync(DiFD, 0xD2, &(diCommand[freeCommandBuf]), sizeof(DVDLowCommand), &diRegValCache, sizeof(DVDLowRegValues), doTransactionCallback,
                        dvdContext);

    if (rv != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowStopLaser) IOS_IoctlAsync returned error: %d\n", rv);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}
bool DVDLowReadDiskBca(DVDDiskBca* diskBca, DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError rv;

    requestInProgress = true;
    dvdContext = newContext(callback, 1);

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = 0xDA;
    rv =
        IOS_IoctlAsync(DiFD, 0xDA, &(diCommand[freeCommandBuf]), sizeof(DVDLowCommand), diskBca, sizeof(DVDDiskBca), doTransactionCallback, dvdContext);

    if (rv != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowReadDiskBca) IOS_IoctlAsync returned error: %d\n", rv);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}
bool DVDLowSerMeasControl(DVDLowDriveSer* ser, bool clear, bool enable, DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError rv;

    requestInProgress = true;
    dvdContext = newContext(callback, 1);

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = 0xDF;
    diCommand[freeCommandBuf].arg[0] = clear;
    diCommand[freeCommandBuf].arg[1] = enable;
    rv =
        IOS_IoctlAsync(DiFD, 0xDF, &(diCommand[freeCommandBuf]), sizeof(DVDLowCommand), ser, sizeof(DVDLowDriveSer), doTransactionCallback, dvdContext);

    if (rv != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowSerMeasControl) IOS_IoctlAsync returned error: %d\n", rv);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}
bool DVDLowRequestDiscStatus(DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError rv;

    requestInProgress = true;
    dvdContext = newContext(callback, 1);

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = 0xDB;

    rv = IOS_IoctlAsync(DiFD, 0xDB, &(diCommand[freeCommandBuf]), sizeof(DVDLowCommand), &diRegValCache, sizeof(DVDLowRegValues), doTransactionCallback,
                        dvdContext);

    if (rv != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowRequestDiscStatus) IOS_IoctlAsync returned error: %d\n", rv);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}
bool DVDLowRequestRetryNumber(DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError rv;

    requestInProgress = true;
    dvdContext = newContext(callback, 1);

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = 0xDC;

    rv = IOS_IoctlAsync(DiFD, 0xDC, &(diCommand[freeCommandBuf]), sizeof(DVDLowCommand), &diRegValCache, sizeof(DVDLowRegValues), doTransactionCallback,
                        dvdContext);

    if (rv != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowRequestRetryNumber) IOS_IoctlAsync returned error: %d\n", rv);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}

bool DVDLowSetMaximumRotation(u32 subcmd, DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError ret;

    requestInProgress = true;

    dvdContext = newContext(callback, 1);

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = DVD_IOCTL_SET_MAX_ROTATION;
    diCommand[freeCommandBuf].arg[0] = (subcmd >> 16) & 3;

    ret =
        IOS_IoctlAsync(DiFD, DVD_IOCTL_SET_MAX_ROTATION, &diCommand[freeCommandBuf], sizeof(DVDLowCommand), 0, 0, doTransactionCallback, dvdContext);
    if (ret != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowSetMaxRotation) IOS_IoctlAsync returned error: %d\n", ret);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}

bool DVDLowRead(void* destAddr, u32 length, u32 wordOffset, DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError ret;

    if (!IS_ALIGNED(destAddr)) {
        OSReport("(DVDLowRead): ERROR - destAddr buffer is not 32 byte aligned\n");
        return false;
    }

    requestInProgress = true;

    dvdContext = newContext(callback, 1);

    readLength = length;
    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = DVD_IOCTL_READ;
    diCommand[freeCommandBuf].arg[0] = length;
    diCommand[freeCommandBuf].arg[1] = wordOffset;

    ret =
        IOS_IoctlAsync(DiFD, DVD_IOCTL_READ, &diCommand[freeCommandBuf], sizeof(DVDLowCommand), destAddr, length, doTransactionCallback, dvdContext);
    if (ret != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowRead) IOS_IoctlAsync returned error: %d\n", ret);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}

bool DVDLowSeek(u32 wordOffset, DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError ret;

    requestInProgress = true;

    dvdContext = newContext(callback, 1);

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = DVD_IOCTL_SEEK;
    diCommand[freeCommandBuf].arg[0] = wordOffset;

    ret = IOS_IoctlAsync(DiFD, DVD_IOCTL_SEEK, &diCommand[freeCommandBuf], sizeof(DVDLowCommand), 0, 0, doTransactionCallback, dvdContext);
    if (ret != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowSeek) IOS_IoctlAsync returned error: %d\n", ret);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}

u32 DVDLowGetCoverReg(void) {
    IOSError rv;

    if (callbackInProgress == true) {
        OSReport("(DVDLowGetCoverReg): Synch functions can't be called in callbacks\n");
        return false;
    }

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = 0x7A;

    rv = IOS_Ioctl(DiFD, 0x7A, &(diCommand[freeCommandBuf]), sizeof(DVDLowCommand), coverRegister, sizeof(u32) * 8);

    if (rv != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowGetCoverReg) IOS_Ioctl returned error: %d\n", rv);
        return false;
    }

    return coverRegister[0];
}

u32 DVDLowGetCoverRegister() {
    return diRegValCache.diCoverReg;
}

u32 DVDLowGetStatusRegister() {
    return statusRegister[0];
}

bool DVDLowPrepareCoverRegister(DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError ret;

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = DVD_IOCTL_PREPARE_COVER_REGISTER;

    requestInProgress = true;

    dvdContext = newContext(callback, 1);

    ret = IOS_IoctlAsync(DiFD, DVD_IOCTL_PREPARE_COVER_REGISTER, &diCommand[freeCommandBuf], sizeof(DVDLowCommand), registerBuf, sizeof(registerBuf),
                         doPrepareCoverRegisterCallback, dvdContext);
    if (ret != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowPrepareCoverRegsiter) IOS_IoctlAsync returned error: %d\n", ret);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}

bool DVDLowPrepareStatusRegister(DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError ret;

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = DVD_IOCTL_PREPARE_STATUS_REGISTER;

    requestInProgress = true;

    dvdContext = newContext(callback, 1);

    ret = IOS_IoctlAsync(DiFD, DVD_IOCTL_PREPARE_STATUS_REGISTER, &diCommand[freeCommandBuf], sizeof(DVDLowCommand), statusRegister,
                         sizeof(statusRegister), doTransactionCallback, dvdContext);
    if (ret != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowPrepareStatusRegsiter) IOS_IoctlAsync returned error: %d\n", ret);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}

u32 DVDLowGetImmBufferReg() {
    return diRegValCache.diImmValue;
}

bool DVDLowUnmaskStatusInterrupts() {
    return true;
}

bool DVDLowMaskCoverInterrupt() {
    return true;
}

bool DVDLowClearCoverInterrupt(DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError ret;

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = DVD_IOCTL_CLEAR_COVER_INTERRUPT;

    requestInProgress = true;

    dvdContext = newContext(callback, 1);

    ret = IOS_IoctlAsync(DiFD, DVD_IOCTL_CLEAR_COVER_INTERRUPT, &diCommand[freeCommandBuf], sizeof(DVDLowCommand), 0, 0, doTransactionCallback,
                         dvdContext);
    if (ret != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowClearCoverInterrupt) IOS_IoctlAsync returned error: %d\n", ret);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}

s32 DVDLowGetLastEticketError() {
    return lastTicketError[0];
}

BOOL __DVDLowTestAlarm(OSAlarm* alarm) {
    return FALSE;
}

bool DVDLowEnableDvdVideo(const bool enable, DVDLowCallback callback) {
    DVDLowContext* dvdContext;
    IOSError rv;

    nextCommandBuf(&freeCommandBuf);
    diCommand[freeCommandBuf].diCmd = 0x8E;
    diCommand[freeCommandBuf].arg[0] = enable;
    requestInProgress = true;
    dvdContext = newContext(callback, 1);

    rv = IOS_IoctlAsync(DiFD, 0x8E, &(diCommand[freeCommandBuf]), sizeof(DVDLowCommand), NULL, 0, doTransactionCallback, dvdContext);

    if (rv != IPC_RESULT_OK) {
        OSReport("@@@ (DVDLowEnableDvdVideo) IOS_IoctlAsync returned error: %d\n", rv);
        dvdContext->inUse = false;
        return false;
    }

    return true;
}
