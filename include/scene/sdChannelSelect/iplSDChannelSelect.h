#ifndef IPL_SCENE_SD_CHANNEL_SELECT_H
#define IPL_SCENE_SD_CHANNEL_SELECT_H

#include "iplSceneUIHeader.h"

#include "math/iplInterporation.h"
#include "scene/sdButton/iplSDButton.h"
#include "system/iplChannelRsoThread.h"
#include "system/iplNandSDWorker.h"

namespace ipl {
    namespace scene {
#ifdef IPL_SD_CHANNEL_SELECT_CPP
        class SDChannelSelect;
        namespace {
            class SDChannelSelectEventHandler;
            class SDChannelSelectButtonEventHandler;
        }
#endif

        class SDChannelObj {
        public:
            SDChannelObj(EGG::Heap* heap, int page, int index);
            ~SDChannelObj();

            EGG::Heap* getHeap() const { return mpHeap; }
            int getPage() const { return mPage; }
            int getIndex() const { return mIndex; }
            nw4r::math::VEC3& getTranslate() const;

#if defined(IPL_SD_CHANNEL_TITLE_CPP) || defined(IPL_SD_CHANNEL_OBJ_CPP)
        public:
#else
        private:
#endif
            friend class SDChannelSelect;

            nw4r::ut::Link mListLink;
            EGG::ExpHeap* mpDialogHeap;
            EGG::ExpHeap* mpChannelHeap;
            EGG::Heap* mpHeap;
#ifdef IPL_SD_CHANNEL_OBJ_CPP
            int mState;
#else
            u32 mState;
#endif
            int mPage;
            int mIndex;
            nand::LayoutFile* mpLayoutFile;
            nw4r::lyt::Pane* mpPane;
#ifdef IPL_SD_CHANNEL_OBJ_CPP
            nand::File* mpPaneAnimator;
#else
            layout::Animator* mpPaneAnimator;
#endif
            layout::Object* mpBaseLayout;
            layout::Animator* mpBaseAnimator;
            layout::Object* mpPageLayout;
            layout::Animator* mpPageAnimators[3];
            int mPageAnimation;
            int mPageAnimationFrame;
            layout::Object* mpDialogLayout;
            layout::Animator* mpDialogAnimator;
            int mDialogState;
            int mDialogFrame;
            int mDialogTimer;
            int mAnimationState;
            nw4r::lyt::Group* mpNewMessageGroup;
#ifdef IPL_SD_CHANNEL_OBJ_CPP
            layout::Animator* mpNewMessageAnimator;
#else
            int mNewMessageCount;
#endif
            u8 mbNewMessageGroupActive;
            int mNewMessageState;
            int mNewMessageFrame;
            f32 mOffsetX;
            f32 mOffsetY;
            f32 mAspectRatioScale;
            int mStateFlags;
            void* mpThumbnailData;
            NandSDWorker::SDAppMetaEntry mAppMeta;
        };
        extern "C" void iplSDChannelObj_813E3104(SDChannelObj* channel);
        extern "C" void iplSDChannelObj_813E311C(SDChannelObj* channel, EGG::ExpHeap* firstHeap,
                                                  EGG::ExpHeap* secondHeap);
        extern "C" void iplSDChannelObj_813E322C(SDChannelObj* channel);
        extern "C" void iplSDChannelObj_813E32C8(SDChannelObj* channel);
        extern "C" void iplSDChannelObj_813E34E0(SDChannelObj* channel);
        extern "C" void iplSDChannelObj_813E3178(SDChannelObj* channel, nw4r::lyt::Pane* pane);
        extern "C" void iplSDChannelObj_813E3180(SDChannelObj* channel, nand::LayoutFile* layoutFile);
        extern "C" void iplSDChannelObj_813E3304(SDChannelObj* channel);
        extern "C" void iplSDChannelObj_813E330C(SDChannelObj* channel);
        extern "C" void iplSDChannelObj_813E3354(SDChannelObj* channel, int state);
        extern "C" void iplSDChannelObj_813E33EC(SDChannelObj* channel, int state);
        extern "C" void iplSDChannelObj_813E3480(SDChannelObj* channel, bool selected);
        extern "C" void iplSDChannelObj_813E34E8(SDChannelObj* channel, int enabled);
        extern "C" void* iplSDChannelObj_813E3128(SDChannelObj* channel);
        extern "C" bool iplSDChannelObj_813E3330(SDChannelObj* channel);

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
            bool used;
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

            NandSDWorker::WorkSDState getSDState() const {
                return static_cast<NandSDWorker::WorkSDState>(mCurrentSDState);
            }
            NandSDWorker* getWorker() const { return mpSDWorker; }

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

            void onButtonEvent(const char* paneName, u32 event,
                               const controller::Interface* controller);
            BOOL onEventDerived(const char* paneName, u32 event,
                                controller::Interface* controller);
            bool collectTitlesByUsage(const s32* firstUsage, const s32* secondUsage,
                                      ESTitleId* titleIds, char* titleNames,
                                      u32* titleCount);

            static const char* mscChannelPaneNames[PAGE_COUNT][MAX_CHANNEL_INDEX];
            static const char* mscBasePaneNames[PAGE_COUNT];
            static const char* mscPicturePaneNames[PAGE_COUNT];
            static const char* mscEdgePaneNames[PAGE_COUNT];
            static const char* mscClockPaneNames[3];
            static const char* mscMaskPaneName;

#if defined(IPL_SD_CHANNEL_TITLE_CPP) || defined(IPL_SD_CHANNEL_OBJ_CPP) || defined(IPL_SDMEMORY_CPP)
        public:
#else
        private:
#endif
#ifdef IPL_SD_CHANNEL_SELECT_CPP
            friend class SDChannelSelectEventHandler;
            friend class SDChannelSelectButtonEventHandler;
#endif
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
            void drawChannelTransitionObjects();
            void drawChannelObjects();
            bool isChannelInCalc(int page, int index, int currentPage) const;
            nw4r::lyt::Pane* getChannelBasePane(int page, int index, int currentPage) const;
            int getCenterChannelIndex(const char* paneName) const;
            nw4r::lyt::Pane* getCenterChannelPane(int index) const;
            nw4r::lyt::Pane* getChannelPane(int index) const;
            static math::VEC3 getChannelPanePosition(SDChannelSelect* scene, int index);
            void calcPageAnimations();
            void processNormalInput();
            void updateArrowVisibility();
            void processWorkerState();
            void updateDialogAnimation();
            void initializeNormalPage();
            void updatePageTransform();
            void setChannelScissor(const SDChannelObj* channel) const;
            bool isCurrentTitleUsageEnough(const s32* usage) const;
            void getCurrentTitleUsage(s32* bytes, s32* blocks) const;
            bool collectTitlesByChannelOrder(const s32* firstUsage, const s32* secondUsage,
                                             ESTitleId* titleIds, char* titleNames,
                                             u32* titleCount);
            bool collectTitlesFromNandUsage(const s32* firstUsage, const s32* secondUsage,
                                            ESTitleId* titleIds, char* titleNames,
                                            u32* titleCount);
            bool collectTitlesBySpecialChannels(const s32* firstUsage, const s32* secondUsage,
                                                ESTitleId* titleIds, char* titleNames,
                                                u32* titleCount);
            bool collectTitlesForMode(const s32* firstUsage, const s32* secondUsage,
                                      ESTitleId* titleIds, char* titleNames,
                                      u32* titleCount, int searchMode);
            bool findAdjacentChannel(int direction, int* page, int* index) const;
            void setStateAndPlaySelectSound(int state) NO_INLINE;
            void finishDialogOperation();
            void finishDialogTransition();
            void processWorkerCommands();
            void handleWorkerStartup();
            void handleNandTitleCount();
            void handleNandTitleUsage();
            void handleNandTitleUsageComplete();
            void handleSDTitleList();
            void handleSDTitleListResult();
            void refreshAfterSDTitleList();
            void handleSDChannelUpdateComplete();
            void updateChannelNotices(int pageOffset, int index);
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
            void destroyUnusedChannelObjects(int currentPage, SDChannelObj* keepChannel);
            void refreshChannelList();
            bool hasChannelObject(int page, int index) const;
            SDChannelObj* findChannelObject(int page, int index) const;
            void createChannelObject(int page, int index);
            void createBaseLayout();
            void createSceneLayouts();
            BOOL isChannelMoveTarget(int page, int index) const;
            void selectChannel(int page, int index);
            BOOL prepareRestarting(int page);
            void startPageTransition(int page, int index);
            void setCurrentPageAndRefresh(int page, int index, SDChannelObj* keepChannel);
            void handleFourPageDialog();
            void handleThreePageDialog();
            void setPageActionFrame();
            void advancePageAnimation();
            void finishPageScroll();
            void finishCardDialog();
            void flushSaveDataAndMountSD();
            void startDrag(const controller::Interface* controller, int page, int index);
            void finishDrag();
            void moveDrag();
            void updateDragState();
            void updateDragPageTransition();
            void finishDragWait();
            void finishDragPageTransition();
            void applyChannelMove();
            void finishChannelMove();
            void resetDragPreview();
            void finishDragPageChange();
            BOOL isPageCreated(int page) const;
            void refreshPageObjects(int page, SDChannelObj* keepChannel, int noticeIndex);
            void updateChannelObjectOrder(int page);
            void moveChannelObjectsToDrawOrder(int page, int mode);
            void setLayoutFrame(int state);
            BOOL tellStartingZoomAnm();
            void initPageAnimations(const math::VEC3& position, int direction);
#ifdef IPL_SD_CHANNEL_SELECT_CPP
            void removeNandTitleInfo(ESTitleId titleId) {
                u32 titleCount = mNandTitleCount;
                u32 index = 0;
                for (; index < titleCount; ++index) {
                    if (mpNandTitleInfo[index].curTitleId == titleId) {
                        break;
                    }
                }
                if (index < mNandTitleCount) {
                    for (; index < mNandTitleCount - 1; ++index) {
                        NandSDWorker::TitleUsage& nextTitle = mpNandTitleInfo[index + 1];
                        NandSDWorker::TitleUsage& currentTitle = mpNandTitleInfo[index];
                        currentTitle.curTitleId = nextTitle.curTitleId;
                        currentTitle.size = nextTitle.size;
                        currentTitle.inode = nextTitle.inode;
                    }
                    --mNandTitleCount;
                }
            }
            nw4r::math::VEC3 getPageTransitionPosition(int index) const {
                nw4r::math::VEC3 position(0.0f, 0.0f, 0.0f);
                nw4r::lyt::Pane* pane = getCenterChannelPane(index);
                PSMTXMultVec(pane->GetGlobalMtx(), position, position);
                return position;
            }
#endif
            static BOOL isChannelReady(const SDChannelObj* channel);
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
            math::VEC3 mPosition;
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
            void* mpCurrentChannel;
            layout::Object* mpStateLayout;
            layout::Animator* mpHelpLayout;
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
            mutable NandSDWorker::TitleUsage* mpNandTitleInfo;
            mutable s32 mFirstTitleCount;
            mutable s32 mSecondTitleCount;
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
            int mOperationState;
            int mDialogState;
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
