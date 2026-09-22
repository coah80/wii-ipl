#include "keyboard/tiHwKeyboard.h"

#include "keyboard/tiManager.h"
#include "keyboard/tiHKBManager.h"
#include "keyboard/tiLayoutGather.h"

extern const u8 lbl_81616B88[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
extern const u8 lbl_81616BC8[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
extern const u8 lbl_81616BD8[] = {0x0f, 0x21, 0x20, 0x08, 0x09, 0x0e, 0x19, 0x00, 0x21, 0x21, 0x00, 0x00};
extern const u8 lbl_81616BE4[] = {0x0f, 0x21, 0x20, 0x04, 0x09, 0x0e, 0x11, 0x00, 0x21, 0x21, 0x00, 0x00};
extern const u8 lbl_81616BF0[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x01, 0x0a, 0x03, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x19, 0x1a, 0x1b, 0x13, 0x15, 0x17, 0x14, 0x16, 0x18, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x0f, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x11, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x05, 0x07, 0x0b, 0x06, 0x05, 0x07, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
extern "C" u32 lbl_81694EF8;
extern "C" u32 lbl_81694F00;
extern "C" void _savegpr_23();
extern "C" void _restgpr_23();
extern "C" void onPressedCaps__Q49textinput8keyboard6pctype12LayoutByNW4RFv();
extern "C" void SetModifierState__Q39textinput5input10HKBManagerFUlUl();
extern "C" void setABCFlag__Q59textinput8keyboard6pctype4Base8KeyStateFUl();
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
extern "C" KeyboardDataFunction const jumptable_81668EF8[0x3f] = {
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
            extern "C" void GetTriggeredKeySet__Q39textinput5input10HKBManagerCFv();
            extern "C" void IsValid__Q49textinput5input10HKBManager6KeySetCFv();
            extern "C" void GetKey__Q49textinput5input10HKBManager6KeySetCFv();
            extern "C" void GetNext__Q49textinput5input10HKBManager6KeySetCFv();
            extern "C" void GetModifierState__Q39textinput5input10HKBManagerCFv();
            extern "C" void GetRepeatedKeySet__Q39textinput5input10HKBManagerCFv();
            extern "C" void GetWChar__Q49textinput5input10HKBManager6KeySetCFv();
            extern "C" void GetReleasedKeySet__Q39textinput5input10HKBManagerCFv();
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

            extern "C" asm bool updateRepeatKey___Q49textinput8keyboard5hwkey10HWKeyboardFRQ39textinput5input10HKBManager() {
                nofralloc
                stwu r1, -0x50(r1)
                mflr r0
                stw r0, 0x54(r1)
                stw r31, 0x4c(r1)
                mr r31, r3
                stw r30, 0x48(r1)
                stw r29, 0x44(r1)
                mr r29, r4
                mr r3, r29
                bl GetModifierState__Q39textinput5input10HKBManagerCFv
                li r5, 0x0
                li r0, -0x1
                stw r5, 0x30(r1)
                mr r30, r3
                mr r4, r29
                addi r3, r1, 0x24
                stb r5, 0x34(r1)
                stb r0, 0x35(r1)
                stb r5, 0x36(r1)
                sth r5, 0x38(r1)
                bl GetRepeatedKeySet__Q39textinput5input10HKBManagerCFv
                lwz r7, 0x24(r1)
                addi r3, r1, 0x30
                lbz r6, 0x28(r1)
                lbz r5, 0x29(r1)
                lbz r4, 0x2a(r1)
                lhz r0, 0x2c(r1)
                stw r7, 0x30(r1)
                stb r6, 0x34(r1)
                stb r5, 0x35(r1)
                stb r4, 0x36(r1)
                sth r0, 0x38(r1)
                bl IsValid__Q49textinput5input10HKBManager6KeySetCFv
                cmpwi r3, 0x0
                bne updateRepeatKey_HWKeyboard_L48F6C
                li r3, 0x0
                b updateRepeatKey_HWKeyboard_L4918C
                updateRepeatKey_HWKeyboard_L48F6C:
                lwz r3, 0x10(r31)
                lwz r12, 0x0(r3)
                lwz r12, 0x94(r12)
                mtctr r12
                bctrl
                lwz r12, 0x0(r3)
                lwz r12, 0x10(r12)
                mtctr r12
                bctrl
                cmpwi r3, 0x0
                bne updateRepeatKey_HWKeyboard_L48FCC
                lwz r3, 0x10(r31)
                lwz r12, 0x0(r3)
                lwz r12, 0x94(r12)
                mtctr r12
                bctrl
                lwz r12, 0x0(r3)
                lwz r12, 0xac(r12)
                mtctr r12
                bctrl
                cmpwi r3, 0x0
                beq updateRepeatKey_HWKeyboard_L48FCC
                li r3, 0x1
                b updateRepeatKey_HWKeyboard_L4918C
                updateRepeatKey_HWKeyboard_L48FCC:
                rlwinm r29, r30, 0, 28, 28
                b updateRepeatKey_HWKeyboard_L49178
                updateRepeatKey_HWKeyboard_L48FD4:
                addi r3, r1, 0x30
                bl GetKey__Q49textinput5input10HKBManager6KeySetCFv
                clrlwi r0, r3, 24
                cmpwi r0, 0x4c
                beq updateRepeatKey_HWKeyboard_L49038
                bge updateRepeatKey_HWKeyboard_L49010
                cmpwi r0, 0x2b
                beq updateRepeatKey_HWKeyboard_L49144
                bge updateRepeatKey_HWKeyboard_L49004
                cmpwi r0, 0x2a
                bge updateRepeatKey_HWKeyboard_L49058
                b updateRepeatKey_HWKeyboard_L49144
                updateRepeatKey_HWKeyboard_L49004:
                cmpwi r0, 0x2d
                bge updateRepeatKey_HWKeyboard_L49144
                b updateRepeatKey_HWKeyboard_L490BC
                updateRepeatKey_HWKeyboard_L49010:
                cmpwi r0, 0x51
                beq updateRepeatKey_HWKeyboard_L49088
                bge updateRepeatKey_HWKeyboard_L4902C
                cmpwi r0, 0x4f
                beq updateRepeatKey_HWKeyboard_L49078
                bge updateRepeatKey_HWKeyboard_L49080
                b updateRepeatKey_HWKeyboard_L49144
                updateRepeatKey_HWKeyboard_L4902C:
                cmpwi r0, 0x53
                bge updateRepeatKey_HWKeyboard_L49144
                b updateRepeatKey_HWKeyboard_L49090
                updateRepeatKey_HWKeyboard_L49038:
                lwz r12, 0x0(r31)
                mr r3, r31
                li r4, 0x2
                li r5, 0x0
                lwz r12, 0x18(r12)
                mtctr r12
                bctrl
                b updateRepeatKey_HWKeyboard_L49144
                updateRepeatKey_HWKeyboard_L49058:
                lwz r12, 0x0(r31)
                mr r3, r31
                li r4, 0x1
                li r5, 0x0
                lwz r12, 0x18(r12)
                mtctr r12
                bctrl
                b updateRepeatKey_HWKeyboard_L49144
                updateRepeatKey_HWKeyboard_L49078:
                li r0, 0x20
                b updateRepeatKey_HWKeyboard_L49094
                updateRepeatKey_HWKeyboard_L49080:
                li r0, 0x1f
                b updateRepeatKey_HWKeyboard_L49094
                updateRepeatKey_HWKeyboard_L49088:
                li r0, 0x1e
                b updateRepeatKey_HWKeyboard_L49094
                updateRepeatKey_HWKeyboard_L49090:
                li r0, 0x1d
                updateRepeatKey_HWKeyboard_L49094:
                stw r0, 0x10(r1)
                mr r3, r31
                addi r5, r1, 0x10
                li r4, 0x26
                stw r30, 0x14(r1)
                lwz r12, 0x0(r31)
                lwz r12, 0x18(r12)
                mtctr r12
                bctrl
                b updateRepeatKey_HWKeyboard_L49144
                updateRepeatKey_HWKeyboard_L490BC:
                lwz r3, 0x10(r31)
                lwz r12, 0x0(r3)
                lwz r12, 0x94(r12)
                mtctr r12
                bctrl
                lwz r12, 0x0(r3)
                lwz r12, 0x10(r12)
                mtctr r12
                bctrl
                cmpwi r3, 0x0
                bne updateRepeatKey_HWKeyboard_L49114
                lwz r3, 0x10(r31)
                lwz r12, 0x0(r3)
                lwz r12, 0x7c(r12)
                mtctr r12
                bctrl
                lwz r12, 0x0(r3)
                lwz r12, 0x48(r12)
                mtctr r12
                bctrl
                cmpwi r3, 0x0
                bne updateRepeatKey_HWKeyboard_L49144
                updateRepeatKey_HWKeyboard_L49114:
                cmpwi r29, 0x0
                bne updateRepeatKey_HWKeyboard_L49144
                lwz r0, lbl_81694EF8(r0)
                mr r3, r31
                stw r30, 0xc(r1)
                addi r5, r1, 0x8
                li r4, 0x26
                stw r0, 0x8(r1)
                lwz r12, 0x0(r31)
                lwz r12, 0x18(r12)
                mtctr r12
                bctrl
                updateRepeatKey_HWKeyboard_L49144:
                addi r3, r1, 0x18
                addi r4, r1, 0x30
                bl GetNext__Q49textinput5input10HKBManager6KeySetCFv
                lwz r6, 0x18(r1)
                lbz r5, 0x1c(r1)
                lbz r4, 0x1d(r1)
                lbz r3, 0x1e(r1)
                lhz r0, 0x20(r1)
                stw r6, 0x30(r1)
                stb r5, 0x34(r1)
                stb r4, 0x35(r1)
                stb r3, 0x36(r1)
                sth r0, 0x38(r1)
                updateRepeatKey_HWKeyboard_L49178:
                addi r3, r1, 0x30
                bl IsValid__Q49textinput5input10HKBManager6KeySetCFv
                cmpwi r3, 0x0
                bne updateRepeatKey_HWKeyboard_L48FD4
                li r3, 0x0
                updateRepeatKey_HWKeyboard_L4918C:
                lwz r0, 0x54(r1)
                lwz r31, 0x4c(r1)
                lwz r30, 0x48(r1)
                lwz r29, 0x44(r1)
                mtlr r0
                addi r1, r1, 0x50
                blr
            }

            extern "C" asm bool updateTriggerKey___Q49textinput8keyboard5hwkey10HWKeyboardFRQ39textinput5input10HKBManager() {
                nofralloc
                stwu r1, -0x80(r1)
                mflr r0
                stw r0, 0x84(r1)
                addi r11, r1, 0x80
                bl _savegpr_23
                mr r28, r4
                mr r27, r3
                mr r3, r28
                bl GetModifierState__Q39textinput5input10HKBManagerCFv
                li r5, 0x0
                li r0, -0x1
                stw r5, 0x40(r1)
                mr r29, r3
                mr r4, r28
                addi r3, r1, 0x24
                stb r5, 0x44(r1)
                stb r0, 0x45(r1)
                stb r5, 0x46(r1)
                sth r5, 0x48(r1)
                bl GetTriggeredKeySet__Q39textinput5input10HKBManagerCFv
                lwz r7, 0x24(r1)
                addi r3, r1, 0x40
                lbz r6, 0x28(r1)
                lbz r5, 0x29(r1)
                lbz r4, 0x2a(r1)
                lhz r0, 0x2c(r1)
                stw r7, 0x40(r1)
                stb r6, 0x44(r1)
                stb r5, 0x45(r1)
                stb r4, 0x46(r1)
                sth r0, 0x48(r1)
                bl IsValid__Q49textinput5input10HKBManager6KeySetCFv
                cmpwi r3, 0x0
                bne updateTriggerKey_HWKeyboard_L49238
                li r3, 0x0
                b updateTriggerKey_HWKeyboard_L497E4
                updateTriggerKey_HWKeyboard_L49238:
                lwz r3, 0x10(r27)
                lwz r12, 0x0(r3)
                lwz r12, 0x94(r12)
                mtctr r12
                bctrl
                lwz r12, 0x0(r3)
                lwz r12, 0x10(r12)
                mtctr r12
                bctrl
                cmpwi r3, 0x0
                bne updateTriggerKey_HWKeyboard_L49298
                lwz r3, 0x10(r27)
                lwz r12, 0x0(r3)
                lwz r12, 0x94(r12)
                mtctr r12
                bctrl
                lwz r12, 0x0(r3)
                lwz r12, 0xac(r12)
                mtctr r12
                bctrl
                cmpwi r3, 0x0
                beq updateTriggerKey_HWKeyboard_L49298
                li r3, 0x1
                b updateTriggerKey_HWKeyboard_L497E4
                updateTriggerKey_HWKeyboard_L49298:
                lwz r3, 0x10(r27)
                lwz r12, 0x0(r3)
                lwz r12, 0x74(r12)
                mtctr r12
                bctrl
                lwz r12, 0x0(r3)
                lwz r12, 0x48(r12)
                mtctr r12
                bctrl
                cmpwi r3, 0x0
                bne updateTriggerKey_HWKeyboard_L4933C
                lwz r3, 0x10(r27)
                lwz r12, 0x0(r3)
                lwz r12, 0x94(r12)
                mtctr r12
                bctrl
                lwz r12, 0x0(r3)
                lwz r12, 0x10(r12)
                mtctr r12
                bctrl
                cmpwi r3, 0x0
                beq updateTriggerKey_HWKeyboard_L49314
                lwz r3, 0x10(r27)
                lwz r3, 0x30(r3)
                cmpwi r3, 0x0
                beq updateTriggerKey_HWKeyboard_L49314
                lwz r12, 0x0(r3)
                li r4, 0xd
                lwz r12, 0x14(r12)
                mtctr r12
                bctrl
                updateTriggerKey_HWKeyboard_L49314:
                lwz r3, 0x10(r27)
                lwz r12, 0x0(r3)
                lwz r12, 0x74(r12)
                mtctr r12
                bctrl
                lwz r12, 0x0(r3)
                li r4, 0x1
                lwz r12, 0x4c(r12)
                mtctr r12
                bctrl
                updateTriggerKey_HWKeyboard_L4933C:
                lis r26, lbl_81616BF0@ha
                lis r31, lbl_81616BC8@ha
                li r30, -0x90
                addi r31, r31, lbl_81616BC8@l
                addi r26, r26, lbl_81616BF0@l
                b updateTriggerKey_HWKeyboard_L497D0
                updateTriggerKey_HWKeyboard_L49354:
                addi r3, r1, 0x40
                bl GetWChar__Q49textinput5input10HKBManager6KeySetCFv
                mr r25, r3
                addi r3, r1, 0x40
                bl GetKey__Q49textinput5input10HKBManager6KeySetCFv
                clrlwi r0, r25, 16
                cmplwi r0, 0x20
                bne updateTriggerKey_HWKeyboard_L493A8
                rlwinm. r0, r29, 0, 28, 28
                beq updateTriggerKey_HWKeyboard_L49714
                lwz r0, lbl_81694F00(r0)
                mr r3, r27
                stw r29, 0x14(r1)
                addi r5, r1, 0x10
                li r4, 0x26
                stw r0, 0x10(r1)
                lwz r12, 0x0(r27)
                lwz r12, 0x18(r12)
                mtctr r12
                bctrl
                b updateTriggerKey_HWKeyboard_L49714
                updateTriggerKey_HWKeyboard_L493A8:
                cmpwi r0, 0x0
                beq updateTriggerKey_HWKeyboard_L4957C
                lwz r3, 0x10(r27)
                li r24, 0x1
                lwz r12, 0x0(r3)
                lwz r12, 0x94(r12)
                mtctr r12
                bctrl
                lwz r12, 0x0(r3)
                lwz r12, 0x10(r12)
                mtctr r12
                bctrl
                cmpwi r3, 0x0
                bne updateTriggerKey_HWKeyboard_L49464
                lwz r3, 0x10(r27)
                lwz r12, 0x0(r3)
                lwz r12, 0x7c(r12)
                mtctr r12
                bctrl
                lwz r12, 0x0(r3)
                lwz r12, 0x48(r12)
                mtctr r12
                bctrl
                cmpwi r3, 0x0
                beq updateTriggerKey_HWKeyboard_L49464
                clrlwi r0, r25, 16
                cmpwi r0, 0x2f
                beq updateTriggerKey_HWKeyboard_L49460
                bge updateTriggerKey_HWKeyboard_L49428
                cmpwi r0, 0x2e
                bge updateTriggerKey_HWKeyboard_L49434
                b updateTriggerKey_HWKeyboard_L49460
                updateTriggerKey_HWKeyboard_L49428:
                cmpwi r0, 0x3a
                bge updateTriggerKey_HWKeyboard_L49460
                b updateTriggerKey_HWKeyboard_L49464
                updateTriggerKey_HWKeyboard_L49434:
                lwz r3, 0x10(r27)
                lwz r12, 0x0(r3)
                lwz r12, 0x7c(r12)
                mtctr r12
                bctrl
                lwz r12, 0x0(r3)
                lwz r12, 0x4c(r12)
                mtctr r12
                bctrl
                cmpwi r3, 0x0
                bne updateTriggerKey_HWKeyboard_L49464
                updateTriggerKey_HWKeyboard_L49460:
                li r24, 0x0
                updateTriggerKey_HWKeyboard_L49464:
                cmpwi r24, 0x0
                beq updateTriggerKey_HWKeyboard_L49714
                mr r3, r28
                li r29, 0x0
                bl GetModifierState__Q39textinput5input10HKBManagerCFv
                rlwinm. r0, r3, 0, 30, 30
                beq updateTriggerKey_HWKeyboard_L49484
                ori r29, r29, 0x1
                updateTriggerKey_HWKeyboard_L49484:
                mr r3, r28
                bl GetModifierState__Q39textinput5input10HKBManagerCFv
                rlwinm. r0, r3, 0, 22, 22
                beq updateTriggerKey_HWKeyboard_L49498
                ori r29, r29, 0x2
                updateTriggerKey_HWKeyboard_L49498:
                clrlwi. r0, r29, 31
                bne updateTriggerKey_HWKeyboard_L494C0
                lwz r3, 0x10(r27)
                lwz r12, 0x0(r3)
                lwz r12, 0x74(r12)
                mtctr r12
                bctrl
                lwzu r0, 0x20(r3)
                and r4, r0, r30
                bl setABCFlag__Q59textinput8keyboard6pctype4Base8KeyStateFUl
                updateTriggerKey_HWKeyboard_L494C0:
                mr r3, r27
                clrlwi r4, r25, 16
                bl convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw
                lwz r4, 0x0(r31)
                clrlwi r25, r3, 16
                lwz r0, 0x4(r31)
                addi r5, r1, 0x30
                stw r4, 0x30(r1)
                li r4, 0x0
                lwz r6, 0x8(r31)
                stw r0, 0x34(r1)
                lwz r0, 0xc(r31)
                sth r3, 0x30(r1)
                mr r3, r27
                stw r6, 0x38(r1)
                stw r0, 0x3c(r1)
                stw r29, 0x34(r1)
                lwz r12, 0x0(r27)
                lwz r12, 0x18(r12)
                mtctr r12
                bctrl
                lwz r3, 0x10(r27)
                lwz r12, 0x0(r3)
                lwz r12, 0x34(r12)
                mtctr r12
                bctrl
                cmpwi r3, 0x8
                bne updateTriggerKey_HWKeyboard_L49714
                addis r3, r25, 0x1
                subi r0, r3, 0x201c
                clrlwi r0, r0, 16
                cmplwi r0, 0x1
                bgt updateTriggerKey_HWKeyboard_L49558
                lbz r0, 0x16(r27)
                cntlzw r0, r0
                srwi r0, r0, 5
                stb r0, 0x16(r27)
                b updateTriggerKey_HWKeyboard_L49714
                updateTriggerKey_HWKeyboard_L49558:
                subi r0, r3, 0x2018
                clrlwi r0, r0, 16
                cmplwi r0, 0x1
                bgt updateTriggerKey_HWKeyboard_L49714
                lbz r0, 0x15(r27)
                cntlzw r0, r0
                srwi r0, r0, 5
                stb r0, 0x15(r27)
                b updateTriggerKey_HWKeyboard_L49714
                updateTriggerKey_HWKeyboard_L4957C:
                clrlwi r0, r3, 24
                li r24, 0x1
                cmplwi r0, 0x20
                bge updateTriggerKey_HWKeyboard_L49594
                li r25, 0x0
                b updateTriggerKey_HWKeyboard_L495D0
                updateTriggerKey_HWKeyboard_L49594:
                cmplwi r0, 0x98
                bge updateTriggerKey_HWKeyboard_L495A8
                add r3, r26, r0
                lbz r25, -0x20(r3)
                b updateTriggerKey_HWKeyboard_L495D0
                updateTriggerKey_HWKeyboard_L495A8:
                cmplwi r0, 0xe0
                bge updateTriggerKey_HWKeyboard_L495B8
                li r25, 0x0
                b updateTriggerKey_HWKeyboard_L495D0
                updateTriggerKey_HWKeyboard_L495B8:
                cmplwi r0, 0xf0
                bge updateTriggerKey_HWKeyboard_L495CC
                add r3, r26, r0
                lbz r25, -0x68(r3)
                b updateTriggerKey_HWKeyboard_L495D0
                updateTriggerKey_HWKeyboard_L495CC:
                li r25, 0x0
                updateTriggerKey_HWKeyboard_L495D0:
                cmpwi r25, 0x1c
                bne updateTriggerKey_HWKeyboard_L49664
                mr r3, r28
                bl GetModifierState__Q39textinput5input10HKBManagerCFv
                rlwinm r0, r3, 0, 23, 23
                lwz r3, 0x10(r27)
                cntlzw r0, r0
                lwz r12, 0x0(r3)
                srwi r23, r0, 5
                lwz r12, 0x94(r12)
                mtctr r12
                bctrl
                lwz r12, 0x0(r3)
                lwz r12, 0x10(r12)
                mtctr r12
                bctrl
                cmpwi r3, 0x0
                bne updateTriggerKey_HWKeyboard_L49648
                lwz r3, 0x10(r27)
                lwz r12, 0x0(r3)
                lwz r12, 0x7c(r12)
                mtctr r12
                bctrl
                lwz r12, 0x0(r3)
                lwz r12, 0x48(r12)
                mtctr r12
                bctrl
                cmpwi r3, 0x0
                beq updateTriggerKey_HWKeyboard_L49648
                li r23, 0x1
                updateTriggerKey_HWKeyboard_L49648:
                neg r0, r23
                mr r3, r28
                or r0, r0, r23
                li r5, 0x100
                srawi r0, r0, 31
                rlwinm r4, r0, 0, 23, 23
                bl SetModifierState__Q39textinput5input10HKBManagerFUlUl
                updateTriggerKey_HWKeyboard_L49664:
                lwz r3, 0x10(r27)
                lwz r12, 0x0(r3)
                lwz r12, 0x94(r12)
                mtctr r12
                bctrl
                lwz r12, 0x0(r3)
                lwz r12, 0x10(r12)
                mtctr r12
                bctrl
                cmpwi r3, 0x0
                bne updateTriggerKey_HWKeyboard_L496E8
                lwz r3, 0x10(r27)
                lwz r12, 0x0(r3)
                lwz r12, 0x7c(r12)
                mtctr r12
                bctrl
                lwz r12, 0x0(r3)
                lwz r12, 0x48(r12)
                mtctr r12
                bctrl
                cmpwi r3, 0x0
                beq updateTriggerKey_HWKeyboard_L496E8
                cmpwi r25, 0x1d
                bge updateTriggerKey_HWKeyboard_L496D8
                cmpwi r25, 0x17
                bge updateTriggerKey_HWKeyboard_L496E4
                cmpwi r25, 0x15
                bge updateTriggerKey_HWKeyboard_L496E8
                b updateTriggerKey_HWKeyboard_L496E4
                updateTriggerKey_HWKeyboard_L496D8:
                cmpwi r25, 0x21
                bge updateTriggerKey_HWKeyboard_L496E4
                b updateTriggerKey_HWKeyboard_L496E8
                updateTriggerKey_HWKeyboard_L496E4:
                li r24, 0x0
                updateTriggerKey_HWKeyboard_L496E8:
                cmpwi r24, 0x0
                beq updateTriggerKey_HWKeyboard_L49714
                stw r25, 0x8(r1)
                mr r3, r27
                addi r5, r1, 0x8
                li r4, 0x26
                stw r29, 0xc(r1)
                lwz r12, 0x0(r27)
                lwz r12, 0x18(r12)
                mtctr r12
                bctrl
                updateTriggerKey_HWKeyboard_L49714:
                addi r3, r1, 0x40
                bl GetKey__Q49textinput5input10HKBManager6KeySetCFv
                clrlwi r0, r3, 24
                cmpwi r0, 0x39
                beq updateTriggerKey_HWKeyboard_L4972C
                b updateTriggerKey_HWKeyboard_L4979C
                updateTriggerKey_HWKeyboard_L4972C:
                lwz r3, 0x10(r27)
                lwz r12, 0x0(r3)
                lwz r12, 0x94(r12)
                mtctr r12
                bctrl
                lwz r12, 0x0(r3)
                lwz r12, 0x10(r12)
                mtctr r12
                bctrl
                cmpwi r3, 0x0
                bne updateTriggerKey_HWKeyboard_L49784
                lwz r3, 0x10(r27)
                lwz r12, 0x0(r3)
                lwz r12, 0x94(r12)
                mtctr r12
                bctrl
                lwz r12, 0x0(r3)
                lwz r12, 0xac(r12)
                mtctr r12
                bctrl
                cmpwi r3, 0x0
                beq updateTriggerKey_HWKeyboard_L4979C
                updateTriggerKey_HWKeyboard_L49784:
                lwz r3, 0x10(r27)
                lwz r12, 0x0(r3)
                lwz r12, 0x74(r12)
                mtctr r12
                bctrl
                bl onPressedCaps__Q49textinput8keyboard6pctype12LayoutByNW4RFv
                updateTriggerKey_HWKeyboard_L4979C:
                addi r3, r1, 0x18
                addi r4, r1, 0x40
                bl GetNext__Q49textinput5input10HKBManager6KeySetCFv
                lwz r6, 0x18(r1)
                lbz r5, 0x1c(r1)
                lbz r4, 0x1d(r1)
                lbz r3, 0x1e(r1)
                lhz r0, 0x20(r1)
                stw r6, 0x40(r1)
                stb r5, 0x44(r1)
                stb r4, 0x45(r1)
                stb r3, 0x46(r1)
                sth r0, 0x48(r1)
                updateTriggerKey_HWKeyboard_L497D0:
                addi r3, r1, 0x40
                bl IsValid__Q49textinput5input10HKBManager6KeySetCFv
                cmpwi r3, 0x0
                bne updateTriggerKey_HWKeyboard_L49354
                li r3, 0x0
                updateTriggerKey_HWKeyboard_L497E4:
                addi r11, r1, 0x80
                bl _restgpr_23
                lwz r0, 0x84(r1)
                mtlr r0
                addi r1, r1, 0x80
                blr
            }

            extern "C" asm bool updateTappingShift___Q49textinput8keyboard5hwkey10HWKeyboardFRQ39textinput5input10HKBManager() {
                nofralloc
                stwu r1, -0x60(r1)
                mflr r0
                stw r0, 0x64(r1)
                stw r31, 0x5c(r1)
                mr r31, r3
                stw r30, 0x58(r1)
                stw r29, 0x54(r1)
                mr r29, r4
                mr r3, r29
                bl GetModifierState__Q39textinput5input10HKBManagerCFv
                li r30, 0x0
                li r0, -0x1
                stw r30, 0x38(r1)
                mr r4, r29
                addi r3, r1, 0x2c
                stb r30, 0x3c(r1)
                stb r0, 0x3d(r1)
                stb r30, 0x3e(r1)
                sth r30, 0x40(r1)
                bl GetTriggeredKeySet__Q39textinput5input10HKBManagerCFv
                lwz r6, 0x2c(r1)
                lbz r5, 0x30(r1)
                lbz r4, 0x31(r1)
                lbz r3, 0x32(r1)
                lhz r0, 0x34(r1)
                stw r6, 0x38(r1)
                stb r5, 0x3c(r1)
                stb r4, 0x3d(r1)
                stb r3, 0x3e(r1)
                sth r0, 0x40(r1)
                b updateTappingShift_HWKeyboard_L498E4
                updateTappingShift_HWKeyboard_L49878:
                addi r3, r1, 0x38
                bl GetKey__Q49textinput5input10HKBManager6KeySetCFv
                clrlwi r0, r3, 24
                cmpwi r0, 0xe5
                beq updateTappingShift_HWKeyboard_L4989C
                bge updateTappingShift_HWKeyboard_L498AC
                cmpwi r0, 0xe1
                beq updateTappingShift_HWKeyboard_L4989C
                b updateTappingShift_HWKeyboard_L498AC
                updateTappingShift_HWKeyboard_L4989C:
                li r0, 0x1
                li r3, 0x0
                stb r0, 0x14(r31)
                b updateTappingShift_HWKeyboard_L49A24
                updateTappingShift_HWKeyboard_L498AC:
                stb r30, 0x14(r31)
                addi r3, r1, 0x20
                addi r4, r1, 0x38
                bl GetNext__Q49textinput5input10HKBManager6KeySetCFv
                lwz r6, 0x20(r1)
                lbz r5, 0x24(r1)
                lbz r4, 0x25(r1)
                lbz r3, 0x26(r1)
                lhz r0, 0x28(r1)
                stw r6, 0x38(r1)
                stb r5, 0x3c(r1)
                stb r4, 0x3d(r1)
                stb r3, 0x3e(r1)
                sth r0, 0x40(r1)
                updateTappingShift_HWKeyboard_L498E4:
                addi r3, r1, 0x38
                bl IsValid__Q49textinput5input10HKBManager6KeySetCFv
                cmpwi r3, 0x0
                bne updateTappingShift_HWKeyboard_L49878
                lbz r0, 0x14(r31)
                cmpwi r0, 0x0
                bne updateTappingShift_HWKeyboard_L49908
                li r3, 0x0
                b updateTappingShift_HWKeyboard_L49A24
                updateTappingShift_HWKeyboard_L49908:
                mr r4, r29
                addi r3, r1, 0x14
                bl GetReleasedKeySet__Q39textinput5input10HKBManagerCFv
                lwz r6, 0x14(r1)
                lbz r5, 0x18(r1)
                lbz r4, 0x19(r1)
                lbz r3, 0x1a(r1)
                lhz r0, 0x1c(r1)
                stw r6, 0x38(r1)
                stb r5, 0x3c(r1)
                stb r4, 0x3d(r1)
                stb r3, 0x3e(r1)
                sth r0, 0x40(r1)
                b updateTappingShift_HWKeyboard_L49A10
                updateTappingShift_HWKeyboard_L49940:
                addi r3, r1, 0x38
                bl GetKey__Q49textinput5input10HKBManager6KeySetCFv
                clrlwi r0, r3, 24
                cmpwi r0, 0xe5
                beq updateTappingShift_HWKeyboard_L49964
                bge updateTappingShift_HWKeyboard_L499DC
                cmpwi r0, 0xe1
                beq updateTappingShift_HWKeyboard_L49964
                b updateTappingShift_HWKeyboard_L499DC
                updateTappingShift_HWKeyboard_L49964:
                li r0, 0x0
                lwz r3, 0x10(r31)
                stb r0, 0x14(r31)
                lwz r12, 0x0(r3)
                lwz r12, 0x94(r12)
                mtctr r12
                bctrl
                lwz r12, 0x0(r3)
                lwz r12, 0x10(r12)
                mtctr r12
                bctrl
                cmpwi r3, 0x0
                beq updateTappingShift_HWKeyboard_L499D4
                lwz r3, 0x10(r31)
                lwz r12, 0x0(r3)
                lwz r12, 0x74(r12)
                mtctr r12
                bctrl
                lbz r0, 0x3d(r3)
                cmpwi r0, 0x0
                beq updateTappingShift_HWKeyboard_L499D4
                lwz r12, 0x0(r31)
                mr r3, r31
                li r4, 0x2e
                li r5, 0x0
                lwz r12, 0x18(r12)
                mtctr r12
                bctrl
                updateTappingShift_HWKeyboard_L499D4:
                li r3, 0x0
                b updateTappingShift_HWKeyboard_L49A24
                updateTappingShift_HWKeyboard_L499DC:
                addi r3, r1, 0x8
                addi r4, r1, 0x38
                bl GetNext__Q49textinput5input10HKBManager6KeySetCFv
                lwz r6, 0x8(r1)
                lbz r5, 0xc(r1)
                lbz r4, 0xd(r1)
                lbz r3, 0xe(r1)
                lhz r0, 0x10(r1)
                stw r6, 0x38(r1)
                stb r5, 0x3c(r1)
                stb r4, 0x3d(r1)
                stb r3, 0x3e(r1)
                sth r0, 0x40(r1)
                updateTappingShift_HWKeyboard_L49A10:
                addi r3, r1, 0x38
                bl IsValid__Q49textinput5input10HKBManager6KeySetCFv
                cmpwi r3, 0x0
                bne updateTappingShift_HWKeyboard_L49940
                li r3, 0x0
                updateTappingShift_HWKeyboard_L49A24:
                lwz r0, 0x64(r1)
                lwz r31, 0x5c(r1)
                lwz r30, 0x58(r1)
                lwz r29, 0x54(r1)
                mtlr r0
                addi r1, r1, 0x60
                blr
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
