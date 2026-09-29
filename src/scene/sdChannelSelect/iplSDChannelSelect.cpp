#define IPL_SD_CHANNEL_SELECT_ACCESS
#define IPL_SD_CHANNEL_SELECT_CPP

#include <decomp/ide.h>

#include "iplSceneUI.h"
#include "system/iplSystem.h"
#include "system/iplSaveDataManager.h"
#include "utility/iplCSFlags.h"
#include "sound/iplSound.h"

#include "scene/sdChannelSelect/iplSDChannelSelect.h"

#include <stdio.h>
#include <stdlib.h>

namespace ipl {
    namespace scene {
        namespace {
            class SDChannelSelectButtonEventHandler : public SDButtonEventHandlerBase {
            public:
                explicit SDChannelSelectButtonEventHandler(SDChannelSelect* scene)
                    : mpScene(scene) {
                }

                void onEventDerived(u32 compId, u32 event, const controller::Interface* con) override {
                }

            private:
                SDChannelSelect* mpScene;
            };

        }

        const char* SDChannelSelect::mscChannelPaneNames[PAGE_COUNT][MAX_CHANNEL_INDEX] = {
            {
                "", "", "", "N_Ch_a04", "", "", "", "N_Ch_a08", "", "", "", "N_Ch_a12",
            },
            {
                "N_Ch_b01", "N_Ch_b02", "N_Ch_b03", "N_Ch_b04", "N_Ch_b05", "N_Ch_b06",
                "N_Ch_b07", "N_Ch_b08", "N_Ch_b09", "N_Ch_b10", "N_Ch_b11", "N_Ch_b12",
            },
            {
                "N_Ch_c01", "N_Ch_c02", "N_Ch_c03", "N_Ch_c04", "N_Ch_c05", "N_Ch_c06",
                "N_Ch_c07", "N_Ch_c08", "N_Ch_c09", "N_Ch_c10", "N_Ch_c11", "N_Ch_c12",
            },
            {
                "N_Ch_d01", "N_Ch_d02", "N_Ch_d03", "N_Ch_d04", "N_Ch_d05", "N_Ch_d06",
                "N_Ch_d07", "N_Ch_d08", "N_Ch_d09", "N_Ch_d10", "N_Ch_d11", "N_Ch_d12",
            },
            {
                "N_Ch_e01", "", "", "", "N_Ch_e05", "", "", "", "N_Ch_e09", "", "", "",
            },
        };

        const char* SDChannelSelect::mscBasePaneNames[PAGE_COUNT] = {
            "BaseMask0", "BaseMask1", "BaseMask2", "BaseMask3", "BaseMask4",
        };

        const char* SDChannelSelect::mscPicturePaneNames[PAGE_COUNT] = {
            "Picture_00", "Picture_01", "Picture_02", "Picture_03", "Picture_04",
        };

        const char* SDChannelSelect::mscEdgePaneNames[PAGE_COUNT] = {
            "Edge0", "Edge1", "Edge2", "Edge3", "Edge4",
        };

        const char* SDChannelSelect::mscClockPaneNames[3] = {
            "N_Clock0", "N_Clock1", "N_Clock2",
        };

        const char* SDChannelSelect::mscMaskPaneName = "ChMask";

        static const f32 sThumbnailOffsets[2][2] = {
            {64.0f, 48.0f},
            {85.0f, 48.0f},
        };

        static const u32 sChannelLayoutOrder[12] = {
            11, 7, 3, 10, 6, 2, 9, 5, 1, 8, 4, 0,
        };

        SDChannelSelect::SDChannelSelect(EGG::Heap* heap)
            : FaderSceneBase(heap),
              mpButtonEventHandler(new SDChannelSelectButtonEventHandler(this)),
              mState(0),
              mThumbOffsetX(sThumbnailOffsets[SCGetAspectRatio()][0]),
              mThumbOffsetY(sThumbnailOffsets[SCGetAspectRatio()][1]),
              mCommandQueue(4, 0, 0, 0),
              mNoticeQueue(42, 0, 0, 0),
              mCurrentSDState(0),
              mPreviousSDState(0),
              mWorkerState(0),
              mWorkerCommand(1),
              mpWorkerHeap(NULL),
              mpThumbnailWorkHeap(NULL),
              mpSDWorker(NULL),
              mpSDTitleIds(NULL),
              mpSDTitleInfo(NULL),
              mpNandTitleInfo(NULL),
              mpCurrentLoadedChannel(NULL),
              mpChannelTitleIds(NULL),
              mLastOperation(14),
              mOperationResult(0),
              mbShowNoCardMessage(false),
              mbOperationActive(false),
              mbSDCardBroken(false),
              mOperationState(0),
              mDialogState(0),
              mpSaveDataFile(NULL),
              mAnimationState(0),
              mAnimationTarget(0),
              mbHazardTitleFound(false),
              mbChannelLimitReached(false),
              mbInitialLoadComplete(false),
              mbNeedsRefresh(false) {
            mCurrentPage = System::getSaveData()->getLastSDPrevPage();
            mPageCount = 20;
            mCurrentChannelIndex = 0;
            mbLeftArrowVisible = mCurrentPage != 0;
            mbRightArrowVisible = mCurrentPage != mPageCount - 1;
            setSceneParentFlags(SCN_PARENTFLAG_DRAW | SCN_PARENTFLAG_CALC);
            math::VEC3 position(0.0f, 0.0f, 0.0f);
            mPosition = position;
            math::VEC2 scale(1.0f, 1.0f);
            mScale = scale;

            nw4r::ut::Rect projection4x3;
            System::getProjectionRect4x3(&projection4x3);
            nw4r::ut::Rect projection16x9;
            System::getProjectionRect16x9(&projection16x9);
            f32 aspectScale = projection16x9.GetWidth() / projection4x3.GetWidth();
            if (SCGetAspectRatio() != SC_ASPECT_RATIO_16x9) {
                aspectScale = 1.0f;
            }
            mAspectRatioScale = aspectScale;

            memset(&mPointerPosition, 0, 0x30);
            mpThumbnailHeap = EGG::ExpHeap::create(
                0x13610, heap, MEM_HEAP_OPT_DEBUG_FILL | MEM_HEAP_OPT_THREAD_SAFE);
            mpLayoutHeap = EGG::UnitHeap::create(
                EGG::UnitHeap::calcHeapSize(0x212B8, 0x2D, 32), 0x212B8,
                System::getMem2App(), 32, 2);
            nw4r::ut::List_Init(&mChannelObjects, 0);
            createChannelList(mCurrentPage, true);
            TVRCManager::getHandle()->setEnable(TRUE);

            mpChannelTitleIds = (u32*)new (System::getMem2App(), 32) u8[mPageCount * 0x30];
            memset(mpChannelTitleIds, 0, mPageCount * 0x30);
            mpSDTitleInfo = new (System::getMem2App(), 32)
                SDChannelSelectTitleInfo[0x4B00 / sizeof(SDChannelSelectTitleInfo)];
            memset(mpSDTitleInfo, 0, 0x4B00);
            mpSDTitleIds = new (System::getMem2App(), 32) ESTitleId32[0x2580 / sizeof(ESTitleId32)];
            memset(mpSDTitleIds, 0, 0x2580);
            mpNandTitleInfo = new (System::getMem2App(), 32)
                NandSDWorker::TitleUsage[0x600 / sizeof(NandSDWorker::TitleUsage)];
            memset(mpNandTitleInfo, 0, 0x600);
            mFirstTitleCount = 0;
            mSecondTitleCount = 0;
            mSourcePage = -1;
            mSourceIndex = -1;
        }

        SDChannelSelect::~SDChannelSelect() {
        }

        BOOL SDChannelSelect::isResetProcessDone() {
            switch (mLastOperation) {
            case 5:
            case 6:
            case 7:
            case 8:
                return FALSE;
            default:
                return TRUE;
            }
        }

        void SDChannelSelect::prepare() {
            System::getBS2Manager()->abort();
            mpLayoutFile = System::getNandManager()->readLayoutAsync(getSceneHeap(), "sdChanSel.ash");
            mpCorruptIconFile = System::getNandManager()->readAsync(
                getSceneHeap(), "corrupt_icon.ash", 0, 0, 0);

            SDChannelObj* channel = NULL;
            while (channel = static_cast<SDChannelObj*>(nw4r::ut::List_GetNext(&mChannelObjects, channel)),
                   channel != NULL) {
                iplSDChannelObj_813E3104(channel);
            }
        }

        void SDChannelSelect::create() {
            mpSDWorker = new (System::getMem2App(), 4) NandSDWorker();
            mpWorkerHeap = (EGG::Heap*)System::getMem2App()->alloc(0x3EA60, 0x40);
            u32 thumbnailHeapSize = MEMCalcHeapSizeForUnitHeap(0x19620, 0x60, 0x20);
            mpThumbnailWorkHeap = (EGG::Heap*)System::getMem2App()->alloc(
                thumbnailHeapSize + 0x40000, 0x40);
            mpSDWorker->create(mpWorkerHeap, NULL, mpThumbnailWorkHeap, 0x12);

            if (System::getSaveData()->didntGotoSDMenu() == FALSE) {
                mpSDWorker->mount_sd_async();
                mWorkerState = 1;
            }

            mpDialogHeap = EGG::ExpHeap::create(0x21100, getSceneHeap(), 6);
            mpChannelHeap = EGG::ExpHeap::create(0x2C100, getSceneHeap(), 6);
            mpRsoHeap = EGG::ExpHeap::create(TVRCManager::getHandle(), 0x200000, 0);
            mpRsoThread = new (System::getMem2App(), 32) channel::RsoThread(mpRsoHeap);

            createBaseLayout();
            if (mCurrentPage < mPageCount - 1) {
                createChannelList(mCurrentPage + 1, false);
            }
            if (mCurrentPage > 0) {
                createChannelList(mCurrentPage - 1, false);
            }
            updateNoCardLayouts();
            createChannelThumbnails();

            u32 startTick = OSGetTick();
            while (System::getBS2Manager()->getIPLState() != 8) {
                System::getBS2Manager()->update();
                OSReport(" ... wait for bs2 abord\n");
                VIWaitForRetrace();
            }
            u32 elapsedTicks = OSGetTick() - startTick;
            OSReport("*** BS2 abort costs: %dms\n", OSTicksToMilliseconds(elapsedTicks));

            System::getFader()->fadeIn();
            mState = 2;
            utility::CSFlags::UpdateFlagsFile();
        }

        void SDChannelSelect::enqueueStartNotice() {
            SDChannelSelectCommand command = {1, 0, {{0, 0, 0}}};
            mCommandQueue.push(command);
        }

        bool SDChannelSelect::enqueueFinishNotice() {
            SDChannelSelectCommand command = {2, 0, {{0, 0, 0}}};
            mCommandQueue.push(command);
            return true;
        }

        bool SDChannelSelect::enqueueNotice(u32 highTitleId, u32 lowTitleId, u32 result) {
            if (mLastOperation != 6) {
                return false;
            }

            if (mNoticeQueue.count != mNoticeQueue.capacity) {
                SDChannelSelectCommand notice = {
                    4, ((u64)highTitleId << 32) | lowTitleId, {{result, 0, 0}}};
                mNoticeQueue.notices[mNoticeQueue.writeIndex].copyFrom(notice);
                ++mNoticeQueue.writeIndex;
                if (mNoticeQueue.writeIndex >= mNoticeQueue.capacity) {
                    mNoticeQueue.writeIndex = 0;
                }
                ++mNoticeQueue.count;
            }
            return true;
        }

        bool SDChannelSelect::enqueueLoadNotice() {
            SDChannelSelectCommand command = {8, 0, {{0, 0, 0}}};
            return mLastOperation == 6 && mCommandQueue.push(command);
        }

        bool SDChannelSelect::enqueuePageNotice() {
            SDChannelSelectCommand command = {9, 0, {{0, 0, 0}}};
            return mLastOperation == 6 && mCommandQueue.push(command);
        }

        bool SDChannelSelect::enqueueResultNotice(u32 result) {
            SDChannelSelectCommand command = {5, result, {{0, 0, 0}}};
            return mLastOperation == 6 && mCommandQueue.push(command);
        }

        bool SDChannelSelect::enqueueChannelNotice(u32 controller, u32 page, u32 index, u32 value) {
            SDChannelSelectCommand command = {
                10, ((u64)value << 32) | index, {{page, (u32)&mSecondTitleCount, 0}}};
            return mLastOperation == 6 && mCommandQueue.push(command);
        }

        bool SDChannelSelect::enqueueMoveNotice(u32 controller, u32 page, u32 index) {
            SDChannelSelectCommand command = {6, ((u64)page << 32) | index, {{0, 0, 0}}};
            return mLastOperation == 6 && mCommandQueue.push(command);
        }

        bool SDChannelSelect::enqueueStateNotice(u32 controller, u32 page, u32 index, u32 state) {
            SDChannelSelectCommand command = {7, ((u64)page << 32) | index, {{state, 0, 0}}};
            return mLastOperation == 6 && mCommandQueue.push(command);
        }

        bool SDChannelSelect::enqueueErrorNotice(u32 page, u32 index) {
            SDChannelSelectCommand command = {11, 0, {{0, page, index}}};
            return mLastOperation == 6 && mCommandQueue.push(command);
        }

        bool SDChannelSelect::enqueueCommandNotice(u32 page, u32 index, u32 commandType) {
            SDChannelSelectCommand command = {12, 0, {{page, index, commandType}}};
            return mLastOperation == 6 && mCommandQueue.push(command);
        }

        bool SDChannelSelect::enqueueDeleteNotice(u32 controller, u32 page, u32 index) {
            SDChannelSelectCommand command = {13, index, {{page, 0, 0}}};
            return mLastOperation == 6 && mCommandQueue.push(command);
        }

        void SDChannelSelect::clearCommandQueue() {
            while (mCommandQueue.count > 0) {
                mCommandQueue.pop();
            }
        }

        void SDChannelSelect::clearNoticeQueue() {
            while (mNoticeQueue.count > 0) {
                mNoticeQueue.pop();
            }
        }

        void SDChannelSelect::handleWorkerStartup() {
            if (!mpSDWorker->is_working()) {
                if (mpSDWorker->get_async_result() == NandSDWorker::RESULT_OK) {
                    if (mDialogState == 0) {
                        setDialogMessage(8, 0xaa);
                    }
                    enqueueFinishNotice();
                    mWorkerCommand = 1;
                }
                mpSDWorker->startup_async();
                mWorkerState = 2;
            } else if (mPreviousSDState != mCurrentSDState && mCurrentSDState == 7) {
                System::getErrorHandler()->set(ErrorHandler::DEFAULT, 1);
            }
        }

        void SDChannelSelect::handleNandTitleCount() {
            if (!mpSDWorker->is_working()) {
                int result = mpSDWorker->get_async_result();
                if (result == NandSDWorker::RESULT_NAND_CORRUPT) {
                    System::getErrorHandler()->set(ErrorHandler::DEFAULT, 1);
                    return;
                }

                mNandTitleCount = mpSDWorker->get_nand_app_num();
                if (mNandTitleCount > 0x60) {
                    mNandTitleCount = 0x60;
                }
                if (mNandTitleCount != 0) {
                    mpSDWorker->list_nand_apps_usage_async(
                        mpNandTitleInfo, reinterpret_cast<void*>(mNandTitleCount));
                    mWorkerState = 3;
                } else {
                    mWorkerState = 4;
                }
            }
        }

        void SDChannelSelect::handleNandTitleUsage() {
            if (!mpSDWorker->is_working()) {
                if (mpSDWorker->get_async_result() == NandSDWorker::RESULT_OK) {
                    qsort(mpNandTitleInfo, mNandTitleCount, sizeof(NandSDWorker::TitleUsage),
                          compareTitleUsage);
                    for (u32 index = 0; index < mNandTitleCount; ++index) {
                        mpNandTitleInfo[index].size -= 0x4000;
                        --mpNandTitleInfo[index].inode;
                    }
                    mWorkerState = 4;
                } else {
                    System::getErrorHandler()->set(ErrorHandler::DEFAULT, 2);
                }
            }
        }

        void SDChannelSelect::handleNandTitleUsageComplete() {
            if (!mpSDWorker->is_working()) {
                mLastOperation = 14;
                mWorkerCommand = 1;
            }
        }

        void SDChannelSelect::handleSDTitleList() {
            if (mpSDWorker->is_working()) {
                return;
            }

            mLastOperation = 14;
            if (mSDTitleCount == 0) {
                if (mDialogState == 0) {
                    setDialogMessage(1, 0);
                    mWorkerCommand = 15;
                }
                return;
            }

            if (mpSDWorker->get_async_result() == NandSDWorker::RESULT_OK) {
                for (u32 index = 0; index < mSDTitleCount; ++index) {
                    mpSDTitleInfo[index].titleId = mpSDTitleIds[index];
                    if (mpSDTitleIds[index] == 0x48415A41) {
                        mbHazardTitleFound = true;
                    }
                }
                qsort(mpSDTitleInfo, mSDTitleCount, sizeof(SDChannelSelectTitleInfo),
                      compareTitleInfo);
                enqueuePageNotice();
                mWorkerCommand = 1;
            } else if (mDialogState == 0) {
                setDialogMessage(2, 0xc3);
                mWorkerCommand = 15;
            }
        }

        bool SDChannelSelect::setDialogMessage(u32 state, u32 message) {
            if (mDialogState == 0) {
                mDialogState = state;
                mAnimationTarget = message;
                return true;
            }
            return false;
        }

        int SDChannelSelect::compareTitleUsage(const void* lhs, const void* rhs) {
            const NandSDWorker::TitleUsage* left =
                static_cast<const NandSDWorker::TitleUsage*>(lhs);
            const NandSDWorker::TitleUsage* right =
                static_cast<const NandSDWorker::TitleUsage*>(rhs);
            if ((s32)left->size < (s32)right->size) {
                return -1;
            }
            return left->size != right->size;
        }

        int SDChannelSelect::compareTitleInfo(const void* lhs, const void* rhs) {
            const SDChannelSelectTitleInfo* left =
                static_cast<const SDChannelSelectTitleInfo*>(lhs);
            const SDChannelSelectTitleInfo* right =
                static_cast<const SDChannelSelectTitleInfo*>(rhs);
            if (left->titleId < right->titleId) {
                return -1;
            }
            return left->titleId != right->titleId;
        }

        void SDChannelSelect::processWorkerCommands() {
            if (mpSDWorker->is_working() || mWorkerState != 4) {
                return;
            }

            if (mCommandQueue.count == 0) {
                if (mNoticeQueue.count > 0) {
                    mNoticeQueue.pop();
                }
                return;
            }

            SDChannelSelectCommand command = {0, 0, {{0, 0, 0}}};
            command.copyFrom(mCommandQueue.commands[mCommandQueue.readIndex]);
            mLastOperation = command.type;

            switch (command.type) {
            case 1:
                mpSDWorker->mount_sd_async();
                mWorkerCommand = 0;
                mbInitialLoadComplete = false;
                break;
            case 2:
                mSDTitleCount = mpSDWorker->get_sd_app_num();
                mpSDWorker->list_sd_app_async(mpSDTitleIds);
                mWorkerCommand = 2;
                break;
            case 5:
                mpSDWorker->copy_sd_app_to_nand_async((ESTitleId32)command.titleId, true);
                mWorkerCommand = 7;
                break;
            case 6:
                mpSDWorker->copy_nand_app_to_sd_async((ESTitleId)command.titleId);
                mWorkerCommand = 9;
                break;
            case 7: {
                mpSDWorker->delete_nand_app_async((ESTitleId)command.titleId,
                                                  command.arguments.values[2] != 0);
                mWorkerCommand = 10;
                u32 index = 0;
                while (index < mNandTitleCount &&
                       mpNandTitleInfo[index].curTitleId != command.titleId) {
                    ++index;
                }
                if (index < mNandTitleCount) {
                    for (; index + 1 < mNandTitleCount; ++index) {
                        mpNandTitleInfo[index] = mpNandTitleInfo[index + 1];
                    }
                    --mNandTitleCount;
                }
                break;
            }
            case 8:
                mpSDWorker->update_sd_app_location_async(mpChannelTitleIds);
                mWorkerCommand = 4;
                break;
            case 9:
                mpSDWorker->read_sd_app_location_async(mpChannelTitleIds);
                mWorkerCommand = 5;
                break;
            case 10:
                mpSDWorker->check_for_sd_app_to_nand_async(
                    (ESTitleId)command.titleId,
                    command.arguments.appBlocks[0], command.arguments.appBlocks[1]);
                mWorkerCommand = 8;
                break;
            case 11:
                mpSDWorker->check_backup_fits_async(
                    command.arguments.titleLists[0], command.arguments.titleLists[1]);
                mWorkerCommand = 11;
                break;
            case 12:
                mpSDWorker->iplNandSD_81348EA8(
                    command.arguments.pointers[0], command.arguments.pointers[1],
                    command.arguments.pointers[2]);
                mWorkerCommand = 12;
                break;
            case 13:
                mpSDWorker->delete_sd_app_async((ESTitleId32)command.titleId);
                mWorkerCommand = 13;
                break;
            default:
                break;
            }

            mCommandQueue.pop();
        }

        void SDChannelSelect::handleSDMountComplete() {
            if (!mpSDWorker->is_working()) {
                mLastOperation = 14;
                if (mpSDWorker->get_async_result() == NandSDWorker::RESULT_OUT_OF_SPACE) {
                    mbSDCardBroken = true;
                }
                mbShowNoCardMessage = true;
                mWorkerCommand = 1;
            }
        }

        void SDChannelSelect::handleCopyComplete() {
            if (!mpSDWorker->is_working()) {
                mLastOperation = 14;
                if (mpSDWorker->get_async_result() == NandSDWorker::RESULT_NAND_CORRUPT) {
                    System::getErrorHandler()->set(ErrorHandler::DEFAULT, 1);
                } else {
                    mWorkerCommand = 1;
                }
            }
        }

        void SDChannelSelect::handleDeleteComplete() {
            if (!mpSDWorker->is_working()) {
                mLastOperation = 14;
                mWorkerCommand = 1;
            }
        }

        void SDChannelSelect::handleMoveComplete() {
            if (!mpSDWorker->is_working()) {
                mLastOperation = 14;
                if (mpSDWorker->get_async_result() == NandSDWorker::RESULT_NAND_CORRUPT) {
                    System::getErrorHandler()->set(ErrorHandler::DEFAULT, 1);
                } else {
                    System::getChannelManager()->reserveRefresh();
                    mWorkerCommand = 1;
                }
            }
        }

        void SDChannelSelect::handleStorageCheckComplete() {
            if (!mpSDWorker->is_working()) {
                mLastOperation = 14;
                mWorkerCommand = 1;
            }
        }

        void SDChannelSelect::handleCardCommand() {
            if (mDialogState != 0) {
                return;
            }

            if (mpSDWorker->get_sd_state() == NandSDWorker::SD_STATE_EJECTED) {
                setDialogMessage(2, 0xa9);
                mWorkerCommand = 6;
            } else if (mpSDWorker->get_sd_state() == NandSDWorker::SD_STATE_INSERTED) {
                mWorkerCommand = 1;
            }
        }

        void SDChannelSelect::handleSDCardReady() {
            if (mpSDWorker->get_sd_state() == NandSDWorker::SD_STATE_INSERTED &&
                mDialogState == 0) {
                setDialogMessage(1, 0);
                mWorkerCommand = 1;
            }
        }

        void SDChannelSelect::handleSDLocationUpdateComplete() {
            if (!mpSDWorker->is_working()) {
                mLastOperation = 14;
                mWorkerCommand = 1;
            }
        }

        void SDChannelSelect::handleSDLocationReadComplete() {
            if (!mpSDWorker->is_working()) {
                mLastOperation = 14;
                mWorkerCommand = 1;
            }
        }

        void SDChannelSelect::handleBackupFitComplete() {
            if (!mpSDWorker->is_working()) {
                mLastOperation = 14;
                mWorkerCommand = 1;
            }
        }

        void SDChannelSelect::handleNandSDCleanupComplete() {
            if (!mpSDWorker->is_working()) {
                mLastOperation = 14;
                mWorkerCommand = 1;
            }
        }

        void SDChannelSelect::handleSDDeleteComplete() {
            if (!mpSDWorker->is_working()) {
                mLastOperation = 14;
                mWorkerCommand = 1;
            }
        }

        void SDChannelSelect::processWorkerState() {
            mPreviousSDState = mCurrentSDState;
            mCurrentSDState = mpSDWorker->get_sd_state();

            if (mWorkerState == 2) {
                handleNandTitleCount();
            } else if (mWorkerState == 1) {
                handleWorkerStartup();
            } else if (mWorkerState == 3) {
                handleNandTitleUsage();
            }

            switch (mWorkerCommand) {
            case 0:
                handleNandTitleUsageComplete();
                break;
            case 1:
                processWorkerCommands();
                break;
            case 2:
                handleSDTitleList();
                break;
            case 3:
                handleCopyComplete();
                break;
            case 4:
                handleSDMountComplete();
                break;
            case 5:
                handleDeleteComplete();
                break;
            case 6:
                handleSDCardReady();
                break;
            case 7:
                handleCopyComplete();
                break;
            case 8:
                handleSDLocationUpdateComplete();
                break;
            case 9:
                handleSDLocationReadComplete();
                break;
            case 10:
                handleMoveComplete();
                break;
            case 11:
                handleBackupFitComplete();
                break;
            case 12:
                handleNandSDCleanupComplete();
                break;
            case 13:
                handleSDDeleteComplete();
                break;
            case 15:
                handleCardCommand();
                break;
            }

            if (mLastOperation != 6 && mState > 14 && mState < 24) {
                mbDialogActive = true;
            }

            updateDialogAnimation();
        }

        void SDChannelSelect::updateDialogAnimation() {
            u32 animationIndex = 0xffffffff;
            if (mpNoCardLayout->isPlaying()) {
                animationIndex = 4;
                if (!mpNoCardLayout->isPlaying(animationIndex)) {
                    return;
                }
            }

            switch (mOperationState) {
            case 3:
                mOperationState = 4;
                mOperationStartTime = OSGetTime();
                break;
            case 6:
                mOperationState = 7;
                break;
            case 9:
                mOperationState = 10;
                mOperationStartTime = OSGetTime();
                break;
            case 12:
                mOperationState = 13;
                break;
            }

            if (mDialogState == 0) {
                if (mOperationState == 10) {
                    mOperationState = 14;
                } else if (mOperationState < 10 && mOperationState == 7) {
                    mOperationState = 8;
                }
            } else if (mDialogState == 2) {
                switch (mOperationState) {
                case 0:
                case 1:
                case 7:
                case 13:
                    mOperationState = 2;
                    mAnimationState = mAnimationTarget;
                    break;
                case 2:
                    if (mAnimationState != mAnimationTarget) {
                        mAnimationState = mAnimationTarget;
                    }
                    mDialogState = 0;
                    break;
                case 4:
                    if (mAnimationState == mAnimationTarget) {
                        mDialogState = 0;
                    } else {
                        mOperationState = 5;
                    }
                    break;
                case 10:
                case 14:
                case 15:
                    mOperationState = 11;
                    break;
                }
            } else if (mDialogState < 2) {
                if (mDialogState > 0) {
                    switch (mOperationState) {
                    case 0:
                    case 1:
                    case 2:
                    case 7:
                    case 8:
                    case 13:
                        mOperationState = 1;
                        mDialogState = 0;
                        mAnimationState = mAnimationTarget;
                        break;
                    case 4:
                        mOperationState = 5;
                        break;
                    case 10:
                    case 14:
                    case 15:
                        mOperationState = 11;
                        break;
                    }
                }
            } else if (mDialogState == 8) {
                switch (mOperationState) {
                case 0:
                case 1:
                case 7:
                case 13:
                    mOperationState = 8;
                    mAnimationState = mAnimationTarget;
                    break;
                case 4:
                    mOperationState = 5;
                    break;
                case 8:
                    if (mAnimationState != mAnimationTarget) {
                        mAnimationState = mAnimationTarget;
                    }
                    mDialogState = 0;
                    break;
                case 10:
                case 14:
                case 15:
                    if (mAnimationState == mAnimationTarget) {
                        mDialogState = 0;
                    } else {
                        mOperationState = 11;
                    }
                    break;
                }
            }

            layout::Animator* animator = NULL;
            switch (mOperationState) {
            case 2:
                static_cast<nw4r::lyt::TextBox*>(mpNoCardLayout->FindPaneByName("T_TimerMes"))
                    ->SetString(System::getMessage(mAnimationState), 0);
                animator = mpNoCardLayout->getAnim(0);
                break;
            case 5:
                animator = mpNoCardLayout->getAnim(1);
                break;
            case 8:
                static_cast<nw4r::lyt::TextBox*>(mpNoCardLayout->FindPaneByName("T_TimerMes_01"))
                    ->SetString(System::getMessage(mAnimationState), 0);
                animator = mpNoCardLayout->getAnim(2);
                break;
            case 11:
                mpNoCardLayout->getAnim(4)->stop();
                animator = mpNoCardLayout->getAnim(3);
                break;
            case 14:
                animator = mpNoCardLayout->getAnim(4);
                break;
            }

            if (animator != NULL) {
                animator->initAnmFrame();
                animator->initFrame();
                animator->restart();
                ++mOperationState;
            }
        }

        void SDChannelSelect::calcChannelObjects() {
            SDChannelObj* channel = NULL;
            while (channel = static_cast<SDChannelObj*>(nw4r::ut::List_GetNext(&mChannelObjects, channel)),
                   channel != NULL) {
                iplSDChannelObj_813E322C(channel);
            }
        }

        void SDChannelSelect::drawChannelObjects() {
            SDChannelObj* channel = NULL;
            while (channel = static_cast<SDChannelObj*>(nw4r::ut::List_GetNext(&mChannelObjects, channel)),
                   channel != NULL) {
                iplSDChannelObj_813E330C(channel);
            }
        }

        void SDChannelSelect::updateArrowVisibility() {
            int leftPageOffset = (mState == 10 || mState == 22) ? 1 : 0;
            int rightPageOffset = (mState == 11 || mState == 23) ? 1 : 0;
            layout::Object* layout = mpLayout;

            if (mCurrentPage <= leftPageOffset) {
                layout->hide(mscEdgePaneNames[0]);
                layout->hide(mscEdgePaneNames[1]);
            } else {
                layout->show(mscEdgePaneNames[0]);
                layout->show(mscEdgePaneNames[1]);
            }

            if (mCurrentPage + rightPageOffset + 1 >= mPageCount) {
                layout->hide(mscEdgePaneNames[3]);
                layout->hide(mscEdgePaneNames[4]);
            } else {
                layout->show(mscEdgePaneNames[3]);
                layout->show(mscEdgePaneNames[4]);
            }
        }

        FaderSceneCommand SDChannelSelect::calcFadein() {
            return mpLayout->isPlaying(0) ? FADER_SCN_CONTINUE : FADER_SCN_NEXT;
        }

        void SDChannelSelect::calcCommon() {
            if (mState == 2 && !mpLayout->isPlaying(0)) {
                SDButton* button = static_cast<SDButton*>(System::getSceneManager()->getScene(0x24));
                if (button != NULL) {
                    button->setEventHandler(mpButtonEventHandler, NULL);
                    mState = 3;
                    if (mCurrentPage < 1) {
                        button->initArrowAppearance(1, false);
                    } else {
                        button->initArrowAppearance(1, true);
                    }

                    if (mPageCount < 2 || mPageCount - 1 <= mCurrentPage) {
                        button->initArrowAppearance(0, false);
                    } else {
                        button->initArrowAppearance(0, true);
                    }
                }
            }

            if (mState == 3 && System::getFader()->getStatus() == EGG::Fader::PREPARE_OUT) {
                if (System::getSaveData()->didntGotoSDMenu()) {
                    mOperationResult = 0;
                    mState = 24;
                } else {
                    mState = 1;
                }
            }

            mpLayout->calc();
            mpPaneManager->calc();
            calcChannelObjects();
            mpPageLayouts[0]->calc();
            mpPageLayouts[1]->calc();
            mpPageLayouts[2]->calc();
            mpHelpButtonLayout->calc();
            mpErrorLayout->calc();
            mpStateLayout->calc();
            mpNoCardLayout->calc();
            processWorkerState();
        }

        void SDChannelSelect::initCalcFadeout() {
            if (mState == 4) {
                clearCommandQueue();
                clearNoticeQueue();
                System::getFader()->fadeOut();
                TVRCManager::getHandle()->setEnable(FALSE);
                System::getChannelManager()->refreshAsync();
                reserveAllSceneDestruction(4, NULL);
            }
        }

        FaderSceneCommand SDChannelSelect::calcFadeout() {
            FaderSceneCommand command = FADER_SCN_CONTINUE;
            if (mState == 4) {
                command = (FaderSceneCommand)!System::getFader()->getStatus();
            }
            return command;
        }

        void SDChannelSelect::draw() {
            bool onDrawLayer = System::onDrawLayer(DRAW_LAYER_DEFAULT);
            if (mState == 13) {
                if (onDrawLayer) {
                    utility::Graphics::setOrtho();
                    GXColor color = {0, 0, 0, 255};
                    nw4r::ut::Rect projection;
                    System::getProjectionRect(&projection);
                    utility::Graphics::drawPolygon(projection, color);
                }
                return;
            }

            if (!onDrawLayer) {
                return;
            }

            if (mState == 7 || mState == 12 || mState == 14) {
                utility::Graphics::setOrthoTransAndScale(mPosition, mScale);
            }
            utility::Graphics::setOrtho();

            for (int edge = 0; edge < PAGE_COUNT; ++edge) {
                nw4r::lyt::Pane* pane = mpLayout->FindPaneByName(mscEdgePaneNames[edge]);
                pane->SetVisible(true);
                mpLayout->draw(pane);
                pane->SetVisible(false);
            }

            drawChannelObjects();
            updateArrowVisibility();

            GXSetScissor(0, 0, System::getRenderModeObj()->fbWidth,
                         System::getRenderModeObj()->efbHeight);

            nw4r::lyt::Pane* mask = mpLayout->FindPaneByName(mscMaskPaneName);
            mask->SetVisible(false);
            mpLayout->draw();

            nw4r::lyt::TextBox* pageText = static_cast<nw4r::lyt::TextBox*>(
                mpDialogLayout->FindPaneByName("TextBox_00"));
            for (int page = 0; page < 3; ++page) {
                wchar_t pageNumber[20];
                swprintf(pageNumber, 19, L"%d", mCurrentPage + page);
                pageText->SetString(pageNumber, 0);
                mpDialogLayout->draw();
            }

            drawChannelObjects();
            mask->SetVisible(true);
            mpLayout->draw(mask);
            mpPageLayouts[1]->draw();
            mpNoCardLayout->draw();
        }

        void SDChannelSelect::destroyChannelObject(SDChannelObj* channel) {
            delete channel;
        }

        bool SDChannelSelect::hasChannelObject(int page, int index) const {
            if (page == mCurrentPage) {
                return true;
            }

            if (page == mCurrentPage - 1) {
                if (mState == 10 || mState == 22) {
                    return true;
                }
                for (int current = 3; current < MAX_CHANNEL_INDEX; current += 4) {
                    if (current == index) {
                        return true;
                    }
                }
            } else if (page == mCurrentPage - 2) {
                if (mState == 10 || mState == 22) {
                    for (int current = 3; current < MAX_CHANNEL_INDEX; current += 4) {
                        if (current == index) {
                            return true;
                        }
                    }
                }
            } else if (page == mCurrentPage + 1) {
                if (mState == 11 || mState == 23) {
                    return true;
                }
                for (int current = 0; current < MAX_CHANNEL_INDEX; current += 4) {
                    if (current == index) {
                        return true;
                    }
                }
            } else if (page == mCurrentPage + 2 && (mState == 11 || mState == 23)) {
                for (int current = 0; current < MAX_CHANNEL_INDEX; current += 4) {
                    if (current == index) {
                        return true;
                    }
                }
            }

            return false;
        }

        void SDChannelSelect::destroy() {
            System::getBS2Manager()->restart();
            System::getSaveData()->setLastSDPrevPage(mCurrentPage);

            SDChannelObj* channel = NULL;
            while (channel = static_cast<SDChannelObj*>(nw4r::ut::List_GetNext(&mChannelObjects, channel)),
                   channel != NULL) {
                nw4r::ut::List_Remove(&mChannelObjects, channel);
                destroyChannelObject(channel);
            }

            if (mpRsoThread != NULL) {
                delete mpRsoThread;
                mpRsoThread = NULL;
            }

            if (mpThumbnailHeap != NULL) {
                mpThumbnailHeap->destroy();
            }
            if (mpLayoutHeap != NULL) {
                mpLayoutHeap->destroy();
            }
            if (mpDialogHeap != NULL) {
                mpDialogHeap->destroy();
            }
            if (mpChannelHeap != NULL) {
                mpChannelHeap->destroy();
            }

            if (mpSaveDataFile != NULL) {
                while (!System::getSaveData()->isFinished(mpSaveDataFile)) {
                    OSYieldThread();
                }
                delete mpSaveDataFile;
                mpSaveDataFile = NULL;
            }

            if (mpSDWorker != NULL) {
                if (!mpSDWorker->is_terminated()) {
                    mpSDWorker->terminate_async();
                    while (mpSDWorker->is_working()) {
                        OSYieldThread();
                    }
                    while (!mpSDWorker->is_terminated()) {
                        OSYieldThread();
                    }
                }

                if (mpWorkerHeap != NULL) {
                    mpWorkerHeap->destroy();
                }
                if (mpThumbnailWorkHeap != NULL) {
                    mpThumbnailWorkHeap->destroy();
                }

                delete[] mpSDTitleIds;
                delete[] mpSDTitleInfo;
                delete[] mpChannelTitleIds;
                delete[] mpNandTitleInfo;
                delete mpSDWorker;
                mpSDWorker = NULL;
            }
        }

        void SDChannelSelect::createBaseLayout() {
            GXTexObj widescreenTexture;
            GXTexObj standardTexture;

            mpLayout = new layout::Object(getSceneHeap(), mpLayoutFile, "arc",
                                          "mn_SdcardMenu_a.brlyt");

            if (SCGetAspectRatio() == SC_ASPECT_RATIO_16x9) {
                mpLayout->FindPaneByName("ChangeTex16x9")
                    ->GetMaterial()
                    ->GetTexture(&widescreenTexture, GX_TEXMAP0);
                mpLayout->FindPaneByName("Picture_16")
                    ->GetMaterial()
                    ->GetTexture(&standardTexture, GX_TEXMAP0);

                for (int page = 0; page < PAGE_COUNT; ++page) {
                    mpLayout->FindPaneByName(mscPicturePaneNames[page])
                        ->GetMaterial()
                        ->SetTexture(GX_TEXMAP0, widescreenTexture);
                    mpLayout->FindPaneByName(mscEdgePaneNames[page])
                        ->GetMaterial()
                        ->SetTexture(GX_TEXMAP0, standardTexture);
                }
            }

            mpLayout->bind("mn_SdcardMenu_a.brlan");
            mpLayout->finishBinding();

            mpDialogLayout = new layout::Object(getSceneHeap(), mpLayoutFile, "arc",
                                                "mn_SdcardMenu_Page.brlyt");
            mpNoCardLayout = new layout::Object(getSceneHeap(), mpLayoutFile, "arc",
                                                "mn_Nocard.brlyt");
            mpNoCardLayout->bindToGroup("mn_Nocard_IN.brlan", "Group_00", false, true);
            mpNoCardLayout->bindToGroup("mn_Nocard_Out.brlan", "Group_00", false, true);
            mpNoCardLayout->bindToGroup("mn_Nocard_IN_02.brlan", "Group_01", false, true);
            mpNoCardLayout->bindToGroup("mn_Nocard_Out_02.brlan", "Group_01", false, true);
            mpNoCardLayout->bindToGroup("mn_Nocard_Wait.brlan", "G_Wait", false, true);
            mpNoCardLayout->getAnim(0)->initAnmFrame();
            mpNoCardLayout->getAnim(2)->initAnmFrame();
            mpNoCardLayout->finishBinding();

            mpHelpButtonLayout = new layout::Object(getSceneHeap(), mpLayoutFile, "arc",
                                                    "help_Btn.brlyt");

            mpButtonEventHandler = new SDChannelSelectButtonEventHandler(this);
            mpPaneManager = new gui::PaneManager(mpButtonEventHandler, mpLayout->getDrawInfo(),
                                                NULL, NULL);
            mpPaneManager->createLayoutScene(*mpLayout->getNW4RLyt());
            mpPaneManager->setAllComponentTriggerTarget(false);

            for (int index = 0; index < MAX_CHANNEL_INDEX; ++index) {
                const char* paneName = mscChannelPaneNames[mCurrentPage % PAGE_COUNT][index];
                if (paneName[0] != '\0') {
                    mpPaneManager->getPaneComponentByPane(mpLayout->FindPaneByName(paneName))
                        ->setTriggerTarget(true);
                }
            }

            for (int index = 0; index < 4; ++index) {
                mpPageAnimations[index] = new math::HermiteIntp<math::VEC3>();
            }
        }

        void SDChannelSelect::startResetting() {
            snd::getSystem()->resetAllSound();
            clearCommandQueue();
            clearNoticeQueue();
        }

        void SDChannelSelectCommand::copyFrom(const SDChannelSelectCommand& other) {
            type = other.type;
            titleId = other.titleId;
            arguments.values[0] = other.arguments.values[0];
            arguments.values[1] = other.arguments.values[1];
            arguments.values[2] = other.arguments.values[2];
        }

        bool SDChannelSelectCommandQueue::push(const SDChannelSelectCommand& command) {
            if (count == capacity) {
                return false;
            }

            commands[writeIndex].copyFrom(command);
            ++writeIndex;
            if (writeIndex >= capacity) {
                writeIndex = 0;
            }
            ++count;
            return true;
        }

        bool SDChannelSelectCommandQueue::pop() {
            if (count == 0) {
                return false;
            }

            ++readIndex;
            if (readIndex >= capacity) {
                readIndex = 0;
            }
            --count;
            return true;
        }

        bool SDChannelSelectNoticeQueue::pop() {
            if (count == 0) {
                return false;
            }

            ++readIndex;
            if (readIndex >= capacity) {
                readIndex = 0;
            }
            --count;
            return true;
        }
    }
}
