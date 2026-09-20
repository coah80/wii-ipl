#include <decomp/ide.h>
#include <math/iplMathTypes.h>
#define IPL_SOUND_RECT_OUT_OF_LINE
#include <nw4r/ut/Rect.h>
#undef IPL_SOUND_RECT_OUT_OF_LINE
#include <revolution/kpad.h>
#include <revolution/mtx/GeoTypes.h>
#include <revolution/os.h>
#include <revolution/os/OSTime.h>
#include <revolution/sc.h>
#include <revolution/wpad.h>

#include "system/iplController.h"
#include "system/iplSystem.h"

const f32 lbl_8160D2C0[] = {0.2, 0.3, 0, 0};
extern const f32 lbl_81694450;
extern const f32 lbl_81694454 = 0.0f;
extern const f32 lbl_81694458;
extern const f32 lbl_8169445C;
extern const f32 lbl_81694460;
extern const f32 lbl_81694478;
extern const f32 lbl_8169447C;
extern const f32 lbl_81694480;
extern const f32 lbl_81694484;
extern const f32 lbl_81694488;
extern const f32 lbl_8169448C;
extern "C" void* mpBuf__Q33ipl10controller7Manager = 0;
extern "C" void* mpParentHeap__Q33ipl10controller7Manager = 0;
extern "C" void* mpHeap__Q33ipl10controller7Manager = 0;
extern "C" void* mpAllocator__Q33ipl10controller7Manager;
extern "C" void _savegpr_25();
extern "C" void _restgpr_25();
extern "C" void _savegpr_16();
extern "C" void _restgpr_16();
extern "C" void _savegpr_29();
extern "C" void _restgpr_29();
extern "C" void _savegpr_27();
extern "C" void _restgpr_27();
extern "C" void _savegpr_28();
extern "C" void _restgpr_28();
extern "C" void __ptmf_scall();
extern "C" void __ct__Q33ipl4math4VEC2Fff();
extern "C" void set__Q33ipl4math4VEC2Fff();
extern "C" void __vt__Q33ipl10controller4Base();
extern "C" void __vt__Q33ipl10controller10Revolution();
extern "C" void __dt__Q33ipl10controller10RevolutionFv();
extern "C" void read__Q33ipl10controller4BaseFv();
extern "C" void isValidDpd__Q33ipl10controller10RevolutionCFv();
extern "C" void getProjectionRect__Q23ipl6SystemFPQ34nw4r2ut4Rect();
extern "C" void __as__Q33ipl4math4VEC2FRCQ33ipl4math4VEC2();
extern "C" void __vt__Q33ipl10controller6Master();
extern "C" void __vt__Q33ipl10controller4Core();
extern "C" void __vt__Q33ipl10controller9FreeStyle();
extern "C" void __ct__Q33ipl10controller10RevolutionFiiR10KPADStatus();
extern "C" void __ct__Q33ipl10controller7ClassicFiR10KPADStatus();
extern "C" asm void alloc__Q33ipl10controller7ManagerFUl();
extern "C" asm void free__Q33ipl10controller7ManagerFPv();
extern "C" void __ct__Q23EGG9AllocatorFPQ23EGG4Heapl();
extern "C" void create__Q23EGG7ExpHeapFPvUlUs();
extern "C" void __nw__FUlPQ23EGG4Heapi();
extern "C" void read__Q33ipl10controller7ManagerFv();
extern "C" void __dl__FPv();

extern "C" asm void __ct__Q34nw4r2ut4RectFv() {
    nofralloc
    lfs f0, lbl_81694454
    stfs f0, 0(r3)
    stfs f0, 4(r3)
    stfs f0, 8(r3)
    stfs f0, 0xc(r3)
    blr
}

extern "C" asm void __dt__Q33ipl10controller7ClassicFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    cmpwi r3, 0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 0x8(r1)
    mr r30, r3
    beq classic_dtor_done
    li r4, 0
    bl __dt__Q33ipl10controller10RevolutionFv
    cmpwi r31, 0
    ble classic_dtor_done
    mr r3, r30
    bl __dl__FPv
classic_dtor_done:
    mr r3, r30
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void __dt__Q33ipl10controller4CoreFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    cmpwi r3, 0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 0x8(r1)
    mr r30, r3
    beq core_dtor_done
    li r4, 0
    bl __dt__Q33ipl10controller10RevolutionFv
    cmpwi r31, 0
    ble core_dtor_done
    mr r3, r30
    bl __dl__FPv
core_dtor_done:
    mr r3, r30
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void __dt__Q33ipl10controller9FreeStyleFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    cmpwi r3, 0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 0x8(r1)
    mr r30, r3
    beq freestyle_dtor_done
    li r4, 0
    bl __dt__Q33ipl10controller10RevolutionFv
    cmpwi r31, 0
    ble freestyle_dtor_done
    mr r3, r30
    bl __dl__FPv
freestyle_dtor_done:
    mr r3, r30
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void getMainStickX__Q33ipl10controller9InterfaceCFv() {
    nofralloc
    li r3, 0
    blr
}

extern "C" asm void getMainStickY__Q33ipl10controller9InterfaceCFv() {
    nofralloc
    li r3, 0
    blr
}

extern "C" asm void getSubStickX__Q33ipl10controller9InterfaceCFv() {
    nofralloc
    li r3, 0
    blr
}

extern "C" asm void getSubStickY__Q33ipl10controller9InterfaceCFv() {
    nofralloc
    li r3, 0
    blr
}

extern "C" asm void getDpdPos__Q33ipl10controller10RevolutionCFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lwz r4, 0x20(r3)
    stw r0, 0x14(r1)
    addi r3, r1, 8
    lfs f1, 0x20(r4)
    lfs f2, 0x24(r4)
    bl __ct__Q33ipl4math4VEC2Fff
    lwz r0, 0x14(r1)
    mr r4, r3
    lwz r3, 0(r3)
    lwz r4, 4(r4)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void getHorizon__Q33ipl10controller10RevolutionCFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lwz r4, 0x20(r3)
    stw r0, 0x14(r1)
    addi r3, r1, 8
    lfs f1, 0x34(r4)
    lfs f2, 0x38(r4)
    bl __ct__Q33ipl4math4VEC2Fff
    lwz r0, 0x14(r1)
    mr r4, r3
    lwz r3, 0(r3)
    lwz r4, 4(r4)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void repeat__Q33ipl10controller10RevolutionCFUl() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    li r31, 0
    stw r30, 8(r1)
    mr r30, r3
    lwz r12, 0(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq iplController_Revolution_repeat_L1
    lwz r3, 0x20(r30)
    lwz r0, 0(r3)
    rlwinm. r0, r0, 0, 0, 0
    beq iplController_Revolution_repeat_L1
    li r31, 1
iplController_Revolution_repeat_L1:
    mr r3, r31
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void down__Q33ipl10controller7ClassicCFUl() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_29
    lwz r12, 0(r3)
    mr r29, r3
    mr r30, r4
    li r31, 0
    lwz r12, 0x6c(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq iplController_Classic_down_L1
    lwz r3, 0x20(r29)
    li r4, 1
    lwz r0, 0(r3)
    and r0, r0, r30
    clrlwi. r0, r0, 16
    bne iplController_Classic_down_L2
    lwz r3, 0x60(r3)
    srwi r0, r30, 16
    and. r0, r3, r0
    bne iplController_Classic_down_L2
    li r4, 0
iplController_Classic_down_L2:
    cmpwi r4, 0
    beq iplController_Classic_down_L1
    li r31, 1
iplController_Classic_down_L1:
    addi r11, r1, 0x20
    mr r3, r31
    bl _restgpr_29
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void downTrg__Q33ipl10controller7ClassicCFUl() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_29
    lwz r12, 0(r3)
    mr r29, r3
    mr r30, r4
    li r31, 0
    lwz r12, 0x6c(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq iplController_Classic_downTrg_L1
    lwz r5, 0x20(r29)
    clrlwi r0, r30, 16
    li r4, 1
    lwz r3, 4(r5)
    and. r0, r3, r0
    bne iplController_Classic_downTrg_L2
    lwz r3, 0x64(r5)
    srwi r0, r30, 16
    and. r0, r3, r0
    bne iplController_Classic_downTrg_L2
    li r4, 0
iplController_Classic_downTrg_L2:
    cmpwi r4, 0
    beq iplController_Classic_downTrg_L1
    li r31, 1
iplController_Classic_downTrg_L1:
    addi r11, r1, 0x20
    mr r3, r31
    bl _restgpr_29
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void upTrg__Q33ipl10controller7ClassicCFUl() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_29
    lwz r12, 0(r3)
    mr r29, r3
    mr r30, r4
    li r31, 0
    lwz r12, 0x6c(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq iplController_Classic_upTrg_L1
    lwz r5, 0x20(r29)
    clrlwi r0, r30, 16
    li r4, 1
    lwz r3, 8(r5)
    and. r0, r3, r0
    bne iplController_Classic_upTrg_L2
    lwz r3, 0x68(r5)
    srwi r0, r30, 16
    and. r0, r3, r0
    bne iplController_Classic_upTrg_L2
    li r4, 0
iplController_Classic_upTrg_L2:
    cmpwi r4, 0
    beq iplController_Classic_upTrg_L1
    li r31, 1
iplController_Classic_upTrg_L1:
    addi r11, r1, 0x20
    mr r3, r31
    bl _restgpr_29
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void downTrg__Q33ipl10controller10RevolutionCFUl() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_29
    lwz r12, 0(r3)
    mr r29, r3
    mr r30, r4
    li r31, 0
    lwz r12, 0x6c(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq iplController_Revolution_downTrg_L1
    lwz r3, 0x20(r29)
    clrlwi r0, r30, 16
    lwz r3, 4(r3)
    and. r0, r3, r0
    beq iplController_Revolution_downTrg_L1
    li r31, 1
iplController_Revolution_downTrg_L1:
    addi r11, r1, 0x20
    mr r3, r31
    bl _restgpr_29
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void upTrg__Q33ipl10controller10RevolutionCFUl() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_29
    lwz r12, 0(r3)
    mr r29, r3
    mr r30, r4
    li r31, 0
    lwz r12, 0x6c(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq iplController_Revolution_upTrg_L1
    lwz r3, 0x20(r29)
    clrlwi r0, r30, 16
    lwz r3, 8(r3)
    and. r0, r3, r0
    beq iplController_Revolution_upTrg_L1
    li r31, 1
iplController_Revolution_upTrg_L1:
    addi r11, r1, 0x20
    mr r3, r31
    bl _restgpr_29
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void decide__Q33ipl10controller6MasterCFv() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_27
    mr r27, r3
    li r29, 0
    li r28, 0
    li r31, 0
iplController_Master_decide_L1:
    lwz r3, 4(r27)
    li r30, 0
    lwzx r3, r3, r31
    cmpwi r3, 0
    beq iplController_Master_decide_L2
    lwz r12, 0(r3)
    lwz r12, 0x2c(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq iplController_Master_decide_L2
    li r30, 1
iplController_Master_decide_L2:
    addi r28, r28, 1
    or r3, r29, r30
    cmpwi r28, 4
    addi r31, r31, 4
    addic r0, r3, -1
    subfe r29, r0, r3
    blt iplController_Master_decide_L1
    addi r11, r1, 0x20
    mr r3, r29
    bl _restgpr_27
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void setForceInvalid__Q33ipl10controller6MasterFb() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_28
    mr r28, r3
    mr r29, r4
    li r30, 0
    li r31, 0
iplController_Master_setForceInvalid_L1:
    lwz r3, 4(r28)
    lwzx r3, r3, r31
    cmpwi r3, 0
    beq iplController_Master_setForceInvalid_L2
    lwz r12, 0(r3)
    mr r4, r29
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl
iplController_Master_setForceInvalid_L2:
    addi r30, r30, 1
    addi r31, r31, 4
    cmpwi r30, 4
    blt iplController_Master_setForceInvalid_L1
    addi r11, r1, 0x20
    bl _restgpr_28
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void __ct__Q33ipl10controller10RevolutionFiiR10KPADStatus() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_29
    lis r7, __vt__Q33ipl10controller4Base@ha
    li r31, 0
    addi r7, r7, __vt__Q33ipl10controller4Base@l
    li r0, -1
    stw r7, 0(r3)
    mr r29, r3
    mr r30, r6
    stb r31, 4(r3)
    stw r31, 8(r3)
    stw r31, 0xc(r3)
    stw r0, 0x10(r3)
    stw r4, 0x14(r3)
    stw r5, 0x18(r3)
    stb r31, 0x1c(r3)
    mr r3, r4
    bl KPADEnableDPD
    lis r3, __vt__Q33ipl10controller10Revolution@ha
    stb r31, 0x1d(r29)
    addi r3, r3, __vt__Q33ipl10controller10Revolution@l
    addi r11, r1, 0x20
    stw r3, 0(r29)
    mr r3, r29
    stb r31, 0x1e(r29)
    stw r30, 0x20(r29)
    bl _restgpr_29
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void call__Q33ipl10controller6MasterCFUlMQ33ipl10controller9InterfaceFPCvPCvUl_b() {
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    addi r11, r1, 0x30
    bl _savegpr_25
    mr r25, r3
    mr r26, r4
    mr r27, r5
    li r29, 0
    li r28, 0
    li r31, 0
iplController_Master_call_L1:
    lwz r3, 4(r25)
    li r30, 0
    lwzx r3, r3, r31
    cmpwi r3, 0
    beq iplController_Master_call_L2
    mr r4, r26
    mr r12, r27
    bl __ptmf_scall
    nop
    cmpwi r3, 0
    beq iplController_Master_call_L2
    li r30, 1
iplController_Master_call_L2:
    addi r28, r28, 1
    or r3, r29, r30
    cmpwi r28, 4
    addi r31, r31, 4
    subic r0, r3, 1
    subfe r29, r0, r3
    blt iplController_Master_call_L1
    addi r11, r1, 0x30
    mr r3, r29
    bl _restgpr_25
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

namespace ipl {
    namespace math {
        void VEC2::operator=(const VEC2& r) {
            x = r.x;
            y = r.y;
        }
    }

    namespace controller {
        void Base::read() {
            if (isValidBtn()) {
                if (downTrg(BTN_INTERACT)) {
                    mButton = 1;
                }
                if (pinch()) {
                    mButton = 0;
                }
                if (mButton != 0) {
                    if (down(BTN_INTERACT)) {
                        unk_0x08++;
                    } else {
                        unk_0x08 = 0;
                        mButton = 0;
                    }
                } else {
                    unk_0x08 = 0;
                }
            } else {
                mButton = 0;
                unk_0x08 = 0;
            }

            switch (mRumbleType) {
                case 0:
                case 1: {
                    u32 time = OSTicksToMilliseconds(OSGetTick() - mLastRumbleTime);
                    f32 f1 = (f32)time / 1000.0f;
                    if (f1 < 7.0f / 120.0f) {
                        WPADControlMotor(mChan, 1);
                    } else if (f1 < lbl_8160D2C0[mRumbleType]) {
                        WPADControlMotor(mChan, 0);
                    } else if (getKPADStatus() == NULL || getKPADStatus()->wpad_err == 0) {
                        mLastRumbleTime = 0;
                        mRumbleType = -1;
                        WPADControlMotor(mChan, 0);
                    }
                    if (downTrg(BTN_INTERACT) != 0 || decide() != 0) {
                        WPADControlMotor(mChan, 0);
                        mRumbleType = 2;
                    }
                    break;
                }
                case 2: {
                    u32 time = OSTicksToMilliseconds(OSGetTick() - mLastRumbleTime);
                    f32 f1 = (f32)time / 1000.0f;
                    if (f1 < lbl_8160D2C0[1]) {
                        WPADControlMotor(mChan, 0);
                    } else if (getKPADStatus() == NULL || getKPADStatus()->wpad_err == 0) {
                        mLastRumbleTime = 0;
                        mRumbleType = -1;
                        WPADControlMotor(mChan, 0);
                    }
                    break;
                }
            }
        }

        int Base::getType() const {
            return mType;
        }

        int Base::getChannel() const {
            return mChan;
        }

        bool Base::setForceInvalid(bool flag) {
            unk_0x1C = flag;
        }

        bool Interface::isValidBtn() const {
            return false;
        }

        bool Interface::downTrg(u32 mButton) const {
            return 0;
        }

        bool Interface::upTrg(u32 mButton) const {
            return 0;
        }

        int Interface::pinch() const {
            return 0;
        }

        int Interface::pinchTrg() const {
            return 0;
        }

        int Interface::pinchOffTrg() const {
            return 0;
        }

        bool Interface::down(u32 mButton) const {
            return 0;
        }

        bool Interface::repeat(u32 mButton) const {
            return 0;
        }

        bool Interface::isValidDpd() const {
            return false;
        }

        math::VEC2 Interface::getDpdPos() const {
            math::VEC2 ret;
            f32 zero = *((volatile const f32*)&lbl_81694454);
            ret.x = zero;
            ret.y = zero;
            return ret;
        }

        math::VEC2 Interface::getDpdProjectionPos() const {
            math::VEC2 ret;
            f32 zero = *((volatile const f32*)&lbl_81694454);
            ret.x = zero;
            ret.y = zero;
            return ret;
        }

        math::VEC2 Interface::getHorizon() const {
            math::VEC2 ret;
            f32 zero = *((volatile const f32*)&lbl_81694454);
            ret.x = zero;
            ret.y = zero;
            return ret;
        }

        int Interface::getClassicHoldFlag() const {
            return 0;
        }

        int Interface::getClassicTrigFlag() const {
            return 0;
        }

        int Interface::getClassicReleaseFlag() const {
            return 0;
        }

        KPADStatus* Interface::getKPADStatus() const {
            return NULL;
        }

        PADStatus* Interface::getPADStatus() const {
            return NULL;
        }

        f32 Interface::getDpdDistance() const {
            return *((volatile const f32*)&lbl_81694454);
        }

        int Interface::getHoldFlag() const {
            return 0;
        }

        int Interface::getReleaseFlag() const {
            return 0;
        }

        int Interface::getTrigFlag() const {
            return 0;
        }

        void Interface::cancelRumbling() {
        }

        int Interface::getChannel() const {
            return -1;
        }

        int Interface::getType() const {
            return -1;
        }

        bool Master::down(u32 button) const {
            return call(button, (bool (Interface::*)(u32) const)&Interface::down);
        }

        bool Master::downTrg(u32 button) const {
            return call(button, (bool (Interface::*)(u32) const)&Interface::downTrg);
        }

        bool Master::upTrg(u32 button) const {
            return call(button, (bool (Interface::*)(u32) const)&Interface::upTrg);
        }

        bool Master::repeat(u32 button) const {
            return call(button, (bool (Interface::*)(u32) const)&Interface::repeat);
        }

        BOOL Interface::rumble(int type) {
            return FALSE;
        }

        void Interface::read() {
        }

        EGG::Allocator* Manager::mpAllocator;

        void* Manager::alloc(u32 size) {
            return mpAllocator->alloc(size);
        }

        Interface* Manager::getMasterController() {
            return (Interface*)((u8*)this + 0xd0);
        }

        Interface* Manager::getController(int chan) {
            return ((Interface**)this)[chan];
        }

        int Manager::free(void* ptr) {
            mpAllocator->free(ptr);
            return TRUE;
        }

        extern "C" asm void __ct__Q33ipl10controller7ManagerFPQ23EGG4Heap() {
            nofralloc
            stwu r1, -0x20(r1)
            mflr r0
            stw r0, 0x24(r1)
            addi r11, r1, 0x20
            bl _savegpr_29
            lis r5, __vt__Q33ipl10controller6Master@ha
            mr r30, r4
            addi r5, r5, __vt__Q33ipl10controller6Master@l
            stw r3, 0xd4(r3)
            mr r29, r3
            li r4, 0
            stw r5, 0xd0(r3)
            li r5, 0x210
            addi r3, r3, 0xd8
            bl memset
            mr r3, r29
            li r4, 0
            li r5, 0x10
            bl memset
            bl WPADGetWorkMemorySize
            lwz r4, mpBuf__Q33ipl10controller7Manager
            addi r31, r3, 0x400
            cmpwi r4, 0
            beq manager_ctor_parent_done
            lwz r3, mpParentHeap__Q33ipl10controller7Manager
            cmpwi r3, 0
            beq manager_ctor_parent_done
            lwz r12, 0(r3)
            lwz r12, 0x18(r12)
            mtctr r12
            bctrl
        manager_ctor_parent_done:
            stw r30, mpParentHeap__Q33ipl10controller7Manager
            mr r3, r30
            mr r4, r31
            li r5, 0x20
            lwz r12, 0(r30)
            lwz r12, 0x14(r12)
            mtctr r12
            bctrl
            lwz r0, mpHeap__Q33ipl10controller7Manager
            stw r3, mpBuf__Q33ipl10controller7Manager
            cmpwi r0, 0
            beq manager_ctor_heap_done
            mr r3, r0
            lwz r12, 0(r3)
            lwz r12, 0x1c(r12)
            mtctr r12
            bctrl
        manager_ctor_heap_done:
            lwz r3, mpBuf__Q33ipl10controller7Manager
            mr r4, r31
            li r5, 2
            bl create__Q23EGG7ExpHeapFPvUlUs
            lwz r0, mpAllocator__Q33ipl10controller7Manager
            stw r3, mpHeap__Q33ipl10controller7Manager
            cmpwi r0, 0
            beq manager_ctor_allocator_done
            beq manager_ctor_allocator_done
            mr r3, r0
            li r4, 1
            lwz r12, 0x10(r3)
            lwz r12, 8(r12)
            mtctr r12
            bctrl
        manager_ctor_allocator_done:
            mr r4, r30
            li r3, 0x14
            li r5, 4
            bl __nw__FUlPQ23EGG4Heapi
            cmpwi r3, 0
            mr r0, r3
            beq manager_ctor_allocator_new_done
            lwz r4, mpHeap__Q33ipl10controller7Manager
            li r5, 4
            bl __ct__Q23EGG9AllocatorFPQ23EGG4Heapl
            mr r0, r3
        manager_ctor_allocator_new_done:
            lis r3, alloc__Q33ipl10controller7ManagerFUl@ha
            lis r4, free__Q33ipl10controller7ManagerFPv@ha
            stw r0, mpAllocator__Q33ipl10controller7Manager
            addi r3, r3, alloc__Q33ipl10controller7ManagerFUl@l
            addi r4, r4, free__Q33ipl10controller7ManagerFPv@l
            bl WPADRegisterAllocator
            bl KPADInit
            bl SCGetBtDpdSensibility
            mr r31, r3
            li r30, 0
        manager_ctor_repeat:
            clrlwi r3, r31, 24
            bl WPADSetDpdSensitivity
            lfs f1, lbl_81694478
            mr r3, r30
            lfs f2, lbl_8169447C
            bl KPADSetBtnRepeat
            addi r30, r30, 1
            cmpwi r30, 4
            blt manager_ctor_repeat
            mr r3, r29
            bl read__Q33ipl10controller7ManagerFv
            addi r11, r1, 0x20
            mr r3, r29
            bl _restgpr_29
            lwz r0, 0x24(r1)
            mtlr r0
            addi r1, r1, 0x20
            blr
        }

        Interface* Manager::getYoungController() {
            Interface* ret = NULL;
            for (int i = 0; i < 4; i++) {
                Interface* controller = ((Interface**)this)[i];
                if (controller != NULL) {
                    ret = controller;
                    break;
                }
            }
            return ret;
        }

        int Base::decide() const {
            return unk_0x08 == 5;
        }

        int Base::rumble(int type) {
            int ret = FALSE;
            if (WPADIsMotorEnabled() && mRumbleType == -1) {
                mLastRumbleTime = OSGetTick();
                ret = TRUE;
                mRumbleType = type;
            }

            return ret;
        }

        void Base::cancelRumbling() {
            if (mRumbleType != -1) {
                WPADControlMotor(mChan, 0);
            }
            mLastRumbleTime = 0;
            mRumbleType = -1;
        }

        extern "C" asm void read__Q33ipl10controller10RevolutionFv() {
            nofralloc
            stwu r1, -0x10(r1)
            mflr r0
            stw r0, 0x14(r1)
            stw r31, 0xc(r1)
            mr r31, r3
            lwz r12, 0(r3)
            lwz r12, 0x70(r12)
            mtctr r12
            bctrl
            cmpwi r3, 0
            bne revolution_read_dpd_done
            lfs f1, lbl_81694450
            lwz r3, 0x20(r31)
            lfs f0, lbl_81694454
            stfs f1, 0x24(r3)
            lwz r3, 0x20(r31)
            stfs f1, 0x20(r3)
            lwz r3, 0x20(r31)
            stfs f0, 0x30(r3)
            lwz r3, 0x20(r31)
            stfs f0, 0x2c(r3)
            lwz r3, 0x20(r31)
            stfs f0, 0x28(r3)
        revolution_read_dpd_done:
            lbz r0, 0x1d(r31)
            mr r3, r31
            stb r0, 0x1e(r31)
            lwz r12, 0(r31)
            lwz r12, 0x6c(r12)
            mtctr r12
            bctrl
            cmpwi r3, 0
            beq revolution_read_btn_invalid
            lbz r0, 0x1e(r31)
            cmpwi r0, 0
            bne revolution_read_btn_was_down
            lwz r12, 0(r31)
            mr r3, r31
            li r4, 0x800
            lwz r12, 0x14(r12)
            mtctr r12
            bctrl
            cmpwi r3, 0
            beq revolution_read_btn_end
            lwz r12, 0(r31)
            mr r3, r31
            li r4, 0x400
            lwz r12, 0x14(r12)
            mtctr r12
            bctrl
            cmpwi r3, 0
            beq revolution_read_btn_end
            li r0, 1
            stb r0, 0x1d(r31)
            b revolution_read_btn_end
        revolution_read_btn_was_down:
            lwz r12, 0(r31)
            mr r3, r31
            li r4, 0x800
            lwz r12, 0x14(r12)
            mtctr r12
            bctrl
            cmpwi r3, 0
            beq revolution_read_clear_btn
            lwz r12, 0(r31)
            mr r3, r31
            li r4, 0x400
            lwz r12, 0x14(r12)
            mtctr r12
            bctrl
            cmpwi r3, 0
            bne revolution_read_btn_end
        revolution_read_clear_btn:
            li r0, 0
            stb r0, 0x1d(r31)
            b revolution_read_btn_end
        revolution_read_btn_invalid:
            li r0, 0
            stb r0, 0x1d(r31)
        revolution_read_btn_end:
            mr r3, r31
            bl read__Q33ipl10controller4BaseFv
            lwz r0, 0x14(r1)
            lwz r31, 0xc(r1)
            mtlr r0
            addi r1, r1, 0x10
            blr
        }

        bool Revolution::isValidDpd() const {
            if (unk_0x1C != 0) {
                return false;
            }

            return (unk_0x20->wpad_err == 0 || unk_0x20->wpad_err == -7) && unk_0x20->dpd_valid_fg != 0;
        }

        bool Revolution::isValidBtn() const {
            u8 val = unk_0x20->wpad_err;

            return (u8)(val + 7) <= 7 && ((1 << (val + 7)) & 0xA1) != 0;
        }

        bool Revolution::down(u32 mButton) const {
            bool ret = false;
            if (isValidBtn()) {
                if (unk_0x20->hold & (mButton & 0xFFFF)) {
                    ret = true;
                }
            }

            return ret;
        }

        int Revolution::pinch() const {
            int ret = 0;
            if (isValidBtn() && unk_0x1D != 0) {
                ret = 1;
            }
            return ret;
        }

        int Revolution::pinchTrg() const {
            int ret = 0;
            if (isValidBtn() && unk_0x1D != 0 && unk_0x1E == 0) {
                ret = 1;
            }
            return ret;
        }

        int Revolution::pinchOffTrg() const {
            int ret = 0;
            if (isValidBtn() && unk_0x1D == 0 && unk_0x1E != 0) {
                ret = 1;
            }
            return ret;
        }

        f32 Revolution::getDpdDistance() const {
            return unk_0x20->dist;
        }

        KPADStatus* Revolution::getKPADStatus() const {
            return unk_0x20;
        }

        int Revolution::getReleaseFlag() const {
            return unk_0x20->release;
        }

        int Revolution::getTrigFlag() const {
            return unk_0x20->trig;
        }

        int Revolution::getHoldFlag() const {
            return unk_0x20->hold;
        }

        // non-matching
        math::VEC2 Revolution::getDpdProjectionPos() const {
            math::VEC2 ret;
            Vec2 dest;
            Vec2 src = {unk_0x20->pos.x, unk_0x20->pos.y};
            nw4r::ut::Rect nw4r_rect;  // constructor shouldn't be inlined
            Rect kpad_rect;

            System::getProjectionRect(&nw4r_rect);

            kpad_rect.left = nw4r_rect.left;
            kpad_rect.top = nw4r_rect.top;
            kpad_rect.right = nw4r_rect.right;
            kpad_rect.bottom = nw4r_rect.bottom;

            KPADGetProjectionPos(&dest, &src, &kpad_rect, 1.10132f);
            if (SCGetAspectRatio() == 1) {
                dest.x *= 1.15f;
                dest.y *= 1.15f;
            }

            // regswap
            if (nw4r_rect.left - 100.0f > dest.x) {
                dest.x = nw4r_rect.left;
            } else if (nw4r_rect.right + 100.0f < dest.x) {
                dest.x = nw4r_rect.right;
            } else if (nw4r_rect.top - 100.0f > dest.y) {
                dest.y = nw4r_rect.top;
            } else if (nw4r_rect.bottom + 100.0f < dest.y) {
                dest.y = nw4r_rect.bottom;
            }
            // //

            ret.set(dest.x, dest.y);  // shouldn't be inlined

            return ret;
        }

        Classic::Classic(int arg0, KPADStatus& arg1) : Revolution(arg0, arg1) {
            unk_0x24.x = 0.01f;
            unk_0x24.y = 0.01f;
            unk_0x2C = 0;
        }

        Base::~Base() {
        }

        Master::~Master() {
        }

        Revolution::~Revolution() {
        }

        void Classic::read() {
            if (!Revolution::isValidDpd()) {
                math::VEC2 lstick(unk_0x20->ex_status.cl.lstick.x, unk_0x20->ex_status.cl.lstick.y);

                if (lstick.x * lstick.x + lstick.y * lstick.y > 0.0036f) {
                    unk_0x24.x = math::abs_clamp(unk_0x24.x + unk_0x20->ex_status.cl.lstick.x * 0.05f, 1.8f);
                    unk_0x24.y = math::abs_clamp(unk_0x24.y - unk_0x20->ex_status.cl.lstick.y * 0.05f, 1.2f);
                }

                math::VEC2 rstick = math::VEC2(unk_0x20->ex_status.cl.rstick.x, unk_0x20->ex_status.cl.rstick.y);
                if (getClassicHoldFlag() != 0 || lstick.x * lstick.x + lstick.y * lstick.y > 0.0036f ||
                    rstick.x * rstick.x + rstick.y * rstick.y > 0.0036f) {
                    unk_0x2C = 180;
                }

                if (--unk_0x2C < 0) {
                    unk_0x2C = 0;
                }
            } else {
                unk_0x24.y = 0.01f;
                unk_0x24.x = 0.01f;
                unk_0x2C = 0;
            }

            Revolution::read();
        }

        bool Classic::isValidDpd() const {
            if (unk_0x1C != 0) {
              return false;
            }

            return (Revolution::isValidDpd() != 0) || (unk_0x2C != 0);
        }

        BOOL Classic::isValidDpdClassic() const {
            return unk_0x2C != 0;
        }

        int Classic::getClassicHoldFlag() const {
            return unk_0x20->ex_status.cl.hold;
        }

        int Classic::getClassicTrigFlag() const {
            return unk_0x20->ex_status.cl.trig;
        }

        int Classic::getClassicReleaseFlag() const {
            return unk_0x20->ex_status.cl.release;
        }

        math::VEC2 Classic::getHorizon() const {
            math::VEC2 ret;
            if (Revolution::isValidDpd()) {
                ret.set(unk_0x20->horizon.x, unk_0x20->horizon.y);
            } else {
                ret.x = 1.0f;
                ret.y = -0.2679492f;
            }
            return ret;
        }

        math::VEC2 Classic::getDpdPos() const {
            math::VEC2 ret;
            if (Revolution::isValidDpd()) {
                ret.set(unk_0x20->pos.x, unk_0x20->pos.y);
            } else if (unk_0x2C != 0) {
                ret = unk_0x24;
            } else {
                ret.x = 1.0f / 0.0f;
                ret.y = 1.0f / 0.0f;
            }
            return ret;
        }

        extern "C" asm void getDpdProjectionPos__Q33ipl10controller7ClassicCFv() {
            nofralloc
            stwu r1, -0x50(r1)
            mflr r0
            stw r0, 0x54(r1)
            stw r31, 0x4c(r1)
            mr r31, r3
            bl isValidDpd__Q33ipl10controller10RevolutionCFv
            cmpwi r3, 0
            beq classic_projection_check_stick
            lwz r4, 0x20(r31)
            addi r3, r1, 0x18
            lfs f1, 0x20(r4)
            lfs f2, 0x24(r4)
            bl set__Q33ipl4math4VEC2Fff
            b classic_projection_have_src
        classic_projection_check_stick:
            lwz r0, 0x2c(r31)
            cmpwi r0, 0
            beq classic_projection_invalid
            addi r3, r1, 0x18
            addi r4, r31, 0x24
            bl __as__Q33ipl4math4VEC2FRCQ33ipl4math4VEC2
            b classic_projection_have_src
        classic_projection_invalid:
            lfs f0, lbl_81694450
            stfs f0, 0x18(r1)
            stfs f0, 0x1c(r1)
        classic_projection_have_src:
            lfs f1, 0x18(r1)
            addi r3, r1, 0x30
            lfs f0, 0x1c(r1)
            stfs f1, 0x8(r1)
            stfs f0, 0xc(r1)
            bl __ct__Q34nw4r2ut4RectFv
            addi r3, r1, 0x30
            bl getProjectionRect__Q23ipl6SystemFPQ34nw4r2ut4Rect
            lfs f1, 0x30(r1)
            addi r3, r1, 0x10
            lfs f3, 0x34(r1)
            addi r4, r1, 0x8
            lfs f2, 0x38(r1)
            addi r5, r1, 0x20
            lfs f0, 0x3c(r1)
            stfs f1, 0x20(r1)
            lfs f1, lbl_81694458
            stfs f3, 0x24(r1)
            stfs f2, 0x28(r1)
            stfs f0, 0x2c(r1)
            bl KPADGetProjectionPos
            bl SCGetAspectRatio
            clrlwi r0, r3, 24
            cmplwi r0, 1
            bne classic_projection_no_aspect
            lfs f1, 0x10(r1)
            lfs f2, lbl_8169445C
            lfs f0, 0x14(r1)
            fmuls f1, f1, f2
            fmuls f0, f0, f2
            stfs f1, 0x10(r1)
            stfs f0, 0x14(r1)
        classic_projection_no_aspect:
            lfs f0, 0x30(r1)
            lfs f2, lbl_81694460
            lfs f1, 0x10(r1)
            fsubs f0, f0, f2
            fcmpo cr0, f0, f1
            ble classic_projection_right
            stfs f0, 0x10(r1)
            b classic_projection_done
        classic_projection_right:
            lfs f0, 0x38(r1)
            fadds f0, f2, f0
            fcmpo cr0, f0, f1
            bge classic_projection_top
            stfs f0, 0x10(r1)
            b classic_projection_done
        classic_projection_top:
            lfs f0, 0x34(r1)
            lfs f1, 0x14(r1)
            fsubs f0, f0, f2
            fcmpo cr0, f0, f1
            ble classic_projection_bottom
            stfs f0, 0x14(r1)
            b classic_projection_done
        classic_projection_bottom:
            lfs f0, 0x3c(r1)
            fadds f0, f2, f0
            fcmpo cr0, f0, f1
            bge classic_projection_done
            stfs f0, 0x14(r1)
        classic_projection_done:
            lfs f1, 0x10(r1)
            addi r3, r1, 0x18
            lfs f2, 0x14(r1)
            bl set__Q33ipl4math4VEC2Fff
            lwz r31, 0x4c(r1)
            lwz r0, 0x54(r1)
            lwz r3, 0x18(r1)
            lwz r4, 0x1c(r1)
            mtlr r0
            addi r1, r1, 0x50
            blr
        }
    }  // namespace controller
}  // namespace ipl
