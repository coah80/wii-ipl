#include "scene/sdChannelMemory/iplSDMemory.h"

#include <cstring>
#include <wchar.h>

#include "iplSound.h"
#include "iplSystem.h"
#include "utility/iplLayout.h"

#include "system/iplDialogWindow.h"
#include "system/iplSaveDataManager.h"

#include "scene/sdChannelSelect/iplSDChannelSelect.h"

namespace ipl {
    namespace scene {
        // clang-format off
        static const char* scDialogABtnPanes[] = {
            "A", "B", "B_BtnA",
        };

        static const char* scDialogBBtnPanes5[] = {
            "A", "B", "C", "D", "B_BtnA",
        };

        static const char* scDialogBBtnPanes4[] = {
            "B_00", "C_00", "D_00", "B_BtnA",
        };

        static const char* scDialogCBtnPanes[] = {
            "B_ArwR", "B_ArwL", "B_CalExit", "B_CalExit_00",
        };
        // clang-format on

        class SDMemoryDialogAEvent : public ::gui::EventHandler {
        public:
            SDMemoryDialogAEvent(SDMemory* memory) : mpSDMemory(memory) {}

            virtual void onEvent(u32 compId, u32 event, void* data);

        private:
            SDMemory* mpSDMemory;  // 0x0C
        };

        class SDMemoryDialogBEvent : public ::gui::EventHandler {
        public:
            SDMemoryDialogBEvent(SDMemory* memory) : mpSDMemory(memory) {}

            virtual void onEvent(u32 compId, u32 event, void* data);

        private:
            SDMemory* mpSDMemory;  // 0x0C
        };

        class SDMemoryDialogCEvent : public ::gui::EventHandler {
        public:
            SDMemoryDialogCEvent(SDMemory* memory) : mpSDMemory(memory) {}

            virtual void onEvent(u32 compId, u32 event, void* data);

        private:
            SDMemory* mpSDMemory;  // 0x0C
        };

        SDMemory::SDMemory() {
        }

        SDMemory::~SDMemory() {
        }

        void SDMemory::create(EGG::Heap* heap, nand::LayoutFile* layoutFile, SDChannelSelect* chanSel) {
            mpChanSelect = chanSel;

            mpDialogA = new layout::Object(heap, layoutFile, "arc", "mn_DialogWindow_ChChange_a.brlyt");
            mpDialogA->bindToGroup("mn_DialogWindow_ChChange_a_DialogIn.brlan", "G_InOut", false, true);
            mpDialogA->bindToGroup("mn_DialogWindow_ChChange_a_DialogOut.brlan", "G_InOut", false, true);
            mpDialogA->bindToGroup("mn_DialogWindow_ChChange_a_FocusBtn_on.brlan", "G_FocusBtnA", false, true);
            mpDialogA->bindToGroup("mn_DialogWindow_ChChange_a_FocusBtn_off.brlan", "G_FocusBtnA", false, true);
            mpDialogA->bindToGroup("mn_DialogWindow_ChChange_a_SelectBtn_Ac.brlan", "G_SelectBtnA", false, true);
            mpDialogA->bindToGroup("mn_DialogWindow_ChChange_a_BtnA_Rollover.brlan", "G_BtnA", false, true);
            mpDialogA->bindToGroup("mn_DialogWindow_ChChange_a_BtnA_Rollout.brlan", "G_BtnA", false, true);
            mpDialogA->bindToGroup("mn_DialogWindow_ChChange_a_BtnA_On.brlan", "G_BtnA", false, true);
            mpDialogA->bindToGroup("mn_DialogWindow_ChChange_a_BtnB_Rollover.brlan", "G_BtnB", false, true);
            mpDialogA->bindToGroup("mn_DialogWindow_ChChange_a_BtnB_Rollout.brlan", "G_BtnB", false, true);
            mpDialogA->bindToGroup("mn_DialogWindow_ChChange_a_BtnB_On.brlan", "G_BtnB", false, true);
            mpDialogA->finishBinding();
            mpDialogA->getAnim(0)->initAnmFrame();
            mpDialogA->getAnim(2)->initAnmFrame();
            mpDialogA->getAnim(5)->initAnmFrame();
            mpDialogA->getAnim(8)->initAnmFrame();

            nw4r::lyt::TextBox* textPane;
            textPane = (nw4r::lyt::TextBox*)mpDialogA->FindPaneByName("T_Dialog_00");
            textPane->SetString(System::getMessage(0xB0), 0);
            textPane = (nw4r::lyt::TextBox*)mpDialogA->FindPaneByName("TextBox_05");
            textPane->SetString(System::getMessage(0xBB), 0);
            textPane = (nw4r::lyt::TextBox*)mpDialogA->FindPaneByName("TextBox_06");
            textPane->SetString(System::getMessage(0xBC), 0);
            textPane = (nw4r::lyt::TextBox*)mpDialogA->FindPaneByName("T_BtnA");
            textPane->SetString(System::getMessage(0x25), 0);

            mpDialogB = new layout::Object(heap, layoutFile, "arc", "mn_DialogWindow_ChChange_b.brlyt");
            mpDialogB->bindToGroup("mn_DialogWindow_ChChange_b_DialogIn.brlan", "G_InOut", false, true);
            mpDialogB->bindToGroup("mn_DialogWindow_ChChange_b_DialogOut.brlan", "G_InOut", false, true);
            mpDialogB->bindToGroup("mn_DialogWindow_ChChange_b_FocusBtn_on.brlan", "G_FocusBtnA", false, true);
            mpDialogB->bindToGroup("mn_DialogWindow_ChChange_b_FocusBtn_off.brlan", "G_FocusBtnA", false, true);
            mpDialogB->bindToGroup("mn_DialogWindow_ChChange_b_SelectBtn_Ac.brlan", "G_SelectBtnA", false, true);
            mpDialogB->bindToGroup("mn_DialogWindow_ChChange_b_BtnA_Rollover.brlan", "G_BtnA", false, true);
            mpDialogB->bindToGroup("mn_DialogWindow_ChChange_b_BtnA_Rollout.brlan", "G_BtnA", false, true);
            mpDialogB->bindToGroup("mn_DialogWindow_ChChange_b_BtnA_On.brlan", "G_BtnA", false, true);
            mpDialogB->bindToGroup("mn_DialogWindow_ChChange_b_BtnB_Rollover.brlan", "G_BtnB", false, true);
            mpDialogB->bindToGroup("mn_DialogWindow_ChChange_b_BtnB_Rollout.brlan", "G_BtnB", false, true);
            mpDialogB->bindToGroup("mn_DialogWindow_ChChange_b_BtnB_On.brlan", "G_BtnB", false, true);
            mpDialogB->bindToGroup("mn_DialogWindow_ChChange_b_BtnC_Rollover.brlan", "G_BtnC", false, true);
            mpDialogB->bindToGroup("mn_DialogWindow_ChChange_b_BtnC_Rollout.brlan", "G_BtnC", false, true);
            mpDialogB->bindToGroup("mn_DialogWindow_ChChange_b_BtnC_On.brlan", "G_BtnC", false, true);
            mpDialogB->bindToGroup("mn_DialogWindow_ChChange_b_BtnD_Rollover.brlan", "G_BtnD", false, true);
            mpDialogB->bindToGroup("mn_DialogWindow_ChChange_b_BtnD_Rollout.brlan", "G_BtnD", false, true);
            mpDialogB->bindToGroup("mn_DialogWindow_ChChange_b_BtnD_On.brlan", "G_BtnD", false, true);
            mpDialogB->finishBinding();
            mpDialogB->getAnim(0)->initAnmFrame();
            mpDialogB->getAnim(2)->initAnmFrame();
            mpDialogB->getAnim(5)->initAnmFrame();
            mpDialogB->getAnim(8)->initAnmFrame();
            mpDialogB->getAnim(0xB)->initAnmFrame();
            mpDialogB->getAnim(0xE)->initAnmFrame();

            textPane = (nw4r::lyt::TextBox*)mpDialogB->FindPaneByName("T_Dialog");
            textPane->SetString(System::getMessage(0xB6), 0);
            textPane = (nw4r::lyt::TextBox*)mpDialogB->FindPaneByName("TextBox_00");
            textPane->SetString(System::getMessage(0xB7), 0);
            textPane = (nw4r::lyt::TextBox*)mpDialogB->FindPaneByName("TextBox_01");
            textPane->SetString(System::getMessage(0xB8), 0);
            textPane = (nw4r::lyt::TextBox*)mpDialogB->FindPaneByName("TextBox_02");
            textPane->SetString(System::getMessage(0xB9), 0);
            textPane = (nw4r::lyt::TextBox*)mpDialogB->FindPaneByName("TextBox_03");
            textPane->SetString(System::getMessage(0xBA), 0);
            textPane = (nw4r::lyt::TextBox*)mpDialogB->FindPaneByName("T_Dialog_00");
            textPane->SetString(System::getMessage(0xB6), 0);
            textPane = (nw4r::lyt::TextBox*)mpDialogB->FindPaneByName("TextBox_05");
            textPane->SetString(System::getMessage(0xB8), 0);
            textPane = (nw4r::lyt::TextBox*)mpDialogB->FindPaneByName("TextBox_06");
            textPane->SetString(System::getMessage(0xB9), 0);
            textPane = (nw4r::lyt::TextBox*)mpDialogB->FindPaneByName("TextBox_07");
            textPane->SetString(System::getMessage(0xBA), 0);

            int numChannels = 0;
            for (int i = 0; i < 0x30; i++) {
                if (System::getSaveData()->mData.titleCache[0][i] != 0) {
                    numChannels++;
                }
            }
            if (numChannels >= 5) {
                layout::Wrapper::Hide(mpDialogB->FindPaneByName("N_Btn_3"));
                mpDialogB->FindPaneByName("N_Btn_4")->SetVisible(true);
                mDialogBtnType = 4;
            } else {
                mpDialogB->FindPaneByName("N_Btn_3")->SetVisible(true);
                layout::Wrapper::Hide(mpDialogB->FindPaneByName("N_Btn_4"));
                mDialogBtnType = 3;
            }

            textPane = (nw4r::lyt::TextBox*)mpDialogB->FindPaneByName("T_BtnA");
            textPane->SetString(System::getMessage(0xA5), 0);

            mpDialogC = new layout::Object(heap, layoutFile, "arc", "mn_DialogWindow_ChChange_c.brlyt");
            ((nw4r::lyt::TextBox*)mpDialogC->FindPaneByName("T_Letter"))->AllocStringBuffer(0x840);
            mpDialogC->bindToGroup("mn_DialogWindow_ChChange_c_Dialog_FadeIn.brlan", "G_Fede", false, true);
            mpDialogC->bindToGroup("mn_DialogWindow_ChChange_c_Dialog_FadeOut.brlan", "G_Fede", false, true);
            mpDialogC->bindToGroup("mn_DialogWindow_ChChange_c_Back_RollOver.brlan", "G_Back_Focus", false, true);
            mpDialogC->bindToGroup("mn_DialogWindow_ChChange_c_Back_Rollout.brlan", "G_Back_Focus", false, true);
            mpDialogC->bindToGroup("mn_DialogWindow_ChChange_c_Back_On.brlan", "G_Back_Ac", false, true);
            mpDialogC->bindToGroup("mn_DialogWindow_ChChange_c_Move_RollOver.brlan", "G_Move_Focus", false, true);
            mpDialogC->bindToGroup("mn_DialogWindow_ChChange_c_Move_Rollout.brlan", "G_Move_Focus", false, true);
            mpDialogC->bindToGroup("mn_DialogWindow_ChChange_c_Move_On.brlan", "G_Move_Ac", false, true);
            mpDialogC->bindToGroup("mn_DialogWindow_ChChange_c_FocusOn.brlan", "G_ArwL_Focus", false, true);
            mpDialogC->bindToGroup("mn_DialogWindow_ChChange_c_FocusOff.brlan", "G_ArwL_Focus", false, true);
            mpDialogC->bindToGroup("mn_DialogWindow_ChChange_c_Select.brlan", "G_ArwL_Ac", false, true);
            mpDialogC->bindToGroup("mn_DialogWindow_ChChange_c_FocusOn.brlan", "G_ArwR_Focus", false, true);
            mpDialogC->bindToGroup("mn_DialogWindow_ChChange_c_FocusOff.brlan", "G_ArwR_Focus", false, true);
            mpDialogC->bindToGroup("mn_DialogWindow_ChChange_c_Select.brlan", "G_ArwR_Ac", false, true);
            mpDialogC->bindToGroup("mn_DialogWindow_ChChange_c_Appear.brlan", "G_ArwL_End", false, true);
            mpDialogC->bindToGroup("mn_DialogWindow_ChChange_c_Lost.brlan", "G_ArwL_End", false, true);
            mpDialogC->bindToGroup("mn_DialogWindow_ChChange_c_Appear.brlan", "G_ArwR_End", false, true);
            mpDialogC->bindToGroup("mn_DialogWindow_ChChange_c_Lost.brlan", "G_ArwR_End", false, true);
            mpDialogC->bindToGroup("mn_DialogWindow_ChChange_c_Loop.brlan", "G_ArwRoop", false, true);
            mpDialogC->bindToGroup("mn_DialogWindow_ChChange_c_HDActionStart.brlan", "G_ArwL_HDAc", false, true);
            mpDialogC->bindToGroup("mn_DialogWindow_ChChange_c_HDActionEnd.brlan", "G_ArwL_HDAc", false, true);
            mpDialogC->bindToGroup("mn_DialogWindow_ChChange_c_HDActionStart.brlan", "G_ArwR_HDAc", false, true);
            mpDialogC->bindToGroup("mn_DialogWindow_ChChange_c_HDActionEnd.brlan", "G_ArwR_HDAc", false, true);
            mpDialogC->finishBinding();
            mpDialogC->getAnim(0)->initAnmFrame();
            mpDialogC->getAnim(2)->initAnmFrame();
            mpDialogC->getAnim(5)->initAnmFrame();
            mpDialogC->getAnim(0xB)->initAnmFrame();
            mpDialogC->getAnim(8)->initAnmFrame();
            mpDialogC->getAnim(0x12)->initAnmFrame();
            layout::Animator* pAnim = mpDialogC->getAnim(0x12);
            pAnim->initFrame();
            pAnim->restart();

            textPane = (nw4r::lyt::TextBox*)mpDialogC->FindPaneByName("T_CalExit");
            textPane->SetString(System::getMessage(0xA5), 0);
            textPane = (nw4r::lyt::TextBox*)mpDialogC->FindPaneByName("T_CalExit_00");
            textPane->SetString(System::getMessage(0xC4), 0);

            mpDialogBg = new layout::Object(heap, layoutFile, "arc", "mn_DialogWindow_Background.brlyt");
            mpDialogBg->bindToGroup("mn_DialogWindow_Background_DialogIn.brlan", "G_InOut", false, true);
            mpDialogBg->bindToGroup("mn_DialogWindow_Background_DialogOut.brlan", "G_InOut", false, true);
            mpDialogC->finishBinding();
            mpDialogBg->getAnim(0)->initAnmFrame();

            SDMemoryDialogAEvent* eventA = new SDMemoryDialogAEvent(this);
            mpPaneMgrA = new gui::PaneManager(eventA, mpDialogA->getDrawInfo(), NULL, NULL, false);
            mpPaneMgrA->setupScene(mpDialogA);
            mpPaneMgrA->setAllComponentTriggerTarget(false);
            for (int i = 0; i < 3; i++) {
                mpPaneMgrA->setTriggerTarget(mpDialogA->FindPaneByName(scDialogABtnPanes[i]), true);
            }

            SDMemoryDialogBEvent* eventB = new SDMemoryDialogBEvent(this);
            mpPaneMgrB = new gui::PaneManager(eventB, mpDialogB->getDrawInfo(), NULL, NULL, false);
            mpPaneMgrB->setupScene(mpDialogB);
            mpPaneMgrB->setAllComponentTriggerTarget(false);
            if (mDialogBtnType == 4) {
                for (int i = 0; i < 5; i++) {
                    mpPaneMgrB->setTriggerTarget(mpDialogB->FindPaneByName(scDialogBBtnPanes5[i]), true);
                }
            } else {
                for (int i = 0; i < 4; i++) {
                    mpPaneMgrB->setTriggerTarget(mpDialogB->FindPaneByName(scDialogBBtnPanes4[i]), true);
                }
            }

            SDMemoryDialogCEvent* eventC = new SDMemoryDialogCEvent(this);
            mpPaneMgrC = new gui::PaneManager(eventC, mpDialogC->getDrawInfo(), NULL, NULL, false);
            mpPaneMgrC->setupScene(mpDialogC);
            mpPaneMgrC->setAllComponentTriggerTarget(false);
            for (int i = 0; i < 4; i++) {
                mpPaneMgrC->setTriggerTarget(mpDialogC->FindPaneByName(scDialogCBtnPanes[i]), true);
            }

            mbDialogOpen = true;
        }

        void SDMemory::startCheck(NandSDWorker::AppBlocksInfo* freeArea, NandSDWorker::AppBlocksInfo* needed) {
            mFreeArea = *freeArea;
            mNeededArea = *needed;

            mbDialogOpen = true;
            mCheckProgress = 0;

            mpDialogA->getAnim(0)->initAnmFrame();
            layout::Animator* pAnim = mpDialogA->getAnim(0);
            pAnim->initFrame();
            pAnim->restart();

            mpDialogBg->getAnim(0)->initAnmFrame();
            pAnim = mpDialogBg->getAnim(0);
            pAnim->initFrame();
            pAnim->restart();

            snd::getSystem()->startSE("WIPL_SE_INFO_WINDOW");

            mbChecking = true;
            mState = 0;
        }

        void SDMemory::initScroller() {
            nw4r::lyt::Pane* header = mpDialogC->FindPaneByName("N_Header");
            nw4r::lyt::Pane* body = mpDialogC->FindPaneByName("N_Body");
            nw4r::lyt::Pane* footer = mpDialogC->FindPaneByName("N_Footer");

            nw4r::ut::Rect projRect;
            System::getProjectionRect(&projRect);

            f32 limit = 160.0f + ((mLineCount * body->GetSize().height) + (header->GetSize().height + footer->GetSize().height) - projRect.GetHeight());
            if (limit < 0.0f) {
                limit = 0.0f;
            }

            mScroller.init();
            mScroller.setDownLimit(limit);
        }

        void SDMemory::resetEdgeAnims() {
            mbEdgePlayed[0] = false;
            mbEdgePlayed[1] = false;
            mbEdgePlayed[2] = false;
            mbEdgePlayed[3] = false;

            mpDialogC->getAnim(0x10)->initAnmFrame();
            mpDialogC->getAnim(0xE)->initAnmFrame();

            if (mScroller.isDownEnd() == false) {
                playEdgeAnim1();
            }
        }

        void SDMemory::updateEdgeAnims(u32 p1, u32 p2, u32 p3, u32 p4) {
            if (p1 != 1 && p3 == 1) {
                playEdgeAnim0();
            }
            if (p1 == 1 && p3 != 1) {
                stopEdgeAnim0();
            }
            if (p2 != 1 && p4 == 1) {
                playEdgeAnim1();
            }
            if (p2 == 1 && p4 != 1) {
                stopEdgeAnim1();
            }
        }

        void SDMemory::playEdgeAnim0() {
            if (!mbEdgePlayed[0]) {
                mpDialogC->getAnim(0x10)->initAnmFrame();
                layout::Animator* pAnim = mpDialogC->getAnim(0x10);
                pAnim->initFrame();
                pAnim->restart();
                mbEdgePlayed[0] = true;
            }
        }

        void SDMemory::playEdgeAnim1() {
            if (!mbEdgePlayed[1]) {
                mpDialogC->getAnim(0xE)->initAnmFrame();
                layout::Animator* pAnim = mpDialogC->getAnim(0xE);
                pAnim->initFrame();
                pAnim->restart();
                mbEdgePlayed[1] = true;
            }
        }

        void SDMemory::stopEdgeAnim0() {
            if (mbEdgePlayed[0]) {
                mpDialogC->getAnim(0x11)->initAnmFrame();
                layout::Animator* pAnim = mpDialogC->getAnim(0x11);
                pAnim->initFrame();
                pAnim->restart();
                mbEdgePlayed[0] = false;
            }
        }

        void SDMemory::stopEdgeAnim1() {
            if (mbEdgePlayed[1]) {
                mpDialogC->getAnim(0xF)->initAnmFrame();
                layout::Animator* pAnim = mpDialogC->getAnim(0xF);
                pAnim->initFrame();
                pAnim->restart();
                mbEdgePlayed[1] = false;
            }
        }

        void SDMemory::updateEdgeArrows() {
            controller::Interface* pCon = System::getMasterController();

            if (mScroller.getBInst().isActive()) {
                if (pCon->down(controller::BTN_UP)) {
                    playEdgeAnim2();
                }
                if (!pCon->down(controller::BTN_UP)) {
                    stopEdgeAnim2();
                }
                if (pCon->down(controller::BTN_DOWN)) {
                    playEdgeAnim3();
                }
                if (!pCon->down(controller::BTN_DOWN)) {
                    stopEdgeAnim3();
                }
            } else {
                if (mScroller.getBInst().isUp()) {
                    playEdgeAnim2();
                }
                if (!mScroller.getBInst().isUp()) {
                    stopEdgeAnim2();
                }
                if (mScroller.getBInst().isDown()) {
                    playEdgeAnim3();
                }
                if (!mScroller.getBInst().isDown()) {
                    stopEdgeAnim3();
                }
            }
        }

        void SDMemory::playEdgeAnim2() {
            if (!mbEdgePlayed[2]) {
                layout::Animator* pAnim = mpDialogC->getAnim(0x13);
                pAnim->initFrame();
                pAnim->restart();
                mbEdgePlayed[2] = true;
            }
        }

        void SDMemory::playEdgeAnim3() {
            if (!mbEdgePlayed[3]) {
                layout::Animator* pAnim = mpDialogC->getAnim(0x15);
                pAnim->initFrame();
                pAnim->restart();
                mbEdgePlayed[3] = true;
            }
        }

        void SDMemory::stopEdgeAnim2() {
            if (mbEdgePlayed[2]) {
                layout::Animator* pAnim = mpDialogC->getAnim(0x14);
                pAnim->initFrame();
                pAnim->restart();
                mbEdgePlayed[2] = false;
            }
        }

        void SDMemory::stopEdgeAnim3() {
            if (mbEdgePlayed[3]) {
                layout::Animator* pAnim = mpDialogC->getAnim(0x16);
                pAnim->initFrame();
                pAnim->restart();
                mbEdgePlayed[3] = false;
            }
        }

        static const char* sc_arwPaneNames[4] = {"B_ArwR", "B_ArwL", "B_CalExit", "B_CalExit_00"};

        void SDMemory::initArwAnims() {

            for (int i = 0; i < 4; i++) {
                if (mScrFlags[i] != 0) {
                    mScrFlags[i] = 0;

                    nw4r::lyt::Pane* pPane = mpDialogC->FindPaneByName(sc_arwPaneNames[i]);
                    mpPaneMgrC->initPane(pPane);

                    layout::Animator* pAnim = NULL;
                    switch (i) {
                        case 2:
                            pAnim = mpDialogC->getAnim(3);
                            break;
                        case 3:
                            pAnim = mpDialogC->getAnim(6);
                            break;
                        case 0:
                            pAnim = mpDialogC->getAnim(0xC);
                            break;
                        case 1:
                            pAnim = mpDialogC->getAnim(9);
                            break;
                    }

                    if (pAnim != NULL) {
                        pAnim->initAnmFrame();
                        pAnim->initFrame();
                        pAnim->restart();
                    }
                }
            }
        }

        BOOL SDMemory::waitEnd() {
            int ret = 0;
            int state = checkProgress();

            if (state == 0) {
                if (mScroller.calc(mCheckProgress == 0xA) == 1) {
                    initArwAnims();
                }

                math::VEC3 pos(0.0f, mScroller.get(), 0.0f);
                mpDialogC->FindPaneByName("N_Memo")->SetTranslate(pos);

                switch (mCheckProgress) {
                    case 0x00:
                        state0();
                        break;
                    case 0x01:
                        mpPaneMgrA->update();
                        mpPaneMgrA->calc();
                        break;
                    case 0x02:
                        state2();
                        break;
                    case 0x03:
                        ret = state3();
                        break;
                    case 0x04:
                        state4();
                        break;
                    case 0x05:
                        mpPaneMgrB->update();
                        mpPaneMgrB->calc();
                        break;
                    case 0x06:
                        state6();
                        break;
                    case 0x07:
                        state7();
                        break;
                    case 0x08:
                        state8();
                        break;
                    case 0x09:
                        state9();
                        break;
                    case 0x0A:
                        state10();
                        break;
                    case 0x0B:
                        state11();
                        break;
                    case 0x0C:
                        state12();
                        break;
                    case 0x0D:
                        state13();
                        break;
                    case 0x0E:
                        state14();
                        break;
                    case 0x0F:
                        state15();
                        break;
                    case 0x10:
                        state16();
                        break;
                    case 0x11:
                        state17();
                        break;
                    case 0x12:
                        state18();
                        break;
                    case 0x13:
                        state19();
                        break;
                    case 0x14:
                        ret = state20();
                        break;
                    case 0x15:
                        state21();
                        break;
                    case 0x16:
                        ret = state22();
                        break;
                    case 0x17:
                        state23();
                        break;
                    case 0x18:
                        ret = state24();
                        break;
                    case 0x19:
                        ret = 1;
                        break;
                }
            }

            mpDialogA->calc();
            mpDialogB->calc();
            mpDialogC->calc();
            mpDialogBg->calc();

            return state == 2 ? TRUE : ret;
        }

        int SDMemory::checkProgress() {
            int chstate = mpChanSelect->mSelState;
            int ret = 0;

            if ((u32)(chstate - 1) <= 1) {
                switch (mCheckProgress) {
                    case 1:
                    case 2: {
                        mpDialogA->getAnim(1)->initAnmFrame();
                        layout::Animator* pAnim = mpDialogA->getAnim(1);
                        pAnim->initFrame();
                        pAnim->restart();

                        mpDialogBg->getAnim(1)->initAnmFrame();
                        pAnim = mpDialogBg->getAnim(1);
                        pAnim->initFrame();
                        pAnim->restart();

                        mbChecking = false;
                        mCheckProgress = 3;
                        ret = 1;
                        break;
                    }
                    case 3: {
                        if (mbChecking) {
                            mpDialogBg->getAnim(1)->initAnmFrame();
                            layout::Animator* pAnim = mpDialogBg->getAnim(1);
                            pAnim->initFrame();
                            pAnim->restart();
                            mbChecking = false;
                        }
                        if (!mpDialogA->isPlaying(1) && !mpDialogBg->isPlaying(1)) {
                            ret = 2;
                        } else {
                            ret = 1;
                        }
                        break;
                    }
                    case 5:
                    case 6: {
                        mpDialogB->getAnim(1)->initAnmFrame();
                        layout::Animator* pAnim = mpDialogB->getAnim(1);
                        pAnim->initFrame();
                        pAnim->restart();

                        mpDialogBg->getAnim(1)->initAnmFrame();
                        pAnim = mpDialogBg->getAnim(1);
                        pAnim->initFrame();
                        pAnim->restart();

                        mbChecking = false;
                        mCheckProgress = 7;
                        ret = 1;
                        break;
                    }
                    case 7: {
                        if (mbChecking) {
                            mpDialogBg->getAnim(1)->initAnmFrame();
                            layout::Animator* pAnim = mpDialogBg->getAnim(1);
                            pAnim->initFrame();
                            pAnim->restart();
                            mbChecking = false;
                        }
                        if (!mpDialogB->isPlaying(1) && !mpDialogBg->isPlaying(1)) {
                            ret = 2;
                        } else {
                            ret = 1;
                        }
                        break;
                    }
                    case 0xA:
                    case 0xB: {
                        mCheckProgress = 0xC;

                        mpDialogC->getAnim(1)->initAnmFrame();
                        layout::Animator* pAnim = mpDialogC->getAnim(1);
                        pAnim->initFrame();
                        pAnim->restart();

                        mpDialogBg->getAnim(1)->initAnmFrame();
                        pAnim = mpDialogBg->getAnim(1);
                        pAnim->initFrame();
                        pAnim->restart();

                        mbChecking = false;

                        mScroller.reset();
                        if (mbEdgePlayed[0]) {
                            stopEdgeAnim0();
                        }
                        if (mbEdgePlayed[1]) {
                            stopEdgeAnim1();
                        }
                        ret = 1;
                        break;
                    }
                    case 0xC: {
                        if (mbChecking) {
                            mScroller.reset();

                            mpDialogBg->getAnim(1)->initAnmFrame();
                            layout::Animator* pAnim = mpDialogBg->getAnim(1);
                            pAnim->initFrame();
                            pAnim->restart();
                            mbChecking = false;
                        }
                        if (!mpDialogC->isPlaying(1) && !mpDialogBg->isPlaying(1)) {
                            ret = 2;
                        } else {
                            ret = 1;
                        }
                        break;
                    }
                    case 8:
                    case 0x16: {
                        if ((u32)(chstate - 1) <= 1) {
                            DialogWindow* pDlg = System::getDialog();
                            if (pDlg->getState() == 2) {
                                pDlg->terminate();

                                mpDialogBg->getAnim(1)->initAnmFrame();
                                layout::Animator* pAnim = mpDialogBg->getAnim(1);
                                pAnim->initFrame();
                                pAnim->restart();
                                mbChecking = false;
                            }
                            else if (pDlg->getState() == 4 || pDlg->getState() == 3) {
                                if (mbChecking) {
                                    mpDialogBg->getAnim(1)->initAnmFrame();
                                    layout::Animator* pAnim = mpDialogBg->getAnim(1);
                                    pAnim->initFrame();
                                    pAnim->restart();
                                    mbChecking = false;
                                }
                            }
                        }
                        if (System::getDialog()->getLastResult() != -1) {
                            if (!mpDialogBg->isPlaying(1)) {
                                if (System::getDialog()->getLastResult() != 1) {
                                    if ((u32)(chstate - 1) <= 1) {
                                        ret = 2;
                                    } else {
                                        ret = 1;
                                    }
                                }
                            }
                        }
                        break;
                    }
                }
            }

            if (ret == 2) {
                mState = 6;
            }
            return ret;
        }
        void SDMemory::state0() {
            static const char* sc_paneNames[3] = {"A", "B", "B_BtnA"};
            if (!mpDialogA->isPlaying(-1)) {
                for (int i = 0; i < 3; i++) {
                    mUnk30[i] = 0;
                    nw4r::lyt::Pane* pPane = mpDialogA->FindPaneByName(sc_paneNames[i]);
                    mpPaneMgrA->initPane(pPane);
                }
                mCheckProgress = 1;
            }
        }

        void SDMemory::state2() {
            if (!mpDialogA->isPlaying(-1)) {
                mpDialogA->getAnim(1)->initAnmFrame();
                layout::Animator* pAnim = mpDialogA->getAnim(1);
                pAnim->initFrame();
                pAnim->restart();

                if (mDialogBtnType == 2) {
                    mpDialogBg->getAnim(1)->initAnmFrame();
                    pAnim = mpDialogBg->getAnim(1);
                    pAnim->initFrame();
                    pAnim->restart();
                    mbChecking = false;
                }
                mCheckProgress = 3;
            }
        }

        int SDMemory::state3() {
            if (!mpDialogA->isPlaying(-1)) {
                switch (mDialogBtnType) {
                    case 0: {
                        if (mpChanSelect->startSDWorker(&mFreeArea, &mNeededArea, unk_0x80, unk_0x380, &mMsgCount, 2)) {
                            mCheckProgress = 4;
                            mpDialogB->getAnim(0)->initAnmFrame();
                            layout::Animator* pAnim = mpDialogB->getAnim(0);
                            pAnim->initFrame();
                            pAnim->restart();
                            snd::sSystem.startSE("WIPL_SE_INFO_WINDOW");
                        } else {
                            mCheckProgress = 0x15;
                            mNextProgress = 0xB4;
                        }
                        break;
                    }
                    case 1: {
                        mCheckProgress = 0x15;
                        mNextProgress = 0xB3;
                        break;
                    }
                    case 2: {
                        mCheckProgress = 0x19;
                        mState = 3;
                        return 1;
                    }
                }
            }
            return 0;
        }

        void SDMemory::state4() {
            static const char* sc_paneNames1[5] = {"A", "B", "C", "D", "B_BtnA"};
            static const char* sc_paneNames2[4] = {"B_00", "C_00", "D_00", "B_BtnA"};
            if (!mpDialogB->isPlaying(-1)) {
                if (mDialogResult == 4) {
                    for (int i = 0; i < 5; i++) {
                        mUnk3C[i] = 0;
                        nw4r::lyt::Pane* pPane = mpDialogB->FindPaneByName(sc_paneNames1[i]);
                        mpPaneMgrB->initPane(pPane);
                    }
                } else {
                    for (int i = 1; i < 5; i++) {
                        mUnk3C[i] = 0;
                        nw4r::lyt::Pane* pPane = mpDialogB->FindPaneByName(sc_paneNames2[i - 1]);
                        mpPaneMgrB->initPane(pPane);
                    }
                }
                mCheckProgress = 5;
            }
        }

        void SDMemory::state6() {
            if (!mpDialogB->isPlaying(-1)) {
                mCheckProgress = 7;
                mpDialogB->getAnim(1)->initAnmFrame();
                layout::Animator* pAnim = mpDialogB->getAnim(1);
                pAnim->initFrame();
                pAnim->restart();
            }
        }

        void SDMemory::state7() {
            if (!mpDialogB->isPlaying(-1)) {
                switch (mDialogBtnType) {
                    case 4: {
                        mCheckProgress = 0;
                        layout::Animator* pAnim = mpDialogA->getAnim(0);
                        pAnim->initFrame();
                        pAnim->restart();
                        snd::sSystem.startSE("WIPL_SE_INFO_WINDOW");
                        break;
                    }
                    default: {
                        mCheckTime = 0;
                        mUnk29E0 = 0;
                        System::getDialog()->callBtn0NoShade(0xCC, 0, true);
                        mCheckProgress = 8;
                        break;
                    }
                }
            }
        }

        void SDMemory::state8() {
            if (System::getDialog()->getState() == 2) {
                if (mCheckTime == 0) {
                    mCheckTime = OSGetTime();
                }
                if (!mpChanSelect->mpWorker->is_working()) {
                    if (OSGetTime() - mCheckTime > OS_TIMER_CLOCK) {
                        System::getDialog()->terminate();
                    }
                }
                if (System::getDialog()->getLastResult() != -1) {
                    if (mpChanSelect->mpWorker->get_async_result() == 0) {
                        mField1648 = mCheckLists[1].count;
                        mField1340 = mCheckLists[2].count;
                    } else {
                        mField1648 = 0;
                        mField1340 = 0;
                    }

                    mCheckProgress = 9;

                    layout::Animator* pAnim = mpDialogC->getAnim(0);
                    pAnim->initFrame();
                    pAnim->restart();

                    nw4r::lyt::TextBox* pHeader = static_cast<nw4r::lyt::TextBox*>(mpDialogC->FindPaneByName("T_Header"));
                    pHeader->SetString(System::getMessage(0xBE));

                    mLineCount = 0;

                    nw4r::lyt::Pane* pBody = mpDialogC->FindPaneByName("N_Body");
                    nw4r::lyt::Pane* pLetter = mpDialogC->FindPaneByName("T_Letter");
                    pLetter->SetAlpha(0xFF);

                    for (int i = 0; i < mMsgCount; i++) {
                        utility::layout::set_string(pLetter, (const wchar_t*)(unk_0x380 + i * 0x2A));
                        nw4r::ut::Rect textRect = mpDialogC->getTextDrawRect("T_Letter");
                        mLineCount += (int)ceilf(-textRect.GetHeight() / pBody->GetSize().height);
                    }

                    initScroller();
                    resetEdgeAnims();
                }
            }
        }

        void SDMemory::state9() {
            if (!mpDialogC->isPlaying(0)) {
                for (int i = 0; i < 4; i++) {
                    mScrFlags[i] = 0;
                    mpPaneMgrC->initPane(mpDialogC->FindPaneByName(sc_arwPaneNames[i]));
                }
                mCheckProgress = 0xA;
            }
        }

        void SDMemory::state10() {
            controller::Interface* pCon = System::getMasterController();
            if (mScroller.isActive()) {
                updateEdgeArrows();
                BOOL idle = !mScroller.getBInst().isActive();
                if (idle) {
                    if (pCon->down(controller::BTN_UP)) {
                        mScroller.scrollUpByCon();
                    } else if (pCon->down(controller::BTN_DOWN)) {
                        mScroller.scrollDownByCon();
                    }
                }
            }
            updateEdgeAnims(!mbEdgePlayed[0], !mbEdgePlayed[1], mScroller.isUpEnd(), mScroller.isDownEnd());
            BOOL idle2 = !mScroller.getBInst().isActive();
            if (idle2) {
                mpPaneMgrC->update();
                mpPaneMgrC->calc();
            }
        }

        void SDMemory::state11() {
            if (!mpDialogC->isPlaying(4) && !mpDialogC->isPlaying(7)) {
                switch (mDialogBtnType) {
                  case 2:
                  case 3: {
                    mCheckProgress = 0xC;
                    mpDialogC->getAnim(1)->initAnmFrame();
                    layout::Animator* pAnim = mpDialogC->getAnim(1);
                    pAnim->initFrame();
                    pAnim->restart();
                    if (mbEdgePlayed[0]) {
                        playEdgeAnim0();
                    }
                    if (mbEdgePlayed[1]) {
                        playEdgeAnim1();
                    }
                    break;
                  }
                  default:
                    mCheckProgress = 0xA;
                    break;
                }
            }
        }

        void SDMemory::state12() {
            if (!mpDialogC->isPlaying(1)) {
                switch (mDialogBtnType) {
                    case 2: {
                        mCheckProgress = 4;
                        layout::Animator* pAnim = mpDialogB->getAnim(0);
                        pAnim->initAnmFrame();
                        pAnim->initFrame();
                        pAnim->restart();
                        snd::sSystem.startSE("WIPL_SE_INFO_WINDOW");
                        break;
                    }
                    case 3: {
                        mbDialogOpen = false;
                        System::getHomeButtonMenu()->disable();
                        if (mField1340 != 0 || mField1648 != 0) {
                            if (mpChanSelect->mpWorker->is_sd_write_protected()) {
                                mState = 5;
                                mCheckProgress = 0x17;
                                mNextProgress = 0xBF;
                                break;
                            }
                        }
                        if (mpChanSelect->iplSDChannelSelect_813DB530(&mCheckLists[2].ids, &mCheckLists[1].ids) != 0) {
                            mCheckProgress = 0x13;
                            mDialogText[0] = 0;
                            unk_0x78 = 0;
                            const wchar_t* msg = System::getMessage(0xB1);
                            swprintf(mDialogText, 0x107F, L"%ls\n%ls", (const wchar_t*)(unk_0x380 + unk_0x78 * 0x2A), msg);
                            System::getDialog()->callBtnPrgNoShade(mDialogText);
                        } else {
                            mCheckProgress = 0x17;
                            mState = 1;
                            mNextProgress = 0xAE;
                        }
                        break;
                    }
                }
            }
        }

        BOOL SDMemory::findId(u64 id, const u64* list, u32 n) {
            for (int i = 0; i < n; i++) {
                if (list[i] == id) {
                    return TRUE;
                }
            }
            return FALSE;
        }

        void SDMemory::state13() {
            if (!mpChanSelect->mpWorker->is_working()) {
                int r = mpChanSelect->mpWorker->get_async_result();
                if (r == 0) {
                    if (findId(unk_0x80[unk_0x78], mEntryList, mField1648)) {
                        mCheckProgress = 0x11;
                    } else {
                        mCheckProgress = 0xD;
                    }
                } else if (r > 0) {
                    System::getDialog()->terminate();
                    mCheckProgress = 0x14;
                    mState = 2;
                    mNextProgress = 0xB5;
                } else {
                    System::getDialog()->terminate();
                    mCheckProgress = 0x14;
                    mState = 1;
                    mNextProgress = 0xAE;
                }
            }
        }

        void SDMemory::state14() {
            if (System::getDialog()->getState() == 2) {
                mDialogText[0] = 0;
                const wchar_t* msg = System::getMessage(0xB1);
                swprintf(mDialogText, 0x107F, L"%ls\n%ls", (const wchar_t*)(unk_0x380 + unk_0x78 * 0x2A), msg);
                System::getDialog()->set_title(mDialogText);
                if (findId(unk_0x80[unk_0x78], mIdListA, mField1340) != 0 ||
                    findId(unk_0x80[unk_0x78], mEntryList, mField1648) != 0) {
                    if (mpChanSelect->iplSDChannelSelect_813DB478(unk_0x80[unk_0x78]) != 0) {
                        mCheckProgress = 0xE;
                    } else {
                        System::getDialog()->terminate();
                        mCheckProgress = 0x14;
                        mState = 1;
                        mNextProgress = 0xAE;
                    }
                } else {
                    f32 pos = 100.0f * (f32)(unk_0x78 + 1) / (f32)mMsgCount;
                    mCheckProgress = 0xF;
                    if (pos >= 100.0f) {
                        pos = 99.0f;
                    }
                    int v = (int)pos;
                    mUnk29E0 = v;
                    System::getDialog()->setProgBarLength(v);
                }
            }
        }

        void SDMemory::state15() {
            f32 pos = 100.0f * (f32)unk_0x78 / (f32)mMsgCount;
            pos += (f32)(NandSDWorker::s_completion_pct / mMsgCount);
            if (pos >= 100.0f) {
                pos = 99.0f;
            }
            int v = (int)pos;
            mUnk29E0 = v;
            System::getDialog()->setProgBarLength(v);

            if (!mpChanSelect->mpWorker->is_working()) {
                int r = mpChanSelect->mpWorker->get_async_result();
                if (r == 0) {
                    mCheckProgress = 0xF;
                } else {
                    System::getDialog()->terminate();
                    mCheckProgress = 0x14;
                    if (r == -7) {
                        mState = 2;
                        mNextProgress = 0xB5;
                    } else {
                        mState = 1;
                        mNextProgress = 0xAE;
                    }
                }
            }
        }

        void SDMemory::state16() {
            if (mMsgCount > unk_0x78) {
                if (System::isReceiveScheduleStopped()) {
                    if (mpChanSelect->iplSDChannelSelect_813DB4D4(unk_0x80[unk_0x78], 0) != 0) {
                        mCheckProgress = 0x10;
                    } else {
                        System::getDialog()->terminate();
                        mCheckProgress = 0x14;
                        mState = 1;
                        mNextProgress = 0xAE;
                    }
                }
            }
        }

        void SDMemory::state17() {
            if (!mpChanSelect->mpWorker->is_working()) {
                if (System::getDialog()->mProgBarFrame >= mUnk29E0) {
                    System::getChannelManager()->fn_8133AA50(unk_0x80[unk_0x78]);
                    if (mpChanSelect->mpWorker->get_async_result() == 0) {
                        unk_0x78++;
                        if (mMsgCount > unk_0x78) {
                            if (findId(unk_0x80[unk_0x78], mEntryList, mField1648)) {
                                mCheckProgress = 0x11;
                            } else {
                                mCheckProgress = 0xD;
                            }
                        } else {
                            System::getDialog()->setProgBarLength(100);
                            mCheckProgress = 0x14;
                            mState = 0;
                        }
                    } else {
                        System::getDialog()->terminate();
                        mCheckProgress = 0x14;
                        mState = 1;
                        mNextProgress = 0xAE;
                    }
                }
            }
        }

        void SDMemory::state18() {
            if (System::getDialog()->getState() == 2) {
                mDialogText[0] = 0;
                const wchar_t* msg = System::getMessage(0xB1);
                swprintf(mDialogText, 0x107F, L"%ls\n%ls", (const wchar_t*)(unk_0x380 + unk_0x78 * 0x2A), msg);
                System::getDialog()->set_title(mDialogText);
                if (mpChanSelect->iplSDChannelSelect_813DB5EC(unk_0x80[unk_0x78]) != 0) {
                    mCheckProgress = 0x12;
                } else {
                    System::getDialog()->terminate();
                    mCheckProgress = 0x14;
                    mState = 1;
                    mNextProgress = 0xAE;
                }
            }
        }

        void SDMemory::state19() {
            if (!mpChanSelect->mpWorker->is_working()) {
                if (mpChanSelect->mpWorker->get_async_result() == 0) {
                    mCheckProgress = 0xD;
                } else {
                    System::getDialog()->terminate();
                    mCheckProgress = 0x14;
                    mState = 1;
                    mNextProgress = 0xAE;
                }
            }
        }

        int SDMemory::state20() {
            if (System::getDialog()->getState() == 4) {
                if (mbChecking && mState == 0) {
                    mbChecking = false;
                    mpDialogBg->getAnim(1)->initAnmFrame();
                    layout::Animator* pAnim = mpDialogBg->getAnim(1);
                    pAnim->initFrame();
                    pAnim->restart();
                }
                if (System::getDialog()->getLastResult() != -1) {
                    switch (mState) {
                        case 0: {
                            mbDialogOpen = true;
                            mCheckProgress = 0x19;
                            return 1;
                        }
                        default: {
                            mCheckProgress = 0x17;
                            break;
                        }
                    }
                }
            }
            return 0;
        }

        void SDMemory::state21() {
            const wchar_t* msg = System::getMessage(mNextProgress);
            const wchar_t* found = wcsstr(msg, L"****");
            wchar_t* buf1 = new (System::getMem2App(), -0x20) wchar_t[0x400];
            wchar_t* buf2 = new (System::getMem2App(), -0x20) wchar_t[0x400];
            if (found != NULL && msg != NULL) {
                buf1[0] = 0;
                memset(buf1 + 1, 1, 0);
                wcsncat(buf1, msg, ((u32)found - (u32)msg) / 2);
                wcscat(buf1, L"%d");
                wcscat(buf1, found + 4);
                int bytes = mFreeArea.bytes;
                int n = bytes / 0x20000;
                if (bytes % 0x20000 != 0) {
                    n++;
                }
                swprintf(buf2, 0x3FF, buf1, n);
            }
            System::getDialog()->callBtn2NoShade(buf2, 0xC8, 0xA5, false);
            mCheckProgress = 0x16;
            delete[] buf1;
            delete[] buf2;
        }

        int SDMemory::state22() {
            if (System::getDialog()->getState() == 3 && System::getDialog()->mResult == 1) {
                mpDialogBg->getAnim(1)->initAnmFrame();
                layout::Animator* pAnim = mpDialogBg->getAnim(1);
                pAnim->initFrame();
                pAnim->restart();
                mbChecking = false;
                DialogWindow* pDlg = System::getDialog();
                int r = pDlg->getLastResult();
                if (r != -1) {
                    if (r == 1) {
                        mState = 4;
                        mCheckProgress = 0x19;
                        return 1;
                    }
                    mpDialogA->getAnim(0)->initAnmFrame();
                    layout::Animator* pAnimA = mpDialogA->getAnim(0);
                    pAnimA->initFrame();
                    pAnimA->restart();
                    snd::sSystem.startSE("WIPL_SE_INFO_WINDOW");
                    mCheckProgress = 0;
                }
            }
            return 0;
        }

        void SDMemory::state23() {
            switch (mNextProgress) {
                case 0xBF:
                case 0xB5: {
                    System::getDialog()->callBtn1NoShade(mNextProgress, 0xA5);
                    break;
                }
                default: {
                    System::getDialog()->callBtn1NoShade(mNextProgress, 0x2E);
                    break;
                }
            }
            mCheckProgress = 0x18;
        }

        int SDMemory::state24() {
            if (System::getDialog()->getState() == 3) {
                mpDialogBg->getAnim(1)->initAnmFrame();
                mpDialogBg->getAnim(1)->play();
                mbChecking = false;
                if (System::getDialog()->getLastResult() != -1) {
                    mbDialogOpen = true;
                    System::getHomeButtonMenu()->enable();
                    mCheckProgress = 0x19;
                    return 1;
                }
            }
            return 0;
        }

        void SDMemory::draw() {
            utility::Graphics::setDefaultOrtho(0);
            mpDialogBg->draw();
            switch (mCheckProgress) {
                case 0:
                case 1:
                case 2:
                case 3: {
                    mpDialogA->draw();
                    break;
                }
                case 4:
                case 5:
                case 6:
                case 7: {
                    mpDialogB->draw();
                    break;
                }
                case 9:
                case 10:
                case 11:
                case 12: {
                    drawProgress();
                    break;
                }
                default: {
                    break;
                }
            }
        }

        void SDMemory::drawProgress() {
            nw4r::math::VEC3 pos = mpDialogC->FindPaneByName("N_Memo")->GetTranslate();

            mpDialogC->FindPaneByName("header_header");
            nw4r::lyt::Pane* pBodyPane = mpDialogC->FindPaneByName("header_body");

            if (pos.y < 500.0f) {
                mpDialogC->draw("header_header");
            }

            u8 alpha = mpDialogC->FindPaneByName("N_Memo")->GetAlpha();
            f32 lineHeight = pBodyPane->GetSize().height;

            for (nw4r::lyt::PaneList::Iterator it = pBodyPane->GetChildList().GetBeginIter(); it != pBodyPane->GetChildList().GetEndIter(); ++it) {
                it->SetAlpha(alpha);
            }

            f32 posY = 0.0f;

            if (mField1648 != 0) {
                const wchar_t* msg = System::getMessage(0xCB);

                int nLines = 0;
                const wchar_t* p = wcsstr(msg, L"\n");
                if (p != NULL) {
                    const wchar_t* nl = L"\n";
                    do {
                        p = wcsstr(p + 1, nl);
                        nLines++;
                    } while (p != NULL);
                }

                msg = System::getMessage(0xCB);
                nw4r::lyt::Pane* pTxtPane = mpDialogC->FindPaneByName("T_Header_body");

                int count = nLines + 1;
                if (count > 0) {
                    const wchar_t* cur = msg;
                    for (int i = 0; i < count; i++) {
                        const wchar_t* end = wcsstr(cur, L"\n");
                        if (end == NULL) {
                            utility::layout::set_string(pTxtPane, cur);
                        } else {
                            int len = end - cur;
                            wcsncpy(mDialogText, cur, len);
                            mDialogText[len] = 0;
                            utility::layout::set_string(pTxtPane, mDialogText);
                            cur = end + 1;
                        }
                        if (posY < 500.0f) {
                            pBodyPane->SetTranslate(nw4r::math::VEC2(0.0f, posY));
                            pBodyPane->CalculateMtx(*mpDialogC->getDrawInfo());
                            mpDialogC->draw(pBodyPane);
                        }
                        posY -= lineHeight;
                    }
                }
            }

            posY += lineHeight;

            f32 bodyY = 40.0f + posY;
            f32 letterY = 79.5f + posY;

            nw4r::lyt::Pane* pNBody = mpDialogC->FindPaneByName("N_Body");
            f32 bodyHeight = pNBody->GetSize().height;

            for (nw4r::lyt::PaneList::Iterator it = pNBody->GetChildList().GetBeginIter(); it != pNBody->GetChildList().GetEndIter(); ++it) {
                it->SetAlpha(alpha);
            }

            nw4r::lyt::TextBox* pLetter = static_cast<nw4r::lyt::TextBox*>(mpDialogC->FindPaneByName("T_Letter"));
            pLetter->SetAlpha(alpha);

            int matchIdx = 0;
            for (u32 i = 0; i < mMsgCount; i++) {
                utility::layout::set_string(pLetter, (const wchar_t*)(unk_0x380 + i * 0x2A));

                if (matchIdx < (int)mField1648 && unk_0x80[i] == mEntryList[matchIdx]) {
                    nw4r::ut::Color color(0x34, 0xBE, 0xED, 0xFF);
                    nw4r::ut::Color color2(color);
                    matchIdx++;
                    pLetter->SetTextColor(color, color);
                } else {
                    nw4r::ut::Color color(0x64, 0x64, 0x64, 0xFF);
                    nw4r::ut::Color color2(color);
                    pLetter->SetTextColor(color, color);
                }

                nw4r::ut::Rect rect = mpDialogC->getTextDrawRect("T_Letter");
                int rows = (int)ceilf(-rect.GetHeight() / bodyHeight);

                for (int j = 0; j < rows; j++) {
                    if (pos.y + bodyY > -500.0f && pos.y + bodyY < 500.0f) {
                        pNBody->SetTranslate(nw4r::math::VEC2(0.0f, bodyY));
                        pNBody->CalculateMtx(*mpDialogC->getDrawInfo());
                        mpDialogC->draw(pNBody);
                    }
                    bodyY -= bodyHeight;
                }

                if (pos.y + letterY > -500.0f && pos.y + letterY < 500.0f) {
                    pLetter->SetTranslate(nw4r::math::VEC2(0.0f, letterY));
                    pLetter->CalculateMtx(*mpDialogC->getDrawInfo());
                    mpDialogC->draw(pLetter);
                }
                letterY -= rows * bodyHeight;
            }

            bodyY += bodyHeight;

            nw4r::lyt::Pane* pFooter = mpDialogC->FindPaneByName("N_Footer");

            for (nw4r::lyt::PaneList::Iterator it = pFooter->GetChildList().GetBeginIter(); it != pFooter->GetChildList().GetEndIter(); ++it) {
                it->SetAlpha(alpha);
            }

            if (pos.y + bodyY > -500.0f) {
                pFooter->SetTranslate(nw4r::math::VEC2(0.0f, bodyY));
                pFooter->CalculateMtx(*mpDialogC->getDrawInfo());
                mpDialogC->draw(pFooter);
            }

            mpDialogC->draw("N_TopBtn_00");
            mpDialogC->draw("N_Back");
            mpDialogC->draw("N_Move");
        }


        int SDMemory::findDialogAPane(const char* name) {
            int result = -1;
            for (int i = 0; i < 3; i++) {
                if (strcmp(name, scDialogABtnPanes[i]) == 0) {
                    result = i;
                    break;
                }
            }
            return result;
        }

        void SDMemory::onPointDialogA(const char* name, controller::Interface* con) {
            layout::Animator* pAnim = NULL;
            int idx = findDialogAPane(name);
            if (mUnk30[idx] == 0) {
                switch (idx) {
                    case 0:
                        pAnim = mpDialogA->getAnim(5);
                        break;
                    case 1:
                        pAnim = mpDialogA->getAnim(8);
                        break;
                    case 2:
                        pAnim = mpDialogA->getAnim(2);
                        break;
                }
                if (pAnim != NULL) {
                    pAnim->initAnmFrame();
                    pAnim->setAnmType(0);
                    pAnim->initFrame();
                    pAnim->restart();
                    snd::sSystem.startSE("WIPL_SE_BT_TARGETTING");
                    if (con != NULL) {
                        con->rumble(0);
                    }
                    if (mUnk30[idx] < 4) {
                        mUnk30[idx]++;
                    }
                }
            }
        }

        void SDMemory::onLeftDialogA(const char* name) {
            layout::Animator* pAnim = NULL;
            int idx = findDialogAPane(name);
            if (mUnk30[idx] == 1) {
                switch (idx) {
                    case 0:
                        pAnim = mpDialogA->getAnim(6);
                        break;
                    case 1:
                        pAnim = mpDialogA->getAnim(9);
                        break;
                    case 2:
                        pAnim = mpDialogA->getAnim(3);
                        break;
                }
                if (pAnim != NULL) {
                    pAnim->initAnmFrame();
                    pAnim->setAnmType(0);
                    pAnim->initFrame();
                    pAnim->restart();
                    if (mUnk30[idx] > 0) {
                        mUnk30[idx]--;
                    }
                }
            }
        }

        void SDMemory::onTrigDialogA(const char* name) {
            layout::Animator* pAnim = NULL;
            int idx = findDialogAPane(name);
            if (mUnk30[idx] > 0) {
                switch (idx) {
                    case 0:
                        pAnim = mpDialogA->getAnim(7);
                        break;
                    case 1:
                        pAnim = mpDialogA->getAnim(0xA);
                        break;
                    case 2:
                        pAnim = mpDialogA->getAnim(4);
                        break;
                }
                if (pAnim != NULL) {
                    mDialogBtnType = idx;
                    mCheckProgress = 2;
                    pAnim->initAnmFrame();
                    pAnim->setAnmType(0);
                    pAnim->initFrame();
                    pAnim->restart();
                    if (idx == 2) {
                        snd::sSystem.startSE("WIPL_SE_CANCEL");
                    } else {
                        snd::sSystem.startSE("WIPL_SE_DECIDE");
                    }
                }
            }
        }

        void SDMemoryDialogAEvent::onEvent(u32 compId, u32 event, void* data) {
            gui::PaneComponent* component = static_cast<gui::PaneComponent*>(mpManager->getComponent(compId));
            const char* paneName = component->getPane()->GetName();
            controller::Interface* con = reinterpret_cast<controller::Interface*>(data);
            switch (event) {
                case ::gui::EventHandler::ON_POINT: {
                    mpSDMemory->onPointDialogA(paneName, con);
                    break;
                }
                case ::gui::EventHandler::ON_LEFT: {
                    mpSDMemory->onLeftDialogA(paneName);
                    break;
                }
                case ::gui::EventHandler::ON_TRIG: {
                    if (con->downTrg(0x100800)) {
                        mpSDMemory->onTrigDialogA(paneName);
                    }
                    break;
                }
            }
        }

        int SDMemory::findDialogBPane(const char* name) {
            int result = -1;
            if (mDialogResult == 4) {
                for (int i = 0; i < 5; i++) {
                    if (strcmp(name, scDialogBBtnPanes5[i]) == 0) {
                        result = i;
                        break;
                    }
                }
            } else {
                for (int i = 0; i < 4; i++) {
                    if (strcmp(name, scDialogBBtnPanes4[i]) == 0) {
                        result = i + 1;
                        break;
                    }
                }
            }
            return result;
        }

        void SDMemory::onPointDialogB(const char* name, controller::Interface* con) {
            layout::Animator* pAnim = NULL;
            int idx = findDialogBPane(name);
            if (mUnk3C[idx] == 0) {
                switch (idx) {
                    case 0:
                        pAnim = mpDialogB->getAnim(5);
                        break;
                    case 1:
                        pAnim = mpDialogB->getAnim(8);
                        break;
                    case 2:
                        pAnim = mpDialogB->getAnim(0xB);
                        break;
                    case 3:
                        pAnim = mpDialogB->getAnim(0xE);
                        break;
                    case 4:
                        pAnim = mpDialogB->getAnim(2);
                        break;
                }
                if (pAnim != NULL) {
                    pAnim->initAnmFrame();
                    pAnim->setAnmType(0);
                    pAnim->initFrame();
                    pAnim->restart();
                    snd::sSystem.startSE("WIPL_SE_BT_TARGETTING");
                    if (con != NULL) {
                        con->rumble(0);
                    }
                    if (mUnk3C[idx] < 4) {
                        mUnk3C[idx]++;
                    }
                }
            }
        }

        void SDMemory::onLeftDialogB(const char* name) {
            layout::Animator* pAnim = NULL;
            int idx = findDialogBPane(name);
            if (mUnk3C[idx] == 1) {
                switch (idx) {
                    case 0:
                        pAnim = mpDialogB->getAnim(6);
                        break;
                    case 1:
                        pAnim = mpDialogB->getAnim(9);
                        break;
                    case 2:
                        pAnim = mpDialogB->getAnim(0xC);
                        break;
                    case 3:
                        pAnim = mpDialogB->getAnim(0xF);
                        break;
                    case 4:
                        pAnim = mpDialogB->getAnim(3);
                        break;
                }
                if (pAnim != NULL) {
                    pAnim->initAnmFrame();
                    pAnim->setAnmType(0);
                    pAnim->initFrame();
                    pAnim->restart();
                    if (mUnk3C[idx] > 0) {
                        mUnk3C[idx]--;
                    }
                }
            }
        }

        void SDMemory::onTrigDialogB(const char* name) {
            layout::Animator* pAnim = NULL;
            int idx = findDialogBPane(name);
            if (mUnk3C[idx] > 0) {
                switch (idx) {
                    case 0:
                        pAnim = mpDialogB->getAnim(7);
                        mpChanSelect->startSDWorker(&mFreeArea, &mNeededArea, unk_0x80, unk_0x380, &mMsgCount, 0);
                        break;
                    case 1:
                        pAnim = mpDialogB->getAnim(0xA);
                        mpChanSelect->startSDWorker(&mFreeArea, &mNeededArea, unk_0x80, unk_0x380, &mMsgCount, 1);
                        break;
                    case 2:
                        pAnim = mpDialogB->getAnim(0xD);
                        mpChanSelect->startSDWorker(&mFreeArea, &mNeededArea, unk_0x80, unk_0x380, &mMsgCount, 2);
                        break;
                    case 3:
                        pAnim = mpDialogB->getAnim(0x10);
                        mpChanSelect->startSDWorker(&mFreeArea, &mNeededArea, unk_0x80, unk_0x380, &mMsgCount, 3);
                        break;
                    case 4:
                        pAnim = mpDialogB->getAnim(4);
                        break;
                }
                if (pAnim != NULL) {
                    mDialogBtnType = idx;
                    mCheckProgress = 6;
                    pAnim->initAnmFrame();
                    pAnim->setAnmType(0);
                    pAnim->initFrame();
                    pAnim->restart();
                    if (idx >= 0 && idx <= 3) {
                        memset(mEntryList, 0, sizeof(mEntryList));
                        memset(mIdListA, 0, sizeof(mIdListA));
                        mField1648 = 0;
                        mField1340 = 0;
                        mCheckLists[0].ids = unk_0x80;
                        mCheckLists[0].count = mMsgCount;
                        mCheckLists[1].ids = mEntryList;
                        mCheckLists[1].count = 0;
                        mCheckLists[2].ids = mIdListA;
                        mCheckLists[2].count = 0;
                        mpChanSelect->iplSDChannelSelect_813DB58C(&mCheckLists[0], &mCheckLists[1], &mCheckLists[2]);
                    }
                    if (idx == 4) {
                        snd::sSystem.startSE("WIPL_SE_CANCEL");
                    } else {
                        snd::sSystem.startSE("WIPL_SE_DECIDE");
                    }
                }
            }
        }

        void SDMemoryDialogBEvent::onEvent(u32 compId, u32 event, void* data) {
            gui::PaneComponent* component = static_cast<gui::PaneComponent*>(mpManager->getComponent(compId));
            const char* paneName = component->getPane()->GetName();
            controller::Interface* con = reinterpret_cast<controller::Interface*>(data);
            switch (event) {
                case ::gui::EventHandler::ON_POINT: {
                    mpSDMemory->onPointDialogB(paneName, con);
                    break;
                }
                case ::gui::EventHandler::ON_LEFT: {
                    mpSDMemory->onLeftDialogB(paneName);
                    break;
                }
                case ::gui::EventHandler::ON_TRIG: {
                    if (con->downTrg(0x100800)) {
                        mpSDMemory->onTrigDialogB(paneName);
                    }
                    break;
                }
            }
        }

        int SDMemory::findDialogCPane(const char* name) {
            int result = -1;
            for (int i = 0; i < 4; i++) {
                if (strcmp(name, scDialogCBtnPanes[i]) == 0) {
                    result = i;
                    break;
                }
            }
            return result;
        }

        void SDMemory::onPointDialogC(const char* name, controller::Interface* con) {
            layout::Animator* pAnim = NULL;
            int idx = findDialogCPane(name);
            if (mScrFlags[idx] == 0) {
                switch (idx) {
                    case 2:
                        pAnim = mpDialogC->getAnim(2);
                        break;
                    case 3:
                        pAnim = mpDialogC->getAnim(5);
                        break;
                    case 0:
                        pAnim = mpDialogC->getAnim(0xB);
                        break;
                    case 1:
                        pAnim = mpDialogC->getAnim(8);
                        break;
                }
                if (pAnim != NULL) {
                    pAnim->initAnmFrame();
                    pAnim->setAnmType(0);
                    pAnim->initFrame();
                    pAnim->restart();
                    snd::sSystem.startSE("WIPL_SE_BT_TARGETTING");
                    if (con != NULL) {
                        con->rumble(0);
                    }
                    if ((int)mScrFlags[idx] < 4) {
                        mScrFlags[idx]++;
                    }
                }
            }
        }

        void SDMemory::onLeftDialogC(const char* name) {
            layout::Animator* pAnim = NULL;
            int idx = findDialogCPane(name);
            if (mScrFlags[idx] == 1) {
                switch (idx) {
                    case 2:
                        pAnim = mpDialogC->getAnim(3);
                        break;
                    case 3:
                        pAnim = mpDialogC->getAnim(6);
                        break;
                    case 0:
                        pAnim = mpDialogC->getAnim(0xC);
                        break;
                    case 1:
                        pAnim = mpDialogC->getAnim(9);
                        break;
                }
                if (pAnim != NULL) {
                    pAnim->initAnmFrame();
                    pAnim->setAnmType(0);
                    pAnim->initFrame();
                    pAnim->restart();
                    if (mScrFlags[idx] > 0) {
                        mScrFlags[idx]--;
                    }
                }
            }
        }

        void SDMemory::onTrigDialogC(const char* name) {
            layout::Animator* pAnim = NULL;
            int idx = findDialogCPane(name);
            if (mScrFlags[idx] > 0) {
                switch (idx) {
                    case 2:
                        if (!mScroller.is_busy()) {
                            pAnim = mpDialogC->getAnim(4);
                        }
                        break;
                    case 3:
                        if (!mScroller.is_busy()) {
                            pAnim = mpDialogC->getAnim(7);
                        }
                        break;
                    case 0:
                        if (!mScroller.is_busy()) {
                            pAnim = mpDialogC->getAnim(0xD);
                            mScroller.scrollUpByBtn();
                        }
                        break;
                    case 1:
                        if (!mScroller.is_busy()) {
                            pAnim = mpDialogC->getAnim(0xA);
                            mScroller.scrollDownByBtn();
                        }
                        break;
                }
                if (pAnim != NULL) {
                    mDialogBtnType = idx;
                    if ((u32)(idx - 2) <= 1) {
                        mCheckProgress = 0xB;
                    }
                    pAnim->initAnmFrame();
                    pAnim->setAnmType(0);
                    pAnim->initFrame();
                    pAnim->restart();
                    if (idx == 2) {
                        snd::sSystem.startSE("WIPL_SE_CANCEL");
                    } else if (idx == 3) {
                        snd::sSystem.startSE("WIPL_SE_DECIDE");
                    }
                }
            }
        }

        void SDMemoryDialogCEvent::onEvent(u32 compId, u32 event, void* data) {
            gui::PaneComponent* component = static_cast<gui::PaneComponent*>(mpManager->getComponent(compId));
            const char* paneName = component->getPane()->GetName();
            controller::Interface* con = reinterpret_cast<controller::Interface*>(data);
            switch (event) {
                case ::gui::EventHandler::ON_POINT: {
                    mpSDMemory->onPointDialogC(paneName, con);
                    break;
                }
                case ::gui::EventHandler::ON_LEFT: {
                    mpSDMemory->onLeftDialogC(paneName);
                    break;
                }
                case ::gui::EventHandler::ON_TRIG: {
                    if (con->downTrg(0x100800)) {
                        mpSDMemory->onTrigDialogC(paneName);
                    }
                    break;
                }
            }
        }

    }  // namespace scene
}  // namespace ipl
