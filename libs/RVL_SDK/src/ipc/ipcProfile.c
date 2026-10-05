#include <revolution/os.h>

#include <private/ipc.h>

#define MAX_REQUEST 32

static u32 IpcNumPendingReqs = 0;
static u32 IpcNumUnIssuedReqs = 0;

static s32 IpcFdArray[MAX_REQUEST] = {0};
static u32 IpcReqPtrArray[MAX_REQUEST];

static void AddReqInfo(void* ptr, s32 fd);
static void DelReqInfo(void* ptr, s32 fd);

void IPCiProfInit() {
    u32 i;

    IpcNumPendingReqs = 0;
    IpcNumUnIssuedReqs = 0;

    for (i = 0; i < MAX_REQUEST; i++) {
        IpcReqPtrArray[i] = 0;
        IpcFdArray[i] = -1;
    }
}

void IPCiProfQueueReq(void* req, s32 fd) {
    ++IpcNumPendingReqs;
    ++IpcNumUnIssuedReqs;
    AddReqInfo(req, fd);
}

static void AddReqInfo(void* ptr, s32 fd) {
    u32 i;

    for (i = 0; i < MAX_REQUEST; i++) {
        if (IpcReqPtrArray[i] == 0 && IpcFdArray[i] == -1) {
            IpcReqPtrArray[i] = (u32)ptr;
            IpcFdArray[i] = fd;
            break;
        }
    }
}

void IPCiProfAck() {
    --IpcNumUnIssuedReqs;
}

void IPCiProfReply(void* req, s32 fd) {
    --IpcNumPendingReqs;
    DelReqInfo(req, fd);
}

static void DelReqInfo(void* ptr, s32 fd) {
    u32 i;

    for (i = 0; i < MAX_REQUEST; i++) {
        if (IpcReqPtrArray[i] == (u32)ptr && IpcFdArray[i] == fd) {
            IpcReqPtrArray[i] = 0;
            IpcFdArray[i] = -1;
            break;
        }
    }
}
