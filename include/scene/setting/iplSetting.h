#ifndef IPL_SCENE_SETTING_H
#define IPL_SCENE_SETTING_H

#include "iplSceneHeader.h"

#ifdef IPL_SETTING_IMPLEMENTATION
#include <revolution/os.h>
#endif

namespace ipl {
    namespace scene {
#ifdef IPL_SETTING_IMPLEMENTATION
        class APEvent {
        public:
            u8 unknown[4];
            u8 eventType;
        };

        struct SettingAnimation {
            u8 unknown[0x14];
            int state;
        };
#endif

        FADER_SCENE_CLASS(Setting) {
        public:
            Setting(EGG::Heap * heap, int arg);
#ifdef IPL_SETTING_IMPLEMENTATION
            virtual ~Setting();

            bool isAnimating();
            void getFuncMsgQ();
            void resetFuncMsgQ();
            int get_arw_no(const char* paneName);
            int get_ap_no(const char* buttonName);
            virtual void destroy();
            virtual void prepare();
            virtual void create();
            virtual void calc();
            virtual void draw();
            virtual FaderSceneCommand calcFadein();
            virtual FaderSceneCommand calcNormal();
            virtual FaderSceneCommand calcFadeout();
            virtual BOOL isResetAcceptable() const;
#endif

            u16 getProfileID();
            void setInitializeResult(bool, int);
            void setConnectTestResult(int, int, bool, int);
            int getUpdateTiming();

            enum {
                ARG_NORMAL_PAGE = 0,
                ARG_INTERNET_SETTING,
                ARG_SETUP,
                ARG_UPDATE,
                ARG_INTERNET_PAGE,
                ARG_UNK_5,
                ARG_UNK_6,
            };

        private:
#ifdef IPL_SETTING_IMPLEMENTATION
            int mUpdateTiming;
            u8 unk_0x5C;
            u8 unk_0x5D[3];
            int unk_0x60;
            int unk_0x64;
            int unk_0x68;
            int unk_0x6C;
            u8 unk_0x70[4];
            int unk_0x74;
            int unk_0x78;
            int unk_0x7C;
            int mProfileIDMode;
            int unk_0x84;
            u8 unk_0x88[8];
            int mFuncMsgPending;
            int unk_0x94;
            u8 unk_0x98[0x24];
            int unk_0xBC;
            u8 unk_0xC0[0xC];
            SettingAnimation* mpFirstAnimation;
            SettingAnimation* mpSecondAnimation;
            u8 unk_0xD4[0xC];
            void* mpResource1;
            void* mpResource2;
            u8 unk_0xE8[0x82C];
            int unk_0x914;
            int unk_0x918;
            u8 unk_0x91C[4];
            u8 unk_0x920[8];
            APEvent* mpAPEvent;
            u8 unk_0x92C;
            u8 unk_0x92D[3];
            int unk_0x930;
            u8 unk_0x934[0x207];
            u8 unk_0xB3B;
            u8 unk_0xB3C[0x10];
            int mInitialArgument;
            int mAspectRatio;
            int mProgressiveMode;
            int mEuRgb60Mode;
            u8 mIsResetAcceptable;
            u8 unk_0xB5D[3];
            OSMessageQueue mFuncMessageQueue;
            u8 unk_0xB80[0x14];
            int unk_0xB94;
            int mState;
            int unk_0xB9C;
            u8 unk_0xBA0[0xC];
            u8 unk_0xBAC;
            u8 unk_0xBAD[3];
            u8 unk_0xBB0[0x10];
            static void* mem1Buffer_;
            static void* mem2Buffer_;
#else
            u8 unk_0x58[0xB68];
#endif

        };
    }  // namespace scene
}  // namespace ipl

#endif  // IPL_SCENE_SETTING_H
