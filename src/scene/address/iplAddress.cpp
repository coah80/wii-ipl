#include "scene/address/iplAddress.h"

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cwchar>
#include <cstdarg>

#include <revolution.h>
#include <revolution/sc.h>
#include <revolution/nwc24.h>

#include <nw4r/lyt/textBox.h>

#include "iplSceneUI.h"

#include "scene/board/iplBoard.h"
#include "scene/button/iplButton.h"
#include "scene/letterWriter/iplLetterWriter.h"
#include "scene/mailAddSel/iplMailAddressSelect.h"
#include "scene/parentalDialog/iplParentalDialog.h"
#include "scene/setting/iplNCDSetting.h"

#include "iplSystem.h"
#include "iplSound.h"

#include "system/iplNigaoe.h"
#include "system/iplPointer.h"

#include "utility/iplCharacterCode.h"
#include "utility/iplGraphics.h"

namespace ipl {
    namespace scene {
        namespace {
            static const char* sTextNameB[5] = {
                "T_name_b_00",
                "T_name_b_01",
                "T_name_b_02",
                "T_name_b_03",
                "T_name_b_04",
            };

            static const char* sTextNameC[5] = {
                "T_name_c_00",
                "T_name_c_01",
                "T_name_c_02",
                "T_name_c_03",
                "T_name_c_04",
            };

            static const char* sButtonNameB[5] = {
                "B_name_b_00",
                "B_name_b_01",
                "B_name_b_02",
                "B_name_b_03",
                "B_name_b_04",
            };

            static const char* sButtonNameBB[] = {
                "B_name_b_00_01",
                "B_name_b_01_02",
                "B_name_b_02_03",
                "B_name_b_03_04",
            };

            static const char* sNameB[5] = {
                "name_b_00",
                "name_b_01",
                "name_b_02",
                "name_b_03",
                "name_b_04",
            };

            static const char* sNameC[5] = {
                "G_name_c_00",
                "G_name_c_01",
                "G_name_c_02",
                "G_name_c_03",
                "G_name_c_04",
            };

            static math::VEC2  sNullVec(-1.0f, -1.0f);
        }

        Address::Address(EGG::Heap* heap, int arg2)
            : FaderSceneBase(heap),
            mArg2(arg2),
            mpLayout(NULL), mpLayoutUnused(NULL), mpEvent(NULL), mpGui(NULL),
            mpBackLayout(NULL),
            mFisttState(1), mCounter(0), mState(1), mPageNo(0), mMaxPage(0x14),
            mUnk_0xb8(0), mUnk_0xbc(0), mChosenFriendIndex(0), mbFlagE0(FALSE) {
            setSceneParentFlags(SCN_PARENTFLAG_CALC | SCN_PARENTFLAG_DRAW);
            int i;
            for (i = 0; i < 5; i++) {
                mPaneFlags[i] = 0;
            }
            for (i = 0; i < 5; i++) {
                mbHovered[i] = 0;
            }
            memset(&mDragPos, 0, 0x24);
            mRightPageNo = -1;
            mLeftPageNo = -1;
        }

        Address::~Address() {
            delete mpFriendList;
        }

        void Address::prepare() {
            // Empty
        }

        void Address::create() {
            nand::LayoutFile* layoutFile = static_cast<Board*>(System::getScene(SCENE_BOARD))->getLayoutFile();

            mbFlagE1 = TRUE;

            mpLayout = new layout::Object(getSceneHeap(), layoutFile, "arc", "th_Adress_a.brlyt");

            mpLayout->bindToGroup("th_Adress_a_note_alp_in.brlan", "G_note_all", false, true);
            mpLayout->bindToGroup("th_Adress_a_note_alp_out.brlan", "G_note_all", false, false);
            mpLayout->bindToGroup("th_Adress_a_note_trns_in.brlan", "G_note_all", false, false);
            mpLayout->bindToGroup("th_Adress_a_note_trns_out.brlan", "G_note_all", false, false);
            mpLayout->bindToGroup("th_Adress_a_note_e_rtt.brlan", "G_note_e_rtt", false, mbFlagE1);
            mpLayout->bindToGroup("th_Adress_a_note_c_rtt.brlan", "note_c_rtt", false, !mbFlagE1);

            for (int i = 0; i < 5; i++) {
                mpLayout->bindToGroup("th_Adress_a_name_in.brlan", sNameB[i], false, false);
            }
            for (int i = 0; i < 5; i++) {
                mpLayout->bindToGroup("th_Adress_a_name_out.brlan", sNameB[i], false, false);
            }
            for (int i = 0; i < 5; i++) {
                mpLayout->bindToGroup("th_Adress_a_name_psh.brlan", sNameB[i], false, false);
            }
            for (int i = 0; i < 5; i++) {
                mpLayout->bindToGroup("th_Adress_a_gry_name_in.brlan", sNameB[i], false, false);
            }
            for (int i = 0; i < 5; i++) {
                mpLayout->bindToGroup("th_Adress_a_gry_name_out.brlan", sNameB[i], false, false);
            }
            for (int i = 0; i < 5; i++) {
                mpLayout->bindToGroup("th_Adress_a_gry_name_psh.brlan", sNameB[i], false, false);
            }
            for (int i = 0; i < 5; i++) {
                mpLayout->bindToGroup("th_Adress_a_name_c_gry.brlan", sNameC[i], false, false);
            }

            mpLayout->finishBinding();

            mpBackLayout = new layout::Object(getSceneHeap(), layoutFile, "arc", "my_Back_a.brlyt");
            mpBackLayout->bind("my_Back_a_Apear.brlan", "Picture_00", false, true);
            mpBackLayout->bind("my_Back_a_Lost.brlan", "Picture_00", false, false);
            mpBackLayout->finishBinding();
            mpBackLayout->getAnim(0)->initAnmFrame();

            mpDialogLayout = new layout::Object(getSceneHeap(), layoutFile, "arc", "my_Dialog_a.brlyt");
            mpDialogLayout->bind("my_Dialog_a_DialogIn.brlan", "N_Top", false, true);
            mpDialogLayout->bind("my_Dialog_a_DialogOut.brlan", "N_Top", false, false);
            mpDialogLayout->finishBinding();

            nw4r::lyt::TextBox* textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpDialogLayout->FindPaneByName("T_Dialog"));
            textBox->SetString(System::getMessage(0x4E), 0);

            mpEvent = new AddressEvent(this);
            mpGui = new gui::PaneManager(mpEvent, mpLayout->getDrawInfo(), NULL, NULL);
            mpGui->setupScene(mpLayout);
            mpGui->setAllComponentTriggerTarget(false);

            for (int i = 0; i < 5; i++) {
                mpGui->setTriggerTarget(mpLayout->FindPaneByName(sButtonNameB[i]), true);
            }
            for (int i = 0; i < 4; i++) {
                mpGui->setTriggerTarget(mpLayout->FindPaneByName(sButtonNameBB[i]), true);
            }

            for (int i = 0; i < 5; i++) {
                char paneName[0x10];
                sprintf(paneName, "mii_b_%02d", i);
                mMiiB[i].init(mpLayout->FindPaneByName(paneName));
            }
            for (int i = 0; i < 5; i++) {
                char paneName[0x10];
                sprintf(paneName, "mii_c_%02d", i);
                mMiiC[i].init(mpLayout->FindPaneByName(paneName));
            }

            set_textbox("T_adrs_00", System::getMessage(0x86));
            set_textbox("T_wii_msg", System::getMessage(0x42));

            mpFriendList = new (0x20) FriendListCache;
            if (mpFriendList->init()) {
                onInitFriendList();
                mFisttState = 1;
            }
            else {
                mFisttState = 0;
            }

            mpWork = new u8[0x2D20];

            mpLayout->FindPaneByName("N_note_move")->SetVisible(false);
        }

        FaderSceneCommand Address::calcFadein() {
            switch (mFisttState) {
                case 0: {
                    fistt_wait_open();
                    break;
                }
                case 1: {
                    fistt_fadein();
                    break;
                }
            }

            return mFisttState == 2 ? FADER_SCN_NEXT : FADER_SCN_CONTINUE;
        }

        FaderSceneCommand Address::calcFadeout() {
            FaderSceneCommand result;
            if (System::getFader()->getStatus() == EGG::Fader::PREPARE_OUT) {
                result = FADER_SCN_CONTINUE;
                bool bDone = !mpLayout->getAnim(1)->isPlaying() && !mpLayout->getAnim(3)->isPlaying();
                if (bDone && !mpDialogLayout->getAnim(1)->isPlaying()) {
                    result = FADER_SCN_NEXT;
                }
            }
            else {
                result = (FaderSceneCommand)(System::getFader()->getStatus() == EGG::Fader::PREPARE_IN);
            }

            return result;
        }

        void Address::initCalcFadeout() {
            static_cast<Button*>(System::getScene(SCENE_BUTTON))->setEventHandler(NULL, NULL);
        }

        void Address::initCalcNormal() {
            static_cast<Button*>(System::getScene(SCENE_BUTTON))->setEventHandler(this);
        }

        FaderSceneCommand Address::calcNormal() {
            switch (mState) {
                case 0: {
                    snd::getSystem()->startSE("WIPL_SE_FL_PAGE_INC");
                    onNextPage();
                    break;
                }
                case 1: {
                    stt_cover_normal();
                    break;
                }
                case 2: {
                    stt_cover_forward();
                    break;
                }
                case 3: {
                    stt_cover_backward();
                    break;
                }
                case 4: {
                    stt_normal();
                    break;
                }
                case 5: {
                    stt_forward();
                    break;
                }
                case 6: {
                    stt_backward();
                    break;
                }
                case 7: {
                    stt_loop_forward();
                    break;
                }
                case 8: {
                    stt_loop_backward();
                    break;
                }
                case 9: {
                    stt_decide();
                    break;
                }
                case 0xA: {
                    stt_drag();
                    break;
                }
                case 0xB: {
                    stt_release();
                    break;
                }
                case 0xC: {
                    stt_wait_child_cst();
                    break;
                }
                case 0xD: {
                    stt_wait_child_dst();
                    break;
                }
                case 0xE: {
                    stt_wait_child_fadeout();
                    break;
                }
                case 0xF: {
                    stt_msg_net();
                    break;
                }
                case 0x10: {
                    stt_wait_parental();
                    break;
                }
                case 0x11: {
                    stt_wait_parental_dst();
                    break;
                }
                case 0x12: {
                    stt_msg_wc();
                    break;
                }
                case 0x13: {
                    stt_wait_parental_wc();
                    break;
                }
                case 0x14: {
                    stt_wait_parental_dst_wc();
                    break;
                }
                case 0x15: {
                    stt_msg_nwc24_error();
                    break;
                }
                case 0x16: {
                    stt_msg_fi_full();
                    break;
                }
                case 0x17: {
                    stt_msg_parental();
                    break;
                }
                case 0x18: {
                    stt_msg_open_failure();
                    break;
                }
                case 0x19: {
                    stt_wait_dialog();
                    break;
                }
            }

            return mState == 0x1A ? FADER_SCN_NEXT : FADER_SCN_CONTINUE;
        }

        void Address::calcCommonAfter() {
            mpLayout->calc();
            mpBackLayout->calc();
            mpDialogLayout->calc();
        }

        void Address::draw() {
            if (System::onDrawLayer(scene::DRAW_LAYER_2)) {
                utility::Graphics::setOrtho(0);

                nw4r::lyt::Pane* pane = mpLayout->FindPaneByName("N_note_a");
                for (int i = mMaxPage; i >= 1; i--) {
                    math::VEC2 t;
                    t.y = sNullVec.y * i;
                    t.x = sNullVec.x * i;
                    math::VEC2 v = t;
                    pane->SetTranslate(nw4r::math::VEC2(v));
                    pane->CalculateMtx(*mpLayout->getDrawInfo());
                    mpLayout->draw(pane);
                }

                mpLayout->draw("N_note_b");

                if (mState == 5 || mState == 6) {
                    mpLayout->draw("N_note_c");
                }

                int count;
                switch (mState) {
                    case 2: case 3:
                    case 5: case 6:
                        count = 1;
                        break;
                    default:
                        count = 0;
                        break;
                }

                pane = mpLayout->FindPaneByName("N_note_d");
                for (int i = count; i < mUnk_0xb8 + count; i++) {
                    math::VEC2 v = sNullVec * -i;
                    pane->SetTranslate(v);
                    pane->CalculateMtx(*mpLayout->getDrawInfo());
                    mpLayout->draw(pane);
                }

                pane = mpLayout->FindPaneByName("N_note_e");
                if (mState < 9 && mState >= 7) {
                    for (int i = 1; i < 0x14; i++) {
                        math::VEC2 v = sNullVec * -i;
                        pane->SetTranslate(v);
                        pane->CalculateMtx(*mpLayout->getDrawInfo());
                        mpLayout->draw(pane);
                    }
                }
                else {
                    math::VEC2 v = sNullVec * -(mUnk_0xb8 + count);
                    pane->SetTranslate(v);
                    pane->CalculateMtx(*mpLayout->getDrawInfo());
                    mpLayout->draw("N_note_e");
                }

                mpBackLayout->draw();
                mpDialogLayout->draw();
            }
            else if (System::onDrawLayer(scene::DRAW_LAYER_3)) {
                utility::Graphics::setOrtho(0);

                switch (mState) {
                    case 1: case 2: case 3:
                    case 5: case 6: case 7: case 8:
                    case 0xA:
                        mpLayout->draw("N_note_move");
                        break;
                }
            }
        }

        void Address::destroy() {
            mpFriendList->fin();
        }

        void Address::fistt_wait_open() {
            if (mpFriendList->init()) {
                onInitFriendList();
                mFisttState = 1;
            }
            else if (mCounter >= 300) {
                System::getDialog()->callBtn1(0x1C6, 0x2E);
                mState = 0x18;
                mFisttState = 2;
            }

            mCounter++;
        }

        void Address::fistt_fadein() {
            if (!mpLayout->getAnim(0)->isPlaying() &&
                !mpLayout->getAnim(2)->isPlaying() &&
                !mpDialogLayout->getAnim(0)->isPlaying()) {
                mFisttState = 2;
            }
        }

        void Address::onInitFriendList() {
            wchar_t wii[0x18];
            wchar_t text[0x18];
            memset(wii, 0, sizeof(wii));
            memset(text, 0, sizeof(text));

            utility::CharacterCode::WiiIdToUTF16(wii, mpFriendList->mMyUserId);

            int i = 0;
            for (int j = 0; j < 4; j++) {
                text[i++] = wii[j];
            }
            text[i] = L' ';
            i++;
            for (int j = 4; j < 8; j++) {
                text[i++] = wii[j];
            }
            text[i] = L' ';
            i++;
            for (int j = 8; j < 12; j++) {
                text[i++] = wii[j];
            }
            text[i] = L' ';
            i++;
            for (int j = 12; j < 16; j++) {
                text[i++] = wii[j];
            }

            set_textbox("T_wii_name", text);
            set_page_text("T_nmbr_b", mPageNo + 1);

            for (u32 i = 0; i < 5; i++) {
                set_friend(sTextNameB[i], i, i, mMiiB[i], false);
                if (mbHovered[i]) {
                    mpLayout->getAnim(i + 6)->initAnmFrame();
                }
                else {
                    mpLayout->getAnim(i + 0x15)->initAnmFrame();
                }
            }

            mPageNo = 0;
            mUnk_0xb8 = 0;
            mMaxPage = 0x14;

            Button* btn = static_cast<Button*>(System::getScene(SCENE_BUTTON));
            btn->animation(0x17);
            btn->animation(0x18);

            if (mArg2 == 0) {
                mState = 1;
            }
            else if (mpFriendList->mNumRegInfos == 0) {
                mState = 1;
            }
            else {
                mState = 0;
            }

            switch (mArg2) {
                case 0: {
                    mpLayout->getAnim(0)->play();
                    break;
                }
                case 1:
                case 2: {
                    mpLayout->getAnim(2)->play();
                    mpDialogLayout->getAnim(0)->play();
                    break;
                }
            }
        }

        void Address::stt_cover_normal() {
            if (mbDragging) {
                changePage_onDrag();
            }
            else {
                Button* button = static_cast<Button*>(System::getScene(SCENE_BUTTON));
                if (button->isActive()) {
                    button->update();
                }
            }

            if (mState == 1) {
                if (System::getMasterController()->down(controller::BTN_NEXT_RIGHT)) {
                    snd::getSystem()->startSE("WIPL_SE_FL_PAGE_INC");
                    onNextPage();
                }
                else if (System::getMasterController()->down(controller::BTN_NEXT_LEFT)) {
                    snd::getSystem()->startSE("WIPL_SE_FL_PAGE_DEC");
                    onPreviousPage();
                }
            }
        }

        void Address::stt_cover_forward() {
            if (!mpLayout->getAnim(4)->isPlaying()) {
                mbFlagE1 = FALSE;
                if (!mbDragging) {
                    mState = 4;
                }
                else {
                    mState = 0xA;
                }
            }
            else if (mbDragging) {
                changePage_onDrag();
            }
        }

        void Address::stt_cover_backward() {
            if (!mpLayout->getAnim(4)->isPlaying()) {
                nw4r::math::VEC2 v;
                v.x = -sNullVec.x;
                v.y = -sNullVec.y;
                nw4r::math::VEC2 w = v;
                math::VEC2 u = w;
                add_translate(mpLayout->FindPaneByName("N_note_base"), u);
                mbFlagE1 = TRUE;
                mMaxPage++;
                mState = 1;
            }
            else if (mbDragging) {
                changePage_onDrag();
            }
        }

        void Address::stt_normal() {
            Button* button = static_cast<Button*>(System::getScene(SCENE_BUTTON));
            if (button->isActive()) {
                button->update();
            }

            if (mState == 4) {
                mpGui->update();

                if (System::getMasterController()->down(controller::BTN_NEXT_RIGHT)) {
                    snd::getSystem()->startSE("WIPL_SE_FL_PAGE_INC");
                    onNextPage();
                }
                else if (System::getMasterController()->down(controller::BTN_NEXT_LEFT)) {
                    snd::getSystem()->startSE("WIPL_SE_FL_PAGE_DEC");
                    onPreviousPage();
                }
            }
        }

        void Address::stt_forward() {
            if (!mpLayout->getAnim(5)->isPlaying()) {
                mUnk_0xb8++;
                if (!mbDragging) {
                    mState = 4;
                }
                else {
                    mState = 0xA;
                }
            }
            else if (mbDragging) {
                changePage_onDrag();
            }
        }

        void Address::stt_backward() {
            nw4r::math::VEC2 w;
            math::VEC2 v;
            if (!mpLayout->getAnim(5)->isPlaying()) {
                mMaxPage++;
                v.y = -sNullVec.y;
                v.x = -sNullVec.x;
                nw4r::math::VEC2 z = v;
                add_translate(mpLayout->FindPaneByName("N_note_base"), z);
                set_page_text("T_nmbr_b", mPageNo + 1);
                for (u32 i = 0; i < 5; i++) {
                    set_friend(sTextNameB[i], mPageNo * 5 + i, i, mMiiB[i], false);
                }
                if (!mbDragging) {
                    mState = 4;
                }
                else {
                    mState = 0xA;
                }
            }
            else if (mbDragging) {
                changePage_onDrag();
            }
        }

        void Address::stt_loop_forward() {
            if (!mpLayout->getAnim(4)->isPlaying()) {
                nw4r::math::VEC2 v;
                v.y = -sNullVec.y;
                v.x = -sNullVec.x;
                nw4r::math::VEC2 w = v;
                add_translate(mpLayout->FindPaneByName("N_note_base"), w * 20.0f);
                set_page_text("T_nmbr_b", mPageNo + 1);
                reset_gui(false);
                for (u32 i = 0; i < 5; i++) {
                    set_friend(sTextNameB[i], mPageNo * 5 + i, i, mMiiB[i], false);
                }
                mbFlagE1 = TRUE;
                mMaxPage = 0x14;
                mState = 1;
            }
            else if (mbDragging) {
                changePage_onDrag();
            }
        }

        void Address::stt_loop_backward() {
            if (!mpLayout->getAnim(4)->isPlaying()) {
                mbFlagE1 = FALSE;
                mUnk_0xb8 = 0x13;
                if (!mbDragging) {
                    mState = 4;
                }
                else {
                    mState = 0xA;
                }
            }
            else if (mbDragging) {
                changePage_onDrag();
            }
        }

        void Address::stt_decide() {
            if (!mpLayout->getAnim(mUnk_0xbc + 0x10)->isPlaying() &&
                !mpLayout->getAnim(mUnk_0xbc + 0x1F)->isPlaying()) {
                reset_gui(true);

                switch (mArg2) {
                    case 0: {
                        createChildScene(SCENE_ADDRESS_EDIT, this, NULL, NULL);
                        mpBackLayout->getAnim(0)->play();
                        mState = 0xC;
                        break;
                    }
                    case 1:
                    case 2: {
                        static_cast<LetterWriter*>(System::getScene(SCENE_LETTER_WRITER))->setFriendInfo(mpFriendList->mInfos[mChosenFriendIndex]);
                        mpLayout->getAnim(3)->play();
                        mpDialogLayout->getAnim(1)->play();
                        mState = 0x1A;
                        break;
                    }
                }
            }
        }

        void Address::stt_drag() {
            mpGui->update();

            if (mState == 0xA) {
                changePage_onDrag();
            }
        }

        void Address::stt_release() {
            mpGui->init();

            for (int i = 0; i < 5; i++) {
                if (mbHovered[i]) {
                    mpLayout->getAnim(i + 6)->initAnmFrame();
                }
                else {
                    mpLayout->getAnim(i + 0x15)->initAnmFrame();
                }
                mPaneFlags[i] = 0;
            }

            mpLayout->FindPaneByName("N_note_move")->SetVisible(false);

            if (mbFlagE1) {
                mState = 1;
            }
            else {
                mState = 4;
            }
        }

        void Address::stt_wait_child_cst() {
            if (getChild() != NULL && !mpBackLayout->getAnim(0)->isPlaying()) {
                mState = 0xD;
                reset_gui(true);
                for (int i = 0; i < 5; i++) {
                    mPaneFlags[i] = 0;
                }
            }
        }

        void Address::stt_wait_child_dst() {
            if (getChild() == NULL && System::getSceneManager()->getReservedScene() == NULL) {
                mpBackLayout->getAnim(1)->play();
                static_cast<Button*>(System::getScene(SCENE_BUTTON))->setEventHandler(this);
                mState = 0xE;
            }
        }

        void Address::stt_wait_child_fadeout() {
            if (!mpBackLayout->getAnim(1)->isPlaying()) {
                Button* button = static_cast<Button*>(System::getScene(SCENE_BUTTON));
                button->setText("T_CalAdd_R", 0x29);
                button->animation(0x17);
                button->animation(0x18);
                if (mbFlagE1) {
                    mState = 1;
                }
                else {
                    mState = 4;
                }
            }
        }

        void Address::stt_msg_net() {
            switch (System::getDialog()->getLastResult()) {
                case 2: {
                    if (mbFlagE1) {
                        mState = 1;
                    }
                    else {
                        mState = 4;
                    }
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(0x17);
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(0x18);
                    break;
                }
                case 1: {
                    SCParentalControlsInfo pcInfo;
                    if (SCGetParentalControl(&pcInfo) && (pcInfo.enable & SC_PARENTAL_FLAG_ENABLED)) {
                        static_cast<Button*>(System::getScene(SCENE_BUTTON))->setEventHandler(NULL, NULL);
                        static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(0x10);
                        createChildScene(SCENE_PARENTAL_DIALOG, this, NULL, (void*)1);
                        mbFlagE0 = FALSE;
                        mState = 0x10;
                    }
                    else {
                        System::getFader()->fadeOut();
                        reserveAllSceneDestruction(SCENE_SETTING, (void*)1);
                        mState = 0x1A;
                    }
                    break;
                }
            }
        }

        void Address::stt_wait_parental() {
            ParentalDialog* parentDialog = static_cast<ParentalDialog*>(System::getScene(SCENE_PARENTAL_DIALOG));

            if (parentDialog != NULL) {
                switch (parentDialog->getResult()) {
                    case ParentalDialog::RESULT_SUCCESS: {
                        mbFlagE0 = TRUE;
                        mState = 0x11;
                        break;
                    }
                    case ParentalDialog::RESULT_OVER_ATTEMPTS:
                    case ParentalDialog::RESULT_CANCELLED: {
                        mbFlagE0 = FALSE;
                        mState = 0x11;
                        break;
                    }
                }
            }
        }

        void Address::stt_wait_parental_dst() {
            if (getChild() == NULL) {
                if (mbFlagE0) {
                    System::getFader()->fadeOut();
                    reserveAllSceneDestruction(SCENE_SETTING, (void*)1);
                    mState = 0x1A;
                }
                else {
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(0xF);
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->setEventHandler(this);
                    if (mbFlagE1) {
                        mState = 1;
                    }
                    else {
                        mState = 4;
                    }
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(0x17);
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(0x18);
                }
            }
        }

        void Address::stt_msg_wc() {
            switch (System::getDialog()->getLastResult()) {
                case 2: {
                    if (mbFlagE1) {
                        mState = 1;
                    }
                    else {
                        mState = 4;
                    }
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(0x17);
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(0x18);
                    break;
                }
                case 1: {
                    SCParentalControlsInfo pcInfo;
                    if (SCGetParentalControl(&pcInfo) && (pcInfo.enable & SC_PARENTAL_FLAG_ENABLED)) {
                        static_cast<Button*>(System::getScene(SCENE_BUTTON))->setEventHandler(NULL, NULL);
                        static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(0x10);
                        createChildScene(SCENE_PARENTAL_DIALOG, this, NULL, (void*)1);
                        mbFlagE0 = FALSE;
                        mState = 0x13;
                    }
                    else {
                        System::getFader()->fadeOut();
                        reserveAllSceneDestruction(SCENE_SETTING, (void*)4);
                        mState = 0x1A;
                    }
                    break;
                }
            }
        }

        void Address::stt_wait_parental_wc() {
            ParentalDialog* parentDialog = static_cast<ParentalDialog*>(System::getScene(SCENE_PARENTAL_DIALOG));

            if (parentDialog != NULL) {
                switch (parentDialog->getResult()) {
                    case ParentalDialog::RESULT_SUCCESS: {
                        mbFlagE0 = TRUE;
                        mState = 0x14;
                        break;
                    }
                    case ParentalDialog::RESULT_OVER_ATTEMPTS:
                    case ParentalDialog::RESULT_CANCELLED: {
                        mbFlagE0 = FALSE;
                        mState = 0x14;
                        break;
                    }
                }
            }
        }

        void Address::stt_wait_parental_dst_wc() {
            if (getChild() == NULL) {
                if (mbFlagE0) {
                    System::getFader()->fadeOut();
                    reserveAllSceneDestruction(SCENE_SETTING, (void*)4);
                    mState = 0x1A;
                }
                else {
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(0xF);
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->setEventHandler(this);
                    if (mbFlagE1) {
                        mState = 1;
                    }
                    else {
                        mState = 4;
                    }
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(0x17);
                    static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(0x18);
                }
            }
        }

        void Address::stt_msg_nwc24_error() {
            switch (System::getDialog()->getLastResult()) {
                case 1:
                if (mbFlagE1) {
                    mState = 1;
                }
                else {
                    mState = 4;
                }
                static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(0x17);
                static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(0x18);
            }
        }

        void Address::stt_msg_fi_full() {
            switch (System::getDialog()->getLastResult()) {
                case 1:
                if (mbFlagE1) {
                    mState = 1;
                }
                else {
                    mState = 4;
                }
                static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(0x17);
                static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(0x18);
            }
        }

        void Address::stt_msg_parental() {
            switch (System::getDialog()->getLastResult()) {
                case 1:
                if (mbFlagE1) {
                    mState = 1;
                }
                else {
                    mState = 4;
                }
                static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(0x17);
                static_cast<Button*>(System::getScene(SCENE_BUTTON))->animation(0x18);
            }
        }

        void Address::stt_msg_open_failure() {
            if (System::getDialog()->getLastResult() == 1) {
                Button* button = static_cast<Button*>(System::getScene(SCENE_BUTTON));
                MailAddressSelect* mailSel = static_cast<MailAddressSelect*>(System::getScene(SCENE_MAIL_ADDRESS_SELECT));

                switch (mArg2) {
                    case 0: {
                        if (mailSel != NULL) {
                            mailSel->finishAddress();
                        }
                        button->reserveAnm(0x10);
                        button->reserveAnm(0xB);
                        break;
                    }
                    case 1: {
                        button->reserveAnm(0xC);
                        button->reserveAnm(0xB);
                        break;
                    }
                    case 2: {
                        button->reserveAnm(0xC);
                        button->reserveText(0, 0x13B);
                        button->reserveText(1, 0x33);
                        button->reserveAnm(0xF);
                        break;
                    }
                }

                button->animation(0x19);
                button->animation(0x1A);
                mState = 0x1A;
            }
        }

        void Address::stt_wait_dialog() {
            if (System::getDialog()->getLastResult() >= 0) {
                reset_gui(true);
                mState = 4;
            }
        }

        void Address::add_translate(nw4r::lyt::Pane* pane, const math::VEC2& trans) {
            nw4r::ut::Rect projRect;
            nw4r::ut::Rect projRect4x3;
            System::getProjectionRect(&projRect);
            System::getProjectionRect4x3(&projRect4x3);

            math::VEC3 pos;
            pos.x = pane->GetTranslate().x;
            pos.y = pane->GetTranslate().y;
            pos.z = pane->GetTranslate().z;
            pos.x += trans.x * (projRect4x3.right - projRect4x3.left) / (projRect.right - projRect.left);
            pos.y += trans.y;
            pane->SetTranslate(pos);
        }

        void Address::set_friend(const char* paneName, u32 index, u32 buttonNo, MiiObj& mii, bool bBackup) {
            wchar_t empty = 0;
            const wchar_t* text = &empty;

            if (mpFriendList->mbHasInfo[index]) {
                NWC24FriendInfo* info = &mpFriendList->mInfos[index];
                text = (const wchar_t*)info->attr.name;

                bool select = info->attr.status == NWC24_FRIENDSTATUS_CONFIRMED;
                if (mArg2 == 2) {
                    select = select & (info->attr.type == NWC24_FRIENDTYPE_WII);
                }

                if (bBackup) {
                    if (select) {
                        mpLayout->getAnim(buttonNo + 0x24)->initAnmFrame(0.0f);
                    }
                    else {
                        mpLayout->getAnim(buttonNo + 0x24)->initAnmFrame(1.0f);
                    }
                }
                else {
                    if (select) {
                        mpLayout->getAnim(buttonNo + 6)->initAnmFrame();
                    }
                    else {
                        mpLayout->getAnim(buttonNo + 0x15)->initAnmFrame();
                    }
                    mbHovered[buttonNo] = select;
                }

                if (!(mbDragging && index == mDragPageNo * 5 + mDragButtonNo)) {
                    mii.set(info->attr.fdId);
                }
            }
            else {
                if (bBackup) {
                    mpLayout->getAnim(buttonNo + 0x24)->initAnmFrame(0.0f);
                }
                else {
                    mbHovered[buttonNo] = FALSE;
                    mpLayout->getAnim(buttonNo + 0x15)->initAnmFrame();
                }
                mii.reset();
            }

            if (mbDragging && index == mDragPageNo * 5 + mDragButtonNo) {
                set_textbox(paneName, L"");
                mii.reset();
            }
            else {
                set_textbox(paneName, text);
            }
        }

        void Address::set_page_text(const char* paneName, int page) {
            wchar_t digits[10] = {L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9'};
            wchar_t buf[6] = {0};

            int i = 0;
            if (page >= 10) {
                buf[i++] = digits[page / 10];
            }
            buf[i++] = digits[page % 10];
            buf[i++] = L'/';
            buf[i++] = digits[2];
            buf[i++] = digits[0];
            buf[i] = 0;

            set_textbox(paneName, buf);
        }

        void Address::set_textbox(const char* paneName, const wchar_t* text) {
            nw4r::lyt::TextBox* pane = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpLayout->FindPaneByName(paneName));
            pane->SetString(text, 0);
        }

        void Address::reset_friend() {
            for (u32 i = 0; i < 5; i++) {
                set_friend(sTextNameB[i], mPageNo * 5 + i, i, mMiiB[i], false);
            }
        }

        void Address::start_point_event(const char* paneName, controller::Interface* con) {
            int buttonNo = get_button_no(paneName);

            if (buttonNo != -1) {
                if (mArg2 == 0 || (mArg2 == 1 && is_selectable(mPageNo * 5 + buttonNo))) {
                    on_point_event(buttonNo, con);
                }
            }
        }

        void Address::start_left_event(const char* paneName) {
            int buttonNo = get_button_no(paneName);

            if (buttonNo != -1) {
                if (mArg2 == 0 || (mArg2 == 1 && is_selectable(mPageNo * 5 + buttonNo))) {
                    left_point_event(buttonNo);
                }
            }
        }

        void Address::start_trig_event(const char* paneName) {
            Button* button = static_cast<Button*>(System::getScene(SCENE_BUTTON));
            int buttonNo = get_button_no(paneName);

            if (mState != 4) {
                return;
            }

            switch (mArg2) {
                case 0: {
                    if (buttonNo != -1 && is_selectable(mPageNo * 5 + buttonNo)) {
                        button->animation(0x19);
                        button->animation(0x1A);
                        button->animation(0x10);
                        button->reserveText(0, 0x13B);
                        button->reserveAnm(0xB);
                        button->setEventHandler(NULL, NULL);
                        if (mbHovered[buttonNo]) {
                            mpLayout->getAnim(buttonNo + 0x10)->play();
                        }
                        else {
                            mpLayout->getAnim(buttonNo + 0x1F)->play();
                        }
                        mUnk_0xbc = buttonNo;
                        mChosenFriendIndex = mPageNo * 5 + buttonNo;
                        snd::getSystem()->startSE("WIPL_SE_DECIDE");
                        mPaneFlags[buttonNo]++;
                        mState = 9;
                    }
                    else if (buttonNo != -1) {
                        mUnk_0xbc = buttonNo;
                        mChosenFriendIndex = mPageNo * 5 + buttonNo;
                        entry_friend();
                    }
                    break;
                }
                case 1:
                case 2: {
                    if (buttonNo != -1 && is_selectable(mPageNo * 5 + buttonNo)) {
                        button->animation(0xC);
                        button->reserveText(0, 0x25);
                        button->reserveText(1, 0x33);
                        button->reserveAnm(0xF);
                        button->animation(0x19);
                        button->animation(0x1A);
                        mpLayout->getAnim(buttonNo + 0x10)->play();
                        mUnk_0xbc = buttonNo;
                        mChosenFriendIndex = mPageNo * 5 + buttonNo;
                        snd::getSystem()->startSE("WIPL_SE_DECIDE");
                        mState = 9;
                    }
                    else if (buttonNo != -1 && mpFriendList->mbHasInfo[mPageNo * 5 + buttonNo]) {
                        if (mArg2 == 1 || mpFriendList->mInfos[mPageNo * 5 + buttonNo].attr.type == NWC24_FRIENDTYPE_WII) {
                            System::getDialog()->callBtn1(0x57, 0x2E);
                        }
                        else {
                            System::getDialog()->callBtn1(0x22, 0x2E);
                        }
                        mState = 0x19;
                    }
                    break;
                }
            }
        }

        void Address::start_drag_event(const char* paneName, const controller::Interface* con) {
            int buttonNo = get_button_no(paneName);

            if (buttonNo == -1 || con->getChannel() < 0 ||
                mState != 4 || mArg2 != 0 ||
                !mpFriendList->mbHasInfo[mPageNo * 5 + buttonNo]) {
                return;
            }

            mbDragging = TRUE;
            mDragChannel = con->getChannel();
            if (con->isValidDpd()) {
                mDragPos = System::getControllerManager()->getController(mDragChannel)->getDpdProjectionPos();
            }
            else {
                mDragPos = math::VEC2(0.0f, 0.0f);
            }

            mDragPageNo = mPageNo;
            mDragButtonNo = buttonNo;
            mRightPageNo = -1;
            mLeftPageNo = -1;
            mUnk_0x80 = 0;

            System::getPointer()->changeType(con->getChannel(), 1);
            static_cast<Button*>(System::getScene(SCENE_BUTTON))->disableBtn();

            wchar_t empty[2] = {0};
            nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpLayout->FindPaneByName(sTextNameB[mDragButtonNo]))->SetString(empty, 0);

            nigaoe::Object* nigaoe = mMiiB[buttonNo].mpNigaoeObj;
            if (nigaoe != NULL) {
                nw4r::lyt::Pane* pane = mpLayout->FindPaneByName("mii_move");
                pane->SetVisible(true);

                memcpy(&mMiiTexObj, &nigaoe->getIconTexture(), 0x20);
                memcpy(mpWork, nigaoe->getIconTexImage(), 0x2D20);
                GXInitTexObj(&mMiiTexObj, mpWork, 0x4C, 0x4C, (GXTexFmt)5, GX_CLAMP, GX_CLAMP, GX_FALSE);
                pane->GetMaterial()->SetTexture(0, mMiiTexObj);

                mMiiB[buttonNo].reset();
            }
            else {
                mpLayout->FindPaneByName("mii_move")->SetVisible(false);
            }

            mpGui->init();

            for (int i = 0; i < 5; i++) {
                mPaneFlags[i] = 0;
                if (mbHovered[i]) {
                    mpLayout->getAnim(i + 6)->initAnmFrame();
                }
                else {
                    mpLayout->getAnim(i + 0x15)->initAnmFrame();
                }
            }

            movePane_onDrag();

            snd::getSystem()->startSEwithPos("WIPL_SE_CH_HOLD", mDragPos.x);

            mState = 0xA;
        }

        void Address::start_drag_point_event(const char* paneName, controller::Interface* con) {
            int buttonNo = get_button_no(paneName);

            if (buttonNo != -1 && isReleasableArea(mPageNo, buttonNo)) {
                on_point_event(buttonNo, con);
                mbDragging = TRUE;
            }
        }

        void Address::start_drag_left_event(const char* paneName) {
            int buttonNo = get_button_no(paneName);

            if (buttonNo != -1) {
                left_point_event(buttonNo);
                mbDragging = TRUE;
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

            if (mArg2) {
                return;
            }

            if (isReleasableArea(mPageNo, buttonNo)) {
                mUnk_0xbc = buttonNo;
                mChosenFriendIndex = mPageNo * 5 + buttonNo;
                if (mChosenFriendIndex != (u32)(mDragPageNo * 5 + mDragButtonNo)) {
                    mpFriendList->swap(mChosenFriendIndex, mDragPageNo * 5 + mDragButtonNo);
                }
                snd::getSystem()->startSEwithPos("WIPL_SE_CH_SET", mDragPos.x);
            }
            else {
                snd::getSystem()->startSEwithPos("WIPL_SE_CH_NOT_MOVE", mDragPos.x);
            }

            System::getPointer()->changeType(mDragChannel, 0);
            static_cast<Button*>(System::getScene(SCENE_BUTTON))->enableBtn();
            mpLayout->FindPaneByName(sTextNameB[mDragButtonNo])->SetVisible(true);
            mbDragging = FALSE;
            mState = 0xB;
            reset_friend();
        }

        void Address::on_point_event(int buttonNo, controller::Interface* con) {
            if (mPaneFlags[buttonNo] == 0) {
                if (mbHovered[buttonNo]) {
                    mpLayout->getAnim(buttonNo + 6)->play();
                }
                else {
                    mpLayout->getAnim(buttonNo + 0x15)->play();
                }
                snd::getSystem()->startSE("WIPL_SE_BT_TARGETTING");
                con->rumble(1);
            }
            mPaneFlags[buttonNo]++;
        }

        void Address::left_point_event(int buttonNo) {
            if (mPaneFlags[buttonNo] == 1) {
                if (mbHovered[buttonNo]) {
                    mpLayout->getAnim(buttonNo + 0xB)->play();
                }
                else {
                    mpLayout->getAnim(buttonNo + 0x1A)->play();
                }
            }
            if (mPaneFlags[buttonNo] > 0) {
                mPaneFlags[buttonNo]--;
            }
        }

        int Address::get_button_no(const char* paneName) {
            int result = -1;
            for (int i = 0; i < 5; i++) {
                if (strcmp(sButtonNameB[i], paneName) == 0) {
                    result = i;
                    break;
                }
            }
            return result;
        }

        int Address::get_button_space_no(const char* paneName) {
            int result = -1;
            for (int i = 0; i < 4; i++) {
                if (strcmp(sButtonNameBB[i], paneName) == 0) {
                    result = i;
                    break;
                }
            }
            return result;
        }

        void Address::reset_gui(bool bPage) {
            mpGui->init();

            for (int i = 0; i < 5; i++) {
                mpLayout->getAnim(i + 6)->initAnmFrame();
                mpLayout->getAnim(i + 6)->calc();
                mpLayout->getAnim(i + 0xB)->initAnmFrame();
                mpLayout->getAnim(i + 0xB)->calc();
                mpLayout->getAnim(i + 0x10)->initAnmFrame();
                mpLayout->getAnim(i + 0x10)->calc();
                mpLayout->getAnim(i + 0x15)->initAnmFrame();
                mpLayout->getAnim(i + 0x15)->calc();
                mpLayout->getAnim(i + 0x1A)->initAnmFrame();
                mpLayout->getAnim(i + 0x1A)->calc();
                mpLayout->getAnim(i + 0x1F)->initAnmFrame();
                mpLayout->getAnim(i + 0x1F)->calc();

                if (mPaneFlags[i] != 0 && bPage) {
                    if (mbHovered[i]) {
                        mpLayout->getAnim(i + 0xB)->play();
                    }
                    else {
                        mpLayout->getAnim(i + 0x1A)->play();
                    }
                }
                else if (mbHovered[i]) {
                    mpLayout->getAnim(i + 6)->initAnmFrame();
                    mpLayout->getAnim(i + 6)->calc();
                }
                else {
                    mpLayout->getAnim(i + 0x15)->initAnmFrame();
                    mpLayout->getAnim(i + 0x15)->calc();
                }

                mPaneFlags[i] = 0;
            }
        }

        BOOL Address::is_selectable(u32 index) {
            switch (mArg2) {
                case 0: {
                    return mpFriendList->mbHasInfo[index];
                }
                case 1: {
                    if (mpFriendList->mbHasInfo[index]) {
                        return mpFriendList->mInfos[index].attr.status == NWC24_FRIENDSTATUS_CONFIRMED;
                    }
                    return FALSE;
                }
                case 2: {
                    if (mpFriendList->mbHasInfo[index]) {
                        NWC24FriendInfo* info = &mpFriendList->mInfos[index];
                        return info->attr.status == NWC24_FRIENDSTATUS_CONFIRMED &&
                            info->attr.type == NWC24_FRIENDTYPE_WII;
                    }
                    return FALSE;
                }
                default: {
                    return FALSE;
                }
            }
        }

        void Address::onEventDerived(u32 compId, u32 event, const controller::Interface* con) {
            gui::PaneComponent* component = static_cast<gui::PaneComponent*>(mpManager->getComponent(compId));
            const char* paneName = component->getPane()->GetName();

            switch (event) {
                case ON_TRIG: {
                    if (con == NULL) {
                        break;
                    }
                    if (con->downTrg(0x100800)) {
                        Button* button = static_cast<Button*>(System::getScene(SCENE_BUTTON));
                        if (mState == 1 || mState == 4) {
                            if (Button::cmpButtonName(paneName, 5) == 0) {
                                MailAddressSelect* sel = static_cast<MailAddressSelect*>(System::getScene(SCENE_MAIL_ADDRESS_SELECT));
                                button->animation(0x1B);
                                switch (mArg2) {
                                    case 0: {
                                        if (sel != NULL) {
                                            sel->finishAddress();
                                        }
                                        mpLayout->getAnim(1)->play();
                                        button->reserveAnm(0x10);
                                        button->reserveAnm(0xB);
                                        break;
                                    }
                                    case 1: {
                                        mpLayout->getAnim(3)->play();
                                        mpDialogLayout->getAnim(1)->play();
                                        button->reserveAnm(0xC);
                                        button->reserveAnm(0xB);
                                        break;
                                    }
                                    case 2: {
                                        mpLayout->getAnim(3)->play();
                                        mpDialogLayout->getAnim(1)->play();
                                        button->reserveAnm(0xC);
                                        button->reserveText(0, 0x13B);
                                        button->reserveText(1, 0x33);
                                        button->reserveAnm(0xF);
                                        break;
                                    }
                                }
                                button->animation(0x19);
                                button->animation(0x1A);
                                snd::getSystem()->startSE("WIPL_SE_CANCEL");
                                mState = 0x1A;
                            }
                            else if (Button::cmpButtonName(paneName, 7) == 0) {
                                mChosenFriendIndex = -1;
                                entry_friend();
                            }
                            else if (Button::cmpButtonName(paneName, 9) == 0) {
                                button->animation(0x13);
                                snd::getSystem()->startSE("WIPL_SE_FL_PAGE_INC");
                                onNextPage();
                            }
                            else if (Button::cmpButtonName(paneName, 10) == 0) {
                                button->animation(0x14);
                                snd::getSystem()->startSE("WIPL_SE_FL_PAGE_DEC");
                                onPreviousPage();
                            }
                        }
                    }
                }
                case ON_POINT: {
                    if (mbDragging) {
                        if (con == NULL || con == System::getControllerManager()->getController(mDragChannel)) {
                            if (Button::cmpButtonName(paneName, 10) == 0) {
                                if (mLeftPageNo < 0) {
                                    mLeftPageNo = 0;
                                }
                            }
                            else if (Button::cmpButtonName(paneName, 9) == 0) {
                                if (mRightPageNo < 0) {
                                    mRightPageNo = 0;
                                }
                            }
                        }
                    }
                    break;
                }
                case ON_LEFT: {
                    if (mbDragging) {
                        if (con == NULL || con == System::getControllerManager()->getController(mDragChannel)) {
                            if (Button::cmpButtonName(paneName, 10) == 0) {
                                mLeftPageNo = -1;
                            }
                            else if (Button::cmpButtonName(paneName, 9) == 0) {
                                mRightPageNo = -1;
                            }
                        }
                    }
                    break;
                }
            }
        }

        void Address::onNextPage() {
            switch (mState) {
                case 4:
                case 0xA: {
                    if (mPageNo < 0x13) {
                        mPageNo++;
                        mMaxPage--;
                        add_translate(mpLayout->FindPaneByName("N_note_base"), sNullVec);
                        mpLayout->getAnim(5)->setAnmType(0);
                        mpLayout->getAnim(5)->play();
                        set_page_text("T_nmbr_b", mPageNo + 1);
                        set_page_text("T_nmbr_c", mPageNo);
                        reset_gui(false);
                        for (u32 i = 0; i < 5; i++) {
                            set_friend(sTextNameB[i], mPageNo * 5 + i, i, mMiiB[i], false);
                            set_friend(sTextNameC[i], (mPageNo - 1) * 5 + i, i, mMiiC[i], true);
                        }
                        mState = 5;
                    }
                    else {
                        mPageNo = 0;
                        mUnk_0xb8 = 0;
                        mbFlagE1 = TRUE;
                        mpLayout->getAnim(4)->setAnmType(1);
                        mpLayout->getAnim(4)->play();
                        reset_gui(true);
                        mState = 7;
                    }
                    break;
                }
                case 0:
                case 1: {
                    mMaxPage--;
                    add_translate(mpLayout->FindPaneByName("N_note_base"), sNullVec);
                    mpLayout->getAnim(4)->setAnmType(0);
                    mpLayout->getAnim(4)->play();
                    reset_gui(true);
                    for (u32 i = 0; i < 5; i++) {
                        set_friend(sTextNameB[i], mPageNo * 5 + i, i, mMiiB[i], false);
                    }
                    mState = 2;
                    break;
                }
            }
        }

        void Address::onPreviousPage() {
            switch (mState) {
                case 4:
                case 0xA: {
                    if (mPageNo > 0) {
                        mPageNo--;
                        mUnk_0xb8--;
                        mpLayout->getAnim(5)->setAnmType(1);
                        mpLayout->getAnim(5)->play();
                        set_page_text("T_nmbr_c", mPageNo + 1);
                        reset_gui(true);
                        for (u32 i = 0; i < 5; i++) {
                            set_friend(sTextNameC[i], mPageNo * 5 + i, i, mMiiC[i], true);
                        }
                        mState = 6;
                    }
                    else {
                        mpLayout->getAnim(4)->setAnmType(1);
                        mpLayout->getAnim(4)->play();
                        reset_gui(true);
                        mState = 3;
                    }
                    break;
                }
                case 1: {
                    mPageNo = 0x13;
                    mMaxPage = 0;
                    mbFlagE1 = FALSE;
                    math::VEC2 w;
                    w.set(sNullVec.x * 20.0f, sNullVec.y * 20.0f);
                    add_translate(mpLayout->FindPaneByName("N_note_base"), math::VEC2(w));
                    mpLayout->getAnim(4)->setAnmType(0);
                    mpLayout->getAnim(4)->play();
                    set_page_text("T_nmbr_b", mPageNo + 1);
                    reset_gui(false);
                    for (u32 i = 0; i < 5; i++) {
                        set_friend(sTextNameB[i], mPageNo * 5 + i, i, mMiiB[i], false);
                    }
                    mState = 8;
                    break;
                }
            }
        }

        void Address::set_err_msg(wchar_t* buf, u32 bufLen, NWC24Err err) {
            wchar_t num[0x20];
            u32 msgId;

            memset(buf, 0, bufLen * sizeof(wchar_t));
            wcsncat(buf, System::getMessage(0x190), bufLen - wcslen(buf));
            memset(num, 0, sizeof(num));
            swprintf(num, 0x20, L"%06d\n", System::getNwc24Manager()->getErrCode());
            wcsncat(buf, num, bufLen - wcslen(buf));

            switch (err) {
                case NWC24_ERR_NETWORK: {
                    msgId = 0x19A;
                    break;
                }
                case NWC24_ERR_SERVER:
                case NWC24_ERR_FULL: {
                    msgId = 0x1C5;
                    break;
                }
            }

            wcsncat(buf, System::getMessage(msgId), bufLen - wcslen(buf));
        }

        void Address::entry_friend() {
            if (mArg2 == 0) {
                Button* button = static_cast<Button*>(System::getScene(SCENE_BUTTON));
                SCParentalControlsInfo pcInfo;
                wchar_t msg[0x400];
                BOOL parental = SCGetParentalControl(&pcInfo);
                u32 count = mpFriendList->mNumRegInfos;

                snd::getSystem()->startSE("WIPL_SE_DECIDE");
                if ((u32)mChosenFriendIndex == 0xFFFFFFFF) {
                    button->animation(0x1D);
                }

                if (!ncd::NCDSetting::getConnectEnableFlag()) {
                    System::getDialog()->callBtn2(0x145, 0x146, 0x25, false);
                    mState = 0xF;
                }
                else if (!(SCGetWCFlags() & 1)) {
                    System::getDialog()->callBtn2(0x17E, 0x146, 0x25, false);
                    mState = 0x12;
                }
                else if (parental && (pcInfo.enable & SC_PARENTAL_FLAG_ENABLED) && (SCGetNetContentRestrictions() & 2)) {
                    System::getDialog()->callBtn1(0x14C, 0x2E);
                    mState = 0x17;
                }
                else if (mpFriendList->check() == NWC24_ERR_NETWORK || mpFriendList->mUnk_0x9D74 == NWC24_ERR_SERVER || mpFriendList->mUnk_0x9D74 == NWC24_ERR_FULL) {
                    wchar_t* p = msg - 1;
                    for (int i = 0; i < 0x200; i++) {
                        *++p = 0;
                        *++p = 0;
                    }
                    set_err_msg(msg, 0x400, (NWC24Err)mpFriendList->mUnk_0x9D74);
                    System::getDialog()->callBtn1(msg, 0x2E);
                    mState = 0x15;
                }
                else if (count >= 0x64) {
                    System::getDialog()->callBtn1(0x50, 0x2E);
                    mState = 0x16;
                }
                else {
                    createChildScene(0x18, this, NULL, NULL);
                    button->reserveAnm(0x10);
                    button->reserveText(0, 0x13B);
                    button->reserveAnm(0xB);
                    button->setEventHandler(NULL, NULL);
                    mpBackLayout->getAnim(0)->play();
                    mState = 0xC;
                }

                button->animation(0x19);
                button->animation(0x1A);
            }
        }

        BOOL Address::isReleasableArea(int page, int buttonNo) {
            if (page < 0 || page >= 0x14) {
                return FALSE;
            }
            if (mbFlagE1) {
                return FALSE;
            }
            if (buttonNo < 0 || buttonNo >= 5) {
                return FALSE;
            }
            if (page == mDragPageNo && buttonNo == mDragButtonNo) {
                return TRUE;
            }
            if (mpFriendList->mbHasInfo[page * 5 + buttonNo]) {
                return FALSE;
            }
            return mbDragging == 1;
        }

        void Address::changePage_onDrag() {
            Button* button = static_cast<Button*>(System::getScene(SCENE_BUTTON));
            if (button->isActive()) {
                button->update();
            }

            if ((mState == 0xA || mState == 1)
                && (System::getControllerManager()->getController(mDragChannel) == NULL
                    || System::getControllerManager()->getController(mDragChannel)->pinch() == 0)) {
                mbDragging = TRUE;
                start_release_event(NULL);
            }
            else {
                set_textbox("T_name_move", (const wchar_t*)mpFriendList->mInfos[mDragPageNo * 5 + mDragButtonNo].attr.name);
                math::VEC2 pos = System::getControllerManager()->getController(mDragChannel)->getDpdProjectionPos();
                if (System::getControllerManager()->getController(mDragChannel) != NULL
                    && System::getControllerManager()->getController(mDragChannel)->isValidDpd()) {
                    nw4r::math::VEC2 v(pos.x - mDragPos.x, pos.y - mDragPos.y);
                    f32 sqLen = v.x * v.x + v.y * v.y;
                    f32 dist;
                    if (sqLen <= 0.0f) {
                        dist = 0.0f;
                    }
                    else {
                        dist = sqLen * nw4r::math::FrSqrt(sqLen);
                    }
                    snd::getSystem()->holdSEwithPosDis("WIPL_SE_CH_DRAG", pos.x, dist);
                    mDragPos = pos;
                }
                nw4r::ut::Rect projRect4x3;
                nw4r::ut::Rect projRect;
                System::getProjectionRect(&projRect);
                System::getProjectionRect4x3(&projRect4x3);
                pos.x = pos.x * ((projRect4x3.right - projRect4x3.left) / (projRect.right - projRect.left));
                pos.x = pos.x + mUnk_0x29C;
                pos.y = -pos.y;
                nw4r::lyt::Pane* pane = mpLayout->FindPaneByName("N_note_move");
                pane->SetTranslate(pos);
                pane->SetVisible(true);
                if (mLeftPageNo >= 0) {
                    mLeftPageNo++;
                }
                if (mRightPageNo >= 0) {
                    mRightPageNo++;
                }
                if (mLeftPageNo >= 0x1E) {
                    button->animation(0x14);
                    snd::getSystem()->startSE("WIPL_SE_FL_PAGE_DEC");
                    onPreviousPage();
                    mLeftPageNo = 0;
                    mRightPageNo = -1;
                }
                else if (mRightPageNo >= 0x1E) {
                    button->animation(0x13);
                    snd::getSystem()->startSE("WIPL_SE_FL_PAGE_INC");
                    onNextPage();
                    mLeftPageNo = -1;
                    mRightPageNo = 0;
                }
            }
        }

        void Address::movePane_onDrag() {
            f32 width = 0.0f;

            nw4r::lyt::Pane* pane = mpLayout->FindPaneByName("N_base_move");
            nw4r::math::VEC3 trans = pane->GetTranslate();
            math::VEC2 pos = System::getControllerManager()->getController(mDragChannel)->getDpdProjectionPos();

            nw4r::lyt::TextBox* textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpLayout->FindPaneByName("T_name_move"));
            if (textBox != NULL) {
                const wchar_t* name = (const wchar_t*)mpFriendList->mInfos[mDragPageNo * 5 + mDragButtonNo].attr.name;
                if (name != NULL) {
                    textBox->GetFont()->GetWidth();
                    for (const wchar_t* p = name; *p != 0; p++) {
                        width += textBox->GetFont()->GetCharWidth(*p);
                    }
                    width = 0.01f + width;
                }
            }

            nw4r::ut::Rect projRect4x3;
            nw4r::ut::Rect projRect;
            System::getProjectionRect(&projRect);
            System::getProjectionRect4x3(&projRect4x3);
            if (trans.x + width < pos.x) {
                mUnk_0x29C = -((trans.x + width) * ((projRect4x3.right - projRect4x3.left) / (projRect.right - projRect.left)));
            }
            else {
                pos.x = pos.x * ((projRect4x3.right - projRect4x3.left) / (projRect.right - projRect.left));
                mUnk_0x29C = -pos.x;
                mUnk_0x29C += (f32)mDragPageNo * sNullVec.x * ((projRect4x3.right - projRect4x3.left) / (projRect.right - projRect.left));
            }
        }

        void AddressEvent::onEvent(u32 compId, u32 event, void* data) {
            gui::PaneComponent* component = static_cast<gui::PaneComponent*>(mpManager->getComponent(compId));
            const char* paneName = component->getPane()->GetName();
            controller::Interface* con = static_cast<controller::Interface*>(data);

            switch (event) {
                case ON_POINT: {
                    if (con != NULL) {
                        if (mpInstance->mbDragging) {
                            if (con == NULL || con == System::getControllerManager()->getController(mpInstance->mDragChannel)) {
                                mpInstance->start_drag_point_event(paneName, con);
                            }
                        }
                        else {
                            if (paneName[0] == 'B' && con->getChannel() == mDragChannel) {
                                mDragChannel = -1;
                            }
                            mpInstance->start_point_event(paneName, con);
                        }
                    }
                    break;
                }
                case ON_LEFT: {
                    if (mpInstance->mbDragging) {
                        if (con == NULL || con == System::getControllerManager()->getController(mpInstance->mDragChannel)) {
                            mpInstance->start_drag_left_event(paneName);
                        }
                    }
                    else {
                        mpInstance->start_left_event(paneName);
                    }
                    break;
                }
                case ON_DRAG: {
                    if (mpInstance->mState == 4 && con != NULL && con->decide() && mDragChannel >= 0) {
                        mpInstance->start_trig_event(paneName);
                    }
                    break;
                }
                case ON_TRIG: {
                    if (mpInstance->mState == 4 && con != NULL) {
                        mDragChannel = con->getChannel();
                        if (con->pinchTrg()) {
                            mpInstance->start_drag_event(paneName, con);
                        }
                    }
                    break;
                }
                case ON_RELEASE: {
                    if (mpInstance->mbDragging) {
                        if (con == NULL || con == System::getControllerManager()->getController(mpInstance->mDragChannel)) {
                            if (!con->pinch()) {
                                mpInstance->start_release_event(paneName);
                            }
                        }
                    }
                    break;
                }
            }
        }

        Address::MiiObj::~MiiObj() {
            if (mpNigaoeObj != NULL) {
                delete mpNigaoeObj;
            }
        }

        void Address::MiiObj::init(nw4r::lyt::Pane* pane) {
            mpMaterial = pane->GetMaterial();
            mpMaterial->GetTexture(&mMiiTexObj, 0);
        }

        void Address::MiiObj::set(u64 userId) {
            RFLCreateID data;
            memcpy(&data, &userId, sizeof(data));

            s16 index;
            if (RFLSearchOfficialData(&data, (u16*)&index)) {
                System::getMiiManager()->create(System::getMem2App(),
                    0x4C, 0x4C, index, create_callback, this);
            }
            else {
                reset();
            }
        }

        void Address::MiiObj::reset() {
            if (mpNigaoeObj != NULL) {
                mpMaterial->SetTexture(0, mMiiTexObj);
                delete mpNigaoeObj;
                mpNigaoeObj = NULL;
            }
        }

        void Address::MiiObj::create_callback(nigaoe::Object* obj, void* work) {
            MiiObj* mii = (MiiObj*)work;

            if (mii->mpNigaoeObj != NULL) {
                delete mii->mpNigaoeObj;
            }
            mii->mpNigaoeObj = obj;
            mii->mpMaterial->SetTexture(0, obj->getIconTexture());
        }

        BOOL FriendListCache::init() {
            nwc24::Manager* manager = System::getNwc24Manager();

            if (!manager->open()) {
                return FALSE;
            }

            manager->getMyUserId(&mMyUserId);

            u32 numFriendInfos;
            manager->getNumFriendInfos(&numFriendInfos);
            manager->getNumRegFriendInfos(&mNumRegInfos);

            for (u32 i = 0; i < 100; i++) {
                mbHasInfo[i] = manager->isFriendInfoThere(i);
                if (mbHasInfo[i]) {
                    manager->readFriendInfo(&mInfos[i], i);
                }
            }

            mUnk_0x9D74 = 0;
            mbOpened = TRUE;
            return TRUE;
        }

        void FriendListCache::fin() {
            if (mbOpened) {
                System::getNwc24Manager()->close();
            }
        }

        void FriendListCache::add(u32 index, const NWC24FriendInfo& info) {
            memcpy(&mInfos[index], &info, sizeof(NWC24FriendInfo));
            mbHasInfo[index] = TRUE;
            mNumRegInfos++;

            System::getNwc24Manager()->writeFriendInfo(&mInfos[index], index);
        }

        void FriendListCache::update(u32 index, const wchar_t* name, NWC24UserId userId) {
            mInfos[index].attr.fdId = userId;
            memset(mInfos[index].attr.name, 0, sizeof(mInfos[index].attr.name));
            wcsncpy((wchar_t*)mInfos[index].attr.name, name, 0xA);

            System::getNwc24Manager()->updateFriendInfo(&mInfos[index], index);
        }

        void FriendListCache::del(u32 index) {
            mbHasInfo[index] = FALSE;
            mNumRegInfos--;

            System::getNwc24Manager()->deleteFriendInfo(index);
        }

        void FriendListCache::swap(u32 indexA, u32 indexB) {
            NWC24FriendInfo work ALIGN32;

            memcpy(&work, &mInfos[indexA], sizeof(NWC24FriendInfo));
            memcpy(&mInfos[indexA], &mInfos[indexB], sizeof(NWC24FriendInfo));
            memcpy(&mInfos[indexB], &work, sizeof(NWC24FriendInfo));

            u8 hasInfo = mbHasInfo[indexA];
            mbHasInfo[indexA] = mbHasInfo[indexB];
            mbHasInfo[indexB] = hasInfo;

            System::getNwc24Manager()->swapFriendInfo(indexA, indexB);
        }

        BOOL FriendListCache::isValidId(const NWC24UserId& userId) {
            return System::getNwc24Manager()->checkUserId(userId);
        }

        BOOL FriendListCache::isDupId(const NWC24UserId& userId) {
            for (int i = 0; i < 100; i++) {
                if (mbHasInfo[i] && mInfos[i].attr.type == NWC24_FRIENDTYPE_WII &&
                    mInfos[i].addr.wiiId == userId) {
                    return TRUE;
                }
            }
            return FALSE;
        }

        BOOL FriendListCache::isDupMail(const char* mailAddr) {
            for (int i = 0; i < 100; i++) {
                if (mbHasInfo[i] && mInfos[i].attr.type == NWC24_FRIENDTYPE_EMAIL) {
                    const char* mail = mInfos[i].addr.mailAddr;
                    if (strcmp(mail, mailAddr) == 0) {
                        return TRUE;
                    }
                }
            }
            return FALSE;
        }

        void FriendListCache::sendRegisterMail(u32 index) {
            wchar_t idStr[0x11];
            NWC24MsgObj msgObj;
            wchar_t text[0x400];

            const NWC24FriendInfo* info = &mInfos[index];
            nwc24::Manager* manager = System::getNwc24Manager();

            manager->initMsgObj(&msgObj, NWC24_MSGTYPE_PUBLIC);
            manager->setMsgToAddr(&msgObj, info->addr.mailAddr, strlen(info->addr.mailAddr));

            const wchar_t* subject = System::getMessage(0x181);
            wcscpy(text, System::getMessage(0x182));

            if (mMyUserId != 0x000462D53C8ABAC0ULL) {
                const wchar_t* needle = L"1234567890123456";
                swprintf(idStr, 0x11, L"%016lld", mMyUserId);

                wchar_t* p;
                while ((p = wcsstr(text, needle)) != NULL) {
                    for (int i = 0; i < 0x10; i++) {
                        p[i] = idStr[i];
                    }
                }
            }

            memset(unk_0x7D74, 0, sizeof(unk_0x7D74));
            manager->setMsgSubjectAndTextPublic(&msgObj, (u16*)subject, wcslen(subject), (u16*)text, wcslen(text), unk_0x7D74, sizeof(unk_0x7D74));
            manager->commitMsg(&msgObj);
        }

        int FriendListCache::check() {
            return mUnk_0x9D74 = System::getNwc24Manager()->check(1);
        }

        int FriendListCache::getErrCode() const {
            return System::getNwc24Manager()->getErrCode();
        }
    }
}
