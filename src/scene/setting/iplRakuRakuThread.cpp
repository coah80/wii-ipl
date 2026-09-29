#include <revolution/os.h>
#include <revolution/soex.h>
#include <revolution/mem.h>

#include <cstring>

#include <revolution/ncd/NCDTypes.h>

#include "utility/iplThread.h"
#include "egg/core/eggHeap.h"

extern "C" {
u32 ATERMi_ApConfigGetVersion(void);
s32 ATERMi_ApConfigStart(s32 priority, u32 size, void (*callback)(u32* data),
                         void* (*alloc)(u32 size), void (*free_)(u32 size),
                         u32 stackSize);
s32 ATERMi_ApConfigGetState(u32* state);
s32 ATERMi_ApConfigEnd(void);
s32 ATERMi_ApConfigGetResult(void* result);
}

namespace ipl {
    namespace scene {
        extern "C" {
        static void* RakuRakuThread_813FDEF0(u32 id, s32 size);
        static void RakuRakuThread_813FDEFC(u32 id, void* ptr, s32 align);
        static void* RakuRakuThread_813FDF08(u32 size);
        static void RakuRakuThread_813FDF18(u32 size);
        }

        typedef struct ATERMResult {
            char ssid[0x20];   // 0x00
            s32 type;          // 0x20
            u32 keyId;         // 0x24
            u8 keys[4][0x20];  // 0x28
            char key[0x40];    // 0xA8
        } ATERMResult;         // 0xE8

        typedef struct RakuRakuWork {
            u32 state;         // 0x00
            u32 unk_0x04;      // 0x04
            s32 result;        // 0x08
            ATERMResult data;  // 0x0C
        } RakuRakuWork;        // 0xF4

        typedef struct QueueWork {
            OSMessageQueue queue;  // 0x00
            OSMessage msg;         // 0x20
        } QueueWork;               // 0x24

        MEMAllocator mAllocator;
        RakuRakuWork mWork;
        QueueWork mQueue;

        static u32 sStartTimeHi;
        static u32 sStartTimeLo;
        static u8 sStarted;
        static OSMessage sMsgArray;
        static s32 sState = 1;

        class RakuRakuThread : public utility::ut_thread {
        public:
            RakuRakuThread(EGG::Heap* heap);

            virtual ~RakuRakuThread();    // 0x08
            virtual void* Run();          // 0x0C
            virtual void unk_0x2C() = 0;  // 0x2C

            static void RakuRakuThread_813FDA04(u32* data);

            void destroy();
            int start();
            int getState();
            void cancel();
            int finish(NCDApConfig* config, int* result);
            void printInfo();

        private:
            s32 mUnk_0x32C;           // 0x32C
            s32 mEndFlag;             // 0x330
            s32 mCreated;             // 0x334
            s32 mThreadPriority;      // 0x338
            u8* mpWorkBuffer;         // 0x33C
            u8* mpStackBuffer;        // 0x340
            MEMHeapHandle mpExpHeap;  // 0x344
        };

        void RakuRakuThread::RakuRakuThread_813FDA04(u32* data) {
            BOOL level = OSDisableInterrupts();
            mWork.state = data[0];
            mWork.unk_0x04 = data[1];
            mWork.result = data[2];
            OSTime t = OSGetTime();
            sStartTimeLo = (u32)t;
            sStartTimeHi = (u32)(t >> 32);
            OSRestoreInterrupts(level);
        }

        RakuRakuThread::RakuRakuThread(EGG::Heap* heap) : utility::ut_thread() {
            u32 version = ATERMi_ApConfigGetVersion();

            if ((((version >> 12) & 0xF) * 10 + ((version >> 8) & 0xF)) != 1) {
                mpWorkBuffer = NULL;
            }
            else {
                mpWorkBuffer = (u8*)heap->alloc(0x40000, 0x20);
                mpStackBuffer = (u8*)heap->alloc(0x1000, 0x20);
            }

            mpExpHeap = NULL;
            sStarted = 0;
            mEndFlag = 0;
            mCreated = 0;
            OSInitMessageQueue(&mQueue.queue, &sMsgArray, 1);
        }

        RakuRakuThread::~RakuRakuThread() {
            if (mCreated != 0) {
                OSJamMessage(&mQueue.queue, (OSMessage)2, TRUE);
                WaitForThreadExit();
            }
            destroy();
        }

        void RakuRakuThread::destroy() {
            if (sStarted != 0) {
                OSSendMessage(&mQueue.queue, (OSMessage)1, FALSE);
                u32 tick = OSGetTick();
                while ((u32)(OSGetTick() - tick) / (OS_TIMER_CLOCK / 1000)
                       < 0x7D0)
                {
                    u32 state[4];
                    if (ATERMi_ApConfigGetState(state) == 1 && (s32)state[0] == 7) {
                        break;
                    }
                }
                SOFinish();
                sStarted = 0;
            }

            if (mpExpHeap != NULL) {
                MEMDestroyExpHeap(mpExpHeap);
                memset(&mAllocator, 0, 0x10);
                mpExpHeap = NULL;
            }
        }

        int RakuRakuThread::start() {
            SOLibraryConfig config;
            MEMAllocator* alloc = &mAllocator;

            if (sStarted != 0 || mpWorkBuffer == NULL) {
                return 0;
            }

            BOOL level = OSDisableInterrupts();
            OSTime t = OSGetTime();
            sStartTimeLo = (u32)t;
            sStartTimeHi = (u32)(t >> 32);

            mpExpHeap = MEMCreateExpHeapEx(mpWorkBuffer, 0x40000, 2);
            MEMInitAllocatorForExpHeap(&mAllocator, mpExpHeap, 0x20);

            mThreadPriority = OSGetThreadPriority(OSGetCurrentThread()) - 1;

            sStarted = 1;
            mEndFlag = 0;
            memset((u8*)alloc + 0x1C, 0, 0xE8);
            memset((u8*)alloc + 0x10, 0, 0xC);

            config.alloc = RakuRakuThread_813FDEF0;
            config.free = RakuRakuThread_813FDEFC;
            SOInit(&config);

            ATERMi_ApConfigStart(mThreadPriority, 0xC8,
                               RakuRakuThread_813FDA04,
                               RakuRakuThread_813FDF08,
                               RakuRakuThread_813FDF18, 0x1000);

            if (mCreated == 0) {
                mCreated = 1;
                memset(mpStackBuffer, 0, 4);
                Create(mpStackBuffer, 0x1000, mThreadPriority - 1, TRUE);
                OSReport("RakuRakuThread (for End function) start with prio(%d) \n",
                         mThreadPriority);
            }

            OSRestoreInterrupts(level);
            return 1;
        }

        void* RakuRakuThread::Run() {
            u32 magic = 0x97654321;
            OSMessage msg;

            for (;;) {
                while (OSReceiveMessage(&mQueue.queue, &msg, FALSE) != FALSE) {
                    if ((s32)msg == 2) {
                        return this;
                    }
                }
                OSReceiveMessage(&mQueue.queue, &msg, TRUE);
                if ((s32)msg == 2) {
                    break;
                }
                *(u32*)(mpStackBuffer + 0x3FC0) = magic;
                ATERMi_ApConfigEnd();
                mEndFlag = 1;
                if (mCreated == 0) {
                    break;
                }
            }
            return this;
        }

        extern "C" {
        static void* RakuRakuThread_813FDEF0(u32 id, s32 size) {
            return MEMAllocFromAllocator(&mAllocator, size);
        }

        static void RakuRakuThread_813FDEFC(u32 id, void* ptr, s32 align) {
            MEMFreeToAllocator(&mAllocator, ptr);
        }

        static void* RakuRakuThread_813FDF08(u32 size) {
            return MEMAllocFromAllocator(&mAllocator, size);
        }

        static void RakuRakuThread_813FDF18(u32 size) {
            MEMFreeToAllocator(&mAllocator, (void*)size);
        }
        }

        int RakuRakuThread::getState() {
            if (sStarted == 0) {
                return 0;
            }

            BOOL level = OSDisableInterrupts();

            switch (mWork.state) {
            case 1:
                sState = 1;
                break;
            case 2:
                sState = 2;
                break;
            case 3:
                sState = 2;
                break;
            case 4:
                sState = 4;
                break;
            case 5:
                sState = 5;
                break;
            case 6:
                sState = 6;
                break;
            case 7:
                sState = 7;
                break;
            default:
                sState = 1;
                break;
            }

            if (sState != 6 && sState != 7) {
                if (((u32)OSGetTime() - (u32)sStartTimeLo)
                        / (OS_TIMER_CLOCK / 1000)
                    >= 90000)
                {
                    OSSendMessage(&mQueue.queue, (OSMessage)1, FALSE);
                }
            }

            OSRestoreInterrupts(level);
            return sState;
        }

        void RakuRakuThread::cancel() {
            OSSendMessage(&mQueue.queue, (OSMessage)1, FALSE);
        }

        int RakuRakuThread::finish(NCDApConfig* config, int* result) {
            u8* ws = (u8*)&mAllocator;
            RakuRakuWork* wk = (RakuRakuWork*)(ws + 0x10);

            if (sStarted == 0) {
                if (result != NULL) {
                    *result = -0x63;
                }
                return 1;
            }

            if ((u32)(wk->state - 6) <= 1) {
                if (mEndFlag == 0) {
                    if ((s32)wk->state == 6) {
                        ATERMi_ApConfigGetResult(&wk->data);
                        printInfo();
                    }
                    OSSendMessage((OSMessageQueue*)(ws + 0x104), (OSMessage)1, FALSE);
                    return 0;
                }
                else {
                    SOFinish();
                    sStarted = 0;
                    destroy();
                }
            }
            else {
                return 0;
            }

            if (config != NULL) {
                memcpy(config->ssid, wk->data.ssid, 0x20);
                config->ssidLength = strlen(wk->data.ssid);

                ATERMResult* data = &wk->data;

                if (data->type == 1) {
                    config->privacy.mode = 1;
                    config->privacy.wep40.keyId = data->keyId;
                    for (int i = 0; i < 4; i++) {
                        memcpy(config->privacy.wep40.key[i],
                               data->keys[i], 5);
                    }
                }
                else if (data->type == 2) {
                    config->privacy.mode = 2;
                    config->privacy.wep104.keyId = data->keyId;
                    for (int i = 0; i < 4; i++) {
                        memcpy(config->privacy.wep104.key[i],
                               data->keys[i], 0xD);
                    }
                }
                else if (data->type == 4) {
                    config->privacy.mode = 4;
                    memcpy(config->privacy.tkip.key, data->key, 0x40);
                    config->privacy.tkip.keyLen = strlen(data->key);
                }
                else if (data->type == 5) {
                    config->privacy.mode = 6;
                    memcpy(config->privacy.aes.key, data->key, 0x40);
                    config->privacy.aes.keyLen = strlen(data->key);
                }
            }

            if (result != NULL) {
                *result = wk->result;
            }
            return 1;
        }

#pragma dont_inline on
        void RakuRakuThread::printInfo() {
        }
#pragma dont_inline reset

    }  // namespace scene
}  // namespace ipl
