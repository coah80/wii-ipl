#define IPL_MEMORY_CARD_CPP
#define IPL_MEMORY_CARD_NOVTABLE
#include "scene/memoryCard/iplMemoryCard.h"

#include "scene/memoryCard/iplGCWindow.h"
#include "scene/memoryCard/iplGCSaveData.h"

#include <cstring>
#include <cwchar>

#include "iplSystem.h"
#include "scene/iplSceneCreator.h"
#include "scene/settingSelect/iplSettingButton.h"
#include "scene/settingSelect/iplSettingSelect.h"
#include "scene/textBalloon/iplBalloon.h"
#include "private/card.h"
#include "sound/iplSound.h"
#include "system/iplController.h"
#include "system/iplNandManager.h"
#include "utility/iplGraphics.h"

namespace ipl {
    namespace scene {
        static const char* scSavedataPaneName[] = {
            "N_Data_a_00", "N_Data_a_01", "N_Data_a_02", "N_Data_a_03", "N_Data_a_04",
            "N_Data_a_05", "N_Data_a_06", "N_Data_a_07", "N_Data_a_08", "N_Data_a_09",
            "N_Data_a_10", "N_Data_a_11", "N_Data_a_12", "N_Data_a_13", "N_Data_a_14",
            "N_Data_b_00", "N_Data_b_01", "N_Data_b_02", "N_Data_b_03", "N_Data_b_04",
            "N_Data_b_05", "N_Data_b_06", "N_Data_b_07", "N_Data_b_08", "N_Data_b_09",
            "N_Data_b_10", "N_Data_b_11", "N_Data_b_12", "N_Data_b_13", "N_Data_b_14",
            "N_Data_c_00", "N_Data_c_01", "N_Data_c_02", "N_Data_c_03", "N_Data_c_04",
            "N_Data_c_05", "N_Data_c_06", "N_Data_c_07", "N_Data_c_08", "N_Data_c_09",
            "N_Data_c_10", "N_Data_c_11", "N_Data_c_12", "N_Data_c_13", "N_Data_c_14",
        };

        static const MemoryBase::AnmName scAnmName[] = {
            {"it_ObjCubeEdit_a_CubeSwitch.brlan", "G_Switch"},
            {"it_ObjCubeEdit_a_DataIn.brlan", "G_DataAll"},
            {"it_ObjCubeEdit_a_SelectIn.brlan", "G_SelectWii"},
            {"it_ObjCubeEdit_a_SelectIn.brlan", "G_SelectSd"},
            {"it_ObjCubeEdit_a_DataOut.brlan", "G_DataAll"},
            {"it_ObjCubeEdit_a_SelectIn.brlan", "G_Select"},
            {"it_ObjCubeEdit_a_SelectWiiFoucusIn.brlan", "G_SelectWii"},
            {"it_ObjCubeEdit_a_SelectWiiFoucusOut.brlan", "G_SelectWii"},
            {"it_ObjCubeEdit_a_SelectWiiFlash.brlan", "G_Select"},
            {"it_ObjCubeEdit_a_SelectSdIn.brlan", "G_SelectSd"},
            {"it_ObjCubeEdit_a_SelectSdOut.brlan", "G_SelectSd"},
            {"it_ObjCubeEdit_a_SelectSdFlash.brlan", "G_Select"},
            {"it_ObjCubeEdit_a_ArwL1.brlan", "G_Arw"},
            {"it_ObjCubeEdit_a_AwrR1.brlan", "G_Arw"},
            {"it_ObjCubeEdit_a_Select.brlan", "G_ArwR_Ac"},
            {"it_ObjCubeEdit_a_Select.brlan", "G_ArwL_Ac"},
            {"it_ObjCubeEdit_a_FocusOn.brlan", "G_ArwR_Focus"},
            {"it_ObjCubeEdit_a_FocusOn.brlan", "G_ArwL_Focus"},
            {"it_ObjCubeEdit_a_FocusOff.brlan", "G_ArwR_Focus"},
            {"it_ObjCubeEdit_a_FocusOff.brlan", "G_ArwL_Focus"},
            {"it_ObjCubeEdit_a_Loop.brlan", "G_ArwRoop"},
            {"it_ObjCubeEdit_a_Appear.brlan", "G_ArwR_End"},
            {"it_ObjCubeEdit_a_Appear.brlan", "G_ArwL_End"},
            {"it_ObjCubeEdit_a_Lost.brlan", "G_ArwR_End"},
            {"it_ObjCubeEdit_a_Lost.brlan", "G_ArwL_End"},
            {"it_ObjCubeEdit_a_ErrorTxtIn.brlan", "G_ErrorTxt"},
            {"it_ObjCubeEdit_a_ErrorTxtOut.brlan", "G_ErrorTxt"},
        };

        struct TextboxMessage {
            const char* paneName;
            u32 messageId;
        };

        static const TextboxMessage scTextboxToMessageID[] = {
            {"T_SelectWii_00", 0x13F},
            {"T_SelectWii_01", 0x13F},
            {"T_SelectSd_00", 0x140},
            {"T_SelectSd_01", 0x140},
            {"T_Error_00", 0xE6},
        };

        static const char* scTriggerPaneName[] = {
            "B_ArwR", "B_ArwL", "B_SelectWii_00", "B_SelectSd_00",
        };

        struct DigitTable {
            wchar_t w[10];
        };

        static const DigitTable scNumber = {{L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9'}};

        class __declspec(novtable) MemoryCardManagerImpl : public MemoryCardManager {
        public:
            virtual void onMount(u8) {}
            virtual void onUnmount(u8) {}
            virtual void onAttach(u8) {}
            virtual void onDetach(u8) {}
            virtual void onCheck(u8) {}
            virtual void onFormat(u8) {}
            virtual void onRepair(u8) {}
            virtual void onRead(u8) {}
            virtual void onWrite(u8) {}
            virtual void onOpen(u8) {}
            virtual void onClose(u8) {}
            virtual void onCreate(u8) {}
            virtual void onDelete(u8) {}
            virtual void onCopy(u8) {}
            virtual void onMove(u8) {}
            virtual void onRename(u8) {}
            virtual void onVerify(u8) {}
            virtual void onCommit(u8) {}
            virtual void onProbe(u8) {}
            virtual void onMountAsync(u8) {}
            virtual void onUnmountAsync(u8) {}
            virtual void onCheckAsync(u8) {}
            virtual void onFormatAsync(u8) {}
            virtual void onReadAsync(u8) {}
            virtual void onWriteAsync(u8) {}
            virtual void onCreateAsync(u8) {}
            virtual void onDeleteAsync(u8) {}
            virtual void onCopyAsync(u8) {}
            virtual void onMoveAsync(u8) {}
            virtual void onRenameAsync(u8) {}
            virtual void onVerifyAsync(u8) {}
            virtual void onCommitAsync(u8) {}
            virtual void onProbeAsync(u8) {}
            virtual void onFreeBlocks(u8) {}
            virtual void onGetLength(u8) {}
            virtual void onSetAttrib(u8) {}
            virtual void onGetAttrib(u8) {}
        };

        MemoryCard::MemoryCard(EGG::Heap* heap)
            : Base(heap), MemoryBase(), mState(2), mPrevState(2), mSlot(0), mIconIndex(-15), mIconCount(0),
              mShowArwR(0), mShowArwL(0), mpEvent(NULL), mpFocusSaveData(NULL) {
            System::getMem2App()->dump();
            nw4r::ut::List_Init(&mSaveDataList, offsetof(GCSaveData, mLink));
            nw4r::ut::List_Init(&mBalloonList, 0);
        }


        void MemoryCard::prepare() {
            System::getBS2Manager()->abort();
            unk_0x08 = System::getNandManager()->readLayoutAsync(getSceneHeap(), "gcMem.ash");
            mBalloonLayoutFile = System::getNandManager()->readLayoutAsync(getSceneHeap(), "balloon.ash");
        }

        void MemoryCard::create() {
            u32 start = OSGetTick();
            while (System::getBS2Manager()->getIPLState() != 8) {
                System::getBS2Manager()->update();
                OSReport(" ... wait for bs2 abord\n");
                VIWaitForRetrace();
            }
            u32 end = OSGetTick();
            OSReport("*** BS2 abort costs: %dms\n", OSTicksToMilliseconds(end - start));
            ES_SetUid((u64(1) << 32) | 2);

            mpLayout = new layout::Object(getSceneHeap(), unk_0x08, "arc", "it_ObjCubeEdit_a.brlyt");
            add_animation(scAnmName, 0x1B);
            get_animation(7)->mAnim->setAnmType(1);
            get_animation(10)->mAnim->setAnmType(1);
            mpLayout->finishBinding();
            do_animation(0);
            do_animation(1);
            do_animation(0x14);
            do_animation(0x17);
            do_animation(0x18);
            mPrevState = mState;
            mState = 0;
            mpLayout->FindPaneByName("N_ArwR")->SetVisible(false);
            mpLayout->FindPaneByName("N_ArwL")->SetVisible(false);

            mpEvent = new MemoryBaseEvent(this);
            mpPaneManager = new gui::PaneManager(mpEvent, mpLayout->getDrawInfo(), NULL, NULL, true);
            mpPaneManager->setupScene(mpLayout);
            mpPaneManager->setAllComponentTriggerTarget(false);

            for (int i = 0; i < 4; i++) {
                nw4r::lyt::Pane* pane = mpLayout->FindPaneByName(scTriggerPaneName[i]);
                mpPaneManager->setTriggerTarget(pane, true);
            }

            add_anmbutton(scTriggerPaneName[2], get_animation(6), get_animation(7), get_animation(8));
            add_anmbutton(scTriggerPaneName[3], get_animation(9), get_animation(10), get_animation(11));
            add_anmbutton(scTriggerPaneName[0], get_animation(16), get_animation(18), get_animation(12));
            add_anmbutton(scTriggerPaneName[1], get_animation(17), get_animation(19), get_animation(13));

            for (int i = 0; i < 5; i++) {
                set_textbox(scTextboxToMessageID[i].paneName, scTextboxToMessageID[i].messageId);
            }

            mpGCWindow = new GCWindow(getSceneHeap(), unk_0x08, "arc", "it_CubeDetail_a.brlyt");
            mpGCWindow->do_animation(0);

            MemoryCardManager* manager = new MemoryCardManagerImpl();
            mpManager = manager;
            mpManager->setEventHandler(mpGCWindow);
            mpGCWindow->mpMemoryCardManager = mpManager;

            for (int i = 0; i < 0x2D; i++) {
                nw4r::lyt::Pane* pane = mpLayout->FindPaneByName(scSavedataPaneName[i]);
                nw4r::math::VEC3 position(0.0f, 0.0f, 0.0f);
                PSMTXMultVec(pane->GetGlobalMtx(), reinterpret_cast<const Vec*>(&position), reinterpret_cast<Vec*>(&position));
                GCSaveData* saveData =
                    new GCSaveData(getSceneHeap(), unk_0x08, "arc", "it_ObjCubeEdit_b.brlyt", position);
                saveData->set_visible("N_Data_00", false);
                nw4r::ut::List_Append(&mSaveDataList, saveData);
                if (i >= 0xF && i < 0x1E) {
                    position.y -= 55.0f;
                    TextBalloon* balloon =
                        new TextBalloon(getSceneHeap(), mBalloonLayoutFile, "arc", "my_IplTopBalloon_a.brlyt",
                                        math::VEC3(position), 90.0f, 60.0f);
                    nw4r::ut::List_Append(&mBalloonList, balloon);
                    saveData->setBalloon(balloon);
                }
            }
            for (int i = 0; i < 2; i++) {
                mSlotState[i] = 0;
            }
            set_visible("N_Capa_00", false);
            set_visible("T_Error_00", false);
        }

        void MemoryCard::calc() {
            mpManager->calc();
            if (is_fadein_enable()) {
                mpLayout->calc();
                mpPaneManager->calc();
                s16 index = mIconIndex;
                mIconCount = 0;
                GCSaveData* saveData = NULL;
                while ((saveData = static_cast<GCSaveData*>(nw4r::ut::List_GetNext(&mSaveDataList, saveData))) != NULL) {
                    if (mpManager->isIconValidate(mSlot, index) || index < 0) {
                        mIconCount++;
                    }
                    saveData->mSlot = mSlot;
                    saveData->mIndex = index;
                    saveData->calc();
                    index++;
                }
                MemoryBase::AnmButton* button = NULL;
                while ((button = static_cast<MemoryBase::AnmButton*>(nw4r::ut::List_GetNext(&mAnmButtonList, button))) != NULL) {
                    button->calc();
                }
                TextBalloon* balloon = NULL;
                while ((balloon = static_cast<TextBalloon*>(nw4r::ut::List_GetNext(&mBalloonList, balloon))) != NULL) {
                    balloon->calc();
                }
                switch (mState) {
                case 0:
                    on_fadein1st();
                    break;
                case 1:
                    on_fadein2nd();
                    break;
                case 2:
                    on_normal();
                    break;
                case 3:
                    on_scroll_r();
                    break;
                case 4:
                    on_scroll_l();
                    break;
                case 5:
                    on_change_tag1st();
                    break;
                case 6:
                    on_change_tag2nd();
                    break;
                case 7:
                    on_fadeout1st();
                    break;
                case 8:
                    on_fadeout2nd();
                    break;
                case 9:
                    mpGCWindow->calc();
                    show_capacity(mSlot);
                    break;
                case 10:
                    on_error();
                    break;
                case 11:
                    on_insert_card();
                    break;
                case 12:
                    on_detach_card();
                    break;
                }
            }
        }

        void MemoryCard::on_fadein1st() {
            if (!is_animation(1)) {
                do_animation(5);
                mpLayout->FindPaneByName("N_ArwR")->SetVisible(true);
                mpLayout->FindPaneByName("N_ArwL")->SetVisible(true);
                if (mpManager->isSlotReady(mSlot)) {
                    mSlotState[mSlot] = 1;
                    start_savedata_fadein();
                    mPrevState = mState;
                    mState = 1;
                } else {
                    start_errormessage_fadein();
                    mPrevState = mState;
                    mState = 10;
                }
            }
        }

        void MemoryCard::on_fadein2nd() {
            GCSaveData* saveData = static_cast<GCSaveData*>(nw4r::ut::List_GetNext(&mSaveDataList, NULL));
            if (!is_animation(5) && !saveData->is_animation(0)) {
                mPrevState = mState;
                mState = 2;
            }
        }

        void MemoryCard::on_normal() {
            if (get_setting_button()->update()) {
                if (mPrevState == 10) {
                    do_animation(0x1A);
                }
                mPrevState = mState;
                mState = 7;
                return;
            }
            show_arw();
            show_capacity(mSlot);
            if (!update_slot()) {
                mpPaneManager->update();
                GCSaveData* saveData = NULL;
                while ((saveData = static_cast<GCSaveData*>(nw4r::ut::List_GetNext(&mSaveDataList, saveData))) != NULL) {
                    saveData->update();
                }
                mpGCWindow->calc();
                if (mIconCount <= 15) {
                    bool canScroll = false;
                    if (mIconIndex >= 0 && mState == 2) {
                        canScroll = true;
                    }
                    if (canScroll) {
                        start_scroll_l();
                        return;
                    }
                }
                controller::Interface* controller = System::getYoungController();
                if (controller != NULL) {
                    if (controller->down(0x30001000)) {
                        start_scroll_l();
                    } else if (controller->down(0x06000010)) {
                        start_scroll_r();
                    }
                }
            }
        }

        void MemoryCard::on_scroll_r() {
            if (!is_animation(0xC)) {
                get_animation(0xC)->mAnim->initAnmFrame();
                mpLayout->calc();
                mState = 2;
                mIconIndex += 0xF;
            }
            scroll_common();
        }

        void MemoryCard::on_scroll_l() {
            if (!is_animation(0xD)) {
                get_animation(0xC)->mAnim->initAnmFrame();
                mpLayout->calc();
                mState = 2;
                mIconIndex -= 0xF;
            }
            scroll_common();
        }

        void MemoryCard::on_change_tag1st() {
            GCSaveData* first = static_cast<GCSaveData*>(nw4r::ut::List_GetNext(&mSaveDataList, NULL));
            if (!first->is_animation(1)) {
                GCSaveData* saveData = NULL;
                while ((saveData = static_cast<GCSaveData*>(nw4r::ut::List_GetNext(&mSaveDataList, saveData))) != NULL) {
                    saveData->set_visible("N_Data_00", false);
                }
                mSlot ^= 1;
                mSlotState[mSlot] = 0;
                mIconIndex = -15;
                mPrevState = mState;
                mState = 2;
            }
        }

        void MemoryCard::on_change_tag2nd() {
            GCSaveData* saveData = NULL;
            while ((saveData = static_cast<GCSaveData*>(nw4r::ut::List_GetNext(&mSaveDataList, saveData))) != NULL) {
                if (!saveData->is_animation(0)) {
                    mState = 2;
                    break;
                }
            }
        }

        void MemoryCard::on_fadeout1st() {
            if (!get_setting_button()->isPlaying()) {
                do_animation(4);
                GCSaveData* saveData = NULL;
                while ((saveData = static_cast<GCSaveData*>(nw4r::ut::List_GetNext(&mSaveDataList, saveData))) != NULL) {
                    saveData->do_animation(1);
                }
                mState = 8;
            }
        }

        void MemoryCard::on_fadeout2nd() {
            if (!is_animation(4)) {
                bool shutdown = memorycard::shutdownCardThread();
                if (shutdown) {
                    requestSceneDestruction();
                    System::getBS2Manager()->restart();
                    OSReport(" ... bs2 manager restarted\n");
                }
            }
        }

        void MemoryCard::on_error() {
            if (!is_animation(0x19)) {
                mPrevState = mState;
                mState = 2;
            }
        }

        void MemoryCard::on_insert_card() {
            if (!is_animation(0x1A)) {
                start_savedata_fadein();
                mPrevState = mState;
                mState = 1;
            }
        }

        void MemoryCard::on_detach_card() {
            GCSaveData* first = static_cast<GCSaveData*>(nw4r::ut::List_GetNext(&mSaveDataList, NULL));
            if (!first->is_animation(1)) {
                start_errormessage_fadein();
                mPrevState = mState;
                mState = 10;
                GCSaveData* saveData = NULL;
                while ((saveData = static_cast<GCSaveData*>(nw4r::ut::List_GetNext(&mSaveDataList, saveData))) != NULL) {
                    saveData->set_visible("N_Data_00", false);
                }
            }
        }

        void MemoryCard::start_savedata_fadein() {
            GCSaveData* saveData = NULL;
            while ((saveData = static_cast<GCSaveData*>(nw4r::ut::List_GetNext(&mSaveDataList, saveData))) != NULL) {
                saveData->set_visible("N_Data_00", true);
                saveData->do_animation(0);
            }
        }

        void MemoryCard::start_savedata_fadeout() {
            GCSaveData* saveData = NULL;
            while ((saveData = static_cast<GCSaveData*>(nw4r::ut::List_GetNext(&mSaveDataList, saveData))) != NULL) {
                saveData->do_animation(1);
            }
            set_visible("N_Capa_00", false);
        }

        void MemoryCard::start_errormessage_fadein() {
            if (mpManager->isSlotWrongDevice(mSlot) != 0) {
                mSlotState[mSlot] = 3;
                set_textbox("T_Error_00", mSlot == 0 ? 0xE8 : 0xE9);
            } else {
                mSlotState[mSlot] = 2;
                set_textbox("T_Error_00", mSlot == 0 ? 0xE6 : 0xE7);
            }
            set_visible("T_Error_00", true);
            do_animation(0x19);
        }

        int MemoryCard::update_slot() {
            if (mSlotState[mSlot] != 1 && mpManager->isSlotReady(mSlot) != 0) {
                for (u16 i = 0xF; i < 0x1E; i++) {
                    static_cast<GCSaveData*>(nw4r::ut::List_GetNth(&mSaveDataList, i))->init();
                }
                mSlotState[mSlot] = 1;
                if (mPrevState == 10) {
                    do_animation(0x1A);
                }
                mPrevState = mState;
                mState = 0xB;
                return true;
            }
            if (mSlotState[mSlot] != 2 && mpManager->isSlotNoCard(mSlot) != 0) {
                for (u16 i = 0xF; i < 0x1E; i++) {
                    static_cast<GCSaveData*>(nw4r::ut::List_GetNth(&mSaveDataList, i))->init();
                }
                mSlotState[mSlot] = 2;
                mIconIndex = -15;
                start_savedata_fadeout();
                mPrevState = mState;
                mState = 0xC;
                return true;
            }
            if ((mSlotState[mSlot] != 3 && mpManager->isSlotWrongDevice(mSlot) != 0) || mSlotState[mSlot] == 0) {
                for (u16 i = 0xF; i < 0x1E; i++) {
                    static_cast<GCSaveData*>(nw4r::ut::List_GetNth(&mSaveDataList, i))->init();
                }
                mSlotState[mSlot] = 3;
                start_savedata_fadeout();
                mPrevState = mState;
                mState = 0xC;
                return true;
            }
            return false;
        }

        void MemoryCard::show_arw() {
            if (mShowArwR == 0 && can_scroll_r()) {
                do_animation(0x15);
                do_animation(0x12);
                mShowArwR = 1;
            } else if (mShowArwR != 0 && !can_scroll_r()) {
                do_animation(0x17);
                mShowArwR = 0;
            }
            if (mShowArwL == 0 && can_scroll_l()) {
                do_animation(0x16);
                do_animation(0x13);
                mShowArwL = 1;
            } else if (mShowArwL != 0 && !can_scroll_l()) {
                do_animation(0x18);
                mShowArwL = 0;
            }
        }

        void MemoryCard::show_capacity(u8 slot) {
            if (!mpManager->isSlotReady(slot)) {
                set_visible("N_Capa_00", false);
                return;
            }
            u32 freeBlocks = mpManager->getFreeBlocks(slot);
            DigitTable digitTable = scNumber;
            wchar_t digits[5] = {0};
            wchar_t text[0x40] = L"";
            int blocks = static_cast<u16>(freeBlocks);
            digits[0] = digitTable.w[blocks / 1000];
            digits[1] = digitTable.w[blocks / 100 % 10];
            digits[2] = digitTable.w[blocks / 10 % 10];
            digits[3] = digitTable.w[blocks % 10];

            int zeroOffset;
            for (zeroOffset = 0; zeroOffset < 3; zeroOffset++) {
                if (digits[zeroOffset] != L'0') {
                    break;
                }
            }

            int blockOpenOffset = 0;
            const wchar_t* blockOpenMessage = System::getMessage(0x9C);
            const wchar_t* blankMessage = System::getMessage(0xF2);

            while (true) {
                wchar_t chr = *blockOpenMessage++;
                text[blockOpenOffset++] = chr;
                if (chr == L'\0') {
                    break;
                }
            }
            text[--blockOpenOffset] = L' ';
            wcscpy(text + blockOpenOffset, digits + zeroOffset);
            wcscat(text, blankMessage);

            set_textbox("T_Capa_00", text);
            set_visible("N_Capa_00", true);
        }

        void MemoryCard::scroll_common() {
            for (u16 i = 0; i < 0x2D; i++) {
                nw4r::lyt::Pane* pane = mpLayout->FindPaneByName(scSavedataPaneName[i]);
                GCSaveData* saveData = static_cast<GCSaveData*>(nw4r::ut::List_GetNth(&mSaveDataList, i));
                nw4r::math::VEC3 position(0.0f, 0.0f, 0.0f);
                PSMTXMultVec(pane->GetGlobalMtx(), reinterpret_cast<const Vec*>(&position), reinterpret_cast<Vec*>(&position));
                saveData->setTranslate(position);
                saveData->init();
            }
        }

        void MemoryCard::start_scroll_r() {
            bool canScroll = false;
            if (mIconCount > 0x1E && mState == 2) {
                canScroll = true;
            }
            if (canScroll) {
                do_animation(0xC);
                mState = 3;
                snd::getSystem()->startSE("WSD_SELECT");
                GCSaveData* saveData = NULL;
                while ((saveData = static_cast<GCSaveData*>(nw4r::ut::List_GetNext(&mSaveDataList, saveData))) != NULL) {
                    saveData->init();
                }
            }
        }

        void MemoryCard::start_scroll_l() {
            bool canScroll = false;
            if (mIconIndex >= 0 && mState == 2) {
                canScroll = true;
            }
            if (canScroll) {
                do_animation(0xD);
                mState = 4;
                snd::getSystem()->startSE("WSD_SELECT");
                GCSaveData* saveData = NULL;
                while ((saveData = static_cast<GCSaveData*>(nw4r::ut::List_GetNext(&mSaveDataList, saveData))) != NULL) {
                    saveData->init();
                }
            }
        }

        void MemoryCard::draw() {
            if (System::onDefaultDrawLayer()) {
                utility::Graphics::setOrtho(0);
                mpLayout->draw();
                GCSaveData* saveData = NULL;
                while ((saveData = static_cast<GCSaveData*>(nw4r::ut::List_GetNext(&mSaveDataList, saveData))) != NULL) {
                    saveData->draw();
                }
                mpLayout->draw("N_ArwR");
                mpLayout->draw("N_ArwL");
                if (mpFocusSaveData != NULL) {
                    mpGCWindow->draw();
                }
                if (mState == 2) {
                    TextBalloon* balloon = NULL;
                    while ((balloon = static_cast<TextBalloon*>(nw4r::ut::List_GetNext(&mBalloonList, balloon))) != NULL) {
                        balloon->draw();
                    }
                }
            }
        }

        void MemoryCard::onPoint(const char* paneName, controller::Interface* controller) {
            MemoryBase::AnmButton* button = get_anmbutton(paneName);
            if (button != NULL) {
                if (button->unk_0x04 == 0 &&
                    (strcmp(paneName, scTriggerPaneName[2]) != 0 || mSlot != 0) &&
                    (strcmp(paneName, scTriggerPaneName[3]) != 0 || mSlot != 1)) {
                    button->onCmdRecv(1);
                    snd::getSystem()->startSE("WIPL_SE_BT_TARGETTING");
                    if (controller != NULL) {
                        controller->rumble(0);
                    }
                }
                button->unk_0x04++;
            }
        }

        void MemoryCard::onLeft(const char* paneName) {
            MemoryBase::AnmButton* button = get_anmbutton(paneName);
            if (button != NULL) {
                if (button->unk_0x04 == 1 &&
                    (strcmp(paneName, scTriggerPaneName[2]) != 0 || mSlot != 0) &&
                    (strcmp(paneName, scTriggerPaneName[3]) != 0 || mSlot != 1)) {
                    button->onCmdRecv(2);
                }
                button->unk_0x04--;
            }
        }

        void MemoryCard::onTrig(const char* paneName) {
            if (mpFocusSaveData == NULL && get_anmbutton(paneName) != NULL) {
                if (strcmp(paneName, scTriggerPaneName[0]) == 0) {
                    do_animation(0xE);
                    start_scroll_r();
                } else if (strcmp(paneName, scTriggerPaneName[1]) == 0) {
                    do_animation(0xF);
                    start_scroll_l();
                } else if (strcmp(paneName, scTriggerPaneName[2]) == 0) {
                    if (mSlot == 1) {
                        do_animation(0xB);
                        GCSaveData* saveData = NULL;
                        while ((saveData = static_cast<GCSaveData*>(nw4r::ut::List_GetNext(&mSaveDataList, saveData))) != NULL) {
                            saveData->do_animation(1);
                        }
                        if (mPrevState == 10) {
                            do_animation(0x1A);
                        }
                        snd::getSystem()->startSE("WIPL_SE_BT_PUSH");
                        mState = 5;
                    }
                } else if (strcmp(paneName, scTriggerPaneName[3]) == 0) {
                    if (mSlot == 0) {
                        do_animation(8);
                        GCSaveData* saveData = NULL;
                        while ((saveData = static_cast<GCSaveData*>(nw4r::ut::List_GetNext(&mSaveDataList, saveData))) != NULL) {
                            saveData->do_animation(1);
                        }
                        if (mPrevState == 10) {
                            do_animation(0x1A);
                        }
                        snd::getSystem()->startSE("WIPL_SE_BT_PUSH");
                        mState = 5;
                    }
                }
            }
        }

        void MemoryCard::onFocus(void* data) {
            if (mState == 2) {
                if (data != NULL) {
                    snd::getSystem()->startSE("WIPL_SE_DECIDE");
                    GCSaveData* saveData = static_cast<GCSaveData*>(data);
                    mpFocusSaveData = saveData;
                    mpGCWindow->init(math::VEC3(*saveData->getTranslate()), mpManager,
                                     saveData->mSlot,
                                     saveData->mIndex);
                    change_button_text_close();
                }
                mState = 9;
            }
        }

        void MemoryCard::onRelease() {
            if (mpFocusSaveData != NULL) {
                TextBalloon* balloon = mpFocusSaveData->mpBalloon;
                if (balloon != NULL) {
                    balloon->terminate();
                }
            }
            mpFocusSaveData = NULL;
            mState = 2;
        }

        BOOL MemoryCard::isResetAcceptable() const {
            return !mpGCWindow->isProcess();
        }

        void MemoryBase::onMove(const char*) {}

        MemoryCardManager::~MemoryCardManager() {}

        MemoryCard::~MemoryCard() {}

    }
}


// Original .sdata2 ends with the PPC int-to-float conversion constant.
extern "C" const f64 sMemoryCardIntToFloat = 4503601774854144.0;
