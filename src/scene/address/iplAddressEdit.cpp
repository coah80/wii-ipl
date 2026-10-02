#define IPL_ADDRESS_EDIT_CPP
#include "scene/address/iplAddressEdit.h"
#include "scene/address/iplAddress.h"
#include "scene/board/iplBoard.h"
#include "scene/faceSelect/iplFaceSelect.h"
#include "scene/parentalDialog/iplParentalDialog.h"
#include "scene/iplSceneManager.h"

#include "layout/iplGuiManager.h"
#include "scene/textBalloon/iplBalloon.h"
#include "sound/iplSound.h"
#include "system/iplSystem.h"
#include "system/iplNigaoe.h"
#include "scene/setting/iplNCDSetting.h"
#include "utility/iplCharacterCode.h"

#include <private/nwc24/NWC24Std.h>
#include <revolution/nwc24.h>

#include <string.h>

static inline bool matchesInputPane(const char* paneName, const char* inputPaneName) {
    return strcmp(paneName, inputPaneName) == 0;
}

typedef s32 ChkHostNameError;

enum {
    CHECK_HOSTNAME_DOT_AT_END = -8,
    CHECK_HOSTNAME_OUT_OF_RANGE,
    CHECK_HOSTNAME_INVALID_CHARACTERS,
    CHECK_HOSTNAME_MULTIPLE_DOTS,
    CHECK_HOSTNAME_INCORRECT,
    CHECK_HOSTNAME_IS_EMPTY,
    CHECK_HOSTNAME_IS_NULL,
    CHECK_HOSTNAME_BAD_LENGTH,
    CHECK_HOSTNAME_SUCCESS
};

static ChkHostNameError CheckHostName(const char* hostName, u32 hostNameLength);

static const char* sButtonPaneNames[5] = {
    "B_crd_btn_00", "B_crd_btn_10", "B_crd_btn_11", "B_mii_icon_00", "B_card_beta"
};

static const char* sInputPaneName = "B_crd_edgi_00";

namespace ipl {
    namespace scene {
        class AddressEditEvent : public ::gui::EventHandler {
        public:
            AddressEditEvent(AddressEdit* parent) : mpParent(parent) {}

            virtual void onEvent(u32 componentId, u32 event, void* data);

        private:
            AddressEdit* mpParent;
        };

        class AddressInputEvent : public ::gui::EventHandler {
        public:
            AddressInputEvent(AddressEdit* parent) : mpParent(parent) {}

            virtual void onEvent(u32 componentId, u32 event, void* data);

        private:
            AddressEdit* mpParent;
        };
    }
}

ipl::keyboard::Manager::KeyboardSetting::KeyboardSetting(
    ipl::keyboard::Manager::KeyboardType keyboardType, const wchar_t* value, u32 limit, u32 rows) {
    type = keyboardType;
    wcString = value;
    stringLimit = limit;
    rowLimit = rows;
}

ipl::scene::AddressEdit::AddressEdit(EGG::Heap* heap, int friendCode)
    : FaderSceneBase(heap), ButtonEventHandlerBase() {
    mMode = friendCode;
    mSelectedButton = -1;
    mSubState = -1;
    mSelectedFriend = 0;
    mString.mpCallbackOwner = this;
    mString.clear();
    mbParentalOK = false;
    mpNigaoe = NULL;
    mNigaoeState = 0;
    setSceneParentFlags(3);
    for (int i = 0; i < 5; ++i) {
        mPointCount[i] = 0;
    }
    for (int i = 0; i < 8; ++i) {
        mCreateID.data[i] = 0;
    }
}

ipl::scene::AddressEdit::~AddressEdit() {
    if (mpNigaoe != NULL) {
        delete mpNigaoe;
    }
}

void ipl::scene::AddressEdit::stt_msg_code_add() {
    if (System::getDialog()->getLastResult() == DialogWindow::RESULT_BUTTON) {
        mState = 0x22;
    }
}

void ipl::scene::AddressEdit::stt_msg_code_edit() {
    if (System::getDialog()->getLastResult() == DialogWindow::RESULT_BUTTON) {
        mState = 0;
    }
}

void ipl::scene::AddressEdit::stt_msg_parental() {
    if (System::getDialog()->getLastResult() == DialogWindow::RESULT_BUTTON) {
        mState = 0;
    }
}

void ipl::scene::AddressEdit::stt_msg_nwc24_error() {
    if (System::getDialog()->getLastResult() == DialogWindow::RESULT_BUTTON) {
        mState = 0;
    }
}

void ipl::scene::AddressEdit::reset_gui() {
    mpEditGui->init();
    mpInputGui->init();
    for (s32 i = 0; i < 5; ++i) {
        if (mPointCount[i] > 0) {
            ipl::layout::Animator* animator = mpCodeLayout->getAnim(i + 0xb);
            animator->play();
            mPointCount[i] = 0;
        }
    }
}


extern "C" void* __nw__FUl(u32);
extern "C" BOOL RFLSearchOfficialData(const RFLCreateID*, u16*);

namespace ipl {
    namespace scene {
        NWC24FriendInfo sFriendInfo;
    }
}
extern "C" const char* smButtonName__Q33ipl5scene6Button[];










int ipl::scene::AddressEdit::get_button_no(const char*);








extern "C" NWC24Err NWC24CheckPublicMailAddr_(const char*);










































void ipl::scene::AddressEdit::stt_msg_no_established() {
    switch (ipl::System::getDialog()->getLastResult()) {
    case 1:
        reset_gui();
        mState = 0;
        break;
    default:
        break;
    }
}

void ipl::scene::AddressEdit::stt_msg_code_invalid() {
    ipl::System::getScene(5);
    switch (ipl::System::getDialog()->getLastResult()) {
    case 1:
        mState = 0x11;
        break;
    default:
        break;
    }
}

void ipl::scene::AddressEdit::stt_msg_dup_wii_no() {
    ipl::System::getScene(5);
    switch (ipl::System::getDialog()->getLastResult()) {
    case 1:
        mState = 0x11;
        break;
    default:
        break;
    }
}

void ipl::scene::AddressEdit::stt_msg_dup_email() {
    ipl::System::getScene(5);
    switch (ipl::System::getDialog()->getLastResult()) {
    case 1:
        mState = 0x11;
        break;
    default:
        break;
    }
}

void ipl::scene::AddressEdit::stt_msg_my_wii_no() {
    ipl::System::getScene(5);
    switch (ipl::System::getDialog()->getLastResult()) {
    case 1:
        mState = 0x11;
        break;
    default:
        break;
    }
}

void ipl::scene::AddressEdit::stt_msg_no_mii_add() {
    ipl::System::getScene(5);
    switch (ipl::System::getDialog()->getLastResult()) {
    case 1:
        mState = 0x1d;
        break;
    default:
        break;
    }
}

void ipl::scene::AddressEdit::stt_msg_add_rlt() {
    ipl::scene::Button* button = static_cast<ipl::scene::Button*>(ipl::System::getScene(5));
    switch (ipl::System::getDialog()->getLastResult()) {
    case 1:
        button->reserveAnm(0xf);
        mState = 0x30;
        break;
    default:
        break;
    }
}

void ipl::scene::AddressEdit::stt_add_code_normal() {
    ipl::scene::Button* button = static_cast<ipl::scene::Button*>(ipl::System::getScene(5));
    if (button->isActive()) {
        button->update();
    }
    if (mState == 0x11) {
        mpInputGui->update();
    }
}

void ipl::scene::AddressEdit::stt_add_name_normal() {
    ipl::scene::Button* button = static_cast<ipl::scene::Button*>(ipl::System::getScene(5));
    if (button->isActive()) {
        button->update();
    }
    if (mState == 0x19) {
        mpInputGui->update();
    }
}

const wchar_t* ipl::scene::AddressEdit::String::getDispCodeLong() const {
    if (!mbHasWiiNo) {
        return;
    }
    return mDisplayText;
}

void ipl::scene::AddressEdit::String::clear() {
    memset(mValue, 0, sizeof(mValue));
    memset(mName, 0, sizeof(mName));
    memset(mDisplayText, 0, sizeof(mDisplayText));
    mbValidMail = false;
    mbNameNotEmpty = false;
    mbHasWiiNo = false;
}



void ipl::scene::AddressEdit::String::setWiiNo(const wchar_t* value) {
    mbHasWiiNo = true;
    memset(mValue, 0, sizeof(mValue));
    wcsncpy(mValue, value, 0x10);
    memset(mDisplayText, 0, sizeof(mDisplayText));

    for (s32 i = 0; i < 0x10; ++i) {
        wchar_t digit = value[i];
        if (digit >= L'0' && digit <= L'9') {
            mDisplayText[i + i / 4] = digit;
        } else {
            mDisplayText[i + i / 4] = L'?';
        }
    }
    mDisplayText[14] = L' ';
    mDisplayText[9] = L' ';
    mDisplayText[4] = L' ';

    bool valid = false;
    if (wcslen(value) == 0x10) {
        u64 userId = AddressEdit::utf16_wiiid(value);
        if (mpCallbackOwner->mpFriendCache->isValidId(userId)) {
            valid = true;
        }
    }
    mbValidMail = valid;
}

BOOL ipl::scene::AddressEdit::String::isDupCode() const {
    if (mbHasWiiNo) {
        u64 userId = AddressEdit::utf16_wiiid(mValue);
        return mpCallbackOwner->mpFriendCache->isDupId(userId);
    }

    u8 mail[0x101];
    memset(mail, 0, sizeof(mail));
    ipl::utility::CharacterCode::UTF16ToANSI(mail, mValue, 0x100);
    return mpCallbackOwner->mpFriendCache->isDupMail(reinterpret_cast<const char*>(mail));
}

BOOL ipl::scene::AddressEdit::String::isMyCode() const {
    if (mbHasWiiNo) {
        NWC24UserId myUserId = mpCallbackOwner->mpFriendCache->getMyUserId();
        return AddressEdit::utf16_wiiid(mValue) == myUserId;
    }
    return false;
}

void ipl::scene::AddressEdit::prepare() {
    mpBalloonFile = ipl::System::getNandManager()->readLayoutAsync(
        getSceneHeap(), "balloon.ash", false);
}

void ipl::scene::AddressEdit::create() {

    ipl::nand::LayoutFile* boardFile =
        static_cast<ipl::scene::Board*>(ipl::System::getScene(4))->getLayoutFile();

    ipl::layout::Object* bLayout =
        new ipl::layout::Object(getHeap(), boardFile, "arc", "th_Adress_b.brlyt");
    bLayout->bindToGroup("th_Adress_b_card_strt.brlan", "card_strt_fnsh", false, true);
    bLayout->bindToGroup("th_Adress_b_btn_in.brlan", "crd_btn_00", false, true);
    bLayout->bindToGroup("th_Adress_b_btn_in.brlan", "crd_btn_10", false, false);
    bLayout->bindToGroup("th_Adress_b_btn_in.brlan", "crd_btn_11", false, false);
    bLayout->bindToGroup("th_Adress_b_btn_in.brlan", "mii_icon_00", false, false);
    bLayout->bind("th_Adress_b_btn_in.brlan", "T_frnd_crd_00", false, false);
    bLayout->bindToGroup("th_Adress_b_btn_psh.brlan", "crd_btn_00", false, false);
    bLayout->bindToGroup("th_Adress_b_btn_psh.brlan", "crd_btn_10", false, false);
    bLayout->bindToGroup("th_Adress_b_btn_psh.brlan", "crd_btn_11", false, false);
    bLayout->bindToGroup("th_Adress_b_btn_psh.brlan", "mii_icon_00", false, false);
    bLayout->bind("th_Adress_b_btn_psh.brlan", "T_frnd_crd_00", false, false);
    bLayout->bindToGroup("th_Adress_b_btn_out.brlan", "crd_btn_00", false, false);
    bLayout->bindToGroup("th_Adress_b_btn_out.brlan", "crd_btn_10", false, true);
    bLayout->bindToGroup("th_Adress_b_btn_out.brlan", "crd_btn_11", false, true);
    bLayout->bindToGroup("th_Adress_b_btn_out.brlan", "mii_icon_00", false, true);
    bLayout->bind("th_Adress_b_btn_out.brlan", "T_frnd_crd_00", false, true);
    bLayout->bindToGroup("th_Adress_b_btn_scl_in.brlan", "crd_btn_00", false, false);
    bLayout->bindToGroup("th_Adress_b_btn_scl_in.brlan", "crd_btn_10", false, false);
    bLayout->bindToGroup("th_Adress_b_btn_scl_in.brlan", "crd_btn_11", false, false);
    bLayout->bindToGroup("th_Adress_b_btn_scl_in.brlan", "mii_icon_00", false, false);
    bLayout->bind("th_Adress_b_btn_scl_in.brlan", "T_frnd_crd_00", false, false);
    bLayout->bindToGroup("th_Adress_b_btn_scl_out.brlan", "crd_btn_00", false, true);
    bLayout->bindToGroup("th_Adress_b_btn_scl_out.brlan", "crd_btn_10", false, true);
    bLayout->bindToGroup("th_Adress_b_btn_scl_out.brlan", "crd_btn_11", false, true);
    bLayout->bindToGroup("th_Adress_b_btn_scl_out.brlan", "mii_icon_00", false, true);
    bLayout->bind("th_Adress_b_btn_scl_out.brlan", "T_frnd_crd_00", false, true);
    bLayout->bindToGroup("th_Adress_b_btn_scl_in.brlan", "crd_btn_gry", false, true);
    bLayout->bindToGroup("th_Adress_b_btn_scl_out.brlan", "crd_btn_gry", false, false);
    bLayout->bindToGroup("th_Adress_b_card_msg_alp_in.brlan", "card_msg", false, true);
    bLayout->bindToGroup("th_Adress_b_card_msg_alp_out.brlan", "card_msg", false, false);
    bLayout->bindToGroup("th_Adress_b_card_fnsh.brlan", "card_strt_fnsh", false, false);
    bLayout->finishBinding();

    ipl::scene::AddressEditEvent* editEvent = new ipl::scene::AddressEditEvent(this);
    ipl::gui::PaneManager* editManager = new ipl::gui::PaneManager(
        static_cast< ::gui::EventHandler*>(editEvent), bLayout->getDrawInfo(), NULL, NULL, false);
    editManager->setupScene(bLayout);
    editManager->setAllComponentTriggerTarget(false);
    for (s32 i = 0; i < 5; i++) {
        const char* paneName = sButtonPaneNames[i];
        nw4r::lyt::Pane* pane = bLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(paneName, true);
        editManager->setTriggerTarget(pane, true);
    }
    mpCodeLayout = bLayout;
    mpEditEvent = editEvent;
    mpEditGui = editManager;

    nw4r::lyt::Pane* textPane = bLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_crd_btn_00", true);
    set_textbox(textPane, ipl::System::getMessage(0x2a));
    textPane = (mpCodeLayout)
        ->getNW4RLyt()->GetRootPane()->FindPaneByName("T_crd_btn_10", true);
    set_textbox(textPane, ipl::System::getMessage(0x2b));
    textPane = (mpCodeLayout)
        ->getNW4RLyt()->GetRootPane()->FindPaneByName("T_crd_btn_11", true);
    set_textbox(textPane, ipl::System::getMessage(0x2f));
    textPane = (mpCodeLayout)
        ->getNW4RLyt()->GetRootPane()->FindPaneByName("T_crd_btn_gry", true);
    set_textbox(textPane, ipl::System::getMessage(0x2a));
    textPane = (mpCodeLayout)
        ->getNW4RLyt()->GetRootPane()->FindPaneByName("T_card_msg_00", true);
    set_textbox(textPane, L"");
    textPane = (mpCodeLayout)
        ->getNW4RLyt()->GetRootPane()->FindPaneByName("T_name_00", true);
    set_textbox(textPane, L"");
    textPane = (mpCodeLayout)
        ->getNW4RLyt()->GetRootPane()->FindPaneByName("T_frnd_crd_00", true);
    set_textbox(textPane, L"");

    ipl::layout::Object* cLayout =
        new ipl::layout::Object(getHeap(), boardFile, "arc", "th_Adress_c.brlyt");
    cLayout->bindToGroup("th_Adress_c_card_strt.brlan", "G_card_strt_fnsh", false, true);
    cLayout->bindToGroup("th_Adress_c_question_alp_in.brlan", "G_question_00", false, true);
    cLayout->bindToGroup("th_Adress_c_name_alp_in.brlan", "G_name_00", false, true);
    cLayout->bindToGroup("th_Adress_c_msg_alp_in.brlan", "G_msg_00", false, true);
    cLayout->bindToGroup("th_Adress_c_mii_alp_in.brlan", "G_mii", false, true);
    cLayout->bindToGroup("th_Adress_c_question_alp_out.brlan", "G_question_00", false, false);
    cLayout->bindToGroup("th_Adress_c_name_alp_out.brlan", "G_name_00", false, false);
    cLayout->bindToGroup("th_Adress_c_msg_alp_out.brlan", "G_msg_00", false, false);
    cLayout->bindToGroup("th_Adress_c_mii_alp_out.brlan", "G_mii", false, false);
    cLayout->bindToGroup("th_Adress_c_card_fnsh.brlan", "G_card_strt_fnsh", false, false);
    cLayout->finishBinding();

    ipl::scene::AddressInputEvent* inputEvent = new ipl::scene::AddressInputEvent(this);
    ipl::gui::PaneManager* inputManager = new ipl::gui::PaneManager(
        static_cast< ::gui::EventHandler*>(inputEvent), cLayout->getDrawInfo(), NULL, NULL, false);
    inputManager->setupScene(cLayout);
    inputManager->setAllComponentTriggerTarget(false);
    textPane = cLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(sInputPaneName, true);
    inputManager->setTriggerTarget(textPane, true);
    mpNameLayout = cLayout;
    mpInputEvent = inputEvent;
    mpInputGui = inputManager;

    ipl::layout::Object* background =
        new ipl::layout::Object(getHeap(), boardFile, "arc", "my_Back_a.brlyt");
    mpBackgroundLayout = background;
    background->bind("my_Back_a_Apear.brlan", "Picture_00", false, true);
    (mpBackgroundLayout)
        ->bind("my_Back_a_Lost.brlan", "Picture_00", false, false);
    (mpBackgroundLayout)->finishBinding();
    (mpBackgroundLayout)
        ->getAnim(0)->initAnmFrame();

    mString.clear();
    memset(&ipl::scene::sFriendInfo, 0, sizeof(ipl::scene::sFriendInfo));
    mpNigaoe = 0;
    mNigaoeState = 0;
    ipl::scene::SceneObj* addressScene = ipl::System::getScene(0x14);
    ipl::scene::Address* address = static_cast<ipl::scene::Address*>(addressScene);
    mpFriendCache = address->getFriendCache();

    s32 mode = mMode;
    ipl::layout::Animator* animator;
    switch (mode) {
    case 0: {
        mSelectedFriend = address->getChosenFriendIndex();
        get_friendinfo();
        u32 friendIndex = mSelectedFriend;
        if (mpFriendCache->getInfo(friendIndex).attr.status == 2) {
            (mpCodeLayout)->getAnim(0x15)->initAnmFrame();
            (mpCodeLayout)->getAnim(0x1a)->initAnmFrame();
        } else {
            (mpCodeLayout)->getAnim(0x10)->initAnmFrame();
            (mpCodeLayout)->getAnim(0x1b)->initAnmFrame();
        }
        animator = (mpCodeLayout)->getAnim(0);
        animator->initFrame();
        const wchar_t* friendText = mString.mName;
        animator->restart();
        textPane = (mpCodeLayout)
            ->getNW4RLyt()->GetRootPane()->FindPaneByName("T_name_00", true);
        set_textbox(textPane, friendText);
        textPane = (mpCodeLayout)
            ->getNW4RLyt()->GetRootPane()->FindPaneByName("T_frnd_crd_00", true);
        friendText = mString.mDisplayText;
        set_textbox(textPane, friendText);
        mState = 0;
            break;
    }
    case 1: {
        animator = (mpNameLayout)->getAnim(0);
        animator->initFrame();
        animator->restart();
        animator = (mpNameLayout)->getAnim(1);
        animator->initFrame();
        animator->restart();
        animator = (mpNameLayout)->getAnim(3);
        animator->initFrame();
        animator->restart();
        (mpCodeLayout)->getAnim(0x1a)->initAnmFrame();
        (mpCodeLayout)->getAnim(0x10)->initAnmFrame();
        textPane = (mpNameLayout)
            ->getNW4RLyt()->GetRootPane()->FindPaneByName("T_question_00", true);
        set_textbox(textPane, ipl::System::getMessage(0x31));
        textPane = (mpNameLayout)
            ->getNW4RLyt()->GetRootPane()->FindPaneByName("T_msg_00", true);
        set_textbox(textPane, ipl::System::getMessage(0x47));
        mState = 0x10;
            break;
    }
    case 2: {
        animator = (mpNameLayout)->getAnim(0);
        animator->initFrame();
        animator->restart();
        animator = (mpNameLayout)->getAnim(1);
        animator->initFrame();
        animator->restart();
        animator = (mpNameLayout)->getAnim(3);
        animator->initFrame();
        animator->restart();
        (mpCodeLayout)->getAnim(0x1a)->initAnmFrame();
        (mpCodeLayout)->getAnim(0x10)->initAnmFrame();
        textPane = (mpNameLayout)
            ->getNW4RLyt()->GetRootPane()->FindPaneByName("T_question_00", true);
        set_textbox(textPane, ipl::System::getMessage(0x3f));
        textPane = (mpNameLayout)
            ->getNW4RLyt()->GetRootPane()->FindPaneByName("T_msg_00", true);
        set_textbox(textPane, ipl::System::getMessage(0x48));
        mState = 0x10;
            break;
    }
    default:
        break;
    }

create_mode_done:

    s16 miiIndex[2];
    if (RFLSearchOfficialData(&mCreateID,
            reinterpret_cast<u16*>(miiIndex))) {
        ipl::System::getMiiManager()->create(ipl::System::getMem2App(), 0x4c, 0x4c, miiIndex[0],
            ipl::scene::AddressEdit::nigaoe_create_callback_edit, this);
        mNigaoeState = 1;
    }

    ipl::System::getKeyboard()->init();

    ipl::scene::TextBalloon* balloon = reinterpret_cast<ipl::scene::TextBalloon*>(__nw__FUl(0x3c));
    if (balloon != NULL) {
        f32 balloonWidth = 30.0f;
        f32 balloonHeight = 120.0f;
        EGG::Heap* heap = getHeap();
        ipl::math::VEC3 position(0.0f, 0.0f, 0.0f);
        balloon = new (balloon) ipl::scene::TextBalloon(heap, mpBalloonFile, "arc", "my_IplTopBalloon_a.brlyt", position, balloonHeight, balloonWidth);
    }
    mpBalloon = balloon;
}

void ipl::scene::AddressEdit::stt_wait_decide_anm() {
    nw4r::lyt::Pane* textPane;
    bool complete = true;
    ipl::scene::Button* button = static_cast<ipl::scene::Button*>(ipl::System::getScene(5));
    for (s32 i = 0; i < 5; ++i) {
        u16 index = static_cast<u16>(mSelectedButton + 6);
        complete = (complete & !mpCodeLayout->getAnim(index)->isPlaying()) != 0;
    }
    if (!complete) {
        return;
    }

    switch (mSelectedButton) {
    case 2: {
        if (mpFriendCache->getInfo(mSelectedFriend).attr.status == 2) {
            ipl::layout::Animator* statusAnimator = mpCodeLayout->getAnim(0x15);
            statusAnimator->initFrame();
            statusAnimator->restart();
        } else {
            ipl::layout::Animator* statusAnimator = mpCodeLayout->getAnim(0x1b);
            statusAnimator->initFrame();
            statusAnimator->restart();
        }
        ipl::layout::Animator* animator = mpCodeLayout->getAnim(0x16);
        animator->initFrame();
        animator->restart();
        animator = mpCodeLayout->getAnim(0x17);
        animator->initFrame();
        animator->restart();
        button->reserveAnm(0xc);
        mState = 3;
        mpBalloon->fadeoutForce();
        reset_gui();
        break;
    }
    case 1: {
        button->reserveAnm(0xc);
        button->reserveText(1, 0x2e);
        button->reserveAnm(0xf);
        ipl::layout::Animator* animator = mpNameLayout->getAnim(0);
        animator->initFrame();
        animator->restart();
        animator = mpNameLayout->getAnim(1);
        animator->initFrame();
        animator->restart();
        animator = mpNameLayout->getAnim(2);
        animator->initFrame();
        animator->restart();
        mpNameLayout->getAnim(3)->initAnmFrame();
        animator = mpBackgroundLayout->getAnim(0);
        animator->initFrame();
        animator->restart();
        textPane = mpNameLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(
            "T_question_00", true);
        set_textbox(textPane, ipl::System::getMessage(0x32));
        textPane = mpNameLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_name_00", true);
        set_textbox(textPane, mString.mName);
        textPane = mpNameLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_msg_00", true);
        set_textbox(textPane, ipl::System::getMessage(0x49));
        mpBalloon->fadeoutForce();
        reset_gui();
        mState = 0xc;
        break;
    }
    case 3: {
        if (mNigaoeState != 1) {
            mNigaoeState = 0;
            if (RFLGetAvailableOfficialDataNum() != 0) {
                button->reserveAnm(0xc);
                button->reserveAnm(0xb);
                createChildScene(0x1c, this, 0, reinterpret_cast<void*>(1));
                mState = 0xb;
            } else {
                ipl::System::getDialog()->callBtn1(0x17c, 0x2e);
                mState = 0xa;
            }
            mpBalloon->fadeoutForce();
        }
        break;
    }
    case 0: {
        SCParentalControlsInfo parentalInfo;
        BOOL parentalResult = SCGetParentalControl(&parentalInfo);
        if (!ipl::ncd::NCDSetting::getConnectEnableFlag()) {
            button->animation(0x1d);
            ipl::System::getDialog()->callBtn2(0x144, 0x146, 0x25, false);
            mState = 0x27;
        } else if ((SCGetWCFlags() & 1) == 0) {
            button->animation(0x1d);
            ipl::System::getDialog()->callBtn2(0x17e, 0x146, 0x25, false);
            mState = 0x2a;
        } else if (parentalResult != 0 && (parentalInfo.enable & 0x80) != 0 &&
                   (SCGetNetContentRestrictions() & 2) != 0) {
            button->animation(0x1d);
            ipl::System::getDialog()->callBtn1(0x14c, 0x2e);
            mState = 0x2d;
        } else {
            s32 friendError = mpFriendCache->check();
            if (friendError == NWC24_ERR_NETWORK ||
                mpFriendCache->getLastErr() == NWC24_ERR_SERVER ||
                mpFriendCache->getLastErr() == NWC24_ERR_FULL) {
                wchar_t errorMessage[0x400];
                wchar_t* errorMessagePointer = errorMessage - 1;
                for (s32 i = 0; i < 0x200; i++) {
                    errorMessagePointer[1] = 0;
                    errorMessagePointer += 2;
                    *errorMessagePointer = 0;
                }
                set_err_msg(errorMessage, 0x400,
                    static_cast<NWC24Err>(mpFriendCache->getLastErr()));
                ipl::System::getDialog()->callBtn1(errorMessage, 0x2e);
                button->animation(0x1d);
                mState = 0x2e;
            } else {
                button->reserveAnm(0xc);
                button->reserveText(1, 0x27);
                button->reserveText(0, 0x4f);
                button->reserveAnm(0xf);
                requestSceneChange(0xb, reinterpret_cast<void*>(1));
                ipl::layout::Animator* animator = mpCodeLayout->getAnim(0x1e);
                animator->initFrame();
                animator->restart();
                mState = 0x30;
            }
        }
        mpBalloon->fadeoutForce();
        reset_gui();
        break;
    }
    case 4: {
        ipl::System::getDialog()->callBtn1(mString.getDispCodeLong(), 0x2e);
        mpBalloon->fadeoutForce();
        reset_gui();
        mState = 9;
        break;
    }
    default:
        mState = 0;
        break;
    }
}

void ipl::scene::AddressEdit::stt_wait_delete() {
    ipl::scene::Button* button = static_cast<ipl::scene::Button*>(ipl::System::getScene(5));
    switch (ipl::System::getDialog()->getLastResult()) {
    case 2: {
        delete_friendinfo();
        ipl::layout::Animator* animator = mpCodeLayout->getAnim(0x1d);
        animator->initFrame();
        animator->restart();
        mState = 6;
        break;
    }
    case 1: {
        button->reserveAnm(0xb);
        ipl::layout::Animator* animator = mpCodeLayout->getAnim(0x1d);
        animator->initFrame();
        animator->restart();
        mState = 5;
        break;
    }
    default:
        break;
    }
}

void ipl::scene::AddressEdit::stt_add_confirm_fadein() {
    if (!mpCodeLayout->getAnim(0)->isPlaying()) {
        mState = 0x22;
    }
}

void ipl::scene::AddressEdit::stt_add_name_fadein() {
    if (!mpNameLayout->getAnim(1)->isPlaying() &&
        !mpNameLayout->getAnim(3)->isPlaying() &&
        !mpNameLayout->getAnim(2)->isPlaying()) {
        mState = 0x19;
    }
}

void ipl::scene::AddressEdit::stt_add_mii_fadein() {
    if (!mpNameLayout->getAnim(1)->isPlaying() &&
        !mpNameLayout->getAnim(4)->isPlaying() &&
        !mpNameLayout->getAnim(0)->isPlaying()) {
        mState = 0x1d;
    }
}

void ipl::scene::AddressEdit::stt_add_code_fadein() {
    if (!mpNameLayout->getAnim(0)->isPlaying() &&
        !mpNameLayout->getAnim(1)->isPlaying() &&
        !mpNameLayout->getAnim(3)->isPlaying() &&
        !mpNameLayout->getAnim(4)->isPlaying() &&
        !mpNameLayout->getAnim(2)->isPlaying()) {
        mState = 0x11;
    }
}

void ipl::scene::AddressEdit::stt_add_name_input() {
    ipl::keyboard::Manager::State* state = ipl::System::getKeyboard()->getState();
    ipl::scene::Button* button = static_cast<ipl::scene::Button*>(ipl::System::getScene(5));
    s32 keyboardType = state->iplType;
    if (keyboardType == 3) {
        goto state_disappearing;
    }
    if (keyboardType >= 3) {
        goto state_at_or_after_disappearing;
    }
    if (keyboardType >= 2) {
        goto done;
    }
    if (keyboardType >= 0) {
        goto state_hidden;
    }
    goto done;

state_at_or_after_disappearing:
    if (keyboardType >= 5) {
        goto done;
    }
    goto state_visible;

state_disappearing: {
        BOOL nameWasEmpty = mString.mName[0] == 0;
        if (state->pressOK) {
            mString.setName(state->wcString);
            nw4r::lyt::Pane* pane = mpNameLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(
                "T_name_00", true);
            set_textbox(pane, mString.mName);
        }
        if (mString.mName[0] == 0) {
            if (!nameWasEmpty) {
                ipl::layout::Animator* animator = mpNameLayout->getAnim(6);
                animator->initFrame();
                animator->restart();
                animator = mpNameLayout->getAnim(3);
                animator->initFrame();
                animator->restart();
            }
            button->reserveAnm(0xb);
        } else {
            if (nameWasEmpty) {
                ipl::layout::Animator* animator = mpNameLayout->getAnim(2);
                animator->initFrame();
                animator->restart();
                animator = mpNameLayout->getAnim(7);
                animator->initFrame();
                animator->restart();
            }
            if (mString.mbNameNotEmpty) {
                button->reserveText(1, 0x2e);
                button->reserveAnm(0xf);
            } else {
                button->reserveAnm(0xb);
            }
        }
    }
    goto done;

state_visible: {
        mState = 0x19;
        if (static_cast<u32>(ipl::System::getRegion()) == 6) {
            ipl::System::getKeyboard()->baseMgr()->enableKSXFilter(false);
        }
    }
    goto done;

state_hidden:
    setDefaultTitleText(NULL, ipl::System::getKeyboard()->baseMgr()->isVacancy());

done:
    return;
}

void ipl::scene::AddressEdit::stt_add_mii_normal() {
    ipl::scene::Button* button = static_cast<ipl::scene::Button*>(ipl::System::getScene(5));
    if (button->isActive()) {
        button->update();
    }
    if (mState == 0x1d) {
        mpInputGui->update();
    }
}

void ipl::scene::AddressEdit::stt_add_mii_input() {
    ipl::scene::Base* child = getChild();
    if (child != NULL) {
        ipl::scene::FaceSelect* faceSelect = static_cast<ipl::scene::FaceSelect*>(getChild());
        int faceId = faceSelect->getSelectedFaceId();
        if (faceId >= 0 && ipl::System::getMiiManager()->isAvalable(faceId) &&
            mNigaoeState == 0) {
            RFLAdditionalInfo additionalInfo;
            RFLGetAdditionalInfo(&additionalInfo, RFLDataSource_Official, NULL, faceId);
            if (!RFLiIsSameID(&mCreateID, &additionalInfo.createID)) {
                memcpy(&mCreateID, &additionalInfo.createID, sizeof(mCreateID));
                ipl::System::getMiiManager()->create(ipl::System::getMem2App(), 0x4c, 0x4c, faceId,
                    ipl::scene::AddressEdit::nigaoe_create_callback_add,
                    this);
                mNigaoeState = 1;
                mpInputGui->init();
                mpBalloon->fadeoutForce();
            }
        }
    }

    if (getChild() == NULL &&
        ipl::System::getSceneManager()->getReservedScene() == NULL) {
        static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->setEventHandler(static_cast< ::gui::EventHandler*>(this), NULL);
        mState = 0x1d;
        mNigaoeState = 0;
    }
}

void ipl::scene::AddressEdit::stt_add_mii_fadeout() {
    if (!mpNameLayout->getAnim(9)->isPlaying() &&
        !mpNameLayout->getAnim(5)->isPlaying() &&
        !mpNameLayout->getAnim(8)->isPlaying()) {
        switch (mSubState) {
    case 5: {
        ipl::layout::Animator* animator = mpNameLayout->getAnim(1);
        animator->initFrame();
        animator->restart();
        animator = mpNameLayout->getAnim(2);
        animator->initFrame();
        animator->restart();

        nw4r::lyt::Pane* pane =
            mpNameLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_question_00", true);
        set_textbox(pane, ipl::System::getMessage(0x32));
        pane = mpNameLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_name_00", true);
        set_textbox(pane, mString.mName);
        pane = mpNameLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_msg_00", true);
        set_textbox(pane, ipl::System::getMessage(0x49));
        mState = 0x18;
        break;
    }

    case 7: {
        ipl::layout::Animator* animator = mpCodeLayout->getAnim(0);
        animator->initFrame();
        animator->restart();
        mpCodeLayout->getAnim(0x10)->initAnmFrame();
        mpCodeLayout->getAnim(0x11)->initAnmFrame();
        mpCodeLayout->getAnim(0x12)->initAnmFrame();
        animator = mpCodeLayout->getAnim(0x1c);
        animator->initFrame();
        animator->restart();

        nw4r::lyt::Pane* pane =
            mpCodeLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_card_msg_00", true);
        set_textbox(pane, ipl::System::getMessage(0x44));
        pane = mpCodeLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_name_00", true);
        set_textbox(pane, mString.mName);
        pane = mpCodeLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_frnd_crd_00", true);
        set_textbox(pane, mString.mDisplayText);
        mState = 0x21;
        break;
    }
    default:
        break;
        }
    }
}

void ipl::scene::AddressEdit::stt_ipt_wait_fadeout() {
    if (!mpNameLayout->getAnim(5)->isPlaying() &&
        !mpNameLayout->getAnim(7)->isPlaying() &&
        !mpNameLayout->getAnim(6)->isPlaying() &&
        !mpNameLayout->getAnim(8)->isPlaying() &&
        !mpNameLayout->getAnim(9)->isPlaying() &&
        !mpBackgroundLayout->getAnim(1)->isPlaying()) {
        mState = 0;
    }
}

void ipl::scene::AddressEdit::stt_wait_del_msg_fadeout() {
    if (!mpCodeLayout->getAnim(0x1d)->isPlaying()) {
        u32 friendIndex = mSelectedFriend;
        u32 status = mpFriendCache->getInfo(friendIndex).attr.status;
        if (status == 2) {
            ipl::layout::Animator* animator = mpCodeLayout->getAnim(0x10);
            animator->initFrame();
            animator->restart();
        } else {
            ipl::layout::Animator* animator = mpCodeLayout->getAnim(0x1a);
            animator->initFrame();
            animator->restart();
        }
        ipl::layout::Animator* animator = mpCodeLayout->getAnim(0x11);
        animator->initFrame();
        animator->restart();
        animator = mpCodeLayout->getAnim(0x12);
        animator->initFrame();
        animator->restart();
        mState = 2;
    }
}

void ipl::scene::AddressEdit::stt_msg_no_mii() {
    switch (ipl::System::getDialog()->getLastResult()) {
    case 1:
        mpEditGui->init();
        for (u32 i = 0; i < 5; ++i) {
            mPointCount[i] = 0;
        }
        mState = 0;
        break;
    default:
        break;
    }
}

void ipl::scene::AddressEdit::stt_add_confirm_fadeout() {
    if (mpCodeLayout->getAnim(0x1e)->isPlaying()) {
        return;
    }

    ipl::scene::Button* button = static_cast<ipl::scene::Button*>(ipl::System::getScene(5));
    switch (mSubState) {
    case 5: {
        ipl::utility::FrameController* animator = mpNameLayout->getAnim(0);
        animator->initFrame();
        animator->restart();
        mState = 0x1c;
        break;
    }
    case 7:
        add_friendinfo();
        button->reserveText(1, 0x29);
        static_cast<ipl::scene::Address*>(ipl::System::getScene(0x14))->reset_friend();
        ipl::System::getDialog()->callBtn1(0x4a, 0x2e);
        mState = 0x26;
        break;
    default:
        break;
    }
}

void ipl::scene::AddressEdit::stt_wait_decide_anm_add() {
    bool complete = true;
    for (s32 i = 0; i < 5; ++i) {
        u16 index = static_cast<u16>(mSelectedButton + 6);
        complete = (complete & !mpCodeLayout->getAnim(index)->isPlaying()) != 0;
    }
    if (complete) {
        switch (mSelectedButton) {
        case 4:
            mpEditGui->init();
            ipl::System::getDialog()->callBtn1(mString.getDispCodeLong(), 0x2e);
            mState = 0x25;
            break;
        default:
            break;
        }
    }
}

void ipl::scene::AddressEdit::stt_add_confirm_normal() {
    ipl::scene::Button* button = static_cast<ipl::scene::Button*>(ipl::System::getScene(5));
    if (button->isActive()) {
        button->update();
    }
    if (mState == 0x22) {
        mpEditGui->update();
    }
}

void ipl::scene::AddressEdit::stt_wait_parental() {
    ipl::scene::ParentalDialog* parental =
        static_cast<ipl::scene::ParentalDialog*>(ipl::System::getScene(0x1b));
    if (parental != NULL) {
        switch (parental->getResult()) {
        case 1:
            mbParentalOK = true;
            mState = 0x29;
            break;
        case 2:
        case 3:
            mbParentalOK = false;
            mState = 0x29;
            break;
        default:
            break;
        }
    }
}

void ipl::scene::AddressEdit::stt_wait_parental_wc() {
    ipl::scene::ParentalDialog* parental =
        static_cast<ipl::scene::ParentalDialog*>(ipl::System::getScene(0x1b));
    if (parental != NULL) {
        switch (parental->getResult()) {
        case 1:
            mbParentalOK = true;
            mState = 0x2c;
            break;
        case 2:
        case 3:
            mbParentalOK = false;
            mState = 0x2c;
            break;
        default:
            break;
        }
    }
}

void ipl::scene::AddressEdit::stt_wait_parental_dst() {
    if (getChild() == NULL) {
        if (mbParentalOK) {
            ipl::System::getFader()->fadeOut();
            reserveAllSceneDestruction(0x12, reinterpret_cast<void*>(1));
            mState = 0x30;
        } else {
            static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->animation(0xb);
            static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->setEventHandler(static_cast< ::gui::EventHandler*>(this), NULL);
            mState = 0;
        }
    }
}

void ipl::scene::AddressEdit::stt_wait_parental_dst_wc() {
    if (getChild() == NULL) {
        if (mbParentalOK) {
            ipl::System::getFader()->fadeOut();
            reserveAllSceneDestruction(0x12, reinterpret_cast<void*>(4));
            mState = 0x30;
        } else {
            static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->animation(0xb);
            static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->setEventHandler(static_cast< ::gui::EventHandler*>(this), NULL);
            mState = 0;
        }
    }
}

void ipl::scene::AddressEdit::stt_msg_net() {
    switch (ipl::System::getDialog()->getLastResult()) {
    case 2:
        mState = 0;
        break;
    case 1: {
        SCParentalControlsInfo info;
        if (SCGetParentalControl(&info) && (info.enable & SC_PARENTAL_FLAG_ENABLED)) {
            static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->setEventHandler(NULL, NULL);
            static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->animation(0xc);
            createChildScene(0x1b, this, NULL, reinterpret_cast<void*>(1));
            mbParentalOK = false;
            mState = 0x28;
        } else {
            ipl::System::getFader()->fadeOut();
            reserveAllSceneDestruction(0x12, reinterpret_cast<void*>(1));
            mState = 0x30;
        }
        break;
    }
    default:
        break;
    }
}

void ipl::scene::AddressEdit::stt_msg_wc() {
    switch (ipl::System::getDialog()->getLastResult()) {
    case 2:
        mState = 0;
        break;
    case 1: {
        SCParentalControlsInfo info;
        if (SCGetParentalControl(&info) && (info.enable & SC_PARENTAL_FLAG_ENABLED)) {
            static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->setEventHandler(NULL, NULL);
            static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->animation(0xc);
            createChildScene(0x1b, this, NULL, reinterpret_cast<void*>(1));
            mbParentalOK = false;
            mState = 0x2b;
        } else {
            ipl::System::getFader()->fadeOut();
            reserveAllSceneDestruction(0x12, reinterpret_cast<void*>(4));
            mState = 0x30;
        }
        break;
    }
    default:
        break;
    }
}

void ipl::scene::AddressEdit::stt_select_mii() {
    if (getChild() != NULL) {
        ipl::scene::FaceSelect* faceSelect =
            static_cast<ipl::scene::FaceSelect*>(getChild());
        int faceId = faceSelect->getSelectedFaceId();
        if (faceId >= 0 && ipl::System::getMiiManager()->isAvalable(faceId) &&
            mNigaoeState == 0) {
            RFLAdditionalInfo info;
            RFLGetAdditionalInfo(&info, RFLDataSource_Official, NULL, faceId);
            if (!RFLiIsSameID(&mCreateID, &info.createID)) {
                memcpy(&mCreateID, &info.createID, sizeof(mCreateID));
                ipl::System::getMiiManager()->create(
                    ipl::System::getMem2App(), 0x4c, 0x4c, faceId,
                    ipl::scene::AddressEdit::nigaoe_create_callback_edit,
                    this);
                mNigaoeState = 1;
                update_friendinfo();
            }
        }
    }

    if (getChild() == NULL && ipl::System::getReservedScene() == NULL) {
        static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->setEventHandler(static_cast< ::gui::EventHandler*>(this), NULL);
        mState = 0;
        mNigaoeState = 0;
        mpEditGui->init();
        for (u32 i = 0; i < 5; ++i) {
            mPointCount[i] = 0;
        }
    }
}

void ipl::scene::AddressEdit::set_textbox(nw4r::lyt::Pane* pane, const wchar_t* text) {
    nw4r::lyt::TextBox* textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(pane);
    textBox->SetString(text, 0);
}

void ipl::scene::AddressEdit::setDefaultTitleText(const wchar_t* text, bool flag) {
    if (!flag && (text == NULL || *text != L'\0')) {
        goto set_empty_title;
    }
    switch (mState) {
    case 0xe:
    case 0x1a:
        ipl::System::getKeyboard()->baseMgr()->setTitleText(ipl::System::getMessage(0x15e));
        return;
    case 0x12:
        ipl::System::getKeyboard()->baseMgr()->setTitleText(ipl::System::getMessage(0x15d));
        break;
    }
    return;

set_empty_title:
    ipl::System::getKeyboard()->baseMgr()->setTitleText(L"");
}

void ipl::scene::AddressEditEvent::onEvent(u32 componentId, u32 event, void* data) {
    s32 signedEvent = static_cast<s32>(event);
    ::gui::Manager* manager = mpManager;
    ::gui::PaneComponent* component =
        static_cast< ::gui::PaneComponent*>(manager->getComponent(componentId));
    const char* paneName = component->getPane()->GetName();

    switch (signedEvent) {
    case 1:
        if (data != NULL) {
            mpParent->start_point_event(paneName, static_cast<ipl::controller::Interface*>(data));
        }
        break;
    case 2:
        mpParent->start_left_event(paneName);
        break;
    case 0:
        if (data != NULL &&
            static_cast<ipl::controller::Interface*>(data)->downTrg(0x100800)) {
            mpParent->start_trig_event(paneName);
        }
        break;
    default:
        break;
    }
}

void ipl::scene::AddressInputEvent::onEvent(u32 componentId, u32 event, void* data) {
    s32 signedEvent = static_cast<s32>(event);
    ::gui::Manager* manager = mpManager;
    ::gui::PaneComponent* component =
        static_cast< ::gui::PaneComponent*>(manager->getComponent(componentId));
    const char* paneName = component->getPane()->GetName();

    switch (signedEvent) {
    case 0:
        if (data != NULL &&
            static_cast<ipl::controller::Interface*>(data)->downTrg(0x100800)) {
            mpParent->start_ipt_trig_event(
                paneName, static_cast<ipl::controller::Interface*>(data)->getChannel());
        }
        break;
    case 1:
        if (data != NULL) {
            mpParent->start_ipt_point_event(
                paneName, static_cast<ipl::controller::Interface*>(data)->getChannel());
        }
        break;
    case 2:
        if (data != NULL) {
            mpParent->start_ipt_left_event(
                paneName, static_cast<ipl::controller::Interface*>(data)->getChannel());
        }
        break;
    default:
        break;
    }
}

void ipl::scene::AddressEdit::nigaoe_create_callback_edit(ipl::nigaoe::Object* object, void* callbackWork) {
    ipl::scene::AddressEdit* self = static_cast<ipl::scene::AddressEdit*>(callbackWork);
    if (self->mpNigaoe != NULL) {
        delete self->mpNigaoe;
    }
    self->mpNigaoe = object;
    nw4r::lyt::Pane* pane = self->mpCodeLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(
        "mii_icon_00", true);
    pane->GetMaterial()->SetTexture(0, object->getIconTexture());
    self->mNigaoeState = 2;
    self->mpBalloon->init(object->getName(), 0xa);
}

void ipl::scene::AddressEdit::nigaoe_create_callback_add(ipl::nigaoe::Object* object, void* callbackWork) {
    ipl::scene::AddressEdit* self = static_cast<ipl::scene::AddressEdit*>(callbackWork);
    if (self->mpNigaoe != NULL) {
        delete self->mpNigaoe;
    }
    self->mpNigaoe = object;
    nw4r::lyt::Pane* pane = self->mpNameLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(
        "mii_icon_00", true);
    pane->GetMaterial()->SetTexture(0, object->getIconTexture());
    pane = self->mpCodeLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("mii_icon_00", true);
    pane->GetMaterial()->SetTexture(0, object->getIconTexture());
    self->mNigaoeState = 2;
    self->mpBalloon->init(object->getName(), 0xa);
}

ipl::scene::FaderSceneCommand ipl::scene::AddressEdit::calcFadein() {
    FaderSceneCommand command = FADER_SCN_CONTINUE;
    if (!mpCodeLayout->getAnim(0)->isPlaying() && !mpNameLayout->getAnim(0)->isPlaying()) {
        command = FADER_SCN_NEXT;
    }
    return command;
}

void ipl::scene::AddressEdit::initCalcNormal() {
    static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->setEventHandler(this);
}

ipl::scene::FaderSceneCommand ipl::scene::AddressEdit::calcNormal() {
    switch (mState) {
        case 0:
            stt_normal();
            break;
        case 1:
            stt_wait_decide_anm();
            break;
        case 2:
            stt_wait_btn_fadein();
            break;
        case 3:
            stt_wait_btn_fadeout();
            break;
        case 4:
            stt_wait_del_msg_fadein();
            break;
        case 5:
            stt_wait_del_msg_fadeout();
            break;
        case 6:
            stt_wait_del_msg_fadeout_to_rlt();
            break;
        case 7:
            stt_wait_delete();
            break;
        case 8:
            stt_msg_del_rlt();
            break;
        case 9:
            stt_msg_code_edit();
            break;
        case 10:
            stt_msg_no_mii();
            break;
        case 11:
            stt_select_mii();
            break;
        case 12:
            stt_ipt_wait_fadein();
            break;
        case 13:
            stt_ipt_normal();
            break;
        case 14:
            stt_ipt_input();
            break;
        case 15:
            stt_ipt_wait_fadeout();
            break;
        case 16:
            stt_add_code_fadein();
            break;
        case 17:
            stt_add_code_normal();
            break;
        case 18:
            stt_add_code_input();
            break;
        case 19:
            stt_msg_code_invalid();
            break;
        case 20:
            stt_msg_dup_wii_no();
            break;
        case 21:
            stt_msg_dup_email();
            break;
        case 22:
            stt_msg_my_wii_no();
            break;
        case 23:
            stt_add_code_fadeout();
            break;
        case 24:
            stt_add_name_fadein();
            break;
        case 25:
            stt_add_name_normal();
            break;
        case 26:
            stt_add_name_input();
            break;
        case 27:
            stt_add_name_fadeout();
            break;
        case 28:
            stt_add_mii_fadein();
            break;
        case 29:
            stt_add_mii_normal();
            break;
        case 30:
            stt_add_mii_input();
            break;
        case 31:
            stt_msg_no_mii_add();
            break;
        case 32:
            stt_add_mii_fadeout();
            break;
        case 33:
            stt_add_confirm_fadein();
            break;
        case 34:
            stt_add_confirm_normal();
            break;
        case 35:
            stt_add_confirm_fadeout();
            break;
        case 36:
            stt_wait_decide_anm_add();
            break;
        case 37:
            stt_msg_code_add();
            break;
        case 38:
            stt_msg_add_rlt();
            break;
        case 39:
            stt_msg_net();
            break;
        case 40:
            stt_wait_parental();
            break;
        case 41:
            stt_wait_parental_dst();
            break;
        case 42:
            stt_msg_wc();
            break;
        case 43:
            stt_wait_parental_wc();
            break;
        case 44:
            stt_wait_parental_dst_wc();
            break;
        case 45:
            stt_msg_parental();
            break;
        case 46:
            stt_msg_nwc24_error();
            break;
        case 47:
            stt_msg_no_established();
            break;
    }

    switch (mState) {
        case 0:
        case 3:
        case 9:
        case 12:
        case 29:
        case 32:
        case 34:
        case 35:
        case 36:
        case 39:
        case 42:
        case 45:
        case 46:
        case 47:
            mpBalloon->calc();
            break;
    }

    return mState == 0x30
        ? ipl::scene::FADER_SCN_NEXT
        : ipl::scene::FADER_SCN_CONTINUE;
}

void ipl::scene::AddressEdit::stt_add_name_fadeout() {

    if (!mpNameLayout->getAnim(5)->isPlaying() &&
        !mpNameLayout->getAnim(7)->isPlaying() &&
        !mpNameLayout->getAnim(6)->isPlaying() &&
        !mpNameLayout->getAnim(9)->isPlaying()) {
        s32 state = mSubState;
        if (state == 6) {
            goto state_done;
        }
        if (state >= 6) {
            goto state_six_or_more;
        }
        if (state >= 5) {
            goto state_five;
        }
        goto state_done;

    state_six_or_more:
        if (state >= 8) {
            goto state_done;
        }
        goto state_seven;

    state_five: {
        ipl::layout::Animator* pane = mpNameLayout->getAnim(1);
        pane->initFrame();
        pane->restart();
        pane = mpNameLayout->getAnim(2);
        pane->initFrame();
        pane->restart();

        s32 inputType = mMode;
        switch (inputType) {
        case 2:
            goto address_type_two;
        case 1:
            goto address_type_one;
        default:
            goto address_type_common;
        }

    address_type_one: {
        nw4r::lyt::Pane* label = (mpNameLayout)->getNW4RLyt()->GetRootPane()->FindPaneByName(
            "T_question_00", true);
        set_textbox(label, ipl::System::getMessage(0x31));
        label = (mpNameLayout)->getNW4RLyt()->GetRootPane()->FindPaneByName(
            "T_msg_00", true);
        set_textbox(label, ipl::System::getMessage(0x47));
    }
        goto address_type_common;

    address_type_two: {
            nw4r::lyt::Pane* label = (mpNameLayout)->getNW4RLyt()->GetRootPane()->FindPaneByName(
                "T_question_00", true);
            set_textbox(label, ipl::System::getMessage(0x3f));
            label = (mpNameLayout)->getNW4RLyt()->GetRootPane()->FindPaneByName(
                "T_msg_00", true);
            set_textbox(label, ipl::System::getMessage(0x48));
    }

    address_type_common: {
        nw4r::lyt::Pane* label = (mpNameLayout)->getNW4RLyt()->GetRootPane()->FindPaneByName(
            "T_name_00", true);
        set_textbox(label, mString.mDisplayText);
        mState = 0x10;
    }
        goto state_done;
    }

    state_seven: {
        ipl::layout::Animator* pane = mpNameLayout->getAnim(1);
        pane->initFrame();
        pane->restart();
        pane = mpNameLayout->getAnim(4);
        pane->initFrame();
        pane->restart();

        nw4r::lyt::Pane* label = (mpNameLayout)->getNW4RLyt()->GetRootPane()->FindPaneByName(
            "T_question_00", true);
        set_textbox(label, ipl::System::getMessage(0x55));
        label = (mpNameLayout)->getNW4RLyt()->GetRootPane()->FindPaneByName(
            "T_mii_msg_00", true);
        set_textbox(label, ipl::System::getMessage(0x8b));
        mState = 0x1c;
        }
    state_done:
        ;
    }
}

void ipl::scene::AddressEdit::initCalcFadeout() {
    static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->setEventHandler(NULL);
    mpBalloon->calc();
}

void ipl::scene::AddressEdit::calcCommonAfter() {
    mpEditGui->calc();
    mpCodeLayout->calc();
    mpInputGui->calc();
    mpNameLayout->calc();
    mpBackgroundLayout->calc();
}

void ipl::scene::AddressEdit::stt_normal() {
    ipl::scene::Button* button = static_cast<ipl::scene::Button*>(ipl::System::getScene(5));
    if (button->isActive()) {
        button->update();
    }
    if (mState == 0) {
        mpEditGui->update();
    }
}

void ipl::scene::AddressEdit::stt_wait_del_msg_fadein() {
    if (!mpCodeLayout->getAnim(0x1c)->isPlaying()) {
        mState = 7;
    }
}

void ipl::scene::AddressEdit::delete_friendinfo() {
    mpFriendCache->del(mSelectedFriend);
    static_cast<ipl::scene::Address*>(ipl::System::getScene(0x14))->reset_friend();
}

u64 ipl::scene::AddressEdit::utf16_wiiid(const wchar_t* value) {
    u64 result = 0;
    u64 multiplier = 1;
    for (int i = 0; i < 0x10; i++) {
        result += static_cast<u64>(value[0xf - i] - L'0') * multiplier;
        multiplier *= 10;
    }
    return result;
}

void ipl::scene::AddressEdit::wiiid_utf16(u64 value, wchar_t* output) {
    u64 multiplier = 1;
    for (int i = 0; i < 0x10; ++i) {
        output[0xf - i] = static_cast<wchar_t>((value / multiplier) % 10 + L'0');
        multiplier *= 10;
    }
    output[0x10] = 0;
}

void ipl::scene::AddressEdit::String::setName(const wchar_t* value) {
    wcsncpy(mName, value, 0xa);
    u32 length = wcslen(value);
    mbNameNotEmpty = false;
    for (u32 i = 0; i < length; i++) {
        if (value[i] == 0) {
            break;
        }
        if (value[i] != L' ' && value[i] != 0x3000) {
            mbNameNotEmpty = true;
            break;
        }
    }
}

ipl::scene::FaderSceneCommand ipl::scene::AddressEdit::calcFadeout() {
    mpBalloon->calc();
    if (ipl::System::getFader()->getStatus() == EGG::Fader::PREPARE_OUT) {
        FaderSceneCommand command = FADER_SCN_CONTINUE;
        if (!mpCodeLayout->getAnim(0x1e)->isPlaying() && !mpNameLayout->getAnim(9)->isPlaying()) {
            command = FADER_SCN_NEXT;
        }
        return command;
    }
    return ipl::System::getFader()->getStatus() == EGG::Fader::PREPARE_IN ? FADER_SCN_NEXT
                                                                           : FADER_SCN_CONTINUE;
}

void ipl::scene::AddressEdit::draw() {
    if (ipl::System::onDefaultDrawLayer()) {
        ipl::utility::Graphics::setOrtho(0);
        mpCodeLayout->draw();
        mpBackgroundLayout->draw();
        mpNameLayout->draw();
        mpBalloon->draw();
    }
}

void ipl::scene::AddressEdit::stt_wait_btn_fadein() {
    u32 friendStatus = mpFriendCache->getInfo(mSelectedFriend).attr.status;
    bool finished;
    if (friendStatus == 2) {
        finished = !mpCodeLayout->getAnim(0x10)->isPlaying();
    } else {
        finished = !mpCodeLayout->getAnim(0x1a)->isPlaying();
    }
    finished = finished & !mpCodeLayout->getAnim(0x11)->isPlaying();
    finished = finished & !mpCodeLayout->getAnim(0x12)->isPlaying();
    if (finished) {
        mState = 0;
    }
}

void ipl::scene::AddressEdit::stt_wait_btn_fadeout() {
    nw4r::lyt::Pane* label;
    const wchar_t* message;
    ipl::utility::FrameController* animator;
    bool friendFinished;
    if (mpFriendCache->getInfo(mSelectedFriend).attr.status == 2) {
        friendFinished = !mpCodeLayout->getAnim(0x15)->isPlaying();
    } else {
        friendFinished = !mpCodeLayout->getAnim(0x1b)->isPlaying();
    }

    friendFinished &= !mpCodeLayout->getAnim(0x16)->isPlaying();
    friendFinished &= !mpCodeLayout->getAnim(0x17)->isPlaying();

    if (friendFinished) {
        label = mpCodeLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_card_msg_00", true);
        message = ipl::System::getMessage(0x30);
        set_textbox(label, message);
        ipl::System::getDialog()->callS2Btn2(0x142, 0x141, true);
        animator = mpCodeLayout->getAnim(0x1c);
        animator->initFrame();
        animator->restart();
        mState = 4;
    }
}

void ipl::scene::AddressEdit::stt_wait_del_msg_fadeout_to_rlt() {
    if (!mpCodeLayout->getAnim(0x1d)->isPlaying()) {
        mState = 8;
        ipl::System::getDialog()->callBtn1(0x51, 0x2e);
    }
}

void ipl::scene::AddressEdit::stt_msg_del_rlt() {
    ipl::scene::Button* button = static_cast<ipl::scene::Button*>(ipl::System::getScene(5));
    switch (ipl::System::getDialog()->getLastResult()) {
    case 1:
        button->reserveText(1, 0x29);
        button->reserveAnm(0xf);
        ipl::layout::Animator* animator = mpCodeLayout->getAnim(0x1e);
        animator->initFrame();
        animator->restart();
        mState = 0x30;
        break;
    default:
        break;
    }
}

void ipl::scene::AddressEdit::stt_ipt_wait_fadein() {
    if (!mpNameLayout->getAnim(0)->isPlaying() && !mpNameLayout->getAnim(1)->isPlaying() &&
        !mpNameLayout->getAnim(2)->isPlaying() && !mpBackgroundLayout->getAnim(0)->isPlaying()) {
        mState = 0xd;
    }
}

void ipl::scene::AddressEdit::stt_ipt_normal() {
    ipl::scene::Button* button = static_cast<ipl::scene::Button*>(ipl::System::getScene(5));
    if (button->isActive()) {
        button->update();
    }
    if (mState == 0xd) {
        mpInputGui->update();
    }
}

void ipl::scene::AddressEdit::stt_ipt_input() {
    ipl::keyboard::Manager::State* state = ipl::System::getKeyboard()->getState();
    ipl::scene::Button* button =
        static_cast<ipl::scene::Button*>(ipl::System::getSceneManager()->getScene(5));
    s32 keyboardType = state->iplType;
    if (keyboardType == ipl::keyboard::Manager::STATE_DISAPPEARING) {
        goto state_disappearing;
    }
    if (keyboardType >= ipl::keyboard::Manager::STATE_DISAPPEARING) {
        goto state_at_or_after_disappearing;
    }
    if (keyboardType >= ipl::keyboard::Manager::STATE_VISIBLE) {
        goto done;
    }
    if (keyboardType >= ipl::keyboard::Manager::STATE_HIDDEN) {
        goto state_hidden;
    }
    goto done;

state_at_or_after_disappearing:
    if (keyboardType >= 5) {
        goto done;
    }
    goto state_hidden_after_disappear;

state_disappearing: {
        BOOL nameWasEmpty = mString.mName[0] == 0;
        if (state->pressOK) {
            mString.setName(state->wcString);
            ipl::layout::Object* layout =
                mpNameLayout;
            nw4r::lyt::Pane* pane = layout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_name_00", true);
            set_textbox(pane, mString.mName);
        }
        if (mString.mName[0] == 0) {
            if (!nameWasEmpty) {
                ipl::layout::Animator* pane = mpNameLayout->getAnim(6);
                pane->initFrame();
                pane->restart();
                pane = mpNameLayout->getAnim(3);
                pane->initFrame();
                pane->restart();
            }
            button->reserveAnm(0xb);
        } else {
            if (nameWasEmpty) {
                ipl::layout::Animator* pane = mpNameLayout->getAnim(2);
                pane->initFrame();
                pane->restart();
                pane = mpNameLayout->getAnim(7);
                pane->initFrame();
                pane->restart();
            }
            if (mString.mbNameNotEmpty != 0) {
                button->reserveText(1, 0x2e);
                button->reserveAnm(0xf);
            } else {
                button->reserveAnm(0xb);
            }
        }
    }
    goto done;

state_hidden_after_disappear: {
        mState = 0xd;
        if (static_cast<u32>(ipl::System::getRegion()) == 6) {
            ipl::System::getKeyboard()->baseMgr()->enableKSXFilter(false);
        }
    }
    goto done;

state_hidden: {
        setDefaultTitleText(NULL, ipl::System::getKeyboard()->baseMgr()->isVacancy());
    }

done:
    return;
}

void ipl::scene::AddressEdit::stt_add_code_input() {
    ipl::keyboard::Manager::State* state = ipl::System::getKeyboard()->getState();
    ipl::scene::Button* button = static_cast<ipl::scene::Button*>(ipl::System::getScene(5));
    switch (state->iplType) {
    case ipl::keyboard::Manager::STATE_DISAPPEARING: {
        BOOL codeWasEmpty = mString.mValue[0] == 0;
        if (state->pressOK) {
            if (mMode == 1) {
                mString.setWiiNo(state->wcString);
            } else {
                mString.setEMail(state->wcString);
            }
            nw4r::lyt::Pane* label = (mpNameLayout)->getNW4RLyt()->GetRootPane()->FindPaneByName("T_name_00", true);
            set_textbox(label, mString.mDisplayText);
        }
        if (mString.mValue[0] == 0) {
            if (!codeWasEmpty) {
                ipl::layout::Animator* pane = mpNameLayout->getAnim(6);
                pane->initFrame();
                pane->restart();
                pane = mpNameLayout->getAnim(3);
                pane->initFrame();
                pane->restart();
            }
            button->reserveAnm(0xb);
        } else {
            if (codeWasEmpty) {
                ipl::layout::Animator* pane = mpNameLayout->getAnim(2);
                pane->initFrame();
                pane->restart();
                pane = mpNameLayout->getAnim(7);
                pane->initFrame();
                pane->restart();
            }
            if (mString.mbValidMail != 0 &&
                mString.isDupCode() == 0 &&
                mString.isMyCode() == 0) {
                button->reserveText(1, 0x2e);
                button->reserveAnm(0xf);
            } else {
                button->reserveAnm(0xb);
            }
        }
        break;
    }
    case ipl::keyboard::Manager::STATE_HIDDEN_AFTER_DISAPPEAR:
        if (state->pressOK) {
            if (mString.mValue[0] != 0) {
                if (mMode == 1) {
                    if (mString.isMyCode() != 0) {
                        ipl::System::getDialog()->callBtn1(0x56, 0x2e);
                        mState = 0x16;
                    } else if (mString.isDupCode() != 0) {
                        ipl::System::getDialog()->callBtn1(0x52, 0x2e);
                        mState = 0x14;
                    } else if (mString.mbValidMail == 0) {
                        ipl::System::getDialog()->callBtn1(0x54, 0x2e);
                        mState = 0x13;
                    } else {
                        mState = 0x11;
                    }
                } else if (mString.isDupCode() != 0) {
                    ipl::System::getDialog()->callBtn1(0x53, 0x2e);
                    mState = 0x15;
                } else if (mString.mbValidMail == 0) {
                    ipl::System::getDialog()->callBtn1(0x1be, 0x2e);
                    mState = 0x13;
                } else {
                    mState = 0x11;
                }
            } else {
                mState = 0x11;
            }
        } else {
            mState = 0x11;
        }
        break;
    case ipl::keyboard::Manager::STATE_HIDDEN:
    case ipl::keyboard::Manager::STATE_APPEARING:
        if (mMode != 1) {
            setDefaultTitleText(NULL, ipl::System::getKeyboard()->baseMgr()->isVacancy());
        }
        break;
    default:
        break;
    }
}

void ipl::scene::AddressEdit::stt_add_code_fadeout() {
    ipl::utility::FrameController* pane = mpNameLayout->getAnim(5);
    if (!pane->isPlaying()) {
        pane = mpNameLayout->getAnim(6);
        if (!pane->isPlaying()) {
            nw4r::lyt::Pane* label = (mpNameLayout)->getNW4RLyt()->GetRootPane()->FindPaneByName(
                reinterpret_cast<const char*>("T_question_00"), true);
            set_textbox(label, ipl::System::getMessage(0x32));
            nw4r::lyt::Pane* messageLabel = (mpNameLayout)->getNW4RLyt()->GetRootPane()->FindPaneByName(
                reinterpret_cast<const char*>("T_msg_00"), true);
            set_textbox(messageLabel, ipl::System::getMessage(0x49));
            nw4r::lyt::Pane* nameLabel = (mpNameLayout)->getNW4RLyt()->GetRootPane()->FindPaneByName(
                    reinterpret_cast<const char*>("T_name_00"), true);
            set_textbox(nameLabel, mString.mName);
            ipl::utility::FrameController* fade = mpNameLayout->getAnim(1);
            fade->initFrame();
            fade->restart();
            if (mString.mName[0] != 0) {
                ipl::utility::FrameController* nameFade = mpNameLayout->getAnim(2);
                nameFade->initFrame();
                nameFade->restart();
            } else {
                ipl::utility::FrameController* nameFade = mpNameLayout->getAnim(3);
                nameFade->initFrame();
                nameFade->restart();
            }
            ipl::System::getKeyboard()->init();
            mState = 0x18;
        }
    }
}

/*
    This is a modified version of NWC24CheckPublicMailAddr.
    Changes:
     - Uses strnicmp instead of NWC24's Mail_strnicmp
     - ... That's it!!
*/
extern "C" NWC24Err NWC24CheckPublicMailAddr_(const char* addr) {
    int i, j;
    int len;
    BOOL readingDomain;

    static const char specials[] = {'(', ')', '<', '>', '[', ']', ':', ';', '\\', ',', '"'};

    // Check parameters
    if (addr == NULL) {
        return NWC24_ERR_NULL;
    }

    // Check address length
    len = STD_strnlen(addr, sizeof(NWC24UserMailAddr));
    if (len == (int)sizeof(NWC24UserMailAddr)) {
        return NWC24_ERR_STRING_END;
    }
    if (len == 0) {
        return NWC24_ERR_FORMAT;
    }

    readingDomain = FALSE;

    for (i = 0; i < len; i++) {
        char ch = addr[i];

        // If we found '@'
        if (ch == '@') {
            // If it was at the beginning of the address, invalid!
            if (i == 0) {
                return NWC24_ERR_FORMAT;
            }
            readingDomain = TRUE;
            break;
        }

        // If the character is not a letter or symbol, invalid!
        if (ch <= ' ' || ch >= '~' + 1) {
            return NWC24_ERR_FORMAT;
        }

        // If the character is special, invalid!
        for (j = 0; j < sizeof(specials); j++) {
            if (ch == specials[j]) {
                return NWC24_ERR_FORMAT;
            }
        }
    }

    // If we are have not found '@', invalid!
    if (!readingDomain) {
        return NWC24_ERR_FORMAT;
    }

    // If the hostname is not valid, invalid!
    if (CheckHostName(&addr[i + 1], (len - i)) < CHECK_HOSTNAME_SUCCESS) {
        return NWC24_ERR_FORMAT;
    }

    return strnicmp(&addr[i], NWC24GetAccountDomain(), (len - i) + 1) == 0 ? NWC24_ERR_PROTECTED : NWC24_OK;
}

static ChkHostNameError CheckHostName(const char* hostName, u32 hostNameLength) {
    int i;
    BOOL foundDot;

    // Parameter check
    if (hostNameLength == 0) {
        return CHECK_HOSTNAME_BAD_LENGTH;
    }

    // Is null or empty check
    if (hostName == NULL) {
        return CHECK_HOSTNAME_IS_NULL;
    }
    if (*hostName == 0) {
        return CHECK_HOSTNAME_IS_EMPTY;
    }

    // Verify check
    if (*hostName == '.') {
        return CHECK_HOSTNAME_INCORRECT;
    }

    foundDot = FALSE;

    for (i = 0; i < hostNameLength; i++) {
        char ch = hostName[i];

        // Stop on NULL
        if (ch == 0) {
            break;
        }

        if (ch == '.') {
            // Check if we already found one again after the previous character.
            if (foundDot) {
                return CHECK_HOSTNAME_MULTIPLE_DOTS;
            }
            foundDot = TRUE;
            continue;
        }

        // Check if there are invalid characters
        if ((ch < '0' || ch > '9') && (ch < 'a' || ch > 'z') && (ch < 'A' || ch > 'Z') && (ch != '-' && ch != '_')) {
            return CHECK_HOSTNAME_INVALID_CHARACTERS;
        }

        foundDot = FALSE;
    }

    // Check if we are out of range
    if (i == hostNameLength) {
        return CHECK_HOSTNAME_OUT_OF_RANGE;
    }

    // Check if the end of hostname has a dot
    if (i > 0 && hostName[i - 1] == '.') {
        return CHECK_HOSTNAME_DOT_AT_END;
    }

    return CHECK_HOSTNAME_SUCCESS;
}





void ipl::scene::AddressEdit::start_point_event(
    const char* paneName, ipl::controller::Interface* controller) {
    int buttonNo = get_button_no(paneName);
    s32 state = mState;

    switch (state) {
        case 0:
            goto state0;
        case 0x22:
            goto state22;
        default:
            goto done;
    }

state0:
    switch (buttonNo) {
        case 0:
            goto state0Button0;
        case 1:
        case 2:
            goto state0Common;
        case 3:
            goto state0Button3;
        case 4:
            goto done;
        default:
            goto done;
    }

state0Button0: {
    u32 friendIndex = mSelectedFriend;
    u32 friendType = mpFriendCache->getInfo(friendIndex).attr.status;
    if (friendType != 2) {
        goto done;
    }
    s32* count = &mPointCount[buttonNo];
    if (*count == 0) {
        ipl::layout::Object* layout = mpCodeLayout;
        ipl::layout::Animator* pane = layout->getAnim(buttonNo + 1);
        pane->initFrame();
        pane->restart();
        ipl::snd::getSystem()->startSE(
            "WIPL_SE_BT_TARGETTING");
        controller->rumble(1);
    }
    ++*count;
    goto done;
}

state0Button3: {
    s32* count = &mPointCount[buttonNo];
    if (*count == 0) {
        ipl::layout::Object* layout = mpCodeLayout;
        nw4r::lyt::Pane* pane = layout->getNW4RLyt()->GetRootPane()->FindPaneByName(paneName, true);
        ipl::math::VEC3 position(0.0f, 0.0f, 0.0f);
        PSMTXMultVec(pane->GetGlobalMtx(), reinterpret_cast<Vec*>(&position), reinterpret_cast<Vec*>(&position));
        f32 xOffset;
        f32 scale;
        f32 height;
        xOffset = 15.0f;
        height = 50.0f;
        scale = 0.5f;
        position.x = position.x + xOffset;
        position.y = position.y + height * scale;
        (mpBalloon)
            ->setPos(position, false, 1);
        (mpBalloon)->fadein();
    }
}

state0Common: {
    s32* count = &mPointCount[buttonNo];
    if (*count == 0) {
        ipl::layout::Object* layout = mpCodeLayout;
        ipl::layout::Animator* pane = layout->getAnim(buttonNo + 1);
        pane->initFrame();
        pane->restart();
        ipl::snd::getSystem()->startSE(
            "WIPL_SE_BT_TARGETTING");
        controller->rumble(1);
    }
    ++*count;
    goto done;
}

state22:
    switch (buttonNo) {
        case 3:
            goto state22Button3;
        default:
            goto done;
    }
state22Button3:
    {
        s32* count = &mPointCount[buttonNo];
        if (*count == 0) {
            ipl::layout::Object* layout = mpCodeLayout;
            nw4r::lyt::Pane* pane = layout->getNW4RLyt()->GetRootPane()->FindPaneByName(paneName, true);
            ipl::math::VEC3 position(0.0f, 0.0f, 0.0f);
            PSMTXMultVec(pane->GetGlobalMtx(), reinterpret_cast<Vec*>(&position), reinterpret_cast<Vec*>(&position));
            f32 xOffset;
            f32 scale;
            f32 height;
            xOffset = 15.0f;
            height = 50.0f;
            scale = 0.5f;
            position.x = position.x + xOffset;
            position.y = position.y + height * scale;
            (mpBalloon)
                ->setPos(position, false, 1);
            (mpBalloon)->fadein();
        }
        ++*count;
    }

done:
    return;
}

void ipl::scene::AddressEdit::start_left_event(const char* paneName) {
    int buttonNo = get_button_no(paneName);
    switch (mState) {
    case 0:
        switch (buttonNo) {
        case 0: {
            if (mpFriendCache->getInfo(mSelectedFriend).attr.status != 2) {
                break;
            }
            s32* count = &mPointCount[buttonNo];
            if (*count == 1) {
                layout::Animator* animator = mpCodeLayout->getAnim(buttonNo + 11);
                animator->initFrame();
                animator->restart();
            }
            if (*count > 0) {
                --*count;
            }
            break;
        }
        case 3:
            if (mPointCount[buttonNo] == 1) {
                mpBalloon->fadeoutForce();
            }
        case 1:
        case 2: {
            s32* count = &mPointCount[buttonNo];
            if (*count == 1) {
                layout::Animator* animator = mpCodeLayout->getAnim(buttonNo + 11);
                animator->initFrame();
                animator->restart();
            }
            if (*count > 0) {
                --*count;
            }
            break;
        }
        case 4:
            break;
        default:
            break;
        }
        break;
    case 0x22:
        switch (buttonNo) {
        case 3: {
            s32* count = &mPointCount[buttonNo];
            if (*count == 1) {
                mpBalloon->fadeoutForce();
            }
            --*count;
            break;
        }
        }
        break;
    default:
        break;
    }
}

void ipl::scene::AddressEdit::start_trig_event(
    const char* paneName) {
    int buttonNo = get_button_no(paneName);
    s32 state = mState;

    switch (state) {
        case 0: {
            if (buttonNo == 0) {
                goto state0Friend;
            }
            if (buttonNo < 0) {
                break;
            }
            if (buttonNo >= 5) {
                break;
            }
            goto state0Event;

        state0Friend: {
            u32 friendIndex = mSelectedFriend;
            u32 friendType = mpFriendCache->getInfo(friendIndex).attr.status;
            if (friendType != 2) {
                goto state0FriendError;
            }
            reset_gui();
            ipl::layout::Object* layout = mpCodeLayout;
            ipl::layout::Animator* pane = layout->getAnim(buttonNo + 6);
            pane->initFrame();
            pane->restart();
            mSelectedButton = buttonNo;
            ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
            mState = 1;
            break;
        }

        state0FriendError: {
            ipl::System::getDialog()->callBtn1(0x57, 0x2e);
            (mpBalloon)->fadeoutForce();
            reset_gui();
            mState = 0x2f;
            break;
        }

        state0Event: {
            ipl::layout::Object* layout = mpCodeLayout;
            ipl::layout::Animator* pane = layout->getAnim(buttonNo + 6);
            pane->initFrame();
            pane->restart();
            mSelectedButton = buttonNo;
            ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
            mState = 1;
            break;
        }
        }
        break;

        case 0x22:
            switch (buttonNo) {
                case 4:
                    goto state22Button4;
                default:
                    break;
            }
            break;

        state22Button4: {
            (mpBalloon)->fadeoutForce();
            for (s32 i = 0; i < 5; ++i) {
                mPointCount[i] = 0;
            }
            ipl::layout::Object* layout = mpCodeLayout;
            ipl::layout::Animator* pane = layout->getAnim(10);
            pane->initFrame();
            pane->restart();
            mSelectedButton = buttonNo;
            ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
            mState = 0x24;
            break;
        }
    }
}

void ipl::scene::AddressEdit::start_ipt_trig_event(
    const char* paneName, int channel) {
    ipl::scene::Button* button = static_cast<ipl::scene::Button*>(ipl::System::getScene(5));
    ipl::controller::Interface* controller = ipl::System::getControllerManager()->getYoungController();
    if (controller == NULL) {
        return;
    }
    if (controller->getChannel() != channel) {
        return;
    }
    if (matchesInputPane(sInputPaneName, paneName)) {
        s32 state = mState;
        switch (state) {
    case 0xd: {
        ipl::keyboard::Manager::KeyboardSetting setting(static_cast<ipl::keyboard::Manager::KeyboardType>(0xb), mString.mName, 0xa, 1);

        switch (ipl::System::getRegion()) {
        case 0xb: {
            void* systemDictionary = ipl::System::getKeyboard()->getZiSystemDic();
            void* oemDictionary = ipl::System::getKeyboard()->getZiOemDic();
            ipl::System::getKeyboard()->baseMgr()->getInputForm()->setZiDictionary(oemDictionary, systemDictionary);
            setting.type = static_cast<ipl::keyboard::Manager::KeyboardType>(0xd);
            break;
        }
        case 6:
            setting.type = static_cast<ipl::keyboard::Manager::KeyboardType>(0xd);
            ipl::System::getKeyboard()->baseMgr()->enableKSXFilter(true);
            break;
        default:
            break;
        }

        ipl::System::getKeyboard()->start(channel, setting);
        setDefaultTitleText(mString.mName, false);
        if (mString.mbNameNotEmpty != 0) {
            button->reserveAnm(0x10);
        } else {
            button->reserveAnm(0xc);
        }
        button->reserveText(1, 0x2e);
        ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
        mState = 0xe;
        break;
    }
    case 0x11: {
        if (mMode == 1) {
            ipl::keyboard::Manager::KeyboardSetting setting(static_cast<ipl::keyboard::Manager::KeyboardType>(0xc), mString.mValue, 0x10, 2);
            ipl::System::getKeyboard()->start(channel, setting);
        } else {
            ipl::keyboard::Manager::KeyboardSetting setting(static_cast<ipl::keyboard::Manager::KeyboardType>(7), mString.mValue, 0x63, 5);
            ipl::System::getKeyboard()->start(channel, setting);
            setDefaultTitleText(mString.mValue, false);
        }
        if (mString.mbValidMail != 0 &&
            !mString.isDupCode() &&
            !mString.isMyCode()) {
            button->reserveAnm(0x10);
        } else {
            button->reserveAnm(0xc);
        }
        ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
        mState = 0x12;
        break;
    }
    case 0x19: {
        ipl::keyboard::Manager::KeyboardSetting setting(static_cast<ipl::keyboard::Manager::KeyboardType>(0xb), mString.mName, 0xa, 1);

        switch (ipl::System::getRegion()) {
        case 0xb: {
            void* systemDictionary = ipl::System::getKeyboard()->getZiSystemDic();
            void* oemDictionary = ipl::System::getKeyboard()->getZiOemDic();
            ipl::System::getKeyboard()->baseMgr()->getInputForm()->setZiDictionary(oemDictionary, systemDictionary);
            setting.type = static_cast<ipl::keyboard::Manager::KeyboardType>(0xd);
            break;
        }
        case 6:
            setting.type = static_cast<ipl::keyboard::Manager::KeyboardType>(0xd);
            ipl::System::getKeyboard()->baseMgr()->enableKSXFilter(true);
            break;
        default:
            break;
        }

        ipl::System::getKeyboard()->start(channel, setting);
        setDefaultTitleText(mString.mName, false);
        if (mString.mbNameNotEmpty != 0) {
            button->reserveAnm(0x10);
        } else {
            button->reserveAnm(0xc);
        }
        ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
        mState = 0x1a;
        break;
    }
    case 0x1d:
        if (mNigaoeState != 1) {
            mNigaoeState = 0;
            if (RFLGetAvailableOfficialDataNum() != 0) {
                createChildScene(0x1c, this, NULL, reinterpret_cast<void*>(2));
                button->reserveAnm(0x10);
                button->reserveAnm(0xb);
                ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
                mState = 0x1e;
            } else {
                ipl::System::getDialog()->callBtn1(0x17c, 0x2e);
                ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
                mState = 0x1f;
            }
        }
        break;
    default:
        break;
        }
    }
}


void ipl::scene::AddressEdit::start_ipt_point_event(
    const char* paneName, int channel) {
    ipl::controller::Interface* controller = ipl::System::getControllerManager()->getYoungController();
    if (controller != NULL) {
        if (controller->getChannel() == channel) {
            switch (mState) {
                case 0x1d: {
                    char paneNameCopy[12] = "mii_icon_00";
                    if (strcmp(paneNameCopy, paneName) == 0) {
                        ipl::layout::Object* layout = mpNameLayout;
                        nw4r::lyt::Pane* pane = layout->getNW4RLyt()->GetRootPane()->FindPaneByName(paneName, true);
                        ipl::math::VEC3 position(0.0f, 0.0f, 0.0f);
                        PSMTXMultVec(pane->GetGlobalMtx(), reinterpret_cast<Vec*>(&position), reinterpret_cast<Vec*>(&position));
                        f32 y;
                        f32 offset;
                        offset = 50.0f;
                        y = position.y;
                        position.y = y + offset;
                        (mpBalloon)
                            ->setPos(position, false, 0);
                        (mpBalloon)->fadein();
                    }
                    break;
                }
            }
        }
    }
}

void ipl::scene::AddressEdit::onEventDerived(u32 componentId, u32 event, const ipl::controller::Interface* controller) {

    ::gui::Manager* manager = getGuiManager();
    gui::PaneComponent* component =
        static_cast<gui::PaneComponent*>(manager->getComponent(componentId));
    nw4r::lyt::Pane* pane = component->getPane();

    const char* paneName = pane->GetName();
    switch (event) {
    case 0: {
    if (controller == NULL) {
        return;
    }
    if (!controller->downTrg(0x100800)) {
        return;
    }
    ipl::scene::Button* button = static_cast<ipl::scene::Button*>(ipl::System::getScene(5));
    ipl::System::getScene(0x14);

        if (strcmp(paneName, smButtonName__Q33ipl5scene6Button[5]) == 0) {
        switch (mState) {
        case 0: {
            button->reserveAnm(0x1b);
            button->reserveAnm(0xc);
            button->reserveText(0, 0x23);
            button->reserveText(1, 0x29);
            button->reserveAnm(0xf);
            ipl::layout::Animator* frame = mpCodeLayout->getAnim(0x1e);
            frame->initFrame();
            frame->restart();
            mSubState = 5;
            ipl::snd::getSystem()->startSE("WIPL_SE_CANCEL");
            (mpBalloon)->fadeoutForce();
            mState = 0x30;
            break;
        }
        case 0xd: {
            button->reserveAnm(0x1b);
            if (mString.mbNameNotEmpty != 0) {
                button->reserveAnm(0x10);
            } else {
                button->reserveAnm(0xc);
            }
            button->reserveAnm(0xb);
            ipl::layout::Animator* frame = mpNameLayout->getAnim(9);
            frame->initFrame();
            frame->restart();
            frame = mpBackgroundLayout->getAnim(1);
            frame->initFrame();
            frame->restart();
            get_friendinfo();
            ipl::snd::getSystem()->startSE("WIPL_SE_CANCEL");
            mState = 0xf;
            break;
        }
        case 0x11: {
            requestSceneChange(getPreviousScene(), NULL);
            button->reserveAnm(0x1b);
            if (mString.mbValidMail != 0 &&
                mString.isDupCode() == 0 &&
                mString.isMyCode() == 0) {
                button->reserveAnm(0x10);
            } else {
                button->reserveAnm(0xc);
            }
            ipl::layout::Animator* frame;
            if (mString.mValue[0] != 0) {
                frame = mpNameLayout->getAnim(6);
                frame->initFrame();
                frame->restart();
            } else {
                frame = mpNameLayout->getAnim(7);
                frame->initFrame();
                frame->restart();
            }
            button->reserveAnm(0xb);
            frame = mpNameLayout->getAnim(9);
            frame->initFrame();
            frame->restart();
            frame = mpNameLayout->getAnim(5);
            frame->initFrame();
            frame->restart();
            mSubState = 5;
            ipl::snd::getSystem()->startSE("WIPL_SE_CANCEL");
            mState = 0x30;
            break;
        }
        case 0x19: {
            button->reserveAnm(0x1b);
            if (mString.mbNameNotEmpty != 0) {
                button->reserveAnm(0x10);
                ipl::layout::Animator* frame = mpNameLayout->getAnim(6);
                frame->initFrame();
                frame->restart();
            } else {
                u16 nameLength = mString.mName[0];
                if (nameLength != 0) {
                    button->reserveAnm(0xc);
                    ipl::layout::Animator* frame = mpNameLayout->getAnim(6);
                    frame->initFrame();
                    frame->restart();
                } else {
                    button->reserveAnm(0xc);
                    ipl::layout::Animator* frame = mpNameLayout->getAnim(7);
                    frame->initFrame();
                    frame->restart();
                }
            }
            button->reserveAnm(0xf);
            ipl::layout::Animator* frame = mpNameLayout->getAnim(5);
            frame->initFrame();
            frame->restart();
            mSubState = 5;
            ipl::snd::getSystem()->startSE("WIPL_SE_CANCEL");
            mState = 0x1b;
            break;
        }
        case 0x1d: {
            button->reserveAnm(0x1b);
            button->reserveAnm(0x10);
            button->reserveAnm(0xf);
            ipl::layout::Animator* frame = mpNameLayout->getAnim(5);
            frame->initFrame();
            frame->restart();
            frame = mpNameLayout->getAnim(8);
            frame->initFrame();
            frame->restart();
            mSubState = 5;
            ipl::snd::getSystem()->startSE("WIPL_SE_CANCEL");
            mState = 0x20;
            (mpBalloon)->fadeoutForce();
            reset_gui();
            break;
        }
        case 0x22: {
            button->reserveAnm(0x1b);
            button->reserveAnm(0x10);
            button->reserveAnm(0xf);
            ipl::layout::Animator* frame = mpCodeLayout->getAnim(0x1e);
            frame->initFrame();
            frame->restart();
            mSubState = 5;
            ipl::snd::getSystem()->startSE("WIPL_SE_CANCEL");
            mState = 0x23;
            (mpBalloon)->fadeoutForce();
            reset_gui();
            break;
        }
        }
        } else if (strcmp(paneName, smButtonName__Q33ipl5scene6Button[7]) == 0) {
            switch (mState) {
        case 0xd: {
            button->reserveAnm(0x1d);
            button->reserveAnm(0x10);
            button->reserveAnm(0xb);
            ipl::layout::Object* layout = mpCodeLayout;
            nw4r::lyt::Pane* pane = layout->getNW4RLyt()->GetRootPane()->FindPaneByName(
                "T_name_00", true);
            set_textbox(pane, mString.mName);
            mSubState = 7;
            ipl::layout::Animator* frame = mpNameLayout->getAnim(9);
            frame->initFrame();
            frame->restart();
            frame = mpBackgroundLayout->getAnim(1);
            frame->initFrame();
            frame->restart();
            update_friendinfo();
            ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
            mState = 0xf;
            break;
        }
        case 0x11: {
            button->reserveAnm(0x1d);
            button->reserveAnm(0x10);
            if (mString.mbNameNotEmpty != 0) {
                button->reserveAnm(0xf);
            } else {
                button->reserveAnm(0xb);
            }
            ipl::layout::Animator* frame = mpNameLayout->getAnim(5);
            frame->initFrame();
            frame->restart();
            frame = mpNameLayout->getAnim(6);
            frame->initFrame();
            frame->restart();
            mSubState = 7;
            ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
            mState = 0x17;
            break;
        }
        case 0x19: {
            button->reserveAnm(0x1d);
            button->reserveAnm(0x10);
            button->reserveAnm(0xf);
            ipl::layout::Animator* frame = mpNameLayout->getAnim(5);
            frame->initFrame();
            frame->restart();
            frame = mpNameLayout->getAnim(6);
            frame->initFrame();
            frame->restart();
            mSubState = 7;
            ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
            mState = 0x1b;
            reset_gui();
            break;
        }
        case 0x1d: {
            button->reserveAnm(0x1d);
            button->reserveAnm(0x10);
            button->reserveAnm(0xf);
            ipl::layout::Animator* frame = mpNameLayout->getAnim(9);
            frame->initFrame();
            frame->restart();
            mSubState = 7;
            ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
            mState = 0x20;
            (mpBalloon)->fadeoutForce();
            reset_gui();
            break;
        }
        case 0x22: {
            button->reserveAnm(0x1d);
            button->reserveAnm(0x10);
            ipl::layout::Animator* frame = mpCodeLayout->getAnim(0x1e);
            frame->initFrame();
            frame->restart();
            mSubState = 7;
            ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
            mState = 0x23;
            (mpBalloon)->fadeoutForce();
            break;
            }
        }
        }
        break;
    }
    default:
        break;
    }
}

void ipl::scene::AddressEdit::start_ipt_left_event(
    const char* paneName, int channel) {
    ipl::controller::Interface* controller = ipl::System::getControllerManager()->getYoungController();
    if (controller != NULL) {
        if (controller->getChannel() == channel) {
            switch (mState) {
                case 0x1d: {
                    char paneNameCopy[12] = "mii_icon_00";
                    if (strcmp(paneNameCopy, paneName) == 0) {
                        (mpBalloon)->fadeoutForce();
                    }
                    break;
                }
            }
        }
    }
}

void ipl::scene::AddressEdit::set_err_msg(wchar_t* outErrMsg, u32 outErrMsgLen, NWC24Err nwc24Err) {
    memset(outErrMsg, 0, outErrMsgLen * sizeof(wchar_t));
    wcsncat(outErrMsg, ipl::System::getMessage(MESG_ERROR_CODE), outErrMsgLen - wcslen(outErrMsg));

    wchar_t nwc24ErrStr[32];
    memset(nwc24ErrStr, 0, sizeof(nwc24ErrStr));
    void* friendListCache = mpFriendCache;
    NWC24Err errorCode = static_cast<NWC24Err>(mpFriendCache->getErrCode());
    swprintf(nwc24ErrStr, sizeof(nwc24ErrStr) / sizeof(wchar_t), L"%06d\n", errorCode);
    wcsncat(outErrMsg, nwc24ErrStr, outErrMsgLen - wcslen(outErrMsg));

    u32 messageId;
    switch (nwc24Err) {
        case NWC24_ERR_NETWORK:
            messageId = MESG_ERROR_NWC24_NETWORK;
            break;
        case NWC24_ERR_SERVER:
        case NWC24_ERR_FULL:
            messageId = MESG_ERROR_NWC24_SERVER;
            break;
        default:
            break;
    }
    wcsncat(outErrMsg, ipl::System::getMessage(messageId), outErrMsgLen - wcslen(outErrMsg));
}







int ipl::scene::AddressEdit::get_button_no(const char* paneName) {
    int result = -1;
    for (int i = 0; i < 5; i++) {
        if (strcmp(smButtonName__Q33ipl5scene6Button[i], paneName) == 0) {
            result = i;
            break;
        }
    }
    return result;
}

void ipl::scene::AddressEdit::add_friendinfo() {
    NWC24FriendInfo info ALIGN32;
    memset(&info, 0, sizeof(info));
    switch (mMode) {
    case 1:
        info.attr.type = 1;
        {
            const wchar_t* name = mString.mName;
            wchar_t* storedName = reinterpret_cast<wchar_t*>(info.attr.name);
            wcsncpy(storedName, name, 0xa);
        }
        info.addr.wiiId = ipl::scene::AddressEdit::utf16_wiiid(mString.mValue);
        memcpy(&info.attr.fdId, &mCreateID, sizeof(mCreateID));
        break;
    case 2:
        info.attr.type = 2;
        {
            const wchar_t* name = mString.mName;
            wchar_t* storedName = reinterpret_cast<wchar_t*>(info.attr.name);
            wcsncpy(storedName, name, 0xa);
        }
        {
            const wchar_t* value = mString.mValue;
            u8* address = reinterpret_cast<u8*>(&info.addr);
            ipl::utility::CharacterCode::UTF16ToANSI(address, value, sizeof(info.addr));
        }
        memcpy(&info.attr.fdId, &mCreateID, sizeof(mCreateID));
        break;
    default:
        break;
    }

    ipl::scene::Address* address =
        static_cast<ipl::scene::Address*>(ipl::System::getScene(0x14));
    u32 index = address->getChosenFriendIndex();
    if (index >= 100) {
        index = 0;
        for (u32 remaining = 100; remaining != 0; --remaining) {
            if (!mpFriendCache->isThere(index)) {
                break;
            }
            ++index;
        }
    }
    mpFriendCache->add(index, info);
    if (mMode == 2) {
        mpFriendCache->sendRegisterMail(index);
    }
}

void ipl::scene::AddressEdit::get_friendinfo() {
    memcpy(&ipl::scene::sFriendInfo, &mpFriendCache->getInfo(mSelectedFriend),
        sizeof(ipl::scene::sFriendInfo));
    mString.setName(reinterpret_cast<const wchar_t*>(ipl::scene::sFriendInfo.attr.name));
    set_textbox(mpCodeLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_name_00", true), mString.mName);

    wchar_t wiiNo[0x100];
    wchar_t email[0x102];
    if (ipl::scene::sFriendInfo.attr.type == 1) {
        memset(wiiNo, 0, sizeof(wiiNo));
        ipl::scene::AddressEdit::wiiid_utf16(ipl::scene::sFriendInfo.addr.wiiId, wiiNo);
        mString.setWiiNo(wiiNo);
    } else {
        memset(email, 0, sizeof(email));
        ipl::utility::CharacterCode::ANSIToUTF16(email, reinterpret_cast<const u8*>(&ipl::scene::sFriendInfo.addr), 0x102);
        mString.setEMail(email);
    }
    set_textbox(mpCodeLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_frnd_crd_00", true), mString.mDisplayText);
    memcpy(&mCreateID, &ipl::scene::sFriendInfo.attr.fdId, sizeof(mCreateID));
}

void ipl::scene::AddressEdit::update_friendinfo() {
    memset(ipl::scene::sFriendInfo.attr.name, 0, 0x18);
    wcsncpy(reinterpret_cast<wchar_t*>(ipl::scene::sFriendInfo.attr.name), mString.mName, 0xa);
    memcpy(&ipl::scene::sFriendInfo.attr.fdId, &mCreateID, sizeof(mCreateID));
    mpFriendCache->update(
        mSelectedFriend,
        reinterpret_cast<const wchar_t*>(ipl::scene::sFriendInfo.attr.name),
        ipl::scene::sFriendInfo.attr.fdId);
    static_cast<ipl::scene::Address*>(ipl::System::getScene(0x14))->reset_friend();
}

void ipl::scene::AddressEdit::String::setEMail(const wchar_t* value) {
    mbHasWiiNo = false;
    memset(mValue, 0, sizeof(mValue));
    wcsncpy(mValue, value, 0xff);
    u32 length = wcslen(value);
    memset(mDisplayText, 0, sizeof(mDisplayText));
    if (length > 0x10) {
        wcsncpy(mDisplayText, value, 0xe);
        wcscpy(mDisplayText + 0xe, L"...");
    } else {
        wcscpy(mDisplayText, value);
    }
    u8 address[0x100];
    memset(address, 0, sizeof(address));
    ipl::utility::CharacterCode::UTF16ToANSI(address, value, sizeof(address));
    mbValidMail = !NWC24CheckPublicMailAddr_(reinterpret_cast<const char*>(address));
}
