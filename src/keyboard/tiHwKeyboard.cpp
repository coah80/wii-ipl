#include "keyboard/tiHwKeyboard.h"

#include "keyboard/tiManager.h"
#include "keyboard/tiHKBManager.h"
#include "keyboard/tiLayoutGather.h"

extern "C" const u8 scHwScrlKeyMap[];
extern "C" const u8 csAninationFile[];
struct HWKeyboardScrlData {
    u32 field_0x00;
    u32 field_0x04;
    const u8* field_0x08;
    u32 field_0x0c;
    const u8* field_0x10;
    u32 field_0x14[11];
};
extern const HWKeyboardScrlData scHwScrlData = {
    0, 0, scHwScrlKeyMap, 1, csAninationFile + 0x154, {0},
};
extern const u32 scHwSendPacket[4] = {0, 0, 0x01000000, 0};
extern const u8 scHwInitSeq0[] = {0x0f, 0x21, 0x20, 0x08, 0x09, 0x0e, 0x19, 0x00, 0x21, 0x21, 0x00, 0x00};
extern const u8 scHwInitSeq1[] = {0x0f, 0x21, 0x20, 0x04, 0x09, 0x0e, 0x11, 0x00, 0x21, 0x21, 0x00, 0x00};
const u8 scKeyMap[136] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x01, 0x0a, 0x03, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26,
    0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x19, 0x1a, 0x1b, 0x13, 0x15, 0x17, 0x14, 0x16, 0x18, 0x00,
    0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x0f, 0x0e, 0x00, 0x00, 0x00, 0x00,
    0x11, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x06, 0x05, 0x07, 0x0b, 0x06, 0x05, 0x07, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
extern const u32 scKeyRepeatData[2];
extern const u32 scTriggerData[1];

#pragma push
#pragma section data_type ".sdata" ".sdata"
u8 sbShiftInit = 0;
u8 sbShiftOn = 1;
u8 sbShiftOff = 0;
#pragma pop
extern "C" void SetCountry__Q39textinput5input10HKBManagerFUc();
extern "C" textinput::input::HKBManager sInstance__Q39textinput5input10HKBManager;
extern "C" void convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw();
extern "C" bool updateInput__Q49textinput8keyboard5hwkey10HWKeyboardFRQ39textinput5input10HKBManager();
extern "C" void __dt__Q49textinput8keyboard5hwkey10HWKeyboardFv();
extern "C" void create__Q29textinput4BaseFP12MEMAllocator();
extern "C" void init__Q49textinput8keyboard5hwkey10HWKeyboardFv();
extern "C" void setCommandReceiver__Q29textinput13CommandSenderFPQ29textinput15CommandReceiver();
extern "C" void sendCommand__Q29textinput13CommandSenderFUlPv();
extern "C" void updateFromReceiver__Q29textinput13CommandSenderFUlPv();

#pragma push
#pragma section const_type ".data"
typedef void (*KeyboardDataFunction)();
extern "C" KeyboardDataFunction const scHwKeyFuncTable[0x3f] = {
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x00000158),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001d8),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001c0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x00000170),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x0000017c),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x00000134),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001a0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x00000140),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x00000188),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x00000194),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x00000148),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x00000150),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x00000164),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001b8),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001f0),
    reinterpret_cast<KeyboardDataFunction>(reinterpret_cast<u32>(convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw) + 0x000001ac)
};
extern "C" KeyboardDataFunction const __vt__Q49textinput8keyboard5hwkey10HWKeyboard[9] = {
    NULL,
    NULL,
    __dt__Q49textinput8keyboard5hwkey10HWKeyboardFv,
    create__Q29textinput4BaseFP12MEMAllocator,
    init__Q49textinput8keyboard5hwkey10HWKeyboardFv,
    setCommandReceiver__Q29textinput13CommandSenderFPQ29textinput15CommandReceiver,
    sendCommand__Q29textinput13CommandSenderFUlPv,
    updateFromReceiver__Q29textinput13CommandSenderFUlPv,
    reinterpret_cast<KeyboardDataFunction>(updateInput__Q49textinput8keyboard5hwkey10HWKeyboardFRQ39textinput5input10HKBManager)
};
#pragma pop

namespace textinput {

    namespace keyboard {

        namespace hwkey {

            struct Packet {
                u16 code;
                u16 unk_02;
                u32 flags;
                u32 unk_08;
                u32 unk_0C;
            };

            extern "C" void GetTriggeredKeySet__Q39textinput5input10HKBManagerCFv();
            extern "C" void IsValid__Q49textinput5input10HKBManager6KeySetCFv();
            extern "C" void GetKey__Q49textinput5input10HKBManager6KeySetCFv();
            extern "C" void GetNext__Q49textinput5input10HKBManager6KeySetCFv();
            extern "C" void GetModifierState__Q39textinput5input10HKBManagerCFv();
            bool HWKeyboard::updateRepeatKey_(input::HKBManager& hkbManager) {
                s32 mods = hkbManager.GetModifierState();
                input::HKBManager::KeySet keySet(NULL, 0);
                keySet = hkbManager.GetRepeatedKeySet();
                if (!keySet.IsValid()) {
                    return false;
                }
                if (!mgr()->getToolBar()->isQwerty() && mgr()->getToolBar()->isEnableKeytopChange()) {
                    return true;
                }
                u32 shift = mods & 0x8;
                while (keySet.IsValid()) {
                    u8 key = keySet.GetKey();
                    u32 v;
                    switch (key) {
                        case 0x4C:
                            sendCommand(2, NULL);
                            break;
                        case 0x2A:
                            sendCommand(1, NULL);
                            break;
                        case 0x4F: v = 0x20; goto send_arrow;
                        case 0x50: v = 0x1F; goto send_arrow;
                        case 0x51: v = 0x1E; goto send_arrow;
                        case 0x52: v = 0x1D;
send_arrow: {
                            u32 data[2] = {v, mods};
                            sendCommand(0x26, data);
                            break;
                        }
                        case 0x2C:
                            if ((mgr()->getToolBar()->isQwerty() != 0 ||
                                 mgr()->getCellPhoneKeyboard()->isNumeric() == 0) && shift == 0) {
                                u32 data[2] = {const_cast<u32*>(scKeyRepeatData)[0], mods};
                                sendCommand(0x26, data);
                            }
                            break;
                    }
                    keySet = keySet.GetNext();
                }
                return false;
            }

            bool HWKeyboard::updateTriggerKey_(input::HKBManager& hkbManager) {
                s32 mods = hkbManager.GetModifierState();
                input::HKBManager::KeySet keySet(NULL, 0);
                keySet = hkbManager.GetTriggeredKeySet();
                if (!keySet.IsValid()) {
                    return false;
                }
                if (mgr()->getToolBar()->isQwerty() == 0 &&
                    mgr()->getToolBar()->isEnableKeytopChange() != 0) {
                    return true;
                }
                if (mgr()->getPCKeyboard()->isABC() == 0) {
                    if (mgr()->getToolBar()->isQwerty() != 0 && mgr()->getEventObserver() != 0) {
                        mgr()->getEventObserver()->onSE((sound::SE)0xD);
                    }
                    mgr()->getPCKeyboard()->setABC(true);
                }
                while (keySet.IsValid()) {
                    wchar_t wc = keySet.GetWChar();
                    u8 key = keySet.GetKey();
                    const u8* keyMap = scKeyMap;
                    if (wc == 0x20) {
                        if (!(mods & 0x8)) {
                            goto check_caps;
                        }
                        u32 data[2] = {const_cast<u32*>(scTriggerData)[0], mods};
                        sendCommand(0x26, data);
                    }
                    else if (wc != 0) {
                        bool send = true;
                        if (mgr()->getToolBar()->isQwerty() == 0 &&
                            mgr()->getCellPhoneKeyboard()->isNumeric() != 0) {
                            if ((int)wc == 0x2F) {
                                goto bad_wc;
                            }
                            else if ((int)wc < 0x2F) {
                                if ((int)wc >= 0x2E) {
                                    goto dot_wc;
                                }
                                goto bad_wc;
                            }
                            else {
                                if ((int)wc >= 0x3A) {
                                    goto bad_wc;
                                }
                                goto ok_wc;
                            }
dot_wc:
                            if (mgr()->getCellPhoneKeyboard()->isNumericWithDot() != 0) {
                                goto ok_wc;
                            }
bad_wc:
                            send = false;
ok_wc:;
                        }
                        if (send) {
                            mods = 0;
                            if (hkbManager.GetModifierState() & 0x2) {
                                mods |= 1;
                            }
                            if (hkbManager.GetModifierState() & 0x200) {
                                mods |= 2;
                            }
                            if (!(mods & 1)) {
                                pctype::LayoutByNW4R* pcKbd = mgr()->getPCKeyboard();
                                pcKbd->mKeyState.setABCFlag(pcKbd->mKeyState.mFlags & ~0x8F);
                            }
                            wc = convertWCCode(wc);
                            Packet packet = *(const Packet*)scHwSendPacket;
                            packet.code = wc;
                            packet.flags = mods;
                            sendCommand(0, &packet);
                            if (mgr()->getLanguage() == 8) {
                                u32 shifted = wc + 0x10000;
                                if ((u16)(shifted - 0x201C) <= 1) {
                                    field_0x16 = !field_0x16;
                                }
                                else if ((u16)(shifted - 0x2018) <= 1) {
                                    field_0x15 = !field_0x15;
                                }
                            }
                        }
                    }
                    else {
                        bool send = true;
                        int code;
                        if (key < 0x20) {
                            code = 0;
                        }
                        else if (key < 0x98) {
                            code = keyMap[key - 0x20];
                        }
                        else if (key < 0xE0) {
                            code = 0;
                        }
                        else if (key < 0xF0) {
                            code = keyMap[key - 0x68];
                        }
                        else {
                            code = 0;
                        }
                        if (code == 0x1C) {
                            u32 m = !(hkbManager.GetModifierState() & 0x100);
                            if (mgr()->getToolBar()->isQwerty() == 0 &&
                                mgr()->getCellPhoneKeyboard()->isNumeric() != 0) {
                                m = 1;
                            }
                            hkbManager.SetModifierState(m ? 0x100 : 0, 0x100);
                        }
                        if (mgr()->getToolBar()->isQwerty() == 0 &&
                            mgr()->getCellPhoneKeyboard()->isNumeric() != 0) {
                            if (code < 0x1D) {
                                if (code >= 0x17 || code < 0x15) {
                                    goto bad_code;
                                }
                            }
                            else {
                                if (code >= 0x21) {
                                    goto bad_code;
                                }
                                goto ok_code;
bad_code:
                                send = false;
                            }
ok_code:;
                        }
                        if (send) {
                            u32 data[2] = {code, mods};
                            sendCommand(0x26, data);
                        }
                    }
check_caps:
                    switch ((int)keySet.GetKey()) {
                        case 0x39:
                            if (mgr()->getToolBar()->isQwerty() != 0 ||
                                mgr()->getToolBar()->isEnableKeytopChange() != 0) {
                                mgr()->getPCKeyboard()->onPressedCaps();
                            }
                            break;
                    }
                    keySet = keySet.GetNext();
                }
                return false;
            }

            bool HWKeyboard::updateTappingShift_(input::HKBManager& hkbManager) {
                hkbManager.GetModifierState();
                input::HKBManager::KeySet keySet(NULL, 0);
                keySet = hkbManager.GetTriggeredKeySet();
                while (keySet.IsValid()) {
                    switch (keySet.GetKey()) {
                        case 0xE1:
                        case 0xE5:
                            field_0x14 = 1;
                            return false;
                        default:
                            field_0x14 = 0;
                            keySet = keySet.GetNext();
                            break;
                    }
                }
                if (field_0x14 == 0) {
                    return false;
                }
                keySet = hkbManager.GetReleasedKeySet();
                while (keySet.IsValid()) {
                    switch (keySet.GetKey()) {
                        case 0xE1:
                        case 0xE5:
                            field_0x14 = 0;
                            if (mgr()->getToolBar()->isQwerty() != 0 &&
                                mgr()->getPCKeyboard()->mbLangKeyActive != 0) {
                                sendCommand(0x2E, NULL);
                            }
                            return false;
                        default:
                            keySet = keySet.GetNext();
                            break;
                    }
                }
                return false;
            }
            extern "C" bool updateRepeatKey___Q49textinput8keyboard5hwkey10HWKeyboardFRQ39textinput5input10HKBManager();
            extern "C" bool updateTriggerKey___Q49textinput8keyboard5hwkey10HWKeyboardFRQ39textinput5input10HKBManager();
            extern "C" bool updateTappingShift___Q49textinput8keyboard5hwkey10HWKeyboardFRQ39textinput5input10HKBManager();
            extern "C" void updateShift__Q49textinput8keyboard5hwkey10HWKeyboardFRQ39textinput5input10HKBManager();
            extern "C" asm bool updateInput__Q49textinput8keyboard5hwkey10HWKeyboardFRQ39textinput5input10HKBManager() {
                nofralloc
                stwu r1, -0x40(r1)
                mflr r0
                stw r0, 0x44(r1)
                stw r31, 0x3c(r1)
                mr r31, r4
                stw r30, 0x38(r1)
                mr r30, r3
                lwz r3, 0x10(r3)
                lwz r12, 0(r3)
                lwz r12, 0x84(r12)
                mtctr r12
                bctrl
                lwz r12, 0(r3)
                lwz r12, 0xdc(r12)
                mtctr r12
                bctrl
                cmpwi r3, 0
                bne updateInput_HWKeyboard_L1
                mr r3, r31
                bl GetModifierState__Q39textinput5input10HKBManagerCFv
                rlwinm. r0, r3, 0, 0x1d, 0x1d
                bne updateInput_HWKeyboard_L2
                li r0, 0
                b updateInput_HWKeyboard_L3
            updateInput_HWKeyboard_L2:
                li r5, 0
                li r0, -1
                stw r5, 8(r1)
                mr r4, r31
                addi r3, r1, 0x14
                stb r5, 0xc(r1)
                stb r0, 0xd(r1)
                stb r5, 0xe(r1)
                sth r5, 0x10(r1)
                bl GetTriggeredKeySet__Q39textinput5input10HKBManagerCFv
                lwz r6, 0x14(r1)
                lbz r5, 0x18(r1)
                lbz r4, 0x19(r1)
                lbz r3, 0x1a(r1)
                lhz r0, 0x1c(r1)
                stw r6, 8(r1)
                stb r5, 0xc(r1)
                stb r4, 0xd(r1)
                stb r3, 0xe(r1)
                sth r0, 0x10(r1)
                b updateInput_HWKeyboard_L4
            updateInput_HWKeyboard_L5:
                addi r3, r1, 8
                bl GetKey__Q49textinput5input10HKBManager6KeySetCFv
                clrlwi r0, r3, 0x18
                cmpwi r0, 0x2b
                bge updateInput_HWKeyboard_L6
                cmpwi r0, 0x28
                beq updateInput_HWKeyboard_L7
                bge updateInput_HWKeyboard_L8
                b updateInput_HWKeyboard_L9
            updateInput_HWKeyboard_L6:
                cmpwi r0, 0x58
                beq updateInput_HWKeyboard_L7
                b updateInput_HWKeyboard_L9
            updateInput_HWKeyboard_L7:
                lwz r3, 0x10(r30)
                lwz r12, 0(r3)
                lwz r12, 0x94(r12)
                mtctr r12
                bctrl
                lwz r12, 0(r3)
                lwz r12, 0xa0(r12)
                mtctr r12
                bctrl
                li r0, 1
                b updateInput_HWKeyboard_L3
            updateInput_HWKeyboard_L8:
                lwz r3, 0x10(r30)
                lwz r12, 0(r3)
                lwz r12, 0x94(r12)
                mtctr r12
                bctrl
                lwz r12, 0(r3)
                lwz r12, 0xa4(r12)
                mtctr r12
                bctrl
                li r0, 1
                b updateInput_HWKeyboard_L3
            updateInput_HWKeyboard_L9:
                addi r3, r1, 0x20
                addi r4, r1, 8
                bl GetNext__Q49textinput5input10HKBManager6KeySetCFv
                lwz r6, 0x20(r1)
                lbz r5, 0x24(r1)
                lbz r4, 0x25(r1)
                lbz r3, 0x26(r1)
                lhz r0, 0x28(r1)
                stw r6, 8(r1)
                stb r5, 0xc(r1)
                stb r4, 0xd(r1)
                stb r3, 0xe(r1)
                sth r0, 0x10(r1)
            updateInput_HWKeyboard_L4:
                addi r3, r1, 8
                bl IsValid__Q49textinput5input10HKBManager6KeySetCFv
                cmpwi r3, 0
                bne updateInput_HWKeyboard_L5
                li r0, 0
            updateInput_HWKeyboard_L3:
                cmpwi r0, 0
                bne updateInput_HWKeyboard_L1
                mr r3, r30
                mr r4, r31
                bl updateRepeatKey___Q49textinput8keyboard5hwkey10HWKeyboardFRQ39textinput5input10HKBManager
                cmpwi r3, 0
                bne updateInput_HWKeyboard_L1
                mr r3, r30
                mr r4, r31
                bl updateTriggerKey___Q49textinput8keyboard5hwkey10HWKeyboardFRQ39textinput5input10HKBManager
                cmpwi r3, 0
                bne updateInput_HWKeyboard_L1
                mr r3, r30
                mr r4, r31
                bl updateTappingShift___Q49textinput8keyboard5hwkey10HWKeyboardFRQ39textinput5input10HKBManager
            updateInput_HWKeyboard_L1:
                mr r3, r30
                mr r4, r31
                bl updateShift__Q49textinput8keyboard5hwkey10HWKeyboardFRQ39textinput5input10HKBManager
                lwz r31, 0x3c(r1)
                li r3, 0
                lwz r30, 0x38(r1)
                lwz r0, 0x44(r1)
                mtlr r0
                addi r1, r1, 0x40
                blr
            }

            HWKeyboard::HWKeyboard(Manager* manager) : mpManager(manager), field_0x14(0), field_0x15(0), field_0x16(0) {
            }

            void HWKeyboard::init() {
                LayoutGather::Singleton::getInstance().setHWPressedShift(sbShiftInit);

                u32 state = input::HKBManager::getInstance().GetModifierState();
                input::HKBManager::getInstance().SetModifierState(state | 0x100, 0x700);
                field_0x15 = 0;
                field_0x16 = 0;
            }

            void HWKeyboard::updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release, void* data) {
                if (trig != 0) {
                    field_0x14 = 0;
                }
            }

            void HWKeyboard::updateShift(input::HKBManager& hkbManager) {
                LayoutGather &gather = LayoutGather::Singleton::getInstance();

                u32 state = hkbManager.GetModifierState();

                if (!mgr()->getToolBar()->isQwerty() && !mgr()->getToolBar()->isEnableKeytopChange()) {
                    return;
                }

                bool previousShift = gather.isHoldingShift();

                if (state & 0x2) {
                    gather.setHWPressedShift(sbShiftOn);
                    if (!previousShift) {
                        mgr()->getPCKeyboard()->onPressedShift(true);
                    }
                } else {
                    gather.setHWPressedShift(sbShiftOff);
                    if (previousShift) {
                        if (!gather.isHoldingShift()) {
                            mgr()->getPCKeyboard()->onReleasedShift();
                        }
                    }
                }
            }

            extern "C" asm void setLanguage__Q49textinput8keyboard5hwkey10HWKeyboardFQ29textinput11DestinationQ29textinput8Language() {
                nofralloc
                cmpwi r4, 2
                bne setLanguage_L1
                lis r4, scHwInitSeq0@ha
                lis r3, sInstance__Q39textinput5input10HKBManager@ha
                addi r4, r4, scHwInitSeq0@l
                lbzx r4, r4, r5
                addi r3, r3, sInstance__Q39textinput5input10HKBManager@l
                b SetCountry__Q39textinput5input10HKBManagerFUc
            setLanguage_L1:
                lis r4, scHwInitSeq1@ha
                lis r3, sInstance__Q39textinput5input10HKBManager@ha
                addi r4, r4, scHwInitSeq1@l
                lbzx r4, r4, r5
                addi r3, r3, sInstance__Q39textinput5input10HKBManager@l
                b SetCountry__Q39textinput5input10HKBManagerFUc
            }

            extern "C" asm void convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw() {
                nofralloc
                stwu r1, -0x10(r1)
                mflr r0
                stw r0, 0x14(r1)
                stw r31, 0xc(r1)
                mr r31, r4
                stw r30, 8(r1)
                mr r30, r3
                lwz r3, 0x10(r3)
                lwz r12, 0(r3)
                lwz r12, 0x98(r12)
                mtctr r12
                bctrl
                lwz r12, 0(r3)
                lwz r12, 0x10(r12)
                mtctr r12
                bctrl
                cmpwi r3, 0
                beq convertWCCode_HWKeyboard_L1
                lwz r3, 0x10(r30)
                lwz r12, 0(r3)
                lwz r12, 0x78(r12)
                mtctr r12
                bctrl
                lwz r12, 0(r3)
                lwz r12, 0x58(r12)
                mtctr r12
                bctrl
                cmpwi r3, 0
                beq convertWCCode_HWKeyboard_L1
                lwz r3, 0x10(r30)
                lwz r12, 0(r3)
                lwz r12, 0x34(r12)
                mtctr r12
                bctrl
                cmpwi r3, 0
                bne convertWCCode_HWKeyboard_L2
                cmpwi r31, 0x5b
                beq convertWCCode_HWKeyboard_L3
                bge convertWCCode_HWKeyboard_L4
                cmpwi r31, 0x2d
                beq convertWCCode_HWKeyboard_L5
                bge convertWCCode_HWKeyboard_L6
                cmpwi r31, 0x2c
                bge convertWCCode_HWKeyboard_L7
                b convertWCCode_HWKeyboard_L1
            convertWCCode_HWKeyboard_L6:
                cmpwi r31, 0x2f
                bge convertWCCode_HWKeyboard_L1
                b convertWCCode_HWKeyboard_L8
            convertWCCode_HWKeyboard_L4:
                cmpwi r31, 0x5d
                beq convertWCCode_HWKeyboard_L9
                b convertWCCode_HWKeyboard_L1
            convertWCCode_HWKeyboard_L7:
                li r3, 0x3001
                b convertWCCode_HWKeyboard_L10
            convertWCCode_HWKeyboard_L8:
                li r3, 0x3002
                b convertWCCode_HWKeyboard_L10
            convertWCCode_HWKeyboard_L5:
                li r3, 0x30fc
                b convertWCCode_HWKeyboard_L10
            convertWCCode_HWKeyboard_L3:
                li r3, 0x300c
                b convertWCCode_HWKeyboard_L10
            convertWCCode_HWKeyboard_L9:
                li r3, 0x300d
                b convertWCCode_HWKeyboard_L10
            convertWCCode_HWKeyboard_L2:
                lwz r3, 0x10(r30)
                lwz r12, 0(r3)
                lwz r12, 0x34(r12)
                mtctr r12
                bctrl
                cmpwi r3, 8
                bne convertWCCode_HWKeyboard_L1
                addi r0, r31, -0x21
                cmplwi r0, 0x3e
                bgt convertWCCode_HWKeyboard_L1
                lis r3, scHwKeyFuncTable@ha
                slwi r0, r0, 2
                addi r3, r3, scHwKeyFuncTable@l
                lwzx r3, r3, r0
                mtctr r3
                bctr
            convertWCCode_HWKeyboard_L11:
                lis r3, 1
                addi r3, r3, -0xf4
                b convertWCCode_HWKeyboard_L10
            convertWCCode_HWKeyboard_L12:
                li r3, 0x3002
                b convertWCCode_HWKeyboard_L10
            convertWCCode_HWKeyboard_L13:
                li r3, 0x300a
                b convertWCCode_HWKeyboard_L10
            convertWCCode_HWKeyboard_L14:
                li r3, 0x300b
                b convertWCCode_HWKeyboard_L10
            convertWCCode_HWKeyboard_L15:
                lis r3, 1
                addi r3, r3, -0xff
                b convertWCCode_HWKeyboard_L10
            convertWCCode_HWKeyboard_L16:
                lis r3, 1
                addi r3, r3, -0xe1
                b convertWCCode_HWKeyboard_L10
            convertWCCode_HWKeyboard_L17:
                lis r3, 1
                addi r3, r3, -0xf8
                b convertWCCode_HWKeyboard_L10
            convertWCCode_HWKeyboard_L18:
                lis r3, 1
                addi r3, r3, -0xf7
                b convertWCCode_HWKeyboard_L10
            convertWCCode_HWKeyboard_L19:
                lis r3, 1
                addi r3, r3, -0xe6
                b convertWCCode_HWKeyboard_L10
            convertWCCode_HWKeyboard_L20:
                lis r3, 1
                addi r3, r3, -0xe5
                b convertWCCode_HWKeyboard_L10
            convertWCCode_HWKeyboard_L21:
                lis r3, 1
                addi r3, r3, -0xf3
                b convertWCCode_HWKeyboard_L10
            convertWCCode_HWKeyboard_L22:
                lis r3, 1
                addi r3, r3, -0xc1
                b convertWCCode_HWKeyboard_L10
            convertWCCode_HWKeyboard_L23:
                li r3, 0x3001
                b convertWCCode_HWKeyboard_L10
            convertWCCode_HWKeyboard_L24:
                lbz r3, 0x15(r30)
                neg r0, r3
                or r0, r0, r3
                srwi r3, r0, 0x1f
                addi r3, r3, 0x2018
                b convertWCCode_HWKeyboard_L10
            convertWCCode_HWKeyboard_L25:
                lbz r3, 0x16(r30)
                neg r0, r3
                or r0, r0, r3
                srwi r3, r0, 0x1f
                addi r3, r3, 0x201c
                b convertWCCode_HWKeyboard_L10
            convertWCCode_HWKeyboard_L1:
                mr r3, r31
            convertWCCode_HWKeyboard_L10:
                lwz r0, 0x14(r1)
                lwz r31, 0xc(r1)
                lwz r30, 8(r1)
                mtlr r0
                addi r1, r1, 0x10
                blr
            }
        }  // namespace hwkey

    }  // namespace keyboard

}  // namespace textinput

const u32 scKeyRepeatData[2] = {8, 0};
const u32 scTriggerData[1] = {8};
