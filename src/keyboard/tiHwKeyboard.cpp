#define TIHWKEYBOARD_IMPLEMENTATION
#include "keyboard/tiHwKeyboard.h"

#include "keyboard/tiManager.h"
#include "keyboard/tiHKBManager.h"
#include "keyboard/tiLayoutGather.h"



namespace textinput {

    namespace keyboard {

        namespace hwkey {
            HWKeyboard::HWKeyboard(Manager* manager) : mpManager(manager), mbShiftTapPending(0), mbSingleQuoteClosing(0), mbDoubleQuoteClosing(0) {
            }

struct NavigationCommand { u32 command; u32 modifiers; };
struct KeyInputData {
    wchar_t character;
    u16 flags;
    u32 modifier;
    u8 direct;
    u8 repeated;
    u16 reserved;
    u32 data;
};
extern const u8 controlKeys[];
            void HWKeyboard::init() {
                LayoutGather::Singleton::getInstance().setHWPressedShift(false);

                u32 state = input::HKBManager::getInstance().GetModifierState();
                input::HKBManager::getInstance().SetModifierState(state | 0x100, 0x700);
                mbSingleQuoteClosing = 0;
                mbDoubleQuoteClosing = 0;
            }

            void HWKeyboard::updateShift(input::HKBManager& hkbManager) {
                LayoutGather &gather = LayoutGather::Singleton::getInstance();

                u32 state = hkbManager.GetModifierState();

                if (!mgr()->getToolBar()->isQwerty() && !mgr()->getToolBar()->isEnableKeytopChange()) {
                    return;
                }

                bool previousShift = gather.isHoldingShift();

                if (state & 0x2) {
                    gather.setHWPressedShift(true);
                    if (!previousShift) {
                        mgr()->getPCKeyboard()->onPressedShift(true);
                    }
                } else {
                    gather.setHWPressedShift(false);
                    if (previousShift) {
                        if (!gather.isHoldingShift()) {
                            mgr()->getPCKeyboard()->onReleasedShift();
                        }
                    }
                }
            }

            inline bool HWKeyboard::controlKeyTriggeredHandler(input::HKBManager& hkbManager) {
                if ((hkbManager.GetModifierState() & 4) == 0) {
                    return false;
                }
                input::HKBManager::KeySet currentKeySet;
                currentKeySet = hkbManager.GetTriggeredKeySet();
                while (currentKeySet.IsValid()) {
                    switch (currentKeySet.GetKey()) {
                        case 0x28:
                        case 0x58: {
                            mgr()->getToolBar()->onOK();
                            return true;
                        }
                        case 0x29:
                        case 0x2A: {
                            mgr()->getToolBar()->onCancel();
                            return true;
                        }
                        default: {
                            currentKeySet = currentKeySet.GetNext();
                            break;
                        }
                    }
                }
                return false;
            }

            bool HWKeyboard::updateInput(input::HKBManager& hkbManager) {
                if (!static_cast<signwindow::LayoutByNW4R*>(mgr()->getSignKeyboard())->isActive() &&
                    !controlKeyTriggeredHandler(hkbManager) &&
                    !updateRepeatKey_(hkbManager) && !updateTriggerKey_(hkbManager)) {
                    updateTappingShift_(hkbManager);
                }
                updateShift(hkbManager);
                return false;
            }

            bool HWKeyboard::updateRepeatKey_(input::HKBManager& hkbManager) {
                u32 modifierState = hkbManager.GetModifierState();
                input::HKBManager::KeySet currentKeySet;
                currentKeySet = hkbManager.GetRepeatedKeySet();

                if (!currentKeySet.IsValid()) {
                    return false;
                }

                if (!mgr()->getToolBar()->isQwerty()) {
                    if (mgr()->getToolBar()->isEnableKeytopChange()) {
                        return true;
                    }
                }

                u32 modifierFlag = modifierState & 0x8;

                while (currentKeySet.IsValid()) {
                    int key = currentKeySet.GetKey();
                    u32 command;

                    if (key == 0x4c) {
                        goto sendCommand2;
                    }

                    if (key < 0x4c) {
                        if (key != 0x2b) {
                            if (key < 0x2b) {
                                if (key >= 0x2a) {
                                    goto sendCommand1;
                                }
                            } else {
                                if (key >= 0x2d) {
                                    goto nextRepeatedKey;
                                }
                                goto checkSpecialCommand;
                            }
                        }
                        goto nextRepeatedKey;
                    }

                    if (key == 0x51) {
                        goto setNavigationCommand1e;
                    }

                    if (key < 0x51) {
                        if (key == 0x4f) {
                            goto setNavigationCommand20;
                        } else if (key >= 0x4f) {
                            goto setNavigationCommand1f;
                        }
                    } else {
                        if (key >= 0x53) {
                            goto nextRepeatedKey;
                        }
                        goto setNavigationCommand1d;
                    }

                    goto nextRepeatedKey;

                sendCommand2:
                    sendCommand(2, NULL);
                    goto nextRepeatedKey;

                sendCommand1:
                    sendCommand(1, NULL);
                    goto nextRepeatedKey;

                setNavigationCommand20:
                    command = 0x20;
                    goto sendNavigationCommand;

                setNavigationCommand1f:
                    command = 0x1f;
                    goto sendNavigationCommand;

                setNavigationCommand1e:
                    command = 0x1e;
                    goto sendNavigationCommand;

                setNavigationCommand1d:
                    command = 0x1d;

                sendNavigationCommand:
                    {
                        u32 commandData[2];
                        commandData[0] = command;
                        commandData[1] = modifierState;
                        sendCommand(0x26, commandData);
                    }
                    goto nextRepeatedKey;

                checkSpecialCommand:
                    if (mgr()->getToolBar()->isQwerty() ||
                        !mgr()->getCellPhoneKeyboard()->isNumeric()) {
                        if (modifierFlag == 0) {
                            goto sendSpecialCommand;
                        }
                    }
                    goto nextRepeatedKey;

                sendSpecialCommand:
                    {
                        NavigationCommand commandData = {8, modifierState};
                        sendCommand(0x26, &commandData);
                    }

                nextRepeatedKey:

                    currentKeySet = currentKeySet.GetNext();
                }

                return false;
            }

            bool HWKeyboard::updateTriggerKey_(input::HKBManager& hkbManager) {
                u32 modifierState = hkbManager.GetModifierState();
                input::HKBManager::KeySet currentKeySet;
                currentKeySet = hkbManager.GetTriggeredKeySet();

                if (!currentKeySet.IsValid()) {
                    return false;
                }

                if (!mgr()->getToolBar()->isQwerty() &&
                    mgr()->getToolBar()->isEnableKeytopChange()) {
                    return true;
                }

                if (!mgr()->getPCKeyboard()->isABC()) {
                    if (mgr()->getToolBar()->isQwerty()) {
                        EventObserver* eventObserver = mgr()->getEventObserverForHardware();
                        if (eventObserver != NULL) {
                            eventObserver->onSE(sound::SE_KETAI_MODE_SWITCHING);
                        }
                    }
                    mgr()->getPCKeyboard()->setABC(true);
                }

                while (currentKeySet.IsValid()) {
                    u32 character = currentKeySet.GetWChar();
                    u8 key = currentKeySet.GetKey();

                    if (static_cast<wchar_t>(character) == 0x20) {
                        if ((modifierState & 0x8) != 0) {
                            NavigationCommand commandData = {8, modifierState};
                            sendCommand(0x26, &commandData);
                        }
                    } else if (static_cast<wchar_t>(character) != 0) {
                        bool sendCharacter = true;
                        if (!mgr()->getToolBar()->isQwerty() &&
                            mgr()->getCellPhoneKeyboard()->isNumeric()) {
                            if (static_cast<wchar_t>(character) == '/') {
                                goto suppressCharacter;
                            }
                            if (static_cast<wchar_t>(character) < '/') {
                                if (static_cast<wchar_t>(character) >= '.') {
                                    goto checkNumericDot;
                                }
                                goto suppressCharacter;
                            }
                            if (static_cast<wchar_t>(character) >= ':') {
                                goto suppressCharacter;
                            }
                            goto sendCharacterCheck;
                        checkNumericDot:
                            if (mgr()->getCellPhoneKeyboard()->isNumericWithDot()) {
                                goto sendCharacterCheck;
                            }
                        suppressCharacter:
                            sendCharacter = false;
                        }

                        goto sendCharacterCheck;
                    sendCharacterCheck:
                        if (sendCharacter) {
                            modifierState = 0;
                            if ((hkbManager.GetModifierState() & 0x2) != 0) {
                                modifierState |= 1;
                            }
                            if ((hkbManager.GetModifierState() & 0x200) != 0) {
                                modifierState |= 2;
                            }
                            if ((modifierState & 1) == 0) {
                                keyboard::pctype::Base::KeyState& keyState = mgr()->getPCKeyboard()->hardwareKeyState();
                                keyState.setABCFlag(keyState.abcFlags & 0xffffff70);
                            }

                            character = convertWCCode(character);
                                                        KeyInputData keyInputData = {0, 0, 0, 1, 0, 0, 0};
                            keyInputData.character = character;
                            keyInputData.modifier = modifierState;
                            sendCommand(0, &keyInputData);

                            if (mgr()->getLanguage() == CN) {
                                if (static_cast<wchar_t>(character + (0x10000 - 0x201c)) <= 1) {
                                    mbDoubleQuoteClosing = !mbDoubleQuoteClosing;
                                } else if (static_cast<wchar_t>(character + (0x10000 - 0x2018)) <= 1) {
                                    mbSingleQuoteClosing = !mbSingleQuoteClosing;
                                }

                            }
                        }
                    } else {
                        bool sendKey = true;
                        int translatedKey;
                        if (key < 0x20) {
                            translatedKey = 0;
                        } else if (key < 0x98) {
                            translatedKey = controlKeys[key - 0x20];
                        } else if (key < 0xe0) {
                            translatedKey = 0;
                        } else if (key < 0xf0) {
                            translatedKey = controlKeys[key - 0x68];
                        } else {
                            translatedKey = 0;
                        }

                        if (translatedKey == 0x1c) {
                            bool capsLock = !(hkbManager.GetModifierState() & 0x100);
                            if (!mgr()->getToolBar()->isQwerty() &&
                                mgr()->getCellPhoneKeyboard()->isNumeric()) {
                                capsLock = true;
                            }
                            hkbManager.SetModifierState(capsLock ? 0x100 : 0, 0x100);
                        }

                        if (mgr()->getToolBar()->isQwerty() ||
                            !mgr()->getCellPhoneKeyboard()->isNumeric()) {
                            goto sendKeyCheck;
                        }

                        switch (translatedKey) {
                        case 0x15:
                        case 0x16:
                        case 0x1d:
                        case 0x1e:
                        case 0x1f:
                        case 0x20:
                            break;
                        default:
                            sendKey = false;
                            break;
                        }
                    sendKeyCheck:
                        if (sendKey) {
                            u32 commandData[2] = {translatedKey, modifierState};
                            sendCommand(0x26, commandData);
                        }
                    }

                    int capsKey = currentKeySet.GetKey();
                    switch (capsKey) {
                    case 0x39:
                        if (mgr()->getToolBar()->isQwerty() ||
                            mgr()->getToolBar()->isEnableKeytopChange()) {
                            mgr()->getPCKeyboard()->onPressedCaps();
                        }
                        break;
                    default:
                        break;
                    }

                    currentKeySet = currentKeySet.GetNext();
                }

                return false;
            }

            bool HWKeyboard::updateTappingShift_(input::HKBManager& hkbManager) {
                hkbManager.GetModifierState();
                input::HKBManager::KeySet currentKeySet;
                input::HKBManager::KeySet triggeredKeySet;
                input::HKBManager::KeySet releasedKeySet;
                input::HKBManager::KeySet releasedNextKeySet;
                triggeredKeySet = hkbManager.GetTriggeredKeySet();
                currentKeySet = triggeredKeySet;

                while (currentKeySet.IsValid()) {
                    int key = currentKeySet.GetKey();
                    switch (key) {
                    case 0xe5:
                    case 0xe1:
                        mbShiftTapPending = 1;
                        return false;
                    default:
                        mbShiftTapPending = 0;
                        currentKeySet = currentKeySet.GetNext();
                        break;
                    }
                }

                if (mbShiftTapPending == 0) {
                    return false;
                }

                releasedKeySet = hkbManager.GetReleasedKeySet();
                currentKeySet = releasedKeySet;
                while (currentKeySet.IsValid()) {
                    int key = currentKeySet.GetKey();
                    switch (key) {
                    case 0xe5:
                    case 0xe1:
                        mbShiftTapPending = 0;
                        if (mgr()->getToolBar()->isQwerty() &&
                            mgr()->getPCKeyboard()->hardwareLanguageKeyActive()) {
                            sendCommand(0x2e, NULL);
                        }
                        return false;
                    default:
                        currentKeySet = currentKeySet.GetNext();
                        break;
                    }
                }

                return false;
            }

            void HWKeyboard::updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release, void* data) {
                if (trig != 0) {
                    mbShiftTapPending = 0;
                }
            }

extern "C" const u8 scCountryMap_EU[] = {0x0f, 0x21, 0x20, 0x08, 0x09, 0x0e, 0x19, 0x00, 0x21, 0x21, 0x00, 0x00};
extern "C" const u8 scCountryMap_NonEU[] = {0x0f, 0x21, 0x20, 0x04, 0x09, 0x0e, 0x11, 0x00, 0x21, 0x21, 0x00, 0x00};

const u8 controlKeys[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x01, 0x0a, 0x03,
    0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00,
    0x00, 0x04, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a,
    0x2b, 0x2c, 0x19, 0x1a, 0x1b, 0x13, 0x15, 0x17, 0x14, 0x16, 0x18, 0x00,
    0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x0f, 0x0e,
    0x00, 0x00, 0x00, 0x00,
    0x11, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x05, 0x07, 0x0b,
    0x06, 0x05, 0x07, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

            wchar_t HWKeyboard::convertWCCode(wchar_t code) const {
                if (mgr()->getToolBar()->isQwerty() && mgr()->getPCKeyboard()->getTranslateMode()) {
                    if (mgr()->getLanguage() == JP) {
                        switch (code) {
                            case 0x2C: { return 0x3001; }
                            case 0x2E: { return 0x3002; }
                            case 0x2D: { return 0x30FC; }
                            case 0x5B: { return 0x300C; }
                            case 0x5D: { return 0x300D; }
                        }
                    } else if (mgr()->getLanguage() == CN) {
                        switch (code) {
                            case 0x2C: { return 0xFF0C; }
                            case 0x2E: { return 0x3002; }
                            case 0x3C: { return 0x300A; }
                            case 0x3E: { return 0x300B; }
                            case 0x21: { return 0xFF01; }
                            case 0x3F: { return 0xFF1F; }
                            case 0x28: { return 0xFF08; }
                            case 0x29: { return 0xFF09; }
                            case 0x3A: { return 0xFF1A; }
                            case 0x3B: { return 0xFF1B; }
                            case 0x2D: { return 0xFF0D; }
                            case 0x5F: { return 0xFF3F; }
                            case 0x5C: { return 0x3001; }
                            case 0x27: { if (mbSingleQuoteClosing) { return 0x2019; } return 0x2018; }
                            case 0x22: { if (mbDoubleQuoteClosing) { return 0x201D; } return 0x201C; }
                        }
                    }
                }
                return code;
            }



            void HWKeyboard::setLanguage(Destination destination, Language language) {
                if (destination == DST_EU) {
                    input::HKBManager::getInstance().SetCountry(scCountryMap_EU[language]);
                } else {
                    input::HKBManager::getInstance().SetCountry(scCountryMap_NonEU[language]);
                }
            }
        }  // namespace hwkey

    }  // namespace keyboard

}  // namespace textinput

