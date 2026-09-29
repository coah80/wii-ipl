#define IPL_SETTING_IMPLEMENTATION
#include "scene/setting/iplSetting.h"
#include "scene/setting/iplAPScanThread.h"

#include "scene/setting/iplNCDSetting.h"
#include "scene/setting/iplParental.h"
#include "scene/nakamuraTest/iplNakamuraTest.h"
#include "scene/parentalDialog/iplParentalDialog.h"
#include "system/iplErrorHandler.h"
#include "system/iplSystem.h"
#include "utility/iplWpad.h"
#include "utility/iplCharacterCode.h"
#include "sound/iplSound.h"
#include "utility/iplESMisc.h"

#include "iplwww/www_wiisetting.h"
#include "iplwww/www_surface.h"
#include "iplwww/www_trasition.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <new>
#include <revolution/sc.h>
#include <revolution/tpl.h>
#include <revolution/vi.h>
#include <revolution/wpad.h>
#include <private/os/OSExec.h>
#include <private/os/OSSram.h>
#include <private/wpad/WPADInternal.h>

extern "C" void __VISetAdjustingValues(s32 horizontal, s32 vertical);

namespace ipl {
    class SensitivityDrawing {
    public:
        static void draw(nand::File* file);
    };
}

namespace ipl {
    namespace keyboard {
        Manager::State& Manager::State::operator=(const Manager::State& other) {
            type = other.type;
            iplType = other.iplType;
            pressOK = other.pressOK;
            reservedByte = other.reservedByte;
            wcString = other.wcString;
            return *this;
        }
    }
}

namespace ipl {
    namespace scene {
        class USBAPThread {
        public:
            USBAPThread();
            bool is();
            void setData(const wchar_t* nickname, u8* result);
            void Init(unsigned short* profile, u8* result);
            void cancel();

        private:
            wchar_t mNickname[10];
        };

        class AOSSThread : public utility::ut_thread {
        public:
            AOSSThread(EGG::Heap* heap);
            virtual ~AOSSThread();
            virtual void* Run();
            int start();
            int finish(NCDAossConfig* config, int* result);
            void cancel();

        private:
            int mResult;
            int mPriority;
            void* mpThreadStack;
            void* mpHeapArea;
            void* mpExpandedHeap;
            u8 mStartParameters[0x26c];
        };

        class RakuRakuThread : public utility::ut_thread {
        public:
            RakuRakuThread(EGG::Heap* heap);
            virtual ~RakuRakuThread();
            virtual void* Run();
            int getState();
            int start();
            int finish(NCDApConfig* config, int* result);
            void cancel();

        private:
            int mResult;
            int mState;
            void* mpMessageQueue;
            u32 mFlags;
            void* mpHeapArea;
            void* mpThreadStack;
            int mMessage;
        };

        struct SettingAnimationBinding {
            u16 animation;
            u16 pane;
        };

        struct SettingSecAText {
            wchar_t firstLine[16];
            wchar_t wrappedLine[17];
        };

        static const SettingAnimationBinding sSettingAnimationBindings[] = {
            {0, 2},  {0, 3},  {1, 2},  {1, 3},  {2, 2},  {2, 3},  {3, 2},  {3, 3},  {4, 2},  {4, 3},
            {5, 0},  {6, 0},  {7, 8},  {7, 9},  {7, 10}, {7, 11}, {8, 8},  {8, 9},  {8, 10}, {8, 11},
            {9, 1},  {10, 1}, {11, 14}, {11, 15}, {11, 16}, {11, 17}, {11, 18}, {11, 19}, {12, 14}, {12, 15},
            {12, 16}, {12, 17}, {12, 18}, {12, 19}, {13, 14}, {13, 15}, {13, 16}, {13, 17}, {13, 18}, {13, 19},
            {14, 14}, {14, 15}, {14, 16}, {14, 17}, {14, 18}, {14, 19}, {15, 20}, {15, 21}, {15, 22}, {15, 23},
            {15, 24}, {15, 25}, {16, 20}, {16, 21}, {16, 22}, {16, 23}, {16, 24}, {16, 25},
        };

        const char* sSettingAPButtonNames[] = {"B_AP2", "B_AP3", "B_AP4", "B_AP5"};

        const char* sSettingArrowNames[] = {"B_ArwA", "B_ArwB"};

        const char* sSettingAPTextNames[] = {"T_Name1", "T_Name2", "T_Name3", "T_Name4", "T_Name5", "T_Name6"};

        const char* sSettingAPNumberNames[] = {"N_AP1", "N_AP2", "N_AP3", "N_AP4", "N_AP5", "N_AP6"};

        const char* sSettingAPPaneNames[] = {
            "G_ListUpDown", "G_ListInOut", "G_ArwA", "G_ArwB", "G_Denpa", "G_Lock",  "G_AP0",
            "G_AP1",        "G_AP2",       "G_AP3",  "G_AP4",  "G_AP5",   "G_AP6",   "G_AP7",
            "G_Denpa1",     "G_Denpa2",    "G_Denpa3", "G_Denpa4", "G_Denpa5", "G_Denpa6",
            "G_Lock1",      "G_Lock2",     "G_Lock3", "G_Lock4", "G_Lock5", "G_Lock6",
        };

        const char* sSettingAPAnimations[] = {
            "my_AP_a_ArwAppear.brlan", "my_AP_a_ArwLost.brlan", "my_AP_a_ArwFocusOn.brlan",
            "my_AP_a_ArwFocusOff.brlan", "my_AP_a_ArwSelect.brlan", "my_AP_a_ScrollUp.brlan",
            "my_AP_a_ScrollDown.brlan", "my_AP_a_BtnFocusOn.brlan", "my_AP_a_BtnFocusOff.brlan",
            "my_AP_a_ListAppear.brlan", "my_AP_a_ListLost.brlan", "my_AP_a_Denpa0.brlan",
            "my_AP_a_Denpa1.brlan", "my_AP_a_Denpa2.brlan", "my_AP_a_Denpa3.brlan",
            "my_AP_a_LockOff.brlan", "my_AP_a_LockOn.brlan",
        };

        NCDAossConfig m_AOSSConfig;
        NCDRakuApConfig m_RakuConfig;

        void* Setting::mem1Buffer_;
        void* Setting::mem2Buffer_;

        Setting::Setting(EGG::Heap* heap, int arg) : FaderSceneBase(heap) {
            unk_0x5C = 0;
            mpWWWLibraryFile = 0;
            mpSettingHTMLFile = 0;
            mpWWWArchiveFile = 0;
            mpFontFile = 0;
            mpSettingLayoutFile = 0;
            mBrowserCreated = 0;
            setSceneParentFlags(3);
            unk_0x74 = 0;
            mInitialArgument = arg;
            unk_0x78 = 1;
            unk_0x84 = 1;
            mProfileIDMode = 0;
            mUpdateTiming = 0;
            unk_0x914 = 0;
            unk_0x918 = -1;
            unk_0x91C[0] = 0;
            unk_0x91C[1] = 0;
            unk_0x91C[2] = 0;
            unk_0x91C[3] = 0;
            unk_0x7C = 0;
            unk_0xB9C = 0;
            unk_0x92C = 0;
            unk_0x930 = 0;
            mIsResetAcceptable = 1;
            mFuncMsgPending = 0;
            mAspectRatio = SCGetAspectRatio();
            mProgressiveMode = SCGetProgressiveMode();
            mEuRgb60Mode = SCGetEuRgb60Mode();
            unk_0xB94 = 0;
            unk_0xBAC = 0;
            unk_0x94 = 0;
        }

        bool Setting::isAnimating() {
            return mpSecondAnimation->state == 1 || mpFirstAnimation->state == 1 || mState != 20;
        }

        void Setting::getFuncMsgQ() {
            OSMessage message = 0;
            if (mFuncMsgPending == 0 && OSReceiveMessage(&mFuncMessageQueue, &message, 0)) {
                mFuncMsgPending = 1;
                mpWiiSettingFlag->smthMsgData = (u8)message;
            }
        }

        void Setting::resetFuncMsgQ() {
            mpWiiSettingFlag->smthMsgData = 0;
            mFuncMsgPending = 0;
        }

        Setting::~Setting() {
            OSReport("***Destruct!!\n");
            if (mem1Buffer_) {
                System::createMem1AppHeap()->free(mem1Buffer_);
                mem1Buffer_ = 0;
            }
            if (mem2Buffer_) {
                System::getMem2App()->free(mem2Buffer_);
                mem2Buffer_ = 0;
            }
            if (mpWWWLibraryFile) {
                delete mpWWWLibraryFile;
            }
            if (mpSettingHTMLFile) {
                delete mpSettingHTMLFile;
            }
            if (mpWWWArchiveFile) {
                delete mpWWWArchiveFile;
            }
            if (mpFontFile) {
                delete mpFontFile;
            }
            if (mpBackgroundTPLFile) {
                delete mpBackgroundTPLFile;
            }
            System::destroyMem1AppHeap();
            System::getBS2Manager()->restart();
            OSReport(" ... bs2 manager restarted\n");
        }

        void Setting::destroy() {
            delete mpAOSSThread;
            delete mpRakuRakuThread;
        }

        void Setting::prepare() {
            System::getBS2Manager()->abort();
            while (System::getBS2Manager()->getIPLState() != 8) {
                System::getBS2Manager()->update();
                VIWaitForRetrace();
            }

            System::getUsbEtherMacAddr();
            mPrepareTick = OSGetTick();
            mpWWWLibraryFile = System::getNandManager()->readSharedAsync(
                System::createMem1AppHeap(), "wwwlib-rvl.lz7", 2);

            char fontName[32];
            char htmlPath[64];
            char productArea = SCGetProductArea();
            if (productArea == 6) {
                goto koreanFont;
            }
            if (productArea < 6) {
                if (productArea != 4) {
                    if (productArea > 3) {
                        goto europeFont;
                    } else if (productArea >= 0) {
                        snprintf(fontName, sizeof(fontName), "WiiNTLG-Regular.ttc");
                        snprintf(htmlPath, sizeof(htmlPath), "/html/%s/iplsetting.ash", "US2");
                        goto loadFiles;
                    }
                }
            } else if (productArea == 11) {
                goto chineseFont;
            }

            snprintf(fontName, sizeof(fontName), "WiiNTLG-Regular.ttc");
            snprintf(htmlPath, sizeof(htmlPath), "/html/%s/iplsetting.ash", "US2");
            goto loadFiles;

        koreanFont:
            snprintf(fontName, sizeof(fontName), "Wii-kr_Round Gothic B.ttf");
            snprintf(htmlPath, sizeof(htmlPath), "/html/%s/iplsetting.ash", "US2");
            goto loadFiles;

        chineseFont:
            snprintf(fontName, sizeof(fontName), "Wii-cn_HeiTiW5.ttf");
            snprintf(htmlPath, sizeof(htmlPath), "/html/%s/iplsetting.ash", "US2");
            goto loadFiles;

        europeFont:
            snprintf(fontName, sizeof(fontName), "WiiNTLG-Regular.ttc");
            snprintf(htmlPath, sizeof(htmlPath), "/html/%s/iplsetting.ash", "TW2");

        loadFiles:
            mpSettingHTMLFile = System::getNandManager()->readAsync(
                System::createMem1AppHeap(), htmlPath, 0, 0, false);
            mpWWWArchiveFile = System::getNandManager()->readAsync(
                System::getMem2App(), "/www.arc", 0, 0, false);
            mpFontFile = System::getNandManager()->readSharedAsync(
                System::getMem2App(), fontName, 3);
            mpBackgroundTPLFile = System::getNandManager()->readAsync(
                System::getMem2App(), "/html/BG_16x9.tpl", 0, 0, false);
            mpSettingLayoutFile = System::getNandManager()->readLayoutAsync(getSceneHeap(), "setting.ash", false);

            if (mInitialArgument == 2) {
                memset(mSettingData, 0, sizeof(mSettingData));
                mAspectRatio = 0;
                www::wiisetting::setInitSetupFlag(1);
            } else if (mInitialArgument == 5) {
                www::wiisetting::setInitSetupFlag(1);
            } else {
                www::wiisetting::setInitSetupFlag(0);
            }
        }

        void Setting::create() {
            nand::File* archiveFile = static_cast<nand::File*>(mpWWWArchiveFile);
            nand::File* writtenArchive = System::getNandManager()->write(
                getSceneHeap(), "/tmp/www.arc", archiveFile->getBuffer(), archiveFile->getLength(), 0x30);
            if (writtenArchive->isFatalError()) {
                System::getErrorHandler()->log("NAND", writtenArchive->checkData(), "iplSetting.cpp", 0x178);
                System::getErrorHandler()->set(ErrorHandler::DEFAULT, 2, NULL, 0, -1);
            }
            if (writtenArchive != NULL) {
                delete writtenArchive;
            }

            mpChangeLayout = new layout::Object(getSceneHeap(), mpSettingLayoutFile, "arc", "SceenChange_b.brlyt");
            mpFirstAnimation = reinterpret_cast<SettingAnimation*>(mpChangeLayout->bind("SceenChange_b_Right.brlan"));
            mpSecondAnimation = reinterpret_cast<SettingAnimation*>(mpChangeLayout->bind("SceenChange_b_Left.brlan"));
            mpChangeLayout->finishBinding();

            mpMainLayout = new layout::Object(getSceneHeap(), mpSettingLayoutFile, "arc", "my_AP_a.brlyt");
            for (int index = 0; index < 58; index++) {
                const SettingAnimationBinding& binding = sSettingAnimationBindings[index];
                mpMainLayout->bindToGroup(sSettingAPAnimations[binding.animation], sSettingAPPaneNames[binding.pane], false,
                                          index == 20 || index == 10);
            }
            mpMainLayout->finishBinding();

            mpWaitLayout = new layout::Object(getSceneHeap(), mpSettingLayoutFile, "arc", "it_Waiting_a.brlyt");
            mpWaitLayout->bindToGroup("it_Waiting_a_Wait.brlan", "G_Wait", false, false);
            mpWaitLayout->finishBinding();
            mpWaitLayout->FindPaneByName("N_Wait")->SetVisible(false);

            mpBrowserData = new ext_ead::www::ImeData;
            mpAPScanThread = new APScanThread();
            mpUSBAPThread = new USBAPThread();
            ncd::NCDSetting::init();
            parental::Parental::init();

            mpAOSSThread = new AOSSThread(getSceneHeap());
            mpRakuRakuThread = new RakuRakuThread(getSceneHeap());

            www::wiisetting::initWiiSetting();
            initWiiSettingData();
            initString();
            www::wiisetting::setStringBuf(mpStringBuffer);
            OSInitMessageQueue(&mFuncMessageQueue, mFuncMessages, 5);
            www::wiisetting::setMsgQueue(&mFuncMessageQueue);

            mpMem1BrowserBuffer = getSceneHeap()->alloc(0x1000, 0x20);
            unk_0x908 = 0;
            mpMem2BrowserBuffer = getSceneHeap()->alloc(0x800, 4);
            memset(mpMem2BrowserBuffer, 0, 0x800);
            mpBrowserStringBuffer = getSceneHeap()->alloc(0x79, 4);
            memset(mpBrowserStringBuffer, 0, 0x79);

            mpEventHandler = new APEvent(this);
            mpPaneManager = new gui::PaneManager(mpEventHandler, mpMainLayout->getDrawInfo(), getSceneHeap(), NULL, false);
            mpPaneManager->setupScene(mpMainLayout);
            mpPaneManager->setAllBoundingBoxComponentTriggerTarget(false);

            for (int index = 0; index < 4; index++) {
                mpPaneManager->setTriggerTarget(mpMainLayout->FindPaneByName(sSettingAPButtonNames[index]), true);
            }
            for (int index = 0; index < 2; index++) {
                mpPaneManager->setTriggerTarget(mpMainLayout->FindPaneByName(sSettingArrowNames[index]), true);
            }

            TPLBind(reinterpret_cast<TPLPalette*>(static_cast<nand::File*>(mpBackgroundTPLFile)->getBuffer()));
            int tick = OSGetTick();
            OSReport("*** prepare costs: %dms\n", (tick - mPrepareTick) / (OS_TIMER_CLOCK / 4000));
            mPrepareTick = OSGetTick();
        }

        void Setting::createBrowser() {
            EGG::Heap* mem1Heap = System::createMem1AppHeap();
            u32 mem1Size = mem1Heap->getAllocatableSize(4);
            EGG::Heap* mem2Heap = System::getMem2App();
            u32 mem2Size = mem2Heap->getAllocatableSize(4) - 0x80000;
            mem1Buffer_ = System::createMem1AppHeap()->alloc(mem1Size, 4);
            mem2Buffer_ = mem2Heap->alloc(mem2Size, 4);
            OSReport("Setting Scene: mem1: %d  mem2: %d\n", mem1Size, mem2Size);

            nw4r::ut::Rect projection16x9;
            nw4r::ut::Rect projection4x3;
            System::getProjectionRect16x9(&projection16x9);
            System::getProjectionRect4x3(&projection4x3);
            int width = projection16x9.right - projection16x9.left;
            int height = projection16x9.bottom - projection16x9.top;

            const char* urlFormats[] = {"marc:%s/%s/", "file:dvd/html/IPLSetting/%s/%s/"};
            const char* pagePaths[] = {
                "index01.html", "Internet/Internet_index.html", "Setup/startup_index1.html",
                "Update/Update_index.html", "index02.html", "Setup/ScreenSave.html",
                "Country/US_Country_flame.html",
            };
            const char* pageNames[] = {"Calendar", "Parental_Control", "Internet", "Wiiconnect24"};
            const char* regionCodes[] = {"JP/JP", "FIX/US", "EU/EU", "TW/TW", "KR/KR", "CN/CN"};
            const char* languageCodes[] = {"JPN", "ENG", "GER", "FRA", "SPA", "ITA", "DUT", "CHN", "KOR"};

            char basePath[100];
            char browserPath[100];
            memset(basePath, 0, sizeof(basePath));
            memset(browserPath, 0, sizeof(browserPath));
            strcpy(basePath, urlFormats[0]);
            int pageIndex = mInitialArgument;
            if (pageIndex < 0 || pageIndex >= 7) {
                pageIndex = 0;
            }
            strcat(basePath, pagePaths[pageIndex]);

            int regionIndex = 1;
            char productArea = SCGetProductArea();
            if (productArea >= 0 && productArea < 4) {
                regionIndex = productArea > 2 ? 2 : 0;
            } else if (productArea == 6) {
                regionIndex = 4;
            } else if (productArea == 11) {
                regionIndex = 5;
            } else if (productArea >= 7 && productArea < 11) {
                regionIndex = 2;
            }

            if (mInitialArgument == ARG_UNK_5) {
                snprintf(browserPath, sizeof(browserPath), basePath, regionCodes[regionIndex],
                         languageCodes[System::getLanguage()], pagePaths[pageIndex]);
            } else if (mInitialArgument == ARG_UNK_6) {
                int directPage = 0;
                for (int index = 0; index < 4; index++) {
                    if (strstr(mpStringBuffer->netSettingArg, pageNames[index]) != NULL) {
                        directPage = index;
                        break;
                    }
                }
                if (directPage == 0) {
                    snprintf(browserPath, sizeof(browserPath), basePath, regionCodes[regionIndex],
                             languageCodes[System::getLanguage()], "index01.html");
                } else if (directPage == 1) {
                    snprintf(browserPath, sizeof(browserPath), basePath, regionCodes[regionIndex],
                             languageCodes[System::getLanguage()], "index02.html");
                } else {
                    snprintf(browserPath, sizeof(browserPath), basePath, regionCodes[regionIndex],
                             languageCodes[System::getLanguage()], "index03.html");
                }
            } else {
                snprintf(browserPath, sizeof(browserPath), basePath, regionCodes[regionIndex],
                         languageCodes[System::getLanguage()]);
            }

            OSReport("***********************************\n");
            OSReport(" RSO PLACED : %p %d\n", static_cast<nand::File*>(mpWWWLibraryFile)->getBuffer(),
                     static_cast<nand::File*>(mpWWWLibraryFile)->getLength());
            ICInvalidateRange(static_cast<nand::File*>(mpWWWLibraryFile)->getBuffer(),
                              static_cast<nand::File*>(mpWWWLibraryFile)->getLength());
            ext_ead::www::SurfaceManager::CreateManager(width, height, width, height, mem1Buffer_, mem1Size,
                                                       mem2Buffer_, mem2Size,
                                                       static_cast<nand::File*>(mpWWWLibraryFile)->getBuffer(),
                                                       browserPath);
            ext_ead::www::SurfaceManager::RegisterArcFile(static_cast<nand::File*>(mpWWWArchiveFile)->getBuffer());
            ext_ead::www::SurfaceManager::RegisterIniFile(static_cast<nand::File*>(mpSettingHTMLFile)->getBuffer(),
                                                          static_cast<nand::File*>(mpSettingHTMLFile)->getLength());
            ext_ead::www::SurfaceManager::RegisterFontFile(0, static_cast<nand::File*>(mpFontFile)->getBuffer(),
                                                           static_cast<nand::File*>(mpFontFile)->getLength());
            ext_ead::www::SurfaceManager::StartThread();
        }

        void Setting::initDirectUrl() {
            if (mInitialArgument != ARG_UNK_6) {
                return;
            }
            const char* settingArgument = System::getNetSettingArg();
            if (settingArgument != NULL) {
                memcpy(mpStringBuffer->netSettingArg, settingArgument, 0x80);
            }
        }

        void Setting::initString() {
            mpStringBuffer = reinterpret_cast<www::wiisetting::SetStringBuf*>(getSceneHeap()->alloc(0x64e, 4));
            OSReport("HTML String Alloc Size:%d\n", 0x64e);
            memset(mpStringBuffer, 0, 0x64e);
            memset(unk_0x938, 0, 0x202);
            initNickName();
            initSecurityKey();
            initSSID();
            initIP();
            initDNS();
            initProxy();
            initBasic();
            initMTU();
            initSecA();
            initVersion();
            initDirectUrl();
        }

        FaderSceneCommand Setting::calcFadein() {
            if (System::hasCreatedAfter() && mBrowserCreated == 0) {
                mBrowserCreated = 1;
                createBrowser();
                OSReport("............browser created\n");
            } else if (mBrowserCreated == 0) {
                OSReport("wait first init\n");
                return FADER_SCN_CONTINUE;
            }

            ext_ead::www::SurfaceManager* surfaceManager = ext_ead::www::SurfaceManager::GetInstance();
            ext_ead::www::BrowserThread* browserThread = surfaceManager->GetBrowserThread();
            if (browserThread != NULL && browserThread->GetTextureBuffer(0, NULL) != NULL && System::hasCreatedAfter()) {
                mKeyboardState = *System::getKeyboard()->getState();
                System::getFader()->fadeIn();
                mCreatePageTime = OSGetTime();
                OSReport("*** create page costs: %dms\n",
                         (OSGetTick() - mPrepareTick) / (OS_TIMER_CLOCK / 1000));
                return FADER_SCN_NEXT;
            }
            return FADER_SCN_CONTINUE;
        }

        void Setting::updateController_() {
            nw4r::ut::Rect projection;
            System::getProjectionRect4x3(&projection);

            if (isAnimating()) {
                return;
            }

            controller::Interface* youngController = System::getYoungController();
            ext_ead::www::BrowserThread::CmdPacket packet;

            if (youngController != NULL) {
                if (unk_0xB9C < 10 || mpStringBuffer->netSettingArg[0] != 0) {
                    packet.data.controller.irX = -1000.0f;
                    packet.data.controller.irY = -1000.0f;
                    packet.data.controller.btnHold = 0;
                    packet.data.controller.btnTrigger = 0;
                    packet.data.controller.btnRelease = 0;
                } else {
                    packet.data.controller.irX = youngController->getDpdProjectionPos().x - projection.left;
                    packet.data.controller.irY = youngController->getDpdProjectionPos().y - projection.top;
                    u32 classicHold = youngController->getClassicHoldFlag();
                    u32 classicTrigger = youngController->getClassicTrigFlag();
                    u32 classicRelease = youngController->getClassicReleaseFlag();
                    packet.data.controller.btnHold = (classicHold << 16) | youngController->getHoldFlag();
                    packet.data.controller.btnTrigger = (classicTrigger << 16) | youngController->getTrigFlag();
                    packet.data.controller.btnRelease = (classicRelease << 16) | youngController->getReleaseFlag();
                }

                packet.type = 0;
                if (mKeyboardState.type == textinput::MemoManager::ST_Hidden && unk_0x74 == 0) {
                    ext_ead::www::SurfaceManager::GetInstance()->GetBrowserThread()->SendUIEvent(&packet);
                }
            } else {
                packet.data.controller.irX = -1000.0f;
                packet.data.controller.irY = -1000.0f;
                packet.data.controller.btnHold = 0;
                packet.data.controller.btnTrigger = 0;
                packet.data.controller.btnRelease = 0;
                packet.type = 0;
                ext_ead::www::SurfaceManager::GetInstance()->GetBrowserThread()->SendUIEvent(&packet);
            }
        }

        void Setting::changeVideoMode() {
            setSE();
            VISetBlack(TRUE);
            VIFlush();
            VIWaitForRetrace();
            System::resetFrameworkRenderMode();

            u32 startTick = OSGetTick();
            while ((OSGetTick() - startTick) / (OS_TIMER_CLOCK / 1000) < 0x67c) {
                VIWaitForRetrace();
            }

            mAspectRatio = SCGetAspectRatio();
            mProgressiveMode = SCGetProgressiveMode();
            mEuRgb60Mode = SCGetEuRgb60Mode();
            unk_0xB94 = 0;

            VISetBlack(FALSE);
            VIFlush();
            VIWaitForRetrace();

            if (static_cast<u32>(System::getRegion()) == 2) {
                if (mEuRgb60Mode == 0) {
                    *reinterpret_cast<u32*>(0x800000cc) = 1;
                } else {
                    *reinterpret_cast<u32*>(0x800000cc) = 5;
                }
            }

            while (mpSecondAnimation->state == 1 || mpFirstAnimation->state == 1) {
                mpChangeLayout->calc();
            }

            mState = 20;
            unk_0xB9C = 10;
        }

        bool Setting::isInitialSequenceExit(const controller::Interface* input) {
            u32 connectedMask = utility::wpad::getWpadConnectedMask();
            if (input->downTrg(0x100800) ||
                ((OSGetTime() - mCreatePageTime) / (OS_TIMER_CLOCK / 1000) >= 500 &&
                 connectedMask != unk_0xBA8 &&
                 utility::wpad::isIncreaseConnectedWpad(unk_0xBA8, connectedMask))) {
                return true;
            }

            if (connectedMask != unk_0xBA8) {
                unk_0xBA8 = connectedMask;
            }
            return false;
        }

        bool Setting::updateScreenMode() {
            if (unk_0x91C[2] != 0) {
                if (unk_0xB94 == 0) {
                    if (mEuRgb60Mode == SCGetEuRgb60Mode()) {
                        if (mProgressiveMode != SCGetProgressiveMode()) {
                            unk_0xB94 = 2;
                        }
                    } else {
                        unk_0xB94 = 3;
                    }

                    if (unk_0xB94 != 0 && unk_0xB94 != 1) {
                        System::getFader()->fadeOut();
                        mState = 0;
                        return true;
                    }
                }
            } else if (unk_0xB94 == 1 && unk_0x74 == 8) {
                    System::getFader()->fadeOut();
                    mState = 0;
                    unk_0x92C = 0;
                    unk_0x74 = 0;
                    return true;
            }

            if (unk_0xB94 == 1) {
                if (System::getFader()->getStatus() == EGG::Fader::PREPARE_IN) {
                    System::getDialog()->terminate();
                    SCSetAspectRatio(mAspectRatio & 0xff);
                    SCFlush();
                    if (System::getDialog()->getLastResult() < 0) {
                        mState = 0;
                        return true;
                    }

                    changeVideoMode();
                    www::wiisetting::setStringBuf(mpStringBuffer);
                    System::getFader()->fadeIn();
                } else {
                    mState = 0;
                    return true;
                }
            } else if (unk_0xB94 > 0 && unk_0xB94 < 4) {
                if (System::getFader()->getStatus() == EGG::Fader::PREPARE_IN) {
                    changeVideoMode();
                    System::getFader()->fadeIn();
                } else {
                    mState = 0;
                    return true;
                }
            }

            return false;
        }

        FaderSceneCommand Setting::calcNormal() {
            if (unk_0x5C == 0) {
                getFuncMsgQ();
                controller::Interface* input = System::getYoungController();

                ++mState;
                if (mState > 20) {
                    mState = 20;
                }
                if (unk_0xB9C > 0) {
                    ++unk_0xB9C;
                }
                if (unk_0xB9C > 10) {
                    unk_0xB9C = 10;
                }
                if (updateScreenMode()) {
                    return FADER_SCN_CONTINUE;
                }

                if (input != NULL) {
                    if (input->downTrg(0x100800) && mpWiiSettingData->data[0x12] == 0x1e &&
                        unk_0x92C > 0x1e && unk_0x92C < 0x78) {
                        unk_0x92C = 0x78;
                        www::wiisetting::setFuncResult(1);
                        mpWiiSettingData->data[0x37] = 1;
                        setSE();
                        unk_0xB9C = 0;
                    }
                    if (isInitialSequenceExit(input) && mpWiiSettingData->data[0x12] == 0x1f) {
                        snd::getSystem()->startSE("WIPL_SE_DECIDE");
                        www::wiisetting::setFuncResult(1);
                        mpWiiSettingData->data[0x12] = 0;
                    }
                }

                if (unk_0xBAC == 0 && unk_0xB9C == 10 && mpStringBuffer->netSettingArg[0] != 0) {
                    www::wiisetting::setFuncResult(1);
                    unk_0xBAC = 1;
                }

                if (System::getAspectRatio()) {
                    updateController_();
                }

                ext_ead::www::BrowserThread* browserThread =
                    ext_ead::www::SurfaceManager::GetInstance()->GetBrowserThread();
                if (browserThread->ReceiveWindowEvent(mpBrowserData)) {
                    if (mpBrowserData->unk_0x00 == 0) {
                        OSReport("IME Created ");
                        if (mpBrowserData->text != NULL) {
                            OSReport("initKeyboard %s\n");
                            OSReport("initKeyboard %d\n", mpWiiSettingData->data[0x11]);
                            if (mpWiiSettingData->data[0x11] == 0) {
                                browserThread->CommitIme(mpBrowserData, mpBrowserData->text);
                                browserThread->DisposeImeData(mpBrowserData);
                            } else {
                                unk_0x74 = 1;
                                initKeyboard(mpBrowserData->text);
                            }
                        } else {
                            OSReport("NULL ptr\n");
                        }
                    } else {
                        OSReport("Other Event\n");
                    }
                }
            }

            switch (unk_0x74) {
            case 1:
                calcKeyboard();
                break;
            case 2:
                if (System::getDialog()->getLastResult() >= 0) {
                    unk_0xB9C = 1;
                    unk_0x74 = 0;
                    mIsResetAcceptable = 1;
                }
                break;
            case 3:
                if (System::getDialog()->getLastResult() == 1) {
                    if (unk_0xB9C == 0) {
                        www::wiisetting::setFuncResult(1);
                    } else if (www::wiisetting::getFuncResult() == 0) {
                        unk_0x74 = 0;
                    }
                    unk_0xB9C = 1;
                } else if (System::getDialog()->getLastResult() == 2) {
                    if (unk_0xB9C == 0) {
                        www::wiisetting::setFuncResult(2);
                    } else if (www::wiisetting::getFuncResult() == 0) {
                        unk_0x74 = 0;
                    }
                    unk_0xB9C = 1;
                }
                break;
            case 4:
                mpWiiSettingData->data[0x12] = 1;
                if (System::getHomeButtonMenu()->disable() &&
                    System::getDialog()->getLastResult() >= 0) {
                    unk_0x74 = 0;
                }
                break;
            case 5:
                if (System::getScene(0x1b) == NULL) {
                    if (unk_0x91C[3] == 1) {
                        unk_0x74 = 0;
                        unk_0x91C[3] = 0;
                        resetFuncMsgQ();
                        if (mpWiiSettingFlag->smthMsgData != 'O') {
                            unk_0xB9C = 1;
                        }
                    }
                } else {
                    unk_0x91C[3] = 1;
                    scene::ParentalDialog* parentalDialog =
                        static_cast<scene::ParentalDialog*>(System::getScene(0x1b));
                    scene::ParentalDialog::Result result = parentalDialog->getResult();
                    if (result == scene::ParentalDialog::RESULT_OVER_ATTEMPTS) {
                        www::wiisetting::setFuncResult(2);
                    } else if (result == scene::ParentalDialog::RESULT_SUCCESS) {
                        unk_0x74 = 6;
                        www::wiisetting::setFuncResult(1);
                    } else if (result > scene::ParentalDialog::RESULT_OVER_ATTEMPTS &&
                               result <= scene::ParentalDialog::RESULT_CANCELLED) {
                        www::wiisetting::setFuncResult(2);
                    }
                }
                break;
            case 6:
                if (System::getScene(0x1b) == NULL) {
                    unk_0x91C[3] = 0;
                    if (mpWiiSettingFlag->smthMsgData == 'O') {
                        if (!ncd::NCDSetting::getEnableFlag()) {
                            System::getDialog()->callBtn2(System::getRegion() == 2 ? 0x174 : 0x170,
                                                          0x146, 0x25);
                            unk_0x74 = 9;
                        } else if (SCGetEULA() == 0) {
                            System::getDialog()->callBtn2(System::getRegion() == 2 ? 0x175 : 0x172,
                                                          0x2e, 0x25);
                            unk_0x74 = 0xe;
                        } else {
                            www::wiisetting::setFuncResult(6);
                            unk_0x74 = 0;
                            resetFuncMsgQ();
                        }
                    } else {
                        unk_0x74 = 0;
                    }
                }
                break;
            case 7:
                if (System::getDialog()->getLastResult() == 1) {
                    www::wiisetting::setFuncResult(1);
                    SCSetWCFlags(SCGetWCFlags() & 0xfffffffe);
                    SCIdleModeInfo idleMode = {0, 0};
                    SCSetIdleMode(&idleMode);
                    System::getNwc24Manager()->enableLedNotification(TRUE);
                    SCSetEULA(0);
                    ncd::NCDSetting::adjustNWC24Flag();
                    parental::Parental::setCountry(mpWiiSettingData->data[0x3c]);
                    parental::Parental::clear();
                    System::reloadDownloadTask();
                    unk_0x74 = 0;
                } else if (System::getDialog()->getLastResult() == 2) {
                    www::wiisetting::setFuncResult(2);
                    unk_0x74 = 0;
                    unk_0xB9C = 1;
                }
                break;
            case 8:
                ++unk_0x92C;
                if (unk_0x92C == 0xb4) {
                    unk_0xB94 = 1;
                    unk_0x92C = 0;
                }
                break;
            case 9:
                if (System::getDialog()->getLastResult() == 1) {
                    if (mpWiiSettingFlag->smthMsgData == 'O') {
                        www::wiisetting::setFuncResult(5);
                        resetFuncMsgQ();
                    } else {
                        www::wiisetting::setFuncResult(6);
                    }
                    unk_0x74 = 0;
                } else if (System::getDialog()->getLastResult() == 2) {
                    if (mpWiiSettingFlag->smthMsgData == 'O') {
                        if (unk_0xB9C == 0) {
                            www::wiisetting::setFuncResult(2);
                        } else if (www::wiisetting::getFuncResult() == 0) {
                            unk_0x74 = 0;
                            resetFuncMsgQ();
                        }
                        unk_0xB9C = 1;
                    } else {
                        unk_0x74 = 0;
                        www::wiisetting::setFuncResult(2);
                    }
                }
                break;
            case 10:
                if (System::getDialog()->getLastResult() == 2) {
                    System::getDialog()->callBtn1(0x172, 1);
                    unk_0x74 = 0xb;
                    SCSetWCFlags(SCGetWCFlags() & 0xfffffffe);
                    SCIdleModeInfo idleMode = {0, 0};
                    SCSetIdleMode(&idleMode);
                    System::getNwc24Manager()->enableLedNotification(TRUE);
                    SCSetEULA(0);
                    ncd::NCDSetting::adjustNWC24Flag();
                    SCFlush();
                } else if (System::getDialog()->getLastResult() == 1) {
                    mProfileIDMode = 0;
                    unk_0xB9C = 1;
                    unk_0x74 = 0;
                }
                break;
            case 0xb:
                if (System::getDialog()->getLastResult() >= 0) {
                    mProfileIDMode = 10;
                    mpWiiSettingFlag->smthMsgData = 0x54;
                    unk_0x74 = 0;
                }
                break;
            case 0xc:
                if (System::getDialog()->getLastResult() == 2) {
                    SCSetWCFlags(SCGetWCFlags() & 0xfffffffe);
                    SCIdleModeInfo idleMode = {0, 0};
                    SCSetIdleMode(&idleMode);
                    System::getNwc24Manager()->enableLedNotification(TRUE);
                    SCSetEULA(0);
                    ncd::NCDSetting::adjustNWC24Flag();
                    SCFlush();
                    System::getDialog()->callBtn1(0x170, 0x2e);
                    unk_0x74 = 9;
                } else if (System::getDialog()->getLastResult() == 1) {
                    unk_0xB9C = 1;
                    unk_0x74 = 0;
                }
                break;
            case 0xd:
                if (System::getDialog()->getLastResult() == 1) {
                    www::wiisetting::setFuncResult(8);
                    unk_0x74 = 0;
                } else if (System::getDialog()->getLastResult() == 2) {
                    www::wiisetting::setFuncResult(7);
                    unk_0x74 = 0;
                }
                break;
            case 0xe:
                if (System::getDialog()->getLastResult() == 1) {
                    mpWiiSettingFlag->smthMsgData = 0x55;
                    unk_0x74 = 0;
                } else if (System::getDialog()->getLastResult() == 2) {
                    if (unk_0xB9C == 0) {
                        www::wiisetting::setFuncResult(2);
                    } else if (www::wiisetting::getFuncResult() == 0) {
                        resetFuncMsgQ();
                        unk_0x74 = 0;
                    }
                    unk_0xB9C = 1;
                }
                break;
            case 0x11:
                calcSafeMode();
                break;
            }

            u8 action = mpWiiSettingData->data[0x12];
            if (action != 0) {
                if (action == 0x1e) {
                    ++unk_0x92C;
                    if (unk_0x92C == 1) {
                        System::getDialog()->callBtn1(0x1bf, 0x2e);
                        unk_0x74 = 4;
                    } else if (unk_0x92C == 3) {
                        TPLBind(NULL);
                    } else if (unk_0x92C == 0x55 || unk_0x92C == 0x5a) {
                        BOOL interruptLevel = OSDisableInterrupts();
                        WPADSetSensorBarPower(unk_0x92C == 0x5a);
                        OSRestoreInterrupts(interruptLevel);
                        if (unk_0x92C == 0x5a) {
                            unk_0x92C = 0x1e;
                        }
                    } else if (unk_0x92C == 0x96) {
                        BOOL interruptLevel = OSDisableInterrupts();
                        WPADSetSensorBarPower(TRUE);
                        OSRestoreInterrupts(interruptLevel);
                        System::getHomeButtonMenu()->enable();
                        mpWiiSettingData->data[0x12] = 0;
                        TPLBind(reinterpret_cast<TPLPalette*>(
                            static_cast<nand::File*>(mpBackgroundTPLFile)->getBuffer()));
                        unk_0x92C = 0;
                    }
                } else if (action < 0x1f) {
                    initHTMLText();
                    initMessage();
                }
            }

            if (mpWiiSettingData->data[0x36] != 0) {
                calcSetting();
            }

            switch (mpWiiSettingFlag->smthMsgData) {
            case 1:
                resetFuncMsgQ();
                waitStart();
                createChildScene(0x19, this, NULL, NULL);
                break;
            case 4:
                resetAP();
                initAP();
                mpWiiSettingFlag->smthMsgData = 2;
            case 2:
            case 3:
                scanAP();
                break;
            case 5:
                resetAP();
                break;
            case 6:
                initAP();
                resetFuncMsgQ();
                break;
            case 7:
                redrawAP();
                break;
            case 9:
                setNUP();
                break;
            case 0x17:
                parental::Parental::clearMiss();
            case 'Z':
                System::getHomeButtonMenu()->enable();
                resetFuncMsgQ();
                break;
            case 0x18:
                ncd::NCDSetting::write();
            case ']':
                mIsResetAcceptable = 0;
                resetFuncMsgQ();
                break;
            case 0x1a:
                System::getDialog()->callBtn2(System::getRegion() == 2 ? 0x160 : 0x15f,
                                              0x2e, 0x13b);
                unk_0x74 = 3;
                resetFuncMsgQ();
                break;
            case 0x1c:
                if (mAspectRatio != mpWiiSettingData->data[6]) {
                    mAspectRatio = mpWiiSettingData->data[6];
                    if (mAspectRatio == 1) {
                        System::getDialog()->callBtn0(0x1bd, 0, false);
                    } else if (mAspectRatio == 0) {
                        System::getDialog()->callBtn0(0x1c9, 0, false);
                    }
                    unk_0x74 = 8;
                }
                resetFuncMsgQ();
                break;
            case 0x1d:
            case 'M':
            case 'N':
                if (action == 0x1d || calcSafeMode()) {
                    if (!parental::Parental::checkFlags()) {
                        www::wiisetting::setFuncResult(1);
                        if (mpWiiSettingFlag->smthMsgData == 'N') {
                            unk_0x74 = 6;
                        }
                    } else {
                        createChildScene(0x1b, this, NULL, reinterpret_cast<void*>(1));
                        unk_0x74 = 5;
                    }
                    if (mpWiiSettingFlag->smthMsgData == 0x1d ||
                        mpWiiSettingFlag->smthMsgData == 'M') {
                        resetFuncMsgQ();
                    } else {
                        mpWiiSettingFlag->smthMsgData = 'O';
                    }
                }
                break;
            case 0x1e:
                memset(mpMem2BrowserBuffer, 0, 0x800);
                memset(mpBrowserStringBuffer, 0, 0x79);
                mpWiiSettingFlag->smthMsgData = 0x23;
            case '#':
                setUSBAP();
                break;
            case 0x1f:
                cancelUSBAP();
                break;
            case ' ':
            case '!':
            case '"':
                AOSSProcess();
                break;
            case '(':
            case ')':
            case '*':
            case '+':
            case ',':
                RakuProcess();
                break;
            case '4':
                if (System::getHomeButtonMenu()->disable() && unk_0x5C == 0) {
                    controller::Interface* youngController = System::getYoungController();
                    if (youngController != NULL && youngController->downTrg(0x100800)) {
                        resetFuncMsgQ();
                        System::getHomeButtonMenu()->enable();
                        www::wiisetting::setFuncResult(5);
                    }
                }
                break;
            case 'P':
                SCSetLanguage(mpWiiSettingData->data[0x30]);
                if (SCGetConfigDoneFlag() == 0 && SCGetConfigDoneFlag2() == 0 &&
                    System::getRegion() == 2) {
                    if (mpWiiSettingData->data[0x30] == 3) {
                        mpWiiSettingData->data[0x3c] = 0x68;
                        parental::Parental::setCountry(0x68);
                    } else {
                        mpWiiSettingData->data[0x3c] = 0x40;
                        parental::Parental::setCountry(0x40);
                    }
                }
                SCFlush();
                System::getKeyboard()->setLanguage(SCGetLanguage());
                parental::Parental::init();
                System::reloadDownloadTask();
                resetFuncMsgQ();
                break;
            case 'Q':
                snd::getSystem()->muteOffBGM(0x5a);
                resetFuncMsgQ();
                break;
            case 'R':
                snd::getSystem()->muteOnBGM(0x5a);
                resetFuncMsgQ();
                break;
            case 'S':
                if (mInitialArgument == 2 || mInitialArgument == 5) {
                    parental::Parental::setCountry(mpWiiSettingData->data[0x3c]);
                    parental::Parental::clear();
                    www::wiisetting::setFuncResult(1);
                } else if (mpWiiSettingData->data[0x3c] == parental::Parental::getCountry()) {
                    www::wiisetting::setFuncResult(1);
                } else {
                    System::getDialog()->callBtn2(0x1c4, 0x2e, 0x13b);
                    unk_0x74 = 7;
                }
                resetFuncMsgQ();
                break;
            case 'T':
                setUpdate_();
                break;
            case 'U':
                if (unk_0x7C == 0) {
                    unk_0x7C = 1;
                }
                setUseEULA_();
                break;
            case 'V':
                mProfileIDMode = 9;
                setUpdate_();
                break;
            case 'W':
                setUseEULA_();
                break;
            case 'X':
                if (unk_0x7C == 0) {
                    unk_0x7C = 2;
                }
                setUseEULA_();
                break;
            case 'Y':
                mProfileIDMode = 2;
                mpWiiSettingFlag->smthMsgData = 0x54;
                break;
            case '[':
                if (System::getHomeButtonMenu()->disable()) {
                    resetFuncMsgQ();
                }
                break;
            case '\\':
                mIsResetAcceptable = 1;
                resetFuncMsgQ();
                break;
            case '^':
                System::getHomeButtonMenu()->enable();
                mIsResetAcceptable = 1;
                resetFuncMsgQ();
                break;
            case '_':
                if (System::getHomeButtonMenu()->disable()) {
                mIsResetAcceptable = 0;
                    resetFuncMsgQ();
                }
                break;
            case 'd':
                createChildScene(0x1d, this, NULL, reinterpret_cast<void*>(2));
                resetFuncMsgQ();
                waitStart();
                break;
            case 'e':
                unk_0x74 = 0xf;
                ++unk_0x92C;
                if (unk_0x92C >= 100) {
                    mIsResetAcceptable = 1;
                    System::getResetHandler()->reset();
                    resetFuncMsgQ();
                }
                break;
            case 'f':
                unk_0x74 = 0x10;
                ++unk_0x92C;
                if (unk_0x92C >= 100) {
                    mIsResetAcceptable = 1;
                    System::getResetHandler()->powerOff();
                    resetFuncMsgQ();
                }
                break;
            case 'g':
                if (calcSafeMode()) {
                    www::wiisetting::setFuncResult(1);
                    resetFuncMsgQ();
                }
                break;
            }

            if (mpWiiSettingData->data[0x37] != 0 || mpWiiSettingData->data[0x38] != 0) {
                setSE();
            }
            if (mpWiiSettingData->data[0x39] != 0) {
                return FADER_SCN_NEXT;
            }

            mpChangeLayout->calc();
            mpMainLayout->calc();
            mpWaitLayout->calc();
            unk_0x91C[2] = 0;
            return FADER_SCN_CONTINUE;
        }

        FaderSceneCommand Setting::calcFadeout() {
            if (System::getFader()->getStatus() == EGG::Fader::PREPARE_IN) {
                if (unk_0x5C == 0) {
                    unk_0x5C = 1;
                    ext_ead::www::SurfaceManager::GetInstance()->StopThreadAsync();
                    OSReport("!!!!!!!!!!!!! SCFlush !!!!!!!!!!!!!!\n");
                    SCFlush();
                } else if (unk_0x7C == 5) {
                if (mInitialArgument == 2 || mInitialArgument == 5) {
                    SCSetConfigDoneFlag(TRUE);
                    SCSetConfigDoneFlag2(TRUE);
                    SCSetUpdateType(0);
                    SCFlush();
                }

                    while (WPADGetStatus() != 0 ||
                           System::getBS2Manager()->getIPLState() != bs2::IPL_STATE_8) {
                        snd::getSystem()->calc();
                        System::getBS2Manager()->update();
                        VIWaitForRetrace();
                        if (WPADGetStatus() != 0) {
                            OSReport("wait for WPAD\n");
                        }
                        if (System::getBS2Manager()->getIPLState() != bs2::IPL_STATE_8) {
                            OSReport("wait for BS2\n");
                        }
                    }

                    VISetBlack(TRUE);
                    VIFlush();
                    VIWaitForRetrace();
                    OSReport("VI Black\n");
                    while (!__OSSyncSram()) {
                        OSReport("sync sram\n");
                    }
                    while (!System::isReceiveScheduleStopped()) {
                        OSReport("Wait ScheduleStopped\n");
                        OSSleepMilliseconds(5);
                    }
                    __OSLaunchTitlelForSystem(mUpdateTitleId, 0, NULL);
                    for (;;) {
                        OSReport(NULL);
                    }
                } else if (ext_ead::www::SurfaceManager::GetInstance()->IsThreadStopped()) {
                    OSReport("reserve destroy\n");
                    ext_ead::www::SurfaceManager::DisposeManager();
                    OSReport("reserve destroy done\n");
                    if (mInitialArgument == 2 || mInitialArgument == 5) {
                        SCSetConfigDoneFlag(TRUE);
                        SCSetConfigDoneFlag2(TRUE);
                        SCSetUpdateType(0);
                        SCFlush();
                        reserveAllSceneDestruction(0x1a, NULL);
                    } else {
                        System::reloadDownloadTask();
                        reserveAllSceneDestruction(0x15, NULL);
                    }
                    delete mpBrowserData;
                    return FADER_SCN_NEXT;
                }
            }

            return FADER_SCN_CONTINUE;
        }

        void Setting::draw() {
            if (!System::onDrawLayer(1)) {
                return;
            }

            if (!mBrowserCreated) {
                utility::Graphics::setOrtho(0);
                nw4r::ut::Rect background(-1000.0f, -1000.0f, 1000.0f, 1000.0f);
                GXColor color = {0, 0, 0, 0xFF};
                utility::Graphics::drawPolygon(background, color);
                return;
            }

            ext_ead::www::SurfaceManager* surface = ext_ead::www::SurfaceManager::GetInstance();
            if (surface == NULL) {
                return;
            }

            ext_ead::www::BrowserThread* browser = surface->GetBrowserThread();
            if (browser == NULL || browser->GetTextureBuffer(0, NULL) == NULL) {
                return;
            }

            WWWRect* wideRect = NULL;
            WWWRect* standardRect = NULL;
            void* wideBuffer = browser->GetTextureBuffer(1, &wideRect);
            void* standardBuffer = browser->GetTextureBuffer(0, &standardRect);
            if (wideBuffer == NULL || standardBuffer == NULL) {
                return;
            }

            if (www::trasition::GetScrollState() != www::trasition::SCROLL_RESET) {
                www::trasition::ResetScrollState();
                OSReport("changed %p %p\n", standardBuffer, wideBuffer);
                ext_ead::www::Heap::reportLeaHeap();
            }

            nw4r::ut::Rect projection4x3;
            nw4r::ut::Rect projection16x9;
            System::getProjectionRect4x3(&projection4x3);
            System::getProjectionRect16x9(&projection16x9);

            GXTexObj standardTexture;
            GXTexObj wideTexture;
            GXInitTexObj(&standardTexture, standardBuffer, standardRect->w, standardRect->h, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
            GXInitTexObj(&wideTexture, wideBuffer, wideRect->w, wideRect->h, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
            GXInitTexObjLOD(&standardTexture, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
            GXInitTexObjLOD(&wideTexture, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);

            utility::Graphics::setOrtho(0);
            GXColor color = {0xFF, 0xFF, 0xFF, (u8)(mState * 0xFF / 20)};
            utility::Graphics::drawTexture(projection4x3, standardTexture, color, 1);
            utility::Graphics::drawTexture(projection16x9, wideTexture, color, 1);

            if (mpWiiSettingData->data[0x12] == 0x1E && unk_0x92C > 3) {
                SensitivityDrawing::draw(static_cast<nand::File*>(mpBackgroundTPLFile));
            }

            mpChangeLayout->draw();
            mpWaitLayout->draw();
            if (mState == 0xC) {
                unk_0xB9C = 1;
            }

            if (mpWiiSettingFlag->smthMsgData >= 2 && mpWiiSettingFlag->smthMsgData <= 7) {
                u32 left;
                u32 top;
                u32 width;
                u32 height;
                GXGetScissor(&left, &top, &width, &height);
                GXSetScissor(0, System::getRenderModeObj()->efbHeight / 2 - 0xA4, System::getRenderModeObj()->fbWidth, 0x132);
                mpWaitLayout->draw();
                GXSetScissor(left, top, width, height);
            }
        }

        void Setting::initWiiSettingData() {
            mpWiiSettingData = www::wiisetting::getWiiSettingData();
            mpWiiSettingFlag = www::wiisetting::getWiiSettingFlag();
            mpWiiSettingData->data[0x3c] = parental::Parental::getCountry();
            mpWiiSettingData->data[7] = 0x20 - (SCGetDisplayOffsetH() + 0x10);
            mpWiiSettingData->data[0xb] = SCGetBtDpdSensibility();
            mpWiiSettingData->data[6] = SCGetAspectRatio();
            mpWiiSettingData->data[0x30] = SCGetLanguage();
            mpWiiSettingData->data[0x2d] = parental::Parental::checkRating();
        }

        void Setting::initHTMLText() {
            OSReport("initHTMLText pageId:%d\n", mpWiiSettingData->data[0x12]);
            memset(unk_0x938, 0, sizeof(unk_0x938));

            switch (mpWiiSettingData->data[0x12]) {
                case 2:
                    initNickName();
                    break;
                case 3:
                    initSecurityKey();
                    break;
                case 4:
                    initSSID();
                    break;
                case 5:
                    initIP();
                    break;
                case 6:
                    initDNS();
                    break;
                case 7:
                    initProxy();
                    break;
                case 8:
                    initBasic();
                    break;
                case 9:
                    initMTU();
                    break;
                case 10:
                    memset(&mpStringBuffer->parentalPass, 0, sizeof(mpStringBuffer->parentalPass));
                    break;
                case 11:
                    memset(&mpStringBuffer->parentalRePass, 0, sizeof(mpStringBuffer->parentalRePass));
                    break;
                case 12:
                    memset(&mpStringBuffer->parentalJudgePass, 0, sizeof(mpStringBuffer->parentalJudgePass));
                    break;
                case 13:
                    initSecA();
                    break;
                case 14:
                    memset(&mpStringBuffer->parentalReSecA, 0, sizeof(mpStringBuffer->parentalReSecA));
                    break;
                case 15:
                    memset(&mpStringBuffer->masterKey, 0, sizeof(mpStringBuffer->masterKey));
                    break;
                case 16:
                    memset(&mpStringBuffer->asterisks, 0, sizeof(mpStringBuffer->asterisks));
                    break;
            }
        }

        void Setting::initMessage() {
            OSReport("initMessage pageId:%d\n", mpWiiSettingData->data[0x12]);
            mpWiiSettingData->data[0x12] = 0;
        }

        void Setting::initKeyboard(const char* text) {
            OSReport("initKeyboard formId:%d\n", mpWiiSettingData->data[0x11]);
            memset(unk_0x938, 0, sizeof(unk_0x938));

            int invalidInput = 0;
            keyboard::Manager::KeyboardType keyboardType = keyboard::Manager::LETTER;
            int rowLimit = 0;
            int stringLimit = 0;
            int productArea = SCGetProductArea();

            switch (mpWiiSettingData->data[0x11]) {
                case 1:
                    stringLimit = 10;
                    rowLimit = 6;
                    break;
                case 2:
                    if (ncd::NCDSetting::getPrivacyMode() == 1) {
                        stringLimit = 0x1A;
                        keyboardType = keyboard::Manager::NORMAL_WITHOUT_LINEFEED;
                    } else {
                        stringLimit = 0x40;
                        keyboardType = keyboard::Manager::NORMAL_WITHOUT_LINEFEED_WITH_SIGN;
                    }
                    rowLimit = 7;
                    break;
                case 3:
                    stringLimit = 0x20;
                    keyboardType = keyboard::Manager::NORMAL_WITHOUT_LINEFEED;
                    rowLimit = 7;
                    break;
                case 12:
                    stringLimit = 0x20;
                    keyboardType = keyboard::Manager::NORMAL_WITHOUT_LINEFEED;
                    rowLimit = 7;
                    break;
                case 13:
                    stringLimit = 0x20;
                    keyboardType = keyboard::Manager::NORMAL_WITHOUT_LINEFEED;
                    rowLimit = 7;
                    break;
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                    stringLimit = 0xF;
                    rowLimit = 10;
                    break;
                case 10:
                    stringLimit = 0xFF;
                    keyboardType = keyboard::Manager::NUMERIC_WITH_DOT;
                    rowLimit = 7;
                    break;
                case 11:
                case 20:
                    stringLimit = 5;
                    rowLimit = 3;
                    break;
                case 14:
                case 15:
                case 16:
                case 17:
                    stringLimit = 4;
                    rowLimit = 3;
                    break;
                case 18:
                case 19:
                    stringLimit = 0x20;
                    keyboardType = keyboard::Manager::NORMAL_WITHOUT_LINEFEED;
                    rowLimit = productArea == 11 || productArea == 6 ? 13 : 5;
                    break;
                case 22:
                    stringLimit = 0x40;
                    keyboardType = keyboard::Manager::NORMAL_WITHOUT_LINEFEED_WITH_SIGN;
                    rowLimit = 7;
                    break;
            }

            if (mpWiiSettingData->data[0x11] != 13 && mpWiiSettingData->data[0x11] != 2 &&
                mpWiiSettingData->data[0x11] != 18 && mpWiiSettingData->data[0x11] != 19 &&
                mpWiiSettingData->data[0x11] != 22) {
                utility::CharacterCode::UTF8ToUTF16(reinterpret_cast<wchar_t*>(unk_0x938), text, 0x101);
            }

            size_t textLength = wcslen(reinterpret_cast<wchar_t*>(unk_0x938));
            OSReport("キーボード: %d %d %d %d\n", rowLimit, stringLimit, keyboardType, textLength);
            reinterpret_cast<wchar_t*>(unk_0x938)[stringLimit] = 0;

            if (mpWiiSettingData->data[0x11] >= 4 && mpWiiSettingData->data[0x11] <= 8) {
                invalidInput = checkIPString(reinterpret_cast<const wchar_t*>(unk_0x938));
            } else if ((mpWiiSettingData->data[0x11] > 0 && mpWiiSettingData->data[0x11] < 4) ||
                       (mpWiiSettingData->data[0x11] >= 10 && mpWiiSettingData->data[0x11] <= 20) ||
                       mpWiiSettingData->data[0x11] == 22) {
                invalidInput = checkInputString(reinterpret_cast<const wchar_t*>(unk_0x938));
            }

            if (invalidInput != 0) {
                memset(unk_0x938, 0, sizeof(unk_0x938));
            }

            keyboard::Manager* keyboardManager = System::getKeyboard();
            if (productArea == 11) {
                keyboardManager->memoFrm()->setZiDictionary(keyboardManager->getZiOemDic(), keyboardManager->getZiSystemDic());
            }

            keyboard::Manager::KeyboardSetting setting;
            setting.type = keyboardType;
            setting.wcString = reinterpret_cast<const wchar_t*>(unk_0x938);
            setting.stringLimit = stringLimit;
            setting.rowLimit = rowLimit;
            keyboardManager->init();
            keyboardManager->start(0, setting);

            if (invalidInput != 0) {
                setDefaultBackString();
            } else {
                reinterpret_cast<textinput::inputform::Base*>(keyboardManager->memoFrm())->setString(reinterpret_cast<const wchar_t*>(unk_0x938));
            }
        }

        void Setting::calcKeyboard() {
            char* formText;
            if (mKeyboardState.iplType == keyboard::Manager::STATE_DISAPPEARING) {
                if (mKeyboardState.pressOK) {
                    onTextInputOK();
                    u8 formId = mpWiiSettingData->data[0x11];
                    formText = NULL;
                    switch (formId) {
                        case 1:
                            formText = mpStringBuffer->nickname;
                            break;
                        case 2:
                        case 22:
                            formText = mpStringBuffer->securityKey;
                            break;
                        case 3:
                            formText = mpStringBuffer->securityKey;
                            break;
                        case 4:
                            formText = mpStringBuffer->ip.addr;
                            break;
                        case 5:
                            formText = mpStringBuffer->ip.netmask;
                            break;
                        case 6:
                            formText = mpStringBuffer->ip.gateway;
                            break;
                        case 7:
                            formText = mpStringBuffer->dns1;
                            break;
                        case 8:
                            formText = mpStringBuffer->dns2;
                            break;
                        case 10:
                            formText = mpStringBuffer->proxy.server;
                            break;
                        case 11:
                            formText = mpStringBuffer->proxy.port;
                            break;
                        case 12:
                            formText = mpStringBuffer->proxyBasic.uname;
                            break;
                        case 13:
                            formText = mpStringBuffer->proxyBasic.pass;
                            break;
                        case 14:
                            formText = mpStringBuffer->adjMtu;
                            break;
                        case 15:
                            formText = mpStringBuffer->parentalPass;
                            break;
                        case 16:
                            formText = mpStringBuffer->parentalRePass;
                            break;
                        case 17:
                            formText = mpStringBuffer->parentalJudgePass;
                            break;
                        case 18:
                            formText = mpStringBuffer->parentalSecA;
                            break;
                        case 19:
                            formText = mpStringBuffer->parentalReSecA;
                            break;
                        case 20:
                            formText = mpStringBuffer->masterKey;
                            break;
                    }
                    OSReport("formID:%d %s\n", formId, formText);
                    if (strlen(formText) == 0) {
                        formText[0] = 0;
                        ext_ead::www::SurfaceManager::GetInstance()->GetBrowserThread()->CommitIme(mpBrowserData, formText);
                        memset(mpStringBuffer->asterisks, 0, sizeof(mpStringBuffer->asterisks));
                    } else if (formId == 2 || formId == 22) {
                        memcpy(mpStringBuffer->asterisks, mpStringBuffer->securityKey, sizeof(mpStringBuffer->securityKey));
                        mpStringBuffer->asterisks[0x41] = 0;
                        u32 index = 0;
                        while (mpStringBuffer->asterisks[index] != 0) {
                            mpStringBuffer->asterisks[index++] = '*';
                        }
                        if (index > 0x20) {
                            mpStringBuffer->asterisks[0x20] = '\n';
                            mpStringBuffer->asterisks[index] = '*';
                        }
                        ext_ead::www::SurfaceManager::GetInstance()->GetBrowserThread()->CommitIme(mpBrowserData, mpStringBuffer->asterisks);
                    } else {
                        ext_ead::www::SurfaceManager::GetInstance()->GetBrowserThread()->CommitIme(mpBrowserData, formText);
                    }
                } else {
                    u8 formId = mpWiiSettingData->data[0x11];
                    formText = NULL;
                    switch (formId) {
                        case 1:
                            formText = mpStringBuffer->nickname;
                            break;
                        case 2:
                        case 22:
                            formText = mpStringBuffer->asterisks;
                            break;
                        case 3:
                            formText = mpStringBuffer->securityKey;
                            break;
                        case 4:
                            formText = mpStringBuffer->ip.addr;
                            break;
                        case 5:
                            formText = mpStringBuffer->ip.netmask;
                            break;
                        case 6:
                            formText = mpStringBuffer->ip.gateway;
                            break;
                        case 7:
                            formText = mpStringBuffer->dns1;
                            break;
                        case 8:
                            formText = mpStringBuffer->dns2;
                            break;
                        case 10:
                            formText = mpStringBuffer->proxy.server;
                            break;
                        case 11:
                            formText = mpStringBuffer->proxy.port;
                            break;
                        case 12:
                            formText = mpStringBuffer->proxyBasic.uname;
                            break;
                        case 13:
                            formText = mpStringBuffer->proxyBasic.pass;
                            break;
                        case 14:
                            formText = mpStringBuffer->adjMtu;
                            break;
                        case 15:
                            formText = mpStringBuffer->parentalPass;
                            break;
                        case 16:
                            formText = mpStringBuffer->parentalRePass;
                            break;
                        case 17:
                            formText = mpStringBuffer->parentalJudgePass;
                            break;
                        case 18:
                            formText = mpStringBuffer->parentalSecA;
                            break;
                        case 19:
                            formText = mpStringBuffer->parentalReSecA;
                            break;
                        case 20:
                            formText = mpStringBuffer->masterKey;
                            break;
                    }
                    ext_ead::www::SurfaceManager::GetInstance()->GetBrowserThread()->CommitIme(mpBrowserData, formText);
                }

                mpWiiSettingData->data[0x11] = 0;
                ext_ead::www::SurfaceManager::GetInstance()->GetBrowserThread()->DisposeImeData(mpBrowserData);
            } else if (mKeyboardState.iplType < keyboard::Manager::STATE_VISIBLE) {
                u8 formId = mpWiiSettingData->data[0x11];
                if (mKeyboardState.iplType < keyboard::Manager::STATE_APPEARING &&
                    formId != 0 && formId != 9 && formId != 21 && formId <= 22) {
                    if (System::getKeyboard()->memoMgr()->isVacancy()) {
                        reinterpret_cast<textinput::inputform::Base*>(System::getKeyboard()->memoFrm())->setString(L"");
                    } else {
                        setDefaultBackString();
                    }
                }
            } else if (mKeyboardState.iplType < keyboard::Manager::STATE_HIDDEN_AFTER_DISAPPEAR) {
                reinterpret_cast<textinput::inputform::Base*>(System::getKeyboard()->memoFrm())->setString(L"");
                unk_0x74 = 0;
            }

            mKeyboardState = *System::getKeyboard()->getState();
        }

        void Setting::calcSetting() {
            OSReport("setstring:%d\n", mpWiiSettingData->data[0x36]);
            u8 settingId = mpWiiSettingData->data[0x36];
            switch (settingId) {
                case 1:
                    setDisPos();
                    break;
                case 2:
                    setNickName();
                    break;
                case 3:
                    setSecurityKey();
                    break;
                case 4:
                    setSSID();
                    break;
                case 5:
                    setIP();
                    break;
                case 6:
                    setDNS();
                    break;
                case 7:
                    setProxy();
                    break;
                case 8:
                    setBasic();
                    break;
                case 9:
                    setMTU();
                    break;
                case 10:
                    setParePass();
                    break;
                case 11:
                    setPareRePass();
                    break;
                case 12:
                    setPareJudgePass();
                    break;
                case 13:
                    setSecA();
                    break;
                case 14:
                    setReSecA();
                    break;
                case 15:
                    setMasterKey();
                    break;
            }
            mpWiiSettingData->data[0x36] = 0;
        }

        void Setting::onTextInputOK() {
            OSReport("Keyboard Confirm:%d\n", mpWiiSettingData->data[0x11]);
            wcslen(mKeyboardState.wcString);

            memset(unk_0x938, 0, sizeof(unk_0x938));
            u8 convertedText[0x302];
            memset(convertedText, 0, sizeof(convertedText));
            memcpy(unk_0x938, mKeyboardState.wcString, sizeof(unk_0x938));
            u8 formId = mpWiiSettingData->data[0x11];

            if (formId == 2 || formId == 22) {
                utility::CharacterCode::UTF16ToANSI(convertedText, reinterpret_cast<const wchar_t*>(unk_0x938), 0x100);
                memset(convertedText + wcslen(reinterpret_cast<const wchar_t*>(unk_0x938)), 0,
                       0x100 - wcslen(reinterpret_cast<const wchar_t*>(unk_0x938)));
                memcpy(mpStringBuffer->securityKey, convertedText, sizeof(mpStringBuffer->securityKey));
                return;
            }

            if (formId == 18 || formId == 19) {
                adjustSecA(reinterpret_cast<wchar_t*>(unk_0x938));
            }
            utility::CharacterCode::UTF16ToUTF8(reinterpret_cast<char*>(convertedText),
                                                reinterpret_cast<const wchar_t*>(unk_0x938), 0x301);

            switch (mpWiiSettingData->data[0x11]) {
                case 1:
                    memcpy(mpStringBuffer->nickname, convertedText, sizeof(mpStringBuffer->nickname));
                    break;
                case 3:
                    memcpy(mpStringBuffer->ssid, convertedText, sizeof(mpStringBuffer->ssid));
                    break;
                case 4:
                    memcpy(mpStringBuffer->ip.addr, convertedText, sizeof(mpStringBuffer->ip.addr));
                    break;
                case 5:
                    memcpy(mpStringBuffer->ip.netmask, convertedText, sizeof(mpStringBuffer->ip.netmask));
                    break;
                case 6:
                    memcpy(mpStringBuffer->ip.gateway, convertedText, sizeof(mpStringBuffer->ip.gateway));
                    break;
                case 7:
                    memcpy(mpStringBuffer->dns1, convertedText, sizeof(mpStringBuffer->dns1));
                    break;
                case 8:
                    memcpy(mpStringBuffer->dns2, convertedText, sizeof(mpStringBuffer->dns2));
                    break;
                case 10:
                    memcpy(mpStringBuffer->proxy.server, convertedText, sizeof(mpStringBuffer->proxy.server));
                    break;
                case 11:
                    memcpy(mpStringBuffer->proxy.port, convertedText, sizeof(mpStringBuffer->proxy.port));
                    break;
                case 12:
                    memcpy(mpStringBuffer->proxyBasic.uname, convertedText, sizeof(mpStringBuffer->proxyBasic.uname));
                    break;
                case 13:
                    memcpy(mpStringBuffer->proxyBasic.pass, convertedText, sizeof(mpStringBuffer->proxyBasic.pass));
                    break;
                case 15:
                    memcpy(mpStringBuffer->parentalPass, convertedText, sizeof(mpStringBuffer->parentalPass));
                    break;
                case 16:
                    memcpy(mpStringBuffer->parentalRePass, convertedText, sizeof(mpStringBuffer->parentalRePass));
                    break;
                case 17:
                    memcpy(mpStringBuffer->parentalJudgePass, convertedText, sizeof(mpStringBuffer->parentalJudgePass));
                    break;
                case 18:
                    memcpy(mpStringBuffer->parentalSecA, convertedText, sizeof(mpStringBuffer->parentalSecA));
                    break;
                case 19:
                    memcpy(mpStringBuffer->parentalReSecA, convertedText, sizeof(mpStringBuffer->parentalReSecA));
                    break;
                case 20:
                    memcpy(mpStringBuffer->masterKey, convertedText, sizeof(mpStringBuffer->masterKey));
                    break;
                case 14:
                    memcpy(mpStringBuffer->adjMtu, convertedText, sizeof(mpStringBuffer->adjMtu));
                    break;
            }
        }

        void Setting::initNickName() {
            bool nicknameExists = SCGetOwnerNickName(reinterpret_cast<SCOwnerNickname*>(mSettingData)) != 0;
            OSReport("SCGetOwnerNickName:%d\n", nicknameExists);
            if (nicknameExists) {
                SCOwnerNickname* ownerNickname = reinterpret_cast<SCOwnerNickname*>(mSettingData);
                    memcpy(unk_0x938, mSettingData, ownerNickname->length * sizeof(wchar_t));
            }
            memset(mpStringBuffer->nickname, 0, sizeof(mpStringBuffer->nickname));
            utility::CharacterCode::UTF16ToUTF8(mpStringBuffer->nickname,
                                                reinterpret_cast<const wchar_t*>(unk_0x938),
                                                sizeof(mpStringBuffer->nickname));
        }

        void Setting::initSecurityKey() {
            memset(mpStringBuffer->securityKey, 0, sizeof(mpStringBuffer->securityKey));
            s32 privacyMode = ncd::NCDSetting::getNCDPrivacyMode();
            size_t keyLength;
            if (privacyMode != 2) {
                if (privacyMode < 2) {
                    if (privacyMode == 0) {
                        keyLength = 0;
                    } else {
                        keyLength = 5;
                    }
                } else if (privacyMode < 7 && privacyMode > 3) {
                    keyLength = 64;
                } else {
                    keyLength = 0;
                }
            } else {
                keyLength = 13;
            }
            if (keyLength != 0) {
                memcpy(mpStringBuffer->securityKey, ncd::NCDSetting::getPrivacy(), keyLength);
            }
            OSReport("privacy : %s\n", ncd::NCDSetting::getPrivacy());
        }

        void Setting::initSSID() {
            memset(mpStringBuffer->ssid, 0, sizeof(mpStringBuffer->ssid));
            u16 stringLength = ncd::NCDSetting::getSSID()->ssidLength;
            utility::CharacterCode::ANSIToUTF8(mpStringBuffer->ssid, ncd::NCDSetting::getSSID()->ssid, stringLength);
            u16 reportLength = ncd::NCDSetting::getSSID()->ssidLength;
            OSReport("initHTMLText initString:%s length:%d\n", ncd::NCDSetting::getSSID()->ssid, reportLength);
        }

        void Setting::initIP() {
            memset(mpStringBuffer->ip.addr, 0, sizeof(mpStringBuffer->ip.addr));
            memset(mpStringBuffer->ip.netmask, 0, sizeof(mpStringBuffer->ip.netmask));
            memset(mpStringBuffer->ip.gateway, 0, sizeof(mpStringBuffer->ip.gateway));
            convertIP(mpStringBuffer->ip.addr, ncd::NCDSetting::getIP()->addr);
            convertIP(mpStringBuffer->ip.netmask, ncd::NCDSetting::getIP()->netmask);
            convertIP(mpStringBuffer->ip.gateway, ncd::NCDSetting::getIP()->gateway);
        }

        void Setting::initDNS() {
            memset(mpStringBuffer->dns1, 0, sizeof(mpStringBuffer->dns1));
            memset(mpStringBuffer->dns2, 0, sizeof(mpStringBuffer->dns2));
            convertIP(mpStringBuffer->dns1, ncd::NCDSetting::getIP()->dns1);
            convertIP(mpStringBuffer->dns2, ncd::NCDSetting::getIP()->dns2);
        }

        void Setting::initProxy() {
            memset(mpStringBuffer->proxy.server, 0, sizeof(mpStringBuffer->proxy.server));
            memset(mpStringBuffer->proxy.port, 0, sizeof(mpStringBuffer->proxy.port));
            memcpy(mpStringBuffer->proxy.server, ncd::NCDSetting::getProxy()->http.server,
                   sizeof(ncd::NCDSetting::getProxy()->http.server));
            sprintf(mpStringBuffer->proxy.port, "%d", ncd::NCDSetting::getProxy()->http.port);
        }

        void Setting::initBasic() {
            memset(mpStringBuffer->proxyBasic.uname, 0, sizeof(mpStringBuffer->proxyBasic.uname));
            memset(mpStringBuffer->proxyBasic.pass, 0, sizeof(mpStringBuffer->proxyBasic.pass));
            memcpy(mpStringBuffer->proxyBasic.uname, ncd::NCDSetting::getProxy()->http.username,
                   sizeof(ncd::NCDSetting::getProxy()->http.username));
            memcpy(mpStringBuffer->proxyBasic.pass, ncd::NCDSetting::getProxy()->http.password,
                   sizeof(ncd::NCDSetting::getProxy()->http.password));
        }

        void Setting::initMTU() {
            memset(mpStringBuffer->adjMtu, 0, sizeof(mpStringBuffer->adjMtu));
            char mtuText[12];
            sprintf(mtuText, "%d", ncd::NCDSetting::getMTU());
            utility::CharacterCode::ANSIToUTF8(mpStringBuffer->adjMtu,
                                               reinterpret_cast<const u8*>(mtuText));
        }

        void Setting::initSecA() {
            memset(mpStringBuffer->parentalSecA, 0, sizeof(mpStringBuffer->parentalSecA));
            wchar_t answer[34];
            memset(answer, 0, 0x44);
            wcsncpy(answer, parental::Parental::getSecA(), 0x20);
            memset(unk_0x938, 0, sizeof(unk_0x938));
            wcsncpy(reinterpret_cast<wchar_t*>(unk_0x938), answer, 0x20);
            adjustSecA(answer);
            utility::CharacterCode::UTF16ToUTF8(mpStringBuffer->parentalSecA, answer,
                                                sizeof(mpStringBuffer->parentalSecA));
        }

        void Setting::initVersion() {
            const char* versionSuffix[12] = {"J", "U", "E", "", "", "J", "K", "", "", "", "", "C"};
            u32 versionData[24] = {
                0x00010008, 0x48414B4A, 0x00010008, 0x48414B45, 0x00010008, 0x48414B50,
                0, 0, 0, 0, 0, 0, 0x00010008, 0x48414B4A, 0x00010008, 0x48414B4B,
                0, 0, 0, 0, 0, 0, 0x00010008, 0x48414B43,
            };
            u32 region = System::getRegion();
            sprintf(mpStringBuffer->version, "Ver. %d.%d%s", 4, 3, versionSuffix[region]);
            mUpdateTitleId = *reinterpret_cast<ESTitleId*>(&versionData[region * 2]);
        }

        void Setting::setDisPos() {
            int displayPosition = 0x10 - mpWiiSettingData->data[7];
            __VISetAdjustingValues(static_cast<char>(displayPosition), 0);
        }

        void Setting::setNickName() {
            reinterpret_cast<SCOwnerNickname*>(mSettingData)->length = wcslen(reinterpret_cast<const wchar_t*>(unk_0x938));
            if (checkTextNum(mpStringBuffer->nickname) == 3) {
                memset(mSettingData, 0, sizeof(reinterpret_cast<SCOwnerNickname*>(mSettingData)->name));
                memcpy(mSettingData, unk_0x938,
                       reinterpret_cast<SCOwnerNickname*>(mSettingData)->length * sizeof(wchar_t));
                bool written = SCSetOwnerNickName(reinterpret_cast<SCOwnerNickname*>(mSettingData)) != 0;
                OSReport("nicknameFlag:1 %d %s\n", written,
                         reinterpret_cast<SCOwnerNickname*>(mSettingData)->name);
            }
        }

        void Setting::setSecurityKey() {
            int keyLength = ncd::NCDSetting::checkWEPKey(mpStringBuffer->securityKey);
            if (keyLength >= 0) {
                www::wiisetting::setFuncResult(3);
                ncd::NCDSetting::setPrivacy(reinterpret_cast<u8*>(mpStringBuffer->securityKey), keyLength);
                OSReport("securityFlag:1 %s\n", mpStringBuffer->securityKey);
            } else {
                System::getDialog()->callBtn0(0x1be, 0xb4, false);
                unk_0x74 = 2;
                www::wiisetting::setFuncResult(4);
            }
        }

        void Setting::setSSID() {
            u8 ssid[0x61];
            memset(ssid, 0, sizeof(ssid));
            utility::CharacterCode::UTF8ToANSI(ssid, mpStringBuffer->ssid);
            memset(ssid + 0x20, 0, 0x41);
            ncd::NCDSetting::setSSID(ssid);
        }

        void Setting::setIP() {
            NCDIpProfile ip;
            memset(&ip, 0, sizeof(ip));
            convertRevIP(ip.addr, mpStringBuffer->ip.addr);
            convertRevIP(ip.netmask, mpStringBuffer->ip.netmask);
            convertRevIP(ip.gateway, mpStringBuffer->ip.gateway);
            ncd::NCDSetting::setIP(&ip);
        }

        void Setting::setDNS() {
            NCDIpProfile ip;
            memset(&ip, 0, sizeof(ip));
            convertRevIP(ip.dns1, mpStringBuffer->dns1);
            convertRevIP(ip.dns2, mpStringBuffer->dns2);
            ncd::NCDSetting::setDNS(&ip);
        }

        void Setting::setProxy() {
            NCDProxyServerProfile proxy;
            const char* portString = mpStringBuffer->proxy.port;
            wchar_t portText[6];
            u32 port;
            memset(portText, 0, sizeof(portText));
            utility::CharacterCode::UTF8ToUTF16(portText, portString, 6);
            utility::CharacterCode::UTF16ToU32(&port, portText);
            proxy.port = port;
            if (proxy.port == 0) {
                www::wiisetting::setFuncResult(4);
                System::getDialog()->callBtn0(0x1be, 0xb4, false);
                unk_0x74 = 2;
            } else {
                if (ncd::NCDSetting::checkProxy(mpStringBuffer->proxy.server) != 0) {
                    www::wiisetting::setFuncResult(3);
                    memset(proxy.server, 0, sizeof(proxy.server));
                    utility::CharacterCode::UTF8ToANSI(reinterpret_cast<u8*>(proxy.server),
                                                       mpStringBuffer->proxy.server);
                    ncd::NCDSetting::setProxy(&proxy);
                } else {
                    www::wiisetting::setFuncResult(4);
                    System::getDialog()->callBtn0(0x1be, 0xb4, false);
                    unk_0x74 = 2;
                }
            }
        }

        void Setting::setBasic() {
            if (ncd::NCDSetting::checkProxyBasic(mpStringBuffer->proxyBasic.uname) != 0 &&
                ncd::NCDSetting::checkProxyBasic(mpStringBuffer->proxyBasic.pass) != 0) {
                NCDProxyServerProfile proxy;
                www::wiisetting::setFuncResult(3);
                memset(&proxy, 0, sizeof(proxy));
                utility::CharacterCode::UTF8ToANSI(reinterpret_cast<u8*>(proxy.username),
                                                   mpStringBuffer->proxyBasic.uname);
                utility::CharacterCode::UTF8ToANSI(reinterpret_cast<u8*>(proxy.password),
                                                   mpStringBuffer->proxyBasic.pass);
                ncd::NCDSetting::setBasic(&proxy);
            } else {
                www::wiisetting::setFuncResult(4);
                System::getDialog()->callBtn0(0x1be, 0xb4, false);
                unk_0x74 = 2;
            }
        }

        void Setting::setMTU() {
            const char* mtuString = mpStringBuffer->adjMtu;
            wchar_t mtuText[6];
            u32 parsedMtu;
            memset(mtuText, 0, sizeof(mtuText));
            utility::CharacterCode::UTF8ToUTF16(mtuText, mtuString, 6);
            utility::CharacterCode::UTF16ToU32(&parsedMtu, mtuText);
            s32 mtu = parsedMtu & 0xffff;
            if (mtu < 0x240 || mtu > 0x5dc) {
                mtu = 0;
            }
            ncd::NCDSetting::setMTU(mtu);
            mpWiiSettingData->data[0x36] = 0;
        }

        void Setting::setParePass() {
            char password[5];
            memset(password, 0, 5);
            utility::CharacterCode::UTF8ToANSI(reinterpret_cast<u8*>(password), mpStringBuffer->parentalPass);
            if (checkTextNum(password) == 3) {
                parental::Parental::setPass(password);
            }
            memset(mpStringBuffer->parentalPass, 0, 5);
        }

        void Setting::setPareRePass() {
            char password[16];
            u8 result = 2;
            memset(password, 0, 5);
            utility::CharacterCode::UTF8ToANSI(reinterpret_cast<u8*>(password), mpStringBuffer->parentalRePass);
            if (checkTextNum(password) == 3 && parental::Parental::checkPass(password)) {
                result = 1;
            }
            www::wiisetting::setFuncResult(result);
            memset(mpStringBuffer->parentalRePass, 0, 5);
        }

        void Setting::setPareJudgePass() {
            char password[16];
            u8 result = 2;
            memset(password, 0, 5);
            utility::CharacterCode::UTF8ToANSI(reinterpret_cast<u8*>(password), mpStringBuffer->parentalJudgePass);
            if (checkTextNum(password) == 3 && parental::Parental::judgePass(password)) {
                result = 1;
            }
            www::wiisetting::setFuncResult(result);
            memset(mpStringBuffer->parentalJudgePass, 0, 5);
        }

        void Setting::setSecA() {
            memset(unk_0x938, 0, sizeof(unk_0x938));
            utility::CharacterCode::UTF8ToUTF16(reinterpret_cast<wchar_t*>(unk_0x938),
                                                mpStringBuffer->parentalSecA, 0x44);
            reAdjustSecA();
            if (checkTextNum(NULL) == 3) {
                parental::Parental::setSecA(reinterpret_cast<const wchar_t*>(unk_0x938));
            }
            memset(unk_0x938, 0, sizeof(unk_0x938));
        }

        void Setting::setReSecA() {
            u8 result = 2;
            memset(unk_0x938, 0, sizeof(unk_0x938));
            utility::CharacterCode::UTF8ToUTF16(reinterpret_cast<wchar_t*>(unk_0x938),
                                                mpStringBuffer->parentalReSecA, 0x44);
            reAdjustSecA();
            if (checkTextNum(NULL) == 3 && parental::Parental::judgeSecA(reinterpret_cast<const wchar_t*>(unk_0x938))) {
                result = 1;
            }
            www::wiisetting::setFuncResult(result);
            memset(unk_0x938, 0, sizeof(unk_0x938));
        }

        void Setting::setMasterKey() {
            char masterKey[16];
            u8 result = 2;
            memset(masterKey, 0, 6);
            if (checkTextNum(mpStringBuffer->masterKey) == 3) {
                utility::CharacterCode::UTF8ToANSI(reinterpret_cast<u8*>(masterKey), mpStringBuffer->masterKey);
                if (parental::Parental::judgeMaster(masterKey)) {
                    result = 1;
                }
                www::wiisetting::setFuncResult(result);
            }
            memset(mpStringBuffer->masterKey, 0, 6);
        }

        u8 Setting::checkTextNum(const char* text) {
            u8 formId = mpWiiSettingData->data[0x36];
            u32 message = 0;
            u8 result = 4;
            if (formId < 13) {
                if (formId == 2) {
                    size_t length = wcslen(reinterpret_cast<const wchar_t*>(unk_0x938));
                    if (length == 0) {
                        message = 0x1c0;
                    } else if (checkSpace()) {
                        result = 3;
                    } else {
                        message = 0x1c1;
                    }
                } else if (formId > 9) {
                    if (strlen(text) == 4) {
                        result = 3;
                    }
                    message = 0x1ba;
                }
            } else if (formId == 15) {
                if (strlen(text) == 5) {
                    result = 3;
                }
                message = 0x1bc;
            } else if (formId <= 14) {
                u32 region = System::getRegion();
                u32 minimum = 6;
                if (region == 6) {
                    minimum = 2;
                } else if (region == 0 || region == 11) {
                    minimum = 3;
                }
                size_t length = wcslen(reinterpret_cast<const wchar_t*>(unk_0x938));
                if (length < minimum) {
                    message = 0x1bb;
                } else if (checkSpace()) {
                    result = 3;
                } else {
                    message = 0x1c1;
                }
            }
            www::wiisetting::setFuncResult(result);
            if (result == 4) {
                System::getDialog()->callBtn0(message, 0xb4, false);
                unk_0x74 = 2;
            }
            return result;
        }

        bool Setting::checkSpace() {
            const wchar_t* text = reinterpret_cast<const wchar_t*>(unk_0x938);
            while (*text != 0) {
                if (*text != L' ' && *text != 0x3000) {
                    return true;
                }
                ++text;
            }
            return false;
        }

        void Setting::convertIP(char* destination, const u8* address) {
            char ascii[20];
            sprintf(ascii, "%03d.%03d.%03d.%03d", address[0], address[1], address[2], address[3]);
            utility::CharacterCode::ANSIToUTF8(destination, reinterpret_cast<const u8*>(ascii));
        }

        void Setting::convertRevIP(u8* destination, const char* address) {
            char ascii[20];
            memset(ascii, 0, sizeof(ascii));
            utility::CharacterCode::UTF8ToANSI(reinterpret_cast<u8*>(ascii), address);
            char* component = ascii;
            u32 count = 0;
            for (char* current = ascii;; ++current) {
                if (*current == '.' || *current == 0) {
                    bool finished = *current == 0;
                    *current = 0;
                    u32 value = atoi(component);
                    if (value > 0xff) {
                        value = 0xff;
                    }
                    destination[count++] = value;
                    if (finished || count == 4) {
                        break;
                    }
                    component = current + 1;
                }
            }
        }

        void Setting::adjustSecA(wchar_t* text) {
            u32 index = 0;
            bool containsWideCharacter = false;
            for (; text[index] != 0; ++index) {
                if (text[index] > 0x7f) {
                    containsWideCharacter = true;
                    break;
                }
            }
            if (containsWideCharacter && wcslen(reinterpret_cast<const wchar_t*>(unk_0x938)) > 0x10) {
                char secondLine[0x22];
                SettingSecAText* lines = reinterpret_cast<SettingSecAText*>(text);
                memcpy(secondLine, lines->wrappedLine, 0x22);
                memcpy(&lines->wrappedLine[1], secondLine, 0x22);
                lines->wrappedLine[0] = L'\n';
            }
        }

        void Setting::reAdjustSecA() {
            wchar_t* text = reinterpret_cast<wchar_t*>(unk_0x938);
            bool containsWideCharacter = false;
            for (u32 i = 0; text[i] != 0; ++i) {
                if (text[i] > 0x7f) {
                    containsWideCharacter = true;
                    break;
                }
            }
            if (containsWideCharacter && wcslen(text) > 0x10) {
                char secondLine[0x22];
                SettingSecAText* lines = reinterpret_cast<SettingSecAText*>(text);
                memcpy(secondLine, &lines->wrappedLine[1], 0x22);
                memcpy(lines->wrappedLine, secondLine, 0x22);
            }
        }

        void Setting::setDefaultBackString() {
            switch (mpWiiSettingData->data[0x11]) {
                case 1:
                    reinterpret_cast<textinput::inputform::Base*>(System::getKeyboard()->memoFrm())->setString(System::getMessage(0x15c));
                    break;
                case 2:
                    reinterpret_cast<textinput::inputform::Base*>(System::getKeyboard()->memoFrm())->setString(System::getMessage(0x153));
                    break;
                case 3:
                    reinterpret_cast<textinput::inputform::Base*>(System::getKeyboard()->memoFrm())->setString(System::getMessage(0x152));
                    break;
                case 4:
                    reinterpret_cast<textinput::inputform::Base*>(System::getKeyboard()->memoFrm())->setString(System::getMessage(0x14d));
                    break;
                case 5:
                    reinterpret_cast<textinput::inputform::Base*>(System::getKeyboard()->memoFrm())->setString(System::getMessage(0x150));
                    break;
                case 6:
                    reinterpret_cast<textinput::inputform::Base*>(System::getKeyboard()->memoFrm())->setString(System::getMessage(0x151));
                    break;
                case 7:
                    reinterpret_cast<textinput::inputform::Base*>(System::getKeyboard()->memoFrm())->setString(System::getMessage(0x14e));
                    break;
                case 8:
                    reinterpret_cast<textinput::inputform::Base*>(System::getKeyboard()->memoFrm())->setString(System::getMessage(0x14f));
                    break;
                case 10:
                    reinterpret_cast<textinput::inputform::Base*>(System::getKeyboard()->memoFrm())->setString(System::getMessage(0x154));
                    break;
                case 11:
                    reinterpret_cast<textinput::inputform::Base*>(System::getKeyboard()->memoFrm())->setString(System::getMessage(0x155));
                    break;
                case 12:
                    reinterpret_cast<textinput::inputform::Base*>(System::getKeyboard()->memoFrm())->setString(System::getMessage(0x156));
                    break;
                case 13:
                    reinterpret_cast<textinput::inputform::Base*>(System::getKeyboard()->memoFrm())->setString(System::getMessage(0x157));
                    break;
                case 14:
                    reinterpret_cast<textinput::inputform::Base*>(System::getKeyboard()->memoFrm())->setString(System::getMessage(0x158));
                    break;
                case 15:
                case 16:
                case 17:
                    reinterpret_cast<textinput::inputform::Base*>(System::getKeyboard()->memoFrm())->setString(System::getMessage(0x159));
                    break;
                case 18:
                case 19:
                    reinterpret_cast<textinput::inputform::Base*>(System::getKeyboard()->memoFrm())->setString(System::getMessage(0x15a));
                    break;
                case 20:
                    reinterpret_cast<textinput::inputform::Base*>(System::getKeyboard()->memoFrm())->setString(System::getMessage(0x15b));
                    break;
                case 22:
                    reinterpret_cast<textinput::inputform::Base*>(System::getKeyboard()->memoFrm())->setString(System::getMessage(0x153));
                    break;
            }
        }

        bool Setting::checkInputString(const wchar_t* text) {
            return *text == 0;
        }

        int Setting::checkIPString(const wchar_t* text) {
            wchar_t zeroAddress[16] = L"000.000.000.000";
            return memcmp(text, zeroAddress, sizeof(zeroAddress)) == 0 || checkInputString(text);
        }

        bool Setting::calcSafeMode() {
            if (System::getNwc24Manager() != NULL) {
                return true;
            }
            if (unk_0x94 == 1) {
                if (System::getDialog()->getLastResult() >= 0) {
                    unk_0xB9C = 1;
                    unk_0x74 = 0;
                    unk_0x94 = 0;
                }
            } else if (unk_0x94 == 0) {
                resetFuncMsgQ();
                System::getDialog()->callBtn1(0x21, 0x2e);
                www::wiisetting::setFuncResult(2);
                unk_0x74 = 0x11;
                unk_0x94 = 1;
            }
            return false;
        }

        void Setting::initAP() {
            unk_0x78 = 1;
            unk_0x914 = 0;
            unk_0x918 = -1;
        }

        void Setting::resetAP() {
            mpChangeLayout->getAnim(0x15)->initFrame();
            mpChangeLayout->getAnim(0x15)->restart();
            if (unk_0x914 != 0) {
                mpChangeLayout->getAnim(2)->initFrame();
                mpChangeLayout->getAnim(2)->restart();
            }
            if (mAPScanList.count != unk_0x914 + 4) {
                mpChangeLayout->getAnim(3)->initFrame();
                mpChangeLayout->getAnim(3)->restart();
            }
            for (int animation = 0x10; animation < 0x14; ++animation) {
                mpChangeLayout->getAnim(animation)->initFrame();
                mpChangeLayout->getAnim(animation)->restart();
            }
            initAP();
            unk_0x918 = 0x15;
            mpWiiSettingFlag->smthMsgData = 3;
            unk_0x78 = 9;
        }

        void Setting::redrawAP() {
            unk_0x78 = 4;
            unk_0x914 = 0;
            unk_0x918 = -1;
            mpWiiSettingFlag->smthMsgData = 3;
            mpChangeLayout->getAnim(0x14)->initFrame();
            for (int animation = 0x10; animation < 0x14; ++animation) {
                mpChangeLayout->getAnim(animation)->initFrame();
                mpChangeLayout->getAnim(animation)->restart();
            }
            mpChangeLayout->calc();
            unk_0x91C[2] = 0;
        }

        void Setting::scanAP() {
            switch (unk_0x78) {
                case 1:
                    memset(&mAPScanList.count, 0, 0x800);
                    mpAPScanThread->setResultData(reinterpret_cast<unsigned short*>(&mAPScanList.count));
                    memset(mpMem1BrowserBuffer, 0, 0x1000);
                    mpAPScanThread->Create(mpMem1BrowserBuffer, 0x1000, 0x12, true);
                    unk_0x78 = 2;
                    unk_0x91C[2] = 0;
                    break;
                case 2:
                    if (unk_0x91C[2] == 1) {
                        waitStart();
                    }
                    if (mpAPScanThread->IsThreadTerminated()) {
                        mpAPScanThread->WaitForThreadExit();
                        if (mAPScanList.count == 0) {
                            www::wiisetting::setFuncResult(2);
                            initAP();
                            mpChangeLayout->getAnim(0x14)->initAnmFrame();
                            mpChangeLayout->getAnim(0)->initAnmFrame();
                            mpChangeLayout->getAnim(1)->initAnmFrame();
                        } else {
                            www::wiisetting::setFuncResult(1);
                            setAPDraw();
                            unk_0x78 = 3;
                        }
                        resetFuncMsgQ();
                        unk_0xB9C = 0;
                        waitFinish();
                    }
                    break;
                case 3:
                    if (mpWiiSettingFlag->smthMsgData == 3) {
                        unk_0x78 = 4;
                        unk_0x91C[2] = 0;
                    }
                    break;
                case 4:
                    initScroll();
                    setAPDraw();
                    mpPaneManager->update();
                    break;
                case 5:
                    mpPaneManager->update();
                    break;
                case 6:
                    unk_0xB9C = 1;
                    if (!mpChangeLayout->getAnim(unk_0x918)->isPlaying()) {
                        unk_0x78 = 5;
                        setAPDraw();
                        mpChangeLayout->getAnim(unk_0x91C[0] == 0 ? 0xb : 0xa)->initAnmFrame();
                        if (unk_0x914 == 0) {
                            mpChangeLayout->FindPaneByName(sSettingAPNumberNames[0])->SetVisible(false);
                        } else if (unk_0x914 == 1) {
                            mpChangeLayout->FindPaneByName(sSettingAPNumberNames[0])->SetVisible(true);
                        }
                        if (mAPScanList.count == unk_0x914 + 4) {
                            mpChangeLayout->FindPaneByName(sSettingAPNumberNames[1])->SetVisible(false);
                        } else if (mAPScanList.count == unk_0x914 + 5) {
                            mpChangeLayout->FindPaneByName(sSettingAPNumberNames[1])->SetVisible(true);
                        }
                        mpChangeLayout->FindPaneByName(sSettingAPTextNames[0])->SetVisible(true);
                        mpChangeLayout->FindPaneByName(sSettingAPTextNames[1])->SetVisible(true);
                    }
                    break;
                case 7:
                    unk_0xB9C = 1;
                    if (!mpChangeLayout->getAnim(unk_0x918)->isPlaying()) {
                        updateScroll();
                        unk_0x78 = 6;
                    }
                    break;
                case 8:
                    resetAP();
                    unk_0x91C[2] = 0;
                    break;
                case 9:
                    if (!mpChangeLayout->getAnim(unk_0x918)->isPlaying()) {
                        resetFuncMsgQ();
                        unk_0x78 = 1;
                        unk_0x918 = -1;
                        mpPaneManager->update();
                        mpChangeLayout->getAnim(0x14)->initFrame();
                        mpChangeLayout->calc();
                    }
                    break;
            }
        }

        void Setting::initScroll() {
            if (unk_0x91C[2] == 0) {
                return;
            }
            for (int index = 1; index <= 4; ++index) {
                mpChangeLayout->FindPaneByName(sSettingAPNumberNames[index])->SetVisible(true);
            }
            u16 count = mAPScanList.count;
            if (count == 2) {
                mpChangeLayout->FindPaneByName(sSettingAPNumberNames[3])->SetVisible(false);
            } else if (count < 2) {
                if (count == 0) {
                    mpChangeLayout->FindPaneByName(sSettingAPNumberNames[1])->SetVisible(false);
                }
                mpChangeLayout->FindPaneByName(sSettingAPNumberNames[2])->SetVisible(false);
                mpChangeLayout->FindPaneByName(sSettingAPNumberNames[3])->SetVisible(false);
            }
            if (count < 4) {
                for (int index = 4; index < 6; ++index) {
                    mpChangeLayout->FindPaneByName(sSettingAPNumberNames[index])->SetVisible(false);
                }
                mpChangeLayout->FindPaneByName("N_AP7")->SetVisible(false);
            }
            mpChangeLayout->getAnim(0x14)->initFrame();
            mpChangeLayout->getAnim(0x14)->restart();
            mpChangeLayout->getAnim(0)->initAnmFrame();
            mpChangeLayout->FindPaneByName(sSettingAPPaneNames[0])->SetVisible(false);
            mpChangeLayout->FindPaneByName(sSettingAPPaneNames[1])->SetVisible(false);
            if (count > unk_0x914 + 4) {
                mpChangeLayout->FindPaneByName(sSettingAPPaneNames[3])->SetVisible(true);
                mpChangeLayout->getAnim(1)->initFrame();
                mpChangeLayout->getAnim(1)->restart();
                for (int index = 1; index < 6; ++index) {
                    mpChangeLayout->FindPaneByName(sSettingAPNumberNames[index])->SetVisible(true);
                }
            } else {
                mpChangeLayout->FindPaneByName(sSettingAPPaneNames[3])->SetVisible(false);
                for (int index = count + 1; index < 6; ++index) {
                    mpChangeLayout->FindPaneByName(sSettingAPNumberNames[index])->SetVisible(false);
                }
            }
            unk_0x78 = 6;
            unk_0x918 = 0x14;
            unk_0x91C[2] = 0;
        }

        void Setting::updateScroll() {
            if (unk_0x91C[0] == 0) {
                --unk_0x914;
                if (unk_0x914 == 0) {
                    mpChangeLayout->getAnim(2)->initFrame();
                    mpChangeLayout->getAnim(2)->restart();
                    mpChangeLayout->FindPaneByName(sSettingAPPaneNames[0])->SetVisible(false);
                }
                if (mAPScanList.count == unk_0x914 + 5) {
                    mpChangeLayout->getAnim(1)->initFrame();
                    mpChangeLayout->getAnim(1)->restart();
                    mpChangeLayout->FindPaneByName(sSettingAPPaneNames[1])->SetVisible(true);
                }
            } else {
                int previous = unk_0x914++;
                if (mAPScanList.count == previous + 5) {
                    mpChangeLayout->getAnim(3)->initFrame();
                    mpChangeLayout->getAnim(3)->restart();
                    mpChangeLayout->FindPaneByName(sSettingAPPaneNames[1])->SetVisible(false);
                }
                if (unk_0x914 == 1) {
                    mpChangeLayout->getAnim(0)->initFrame();
                    mpChangeLayout->getAnim(0)->restart();
                    mpChangeLayout->FindPaneByName(sSettingAPPaneNames[0])->SetVisible(true);
                }
            }
            mpChangeLayout->getAnim(10)->stop();
            mpChangeLayout->getAnim(11)->stop();
            unk_0x918 = unk_0x91C[0] + 10;
            mpChangeLayout->getAnim(unk_0x918)->initFrame();
            mpChangeLayout->getAnim(unk_0x918)->restart();
        }

        void Setting::setAPDraw() {
            WDBssDesc_* descriptor = reinterpret_cast<WDBssDesc_*>(mAPScanList.entries);
            u32 recordOffset = 2;
            for (u32 index = 0; index <= mAPScanList.count; ++index) {
                if (recordOffset > 0x800) {
                    return;
                }
                descriptor = reinterpret_cast<WDBssDesc_*>(mAPScanList.entries + recordOffset - 2);
                mpChangeLayout->getAnim(10)->stop();
                mpChangeLayout->getAnim(11)->stop();
                int privacyMode = WDGetPrivacyMode(descriptor);
                char ssid[0x21];
                wchar_t displayName[0x21];
                memcpy(ssid, descriptor->ssid, 0x20);
                ssid[0x20] = 0;
                memset(displayName, 0, sizeof(displayName));
                int row = index + 1 - unk_0x914;
                if (row >= 0 && row < 6) {
                    utility::CharacterCode::UTF8ToUTF16(displayName, ssid, 0x21);
                    nw4r::lyt::TextBox* textBox = static_cast<nw4r::lyt::TextBox*>(
                        mpChangeLayout->FindPaneByName(sSettingAPTextNames[row]));
                    textBox->SetString(displayName);
                    if (privacyMode == 0) {
                        mpChangeLayout->getAnim(row + 0x2e)->initFrame();
                        mpChangeLayout->getAnim(row + 0x2e)->restart();
                        mpChangeLayout->getAnim(row + 0x34)->stop();
                    } else {
                        mpChangeLayout->getAnim(row + 0x34)->initFrame();
                        mpChangeLayout->getAnim(row + 0x34)->restart();
                        mpChangeLayout->getAnim(row + 0x2e)->stop();
                    }
                    for (int animation = row + 0x16; animation <= row + 0x28; animation += 6) {
                        mpChangeLayout->getAnim(animation)->stop();
                    }
                    int signal = getRadioLevel(descriptor);
                    mpChangeLayout->getAnim(row + signal * 6 + 0x16)->initFrame();
                    mpChangeLayout->getAnim(row + signal * 6 + 0x16)->restart();
                }
                recordOffset += descriptor->length * 2;
            }
        }

        int Setting::get_arw_no(const char* paneName) {
            for (int index = 0; index < 2; ++index) {
                if (strcmp(sSettingArrowNames[index], paneName) == 0) {
                    return index;
                }
            }
            return -1;
        }

        int Setting::get_ap_no(const char* buttonName) {
            for (int index = 0; index < 4; ++index) {
                if (strcmp(sSettingAPButtonNames[index], buttonName) == 0) {
                    return index;
                }
            }
            return -1;
        }

        void Setting::start_point_event(const char* pageName) {
            int accessPoint = get_ap_no(pageName);
            mpChangeLayout->getAnim(10)->stop();
            mpChangeLayout->getAnim(11)->stop();
            int animation = accessPoint == -1 ? get_arw_no(pageName) + 4 : accessPoint + 0xc;
            if (accessPoint == -1 && animation == 3) {
                return;
            }
            mpChangeLayout->getAnim(animation)->initFrame();
            mpChangeLayout->getAnim(animation)->restart();
            mpWiiSettingData->data[0x37] = 2;
            setSE();
        }

        void Setting::start_left_event(const char* pageName) {
            int accessPoint = get_ap_no(pageName);
            int animation;
            if (accessPoint == -1) {
                int arrow = get_arw_no(pageName);
                if (arrow == -1) {
                    return;
                }
                animation = arrow + 6;
            } else {
                animation = accessPoint + 0x10;
            }
            mpChangeLayout->getAnim(animation)->initFrame();
            mpChangeLayout->getAnim(animation)->restart();
        }

        void Setting::start_trig_event(const char* pageName) {
            int accessPoint = get_ap_no(pageName);
            if (accessPoint != -1) {
                u32 recordOffset = 2;
                WDBssDesc_* descriptor = reinterpret_cast<WDBssDesc_*>(mAPScanList.entries);
                for (u32 index = 0; index <= mAPScanList.count; ++index) {
                    recordOffset += descriptor->length * 2;
                    if (recordOffset > 0x800) {
                        break;
                    }
                    if (index == accessPoint + unk_0x914 + 1) {
                        int privacyMode = WDGetPrivacyMode(descriptor);
                        char ssid[0x21];
                        memcpy(ssid, descriptor->ssid, 0x20);
                        ssid[0x20] = 0;
                        memset(mpStringBuffer->securityKey, 0, sizeof(mpStringBuffer->securityKey));
                        memset(mpStringBuffer->ssid, 0, sizeof(mpStringBuffer->ssid));
                        utility::CharacterCode::ANSIToUTF8(mpStringBuffer->ssid,
                                                           reinterpret_cast<const u8*>(ssid), 0x20);
                        ncd::NCDSetting::setSSID(reinterpret_cast<u8*>(ssid));
                        ncd::NCDSetting::setWDPrivacyMode(privacyMode);
                        www::wiisetting::setFuncResult(privacyMode == 0 ? 2 : 1);
                        mpWiiSettingData->data[0x37] = 3;
                        setSE();
                        OSReport("SET DATA : %d %s %d\n", index, ssid, privacyMode);
                        break;
                    }
                    descriptor = reinterpret_cast<WDBssDesc_*>(mAPScanList.entries + recordOffset - 2);
                }
                unk_0x91C[2] = 0;
                unk_0x78 = 8;
            } else {
                int arrow = get_arw_no(pageName);
                if (arrow == -1) {
                    return;
                }
                unk_0x918 = arrow + 8;
                mpChangeLayout->getAnim(unk_0x918)->initFrame();
                mpChangeLayout->getAnim(unk_0x918)->restart();
                if (arrow == 0) {
                    unk_0x91C[0] = 0;
                    if (unk_0x914 == 1) {
                        mpChangeLayout->FindPaneByName("N_AP0")->SetVisible(false);
                    }
                } else {
                    unk_0x91C[0] = 1;
                    if (mAPScanList.count == unk_0x914 + 5) {
                        mpChangeLayout->FindPaneByName("N_AP7")->SetVisible(false);
                    }
                }
                unk_0x78 = 7;
                snd::getSystem()->startSE("WIPL_SE_BT_PUSH");
            }
        }

        int Setting::getRadioLevel(const WDBssDesc_* descriptor) {
            u16 signal = descriptor->rssi & 0xff;
            if (signal > 0xc3) {
                return 3;
            }
            if (signal > 0xb4) {
                return 2;
            }
            return signal < 0xab ? 0 : 1;
        }

        void Setting::setUseEULA_() {
            if (unk_0x7C == 2) {
                setUseEULA_Cancel_();
            } else if (unk_0x7C == 0) {
                setUseEULA_Init_();
            } else if (unk_0x7C == 1) {
                setUseEULA_Start_();
            } else if (unk_0x7C == 4) {
                setUseEULA_WaitStopMotor_();
            } else if (unk_0x7C < 4 && !snd::getSystem()->isSEActive("WIPL_SE_DECIDE")) {
                unk_0x7C = 4;
            }
        }

        void Setting::setUseEULA_Init_() {
            if (ncd::NCDSetting::getEnableFlag()) {
                unk_0x7C = 1;
            } else {
                if (static_cast<u32>(System::getRegion()) != 2) {
                    System::getDialog()->callBtn2(0x170, 0x146, 0x25);
                } else {
                    System::getDialog()->callBtn2(0x174, 0x146, 0x25);
                }
                unk_0x74 = 9;
                unk_0x7C = 0;
                resetFuncMsgQ();
            }
        }

        void Setting::setUseEULA_Cancel_() {
            System::getDialog()->callBtn2(0x16f, 0x142, 0x141, true);
            unk_0x74 = 0xc;
            unk_0x7C = 0;
            resetFuncMsgQ();
        }

        void Setting::setUseEULA_Start_() {
            if (!validateEULA_()) {
                return;
            }
            for (int channel = 0; channel < 4; ++channel) {
                controller::Interface* input = System::getController(channel);
                if (input != NULL) {
                    input->rumble();
                }
            }
            System::getBS2Manager()->abort();
            System::stopReceiveSchedule();
            unk_0x7C = 3;
        }

        void Setting::setUseEULA_WaitStopMotor_() {
            __WPADReconnect(1);
            mSettingData[0x39] = 1;
            snd::getSystem()->stopAllSound(0x14);
            unk_0x7C = 5;
            resetFuncMsgQ();
        }

        bool Setting::validateEULA_() {
            ESTmdView* titleView = NULL;
            s32 contentResult = 0;
            s32 result = utility::ESMisc::GetTmdView(System::getMem1Root(), mUpdateTitleId, &titleView);
            bool valid = false;
            if (result == -0x401 || result == -0x6a) {
                unk_0x7C = 0;
                unk_0x74 = 0xd;
                resetFuncMsgQ();
                System::getDialog()->callBtn2(0x180, 0x2e, 0x25);
            } else if (result == 0) {
                if (!utility::ESMisc::ContentExist(titleView, 1, &contentResult) && contentResult != 0) {
                    System::getErrorHandler()->log("error", contentResult, "iplSetting.cpp", 0x10fc);
                    System::getErrorHandler()->set(ErrorHandler::DEFAULT, 2);
                }
                valid = true;
            } else {
                System::getErrorHandler()->log("error", result, "iplSetting.cpp", 0x10f1);
                System::getErrorHandler()->set(ErrorHandler::DEFAULT, 2);
            }
            if (titleView != NULL) {
                System::getMem1Root()->free(titleView);
            }
            return valid;
        }

        void Setting::setUpdate_() {
            switch (mProfileIDMode) {
                case 0: setUpdate_Init_(); break;
                case 1: setUpdate_WaitAcceptDialog_(); break;
                case 2: setUpdate_ConnectTestStart_(); break;
                case 3: setUpdate_ConnectTestCreateWait_(); break;
                case 4: setUpdate_ConnectTestRun_(); break;
                case 5: setUpdate_ConnectTestFailed_(); break;
                case 6: setUpdate_SuccessDialog_(); break;
                case 7: setUpdate_NoUpdateDialog_(); break;
                case 8: setUpdate_EULAInit_(); break;
                case 9:
                    System::getDialog()->callBtn2(0x16f, 0x142, 0x141, true);
                    unk_0x74 = 10;
                    resetFuncMsgQ();
                    break;
                case 10: setUpdate_Reboot_(); break;
            }
        }

        void Setting::setUpdate_Init_() {
            if (ncd::NCDSetting::getEnableFlag()) {
                www::wiisetting::setFuncResult(1);
                if (static_cast<u32>(System::getRegion()) == 2) {
                    System::getDialog()->callBtn1Sml(0x177, 0x179);
                } else {
                    System::getDialog()->callBtn1Sml(0x176, 0x178);
                }
                mProfileIDMode = 1;
            } else {
                System::getDialog()->callBtn2(0x17f, 0x146, 0x25);
                unk_0x74 = 9;
                resetFuncMsgQ();
            }
        }

        void Setting::setUpdate_WaitAcceptDialog_() {
            if (System::getDialog()->getLastResult() >= 0) {
                mProfileIDMode = 2;
            }
        }

        void Setting::setUpdate_ConnectTestStart_() {
            if (System::getSceneManager()->getScene(0x19) == NULL && www::wiisetting::getFuncResult() == 0) {
                waitStart();
                createChildScene(0x19, this, NULL, NULL);
                mProfileIDMode = 3;
            }
        }

        void Setting::setUpdate_ConnectTestCreateWait_() {
            if (System::getSceneManager()->getScene(0x19) != NULL) {
                mProfileIDMode = 4;
            }
        }

        void Setting::setUpdate_ConnectTestRun_() {
            if (isWaitPlaying()) {
                return;
            }
            if (mpWiiSettingFlag->err == 0) {
                mpWiiSettingFlag->smthMsgData = 9;
                mUpdateTiming = 3;
            } else if (System::getDialog()->getLastResult() == 1) {
                mProfileIDMode = 2;
            } else if (System::getDialog()->getLastResult() == 2) {
                www::wiisetting::setFuncResult(1);
                mProfileIDMode = 5;
                unk_0x92C = 0;
            }
        }

        void Setting::setUpdate_ConnectTestFailed_() {
            if (unk_0x92C == 0) {
                System::getDialog()->callBtn1(0x16c, 1);
                ++unk_0x92C;
            } else if (System::getDialog()->getLastResult() >= 0) {
                mProfileIDMode = 10;
            }
        }

        void Setting::setUpdate_SuccessDialog_() {
            if (System::getDialog()->getLastResult() >= 0) {
                System::getDialog()->callBtn1(0x16a, 0x2e);
                mProfileIDMode = 8;
            }
        }

        void Setting::setUpdate_NoUpdateDialog_() {
            if (System::getDialog()->getLastResult() >= 0) {
                if (unk_0x92C == 0) {
                    System::getDialog()->callBtn1(0x167, 1);
                    ++unk_0x92C;
                } else {
                    mProfileIDMode = 10;
                }
            }
        }

        void Setting::setUpdate_EULAInit_() {
            if (System::getDialog()->getLastResult() >= 0) {
                if (SCGetEULA() != 0) {
                    mProfileIDMode = 10;
                } else {
                    mProfileIDMode = 0;
                    www::wiisetting::setFuncResult(1);
                    resetFuncMsgQ();
                }
            }
        }

        void Setting::setUpdate_Reboot_() {
            if (unk_0x92C == 0xb4) {
                if (mInitialArgument == 2 || mInitialArgument == 5) {
                    SCSetConfigDoneFlag(1);
                    SCSetConfigDoneFlag2(1);
                    SCFlush();
                }
                mIsResetAcceptable = 1;
                System::getResetHandler()->reset();
            }
            ++unk_0x92C;
        }

        u16 Setting::getProfileID() {
            if (mProfileIDMode < 3) {
                return ncd::NCDSetting::getID();
            }
            u16 profileID = ncd::NCDSetting::getUseProfileID();
            ncd::NCDSetting::initSetID(profileID & 0xff);
            if ((profileID & 0xff) == 3) {
                profileID = 0;
            }
            return profileID;
        }

        int Setting::getUpdateTiming() {
            return mUpdateTiming;
        }

        void Setting::setConnectTestResult(int result, int networkError, bool updateFound, int supportCode) {
            unk_0x930 = supportCode;
            if (!updateFound && result == 3) {
                resetFuncMsgQ();
                mUpdateTiming = 0;
                mIsResetAcceptable = 1;
            } else if (mpWiiSettingFlag->smthMsgData == 9) {
                if (result == 2) {
                    System::getDialog()->terminate();
                    mUpdateTiming = 6;
                    mpWiiSettingFlag->err = networkError;
                } else if (result == 1) {
                    System::getDialog()->setProgBarLength(100);
                    mProfileIDMode = 6;
                    mUpdateTiming = 0;
                    mpWiiSettingFlag->smthMsgData = 0x54;
                    SCSetUpdateType(2);
                    SCFlush();
                } else if (result == 3) {
                    System::getDialog()->terminate();
                    if (SCGetConfigDoneFlag2() == 0) {
                        mProfileIDMode = 6;
                    } else {
                        mProfileIDMode = 7;
                        unk_0x92C = 0;
                    }
                    mUpdateTiming = 0;
                    mpWiiSettingFlag->smthMsgData = 0x54;
                }
            } else {
                if (result == 1) {
                    mpWiiSettingFlag->err = 0;
                    ncd::NCDSetting::setConnectTestFlag(true);
                    System::reloadDownloadTask();
                } else {
                    if (mProfileIDMode == 0) {
                        unk_0x74 = 2;
                    }
                    mpWiiSettingFlag->err = networkError;
                    makeErrorMessage();
                    ncd::NCDSetting::setConnectTestFlag(false);
                }
                waitFinish();
                www::wiisetting::setFuncResult(result);
            }
        }

        void Setting::setNUP() {
            switch (mUpdateTiming) {
                case 0:
                    makeSupportCode();
                    mUpdateTiming = 1;
                    break;
                case 1:
                    if (System::getDialog()->getLastResult() == 2) {
                        System::getDialog()->callBtn1Sml(System::getRegion() == 2 ? 0x177 : 0x176,
                                                        System::getRegion() == 2 ? 0x179 : 0x178);
                        mUpdateTiming = 2;
                    } else if (System::getDialog()->getLastResult() == 1) {
                        www::wiisetting::setFuncResult(2);
                        mUpdateTiming = 10;
                    }
                    break;
                case 2:
                    if (System::getDialog()->getLastResult() >= 0) {
                        mUpdateTiming = 3;
                    }
                    break;
                case 3:
                    System::getDialog()->callBtnPrg(0x162);
                    mUpdateTiming = 4;
                    break;
                case 4: {
                    scene::NakamuraTest* test = static_cast<scene::NakamuraTest*>(System::getSceneManager()->getScene(0x19));
                    if (test != NULL && test->amtTotal() != 0) {
                        System::getDialog()->setProgBarLength(test->amtCompleted() * 100 / test->amtTotal());
                    }
                    break;
                }
                case 5:
                    if (System::getDialog()->getLastResult() >= 0) {
                        System::getDialog()->callBtn0(0x163, 0xb4);
                        mUpdateTiming = 8;
                    }
                    break;
                case 6:
                    if (System::getDialog()->getLastResult() >= 0) {
                        makeErrorMessage();
                        mUpdateTiming = 0xb;
                    }
                    break;
                case 7:
                    if (System::getDialog()->getLastResult() >= 0) {
                        System::getDialog()->callBtn1(0x167, 1);
                        mUpdateTiming = 8;
                    }
                    break;
                case 8:
                    if (System::getDialog()->getLastResult() >= 0) {
                        mUpdateTiming = 9;
                        unk_0x92C = 0;
                        if (mProgressiveMode == 2 || mProgressiveMode == 5) {
                            SCSetConfigDoneFlag(1);
                            SCSetConfigDoneFlag2(1);
                            SCFlush();
                        }
                    }
                    break;
                case 9:
                    if (unk_0x92C == 0xb4) {
                        mIsResetAcceptable = 1;
                        System::getResetHandler()->reset();
                    }
                    ++unk_0x92C;
                    break;
                case 0xb:
                    if (System::getDialog()->getLastResult() >= 0) {
                        mProfileIDMode = 5;
                        mpWiiSettingFlag->smthMsgData = 0x54;
                        mUpdateTiming = 0;
                        unk_0x92C = 0;
                    }
                    break;
            }
        }

        void Setting::makeErrorMessage() {
            const wchar_t* prefix = System::getMessage(400);
            int messageId = getErrorNum();
            const wchar_t* detail = System::getMessage(messageId);
            int error = mpWiiSettingFlag->err;
            OSReport("error:%d\n", error);
            wchar_t errorText[8];
            wchar_t message[0x140];
            swprintf(errorText, 8, L"\n%03d", error);
            memset(message, 0, sizeof(message));
            size_t prefixLength = wcslen(prefix);
            wcsncat(message, prefix, prefixLength);
            size_t errorLength = wcslen(errorText);
            wcsncat(message + prefixLength, errorText, errorLength);
            size_t detailLength = wcslen(detail);
            wcsncat(message + prefixLength + errorLength, detail, detailLength);
            message[prefixLength + errorLength + detailLength] = 0;
            bool connectTestError = mpWiiSettingFlag->smthMsgData == 9;
            bool japaneseRegion = System::getRegion() == 2 && System::getLanguage() == 2 && getErrorNum() == 0x1b6;
            if (connectTestError || mProfileIDMode == 0) {
                if (japaneseRegion) {
                    System::getDialog()->callBtn1(message, 0x2e, 46.0f);
                } else {
                    System::getDialog()->callBtn1(message, 0x2e);
                }
            } else {
                System::getDialog()->callBtn2(message, 0x171, 0x25);
            }
        }

        int Setting::getErrorNum() {
            int error = mpWiiSettingFlag->err;
            if (error == 0x7d01) return System::getRegion() == 2 ? 0x1a5 : 0x191;
            if (error == 0x7d02) return System::getRegion() == 2 ? 0x1a6 : 0x192;
            if (error == 0x7d03) return System::getRegion() == 2 ? 0x1a7 : 0x193;
            if (error < 33000) return System::getRegion() == 2 ? 0x1a8 : 0x194;
            if (error < 0xc418) return System::getRegion() == 2 ? 0x1a9 : 0x195;
            if (error < 0xc47c) return System::getRegion() == 2 ? 0x1aa : 0x196;
            if (error < 0xc4e0) return System::getRegion() == 2 ? 0x1ab : 0x197;
            if (error < 0xc544) return System::getRegion() == 2 ? 0x1ac : 0x198;
            if (error < 0xc760) return System::getRegion() == 2 ? 0x1ad : 0x199;
            if (error < 0xc76a) return System::getRegion() == 2 ? 0x1b8 : 0x1a4;
            if (error < 0xc79c) return System::getRegion() == 2 ? 0x1ad : 0x199;
            if (error < 0xc8c8) return System::getRegion() == 2 ? 0x1ae : 0x19a;
            if (error < 0xc92c) return System::getRegion() == 2 ? 0x1af : 0x19b;
            if (error < 0xcb84) return System::getRegion() == 2 ? 0x1b0 : 0x19c;
            if (error < 0xcbe8) return System::getRegion() == 2 ? 0x1b1 : 0x19d;
            if (error < 0xcc4c) return System::getRegion() == 2 ? 0x1b2 : 0x19e;
            if (error < 0xcd14) return System::getRegion() == 2 ? 0x1b3 : 0x19f;
            if (error < 0xcd78) return System::getRegion() == 2 ? 0x1b4 : 0x1a0;
            if (error < 0xcddc) return System::getRegion() == 2 ? 0x1b5 : 0x1a1;
            if (error < 0xce40) return System::getRegion() == 2 ? 0x1b6 : 0x1a2;
            if (error < 55000) return System::getRegion() == 2 ? 0x1b7 : 0x1a3;
            if (error > 100000) return 0x1c5;
            return System::getRegion();
        }

        void Setting::makeSupportCode() {
            const wchar_t* title = System::getMessage(0x16d);
            const wchar_t* codeLabel = System::getMessage(0x1b9);
            wchar_t supportCode[12];
            wchar_t message[0x110];
            swprintf(supportCode, 12, L"\n%03d", unk_0x930);
            memset(message, 0, sizeof(message));
            size_t titleLength = wcslen(title);
            wcsncat(message, title, titleLength);
            message[titleLength] = L'\n';
            message[titleLength + 1] = 0;
            size_t labelLength = wcslen(codeLabel);
            wcsncat(message + titleLength + 1, codeLabel, labelLength);
            size_t codeLength = wcslen(supportCode);
            wcsncat(message + titleLength + 1 + labelLength, supportCode, codeLength);
            message[titleLength + 1 + labelLength + codeLength] = 0;
            System::getDialog()->callBtn2(message, 0x142, 0x141, true);
        }

        void Setting::setInitializeResult(bool initialized, int error) {
            waitFinish();
            if (!initialized) {
                if (error == -2) {
                    System::getErrorHandler()->log("NandSDWorker", error, "iplSetting.cpp", 0x13a7);
                    System::getErrorHandler()->set(ErrorHandler::DEFAULT, 2);
                } else if (error == -5) {
                    System::getErrorHandler()->set(ErrorHandler::DEFAULT, 1);
                }
            } else {
                www::wiisetting::setFuncResult(1);
            }
        }

        void Setting::setUSBAP() {
            if (unk_0x84 == 2) {
                if (unk_0x91C[1] != 0) {
                    www::wiisetting::setFuncResult(unk_0x91C[1]);
                    unk_0x84 = 1;
                    unk_0x91C[1] = 0;
                    resetFuncMsgQ();
                }
            } else if (unk_0x84 == 1 && static_cast<USBAPThread*>(mpUSBAPThread)->is()) {
                SCOwnerNickname nickname;
                int result = SCGetOwnerNickName(&nickname);
                if (!result) {
                    www::wiisetting::setFuncResult(2);
                    resetFuncMsgQ();
                } else {
                    OSReport("USB SCGetOwnerNickName:%d\n", result);
                    static_cast<USBAPThread*>(mpUSBAPThread)->setData(
                        reinterpret_cast<const wchar_t*>(nickname.name), &unk_0x91C[1]);
                    static_cast<USBAPThread*>(mpUSBAPThread)->Init(
                        reinterpret_cast<unsigned short*>(mpMem1BrowserBuffer),
                        reinterpret_cast<u8*>(mpMem2BrowserBuffer));
                    unk_0x84 = 2;
                }
            }
        }

        void Setting::cancelUSBAP() {
            if (unk_0x84 == 3) {
                if (unk_0x91C[1] != 0 || static_cast<USBAPThread*>(mpUSBAPThread)->is()) {
                    www::wiisetting::setFuncResult(5);
                    unk_0x84 = 1;
                    unk_0x91C[1] = 0;
                    resetFuncMsgQ();
                }
            } else if (unk_0x84 > 0 && unk_0x84 < 3) {
                static_cast<USBAPThread*>(mpUSBAPThread)->cancel();
                unk_0x84 = 3;
            }
        }

        void Setting::AOSSProcess() {
            int error = mpWiiSettingFlag->err;
            if (error == '"') {
                if (mAOSSState == 3) {
                    if (System::getDialog()->getLastResult() >= 0) {
                        mAOSSState = 0;
                        www::wiisetting::setFuncResult(10);
                        resetFuncMsgQ();
                    }
                } else {
                    System::getDialog()->callBtn1(0x1c2, 0x2e);
                    mAOSSState = 3;
                    unk_0x74 = 2;
                }
                return;
            }
            AOSSThread* thread = reinterpret_cast<AOSSThread*>(mpAOSSThread);
            bool cancelled = error == '!';
            if (mAOSSState == 0) {
                if (!snd::getSystem()->isSEActive("WIPL_SE_DECIDE")) {
                    if (cancelled || thread->start() == 0) {
                        www::wiisetting::setFuncResult(cancelled ? 5 : 2);
                        resetFuncMsgQ();
                    } else {
                        mAOSSState = 1;
                    }
                }
            } else if (mAOSSState >= 0 && mAOSSState < 3) {
                int result = 0;
                if (thread->finish(&m_AOSSConfig, &result) != 0) {
                    mAOSSState = 0;
                    if (cancelled) {
                        www::wiisetting::setFuncResult(5);
                    } else if (result == 0) {
                        ncd::NCDSetting::getData();
                        ncd::NCDSetting::getID();
                        ncd::NCDSetting::setAOSSParams(m_AOSSConfig);
                        www::wiisetting::setFuncResult(1);
                    } else {
                        OSReport("m_AOSSThread : Terminated with Error(%d)\n", result);
                        www::wiisetting::setFuncResult(2);
                    }
                    resetFuncMsgQ();
                } else if (cancelled && mAOSSState != 2) {
                    thread->cancel();
                    mAOSSState = 2;
                }
            }
        }

        void Setting::RakuProcess() {
            int command = mpWiiSettingFlag->smthMsgData;
            int state = reinterpret_cast<RakuRakuThread*>(mpRakuRakuThread)->getState();
            RakuRakuThread* thread = reinterpret_cast<RakuRakuThread*>(mpRakuRakuThread);
            int result = 0;
            if (command == ',') {
                if (mRakuState != 1) {
                    System::getDialog()->callBtn1(0x1c3, 0x2e);
                    mRakuState = 1;
                    unk_0x74 = 2;
                } else if (System::getDialog()->getLastResult() >= 0) {
                    mRakuState = 0;
                    www::wiisetting::setFuncResult(10);
                    resetFuncMsgQ();
                }
                return;
            }
            if (command == '+' && (state == 0 || state == 6 || state == 7 || state == 8)) {
                if (thread->finish(NULL, NULL) != 0) {
                    www::wiisetting::setFuncResult(5);
                    resetFuncMsgQ();
                } else {
                    thread->cancel();
                }
                return;
            }
            if (command != '+' && state == 0) {
                if (!snd::getSystem()->isSEActive("WIPL_SE_DECIDE") && thread->start() == 0) {
                    www::wiisetting::setFuncResult(2);
                    resetFuncMsgQ();
                }
                return;
            }
            if (command != '+' && state == 5) {
                if (command == ')') {
                    www::wiisetting::setFuncResult(1);
                    resetFuncMsgQ();
                }
                return;
            }
            if (state == 7) {
                if (thread->finish(NULL, &result) != 0) {
                    www::wiisetting::setFuncResult(2);
                    resetFuncMsgQ();
                }
                return;
            }
            if (state > 4 && state < 7) {
                if (thread->finish(&m_RakuConfig.cfg, &result) != 0) {
                    if (result == 1) {
                        ncd::NCDSetting::getData();
                        ncd::NCDSetting::getID();
                        ncd::NCDSetting::setRakuParams(m_RakuConfig.cfg);
                        www::wiisetting::setFuncResult(1);
                    } else {
                        www::wiisetting::setFuncResult(2);
                    }
                    resetFuncMsgQ();
                }
                return;
            }
            if (state > 0 && state < 4 && command == '(') {
                www::wiisetting::setFuncResult(1);
                resetFuncMsgQ();
            }
        }

        void Setting::waitStart() {
            mpWaitLayout->getAnim(0)->initFrame();
            mpWaitLayout->getAnim(0)->restart();
            mpWaitLayout->FindPaneByName("G_Wait")->SetVisible(true);
            snd::getSystem()->startSE("WIPL_SE_COPYING");
        }

        void Setting::waitFinish() {
            mpWaitLayout->getAnim(0)->stop();
            mpWaitLayout->FindPaneByName("G_Wait")->SetVisible(false);
            snd::getSystem()->startSE("WIPL_SE_COPY_FINISH");
        }

        bool Setting::isWaitPlaying() {
            return mpWaitLayout->getAnim(0)->isPlaying();
        }

        void Setting::setSE() {
            u8& action = mpWiiSettingData->data[0x37];
            u8& pendingAction = mpWiiSettingData->data[0x38];
            if (unk_0xB9C < 10 && action == 2) {
                action = 0;
            }
            if ((action == 0 || action == 2) && pendingAction != 0) {
                action = pendingAction;
            }
            switch (action) {
                case 1:
                    snd::getSystem()->startSE("WIPL_SE_BT_PUSH");
                    break;
                case 2:
                    snd::getSystem()->startSE("WIPL_SE_BT_TARGETTING");
                    break;
                case 3:
                    snd::getSystem()->startSE("WIPL_SE_DECIDE");
                    break;
                case 4:
                    snd::getSystem()->startSE("WIPL_SE_CANCEL");
                    break;
                case 5:
                    snd::getSystem()->startSE("WIPL_SE_CHOICE_CHG");
                    break;
                case 6:
                    snd::getSystem()->startSE("WIPL_SE_CHAR_DELETE_ERROR");
                    break;
                case 10:
                    snd::getSystem()->setOutputMode(snd::AUDIO_OUTPUT_MODE_MONO);
                    snd::getSystem()->startSE("WIPL_SE_OUTPUT_MODE_SELECT");
                    break;
                case 11:
                    snd::getSystem()->setOutputMode(snd::AUDIO_OUTPUT_MODE_STEREO);
                    snd::getSystem()->startSE("WIPL_SE_OUTPUT_MODE_SELECT");
                    break;
                case 12:
                    snd::getSystem()->setOutputMode(snd::AUDIO_OUTPUT_MODE_SURROUND);
                    snd::getSystem()->startSE("WIPL_SE_OUTPUT_MODE_SELECT");
                    break;
                case 30:
                    snd::getSystem()->setOutputMode(snd::AUDIO_OUTPUT_MODE_MONO);
                    snd::getSystem()->startSE("WIPL_SE_CANCEL");
                    break;
                case 31:
                    snd::getSystem()->setOutputMode(snd::AUDIO_OUTPUT_MODE_STEREO);
                    snd::getSystem()->startSE("WIPL_SE_CANCEL");
                    break;
                case 32:
                    snd::getSystem()->setOutputMode(snd::AUDIO_OUTPUT_MODE_SURROUND);
                    snd::getSystem()->startSE("WIPL_SE_CANCEL");
                    break;
            }
            if (action == 2 || action == 0 || mpWiiSettingData->data[0x12] == 0x1e || pendingAction != 0) {
                if (action == 2) {
                    controller::Interface* controller = System::getYoungController();
                    if (controller != NULL) {
                        controller->rumble(0);
                    }
                }
            } else {
                unk_0xB9C = 0;
            }
            action = 0;
            pendingAction = 0;
        }

        void APEvent::onEvent(u32 componentID, u32 event, void* data) {
            gui::PaneComponent* component = static_cast<gui::PaneComponent*>(mpManager->getComponent(componentID));
            const char* paneName = component->getPane()->GetName();
            if (event == ::gui::EventHandler::ON_POINT) {
                mpSetting->start_point_event(paneName);
            } else if (event == ::gui::EventHandler::ON_TRIG) {
                controller::Interface* input = static_cast<controller::Interface*>(data);
                if (input->downTrg(0x100800)) {
                    mpSetting->start_trig_event(paneName);
                }
            } else if (event == ::gui::EventHandler::ON_LEFT) {
                mpSetting->start_left_event(paneName);
            }
        }

        BOOL Setting::isResetAcceptable() const {
            return mIsResetAcceptable;
        }

    }  // namespace scene
}  // namespace ipl
