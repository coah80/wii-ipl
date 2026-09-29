#define IPL_SETTING_IMPLEMENTATION
#include "scene/setting/iplSetting.h"

#include "scene/setting/iplNCDSetting.h"
#include "system/iplSystem.h"

#include "iplwww/www_wiisetting.h"

#include <cstdio>
#include <cstring>

namespace ipl {
    namespace scene {
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
            unk_0xB3B = 0;
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
                mpAPEvent->eventType = (u8)message;
            }
        }

        void Setting::resetFuncMsgQ() {
            mpAPEvent->eventType = 0;
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
            bs2::Manager* bs2Manager = System::getBS2Manager();
            bs2Manager->abort();
            while (bs2Manager->getIPLState() != 8) {
                bs2Manager->update();
                VIWaitForRetrace();
            }

            System::getUsbEtherMacAddr();
            mPrepareTick = OSGetTick();
            mpWWWLibraryFile = System::getNandManager()->readSharedAsync(
                System::createMem1AppHeap(), "wwwlib-rvl.lz7", 2, 0, 0, 1, 2);

            char fontName[32];
            char htmlPath[64];
            char productArea = SCGetProductArea();
            if (productArea < 6) {
                if (productArea != 4) {
                    if (productArea > 3) {
                        snprintf(fontName, sizeof(fontName), "WiiNTLG-Regular.ttc");
                        snprintf(htmlPath, sizeof(htmlPath), "/html/%s/iplsetting.ash", "EU/EU");
                        goto loadFiles;
                    }
                    if (productArea >= 0) {
                        snprintf(fontName, sizeof(fontName), "WiiNTLG-Regular.ttc");
                        snprintf(htmlPath, sizeof(htmlPath), "/html/%s/iplsetting.ash", "FIX/US");
                        goto loadFiles;
                    }
                }
            } else if (productArea == 6) {
                snprintf(fontName, sizeof(fontName), "Wii-kr_Round Gothic B.ttf");
                snprintf(htmlPath, sizeof(htmlPath), "/html/%s/iplsetting.ash", "FIX/US");
                goto loadFiles;
            } else if (productArea == 11) {
                snprintf(fontName, sizeof(fontName), "Wii-cn_HeiTiW5.ttf");
                snprintf(htmlPath, sizeof(htmlPath), "/html/%s/iplsetting.ash", "FIX/US");
                goto loadFiles;
            }

            snprintf(fontName, sizeof(fontName), "WiiNTLG-Regular.ttc");
            snprintf(htmlPath, sizeof(htmlPath), "/html/%s/iplsetting.ash", "FIX/US");

        loadFiles:
            mpSettingHTMLFile = System::getNandManager()->readAsync(
                System::createMem1AppHeap(), htmlPath, 0, 0, false);
            mpWWWArchiveFile = System::getNandManager()->readAsync(
                System::createMem1AppHeap(), "/www.arc", 0, 0, false);
            mpFontFile = System::getNandManager()->readSharedAsync(
                System::createMem1AppHeap(), fontName, 3, 0, 0, 1, 2);
            mpBackgroundTPLFile = System::getNandManager()->readAsync(
                System::createMem1AppHeap(), "/html/BG_16x9.tpl", 0, 0, false);
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
