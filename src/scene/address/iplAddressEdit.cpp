#include "scene/address/iplAddressEdit.h"

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

namespace ipl {
    namespace scene {
        class AddressEditEvent : public ::gui::EventHandler {
        public:
            virtual void onEvent(u32 componentId, u32 event, void* data);

        private:
            AddressEdit* mpParent;
        };

        class AddressInputEvent : public ::gui::EventHandler {
        public:
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

struct AddressEditDataPool {
    u64 prefix[8];
    u32 padding;
    const char* panes[5];
    u64 suffix[121];
};
AddressEditDataPool s_addressEditDataPool = {
    {
        0x425f6372645f6274, 0x6e5f303000425f63,
        0x72645f62746e5f31, 0x3000425f6372645f,
        0x62746e5f31310042, 0x5f6d69695f69636f,
        0x6e5f303000425f63, 0x6172645f62657461
    },
    0,
    {
        reinterpret_cast<const char*>(&s_addressEditDataPool) + 0x00,
        reinterpret_cast<const char*>(&s_addressEditDataPool) + 0x0d,
        reinterpret_cast<const char*>(&s_addressEditDataPool) + 0x1a,
        reinterpret_cast<const char*>(&s_addressEditDataPool) + 0x27,
        reinterpret_cast<const char*>(&s_addressEditDataPool) + 0x35
    },
    {
        0x425f6372645f6564, 0x67695f3030006261, 0x6c6c6f6f6e2e6173, 0x680074685f416472,
        0x6573735f622e6272, 0x6c79740074685f41, 0x64726573735f625f, 0x636172645f737472,
        0x742e62726c616e00, 0x636172645f737472, 0x745f666e73680074, 0x685f416472657373,
        0x5f625f62746e5f69, 0x6e2e62726c616e00, 0x6372645f62746e5f, 0x3030006372645f62,
        0x746e5f3130006372, 0x645f62746e5f3131, 0x006d69695f69636f, 0x6e5f303000545f66,
        0x726e645f6372645f, 0x30300074685f4164, 0x726573735f625f62, 0x746e5f7073682e62,
        0x726c616e0074685f, 0x4164726573735f62, 0x5f62746e5f6f7574, 0x2e62726c616e0074,
        0x685f416472657373, 0x5f625f62746e5f73, 0x636c5f696e2e6272, 0x6c616e0074685f41,
        0x64726573735f625f, 0x62746e5f73636c5f, 0x6f75742e62726c61, 0x6e006372645f6274,
        0x6e5f677279007468, 0x5f4164726573735f, 0x625f636172645f6d, 0x73675f616c705f69,
        0x6e2e62726c616e00, 0x636172645f6d7367, 0x0074685f41647265, 0x73735f625f636172,
        0x645f6d73675f616c, 0x705f6f75742e6272, 0x6c616e0074685f41, 0x64726573735f625f,
        0x636172645f666e73, 0x682e62726c616e00, 0x545f6372645f6274, 0x6e5f303000545f63,
        0x72645f62746e5f31, 0x3000545f6372645f, 0x62746e5f31310054, 0x5f6372645f62746e,
        0x5f67727900545f63, 0x6172645f6d73675f, 0x303000545f6e616d, 0x655f30300074685f,
        0x4164726573735f63, 0x2e62726c79740074, 0x685f416472657373, 0x5f635f636172645f,
        0x737472742e62726c, 0x616e00475f636172, 0x645f737472745f66, 0x6e73680074685f41,
        0x64726573735f635f, 0x7175657374696f6e, 0x5f616c705f696e2e, 0x62726c616e00475f,
        0x7175657374696f6e, 0x5f30300074685f41, 0x64726573735f635f, 0x6e616d655f616c70,
        0x5f696e2e62726c61, 0x6e00475f6e616d65, 0x5f30300074685f41, 0x64726573735f635f,
        0x6d73675f616c705f, 0x696e2e62726c616e, 0x00475f6d73675f30, 0x300074685f416472,
        0x6573735f635f6d69, 0x695f616c705f696e, 0x2e62726c616e0074, 0x685f416472657373,
        0x5f635f7175657374, 0x696f6e5f616c705f, 0x6f75742e62726c61, 0x6e0074685f416472,
        0x6573735f635f6e61, 0x6d655f616c705f6f, 0x75742e62726c616e, 0x0074685f41647265,
        0x73735f635f6d7367, 0x5f616c705f6f7574, 0x2e62726c616e0074, 0x685f416472657373,
        0x5f635f6d69695f61, 0x6c705f6f75742e62, 0x726c616e0074685f, 0x4164726573735f63,
        0x5f636172645f666e, 0x73682e62726c616e, 0x006d795f4261636b, 0x5f612e62726c7974,
        0x006d795f4261636b, 0x5f615f4170656172, 0x2e62726c616e0050, 0x6963747572655f30,
        0x30006d795f426163, 0x6b5f615f4c6f7374, 0x2e62726c616e0054, 0x5f7175657374696f,
        0x6e5f303000545f6d, 0x73675f3030006d79, 0x5f49706c546f7042, 0x616c6c6f6f6e5f61,
        0x2e62726c79740000
    }
};

ipl::scene::AddressEdit::AddressEdit(EGG::Heap* heap, int friendCode)
    : FaderSceneBase(heap), ButtonEventHandlerBase() {
    u8* object = reinterpret_cast<u8*>(this);
    u32 zero = 0;

    *reinterpret_cast<u32*>(object + 0x84) = friendCode;
    *reinterpret_cast<s32*>(object + 0x88) = -1;
    *reinterpret_cast<s32*>(object + 0x8c) = -1;
    *reinterpret_cast<u32*>(object + 0xa4) = zero;
    *reinterpret_cast<void**>(object + 0x4d4) = this;

    reinterpret_cast<ipl::scene::AddressEdit::String*>(object + 0xb0)->clear();

    *reinterpret_cast<u8*>(object + 0x4d8) = 0;
    *reinterpret_cast<u32*>(object + 0x4dc) = zero;
    *reinterpret_cast<u32*>(object + 0x4e8) = zero;
    *reinterpret_cast<u32*>(object + 0x28) = 3;
    for (int i = 0; i < 5; ++i) {
        *reinterpret_cast<u32*>(object + 0x90 + i * 4) = zero;
    }
    for (int i = 0; i < 8; ++i) {
        object[0x4e0 + i] = 0;
    }
}

ipl::scene::AddressEdit::~AddressEdit() {
    ipl::nigaoe::Object* object = *reinterpret_cast<ipl::nigaoe::Object**>(
        reinterpret_cast<u8*>(this) + 0x4dc);
    if (object != 0) {
        __dt__Q33ipl6nigaoe6ObjectFv(object, 1);
    }
}


extern "C" char lbl_81647EE0[];
extern "C" char lbl_81647FC9[];
extern "C" char lbl_81647FD5[];
extern "C" char lbl_816480FD[];
extern "C" char lbl_8164810B[];
extern "C" __declspec(section ".sdata") const char* lbl_816965E0;
extern "C" __declspec(section ".sdata") char lbl_816965E4[];
extern "C" __declspec(section ".sdata") const char lbl_816965EA[];
extern "C" __declspec(section ".sdata") wchar_t lbl_816965E8[];
extern "C" __declspec(section ".sdata") const wchar_t lbl_816965F0[];
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
extern "C" char sFriendInfo__Q23ipl5scene[];
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
extern "C" void add_friendinfo__Q33ipl5scene11AddressEditFv(void*);
extern "C" void delete_friendinfo__Q33ipl5scene11AddressEditFv(void*);
extern "C" void add__Q33ipl5scene15FriendListCacheFUlRC15NWC24FriendInfo(
    void*, u32, const NWC24FriendInfo&);
extern "C" void sendRegisterMail__Q33ipl5scene15FriendListCacheFUl(void*, u32);
extern "C" void update__Q33ipl5scene15FriendListCacheFUlPCwUx(void*, u32, const wchar_t*, u64);
extern "C" void setName__Q43ipl5scene11AddressEdit6StringFPCw(void*, const wchar_t*);
extern "C" void setWiiNo__Q43ipl5scene11AddressEdit6StringFPCw(void*, const wchar_t*);
extern "C" void setEMail__Q43ipl5scene11AddressEdit6StringFPCw(void*, const wchar_t*);
extern "C" void set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
    void*, nw4r::lyt::Pane*, const wchar_t*);
extern "C" void setDefaultTitleText__Q33ipl5scene11AddressEditFPCwb(
    ipl::scene::AddressEdit*, const wchar_t*, bool);
extern "C" void wiiid_utf16__Q33ipl5scene11AddressEditFUxPw(u64, wchar_t*);
extern "C" void ANSIToUTF16__Q33ipl7utility13CharacterCodeFPwPCUcl(wchar_t*, const u8*, s32);
extern "C" const wchar_t* getName__Q33ipl6nigaoe6ObjectCFv(void*);
extern "C" void nigaoe_create_callback_add__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv(
    ipl::nigaoe::Object*, void*);
extern "C" void nigaoe_create_callback_edit__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv(
    ipl::nigaoe::Object*, void*);
extern "C" void update_friendinfo__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
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
extern "C" u64 utf16_wiiid__Q33ipl5scene11AddressEditFPCw(const wchar_t*);
extern "C" void stt_normal__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_wait_decide_anm__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_wait_btn_fadein__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_wait_btn_fadeout__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_wait_del_msg_fadein__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_wait_del_msg_fadeout_to_rlt__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_msg_del_rlt__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_select_mii__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_ipt_wait_fadein__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_ipt_normal__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_ipt_input__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void enableKSXFilter__Q29textinput7ManagerFb(textinput::Manager*, bool);
extern "C" void stt_add_code_input__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_add_code_fadeout__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" int isDupCode__Q43ipl5scene11AddressEdit6StringCFv(void*);
extern "C" int isMyCode__Q43ipl5scene11AddressEdit6StringCFv(void*);
extern "C" void stt_add_name_input__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_add_name_fadeout__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_add_mii_input__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void stt_add_mii_fadeout__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit*);
extern "C" void _savegpr_29();
extern "C" void _restgpr_29();
extern "C" void _savegpr_23();
extern "C" void _savegpr_29();
extern "C" void _savegpr_27();
extern "C" void _restgpr_23();
extern "C" void _restgpr_29();
extern "C" void _restgpr_27();
extern "C" void reset_gui__Q33ipl5scene11AddressEditFv(void*);
extern "C" bool getConnectEnableFlag__Q33ipl3ncd10NCDSettingFv();
extern "C" void reserveSceneChange__Q33ipl5scene4BaseFiPv(void*, int, void*);
extern "C" void start_point_event__Q33ipl5scene11AddressEditFPCcPQ33ipl10controller9Interface(
    ipl::scene::AddressEdit*, const char*, ipl::controller::Interface*);
extern "C" void start_trig_event__Q33ipl5scene11AddressEditFPCc(
    ipl::scene::AddressEdit*, const char*);
extern "C" void start_left_event__Q33ipl5scene11AddressEditFPCc(
    ipl::scene::AddressEdit*, const char*);
extern "C" void start_ipt_point_event__Q33ipl5scene11AddressEditFPCci(
    ipl::scene::AddressEdit*, const char*, int);
extern "C" void start_ipt_trig_event__Q33ipl5scene11AddressEditFPCci(
    ipl::scene::AddressEdit*, const char*, int);
extern "C" void start_ipt_left_event__Q33ipl5scene11AddressEditFPCci(
    ipl::scene::AddressEdit*, const char*, int);
extern "C" NWC24Err check__Q33ipl5scene15FriendListCacheFv(void*);
extern "C" void set_err_msg__Q33ipl5scene11AddressEditFPwUl8NWC24Err(
    ipl::scene::AddressEdit*, wchar_t*, u32, NWC24Err);













void ipl::scene::AddressEdit::stt_msg_code_add() {
    if (System::getDialog()->getLastResult() == DialogWindow::RESULT_BUTTON) {
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(this) + 0x64) = 0x22;
    }
}

void ipl::scene::AddressEdit::stt_msg_code_edit() {
    if (System::getDialog()->getLastResult() == DialogWindow::RESULT_BUTTON) {
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(this) + 0x64) = 0;
    }
}

void ipl::scene::AddressEdit::stt_msg_parental() {
    if (System::getDialog()->getLastResult() == DialogWindow::RESULT_BUTTON) {
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(this) + 0x64) = 0;
    }
}

void ipl::scene::AddressEdit::stt_msg_nwc24_error() {
    if (System::getDialog()->getLastResult() == DialogWindow::RESULT_BUTTON) {
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(this) + 0x64) = 0;
    }
}

extern "C" void stt_msg_no_established__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    switch (ipl::System::getDialog()->getLastResult()) {
    case 1:
        reset_gui__Q33ipl5scene11AddressEditFv(self);
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0x64) = 0;
        break;
    default:
        break;
    }
}

extern "C" void stt_msg_code_invalid__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    ipl::System::getScene(5);
    switch (ipl::System::getDialog()->getLastResult()) {
    case 1:
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x11;
        break;
    default:
        break;
    }
}

extern "C" void stt_msg_dup_wii_no__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    ipl::System::getScene(5);
    switch (ipl::System::getDialog()->getLastResult()) {
    case 1:
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x11;
        break;
    default:
        break;
    }
}

extern "C" void stt_msg_dup_email__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    ipl::System::getScene(5);
    switch (ipl::System::getDialog()->getLastResult()) {
    case 1:
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x11;
        break;
    default:
        break;
    }
}

extern "C" void stt_msg_my_wii_no__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    ipl::System::getScene(5);
    switch (ipl::System::getDialog()->getLastResult()) {
    case 1:
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x11;
        break;
    default:
        break;
    }
}

extern "C" void stt_msg_no_mii_add__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    ipl::System::getScene(5);
    switch (ipl::System::getDialog()->getLastResult()) {
    case 1:
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x1d;
        break;
    default:
        break;
    }
}

extern "C" void stt_msg_add_rlt__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    void* button = ipl::System::getScene(5);
    switch (ipl::System::getDialog()->getLastResult()) {
    case 1:
        reserveAnm__Q33ipl5scene6ButtonFi(button, 0xf);
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x30;
        break;
    default:
        break;
    }
}

extern "C" void stt_add_code_normal__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    void* button = ipl::System::getScene(5);
    if (isActive__Q33ipl5scene6ButtonCFv(button)) {
        update__Q33ipl5scene6ButtonFv(button);
    }
    if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) == 0x11) {
        update__Q33ipl3gui11PaneManagerFv(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x7c));
    }
}

extern "C" void stt_add_name_normal__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    void* button = ipl::System::getScene(5);
    if (isActive__Q33ipl5scene6ButtonCFv(button)) {
        update__Q33ipl5scene6ButtonFv(button);
    }
    if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) == 0x19) {
        update__Q33ipl3gui11PaneManagerFv(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x7c));
    }
}

extern "C" void stt_add_name_input__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
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
        bool nameWasEmpty = *reinterpret_cast<volatile u16*>(reinterpret_cast<volatile u8*>(self) + 0x2b4) == 0;
        if (state->pressOK) {
            setName__Q43ipl5scene11AddressEdit6StringFPCw(
                reinterpret_cast<u8*>(self) + 0xb0, state->wcString);
            nw4r::lyt::Pane* pane = (*reinterpret_cast<ipl::layout::Object**>(
                reinterpret_cast<u8*>(self) + 0x74))->getNW4RLyt()->GetRootPane()->FindPaneByName(lbl_8164810B, true);
            set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
                self, pane, reinterpret_cast<const wchar_t*>(reinterpret_cast<u8*>(self) + 0x2b4));
        }
        if (*reinterpret_cast<volatile u16*>(reinterpret_cast<volatile u8*>(self) + 0x2b4) == 0) {
            if (!nameWasEmpty) {
                void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 6);
                initFrame__Q33ipl7utility15FrameControllerFv(pane);
                *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
                pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 3);
                initFrame__Q33ipl7utility15FrameControllerFv(pane);
                *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
            }
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xb);
        } else {
            if (nameWasEmpty) {
                void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 2);
                initFrame__Q33ipl7utility15FrameControllerFv(pane);
                *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
                pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 7);
                initFrame__Q33ipl7utility15FrameControllerFv(pane);
                *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
            }
            if (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(self) + 0x4d1) != 0) {
                reserveText__Q33ipl5scene6ButtonFiUl(button, 1, 0x2e);
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xf);
            } else {
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xb);
            }
        }
        }
    goto done;

state_visible: {
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x19;
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



extern "C" void stt_add_mii_normal__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    void* button = ipl::System::getScene(5);
    if (isActive__Q33ipl5scene6ButtonCFv(button)) {
        update__Q33ipl5scene6ButtonFv(button);
    }
    if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) == 0x1d) {
        update__Q33ipl3gui11PaneManagerFv(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x7c));
    }
}

extern "C" void stt_add_mii_input__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    ipl::scene::Base* child = self->getChild();
    if (child != NULL) {
        child = self->getChild();
        s32 faceId = *reinterpret_cast<s32*>(reinterpret_cast<u8*>(child) + 0x23c);
        if (faceId >= 0 && ipl::System::getMiiManager()->isAvalable(faceId) &&
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x4e8) == 0) {
            RFLAdditionalInfo additionalInfo;
            RFLGetAdditionalInfo(&additionalInfo, RFLDataSource_Official, NULL, faceId);
            if (!RFLiIsSameID(
                    reinterpret_cast<RFLCreateID*>(reinterpret_cast<u8*>(self) + 0x4e0),
                    &additionalInfo.createID)) {
                memcpy(reinterpret_cast<void*>(reinterpret_cast<u32>(self) + 0x4e0),
                    &additionalInfo.createID, sizeof(RFLCreateID));
                ipl::System::getMiiManager()->create(ipl::System::getMem2App(), 0x4c, 0x4c, faceId,
                    nigaoe_create_callback_add__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv,
                    self);
                *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x4e8) = 1;
                reinterpret_cast<ipl::gui::PaneManager*>(
                    *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x7c))->init();
                (*reinterpret_cast<ipl::scene::TextBalloon**>(reinterpret_cast<u8*>(self) + 0xa8))->fadeoutForce();
            }
        }
    }

    if (self->getChild() == NULL &&
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(ipl::System::getSceneManager()) + 0x104) == 0) {
        void* handler = self;
        if (self != NULL) {
            handler = reinterpret_cast<u8*>(self) + 0x58;
        }
        setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler(
            ipl::System::getScene(5), handler, NULL);
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x1d;
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x4e8) = 0;
    }
}

extern "C" void stt_add_mii_fadeout__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    char* pool = lbl_81647EE0;

    if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 9)) + 0x14) != 1 &&
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 5)) + 0x14) != 1 &&
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 8)) + 0x14) != 1) {
        s32 state = *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x8c);
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
        void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 1);
        initFrame__Q33ipl7utility15FrameControllerFv(pane);
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
        pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 2);
        initFrame__Q33ipl7utility15FrameControllerFv(pane);
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;

        nw4r::lyt::Pane* label = (*reinterpret_cast<ipl::layout::Object**>(
            reinterpret_cast<u8*>(self) + 0x74))->getNW4RLyt()->GetRootPane()->FindPaneByName(pool + 0x3ef, true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, label, ipl::System::getMessage(0x32));
        label = (*reinterpret_cast<ipl::layout::Object**>(
            reinterpret_cast<u8*>(self) + 0x74))->getNW4RLyt()->GetRootPane()->FindPaneByName(pool + 0x22b, true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, label, reinterpret_cast<const wchar_t*>(reinterpret_cast<u8*>(self) + 0x2b4));
        label = (*reinterpret_cast<ipl::layout::Object**>(
            reinterpret_cast<u8*>(self) + 0x74))->getNW4RLyt()->GetRootPane()->FindPaneByName(pool + 0x3fd, true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, label, ipl::System::getMessage(0x49));
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x18;
    }
        goto state_done;

    state_seven: {
        void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x68)) + 0x28c, 0);
        initFrame__Q33ipl7utility15FrameControllerFv(pane);
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
        pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x68)) + 0x28c, 0x10);
        initAnmFrame__Q33ipl6layout8AnimatorFv(pane);
        pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x68)) + 0x28c, 0x11);
        initAnmFrame__Q33ipl6layout8AnimatorFv(pane);
        pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x68)) + 0x28c, 0x12);
        initAnmFrame__Q33ipl6layout8AnimatorFv(pane);
        pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x68)) + 0x28c, 0x1c);
        initFrame__Q33ipl7utility15FrameControllerFv(pane);
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;

        nw4r::lyt::Pane* label = (*reinterpret_cast<ipl::layout::Object**>(
            reinterpret_cast<u8*>(self) + 0x68))->getNW4RLyt()->GetRootPane()->FindPaneByName(pool + 0x21d, true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, label, ipl::System::getMessage(0x44));
        label = (*reinterpret_cast<ipl::layout::Object**>(
            reinterpret_cast<u8*>(self) + 0x68))->getNW4RLyt()->GetRootPane()->FindPaneByName(pool + 0x22b, true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, label, reinterpret_cast<const wchar_t*>(reinterpret_cast<u8*>(self) + 0x2b4));
        label = (*reinterpret_cast<ipl::layout::Object**>(
            reinterpret_cast<u8*>(self) + 0x68))->getNW4RLyt()->GetRootPane()->FindPaneByName(pool + 0xf5, true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, label, reinterpret_cast<const wchar_t*>(reinterpret_cast<u8*>(self) + 0x2cc));
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x21;
    }
    state_done:
        ;
    }
}

extern "C" void stt_select_mii__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    ipl::scene::Base* child = self->getChild();
    if (child != NULL) {
        child = self->getChild();
        s32 faceId = *reinterpret_cast<s32*>(reinterpret_cast<u8*>(child) + 0x23c);
        if (faceId >= 0 && ipl::System::getMiiManager()->isAvalable(faceId) &&
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x4e8) == 0) {
            RFLAdditionalInfo additionalInfo;
            RFLGetAdditionalInfo(&additionalInfo, RFLDataSource_Official, NULL, faceId);
            if (!RFLiIsSameID(
                    reinterpret_cast<RFLCreateID*>(reinterpret_cast<u8*>(self) + 0x4e0),
                    &additionalInfo.createID)) {
                memcpy(reinterpret_cast<void*>(reinterpret_cast<u32>(self) + 0x4e0),
                    &additionalInfo.createID, sizeof(RFLCreateID));
                ipl::System::getMiiManager()->create(ipl::System::getMem2App(), 0x4c, 0x4c, faceId,
                    nigaoe_create_callback_edit__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv,
                    self);
                *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x4e8) = 1;
                update_friendinfo__Q33ipl5scene11AddressEditFv(self);
            }
        }
    }

    if (self->getChild() == NULL &&
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(ipl::System::getSceneManager()) + 0x104) == 0) {
        void* handler = self;
        if (self != NULL) {
            handler = reinterpret_cast<u8*>(self) + 0x58;
        }
        setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler(
            ipl::System::getScene(5), handler, NULL);
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0;
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x4e8) = 0;
        reinterpret_cast<ipl::gui::PaneManager*>(
            *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x70))->init();
        for (u32 i = 0; i < 5; i++) {
            *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0x90 + i * 4) = 0;
        }
    }
}

extern "C" void stt_add_confirm_normal__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    void* button = ipl::System::getScene(5);
    if (isActive__Q33ipl5scene6ButtonCFv(button)) {
        update__Q33ipl5scene6ButtonFv(button);
    }
    if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) == 0x22) {
        update__Q33ipl3gui11PaneManagerFv(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x70));
    }
}

extern "C" void stt_wait_parental__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    void* scene = ipl::System::getScene(0x1b);
    if (scene != NULL) {
        switch (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(scene) + 0x70)) {
        case 1:
            *reinterpret_cast<u8*>(reinterpret_cast<u8*>(self) + 0x4d8) = 1;
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x29;
            break;
        case 2:
        case 3:
            *reinterpret_cast<u8*>(reinterpret_cast<u8*>(self) + 0x4d8) = 0;
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x29;
            break;
        default:
            break;
        }
    }
}

extern "C" void stt_wait_parental_wc__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    void* scene = ipl::System::getScene(0x1b);
    if (scene != NULL) {
        switch (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(scene) + 0x70)) {
        case 1:
            *reinterpret_cast<u8*>(reinterpret_cast<u8*>(self) + 0x4d8) = 1;
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x2c;
            break;
        case 2:
        case 3:
            *reinterpret_cast<u8*>(reinterpret_cast<u8*>(self) + 0x4d8) = 0;
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x2c;
            break;
        default:
            break;
        }
    }
}

extern "C" void stt_wait_parental_dst__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    if (self->getChild() == NULL) {
        if (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(self) + 0x4d8) != 0) {
            ipl::System::getFader()->fadeOut();
            reserveAllSceneDestruction__Q33ipl5scene4BaseFiPv(self, 0x12, reinterpret_cast<void*>(1));
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x30;
        } else {
            animation__Q33ipl5scene6ButtonFi(ipl::System::getScene(5), 0xb);
            void* handler = reinterpret_cast<void*>(self);
            if (self != NULL) {
                handler = reinterpret_cast<void*>(reinterpret_cast<u8*>(self) + 0x58);
            }
            setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler(
                ipl::System::getScene(5), handler, NULL);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0;
        }
    }
}

extern "C" void stt_wait_parental_dst_wc__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    if (self->getChild() == NULL) {
        if (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(self) + 0x4d8) != 0) {
            ipl::System::getFader()->fadeOut();
            reserveAllSceneDestruction__Q33ipl5scene4BaseFiPv(self, 0x12, reinterpret_cast<void*>(4));
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x30;
        } else {
            animation__Q33ipl5scene6ButtonFi(ipl::System::getScene(5), 0xb);
            void* handler = reinterpret_cast<void*>(self);
            if (self != NULL) {
                handler = reinterpret_cast<void*>(reinterpret_cast<u8*>(self) + 0x58);
            }
            setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler(
                ipl::System::getScene(5), handler, NULL);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0;
        }
    }
}

extern "C" void stt_msg_net__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    switch (ipl::System::getDialog()->getLastResult()) {
    case 2:
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0;
        break;
    case 1: {
        SCParentalControlsInfo info;
        if (SCGetParentalControl(&info) && (info.enable & SC_PARENTAL_FLAG_ENABLED)) {
            void* button = ipl::System::getScene(5);
            setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler(button, NULL, NULL);
            animation__Q33ipl5scene6ButtonFi(ipl::System::getScene(5), 0xc);
            createChildScene__Q33ipl5scene4BaseFiPQ33ipl5scene4BasePQ33ipl5scene4BasePv(
                self, 0x1b, self, NULL, reinterpret_cast<void*>(1));
            *reinterpret_cast<u8*>(reinterpret_cast<u8*>(self) + 0x4d8) = 0;
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x28;
        } else {
            ipl::System::getFader()->fadeOut();
            reserveAllSceneDestruction__Q33ipl5scene4BaseFiPv(self, 0x12, reinterpret_cast<void*>(1));
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x30;
        }
        break;
    }
    default:
        break;
    }
}

extern "C" void stt_msg_wc__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    switch (ipl::System::getDialog()->getLastResult()) {
    case 2:
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0;
        break;
    case 1: {
        SCParentalControlsInfo info;
        if (SCGetParentalControl(&info) && (info.enable & SC_PARENTAL_FLAG_ENABLED)) {
            void* button = ipl::System::getScene(5);
            setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler(button, NULL, NULL);
            animation__Q33ipl5scene6ButtonFi(ipl::System::getScene(5), 0xc);
            createChildScene__Q33ipl5scene4BaseFiPQ33ipl5scene4BasePQ33ipl5scene4BasePv(
                self, 0x1b, self, NULL, reinterpret_cast<void*>(1));
            *reinterpret_cast<u8*>(reinterpret_cast<u8*>(self) + 0x4d8) = 0;
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x2b;
        } else {
            ipl::System::getFader()->fadeOut();
            reserveAllSceneDestruction__Q33ipl5scene4BaseFiPv(self, 0x12, reinterpret_cast<void*>(4));
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x30;
        }
        break;
    }
    default:
        break;
    }
}

extern "C" void reset_gui__Q33ipl5scene11AddressEditFv(void* object) {
    ipl::scene::AddressEdit* self = reinterpret_cast<ipl::scene::AddressEdit*>(object);
    reinterpret_cast<ipl::gui::PaneManager*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x70))->init();
    reinterpret_cast<ipl::gui::PaneManager*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x7c))->init();
    for (s32 i = 0; i < 5; i++) {
        s32* count = reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x90 + i * 4);
        if (*count > 0) {
            void* list = *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x68);
            void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(list) + 0x28c, i + 0xb);
            initFrame__Q33ipl7utility15FrameControllerFv(pane);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
            *count = 0;
        }
    }
}

extern "C" void add_friendinfo__Q33ipl5scene11AddressEditFv(void* object) {
    ipl::scene::AddressEdit* self = reinterpret_cast<ipl::scene::AddressEdit*>(object);
    NWC24FriendInfo info ALIGN32;
    memset(&info, 0, sizeof(info));
    switch (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x84)) {
    case 1:
        info.attr.type = 1;
        {
            const wchar_t* name = reinterpret_cast<const wchar_t*>(reinterpret_cast<u8*>(self) + 0x2b4);
            wchar_t* destination = reinterpret_cast<wchar_t*>(info.attr.name);
            wcsncpy(destination, name, 0xa);
        }
        info.addr.wiiId = utf16_wiiid__Q33ipl5scene11AddressEditFPCw(
            reinterpret_cast<const wchar_t*>(reinterpret_cast<u8*>(self) + 0xb0));
        memcpy(&info.attr.fdId, reinterpret_cast<u8*>(self) + 0x4e0, 8);
        break;
    case 2:
        info.attr.type = 2;
        {
            const wchar_t* name = reinterpret_cast<const wchar_t*>(reinterpret_cast<u8*>(self) + 0x2b4);
            wchar_t* destination = reinterpret_cast<wchar_t*>(info.attr.name);
            wcsncpy(destination, name, 0xa);
        }
        {
            const wchar_t* address = reinterpret_cast<const wchar_t*>(reinterpret_cast<u8*>(self) + 0xb0);
            u8* destination = reinterpret_cast<u8*>(&info.addr);
            UTF16ToANSI__Q33ipl7utility13CharacterCodeFPUcPCwl(destination, address, 0x100);
        }
        memcpy(&info.attr.fdId, reinterpret_cast<u8*>(self) + 0x4e0, 8);
        break;
    default:
        break;
    }
    u32 index = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(ipl::System::getScene(0x14)) + 0xc0);
    if (index >= 100) {
        index = 0;
        for (u32 count = 100; count != 0; count--) {
            if (!*reinterpret_cast<u8*>(reinterpret_cast<u8*>(
                    *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x4ec)) + 0x7d00 + index)) {
                break;
            }
            index++;
        }
    }
    add__Q33ipl5scene15FriendListCacheFUlRC15NWC24FriendInfo(
        *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x4ec), index, info);
    if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x84) == 2) {
        sendRegisterMail__Q33ipl5scene15FriendListCacheFUl(
            *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x4ec), index);
    }
}

extern "C" void set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
    void*, nw4r::lyt::Pane* pane, const wchar_t* text) {
    nw4r::lyt::TextBox* textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(pane);
    textBox->SetString(text, 0);
}

struct AddressEditTextBoxAccess {
    void setTextBox(nw4r::lyt::Pane* pane, const wchar_t* text) {
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(this, pane, text);
    }
};

struct AddressEditStringAccess {
    void setName(const wchar_t* value) {
        setName__Q43ipl5scene11AddressEdit6StringFPCw(this, value);
    }

    void setWiiNo(const wchar_t* value) {
        setWiiNo__Q43ipl5scene11AddressEdit6StringFPCw(this, value);
    }

    void setEMail(const wchar_t* value) {
        setEMail__Q43ipl5scene11AddressEdit6StringFPCw(this, value);
    }
};

extern "C" void update_friendinfo__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    memset(sFriendInfo__Q23ipl5scene + 8, 0, 0x18);
    wcsncpy(reinterpret_cast<wchar_t*>(sFriendInfo__Q23ipl5scene + 8),
        reinterpret_cast<const wchar_t*>(reinterpret_cast<u8*>(self) + 0x2b4), 0xa);
    memcpy(sFriendInfo__Q23ipl5scene + 0x20, reinterpret_cast<u8*>(self) + 0x4e0, 8);
    update__Q33ipl5scene15FriendListCacheFUlPCwUx(
        *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x4ec),
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0xa4),
        reinterpret_cast<const wchar_t*>(sFriendInfo__Q23ipl5scene + 8),
        *reinterpret_cast<u64*>(sFriendInfo__Q23ipl5scene + 0x20));
    reset_friend__Q33ipl5scene7AddressFv(ipl::System::getScene(0x14));
}

extern "C" void setEMail__Q43ipl5scene11AddressEdit6StringFPCw(void* self, const wchar_t* value) {
    u8* bytes = reinterpret_cast<u8*>(self);
    bytes[0x422] = 0;
    memset(self, 0, 0x204);
    wcsncpy(reinterpret_cast<wchar_t*>(self), value, 0xff);
    u32 length = wcslen(value);
    memset(bytes + 0x21c, 0, 0x204);
    if (length > 0x10) {
        wcsncpy(reinterpret_cast<wchar_t*>(bytes + 0x21c), value, 0xe);
        wcscpy(reinterpret_cast<wchar_t*>(bytes + 0x238), lbl_816965F0);
    } else {
        wcscpy(reinterpret_cast<wchar_t*>(bytes + 0x21c), value);
    }
    u8 addr[0x100];
    memset(addr, 0, sizeof(addr));
    UTF16ToANSI__Q33ipl7utility13CharacterCodeFPUcPCwl(addr, value, 0x100);
    bytes[0x420] = NWC24CheckPublicMailAddr_(reinterpret_cast<const char*>(addr)) ? 0 : 1;
}

extern "C" void get_friendinfo__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    u32 index = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0xa4);
    void* friendInfo = *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x4ec);
    friendInfo = reinterpret_cast<u8*>(friendInfo) + index * 0x140;
    memcpy(sFriendInfo__Q23ipl5scene, friendInfo, 0x140);
    setName__Q43ipl5scene11AddressEdit6StringFPCw(
        reinterpret_cast<u8*>(self) + 0xb0,
        reinterpret_cast<const wchar_t*>(sFriendInfo__Q23ipl5scene + 8));
    const wchar_t* name = reinterpret_cast<const wchar_t*>(reinterpret_cast<u8*>(self) + 0x2b4);
    set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
        self,
        (*reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<u8*>(self) + 0x68))
            ->getNW4RLyt()
            ->GetRootPane()
            ->FindPaneByName(lbl_8164810B, true),
        name);
    wchar_t wiiNo[0x100];
    wchar_t email[0x102];
    if (*reinterpret_cast<u32*>(sFriendInfo__Q23ipl5scene) == 1) {
        memset(wiiNo, 0, sizeof(wiiNo));
        wiiid_utf16__Q33ipl5scene11AddressEditFUxPw(
            *reinterpret_cast<u64*>(sFriendInfo__Q23ipl5scene + 0x40), wiiNo);
        setWiiNo__Q43ipl5scene11AddressEdit6StringFPCw(
            reinterpret_cast<u8*>(self) + 0xb0, wiiNo);
    } else {
        memset(email, 0, sizeof(email));
        ANSIToUTF16__Q33ipl7utility13CharacterCodeFPwPCUcl(
            email, reinterpret_cast<const u8*>(sFriendInfo__Q23ipl5scene + 0x40), 0x102);
        setEMail__Q43ipl5scene11AddressEdit6StringFPCw(
            reinterpret_cast<u8*>(self) + 0xb0, email);
    }
    const wchar_t* friendCode = reinterpret_cast<const wchar_t*>(reinterpret_cast<u8*>(self) + 0x2cc);
    set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
        self,
        (*reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<u8*>(self) + 0x68))
            ->getNW4RLyt()
            ->GetRootPane()
            ->FindPaneByName(lbl_81647FD5, true),
        friendCode);
    memcpy(reinterpret_cast<u8*>(self) + 0x4e0, sFriendInfo__Q23ipl5scene + 0x20, 8);
}

extern "C" void nigaoe_create_callback_edit__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv(
    ipl::nigaoe::Object* object, void* callbackWork) {
    ipl::scene::AddressEdit* self = reinterpret_cast<ipl::scene::AddressEdit*>(callbackWork);
    ipl::nigaoe::Object** icon = reinterpret_cast<ipl::nigaoe::Object**>(reinterpret_cast<u8*>(self) + 0x4dc);
    if (*icon != NULL) {
        __dt__Q33ipl6nigaoe6ObjectFv(*icon, 1);
    }
    *icon = object;
    ipl::layout::Object* layout = *reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<u8*>(self) + 0x68);
    nw4r::lyt::Pane* pane = layout->getNW4RLyt()->GetRootPane()->FindPaneByName(lbl_81647FC9, true);
    pane->GetMaterial()->SetTexture(0, object->getIconTexture());
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0x4e8) = 2;
    (*reinterpret_cast<ipl::scene::TextBalloon**>(reinterpret_cast<u8*>(self) + 0xa8))->init(
        getName__Q33ipl6nigaoe6ObjectCFv(object), 0xa);
}

extern "C" void nigaoe_create_callback_add__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv(
    ipl::nigaoe::Object* object, void* callbackWork) {
    ipl::scene::AddressEdit* self = reinterpret_cast<ipl::scene::AddressEdit*>(callbackWork);
    ipl::nigaoe::Object** icon = reinterpret_cast<ipl::nigaoe::Object**>(reinterpret_cast<u8*>(self) + 0x4dc);
    if (*icon != NULL) {
        __dt__Q33ipl6nigaoe6ObjectFv(*icon, 1);
    }
    *icon = object;
    ipl::layout::Object* layout = *reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<u8*>(self) + 0x74);
    nw4r::lyt::Pane* pane = layout->getNW4RLyt()->GetRootPane()->FindPaneByName(lbl_81647FC9, true);
    pane->GetMaterial()->SetTexture(0, object->getIconTexture());
    layout = *reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<u8*>(self) + 0x68);
    pane = layout->getNW4RLyt()->GetRootPane()->FindPaneByName(lbl_81647FC9, true);
    pane->GetMaterial()->SetTexture(0, object->getIconTexture());
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0x4e8) = 2;
    (*reinterpret_cast<ipl::scene::TextBalloon**>(reinterpret_cast<u8*>(self) + 0xa8))->init(
        getName__Q33ipl6nigaoe6ObjectCFv(object), 0xa);
}

extern "C" void setDefaultTitleText__Q33ipl5scene11AddressEditFPCwb(
    ipl::scene::AddressEdit* self, const wchar_t* text, bool flag) {
    if (!flag && (text == NULL || *text != L'\0')) {
        goto set_empty_title;
    }
    switch (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64)) {
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
    ipl::System::getKeyboard()->baseMgr()->setTitleText(lbl_816965E8);
}



void ipl::scene::AddressEditEvent::onEvent(u32 componentId, u32 event, void* data) {
    s32 signedEvent = static_cast<s32>(event);
    ::gui::Manager* manager = mpManager;
    ::gui::PaneComponent* component =
        static_cast< ::gui::PaneComponent*>(manager->getComponent(componentId));
    const char* paneName = component->getPane()->GetName();

    if (signedEvent == 1) goto point_event;
    if (signedEvent >= 1) goto left_check;
    if (signedEvent >= 0) goto trig_event;
    goto done;

left_check:
    if (signedEvent >= 3) goto done;
    goto left_event;

point_event:
    if (data != NULL) {
        start_point_event__Q33ipl5scene11AddressEditFPCcPQ33ipl10controller9Interface(
            mpParent, paneName, static_cast<ipl::controller::Interface*>(data));
    }
    goto done;

left_event:
    start_left_event__Q33ipl5scene11AddressEditFPCc(
        mpParent, paneName);
    goto done;

trig_event:
    if (data != NULL &&
        static_cast<ipl::controller::Interface*>(data)->downTrg(0x100800)) {
        start_trig_event__Q33ipl5scene11AddressEditFPCc(
            mpParent, paneName);
    }

done:
    ;
}
void ipl::scene::AddressInputEvent::onEvent(u32 componentId, u32 event, void* data) {
    s32 signedEvent = static_cast<s32>(event);
    ::gui::Manager* manager = mpManager;
    ::gui::PaneComponent* component =
        static_cast< ::gui::PaneComponent*>(manager->getComponent(componentId));
    const char* paneName = component->getPane()->GetName();

    if (signedEvent == 1) goto point_event;
    if (signedEvent >= 1) goto left_check;
    if (signedEvent >= 0) goto trig_event;
    goto done;

left_check:
    if (signedEvent >= 3) goto done;
    goto left_event;

trig_event: {
    ipl::controller::Interface* controller =
        static_cast<ipl::controller::Interface*>(data);
    if (controller == NULL || !controller->downTrg(0x100800)) goto done;
    int channel = controller->getChannel();
    start_ipt_trig_event__Q33ipl5scene11AddressEditFPCci(
            mpParent, paneName, channel);
    goto done;
}

point_event: {
    if (data == NULL) goto done;
    int channel = static_cast<ipl::controller::Interface*>(data)->getChannel();
    start_ipt_point_event__Q33ipl5scene11AddressEditFPCci(
            mpParent, paneName, channel);
    goto done;
}

left_event: {
    if (data == NULL) goto done;
    int channel = static_cast<ipl::controller::Interface*>(data)->getChannel();
    start_ipt_left_event__Q33ipl5scene11AddressEditFPCci(
            mpParent, paneName, channel);
}

done:
    ;
}
extern "C" void stt_wait_delete__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    void* button = ipl::System::getScene(5);
    switch (ipl::System::getDialog()->getLastResult()) {
    case 2: {
        delete_friendinfo__Q33ipl5scene11AddressEditFv(self);
        void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x68)) + 0x28c, 0x1d);
        initFrame__Q33ipl7utility15FrameControllerFv(pane);
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 6;
        break;
    }
    case 1: {
        reserveAnm__Q33ipl5scene6ButtonFi(button, 0xb);
        void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x68)) + 0x28c, 0x1d);
        initFrame__Q33ipl7utility15FrameControllerFv(pane);
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 5;
        break;
    }
    default:
        break;
    }
}

extern "C" void stt_add_confirm_fadeout__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    void* list = *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x68);
    void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(reinterpret_cast<u8*>(list) + 0x28c, 0x1e);
    if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) != 1) {
        void* button = ipl::System::getScene(5);
        switch (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x8c)) {
        case 5: {
            void* paneList = *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74);
            void* frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(reinterpret_cast<u8*>(paneList) + 0x28c, 0);
            initFrame__Q33ipl7utility15FrameControllerFv(frame);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(frame) + 0x14) = 1;
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x1c;
            break;
        }
        case 7:
            add_friendinfo__Q33ipl5scene11AddressEditFv(self);
            reserveText__Q33ipl5scene6ButtonFiUl(button, 1, 0x29);
            reset_friend__Q33ipl5scene7AddressFv(ipl::System::getScene(0x14));
            callBtn1__Q23ipl12DialogWindowFUlUl(ipl::System::getDialog(), 0x4a, 0x2e);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x26;
            break;
        default:
            break;
        }
    }
}

extern "C" void stt_wait_del_msg_fadeout__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x68)) + 0x28c, 0x1d)) + 0x14) != 1) {
        s32 index = *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0xa4);
        u32 type = *reinterpret_cast<u32*>(*reinterpret_cast<u8**>(reinterpret_cast<u8*>(self) + 0x4ec) + index * 0x140 + 4);
        void* pane;
        if (type == 2) {
            pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x68)) + 0x28c, 0x10);
            initFrame__Q33ipl7utility15FrameControllerFv(pane);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
        } else {
            pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x68)) + 0x28c, 0x1a);
            initFrame__Q33ipl7utility15FrameControllerFv(pane);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
        }
        pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x68)) + 0x28c, 0x11);
        initFrame__Q33ipl7utility15FrameControllerFv(pane);
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
        pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x68)) + 0x28c, 0x12);
        initFrame__Q33ipl7utility15FrameControllerFv(pane);
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 2;
    }
}

extern "C" void stt_msg_no_mii__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    switch (ipl::System::getDialog()->getLastResult()) {
    case 1: {
        void* manager = *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x70);
        reinterpret_cast<ipl::gui::PaneManager*>(manager)->init();
        for (u32 i = 0; i < 5; i++) {
            *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0x90 + i * 4) = 0;
        }
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0;
        break;
    }
    default:
        break;
    }
}

extern "C" void stt_wait_decide_anm_add__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    s32 complete = 1;
    for (s32 i = 0; i < 5; i++) {
        u16 index = (u16)(*reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x88) + 6);
        void* list = *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x68);
        void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(reinterpret_cast<u8*>(list) + 0x28c, index);
        u32 state = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(pane) + 0x14);
        complete = (complete & (state - 1 > 0)) != 0;
    }
    if (complete != 0) {
        switch (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x88)) {
        case 4:
        reinterpret_cast<ipl::gui::PaneManager*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x70))->init();
        ipl::System::getDialog()->callBtn1(
            reinterpret_cast<ipl::scene::AddressEdit::String*>(reinterpret_cast<u8*>(self) + 0xb0)->getDispCodeLong(), 0x2e);
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x25;
        break;
        default:
            break;
        }
    }
}

extern "C" void stt_add_confirm_fadein__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    void* paneList = *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x68);
    void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(reinterpret_cast<u8*>(paneList) + 0x28c, 0);
    if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) != 1) {
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x22;
    }
}

extern "C" void stt_add_name_fadein__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 1)) + 0x14) != 1 &&
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 3)) + 0x14) != 1 &&
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 2)) + 0x14) != 1) {
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x19;
    }
}

extern "C" void stt_add_mii_fadein__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 1)) + 0x14) != 1 &&
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 4)) + 0x14) != 1 &&
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 0)) + 0x14) != 1) {
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x1d;
    }
}

extern "C" void stt_add_code_fadein__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 0)) + 0x14) != 1 &&
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 1)) + 0x14) != 1 &&
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 3)) + 0x14) != 1 &&
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 4)) + 0x14) != 1 &&
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 2)) + 0x14) != 1) {
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x11;
    }
}

extern "C" void stt_ipt_wait_fadeout__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 5)) + 0x14) != 1 &&
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 7)) + 0x14) != 1 &&
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 6)) + 0x14) != 1 &&
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 8)) + 0x14) != 1 &&
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 9)) + 0x14) != 1 &&
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x80)) + 0x28c, 1)) + 0x14) != 1) {
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0;
    }
}

extern "C" asm void __ct__Q43ipl8keyboard7Manager15KeyboardSettingFQ43ipl8keyboard7Manager12KeyboardTypePCwUlUl(
    void*, ipl::keyboard::Manager::KeyboardType, const wchar_t*, u32, u32) {
    nofralloc
    stw r4, 0(r3)
    stw r5, 4(r3)
    stw r6, 8(r3)
    stw r7, 0xc(r3)
    blr
}

extern "C" void stt_wait_decide_anm__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    char* pool = lbl_81647EE0;
    s32 complete = 1;
    void* button = ipl::System::getScene(5);
    for (s32 i = 0; i < 5; i++) {
        u16 index = (u16)(*reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x88) + 6);
        void* list = *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x68);
        void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(reinterpret_cast<u8*>(list) + 0x28c, index);
        u32 state = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(pane) + 0x14);
        complete = (complete & (state - 1 > 0)) != 0;
    }
    if (complete == 0) {
        return;
    }
    u8* bytes = reinterpret_cast<u8*>(self);
    s32 state = *reinterpret_cast<s32*>(bytes + 0x88);
    switch (state) {
    case 2: {
        u32 index = *reinterpret_cast<u32*>(bytes + 0xa4);
        u8* friendInfo = reinterpret_cast<u8*>(*reinterpret_cast<void**>(bytes + 0x4ec)) + index * 0x140;
        ipl::layout::Animator* animator;
        if (*reinterpret_cast<u32*>(friendInfo + 4) == 2) {
            animator = (*reinterpret_cast<ipl::layout::Object* volatile*>(bytes + 0x68))->getAnim(0x15);
            animator->initFrame();
            *reinterpret_cast<u32*>(reinterpret_cast<u8*>(animator) + 0x14) = 1;
        } else {
            animator = (*reinterpret_cast<ipl::layout::Object* volatile*>(bytes + 0x68))->getAnim(0x1b);
            animator->initFrame();
            *reinterpret_cast<u32*>(reinterpret_cast<u8*>(animator) + 0x14) = 1;
        }
        animator = (*reinterpret_cast<ipl::layout::Object* volatile*>(bytes + 0x68))->getAnim(0x16);
        animator->initFrame();
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(animator) + 0x14) = 1;
        animator = (*reinterpret_cast<ipl::layout::Object* volatile*>(bytes + 0x68))->getAnim(0x17);
        animator->initFrame();
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(animator) + 0x14) = 1;
        reserveAnm__Q33ipl5scene6ButtonFi(button, 0xc);
        *reinterpret_cast<u32*>(bytes + 0x64) = 3;
        reinterpret_cast<ipl::scene::TextBalloon*>(*reinterpret_cast<void**>(bytes + 0xa8))->fadeoutForce();
        reset_gui__Q33ipl5scene11AddressEditFv(self);
        break;
    }
    case 1: {
        reserveAnm__Q33ipl5scene6ButtonFi(button, 0xc);
        reserveText__Q33ipl5scene6ButtonFiUl(button, 1, 0x2e);
        reserveAnm__Q33ipl5scene6ButtonFi(button, 0xf);
        ipl::layout::Animator* animator =
            (*reinterpret_cast<ipl::layout::Object* volatile*>(bytes + 0x74))->getAnim(0);
        animator->initFrame();
        u32 one = 1;
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(animator) + 0x14) = one;
        animator = (*reinterpret_cast<ipl::layout::Object* volatile*>(bytes + 0x74))->getAnim(1);
        animator->initFrame();
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(animator) + 0x14) = one;
        animator = (*reinterpret_cast<ipl::layout::Object* volatile*>(bytes + 0x74))->getAnim(2);
        animator->initFrame();
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(animator) + 0x14) = one;
        animator = (*reinterpret_cast<ipl::layout::Object* volatile*>(bytes + 0x74))->getAnim(3);
        animator->initAnmFrame();
        animator = (*reinterpret_cast<ipl::layout::Object* volatile*>(bytes + 0x80))->getAnim(0);
        animator->initFrame();
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(animator) + 0x14) = one;
        nw4r::lyt::Pane* textPane = (*reinterpret_cast<ipl::layout::Object* volatile*>(bytes + 0x74))
            ->getNW4RLyt()->GetRootPane()->FindPaneByName(pool + 0x3ef, true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, textPane, ipl::System::getMessage(0x32));
        textPane = (*reinterpret_cast<ipl::layout::Object* volatile*>(bytes + 0x74))
            ->getNW4RLyt()->GetRootPane()->FindPaneByName(pool + 0x22b, true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, textPane, reinterpret_cast<const wchar_t*>(bytes + 0x2b4));
        textPane = (*reinterpret_cast<ipl::layout::Object* volatile*>(bytes + 0x74))
            ->getNW4RLyt()->GetRootPane()->FindPaneByName(pool + 0x3fd, true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, textPane, ipl::System::getMessage(0x49));
        reinterpret_cast<ipl::scene::TextBalloon*>(*reinterpret_cast<void**>(bytes + 0xa8))->fadeoutForce();
        reset_gui__Q33ipl5scene11AddressEditFv(self);
        *reinterpret_cast<u32*>(bytes + 0x64) = 0xc;
        break;
    }
    case 3: {
        if (*reinterpret_cast<s32*>(bytes + 0x4e8) != 1) {
            *reinterpret_cast<u32*>(bytes + 0x4e8) = 0;
            if (RFLGetAvailableOfficialDataNum() != 0) {
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xc);
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xb);
                createChildScene__Q33ipl5scene4BaseFiPQ33ipl5scene4BasePQ33ipl5scene4BasePv(
                    self, 0x1c, self, 0, reinterpret_cast<void*>(1));
                *reinterpret_cast<u32*>(bytes + 0x64) = 0xb;
            } else {
                ipl::System::getDialog()->callBtn1(0x17c, 0x2e);
                *reinterpret_cast<u32*>(bytes + 0x64) = 0xa;
            }
            reinterpret_cast<ipl::scene::TextBalloon*>(*reinterpret_cast<void**>(bytes + 0xa8))->fadeoutForce();
        }
        break;
    }
    case 0: {
        SCParentalControlsInfo parentalInfo;
        BOOL parentalResult = SCGetParentalControl(&parentalInfo);
        if (!getConnectEnableFlag__Q33ipl3ncd10NCDSettingFv()) {
            animation__Q33ipl5scene6ButtonFi(button, 0x1d);
            ipl::System::getDialog()->callBtn2(0x144, 0x146, 0x25, false);
            *reinterpret_cast<u32*>(bytes + 0x64) = 0x27;
        } else if ((SCGetWCFlags() & 1) == 0) {
            animation__Q33ipl5scene6ButtonFi(button, 0x1d);
            ipl::System::getDialog()->callBtn2(0x17e, 0x146, 0x25, false);
            *reinterpret_cast<u32*>(bytes + 0x64) = 0x2a;
        } else if (parentalResult != 0 && (parentalInfo.enable & 0x80) != 0 &&
                   (SCGetNetContentRestrictions() & 2) != 0) {
            animation__Q33ipl5scene6ButtonFi(button, 0x1d);
            ipl::System::getDialog()->callBtn1(0x14c, 0x2e);
            *reinterpret_cast<u32*>(bytes + 0x64) = 0x2d;
        } else {
            if (check__Q33ipl5scene15FriendListCacheFv(
                    *reinterpret_cast<void**>(bytes + 0x4ec)) == NWC24_ERR_NETWORK ||
                *reinterpret_cast<NWC24Err*>(reinterpret_cast<u8*>(
                    *reinterpret_cast<void**>(bytes + 0x4ec)) + 0x9d74) == NWC24_ERR_SERVER ||
                *reinterpret_cast<NWC24Err*>(reinterpret_cast<u8*>(
                    *reinterpret_cast<void**>(bytes + 0x4ec)) + 0x9d74) == NWC24_ERR_FULL) {
                wchar_t errorMessage[0x400];
                wchar_t* errorMessagePointer = errorMessage - 1;
                for (s32 i = 0; i < 0x200; i++) {
                    errorMessagePointer[1] = 0;
                    errorMessagePointer += 2;
                    *errorMessagePointer = 0;
                }
                set_err_msg__Q33ipl5scene11AddressEditFPwUl8NWC24Err(
                    self, errorMessage, 0x400,
                    *reinterpret_cast<NWC24Err*>(reinterpret_cast<u8*>(
                        *reinterpret_cast<void**>(bytes + 0x4ec)) + 0x9d74));
                ipl::System::getDialog()->callBtn1(errorMessage, 0x2e);
                animation__Q33ipl5scene6ButtonFi(button, 0x1d);
                *reinterpret_cast<u32*>(bytes + 0x64) = 0x2e;
            } else {
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xc);
                reserveText__Q33ipl5scene6ButtonFiUl(button, 1, 0x27);
                reserveText__Q33ipl5scene6ButtonFiUl(button, 0, 0x4f);
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xf);
                reserveSceneChange__Q33ipl5scene4BaseFiPv(self, 0xb, reinterpret_cast<void*>(1));
                ipl::layout::Animator* animator =
                    (*reinterpret_cast<ipl::layout::Object* volatile*>(bytes + 0x68))->getAnim(0x1e);
                animator->initFrame();
                *reinterpret_cast<u32*>(reinterpret_cast<u8*>(animator) + 0x14) = 1;
                *reinterpret_cast<u32*>(bytes + 0x64) = 0x30;
            }
        }
        reinterpret_cast<ipl::scene::TextBalloon*>(*reinterpret_cast<void**>(bytes + 0xa8))->fadeoutForce();
        reset_gui__Q33ipl5scene11AddressEditFv(self);
        break;
    }
    case 4: {
        ipl::DialogWindow* dialog = ipl::System::getDialog();
        const wchar_t* code = reinterpret_cast<ipl::scene::AddressEdit::String*>(bytes + 0xb0)->getDispCodeLong();
        dialog->callBtn1(code, 0x2e);
        reinterpret_cast<ipl::scene::TextBalloon*>(*reinterpret_cast<void**>(bytes + 0xa8))->fadeoutForce();
        reset_gui__Q33ipl5scene11AddressEditFv(self);
        *reinterpret_cast<u32*>(bytes + 0x64) = 9;
        break;
    }
    default:
        *reinterpret_cast<u32*>(bytes + 0x64) = 0;
        break;
    }
}

const wchar_t* ipl::scene::AddressEdit::String::getDispCodeLong() const {
    if (reinterpret_cast<const u8*>(this)[0x422] == 0) {
        return;
    }
    return reinterpret_cast<const wchar_t*>(reinterpret_cast<const u8*>(this) + 0x21c);
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
    memset(this, 0, 0x204);
    memset(reinterpret_cast<u8*>(this) + 0x204, 0, 0x18);
    memset(reinterpret_cast<u8*>(this) + 0x21c, 0, 0x204);
    reinterpret_cast<u8*>(this)[0x420] = 0;
    reinterpret_cast<u8*>(this)[0x421] = 0;
    reinterpret_cast<u8*>(this)[0x422] = 0;
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

extern "C" asm void prepare__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r4, smArg__Q23ipl6System@ha
    lis r5, lbl_81647EE0@ha
    stw r0, 0x14(r1)
    addi r4, r4, smArg__Q23ipl6System@l
    addi r5, r5, lbl_81647EE0@l
    li r6, 0
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r3, 0x6c(r4)
    lwz r4, 0x24(r31)
    bl readLayoutAsync__Q33ipl4nand7ManagerFPQ23EGG4HeapPCcb
    stw r3, 0xac(r31)
    lwz r31, 0xc(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" void create__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    const char* pool = reinterpret_cast<const char*>(&s_addressEditDataPool);
    const char* const* paneNames;
    ipl::layout::Object* bLayout;
    ipl::scene::SceneObj* board = ipl::System::getScene(4);
    ipl::nand::LayoutFile* boardFile = *reinterpret_cast<ipl::nand::LayoutFile**>(
        reinterpret_cast<u8*>(board) + 0xd20);

    bLayout = reinterpret_cast<ipl::layout::Object*>(__nw__FUl(0x580));
    if (bLayout != NULL) {
        bLayout = __ct__Q33ipl6layout6ObjectFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePCcPCc(
            bLayout, *reinterpret_cast<EGG::Heap**>(reinterpret_cast<u8*>(self) + 0x24),
            boardFile, lbl_816965E4, pool + 0x72);
    }
    bLayout->bindToGroup(pool + 0x84, pool + 0xa0, false, true);
    bLayout->bindToGroup(pool + 0xaf, pool + 0xc8, false, true);
    bLayout->bindToGroup(pool + 0xaf, pool + 0xd3, false, false);
    bLayout->bindToGroup(pool + 0xaf, pool + 0xde, false, false);
    bLayout->bindToGroup(pool + 0xaf, pool + 0xe9, false, false);
    bLayout->bind(pool + 0xaf, pool + 0xf5, false, false);
    bLayout->bindToGroup(pool + 0x103, pool + 0xc8, false, false);
    bLayout->bindToGroup(pool + 0x103, pool + 0xd3, false, false);
    bLayout->bindToGroup(pool + 0x103, pool + 0xde, false, false);
    bLayout->bindToGroup(pool + 0x103, pool + 0xe9, false, false);
    bLayout->bind(pool + 0x103, pool + 0xf5, false, false);
    bLayout->bindToGroup(pool + 0x11d, pool + 0xc8, false, false);
    bLayout->bindToGroup(pool + 0x11d, pool + 0xd3, false, true);
    bLayout->bindToGroup(pool + 0x11d, pool + 0xde, false, true);
    bLayout->bindToGroup(pool + 0x11d, pool + 0xe9, false, true);
    bLayout->bind(pool + 0x11d, pool + 0xf5, false, true);
    bLayout->bindToGroup(pool + 0x137, pool + 0xc8, false, false);
    bLayout->bindToGroup(pool + 0x137, pool + 0xd3, false, false);
    bLayout->bindToGroup(pool + 0x137, pool + 0xde, false, false);
    bLayout->bindToGroup(pool + 0x137, pool + 0xe9, false, false);
    bLayout->bind(pool + 0x137, pool + 0xf5, false, false);
    bLayout->bindToGroup(pool + 0x154, pool + 0xc8, false, true);
    bLayout->bindToGroup(pool + 0x154, pool + 0xd3, false, true);
    bLayout->bindToGroup(pool + 0x154, pool + 0xde, false, true);
    bLayout->bindToGroup(pool + 0x154, pool + 0xe9, false, true);
    bLayout->bind(pool + 0x154, pool + 0xf5, false, true);
    bLayout->bindToGroup(pool + 0x137, pool + 0x172, false, true);
    bLayout->bindToGroup(pool + 0x154, pool + 0x172, false, false);
    bLayout->bindToGroup(pool + 0x17e, pool + 0x1a0, false, true);
    bLayout->bindToGroup(pool + 0x1a9, pool + 0x1a0, false, false);
    bLayout->bindToGroup(pool + 0x1cc, pool + 0xa0, false, false);
    bLayout->finishBinding();

    u32* editEvent = reinterpret_cast<u32*>(__nw__FUl(0x10));
    if (editEvent != NULL) {
        editEvent[2] = 0;
        editEvent[0] = reinterpret_cast<u32>(__vt__Q33ipl5scene16AddressEditEvent);
        editEvent[3] = reinterpret_cast<u32>(self);
    }
    void* editManagerMemory = __nw__FUl(0x34);
    ipl::gui::PaneManager* editManager = reinterpret_cast<ipl::gui::PaneManager*>(editManagerMemory);
    if (editManagerMemory != NULL) {
        editManager = __ct__Q33ipl3gui11PaneManagerFPQ23gui12EventHandlerPCQ34nw4r3lyt8DrawInfoPQ23EGG4HeapPQ23EGG9Allocatorb(
            editManagerMemory, reinterpret_cast<gui::EventHandler*>(editEvent), bLayout->getDrawInfo(), NULL, NULL,
            false);
    }
    editManager->setupScene(bLayout);
    editManager->setAllComponentTriggerTarget(false);
    paneNames = reinterpret_cast<const char* const*>(pool + 0x44);
    for (s32 i = 0; i < 5; i++) {
        const char* paneName = paneNames[i];
        nw4r::lyt::Pane* pane = bLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(paneName, true);
        editManager->setTriggerTarget(pane, true);
    }
    *reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<u8*>(self) + 0x68) = bLayout;
    *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x6c) = editEvent;
    *reinterpret_cast<ipl::gui::PaneManager**>(reinterpret_cast<u8*>(self) + 0x70) = editManager;

    nw4r::lyt::Pane* textPane = bLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(pool + 0x1e8, true);
    set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, textPane, ipl::System::getMessage(0x2a));
    textPane = (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x68))
        ->getNW4RLyt()->GetRootPane()->FindPaneByName(pool + 0x1f5, true);
    set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, textPane, ipl::System::getMessage(0x2b));
    textPane = (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x68))
        ->getNW4RLyt()->GetRootPane()->FindPaneByName(pool + 0x202, true);
    set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, textPane, ipl::System::getMessage(0x2f));
    textPane = (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x68))
        ->getNW4RLyt()->GetRootPane()->FindPaneByName(pool + 0x20f, true);
    set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, textPane, ipl::System::getMessage(0x2a));
    textPane = (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x68))
        ->getNW4RLyt()->GetRootPane()->FindPaneByName(pool + 0x21d, true);
    set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, textPane, lbl_816965E8);
    textPane = (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x68))
        ->getNW4RLyt()->GetRootPane()->FindPaneByName(pool + 0x22b, true);
    set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, textPane, lbl_816965E8);
    textPane = (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x68))
        ->getNW4RLyt()->GetRootPane()->FindPaneByName(pool + 0xf5, true);
    set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, textPane, lbl_816965E8);

    ipl::layout::Object* cLayout = reinterpret_cast<ipl::layout::Object*>(__nw__FUl(0x580));
    if (cLayout != NULL) {
        cLayout = __ct__Q33ipl6layout6ObjectFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePCcPCc(
            cLayout, *reinterpret_cast<EGG::Heap**>(reinterpret_cast<u8*>(self) + 0x24),
            boardFile, lbl_816965E4, pool + 0x235);
    }
    cLayout->bindToGroup(pool + 0x247, pool + 0x263, false, true);
    cLayout->bindToGroup(pool + 0x274, pool + 0x296, false, true);
    cLayout->bindToGroup(pool + 0x2a4, pool + 0x2c2, false, true);
    cLayout->bindToGroup(pool + 0x2cc, pool + 0x2e9, false, true);
    cLayout->bindToGroup(pool + 0x2f2, lbl_816965EA, false, true);
    cLayout->bindToGroup(pool + 0x30f, pool + 0x296, false, false);
    cLayout->bindToGroup(pool + 0x332, pool + 0x2c2, false, false);
    cLayout->bindToGroup(pool + 0x351, pool + 0x2e9, false, false);
    cLayout->bindToGroup(pool + 0x36f, lbl_816965EA, false, false);
    cLayout->bindToGroup(pool + 0x38d, pool + 0x263, false, false);
    cLayout->finishBinding();

    u32* inputEvent = reinterpret_cast<u32*>(__nw__FUl(0x10));
    if (inputEvent != NULL) {
        inputEvent[2] = 0;
        inputEvent[0] = reinterpret_cast<u32>(__vt__Q33ipl5scene17AddressInputEvent);
        inputEvent[3] = reinterpret_cast<u32>(self);
    }
    void* inputManagerMemory = __nw__FUl(0x34);
    ipl::gui::PaneManager* inputManager = reinterpret_cast<ipl::gui::PaneManager*>(inputManagerMemory);
    if (inputManagerMemory != NULL) {
        inputManager = __ct__Q33ipl3gui11PaneManagerFPQ23gui12EventHandlerPCQ34nw4r3lyt8DrawInfoPQ23EGG4HeapPQ23EGG9Allocatorb(
            inputManagerMemory, reinterpret_cast<gui::EventHandler*>(inputEvent), cLayout->getDrawInfo(), NULL, NULL,
            false);
    }
    inputManager->setupScene(cLayout);
    inputManager->setAllComponentTriggerTarget(false);
    textPane = cLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(lbl_816965E0, true);
    inputManager->setTriggerTarget(textPane, true);
    *reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<u8*>(self) + 0x74) = cLayout;
    *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x78) = inputEvent;
    *reinterpret_cast<ipl::gui::PaneManager**>(reinterpret_cast<u8*>(self) + 0x7c) = inputManager;

    ipl::layout::Object* background = reinterpret_cast<ipl::layout::Object*>(__nw__FUl(0x580));
    if (background != NULL) {
        background = __ct__Q33ipl6layout6ObjectFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePCcPCc(
            background, *reinterpret_cast<EGG::Heap**>(reinterpret_cast<u8*>(self) + 0x24),
            boardFile, lbl_816965E4, pool + 0x3a9);
    }
    *reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<u8*>(self) + 0x80) = background;
    background->bind(pool + 0x3b9, pool + 0x3cf, false, true);
    (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x80))
        ->bind(pool + 0x3da, pool + 0x3cf, false, false);
    (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x80))->finishBinding();
    (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x80))
        ->getAnim(0)->initAnmFrame();

    reinterpret_cast<ipl::scene::AddressEdit::String*>(reinterpret_cast<u8*>(self) + 0xb0)->clear();
    memset(sFriendInfo__Q23ipl5scene, 0, 0x140);
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0x4dc) = 0;
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0x4e8) = 0;
    ipl::scene::SceneObj* addressScene = ipl::System::getScene(0x14);
    *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x4ec) =
        *reinterpret_cast<void**>(reinterpret_cast<u8*>(addressScene) + 0x274);

    s32 mode = *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x84);
    ipl::layout::Animator* animator;
    wchar_t* friendText;
    switch (mode) {
    case 0: {
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0xa4) =
            *reinterpret_cast<u32*>(reinterpret_cast<u8*>(addressScene) + 0xc0);
        get_friendinfo__Q33ipl5scene11AddressEditFv(self);
        u32 friendIndex = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0xa4);
        u8* friendInfo = reinterpret_cast<u8*>(
            *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x4ec)) + friendIndex * 0x140;
        if (*reinterpret_cast<u32*>(friendInfo + 4) == 2) {
            (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x68))->getAnim(0x15)->initAnmFrame();
            (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x68))->getAnim(0x1a)->initAnmFrame();
        } else {
            (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x68))->getAnim(0x10)->initAnmFrame();
            (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x68))->getAnim(0x1b)->initAnmFrame();
        }
        animator = (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x68))->getAnim(0);
        animator->initFrame();
        friendText = reinterpret_cast<wchar_t*>(reinterpret_cast<u8*>(self) + 0x2b4);
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(animator) + 0x14) = 1;
        textPane = (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x68))
            ->getNW4RLyt()->GetRootPane()->FindPaneByName(pool + 0x22b, true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, textPane, friendText);
        friendText = reinterpret_cast<wchar_t*>(reinterpret_cast<u8*>(friendText) + 0x18);
        textPane = (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x68))
            ->getNW4RLyt()->GetRootPane()->FindPaneByName(pool + 0xf5, true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, textPane, friendText);
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0;
            break;
    }
    case 1: {
        animator = (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x74))->getAnim(0);
        animator->initFrame();
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(animator) + 0x14) = 1;
        animator = (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x74))->getAnim(1);
        animator->initFrame();
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(animator) + 0x14) = 1;
        animator = (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x74))->getAnim(3);
        animator->initFrame();
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(animator) + 0x14) = 1;
        (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x68))->getAnim(0x1a)->initAnmFrame();
        (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x68))->getAnim(0x10)->initAnmFrame();
        textPane = (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x74))
            ->getNW4RLyt()->GetRootPane()->FindPaneByName(pool + 0x3ef, true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, textPane, ipl::System::getMessage(0x31));
        textPane = (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x74))
            ->getNW4RLyt()->GetRootPane()->FindPaneByName(pool + 0x3fd, true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, textPane, ipl::System::getMessage(0x47));
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x10;
            break;
    }
    case 2: {
        animator = (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x74))->getAnim(0);
        animator->initFrame();
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(animator) + 0x14) = 1;
        animator = (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x74))->getAnim(1);
        animator->initFrame();
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(animator) + 0x14) = 1;
        animator = (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x74))->getAnim(3);
        animator->initFrame();
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(animator) + 0x14) = 1;
        (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x68))->getAnim(0x1a)->initAnmFrame();
        (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x68))->getAnim(0x10)->initAnmFrame();
        textPane = (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x74))
            ->getNW4RLyt()->GetRootPane()->FindPaneByName(pool + 0x3ef, true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, textPane, ipl::System::getMessage(0x3f));
        textPane = (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<u8*>(self) + 0x74))
            ->getNW4RLyt()->GetRootPane()->FindPaneByName(pool + 0x3fd, true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, textPane, ipl::System::getMessage(0x48));
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x10;
            break;
    }
    default:
        break;
    }

create_mode_done:

    s16 miiIndex[2];
    if (RFLSearchOfficialData(reinterpret_cast<RFLCreateID*>(reinterpret_cast<u8*>(self) + 0x4e0),
            reinterpret_cast<u16*>(miiIndex))) {
        ipl::System::getMiiManager()->create(ipl::System::getMem2App(), 0x4c, 0x4c, miiIndex[0],
            nigaoe_create_callback_edit__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv, self);
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0x4e8) = 1;
    }

    ipl::System::getKeyboard()->init();

    ipl::scene::TextBalloon* balloon = reinterpret_cast<ipl::scene::TextBalloon*>(__nw__FUl(0x3c));
    if (balloon != NULL) {
        f32 balloonWidth = 30.0f;
        f32 balloonHeight = 120.0f;
        EGG::Heap* heap = *reinterpret_cast<EGG::Heap**>(reinterpret_cast<u8*>(self) + 0x24);
        ipl::math::VEC3 position;
        ipl::math::VEC3* positionPtr = __ct__Q33ipl4math4VEC3Ffff(&position, 0.0f, 0.0f, 0.0f);
        balloon = __ct__Q33ipl5scene11TextBalloonFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePCcPCcRCQ33ipl4math4VEC3ff(
            balloon, heap,
            *reinterpret_cast<ipl::nand::LayoutFile**>(reinterpret_cast<u8*>(self) + 0xac),
            lbl_816965E4, pool + 0x406, *positionPtr, balloonHeight, balloonWidth);
    }
    *reinterpret_cast<ipl::scene::TextBalloon**>(reinterpret_cast<u8*>(self) + 0xa8) = balloon;
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
    switch (*reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0x64)) {
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

    switch (*reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0x64)) {
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
            calc__Q33ipl5scene11TextBalloonFv(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0xa8));
            break;
    }

    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0x64) == 0x30
        ? ipl::scene::FADER_SCN_NEXT
        : ipl::scene::FADER_SCN_CONTINUE;
}

extern "C" void stt_add_name_fadeout__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    char* pool = lbl_81647EE0;

    if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 5)) + 0x14) != 1 &&
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 7)) + 0x14) != 1 &&
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 6)) + 0x14) != 1 &&
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 9)) + 0x14) != 1) {
        s32 state = *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x8c);
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
        void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 1);
        initFrame__Q33ipl7utility15FrameControllerFv(pane);
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
        pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 2);
        initFrame__Q33ipl7utility15FrameControllerFv(pane);
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;

        s32 inputType = *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x84);
        switch (inputType) {
        case 2:
            goto address_type_two;
        case 1:
            goto address_type_one;
        default:
            goto address_type_common;
        }

    address_type_one: {
        nw4r::lyt::Pane* label = (*reinterpret_cast<ipl::layout::Object**>(
            reinterpret_cast<u8*>(self) + 0x74))->getNW4RLyt()->GetRootPane()->FindPaneByName(
            pool + 0x3ef, true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, label, ipl::System::getMessage(0x31));
        label = (*reinterpret_cast<ipl::layout::Object**>(
            reinterpret_cast<u8*>(self) + 0x74))->getNW4RLyt()->GetRootPane()->FindPaneByName(
            pool + 0x3fd, true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, label, ipl::System::getMessage(0x47));
    }
        goto address_type_common;

    address_type_two: {
            nw4r::lyt::Pane* label = (*reinterpret_cast<ipl::layout::Object**>(
                reinterpret_cast<u8*>(self) + 0x74))->getNW4RLyt()->GetRootPane()->FindPaneByName(
                pool + 0x3ef, true);
            set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
                self, label, ipl::System::getMessage(0x3f));
            label = (*reinterpret_cast<ipl::layout::Object**>(
                reinterpret_cast<u8*>(self) + 0x74))->getNW4RLyt()->GetRootPane()->FindPaneByName(
                pool + 0x3fd, true);
            set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
                self, label, ipl::System::getMessage(0x48));
    }

    address_type_common: {
        nw4r::lyt::Pane* label = (*reinterpret_cast<ipl::layout::Object**>(
            reinterpret_cast<u8*>(self) + 0x74))->getNW4RLyt()->GetRootPane()->FindPaneByName(
            pool + 0x22b, true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, label, reinterpret_cast<const wchar_t*>(reinterpret_cast<u8*>(self) + 0x2cc));
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x10;
    }
        goto state_done;
    }

    state_seven: {
        void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 1);
        initFrame__Q33ipl7utility15FrameControllerFv(pane);
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
        pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 4);
        initFrame__Q33ipl7utility15FrameControllerFv(pane);
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;

        nw4r::lyt::Pane* label = (*reinterpret_cast<ipl::layout::Object**>(
            reinterpret_cast<u8*>(self) + 0x74))->getNW4RLyt()->GetRootPane()->FindPaneByName(
            pool + 0x3ef, true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, label, ipl::System::getMessage(0x55));
        label = (*reinterpret_cast<ipl::layout::Object**>(
            reinterpret_cast<u8*>(self) + 0x74))->getNW4RLyt()->GetRootPane()->FindPaneByName(
            "T_mii_msg_00", true);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
            self, label, ipl::System::getMessage(0x8b));
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x1c;
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

extern "C" void setName__Q43ipl5scene11AddressEdit6StringFPCw(void* self, const wchar_t* value) {
    wchar_t* name = reinterpret_cast<wchar_t*>(reinterpret_cast<u8*>(self) + 0x204);
    wcsncpy(name, value, 0xa);
    u32 length = wcslen(value);
    reinterpret_cast<u8*>(self)[0x421] = 0;
    for (u32 i = 0; i < length; i++) {
        if (value[i] == 0) {
            break;
        }
        if (value[i] != L' ' && value[i] != 0x3000) {
            reinterpret_cast<u8*>(self)[0x421] = 1;
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
    u8* bytes = reinterpret_cast<u8*>(self);
    u32 index = *reinterpret_cast<u32*>(bytes + 0xa4);
    u8* friendInfo = *reinterpret_cast<u8**>(bytes + 0x4ec) + index * 0x140;
    u32 friendType = *reinterpret_cast<u32*>(friendInfo + 4);
    u32 friendFinished;
    if (friendType == 2) {
        void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(bytes + 0x68)) + 0x28c, 0x15);
        friendFinished = *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) != 1;
    } else {
        void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(bytes + 0x68)) + 0x28c, 0x1b);
        friendFinished = *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) != 1;
    }

    void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
        reinterpret_cast<u8*>(*reinterpret_cast<void**>(bytes + 0x68)) + 0x28c, 0x16);
    u32 finished = (friendFinished & (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) != 1)) != 0;
    pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
        reinterpret_cast<u8*>(*reinterpret_cast<void**>(bytes + 0x68)) + 0x28c, 0x17);
    finished = (finished & (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) != 1)) != 0;

    if (finished != 0) {
        ipl::layout::Object* layoutObject = *reinterpret_cast<ipl::layout::Object**>(bytes + 0x68);
        nw4r::lyt::Pane* label = layoutObject->getNW4RLyt()->GetRootPane()->FindPaneByName(lbl_816480FD, true);
        const wchar_t* message = ipl::System::getMessage(0x30);
        set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(self, label, message);
        ipl::System::getDialog()->callS2Btn2(0x142, 0x141, true);
        pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(bytes + 0x68)) + 0x28c, 0x1c);
        initFrame__Q33ipl7utility15FrameControllerFv(pane);
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
        *reinterpret_cast<s32*>(bytes + 0x64) = 4;
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
        bool nameWasEmpty = *reinterpret_cast<volatile u16*>(reinterpret_cast<volatile u8*>(self) + 0x2b4) == 0;
        if (state->pressOK) {
            setName__Q43ipl5scene11AddressEdit6StringFPCw(
                reinterpret_cast<u8*>(self) + 0xb0, state->wcString);
            ipl::layout::Object* layout =
                *reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<u8*>(self) + 0x74);
            nw4r::lyt::Pane* pane = layout->getNW4RLyt()->GetRootPane()->FindPaneByName(lbl_8164810B, true);
            set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
                self, pane, reinterpret_cast<const wchar_t*>(reinterpret_cast<u8*>(self) + 0x2b4));
        }
        if (*reinterpret_cast<volatile u16*>(reinterpret_cast<volatile u8*>(self) + 0x2b4) == 0) {
            if (!nameWasEmpty) {
                void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 6);
                initFrame__Q33ipl7utility15FrameControllerFv(pane);
                *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
                pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 3);
                initFrame__Q33ipl7utility15FrameControllerFv(pane);
                *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
            }
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xb);
        } else {
            if (nameWasEmpty) {
                void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 2);
                initFrame__Q33ipl7utility15FrameControllerFv(pane);
                *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
                pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 7);
                initFrame__Q33ipl7utility15FrameControllerFv(pane);
                *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
            }
            if (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(self) + 0x4d1) != 0) {
                reserveText__Q33ipl5scene6ButtonFiUl(button, 1, 0x2e);
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xf);
            } else {
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xb);
            }
        }
    }
    goto done;

state_hidden_after_disappear: {
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0xd;
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
        bool codeWasEmpty = *reinterpret_cast<volatile u16*>(reinterpret_cast<volatile u8*>(self) + 0xb0) == 0;
        u8* code = reinterpret_cast<u8*>(self) + 0xb0;
        if (state->pressOK) {
            if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x84) == 1) {
                setWiiNo__Q43ipl5scene11AddressEdit6StringFPCw(
                    code, state->wcString);
            } else {
                setEMail__Q43ipl5scene11AddressEdit6StringFPCw(
                    code, state->wcString);
            }
            nw4r::lyt::Pane* label = (*reinterpret_cast<ipl::layout::Object**>(
                reinterpret_cast<u8*>(self) + 0x74))->getNW4RLyt()->GetRootPane()->FindPaneByName(lbl_8164810B, true);
            set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
                self, label, reinterpret_cast<const wchar_t*>(reinterpret_cast<u8*>(self) + 0x2cc));
        }
        if (*reinterpret_cast<volatile u16*>(reinterpret_cast<volatile u8*>(self) + 0xb0) == 0) {
            if (!codeWasEmpty) {
                void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 6);
                initFrame__Q33ipl7utility15FrameControllerFv(pane);
                *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
                pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 3);
                initFrame__Q33ipl7utility15FrameControllerFv(pane);
                *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
            }
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xb);
        } else {
            if (codeWasEmpty) {
                void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 2);
                initFrame__Q33ipl7utility15FrameControllerFv(pane);
                *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
                pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 7);
                initFrame__Q33ipl7utility15FrameControllerFv(pane);
                *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
            }
            if (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(self) + 0x4d0) != 0 &&
                isDupCode__Q43ipl5scene11AddressEdit6StringCFv(code) == 0 &&
                isMyCode__Q43ipl5scene11AddressEdit6StringCFv(code) == 0) {
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
            if (*reinterpret_cast<volatile u16*>(reinterpret_cast<volatile u8*>(self) + 0xb0) != 0) {
                if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x84) == 1) {
                    if (isMyCode__Q43ipl5scene11AddressEdit6StringCFv(
                            reinterpret_cast<u8*>(self) + 0xb0) != 0) {
                        callBtn1__Q23ipl12DialogWindowFUlUl(ipl::System::getDialog(), 0x56, 0x2e);
                        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x16;
                    } else if (isDupCode__Q43ipl5scene11AddressEdit6StringCFv(
                                   reinterpret_cast<u8*>(self) + 0xb0) != 0) {
                        callBtn1__Q23ipl12DialogWindowFUlUl(ipl::System::getDialog(), 0x52, 0x2e);
                        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x14;
                    } else if (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(self) + 0x4d0) == 0) {
                        callBtn1__Q23ipl12DialogWindowFUlUl(ipl::System::getDialog(), 0x54, 0x2e);
                        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x13;
                    } else {
                        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x11;
                    }
                } else if (isDupCode__Q43ipl5scene11AddressEdit6StringCFv(
                               reinterpret_cast<u8*>(self) + 0xb0) != 0) {
                    callBtn1__Q23ipl12DialogWindowFUlUl(ipl::System::getDialog(), 0x53, 0x2e);
                    *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x15;
                } else if (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(self) + 0x4d0) == 0) {
                    callBtn1__Q23ipl12DialogWindowFUlUl(ipl::System::getDialog(), 0x1be, 0x2e);
                    *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x13;
                } else {
                    *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x11;
                }
            } else {
                *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x11;
            }
        } else {
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x11;
        }
        break;
    case ipl::keyboard::Manager::STATE_HIDDEN:
    case ipl::keyboard::Manager::STATE_APPEARING:
        if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x84) != 1) {
            setDefaultTitleText__Q33ipl5scene11AddressEditFPCwb(
                self, NULL, ipl::System::getKeyboard()->baseMgr()->isVacancy());
        }
        break;
    default:
        break;
    }
}

extern "C" void stt_add_code_fadeout__Q33ipl5scene11AddressEditFv(ipl::scene::AddressEdit* self) {
    void* layout = *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74);
    const u8* poolBase = reinterpret_cast<const u8*>(&s_addressEditDataPool);
    void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
        reinterpret_cast<u8*>(layout) + 0x28c, 5);
    if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) != 1) {
        pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 6);
        if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) != 1) {
            nw4r::lyt::Pane* label = (*reinterpret_cast<ipl::layout::Object**>(
                reinterpret_cast<u8*>(self) + 0x74))->getNW4RLyt()->GetRootPane()->FindPaneByName(
                reinterpret_cast<const char*>(poolBase + 0x3ef), true);
            set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
                self, label, ipl::System::getMessage(0x32));
            label = (*reinterpret_cast<ipl::layout::Object**>(
                reinterpret_cast<u8*>(self) + 0x74))->getNW4RLyt()->GetRootPane()->FindPaneByName(
                reinterpret_cast<const char*>(poolBase + 0x3fd), true);
            set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
                self, label, ipl::System::getMessage(0x49));
            label = (*reinterpret_cast<ipl::layout::Object**>(
                reinterpret_cast<u8*>(self) + 0x74))->getNW4RLyt()->GetRootPane()->FindPaneByName(
                    reinterpret_cast<const char*>(poolBase + 0x22b), true);
            set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
                self, label, reinterpret_cast<const wchar_t*>(reinterpret_cast<u8*>(self) + 0x2b4));
            pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 1);
            initFrame__Q33ipl7utility15FrameControllerFv(pane);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
            if (*reinterpret_cast<volatile u16*>(reinterpret_cast<volatile u8*>(self) + 0x2b4) != 0) {
                pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 2);
                initFrame__Q33ipl7utility15FrameControllerFv(pane);
                *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
            } else {
                pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 3);
                initFrame__Q33ipl7utility15FrameControllerFv(pane);
                *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
            }
            ipl::System::getKeyboard()->init();
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x18;
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
    s32 state = *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64);

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
    u32 friendIndex = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0xa4);
    u8* friendList = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(self) + 0x4ec);
    u32 friendType = *reinterpret_cast<u32*>(friendList + friendIndex * 0x140 + 4);
    if (friendType != 2) {
        goto done;
    }
    s32* count = reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x90 + buttonNo * 4);
    if (*count == 0) {
        void* layout = *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x68);
        void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(layout) + 0x28c, buttonNo + 1);
        initFrame__Q33ipl7utility15FrameControllerFv(pane);
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
        ipl::snd::getSystem()->startSE(
            "WIPL_SE_BT_TARGETTING");
        controller->rumble(1);
    }
    ++*count;
    goto done;
}

state0Button3: {
    s32* count = reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x90 + buttonNo * 4);
    if (*count == 0) {
        ipl::layout::Object* layout = *reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<u8*>(self) + 0x68);
        nw4r::lyt::Pane* pane = layout->getNW4RLyt()->GetRootPane()->FindPaneByName(paneName, true);
        ipl::math::VEC3 position;
        __ct__Q33ipl4math4VEC3Ffff(&position, 0.0f, 0.0f, 0.0f);
        PSMTXMultVec(pane->GetGlobalMtx(), reinterpret_cast<Vec*>(&position), reinterpret_cast<Vec*>(&position));
        f32 xOffset = 15.0f;
        f32 height = 50.0f;
        f32 scale = 0.5f;
        position.x = position.x + xOffset;
        position.y = position.y + scale * height;
        (*reinterpret_cast<ipl::scene::TextBalloon**>(reinterpret_cast<u8*>(self) + 0xa8))
            ->setPos(position, false, 1);
        (*reinterpret_cast<ipl::scene::TextBalloon**>(reinterpret_cast<u8*>(self) + 0xa8))->fadein();
    }
}

state0Common: {
    s32* count = reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x90 + buttonNo * 4);
    if (*count == 0) {
        void* layout = *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x68);
        void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<u8*>(layout) + 0x28c, buttonNo + 1);
        initFrame__Q33ipl7utility15FrameControllerFv(pane);
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
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
        s32* count = reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x90 + buttonNo * 4);
        if (*count == 0) {
            ipl::layout::Object* layout = *reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<u8*>(self) + 0x68);
            nw4r::lyt::Pane* pane = layout->getNW4RLyt()->GetRootPane()->FindPaneByName(paneName, true);
            ipl::math::VEC3 position;
            __ct__Q33ipl4math4VEC3Ffff(&position, 0.0f, 0.0f, 0.0f);
            PSMTXMultVec(pane->GetGlobalMtx(), reinterpret_cast<Vec*>(&position), reinterpret_cast<Vec*>(&position));
            f32 xOffset = 15.0f;
            f32 height = 50.0f;
            f32 scale = 0.5f;
            position.x = position.x + xOffset;
            position.y = position.y + scale * height;
            (*reinterpret_cast<ipl::scene::TextBalloon**>(reinterpret_cast<u8*>(self) + 0xa8))
                ->setPos(position, false, 1);
            (*reinterpret_cast<ipl::scene::TextBalloon**>(reinterpret_cast<u8*>(self) + 0xa8))->fadein();
        }
        ++*count;
    }

done:
    return;
}

extern "C" void start_left_event__Q33ipl5scene11AddressEditFPCc(
    ipl::scene::AddressEdit* self, const char* paneName) {
    int buttonNo = get_button_no__Q33ipl5scene11AddressEditFPCc(self, paneName);
    s32 state = *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64);
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
        u32 friendIndex = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0xa4);
        u8* friendList = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(self) + 0x4ec);
        u32 friendType = *reinterpret_cast<u32*>(friendList + friendIndex * 0x140 + 4);
        if (friendType != 2) {
            goto done;
        }
        s32* count = reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x90 + buttonNo * 4);
        if (*count == 1) {
            void* layout = *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x68);
            void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(layout) + 0x28c, buttonNo + 0xb);
            initFrame__Q33ipl7utility15FrameControllerFv(pane);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
        }
        if (*count > 0) {
            --*count;
        }
        goto done;
    }

state0Button3: {
        s32* count = reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x90 + buttonNo * 4);
        if (*count == 1) {
            (*reinterpret_cast<ipl::scene::TextBalloon**>(reinterpret_cast<u8*>(self) + 0xa8))->fadeoutForce();
        }
        --*count;
        goto done;
    }

state0Common: {
        s32* count = reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x90 + buttonNo * 4);
        if (*count == 1) {
            void* layout = *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x68);
            void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(layout) + 0x28c, buttonNo + 0xb);
            initFrame__Q33ipl7utility15FrameControllerFv(pane);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
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
        s32* count = reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x90 + buttonNo * 4);
        if (*count == 1) {
            (*reinterpret_cast<ipl::scene::TextBalloon**>(reinterpret_cast<u8*>(self) + 0xa8))->fadeoutForce();
        }
        --*count;
    }

done:
    return;
}

extern "C" void start_trig_event__Q33ipl5scene11AddressEditFPCc(
    ipl::scene::AddressEdit* self, const char* paneName) {
    int buttonNo = get_button_no__Q33ipl5scene11AddressEditFPCc(self, paneName);
    s32 state = *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64);

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
            u32 friendIndex = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0xa4);
            u8* friendList = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(self) + 0x4ec);
            u32 friendType = *reinterpret_cast<u32*>(friendList + friendIndex * 0x140 + 4);
            if (friendType != 2) {
                goto state0FriendError;
            }
            reset_gui__Q33ipl5scene11AddressEditFv(self);
            void* layout = *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x68);
            void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(layout) + 0x28c, buttonNo + 6);
            initFrame__Q33ipl7utility15FrameControllerFv(pane);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x88) = buttonNo;
            ipl::snd::getSystem()->startSE("WIPL_SE_BT_TARGETTING");
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 1;
            break;
        }

        state0FriendError: {
            callBtn1__Q23ipl12DialogWindowFUlUl(ipl::System::getDialog(), 0x57, 0x2e);
            (*reinterpret_cast<ipl::scene::TextBalloon**>(reinterpret_cast<u8*>(self) + 0xa8))->fadeoutForce();
            reset_gui__Q33ipl5scene11AddressEditFv(self);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x2f;
            break;
        }

        state0Event: {
            void* layout = *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x68);
            void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(layout) + 0x28c, buttonNo + 6);
            initFrame__Q33ipl7utility15FrameControllerFv(pane);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x88) = buttonNo;
            ipl::snd::getSystem()->startSE("WIPL_SE_BT_TARGETTING");
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 1;
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
            (*reinterpret_cast<ipl::scene::TextBalloon**>(reinterpret_cast<u8*>(self) + 0xa8))->fadeoutForce();
            for (s32 i = 0; i < 5; ++i) {
                *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x90 + i * 4) = 0;
            }
            void* layout = *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x68);
            void* pane = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(layout) + 0x28c, 10);
            initFrame__Q33ipl7utility15FrameControllerFv(pane);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(pane) + 0x14) = 1;
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x88) = buttonNo;
            ipl::snd::getSystem()->startSE("WIPL_SE_BT_TARGETTING");
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x24;
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
    if (!strcmp(lbl_816965E0, paneName)) {
        s32 state = *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64);
        switch (state) {
    case 0xd: {
        ipl::keyboard::Manager::KeyboardSetting setting;
        __ct__Q43ipl8keyboard7Manager15KeyboardSettingFQ43ipl8keyboard7Manager12KeyboardTypePCwUlUl(
            &setting, static_cast<ipl::keyboard::Manager::KeyboardType>(0xb),
            reinterpret_cast<const wchar_t*>(reinterpret_cast<u8*>(self) + 0x2b4), 0xa, 1);

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
            self, reinterpret_cast<const wchar_t*>(reinterpret_cast<u8*>(self) + 0x2b4), false);
        if (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(self) + 0x4d1) != 0) {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
        } else {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xc);
        }
        reserveText__Q33ipl5scene6ButtonFiUl(button, 1, 0x2e);
        ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0xe;
        break;
    }
    case 0x11: {
        if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x84) == 1) {
            ipl::keyboard::Manager::KeyboardSetting setting;
            __ct__Q43ipl8keyboard7Manager15KeyboardSettingFQ43ipl8keyboard7Manager12KeyboardTypePCwUlUl(
                &setting, static_cast<ipl::keyboard::Manager::KeyboardType>(0xc),
                reinterpret_cast<const wchar_t*>(reinterpret_cast<u8*>(self) + 0xb0), 0x10, 2);
            ipl::System::getKeyboard()->start(channel, setting);
        } else {
            ipl::keyboard::Manager::KeyboardSetting setting;
            __ct__Q43ipl8keyboard7Manager15KeyboardSettingFQ43ipl8keyboard7Manager12KeyboardTypePCwUlUl(
                &setting, static_cast<ipl::keyboard::Manager::KeyboardType>(7),
                reinterpret_cast<const wchar_t*>(reinterpret_cast<u8*>(self) + 0xb0), 0x63, 5);
            ipl::System::getKeyboard()->start(channel, setting);
        }
        setDefaultTitleText__Q33ipl5scene11AddressEditFPCwb(
            self, reinterpret_cast<const wchar_t*>(reinterpret_cast<u8*>(self) + 0xb0), false);
        if (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(self) + 0x4d0) != 0 &&
            isDupCode__Q43ipl5scene11AddressEdit6StringCFv(reinterpret_cast<u8*>(self) + 0xb0) == 0 &&
            isMyCode__Q43ipl5scene11AddressEdit6StringCFv(reinterpret_cast<u8*>(self) + 0xb0) == 0) {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
        } else {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xc);
        }
        ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x12;
        break;
    }
    case 0x19: {
        ipl::keyboard::Manager::KeyboardSetting setting;
        __ct__Q43ipl8keyboard7Manager15KeyboardSettingFQ43ipl8keyboard7Manager12KeyboardTypePCwUlUl(
            &setting, static_cast<ipl::keyboard::Manager::KeyboardType>(0xb),
            reinterpret_cast<const wchar_t*>(reinterpret_cast<u8*>(self) + 0x2b4), 0xa, 1);

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
            self, reinterpret_cast<const wchar_t*>(reinterpret_cast<u8*>(self) + 0x2b4), false);
        if (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(self) + 0x4d1) != 0) {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
        } else {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xc);
        }
        reserveText__Q33ipl5scene6ButtonFiUl(button, 1, 0x2e);
        ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x1a;
        break;
    }
    case 0x1d:
        if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x4e8) != 1) {
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x4e8) = 0;
            if (RFLGetAvailableOfficialDataNum() != 0) {
                createChildScene__Q33ipl5scene4BaseFiPQ33ipl5scene4BasePQ33ipl5scene4BasePv(
                    self, 0x1c, self, NULL, reinterpret_cast<void*>(2));
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xb);
                ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
                *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x1e;
            } else {
                callBtn1__Q23ipl12DialogWindowFUlUl(ipl::System::getDialog(), 0x17c, 0x2e);
                ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
                *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x1f;
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
            switch (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64)) {
                case 0x1d: {
                    char paneNameCopy[12] = "mii_icon_00";
                    if (strcmp(paneNameCopy, paneName) == 0) {
                        ipl::layout::Object* layout = *reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<u8*>(self) + 0x74);
                        nw4r::lyt::Pane* pane = layout->getNW4RLyt()->GetRootPane()->FindPaneByName(paneName, true);
                        ipl::math::VEC3 position;
                        __ct__Q33ipl4math4VEC3Ffff(&position, 0.0f, 0.0f, 0.0f);
                        PSMTXMultVec(pane->GetGlobalMtx(), reinterpret_cast<Vec*>(&position), reinterpret_cast<Vec*>(&position));
                        f32 y;
                        f32 offset;
                        offset = 50.0f;
                        y = position.y;
                        position.y = y + offset;
                        (*reinterpret_cast<ipl::scene::TextBalloon**>(reinterpret_cast<u8*>(self) + 0xa8))
                            ->setPos(position, false, 0);
                        (*reinterpret_cast<ipl::scene::TextBalloon**>(reinterpret_cast<u8*>(self) + 0xa8))->fadein();
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
    const char* pool = lbl_81647EE0;
    gui::Manager* manager = *reinterpret_cast<gui::Manager**>(
        reinterpret_cast<u8*>(self) + 0x5c);
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
        switch (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64)) {
        case 0: {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x1b);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xc);
            reserveText__Q33ipl5scene6ButtonFiUl(button, 0, 0x23);
            reserveText__Q33ipl5scene6ButtonFiUl(button, 1, 0x29);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xf);
            void* frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(*reinterpret_cast<void**>(
                    reinterpret_cast<u8*>(self) + 0x68)) + 0x28c, 0x1e);
            initFrame__Q33ipl7utility15FrameControllerFv(frame);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(frame) + 0x14) = 1;
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x8c) = 5;
            ipl::snd::getSystem()->startSE("WIPL_SE_CANCEL");
            (*reinterpret_cast<ipl::scene::TextBalloon**>(
                reinterpret_cast<u8*>(self) + 0xa8))->fadeoutForce();
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x30;
            break;
        }
        case 0xd: {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x1b);
            if (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(self) + 0x4d1) != 0) {
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
            } else {
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xc);
            }
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xb);
            void* frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(*reinterpret_cast<void**>(
                    reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 9);
            initFrame__Q33ipl7utility15FrameControllerFv(frame);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(frame) + 0x14) = 1;
            frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(*reinterpret_cast<void**>(
                    reinterpret_cast<u8*>(self) + 0x80)) + 0x28c, 1);
            initFrame__Q33ipl7utility15FrameControllerFv(frame);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(frame) + 0x14) = 1;
            get_friendinfo__Q33ipl5scene11AddressEditFv(self);
            ipl::snd::getSystem()->startSE("WIPL_SE_CANCEL");
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0xf;
            break;
        }
        case 0x11: {
            reserveSceneChange__Q33ipl5scene4BaseFiPv(
                self, *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x34), NULL);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x1b);
            if (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(self) + 0x4d0) != 0 &&
                isDupCode__Q43ipl5scene11AddressEdit6StringCFv(
                    reinterpret_cast<u8*>(self) + 0xb0) == 0 &&
                isMyCode__Q43ipl5scene11AddressEdit6StringCFv(
                    reinterpret_cast<u8*>(self) + 0xb0) == 0) {
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
            } else {
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xc);
            }
            void* frame;
            if (*reinterpret_cast<u16*>(reinterpret_cast<u8*>(self) + 0xb0) != 0) {
                frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    reinterpret_cast<u8*>(*reinterpret_cast<void**>(
                        reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 6);
                initFrame__Q33ipl7utility15FrameControllerFv(frame);
                *reinterpret_cast<s32*>(reinterpret_cast<u8*>(frame) + 0x14) = 1;
            } else {
                frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    reinterpret_cast<u8*>(*reinterpret_cast<void**>(
                        reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 7);
                initFrame__Q33ipl7utility15FrameControllerFv(frame);
                *reinterpret_cast<s32*>(reinterpret_cast<u8*>(frame) + 0x14) = 1;
            }
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xb);
            frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(*reinterpret_cast<void**>(
                    reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 9);
            initFrame__Q33ipl7utility15FrameControllerFv(frame);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(frame) + 0x14) = 1;
            frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(*reinterpret_cast<void**>(
                    reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 5);
            initFrame__Q33ipl7utility15FrameControllerFv(frame);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(frame) + 0x14) = 1;
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x8c) = 5;
            ipl::snd::getSystem()->startSE("WIPL_SE_CANCEL");
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x30;
            break;
        }
        case 0x19: {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x1b);
            if (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(self) + 0x4d1) != 0) {
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
                void* frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    reinterpret_cast<u8*>(*reinterpret_cast<void**>(
                        reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 6);
                initFrame__Q33ipl7utility15FrameControllerFv(frame);
                *reinterpret_cast<s32*>(reinterpret_cast<u8*>(frame) + 0x14) = 1;
            } else {
                u16 nameLength = *reinterpret_cast<u16*>(reinterpret_cast<u8*>(self) + 0x2b4);
                if (nameLength != 0) {
                    reserveAnm__Q33ipl5scene6ButtonFi(button, 0xc);
                    void* frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                        reinterpret_cast<u8*>(*reinterpret_cast<void**>(
                            reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 6);
                    initFrame__Q33ipl7utility15FrameControllerFv(frame);
                    *reinterpret_cast<s32*>(reinterpret_cast<u8*>(frame) + 0x14) = 1;
                } else {
                    reserveAnm__Q33ipl5scene6ButtonFi(button, 0xc);
                    void* frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                        reinterpret_cast<u8*>(*reinterpret_cast<void**>(
                            reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 7);
                    initFrame__Q33ipl7utility15FrameControllerFv(frame);
                    *reinterpret_cast<s32*>(reinterpret_cast<u8*>(frame) + 0x14) = 1;
                }
            }
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xf);
            void* frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(*reinterpret_cast<void**>(
                    reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 5);
            initFrame__Q33ipl7utility15FrameControllerFv(frame);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(frame) + 0x14) = 1;
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x8c) = 5;
            ipl::snd::getSystem()->startSE("WIPL_SE_CANCEL");
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x1b;
            break;
        }
        case 0x1d: {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x1b);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xf);
            void* frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(*reinterpret_cast<void**>(
                    reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 5);
            initFrame__Q33ipl7utility15FrameControllerFv(frame);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(frame) + 0x14) = 1;
            frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(*reinterpret_cast<void**>(
                    reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 8);
            initFrame__Q33ipl7utility15FrameControllerFv(frame);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(frame) + 0x14) = 1;
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x8c) = 5;
            ipl::snd::getSystem()->startSE("WIPL_SE_CANCEL");
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x20;
            (*reinterpret_cast<ipl::scene::TextBalloon**>(
                reinterpret_cast<u8*>(self) + 0xa8))->fadeoutForce();
            reset_gui__Q33ipl5scene11AddressEditFv(self);
            break;
        }
        case 0x22: {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x1b);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xf);
            void* frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(*reinterpret_cast<void**>(
                    reinterpret_cast<u8*>(self) + 0x68)) + 0x28c, 0x1e);
            initFrame__Q33ipl7utility15FrameControllerFv(frame);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(frame) + 0x14) = 1;
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x8c) = 5;
            ipl::snd::getSystem()->startSE("WIPL_SE_CANCEL");
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x23;
            (*reinterpret_cast<ipl::scene::TextBalloon**>(
                reinterpret_cast<u8*>(self) + 0xa8))->fadeoutForce();
            reset_gui__Q33ipl5scene11AddressEditFv(self);
            break;
        }
        }
        } else if (strcmp(paneName, smButtonName__Q33ipl5scene6Button[7]) == 0) {
            switch (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64)) {
        case 0xd: {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x1d);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xb);
            ipl::layout::Object* layout = *reinterpret_cast<ipl::layout::Object**>(
                reinterpret_cast<u8*>(self) + 0x68);
            nw4r::lyt::Pane* pane = layout->getNW4RLyt()->GetRootPane()->FindPaneByName(
                pool + 0x22b, true);
            set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw(
                self, pane, reinterpret_cast<const wchar_t*>(
                    reinterpret_cast<u8*>(self) + 0x2b4));
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x8c) = 7;
            void* frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(*reinterpret_cast<void**>(
                    reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 9);
            initFrame__Q33ipl7utility15FrameControllerFv(frame);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(frame) + 0x14) = 1;
            frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(*reinterpret_cast<void**>(
                    reinterpret_cast<u8*>(self) + 0x80)) + 0x28c, 1);
            initFrame__Q33ipl7utility15FrameControllerFv(frame);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(frame) + 0x14) = 1;
            update_friendinfo__Q33ipl5scene11AddressEditFv(self);
            ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0xf;
            break;
        }
        case 0x11: {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x1d);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
            if (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(self) + 0x4d1) != 0) {
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xf);
            } else {
                reserveAnm__Q33ipl5scene6ButtonFi(button, 0xb);
            }
            void* frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(*reinterpret_cast<void**>(
                    reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 5);
            initFrame__Q33ipl7utility15FrameControllerFv(frame);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(frame) + 0x14) = 1;
            frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(*reinterpret_cast<void**>(
                    reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 6);
            initFrame__Q33ipl7utility15FrameControllerFv(frame);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(frame) + 0x14) = 1;
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x8c) = 7;
            ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x17;
            break;
        }
        case 0x19: {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x1d);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xf);
            void* frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(*reinterpret_cast<void**>(
                    reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 5);
            initFrame__Q33ipl7utility15FrameControllerFv(frame);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(frame) + 0x14) = 1;
            frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(*reinterpret_cast<void**>(
                    reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 6);
            initFrame__Q33ipl7utility15FrameControllerFv(frame);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(frame) + 0x14) = 1;
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x8c) = 7;
            ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x1b;
            reset_gui__Q33ipl5scene11AddressEditFv(self);
            break;
        }
        case 0x1d: {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x1d);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0xf);
            void* frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(*reinterpret_cast<void**>(
                    reinterpret_cast<u8*>(self) + 0x74)) + 0x28c, 9);
            initFrame__Q33ipl7utility15FrameControllerFv(frame);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(frame) + 0x14) = 1;
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x8c) = 7;
            ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x20;
            (*reinterpret_cast<ipl::scene::TextBalloon**>(
                reinterpret_cast<u8*>(self) + 0xa8))->fadeoutForce();
            reset_gui__Q33ipl5scene11AddressEditFv(self);
            break;
        }
        case 0x22: {
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x1d);
            reserveAnm__Q33ipl5scene6ButtonFi(button, 0x10);
            void* frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<u8*>(*reinterpret_cast<void**>(
                    reinterpret_cast<u8*>(self) + 0x68)) + 0x28c, 0x1e);
            initFrame__Q33ipl7utility15FrameControllerFv(frame);
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(frame) + 0x14) = 1;
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x8c) = 7;
            ipl::snd::getSystem()->startSE("WIPL_SE_DECIDE");
            *reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64) = 0x23;
            (*reinterpret_cast<ipl::scene::TextBalloon**>(
                reinterpret_cast<u8*>(self) + 0xa8))->fadeoutForce();
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
            switch (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(self) + 0x64)) {
                case 0x1d: {
                    char paneNameCopy[12] = "mii_icon_00";
                    if (strcmp(paneNameCopy, paneName) == 0) {
                        (*reinterpret_cast<ipl::scene::TextBalloon**>(reinterpret_cast<u8*>(self) + 0xa8))->fadeoutForce();
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
    void* friendListCache = *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x4ec);
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
