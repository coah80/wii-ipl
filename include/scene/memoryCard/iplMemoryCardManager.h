#ifndef IPL_SCENE_MEMORY_CARD_MANAGER_H
#define IPL_SCENE_MEMORY_CARD_MANAGER_H

#include <revolution/types.h>
#include <revolution/gx.h>

#include <private/card.h>

#include <wchar.h>

#include "iplMemoryCardLib.h"

namespace ipl {
    namespace scene {
        class MemCardEventHandler {
        public:
            MemCardEventHandler() {}

            virtual ~MemCardEventHandler();

            virtual void onMemEvent(long event, u8 slot);
        };

        typedef struct MCFile {
            u32 fileNo;    // 0x00
            u32 unk_0x04;  // 0x04
            u32 unk_0x08;  // 0x08
            s32 sortKey;   // 0x0C
        } MCFile;            // 0x10

        typedef struct MCFileCell {
            wchar_t   comment[2][0x40];  // 0x000
            s16       iconAnmCounter;    // 0x100
            u16       unk_0x102;         // 0x102
            GXTexObj  icon;              // 0x104
            GXTexObj  banner;            // 0x124
            GXTlutObj iconTlut;          // 0x144
            GXTlutObj bannerTlut;        // 0x150
        } MCFileCell;                        // 0x15C

        class MemoryCardManager {
        public:
            MemoryCardManager() {
                MCFileCell* pCell = mFileCell[0];
                do {
                    pCell->iconAnmCounter = 0;
                    wmemset(pCell->comment[0], 0, 0x40);
                    pCell++;
                } while (pCell < mFileCell[2]);
                mLastResult = 0;
                mLastCmd    = 0;
                __CARDSetDiskID(NULL);
                memorycard::initCardThread();
                sort_file_array(0);
                sort_file_array(1);
            }
            virtual ~MemoryCardManager();

            void calc();

            bool isSlotReady(u8 slot);
            bool isSlotNoCard(u8 slot);
            long isSlotWrongDevice(u8 slot);

            void sort_file_array(u8 slot);

            void sendCardCmdMove(u8 slot, s16 index);
            void sendCardCmdCopy(u8 slot, s16 index);
            void sendCardCmdDelete(u8 slot, s16 index);
            void sendCardCmdFormat(u8 slot);

            bool isDistSlot(u8 slot, long* pState);
            bool isMoveEnable(u8 slot, u32 index, long* pCode);
            bool isCopyEnable(u8 slot, u32 index, long* pCode);

            bool isIconValidate(u8 slot, s16 index);
            bool isBannerEnable(u8 slot, s16 index);

            void update_icon_anm();
            void update_file_array(u8 slot);
            void update_change_cardstate(u8 slot);

            GXTexObj*       create_icon(u8 slot, s16 index);
            GXTexObj*       create_icon(u8 slot, s16 index, long start);
            GXTexObj*       _create_icon(u8 slot, s16 fileNo, long start);
            const wchar_t*  getComment(u8 slot, s16 index, int which);
            GXTexObj*       create_banner(u8 slot, s16 index);
#ifdef IPL_GC_WINDOW_CPP
            u32             getBlocks(u8 slot, s16 index);
#else
            u16             getBlocks(u8 slot, s16 index);
#endif
#ifdef IPL_MEMORY_CARD_CPP
            u32             getFreeBlocks(u8 slot);
#else
            u16             getFreeBlocks(u8 slot);
#endif

            void setEventHandler(MemCardEventHandler* eventHandler) {
                mpEventHandler = eventHandler;
            }

        private:
            u32                  unk_0x04;            // 0x00004
            MCFile               mFile[2][0x7F];      // 0x00008
            MCFileCell           mFileCell[2][0x7F];  // 0x00FE8
            s32                  mLastResult;         // 0x16930
            s32                  mLastCmd;            // 0x16934
            u32                  unk_0x16938;         // 0x16938
            MemCardEventHandler* mpEventHandler;      // 0x1693C
        };
    }  // namespace scene
}  // namespace ipl

#endif  // IPL_SCENE_MEMORY_CARD_MANAGER_H
