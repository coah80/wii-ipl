#include <revolution/os.h>
#include <string.h>
#include "utility/iplCharacterCode.h"

extern "C" {
BOOL USBAPStartRegistration(void*, void*, u32, u32, void*, void (*)(int), u16*, u8*);
BOOL USBAPCancelRegistration();
BOOL USBAPIsThreadTerminated();
void _savegpr_29();
void _restgpr_29();
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

extern "C" u8* lbl_81698C20;

#pragma push
#pragma section const_type ".data"
extern "C" const char lbl_81657B18[] = "Registration completed !\n";
extern "C" const char lbl_81657B32[] = "Registration failed...\n";
extern "C" const char lbl_81657B4A[] = "Registration started\n";
#pragma pop

USBAPThread::USBAPThread() {
}

extern "C" void USBAPRegisterCallback__Q23ipl5sceneFi(int result) {
    if (result == 1) {
        *lbl_81698C20 = 1;
        OSReport(lbl_81657B18);
    } else {
        *lbl_81698C20 = 2;
        OSReport(lbl_81657B32);
    }
}

asm void USBAPThread::Init(unsigned short* buffer, unsigned char* accessPoints) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_29
    mr r29, r3
    mr r30, r4
    mr r31, r5
    bl OSGetCurrentThread
    bl OSGetThreadPriority
    lis r8, USBAPRegisterCallback__Q23ipl5sceneFi@ha
    addi r5, r3, 1
    mr r7, r29
    mr r9, r30
    mr r10, r31
    addi r8, r8, USBAPRegisterCallback__Q23ipl5sceneFi@l
    li r4, 0
    li r3, 0
    li r6, 0
    bl USBAPStartRegistration
    cmpwi r3, 1
    bne lbl_init_done
    lis r3, lbl_81657B4A@ha
    addi r3, r3, lbl_81657B4A@l
    crclr 4*cr1+eq
    bl OSReport
lbl_init_done:
    addi r11, r1, 0x20
    bl _restgpr_29
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

BOOL USBAPThread::cancel() {
    return USBAPCancelRegistration();
}

BOOL USBAPThread::is() {
    return USBAPIsThreadTerminated();
}

void USBAPThread::setData(const wchar_t* nickname, unsigned char* result) {
    lbl_81698C20 = result;
    memcpy(mNickname, nickname, 20);
    utility::CharacterCode::changeEndian(mNickname, 10);
}

void USBAPThread::callback() {
}

}
}
