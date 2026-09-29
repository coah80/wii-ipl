#include <revolution/os.h>

#include <cstring>

#include "utility/iplCharacterCode.h"

extern "C" int USBAPStartRegistration(void* arg1, void* arg2, s32 priority,
    void* arg4, void* arg5, void* callback, void* arg7, void* arg8);
extern "C" int USBAPCancelRegistration(void);
extern "C" int USBAPIsThreadTerminated(void);

extern u8* gUSBAPResult;

namespace ipl {
    namespace scene {
        class USBAPThread {
        public:
            USBAPThread();
            void Init(u16* pData, u8* pBuf);
            void cancel();
            void is();
            void setData(const wchar_t* pData, u8* pBuf);
            void callback();

        private:
            wchar_t mData[10];
        };

        USBAPThread::USBAPThread() {
        }

        void USBAPRegisterCallback(int result) {
            if (result == 1) {
                *gUSBAPResult = 1;
                OSReport("Registration completed !\n");
            }
            else {
                *gUSBAPResult = 2;
                OSReport("Registration failed...\n");
            }
        }

        void USBAPThread::Init(u16* pData, u8* pBuf) {
            s32 priority = OSGetThreadPriority(OSGetCurrentThread()) + 1;
            if (USBAPStartRegistration(NULL, NULL, priority, NULL, this,
                    USBAPRegisterCallback, pData, pBuf)
                == 1)
            {
                OSReport("Registration started\n");
            }
        }

        void USBAPThread::cancel() {
            USBAPCancelRegistration();
        }

        void USBAPThread::is() {
            USBAPIsThreadTerminated();
        }

        void USBAPThread::setData(const wchar_t* pData, u8* pBuf) {
            gUSBAPResult = pBuf;
            std::memcpy(mData, pData, sizeof(mData));
            utility::CharacterCode::changeEndian(
                reinterpret_cast<wchar_t*>(mData), 0xA);
        }

        void USBAPThread::callback() {
        }
    }  // namespace scene
}  // namespace ipl
