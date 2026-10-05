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
extern "C" {
#include <revolution/wd.h>
}
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

#ifdef IPL_SETTING_IMPLEMENTATION
        class APEvent;
#else
        class APEvent : public ::gui::EventHandler {
        public:
            APEvent(Setting* setting) : ::gui::EventHandler(), mpSetting(setting) {}

            virtual void onEvent(u32 componentID, u32 event, void* data);

        private:
            Setting* mpSetting;
        };
#endif

        struct SettingAPScanList {
            u8 reservedHeader[0x14];
            union {
                struct {
                    u16 count;
                    u8 entries[0x7fe];
                };
                u8 recordBuffer[0x800];
            };
            union {
                WDBssDesc_* currentDescriptor;
                u16* currentDescriptorWords;
            };
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
            bool checkInputString(const wchar_t* text) NO_INLINE;
            int checkIPString(const wchar_t* text);
            void setDefaultBackString();
            void calcKeyboard();
            void calcSetting();
            void onTextInputOK();
            void setDisPos();
            void setNickName();
            void setSecurityKey();
            void setSSID();
            void setIP();
            void setDNS();
            void setProxy();
            void setBasic();
            void setMTU();
            void setParePass();
            void setPareRePass();
            void setPareJudgePass();
            void setSecA();
            void setReSecA();
            void setMasterKey();
            void adjustSecA(wchar_t* text);
            void reAdjustSecA();
            u8 checkTextNum(const char* text);
            bool checkSpace();
            void convertIP(char* destination, const u8* address);
            void convertRevIP(u8* destination, const char* address);
            void initScroll();
            void updateScroll();
            void setAPDraw();
            int getRadioLevel(const WDBssDesc_* descriptor);
            void setUseEULA_Init_();
            void setUseEULA_Cancel_();
            void setUseEULA_Start_();
            void setUseEULA_WaitStopMotor_();
            bool validateEULA_();
            void setUpdate_Init_();
            void setUpdate_WaitAcceptDialog_();
            void setUpdate_ConnectTestStart_();
            void setUpdate_ConnectTestCreateWait_();
            void setUpdate_ConnectTestRun_();
            void setUpdate_ConnectTestFailed_();
            void setUpdate_SuccessDialog_();
            void setUpdate_NoUpdateDialog_();
            void setUpdate_EULAInit_();
            void setUpdate_Reboot_();
            void makeErrorMessage();
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
            void makeSupportCode();
            int getErrorNum();
            virtual void destroy();
            virtual void prepare();
            virtual void create();
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
                ARG_RESUME_SETUP,
                ARG_DIRECT_PAGE,
            };

        private:
#ifdef IPL_SETTING_IMPLEMENTATION
            int mUpdateTiming;
            u8 mBrowserStopRequested;
            u8 reservedAfterBrowserStop[3];
            nand::Base* mpWWWLibraryFile;
            nand::Base* mpSettingHTMLFile;
            nand::Base* mpWWWArchiveFile;
            nand::Base* mpFontFile;
            nand::Base* mpBackgroundTPLFile;
            int mDialogState;
            int mAPScanState;
            int mEULAState;
            int mProfileIDMode;
            int mUSBAPState;
            int mAOSSState;
            int mRakuState;
            int mFuncMsgPending;
            int mSafeModeDialogState;
            ESTitleId mUpdateTitleId;
            u32 mPrepareTick;
            u8 mSettingData[0x16];
            u8 reservedAfterSettingData[2];
            nand::LayoutFile* mpSettingLayoutFile;
            layout::Object* mpChangeLayout;
            layout::Object* mpMainLayout;
            layout::Object* mpWaitLayout;
            utility::FrameController* mpFirstAnimation;
            utility::FrameController* mpSecondAnimation;
            APEvent* mpEventHandler;
            gui::PaneManager* mpPaneManager;
            void* mpUSBAPThread;
            utility::ut_thread* mpAOSSThread;
            utility::ut_thread* mpRakuRakuThread;
            APScanThread* mpAPScanThread;
            SettingAPScanList mAPScanList;
            void* mpMem1BrowserBuffer;
            u32 reservedBrowserWord;
            void* mpMem2BrowserBuffer;
            void* mpBrowserStringBuffer;
            int mAPScrollOffset;
            int mAPAnimationIndex;
            u8 mUiStatus[4];
            ext_ead::www::ImeData* mpBrowserData;
            www::wiisetting::WiiData* mpWiiSettingData;
            www::wiisetting::WiiFlag* mpWiiSettingFlag;
            u8 mActionFrame;
            u8 reservedAfterActionFrame[3];
            int mSupportCode;
            www::wiisetting::SetStringBuf* mpStringBuffer;
#ifdef IPL_SETTING_IMPLEMENTATION
            wchar_t mInputText[0x101];
#else
            u8 mInputText[0x202];
#endif
            u8 reservedAfterInputText;
            u8 mBrowserCreated;
            keyboard::Manager::State mKeyboardState;
            int mInitialArgument;
            int mAspectRatio;
            int mProgressiveMode;
            int mEuRgb60Mode;
            u8 mIsResetAcceptable;
            u8 reservedAfterResetFlag[3];
            OSMessageQueue mFuncMessageQueue;
            OSMessage mFuncMessages[5];
            int mScreenModeChangeState;
            int mState;
            int mInputDelayFrame;
            OSTime mCreatePageTime;
            u32 mConnectedControllerMask;
            u8 mNetSettingResultSent;
            u8 reservedAfterNetSettingResult[3];
            u8 reservedTail[0x10];
            static void* mem1Buffer_;
            static void* mem2Buffer_;
#else
            u8 mSettingStorage[0xB68];
#endif

        };
#ifdef IPL_SETTING_IMPLEMENTATION
        class APEvent : public ::gui::EventHandler {
        public:
            APEvent(Setting* setting) : ::gui::EventHandler(), mpSetting(setting) {}

            virtual void onEvent(u32 componentID, u32 event, void* data);

        private:
            Setting* mpSetting;
        };
#endif
    }  // namespace scene
}  // namespace ipl

#endif  // IPL_SCENE_SETTING_H
