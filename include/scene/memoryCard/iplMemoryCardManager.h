#ifndef IPL_SCENE_MEMORY_CARD_MANAGER_H
#define IPL_SCENE_MEMORY_CARD_MANAGER_H

#include <revolution/types.h>
#include <revolution/gx.h>

#include <private/card.h>

#include <wchar.h>

#include "iplMemoryCardLib.h"

namespace ipl {
    namespace scene {
        class __declspec(novtable) MemCardEventListener {
        public:
            MemCardEventListener() {}

            virtual ~MemCardEventListener() {}

            virtual void onMemEvent(long event, u8 slot);
        };

        class MemCardEventHandler : public MemCardEventListener {
        public:
            MemCardEventHandler() {}

            virtual ~MemCardEventHandler();

            virtual void onMemEvent(long event, u8 slot);

            virtual void onMount(u8 slot) = 0;
            virtual void onUnmount(u8 slot) = 0;
            virtual void onAttach(u8 slot) = 0;
            virtual void onDetach(u8 slot) = 0;
            virtual void onCheck(u8 slot) = 0;
            virtual void onFormat(u8 slot) = 0;
            virtual void onRepair(u8 slot) = 0;
            virtual void onRead(u8 slot) = 0;
            virtual void onWrite(u8 slot) = 0;
            virtual void onOpen(u8 slot) = 0;
            virtual void onClose(u8 slot) = 0;
            virtual void onCreate(u8 slot) = 0;
            virtual void onDelete(u8 slot) = 0;
            virtual void onCopy(u8 slot) = 0;
            virtual void onMove(u8 slot) = 0;
            virtual void onRename(u8 slot) = 0;
            virtual void onVerify(u8 slot) = 0;
            virtual void onCommit(u8 slot) = 0;
            virtual void onProbe(u8 slot) = 0;
            virtual void onMountAsync(u8 slot) = 0;
            virtual void onUnmountAsync(u8 slot) = 0;
            virtual void onCheckAsync(u8 slot) = 0;
            virtual void onFormatAsync(u8 slot) = 0;
            virtual void onReadAsync(u8 slot) = 0;
            virtual void onWriteAsync(u8 slot) = 0;
            virtual void onCreateAsync(u8 slot) = 0;
            virtual void onDeleteAsync(u8 slot) = 0;
            virtual void onCopyAsync(u8 slot) = 0;
            virtual void onMoveAsync(u8 slot) = 0;
            virtual void onRenameAsync(u8 slot) = 0;
            virtual void onVerifyAsync(u8 slot) = 0;
            virtual void onCommitAsync(u8 slot) = 0;
            virtual void onProbeAsync(u8 slot) = 0;
            virtual void onFreeBlocks(u8 slot) = 0;
            virtual void onGetLength(u8 slot) = 0;
            virtual void onSetAttrib(u8 slot) = 0;
            virtual void onGetAttrib(u8 slot) = 0;
            virtual void onSlotStatus(u8 slot) = 0;
        };

        typedef struct MCFile {
            u32 fileNo;    // 0x00
            u32 reserved;  // 0x04
            u32 sortKeyHigh;  // 0x08
            s32 sortKey;   // 0x0C
        } MCFile;            // 0x10

        typedef struct MCFileCell {
            wchar_t   comment[2][0x40];  // 0x000
            s16       iconAnmCounter;    // 0x100
            u16       reserved;         // 0x102
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
                sort_file_array(CARD_CHAN_0);
                sort_file_array(CARD_CHAN_1);
            }
            virtual ~MemoryCardManager();

            virtual void onMount(u8 slot) = 0;
            virtual void onUnmount(u8 slot) = 0;
            virtual void onAttach(u8 slot) = 0;
            virtual void onDetach(u8 slot) = 0;
            virtual void onCheck(u8 slot) = 0;
            virtual void onFormat(u8 slot) = 0;
            virtual void onRepair(u8 slot) = 0;
            virtual void onRead(u8 slot) = 0;
            virtual void onWrite(u8 slot) = 0;
            virtual void onOpen(u8 slot) = 0;
            virtual void onClose(u8 slot) = 0;
            virtual void onCreate(u8 slot) = 0;
            virtual void onDelete(u8 slot) = 0;
            virtual void onCopy(u8 slot) = 0;
            virtual void onMove(u8 slot) = 0;
            virtual void onRename(u8 slot) = 0;
            virtual void onVerify(u8 slot) = 0;
            virtual void onCommit(u8 slot) = 0;
            virtual void onProbe(u8 slot) = 0;
            virtual void onMountAsync(u8 slot) = 0;
            virtual void onUnmountAsync(u8 slot) = 0;
            virtual void onCheckAsync(u8 slot) = 0;
            virtual void onFormatAsync(u8 slot) = 0;
            virtual void onReadAsync(u8 slot) = 0;
            virtual void onWriteAsync(u8 slot) = 0;
            virtual void onCreateAsync(u8 slot) = 0;
            virtual void onDeleteAsync(u8 slot) = 0;
            virtual void onCopyAsync(u8 slot) = 0;
            virtual void onMoveAsync(u8 slot) = 0;
            virtual void onRenameAsync(u8 slot) = 0;
            virtual void onVerifyAsync(u8 slot) = 0;
            virtual void onCommitAsync(u8 slot) = 0;
            virtual void onProbeAsync(u8 slot) = 0;
            virtual void onFreeBlocks(u8 slot) = 0;
            virtual void onGetLength(u8 slot) = 0;
            virtual void onSetAttrib(u8 slot) = 0;
            virtual void onGetAttrib(u8 slot) = 0;

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

            void setEventHandler(MemCardEventListener* eventHandler) {
                mpEventHandler = eventHandler;
            }

        private:
            GXTexObj* initBannerTexture(u8 slot, s32 file, void* data) {
                GXInitTexObj(&mFileCell[slot][file].banner, data, CARD_BANNER_WIDTH, CARD_BANNER_HEIGHT,
                             GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, GX_FALSE);
                return &mFileCell[slot][file].banner;
            }

            void initBannerTextureCI(u8 slot, s32 file, void* data) {
                GXInitTexObjCI(&mFileCell[slot][file].banner, data, CARD_BANNER_WIDTH, CARD_BANNER_HEIGHT,
                               GX_TF_C8, GX_CLAMP, GX_CLAMP, GX_FALSE, GX_TLUT0);
            }

            GXTlutObj* initBannerPalette(u8 slot, s32 file, void* data) {
                GXInitTlutObj(&mFileCell[slot][file].bannerTlut, data, GX_TL_RGB5A3, 0x100);
                return &mFileCell[slot][file].bannerTlut;
            }

            u32                  reserved;            // 0x00004
            MCFile               mFile[2][CARD_MAX_FILE];      // 0x00008
            MCFileCell           mFileCell[2][CARD_MAX_FILE];  // 0x00FE8
            s32                  mLastResult;         // 0x16930
            s32                  mLastCmd;            // 0x16934
            u32                  mReservedResult;         // 0x16938
            MemCardEventListener* mpEventHandler;      // 0x1693C
        };
    }  // namespace scene
}  // namespace ipl

#endif  // IPL_SCENE_MEMORY_CARD_MANAGER_H
