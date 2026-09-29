#ifndef IPL_SCENE_SETTING_H
#define IPL_SCENE_SETTING_H

#include "iplSceneHeader.h"

#ifdef IPL_SETTING_IMPLEMENTATION
#include <revolution/os.h>
#include "layout/iplGuiManager.h"
#include "layout/GUIManager.h"
#include "iplwww/www_wiisetting.h"
#include "iplwww/www_browser.h"
#include "system/iplKeyboard.h"
#include "system/iplNand.h"
#include "utility/iplThread.h"
#endif

namespace ipl {
    namespace controller {
        class Interface;
    }
}

namespace ipl {
    namespace scene {
#ifdef IPL_SETTING_IMPLEMENTATION
        class Setting;
        class APScanThread;

        class APEvent : public ::gui::EventHandler {
        public:
            APEvent(Setting* setting) : ::gui::EventHandler(), mpSetting(setting) {}

            virtual void onEvent(u32 componentID, u32 event, void* data);

            void setEventType(u8 eventType) { reinterpret_cast<u8&>(mpManager) = eventType; }
            u8 getEventType() const { return reinterpret_cast<const u8&>(mpManager); }

        private:
            Setting* mpSetting;
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
            void createBrowser();
            void initDirectUrl();
            void initString();
            void initWiiSettingData();
            void initNickName();
            void initSecurityKey();
            void initSSID();
            void initIP();
            void initDNS();
            void initProxy();
            void initBasic();
            void initMTU();
            void initSecA();
            void initVersion();
            void updateController_();
            void setSE();
            void changeVideoMode();
            bool isInitialSequenceExit(const ::ipl::controller::Interface* input);
            bool updateScreenMode();
            void initHTMLText();
            void initMessage();
            void initKeyboard(const char* text);
            void calcKeyboard();
            void calcSetting();
            bool calcSafeMode();
            void waitStart();
            void waitFinish();
            bool isWaitPlaying();
            void initAP();
            void resetAP();
            void redrawAP();
            void scanAP();
            void setNUP();
            void setUSBAP();
            void cancelUSBAP();
            void AOSSProcess();
            void RakuProcess();
            void setUpdate_();
            void setUseEULA_();
            void start_point_event(const char* pageName);
            void start_trig_event(const char* pageName);
            void start_left_event(const char* pageName);
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
            nand::Base* mpWWWLibraryFile;
            nand::Base* mpSettingHTMLFile;
            nand::Base* mpWWWArchiveFile;
            nand::Base* mpFontFile;
            nand::Base* mpBackgroundTPLFile;
            int unk_0x74;
            int unk_0x78;
            int unk_0x7C;
            int mProfileIDMode;
            int unk_0x84;
            u8 unk_0x88[8];
            int mFuncMsgPending;
            int unk_0x94;
            ESTitleId mUpdateTitleId;
            u32 mPrepareTick;
            u8 mSettingData[0x16];
            u8 unk_0xBA[2];
            nand::LayoutFile* mpSettingLayoutFile;
            layout::Object* mpChangeLayout;
            layout::Object* mpMainLayout;
            layout::Object* mpWaitLayout;
            SettingAnimation* mpFirstAnimation;
            SettingAnimation* mpSecondAnimation;
            APEvent* mpEventHandler;
            gui::PaneManager* mpPaneManager;
            void* mpUSBAPThread;
            utility::ut_thread* mpAOSSThread;
            utility::ut_thread* mpRakuRakuThread;
            APScanThread* mpAPScanThread;
            u8 unk_0xEC[0x818];
            void* mpMem1BrowserBuffer;
            u32 unk_0x908;
            void* mpMem2BrowserBuffer;
            void* mpBrowserStringBuffer;
            int unk_0x914;
            int unk_0x918;
            u8 unk_0x91C[4];
            ext_ead::www::ImeData* mpBrowserData;
            www::wiisetting::WiiData* mpWiiSettingData;
            APEvent* mpAPEvent;
            u8 unk_0x92C;
            u8 unk_0x92D[3];
            int unk_0x930;
            www::wiisetting::SetStringBuf* mpStringBuffer;
            u8 unk_0x938[0x202];
            u8 unk_0xB3A;
            u8 mBrowserCreated;
            keyboard::Manager::State mKeyboardState;
            int mInitialArgument;
            int mAspectRatio;
            int mProgressiveMode;
            int mEuRgb60Mode;
            u8 mIsResetAcceptable;
            u8 unk_0xB5D[3];
            OSMessageQueue mFuncMessageQueue;
            OSMessage mFuncMessages[5];
            int unk_0xB94;
            int mState;
            int unk_0xB9C;
            OSTime mCreatePageTime;
            u32 unk_0xBA8;
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
