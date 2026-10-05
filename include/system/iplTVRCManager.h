#ifndef IPL_TVRC_MANAGER_H
#define IPL_TVRC_MANAGER_H

#include <revolution/types.h>

#include "system/TVRC.h"
#include "system/iplNandShared.h"

#include <egg/core.h>

namespace ipl {
    class TVRCManager {
    public:
        TVRCManager(EGG::Heap* heap);
        virtual ~TVRCManager();

        void setEnable(BOOL flag);

        void update();

        void loadDatabase();

        void resetProcessAsync(BOOL flag);
        BOOL waitResetProcessCompleted();

        s32 getTrigger();

        BOOL snd_shutup(BOOL stopDma);
        s32 trans_cmd(s32 command);

        BOOL isTVRCChannel(u32 titleCode);

        static TVRCManager* getHandle() { return m_handle; }

    private:
        BOOL loadResources_(EGG::Heap* heap);

        static void initManagerTask(void* work);

        static TVRCManager* m_handle;

        enum {
            STATE_0,
            STATE_1,
            STATE_2,
            STATE_3,
            STATE_4,
            STATE_5,
            STATE_6,
            STATE_7,
            STATE_8,
            STATE_9,
            STATE_10,
            STATE_11,
            STATE_12,
        };

        u32 mbDisabledTriggerEnabled;
        BOOL mbInitialized;          // 0x08
        nand::SharedFile* mpDBFile;  // 0x0C
        BOOL mbResetting;            // 0x10
        s32 mCurrentCommand;         // 0x14
        u32 mRepeatCount;
        u32 mbRepeatCommand;
        u32 mModelMakerID;    // 0x20
        u32 mModelType;       // 0x24
        BOOL mbPrepTVRC;      // 0x28
        void* mpDatabaseArc;  // 0x2C
        OSTime mCommandTransitionTime;
        OSTime mMuteStartTime;
        OSTime mSoundShutupTime;
        OSTime mLastCommandTime;
        int mCmdMaps[TVRC_COMMAND_MAP_MAX];  // 0x50
        u32 mState;                          // 0x70
        OSTick mDisabledTriggerTick;
        BOOL mbDisabled;  // 0x78
        BOOL mbDisabledTriggerPending;
        u8 mDisabledTriggerState;
        undefined unused_0x81[7];
    };
}  // namespace ipl

#endif  // IPL_TVRC_MANAGER_H
