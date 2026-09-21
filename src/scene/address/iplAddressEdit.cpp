#include "scene/address/iplAddressEdit.h"

#include "system/iplSystem.h"

#include <private/nwc24/NWC24Std.h>
#include <revolution/nwc24.h>

#include <string.h>

typedef s32 ChkHostNameError;

enum {
    CHECK_HOSTNAME_DOT_AT_END = -8,
    CHECK_HOSTNAME_OUT_OF_RANGE,
    CHECK_HOSTNAME_INVALID_CHARACTERS,
    CHECK_HOSTNAME_MULTIPLE_DOTS,
    CHECK_HOSTNAME_INCORRECT,
    CHECK_HOSTNAME_IS_EMPTY,
    CHECK_HOSTNAME_IS_NULL,
    CHECK_HOSTNAME_BAD_LENGTH,
    CHECK_HOSTNAME_SUCCESS
};

static ChkHostNameError CheckHostName(const char* hostName, u32 hostNameLength);

extern "C" char lbl_81647EE0;
extern "C" char smArg__Q23ipl6System;
extern "C" const char* smButtonName__Q33ipl5scene6Button[];
extern "C" void readLayoutAsync__Q33ipl4nand7ManagerFPQ23EGG4HeapPCcb();
extern "C" void List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs();
extern "C" void getScene__Q33ipl5scene7ManagerFi();
extern "C" void setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler();
extern "C" void calc__Q33ipl5scene11TextBalloonFv();
extern "C" void calc__Q33ipl6layout6ObjectFv();
extern "C" void isActive__Q33ipl5scene6ButtonCFv();
extern "C" void update__Q33ipl5scene6ButtonFv();
extern "C" void update__Q33ipl3gui11PaneManagerFv();
extern "C" void del__Q33ipl5scene15FriendListCacheFUl();
extern "C" void reset_friend__Q33ipl5scene7AddressFv();
extern "C" void __div2u();
extern "C" void __mod2u();
extern "C" void UTF16ToANSI__Q33ipl7utility13CharacterCodeFPUcPCwl();
extern "C" void isValidId__Q33ipl5scene15FriendListCacheFRCUx();
extern "C" void isDupId__Q33ipl5scene15FriendListCacheFRCUx();
extern "C" void isDupMail__Q33ipl5scene15FriendListCacheFPCc();
extern "C" u64 utf16_wiiid__Q33ipl5scene11AddressEditFPCw(const wchar_t*);
extern "C" void _savegpr_29();
extern "C" void _restgpr_29();
extern "C" void _savegpr_23();
extern "C" void _savegpr_27();
extern "C" void _restgpr_23();
extern "C" void _restgpr_27();

void ipl::scene::AddressEdit::stt_msg_code_add() {
    if (System::getDialog()->getLastResult() == DialogWindow::RESULT_BUTTON) {
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(this) + 0x64) = 0x22;
    }
}

void ipl::scene::AddressEdit::stt_msg_code_edit() {
    if (System::getDialog()->getLastResult() == DialogWindow::RESULT_BUTTON) {
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(this) + 0x64) = 0;
    }
}

void ipl::scene::AddressEdit::stt_msg_parental() {
    if (System::getDialog()->getLastResult() == DialogWindow::RESULT_BUTTON) {
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(this) + 0x64) = 0;
    }
}

void ipl::scene::AddressEdit::stt_msg_nwc24_error() {
    if (System::getDialog()->getLastResult() == DialogWindow::RESULT_BUTTON) {
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(this) + 0x64) = 0;
    }
}

extern "C" asm void __ct__Q43ipl8keyboard7Manager15KeyboardSettingFQ43ipl8keyboard7Manager12KeyboardTypePCwUlUl() {
    nofralloc
    stw r4, 0(r3)
    stw r5, 4(r3)
    stw r6, 8(r3)
    stw r7, 0xc(r3)
    blr
}

const wchar_t* ipl::scene::AddressEdit::String::getDispCodeLong() const {
    if (reinterpret_cast<const u8*>(this)[0x422] == 0) {
        return;
    }
    return reinterpret_cast<const wchar_t*>(reinterpret_cast<const u8*>(this) + 0x21c);
}

extern "C" asm void getName__Q33ipl6nigaoe6ObjectCFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    lwz r0, 0x3c(r3)
    cmpwi r0, 0
    blt getName_L1
    clrlwi r3, r0, 16
    bl RFLiGetCharData
    addi r3, r3, 2
    b getName_L2
getName_L1:
    li r3, 0
getName_L2:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void getInputForm__Q29textinput7ManagerFv() {
    nofralloc
    lwz r3, 0x1c(r3)
    blr
}

void ipl::scene::AddressEdit::String::clear() {
    memset(this, 0, 0x204);
    memset(reinterpret_cast<u8*>(this) + 0x204, 0, 0x18);
    memset(reinterpret_cast<u8*>(this) + 0x21c, 0, 0x204);
    reinterpret_cast<u8*>(this)[0x420] = 0;
    reinterpret_cast<u8*>(this)[0x421] = 0;
    reinterpret_cast<u8*>(this)[0x422] = 0;
}

extern "C" asm void setWiiNo__Q43ipl5scene11AddressEdit6StringFPCw() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_29
    li r0, 1
    mr r31, r4
    stb r0, 0x422(r3)
    mr r30, r3
    li r4, 0
    li r5, 0x204
    bl memset
    mr r3, r30
    mr r4, r31
    li r5, 0x10
    bl wcsncpy
    addi r3, r30, 0x21c
    li r4, 0
    li r5, 0x204
    bl memset
    li r0, 0x10
    li r7, 0
    li r3, 0
    li r5, 0x3f
    mtctr r0
setWiiNo_L1:
    lhzx r6, r31, r3
    cmplwi r6, 0x30
    blt setWiiNo_L2
    cmplwi r6, 0x39
    bgt setWiiNo_L2
    srawi r0, r7, 2
    addze r0, r0
    add r0, r7, r0
    slwi r0, r0, 1
    add r4, r30, r0
    sth r6, 0x21c(r4)
    b setWiiNo_L3
setWiiNo_L2:
    srawi r0, r7, 2
    addze r0, r0
    add r0, r7, r0
    slwi r0, r0, 1
    add r4, r30, r0
    sth r5, 0x21c(r4)
setWiiNo_L3:
    addi r7, r7, 1
    addi r3, r3, 2
    bdnz setWiiNo_L1
    li r0, 0x20
    mr r3, r31
    sth r0, 0x238(r30)
    li r29, 0
    sth r0, 0x22e(r30)
    sth r0, 0x224(r30)
    bl wcslen
    cmplwi r3, 0x10
    bne setWiiNo_L4
    mr r3, r31
    bl utf16_wiiid__Q33ipl5scene11AddressEditFPCw
    stw r4, 0xc(r1)
    addi r4, r1, 8
    stw r3, 8(r1)
    lwz r3, 0x424(r30)
    lwz r3, 0x4ec(r3)
    bl isValidId__Q33ipl5scene15FriendListCacheFRCUx
    cmpwi r3, 0
    beq setWiiNo_L4
    li r29, 1
setWiiNo_L4:
    stb r29, 0x420(r30)
    addi r11, r1, 0x20
    bl _restgpr_29
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void isDupCode__Q43ipl5scene11AddressEdit6StringCFv() {
    nofralloc
    stwu r1, -0x120(r1)
    mflr r0
    stw r0, 0x124(r1)
    lbz r0, 0x422(r3)
    stw r31, 0x11c(r1)
    mr r31, r3
    cmpwi r0, 0
    beq isDupCode_L1
    bl utf16_wiiid__Q33ipl5scene11AddressEditFPCw
    stw r4, 0xc(r1)
    addi r4, r1, 8
    lwz r5, 0x424(r31)
    stw r3, 8(r1)
    lwz r3, 0x4ec(r5)
    bl isDupId__Q33ipl5scene15FriendListCacheFRCUx
    b isDupCode_L2
isDupCode_L1:
    addi r3, r1, 0x10
    li r4, 0
    li r5, 0x101
    bl memset
    mr r4, r31
    addi r3, r1, 0x10
    li r5, 0x100
    bl UTF16ToANSI__Q33ipl7utility13CharacterCodeFPUcPCwl
    lwz r3, 0x424(r31)
    addi r4, r1, 0x10
    lwz r3, 0x4ec(r3)
    bl isDupMail__Q33ipl5scene15FriendListCacheFPCc
isDupCode_L2:
    lwz r0, 0x124(r1)
    lwz r31, 0x11c(r1)
    mtlr r0
    addi r1, r1, 0x120
    blr
}

extern "C" asm void isMyCode__Q43ipl5scene11AddressEdit6StringCFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    lbz r0, 0x422(r3)
    stw r31, 0xc(r1)
    cmpwi r0, 0
    stw r30, 8(r1)
    beq isMyCode_L1
    lwz r4, 0x424(r3)
    lwz r4, 0x4ec(r4)
    lwz r31, 0x7d68(r4)
    lwz r30, 0x7d6c(r4)
    bl utf16_wiiid__Q33ipl5scene11AddressEditFPCw
    xor r4, r30, r4
    xor r0, r31, r3
    or r0, r4, r0
    cntlzw r0, r0
    srwi r3, r0, 5
    b isMyCode_L2
isMyCode_L1:
    li r3, 0
isMyCode_L2:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void prepare__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r4, smArg__Q23ipl6System@ha
    lis r5, lbl_81647EE0@ha
    stw r0, 0x14(r1)
    addi r4, r4, smArg__Q23ipl6System@l
    addi r5, r5, lbl_81647EE0@l
    li r6, 0
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r3, 0x6c(r4)
    lwz r4, 0x24(r31)
    bl readLayoutAsync__Q33ipl4nand7ManagerFPQ23EGG4HeapPCcb
    stw r3, 0xac(r31)
    lwz r31, 0xc(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void calcFadein__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    li r31, 0
    stw r30, 8(r1)
    mr r30, r3
    lwz r5, 0x68(r3)
    addi r3, r5, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 1
    beq calcFadein_L1
    lwz r3, 0x74(r30)
    li r4, 0
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 1
    beq calcFadein_L1
    li r31, 1
calcFadein_L1:
    mr r3, r31
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void initCalcNormal__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    cmpwi r3, 0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    beq initCalcNormal_L1
    addi r31, r3, 0x58
initCalcNormal_L1:
    lis r3, smArg__Q23ipl6System@ha
    li r4, 5
    addi r3, r3, smArg__Q23ipl6System@l
    lwz r3, 0x64(r3)
    bl getScene__Q33ipl5scene7ManagerFi
    mr r4, r31
    li r5, 0
    bl setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void initCalcFadeout__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r5, smArg__Q23ipl6System@ha
    li r4, 5
    stw r0, 0x14(r1)
    addi r5, r5, smArg__Q23ipl6System@l
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r3, 0x64(r5)
    bl getScene__Q33ipl5scene7ManagerFi
    li r4, 0
    li r5, 0
    bl setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler
    lwz r3, 0xa8(r31)
    bl calc__Q33ipl5scene11TextBalloonFv
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void calcCommonAfter__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r3, 0x70(r3)
    lwz r12, 0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lwz r3, 0x68(r31)
    bl calc__Q33ipl6layout6ObjectFv
    lwz r3, 0x7c(r31)
    lwz r12, 0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lwz r3, 0x74(r31)
    bl calc__Q33ipl6layout6ObjectFv
    lwz r3, 0x80(r31)
    bl calc__Q33ipl6layout6ObjectFv
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_normal__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r5, smArg__Q23ipl6System@ha
    li r4, 5
    stw r0, 0x14(r1)
    addi r5, r5, smArg__Q23ipl6System@l
    stw r31, 0xc(r1)
    stw r30, 8(r1)
    mr r30, r3
    lwz r3, 0x64(r5)
    bl getScene__Q33ipl5scene7ManagerFi
    mr r31, r3
    bl isActive__Q33ipl5scene6ButtonCFv
    cmpwi r3, 0
    beq stt_normal_L1
    mr r3, r31
    bl update__Q33ipl5scene6ButtonFv
stt_normal_L1:
    lwz r0, 0x64(r30)
    cmpwi r0, 0
    bne stt_normal_L2
    lwz r3, 0x70(r30)
    bl update__Q33ipl3gui11PaneManagerFv
stt_normal_L2:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_wait_del_msg_fadein__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0x1c
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r5, 0x68(r3)
    addi r3, r5, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 1
    beq stt_wait_del_msg_fadein_L1
    li r0, 7
    stw r0, 0x64(r31)
stt_wait_del_msg_fadein_L1:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void delete_friendinfo__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    mr r4, r3
    stw r0, 0x14(r1)
    lwz r3, 0x4ec(r3)
    lwz r4, 0xa4(r4)
    bl del__Q33ipl5scene15FriendListCacheFUl
    lis r3, smArg__Q23ipl6System@ha
    li r4, 0x14
    addi r3, r3, smArg__Q23ipl6System@l
    lwz r3, 0x64(r3)
    bl getScene__Q33ipl5scene7ManagerFi
    bl reset_friend__Q33ipl5scene7AddressFv
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" int get_button_no__Q33ipl5scene11AddressEditFPCc(void*, const char* paneName) {
    int result = -1;
    for (int i = 0; i < 5; i++) {
        if (strcmp(smButtonName__Q33ipl5scene6Button[i], paneName) == 0) {
            result = i;
            break;
        }
    }
    return result;
}

extern "C" u64 utf16_wiiid__Q33ipl5scene11AddressEditFPCw(const wchar_t* value) {
    u64 result = 0;
    u64 multiplier = 1;
    for (int i = 0; i < 0x10; i++) {
        result += static_cast<u64>(value[0xf - i] - L'0') * multiplier;
        multiplier *= 10;
    }
    return result;
}

extern "C" asm void wiiid_utf16__Q33ipl5scene11AddressEditFUxPw() {
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    addi r11, r1, 0x30
    bl _savegpr_23
    mr r24, r3
    mr r23, r4
    mr r25, r5
    li r27, 1
    li r28, 0
    li r26, 0
    li r29, 0x30
    li r30, 0
    li r31, 0xa
wiiid_utf16_L1:
    mr r3, r24
    mr r4, r23
    mr r5, r28
    mr r6, r27
    bl __div2u
    li r6, 0xa
    li r5, 0
    bl __mod2u
    addc r5, r4, r29
    adde r3, r3, r30
    subfic r3, r26, 0xf
    addi r26, r26, 1
    slwi r4, r3, 1
    mulhwu r0, r27, r31
    cmpwi r26, 0x10
    sthx r5, r25, r4
    mullw r3, r28, r31
    mulli r27, r27, 0xa
    add r28, r0, r3
    blt wiiid_utf16_L1
    li r0, 0
    addi r11, r1, 0x30
    sth r0, 0x20(r25)
    bl _restgpr_23
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

extern "C" void setName__Q43ipl5scene11AddressEdit6StringFPCw(void* self, const wchar_t* value) {
    wchar_t* name = reinterpret_cast<wchar_t*>(reinterpret_cast<u8*>(self) + 0x204);
    wcsncpy(name, value, 0xa);
    u32 length = wcslen(value);
    reinterpret_cast<u8*>(self)[0x421] = 0;
    for (u32 i = 0; i < length; i++) {
        if (value[i] == 0) {
            break;
        }
        if (value[i] != L' ' && value[i] != 0x3000) {
            reinterpret_cast<u8*>(self)[0x421] = 1;
            break;
        }
    }
}

/*
    This is a modified version of NWC24CheckPublicMailAddr.
    Changes:
     - Uses strnicmp instead of NWC24's Mail_strnicmp
     - ... That's it!!
*/
extern "C" NWC24Err NWC24CheckPublicMailAddr_(const char* addr) {
    int i, j;
    int len;
    BOOL readingDomain;

    static const char specials[] = {'(', ')', '<', '>', '[', ']', ':', ';', '\\', ',', '"'};

    // Check parameters
    if (addr == NULL) {
        return NWC24_ERR_NULL;
    }

    // Check address length
    len = STD_strnlen(addr, sizeof(NWC24UserMailAddr));
    if (len == (int)sizeof(NWC24UserMailAddr)) {
        return NWC24_ERR_STRING_END;
    }
    if (len == 0) {
        return NWC24_ERR_FORMAT;
    }

    readingDomain = FALSE;

    for (i = 0; i < len; i++) {
        char ch = addr[i];

        // If we found '@'
        if (ch == '@') {
            // If it was at the beginning of the address, invalid!
            if (i == 0) {
                return NWC24_ERR_FORMAT;
            }
            readingDomain = TRUE;
            break;
        }

        // If the character is not a letter or symbol, invalid!
        if (ch <= ' ' || ch >= '~' + 1) {
            return NWC24_ERR_FORMAT;
        }

        // If the character is special, invalid!
        for (j = 0; j < sizeof(specials); j++) {
            if (ch == specials[j]) {
                return NWC24_ERR_FORMAT;
            }
        }
    }

    // If we are have not found '@', invalid!
    if (!readingDomain) {
        return NWC24_ERR_FORMAT;
    }

    // If the hostname is not valid, invalid!
    if (CheckHostName(&addr[i + 1], (len - i)) < CHECK_HOSTNAME_SUCCESS) {
        return NWC24_ERR_FORMAT;
    }

    return strnicmp(&addr[i], NWC24GetAccountDomain(), (len - i) + 1) == 0 ? NWC24_ERR_PROTECTED : NWC24_OK;
}

static ChkHostNameError CheckHostName(const char* hostName, u32 hostNameLength) {
    int i;
    BOOL foundDot;

    // Parameter check
    if (hostNameLength == 0) {
        return CHECK_HOSTNAME_BAD_LENGTH;
    }

    // Is null or empty check
    if (hostName == NULL) {
        return CHECK_HOSTNAME_IS_NULL;
    }
    if (*hostName == 0) {
        return CHECK_HOSTNAME_IS_EMPTY;
    }

    // Verify check
    if (*hostName == '.') {
        return CHECK_HOSTNAME_INCORRECT;
    }

    foundDot = FALSE;

    for (i = 0; i < hostNameLength; i++) {
        char ch = hostName[i];

        // Stop on NULL
        if (ch == 0) {
            break;
        }

        if (ch == '.') {
            // Check if we already found one again after the previous character.
            if (foundDot) {
                return CHECK_HOSTNAME_MULTIPLE_DOTS;
            }
            foundDot = TRUE;
            continue;
        }

        // Check if there are invalid characters
        if ((ch < '0' || ch > '9') && (ch < 'a' || ch > 'z') && (ch < 'A' || ch > 'Z') && (ch != '-' && ch != '_')) {
            return CHECK_HOSTNAME_INVALID_CHARACTERS;
        }

        foundDot = FALSE;
    }

    // Check if we are out of range
    if (i == hostNameLength) {
        return CHECK_HOSTNAME_OUT_OF_RANGE;
    }

    // Check if the end of hostname has a dot
    if (i > 0 && hostName[i - 1] == '.') {
        return CHECK_HOSTNAME_DOT_AT_END;
    }

    return CHECK_HOSTNAME_SUCCESS;
}
