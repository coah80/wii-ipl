#define IPL_SD_CHANNEL_SELECT_CPP
#include "scene/sdButton/iplSDButton.h"
#include "scene/sdChannelSelect/iplSDChannelSelect.h"

#include <cstring>
#include <cstdlib>
#include <revolution/os.h>
#include <revolution/sc.h>
#include <revolution/mtx.h>
#include <revolution/vi.h>
#include <revolution/gx.h>
#include <revolution/mem.h>

#include "iplSound.h"
#include "iplSystem.h"
#include "iplUtility.h"
#include "utility/iplLayout.h"
#include "system/iplPointer.h"
#include "system/iplDialogWindow.h"
#include "system/iplSaveDataManager.h"
#include "system/iplChannelRsoThread.h"
#include "utility/iplCSFlags.h"

namespace ipl {
    namespace math {
        static inline nw4r::math::VEC3 subHermitePoints(const VEC3& start, const VEC3& end) {
            nw4r::math::VEC3 temp;
            nw4r::math::VEC3Sub(&temp, &start, &end);
            return temp;
        }

    }  // namespace math

    namespace scene {
        static void copyRequest(s32* dst, const s32* src) {
            dst[0] = src[0];
            s32 v2 = src[2];
            s32 v3 = src[3];
            dst[3] = v3;
            dst[2] = v2;
            dst[4] = src[4];
            dst[5] = src[5];
            dst[6] = src[6];
        }

        static const char* scChanPaneNames[5][12] = {
            {"", "", "", "N_Ch_a04", "", "", "", "N_Ch_a08", "", "", "", "N_Ch_a12"},
            {"N_Ch_b01", "N_Ch_b02", "N_Ch_b03", "N_Ch_b04", "N_Ch_b05", "N_Ch_b06",
             "N_Ch_b07", "N_Ch_b08", "N_Ch_b09", "N_Ch_b10", "N_Ch_b11", "N_Ch_b12"},
            {"N_Ch_c01", "N_Ch_c02", "N_Ch_c03", "N_Ch_c04", "N_Ch_c05", "N_Ch_c06",
             "N_Ch_c07", "N_Ch_c08", "N_Ch_c09", "N_Ch_c10", "N_Ch_c11", "N_Ch_c12"},
            {"N_Ch_d01", "N_Ch_d02", "N_Ch_d03", "N_Ch_d04", "N_Ch_d05", "N_Ch_d06",
             "N_Ch_d07", "N_Ch_d08", "N_Ch_d09", "N_Ch_d10", "N_Ch_d11", "N_Ch_d12"},
            {"N_Ch_e01", "", "", "", "N_Ch_e05", "", "", "", "N_Ch_e09", "", "", ""},
        };

        static const char* scBaseMaskPaneNames[5] = {
            "BaseMask0", "BaseMask1", "BaseMask2", "BaseMask3", "BaseMask4",
        };

        static const char* scPicturePaneNames[5] = {
            "Picture_00", "Picture_01", "Picture_02", "Picture_03", "Picture_04",
        };

        static const char* scEdgePaneNames[5] = {
            "Edge0", "Edge1", "Edge2", "Edge3", "Edge4",
        };

        static DialogWindow::Page scPages1[4] = {
            {0x9D, 0xA3, 0xA5, false, NULL, 0.0f, false},
            {0x9E, 0xA3, 0xA5, true,  NULL, 0.0f, false},
            {0x9F, 0xA3, 0xA5, true,  NULL, 74.0f, true},
            {0xCA, 0xA4, 0xA5, true,  NULL, 108.0f, false},
        };

        static DialogWindow::Page scPages2[3] = {
            {0xC9, 0xA3, 0xA5, true, NULL, 0.0f, false},
            {0x9E, 0xA3, 0xA5, true, NULL, 0.0f, false},
            {0x9F, 0xA4, 0xA5, true, NULL, 74.0f, true},
        };

        static const char* scClockPaneNames[3] = {
            "N_Clock0", "N_Clock1", "N_Clock2",
        };

        static const char* scMaskPaneName = "ChMask";


        static const f32 scChanSize[2][2] = {
            {64.0f, 48.0f},
            {85.0f, 48.0f},
        };


        // clang-format off
        extern "C" void setEventHandler__Q33ipl5scene8SDButtonFPQ23gui12EventHandlerPQ23gui12EventHandler(
            ipl::scene::SDButton* button, ::gui::EventHandler* event);
        // clang-format on


        class SDChannelSelectEvent : public ::gui::EventHandler {
        public:
            SDChannelSelectEvent(SDChannelSelect* scene) : mpScene(scene) {}

        private:
            virtual void onEvent(u32 compId, u32 event, void* data);

            SDChannelSelect* mpScene;  // 0x0C
        };

        class SDChannelSelectBtnEvent : public SDButtonEventHandlerBase {
        public:
            SDChannelSelectBtnEvent(SDChannelSelect* scene) : mpScene(scene) {}

        private:
            virtual void onEventDerived(u32 compId, u32 event, const controller::Interface* con);

            SDChannelSelect* mpScene;  // 0x0C
        };

    }  // namespace scene

    namespace math {
        template <>
        class HermiteIntp<VEC3> : public Interporation<VEC3> {
        public:
            HermiteIntp() {}
            virtual ~HermiteIntp() {}

            void init(const VEC3& start, const VEC3& end, f32 maxFrame, f32 param_5, f32 param_6, int playback = ANIM_TYPE_FORWARD,
                      f32 speed = 1.0f);

            VEC3 get() const {
                f32 var_f27 = mFrame;
                f32 var_f28 = 1.0f / mMaxFrame;
                nw4r::math::VEC3 r;
                nw4r::math::VEC3Add(&r,
                                    &(mStart * (1.0f + ((var_f28 * (var_f28 * (var_f28 * (var_f27 * (2.0f * var_f27 * var_f27))))) -
                                                        (var_f28 * (var_f28 * (3.0f * var_f27 * var_f27)))))),
                                    &(mEnd * ((var_f28 * (var_f28 * (var_f28 * (var_f27 * (2.0f * var_f27 * var_f27))))) -
                                              (var_f28 * (var_f28 * (3.0f * var_f27 * var_f27))))));
                VEC3 out(r);
                f32 tan =
                    unkVal0 * (var_f27 +
                               (var_f28 * (var_f27 * (var_f27 * (var_f27 * var_f27))) -
                                var_f28 * (2.0f * var_f27 * var_f27))) +
                    unkVal1 * (var_f28 * (var_f28 * (var_f27 * (var_f27 * var_f27))) -
                               var_f28 * (var_f27 * var_f27));
                out.x += tan;
                out.y += tan;
                out.z += tan;
                return out;
            }

        protected:
            f32 unkVal0;
            f32 unkVal1;
        };
    }  // namespace math

    namespace scene {

        SDChannelSelect::SDChannelSelect(EGG::Heap* heap)
            : FaderSceneBase(heap) {
            mpEvent = new SDChannelSelectBtnEvent(this);
            mState = 0;

            mChanSizeX = scChanSize[SCGetAspectRatio()][0];
            mChanSizeY = scChanSize[SCGetAspectRatio()][1];

            mCmdQueue.mCap = 4;
            mCmdQueue.mCount = 0;
            mCmdQueue.mRead = 0;
            mCmdQueue.mWrite = 0;
            mChanQueue.mCap = 0x2A;
            mChanQueue.mCount = 0;
            mChanQueue.mRead = 0;
            mChanQueue.mWrite = 0;
            mSelState = 0;
            unk_0x704 = 0;
            mMountFlag = 0;
            mAsyncFlag = 1;
            mpWorkBuf1 = NULL;
            mpWorkBuf2 = NULL;
            mpWorker = NULL;
            mpBuf71C = NULL;
            mpBuf720 = NULL;
            mpBuf724 = NULL;
            mpPendingChan = NULL;
            mpChanTable = NULL;
            mResetState = 0xE;
            unk_0x754 = 0;
            mFlag758 = 0;
            mFlag759 = 0;
            mFlag75A = 0;
            unk_0x75C = 0;
            mReqType = 0;
            mpReqFile = NULL;
            unk_0x768 = 0;
            mReqParam = 0;
            unk_0x77C = 0;
            unk_0x77D = 0;
            unk_0x77E = 0;
            unk_0x77F = 0;
            mChanCount = 0x14;
            mChanPage = System::getSaveData()->mLastSDPrevPage;
            mChanIndex = 0;
            if (mChanPage == 0) {
                mbFlagC8 = 0;
            } else {
                mbFlagC8 = 1;
            }
            if (mChanPage == mChanCount - 1) {
                mbFlagC9 = 0;
            } else {
                mbFlagC9 = 1;
            }

            setSceneParentFlags(SCN_PARENTFLAG_DRAW | SCN_PARENTFLAG_CALC);

            math::VEC3 vec(0.0f, 0.0f, 0.0f);
            mVec = vec;
            math::VEC2 vec2(1.0f, 1.0f);
            mVec2 = vec2;

            nw4r::ut::Rect rect43;
            System::getProjectionRect4x3(&rect43);
            nw4r::ut::Rect rect169;
            System::getProjectionRect16x9(&rect169);
            f32 w43 = rect43.right - rect43.left;
            f32 w169 = rect169.right - rect169.left;
            f32 scale = w169 / w43;
            if (SCGetAspectRatio() == SC_ASPECT_RATIO_16x9) {
            } else {
                scale = 1.0f;
            }
            mAspectScale = scale;

            memset(&mCursorPos, 0, 0x30);

            mpObjHeap = EGG::ExpHeap::create(0x13610, heap, MEM_HEAP_OPT_DEBUG_FILL | MEM_HEAP_OPT_THREAD_SAFE);
            mpWorkHeap = EGG::UnitHeap::create(EGG::UnitHeap::calcHeapSize(0x212B8, 0x2D, 0x20), 0x212B8,
                                             System::getMem2App(), 0x20, 2);

            nw4r::ut::List_Init(&mChanList, 0);

            iplSDChannelSelect_813DF834(mChanPage, 1);

            TVRCManager::getHandle()->setEnable(1);

            mpChanTable = new (System::getMem2App(), 0x20) s32[mChanCount * 12];
            memset(mpChanTable, 0, mChanCount * 0x30);
            mpBuf720 = new (System::getMem2App(), 0x20) u8[0x4B00];
            memset(mpBuf720, 0, 0x4B00);
            mpBuf71C = new (System::getMem2App(), 0x20) u8[0x2580];
            memset(mpBuf71C, 0, 0x2580);
            mpBuf724 = new (System::getMem2App(), 0x20) u8[0x600];
            memset(mpBuf724, 0, 0x600);

            unk_0x728 = 0;
            unk_0x72C = 0;
            mSelPage = -1;
            mSelIndex = -1;
        }

        SDChannelSelect::~SDChannelSelect() {
        }

        void SDChannelSelect::prepare() {
            System::getBS2Manager()->abort();

            mpChanLayoutFile = System::getNandManager()->readLayoutAsync(getSceneHeap(), "sdChanSel.ash", false);
            mpThumbData = System::getNandManager()->readAsync(getSceneHeap(), "corrupt_icon.ash", 0, 0, false);

            SDChannelObj* chanObj = NULL;
            while ((chanObj = (SDChannelObj*)nw4r::ut::List_GetNext(&mChanList, chanObj)) != NULL) {
                chanObj->prepare();
            }
        }

        void SDChannelSelect::create() {
            mpWorker = new (System::getMem2App(), 4) NandSDWorker();

            mpWorkBuf1 = System::getMem2App()->alloc(0x3EA60, 0x40);
            u32 heapSize = MEMCalcHeapSizeForUnitHeap(0x19620, 0x60, 0x20) + 0x40000;
            mpWorkBuf2 = System::getMem2App()->alloc(heapSize, 0x40);
            mpWorker->create(mpWorkBuf1, NULL, mpWorkBuf2, 0x12);

            if (System::getSaveData()->mData.didntGotoSDMenu == 0) {
                mpWorker->mount_sd_async();
                mMountFlag = 1;
            }

            mpHeap1 = EGG::ExpHeap::create(0x21100, getSceneHeap(), MEM_HEAP_OPT_DEBUG_FILL | MEM_HEAP_OPT_THREAD_SAFE);
            mpHeap2 = EGG::ExpHeap::create(0x2C100, getSceneHeap(), MEM_HEAP_OPT_DEBUG_FILL | MEM_HEAP_OPT_THREAD_SAFE);
            mpCsHeap = EGG::ExpHeap::create(System::getChannelArena(), 0x200000, 0);

            mpRsoThread = new (System::getMem2App(), 32) channel::RsoThread(mpCsHeap);

            createBaseLayout();

            if (mChanPage < mChanCount - 1) {
                iplSDChannelSelect_813DF834(mChanPage + 1, 0);
            }
            if (0 < mChanPage) {
                iplSDChannelSelect_813DF834(mChanPage - 1, 0);
            }

            updateChannelObjects();
            iplSDChannelSelect_813E11C4();

            u32 bs2AbortStart = OSGetTick();
            while (System::getBS2Manager()->getIPLState() != bs2::IPL_STATE_8) {
                System::getBS2Manager()->update();
                OSReport(" ... wait for bs2 abord\n");
                VIWaitForRetrace();
            }
            OSReport("*** BS2 abort costs: %dms\n", OSTicksToMilliseconds(OSGetTick() - bs2AbortStart));

            System::getFader()->fadeIn();
            mState = 2;

            utility::CSFlags::UpdateFlagsFile();
        }

        void SDChannelSelect::enqueueStartNotice() {
            SDChannelSelectCommand cmd;
            cmd.type = 1;
            cmd.arguments.values[0] = 0;
            cmd.arguments.values[1] = 0;
            cmd.titleId = 0;
            mCmdQueue.push(cmd);
        }

        BOOL SDChannelSelect::enqueueFinishNotice() {
            SDChannelSelectCommand cmd;
            cmd.type = 2;
            cmd.arguments.values[0] = 0;
            cmd.arguments.values[1] = 0;
            cmd.titleId = 0;
            mCmdQueue.push(cmd);
            return TRUE;
        }

        BOOL SDChannelSelect::enqueueNotice(u32 titleId, u32 arg1, u32 arg2) {
            if (mSelState != 6) {
                return FALSE;
            }
            {
                SDChannelSelectCommand cmd;
                cmd.type = 4;
                cmd.arguments.values[0] = arg1;
                cmd.arguments.values[1] = arg2;
                cmd.titleId = titleId;
                mChanQueue.push(cmd);
                return TRUE;
            }
        }

        BOOL SDChannelSelect::enqueueLoadNotice() {
            if (mSelState != 6) {
                return FALSE;
            }
            SDChannelSelectCommand cmd;
            cmd.type = 8;
            cmd.arguments.values[0] = 0;
            cmd.arguments.values[1] = 0;
            cmd.titleId = 0;
            mCmdQueue.push(cmd);
            return TRUE;
        }

        BOOL SDChannelSelect::enqueuePageNotice() {
            if (mSelState != 6) {
                return FALSE;
            }
            SDChannelSelectCommand cmd;
            cmd.type = 9;
            cmd.arguments.values[0] = 0;
            cmd.arguments.values[1] = 0;
            cmd.titleId = 0;
            mCmdQueue.push(cmd);
            return TRUE;
        }

        BOOL SDChannelSelect::enqueueResultNotice(u32 titleId) {
            if (mSelState != 6) {
                return FALSE;
            }
            SDChannelSelectCommand cmd;
            cmd.titleId = titleId;
            cmd.type = 5;
            cmd.arguments.values[0] = 0;
            cmd.arguments.values[1] = 0;
            mCmdQueue.push(cmd);
            return TRUE;
        }

        BOOL SDChannelSelect::enqueueChannelNotice(u32 channel, u32 highTitleId, u32 lowTitleId, u32 freeOut) {
            if (mSelState != 6) {
                return FALSE;
            }
            SDChannelSelectCommand cmd;
            cmd.type = 0xA;
            cmd.arguments.values[0] = freeOut;
            cmd.arguments.values[1] = (u32)&unk_0x728;
            cmd.titleId = (((u64)highTitleId) << 32) | lowTitleId;
            mCmdQueue.push(cmd);
            return TRUE;
        }

        BOOL SDChannelSelect::enqueueMoveNotice(u32 channel, u32 highTitleId, u32 lowTitleId) {
            if (mSelState != 6) {
                return FALSE;
            }
            SDChannelSelectCommand cmd;
            cmd.type = 6;
            cmd.arguments.values[0] = 0;
            cmd.arguments.values[1] = 0;
            cmd.titleId = (((u64)highTitleId) << 32) | lowTitleId;
            mCmdQueue.push(cmd);
            return TRUE;
        }

        BOOL SDChannelSelect::enqueueStateNotice(u32 channel, u32 highTitleId, u32 lowTitleId, u32 state) {
            if (mSelState != 6) {
                return FALSE;
            }
            SDChannelSelectCommand cmd;
            cmd.type = 7;
            cmd.arguments.values[0] = state;
            cmd.arguments.values[1] = 0;
            cmd.titleId = (((u64)highTitleId) << 32) | lowTitleId;
            mCmdQueue.push(cmd);
            return TRUE;
        }

        BOOL SDChannelSelect::enqueueErrorNotice(u32 arg1, u32 arg2) {
            if (mSelState != 6) {
                return FALSE;
            }
            SDChannelSelectCommand cmd;
            cmd.type = 0xB;
            cmd.arguments.values[0] = arg1;
            cmd.arguments.values[1] = arg2;
            cmd.titleId = 0;
            mCmdQueue.push(cmd);
            return TRUE;
        }

        BOOL SDChannelSelect::enqueueCommandNotice(u32 arg1, u32 arg2, u32 arg3) {
            if (mSelState != 6) {
                return FALSE;
            }
            SDChannelSelectCommand cmd;
            cmd.type = 0xC;
            cmd.arguments.values[0] = arg1;
            cmd.arguments.values[1] = arg2;
            cmd.arguments.values[2] = arg3;
            cmd.titleId = 0;
            mCmdQueue.push(cmd);
            return TRUE;
        }

        BOOL SDChannelSelect::enqueueDeleteNotice(u32 channel, u32 highTitleId, u32 lowTitleId) {
            if (mSelState != 6) {
                return FALSE;
            }
            SDChannelSelectCommand cmd;
            cmd.type = 0xD;
            cmd.arguments.values[0] = 0;
            cmd.arguments.values[1] = 0;
            cmd.arguments.values[2] = 0;
            cmd.titleId = (((u64)highTitleId) << 32) | lowTitleId;
            mCmdQueue.push(cmd);
            return TRUE;
        }

        void SDChannelSelect::processWorkerCommands() {
            switch (mSelState) {
            case 1:
            case 3:
            case 4:
                unk_0x77E = 0;
            case 2:
                clearCommandQueue();
                clearNoticeQueue();
                break;
            }

            switch (mState) {
            case 0x0:
            case 0x2:
            case 0x3:
            case 0x4:
            case 0x5:
            case 0x6:
            case 0x7:
            case 0xC:
            case 0xD:
            case 0xE:
                goto skipReset;
            }

            {
                if (mSelState < 5) {
                if (mSelState >= 1) {
                    if (mReqType != 0) {
                        return;
                    }
                    mSelPage = -1;
                    mSelIndex = -1;
                    mFlag758 = 1;
                    iplSDChannelSelect_813DFAC0();
                    memset(mpChanTable, 0, mChanCount * 0x30);
                    memset(mpBuf720, 0, 0x4B00);
                    unk_0x734 = 0;
                    mFlag759 = 0;
                    unk_0x77C = 0;
                    unk_0x77D = 0;
                    mFlag75A = 0;
                    unk_0x77F = 0;
                    switch (mSelState) {
                    case 1:
                        setDialogMessage(2, 0xA9);
                        mAsyncFlag = 6;
                        break;
                    case 2:
                        if (unk_0x77E == 0) {
                            setDialogMessage(8, 0xAA);
                        }
                        unk_0x77E = 1;
                        enqueueStartNotice();
                        enqueueFinishNotice();
                        break;
                    case 3:
                    case 4:
                        setDialogMessage(2, 0xAB);
                        mAsyncFlag = 0xF;
                        break;
                    }
                }
                }
            }
        skipReset:

            if (mpWorker->is_working() == 0 && mMountFlag == 4) {
                if (mCmdQueue.mCount != 0) {
                    SDChannelSelectCommand cmd = mCmdQueue.mEntries[mCmdQueue.mRead];
                    switch (cmd.type) {
                    case 1:
                        mpWorker->mount_sd_async();
                        mAsyncFlag = 0;
                        unk_0x77E = 0;
                        break;
                    case 2:
                        unk_0x734 = mpWorker->get_sd_app_num();
                        mpWorker->list_sd_app_async((u32*)mpBuf71C);
                        mAsyncFlag = 2;
                        break;
                    case 8:
                        mpWorker->update_sd_app_location_async((u32*)mpChanTable);
                        mAsyncFlag = 4;
                        break;
                    case 9:
                        mpWorker->read_sd_app_location_async((u32*)mpChanTable);
                        mAsyncFlag = 5;
                        break;
                    case 5:
                        mpWorker->copy_sd_app_to_nand_async((u32)cmd.titleId, 1);
                        mAsyncFlag = 7;
                        break;
                    case 10:
                        mpWorker->check_for_sd_app_to_nand_async(
                            cmd.titleId, (NandSDWorker::AppBlocksInfo*)cmd.arguments.values[0],
                            (NandSDWorker::AppBlocksInfo*)cmd.arguments.values[1]);
                        mAsyncFlag = 8;
                        break;
                    case 6:
                        mpWorker->copy_nand_app_to_sd_async(cmd.titleId);
                        mAsyncFlag = 9;
                        break;
                    case 7: {
                        struct SDBufRec { u64 titleId; u64 extra; };
                        u64 titleId = cmd.titleId;
                        mpWorker->delete_nand_app_async(titleId, cmd.arguments.values[0] != 0);
                        mAsyncFlag = 10;
                        u32 i;
                        for (i = 0; i < (u32)unk_0x738; i++) {
                            if (((SDBufRec*)mpBuf724)[i].titleId == titleId) {
                                break;
                            }
                        }
                        if (i < (u32)unk_0x738) {
                            for (; i < (u32)unk_0x738 - 1; i++) {
                                ((SDBufRec*)mpBuf724)[i] = ((SDBufRec*)mpBuf724)[i + 1];
                            }
                            unk_0x738--;
                        }
                        break;
                    }
                    case 0xB:
                        mpWorker->check_backup_fits_async(
                            (NandSDWorker::TitleIdList*)cmd.arguments.values[0],
                            (NandSDWorker::TitleIdList*)cmd.arguments.values[1]);
                        mAsyncFlag = 0xB;
                        break;
                    case 0xC:
                        mpWorker->iplNandSD_81348EA8((void*)cmd.arguments.values[0], (void*)cmd.arguments.values[1], (void*)cmd.arguments.values[2]);
                        mAsyncFlag = 0xC;
                        break;
                    case 0xD:
                        mpWorker->delete_sd_app_async((u32)cmd.titleId);
                        mAsyncFlag = 0xD;
                        break;
                    }
                    mResetState = cmd.type;
                    mCmdQueue.pop();
                } else if (mChanQueue.mCount != 0) {
                    SDChannelSelectCommand entry = mChanQueue.mEntries[mChanQueue.mRead];
                    SDChannelObj* chanObj = getChanObj(entry.arguments.values[0], entry.arguments.values[1]);
                    if (chanObj != NULL && (u32)(chanObj->mChanType - 1) <= 1) {
                        EGG::Heap* heap = EGG::FrmHeap::create(0x212B8, mpWorkHeap, 2);
                        SDChannelObj* newChan = new (mpObjHeap, 4) SDChannelObj(heap, entry.arguments.values[0], entry.arguments.values[1]);
                        mpPendingChan = newChan;
                        u8* thumb = (u8*)newChan->allocThumbBuffer();
                        mpWorker->get_sd_app_meta_async((u32)entry.titleId, thumb,
                            (NandSDWorker::SDAppMetaEntry*)&newChan->mTitleID);
                        mAsyncFlag = 3;
                    }
                    mChanQueue.pop();
                }
            }
        }

        void SDChannelSelect::handleWorkerStartup() {
            if (mpWorker->is_working() == 0) {
                if (mpWorker->get_async_result() == 0) {
                    if (unk_0x75C == 0) {
                        setDialogMessage(8, 0xAA);
                    }
                    enqueueFinishNotice();
                    mAsyncFlag = 1;
                }
                mpWorker->startup_async();
                mMountFlag = 2;
            } else if (unk_0x704 != mSelState && mSelState == 7) {
                setDialogMessage(8, 0xAA);
            }
        }

        void SDChannelSelect::handleNandTitleCount() {
            if (mpWorker->is_working() == 0) {
                if (mpWorker->get_async_result() == -5) {
                    System::getErrorHandler()->set(ErrorHandler::DEFAULT, 1, NULL, 0, -1);
                } else {
                    u32 num = mpWorker->get_nand_app_num();
                    unk_0x738 = num;
                    if (num > 0x60) {
                        unk_0x738 = 0x60;
                    }
                    if (unk_0x738 != 0) {
                        mpWorker->list_nand_apps_usage_async(mpBuf724, (void*)unk_0x738);
                        mMountFlag = 3;
                    } else {
                        mMountFlag = 4;
                    }
                }
            }
        }

        void SDChannelSelect::clearCommandQueue() {
            while (mCmdQueue.getCount() > 0) {
                mCmdQueue.pop();
            }
        }

        void SDChannelSelect::clearNoticeQueue() {
            while (mChanQueue.getCount() > 0) {
                mChanQueue.pop();
            }
        }

        void SDChannelSelect::handleNandTitleUsageComplete() {
            if (!mpWorker->is_working()) {
                mResetState = 0xE;
                mAsyncFlag = 1;
            }
        }

        struct ChanSortEntry8 {
            u32 unk_0x00;
            u32 unk_0x04;
            int mKey;  // 0x08
            int unk_0x0C;
        };


        void SDChannelSelect::handleNandTitleUsage() {
            if (mpWorker->is_working() == 0) {
                if (mpWorker->get_async_result() == 0) {
                    qsort(mpBuf724, unk_0x738, 0x10, compareTitleUsage);
                    int off = 0;
                    for (u32 i = 0; i < unk_0x738; i++) {
                        int* e = (int*)((char*)mpBuf724 + off);
                        e[2] -= 0x4000;
                        e = (int*)((char*)mpBuf724 + off);
                        off += 0x10;
                        e[3] -= 1;
                    }
                    mMountFlag = 4;
                } else {
                    System::getErrorHandler()->set(ErrorHandler::DEFAULT, 2, NULL, 0, -1);
                }
            }
        }

        int SDChannelSelect::compareTitleUsage(const void* pa, const void* pb) {
            const ChanSortEntry8* a = (const ChanSortEntry8*)pa;
            const ChanSortEntry8* b = (const ChanSortEntry8*)pb;
            if (a->mKey < b->mKey) {
                return -1;
            }
            return a->mKey != b->mKey;
        }

        struct ChanSortEntry0 {
            u32 mKey;  // 0x00
        };

        void SDChannelSelect::handleSDTitleList() {
            if (mpWorker->is_working() == 0) {
                mResetState = 0xE;
                if (unk_0x734 == 0) {
                    if (mReqType == 0) {
                        setDialogMessage(1, 0);
                        mAsyncFlag = 0xF;
                    }
                } else {
                    if (mpWorker->get_async_result() == 0) {
                        int off1 = 0;
                        int off2 = 0;
                        for (u32 i = 0; i < unk_0x734; i++) {
                            *(u32*)((char*)mpBuf720 + off1) = *(u32*)((char*)mpBuf71C + off2);
                            if (*(int*)((char*)mpBuf71C + off2) == 0x48415A41) {
                                unk_0x77C = 1;
                            }
                            off1 += 8;
                            off2 += 4;
                        }
                        qsort(mpBuf720, unk_0x734, 8, compareTitleInfo);
                        enqueuePageNotice();
                        mAsyncFlag = 1;
                    } else if (mReqType == 0) {
                        setDialogMessage(2, 0xC3);
                        mAsyncFlag = 0xF;
                    }
                }
            }
        }

        int SDChannelSelect::compareTitleInfo(const void* pa, const void* pb) {
            const ChanSortEntry0* a = (const ChanSortEntry0*)pa;
            const ChanSortEntry0* b = (const ChanSortEntry0*)pb;
            if (a->mKey < b->mKey) {
                return -1;
            }
            return a->mKey != b->mKey;
        }

        struct SDRec8 {
            u32 key;   // 0x00
            u8 used;   // 0x04
            u8 pad_5[3];
        };

        void SDChannelSelect::iplSDChannelSelect_813DBFE0() {
            if (mpWorker->is_working() == 0) {
                mResetState = 0xE;
                if (mReqType == 0) {
                    if (OSGetTime() - mLastTime >= OSSecondsToTicks(1)) {
                        setDialogMessage(1, 0);
                        int result = mpWorker->get_async_result();
                        if (result == 0 || result == -0x11) {
                            for (int i = 0; i < mChanCount * 0xC; i++) {
                                if (mpChanTable[i] != 0) {
                                    SDRec8* found = (SDRec8*)bsearch(&mpChanTable[i], mpBuf720, unk_0x734, 8,
                                        compareTitleInfo);
                                    if (found != NULL) {
                                        found->used = 1;
                                    } else {
                                        mpChanTable[i] = 0;
                                    }
                                }
                            }
                            u32 src = 0;
                            bool found9 = false;
                            for (int i = 0; i < mChanCount * 0xC; i++) {
                                if (mpChanTable[i] == 0) {
                                    u32 count = unk_0x734;
                                    if (src == count) {
                                        break;
                                    }
                                    for (; src < count; src++) {
                                        SDRec8* rec = (SDRec8*)mpBuf720 + src;
                                        if (rec->used == 0 && rec->key != 0x48415A41) {
                                            mpChanTable[i] = rec->key;
                                            found9 = true;
                                            src++;
                                            break;
                                        }
                                    }
                                }
                            }
                            if (found9 || result == -0x11) {
                                enqueueLoadNotice();
                            }
                        } else {
                            int cnt = 0;
                            for (u32 i = 0; i < unk_0x734; i++) {
                                SDRec8* rec = (SDRec8*)mpBuf720 + i;
                                u32 v = rec->key;
                                if (v != 0x48415A41) {
                                    mpChanTable[cnt] = v;
                                    cnt++;
                                    if (cnt == mChanCount * 0xC) {
                                        break;
                                    }
                                }
                            }
                            enqueueLoadNotice();
                        }
                        mAsyncFlag = 1;
                        unk_0x77F = 1;
                        u32 v1;
                        if (unk_0x77C == 0) {
                            v1 = unk_0x734;
                        } else {
                            v1 = unk_0x734 - 1;
                        }
                        if (mChanCount * 0xC < v1) {
                            mFlag759 = 1;
                        }
                        if (mChanCount * 0xC <= v1) {
                            mFlag75A = 1;
                        }
                        iplSDChannelSelect_813DFBBC();
                    }
                }
            }
        }

        void SDChannelSelect::handleSDMountComplete() {
            if (!mpWorker->is_working()) {
                mResetState = 0xE;
                if (mpWorker->get_async_result() == -7) {
                    mFlag75A = 1;
                }
                mFlag758 = 1;
                mAsyncFlag = 1;
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813DC2F0() {
            if (mpWorker->is_working() == 0) {
                mResetState = 0xE;
                int index = mpPendingChan->mChanIndex;
                int page = mpPendingChan->mChanPage;
                if (isChannelInCalc(page, index, mChanPage) == 0 || (u32)(mSelState - 1) <= 1) {
                    destroyChannelObject(mpPendingChan);
                    mAsyncFlag = 1;
                    mpPendingChan = NULL;
                } else {
                    if (mpWorker->get_async_result() >= 0) {
                        SDChannelObj* p = mpPendingChan;
                        p->mChanType = 0;
                        p->mState = 2;
                        DCFlushRange(mpPendingChan->allocThumbBuffer(), 0x19000);
                    } else {
                        nand::File* thumb = mpThumbData;
                        memcpy(mpPendingChan->allocThumbBuffer(), thumb->getBuffer(), thumb->getLength());
                        memset((char*)mpPendingChan + 0x90, 0, 0x608);
                        SDChannelObj* p = mpPendingChan;
                        p->mChanType = 3;
                        p->mState = 2;
                    }
                    SDChannelObj* old = getChanObj(page, index);
                    if (old != NULL) {
                        nw4r::ut::List_Insert(&mChanList, old, mpPendingChan);
                        nw4r::ut::List_Remove(&mChanList, old);
                        destroyChannelObject(old);
                    } else {
                        nw4r::ut::List_Append(&mChanList, mpPendingChan);
                    }
                    updateChannelObject(mpPendingChan);
                    if (mChanPage == page) {
                        mpGui->initPane(getChannelPane(index));
                    }
                    mAsyncFlag = 1;
                    mpPendingChan = NULL;
                }
            }
        }

        void SDChannelSelect::handleSDCardReady() {
            if (mpWorker->get_sd_state() == 2 && mReqType == 0) {
                setDialogMessage(1, 0);
                mAsyncFlag = 1;
            }
        }

        void SDChannelSelect::handleCardCommand() {
            if (mReqType == 0) {
                if (mpWorker->get_sd_state() == 1) {
                    setDialogMessage(2, 0xA9);
                    mAsyncFlag = 6;
                } else if (mpWorker->get_sd_state() == 2) {
                    mAsyncFlag = 1;
                }
            }
        }

        void SDChannelSelect::handleCopyComplete() {
            if (mpWorker->is_working() == 0) {
                mResetState = 0xE;
                if (mpWorker->get_async_result() == -5) {
                    System::getErrorHandler()->set(ErrorHandler::DEFAULT, 1, NULL, 0, -1);
                } else {
                    mAsyncFlag = 1;
                }
            }
        }

        void SDChannelSelect::handleSDLocationUpdateComplete() {
            if (!mpWorker->is_working()) {
                mResetState = 0xE;
                mAsyncFlag = 1;
            }
        }

        void SDChannelSelect::handleSDLocationReadComplete() {
            if (!mpWorker->is_working()) {
                mResetState = 0xE;
                mAsyncFlag = 1;
            }
        }

        void SDChannelSelect::handleMoveComplete() {
            if (mpWorker->is_working() == 0) {
                mResetState = 0xE;
                if (mpWorker->get_async_result() == -5) {
                    System::getErrorHandler()->set(ErrorHandler::DEFAULT, 1, NULL, 0, -1);
                } else {
                    System::getChannelManager()->reserveRefresh();
                    mAsyncFlag = 1;
                }
            }
        }

        void SDChannelSelect::handleBackupFitComplete() {
            if (!mpWorker->is_working()) {
                mResetState = 0xE;
                mAsyncFlag = 1;
            }
        }

        void SDChannelSelect::handleNandSDCleanupComplete() {
            if (!mpWorker->is_working()) {
                mResetState = 0xE;
                mAsyncFlag = 1;
            }
        }

        void SDChannelSelect::handleSDDeleteComplete() {
            if (!mpWorker->is_working()) {
                mResetState = 0xE;
                mAsyncFlag = 1;
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813DC7EC(int dir, int focusedIndex) {
            const int targetPage = mChanPage + dir;
            if (targetPage < 0) {
                return;
            }
            if (mpChanTable != NULL) {
                int start;
                int step;
                switch (dir) {
                case -2:
                    start = 3;
                    step = 4;
                    break;
                case 2:
                    start = 0;
                    step = 4;
                    break;
                default:
                    start = 0;
                    step = 1;
                }
                const int rowBase = targetPage * 0xC;
                if (focusedIndex >= 0 && focusedIndex < 0xC) {
                    SDChannelObj* chanObj = getChanObj(targetPage, focusedIndex);
                    const int tIdx = rowBase + focusedIndex;
                    if (
                        chanObj != NULL &&
                        chanObj->mChanType == 2 &&
                        mpChanTable[tIdx] != 0
                    ) {
                        enqueueNotice(
                            mpChanTable[tIdx],
                            targetPage,
                            focusedIndex);
                    }
                }
                for (int i = start; i < 0xC; i += step) {
                    if (focusedIndex != i) {
                        SDChannelObj* chanObj = getChanObj(targetPage, i);
                        const int tIdx = rowBase + i;
                        if (
                            chanObj != NULL &&
                            chanObj->mChanType == 2 &&
                            mpChanTable[tIdx] != 0
                        ) {
                            enqueueNotice(
                                mpChanTable[tIdx],
                                targetPage,
                                i);
                        }
                    }
                }
            }
        }


        void SDChannelSelect::processWorkerState() {
            unk_0x704 = mSelState;
            mSelState = mpWorker->get_sd_state();
            switch (mMountFlag) {
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
            switch (mAsyncFlag) {
            case 1:
                processWorkerCommands();
                break;
            case 0:
                handleNandTitleUsageComplete();
                break;
            case 2:
                handleSDTitleList();
                break;
            case 4:
                handleSDMountComplete();
                break;
            case 5:
                iplSDChannelSelect_813DBFE0();
                break;
            case 3:
                iplSDChannelSelect_813DC2F0();
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
            case 0xb:
                handleBackupFitComplete();
                break;
            case 0xc:
                handleNandSDCleanupComplete();
                break;
            case 0xd:
                handleSDDeleteComplete();
                break;
            case 6:
                handleSDCardReady();
                break;
            case 0xf:
                handleCardCommand();
                break;
            }
            if (mSelState != 6 && mState < 0x18 && mState > 0xE) {
                unk_0x105 = 1;
            }
            updateDialogAnimation();
        }

        void SDChannelSelect::updateDialogAnimation() {
            if (!mpTimerAnim->isPlaying(-1) || mpTimerAnim->isPlaying(4)) {
                switch (unk_0x75C) {
                case 3:
                    unk_0x75C = 4;
                    mLastTime = OSGetTime();
                    break;
                case 6:
                    unk_0x75C = 7;
                    break;
                case 9:
                    unk_0x75C = 10;
                    mLastTime = OSGetTime();
                    break;
                case 0xc:
                    unk_0x75C = 0xd;
                    break;
                }
                if (mReqType == 0) {
                    switch (unk_0x75C) {
                        case 7:
                            unk_0x75C = 8;
                            break;
                        case 0xA:
                            unk_0x75C = 0xE;
                            break;
                    }
                } else switch (mReqType) {
                case 2:
                    switch (unk_0x75C) {
                    case 0:
                    case 1:
                    case 7:
                    case 0xd:
                        unk_0x75C = 2;
                        unk_0x768 = mReqParam;
                        break;
                    case 2:
                        if (unk_0x768 != mReqParam) {
                            unk_0x768 = mReqParam;
                        }
                        mReqType = 0;
                        break;
                    case 4:
                        if (unk_0x768 == mReqParam) {
                            mReqType = 0;
                        } else {
                            unk_0x75C = 5;
                        }
                        break;
                    case 10:
                    case 0xe:
                    case 0xf:
                        unk_0x75C = 0xb;
                        break;
                    }
                case 8:
                    switch (unk_0x75C) {
                    case 0:
                    case 1:
                    case 7:
                    case 0xd:
                        unk_0x75C = 8;
                        unk_0x768 = mReqParam;
                        break;
                    case 8:
                        if (unk_0x768 != mReqParam) {
                            unk_0x768 = mReqParam;
                        }
                        mReqType = 0;
                        break;
                    case 10:
                    case 0xe:
                    case 0xf:
                        if (unk_0x768 == mReqParam) {
                            mReqType = 0;
                        } else {
                            unk_0x75C = 0xb;
                        }
                        break;
                    case 4:
                        unk_0x75C = 5;
                        break;
                    }
                case 1:
                    switch (unk_0x75C) {
                    case 0:
                    case 1:
                    case 2:
                    case 7:
                    case 8:
                    case 0xd:
                        unk_0x75C = 1;
                        mReqType = 0;
                        unk_0x768 = mReqParam;
                        break;
                    case 4:
                        unk_0x75C = 5;
                        break;
                    case 10:
                    case 0xe:
                    case 0xf:
                        unk_0x75C = 0xb;
                        break;
                    }
                    break;
                }
                layout::Animator* anim = NULL;
                switch (unk_0x75C) {
                case 2: {
                    nw4r::lyt::TextBox* pane = static_cast<nw4r::lyt::TextBox*>(
                        mpTimerAnim->GetRootPane()->FindPaneByName("T_TimerMes"));
                    pane->SetString(System::getMessage(unk_0x768), 0);
                    anim = mpTimerAnim->getAnim(0);
                    break;
                }
                case 5:
                    anim = mpTimerAnim->getAnim(1);
                    break;
                case 8: {
                    nw4r::lyt::TextBox* pane = static_cast<nw4r::lyt::TextBox*>(
                        mpTimerAnim->GetRootPane()->FindPaneByName("T_TimerMes_01"));
                    pane->SetString(System::getMessage(unk_0x768), 0);
                    anim = mpTimerAnim->getAnim(2);
                    break;
                }
                case 0xb:
                    mpTimerAnim->getAnim(4)->stop();
                    anim = mpTimerAnim->getAnim(3);
                    break;
                case 0xe:
                    anim = mpTimerAnim->getAnim(4);
                    break;
                }
                if (anim != NULL) {
                    anim->initAnmFrame();
                    anim->play();
                    unk_0x75C++;
                }
            }
        }


        BOOL SDChannelSelect::setDialogMessage(u32 state, u32 message) {
            if (mReqType == 0) {
                mReqType = state;
                mReqParam = message;
                return TRUE;
            }
            return FALSE;
        }

        BOOL SDChannelSelect::getNandFree(NandSDWorker::AppBlocksInfo* freeOut) {
            int bytes = unk_0x728;
            int blocks = unk_0x72C;
            u64 tmpId = SCGetTmpTitleID();
            int num = unk_0x738;
            u32 count = 0;
            int off = 0;
            while (count < (u32)num) {
                if (tmpId == *(u64*)((char*)mpBuf724 + off)) break;
                count++;
                off += 0x10;
            }
            if (count < (u32)num) {
                const int* rec = (const int*)((char*)mpBuf724 + count * 0x10);
                bytes += rec[2];
                blocks += rec[3];
            }
            if (bytes < (int)freeOut->bytes || blocks < (int)freeOut->blocks) {
                return FALSE;
            }
            return TRUE;
        }

        void SDChannelSelect::iplSDChannelSelect_813DCFE0(int* p1, int* p2) {
            *p1 = unk_0x728;
            *p2 = unk_0x72C;
            u64 tmpId = SCGetTmpTitleID();
            int num = unk_0x738;
            u32 count = 0;
            int off = 0;
            while (count < (u32)num) {
                if (tmpId == *(u64*)((char*)mpBuf724 + off)) break;
                count++;
                off += 0x10;
            }
            if (count < (u32)num) {
                *p1 += *(int*)((char*)mpBuf724 + count * 0x10 + 8);
                *p2 += *(int*)((char*)mpBuf724 + count * 0x10 + 0xC);
            }
        }

        int SDChannelSelect::iplSDChannelSelect_813DD0AC(NandSDWorker::AppBlocksInfo* freeArea, NandSDWorker::AppBlocksInfo* needed, void* unk1, void* unk2, void* unk3) {
            int bytes, blocks;
            iplSDChannelSelect_813DCFE0(&bytes, &blocks);
            int* count = (int*)unk3;
            *count = 0;
            int off = 0;
            for (u32 i = 0; i < (u32)unk_0x738; i++) {
                if (*(ESTitleId*)((char*)mpBuf724 + off) != 0x48415A41ULL) {
                    int page, index;
                    if (System::getChannelManager()->hasChannel(*(ESTitleId*)((char*)mpBuf724 + off), &page, &index) != 0) {
                        bytes += *(int*)((char*)mpBuf724 + off + 8);
                        blocks += *(int*)((char*)mpBuf724 + off + 0xC);
                        *(ESTitleId*)((char*)unk1 + *count * 8) = *(ESTitleId*)((char*)mpBuf724 + off);
                        wchar_t* name = System::getChannelManager()->getTitleName(page, index, 0);
                        memcpy((char*)unk2 + *count * 0x2A, name, 0x2A);
                        *count += 1;
                        if (bytes >= (int)needed->bytes && blocks >= (int)needed->blocks) {
                            return 1;
                        }
                    }
                }
                off += 0x10;
            }
            if (bytes < (int)freeArea->bytes || blocks < (int)freeArea->blocks) {
                return 0;
            }
            return 1;
        }

        int SDChannelSelect::iplSDChannelSelect_813DD240(NandSDWorker::AppBlocksInfo* freeArea, NandSDWorker::AppBlocksInfo* needed, void* unk1, void* unk2, void* unk3) {
            int bytes, blocks;
            iplSDChannelSelect_813DCFE0(&bytes, &blocks);
            int* count = (int*)unk3;
            *count = 0;
            int i = unk_0x738 - 1;
            int off = i * 0x10;
            for (; i >= 0; i--) {
                if (*(ESTitleId*)((char*)mpBuf724 + off) != 0x48415A41ULL) {
                    int page, index;
                    if (System::getChannelManager()->hasChannel(*(ESTitleId*)((char*)mpBuf724 + off), &page, &index) != 0) {
                        bytes += *(int*)((char*)mpBuf724 + off + 8);
                        blocks += *(int*)((char*)mpBuf724 + off + 0xC);
                        *(ESTitleId*)((char*)unk1 + *count * 8) = *(ESTitleId*)((char*)mpBuf724 + off);
                        wchar_t* name = System::getChannelManager()->getTitleName(page, index, 0);
                        memcpy((char*)unk2 + *count * 0x2A, name, 0x2A);
                        *count += 1;
                        if (bytes >= (int)needed->bytes && blocks >= (int)needed->blocks) {
                            return 1;
                        }
                    }
                }
                off -= 0x10;
            }
            if (bytes < (int)freeArea->bytes || blocks < (int)freeArea->blocks) {
                return 0;
            }
            return 1;
        }

        int SDChannelSelect::iplSDChannelSelect_813DD3D8(NandSDWorker::AppBlocksInfo* freeArea, NandSDWorker::AppBlocksInfo* needed, void* unk1, void* unk2, void* unk3) {
            static const int sChanOrder[0xC] = {0xB, 0x7, 0x3, 0xA, 0x6, 0x2, 0x9, 0x5, 0x1, 0x8, 0x4, 0x0};
            int bytes, blocks;
            iplSDChannelSelect_813DCFE0(&bytes, &blocks);
            int* count = (int*)unk3;
            *count = 0;
            int page = 3;
            int base = 0xFC0;
            do {
                for (int i = 0; i < 0xC; i++) {
                    const u8* entry = (const u8*)System::getChannelManager() + base + sChanOrder[i] * 0x70;
                    ESTitleId title;
                    if (entry[0x24] != 0) {
                        title = *(ESTitleId*)(entry + 0x4C);
                    } else {
                        title = 0;
                    }
                    if (title != 0 && title != 0x48415A41ULL) {
                        int off = 0;
                        for (u32 j = 0; j < (u32)unk_0x738; j++) {
                            if (title == *(ESTitleId*)((char*)mpBuf724 + off)) {
                                bytes += *(int*)((char*)mpBuf724 + off + 8);
                                blocks += *(int*)((char*)mpBuf724 + off + 0xC);
                                *(ESTitleId*)((char*)unk1 + *count * 8) = *(ESTitleId*)((char*)mpBuf724 + off);
                                wchar_t* name = System::getChannelManager()->getTitleName(page, sChanOrder[i], 0);
                                memcpy((char*)unk2 + *count * 0x2A, name, 0x2A);
                                *count += 1;
                                if (bytes >= (int)needed->bytes && blocks >= (int)needed->blocks) {
                                    return 1;
                                }
                            }
                            off += 0x10;
                        }
                    }
                }
                page--;
                base -= 0x540;
            } while (page >= 0);
            if (bytes < (int)freeArea->bytes || blocks < (int)freeArea->blocks) {
                return 0;
            }
            return 1;
        }

        int SDChannelSelect::iplSDChannelSelect_813DD5D0(NandSDWorker::AppBlocksInfo* freeArea, NandSDWorker::AppBlocksInfo* needed, void* unk1, void* unk2, void* unk3) {
            int bytes, blocks;
            iplSDChannelSelect_813DCFE0(&bytes, &blocks);
            int i1 = -1, p1a = -1, p1b = -1;
            int i2 = -1, p2a = -1, p2b = -1;
            for (u32 i = 0; i < (u32)unk_0x738; i++) {
                if (*(ESTitleId*)((char*)mpBuf724 + i * 0x10) == 0x0001000148415445ULL) {
                    int page, index;
                    System::getChannelManager()->hasChannel(0x0001000148415445ULL, &page, &index);
                    p1a = page;
                    p1b = index;
                    i1 = i;
                } else if (*(ESTitleId*)((char*)mpBuf724 + i * 0x10) == 0x0001000148414445ULL) {
                    int page, index;
                    System::getChannelManager()->hasChannel(0x0001000148414445ULL, &page, &index);
                    p2a = page;
                    p2b = index;
                    i2 = i;
                }
            }
            int* count = (int*)unk3;
            *count = 0;
            int j = unk_0x738 - 1;
            while (j >= 0) {
                int off = j * 0x10;
                ESTitleId title = *(ESTitleId*)((char*)mpBuf724 + off);
                if (title != 0x48415A41ULL && title != 0x0001000148415445ULL && title != 0x0001000148414445ULL) {
                    int page, index;
                    if (System::getChannelManager()->hasChannel(*(ESTitleId*)((char*)mpBuf724 + off), &page, &index) != 0 &&
                        iplSavedata_813597A0(System::getSaveData(), *(ESTitleId*)((char*)mpBuf724 + off)) == 0) {
                        bytes += *(int*)((char*)mpBuf724 + off + 8);
                        blocks += *(int*)((char*)mpBuf724 + off + 0xC);
                        *(ESTitleId*)((char*)unk1 + *count * 8) = *(ESTitleId*)((char*)mpBuf724 + off);
                        wchar_t* name = System::getChannelManager()->getTitleName(page, index, 0);
                        memcpy((char*)unk2 + *count * 0x2A, name, 0x2A);
                        *count += 1;
                        if (bytes >= (int)needed->bytes && blocks >= (int)needed->blocks) {
                            return 1;
                        }
                    }
                }
                j--;
            }
            int k = 0x2F;
            int coff = 0x178;
            do {
                ESTitleId title;
                if (k < 0 || k >= 0x30) {
                    title = 0;
                } else {
                    title = *(ESTitleId*)((char*)System::getSaveData() + 0x340 + coff);
                }
                int page, index;
                if (System::getChannelManager()->hasChannel(title, &page, &index) != 0) {
                    int roff = 0;
                    for (u32 l = 0; l < (u32)unk_0x738; l++) {
                        char* rec = (char*)mpBuf724 + roff;
                        if (title == *(ESTitleId*)rec) {
                            bytes += *(int*)(rec + 8);
                            blocks += *(int*)(rec + 0xC);
                            *(ESTitleId*)((char*)unk1 + *count * 8) = *(ESTitleId*)rec;
                            wchar_t* name = System::getChannelManager()->getTitleName(page, index, 0);
                            memcpy((char*)unk2 + *count * 0x2A, name, 0x2A);
                            *count += 1;
                            if (bytes >= (int)needed->bytes && blocks >= (int)needed->blocks) {
                                return 1;
                            }
                        }
                        roff += 0x10;
                    }
                }
                k--;
                coff -= 8;
            } while (k >= 0);
            if (i2 >= 0) {
                int off2 = i2 * 0x10;
                bytes += *(int*)((char*)mpBuf724 + off2 + 8);
                blocks += *(int*)((char*)mpBuf724 + off2 + 0xC);
                *(ESTitleId*)((char*)unk1 + *count * 8) = *(ESTitleId*)((char*)mpBuf724 + off2);
                wchar_t* name = System::getChannelManager()->getTitleName(p2a, p2b, 0);
                memcpy((char*)unk2 + *count * 0x2A, name, 0x2A);
                *count += 1;
                if (bytes >= (int)needed->bytes && blocks >= (int)needed->blocks) {
                    return 1;
                }
            }
            if (i1 >= 0) {
                int off2 = i1 * 0x10;
                bytes += *(int*)((char*)mpBuf724 + off2 + 8);
                blocks += *(int*)((char*)mpBuf724 + off2 + 0xC);
                *(ESTitleId*)((char*)unk1 + *count * 8) = *(ESTitleId*)((char*)mpBuf724 + off2);
                wchar_t* name = System::getChannelManager()->getTitleName(p1a, p1b, 0);
                memcpy((char*)unk2 + *count * 0x2A, name, 0x2A);
                *count += 1;
                if (bytes >= (int)needed->bytes && blocks >= (int)needed->blocks) {
                    return 1;
                }
            }
            if (bytes >= (int)freeArea->bytes && blocks >= (int)freeArea->blocks) {
                return 1;
            }
            return 0;
        }

        int SDChannelSelect::startSDWorker(NandSDWorker::AppBlocksInfo* freeArea, NandSDWorker::AppBlocksInfo* needed, void* unk1, void* unk2, void* unk3, int type) {
            switch (type) {
                case 0:
                    return iplSDChannelSelect_813DD5D0(freeArea, needed, unk1, unk2, unk3);
                case 1:
                    return iplSDChannelSelect_813DD3D8(freeArea, needed, unk1, unk2, unk3);
                case 2:
                    return iplSDChannelSelect_813DD240(freeArea, needed, unk1, unk2, unk3);
                case 3:
                    return iplSDChannelSelect_813DD0AC(freeArea, needed, unk1, unk2, unk3);
                default:
                    return 0;
            }
        }

        int SDChannelSelect::getSelectChan(int dir, int* pageOut, int* indexOut) {
            int step = 1;
            int cur = mChanIndex + mChanPage * 0xC;
            if (dir == 1) {
                step = -1;
            }
            int i = cur + step;
            int limit = mChanCount * 0xC;
            int ret;
            while (true) {
                if (i < 0) {
                    i = limit - 1;
                }
                if (i >= limit) {
                    i = 0;
                }
                if (i == cur) {
                    *pageOut = mChanPage;
                    ret = 0;
                    *indexOut = mChanIndex;
                    break;
                }
                int page = i / 0xC;
                int index = i % 0xC;
                if (mpChanTable[i] != 0) {
                    *pageOut = page;
                    ret = 1;
                    *indexOut = index;
                    break;
                }
                i += step;
            }
            return ret;
        }

        void SDChannelSelect::setSelectChan(int page, int index, SDChannelObj* chanObj) {
            int t = index;
            mChanPage = page;
            index = t;
            mChanIndex = t;
            iplSDChannelSelect_813DF6D0(page, chanObj, index);
        }

        void SDChannelSelect::iplSDChannelSelect_813DDC80() {
            if (System::getDialog()->callBtn2Multi(scPages1, 4, 0xA)) {
                mState = 0x19;
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813DDCD8() {
            if (System::getDialog()->getLastResult() != -1) {
                mDialogAnim->getAnim(0)->initAnmFrame();
                System::getSaveData()->mData.didntGotoSDMenu = FALSE;
                EGG::Heap* heap = System::getMem2App();
                mpReqFile = System::getSaveData()->flushAsync(heap);
                mState = 1;
                mpWorker->mount_sd_async();
                mMountFlag = 1;
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813DDD64() {
            if (System::getDialog()->callBtn2Multi(scPages2, 3, 0xA)) {
                mState = 0x1B;
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813DDDBC() {
            if (System::getDialog()->getLastResult() != -1) {
                mDialogAnim->getAnim(0)->initAnmFrame();
                mState = 1;
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813DDE18() {
            if (System::getDialog()->getLastResult() != -1) {
                mFlag759 = 0;
                mState = 1;
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813DDE44() {
            if (System::getDialog()->getLastResult() != -1) {
                mState = 1;
            }
        }

        BOOL SDChannelSelect::isResetProcessDone() {
            if (mResetState >= 9) {
                goto ret0;
            }
            if (mResetState >= 5) {
                goto ret1;
            }
ret0:
            return FALSE;
ret1:
            return TRUE;
        }

        void SDChannelSelect::calcCommon() {
            if (mState == 2 && mpLayout->isPlaying(0) == 0) {
                SDButton* btn = (SDButton*)System::getSceneManager()->getScene(0x24);
                if (btn != NULL) {
                    setEventHandler__Q33ipl5scene8SDButtonFPQ23gui12EventHandlerPQ23gui12EventHandler(btn, mpEvent);
                    mState = 3;
                    if (mChanPage > 0) {
                        btn->initArrowAppearance(1, true);
                    } else {
                        btn->initArrowAppearance(1, false);
                    }
                    if (mChanCount > 1 && mChanPage < mChanCount - 1) {
                        btn->initArrowAppearance(0, true);
                    } else {
                        btn->initArrowAppearance(0, false);
                    }
                }
            }
            if (mState == 3 && System::getFader()->getStatus() == EGG::Fader::PREPARE_OUT) {
                if (*(int*)((char*)System::getSaveData() + 0x33C) != 0) {
                    unk_0x754 = 0;
                    mState = 0x18;
                } else {
                    mState = 1;
                }
            }
            mpLayout->calc();
            mpGui->calc();
            calcChannelObjects();
            mpAnimLayout1->calc();
            mpAnimLayout2->calc();
            mpAnimLayout3->calc();
            mpAnimLayout5->calc();
            mDialogAnim->calc();
            mpAnimLayout4->calc();
            mpTimerAnim->calc();
            processWorkerState();
        }

        FaderSceneCommand SDChannelSelect::calcFadein() {
            return (FaderSceneCommand)!mpLayout->isPlaying(0);
        }

        FaderSceneCommand SDChannelSelect::calcNormal() {
            int state = mState;
            bool ret;
            if (state == 0xD) {
                ret = false;
            } else {
                switch (state) {
                case 1:
                    iplSDChannelSelect_813DF2A8();
                    break;
                case 8:
                case 9:
                    iplSDChannelSelect_813DF3E0();
                    break;
                case 0xA:
                case 0xB:
                    iplSDChannelSelect_813DF3FC();
                    break;
                case 5:
                    createChildScene(0x23, this, NULL, this);
                    mState = 6;
                    break;
                case 7:
                    iplSDChannelSelect_813DF50C();
                    break;
                case 0xC:
                    mState = 0xD;
                    break;
                case 0xE:
                    iplSDChannelSelect_813DF558();
                    break;
                case 0xF:
                    iplSDChannelSelect_813E1568();
                    break;
                case 0x10:
                    iplSDChannelSelect_813E168C();
                    break;
                case 0x11:
                    iplSDChannelSelect_813E195C();
                    break;
                case 0x12:
                    iplSDChannelSelect_813E19C8();
                    break;
                case 0x13:
                    iplSDChannelSelect_813E1A30();
                    break;
                case 0x14:
                    iplSDChannelSelect_813E1C38();
                    break;
                case 0x15:
                    iplSDChannelSelect_813E1D50();
                    break;
                case 0x16:
                case 0x17:
                    iplSDChannelSelect_813E1E4C();
                    break;
                case 0x18:
                    iplSDChannelSelect_813DDC80();
                    break;
                case 0x19:
                    iplSDChannelSelect_813DDCD8();
                    break;
                case 0x1A:
                    iplSDChannelSelect_813DDD64();
                    break;
                case 0x1B:
                    iplSDChannelSelect_813DDDBC();
                    break;
                case 0x1C:
                    iplSDChannelSelect_813DDE18();
                    break;
                case 0x1D:
                    iplSDChannelSelect_813DDE44();
                    break;
                }
                if (state == 1 && mState != 1 && mState != 0xF) {
                    SDChannelObj* chanObj = NULL;
                    while ((chanObj = (SDChannelObj*)nw4r::ut::List_GetNext(&mChanList, chanObj)) != NULL) {
                        if (chanObj->mChanPage == mChanPage) {
                            if (mState != 5 || chanObj->mChanIndex != mChanIndex) {
                                chanObj->initCursorAnim(true);
                            }
                            chanObj->initBalloonAnim(true);
                        }
                    }
                    int i = 0;
                    do {
                        mpGui->initPane(getChannelPane(i));
                        i++;
                    } while (i < 0xC);
                }
                ret = mState == 4;
            }
            return (FaderSceneCommand)ret;
        }

        void SDChannelSelect::initCalcFadeout() {
            if (mState == 4) {
                clearCommandQueue();
                clearNoticeQueue();
                System::getFader()->fadeOut();
                TVRCManager::getHandle()->setEnable(0);
                System::getChannelManager()->refreshAsync();
                reserveAllSceneDestruction(4, (void*)System::getNwc24Manager()->received());
            }
        }

        FaderSceneCommand SDChannelSelect::calcFadeout() {
            bool ret = false;
            if (mState == 4) {
                ret = System::getFader()->getStatus() == EGG::Fader::PREPARE_IN;
            }
            return (FaderSceneCommand)ret;
        }

        void SDChannelSelect::draw() {
            if (mState != 0xD && System::getSceneManager()->onDrawLayer(scene::DRAW_LAYER_2)) {
                if (mState == 7 || mState == 0xC || mState == 0xE) {
                    utility::Graphics::setOrthoTransAndScale(mVec, mVec2);
                }
                utility::Graphics::setOrtho(0);
                for (int i = 0; i < 5; i++) {
                    nw4r::lyt::Pane* pane = mpLayout->GetRootPane()->FindPaneByName(scBaseMaskPaneNames[i], true);
                    pane->SetVisible(true);
                    mpLayout->draw(pane);
                    pane->SetVisible(false);
                }
                iplSDChannelSelect_813DEF68();
                iplSDChannelSelect_813DFF2C();
                u16 efbHeight = System::getRenderModeObj()->efbHeight;
                u16 fbWidth = System::getRenderModeObj()->fbWidth;
                GXSetScissor(0, 0, fbWidth, efbHeight);
                nw4r::lyt::Pane* maskPane = mpLayout->GetRootPane()->FindPaneByName(scMaskPaneName, true);
                maskPane->SetVisible(false);
                mpLayout->draw();
                nw4r::lyt::Pane* pagePane = mpAnimLayout6->GetRootPane()->FindPaneByName("TextBox_00", true);
                nw4r::lyt::TextBox* textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(pagePane);
                for (int i = 0; i < 3; i++) {
                    wchar_t text[0x15];
                    text[0x14] = L'\0';
                    swprintf(text, 0x13, L"%d", mChanPage + i);
                    textBox->SetString(text, 0);
                    nw4r::lyt::Pane* pane = mpLayout->GetRootPane()->FindPaneByName(scClockPaneNames[i], true);
                    nw4r::math::MTX34 mtx(pane->GetGlobalMtx());
                    math::VEC3 pos(0.0f, 0.0f, 0.0f);
                    PSMTXMultVec(mtx, pos, pos);
                    mpAnimLayout6->GetRootPane()->SetTranslate(pos);
                    mpAnimLayout6->calcMtx();
                    mpAnimLayout6->draw();
                }
                drawChannelObjects();
                maskPane->SetVisible(true);
                mpLayout->draw(maskPane);
                mpAnimLayout2->draw();
                mpTimerAnim->draw();
            }
            if (mState == 0xD && System::getSceneManager()->onDrawLayer(scene::DRAW_LAYER_2)) {
                utility::Graphics::setOrtho(0);
                GXColor color = {0x00, 0x00, 0x00, 0xFF};
                nw4r::ut::Rect rect;
                System::getProjectionRect(&rect);
                utility::Graphics::drawPolygon(rect, color);
            }
        }

        void SDChannelSelect::destroy() {
            System::getBS2Manager()->restart();
            System::getSaveData()->mLastSDPrevPage = mChanPage;

            SDChannelObj* chanObj = NULL;
            while ((chanObj = (SDChannelObj*)nw4r::ut::List_GetNext(&mChanList, NULL)) != NULL) {
                nw4r::ut::List_Remove(&mChanList, chanObj);
                destroyChannelObject(chanObj);
            }

            mpWorkHeap->destroy();
            mpObjHeap->destroy();
            mpHeap1->destroy();
            mpHeap2->destroy();
            if (mpRsoThread != NULL) {
                delete mpRsoThread;
            }
            mpCsHeap->destroy();
            if (mpReqFile != NULL) {
                while (!System::getSaveData()->isFinished(mpReqFile)) {
                    OSSleepTicks(((s64)((OS_BUS_CLOCK / 4) / 125000) * 100) / 8);
                }
                delete mpReqFile;
                mpReqFile = NULL;
            }
            if (mpWorker != NULL) {
                if (!mpWorker->is_terminated()) {
                    mpWorker->unk_0x04 = true;
                    while (mpWorker->is_working()) {
                        OSSleepTicks(((s64)((OS_BUS_CLOCK / 4) / 125000) * 100) / 8);
                    }
                    mpWorker->terminate_async();
                    while (!mpWorker->is_terminated()) {
                        OSSleepTicks(((s64)((OS_BUS_CLOCK / 4) / 125000) * 100) / 8);
                    }
                }
                System::getMem2App()->free(mpWorkBuf1);
                System::getMem2App()->free(mpWorkBuf2);
                if (mpBuf71C != NULL) {
                    delete[] mpBuf71C;
                }
                if (mpBuf720 != NULL) {
                    delete[] mpBuf720;
                }
                if (mpChanTable != NULL) {
                    delete[] mpChanTable;
                }
                if (mpBuf724 != NULL) {
                    delete[] mpBuf724;
                }
                mAsyncFlag = 6;
                delete mpWorker;
                mpWorker = NULL;
            }
        }

        void SDChannelSelect::createBaseLayout() {
            mpLayout = new layout::Object(getSceneHeap(), mpChanLayoutFile, "arc", "mn_SdcardMenu_a.brlyt");
            if (SCGetAspectRatio() == SC_ASPECT_RATIO_16x9) {
                GXTexObj tex16x9;
                GXTexObj tex16;
                nw4r::lyt::Pane* pane16x9 = mpLayout->GetRootPane()->FindPaneByName("ChangeTex16x9", true);
                pane16x9->GetMaterial()->GetTexture(&tex16x9, GX_TEXMAP0);
                nw4r::lyt::Pane* pane16 = mpLayout->GetRootPane()->FindPaneByName("Picture_16", true);
                pane16->GetMaterial()->GetTexture(&tex16, GX_TEXMAP0);
                for (int i = 0; i < 5; i++) {
                    nw4r::lyt::Pane* pane = mpLayout->GetRootPane()->FindPaneByName(scPicturePaneNames[i], true);
                    pane->GetMaterial()->SetTexture(GX_TEXMAP0, tex16x9);
                    nw4r::lyt::Pane* edgePane = mpLayout->GetRootPane()->FindPaneByName(scEdgePaneNames[i], true);
                    edgePane->GetMaterial()->SetTexture(GX_TEXMAP0, tex16);
                }
            }
            mpLayout->bind("mn_SdcardMenu_a.brlan");
            mpLayout->finishBinding();

            mpAnimLayout6 = new layout::Object(getSceneHeap(), mpChanLayoutFile, "arc", "mn_SdcardMenu_Page.brlyt");

            mpTimerAnim = new layout::Object(getSceneHeap(), mpChanLayoutFile, "arc", "mn_Nocard.brlyt");
            mpTimerAnim->bindToGroup("mn_Nocard_IN.brlan", "Group_00", false, true);
            mpTimerAnim->bindToGroup("mn_Nocard_Out.brlan", "Group_00", false, true);
            mpTimerAnim->bindToGroup("mn_Nocard_IN_02.brlan", "Group_01", false, true);
            mpTimerAnim->bindToGroup("mn_Nocard_Out_02.brlan", "Group_01", false, true);
            mpTimerAnim->bindToGroup("mn_Nocard_Wait.brlan", "G_Wait", false, true);
            mpTimerAnim->getAnim(0)->initAnmFrame();
            mpTimerAnim->getAnim(2)->initAnmFrame();
            mpTimerAnim->finishBinding();

            mpBtnLayout = new layout::Object(getSceneHeap(), mpChanLayoutFile, "arc", "help_Btn.brlyt");
            scPages1[3].layoutObj = mpBtnLayout;

            SDChannelSelectEvent* event = new SDChannelSelectEvent(this);
            mpGui = new gui::PaneManager(event, mpLayout->getDrawInfo(), NULL, NULL);
            mpGui->createLayoutScene(*mpLayout->getNW4RLyt());
            mpGui->setAllComponentTriggerTarget(false);
            for (int i = 0; i < 0xC; i++) {
                mpGui->getPaneComponentByPane(getChannelPane(i))->setTriggerTarget(true);
            }
            for (int i = 0; i < 4; i++) {
                mHandlers[i] = new math::HermiteIntp<math::VEC3>();
            }
        }

        void SDChannelSelect::updateChannelObjects() {
            SDChannelObj* chanObj = NULL;
            while (chanObj = (SDChannelObj*)nw4r::ut::List_GetNext(&mChanList, chanObj), chanObj != NULL) {
                updateChannelObject(chanObj);
            }
        }

        void SDChannelSelect::updateChannelObject(SDChannelObj* chanObj) {
            chanObj->prepare();
            chanObj->setHeaps(mpHeap1, mpHeap2);
            chanObj->setBasePane(getChannelBasePane(chanObj->mChanPage, chanObj->mChanIndex, mChanPage));
            chanObj->create(mpChanLayoutFile);
        }

        void SDChannelSelect::calcChannelObjects() {
            SDChannelObj* chanObj = NULL;
            while (chanObj = (SDChannelObj*)nw4r::ut::List_GetNext(&mChanList, chanObj), chanObj != NULL) {
                chanObj->calc();
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813DEF68() {
            int page;
            int index;
            SDChannelObj* chanObj = NULL;
            while ((chanObj = (SDChannelObj*)nw4r::ut::List_GetNext(&mChanList, chanObj)) != NULL) {
                page = chanObj->mChanPage;
                index = chanObj->mChanIndex;
                if (hasChannelObject(page, index) == 0 || iplSDChannelSelect_813DF1E4(chanObj) == 0) {
                    continue;
                }

                iplSDChannelSelect_813E0848(chanObj);
                chanObj->drawThumbnail();

                if (chanObj->isValid() != 0) {
                    if (mState < 0x18) {
                        if (mState >= 0xF) {
                            if (page != mSelPage || index != mSelIndex) {
                        nw4r::math::VEC3 pos = chanObj->getTranslate();
                        mpAnimLayout1->GetRootPane()->SetTranslate(pos);
                        mpAnimLayout1->calcMtx();
                        mpAnimLayout1->draw();
                            }
                        }
                    }
                } else {
                    if (chanObj->mChanType == 2) {
                        nw4r::math::VEC3 pos = chanObj->getTranslate();
                        mpAnimLayout5->GetRootPane()->SetTranslate(pos);
                        mpAnimLayout5->calcMtx();
                        mpAnimLayout5->draw();
                    }
                }

                switch (mState) {
                    case 0xF:
                    case 0x10:
                    case 0x13:
                    case 0x14:
                    case 0x16:
                    case 0x17: {
                        if (page == mSelPage && index == mSelIndex) {
                            nw4r::math::VEC3 pos = chanObj->getTranslate();
                            mpAnimLayout4->GetRootPane()->SetTranslate(pos);
                            mpAnimLayout4->calcMtx();
                            mpAnimLayout4->draw();
                        }
                        break;
                    }
                }

                if (mState < 0x16) {
                    if (mState >= 0x13) {
                        if (page == mFieldF0 && index == mFieldF4) {
                            mpAnimLayout3->draw();
                            mDialogAnim->draw();
                        }
                    }
                }
            }
        }

        BOOL SDChannelSelect::iplSDChannelSelect_813DF1E4(SDChannelObj* chanObj) {
            return chanObj->mState == 3;
        }

        void SDChannelSelect::drawChannelObjects() {
            SDChannelObj* chanObj = NULL;
            while (chanObj = (SDChannelObj*)nw4r::ut::List_GetNext(&mChanList, chanObj), chanObj != NULL) {
                if (hasChannelObject(chanObj->mChanPage, chanObj->mChanIndex) != 0) {
                    chanObj->drawCursor();
                }
            }
            chanObj = NULL;
            while (chanObj = (SDChannelObj*)nw4r::ut::List_GetNext(&mChanList, chanObj), chanObj != NULL) {
                if (hasChannelObject(chanObj->mChanPage, chanObj->mChanIndex) != 0) {
                    chanObj->drawBalloon();
                }
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813DF2A8() {
            if (mFlag759 != 0 && System::getDialog()->callBtn1(0xC1, 0x2E) != 0) {
                mState = 0x1C;
            }
            SDButton* button = (SDButton*)System::getSceneManager()->getScene(0x24);
            if (button != NULL && button->isActive()) {
                button->update();
            }
            if (mState == 1) {
                controller::Interface* con = System::getMasterController();
                if (con->down(controller::BTN_NEXT_LEFT)) {
                    if (mChanPage > 0) {
                        iplSDChannelSelect_813E0398(8);
                        return;
                    }
                } else if (con->down(controller::BTN_NEXT_RIGHT) && mChanPage < mChanCount - 1) {
                    iplSDChannelSelect_813E0398(9);
                    return;
                }
            }
            mpGui->update();
        }

        void SDChannelSelect::iplSDChannelSelect_813DF3E0() {
            if (mState == 8) {
                iplSDChannelSelect_813E03B0(0xA);
            } else {
                iplSDChannelSelect_813E03B0(0xB);
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813DF3FC() {
            if (!mpLayout->isPlaying(0)) {
                SDButton* button = (SDButton*)System::getSceneManager()->getScene(0x24);
                if (mState == 0xA) {
                    mChanPage--;
                    if (mChanPage == 0) {
                        button->animation(0xF);
                        mbFlagC8 = 0;
                    } else if (mbFlagC9 == 0) {
                        button->animation(0xE);
                        mbFlagC9 = 1;
                    }
                } else {
                    mChanPage++;
                    if (mChanPage == mChanCount - 1) {
                        button->animation(0x10);
                        mbFlagC9 = 0;
                    } else if (mbFlagC8 == 0) {
                        button->animation(0xD);
                        mbFlagC8 = 1;
                    }
                }
                mpLayout->finishBinding();
                iplSDChannelSelect_813DF6D0(mChanPage, NULL, -1);
                mState = 1;
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813DF50C() {
            calcPageAnimations();
            iplSDChannelSelect_813E0EE0();
            if (*(int*)((u8*)mHandlers[0] + 0x14) != 1) {
                mState = 0xC;
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813DF558() {
            if (mHandlers[0]->isPlaying() && System::getSceneManager()->getScene(0x23) == NULL) {
                SDButton* button = (SDButton*)System::getSceneManager()->getScene(0x24);
                button->enableBtn();
                if (mChanPage > 0) {
                    button->animation(0xD);
                    mbFlagC8 = 1;
                } else {
                    mbFlagC8 = 0;
                }
                if (mChanCount > 1 && mChanPage < mChanCount - 1) {
                    button->animation(0xE);
                    mbFlagC9 = 1;
                } else {
                    mbFlagC9 = 0;
                }
                setEventHandler__Q33ipl5scene8SDButtonFPQ23gui12EventHandlerPQ23gui12EventHandler(button, mpEvent);
                TVRCManager::getHandle()->setEnable(1);
                snd::getSystem()->startBGM("WIPL_BGM_MENU");
                clearNoticeQueue();
                iplSDChannelSelect_813DC7EC(0, -1);
                iplSDChannelSelect_813DC7EC(-1, -1);
                iplSDChannelSelect_813DC7EC(1, -1);
                iplSDChannelSelect_813DC7EC(-2, -1);
                iplSDChannelSelect_813DC7EC(2, -1);
                mState = 1;
            } else {
                calcPageAnimations();
                iplSDChannelSelect_813E0EE0();
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813DF6D0(int page, SDChannelObj* chanObj, int index) {
            iplSDChannelSelect_813DF9C8(page, chanObj);
            iplSDChannelSelect_813DF834(page, 0);
            if (page < mChanCount - 1) {
                iplSDChannelSelect_813DF834(page + 1, 0);
            }
            if (page > 0) {
                iplSDChannelSelect_813DF834(page - 1, 0);
            }
            iplSDChannelSelect_813DFCF0(page);
            SDChannelObj* obj = NULL;
            while (obj = (SDChannelObj*)nw4r::ut::List_GetNext(&mChanList, obj), obj != NULL) {
                int entry = obj->mChanIndex + obj->mChanPage * 0xC;
                if (!obj->isValid() && mpChanTable[entry] != 0 && unk_0x77F != 0) {
                    obj->mChanType = 2;
                }
            }
            updateChannelObjects();
            if (unk_0x77F != 0) {
                clearNoticeQueue();
                iplSDChannelSelect_813DC7EC(0, index);
                iplSDChannelSelect_813DC7EC(-1, -1);
                iplSDChannelSelect_813DC7EC(1, -1);
                iplSDChannelSelect_813DC7EC(-2, -1);
                iplSDChannelSelect_813DC7EC(2, -1);
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813DF834(int page, int unk) {
            for (int i = 0; i < 0xC; i++) {
                if (unk != 0 || getChanObj(page, i) == NULL) {
                    iplSDChannelSelect_813DF944(page, i);
                }
            }
            if (page < mChanCount - 1) {
                for (int i = 0; i < 0xC; i += 4) {
                    if (unk != 0 || getChanObj(page + 1, i) == NULL) {
                        iplSDChannelSelect_813DF944(page + 1, i);
                    }
                }
            }
            if (page > 0) {
                for (int i = 3; i < 0xC; i += 4) {
                    if (unk != 0 || getChanObj(page - 1, i) == NULL) {
                        iplSDChannelSelect_813DF944(page - 1, i);
                    }
                }
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813DF944(int page, int index) {
            EGG::Heap* heap = EGG::FrmHeap::create(0x212B8, mpWorkHeap, 2);
            SDChannelObj* chanObj = new (mpObjHeap, 4) SDChannelObj(heap, page, index);
            nw4r::ut::List_Append(&mChanList, chanObj);
        }

        void SDChannelSelect::iplSDChannelSelect_813DF9C8(int page, SDChannelObj* keepObj) {
            int keepPage;
            int keepIndex;
            if (keepObj != NULL) {
                keepPage = keepObj->mChanPage;
                keepIndex = keepObj->mChanIndex;
            }
            SDChannelObj* chanObj = NULL;
            while (chanObj = (SDChannelObj*)nw4r::ut::List_GetNext(&mChanList, chanObj), chanObj != NULL) {
                int chanPage = chanObj->mChanPage;
                int chanIndex = chanObj->mChanIndex;
                if ((keepObj == NULL || chanPage != keepPage || chanIndex != keepIndex) &&
                    ((mState >= 0x18 || mState < 0xF || chanPage != mSelPage || chanIndex != mSelIndex) &&
                     isChannelInCalc(chanPage, chanIndex, page) == 0)) {
                    SDChannelObj* prev = (SDChannelObj*)nw4r::ut::List_GetPrev(&mChanList, chanObj);
                    nw4r::ut::List_Remove(&mChanList, chanObj);
                    destroyChannelObject(chanObj);
                    chanObj = prev;
                }
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813DFAC0() {
            SDChannelObj* chanObj = NULL;
            while (chanObj = (SDChannelObj*)nw4r::ut::List_GetNext(&mChanList, chanObj), chanObj != NULL) {
                if (chanObj->isValid() != 0) {
                    SDChannelObj* prev = (SDChannelObj*)nw4r::ut::List_GetPrev(&mChanList, chanObj);
                    nw4r::ut::List_Remove(&mChanList, chanObj);
                    destroyChannelObject(chanObj);
                    chanObj = prev;
                } else {
                    if (chanObj->mChanType == 2) {
                        chanObj->mChanType = 1;
                    }
                }
            }
            iplSDChannelSelect_813DF834(mChanPage, 0);
            if (mChanPage < mChanCount - 1) {
                iplSDChannelSelect_813DF834(mChanPage + 1, 0);
            }
            if (mChanPage > 0) {
                iplSDChannelSelect_813DF834(mChanPage - 1, 0);
            }
            updateChannelObjects();
        }

        void SDChannelSelect::iplSDChannelSelect_813DFBBC() {
            SDChannelObj* chanObj = NULL;
            while (chanObj = (SDChannelObj*)nw4r::ut::List_GetNext(&mChanList, chanObj), chanObj != NULL) {
                int entry = chanObj->mChanIndex + chanObj->mChanPage * 0xC;
                if (!chanObj->isValid() && mpChanTable[entry] != 0) {
                    chanObj->mChanType = 2;
                }
            }
            clearNoticeQueue();
            iplSDChannelSelect_813DC7EC(0, -1);
            iplSDChannelSelect_813DC7EC(-1, -1);
            iplSDChannelSelect_813DC7EC(1, -1);
            iplSDChannelSelect_813DC7EC(-2, -1);
            iplSDChannelSelect_813DC7EC(2, -1);
        }

        void SDChannelSelect::destroyChannelObject(SDChannelObj* channel) {
            EGG::Heap* heap = *(EGG::Heap**)((u8*)channel + 0x10);
            delete channel;
            if (heap != NULL) {
                heap->destroy();
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813DFCF0(int idx) {
            iplSDChannelSelect_813DFD64(idx, 0);
            if (idx < mChanCount - 1) {
                iplSDChannelSelect_813DFD64(idx + 1, -1);
            }
            if (idx > 0) {
                iplSDChannelSelect_813DFD64(idx - 1, 1);
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813DFD64(int idx, int dir) {
            for (int i = 0; i < 0xC; i++) {
                if (dir == -1) {
                    if ((i & 3) == 0) {
                        continue;
                    }
                } else if (dir == 1 && (i & 3) == 3) {
                    continue;
                }
                SDChannelObj* chanObj = getChanObj(idx, (int)i);
                if (chanObj != NULL) {
                    nw4r::ut::List_Remove(&mChanList, chanObj);
                    nw4r::ut::List_Append(&mChanList, chanObj);
                }
            }
            if (dir != 1 && idx + 1 < mChanCount) {
                for (int i = 0; i < 0xC; i += 4) {
                    SDChannelObj* chanObj = getChanObj(idx + 1, i);
                    if (chanObj != NULL) {
                        nw4r::ut::List_Remove(&mChanList, chanObj);
                        nw4r::ut::List_Append(&mChanList, chanObj);
                    }
                }
            }
            if (dir != -1 && idx - 1 >= 0) {
                for (int i = 3; i < 0xC; i += 4) {
                    SDChannelObj* chanObj = getChanObj(idx - 1, i);
                    if (chanObj != NULL) {
                        nw4r::ut::List_Remove(&mChanList, chanObj);
                        nw4r::ut::List_Append(&mChanList, chanObj);
                    }
                }
            }
        }

        SDChannelObj* SDChannelSelect::getChanObj(int page, int index) {
            SDChannelObj* chanObj = NULL;
            while ((chanObj = (SDChannelObj*)nw4r::ut::List_GetNext(&mChanList, chanObj)) != NULL) {
                int chanPage = chanObj->mChanPage;
                int chanIndex = chanObj->mChanIndex;
                if (chanPage == page && chanIndex == index) {
                    return chanObj;
                }
            }
            return NULL;
        }

        void SDChannelSelect::iplSDChannelSelect_813DFF2C() {
            int left;
            if (mState == 0xA || mState == 0x16) {
                left = 1;
            } else {
                left = 0;
            }
            if (mChanPage - 1 - left >= 0) {
                mpLayout->GetRootPane()->FindPaneByName(scEdgePaneNames[0], true)->SetVisible(true);
                mpLayout->GetRootPane()->FindPaneByName(scEdgePaneNames[1], true)->SetVisible(true);
            } else {
                mpLayout->GetRootPane()->FindPaneByName(scEdgePaneNames[1 - left], true)->SetVisible(false);
            }
            int right;
            if (mState == 0xB || mState == 0x17) {
                right = 1;
            } else {
                right = 0;
            }
            if (right + mChanPage + 1 < mChanCount) {
                mpLayout->GetRootPane()->FindPaneByName(scEdgePaneNames[3], true)->SetVisible(true);
                mpLayout->GetRootPane()->FindPaneByName(scEdgePaneNames[4], true)->SetVisible(true);
            } else {
                mpLayout->GetRootPane()->FindPaneByName(scEdgePaneNames[right + 3], true)->SetVisible(false);
            }
        }

        BOOL SDChannelSelect::hasChannelObject(int page, int index) const {
            if (page == mChanPage) {
                return TRUE;
            }
            if (page == mChanPage - 1) {
                if (mState == 0xA || mState == 0x16) {
                    return TRUE;
                }
                for (int i = 3; i < 3 + 12; i += 4) {
                    if (i == index) {
                        return TRUE;
                    }
                }
            } else if (page == mChanPage - 2) {
                if (mState == 0xA || mState == 0x16) {
                    for (int i = 3; i < 3 + 12; i += 4) {
                        if (i == index) {
                            return TRUE;
                        }
                    }
                }
            } else if (page == mChanPage + 1) {
                if (mState == 0xB || mState == 0x17) {
                    return TRUE;
                }
                for (int i = 0; i < 0 + 12; i += 4) {
                    if (i == index) {
                        return TRUE;
                    }
                }
            } else if (page == mChanPage + 2 && (mState == 0xB || mState == 0x17)) {
                for (int i = 0; i < 0 + 12; i += 4) {
                    if (i == index) {
                        return TRUE;
                    }
                }
            }
            return FALSE;
        }

        BOOL SDChannelSelect::isChannelInCalc(int page, int index, int currentPage) const {
            if (page - currentPage <= -3 || page - currentPage >= 3 || strcmp(scChanPaneNames[page - currentPage + 2][index], "") == 0) {
                return FALSE;
            }
            return TRUE;
        }

        BOOL SDChannelSelect::iplSDChannelSelect_813E0294(int page) {
            BOOL ret;
            for (int i = 0; i < 0xC; i++) {
                SDChannelObj* chanObj = getChanObj(page, i);
                if (chanObj == NULL || iplSDChannelSelect_813DF1E4(chanObj) == 0) {
                    ret = FALSE;
                    goto done;
                }
            }
            if (page + 1 < mChanCount) {
                for (int i = 0; i < 0xC; i += 4) {
                    SDChannelObj* chanObj = getChanObj(page + 1, i);
                    if (chanObj == NULL || iplSDChannelSelect_813DF1E4(chanObj) == 0) {
                        ret = FALSE;
                        goto done;
                    }
                }
            }
            if (page - 1 >= 0) {
                for (int i = 3; i < 0xC; i += 4) {
                    SDChannelObj* chanObj = getChanObj(page - 1, i);
                    if (chanObj == NULL || iplSDChannelSelect_813DF1E4(chanObj) == 0) {
                        ret = FALSE;
                        goto done;
                    }
                }
            }
            ret = TRUE;
        done:
            return ret;
        }

        void SDChannelSelect::iplSDChannelSelect_813E0398(int state) {
            mState = state;
            snd::getSystem()->startSE("WSD_SELECT");
        }

        void SDChannelSelect::iplSDChannelSelect_813E03B0(int a) {
            if (a == 0xA) {
                mpLayout->setMinFrame(0.0f, -1);
                mpLayout->setMaxFrame(20.0f, -1);
            } else {
                mpLayout->setMinFrame(40.0f, -1);
                mpLayout->setMaxFrame(60.0f, -1);
            }
            mpLayout->setAnmType(0, -1);
            mpLayout->start(-1);
            mState = a;
        }

        void SDChannelSelect::iplSDChannelSelect_813E0450(int page, int index) {
            SDChannelObj* chanObj = getChanObj(page, index);
            iplSDChannelSelect_813E0BEC(&math::VEC3(chanObj->mpThumbLayout->GetRootPane()->GetTranslate()), 0);
            chanObj->setCursorDecideAnim();
            SDButton* button = (SDButton*)System::getSceneManager()->getScene(0x24);
            if (mbFlagC8 != 0) {
                button->animation(0xF);
            }
            if (mbFlagC9 != 0) {
                button->animation(0x10);
            }
            button->disableBtn();
            setEventHandler__Q33ipl5scene8SDButtonFPQ23gui12EventHandlerPQ23gui12EventHandler(button, NULL);
            mChanIndex = index;
            mState = 5;
            snd::getSystem()->startSE("WIPL_SE_BT_PUSH");
            snd::getSystem()->stopBGM(5);
        }

        BOOL SDChannelSelect::isAnyChanMoving() {
            mpLayout->setMinFrame(200.0f, -1);
            mpLayout->setMaxFrame(228.0f, -1);
            mpLayout->setAnmType(0, -1);
            mpLayout->start(-1);
            snd::getSystem()->startSE("WIPL_SE_CH_SELECT");
            mState = 7;
            return TRUE;
        }

        BOOL SDChannelSelect::fn_813E05C0(int page) {
            if (page == mChanPage) {
                return iplSDChannelSelect_813E0294(page);
            } else {
                mChanPage = page;
                iplSDChannelSelect_813DF6D0(page, 0, -1);
                return iplSDChannelSelect_813E0294(page);
            }
        }

        void SDChannelSelect::fn_813E0624(int page, int index) {
            mChanPage = page;
            mChanIndex = index;
            mpLayout->setAnmType(1, -1);
            mpLayout->start(-1);
            nw4r::math::VEC3 v = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
            nw4r::lyt::Pane* pane = getCenterChannelPane(index);
            PSMTXMultVec(pane->GetGlobalMtx(), v, v);
            math::VEC3 v2(v);
            iplSDChannelSelect_813E0BEC(&v2, 1);
            iplSDChannelSelect_813E0EE0();
            mState = 0xE;
        }

        nw4r::lyt::Pane* SDChannelSelect::getChannelBasePane(int page, int index, int currentPage) const {
            if (isChannelInCalc(page, index, currentPage) != 0) {
                return mpLayout->GetRootPane()->FindPaneByName(scChanPaneNames[page - currentPage + 2][index], true);
            }
            return mpLayout->GetRootPane()->FindPaneByName("Picture_16", true);
        }

        nw4r::lyt::Pane* SDChannelSelect::getCenterChannelPane(int index) const {
            return mpLayout->GetRootPane()->FindPaneByName(scChanPaneNames[2][index], true);
        }

        nw4r::lyt::Pane* SDChannelSelect::getChannelPane(int index) const {
            return mpLayout->GetRootPane()->FindPaneByName(scChanPaneNames[2][index], true);
        }

        void SDChannelSelect::iplSDChannelSelect_813E0848(SDChannelObj* chanObj) {
            nw4r::math::VEC3 vec(chanObj->getTranslate());
            nw4r::ut::Rect projRect;
            System::getProjectionRect(&projRect);
            GXRenderModeObj* rMode = System::getRenderModeObj();
            f32 var_f29;
            f32 var_f30;
            f32 var_f31;
            f32 var_f1;
            u16 var_r0;
            u16 var_r3;
            if (mState == 7 || mState == 0xC || mState == 0xE) {
                nw4r::math::MTX44 mtx;
                f32 rightScale = projRect.right / mVec2.x;
                f32 leftScale = projRect.left / mVec2.x;
                f32 bottomScale = projRect.bottom / mVec2.y;
                f32 topScale = projRect.top / mVec2.y;
                f32 bottom = mVec.y - bottomScale;
                f32 right = mVec.x + rightScale;
                f32 left = mVec.x + leftScale;
                f32 top = mVec.y - topScale;
                MTXOrtho(mtx, top, bottom, left, right, -100.0f, 100.0f);
                nw4r::math::VEC4 vec4_in(vec.x, vec.y, 0.0f, 1.0f);
                nw4r::math::VEC4 vec4;
                nw4r::math::VEC4Transform(&vec4, &mtx, &vec4_in);
                var_r0 = rMode->fbWidth;
                var_r3 = rMode->efbHeight;
                var_f29 = projRect.GetWidth();
                var_f31 = ((1.0f + vec4.x) * (f32)var_r0 * 0.5f) - ((mChanSizeX * mVec2.x) * ((f32)var_r0 / var_f29));
                var_f30 = ((f32)var_r3 - ((1.0f + vec4.y) * (f32)var_r3 * 0.5f)) - (mChanSizeY * mVec2.y);
                var_f29 = 2.0f * (mChanSizeX * mVec2.x) * ((f32)var_r0 / var_f29);
                var_f1 = 2.0f * (mChanSizeY * mVec2.y);
            } else {
                var_r0 = rMode->fbWidth;
                var_r3 = rMode->efbHeight;
                var_f29 = projRect.GetWidth();
                var_f31 = ((f32)var_r0 * 0.5f) + ((vec.x - mChanSizeX) * ((f32)var_r0 / var_f29));
                var_f30 = (((f32)var_r3 * 0.5f) - vec.y) - mChanSizeY;
                var_f29 = 2.0f * mChanSizeX * ((f32)var_r0 / var_f29);
                var_f1 = 2.0f * mChanSizeY;
            }
            var_f31 -= 1.0f;
            var_f30 -= 1.0f;
            var_f29 += 2.0f;
            var_f1 += 2.0f;
            if (var_f31 >= var_r0 || (var_f31 + var_f29) <= 0.0f || var_f30 >= var_r3 || (var_f30 + var_f1) <= 0.0f) {
                GXSetScissor(0, 0, 0, 0);
            } else {
                if (var_f31 < 0.0f) {
                    var_f29 += var_f31;
                    var_f31 = 0.0f;
                }
                if (var_f30 < 0.0f) {
                    var_f1 += var_f30;
                    var_f30 = 0.0f;
                }
                if ((var_f31 + var_f29) > 1705.0f) {
                    var_f29 -= (var_f31 + var_f29) - 1705.0f;
                }
                if ((var_f30 + var_f1) > 1705.0f) {
                    var_f1 -= (var_f30 + var_f1) - 1705.0f;
                }
                GXSetScissor(var_f31, var_f30, var_f29, var_f1);
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813E0BEC(nw4r::math::VEC3* pos, int a) {
            nw4r::ut::Rect projRect;
            System::getProjectionRect(&projRect);

            math::VEC3 vec0(projRect.left, -projRect.top, 0.0f);
            math::VEC3 vec1(pos->x - mChanSizeX, pos->y + mChanSizeY, 0.0f);
            math::VEC3 vec2(projRect.right, -projRect.top, 0.0f);
            math::VEC3 vec3(pos->x + mChanSizeX, pos->y + mChanSizeY, 0.0f);
            math::VEC3 vec4(projRect.left, -projRect.bottom, 0.0f);
            math::VEC3 vec5(pos->x - mChanSizeX, pos->y - mChanSizeY, 0.0f);
            math::VEC3 vec6(projRect.right, -projRect.bottom, 0.0f);
            math::VEC3 vec7(pos->x + mChanSizeX, pos->y - mChanSizeY, 0.0f);

            if (a == 0) {
                mHandlers[0]->init(vec0, vec1, 28.0f, 0.0f, 0.0f, 0);
                mHandlers[1]->init(vec2, vec3, 28.0f, 0.0f, 0.0f, 0);
                mHandlers[2]->init(vec4, vec5, 28.0f, 0.0f, 0.0f, 0);
                mHandlers[3]->init(vec6, vec7, 28.0f, 0.0f, 0.0f, 0);
            } else {
                mHandlers[0]->init(vec1, vec0, 28.0f, 0.0f, 0.0f, 0);
                mHandlers[1]->init(vec3, vec2, 28.0f, 0.0f, 0.0f, 0);
                mHandlers[2]->init(vec5, vec4, 28.0f, 0.0f, 0.0f, 0);
                mHandlers[3]->init(vec7, vec6, 28.0f, 0.0f, 0.0f, 0);
            }
            for (int i = 0; i < 4; i++) {
                mHandlers[i]->play();
            }
        }

        void SDChannelSelect::calcPageAnimations() {
            for (int i = 0; i < 4; i++) {
                mHandlers[i]->calc();
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813E0EE0() {
            nw4r::math::VEC3 frames[3];
            for (int i = 0; i < 3; i++) {
                frames[i] = mHandlers[i]->get();
            }

            nw4r::ut::Rect projRect;
            System::getProjectionRect(&projRect);

            mVec = math::VEC3((frames[0].x + frames[1].x) * 0.5f, (frames[0].y + frames[2].y) * 0.5f, 0.0f);
            mVec2 = math::VEC2(projRect.GetWidth() / (frames[1].x - frames[0].x), projRect.GetHeight() / (frames[0].y - frames[2].y));
        }

        int SDChannelSelect::iplSDChannelSelect_813E114C(const char* name) {
            int i;
            for (i = 0; i < 12; i++) {
                if (strcmp(name, scChanPaneNames[2][i]) == 0) {
                    break;
                }
            }
            return i < 12 ? i : -1;
        }

        void SDChannelSelect::iplSDChannelSelect_813E11C4() {
            mpAnimLayout4 = new layout::Object(getSceneHeap(), mpChanLayoutFile, "arc", "mn_SdcardMenu_d.brlyt");
            mpMoveAnim = mpAnimLayout4->bind("mn_SdcardMenu_d.brlan", true);
            f32 frame = (f32)(System::getRndm()->get_u16() % 2000);
            mpMoveAnim->play();
            mpAnimLayout4->finishBinding();
            mpMoveAnim->setCurrentFrame(frame);

            mpAnimLayout1 = new layout::Object(getSceneHeap(), mpChanLayoutFile, "arc", "my_TVMask_a.brlyt");
            mpAnimLayout1->bind("my_TVMask_a_Apear.brlan", "Picture_00", false);
            mpAnimLayout1->bind("my_TVMask_a_Lost.brlan", "Picture_00", false, false);
            mpAnimLayout1->finishBinding();
            mpAnimLayout1->getAnim()->initAnmFrame();

            mpAnimLayout2 = new layout::Object(getSceneHeap(), mpChanLayoutFile, "arc", "my_TVShade_a.brlyt");
            mpAnimLayout2->bind("my_TVShade_a_Apear.brlan", "4x3", true);
            mpAnimLayout2->bind("my_TVShade_a_Lost.brlan", "4x3", true, false);
            mpAnimLayout2->finishBinding();
            if (SCGetAspectRatio() == SC_ASPECT_RATIO_16x9) {
                GXTexObj tex;
                mpAnimLayout2->FindPaneByName("16x9")->GetMaterial()->GetTexture(&tex, GX_TEXMAP0);
                mpAnimLayout2->FindPaneByName("4x3")->GetMaterial()->SetTexture(GX_TEXMAP0, tex);
                mpAnimLayout2->FindPaneByName("4x3_dummy")->GetMaterial()->SetTexture(GX_TEXMAP0, tex);
            }
            mpAnimLayout2->getAnim()->initAnmFrame();

            mpAnimLayout3 = new layout::Object(getSceneHeap(), mpChanLayoutFile, "arc", "my_TVApear_a.brlyt");
            mpAnimLayout3->bind("my_TVApear_a_Apear.brlan", "Picture_00", false);
            mpAnimLayout3->bind("my_TVApear_a_Lost.brlan", "Picture_00", false, false);
            mpAnimLayout3->finishBinding();
            mpAnimLayout3->getAnim()->initAnmFrame();

            mpAnimLayout5 = new layout::Object(getSceneHeap(), mpChanLayoutFile, "arc", "my_TVMask_a.brlyt");
            mpAnimLayout5->bind("my_TVMask_a_Lost.brlan", "Picture_00", false);
            mpAnimLayout5->finishBinding();

            mDialogAnim = new layout::Object(getSceneHeap(), mpChanLayoutFile, "arc", "wait_icon.brlyt");
            mDialogAnim->bind("wait_icon_wait_loop.brlan", "Wait_00", false);
            mDialogAnim->finishBinding();
            mDialogAnim->getAnim()->initAnmFrame();

            scPages1[2].layoutObj = mDialogAnim;
            scPages2[2].layoutObj = mDialogAnim;
        }

        void SDChannelSelect::iplSDChannelSelect_813E1568() {
            SDButton* button = (SDButton*)System::getSceneManager()->getScene(0x24);
            if (button != NULL && button->isActive()) {
                button->update();
            }
            mpGui->update();

            if (System::getControllerManager()->getController(mCtrlChan) == NULL ||
                !System::getControllerManager()->getController(mCtrlChan)->pinch()) {
                unk_0x104 = 1;
            }
            if (mFieldFC >= 0) {
                mFieldFC++;
            }
            if (mFieldF8 >= 0) {
                mFieldF8++;
            }
            iplSDChannelSelect_813E2750();
            if (!mpAnimLayout1->getAnim(0)->isPlaying() && !mpAnimLayout2->getAnim(0)->isPlaying()) {
                mState = 0x10;
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813E168C() {
            SDButton* button = (SDButton*)System::getSceneManager()->getScene(0x24);
            if (button != NULL && button->isActive()) {
                button->update();
            }
            mpGui->update();

            if (System::getControllerManager()->getController(mCtrlChan) == NULL ||
                !System::getControllerManager()->getController(mCtrlChan)->pinch()) {
                unk_0x104 = 1;
            }
            if (mFieldFC >= 0) {
                mFieldFC++;
            }
            if (mFieldF8 >= 0) {
                mFieldF8++;
            }
            iplSDChannelSelect_813E2750();

            if (unk_0x104 != 0 || unk_0x105 != 0) {
                iplSDChannelSelect_813E24D8();
                return;
            }
            if (mChanPage > 0 && mFieldFC >= 0xF) {
                button->animation(7);
                mpLayout->setMinFrame(0.0f, -1);
                mpLayout->setMaxFrame(20.0f, -1);
                mpLayout->setAnmType(0, -1);
                mpLayout->start(-1);
                mState = 0x16;
                mFieldFC = 0;
                mFieldF8 = -1;
                SDChannelObj* chanObj = NULL;
                while (chanObj = (SDChannelObj*)nw4r::ut::List_GetNext(&mChanList, chanObj), chanObj != NULL) {
                    chanObj->initCursorAnim(true);
                }
                for (int i = 0; i < 0xC; i++) {
                    mpGui->initPane(getChannelPane(i));
                }
                snd::getSystem()->startSE("WSD_SELECT");
            } else if (mChanPage < mChanCount - 1 && mFieldF8 >= 0xF) {
                button->animation(8);
                mpLayout->setMinFrame(40.0f, -1);
                mpLayout->setMaxFrame(60.0f, -1);
                mpLayout->setAnmType(0, -1);
                mpLayout->start(-1);
                mState = 0x17;
                mFieldFC = -1;
                mFieldF8 = 0;
                SDChannelObj* chanObj = NULL;
                while (chanObj = (SDChannelObj*)nw4r::ut::List_GetNext(&mChanList, chanObj), chanObj != NULL) {
                    chanObj->initCursorAnim(true);
                }
                for (int i = 0; i < 0xC; i++) {
                    mpGui->initPane(getChannelPane(i));
                }
                snd::getSystem()->startSE("WSD_SELECT");
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813E195C() {
            if (++mCounter100 > 0x14) {
                layout::Animator* pAnim = mpAnimLayout1->getAnim(1);
                pAnim->initFrame();
                pAnim->restart();
                mState = 0x12;
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813E19C8() {
            if (!mpAnimLayout1->getAnim(1)->isPlaying()) {
                if (!mpAnimLayout2->getAnim(1)->isPlaying()) {
                    mState = 1;
                }
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813E1A30() {
            if (!mpAnimLayout3->getAnim(0)->isPlaying()) {
                if (mSelPage == mFieldF0 && mSelIndex == mFieldF4) {
                    mpAnimLayout3->getAnim(1)->play();
                    mState = 0x15;
                } else {
                    int selEntry = mSelIndex + mSelPage * 0xC;
                    int dstEntry = mFieldF4 + mFieldF0 * 0xC;
                    s32 tmp = mpChanTable[selEntry];
                    mpChanTable[selEntry] = mpChanTable[dstEntry];
                    mpChanTable[dstEntry] = tmp;
                    if (enqueueLoadNotice() != 0) {
                        mFlag758 = 0;
                        goto swap;
                    } else {
                        mpAnimLayout3->getAnim(1)->play();
                        mState = 0x15;
                    }
                    return;
                swap:
                    {
                        mpSwapChanObj = getChanObj(mSelPage, mSelIndex);
                        if (mpSwapChanObj == NULL) {
                            mpSwapChanObj = getChanObj(mFieldF0, mFieldF4);
                            enqueueNotice(mpChanTable[dstEntry], mFieldF0, mFieldF4);
                        } else {
                            SDChannelObj* otherObj = getChanObj(mFieldF0, mFieldF4);
                            mpSwapChanObj->setBasePane(getChannelBasePane(mFieldF0, mFieldF4, mChanPage));
                            otherObj->setBasePane(getChannelBasePane(mSelPage, mSelIndex, mChanPage));
                            s32 dstIndex = mFieldF4;
                            SDChannelObj* swapObj = mpSwapChanObj;
                            s32 dstPage = mFieldF0;
                            swapObj->mChanPage = dstPage;
                            swapObj->mChanIndex = dstIndex;
                            s32 srcIndex = mSelIndex;
                            s32 srcPage = mSelPage;
                            otherObj->mChanPage = srcPage;
                            otherObj->mChanIndex = srcIndex;
                            mpSwapChanObj->calc();
                            otherObj->calc();
                            mpSwapChanObj = NULL;
                            otherObj->mpThumbAnim->setCurrentFrame(mpMoveAnim->getCurrentFrame());
                        }
                        mState = 0x14;
                    }
                }
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813E1C38() {
            if (mFlag758 != 0 && (mpSwapChanObj == NULL || iplSDChannelSelect_813DF1E4(mpSwapChanObj) != 0)) {
                if (mpSwapChanObj != NULL) {
                    mpSwapChanObj = NULL;
                } else {
                    if (mSelPage != -1) {
                        SDChannelObj* objA = getChanObj(mSelPage, mSelIndex);
                        SDChannelObj* objB = getChanObj(mFieldF0, mFieldF4);
                        SDChannelObj* next = (SDChannelObj*)nw4r::ut::List_GetNext(&mChanList, objB);
                        if (next == objA) {
                            next = objB;
                        }
                        nw4r::ut::List_Remove(&mChanList, objB);
                        nw4r::ut::List_Insert(&mChanList, objA, objB);
                        nw4r::ut::List_Remove(&mChanList, objA);
                        nw4r::ut::List_Insert(&mChanList, next, objA);
                    }
                }
                mpAnimLayout3->getAnim(1)->play();
                mState = 0x15;
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813E1D50() {
            if (!mpAnimLayout1->getAnim(1)->isPlaying() && !mpAnimLayout2->getAnim(1)->isPlaying() && !mpAnimLayout3->getAnim(1)->isPlaying()) {
                mpMoveAnim->setCurrentFrame((f32)(u16)(System::getRndm()->get_u16() % 2000));
                mSelPage = -1;
                mSelIndex = -1;
                mDialogAnim->getAnim(0)->stop();
                mDialogAnim->getAnim(0)->initAnmFrame();
                mState = 1;
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813E1E4C() {
            SDButton* button = (SDButton*)System::getSceneManager()->getScene(0x24);
            if (button != NULL && button->isActive()) {
                button->update();
            }
            if (System::getControllerManager()->getController(mCtrlChan) == NULL ||
                !System::getControllerManager()->getController(mCtrlChan)->pinch()) {
                unk_0x104 = 1;
            }
            iplSDChannelSelect_813E2750();

            if (!mpLayout->isPlaying(0)) {
                button = (SDButton*)System::getSceneManager()->getScene(0x24);
                if (mState == 0x16) {
                    mChanPage--;
                    if (mChanPage == 0) {
                        button->animation(0xF);
                        mbFlagC8 = 0;
                    } else if (mbFlagC9 == 0) {
                        button->animation(0xE);
                        mbFlagC9 = 1;
                    }
                } else {
                    mChanPage++;
                    if (mChanPage == mChanCount - 1) {
                        button->animation(0x10);
                        mbFlagC9 = 0;
                    } else if (mbFlagC8 == 0) {
                        button->animation(0xD);
                        mbFlagC8 = 1;
                    }
                }
                mpLayout->finishBinding();
                iplSDChannelSelect_813DF6D0(mChanPage, NULL, -1);
                mState = 0x10;
            }
        }

        int SDChannelSelect::iplSDChannelSelect_813E1FE8(const char* name, int event, controller::Interface* con) {
            if (con != NULL && con != System::getControllerManager()->getController(mCtrlChan)) {
                return 1;
            }
            int index = iplSDChannelSelect_813E114C(name);
            if (index >= 0) {
                switch (event) {
                case 5:
                    if (con->pinch() == 0) {
                        mFieldF4 = index;
                        mFieldF0 = mChanPage;
                        unk_0x104 = 1;
                    }
                    break;
                case 1:
                    if (iplSDChannelSelect_813E26DC(mChanPage, index) != 0 || (mChanPage == mSelPage && index == mSelIndex)) {
                        getChanObj(mChanPage, index)->onPoint(2);
                        snd::getSystem()->startSE("WIPL_SE_CH_TARGETTING");
                        con->rumble(1);
                    }
                    break;
                case 2:
                    if (iplSDChannelSelect_813E26DC(mChanPage, index) != 0 || (mChanPage == mSelPage && index == mSelIndex)) {
                        getChanObj(mChanPage, index)->onLeft(2);
                    }
                    break;
                }
            }
            return 1;
        }

        void SDChannelSelect::iplSDChannelSelect_813E218C(const char* name, int event, controller::Interface* con) {
            if (con == NULL || con == System::getControllerManager()->getController(mCtrlChan)) {
                switch (event) {
                case 2:
                    if (strcmp(name, SDButton::smButtonName[3]) == 0 && mChanPage > 0) {
                        mFieldFC = -1;
                    } else if (strcmp(name, SDButton::smButtonName[2]) == 0 && mChanPage < mChanCount - 1) {
                        mFieldF8 = -1;
                    }
                    break;
                case 1:
                    if (strcmp(name, SDButton::smButtonName[3]) == 0 && mChanPage > 0) {
                        if (mFieldFC < 0) {
                            mFieldFC = 0;
                        }
                    } else if (strcmp(name, SDButton::smButtonName[2]) == 0 && mChanPage < mChanCount - 1 && mFieldF8 < 0) {
                        mFieldF8 = 0;
                    }
                    break;
                }
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813E22F8(controller::Interface* con, int page, int index) {
            if (con->getChannel() >= 0) {
                if (con->isValidDpd()) {
                    mCursorPos = con->getDpdPos();
                } else {
                    mCursorPos = nw4r::math::VEC2(0.0f, 0.0f);
                }
                mCtrlChan = con->getChannel();
                mSelPage = page;
                mSelIndex = index;
                mFieldF0 = -1;
                mFieldF4 = -1;
                mFieldF8 = -1;
                mFieldFC = -1;
                mCounter100 = 0;
                unk_0x104 = 0;
                unk_0x105 = 0;
                System::getPointer()->changeType(con->getChannel(), 1);
                mpAnimLayout1->getAnim(0)->play();
                mpAnimLayout2->getAnim(0)->play();
                ((SDButton*)System::getSceneManager()->getScene(0x24))->disableBtn();
                SDChannelObj* chanObj = NULL;
                while ((chanObj = (SDChannelObj*)nw4r::ut::List_GetNext(&mChanList, chanObj)) != NULL) {
                    chanObj->onPinch(chanObj->mChanPage == page && chanObj->mChanIndex == index);
                }
                snd::getSystem()->startSEwithPos("WIPL_SE_CH_HOLD", mCursorPos.x);
                mState = 0xF;
            }
        }

        void SDChannelSelect::iplSDChannelSelect_813E24D8() {
            if (iplSDChannelSelect_813E26DC(mFieldF0, mFieldF4) != 0 && unk_0x105 == 0) {
                nw4r::math::VEC3 translate = getChanObj(mFieldF0, mFieldF4)->getTranslate();
                mpAnimLayout3->GetRootPane()->SetTranslate(translate);
                mpAnimLayout3->getAnim(0)->play();
                mDialogAnim->GetRootPane()->SetTranslate(translate);
                mDialogAnim->calcMtx();
                mDialogAnim->getAnim(0)->play();
                snd::getSystem()->startSEwithPos("WIPL_SE_CH_SET", mCursorPos.x);
                mpAnimLayout1->getAnim(1)->play();
                mState = 0x13;
            } else {
                snd::getSystem()->startSEwithPos("WIPL_SE_CH_NOT_MOVE", mCursorPos.x);
                mState = 0x11;
            }
            System::getPointer()->changeType(mCtrlChan, 0);
            mpAnimLayout2->getAnim(1)->play();
            ((SDButton*)System::getSceneManager()->getScene(0x24))->enableBtn();
            unk_0x104 = 0;
            unk_0x105 = 0;
            SDChannelObj* chanObj = NULL;
            while (chanObj = (SDChannelObj*)nw4r::ut::List_GetNext(&mChanList, chanObj), chanObj != NULL) {
                chanObj->initCursorAnim(true);
            }
            for (int i = 0; i < 0xC; i++) {
                mpGui->initPane(getChannelPane(i));
            }
        }

        int SDChannelSelect::iplSDChannelSelect_813E26DC(int page, int index) {
            if (page < 0 || page >= mChanCount) {
                return 0;
            }
            if (index < 0 || index >= 12) {
                return 0;
            }
            if (page == mSelPage && index == mSelIndex) {
                return 1;
            }
            return mpChanTable[page * 12 + index] == 0;
        }

        void SDChannelSelect::iplSDChannelSelect_813E2750() {
            if (System::getControllerManager()->getController(mCtrlChan) != NULL &&
                System::getControllerManager()->getController(mCtrlChan)->isValidDpd()) {
                math::VEC2 pos = System::getControllerManager()->getController(mCtrlChan)->getDpdProjectionPos();
                nw4r::math::VEC3 newPos(pos.x, -pos.y, 0.0f);
                mpAnimLayout2->GetRootPane()->SetTranslate(newPos);
                mpAnimLayout2->calcMtx();

                f32 speed;

                math::VEC2 delta;
                delta.y = pos.y - mCursorPos.y;
                delta.x = pos.x - mCursorPos.x;

                f32 val = (delta.x * delta.x) + (delta.y * delta.y);

                if (val <= 0.0f) {
                    speed = 0.0f;
                } else {
                    speed = (val * nw4r::math::FrSqrt(val));
                }

                snd::getSystem()->holdSEwithPosDis("WIPL_SE_CH_DRAG", pos.x, speed);
                mCursorPos = pos;
            }
        }

        void SDChannelSelectEvent::onEvent(u32 compId, u32 event, void* data) {
            controller::Interface* con = (controller::Interface*)data;
            gui::PaneComponent* component = static_cast<gui::PaneComponent*>(mpManager->getComponent(compId));
            const char* paneName = component->getPane()->GetName();

            int result = 0;
            if (mpScene->mState < 0x11 && mpScene->mState >= 0xF) {
                result = mpScene->iplSDChannelSelect_813E1FE8(paneName, event, (controller::Interface*)con);
            }
            if (result == 0) {
                int index = mpScene->iplSDChannelSelect_813E114C(paneName);
                if (index >= 0) {
                    SDChannelObj* chanObj = mpScene->getChanObj(mpScene->mChanPage, index);
                    if (chanObj != NULL) {
                        switch (event) {
                        case ::gui::EventHandler::ON_TRIG: {
                            if (mpScene->mState == 1 && con != NULL) {
                                int wp = mpScene->mpWorker->is_sd_write_protected();
                                if (con->pinchTrg() && chanObj->isValid() != 0 && mpScene->mFlag75A == 0) {
                                    if (wp == 0) {
                                        mpScene->iplSDChannelSelect_813E22F8((controller::Interface*)con, mpScene->mChanPage, index);
                                    } else if (mpScene->unk_0x77D == 0 && System::getDialog()->callBtn1(0xC6, 0x2E) != 0) {
                                        mpScene->unk_0x77D = 1;
                                        mpScene->mState = 0x1D;
                                    }
                                }
                            }
                            break;
                        }
                        case ::gui::EventHandler::ON_DRAG: {
                            if (mpScene->mState == 1 && con != NULL &&
                                ((controller::Interface*)con)->decide() && chanObj->isValid() != 0) {
                                mpScene->iplSDChannelSelect_813E0450(chanObj->mChanPage, chanObj->mChanIndex);
                                TVRCManager::getHandle()->setEnable(0);
                            }
                            break;
                        }
                        case 1: {
                            if (mpScene->mState == 1 && chanObj->isValid() != 0) {
                                chanObj->onPoint(0);
                                snd::getSystem()->startSE("WIPL_SE_CH_TARGETTING");
                                ((controller::Interface*)con)->rumble(1);
                            }
                            break;
                        }
                        case ::gui::EventHandler::ON_LEFT: {
                            if (mpScene->mState == 1 && chanObj->isValid() != 0) {
                                chanObj->onLeft(0);
                            }
                            break;
                        }
                        }
                    }
                }
            }
        }

        void SDChannelSelectBtnEvent::onEventDerived(u32 compId, u32 event, const controller::Interface* con) {
            gui::PaneComponent* component = static_cast<gui::PaneComponent*>(mpManager->getComponent(compId));
            const char* paneName = component->getPane()->GetName();

            if (mpScene->mState >= 0xF && (mpScene->mState < 0x11 || (mpScene->mState >= 0x16 && mpScene->mState < 0x18))) {
                mpScene->iplSDChannelSelect_813E218C(paneName, event, (controller::Interface*)con);
                return;
            }
            if (event == ::gui::EventHandler::ON_TRIG && mpScene->mState == 1 &&
                System::getFader()->getStatus() == EGG::Fader::PREPARE_OUT &&
                con != NULL && con->downTrg(controller::BTN_INTERACT)) {
                SDButton* button = (SDButton*)System::getSceneManager()->getScene(0x24);
                if (strcmp(paneName, SDButton::smButtonName[1]) == 0) {
                    mpScene->unk_0x754 = 0;
                    mpScene->mState = 0x1A;
                    button->animation(4);
                    snd::getSystem()->startSE("WIPL_SE_DECIDE");
                } else if (strcmp(paneName, SDButton::smButtonName[0]) == 0) {
                    setEventHandler__Q33ipl5scene8SDButtonFPQ23gui12EventHandlerPQ23gui12EventHandler(button, NULL);
                    mpScene->mState = 4;
                    snd::getSystem()->startSE("WIPL_SE_DECIDE");
                } else if (strcmp(paneName, SDButton::smButtonName[3]) == 0 && mpScene->mChanPage > 0) {
                    button->animation(7);
                    mpScene->iplSDChannelSelect_813E0398(8);
                } else if (strcmp(paneName, SDButton::smButtonName[2]) == 0 && mpScene->mChanPage < mpScene->mChanCount - 1) {
                    button->animation(8);
                    mpScene->iplSDChannelSelect_813E0398(9);
                }
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
            arguments = other.arguments;
        }

        BOOL SDChannelSelectNoticeQueue::pop() {
            BOOL ret = TRUE;
            if (mCount == 0) {
                ret = FALSE;
            } else {
                if (++mRead >= mCap) {
                    mRead = 0;
                }
                mCount--;
            }
            return ret;
        }

        BOOL SDChannelSelectCommandQueue::push(const SDChannelSelectCommand& command) {
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

        BOOL SDChannelSelectCommandQueue::pop() {
            BOOL ret = TRUE;
            if (mCount == 0) {
                ret = FALSE;
            } else {
                if (++mRead >= mCap) {
                    mRead = 0;
                }
                mCount--;
            }
            return ret;
        }

        nw4r::math::VEC3 SDChannelSelect::getChannelPanePosition(SDChannelSelect* scene, int index) {
            nw4r::math::VEC3 position(0.0f, 0.0f, 0.0f);
            PSMTXMultVec(scene->getCenterChannelPane(index)->GetGlobalMtx(), position, position);
            return position;
        }
    }
}
