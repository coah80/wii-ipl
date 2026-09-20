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

void ipl::scene::AddressEdit::String::clear() {
    memset(this, 0, 0x204);
    memset(reinterpret_cast<u8*>(this) + 0x204, 0, 0x18);
    memset(reinterpret_cast<u8*>(this) + 0x21c, 0, 0x204);
    reinterpret_cast<u8*>(this)[0x420] = 0;
    reinterpret_cast<u8*>(this)[0x421] = 0;
    reinterpret_cast<u8*>(this)[0x422] = 0;
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
