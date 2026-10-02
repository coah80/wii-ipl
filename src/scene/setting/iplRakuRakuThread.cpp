#include "utility/iplThread.h"
#include <egg/core.h>
#include <revolution/mem.h>
#include <revolution/ncd.h>
#include <revolution/soex.h>
#include <string.h>

struct RakuProgress {
    s32 state;
    int remainingTime;
    int result;
};
struct RakuConfiguration {
    char ssid[32];
    s32 security;
    u32 keyId;
    char wepKeys[4][32];
    char passphrase[64];
};
extern "C" {
int ATERMi_ApConfigGetVersion();
int ATERMi_ApConfigGetState(RakuProgress* progress);
int ATERMi_ApConfigGetResult(RakuConfiguration* configuration);
int ATERMi_ApConfigStart(int priority, u32 scanLimit, void (*callback)(RakuProgress*),
                        void* (*allocate)(u32), void (*release)(void*), u32 stackSize);
int ATERMi_ApConfigEnd();
}

namespace ipl {
namespace scene {
extern "C" MEMAllocator sRakuAllocator;
MEMAllocator sRakuAllocator;
extern "C" RakuProgress sRakuStatus;
RakuProgress sRakuStatus;
extern "C" RakuConfiguration sRakuConfiguration;
RakuConfiguration sRakuConfiguration;
extern "C" OSMessageQueue sRakuMsgQueue;
OSMessageQueue sRakuMsgQueue;
static u32 startTimeHigh = 0;
static u32 startTimeLow = 0;
static bool active = false;
static OSMessage messageSlot = NULL;
static int displayState = 1;

extern "C" {
static void* RakuSocketAlloc(u32, s32 size);
static void RakuSocketFree(u32, void* block, s32);
static void* RakuAtermAlloc(u32 size);
static void RakuAtermFree(void* block);
}

struct RakuStack {
    u32 storage[4080];
    u32 sentinel;
};
class RakuRakuThread : public utility::ut_thread {
public:
    RakuRakuThread(EGG::Heap* heap);
    virtual ~RakuRakuThread();
    virtual void* Run();
    virtual void unk_0x2C() = 0;
    static void syncRakuProgress(RakuProgress* progress);
    void destroy();
    int start();
    int getState();
    int cancel();
    int finish(NCDApConfig* config, int* result);
    void printInfo() NO_INLINE;
private:
    int mReserved;
    int mFinished;
    int mRunning;
    int mPriority;
    void* mHeapBuffer;
    RakuStack* mStack;
    MEMHeapHandle mHeap;
};

void RakuRakuThread::syncRakuProgress(RakuProgress* progress) {
    BOOL interrupts = OSDisableInterrupts();
    sRakuStatus = *progress;
    OSTime time = OSGetTime();
    startTimeHigh = time >> 32;
    startTimeLow = time;
    OSRestoreInterrupts(interrupts);
}

RakuRakuThread::RakuRakuThread(EGG::Heap* heap) : utility::ut_thread() {
    u32 version = ATERMi_ApConfigGetVersion();
    if (((version >> 12) & 15) * 10 + ((version >> 8) & 15) != 1) {
        mHeapBuffer = NULL;
    } else {
        mHeapBuffer = heap->alloc(0x40000, 32);
        mStack = (RakuStack*)heap->alloc(4096, 32);
    }
    mHeap = NULL;
    active = false;
    mFinished = 0;
    mRunning = 0;
    OSInitMessageQueue(&sRakuMsgQueue, &messageSlot, 1);
}

RakuRakuThread::~RakuRakuThread() {
    if (mRunning) {
        OSJamMessage(&sRakuMsgQueue, (OSMessage)2, 1);
        WaitForThreadExit();
    }
    destroy();
}

void RakuRakuThread::destroy() {
    if (active) {
        OSSendMessage(&sRakuMsgQueue, (OSMessage)1, 0);
        u32 start = OSGetTick();
        while ((u32)(OSGetTick() - start) / (OS_TIMER_CLOCK / 1000) < 2000) {
            RakuProgress progress;
            if (ATERMi_ApConfigGetState(&progress) == 1 && progress.state == 7) {
                break;
            }
        }
        SOFinish();
        active = false;
    }
    if (mHeap != NULL) {
        MEMDestroyExpHeap(mHeap);
        memset(&sRakuAllocator, 0, sizeof(MEMAllocator));
        mHeap = NULL;
    }
}

int RakuRakuThread::start() {
    if (active || mHeapBuffer == NULL) {
        return 0;
    }
    BOOL interrupts = OSDisableInterrupts();
    OSTime time = OSGetTime();
    startTimeHigh = time >> 32;
    startTimeLow = time;
    mHeap = MEMCreateExpHeapEx(mHeapBuffer, 0x40000, 2);
    MEMInitAllocatorForExpHeap(&sRakuAllocator, mHeap, 32);
    mPriority = OSGetThreadPriority(OSGetCurrentThread()) - 1;
    active = true;
    mFinished = 0;
    memset(&sRakuConfiguration, 0, sizeof(RakuConfiguration));
    memset(&sRakuStatus, 0, sizeof(RakuProgress));
    SOLibraryConfig socketConfig;
    socketConfig.alloc = RakuSocketAlloc;
    socketConfig.free = RakuSocketFree;
    SOInit(&socketConfig);
    ATERMi_ApConfigStart(mPriority, 200,
        syncRakuProgress,
        RakuAtermAlloc, RakuAtermFree, 4096);
    if (!mRunning) {
        mRunning = 1;
        memset(mStack, 0, 4);
        Create(mStack, 4096, mPriority - 1, true);
        OSReport("RakuRakuThread (for End function) start with prio(%d) \n", mPriority);
    }
    OSRestoreInterrupts(interrupts);
    return 1;
}

void* RakuRakuThread::Run() {
    OSMessage message;
    while (true) {
        while (OSReceiveMessage(&sRakuMsgQueue, &message, 0)) {
            if ((s32)message == 2) {
                return this;
            }
        }
        OSReceiveMessage(&sRakuMsgQueue, &message, 1);
        if ((s32)message == 2) {
            break;
        }
        mStack->sentinel = 0x97654321;
        ATERMi_ApConfigEnd();
        mFinished = 1;
        if (!mRunning) {
            break;
        }
    }
    return this;
}

static void* RakuSocketAlloc(u32, s32 size) {
    return MEMAllocFromAllocator(&sRakuAllocator, size);
}
static void RakuSocketFree(u32, void* block, s32) {
    MEMFreeToAllocator(&sRakuAllocator, block);
}
static void* RakuAtermAlloc(u32 size) {
    return MEMAllocFromAllocator(&sRakuAllocator, size);
}
static void RakuAtermFree(void* block) {
    MEMFreeToAllocator(&sRakuAllocator, block);
}

int RakuRakuThread::getState() {
    if (!active) {
        return 0;
    }
    BOOL interrupts = OSDisableInterrupts();
    switch (sRakuStatus.state) {
    case 1: displayState = 1; break;
    case 2: displayState = 2; break;
    case 3: displayState = 2; break;
    case 4: displayState = 4; break;
    case 5: displayState = 5; break;
    case 6: displayState = 6; break;
    case 7: displayState = 7; break;
    default: displayState = 1; break;
    }
    if (displayState != 6 && displayState != 7 &&
        ((u32)OSGetTime() - startTimeLow) / (OS_TIMER_CLOCK / 1000) >= 90000) {
        OSSendMessage(&sRakuMsgQueue, (OSMessage)1, 0);
    }
    OSRestoreInterrupts(interrupts);
    return displayState;
}

int RakuRakuThread::cancel() {
    return OSSendMessage(&sRakuMsgQueue, (OSMessage)1, 0);
}

inline void copyRakuPrivacy(NCDApConfig* config, const RakuConfiguration* settings) {
    if (settings->security == 1) {
        config->privacy.mode = 1;
        config->privacy.wep40.keyId = settings->keyId;
        for (int index = 0; index < 4; ++index) {
            memcpy(config->privacy.wep40.key[index], settings->wepKeys[index], 5);
        }
    } else if (settings->security == 2) {
        config->privacy.mode = 2;
        config->privacy.wep104.keyId = settings->keyId;
        for (int index = 0; index < 4; ++index) {
            memcpy(config->privacy.wep104.key[index], settings->wepKeys[index], 13);
        }
    } else if (settings->security == 4) {
        config->privacy.mode = 4;
        memcpy(config->privacy.tkip.key, settings->passphrase, 64);
        config->privacy.tkip.keyLen = strlen(settings->passphrase);
    } else if (settings->security == 5) {
        config->privacy.mode = 6;
        memcpy(config->privacy.aes.key, settings->passphrase, 64);
        config->privacy.aes.keyLen = strlen(settings->passphrase);
    }
}

int RakuRakuThread::finish(NCDApConfig* config, int* result) {
    if (!active) {
        if (result != NULL) {
            *result = -99;
        }
        return 1;
    }
    s32 state = sRakuStatus.state;
    if ((u32)(state - 6) <= 1) {
        if (!mFinished) {
            if (state == 6) {
                ATERMi_ApConfigGetResult(&sRakuConfiguration);
                printInfo();
            }
            OSSendMessage(&sRakuMsgQueue, (OSMessage)1, 0);
            return 0;
        }
        SOFinish();
        active = false;
        destroy();
    } else {
        return 0;
    }
    if (config != NULL) {
        memcpy(config->ssid, sRakuConfiguration.ssid, 32);
        config->ssidLength = strlen(sRakuConfiguration.ssid);
        copyRakuPrivacy(config, &sRakuConfiguration);
    }
    if (result != NULL) {
        *result = sRakuStatus.result;
    }
    return 1;
}

void RakuRakuThread::printInfo() {
}
}
}
