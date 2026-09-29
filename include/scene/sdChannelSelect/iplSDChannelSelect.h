#ifndef IPL_SCENE_SD_CHANNEL_SELECT_H
#define IPL_SCENE_SD_CHANNEL_SELECT_H

#include "iplSceneUIHeader.h"

#include "math/iplInterporation.h"
#include "scene/sdButton/iplSDButton.h"
#include "system/iplChannelRsoThread.h"
#include "system/iplNandSDWorker.h"

namespace ipl {
    namespace scene {
        class SDChannelObj {
        public:
            ~SDChannelObj();

            EGG::Heap* getHeap() const { return mpHeap; }
            int getPage() const { return mPage; }
            int getIndex() const { return mIndex; }

        private:
            nw4r::ut::Link mListLink;
            f32 mOffsetX;
            f32 mOffsetY;
            EGG::Heap* mpHeap;
            u32 mState;
            int mPage;
            int mIndex;
        };
        extern "C" void iplSDChannelObj_813E3104(SDChannelObj* channel);
        extern "C" void iplSDChannelObj_813E311C(SDChannelObj* channel, EGG::ExpHeap* firstHeap,
                                                  EGG::ExpHeap* secondHeap);
        extern "C" void iplSDChannelObj_813E322C(SDChannelObj* channel);
        extern "C" void iplSDChannelObj_813E3178(SDChannelObj* channel, nw4r::lyt::Pane* pane);
        extern "C" void iplSDChannelObj_813E3180(SDChannelObj* channel, nand::LayoutFile* layoutFile);
        extern "C" void iplSDChannelObj_813E3304(SDChannelObj* channel);
        extern "C" void iplSDChannelObj_813E330C(SDChannelObj* channel);

        union SDChannelSelectCommandArguments {
            u32 values[3];
            NandSDWorker::AppBlocksInfo* appBlocks[3];
            NandSDWorker::TitleIdList* titleLists[3];
            void* pointers[3];
        };

        struct SDChannelSelectCommand {
            u32 type;
            u64 titleId;
            SDChannelSelectCommandArguments arguments;

            void copyFrom(const SDChannelSelectCommand& other);
        };

        struct SDChannelSelectCommandQueue {
            SDChannelSelectCommand commands[4];
            int capacity;
            int count;
            int readIndex;
            int writeIndex;

            SDChannelSelectCommandQueue(u32 capacity, u32 count, u32 readIndex, u32 writeIndex)
                : capacity(capacity), count(count), readIndex(readIndex), writeIndex(writeIndex) {
            }

            bool push(const SDChannelSelectCommand& command);
            bool pop();
        };

        struct SDChannelSelectTitleInfo {
            ESTitleId32 titleId;
            u32 state;
        };

        struct SDChannelSelectNoticeQueue {
            SDChannelSelectCommand notices[42];
            int capacity;
            int count;
            int readIndex;
            int writeIndex;

            SDChannelSelectNoticeQueue(u32 capacity, u32 count, u32 readIndex, u32 writeIndex)
                : capacity(capacity), count(count), readIndex(readIndex), writeIndex(writeIndex) {
            }

            bool pop();
        };

        FADER_SCENE_CLASS(SDChannelSelect) {
        public:
            enum {
                PAGE_COUNT = 5,
            };

            SDChannelSelect(EGG::Heap* heap);
            virtual ~SDChannelSelect();

            virtual BOOL isResetProcessDone();
            virtual void startResetting();
            virtual void prepare();
            virtual void create();
            virtual void draw();
            virtual void destroy();
            virtual void initCalcFadeout();
            virtual void calcCommon();
            virtual FaderSceneCommand calcFadein();
            virtual FaderSceneCommand calcNormal();
            virtual FaderSceneCommand calcFadeout();

            static const char* mscChannelPaneNames[PAGE_COUNT][MAX_CHANNEL_INDEX];
            static const char* mscBasePaneNames[PAGE_COUNT];
            static const char* mscPicturePaneNames[PAGE_COUNT];
            static const char* mscEdgePaneNames[PAGE_COUNT];
            static const char* mscClockPaneNames[3];
            static const char* mscMaskPaneName;

        private:
            void enqueueStartNotice();
            bool enqueueFinishNotice();
            bool enqueueNotice(u32 highTitleId, u32 lowTitleId, u32 result);
            bool enqueueLoadNotice();
            bool enqueuePageNotice();
            bool enqueueResultNotice(u32 result);
            bool enqueueChannelNotice(u32 controller, u32 page, u32 index, u32 value);
            bool enqueueMoveNotice(u32 controller, u32 page, u32 index);
            bool enqueueStateNotice(u32 controller, u32 page, u32 index, u32 state);
            bool enqueueErrorNotice(u32 page, u32 index);
            bool enqueueCommandNotice(u32 page, u32 index, u32 command);
            bool enqueueDeleteNotice(u32 controller, u32 page, u32 index);
            void clearCommandQueue();
            void clearNoticeQueue();
            void calcChannelObjects();
            void updateChannelObjects();
            void updateChannelObject(SDChannelObj* channel);
            void drawChannelObjects();
            bool isChannelInCalc(int page, int index, int currentPage) const;
            nw4r::lyt::Pane* getChannelBasePane(int page, int index, int currentPage) const;
            nw4r::lyt::Pane* getCenterChannelPane(int index) const;
            nw4r::lyt::Pane* getChannelPane(int index) const;
            static math::VEC3 getChannelPanePosition(SDChannelSelect* scene, int index);
            void updateArrowVisibility();
            void processWorkerState();
            void updateDialogAnimation();
            void processWorkerCommands();
            void handleWorkerStartup();
            void handleNandTitleCount();
            void handleNandTitleUsage();
            void handleNandTitleUsageComplete();
            void handleSDTitleList();
            void handleSDMountComplete();
            void handleCopyComplete();
            void handleDeleteComplete();
            void handleMoveComplete();
            void handleStorageCheckComplete();
            void handleCardCommand();
            void handleSDCardReady();
            void handleSDLocationUpdateComplete();
            void handleSDLocationReadComplete();
            void handleBackupFitComplete();
            void handleNandSDCleanupComplete();
            void handleSDDeleteComplete();
            bool setDialogMessage(u32 state, u32 message);
            static int compareTitleUsage(const void* lhs, const void* rhs);
            static int compareTitleInfo(const void* lhs, const void* rhs);
            void createChannelList(int page, bool force);
            void destroyChannelObject(SDChannelObj* channel);
            bool hasChannelObject(int page, int index) const;
            void createChannelObject(int page, int index);
            void createBaseLayout();
            void updateNoCardLayouts();
            void createChannelThumbnails();

            nw4r::ut::List mChannelObjects;
            nand::LayoutFile* mpLayoutFile;
            layout::Object* mpLayout;
            math::HermiteIntp<math::VEC3>* mpPageAnimations[4];
            gui::PaneManager* mpPaneManager;
            layout::Object* mpNoCardLayout;
            layout::Object* mpPageLayouts[3];
            layout::Object* mpDialogLayout;
            SDButtonEventHandlerBase* mpButtonEventHandler;
            int mState;
            int mCurrentPage;
            int mPageCount;
            int mCurrentChannelIndex;
            f32 mThumbOffsetX;
            f32 mThumbOffsetY;
            nw4r::math::VEC3 mPosition;
            math::VEC2 mScale;
            f32 mAspectRatioScale;
            bool mbLeftArrowVisible;
            bool mbRightArrowVisible;
            u8 mArrowState;
            u8 mNoCardState;
            EGG::UnitHeap* mpLayoutHeap;
            EGG::ExpHeap* mpDialogHeap;
            EGG::ExpHeap* mpChannelHeap;
            EGG::ExpHeap* mpThumbnailHeap;
            nw4r::math::VEC2 mPointerPosition;
            int mControllerChannel;
            int mSourcePage;
            int mSourceIndex;
            int mDestinationPage;
            int mDestinationIndex;
            int mPendingPage;
            int mPendingIndex;
            int mMoveState;
            bool mbButtonEnabled;
            bool mbDialogActive;
            u16 mInputFlags;
            SDChannelObj* mpCurrentChannel;
            layout::Object* mpStateLayout;
            layout::Object* mpHelpLayout;
            EGG::ExpHeap* mpRsoHeap;
            channel::RsoThread* mpRsoThread;
            u32 mCommandQueueState;
            SDChannelSelectCommandQueue mCommandQueue;
            SDChannelSelectNoticeQueue mNoticeQueue;
            int mCurrentSDState;
            int mPreviousSDState;
            int mWorkerState;
            int mWorkerCommand;
            EGG::Heap* mpWorkerHeap;
            EGG::Heap* mpThumbnailWorkHeap;
            NandSDWorker* mpSDWorker;
            ESTitleId32* mpSDTitleIds;
            SDChannelSelectTitleInfo* mpSDTitleInfo;
            NandSDWorker::TitleUsage* mpNandTitleInfo;
            u32 mFirstTitleCount;
            u32 mSecondTitleCount;
            SDChannelObj* mpCurrentLoadedChannel;
            u32 mSDTitleCount;
            u32 mNandTitleCount;
            u32* mpChannelTitleIds;
            u32 mPendingOperation;
            int mLastOperation;
            layout::Object* mpErrorLayout;
            layout::Object* mpPointerLayout;
            layout::Object* mpHelpButtonLayout;
            int mOperationResult;
            u8 mbShowNoCardMessage;
            u8 mbOperationActive;
            u8 mbSDCardBroken;
            u32 mOperationState;
            u32 mDialogState;
            nand::File* mpSaveDataFile;
            u32 mAnimationState;
            u32 mAnimationTarget;
            OSTime mOperationStartTime;
            nand::File* mpCorruptIconFile;
            u8 mbHazardTitleFound;
            u8 mbChannelLimitReached;
            u8 mbInitialLoadComplete;
            u8 mbNeedsRefresh;
        };
    }
}

#endif
