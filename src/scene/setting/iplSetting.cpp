#define IPL_SETTING_IMPLEMENTATION
#include "scene/setting/iplSetting.h"

#include "scene/setting/iplNCDSetting.h"
#include "scene/setting/iplParental.h"
#include "scene/parentalDialog/iplParentalDialog.h"
#include "system/iplErrorHandler.h"
#include "system/iplSystem.h"
#include "utility/iplWpad.h"
#include "utility/iplCharacterCode.h"
#include "sound/iplSound.h"

#include "iplwww/www_wiisetting.h"
#include "iplwww/www_surface.h"
#include "iplwww/www_trasition.h"

#include <cstdio>
#include <cstring>
#include <new>
#include <revolution/sc.h>
#include <revolution/tpl.h>
#include <revolution/vi.h>
#include <revolution/wpad.h>
#include <private/os/OSExec.h>
#include <private/os/OSSram.h>

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
        class APScanThread {
        public:
            APScanThread();
        };

        class USBAPThread {
        public:
            USBAPThread();
        };

        class AOSSThread {
        public:
            AOSSThread(EGG::Heap* heap);
        };

        class RakuRakuThread {
        public:
            RakuRakuThread(EGG::Heap* heap);
        };

        struct SettingAnimationBinding {
            u16 animation;
            u16 pane;
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
                writtenArchive->write();
            }

            mpChangeLayout = new layout::Object(getSceneHeap(), mpSettingLayoutFile, "arc", "SceenChange_b.brlyt");
            mpFirstAnimation = reinterpret_cast<SettingAnimation*>(mpChangeLayout->bind("SceenChange_b_Right.brlan"));
            mpSecondAnimation = reinterpret_cast<SettingAnimation*>(mpChangeLayout->bind("SceenChange_b_Left.brlan"));
            mpChangeLayout->finishBinding();

            mpMainLayout = new layout::Object(getSceneHeap(), mpSettingLayoutFile, "arc", "my_AP_a.brlyt");
            for (int index = 0; index < 58; index++) {
                const SettingAnimationBinding& binding = sSettingAnimationBindings[index];
                bool isSpecialAnimation = index == 10 || index == 20;
                mpMainLayout->bindToGroup(sSettingAPAnimations[binding.animation], sSettingAPPaneNames[binding.pane], false,
                                          isSpecialAnimation);
            }
            mpMainLayout->finishBinding();

            mpWaitLayout = new layout::Object(getSceneHeap(), mpSettingLayoutFile, "arc", "it_Waiting_a.brlyt");
            mpWaitLayout->bindToGroup("it_Waiting_a_Wait.brlan", "G_Wait", false, false);
            mpWaitLayout->finishBinding();
            mpWaitLayout->FindPaneByName("N_Wait")->SetVisible(false);

            mpBrowserData = static_cast<ext_ead::www::ImeData*>(::operator new(0x20));
            void* apScanThreadMemory = ::operator new(0x380);
            mpAPScanThread = apScanThreadMemory != NULL ? new (apScanThreadMemory) APScanThread() : NULL;
            void* usbThreadMemory = ::operator new(0x14);
            mpUSBAPThread = usbThreadMemory != NULL ? new (usbThreadMemory) USBAPThread() : NULL;
            ncd::NCDSetting::init();
            parental::Parental::init();

            void* aossThreadMemory = ::operator new(0x5b0);
            mpAOSSThread = aossThreadMemory != NULL
                               ? reinterpret_cast<utility::ut_thread*>(new (aossThreadMemory) AOSSThread(getSceneHeap()))
                               : NULL;
            void* rakuThreadMemory = ::operator new(0x348);
            mpRakuRakuThread = rakuThreadMemory != NULL
                                   ? reinterpret_cast<utility::ut_thread*>(new (rakuThreadMemory) RakuRakuThread(getSceneHeap()))
                                   : NULL;

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
            static const char* urlFormats[] = {"marc:%s/%s/", "file:dvd/html/IPLSetting/%s/%s/"};
            static const char* pagePaths[] = {
                "index01.html", "Internet/Internet_index.html", "Setup/startup_index1.html",
                "Update/Update_index.html", "index02.html", "Setup/ScreenSave.html",
                "Country/US_Country_flame.html",
            };
            static const char* pageNames[] = {"Calendar", "Parental_Control", "Internet", "Wiiconnect24"};
            static const char* regionCodes[] = {"JP/JP", "FIX/US", "EU/EU", "TW/TW", "KR/KR", "CN/CN"};
            static const char* languageCodes[] = {"JPN", "ENG", "GER", "FRA", "SPA", "ITA", "DUT", "CHN", "KOR"};

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
                    if (strstr(reinterpret_cast<char*>(mpStringBuffer) + 0x60e, pageNames[index]) != NULL) {
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
                memcpy(reinterpret_cast<char*>(mpStringBuffer) + 0x60e, settingArgument, 0x80);
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
            if (System::hasCreatedAfter()) {
                if (mBrowserCreated == 0) {
                    mBrowserCreated = 1;
                    createBrowser();
                    OSReport("............browser created\n");
                }
            } else if (mBrowserCreated == 0) {
                OSReport("wait first init\n");
                return FADER_SCN_CONTINUE;
            }

            ext_ead::www::SurfaceManager* surfaceManager = ext_ead::www::SurfaceManager::GetInstance();
            ext_ead::www::BrowserThread* browserThread = surfaceManager->GetBrowserThread();
            if (browserThread == NULL || browserThread->GetTextureBuffer(0, NULL) == NULL || !System::hasCreatedAfter()) {
                return FADER_SCN_CONTINUE;
            }

            mKeyboardState = *System::getKeyboard()->getState();
            System::getFader()->fadeIn();
            mCreatePageTime = OSGetTime();
            OSReport("*** create page costs: %dms\n",
                     (OSGetTick() - mPrepareTick) / (OS_TIMER_CLOCK / 1000));
            return FADER_SCN_NEXT;
        }

        void Setting::updateController_() {
            nw4r::ut::Rect projection;
            System::getProjectionRect4x3(&projection);

            if (isAnimating()) {
                return;
            }

            controller::Interface* youngController = System::getYoungController();
            ext_ead::www::BrowserThread::CmdPacket packet;

            if (youngController == NULL) {
                packet.type = 0;
                packet.data.controller.irX = -1000.0f;
                packet.data.controller.irY = -1000.0f;
                packet.data.controller.btnHold = 0;
                packet.data.controller.btnTrigger = 0;
                packet.data.controller.btnRelease = 0;
                ext_ead::www::SurfaceManager::GetInstance()->GetBrowserThread()->SendUIEvent(&packet);
                return;
            }

            if (unk_0xB9C >= 10 && *(reinterpret_cast<char*>(mpStringBuffer) + 0x60e) == 0) {
                packet.data.controller.irX = youngController->getDpdProjectionPos().x - projection.left;
                packet.data.controller.irY = youngController->getDpdProjectionPos().y - projection.top;
                u32 classicHold = youngController->getClassicHoldFlag();
                u32 classicTrigger = youngController->getClassicTrigFlag();
                u32 classicRelease = youngController->getClassicReleaseFlag();
                packet.data.controller.btnHold = (classicHold << 16) | youngController->getHoldFlag();
                packet.data.controller.btnTrigger = (classicTrigger << 16) | youngController->getTrigFlag();
                packet.data.controller.btnRelease = (classicRelease << 16) | youngController->getReleaseFlag();
            } else {
                packet.data.controller.irX = -1000.0f;
                packet.data.controller.irY = -1000.0f;
                packet.data.controller.btnHold = 0;
                packet.data.controller.btnTrigger = 0;
                packet.data.controller.btnRelease = 0;
            }

            packet.type = 0;
            if (mKeyboardState.type == textinput::MemoManager::ST_Hidden && unk_0x74 == 0) {
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
            if (input->downTrg(0x100800)) {
                return true;
            }

            OSTime elapsed = OSGetTime() - mCreatePageTime;
            if (elapsed / (OS_TIMER_CLOCK / 1000) >= 500 && connectedMask != unk_0xBA8 &&
                utility::wpad::isIncreaseConnectedWpad(unk_0xBA8, connectedMask)) {
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
                if (System::getFader()->getStatus() != EGG::Fader::PREPARE_IN) {
                    mState = 0;
                    return true;
                }

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
            } else if (unk_0xB94 > 0 && unk_0xB94 < 4) {
                if (System::getFader()->getStatus() != EGG::Fader::PREPARE_IN) {
                    mState = 0;
                    return true;
                }

                changeVideoMode();
                System::getFader()->fadeIn();
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
                if (System::getDialog()->getLastResult() == 1 ||
                    System::getDialog()->getLastResult() == 2) {
                    if (unk_0xB9C == 0) {
                        www::wiisetting::setFuncResult(System::getDialog()->getLastResult());
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
                    if (System::getNwc24Manager() != NULL) {
                        System::getNwc24Manager()->enableLedNotification(TRUE);
                    }
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
                    if (System::getNwc24Manager() != NULL) {
                        System::getNwc24Manager()->enableLedNotification(TRUE);
                    }
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
                    if (System::getNwc24Manager() != NULL) {
                        System::getNwc24Manager()->enableLedNotification(TRUE);
                    }
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
            u8 formId = mpWiiSettingData->data[0x11];
            OSReport("initKeyboard formId:%d\n", formId);
            memset(unk_0x938, 0, sizeof(unk_0x938));

            int productArea = SCGetProductArea();
            int rowLimit = 0;
            int stringLimit = 0;
            keyboard::Manager::KeyboardType keyboardType = keyboard::Manager::LETTER;

            switch (formId) {
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
                case 12:
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

            if (formId != 13 && formId != 2 && formId != 18 && formId != 19 && formId != 22) {
                utility::CharacterCode::UTF8ToUTF16(reinterpret_cast<wchar_t*>(unk_0x938), text, 0x101);
            }

            size_t textLength = wcslen(reinterpret_cast<wchar_t*>(unk_0x938));
            OSReport("キーボード: %d %d %d %d\n", rowLimit, stringLimit, keyboardType, textLength);
            reinterpret_cast<wchar_t*>(unk_0x938)[stringLimit] = 0;

            int invalidInput = 0;
            if (formId >= 4 && formId <= 8) {
                invalidInput = checkIPString(reinterpret_cast<const wchar_t*>(unk_0x938));
            } else if ((formId > 0 && formId < 4) || (formId >= 10 && formId <= 20) || formId == 22) {
                invalidInput = checkInputString(reinterpret_cast<const wchar_t*>(unk_0x938));
            }

            if (invalidInput != 0) {
                memset(unk_0x938, 0, sizeof(unk_0x938));
            }

            keyboard::Manager* keyboardManager = System::getKeyboard();
            if (productArea == 11) {
                keyboardManager->memoFrm()->setZiDictionary(keyboardManager->getZiSystemDic(), keyboardManager->getZiOemDic());
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
            u8 formId = mpWiiSettingData->data[0x11];
            char* formText = NULL;
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

            ext_ead::www::BrowserThread* browser = ext_ead::www::SurfaceManager::GetInstance()->GetBrowserThread();
            if (mKeyboardState.iplType == keyboard::Manager::STATE_DISAPPEARING) {
                if (!mKeyboardState.pressOK) {
                    browser->CommitIme(mpBrowserData, formText);
                } else {
                    onTextInputOK();
                    formId = mpWiiSettingData->data[0x11];
                    OSReport("formID:%d %s\n", formId, formText);
                    if (strlen(formText) == 0) {
                        formText[0] = 0;
                        browser->CommitIme(mpBrowserData, formText);
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
                        browser->CommitIme(mpBrowserData, mpStringBuffer->asterisks);
                    } else {
                        browser->CommitIme(mpBrowserData, formText);
                    }
                }

                mpWiiSettingData->data[0x11] = 0;
                browser->DisposeImeData(mpBrowserData);
            } else if (mKeyboardState.iplType < keyboard::Manager::STATE_VISIBLE) {
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
            u8 settingId = mpWiiSettingData->data[0x36];
            OSReport("setstring:%d\n", settingId);
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
            u8 formId = mpWiiSettingData->data[0x11];
            OSReport("Keyboard Confirm:%d\n", formId);
            wcslen(mKeyboardState.wcString);

            memset(unk_0x938, 0, sizeof(unk_0x938));
            u8 convertedText[0x302];
            memset(convertedText, 0, sizeof(convertedText));
            memcpy(unk_0x938, mKeyboardState.wcString, sizeof(unk_0x938));

            if (formId == 2 || formId == 22) {
                utility::CharacterCode::UTF16ToANSI(convertedText, reinterpret_cast<const wchar_t*>(unk_0x938), 0x100);
                size_t textLength = wcslen(reinterpret_cast<const wchar_t*>(unk_0x938));
                memset(convertedText + textLength, 0, 0x100 - textLength);
                memcpy(mpStringBuffer->securityKey, convertedText, sizeof(mpStringBuffer->securityKey));
                return;
            }

            if (formId == 18 || formId == 19) {
                adjustSecA(reinterpret_cast<wchar_t*>(unk_0x938));
            }
            utility::CharacterCode::UTF16ToUTF8(reinterpret_cast<char*>(convertedText),
                                                reinterpret_cast<const wchar_t*>(unk_0x938), 0x301);

            switch (formId) {
                case 1:
                    memcpy(mpStringBuffer->nickname, convertedText, sizeof(mpStringBuffer->nickname));
                    break;
                case 3:
                    memcpy(mpStringBuffer->securityKey, convertedText, sizeof(mpStringBuffer->securityKey));
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
                case 14:
                    memcpy(mpStringBuffer->adjMtu, convertedText, sizeof(mpStringBuffer->adjMtu));
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
            }
        }

        void Setting::initNickName() {
            BOOL hasNickname = SCGetOwnerNickName(reinterpret_cast<SCOwnerNickname*>(mSettingData));
            OSReport("SCGetOwnerNickName:%d\n", hasNickname);
            if (hasNickname) {
                SCOwnerNickname* ownerNickname = reinterpret_cast<SCOwnerNickname*>(mSettingData);
                memcpy(unk_0x938, ownerNickname->name, ownerNickname->length * sizeof(wchar_t));
            }
            memset(mpStringBuffer->nickname, 0, sizeof(mpStringBuffer->nickname));
            utility::CharacterCode::UTF16ToUTF8(mpStringBuffer->nickname,
                                                reinterpret_cast<const wchar_t*>(unk_0x938),
                                                sizeof(mpStringBuffer->nickname));
        }

        void Setting::initSecurityKey() {
            memset(mpStringBuffer->securityKey, 0, sizeof(mpStringBuffer->securityKey));
            u16 privacyMode = ncd::NCDSetting::getNCDPrivacyMode();
            size_t keyLength = 0;
            if (privacyMode == 2) {
                keyLength = 13;
            } else if (privacyMode < 2) {
                if (privacyMode == 1) {
                    keyLength = 5;
                }
            } else if (privacyMode > 3 && privacyMode < 7) {
                keyLength = 64;
            }
            if (keyLength != 0) {
                memcpy(mpStringBuffer->securityKey, ncd::NCDSetting::getPrivacy(), keyLength);
            }
            OSReport("privacy : %s\n", ncd::NCDSetting::getPrivacy());
        }

        void Setting::initSSID() {
            memset(mpStringBuffer->ssid, 0, sizeof(mpStringBuffer->ssid));
            NCDApConfig* ssid = ncd::NCDSetting::getSSID();
            utility::CharacterCode::ANSIToUTF8(mpStringBuffer->ssid, ssid->ssid, ssid->ssidLength);
            OSReport("initHTMLText initString:%s length:%d\n", ssid->ssid, ssid->ssidLength);
        }

        void Setting::initIP() {
            memset(mpStringBuffer->ip.addr, 0, sizeof(mpStringBuffer->ip.addr));
            memset(mpStringBuffer->ip.netmask, 0, sizeof(mpStringBuffer->ip.netmask));
            memset(mpStringBuffer->ip.gateway, 0, sizeof(mpStringBuffer->ip.gateway));
            NCDIpProfile* ip = ncd::NCDSetting::getIP();
            convertIP(mpStringBuffer->ip.addr, ip->addr);
            convertIP(mpStringBuffer->ip.netmask, ip->netmask);
            convertIP(mpStringBuffer->ip.gateway, ip->gateway);
        }

        void Setting::initDNS() {
            memset(mpStringBuffer->dns1, 0, sizeof(mpStringBuffer->dns1));
            memset(mpStringBuffer->dns2, 0, sizeof(mpStringBuffer->dns2));
            NCDIpProfile* ip = ncd::NCDSetting::getIP();
            convertIP(mpStringBuffer->dns1, ip->dns1);
            convertIP(mpStringBuffer->dns2, ip->dns2);
        }

        void Setting::initProxy() {
            memset(mpStringBuffer->proxy.server, 0, sizeof(mpStringBuffer->proxy.server));
            memset(mpStringBuffer->proxy.port, 0, sizeof(mpStringBuffer->proxy.port));
            NCDProxyProfile* proxy = ncd::NCDSetting::getProxy();
            memcpy(mpStringBuffer->proxy.server, proxy->http.server, sizeof(proxy->http.server));
            sprintf(mpStringBuffer->proxy.port, "%d", proxy->http.port);
        }

        void Setting::initBasic() {
            memset(mpStringBuffer->proxyBasic.uname, 0, sizeof(mpStringBuffer->proxyBasic.uname));
            memset(mpStringBuffer->proxyBasic.pass, 0, sizeof(mpStringBuffer->proxyBasic.pass));
            NCDProxyProfile* proxy = ncd::NCDSetting::getProxy();
            memcpy(mpStringBuffer->proxyBasic.uname, proxy->http.username, sizeof(proxy->http.username));
            memcpy(mpStringBuffer->proxyBasic.pass, proxy->http.password, sizeof(proxy->http.password));
        }

        void Setting::initMTU() {
            memset(mpStringBuffer->adjMtu, 0, sizeof(mpStringBuffer->adjMtu));
            char mtuText[20];
            sprintf(mtuText, "%d", ncd::NCDSetting::getMTU());
            utility::CharacterCode::ANSIToUTF8(mpStringBuffer->adjMtu,
                                               reinterpret_cast<const u8*>(mtuText));
        }

        void Setting::initSecA() {
            memset(mpStringBuffer->parentalSecA, 0, sizeof(mpStringBuffer->parentalSecA));
            wchar_t answer[42];
            memset(answer, 0, 0x44);
            wcsncpy(answer, parental::Parental::getSecA(), 0x20);
            memset(unk_0x938, 0, sizeof(unk_0x938));
            wcsncpy(reinterpret_cast<wchar_t*>(unk_0x938), answer, 0x20);
            adjustSecA(answer);
            utility::CharacterCode::UTF16ToUTF8(mpStringBuffer->parentalSecA, answer,
                                                sizeof(mpStringBuffer->parentalSecA));
        }

        u16 Setting::getProfileID() {
            u16 profileID;
            if (mProfileIDMode >= 3) {
                profileID = ncd::NCDSetting::getUseProfileID();
                ncd::NCDSetting::initSetID(profileID & 0xFF);
                if ((u8)profileID == 3) {
                    profileID = 0;
                }
            } else {
                profileID = ncd::NCDSetting::getID();
            }
            return profileID;
        }

        int Setting::getUpdateTiming() {
            return mUpdateTiming;
        }

        int Setting::get_arw_no(const char* paneName) {
            int result = -1;
            for (int index = 0; index < 2; index++) {
                if (strcmp(sSettingArrowNames[index], paneName) == 0) {
                    result = index;
                    break;
                }
            }
            return result;
        }

        int Setting::get_ap_no(const char* buttonName) {
            int result = -1;
            for (int index = 0; index < 4; index++) {
                if (strcmp(sSettingAPButtonNames[index], buttonName) == 0) {
                    result = index;
                    break;
                }
            }
            return result;
        }

        BOOL Setting::isResetAcceptable() const {
            return mIsResetAcceptable;
        }

    }  // namespace scene
}  // namespace ipl
