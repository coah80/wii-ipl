#include "keyboard/tiHwKeyboard.h"

#include "keyboard/tiManager.h"
#include "keyboard/tiHKBManager.h"
#include "keyboard/tiLayoutGather.h"

extern const u8 lbl_81616BD8[] = {0x0f, 0x21, 0x20, 0x08, 0x09, 0x0e, 0x19, 0x00, 0x21, 0x21, 0x00, 0x00};
extern const u8 lbl_81616BE4[] = {0x0f, 0x21, 0x20, 0x04, 0x09, 0x0e, 0x11, 0x00, 0x21, 0x21, 0x00, 0x00};
extern "C" void SetCountry__Q39textinput5input10HKBManagerFUc();
extern "C" textinput::input::HKBManager sInstance__Q39textinput5input10HKBManager;

namespace textinput {

    namespace keyboard {

        namespace hwkey {
            HWKeyboard::HWKeyboard(Manager* manager) : mpManager(manager), field_0x14(0), field_0x15(0), field_0x16(0) {
            }

            void HWKeyboard::init() {
                LayoutGather::Singleton::getInstance().setHWPressedShift(false);

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

            bool HWKeyboard::updateInput(input::HKBManager &hkbManager) {
                cellphonetype::KeySet set;
                mgr()->getSignKeyboard();
                // TODO

                return true;
            }

            extern "C" asm void setLanguage__Q49textinput8keyboard5hwkey10HWKeyboardFQ29textinput11DestinationQ29textinput8Language() {
                nofralloc
                cmpwi r4, 2
                bne setLanguage_L1
                lis r4, lbl_81616BD8@ha
                lis r3, sInstance__Q39textinput5input10HKBManager@ha
                addi r4, r4, lbl_81616BD8@l
                lbzx r4, r4, r5
                addi r3, r3, sInstance__Q39textinput5input10HKBManager@l
                b SetCountry__Q39textinput5input10HKBManagerFUc
            setLanguage_L1:
                lis r4, lbl_81616BE4@ha
                lis r3, sInstance__Q39textinput5input10HKBManager@ha
                addi r4, r4, lbl_81616BE4@l
                lbzx r4, r4, r5
                addi r3, r3, sInstance__Q39textinput5input10HKBManager@l
                b SetCountry__Q39textinput5input10HKBManagerFUc
            }
        }  // namespace hwkey

    }  // namespace keyboard

}  // namespace textinput
