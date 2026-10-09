#define IPL_CHANNEL_SELECT_CPP

#include <decomp/ide.h>
#include "iplSceneUI.h"

#include "scene/channelSelect/iplChannelSelect.h"

#include "iplSound.h"
#include "iplSystem.h"

#include "utility/iplCSFlags.h"

#include "scene/board/iplBoard.h"
#include "scene/button/iplButton.h"
#include "scene/channelTitle/iplChannelTitle.h"

#include <cstring>

namespace ipl {
    namespace math {
        static inline nw4r::math::VEC3 subHermitePoints(const VEC3& start, const VEC3& end) {
            nw4r::math::VEC3 difference;
            nw4r::math::VEC3Sub(&difference, &start, &end);
            return difference;
        }

        template <>
        VEC3 HermiteIntp<VEC3>::get() const {
            f32 frame = mFrame;
            f32 inverseDuration = 1.0f / mMaxFrame;
            VEC3 r(subHermitePoints(
                mStart * (1.0f + ((inverseDuration * (inverseDuration * (inverseDuration * (frame * (2.0f * frame * frame))))) -
                                  (inverseDuration * (inverseDuration * (3.0f * frame * frame))))),
                mEnd * ((inverseDuration * (inverseDuration * (inverseDuration * (frame * (2.0f * frame * frame))))) -
                        (inverseDuration * (inverseDuration * (3.0f * frame * frame))))));
            f32 frameSquared = frame * frame;
            f32 scaledCubic = inverseDuration * (inverseDuration * (frame * frameSquared));
            f32 tangentContribution = (mStartTangent * (frame + (scaledCubic - (inverseDuration * (2.0f * frame * frame))))) +
                          (mEndTangent * (scaledCubic - (inverseDuration * frameSquared)));
            r.x += tangentContribution;
            r.y += tangentContribution;
            r.z += tangentContribution;
            return r;
        }

        inline f32 HermiteIntp<f32>::get() const {
            f32 frame = mFrame;
            f32 inverseDuration = 1.0f / mMaxFrame;
            f32 r = (mStart * (1.0f + ((inverseDuration * (inverseDuration * (inverseDuration * (frame * (2.0f * frame * frame))))) -
                                       (inverseDuration * (inverseDuration * (3.0f * frame * frame)))))) -
                    (mEnd * ((inverseDuration * (inverseDuration * (inverseDuration * (frame * (2.0f * frame * frame))))) -
                             (inverseDuration * (inverseDuration * (3.0f * frame * frame)))));
            r += (mStartTangent * (frame + ((inverseDuration * (inverseDuration * (frame * (frame * frame)))) - (inverseDuration * (2.0f * frame * frame))))) +
                 (mEndTangent * ((inverseDuration * (inverseDuration * (frame * (frame * frame)))) - (inverseDuration * (frame * frame))));
            return r;
        }
    }  // namespace math
}  // namespace ipl

namespace ipl {
    namespace scene {
        extern "C" char smArg__Q23ipl6System;
        extern "C" char sSystem__Q23ipl3snd;
        extern "C" void* m_handle__Q23ipl11TVRCManager;
        extern "C" void calcChanZoomParam__Q33ipl5scene13ChannelSelectFv();
        extern "C" void setChanZoomOrtho__Q33ipl5scene13ChannelSelectFv();
        extern "C" void calcNormal__Q33ipl5scene13ChannelSelectFv();
        extern "C" void restartChannelModules__Q33ipl5scene13ChannelSelectFv();
        extern "C" void setEnable__Q23ipl11TVRCManagerFi();
        extern "C" void enableBtn__Q33ipl5scene6ButtonFv();
        extern "C" void calcNormalNormal__Q33ipl5scene13ChannelSelectFv();
        extern "C" void calcNormalWaitScrl__Q33ipl5scene13ChannelSelectFv();
        extern "C" void calcNormalScrl__Q33ipl5scene13ChannelSelectFv();
        extern "C" void tryToStartBoardScene__Q33ipl5scene13ChannelSelectFv();
        extern "C" void calcNormalWaitLoading__Q33ipl5scene13ChannelSelectFv();
        extern "C" void calcNormalFadeOutZoom__Q33ipl5scene13ChannelSelectFv();
        extern "C" void calcNormalSafeModeDialog__Q33ipl5scene13ChannelSelectFv();
        extern "C" void calcNormalGrab__Q33ipl5scene13ChannelSelectFv();
        extern "C" void calcNormalDrag__Q33ipl5scene13ChannelSelectFv();
        extern "C" void calcNormalReleaseWait__Q33ipl5scene13ChannelSelectFv();
        extern "C" void calcNormalRelease__Q33ipl5scene13ChannelSelectFv();
        extern "C" void calcNormalMoveChanIn__Q33ipl5scene13ChannelSelectFv();
        extern "C" void calcNormalMoveChanSave__Q33ipl5scene13ChannelSelectFv();
        extern "C" void calcNormalMoveChanOut__Q33ipl5scene13ChannelSelectFv();
        extern "C" void calcNormalDragScrl__Q33ipl5scene13ChannelSelectFv();
        extern "C" void getRndm__Q23ipl6SystemFv();
        extern "C" void get_u16__Q33ipl4math6RandomFv();
        extern "C" void initCursorAnim__Q33ipl5scene10ChannelObjFb();
        extern "C" void initBalloonAnim__Q33ipl5scene10ChannelObjFb();
        extern "C" void List_GetNext__Q24nw4r2utFPCQ34nw4r2ut4ListPCv();
        extern "C" void List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs();
        extern "C" void getChannelBasePane__Q33ipl5scene13ChannelSelectFi();
        extern "C" void initPane__Q33ipl3gui11PaneManagerFPQ34nw4r3lyt4Pane();
        extern "C" void getCurrentChannel__Q33ipl7channel7ManagerFPiPi();
        extern "C" void calcNormalRestart__Q33ipl5scene13ChannelSelectFv();
        extern "C" void _savegpr_28();
        extern "C" void _restgpr_28();
        extern "C" void isPlaying__Q33ipl6layout6ObjectCFi();
        extern "C" void getScene__Q33ipl5scene7ManagerFi();
        extern "C" void setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler();
        extern "C" void setEventHandler__Q33ipl5scene12SDMenuButtonFPQ23gui12EventHandler();
        extern "C" void initArrowAppearance__Q33ipl5scene6ButtonFib();
        extern "C" void startSE__Q33ipl3snd6SystemFPCc();
        extern "C" void startBGM__Q33ipl3snd6SystemFPCc();
        extern "C" void animation__Q33ipl5scene6ButtonFi();
        extern "C" void toggle_insert__Q33ipl5scene12SDMenuButtonFi();
        extern "C" void calc__Q33ipl6layout6ObjectFv();
        extern "C" void calcChannelModules__Q33ipl5scene13ChannelSelectFv();
        extern "C" void calcChannelThumbnails__Q33ipl5scene13ChannelSelectFv();
        extern "C" asm void calc__Q33ipl5scene5clockFv();
        extern "C" void playingSdAnim__Q33ipl5scene6ButtonFi();
        extern "C" void getDiskThumbnail__Q33ipl7channel7ManagerFb();
        extern "C" void getDiskInfo__Q33ipl3bs27ManagerFPPcPPc();
        extern "C" void createDiskLayout__Q33ipl5scene10ChannelObjFPv();
        extern "C" void setLangPane__Q33ipl5scene10ChannelObjFPCQ33ipl6layout6Object();
        extern "C" void resetDiskTitleName__Q33ipl5scene10ChannelObjFv();
        extern "C" void changeDisk__Q33ipl5scene10ChannelObjFv();
        extern "C" void destroyDiskLayout__Q33ipl5scene10ChannelObjFv();
        extern "C" void startDiskInEvent__Q33ipl5scene13ChannelSelectFv();
        extern "C" void startDiskOutEvent__Q33ipl5scene13ChannelSelectFv();
        extern "C" void initFrame__Q33ipl7utility15FrameControllerFv();
        extern "C" void _savegpr_27();
        extern "C" void _restgpr_27();
        extern "C" char mArg__Q33ipl7utility8Graphics;
        extern "C" void __as__Q34nw4r4math4VEC3FRCQ34nw4r4math4VEC3();
        extern "C" void __as__Q33ipl4math4VEC2FRCQ33ipl4math4VEC2();
        extern "C" void setOrtho__Q33ipl7utility8GraphicsFUl();
        extern "C" char mscBasePaneNames__Q33ipl5scene13ChannelSelect[];
        extern "C" char mscClockPaneNames__Q33ipl5scene13ChannelSelect[];
        extern "C" u32 mscMaskPaneName__Q33ipl5scene13ChannelSelect;
        extern "C" char scSE_WIPL_SE_CH_HOLD[];
        extern "C" char scPaneName_N_GCIcon[];
        extern "C" char scPaneName_N_DiscUpdateIcon[];
        extern "C" char scSE_WSD_SELECT[];
        extern "C" char scSE_WIPL_SE_CH_TARGETTING[];
        extern "C" char scSE_WIPL_SE_CH_SET[];
        extern "C" char scSE_WIPL_SE_CH_NOT_MOVE[];
        extern "C" char scSE_WIPL_SE_GRAY_BUTTON[];
        extern "C" char scSE_WIPL_SE_DECIDE[];
        extern "C" void draw__Q33ipl6layout6ObjectFPQ34nw4r3lyt4Pane();
        extern "C" void SetVisible__Q34nw4r3lyt4PaneFb();
        extern "C" void drawChannelThumbnails__Q33ipl5scene13ChannelSelectFv();
        extern "C" void setChanFrameVisibility__Q33ipl5scene13ChannelSelectFv();
        extern "C" void getRenderModeObj__Q23ipl6SystemFv();
        extern "C" void draw__Q33ipl6layout6ObjectFv();
        extern "C" void draw__Q33ipl5scene5clockFPQ34nw4r3lyt4Pane();
        extern "C" void drawChannelOthers__Q33ipl5scene13ChannelSelectFv();
        extern "C" void __ct__Q34nw4r2ut4RectFv();
        extern "C" void getProjectionRect__Q23ipl6SystemFPQ34nw4r2ut4Rect();
        extern "C" void drawPolygon__Q33ipl7utility8GraphicsFRCQ34nw4r2ut4Rect8_GXColor();
        extern "C" BOOL msInitFlag__Q33ipl5scene13ChannelSelect = FALSE;


        static Board* getBoard() {
            return (Board*)System::getSceneManager()->getScene(SCENE_BOARD);
        }

        static Button* getButton() {
            return (Button*)System::getSceneManager()->getScene(SCENE_BUTTON);
        }

        static ChannelTitle* getChannelTitle() {
            return (ChannelTitle*)System::getSceneManager()->getScene(SCENE_CHANNEL_TITLE);
        }

        // clang-format off
        const char* ChannelSelect::mscChanPaneNames[CHAN_SCROLL_MAX][MAX_CHANNEL_INDEX] = {
            {
                "",
                "",
                "",
                "N_Ch_a04",
                "",
                "",
                "",
                "N_Ch_a08",
                "",
                "",
                "",
                "N_Ch_a12"
            },
        {
                "N_Ch_b01",
                "N_Ch_b02",
                "N_Ch_b03",
                "N_Ch_b04",
                "N_Ch_b05",
                "N_Ch_b06",
                "N_Ch_b07",
                "N_Ch_b08",
                "N_Ch_b09",
                "N_Ch_b10",
                "N_Ch_b11",
                "N_Ch_b12"
            },
            {
                "N_Ch_c01",
                "N_Ch_c02",
                "N_Ch_c03",
                "N_Ch_c04",
                "N_Ch_c05",
                "N_Ch_c06",
                "N_Ch_c07",
                "N_Ch_c08",
                "N_Ch_c09",
                "N_Ch_c10",
                "N_Ch_c11",
                "N_Ch_c12"
            },
            {
                "N_Ch_d01",
                "N_Ch_d02",
                "N_Ch_d03",
                "N_Ch_d04",
                "N_Ch_d05",
                "N_Ch_d06",
                "N_Ch_d07",
                "N_Ch_d08",
                "N_Ch_d09",
                "N_Ch_d10",
                "N_Ch_d11",
                "N_Ch_d12"
            },
            {
                "N_Ch_e01",
                "",
                "",
                "",
                "N_Ch_e05",
                "",
                "",
                "",
                "N_Ch_e09",
                "",
                "",
                ""
            }
        };


        const char* ChannelSelect::mscBasePaneNames[CHAN_SCROLL_MAX] = {
            "BaseMask0",
            "BaseMask1",
            "BaseMask2",
            "BaseMask3",
            "BaseMask4"
        };


        const char* ChannelSelect::mscPicturePaneNames[CHAN_SCROLL_MAX] = {
            "Picture_00",
            "Picture_01",
            "Picture_02",
            "Picture_03",
            "Picture_04"
        };
        
        const char* ChannelSelect::mscEdgePaneNames[CHAN_SCROLL_MAX] = {
            "Edge0",
            "Edge1",
            "Edge2",
            "Edge3",
            "Edge4"
        };


        const char* ChannelSelect::mscClockPaneNames[3] = {
            "N_Clock0",
            "N_Clock1",
            "N_Clock2"
        };

        const char* ChannelSelect::mscMaskPaneName ="ChMask";

        static const f32 cfChanThumbOfss[2][2] = {
            {
                64.0f,
                48.0f,
            },
            {
                85.0f,
                48.0f,
            }
        };

        // clang-format on

#define FOREACH_CHANNEL_OBJ(chanObj) while ((chanObj = (ChannelObj*)nw4r::ut::List_GetNext(&mChanList, chanObj)) != NULL)

        ChannelSelect::ChannelSelect(EGG::Heap* heap, int startup)
            : scene::FaderSceneBase(heap),
              mpDiskChanObj(NULL),
              mpButtonEvent(new CsChanSelButtonEventHandler(this)),
              mpSDMenuEvent(new CsChanSelSDMenuEventHandler(this)),
              mState(STATE_NONE),
              mStartType(startup),
              mChanThumbOff_X(cfChanThumbOfss[SCGetAspectRatio()][0]),
              mChanThumbOff_Y(cfChanThumbOfss[SCGetAspectRatio()][1]),
              mDiskState(DISK_STATE_READ),
              mspDiskID(NULL),
              mspDiskMaker(NULL) {

            // mClock = clock();

            mPrevSDState = 0;

            mModuleState = 1;
            mbModuleSceneChange = false;
            mpCurrentRsoChanObj = NULL;
            mpPriorityModuleChanObj = NULL;

            mMaxPages = MAX_CHANNEL_PAGE;

            mCurrentPage = System::getSaveData()->getPrevPage();
            if (mCurrentPage == 0) {
                mbLeftArrowVisible = false;
            } else {
                mbLeftArrowVisible = true;
            }

            if (mCurrentPage == mMaxPages + -1) {
                mbRightArrowVisible = false;
            } else {
                mbRightArrowVisible = true;
            }

            setSceneParentFlags(SCN_PARENTFLAG_DRAW | SCN_PARENTFLAG_CALC);

            mOrthoTrans = math::VEC3(0.0f, 0.0f, 0.0f);
            mOrthoScale = math::VEC2(1.0f, 1.0f);

            nw4r::ut::Rect proj4x3;
            System::getProjectionRect4x3(&proj4x3);
            nw4r::ut::Rect proj16x9;
            System::getProjectionRect16x9(&proj16x9);

            f32 scale16x9 = proj16x9.GetWidth() / proj4x3.GetWidth();
            mScaleAdjust = (u8)SCGetAspectRatio() == SC_ASPECT_RATIO_16x9 ? scale16x9 : 1.0f;

            // ??? (although nothing really happens)
            memset(&mDragPos, 0, 0x34);

            mpChannelObjHeap = EGG::ExpHeap::create(0x3D28, heap, MEM_HEAP_OPT_DEBUG_FILL | MEM_HEAP_OPT_THREAD_SAFE);
            mpThumbnailHeap = EGG::UnitHeap::create(EGG::UnitHeap::calcHeapSize(0x212B8, 0x31, 32), 0x212B8, System::getMem2App(), 32, 2);

            nw4r::ut::List_Init(&mChanList, 0);
            makeChannelList(mCurrentPage, true);
            setupDiskChanObj();

            if (mStartType != START_FROM_CHJUMP) {
                TVRCManager::getHandle()->setEnable(TRUE);
            }
        }

        ChannelSelect::~ChannelSelect() {
        }

        void ChannelSelect::prepare() {
            mpLayoutFile = System::getNandManager()->readLayoutAsync(getSceneHeap(), "chanSel.ash");
            mpDiskThumbFile = System::getNandManager()->readLayoutAsync(getSceneHeap(), "diskThum.ash");

            ChannelObj* chanObj = NULL;
            FOREACH_CHANNEL_OBJ(chanObj) {
                chanObj->prepare();
            }
        }

        void ChannelSelect::create() {
            mpDiskHeap = EGG::ExpHeap::create(0x19100, getSceneHeap(), MEM_HEAP_OPT_DEBUG_FILL | MEM_HEAP_OPT_THREAD_SAFE);
            mpCursorHeap = EGG::ExpHeap::create(0x25900, getSceneHeap(), MEM_HEAP_OPT_DEBUG_FILL | MEM_HEAP_OPT_THREAD_SAFE);
            mpBalloonHeap = EGG::ExpHeap::create(0x32100, getSceneHeap(), MEM_HEAP_OPT_DEBUG_FILL | MEM_HEAP_OPT_THREAD_SAFE);

            createChannelModulesHeap();

            for (int page = 0; page < mMaxPages; page++) {
                for (int index = 0; index < MAX_CHANNEL_INDEX; index++) {
                    System::getChannelManager()->clearRsoExBuf(page, index);
                }
            }

            mpModuleThread = new (System::getMem2App(), 32) channel::RsoThread(mpModuleWorkHeap);

            System::getChannelManager()->setDiskChannelName();

            createBaseLayout();
            createDiskLayout();

            if (mCurrentPage < mMaxPages - 1) {
                makeChannelList(mCurrentPage + 1, false);
            }
            if (mCurrentPage > 0) {
                makeChannelList(mCurrentPage - 1, false);
            }

            createChannelThumbnails();
            calcDiskLayout();
            createChanMoveLayout();

            mClock.init(getSceneHeap(), mpLayoutFile);

            mState = STATE_CREATE;

            utility::CSFlags::UpdateFlagsFile();
        }

        void ChannelSelect::calcCommon() {
            if (mState == STATE_CREATE && !mpLayout->isPlaying(0)) {
                Button* button = getButton();
                if (button != NULL) {
                    button->setEventHandler(mpButtonEvent);
                    if (!System::isSafeMode()) {
                        button->get_sd_menu_btn()->setEventHandler(mpSDMenuEvent);
                    }

                    mState = STATE_FADING_IN;

                    if (mStartType == START_NORMAL) {
                        if (mCurrentPage > 0) {
                            button->initArrowAppearance(Button::ARROW_BTN_LEFT, true);
                        } else {
                            button->initArrowAppearance(Button::ARROW_BTN_LEFT, false);
                        }
                        if (mMaxPages > 1 && mCurrentPage < mMaxPages - 1) {
                            button->initArrowAppearance(Button::ARROW_BTN_RIGHT, true);
                        } else {
                            button->initArrowAppearance(Button::ARROW_BTN_RIGHT, false);
                        }

                        if (!msInitFlag) {
                            snd::getSystem()->startSE("WIPL_SE_WII_START");
                            msInitFlag = (BOOL)snd::getSystem()->startBGM("WIPL_BGM_MENU");
                        }
                    } else if (mStartType == START_FROM_BOARD) {
                        if (mCurrentPage > 0) {
                            button->animation(Button::IDANIM_ARROW_LEFT_APPEAR);
                        }
                        if (mMaxPages > 1 && mCurrentPage < mMaxPages - 1) {
                            button->animation(Button::IDANIM_ARROW_RIGHT_APPEAR);
                        }
                        if (!System::isSafeMode()) {
                            if (getBoard()->getSDState() == BoardSD::SD_STATE_INSERTED) {
                                button->get_sd_menu_btn()->toggle_insert(TRUE);
                            } else {
                                button->get_sd_menu_btn()->toggle_insert(FALSE);
                            }
                            button->animation(Button::IDANIM_SD_BUTTON_BTN_IN);
                        }
                    } else if (mStartType == START_FROM_CHJUMP) {
                        mbLeftArrowVisible = false;
                        mbRightArrowVisible = false;
                    }
                }
            }

            if (mState == STATE_FADING_IN && System::getFader()->getStatus() == EGG::Fader::PREPARE_OUT) {
                mState = STATE_NORMAL;
            }

            mpLayout->calc();
            mpGui->calc();

            updateDiskState();
            calcChannelModules();
            calcChannelThumbnails();

            mpMoveLytMask->calc();
            mpMoveLytObject->calc();
            mpMoveLytDrop->calc();
            mpMoveThumbnailLayout->calc();

            mClock.calc();

            s32 sdState = getBoard()->getSDState();

            if (sdState != mPrevSDState && !System::isSafeMode()) {
                if (sdState == 1) {
                    getButton()->get_sd_menu_btn()->toggle_insert(TRUE);
                } else {
                    getButton()->get_sd_menu_btn()->toggle_insert(FALSE);
                }

                switch (mState) {
                    case STATE_NORMAL_DONE_FADE_ZOOM:
                    case STATE_INACTIVE:
                    case STATE_NORMAL_RESTART: {
                        break;
                    }
                    case STATE_NORMAL_FADE_ZOOM:
                    case STATE_CHANNEL_TITLE:
                    case STATE_NORMAL_WAIT_LOADING:
                    case STATE_START_SETTING_SCENE:
                    case STATE_BOARD_SCENE:
                    case STATE_START_BOARD_SCENE: {
                        break;
                    }
                    case STATE_NONE: {
                        break;
                    }
                    case STATE_CREATE:
                    case STATE_FADING_IN: {
                        if (mStartType == START_FROM_BOARD) {
                            break;
                        }
                    }
                    case STATE_NORMAL:
                    default: {
                        if (sdState == 1 && mPrevSDState) {
                            if (!getButton()->playingSdAnim(40)) {
                                snd::getSystem()->startSE("WIPL_SE_SDCARD_IN");
                                getButton()->animation(Button::IDANIM_SD_BUTTON_INSERT);
                            }
                        } else if (mPrevSDState) {
                            snd::getSystem()->startSE("WIPL_SE_SDCARD_OUT");
                        }
                        break;
                    }
                }
            }

            mPrevSDState = sdState;
        }

        FaderSceneCommand ChannelSelect::calcFadein() {
            return mpLayout->isPlaying(0) ? FADER_SCN_CONTINUE : FADER_SCN_NEXT;
        }

        FaderSceneCommand ChannelSelect::calcNormal() {
            int state = mState;
            if (state == STATE_INACTIVE) {
                return FADER_SCN_CONTINUE;
            }

            switch (state) {
                case STATE_NORMAL:
                    calcNormalNormal();
                    break;
                case STATE_PREP_LEFT_PAGE_SCROLL:
                case STATE_PREP_RIGHT_PAGE_SCROLL:
                    calcNormalWaitScrl();
                    break;
                case STATE_LEFT_PAGE_SCROLL:
                case STATE_RIGHT_PAGE_SCROLL:
                    calcNormalScrl();
                    break;
                case STATE_START_BOARD_SCENE:
                    tryToStartBoardScene();
                    break;
                case STATE_NORMAL_WAIT_LOADING:
                    calcNormalWaitLoading();
                    break;
                case STATE_NORMAL_FADE_ZOOM:
                    calcNormalFadeOutZoom();
                    break;
                case STATE_NORMAL_DONE_FADE_ZOOM:
                    mState = STATE_INACTIVE;
                    break;
                case STATE_NORMAL_RESTART:
                    calcNormalRestart();
                    break;
                case STATE_NORMAL_SAFE_MODE_DIALOG:
                    calcNormalSafeModeDialog();
                    break;
                case STATE_NORMAL_GRAB:
                    calcNormalGrab();
                    break;
                case STATE_NORMAL_DRAG:
                    calcNormalDrag();
                    break;
                case STATE_NORMAL_RELEASE_WAIT:
                    calcNormalReleaseWait();
                    break;
                case STATE_NORMAL_RELEASE:
                    calcNormalRelease();
                    break;
                case STATE_NORMAL_MOVE_CHAN_IN:
                    calcNormalMoveChanIn();
                    break;
                case STATE_NORMAL_MOVE_CHAN_SAVE:
                    calcNormalMoveChanSave();
                    break;
                case STATE_NORMAL_MOVE_CHAN_OUT:
                    calcNormalMoveChanOut();
                    break;
                case STATE_DRAG_SCROLL_LEFT:
                case STATE_DRAG_SCROLL_RIGHT:
                    calcNormalDragScrl();
                    break;
                default:
                    break;
            }

            if (state == STATE_NORMAL && mState != STATE_NORMAL && mState != STATE_NORMAL_GRAB) {
                int page;
                int index;
                channel::Manager::getCurrentChannel(&page, &index);
                ChannelObj* chanObj = NULL;
                FOREACH_CHANNEL_OBJ(chanObj) {
                    int chanPage = chanObj->mChanPage;
                    int chanIndex = chanObj->mChanIndex;
                    if (chanPage == mCurrentPage) {
                        if (mState != STATE_NORMAL_WAIT_LOADING || chanIndex != index) {
                            chanObj->initCursorAnim(TRUE);
                        }
                        chanObj->initBalloonAnim(TRUE);
                    }
                }

                for (int i = 0; i < MAX_CHANNEL_INDEX; i++) {
                    mpGui->initPane(getChannelBasePane(i));
                }
            }

            if (mState == STATE_BOARD_SCENE || mState == STATE_START_SETTING_SCENE) {
                mbModuleSceneChange = true;
                mbWaitForModuleStop = true;
                return FADER_SCN_NEXT;
            }
            return FADER_SCN_CONTINUE;
        }

        void ChannelSelect::initCalcFadeout() {
        }

        FaderSceneCommand ChannelSelect::calcFadeout() {
            FaderSceneCommand result = FADER_SCN_CONTINUE;

            if (isPageCreatedAllDone(mCurrentPage)) {
                if (mState == STATE_BOARD_SCENE) {
                    result = !mpLayout->isPlaying(0) ? FADER_SCN_NEXT : FADER_SCN_CONTINUE;
                } else if (mState == STATE_START_SETTING_SCENE) {
                    result = System::getFader()->getStatus() == EGG::Fader::PREPARE_IN ? FADER_SCN_NEXT : FADER_SCN_CONTINUE;
                }
            } else {
                result = FADER_SCN_CONTINUE;
            }

            if (!unkBool()) {
                result = FADER_SCN_CONTINUE;
            }

            return result;
        }

        void ChannelSelect::draw() {
            if (mState != STATE_INACTIVE && System::getSceneManager()->onDrawLayer(scene::DRAW_LAYER_DEFAULT)) {
                if (mState == STATE_NORMAL_FADE_ZOOM || mState == STATE_NORMAL_DONE_FADE_ZOOM || mState == STATE_NORMAL_RESTART) {
                    utility::Graphics::setOrthoTransAndScale(mOrthoTrans, mOrthoScale);
                }
                utility::Graphics::setOrtho();

                for (int i = 0; i < CHAN_SCROLL_MAX; i++) {
                    nw4r::lyt::Pane* pane = mpLayout->FindPaneByName(mscBasePaneNames[i]);
                    pane->SetVisible(true);
                    mpLayout->draw(pane);
                    pane->SetVisible(false);
                }

                drawChannelThumbnails();
                setChanFrameVisibility();

                GXSetScissor(0, 0, System::getRenderModeObj()->fbWidth, System::getRenderModeObj()->efbHeight);

                nw4r::lyt::Pane* maskPane = mpLayout->FindPaneByName(mscMaskPaneName);
                maskPane->SetVisible(false);

                mpLayout->draw();
                mpDiskInOutLyt->draw();

                for (int i = 0; i < CLOCK_MAX; i++) {
                    nw4r::lyt::Pane* pane = mpLayout->FindPaneByName(mscClockPaneNames[i]);
                    mClock.draw(pane);
                }

                drawChannelOthers();

                maskPane->SetVisible(true);

                mpLayout->draw(maskPane);
                mpMoveLytObject->draw();
            } else if (mState == STATE_INACTIVE && System::getSceneManager()->onDrawLayer(scene::DRAW_LAYER_DEFAULT)) {
                utility::Graphics::setOrtho();

                GXColor color = {0, 0, 0, 255};
                nw4r::ut::Rect pos;
                System::getProjectionRect(&pos);

                utility::Graphics::drawPolygon(pos, color);
            }
        }

        void ChannelSelect::destroy() {
            System::getSaveData()->setLastPrevPage(mCurrentPage);

            ChannelObj* chanObj = NULL;
            FOREACH_CHANNEL_OBJ(chanObj) {
                nw4r::ut::List_Remove(&mChanList, chanObj);
                destroyChannelObj(chanObj);
                chanObj = NULL;
            }

            mpThumbnailHeap->destroy();

            for (int i = 0; i < 49; i++) {
                mpModuleHeaps[i]->destroy();
            }

            delete mpModuleThread;

            mpModuleWorkHeap->destroy();
            mpChannelObjHeap->destroy();
            mpDiskHeap->destroy();
            mpCursorHeap->destroy();
            mpBalloonHeap->destroy();
        }

        BOOL ChannelSelect::isFirstCall() const {
            return !mpCurrentRsoChanObj->mbModuleTerminated;
        }

        void ChannelSelect::getRsoExBufData(void* rsoExBuf) const {
            memcpy(rsoExBuf, System::getChannelManager()->getChannel(mpCurrentRsoChanObj->mChanPage, mpCurrentRsoChanObj->mChanIndex).rsoExBuf,
                   channel::RSO_EXTRA_BUFFER_LENGTH);
        }

        void ChannelSelect::setRsoExBufData(const void* rsoExBuf) {
            memcpy(System::getChannelManager()->getChannel(mpCurrentRsoChanObj->mChanPage, mpCurrentRsoChanObj->mChanIndex).rsoExBuf, rsoExBuf,
                   channel::RSO_EXTRA_BUFFER_LENGTH);
        }

        void ChannelSelect::getRsoTitleDataPath(char* dataPath) const {
            int page = mpCurrentRsoChanObj->mChanPage;
            int index = mpCurrentRsoChanObj->mChanIndex;
            sprintf(dataPath, "/title/%08x/%08x/data/", (u32)ES_TITLE_TYPE(System::getChannelManager()->getTitleID(page, index)),
                    (u32)ES_TITLE_CODE(System::getChannelManager()->getTitleID(page, index)));
        }

        layout::Animator* ChannelSelect::getRsoAnimator(int idx) const {
            return mpCurrentRsoChanObj->mpModuleAnims[idx];
        }

        BOOL ChannelSelect::isStartAnimFinished() const {
            BOOL result = TRUE;
            layout::Animator* anim = mpCurrentRsoChanObj->mpThumbAnim;
            if (anim != NULL && anim->isPlaying()) {
                result = FALSE;
            }
            return result;
        }

        void* ChannelSelect::allocFromRsoExHeap(u32 size, int align) {
            return mpCurrentRsoChanObj->mpModuleHeap->alloc(size, align);
        }

        void ChannelSelect::freeToRsoExHeap(void* buffer) {
            if (buffer) {
                mpCurrentRsoChanObj->mpModuleHeap->free(buffer);
            }
        }

        u32 ChannelSelect::getAllocatableSizeForRsoExHeap() const {
            return mpCurrentRsoChanObj->mpModuleHeap->getAllocatableSize();
        }

        void ChannelSelect::setDebugRsoInterval(u32 val) {
            /* stripped out code*/
        }

        void ChannelSelect::createChannelModulesHeap() {
            mpModuleWorkHeap = EGG::ExpHeap::create(System::getChannelArena(), 0x200000, 0);
            for (int i = 0; i < 49; i++) {
                mpModuleHeaps[i] = EGG::ExpHeap::create(0x10000, System::getMem2App(), MEM_HEAP_OPT_DEBUG_FILL | MEM_HEAP_OPT_THREAD_SAFE);
                mbModuleHeapInUse[i] = false;
            }
        }

        void ChannelSelect::createBaseLayout() {
            GXTexObj texObj[2];

            mpLayout = new layout::Object(getSceneHeap(), mpLayoutFile, "arc", "my_IplTop_a.brlyt");

            // Change pane textures for widescreen
            if (SCGetAspectRatio() == SC_ASPECT_RATIO_16x9) {
                mpLayout->FindPaneByName("ChangeTex16x9")->GetMaterial()->GetTexture(&texObj[1], GX_TEXMAP0);
                mpLayout->FindPaneByName("Picture_16")->GetMaterial()->GetTexture(&texObj[0], GX_TEXMAP0);

                for (int i = 0; i < CHAN_SCROLL_MAX; i++) {
                    mpLayout->FindPaneByName(mscPicturePaneNames[i])->GetMaterial()->SetTexture(GX_TEXMAP0, texObj[1]);
                    mpLayout->FindPaneByName(mscEdgePaneNames[i])->GetMaterial()->SetTexture(GX_TEXMAP0, texObj[0]);
                }
            }

            mpLayout->bind("my_IplTop_a.brlan");

            if (mStartType == START_FROM_BOARD || mStartType == START_FROM_CHJUMP) {
                mpLayout->setMinFrame(100.0f);
                mpLayout->setMaxFrame(120.0f);
                mpLayout->setAnmType(ANIM_TYPE_FORWARD);
                mpLayout->start();
            }

            mpLayout->finishBinding();

            ChannelSelectEventHandler* event = new ChannelSelectEventHandler(this);
            mpGui = new gui::PaneManager(event, mpLayout->getDrawInfo(), NULL, NULL);
            mpGui->createLayoutScene(*mpLayout->getNW4RLyt());
            mpGui->setAllComponentTriggerTarget(false);

            for (int i = 0; i < MAX_CHANNEL_INDEX; i++) {
                mpGui->getPaneComponentByPane(getChannelBasePane(i))->setTriggerTarget(true);
            }

            for (int i = 0; i < MAX_CHANNEL_PAGE; i++) {
                mpChanZoomParams[i] = new math::HermiteIntp<math::VEC3>();
            }
        }

        void ChannelSelect::createDiskLayout() {
            int state = System::getBS2Manager()->getIPLState();
            if (state == bs2::IPL_STATE_RVL_GAME || state == bs2::IPL_STATE_GC_GAME || state == bs2::IPL_STATE_DISK_UPDATE) {
                mbDiskInserted = true;
            } else {
                mbDiskInserted = false;
            }

            mpNoDiskLayout = new layout::Object(getSceneHeap(), mpDiskThumbFile, "arc", "my_DiskCh_b.brlyt");
            mpNoDiskAnim = mpNoDiskLayout->bind("my_DiskCh_b.brlan");
            mpNoDiskLayout->setAnmType(ANIM_TYPE_LOOP);
            mpNoDiskLayout->start();
            mpNoDiskLayout->getDrawInfo()->SetInfluencedAlpha(true);
            mpNoDiskLayout->GetRootPane()->SetInfluencedAlpha(true);
            mpNoDiskLayout->finishBinding();

            mpDiskFadeAnim = new math::HermiteIntp<f32>();
            mpDiskFadeAnim->init(255.0f, 0.0f, 28.0f, 0.0f, 0.0f, ANIM_TYPE_FORWARD, 1.0f);
            if (mbDiskInserted) {
                mpDiskFadeAnim->setCurrentFrame(mpDiskFadeAnim->getMaxFrame());
            }

            mpDiskLayout = new layout::Object(getSceneHeap(), mpDiskThumbFile, "arc", "my_GCIcon_a.brlyt");
            mpDiskAnim = mpDiskLayout->bind("my_GCIcon_a.brlan");
            mpDiskAnim->play();
            mpDiskLayout->finishBinding();

            mpDiskInOutLyt = new layout::Object(getSceneHeap(), mpDiskThumbFile, "arc", "my_DiskCh_In.brlyt");
            if (SCGetAspectRatio() == SC_ASPECT_RATIO_16x9) {
                GXTexObj tex;
                mpDiskInOutLyt->FindPaneByName("16x9")->GetMaterial()->GetTexture(&tex, GX_TEXMAP0);
                mpDiskInOutLyt->FindPaneByName("DiskIn")->GetMaterial()->SetTexture(GX_TEXMAP0, tex);
            }
            mpDiskInAnim = mpDiskInOutLyt->bind("my_DiskCh_In_DiskIn.brlan", !mbDiskInserted);
            mpDiskOutAnim = mpDiskInOutLyt->bind("my_DiskCh_In_DiskOut.brlan", mbDiskInserted);
            mpDiskInOutLyt->finishBinding();
        }

        extern "C" char scPaneName_N_GCIcon[] = "N_GCIcon";
        extern "C" char scPaneName_N_DiscUpdateIcon[] = "N_DiscUpdateIcon";


        void ChannelSelect::createChannelThumbnails() {
            ChannelObj* chanObj = NULL;
            FOREACH_CHANNEL_OBJ(chanObj) {
                createChannelThumbnail(chanObj);
            }
        }

        void ChannelSelect::createChannelThumbnail(ChannelObj* channelObj) {
            channelObj->prepare();
            channelObj->setHeaps(mpCursorHeap, mpBalloonHeap);
            channelObj->setBasePane(getChannelBasePane(channelObj->mChanPage, channelObj->mChanIndex, mCurrentPage));
            if (channelObj->isDiskChannel()) {
                channelObj->setDiskLayouts(mpDiskLayout, mpDiskAnim, mpDiskHeap);
            }
            channelObj->initExtModule(mpModuleWorkHeap, mpModuleThread);
            channelObj->create(mpLayoutFile);
        }

        void ChannelSelect::calcChannelModules() {
            if (mModuleState == 3) {
                return;
            }

            if (!System::isSafeMode()) {
                bool result = true;
                EGG::ExpHeap* expHeap = getFreeModuleExHeap();
                ChannelObj* chanObj = NULL;
                FOREACH_CHANNEL_OBJ(chanObj) {
                    if (mpPriorityModuleChanObj == NULL || chanObj == mpPriorityModuleChanObj) {
                        if (mModuleState == 2) {
                            result = false;
                        }

                        int state = chanObj->calcExtModule(expHeap, result, mbModuleSceneChange);
                        if (state == ChannelObj::EXT_MODULE_RESULT_DESTROY) {
                            updateModuleExHeap(chanObj->mpPrevModuleHeap, expHeap);
                            mpCurrentRsoChanObj = NULL;
                            mModuleState = 1;
                        } else if (state == ChannelObj::EXT_MODULE_RESULT_CALC && mModuleState == 1) {
                            mModuleState = 2;
                            mpCurrentRsoChanObj = chanObj;
                        }
                    }
                }
            }

            mpPriorityModuleChanObj = NULL;
            if (mbModuleSceneChange && mModuleState == 1) {
                mbModuleSceneChange = false;
                mModuleState = 3;
            }
        }

        void ChannelSelect::calcChannelThumbnails() {
            ChannelObj* chanObj = NULL;
            FOREACH_CHANNEL_OBJ(chanObj) {
                chanObj->calc();
            }

            if (mpMovedChanObj != NULL) {
                mpMovedChanObj->calc();
            }

            calcDiskLayout();
        }

        void ChannelSelect::calcDiskLayout() {
            int page = mpDiskChanObj->mChanPage;
            int index = mpDiskChanObj->mChanIndex;
            if (isChannelInCalc(page, index, mCurrentPage)) {
                mpNoDiskLayout->GetRootPane()->SetVisible(true);
                mpDiskInOutLyt->GetRootPane()->SetVisible(true);

                nw4r::math::VEC3 vec(0.0f, 0.0f, 0.0f);
                MTXMultVec(getChannelBasePane(page, index, mCurrentPage)->GetGlobalMtx(), vec, vec);

                mpNoDiskLayout->GetRootPane()->SetTranslate(vec);
                mpDiskInOutLyt->GetRootPane()->SetTranslate(vec);
            } else {
                mpNoDiskLayout->GetRootPane()->SetVisible(false);
                mpDiskInOutLyt->GetRootPane()->SetVisible(false);
            }

            mpDiskFadeAnim->calc();
            int frame = mpDiskFadeAnim->get();
            mpNoDiskLayout->GetRootPane()->SetAlpha(frame);

            mpNoDiskLayout->calc();
            mpDiskInOutLyt->calc();
        }

        void ChannelSelect::drawChannelThumbnails() {
            ChannelObj* chanObj = NULL;
            FOREACH_CHANNEL_OBJ(chanObj) {
                int chanPage = chanObj->mChanPage;
                int chanIndex = chanObj->mChanIndex;
                if (isChannelInView(chanPage, chanIndex)) {
                    setChannelScissor(chanObj);

                    chanObj->drawThumbnail();

                    if (chanObj->isDiskChannel()) {
                        mpNoDiskLayout->draw();
                    }

                    if (chanObj->isValid()) {
                        switch (mState) {
                            case STATE_DRAG_SCROLL_RIGHT:
                            case STATE_DRAG_SCROLL_LEFT:
                            case STATE_NORMAL_MOVE_CHAN_OUT:
                            case STATE_NORMAL_MOVE_CHAN_SAVE:
                            case STATE_NORMAL_MOVE_CHAN_IN:
                            case STATE_NORMAL_RELEASE:
                            case STATE_NORMAL_RELEASE_WAIT:
                            case STATE_NORMAL_DRAG:
                            case STATE_NORMAL_GRAB: {
                                if (chanPage != mMoveOldPage || chanIndex != mMoveOldIndex) {
                                    nw4r::math::VEC3 trans = chanObj->getTranslate();
                                    mpMoveLytMask->GetRootPane()->SetTranslate(trans);
                                    mpMoveLytMask->calcMtx();
                                    mpMoveLytMask->draw();
                                }
                            }
                        }
                    }

                    switch (mState) {
                        case STATE_NORMAL_GRAB:
                        case STATE_NORMAL_DRAG:
                        case STATE_NORMAL_MOVE_CHAN_IN:
                        case STATE_NORMAL_MOVE_CHAN_SAVE:
                        case STATE_DRAG_SCROLL_LEFT:
                        case STATE_DRAG_SCROLL_RIGHT: {
                            if (chanPage == mMoveOldPage && chanIndex == mMoveOldIndex) {
                                nw4r::math::VEC3 trans = chanObj->getTranslate();
                                mpMoveThumbnailLayout->GetRootPane()->SetTranslate(trans);
                                mpMoveThumbnailLayout->calcMtx();
                                mpMoveThumbnailLayout->draw();
                            }
                        }
                    }

                    switch (mState) {
                        case STATE_NORMAL_MOVE_CHAN_OUT:
                        case STATE_NORMAL_MOVE_CHAN_SAVE:
                        case STATE_NORMAL_MOVE_CHAN_IN: {
                            if (chanPage == mMoveNewPage && chanIndex == mMoveNewIndex) {
                                mpMoveLytDrop->draw();
                            }
                        }
                    }
                }
            }
        }

        void ChannelSelect::drawChannelOthers() {
            ChannelObj* chanObj = NULL;
            FOREACH_CHANNEL_OBJ(chanObj) {
                if (isChannelInView(chanObj->mChanPage, chanObj->mChanIndex)) {
                    chanObj->drawCursor();
                }
            }
            chanObj = NULL;
            FOREACH_CHANNEL_OBJ(chanObj) {
                if (isChannelInView(chanObj->mChanPage, chanObj->mChanIndex)) {
                    chanObj->drawBalloon();
                }
            }
        }

        void ChannelSelect::calcNormalNormal() {
            if (mStartType == START_FROM_CHJUMP) {
                startChanTtlScene(System::getChannelManager()->getChJumpChanPage(), System::getChannelManager()->getChJumpChanIndex());
                return;
            }

            Button* button = getButton();
            if (button != NULL && button->isActive()) {
                button->update();
            }

            if (mState == STATE_NORMAL) {
                controller::Interface* con = System::getMasterController();
                if (con->down(controller::BTN_NEXT_LEFT)) {
                    if (mCurrentPage > 0) {
                        preparePageScrolling(STATE_PREP_LEFT_PAGE_SCROLL);
                        return;
                    }
                } else if (con->down(controller::BTN_NEXT_RIGHT)) {
                    if (mCurrentPage < (mMaxPages - 1)) {
                        preparePageScrolling(STATE_PREP_RIGHT_PAGE_SCROLL);
                        return;
                    }
                }
            }

            mpGui->update();
        }

        void ChannelSelect::calcNormalWaitScrl() {
            if (mState == STATE_PREP_LEFT_PAGE_SCROLL) {
                if (isPageCreatedAllDone(mCurrentPage)) {
                    if (unkBool()) {
                        startPageScroll(STATE_LEFT_PAGE_SCROLL);
                    }
                }
            } else {
                if (isPageCreatedAllDone(mCurrentPage)) {
                    if (unkBool()) {
                        startPageScroll(STATE_RIGHT_PAGE_SCROLL);
                    }
                }
            }
        }

        void ChannelSelect::calcNormalScrl() {
            if (mpLayout->isPlaying(0)) {
                return;
            }

            Button* button = getButton();

            if (mState == STATE_LEFT_PAGE_SCROLL) {
                if (--mCurrentPage == 0) {
                    button->animation(Button::IDANIM_ARROW_LEFT_DISAPPEAR);
                    mbLeftArrowVisible = false;
                } else if (!mbRightArrowVisible) {
                    button->animation(Button::IDANIM_ARROW_RIGHT_APPEAR);
                    mbRightArrowVisible = true;
                }
            } else {
                if (++mCurrentPage == mMaxPages - 1) {
                    button->animation(Button::IDANIM_ARROW_RIGHT_DISAPPEAR);
                    mbRightArrowVisible = false;
                } else if (!mbLeftArrowVisible) {
                    button->animation(Button::IDANIM_ARROW_LEFT_APPEAR);
                    mbLeftArrowVisible = true;
                }
            }

            mpLayout->finishBinding();

            refreshChannelList(mCurrentPage);
            restartChannelModules();
            mState = STATE_NORMAL;
        }

        void ChannelSelect::calcNormalWaitLoading() {
            if (isPageCreatedAllDone(mCurrentPage)) {
                if (unkBool()) {
                    int page, index;
                    channel::Manager::getCurrentChannel(&page, &index);
                    reserveSceneChangeDerived(page, index);
                    mState = STATE_CHANNEL_TITLE;
                }
            }
        }

        void ChannelSelect::calcNormalFadeOutZoom() {
            // unused
            int page, index;
            channel::Manager::getCurrentChannel(&page, &index);

            calcChanZoomParam();
            setChanZoomOrtho();

            if (!mpChanZoomParams[0]->isPlaying()) {
                mState = STATE_NORMAL_DONE_FADE_ZOOM;
            }
        }

        void ChannelSelect::calcNormalRestart() {
            if (!mpChanZoomParams[0]->isPlaying()) {
                if (System::getSceneManager()->getScene(SCENE_CHANNEL_TITLE) == NULL) {
                    Button* button = getButton();
                    button->enableBtn();

                    if (mCurrentPage > 0) {
                        button->animation(Button::IDANIM_ARROW_LEFT_APPEAR);
                        mbLeftArrowVisible = TRUE;
                    } else {
                        mbLeftArrowVisible = FALSE;
                    }

                    if (mMaxPages > 1 && mCurrentPage < mMaxPages - 1) {
                        button->animation(Button::IDANIM_ARROW_RIGHT_APPEAR);
                        mbRightArrowVisible = TRUE;
                    } else {
                        mbRightArrowVisible = FALSE;
                    }

                    button->setEventHandler(mpButtonEvent);
                    if (!System::isSafeMode()) {
                        button->get_sd_menu_btn()->setEventHandler(mpSDMenuEvent);
                    }

                    restartChannelModules();
                    TVRCManager::getHandle()->setEnable(TRUE);
                    snd::getSystem()->startBGM("WIPL_BGM_MENU");
                    mState = STATE_NORMAL;
                    return;
                }
            }

            calcChanZoomParam();
            setChanZoomOrtho();
        }

        void ChannelSelect::calcNormalSafeModeDialog() {
            if (System::getDialog()->getLastResult() == DialogWindow::RESULT_WAIT) {
                mState = STATE_NORMAL;
            }
        }

        void ChannelSelect::refreshChannelList(int page) {
            makeChannelList(page, false);

            if (page < mMaxPages - 1) {
                makeChannelList(page + 1, false);
            }
            if (page > 0) {
                makeChannelList(page - 1, false);
            }

            sortChannelList(page);
            createChannelThumbnails();
        }

        void ChannelSelect::makeChannelList(int page, bool force) {
            for (int i = 0; i < MAX_CHANNEL_INDEX; i++) {
                if (force || searchList(page, i) == NULL) {
                    appendToChannelList(page, i);
                }
            }

            if (page < mMaxPages - 1) {
                for (int i = 0; i < MAX_CHANNEL_INDEX; i += MAX_CHANNEL_ROW) {
                    if (force || searchList(page + 1, i) == NULL) {
                        appendToChannelList(page + 1, i);
                    }
                }
            }

            if (page > 0) {
                for (int i = MAX_CHANNEL_COLUMN; i < MAX_CHANNEL_INDEX; i += MAX_CHANNEL_ROW) {
                    if (force || searchList(page - 1, i) == NULL) {
                        appendToChannelList(page - 1, i);
                    }
                }
            }
        }

        void ChannelSelect::appendToChannelList(int page, int index) {
            bool isDisk = false;
            EGG::FrmHeap* frmHeap;
            int diskPage, diskIndex;
            System::getChannelManager()->getDiskChannelLocation(&diskPage, &diskIndex);

            if (diskPage == page && diskIndex == index) {
                isDisk = true;
                frmHeap = NULL;
            } else {
                frmHeap = EGG::FrmHeap::create(0x212B8, mpThumbnailHeap, 2);
            }

            ChannelObj* chanObj = new (mpChannelObjHeap, 4) ChannelObj(frmHeap, page, index);
            nw4r::ut::List_Append(&mChanList, chanObj);

            if (isDisk) {
                mpDiskChanObj = chanObj;
            }
        }

        void ChannelSelect::destroyChannelObj(ChannelObj* channelObj) {
            EGG::Heap* heap = channelObj->mpMainHeap;
            delete channelObj;
            if (heap != NULL) {
                heap->destroy();
            }
        }

        void ChannelSelect::sortChannelList(int page) {
            sortChannelListByPage(page, 0);

            if (page < mMaxPages - 1) {
                sortChannelListByPage(page + 1, -1);
            }
            if (page > 0) {
                sortChannelListByPage(page - 1, 1);
            }

            if (page < mMaxPages - 2 && isPageCreated(page + 2)) {
                sortChannelListByPage(page + 2, -1);
            }
            if (page > 1 && isPageCreated(page - 2)) {
                sortChannelListByPage(page - 2, 1);
            }

            if (page < mMaxPages - 3 && isPageCreated(page + 3)) {
                sortChannelListByPage(page + 3, -1);
            }
            if (page > 2 && isPageCreated(page - 3)) {
                sortChannelListByPage(page - 3, 1);
            }
        }

        void ChannelSelect::sortChannelListByPage(int page, int edgeDirection) {
            for (int i = 0; i < MAX_CHANNEL_INDEX; i++) {
                if (edgeDirection == -1) {
                    if (!(i & 3)) {
                        continue;
                    }
                } else if (edgeDirection == 1 && (i & 3) == 3) {
                    continue;
                }

                ChannelObj* chanObj = searchList(page, i);
                nw4r::ut::List_Remove(&mChanList, chanObj);
                nw4r::ut::List_Append(&mChanList, chanObj);
            }

            if (edgeDirection != 1 && page + 1 < mMaxPages) {
                for (int i = 0; i < MAX_CHANNEL_INDEX; i += MAX_CHANNEL_ROW) {
                    ChannelObj* chanObj = searchList(page + 1, i);
                    nw4r::ut::List_Remove(&mChanList, chanObj);
                    nw4r::ut::List_Append(&mChanList, chanObj);
                }
            }

            if (edgeDirection != -1 && page - 1 >= 0) {
                for (int i = MAX_CHANNEL_COLUMN; i < MAX_CHANNEL_INDEX; i += MAX_CHANNEL_ROW) {
                    ChannelObj* chanObj = searchList(page - 1, i);
                    nw4r::ut::List_Remove(&mChanList, chanObj);
                    nw4r::ut::List_Append(&mChanList, chanObj);
                }
            }
        }

        ChannelObj* ChannelSelect::searchList(int page, int index) const {
            ChannelObj* chanObj = NULL;
            FOREACH_CHANNEL_OBJ(chanObj) {
                int chanPage = chanObj->mChanPage;
                int chanIndex = chanObj->mChanIndex;
                if (chanPage == page && chanIndex == index) {
                    return chanObj;
                }
            }
            return NULL;
        }

        void ChannelSelect::setupDiskChanObj() {
            if (mpDiskChanObj == NULL) {
                int page, index;
                System::getChannelManager()->getDiskChannelLocation(&page, &index);
                appendToChannelList(page, index);
            }
        }

        void ChannelSelect::updateDiskState() {
            int diskState = System::getBS2Manager()->getIPLState();
            switch (mDiskState) {
                case DISK_STATE_READ:
                    if (!mpDiskOutAnim->isPlaying()) {
                        mpDiskLayout->FindPaneByName(scPaneName_N_GCIcon)->SetVisible(true);
                        mpDiskLayout->FindPaneByName(scPaneName_N_DiscUpdateIcon)->SetVisible(false);
                        if (diskState == bs2::IPL_STATE_RVL_GAME) {
                            void* thumbnail = System::getChannelManager()->getDiskThumbnail(mState != STATE_INACTIVE);
                            if (mState == STATE_INACTIVE) {
                                System::getBS2Manager()->getDiskInfo(&mspDiskID, &mspDiskMaker);
                            }
                            if (thumbnail != NULL) {
                                mpDiskChanObj->createDiskLayout(thumbnail);
                            }
                            if (!mbDiskInserted) {
                                startDiskInEvent();
                            }
                            mbDiskInserted = false;
                            mDiskState = DISK_STATE_PLAY_THUMB;
                        } else if (diskState == bs2::IPL_STATE_DISK_UPDATE) {
                            System::getChannelManager()->setDiskChannelReady(false);
                            mpDiskLayout->FindPaneByName(scPaneName_N_GCIcon)->SetVisible(false);
                            mpDiskLayout->FindPaneByName(scPaneName_N_DiscUpdateIcon)->SetVisible(true);
                            ChannelObj::setLangPane(mpDiskLayout);
                            if (mpDiskAnim != NULL) {
                                mpDiskAnim->setAnmType(ANIM_TYPE_LOOP);
                                mpDiskAnim->play();
                            }
                            if (!mbDiskInserted) {
                                startDiskInEvent();
                            }
                            mbDiskInserted = false;
                            mDiskState = DISK_STATE_PLAY_THUMB;
                        } else if (diskState == bs2::IPL_STATE_GC_GAME) {
                            if (!mbDiskInserted) {
                                startDiskInEvent();
                            }
                            mbDiskInserted = false;
                            mDiskState = DISK_STATE_GC_GAME_WAIT;
                        }
                    }
                    break;
                case DISK_STATE_PLAY_THUMB:
                    if (!mpDiskFadeAnim->isPlaying()) {
                        mpDiskChanObj->resetDiskTitleName();
                        if (diskState == bs2::IPL_STATE_RVL_GAME) {
                            if (mpDiskChanObj->mpThumbAnim != NULL) {
                                mpDiskChanObj->mpThumbAnim->setAnmType(ANIM_TYPE_LOOP);
                                layout::Animator* thumbnailAnim = mpDiskChanObj->mpThumbAnim;
                                thumbnailAnim->play();
                            }
                            mDiskState = DISK_STATE_RVL_GAME;
                        } else {
                            mDiskState = DISK_STATE_DISK_UPDATE;
                        }
                    }
                    break;
                case DISK_STATE_RVL_GAME:
                    if ((diskState != bs2::IPL_STATE_RVL_GAME || System::getChannelManager()->isDiskChannelReady()) && !mpDiskInAnim->isPlaying()) {
                        startDiskOutEvent();
                        mpDiskChanObj->changeDisk();
                        mDiskState = DISK_STATE_DESTROY;
                    }
                    break;
                case DISK_STATE_DISK_UPDATE:
                    if ((diskState != bs2::IPL_STATE_DISK_UPDATE || System::getChannelManager()->isDiskChannelReady()) && !mpDiskInAnim->isPlaying()) {
                        startDiskOutEvent();
                        mpDiskChanObj->changeDisk();
                        mDiskState = DISK_STATE_DESTROY;
                    }
                    break;
                case DISK_STATE_GC_GAME_WAIT:
                    if (!mpDiskFadeAnim->isPlaying()) {
                        mDiskState = DISK_STATE_GC_GAME;
                    }
                    break;
                case DISK_STATE_GC_GAME:
                    if (diskState != bs2::IPL_STATE_GC_GAME && !mpDiskInAnim->isPlaying()) {
                        startDiskOutEvent();
                        mpDiskChanObj->changeDisk();
                        mDiskState = DISK_STATE_DESTROY;
                    }
                    break;
                case DISK_STATE_DESTROY:
                    if (!mpDiskFadeAnim->isPlaying()) {
                        mpDiskChanObj->destroyDiskLayout();
                        mpDiskChanObj->resetDiskTitleName();
                        mDiskState = DISK_STATE_READ;
                    }
                    break;
            }
        }


        void ChannelSelect::startDiskInEvent() {
            mpDiskFadeAnim->setAnmType(ANIM_TYPE_FORWARD);
            mpDiskFadeAnim->play();
            mpDiskInAnim->play();
        }

        void ChannelSelect::startDiskOutEvent() {
            mpDiskFadeAnim->setAnmType(ANIM_TYPE_BACKWARD);
            mpDiskFadeAnim->play();
            mpDiskOutAnim->play();
        }

        void ChannelSelect::setChanFrameVisibility() {
            int neg;
            if (mState == STATE_LEFT_PAGE_SCROLL || mState == STATE_DRAG_SCROLL_LEFT) {
                neg = 1;
            } else {
                neg = 0;
            }

            if ((mCurrentPage - 1) - neg >= 0) {
                mpLayout->FindPaneByName(mscEdgePaneNames[0])->SetVisible(true);
                mpLayout->FindPaneByName(mscEdgePaneNames[1])->SetVisible(true);
            } else {
                mpLayout->FindPaneByName(mscEdgePaneNames[1 - neg])->SetVisible(false);
            }

            if (mState == STATE_RIGHT_PAGE_SCROLL || mState == STATE_DRAG_SCROLL_RIGHT) {
                neg = 1;
            } else {
                neg = 0;
            }

            if ((mCurrentPage + 1) + neg < mMaxPages) {
                mpLayout->FindPaneByName(mscEdgePaneNames[3])->SetVisible(true);
                mpLayout->FindPaneByName(mscEdgePaneNames[4])->SetVisible(true);
            } else {
                mpLayout->FindPaneByName(mscEdgePaneNames[3 + neg])->SetVisible(false);
            }
        }

        BOOL ChannelSelect::isChannelInView(int page, int index) const {
            int pageOrEdgeIndex = mCurrentPage;
            if (page == pageOrEdgeIndex) {
                return TRUE;
            }

            if (page == pageOrEdgeIndex - 1) {
                if (mState == STATE_LEFT_PAGE_SCROLL || mState == STATE_DRAG_SCROLL_LEFT) {
                    return TRUE;
                }
                pageOrEdgeIndex = 3;
                for (int i = 0; i < MAX_CHANNEL_COLUMN; i++) {
                    if (pageOrEdgeIndex == index) {
                        return TRUE;
                    }
                    pageOrEdgeIndex += MAX_CHANNEL_ROW;
                }
            }

            else if (page == pageOrEdgeIndex - 2) {
                if (mState == STATE_LEFT_PAGE_SCROLL || mState == STATE_DRAG_SCROLL_LEFT) {
                    pageOrEdgeIndex = 3;
                    for (int i = 0; i < MAX_CHANNEL_COLUMN; i++) {
                        if (pageOrEdgeIndex == index) {
                            return TRUE;
                        }
                        pageOrEdgeIndex += MAX_CHANNEL_ROW;
                    }
                }
            }

            else if (page == pageOrEdgeIndex + 1) {
                if (mState == STATE_RIGHT_PAGE_SCROLL || mState == STATE_DRAG_SCROLL_RIGHT) {
                    return TRUE;
                }
                pageOrEdgeIndex = 0;
                for (int i = 0; i < MAX_CHANNEL_COLUMN; i++) {
                    if (pageOrEdgeIndex == index) {
                        return TRUE;
                    }
                    pageOrEdgeIndex += MAX_CHANNEL_ROW;
                }
            }

            else if (page == pageOrEdgeIndex + 2) {
                if (mState == STATE_RIGHT_PAGE_SCROLL || mState == STATE_DRAG_SCROLL_RIGHT) {
                    pageOrEdgeIndex = 0;
                    for (int i = 0; i < MAX_CHANNEL_COLUMN; i++) {
                        if (pageOrEdgeIndex == index) {
                            return TRUE;
                        }
                        pageOrEdgeIndex += MAX_CHANNEL_ROW;
                    }
                }
            }

            return FALSE;
        }

        BOOL ChannelSelect::isChannelInCalc(int page, int index, int currentPage) const {
            int pageOffset = page - currentPage;
            if (pageOffset <= -3 || pageOffset >= 3 || strcmp(mscChanPaneNames[pageOffset + 2][index], "") == 0) {
                return FALSE;
            } else {
                return TRUE;
            }
        }

        BOOL ChannelSelect::isPageCreated(int page) const {
            for (int i = 0; i < MAX_CHANNEL_INDEX; i++) {
                ChannelObj* chanObj = searchList(page, i);
                if (chanObj == NULL || !chanObj->isLayoutCreated()) {
                    return FALSE;
                }
            }
            if (page + 1 < mMaxPages) {
                for (int i = 0; i < MAX_CHANNEL_INDEX; i += MAX_CHANNEL_ROW) {
                    ChannelObj* chanObj = searchList(page + 1, i);
                    if (chanObj == NULL || !chanObj->isLayoutCreated()) {
                        return FALSE;
                    }
                }
            }
            if (page - 1 >= 0) {
                for (int i = 3; i < MAX_CHANNEL_INDEX; i += MAX_CHANNEL_ROW) {
                    ChannelObj* chanObj = searchList(page - 1, i);
                    if (chanObj == NULL || !chanObj->isLayoutCreated()) {
                        return FALSE;
                    }
                }
            }
            return TRUE;
        }

        BOOL ChannelSelect::isPageCreatedAllDone(int page) const {
            if (!isPageCreated(page)) {
                return FALSE;
            } else if (page < mMaxPages - 1 && !isPageCreated(page + 1)) {
                return FALSE;
            } else if (page > 0 && !isPageCreated(page - 1)) {
                return FALSE;
            } else {
                return TRUE;
            }
        }

        extern "C" char scSE_WSD_SELECT[] = "WSD_SELECT";

        void ChannelSelect::preparePageScrolling(int nextState) {
            mbModuleSceneChange = true;
            mState = nextState;
            mbWaitForModuleStop = false;
            snd::getSystem()->startSE(scSE_WSD_SELECT);
        }

        void ChannelSelect::startPageScroll(int nextState) {
            if (nextState == STATE_LEFT_PAGE_SCROLL) {
                mpLayout->setMinFrame(0.0f);
                mpLayout->setMaxFrame(20.0f);
            } else {
                mpLayout->setMinFrame(40.0f);
                mpLayout->setMaxFrame(60.0f);
            }
            mpLayout->setAnmType(ANIM_TYPE_FORWARD);
            mpLayout->start();
            mState = nextState;
        }

        void ChannelSelect::tryToStartBoardScene() {
            if (unkBool()) {
                Button* button = getButton();
                button->animation(Button::IDANIM_FROM_CH_SEL_TO_BOARD);
                if (mbLeftArrowVisible) {
                    button->animation(Button::IDANIM_ARROW_LEFT_DISAPPEAR);
                }
                if (mbRightArrowVisible) {
                    button->animation(Button::IDANIM_ARROW_RIGHT_DISAPPEAR);
                }
                button->animation(Button::IDANIM_SD_BUTTON_BTN_OUT);
                button->setEventHandler(NULL);
                button->get_sd_menu_btn()->setEventHandler(NULL);

                mpLayout->setMinFrame(70.0f);
                mpLayout->setMaxFrame(90.0f);
                mpLayout->setAnmType(ANIM_TYPE_FORWARD);
                mpLayout->start();

                mState = STATE_BOARD_SCENE;
            }
        }

        void ChannelSelect::startChanTtlScene(int page, int index) {
            ChannelObj* chanObj = searchList(page, index);

            initChanZoomParam(math::VEC3(chanObj->mpThumbLayout->GetRootPane()->GetTranslate()), 0);
            chanObj->setCursorDecideAnim();

            Button* button = getButton();
            if (mbLeftArrowVisible) {
                button->animation(Button::IDANIM_ARROW_LEFT_DISAPPEAR);
            }
            if (mbRightArrowVisible) {
                button->animation(Button::IDANIM_ARROW_RIGHT_DISAPPEAR);
            }

            button->disableBtn();
            button->setEventHandler(NULL);
            button->get_sd_menu_btn()->setEventHandler(NULL);
            channel::Manager::setCurrentChannel(page, index);

            mState = STATE_NORMAL_WAIT_LOADING;
            mbModuleSceneChange = true;
            mbWaitForModuleStop = true;

            snd::getSystem()->startSE("WIPL_SE_BT_PUSH");
            snd::getSystem()->stopBGM(5);
        }

        void ChannelSelect::reserveSceneChangeDerived(int page, int index) {
            s32 sceneID = System::getChannelManager()->getSceneID(page, index);

            if (sceneID != 0) {
                createChildScene(SCENE_CHANNEL_TITLE, this, NULL, this);
            }
        }

        BOOL ChannelSelect::tellStartingZoomAnm() {
            mpLayout->setMinFrame(200.0f);
            mpLayout->setMaxFrame(228.0f);
            mpLayout->setAnmType(ANIM_TYPE_FORWARD);
            mpLayout->start();

            snd::getSystem()->startSE("WIPL_SE_CH_SELECT");

            mState = STATE_NORMAL_FADE_ZOOM;
            return TRUE;
        }

        BOOL ChannelSelect::prepareRestarting(int page) {
            if (page == mCurrentPage) {
                return isPageCreated(page);
            } else {
                mCurrentPage = page;
                refreshChannelList(page);
                return isPageCreated(page);
            }
        }

        void ChannelSelect::restart(int page, int index) {
            mpLayout->setAnmType(ANIM_TYPE_BACKWARD);
            mpLayout->start();

            math::VEC3 myVec(getDispChanTrans(index));
            initChanZoomParam(myVec, 1);
            setChanZoomOrtho();

            if (System::getChannelManager()->isDiskChannelReady()) {
                if (System::getBS2Manager()->getIPLState() == bs2::IPL_STATE_RVL_GAME ||
                    System::getBS2Manager()->getIPLState() == bs2::IPL_STATE_DISK_UPDATE) {
                    if (mspDiskID != NULL) {
                        if (mspDiskMaker != NULL) {
                            // unused
                            char* diskID;
                            char* diskMaker;
                            System::getBS2Manager()->getDiskInfo((char**)&diskID, (char**)&diskMaker);

                            if (strncmp(diskID, mspDiskID, 4) == 0) {
                                if (strncmp(diskMaker, mspDiskMaker, 2) == 0) {
                                    System::getChannelManager()->setDiskChannelReady(false);
                                }
                            }
                        }
                    }
                }
            }

            mpPriorityModuleChanObj = searchList(page, index);

            ChannelObj* chanObj = NULL;
            FOREACH_CHANNEL_OBJ(chanObj) {
                chanObj->FillModuleCount();
            }

            mState = STATE_NORMAL_RESTART;
        }

        nw4r::lyt::Pane* ChannelSelect::getChannelBasePane(int page, int index, int currentPage) const {
            if (isChannelInCalc(page, index, currentPage)) {
                return mpLayout->FindPaneByName(mscChanPaneNames[(page - currentPage) + 2][index]);
            } else {
                return mpLayout->FindPaneByName("Picture_16");
            }
        }

        const nw4r::lyt::Pane* ChannelSelect::getChannelBasePane(int index) const {
            return mpLayout->FindPaneByName(mscChanPaneNames[2][index]);
        }

        nw4r::lyt::Pane* ChannelSelect::getChannelBasePane(int index) {
            return mpLayout->FindPaneByName(mscChanPaneNames[2][index]);
        }

        nw4r::math::VEC3 ChannelSelect::getDispChanTrans(int index) const {
            nw4r::math::VEC3 vec(0.0f, 0.0f, 0.0f);
            MTXMultVec(getChannelBasePane(index)->GetGlobalMtx(), vec, vec);
            return vec;
        }

        void ChannelSelect::setChannelScissor(const ChannelObj* channelObj) const {
            nw4r::math::VEC3 vec(channelObj->getTranslate());
            nw4r::ut::Rect projRect;
            System::getProjectionRect(&projRect);
            GXRenderModeObj* rMode = System::getRenderModeObj();
            f32 scissorX;
            f32 scissorY;
            f32 scissorWidth;
            f32 scissorHeight;
            u16 fbWidth;
            u16 efbHeight;
            if (mState == STATE_NORMAL_FADE_ZOOM || mState == STATE_NORMAL_DONE_FADE_ZOOM || mState == STATE_NORMAL_RESTART) {
                nw4r::math::MTX44 mtx;
                f32 right = mOrthoTrans.x + projRect.right / mOrthoScale.x;
                f32 left = mOrthoTrans.x + projRect.left / mOrthoScale.x;
                f32 bottom = mOrthoTrans.y - projRect.bottom / mOrthoScale.y;
                f32 top = mOrthoTrans.y - projRect.top / mOrthoScale.y;
                MTXOrtho(mtx, top, bottom, left, right, -100.0f, 100.0f);
                nw4r::math::VEC4 vec4_in(vec.x, vec.y, 0.0f, 1.0f);
                nw4r::math::VEC4 vec4;
                nw4r::math::VEC4Transform(&vec4, &mtx, &vec4_in);
                fbWidth = rMode->fbWidth;
                efbHeight = rMode->efbHeight;
                f32 projectionWidth = projRect.GetWidth();
                scissorX = ((1.0f + vec4.x) * fbWidth / 2) - ((mChanThumbOff_X * mOrthoScale.x) * (fbWidth / projectionWidth));
                scissorY = (efbHeight - ((1.0f + vec4.y) * efbHeight / 2)) - (mChanThumbOff_Y * mOrthoScale.y);
                scissorWidth = 2.0f * (mChanThumbOff_X * mOrthoScale.x) * (fbWidth / projectionWidth);
                scissorHeight = 2.0f * (mChanThumbOff_Y * mOrthoScale.y);
            } else {
                fbWidth = rMode->fbWidth;
                efbHeight = rMode->efbHeight;
                scissorX = ((f32)fbWidth / 2) + ((vec.x - mChanThumbOff_X) * (fbWidth / projRect.GetWidth()));
                scissorY = (((f32)efbHeight / 2) - vec.y) - mChanThumbOff_Y;
                scissorWidth = 2.0f * mChanThumbOff_X * (fbWidth / projRect.GetWidth());
                scissorHeight = 2.0f * mChanThumbOff_Y;
            }
            scissorX -= 1.0f;
            scissorY -= 1.0f;
            scissorWidth += 2.0f;
            scissorHeight += 2.0f;
            if (scissorX >= fbWidth || (scissorX + scissorWidth) <= 0.0f || scissorY >= efbHeight || (scissorY + scissorHeight) <= 0.0f) {
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

        void ChannelSelect::initChanZoomParam(const math::VEC3& pos, BOOL zoomOut) {
            nw4r::ut::Rect projRect;
            System::getProjectionRect(&projRect);

            math::VEC3 screenTopLeft(projRect.left, -projRect.top, 0.0f);
            math::VEC3 channelTopLeft(pos.x - mChanThumbOff_X, pos.y + mChanThumbOff_Y, 0.0f);
            math::VEC3 screenTopRight(projRect.right, -projRect.top, 0.0f);
            math::VEC3 channelTopRight(pos.x + mChanThumbOff_X, pos.y + mChanThumbOff_Y, 0.0f);
            math::VEC3 screenBottomLeft(projRect.left, -projRect.bottom, 0.0f);
            math::VEC3 channelBottomLeft(pos.x - mChanThumbOff_X, pos.y - mChanThumbOff_Y, 0.0f);
            math::VEC3 screenBottomRight(projRect.right, -projRect.bottom, 0.0f);
            math::VEC3 channelBottomRight(pos.x + mChanThumbOff_X, pos.y - mChanThumbOff_Y, 0.0f);

            if (!zoomOut) {
                mpChanZoomParams[0]->init(screenTopLeft, channelTopLeft, 28.0f, 0.0f, 0.0f, ANIM_TYPE_FORWARD);
                mpChanZoomParams[1]->init(screenTopRight, channelTopRight, 28.0f, 0.0f, 0.0f, ANIM_TYPE_FORWARD);
                mpChanZoomParams[2]->init(screenBottomLeft, channelBottomLeft, 28.0f, 0.0f, 0.0f, ANIM_TYPE_FORWARD);
                mpChanZoomParams[3]->init(screenBottomRight, channelBottomRight, 28.0f, 0.0f, 0.0f, ANIM_TYPE_FORWARD);
            } else {
                mpChanZoomParams[0]->init(channelTopLeft, screenTopLeft, 28.0f, 0.0f, 0.0f, ANIM_TYPE_FORWARD);
                mpChanZoomParams[1]->init(channelTopRight, screenTopRight, 28.0f, 0.0f, 0.0f, ANIM_TYPE_FORWARD);
                mpChanZoomParams[2]->init(channelBottomLeft, screenBottomLeft, 28.0f, 0.0f, 0.0f, ANIM_TYPE_FORWARD);
                mpChanZoomParams[3]->init(channelBottomRight, screenBottomRight, 28.0f, 0.0f, 0.0f, ANIM_TYPE_FORWARD);
            }

            for (int i = 0; i < 4; i++) {
                mpChanZoomParams[i]->play();
            }
        }

        void ChannelSelect::calcChanZoomParam() {
            for (int i = 0; i < 4; i++) {
                mpChanZoomParams[i]->calc();
            }
        }

        void ChannelSelect::setChanZoomOrtho() {
            nw4r::math::VEC3 frames[3];
            for (int i = 0; i < 3; i++) {
                frames[i] = mpChanZoomParams[i]->get();
            }

            nw4r::ut::Rect projRect;
            System::getProjectionRect(&projRect);

            mOrthoTrans = math::VEC3((frames[0].x + frames[1].x) / 2, (frames[0].y + frames[2].y) / 2, 0.0f);
            mOrthoScale = math::VEC2(projRect.GetWidth() / (frames[1].x - frames[0].x), projRect.GetHeight() / (frames[0].y - frames[2].y));
        }

        int ChannelSelect::isInChannelPaneNames(const char* name) const {
            int i = 0;
            for (i = 0; i < MAX_CHANNEL_INDEX; i++) {
                if (strcmp(name, mscChanPaneNames[2][i]) == 0) {
                    break;
                }
            }
            return i < MAX_CHANNEL_INDEX ? i : -1;
        }

        EGG::ExpHeap* ChannelSelect::getFreeModuleExHeap() {
            int i = 0;
            for (i = 0; i < 49; i++) {
                if (!mbModuleHeapInUse[i]) {
                    break;
                }
            }
            return mpModuleHeaps[i];
        }

        void ChannelSelect::updateModuleExHeap(EGG::ExpHeap* heap1, EGG::ExpHeap* heap2) {
            if (heap1 != NULL || heap2 != NULL) {
                for (int i = 0; i < 49; i++) {
                    if (heap1 != NULL && mpModuleHeaps[i] == heap1) {
                        mbModuleHeapInUse[i] = false;
                        heap1->freeAll();
                    }
                    if (heap2 != NULL && mpModuleHeaps[i] == heap2) {
                        mbModuleHeapInUse[i] = true;
                    }
                }
            }
        }

        void ChannelSelect::restartChannelModules() {
            if (!mbModuleSceneChange) {
                mModuleState = 1;
            }
            mbModuleSceneChange = false;
            mbWaitForModuleStop = true;
        }

        void ChannelSelect::createChanMoveLayout() {
            mpMoveThumbnailLayout = new layout::Object(getSceneHeap(), mpLayoutFile, "arc", "my_IplTop_b.brlyt");
            mpMoveThumbnailAnim = mpMoveThumbnailLayout->bind("my_IplTop_b.brlan");

            f32 frame = System::getRndm()->get_u16() % 2000;
            mpMoveThumbnailAnim->play();
            mpMoveThumbnailLayout->finishBinding();
            mpMoveThumbnailAnim->setCurrentFrame(frame);

            mpMoveLytMask = new layout::Object(getSceneHeap(), mpLayoutFile, "arc", "my_TVMask_a.brlyt");
            mpMoveLytMask->bind("my_TVMask_a_Apear.brlan", "Picture_00", false);
            mpMoveLytMask->bind("my_TVMask_a_Lost.brlan", "Picture_00", false, false);
            mpMoveLytMask->finishBinding();
            mpMoveLytMask->getAnim()->initAnmFrame();

            mpMoveLytObject = new layout::Object(getSceneHeap(), mpLayoutFile, "arc", "my_TVShade_a.brlyt");
            mpMoveLytObject->bind("my_TVShade_a_Apear.brlan", "4x3", true);
            mpMoveLytObject->bind("my_TVShade_a_Lost.brlan", "4x3", true, false);
            mpMoveLytObject->finishBinding();

            if (SCGetAspectRatio() == SC_ASPECT_RATIO_16x9) {
                GXTexObj tex;
                mpMoveLytObject->FindPaneByName("16x9")->GetMaterial()->GetTexture(&tex, GX_TEXMAP0);
                mpMoveLytObject->FindPaneByName("4x3")->GetMaterial()->SetTexture(GX_TEXMAP0, tex);
                mpMoveLytObject->FindPaneByName("4x3_dummy")->GetMaterial()->SetTexture(GX_TEXMAP0, tex);
            }

            mpMoveLytObject->getAnim()->initAnmFrame();

            mpMoveLytDrop = new layout::Object(getSceneHeap(), mpLayoutFile, "arc", "my_TVApear_a.brlyt");
            mpMoveLytDrop->bind("my_TVApear_a_Apear.brlan", "Picture_00", false);
            mpMoveLytDrop->bind("my_TVApear_a_Lost.brlan", "Picture_00", false, false);
            mpMoveLytDrop->finishBinding();
            mpMoveLytDrop->getAnim()->initAnmFrame();
        }

        extern "C" char scSE_WIPL_SE_CH_TARGETTING[] = "WIPL_SE_CH_TARGETTING";
        extern "C" char scSE_WIPL_SE_CH_HOLD[] = "WIPL_SE_CH_HOLD";
        extern "C" char scSE_WIPL_SE_CH_SET[] = "WIPL_SE_CH_SET";
        extern "C" char scSE_WIPL_SE_CH_NOT_MOVE[] = "WIPL_SE_CH_NOT_MOVE";

        void ChannelSelect::calcNormalGrab() {
            Button* button = getButton();
            if (button != NULL && button->isActive()) {
                button->update();
            }

            mpGui->update();

            if (System::getControllerManager()->getController(mConChan) == NULL ||
                !System::getControllerManager()->getController(mConChan)->pinch()) {
                mbDragReleased = true;
            }

            if (mDragLeftScrollFrame >= 0) {
                mDragLeftScrollFrame++;
            }
            if (mDragRightScrollFrame >= 0) {
                mDragRightScrollFrame++;
            }

            moveDrag();

            if (!mpMoveLytMask->getAnim(0)->isPlaying() && !mpMoveLytObject->getAnim(0)->isPlaying()) {
                mState = STATE_NORMAL_DRAG;
            }
        }

        void ChannelSelect::calcNormalDrag() {
            Button* button = getButton();
            if (button != NULL && button->isActive()) {
                button->update();
            }

            mpGui->update();

            if (System::getControllerManager()->getController(mConChan) == NULL ||
                !System::getControllerManager()->getController(mConChan)->pinch()) {
                mbDragReleased = true;
            }

            if (mDragLeftScrollFrame >= 0) {
                mDragLeftScrollFrame++;
            }
            if (mDragRightScrollFrame >= 0) {
                mDragRightScrollFrame++;
            }

            moveDrag();

            if (mbDragReleased) {
                finishDrag();
                return;
            }

            if (mCurrentPage > 0 && mDragLeftScrollFrame >= 15 && isPageCreatedAllDone(mCurrentPage)) {
                if (unkBool()) {
                    button->animation(Button::IDANIM_ARROW_LEFT_SELECT);
                    mpLayout->setMinFrame(0.0f);
                    mpLayout->setMaxFrame(20.0f);
                    mpLayout->setAnmType(ANIM_TYPE_FORWARD);
                    mpLayout->start();

                    mState = STATE_DRAG_SCROLL_LEFT;

                    mDragLeftScrollFrame = 0;
                    mDragRightScrollFrame = -1;

                    ChannelObj* chanObj = NULL;
                    FOREACH_CHANNEL_OBJ(chanObj) {
                        chanObj->initCursorAnim(true);
                    }

                    for (int i = 0; i < MAX_CHANNEL_INDEX; i++) {
                        mpGui->initPane(getChannelBasePane(i));
                    }
                    snd::getSystem()->startSE(scSE_WSD_SELECT);
                    return;
                }
            }

            if (mCurrentPage < mMaxPages - 1 && mDragRightScrollFrame >= 15 && isPageCreatedAllDone(mCurrentPage)) {
                if (unkBool()) {
                    button->animation(Button::IDANIM_ARROW_RIGHT_SELECT);
                    mpLayout->setMinFrame(40.0f);
                    mpLayout->setMaxFrame(60.0f);
                    mpLayout->setAnmType(ANIM_TYPE_FORWARD);
                    mpLayout->start();

                    mState = STATE_DRAG_SCROLL_RIGHT;

                    mDragLeftScrollFrame = -1;
                    mDragRightScrollFrame = 0;

                    ChannelObj* chanObj = NULL;
                    FOREACH_CHANNEL_OBJ(chanObj) {
                        chanObj->initCursorAnim(true);
                    }

                    for (int i = 0; i < MAX_CHANNEL_INDEX; i++) {
                        mpGui->initPane(getChannelBasePane(i));
                    }
                    snd::getSystem()->startSE(scSE_WSD_SELECT);
                    return;
                }
            }
        }

        void ChannelSelect::calcNormalReleaseWait() {
            mReleaseWaitFrame++;
            if (mReleaseWaitFrame > 20) {
                mpMoveLytMask->getAnim(1)->play();
                mState = STATE_NORMAL_RELEASE;
            }
        }

        void ChannelSelect::calcNormalRelease() {
            if (!mpMoveLytMask->getAnim(1)->isPlaying() && !mpMoveLytObject->getAnim(1)->isPlaying()) {
                restartChannelModules();
                mState = STATE_NORMAL;
            }
        }

        void ChannelSelect::calcNormalMoveChanIn() {
            if (!mpMoveLytDrop->getAnim(0)->isPlaying()) {
                if (mMoveOldPage == mMoveNewPage && mMoveOldIndex == mMoveNewIndex) {
                    mpMoveLytDrop->getAnim(1)->play();
                    mState = STATE_NORMAL_MOVE_CHAN_OUT;
                } else {
                    System::getChannelManager()->moveChannelInfo(mMoveOldPage, mMoveOldIndex, mMoveNewPage, mMoveNewIndex);
                    mpMovedChanObj = searchList(mMoveOldPage, mMoveOldIndex);
                    if (mpMovedChanObj == NULL) {
                        EGG::FrmHeap* heap = EGG::FrmHeap::create(0x212B8, mpThumbnailHeap, MEM_HEAP_OPT_DEBUG_FILL);
                        mpMovedChanObj = new (mpChannelObjHeap, 4) ChannelObj(heap, mMoveNewPage, mMoveNewIndex);
                        createChannelThumbnail(mpMovedChanObj);
                    } else {
                        ChannelObj* chanObj = searchList(mMoveNewPage, mMoveNewIndex);
                        mpMovedChanObj->setBasePane(getChannelBasePane(mMoveNewPage, mMoveNewIndex, mCurrentPage));
                        chanObj->setBasePane(getChannelBasePane(mMoveOldPage, mMoveOldIndex, mCurrentPage));

                        mpMovedChanObj->setPageIndex(mMoveNewPage, mMoveNewIndex);
                        chanObj->setPageIndex(mMoveOldPage, mMoveOldIndex);

                        mpMovedChanObj->calc();
                        chanObj->calc();

                        mpMovedChanObj = NULL;
                        chanObj->mpThumbAnim->setCurrentFrame(mpMoveThumbnailAnim->getCurrentFrame());
                    }

                    mpSaveDataFile = System::getSaveData()->flushAsync(System::getMem2App());
                    mState = STATE_NORMAL_MOVE_CHAN_SAVE;
                }
            }
        }

        void ChannelSelect::calcNormalMoveChanSave() {
            if (System::getSaveData()->isFinished(mpSaveDataFile) && (mpMovedChanObj == NULL || mpMovedChanObj->isLayoutCreated())) {
                if (mpMovedChanObj != NULL) {
                    ChannelObj* chanObj = searchList(mMoveNewPage, mMoveNewIndex);
                    nw4r::ut::List_Insert(&mChanList, chanObj, mpMovedChanObj);
                    nw4r::ut::List_Remove(&mChanList, chanObj);
                    destroyChannelObj(chanObj);
                    mpMovedChanObj = NULL;
                } else {
                    ChannelObj* chanObj = searchList(mMoveOldPage, mMoveOldIndex);
                    ChannelObj* chanObj2 = searchList(mMoveNewPage, mMoveNewIndex);
                    ChannelObj* chanObj3 = (ChannelObj*)nw4r::ut::List_GetNext(&mChanList, chanObj2);
                    if (chanObj3 == chanObj) {
                        chanObj3 = chanObj2;
                    }
                    nw4r::ut::List_Remove(&mChanList, chanObj2);
                    nw4r::ut::List_Insert(&mChanList, chanObj, chanObj2);
                    nw4r::ut::List_Remove(&mChanList, chanObj);
                    nw4r::ut::List_Insert(&mChanList, chanObj3, chanObj);
                }

                delete mpSaveDataFile;
                mpSaveDataFile = NULL;

                mpMoveLytDrop->getAnim(1)->play();
                mState = STATE_NORMAL_MOVE_CHAN_OUT;
            }
        }

        void ChannelSelect::calcNormalMoveChanOut() {
            if (mpMoveLytMask->getAnim(1)->isPlaying()) {
                return;
            }
            if (mpMoveLytObject->getAnim(1)->isPlaying()) {
                return;
            }
            if (mpMoveLytDrop->getAnim(1)->isPlaying()) {
                return;
            }

            f32 frame = System::getRndm()->get_u16() % 2000;
            mpMoveThumbnailAnim->setCurrentFrame(frame);
            restartChannelModules();
            mState = STATE_NORMAL;
        }

        void ChannelSelect::calcNormalDragScrl() {
            Button* button = getButton();
            if (button != NULL && button->isActive()) {
                button->update();
            }

            if (System::getControllerManager()->getController(mConChan) == NULL ||
                !System::getControllerManager()->getController(mConChan)->pinch()) {
                mbDragReleased = true;
            }

            moveDrag();

            if (mpLayout->isPlaying(0)) {
                return;
            }

            button = getButton();

            if (mState == STATE_DRAG_SCROLL_LEFT) {
                if (--mCurrentPage == 0) {
                    button->animation(Button::IDANIM_ARROW_LEFT_DISAPPEAR);
                    mbLeftArrowVisible = false;
                } else if (!mbRightArrowVisible) {
                    button->animation(Button::IDANIM_ARROW_RIGHT_APPEAR);
                    mbRightArrowVisible = true;
                }
            } else {
                if (++mCurrentPage == mMaxPages - 1) {
                    button->animation(Button::IDANIM_ARROW_RIGHT_DISAPPEAR);
                    mbRightArrowVisible = false;
                } else if (mbLeftArrowVisible == 0) {
                    button->animation(Button::IDANIM_ARROW_LEFT_APPEAR);
                    mbLeftArrowVisible = true;
                }
            }

            mpLayout->finishBinding();

            refreshChannelList(mCurrentPage);
            mState = STATE_NORMAL_DRAG;
        }

        BOOL ChannelSelect::onEventDrag(const char* paneName, u32 event, controller::Interface* con) {
            if (con != NULL && con != System::getControllerManager()->getController(mConChan)) {
                return TRUE;
            }

            int id = isInChannelPaneNames(paneName);

            if (id >= 0) {
                switch (event) {
                    case ::gui::EventHandler::ON_RELEASE: {
                        if (!con->pinch()) {
                            mMoveNewIndex = id;
                            mMoveNewPage = mCurrentPage;
                            mbDragReleased = true;
                            break;
                        }
                        break;
                    }
                    case ::gui::EventHandler::ON_POINT: {
                        if (isReleasableArea(mCurrentPage, id) || (mCurrentPage == mMoveOldPage && id == mMoveOldIndex)) {
                            searchList(mCurrentPage, id)->onPoint(2);
                            snd::getSystem()->startSE(scSE_WIPL_SE_CH_TARGETTING);
                            con->rumble(1);
                            break;
                        }
                        break;
                    }
                    case ::gui::EventHandler::ON_LEFT: {
                        if (isReleasableArea(mCurrentPage, id) || (mCurrentPage == mMoveOldPage && id == mMoveOldIndex)) {
                            searchList(mCurrentPage, id)->onLeft(2);
                            break;
                        }
                        break;
                    }
                }
            }

            return TRUE;
        }

        void ChannelSelect::onEventDerivedDrag(const char* paneName, u32 event, const controller::Interface* con) {
            if (con == NULL || con == System::getControllerManager()->getController(mConChan)) {
                switch (event) {
                    case ::gui::EventHandler::ON_LEFT: {
                        if (Button::cmpButtonName(paneName, Button::BTN_ARROW_LEFT) == 0 && mCurrentPage > 0) {
                            mDragLeftScrollFrame = -1;
                        } else if (Button::cmpButtonName(paneName, Button::BTN_ARROW_RIGHT) == 0 && mCurrentPage < mMaxPages - 1) {
                            mDragRightScrollFrame = -1;
                        }
                        break;
                    }
                    case ::gui::EventHandler::ON_POINT: {
                        if (Button::cmpButtonName(paneName, Button::BTN_ARROW_LEFT) == 0 && mCurrentPage > 0) {
                            if (mDragLeftScrollFrame < 0) {
                                mDragLeftScrollFrame = 0;
                            }
                        } else if (Button::cmpButtonName(paneName, Button::BTN_ARROW_RIGHT) == 0 && mCurrentPage < mMaxPages - 1) {
                            if (mDragRightScrollFrame < 0) {
                                mDragRightScrollFrame = 0;
                            }
                        }
                        break;
                    }
                }
            }
        }

        void ChannelSelect::startDrag(const controller::Interface* con, int page, int index) {
            if (con->getChannel() >= 0) {
                if (con->isValidDpd()) {
                    mDragPos = con->getDpdPos();
                } else {
                    mDragPos = nw4r::math::VEC2(0.0f, 0.0f);
                }

                mConChan = con->getChannel();
                mMoveOldPage = page;
                mMoveOldIndex = index;
                mMoveNewPage = -1;
                mMoveNewIndex = -1;
                mDragRightScrollFrame = -1;
                mDragLeftScrollFrame = -1;
                mReleaseWaitFrame = 0;
                mbDragReleased = false;

                System::getPointer()->changeType(con->getChannel(), Pointer::TYPE_GRAB);

                mpMoveLytMask->getAnim(0)->play();
                mpMoveLytObject->getAnim(0)->play();

                getButton()->disableBtn();

                ChannelObj* chanObj = NULL;
                FOREACH_CHANNEL_OBJ(chanObj) {
                    int chanPage = chanObj->mChanPage;
                    int chanIndex = chanObj->mChanIndex;
                    chanObj->onPinch(chanPage == page && chanIndex == index);
                }

                mbModuleSceneChange = true;
                mbWaitForModuleStop = true;

                snd::getSystem()->startSEwithPos(scSE_WIPL_SE_CH_HOLD, mDragPos.x);

                mState = STATE_NORMAL_GRAB;
            }
        }

        void ChannelSelect::finishDrag() {
            if (isReleasableArea(mMoveNewPage, mMoveNewIndex)) {
                nw4r::math::VEC3 translate = searchList(mMoveNewPage, mMoveNewIndex)->getTranslate();
                mpMoveLytDrop->GetRootPane()->SetTranslate(translate);
                mpMoveLytDrop->getAnim(0)->play();

                snd::getSystem()->startSEwithPos(scSE_WIPL_SE_CH_SET, mDragPos.x);

                mpMoveLytMask->getAnim(1)->play();

                mState = STATE_NORMAL_MOVE_CHAN_IN;
            } else {
                snd::getSystem()->startSEwithPos(scSE_WIPL_SE_CH_NOT_MOVE, mDragPos.x);

                mState = STATE_NORMAL_RELEASE_WAIT;
            }

            System::getPointer()->changeType(mConChan, Pointer::TYPE_POINT);

            mpMoveLytObject->getAnim(1)->play();

            getButton()->enableBtn();

            mbDragReleased = false;

            ChannelObj* chanObj = NULL;
            FOREACH_CHANNEL_OBJ(chanObj) {
                chanObj->initCursorAnim(TRUE);
            }

            for (int i = 0; i < MAX_CHANNEL_INDEX; i++) {
                mpGui->initPane(getChannelBasePane(i));
            }
        }

        bool ChannelSelect::isReleasableArea(int page, int index) {
            if (page < 0 || page >= mMaxPages) {
                return false;
            }

            if (index < 0 || index >= MAX_CHANNEL_INDEX) {
                return false;
            }
            if (page == mMoveOldPage && index == mMoveOldIndex) {
                return true;
            }
            return System::getChannelManager()->getChannel(page, index).loadedBnr == false;
        }

        void ChannelSelect::moveDrag() {
            if (System::getControllerManager()->getController(mConChan) && System::getControllerManager()->getController(mConChan)->isValidDpd()) {
                math::VEC2 pos = System::getControllerManager()->getController(mConChan)->getDpdProjectionPos();
                nw4r::math::VEC3 newPos(pos.x, -pos.y, 0.0f);
                mpMoveLytObject->GetRootPane()->SetTranslate(newPos);
                mpMoveLytObject->calcMtx();

                f32 speed;

                math::VEC2 delta;
                delta.y = pos.y - mDragPos.y;
                delta.x = pos.x - mDragPos.x;

                f32 val = (delta.x * delta.x) + (delta.y * delta.y);

                if (val <= 0.0f) {
                    speed = 0.0f;
                } else {
                    speed = (val * nw4r::math::FrSqrt(val));
                }

                snd::getSystem()->holdSEwithPosDis("WIPL_SE_CH_DRAG", pos.x, speed);
                mDragPos = pos;
            }
        }

        extern "C" char scSE_WIPL_SE_GRAY_BUTTON[] = "WIPL_SE_GRAY_BUTTON";
        extern "C" char scSE_WIPL_SE_DECIDE[] = "WIPL_SE_DECIDE";

        void ChannelSelectEventHandler::onEvent(u32 compId, u32 event, void* data) {
            gui::PaneComponent* component = static_cast<gui::PaneComponent*>(mpManager->getComponent(compId));
            const char* paneName = component->getPane()->GetName();

            controller::Interface* con = static_cast<controller::Interface*>(data);

            BOOL result = FALSE;
            switch (mpInstance->mState) {
                case ChannelSelect::STATE_NORMAL_DRAG:
                case ChannelSelect::STATE_NORMAL_GRAB: {
                    result = mpInstance->onEventDrag(paneName, event, con);
                    break;
                }
            }

            if (!result) {
                int index = mpInstance->isInChannelPaneNames(paneName);
                if (index >= 0) {
                    ChannelObj* chanObj = mpInstance->searchList(mpInstance->mCurrentPage, index);
                    switch (event) {
                        // Drag and trig events are swapped, but still act as intended?
                        case ::gui::EventHandler::ON_TRIG: {
                            if (mpInstance->mState == ChannelSelect::STATE_NORMAL && con != NULL && con->pinchTrg() &&
                                System::getChannelManager()->isNormalChannel(mpInstance->mCurrentPage, index) &&
                                mpInstance->mMaxPages * MAX_CHANNEL_INDEX != (u32)System::getSaveData()->getNumValidChannel()) {
                                mpInstance->startDrag(con, mpInstance->mCurrentPage, index);
                            }
                            break;
                        }
                        case ::gui::EventHandler::ON_DRAG: {
                            if (mpInstance->mState == ChannelSelect::STATE_NORMAL && con != NULL && con->decide() && chanObj->isValid()) {
                                mpInstance->startChanTtlScene(chanObj);
                                TVRCManager::getHandle()->setEnable(FALSE);
                            }
                            break;
                        }
                        case ::gui::EventHandler::ON_POINT: {
                            if (mpInstance->mState == ChannelSelect::STATE_NORMAL && chanObj->isValid()) {
                                chanObj->onPoint(0);
                                snd::getSystem()->startSE(scSE_WIPL_SE_CH_TARGETTING);
                                con->rumble(1);
                            }
                            break;
                        }
                        case ::gui::EventHandler::ON_LEFT: {
                            if (mpInstance->mState == ChannelSelect::STATE_NORMAL && chanObj->isValid()) {
                                chanObj->onLeft(0);
                            }
                            break;
                        }
                    }
                }
            }
        }

        void CsChanSelButtonEventHandler::onEventDerived(u32 compId, u32 event, const controller::Interface* con) {
            gui::PaneComponent* component = static_cast<gui::PaneComponent*>(mpManager->getComponent(compId));
            const char* paneName = component->getPane()->GetName();

            switch (mpInstance->mState) {
                case ChannelSelect::STATE_DRAG_SCROLL_RIGHT:
                case ChannelSelect::STATE_DRAG_SCROLL_LEFT:
                case ChannelSelect::STATE_NORMAL_GRAB:
                case ChannelSelect::STATE_NORMAL_DRAG: {
                    mpInstance->onEventDerivedDrag(paneName, event, con);
                    break;
                }
                default: {
                    switch (event) {
                        case ::gui::EventHandler::ON_TRIG: {
                            if (mpInstance->mState == ChannelSelect::STATE_NORMAL && System::getFader()->getStatus() == EGG::Fader::PREPARE_OUT &&
                                con != NULL && con->downTrg(controller::BTN_INTERACT)) {
                                Button* button = getButton();
                                if (Button::cmpButtonName(paneName, Button::BTN_BBS_BOARD) == 0) {
                                    if (System::isSafeMode()) {
                                        System::getDialog()->callBtn0(MESG_CHAN_SEL_SAFE_MODE, 180);
                                        mpInstance->mState = ChannelSelect::STATE_NORMAL_SAFE_MODE_DIALOG;
                                        snd::getSystem()->startSE(scSE_WIPL_SE_GRAY_BUTTON);
                                    } else {
                                        mpInstance->setSomething();
                                        mpInstance->mState = ChannelSelect::STATE_START_BOARD_SCENE;
                                        mpInstance->tryToStartBoardScene();
                                        TVRCManager::getHandle()->setEnable(FALSE);
                                        snd::getSystem()->startSE(scSE_WIPL_SE_DECIDE);
                                    }
                                } else if (Button::cmpButtonName(paneName, Button::BTN_SETTING) == 0) {
                                    button->setEventHandler(NULL);
                                    button->get_sd_menu_btn()->setEventHandler(NULL);
                                    mpInstance->reserveAllSceneDestruction(SCENE_SETTING_BG, NULL);
                                    getBoard()->requestExit();
                                    System::getFader()->fadeOut();
                                    TVRCManager::getHandle()->setEnable(FALSE);
                                    mpInstance->mState = ChannelSelect::STATE_START_SETTING_SCENE;
                                    snd::getSystem()->startSE(scSE_WIPL_SE_DECIDE);
                                } else if (Button::cmpButtonName(paneName, Button::BTN_ARROW_LEFT) == 0 && mpInstance->mCurrentPage > 0) {
                                    button->animation(Button::IDANIM_ARROW_LEFT_SELECT);
                                    mpInstance->preparePageScrolling(ChannelSelect::STATE_PREP_LEFT_PAGE_SCROLL);
                                } else if (Button::cmpButtonName(paneName, Button::BTN_ARROW_RIGHT) == 0 &&
                                           mpInstance->mCurrentPage < mpInstance->mMaxPages - 1) {
                                    button->animation(Button::IDANIM_ARROW_RIGHT_SELECT);
                                    mpInstance->preparePageScrolling(ChannelSelect::STATE_PREP_RIGHT_PAGE_SCROLL);
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }

        void CsChanSelSDMenuEventHandler::onEventDerived(u32 compId, u32 event, const controller::Interface* con) {
            gui::PaneComponent* component = static_cast<gui::PaneComponent*>(mpManager->getComponent(compId));
            const char* paneName = component->getPane()->GetName();

            switch (event) {
                case ::gui::EventHandler::ON_TRIG: {
                    if (mpInstance->mState == ChannelSelect::STATE_NORMAL && System::getFader()->getStatus() == EGG::Fader::PREPARE_OUT &&
                        con != NULL && con->downTrg(controller::BTN_INTERACT)) {
                        Button* button = getButton();
                        if (strcmp(paneName, getPaneName(SDMenuButton::BTN_SD_CARD)) == 0) {
                            button->animation(Button::IDANIM_SD_BUTTON_SELECT);
                            button->setEventHandler(NULL);
                            button->get_sd_menu_btn()->setEventHandler(NULL);
                            mpInstance->reserveAllSceneDestruction(SCENE_SD_BUTTON, NULL);
                            getBoard()->requestExit();
                            System::getFader()->fadeOut();
                            TVRCManager::getHandle()->setEnable(FALSE);
                            mpInstance->mState = ChannelSelect::STATE_START_SD_MENU_SCENE;
                            snd::getSystem()->startSE(scSE_WIPL_SE_DECIDE);
                        }
                    }
                    break;
                }
            }
        }

        const char* CsChanSelSDMenuEventHandler::getPaneName(int index) {
            return SDMenuButton::getButtonName(index);
        }

        void ChannelSelect::startResetting() {
            snd::getSystem()->resetAllSound();
        }

        // Stripped out function generated a weak of math::VEC2().
#ifndef NON_MATCHING
        math::VEC2 ForceCTORWeak() {
            return math::VEC2(NULL, NULL);
        }
#endif  // NON_MATCHING
    }  // namespace scene
}  // namespace ipl
