#include "scene/channelEdit/iplChanAppBox.h"

#include "scene/channelEdit/iplChannelEdit.h"

#pragma push
#pragma section const_type ".data"
extern "C" const char lbl_8164D108[] = "it_ObjChannelEdit_b_SaveDataIn.brlan";
extern "C" const char lbl_8164D12D[] = "it_ObjChannelEdit_b_SaveDataOut.brlan";
extern "C" const char lbl_8164D153[] = "it_ObjChannelEdit_b_SaveDataFoucusIn.brlan";
extern "C" const char lbl_8164D17E[] = "it_ObjChannelEdit_b_SaveDataFoucusOut.brlan";
extern "C" const char lbl_8164D1AA[] = "N_Data16x9";
extern "C" const char lbl_8164D1B5[] = "N_Data4x3";
extern "C" const char lbl_8164D1BF[] = "B_Data_01";
extern "C" const char lbl_8164D1C9[] = "B_Data_00";
extern "C" const char lbl_8164D1D3[] = "N_Atari16x9";
extern "C" const char lbl_8164D1DF[] = "N_Data_01";
extern "C" const char lbl_8164D1E9[] = "N_Atari4x3";
extern "C" const char lbl_8164D1F4[] = "N_Data_00";
extern "C" const char lbl_8164D1FE[] = "DataBaseCover_00";
extern "C" const char lbl_8164D20F[] = "DataBaseCover_01";
#pragma section const_type ".sdata"
extern "C" __declspec(section ".sdata") const char lbl_81696848[] = "G_Data";
extern "C" __declspec(section ".sdata") const wchar_t lbl_81696850[] = L"???";
#pragma section sconst_type ".sdata2"
extern "C" __declspec(section ".sdata2") const f32 lbl_81694900 = 0.5f;
extern "C" __declspec(section ".sdata2") const f32 lbl_81694904 = 2.0f;
extern "C" __declspec(section ".sdata2") const f64 lbl_81694908 = 4503599627370496.0;
#pragma pop

namespace ipl {
    namespace scene {
        ChanAppBox::ChanAppBox(EGG::Heap* heap, nand::LayoutFile* layoutFile, const char* layoutDir, const char* layoutFileName)
            : AnmController(heap), ::gui::EventHandler(), mState(STATE_HIDDEN), mpThumbnail(NULL), mpBalloon(NULL), mbInitBalloon(false) {
            mpLayout = new (heap) layout::Object(heap, layoutFile, layoutDir, layoutFileName);

            add_animation(lbl_8164D108, lbl_81696848);
            add_animation(lbl_8164D12D, lbl_81696848);
            add_animation(lbl_8164D153, lbl_81696848);
            add_animation(lbl_8164D17E, lbl_81696848);

            mpLayout->finishBinding();

            set_visible(lbl_8164D1AA, false);
            set_visible(lbl_8164D1B5, false);

            mpGui = new gui::PaneManager(this, mpLayout->getDrawInfo(), NULL, NULL, true);
            mpGui->createLayoutScene(*mpLayout->getNW4RLyt());
            mpGui->setAllComponentTriggerTarget(false);

            if (SCGetAspectRatio() == SC_ASPECT_RATIO_16x9) {
                mpGui->setTriggerTarget(mpLayout->FindPaneByName(lbl_8164D1BF), true);
                add_anmpane(lbl_8164D1BF, get_animation(ANIM_DATA_FOCUS_IN), get_animation(ANIM_DATA_FOCUS_OUT));
            } else {
                mpGui->setTriggerTarget(mpLayout->FindPaneByName(lbl_8164D1C9), true);
                add_anmpane(lbl_8164D1C9, get_animation(ANIM_DATA_FOCUS_IN), get_animation(ANIM_DATA_FOCUS_OUT));
            }
        }

        ChanAppBox::~ChanAppBox() {
            delete mpLayout;
            delete mpGui;
        }

        void ChanAppBox::calc() {
            AnmPane* anmPane;

            mpLayout->calc();
            mpGui->calc();

            anmPane = NULL;
            while (anmPane = (AnmPane*)nw4r::ut::List_GetNext(&mPaneList, anmPane), anmPane != NULL) {
                anmPane->calc();
            }

            if (mState != STATE_HIDDEN && mpThumbnail != NULL && mpThumbnail->getLytObj() != NULL) {
                nw4r::ut::Rect rect4x3;
                System::getProjectionRect4x3(&rect4x3);
                nw4r::ut::Rect rect16x9;
                System::getProjectionRect16x9(&rect16x9);

                f32 width4x3 = rect4x3.right - rect4x3.left;
                f32 width16x9 = rect16x9.right - rect16x9.left;
                f32 widescreenScale = width16x9 / width4x3;

                nw4r::math::VEC3 translate = get_translate(s_all_pane_name);
                if (SCGetAspectRatio() == SC_ASPECT_RATIO_16x9) {
                    translate.x *= widescreenScale;
                }

                mpThumbnail->getLytObj()->GetRootPane()->SetTranslate(translate);
                mpThumbnail->calc();

                nw4r::math::VEC2 scale = mpThumbnail->getLytObj()->GetRootPane()->GetScale();
                if (SCGetAspectRatio() == SC_ASPECT_RATIO_16x9) {
                    scale *= get_scale(lbl_8164D1D3).x;
                    scale *= get_scale(lbl_8164D1DF).x;
                } else {
                    scale *= get_scale(lbl_8164D1E9).x;
                    scale *= get_scale(lbl_8164D1F4).x;
                }
                mpThumbnail->getLytObj()->GetRootPane()->SetScale(scale);
            }

            switch (mState) {
                case STATE_HIDDEN:
                case STATE_IDLE: {
                    break;
                }
                case STATE_FADE_IN: {
                    on_fadein();
                    break;
                }
                case STATE_FADE_OUT: {
                    on_fadeout();
                    break;
                }
            }
        }

        const f32 offsets[2][2] = {
            {38.400000f, 28.800001f},
            {51.000004f, 28.800001f},
        };

        void ChanAppBox::draw() {
            if (mState == STATE_HIDDEN)
                return;
            mpLayout->draw();

            set_visible(lbl_8164D1FE, false);
            set_visible(lbl_8164D20F, false);

            ChannelEdit* sceneChannelEdit = get_channel_edit();
            if (sceneChannelEdit->getState() == ChannelEdit::STATE_ON_SCROLL_R || sceneChannelEdit->getState() == ChannelEdit::STATE_ON_SCROLL_L)
                return;
            if (mState == STATE_FADE_IN)
                return;
            if (mState == STATE_FADE_OUT)
                return;

            if (!get_visible(lbl_8164D1B5) && !get_visible(lbl_8164D1AA))
                return;

            if (mpThumbnail == NULL) {
                return;
            }
            if (mpThumbnail->getLytObj() == NULL) {
                return;
            }

            f32 fScisHalfW = offsets[SCGetAspectRatio()][0];
            f32 fScisHalfH = offsets[SCGetAspectRatio()][1];

            nw4r::ut::Rect projRect;
            System::getProjectionRect(&projRect);

            GXRenderModeObj* renderModeObj = System::getRenderModeObj();

            u32 fbW = renderModeObj->fbWidth;
            u32 efbH = renderModeObj->efbHeight;

            nw4r::math::VEC3 translate = mpThumbnail->getLytObj()->GetRootPane()->GetTranslate();

            f32 scisL = (translate.x - fScisHalfW) * (fbW / projRect.GetWidth()) + fbW / 2.f;
            f32 scisT = efbH / 2.f - translate.y - fScisHalfH;
            f32 scisW = fScisHalfW * 2.f * (fbW / projRect.GetWidth());
            f32 scisH = fScisHalfH * 2.f;
            GXSetScissor(scisL, scisT, scisW, scisH);

            mpThumbnail->getLytObj()->GetRootPane()->CalculateMtx(*mpLayout->getDrawInfo());
            mpThumbnail->draw();

            if (SCGetAspectRatio() == SC_ASPECT_RATIO_16x9) {
                set_visible(lbl_8164D20F, true);
                mpLayout->draw(lbl_8164D20F);
            } else {
                set_visible(lbl_8164D1FE, true);
                mpLayout->draw(lbl_8164D1FE);
            }

            GXSetScissor(0, 0, System::getRenderModeObj()->fbWidth, System::getRenderModeObj()->efbHeight);
        }

        void ChanAppBox::update() {
            mpGui->update();
        }

        void ChanAppBox::anmFadein() {
            if (SCGetAspectRatio() == SC_ASPECT_RATIO_16x9) {
                set_visible(lbl_8164D1AA, true);
                set_visible(lbl_8164D1B5, false);
            } else {
                set_visible(lbl_8164D1AA, false);
                set_visible(lbl_8164D1B5, true);
            }
            do_animation(ANIM_DATA_IN, ANIM_TYPE_FORWARD, true);
            mState = STATE_FADE_IN;
        }

        void ChanAppBox::anmFadeout() {
            if (mpBalloon != NULL) {
                mpBalloon->terminate();
            }
            do_animation(ANIM_DATA_OUT, ANIM_TYPE_FORWARD, true);
            mState = STATE_FADE_OUT;
        }

        void ChanAppBox::onEvent(u32 compId, u32 event, void* data) {
            gui::PaneComponent* paneComponent = (gui::PaneComponent*)mpManager->getComponent(compId);
            const char* paneName = paneComponent->getPane()->GetName();

            controller::Interface* con = (controller::Interface*)data;

            switch (event) {
                case ON_POINT: {
                    AnmPane* anmPane = get_anmpane(paneName);
                    if (anmPane == NULL)
                        break;

                    anmPane->incHoverCount();
                    get_channel_edit()->onPoint(anmPane);

                    if (mpBalloon == NULL || mpThumbnail == NULL || mbInitBalloon) {
                        break;
                    }

                    mbInitBalloon = true;
                    if (mpThumbnail->getIsCorrupt()) {
                        mpBalloon->init(lbl_81696850);
                    } else {
                        if (mpThumbnail->getMatchesTmpTitle()) {
                            mpBalloon->init(System::getMessage(MESG_CHAN_EDIT_SD_CARD_MENU));
                        } else {
                            mpBalloon->init(mpThumbnail->getTitle(0));
                        }
                    }
                    mpBalloon->fadein();
                    break;
                }
                case ON_MOVE: {
                    AnmPane* anmPane = get_anmpane(paneName);
                    if (anmPane == NULL) {
                        break;
                    }
                    if (mpBalloon == NULL || mpThumbnail == NULL) {
                        break;
                    }
                    if (mbInitBalloon) {
                        break;
                    }

                    mbInitBalloon = true;
                    if (mpThumbnail->getIsCorrupt()) {
                        mpBalloon->init(lbl_81696850);
                    } else {
                        if (mpThumbnail->getMatchesTmpTitle()) {
                            mpBalloon->init(System::getMessage(MESG_CHAN_EDIT_SD_CARD_MENU));
                        } else {
                            mpBalloon->init(mpThumbnail->getTitle(0));
                        }
                    }

                    mpBalloon->fadein();
                    break;
                }
                case ON_LEFT: {
                    AnmPane* anmPane = get_anmpane(paneName);
                    if (anmPane == NULL) {
                        break;
                    }

                    anmPane->decHoverCount();
                    get_channel_edit()->onLeft(anmPane);

                    mbInitBalloon = false;
                    if (mpBalloon == NULL || mpThumbnail == NULL) {
                        break;
                    }

                    mpBalloon->fadeout();
                    break;
                }
                case ON_TRIG: {
                    if (!con->downTrg(controller::BTN_INTERACT)) {
                        break;
                    }

                    AnmPane* anmPane = get_anmpane(paneName);
                    if (anmPane == NULL || mpThumbnail == NULL)
                        break;

                    get_channel_edit()->onTrig(this);
                    break;
                }
            }
        }

        void ChanAppBox::clearEvent() {
            if (SCGetAspectRatio() == SC_ASPECT_RATIO_16x9) {
                clear_anmpane(lbl_8164D1BF);
            } else {
                clear_anmpane(lbl_8164D1C9);
            }

            if (mpBalloon != NULL) {
                mpBalloon->terminate();
                mbInitBalloon = false;
            }
        }

        ChannelEdit* ChanAppBox::get_channel_edit() {
            return (ChannelEdit*)System::getScene(SCENE_CHANNEL_EDIT);
        }

        WAIT_FOR_ANIM_STATE(ChanAppBox::on_fadein, ANIM_DATA_IN, mState = STATE_IDLE);
        WAIT_FOR_ANIM_STATE(ChanAppBox::on_fadeout, ANIM_DATA_OUT, {
            set_visible(lbl_8164D1AA, false);
            set_visible(lbl_8164D1B5, false);
            mState = STATE_IDLE;
        });

        char ChanAppBox::s_all_pane_name[6] = "N_All";
    }  // namespace scene
}  // namespace ipl
