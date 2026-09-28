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
    mpCallbackOwner = this;
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
            animator->initFrame();
            animator->restart();
        }
        mPointCount[i] = 0;
    }
}


extern "C" void* __nw__FUl(u32);
extern "C" BOOL RFLSearchOfficialData(const RFLCreateID*, u16*);

extern "C" NWC24FriendInfo sFriendInfo__Q23ipl5scene;
extern "C" char smArg__Q23ipl6System;
extern "C" const char* smButtonName__Q33ipl5scene6Button[];
extern "C" void List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs();
extern "C" void getScene__Q33ipl5scene7ManagerFi();
extern "C" void UTF16ToANSI__Q33ipl7utility13CharacterCodeFPUcPCwl();
extern "C" void reset_friend__Q33ipl5scene7AddressFv();
extern "C" void callBtn1__Q23ipl12DialogWindowFUlUl();
extern "C" void setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler();
extern "C" void calc__Q33ipl5scene11TextBalloonFv();
extern "C" void calc__Q33ipl6layout6ObjectFv();
extern "C" void isActive__Q33ipl5scene6ButtonCFv();
extern "C" void update__Q33ipl5scene6ButtonFv();
extern "C" void update__Q33ipl3gui11PaneManagerFv();
extern "C" void setOrtho__Q33ipl7utility8GraphicsFUl();
extern "C" void draw__Q33ipl6layout6ObjectFv();
extern "C" void draw__Q33ipl5scene11TextBalloonFv();










int ipl::scene::AddressEdit::get_button_no(const char*);
extern "C" void reserveText__Q33ipl5scene6ButtonFiUl();
extern "C" void reserveAnm__Q33ipl5scene6ButtonFi();
extern "C" void initFrame__Q33ipl7utility15FrameControllerFv();
extern "C" void del__Q33ipl5scene15FriendListCacheFUl();








extern "C" NWC24Err NWC24CheckPublicMailAddr_(const char*);
extern "C" void __div2u();
extern "C" void __mod2u();
extern "C" u64 utf16_wiiid__Q33ipl5scene11AddressEditFPCw(const wchar_t*);
extern "C" void isValidId__Q33ipl5scene15FriendListCacheFRCUx();
extern "C" void isDupId__Q33ipl5scene15FriendListCacheFRCUx();
extern "C" void isDupMail__Q33ipl5scene15FriendListCacheFPCc();



extern "C" void _savegpr_29();
extern "C" void _restgpr_29();
extern "C" void _savegpr_23();
extern "C" void _restgpr_23();










































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

extern "C" asm const wchar_t* getName__Q33ipl6nigaoe6ObjectCFv(void*) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    lwz r0, 0x3c(r3)
    cmpwi r0, 0
    blt getName_L1
    clrlwi r3, r0, 16
    bl RFLiGetCharData
    addi r3, r3, 2
    b getName_L2
getName_L1:
    li r3, 0
getName_L2:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void getInputForm__Q29textinput7ManagerFv() {
    nofralloc
    lwz r3, 0x1c(r3)
    blr
}

void ipl::scene::AddressEdit::String::clear() {
    memset(mValue, 0, sizeof(mValue));
    memset(mName, 0, sizeof(mName));
    memset(mDisplayText, 0, sizeof(mDisplayText));
    mbValidMail = false;
    mbNameNotEmpty = false;
    mbHasWiiNo = false;
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

extern "C" asm void setWiiNo__Q43ipl5scene11AddressEdit6StringFPCw(void*, const wchar_t*) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_29
    li r0, 1
    mr r31, r4
    stb r0, 0x422(r3)
    mr r30, r3
    li r4, 0
    li r5, 0x204
    bl memset
    mr r3, r30
    mr r4, r31
    li r5, 0x10
    bl wcsncpy
    addi r3, r30, 0x21c
    li r4, 0
    li r5, 0x204
    bl memset
    li r0, 0x10
    li r7, 0
    li r3, 0
    li r5, 0x3f
    mtctr r0
setWiiNo_L1:
    lhzx r6, r31, r3
    cmplwi r6, 0x30
    blt setWiiNo_L2
    cmplwi r6, 0x39
    bgt setWiiNo_L2
    srawi r0, r7, 2
    addze r0, r0
    add r0, r7, r0
    slwi r0, r0, 1
    add r4, r30, r0
    sth r6, 0x21c(r4)
    b setWiiNo_L3
setWiiNo_L2:
    srawi r0, r7, 2
    addze r0, r0
    add r0, r7, r0
    slwi r0, r0, 1
    add r4, r30, r0
    sth r5, 0x21c(r4)
setWiiNo_L3:
    addi r7, r7, 1
    addi r3, r3, 2
    bdnz setWiiNo_L1
    li r0, 0x20
    mr r3, r31
    sth r0, 0x238(r30)
    li r29, 0
    sth r0, 0x22e(r30)
    sth r0, 0x224(r30)
    bl wcslen
    cmplwi r3, 0x10
    bne setWiiNo_L4
    mr r3, r31
    bl utf16_wiiid__Q33ipl5scene11AddressEditFPCw
    stw r4, 0xc(r1)
    addi r4, r1, 8
    stw r3, 8(r1)
    lwz r3, 0x424(r30)
    lwz r3, 0x4ec(r3)
    bl isValidId__Q33ipl5scene15FriendListCacheFRCUx
    cmpwi r3, 0
    beq setWiiNo_L4
    li r29, 1
setWiiNo_L4:
    stb r29, 0x420(r30)
    addi r11, r1, 0x20
    bl _restgpr_29
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm int isDupCode__Q43ipl5scene11AddressEdit6StringCFv(void*) {
    nofralloc
    stwu r1, -0x120(r1)
    mflr r0
    stw r0, 0x124(r1)
    lbz r0, 0x422(r3)
    stw r31, 0x11c(r1)
    mr r31, r3
    cmpwi r0, 0
    beq isDupCode_L1
    bl utf16_wiiid__Q33ipl5scene11AddressEditFPCw
    stw r4, 0xc(r1)
    addi r4, r1, 8
    lwz r5, 0x424(r31)
    stw r3, 8(r1)
    lwz r3, 0x4ec(r5)
    bl isDupId__Q33ipl5scene15FriendListCacheFRCUx
    b isDupCode_L2
isDupCode_L1:
    addi r3, r1, 0x10
    li r4, 0
    li r5, 0x101
    bl memset
    mr r4, r31
    addi r3, r1, 0x10
    li r5, 0x100
    bl UTF16ToANSI__Q33ipl7utility13CharacterCodeFPUcPCwl
    lwz r3, 0x424(r31)
    addi r4, r1, 0x10
    lwz r3, 0x4ec(r3)
    bl isDupMail__Q33ipl5scene15FriendListCacheFPCc
isDupCode_L2:
    lwz r0, 0x124(r1)
    lwz r31, 0x11c(r1)
    mtlr r0
    addi r1, r1, 0x120
    blr
}

extern "C" asm int isMyCode__Q43ipl5scene11AddressEdit6StringCFv(void*) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    lbz r0, 0x422(r3)
    stw r31, 0xc(r1)
    cmpwi r0, 0
    stw r30, 8(r1)
    beq isMyCode_L1
    lwz r4, 0x424(r3)
    lwz r4, 0x4ec(r4)
    lwz r31, 0x7d68(r4)
    lwz r30, 0x7d6c(r4)
    bl utf16_wiiid__Q33ipl5scene11AddressEditFPCw
    xor r4, r30, r4
    xor r0, r31, r3
    or r0, r4, r0
    cntlzw r0, r0
    srwi r3, r0, 5
    b isMyCode_L2
isMyCode_L1:
    li r3, 0
isMyCode_L2:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

void ipl::scene::AddressEdit::prepare() {
    mpBalloonFile = ipl::System::getNandManager()->readLayoutAsync(
        getSceneHeap(), "balloon.ash", false);
}

void ipl::scene::AddressEdit::create() {

    ipl::layout::Object* bLayout;
    ipl::scene::Board* board = static_cast<ipl::scene::Board*>(ipl::System::getScene(4));
    ipl::nand::LayoutFile* boardFile = board->getLayoutFile();

    bLayout = reinterpret_cast<ipl::layout::Object*>(__nw__FUl(0x580));
    if (bLayout != NULL) {
        bLayout = new (bLayout) ipl::layout::Object(getHeap(), boardFile, "arc", "th_Adress_b.brlyt");
    }
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

    ipl::scene::AddressEditEvent* editEvent = static_cast<ipl::scene::AddressEditEvent*>(__nw__FUl(sizeof(ipl::scene::AddressEditEvent)));
    if (editEvent != NULL) {
        new (editEvent) ipl::scene::AddressEditEvent(this);
    }
    void* editManagerMemory = __nw__FUl(0x34);
    ipl::gui::PaneManager* editManager = reinterpret_cast<ipl::gui::PaneManager*>(editManagerMemory);
    if (editManagerMemory != NULL) {
        editManager = new (editManagerMemory) ipl::gui::PaneManager(static_cast< ::gui::EventHandler*>(editEvent), bLayout->getDrawInfo(), NULL, NULL, false);
    }
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

    ipl::layout::Object* cLayout = reinterpret_cast<ipl::layout::Object*>(__nw__FUl(0x580));
    if (cLayout != NULL) {
        cLayout = new (cLayout) ipl::layout::Object(getHeap(), boardFile, "arc", "th_Adress_c.brlyt");
    }
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

    ipl::scene::AddressInputEvent* inputEvent = static_cast<ipl::scene::AddressInputEvent*>(__nw__FUl(sizeof(ipl::scene::AddressInputEvent)));
    if (inputEvent != NULL) {
        new (inputEvent) ipl::scene::AddressInputEvent(this);
    }
    void* inputManagerMemory = __nw__FUl(0x34);
    ipl::gui::PaneManager* inputManager = reinterpret_cast<ipl::gui::PaneManager*>(inputManagerMemory);
    if (inputManagerMemory != NULL) {
        inputManager = new (inputManagerMemory) ipl::gui::PaneManager(static_cast< ::gui::EventHandler*>(inputEvent), cLayout->getDrawInfo(), NULL, NULL, false);
    }
    inputManager->setupScene(cLayout);
    inputManager->setAllComponentTriggerTarget(false);
    textPane = cLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(sInputPaneName, true);
    inputManager->setTriggerTarget(textPane, true);
    mpNameLayout = cLayout;
    mpInputEvent = inputEvent;
    mpInputGui = inputManager;

    ipl::layout::Object* background = reinterpret_cast<ipl::layout::Object*>(__nw__FUl(0x580));
    if (background != NULL) {
        background = new (background) ipl::layout::Object(getHeap(), boardFile, "arc", "my_Back_a.brlyt");
    }
    mpBackgroundLayout = background;
    background->bind("my_Back_a_Apear.brlan", "Picture_00", false, true);
    (mpBackgroundLayout)
        ->bind("my_Back_a_Lost.brlan", "Picture_00", false, false);
    (mpBackgroundLayout)->finishBinding();
    (mpBackgroundLayout)
        ->getAnim(0)->initAnmFrame();

    mString.clear();
    memset(&sFriendInfo__Q23ipl5scene, 0, sizeof(sFriendInfo__Q23ipl5scene));
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
        set_textbox(textPane, mString.mDisplayText);
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
    bool complete = true;
    ipl::scene::Button* button = static_cast<ipl::scene::Button*>(ipl::System::getScene(5));
    for (s32 i = 0; i < 5; ++i) {
        u16 index = static_cast<u16>(mSelectedButton + 6);
        complete = complete && !mpCodeLayout->getAnim(index)->isPlaying();
    }
    if (!complete) {
        return;
    }

    switch (mSelectedButton) {
    case 2: {
        u32 friendIndex = mSelectedFriend;
        ipl::layout::Animator* animator;
        if (mpFriendCache->getInfo(friendIndex).attr.status == 2) {
            animator = mpCodeLayout->getAnim(0x15);
        } else {
            animator = mpCodeLayout->getAnim(0x1b);
        }
        animator->initFrame();
        animator->restart();
        animator = mpCodeLayout->getAnim(0x16);
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
        nw4r::lyt::Pane* textPane = mpNameLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(
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
        bool nameWasEmpty = mString.mName[0] == 0;
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
        ipl::scene::FaceSelect* faceSelect = static_cast<ipl::scene::FaceSelect*>(child);
        s32 faceId = faceSelect->getSelectedFaceId();
        if (faceId >= 0 && ipl::System::getMiiManager()->isAvalable(faceId) &&
            mNigaoeState == 0) {
            RFLAdditionalInfo additionalInfo;
            RFLGetAdditionalInfo(&additionalInfo, RFLDataSource_Official, NULL, faceId);
            if (!RFLiIsSameID(&mCreateID, &additionalInfo.createID)) {
                mCreateID = additionalInfo.createID;
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
    if (mpNameLayout->getAnim(9)->isPlaying() ||
        mpNameLayout->getAnim(5)->isPlaying() ||
        mpNameLayout->getAnim(8)->isPlaying()) {
        return;
    }

    if (mSubState == 5) {
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
        return;
    }

    if (mSubState == 7) {
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
        ipl::layout::Animator* animator;
        if (status == 2) {
            animator = mpCodeLayout->getAnim(0x10);
        } else {
            animator = mpCodeLayout->getAnim(0x1a);
        }
        animator->initFrame();
        animator->restart();
        animator = mpCodeLayout->getAnim(0x11);
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
    if (!mpCodeLayout->getAnim(0x1e)->isPlaying()) {
        ipl::scene::Button* button = static_cast<ipl::scene::Button*>(ipl::System::getScene(5));
        switch (mSubState) {
        case 5: {
            ipl::layout::Animator* animator = mpNameLayout->getAnim(0);
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
        s32 faceId = faceSelect->getSelectedFaceId();
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

    if (signedEvent == 1) {
        if (data != NULL) {
            mpParent->start_point_event(paneName, static_cast<ipl::controller::Interface*>(data));
        }
    } else if (signedEvent >= 1) {
        if (signedEvent < 3) {
            mpParent->start_left_event(paneName);
        }
    } else if (signedEvent >= 0 && data != NULL &&
               static_cast<ipl::controller::Interface*>(data)->downTrg(0x100800)) {
        mpParent->start_trig_event(paneName);
    }
}

void ipl::scene::AddressInputEvent::onEvent(u32 componentId, u32 event, void* data) {
    s32 signedEvent = static_cast<s32>(event);
    ::gui::Manager* manager = mpManager;
    ::gui::PaneComponent* component =
        static_cast< ::gui::PaneComponent*>(manager->getComponent(componentId));
    const char* paneName = component->getPane()->GetName();
    ipl::controller::Interface* controller = static_cast<ipl::controller::Interface*>(data);

    if (signedEvent == 1) {
        if (controller != NULL) {
            mpParent->start_ipt_point_event(paneName, controller->getChannel());
        }
    } else if (signedEvent >= 1) {
        if (signedEvent < 3 && controller != NULL) {
            mpParent->start_ipt_left_event(paneName, controller->getChannel());
        }
    } else if (signedEvent >= 0 && controller != NULL && controller->downTrg(0x100800)) {
        mpParent->start_ipt_trig_event(paneName, controller->getChannel());
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

extern "C" asm void calcFadein__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    li r31, 0
    stw r30, 8(r1)
    mr r30, r3
    lwz r5, 0x68(r3)
    addi r3, r5, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 1
    beq calcFadein_L1
    lwz r3, 0x74(r30)
    li r4, 0
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 1
    beq calcFadein_L1
    li r31, 1
calcFadein_L1:
    mr r3, r31
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void initCalcNormal__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    cmpwi r3, 0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    beq initCalcNormal_L1
    addi r31, r3, 0x58
initCalcNormal_L1:
    lis r3, smArg__Q23ipl6System@ha
    li r4, 5
    addi r3, r3, smArg__Q23ipl6System@l
    lwz r3, 0x64(r3)
    bl getScene__Q33ipl5scene7ManagerFi
    mr r4, r31
    li r5, 0
    bl setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
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

extern "C" asm void initCalcFadeout__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r5, smArg__Q23ipl6System@ha
    li r4, 5
    stw r0, 0x14(r1)
    addi r5, r5, smArg__Q23ipl6System@l
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r3, 0x64(r5)
    bl getScene__Q33ipl5scene7ManagerFi
    li r4, 0
    li r5, 0
    bl setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler
    lwz r3, 0xa8(r31)
    bl calc__Q33ipl5scene11TextBalloonFv
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void calcCommonAfter__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r3, 0x70(r3)
    lwz r12, 0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lwz r3, 0x68(r31)
    bl calc__Q33ipl6layout6ObjectFv
    lwz r3, 0x7c(r31)
    lwz r12, 0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lwz r3, 0x74(r31)
    bl calc__Q33ipl6layout6ObjectFv
    lwz r3, 0x80(r31)
    bl calc__Q33ipl6layout6ObjectFv
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_normal__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r5, smArg__Q23ipl6System@ha
    li r4, 5
    stw r0, 0x14(r1)
    addi r5, r5, smArg__Q23ipl6System@l
    stw r31, 0xc(r1)
    stw r30, 8(r1)
    mr r30, r3
    lwz r3, 0x64(r5)
    bl getScene__Q33ipl5scene7ManagerFi
    mr r31, r3
    bl isActive__Q33ipl5scene6ButtonCFv
    cmpwi r3, 0
    beq stt_normal_L1
    mr r3, r31
    bl update__Q33ipl5scene6ButtonFv
stt_normal_L1:
    lwz r0, 0x64(r30)
    cmpwi r0, 0
    bne stt_normal_L2
    lwz r3, 0x70(r30)
    bl update__Q33ipl3gui11PaneManagerFv
stt_normal_L2:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_wait_del_msg_fadein__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0x1c
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r5, 0x68(r3)
    addi r3, r5, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 1
    beq stt_wait_del_msg_fadein_L1
    li r0, 7
    stw r0, 0x64(r31)
stt_wait_del_msg_fadein_L1:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void delete_friendinfo__Q33ipl5scene11AddressEditFv(void* self) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    mr r4, r3
    stw r0, 0x14(r1)
    lwz r3, 0x4ec(r3)
    lwz r4, 0xa4(r4)
    bl del__Q33ipl5scene15FriendListCacheFUl
    lis r3, smArg__Q23ipl6System@ha
    li r4, 0x14
    addi r3, r3, smArg__Q23ipl6System@l
    lwz r3, 0x64(r3)
    bl getScene__Q33ipl5scene7ManagerFi
    bl reset_friend__Q33ipl5scene7AddressFv
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
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

extern "C" asm void wiiid_utf16__Q33ipl5scene11AddressEditFUxPw(u64, wchar_t*) {
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    addi r11, r1, 0x30
    bl _savegpr_23
    mr r24, r3
    mr r23, r4
    mr r25, r5
    li r27, 1
    li r28, 0
    li r26, 0
    li r29, 0x30
    li r30, 0
    li r31, 0xa
wiiid_utf16_L1:
    mr r3, r24
    mr r4, r23
    mr r5, r28
    mr r6, r27
    bl __div2u
    li r6, 0xa
    li r5, 0
    bl __mod2u
    addc r5, r4, r29
    adde r3, r3, r30
    subfic r3, r26, 0xf
    addi r26, r26, 1
    slwi r4, r3, 1
    mulhwu r0, r27, r31
    cmpwi r26, 0x10
    sthx r5, r25, r4
    mullw r3, r28, r31
    mulli r27, r27, 0xa
    add r28, r0, r3
    blt wiiid_utf16_L1
    li r0, 0
    addi r11, r1, 0x30
    sth r0, 0x20(r25)
    bl _restgpr_23
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
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

extern "C" asm void calcFadeout__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    stw r30, 8(r1)
    mr r30, r3
    lwz r3, 0xa8(r3)
    bl calc__Q33ipl5scene11TextBalloonFv
    lis r31, smArg__Q23ipl6System@ha
    addi r31, r31, smArg__Q23ipl6System@l
    lwz r3, 0xc4(r31)
    lwz r12, 0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    cmpwi r3, 1
    bne calcFadeout_L1
    lwz r3, 0x68(r30)
    li r31, 0
    li r4, 0x1e
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 1
    beq calcFadeout_L2
    lwz r3, 0x74(r30)
    li r4, 9
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 1
    beq calcFadeout_L2
    li r31, 1
calcFadeout_L2:
    mr r3, r31
    b calcFadeout_L3
calcFadeout_L1:
    lwz r3, 0xc4(r31)
    lwz r12, 0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    cntlzw r0, r3
    srwi r3, r0, 5
calcFadeout_L3:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void draw__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r4, smArg__Q23ipl6System@ha
    stw r0, 0x14(r1)
    addi r4, r4, smArg__Q23ipl6System@l
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r3, 0x64(r4)
    lwz r0, 0x100(r3)
    cmpwi r0, 1
    bne draw_L1
    li r3, 0
    bl setOrtho__Q33ipl7utility8GraphicsFUl
    lwz r3, 0x68(r31)
    bl draw__Q33ipl6layout6ObjectFv
    lwz r3, 0x80(r31)
    bl draw__Q33ipl6layout6ObjectFv
    lwz r3, 0x74(r31)
    bl draw__Q33ipl6layout6ObjectFv
    lwz r3, 0xa8(r31)
    bl draw__Q33ipl5scene11TextBalloonFv
draw_L1:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_wait_btn_fadein__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    stw r30, 8(r1)
    lwz r0, 0xa4(r3)
    lwz r4, 0x4ec(r3)
    mulli r0, r0, 0x140
    add r4, r4, r0
    lwz r0, 4(r4)
    cmplwi r0, 2
    bne stt_wait_btn_fadein_L1
    lwz r3, 0x68(r3)
    li r4, 0x10
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r3, 0x14(r3)
    addi r3, r3, -1
    addic r0, r3, -1
    subfe r30, r0, r3
    b stt_wait_btn_fadein_L2
stt_wait_btn_fadein_L1:
    lwz r3, 0x68(r3)
    li r4, 0x1a
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r3, 0x14(r3)
    addi r3, r3, -1
    addic r0, r3, -1
    subfe r30, r0, r3
stt_wait_btn_fadein_L2:
    lwz r3, 0x68(r31)
    li r4, 0x11
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r5, 0x14(r3)
    li r4, 0x12
    lwz r3, 0x68(r31)
    addi r5, r5, -1
    addic r0, r5, -1
    addi r3, r3, 0x28c
    subfe r0, r0, r5
    and r5, r30, r0
    addic r0, r5, -1
    subfe r30, r0, r5
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r3, 0x14(r3)
    addi r3, r3, -1
    addic r0, r3, -1
    subfe r0, r0, r3
    and r3, r30, r0
    addic r0, r3, -1
    subfe. r0, r0, r3
    beq stt_wait_btn_fadein_L3
    li r0, 0
    stw r0, 0x64(r31)
stt_wait_btn_fadein_L3:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

void ipl::scene::AddressEdit::stt_wait_btn_fadeout() {
    u32 index = mSelectedFriend;
    u32 friendType = mpFriendCache->getInfo(index).attr.status;
    u32 friendFinished;
    if (friendType == 2) {
        friendFinished = !mpCodeLayout->getAnim(0x15)->isPlaying();
    } else {
        friendFinished = !mpCodeLayout->getAnim(0x1b)->isPlaying();
    }

    bool finished = friendFinished && !mpCodeLayout->getAnim(0x16)->isPlaying();
    finished = finished && !mpCodeLayout->getAnim(0x17)->isPlaying();

    if (finished) {
        nw4r::lyt::Pane* label = mpCodeLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_card_msg_00", true);
        const wchar_t* message = ipl::System::getMessage(0x30);
        set_textbox(label, message);
        ipl::System::getDialog()->callS2Btn2(0x142, 0x141, true);
        mpCodeLayout->getAnim(0x1c)->initFrame();
        mpCodeLayout->getAnim(0x1c)->restart();
        mState = 4;
    }
}

extern "C" asm void stt_wait_del_msg_fadeout_to_rlt__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0x1d
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r5, 0x68(r3)
    addi r3, r5, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 1
    beq stt_wait_del_msg_fadeout_to_rlt_L1
    li r0, 8
    lis r3, smArg__Q23ipl6System@ha
    stw r0, 0x64(r31)
    addi r3, r3, smArg__Q23ipl6System@l
    li r4, 0x51
    li r5, 0x2e
    lwz r3, 0xac(r3)
    bl callBtn1__Q23ipl12DialogWindowFUlUl
stt_wait_del_msg_fadeout_to_rlt_L1:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_msg_del_rlt__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 5
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    lis r31, smArg__Q23ipl6System@ha
    addi r31, r31, smArg__Q23ipl6System@l
    stw r30, 8(r1)
    mr r30, r3
    lwz r3, 0x64(r31)
    bl getScene__Q33ipl5scene7ManagerFi
    lwz r4, 0xac(r31)
    mr r31, r3
    lwz r0, 0x24(r4)
    cmpwi r0, 1
    beq stt_msg_del_rlt_L2
    b stt_msg_del_rlt_L1
stt_msg_del_rlt_L2:
    li r4, 1
    li r5, 0x29
    bl reserveText__Q33ipl5scene6ButtonFiUl
    mr r3, r31
    li r4, 0xf
    bl reserveAnm__Q33ipl5scene6ButtonFi
    lwz r3, 0x68(r30)
    li r4, 0x1e
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r31, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    li r3, 1
    li r0, 0x30
    stw r3, 0x14(r31)
    stw r0, 0x64(r30)
stt_msg_del_rlt_L1:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_ipt_wait_fadein__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r5, 0x74(r3)
    addi r3, r5, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 1
    beq stt_ipt_wait_fadein_L1
    lwz r3, 0x74(r31)
    li r4, 1
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 1
    beq stt_ipt_wait_fadein_L1
    lwz r3, 0x74(r31)
    li r4, 2
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 1
    beq stt_ipt_wait_fadein_L1
    lwz r3, 0x80(r31)
    li r4, 0
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 1
    beq stt_ipt_wait_fadein_L1
    li r0, 0xd
    stw r0, 0x64(r31)
stt_ipt_wait_fadein_L1:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_ipt_normal__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r5, smArg__Q23ipl6System@ha
    li r4, 5
    stw r0, 0x14(r1)
    addi r5, r5, smArg__Q23ipl6System@l
    stw r31, 0xc(r1)
    stw r30, 8(r1)
    mr r30, r3
    lwz r3, 0x64(r5)
    bl getScene__Q33ipl5scene7ManagerFi
    mr r31, r3
    bl isActive__Q33ipl5scene6ButtonCFv
    cmpwi r3, 0
    beq stt_ipt_normal_L1
    mr r3, r31
    bl update__Q33ipl5scene6ButtonFv
stt_ipt_normal_L1:
    lwz r0, 0x64(r30)
    cmpwi r0, 0xd
    bne stt_ipt_normal_L2
    lwz r3, 0x7c(r30)
    bl update__Q33ipl3gui11PaneManagerFv
stt_ipt_normal_L2:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

void ipl::scene::AddressEdit::stt_ipt_input() {
    ipl::keyboard::Manager::State* state = ipl::System::getKeyboard()->getState();
    ipl::scene::Manager* sceneManager = ipl::System::getSceneManager();
    ipl::scene::Button* button = static_cast<ipl::scene::Button*>(sceneManager->getScene(5));
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
        bool nameWasEmpty = mString.mName[0] == 0;
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
        bool codeWasEmpty = mString.mValue[0] == 0;
        if (state->pressOK) {
            if (mMode == 1) {
                setWiiNo__Q43ipl5scene11AddressEdit6StringFPCw(
                    &mString, state->wcString);
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
                isDupCode__Q43ipl5scene11AddressEdit6StringCFv(&mString) == 0 &&
                isMyCode__Q43ipl5scene11AddressEdit6StringCFv(&mString) == 0) {
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
                    if (isMyCode__Q43ipl5scene11AddressEdit6StringCFv(
                &mString) != 0) {
                        ipl::System::getDialog()->callBtn1(0x56, 0x2e);
                        mState = 0x16;
                    } else if (isDupCode__Q43ipl5scene11AddressEdit6StringCFv(
                       &mString) != 0) {
                        ipl::System::getDialog()->callBtn1(0x52, 0x2e);
                        mState = 0x14;
                    } else if (mString.mbValidMail == 0) {
                        ipl::System::getDialog()->callBtn1(0x54, 0x2e);
                        mState = 0x13;
                    } else {
                        mState = 0x11;
                    }
                } else if (isDupCode__Q43ipl5scene11AddressEdit6StringCFv(
                   &mString) != 0) {
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
    ipl::layout::Object* layout = mpNameLayout;
    ipl::layout::Animator* pane = layout->getAnim(5);
    if (!pane->isPlaying()) {
        pane = mpNameLayout->getAnim(6);
        if (!pane->isPlaying()) {
            nw4r::lyt::Pane* label = (mpNameLayout)->getNW4RLyt()->GetRootPane()->FindPaneByName(
                reinterpret_cast<const char*>("T_question_00"), true);
            set_textbox(label, ipl::System::getMessage(0x32));
            label = (mpNameLayout)->getNW4RLyt()->GetRootPane()->FindPaneByName(
                reinterpret_cast<const char*>("T_msg_00"), true);
            set_textbox(label, ipl::System::getMessage(0x49));
            label = (mpNameLayout)->getNW4RLyt()->GetRootPane()->FindPaneByName(
                    reinterpret_cast<const char*>("T_name_00"), true);
            set_textbox(label, mString.mName);
            pane = mpNameLayout->getAnim(1);
            pane->initFrame();
            pane->restart();
            if (mString.mName[0] != 0) {
                pane = mpNameLayout->getAnim(2);
                pane->initFrame();
                pane->restart();
            } else {
                pane = mpNameLayout->getAnim(3);
                pane->initFrame();
                pane->restart();
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
        f32 xOffset = 15.0f;
        f32 height = 50.0f;
        f32 scale = 0.5f;
        position.x = position.x + xOffset;
        position.y = position.y + scale * height;
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
            f32 xOffset = 15.0f;
            f32 height = 50.0f;
            f32 scale = 0.5f;
            position.x = position.x + xOffset;
            position.y = position.y + scale * height;
            (mpBalloon)
                ->setPos(position, false, 1);
            (mpBalloon)->fadein();
        }
        ++*count;
    }

done:
    return;
}

void ipl::scene::AddressEdit::start_left_event(
    const char* paneName) {
    int buttonNo = get_button_no(paneName);
    s32 state = mState;
    switch (state) {
    case 0x22:
        goto state22;
    case 0:
        switch (buttonNo) {
        case 3:
            goto state0Button3;
        case 0:
            goto state0Friend;
        case 1:
        case 2:
            goto state0Common;
        default:
            break;
        }
        break;
    default:
        break;
    }
    goto done;

state0Friend: {
        u32 friendIndex = mSelectedFriend;
        u32 friendType = mpFriendCache->getInfo(friendIndex).attr.status;
        if (friendType != 2) {
            goto done;
        }
        s32* count = &mPointCount[buttonNo];
        if (*count == 1) {
            ipl::layout::Object* layout = mpCodeLayout;
            ipl::layout::Animator* pane = layout->getAnim(buttonNo + 0xb);
            pane->initFrame();
            pane->restart();
        }
        if (*count > 0) {
            --*count;
        }
        goto done;
    }

state0Button3: {
        s32* count = &mPointCount[buttonNo];
        if (*count == 1) {
            (mpBalloon)->fadeoutForce();
        }
        --*count;
        goto done;
    }

state0Common: {
        s32* count = &mPointCount[buttonNo];
        if (*count == 1) {
            ipl::layout::Object* layout = mpCodeLayout;
            ipl::layout::Animator* pane = layout->getAnim(buttonNo + 0xb);
            pane->initFrame();
            pane->restart();
        }
        if (*count > 0) {
            --*count;
        }
        goto done;
    }

state22:
    if (buttonNo != 3) {
        goto done;
    }
    {
        s32* count = &mPointCount[buttonNo];
        if (*count == 1) {
            (mpBalloon)->fadeoutForce();
        }
        --*count;
    }

done:
    return;
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
            ipl::snd::getSystem()->startSE("WIPL_SE_BT_TARGETTING");
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
            ipl::snd::getSystem()->startSE("WIPL_SE_BT_TARGETTING");
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
            ipl::snd::getSystem()->startSE("WIPL_SE_BT_TARGETTING");
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
    if (!strcmp(sInputPaneName, paneName)) {
        s32 state = mState;
        switch (state) {
    case 0xd: {
        ipl::keyboard::Manager::KeyboardSetting setting(static_cast<ipl::keyboard::Manager::KeyboardType>(0xb), mString.mName, 0xa, 1);

        switch (ipl::System::getRegion()) {
        case 0xb: {
            void* oemDictionary;
            void* systemDictionary;
            systemDictionary = ipl::System::getKeyboard()->getZiSystemDic();
            oemDictionary = ipl::System::getKeyboard()->getZiOemDic();
            textinput::InputForm* inputForm = ipl::System::getKeyboard()->baseMgr()->getInputForm();
            inputForm->setZiDictionary(oemDictionary, systemDictionary);
            setting.type = static_cast<ipl::keyboard::Manager::KeyboardType>(0xd);
            break;
        }
        case 6:
            ipl::System::getKeyboard()->baseMgr()->enableKSXFilter(true);
            setting.type = static_cast<ipl::keyboard::Manager::KeyboardType>(0xd);
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
        }
        setDefaultTitleText(mString.mValue, false);
        if (mString.mbValidMail != 0 &&
            isDupCode__Q43ipl5scene11AddressEdit6StringCFv(&mString) == 0 &&
            isMyCode__Q43ipl5scene11AddressEdit6StringCFv(&mString) == 0) {
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
            void* oemDictionary;
            void* systemDictionary;
            systemDictionary = ipl::System::getKeyboard()->getZiSystemDic();
            oemDictionary = ipl::System::getKeyboard()->getZiOemDic();
            textinput::InputForm* inputForm = ipl::System::getKeyboard()->baseMgr()->getInputForm();
            inputForm->setZiDictionary(oemDictionary, systemDictionary);
            setting.type = static_cast<ipl::keyboard::Manager::KeyboardType>(0xd);
            break;
        }
        case 6:
            ipl::System::getKeyboard()->baseMgr()->enableKSXFilter(true);
            setting.type = static_cast<ipl::keyboard::Manager::KeyboardType>(0xd);
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
    if (event != 0) {
        return;
    }
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
                isDupCode__Q43ipl5scene11AddressEdit6StringCFv(
                    &mString) == 0 &&
                isMyCode__Q43ipl5scene11AddressEdit6StringCFv(
                    &mString) == 0) {
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

    u32 messageId = MESG_ERROR_NWC24_SERVER;
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
    const NWC24FriendInfo& friendInfo = mpFriendCache->getInfo(mSelectedFriend);
    memcpy(&sFriendInfo__Q23ipl5scene, &friendInfo, sizeof(sFriendInfo__Q23ipl5scene));
    mString.setName(reinterpret_cast<const wchar_t*>(sFriendInfo__Q23ipl5scene.attr.name));
    const wchar_t* name = mString.mName;
    nw4r::lyt::Pane* namePane =
        mpCodeLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_name_00", true);
    set_textbox(namePane, name);

    wchar_t wiiNo[0x100];
    wchar_t email[0x102];
    if (sFriendInfo__Q23ipl5scene.attr.type == 1) {
        memset(wiiNo, 0, sizeof(wiiNo));
        ipl::scene::AddressEdit::wiiid_utf16(sFriendInfo__Q23ipl5scene.addr.wiiId, wiiNo);
        mString.setWiiNo(wiiNo);
    } else {
        memset(email, 0, sizeof(email));
        ipl::utility::CharacterCode::ANSIToUTF16(email, reinterpret_cast<const u8*>(&sFriendInfo__Q23ipl5scene.addr), 0x102);
        mString.setEMail(email);
    }
    const wchar_t* displayText = mString.mDisplayText;
    nw4r::lyt::Pane* friendCodePane =
        mpCodeLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_frnd_crd_00", true);
    set_textbox(friendCodePane, displayText);
    memcpy(&mCreateID, &sFriendInfo__Q23ipl5scene.attr.fdId, sizeof(mCreateID));
}

void ipl::scene::AddressEdit::update_friendinfo() {
    memset(sFriendInfo__Q23ipl5scene.attr.name, 0, 0x18);
    wcsncpy(reinterpret_cast<wchar_t*>(sFriendInfo__Q23ipl5scene.attr.name), mString.mName, 0xa);
    memcpy(&sFriendInfo__Q23ipl5scene.attr.fdId, &mCreateID, sizeof(mCreateID));
    mpFriendCache->update(
        mSelectedFriend,
        reinterpret_cast<const wchar_t*>(sFriendInfo__Q23ipl5scene.attr.name),
        sFriendInfo__Q23ipl5scene.attr.fdId);
    static_cast<ipl::scene::Address*>(ipl::System::getScene(0x14))->reset_friend();
}
