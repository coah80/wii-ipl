#define IPL_SETTING_IMPLEMENTATION
#include "scene/setting/iplSetting.h"

#include "scene/setting/iplNCDSetting.h"

namespace ipl {
    namespace scene {
        static const char* sSettingAPButtonNames[] = {
            "B_AP2", "B_AP3", "B_AP4", "B_AP5", "T_Name1", "T_Name2", "T_Name3", "T_Name4",
            "T_Name5", "T_Name6", "N_AP1",  "N_AP2",  "N_AP3",  "N_AP4",  "N_AP5",  "N_AP6",
        };

        static const char* sSettingArrowNames[] = {"B_ArwA", "B_ArwB"};

        static const char* sSettingAPPaneNames[] = {
            "G_ListUpDown", "G_ListInOut", "G_ArwA", "G_ArwB", "G_Denpa", "G_Lock",  "G_AP0",
            "G_AP1",        "G_AP2",       "G_AP3",  "G_AP4",  "G_AP5",   "G_AP6",   "G_AP7",
            "G_Denpa1",     "G_Denpa2",    "G_Denpa3", "G_Denpa4", "G_Denpa5", "G_Denpa6",
            "G_Lock1",      "G_Lock2",     "G_Lock3", "G_Lock4", "G_Lock5", "G_Lock6",
        };

        static const char* sSettingAPAnimations[] = {
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
            unk_0x60 = 0;
            unk_0x64 = 0;
            unk_0x68 = 0;
            unk_0x6C = 0;
            unk_0xBC = 0;
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
