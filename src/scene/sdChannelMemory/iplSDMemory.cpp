#define IPL_SDMEMORY_SCROLLER_INIT_OUT_OF_LINE
#define IPL_SDMEMORY_SET_TRANSLATE_OUT_OF_LINE
#define IPL_SDMEMORY_DIALOG_STATE_ACCESSOR
#define IPL_SDMEMORY_GET_TEXT_DRAW_RECT_OUT_OF_LINE
#include "scene/sdChannelMemory/iplSDMemory.h"
#undef IPL_SDMEMORY_DIALOG_STATE_ACCESSOR
#undef IPL_SDMEMORY_SET_TRANSLATE_OUT_OF_LINE
#undef IPL_SDMEMORY_SCROLLER_INIT_OUT_OF_LINE
#undef IPL_SDMEMORY_GET_TEXT_DRAW_RECT_OUT_OF_LINE

#include "system/iplSystem.h"
#include "sound/iplSound.h"
#include "utility/iplLayout.h"
#include <revolution/os/OSTime.h>

extern "C" bool iplSDChannelSelect_813DDB74(ipl::scene::NandSDCardManager* manager,
                                             ipl::scene::SDMemory::TitleRange* nandTitles,
                                             ipl::scene::SDMemory::TitleRange* sdTitles,
                                             ESTitleId* titleIds, wchar_t* titleNames, u32* titleCount,
                                             s32 state);
extern "C" bool iplSDChannelSelect_813DB5EC(ipl::scene::NandSDCardManager* manager,
                                             const ESTitleId* titleEntry, ESTitleId titleId);
extern "C" bool iplSDChannelSelect_813DB4D4(ipl::scene::NandSDCardManager* manager,
                                             const ESTitleId* titleEntry, ESTitleId titleId, u32 flags);

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
            "A", "B", "B_BtnA",
        };

        static const char* const sTitlePaneNames[] = {"A", "B", "B_BtnA", "C", "D"};
        static const char* const sAdditionalTitlePaneNames[] = {"B_00", "C_00", "D_00", "B_BtnA"};
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

        void SDMemory::onDialogState0() {
            if (!mpMainLayout->isPlaying(-1)) {
                for (int i = 0; i < 3; i++) {
                    mPanelStates[i] = 0;
                    nw4r::lyt::Pane* pane = mpMainLayout->FindPaneByName(sControlPaneNames[i]);
                    mpPaneManagers[0]->initPane(pane);
                }

                mDialogState = 1;
            }
        }

        void SDMemory::onDialogState2() {
            if (!mpMainLayout->isPlaying(-1)) {
                mpMainLayout->getAnim(1)->initAnmFrame();
                mpMainLayout->getAnim(1)->play();

                if (mProcessState == 2) {
                    mpProgressLayout->getAnim(1)->initAnmFrame();
                    mpProgressLayout->getAnim(1)->play();
                    mTransferFlags[1] = 0;
                }

                mDialogState = 3;
            }
        }

        bool SDMemory::onDialogState3() {
            if (!mpMainLayout->isPlaying(-1)) {
                switch (mProcessState) {
                case 0:
                    if (iplSDChannelSelect_813DDB74(mpNandSDCardManager, &mNandTitleRange, &mSDTitleRange,
                                                   mTitleIds, &mTitleNames[0][0], &mTitleCount, 2)) {
                        mDialogState = 4;
                        mpTitleLayout->getAnim(0)->initAnmFrame();
                        mpTitleLayout->getAnim(0)->play();
                        snd::getSystem()->startSE("WIPL_SE_INFO_WINDOW");
                    } else {
                        mDialogState = 21;
                        mMessageId = 0xB4;
                    }
                    break;
                case 1:
                    mDialogState = 21;
                    mMessageId = 0xB3;
                    break;
                case 2:
                    mDialogState = 25;
                    mErrorCode = 3;
                    return true;
                }
            }

            return false;
        }

        void SDMemory::onDialogState4() {
            if (!mpTitleLayout->isPlaying(-1)) {
                if (mDisplayMode == 4) {
                    for (int i = 0; i < 5; i++) {
                        mTitlePanelStates[i] = 0;
                        mpPaneManagers[1]->initPane(mpTitleLayout->GetRootPane()->FindPaneByName(sTitlePaneNames[i], true));
                    }
                } else {
                    for (int i = 1; i < 5; i++) {
                        mTitlePanelStates[i] = 0;
                        mpPaneManagers[1]->initPane(mpTitleLayout->GetRootPane()->FindPaneByName(sAdditionalTitlePaneNames[i - 1], true));
                    }
                }

                mDialogState = 5;
            }
        }

        void SDMemory::onDialogState6() {
            if (!mpTitleLayout->isPlaying(-1)) {
                mDialogState = 7;
                mpTitleLayout->getAnim(1)->initAnmFrame();
                mpTitleLayout->getAnim(1)->play();
            }
        }

        void SDMemory::onDialogState8() {
            if (System::getDialog()->getStateForSDMemory() == 2) {
                if (mTransferStartTime == 0) {
                    mTransferStartTime = OSGetTime();
                }

                if (!mpNandSDCardManager->getWorker()->is_working() &&
                    OSGetTime() - mTransferStartTime > OS_TIMER_CLOCK) {
                    System::getDialog()->terminate();
                }
            }

            if (System::getDialog()->getLastResult() != -1) {
                if (mpNandSDCardManager->getWorker()->get_async_result() == 0) {
                    mNandTitleCount = mTitleListState.mSecondaryCount;
                    mTitleNameCount = mTitleListState.mNameCount;
                } else {
                    mNandTitleCount = 0;
                    mTitleNameCount = 0;
                }

                mDialogState = 9;
                layout::Animator* animation = mpMainLayout->getAnim(0);
                animation->initFrame();
                animation->restart();

                nw4r::lyt::Pane* headerPane = mpMainLayout->FindPaneByName("T_Header");
                static_cast<nw4r::lyt::TextBox*>(headerPane)->SetString(System::getMessage(0xBE), 0);

                mButtonState = 0;
                nw4r::lyt::Pane* titlePane = mpMainLayout->FindPaneByName("N_Body");
                nw4r::lyt::Pane* bodyPane = mpMainLayout->FindPaneByName("T_Letter");
                bodyPane->SetAlpha(0xFF);

                for (u32 i = 0; i < mTitleCount; i++) {
                    utility::layout::set_string(bodyPane, mTitleNames[i]);
                    nw4r::ut::Rect textRect = mpMainLayout->getTextDrawRect("T_Letter");
                    f32 lineCount = -(textRect.bottom - textRect.top) / titlePane->GetSize().height;
                    mButtonState += static_cast<s32>(ceil(lineCount));
                }

                setScrollLimit();
                resetScrollArrows();
            }
        }

        void SDMemory::onDialogState7() {
            if (!mpTitleLayout->isPlaying(-1)) {
                switch (mProcessState) {
                case 4:
                    mDialogState = 0;
                    mpMainLayout->getAnim(0)->play();
                    snd::getSystem()->startSE("WIPL_SE_BT_TARGETTING");
                    break;
                default:
                    mTransferStartTime = 0;
                    mTransferFrame = 0;
                    System::getDialog()->callBtn0NoShade(0xCC, 0, true);
                    mDialogState = 8;
                    break;
                }
            }
        }



        void SDMemory::onDialogState9() {
            if (!mpDialogLayout->isPlaying(0)) {
                for (int i = 0; i < 4; i++) {
                    mPanelAnimationStates[i] = 0;
                    nw4r::lyt::Pane* pane = mpDialogLayout->FindPaneByName(sDialogPaneNames[i]);
                    mpPaneManagers[2]->initPane(pane);
                }

                mDialogState = 10;
            }
        }

        void SDMemory::onDialogState10() {
            controller::Interface* masterController = System::getMasterController();
            if (mScroller.isActive()) {
                updateSideArrows();
                if (mScroller.getBInst().isActive() ? false : true) {
                    if (masterController->down(controller::BTN_UP)) {
                        mScroller.scrollUpByCon();
                    } else if (masterController->down(controller::BTN_DOWN)) {
                        mScroller.scrollDownByCon();
                    }
                }
            }

            bool previousDownEnd = !!mControllerFlags[0];
            bool previousUpEnd = !!mControllerFlags[1];
            updateScrollArrows(previousDownEnd, previousUpEnd, mScroller.isUpEnd(), mScroller.isDownEnd());

            if (mScroller.getBInst().isActive() ? false : true) {
                mpPaneManagers[2]->update();
            }
            mpPaneManagers[2]->calc();
        }

        void SDMemory::onDialogState11() {
            if (!mpDialogLayout->isPlaying(4) && !mpDialogLayout->isPlaying(7)) {
                if (mProcessState < 4 && mProcessState >= 2) {
                    mDialogState = 12;
                    mpDialogLayout->getAnim(1)->initAnmFrame();
                    mpDialogLayout->getAnim(1)->play();

                    if (mControllerFlags[0] != 0) {
                        hideDownArrow();
                    }
                    if (mControllerFlags[1] != 0) {
                        hideUpArrow();
                    }
                } else {
                    mDialogState = 10;
                }
            }
        }

        void SDMemory::onDialogState16() {
            if (mTitleCount > mCurrentTitle && System::isReceiveScheduleStopped()) {
                const ESTitleId* titleEntry = &mTitleIds[mCurrentTitle];
                if (iplSDChannelSelect_813DB4D4(mpNandSDCardManager, titleEntry, *titleEntry, 0)) {
                    mDialogState = 16;
                } else {
                    System::getDialog()->terminate();
                    mDialogState = 20;
                    mErrorCode = 1;
                    mMessageId = 0xAE;
                }
            }
        }

        void SDMemory::onDialogState18() {
            if (System::getDialog()->getStateForSDMemory() == 2) {
                mCurrentTitleName[0] = L'\0';
                const wchar_t* message = System::getMessage(0xB1);
                const wchar_t* titleName = mTitleNames[mCurrentTitle];
                swprintf(mCurrentTitleName, 0x107f, L"%ls\n%ls", titleName, message);
                System::getDialog()->setTitleForSDMemory(mCurrentTitleName);

                const ESTitleId* titleEntry = &mTitleIds[mCurrentTitle];
                const ESTitleId titleId = *titleEntry;
                if (iplSDChannelSelect_813DB5EC(mpNandSDCardManager, titleEntry, titleId)) {
                    mDialogState = 18;
                } else {
                    System::getDialog()->terminate();
                    mDialogState = 20;
                    mErrorCode = 1;
                    mMessageId = 0xAE;
                }
            }
        }

        void SDMemory::onDialogState19() {
            if (!mpNandSDCardManager->getWorker()->is_working()) {
                if (mpNandSDCardManager->getWorker()->get_async_result() == 0) {
                    mDialogState = 13;
                } else {
                    System::getDialog()->terminate();
                    mDialogState = 20;
                    mErrorCode = 1;
                    mMessageId = 0xAE;
                }
            }
        }

        bool SDMemory::onDialogState20() {
            DialogWindow* dialog = System::getDialog();
            if (dialog->getStateForSDMemory() == 4 && mTransferFlags[1] && mErrorCode == 0) {
                mTransferFlags[1] = 0;
                mpProgressLayout->getAnim(1)->initAnmFrame();
                mpProgressLayout->getAnim(1)->play();
            }

            if (System::getDialog()->getLastResult() != -1) {
                if (mErrorCode == 0) {
                    mTransferFlags[0] = 1;
                    mDialogState = 25;
                    return true;
                }

                mDialogState = 23;
            }

            return false;
        }

        void SDMemory::onDialogState21() {
            const wchar_t* message = System::getMessage(mMessageId);
            const wchar_t* blockCountMarker = wcsstr(message, L"***\n");
            wchar_t* format = new (System::getMem2App(), -32) wchar_t[0x400];
            wchar_t* dialogMessage = new (System::getMem2App(), -32) wchar_t[0x400];

            if (blockCountMarker != NULL && message != NULL) {
                format[0] = L'\0';
                wcsncat(format, message, static_cast<u32>(blockCountMarker - message) >> 1);
                wcscat(format, L"%d");
                wcscat(format, blockCountMarker + 4);

                s32 blocks = mNandTitleRange.mByteSize / 0x20000;
                if (mNandTitleRange.mByteSize % 0x20000 != 0) {
                    blocks++;
                }

                swprintf(dialogMessage, 0x3ff, format, blocks);
            }

            System::getDialog()->callBtn2NoShade(dialogMessage, 0xC8, 0xA5, false);
            mDialogState = 22;

            delete[] format;
            delete[] dialogMessage;
        }

        bool SDMemory::onDialogState22() {
            DialogWindow* dialog = System::getDialog();
            if (dialog->getStateForSDMemory() == 3 && dialog->getResultForSDMemory() == 1) {
                mpProgressLayout->getAnim(1)->initAnmFrame();
                mpProgressLayout->getAnim(1)->play();
                mTransferFlags[1] = 0;
            }

            if (System::getDialog()->getLastResult() != -1) {
                if (System::getDialog()->getLastResult() == 1) {
                    mErrorCode = 4;
                    mDialogState = 25;
                    return true;
                }

                mpMainLayout->getAnim(0)->initAnmFrame();
                mpMainLayout->getAnim(0)->play();
                snd::getSystem()->startSE("WIPL_SE_CANCEL");
                mDialogState = 0;
            }

            return false;
        }

        void SDMemory::onDialogState23() {
            switch (mMessageId) {
            case 0xBF:
            case 0xB5:
                System::getDialog()->callBtn1NoShade(mMessageId, 0xA5);
                break;
            default:
                System::getDialog()->callBtn1NoShade(mMessageId, 0x2E);
                break;
            }

            mDialogState = 24;
        }

        bool SDMemory::onDialogState24() {
            if (System::getDialog()->getStateForSDMemory() == 3) {
                mpProgressLayout->getAnim(1)->initAnmFrame();
                mpProgressLayout->getAnim(1)->play();
                mTransferFlags[1] = 0;
            }

            if (System::getDialog()->getLastResult() != -1) {
                mTransferFlags[0] = 1;
                System::getHomeButtonMenu()->enable();
                mDialogState = 25;
                return true;
            }

            return false;
        }

        s32 SDMemory::getControlPaneIndex(const char* paneName) {
            s32 paneIndex = -1;
            for (s32 i = 0; i < 3; i++) {
                if (strcmp(paneName, sControlPaneNames[i]) == 0) {
                    paneIndex = i;
                    break;
                }
            }

            return paneIndex;
        }

        void writeFourFlagBytes(u8* flags, u8 first, u8 second, u8 third, u8 fourth) {
            flags[0] = first;
            flags[1] = second;
            flags[2] = third;
            flags[3] = fourth;
        }
    }
}
