#include <revolution/os.h>

#include <cstring>

#include <egg/core.h>

#include <revolution/mem.h>
#include <revolution/net.h>
#include <revolution/soex.h>
#include <revolution/ncd.h>

#include "utility/iplThread.h"

extern "C" {
int AOSSi_Init(void* config);
int AOSSi_InitLocal(SOAlloc alloc, SOFree free_);
int AOSSi_EndLocal(void);
int AOSSi_Cancel(void);
int AOSS_SetCallback(void (*callback)(void));
}

namespace ipl {
    namespace scene {
        class USBAPThread {
        public:
            static void callback();
        };

        MEMAllocator m_allocator;

        typedef struct AOSSResult {
            u8 wep40Key[4][6];     // 0x000
            char wep40Ssid[0x20];  // 0x018
            u8 pad_0x38;           // 0x038
            u8 wep104Key[4][0xE];  // 0x039
            char wep104Ssid[0x20]; // 0x071
            u8 pad_0x91;           // 0x091
            char tkipKey[0x40];    // 0x092
            char tkipSsid[0x20];   // 0x0D2
            u8 pad_0xF2;           // 0x0F2
            char aesKey[0x40];     // 0x0F3
            char aesSsid[0x20];    // 0x133
            u8 pad_0x153[2];       // 0x153
        } AOSSResult;              // 0x155

        typedef struct AOSSConfig {
            u16 version;           // 0x000
            u8 interfaceType;           // 0x002
            u16 ssidLength;          // 0x004
            u8 name[3];            // 0x006
            u8 pad_0x09[0xFD];     // 0x009
            u16 connectionAttemptLimit;         // 0x106
            u16 responseWaitCount;         // 0x108
            u16 requestAttemptLimit;         // 0x10A
            u16 requestRetryDelay;         // 0x10C
            u16 socketTimeoutMs;         // 0x10E
            u8 mac[6];             // 0x110
            u8 result;             // 0x116
            AOSSResult security;   // 0x117
        } AOSSConfig;              // 0x26C

        static u32 sAOSSStartTimeHi;
        static u32 sAOSSStartTimeLo;
        static s32 sAOSSState;
        static s32 sAOSSReservedState;

        struct AOSSStack {
            u32 storage[4080];
            u32 sentinel;
        };

        class AOSSThread : public utility::ut_thread {
        public:
            AOSSThread(EGG::Heap* heap);

            virtual ~AOSSThread();        // 0x08
            virtual void* Run();          // 0x0C
            virtual void unk_0x2C() = 0;  // 0x2C

            void destroy(int flag);
            int start();
            int cancel();
            int finish(NCDAossConfig* config, int* result);
            void printInfo();

            static void* aossAlloc(u32 id, s32 size);
            static void aossFree(u32 id, void* ptr, s32 align);

        private:
            s32 mState;                // 0x32C
            s32 mThreadPriority;       // 0x330
            AOSSStack* mpStack;         // 0x334
            u8* mpHeapBuffer;          // 0x338
            MEMHeapHandle mpExpHeap;   // 0x33C
            AOSSConfig mAoss;          // 0x340
        };

        AOSSThread::AOSSThread(EGG::Heap* heap) : utility::ut_thread() {
            mpExpHeap = NULL;
            sAOSSState = 0;
            mpHeapBuffer = (u8*)heap->alloc(0x40000, 0x20);
            mpStack = (AOSSStack*)heap->alloc(0x1000, 0x20);
        }

        void AOSSThread::destroy(int flag) {
            if (sAOSSState != 0) {
                if (IsThreadTerminated()) {
                    WaitForThreadExit();
                    SOFinish();
                    sAOSSState = 0;
                }
            }
            if (mpExpHeap != NULL) {
                MEMDestroyExpHeap(mpExpHeap);
                mpExpHeap = NULL;
            }
        }

        AOSSThread::~AOSSThread() {
            destroy(1);
        }

        int AOSSThread::start() {
            SOLibraryConfig config;

            if (sAOSSState != 0) {
                return 0;
            }

            config.alloc = aossAlloc;
            config.free = aossFree;

            BOOL level = OSDisableInterrupts();

            OSTime t = OSGetTime();
            sAOSSStartTimeLo = (u32)t;
            sAOSSStartTimeHi = (u32)(t >> 32);

            mpExpHeap = MEMCreateExpHeapEx(mpHeapBuffer, 0x40000, 2);
            MEMInitAllocatorForExpHeap(&m_allocator, mpExpHeap, 0x20);

            mThreadPriority = OSGetThreadPriority(OSGetCurrentThread()) - 2;
            sAOSSState = 1;
            SOInit(&config);
            memset(mpStack, 0, 4);
            Create(mpStack, 0x1000, mThreadPriority, TRUE);

            OSRestoreInterrupts(level);
            return 1;
        }

        void* AOSSThread::aossAlloc(u32 id, s32 size) {
            void* buffer;
            BOOL level = OSDisableInterrupts();
            buffer = MEMAllocFromAllocator(&m_allocator, size);
            OSRestoreInterrupts(level);
            return buffer;
        }

        void AOSSThread::aossFree(u32 id, void* ptr, s32 align) {
            BOOL level = OSDisableInterrupts();
            MEMFreeToAllocator(&m_allocator, ptr);
            OSRestoreInterrupts(level);
        }

        void* AOSSThread::Run() {
            mState = 0xF;
            AOSS_SetCallback(USBAPThread::callback);

            if (AOSSi_InitLocal(aossAlloc, aossFree) == -1) {
                return this;
            }

            memset(&mAoss, 0, sizeof(mAoss));
            mAoss.version = 0xF;
            mAoss.connectionAttemptLimit = 0x32;
            mAoss.requestAttemptLimit = 0x32;
            mAoss.responseWaitCount = 0x64;
            mAoss.requestRetryDelay = 0x64;
            mAoss.socketTimeoutMs = 0x4E20;
            mAoss.interfaceType = 0x50;
            memcpy(mAoss.name, "Wii", 3);
            mAoss.ssidLength = 4;
            NETGetWirelessMacAddress(mAoss.mac);

            mpStack->sentinel = 0x97654321;

            mState = AOSSi_Init(&mAoss);
            AOSSi_EndLocal();
            OSCheckActiveThreads();
            return this;
        }

        int AOSSThread::cancel() {
            if (sAOSSState == 0) {
                return 0;
            }
            BOOL level = OSDisableInterrupts();
            AOSSi_Cancel();
            OSRestoreInterrupts(level);
            return 1;
        }

        int AOSSThread::finish(NCDAossConfig* config, int* result) {
            if (sAOSSState == 0) {
                *result = -0x63;
                return 1;
            }
            if (IsThreadTerminated()) {
                destroy(0);
            }
            else {
                if (((u32)OSGetTime() - sAOSSStartTimeLo)
                        / (OS_TIMER_CLOCK / 1000)
                    >= 90000)
                {
                    BOOL level = OSDisableInterrupts();
                    AOSSi_Cancel();
                    OSRestoreInterrupts(level);
                }
                return 0;
            }

            if (mState == 0) {
                BOOL level = OSDisableInterrupts();
                AOSSResult* sec = &mAoss.security;

                if ((mAoss.version & 0x0001) == 1) {
                    memcpy(config->wep40.ssid, sec->wep40Ssid, 0x20);
                    memcpy(config->wep40.key[0], sec->wep40Key[0], 5);
                    memcpy(config->wep40.key[1], sec->wep40Key[1], 5);
                    memcpy(config->wep40.key[2], sec->wep40Key[2], 5);
                    memcpy(config->wep40.key[3], sec->wep40Key[3], 5);
                    config->wep40.keyId = 1;
                    config->wep40.ssidLength = strlen(sec->wep40Ssid);
                }
                else {
                    memset(config->wep40.ssid, 0, 0x20);
                    config->wep40.ssidLength = 0;
                }

                if ((mAoss.version & 0x0002) == 2) {
                    memcpy(config->wep104.ssid, sec->wep104Ssid, 0x20);
                    memcpy(config->wep104.key[0], sec->wep104Key[0], 0xD);
                    memcpy(config->wep104.key[1], sec->wep104Key[1], 0xD);
                    memcpy(config->wep104.key[2], sec->wep104Key[2], 0xD);
                    memcpy(config->wep104.key[3], sec->wep104Key[3], 0xD);
                    config->wep104.keyId = 1;
                    config->wep104.ssidLength = strlen(sec->wep104Ssid);
                }
                else {
                    memset(config->wep104.ssid, 0, 0x20);
                    config->wep104.ssidLength = 0;
                }

                if ((mAoss.version & 0x0004) == 4) {
                    memcpy(config->tkip.ssid, sec->tkipSsid, 0x20);
                    memcpy(config->tkip.key, sec->tkipKey, 0x40);
                    config->tkip.ssidLength = strlen(sec->tkipSsid);
                    config->tkip.keyLen = strlen(sec->tkipKey);
                }
                else {
                    memset(config->tkip.ssid, 0, 0x20);
                    config->tkip.ssidLength = 0;
                }

                if ((mAoss.version & 0x0008) == 8) {
                    memcpy(config->aes.ssid, sec->aesSsid, 0x20);
                    memcpy(config->aes.key, sec->aesKey, 0x40);
                    config->aes.ssidLength = strlen(sec->aesSsid);
                    config->aes.keyLen = strlen(sec->aesKey);
                }
                else {
                    memset(config->aes.ssid, 0, 0x20);
                    config->aes.ssidLength = 0;
                }

                printInfo();
                OSRestoreInterrupts(level);
            }
            else if (mState == -2) {
                *result = -0x62;
            }

            *result = mAoss.result;
            return 1;
        }

#pragma dont_inline on
        void AOSSThread::printInfo() {
        }
#pragma dont_inline reset

    }  // namespace scene
}  // namespace ipl
