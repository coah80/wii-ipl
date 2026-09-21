#include "keyboard/tiHwKeyboard.h"

#include "keyboard/tiManager.h"
#include "keyboard/tiHKBManager.h"
#include "keyboard/tiLayoutGather.h"

extern const u8 lbl_81616BD8[] = {0x0f, 0x21, 0x20, 0x08, 0x09, 0x0e, 0x19, 0x00, 0x21, 0x21, 0x00, 0x00};
extern const u8 lbl_81616BE4[] = {0x0f, 0x21, 0x20, 0x04, 0x09, 0x0e, 0x11, 0x00, 0x21, 0x21, 0x00, 0x00};
extern "C" void SetCountry__Q39textinput5input10HKBManagerFUc();
extern "C" textinput::input::HKBManager sInstance__Q39textinput5input10HKBManager;
extern "C" char jumptable_81668EF8[];

namespace textinput {

    namespace keyboard {

        namespace hwkey {
            extern "C" void GetTriggeredKeySet__Q39textinput5input10HKBManagerCFv();
            extern "C" void IsValid__Q49textinput5input10HKBManager6KeySetCFv();
            extern "C" void GetKey__Q49textinput5input10HKBManager6KeySetCFv();
            extern "C" void GetNext__Q49textinput5input10HKBManager6KeySetCFv();
            extern "C" void GetModifierState__Q39textinput5input10HKBManagerCFv();
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
                lis r3, jumptable_81668EF8@ha
                slwi r0, r0, 2
                addi r3, r3, jumptable_81668EF8@l
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
