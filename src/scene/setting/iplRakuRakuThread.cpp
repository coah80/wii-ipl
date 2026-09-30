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
extern "C" MEMAllocator RakuRakuThread_810BDDD0;
MEMAllocator RakuRakuThread_810BDDD0;
struct RakuStatus {
    RakuProgress progress;
    RakuConfiguration configuration;
};
extern "C" RakuStatus RakuRakuThread_810BDDE0;
RakuStatus RakuRakuThread_810BDDE0;
extern "C" OSMessageQueue RakuRakuThread_810BDED4;
OSMessageQueue RakuRakuThread_810BDED4;
static OSTime startTime;
static bool active;
static OSMessage messageSlot;
static int displayState = 1;

extern "C" {
static void* RakuRakuThread_813FDEF0(u32, s32 size);
static void RakuRakuThread_813FDEFC(u32, void* block, s32);
static void* RakuRakuThread_813FDF08(u32 size);
static void RakuRakuThread_813FDF18(void* block);
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
    void RakuRakuThread_813FDA04();
    static void progressCallback(RakuProgress* progress);
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

void RakuRakuThread::RakuRakuThread_813FDA04() {
    BOOL interrupts = OSDisableInterrupts();
    RakuRakuThread_810BDDE0.progress = *(RakuProgress*)this;
    startTime = OSGetTime();
    OSRestoreInterrupts(interrupts);
}

void RakuRakuThread::progressCallback(RakuProgress* progress) {
    ((RakuRakuThread*)progress)->RakuRakuThread_813FDA04();
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
    OSInitMessageQueue(&RakuRakuThread_810BDED4, &messageSlot, 1);
}

RakuRakuThread::~RakuRakuThread() {
    if (mRunning) {
        OSJamMessage(&RakuRakuThread_810BDED4, (OSMessage)2, 1);
        WaitForThreadExit();
    }
    destroy();
}

void RakuRakuThread::destroy() {
    if (active) {
        OSSendMessage(&RakuRakuThread_810BDED4, (OSMessage)1, 0);
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
        memset(&RakuRakuThread_810BDDD0, 0, sizeof(MEMAllocator));
        mHeap = NULL;
    }
}

int RakuRakuThread::start() {
    if (active || mHeapBuffer == NULL) {
        return 0;
    }
    BOOL interrupts = OSDisableInterrupts();
    startTime = OSGetTime();
    mHeap = MEMCreateExpHeapEx(mHeapBuffer, 0x40000, 2);
    MEMInitAllocatorForExpHeap(&RakuRakuThread_810BDDD0, mHeap, 32);
    mPriority = OSGetThreadPriority(OSGetCurrentThread()) - 1;
    active = true;
    mFinished = 0;
    memset(&RakuRakuThread_810BDDE0.configuration, 0, sizeof(RakuConfiguration));
    memset(&RakuRakuThread_810BDDE0.progress, 0, sizeof(RakuProgress));
    SOLibraryConfig socketConfig;
    socketConfig.alloc = RakuRakuThread_813FDEF0;
    socketConfig.free = RakuRakuThread_813FDEFC;
    SOInit(&socketConfig);
    ATERMi_ApConfigStart(mPriority, 200,
        progressCallback,
        RakuRakuThread_813FDF08, RakuRakuThread_813FDF18, 4096);
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
        while (OSReceiveMessage(&RakuRakuThread_810BDED4, &message, 0)) {
            if ((s32)message == 2) {
                return this;
            }
        }
        OSReceiveMessage(&RakuRakuThread_810BDED4, &message, 1);
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

static void* RakuRakuThread_813FDEF0(u32, s32 size) {
    return MEMAllocFromAllocator(&RakuRakuThread_810BDDD0, size);
}
static void RakuRakuThread_813FDEFC(u32, void* block, s32) {
    MEMFreeToAllocator(&RakuRakuThread_810BDDD0, block);
}
static void* RakuRakuThread_813FDF08(u32 size) {
    return MEMAllocFromAllocator(&RakuRakuThread_810BDDD0, size);
}
static void RakuRakuThread_813FDF18(void* block) {
    MEMFreeToAllocator(&RakuRakuThread_810BDDD0, block);
}

int RakuRakuThread::getState() {
    if (!active) {
        return 0;
    }
    BOOL interrupts = OSDisableInterrupts();
    switch (RakuRakuThread_810BDDE0.progress.state) {
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
        ((u32)OSGetTime() - (u32)startTime) / (OS_TIMER_CLOCK / 1000) >= 90000) {
        OSSendMessage(&RakuRakuThread_810BDED4, (OSMessage)1, 0);
    }
    OSRestoreInterrupts(interrupts);
    return displayState;
}

int RakuRakuThread::cancel() {
    return OSSendMessage(&RakuRakuThread_810BDED4, (OSMessage)1, 0);
}

int RakuRakuThread::finish(NCDApConfig* config, int* result) {
    if (!active) {
        if (result != NULL) {
            *result = -99;
        }
        return 1;
    }
    s32 state = RakuRakuThread_810BDDE0.progress.state;
    if ((u32)(state - 6) > 1) {
        return 0;
    }
    if (!mFinished) {
        if (state == 6) {
            ATERMi_ApConfigGetResult(&RakuRakuThread_810BDDE0.configuration);
            printInfo();
        }
        OSSendMessage(&RakuRakuThread_810BDED4, (OSMessage)1, 0);
        return 0;
    }
    SOFinish();
    active = false;
    destroy();
    if (config != NULL) {
        RakuConfiguration* settings = &RakuRakuThread_810BDDE0.configuration;
        memcpy(config->ssid, settings->ssid, 32);
        config->ssidLength = strlen(settings->ssid);
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
    if (result != NULL) {
        *result = RakuRakuThread_810BDDE0.progress.result;
    }
    return 1;
}

void RakuRakuThread::printInfo() {
}
}
}
