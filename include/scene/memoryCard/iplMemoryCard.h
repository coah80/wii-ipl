#ifndef IPL_SCENE_MEMORY_CARD_H
#define IPL_SCENE_MEMORY_CARD_H

#include "iplSceneHeader.h"

#include "scene/memoryCard/iplMemoryCardBase.h"
#include "scene/memoryCard/iplMemoryCardManager.h"

#include "math/iplMathTypes.h"

namespace ipl {
    namespace scene {
        class GCSaveData;
        class GCWindow;
        class SavedataEditWindow;

        class MemoryCard : public Base, public MemoryBase {
        public:
            MemoryCard(EGG::Heap* heap);
            virtual ~MemoryCard();

            virtual BOOL isResetAcceptable() const;

            virtual void prepare();
            virtual void create();
            virtual void calc();
            virtual void draw();

            virtual void onPoint(const char* paneName, controller::Interface* controller);
            virtual void onLeft(const char* paneName);
            virtual void onTrig(const char* paneName);

            void onFocus(void* data);
            void onRelease();

            MemoryCardManager* getManager() { return mpManager; }

        private:
            enum {
                SLOT_A = 0,
                SLOT_B,
            };

            void on_fadein1st();
            void on_fadein2nd();
            void on_normal();
            void on_scroll_r();
            void on_scroll_l();
            void on_change_tag1st();
            void on_change_tag2nd();
            void on_fadeout1st();
            void on_fadeout2nd();
            void on_error();
            void on_insert_card();
            void on_detach_card();

            void start_savedata_fadein();
            void start_savedata_fadeout();
            void start_errormessage_fadein();
            int  update_slot();

#ifdef IPL_MEMORY_CARD_CPP
            bool can_scroll_r() const { return mIconCount > 30 && mState == 2; }
            bool can_scroll_l() const { return mIconIndex >= 0 && mState == 2; }
#endif
            void show_arw();
            void show_capacity(u8 slot);

            void scroll_common();
            void start_scroll_r();
            void start_scroll_l();

        private:
            s32                mState;             // 0x88
            s32                mPrevState;         // 0x8C
            u8                 mSlot;              // 0x90
            u8                 mReservedSlot[3];        // 0x91
            s32                mSlotState[2];      // 0x94
            s16                mIconIndex;         // 0x9C
            s16                mIconCount;         // 0x9E
            u8                 mShowArwR;          // 0xA0
            u8                 mShowArwL;          // 0xA1
            u8                 mReservedArrows[2];        // 0xA2
            MemoryCardManager* mpManager;          // 0xA4
            MemoryBaseEvent*   mpEvent;            // 0xA8
            nw4r::ut::List     mSaveDataList;      // 0xAC
            nand::LayoutFile*  mBalloonLayoutFile;  // 0xB8
            nw4r::ut::List     mBalloonList;       // 0xBC
            GCSaveData*        mpFocusSaveData;    // 0xC8
            GCWindow*          mpGCWindow;         // 0xCC
        };
    }  // namespace scene
}  // namespace ipl

#endif  // IPL_SCENE_MEMORY_CARD_H
