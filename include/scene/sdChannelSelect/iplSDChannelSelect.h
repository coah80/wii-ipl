#ifndef IPL_SCENE_SD_CHANNEL_SELECT_H
#define IPL_SCENE_SD_CHANNEL_SELECT_H

#include "iplSceneUIHeader.h"

#include <nw4r/math.h>

#include "scene/sdChannelSelect/iplSDChannelObj.h"
#include "system/iplNandSDWorker.h"
#include "math/iplMathTypes.h"

namespace ipl {
    namespace controller {
        class Interface;
    }
    namespace channel {
        class RsoThread;
    }
    namespace scene {
        class SDChannelSelectEvent;
        class SDChannelSelectBtnEvent;
    }
    class NandSDWorker;

    namespace scene {
        union SDChannelSelectCommandArguments {
            u32 values[3];
            NandSDWorker::AppBlocksInfo* appBlocks[3];
            NandSDWorker::TitleIdList* titleLists[3];
            void* pointers[3];
        };

        struct SDChannelSelectCommand {
            u32 type;                               // 0x00
            u32 unknown_0x04;                       // 0x04
            u64 titleId;                            // 0x08
            SDChannelSelectCommandArguments arguments;  // 0x10
            u32 unknown_0x1C;                       // 0x1C

            void copyFrom(const SDChannelSelectCommand& other);
        };

        class SDChannelSelectCommandQueue {
        public:
            BOOL push(const SDChannelSelectCommand& command);
            BOOL pop();

            int getCount() const { return mCount; }

            friend class SDChannelSelect;

        private:
            SDChannelSelectCommand mEntries[4];     // 0x00
            s32 mCap;                               // 0x80
            s32 mCount;                             // 0x84
            s32 mRead;                              // 0x88
            s32 mWrite;                             // 0x8C
        };

        class SDChannelSelectNoticeQueue {
        public:
            BOOL push(const SDChannelSelectCommand& command) {
                if (mCap == mCount) {
                    return FALSE;
                }
                mEntries[mWrite].copyFrom(command);
                if (++mWrite >= mCap) {
                    mWrite = 0;
                }
                mCount++;
                return TRUE;
            }
            BOOL pop();

            int getCount() const { return mCount; }

            friend class SDChannelSelect;

        private:
            SDChannelSelectCommand mEntries[42];    // 0x00
            s32 mCap;                               // 0x540
            s32 mCount;                             // 0x544
            s32 mRead;                              // 0x548
            s32 mWrite;                             // 0x54C
        };

        FADER_SCENE_CLASS(SDChannelSelect) {
        public:
            SDChannelSelect(EGG::Heap * heap);
            virtual ~SDChannelSelect();


            void prepare();
            void create();

            void calcCommon();
            FaderSceneCommand calcFadein();
            FaderSceneCommand calcNormal();
            void initCalcFadeout();
            FaderSceneCommand calcFadeout();

            void draw();
            void destroy();

            BOOL isResetProcessDone();
            void startResetting();

            SDChannelObj* findChannelObject() {
                return NULL;
            }
            SDChannelObj* findChannelObject(int page, int index) const;
            NandSDWorker::WorkSDState getSDState() const {
                return static_cast<NandSDWorker::WorkSDState>(mSelState);
            }
            NandSDWorker* getWorker() {
                return mpWorker;
            }

            int getSelectChan(int dir, int* pageOut, int* indexOut);
            void setSelectChan(int page, int index, SDChannelObj* chanObj);
            BOOL isAnyChanMoving();
            BOOL startChanAnime(int page);
            void getChanSelectState(int page, int index);
            int startSDWorker(NandSDWorker::AppBlocksInfo* freeArea, NandSDWorker::AppBlocksInfo* needed, void* unk1, void* unk2, void* unk3, int type);
            void clearCommandQueue();
            void clearNoticeQueue();
            BOOL enqueueResultNotice(u32 titleId);
            BOOL enqueueChannelNotice(u32 channel, u32 highTitleId, u32 lowTitleId, u32 freeOut);
            BOOL enqueueMoveNotice(u32 channel, u32 highTitleId, u32 lowTitleId);
            BOOL enqueueStateNotice(u32 channel, u32 highTitleId, u32 lowTitleId, u32 state);
            BOOL enqueueErrorNotice(u32 arg1, u32 arg2);
            BOOL enqueueCommandNotice(u32 arg1, u32 arg2, u32 arg3);
            BOOL enqueueDeleteNotice(u32 channel, u32 highTitleId, u32 lowTitleId);
            void processWorkerCommands();
            void handleWorkerStartup();
            void handleNandTitleCount();
            void handleNandTitleUsage();
            void handleSDTitleList();
            static int compareTitleUsage(const void* a, const void* b);
            static int compareTitleInfo(const void* a, const void* b);
            void handleSDTitleListResult();
            void refreshAfterSDTitleList();
            void refreshChannelList();
            BOOL getNandFree(NandSDWorker::AppBlocksInfo* freeOut);
            BOOL fn_813E05C0(int page);
            void fn_813E0624(int page, int index);

            controller::Interface* getController();

            friend class SDChannelTitle;
            friend class SDMemory;
            friend class SDChannelSelectEvent;
            friend class SDChannelSelectBtnEvent;

        private:
            nw4r::ut::List mChanList;               // 0x58
            nand::LayoutFile* mpChanLayoutFile;     // 0x64
            layout::Object* mpLayout;               // 0x68
            math::HermiteIntp<math::VEC3>* mHandlers[4];  // 0x6C
            gui::PaneManager* mpGui;                // 0x7C
            layout::Object* mpTimerAnim;            // 0x80
            layout::Object* mpAnimLayout1;          // 0x84
            layout::Object* mpAnimLayout2;          // 0x88
            layout::Object* mpAnimLayout3;          // 0x8C
            layout::Object* mpAnimLayout6;          // 0x90
            SDChannelSelectBtnEvent* mpEvent;       // 0x94
            int mState;                             // 0x98
            int mChanPage;                          // 0x9C
            int mChanCount;                         // 0xA0
            int mChanIndex;                         // 0xA4
            f32 mChanSizeX;                         // 0xA8
            f32 mChanSizeY;                         // 0xAC
            math::VEC3 mVec;                        // 0xB0
            math::VEC2 mVec2;                       // 0xBC
            f32 mAspectScale;                       // 0xC4
            u8 mbFlagC8;                            // 0xC8
            u8 mbFlagC9;                            // 0xC9
            u8 unk_0xCA[0x2];                       // 0xCA
            EGG::Heap* mpWorkHeap;                  // 0xCC
            EGG::Heap* mpHeap1;                     // 0xD0
            EGG::Heap* mpHeap2;                     // 0xD4
            EGG::Heap* mpObjHeap;                   // 0xD8
            nw4r::math::VEC2 mCursorPos;              // 0xDC
            int mCtrlChan;                          // 0xE4
            int mSelPage;                           // 0xE8
            int mSelIndex;                          // 0xEC
            int mFieldF0;                           // 0xF0
            int mFieldF4;                           // 0xF4
            int mFieldF8;                           // 0xF8
            int mFieldFC;                           // 0xFC
            int mCounter100;                        // 0x100
            u8 unk_0x104;                           // 0x104
            u8 unk_0x105;                           // 0x105
            u8 unk_0x106[0x2];                      // 0x106
            SDChannelObj* mpSwapChanObj;            // 0x108
            layout::Object* mpAnimLayout4;          // 0x10C
            layout::Animator* mpMoveAnim;           // 0x110
            EGG::ExpHeap* mpCsHeap;                // 0x114
            channel::RsoThread* mpRsoThread;        // 0x118
            u8 unk_0x11C[0x4];                      // 0x11C
            SDChannelSelectCommandQueue mCmdQueue; // 0x120
            SDChannelSelectNoticeQueue mChanQueue;  // 0x1B0
            int mSelState;                          // 0x700
            s32 unk_0x704;                          // 0x704
            int mMountFlag;                         // 0x708
            int mAsyncFlag;                         // 0x70C
            void* mpWorkBuf1;                       // 0x710
            void* mpWorkBuf2;                       // 0x714
            NandSDWorker* mpWorker;                 // 0x718
            void* mpBuf71C;                         // 0x71C
            void* mpBuf720;                         // 0x720
            void* mpBuf724;                         // 0x724
            s32 unk_0x728;                          // 0x728
            s32 unk_0x72C;                          // 0x72C
            SDChannelObj* mpPendingChan;            // 0x730
            s32 unk_0x734;                          // 0x734
            s32 unk_0x738;                          // 0x738
            s32* mpChanTable;                       // 0x73C
            u8 unk_0x740[0x4];                      // 0x740
            int mResetState;                        // 0x744
            layout::Object* mpAnimLayout5;          // 0x748
            layout::Object* mDialogAnim;            // 0x74C
            layout::Object* mpBtnLayout;            // 0x750
            s32 unk_0x754;                          // 0x754
            u8 mFlag758;                            // 0x758
            u8 mFlag759;                            // 0x759
            u8 mFlag75A;                            // 0x75A
            u8 unk_0x75B[0x1];                      // 0x75B
            s32 unk_0x75C;                          // 0x75C
            int mReqType;                           // 0x760
            nand::File* mpReqFile;                  // 0x764
            u32 unk_0x768;                          // 0x768
            u32 mReqParam;                          // 0x76C
            OSTime mLastTime;                       // 0x770
            nand::File* mpThumbData;                // 0x778
            u8 unk_0x77C;                           // 0x77C
            u8 unk_0x77D;                           // 0x77D
            u8 unk_0x77E;                           // 0x77E
            u8 unk_0x77F;                           // 0x77F

        private:
            void enqueueStartNotice();
            BOOL enqueueFinishNotice();
            BOOL enqueueNotice(u32 titleId, u32 arg1, u32 arg2);
            BOOL enqueueLoadNotice();
            BOOL enqueuePageNotice();
            void handleNandTitleUsageComplete();
            void handleSDMountComplete();
            void handleSDChannelUpdateComplete();
            void handleSDCardReady();
            void handleCardCommand();
            void handleCopyComplete();
            void handleSDLocationUpdateComplete();
            void handleSDLocationReadComplete();
            void handleMoveComplete();
            void updateChannelNotices(int dir, int focusedIndex);
            void processWorkerState();
            void updateDialogAnimation();
            void handleBackupFitComplete();
            void handleNandSDCleanupComplete();
            void handleSDDeleteComplete();
            BOOL setDialogMessage(u32 state, u32 message);
            void iplSDChannelSelect_813DCFE0(int* p1, int* p2);
            int iplSDChannelSelect_813DD0AC(NandSDWorker::AppBlocksInfo* freeArea, NandSDWorker::AppBlocksInfo* needed, void* unk1, void* unk2, void* unk3);
            int iplSDChannelSelect_813DD240(NandSDWorker::AppBlocksInfo* freeArea, NandSDWorker::AppBlocksInfo* needed, void* unk1, void* unk2, void* unk3);
            int iplSDChannelSelect_813DD3D8(NandSDWorker::AppBlocksInfo* freeArea, NandSDWorker::AppBlocksInfo* needed, void* unk1, void* unk2, void* unk3);
            int iplSDChannelSelect_813DD5D0(NandSDWorker::AppBlocksInfo* freeArea, NandSDWorker::AppBlocksInfo* needed, void* unk1, void* unk2, void* unk3);
            void iplSDChannelSelect_813DDC80();
            void iplSDChannelSelect_813DDCD8();
            void iplSDChannelSelect_813DDD64();
            void iplSDChannelSelect_813DDDBC();
            void iplSDChannelSelect_813DDE18();
            void iplSDChannelSelect_813DDE44();
            void calcChannelObjects();
            void iplSDChannelSelect_813DEF68();
            void drawChannelObjects();
            void iplSDChannelSelect_813DF2A8();
            void iplSDChannelSelect_813DF3FC();
            void iplSDChannelSelect_813DF558();

            void iplSDChannelSelect_813DFF2C();
            BOOL hasChannelObject(int page, int index) const;
            void iplSDChannelSelect_813E0848(SDChannelObj* chanObj);
            static nw4r::math::VEC3 getChannelPanePosition(SDChannelSelect* scene, int index);
            void iplSDChannelSelect_813E1568();
            void iplSDChannelSelect_813E168C();
            void iplSDChannelSelect_813E1A30();
            void iplSDChannelSelect_813E1C38();
            void iplSDChannelSelect_813E1D50();
            void iplSDChannelSelect_813E1E4C();
            int iplSDChannelSelect_813E1FE8(const char* name, int event, controller::Interface* con);
            void iplSDChannelSelect_813E218C(const char* name, int event, controller::Interface* con);
            void iplSDChannelSelect_813E22F8(controller::Interface* con, int page, int index);
            void iplSDChannelSelect_813E24D8();
            void iplSDChannelSelect_813E2750();
            void createBaseLayout();
            void updateChannelObjects();
            void updateChannelObject(SDChannelObj* chanObj);
            static BOOL iplSDChannelSelect_813DF1E4(SDChannelObj* chanObj) NO_INLINE;
            void iplSDChannelSelect_813DF3E0();
            void iplSDChannelSelect_813DF50C();
            void iplSDChannelSelect_813DF6D0(int page, SDChannelObj* chanObj, int index);
            void createChannelList(int page, bool unk);
            void createChannelObject(int page, int index);
            void destroyUnusedChannelObjects(int page, SDChannelObj* chanObj);
            void destroyChannelObject(SDChannelObj* channel);
            void iplSDChannelSelect_813DFCF0(int idx);
            void iplSDChannelSelect_813DFD64(int idx, int dir);
            BOOL isChannelInCalc(int page, int index, int currentPage) const;
            BOOL iplSDChannelSelect_813E0294(int page);
            void iplSDChannelSelect_813E0398(int state) NO_INLINE;
            void iplSDChannelSelect_813E03B0(int a);
            void iplSDChannelSelect_813E0450(int page, int index);
            nw4r::lyt::Pane* getChannelBasePane(int page, int index, int currentPage) const;
            nw4r::lyt::Pane* getCenterChannelPane(int index) const;
            nw4r::lyt::Pane* getChannelPane(int index) const;
            void iplSDChannelSelect_813E0BEC(nw4r::math::VEC3* pos, int a);
            void calcPageAnimations();
            void iplSDChannelSelect_813E0EE0();
            int iplSDChannelSelect_813E114C(const char* name);
            void iplSDChannelSelect_813E11C4();
            void iplSDChannelSelect_813E195C();
            void iplSDChannelSelect_813E19C8();
            int iplSDChannelSelect_813E26DC(int page, int index);
        };
    }  // namespace scene
}  // namespace ipl

#endif  // IPL_SCENE_SD_CHANNEL_SELECT_H
