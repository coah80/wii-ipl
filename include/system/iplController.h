#ifndef IPL_CONTROLLER_H
#define IPL_CONTROLLER_H

#include <decomp.h>

#include <revolution.h>
#include <revolution/kpad.h>
#include <revolution/pad.h>
#include <revolution/wpad.h>

#include <egg/core.h>

#include "iplMath.h"
#include "math/iplMathTypes.h"
#include "revolution/os/OSTime.h"

namespace ipl {
    namespace controller {
#define __iplWpadCl(btn) ((btn) << 16)

        // clang-format off
        /* Revolution Controller (Wii Remote) */
        enum {
            REVO_BTN_UP     = WPAD_BUTTON_UP,
            REVO_BTN_DOWN   = WPAD_BUTTON_DOWN,
            REVO_BTN_LEFT   = WPAD_BUTTON_LEFT,
            REVO_BTN_RIGHT  = WPAD_BUTTON_RIGHT,
            REVO_BTN_A      = WPAD_BUTTON_A,
            REVO_BTN_B      = WPAD_BUTTON_B,
            REVO_BTN_PLUS   = WPAD_BUTTON_PLUS,
            REVO_BTN_MINUS  = WPAD_BUTTON_MINUS,
            REVO_BTN_HOME   = WPAD_BUTTON_HOME,
            REVO_BTN_1      = WPAD_BUTTON_1,
            REVO_BTN_2      = WPAD_BUTTON_2,
        };
        /* Classic Controller */
        enum {
            CL_BTN_PAD_UP       = __iplWpadCl(WPAD_BUTTON_CL_UP),
            CL_BTN_PAD_DOWN     = __iplWpadCl(WPAD_BUTTON_CL_DOWN),
            CL_BTN_PAD_LEFT     = __iplWpadCl(WPAD_BUTTON_CL_LEFT),
            CL_BTN_PAD_RIGHT    = __iplWpadCl(WPAD_BUTTON_CL_RIGHT),
            CL_BTN_A            = __iplWpadCl(WPAD_BUTTON_CL_A),
            CL_BTN_B            = __iplWpadCl(WPAD_BUTTON_CL_B),
            CL_BTN_PLUS         = __iplWpadCl(WPAD_BUTTON_CL_PLUS),
            CL_BTN_MINUS        = __iplWpadCl(WPAD_BUTTON_CL_MINUS),
            CL_BTN_L            = __iplWpadCl(WPAD_BUTTON_CL_FULL_R),
            CL_BTN_R            = __iplWpadCl(WPAD_BUTTON_CL_FULL_L),
            CL_BTN_HOME         = __iplWpadCl(WPAD_BUTTON_CL_HOME),
        };
        /* Common button inputs */
        enum {
            BTN_UP          = REVO_BTN_UP       | CL_BTN_PAD_UP,                /* 0x00010008 */
            BTN_DOWN        = REVO_BTN_DOWN     | CL_BTN_PAD_DOWN,              /* 0x40000004 */
            BTN_LEFT        = REVO_BTN_LEFT     | CL_BTN_PAD_LEFT,              /* 0x00020001 */
            BTN_RIGHT       = REVO_BTN_RIGHT    | CL_BTN_PAD_RIGHT,             /* 0x80000002 */
            BTN_INTERACT    = REVO_BTN_A        | CL_BTN_A,                     /* 0x00100800 */
            BTN_BACK        = REVO_BTN_B        | CL_BTN_B,                     /* 0x00400400 */
            BTN_DRAG        = REVO_BTN_A        | REVO_BTN_B,                   /* 0x00000C00 */
            BTN_NEXT_RIGHT  = REVO_BTN_PLUS     | CL_BTN_PLUS       | CL_BTN_L, /* 0x06000010 */
            BTN_NEXT_LEFT   = REVO_BTN_MINUS    | CL_BTN_MINUS      | CL_BTN_R, /* 0x30001000 */
            BTN_HOME        = REVO_BTN_HOME     | CL_BTN_HOME,                  /* 0x08008000 */
        };
        // clang-format on

#ifdef IPL_CONTROLLER_NATIVE_HIERARCHY
#ifdef IPL_CONTROLLER_OUT_OF_LINE_INTERFACE
#define IPL_CONTROLLER_DEFAULT_VIRTUAL(signature, implementation) virtual signature;
#else
#ifdef IPL_CONTROLLER_INLINE_INTERFACE
#define IPL_CONTROLLER_DEFAULT_VIRTUAL(signature, implementation) virtual signature implementation
#else
#define IPL_CONTROLLER_DEFAULT_VIRTUAL(signature, implementation) virtual signature;
#endif
#endif
        class Interface {
        public:
            virtual ~Interface() = 0;
            IPL_CONTROLLER_DEFAULT_VIRTUAL(int getType() const, { return -1; })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(int getChannel() const, { return -1; })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(bool down(u32 button) const, { return false; })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(bool downTrg(u32 button) const, { return false; })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(bool upTrg(u32 button) const, { return false; })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(int pinch() const, { return 0; })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(int pinchTrg() const, { return 0; })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(int pinchOffTrg() const, { return 0; })
            virtual int decide() const = 0;
            IPL_CONTROLLER_DEFAULT_VIRTUAL(bool repeat(u32 button) const, { return false; })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(BOOL rumble(int type = 0), { return FALSE; })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(void cancelRumbling(), {  })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(int getHoldFlag() const, { return 0; })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(int getTrigFlag() const, { return 0; })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(int getReleaseFlag() const, { return 0; })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(int getClassicHoldFlag() const, { return 0; })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(int getClassicTrigFlag() const, { return 0; })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(int getClassicReleaseFlag() const, { return 0; })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(math::VEC2 getDpdPos() const, { return math::VEC2(0.0f, 0.0f); })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(math::VEC2 getDpdProjectionPos() const, { return math::VEC2(0.0f, 0.0f); })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(math::VEC2 getHorizon() const, { return math::VEC2(0.0f, 0.0f); })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(f32 getDpdDistance() const, { return 0.0f; })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(KPADStatus* getKPADStatus() const, { return NULL; })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(PADStatus* getPADStatus() const, { return NULL; })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(bool isValidBtn() const, { return false; })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(bool isValidDpd() const, { return false; })
            virtual void setForceInvalid(bool flag) = 0;
            IPL_CONTROLLER_DEFAULT_VIRTUAL(int getMainStickX() const, { return 0; })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(int getMainStickY() const, { return 0; })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(int getSubStickX() const, { return 0; })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(int getSubStickY() const, { return 0; })
            IPL_CONTROLLER_DEFAULT_VIRTUAL(void read(), {  })
        };

#undef IPL_CONTROLLER_DEFAULT_VIRTUAL
#ifdef IPL_CONTROLLER_INLINE_INTERFACE
        inline Interface::~Interface() {}
#endif

        class Base : public Interface {
        public:
            Base(int chan, KPADStatus& status) {
                mButton = 0;
                mDecideHoldCount = 0;
                mLastRumbleTime = 0;
                mRumbleType = -1;
                mChan = chan;
                mType = 2;
                mbForceInvalid = 0;
                KPADEnableDPD(chan);
                mbPinch = 0;
                mbPrevPinch = 0;
                mpStatus = &status;
            }

            Base(int chan, int type, KPADStatus& status) {
                mButton = 0;
                mDecideHoldCount = 0;
                mLastRumbleTime = 0;
                mRumbleType = -1;
                mChan = chan;
                mType = type;
                mbForceInvalid = 0;
                KPADEnableDPD(chan);
            }

            virtual ~Base();
            virtual int getType() const override;
            virtual int getChannel() const override;
            virtual int decide() const override;
            virtual BOOL rumble(int timer = 0) override;
            virtual void cancelRumbling() override;
            virtual void setForceInvalid(bool flag) override;
            virtual void read() override;

        protected:
            u8 mButton;
            u32 mDecideHoldCount;
            OSTick mLastRumbleTime;
            s32 mRumbleType;
            u32 mChan;
            u32 mType;
            u8 mbForceInvalid;
            u8 mbPinch;
            u8 mbPrevPinch;
            KPADStatus* mpStatus;
        };

        class Revolution : public Base {
        public:
            Revolution(int chan, KPADStatus& status) : Base(chan, status) {}
            Revolution(int chan, int type, KPADStatus& status);
            virtual ~Revolution();
            virtual bool down(u32 button) const override;
            virtual bool downTrg(u32 button) const override;
            virtual bool upTrg(u32 button) const override;
            virtual int pinch() const override;
            virtual int pinchTrg() const override;
            virtual int pinchOffTrg() const override;
            virtual bool repeat(u32 button) const override;
            virtual f32 getDpdDistance() const override;
            virtual KPADStatus* getKPADStatus() const override;
            virtual int getReleaseFlag() const override;
            virtual int getTrigFlag() const override;
            virtual int getHoldFlag() const override;
            virtual math::VEC2 getDpdPos() const override;
            virtual math::VEC2 getDpdProjectionPos() const override;
            virtual math::VEC2 getHorizon() const override;
            virtual bool isValidBtn() const override;
            virtual bool isValidDpd() const override;
            virtual void read() override;
        };

        class Classic : public Revolution {
        public:
            Classic(int chan, KPADStatus& status);
            virtual ~Classic();
            virtual bool down(u32 button) const override;
            virtual bool downTrg(u32 button) const override;
            virtual bool upTrg(u32 button) const override;
            virtual int getClassicHoldFlag() const override;
            virtual int getClassicTrigFlag() const override;
            virtual int getClassicReleaseFlag() const override;
            virtual math::VEC2 getDpdPos() const override;
            virtual math::VEC2 getDpdProjectionPos() const override;
            virtual math::VEC2 getHorizon() const override;
            virtual bool isValidDpd() const override;
            virtual void read() override;
            virtual BOOL isValidDpdClassic() const;

        private:
            math::VEC2 mClassicCursor;
            int mClassicCursorTimer;
        };

        class Master : public Interface {
        public:
            Master(Interface** controllers) : mpControllers(controllers) {}
            virtual ~Master();
            virtual bool down(u32 button) const override;
            virtual bool downTrg(u32 button) const override;
            virtual bool upTrg(u32 button) const override;
            virtual bool repeat(u32 button) const override;
            virtual int decide() const override;
            virtual void setForceInvalid(bool flag) override;

        private:
            bool call(u32 button, bool (Interface::*func)(u32) const) const;
            Interface** mpControllers;
        };

        class Core : public Revolution {
        public:
            Core(int chan, int type, KPADStatus& status) : Revolution(chan, type, status) {}
            virtual ~Core();
        };

        class FreeStyle : public Revolution {
        public:
            FreeStyle(int chan, int type, KPADStatus& status) : Revolution(chan, type, status) {}
            virtual ~FreeStyle();
        };

        class Manager {
        public:
            Manager(EGG::Heap* heap);
            void read();
            Interface* getController(int chan);
            Interface* getMasterController();
            Interface* getYoungController();
            static void* alloc(u32 size);
            static int free(void* ptr);

        private:
            static void* mpBuf;
            static EGG::Heap* mpParentHeap;
            static EGG::ExpHeap* mpHeap;
            static EGG::Allocator* mpAllocator;
            Interface* mControllers[4];
            u32 mControllerStorage[4][12];
            Master mMaster;
            KPADStatus mKPADStatus[4];
            s32 mInvalidCount[4];
        };
#else
        class Base {
        public:
            Base(int chan, KPADStatus& arg1) {
                mButton = 0;
                mDecideHoldCount = 0;
                mLastRumbleTime = 0;
                mRumbleType = -1;
                mChan = chan;
                mType = 2;
                mbForceInvalid = 0;

                KPADEnableDPD(chan);

                mbPinch = 0;
                mbPrevPinch = 0;
                mpStatus = &arg1;
            }

            virtual ~Base();                            // 0x08
            virtual int getType() const;                // 0x0C
            virtual int getChannel() const;             // 0x10
            virtual bool down(u32 button) const;        // 0x14
            virtual bool downTrg(u32 button) const;     // 0x18
            virtual bool upTrg(u32 button) const;       // 0x1C
            virtual int pinch() const;                  // 0x20
            virtual int pinchTrg() const;               // 0x24
            virtual int pinchOffTrg() const;            // 0x28
            virtual int decide() const;                 // 0x2C
            virtual bool repeat(u32 button) const;      // 0x30
            virtual BOOL rumble(int timer = 0);         // 0x34
            virtual void cancelRumbling();              // 0x38
            virtual int getHoldFlag() const;            // 0x3C
            virtual int getTrigFlag() const;            // 0x40
            virtual int getReleaseFlag() const;         // 0x44
            virtual int getClassicHoldFlag() const;     // 0x48
            virtual int getClassicTrigFlag() const;     // 0x4C
            virtual int getClassicReleaseFlag() const;  // 0x50
            virtual math::VEC2 getDpdPos() const;       // 0x54
            /**
             * @brief Gets the IR sensor position of the Wii Remote.
             * @return The IR sensor X and Y as `ipl::math::VEC2`.
             */
            virtual math::VEC2 getDpdProjectionPos() const;  // 0x58
            /**
             * @brief Gets the Horizon of the Wii Remote.
             * @return The Horizon X and Y as `ipl::math::VEC2`.
             */
            virtual math::VEC2 getHorizon() const;      // 0x5C
            virtual f32 getDpdDistance() const;         // 0x60
            virtual KPADStatus* getKPADStatus() const;  // 0x64
            virtual PADStatus* getPADStatus() const;    // 0x68
            virtual bool isValidBtn() const;            // 0x6C
            virtual bool isValidDpd() const;            // 0x70

            virtual bool setForceInvalid(bool flag);  // 0x74

            virtual int getMainStickX() const;  // 0x78
            virtual int getMainStickY() const;  // 0x7C

            virtual int getSubStickX() const;  // 0x80
            virtual int getSubStickY() const;  // 0x84

            virtual void read();  // 0x88

            // protected:
            u8 mButton;              // 0x4
            u32 mDecideHoldCount;            // 0x8
            OSTick mLastRumbleTime;  // 0xC
            s32 mRumbleType;         // 0x10
            u32 mChan;               // 0x14
            u32 mType;               // 0x18
            u8 mbForceInvalid;
            u8 mbPinch;           // 0x1D
            u8 mbPrevPinch;           // 0x1E
            KPADStatus* mpStatus;  // 0x20
        };

        class Interface : public Base {
        public:
            Interface(int chan, KPADStatus& arg1) : Base(chan, arg1) {}

            ~Interface() {}

            virtual bool down(u32 button) const override;        // 0x10
            virtual bool downTrg(u32 button) const override;     // 0x18
            virtual bool upTrg(u32 button) const override;
            virtual int pinch() const override;                  // 0x1C
            virtual int pinchTrg() const override;
            virtual int pinchOffTrg() const override;
            virtual bool repeat(u32 button) const override;
            virtual int getClassicHoldFlag() const override;     // 0x48
            virtual int getClassicTrigFlag() const override;     // 0x4C
            virtual int getClassicReleaseFlag() const override;  // 0x50
            virtual KPADStatus* getKPADStatus() const override;  // 0x64
            virtual PADStatus* getPADStatus() const override;    // 0x68
            virtual f32 getDpdDistance() const override;         // 0x60
            virtual bool isValidBtn() const override;            // 0x6C
            virtual int getReleaseFlag() const override;
            virtual int getHoldFlag() const override;
            virtual int getTrigFlag() const override;
            virtual void cancelRumbling() override;
            virtual int getChannel() const override;
            virtual int getType() const override;
            virtual bool isValidDpd() const override;
            virtual math::VEC2 getDpdPos() const override;
            virtual math::VEC2 getDpdProjectionPos() const override;
            virtual math::VEC2 getHorizon() const override;
            virtual int getMainStickX() const override;
            virtual int getMainStickY() const override;
            virtual int getSubStickX() const override;
            virtual int getSubStickY() const override;
            virtual BOOL rumble(int type = 0) override;
            virtual void read() override;
        };

        class Master {
        public:
            virtual ~Master();
            virtual bool down(u32 button) const;
            virtual bool downTrg(u32 button) const;
            virtual bool upTrg(u32 button) const;
            virtual bool repeat(u32 button) const;
            virtual int decide() const;
            virtual void setForceInvalid(bool flag);

        private:
            bool call(u32 button, bool (Interface::*func)(u32) const) const;
            Interface** mpControllers;
        };

        class Revolution : public Interface {
        public:
            Revolution(int chan, KPADStatus& arg1) : Interface(chan, arg1) {}
            Revolution(int chan, int type, KPADStatus& arg1);

            virtual ~Revolution();

            virtual bool down(u32 button) const override;  // 0x10
            virtual bool downTrg(u32 button) const override;
            virtual bool upTrg(u32 button) const override;
            virtual int pinch() const override;
            virtual int pinchTrg() const override;
            virtual int pinchOffTrg() const override;
            virtual bool repeat(u32 button) const override;

            virtual f32 getDpdDistance() const override;  // 0x60

            virtual KPADStatus* getKPADStatus() const override;  // 0x64

            virtual int getReleaseFlag() const override;
            virtual int getTrigFlag() const override;
            virtual int getHoldFlag() const override;

            virtual math::VEC2 getDpdPos() const override;
            virtual math::VEC2 getDpdProjectionPos() const override;  // 0x58
            virtual math::VEC2 getHorizon() const override;

            virtual bool isValidBtn() const override;  // 0x6C
            virtual bool isValidDpd() const override;  // 0x70

            virtual void read() override;  // 0x88
        };

        class Classic : public Revolution {
        public:
            Classic(int arg0, KPADStatus& arg1);
            virtual ~Classic();

            virtual bool down(u32 button) const override;
            virtual bool downTrg(u32 button) const override;
            virtual bool upTrg(u32 button) const override;
            virtual int getClassicHoldFlag() const override;     // 0x48
            virtual int getClassicTrigFlag() const override;     // 0x4C
            virtual int getClassicReleaseFlag() const override;  // 0x50

            virtual math::VEC2 getDpdPos() const override;            // 0x54
            virtual math::VEC2 getDpdProjectionPos() const override;  // 0x58
            virtual math::VEC2 getHorizon() const override;           // 0x5C

            virtual bool isValidDpd() const override; // 0x70

            virtual void read() override;  // 0x88

            virtual BOOL isValidDpdClassic() const;  // 0x8C

        private:
            math::VEC2 mClassicCursor;
            int mClassicCursorTimer;
        };

        class Manager {
        public:
            Manager(EGG::Heap* heap);

            void read();

            Interface* getController(int chan);
            Interface* getMasterController();
            Interface* getYoungController();

            static void* alloc(u32 size);
            static int free(void* ptr);

        private:
            static EGG::Allocator* mpAllocator;
            u8 dummy[0x2F8];
        };
#endif
    }  // namespace controller
}  // namespace ipl

#endif  // IPL_CONTROLLER_H
