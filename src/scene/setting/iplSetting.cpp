#define IPL_SETTING_IMPLEMENTATION
#include "scene/setting/iplSetting.h"

#include "scene/setting/iplNCDSetting.h"
#include "scene/setting/iplParental.h"
#include "system/iplErrorHandler.h"
#include "system/iplSystem.h"
#include "utility/iplWpad.h"

#include "iplwww/www_wiisetting.h"
#include "iplwww/www_surface.h"

#include <cstdio>
#include <cstring>
#include <new>
#include <revolution/sc.h>
#include <revolution/tpl.h>
#include <revolution/vi.h>

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
                mpAPEvent->setEventType((u8)message);
            }
        }

        void Setting::resetFuncMsgQ() {
            mpAPEvent->setEventType(0);
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

            mpBrowserData = ::operator new(0x20);
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
            mpAPEvent = mpEventHandler;
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
