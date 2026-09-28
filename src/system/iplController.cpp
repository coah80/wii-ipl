#include <decomp/ide.h>
#define IPL_CONTROLLER_OUT_OF_LINE_VEC2
#define IPL_CONTROLLER_OUT_OF_LINE_ABS_CLAMP
#include <math/iplMathTypes.h>
#undef IPL_CONTROLLER_OUT_OF_LINE_ABS_CLAMP
#undef IPL_CONTROLLER_OUT_OF_LINE_VEC2
#define IPL_CONTROLLER_TRIVIAL_RECT_DTOR
#define IPL_SOUND_RECT_OUT_OF_LINE
#include <nw4r/ut/Rect.h>
#undef IPL_SOUND_RECT_OUT_OF_LINE
#undef IPL_CONTROLLER_TRIVIAL_RECT_DTOR
#include <revolution/kpad.h>
#include <revolution/mtx/GeoTypes.h>
#include <revolution/os.h>
#include <revolution/os/OSTime.h>
#include <revolution/sc.h>
#include <revolution/wpad.h>

#define IPL_CONTROLLER_NATIVE_HIERARCHY
#define IPL_CONTROLLER_INLINE_INTERFACE
#define IPL_CONTROLLER_OUT_OF_LINE_INTERFACE
#include "system/iplController.h"
#undef IPL_CONTROLLER_OUT_OF_LINE_INTERFACE
#undef IPL_CONTROLLER_INLINE_INTERFACE
#undef IPL_CONTROLLER_NATIVE_HIERARCHY
#include "system/iplSystem.h"

namespace ipl {
    namespace controller {
        static const f32 kRumbleDuration[4] = {0.2f, 0.3f, 0.0f, 0.0f};
        typedef bool (Interface::*ButtonMember)(u32) const;
        static ButtonMember kDownMember = &Interface::down;
        static ButtonMember kDownTrgMember = &Interface::downTrg;
        static ButtonMember kUpTrgMember = &Interface::upTrg;
        static ButtonMember kRepeatMember = &Interface::repeat;
    }
}

        void ipl::controller::Base::read() {
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
                    if (f1 < 0.058333333f) {
                        WPADControlMotor(mChan, 1);
                    } else if (f1 < kRumbleDuration[mRumbleType]) {
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
                    if (f1 < kRumbleDuration[1]) {
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
        bool ipl::controller::Interface::isValidBtn() const {
            return false;
        }
        bool ipl::controller::Interface::downTrg(u32 button) const {
            return false;
        }
        int ipl::controller::Interface::pinch() const {
            return 0;
        }
        bool ipl::controller::Interface::down(u32 button) const {
            return false;
        }
        KPADStatus* ipl::controller::Interface::getKPADStatus() const {
            return NULL;
        }
        int ipl::controller::Base::decide() const {
            return unk_0x08 == 5;
        }
        int ipl::controller::Base::rumble(int type) {
            int ret = FALSE;
            if (WPADIsMotorEnabled() && mRumbleType == -1) {
                mLastRumbleTime = OSGetTick();
                ret = TRUE;
                mRumbleType = type;
            }

            return ret;
        }
        void ipl::controller::Base::cancelRumbling() {
            if (mRumbleType != -1) {
                WPADControlMotor(mChan, 0);
            }
            mLastRumbleTime = 0;
            mRumbleType = -1;
        }
        void ipl::controller::Revolution::read() {
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
                    if (down(0x800) && down(0x400)) {
                        unk_0x1D = 1;
                    }
                } else if (!down(0x800) || !down(0x400)) {
                    unk_0x1D = 0;
                }
            } else {
                unk_0x1D = 0;
            }

            Base::read();
        }
        bool ipl::controller::Revolution::isValidDpd() const {
            if (unk_0x1C != 0) {
                return false;
            }

            return (unk_0x20->wpad_err == 0 || unk_0x20->wpad_err == -7) && unk_0x20->dpd_valid_fg != 0;
        }
        bool ipl::controller::Revolution::isValidBtn() const {
            u8 val = unk_0x20->wpad_err;

            return (u8)(val + 7) <= 7 && ((1 << (val + 7)) & 0xA1) != 0;
        }
        bool ipl::controller::Revolution::down(u32 mButton) const {
            bool ret = false;
            if (isValidBtn()) {
                if (unk_0x20->hold & (mButton & 0xFFFF)) {
                    ret = true;
                }
            }

            return ret;
        }
        ipl::math::VEC2 ipl::controller::Revolution::getDpdProjectionPos() const {
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

            KPADGetProjectionPos(&dest, &src, &kpad_rect, 1.10132003f);
            if (SCGetAspectRatio() == 1) {
                dest.x *= 1.15f;
                dest.y *= 1.15f;
            }

            // regswap
            if (nw4r_rect.left - 100.0f > dest.x) {
                dest.x = nw4r_rect.left - 100.0f;
            } else if (nw4r_rect.right + 100.0f < dest.x) {
                dest.x = nw4r_rect.right + 100.0f;
            } else if (nw4r_rect.top - 100.0f > dest.y) {
                dest.y = nw4r_rect.top - 100.0f;
            } else if (nw4r_rect.bottom + 100.0f < dest.y) {
                dest.y = nw4r_rect.bottom + 100.0f;
            }
            // //

            ret.set(dest.x, dest.y);  // shouldn't be inlined

            return ret;
        }
        nw4r::ut::Rect::Rect() : left(0.0f), top(0.0f), right(0.0f), bottom(0.0f) {}
        void ipl::math::VEC2::set(f32 fx, f32 fy) {
            x = fx;
            y = fy;
        }
        ipl::controller::Classic::Classic(int arg0, KPADStatus& arg1) : Revolution(arg0, arg1) {
            unk_0x24.x = 0.01f;
            unk_0x24.y = 0.01f;
            unk_0x2C = 0;
        }
        ipl::controller::Base::~Base() {
        }
        ipl::controller::Revolution::~Revolution() {
        }
        ipl::math::VEC2::VEC2(f32 fx, f32 fy) {
            x = fx;
            y = fy;
        }
        void ipl::controller::Classic::read() {
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
        int ipl::controller::Classic::getClassicHoldFlag() const {
            return unk_0x20->ex_status.cl.hold;
        }
        template <>
        f32 ipl::math::abs_clamp<f32>(const f32& x, const f32& y) {
            if (x > y) {
                return y;
            } else if (x < -y) {
                return -y;
            } else {
                return x;
            }
        }
        ipl::math::VEC2 ipl::controller::Classic::getHorizon() const {
            math::VEC2 ret;
            if (Revolution::isValidDpd()) {
                ret.set(unk_0x20->horizon.x, unk_0x20->horizon.y);
            } else {
                ret.x = 1.0f;
                ret.y = -0.2679492f;
            }
            return ret;
        }
        ipl::math::VEC2 ipl::controller::Classic::getDpdPos() const {
            math::VEC2 ret;
            if (Revolution::isValidDpd()) {
                ret.set(unk_0x20->pos.x, unk_0x20->pos.y);
            } else if (unk_0x2C != 0) {
                ret = unk_0x24;
            } else {
                ret.x = (1.0f / 0.0f);
                ret.y = (1.0f / 0.0f);
            }
            return ret;
        }
        void ipl::math::VEC2::operator=(const ipl::math::VEC2& r) {
            x = r.x;
            y = r.y;
        }
        ipl::math::VEC2 ipl::controller::Classic::getDpdProjectionPos() const {
            math::VEC2 ret;
            if (Revolution::isValidDpd()) {
                ret.set(unk_0x20->pos.x, unk_0x20->pos.y);
            } else if (unk_0x2C != 0) {
                ret = unk_0x24;
            } else {
                ret.set(1.0f / 0.0f, 1.0f / 0.0f);
            }

            Vec2 dest;
            Vec2 src;
            src.x = ret.x;
            src.y = ret.y;
            nw4r::ut::Rect nw4r_rect;
            System::getProjectionRect(&nw4r_rect);
            Rect rect;
            rect.left = nw4r_rect.left;
            rect.top = nw4r_rect.top;
            rect.right = nw4r_rect.right;
            rect.bottom = nw4r_rect.bottom;
            KPADGetProjectionPos(&dest, &src, &rect, 1.10132003f);
            if (SCGetAspectRatio() == 1) {
                dest.x *= 1.15f;
                dest.y *= 1.15f;
            }

            if (nw4r_rect.left - 100.0f > dest.x) {
                dest.x = nw4r_rect.left - 100.0f;
            } else if (nw4r_rect.right + 100.0f < dest.x) {
                dest.x = nw4r_rect.right + 100.0f;
            } else if (nw4r_rect.top - 100.0f > dest.y) {
                dest.y = nw4r_rect.top - 100.0f;
            } else if (nw4r_rect.bottom + 100.0f < dest.y) {
                dest.y = nw4r_rect.bottom + 100.0f;
            }

            ret.set(dest.x, dest.y);
            return ret;
        }
        bool ipl::controller::Master::down(u32 button) const {
            return call(button, kDownMember);
        }
        bool ipl::controller::Master::downTrg(u32 button) const {
            return call(button, kDownTrgMember);
        }
        bool ipl::controller::Master::upTrg(u32 button) const {
            return call(button, kUpTrgMember);
        }
        bool ipl::controller::Interface::upTrg(u32 button) const {
            return false;
        }
        bool ipl::controller::Master::repeat(u32 button) const {
            return call(button, kRepeatMember);
        }
        bool ipl::controller::Interface::repeat(u32 button) const {
            return false;
        }
        int ipl::controller::Master::decide() const {
            bool current = false;
            bool ret = false;
            for (int i = 0; i < 4; i++) {
                current = false;
                Interface* controller = mpControllers[i];
                if (controller != NULL) {
                    if (controller->decide() != 0) {
                        current = true;
                    }
                }
                ret = ret | current;
            }
            return ret;
        }
void ipl::controller::Master::setForceInvalid(bool flag) {
    for (int i = 0; i < 4; i++) {
        if (mpControllers[i] != NULL) {
            mpControllers[i]->setForceInvalid(flag);
        }
    }
}
        bool ipl::controller::Master::call(u32 button, bool (Interface::*func)(u32) const) const {
            bool current = false;
            bool ret = false;
            for (int i = 0; i < 4; i++) {
                current = false;
                Interface* controller = mpControllers[i];
                if (controller != NULL) {
                    if ((controller->*func)(button)) {
                        current = true;
                    }
                }
                ret = ret | current;
            }
            return ret;
        }
        void ipl::controller::Interface::read() {}
        int ipl::controller::Interface::getSubStickY() const {
            return 0;
        }
        int ipl::controller::Interface::getSubStickX() const {
            return 0;
        }
        int ipl::controller::Interface::getMainStickY() const {
            return 0;
        }
        int ipl::controller::Interface::getMainStickX() const {
            return 0;
        }
        bool ipl::controller::Interface::isValidDpd() const {
            return false;
        }
        PADStatus* ipl::controller::Interface::getPADStatus() const {
            return NULL;
        }
        f32 ipl::controller::Interface::getDpdDistance() const {
            return 0.0f;
        }
        ipl::math::VEC2 ipl::controller::Interface::getHorizon() const {
            return ipl::math::VEC2(0.0f, 0.0f);
        }
        ipl::math::VEC2 ipl::controller::Interface::getDpdProjectionPos() const {
            return ipl::math::VEC2(0.0f, 0.0f);
        }
        ipl::math::VEC2 ipl::controller::Interface::getDpdPos() const {
            return ipl::math::VEC2(0.0f, 0.0f);
        }
        int ipl::controller::Interface::getClassicReleaseFlag() const {
            return 0;
        }
        int ipl::controller::Interface::getClassicTrigFlag() const {
            return 0;
        }
        int ipl::controller::Interface::getClassicHoldFlag() const {
            return 0;
        }
        int ipl::controller::Interface::getReleaseFlag() const {
            return 0;
        }
        int ipl::controller::Interface::getTrigFlag() const {
            return 0;
        }
        int ipl::controller::Interface::getHoldFlag() const {
            return 0;
        }
        void ipl::controller::Interface::cancelRumbling() {}
        BOOL ipl::controller::Interface::rumble(int type) {
            return FALSE;
        }
        int ipl::controller::Interface::pinchOffTrg() const {
            return 0;
        }
        int ipl::controller::Interface::pinchTrg() const {
            return 0;
        }
        int ipl::controller::Interface::getChannel() const {
            return -1;
        }
        int ipl::controller::Interface::getType() const {
            return -1;
        }
        void ipl::controller::Base::setForceInvalid(bool flag) {
            unk_0x1C = flag;
        }
        int ipl::controller::Base::getType() const {
            return mType;
        }
        int ipl::controller::Base::getChannel() const {
            return mChan;
        }
        KPADStatus* ipl::controller::Revolution::getKPADStatus() const {
            return unk_0x20;
        }
        f32 ipl::controller::Revolution::getDpdDistance() const {
            return unk_0x20->dist;
        }
        int ipl::controller::Revolution::getReleaseFlag() const {
            return unk_0x20->release;
        }
        int ipl::controller::Revolution::getTrigFlag() const {
            return unk_0x20->trig;
        }
        int ipl::controller::Revolution::getHoldFlag() const {
            return unk_0x20->hold;
        }
        int ipl::controller::Revolution::pinchOffTrg() const {
            int ret = 0;
            if (isValidBtn() && unk_0x1D == 0 && unk_0x1E != 0) {
                ret = 1;
            }
            return ret;
        }
        int ipl::controller::Revolution::pinch() const {
            int ret = 0;
            if (isValidBtn() && unk_0x1D != 0) {
                ret = 1;
            }
            return ret;
        }
        int ipl::controller::Revolution::pinchTrg() const {
            int ret = 0;
            if (isValidBtn() && unk_0x1D != 0 && unk_0x1E == 0) {
                ret = 1;
            }
            return ret;
        }
        bool ipl::controller::Revolution::repeat(u32 button) const {
            return down(button) && (unk_0x20->hold & 0x80000000) != 0;
        }
        BOOL ipl::controller::Classic::isValidDpdClassic() const {
            return unk_0x2C != 0;
        }
        bool ipl::controller::Classic::isValidDpd() const {
            if (unk_0x1C != 0) {
              return false;
            }

            return (Revolution::isValidDpd() != 0) || (unk_0x2C != 0);
        }
        int ipl::controller::Classic::getClassicReleaseFlag() const {
            return unk_0x20->ex_status.cl.release;
        }
        int ipl::controller::Classic::getClassicTrigFlag() const {
            return unk_0x20->ex_status.cl.trig;
        }
        bool ipl::controller::Classic::upTrg(u32 button) const {
            bool ret = false;
            if (isValidBtn()) {
                bool pressed = true;
                KPADStatus* status = unk_0x20;
                if ((status->release & (button & 0xFFFF)) == 0) {
                    if ((status->ex_status.cl.release & (button >> 16)) == 0) {
                        pressed = false;
                    }
                }
                if (pressed) {
                    ret = true;
                }
            }
            return ret;
        }
        bool ipl::controller::Classic::downTrg(u32 button) const {
            bool ret = false;
            if (isValidBtn()) {
                bool pressed = true;
                KPADStatus* status = unk_0x20;
                if ((status->trig & (button & 0xFFFF)) == 0) {
                    if ((status->ex_status.cl.trig & (button >> 16)) == 0) {
                        pressed = false;
                    }
                }
                if (pressed) {
                    ret = true;
                }
            }
            return ret;
        }
        bool ipl::controller::Classic::down(u32 button) const {
            bool ret = false;
            if (isValidBtn()) {
                bool pressed = true;
                if ((unk_0x20->hold & (button & 0xFFFF)) == 0) {
                    if ((unk_0x20->ex_status.cl.hold & (button >> 16)) == 0) {
                        pressed = false;
                    }
                }
                if (pressed) {
                    ret = true;
                }
            }
            return ret;
        }
        ipl::math::VEC2 ipl::controller::Revolution::getHorizon() const {
            return math::VEC2(unk_0x20->horizon.x, unk_0x20->horizon.y);
        }
        ipl::math::VEC2 ipl::controller::Revolution::getDpdPos() const {
            return math::VEC2(unk_0x20->pos.x, unk_0x20->pos.y);
        }
        bool ipl::controller::Revolution::upTrg(u32 button) const {
            bool ret = false;
            if (isValidBtn()) {
                if (unk_0x20->release & (button & 0xFFFF)) {
                    ret = true;
                }
            }
            return ret;
        }
        bool ipl::controller::Revolution::downTrg(u32 button) const {
            bool ret = false;
            if (isValidBtn()) {
                if (unk_0x20->trig & (button & 0xFFFF)) {
                    ret = true;
                }
            }
            return ret;
        }
        ipl::controller::Classic::~Classic() {}
        ipl::controller::Master::~Master() {
        }
