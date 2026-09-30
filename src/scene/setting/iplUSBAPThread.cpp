#include <revolution/os.h>
#include <string.h>
#include "utility/iplCharacterCode.h"

extern "C" {
BOOL USBAPStartRegistration(void*, void*, u32, u32, void*, void (*)(int), u16*, u8*);
BOOL USBAPCancelRegistration();
BOOL USBAPIsThreadTerminated();
}

namespace ipl {
namespace scene {

class USBAPThread {
public:
    USBAPThread();
    void Init(unsigned short* buffer, unsigned char* accessPoints);
    BOOL cancel();
    BOOL is();
    void setData(const wchar_t* nickname, unsigned char* result);
    void callback();
private:
    wchar_t mNickname[10];
};

static u8* registrationResult;

USBAPThread::USBAPThread() {
}

void USBAPRegisterCallback(int result) {
    if (result == 1) {
        *registrationResult = 1;
        OSReport("Registration completed !\n");
    } else {
        *registrationResult = 2;
        OSReport("Registration failed...\n");
    }
}

void USBAPThread::Init(unsigned short* buffer, unsigned char* accessPoints) {
    int priority = OSGetThreadPriority(OSGetCurrentThread()) + 1;
    if (USBAPStartRegistration(NULL, NULL, priority,
                              0, this, USBAPRegisterCallback, buffer, accessPoints) == 1) {
        OSReport("Registration started\n");
    }
}

BOOL USBAPThread::cancel() {
    return USBAPCancelRegistration();
}

BOOL USBAPThread::is() {
    return USBAPIsThreadTerminated();
}

void USBAPThread::setData(const wchar_t* nickname, unsigned char* result) {
    registrationResult = result;
    memcpy(mNickname, nickname, 20);
    utility::CharacterCode::changeEndian(mNickname, 10);
}

void USBAPThread::callback() {
}

}
}
