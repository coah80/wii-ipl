#define IPL_SETTING_IMPLEMENTATION
#include "scene/setting/iplSetting.h"

#include "scene/setting/iplNCDSetting.h"

namespace ipl {
    namespace scene {
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
            if (mProfileIDMode < 3) {
                return ncd::NCDSetting::getID();
            }

            u16 profileID = ncd::NCDSetting::getUseProfileID();
            ncd::NCDSetting::initSetID(profileID & 0xFF);
            if ((profileID & 0xFF) == 3) {
                profileID = 0;
            }
            return profileID;
        }

        int Setting::getUpdateTiming() {
            return mUpdateTiming;
        }

        BOOL Setting::isResetAcceptable() const {
            return mIsResetAcceptable;
        }
    }  // namespace scene
}  // namespace ipl
