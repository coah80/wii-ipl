#define IPL_ADDRESS_MATCHING
#define IPL_SOUND_RECT_OUT_OF_LINE
#include <nw4r/ut/Rect.h>
#undef IPL_SOUND_RECT_OUT_OF_LINE

#include "scene/address/iplAddress.h"

#include "iplSceneUI.h"

#include "scene/board/iplBoard.h"
#include "scene/letterWriter/iplLetterWriter.h"
#include "scene/mailAddSel/iplMailAddressSelect.h"
#include "scene/parentalDialog/iplParentalDialog.h"

#include "scene/setting/iplNCDSetting.h"

#include "system/MESGEntries.h"
#include "system/iplNigaoe.h"
#include "system/iplNigaoeManager.h"
#include "system/iplSystem.h"
#include "utility/iplCharacterCode.h"

#include <string.h>
#include <wchar.h>

namespace ipl {
    namespace scene {
        static const char* sTextNameB[Address::BTN_MAX] = {"T_name_b_00", "T_name_b_01", "T_name_b_02", "T_name_b_03", "T_name_b_04"};

        static const char* sTextNameC[Address::BTN_MAX] = {"T_name_c_00", "T_name_c_01", "T_name_c_02", "T_name_c_03", "T_name_c_04"};

        static const char* sButtonName[Address::BTN_MAX] = {"B_name_b_00", "B_name_b_01", "B_name_b_02", "B_name_b_03", "B_name_b_04"};

        static const char* sButtonSpaceName[Address::BTN_SPACE_MAX] = {"B_name_b_00_01", "B_name_b_01_02", "B_name_b_02_03",
                                                                       "B_name_b_03_04"};

        static const char* sNameGroup[Address::BTN_MAX] = {"name_b_00", "name_b_01", "name_b_02", "name_b_03", "name_b_04"};

        static const char* sNameCGroup[Address::BTN_MAX] = {"G_name_c_00", "G_name_c_01", "G_name_c_02", "G_name_c_03", "G_name_c_04"};

        static math::VEC2 sPageOffset(-1.0f, -1.0f);

        inline void Address::set_textbox(const char* paneName, u32 msgId) {
            set_textbox(paneName, System::getMessage(msgId));
        }

        Address::Address(EGG::Heap* heap, int mode)
            : FaderSceneBase(heap), mMode(mode), mpLayout(NULL), unk_0x90(0), mpEvent(NULL), mpGui(NULL), mpBackLayout(NULL),
              mFadeinState(FADEIN_STATE_FADEIN), mWaitOpenCount(0), mState(STATE_COVER_NORMAL), mPage(0), mNextPageNum(PAGE_MAX),
              mPrevPageNum(0), mSelectedButton(0), mChosenFriend(0), mbParentalOK(false) {
            setSceneParentFlags(SCN_PARENTFLAG_CALC | SCN_PARENTFLAG_DRAW);

            for (int i = 0; i < BTN_MAX; i++) {
                mPointCount[i] = 0;
            }

            for (int i = 0; i < BTN_MAX; i++) {
                mbFaceValid[i] = false;
            }

            memset(&mDrag, 0, sizeof(DragInfo));
            mDrag.mNextCount = -1;
            mDrag.mPrevCount = -1;
        }

        Address::~Address() {
            if (mpFriendCache != NULL) {
                delete mpFriendCache;
            }
        }

        void Address::prepare() {}

        void Address::create() {
            nand::LayoutFile* layoutFile = static_cast<Board*>(System::getScene(SCENE_BOARD))->getLayoutFile();

            mbCover = true;

            // Main layout
            mpLayout = new layout::Object(getSceneHeap(), layoutFile, "arc", "th_Adress_a.brlyt");
            mpLayout->bindToGroup("th_Adress_a_note_alp_in.brlan", "G_note_all", false, true);
            mpLayout->bindToGroup("th_Adress_a_note_alp_out.brlan", "G_note_all", false, false);
            mpLayout->bindToGroup("th_Adress_a_note_trns_in.brlan", "G_note_all", false, false);
            mpLayout->bindToGroup("th_Adress_a_note_trns_out.brlan", "G_note_all", false, false);
            mpLayout->bindToGroup("th_Adress_a_note_e_rtt.brlan", "G_note_e_rtt", false, mbCover);
            mpLayout->bindToGroup("th_Adress_a_note_c_rtt.brlan", "note_c_rtt", false, !mbCover);

            for (int i = 0; i < BTN_MAX; i++) {
                mpLayout->bindToGroup("th_Adress_a_name_in.brlan", sNameGroup[i], false, false);
            }
            for (int i = 0; i < BTN_MAX; i++) {
                mpLayout->bindToGroup("th_Adress_a_name_out.brlan", sNameGroup[i], false, false);
            }
            for (int i = 0; i < BTN_MAX; i++) {
                mpLayout->bindToGroup("th_Adress_a_name_psh.brlan", sNameGroup[i], false, false);
            }
            for (int i = 0; i < BTN_MAX; i++) {
                mpLayout->bindToGroup("th_Adress_a_gry_name_in.brlan", sNameGroup[i], false, false);
            }
            for (int i = 0; i < BTN_MAX; i++) {
                mpLayout->bindToGroup("th_Adress_a_gry_name_out.brlan", sNameGroup[i], false, false);
            }
            for (int i = 0; i < BTN_MAX; i++) {
                mpLayout->bindToGroup("th_Adress_a_gry_name_psh.brlan", sNameGroup[i], false, false);
            }
            for (int i = 0; i < BTN_MAX; i++) {
                mpLayout->bindToGroup("th_Adress_a_name_c_gry.brlan", sNameCGroup[i], false, false);
            }
            mpLayout->finishBinding();

            // Background layout
            mpBackLayout = new layout::Object(getSceneHeap(), layoutFile, "arc", "my_Back_a.brlyt");
            mpBackLayout->bind("my_Back_a_Apear.brlan", "Picture_00", false, true);
            mpBackLayout->bind("my_Back_a_Lost.brlan", "Picture_00", false, false);
            mpBackLayout->finishBinding();
            mpBackLayout->getAnim()->initAnmFrame();

            // Dialog layout
            mpDialogLayout = new layout::Object(getSceneHeap(), layoutFile, "arc", "my_Dialog_a.brlyt");
            mpDialogLayout->bind("my_Dialog_a_DialogIn.brlan", "N_Top", false, true);
            mpDialogLayout->bind("my_Dialog_a_DialogOut.brlan", "N_Top", false, false);
            mpDialogLayout->finishBinding();
            nw4r::lyt::TextBox* dialogText = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpDialogLayout->FindPaneByName("T_Dialog"));
            dialogText->SetString(System::getMessage(MESG_ADDRESS_CHOOSE), 0);

            // GUI
            mpEvent = new AddressEvent(this);
            mpGui = new gui::PaneManager(mpEvent, mpLayout->getDrawInfo(), NULL, NULL);
            mpGui->setupScene(mpLayout);
            mpGui->setAllComponentTriggerTarget(false);
            for (int i = 0; i < BTN_MAX; i++) {
                mpGui->setTriggerTarget(mpLayout->FindPaneByName(sButtonName[i]), true);
            }
            for (int i = 0; i < BTN_SPACE_MAX; i++) {
                mpGui->setTriggerTarget(mpLayout->FindPaneByName(sButtonSpaceName[i]), true);
            }

            // Mii panes
            char miiName[16];
            for (int i = 0; i < BTN_MAX; i++) {
                sprintf(miiName, "mii_b_%02d", i);
                mMiiObj[i].init(mpLayout->FindPaneByName(miiName));
            }
            char nextMiiName[16];
            for (int i = 0; i < BTN_MAX; i++) {
                sprintf(nextMiiName, "mii_c_%02d", i);
                mNextMiiObj[i].init(mpLayout->FindPaneByName(nextMiiName));
            }

            set_textbox("T_adrs_00", MESG_ADDRESS_TITLE);
            set_textbox("T_wii_msg", MESG_ADDRESS_WII_ID);

            // Friend list
            mpFriendCache = new (32) FriendListCache();
            if (mpFriendCache->init()) {
                onInitFriendList();
                mFadeinState = FADEIN_STATE_FADEIN;
            } else {
                mFadeinState = FADEIN_STATE_WAIT_OPEN;
            }

            mpWork = new u8[0x2D20];

            mpLayout->FindPaneByName("N_note_move")->SetVisible(false);
        }

        FaderSceneCommand Address::calcFadein() {
            switch (mFadeinState) {
                case FADEIN_STATE_WAIT_OPEN: {
                    fistt_wait_open();
                    break;
                }
                case FADEIN_STATE_FADEIN: {
                    fistt_fadein();
                    break;
                }
            }

            return mFadeinState == FADEIN_STATE_DONE ? FADER_SCN_NEXT : FADER_SCN_CONTINUE;
        }

        void Address::initCalcNormal() {
            static_cast<Button*>(System::getScene(SCENE_BUTTON))->setEventHandler(this);
        }

        FaderSceneCommand Address::calcNormal() {
            switch (mState) {
                case STATE_INIT: {
                    snd::getSystem()->startSE("WIPL_SE_FL_PAGE_INC");
                    onNextPage();
                    break;
                }
                case STATE_COVER_NORMAL: {
                    stt_cover_normal();
                    break;
                }
                case STATE_COVER_FORWARD: {
                    stt_cover_forward();
                    break;
                }
                case STATE_COVER_BACKWARD: {
                    stt_cover_backward();
                    break;
                }
                case STATE_NORMAL: {
                    stt_normal();
                    break;
                }
                case STATE_FORWARD: {
                    stt_forward();
                    break;
                }
                case STATE_BACKWARD: {
                    stt_backward();
                    break;
                }
                case STATE_LOOP_FORWARD: {
                    stt_loop_forward();
                    break;
                }
                case STATE_LOOP_BACKWARD: {
                    stt_loop_backward();
                    break;
                }
                case STATE_DECIDE: {
                    stt_decide();
                    break;
                }
                case STATE_DRAG: {
                    stt_drag();
                    break;
                }
                case STATE_RELEASE: {
                    stt_release();
                    break;
                }
                case STATE_WAIT_CHILD_CST: {
                    stt_wait_child_cst();
                    break;
                }
                case STATE_WAIT_CHILD_DST: {
                    stt_wait_child_dst();
                    break;
                }
                case STATE_WAIT_CHILD_FADEOUT: {
                    stt_wait_child_fadeout();
                    break;
                }
                case STATE_MSG_NET: {
                    stt_msg_net();
                    break;
                }
                case STATE_WAIT_PARENTAL: {
                    stt_wait_parental();
                    break;
                }
                case STATE_WAIT_PARENTAL_DST: {
                    stt_wait_parental_dst();
                    break;
                }
                case STATE_MSG_WC: {
                    stt_msg_wc();
                    break;
                }
                case STATE_WAIT_PARENTAL_WC: {
                    stt_wait_parental_wc();
                    break;
                }
                case STATE_WAIT_PARENTAL_DST_WC: {
                    stt_wait_parental_dst_wc();
                    break;
                }
                case STATE_MSG_NWC24_ERROR: {
                    stt_msg_nwc24_error();
                    break;
                }
                case STATE_MSG_FI_FULL: {
                    stt_msg_fi_full();
                    break;
                }
                case STATE_MSG_PARENTAL: {
                    stt_msg_parental();
                    break;
                }
                case STATE_MSG_OPEN_FAILURE: {
                    stt_msg_open_failure();
                    break;
                }
                case STATE_WAIT_DIALOG: {
                    stt_wait_dialog();
                    break;
                }
            }

            return mState == STATE_DONE ? FADER_SCN_NEXT : FADER_SCN_CONTINUE;
        }

        void Address::initCalcFadeout() {
            static_cast<Button*>(System::getScene(SCENE_BUTTON))->setEventHandler(NULL);
        }

        FaderSceneCommand Address::calcFadeout() {
            BOOL bAnimDone;
            BOOL ret;

            if (System::getFader()->getStatus() == EGG::Fader::PREPARE_OUT) {
                ret = FALSE;

                bAnimDone = FALSE;
                if (!mpLayout->getAnim(1)->isPlaying() && !mpLayout->getAnim(3)->isPlaying()) {
                    bAnimDone = TRUE;
                }

                if (bAnimDone && !mpDialogLayout->getAnim(1)->isPlaying()) {
                    ret = TRUE;
                }
            } else {
                ret = System::getFader()->getStatus() == EGG::Fader::PREPARE_IN;
            }

            return (FaderSceneCommand)ret;
        }

        void Address::calcCommonAfter() {
            mpLayout->calc();
            mpBackLayout->calc();
            mpDialogLayout->calc();
        }

        static inline math::VEC2 scaledPageOffset(f32 scale) {
            math::VEC2 result;
            result.y = sPageOffset.y * scale;
            result.x = sPageOffset.x * scale;
            return result;
        }

        void Address::draw() {
            if (System::getSceneManager()->onDrawLayer(DRAW_LAYER_2)) {
                utility::Graphics::setOrtho(0);

                nw4r::lyt::Pane* pane = mpLayout->FindPaneByName("N_note_a");
                for (int i = mNextPageNum; i >= 1; i--) {
                    math::VEC2 trans = scaledPageOffset(i);
                    pane->SetTranslate(trans);
                    pane->CalculateMtx(*mpLayout->getDrawInfo());
                    mpLayout->draw(pane);
                }

                mpLayout->draw("N_note_b");

                if (mState == STATE_FORWARD || mState == STATE_BACKWARD) {
                    mpLayout->draw("N_note_c");
                }

                int offset = 0;
                switch (mState) {
                    case STATE_COVER_FORWARD:
                    case STATE_COVER_BACKWARD:
                    case STATE_FORWARD:
                    case STATE_BACKWARD: {
                        offset = 1;
                        break;
                    }
                }

                pane = mpLayout->FindPaneByName("N_note_d");
                for (int i = offset; i < mPrevPageNum + offset; i++) {
                    math::VEC2 trans = sPageOffset * -i;
                    pane->SetTranslate(trans);
                    pane->CalculateMtx(*mpLayout->getDrawInfo());
                    mpLayout->draw(pane);
                }

                pane = mpLayout->FindPaneByName("N_note_e");
                switch (mState) {
                    case STATE_LOOP_FORWARD:
                    case STATE_LOOP_BACKWARD: {
                        for (int i = 1; i < PAGE_MAX; i++) {
                            math::VEC2 trans = sPageOffset * -i;
                    pane->SetTranslate(trans);
                            pane->CalculateMtx(*mpLayout->getDrawInfo());
                            mpLayout->draw(pane);
                        }
                        break;
                    }
                    default: {
                        math::VEC2 trans = sPageOffset * -(mPrevPageNum + offset);
                        pane->SetTranslate(trans);
                        pane->CalculateMtx(*mpLayout->getDrawInfo());
                        mpLayout->draw("N_note_e");
                        break;
                    }
                }

                mpBackLayout->draw();
                mpDialogLayout->draw();
            } else if (System::getSceneManager()->onDrawLayer(DRAW_LAYER_3)) {
                utility::Graphics::setOrtho(0);

                switch (mState) {
                    case STATE_COVER_NORMAL:
                    case STATE_COVER_FORWARD:
                    case STATE_COVER_BACKWARD:
                    case STATE_FORWARD:
                    case STATE_BACKWARD:
                    case STATE_LOOP_FORWARD:
                    case STATE_LOOP_BACKWARD:
                    case STATE_DRAG: {
                        mpLayout->draw("N_note_move");
                        break;
                    }
                }
            }
        }

        void Address::destroy() {
            mpFriendCache->fin();
        }

        void Address::fistt_wait_open() {
            if (mpFriendCache->init()) {
                onInitFriendList();
                mFadeinState = FADEIN_STATE_FADEIN;
            } else if (mWaitOpenCount >= 300) {
                System::getDialog()->callBtn1(MESG_ERROR_NWC24_FATAL, MESG_CMN_OK);
                mState = STATE_MSG_OPEN_FAILURE;
                mFadeinState = FADEIN_STATE_DONE;
            }

            mWaitOpenCount++;
        }

        void Address::fistt_fadein() {
            if (!mpLayout->getAnim(0)->isPlaying() && !mpLayout->getAnim(2)->isPlaying() && !mpDialogLayout->getAnim(0)->isPlaying()) {
                mFadeinState = FADEIN_STATE_DONE;
            }
        }

        void Address::onInitFriendList() {
            Button* button;
            wchar_t idStr[24];
            wchar_t text[24];

            memset(idStr, 0, sizeof(idStr));
            memset(text, 0, sizeof(text));

            utility::CharacterCode::WiiIdToUTF16(idStr, mpFriendCache->getMyUserId());

            // Format the Wii number as "XXXX XXXX XXXX XXXX"
            int textIdx = 0;
            for (int i = 0; i < 4; i++) {
                text[textIdx++] = idStr[i];
            }
            text[textIdx++] = L' ';
            for (int i = 4; i < 8; i++) {
                text[textIdx++] = idStr[i];
            }
            text[textIdx++] = L' ';
            for (int i = 8; i < 12; i++) {
                text[textIdx++] = idStr[i];
            }
            text[textIdx++] = L' ';
            for (int i = 12; i < 16; i++) {
                text[textIdx++] = idStr[i];
            }

            set_textbox("T_wii_name", text);
            set_page_text("T_nmbr_b", mPage + 1);

            for (u32 i = 0; i < BTN_MAX; i++) {
                set_friend(sTextNameB[i], i, i, mMiiObj[i], false);

                if (mbFaceValid[i]) {
                    mpLayout->getAnim(i + 6)->initAnmFrame();
                } else {
                    mpLayout->getAnim(i + 21)->initAnmFrame();
                }
            }

            mPage = 0;
            mPrevPageNum = 0;
            mNextPageNum = PAGE_MAX;

            button = static_cast<Button*>(System::getScene(SCENE_BUTTON));
            button->animation(Button::IDANIM_ARROW_RIGHT_APPEAR);
            button->animation(Button::IDANIM_ARROW_LEFT_APPEAR);

            if (mMode == 0) {
                mState = STATE_COVER_NORMAL;
            } else if (mpFriendCache->getRegFriendNum() == 0) {
                mState = STATE_COVER_NORMAL;
            } else {
                mState = STATE_INIT;
            }

            switch (mMode) {
                case 0: {
                    mpLayout->getAnim(0)->play();
                    break;
                }
                case SCENE_ADD_WII:
                case SCENE_ADD_EMAIL: {
                    mpLayout->getAnim(2)->play();
                    mpDialogLayout->getAnim(0)->play();
                    break;
                }
            }
        }

        void Address::stt_cover_normal() {
            if (mDrag.mbDragging) {
                changePage_onDrag();
            } else {
                Button* button = static_cast<Button*>(System::getScene(SCENE_BUTTON));
                if (button->isActive()) {
                    button->update();
                }
            }

            if (mState == STATE_COVER_NORMAL) {
                if (System::getMasterController()->down(controller::BTN_NEXT_RIGHT)) {
                    snd::getSystem()->startSE("WIPL_SE_FL_PAGE_INC");
                    onNextPage();
                } else if (System::getMasterController()->down(controller::BTN_NEXT_LEFT)) {
                    snd::getSystem()->startSE("WIPL_SE_FL_PAGE_DEC");
                    onPreviousPage();
                }
            }
        }

        void Address::stt_cover_forward() {
            if (!mpLayout->getAnim(4)->isPlaying()) {
                mbCover = false;
                if (!mDrag.mbDragging) {
                    mState = STATE_NORMAL;
                } else {
                    mState = STATE_DRAG;
                }
            } else if (mDrag.mbDragging) {
                changePage_onDrag();
            }
        }

        static inline nw4r::math::_VEC2 negativeOffset(const nw4r::math::_VEC2& value) {
            f32 negativeY = -value.y;
            f32 negativeX = -value.x;
            nw4r::math::_VEC2 result = {negativeX, negativeY};
            return result;
        }

        void Address::stt_cover_backward() {
            if (!mpLayout->getAnim(4)->isPlaying()) {
                math::VEC2 offset = negativeOffset(sPageOffset);
                add_translate(mpLayout->FindPaneByName("N_note_base"), offset);
                mbCover = true;
                mNextPageNum++;
                mState = STATE_COVER_NORMAL;
            } else if (mDrag.mbDragging) {
                changePage_onDrag();
            }
        }

        void Address::stt_normal() {
            Button* button = static_cast<Button*>(System::getScene(SCENE_BUTTON));
            if (button->isActive()) {
                button->update();
            }

            if (mState == STATE_NORMAL) {
                mpGui->update();

                if (System::getMasterController()->down(controller::BTN_NEXT_RIGHT)) {
                    snd::getSystem()->startSE("WIPL_SE_FL_PAGE_INC");
                    onNextPage();
                } else if (System::getMasterController()->down(controller::BTN_NEXT_LEFT)) {
                    snd::getSystem()->startSE("WIPL_SE_FL_PAGE_DEC");
                    onPreviousPage();
                }
            }
        }

        void Address::stt_forward() {
            if (!mpLayout->getAnim(5)->isPlaying()) {
                mPrevPageNum++;
                if (!mDrag.mbDragging) {
                    mState = STATE_NORMAL;
                } else {
                    mState = STATE_DRAG;
                }
            } else if (mDrag.mbDragging) {
                changePage_onDrag();
            }
        }

        static inline nw4r::math::_VEC2 previousPageOffset() {
            f32 negativeY = -sPageOffset.y;
            f32 negativeX = -sPageOffset.x;
            nw4r::math::_VEC2 result;
            result.y = negativeY;
            result.x = negativeX;
            return result;
        }

        void Address::stt_backward() {
            if (!mpLayout->getAnim(5)->isPlaying()) {
                mNextPageNum++;
                math::VEC2 offset = previousPageOffset();
                add_translate(mpLayout->FindPaneByName("N_note_base"), offset);
                set_page_text("T_nmbr_b", mPage + 1);

                for (u32 i = 0; i < BTN_MAX; i++) {
                    set_friend(sTextNameB[i], i + mPage * BTN_MAX, i, mMiiObj[i], false);
                }

                if (!mDrag.mbDragging) {
                    mState = STATE_NORMAL;
                } else {
                    mState = STATE_DRAG;
                }
            } else if (mDrag.mbDragging) {
                changePage_onDrag();
            }
        }

        static inline nw4r::math::VEC2 loopPageOffset() {
            nw4r::math::VEC2 result;
            result.y = -sPageOffset.y;
            result.x = -sPageOffset.x;
            return result;
        }

        void Address::stt_loop_forward() {
            if (!mpLayout->getAnim(4)->isPlaying()) {
                math::VEC2 offset = loopPageOffset() * PAGE_MAX;
                add_translate(mpLayout->FindPaneByName("N_note_base"), offset);
                set_page_text("T_nmbr_b", mPage + 1);
                reset_gui(false);

                for (u32 i = 0; i < BTN_MAX; i++) {
                    set_friend(sTextNameB[i], i + mPage * BTN_MAX, i, mMiiObj[i], false);
                }

                mbCover = true;
                mNextPageNum = PAGE_MAX;
                mState = STATE_COVER_NORMAL;
            } else if (mDrag.mbDragging) {
                changePage_onDrag();
            }
        }

        void Address::stt_loop_backward() {
            if (!mpLayout->getAnim(4)->isPlaying()) {
                mbCover = false;
                mPrevPageNum = PAGE_MAX - 1;
                if (!mDrag.mbDragging) {
                    mState = STATE_NORMAL;
                } else {
                    mState = STATE_DRAG;
                }
            } else if (mDrag.mbDragging) {
                changePage_onDrag();
            }
        }

        void Address::stt_decide() {
            if (!mpLayout->getAnim(mSelectedButton + 16)->isPlaying() && !mpLayout->getAnim(mSelectedButton + 31)->isPlaying()) {
                reset_gui(true);

                switch (mMode) {
                    case 0: {
                        createChildScene(SCENE_ADDRESS_EDIT, this, NULL, NULL);
                        mpBackLayout->getAnim(0)->play();
                        mState = STATE_WAIT_CHILD_CST;
                        break;
                    }
                    case SCENE_ADD_WII:
                    case SCENE_ADD_EMAIL: {
                        LetterWriter* letterWriter = static_cast<LetterWriter*>(System::getScene(SCENE_LETTER_WRITER));
                        letterWriter->setFriendInfo(mpFriendCache->getInfo(mChosenFriend));
                        mpLayout->getAnim(3)->play();
                        mpDialogLayout->getAnim(1)->play();
                        mState = STATE_DONE;
                        break;
                    }
                }
            }
        }

        void Address::stt_drag() {
            mpGui->update();
            if (mState == STATE_DRAG) {
                changePage_onDrag();
            }
        }

        void Address::stt_release() {
            mpGui->init();

            for (int i = 0; i < BTN_MAX; i++) {
                if (mbFaceValid[i]) {
                    mpLayout->getAnim(i + 6)->initAnmFrame();
                } else {
                    mpLayout->getAnim(i + 21)->initAnmFrame();
                }

                mPointCount[i] = 0;
            }

            mpLayout->FindPaneByName("N_note_move")->SetVisible(false);

            if (mbCover) {
                mState = STATE_COVER_NORMAL;
            } else {
                mState = STATE_NORMAL;
            }
        }

        void Address::stt_wait_child_cst() {
            if (getChild() != NULL && !mpBackLayout->getAnim(0)->isPlaying()) {
                mState = STATE_WAIT_CHILD_DST;
                reset_gui(true);

                for (int i = 0; i < BTN_MAX; i++) {
                    mPointCount[i] = 0;
                }
            }
        }

        void Address::stt_wait_child_dst() {
            if (getChild() == NULL && System::getReservedScene() == NULL) {
                mpBackLayout->getAnim(1)->play();
                static_cast<Button*>(System::getScene(SCENE_BUTTON))->setEventHandler(this);
                mState = STATE_WAIT_CHILD_FADEOUT;
            }
        }

        void Address::stt_wait_child_fadeout() {
            if (!mpBackLayout->getAnim(1)->isPlaying()) {
                Button* button = static_cast<Button*>(System::getScene(SCENE_BUTTON));
                button->setText("T_CalAdd_R", MESG_ADDRESS_REGISTER);
                button->animation(Button::IDANIM_ARROW_RIGHT_APPEAR);
                button->animation(Button::IDANIM_ARROW_LEFT_APPEAR);

                if (mbCover) {
                    mState = STATE_COVER_NORMAL;
                } else {
                    mState = STATE_NORMAL;
                }
            }
        }

        void Address::stt_msg_net() {
            switch (System::getDialog()->getLastResult()) {
                case DialogWindow::RESULT_LEFT_BUTTON: {
                    if (mbCover) {
                        mState = STATE_COVER_NORMAL;
                    } else {
                        mState = STATE_NORMAL;
                    }

                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_ARROW_RIGHT_APPEAR);
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_ARROW_LEFT_APPEAR);
                    break;
                }
                case DialogWindow::RESULT_RIGHT_BUTTON: {
                    SCParentalControlsInfo pcInfo;
                    if (SCGetParentalControl(&pcInfo) && (pcInfo.enable & SC_PARENTAL_FLAG_ENABLED)) {
                        static_cast<Button*>(System::getScene(SCENE_BUTTON))->setEventHandler(NULL);
                        static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_DISAPPEAR_LEFT_AND_RIGHT_BUTTON);
                        createChildScene(SCENE_PARENTAL_DIALOG, this, NULL, (void*)1);
                        mbParentalOK = false;
                        mState = STATE_WAIT_PARENTAL;
                    } else {
                        System::getFader()->fadeOut();
                        reserveAllSceneDestruction(SCENE_SETTING, (void*)1);
                        mState = STATE_DONE;
                    }
                    break;
                }
            }
        }

        void Address::stt_wait_parental() {
            ParentalDialog* parental = static_cast<ParentalDialog*>(System::getScene(SCENE_PARENTAL_DIALOG));
            if (parental != NULL) {
                switch (parental->getResult()) {
                    case ParentalDialog::RESULT_SUCCESS: {
                        mbParentalOK = true;
                        mState = STATE_WAIT_PARENTAL_DST;
                        break;
                    }
                    case ParentalDialog::RESULT_OVER_ATTEMPTS:
                    case ParentalDialog::RESULT_CANCELLED: {
                        mbParentalOK = false;
                        mState = STATE_WAIT_PARENTAL_DST;
                        break;
                    }
                }
            }
        }

        void Address::stt_wait_parental_dst() {
            if (getChild() == NULL) {
                if (mbParentalOK) {
                    System::getFader()->fadeOut();
                    reserveAllSceneDestruction(SCENE_SETTING, (void*)1);
                    mState = STATE_DONE;
                } else {
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_APPEAR_LEFT_AND_RIGHT_BUTTON);
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->setEventHandler(this);

                    if (mbCover) {
                        mState = STATE_COVER_NORMAL;
                    } else {
                        mState = STATE_NORMAL;
                    }

                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_ARROW_RIGHT_APPEAR);
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_ARROW_LEFT_APPEAR);
                }
            }
        }

        void Address::stt_msg_wc() {
            switch (System::getDialog()->getLastResult()) {
                case DialogWindow::RESULT_LEFT_BUTTON: {
                    if (mbCover) {
                        mState = STATE_COVER_NORMAL;
                    } else {
                        mState = STATE_NORMAL;
                    }

                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_ARROW_RIGHT_APPEAR);
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_ARROW_LEFT_APPEAR);
                    break;
                }
                case DialogWindow::RESULT_RIGHT_BUTTON: {
                    SCParentalControlsInfo pcInfo;
                    if (SCGetParentalControl(&pcInfo) && (pcInfo.enable & SC_PARENTAL_FLAG_ENABLED)) {
                        static_cast<Button*>(System::getScene(SCENE_BUTTON))->setEventHandler(NULL);
                        static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_DISAPPEAR_LEFT_AND_RIGHT_BUTTON);
                        createChildScene(SCENE_PARENTAL_DIALOG, this, NULL, (void*)1);
                        mbParentalOK = false;
                        mState = STATE_WAIT_PARENTAL_WC;
                    } else {
                        System::getFader()->fadeOut();
                        reserveAllSceneDestruction(SCENE_SETTING, (void*)4);
                        mState = STATE_DONE;
                    }
                    break;
                }
            }
        }

        void Address::stt_wait_parental_wc() {
            ParentalDialog* parental = static_cast<ParentalDialog*>(System::getScene(SCENE_PARENTAL_DIALOG));
            if (parental != NULL) {
                switch (parental->getResult()) {
                    case ParentalDialog::RESULT_SUCCESS: {
                        mbParentalOK = true;
                        mState = STATE_WAIT_PARENTAL_DST_WC;
                        break;
                    }
                    case ParentalDialog::RESULT_OVER_ATTEMPTS:
                    case ParentalDialog::RESULT_CANCELLED: {
                        mbParentalOK = false;
                        mState = STATE_WAIT_PARENTAL_DST_WC;
                        break;
                    }
                }
            }
        }

        void Address::stt_wait_parental_dst_wc() {
            if (getChild() == NULL) {
                if (mbParentalOK) {
                    System::getFader()->fadeOut();
                    reserveAllSceneDestruction(SCENE_SETTING, (void*)4);
                    mState = STATE_DONE;
                } else {
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_APPEAR_LEFT_AND_RIGHT_BUTTON);
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->setEventHandler(this);

                    if (mbCover) {
                        mState = STATE_COVER_NORMAL;
                    } else {
                        mState = STATE_NORMAL;
                    }

                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_ARROW_RIGHT_APPEAR);
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_ARROW_LEFT_APPEAR);
                }
            }
        }

        void Address::stt_msg_nwc24_error() {
            switch (System::getDialog()->getLastResult()) {
                case DialogWindow::RESULT_BUTTON: {
                    if (mbCover) {
                        mState = STATE_COVER_NORMAL;
                    } else {
                        mState = STATE_NORMAL;
                    }

                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_ARROW_RIGHT_APPEAR);
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_ARROW_LEFT_APPEAR);
                    break;
                }
            }
        }

        void Address::stt_msg_fi_full() {
            switch (System::getDialog()->getLastResult()) {
                case DialogWindow::RESULT_BUTTON: {
                    if (mbCover) {
                        mState = STATE_COVER_NORMAL;
                    } else {
                        mState = STATE_NORMAL;
                    }

                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_ARROW_RIGHT_APPEAR);
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_ARROW_LEFT_APPEAR);
                    break;
                }
            }
        }

        void Address::stt_msg_parental() {
            switch (System::getDialog()->getLastResult()) {
                case DialogWindow::RESULT_BUTTON: {
                    if (mbCover) {
                        mState = STATE_COVER_NORMAL;
                    } else {
                        mState = STATE_NORMAL;
                    }

                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_ARROW_RIGHT_APPEAR);
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(Button::IDANIM_ARROW_LEFT_APPEAR);
                    break;
                }
            }
        }

        void Address::stt_msg_open_failure() {
            switch (System::getDialog()->getLastResult()) {
                case DialogWindow::RESULT_BUTTON: {
                    Button* button = static_cast<Button*>(System::getScene(SCENE_BUTTON));
                    MailAddressSelect* mailAddrSel = static_cast<MailAddressSelect*>(System::getScene(SCENE_MAIL_ADDRESS_SELECT));

                    switch (mMode) {
                        case 0: {
                            if (mailAddrSel != NULL) {
                                mailAddrSel->finishAddress();
                            }
                            button->reserveAnm(Button::IDANIM_DISAPPEAR_LEFT_AND_RIGHT_BUTTON);
                            button->reserveAnm(Button::IDANIM_APPEAR_LEFT_BUTTON);
                            break;
                        }
                        case SCENE_ADD_WII: {
                            button->reserveAnm(Button::IDANIM_DISAPPEAR_LEFT_BUTTON);
                            button->reserveAnm(Button::IDANIM_APPEAR_LEFT_BUTTON);
                            break;
                        }
                        case SCENE_ADD_EMAIL: {
                            button->reserveAnm(Button::IDANIM_DISAPPEAR_LEFT_BUTTON);
                            button->reserveText(0, MESG_CMN_BACK_ALT);
                            button->reserveText(1, 51);
                            button->reserveAnm(Button::IDANIM_APPEAR_LEFT_AND_RIGHT_BUTTON);
                            break;
                        }
                    }

                    button->animation(Button::IDANIM_ARROW_RIGHT_DISAPPEAR);
                    button->animation(Button::IDANIM_ARROW_LEFT_DISAPPEAR);
                    mState = STATE_DONE;
                    break;
                }
            }
        }

        void Address::stt_wait_dialog() {
            if (System::getDialog()->getLastResult() >= DialogWindow::RESULT_WAIT) {
                reset_gui(true);
                mState = STATE_NORMAL;
            }
        }

        void Address::add_translate(nw4r::lyt::Pane* pane, const math::VEC2& offset) {
            nw4r::ut::Rect rect;
            nw4r::ut::Rect rect4x3;

            System::getProjectionRect(&rect);
            System::getProjectionRect4x3(&rect4x3);

            nw4r::math::VEC3 trans;
            trans.x = pane->GetTranslate().x;
            trans.y = pane->GetTranslate().y;
            trans.z = pane->GetTranslate().z;
            trans.x += offset.x * rect4x3.GetWidth() / rect.GetWidth();
            trans.y += offset.y;
            pane->SetTranslate(trans);
        }

        void Address::set_friend(const char* paneName, u32 friendNo, u32 buttonNo, MiiObj& miiObj, bool bDrag) {
            wchar_t blank[1];
            blank[0] = 0;
            const wchar_t* name = blank;

            if (mpFriendCache->isThere(friendNo)) {
                const NWC24FriendInfo& info = mpFriendCache->getInfo(friendNo);
                name = (const wchar_t*)info.attr.name;

                bool bValid = info.attr.status == NWC24_FRIENDSTATUS_CONFIRMED;
                if (mMode == SCENE_ADD_EMAIL) {
                    bValid = bValid & (info.attr.type == NWC24_FRIENDTYPE_WII);
                }

                if (bDrag) {
                    if (bValid) {
                        mpLayout->getAnim(buttonNo + 36)->initAnmFrame(0.0f);
                    } else {
                        mpLayout->getAnim(buttonNo + 36)->initAnmFrame(1.0f);
                    }
                } else {
                    if (bValid) {
                        mpLayout->getAnim(buttonNo + 6)->initAnmFrame();
                    } else {
                        mpLayout->getAnim(buttonNo + 21)->initAnmFrame();
                    }
                    mbFaceValid[buttonNo] = bValid;
                }

                if (!mDrag.mbDragging || friendNo != mDrag.mButton + mDrag.mPage * BTN_MAX) {
                    miiObj.set(info.attr.fdId);
                }
            } else {
                if (bDrag) {
                    mpLayout->getAnim(buttonNo + 36)->initAnmFrame(0.0f);
                } else {
                    mbFaceValid[buttonNo] = false;
                    mpLayout->getAnim(buttonNo + 21)->initAnmFrame();
                }

                miiObj.reset();
            }

            if (!mDrag.mbDragging || friendNo != mDrag.mButton + mDrag.mPage * BTN_MAX) {
                set_textbox(paneName, name);
            } else {
                set_textbox(paneName, L"");
                miiObj.reset();
            }
        }

        void Address::set_page_text(const char* paneName, int page) {
            const wchar_t digits[10] = {L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9'};
            wchar_t text[6] = {0};

            int i = 0;
            if (page >= 10) {
                text[i++] = digits[page / 10];
            }
            text[i++] = digits[page % 10];
            text[i++] = L'/';
            text[i++] = digits[PAGE_MAX / 10];
            text[i++] = digits[PAGE_MAX % 10];
            text[i] = 0;

            set_textbox(paneName, text);
        }

        void Address::set_textbox(const char* paneName, const wchar_t* text) {
            nw4r::lyt::TextBox* textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpLayout->FindPaneByName(paneName));
            textBox->SetString(text, 0);
        }

        void Address::reset_friend() {
            for (u32 i = 0; i < BTN_MAX; i++) {
                set_friend(sTextNameB[i], i + mPage * BTN_MAX, i, mMiiObj[i], false);
            }
        }

        void Address::start_point_event(const char* paneName, controller::Interface* con) {
            int buttonNo = get_button_no(paneName);
            if (buttonNo != -1) {
                if (mMode == 0 || (mMode == SCENE_ADD_WII && is_selectable(buttonNo + mPage * BTN_MAX))) {
                    on_point_event(buttonNo, con);
                }
            }
        }

        void Address::start_left_event(const char* paneName) {
            int buttonNo = get_button_no(paneName);
            if (buttonNo != -1) {
                if (mMode == 0 || (mMode == SCENE_ADD_WII && is_selectable(buttonNo + mPage * BTN_MAX))) {
                    left_point_event(buttonNo);
                }
            }
        }

        void Address::start_trig_event(const char* paneName) {
            Button* button = static_cast<Button*>(System::getScene(SCENE_BUTTON));
            int buttonNo = get_button_no(paneName);

            switch (mState) {
                case STATE_NORMAL: {
                switch (mMode) {
                    case 0: {
                        if (buttonNo != -1 && is_selectable(buttonNo + mPage * BTN_MAX)) {
                            button->animation(Button::IDANIM_ARROW_RIGHT_DISAPPEAR);
                            button->animation(Button::IDANIM_ARROW_LEFT_DISAPPEAR);
                            button->animation(Button::IDANIM_DISAPPEAR_LEFT_AND_RIGHT_BUTTON);
                            button->reserveText(Button::TEXT_LEFT_BUTTON, MESG_CMN_BACK_ALT);
                            button->reserveAnm(Button::IDANIM_APPEAR_LEFT_BUTTON);
                            button->setEventHandler(NULL);

                            if (mbFaceValid[buttonNo]) {
                                mpLayout->getAnim(buttonNo + 16)->play();
                            } else {
                                mpLayout->getAnim(buttonNo + 31)->play();
                            }

                            mSelectedButton = buttonNo;
                            mChosenFriend = buttonNo + mPage * BTN_MAX;
                            snd::getSystem()->startSE("WIPL_SE_DECIDE");
                            mPointCount[buttonNo]++;
                            mState = STATE_DECIDE;
                        } else if (buttonNo != -1) {
                            mSelectedButton = buttonNo;
                            mChosenFriend = buttonNo + mPage * BTN_MAX;
                            entry_friend();
                        }
                        break;
                    }
                    case SCENE_ADD_WII:
                    case SCENE_ADD_EMAIL: {
                        if (buttonNo != -1 && is_selectable(buttonNo + mPage * BTN_MAX)) {
                            button->animation(Button::IDANIM_DISAPPEAR_LEFT_BUTTON);
                            button->reserveText(Button::TEXT_LEFT_BUTTON, MESG_CMN_QUIT);
                            button->reserveText(Button::TEXT_RIGHT_BUTTON, 51);
                            button->reserveAnm(Button::IDANIM_APPEAR_LEFT_AND_RIGHT_BUTTON);
                            button->animation(Button::IDANIM_ARROW_RIGHT_DISAPPEAR);
                            button->animation(Button::IDANIM_ARROW_LEFT_DISAPPEAR);

                            mpLayout->getAnim(buttonNo + 16)->play();

                            mSelectedButton = buttonNo;
                            mChosenFriend = buttonNo + mPage * BTN_MAX;
                            snd::getSystem()->startSE("WIPL_SE_DECIDE");
                            mState = STATE_DECIDE;
                        } else if (buttonNo != -1) {
                            u32 friendNo = buttonNo + mPage * BTN_MAX;
                            if (mpFriendCache->isThere(friendNo)) {
                                if (mMode == SCENE_ADD_WII) {
                                    System::getDialog()->callBtn1(87, MESG_CMN_OK);
                                } else if (mpFriendCache->getInfo(friendNo).attr.type == NWC24_FRIENDTYPE_WII) {
                                    System::getDialog()->callBtn1(87, MESG_CMN_OK);
                                } else {
                                    System::getDialog()->callBtn1(34, MESG_CMN_OK);
                                }

                                mState = STATE_WAIT_DIALOG;
                            }
                        }
                        break;
                    }
                }
                    break;
                }
            }
        }

        void Address::start_drag_event(const char* paneName, const controller::Interface* con) {
            int buttonNo = get_button_no(paneName);
            if (buttonNo == -1) {
                return;
            }
            if (con->getChannel() < 0) {
                return;
            }

            if (mState != STATE_NORMAL || mMode != 0) {
                return;
            }

            if (!mpFriendCache->isThere(buttonNo + mPage * BTN_MAX)) {
                return;
            }

            mDrag.mbDragging = true;
            mDrag.mChan = con->getChannel();

            if (con->isValidDpd()) {
                mDrag.mPos = System::getControllerManager()->getController(mDrag.mChan)->getDpdProjectionPos();
            } else {
                mDrag.mPos = nw4r::math::VEC2(0.0f, 0.0f);
            }

            mDrag.mPage = mPage;
            mDrag.mButton = buttonNo;
            mDrag.mNextCount = -1;
            mDrag.mPrevCount = -1;
            mDrag.unk_0x1C = 0;

            System::getPointer()->changeType(con->getChannel(), 1);
            static_cast<Button*>(System::getScene(SCENE_BUTTON))->disableBtn();

            wchar_t blank[2] = {0, 0};
            static_cast<nw4r::lyt::TextBox*>(mpLayout->FindPaneByName(sTextNameB[mDrag.mButton]))->SetString(blank, 0);

            nigaoe::Object* nigaoe = mMiiObj[buttonNo].mpNigaoe;
            if (nigaoe != NULL) {
                nw4r::lyt::Pane* miiPane = mpLayout->FindPaneByName("mii_move");
                miiPane->SetVisible(true);

                mDragTexObj = nigaoe->getIconTexture();
                memcpy(mpWork, nigaoe->getIconImage(), 0x2D20);
                GXInitTexObj(&mDragTexObj, mpWork, 76, 76, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, GX_FALSE);
                miiPane->GetMaterial()->SetTexture(GX_TEXMAP0, mDragTexObj);

                mMiiObj[buttonNo].reset();
            } else {
                mpLayout->FindPaneByName("mii_move")->SetVisible(false);
            }

            mpGui->init();

            for (int i = 0; i < BTN_MAX; i++) {
                mPointCount[i] = 0;

                if (mbFaceValid[i]) {
                    mpLayout->getAnim(i + 6)->initAnmFrame();
                } else {
                    mpLayout->getAnim(i + 21)->initAnmFrame();
                }
            }

            movePane_onDrag();

            snd::getSystem()->startSEwithPos("WIPL_SE_CH_HOLD", mDrag.mPos.x);

            mState = STATE_DRAG;
        }

        void Address::start_drag_point_event(const char* paneName, controller::Interface* con) {
            int buttonNo = get_button_no(paneName);
            if (buttonNo != -1 && isReleasableArea(mPage, buttonNo)) {
                on_point_event(buttonNo, con);
                mDrag.mbDragging = true;
            }
        }

        void Address::start_drag_left_event(const char* paneName) {
            int buttonNo = get_button_no(paneName);
            if (buttonNo != -1) {
                left_point_event(buttonNo);
                mDrag.mbDragging = true;
            }
        }

        void Address::start_release_event(const char* paneName) {
            Button* button = static_cast<Button*>(System::getScene(SCENE_BUTTON));

            int buttonNo = -1;
            if (paneName != NULL) {
                buttonNo = get_button_no(paneName);
                if (buttonNo == -1) {
                    buttonNo = get_button_space_no(paneName);
                }
            }

            switch (mMode) {
                case 0: {
                    if (isReleasableArea(mPage, buttonNo)) {
                        u32 friendNo = buttonNo + mPage * BTN_MAX;
                        u32 dragFriendNo = mDrag.mButton + mDrag.mPage * BTN_MAX;
                        mSelectedButton = buttonNo;
                        mChosenFriend = friendNo;
                        if (friendNo != dragFriendNo) {
                            mpFriendCache->swap(friendNo, dragFriendNo);
                        }
                        snd::getSystem()->startSEwithPos("WIPL_SE_CH_SET", mDrag.mPos.x);
                    } else {
                        snd::getSystem()->startSEwithPos("WIPL_SE_CH_NOT_MOVE", mDrag.mPos.x);
                    }

                    System::getPointer()->changeType(mDrag.mChan, 0);
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->enableBtn();

                    mpLayout->FindPaneByName(sTextNameB[mDrag.mButton])->SetVisible(true);

                    mDrag.mbDragging = false;
                    mState = STATE_RELEASE;
                    reset_friend();
                    break;
                }
            }
        }

        void Address::on_point_event(int buttonNo, controller::Interface* con) {
            if (mPointCount[buttonNo] == 0) {
                if (mbFaceValid[buttonNo]) {
                    mpLayout->getAnim(buttonNo + 6)->play();
                } else {
                    mpLayout->getAnim(buttonNo + 21)->play();
                }

                snd::getSystem()->startSE("WIPL_SE_BT_TARGETTING");
                con->rumble(1);
            }

            mPointCount[buttonNo]++;
        }

        void Address::left_point_event(int buttonNo) {
            if (mPointCount[buttonNo] == 1) {
                if (mbFaceValid[buttonNo]) {
                    mpLayout->getAnim(buttonNo + 11)->play();
                } else {
                    mpLayout->getAnim(buttonNo + 26)->play();
                }
            }

            if (mPointCount[buttonNo] > 0) {
                mPointCount[buttonNo]--;
            }
        }

        int Address::get_button_no(const char* paneName) {
            int ret = -1;
            for (int i = 0; i < BTN_MAX; i++) {
                if (strcmp(sButtonName[i], paneName) == 0) {
                    ret = i;
                    break;
                }
            }

            return ret;
        }

        int Address::get_button_space_no(const char* paneName) {
            int ret = -1;
            for (int i = 0; i < BTN_SPACE_MAX; i++) {
                if (strcmp(sButtonSpaceName[i], paneName) == 0) {
                    ret = i;
                    break;
                }
            }

            return ret;
        }

        void Address::reset_gui(bool bKeepPointed) {
            mpGui->init();

            for (int i = 0; i < BTN_MAX; i++) {
                mpLayout->getAnim(i + 6)->initAnmFrame();
                mpLayout->getAnim(i + 6)->calc();
                mpLayout->getAnim(i + 11)->initAnmFrame();
                mpLayout->getAnim(i + 11)->calc();
                mpLayout->getAnim(i + 16)->initAnmFrame();
                mpLayout->getAnim(i + 16)->calc();
                mpLayout->getAnim(i + 21)->initAnmFrame();
                mpLayout->getAnim(i + 21)->calc();
                mpLayout->getAnim(i + 26)->initAnmFrame();
                mpLayout->getAnim(i + 26)->calc();
                mpLayout->getAnim(i + 31)->initAnmFrame();
                mpLayout->getAnim(i + 31)->calc();

                if (mPointCount[i] != 0 && bKeepPointed) {
                    if (mbFaceValid[i]) {
                        mpLayout->getAnim(i + 11)->play();
                    } else {
                        mpLayout->getAnim(i + 26)->play();
                    }
                } else {
                    if (mbFaceValid[i]) {
                        mpLayout->getAnim(i + 6)->initAnmFrame();
                        mpLayout->getAnim(i + 6)->calc();
                    } else {
                        mpLayout->getAnim(i + 21)->initAnmFrame();
                        mpLayout->getAnim(i + 21)->calc();
                    }
                }

                mPointCount[i] = 0;
            }
        }

        BOOL Address::is_selectable(u32 friendNo) {
            switch (mMode) {
                case 0: {
                    return mpFriendCache->isThere(friendNo);
                }
                case SCENE_ADD_WII: {
                    if (mpFriendCache->isThere(friendNo)) {
                        return mpFriendCache->getInfo(friendNo).attr.status == NWC24_FRIENDSTATUS_CONFIRMED;
                    }
                    return FALSE;
                }
                case SCENE_ADD_EMAIL: {
                    if (mpFriendCache->isThere(friendNo)) {
                        const NWC24FriendInfo& info = mpFriendCache->getInfo(friendNo);
                        BOOL ret = FALSE;
                        if (info.attr.status == NWC24_FRIENDSTATUS_CONFIRMED && info.attr.type == NWC24_FRIENDTYPE_WII) {
                            ret = TRUE;
                        }
                        return ret;
                    }
                    return FALSE;
                }
            }

            return FALSE;
        }

        void Address::onEventDerived(u32 compId, u32 event, const controller::Interface* con) {
            const char* paneName = static_cast<gui::PaneComponent*>(mpManager->getComponent(compId))->getPane()->GetName();

            switch (event) {
                case ::gui::EventHandler::ON_TRIG: {
                    if (con == NULL) {
                        break;
                    }

                    if (con->downTrg(controller::BTN_INTERACT)) {
                        Button* button = static_cast<Button*>(System::getScene(SCENE_BUTTON));
                        if (mState != STATE_COVER_NORMAL && mState != STATE_NORMAL) {
                            break;
                        }

                        if (Button::cmpButtonName(paneName, Button::BTN_EXIT) == 0) {
                            MailAddressSelect* mailAddrSel = static_cast<MailAddressSelect*>(System::getScene(SCENE_MAIL_ADDRESS_SELECT));
                            button->animation(Button::IDANIM_SELECT_CALENDAR_EXIT);

                            switch (mMode) {
                                case 0: {
                                    if (mailAddrSel != NULL) {
                                        mailAddrSel->finishAddress();
                                    }
                                    mpLayout->getAnim(1)->play();
                                    button->reserveAnm(Button::IDANIM_DISAPPEAR_LEFT_AND_RIGHT_BUTTON);
                                    button->reserveAnm(Button::IDANIM_APPEAR_LEFT_BUTTON);
                                    break;
                                }
                                case SCENE_ADD_WII: {
                                    mpLayout->getAnim(3)->play();
                                    mpDialogLayout->getAnim(1)->play();
                                    button->reserveAnm(Button::IDANIM_DISAPPEAR_LEFT_BUTTON);
                                    button->reserveAnm(Button::IDANIM_APPEAR_LEFT_BUTTON);
                                    break;
                                }
                                case SCENE_ADD_EMAIL: {
                                    mpLayout->getAnim(3)->play();
                                    mpDialogLayout->getAnim(1)->play();
                                    button->reserveAnm(Button::IDANIM_DISAPPEAR_LEFT_BUTTON);
                                    button->reserveText(Button::TEXT_LEFT_BUTTON, MESG_CMN_BACK_ALT);
                                    button->reserveText(Button::TEXT_RIGHT_BUTTON, 51);
                                    button->reserveAnm(Button::IDANIM_APPEAR_LEFT_AND_RIGHT_BUTTON);
                                    break;
                                }
                            }

                            button->animation(Button::IDANIM_ARROW_RIGHT_DISAPPEAR);
                            button->animation(Button::IDANIM_ARROW_LEFT_DISAPPEAR);
                            snd::getSystem()->startSE("WIPL_SE_CANCEL");
                            mState = STATE_DONE;
                        } else if (Button::cmpButtonName(paneName, Button::BTN_CREATE_R_BUTTON) == 0) {
                            mChosenFriend = -1;
                            entry_friend();
                        } else if (Button::cmpButtonName(paneName, Button::BTN_ARROW_RIGHT) == 0) {
                            button->animation(Button::IDANIM_ARROW_RIGHT_SELECT);
                            snd::getSystem()->startSE("WIPL_SE_FL_PAGE_INC");
                            onNextPage();
                        } else if (Button::cmpButtonName(paneName, Button::BTN_ARROW_LEFT) == 0) {
                            button->animation(Button::IDANIM_ARROW_LEFT_SELECT);
                            snd::getSystem()->startSE("WIPL_SE_FL_PAGE_DEC");
                            onPreviousPage();
                        }
                        break;
                    }
                    // fallthrough
                }
                case ::gui::EventHandler::ON_POINT: {
                    if (mDrag.mbDragging && (con == NULL || con == System::getControllerManager()->getController(mDrag.mChan))) {
                        if (Button::cmpButtonName(paneName, Button::BTN_ARROW_LEFT) == 0) {
                            if (mDrag.mPrevCount < 0) {
                                mDrag.mPrevCount = 0;
                            }
                        } else if (Button::cmpButtonName(paneName, Button::BTN_ARROW_RIGHT) == 0) {
                            if (mDrag.mNextCount < 0) {
                                mDrag.mNextCount = 0;
                            }
                        }
                    }
                    break;
                }
                case ::gui::EventHandler::ON_LEFT: {
                    if (mDrag.mbDragging && (con == NULL || con == System::getControllerManager()->getController(mDrag.mChan))) {
                        if (Button::cmpButtonName(paneName, Button::BTN_ARROW_LEFT) == 0) {
                            mDrag.mPrevCount = -1;
                        } else if (Button::cmpButtonName(paneName, Button::BTN_ARROW_RIGHT) == 0) {
                            mDrag.mNextCount = -1;
                        }
                    }
                    break;
                }
            }
        }

        void Address::onNextPage() {
            switch (mState) {
                case STATE_NORMAL:
                case STATE_DRAG: {
                    if (mPage < PAGE_MAX - 1) {
                        mPage++;
                        mNextPageNum--;
                        add_translate(mpLayout->FindPaneByName("N_note_base"), sPageOffset);
                        mpLayout->getAnim(5)->setAnmType(0);
                        mpLayout->getAnim(5)->play();
                        set_page_text("T_nmbr_b", mPage + 1);
                        set_page_text("T_nmbr_c", mPage);
                        reset_gui(false);

                        for (u32 i = 0; i < BTN_MAX; i++) {
                            set_friend(sTextNameB[i], i + mPage * BTN_MAX, i, mMiiObj[i], false);
                            set_friend(sTextNameC[i], i + (mPage - 1) * BTN_MAX, i, mNextMiiObj[i], true);
                        }

                        mState = STATE_FORWARD;
                    } else {
                        mPage = 0;
                        mPrevPageNum = 0;
                        mbCover = true;
                        mpLayout->getAnim(4)->setAnmType(1);
                        mpLayout->getAnim(4)->play();
                        reset_gui(true);
                        mState = STATE_LOOP_FORWARD;
                    }
                    break;
                }
                case STATE_INIT:
                case STATE_COVER_NORMAL: {
                    mNextPageNum--;
                    add_translate(mpLayout->FindPaneByName("N_note_base"), sPageOffset);
                    mpLayout->getAnim(4)->setAnmType(0);
                    mpLayout->getAnim(4)->play();
                    reset_gui(true);

                    for (u32 i = 0; i < BTN_MAX; i++) {
                        set_friend(sTextNameB[i], i + mPage * BTN_MAX, i, mMiiObj[i], false);
                    }

                    mState = STATE_COVER_FORWARD;
                    break;
                }
            }
        }

        void Address::onPreviousPage() {
            switch (mState) {
                case STATE_NORMAL:
                case STATE_DRAG: {
                    if (mPage > 0) {
                        mPage--;
                        mPrevPageNum--;
                        mpLayout->getAnim(5)->setAnmType(1);
                        mpLayout->getAnim(5)->play();
                        set_page_text("T_nmbr_c", mPage + 1);
                        reset_gui(true);

                        for (u32 i = 0; i < BTN_MAX; i++) {
                            set_friend(sTextNameC[i], i + mPage * BTN_MAX, i, mNextMiiObj[i], true);
                        }

                        mState = STATE_BACKWARD;
                    } else {
                        mpLayout->getAnim(4)->setAnmType(1);
                        mpLayout->getAnim(4)->play();
                        reset_gui(true);
                        mState = STATE_COVER_BACKWARD;
                    }
                    break;
                }
                case STATE_COVER_NORMAL: {
                    mPage = PAGE_MAX - 1;
                    mNextPageNum = 0;
                    mbCover = false;
                    math::VEC2 offset;
                    offset.y = sPageOffset.y * PAGE_MAX;
                    offset.x = sPageOffset.x * PAGE_MAX;
                    add_translate(mpLayout->FindPaneByName("N_note_base"), math::VEC2(offset));
                    mpLayout->getAnim(4)->setAnmType(0);
                    mpLayout->getAnim(4)->play();
                    set_page_text("T_nmbr_b", mPage + 1);
                    reset_gui(false);

                    for (u32 i = 0; i < BTN_MAX; i++) {
                        set_friend(sTextNameB[i], i + mPage * BTN_MAX, i, mMiiObj[i], false);
                    }

                    mState = STATE_LOOP_BACKWARD;
                    break;
                }
            }
        }

        void Address::set_err_msg(wchar_t* errMsg, u32 errMsgLen, NWC24Err err) {
            memset(errMsg, 0, errMsgLen * sizeof(wchar_t));
            union MessageValue {
                const wchar_t* text;
                u32 id;
            } message;
            message.text = System::getMessage(MESG_ERROR_CODE);
            wcsncat(errMsg, message.text, errMsgLen - wcslen(errMsg));
||||||| parent of f3413243 (sceneleft: iplAddress set_err_msg/movePane_onDrag decodes, SDChannelSelect static setEventHandler)
            wcsncat(errMsg, System::getMessage(MESG_ERROR_CODE), errMsgLen - wcslen(errMsg));
            u32 msgId = MESG_ERROR_CODE;

            wchar_t errCode[32];
            memset(errCode, 0, sizeof(errCode));
            swprintf(errCode, ARRAY_LENGTH(errCode), L"%06d\n", System::getNwc24Manager()->getErrCode());
            wcsncat(errMsg, errCode, errMsgLen - wcslen(errMsg));

            switch (err) {
                case NWC24_ERR_NETWORK: {
                    message.id = MESG_ERROR_NWC24_NETWORK;
                    break;
                }
                case NWC24_ERR_SERVER:
                case NWC24_ERR_FULL: {
                    message.id = MESG_ERROR_NWC24_SERVER;
                    break;
                }
                default: {
                    message.id = reinterpret_cast<u32>(message.text);
                    break;
                }
            }

            message.text = System::getMessage(message.id);
            wcsncat(errMsg, message.text, errMsgLen - wcslen(errMsg));
        }

        void Address::entry_friend() {
            if (mMode != 0) {
                return;
            }

            Button* button = static_cast<Button*>(System::getScene(SCENE_BUTTON));

            SCParentalControlsInfo pcInfo;
            BOOL bGotParental = SCGetParentalControl(&pcInfo);
            u32 regFriendNum = mpFriendCache->getRegFriendNum();

            snd::getSystem()->startSE("WIPL_SE_DECIDE");

            if (mChosenFriend == -1) {
                button->animation(Button::IDANIM_SELECT_CREATE_R);
            }

            if (!ncd::NCDSetting::getConnectEnableFlag()) {
                System::getDialog()->callBtn2(325, MESG_NETWORK_SETTINGS_BTN, MESG_CMN_QUIT);
                mState = STATE_MSG_NET;
            } else if (!(SCGetWCFlags() & SC_WC_FLAGS_ENABLED)) {
                System::getDialog()->callBtn2(MESG_NETWORK_NO_WC24_CONFIG, MESG_NETWORK_SETTINGS_BTN, MESG_CMN_QUIT);
                mState = STATE_MSG_WC;
            } else if (bGotParental && (pcInfo.enable & SC_PARENTAL_FLAG_ENABLED) && (SCGetNetContentRestrictions() & 2)) {
                System::getDialog()->callBtn1(MESG_NETWORK_PARENTAL_RESTRICT, MESG_CMN_OK);
                mState = STATE_MSG_PARENTAL;
            } else if (mpFriendCache->check() == NWC24_ERR_NETWORK || mpFriendCache->getLastErr() == NWC24_ERR_SERVER ||
                       mpFriendCache->getLastErr() == NWC24_ERR_FULL) {
                wchar_t errMsg[0x400] = {0};
                set_err_msg(errMsg, ARRAY_LENGTH(errMsg), (NWC24Err)mpFriendCache->getLastErr());
                System::getDialog()->callBtn1(errMsg, MESG_CMN_OK);
                mState = STATE_MSG_NWC24_ERROR;
            } else if (regFriendNum >= FriendListCache::FRIEND_MAX) {
                System::getDialog()->callBtn1(80, MESG_CMN_OK);
                mState = STATE_MSG_FI_FULL;
            } else {
                createChildScene(SCENE_ADDRESS_ADD_SELECT, this, NULL, NULL);
                button->reserveAnm(Button::IDANIM_DISAPPEAR_LEFT_AND_RIGHT_BUTTON);
                button->reserveText(Button::TEXT_LEFT_BUTTON, MESG_CMN_BACK_ALT);
                button->reserveAnm(Button::IDANIM_APPEAR_LEFT_BUTTON);
                button->setEventHandler(NULL);
                mpBackLayout->getAnim(0)->play();
                mState = STATE_WAIT_CHILD_CST;
            }

            button->animation(Button::IDANIM_ARROW_RIGHT_DISAPPEAR);
            button->animation(Button::IDANIM_ARROW_LEFT_DISAPPEAR);
        }

        bool Address::isReleasableArea(int page, int buttonNo) {
            if (page < 0 || page >= PAGE_MAX) {
                return false;
            }

            if (mbCover) {
                return false;
            }

            if (buttonNo < 0 || buttonNo >= BTN_MAX) {
                return false;
            }

            if (page == mDrag.mPage && buttonNo == mDrag.mButton) {
                return true;
            }

            if (mpFriendCache->isThere(buttonNo + page * BTN_MAX)) {
                return false;
            }

            return mDrag.mbDragging == true;
        }

        void Address::changePage_onDrag() {
            Button* button = static_cast<Button*>(System::getScene(SCENE_BUTTON));
            if (button->isActive()) {
                button->update();
            }

            if (mState == STATE_DRAG || mState == STATE_COVER_NORMAL) {
                if (System::getControllerManager()->getController(mDrag.mChan) == NULL ||
                    !System::getControllerManager()->getController(mDrag.mChan)->pinch()) {
                    mDrag.mbDragging = true;
                    start_release_event(NULL);
                    return;
                }
            }

            set_textbox("T_name_move", (const wchar_t*)mpFriendCache->getInfo(mDrag.mButton + mDrag.mPage * BTN_MAX).attr.name);

            math::VEC2 pos = System::getControllerManager()->getController(mDrag.mChan)->getDpdProjectionPos();

            if (System::getControllerManager()->getController(mDrag.mChan) != NULL &&
                System::getControllerManager()->getController(mDrag.mChan)->isValidDpd()) {
                nw4r::math::VEC2 move(pos.x - mDrag.mPos.x, pos.y - mDrag.mPos.y);
                snd::getSystem()->holdSEwithPosDis("WIPL_SE_CH_DRAG", pos.x, nw4r::math::FSqrt(nw4r::math::VEC2LenSq(&move)));
                mDrag.mPos = pos;
            }

            nw4r::ut::Rect rect;
            nw4r::ut::Rect rect4x3;
            System::getProjectionRect(&rect);
            System::getProjectionRect4x3(&rect4x3);

            pos.x *= rect4x3.GetWidth() / rect.GetWidth();
            pos.x += mDragOffsetX;
            pos.y = -pos.y;

            nw4r::lyt::Pane* movePane = mpLayout->FindPaneByName("N_note_move");
            movePane->SetTranslate(pos);
            movePane->SetVisible(true);

            if (mDrag.mPrevCount >= 0) {
                mDrag.mPrevCount++;
            }
            if (mDrag.mNextCount >= 0) {
                mDrag.mNextCount++;
            }

            if (mDrag.mPrevCount >= 30) {
                button->animation(Button::IDANIM_ARROW_LEFT_SELECT);
                snd::getSystem()->startSE("WIPL_SE_FL_PAGE_DEC");
                onPreviousPage();
                mDrag.mPrevCount = 0;
                mDrag.mNextCount = -1;
            } else if (mDrag.mNextCount >= 30) {
                button->animation(Button::IDANIM_ARROW_RIGHT_SELECT);
                snd::getSystem()->startSE("WIPL_SE_FL_PAGE_INC");
                onNextPage();
                mDrag.mPrevCount = -1;
                mDrag.mNextCount = 0;
            }
        }

        void Address::movePane_onDrag() {
            nw4r::math::VEC3 baseTrans = mpLayout->FindPaneByName("N_base_move")->GetTranslate();
            math::VEC2 pos = System::getControllerManager()->getController(mDrag.mChan)->getDpdProjectionPos();
            nw4r::lyt::TextBox* textBox = static_cast<nw4r::lyt::TextBox*>(mpLayout->FindPaneByName("T_name_move"));
            const NWC24FriendInfo& info = mpFriendCache->getInfo(mDrag.mButton + mDrag.mPage * BTN_MAX);

            f32 width = 0.0f;
            const u16* name;
            if (textBox != NULL && (name = info.attr.name) != NULL) {
                textBox->GetFont()->GetWidth();
                for (; *name != 0; name++) {
                    width += textBox->GetFont()->GetCharWidth(*name);
                }
            }
            width += 0.01f;

            nw4r::ut::Rect rect;
            nw4r::ut::Rect rect4x3;
            System::getProjectionRect(&rect);
            System::getProjectionRect4x3(&rect4x3);

            if (baseTrans.x + width < pos.x) {
                mDragOffsetX = -((baseTrans.x + width) * (rect4x3.GetWidth() / rect.GetWidth()));
            } else {
                pos.x *= rect4x3.GetWidth() / rect.GetWidth();
                mDragOffsetX = -pos.x;
                mDragOffsetX += (mDrag.mPage * sPageOffset.x) * (rect4x3.GetWidth() / rect.GetWidth());
            }
        }

        Address::MiiObj::MiiObj() : mpNigaoe(NULL) {}

        Address::MiiObj::~MiiObj() {
            if (mpNigaoe != NULL) {
                delete mpNigaoe;
            }
        }

        void Address::MiiObj::init(nw4r::lyt::Pane* pane) {
            mpMaterial = pane->GetMaterial();
            mpMaterial->GetTexture(&mTexObj, GX_TEXMAP0);
        }

        void Address::MiiObj::set(u64 fdId) {
            RFLCreateID createId;
            u16 index;

            memcpy(&createId, &fdId, sizeof(RFLCreateID));
            if (RFLSearchOfficialData(&createId, &index)) {
                System::getMiiManager()->create(System::getMem2App(), 76, 76, (s16)index, create_callback, this);
            } else {
                reset();
            }
        }

        void Address::MiiObj::reset() {
            if (mpNigaoe != NULL) {
                mpMaterial->SetTexture(GX_TEXMAP0, mTexObj);
                delete mpNigaoe;
                mpNigaoe = NULL;
            }
        }

        void Address::MiiObj::create_callback(nigaoe::Object* object, void* work) {
            MiiObj* miiObj = static_cast<MiiObj*>(work);

            if (miiObj->mpNigaoe != NULL) {
                delete miiObj->mpNigaoe;
            }

            miiObj->mpNigaoe = object;
            miiObj->mpMaterial->SetTexture(GX_TEXMAP0, object->getIconTexture());
        }

        void AddressEvent::onEvent(u32 compId, u32 event, void* data) {
            const char* paneName = static_cast<gui::PaneComponent*>(mpManager->getComponent(compId))->getPane()->GetName();
            controller::Interface* con = static_cast<controller::Interface*>(data);

            switch (event) {
                case ::gui::EventHandler::ON_POINT: {
                    if (con != NULL) {
                        if (mpInstance->mDrag.mbDragging) {
                            if (con == NULL || con == System::getControllerManager()->getController(mpInstance->mDrag.mChan)) {
                                mpInstance->start_drag_point_event(paneName, con);
                            }
                        } else {
                            if (paneName[0] == 'B' && mTrigChan == con->getChannel()) {
                                mTrigChan = -1;
                            }
                            mpInstance->start_point_event(paneName, con);
                        }
                    }
                    break;
                }
                case ::gui::EventHandler::ON_LEFT: {
                    if (mpInstance->mDrag.mbDragging) {
                        if (con == NULL || con == System::getControllerManager()->getController(mpInstance->mDrag.mChan)) {
                            mpInstance->start_drag_left_event(paneName);
                        }
                    } else {
                        mpInstance->start_left_event(paneName);
                    }
                    break;
                }
                case ::gui::EventHandler::ON_DRAG: {
                    if (mpInstance->mState == Address::STATE_NORMAL && con != NULL && con->decide() && mTrigChan >= 0) {
                        mpInstance->start_trig_event(paneName);
                    }
                    break;
                }
                case ::gui::EventHandler::ON_TRIG: {
                    if (mpInstance->mState == Address::STATE_NORMAL && con != NULL) {
                        mTrigChan = con->getChannel();
                        if (con->pinchTrg()) {
                            mpInstance->start_drag_event(paneName, con);
                        }
                    }
                    break;
                }
                case ::gui::EventHandler::ON_RELEASE: {
                    if (mpInstance->mDrag.mbDragging &&
                        (con == NULL || con == System::getControllerManager()->getController(mpInstance->mDrag.mChan)) && !con->pinch()) {
                        mpInstance->start_release_event(paneName);
                    }
                    break;
                }
            }
        }

        BOOL FriendListCache::init() {
            nwc24::Manager* manager = System::getNwc24Manager();
            if (!manager->open()) {
                return FALSE;
            }

            manager->getMyUserId(&mMyUserId);

            u32 friendNum;
            manager->getNumFriendInfos(&friendNum);
            manager->getNumRegFriendInfos(&mRegFriendNum);

            for (u32 i = 0; i < FRIEND_MAX; i++) {
                mbThere[i] = manager->isFriendInfoThere(i);
                if (mbThere[i]) {
                    manager->readFriendInfo(&mInfos[i], i);
                }
            }

            mErrCode = 0;
            mbOpened = true;

            return TRUE;
        }

        void FriendListCache::fin() {
            if (mbOpened) {
                System::getNwc24Manager()->close();
            }
        }

        void FriendListCache::add(u32 index, const NWC24FriendInfo& info) {
            memcpy(&mInfos[index], &info, sizeof(NWC24FriendInfo));
            mbThere[index] = true;
            mRegFriendNum++;
            System::getNwc24Manager()->writeFriendInfo(&mInfos[index], index);
        }

        void FriendListCache::update(u32 index, const wchar_t* name, u64 fdId) {
            mInfos[index].attr.fdId = fdId;
            memset(mInfos[index].attr.name, 0, sizeof(mInfos[index].attr.name));
            wcsncpy((wchar_t*)mInfos[index].attr.name, name, 10);
            System::getNwc24Manager()->updateFriendInfo(&mInfos[index], index);
        }

        void FriendListCache::del(u32 index) {
            mbThere[index] = false;
            mRegFriendNum--;
            System::getNwc24Manager()->deleteFriendInfo(index);
        }

        void FriendListCache::swap(u32 index1, u32 index2) {
            NWC24FriendInfo temp ATTRIBUTE_ALIGN(32);

            memcpy(&temp, &mInfos[index1], sizeof(NWC24FriendInfo));
            memcpy(&mInfos[index1], &mInfos[index2], sizeof(NWC24FriendInfo));
            memcpy(&mInfos[index2], &temp, sizeof(NWC24FriendInfo));

            u8 bThere = mbThere[index1];
            mbThere[index1] = mbThere[index2];
            mbThere[index2] = bThere;

            System::getNwc24Manager()->swapFriendInfo(index1, index2);
        }

        BOOL FriendListCache::isValidId(const NWC24UserId& userId) {
            return System::getNwc24Manager()->checkUserId(userId);
        }

        BOOL FriendListCache::isDupId(const NWC24UserId& userId) {
            for (u32 i = 0; i < FRIEND_MAX; i++) {
                if (mbThere[i] && mInfos[i].attr.type == NWC24_FRIENDTYPE_WII && userId == getInfo(i).addr.wiiId) {
                    return TRUE;
                }
            }

            return FALSE;
        }

        BOOL FriendListCache::isDupMail(const char* mailAddr) {
            for (int i = 0; i < FRIEND_MAX; i++) {
                if (mbThere[i] && getInfo(i).attr.type == NWC24_FRIENDTYPE_EMAIL && strcmp(getInfo(i).addr.mailAddr, mailAddr) == 0) {
                    return TRUE;
                }
            }

            return FALSE;
        }

        void FriendListCache::sendRegisterMail(u32 index) {
            const NWC24FriendInfo& info = getInfo(index);
            nwc24::Manager* manager = System::getNwc24Manager();

            NWC24MsgObj msgObj;
            manager->initMsgObj(&msgObj, NWC24_MSGTYPE_PUBLIC);
            manager->setMsgToAddr(&msgObj, info.addr.mailAddr, strlen(info.addr.mailAddr));

            const wchar_t* subject = System::getMessage(385);

            wchar_t text[0x400];
            wcscpy(text, System::getMessage(386));

            if (mMyUserId != 1234567890123456ULL) {
                wchar_t idStr[17];
                const wchar_t* idPattern = L"1234567890123456";
                swprintf(idStr, ARRAY_LENGTH(idStr), L"%016lld", mMyUserId);

                wchar_t* pos;
                while ((pos = wcsstr(text, idPattern)) != NULL) {
                    for (int i = 0; i < 16; i++) {
                        pos[i] = idStr[i];
                    }
                }
            }

            memset(mSendWork, 0, sizeof(mSendWork));
            manager->setMsgSubjectAndTextPublic(&msgObj, (const u16*)subject, wcslen(subject), (const u16*)text, wcslen(text), mSendWork,
                                                sizeof(mSendWork));
            manager->commitMsg(&msgObj);
        }

        s32 FriendListCache::check() {
            return mErrCode = System::getNwc24Manager()->check(1);
        }

        s32 FriendListCache::getErrCode() const {
            return System::getNwc24Manager()->getErrCode();
        }
    }  // namespace scene
}  // namespace ipl
