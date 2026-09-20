#include <decomp/ide.h>
#include <math/iplMathTypes.h>
#include <nw4r/ut/Rect.h>
#include <revolution/kpad.h>
#include <revolution/mtx/GeoTypes.h>
#include <revolution/os.h>
#include <revolution/os/OSTime.h>
#include <revolution/sc.h>
#include <revolution/wpad.h>

#include "system/iplController.h"
#include "system/iplSystem.h"

const f32 lbl_8160D2C0[] = {0.2, 0.3, 0, 0};
extern const f32 lbl_81694454 = 0.0f;
extern "C" void _savegpr_25();
extern "C" void _restgpr_25();
extern "C" void __ptmf_scall();

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

        void Revolution::read() {
            if (!isValidDpd()) {
                unk_0x20->pos.y = 1.0f / 0.0f;
                unk_0x20->pos.x = 1.0f / 0.0f;
                unk_0x20->speed = 0.0f;
                unk_0x20->vec.y = 0.0f;
                unk_0x20->vec.x = 0.0f;
            }
            unk_0x1E = unk_0x1D;

            if (isValidBtn()) {
                if (unk_0x1E == 0) {
                    if (down(REVO_BTN_A) && down(REVO_BTN_B)) {
                        unk_0x1D = 1;
                    }
                } else if (!down(REVO_BTN_A) || !down(REVO_BTN_B)) {
                    unk_0x1D = 0;
                }
            } else {
                unk_0x1D = 0;
            }

            Interface::read();
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
    }  // namespace controller
}  // namespace ipl
