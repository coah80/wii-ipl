#include "iplSceneUI.h"

#include "scene/calendar/iplCalendar.h"
#include "scene/calendar/iplDate.h"

#include "iplSystem.h"

namespace ipl {
    namespace scene {
        extern "C" char scW_Cal[];
        extern "C" char scT_Cal[];
        extern "C" char scCal_Ac[];
        extern "C" char scInfo_a[];
        extern "C" char scB_Cal[];

        #pragma push
        #pragma section const_type ".data"
        extern "C" const char scN_CalDay_r[] = "N_CalDay_r";
        #pragma pop

        // clang-format off
        extern "C" const char* scDateAnimPaneNames[Date::ANIM_PANE_MAX] = {
            scN_CalDay_r,
            scW_Cal,
            scT_Cal,
            scCal_Ac,
            scInfo_a,
        };

        #pragma push
        #pragma section const_type ".data"
        extern "C" const char scMyIplTopFBrlan[] = "my_IplTop_f.brlan";
        extern "C" const char scN_CalDay_t[] = "N_CalDay_t";
        extern "C" const char scSEDateFocus[] = "WIPL_SE_DATE_FOCUS";
        #pragma pop

        #pragma push
        #pragma section const_type ".sdata"
        extern "C" char scW_Cal[] = "W_Cal";
        extern "C" char scT_Cal[] = "T_Cal";
        extern "C" char scCal_Ac[] = "Cal_Ac";
        extern "C" char scInfo_a[] = "Info_a";
        extern "C" char scB_Cal[] = "B_Cal";
        #pragma pop

        static const Date::AnmFrame scAnmFrame[] = {
            { Date::ANIM_PANE_BTN_HOVER,    0.0f,  6.0f  },
            { Date::ANIM_PANE_BTN_HOVER,    10.0f, 18.0f },
            { Date::ANIM_PANE_BODY,         50.0f, 80.0f },
            { Date::ANIM_PANE_BTN,          1.0f,  1.0f  },
            { Date::ANIM_PANE_BTN_TEXT,     1.0f,  1.0f  },
            { Date::ANIM_PANE_BTN_TEXT,     2.0f,  2.0f  },
            { Date::ANIM_PANE_BTN_TEXT,     0.0f,  0.0f  },
            { Date::ANIM_PANE_BTN,          0.0f,  0.0f  },
            { Date::ANIM_PANE_BTN_TEXT,     3.0f,  3.0f  },
            { Date::ANIM_PANE_BTN,          3.0f,  3.0f  },
            { Date::ANIM_PANE_MSG,          1.0f,  1.0f  },
            { Date::ANIM_PANE_MSG,          0.0f,  0.0f  },
        };
        // clang-format on

        utility::Date Date::mscMinDate(MIN_YEAR, MIN_MONTH, MIN_DAY);
        utility::Date Date::mscMaxDate(MAX_YEAR, MAX_MONTH, MAX_DAY);

        u8 padding[0x10];

        DECOMP_FORCE_ACTIVE(iplDate_cpp, padding);

        Date::Date(EGG::Heap* heap, nand::LayoutFile* file, const char* layoutFolder, const char* layoutFileName)
            : ::gui::EventHandler(), mbAppearMsg(0), unk_0x10(0), unk_0x14(0), mpLayout(NULL), mpCurrentPaneAnim(0), unk_0x3C(0) {
            // Layout
            mpLayout = new layout::Object(heap, file, layoutFolder, layoutFileName);

            // Bind animations
            for (int i = 0; i < ANIM_PANE_MAX; i++) {
                mpPaneAnims[i] = mpLayout->bind(scMyIplTopFBrlan, scDateAnimPaneNames[i], false);
            }
            mpLayout->finishBinding();

            // Setup GUI
            mpGui = new gui::PaneManager(this, mpLayout->getDrawInfo(), NULL, NULL);
            mpGui->setupScene(mpLayout);
            mpGui->setAllComponentTriggerTarget(false);
            mpGui->setTriggerTarget(mpLayout->FindPaneByName(scB_Cal), true);

            // Init date
            mpDate = new utility::Date();
        }

        void Date::calc() {
            int animId = IDANIM_NO_MSG;
            if (mbAppearMsg) {
                animId = IDANIM_APPEAR_MSG;
            }

            doAnim(animId);

            mpLayout->calc();
            mpGui->calc();

            if (mpCurrentPaneAnim != NULL && !mpCurrentPaneAnim->isPlaying()) {
                mpCurrentPaneAnim = NULL;
                onCmdRecv(3);
            }

            onCmdRecv(unk_0x14);
        }

        void Date::draw(bool unk) {
            if (unk) {
                if (unk_0x3C != 0) {
                    mpLayout->draw();
                }
            } else {
                if (unk_0x3C == 0) {
                    mpLayout->draw();
                }
            }
        }

        layout::PaneAnimator* Date::doAnim(int animId) {
            layout::PaneAnimator* anim = mpPaneAnims[scAnmFrame[animId].paneAnim];
            anim->setMinFrame(scAnmFrame[animId].start);
            anim->setMaxFrame(scAnmFrame[animId].end);
            anim->setAnmType(ANIM_TYPE_FORWARD);
            anim->play();
            return mpPaneAnims[scAnmFrame[animId].paneAnim];
        }

        void Date::setRotate(const nw4r::math::VEC3& vec) {
            mpLayout->FindPaneByName(scN_CalDay_t)->SetRotate(vec);
        }

        void Date::setTranslate(const nw4r::math::VEC3& vec) {
            mpLayout->FindPaneByName(scN_CalDay_t)->SetTranslate(vec);
        }

        void Date::setVisible(bool visible) {
            mpLayout->FindPaneByName(scDateAnimPaneNames[0])->SetVisible(visible);
        }

        bool Date::getVisible() {
            return mpLayout->FindPaneByName(scDateAnimPaneNames[0])->IsVisible();
        }

        void Date::setAttribute(int attr) {
            if ((attr & 2) == 2) {
                if ((attr & 8) == 8) {
                    doAnim(IDANIM_BLUE_TEXT);
                } else if ((attr & 4) == 4) {
                    doAnim(IDANIM_RED_TEXT);
                } else {
                    doAnim(IDANIM_RESET_GREY_TEXT);
                }
                if ((attr & 1) == 1) {
                    doAnim(IDANIM_LOOP);
                } else {
                    doAnim(IDANIM_RESET_GREY_BUTTON);
                }
            } else {
                doAnim(IDANIM_GREY_TEXT);
                doAnim(IDANIM_GREY_BUTTON);
            }
            if (mbAppearMsg) {
                doAnim(IDANIM_APPEAR_MSG);
            } else {
                doAnim(IDANIM_NO_MSG);
            }
            return;
        }

        void Date::setDate(const utility::Date& date) {
            *mpDate = date;
            set_textbox(mpDate->day);
        }

        void Date::update() {
            mpGui->update();
        }

        void Date::onEvent(u32 compId, u32 event, void* data) {
            if (isValidDate(*mpDate)) {
                gui::PaneComponent* component = static_cast<gui::PaneComponent*>(mpManager->getComponent(compId));
                const char* paneName = component->getPane()->GetName();
                controller::Interface* con = static_cast<controller::Interface*>(data);

                int unused = con != NULL ? con->getChannel() : getLatestEventCtrlNo();

                switch (event) {
                    // Pointer on button
                    case ::gui::EventHandler::ON_POINT: {
                        start_point_event(paneName, con);
                        break;
                    }
                    // Pointer not on button anymore
                    case ::gui::EventHandler::ON_LEFT: {
                        start_left_event(paneName);
                        break;
                    }
                    // Pointer click on button
                    case ::gui::EventHandler::ON_TRIG: {
                        if (getVisible() && con != NULL && con->downTrg(controller::BTN_INTERACT)) {
                            static_cast<Calendar*>(System::getScene(SCENE_CALENDAR))->onTrigDate(this);
                        }
                        break;
                    }
                }
            }
        }

        void Date::start_point_event(const char* paneName, controller::Interface* con) {
            if (strcmp(paneName, scB_Cal) == 0) {
                if (unk_0x3C == 0) {
                    static_cast<Calendar*>(System::getScene(SCENE_CALENDAR))->onPointDate(this);
                    onCmdRecv(1);

                    if (getVisible()) {
                        snd::getSystem()->startSE(scSEDateFocus);
                        if (con != NULL) {
                            con->rumble(1);
                        }
                    }
                }
                unk_0x3C++;
            }
        }

        void Date::start_left_event(const char* paneName) {
            if (strcmp(paneName, scB_Cal) == 0) {
                if (unk_0x3C == 1) {
                    onCmdRecv(2);
                }
                unk_0x3C--;
            }
        }

        static const wchar_t scNumber[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

        bool Date::isValidDate(const utility::Date& date) {
            return date.year >= mscMinDate.year && date.year <= mscMaxDate.year;
        }

        void Date::set_textbox(int day) {
            wchar_t numStr[3];

            int index = 0;

            wchar_t ch;
            if (day >= 10) {
                ch = scNumber[day / 10];
            } else {
                ch = scNumber[day % 10];
            }
            numStr[index++] = ch;

            if (day >= 10) {
                ch = scNumber[day % 10];
            } else {
                ch = 0;
            }
            numStr[index++] = ch;

            numStr[index++] = 0;

            nw4r::lyt::TextBox* pane = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpLayout->FindPaneByName(scDateAnimPaneNames[2]));
            pane->SetString(numStr);
        }

        void Date::onCmdRecv(int cmd) {
            if (cmd == 1 || cmd == 2) {
                unk_0x14 = cmd;
            }

            switch (unk_0x10) {
                case 0: {
                    if (cmd == 1) {
                        mpCurrentPaneAnim = doAnim(IDANIM_FOCUS_IN);
                        unk_0x10 = 1;
                    } else if (cmd == 2) {
                        mpCurrentPaneAnim = doAnim(IDANIM_FOCUS_OUT);
                        unk_0x10 = 2;
                    }
                    break;
                }
                case 1: {
                    if (cmd == 3) {
                        if (unk_0x14 == 1) {
                            unk_0x14 = 0;
                        }
                        unk_0x10 = 0;
                    }
                    break;
                }
                case 2: {
                    if (cmd == 3) {
                        if (unk_0x14 == 2) {
                            unk_0x14 = 0;
                        }
                        unk_0x10 = 0;
                    }
                    break;
                }
            }
        }

        void Date::initEvent() {
            mpGui->init();
            mpPaneAnims[ANIM_PANE_BTN_HOVER]->initAnmFrame(0.0f);
            unk_0x3C = 0;
            onCmdRecv(3);
        }

        #pragma push
        #pragma section sconst_type ".sdata2"
        extern "C" const f32 lbl_816948EC = 0.0f;
        extern "C" const f32 lbl_816948F0;
        #pragma pop
    }  // namespace scene
}  // namespace ipl
