#define IPL_SDMEMORY_SCROLLER_INIT_OUT_OF_LINE
#define IPL_SDMEMORY_SET_TRANSLATE_OUT_OF_LINE
#include "scene/sdChannelMemory/iplSDMemory.h"
#undef IPL_SDMEMORY_SET_TRANSLATE_OUT_OF_LINE
#undef IPL_SDMEMORY_SCROLLER_INIT_OUT_OF_LINE

#include "system/iplSystem.h"
#include "sound/iplSound.h"

namespace ipl {
    namespace utility {
        void Scroller::init() {
            mState = 0;
            mScroll = 0.0f;
            unk_0x3C = 0.0f;
            mUpLimit = 0.0f;
            mDownLimit = 0.0f;
        }
    }

    namespace scene {
        static const char* const sControlPaneNames[] = {
            "A", "B", "B_BtnA", "A", "B", "C", "D", "B_BtnA", "B_00", "C_00", "D_00", "B_BtnA",
        };

        static const char* const sDialogPaneNames[] = {"B_ArwR", "B_ArwL", "B_CalExit", "B_CalExit_00"};

        SDMemory::SDMemory() : mScroller() {}

        SDMemory::~SDMemory() {}

        void SDMemory::create(EGG::Heap* heap, nand::LayoutFile* layoutFile, NandSDCardManager* manager) {
            mpNandSDCardManager = manager;

            mpMainLayout = new (heap) layout::Object(heap, layoutFile, "arc", "mn_DialogWindow_ChChange_a.brlyt");
            mpMainLayout->bindToGroup("mn_DialogWindow_ChChange_a_DialogIn.brlan", "G_InOut", false, true);
            mpMainLayout->bindToGroup("mn_DialogWindow_ChChange_a_DialogOut.brlan", "G_InOut", false, true);
            mpMainLayout->bindToGroup("mn_DialogWindow_ChChange_a_FocusBtn_on.brlan", "G_FocusBtnA", false, true);
            mpMainLayout->bindToGroup("mn_DialogWindow_ChChange_a_FocusBtn_off.brlan", "G_FocusBtnA", false, true);
            mpMainLayout->bindToGroup("mn_DialogWindow_ChChange_a_SelectBtn_Ac.brlan", "G_SelectBtnA", false, true);
            mpMainLayout->bindToGroup("mn_DialogWindow_ChChange_a_BtnA_Rollover.brlan", "G_BtnA", false, true);
            mpMainLayout->bindToGroup("mn_DialogWindow_ChChange_a_BtnA_Rollout.brlan", "G_BtnA", false, true);
            mpMainLayout->bindToGroup("mn_DialogWindow_ChChange_a_BtnA_On.brlan", "G_BtnA", false, true);
            mpMainLayout->bindToGroup("mn_DialogWindow_ChChange_a_BtnB_Rollover.brlan", "G_BtnB", false, true);
            mpMainLayout->bindToGroup("mn_DialogWindow_ChChange_a_BtnB_Rollout.brlan", "G_BtnB", false, true);
            mpMainLayout->bindToGroup("mn_DialogWindow_ChChange_a_BtnB_On.brlan", "G_BtnB", false, true);
            mpMainLayout->finishBinding();
            mpMainLayout->getAnim(0)->initAnmFrame();
            mpMainLayout->getAnim(2)->initAnmFrame();
            mpMainLayout->getAnim(5)->initAnmFrame();
            mpMainLayout->getAnim(8)->initAnmFrame();

            nw4r::lyt::TextBox* textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpMainLayout->FindPaneByName("T_Dialog_00"));
            textBox->SetString(System::getMessage(0xB0));
            textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpMainLayout->FindPaneByName("TextBox_05"));
            textBox->SetString(System::getMessage(0xBB));
            textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpMainLayout->FindPaneByName("TextBox_06"));
            textBox->SetString(System::getMessage(0xBC));
            textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpMainLayout->FindPaneByName("T_BtnA"));
            textBox->SetString(System::getMessage(0x25));

            mpTitleLayout = new (heap) layout::Object(heap, layoutFile, "arc", "mn_DialogWindow_ChChange_b.brlyt");
            mpTitleLayout->bindToGroup("mn_DialogWindow_ChChange_b_DialogIn.brlan", "G_InOut", false, true);
            mpTitleLayout->bindToGroup("mn_DialogWindow_ChChange_b_DialogOut.brlan", "G_InOut", false, true);
            mpTitleLayout->bindToGroup("mn_DialogWindow_ChChange_b_FocusBtn_on.brlan", "G_FocusBtnA", false, true);
            mpTitleLayout->bindToGroup("mn_DialogWindow_ChChange_b_FocusBtn_off.brlan", "G_FocusBtnA", false, true);
            mpTitleLayout->bindToGroup("mn_DialogWindow_ChChange_b_SelectBtn_Ac.brlan", "G_SelectBtnA", false, true);
            mpTitleLayout->bindToGroup("mn_DialogWindow_ChChange_b_BtnA_Rollover.brlan", "G_BtnA", false, true);
            mpTitleLayout->bindToGroup("mn_DialogWindow_ChChange_b_BtnA_Rollout.brlan", "G_BtnA", false, true);
            mpTitleLayout->bindToGroup("mn_DialogWindow_ChChange_b_BtnA_On.brlan", "G_BtnA", false, true);
            mpTitleLayout->bindToGroup("mn_DialogWindow_ChChange_b_BtnB_Rollover.brlan", "G_BtnB", false, true);
            mpTitleLayout->bindToGroup("mn_DialogWindow_ChChange_b_BtnB_Rollout.brlan", "G_BtnB", false, true);
            mpTitleLayout->bindToGroup("mn_DialogWindow_ChChange_b_BtnB_On.brlan", "G_BtnB", false, true);
            mpTitleLayout->bindToGroup("mn_DialogWindow_ChChange_b_BtnC_Rollover.brlan", "G_BtnC", false, true);
            mpTitleLayout->bindToGroup("mn_DialogWindow_ChChange_b_BtnC_Rollout.brlan", "G_BtnC", false, true);
            mpTitleLayout->bindToGroup("mn_DialogWindow_ChChange_b_BtnC_On.brlan", "G_BtnC", false, true);
            mpTitleLayout->bindToGroup("mn_DialogWindow_ChChange_b_BtnD_Rollover.brlan", "G_BtnD", false, true);
            mpTitleLayout->bindToGroup("mn_DialogWindow_ChChange_b_BtnD_Rollout.brlan", "G_BtnD", false, true);
            mpTitleLayout->bindToGroup("mn_DialogWindow_ChChange_b_BtnD_On.brlan", "G_BtnD", false, true);
            mpTitleLayout->finishBinding();
            mpTitleLayout->getAnim(0)->initAnmFrame();
            mpTitleLayout->getAnim(2)->initAnmFrame();
            mpTitleLayout->getAnim(5)->initAnmFrame();
            mpTitleLayout->getAnim(8)->initAnmFrame();
            mpTitleLayout->getAnim(11)->initAnmFrame();
            mpTitleLayout->getAnim(14)->initAnmFrame();

            textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpTitleLayout->FindPaneByName("T_Dialog"));
            textBox->SetString(System::getMessage(0xB6));
            textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpTitleLayout->FindPaneByName("TextBox_00"));
            textBox->SetString(System::getMessage(0xB7));
            textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpTitleLayout->FindPaneByName("TextBox_01"));
            textBox->SetString(System::getMessage(0xB8));
            textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpTitleLayout->FindPaneByName("TextBox_02"));
            textBox->SetString(System::getMessage(0xB9));
            textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpTitleLayout->FindPaneByName("TextBox_03"));
            textBox->SetString(System::getMessage(0xBA));
            textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpTitleLayout->FindPaneByName("T_Dialog_00"));
            textBox->SetString(System::getMessage(0xB6));
            textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpTitleLayout->FindPaneByName("TextBox_05"));
            textBox->SetString(System::getMessage(0xB8));
            textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpTitleLayout->FindPaneByName("TextBox_06"));
            textBox->SetString(System::getMessage(0xB9));
            textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpTitleLayout->FindPaneByName("TextBox_07"));
            textBox->SetString(System::getMessage(0xBA));

            mpDialogLayout = new (heap) layout::Object(heap, layoutFile, "arc", "mn_DialogWindow_ChChange_c.brlyt");
            static_cast<nw4r::lyt::TextBox*>(mpDialogLayout->FindPaneByName("T_Letter"))->AllocStringBuffer(0x840);
            mpDialogLayout->bindToGroup("mn_DialogWindow_ChChange_c_Dialog_FadeIn.brlan", "G_Fede", false, true);
            mpDialogLayout->bindToGroup("mn_DialogWindow_ChChange_c_Dialog_FadeOut.brlan", "G_Fede", false, true);
            mpDialogLayout->bindToGroup("mn_DialogWindow_ChChange_c_Back_RollOver.brlan", "G_Back_Focus", false, true);
            mpDialogLayout->bindToGroup("mn_DialogWindow_ChChange_c_Back_Rollout.brlan", "G_Back_Focus", false, true);
            mpDialogLayout->bindToGroup("mn_DialogWindow_ChChange_c_Back_On.brlan", "G_Back_Ac", false, true);
            mpDialogLayout->bindToGroup("mn_DialogWindow_ChChange_c_Move_RollOver.brlan", "G_Move_Focus", false, true);
            mpDialogLayout->bindToGroup("mn_DialogWindow_ChChange_c_Move_Rollout.brlan", "G_Move_Focus", false, true);
            mpDialogLayout->bindToGroup("mn_DialogWindow_ChChange_c_Move_On.brlan", "G_Move_Ac", false, true);
            mpDialogLayout->bindToGroup("mn_DialogWindow_ChChange_c_FocusOn.brlan", "G_ArwL_Focus", false, true);
            mpDialogLayout->bindToGroup("mn_DialogWindow_ChChange_c_FocusOff.brlan", "G_ArwL_Focus", false, true);
            mpDialogLayout->bindToGroup("mn_DialogWindow_ChChange_c_Select.brlan", "G_ArwL_Ac", false, true);
            mpDialogLayout->bindToGroup("mn_DialogWindow_ChChange_c_FocusOn.brlan", "G_ArwR_Focus", false, true);
            mpDialogLayout->bindToGroup("mn_DialogWindow_ChChange_c_FocusOff.brlan", "G_ArwR_Focus", false, true);
            mpDialogLayout->bindToGroup("mn_DialogWindow_ChChange_c_Select.brlan", "G_ArwR_Ac", false, true);
            mpDialogLayout->bindToGroup("mn_DialogWindow_ChChange_c_Appear.brlan", "G_ArwL_End", false, true);
            mpDialogLayout->bindToGroup("mn_DialogWindow_ChChange_c_Lost.brlan", "G_ArwL_End", false, true);
            mpDialogLayout->bindToGroup("mn_DialogWindow_ChChange_c_Appear.brlan", "G_ArwR_End", false, true);
            mpDialogLayout->bindToGroup("mn_DialogWindow_ChChange_c_Lost.brlan", "G_ArwR_End", false, true);
            mpDialogLayout->bindToGroup("mn_DialogWindow_ChChange_c_Loop.brlan", "G_ArwRoop", false, true);
            mpDialogLayout->bindToGroup("mn_DialogWindow_ChChange_c_HDActionStart.brlan", "G_ArwL_HDAc", false, true);
            mpDialogLayout->bindToGroup("mn_DialogWindow_ChChange_c_HDActionEnd.brlan", "G_ArwL_HDAc", false, true);
            mpDialogLayout->bindToGroup("mn_DialogWindow_ChChange_c_HDActionStart.brlan", "G_ArwR_HDAc", false, true);
            mpDialogLayout->bindToGroup("mn_DialogWindow_ChChange_c_HDActionEnd.brlan", "G_ArwR_HDAc", false, true);
            mpDialogLayout->finishBinding();
            mpDialogLayout->getAnim(0)->initAnmFrame();
            mpDialogLayout->getAnim(2)->initAnmFrame();
            mpDialogLayout->getAnim(5)->initAnmFrame();
            mpDialogLayout->getAnim(11)->initAnmFrame();
            mpDialogLayout->getAnim(8)->initAnmFrame();
            mpDialogLayout->getAnim(18)->initAnmFrame();
            mpDialogLayout->getAnim(18)->initFrame();
            mpDialogLayout->getAnim(18)->restart();

            textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpDialogLayout->FindPaneByName("T_CalExit"));
            textBox->SetString(System::getMessage(0xA5));
            textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpDialogLayout->FindPaneByName("T_CalExit_00"));
            textBox->SetString(System::getMessage(0xC4));

            mpProgressLayout = new (heap) layout::Object(heap, layoutFile, "arc", "mn_DialogWindow_Background.brlyt");
            mpProgressLayout->bindToGroup("mn_DialogWindow_Background_DialogIn.brlan", "G_InOut", false, true);
            mpProgressLayout->bindToGroup("mn_DialogWindow_Background_DialogOut.brlan", "G_InOut", false, true);
            mpProgressLayout->finishBinding();
            mpProgressLayout->getAnim(0)->initAnmFrame();

        }

        void SDMemory::setTitleLists(const TitleRange& nandTitles, const TitleRange& sdTitles) {
            mNandTitleRange = nandTitles;
            mSDTitleRange = sdTitles;
            mTransferFlags[0] = 1;
            mDialogState = 0;
            mpMainLayout->getAnim(0)->initAnmFrame();
            mpMainLayout->getAnim(0)->play();
            mpProgressLayout->getAnim(0)->initAnmFrame();
            mpProgressLayout->getAnim(0)->play();
            snd::getSystem()->startSE("WIPL_SE_INFO_WINDOW");
            mTransferFlags[1] = 1;
            mErrorCode = 0;
        }

        void SDMemory::setScrollLimit() {
            nw4r::lyt::Pane* headerPane = mpDialogLayout->FindPaneByName("N_Header");
            nw4r::lyt::Pane* buttonPane = mpDialogLayout->FindPaneByName("T_BtnA");
            nw4r::lyt::Pane* footerPane = mpDialogLayout->FindPaneByName("N_Footer");

            nw4r::ut::Rect projection;
            System::getProjectionRect(&projection);

            f32 itemCount = static_cast<f32>(mButtonState);
            f32 buttonHeight = buttonPane->GetSize().height;
            f32 headerHeight = headerPane->GetSize().height;
            f32 footerHeight = footerPane->GetSize().height;
            f32 contentHeight = headerHeight + footerHeight;
            f32 itemHeight = itemCount * buttonHeight;
            f32 contentHeightWithItems = itemHeight + contentHeight;
            f32 downLimit = contentHeightWithItems - projection.GetHeight() + 1.0f;
            if (downLimit < 0.0f) {
                downLimit = 0.0f;
            }

            mScroller.init();
            mScroller.setDownLimit(downLimit);
        }

        void SDMemory::updateSideArrows() {
            controller::Interface* masterController = System::getMasterController();

            if (mScroller.getBInst().isActive() ? false : true) {
                if (masterController->down(controller::BTN_UP)) {
                    showLeftArrow();
                }
                if (!masterController->down(controller::BTN_UP)) {
                    hideLeftArrow();
                }
                if (masterController->down(controller::BTN_DOWN)) {
                    showRightArrow();
                }
                if (!masterController->down(controller::BTN_DOWN)) {
                    hideRightArrow();
                }
            } else {
                if (mScroller.getBInst().isUp()) {
                    showLeftArrow();
                }
                if (!mScroller.getBInst().isUp()) {
                    hideLeftArrow();
                }
                if (mScroller.getBInst().isDown()) {
                    showRightArrow();
                }
                if (!mScroller.getBInst().isDown()) {
                    hideRightArrow();
                }
            }
        }

        void SDMemory::resetScrollArrows() {
            mControllerFlags[0] = 0;
            mControllerFlags[1] = 0;
            mControllerFlags[2] = 0;
            mControllerFlags[3] = 0;
            mpDialogLayout->getAnim(16)->initAnmFrame();
            mpDialogLayout->getAnim(14)->initAnmFrame();
            if (!mScroller.isDownEnd()) {
                showUpArrow();
            }
        }

        void SDMemory::updateScrollArrows(u32 previousDownEnd, u32 previousUpEnd, u32 downEnd, u32 upEnd) {
            if (previousDownEnd != 1 && downEnd == 1) {
                hideDownArrow();
            }
            if (previousDownEnd == 1 && downEnd != 1) {
                showDownArrow();
            }
            if (previousUpEnd != 1 && upEnd == 1) {
                hideUpArrow();
            }
            if (previousUpEnd == 1 && upEnd != 1) {
                showUpArrow();
            }
        }

        void SDMemory::showDownArrow() {
            if (mControllerFlags[0] == 0) {
                layout::Animator* initAnimation = mpDialogLayout->getAnim(16);
                initAnimation->initAnmFrame();
                layout::Animator* playAnimation = mpDialogLayout->getAnim(16);
                playAnimation->initFrame();
                playAnimation->restart();
                mControllerFlags[0] = 1;
            }
        }

        void SDMemory::showUpArrow() {
            if (mControllerFlags[1] == 0) {
                layout::Animator* initAnimation = mpDialogLayout->getAnim(14);
                initAnimation->initAnmFrame();
                layout::Animator* playAnimation = mpDialogLayout->getAnim(14);
                playAnimation->initFrame();
                playAnimation->restart();
                mControllerFlags[1] = 1;
            }
        }

        void SDMemory::hideDownArrow() {
            if (mControllerFlags[0] != 0) {
                layout::Animator* initAnimation = mpDialogLayout->getAnim(17);
                initAnimation->initAnmFrame();
                layout::Animator* playAnimation = mpDialogLayout->getAnim(17);
                playAnimation->initFrame();
                playAnimation->restart();
                mControllerFlags[0] = 0;
            }
        }

        void SDMemory::hideUpArrow() {
            if (mControllerFlags[1] != 0) {
                layout::Animator* initAnimation = mpDialogLayout->getAnim(15);
                initAnimation->initAnmFrame();
                layout::Animator* playAnimation = mpDialogLayout->getAnim(15);
                playAnimation->initFrame();
                playAnimation->restart();
                mControllerFlags[1] = 0;
            }
        }

        void SDMemory::showLeftArrow() {
            if (mControllerFlags[2] == 0) {
                layout::Animator* animation = mpDialogLayout->getAnim(19);
                animation->initFrame();
                animation->restart();
                mControllerFlags[2] = 1;
            }
        }

        void SDMemory::showRightArrow() {
            if (mControllerFlags[3] == 0) {
                layout::Animator* animation = mpDialogLayout->getAnim(21);
                animation->initFrame();
                animation->restart();
                mControllerFlags[3] = 1;
            }
        }

        void SDMemory::hideLeftArrow() {
            if (mControllerFlags[2] != 0) {
                layout::Animator* animation = mpDialogLayout->getAnim(20);
                animation->initFrame();
                animation->restart();
                mControllerFlags[2] = 0;
            }
        }

        void SDMemory::hideRightArrow() {
            if (mControllerFlags[3] != 0) {
                layout::Animator* animation = mpDialogLayout->getAnim(22);
                animation->initFrame();
                animation->restart();
                mControllerFlags[3] = 0;
            }
        }

        void SDMemory::resetDialogPaneAnimations() {
            for (int i = 0; i < 4; i++) {
                if (mPanelAnimationStates[i] != 0) {
                    mPanelAnimationStates[i] = 0;
                    nw4r::lyt::Pane* pane = mpDialogLayout->FindPaneByName(sDialogPaneNames[i]);
                    mpPaneManagers[2]->initPane(pane);

                    layout::Animator* animation = NULL;
                    switch (i) {
                    case 2:
                        animation = mpDialogLayout->getAnim(3);
                        break;
                    case 3:
                        animation = mpDialogLayout->getAnim(6);
                        break;
                    case 0:
                        animation = mpDialogLayout->getAnim(12);
                        break;
                    case 1:
                        animation = mpDialogLayout->getAnim(9);
                        break;
                    }

                    if (animation != NULL) {
                        animation->initAnmFrame();
                        animation->initFrame();
                        animation->restart();
                    }
                }
            }
        }

        bool SDMemory::calc() {
            bool result = false;
            s32 stateResult = updateState();
            if (stateResult == 0) {
                if (mScroller.calc(mDialogState == 10) == TRUE) {
                    resetDialogPaneAnimations();
                }

                nw4r::math::VEC3 translation(0.0f, mScroller.get(), 0.0f);
                mpDialogLayout->FindPaneByName("N_Memo")->SetTranslate(translation);

                switch (mDialogState) {
                case 0:
                    onDialogState0();
                    break;
                case 1:
                    mpPaneManagers[0]->update();
                    mpPaneManagers[0]->calc();
                    break;
                case 2:
                    onDialogState2();
                    break;
                case 3:
                    result = onDialogState3();
                    break;
                case 4:
                    onDialogState4();
                    break;
                case 5:
                    mpPaneManagers[1]->update();
                    mpPaneManagers[1]->calc();
                    break;
                case 6:
                    onDialogState6();
                    break;
                case 7:
                    onDialogState7();
                    break;
                case 8:
                    onDialogState8();
                    break;
                case 9:
                    onDialogState9();
                    break;
                case 10:
                    onDialogState10();
                    break;
                case 11:
                    onDialogState11();
                    break;
                case 12:
                    onDialogState12();
                    break;
                case 13:
                    onDialogState13();
                    break;
                case 14:
                    onDialogState14();
                    break;
                case 15:
                    onDialogState15();
                    break;
                case 16:
                    onDialogState16();
                    break;
                case 17:
                    onDialogState17();
                    break;
                case 18:
                    onDialogState18();
                    break;
                case 19:
                    onDialogState19();
                    break;
                case 20:
                    result = onDialogState20();
                    break;
                case 21:
                    onDialogState21();
                    break;
                case 22:
                    result = onDialogState22();
                    break;
                case 23:
                    onDialogState23();
                    break;
                case 24:
                    result = onDialogState24();
                    break;
                case 25:
                    result = true;
                    break;
                }
            }

            mpMainLayout->calc();
            mpTitleLayout->calc();
            mpDialogLayout->calc();
            mpProgressLayout->calc();

            return stateResult == 2 ? true : result;
        }
    }
}
