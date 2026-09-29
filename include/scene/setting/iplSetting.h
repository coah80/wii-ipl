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
            u8 unk_0x5C[0x24];
            int mProfileIDMode;
            u8 unk_0x84[0xC];
            int mFuncMsgPending;
            u8 unk_0x94[0x38];
            SettingAnimation* mpFirstAnimation;
            SettingAnimation* mpSecondAnimation;
            u8 unk_0xD4[0xC];
            void* mpResource1;
            void* mpResource2;
            u8 unk_0xE8[0x840];
            APEvent* mpAPEvent;
            u8 unk_0x92C[0x230];
            u8 mIsResetAcceptable;
            u8 unk_0xB5D[3];
            OSMessageQueue mFuncMessageQueue;
            u8 unk_0xB80[0x18];
            int mState;
            u8 unk_0xB9C[0x24];
#else
            u8 unk_0x58[0xB68];
#endif

        };
    }  // namespace scene
}  // namespace ipl

#endif  // IPL_SCENE_SETTING_H
