#define IPL_SDMEMORY_TITLE_CACHE_ACCESS
#define IPL_SDMEMORY_SCROLLER_INIT_OUT_OF_LINE
#define IPL_SDMEMORY_SET_TRANSLATE_OUT_OF_LINE
#define IPL_SDMEMORY_DIALOG_STATE_ACCESSOR
#define IPL_SDMEMORY_GET_TEXT_DRAW_RECT_OUT_OF_LINE
#define IPL_SDMEMORY_SCROLLER_BINST_RESET
#define IPL_SDMEMORY_SD_CHANNEL_SELECT_LAYOUT
#define IPL_SDMEMORY_COMPLETION_PCT_ACCESSOR
#define IPL_SDMEMORY_DIALOG_PROGRESS_FRAME_ACCESSOR
#define IPL_SDMEMORY_SET_TEXT_COLORS
#define IPL_SDMEMORY_SCROLLER_STATE_ACCESSOR
#include "system/iplDialogWindow.h"
#undef IPL_SDMEMORY_DIALOG_PROGRESS_FRAME_ACCESSOR
#include "scene/sdChannelMemory/iplSDMemory.h"
#include "scene/sdChannelSelect/iplSDChannelSelect.h"
#undef IPL_SDMEMORY_SET_TEXT_COLORS
#undef IPL_SDMEMORY_SCROLLER_STATE_ACCESSOR
#undef IPL_SDMEMORY_DIALOG_STATE_ACCESSOR
#undef IPL_SDMEMORY_SET_TRANSLATE_OUT_OF_LINE
#undef IPL_SDMEMORY_SCROLLER_INIT_OUT_OF_LINE
#undef IPL_SDMEMORY_GET_TEXT_DRAW_RECT_OUT_OF_LINE
#undef IPL_SDMEMORY_SCROLLER_BINST_RESET
#undef IPL_SDMEMORY_SD_CHANNEL_SELECT_LAYOUT
#undef IPL_SDMEMORY_COMPLETION_PCT_ACCESSOR

#include "system/iplSystem.h"
#include "sound/iplSound.h"
#include "utility/iplLayout.h"
#include <revolution/os/OSTime.h>

extern "C" bool iplSDChannelSelect_813DDB74(ipl::scene::SDChannelSelect* channelSelect,
                                             ipl::scene::SDMemory::TitleRange* nandTitles,
                                             ipl::scene::SDMemory::TitleRange* sdTitles,
                                             ESTitleId* titleIds, wchar_t* titleNames, u32* titleCount,
                                             s32 state);
extern "C" bool iplSDChannelSelect_813DB5EC(ipl::scene::SDChannelSelect* channelSelect,
                                             ESTitleId titleId);
extern "C" bool iplSDChannelSelect_813DB4D4(ipl::scene::SDChannelSelect* channelSelect,
                                             ESTitleId titleId, u32 flags);
extern "C" bool iplSDChannelSelect_813DB530(ipl::scene::SDChannelSelect* channelSelect,
                                             ESTitleId** titleNames, ESTitleId** secondaryTitles);
extern "C" bool iplSDChannelSelect_813DB478(ipl::scene::SDChannelSelect* channelSelect,
                                             ESTitleId titleId);
extern "C" bool iplSDChannelSelect_813DB58C(ipl::scene::SDChannelSelect* channelSelect,
                                             ESTitleId** titles, ESTitleId** secondaryTitles,
                                             ESTitleId** names);

namespace ipl {
    namespace scene {
        typedef ::gui::Component GuiComponent;
        typedef ::gui::PaneComponent GuiPaneComponent;
        typedef controller::Interface ControllerInterface;

        void writeFourFlagBytes(u8* flags, u8 first, u8 second, u8 third, u8 fourth);

        void setTitleRowColors(nw4r::lyt::TextBox* textBox, const nw4r::ut::Color& first,
                               const nw4r::ut::Color& second) NO_INLINE;

        static const char* sControlPaneNames[] = {
            "A", "B", "B_BtnA",
        };

        static const char* sTitlePaneNames[] = {"A", "B", "C", "D", "B_BtnA"};
        static const char* sAdditionalTitlePaneNames[] = {"B_00", "C_00", "D_00", "B_BtnA"};
        static const char* sDialogPaneNames[] = {"B_ArwR", "B_ArwL", "B_CalExit", "B_CalExit_00"};

        SDMemory::SDMemory() : mScroller() {}

        SDMemory::~SDMemory() {}

        void SDMemory::create(EGG::Heap* heap, nand::LayoutFile* layoutFile, SDChannelSelect* channelSelect) {
            s32 cachedTitleCount;
            const savedata::Manager* saveData;
            nw4r::lyt::TextBox* textBox;
            layout::Animator* scrollAnimator;
            ControlPaneEventHandler* controlEvent;
            TitlePaneEventHandler* titleEvent;
            DialogPaneEventHandler* dialogEvent;
            mpSDChannelSelect = channelSelect;

            mpMainLayout = new layout::Object(heap, layoutFile, "arc", "mn_DialogWindow_ChChange_a.brlyt");
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

            textBox = static_cast<nw4r::lyt::TextBox*>(mpMainLayout->FindPaneByName("T_Dialog_00"));
            textBox->SetString(System::getMessage(0xB0));
            textBox = static_cast<nw4r::lyt::TextBox*>(mpMainLayout->FindPaneByName("TextBox_05"));
            textBox->SetString(System::getMessage(0xBB));
            textBox = static_cast<nw4r::lyt::TextBox*>(mpMainLayout->FindPaneByName("TextBox_06"));
            textBox->SetString(System::getMessage(0xBC));
            textBox = static_cast<nw4r::lyt::TextBox*>(mpMainLayout->FindPaneByName("T_BtnA"));
            textBox->SetString(System::getMessage(0x25));

            mpTitleLayout = new layout::Object(heap, layoutFile, "arc", "mn_DialogWindow_ChChange_b.brlyt");
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

            textBox = static_cast<nw4r::lyt::TextBox*>(mpTitleLayout->FindPaneByName("T_Dialog"));
            textBox->SetString(System::getMessage(0xB6));
            textBox = static_cast<nw4r::lyt::TextBox*>(mpTitleLayout->FindPaneByName("TextBox_00"));
            textBox->SetString(System::getMessage(0xB7));
            textBox = static_cast<nw4r::lyt::TextBox*>(mpTitleLayout->FindPaneByName("TextBox_01"));
            textBox->SetString(System::getMessage(0xB8));
            textBox = static_cast<nw4r::lyt::TextBox*>(mpTitleLayout->FindPaneByName("TextBox_02"));
            textBox->SetString(System::getMessage(0xB9));
            textBox = static_cast<nw4r::lyt::TextBox*>(mpTitleLayout->FindPaneByName("TextBox_03"));
            textBox->SetString(System::getMessage(0xBA));
            textBox = static_cast<nw4r::lyt::TextBox*>(mpTitleLayout->FindPaneByName("T_Dialog_00"));
            textBox->SetString(System::getMessage(0xB6));
            textBox = static_cast<nw4r::lyt::TextBox*>(mpTitleLayout->FindPaneByName("TextBox_05"));
            textBox->SetString(System::getMessage(0xB8));
            textBox = static_cast<nw4r::lyt::TextBox*>(mpTitleLayout->FindPaneByName("TextBox_06"));
            textBox->SetString(System::getMessage(0xB9));
            textBox = static_cast<nw4r::lyt::TextBox*>(mpTitleLayout->FindPaneByName("TextBox_07"));
            textBox->SetString(System::getMessage(0xBA));

            saveData = System::getSaveData();
            cachedTitleCount = 0;
            for (s32 i = 0; i < 48; ++i) {
                if (saveData->getTitleCacheEntry(i) == 0) {
                    break;
                }
                ++cachedTitleCount;
            }
            if (cachedTitleCount >= 5) {
                mpTitleLayout->FindPaneByName("N_Btn_3")->SetVisible(false);
                nw4r::lyt::Pane* expandedButton = mpTitleLayout->FindPaneByName("N_Btn_4");
                expandedButton->SetVisible(true);
                mDisplayMode = 4;
            } else {
                nw4r::lyt::Pane* compactButton = mpTitleLayout->FindPaneByName("N_Btn_3");
                compactButton->SetVisible(true);
                mpTitleLayout->FindPaneByName("N_Btn_4")->SetVisible(false);
                mDisplayMode = 3;
            }
            textBox = static_cast<nw4r::lyt::TextBox*>(mpTitleLayout->FindPaneByName("T_BtnA"));
            textBox->SetString(System::getMessage(0xA5));

            mpDialogLayout = new layout::Object(heap, layoutFile, "arc", "mn_DialogWindow_ChChange_c.brlyt");
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
            scrollAnimator = mpDialogLayout->getAnim(18);
            scrollAnimator->initFrame();
            scrollAnimator->restart();

            textBox = static_cast<nw4r::lyt::TextBox*>(mpDialogLayout->FindPaneByName("T_CalExit"));
            textBox->SetString(System::getMessage(0xA5));
            textBox = static_cast<nw4r::lyt::TextBox*>(mpDialogLayout->FindPaneByName("T_CalExit_00"));
            textBox->SetString(System::getMessage(0xC4));

            mpProgressLayout = new layout::Object(heap, layoutFile, "arc", "mn_DialogWindow_Background.brlyt");
            mpProgressLayout->bindToGroup("mn_DialogWindow_Background_DialogIn.brlan", "G_InOut", false, true);
            mpProgressLayout->bindToGroup("mn_DialogWindow_Background_DialogOut.brlan", "G_InOut", false, true);
            mpDialogLayout->finishBinding();
            mpProgressLayout->getAnim(0)->initAnmFrame();

            controlEvent = new ControlPaneEventHandler(this);
            mpPaneManagers[0] = new gui::PaneManager(controlEvent, mpMainLayout->getDrawInfo(), NULL, NULL);
            mpPaneManagers[0]->setupScene(mpMainLayout);
            mpPaneManagers[0]->setAllComponentTriggerTarget(false);
            for (s32 i = 0; i < 3; ++i) {
                mpPaneManagers[0]->setTriggerTarget(mpMainLayout->FindPaneByName(sControlPaneNames[i]), true);
            }

            titleEvent = new TitlePaneEventHandler(this);
            mpPaneManagers[1] = new gui::PaneManager(titleEvent, mpTitleLayout->getDrawInfo(), NULL, NULL);
            mpPaneManagers[1]->setupScene(mpTitleLayout);
            mpPaneManagers[1]->setAllComponentTriggerTarget(false);
            if (mDisplayMode == 4) {
                for (s32 i = 0; i < 5; ++i) {
                    mpPaneManagers[1]->setTriggerTarget(mpTitleLayout->FindPaneByName(sTitlePaneNames[i]), true);
                }
            } else {
                for (s32 i = 0; i < 4; ++i) {
                    mpPaneManagers[1]->setTriggerTarget(
                        mpTitleLayout->FindPaneByName(sAdditionalTitlePaneNames[i]), true);
                }
            }

            dialogEvent = new DialogPaneEventHandler(this);
            mpPaneManagers[2] = new gui::PaneManager(dialogEvent, mpDialogLayout->getDrawInfo(), NULL, NULL);
            mpPaneManagers[2]->setupScene(mpDialogLayout);
            mpPaneManagers[2]->setAllComponentTriggerTarget(false);
            for (s32 i = 0; i < 4; ++i) {
                mpPaneManagers[2]->setTriggerTarget(mpDialogLayout->FindPaneByName(sDialogPaneNames[i]), true);
            }

            mTransferFlags[0] = 1;
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
            nw4r::lyt::Pane* buttonPane = mpDialogLayout->FindPaneByName("N_Body");
            nw4r::lyt::Pane* footerPane = mpDialogLayout->FindPaneByName("N_Footer");

            nw4r::ut::Rect projection;
            System::getProjectionRect(&projection);

            f32 downLimit = 160.0f + (static_cast<f32>(mButtonState) * buttonPane->GetSize().height +
                (headerPane->GetSize().height + footerPane->GetSize().height) - projection.GetHeight());
            if (downLimit < 0.0f) {
                downLimit = 0.0f;
            }

            mScroller.init();
            mScroller.setDownLimit(downLimit);
        }

    }

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
                    mpPaneManagers[2]->initPane(mpDialogLayout->GetRootPane()->FindPaneByName(sDialogPaneNames[i], true));

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
                case 19:
                    onDialogState13();
                    break;
                case 13:
                    onDialogState14();
                    break;
                case 14:
                    onDialogState15();
                    break;
                case 15:
                    onDialogState16();
                    break;
                case 16:
                    onDialogState17();
                    break;
                case 17:
                    onDialogState18();
                    break;
                case 18:
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

        s32 SDMemory::updateState() {
            NandSDWorker::WorkSDState sdState = mpSDChannelSelect->getSDState();
            s32 result = 0;
            if (sdState == NandSDWorker::SD_STATE_EJECTED || sdState == NandSDWorker::SD_STATE_INSERTED) {
                switch (mDialogState) {
                case 1:
                case 2: {
                    mpMainLayout->getAnim(1)->initAnmFrame();
                    mpMainLayout->getAnim(1)->play();
                    mpProgressLayout->getAnim(1)->initAnmFrame();
                    mpProgressLayout->getAnim(1)->play();
                    mTransferFlags[1] = 0;
                    mDialogState = 3;
                    result = 1;
                    break;
                }
                case 3:
                    if (mTransferFlags[1] != 0) {
                        mpProgressLayout->getAnim(1)->initAnmFrame();
                        mpProgressLayout->getAnim(1)->play();
                        mTransferFlags[1] = 0;
                    }
                    if (!mpMainLayout->isPlaying(1) && !mpProgressLayout->isPlaying(1)) {
                        result = 2;
                    } else {
                        result = 1;
                    }
                    break;
                case 5:
                case 6:
                    mpTitleLayout->getAnim(1)->initAnmFrame();
                    mpTitleLayout->getAnim(1)->play();
                    mpProgressLayout->getAnim(1)->initAnmFrame();
                    mpProgressLayout->getAnim(1)->play();
                    mTransferFlags[1] = 0;
                    mDialogState = 7;
                    result = 1;
                    break;
                case 7:
                    if (mTransferFlags[1] != 0) {
                        mpProgressLayout->getAnim(1)->initAnmFrame();
                        mpProgressLayout->getAnim(1)->play();
                        mTransferFlags[1] = 0;
                    }
                    if (!mpTitleLayout->isPlaying(1) && !mpProgressLayout->isPlaying(1)) {
                        result = 2;
                    } else {
                        result = 1;
                    }
                    break;
                case 10:
                case 11:
                    mDialogState = 12;
                    mpDialogLayout->getAnim(1)->initAnmFrame();
                    mpDialogLayout->getAnim(1)->play();
                    mpProgressLayout->getAnim(1)->initAnmFrame();
                    mpProgressLayout->getAnim(1)->play();
                    mTransferFlags[1] = 0;
                    mScroller.initScroll();
                    mScroller.resetBInst();
                    if (mControllerFlags[0] != 0) {
                        hideDownArrow();
                    }
                    if (mControllerFlags[1] != 0) {
                        hideUpArrow();
                    }
                    result = 1;
                    break;
                case 12:
                    if (mTransferFlags[1] != 0) {
                        mScroller.initScroll();
                        mScroller.resetBInst();
                        mpProgressLayout->getAnim(1)->initAnmFrame();
                        mpProgressLayout->getAnim(1)->play();
                        mTransferFlags[1] = 0;
                    }
                    if (!mpDialogLayout->isPlaying(1) && !mpProgressLayout->isPlaying(1)) {
                        result = 2;
                    } else {
                        result = 1;
                    }
                    break;
                case 8:
                case 22: {
                    if (sdState == NandSDWorker::SD_STATE_EJECTED || sdState == NandSDWorker::SD_STATE_INSERTED) {
                        if (System::getDialog()->getStateForSDMemory() == 2) {
                            System::getDialog()->terminate();
                            mpProgressLayout->getAnim(1)->initAnmFrame();
                            mpProgressLayout->getAnim(1)->play();
                            mTransferFlags[1] = 0;
                        } else if (System::getDialog()->getStateForSDMemory() == 4 ||
                                   System::getDialog()->getStateForSDMemory() == 3) {
                            if (mTransferFlags[1] != 0) {
                                mpProgressLayout->getAnim(1)->initAnmFrame();
                                mpProgressLayout->getAnim(1)->play();
                                mTransferFlags[1] = 0;
                            }
                        }
                    }

                    if (System::getDialog()->getLastResult() != -1 && !mpProgressLayout->isPlaying(1)) {
                        if (System::getDialog()->getLastResult() != 1 &&
                            (sdState == NandSDWorker::SD_STATE_EJECTED || sdState == NandSDWorker::SD_STATE_INSERTED)) {
                            result = 2;
                        }
                    } else {
                        result = 1;
                    }
                    break;
                }
                default:
                    break;
                }

            }

            if (result == 2) {
                mErrorCode = 6;
            }
            return result;
        }

        void SDMemory::onDialogState0() {
            if (!mpMainLayout->isPlaying(-1)) {
                for (int i = 0; i < 3; i++) {
                    mPanelStates[i] = 0;
                    mpPaneManagers[0]->initPane(mpMainLayout->GetRootPane()->FindPaneByName(sControlPaneNames[i], true));
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
                    if (iplSDChannelSelect_813DDB74(mpSDChannelSelect, &mNandTitleRange, &mSDTitleRange,
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

        void SDMemory::onDialogState7() {
            if (!mpTitleLayout->isPlaying(-1)) {
                switch (mProcessState) {
                case 4:
                    mDialogState = 0;
                    mpMainLayout->getAnim(0)->play();
                    snd::getSystem()->startSE("WIPL_SE_INFO_WINDOW");
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


        void SDMemory::onDialogState8() {
            if (System::getDialog()->getStateForSDMemory() == 2) {
                if (mTransferStartTime == 0) {
                    mTransferStartTime = OSGetTime();
                }

                if (!mpSDChannelSelect->getWorker()->is_working() &&
                    static_cast<s64>(OSGetTime() - mTransferStartTime) > static_cast<s64>(OS_TIMER_CLOCK)) {
                    System::getDialog()->terminate();
                }
            }

            if (System::getDialog()->getLastResult() != -1) {
                if (mpSDChannelSelect->getWorker()->get_async_result() == NandSDWorker::RESULT_OK) {
                    mNandTitleCount = mTitleListState.mSecondaryCount;
                    mTitleNameCount = mTitleListState.mNameCount;
                } else {
                    mNandTitleCount = 0;
                    mTitleNameCount = 0;
                }

                mDialogState = 9;
                layout::Animator* animation = mpDialogLayout->getAnim(0);
                animation->initFrame();
                animation->restart();

                nw4r::lyt::TextBox* titleText = static_cast<nw4r::lyt::TextBox*>(mpDialogLayout->FindPaneByName("T_Header"));
                titleText->SetString(System::getMessage(0xBE), 0);

                mButtonState = 0;
                nw4r::lyt::Pane* titlePane = mpDialogLayout->FindPaneByName("N_Body");
                titleText = static_cast<nw4r::lyt::TextBox*>(mpDialogLayout->FindPaneByName("T_Letter"));
                titleText->SetAlpha(0xFF);

                for (u32 i = 0; i < mTitleCount; i++) {
                    utility::layout::set_string(titleText, mTitleNames[i]);
                    nw4r::ut::Rect textRect = mpDialogLayout->getTextDrawRect("T_Letter");
                    f32 lineCount = -(textRect.bottom - textRect.top) / titlePane->GetSize().height;
                    mButtonState += static_cast<s32>(static_cast<f32>(ceil(lineCount)));
                }

                setScrollLimit();
                resetScrollArrows();
            }
        }

        void SDMemory::onDialogState9() {
            if (!mpDialogLayout->isPlaying(0)) {
                for (int i = 0; i < 4; i++) {
                    mPanelAnimationStates[i] = 0;
                    mpPaneManagers[2]->initPane(mpDialogLayout->GetRootPane()->FindPaneByName(sDialogPaneNames[i], true));
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

            bool previousDownEnd = !mControllerFlags[0];
            bool previousUpEnd = !mControllerFlags[1];
            updateScrollArrows(previousDownEnd, previousUpEnd, mScroller.isUpEnd(), mScroller.isDownEnd());

            if (mScroller.getBInst().isActive() ? false : true) {
                mpPaneManagers[2]->update();
            }
            mpPaneManagers[2]->calc();
        }

        void SDMemory::onDialogState11() {
            if (!mpDialogLayout->isPlaying(4) && !mpDialogLayout->isPlaying(7)) {
                switch (mProcessState) {
                case 2:
                case 3:
                    mDialogState = 12;
                    mpDialogLayout->getAnim(1)->initAnmFrame();
                    mpDialogLayout->getAnim(1)->play();

                    if (mControllerFlags[0] != 0) {
                        hideDownArrow();
                    }
                    if (mControllerFlags[1] != 0) {
                        hideUpArrow();
                    }
                    break;
                default:
                    mDialogState = 10;
                    break;
                }
            }
        }

        void SDMemory::onDialogState12() {
            if (mpDialogLayout->isPlaying(1)) {
                return;
            }

            switch (mProcessState) {
            case 2: {
                mDialogState = 4;
                layout::Animator* animation = mpTitleLayout->getAnim(0);
                animation->initAnmFrame();
                animation->play();
                snd::getSystem()->startSE("WIPL_SE_INFO_WINDOW");
                break;
            }
            case 3: {
                mTransferFlags[0] = 0;
                System::getHomeButtonMenu()->disable();

                if ((mTitleNameCount != 0 || mNandTitleCount != 0) &&
                    mpSDChannelSelect->getWorker()->is_sd_write_protected()) {
                    mErrorCode = 5;
                    mDialogState = 23;
                    mMessageId = 0xBF;
                    return;
                }

                if (iplSDChannelSelect_813DB530(mpSDChannelSelect, &mTitleListState.mpNames,
                                                &mTitleListState.mpSecondaryTitles)) {
                    mDialogState = 19;
                    mCurrentTitleName[0] = L'\0';
                    mCurrentTitle = 0;
                    const wchar_t* message = System::getMessage(0xB1);
                    const wchar_t* titleName = mTitleNames[mCurrentTitle];
                    swprintf(mCurrentTitleName, 0x107f, L"%ls\n%ls", titleName, message);
                    System::getDialog()->callBtnPrgNoShade(mCurrentTitleName);
                } else {
                    mDialogState = 23;
                    mErrorCode = 1;
                    mMessageId = 0xAE;
                }
                break;
            }
            default:
                break;
            }
        }

        extern "C" bool iplSDMemory_containsTitleId(const SDMemory* memory,
                                             ESTitleId titleId,
                                             const ESTitleId* titleIds, u32 titleCount) {
            for (u32 i = 0; i < titleCount; i++) {
                if (titleIds[i] == titleId) {
                    return true;
                }
            }

            return false;
        }

        void SDMemory::onDialogState13() {
            if (!mpSDChannelSelect->getWorker()->is_working()) {
                s32 result = mpSDChannelSelect->getWorker()->get_async_result();
                if (result == NandSDWorker::RESULT_OK) {
                    ESTitleId titleId = mTitleIds[mCurrentTitle];
                    if (iplSDMemory_containsTitleId(this, titleId,
                                             mNandTitleIds, mNandTitleCount)) {
                        mDialogState = 17;
                    } else {
                        mDialogState = 13;
                    }
                } else {
                    if (result > NandSDWorker::RESULT_OK) {
                        System::getDialog()->terminate();
                        mDialogState = 20;
                        mErrorCode = 2;
                        mMessageId = 0xB5;
                    } else {
                        System::getDialog()->terminate();
                        mDialogState = 20;
                        mErrorCode = 1;
                        mMessageId = 0xAE;
                    }
                }
            }
        }

        void SDMemory::onDialogState14() {
            if (System::getDialog()->getStateForSDMemory() != 2) {
                return;
            }

            mCurrentTitleName[0] = L'\0';
            const wchar_t* message = System::getMessage(0xB1);
            const wchar_t* titleName = mTitleNames[mCurrentTitle];
            swprintf(mCurrentTitleName, 0x107f, L"%ls\n%ls", titleName, message);
            System::getDialog()->setTitleForSDMemory(mCurrentTitleName);

            if (iplSDMemory_containsTitleId(this, mTitleIds[mCurrentTitle], mSDTitleIds, mTitleNameCount) ||
                iplSDMemory_containsTitleId(this, mTitleIds[mCurrentTitle], mNandTitleIds, mNandTitleCount)) {
                ESTitleId titleId = mTitleIds[mCurrentTitle];
                if (iplSDChannelSelect_813DB478(mpSDChannelSelect, titleId)) {
                    mDialogState = 14;
                } else {
                    System::getDialog()->terminate();
                    mDialogState = 20;
                    mErrorCode = 1;
                    mMessageId = 0xAE;
                }
            } else {
                mDialogState = 15;
                f32 progress = static_cast<f32>(mCurrentTitle + 1) * 100.0f / static_cast<f32>(mTitleCount);
                if (progress >= 100.0f) {
                    progress = 99.0f;
                }

                mTransferFrame = static_cast<s32>(progress);
                System::getDialog()->setProgBarLength(mTransferFrame);
            }
        }

        void SDMemory::onDialogState15() {
            f32 progress = static_cast<f32>(mCurrentTitle) * 100.0f / static_cast<f32>(mTitleCount);
            progress += static_cast<f32>(NandSDWorker::getCompletionPct() / mTitleCount);
            if (progress >= 100.0f) {
                progress = 99.0f;
            }

            mTransferFrame = static_cast<s32>(progress);
            System::getDialog()->setProgBarLength(mTransferFrame);

            if (!mpSDChannelSelect->getWorker()->is_working()) {
                s32 result = mpSDChannelSelect->getWorker()->get_async_result();
                if (result == NandSDWorker::RESULT_OK) {
                    mDialogState = 15;
                } else {
                    System::getDialog()->terminate();
                    mDialogState = 20;
                    if (result == NandSDWorker::RESULT_OUT_OF_SPACE) {
                        mErrorCode = 2;
                        mMessageId = 0xB5;
                    } else {
                        mErrorCode = 1;
                        mMessageId = 0xAE;
                    }
                }
            }
        }

        void SDMemory::onDialogState16() {
            if (mTitleCount > mCurrentTitle && System::isReceiveScheduleStopped()) {
                if (iplSDChannelSelect_813DB4D4(mpSDChannelSelect, mTitleIds[mCurrentTitle], 0)) {
                    mDialogState = 16;
                } else {
                    System::getDialog()->terminate();
                    mDialogState = 20;
                    mErrorCode = 1;
                    mMessageId = 0xAE;
                }
            }
        }

        void SDMemory::onDialogState17() {
            if (mpSDChannelSelect->getWorker()->is_working()) {
                return;
            }

            if (System::getDialog()->getProgBarFrame() < mTransferFrame) {
                return;
            }

            const ESTitleId* titleEntry = &mTitleIds[mCurrentTitle];
            System::getChannelManager()->unloadBanner(*titleEntry);

            if (mpSDChannelSelect->getWorker()->get_async_result() == NandSDWorker::RESULT_OK) {
                mCurrentTitle++;
                if (mTitleCount > mCurrentTitle) {
                    ESTitleId nextTitleId = mTitleIds[mCurrentTitle];
                    if (iplSDMemory_containsTitleId(this, nextTitleId,
                                             mNandTitleIds, mNandTitleCount)) {
                        mDialogState = 17;
                    } else {
                        mDialogState = 13;
                    }
                } else {
                    System::getDialog()->setProgBarLength(100);
                    mDialogState = 20;
                    mErrorCode = 0;
                }
            } else {
                System::getDialog()->terminate();
                mDialogState = 20;
                mErrorCode = 1;
                mMessageId = 0xAE;
            }
        }

        void SDMemory::onDialogState18() {
            if (System::getDialog()->getStateForSDMemory() == 2) {
                mCurrentTitleName[0] = L'\0';
                const wchar_t* message = System::getMessage(0xB1);
                const wchar_t* titleName = mTitleNames[mCurrentTitle];
                swprintf(mCurrentTitleName, 0x107f, L"%ls\n%ls", titleName, message);
                System::getDialog()->setTitleForSDMemory(mCurrentTitleName);

                const ESTitleId titleId = mTitleIds[mCurrentTitle];
                if (iplSDChannelSelect_813DB5EC(mpSDChannelSelect, titleId)) {
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
            if (!mpSDChannelSelect->getWorker()->is_working()) {
                if (mpSDChannelSelect->getWorker()->get_async_result() == NandSDWorker::RESULT_OK) {
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
                switch (mErrorCode) {
                case 0:
                    mTransferFlags[0] = 1;
                    mDialogState = 25;
                    return true;
                default:
                    mDialogState = 23;
                    break;
                }
            }

            return false;
        }

        void SDMemory::onDialogState21() {
            const wchar_t* message = System::getMessage(mMessageId);
            const wchar_t* blockCountMarker = wcsstr(message, L"****");
            wchar_t* format = new (System::getMem2App(), -32) wchar_t[0x400];
            wchar_t* dialogMessage = new (System::getMem2App(), -32) wchar_t[0x400];

            if (blockCountMarker != NULL && message != NULL) {
                format[0] = L'\0';
                memset(format + 1, 1, 0);
                wcsncat(format, message,
                        (reinterpret_cast<u32>(blockCountMarker) - reinterpret_cast<u32>(message)) >> 1);
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
                snd::getSystem()->startSE("WIPL_SE_INFO_WINDOW");
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

        void SDMemory::draw() {
            utility::Graphics::setDefaultOrtho(0);
            mpProgressLayout->draw();

            switch (mDialogState) {
            case 0:
            case 1:
            case 2:
            case 3:
                mpMainLayout->draw();
                break;
            case 4:
            case 5:
            case 6:
            case 7:
                mpTitleLayout->draw();
                break;
            case 9:
            case 10:
            case 11:
            case 12:
                drawTransferTitles();
                break;
            default:
                break;
            }
        }

        void SDMemory::drawTransferTitles() {
            const nw4r::math::VEC3& translation = mpDialogLayout->FindPaneByName("N_Memo")->GetTranslate();
            nw4r::math::VEC3 memoPosition;
            memoPosition.x = translation.x;
            memoPosition.y = translation.y;
            memoPosition.z = translation.z;
            f32 bodyY = memoPosition.y;
            mpDialogLayout->FindPaneByName("header_header");
            nw4r::lyt::Pane* bodyPane = mpDialogLayout->FindPaneByName("header_body");
            if (bodyY < 500.0f) {
                mpDialogLayout->draw("header_header");
            }

            u8 alpha = mpDialogLayout->FindPaneByName("N_Memo")->GetAlpha();
            nw4r::ut::LinkList<nw4r::lyt::Pane, offsetof(nw4r::lyt::detail::PaneBase, mLink)>::Iterator child =
                bodyPane->GetChildList().GetBeginIter();
            while (child != bodyPane->GetChildList().GetEndIter()) {
                child->SetAlpha(alpha);
                ++child;
            }

            f32 messageOffset = 0.0f;
            f32 bodyHeight = bodyPane->GetSize().height;
            if (mNandTitleCount != 0) {
                const wchar_t* messageForCount = System::getMessage(0xCB);
                s32 lineCount = 0;
                const wchar_t* newline = wcsstr(messageForCount, L"\n");
                while (newline != NULL) {
                    ++lineCount;
                    newline = wcsstr(newline + 1, L"\n");
                }

                const wchar_t* messageLine = System::getMessage(0xCB);
                nw4r::lyt::TextBox* messageText = static_cast<nw4r::lyt::TextBox*>(
                    mpDialogLayout->FindPaneByName("T_Header_body"));
                s32 totalLines = lineCount + 1;
                s32 lineIndex = 0;
                if (lineIndex < totalLines) {
                    do {
                    const wchar_t* lineEnd = wcsstr(messageLine, L"\n");
                    if (lineEnd == NULL) {
                        utility::layout::set_string(messageText, messageLine);
                    } else {
                        u32 lineLength = static_cast<u32>(lineEnd - messageLine);
                        wcsncpy(mCurrentTitleName, messageLine, lineLength);
                        mCurrentTitleName[lineLength] = L'\0';
                        utility::layout::set_string(messageText, mCurrentTitleName);
                        messageLine = lineEnd + 1;
                    }

                    if (bodyY < 500.0f) {
                        nw4r::math::VEC2 translation(0.0f, messageOffset);
                        bodyPane->SetTranslate(translation);
                        bodyPane->CalculateMtx(*mpDialogLayout->getDrawInfo());
                        mpDialogLayout->draw(bodyPane);
                    }

                    messageOffset -= bodyHeight;
                    ++lineIndex;
                    } while (lineIndex < totalLines);
                }
            }

            messageOffset += bodyHeight;
            f32 backgroundOffset = 40.0f + messageOffset;
            f32 titleOffset = 79.5f + messageOffset;

            nw4r::lyt::Pane* titleSizePane = mpDialogLayout->FindPaneByName("N_Body");
            f32 rowHeight = titleSizePane->GetSize().height;
            nw4r::lyt::PaneList::Iterator titleChild = titleSizePane->GetChildList().GetBeginIter();
            while (titleChild != titleSizePane->GetChildList().GetEndIter()) {
                titleChild->SetAlpha(alpha);
                ++titleChild;
            }

            nw4r::lyt::TextBox* titleText = static_cast<nw4r::lyt::TextBox*>(
                mpDialogLayout->FindPaneByName("T_Letter"));
            titleText->SetAlpha(alpha);

            u32 nandTitleIndex = 0;
            for (u32 titleIndex = 0; titleIndex < mTitleCount; ++titleIndex) {
                utility::layout::set_string(titleText, mTitleNames[titleIndex]);
                if (nandTitleIndex < mNandTitleCount && mTitleIds[titleIndex] == mNandTitleIds[nandTitleIndex]) {
                    GXColor gxActive;
                    writeFourFlagBytes(&gxActive.r, 0x34, 0xBE, 0xED, 0xFF);
                    ++nandTitleIndex;
                    nw4r::ut::Color active0 = *reinterpret_cast<const nw4r::ut::Color*>(&gxActive);
                    setTitleRowColors(titleText,
                                      nw4r::ut::Color(*reinterpret_cast<const nw4r::ut::Color*>(&gxActive)),
                                      nw4r::ut::Color(*reinterpret_cast<const nw4r::ut::Color*>(&gxActive)));
                } else {
                    GXColor gxInactive;
                    writeFourFlagBytes(&gxInactive.r, 0x64, 0x64, 0x64, 0xFF);
                    nw4r::ut::Color inactive0 = *reinterpret_cast<const nw4r::ut::Color*>(&gxInactive);
                    setTitleRowColors(titleText,
                                      nw4r::ut::Color(*reinterpret_cast<const nw4r::ut::Color*>(&gxInactive)),
                                      nw4r::ut::Color(*reinterpret_cast<const nw4r::ut::Color*>(&gxInactive)));
                }

                nw4r::ut::Rect textRect = mpDialogLayout->getTextDrawRect("T_Letter");
                f32 rowTop = textRect.bottom - textRect.top;
                s32 visibleRows = static_cast<s32>(static_cast<f32>(ceil(-rowTop / titleSizePane->GetSize().height)));
                for (s32 row = 0; row < visibleRows; ++row) {
                    f32 rowY = bodyY + backgroundOffset;
                    if (-500.0f < rowY && rowY < 500.0f) {
                        nw4r::math::VEC2 translation(0.0f, backgroundOffset);
                        titleSizePane->SetTranslate(translation);
                        titleSizePane->CalculateMtx(*mpDialogLayout->getDrawInfo());
                        mpDialogLayout->draw(titleSizePane);
                    }
                    backgroundOffset -= rowHeight;
                }
                if (-500.0f < bodyY + titleOffset && bodyY + titleOffset < 500.0f) {
                    nw4r::math::VEC2 translation(0.0f, titleOffset);
                    titleText->SetTranslate(translation);
                    titleText->CalculateMtx(*mpDialogLayout->getDrawInfo());
                    mpDialogLayout->draw(titleText);
                }
                titleOffset -= rowHeight * static_cast<f32>(visibleRows);
            }

            backgroundOffset += rowHeight;
            nw4r::lyt::Pane* footerPane = mpDialogLayout->FindPaneByName("N_Footer");
            nw4r::lyt::PaneList::Iterator footerChild = footerPane->GetChildList().GetBeginIter();
            while (footerChild != footerPane->GetChildList().GetEndIter()) {
                footerChild->SetAlpha(alpha);
                ++footerChild;
            }

            if (-500.0f < bodyY + backgroundOffset) {
                nw4r::math::VEC2 translation(0.0f, backgroundOffset);
                footerPane->SetTranslate(translation);
                footerPane->CalculateMtx(*mpDialogLayout->getDrawInfo());
                mpDialogLayout->draw(footerPane);
            }

            mpDialogLayout->draw("N_TopBtn_00");
            mpDialogLayout->draw("N_Back");
            mpDialogLayout->draw("N_Move");
        }

        void writeFourFlagBytes(u8* flags, u8 first, u8 second, u8 third, u8 fourth) {
            flags[0] = first;
            flags[1] = second;
            flags[2] = third;
            flags[3] = fourth;
        }

        void setTitleRowColors(nw4r::lyt::TextBox* textBox, const nw4r::ut::Color& first,
                               const nw4r::ut::Color& second) NO_INLINE {
            textBox->SetTextColors(first, second);
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

        void SDMemory::activateControlPane(const char* paneName, ::gui::Component* component) {
            layout::Animator* animator = NULL;
            s32 paneIndex = getControlPaneIndex(paneName);
            if (mPanelStates[paneIndex] == 0) {
                switch (paneIndex) {
                case 0:
                    animator = mpMainLayout->getAnim(5);
                    break;
                case 1:
                    animator = mpMainLayout->getAnim(8);
                    break;
                case 2:
                    animator = mpMainLayout->getAnim(2);
                    break;
                }

                if (animator != NULL) {
                    animator->initAnmFrame();
                    animator->setAnmType(ANIM_TYPE_FORWARD);
                    animator->initFrame();
                    animator->restart();
                    snd::getSystem()->startSE("WIPL_SE_BT_TARGETTING");
                    if (component != NULL) {
                        component->offPoint(0);
                    }
                    if (static_cast<s32>(mPanelStates[paneIndex]) < 4) {
                        ++mPanelStates[paneIndex];
                    }
                }
            }
        }

        void SDMemory::deactivateControlPane(const char* paneName) {
            layout::Animator* animator = NULL;
            s32 paneIndex = getControlPaneIndex(paneName);
            if (static_cast<s32>(mPanelStates[paneIndex]) == 1) {
                switch (paneIndex) {
                case 0:
                    animator = mpMainLayout->getAnim(6);
                    break;
                case 1:
                    animator = mpMainLayout->getAnim(9);
                    break;
                case 2:
                    animator = mpMainLayout->getAnim(3);
                    break;
                }

                if (animator != NULL) {
                    animator->initAnmFrame();
                    animator->setAnmType(ANIM_TYPE_FORWARD);
                    animator->initFrame();
                    animator->restart();
                    if (static_cast<s32>(mPanelStates[paneIndex]) > 0) {
                        --mPanelStates[paneIndex];
                    }
                }
            }
        }

        void SDMemory::cancelControlPane(const char* paneName) {
            layout::Animator* animator = NULL;
            s32 paneIndex = getControlPaneIndex(paneName);
            if (static_cast<s32>(mPanelStates[paneIndex]) > 0) {
                switch (paneIndex) {
                case 0:
                    animator = mpMainLayout->getAnim(7);
                    break;
                case 1:
                    animator = mpMainLayout->getAnim(10);
                    break;
                case 2:
                    animator = mpMainLayout->getAnim(4);
                    break;
                }

                if (animator != NULL) {
                    mProcessState = paneIndex;
                    mDialogState = 2;
                    animator->initAnmFrame();
                    animator->setAnmType(ANIM_TYPE_FORWARD);
                    animator->initFrame();
                    animator->restart();
                    if (paneIndex == 2) {
                        snd::getSystem()->startSE("WIPL_SE_CANCEL");
                    } else {
                        snd::getSystem()->startSE("WIPL_SE_DECIDE");
                    }
                }
            }
        }

        void SDMemory::ControlPaneEventHandler::onEvent(u32 compId, u32 event, void* data) {
            GuiPaneComponent* component = static_cast<GuiPaneComponent*>(mpManager->getComponent(compId));
            const char* paneName = component->getPane()->GetName();
            s32 eventType = static_cast<s32>(event);
            switch (eventType) {
            case ON_POINT:
                mpInstance->activateControlPane(paneName, static_cast<GuiComponent*>(data));
                break;
            case ON_LEFT:
                mpInstance->deactivateControlPane(paneName);
                break;
            case ON_TRIG:
                if (static_cast<ControllerInterface*>(data)->downTrg(controller::BTN_INTERACT)) {
                    mpInstance->cancelControlPane(paneName);
                }
                break;
            }
        }

        s32 SDMemory::getTitlePaneIndex(const char* paneName) {
            s32 paneIndex = -1;
            if (mDisplayMode == 4) {
                for (s32 i = 0; i < 5; i++) {
                    if (strcmp(paneName, sTitlePaneNames[i]) == 0) {
                        paneIndex = i;
                        break;
                    }
                }
            } else {
                for (s32 i = 0; i < 4; i++) {
                    if (strcmp(paneName, sAdditionalTitlePaneNames[i]) == 0) {
                        paneIndex = i + 1;
                        break;
                    }
                }
            }
            return paneIndex;
        }

        void SDMemory::activateTitlePane(const char* paneName, ::gui::Component* component) {
            layout::Animator* animator = NULL;
            s32 paneIndex = getTitlePaneIndex(paneName);
            u32* panelState = &mTitlePanelStates[paneIndex];
            if (*panelState == 0) {
                switch (paneIndex) {
                case 0:
                    animator = mpTitleLayout->getAnim(5);
                    break;
                case 1:
                    animator = mpTitleLayout->getAnim(8);
                    break;
                case 2:
                    animator = mpTitleLayout->getAnim(11);
                    break;
                case 3:
                    animator = mpTitleLayout->getAnim(14);
                    break;
                case 4:
                    animator = mpTitleLayout->getAnim(2);
                    break;
                }

                if (animator != NULL) {
                    animator->initAnmFrame();
                    animator->setAnmType(ANIM_TYPE_FORWARD);
                    animator->initFrame();
                    animator->restart();
                    snd::getSystem()->startSE("WIPL_SE_BT_TARGETTING");
                    if (component != NULL) {
                        component->offPoint(0);
                    }
                    if (static_cast<s32>(*panelState) < 4) {
                        ++*panelState;
                    }
                }
            }
        }

        void SDMemory::deactivateTitlePane(const char* paneName) {
            layout::Animator* animator = NULL;
            s32 paneIndex = getTitlePaneIndex(paneName);
            if (static_cast<s32>(mTitlePanelStates[paneIndex]) == 1) {
                switch (paneIndex) {
                case 0:
                    animator = mpTitleLayout->getAnim(6);
                    break;
                case 1:
                    animator = mpTitleLayout->getAnim(9);
                    break;
                case 2:
                    animator = mpTitleLayout->getAnim(12);
                    break;
                case 3:
                    animator = mpTitleLayout->getAnim(15);
                    break;
                case 4:
                    animator = mpTitleLayout->getAnim(3);
                    break;
                }

                if (animator != NULL) {
                    animator->initAnmFrame();
                    animator->setAnmType(ANIM_TYPE_FORWARD);
                    animator->initFrame();
                    animator->restart();
                    if (static_cast<s32>(mTitlePanelStates[paneIndex]) > 0) {
                        --mTitlePanelStates[paneIndex];
                    }
                }
            }
        }

        void SDMemory::selectTitlePane(const char* paneName) {
            layout::Animator* animator = NULL;
            s32 paneIndex = getTitlePaneIndex(paneName);
            if (static_cast<s32>(mTitlePanelStates[paneIndex]) > 0) {
                switch (paneIndex) {
                case 0:
                    animator = mpTitleLayout->getAnim(7);
                    iplSDChannelSelect_813DDB74(mpSDChannelSelect, &mNandTitleRange, &mSDTitleRange,
                                                mTitleIds, &mTitleNames[0][0], &mTitleCount, 0);
                    break;
                case 1:
                    animator = mpTitleLayout->getAnim(10);
                    iplSDChannelSelect_813DDB74(mpSDChannelSelect, &mNandTitleRange, &mSDTitleRange,
                                                mTitleIds, &mTitleNames[0][0], &mTitleCount, 1);
                    break;
                case 2:
                    animator = mpTitleLayout->getAnim(13);
                    iplSDChannelSelect_813DDB74(mpSDChannelSelect, &mNandTitleRange, &mSDTitleRange,
                                                mTitleIds, &mTitleNames[0][0], &mTitleCount, 2);
                    break;
                case 3:
                    animator = mpTitleLayout->getAnim(16);
                    iplSDChannelSelect_813DDB74(mpSDChannelSelect, &mNandTitleRange, &mSDTitleRange,
                                                mTitleIds, &mTitleNames[0][0], &mTitleCount, 3);
                    break;
                case 4:
                    animator = mpTitleLayout->getAnim(4);
                    break;
                }

                if (animator != NULL) {
                    mProcessState = paneIndex;
                    mDialogState = 6;
                    animator->initAnmFrame();
                    animator->setAnmType(ANIM_TYPE_FORWARD);
                    animator->initFrame();
                    animator->restart();

                    if (paneIndex >= 0 && paneIndex <= 3) {
                        memset(mNandTitleIds, 0, sizeof(mNandTitleIds));
                        memset(mSDTitleIds, 0, sizeof(mSDTitleIds));
                        mNandTitleCount = 0;
                        mTitleNameCount = 0;
                        mTitleListState.mpTitles = mTitleIds;
                        mTitleListState.mCount = mTitleCount;
                        mTitleListState.mpSecondaryTitles = mNandTitleIds;
                        mTitleListState.mSecondaryCount = 0;
                        mTitleListState.mpNames = mSDTitleIds;
                        mTitleListState.mNameCount = 0;
                        iplSDChannelSelect_813DB58C(mpSDChannelSelect,
                                                    &mTitleListState.mpTitles,
                                                    &mTitleListState.mpSecondaryTitles,
                                                    &mTitleListState.mpNames);
                    }

                    if (paneIndex == 4) {
                        snd::getSystem()->startSE("WIPL_SE_CANCEL");
                    } else {
                        snd::getSystem()->startSE("WIPL_SE_DECIDE");
                    }
                }
            }
        }

        void SDMemory::TitlePaneEventHandler::onEvent(u32 compId, u32 event, void* data) {
            GuiPaneComponent* component = static_cast<GuiPaneComponent*>(mpManager->getComponent(compId));
            const char* paneName = component->getPane()->GetName();
            s32 eventType = static_cast<s32>(event);
            switch (eventType) {
            case ON_POINT:
                mpInstance->activateTitlePane(paneName, static_cast<GuiComponent*>(data));
                break;
            case ON_LEFT:
                mpInstance->deactivateTitlePane(paneName);
                break;
            case ON_TRIG:
                if (static_cast<ControllerInterface*>(data)->downTrg(controller::BTN_INTERACT)) {
                    mpInstance->selectTitlePane(paneName);
                }
                break;
            }
        }

        s32 SDMemory::getDialogPaneIndex(const char* paneName) {
            s32 paneIndex = -1;
            for (s32 i = 0; i < 4; i++) {
                if (strcmp(paneName, sDialogPaneNames[i]) == 0) {
                    paneIndex = i;
                    break;
                }
            }
            return paneIndex;
        }

        void SDMemory::activateDialogPane(const char* paneName, ::gui::Component* component) {
            layout::Animator* animator = NULL;
            s32 paneIndex = getDialogPaneIndex(paneName);
            if (static_cast<s32>(mPanelAnimationStates[paneIndex]) == 0) {
                switch (paneIndex) {
                case 2:
                    animator = mpDialogLayout->getAnim(2);
                    break;
                case 3:
                    animator = mpDialogLayout->getAnim(5);
                    break;
                case 0:
                    animator = mpDialogLayout->getAnim(11);
                    break;
                case 1:
                    animator = mpDialogLayout->getAnim(8);
                    break;
                }

                if (animator != NULL) {
                    animator->initAnmFrame();
                    animator->setAnmType(ANIM_TYPE_FORWARD);
                    animator->initFrame();
                    animator->restart();
                    snd::getSystem()->startSE("WIPL_SE_BT_TARGETTING");
                    if (component != NULL) {
                        component->offPoint(0);
                    }
                    if (static_cast<s32>(mPanelAnimationStates[paneIndex]) < 4) {
                        ++mPanelAnimationStates[paneIndex];
                    }
                }
            }
        }

        void SDMemory::deactivateDialogPane(const char* paneName) {
            layout::Animator* animator = NULL;
            s32 paneIndex = getDialogPaneIndex(paneName);
            if (static_cast<s32>(mPanelAnimationStates[paneIndex]) == 1) {
                switch (paneIndex) {
                case 2:
                    animator = mpDialogLayout->getAnim(3);
                    break;
                case 3:
                    animator = mpDialogLayout->getAnim(6);
                    break;
                case 0:
                    animator = mpDialogLayout->getAnim(12);
                    break;
                case 1:
                    animator = mpDialogLayout->getAnim(9);
                    break;
                }

                if (animator != NULL) {
                    animator->initAnmFrame();
                    animator->setAnmType(ANIM_TYPE_FORWARD);
                    animator->initFrame();
                    animator->restart();
                    if (static_cast<s32>(mPanelAnimationStates[paneIndex]) > 0) {
                        --mPanelAnimationStates[paneIndex];
                    }
                }
            }
        }

        void SDMemory::selectDialogPane(const char* paneName) {
            layout::Animator* animator = NULL;
            s32 paneIndex = getDialogPaneIndex(paneName);
            if (static_cast<s32>(mPanelAnimationStates[paneIndex]) > 0) {
                switch (paneIndex) {
                case 2:
                    if (!mScroller.is_busy()) {
                        animator = mpDialogLayout->getAnim(4);
                    }
                    break;
                case 3:
                    if (!mScroller.is_busy()) {
                        animator = mpDialogLayout->getAnim(7);
                    }
                    break;
                case 0:
                    if (!mScroller.is_busy()) {
                        animator = mpDialogLayout->getAnim(13);
                        mScroller.setState(3);
                    }
                    break;
                case 1:
                    if (!mScroller.is_busy()) {
                        animator = mpDialogLayout->getAnim(10);
                        mScroller.setState(4);
                    }
                    break;
                }

                if (animator != NULL) {
                    mProcessState = paneIndex;
                    if (static_cast<u32>(paneIndex - 2) <= 1) {
                        mDialogState = 11;
                    }
                    animator->initAnmFrame();
                    animator->setAnmType(ANIM_TYPE_FORWARD);
                    animator->initFrame();
                    animator->restart();
                    if (paneIndex == 2) {
                        snd::getSystem()->startSE("WIPL_SE_CANCEL");
                    } else if (paneIndex == 3) {
                        snd::getSystem()->startSE("WIPL_SE_DECIDE");
                    }
                }
            }
        }

        void SDMemory::DialogPaneEventHandler::onEvent(u32 compId, u32 event, void* data) {
            GuiPaneComponent* component = static_cast<GuiPaneComponent*>(mpManager->getComponent(compId));
            const char* paneName = component->getPane()->GetName();
            s32 eventType = static_cast<s32>(event);
            switch (eventType) {
            case ON_POINT:
                mpInstance->activateDialogPane(paneName, static_cast<GuiComponent*>(data));
                break;
            case ON_LEFT:
                mpInstance->deactivateDialogPane(paneName);
                break;
            case ON_TRIG:
                if (static_cast<ControllerInterface*>(data)->downTrg(controller::BTN_INTERACT)) {
                    mpInstance->selectDialogPane(paneName);
                }
                break;
            }
        }

    }
}
