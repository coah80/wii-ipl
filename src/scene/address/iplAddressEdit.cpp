#include "scene/address/iplAddressEdit.h"

#include "system/iplSystem.h"
#include "iplSound.h"
#include "scene/iplSceneCreator.h"
#include "utility/iplCharacterCode.h"

#include "scene/address/iplAddress.h"
#include "scene/board/iplBoard.h"
#include "scene/setting/iplNCDSetting.h"
#include "scene/textBalloon/iplBalloon.h"
#include "system/iplKeyboard.h"

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

const char* scGuiPaneNames[5] = {
    "B_crd_btn_00", "B_crd_btn_10", "B_crd_btn_11", "B_mii_icon_00", "B_card_beta",
};
extern "C" char lbl_81647F38[] = "B_crd_edgi_00";
char sPool_balloon[] = "balloon.ash";
extern "C" const char lbl_8160F668[0xB] =
    { '(', ')', '<', '>', '[', ']', ':', ';', '\\', ',', '"' };

extern "C" char lbl_81647F38[];
extern "C" __declspec(section ".sdata") char* lbl_816965E0 = lbl_81647F38;

namespace ipl {
    namespace scene {
        NWC24FriendInfo sFriendInfo;
    }
}


extern "C" char lbl_81647EE0;
extern "C" int get_button_no__Q33ipl5scene11AddressEditFPCc();
extern "C" NWC24Err NWC24CheckPublicMailAddr_(const char* addr);
extern "C" u16 RFLGetAvailableOfficialDataNum();
extern "C" char sFriendInfo__Q23ipl5scene;
extern "C" void clear__Q43ipl5scene11AddressEdit6StringFv();
extern "C" void getDispCodeLong__Q43ipl5scene11AddressEdit6StringCFv();
extern "C" void reserveAllSceneDestruction__Q33ipl5scene4BaseFiPv();
extern "C" void reserveSceneChange__Q33ipl5scene4BaseFiPv();
extern "C" void resetContextPredict___Q39textinput9inputform4BaseFv();
extern "C" void stt_msg_code_add__Q33ipl5scene11AddressEditFv();
extern "C" void stt_msg_code_edit__Q33ipl5scene11AddressEditFv();
extern "C" void stt_msg_nwc24_error__Q33ipl5scene11AddressEditFv();
extern "C" void stt_msg_parental__Q33ipl5scene11AddressEditFv();extern "C" void setName__Q43ipl5scene11AddressEdit6StringFPCw(void*, const wchar_t*);
extern "C" void stt_ipt_input__Q33ipl5scene11AddressEditFv();
extern "C" void stt_ipt_wait_fadeout__Q33ipl5scene11AddressEditFv();
extern "C" void stt_add_code_fadein__Q33ipl5scene11AddressEditFv();
extern "C" void stt_add_code_normal__Q33ipl5scene11AddressEditFv();
extern "C" void stt_add_code_input__Q33ipl5scene11AddressEditFv();
extern "C" void stt_msg_code_invalid__Q33ipl5scene11AddressEditFv();
extern "C" void stt_msg_dup_wii_no__Q33ipl5scene11AddressEditFv();
extern "C" void stt_msg_dup_email__Q33ipl5scene11AddressEditFv();
extern "C" void stt_msg_my_wii_no__Q33ipl5scene11AddressEditFv();
extern "C" void stt_add_code_fadeout__Q33ipl5scene11AddressEditFv();
extern "C" void stt_add_name_fadein__Q33ipl5scene11AddressEditFv();
extern "C" void stt_add_name_normal__Q33ipl5scene11AddressEditFv();
extern "C" void stt_add_name_input__Q33ipl5scene11AddressEditFv();
extern "C" void stt_add_name_fadeout__Q33ipl5scene11AddressEditFv();
extern "C" void stt_add_mii_fadein__Q33ipl5scene11AddressEditFv();
extern "C" void stt_add_mii_normal__Q33ipl5scene11AddressEditFv();
extern "C" void stt_add_mii_input__Q33ipl5scene11AddressEditFv();
extern "C" void stt_msg_no_mii_add__Q33ipl5scene11AddressEditFv();
extern "C" void stt_add_mii_fadeout__Q33ipl5scene11AddressEditFv();
extern "C" void stt_add_confirm_fadein__Q33ipl5scene11AddressEditFv();
extern "C" void stt_add_confirm_normal__Q33ipl5scene11AddressEditFv();
extern "C" void stt_add_confirm_fadeout__Q33ipl5scene11AddressEditFv();
extern "C" void stt_wait_decide_anm_add__Q33ipl5scene11AddressEditFv();
extern "C" void stt_msg_no_mii__Q33ipl5scene11AddressEditFv();
extern "C" void stt_select_mii__Q33ipl5scene11AddressEditFv();
extern "C" void stt_msg_add_rlt__Q33ipl5scene11AddressEditFv();
extern "C" void stt_msg_net__Q33ipl5scene11AddressEditFv();
extern "C" void stt_wait_parental__Q33ipl5scene11AddressEditFv();
extern "C" void stt_wait_parental_dst__Q33ipl5scene11AddressEditFv();
extern "C" void stt_msg_wc__Q33ipl5scene11AddressEditFv();
extern "C" void stt_wait_parental_wc__Q33ipl5scene11AddressEditFv();
extern "C" void stt_wait_parental_dst_wc__Q33ipl5scene11AddressEditFv();
extern "C" void nigaoe_create_callback_add__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv();
extern "C" void start_point_event__Q33ipl5scene11AddressEditFPCcPQ33ipl10controller9Interface();
extern "C" void start_left_event__Q33ipl5scene11AddressEditFPCc();
extern "C" void start_trig_event__Q33ipl5scene11AddressEditFPCc();
extern "C" void start_ipt_trig_event__Q33ipl5scene11AddressEditFPCci();
extern "C" void stt_wait_decide_anm__Q33ipl5scene11AddressEditFv();
extern "C" void stt_msg_no_established__Q33ipl5scene11AddressEditFv();
extern "C" void set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw();
extern "C" void nigaoe_create_callback_edit__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv();
extern "C" void getName__Q33ipl6nigaoe6ObjectCFv();
extern "C" void getInputForm__Q29textinput7ManagerFv();
extern "C" void setDefaultTitleText__Q33ipl5scene11AddressEditFPCwb();
extern "C" void setEMail__Q43ipl5scene11AddressEdit6StringFPCw();
extern "C" void setWiiNo__Q43ipl5scene11AddressEdit6StringFPCw();
extern "C" void isDupCode__Q43ipl5scene11AddressEdit6StringCFv();
extern "C" void isMyCode__Q43ipl5scene11AddressEdit6StringCFv();
extern "C" void __ct__Q33ipl5scene11AddressEditFPQ23EGG4Heapi();
extern "C" void prepare__Q33ipl5scene11AddressEditFv();
extern "C" void create__Q33ipl5scene11AddressEditFv();
extern "C" void calcFadein__Q33ipl5scene11AddressEditFv();
extern "C" void initCalcNormal__Q33ipl5scene11AddressEditFv();
extern "C" void initCalcFadeout__Q33ipl5scene11AddressEditFv();
extern "C" void calcCommonAfter__Q33ipl5scene11AddressEditFv();
extern "C" void stt_normal__Q33ipl5scene11AddressEditFv();
extern "C" void stt_wait_btn_fadeout__Q33ipl5scene11AddressEditFv();
extern "C" void stt_wait_del_msg_fadein__Q33ipl5scene11AddressEditFv();
extern "C" void start_ipt_point_event__Q33ipl5scene11AddressEditFPCci();
extern "C" void start_ipt_left_event__Q33ipl5scene11AddressEditFPCci();
extern "C" void reset_gui__Q33ipl5scene11AddressEditFv();
extern "C" void add_friendinfo__Q33ipl5scene11AddressEditFv();
extern "C" void get_friendinfo__Q33ipl5scene11AddressEditFv();
extern "C" void delete_friendinfo__Q33ipl5scene11AddressEditFv();
extern "C" void update_friendinfo__Q33ipl5scene11AddressEditFv();
extern "C" void wiiid_utf16__Q33ipl5scene11AddressEditFUxPw();
extern "C" void calcFadeout__Q33ipl5scene11AddressEditFv();
extern "C" void draw__Q33ipl5scene11AddressEditFv();
extern "C" void stt_wait_btn_fadein__Q33ipl5scene11AddressEditFv();
extern "C" void stt_wait_del_msg_fadeout__Q33ipl5scene11AddressEditFv();
extern "C" void stt_wait_delete__Q33ipl5scene11AddressEditFv();
extern "C" void stt_wait_del_msg_fadeout_to_rlt__Q33ipl5scene11AddressEditFv();
extern "C" void stt_msg_del_rlt__Q33ipl5scene11AddressEditFv();
extern "C" void stt_ipt_wait_fadein__Q33ipl5scene11AddressEditFv();
extern "C" void stt_ipt_normal__Q33ipl5scene11AddressEditFv();
extern "C" void set_err_msg__Q33ipl5scene11AddressEditFPwUl8NWC24Err();
extern "C" void _savegpr_23();
extern "C" void _restgpr_23();
extern "C" void _savegpr_25();
extern "C" void _restgpr_25();
extern "C" void _savegpr_26();
extern "C" void _restgpr_26();
extern "C" void _savegpr_27();
extern "C" void _restgpr_27();
extern "C" void _savegpr_28();
extern "C" void _restgpr_28();
extern "C" void _savegpr_29();
extern "C" void _restgpr_29();
extern "C" void _savegpr_30();
extern "C" void _restgpr_30();
extern "C" void _savegpr_31();
extern "C" void _restgpr_31();
extern "C" void _savefpr_14();
extern "C" void _restfpr_14();
extern "C" void _savefpr_15();
extern "C" void _restfpr_15();
extern "C" void _savefpr_16();
extern "C" void _restfpr_16();
extern "C" void _savefpr_17();
extern "C" void _restfpr_17();
extern "C" void _savefpr_18();
extern "C" void _restfpr_18();
extern "C" void _savefpr_19();
extern "C" void _restfpr_19();
extern "C" void _savefpr_20();
extern "C" void _restfpr_20();
extern "C" void _savefpr_21();
extern "C" void _restfpr_21();
extern "C" void _savefpr_22();
extern "C" void _restfpr_22();
extern "C" void _savefpr_23();
extern "C" void _restfpr_23();
extern "C" void _savefpr_24();
extern "C" void _restfpr_24();
extern "C" void _savefpr_25();
extern "C" void _restfpr_25();
extern "C" void _savefpr_26();
extern "C" void _restfpr_26();
extern "C" void _savefpr_27();
extern "C" void _restfpr_27();
extern "C" void _savefpr_28();
extern "C" void _restfpr_28();
extern "C" void _savefpr_29();
extern "C" void _restfpr_29();
extern "C" void _savefpr_30();
extern "C" void _restfpr_30();
extern "C" void _savefpr_31();
extern "C" void _restfpr_31();
extern "C" void __div2u();
extern "C" void __mod2u();
extern "C" void __div2i();
extern "C" void __mod2i();
extern "C" void __cvt_sll_flt();
extern "C" void __cvt_flt_sll();
extern "C" void __shl2i();
extern "C" void __shr2i();
extern "C" void __shr2u();
extern "C" void __cvt_dbl_usll();
extern "C" void __cvt_usll_dbl();
extern "C" char __vt__Q33ipl5scene11AddressEdit;
extern "C" char __vt__Q33ipl5scene16AddressEditEvent;
extern "C" char __vt__Q33ipl5scene17AddressInputEvent;
extern "C" char jumptable_81648300;
extern "C" char jumptable_816483C0;
extern "C" char jumptable_816484B4;
extern "C" char jumptable_81648508;
extern "C" char jumptable_81648560;
extern "C" char lbl_81647FC9;
extern "C" char lbl_81647FD5;
extern "C" char lbl_816480FD;
extern "C" char lbl_8164810B;
extern "C" char lbl_8164848D;
extern "C" char lbl_816484A3;
extern "C" char lbl_816485EC;
extern "C" char sSystem__Q23ipl3snd;
extern "C" char typeInfo__Q34nw4r3lyt7TextBox;
extern "C" void ANSIToUTF16__Q33ipl7utility13CharacterCodeFPwPCUcl();
extern "C" void SetTexture__Q34nw4r3lyt8MaterialFUcRC9_GXTexObj();
extern "C" void __ct__Q33ipl3gui11PaneManagerFPQ23gui12EventHandlerPCQ34nw4r3lyt8DrawInfoPQ23EGG4HeapPQ23EGG9Allocatorb();
extern "C" void __ct__Q33ipl4math4VEC3Ffff();
extern "C" void __ct__Q33ipl5scene11TextBalloonFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePCcPCcRCQ33ipl4math4VEC3ff();
extern "C" void __ct__Q33ipl5scene14FaderSceneBaseFPQ23EGG4Heap();
extern "C" void __ct__Q33ipl6layout6ObjectFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePCcPCc();
extern "C" void __dl__FPv();
extern "C" void __dt__Q33ipl5scene4BaseFv();
extern "C" void __dt__Q33ipl6nigaoe6ObjectFv();
extern "C" void __nw__FUl();
extern "C" void add__Q33ipl5scene15FriendListCacheFUlRC15NWC24FriendInfo();
extern "C" void animation__Q33ipl5scene6ButtonFi();
extern "C" void bindToGroup__Q33ipl6layout6ObjectFPCcPCcbb();
extern "C" void bind__Q33ipl6layout6ObjectFPCcPCcbb();
extern "C" void callBtn1__Q23ipl12DialogWindowFPCwUl();
extern "C" void callBtn2__Q23ipl12DialogWindowFUlUlUlb();
extern "C" void check__Q33ipl5scene15FriendListCacheFv();
extern "C" void createChildScene__Q33ipl5scene4BaseFiPQ33ipl5scene4BasePQ33ipl5scene4BasePv();
extern "C" void create__Q33ipl6nigaoe7ManagerFPQ23EGG4HeapiiiPFPQ33ipl6nigaoe6ObjectPv_vPv();
extern "C" void enableKSXFilter__Q29textinput7ManagerFb();
extern "C" void fadein__Q33ipl5scene11TextBalloonFv();
extern "C" void fadeoutForce__Q33ipl5scene11TextBalloonFv();
extern "C" void finishBinding__Q33ipl6layout6ObjectFv();
extern "C" void getConnectEnableFlag__Q33ipl3ncd10NCDSettingFv();
extern "C" void getErrCode__Q33ipl5scene15FriendListCacheCFv();
extern "C" void getRegion__Q23ipl6SystemFv();
extern "C" void getYoungController__Q33ipl10controller7ManagerFv();
extern "C" void getZiOemDic__Q33ipl8keyboard7ManagerFv();
extern "C" void getZiSystemDic__Q33ipl8keyboard7ManagerFv();
extern "C" void initAnmFrame__Q33ipl6layout8AnimatorFv();
extern "C" void initZiString__Q39textinput9inputform4BaseFv();
extern "C" void init__Q33ipl5scene11TextBalloonFPCwUl();
extern "C" void isAvalable__Q33ipl6nigaoe7ManagerFUs();
extern "C" void isVacancy__Q29textinput7ManagerCFv();
extern "C" void openDictionary__Q39textinput8tistring6WithZiFPvPv();
extern "C" void sendRegisterMail__Q33ipl5scene15FriendListCacheFUl();
extern "C" void setPos__Q33ipl5scene11TextBalloonFRCQ33ipl4math4VEC3bi();
extern "C" void setTriggerTarget__Q33ipl3gui11PaneManagerFPQ34nw4r3lyt4Paneb();
extern "C" void startSE__Q33ipl3snd6SystemFPCc();
extern "C" void update__Q33ipl5scene15FriendListCacheFUlPCwUx();
extern "C" char smArg__Q23ipl6System;
extern "C" const char* smButtonName__Q33ipl5scene6Button[];
extern "C" void readLayoutAsync__Q33ipl4nand7ManagerFPQ23EGG4HeapPCcb();
extern "C" void List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs();
extern "C" void getScene__Q33ipl5scene7ManagerFi();
extern "C" void setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler();
extern "C" void calc__Q33ipl5scene11TextBalloonFv();
extern "C" void calc__Q33ipl6layout6ObjectFv();
extern "C" void isActive__Q33ipl5scene6ButtonCFv();
extern "C" void update__Q33ipl5scene6ButtonFv();
extern "C" void update__Q33ipl3gui11PaneManagerFv();
extern "C" void setOrtho__Q33ipl7utility8GraphicsFUl();
extern "C" void draw__Q33ipl6layout6ObjectFv();
extern "C" void draw__Q33ipl5scene11TextBalloonFv();
extern "C" void callBtn1__Q23ipl12DialogWindowFUlUl();
extern "C" void callS2Btn2__Q23ipl12DialogWindowFUlUlb();
extern "C" void reserveText__Q33ipl5scene6ButtonFiUl();
extern "C" void reserveAnm__Q33ipl5scene6ButtonFi();
extern "C" void initFrame__Q33ipl7utility15FrameControllerFv();
extern "C" void getMessage__Q33ipl7message7MessageCFUl();
extern "C" void del__Q33ipl5scene15FriendListCacheFUl();
extern "C" void reset_friend__Q33ipl5scene7AddressFv();
extern "C" void __div2u();
extern "C" void __mod2u();
extern "C" void UTF16ToANSI__Q33ipl7utility13CharacterCodeFPUcPCwl();
extern "C" void isValidId__Q33ipl5scene15FriendListCacheFRCUx();
extern "C" void isDupId__Q33ipl5scene15FriendListCacheFRCUx();
extern "C" void isDupMail__Q33ipl5scene15FriendListCacheFPCc();
extern "C" u64 utf16_wiiid__Q33ipl5scene11AddressEditFPCw(const wchar_t*);

extern "C" NWC24Err NWC24CheckPublicMailAddr_(const char* addr) {
    int i, j;
    int len;
    BOOL readingDomain;



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
        for (j = 0; j < (int)sizeof(lbl_8160F668); j++) {
            if (ch == lbl_8160F668[j]) {
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

ipl::scene::AddressEdit::AddressEdit(EGG::Heap* heap, int friendCode)
    : FaderSceneBase(heap) {
    u8* p = reinterpret_cast<u8*>(this);
    *reinterpret_cast<u32*>(p + 0x60) = 0;
    *reinterpret_cast<int*>(p + 0x84) = friendCode;
    *reinterpret_cast<int*>(p + 0x88) = -1;
    *reinterpret_cast<int*>(p + 0x8C) = -1;
    *reinterpret_cast<u32*>(p + 0xA4) = 0;
    *reinterpret_cast<AddressEdit**>(p + 0x4D4) = this;
    reinterpret_cast<String*>(p + 0xB0)->clear();
    *reinterpret_cast<u8*>(p + 0x4D8) = 0;
    *reinterpret_cast<u32*>(p + 0x4DC) = 0;
    *reinterpret_cast<u32*>(p + 0x4E8) = 0;
    *reinterpret_cast<u32*>(p + 0x28) = 3;
    for (int i = 0; i < 5; i++) {
        *reinterpret_cast<u32*>(p + 0x90 + i * 4) = 0;
    }
    for (int i = 0; i < 8; i++) {
        *reinterpret_cast<u8*>(p + 0x4E0 + i) = 0;
    }
}

ipl::scene::AddressEdit::~AddressEdit() {
    nigaoe::Object* obj =
        *reinterpret_cast<nigaoe::Object**>(reinterpret_cast<u8*>(this) + 0x4DC);
    if (obj != NULL) {
        delete obj;
    }
}

void ipl::scene::AddressEdit::prepare() {
    u8* p = reinterpret_cast<u8*>(this);
    *reinterpret_cast<nand::LayoutFile**>(p + 0xAC) =
        System::getNandManager()->readLayoutAsync(getSceneHeap(), sPool_balloon, false);
}


void ipl::scene::AddressEdit::create() {
    u8* p = reinterpret_cast<u8*>(this);

    Board* board = static_cast<Board*>(System::getScene(SCENE_BOARD));
    nand::LayoutFile* file = board->getLayoutFile();

    layout::Object* editLyt = new layout::Object(getSceneHeap(), file, "arc", "th_Adress_b.brlyt");
    editLyt->bindToGroup("th_Adress_b_card_strt.brlan", "card_strt_fnsh", false, true);
    editLyt->bindToGroup("th_Adress_b_btn_in.brlan", "crd_btn_00", false, true);
    editLyt->bindToGroup("th_Adress_b_btn_in.brlan", "crd_btn_10", false, false);
    editLyt->bindToGroup("th_Adress_b_btn_in.brlan", "crd_btn_11", false, false);
    editLyt->bindToGroup("th_Adress_b_btn_in.brlan", "mii_icon_00", false, false);
    editLyt->bind("th_Adress_b_btn_in.brlan", "T_frnd_crd_00", false, false);
    editLyt->bindToGroup("th_Adress_b_btn_psh.brlan", "crd_btn_00", false, false);
    editLyt->bindToGroup("th_Adress_b_btn_psh.brlan", "crd_btn_10", false, false);
    editLyt->bindToGroup("th_Adress_b_btn_psh.brlan", "crd_btn_11", false, false);
    editLyt->bindToGroup("th_Adress_b_btn_psh.brlan", "mii_icon_00", false, false);
    editLyt->bind("th_Adress_b_btn_psh.brlan", "T_frnd_crd_00", false, false);
    editLyt->bindToGroup("th_Adress_b_btn_out.brlan", "crd_btn_00", false, false);
    editLyt->bindToGroup("th_Adress_b_btn_out.brlan", "crd_btn_10", false, true);
    editLyt->bindToGroup("th_Adress_b_btn_out.brlan", "crd_btn_11", false, true);
    editLyt->bindToGroup("th_Adress_b_btn_out.brlan", "mii_icon_00", false, true);
    editLyt->bind("th_Adress_b_btn_out.brlan", "T_frnd_crd_00", false, true);
    editLyt->bindToGroup("th_Adress_b_btn_scl_in.brlan", "crd_btn_00", false, false);
    editLyt->bindToGroup("th_Adress_b_btn_scl_in.brlan", "crd_btn_10", false, false);
    editLyt->bindToGroup("th_Adress_b_btn_scl_in.brlan", "crd_btn_11", false, false);
    editLyt->bindToGroup("th_Adress_b_btn_scl_in.brlan", "mii_icon_00", false, false);
    editLyt->bind("th_Adress_b_btn_scl_in.brlan", "T_frnd_crd_00", false, false);
    editLyt->bindToGroup("th_Adress_b_btn_scl_out.brlan", "crd_btn_00", false, true);
    editLyt->bindToGroup("th_Adress_b_btn_scl_out.brlan", "crd_btn_10", false, true);
    editLyt->bindToGroup("th_Adress_b_btn_scl_out.brlan", "crd_btn_11", false, true);
    editLyt->bindToGroup("th_Adress_b_btn_scl_out.brlan", "mii_icon_00", false, true);
    editLyt->bind("th_Adress_b_btn_scl_out.brlan", "T_frnd_crd_00", false, true);
    editLyt->bindToGroup("th_Adress_b_btn_scl_in.brlan", "crd_btn_gry", false, true);
    editLyt->bindToGroup("th_Adress_b_btn_scl_out.brlan", "crd_btn_gry", false, false);
    editLyt->bindToGroup("th_Adress_b_card_msg_alp_in.brlan", "card_msg", false, true);
    editLyt->bindToGroup("th_Adress_b_card_msg_alp_out.brlan", "card_msg", false, false);
    editLyt->bindToGroup("th_Adress_b_card_fnsh.brlan", "card_strt_fnsh", false, false);
    editLyt->finishBinding();

    AddressEditEvent* evt = new AddressEditEvent(this);
    gui::PaneManager* pm = new gui::PaneManager(evt, editLyt->getDrawInfo(), NULL, NULL);
    pm->setupScene(editLyt);
    pm->setAllComponentTriggerTarget(false);
    for (int i = 0; i < 5; i++) {
        pm->setTriggerTarget(editLyt->FindPaneByName(scGuiPaneNames[i]), true);
    }
    *reinterpret_cast<layout::Object**>(p + 0x68) = editLyt;
    *reinterpret_cast<AddressEditEvent**>(p + 0x6C) = evt;
    *reinterpret_cast<gui::PaneManager**>(p + 0x70) = pm;
    nw4r::lyt::Pane* pane;
    pane = (*reinterpret_cast<layout::Object**>(p + 0x68))->GetRootPane()->FindPaneByName("T_crd_btn_00", true);
    set_textbox(pane, System::getMessage(0x2A));
    pane = (*reinterpret_cast<layout::Object**>(p + 0x68))->GetRootPane()->FindPaneByName("T_crd_btn_10", true);
    set_textbox(pane, System::getMessage(0x2B));
    pane = (*reinterpret_cast<layout::Object**>(p + 0x68))->GetRootPane()->FindPaneByName("T_crd_btn_11", true);
    set_textbox(pane, System::getMessage(0x2F));
    pane = (*reinterpret_cast<layout::Object**>(p + 0x68))->GetRootPane()->FindPaneByName("T_crd_btn_gry", true);
    set_textbox(pane, System::getMessage(0x2A));
    pane = (*reinterpret_cast<layout::Object**>(p + 0x68))->GetRootPane()->FindPaneByName("T_card_msg_00", true);
    set_textbox(pane, L"");
    pane = (*reinterpret_cast<layout::Object**>(p + 0x68))->GetRootPane()->FindPaneByName("T_name_00", true);
    set_textbox(pane, L"");
    pane = (*reinterpret_cast<layout::Object**>(p + 0x68))->GetRootPane()->FindPaneByName("T_frnd_crd_00", true);
    set_textbox(pane, L"");

    layout::Object* inputLyt = new layout::Object(getSceneHeap(), file, "arc", "th_Adress_c.brlyt");
    inputLyt->bindToGroup("th_Adress_c_card_strt.brlan", "G_card_strt_fnsh", false, true);
    inputLyt->bindToGroup("th_Adress_c_question_alp_in.brlan", "G_question_00", false, true);
    inputLyt->bindToGroup("th_Adress_c_name_alp_in.brlan", "G_name_00", false, true);
    inputLyt->bindToGroup("th_Adress_c_msg_alp_in.brlan", "G_msg_00", false, true);
    inputLyt->bindToGroup("th_Adress_c_mii_alp_in.brlan", "G_mii", false, true);
    inputLyt->bindToGroup("th_Adress_c_question_alp_out.brlan", "G_question_00", false, false);
    inputLyt->bindToGroup("th_Adress_c_name_alp_out.brlan", "G_name_00", false, false);
    inputLyt->bindToGroup("th_Adress_c_msg_alp_out.brlan", "G_msg_00", false, false);
    inputLyt->bindToGroup("th_Adress_c_mii_alp_out.brlan", "G_mii", false, false);
    inputLyt->bindToGroup("th_Adress_c_card_fnsh.brlan", "G_card_strt_fnsh", false, false);
    inputLyt->finishBinding();

    AddressInputEvent* evt2 = new AddressInputEvent(this);
    gui::PaneManager* pm2 = new gui::PaneManager(evt2, inputLyt->getDrawInfo(), NULL, NULL);
    pm2->setupScene(inputLyt);
    pm2->setAllComponentTriggerTarget(false);
    pm2->setTriggerTarget(inputLyt->FindPaneByName(lbl_816965E0), true);
    *reinterpret_cast<layout::Object**>(p + 0x74) = inputLyt;
    *reinterpret_cast<AddressInputEvent**>(p + 0x78) = evt2;
    *reinterpret_cast<gui::PaneManager**>(p + 0x7C) = pm2;

    *reinterpret_cast<layout::Object**>(p + 0x80) =
        new layout::Object(getSceneHeap(), file, "arc", "my_Back_a.brlyt");
    (*reinterpret_cast<layout::Object**>(p + 0x80))->bind("my_Back_a_Apear.brlan", "Picture_00", false, true);
    (*reinterpret_cast<layout::Object**>(p + 0x80))->bind("my_Back_a_Lost.brlan", "Picture_00", false, false);
    (*reinterpret_cast<layout::Object**>(p + 0x80))->finishBinding();
    (*reinterpret_cast<layout::Object**>(p + 0x80))->getAnim(0)->initAnmFrame();

    reinterpret_cast<String*>(p + 0xB0)->clear();
    memset(&sFriendInfo, 0, sizeof(NWC24FriendInfo));
    *reinterpret_cast<u32*>(p + 0x4DC) = 0;
    *reinterpret_cast<u32*>(p + 0x4E8) = 0;

    u8* addr = reinterpret_cast<u8*>(System::getScene(SCENE_ADDRESS));
    *reinterpret_cast<void**>(p + 0x4EC) = *reinterpret_cast<void**>(addr + 0x274);

    switch (*reinterpret_cast<int*>(p + 0x84)) {
        case 0: {
            *reinterpret_cast<int*>(p + 0xA4) = *reinterpret_cast<int*>(addr + 0xC0);
            get_friendinfo();
            if (*reinterpret_cast<u32*>(
                    *reinterpret_cast<u8**>(p + 0x4EC) + *reinterpret_cast<u32*>(p + 0xA4) * 0x140 + 4) == 2) {
                (*reinterpret_cast<layout::Object**>(p + 0x68))->getAnim(0x15)->initAnmFrame();
                (*reinterpret_cast<layout::Object**>(p + 0x68))->getAnim(0x1A)->initAnmFrame();
            } else {
                (*reinterpret_cast<layout::Object**>(p + 0x68))->getAnim(0x10)->initAnmFrame();
                (*reinterpret_cast<layout::Object**>(p + 0x68))->getAnim(0x1B)->initAnmFrame();
            }
            (*reinterpret_cast<layout::Object**>(p + 0x68))->getAnim(0)->play();
            nw4r::lyt::Pane* pane = (*reinterpret_cast<layout::Object**>(p + 0x68))->GetRootPane()->FindPaneByName("T_name_00", true);
            const wchar_t* str = reinterpret_cast<const wchar_t*>(p + 0x2B4);
            set_textbox(pane, str);
            pane = (*reinterpret_cast<layout::Object**>(p + 0x68))->GetRootPane()->FindPaneByName("T_frnd_crd_00", true);
            str = reinterpret_cast<const wchar_t*>(p + 0x2CC);
            set_textbox(pane, str);
            *reinterpret_cast<s32*>(p + 0x64) = 0;
            break;
        }
        case 1: {
            (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(0)->play();
            (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(1)->play();
            (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(3)->play();
            (*reinterpret_cast<layout::Object**>(p + 0x68))->getAnim(0x1A)->initAnmFrame();
            (*reinterpret_cast<layout::Object**>(p + 0x68))->getAnim(0x10)->initAnmFrame();
            nw4r::lyt::Pane* pane = (*reinterpret_cast<layout::Object**>(p + 0x74))->GetRootPane()->FindPaneByName("T_question_00", true);
            set_textbox(pane, System::getMessage(0x31));
            pane = (*reinterpret_cast<layout::Object**>(p + 0x74))->GetRootPane()->FindPaneByName("T_msg_00", true);
            set_textbox(pane, System::getMessage(0x47));
            *reinterpret_cast<s32*>(p + 0x64) = 0x10;
            break;
        }
        case 2: {
            (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(0)->play();
            (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(1)->play();
            (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(3)->play();
            (*reinterpret_cast<layout::Object**>(p + 0x68))->getAnim(0x1A)->initAnmFrame();
            (*reinterpret_cast<layout::Object**>(p + 0x68))->getAnim(0x10)->initAnmFrame();
            nw4r::lyt::Pane* pane = (*reinterpret_cast<layout::Object**>(p + 0x74))->GetRootPane()->FindPaneByName("T_question_00", true);
            set_textbox(pane, System::getMessage(0x3F));
            pane = (*reinterpret_cast<layout::Object**>(p + 0x74))->GetRootPane()->FindPaneByName("T_msg_00", true);
            set_textbox(pane, System::getMessage(0x48));
            *reinterpret_cast<s32*>(p + 0x64) = 0x10;
            break;
        }
    }

    s16 rflIdx;
    if (RFLSearchOfficialData(reinterpret_cast<RFLCreateID*>(p + 0x4E0), reinterpret_cast<u16*>(&rflIdx))) {
        EGG::Heap* mem2 = System::getMem2App();
        System::getMiiManager()->create(mem2, 0x4C, 0x4C, rflIdx,
                                        nigaoe_create_callback_edit, this);
        *reinterpret_cast<u32*>(p + 0x4E8) = 1;
    }

    System::getKeyboard()->init();

    float balloonSpeed = 30.0f, balloonScale = 120.0f;
    *reinterpret_cast<TextBalloon**>(p + 0xA8) = new TextBalloon(
        getSceneHeap(), *reinterpret_cast<nand::LayoutFile**>(p + 0xAC),
        "arc", "my_IplTopBalloon_a.brlyt",
        math::VEC3(0.0f, 0.0f, 0.0f), balloonScale, balloonSpeed);
}


ipl::scene::FaderSceneCommand ipl::scene::AddressEdit::calcFadein() {
    u8* p = reinterpret_cast<u8*>(this);
    FaderSceneCommand result = FADER_SCN_CONTINUE;
    if (!(*reinterpret_cast<layout::Object**>(p + 0x68))->getAnim()->isPlaying() &&
        !(*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim()->isPlaying()) {
        result = FADER_SCN_NEXT;
    }
    return result;
}

void ipl::scene::AddressEdit::initCalcNormal() {
    static_cast<scene::Button*>(System::getScene(SCENE_BUTTON))->setEventHandler(this, NULL);
}


ipl::scene::FaderSceneCommand ipl::scene::AddressEdit::calcNormal() {
    u8* p = reinterpret_cast<u8*>(this);
    switch (*reinterpret_cast<u32*>(p + 0x64)) {
        case 0x00: stt_normal(); break;
        case 0x01: stt_wait_decide_anm(); break;
        case 0x02: stt_wait_btn_fadein(); break;
        case 0x03: stt_wait_btn_fadeout(); break;
        case 0x04: stt_wait_del_msg_fadein(); break;
        case 0x05: stt_wait_del_msg_fadeout(); break;
        case 0x06: stt_wait_del_msg_fadeout_to_rlt(); break;
        case 0x07: stt_wait_delete(); break;
        case 0x08: stt_msg_del_rlt(); break;
        case 0x09: stt_msg_code_edit(); break;
        case 0x0A: stt_msg_no_mii(); break;
        case 0x0B: stt_select_mii(); break;
        case 0x0C: stt_ipt_wait_fadein(); break;
        case 0x0D: stt_ipt_normal(); break;
        case 0x0E: stt_ipt_input(); break;
        case 0x0F: stt_ipt_wait_fadeout(); break;
        case 0x10: stt_add_code_fadein(); break;
        case 0x11: stt_add_code_normal(); break;
        case 0x12: stt_add_code_input(); break;
        case 0x13: stt_msg_code_invalid(); break;
        case 0x14: stt_msg_dup_wii_no(); break;
        case 0x15: stt_msg_dup_email(); break;
        case 0x16: stt_msg_my_wii_no(); break;
        case 0x17: stt_add_code_fadeout(); break;
        case 0x18: stt_add_name_fadein(); break;
        case 0x19: stt_add_name_normal(); break;
        case 0x1A: stt_add_name_input(); break;
        case 0x1B: stt_add_name_fadeout(); break;
        case 0x1C: stt_add_mii_fadein(); break;
        case 0x1D: stt_add_mii_normal(); break;
        case 0x1E: stt_add_mii_input(); break;
        case 0x1F: stt_msg_no_mii_add(); break;
        case 0x20: stt_add_mii_fadeout(); break;
        case 0x21: stt_add_confirm_fadein(); break;
        case 0x22: stt_add_confirm_normal(); break;
        case 0x23: stt_add_confirm_fadeout(); break;
        case 0x24: stt_wait_decide_anm_add(); break;
        case 0x25: stt_msg_code_add(); break;
        case 0x26: stt_msg_add_rlt(); break;
        case 0x27: stt_msg_net(); break;
        case 0x28: stt_wait_parental(); break;
        case 0x29: stt_wait_parental_dst(); break;
        case 0x2A: stt_msg_wc(); break;
        case 0x2B: stt_wait_parental_wc(); break;
        case 0x2C: stt_wait_parental_dst_wc(); break;
        case 0x2D: stt_msg_parental(); break;
        case 0x2E: stt_msg_nwc24_error(); break;
        case 0x2F: stt_msg_no_established(); break;
    }
    switch (*reinterpret_cast<u32*>(p + 0x64)) {
        case 0x00:
        case 0x03:
        case 0x09:
        case 0x0C:
        case 0x1D:
        case 0x20:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x27:
        case 0x2A:
        case 0x2D:
        case 0x2E:
        case 0x2F:
            (*reinterpret_cast<TextBalloon**>(p + 0xA8))->calc();
            break;
    }
    return *reinterpret_cast<u32*>(p + 0x64) == 0x30 ? FADER_SCN_NEXT : FADER_SCN_CONTINUE;
}

void ipl::scene::AddressEdit::initCalcFadeout() {
    u8* p = reinterpret_cast<u8*>(this);
    static_cast<scene::Button*>(System::getScene(SCENE_BUTTON))->setEventHandler(NULL, NULL);
    (*reinterpret_cast<TextBalloon**>(p + 0xA8))->calc();
}

ipl::scene::FaderSceneCommand ipl::scene::AddressEdit::calcFadeout() {
    u8* p = reinterpret_cast<u8*>(this);
    (*reinterpret_cast<TextBalloon**>(p + 0xA8))->calc();
    if (System::getFader()->getStatus() == EGG::Fader::PREPARE_OUT) {
        FaderSceneCommand result = FADER_SCN_CONTINUE;
        if (!(*reinterpret_cast<layout::Object**>(p + 0x68))->getAnim(0x1E)->isPlaying() &&
            !(*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(9)->isPlaying()) {
            result = FADER_SCN_NEXT;
        }
        return result;
    }
    return (FaderSceneCommand)(System::getFader()->getStatus() == EGG::Fader::PREPARE_IN);
}

void ipl::scene::AddressEdit::calcCommonAfter() {
    u8* p = reinterpret_cast<u8*>(this);
    (*reinterpret_cast<gui::PaneManager**>(p + 0x70))->calc();
    (*reinterpret_cast<layout::Object**>(p + 0x68))->calc();
    (*reinterpret_cast<gui::PaneManager**>(p + 0x7C))->calc();
    (*reinterpret_cast<layout::Object**>(p + 0x74))->calc();
    (*reinterpret_cast<layout::Object**>(p + 0x80))->calc();
}

void ipl::scene::AddressEdit::draw() {
    u8* p = reinterpret_cast<u8*>(this);
    if (System::onDefaultDrawLayer()) {
        utility::Graphics::setOrtho(0);
        (*reinterpret_cast<layout::Object**>(p + 0x68))->draw();
        (*reinterpret_cast<layout::Object**>(p + 0x80))->draw();
        (*reinterpret_cast<layout::Object**>(p + 0x74))->draw();
        (*reinterpret_cast<TextBalloon**>(p + 0xA8))->draw();
    }
}

char sPool_mii_msg[] = "T_mii_msg_00";

void ipl::scene::AddressEdit::stt_normal() {
    u8* p = reinterpret_cast<u8*>(this);
    scene::Button* button = static_cast<scene::Button*>(System::getScene(SCENE_BUTTON));
    if (button->isActive()) {
        button->update();
    }
    if (*reinterpret_cast<u32*>(p + 0x64) == 0) {
        (*reinterpret_cast<gui::PaneManager**>(p + 0x70))->update();
    }
}

void ipl::scene::AddressEdit::stt_wait_decide_anm() {
    u8* p = reinterpret_cast<u8*>(this);
    bool finished = true;
    Button* button = static_cast<Button*>(System::getScene(SCENE_BUTTON));
    for (int i = 0; i < 5; i++) {
        finished &= !(*reinterpret_cast<layout::Object**>(p + 0x68))
                                    ->getAnim((u16)(*reinterpret_cast<u32*>(p + 0x88) + 6))
                                    ->isPlaying();
    }
    if (finished) {
        switch (*reinterpret_cast<u32*>(p + 0x88)) {
            case 2: {
                if (reinterpret_cast<FriendListCache*>(*reinterpret_cast<void**>(p + 0x4EC))
                        ->getInfo(*reinterpret_cast<u32*>(p + 0xA4))
                        .attr.status == NWC24_FRIENDSTATUS_CONFIRMED) {
                    (*reinterpret_cast<layout::Object**>(p + 0x68))->getAnim(0x15)->play();
                }
                else {
                    (*reinterpret_cast<layout::Object**>(p + 0x68))->getAnim(0x1B)->play();
                }
                (*reinterpret_cast<layout::Object**>(p + 0x68))->getAnim(0x16)->play();
                (*reinterpret_cast<layout::Object**>(p + 0x68))->getAnim(0x17)->play();
                button->reserveAnm(0xC);
                *reinterpret_cast<u32*>(p + 0x64) = 3;
                (*reinterpret_cast<TextBalloon**>(p + 0xA8))->fadeoutForce();
                reset_gui();
                break;
            }
            case 1: {
                button->reserveAnm(0xC);
                button->reserveText(1, 0x2E);
                button->reserveAnm(0xF);
                (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(0)->play();
                (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(1)->play();
                (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(2)->play();
                (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(3)->initAnmFrame();
                (*reinterpret_cast<layout::Object**>(p + 0x80))->getAnim(0)->play();
                nw4r::lyt::Pane* tp = (*reinterpret_cast<layout::Object**>(p + 0x74))
                                          ->GetRootPane()->FindPaneByName("T_question_00", true);
                set_textbox(tp, System::getMessage(0x32));
                tp = (*reinterpret_cast<layout::Object**>(p + 0x74))
                         ->GetRootPane()->FindPaneByName("T_name_00", true);
                set_textbox(tp, reinterpret_cast<const wchar_t*>(p + 0x2B4));
                tp = (*reinterpret_cast<layout::Object**>(p + 0x74))
                         ->GetRootPane()->FindPaneByName("T_msg_00", true);
                set_textbox(tp, System::getMessage(0x49));
                (*reinterpret_cast<TextBalloon**>(p + 0xA8))->fadeoutForce();
                reset_gui();
                *reinterpret_cast<u32*>(p + 0x64) = 0xC;
                break;
            }
            case 3: {
                if (*reinterpret_cast<s32*>(p + 0x4E8) == 1) {
                    return;
                }
                *reinterpret_cast<u32*>(p + 0x4E8) = 0;
                if (RFLGetAvailableOfficialDataNum() != 0) {
                    button->reserveAnm(0xC);
                    button->reserveAnm(0xB);
                    createChildScene(SCENE_FACE_SELECT, this, NULL, (void*)1);
                    *reinterpret_cast<u32*>(p + 0x64) = 0xB;
                }
                else {
                    System::getDialog()->callBtn1(0x17C, 0x2E);
                    *reinterpret_cast<u32*>(p + 0x64) = 0xA;
                }
                (*reinterpret_cast<TextBalloon**>(p + 0xA8))->fadeoutForce();
                break;
            }
            case 0: {
                SCParentalControlsInfo pcInfo;
                BOOL parental = SCGetParentalControl(&pcInfo);
                if (!ncd::NCDSetting::getConnectEnableFlag()) {
                    button->animation(0x1D);
                    System::getDialog()->callBtn2(0x144, 0x146, 0x25, false);
                    *reinterpret_cast<u32*>(p + 0x64) = 0x27;
                }
                else if (!(SCGetWCFlags() & 1)) {
                    button->animation(0x1D);
                    System::getDialog()->callBtn2(0x17E, 0x146, 0x25, false);
                    *reinterpret_cast<u32*>(p + 0x64) = 0x2A;
                }
                else if (parental && (pcInfo.enable & SC_PARENTAL_FLAG_ENABLED) && (SCGetNetContentRestrictions() & 2)) {
                    button->animation(0x1D);
                    System::getDialog()->callBtn1(0x14C, 0x2E);
                    *reinterpret_cast<u32*>(p + 0x64) = 0x2D;
                }
                else if (reinterpret_cast<FriendListCache*>(*reinterpret_cast<void**>(p + 0x4EC))->check() == NWC24_ERR_NETWORK
                         || reinterpret_cast<FriendListCache*>(*reinterpret_cast<void**>(p + 0x4EC))->mUnk_0x9D74 == NWC24_ERR_SERVER
                         || reinterpret_cast<FriendListCache*>(*reinterpret_cast<void**>(p + 0x4EC))->mUnk_0x9D74 == NWC24_ERR_FULL) {
                    wchar_t msg[0x400];
                    wchar_t* wp = msg - 1;
                    for (int i = 0; i < 0x200; i++) {
                        *++wp = 0;
                        *++wp = 0;
                    }
                    set_err_msg(msg, 0x400,
                                (NWC24Err)reinterpret_cast<FriendListCache*>(*reinterpret_cast<void**>(p + 0x4EC))->mUnk_0x9D74);
                    System::getDialog()->callBtn1(msg, 0x2E);
                    button->animation(0x1D);
                    *reinterpret_cast<u32*>(p + 0x64) = 0x2E;
                }
                else {
                    button->reserveAnm(0xC);
                    button->reserveText(1, 0x27);
                    button->reserveText(0, 0x4F);
                    button->reserveAnm(0xF);
                    reserveSceneChange(0xB, (void*)1);
                    (*reinterpret_cast<layout::Object**>(p + 0x68))->getAnim(0x1E)->play();
                    *reinterpret_cast<u32*>(p + 0x64) = 0x30;
                }
                (*reinterpret_cast<TextBalloon**>(p + 0xA8))->fadeoutForce();
                reset_gui();
                break;
            }
            case 4: {
                System::getDialog()->callBtn1(reinterpret_cast<String*>(p + 0xB0)->getDispCodeLong(), 0x2E);
                (*reinterpret_cast<TextBalloon**>(p + 0xA8))->fadeoutForce();
                reset_gui();
                *reinterpret_cast<u32*>(p + 0x64) = 9;
                break;
            }
            default: {
                *reinterpret_cast<u32*>(p + 0x64) = 0;
                break;
            }
        }
    }
}

const wchar_t* ipl::scene::AddressEdit::String::getDispCodeLong() const {
    if (reinterpret_cast<const u8*>(this)[0x422] == 0) {
        return;
    }
    return reinterpret_cast<const wchar_t*>(reinterpret_cast<const u8*>(this) + 0x21c);
}

extern "C" asm void stt_wait_btn_fadein__Q33ipl5scene11AddressEditFv() {
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

extern "C" asm void stt_wait_btn_fadeout__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_29
    lwz r0, 0xa4(r3)
    mr r31, r3
    lwz r4, 0x4ec(r3)
    mulli r0, r0, 0x140
    add r4, r4, r0
    lwz r0, 0x4(r4)
    cmplwi r0, 0x2
    bne stt_wait_btn_fadeout__Q3_L0
    lwz r3, 0x68(r3)
    li r4, 0x15
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r3, 0x14(r3)
    subi r3, r3, 0x1
    subic r0, r3, 0x1
    subfe r29, r0, r3
    b stt_wait_btn_fadeout__Q3_L1
stt_wait_btn_fadeout__Q3_L0:
    lwz r3, 0x68(r3)
    li r4, 0x1b
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r3, 0x14(r3)
    subi r3, r3, 0x1
    subic r0, r3, 0x1
    subfe r29, r0, r3
stt_wait_btn_fadeout__Q3_L1:
    lwz r3, 0x68(r31)
    li r4, 0x16
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r5, 0x14(r3)
    li r4, 0x17
    lwz r3, 0x68(r31)
    subi r5, r5, 0x1
    subic r0, r5, 0x1
    addi r3, r3, 0x28c
    subfe r0, r0, r5
    and r5, r29, r0
    subic r0, r5, 0x1
    subfe r30, r0, r5
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r3, 0x14(r3)
    subi r3, r3, 0x1
    subic r0, r3, 0x1
    subfe r0, r0, r3
    and r3, r30, r0
    subic r0, r3, 0x1
    subfe. r0, r0, r3
    beq stt_wait_btn_fadeout__Q3_L2
    lwz r3, 0x68(r31)
    lis r4, lbl_816480FD@ha
    addi r4, r4, lbl_816480FD@l
    li r5, 0x1
    lwz r3, 0x14(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    lis r30, smArg__Q23ipl6System@ha
    mr r29, r3
    addi r30, r30, smArg__Q23ipl6System@l
    li r4, 0x30
    lwz r3, 0x80(r30)
    lwz r3, 0x0(r3)
    bl getMessage__Q33ipl7message7MessageCFUl
    mr r5, r3
    mr r3, r31
    mr r4, r29
    bl set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw
    lwz r3, 0xac(r30)
    li r4, 0x142
    li r5, 0x141
    li r6, 0x1
    bl callS2Btn2__Q23ipl12DialogWindowFUlUlb
    lwz r3, 0x68(r31)
    li r4, 0x1c
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r29, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    li r3, 0x1
    li r0, 0x4
    stw r3, 0x14(r29)
    stw r0, 0x64(r31)
stt_wait_btn_fadeout__Q3_L2:
    addi r11, r1, 0x20
    bl _restgpr_29
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void stt_wait_del_msg_fadein__Q33ipl5scene11AddressEditFv() {
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

extern "C" asm void stt_wait_del_msg_fadeout__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_29
    lwz r5, 0x68(r3)
    mr r31, r3
    li r4, 0x1d
    addi r3, r5, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_wait_del_msg_fadeout_L2
    lwz r0, 0xa4(r31)
    lwz r3, 0x4ec(r31)
    mulli r0, r0, 0x140
    add r3, r3, r0
    lwz r0, 0x4(r3)
    cmplwi r0, 0x2
    bne stt_wait_del_msg_fadeout_L0
    lwz r3, 0x68(r31)
    li r4, 0x10
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r30, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    li r0, 0x1
    stw r0, 0x14(r30)
    b stt_wait_del_msg_fadeout_L1
stt_wait_del_msg_fadeout_L0:
    lwz r3, 0x68(r31)
    li r4, 0x1a
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r30, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    li r0, 0x1
    stw r0, 0x14(r30)
stt_wait_del_msg_fadeout_L1:
    lwz r3, 0x68(r31)
    li r4, 0x11
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r29, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    li r30, 0x1
    li r4, 0x12
    stw r30, 0x14(r29)
    lwz r3, 0x68(r31)
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r29, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    stw r30, 0x14(r29)
    li r0, 0x2
    stw r0, 0x64(r31)
stt_wait_del_msg_fadeout_L2:
    addi r11, r1, 0x20
    bl _restgpr_29
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void stt_wait_delete__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0x5
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    lis r31, smArg__Q23ipl6System@ha
    addi r31, r31, smArg__Q23ipl6System@l
    stw r30, 0x8(r1)
    mr r30, r3
    lwz r3, 0x64(r31)
    bl getScene__Q33ipl5scene7ManagerFi
    lwz r4, 0xac(r31)
    lwz r0, 0x24(r4)
    cmpwi r0, 0x2
    beq stt_wait_delete__Q33ipl5_L0
    bge stt_wait_delete__Q33ipl5_L2
    cmpwi r0, 0x1
    bge stt_wait_delete__Q33ipl5_L1
    b stt_wait_delete__Q33ipl5_L2
stt_wait_delete__Q33ipl5_L0:
    mr r3, r30
    bl delete_friendinfo__Q33ipl5scene11AddressEditFv
    lwz r3, 0x68(r30)
    li r4, 0x1d
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r31, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    li r3, 0x1
    li r0, 0x6
    stw r3, 0x14(r31)
    stw r0, 0x64(r30)
    b stt_wait_delete__Q33ipl5_L2
stt_wait_delete__Q33ipl5_L1:
    li r4, 0xb
    bl reserveAnm__Q33ipl5scene6ButtonFi
    lwz r3, 0x68(r30)
    li r4, 0x1d
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r31, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    li r3, 0x1
    li r0, 0x5
    stw r3, 0x14(r31)
    stw r0, 0x64(r30)
stt_wait_delete__Q33ipl5_L2:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_wait_del_msg_fadeout_to_rlt__Q33ipl5scene11AddressEditFv() {
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

extern "C" asm void stt_msg_del_rlt__Q33ipl5scene11AddressEditFv() {
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

extern "C" asm void stt_ipt_wait_fadein__Q33ipl5scene11AddressEditFv() {
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

extern "C" asm void stt_ipt_normal__Q33ipl5scene11AddressEditFv() {
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

/*
    This is a modified version of NWC24CheckPublicMailAddr.
    Changes:
     - Uses strnicmp instead of NWC24's Mail_strnicmp
     - ... That's it!!
*/

extern "C" asm void stt_ipt_input__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_28
    lis r29, smArg__Q23ipl6System@ha
    mr r30, r3
    addi r29, r29, smArg__Q23ipl6System@l
    lwz r3, 0x90(r29)
    lwz r12, 0x0(r3)
    lwz r12, 0x34(r12)
    mtctr r12
    bctrl
    mr r28, r3
    lwz r3, 0x64(r29)
    li r4, 0x5
    bl getScene__Q33ipl5scene7ManagerFi
    lwz r0, 0x4(r28)
    mr r31, r3
    cmpwi r0, 0x3
    beq stt_ipt_input__Q33ipl5sc_L1
    bge stt_ipt_input__Q33ipl5sc_L0
    cmpwi r0, 0x2
    bge stt_ipt_input__Q33ipl5sc_L9
    cmpwi r0, 0x0
    bge stt_ipt_input__Q33ipl5sc_L8
    b stt_ipt_input__Q33ipl5sc_L9
stt_ipt_input__Q33ipl5sc_L0:
    cmpwi r0, 0x5
    bge stt_ipt_input__Q33ipl5sc_L9
    b stt_ipt_input__Q33ipl5sc_L7
stt_ipt_input__Q33ipl5sc_L1:
    lbz r0, 0x8(r28)
    lhz r3, 0x2b4(r30)
    cmpwi r0, 0x0
    cntlzw r0, r3
    srwi r29, r0, 5
    beq stt_ipt_input__Q33ipl5sc_L2
    lwz r4, 0xc(r28)
    addi r3, r30, 0xb0
    bl setName__Q43ipl5scene11AddressEdit6StringFPCw
    lwz r3, 0x74(r30)
    lis r4, lbl_8164810B@ha
    addi r4, r4, lbl_8164810B@l
    li r5, 0x1
    lwz r3, 0x14(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    mr r4, r3
    mr r3, r30
    addi r5, r30, 0x2b4
    bl set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw
stt_ipt_input__Q33ipl5sc_L2:
    lhz r0, 0x2b4(r30)
    cmpwi r0, 0x0
    bne stt_ipt_input__Q33ipl5sc_L4
    cmpwi r29, 0x0
    bne stt_ipt_input__Q33ipl5sc_L3
    lwz r3, 0x74(r30)
    li r4, 0x6
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    li r29, 0x1
    li r4, 0x3
    stw r29, 0x14(r28)
    lwz r3, 0x74(r30)
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    stw r29, 0x14(r28)
stt_ipt_input__Q33ipl5sc_L3:
    mr r3, r31
    li r4, 0xb
    bl reserveAnm__Q33ipl5scene6ButtonFi
    b stt_ipt_input__Q33ipl5sc_L9
stt_ipt_input__Q33ipl5sc_L4:
    cmpwi r29, 0x0
    beq stt_ipt_input__Q33ipl5sc_L5
    lwz r3, 0x74(r30)
    li r4, 0x2
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    li r29, 0x1
    li r4, 0x7
    stw r29, 0x14(r28)
    lwz r3, 0x74(r30)
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    stw r29, 0x14(r28)
stt_ipt_input__Q33ipl5sc_L5:
    lbz r0, 0x4d1(r30)
    cmpwi r0, 0x0
    beq stt_ipt_input__Q33ipl5sc_L6
    mr r3, r31
    li r4, 0x1
    li r5, 0x2e
    bl reserveText__Q33ipl5scene6ButtonFiUl
    mr r3, r31
    li r4, 0xf
    bl reserveAnm__Q33ipl5scene6ButtonFi
    b stt_ipt_input__Q33ipl5sc_L9
stt_ipt_input__Q33ipl5sc_L6:
    mr r3, r31
    li r4, 0xb
    bl reserveAnm__Q33ipl5scene6ButtonFi
    b stt_ipt_input__Q33ipl5sc_L9
stt_ipt_input__Q33ipl5sc_L7:
    li r0, 0xd
    stw r0, 0x64(r30)
    bl getRegion__Q23ipl6SystemFv
    cmplwi r3, 0x6
    bne stt_ipt_input__Q33ipl5sc_L9
    lwz r3, 0x90(r29)
    li r4, 0x0
    lwz r3, 0x4(r3)
    bl enableKSXFilter__Q29textinput7ManagerFb
    b stt_ipt_input__Q33ipl5sc_L9
stt_ipt_input__Q33ipl5sc_L8:
    lwz r3, 0x90(r29)
    lwz r3, 0x4(r3)
    bl isVacancy__Q29textinput7ManagerCFv
    mr r5, r3
    mr r3, r30
    li r4, 0x0
    bl setDefaultTitleText__Q33ipl5scene11AddressEditFPCwb
stt_ipt_input__Q33ipl5sc_L9:
    addi r11, r1, 0x20
    bl _restgpr_28
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void stt_ipt_wait_fadeout__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0x5
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r5, 0x74(r3)
    addi r3, r5, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_ipt_wait_fadeout__Q3_L0
    lwz r3, 0x74(r31)
    li r4, 0x7
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_ipt_wait_fadeout__Q3_L0
    lwz r3, 0x74(r31)
    li r4, 0x6
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_ipt_wait_fadeout__Q3_L0
    lwz r3, 0x74(r31)
    li r4, 0x8
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_ipt_wait_fadeout__Q3_L0
    lwz r3, 0x74(r31)
    li r4, 0x9
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_ipt_wait_fadeout__Q3_L0
    lwz r3, 0x80(r31)
    li r4, 0x1
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_ipt_wait_fadeout__Q3_L0
    li r0, 0x0
    stw r0, 0x64(r31)
stt_ipt_wait_fadeout__Q3_L0:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_add_code_fadein__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0x0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r5, 0x74(r3)
    addi r3, r5, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_add_code_fadein__Q33_L0
    lwz r3, 0x74(r31)
    li r4, 0x1
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_add_code_fadein__Q33_L0
    lwz r3, 0x74(r31)
    li r4, 0x3
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_add_code_fadein__Q33_L0
    lwz r3, 0x74(r31)
    li r4, 0x4
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_add_code_fadein__Q33_L0
    lwz r3, 0x74(r31)
    li r4, 0x2
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_add_code_fadein__Q33_L0
    li r0, 0x11
    stw r0, 0x64(r31)
stt_add_code_fadein__Q33_L0:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_add_code_normal__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r5, smArg__Q23ipl6System@ha
    li r4, 0x5
    stw r0, 0x14(r1)
    addi r5, r5, smArg__Q23ipl6System@l
    stw r31, 0xc(r1)
    stw r30, 0x8(r1)
    mr r30, r3
    lwz r3, 0x64(r5)
    bl getScene__Q33ipl5scene7ManagerFi
    mr r31, r3
    bl isActive__Q33ipl5scene6ButtonCFv
    cmpwi r3, 0x0
    beq stt_add_code_normal__Q33_L0
    mr r3, r31
    bl update__Q33ipl5scene6ButtonFv
stt_add_code_normal__Q33_L0:
    lwz r0, 0x64(r30)
    cmpwi r0, 0x11
    bne stt_add_code_normal__Q33_L1
    lwz r3, 0x7c(r30)
    bl update__Q33ipl3gui11PaneManagerFv
stt_add_code_normal__Q33_L1:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_add_code_input__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_28
    lis r29, smArg__Q23ipl6System@ha
    mr r30, r3
    addi r29, r29, smArg__Q23ipl6System@l
    lwz r3, 0x90(r29)
    lwz r12, 0x0(r3)
    lwz r12, 0x34(r12)
    mtctr r12
    bctrl
    mr r28, r3
    lwz r3, 0x64(r29)
    li r4, 0x5
    bl getScene__Q33ipl5scene7ManagerFi
    lwz r0, 0x4(r28)
    mr r31, r3
    cmpwi r0, 0x3
    beq stt_add_code_input__Q33i_L1
    bge stt_add_code_input__Q33i_L0
    cmpwi r0, 0x2
    bge stt_add_code_input__Q33i_L19
    cmpwi r0, 0x0
    bge stt_add_code_input__Q33i_L18
    b stt_add_code_input__Q33i_L19
stt_add_code_input__Q33i_L0:
    cmpwi r0, 0x5
    bge stt_add_code_input__Q33i_L19
    b stt_add_code_input__Q33i_L9
stt_add_code_input__Q33i_L1:
    lbz r0, 0x8(r28)
    lhz r3, 0xb0(r30)
    cmpwi r0, 0x0
    cntlzw r0, r3
    srwi r29, r0, 5
    beq stt_add_code_input__Q33i_L4
    lwz r0, 0x84(r30)
    cmpwi r0, 0x1
    bne stt_add_code_input__Q33i_L2
    lwz r4, 0xc(r28)
    addi r3, r30, 0xb0
    bl setWiiNo__Q43ipl5scene11AddressEdit6StringFPCw
    b stt_add_code_input__Q33i_L3
stt_add_code_input__Q33i_L2:
    lwz r4, 0xc(r28)
    addi r3, r30, 0xb0
    bl setEMail__Q43ipl5scene11AddressEdit6StringFPCw
stt_add_code_input__Q33i_L3:
    lwz r3, 0x74(r30)
    lis r4, lbl_8164810B@ha
    addi r4, r4, lbl_8164810B@l
    li r5, 0x1
    lwz r3, 0x14(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    mr r4, r3
    mr r3, r30
    addi r5, r30, 0x2cc
    bl set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw
stt_add_code_input__Q33i_L4:
    lhz r0, 0xb0(r30)
    cmpwi r0, 0x0
    bne stt_add_code_input__Q33i_L6
    cmpwi r29, 0x0
    bne stt_add_code_input__Q33i_L5
    lwz r3, 0x74(r30)
    li r4, 0x6
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    li r29, 0x1
    li r4, 0x3
    stw r29, 0x14(r28)
    lwz r3, 0x74(r30)
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    stw r29, 0x14(r28)
stt_add_code_input__Q33i_L5:
    mr r3, r31
    li r4, 0xb
    bl reserveAnm__Q33ipl5scene6ButtonFi
    b stt_add_code_input__Q33i_L19
stt_add_code_input__Q33i_L6:
    cmpwi r29, 0x0
    beq stt_add_code_input__Q33i_L7
    lwz r3, 0x74(r30)
    li r4, 0x2
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    li r29, 0x1
    li r4, 0x7
    stw r29, 0x14(r28)
    lwz r3, 0x74(r30)
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    stw r29, 0x14(r28)
stt_add_code_input__Q33i_L7:
    lbz r0, 0x4d0(r30)
    cmpwi r0, 0x0
    beq stt_add_code_input__Q33i_L8
    addi r3, r30, 0xb0
    bl isDupCode__Q43ipl5scene11AddressEdit6StringCFv
    cmpwi r3, 0x0
    bne stt_add_code_input__Q33i_L8
    addi r3, r30, 0xb0
    bl isMyCode__Q43ipl5scene11AddressEdit6StringCFv
    cmpwi r3, 0x0
    bne stt_add_code_input__Q33i_L8
    mr r3, r31
    li r4, 0x1
    li r5, 0x2e
    bl reserveText__Q33ipl5scene6ButtonFiUl
    mr r3, r31
    li r4, 0xf
    bl reserveAnm__Q33ipl5scene6ButtonFi
    b stt_add_code_input__Q33i_L19
stt_add_code_input__Q33i_L8:
    mr r3, r31
    li r4, 0xb
    bl reserveAnm__Q33ipl5scene6ButtonFi
    b stt_add_code_input__Q33i_L19
stt_add_code_input__Q33i_L9:
    lbz r0, 0x8(r28)
    cmpwi r0, 0x0
    beq stt_add_code_input__Q33i_L17
    lhz r0, 0xb0(r30)
    cmpwi r0, 0x0
    beq stt_add_code_input__Q33i_L16
    lwz r0, 0x84(r30)
    cmpwi r0, 0x1
    bne stt_add_code_input__Q33i_L13
    addi r3, r30, 0xb0
    bl isMyCode__Q43ipl5scene11AddressEdit6StringCFv
    cmpwi r3, 0x0
    beq stt_add_code_input__Q33i_L10
    lwz r3, 0xac(r29)
    li r4, 0x56
    li r5, 0x2e
    bl callBtn1__Q23ipl12DialogWindowFUlUl
    li r0, 0x16
    stw r0, 0x64(r30)
    b stt_add_code_input__Q33i_L19
stt_add_code_input__Q33i_L10:
    addi r3, r30, 0xb0
    bl isDupCode__Q43ipl5scene11AddressEdit6StringCFv
    cmpwi r3, 0x0
    beq stt_add_code_input__Q33i_L11
    lwz r3, 0xac(r29)
    li r4, 0x52
    li r5, 0x2e
    bl callBtn1__Q23ipl12DialogWindowFUlUl
    li r0, 0x14
    stw r0, 0x64(r30)
    b stt_add_code_input__Q33i_L19
stt_add_code_input__Q33i_L11:
    lbz r0, 0x4d0(r30)
    cmpwi r0, 0x0
    bne stt_add_code_input__Q33i_L12
    lwz r3, 0xac(r29)
    li r4, 0x54
    li r5, 0x2e
    bl callBtn1__Q23ipl12DialogWindowFUlUl
    li r0, 0x13
    stw r0, 0x64(r30)
    b stt_add_code_input__Q33i_L19
stt_add_code_input__Q33i_L12:
    li r0, 0x11
    stw r0, 0x64(r30)
    b stt_add_code_input__Q33i_L19
stt_add_code_input__Q33i_L13:
    addi r3, r30, 0xb0
    bl isDupCode__Q43ipl5scene11AddressEdit6StringCFv
    cmpwi r3, 0x0
    beq stt_add_code_input__Q33i_L14
    lwz r3, 0xac(r29)
    li r4, 0x53
    li r5, 0x2e
    bl callBtn1__Q23ipl12DialogWindowFUlUl
    li r0, 0x15
    stw r0, 0x64(r30)
    b stt_add_code_input__Q33i_L19
stt_add_code_input__Q33i_L14:
    lbz r0, 0x4d0(r30)
    cmpwi r0, 0x0
    bne stt_add_code_input__Q33i_L15
    lwz r3, 0xac(r29)
    li r4, 0x1be
    li r5, 0x2e
    bl callBtn1__Q23ipl12DialogWindowFUlUl
    li r0, 0x13
    stw r0, 0x64(r30)
    b stt_add_code_input__Q33i_L19
stt_add_code_input__Q33i_L15:
    li r0, 0x11
    stw r0, 0x64(r30)
    b stt_add_code_input__Q33i_L19
stt_add_code_input__Q33i_L16:
    li r0, 0x11
    stw r0, 0x64(r30)
    b stt_add_code_input__Q33i_L19
stt_add_code_input__Q33i_L17:
    li r0, 0x11
    stw r0, 0x64(r30)
    b stt_add_code_input__Q33i_L19
stt_add_code_input__Q33i_L18:
    lwz r0, 0x84(r30)
    cmpwi r0, 0x1
    beq stt_add_code_input__Q33i_L19
    lwz r3, 0x90(r29)
    lwz r3, 0x4(r3)
    bl isVacancy__Q29textinput7ManagerCFv
    mr r5, r3
    mr r3, r30
    li r4, 0x0
    bl setDefaultTitleText__Q33ipl5scene11AddressEditFPCwb
stt_add_code_input__Q33i_L19:
    addi r11, r1, 0x20
    bl _restgpr_28
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void stt_msg_code_invalid__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0x5
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    lis r31, smArg__Q23ipl6System@ha
    addi r31, r31, smArg__Q23ipl6System@l
    stw r30, 0x8(r1)
    mr r30, r3
    lwz r3, 0x64(r31)
    bl getScene__Q33ipl5scene7ManagerFi
    lwz r3, 0xac(r31)
    lwz r0, 0x24(r3)
    cmpwi r0, 0x1
    beq stt_msg_code_invalid__Q3_L0
    b stt_msg_code_invalid__Q3_L1
stt_msg_code_invalid__Q3_L0:
    li r0, 0x11
    stw r0, 0x64(r30)
stt_msg_code_invalid__Q3_L1:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_msg_dup_wii_no__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0x5
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    lis r31, smArg__Q23ipl6System@ha
    addi r31, r31, smArg__Q23ipl6System@l
    stw r30, 0x8(r1)
    mr r30, r3
    lwz r3, 0x64(r31)
    bl getScene__Q33ipl5scene7ManagerFi
    lwz r3, 0xac(r31)
    lwz r0, 0x24(r3)
    cmpwi r0, 0x1
    beq stt_msg_dup_wii_no__Q33i_L0
    b stt_msg_dup_wii_no__Q33i_L1
stt_msg_dup_wii_no__Q33i_L0:
    li r0, 0x11
    stw r0, 0x64(r30)
stt_msg_dup_wii_no__Q33i_L1:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_msg_dup_email__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0x5
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    lis r31, smArg__Q23ipl6System@ha
    addi r31, r31, smArg__Q23ipl6System@l
    stw r30, 0x8(r1)
    mr r30, r3
    lwz r3, 0x64(r31)
    bl getScene__Q33ipl5scene7ManagerFi
    lwz r3, 0xac(r31)
    lwz r0, 0x24(r3)
    cmpwi r0, 0x1
    beq stt_msg_dup_email__Q33ip_L0
    b stt_msg_dup_email__Q33ip_L1
stt_msg_dup_email__Q33ip_L0:
    li r0, 0x11
    stw r0, 0x64(r30)
stt_msg_dup_email__Q33ip_L1:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_msg_my_wii_no__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0x5
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    lis r31, smArg__Q23ipl6System@ha
    addi r31, r31, smArg__Q23ipl6System@l
    stw r30, 0x8(r1)
    mr r30, r3
    lwz r3, 0x64(r31)
    bl getScene__Q33ipl5scene7ManagerFi
    lwz r3, 0xac(r31)
    lwz r0, 0x24(r3)
    cmpwi r0, 0x1
    beq stt_msg_my_wii_no__Q33ip_L0
    b stt_msg_my_wii_no__Q33ip_L1
stt_msg_my_wii_no__Q33ip_L0:
    li r0, 0x11
    stw r0, 0x64(r30)
stt_msg_my_wii_no__Q33ip_L1:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_add_code_fadeout__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_28
    lwz r5, 0x74(r3)
    lis r29, lbl_81647EE0@ha
    mr r31, r3
    li r4, 0x5
    addi r29, r29, lbl_81647EE0@l
    addi r3, r5, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_add_code_fadeout__Q3_L2
    lwz r3, 0x74(r31)
    li r4, 0x6
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_add_code_fadeout__Q3_L2
    lwz r3, 0x74(r31)
    addi r4, r29, 0x3ef
    li r5, 0x1
    lwz r3, 0x14(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    lis r30, smArg__Q23ipl6System@ha
    mr r28, r3
    addi r30, r30, smArg__Q23ipl6System@l
    li r4, 0x32
    lwz r3, 0x80(r30)
    lwz r3, 0x0(r3)
    bl getMessage__Q33ipl7message7MessageCFUl
    mr r5, r3
    mr r3, r31
    mr r4, r28
    bl set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw
    lwz r3, 0x74(r31)
    addi r4, r29, 0x3fd
    li r5, 0x1
    lwz r3, 0x14(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    lwz r5, 0x80(r30)
    mr r28, r3
    li r4, 0x49
    lwz r3, 0x0(r5)
    bl getMessage__Q33ipl7message7MessageCFUl
    mr r5, r3
    mr r3, r31
    mr r4, r28
    bl set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw
    lwz r3, 0x74(r31)
    addi r4, r29, 0x22b
    li r5, 0x1
    lwz r3, 0x14(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    mr r4, r3
    mr r3, r31
    addi r5, r31, 0x2b4
    bl set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw
    lwz r3, 0x74(r31)
    li r4, 0x1
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    li r30, 0x1
    stw r30, 0x14(r28)
    lhz r0, 0x2b4(r31)
    cmpwi r0, 0x0
    beq stt_add_code_fadeout__Q3_L0
    lwz r3, 0x74(r31)
    li r4, 0x2
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    stw r30, 0x14(r28)
    b stt_add_code_fadeout__Q3_L1
stt_add_code_fadeout__Q3_L0:
    lwz r3, 0x74(r31)
    li r4, 0x3
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    stw r30, 0x14(r28)
stt_add_code_fadeout__Q3_L1:
    lis r3, smArg__Q23ipl6System@ha
    addi r3, r3, smArg__Q23ipl6System@l
    lwz r3, 0x90(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    li r0, 0x18
    stw r0, 0x64(r31)
stt_add_code_fadeout__Q3_L2:
    addi r11, r1, 0x20
    bl _restgpr_28
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void stt_add_name_fadein__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0x1
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r5, 0x74(r3)
    addi r3, r5, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_add_name_fadein__Q33_L0
    lwz r3, 0x74(r31)
    li r4, 0x3
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_add_name_fadein__Q33_L0
    lwz r3, 0x74(r31)
    li r4, 0x2
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_add_name_fadein__Q33_L0
    li r0, 0x19
    stw r0, 0x64(r31)
stt_add_name_fadein__Q33_L0:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_add_name_normal__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r5, smArg__Q23ipl6System@ha
    li r4, 0x5
    stw r0, 0x14(r1)
    addi r5, r5, smArg__Q23ipl6System@l
    stw r31, 0xc(r1)
    stw r30, 0x8(r1)
    mr r30, r3
    lwz r3, 0x64(r5)
    bl getScene__Q33ipl5scene7ManagerFi
    mr r31, r3
    bl isActive__Q33ipl5scene6ButtonCFv
    cmpwi r3, 0x0
    beq stt_add_name_normal__Q33_L0
    mr r3, r31
    bl update__Q33ipl5scene6ButtonFv
stt_add_name_normal__Q33_L0:
    lwz r0, 0x64(r30)
    cmpwi r0, 0x19
    bne stt_add_name_normal__Q33_L1
    lwz r3, 0x7c(r30)
    bl update__Q33ipl3gui11PaneManagerFv
stt_add_name_normal__Q33_L1:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_add_name_input__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_28
    lis r29, smArg__Q23ipl6System@ha
    mr r30, r3
    addi r29, r29, smArg__Q23ipl6System@l
    lwz r3, 0x90(r29)
    lwz r12, 0x0(r3)
    lwz r12, 0x34(r12)
    mtctr r12
    bctrl
    mr r28, r3
    lwz r3, 0x64(r29)
    li r4, 0x5
    bl getScene__Q33ipl5scene7ManagerFi
    lwz r0, 0x4(r28)
    mr r31, r3
    cmpwi r0, 0x3
    beq stt_add_name_input__Q33i_L1
    bge stt_add_name_input__Q33i_L0
    cmpwi r0, 0x2
    bge stt_add_name_input__Q33i_L9
    cmpwi r0, 0x0
    bge stt_add_name_input__Q33i_L8
    b stt_add_name_input__Q33i_L9
stt_add_name_input__Q33i_L0:
    cmpwi r0, 0x5
    bge stt_add_name_input__Q33i_L9
    b stt_add_name_input__Q33i_L7
stt_add_name_input__Q33i_L1:
    lbz r0, 0x8(r28)
    lhz r3, 0x2b4(r30)
    cmpwi r0, 0x0
    cntlzw r0, r3
    srwi r29, r0, 5
    beq stt_add_name_input__Q33i_L2
    lwz r4, 0xc(r28)
    addi r3, r30, 0xb0
    bl setName__Q43ipl5scene11AddressEdit6StringFPCw
    lwz r3, 0x74(r30)
    lis r4, lbl_8164810B@ha
    addi r4, r4, lbl_8164810B@l
    li r5, 0x1
    lwz r3, 0x14(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    mr r4, r3
    mr r3, r30
    addi r5, r30, 0x2b4
    bl set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw
stt_add_name_input__Q33i_L2:
    lhz r0, 0x2b4(r30)
    cmpwi r0, 0x0
    bne stt_add_name_input__Q33i_L4
    cmpwi r29, 0x0
    bne stt_add_name_input__Q33i_L3
    lwz r3, 0x74(r30)
    li r4, 0x6
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    li r29, 0x1
    li r4, 0x3
    stw r29, 0x14(r28)
    lwz r3, 0x74(r30)
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    stw r29, 0x14(r28)
stt_add_name_input__Q33i_L3:
    mr r3, r31
    li r4, 0xb
    bl reserveAnm__Q33ipl5scene6ButtonFi
    b stt_add_name_input__Q33i_L9
stt_add_name_input__Q33i_L4:
    cmpwi r29, 0x0
    beq stt_add_name_input__Q33i_L5
    lwz r3, 0x74(r30)
    li r4, 0x2
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    li r29, 0x1
    li r4, 0x7
    stw r29, 0x14(r28)
    lwz r3, 0x74(r30)
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    stw r29, 0x14(r28)
stt_add_name_input__Q33i_L5:
    lbz r0, 0x4d1(r30)
    cmpwi r0, 0x0
    beq stt_add_name_input__Q33i_L6
    mr r3, r31
    li r4, 0x1
    li r5, 0x2e
    bl reserveText__Q33ipl5scene6ButtonFiUl
    mr r3, r31
    li r4, 0xf
    bl reserveAnm__Q33ipl5scene6ButtonFi
    b stt_add_name_input__Q33i_L9
stt_add_name_input__Q33i_L6:
    mr r3, r31
    li r4, 0xb
    bl reserveAnm__Q33ipl5scene6ButtonFi
    b stt_add_name_input__Q33i_L9
stt_add_name_input__Q33i_L7:
    li r0, 0x19
    stw r0, 0x64(r30)
    bl getRegion__Q23ipl6SystemFv
    cmplwi r3, 0x6
    bne stt_add_name_input__Q33i_L9
    lwz r3, 0x90(r29)
    li r4, 0x0
    lwz r3, 0x4(r3)
    bl enableKSXFilter__Q29textinput7ManagerFb
    b stt_add_name_input__Q33i_L9
stt_add_name_input__Q33i_L8:
    lwz r3, 0x90(r29)
    lwz r3, 0x4(r3)
    bl isVacancy__Q29textinput7ManagerCFv
    mr r5, r3
    mr r3, r30
    li r4, 0x0
    bl setDefaultTitleText__Q33ipl5scene11AddressEditFPCwb
stt_add_name_input__Q33i_L9:
    addi r11, r1, 0x20
    bl _restgpr_28
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void stt_add_name_fadeout__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_28
    lwz r5, 0x74(r3)
    lis r31, lbl_81647EE0@ha
    mr r30, r3
    li r4, 0x5
    addi r31, r31, lbl_81647EE0@l
    addi r3, r5, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_add_name_fadeout__Q3_L6
    lwz r3, 0x74(r30)
    li r4, 0x7
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_add_name_fadeout__Q3_L6
    lwz r3, 0x74(r30)
    li r4, 0x6
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_add_name_fadeout__Q3_L6
    lwz r3, 0x74(r30)
    li r4, 0x9
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_add_name_fadeout__Q3_L6
    lwz r0, 0x8c(r30)
    cmpwi r0, 0x6
    beq stt_add_name_fadeout__Q3_L6
    bge stt_add_name_fadeout__Q3_L0
    cmpwi r0, 0x5
    bge stt_add_name_fadeout__Q3_L1
    b stt_add_name_fadeout__Q3_L6
stt_add_name_fadeout__Q3_L0:
    cmpwi r0, 0x8
    bge stt_add_name_fadeout__Q3_L6
    b stt_add_name_fadeout__Q3_L5
stt_add_name_fadeout__Q3_L1:
    lwz r3, 0x74(r30)
    li r4, 0x1
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    li r29, 0x1
    li r4, 0x2
    stw r29, 0x14(r28)
    lwz r3, 0x74(r30)
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    stw r29, 0x14(r28)
    lwz r0, 0x84(r30)
    cmpwi r0, 0x2
    beq stt_add_name_fadeout__Q3_L3
    bge stt_add_name_fadeout__Q3_L4
    cmpwi r0, 0x1
    bge stt_add_name_fadeout__Q3_L2
    b stt_add_name_fadeout__Q3_L4
stt_add_name_fadeout__Q3_L2:
    lwz r3, 0x74(r30)
    addi r4, r31, 0x3ef
    li r5, 0x1
    lwz r3, 0x14(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    lis r29, smArg__Q23ipl6System@ha
    mr r28, r3
    addi r29, r29, smArg__Q23ipl6System@l
    li r4, 0x31
    lwz r3, 0x80(r29)
    lwz r3, 0x0(r3)
    bl getMessage__Q33ipl7message7MessageCFUl
    mr r5, r3
    mr r3, r30
    mr r4, r28
    bl set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw
    lwz r3, 0x74(r30)
    addi r4, r31, 0x3fd
    li r5, 0x1
    lwz r3, 0x14(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    lwz r5, 0x80(r29)
    mr r28, r3
    li r4, 0x47
    lwz r3, 0x0(r5)
    bl getMessage__Q33ipl7message7MessageCFUl
    mr r5, r3
    mr r3, r30
    mr r4, r28
    bl set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw
    b stt_add_name_fadeout__Q3_L4
stt_add_name_fadeout__Q3_L3:
    lwz r3, 0x74(r30)
    addi r4, r31, 0x3ef
    li r5, 0x1
    lwz r3, 0x14(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    lis r29, smArg__Q23ipl6System@ha
    mr r28, r3
    addi r29, r29, smArg__Q23ipl6System@l
    li r4, 0x3f
    lwz r3, 0x80(r29)
    lwz r3, 0x0(r3)
    bl getMessage__Q33ipl7message7MessageCFUl
    mr r5, r3
    mr r3, r30
    mr r4, r28
    bl set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw
    lwz r3, 0x74(r30)
    addi r4, r31, 0x3fd
    li r5, 0x1
    lwz r3, 0x14(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    lwz r5, 0x80(r29)
    mr r28, r3
    li r4, 0x48
    lwz r3, 0x0(r5)
    bl getMessage__Q33ipl7message7MessageCFUl
    mr r5, r3
    mr r3, r30
    mr r4, r28
    bl set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw
stt_add_name_fadeout__Q3_L4:
    lwz r3, 0x74(r30)
    addi r4, r31, 0x22b
    li r5, 0x1
    lwz r3, 0x14(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    mr r4, r3
    mr r3, r30
    addi r5, r30, 0x2cc
    bl set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw
    li r0, 0x10
    stw r0, 0x64(r30)
    b stt_add_name_fadeout__Q3_L6
stt_add_name_fadeout__Q3_L5:
    lwz r3, 0x74(r30)
    li r4, 0x1
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    li r29, 0x1
    li r4, 0x4
    stw r29, 0x14(r28)
    lwz r3, 0x74(r30)
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    stw r29, 0x14(r28)
    addi r4, r31, 0x3ef
    li r5, 0x1
    lwz r3, 0x74(r30)
    lwz r3, 0x14(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    lis r29, smArg__Q23ipl6System@ha
    mr r28, r3
    addi r29, r29, smArg__Q23ipl6System@l
    li r4, 0x55
    lwz r3, 0x80(r29)
    lwz r3, 0x0(r3)
    bl getMessage__Q33ipl7message7MessageCFUl
    mr r5, r3
    mr r3, r30
    mr r4, r28
    bl set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw
    lwz r3, 0x74(r30)
    addi r4, r31, 0x5a0
    li r5, 0x1
    lwz r3, 0x14(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    lwz r5, 0x80(r29)
    mr r28, r3
    li r4, 0x8b
    lwz r3, 0x0(r5)
    bl getMessage__Q33ipl7message7MessageCFUl
    mr r5, r3
    mr r3, r30
    mr r4, r28
    bl set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw
    li r0, 0x1c
    stw r0, 0x64(r30)
stt_add_name_fadeout__Q3_L6:
    addi r11, r1, 0x20
    bl _restgpr_28
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void stt_add_mii_fadein__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0x1
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r5, 0x74(r3)
    addi r3, r5, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_add_mii_fadein__Q33i_L0
    lwz r3, 0x74(r31)
    li r4, 0x4
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_add_mii_fadein__Q33i_L0
    lwz r3, 0x74(r31)
    li r4, 0x0
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_add_mii_fadein__Q33i_L0
    li r0, 0x1d
    stw r0, 0x64(r31)
stt_add_mii_fadein__Q33i_L0:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_add_mii_normal__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r5, smArg__Q23ipl6System@ha
    li r4, 0x5
    stw r0, 0x14(r1)
    addi r5, r5, smArg__Q23ipl6System@l
    stw r31, 0xc(r1)
    stw r30, 0x8(r1)
    mr r30, r3
    lwz r3, 0x64(r5)
    bl getScene__Q33ipl5scene7ManagerFi
    mr r31, r3
    bl isActive__Q33ipl5scene6ButtonCFv
    cmpwi r3, 0x0
    beq stt_add_mii_normal__Q33i_L0
    mr r3, r31
    bl update__Q33ipl5scene6ButtonFv
stt_add_mii_normal__Q33i_L0:
    lwz r0, 0x64(r30)
    cmpwi r0, 0x1d
    bne stt_add_mii_normal__Q33i_L1
    lwz r3, 0x7c(r30)
    bl update__Q33ipl3gui11PaneManagerFv
stt_add_mii_normal__Q33i_L1:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_add_mii_input__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    addi r11, r1, 0x60
    bl _savegpr_29
    lwz r12, 0x0(r3)
    mr r29, r3
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0x0
    beq stt_add_mii_input__Q33ip_L0
    lwz r12, 0x0(r29)
    mr r3, r29
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lwz r30, 0x23c(r3)
    cmpwi r30, 0x0
    blt stt_add_mii_input__Q33ip_L0
    lis r31, smArg__Q23ipl6System@ha
    clrlwi r4, r30, 16
    addi r31, r31, smArg__Q23ipl6System@l
    lwz r3, 0x70(r31)
    bl isAvalable__Q33ipl6nigaoe7ManagerFUs
    cmpwi r3, 0x0
    beq stt_add_mii_input__Q33ip_L0
    lwz r0, 0x4e8(r29)
    cmpwi r0, 0x0
    bne stt_add_mii_input__Q33ip_L0
    addi r3, r1, 0x8
    clrlwi r6, r30, 16
    li r4, 0x0
    li r5, 0x0
    bl RFLGetAdditionalInfo
    addi r3, r29, 0x4e0
    addi r4, r1, 0x34
    bl RFLiIsSameID
    cmpwi r3, 0x0
    bne stt_add_mii_input__Q33ip_L0
    addi r3, r29, 0x4e0
    addi r4, r1, 0x34
    li r5, 0x8
    bl memcpy
    lis r8, nigaoe_create_callback_add__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv@ha
    lwz r3, 0x70(r31)
    lwz r4, 0x28(r31)
    mr r7, r30
    mr r9, r29
    addi r8, r8, nigaoe_create_callback_add__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv@l
    li r5, 0x4c
    li r6, 0x4c
    bl create__Q33ipl6nigaoe7ManagerFPQ23EGG4HeapiiiPFPQ33ipl6nigaoe6ObjectPv_vPv
    li r0, 0x1
    lwz r3, 0x7c(r29)
    stw r0, 0x4e8(r29)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    lwz r3, 0xa8(r29)
    bl fadeoutForce__Q33ipl5scene11TextBalloonFv
stt_add_mii_input__Q33ip_L0:
    lwz r12, 0x0(r29)
    mr r3, r29
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0x0
    bne stt_add_mii_input__Q33ip_L2
    lis r3, smArg__Q23ipl6System@ha
    addi r3, r3, smArg__Q23ipl6System@l
    lwz r3, 0x64(r3)
    lwz r0, 0x104(r3)
    cmpwi r0, 0x0
    bne stt_add_mii_input__Q33ip_L2
    cmpwi r29, 0x0
    mr r30, r29
    beq stt_add_mii_input__Q33ip_L1
    addi r30, r29, 0x58
stt_add_mii_input__Q33ip_L1:
    li r4, 0x5
    bl getScene__Q33ipl5scene7ManagerFi
    mr r4, r30
    li r5, 0x0
    bl setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler
    li r3, 0x1d
    li r0, 0x0
    stw r3, 0x64(r29)
    stw r0, 0x4e8(r29)
stt_add_mii_input__Q33ip_L2:
    addi r11, r1, 0x60
    bl _restgpr_29
    lwz r0, 0x64(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}

extern "C" asm void stt_msg_no_mii_add__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0x5
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    lis r31, smArg__Q23ipl6System@ha
    addi r31, r31, smArg__Q23ipl6System@l
    stw r30, 0x8(r1)
    mr r30, r3
    lwz r3, 0x64(r31)
    bl getScene__Q33ipl5scene7ManagerFi
    lwz r3, 0xac(r31)
    lwz r0, 0x24(r3)
    cmpwi r0, 0x1
    beq stt_msg_no_mii_add__Q33i_L0
    b stt_msg_no_mii_add__Q33i_L1
stt_msg_no_mii_add__Q33i_L0:
    li r0, 0x1d
    stw r0, 0x64(r30)
stt_msg_no_mii_add__Q33i_L1:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_add_mii_fadeout__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_28
    lwz r5, 0x74(r3)
    lis r31, lbl_81647EE0@ha
    mr r30, r3
    li r4, 0x9
    addi r31, r31, lbl_81647EE0@l
    addi r3, r5, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_add_mii_fadeout__Q33_L3
    lwz r3, 0x74(r30)
    li r4, 0x5
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_add_mii_fadeout__Q33_L3
    lwz r3, 0x74(r30)
    li r4, 0x8
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_add_mii_fadeout__Q33_L3
    lwz r0, 0x8c(r30)
    cmpwi r0, 0x6
    beq stt_add_mii_fadeout__Q33_L3
    bge stt_add_mii_fadeout__Q33_L0
    cmpwi r0, 0x5
    bge stt_add_mii_fadeout__Q33_L1
    b stt_add_mii_fadeout__Q33_L3
stt_add_mii_fadeout__Q33_L0:
    cmpwi r0, 0x8
    bge stt_add_mii_fadeout__Q33_L3
    b stt_add_mii_fadeout__Q33_L2
stt_add_mii_fadeout__Q33_L1:
    lwz r3, 0x74(r30)
    li r4, 0x1
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    li r29, 0x1
    li r4, 0x2
    stw r29, 0x14(r28)
    lwz r3, 0x74(r30)
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    stw r29, 0x14(r28)
    addi r4, r31, 0x3ef
    li r5, 0x1
    lwz r3, 0x74(r30)
    lwz r3, 0x14(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    lis r29, smArg__Q23ipl6System@ha
    mr r28, r3
    addi r29, r29, smArg__Q23ipl6System@l
    li r4, 0x32
    lwz r3, 0x80(r29)
    lwz r3, 0x0(r3)
    bl getMessage__Q33ipl7message7MessageCFUl
    mr r5, r3
    mr r3, r30
    mr r4, r28
    bl set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw
    lwz r3, 0x74(r30)
    addi r4, r31, 0x22b
    li r5, 0x1
    lwz r3, 0x14(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    mr r4, r3
    mr r3, r30
    addi r5, r30, 0x2b4
    bl set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw
    lwz r3, 0x74(r30)
    addi r4, r31, 0x3fd
    li r5, 0x1
    lwz r3, 0x14(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    lwz r5, 0x80(r29)
    mr r28, r3
    li r4, 0x49
    lwz r3, 0x0(r5)
    bl getMessage__Q33ipl7message7MessageCFUl
    mr r5, r3
    mr r3, r30
    mr r4, r28
    bl set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw
    li r0, 0x18
    stw r0, 0x64(r30)
    b stt_add_mii_fadeout__Q33_L3
stt_add_mii_fadeout__Q33_L2:
    lwz r3, 0x68(r30)
    li r4, 0x0
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    li r29, 0x1
    li r4, 0x10
    stw r29, 0x14(r28)
    lwz r3, 0x68(r30)
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    bl initAnmFrame__Q33ipl6layout8AnimatorFv
    lwz r3, 0x68(r30)
    li r4, 0x11
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    bl initAnmFrame__Q33ipl6layout8AnimatorFv
    lwz r3, 0x68(r30)
    li r4, 0x12
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    bl initAnmFrame__Q33ipl6layout8AnimatorFv
    lwz r3, 0x68(r30)
    li r4, 0x1c
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    stw r29, 0x14(r28)
    addi r4, r31, 0x21d
    li r5, 0x1
    lwz r3, 0x68(r30)
    lwz r3, 0x14(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    lis r5, smArg__Q23ipl6System@ha
    mr r28, r3
    addi r5, r5, smArg__Q23ipl6System@l
    li r4, 0x44
    lwz r3, 0x80(r5)
    lwz r3, 0x0(r3)
    bl getMessage__Q33ipl7message7MessageCFUl
    mr r5, r3
    mr r3, r30
    mr r4, r28
    bl set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw
    lwz r3, 0x68(r30)
    addi r4, r31, 0x22b
    li r5, 0x1
    lwz r3, 0x14(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    mr r4, r3
    mr r3, r30
    addi r5, r30, 0x2b4
    bl set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw
    lwz r3, 0x68(r30)
    addi r4, r31, 0xf5
    li r5, 0x1
    lwz r3, 0x14(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    mr r4, r3
    mr r3, r30
    addi r5, r30, 0x2cc
    bl set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw
    li r0, 0x21
    stw r0, 0x64(r30)
stt_add_mii_fadeout__Q33_L3:
    addi r11, r1, 0x20
    bl _restgpr_28
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void stt_add_confirm_fadein__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0x0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r5, 0x68(r3)
    addi r3, r5, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_add_confirm_fadein___L0
    li r0, 0x22
    stw r0, 0x64(r31)
stt_add_confirm_fadein___L0:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_add_confirm_normal__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r5, smArg__Q23ipl6System@ha
    li r4, 0x5
    stw r0, 0x14(r1)
    addi r5, r5, smArg__Q23ipl6System@l
    stw r31, 0xc(r1)
    stw r30, 0x8(r1)
    mr r30, r3
    lwz r3, 0x64(r5)
    bl getScene__Q33ipl5scene7ManagerFi
    mr r31, r3
    bl isActive__Q33ipl5scene6ButtonCFv
    cmpwi r3, 0x0
    beq stt_add_confirm_normal___L0
    mr r3, r31
    bl update__Q33ipl5scene6ButtonFv
stt_add_confirm_normal___L0:
    lwz r0, 0x64(r30)
    cmpwi r0, 0x22
    bne stt_add_confirm_normal___L1
    lwz r3, 0x70(r30)
    bl update__Q33ipl3gui11PaneManagerFv
stt_add_confirm_normal___L1:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_add_confirm_fadeout__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_29
    lwz r5, 0x68(r3)
    mr r29, r3
    li r4, 0x1e
    addi r3, r5, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    beq stt_add_confirm_fadeout__L3
    lis r31, smArg__Q23ipl6System@ha
    li r4, 0x5
    addi r31, r31, smArg__Q23ipl6System@l
    lwz r3, 0x64(r31)
    bl getScene__Q33ipl5scene7ManagerFi
    lwz r0, 0x8c(r29)
    mr r30, r3
    cmpwi r0, 0x6
    beq stt_add_confirm_fadeout__L3
    bge stt_add_confirm_fadeout__L0
    cmpwi r0, 0x5
    bge stt_add_confirm_fadeout__L1
    b stt_add_confirm_fadeout__L3
stt_add_confirm_fadeout__L0:
    cmpwi r0, 0x8
    bge stt_add_confirm_fadeout__L3
    b stt_add_confirm_fadeout__L2
stt_add_confirm_fadeout__L1:
    lwz r3, 0x74(r29)
    li r4, 0x0
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r30, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    li r3, 0x1
    li r0, 0x1c
    stw r3, 0x14(r30)
    stw r0, 0x64(r29)
    b stt_add_confirm_fadeout__L3
stt_add_confirm_fadeout__L2:
    mr r3, r29
    bl add_friendinfo__Q33ipl5scene11AddressEditFv
    mr r3, r30
    li r4, 0x1
    li r5, 0x29
    bl reserveText__Q33ipl5scene6ButtonFiUl
    lwz r3, 0x64(r31)
    li r4, 0x14
    bl getScene__Q33ipl5scene7ManagerFi
    bl reset_friend__Q33ipl5scene7AddressFv
    lwz r3, 0xac(r31)
    li r4, 0x4a
    li r5, 0x2e
    bl callBtn1__Q23ipl12DialogWindowFUlUl
    li r0, 0x26
    stw r0, 0x64(r29)
stt_add_confirm_fadeout__L3:
    addi r11, r1, 0x20
    bl _restgpr_29
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void stt_wait_decide_anm_add__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_29
    mr r29, r3
    li r31, 0x1
    li r30, 0x0
stt_wait_decide_anm_add__L0:
    lwz r3, 0x88(r29)
    lwz r4, 0x68(r29)
    addi r0, r3, 0x6
    addi r3, r4, 0x28c
    clrlwi r4, r0, 16
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    lwz r3, 0x14(r3)
    addi r30, r30, 0x1
    cmpwi r30, 0x5
    subi r3, r3, 0x1
    subic r0, r3, 0x1
    subfe r0, r0, r3
    and r3, r31, r0
    subic r0, r3, 0x1
    subfe r31, r0, r3
    blt stt_wait_decide_anm_add__L0
    cmpwi r31, 0x0
    beq stt_wait_decide_anm_add__L2
    lwz r0, 0x88(r29)
    cmpwi r0, 0x4
    beq stt_wait_decide_anm_add__L1
    b stt_wait_decide_anm_add__L2
stt_wait_decide_anm_add__L1:
    lwz r3, 0x70(r29)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    lis r4, smArg__Q23ipl6System@ha
    addi r3, r29, 0xb0
    addi r4, r4, smArg__Q23ipl6System@l
    lwz r31, 0xac(r4)
    bl getDispCodeLong__Q43ipl5scene11AddressEdit6StringCFv
    mr r4, r3
    mr r3, r31
    li r5, 0x2e
    bl callBtn1__Q23ipl12DialogWindowFPCwUl
    li r0, 0x25
    stw r0, 0x64(r29)
stt_wait_decide_anm_add__L2:
    addi r11, r1, 0x20
    bl _restgpr_29
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

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

extern "C" asm void stt_msg_no_mii__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r4, smArg__Q23ipl6System@ha
    stw r0, 0x14(r1)
    addi r4, r4, smArg__Q23ipl6System@l
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r4, 0xac(r4)
    lwz r0, 0x24(r4)
    cmpwi r0, 0x1
    beq stt_msg_no_mii__Q33ipl5s_L0
    b stt_msg_no_mii__Q33ipl5s_L2
stt_msg_no_mii__Q33ipl5s_L0:
    lwz r3, 0x70(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    li r0, 0x5
    li r5, 0x0
    li r3, 0x0
    mtctr r0
stt_msg_no_mii__Q33ipl5s_L1:
    add r4, r31, r3
    addi r3, r3, 0x4
    stw r5, 0x90(r4)
    bdnz stt_msg_no_mii__Q33ipl5s_L1
    li r0, 0x0
    stw r0, 0x64(r31)
stt_msg_no_mii__Q33ipl5s_L2:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_select_mii__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    addi r11, r1, 0x60
    bl _savegpr_29
    lwz r12, 0x0(r3)
    mr r29, r3
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0x0
    beq stt_select_mii__Q33ipl5s_L0
    lwz r12, 0x0(r29)
    mr r3, r29
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lwz r30, 0x23c(r3)
    cmpwi r30, 0x0
    blt stt_select_mii__Q33ipl5s_L0
    lis r31, smArg__Q23ipl6System@ha
    clrlwi r4, r30, 16
    addi r31, r31, smArg__Q23ipl6System@l
    lwz r3, 0x70(r31)
    bl isAvalable__Q33ipl6nigaoe7ManagerFUs
    cmpwi r3, 0x0
    beq stt_select_mii__Q33ipl5s_L0
    lwz r0, 0x4e8(r29)
    cmpwi r0, 0x0
    bne stt_select_mii__Q33ipl5s_L0
    addi r3, r1, 0x8
    clrlwi r6, r30, 16
    li r4, 0x0
    li r5, 0x0
    bl RFLGetAdditionalInfo
    addi r3, r29, 0x4e0
    addi r4, r1, 0x34
    bl RFLiIsSameID
    cmpwi r3, 0x0
    bne stt_select_mii__Q33ipl5s_L0
    addi r3, r29, 0x4e0
    addi r4, r1, 0x34
    li r5, 0x8
    bl memcpy
    lis r8, nigaoe_create_callback_edit__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv@ha
    lwz r3, 0x70(r31)
    lwz r4, 0x28(r31)
    mr r7, r30
    mr r9, r29
    addi r8, r8, nigaoe_create_callback_edit__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv@l
    li r5, 0x4c
    li r6, 0x4c
    bl create__Q33ipl6nigaoe7ManagerFPQ23EGG4HeapiiiPFPQ33ipl6nigaoe6ObjectPv_vPv
    li r0, 0x1
    mr r3, r29
    stw r0, 0x4e8(r29)
    bl update_friendinfo__Q33ipl5scene11AddressEditFv
stt_select_mii__Q33ipl5s_L0:
    lwz r12, 0x0(r29)
    mr r3, r29
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0x0
    bne stt_select_mii__Q33ipl5s_L3
    lis r3, smArg__Q23ipl6System@ha
    addi r3, r3, smArg__Q23ipl6System@l
    lwz r3, 0x64(r3)
    lwz r0, 0x104(r3)
    cmpwi r0, 0x0
    bne stt_select_mii__Q33ipl5s_L3
    cmpwi r29, 0x0
    mr r30, r29
    beq stt_select_mii__Q33ipl5s_L1
    addi r30, r29, 0x58
stt_select_mii__Q33ipl5s_L1:
    li r4, 0x5
    bl getScene__Q33ipl5scene7ManagerFi
    mr r4, r30
    li r5, 0x0
    bl setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler
    li r31, 0x0
    lwz r3, 0x70(r29)
    stw r31, 0x64(r29)
    stw r31, 0x4e8(r29)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    li r0, 0x5
    mr r3, r31
    mtctr r0
stt_select_mii__Q33ipl5s_L2:
    add r4, r29, r3
    addi r3, r3, 0x4
    stw r31, 0x90(r4)
    bdnz stt_select_mii__Q33ipl5s_L2
stt_select_mii__Q33ipl5s_L3:
    addi r11, r1, 0x60
    bl _restgpr_29
    lwz r0, 0x64(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}

extern "C" asm void stt_msg_add_rlt__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0x5
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    lis r31, smArg__Q23ipl6System@ha
    addi r31, r31, smArg__Q23ipl6System@l
    stw r30, 0x8(r1)
    mr r30, r3
    lwz r3, 0x64(r31)
    bl getScene__Q33ipl5scene7ManagerFi
    lwz r4, 0xac(r31)
    lwz r0, 0x24(r4)
    cmpwi r0, 0x1
    beq stt_msg_add_rlt__Q33ipl5_L0
    b stt_msg_add_rlt__Q33ipl5_L1
stt_msg_add_rlt__Q33ipl5_L0:
    li r4, 0xf
    bl reserveAnm__Q33ipl5scene6ButtonFi
    li r0, 0x30
    stw r0, 0x64(r30)
stt_msg_add_rlt__Q33ipl5_L1:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_msg_net__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    stw r31, 0x5c(r1)
    lis r31, smArg__Q23ipl6System@ha
    addi r31, r31, smArg__Q23ipl6System@l
    stw r30, 0x58(r1)
    mr r30, r3
    lwz r4, 0xac(r31)
    lwz r0, 0x24(r4)
    cmpwi r0, 0x2
    beq stt_msg_net__Q33ipl5scen_L0
    bge stt_msg_net__Q33ipl5scen_L3
    cmpwi r0, 0x1
    bge stt_msg_net__Q33ipl5scen_L1
    b stt_msg_net__Q33ipl5scen_L3
stt_msg_net__Q33ipl5scen_L0:
    li r0, 0x0
    stw r0, 0x64(r3)
    b stt_msg_net__Q33ipl5scen_L3
stt_msg_net__Q33ipl5scen_L1:
    addi r3, r1, 0x8
    bl SCGetParentalControl
    cmpwi r3, 0x0
    beq stt_msg_net__Q33ipl5scen_L2
    lbz r0, 0x8(r1)
    rlwinm. r0, r0, 0, 24, 24
    beq stt_msg_net__Q33ipl5scen_L2
    lwz r3, 0x64(r31)
    li r4, 0x5
    bl getScene__Q33ipl5scene7ManagerFi
    li r4, 0x0
    li r5, 0x0
    bl setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler
    lwz r3, 0x64(r31)
    li r4, 0x5
    bl getScene__Q33ipl5scene7ManagerFi
    li r4, 0xc
    bl animation__Q33ipl5scene6ButtonFi
    mr r3, r30
    mr r5, r30
    li r4, 0x1b
    li r6, 0x0
    li r7, 0x1
    bl createChildScene__Q33ipl5scene4BaseFiPQ33ipl5scene4BasePQ33ipl5scene4BasePv
    li r3, 0x0
    li r0, 0x28
    stb r3, 0x4d8(r30)
    stw r0, 0x64(r30)
    b stt_msg_net__Q33ipl5scen_L3
stt_msg_net__Q33ipl5scen_L2:
    lis r3, smArg__Q23ipl6System@ha
    addi r3, r3, smArg__Q23ipl6System@l
    lwz r3, 0xc4(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    mr r3, r30
    li r4, 0x12
    li r5, 0x1
    bl reserveAllSceneDestruction__Q33ipl5scene4BaseFiPv
    li r0, 0x30
    stw r0, 0x64(r30)
stt_msg_net__Q33ipl5scen_L3:
    lwz r0, 0x64(r1)
    lwz r31, 0x5c(r1)
    lwz r30, 0x58(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}

extern "C" asm void stt_wait_parental__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r5, smArg__Q23ipl6System@ha
    li r4, 0x1b
    stw r0, 0x14(r1)
    addi r5, r5, smArg__Q23ipl6System@l
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r3, 0x64(r5)
    bl getScene__Q33ipl5scene7ManagerFi
    cmpwi r3, 0x0
    beq stt_wait_parental__Q33ip_L2
    lwz r0, 0x70(r3)
    cmpwi r0, 0x1
    beq stt_wait_parental__Q33ip_L0
    blt stt_wait_parental__Q33ip_L2
    cmpwi r0, 0x4
    bge stt_wait_parental__Q33ip_L2
    b stt_wait_parental__Q33ip_L1
stt_wait_parental__Q33ip_L0:
    li r3, 0x1
    li r0, 0x29
    stb r3, 0x4d8(r31)
    stw r0, 0x64(r31)
    b stt_wait_parental__Q33ip_L2
stt_wait_parental__Q33ip_L1:
    li r3, 0x0
    li r0, 0x29
    stb r3, 0x4d8(r31)
    stw r0, 0x64(r31)
stt_wait_parental__Q33ip_L2:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_wait_parental_dst__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    stw r30, 0x8(r1)
    mr r30, r3
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0x0
    bne stt_wait_parental_dst__Q_L2
    lbz r0, 0x4d8(r30)
    cmpwi r0, 0x0
    beq stt_wait_parental_dst__Q_L0
    lis r3, smArg__Q23ipl6System@ha
    addi r3, r3, smArg__Q23ipl6System@l
    lwz r3, 0xc4(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    mr r3, r30
    li r4, 0x12
    li r5, 0x1
    bl reserveAllSceneDestruction__Q33ipl5scene4BaseFiPv
    li r0, 0x30
    stw r0, 0x64(r30)
    b stt_wait_parental_dst__Q_L2
stt_wait_parental_dst__Q_L0:
    lis r3, smArg__Q23ipl6System@ha
    li r4, 0x5
    addi r3, r3, smArg__Q23ipl6System@l
    lwz r3, 0x64(r3)
    bl getScene__Q33ipl5scene7ManagerFi
    li r4, 0xb
    bl animation__Q33ipl5scene6ButtonFi
    cmpwi r30, 0x0
    mr r31, r30
    beq stt_wait_parental_dst__Q_L1
    addi r31, r30, 0x58
stt_wait_parental_dst__Q_L1:
    lis r3, smArg__Q23ipl6System@ha
    li r4, 0x5
    addi r3, r3, smArg__Q23ipl6System@l
    lwz r3, 0x64(r3)
    bl getScene__Q33ipl5scene7ManagerFi
    mr r4, r31
    li r5, 0x0
    bl setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler
    li r0, 0x0
    stw r0, 0x64(r30)
stt_wait_parental_dst__Q_L2:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_msg_wc__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    stw r31, 0x5c(r1)
    lis r31, smArg__Q23ipl6System@ha
    addi r31, r31, smArg__Q23ipl6System@l
    stw r30, 0x58(r1)
    mr r30, r3
    lwz r4, 0xac(r31)
    lwz r0, 0x24(r4)
    cmpwi r0, 0x2
    beq stt_msg_wc__Q33ipl5scene_L0
    bge stt_msg_wc__Q33ipl5scene_L3
    cmpwi r0, 0x1
    bge stt_msg_wc__Q33ipl5scene_L1
    b stt_msg_wc__Q33ipl5scene_L3
stt_msg_wc__Q33ipl5scene_L0:
    li r0, 0x0
    stw r0, 0x64(r3)
    b stt_msg_wc__Q33ipl5scene_L3
stt_msg_wc__Q33ipl5scene_L1:
    addi r3, r1, 0x8
    bl SCGetParentalControl
    cmpwi r3, 0x0
    beq stt_msg_wc__Q33ipl5scene_L2
    lbz r0, 0x8(r1)
    rlwinm. r0, r0, 0, 24, 24
    beq stt_msg_wc__Q33ipl5scene_L2
    lwz r3, 0x64(r31)
    li r4, 0x5
    bl getScene__Q33ipl5scene7ManagerFi
    li r4, 0x0
    li r5, 0x0
    bl setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler
    lwz r3, 0x64(r31)
    li r4, 0x5
    bl getScene__Q33ipl5scene7ManagerFi
    li r4, 0xc
    bl animation__Q33ipl5scene6ButtonFi
    mr r3, r30
    mr r5, r30
    li r4, 0x1b
    li r6, 0x0
    li r7, 0x1
    bl createChildScene__Q33ipl5scene4BaseFiPQ33ipl5scene4BasePQ33ipl5scene4BasePv
    li r3, 0x0
    li r0, 0x2b
    stb r3, 0x4d8(r30)
    stw r0, 0x64(r30)
    b stt_msg_wc__Q33ipl5scene_L3
stt_msg_wc__Q33ipl5scene_L2:
    lis r3, smArg__Q23ipl6System@ha
    addi r3, r3, smArg__Q23ipl6System@l
    lwz r3, 0xc4(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    mr r3, r30
    li r4, 0x12
    li r5, 0x4
    bl reserveAllSceneDestruction__Q33ipl5scene4BaseFiPv
    li r0, 0x30
    stw r0, 0x64(r30)
stt_msg_wc__Q33ipl5scene_L3:
    lwz r0, 0x64(r1)
    lwz r31, 0x5c(r1)
    lwz r30, 0x58(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}

extern "C" asm void stt_wait_parental_wc__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r5, smArg__Q23ipl6System@ha
    li r4, 0x1b
    stw r0, 0x14(r1)
    addi r5, r5, smArg__Q23ipl6System@l
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r3, 0x64(r5)
    bl getScene__Q33ipl5scene7ManagerFi
    cmpwi r3, 0x0
    beq stt_wait_parental_wc__Q3_L2
    lwz r0, 0x70(r3)
    cmpwi r0, 0x1
    beq stt_wait_parental_wc__Q3_L0
    blt stt_wait_parental_wc__Q3_L2
    cmpwi r0, 0x4
    bge stt_wait_parental_wc__Q3_L2
    b stt_wait_parental_wc__Q3_L1
stt_wait_parental_wc__Q3_L0:
    li r3, 0x1
    li r0, 0x2c
    stb r3, 0x4d8(r31)
    stw r0, 0x64(r31)
    b stt_wait_parental_wc__Q3_L2
stt_wait_parental_wc__Q3_L1:
    li r3, 0x0
    li r0, 0x2c
    stb r3, 0x4d8(r31)
    stw r0, 0x64(r31)
stt_wait_parental_wc__Q3_L2:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void stt_wait_parental_dst_wc__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    stw r30, 0x8(r1)
    mr r30, r3
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0x0
    bne stt_wait_parental_dst_wc_L2
    lbz r0, 0x4d8(r30)
    cmpwi r0, 0x0
    beq stt_wait_parental_dst_wc_L0
    lis r3, smArg__Q23ipl6System@ha
    addi r3, r3, smArg__Q23ipl6System@l
    lwz r3, 0xc4(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    mr r3, r30
    li r4, 0x12
    li r5, 0x4
    bl reserveAllSceneDestruction__Q33ipl5scene4BaseFiPv
    li r0, 0x30
    stw r0, 0x64(r30)
    b stt_wait_parental_dst_wc_L2
stt_wait_parental_dst_wc_L0:
    lis r3, smArg__Q23ipl6System@ha
    li r4, 0x5
    addi r3, r3, smArg__Q23ipl6System@l
    lwz r3, 0x64(r3)
    bl getScene__Q33ipl5scene7ManagerFi
    li r4, 0xb
    bl animation__Q33ipl5scene6ButtonFi
    cmpwi r30, 0x0
    mr r31, r30
    beq stt_wait_parental_dst_wc_L1
    addi r31, r30, 0x58
stt_wait_parental_dst_wc_L1:
    lis r3, smArg__Q23ipl6System@ha
    li r4, 0x5
    addi r3, r3, smArg__Q23ipl6System@l
    lwz r3, 0x64(r3)
    bl getScene__Q33ipl5scene7ManagerFi
    mr r4, r31
    li r5, 0x0
    bl setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler
    li r0, 0x0
    stw r0, 0x64(r30)
stt_wait_parental_dst_wc_L2:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
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

extern "C" asm void stt_msg_no_established__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r4, smArg__Q23ipl6System@ha
    stw r0, 0x14(r1)
    addi r4, r4, smArg__Q23ipl6System@l
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r4, 0xac(r4)
    lwz r0, 0x24(r4)
    cmpwi r0, 0x1
    beq stt_msg_no_established___L0
    b stt_msg_no_established___L1
stt_msg_no_established___L0:
    bl reset_gui__Q33ipl5scene11AddressEditFv
    li r0, 0x0
    stw r0, 0x64(r31)
stt_msg_no_established___L1:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

void ipl::scene::AddressEdit::set_textbox(nw4r::lyt::Pane* pane, const wchar_t* text) {
    nw4r::lyt::TextBox* textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(pane);
    textBox->SetString(text, 0);
}

extern "C" asm void nigaoe_create_callback_edit__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 0x8(r1)
    mr r30, r3
    lwz r0, 0x4dc(r4)
    cmpwi r0, 0x0
    beq nigaoe_create_callback_e_L0
    mr r3, r0
    li r4, 0x1
    bl __dt__Q33ipl6nigaoe6ObjectFv
nigaoe_create_callback_e_L0:
    stw r30, 0x4dc(r31)
    lis r4, lbl_81647FC9@ha
    lwz r3, 0x68(r31)
    addi r4, r4, lbl_81647FC9@l
    li r5, 0x1
    lwz r3, 0x14(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    lwz r12, 0x0(r3)
    lwz r12, 0x5c(r12)
    mtctr r12
    bctrl
    addi r5, r30, 0x18
    li r4, 0x0
    bl SetTexture__Q34nw4r3lyt8MaterialFUcRC9_GXTexObj
    li r0, 0x2
    mr r3, r30
    stw r0, 0x4e8(r31)
    bl getName__Q33ipl6nigaoe6ObjectCFv
    mr r4, r3
    lwz r3, 0xa8(r31)
    li r5, 0xa
    bl init__Q33ipl5scene11TextBalloonFPCwUl
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void getName__Q33ipl6nigaoe6ObjectCFv() {
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

extern "C" asm void nigaoe_create_callback_add__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_29
    lwz r0, 0x4dc(r4)
    mr r29, r3
    mr r30, r4
    cmpwi r0, 0x0
    beq nigaoe_create_callback_a_L0
    mr r3, r0
    li r4, 0x1
    bl __dt__Q33ipl6nigaoe6ObjectFv
nigaoe_create_callback_a_L0:
    stw r29, 0x4dc(r30)
    lis r31, lbl_81647FC9@ha
    lwz r3, 0x74(r30)
    addi r4, r31, lbl_81647FC9@l
    li r5, 0x1
    lwz r3, 0x14(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    lwz r12, 0x0(r3)
    lwz r12, 0x5c(r12)
    mtctr r12
    bctrl
    addi r5, r29, 0x18
    li r4, 0x0
    bl SetTexture__Q34nw4r3lyt8MaterialFUcRC9_GXTexObj
    lwz r3, 0x68(r30)
    addi r4, r31, lbl_81647FC9@l
    li r5, 0x1
    lwz r3, 0x14(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    lwz r12, 0x0(r3)
    lwz r12, 0x5c(r12)
    mtctr r12
    bctrl
    addi r5, r29, 0x18
    li r4, 0x0
    bl SetTexture__Q34nw4r3lyt8MaterialFUcRC9_GXTexObj
    li r0, 0x2
    mr r3, r29
    stw r0, 0x4e8(r30)
    bl getName__Q33ipl6nigaoe6ObjectCFv
    mr r4, r3
    lwz r3, 0xa8(r30)
    li r5, 0xa
    bl init__Q33ipl5scene11TextBalloonFPCwUl
    addi r11, r1, 0x20
    bl _restgpr_29
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

void ipl::scene::AddressEdit::start_point_event(const char* paneName, controller::Interface* con) {
    int buttonNo = get_button_no(paneName);
    u8* p = reinterpret_cast<u8*>(this);

    switch (*reinterpret_cast<s32*>(p + 0x64)) {
        case 0:
            switch (buttonNo) {
                case 4:
                    break;
                case 0:
                    if (*reinterpret_cast<u32*>(*reinterpret_cast<u8**>(p + 0x4EC)
                                                + *reinterpret_cast<u32*>(p + 0xA4) * 0x140 + 4)
                        != 2) {
                        break;
                    }
                    if (*reinterpret_cast<u32*>(p + 0x90 + buttonNo * 4) == 0) {
                        layout::Animator* anim = (*reinterpret_cast<layout::Object**>(p + 0x68))->getAnim(buttonNo + 1);
                        anim->initFrame();
                        *reinterpret_cast<int*>(reinterpret_cast<u8*>(anim) + 0x14) = 1;
                        snd::getSystem()->startSE("WIPL_SE_BT_TARGETTING");
                        con->rumble(1);
                    }
                    (*reinterpret_cast<u32*>(p + 0x90 + buttonNo * 4))++;
                    break;
                case 3:
                    if (*reinterpret_cast<u32*>(p + 0x90 + buttonNo * 4) == 0) {
                        nw4r::lyt::Pane* pane = (*reinterpret_cast<layout::Object**>(p + 0x68))
                                                    ->GetRootPane()
                                                    ->FindPaneByName(paneName, true);
                        math::VEC3 pos(0.0f, 0.0f, 0.0f);
                        PSMTXMultVec(pane->GetGlobalMtx(), pos, pos);
                        float t15 = 15.0f;
                        float t = 50.0f;
                        float h = 0.5f;
                        pos.x += t15;
                        pos.y += h * t;
                        (*reinterpret_cast<TextBalloon**>(p + 0xA8))->setPos(pos, false, 1);
                        (*reinterpret_cast<TextBalloon**>(p + 0xA8))->fadein();
                    }
                /* fallthrough */
                case 1:
                case 2:
                    if (*reinterpret_cast<u32*>(p + 0x90 + buttonNo * 4) == 0) {
                        layout::Animator* anim = (*reinterpret_cast<layout::Object**>(p + 0x68))->getAnim(buttonNo + 1);
                        anim->initFrame();
                        *reinterpret_cast<int*>(reinterpret_cast<u8*>(anim) + 0x14) = 1;
                        snd::getSystem()->startSE("WIPL_SE_BT_TARGETTING");
                        con->rumble(1);
                    }
                    (*reinterpret_cast<u32*>(p + 0x90 + buttonNo * 4))++;
                    break;
            }
            break;
        case 0x22:
            switch (buttonNo) {
                case 3:
                if (*reinterpret_cast<u32*>(p + 0x90 + buttonNo * 4) == 0) {
                    nw4r::lyt::Pane* pane = (*reinterpret_cast<layout::Object**>(p + 0x68))
                                                ->GetRootPane()
                                                ->FindPaneByName(paneName, true);
                    math::VEC3 pos(0.0f, 0.0f, 0.0f);
                    PSMTXMultVec(pane->GetGlobalMtx(), pos, pos);
                    float t15 = 15.0f;
                    float t = 50.0f;
                    float h = 0.5f;
                    pos.x += t15;
                    pos.y += h * t;
                    (*reinterpret_cast<TextBalloon**>(p + 0xA8))->setPos(pos, false, 1);
                    (*reinterpret_cast<TextBalloon**>(p + 0xA8))->fadein();
                }
                (*reinterpret_cast<u32*>(p + 0x90 + buttonNo * 4))++;
                break;
            }
    }
}

extern "C" asm void start_left_event__Q33ipl5scene11AddressEditFPCc() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_29
    mr r30, r3
    bl get_button_no__Q33ipl5scene11AddressEditFPCc
    lwz r0, 0x64(r30)
    mr r31, r3
    cmpwi r0, 0x22
    beq start_left_event__Q33ipl_L6
    bge start_left_event__Q33ipl_L9
    cmpwi r0, 0x0
    beq start_left_event__Q33ipl_L0
    b start_left_event__Q33ipl_L9
start_left_event__Q33ipl_L0:
    cmpwi r3, 0x3
    beq start_left_event__Q33ipl_L3
    bge start_left_event__Q33ipl_L9
    cmpwi r3, 0x0
    beq start_left_event__Q33ipl_L1
    bge start_left_event__Q33ipl_L4
    b start_left_event__Q33ipl_L9
    b start_left_event__Q33ipl_L9
start_left_event__Q33ipl_L1:
    lwz r0, 0xa4(r30)
    lwz r4, 0x4ec(r30)
    mulli r0, r0, 0x140
    add r4, r4, r0
    lwz r0, 0x4(r4)
    cmplwi r0, 0x2
    bne start_left_event__Q33ipl_L9
    slwi r0, r3, 2
    add r29, r30, r0
    lwz r0, 0x90(r29)
    cmpwi r0, 0x1
    bne start_left_event__Q33ipl_L2
    lwz r3, 0x68(r30)
    addi r0, r31, 0xb
    clrlwi r4, r0, 16
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r30, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    li r0, 0x1
    stw r0, 0x14(r30)
start_left_event__Q33ipl_L2:
    lwz r3, 0x90(r29)
    cmpwi r3, 0x0
    ble start_left_event__Q33ipl_L9
    subi r0, r3, 0x1
    stw r0, 0x90(r29)
    b start_left_event__Q33ipl_L9
start_left_event__Q33ipl_L3:
    slwi r0, r3, 2
    add r3, r30, r0
    lwz r0, 0x90(r3)
    cmpwi r0, 0x1
    bne start_left_event__Q33ipl_L4
    lwz r3, 0xa8(r30)
    bl fadeoutForce__Q33ipl5scene11TextBalloonFv
start_left_event__Q33ipl_L4:
    slwi r0, r31, 2
    add r29, r30, r0
    lwz r0, 0x90(r29)
    cmpwi r0, 0x1
    bne start_left_event__Q33ipl_L5
    lwz r3, 0x68(r30)
    addi r0, r31, 0xb
    clrlwi r4, r0, 16
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r30, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    li r0, 0x1
    stw r0, 0x14(r30)
start_left_event__Q33ipl_L5:
    lwz r3, 0x90(r29)
    cmpwi r3, 0x0
    ble start_left_event__Q33ipl_L9
    subi r0, r3, 0x1
    stw r0, 0x90(r29)
    b start_left_event__Q33ipl_L9
start_left_event__Q33ipl_L6:
    cmpwi r3, 0x3
    beq start_left_event__Q33ipl_L7
    b start_left_event__Q33ipl_L9
start_left_event__Q33ipl_L7:
    slwi r0, r3, 2
    add r31, r30, r0
    lwz r0, 0x90(r31)
    cmpwi r0, 0x1
    bne start_left_event__Q33ipl_L8
    lwz r3, 0xa8(r30)
    bl fadeoutForce__Q33ipl5scene11TextBalloonFv
start_left_event__Q33ipl_L8:
    lwz r3, 0x90(r31)
    subi r0, r3, 0x1
    stw r0, 0x90(r31)
start_left_event__Q33ipl_L9:
    addi r11, r1, 0x20
    bl _restgpr_29
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void start_trig_event__Q33ipl5scene11AddressEditFPCc() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_28
    mr r30, r3
    bl get_button_no__Q33ipl5scene11AddressEditFPCc
    lwz r0, 0x64(r30)
    mr r31, r3
    cmpwi r0, 0x22
    beq start_trig_event__Q33ipl_L4
    bge start_trig_event__Q33ipl_L7
    cmpwi r0, 0x0
    beq start_trig_event__Q33ipl_L0
    b start_trig_event__Q33ipl_L7
start_trig_event__Q33ipl_L0:
    cmpwi r3, 0x0
    beq start_trig_event__Q33ipl_L1
    blt start_trig_event__Q33ipl_L7
    cmpwi r3, 0x5
    bge start_trig_event__Q33ipl_L7
    b start_trig_event__Q33ipl_L3
start_trig_event__Q33ipl_L1:
    lwz r0, 0xa4(r30)
    lwz r3, 0x4ec(r30)
    mulli r0, r0, 0x140
    add r3, r3, r0
    lwz r0, 0x4(r3)
    cmplwi r0, 0x2
    bne start_trig_event__Q33ipl_L2
    mr r3, r30
    bl reset_gui__Q33ipl5scene11AddressEditFv
    lwz r3, 0x68(r30)
    addi r0, r31, 0x6
    clrlwi r4, r0, 16
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    li r29, 0x1
    lis r3, sSystem__Q23ipl3snd@ha
    stw r29, 0x14(r28)
    lis r4, lbl_816484A3@ha
    addi r3, r3, sSystem__Q23ipl3snd@l
    stw r31, 0x88(r30)
    addi r4, r4, lbl_816484A3@l
    bl startSE__Q33ipl3snd6SystemFPCc
    stw r29, 0x64(r30)
    b start_trig_event__Q33ipl_L7
start_trig_event__Q33ipl_L2:
    lis r3, smArg__Q23ipl6System@ha
    li r4, 0x57
    addi r3, r3, smArg__Q23ipl6System@l
    li r5, 0x2e
    lwz r3, 0xac(r3)
    bl callBtn1__Q23ipl12DialogWindowFUlUl
    lwz r3, 0xa8(r30)
    bl fadeoutForce__Q33ipl5scene11TextBalloonFv
    mr r3, r30
    bl reset_gui__Q33ipl5scene11AddressEditFv
    li r0, 0x2f
    stw r0, 0x64(r30)
    b start_trig_event__Q33ipl_L7
start_trig_event__Q33ipl_L3:
    lwz r3, 0x68(r30)
    addi r0, r31, 0x6
    clrlwi r4, r0, 16
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    li r29, 0x1
    lis r3, sSystem__Q23ipl3snd@ha
    stw r29, 0x14(r28)
    lis r4, lbl_816484A3@ha
    addi r3, r3, sSystem__Q23ipl3snd@l
    stw r31, 0x88(r30)
    addi r4, r4, lbl_816484A3@l
    bl startSE__Q33ipl3snd6SystemFPCc
    stw r29, 0x64(r30)
    b start_trig_event__Q33ipl_L7
start_trig_event__Q33ipl_L4:
    cmpwi r3, 0x4
    beq start_trig_event__Q33ipl_L5
    b start_trig_event__Q33ipl_L7
start_trig_event__Q33ipl_L5:
    lwz r3, 0xa8(r30)
    bl fadeoutForce__Q33ipl5scene11TextBalloonFv
    li r0, 0x5
    li r5, 0x0
    li r3, 0x0
    mtctr r0
start_trig_event__Q33ipl_L6:
    add r4, r30, r3
    addi r3, r3, 0x4
    stw r5, 0x90(r4)
    bdnz start_trig_event__Q33ipl_L6
    lwz r3, 0x68(r30)
    li r4, 0xa
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    li r0, 0x1
    lis r3, sSystem__Q23ipl3snd@ha
    stw r0, 0x14(r28)
    lis r4, lbl_816484A3@ha
    addi r3, r3, sSystem__Q23ipl3snd@l
    stw r31, 0x88(r30)
    addi r4, r4, lbl_816484A3@l
    bl startSE__Q33ipl3snd6SystemFPCc
    li r0, 0x24
    stw r0, 0x64(r30)
start_trig_event__Q33ipl_L7:
    addi r11, r1, 0x20
    bl _restgpr_28
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

void ipl::scene::AddressEdit::start_ipt_trig_event(const char* paneName, int chan) {
    u8* p = reinterpret_cast<u8*>(this);
    scene::Button* button = static_cast<scene::Button*>(System::getScene(SCENE_BUTTON));
    controller::Interface* con = System::getControllerManager()->getYoungController();
    if (con != NULL && chan == con->getChannel()) {
        bool ok = strcmp(lbl_816965E0, paneName) == 0;
        if (ok) {
        switch (*reinterpret_cast<s32*>(p + 0x64)) {
            case 0xD: {
                keyboard::Manager::KeyboardSetting setting(keyboard::Manager::NORMAL_BIGTEXT_WITHOUT_LINEFEED_WITH_SIGN,
                    reinterpret_cast<const wchar_t*>(p + 0x2B4), 0xA, 1);
                switch (System::getRegion()) {
                    case 0xB: {
                        void* sysDict = System::getKeyboard()->getZiSystemDic();
                        void* oemDict = System::getKeyboard()->getZiOemDic();
                        textinput::InputForm* form = System::getKeyboard()->baseMgr()->getInputForm();
                        form->setZiDictionary(oemDict, sysDict);
                        setting.type = keyboard::Manager::PREDICT_WITHOUT_LINEFEED;
                        break;
                    }
                    case 0x6: {
                        setting.type = keyboard::Manager::PREDICT_WITHOUT_LINEFEED;
                        System::getKeyboard()->baseMgr()->enableKSXFilter(true);
                        break;
                    }
                }
                System::getKeyboard()->start(chan, setting);
                setDefaultTitleText(reinterpret_cast<const wchar_t*>(p + 0x2B4), false);
                if (*reinterpret_cast<u8*>(p + 0x4D1) != 0) {
                    button->reserveAnm(0x10);
                } else {
                    button->reserveAnm(0xC);
                }
                button->reserveText(1, 0x2E);
                snd::getSystem()->startSE("WIPL_SE_DECIDE");
                *reinterpret_cast<u32*>(p + 0x64) = 0xE;
                break;
            }
            case 0x11: {
                if (*reinterpret_cast<s32*>(p + 0x84) == 1) {
                    keyboard::Manager::KeyboardSetting setting(keyboard::Manager::NUMERIC_WITH_SEPERATOR,
                        reinterpret_cast<const wchar_t*>(p + 0xB0), 0x10, 2);
                    System::getKeyboard()->start(chan, setting);
                } else {
                    keyboard::Manager::KeyboardSetting setting(keyboard::Manager::ONLY_QWERTY_WITHOUT_LINEFEED_AND_SIGN,
                        reinterpret_cast<const wchar_t*>(p + 0xB0), 0x63, 5);
                    System::getKeyboard()->start(chan, setting);
                    setDefaultTitleText(reinterpret_cast<const wchar_t*>(p + 0xB0), false);
                }
                if (*reinterpret_cast<u8*>(p + 0x4D0) != 0
                    && !reinterpret_cast<String*>(p + 0xB0)->isDupCode()
                    && !reinterpret_cast<String*>(p + 0xB0)->isMyCode()) {
                    button->reserveAnm(0x10);
                } else {
                    button->reserveAnm(0xC);
                }
                snd::getSystem()->startSE("WIPL_SE_DECIDE");
                *reinterpret_cast<u32*>(p + 0x64) = 0x12;
                break;
            }
            case 0x19: {
                keyboard::Manager::KeyboardSetting setting(keyboard::Manager::NORMAL_BIGTEXT_WITHOUT_LINEFEED_WITH_SIGN,
                    reinterpret_cast<const wchar_t*>(p + 0x2B4), 0xA, 1);
                switch (System::getRegion()) {
                    case 0xB: {
                        void* sysDict = System::getKeyboard()->getZiSystemDic();
                        void* oemDict = System::getKeyboard()->getZiOemDic();
                        textinput::InputForm* form = System::getKeyboard()->baseMgr()->getInputForm();
                        form->setZiDictionary(oemDict, sysDict);
                        setting.type = keyboard::Manager::PREDICT_WITHOUT_LINEFEED;
                        break;
                    }
                    case 0x6: {
                        setting.type = keyboard::Manager::PREDICT_WITHOUT_LINEFEED;
                        System::getKeyboard()->baseMgr()->enableKSXFilter(true);
                        break;
                    }
                }
                System::getKeyboard()->start(chan, setting);
                setDefaultTitleText(reinterpret_cast<const wchar_t*>(p + 0x2B4), false);
                if (*reinterpret_cast<u8*>(p + 0x4D1) != 0) {
                    button->reserveAnm(0x10);
                } else {
                    button->reserveAnm(0xC);
                }
                snd::getSystem()->startSE("WIPL_SE_DECIDE");
                *reinterpret_cast<u32*>(p + 0x64) = 0x1A;
                break;
            }
            case 0x1D: {
                if (*reinterpret_cast<s32*>(p + 0x4E8) == 1) {
                    break;
                }
                *reinterpret_cast<s32*>(p + 0x4E8) = 0;
                if (RFLGetAvailableOfficialDataNum() != 0) {
                    createChildScene(0x1C, this, NULL, reinterpret_cast<void*>(2));
                    button->reserveAnm(0x10);
                    button->reserveAnm(0xB);
                    snd::getSystem()->startSE("WIPL_SE_DECIDE");
                    *reinterpret_cast<u32*>(p + 0x64) = 0x1E;
                } else {
                    System::getDialog()->callBtn1(0x17C, 0x2E);
                    snd::getSystem()->startSE("WIPL_SE_DECIDE");
                    *reinterpret_cast<u32*>(p + 0x64) = 0x1F;
                }
                break;
            }
        }
        }
    }
}

ipl::keyboard::Manager::KeyboardSetting::KeyboardSetting(
    KeyboardType type_, const wchar_t* wcString_, u32 stringLimit_, u32 rowLimit_) {
    type = type_;
    wcString = wcString_;
    stringLimit = stringLimit_;
    rowLimit = rowLimit_;
}


void ipl::scene::AddressEdit::start_ipt_point_event(const char* paneName, int chan) {
    controller::Interface* con = System::getControllerManager()->getYoungController();
    if (con != NULL && chan == con->getChannel()) {
        switch (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(this) + 0x64)) {
        case 0x1D: {
        char iconName[0xC] = "mii_icon_00";
        if (strcmp(iconName, paneName) == 0) {
            nw4r::lyt::Pane* pane =
                (*reinterpret_cast<layout::Object**>(reinterpret_cast<u8*>(this) + 0x74))
                    ->GetRootPane()
                    ->FindPaneByName(paneName, true);
            math::VEC3 pos(0.0f, 0.0f, 0.0f);
            PSMTXMultVec(pane->GetGlobalMtx(), pos, pos);
            {
            float yoff = 50.0f;
            pos.y = pos.y + yoff;
            }
            (*reinterpret_cast<TextBalloon**>(reinterpret_cast<u8*>(this) + 0xA8))->setPos(pos, false, 0);
            (*reinterpret_cast<TextBalloon**>(reinterpret_cast<u8*>(this) + 0xA8))->fadein();
        break;
        }
        }
        }
    }
}

extern "C" const char lbl_8160F67F[0x11] = "mii_icon_00";

extern "C" asm void start_ipt_left_event__Q33ipl5scene11AddressEditFPCci() {
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    addi r11, r1, 0x30
    bl _savegpr_27
    lis r6, smArg__Q23ipl6System@ha
    mr r31, r3
    addi r6, r6, smArg__Q23ipl6System@l
    mr r28, r4
    lwz r3, 0x68(r6)
    mr r27, r5
    bl getYoungController__Q33ipl10controller7ManagerFv
    cmpwi r3, 0x0
    beq start_ipt_left_event__Q3_L1
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    cmpw r27, r3
    bne start_ipt_left_event__Q3_L1
    lwz r0, 0x64(r31)
    cmpwi r0, 0x1d
    beq start_ipt_left_event__Q3_L0
    b start_ipt_left_event__Q3_L1
start_ipt_left_event__Q3_L0:
    lis r27, lbl_8160F67F@ha
    mr r4, r28
    lbzu r28, lbl_8160F67F@l(r27)
    addi r3, r1, 0x8
    lbz r29, 0x1(r27)
    lbz r30, 0x2(r27)
    lbz r12, 0x3(r27)
    lbz r11, 0x4(r27)
    lbz r10, 0x5(r27)
    lbz r9, 0x6(r27)
    lbz r8, 0x7(r27)
    lbz r7, 0x8(r27)
    lbz r6, 0x9(r27)
    lbz r5, 0xa(r27)
    lbz r0, 0xb(r27)
    stb r28, 0x8(r1)
    stb r29, 0x9(r1)
    stb r30, 0xa(r1)
    stb r12, 0xb(r1)
    stb r11, 0xc(r1)
    stb r10, 0xd(r1)
    stb r9, 0xe(r1)
    stb r8, 0xf(r1)
    stb r7, 0x10(r1)
    stb r6, 0x11(r1)
    stb r5, 0x12(r1)
    stb r0, 0x13(r1)
    bl strcmp
    cmpwi r3, 0x0
    bne start_ipt_left_event__Q3_L1
    lwz r3, 0xa8(r31)
    bl fadeoutForce__Q33ipl5scene11TextBalloonFv
start_ipt_left_event__Q3_L1:
    addi r11, r1, 0x30
    bl _restgpr_27
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
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

extern "C" asm void reset_gui__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    addi r11, r1, 0x30
    bl _savegpr_25
    mr r25, r3
    lwz r3, 0x70(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    lwz r3, 0x7c(r25)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    li r26, 0x0
    li r31, 0x0
    mr r30, r26
    li r29, 0x1
reset_gui__Q33ipl5scene1_L0:
    add r27, r25, r31
    lwz r0, 0x90(r27)
    cmpwi r0, 0x0
    ble reset_gui__Q33ipl5scene1_L1
    lwz r3, 0x68(r25)
    addi r0, r26, 0xb
    clrlwi r4, r0, 16
    addi r3, r3, 0x28c
    bl List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs
    mr r28, r3
    bl initFrame__Q33ipl7utility15FrameControllerFv
    stw r29, 0x14(r28)
    stw r30, 0x90(r27)
reset_gui__Q33ipl5scene1_L1:
    addi r26, r26, 0x1
    addi r31, r31, 0x4
    cmpwi r26, 0x5
    blt reset_gui__Q33ipl5scene1_L0
    addi r11, r1, 0x30
    bl _restgpr_25
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

extern "C" asm void add_friendinfo__Q33ipl5scene11AddressEditFv() {
    nofralloc
    clrlwi r11, r1, 27
    mr r12, r1
    subfic r11, r11, -0x180
    stwux r1, r1, r11
    mflr r0
    li r4, 0x0
    li r5, 0x140
    stw r0, 0x4(r12)
    stw r31, -0x4(r12)
    stw r30, -0x8(r12)
    mr r30, r3
    addi r3, r1, 0x20
    bl memset
    lwz r0, 0x84(r30)
    cmpwi r0, 0x2
    beq add_friendinfo__Q33ipl5s_L1
    bge add_friendinfo__Q33ipl5s_L2
    cmpwi r0, 0x1
    bge add_friendinfo__Q33ipl5s_L0
    b add_friendinfo__Q33ipl5s_L2
add_friendinfo__Q33ipl5s_L0:
    li r0, 0x1
    addi r4, r30, 0x2b4
    stw r0, 0x20(r1)
    addi r3, r1, 0x28
    li r5, 0xa
    bl wcsncpy
    addi r3, r30, 0xb0
    bl utf16_wiiid__Q33ipl5scene11AddressEditFPCw
    stw r4, 0x64(r1)
    addi r4, r30, 0x4e0
    li r5, 0x8
    stw r3, 0x60(r1)
    addi r3, r1, 0x40
    bl memcpy
    b add_friendinfo__Q33ipl5s_L2
add_friendinfo__Q33ipl5s_L1:
    li r0, 0x2
    addi r4, r30, 0x2b4
    stw r0, 0x20(r1)
    addi r3, r1, 0x28
    li r5, 0xa
    bl wcsncpy
    addi r4, r30, 0xb0
    addi r3, r1, 0x60
    li r5, 0x100
    bl UTF16ToANSI__Q33ipl7utility13CharacterCodeFPUcPCwl
    addi r3, r1, 0x40
    addi r4, r30, 0x4e0
    li r5, 0x8
    bl memcpy
add_friendinfo__Q33ipl5s_L2:
    lis r3, smArg__Q23ipl6System@ha
    li r4, 0x14
    addi r3, r3, smArg__Q23ipl6System@l
    lwz r3, 0x64(r3)
    bl getScene__Q33ipl5scene7ManagerFi
    lwz r31, 0xc0(r3)
    cmplwi r31, 0x64
    blt add_friendinfo__Q33ipl5s_L4
    li r0, 0x64
    li r31, 0x0
    mtctr r0
add_friendinfo__Q33ipl5s_L3:
    lwz r0, 0x4ec(r30)
    add r3, r0, r31
    lbz r0, 0x7d00(r3)
    cmpwi r0, 0x0
    beq add_friendinfo__Q33ipl5s_L4
    addi r31, r31, 0x1
    bdnz add_friendinfo__Q33ipl5s_L3
add_friendinfo__Q33ipl5s_L4:
    lwz r3, 0x4ec(r30)
    mr r4, r31
    addi r5, r1, 0x20
    bl add__Q33ipl5scene15FriendListCacheFUlRC15NWC24FriendInfo
    lwz r0, 0x84(r30)
    cmpwi r0, 0x2
    bne add_friendinfo__Q33ipl5s_L5
    lwz r3, 0x4ec(r30)
    mr r4, r31
    bl sendRegisterMail__Q33ipl5scene15FriendListCacheFUl
add_friendinfo__Q33ipl5s_L5:
    lwz r10, 0x0(r1)
    lwz r0, 0x4(r10)
    lwz r31, -0x4(r10)
    lwz r30, -0x8(r10)
    mtlr r0
    mr r1, r10
    blr
}

extern "C" asm void get_friendinfo__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x420(r1)
    mflr r0
    stw r0, 0x424(r1)
    addi r11, r1, 0x420
    bl _savegpr_28
    lwz r0, 0xa4(r3)
    lis r30, sFriendInfo__Q23ipl5scene@ha
    lwz r4, 0x4ec(r3)
    mr r28, r3
    mulli r0, r0, 0x140
    addi r3, r30, sFriendInfo__Q23ipl5scene@l
    li r5, 0x140
    add r4, r4, r0
    bl memcpy
    addi r31, r30, sFriendInfo__Q23ipl5scene@l
    addi r3, r28, 0xb0
    addi r4, r31, 0x8
    bl setName__Q43ipl5scene11AddressEdit6StringFPCw
    lwz r3, 0x68(r28)
    lis r4, lbl_8164810B@ha
    addi r29, r28, 0x2b4
    li r5, 0x1
    lwz r3, 0x14(r3)
    addi r4, r4, lbl_8164810B@l
    lwz r12, 0x0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    mr r4, r3
    mr r3, r28
    mr r5, r29
    bl set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw
    lwz r0, sFriendInfo__Q23ipl5scene@l(r30)
    cmplwi r0, 0x1
    bne get_friendinfo__Q33ipl5s_L0
    addi r3, r1, 0x8
    li r4, 0x0
    li r5, 0x200
    bl memset
    lwz r3, 0x40(r31)
    addi r5, r1, 0x8
    lwz r4, 0x44(r31)
    bl wiiid_utf16__Q33ipl5scene11AddressEditFUxPw
    addi r3, r28, 0xb0
    addi r4, r1, 0x8
    bl setWiiNo__Q43ipl5scene11AddressEdit6StringFPCw
    b get_friendinfo__Q33ipl5s_L1
get_friendinfo__Q33ipl5s_L0:
    addi r3, r1, 0x208
    li r4, 0x0
    li r5, 0x204
    bl memset
    addi r3, r1, 0x208
    addi r4, r31, 0x40
    li r5, 0x102
    bl ANSIToUTF16__Q33ipl7utility13CharacterCodeFPwPCUcl
    addi r3, r28, 0xb0
    addi r4, r1, 0x208
    bl setEMail__Q43ipl5scene11AddressEdit6StringFPCw
get_friendinfo__Q33ipl5s_L1:
    lwz r3, 0x68(r28)
    lis r4, lbl_81647FD5@ha
    addi r29, r28, 0x2cc
    li r5, 0x1
    lwz r3, 0x14(r3)
    addi r4, r4, lbl_81647FD5@l
    lwz r12, 0x0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    mr r4, r3
    mr r3, r28
    mr r5, r29
    bl set_textbox__Q33ipl5scene11AddressEditFPQ34nw4r3lyt4PanePCw
    lis r4, sFriendInfo__Q23ipl5scene@ha
    addi r3, r28, 0x4e0
    addi r4, r4, sFriendInfo__Q23ipl5scene@l
    li r5, 0x8
    addi r4, r4, 0x20
    bl memcpy
    addi r11, r1, 0x420
    bl _restgpr_28
    lwz r0, 0x424(r1)
    mtlr r0
    addi r1, r1, 0x420
    blr
}

extern "C" asm void delete_friendinfo__Q33ipl5scene11AddressEditFv() {
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

extern "C" asm void update_friendinfo__Q33ipl5scene11AddressEditFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0x0
    li r5, 0x18
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    lis r31, sFriendInfo__Q23ipl5scene@ha
    addi r31, r31, sFriendInfo__Q23ipl5scene@l
    stw r30, 0x8(r1)
    mr r30, r3
    addi r3, r31, 0x8
    bl memset
    addi r4, r30, 0x2b4
    addi r3, r31, 0x8
    li r5, 0xa
    bl wcsncpy
    addi r3, r31, 0x20
    addi r4, r30, 0x4e0
    li r5, 0x8
    bl memcpy
    lwz r3, 0x4ec(r30)
    addi r5, r31, 0x8
    lwz r4, 0xa4(r30)
    lwz r7, 0x20(r31)
    lwz r8, 0x24(r31)
    bl update__Q33ipl5scene15FriendListCacheFUlPCwUx
    lis r3, smArg__Q23ipl6System@ha
    li r4, 0x14
    addi r3, r3, smArg__Q23ipl6System@l
    lwz r3, 0x64(r3)
    bl getScene__Q33ipl5scene7ManagerFi
    bl reset_friend__Q33ipl5scene7AddressFv
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
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

extern "C" asm void wiiid_utf16__Q33ipl5scene11AddressEditFUxPw() {
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

void ipl::scene::AddressEdit::setDefaultTitleText(const wchar_t* text, bool flag) {
    if (flag || (text != NULL && text[0] == 0)) {
        switch (*reinterpret_cast<u32*>(reinterpret_cast<u8*>(this) + 0x64)) {
            case 0xE:
            case 0x1A:
                System::getKeyboard()->baseMgr()->setTitleText(System::getMessage(0x15E));
                break;
            case 0x12:
                System::getKeyboard()->baseMgr()->setTitleText(System::getMessage(0x15D));
                break;
        }
    } else {
        System::getKeyboard()->baseMgr()->setTitleText(L"");
    }
}


void ipl::scene::AddressEdit::onEventDerived(u32 compId, u32 event, const controller::Interface* con) {
    u8* p = reinterpret_cast<u8*>(this);
    gui::PaneComponent* component = static_cast<gui::PaneComponent*>(mpManager->getComponent(compId));
    const char* paneName = component->getPane()->GetName();

    if (event == ::gui::EventHandler::ON_TRIG) {
        if (con != NULL && con->downTrg(controller::BTN_INTERACT)) {
            scene::Button* button = static_cast<scene::Button*>(System::getScene(SCENE_BUTTON));
            layout::Animator* anim;
            System::getScene(SCENE_ADDRESS);

            if (scene::Button::cmpButtonName(paneName, scene::Button::BTN_EXIT) == 0) {
                switch (*reinterpret_cast<u32*>(p + 0x64)) {
                    case 0x00:
                        button->reserveAnm(0x1B);
                        button->reserveAnm(0x0C);
                        button->reserveText(0, 0x23);
                        button->reserveText(1, 0x29);
                        button->reserveAnm(0x0F);
                        anim = (*reinterpret_cast<layout::Object**>(p + 0x68))->getAnim(0x1E);
                        anim->initFrame();
                        *reinterpret_cast<int*>(reinterpret_cast<u8*>(anim) + 0x14) = 1;
                        *reinterpret_cast<u32*>(p + 0x8C) = 5;
                        snd::getSystem()->startSE("WIPL_SE_CANCEL");
                        (*reinterpret_cast<TextBalloon**>(p + 0xA8))->fadeoutForce();
                        *reinterpret_cast<u32*>(p + 0x64) = 0x30;
                        break;
                    case 0x0D:
                        button->reserveAnm(0x1B);
                        if (*reinterpret_cast<u8*>(p + 0x4D1) != 0) {
                            button->reserveAnm(0x10);
                        } else {
                            button->reserveAnm(0x0C);
                        }
                        button->reserveAnm(0x0B);
                        anim = (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(9);
                        anim->initFrame();
                        *reinterpret_cast<int*>(reinterpret_cast<u8*>(anim) + 0x14) = 1;
                        anim = (*reinterpret_cast<layout::Object**>(p + 0x80))->getAnim(1);
                        anim->initFrame();
                        *reinterpret_cast<int*>(reinterpret_cast<u8*>(anim) + 0x14) = 1;
                        get_friendinfo();
                        snd::getSystem()->startSE("WIPL_SE_CANCEL");
                        *reinterpret_cast<u32*>(p + 0x64) = 0x0F;
                        break;
                    case 0x11:
                        reserveSceneChange(*reinterpret_cast<int*>(p + 0x34), NULL);
                        button->reserveAnm(0x1B);
                        if (*reinterpret_cast<u8*>(p + 0x4D0) != 0 &&
                            !reinterpret_cast<String*>(p + 0xB0)->isDupCode() &&
                            !reinterpret_cast<String*>(p + 0xB0)->isMyCode()) {
                            button->reserveAnm(0x10);
                        } else {
                            button->reserveAnm(0x0C);
                        }
                        if (*reinterpret_cast<u16*>(p + 0xB0) != 0) {
                            anim = (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(6);
                        } else {
                            anim = (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(7);
                        }
                        anim->initFrame();
                        *reinterpret_cast<int*>(reinterpret_cast<u8*>(anim) + 0x14) = 1;
                        button->reserveAnm(0x0B);
                        anim = (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(9);
                        anim->initFrame();
                        *reinterpret_cast<int*>(reinterpret_cast<u8*>(anim) + 0x14) = 1;
                        anim = (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(5);
                        anim->initFrame();
                        *reinterpret_cast<int*>(reinterpret_cast<u8*>(anim) + 0x14) = 1;
                        *reinterpret_cast<u32*>(p + 0x8C) = 5;
                        snd::getSystem()->startSE("WIPL_SE_CANCEL");
                        *reinterpret_cast<u32*>(p + 0x64) = 0x30;
                        break;
                    case 0x19:
                        button->reserveAnm(0x1B);
                        if (*reinterpret_cast<u8*>(p + 0x4D1) != 0) {
                            button->reserveAnm(0x10);
                            anim = (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(6);
                            anim->initFrame();
                            *reinterpret_cast<int*>(reinterpret_cast<u8*>(anim) + 0x14) = 1;
                        } else if (*reinterpret_cast<u16*>(p + 0x2B4) != 0) {
                            button->reserveAnm(0x0C);
                            anim = (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(6);
                            anim->initFrame();
                            *reinterpret_cast<int*>(reinterpret_cast<u8*>(anim) + 0x14) = 1;
                        } else {
                            button->reserveAnm(0x0C);
                            anim = (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(7);
                            anim->initFrame();
                            *reinterpret_cast<int*>(reinterpret_cast<u8*>(anim) + 0x14) = 1;
                        }
                        button->reserveAnm(0x0F);
                        anim = (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(5);
                        anim->initFrame();
                        *reinterpret_cast<int*>(reinterpret_cast<u8*>(anim) + 0x14) = 1;
                        *reinterpret_cast<u32*>(p + 0x8C) = 5;
                        snd::getSystem()->startSE("WIPL_SE_CANCEL");
                        *reinterpret_cast<u32*>(p + 0x64) = 0x1B;
                        break;
                    case 0x1D:
                        button->reserveAnm(0x1B);
                        button->reserveAnm(0x10);
                        button->reserveAnm(0x0F);
                        anim = (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(5);
                        anim->initFrame();
                        *reinterpret_cast<int*>(reinterpret_cast<u8*>(anim) + 0x14) = 1;
                        anim = (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(8);
                        anim->initFrame();
                        *reinterpret_cast<int*>(reinterpret_cast<u8*>(anim) + 0x14) = 1;
                        *reinterpret_cast<u32*>(p + 0x8C) = 5;
                        snd::getSystem()->startSE("WIPL_SE_CANCEL");
                        *reinterpret_cast<u32*>(p + 0x64) = 0x20;
                        (*reinterpret_cast<TextBalloon**>(p + 0xA8))->fadeoutForce();
                        reset_gui();
                        break;
                    case 0x22:
                        button->reserveAnm(0x1B);
                        button->reserveAnm(0x10);
                        button->reserveAnm(0x0F);
                        anim = (*reinterpret_cast<layout::Object**>(p + 0x68))->getAnim(0x1E);
                        anim->initFrame();
                        *reinterpret_cast<int*>(reinterpret_cast<u8*>(anim) + 0x14) = 1;
                        *reinterpret_cast<u32*>(p + 0x8C) = 5;
                        snd::getSystem()->startSE("WIPL_SE_CANCEL");
                        *reinterpret_cast<u32*>(p + 0x64) = 0x23;
                        (*reinterpret_cast<TextBalloon**>(p + 0xA8))->fadeoutForce();
                        reset_gui();
                        break;
                }
            } else if (scene::Button::cmpButtonName(paneName, scene::Button::BTN_CREATE_R_BUTTON) == 0) {
                switch (*reinterpret_cast<u32*>(p + 0x64)) {
                    case 0x0D:
                        button->reserveAnm(0x1D);
                        button->reserveAnm(0x10);
                        button->reserveAnm(0x0B);
                        set_textbox((*reinterpret_cast<layout::Object**>(p + 0x68))
                                        ->GetRootPane()
                                        ->FindPaneByName("T_name_00", true),
                                    reinterpret_cast<wchar_t*>(p + 0x2B4));
                        *reinterpret_cast<u32*>(p + 0x8C) = 7;
                        anim = (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(9);
                        anim->initFrame();
                        *reinterpret_cast<int*>(reinterpret_cast<u8*>(anim) + 0x14) = 1;
                        anim = (*reinterpret_cast<layout::Object**>(p + 0x80))->getAnim(1);
                        anim->initFrame();
                        *reinterpret_cast<int*>(reinterpret_cast<u8*>(anim) + 0x14) = 1;
                        update_friendinfo();
                        snd::getSystem()->startSE("WIPL_SE_DECIDE");
                        *reinterpret_cast<u32*>(p + 0x64) = 0x0F;
                        break;
                    case 0x11:
                        button->reserveAnm(0x1D);
                        button->reserveAnm(0x10);
                        if (*reinterpret_cast<u8*>(p + 0x4D1) != 0) {
                            button->reserveAnm(0x0F);
                        } else {
                            button->reserveAnm(0x0B);
                        }
                        anim = (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(5);
                        anim->initFrame();
                        *reinterpret_cast<int*>(reinterpret_cast<u8*>(anim) + 0x14) = 1;
                        anim = (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(6);
                        anim->initFrame();
                        *reinterpret_cast<int*>(reinterpret_cast<u8*>(anim) + 0x14) = 1;
                        *reinterpret_cast<u32*>(p + 0x8C) = 7;
                        snd::getSystem()->startSE("WIPL_SE_DECIDE");
                        *reinterpret_cast<u32*>(p + 0x64) = 0x17;
                        break;
                    case 0x1A:
                        button->reserveAnm(0x1D);
                        button->reserveAnm(0x10);
                        button->reserveAnm(0x0F);
                        anim = (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(5);
                        anim->initFrame();
                        *reinterpret_cast<int*>(reinterpret_cast<u8*>(anim) + 0x14) = 1;
                        anim = (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(6);
                        anim->initFrame();
                        *reinterpret_cast<int*>(reinterpret_cast<u8*>(anim) + 0x14) = 1;
                        *reinterpret_cast<u32*>(p + 0x8C) = 7;
                        snd::getSystem()->startSE("WIPL_SE_DECIDE");
                        *reinterpret_cast<u32*>(p + 0x64) = 0x1B;
                        reset_gui();
                        break;
                    case 0x1D:
                        button->reserveAnm(0x1D);
                        button->reserveAnm(0x10);
                        button->reserveAnm(0x0F);
                        anim = (*reinterpret_cast<layout::Object**>(p + 0x74))->getAnim(9);
                        anim->initFrame();
                        *reinterpret_cast<int*>(reinterpret_cast<u8*>(anim) + 0x14) = 1;
                        *reinterpret_cast<u32*>(p + 0x8C) = 7;
                        snd::getSystem()->startSE("WIPL_SE_DECIDE");
                        *reinterpret_cast<u32*>(p + 0x64) = 0x20;
                        (*reinterpret_cast<TextBalloon**>(p + 0xA8))->fadeoutForce();
                        reset_gui();
                        break;
                    case 0x22:
                        button->reserveAnm(0x1D);
                        button->reserveAnm(0x10);
                        anim = (*reinterpret_cast<layout::Object**>(p + 0x68))->getAnim(0x1E);
                        anim->initFrame();
                        *reinterpret_cast<int*>(reinterpret_cast<u8*>(anim) + 0x14) = 1;
                        *reinterpret_cast<u32*>(p + 0x8C) = 7;
                        snd::getSystem()->startSE("WIPL_SE_DECIDE");
                        *reinterpret_cast<u32*>(p + 0x64) = 0x23;
                        (*reinterpret_cast<TextBalloon**>(p + 0xA8))->fadeoutForce();
                        break;
                }
            }
        }
    }
}

wchar_t sPool_fmt[] = L"%06d\n";

void ipl::scene::AddressEdit::String::clear() {
    memset(this, 0, 0x204);
    memset(reinterpret_cast<u8*>(this) + 0x204, 0, 0x18);
    memset(reinterpret_cast<u8*>(this) + 0x21c, 0, 0x204);
    reinterpret_cast<u8*>(this)[0x420] = 0;
    reinterpret_cast<u8*>(this)[0x421] = 0;
    reinterpret_cast<u8*>(this)[0x422] = 0;
}

void ipl::scene::AddressEdit::String::setEMail(const wchar_t* email) {
    char ansi[0x100];
    u8* p = reinterpret_cast<u8*>(this);
    p[0x422] = 0;
    memset(p, 0, 0x204);
    wcsncpy(reinterpret_cast<wchar_t*>(p), email, 0xFF);
    u32 len = wcslen(email);
    memset(p + 0x21C, 0, 0x204);
    if (len > 0x10) {
        wcsncpy(reinterpret_cast<wchar_t*>(p + 0x21C), email, 0xE);
        wcscpy(reinterpret_cast<wchar_t*>(p + 0x238), L"...");
    } else {
        wcscpy(reinterpret_cast<wchar_t*>(p + 0x21C), email);
    }
    memset(ansi, 0, 0x100);
    utility::CharacterCode::UTF16ToANSI(reinterpret_cast<u8*>(ansi), email, 0x100);
    int ok = (NWC24CheckPublicMailAddr_(ansi) == 0);
    p[0x420] = ok;
}

extern "C" asm void setWiiNo__Q43ipl5scene11AddressEdit6StringFPCw() {
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


extern "C" asm void isDupCode__Q43ipl5scene11AddressEdit6StringCFv() {
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

extern "C" asm void isMyCode__Q43ipl5scene11AddressEdit6StringCFv() {
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

extern "C" asm void set_err_msg__Q33ipl5scene11AddressEditFPwUl8NWC24Err() {
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    addi r11, r1, 0x60
    bl _savegpr_27
    mr r28, r4
    mr r27, r3
    mr r29, r5
    mr r30, r6
    mr r3, r28
    slwi r5, r5, 1
    li r4, 0x0
    bl memset
    lis r3, smArg__Q23ipl6System@ha
    li r4, 0x190
    addi r3, r3, smArg__Q23ipl6System@l
    lwz r3, 0x80(r3)
    lwz r3, 0x0(r3)
    bl getMessage__Q33ipl7message7MessageCFUl
    mr r31, r3
    mr r3, r28
    bl wcslen
    subf r5, r3, r29
    mr r3, r28
    mr r4, r31
    bl wcsncat
    addi r3, r1, 0x8
    li r4, 0x0
    li r5, 0x40
    bl memset
    lwz r3, 0x4ec(r27)
    bl getErrCode__Q33ipl5scene15FriendListCacheCFv
    lis r5, lbl_816485EC@ha
    mr r6, r3
    addi r3, r1, 0x8
    li r4, 0x20
    addi r5, r5, lbl_816485EC@l
    crclr 4*cr1+eq
    bl swprintf
    mr r3, r28
    bl wcslen
    subf r5, r3, r29
    mr r3, r28
    addi r4, r1, 0x8
    bl wcsncat
    cmpwi r30, -0x1f
    beq set_err_msg__Q33ipl5scen_L1
    bge set_err_msg__Q33ipl5scen_L0
    cmpwi r30, -0x20
    bge set_err_msg__Q33ipl5scen_L2
    b set_err_msg__Q33ipl5scen_L3
set_err_msg__Q33ipl5scen_L0:
    cmpwi r30, -0x6
    beq set_err_msg__Q33ipl5scen_L2
    b set_err_msg__Q33ipl5scen_L3
set_err_msg__Q33ipl5scen_L1:
    li r4, 0x19a
    b set_err_msg__Q33ipl5scen_L3
set_err_msg__Q33ipl5scen_L2:
    li r4, 0x1c5
set_err_msg__Q33ipl5scen_L3:
    lis r3, smArg__Q23ipl6System@ha
    addi r3, r3, smArg__Q23ipl6System@l
    lwz r3, 0x80(r3)
    lwz r3, 0x0(r3)
    bl getMessage__Q33ipl7message7MessageCFUl
    mr r31, r3
    mr r3, r28
    bl wcslen
    subf r5, r3, r29
    mr r3, r28
    mr r4, r31
    bl wcsncat
    addi r11, r1, 0x60
    bl _restgpr_27
    lwz r0, 0x64(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}

void ipl::scene::AddressEditEvent::onEvent(u32 compId, u32 event, void* data) {
    gui::PaneComponent* component = static_cast<gui::PaneComponent*>(mpManager->getComponent(compId));
    const char* paneName = component->getPane()->GetName();

    switch (event) {
        case ON_POINT:
            if (data != NULL) {
                static_cast<AddressEdit*>(mpInstance)
                    ->start_point_event(paneName, static_cast<controller::Interface*>(data));
            }
            break;
        case ON_LEFT:
            static_cast<AddressEdit*>(mpInstance)->start_left_event(paneName);
            break;
        case ON_TRIG:
            if (data != NULL &&
                static_cast<controller::Interface*>(data)->downTrg(controller::BTN_INTERACT)) {
                static_cast<AddressEdit*>(mpInstance)->start_trig_event(paneName);
            }
            break;
    }
}


void ipl::scene::AddressInputEvent::onEvent(u32 compId, u32 event, void* data) {
    gui::PaneComponent* component = static_cast<gui::PaneComponent*>(mpManager->getComponent(compId));
    const char* paneName = component->getPane()->GetName();

    switch (event) {
        case ON_TRIG:
            if (data != NULL &&
                static_cast<controller::Interface*>(data)->downTrg(controller::BTN_INTERACT)) {
                static_cast<AddressEdit*>(mpInstance)
                    ->start_ipt_trig_event(paneName,
                                           static_cast<controller::Interface*>(data)->getChannel());
            }
            break;
        case ON_POINT:
            if (data != NULL) {
                static_cast<AddressEdit*>(mpInstance)
                    ->start_ipt_point_event(paneName,
                                            static_cast<controller::Interface*>(data)->getChannel());
            }
            break;
        case ON_LEFT:
            if (data != NULL) {
                static_cast<AddressEdit*>(mpInstance)
                    ->start_ipt_left_event(paneName,
                                           static_cast<controller::Interface*>(data)->getChannel());
            }
            break;
    }
}


