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
            class SDChannelSelectEventHandler : public ::gui::EventHandler {
            public:
                explicit SDChannelSelectEventHandler(SDChannelSelect* scene)
                    : mpScene(scene) {
                }

                void onEvent(u32 compId, u32 event, void* data) override;

            private:
                SDChannelSelect* mpScene;
            };

            class SDChannelSelectButtonEventHandler : public SDButtonEventHandlerBase {
            public:
                explicit SDChannelSelectButtonEventHandler(SDChannelSelect* scene)
                    : mpScene(scene) {
                }

                void onEventDerived(u32 compId, u32 event,
                                    const controller::Interface* con) override;

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

        static DialogWindow::Page sFourPageDialogPages[4] = {
            {0x9d, 0xa3, 0xa5, FALSE, NULL, 0.0f, FALSE},
            {0x9e, 0xa3, 0xa5, TRUE, NULL, 0.0f, FALSE},
            {0x9f, 0xa3, 0xa5, TRUE, NULL, 74.0f, TRUE},
            {0xca, 0xa4, 0xa5, TRUE, NULL, 108.0f, FALSE},
        };

        static DialogWindow::Page sThreePageDialogPages[3] = {
            {0xc9, 0xa3, 0xa5, TRUE, NULL, 0.0f, FALSE},
            {0x9e, 0xa3, 0xa5, TRUE, NULL, 0.0f, FALSE},
            {0x9f, 0xa4, 0xa5, TRUE, NULL, 74.0f, TRUE},
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

        void SDChannelSelect::onButtonEvent(const char* paneName, u32 event,
                                            const controller::Interface* controller) {
            if (controller != NULL &&
                controller != System::getControllerManager()->getController(mControllerChannel)) {
                return;
            }

            switch (event) {
            case ::gui::EventHandler::ON_LEFT:
                if (strcmp(paneName, SDButton::smButtonName[SDButton::BTN_ARROW_LEFT]) == 0) {
                    if (mCurrentPage > 0) {
                        mPendingIndex = -1;
                    }
                } else if (strcmp(paneName, SDButton::smButtonName[SDButton::BTN_ARROW_RIGHT]) == 0) {
                    if (mCurrentPage < mPageCount - 1) {
                        mPendingPage = -1;
                    }
                }
                break;
            case ::gui::EventHandler::ON_POINT:
                if (strcmp(paneName, SDButton::smButtonName[SDButton::BTN_ARROW_LEFT]) == 0) {
                    if (mCurrentPage > 0 && mPendingIndex < 0) {
                        mPendingIndex = 0;
                    }
                } else if (strcmp(paneName, SDButton::smButtonName[SDButton::BTN_ARROW_RIGHT]) == 0) {
                    if (mCurrentPage < mPageCount - 1 && mPendingPage < 0) {
                        mPendingPage = 0;
                    }
                }
                break;
            }
        }

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
            mPageCount = 20;
            mCurrentPage = System::getSaveData()->getLastSDPrevPage();
            mCurrentChannelIndex = 0;
            if (mCurrentPage == 0) {
                mbLeftArrowVisible = false;
            } else {
                mbLeftArrowVisible = true;
            }
            if (mCurrentPage == mPageCount - 1) {
                mbRightArrowVisible = false;
            } else {
                mbRightArrowVisible = true;
            }
            setSceneParentFlags(SCN_PARENTFLAG_DRAW | SCN_PARENTFLAG_CALC);
            mPosition = math::VEC3(0.0f, 0.0f, 0.0f);
            mScale = math::VEC2(1.0f, 1.0f);

            nw4r::ut::Rect projection4x3;
            System::getProjectionRect4x3(&projection4x3);
            nw4r::ut::Rect projection16x9;
            System::getProjectionRect16x9(&projection16x9);
            f32 aspectScale = projection16x9.GetWidth() / projection4x3.GetWidth();
            aspectScale = SCGetAspectRatio() == SC_ASPECT_RATIO_16x9 ? aspectScale : 1.0f;
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

            mpChannelTitleIds = new (System::getMem2App(), 32)
                u32[mPageCount * MAX_CHANNEL_INDEX];
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
            mpThumbnailWorkHeap = (EGG::Heap*)System::getMem2App()->alloc(
                MEMCalcHeapSizeForUnitHeap(0x19620, 0x60, 0x20) + 0x40000, 0x40);
            mpSDWorker->create(mpWorkerHeap, NULL, mpThumbnailWorkHeap, 0x12);

            if (System::getSaveData()->didntGotoSDMenu() == FALSE) {
                mpSDWorker->mount_sd_async();
                mWorkerState = 1;
            }

            mpDialogHeap = EGG::ExpHeap::create(0x21100, getSceneHeap(), 6);
            mpChannelHeap = EGG::ExpHeap::create(0x2C100, getSceneHeap(), 6);
            mpRsoHeap = EGG::ExpHeap::create(System::getChannelArena(), 0x200000, 0);
            mpRsoThread = new (System::getMem2App(), 32) channel::RsoThread(mpRsoHeap);

            createBaseLayout();
            if (mCurrentPage < mPageCount - 1) {
                createChannelList(mCurrentPage + 1, false);
            }
            if (mCurrentPage > 0) {
                createChannelList(mCurrentPage - 1, false);
            }
            updateChannelObjects();
            createSceneLayouts();

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
            SDChannelSelectCommand command;
            command.type = 1;
            command.arguments.values[0] = 0;
            command.arguments.values[1] = 0;
            command.titleId = 0;
            command.arguments.values[2] = 0;
            mCommandQueue.push(command);
        }

        bool SDChannelSelect::enqueueFinishNotice() {
            SDChannelSelectCommand command;
            command.type = 2;
            command.arguments.values[0] = 0;
            command.arguments.values[1] = 0;
            command.titleId = 0;
            command.arguments.values[2] = 0;
            mCommandQueue.push(command);
            return true;
        }

        bool SDChannelSelect::enqueueNotice(u32 titleId, u32 argument0, u32 argument1) {
            if (mCurrentSDState != 6) {
                return false;
            }

            SDChannelSelectCommand notice;
            notice.type = 4;
            notice.arguments.values[0] = argument0;
            notice.arguments.values[1] = argument1;
            notice.titleId = titleId;
            notice.arguments.values[2] = 0;
            if (mNoticeQueue.capacity != mNoticeQueue.count) {
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
            if (mCurrentSDState != 6) {
                return false;
            }

            SDChannelSelectCommand command;
            command.type = 8;
            command.arguments.values[0] = 0;
            command.arguments.values[1] = 0;
            command.titleId = 0;
            command.arguments.values[2] = 0;
            mCommandQueue.push(command);
            return true;
        }

        bool SDChannelSelect::enqueuePageNotice() {
            if (mCurrentSDState != 6) {
                return false;
            }

            SDChannelSelectCommand command;
            command.type = 9;
            command.arguments.values[0] = 0;
            command.arguments.values[1] = 0;
            command.titleId = 0;
            command.arguments.values[2] = 0;
            mCommandQueue.push(command);
            return true;
        }

        bool SDChannelSelect::enqueueResultNotice(u32 result) {
            if (mCurrentSDState != 6) {
                return false;
            }

            SDChannelSelectCommand command;
            command.type = 5;
            command.arguments.values[0] = 0;
            command.arguments.values[1] = 0;
            command.titleId = result;
            command.arguments.values[2] = 0;
            mCommandQueue.push(command);
            return true;
        }

        bool SDChannelSelect::enqueueChannelNotice(u32 controller, u32 page, u32 index, u32 value) {
            if (mCurrentSDState != 6) {
                return false;
            }

            SDChannelSelectCommand command;
            command.type = 10;
            command.arguments.values[0] = value;
            command.arguments.values[1] = (u32)&mFirstTitleCount;
            command.titleId = ((u64)page << 32) | index;
            command.arguments.values[2] = 0;
            mCommandQueue.push(command);
            return true;
        }

        bool SDChannelSelect::enqueueMoveNotice(u32 controller, u32 page, u32 index) {
            if (mCurrentSDState != 6) {
                return false;
            }

            SDChannelSelectCommand command;
            command.type = 6;
            command.arguments.values[0] = 0;
            command.arguments.values[1] = 0;
            command.titleId = ((u64)page << 32) | index;
            command.arguments.values[2] = 0;
            mCommandQueue.push(command);
            return true;
        }

        bool SDChannelSelect::enqueueStateNotice(u32 controller, u32 page, u32 index, u32 state) {
            if (mCurrentSDState != 6) {
                return false;
            }

            SDChannelSelectCommand command;
            command.type = 7;
            command.arguments.values[0] = state;
            command.arguments.values[1] = 0;
            command.titleId = ((u64)page << 32) | index;
            command.arguments.values[2] = 0;
            mCommandQueue.push(command);
            return true;
        }

        bool SDChannelSelect::enqueueErrorNotice(u32 page, u32 index) {
            if (mCurrentSDState != 6) {
                return false;
            }

            SDChannelSelectCommand command;
            command.type = 11;
            command.arguments.values[0] = page;
            command.arguments.values[1] = index;
            command.titleId = 0;
            command.arguments.values[2] = 0;
            mCommandQueue.push(command);
            return true;
        }

        bool SDChannelSelect::enqueueCommandNotice(u32 page, u32 index, u32 commandType) {
            if (mCurrentSDState != 6) {
                return false;
            }

            SDChannelSelectCommand command;
            command.arguments.values[0] = page;
            command.type = 12;
            command.arguments.values[1] = index;
            command.arguments.values[2] = commandType;
            command.titleId = 0;
            mCommandQueue.push(command);
            return true;
        }

        bool SDChannelSelect::enqueueDeleteNotice(u32 controller, u32 page, u32 index) {
            if (mCurrentSDState != 6) {
                return false;
            }

            SDChannelSelectCommand command;
            command.type = 13;
            command.arguments.values[0] = 0;
            command.arguments.values[1] = 0;
            command.arguments.values[2] = 0;
            command.titleId = ((u64)page << 32) | index;
            mCommandQueue.push(command);
            return true;
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
                    if (mOperationState == 0) {
                        setDialogMessage(8, 0xaa);
                    }
                    enqueueFinishNotice();
                    mWorkerCommand = 1;
                }
                mpSDWorker->startup_async();
                mWorkerState = 2;
            } else if (mPreviousSDState != mCurrentSDState && mCurrentSDState == 7) {
                setDialogMessage(8, 0xaa);
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

        void SDChannelSelect::handleSDTitleListResult() {
            if (mpSDWorker->is_working()) {
                return;
            }

            mLastOperation = 14;
            if (mDialogState != 0) {
                return;
            }

            if (OSGetTime() - mOperationStartTime < OS_TIMER_CLOCK) {
                return;
            }
            setDialogMessage(1, 0);
            int result = mpSDWorker->get_async_result();
            if (result == NandSDWorker::RESULT_OK ||
                result == NandSDWorker::RESULT_SD_APP_LOC_NOT_FOUND) {
                for (int channelIndex = 0; channelIndex < mPageCount * 12;
                     ++channelIndex) {
                    if (mpChannelTitleIds[channelIndex] != 0) {
                        SDChannelSelectTitleInfo* info =
                            static_cast<SDChannelSelectTitleInfo*>(
                                bsearch(mpChannelTitleIds + channelIndex, mpSDTitleInfo,
                                        mSDTitleCount, sizeof(SDChannelSelectTitleInfo),
                                        compareTitleInfo));
                        if (info != NULL) {
                            info->used = true;
                        } else {
                            mpChannelTitleIds[channelIndex] = 0;
                        }
                    }
                }

                int channelIndex = 0;
                u32 titleIndex = 0;
                bool addedTitle = false;
                for (; channelIndex < mPageCount * 12; ++channelIndex) {
                    if (mpChannelTitleIds[channelIndex] == 0) {
                        if (titleIndex == mSDTitleCount) {
                            break;
                        }

                        for (; titleIndex < mSDTitleCount; ++titleIndex) {
                            SDChannelSelectTitleInfo* info = &mpSDTitleInfo[titleIndex];
                            if (info->used) {
                                continue;
                            }
                            if (info->titleId == 0x48415A41) {
                                continue;
                            }
                            mpChannelTitleIds[channelIndex] = info->titleId;
                            addedTitle = true;
                            ++titleIndex;
                            break;
                        }
                    }
                }

                if (addedTitle || result == NandSDWorker::RESULT_SD_APP_LOC_NOT_FOUND) {
                    enqueueLoadNotice();
                }
            } else {
                int channelCount = 0;
                int channelIndex = 0;
                u32 titleIndex = 0;
                for (; titleIndex < mSDTitleCount; ++titleIndex) {
                    u32 titleId = mpSDTitleInfo[titleIndex].titleId;
                    if (titleId != 0x48415A41) {
                        ++channelCount;
                        mpChannelTitleIds[channelIndex++] = titleId;
                        if (channelCount == mPageCount * 12) {
                            break;
                        }
                    }
                }
                enqueueLoadNotice();
            }

            mWorkerCommand = 1;
            mbNeedsRefresh = true;
            u32 titleCount = mbHazardTitleFound ? mSDTitleCount - 1 : mSDTitleCount;
            if (titleCount > static_cast<u32>(mPageCount * 12)) {
                mbOperationActive = true;
            }
            if (titleCount >= static_cast<u32>(mPageCount * 12)) {
                mbSDCardBroken = true;
            }
            refreshAfterSDTitleList();
        }

        void SDChannelSelect::processWorkerCommands() {
            switch (mCurrentSDState) {
            case 1:
            case 3:
            case 4:
                mbInitialLoadComplete = false;
                break;
            case 2:
                clearCommandQueue();
                clearNoticeQueue();
                break;
            default:
                break;
            }

            if (mState < 8) {
                if (mState == 1) {
                } else if (mState >= 1) {
                    goto process_worker;
                } else if (mState >= 0) {
                    goto process_worker;
                }
            } else {
                if (mState >= 15) {
                } else if (mState >= 12) {
                    goto process_worker;
                }
            }
            if (mCurrentSDState < 5 && mCurrentSDState >= 1 && mDialogState == 0) {
                mSourcePage = -1;
                mSourceIndex = -1;
                mbShowNoCardMessage = true;
                refreshChannelList();
                memset(mpChannelTitleIds, 0, mPageCount * 0x30);
                memset(mpSDTitleInfo, 0, 0x4b00);
                mSDTitleCount = 0;
                mbOperationActive = false;
                mbHazardTitleFound = false;
                mbChannelLimitReached = false;
                mbSDCardBroken = false;
                mbNeedsRefresh = false;

                switch (mCurrentSDState) {
                case 1:
                    setDialogMessage(2, 0xa9);
                    mWorkerCommand = 6;
                    break;
                case 2:
                    if (!mbInitialLoadComplete) {
                        setDialogMessage(8, 0xaa);
                    }
                    mbInitialLoadComplete = true;
                    enqueueStartNotice();
                    enqueueFinishNotice();
                    break;
                case 3:
                case 4:
                    setDialogMessage(2, 0xab);
                    mWorkerCommand = 15;
                    break;
                default:
                    break;
                }
            }

        process_worker:
            if (mpSDWorker->is_working() || mWorkerState != 4) {
                return;
            }

            if (mCommandQueue.count > 0) {
                SDChannelSelectCommand command =
                    mCommandQueue.commands[mCommandQueue.readIndex];

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
                    mpSDWorker->copy_sd_app_to_nand_async(
                        static_cast<ESTitleId32>(command.titleId), true);
                    mWorkerCommand = 7;
                    break;
                case 6:
                    mpSDWorker->copy_nand_app_to_sd_async(
                        static_cast<ESTitleId>(command.titleId));
                    mWorkerCommand = 9;
                    break;
                case 7: {
                    mpSDWorker->delete_nand_app_async(
                        static_cast<ESTitleId>(command.titleId),
                        command.arguments.values[2] != 0);
                    mWorkerCommand = 10;
                    u32 index = 0;
                    if (mNandTitleCount > 0) {
                        do {
                            if (mpNandTitleInfo[index].curTitleId == command.titleId) {
                                break;
                            }
                            ++index;
                        } while (index < mNandTitleCount);
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
                        static_cast<ESTitleId>(command.titleId),
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
                    mpSDWorker->delete_sd_app_async(
                        static_cast<ESTitleId32>(command.titleId));
                    mWorkerCommand = 13;
                    break;
                default:
                    break;
                }

                mLastOperation = command.type;
                mCommandQueue.pop();
            } else if (mNoticeQueue.count > 0) {
                SDChannelSelectCommand notice =
                    mNoticeQueue.notices[mNoticeQueue.readIndex];
                SDChannelObj* channel = findChannelObject(
                    notice.arguments.values[1], notice.arguments.values[2]);
                if (channel != NULL && channel->mStateFlags >= 1 &&
                    channel->mStateFlags <= 2) {
                    EGG::FrmHeap* objectHeap = EGG::FrmHeap::create(
                        0x212b8, mpLayoutHeap, 2);
                    SDChannelObj* loadedChannel =
                        new (mpThumbnailHeap, 4) SDChannelObj(
                            objectHeap, notice.arguments.values[1],
                            notice.arguments.values[2]);
                    mpCurrentLoadedChannel = loadedChannel;
                    mpSDWorker->get_sd_app_meta_async(
                        notice.arguments.values[0],
                        static_cast<u8*>(iplSDChannelObj_813E3128(loadedChannel)),
                        &loadedChannel->mAppMeta);
                    mWorkerCommand = 3;
                }
                mNoticeQueue.pop();
            }
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

        void SDChannelSelect::handleSDChannelUpdateComplete() {
            if (mpSDWorker->is_working()) {
                return;
            }

            mLastOperation = 14;
            SDChannelObj* channel = mpCurrentLoadedChannel;
            int page = channel->mPage;
            int index = channel->mIndex;
            if (!isChannelInCalc(page, index, mCurrentPage) ||
                static_cast<u32>(mCurrentSDState) - 1 <= 1) {
                destroyChannelObject(channel);
                mWorkerCommand = 1;
                mpCurrentLoadedChannel = NULL;
                return;
            }

            if (mpSDWorker->get_async_result() >= 0) {
                channel->mStateFlags = 0;
                channel->mState = 2;
                DCFlushRange(iplSDChannelObj_813E3128(channel), 0x19000);
            } else {
                memcpy(iplSDChannelObj_813E3128(channel),
                       mpCorruptIconFile->getBuffer(), mpCorruptIconFile->getLength());
                memset(&channel->mAppMeta, 0, sizeof(channel->mAppMeta));
                channel->mStateFlags = 3;
                channel->mState = 2;
            }

            SDChannelObj* previous = findChannelObject(page, index);
            if (previous != NULL) {
                nw4r::ut::List_Insert(&mChannelObjects, previous, channel);
                nw4r::ut::List_Remove(&mChannelObjects, previous);
                destroyChannelObject(previous);
            } else {
                nw4r::ut::List_Append(&mChannelObjects, channel);
            }

            updateChannelObject(channel);
            if (mCurrentPage == page) {
                mpPaneManager->initPane(getChannelPane(index));
            }

            mWorkerCommand = 1;
            mpCurrentLoadedChannel = NULL;
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

        void SDChannelSelect::updateChannelNotices(int pageOffset, int index) {
            int page = mCurrentPage + pageOffset;
            if (page < 0 || mpChannelTitleIds == NULL) {
                return;
            }

            int indexStep;
            int pageTitleIndex;
            int firstIndex;
            switch (pageOffset) {
            case -2:
                firstIndex = 3;
                indexStep = 4;
                break;
            case 2:
                firstIndex = 0;
                indexStep = 4;
                break;
            default:
                firstIndex = 0;
                indexStep = 1;
                break;
            }

            pageTitleIndex = page * 12;
            if (index >= 0 && index < 12) {
                SDChannelObj* channel = findChannelObject(page, index);
                if (channel != NULL) {
                    int titleIndex = pageTitleIndex + index;
                    if (channel->mStateFlags == 2) {
                        ESTitleId titleId = mpChannelTitleIds[titleIndex];
                        if (titleId != 0) {
                            enqueueNotice(titleId, page, index);
                        }
                    }
                }
            }

            for (; firstIndex < 12; firstIndex += indexStep) {
                if (index != firstIndex) {
                    SDChannelObj* channel = findChannelObject(page, firstIndex);
                    if (channel != NULL) {
                        int titleIndex = pageTitleIndex + firstIndex;
                        if (channel->mStateFlags == 2) {
                            ESTitleId titleId = mpChannelTitleIds[titleIndex];
                            if (titleId != 0) {
                                enqueueNotice(titleId, page, firstIndex);
                            }
                        }
                    }
                }
            }
        }

        void SDChannelSelect::processWorkerState() {
            mPreviousSDState = mCurrentSDState;
            mCurrentSDState = mpSDWorker->get_sd_state();

            switch (mWorkerState) {
            case 1:
                handleWorkerStartup();
                break;
            case 2:
                handleNandTitleCount();
                break;
            case 3:
                handleNandTitleUsage();
                break;
            }

            switch (mWorkerCommand) {
            case 0:
                processWorkerCommands();
                break;
            case 1:
                handleNandTitleUsageComplete();
                break;
            case 2:
                handleSDTitleList();
                break;
            case 3:
                handleSDMountComplete();
                break;
            case 4:
                handleSDTitleListResult();
                break;
            case 5:
                handleSDChannelUpdateComplete();
                break;
            case 6:
                handleCopyComplete();
                break;
            case 7:
                handleSDLocationUpdateComplete();
                break;
            case 8:
                handleSDLocationReadComplete();
                break;
            case 9:
                handleMoveComplete();
                break;
            case 10:
                handleBackupFitComplete();
                break;
            case 11:
                handleNandSDCleanupComplete();
                break;
            case 12:
                handleSDDeleteComplete();
                break;
            case 13:
                handleSDCardReady();
                break;
            case 14:
                handleCardCommand();
                break;
            case 15:
                break;
            }

            if (mCurrentSDState != 6) {
                switch (mState) {
                case 15:
                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                    mbDialogActive = true;
                    break;
                }
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

            switch (mDialogState) {
            case 0:
                if (mOperationState != 10) {
                    if (mOperationState < 10 && mOperationState == 7) {
                        mOperationState = 8;
                    }
                } else {
                    mOperationState = 14;
                }
                break;
            case 2:
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
                break;
            case 1:
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
                break;
            case 8:
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
                break;
            default:
                break;
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

        bool SDChannelSelect::isCurrentTitleUsageEnough(const s32* usage) const {
            s32 blocks = mSecondTitleCount;
            s32 bytes = mFirstTitleCount;
            ESTitleId currentTitleId = SCGetTmpTitleID();

            u32 titleCount = mNandTitleCount;
            u32 index;
            for (index = 0; index < titleCount; ++index) {
                if (mpNandTitleInfo[index].curTitleId == currentTitleId) {
                    break;
                }
            }
            if (index < titleCount) {
                bytes += mpNandTitleInfo[index].size;
                blocks += mpNandTitleInfo[index].inode;
            }

            return bytes >= usage[0] && blocks >= usage[1];
        }

        void SDChannelSelect::getCurrentTitleUsage(s32* bytes, s32* blocks) const {
            *bytes = mFirstTitleCount;
            *blocks = mSecondTitleCount;
            ESTitleId currentTitleId = SCGetTmpTitleID();

            u32 titleCount = mNandTitleCount;
            u32 index;
            for (index = 0; index < titleCount; ++index) {
                if (mpNandTitleInfo[index].curTitleId == currentTitleId) {
                    break;
                }
            }
            if (index < titleCount) {
                *bytes += mpNandTitleInfo[index].size;
                *blocks += mpNandTitleInfo[index].inode;
            }
        }

        bool SDChannelSelect::collectTitlesByUsage(
            const s32* firstUsage, const s32* secondUsage, ESTitleId* titleIds,
            char* titleNames, u32* titleCount) {
            s32 bytes;
            s32 blocks;
            getCurrentTitleUsage(&bytes, &blocks);
            *titleCount = 0;

            for (u32 index = 0; index < mNandTitleCount; ++index) {
                if (mpNandTitleInfo[index].curTitleId != 0x48415A41) {
                    int page;
                    int channelIndex;
                    if (System::getChannelManager()->hasChannel(
                            mpNandTitleInfo[index].curTitleId, &page, &channelIndex) != 0) {
                        bytes += mpNandTitleInfo[index].size;
                        blocks += mpNandTitleInfo[index].inode;
                        titleIds[*titleCount] = mpNandTitleInfo[index].curTitleId;
                        wchar_t* titleName = System::getChannelManager()->getTitleName(
                            page, channelIndex, 0);
                        memcpy(titleNames + *titleCount * 0x2a, titleName, 0x2a);
                        u32 nextTitleCount = *titleCount + 1;
                        *titleCount = nextTitleCount;

                        if (bytes < secondUsage[0] || blocks < secondUsage[1]) {
                            continue;
                        }
                        return true;
                    }
                }
            }

            if (bytes >= firstUsage[0] && blocks >= firstUsage[1]) {
                return true;
            }
            return false;
        }

        bool SDChannelSelect::collectTitlesFromNandUsage(
            const s32* firstUsage, const s32* secondUsage,
            ESTitleId* titleIds, char* titleNames, u32* titleCount) {
            s32 bytes;
            s32 blocks;
            getCurrentTitleUsage(&bytes, &blocks);
            *titleCount = 0;

            for (int index = mNandTitleCount - 1; index >= 0; --index) {
                if (mpNandTitleInfo[index].curTitleId == 0x48415A41) {
                    continue;
                }

                int page;
                int channelIndex;
                if (System::getChannelManager()->hasChannel(
                        mpNandTitleInfo[index].curTitleId, &page, &channelIndex) == 0) {
                    continue;
                }

                bytes += mpNandTitleInfo[index].size;
                blocks += mpNandTitleInfo[index].inode;
                titleIds[*titleCount] = mpNandTitleInfo[index].curTitleId;
                wchar_t* titleName = System::getChannelManager()->getTitleName(
                    page, channelIndex, 0);
                memcpy(titleNames + *titleCount * 0x2a, titleName, 0x2a);
                ++*titleCount;

                if (bytes >= secondUsage[0] && blocks >= secondUsage[1]) {
                    return true;
                }
            }

            if (bytes >= firstUsage[0] && blocks >= firstUsage[1]) {
                return true;
            }
            return false;
        }

        bool SDChannelSelect::findAdjacentChannel(int direction, int* page, int* index) const {
            int currentPage = mCurrentPage;
            int currentIndex = mCurrentChannelIndex;
            int pageSize = MAX_CHANNEL_INDEX;
            int currentSlot = currentPage * pageSize + currentIndex;
            int step = direction == 1 ? -1 : 1;
            int slotCount = mPageCount * pageSize;
            int slot = currentSlot + step;

            if (slot < 0) {
                slot = slotCount - 1;
            }
            if (slot >= slotCount) {
                slot = 0;
            }

            while (slot != currentSlot) {
                int candidatePage = slot / pageSize;
                int candidateIndex = slot % pageSize;
                if (mpChannelTitleIds[slot] != 0) {
                    *page = candidatePage;
                    *index = candidateIndex;
                    return true;
                }

                slot += step;
                if (slot < 0) {
                    slot = slotCount - 1;
                }
                if (slot >= slotCount) {
                    slot = 0;
                }
            }

            *page = currentPage;
            *index = currentIndex;
            return false;
        }

        extern "C" bool iplSDChannelSelect_813DD240(
            SDChannelSelect* scene, const s32* requiredBytes, const s32* requiredBlocks,
            ESTitleId* titleIds, char* titleNames, u32* titleCount);

        bool SDChannelSelect::collectTitlesByChannelOrder(
            const s32* firstUsage, const s32* secondUsage, ESTitleId* titleIds,
            char* titleNames, u32* titleCount) {
            static const int channelOrder[MAX_CHANNEL_INDEX] = {
                11, 7, 3, 10, 6, 2, 9, 5, 1, 8, 4, 0,
            };
            s32 bytes;
            s32 blocks;
            getCurrentTitleUsage(&bytes, &blocks);
            *titleCount = 0;

            for (int page = MAX_CHANNEL_PAGE - 1; page >= 0; --page) {
                for (int order = 0; order < MAX_CHANNEL_INDEX; ++order) {
                    int channelIndex = channelOrder[order];
                    if (!System::getChannelManager()->mChannels[page][channelIndex].loadedBnr) {
                        continue;
                    }

                    ESTitleId titleId = ES_TITLE_ID(
                        System::getChannelManager()->mChannels[page][channelIndex].info.titleType,
                        System::getChannelManager()->mChannels[page][channelIndex].info.titleCode);
                    if (titleId == 0 || titleId == 0x48415A41) {
                        continue;
                    }

                    for (u32 usageIndex = 0; usageIndex < mNandTitleCount; ++usageIndex) {
                        NandSDWorker::TitleUsage& usage = mpNandTitleInfo[usageIndex];
                        if (usage.curTitleId != titleId) {
                            continue;
                        }

                        bytes += usage.size;
                        blocks += usage.inode;
                        titleIds[*titleCount] = titleId;
                        wchar_t* titleName =
                            System::getChannelManager()->getTitleName(page, channelIndex, 0);
                        memcpy(titleNames + *titleCount * 0x2a, titleName, 0x2a);
                        ++*titleCount;

                        if (bytes >= secondUsage[0] && blocks >= secondUsage[1]) {
                            return true;
                        }
                    }
                }
            }

            if (bytes >= firstUsage[0] && blocks >= firstUsage[1]) {
                return true;
            }
            return false;
        }

        bool SDChannelSelect::collectTitlesBySpecialChannels(
            const s32* firstUsage, const s32* secondUsage, ESTitleId* titleIds,
            char* titleNames, u32* titleCount) {
            const ESTitleId hateTitle = ES_TITLE_ID(0x00010001, 0x48415445);
            const ESTitleId hadeTitle = ES_TITLE_ID(0x00010001, 0x48414445);
            const ESTitleId hazardTitle = 0x48415A41;
            int hateUsageIndex = -1;
            int hatePage = 0;
            int hateChannelIndex = 0;
            int hadeUsageIndex = -1;
            int hadePage = 0;
            int hadeChannelIndex = 0;
            s32 bytes;
            s32 blocks;
            getCurrentTitleUsage(&bytes, &blocks);

            for (u32 usageIndex = 0; usageIndex < mNandTitleCount; ++usageIndex) {
                ESTitleId titleId = mpNandTitleInfo[usageIndex].curTitleId;
                if (titleId == hateTitle) {
                    hateUsageIndex = usageIndex;
                    System::getChannelManager()->hasChannel(
                        hateTitle, &hatePage, &hateChannelIndex);
                } else if (titleId == hadeTitle) {
                    hadeUsageIndex = usageIndex;
                    System::getChannelManager()->hasChannel(
                        hadeTitle, &hadePage, &hadeChannelIndex);
                }
            }

            *titleCount = 0;
            for (int usageIndex = mNandTitleCount - 1; usageIndex >= 0; --usageIndex) {
                NandSDWorker::TitleUsage& usage = mpNandTitleInfo[usageIndex];
                ESTitleId titleId = usage.curTitleId;
                if (titleId == hazardTitle || titleId == hateTitle || titleId == hadeTitle) {
                    continue;
                }

                int page;
                int channelIndex;
                if (System::getChannelManager()->hasChannel(titleId, &page, &channelIndex) == 0) {
                    continue;
                }
                if (iplSavedata_813597A0(System::getSaveData(), titleId) != FALSE) {
                    continue;
                }

                bytes += usage.size;
                blocks += usage.inode;
                titleIds[*titleCount] = titleId;
                wchar_t* titleName = System::getChannelManager()->getTitleName(
                    page, channelIndex, 0);
                memcpy(titleNames + *titleCount * 0x2a, titleName, 0x2a);
                ++*titleCount;

                if (bytes >= secondUsage[0] && blocks >= secondUsage[1]) {
                    return true;
                }
            }

            ESTitleId* cachedTitles = &System::getSaveData()->mData.titleCache[0][0];
            for (int cacheIndex = MAX_CHANNEL_TOTAL - 1; cacheIndex >= 0; --cacheIndex) {
                ESTitleId titleId = cachedTitles[cacheIndex];
                int page;
                int channelIndex;
                if (System::getChannelManager()->hasChannel(titleId, &page, &channelIndex) == 0) {
                    continue;
                }

                for (u32 usageIndex = 0; usageIndex < mNandTitleCount; ++usageIndex) {
                    NandSDWorker::TitleUsage& usage = mpNandTitleInfo[usageIndex];
                    if (usage.curTitleId != titleId) {
                        continue;
                    }

                    bytes += usage.size;
                    blocks += usage.inode;
                    titleIds[*titleCount] = titleId;
                    wchar_t* titleName = System::getChannelManager()->getTitleName(
                        page, channelIndex, 0);
                    memcpy(titleNames + *titleCount * 0x2a, titleName, 0x2a);
                    ++*titleCount;

                    if (bytes >= secondUsage[0] && blocks >= secondUsage[1]) {
                        return true;
                    }
                }
            }

            if (hadeUsageIndex >= 0) {
                NandSDWorker::TitleUsage& usage = mpNandTitleInfo[hadeUsageIndex];
                bytes += usage.size;
                blocks += usage.inode;
                titleIds[*titleCount] = hadeTitle;
                wchar_t* titleName =
                    System::getChannelManager()->getTitleName(
                        hadePage, hadeChannelIndex, 0);
                memcpy(titleNames + *titleCount * 0x2a, titleName, 0x2a);
                ++*titleCount;

                if (bytes >= secondUsage[0] && blocks >= secondUsage[1]) {
                    return true;
                }
            }

            if (hateUsageIndex >= 0) {
                NandSDWorker::TitleUsage& usage = mpNandTitleInfo[hateUsageIndex];
                bytes += usage.size;
                blocks += usage.inode;
                titleIds[*titleCount] = hateTitle;
                wchar_t* titleName =
                    System::getChannelManager()->getTitleName(
                        hatePage, hateChannelIndex, 0);
                memcpy(titleNames + *titleCount * 0x2a, titleName, 0x2a);
                ++*titleCount;

                if (bytes >= secondUsage[0] && blocks >= secondUsage[1]) {
                    return true;
                }
            }

            if (bytes >= firstUsage[0] && blocks >= firstUsage[1]) {
                return true;
            }
            return false;
        }

        bool SDChannelSelect::collectTitlesForMode(
            const s32* requiredBytes, const s32* requiredBlocks,
            ESTitleId* titleIds, char* titleNames, u32* titleCount, int searchMode) {
            switch (searchMode) {
            case 0:
                return collectTitlesBySpecialChannels(
                    requiredBytes, requiredBlocks, titleIds, titleNames, titleCount);
            case 1:
                return collectTitlesByChannelOrder(
                    requiredBytes, requiredBlocks, titleIds, titleNames, titleCount);
            case 2:
                return collectTitlesFromNandUsage(
                    requiredBytes, requiredBlocks, titleIds, titleNames, titleCount);
            case 3:
                return collectTitlesByUsage(
                    requiredBytes, requiredBlocks, titleIds, titleNames, titleCount);
            default:
                return false;
            }
        }

        void SDChannelSelect::finishDialogOperation() {
            if (System::getDialog()->getLastResult() != DialogWindow::RESULT_NONE) {
                mbOperationActive = false;
                mState = 1;
            }
        }

        void SDChannelSelect::finishDialogTransition() {
            if (System::getDialog()->getLastResult() != DialogWindow::RESULT_NONE) {
                mState = 1;
            }
        }

        void SDChannelSelect::updateChannelObjects() {
            SDChannelObj* channel = NULL;
            while (channel = static_cast<SDChannelObj*>(nw4r::ut::List_GetNext(&mChannelObjects, channel)),
                   channel != NULL) {
                updateChannelObject(channel);
            }
        }

        void SDChannelSelect::updateChannelObject(SDChannelObj* channel) {
            iplSDChannelObj_813E3104(channel);
            iplSDChannelObj_813E311C(channel, mpDialogHeap, mpChannelHeap);
            iplSDChannelObj_813E3178(channel,
                                     getChannelBasePane(channel->getPage(), channel->getIndex(),
                                                        mCurrentPage));
            iplSDChannelObj_813E3180(channel, mpLayoutFile);
        }

        void SDChannelSelect::calcChannelObjects() {
            SDChannelObj* channel = NULL;
            while (channel = static_cast<SDChannelObj*>(nw4r::ut::List_GetNext(&mChannelObjects, channel)),
                   channel != NULL) {
                iplSDChannelObj_813E322C(channel);
            }
        }

        void SDChannelSelect::drawChannelTransitionObjects() {
            int index;
            int page;
            SDChannelObj* channel = NULL;
            while (channel = static_cast<SDChannelObj*>(nw4r::ut::List_GetNext(&mChannelObjects, channel)),
                   channel != NULL) {
                page = channel->getPage();
                index = channel->getIndex();
                if (!hasChannelObject(page, index) || !isChannelReady(channel)) {
                    continue;
                }

                setChannelScissor(channel);
                iplSDChannelObj_813E32C8(channel);

                if (iplSDChannelObj_813E3330(channel)) {
                    if (mState < 24 && mState >= 15 &&
                        (page != mSourcePage || index != mSourceIndex)) {
                        nw4r::math::VEC3 position(channel->getTranslate());
                        mpPageLayouts[0]->GetRootPane()->SetTranslate(position);
                        mpPageLayouts[0]->calcMtx();
                        mpPageLayouts[0]->draw();
                    }
                } else if (channel->mState == 2) {
                    nw4r::math::VEC3 position(channel->getTranslate());
                    mpErrorLayout->GetRootPane()->SetTranslate(position);
                    mpErrorLayout->calcMtx();
                    mpErrorLayout->draw();
                }

                switch (mState) {
                case 15:
                case 16:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                    if (page == mSourcePage && index == mSourceIndex) {
                        nw4r::math::VEC3 position(channel->getTranslate());
                        mpStateLayout->GetRootPane()->SetTranslate(position);
                        mpStateLayout->calcMtx();
                        mpStateLayout->draw();
                    }
                    break;
                }

                if (mState < 22 && mState >= 19 &&
                    page == mDestinationPage && index == mDestinationIndex) {
                    mpPageLayouts[2]->draw();
                    mpPointerLayout->draw();
                }
            }
        }

        void SDChannelSelect::drawChannelObjects() {
            SDChannelObj* channel = NULL;
            while (channel = static_cast<SDChannelObj*>(nw4r::ut::List_GetNext(&mChannelObjects, channel)),
                   channel != NULL) {
                if (hasChannelObject(channel->getPage(), channel->getIndex())) {
                    iplSDChannelObj_813E3304(channel);
                }
            }

            channel = NULL;
            while (channel = static_cast<SDChannelObj*>(nw4r::ut::List_GetNext(&mChannelObjects, channel)),
                   channel != NULL) {
                if (hasChannelObject(channel->getPage(), channel->getIndex())) {
                    iplSDChannelObj_813E330C(channel);
                }
            }
        }

        void SDChannelSelect::updateArrowVisibility() {
            int leftPageOffset;
            if (mState == 10 || mState == 22) {
                leftPageOffset = 1;
            } else {
                leftPageOffset = 0;
            }

            if (mCurrentPage - 1 - leftPageOffset >= 0) {
                mpLayout->FindPaneByName(mscEdgePaneNames[0])->SetVisible(true);
                mpLayout->FindPaneByName(mscEdgePaneNames[1])->SetVisible(true);
            } else {
                mpLayout->FindPaneByName(mscEdgePaneNames[1 - leftPageOffset])->SetVisible(false);
            }

            int rightPageOffset;
            if (mState == 11 || mState == 23) {
                rightPageOffset = 1;
            } else {
                rightPageOffset = 0;
            }
            if (mCurrentPage + rightPageOffset + 1 < mPageCount) {
                mpLayout->FindPaneByName(mscEdgePaneNames[3])->SetVisible(true);
                mpLayout->FindPaneByName(mscEdgePaneNames[4])->SetVisible(true);
            } else {
                mpLayout->FindPaneByName(mscEdgePaneNames[rightPageOffset + 3])->SetVisible(false);
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
                    if (mCurrentPage > 0) {
                        button->initArrowAppearance(1, true);
                    } else {
                        button->initArrowAppearance(1, false);
                    }

                    if (mPageCount > 1 && mCurrentPage < mPageCount - 1) {
                        button->initArrowAppearance(0, true);
                    } else {
                        button->initArrowAppearance(0, false);
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
            mpErrorLayout->calc();
            mpPointerLayout->calc();
            mpStateLayout->calc();
            mpNoCardLayout->calc();
            processWorkerState();
        }

        extern "C" void iplSDChannelObj_813E3534(SDChannelObj* channel, int enabled);

        FaderSceneCommand SDChannelSelect::calcNormal() {
            int state = mState;
            if (state == 13) {
                return FADER_SCN_CONTINUE;
            }

            switch (state) {
            case 0:
                processNormalInput();
                break;
            case 1:
                setPageActionFrame();
                break;
            case 2:
                finishPageScroll();
                break;
            case 3:
                createChildScene(0x23, this, NULL, this);
                mState = 6;
                break;
            case 4:
                advancePageAnimation();
                break;
            case 5:
                mState = 13;
                break;
            case 6:
                initializeNormalPage();
                break;
            case 7:
                updateDragState();
                break;
            case 8:
                updateDragPageTransition();
                break;
            case 9:
                finishDragWait();
                break;
            case 10:
                finishDragPageTransition();
                break;
            case 11:
                applyChannelMove();
                break;
            case 12:
                finishChannelMove();
                break;
            case 13:
                resetDragPreview();
                break;
            case 14:
                finishDragPageChange();
                break;
            case 15:
                handleFourPageDialog();
                break;
            case 16:
                flushSaveDataAndMountSD();
                break;
            case 17:
                handleThreePageDialog();
                break;
            case 18:
                finishCardDialog();
                break;
            case 19:
                finishDialogOperation();
                break;
            case 20:
                finishDialogTransition();
                break;
            case 21:
            case 22:
            case 23:
            case 24:
            case 25:
            case 26:
            case 27:
            case 28:
            case 29:
            default:
                break;
            }

            if (state == 1 && mState != 1 && mState != 15) {
                SDChannelObj* channel = NULL;
                while (channel = static_cast<SDChannelObj*>(
                           nw4r::ut::List_GetNext(&mChannelObjects, channel)),
                       channel != NULL) {
                    int channelPage = channel->getPage();
                    int channelIndex = channel->getIndex();
                    if (channelPage == mCurrentPage) {
                        if (mState != 5 || channelIndex != mCurrentChannelIndex) {
                            iplSDChannelObj_813E34E8(channel, 1);
                        }
                        iplSDChannelObj_813E3534(channel, 1);
                    }
                }

                for (int index = 0; index < MAX_CHANNEL_INDEX; ++index) {
                    mpPaneManager->initPane(getChannelPane(index));
                }
            }

            return mState == 4 ? FADER_SCN_NEXT : FADER_SCN_CONTINUE;
        }

        void SDChannelSelect::initCalcFadeout() {
            if (mState == 4) {
                clearCommandQueue();
                clearNoticeQueue();
                System::getFader()->fadeOut();
                TVRCManager::getHandle()->setEnable(FALSE);
                System::getChannelManager()->refreshAsync();
                reserveAllSceneDestruction(4, reinterpret_cast<void*>(System::getNwc24Manager()->received()));
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
            if (mState != 13) {
                if (System::onDrawLayer(DRAW_LAYER_DEFAULT)) {
                    if (mState == 7 || mState == 12 || mState == 14) {
                        utility::Graphics::setOrthoTransAndScale(mPosition, mScale);
                    }
                    utility::Graphics::setOrtho();

                    for (int edge = 0; edge < PAGE_COUNT; ++edge) {
                        nw4r::lyt::Pane* pane = mpLayout->FindPaneByName(mscBasePaneNames[edge]);
                        pane->SetVisible(true);
                        mpLayout->draw(pane);
                        pane->SetVisible(false);
                    }

                    drawChannelTransitionObjects();
                    updateArrowVisibility();

                    GXSetScissor(0, 0, System::getRenderModeObj()->fbWidth,
                                 System::getRenderModeObj()->efbHeight);

                    nw4r::lyt::Pane* mask = mpLayout->FindPaneByName(mscMaskPaneName);
                    mask->SetVisible(false);
                    mpLayout->draw();

                    nw4r::lyt::TextBox* pageText = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(
                        mpDialogLayout->FindPaneByName("TextBox_00"));
                    for (int page = 0; page < 3; ++page) {
                        wchar_t pageNumber[21];
                        pageNumber[20] = L'\0';
                        swprintf(pageNumber, 19, L"%d", mCurrentPage + page);
                        pageText->SetString(pageNumber, 0);
                        nw4r::lyt::Pane* clockPane = mpLayout->FindPaneByName(mscClockPaneNames[page]);
                        nw4r::math::MTX34 paneMatrix = clockPane->GetGlobalMtx();
                        nw4r::math::VEC3 position(0.0f, 0.0f, 0.0f);
                        PSMTXMultVec(paneMatrix, position, position);
                        mpDialogLayout->GetRootPane()->SetTranslate(position);
                        mpDialogLayout->calcMtx();
                        mpDialogLayout->draw();
                    }

                    drawChannelObjects();
                    mask->SetVisible(true);
                    mpLayout->draw(mask);
                    mpPageLayouts[1]->draw();
                    mpNoCardLayout->draw();
                    return;
                }
            }

            if (mState == 13 && System::onDrawLayer(DRAW_LAYER_DEFAULT)) {
                utility::Graphics::setOrtho();
                GXColor color = {0, 0, 0, 255};
                nw4r::ut::Rect projection;
                System::getProjectionRect(&projection);
                utility::Graphics::drawPolygon(projection, color);
            }
        }

        void SDChannelSelect::destroyChannelObject(SDChannelObj* channel) {
            EGG::Heap* heap = channel->getHeap();
            delete channel;
            if (heap != NULL) {
                heap->destroy();
            }
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

            SDChannelObj* channel = NULL;
            System::getSaveData()->setLastSDPrevPage(mCurrentPage);

            while (channel = static_cast<SDChannelObj*>(nw4r::ut::List_GetNext(&mChannelObjects, NULL)),
                   channel != NULL) {
                nw4r::ut::List_Remove(&mChannelObjects, channel);
                destroyChannelObject(channel);
            }

            mpLayoutHeap->destroy();
            mpThumbnailHeap->destroy();
            mpDialogHeap->destroy();
            mpChannelHeap->destroy();

            delete mpRsoThread;
            mpRsoHeap->destroy();

            if (mpSaveDataFile != NULL) {
                while (!System::getSaveData()->isFinished(mpSaveDataFile)) {
                    OSSleepTicks(OSMicrosecondsToTicks((OSTime)100));
                }
                delete mpSaveDataFile;
            }
            mpSaveDataFile = NULL;

            if (mpSDWorker != NULL) {
                if (!mpSDWorker->is_terminated()) {
                    mpSDWorker->requestCancel();
                    while (mpSDWorker->is_working()) {
                        OSSleepTicks(OSMicrosecondsToTicks((OSTime)100));
                    }
                    mpSDWorker->terminate_async();
                    while (!mpSDWorker->is_terminated()) {
                        OSSleepTicks(OSMicrosecondsToTicks((OSTime)100));
                    }
                }

                System::getMem2App()->free(mpWorkerHeap);
                System::getMem2App()->free(mpThumbnailWorkHeap);

                if (mpSDTitleIds != NULL) {
                    delete[] mpSDTitleIds;
                }
                if (mpSDTitleInfo != NULL) {
                    delete[] mpSDTitleInfo;
                }
                if (mpChannelTitleIds != NULL) {
                    delete[] mpChannelTitleIds;
                }
                if (mpNandTitleInfo != NULL) {
                    delete[] mpNandTitleInfo;
                }
                mWorkerCommand = 6;
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
            sFourPageDialogPages[3].layoutObj = mpHelpButtonLayout;

            SDChannelSelectEventHandler* eventHandler = new SDChannelSelectEventHandler(this);
            mpPaneManager = new gui::PaneManager(eventHandler, mpLayout->getDrawInfo(),
                                                NULL, NULL);
            mpPaneManager->createLayoutScene(*mpLayout->getNW4RLyt());
            mpPaneManager->setAllComponentTriggerTarget(false);

            for (int index = 0; index < MAX_CHANNEL_INDEX; ++index) {
                mpPaneManager->getPaneComponentByPane(getChannelPane(index))
                    ->setTriggerTarget(true);
            }

            for (int index = 0; index < 4; ++index) {
                mpPageAnimations[index] = new math::HermiteIntp<math::VEC3>();
            }
        }

        bool SDChannelSelect::isChannelInCalc(int page, int index, int currentPage) const {
            int relativePage = page - currentPage;
            if (relativePage <= -3 || relativePage >= 3 ||
                strcmp(mscChannelPaneNames[relativePage + 2][index], "") == 0) {
                return false;
            }
            return true;
        }

        nw4r::lyt::Pane* SDChannelSelect::getChannelBasePane(int page, int index,
                                                             int currentPage) const {
            if (isChannelInCalc(page, index, currentPage)) {
                return mpLayout->FindPaneByName(mscChannelPaneNames[page - currentPage + 2][index]);
            }
            return mpLayout->FindPaneByName("Picture_16");
        }

        nw4r::lyt::Pane* SDChannelSelect::getCenterChannelPane(int index) const {
            return mpLayout->FindPaneByName(mscChannelPaneNames[2][index]);
        }

        nw4r::lyt::Pane* SDChannelSelect::getChannelPane(int index) const {
            return mpLayout->FindPaneByName(mscChannelPaneNames[2][index]);
        }

        void SDChannelSelect::createChannelList(int page, bool force) {
            for (int index = 0; index < MAX_CHANNEL_INDEX; ++index) {
                if (force || findChannelObject(page, index) == NULL) {
                    createChannelObject(page, index);
                }
            }

            if (page < mPageCount - 1) {
                for (int index = 0; index < MAX_CHANNEL_INDEX; index += 4) {
                    if (force || findChannelObject(page + 1, index) == NULL) {
                        createChannelObject(page + 1, index);
                    }
                }
            }

            if (page > 0) {
                for (int index = 3; index < MAX_CHANNEL_INDEX; index += 4) {
                    if (force || findChannelObject(page - 1, index) == NULL) {
                        createChannelObject(page - 1, index);
                    }
                }
            }
        }

        void SDChannelSelect::destroyUnusedChannelObjects(int currentPage,
                                                           SDChannelObj* keepChannel) {
            int keepPage;
            int keepIndex;
            if (keepChannel != NULL) {
                keepPage = keepChannel->getPage();
                keepIndex = keepChannel->getIndex();
            }

            SDChannelObj* channel = NULL;
            while (channel = static_cast<SDChannelObj*>(
                       nw4r::ut::List_GetNext(&mChannelObjects, channel)),
                   channel != NULL) {
                int page = channel->getPage();
                int index = channel->getIndex();
                if (keepChannel != NULL && page == keepPage && index == keepIndex) {
                    continue;
                }
                switch (mState) {
                case 15:
                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                    if (page == mSourcePage && index == mSourceIndex) {
                        continue;
                    }
                    break;
                }
                if (!isChannelInCalc(page, index, currentPage)) {
                    SDChannelObj* previous = static_cast<SDChannelObj*>(
                        nw4r::ut::List_GetPrev(&mChannelObjects, channel));
                    nw4r::ut::List_Remove(&mChannelObjects, channel);
                    destroyChannelObject(channel);
                    channel = previous;
                }
            }
        }

        void SDChannelSelect::createChannelObject(int page, int index) {
            EGG::FrmHeap* objectHeap = EGG::FrmHeap::create(0x212B8, mpLayoutHeap, 2);
            SDChannelObj* channel = new (mpThumbnailHeap, 4) SDChannelObj(objectHeap, page, index);
            nw4r::ut::List_Append(&mChannelObjects, channel);
        }

#pragma dont_inline on
        BOOL SDChannelSelect::isChannelReady(const SDChannelObj* channel) {
            return channel->mState == 3;
        }
#pragma dont_inline reset

        BOOL SDChannelSelect::isPageCreated(int page) const {
            for (int index = 0; index < MAX_CHANNEL_INDEX; ++index) {
                SDChannelObj* channel = findChannelObject(page, index);
                if (channel == NULL || !isChannelReady(channel)) {
                    return FALSE;
                }
            }

            if (page + 1 < mPageCount) {
                for (int index = 0; index < MAX_CHANNEL_INDEX; index += 4) {
                    SDChannelObj* channel = findChannelObject(page + 1, index);
                    if (channel == NULL || !isChannelReady(channel)) {
                        return FALSE;
                    }
                }
            }

            if (page - 1 >= 0) {
                for (int index = 3; index < MAX_CHANNEL_INDEX; index += 4) {
                    SDChannelObj* channel = findChannelObject(page - 1, index);
                    if (channel == NULL || !isChannelReady(channel)) {
                        return FALSE;
                    }
                }
            }

            return TRUE;
        }

        BOOL SDChannelSelect::prepareRestarting(int page) {
            if (page == mCurrentPage) {
                return isPageCreated(page);
            }

            mCurrentPage = page;
            refreshPageObjects(page, NULL, -1);
            return isPageCreated(page);
        }

        void SDChannelSelect::startPageTransition(int page, int index) {
            mCurrentPage = page;
            mCurrentChannelIndex = index;
            mpLayout->setAnmType(ANIM_TYPE_BACKWARD, -1);
            mpLayout->start(-1);

            nw4r::math::VEC3 position(0.0f, 0.0f, 0.0f);
            nw4r::lyt::Pane* pane = getCenterChannelPane(index);
            PSMTXMultVec(pane->GetGlobalMtx(), position, position);
            math::VEC3 animationPosition(position);
            initPageAnimations(animationPosition, 1);
            updatePageTransform();
            mState = 14;
        }

        void SDChannelSelect::moveChannelObjectsToDrawOrder(int page, int mode) {
            for (int index = 0; index < MAX_CHANNEL_INDEX; ++index) {
                if (mode == -1) {
                    if ((index & 3) == 0) {
                        continue;
                    }
                } else if (mode == 1 && (index & 3) == 3) {
                    continue;
                }

                SDChannelObj* channel = findChannelObject(page, index);
                if (channel != NULL) {
                    nw4r::ut::List_Remove(&mChannelObjects, channel);
                    nw4r::ut::List_Append(&mChannelObjects, channel);
                }
            }

            if (mode != 1 && page + 1 < mPageCount) {
                for (int index = 0; index < MAX_CHANNEL_INDEX; index += 4) {
                    SDChannelObj* channel = findChannelObject(page + 1, index);
                    if (channel != NULL) {
                        nw4r::ut::List_Remove(&mChannelObjects, channel);
                        nw4r::ut::List_Append(&mChannelObjects, channel);
                    }
                }
            }

            if (mode != -1 && page - 1 >= 0) {
                for (int index = 3; index < MAX_CHANNEL_INDEX; index += 4) {
                    SDChannelObj* channel = findChannelObject(page - 1, index);
                    if (channel != NULL) {
                        nw4r::ut::List_Remove(&mChannelObjects, channel);
                        nw4r::ut::List_Append(&mChannelObjects, channel);
                    }
                }
            }
        }

        void SDChannelSelect::updateChannelObjectOrder(int page) {
            moveChannelObjectsToDrawOrder(page, 0);
            if (page < mPageCount - 1) {
                moveChannelObjectsToDrawOrder(page + 1, -1);
            }
            if (page > 0) {
                moveChannelObjectsToDrawOrder(page - 1, 1);
            }
        }

        void SDChannelSelect::refreshPageObjects(int page, SDChannelObj* keepChannel,
                                                  int noticeIndex) {
            destroyUnusedChannelObjects(page, keepChannel);
            createChannelList(page, false);
            if (page < mPageCount - 1) {
                createChannelList(page + 1, false);
            }
            if (page > 0) {
                createChannelList(page - 1, false);
            }

            updateChannelObjectOrder(page);

            SDChannelObj* channel = NULL;
            while (channel = static_cast<SDChannelObj*>(
                       nw4r::ut::List_GetNext(&mChannelObjects, channel)),
                   channel != NULL) {
                int titleIndex = channel->getPage() * MAX_CHANNEL_INDEX + channel->getIndex();
                if (!iplSDChannelObj_813E3330(channel) && mpChannelTitleIds[titleIndex] != 0 &&
                    mbNeedsRefresh) {
                    channel->mStateFlags = 2;
                }
            }

            updateChannelObjects();
            if (mbNeedsRefresh) {
                clearNoticeQueue();
                updateChannelNotices(0, noticeIndex);
                updateChannelNotices(-1, -1);
                updateChannelNotices(1, -1);
                updateChannelNotices(-2, -1);
                updateChannelNotices(2, -1);
            }
        }

        void SDChannelSelect::setCurrentPageAndRefresh(int page, int index,
                                                       SDChannelObj* keepChannel) {
            mCurrentPage = page;
            mCurrentChannelIndex = index;
            refreshPageObjects(page, keepChannel, index);
        }

        void SDChannelSelect::handleFourPageDialog() {
            if (System::getDialog()->callBtn2Multi(sFourPageDialogPages, 4, 10)) {
                mState = 25;
            }
        }

        void SDChannelSelect::handleThreePageDialog() {
            if (System::getDialog()->callBtn2Multi(sThreePageDialogPages, 3, 10)) {
                mState = 27;
            }
        }

        void SDChannelSelect::refreshChannelList() {
            SDChannelObj* channel = NULL;
            while (channel = static_cast<SDChannelObj*>(
                       nw4r::ut::List_GetNext(&mChannelObjects, channel)),
                   channel != NULL) {
                if (iplSDChannelObj_813E3330(channel)) {
                    SDChannelObj* previous = static_cast<SDChannelObj*>(
                        nw4r::ut::List_GetPrev(&mChannelObjects, channel));
                    nw4r::ut::List_Remove(&mChannelObjects, channel);
                    destroyChannelObject(channel);
                    channel = previous;
                } else if (channel->mStateFlags == 2) {
                    channel->mStateFlags = 1;
                }
            }

            createChannelList(mCurrentPage, false);
            if (mCurrentPage < mPageCount - 1) {
                createChannelList(mCurrentPage + 1, false);
            }
            if (mCurrentPage > 0) {
                createChannelList(mCurrentPage - 1, false);
            }
            updateChannelObjects();
        }

        void SDChannelSelect::refreshAfterSDTitleList() {
            SDChannelObj* channel = NULL;
            while (channel = static_cast<SDChannelObj*>(
                       nw4r::ut::List_GetNext(&mChannelObjects, channel)),
                   channel != NULL) {
                int channelIndex = channel->mPage * 12 + channel->mIndex;
                if (!iplSDChannelObj_813E3330(channel) &&
                    mpChannelTitleIds[channelIndex] != 0) {
                    channel->mStateFlags = 2;
                }
            }

            clearNoticeQueue();
            updateChannelNotices(0, -1);
            updateChannelNotices(-1, -1);
            updateChannelNotices(1, -1);
            updateChannelNotices(-2, -1);
            updateChannelNotices(2, -1);
        }

        SDChannelObj* SDChannelSelect::findChannelObject(int page, int index) const {
            SDChannelObj* channel = NULL;
            while (channel = static_cast<SDChannelObj*>(
                   nw4r::ut::List_GetNext(&mChannelObjects, channel)),
                   channel != NULL) {
                int channelPage = channel->getPage();
                int channelIndex = channel->getIndex();
                if (channelPage == page && channelIndex == index) {
                    return channel;
                }
            }
            return NULL;
        }

        math::VEC3 SDChannelSelect::getChannelPanePosition(SDChannelSelect* scene, int index) {
            math::VEC3 position(0.0f, 0.0f, 0.0f);
            MTXMultVec(scene->getCenterChannelPane(index)->GetGlobalMtx(), position, position);
            return position;
        }

        void SDChannelSelect::calcPageAnimations() {
            for (int index = 0; index < 4; ++index) {
                math::HermiteIntp<math::VEC3>* animation = mpPageAnimations[index];
                animation->calc();
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
            if (capacity == count) {
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
            bool result = true;
            if (count == 0) {
                result = false;
            } else {
                ++readIndex;
                if (readIndex >= capacity) {
                    readIndex = 0;
                }
                --count;
            }
            return result;
        }

        bool SDChannelSelectNoticeQueue::pop() {
            bool result = true;
            if (count == 0) {
                result = false;
            } else {
                ++readIndex;
                if (readIndex >= capacity) {
                    readIndex = 0;
                }
                --count;
            }
            return result;
        }

        void SDChannelSelect::updatePageTransform() {
            math::VEC3 frames[3];
            for (int index = 0; index < 3; ++index) {
                frames[index] = mpPageAnimations[index]->get();
            }

            nw4r::ut::Rect projection;
            System::getProjectionRect(&projection);

            mPosition = math::VEC3((frames[0].x + frames[1].x) / 2.0f,
                                   (frames[0].y + frames[2].y) / 2.0f, 0.0f);
            mScale = math::VEC2(projection.GetWidth() / (frames[1].x - frames[0].x),
                                projection.GetHeight() / (frames[0].y - frames[2].y));
        }

        void SDChannelSelect::advancePageAnimation() {
            calcPageAnimations();
            updatePageTransform();
            if (!mpPageAnimations[0]->isPlaying()) {
                mState = 12;
            }
        }

        void SDChannelSelect::finishPageScroll() {
            if (mpLayout->isPlaying(0)) {
                return;
            }

            SDButton* button = static_cast<SDButton*>(System::getSceneManager()->getScene(0x24));
            if (mState == 10) {
                --mCurrentPage;
                if (mCurrentPage == 0) {
                    button->animation(15);
                    mbLeftArrowVisible = false;
                } else if (!mbRightArrowVisible) {
                    button->animation(14);
                    mbRightArrowVisible = true;
                }
            } else {
                ++mCurrentPage;
                if (mCurrentPage == mPageCount - 1) {
                    button->animation(16);
                    mbRightArrowVisible = false;
                } else if (!mbLeftArrowVisible) {
                    button->animation(13);
                    mbLeftArrowVisible = true;
                }
            }

            mpLayout->finishBinding();
            refreshPageObjects(mCurrentPage, NULL, -1);
            mState = 1;
        }

        void SDChannelSelect::finishCardDialog() {
            if (System::getDialog()->getLastResult() != DialogWindow::RESULT_NONE) {
                mpPointerLayout->getAnim(0)->initAnmFrame();
                mState = 1;
            }
        }

        void SDChannelSelect::flushSaveDataAndMountSD() {
            if (System::getDialog()->getLastResult() != DialogWindow::RESULT_NONE) {
                mpPointerLayout->getAnim(0)->initAnmFrame();
                System::getSaveData()->setDidntGotoSDMenu(FALSE);
                mpSaveDataFile = System::getSaveData()->flushAsync(System::getMem2App());
                mState = 1;
                mpSDWorker->mount_sd_async();
                mWorkerState = 1;
            }
        }

        int SDChannelSelect::getCenterChannelIndex(const char* paneName) const {
            int index = 0;
            while (index < MAX_CHANNEL_INDEX) {
                if (strcmp(paneName, mscChannelPaneNames[2][index]) == 0) {
                    break;
                }
                ++index;
            }

            return index < MAX_CHANNEL_INDEX ? index : -1;
        }

        void SDChannelSelect::initializeNormalPage() {
            if (!mpPageAnimations[0]->isPlaying() &&
                System::getSceneManager()->getScene(0x23) == NULL) {
                SDButton* button = static_cast<SDButton*>(
                    System::getSceneManager()->getScene(0x24));
                button->enableBtn();

                if (mCurrentPage > 0) {
                    button->animation(SDButton::IDANIM_ARROW_LEFT_APPEAR);
                    mbLeftArrowVisible = true;
                } else {
                    mbLeftArrowVisible = false;
                }

                if (mPageCount > 1 && mCurrentPage < mPageCount - 1) {
                    button->animation(SDButton::IDANIM_ARROW_RIGHT_APPEAR);
                    mbRightArrowVisible = true;
                } else {
                    mbRightArrowVisible = false;
                }

                button->setEventHandler(mpButtonEventHandler, NULL);
                TVRCManager::getHandle()->setEnable(TRUE);
                snd::getSystem()->startBGM("WIPL_BGM_MENU");
                clearNoticeQueue();
                updateChannelNotices(0, -1);
                updateChannelNotices(-1, -1);
                updateChannelNotices(1, -1);
                updateChannelNotices(-2, -1);
                updateChannelNotices(2, -1);
                mState = 1;
            } else {
                calcPageAnimations();
                updatePageTransform();
            }
        }

        void SDChannelSelect::processNormalInput() {
            if (mbOperationActive && System::getDialog()->callBtn1(0xc1, 0x2e)) {
                mState = 28;
            }

            SDButton* button = static_cast<SDButton*>(System::getSceneManager()->getScene(0x24));
            if (button != NULL && button->isActive()) {
                button->update();
            }

            if (mState == 1) {
                controller::Interface* controller = System::getMasterController();
                if (controller->down(0x30001000)) {
                    if (mCurrentPage > 0) {
                        setStateAndPlaySelectSound(8);
                        return;
                    }
                } else if (controller->down(0x06000010) && mCurrentPage < mPageCount - 1) {
                    setStateAndPlaySelectSound(9);
                    return;
                }

            }

            mpPaneManager->update();
        }

        void SDChannelSelect::setStateAndPlaySelectSound(int state) {
            mState = state;
            snd::getSystem()->startSE("WSD_SELECT");
        }

        void SDChannelSelect::selectChannel(int page, int index) {
            SDChannelObj* channel = findChannelObject(page, index);
            initPageAnimations(
                math::VEC3((nw4r::math::VEC3&)channel->mpBaseLayout->GetRootPane()->GetTranslate()),
                0);
            iplSDChannelObj_813E34E0(channel);

            SDButton* button = static_cast<SDButton*>(System::getSceneManager()->getScene(0x24));
            if (mbLeftArrowVisible) {
                button->animation(SDButton::IDANIM_ARROW_LEFT_DISAPPEAR);
            }
            if (mbRightArrowVisible) {
                button->animation(SDButton::IDANIM_ARROW_RIGHT_DISAPPEAR);
            }
            button->disableBtn();
            button->setEventHandler(NULL);
            mCurrentChannelIndex = index;
            mState = 5;
            snd::getSystem()->startSE("WIPL_SE_BT_PUSH");
            snd::getSystem()->stopBGM(5);
        }

        BOOL SDChannelSelect::tellStartingZoomAnm() {
            mpLayout->setMinFrame(200.0f);
            mpLayout->setMaxFrame(228.0f);
            mpLayout->setAnmType(ANIM_TYPE_FORWARD);
            mpLayout->start();
            snd::getSystem()->startSE("WIPL_SE_CH_SELECT");
            mState = 7;
            return TRUE;
        }

        void SDChannelSelect::setPageActionFrame() {
            if (mState == 8) {
                setLayoutFrame(10);
            } else {
                setLayoutFrame(11);
            }
        }

        void SDChannelSelect::setLayoutFrame(int state) {
            if (state == 10) {
                mpLayout->setMinFrame(0.0f);
                mpLayout->setMaxFrame(20.0f);
            } else {
                mpLayout->setMinFrame(40.0f);
                mpLayout->setMaxFrame(60.0f);
            }
            mpLayout->setAnmType(ANIM_TYPE_FORWARD);
            mpLayout->start();
            mState = state;
        }

        void SDChannelSelect::initPageAnimations(const math::VEC3& position, int direction) {
            nw4r::ut::Rect projection;
            System::getProjectionRect(&projection);

            math::VEC3 topLeft(projection.left, -projection.top, 0.0f);
            math::VEC3 lowerLeft(position.x - mThumbOffsetX, position.y + mThumbOffsetY, 0.0f);
            math::VEC3 topRight(projection.right, -projection.top, 0.0f);
            math::VEC3 lowerRight(position.x + mThumbOffsetX, position.y + mThumbOffsetY, 0.0f);
            math::VEC3 bottomLeft(projection.left, -projection.bottom, 0.0f);
            math::VEC3 upperLeft(position.x - mThumbOffsetX, position.y - mThumbOffsetY, 0.0f);
            math::VEC3 bottomRight(projection.right, -projection.bottom, 0.0f);
            math::VEC3 upperRight(position.x + mThumbOffsetX, position.y - mThumbOffsetY, 0.0f);

            if (direction == 0) {
                mpPageAnimations[0]->init(topLeft, lowerLeft, 28.0f, 0.0f, 0.0f,
                                          ANIM_TYPE_FORWARD, 1.0f);
                mpPageAnimations[1]->init(topRight, lowerRight, 28.0f, 0.0f, 0.0f,
                                          ANIM_TYPE_FORWARD, 1.0f);
                mpPageAnimations[2]->init(bottomLeft, upperLeft, 28.0f, 0.0f, 0.0f,
                                          ANIM_TYPE_FORWARD, 1.0f);
                mpPageAnimations[3]->init(bottomRight, upperRight, 28.0f, 0.0f, 0.0f,
                                          ANIM_TYPE_FORWARD, 1.0f);
            } else {
                mpPageAnimations[0]->init(lowerLeft, topLeft, 28.0f, 0.0f, 0.0f,
                                          ANIM_TYPE_FORWARD, 1.0f);
                mpPageAnimations[1]->init(lowerRight, topRight, 28.0f, 0.0f, 0.0f,
                                          ANIM_TYPE_FORWARD, 1.0f);
                mpPageAnimations[2]->init(upperLeft, bottomLeft, 28.0f, 0.0f, 0.0f,
                                          ANIM_TYPE_FORWARD, 1.0f);
                mpPageAnimations[3]->init(upperRight, bottomRight, 28.0f, 0.0f, 0.0f,
                                          ANIM_TYPE_FORWARD, 1.0f);
            }

            math::HermiteIntp<math::VEC3>* animation;
            int index = 0;
            do {
                animation = mpPageAnimations[index];
                animation->play();
                ++index;
            } while (index < 4);
        }

        void SDChannelSelect::setChannelScissor(const SDChannelObj* channel) const {
            nw4r::math::VEC3 position(channel->getTranslate());
            nw4r::ut::Rect projection;
            System::getProjectionRect(&projection);
            GXRenderModeObj* renderMode = System::getRenderModeObj();
            f32 scissorWidth;
            f32 scissorY;
            f32 scissorX;
            f32 scissorHeight;
            u16 framebufferWidth;
            u16 framebufferHeight;

            if (mState == 7 || mState == 12 || mState == 14) {
                nw4r::math::MTX44 matrix;
                f32 rightScale = projection.right / mScale.x;
                f32 leftScale = projection.left / mScale.x;
                f32 topScale = projection.top / mScale.y;
                f32 bottomScale = projection.bottom / mScale.y;
                f32 bottom = mPosition.y - bottomScale;
                f32 right = mPosition.x + rightScale;
                f32 left = mPosition.x + leftScale;
                f32 top = mPosition.y - topScale;
                MTXOrtho(matrix, top, bottom, left, right, -100.0f, 100.0f);

                nw4r::math::VEC4 input(position.x, position.y, 0.0f, 1.0f);
                nw4r::math::VEC4 transformed;
                nw4r::math::VEC4Transform(&transformed, &matrix, &input);
                framebufferWidth = renderMode->fbWidth;
                framebufferHeight = renderMode->efbHeight;
                scissorWidth = projection.GetWidth();
                scissorY = (framebufferHeight - ((1.0f + transformed.y) * framebufferHeight / 2)) -
                           (mThumbOffsetY * mScale.y);
                f32 widthScale = framebufferWidth / scissorWidth;
                scissorX = ((1.0f + transformed.x) * framebufferWidth / 2) -
                           ((mThumbOffsetX * mScale.x) * widthScale);
                scissorWidth = 2.0f * (mThumbOffsetX * mScale.x) *
                               (framebufferWidth / scissorWidth);
                scissorHeight = 2.0f * (mThumbOffsetY * mScale.y);
            } else {
                framebufferWidth = renderMode->fbWidth;
                framebufferHeight = renderMode->efbHeight;
                scissorX = ((f32)framebufferWidth / 2) +
                           ((position.x - mThumbOffsetX) *
                            (framebufferWidth / projection.GetWidth()));
                scissorY = (((f32)framebufferHeight / 2) - position.y) - mThumbOffsetY;
                scissorWidth = 2.0f * mThumbOffsetX *
                               (framebufferWidth / projection.GetWidth());
                scissorHeight = 2.0f * mThumbOffsetY;
            }

            scissorX -= 1.0f;
            scissorY -= 1.0f;
            scissorWidth += 2.0f;
            scissorHeight += 2.0f;

            if (scissorX >= framebufferWidth || (scissorX + scissorWidth) <= 0.0f ||
                scissorY >= framebufferHeight || (scissorY + scissorHeight) <= 0.0f) {
                GXSetScissor(0, 0, 0, 0);
            } else {
                if (scissorX < 0.0f) {
                    scissorWidth += scissorX;
                    scissorX = 0.0f;
                }
                if (scissorY < 0.0f) {
                    scissorHeight += scissorY;
                    scissorY = 0.0f;
                }
                if ((scissorX + scissorWidth) > 1705.0f) {
                    scissorWidth -= (scissorX + scissorWidth) - 1705.0f;
                }
                if ((scissorY + scissorHeight) > 1705.0f) {
                    scissorHeight -= (scissorY + scissorHeight) - 1705.0f;
                }
                GXSetScissor(scissorX, scissorY, scissorWidth, scissorHeight);
            }
        }

        void SDChannelSelect::createSceneLayouts() {
            GXTexObj widescreenTexture;

            mpStateLayout = new layout::Object(getSceneHeap(), mpLayoutFile, "arc",
                                               "mn_SdcardMenu_d.brlyt");
            mpHelpLayout = mpStateLayout->bind("mn_SdcardMenu_d.brlan");
            f32 frame = System::getRndm()->get_u16() % 2000;
            mpHelpLayout->play();
            mpStateLayout->finishBinding();
            mpHelpLayout->setCurrentFrame(frame);

            mpPageLayouts[0] = new layout::Object(getSceneHeap(), mpLayoutFile, "arc",
                                                  "my_TVMask_a.brlyt");
            mpPageLayouts[0]->bind("my_TVMask_a_Apear.brlan", "Picture_00", false, true);
            mpPageLayouts[0]->bind("my_TVMask_a_Lost.brlan", "Picture_00", false, false);
            mpPageLayouts[0]->finishBinding();
            mpPageLayouts[0]->getAnim(0)->initAnmFrame();

            mpPageLayouts[1] = new layout::Object(getSceneHeap(), mpLayoutFile, "arc",
                                                  "my_TVShade_a.brlyt");
            const char* shadeAppear = "my_TVShade_a_Apear.brlan";
            mpPageLayouts[1]->bind(shadeAppear, "4x3", true, true);
            mpPageLayouts[1]->bind("my_TVShade_a_Lost.brlan", "4x3", true, false);
            mpPageLayouts[1]->finishBinding();

            if (SCGetAspectRatio() == SC_ASPECT_RATIO_16x9) {
                mpPageLayouts[1]->FindPaneByName("16x9")
                    ->GetMaterial()->GetTexture(&widescreenTexture, GX_TEXMAP0);
                mpPageLayouts[1]->FindPaneByName("4x3")
                    ->GetMaterial()->SetTexture(GX_TEXMAP0, widescreenTexture);
                mpPageLayouts[1]->FindPaneByName("4x3_dummy")
                    ->GetMaterial()->SetTexture(GX_TEXMAP0, widescreenTexture);
            }

            mpPageLayouts[1]->getAnim(0)->initAnmFrame();

            mpPageLayouts[2] = new layout::Object(getSceneHeap(), mpLayoutFile, "arc",
                                                  "my_TVApear_a.brlyt");
            mpPageLayouts[2]->bind("my_TVApear_a_Apear.brlan", "Picture_00", false, true);
            mpPageLayouts[2]->bind("my_TVApear_a_Lost.brlan", "Picture_00", false, false);
            mpPageLayouts[2]->finishBinding();
            mpPageLayouts[2]->getAnim(0)->initAnmFrame();

            mpErrorLayout = new layout::Object(getSceneHeap(), mpLayoutFile, "arc",
                                               "my_TVMask_a.brlyt");
            mpErrorLayout->bind("my_TVMask_a_Lost.brlan", "Picture_00", false, true);
            mpErrorLayout->finishBinding();

            mpPointerLayout = new layout::Object(getSceneHeap(), mpLayoutFile, "arc",
                                                 "wait_icon.brlyt");
            mpPointerLayout->bind("wait_icon_wait_loop.brlan", "Wait_00", false, true);
            mpPointerLayout->finishBinding();
            mpPointerLayout->getAnim(0)->initAnmFrame();

            sFourPageDialogPages[2].layoutObj = mpPointerLayout;
            sThreePageDialogPages[2].layoutObj = mpPointerLayout;
        }

        BOOL SDChannelSelect::isChannelMoveTarget(int page, int index) const {
            if (page < 0 || page >= mPageCount) {
                return FALSE;
            }
            if (index < 0 || index >= MAX_CHANNEL_INDEX) {
                return FALSE;
            }
            if (page == mSourcePage && index == mSourceIndex) {
                return TRUE;
            }
            u32 titleId = mpChannelTitleIds[page * MAX_CHANNEL_INDEX + index];
            return titleId == 0;
        }

        BOOL SDChannelSelect::onEventDerived(const char* paneName, u32 event,
                                              controller::Interface* controller) {
            if (controller != NULL &&
                controller != System::getControllerManager()->getController(mControllerChannel)) {
                return TRUE;
            }

            int index = getCenterChannelIndex(paneName);
            if (index >= 0) {
                s32 eventType = event;
                if (eventType != 2) {
                    if (eventType >= 2) {
                        if (eventType == 5 && !controller->pinch()) {
                            mDestinationIndex = index;
                            mDestinationPage = mCurrentPage;
                            mbButtonEnabled = true;
                        }
                    } else if (eventType >= 1) {
                        if (isChannelMoveTarget(mCurrentPage, index) ||
                            (mCurrentPage == mSourcePage && index == mSourceIndex)) {
                            SDChannelObj* channel = findChannelObject(mCurrentPage, index);
                            iplSDChannelObj_813E3354(channel, 2);
                            snd::getSystem()->startSE("WIPL_SE_CH_TARGETTING");
                            controller->rumble(1);
                        }
                    }
                } else if (isChannelMoveTarget(mCurrentPage, index) ||
                           (mCurrentPage == mSourcePage && index == mSourceIndex)) {
                    SDChannelObj* channel = findChannelObject(mCurrentPage, index);
                    iplSDChannelObj_813E33EC(channel, 2);
                }
            }

            return TRUE;
        }

        void SDChannelSelect::startDrag(const controller::Interface* controller,
                                        int page, int index) {
            if (controller->getChannel() < 0) {
                return;
            }

            if (controller->isValidDpd()) {
                mPointerPosition = controller->getDpdPos();
            } else {
                mPointerPosition = math::VEC2(0.0f, 0.0f);
            }

            mControllerChannel = controller->getChannel();
            mSourcePage = page;
            mSourceIndex = index;
            mDestinationPage = -1;
            mDestinationIndex = -1;
            mPendingPage = -1;
            mPendingIndex = -1;
            mMoveState = 0;
            mbButtonEnabled = false;
            mbDialogActive = false;

            System::getPointer()->changeType(controller->getChannel(), 1);
            mpPageLayouts[0]->getAnim(0)->play();
            mpPageLayouts[1]->getAnim(0)->play();

            SDButton* button = static_cast<SDButton*>(System::getSceneManager()->getScene(0x24));
            button->disableBtn();

            SDChannelObj* channel = NULL;
            while (channel = static_cast<SDChannelObj*>(nw4r::ut::List_GetNext(&mChannelObjects, channel)),
                   channel != NULL) {
                int channelPage = channel->getPage();
                int channelIndex = channel->getIndex();
                bool selected = channelPage == page && channelIndex == index;
                iplSDChannelObj_813E3480(channel, selected);
            }

            snd::getSystem()->startSEwithPos("WIPL_SE_CH_HOLD", mPointerPosition.x);
            mState = 15;
        }

        void SDChannelSelect::finishDrag() {
            if (isChannelMoveTarget(mDestinationPage, mDestinationIndex) && !mbDialogActive) {
                SDChannelObj* channel = findChannelObject(mDestinationPage, mDestinationIndex);
                nw4r::math::VEC3 position = channel->getTranslate();
                mpPageLayouts[2]->GetRootPane()->SetTranslate(position);
                mpPageLayouts[2]->getAnim(0)->play();
                mpPointerLayout->GetRootPane()->SetTranslate(position);
                mpPointerLayout->calcMtx();
                mpPointerLayout->getAnim(0)->play();
                snd::getSystem()->startSEwithPos("WIPL_SE_CH_SET", mPointerPosition.x);
                mpPageLayouts[0]->getAnim(1)->play();
                mState = 19;
            } else {
                snd::getSystem()->startSEwithPos("WIPL_SE_CH_NOT_MOVE", mPointerPosition.x);
                mState = 17;
            }

            System::getPointer()->changeType(mControllerChannel, 0);
            mpPageLayouts[1]->getAnim(1)->play();

            SDButton* button = static_cast<SDButton*>(System::getSceneManager()->getScene(0x24));
            button->enableBtn();

            mbButtonEnabled = false;
            mbDialogActive = false;

            SDChannelObj* channel = NULL;
            while (channel = static_cast<SDChannelObj*>(nw4r::ut::List_GetNext(&mChannelObjects, channel)),
                   channel != NULL) {
                iplSDChannelObj_813E34E8(channel, 1);
            }

            for (int index = 0; index < MAX_CHANNEL_INDEX; ++index) {
                mpPaneManager->initPane(getChannelPane(index));
            }
        }

        void SDChannelSelect::moveDrag() {
            if (System::getControllerManager()->getController(mControllerChannel) != NULL &&
                System::getControllerManager()->getController(mControllerChannel)->isValidDpd()) {
                math::VEC2 position = System::getControllerManager()
                                          ->getController(mControllerChannel)
                                          ->getDpdProjectionPos();
                nw4r::math::VEC3 translation(position.x, -position.y, 0.0f);
                mpPageLayouts[1]->GetRootPane()->SetTranslate(translation);
                mpPageLayouts[1]->calcMtx();

                math::VEC2 delta;
                delta.y = position.y - mPointerPosition.y;
                delta.x = position.x - mPointerPosition.x;
                f32 distance = delta.x * delta.x + delta.y * delta.y;
                f32 speed = distance <= 0.0f ? 0.0f : distance * nw4r::math::FrSqrt(distance);

                snd::getSystem()->holdSEwithPosDis("WIPL_SE_CH_DRAG", position.x, speed);
                mPointerPosition = position;
            }
        }

        void SDChannelSelect::updateDragState() {
            SDButton* button = static_cast<SDButton*>(System::getSceneManager()->getScene(0x24));
            if (button != NULL && button->isActive()) {
                button->update();
            }

            mpPaneManager->update();

            if (System::getControllerManager()->getController(mControllerChannel) == NULL ||
                !System::getControllerManager()->getController(mControllerChannel)->pinch()) {
                mbButtonEnabled = true;
            }

            if (mPendingIndex >= 0) {
                ++mPendingIndex;
            }
            if (mPendingPage >= 0) {
                ++mPendingPage;
            }

            moveDrag();

            if (!mpPageLayouts[0]->getAnim(0)->isPlaying() &&
                !mpPageLayouts[1]->getAnim(0)->isPlaying()) {
                mState = 16;
            }
        }

        void SDChannelSelect::updateDragPageTransition() {
            SDButton* button = static_cast<SDButton*>(System::getSceneManager()->getScene(0x24));
            if (button != NULL && button->isActive()) {
                button->update();
            }

            mpPaneManager->update();

            if (System::getControllerManager()->getController(mControllerChannel) == NULL ||
                !System::getControllerManager()->getController(mControllerChannel)->pinch()) {
                mbButtonEnabled = true;
            }

            if (mPendingIndex >= 0) {
                ++mPendingIndex;
            }
            if (mPendingPage >= 0) {
                ++mPendingPage;
            }

            moveDrag();

            if (mbButtonEnabled || mbDialogActive) {
                finishDrag();
            } else if (mCurrentPage > 0 && mPendingIndex >= 15) {
                button->animation(7);
                mpLayout->setMinFrame(0.0f, -1);
                mpLayout->setMaxFrame(20.0f, -1);
                mpLayout->setAnmType(ANIM_TYPE_FORWARD, -1);
                mpLayout->start(-1);
                mState = 22;
                mPendingIndex = 0;
                mPendingPage = -1;

                SDChannelObj* channel = NULL;
                while (channel = static_cast<SDChannelObj*>(
                           nw4r::ut::List_GetNext(&mChannelObjects, channel)),
                       channel != NULL) {
                    iplSDChannelObj_813E34E8(channel, 1);
                }

                for (int index = 0; index < MAX_CHANNEL_INDEX; ++index) {
                    mpPaneManager->initPane(getChannelPane(index));
                }

                snd::getSystem()->startSE("WSD_SELECT");
            } else if (mCurrentPage < mPageCount - 1 && mPendingPage >= 15) {
                button->animation(8);
                mpLayout->setMinFrame(40.0f, -1);
                mpLayout->setMaxFrame(60.0f, -1);
                mpLayout->setAnmType(ANIM_TYPE_FORWARD, -1);
                mpLayout->start(-1);
                mState = 23;
                mPendingIndex = -1;
                mPendingPage = 0;

                SDChannelObj* channel = NULL;
                while (channel = static_cast<SDChannelObj*>(
                           nw4r::ut::List_GetNext(&mChannelObjects, channel)),
                       channel != NULL) {
                    iplSDChannelObj_813E34E8(channel, 1);
                }

                for (int index = 0; index < MAX_CHANNEL_INDEX; ++index) {
                    mpPaneManager->initPane(getChannelPane(index));
                }

                snd::getSystem()->startSE("WSD_SELECT");
            }
        }

        void SDChannelSelect::finishDragWait() {
            if (++mMoveState > 20) {
                mpPageLayouts[0]->getAnim(1)->play();
                mState = 18;
            }
        }

        void SDChannelSelect::finishDragPageTransition() {
            if (!mpPageLayouts[0]->getAnim(1)->isPlaying() &&
                !mpPageLayouts[1]->getAnim(1)->isPlaying()) {
                mState = 1;
            }
        }

        void SDChannelSelect::applyChannelMove() {
            if (mpPageLayouts[2]->getAnim(0)->isPlaying()) {
                return;
            }

            if (mSourcePage == mDestinationPage && mSourceIndex == mDestinationIndex) {
                mpPageLayouts[2]->getAnim(1)->play();
                mState = 21;
                return;
            }

            int sourceSlot = mSourcePage * MAX_CHANNEL_INDEX + mSourceIndex;
            int destinationSlot = mDestinationPage * MAX_CHANNEL_INDEX + mDestinationIndex;
            u32 sourceTitleId = mpChannelTitleIds[sourceSlot];
            u32 destinationTitleId = mpChannelTitleIds[destinationSlot];
            mpChannelTitleIds[sourceSlot] = destinationTitleId;
            mpChannelTitleIds[destinationSlot] = sourceTitleId;

            layout::Animator* transitionAnimator;
            if (enqueueLoadNotice()) {
                transitionAnimator = NULL;
                mbShowNoCardMessage = false;
            } else {
                transitionAnimator = mpPageLayouts[2]->getAnim(1);
                transitionAnimator->play();
                mState = 21;
            }

            mpCurrentChannel = findChannelObject(mSourcePage, mSourceIndex);
            if (mpCurrentChannel == NULL) {
                mpCurrentChannel = findChannelObject(mDestinationPage, mDestinationIndex);
                enqueueNotice(mpChannelTitleIds[destinationSlot], mDestinationPage,
                              mDestinationIndex);
            } else {
                SDChannelObj* destination = findChannelObject(mDestinationPage, mDestinationIndex);

                iplSDChannelObj_813E3178(
                    static_cast<SDChannelObj*>(mpCurrentChannel),
                    getChannelBasePane(mDestinationPage, mDestinationIndex, mCurrentPage));
                iplSDChannelObj_813E3178(
                    destination, getChannelBasePane(mSourcePage, mSourceIndex, mCurrentPage));

                static_cast<SDChannelObj*>(mpCurrentChannel)->mPage = mDestinationPage;
                static_cast<SDChannelObj*>(mpCurrentChannel)->mIndex = mDestinationIndex;
                destination->mPage = mSourcePage;
                destination->mIndex = mSourceIndex;

                iplSDChannelObj_813E322C(static_cast<SDChannelObj*>(mpCurrentChannel));
                iplSDChannelObj_813E322C(destination);

                mpCurrentChannel = transitionAnimator;
                destination->mpBaseAnimator->setCurrentFrame(mpHelpLayout->getCurrentFrame());
            }

            mState = 20;
        }

        void SDChannelSelect::finishChannelMove() {
            if (!mbShowNoCardMessage) {
                return;
            }

            if (mpCurrentChannel != NULL &&
                !isChannelReady(static_cast<SDChannelObj*>(mpCurrentChannel))) {
                return;
            }

            if (mpCurrentChannel != NULL) {
                mpCurrentChannel = NULL;
            } else if (mSourcePage != -1) {
                SDChannelObj* source = findChannelObject(mSourcePage, mSourceIndex);
                SDChannelObj* destination =
                    findChannelObject(mDestinationPage, mDestinationIndex);
                SDChannelObj* next = static_cast<SDChannelObj*>(
                    nw4r::ut::List_GetNext(&mChannelObjects, destination));
                if (next == source) {
                    next = destination;
                }

                nw4r::ut::List_Remove(&mChannelObjects, destination);
                nw4r::ut::List_Insert(&mChannelObjects, source, destination);
                nw4r::ut::List_Remove(&mChannelObjects, source);
                nw4r::ut::List_Insert(&mChannelObjects, next, source);
            }

            mpPageLayouts[2]->getAnim(1)->play();
            mState = 21;
        }

        void SDChannelSelect::resetDragPreview() {
            if (mpPageLayouts[0]->getAnim(1)->isPlaying()) {
                return;
            }
            if (mpPageLayouts[1]->getAnim(1)->isPlaying()) {
                return;
            }
            if (mpPageLayouts[2]->getAnim(1)->isPlaying()) {
                return;
            }

            f32 frame = System::getRndm()->get_u16() % 2000;
            mpHelpLayout->setCurrentFrame(frame);
            mSourcePage = -1;
            mSourceIndex = -1;
            mpPointerLayout->getAnim(0)->stop();
            mpPointerLayout->getAnim(0)->initAnmFrame();
            mState = 1;
        }

        void SDChannelSelect::finishDragPageChange() {
            SDButton* button = static_cast<SDButton*>(System::getSceneManager()->getScene(0x24));
            if (button != NULL && button->isActive()) {
                button->update();
            }

            if (System::getControllerManager()->getController(mControllerChannel) == NULL ||
                !System::getControllerManager()->getController(mControllerChannel)->pinch()) {
                mbButtonEnabled = true;
            }

            moveDrag();
            if (mpLayout->isPlaying(0)) {
                return;
            }

            button = static_cast<SDButton*>(System::getSceneManager()->getScene(0x24));
            if (mState == 22) {
                --mCurrentPage;
                if (mCurrentPage == 0) {
                    button->animation(15);
                    mbLeftArrowVisible = false;
                } else if (!mbRightArrowVisible) {
                    button->animation(14);
                    mbRightArrowVisible = true;
                }
            } else {
                ++mCurrentPage;
                if (mCurrentPage == mPageCount - 1) {
                    button->animation(16);
                    mbRightArrowVisible = false;
                } else if (!mbLeftArrowVisible) {
                    button->animation(13);
                    mbLeftArrowVisible = true;
                }
            }

            mpLayout->finishBinding();
            refreshPageObjects(mCurrentPage, NULL, -1);
            mState = 16;
        }

        void SDChannelSelectButtonEventHandler::onEventDerived(
            u32 compId, u32 event, const controller::Interface* con) {
            gui::PaneComponent* component = static_cast<gui::PaneComponent*>(
                mpManager->getComponent(compId));
            const char* paneName = component->getPane()->GetName();

            int state = mpScene->mState;
            switch (state) {
            case 15:
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 23:
                mpScene->onButtonEvent(paneName, event, con);
                return;
            default:
                break;
            }

            if (event == 0) {
                if (mpScene->mState == 1) {
                    if (System::getFader()->getStatus() == EGG::Fader::PREPARE_OUT) {
                        if (con != NULL) {
                            if (con->downTrg(0x00100800)) {
                                SDButton* button = static_cast<SDButton*>(
                                    System::getSceneManager()->getScene(0x24));
                                if (strcmp(paneName,
                                           SDButton::smButtonName[SDButton::BTN_HELP]) == 0) {
                                    mpScene->mOperationResult = 0;
                                    mpScene->mState = 26;
                                    button->animation(4);
                                    snd::getSystem()->startSE("WIPL_SE_DECIDE");
                                    return;
                                }

                                if (strcmp(paneName,
                                           SDButton::smButtonName[SDButton::BTN_WII_MENU]) == 0) {
                                    button->setEventHandler(NULL, NULL);
                                    mpScene->mState = 4;
                                    snd::getSystem()->startSE("WIPL_SE_DECIDE");
                                    return;
                                }

                                if (strcmp(paneName,
                                           SDButton::smButtonName[SDButton::BTN_ARROW_LEFT]) == 0) {
                                    if (mpScene->mCurrentPage > 0) {
                                        button->animation(7);
                                        mpScene->setStateAndPlaySelectSound(8);
                                        return;
                                    }
                                }

                                if (strcmp(paneName,
                                           SDButton::smButtonName[SDButton::BTN_ARROW_RIGHT]) == 0 &&
                                    mpScene->mCurrentPage < mpScene->mPageCount - 1) {
                                    button->animation(8);
                                    mpScene->setStateAndPlaySelectSound(9);
                                }
                            } else {
                                return;
                            }
                        } else {
                            return;
                        }
                    }
                }
            } else {
                return;
            }
        }

        void SDChannelSelectEventHandler::onEvent(u32 compId, u32 event, void* data) {
            gui::PaneComponent* component = static_cast<gui::PaneComponent*>(
                mpManager->getComponent(compId));
            const char* paneName = component->getPane()->GetName();
            controller::Interface* controller = static_cast<controller::Interface*>(data);

            BOOL handled = FALSE;
            switch (mpScene->mState) {
            case 15:
            case 16:
                handled = mpScene->onEventDerived(paneName, event, controller);
                break;
            default:
                break;
            }

        handle_channel_event:
            if (handled) {
                return;
            }

            int index = mpScene->getCenterChannelIndex(paneName);
            if (index < 0) {
                return;
            }

            SDChannelObj* channel = mpScene->findChannelObject(mpScene->mCurrentPage, index);
            if (channel == NULL) {
                return;
            }

            switch (event) {
            case ::gui::EventHandler::ON_TRIG:
                if (mpScene->mState == 1 && controller != NULL) {
                    BOOL writeProtected = mpScene->mpSDWorker->is_sd_write_protected();
                    if (controller->pinchTrg() && SDChannelSelect::isChannelReady(channel) &&
                        !mpScene->mbSDCardBroken) {
                        if (!writeProtected) {
                            mpScene->startDrag(controller, mpScene->mCurrentPage, index);
                        } else if (!mpScene->mbChannelLimitReached &&
                                   System::getDialog()->callBtn1(0xC6, 0x2E)) {
                            mpScene->mbChannelLimitReached = true;
                            mpScene->mState = 29;
                        }
                    }
                }
                break;
            case ::gui::EventHandler::ON_DRAG:
                if (mpScene->mState == 1 && controller != NULL && controller->decide() &&
                    SDChannelSelect::isChannelReady(channel)) {
                    mpScene->selectChannel(channel->getPage(), channel->getIndex());
                    TVRCManager::getHandle()->setEnable(FALSE);
                }
                break;
            case ::gui::EventHandler::ON_POINT:
                if (mpScene->mState == 1 && SDChannelSelect::isChannelReady(channel)) {
                    iplSDChannelObj_813E3354(channel, 0);
                    snd::getSystem()->startSE("WIPL_SE_CH_TARGETTING");
                    controller->rumble(1);
                }
                break;
            case ::gui::EventHandler::ON_LEFT:
                if (mpScene->mState == 1 && SDChannelSelect::isChannelReady(channel)) {
                    iplSDChannelObj_813E33EC(channel, 0);
                }
                break;
            }
        }
    }
}
