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

extern "C" u8 __vt__Q33ipl5scene11AddressEdit[];
extern "C" void __ct__Q33ipl5scene14FaderSceneBaseFPQ23EGG4Heap(void*, EGG::Heap*);
extern "C" void __dt__Q33ipl6nigaoe6ObjectFv(void*, int);
extern "C" void __dt__Q33ipl5scene4BaseFv(void*, int);
extern "C" void __dl__FPv(void*);
extern "C" void reset_gui__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void start_point_event__Q33ipl5scene11AddressEditFPCcPQ33ipl10controller9Interface(
    ipl::scene::AddressEdit*, const char*, ipl::controller::Interface*);
extern "C" void start_left_event__Q33ipl5scene11AddressEditFPCc(
    ipl::scene::AddressEdit*, const char*);
extern "C" void start_trig_event__Q33ipl5scene11AddressEditFPCc(
    ipl::scene::AddressEdit*, const char*);
extern "C" void start_ipt_point_event__Q33ipl5scene11AddressEditFPCci(
    ipl::scene::AddressEdit*, const char*, int);
extern "C" void start_ipt_left_event__Q33ipl5scene11AddressEditFPCci(
    ipl::scene::AddressEdit*, const char*, int);
extern "C" void start_ipt_trig_event__Q33ipl5scene11AddressEditFPCci(
    ipl::scene::AddressEdit*, const char*, int);


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
        __dt__Q33ipl6nigaoe6ObjectFv(mpNigaoe, 1);
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

extern "C" void reset_gui__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    self->mpEditGui->init();
    self->mpInputGui->init();
    for (s32 i = 0; i < 5; ++i) {
        if (self->mPointCount[i] > 0) {
            ipl::layout::Animator* animator = self->mpCodeLayout->getAnim(i + 0xb);
            animator->initFrame();
            animator->restart();
        }
        self->mPointCount[i] = 0;
    }
}


extern "C" u8 __vt__Q33ipl5scene16AddressEditEvent[];
extern "C" u8 __vt__Q33ipl5scene17AddressInputEvent[];
extern "C" void* __nw__FUl(u32);
extern "C" ipl::layout::Object* __ct__Q33ipl6layout6ObjectFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePCcPCc(
    void*, EGG::Heap*, ipl::nand::LayoutFile*, const char*, const char*);
extern "C" ipl::math::VEC3* __ct__Q33ipl4math4VEC3Ffff(ipl::math::VEC3*, f32, f32, f32);
extern "C" ipl::scene::TextBalloon* __ct__Q33ipl5scene11TextBalloonFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePCcPCcRCQ33ipl4math4VEC3ff(
    void*, EGG::Heap*, ipl::nand::LayoutFile*, const char*, const char*, const ipl::math::VEC3&, f32, f32);
extern "C" BOOL RFLSearchOfficialData(const RFLCreateID*, u16*);
extern "C" ipl::gui::PaneManager* __ct__Q33ipl3gui11PaneManagerFPQ23gui12EventHandlerPCQ34nw4r3lyt8DrawInfoPQ23EGG4HeapPQ23EGG9Allocatorb(
    void*, gui::EventHandler*, const nw4r::lyt::DrawInfo*, EGG::Heap*, EGG::Allocator*, bool);
extern "C" void initAnmFrame__Q33ipl6layout8AnimatorFv(void*);
extern "C" NWC24FriendInfo sFriendInfo__Q23ipl5scene;
extern "C" char smArg__Q23ipl6System;
extern "C" const char* smButtonName__Q33ipl5scene6Button[];
extern "C" void readLayoutAsync__Q33ipl4nand7ManagerFPQ23EGG4HeapPCcb();
extern "C" void* List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(void*, u16);
extern "C" void getScene__Q33ipl5scene7ManagerFi();
extern "C" void setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler(void*, void*, void*);
extern "C" void animation__Q33ipl5scene6ButtonFi(void*, int);
extern "C" void calc__Q33ipl5scene11TextBalloonFv(void*);
extern "C" void calc__Q33ipl6layout6ObjectFv();
extern "C" bool isActive__Q33ipl5scene6ButtonCFv(void*);
extern "C" void update__Q33ipl5scene6ButtonFv(void*);
extern "C" void update__Q33ipl3gui11PaneManagerFv(void*);
extern "C" void setOrtho__Q33ipl7utility8GraphicsFUl();
extern "C" void draw__Q33ipl6layout6ObjectFv();
extern "C" void draw__Q33ipl5scene11TextBalloonFv();
extern "C" ipl::math::VEC3* __ct__Q33ipl4math4VEC3Ffff(ipl::math::VEC3*, f32, f32, f32);










extern "C" int get_button_no__Q33ipl5scene11AddressEditFPCc(void*, const char*);
extern "C" void callBtn1__Q23ipl12DialogWindowFUlUl(void*, u32, u32);
extern "C" void callS2Btn2__Q23ipl12DialogWindowFUlUlb();
extern "C" void reserveText__Q33ipl5scene6ButtonFiUl(void*, int, u32);
extern "C" void reserveAnm__Q33ipl5scene6ButtonFi(void*, int);
extern "C" void initFrame__Q33ipl7utility15FrameControllerFv(void*);
extern "C" void getMessage__Q33ipl7message7MessageCFUl();
extern "C" void del__Q33ipl5scene15FriendListCacheFUl();
extern "C" void reset_friend__Q33ipl5scene7AddressFv(void*);
extern "C" void add_friendinfo__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void delete_friendinfo__Q33ipl5scene11AddressEditFv(void*);
extern "C" void add__Q33ipl5scene15FriendListCacheFUlRC15NWC24FriendInfo(
    void*, u32, const NWC24FriendInfo&);
extern "C" void sendRegisterMail__Q33ipl5scene15FriendListCacheFUl(void*, u32);
extern "C" void update__Q33ipl5scene15FriendListCacheFUlPCwUx(void*, u32, const wchar_t*, u64);
extern "C" void setWiiNo__Q43ipl5scene11AddressEdit6StringFPCw(void*, const wchar_t*);
extern "C" void set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
    ipl::scene::AddressEdit*, nw4r::lyt::Pane*, const wchar_t*);
extern "C" void setDefaultTitleText__Q33ipl5scene11AddressEditFPCwb(
    ipl::scene::AddressEdit*, const wchar_t*, bool);
extern "C" void wiiid_utf16__Q33ipl5scene11AddressEditFUxPw(u64, wchar_t*);
extern "C" void ANSIToUTF16__Q33ipl7utility13CharacterCodeFPwPCUcl(wchar_t*, const u8*, s32);
extern "C" const wchar_t* getName__Q33ipl6nigaoe6ObjectCFv(void*);
extern "C" void nigaoe_create_callback_add__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv(
    ipl::nigaoe::Object*, void*);
extern "C" void nigaoe_create_callback_edit__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv(
    ipl::nigaoe::Object*, void*);
extern "C" NWC24Err NWC24CheckPublicMailAddr_(const char*);
extern "C" void reserveAllSceneDestruction__Q33ipl5scene4BaseFiPv(void*, int, void*);
extern "C" void createChildScene__Q33ipl5scene4BaseFiPQ33ipl5scene4BasePQ33ipl5scene4BasePv(
    void*, int, void*, void*, void*);
extern "C" void __div2u();
extern "C" void __mod2u();
extern "C" void UTF16ToANSI__Q33ipl7utility13CharacterCodeFPUcPCwl(u8*, const wchar_t*, s32);
extern "C" void isValidId__Q33ipl5scene15FriendListCacheFRCUx();
extern "C" void isDupId__Q33ipl5scene15FriendListCacheFRCUx();
extern "C" void isDupMail__Q33ipl5scene15FriendListCacheFPCc();
extern "C" NWC24Err getErrCode__Q33ipl5scene15FriendListCacheCFv(void*);
extern "C" BOOL getConnectEnableFlag__Q33ipl3ncd10NCDSettingFv();
extern "C" void set_err_msg__Q33ipl5scene11AddressEditFPwUl8NWC24Err(
    ipl::scene::AddressEdit*, wchar_t*, u32, NWC24Err);
extern "C" void get_friendinfo__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void reset_gui__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" u64 utf16_wiiid__Q33ipl5scene11AddressEditFPCw(const wchar_t*);
extern "C" void _savegpr_29();
extern "C" void _restgpr_29();
extern "C" void _savegpr_23();
extern "C" void _savegpr_27();
extern "C" void _restgpr_23();
extern "C" void _restgpr_27();
extern "C" void stt_add_code_fadein__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_add_code_fadeout__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_add_code_input__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_add_code_normal__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_add_confirm_fadein__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_add_confirm_fadeout__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_add_confirm_normal__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_add_mii_fadein__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_add_mii_fadeout__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_add_mii_input__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_add_mii_normal__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_add_name_fadein__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_add_name_fadeout__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_add_name_input__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_add_name_normal__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_ipt_input__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_ipt_normal__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_ipt_wait_fadein__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_ipt_wait_fadeout__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_msg_add_rlt__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_msg_code_invalid__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_msg_del_rlt__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_msg_dup_email__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_msg_dup_wii_no__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_msg_my_wii_no__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_msg_net__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_msg_no_established__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_msg_no_mii__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_msg_no_mii_add__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_msg_wc__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_select_mii__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_wait_btn_fadein__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_wait_btn_fadeout__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_wait_del_msg_fadein__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_wait_del_msg_fadeout__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_wait_del_msg_fadeout_to_rlt__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_wait_delete__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_wait_decide_anm_add__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_wait_parental__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_wait_parental_dst__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_wait_parental_dst_wc__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_wait_parental_wc__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void enableKSXFilter__Q29textinput7ManagerFb(textinput::Manager*, bool);
extern "C" void __ct__Q43ipl8keyboard7Manager15KeyboardSettingFQ43ipl8keyboard7Manager12KeyboardTypePCwUlUl(
    ipl::keyboard::Manager::KeyboardSetting*, ipl::keyboard::Manager::KeyboardType,
    const wchar_t*, u32, u32);
extern "C" void __ct__Q43ipl8keyboard7Manager15KeyboardSettingFQ43ipl8keyboard7Manager12KeyboardTypePCwUlUl(
    ipl::keyboard::Manager::KeyboardSetting* setting,
    ipl::keyboard::Manager::KeyboardType type, const wchar_t* value, u32 stringLimit,
    u32 rowLimit) {
    setting->type = type;
    setting->wcString = value;
    setting->stringLimit = stringLimit;
    setting->rowLimit = rowLimit;
}
extern "C" void stt_normal__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_msg_no_established__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    switch (ipl::System::getDialog()->getLastResult()) {
    case 1:
        reset_gui__Q33ipl5scene11AddressEditFv(self);
        self->mState = 0;
        break;
    default:
        break;
    }
}

extern "C" void stt_msg_code_invalid__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    ipl::System::getScene(5);
    switch (ipl::System::getDialog()->getLastResult()) {
    case 1:
        self->mState = 0x11;
        break;
    default:
        break;
    }
}

extern "C" void stt_msg_dup_wii_no__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    ipl::System::getScene(5);
    switch (ipl::System::getDialog()->getLastResult()) {
    case 1:
        self->mState = 0x11;
        break;
    default:
        break;
    }
}

extern "C" void stt_msg_dup_email__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    ipl::System::getScene(5);
    switch (ipl::System::getDialog()->getLastResult()) {
    case 1:
        self->mState = 0x11;
        break;
    default:
        break;
    }
}

extern "C" void stt_msg_my_wii_no__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    ipl::System::getScene(5);
    switch (ipl::System::getDialog()->getLastResult()) {
    case 1:
        self->mState = 0x11;
        break;
    default:
        break;
    }
}

extern "C" void stt_msg_no_mii_add__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    ipl::System::getScene(5);
    switch (ipl::System::getDialog()->getLastResult()) {
    case 1:
        self->mState = 0x1d;
        break;
    default:
        break;
    }
}

extern "C" void stt_msg_add_rlt__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    void* button = ipl::System::getScene(5);
    switch (ipl::System::getDialog()->getLastResult()) {
    case 1:
        reserveAnm__Q33ipl5scene6ButtonFi(button, 0xf);
        self->mState = 0x30;
        break;
    default:
        break;
    }
}

extern "C" void stt_add_code_normal__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    void* button = ipl::System::getScene(5);
    if (isActive__Q33ipl5scene6ButtonCFv(button)) {
        update__Q33ipl5scene6ButtonFv(button);
    }
    if (self->mState == 0x11) {
        update__Q33ipl3gui11PaneManagerFv(self->mpInputGui);
    }
}

extern "C" void stt_add_name_normal__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    void* button = ipl::System::getScene(5);
    if (isActive__Q33ipl5scene6ButtonCFv(button)) {
        update__Q33ipl5scene6ButtonFv(button);
    }
    if (self->mState == 0x19) {
        update__Q33ipl3gui11PaneManagerFv(self->mpInputGui);
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
    UTF16ToANSI__Q33ipl7utility13CharacterCodeFPUcPCwl(address, value, sizeof(address));
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

extern "C" void create__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {

    ipl::layout::Object* bLayout;
    ipl::scene::Board* board = static_cast<ipl::scene::Board*>(ipl::System::getScene(4));
    ipl::nand::LayoutFile* boardFile = board->getLayoutFile();

    bLayout = reinterpret_cast<ipl::layout::Object*>(__nw__FUl(0x580));
    if (bLayout != NULL) {
        bLayout = __ct__Q33ipl6layout6ObjectFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePCcPCc(
            bLayout, self->getHeap(), boardFile, "arc", "th_Adress_b.brlyt");
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
        new (editEvent) ipl::scene::AddressEditEvent(self);
    }
    void* editManagerMemory = __nw__FUl(0x34);
    ipl::gui::PaneManager* editManager = reinterpret_cast<ipl::gui::PaneManager*>(editManagerMemory);
    if (editManagerMemory != NULL) {
        editManager = __ct__Q33ipl3gui11PaneManagerFPQ23gui12EventHandlerPCQ34nw4r3lyt8DrawInfoPQ23EGG4HeapPQ23EGG9Allocatorb(
            editManagerMemory, static_cast<gui::EventHandler*>(editEvent), bLayout->getDrawInfo(), NULL, NULL,
            false);
    }
    editManager->setupScene(bLayout);
    editManager->setAllComponentTriggerTarget(false);
    for (s32 i = 0; i < 5; i++) {
        const char* paneName = sButtonPaneNames[i];
        nw4r::lyt::Pane* pane = bLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(paneName, true);
        editManager->setTriggerTarget(pane, true);
    }
    self->mpCodeLayout = bLayout;
    self->mpEditEvent = editEvent;
    self->mpEditGui = editManager;

    nw4r::lyt::Pane* textPane = bLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_crd_btn_00", true);
    set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, textPane, ipl::System::getMessage(0x2a));
    textPane = (self->mpCodeLayout)
        ->getNW4RLyt()->GetRootPane()->FindPaneByName("T_crd_btn_10", true);
    set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, textPane, ipl::System::getMessage(0x2b));
    textPane = (self->mpCodeLayout)
        ->getNW4RLyt()->GetRootPane()->FindPaneByName("T_crd_btn_11", true);
    set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, textPane, ipl::System::getMessage(0x2f));
    textPane = (self->mpCodeLayout)
        ->getNW4RLyt()->GetRootPane()->FindPaneByName("T_crd_btn_gry", true);
    set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, textPane, ipl::System::getMessage(0x2a));
    textPane = (self->mpCodeLayout)
        ->getNW4RLyt()->GetRootPane()->FindPaneByName("T_card_msg_00", true);
    set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, textPane, L"");
    textPane = (self->mpCodeLayout)
        ->getNW4RLyt()->GetRootPane()->FindPaneByName("T_name_00", true);
    set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, textPane, L"");
    textPane = (self->mpCodeLayout)
        ->getNW4RLyt()->GetRootPane()->FindPaneByName("T_frnd_crd_00", true);
    set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, textPane, L"");

    ipl::layout::Object* cLayout = reinterpret_cast<ipl::layout::Object*>(__nw__FUl(0x580));
    if (cLayout != NULL) {
        cLayout = __ct__Q33ipl6layout6ObjectFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePCcPCc(
            cLayout, self->getHeap(), boardFile, "arc", "th_Adress_c.brlyt");
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
        new (inputEvent) ipl::scene::AddressInputEvent(self);
    }
    void* inputManagerMemory = __nw__FUl(0x34);
    ipl::gui::PaneManager* inputManager = reinterpret_cast<ipl::gui::PaneManager*>(inputManagerMemory);
    if (inputManagerMemory != NULL) {
        inputManager = __ct__Q33ipl3gui11PaneManagerFPQ23gui12EventHandlerPCQ34nw4r3lyt8DrawInfoPQ23EGG4HeapPQ23EGG9Allocatorb(
            inputManagerMemory, static_cast<gui::EventHandler*>(inputEvent), cLayout->getDrawInfo(), NULL, NULL,
            false);
    }
    inputManager->setupScene(cLayout);
    inputManager->setAllComponentTriggerTarget(false);
    textPane = cLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(sInputPaneName, true);
    inputManager->setTriggerTarget(textPane, true);
    self->mpNameLayout = cLayout;
    self->mpInputEvent = inputEvent;
    self->mpInputGui = inputManager;

    ipl::layout::Object* background = reinterpret_cast<ipl::layout::Object*>(__nw__FUl(0x580));
    if (background != NULL) {
        background = __ct__Q33ipl6layout6ObjectFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePCcPCc(
            background, self->getHeap(), boardFile, "arc", "my_Back_a.brlyt");
    }
    self->mpBackgroundLayout = background;
    background->bind("my_Back_a_Apear.brlan", "Picture_00", false, true);
    (self->mpBackgroundLayout)
        ->bind("my_Back_a_Lost.brlan", "Picture_00", false, false);
    (self->mpBackgroundLayout)->finishBinding();
    (self->mpBackgroundLayout)
        ->getAnim(0)->initAnmFrame();

    self->mString.clear();
    memset(&sFriendInfo__Q23ipl5scene, 0, sizeof(sFriendInfo__Q23ipl5scene));
    self->mpNigaoe = 0;
    self->mNigaoeState = 0;
    ipl::scene::SceneObj* addressScene = ipl::System::getScene(0x14);
    ipl::scene::Address* address = static_cast<ipl::scene::Address*>(addressScene);
    self->mpFriendCache = address->getFriendCache();

    s32 mode = self->mMode;
    ipl::layout::Animator* animator;
    switch (mode) {
    case 0: {
        self->mSelectedFriend = address->getChosenFriendIndex();
        get_friendinfo__Q33ipl5scene11AddressEditFv(self);
        u32 friendIndex = self->mSelectedFriend;
        if (self->mpFriendCache->getInfo(friendIndex).attr.status == 2) {
            (self->mpCodeLayout)->getAnim(0x15)->initAnmFrame();
            (self->mpCodeLayout)->getAnim(0x1a)->initAnmFrame();
        } else {
            (self->mpCodeLayout)->getAnim(0x10)->initAnmFrame();
            (self->mpCodeLayout)->getAnim(0x1b)->initAnmFrame();
        }
        animator = (self->mpCodeLayout)->getAnim(0);
        animator->initFrame();
        const wchar_t* friendText = self->mString.mName;
        animator->restart();
        textPane = (self->mpCodeLayout)
            ->getNW4RLyt()->GetRootPane()->FindPaneByName("T_name_00", true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, textPane, friendText);
        textPane = (self->mpCodeLayout)
            ->getNW4RLyt()->GetRootPane()->FindPaneByName("T_frnd_crd_00", true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, textPane, self->mString.mDisplayText);
        self->mState = 0;
            break;
    }
    case 1: {
        animator = (self->mpNameLayout)->getAnim(0);
        animator->initFrame();
        animator->restart();
        animator = (self->mpNameLayout)->getAnim(1);
        animator->initFrame();
        animator->restart();
        animator = (self->mpNameLayout)->getAnim(3);
        animator->initFrame();
        animator->restart();
        (self->mpCodeLayout)->getAnim(0x1a)->initAnmFrame();
        (self->mpCodeLayout)->getAnim(0x10)->initAnmFrame();
        textPane = (self->mpNameLayout)
            ->getNW4RLyt()->GetRootPane()->FindPaneByName("T_question_00", true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, textPane, ipl::System::getMessage(0x31));
        textPane = (self->mpNameLayout)
            ->getNW4RLyt()->GetRootPane()->FindPaneByName("T_msg_00", true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, textPane, ipl::System::getMessage(0x47));
        self->mState = 0x10;
            break;
    }
    case 2: {
        animator = (self->mpNameLayout)->getAnim(0);
        animator->initFrame();
        animator->restart();
        animator = (self->mpNameLayout)->getAnim(1);
        animator->initFrame();
        animator->restart();
        animator = (self->mpNameLayout)->getAnim(3);
        animator->initFrame();
        animator->restart();
        (self->mpCodeLayout)->getAnim(0x1a)->initAnmFrame();
        (self->mpCodeLayout)->getAnim(0x10)->initAnmFrame();
        textPane = (self->mpNameLayout)
            ->getNW4RLyt()->GetRootPane()->FindPaneByName("T_question_00", true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, textPane, ipl::System::getMessage(0x3f));
        textPane = (self->mpNameLayout)
            ->getNW4RLyt()->GetRootPane()->FindPaneByName("T_msg_00", true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, textPane, ipl::System::getMessage(0x48));
        self->mState = 0x10;
            break;
    }
    default:
        break;
    }

create_mode_done:

    s16 miiIndex[2];
    if (RFLSearchOfficialData(&self->mCreateID,
            reinterpret_cast<u16*>(miiIndex))) {
        ipl::System::getMiiManager()->create(ipl::System::getMem2App(), 0x4c, 0x4c, miiIndex[0],
            nigaoe_create_callback_edit__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv, self);
        self->mNigaoeState = 1;
    }

    ipl::System::getKeyboard()->init();

    ipl::scene::TextBalloon* balloon = reinterpret_cast<ipl::scene::TextBalloon*>(__nw__FUl(0x3c));
    if (balloon != NULL) {
        f32 balloonWidth = 30.0f;
        f32 balloonHeight = 120.0f;
        EGG::Heap* heap = self->getHeap();
        ipl::math::VEC3 position;
        ipl::math::VEC3* positionPtr = __ct__Q33ipl4math4VEC3Ffff(&position, 0.0f, 0.0f, 0.0f);
        balloon = __ct__Q33ipl5scene11TextBalloonFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePCcPCcRCQ33ipl4math4VEC3ff(
            balloon, heap,
            self->mpBalloonFile,
            "arc", "my_IplTopBalloon_a.brlyt", *positionPtr, balloonHeight, balloonWidth);
    }
    self->mpBalloon = balloon;
}

extern "C" void stt_wait_decide_anm__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    bool complete = true;
    void* button = ipl::System::getScene(5);
    for (s32 i = 0; i < 5; ++i) {
        u16 index = static_cast<u16>(self->mSelectedButton + 6);
        complete = complete && !self->mpCodeLayout->getAnim(index)->isPlaying();
    }
    if (!complete) {
        return;
    }

    switch (self->mSelectedButton) {
    case 2: {
        u32 friendIndex = self->mSelectedFriend;
        ipl::layout::Animator* animator;
        if (self->mpFriendCache->getInfo(friendIndex).attr.status == 2) {
            animator = self->mpCodeLayout->getAnim(0x15);
        } else {
            animator = self->mpCodeLayout->getAnim(0x1b);
        }
        animator->initFrame();
        animator->restart();
        animator = self->mpCodeLayout->getAnim(0x16);
        animator->initFrame();
        animator->restart();
        animator = self->mpCodeLayout->getAnim(0x17);
        animator->initFrame();
        animator->restart();
        reserveAnm__Q33ipl5scene6ButtonFi(button, 0xc);
        self->mState = 3;
        self->mpBalloon->fadeoutForce();
        reset_gui__Q33ipl5scene11AddressEditFv(self);
        break;
    }
    case 1: {
        reserveAnm__Q33ipl5scene6ButtonFi(button, 0xc);
        reserveText__Q33ipl5scene6ButtonFiUl(button, 1, 0x2e);
        reserveAnm__Q33ipl5scene6ButtonFi(button, 0xf);
        ipl::layout::Animator* animator = self->mpNameLayout->getAnim(0);
        animator->initFrame();
        animator->restart();
        animator = self->mpNameLayout->getAnim(1);
        animator->initFrame();
        animator->restart();
        animator = self->mpNameLayout->getAnim(2);
        animator->initFrame();
        animator->restart();
        self->mpNameLayout->getAnim(3)->initAnmFrame();
        animator = self->mpBackgroundLayout->getAnim(0);
        animator->initFrame();
        animator->restart();
        nw4r::lyt::Pane* textPane = self->mpNameLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(
            "T_question_00", true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, textPane, ipl::System::getMessage(0x32));
        textPane = self->mpNameLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_name_00", true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, textPane, self->mString.mName);
        textPane = self->mpNameLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_msg_00", true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, textPane, ipl::System::getMessage(0x49));
        self->mpBalloon->fadeoutForce();
        reset_gui__Q33ipl5scene11AddressEditFv(self);
        self->mState = 0xc;
        break;
    }
    case 3: {
        if (self->mNigaoeState != 1) {
            self->mNigaoeState = 0;
            if (RFLGetAvailableOfficialDataNum() != 0) {
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xc);
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xb);
                createChildScene__Q33ipl5scene4BaseFiPQ33ipl5scene4BasePQ33ipl5scene4BasePv(
                    self, 0x1c, self, 0, reinterpret_cast<void*>(1));
                self->mState = 0xb;
            } else {
                ipl::System::getDialog()->callBtn1(0x17c, 0x2e);
                self->mState = 0xa;
            }
            self->mpBalloon->fadeoutForce();
        }
        break;
    }
    case 0: {
        SCParentalControlsInfo parentalInfo;
        BOOL parentalResult = SCGetParentalControl(&parentalInfo);
        if (!getConnectEnableFlag__Q33ipl3ncd10NCDSettingFv()) {
            animation__Q33ipl5scene6ButtonFi(button, 0x1d);
            ipl::System::getDialog()->callBtn2(0x144, 0x146, 0x25, false);
            self->mState = 0x27;
        } else if ((SCGetWCFlags() & 1) == 0) {
            animation__Q33ipl5scene6ButtonFi(button, 0x1d);
            ipl::System::getDialog()->callBtn2(0x17e, 0x146, 0x25, false);
            self->mState = 0x2a;
        } else if (parentalResult != 0 && (parentalInfo.enable & 0x80) != 0 &&
                   (SCGetNetContentRestrictions() & 2) != 0) {
            animation__Q33ipl5scene6ButtonFi(button, 0x1d);
            ipl::System::getDialog()->callBtn1(0x14c, 0x2e);
            self->mState = 0x2d;
        } else {
            s32 friendError = self->mpFriendCache->check();
            if (friendError == NWC24_ERR_NETWORK ||
                self->mpFriendCache->getLastErr() == NWC24_ERR_SERVER ||
                self->mpFriendCache->getLastErr() == NWC24_ERR_FULL) {
                wchar_t errorMessage[0x400];
                wchar_t* errorMessagePointer = errorMessage - 1;
                for (s32 i = 0; i < 0x200; i++) {
                    errorMessagePointer[1] = 0;
                    errorMessagePointer += 2;
                    *errorMessagePointer = 0;
                }
                set_err_msg__Q33ipl5scene11AddressEditFPwUl8NWC24Err(
                    self, errorMessage, 0x400,
                    static_cast<NWC24Err>(self->mpFriendCache->getLastErr()));
                ipl::System::getDialog()->callBtn1(errorMessage, 0x2e);
                animation__Q33ipl5scene6ButtonFi(button, 0x1d);
                self->mState = 0x2e;
            } else {
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xc);
                reserveText__Q33ipl5scene6ButtonFiUl(button, 1, 0x27);
                reserveText__Q33ipl5scene6ButtonFiUl(button, 0, 0x4f);
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xf);
                self->requestSceneChange(0xb, reinterpret_cast<void*>(1));
                ipl::layout::Animator* animator = self->mpCodeLayout->getAnim(0x1e);
                animator->initFrame();
                animator->restart();
                self->mState = 0x30;
            }
        }
        self->mpBalloon->fadeoutForce();
        reset_gui__Q33ipl5scene11AddressEditFv(self);
        break;
    }
    case 4: {
        ipl::System::getDialog()->callBtn1(self->mString.getDispCodeLong(), 0x2e);
        self->mpBalloon->fadeoutForce();
        reset_gui__Q33ipl5scene11AddressEditFv(self);
        self->mState = 9;
        break;
    }
    default:
        self->mState = 0;
        break;
    }
}

extern "C" void stt_wait_delete__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    void* button = ipl::System::getScene(5);
    switch (ipl::System::getDialog()->getLastResult()) {
    case 2: {
        delete_friendinfo__Q33ipl5scene11AddressEditFv(self);
        ipl::layout::Animator* animator = self->mpCodeLayout->getAnim(0x1d);
        animator->initFrame();
        animator->restart();
        self->mState = 6;
        break;
    }
    case 1: {
        reserveAnm__Q33ipl5scene6ButtonFi(button, 0xb);
        ipl::layout::Animator* animator = self->mpCodeLayout->getAnim(0x1d);
        animator->initFrame();
        animator->restart();
        self->mState = 5;
        break;
    }
    default:
        break;
    }
}

extern "C" void stt_add_confirm_fadein__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    if (!self->mpCodeLayout->getAnim(0)->isPlaying()) {
        self->mState = 0x22;
    }
}

extern "C" void stt_add_name_fadein__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    if (!self->mpNameLayout->getAnim(1)->isPlaying() &&
        !self->mpNameLayout->getAnim(3)->isPlaying() &&
        !self->mpNameLayout->getAnim(2)->isPlaying()) {
        self->mState = 0x19;
    }
}

extern "C" void stt_add_mii_fadein__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    if (!self->mpNameLayout->getAnim(1)->isPlaying() &&
        !self->mpNameLayout->getAnim(4)->isPlaying() &&
        !self->mpNameLayout->getAnim(0)->isPlaying()) {
        self->mState = 0x1d;
    }
}

extern "C" void stt_add_code_fadein__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    if (!self->mpNameLayout->getAnim(0)->isPlaying() &&
        !self->mpNameLayout->getAnim(1)->isPlaying() &&
        !self->mpNameLayout->getAnim(3)->isPlaying() &&
        !self->mpNameLayout->getAnim(4)->isPlaying() &&
        !self->mpNameLayout->getAnim(2)->isPlaying()) {
        self->mState = 0x11;
    }
}

extern "C" void stt_add_name_input__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    ipl::keyboard::Manager::State* state = ipl::System::getKeyboard()->getState();
    void* button = ipl::System::getScene(5);
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
        bool nameWasEmpty = self->mString.mName[0] == 0;
        if (state->pressOK) {
            self->mString.setName(state->wcString);
            nw4r::lyt::Pane* pane = self->mpNameLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(
                "T_name_00", true);
            set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
                self, pane, self->mString.mName);
        }
        if (self->mString.mName[0] == 0) {
            if (!nameWasEmpty) {
                ipl::layout::Animator* animator = self->mpNameLayout->getAnim(6);
                animator->initFrame();
                animator->restart();
                animator = self->mpNameLayout->getAnim(3);
                animator->initFrame();
                animator->restart();
            }
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xb);
        } else {
            if (nameWasEmpty) {
                ipl::layout::Animator* animator = self->mpNameLayout->getAnim(2);
                animator->initFrame();
                animator->restart();
                animator = self->mpNameLayout->getAnim(7);
                animator->initFrame();
                animator->restart();
            }
            if (self->mString.mbNameNotEmpty) {
                reserveText__Q33ipl5scene6ButtonFiUl(button, 1, 0x2e);
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xf);
            } else {
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xb);
            }
        }
    }
    goto done;

state_visible: {
        self->mState = 0x19;
        if (static_cast<u32>(ipl::System::getRegion()) == 6) {
            enableKSXFilter__Q29textinput7ManagerFb(
                ipl::System::getKeyboard()->baseMgr(), false);
        }
    }
    goto done;

state_hidden:
    setDefaultTitleText__Q33ipl5scene11AddressEditFPCwb(
        self, NULL, ipl::System::getKeyboard()->baseMgr()->isVacancy());

done:
    return;
}

extern "C" void stt_add_mii_normal__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    void* button = ipl::System::getScene(5);
    if (isActive__Q33ipl5scene6ButtonCFv(button)) {
        update__Q33ipl5scene6ButtonFv(button);
    }
    if (self->mState == 0x1d) {
        update__Q33ipl3gui11PaneManagerFv(self->mpInputGui);
    }
}

extern "C" void stt_add_mii_input__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    ipl::scene::Base* child = self->getChild();
    if (child != NULL) {
        ipl::scene::FaceSelect* faceSelect = static_cast<ipl::scene::FaceSelect*>(child);
        s32 faceId = faceSelect->getSelectedFaceId();
        if (faceId >= 0 && ipl::System::getMiiManager()->isAvalable(faceId) &&
            self->mNigaoeState == 0) {
            RFLAdditionalInfo additionalInfo;
            RFLGetAdditionalInfo(&additionalInfo, RFLDataSource_Official, NULL, faceId);
            if (!RFLiIsSameID(&self->mCreateID, &additionalInfo.createID)) {
                self->mCreateID = additionalInfo.createID;
                ipl::System::getMiiManager()->create(ipl::System::getMem2App(), 0x4c, 0x4c, faceId,
                    nigaoe_create_callback_add__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv,
                    self);
                self->mNigaoeState = 1;
                self->mpInputGui->init();
                self->mpBalloon->fadeoutForce();
            }
        }
    }

    if (self->getChild() == NULL &&
        ipl::System::getSceneManager()->getReservedScene() == NULL) {
        setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler(
            ipl::System::getScene(5), static_cast<gui::EventHandler*>(self), NULL);
        self->mState = 0x1d;
        self->mNigaoeState = 0;
    }
}

extern "C" void stt_add_mii_fadeout__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    if (self->mpNameLayout->getAnim(9)->isPlaying() ||
        self->mpNameLayout->getAnim(5)->isPlaying() ||
        self->mpNameLayout->getAnim(8)->isPlaying()) {
        return;
    }

    if (self->mSubState == 5) {
        ipl::layout::Animator* animator = self->mpNameLayout->getAnim(1);
        animator->initFrame();
        animator->restart();
        animator = self->mpNameLayout->getAnim(2);
        animator->initFrame();
        animator->restart();

        nw4r::lyt::Pane* pane =
            self->mpNameLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_question_00", true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, pane, ipl::System::getMessage(0x32));
        pane = self->mpNameLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_name_00", true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, pane, self->mString.mName);
        pane = self->mpNameLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_msg_00", true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, pane, ipl::System::getMessage(0x49));
        self->mState = 0x18;
        return;
    }

    if (self->mSubState == 7) {
        ipl::layout::Animator* animator = self->mpCodeLayout->getAnim(0);
        animator->initFrame();
        animator->restart();
        self->mpCodeLayout->getAnim(0x10)->initAnmFrame();
        self->mpCodeLayout->getAnim(0x11)->initAnmFrame();
        self->mpCodeLayout->getAnim(0x12)->initAnmFrame();
        animator = self->mpCodeLayout->getAnim(0x1c);
        animator->initFrame();
        animator->restart();

        nw4r::lyt::Pane* pane =
            self->mpCodeLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_card_msg_00", true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, pane, ipl::System::getMessage(0x44));
        pane = self->mpCodeLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_name_00", true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, pane, self->mString.mName);
        pane = self->mpCodeLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_frnd_crd_00", true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, pane, self->mString.mDisplayText);
        self->mState = 0x21;
    }
}

extern "C" void stt_ipt_wait_fadeout__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    if (!self->mpNameLayout->getAnim(5)->isPlaying() &&
        !self->mpNameLayout->getAnim(7)->isPlaying() &&
        !self->mpNameLayout->getAnim(6)->isPlaying() &&
        !self->mpNameLayout->getAnim(8)->isPlaying() &&
        !self->mpNameLayout->getAnim(9)->isPlaying() &&
        !self->mpBackgroundLayout->getAnim(1)->isPlaying()) {
        self->mState = 0;
    }
}

extern "C" void stt_wait_del_msg_fadeout__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    if (!self->mpCodeLayout->getAnim(0x1d)->isPlaying()) {
        u32 friendIndex = self->mSelectedFriend;
        u32 status = self->mpFriendCache->getInfo(friendIndex).attr.status;
        ipl::layout::Animator* animator;
        if (status == 2) {
            animator = self->mpCodeLayout->getAnim(0x10);
        } else {
            animator = self->mpCodeLayout->getAnim(0x1a);
        }
        animator->initFrame();
        animator->restart();
        animator = self->mpCodeLayout->getAnim(0x11);
        animator->initFrame();
        animator->restart();
        animator = self->mpCodeLayout->getAnim(0x12);
        animator->initFrame();
        animator->restart();
        self->mState = 2;
    }
}

extern "C" void stt_msg_no_mii__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    switch (ipl::System::getDialog()->getLastResult()) {
    case 1:
        self->mpEditGui->init();
        for (u32 i = 0; i < 5; ++i) {
            self->mPointCount[i] = 0;
        }
        self->mState = 0;
        break;
    default:
        break;
    }
}

extern "C" void stt_add_confirm_fadeout__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    if (!self->mpCodeLayout->getAnim(0x1e)->isPlaying()) {
        void* button = ipl::System::getScene(5);
        switch (self->mSubState) {
        case 5: {
            ipl::layout::Animator* animator = self->mpNameLayout->getAnim(0);
            animator->initFrame();
            animator->restart();
            self->mState = 0x1c;
            break;
        }
        case 7:
            add_friendinfo__Q33ipl5scene11AddressEditFv(self);
            reserveText__Q33ipl5scene6ButtonFiUl(button, 1, 0x29);
            reset_friend__Q33ipl5scene7AddressFv(ipl::System::getScene(0x14));
            callBtn1__Q23ipl12DialogWindowFUlUl(ipl::System::getDialog(), 0x4a, 0x2e);
            self->mState = 0x26;
            break;
        default:
            break;
        }
    }
}

extern "C" void stt_wait_decide_anm_add__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    bool complete = true;
    for (s32 i = 0; i < 5; ++i) {
        u16 index = static_cast<u16>(self->mSelectedButton + 6);
        complete = (complete & !self->mpCodeLayout->getAnim(index)->isPlaying()) != 0;
    }
    if (complete) {
        switch (self->mSelectedButton) {
        case 4:
            self->mpEditGui->init();
            ipl::System::getDialog()->callBtn1(self->mString.getDispCodeLong(), 0x2e);
            self->mState = 0x25;
            break;
        default:
            break;
        }
    }
}

extern "C" void stt_add_confirm_normal__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    void* button = ipl::System::getScene(5);
    if (isActive__Q33ipl5scene6ButtonCFv(button)) {
        update__Q33ipl5scene6ButtonFv(button);
    }
    if (self->mState == 0x22) {
        self->mpEditGui->update();
    }
}

extern "C" void stt_wait_parental__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    ipl::scene::ParentalDialog* parental =
        static_cast<ipl::scene::ParentalDialog*>(ipl::System::getScene(0x1b));
    if (parental != NULL) {
        switch (parental->getResult()) {
        case 1:
            self->mbParentalOK = true;
            self->mState = 0x29;
            break;
        case 2:
        case 3:
            self->mbParentalOK = false;
            self->mState = 0x29;
            break;
        default:
            break;
        }
    }
}

extern "C" void stt_wait_parental_wc__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    ipl::scene::ParentalDialog* parental =
        static_cast<ipl::scene::ParentalDialog*>(ipl::System::getScene(0x1b));
    if (parental != NULL) {
        switch (parental->getResult()) {
        case 1:
            self->mbParentalOK = true;
            self->mState = 0x2c;
            break;
        case 2:
        case 3:
            self->mbParentalOK = false;
            self->mState = 0x2c;
            break;
        default:
            break;
        }
    }
}

extern "C" void stt_wait_parental_dst__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    if (self->getChild() == NULL) {
        if (self->mbParentalOK) {
            ipl::System::getFader()->fadeOut();
            reserveAllSceneDestruction__Q33ipl5scene4BaseFiPv(self, 0x12, reinterpret_cast<void*>(1));
            self->mState = 0x30;
        } else {
            animation__Q33ipl5scene6ButtonFi(ipl::System::getScene(5), 0xb);
            setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler(
                ipl::System::getScene(5), static_cast<gui::EventHandler*>(self), NULL);
            self->mState = 0;
        }
    }
}

extern "C" void stt_wait_parental_dst_wc__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    if (self->getChild() == NULL) {
        if (self->mbParentalOK) {
            ipl::System::getFader()->fadeOut();
            reserveAllSceneDestruction__Q33ipl5scene4BaseFiPv(self, 0x12, reinterpret_cast<void*>(4));
            self->mState = 0x30;
        } else {
            animation__Q33ipl5scene6ButtonFi(ipl::System::getScene(5), 0xb);
            setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler(
                ipl::System::getScene(5), static_cast<gui::EventHandler*>(self), NULL);
            self->mState = 0;
        }
    }
}

extern "C" void stt_msg_net__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    switch (ipl::System::getDialog()->getLastResult()) {
    case 2:
        self->mState = 0;
        break;
    case 1: {
        SCParentalControlsInfo info;
        if (SCGetParentalControl(&info) && (info.enable & SC_PARENTAL_FLAG_ENABLED)) {
            setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler(
                ipl::System::getScene(5), NULL, NULL);
            animation__Q33ipl5scene6ButtonFi(ipl::System::getScene(5), 0xc);
            createChildScene__Q33ipl5scene4BaseFiPQ33ipl5scene4BasePQ33ipl5scene4BasePv(
                self, 0x1b, self, NULL, reinterpret_cast<void*>(1));
            self->mbParentalOK = false;
            self->mState = 0x28;
        } else {
            ipl::System::getFader()->fadeOut();
            reserveAllSceneDestruction__Q33ipl5scene4BaseFiPv(self, 0x12, reinterpret_cast<void*>(1));
            self->mState = 0x30;
        }
        break;
    }
    default:
        break;
    }
}

extern "C" void stt_msg_wc__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    switch (ipl::System::getDialog()->getLastResult()) {
    case 2:
        self->mState = 0;
        break;
    case 1: {
        SCParentalControlsInfo info;
        if (SCGetParentalControl(&info) && (info.enable & SC_PARENTAL_FLAG_ENABLED)) {
            setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler(
                ipl::System::getScene(5), NULL, NULL);
            animation__Q33ipl5scene6ButtonFi(ipl::System::getScene(5), 0xc);
            createChildScene__Q33ipl5scene4BaseFiPQ33ipl5scene4BasePQ33ipl5scene4BasePv(
                self, 0x1b, self, NULL, reinterpret_cast<void*>(1));
            self->mbParentalOK = false;
            self->mState = 0x2b;
        } else {
            ipl::System::getFader()->fadeOut();
            reserveAllSceneDestruction__Q33ipl5scene4BaseFiPv(self, 0x12, reinterpret_cast<void*>(4));
            self->mState = 0x30;
        }
        break;
    }
    default:
        break;
    }
}

extern "C" void stt_select_mii__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    if (self->getChild() != NULL) {
        ipl::scene::FaceSelect* faceSelect =
            static_cast<ipl::scene::FaceSelect*>(self->getChild());
        s32 faceId = faceSelect->getSelectedFaceId();
        if (faceId >= 0 && ipl::System::getMiiManager()->isAvalable(faceId) &&
            self->mNigaoeState == 0) {
            RFLAdditionalInfo info;
            RFLGetAdditionalInfo(&info, RFLDataSource_Official, NULL, faceId);
            if (!RFLiIsSameID(&self->mCreateID, &info.createID)) {
                memcpy(&self->mCreateID, &info.createID, sizeof(self->mCreateID));
                ipl::System::getMiiManager()->create(
                    ipl::System::getMem2App(), 0x4c, 0x4c, faceId,
                    nigaoe_create_callback_edit__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv,
                    self);
                self->mNigaoeState = 1;
                self->update_friendinfo();
            }
        }
    }

    if (self->getChild() == NULL && ipl::System::getReservedScene() == NULL) {
        setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler(
            ipl::System::getScene(5), static_cast<gui::EventHandler*>(self), NULL);
        self->mState = 0;
        self->mNigaoeState = 0;
        self->mpEditGui->init();
        for (u32 i = 0; i < 5; ++i) {
            self->mPointCount[i] = 0;
        }
    }
}

extern "C" void set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
    ipl::scene::AddressEdit*, nw4r::lyt::Pane* pane, const wchar_t* text) {
    nw4r::lyt::TextBox* textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(pane);
    textBox->SetString(text, 0);
}

extern "C" void setDefaultTitleText__Q33ipl5scene11AddressEditFPCwb(
    ipl::scene::AddressEdit* self, const wchar_t* text, bool flag) {
    if (!flag && (text == NULL || *text != L'\0')) {
        goto set_empty_title;
    }
    switch (self->mState) {
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
            start_point_event__Q33ipl5scene11AddressEditFPCcPQ33ipl10controller9Interface(
                mpParent, paneName, static_cast<ipl::controller::Interface*>(data));
        }
    } else if (signedEvent >= 1) {
        if (signedEvent < 3) {
            start_left_event__Q33ipl5scene11AddressEditFPCc(mpParent, paneName);
        }
    } else if (signedEvent >= 0 && data != NULL &&
               static_cast<ipl::controller::Interface*>(data)->downTrg(0x100800)) {
        start_trig_event__Q33ipl5scene11AddressEditFPCc(mpParent, paneName);
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
            start_ipt_point_event__Q33ipl5scene11AddressEditFPCci(
                mpParent, paneName, controller->getChannel());
        }
    } else if (signedEvent >= 1) {
        if (signedEvent < 3 && controller != NULL) {
            start_ipt_left_event__Q33ipl5scene11AddressEditFPCci(
                mpParent, paneName, controller->getChannel());
        }
    } else if (signedEvent >= 0 && controller != NULL && controller->downTrg(0x100800)) {
        start_ipt_trig_event__Q33ipl5scene11AddressEditFPCci(
            mpParent, paneName, controller->getChannel());
    }
}

extern "C" void nigaoe_create_callback_edit__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv(
    ipl::nigaoe::Object* object, void* callbackWork) {
    ipl::scene::AddressEdit* self = static_cast<ipl::scene::AddressEdit*>(callbackWork);
    if (self->mpNigaoe != NULL) {
        __dt__Q33ipl6nigaoe6ObjectFv(self->mpNigaoe, 1);
    }
    self->mpNigaoe = object;
    nw4r::lyt::Pane* pane = self->mpCodeLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(
        "mii_icon_00", true);
    pane->GetMaterial()->SetTexture(0, object->getIconTexture());
    self->mNigaoeState = 2;
    self->mpBalloon->init(getName__Q33ipl6nigaoe6ObjectCFv(object), 0xa);
}

extern "C" void nigaoe_create_callback_add__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv(
    ipl::nigaoe::Object* object, void* callbackWork) {
    ipl::scene::AddressEdit* self = static_cast<ipl::scene::AddressEdit*>(callbackWork);
    if (self->mpNigaoe != NULL) {
        __dt__Q33ipl6nigaoe6ObjectFv(self->mpNigaoe, 1);
    }
    self->mpNigaoe = object;
    nw4r::lyt::Pane* pane = self->mpNameLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(
        "mii_icon_00", true);
    pane->GetMaterial()->SetTexture(0, object->getIconTexture());
    pane = self->mpCodeLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("mii_icon_00", true);
    pane->GetMaterial()->SetTexture(0, object->getIconTexture());
    self->mNigaoeState = 2;
    self->mpBalloon->init(getName__Q33ipl6nigaoe6ObjectCFv(object), 0xa);
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

extern "C" ipl::scene::FaderSceneCommand calcNormal__Q33ipl5scene11AddressEditFv(
    ipl::scene::AddressEdit* self) {
    switch (self->mState) {
        case 0:
            stt_normal__Q33ipl5scene11AddressEditFv(self);
            break;
        case 1:
            stt_wait_decide_anm__Q33ipl5scene11AddressEditFv(self);
            break;
        case 2:
            stt_wait_btn_fadein__Q33ipl5scene11AddressEditFv(self);
            break;
        case 3:
            stt_wait_btn_fadeout__Q33ipl5scene11AddressEditFv(self);
            break;
        case 4:
            stt_wait_del_msg_fadein__Q33ipl5scene11AddressEditFv(self);
            break;
        case 5:
            stt_wait_del_msg_fadeout__Q33ipl5scene11AddressEditFv(self);
            break;
        case 6:
            stt_wait_del_msg_fadeout_to_rlt__Q33ipl5scene11AddressEditFv(self);
            break;
        case 7:
            stt_wait_delete__Q33ipl5scene11AddressEditFv(self);
            break;
        case 8:
            stt_msg_del_rlt__Q33ipl5scene11AddressEditFv(self);
            break;
        case 9:
            self->stt_msg_code_edit();
            break;
        case 10:
            stt_msg_no_mii__Q33ipl5scene11AddressEditFv(self);
            break;
        case 11:
            stt_select_mii__Q33ipl5scene11AddressEditFv(self);
            break;
        case 12:
            stt_ipt_wait_fadein__Q33ipl5scene11AddressEditFv(self);
            break;
        case 13:
            stt_ipt_normal__Q33ipl5scene11AddressEditFv(self);
            break;
        case 14:
            stt_ipt_input__Q33ipl5scene11AddressEditFv(self);
            break;
        case 15:
            stt_ipt_wait_fadeout__Q33ipl5scene11AddressEditFv(self);
            break;
        case 16:
            stt_add_code_fadein__Q33ipl5scene11AddressEditFv(self);
            break;
        case 17:
            stt_add_code_normal__Q33ipl5scene11AddressEditFv(self);
            break;
        case 18:
            stt_add_code_input__Q33ipl5scene11AddressEditFv(self);
            break;
        case 19:
            stt_msg_code_invalid__Q33ipl5scene11AddressEditFv(self);
            break;
        case 20:
            stt_msg_dup_wii_no__Q33ipl5scene11AddressEditFv(self);
            break;
        case 21:
            stt_msg_dup_email__Q33ipl5scene11AddressEditFv(self);
            break;
        case 22:
            stt_msg_my_wii_no__Q33ipl5scene11AddressEditFv(self);
            break;
        case 23:
            stt_add_code_fadeout__Q33ipl5scene11AddressEditFv(self);
            break;
        case 24:
            stt_add_name_fadein__Q33ipl5scene11AddressEditFv(self);
            break;
        case 25:
            stt_add_name_normal__Q33ipl5scene11AddressEditFv(self);
            break;
        case 26:
            stt_add_name_input__Q33ipl5scene11AddressEditFv(self);
            break;
        case 27:
            stt_add_name_fadeout__Q33ipl5scene11AddressEditFv(self);
            break;
        case 28:
            stt_add_mii_fadein__Q33ipl5scene11AddressEditFv(self);
            break;
        case 29:
            stt_add_mii_normal__Q33ipl5scene11AddressEditFv(self);
            break;
        case 30:
            stt_add_mii_input__Q33ipl5scene11AddressEditFv(self);
            break;
        case 31:
            stt_msg_no_mii_add__Q33ipl5scene11AddressEditFv(self);
            break;
        case 32:
            stt_add_mii_fadeout__Q33ipl5scene11AddressEditFv(self);
            break;
        case 33:
            stt_add_confirm_fadein__Q33ipl5scene11AddressEditFv(self);
            break;
        case 34:
            stt_add_confirm_normal__Q33ipl5scene11AddressEditFv(self);
            break;
        case 35:
            stt_add_confirm_fadeout__Q33ipl5scene11AddressEditFv(self);
            break;
        case 36:
            stt_wait_decide_anm_add__Q33ipl5scene11AddressEditFv(self);
            break;
        case 37:
            self->stt_msg_code_add();
            break;
        case 38:
            stt_msg_add_rlt__Q33ipl5scene11AddressEditFv(self);
            break;
        case 39:
            stt_msg_net__Q33ipl5scene11AddressEditFv(self);
            break;
        case 40:
            stt_wait_parental__Q33ipl5scene11AddressEditFv(self);
            break;
        case 41:
            stt_wait_parental_dst__Q33ipl5scene11AddressEditFv(self);
            break;
        case 42:
            stt_msg_wc__Q33ipl5scene11AddressEditFv(self);
            break;
        case 43:
            stt_wait_parental_wc__Q33ipl5scene11AddressEditFv(self);
            break;
        case 44:
            stt_wait_parental_dst_wc__Q33ipl5scene11AddressEditFv(self);
            break;
        case 45:
            self->stt_msg_parental();
            break;
        case 46:
            self->stt_msg_nwc24_error();
            break;
        case 47:
            stt_msg_no_established__Q33ipl5scene11AddressEditFv(self);
            break;
    }

    switch (self->mState) {
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
            calc__Q33ipl5scene11TextBalloonFv(self->mpBalloon);
            break;
    }

    return self->mState == 0x30
        ? ipl::scene::FADER_SCN_NEXT
        : ipl::scene::FADER_SCN_CONTINUE;
}

extern "C" void stt_add_name_fadeout__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {

    if (!self->mpNameLayout->getAnim(5)->isPlaying() &&
        !self->mpNameLayout->getAnim(7)->isPlaying() &&
        !self->mpNameLayout->getAnim(6)->isPlaying() &&
        !self->mpNameLayout->getAnim(9)->isPlaying()) {
        s32 state = self->mSubState;
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
        ipl::layout::Animator* pane = self->mpNameLayout->getAnim(1);
        pane->initFrame();
        pane->restart();
        pane = self->mpNameLayout->getAnim(2);
        pane->initFrame();
        pane->restart();

        s32 inputType = self->mMode;
        switch (inputType) {
        case 2:
            goto address_type_two;
        case 1:
            goto address_type_one;
        default:
            goto address_type_common;
        }

    address_type_one: {
        nw4r::lyt::Pane* label = (self->mpNameLayout)->getNW4RLyt()->GetRootPane()->FindPaneByName(
            "T_question_00", true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, label, ipl::System::getMessage(0x31));
        label = (self->mpNameLayout)->getNW4RLyt()->GetRootPane()->FindPaneByName(
            "T_msg_00", true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, label, ipl::System::getMessage(0x47));
    }
        goto address_type_common;

    address_type_two: {
            nw4r::lyt::Pane* label = (self->mpNameLayout)->getNW4RLyt()->GetRootPane()->FindPaneByName(
                "T_question_00", true);
            set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
                self, label, ipl::System::getMessage(0x3f));
            label = (self->mpNameLayout)->getNW4RLyt()->GetRootPane()->FindPaneByName(
                "T_msg_00", true);
            set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
                self, label, ipl::System::getMessage(0x48));
    }

    address_type_common: {
        nw4r::lyt::Pane* label = (self->mpNameLayout)->getNW4RLyt()->GetRootPane()->FindPaneByName(
            "T_name_00", true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, label, self->mString.mDisplayText);
        self->mState = 0x10;
    }
        goto state_done;
    }

    state_seven: {
        ipl::layout::Animator* pane = self->mpNameLayout->getAnim(1);
        pane->initFrame();
        pane->restart();
        pane = self->mpNameLayout->getAnim(4);
        pane->initFrame();
        pane->restart();

        nw4r::lyt::Pane* label = (self->mpNameLayout)->getNW4RLyt()->GetRootPane()->FindPaneByName(
            "T_question_00", true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, label, ipl::System::getMessage(0x55));
        label = (self->mpNameLayout)->getNW4RLyt()->GetRootPane()->FindPaneByName(
            "T_mii_msg_00", true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, label, ipl::System::getMessage(0x8b));
        self->mState = 0x1c;
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

extern "C" u64 utf16_wiiid__Q33ipl5scene11AddressEditFPCw(const wchar_t* value) {
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

extern "C" void stt_wait_btn_fadeout__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    u32 index = self->mSelectedFriend;
    u32 friendType = self->mpFriendCache->getInfo(index).attr.status;
    u32 friendFinished;
    if (friendType == 2) {
        friendFinished = !self->mpCodeLayout->getAnim(0x15)->isPlaying();
    } else {
        friendFinished = !self->mpCodeLayout->getAnim(0x1b)->isPlaying();
    }

    bool finished = friendFinished && !self->mpCodeLayout->getAnim(0x16)->isPlaying();
    finished = finished && !self->mpCodeLayout->getAnim(0x17)->isPlaying();

    if (finished) {
        nw4r::lyt::Pane* label = self->mpCodeLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_card_msg_00", true);
        const wchar_t* message = ipl::System::getMessage(0x30);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, label, message);
        ipl::System::getDialog()->callS2Btn2(0x142, 0x141, true);
        self->mpCodeLayout->getAnim(0x1c)->initFrame();
        self->mpCodeLayout->getAnim(0x1c)->restart();
        self->mState = 4;
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

extern "C" void stt_ipt_input__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    ipl::keyboard::Manager::State* state = ipl::System::getKeyboard()->getState();
    ipl::scene::Manager* sceneManager = ipl::System::getSceneManager();
    void* button = sceneManager->getScene(5);
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
        bool nameWasEmpty = self->mString.mName[0] == 0;
        if (state->pressOK) {
            self->mString.setName(state->wcString);
            ipl::layout::Object* layout =
                self->mpNameLayout;
            nw4r::lyt::Pane* pane = layout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_name_00", true);
            set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
                self, pane, self->mString.mName);
        }
        if (self->mString.mName[0] == 0) {
            if (!nameWasEmpty) {
                ipl::layout::Animator* pane = self->mpNameLayout->getAnim(6);
                pane->initFrame();
                pane->restart();
                pane = self->mpNameLayout->getAnim(3);
                pane->initFrame();
                pane->restart();
            }
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xb);
        } else {
            if (nameWasEmpty) {
                ipl::layout::Animator* pane = self->mpNameLayout->getAnim(2);
                pane->initFrame();
                pane->restart();
                pane = self->mpNameLayout->getAnim(7);
                pane->initFrame();
                pane->restart();
            }
            if (self->mString.mbNameNotEmpty != 0) {
                reserveText__Q33ipl5scene6ButtonFiUl(button, 1, 0x2e);
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xf);
            } else {
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xb);
            }
        }
    }
    goto done;

state_hidden_after_disappear: {
        self->mState = 0xd;
        if (static_cast<u32>(ipl::System::getRegion()) == 6) {
            enableKSXFilter__Q29textinput7ManagerFb(ipl::System::getKeyboard()->baseMgr(), false);
        }
    }
    goto done;

state_hidden: {
        setDefaultTitleText__Q33ipl5scene11AddressEditFPCwb(
            self, NULL, ipl::System::getKeyboard()->baseMgr()->isVacancy());
    }

done:
    return;
}

extern "C" void stt_add_code_input__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    ipl::keyboard::Manager::State* state = ipl::System::getKeyboard()->getState();
    void* button = ipl::System::getScene(5);
    switch (state->iplType) {
    case ipl::keyboard::Manager::STATE_DISAPPEARING: {
        bool codeWasEmpty = self->mString.mValue[0] == 0;
        if (state->pressOK) {
            if (self->mMode == 1) {
                setWiiNo__Q43ipl5scene11AddressEdit6StringFPCw(
                    &self->mString, state->wcString);
            } else {
                self->mString.setEMail(state->wcString);
            }
            nw4r::lyt::Pane* label = (self->mpNameLayout)->getNW4RLyt()->GetRootPane()->FindPaneByName("T_name_00", true);
            set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
                self, label, self->mString.mDisplayText);
        }
        if (self->mString.mValue[0] == 0) {
            if (!codeWasEmpty) {
                ipl::layout::Animator* pane = self->mpNameLayout->getAnim(6);
                pane->initFrame();
                pane->restart();
                pane = self->mpNameLayout->getAnim(3);
                pane->initFrame();
                pane->restart();
            }
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xb);
        } else {
            if (codeWasEmpty) {
                ipl::layout::Animator* pane = self->mpNameLayout->getAnim(2);
                pane->initFrame();
                pane->restart();
                pane = self->mpNameLayout->getAnim(7);
                pane->initFrame();
                pane->restart();
            }
            if (self->mString.mbValidMail != 0 &&
                isDupCode__Q43ipl5scene11AddressEdit6StringCFv(&self->mString) == 0 &&
                isMyCode__Q43ipl5scene11AddressEdit6StringCFv(&self->mString) == 0) {
                reserveText__Q33ipl5scene6ButtonFiUl(button, 1, 0x2e);
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xf);
            } else {
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xb);
            }
        }
        break;
    }
    case ipl::keyboard::Manager::STATE_HIDDEN_AFTER_DISAPPEAR:
        if (state->pressOK) {
            if (self->mString.mValue[0] != 0) {
                if (self->mMode == 1) {
                    if (isMyCode__Q43ipl5scene11AddressEdit6StringCFv(
                &self->mString) != 0) {
                        callBtn1__Q23ipl12DialogWindowFUlUl(ipl::System::getDialog(), 0x56, 0x2e);
                        self->mState = 0x16;
                    } else if (isDupCode__Q43ipl5scene11AddressEdit6StringCFv(
                       &self->mString) != 0) {
                        callBtn1__Q23ipl12DialogWindowFUlUl(ipl::System::getDialog(), 0x52, 0x2e);
                        self->mState = 0x14;
                    } else if (self->mString.mbValidMail == 0) {
                        callBtn1__Q23ipl12DialogWindowFUlUl(ipl::System::getDialog(), 0x54, 0x2e);
                        self->mState = 0x13;
                    } else {
                        self->mState = 0x11;
                    }
                } else if (isDupCode__Q43ipl5scene11AddressEdit6StringCFv(
                   &self->mString) != 0) {
                    callBtn1__Q23ipl12DialogWindowFUlUl(ipl::System::getDialog(), 0x53, 0x2e);
                    self->mState = 0x15;
                } else if (self->mString.mbValidMail == 0) {
                    callBtn1__Q23ipl12DialogWindowFUlUl(ipl::System::getDialog(), 0x1be, 0x2e);
                    self->mState = 0x13;
                } else {
                    self->mState = 0x11;
                }
            } else {
                self->mState = 0x11;
            }
        } else {
            self->mState = 0x11;
        }
        break;
    case ipl::keyboard::Manager::STATE_HIDDEN:
    case ipl::keyboard::Manager::STATE_APPEARING:
        if (self->mMode != 1) {
            setDefaultTitleText__Q33ipl5scene11AddressEditFPCwb(
                self, NULL, ipl::System::getKeyboard()->baseMgr()->isVacancy());
        }
        break;
    default:
        break;
    }
}

extern "C" void stt_add_code_fadeout__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    ipl::layout::Object* layout = self->mpNameLayout;
    ipl::layout::Animator* pane = layout->getAnim(5);
    if (!pane->isPlaying()) {
        pane = self->mpNameLayout->getAnim(6);
        if (!pane->isPlaying()) {
            nw4r::lyt::Pane* label = (self->mpNameLayout)->getNW4RLyt()->GetRootPane()->FindPaneByName(
                reinterpret_cast<const char*>("T_question_00"), true);
            set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
                self, label, ipl::System::getMessage(0x32));
            label = (self->mpNameLayout)->getNW4RLyt()->GetRootPane()->FindPaneByName(
                reinterpret_cast<const char*>("T_msg_00"), true);
            set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
                self, label, ipl::System::getMessage(0x49));
            label = (self->mpNameLayout)->getNW4RLyt()->GetRootPane()->FindPaneByName(
                    reinterpret_cast<const char*>("T_name_00"), true);
            set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
                self, label, self->mString.mName);
            pane = self->mpNameLayout->getAnim(1);
            pane->initFrame();
            pane->restart();
            if (self->mString.mName[0] != 0) {
                pane = self->mpNameLayout->getAnim(2);
                pane->initFrame();
                pane->restart();
            } else {
                pane = self->mpNameLayout->getAnim(3);
                pane->initFrame();
                pane->restart();
            }
            ipl::System::getKeyboard()->init();
            self->mState = 0x18;
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





extern "C" void start_point_event__Q33ipl5scene11AddressEditFPCcPQ33ipl10controller9Interface(
    ipl::scene::AddressEdit* self, const char* paneName, ipl::controller::Interface* controller) {
    int buttonNo = get_button_no__Q33ipl5scene11AddressEditFPCc(self, paneName);
    s32 state = self->mState;

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
    u32 friendIndex = self->mSelectedFriend;
    u32 friendType = self->mpFriendCache->getInfo(friendIndex).attr.status;
    if (friendType != 2) {
        goto done;
    }
    s32* count = &self->mPointCount[buttonNo];
    if (*count == 0) {
        ipl::layout::Object* layout = self->mpCodeLayout;
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
    s32* count = &self->mPointCount[buttonNo];
    if (*count == 0) {
        ipl::layout::Object* layout = self->mpCodeLayout;
        nw4r::lyt::Pane* pane = layout->getNW4RLyt()->GetRootPane()->FindPaneByName(paneName, true);
        ipl::math::VEC3 position;
        __ct__Q33ipl4math4VEC3Ffff(&position, 0.0f, 0.0f, 0.0f);
        PSMTXMultVec(pane->GetGlobalMtx(), reinterpret_cast<Vec*>(&position), reinterpret_cast<Vec*>(&position));
        f32 xOffset = 15.0f;
        f32 height = 50.0f;
        f32 scale = 0.5f;
        position.x = position.x + xOffset;
        position.y = position.y + scale * height;
        (self->mpBalloon)
            ->setPos(position, false, 1);
        (self->mpBalloon)->fadein();
    }
}

state0Common: {
    s32* count = &self->mPointCount[buttonNo];
    if (*count == 0) {
        ipl::layout::Object* layout = self->mpCodeLayout;
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
        s32* count = &self->mPointCount[buttonNo];
        if (*count == 0) {
            ipl::layout::Object* layout = self->mpCodeLayout;
            nw4r::lyt::Pane* pane = layout->getNW4RLyt()->GetRootPane()->FindPaneByName(paneName, true);
            ipl::math::VEC3 position;
            __ct__Q33ipl4math4VEC3Ffff(&position, 0.0f, 0.0f, 0.0f);
            PSMTXMultVec(pane->GetGlobalMtx(), reinterpret_cast<Vec*>(&position), reinterpret_cast<Vec*>(&position));
            f32 xOffset = 15.0f;
            f32 height = 50.0f;
            f32 scale = 0.5f;
            position.x = position.x + xOffset;
            position.y = position.y + scale * height;
            (self->mpBalloon)
                ->setPos(position, false, 1);
            (self->mpBalloon)->fadein();
        }
        ++*count;
    }

done:
    return;
}

extern "C" void start_left_event__Q33ipl5scene11AddressEditFPCc(
    ipl::scene::AddressEdit* self, const char* paneName) {
    int buttonNo = get_button_no__Q33ipl5scene11AddressEditFPCc(self, paneName);
    s32 state = self->mState;
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
        u32 friendIndex = self->mSelectedFriend;
        u32 friendType = self->mpFriendCache->getInfo(friendIndex).attr.status;
        if (friendType != 2) {
            goto done;
        }
        s32* count = &self->mPointCount[buttonNo];
        if (*count == 1) {
            ipl::layout::Object* layout = self->mpCodeLayout;
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
        s32* count = &self->mPointCount[buttonNo];
        if (*count == 1) {
            (self->mpBalloon)->fadeoutForce();
        }
        --*count;
        goto done;
    }

state0Common: {
        s32* count = &self->mPointCount[buttonNo];
        if (*count == 1) {
            ipl::layout::Object* layout = self->mpCodeLayout;
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
        s32* count = &self->mPointCount[buttonNo];
        if (*count == 1) {
            (self->mpBalloon)->fadeoutForce();
        }
        --*count;
    }

done:
    return;
}

extern "C" void start_trig_event__Q33ipl5scene11AddressEditFPCc(
    ipl::scene::AddressEdit* self, const char* paneName) {
    int buttonNo = get_button_no__Q33ipl5scene11AddressEditFPCc(self, paneName);
    s32 state = self->mState;

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
            u32 friendIndex = self->mSelectedFriend;
            u32 friendType = self->mpFriendCache->getInfo(friendIndex).attr.status;
            if (friendType != 2) {
                goto state0FriendError;
            }
            reset_gui__Q33ipl5scene11AddressEditFv(self);
            ipl::layout::Object* layout = self->mpCodeLayout;
            ipl::layout::Animator* pane = layout->getAnim(buttonNo + 6);
            pane->initFrame();
            pane->restart();
            self->mSelectedButton = buttonNo;
            ipl::snd::getSystem()->startSE("WIPL_SE_BT_TARGETTING");
            self->mState = 1;
            break;
        }

        state0FriendError: {
            callBtn1__Q23ipl12DialogWindowFUlUl(ipl::System::getDialog(), 0x57, 0x2e);
            (self->mpBalloon)->fadeoutForce();
            reset_gui__Q33ipl5scene11AddressEditFv(self);
            self->mState = 0x2f;
            break;
        }

        state0Event: {
            ipl::layout::Object* layout = self->mpCodeLayout;
            ipl::layout::Animator* pane = layout->getAnim(buttonNo + 6);
            pane->initFrame();
            pane->restart();
            self->mSelectedButton = buttonNo;
            ipl::snd::getSystem()->startSE("WIPL_SE_BT_TARGETTING");
            self->mState = 1;
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
            (self->mpBalloon)->fadeoutForce();
            for (s32 i = 0; i < 5; ++i) {
                self->mPointCount[i] = 0;
            }
            ipl::layout::Object* layout = self->mpCodeLayout;
            ipl::layout::Animator* pane = layout->getAnim(10);
            pane->initFrame();
            pane->restart();
            self->mSelectedButton = buttonNo;
            ipl::snd::getSystem()->startSE("WIPL_SE_BT_TARGETTING");
            self->mState = 0x24;
            break;
        }
    }
}

extern "C" void start_ipt_trig_event__Q33ipl5scene11AddressEditFPCci(
    ipl::scene::AddressEdit* self, const char* paneName, int channel) {
    ipl::scene::SceneObj* button = ipl::System::getScene(5);
    ipl::controller::Interface* controller = ipl::System::getControllerManager()->getYoungController();
    if (controller == NULL) {
        return;
    }
    if (controller->getChannel() != channel) {
        return;
    }
    if (!strcmp(sInputPaneName, paneName)) {
        s32 state = self->mState;
        switch (state) {
    case 0xd: {
        ipl::keyboard::Manager::KeyboardSetting setting;
        __ct__Q43ipl8keyboard7Manager15KeyboardSettingFQ43ipl8keyboard7Manager12KeyboardTypePCwUlUl(
            &setting, static_cast<ipl::keyboard::Manager::KeyboardType>(0xb),
            self->mString.mName, 0xa, 1);

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
            enableKSXFilter__Q29textinput7ManagerFb(
                ipl::System::getKeyboard()->baseMgr(), true);
            setting.type = static_cast<ipl::keyboard::Manager::KeyboardType>(0xd);
            break;
        default:
            break;
        }

        ipl::System::getKeyboard()->start(channel, setting);
        setDefaultTitleText__Q33ipl5scene11AddressEditFPCwb(
            self, self->mString.mName, false);
        if (self->mString.mbNameNotEmpty != 0) {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
        } else {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xc);
        }
        reserveText__Q33ipl5scene6ButtonFiUl(button, 1, 0x2e);
        ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
        self->mState = 0xe;
        break;
    }
    case 0x11: {
        if (self->mMode == 1) {
            ipl::keyboard::Manager::KeyboardSetting setting;
            __ct__Q43ipl8keyboard7Manager15KeyboardSettingFQ43ipl8keyboard7Manager12KeyboardTypePCwUlUl(
                &setting, static_cast<ipl::keyboard::Manager::KeyboardType>(0xc),
                self->mString.mValue, 0x10, 2);
            ipl::System::getKeyboard()->start(channel, setting);
        } else {
            ipl::keyboard::Manager::KeyboardSetting setting;
            __ct__Q43ipl8keyboard7Manager15KeyboardSettingFQ43ipl8keyboard7Manager12KeyboardTypePCwUlUl(
                &setting, static_cast<ipl::keyboard::Manager::KeyboardType>(7),
                self->mString.mValue, 0x63, 5);
            ipl::System::getKeyboard()->start(channel, setting);
        }
        setDefaultTitleText__Q33ipl5scene11AddressEditFPCwb(
            self, self->mString.mValue, false);
        if (self->mString.mbValidMail != 0 &&
            isDupCode__Q43ipl5scene11AddressEdit6StringCFv(&self->mString) == 0 &&
            isMyCode__Q43ipl5scene11AddressEdit6StringCFv(&self->mString) == 0) {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
        } else {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xc);
        }
        ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
        self->mState = 0x12;
        break;
    }
    case 0x19: {
        ipl::keyboard::Manager::KeyboardSetting setting;
        __ct__Q43ipl8keyboard7Manager15KeyboardSettingFQ43ipl8keyboard7Manager12KeyboardTypePCwUlUl(
            &setting, static_cast<ipl::keyboard::Manager::KeyboardType>(0xb),
            self->mString.mName, 0xa, 1);

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
            enableKSXFilter__Q29textinput7ManagerFb(
                ipl::System::getKeyboard()->baseMgr(), true);
            setting.type = static_cast<ipl::keyboard::Manager::KeyboardType>(0xd);
            break;
        default:
            break;
        }

        ipl::System::getKeyboard()->start(channel, setting);
        setDefaultTitleText__Q33ipl5scene11AddressEditFPCwb(
            self, self->mString.mName, false);
        if (self->mString.mbNameNotEmpty != 0) {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
        } else {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xc);
        }
        reserveText__Q33ipl5scene6ButtonFiUl(button, 1, 0x2e);
        ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
        self->mState = 0x1a;
        break;
    }
    case 0x1d:
        if (self->mNigaoeState != 1) {
            self->mNigaoeState = 0;
            if (RFLGetAvailableOfficialDataNum() != 0) {
                createChildScene__Q33ipl5scene4BaseFiPQ33ipl5scene4BasePQ33ipl5scene4BasePv(
                    self, 0x1c, self, NULL, reinterpret_cast<void*>(2));
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xb);
                ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
                self->mState = 0x1e;
            } else {
                callBtn1__Q23ipl12DialogWindowFUlUl(ipl::System::getDialog(), 0x17c, 0x2e);
                ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
                self->mState = 0x1f;
            }
        }
        break;
    default:
        break;
        }
    }
}


extern "C" void start_ipt_point_event__Q33ipl5scene11AddressEditFPCci(
    ipl::scene::AddressEdit* self, const char* paneName, int channel) {
    ipl::controller::Interface* controller = ipl::System::getControllerManager()->getYoungController();
    if (controller != NULL) {
        if (controller->getChannel() == channel) {
            switch (self->mState) {
                case 0x1d: {
                    char paneNameCopy[12] = "mii_icon_00";
                    if (strcmp(paneNameCopy, paneName) == 0) {
                        ipl::layout::Object* layout = self->mpNameLayout;
                        nw4r::lyt::Pane* pane = layout->getNW4RLyt()->GetRootPane()->FindPaneByName(paneName, true);
                        ipl::math::VEC3 position;
                        __ct__Q33ipl4math4VEC3Ffff(&position, 0.0f, 0.0f, 0.0f);
                        PSMTXMultVec(pane->GetGlobalMtx(), reinterpret_cast<Vec*>(&position), reinterpret_cast<Vec*>(&position));
                        f32 y;
                        f32 offset;
                        offset = 50.0f;
                        y = position.y;
                        position.y = y + offset;
                        (self->mpBalloon)
                            ->setPos(position, false, 0);
                        (self->mpBalloon)->fadein();
                    }
                    break;
                }
            }
        }
    }
}

extern "C" void onEventDerived__Q33ipl5scene11AddressEditFUlUlPCQ33ipl10controller9Interface(
    ipl::scene::AddressEdit* self, u32 componentId, u32 event,
    const ipl::controller::Interface* controller) {

    gui::Manager* manager = self->getGuiManager();
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
    void* button = ipl::System::getScene(5);
    ipl::System::getScene(0x14);

        if (strcmp(paneName, smButtonName__Q33ipl5scene6Button[5]) == 0) {
        switch (self->mState) {
        case 0: {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x1b);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xc);
            reserveText__Q33ipl5scene6ButtonFiUl(button, 0, 0x23);
            reserveText__Q33ipl5scene6ButtonFiUl(button, 1, 0x29);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xf);
            ipl::layout::Animator* frame = self->mpCodeLayout->getAnim(0x1e);
            frame->initFrame();
            frame->restart();
            self->mSubState = 5;
            ipl::snd::getSystem()->startSE("WIPL_SE_CANCEL");
            (self->mpBalloon)->fadeoutForce();
            self->mState = 0x30;
            break;
        }
        case 0xd: {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x1b);
            if (self->mString.mbNameNotEmpty != 0) {
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
            } else {
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xc);
            }
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xb);
            ipl::layout::Animator* frame = self->mpNameLayout->getAnim(9);
            frame->initFrame();
            frame->restart();
            frame = self->mpBackgroundLayout->getAnim(1);
            frame->initFrame();
            frame->restart();
            get_friendinfo__Q33ipl5scene11AddressEditFv(self);
            ipl::snd::getSystem()->startSE("WIPL_SE_CANCEL");
            self->mState = 0xf;
            break;
        }
        case 0x11: {
            self->requestSceneChange(self->getPreviousScene(), NULL);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x1b);
            if (self->mString.mbValidMail != 0 &&
                isDupCode__Q43ipl5scene11AddressEdit6StringCFv(
                    &self->mString) == 0 &&
                isMyCode__Q43ipl5scene11AddressEdit6StringCFv(
                    &self->mString) == 0) {
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
            } else {
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xc);
            }
            ipl::layout::Animator* frame;
            if (self->mString.mValue[0] != 0) {
                frame = self->mpNameLayout->getAnim(6);
                frame->initFrame();
                frame->restart();
            } else {
                frame = self->mpNameLayout->getAnim(7);
                frame->initFrame();
                frame->restart();
            }
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xb);
            frame = self->mpNameLayout->getAnim(9);
            frame->initFrame();
            frame->restart();
            frame = self->mpNameLayout->getAnim(5);
            frame->initFrame();
            frame->restart();
            self->mSubState = 5;
            ipl::snd::getSystem()->startSE("WIPL_SE_CANCEL");
            self->mState = 0x30;
            break;
        }
        case 0x19: {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x1b);
            if (self->mString.mbNameNotEmpty != 0) {
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
                ipl::layout::Animator* frame = self->mpNameLayout->getAnim(6);
                frame->initFrame();
                frame->restart();
            } else {
                u16 nameLength = self->mString.mName[0];
                if (nameLength != 0) {
                    reserveAnm__Q33ipl5scene6ButtonFi(button, 0xc);
                    ipl::layout::Animator* frame = self->mpNameLayout->getAnim(6);
                    frame->initFrame();
                    frame->restart();
                } else {
                    reserveAnm__Q33ipl5scene6ButtonFi(button, 0xc);
                    ipl::layout::Animator* frame = self->mpNameLayout->getAnim(7);
                    frame->initFrame();
                    frame->restart();
                }
            }
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xf);
            ipl::layout::Animator* frame = self->mpNameLayout->getAnim(5);
            frame->initFrame();
            frame->restart();
            self->mSubState = 5;
            ipl::snd::getSystem()->startSE("WIPL_SE_CANCEL");
            self->mState = 0x1b;
            break;
        }
        case 0x1d: {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x1b);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xf);
            ipl::layout::Animator* frame = self->mpNameLayout->getAnim(5);
            frame->initFrame();
            frame->restart();
            frame = self->mpNameLayout->getAnim(8);
            frame->initFrame();
            frame->restart();
            self->mSubState = 5;
            ipl::snd::getSystem()->startSE("WIPL_SE_CANCEL");
            self->mState = 0x20;
            (self->mpBalloon)->fadeoutForce();
            reset_gui__Q33ipl5scene11AddressEditFv(self);
            break;
        }
        case 0x22: {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x1b);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xf);
            ipl::layout::Animator* frame = self->mpCodeLayout->getAnim(0x1e);
            frame->initFrame();
            frame->restart();
            self->mSubState = 5;
            ipl::snd::getSystem()->startSE("WIPL_SE_CANCEL");
            self->mState = 0x23;
            (self->mpBalloon)->fadeoutForce();
            reset_gui__Q33ipl5scene11AddressEditFv(self);
            break;
        }
        }
        } else if (strcmp(paneName, smButtonName__Q33ipl5scene6Button[7]) == 0) {
            switch (self->mState) {
        case 0xd: {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x1d);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xb);
            ipl::layout::Object* layout = self->mpCodeLayout;
            nw4r::lyt::Pane* pane = layout->getNW4RLyt()->GetRootPane()->FindPaneByName(
                "T_name_00", true);
            set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
                self, pane, self->mString.mName);
            self->mSubState = 7;
            ipl::layout::Animator* frame = self->mpNameLayout->getAnim(9);
            frame->initFrame();
            frame->restart();
            frame = self->mpBackgroundLayout->getAnim(1);
            frame->initFrame();
            frame->restart();
            self->update_friendinfo();
            ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
            self->mState = 0xf;
            break;
        }
        case 0x11: {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x1d);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
            if (self->mString.mbNameNotEmpty != 0) {
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xf);
            } else {
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xb);
            }
            ipl::layout::Animator* frame = self->mpNameLayout->getAnim(5);
            frame->initFrame();
            frame->restart();
            frame = self->mpNameLayout->getAnim(6);
            frame->initFrame();
            frame->restart();
            self->mSubState = 7;
            ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
            self->mState = 0x17;
            break;
        }
        case 0x19: {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x1d);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xf);
            ipl::layout::Animator* frame = self->mpNameLayout->getAnim(5);
            frame->initFrame();
            frame->restart();
            frame = self->mpNameLayout->getAnim(6);
            frame->initFrame();
            frame->restart();
            self->mSubState = 7;
            ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
            self->mState = 0x1b;
            reset_gui__Q33ipl5scene11AddressEditFv(self);
            break;
        }
        case 0x1d: {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x1d);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xf);
            ipl::layout::Animator* frame = self->mpNameLayout->getAnim(9);
            frame->initFrame();
            frame->restart();
            self->mSubState = 7;
            ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
            self->mState = 0x20;
            (self->mpBalloon)->fadeoutForce();
            reset_gui__Q33ipl5scene11AddressEditFv(self);
            break;
        }
        case 0x22: {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x1d);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
            ipl::layout::Animator* frame = self->mpCodeLayout->getAnim(0x1e);
            frame->initFrame();
            frame->restart();
            self->mSubState = 7;
            ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
            self->mState = 0x23;
            (self->mpBalloon)->fadeoutForce();
            break;
            }
        }
        }
}

extern "C" void start_ipt_left_event__Q33ipl5scene11AddressEditFPCci(
    ipl::scene::AddressEdit* self, const char* paneName, int channel) {
    ipl::controller::Interface* controller = ipl::System::getControllerManager()->getYoungController();
    if (controller != NULL) {
        if (controller->getChannel() == channel) {
            switch (self->mState) {
                case 0x1d: {
                    char paneNameCopy[12] = "mii_icon_00";
                    if (strcmp(paneNameCopy, paneName) == 0) {
                        (self->mpBalloon)->fadeoutForce();
                    }
                    break;
                }
            }
        }
    }
}

extern "C" void set_err_msg__Q33ipl5scene11AddressEditFPwUl8NWC24Err(
    ipl::scene::AddressEdit* self, wchar_t* outErrMsg, u32 outErrMsgLen, NWC24Err nwc24Err) {
    memset(outErrMsg, 0, outErrMsgLen * sizeof(wchar_t));
    wcsncat(outErrMsg, ipl::System::getMessage(MESG_ERROR_CODE), outErrMsgLen - wcslen(outErrMsg));

    wchar_t nwc24ErrStr[32];
    memset(nwc24ErrStr, 0, sizeof(nwc24ErrStr));
    void* friendListCache = self->mpFriendCache;
    NWC24Err errorCode = getErrCode__Q33ipl5scene15FriendListCacheCFv(friendListCache);
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







extern "C" int get_button_no__Q33ipl5scene11AddressEditFPCc(void*, const char* paneName) {
    int result = -1;
    for (int i = 0; i < 5; i++) {
        if (strcmp(smButtonName__Q33ipl5scene6Button[i], paneName) == 0) {
            result = i;
            break;
        }
    }
    return result;
}

extern "C" void add_friendinfo__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    NWC24FriendInfo info ALIGN32;
    memset(&info, 0, sizeof(info));
    switch (self->mMode) {
    case 1:
        info.attr.type = 1;
        {
            const wchar_t* name = self->mString.mName;
            wchar_t* storedName = reinterpret_cast<wchar_t*>(info.attr.name);
            wcsncpy(storedName, name, 0xa);
        }
        info.addr.wiiId = utf16_wiiid__Q33ipl5scene11AddressEditFPCw(self->mString.mValue);
        memcpy(&info.attr.fdId, &self->mCreateID, sizeof(self->mCreateID));
        break;
    case 2:
        info.attr.type = 2;
        {
            const wchar_t* name = self->mString.mName;
            wchar_t* storedName = reinterpret_cast<wchar_t*>(info.attr.name);
            wcsncpy(storedName, name, 0xa);
        }
        {
            const wchar_t* value = self->mString.mValue;
            u8* address = reinterpret_cast<u8*>(&info.addr);
            UTF16ToANSI__Q33ipl7utility13CharacterCodeFPUcPCwl(address, value, sizeof(info.addr));
        }
        memcpy(&info.attr.fdId, &self->mCreateID, sizeof(self->mCreateID));
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
            if (!self->mpFriendCache->isThere(index)) {
                break;
            }
            ++index;
        }
    }
    self->mpFriendCache->add(index, info);
    if (self->mMode == 2) {
        self->mpFriendCache->sendRegisterMail(index);
    }
}

extern "C" void get_friendinfo__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    const NWC24FriendInfo& friendInfo = self->mpFriendCache->getInfo(self->mSelectedFriend);
    memcpy(&sFriendInfo__Q23ipl5scene, &friendInfo, sizeof(sFriendInfo__Q23ipl5scene));
    self->mString.setName(reinterpret_cast<const wchar_t*>(sFriendInfo__Q23ipl5scene.attr.name));
    const wchar_t* name = self->mString.mName;
    nw4r::lyt::Pane* namePane =
        self->mpCodeLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_name_00", true);
    set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
        self, namePane, name);

    wchar_t wiiNo[0x100];
    wchar_t email[0x102];
    if (sFriendInfo__Q23ipl5scene.attr.type == 1) {
        memset(wiiNo, 0, sizeof(wiiNo));
        wiiid_utf16__Q33ipl5scene11AddressEditFUxPw(sFriendInfo__Q23ipl5scene.addr.wiiId, wiiNo);
        self->mString.setWiiNo(wiiNo);
    } else {
        memset(email, 0, sizeof(email));
        ANSIToUTF16__Q33ipl7utility13CharacterCodeFPwPCUcl(
            email, reinterpret_cast<const u8*>(&sFriendInfo__Q23ipl5scene.addr), 0x102);
        self->mString.setEMail(email);
    }
    const wchar_t* displayText = self->mString.mDisplayText;
    nw4r::lyt::Pane* friendCodePane =
        self->mpCodeLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("T_frnd_crd_00", true);
    set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
        self, friendCodePane, displayText);
    memcpy(&self->mCreateID, &sFriendInfo__Q23ipl5scene.attr.fdId, sizeof(self->mCreateID));
}

void ipl::scene::AddressEdit::update_friendinfo() {
    memset(sFriendInfo__Q23ipl5scene.attr.name, 0, 0x18);
    wcsncpy(reinterpret_cast<wchar_t*>(sFriendInfo__Q23ipl5scene.attr.name), mString.mName, 0xa);
    memcpy(&sFriendInfo__Q23ipl5scene.attr.fdId, &mCreateID, sizeof(mCreateID));
    mpFriendCache->update(
        mSelectedFriend,
        reinterpret_cast<const wchar_t*>(sFriendInfo__Q23ipl5scene.attr.name),
        sFriendInfo__Q23ipl5scene.attr.fdId);
    reset_friend__Q33ipl5scene7AddressFv(ipl::System::getScene(0x14));
}
