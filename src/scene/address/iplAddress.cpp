#include "scene/address/iplAddress.h"
#include "scene/letterWriter/iplLetterWriter.h"
#include "scene/mailAddSel/iplMailAddressSelect.h"
#include "scene/button/iplButton.h"
#include "sound/iplSound.h"

#include "system/iplController.h"
#include "system/MESGEntries.h"
#include "system/iplSystem.h"
#include "scene/setting/iplNCDSetting.h"
#include "layout/iplGuiManager.h"
#include "layout/iplLayout.h"
#include "utility/iplCharacterCode.h"

#include <stdio.h>
#include <string.h>

extern "C" char lbl_81647538[] __attribute__((aligned(1))) = "T_name_b_00";
extern "C" char lbl_81647544[] __attribute__((aligned(1))) = "T_name_b_01";
extern "C" char lbl_81647550[] __attribute__((aligned(1))) = "T_name_b_02";
extern "C" char lbl_8164755C[] __attribute__((aligned(1))) = "T_name_b_03";
extern "C" char lbl_81647568[] __attribute__((aligned(1))) = "T_name_b_04";
extern "C" const char* lbl_81647574[5] = {
    lbl_81647538, lbl_81647544, lbl_81647550, lbl_8164755C, lbl_81647568,
};

extern "C" char lbl_81647588[] __attribute__((aligned(1))) = "T_name_c_00";
extern "C" char lbl_81647594[] __attribute__((aligned(1))) = "T_name_c_01";
extern "C" char lbl_816475A0[] __attribute__((aligned(1))) = "T_name_c_02";
extern "C" char lbl_816475AC[] __attribute__((aligned(1))) = "T_name_c_03";
struct TextNameCData {
    char lastName[12];
    const char* names[5];
};
extern "C" TextNameCData lbl_816475B8 = {
    "T_name_c_04", {lbl_81647588, lbl_81647594, lbl_816475A0, lbl_816475AC,
                    lbl_816475B8.lastName},
};

extern "C" char lbl_816475D8[] __attribute__((aligned(1))) = "B_name_b_00";
extern "C" char lbl_816475E4[] __attribute__((aligned(1))) = "B_name_b_01";
extern "C" char lbl_816475F0[] __attribute__((aligned(1))) = "B_name_b_02";
extern "C" char lbl_816475FC[] __attribute__((aligned(1))) = "B_name_b_03";
extern "C" char lbl_81647608[] __attribute__((aligned(1))) = "B_name_b_04";
extern "C" const char* lbl_81647614[5] = {
    lbl_816475D8, lbl_816475E4, lbl_816475F0, lbl_816475FC, lbl_81647608,
};

extern "C" char lbl_81647628[] __attribute__((aligned(1))) = "B_name_b_00_01";
extern "C" char lbl_81647637[] __attribute__((aligned(1))) = "B_name_b_01_02";
extern "C" char lbl_81647646[] __attribute__((aligned(1))) = "B_name_b_02_03";
extern "C" char lbl_81647655[] __attribute__((aligned(1))) = "B_name_b_03_04";
extern "C" const char* lbl_81647664[4] = {
    lbl_81647628, lbl_81647637, lbl_81647646, lbl_81647655,
};

extern "C" char lbl_81647674[] __attribute__((aligned(1))) = "name_b_00";
extern "C" char lbl_8164767E[] __attribute__((aligned(1))) = "name_b_01";
extern "C" char lbl_81647688[] __attribute__((aligned(1))) = "name_b_02";
extern "C" char lbl_81647692[] __attribute__((aligned(1))) = "name_b_03";
struct NameBData {
    char lastName[10];
    unsigned char alignment[2];
    const char* names[5];
};
extern "C" NameBData lbl_8164769C = {
    "name_b_04", {0, 0}, {lbl_81647674, lbl_8164767E, lbl_81647688, lbl_81647692,
                           lbl_8164769C.lastName},
};

extern "C" char lbl_816476BC[] __attribute__((aligned(1))) = "G_name_c_00";
extern "C" char lbl_816476C8[] __attribute__((aligned(1))) = "G_name_c_01";
extern "C" char lbl_816476D4[] __attribute__((aligned(1))) = "G_name_c_02";
extern "C" char lbl_816476E0[] __attribute__((aligned(1))) = "G_name_c_03";
#pragma pack(push, 1)
struct NameCData {
    char lastName[12];
    const char* names[5];
    char pool[0x276];
};
#pragma pack(pop)
extern "C" NameCData lbl_816476EC = {
    "G_name_c_04",
    {lbl_816476BC, lbl_816476C8, lbl_816476D4, lbl_816476E0, lbl_816476EC.lastName},
    "th_Adress_a.brlyt\0"
    "th_Adress_a_note_alp_in.brlan\0"
    "G_note_all\0"
    "th_Adress_a_note_alp_out.brlan\0"
    "th_Adress_a_note_trns_in.brlan\0"
    "th_Adress_a_note_trns_out.brlan\0"
    "th_Adress_a_note_e_rtt.brlan\0"
    "G_note_e_rtt\0"
    "th_Adress_a_note_c_rtt.brlan\0"
    "note_c_rtt\0"
    "th_Adress_a_name_in.brlan\0"
    "th_Adress_a_name_out.brlan\0"
    "th_Adress_a_name_psh.brlan\0"
    "th_Adress_a_gry_name_in.brlan\0"
    "th_Adress_a_gry_name_out.brlan\0"
    "th_Adress_a_gry_name_psh.brlan\0"
    "th_Adress_a_name_c_gry.brlan\0"
    "my_Back_a.brlyt\0"
    "my_Back_a_Apear.brlan\0"
    "Picture_00\0"
    "my_Back_a_Lost.brlan\0"
    "my_Dialog_a.brlyt\0"
    "my_Dialog_a_DialogIn.brlan\0"
    "my_Dialog_a_DialogOut.brlan\0"
    "T_Dialog\0"
    "mii_b_%02d\0"
    "mii_c_%02d\0"
    "T_adrs_00\0"
    "T_wii_msg"
};
extern "C" const wchar_t lbl_8160F650[] = L"0123456789";
extern "C" const float lbl_816947D0[2] = {176.0f, -0.0f};
extern "C" const float lbl_816947D8 = 0.0f;
extern "C" const float lbl_816947DC = 20.0f;
extern "C" const float lbl_816947E0 = 1.0f;
extern "C" const float lbl_816947E4 = 0.01f;
extern "C" float lbl_81698B50;
extern "C" float lbl_81698B54;
extern "C" float lbl_816947E8 __attribute__((section(".sdata2"), aligned(4))) = -1.0f;
extern "C" const u16 lbl_8160F666 __attribute__((section(".rodata"), aligned(1), used)) = 0;
static ipl::math::VEC2 sAddressVEC2(lbl_816947E8, lbl_816947E8);
extern "C" char lbl_81647982[] __attribute__((aligned(1))) = "N_note_move";
extern "C" char lbl_8164798E[] __attribute__((aligned(1))) = "WIPL_SE_FL_PAGE_INC";
extern "C" char sAddressStringPoolB[];

extern "C" char smArg__Q23ipl6System;
extern "C" void checkUserId__Q33ipl5nwc247ManagerFUx();
extern "C" void getErrCode__Q33ipl5nwc247ManagerFv();
extern "C" void close__Q33ipl5nwc247ManagerFv();
extern "C" int check__Q33ipl5nwc247ManagerFUl(void*, unsigned int);
extern "C" void initFrame__Q33ipl7utility15FrameControllerFv(void*);
extern "C" char lbl_81647AC3[];
extern "C" char lbl_81647538[];
extern "C" char lbl_81647982[];
extern "C" void deleteFriendInfo__Q33ipl5nwc247ManagerFUl();
extern "C" void getScene__Q33ipl5scene7ManagerFi();
extern "C" void setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler();
extern "C" void calc__Q33ipl6layout6ObjectFv();
extern "C" void __ct__Q33ipl4math4VEC2Fff();
extern "C" void __dt__Q33ipl6nigaoe6ObjectFv();
extern "C" void __dl__FPv(void*);
extern "C" void GetTexture__Q34nw4r3lyt8MaterialCFP9_GXTexObjUc();
extern "C" void SetTexture__Q34nw4r3lyt8MaterialFUcRC9_GXTexObj();
extern "C" void create__Q33ipl6nigaoe7ManagerFPQ23EGG4HeapiiiPFPQ33ipl6nigaoe6ObjectPvPv();
extern "C" int init__Q33ipl5scene15FriendListCacheFv(ipl::scene::FriendListCache*);
extern "C" int check__Q33ipl5scene15FriendListCacheFv(
    ipl::scene::FriendListCache*);
extern "C" void onInitFriendList__Q33ipl5scene7AddressFv(void*);
extern "C" void callBtn1__Q23ipl12DialogWindowFUlUl(void*, unsigned int, unsigned int);
extern "C" void* List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(const void*, unsigned short);
extern "C" void update__Q33ipl3gui11PaneManagerFv(void*);
extern "C" void changePage_onDrag__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void reset_gui__Q33ipl5scene7AddressFb(ipl::scene::Address* self, bool reset);
extern "C" void left_point_event__Q33ipl5scene7AddressFi(ipl::scene::Address* self, int index);
extern "C" void set_textbox__Q33ipl5scene7AddressFPCcPCw(
    ipl::scene::Address* self, const char* paneName, const wchar_t* text);
extern "C" void set_page_text__Q33ipl5scene7AddressFPCci(
    ipl::scene::Address* self, const char* paneName, int page);
extern "C" void add_translate__Q33ipl5scene7AddressFPQ34nw4r3lyt4PaneRCQ33ipl4math4VEC2(
    void* self, nw4r::lyt::Pane* pane, const ipl::math::VEC2& offset);
extern "C" int get_button_no__Q33ipl5scene7AddressFPCc(void* self, const char* paneName);
extern "C" void on_point_event__Q33ipl5scene7AddressFiPQ33ipl10controller9Interface(
    ipl::scene::Address* self, int index, void* controller);
extern "C" bool isReleasableArea__Q33ipl5scene7AddressFii(ipl::scene::Address* self, int page,
                                                          int index);
extern "C" void SetTranslate__Q34nw4r3lyt4PaneFRCQ34nw4r4math4VEC3(
    nw4r::lyt::Pane* pane, const nw4r::math::VEC3* translate);
extern "C" void SetTranslate__Q34nw4r3lyt4PaneFRCQ34nw4r4math4VEC2(
    nw4r::lyt::Pane* pane, const nw4r::math::VEC2* translate);
extern "C" void set_friend__Q33ipl5scene7AddressFPCcUlUlRQ43ipl5scene7Address6MiiObjb(
    ipl::scene::Address* self, const char* paneName, unsigned int friendIndex,
    unsigned int buttonIndex, void* miiObj, bool isDrag);
extern "C" void writeFriendInfo__Q33ipl5nwc247ManagerFPC15NWC24FriendInfoUl(
    void* manager, const NWC24FriendInfo* info, unsigned int index);
extern "C" void updateFriendInfo__Q33ipl5nwc247ManagerFPC15NWC24FriendInfoUl(
    void* manager, const NWC24FriendInfo* info, unsigned int index);
extern "C" void swapFriendInfo__Q33ipl5nwc247ManagerFUlUl(
    void* manager, unsigned int first, unsigned int second);
extern "C" void swap__Q33ipl5scene15FriendListCacheFUlUl(
    ipl::scene::FriendListCache* self, unsigned int first, unsigned int second);
extern "C" void entry_friend__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void reserveAllSceneDestruction__Q33ipl5scene4BaseFiPv(
    void* self, int sceneId, void* args);
extern "C" void createChildScene__Q33ipl5scene4BaseFiPQ33ipl5scene4BasePQ33ipl5scene4BasePv(
    void* self, int sceneId, void* parent, void* child, void* args);
extern "C" void __ct__Q43ipl5scene7Address6MiiObjFv();
extern "C" void __dt__Q43ipl5scene7Address6MiiObjFv();
extern "C" void init__Q43ipl5scene7Address6MiiObjFPQ34nw4r3lyt4Pane(
    void*, nw4r::lyt::Pane*);
extern "C" void reset__Q43ipl5scene7Address6MiiObjFv(void*);
extern "C" void set__Q43ipl5scene7Address6MiiObjFUx(void*, unsigned long long);
extern "C" void __construct_array(void*, void (*)(), void (*)(), unsigned int, unsigned int);
extern "C" char __vt__Q33ipl5scene7Address[];
extern "C" char __vt__Q33ipl5scene12AddressEvent[];
extern "C" void* __nw__FUli(unsigned int, int);
extern "C" void* __nwa__FUl(unsigned int);
extern "C" void SetVisible__Q34nw4r3lyt4PaneFb(nw4r::lyt::Pane*, bool);
extern "C" void __destroy_arr(void*, void (*)(), unsigned int, unsigned int);

ipl::scene::Address::Address(EGG::Heap* heap, int mode) : ipl::scene::FaderSceneBase(heap) {
    char* address = reinterpret_cast<char*>(this);
    *reinterpret_cast<int*>(address + 0x88) = mode;
    *reinterpret_cast<int*>(address + 0x8c) = 0;
    *reinterpret_cast<int*>(address + 0x90) = 0;
    *reinterpret_cast<int*>(address + 0x94) = 0;
    *reinterpret_cast<int*>(address + 0x98) = 0;
    *reinterpret_cast<int*>(address + 0x9c) = 0;
    *reinterpret_cast<int*>(address + 0xa4) = 1;
    *reinterpret_cast<int*>(address + 0xa8) = 0;
    *reinterpret_cast<int*>(address + 0xac) = 1;
    *reinterpret_cast<int*>(address + 0xb0) = 0;
    *reinterpret_cast<int*>(address + 0xb4) = 20;
    *reinterpret_cast<int*>(address + 0xb8) = 0;
    *reinterpret_cast<int*>(address + 0xbc) = 0;
    *reinterpret_cast<int*>(address + 0xc0) = 0;
    *reinterpret_cast<unsigned char*>(address + 0xe0) = 0;
    __construct_array(&mMiiObjA[0], __ct__Q43ipl5scene7Address6MiiObjFv,
                      __dt__Q43ipl5scene7Address6MiiObjFv, 0x28, 5);
    __construct_array(&mMiiObjB[0], __ct__Q43ipl5scene7Address6MiiObjFv,
                      __dt__Q43ipl5scene7Address6MiiObjFv, 0x28, 5);
    *reinterpret_cast<int*>(address + 0x28) = 3;
    for (int index = 0; index < 5; index++) {
        reinterpret_cast<int*>(address + 0xcc)[index] = 0;
    }
    for (int index = 0; index < 5; index++) {
        *reinterpret_cast<unsigned char*>(address + 0xc4 + index) = 0;
    }
    memset(address + 0x64, 0, 0x24);
    *reinterpret_cast<int*>(address + 0x78) = -1;
    *reinterpret_cast<int*>(address + 0x7c) = -1;
}

ipl::scene::Address::~Address() {
    if (unk_0x274 != NULL) {
        __dl__FPv(unk_0x274);
    }
    __destroy_arr(&mMiiObjB[0], __dt__Q43ipl5scene7Address6MiiObjFv, 0x28, 5);
    __destroy_arr(&mMiiObjA[0], __dt__Q43ipl5scene7Address6MiiObjFv, 0x28, 5);
}

extern "C" asm void getChild__Q33ipl5scene4BaseFv() {
    nofralloc
    lwz r3, 8(r3)
    blr
}

extern "C" asm void getPrev__Q33ipl5scene4BaseFv() {
    nofralloc
    lwz r3, 0x10(r3)
    blr
}

extern "C" asm void getNext__Q33ipl5scene4BaseFv() {
    nofralloc
    lwz r3, 0x0C(r3)
    blr
}

extern "C" asm void getParent__Q33ipl5scene4BaseFv() {
    nofralloc
    lwz r3, 4(r3)
    blr
}

extern "C" asm void startResetting__Q33ipl5scene4BaseFv() {
    nofralloc
    blr
}

extern "C" asm void isResetProcessDone__Q33ipl5scene4BaseFv() {
    nofralloc
    li r3, 1
    blr
}

extern "C" asm void isResetAcceptable__Q33ipl5scene4BaseCFv() {
    nofralloc
    li r3, 1
    blr
}

extern "C" asm void isReady__Q33ipl5scene4BaseCFv() {
    nofralloc
    li r3, 0
    blr
}

extern "C" asm void prepare__Q33ipl5scene7AddressFv() {
    nofralloc
    blr
}

typedef gui::EventHandler GUIEventHandler;

struct AddressCreateFields {
    char unk00[0x24];
    EGG::Heap* heap;
    char unk28[0x64];
    ipl::layout::Object* mainLayout;
    void* unk90;
    gui::EventHandler* event;
    ipl::gui::PaneManager* gui;
    ipl::layout::Object* backLayout;
    ipl::layout::Object* dialogLayout;
};

void ipl::scene::Address::create() {
    const char* data = lbl_81647538;
    ipl::scene::SceneObj* scene = ipl::System::getScene(4);
    ipl::nand::LayoutFile* file = *reinterpret_cast<ipl::nand::LayoutFile**>(reinterpret_cast<char*>(scene) + 0xd20);
    *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(this) + 0xe1) = 1;
    *reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<char*>(this) + 0x8c) =
        new ipl::layout::Object(*reinterpret_cast<EGG::Heap**>(reinterpret_cast<char*>(this) + 0x24),
                                file, "arc", data + 0x1d4);
    (*reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<char*>(this) + 0x8c))
        ->bindToGroup(data + 0x1e6, data + 0x204, false, true);
    (*reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<char*>(this) + 0x8c))
        ->bindToGroup(data + 0x20f, data + 0x204, false, false);
    (*reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<char*>(this) + 0x8c))
        ->bindToGroup(data + 0x22e, data + 0x204, false, false);
    (*reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<char*>(this) + 0x8c))
        ->bindToGroup(data + 0x24d, data + 0x204, false, false);
    (*reinterpret_cast<ipl::layout::Object* volatile*>(reinterpret_cast<char*>(this) + 0x8c))
        ->bindToGroup(data + 0x26d, data + 0x28a, false,
                      *reinterpret_cast<bool volatile*>(reinterpret_cast<char*>(this) + 0xe1));
    (*reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<char*>(this) + 0x8c))
        ->bindToGroup(data + 0x297, data + 0x2b4, false,
                      !*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(this) + 0xe1));

    {
        const char* const* names = reinterpret_cast<const char* const*>(data + 0x170);
        for (int i = 0; i < 5; i++) {
            (*reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<char*>(this) + 0x8c))
                ->bindToGroup(data + 0x2bf, names[i], false, false);
        }
    }
    {
        const char* const* names = reinterpret_cast<const char* const*>(data + 0x170);
        for (int i = 0; i < 5; i++) {
            (*reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<char*>(this) + 0x8c))
                ->bindToGroup(data + 0x2d9, names[i], false, false);
        }
    }
    {
        const char* const* names = reinterpret_cast<const char* const*>(data + 0x170);
        for (int i = 0; i < 5; i++) {
            (*reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<char*>(this) + 0x8c))
                ->bindToGroup(data + 0x2f4, names[i], false, false);
        }
    }
    {
        const char* const* names = reinterpret_cast<const char* const*>(data + 0x170);
        for (int i = 0; i < 5; i++) {
            (*reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<char*>(this) + 0x8c))
                ->bindToGroup(data + 0x30f, names[i], false, false);
        }
    }
    {
        const char* const* names = reinterpret_cast<const char* const*>(data + 0x170);
        for (int i = 0; i < 5; i++) {
            (*reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<char*>(this) + 0x8c))
                ->bindToGroup(data + 0x32d, names[i], false, false);
        }
    }
    {
        const char* const* names = reinterpret_cast<const char* const*>(data + 0x170);
        for (int i = 0; i < 5; i++) {
            (*reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<char*>(this) + 0x8c))
                ->bindToGroup(data + 0x34c, names[i], false, false);
        }
    }
    {
        const char* const* names = reinterpret_cast<const char* const*>(data + 0x1c0);
        for (int i = 0; i < 5; i++) {
            (*reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<char*>(this) + 0x8c))
                ->bindToGroup(data + 0x36b, names[i], false, false);
        }
    }
    (*reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<char*>(this) + 0x8c))->finishBinding();

    *reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<char*>(this) + 0x9c) =
        new ipl::layout::Object(*reinterpret_cast<EGG::Heap**>(reinterpret_cast<char*>(this) + 0x24),
                                file, "arc", data + 0x388);
    (*reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<char*>(this) + 0x9c))
        ->bind(data + 0x398, data + 0x3ae, false, true);
    (*reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<char*>(this) + 0x9c))
        ->bind(data + 0x3b9, data + 0x3ae, false, false);
    (*reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<char*>(this) + 0x9c))->finishBinding();
    static_cast<ipl::layout::Animator*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
        reinterpret_cast<char*>(*reinterpret_cast<ipl::layout::Object**>(
            reinterpret_cast<char*>(this) + 0x9c)) + 0x28c, 0))->initAnmFrame();

    *reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<char*>(this) + 0xa0) =
        new ipl::layout::Object(*reinterpret_cast<EGG::Heap**>(reinterpret_cast<char*>(this) + 0x24),
                                file, "arc", data + 0x3ce);
    (*reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<char*>(this) + 0xa0))
        ->bind(data + 0x3e0, "N_Top", false, true);
    (*reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<char*>(this) + 0xa0))
        ->bind(data + 0x3fb, "N_Top", false, false);
    (*reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<char*>(this) + 0xa0))->finishBinding();
    nw4r::lyt::TextBox* dialog = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(
        (*reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<char*>(this) + 0xa0))
            ->GetRootPane()->FindPaneByName(data + 0x417, true));
    dialog->SetString(ipl::System::getMessage(0x4e), 0);

    AddressCreateFields* fields = reinterpret_cast<AddressCreateFields*>(this);
    GUIEventHandler* event = reinterpret_cast<GUIEventHandler*>(::operator new(0x14));
    if (event != NULL) {
        *reinterpret_cast<int*>(reinterpret_cast<char*>(event) + 8) = 0;
        *reinterpret_cast<char**>(event) = __vt__Q33ipl5scene12AddressEvent;
        *reinterpret_cast<ipl::scene::Address**>(reinterpret_cast<char*>(event) + 0xc) = this;
    }
    fields->event = event;

    fields->gui = new ipl::gui::PaneManager(
        fields->event, fields->mainLayout->getDrawInfo(), NULL, NULL);
    fields->gui->setupScene(fields->mainLayout);
    fields->gui->setAllComponentTriggerTarget(false);

    const char* const* buttons = reinterpret_cast<const char* const*>(data + 0xdc);
    for (int i = 0; i < 5; i++) {
        fields->gui->setTriggerTarget(
            (*reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<char*>(this) + 0x8c))
                ->GetRootPane()->FindPaneByName(buttons[i], true), true);
    }
    buttons = reinterpret_cast<const char* const*>(data + 0x12c);
    for (int i = 0; i < 4; i++) {
        fields->gui->setTriggerTarget(
            (*reinterpret_cast<ipl::layout::Object**>(reinterpret_cast<char*>(this) + 0x8c))
                ->GetRootPane()->FindPaneByName(buttons[i], true), true);
    }

    char paneNameC[16];
    char paneNameB[16];
    for (int i = 0; i < 5; i++) {
        sprintf(paneNameC, data + 0x420, i);
        void* pane = (*reinterpret_cast<ipl::layout::Object**>(
            reinterpret_cast<char*>(this) + 0x8c))->GetRootPane()->FindPaneByName(paneNameC, true);
        init__Q43ipl5scene7Address6MiiObjFPQ34nw4r3lyt4Pane(
            reinterpret_cast<char*>(this) + 0xe4 + i * 0x28,
            static_cast<nw4r::lyt::Pane*>(pane));
    }
    for (int i = 0; i < 5; i++) {
        sprintf(paneNameB, data + 0x42b, i);
        void* pane = (*reinterpret_cast<ipl::layout::Object**>(
            reinterpret_cast<char*>(this) + 0x8c))->GetRootPane()->FindPaneByName(paneNameB, true);
        init__Q43ipl5scene7Address6MiiObjFPQ34nw4r3lyt4Pane(
            reinterpret_cast<char*>(this) + 0x1ac + i * 0x28,
            static_cast<nw4r::lyt::Pane*>(pane));
    }

    const char* paneName = data + 0x436;
    set_textbox__Q33ipl5scene7AddressFPCcPCw(this, paneName, ipl::System::getMessage(0x86));
    paneName = data + 0x440;
    set_textbox__Q33ipl5scene7AddressFPCcPCw(this, paneName, ipl::System::getMessage(0x42));

    void* cache = __nw__FUli(0x9d80, 0x20);
    if (cache != NULL) {
        *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(cache) + 0x9d78) = 0;
    }
    *reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x274) = cache;
    if (init__Q33ipl5scene15FriendListCacheFv(
            reinterpret_cast<ipl::scene::FriendListCache*>(cache))) {
        onInitFriendList__Q33ipl5scene7AddressFv(this);
        *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0xa4) = 1;
    } else {
        *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0xa4) = 0;
    }
    *reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x298) = __nwa__FUl(0x2d20);
    nw4r::lyt::Pane* pane = (*reinterpret_cast<ipl::layout::Object**>(
        reinterpret_cast<char*>(this) + 0x8c))->GetRootPane()->FindPaneByName(data + 0x44a, true);
    SetVisible__Q34nw4r3lyt4PaneFb(pane, false);
}

extern "C" asm void calcCommon__Q33ipl5scene14FaderSceneBaseFv() {
    nofralloc
    blr
}

extern "C" void fistt_fadein__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void fistt_wait_open__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" char lbl_8164798E[];
extern "C" void onNextPage__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void onPreviousPage__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void stt_cover_normal__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void stt_cover_forward__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void stt_cover_backward__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void stt_normal__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void stt_forward__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void stt_backward__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void stt_loop_forward__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void stt_loop_backward__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void stt_decide__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void stt_drag__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void stt_release__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void stt_wait_child_cst__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void stt_wait_child_dst__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void stt_wait_child_fadeout__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void stt_msg_net__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void stt_wait_parental__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void stt_wait_parental_dst__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void stt_msg_wc__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void stt_wait_parental_wc__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void stt_wait_parental_dst_wc__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void stt_msg_nwc24_error__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void stt_msg_fi_full__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void stt_msg_parental__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void stt_msg_open_failure__Q33ipl5scene7AddressFv(ipl::scene::Address* self);
extern "C" void stt_wait_dialog__Q33ipl5scene7AddressFv(ipl::scene::Address* self);

extern "C" ipl::scene::FaderSceneCommand calcFadein__Q33ipl5scene7AddressFv(
    ipl::scene::Address* self) {
    int state = *reinterpret_cast<int*>(reinterpret_cast<char*>(self) + 0xa4);
    switch (state) {
    case 0:
        fistt_wait_open__Q33ipl5scene7AddressFv(self);
        break;
    case 1:
        fistt_fadein__Q33ipl5scene7AddressFv(self);
        break;
    }
    return *reinterpret_cast<int*>(reinterpret_cast<char*>(self) + 0xa4) == 2
               ? ipl::scene::FADER_SCN_NEXT
               : ipl::scene::FADER_SCN_CONTINUE;
}

extern "C" void initCalcNormal__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    gui::EventHandler* event = reinterpret_cast<gui::EventHandler*>(self);
    if (event != NULL) {
        event = reinterpret_cast<gui::EventHandler*>(reinterpret_cast<char*>(event) + 0x58);
    }
    static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->setEventHandler(event, NULL);
}

extern "C" ipl::scene::FaderSceneCommand calcNormal__Q33ipl5scene7AddressFv(
    ipl::scene::Address* self) {
    int state = *reinterpret_cast<int*>(reinterpret_cast<char*>(self) + 0xac);
    switch (state) {
    case 0:
        ipl::snd::sSystem.startSE(lbl_8164798E);
        onNextPage__Q33ipl5scene7AddressFv(self);
        break;
    case 1:
        stt_cover_normal__Q33ipl5scene7AddressFv(self);
        break;
    case 2:
        stt_cover_forward__Q33ipl5scene7AddressFv(self);
        break;
    case 3:
        stt_cover_backward__Q33ipl5scene7AddressFv(self);
        break;
    case 4:
        stt_normal__Q33ipl5scene7AddressFv(self);
        break;
    case 5:
        stt_forward__Q33ipl5scene7AddressFv(self);
        break;
    case 6:
        stt_backward__Q33ipl5scene7AddressFv(self);
        break;
    case 7:
        stt_loop_forward__Q33ipl5scene7AddressFv(self);
        break;
    case 8:
        stt_loop_backward__Q33ipl5scene7AddressFv(self);
        break;
    case 9:
        stt_decide__Q33ipl5scene7AddressFv(self);
        break;
    case 10:
        stt_drag__Q33ipl5scene7AddressFv(self);
        break;
    case 11:
        stt_release__Q33ipl5scene7AddressFv(self);
        break;
    case 12:
        stt_wait_child_cst__Q33ipl5scene7AddressFv(self);
        break;
    case 13:
        stt_wait_child_dst__Q33ipl5scene7AddressFv(self);
        break;
    case 14:
        stt_wait_child_fadeout__Q33ipl5scene7AddressFv(self);
        break;
    case 15:
        stt_msg_net__Q33ipl5scene7AddressFv(self);
        break;
    case 16:
        stt_wait_parental__Q33ipl5scene7AddressFv(self);
        break;
    case 17:
        stt_wait_parental_dst__Q33ipl5scene7AddressFv(self);
        break;
    case 18:
        stt_msg_wc__Q33ipl5scene7AddressFv(self);
        break;
    case 19:
        stt_wait_parental_wc__Q33ipl5scene7AddressFv(self);
        break;
    case 20:
        stt_wait_parental_dst_wc__Q33ipl5scene7AddressFv(self);
        break;
    case 21:
        stt_msg_nwc24_error__Q33ipl5scene7AddressFv(self);
        break;
    case 22:
        stt_msg_fi_full__Q33ipl5scene7AddressFv(self);
        break;
    case 23:
        stt_msg_parental__Q33ipl5scene7AddressFv(self);
        break;
    case 24:
        stt_msg_open_failure__Q33ipl5scene7AddressFv(self);
        break;
    case 25:
        stt_wait_dialog__Q33ipl5scene7AddressFv(self);
        break;
    }
    return static_cast<ipl::scene::FaderSceneCommand>(
        *reinterpret_cast<int*>(reinterpret_cast<char*>(self) + 0xac) == 0x1a);
}

extern "C" char sAddressStringPoolBPrefix[0x41] __attribute__((aligned(1))) =
    "N_note_a\0"
    "N_note_b\0"
    "N_note_c\0"
    "N_note_d\0"
    "N_note_e\0"
    "T_wii_name\0"
    "T_nmbr_b";
extern "C" char lbl_81647A4D[0x14] __attribute__((aligned(1))) = "WIPL_SE_FL_PAGE_DEC";
extern "C" char lbl_81647A61[0xc] __attribute__((aligned(1))) = "N_note_base";
extern "C" char lbl_81647A6D[0xb] __attribute__((aligned(1))) = "T_CalAdd_R";
extern "C" char lbl_81647A78[0x4b] __attribute__((aligned(1))) =
    "WIPL_SE_DECIDE\0"
    "mii_move\0"
    "WIPL_SE_CH_HOLD\0"
    "WIPL_SE_CH_SET\0"
    "WIPL_SE_CH_NOT_MOVE";
extern "C" char lbl_81647AC3[0x2f] __attribute__((aligned(1))) =
    "WIPL_SE_BT_TARGETTING\0"
    "WIPL_SE_CANCEL\0"
    "T_nmbr_c\0";
extern "C" wchar_t lbl_81647AF2[] = L"%06d\n";
extern "C" char lbl_81647AFE[0x1c] __attribute__((aligned(1))) =
    "T_name_move\0"
    "WIPL_SE_CH_DRAG";
extern "C" char lbl_81647B1A[0xc] __attribute__((aligned(1))) = "N_base_move";
extern "C" wchar_t lbl_81647B26[] = L"1234567890123456";
extern "C" wchar_t lbl_81647B48[] = L"%016lld";
extern "C" void fistt_wait_open__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    if (init__Q33ipl5scene15FriendListCacheFv(
            *reinterpret_cast<ipl::scene::FriendListCache**>(address + 0x274))) {
        onInitFriendList__Q33ipl5scene7AddressFv(self);
        *reinterpret_cast<int*>(address + 0xa4) = 1;
    } else if (*reinterpret_cast<int*>(address + 0xa8) >= 300) {
        callBtn1__Q23ipl12DialogWindowFUlUl(ipl::System::getDialog(), MESG_ERROR_NWC24_FATAL,
                                            MESG_CMN_OK);
        *reinterpret_cast<int*>(address + 0xac) = 0x18;
        *reinterpret_cast<int*>(address + 0xa4) = 2;
    }
    *reinterpret_cast<int*>(address + 0xa8) += 1;
}

extern "C" void fistt_fadein__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    if (*reinterpret_cast<int*>(static_cast<char*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            static_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c, 0)) + 0x14) != 1 &&
        *reinterpret_cast<int*>(static_cast<char*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            static_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c, 2)) + 0x14) != 1 &&
        *reinterpret_cast<int*>(static_cast<char*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            static_cast<char*>(*reinterpret_cast<void**>(address + 0xa0)) + 0x28c, 0)) + 0x14) != 1) {
        *reinterpret_cast<int*>(address + 0xa4) = 2;
    }
}

extern "C" void onInitFriendList__Q33ipl5scene7AddressFv(void* self) {
    char* address = static_cast<char*>(self);
    char* stringPool = lbl_81647538;
    wchar_t wiiId[24];
    wchar_t displayName[24];
    memset(wiiId, 0, 0x30);
    memset(displayName, 0, 0x30);
    ipl::utility::CharacterCode::WiiIdToUTF16(
        wiiId,
        *reinterpret_cast<u64*>(static_cast<char*>(*reinterpret_cast<void**>(address + 0x274)) +
                                  0x7d68));

    int destinationIndex = 0;
    int sourceIndex = 0;
    for (int i = 0; i < 4; i++) {
        displayName[destinationIndex++] = wiiId[sourceIndex++];
    }
    displayName[destinationIndex++] = L' ';
    sourceIndex = 4;
    for (int i = 0; i < 4; i++) {
        displayName[destinationIndex++] = wiiId[sourceIndex++];
    }
    displayName[destinationIndex++] = L' ';
    sourceIndex = 8;
    for (int i = 0; i < 4; i++) {
        displayName[destinationIndex++] = wiiId[sourceIndex++];
    }
    displayName[destinationIndex++] = L' ';
    sourceIndex = 12;
    for (int i = 0; i < 4; i++) {
        displayName[destinationIndex++] = wiiId[sourceIndex++];
    }

    set_textbox__Q33ipl5scene7AddressFPCcPCw(
        static_cast<ipl::scene::Address*>(self), stringPool + 0x501,
        displayName);
    set_page_text__Q33ipl5scene7AddressFPCci(static_cast<ipl::scene::Address*>(self),
                                              stringPool + 0x50c,
                                              *reinterpret_cast<int*>(address + 0xb0) + 1);

    const char** friendNames = reinterpret_cast<const char**>(stringPool + 0x3c);
    unsigned int friendIndex = 0;
    int objectOffset = 0;
    do {
        char* miiObject = address + objectOffset + 0xe4;
        set_friend__Q33ipl5scene7AddressFPCcUlUlRQ43ipl5scene7Address6MiiObjb(
            static_cast<ipl::scene::Address*>(self), friendNames[friendIndex], friendIndex,
            friendIndex, miiObject, false);
        if (*reinterpret_cast<unsigned char*>(address + friendIndex + 0xc4) != 0) {
            static_cast<ipl::layout::Animator*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                static_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c,
                friendIndex + 6))
                ->initAnmFrame();
        } else {
            static_cast<ipl::layout::Animator*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                static_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c,
                friendIndex + 0x15))
                ->initAnmFrame();
        }
        friendIndex++;
        objectOffset += 0x28;
    } while (friendIndex < 5);

    *reinterpret_cast<int*>(address + 0xb0) = 0;
    *reinterpret_cast<int*>(address + 0xb8) = 0;
    *reinterpret_cast<int*>(address + 0xb4) = 20;
    ipl::scene::Button* button = reinterpret_cast<ipl::scene::Button*>(
        ipl::System::getScene(5));
    button->animation(0x17);
    button->animation(0x18);

    if (*reinterpret_cast<int*>(address + 0x88) == 0) {
        *reinterpret_cast<int*>(address + 0xac) = 1;
    } else if (*reinterpret_cast<int*>(static_cast<char*>(
                                               *reinterpret_cast<void**>(address + 0x274)) +
                                           0x7d70) == 0) {
        *reinterpret_cast<int*>(address + 0xac) = 1;
    } else {
        *reinterpret_cast<int*>(address + 0xac) = 0;
    }

    int mode = *reinterpret_cast<int*>(address + 0x88);
    if (mode == 0) {
        goto init_friend_list_mode_zero;
    }
    if (mode < 0) {
        goto init_friend_list_mode_done;
    }
    if (mode >= 3) {
        goto init_friend_list_mode_done;
    }
    goto init_friend_list_mode_other;

init_friend_list_mode_zero: {
        void* frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            static_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c, 0);
        initFrame__Q33ipl7utility15FrameControllerFv(frame);
        *reinterpret_cast<int*>(static_cast<char*>(frame) + 0x14) = 1;
    }
    goto init_friend_list_mode_done;

init_friend_list_mode_other: {
        void* frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            static_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c, 2);
        initFrame__Q33ipl7utility15FrameControllerFv(frame);
        *reinterpret_cast<int*>(static_cast<char*>(frame) + 0x14) = 1;
        void* dialogLayout = *reinterpret_cast<void**>(address + 0xa0);
        frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            static_cast<char*>(dialogLayout) + 0x28c, 0);
        initFrame__Q33ipl7utility15FrameControllerFv(frame);
        *reinterpret_cast<int*>(static_cast<char*>(frame) + 0x14) = 1;
    }

init_friend_list_mode_done:;
}

extern "C" void stt_cover_normal__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    if (*reinterpret_cast<unsigned char*>(address + 0x84) != 0) {
        changePage_onDrag__Q33ipl5scene7AddressFv(self);
    } else {
        ipl::scene::Button* button = static_cast<ipl::scene::Button*>(ipl::System::getScene(5));
        if (button->isActive()) {
            button->update();
        }
    }
    if (*reinterpret_cast<int*>(address + 0xac) == 1) {
        if (ipl::System::getMasterController()->down(ipl::controller::BTN_NEXT_RIGHT)) {
            ipl::snd::sSystem.startSE(lbl_8164798E);
            onNextPage__Q33ipl5scene7AddressFv(self);
        } else if (ipl::System::getMasterController()->down(ipl::controller::BTN_NEXT_LEFT)) {
            ipl::snd::sSystem.startSE(lbl_81647A4D);
            onPreviousPage__Q33ipl5scene7AddressFv(self);
        }
    }
}

extern "C" void stt_cover_forward__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    void* layout = *reinterpret_cast<void**>(address + 0x8c);
    void* animator = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
        reinterpret_cast<char*>(layout) + 0x28c, 4);
    if (*reinterpret_cast<int*>(reinterpret_cast<char*>(animator) + 0x14) != 1) {
        *reinterpret_cast<unsigned char*>(address + 0xe1) = 0;
        if (*reinterpret_cast<unsigned char*>(address + 0x84) == 0) {
            *reinterpret_cast<int*>(address + 0xac) = 4;
        } else {
            *reinterpret_cast<int*>(address + 0xac) = 10;
        }
    } else if (*reinterpret_cast<unsigned char*>(address + 0x84) != 0) {
        changePage_onDrag__Q33ipl5scene7AddressFv(self);
    }
}

extern "C" void stt_cover_backward__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    void* animator = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
        reinterpret_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c, 4);
    if (*reinterpret_cast<int*>(reinterpret_cast<char*>(animator) + 0x14) != 1) {
        nw4r::math::_VEC2 offset = {-sAddressVEC2.x, -sAddressVEC2.y};
        ipl::math::VEC2 translate(offset);
        nw4r::lyt::Pane* pane = reinterpret_cast<ipl::layout::Object*>(
                                    *reinterpret_cast<void**>(address + 0x8c))
                                    ->GetRootPane()
                                    ->FindPaneByName(lbl_81647A61, true);
        add_translate__Q33ipl5scene7AddressFPQ34nw4r3lyt4PaneRCQ33ipl4math4VEC2(self, pane,
                                                                                 translate);
        *reinterpret_cast<unsigned char*>(address + 0xe1) = 1;
        *reinterpret_cast<int*>(address + 0xb4) += 1;
        *reinterpret_cast<int*>(address + 0xac) = 1;
    } else if (*reinterpret_cast<unsigned char*>(address + 0x84) != 0) {
        changePage_onDrag__Q33ipl5scene7AddressFv(self);
    }
}

extern "C" void stt_normal__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    ipl::scene::Button* button = static_cast<ipl::scene::Button*>(ipl::System::getScene(5));
    if (button->isActive()) {
        button->update();
    }
    if (*reinterpret_cast<int*>(address + 0xac) == 4) {
        update__Q33ipl3gui11PaneManagerFv(*reinterpret_cast<void**>(address + 0x98));
        if (ipl::System::getMasterController()->down(ipl::controller::BTN_NEXT_RIGHT)) {
            ipl::snd::sSystem.startSE(lbl_8164798E);
            onNextPage__Q33ipl5scene7AddressFv(self);
        } else if (ipl::System::getMasterController()->down(ipl::controller::BTN_NEXT_LEFT)) {
            ipl::snd::sSystem.startSE(lbl_81647A4D);
            onPreviousPage__Q33ipl5scene7AddressFv(self);
        }
    }
}

extern "C" void stt_forward__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    void* layout = *reinterpret_cast<void**>(address + 0x8c);
    void* animator = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
        reinterpret_cast<char*>(layout) + 0x28c, 5);
    if (*reinterpret_cast<int*>(reinterpret_cast<char*>(animator) + 0x14) != 1) {
        *reinterpret_cast<int*>(address + 0xb8) += 1;
        if (*reinterpret_cast<unsigned char*>(address + 0x84) == 0) {
            *reinterpret_cast<int*>(address + 0xac) = 4;
        } else {
            *reinterpret_cast<int*>(address + 0xac) = 10;
        }
    } else if (*reinterpret_cast<unsigned char*>(address + 0x84) != 0) {
        changePage_onDrag__Q33ipl5scene7AddressFv(self);
    }
}

extern "C" void stt_backward__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* data = lbl_81647538;
    char* address = reinterpret_cast<char*>(self);
    void* animator = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
        reinterpret_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c, 5);
    if (*reinterpret_cast<int*>(reinterpret_cast<char*>(animator) + 0x14) != 1) {
        *reinterpret_cast<int*>(address + 0xb4) += 1;
        ipl::math::VEC2 translate;
        translate.y = -sAddressVEC2.y;
        translate.x = -sAddressVEC2.x;
        nw4r::lyt::Pane* pane = reinterpret_cast<ipl::layout::Object*>(
                                    *reinterpret_cast<void**>(address + 0x8c))
                                    ->GetRootPane()
                                    ->FindPaneByName(data + 0x529, true);
        add_translate__Q33ipl5scene7AddressFPQ34nw4r3lyt4PaneRCQ33ipl4math4VEC2(
            self, pane, translate);
        set_page_text__Q33ipl5scene7AddressFPCci(
            self, data + 0x50c,
            *reinterpret_cast<int*>(address + 0xb0) + 1);
        const char** names = reinterpret_cast<const char**>(data + 0x3c);
        unsigned int index = 0;
        int objectOffset = 0;
        int nameIndex = 0;
        do {
            set_friend__Q33ipl5scene7AddressFPCcUlUlRQ43ipl5scene7Address6MiiObjb(
                self, names[nameIndex],
                index + *reinterpret_cast<int*>(address + 0xb0) * 5, index,
                address + objectOffset + 0xe4, false);
            index++;
            nameIndex++;
            objectOffset += 0x28;
        } while (index < 5);
        if (*reinterpret_cast<unsigned char*>(address + 0x84) == 0) {
            *reinterpret_cast<int*>(address + 0xac) = 4;
        } else {
            *reinterpret_cast<int*>(address + 0xac) = 10;
        }
    } else if (*reinterpret_cast<unsigned char*>(address + 0x84) != 0) {
        changePage_onDrag__Q33ipl5scene7AddressFv(self);
    }
}

extern "C" void stt_loop_forward__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    void* layout = *reinterpret_cast<void**>(address + 0x8c);
    void* animator = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
        reinterpret_cast<char*>(layout) + 0x28c, 4);
    if (*reinterpret_cast<int*>(reinterpret_cast<char*>(animator) + 0x14) != 1) {
        nw4r::math::VEC2 offset(-sAddressVEC2.x, -sAddressVEC2.y);
        ipl::math::VEC2 translate(offset);
        nw4r::lyt::Pane* pane = static_cast<ipl::layout::Object*>(layout)
                                    ->GetRootPane()
                                    ->FindPaneByName(lbl_81647A61, true);
        add_translate__Q33ipl5scene7AddressFPQ34nw4r3lyt4PaneRCQ33ipl4math4VEC2(
            self, pane, translate);
        set_page_text__Q33ipl5scene7AddressFPCci(
            self, lbl_81647538 + 0x50c,
            *reinterpret_cast<int*>(address + 0xb0) + 1);
        reset_gui__Q33ipl5scene7AddressFb(self, false);
        unsigned int friendIndex = 0;
        int objectOffset = 0;
        int nameOffset = 0;
        char* names = lbl_81647538 + 0x3c;
        do {
            set_friend__Q33ipl5scene7AddressFPCcUlUlRQ43ipl5scene7Address6MiiObjb(
                self, *reinterpret_cast<const char**>(names + nameOffset),
                friendIndex + *reinterpret_cast<int*>(address + 0xb0) * 5,
                friendIndex, address + objectOffset + 0xe4, false);
            friendIndex++;
            nameOffset += 4;
            objectOffset += 0x28;
        } while (friendIndex < 5);
        *reinterpret_cast<unsigned char*>(address + 0xe1) = 1;
        *reinterpret_cast<int*>(address + 0xb4) = 0x14;
        *reinterpret_cast<int*>(address + 0xac) = 1;
    } else if (*reinterpret_cast<unsigned char*>(address + 0x84) != 0) {
        changePage_onDrag__Q33ipl5scene7AddressFv(self);
    }
}

extern "C" void stt_loop_backward__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    void* layout = *reinterpret_cast<void**>(address + 0x8c);
    void* animator = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
        reinterpret_cast<char*>(layout) + 0x28c, 4);
    if (*reinterpret_cast<int*>(reinterpret_cast<char*>(animator) + 0x14) != 1) {
        *reinterpret_cast<unsigned char*>(address + 0xe1) = 0;
        *reinterpret_cast<int*>(address + 0xb8) = 0x13;
        if (*reinterpret_cast<unsigned char*>(address + 0x84) == 0) {
            *reinterpret_cast<int*>(address + 0xac) = 4;
        } else {
            *reinterpret_cast<int*>(address + 0xac) = 10;
        }
    } else if (*reinterpret_cast<unsigned char*>(address + 0x84) != 0) {
        changePage_onDrag__Q33ipl5scene7AddressFv(self);
    }
}

extern "C" void stt_decide__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    ipl::utility::FrameController* animator = static_cast<ipl::utility::FrameController*>(
        List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            static_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c,
            *reinterpret_cast<int*>(address + 0xbc) + 0x10));
    if (*reinterpret_cast<int*>(reinterpret_cast<char*>(animator) + 0x14) != 1) {
        animator = static_cast<ipl::utility::FrameController*>(
            List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                static_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c,
                *reinterpret_cast<int*>(address + 0xbc) + 0x1f));
        if (*reinterpret_cast<int*>(reinterpret_cast<char*>(animator) + 0x14) != 1) {
            reset_gui__Q33ipl5scene7AddressFb(self, true);
            int mode = *reinterpret_cast<int*>(address + 0x88);
            if (mode != 0) {
                if (mode < 0) {
                    goto stt_decide_done;
                }
                if (mode >= 3) {
                    goto stt_decide_done;
                }
                goto set_friend_info;
            }
            {
                createChildScene__Q33ipl5scene4BaseFiPQ33ipl5scene4BasePQ33ipl5scene4BasePv(
                    self, 0x17, self, NULL, NULL);
                ipl::utility::FrameController* childAnimator =
                    static_cast<ipl::utility::FrameController*>(
                    List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                        static_cast<char*>(*reinterpret_cast<void**>(address + 0x9c)) + 0x28c,
                        0));
                childAnimator->play();
                *reinterpret_cast<int*>(address + 0xac) = 0xc;
            }
            goto stt_decide_done;
        set_friend_info:
            {
            ipl::scene::LetterWriter* letterWriter =
                static_cast<ipl::scene::LetterWriter*>(
                    ipl::System::getScene(ipl::SCENE_LETTER_WRITER));
            letterWriter->setFriendInfo(
                (*reinterpret_cast<ipl::scene::FriendListCache**>(address + 0x274))
                    ->getInfo(*reinterpret_cast<int*>(address + 0xc0)));
            animator = static_cast<ipl::utility::FrameController*>(
                List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    static_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c,
                    3));
            animator->play();
            animator = static_cast<ipl::utility::FrameController*>(
                List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    static_cast<char*>(*reinterpret_cast<void**>(address + 0xa0)) + 0x28c,
                    1));
            animator->play();
            *reinterpret_cast<int*>(address + 0xac) = 0x1a;
            }
        }
    }
stt_decide_done:
    return;
}

extern "C" void stt_release__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    static_cast<ipl::gui::PaneManager*>(*reinterpret_cast<void**>(address + 0x98))->init();
    int counterOffset = 0;
    int index = 0;
    do {
        if (*reinterpret_cast<unsigned char*>(address + index + 0xc4) != 0) {
            ipl::layout::Animator* animator = static_cast<ipl::layout::Animator*>(
                List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    static_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c,
                    index + 6));
            animator->initAnmFrame();
        } else {
            ipl::layout::Animator* animator = static_cast<ipl::layout::Animator*>(
                List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    static_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c,
                    index + 0x15));
            animator->initAnmFrame();
        }
        *reinterpret_cast<int*>(address + counterOffset + 0xcc) = 0;
        index++;
        counterOffset += 4;
    } while (index < 5);
    ipl::layout::Object* layout = *reinterpret_cast<ipl::layout::Object**>(address + 0x8c);
    SetVisible__Q34nw4r3lyt4PaneFb(
        layout->GetRootPane()->FindPaneByName(lbl_81647982, true), false);
    if (*reinterpret_cast<unsigned char*>(address + 0xe1) == 0) {
        goto release_state_four;
    }
    *reinterpret_cast<int*>(address + 0xac) = 1;
    goto release_state_done;
release_state_four:
    *reinterpret_cast<int*>(address + 0xac) = 4;
release_state_done:
    return;
}

extern "C" void stt_wait_child_cst__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    if (self->getChild() != 0) {
        ipl::layout::Object* layout = *reinterpret_cast<ipl::layout::Object**>(address + 0x9c);
        void* animator = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<char*>(layout) + 0x28c, 0);
        if (*reinterpret_cast<int*>(reinterpret_cast<char*>(animator) + 0x14) != 1) {
            *reinterpret_cast<int*>(address + 0xac) = 13;
            reset_gui__Q33ipl5scene7AddressFb(self, true);
            for (int index = 0; index < 5; index++) {
                *reinterpret_cast<int*>(address + 0xcc + index * 4) = 0;
            }
        }
    }
}

extern "C" void stt_wait_child_dst__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    if (self->getChild() == 0 && ipl::System::getSceneManager()->getReservedScene() == 0) {
        ipl::layout::Object* layout = *reinterpret_cast<ipl::layout::Object**>(address + 0x9c);
        void* animator = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<char*>(layout) + 0x28c, 1);
        initFrame__Q33ipl7utility15FrameControllerFv(animator);
        *reinterpret_cast<int*>(reinterpret_cast<char*>(animator) + 0x14) = 1;
        gui::EventHandler* event = reinterpret_cast<gui::EventHandler*>(self);
        if (event != 0) {
            event = reinterpret_cast<gui::EventHandler*>(address + 0x58);
        }
        static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->setEventHandler(event, 0);
        *reinterpret_cast<int*>(address + 0xac) = 0xe;
    }
}

extern "C" void stt_wait_child_fadeout__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    ipl::layout::Object* layout = *reinterpret_cast<ipl::layout::Object**>(address + 0x9c);
    void* animator = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
        reinterpret_cast<char*>(layout) + 0x28c, 1);
    if (*reinterpret_cast<int*>(reinterpret_cast<char*>(animator) + 0x14) != 1) {
        ipl::scene::Button* button = static_cast<ipl::scene::Button*>(ipl::System::getScene(5));
        button->setText(lbl_81647A6D, 0x29);
        button->animation(0x17);
        button->animation(0x18);
        if (*reinterpret_cast<unsigned char*>(address + 0xe1) != 0) {
            *reinterpret_cast<int*>(address + 0xac) = 1;
        } else {
            *reinterpret_cast<int*>(address + 0xac) = 4;
        }
    }
}

extern "C" void stt_msg_net__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    int dialogState = *reinterpret_cast<int*>(
        reinterpret_cast<char*>(ipl::System::getDialog()) + 0x24);
    if (dialogState == 2) {
        goto msg_net_complete;
    }
    if (dialogState >= 2) {
        goto msg_net_done;
    }
    if (dialogState >= 1) {
        goto msg_net_parental;
    }
    goto msg_net_done;
msg_net_complete:
    if (*reinterpret_cast<unsigned char*>(address + 0xe1) == 0) {
        goto msg_net_complete_flag_zero;
    }
    *reinterpret_cast<int*>(address + 0xac) = 1;
    goto msg_net_complete_state_done;
msg_net_complete_flag_zero:
    *reinterpret_cast<int*>(address + 0xac) = 4;
msg_net_complete_state_done:
    static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->animation(0x17);
    static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->animation(0x18);
    goto msg_net_done;
msg_net_parental: {
    SCParentalControlsInfo parental;
    if (SCGetParentalControl(&parental) == 0) {
        goto msg_net_parental_disabled;
    }
    if ((parental.enable & SC_PARENTAL_FLAG_ENABLED) == 0) {
        goto msg_net_parental_disabled;
    }
    static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->setEventHandler(0, 0);
    static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->animation(0x10);
    createChildScene__Q33ipl5scene4BaseFiPQ33ipl5scene4BasePQ33ipl5scene4BasePv(
        self, 0x1b, self, 0, reinterpret_cast<void*>(1));
    *reinterpret_cast<unsigned char*>(address + 0xe0) = 0;
    *reinterpret_cast<int*>(address + 0xac) = 0x10;
    goto msg_net_done;
msg_net_parental_disabled:
    ipl::System::getFader()->fadeOut();
    reserveAllSceneDestruction__Q33ipl5scene4BaseFiPv(self, 0x12,
                                                       reinterpret_cast<void*>(1));
    *reinterpret_cast<int*>(address + 0xac) = 0x1a;
}
msg_net_done:
    return;
}

extern "C" void stt_wait_parental__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    void* dialog = ipl::System::getScene(0x1b);
    if (dialog != 0) {
        int state = *reinterpret_cast<int*>(reinterpret_cast<char*>(dialog) + 0x70);
        if (state == 1) {
            goto parental_confirmed;
        }
        if (state < 1) {
            goto parental_done;
        }
        if (state >= 4) {
            goto parental_done;
        }
        goto parental_rejected;
parental_confirmed:
        *reinterpret_cast<unsigned char*>(address + 0xe0) = 1;
        *reinterpret_cast<int*>(address + 0xac) = 0x11;
        goto parental_done;
parental_rejected:
        *reinterpret_cast<unsigned char*>(address + 0xe0) = 0;
        *reinterpret_cast<int*>(address + 0xac) = 0x11;
    }
parental_done:
    return;
}

extern "C" void stt_wait_parental_dst__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    if (self->getChild() == 0) {
        if (*reinterpret_cast<unsigned char*>(address + 0xe0) != 0) {
            ipl::System::getFader()->fadeOut();
            reserveAllSceneDestruction__Q33ipl5scene4BaseFiPv(self, 0x12,
                                                               reinterpret_cast<void*>(1));
            *reinterpret_cast<int*>(address + 0xac) = 0x1a;
        } else {
            static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->animation(0xf);
            gui::EventHandler* event = reinterpret_cast<gui::EventHandler*>(self);
            if (event != 0) {
                event = reinterpret_cast<gui::EventHandler*>(address + 0x58);
            }
            static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->setEventHandler(event, 0);
            if (*reinterpret_cast<unsigned char*>(address + 0xe1) != 0) {
                *reinterpret_cast<int*>(address + 0xac) = 1;
            } else {
                *reinterpret_cast<int*>(address + 0xac) = 4;
            }
            static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->animation(0x17);
            static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->animation(0x18);
        }
    }
}

extern "C" void stt_msg_wc__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    int dialogState = *reinterpret_cast<int*>(
        reinterpret_cast<char*>(ipl::System::getDialog()) + 0x24);
    if (dialogState == 2) {
        goto msg_wc_complete;
    }
    if (dialogState >= 2) {
        goto msg_wc_done;
    }
    if (dialogState >= 1) {
        goto msg_wc_parental;
    }
    goto msg_wc_done;
msg_wc_complete:
    if (*reinterpret_cast<unsigned char*>(address + 0xe1) == 0) {
        goto msg_wc_complete_flag_zero;
    }
    *reinterpret_cast<int*>(address + 0xac) = 1;
    goto msg_wc_complete_state_done;
msg_wc_complete_flag_zero:
    *reinterpret_cast<int*>(address + 0xac) = 4;
msg_wc_complete_state_done:
    static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->animation(0x17);
    static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->animation(0x18);
    goto msg_wc_done;
msg_wc_parental: {
    SCParentalControlsInfo parental;
    if (SCGetParentalControl(&parental) == 0) {
        goto msg_wc_parental_disabled;
    }
    if ((parental.enable & SC_PARENTAL_FLAG_ENABLED) == 0) {
        goto msg_wc_parental_disabled;
    }
    static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->setEventHandler(0, 0);
    static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->animation(0x10);
    createChildScene__Q33ipl5scene4BaseFiPQ33ipl5scene4BasePQ33ipl5scene4BasePv(
        self, 0x1b, self, 0, reinterpret_cast<void*>(1));
    *reinterpret_cast<unsigned char*>(address + 0xe0) = 0;
    *reinterpret_cast<int*>(address + 0xac) = 0x13;
    goto msg_wc_done;
msg_wc_parental_disabled:
    ipl::System::getFader()->fadeOut();
    reserveAllSceneDestruction__Q33ipl5scene4BaseFiPv(self, 0x12,
                                                       reinterpret_cast<void*>(4));
    *reinterpret_cast<int*>(address + 0xac) = 0x1a;
}
msg_wc_done:
    return;
}

extern "C" void stt_wait_parental_wc__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    void* dialog = ipl::System::getScene(0x1b);
    if (dialog != 0) {
        int state = *reinterpret_cast<int*>(reinterpret_cast<char*>(dialog) + 0x70);
        if (state == 1) {
            goto parental_wc_confirmed;
        }
        if (state < 1) {
            goto parental_wc_done;
        }
        if (state >= 4) {
            goto parental_wc_done;
        }
        goto parental_wc_rejected;
parental_wc_confirmed:
        *reinterpret_cast<unsigned char*>(address + 0xe0) = 1;
        *reinterpret_cast<int*>(address + 0xac) = 0x14;
        goto parental_wc_done;
parental_wc_rejected:
        *reinterpret_cast<unsigned char*>(address + 0xe0) = 0;
        *reinterpret_cast<int*>(address + 0xac) = 0x14;
    }
parental_wc_done:
    return;
}

extern "C" void stt_wait_parental_dst_wc__Q33ipl5scene7AddressFv(
    ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    if (self->getChild() == 0) {
        if (*reinterpret_cast<unsigned char*>(address + 0xe0) != 0) {
            ipl::System::getFader()->fadeOut();
            reserveAllSceneDestruction__Q33ipl5scene4BaseFiPv(self, 0x12,
                                                               reinterpret_cast<void*>(4));
            *reinterpret_cast<int*>(address + 0xac) = 0x1a;
        } else {
            static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->animation(0xf);
            gui::EventHandler* event = reinterpret_cast<gui::EventHandler*>(self);
            if (event != 0) {
                event = reinterpret_cast<gui::EventHandler*>(address + 0x58);
            }
            static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->setEventHandler(event, 0);
            if (*reinterpret_cast<unsigned char*>(address + 0xe1) != 0) {
                *reinterpret_cast<int*>(address + 0xac) = 1;
            } else {
                *reinterpret_cast<int*>(address + 0xac) = 4;
            }
            static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->animation(0x17);
            static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->animation(0x18);
        }
    }
}

extern "C" void stt_msg_nwc24_error__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    int state = *reinterpret_cast<int*>(reinterpret_cast<char*>(ipl::System::getDialog()) + 0x24);
    switch (state) {
    case 1:
        if (*reinterpret_cast<unsigned char*>(address + 0xe1) == 0) {
            goto msg_nwc24_not_e1;
        }
        *reinterpret_cast<int*>(address + 0xac) = 1;
        goto msg_nwc24_state_done;
    msg_nwc24_not_e1:
        *reinterpret_cast<int*>(address + 0xac) = 4;
    msg_nwc24_state_done:
        static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->animation(0x17);
        static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->animation(0x18);
        break;
    }
}

extern "C" void stt_msg_fi_full__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    int state = *reinterpret_cast<int*>(reinterpret_cast<char*>(ipl::System::getDialog()) + 0x24);
    switch (state) {
    case 1:
        if (*reinterpret_cast<unsigned char*>(address + 0xe1) == 0) {
            goto msg_fi_full_not_e1;
        }
        *reinterpret_cast<int*>(address + 0xac) = 1;
        goto msg_fi_full_state_done;
    msg_fi_full_not_e1:
        *reinterpret_cast<int*>(address + 0xac) = 4;
    msg_fi_full_state_done:
        static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->animation(0x17);
        static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->animation(0x18);
        break;
    }
}

extern "C" void stt_msg_parental__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    int state = *reinterpret_cast<int*>(reinterpret_cast<char*>(ipl::System::getDialog()) + 0x24);
    switch (state) {
    case 1:
        if (*reinterpret_cast<unsigned char*>(address + 0xe1) == 0) {
            goto msg_parental_not_e1;
        }
        *reinterpret_cast<int*>(address + 0xac) = 1;
        goto msg_parental_state_done;
    msg_parental_not_e1:
        *reinterpret_cast<int*>(address + 0xac) = 4;
    msg_parental_state_done:
        static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->animation(0x17);
        static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->animation(0x18);
        break;
    }
}

extern "C" void stt_msg_open_failure__Q33ipl5scene7AddressFv(
    ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    int dialogState =
        *reinterpret_cast<int*>(reinterpret_cast<char*>(ipl::System::getDialog()) + 0x24);
    switch (dialogState) {
    default:
        goto open_failure_done;
    case 1: {
        ipl::scene::Button* button =
            static_cast<ipl::scene::Button*>(ipl::System::getScene(5));
        ipl::scene::MailAddressSelect* mailAddressSelect =
            static_cast<ipl::scene::MailAddressSelect*>(ipl::System::getScene(8));
        int mode = *reinterpret_cast<int*>(address + 0x88);
        if (mode == 1) {
            goto open_failure_mode_one;
        }
        if (mode >= 1) {
            goto open_failure_positive;
        }
        if (mode >= 0) {
            goto open_failure_mode_zero;
        }
        goto open_failure_finish;
    open_failure_positive:
        if (mode >= 3) {
            goto open_failure_finish;
        }
        goto open_failure_mode_two;
    open_failure_mode_zero:
        if (mailAddressSelect != 0) {
            mailAddressSelect->finishAddress();
        }
        button->reserveAnm(0x10);
        button->reserveAnm(0xb);
        goto open_failure_finish;
    open_failure_mode_one:
        button->reserveAnm(0xc);
        button->reserveAnm(0xb);
        goto open_failure_finish;
    open_failure_mode_two:
        button->reserveAnm(0xc);
        button->reserveText(0, 0x13b);
        button->reserveText(1, 0x33);
        button->reserveAnm(0xf);
    open_failure_finish:
        button->animation(0x19);
        button->animation(0x1a);
        *reinterpret_cast<int*>(address + 0xac) = 0x1a;
    }
    }
open_failure_done:
    return;
}

extern "C" void set_friend__Q33ipl5scene7AddressFPCcUlUlRQ43ipl5scene7Address6MiiObjb(
    ipl::scene::Address* self, const char* paneName, unsigned int friendIndex,
    unsigned int buttonIndex, void* miiObj, bool isDrag) {
    bool showMii = false;
    char* address = reinterpret_cast<char*>(self);
    u16 emptyText[1];
    emptyText[0] = 0;
    const wchar_t* text = reinterpret_cast<const wchar_t*>(emptyText);
    ipl::scene::FriendListCache* cache =
        *reinterpret_cast<ipl::scene::FriendListCache**>(address + 0x274);
    unsigned char* flags = reinterpret_cast<unsigned char*>(cache) + 0x7d00;
    if (flags[friendIndex] != 0) {
        const NWC24FriendInfo* info = &cache->getInfo(friendIndex);
        text = reinterpret_cast<const wchar_t*>(info->attr.name);
        showMii = info->attr.status == 2;
        if (*reinterpret_cast<int*>(address + 0x88) == 2) {
            showMii = showMii & (info->attr.type == 1);
        }
        if (isDrag) {
            if (showMii) {
                ipl::layout::Animator* animator =
                    static_cast<ipl::layout::Animator*>(
                        List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                            static_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) +
                                0x28c,
                            static_cast<unsigned short>(buttonIndex + 0x24)));
                animator->initAnmFrame(lbl_816947D8);
            } else {
                ipl::layout::Animator* animator =
                    static_cast<ipl::layout::Animator*>(
                        List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                            static_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) +
                                0x28c,
                            static_cast<unsigned short>(buttonIndex + 0x24)));
                animator->initAnmFrame(lbl_816947E0);
            }
        } else {
            if (showMii) {
                ipl::layout::Animator* animator =
                    static_cast<ipl::layout::Animator*>(
                        List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                            static_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) +
                                0x28c,
                            static_cast<unsigned short>(buttonIndex + 6)));
                animator->initAnmFrame();
            } else {
                ipl::layout::Animator* animator =
                    static_cast<ipl::layout::Animator*>(
                        List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                            static_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) +
                                0x28c,
                            static_cast<unsigned short>(buttonIndex + 0x15)));
                animator->initAnmFrame();
            }
            *reinterpret_cast<unsigned char*>(address + buttonIndex + 0xc4) = showMii;
        }
        if (*reinterpret_cast<unsigned char*>(address + 0x84) == 0 ||
            friendIndex != static_cast<unsigned int>(
                               *reinterpret_cast<int*>(address + 0x74) +
                               *reinterpret_cast<int*>(address + 0x70) * 5)) {
            set__Q43ipl5scene7Address6MiiObjFUx(miiObj, info->attr.fdId);
        }
    } else {
        if (isDrag) {
            ipl::layout::Animator* animator =
                static_cast<ipl::layout::Animator*>(
                    List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                        static_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c,
                        static_cast<unsigned short>(buttonIndex + 0x24)));
            animator->initAnmFrame(lbl_816947D8);
        } else {
            *reinterpret_cast<unsigned char*>(address + buttonIndex + 0xc4) = 0;
            ipl::layout::Animator* animator =
                static_cast<ipl::layout::Animator*>(
                    List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                        static_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c,
                        static_cast<unsigned short>(buttonIndex + 0x15)));
            animator->initAnmFrame();
        }
        reset__Q43ipl5scene7Address6MiiObjFv(miiObj);
    }
    if (*reinterpret_cast<unsigned char*>(address + 0x84) == 0 ||
        friendIndex != static_cast<unsigned int>(
                           *reinterpret_cast<int*>(address + 0x74) +
                           *reinterpret_cast<int*>(address + 0x70) * 5)) {
        set_textbox__Q33ipl5scene7AddressFPCcPCw(self, paneName, text);
    } else {
        set_textbox__Q33ipl5scene7AddressFPCcPCw(self, paneName, L"");
        reset__Q43ipl5scene7Address6MiiObjFv(miiObj);
    }
}

void ipl::scene::LetterWriter::setFriendInfo(const NWC24FriendInfo& info) {
    mbToFriend = true;
    mFriendInfo = info;
}

extern "C" void stt_drag__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    update__Q33ipl3gui11PaneManagerFv(*reinterpret_cast<void**>(address + 0x98));
    if (*reinterpret_cast<int*>(address + 0xac) == 10) {
        changePage_onDrag__Q33ipl5scene7AddressFv(self);
    }
}

void ipl::scene::Address::destroy() {
    getFriendCache()->fin();
}

extern "C" asm void isValidId__Q33ipl5scene15FriendListCacheFRCUx() {
    nofralloc
    lis r3, smArg__Q23ipl6System@ha
    addi r3, r3, smArg__Q23ipl6System@l
    lbz r0, 0x2bc(r3)
    cmpwi r0, 0
    beq isValidId_L1
    li r3, 0
    b isValidId_L2
isValidId_L1:
    lwz r3, 0x8c(r3)
isValidId_L2:
    lwz r5, 0(r4)
    lwz r6, 4(r4)
    b checkUserId__Q33ipl5nwc247ManagerFUx
}

extern "C" asm void getErrCode__Q33ipl5scene15FriendListCacheCFv() {
    nofralloc
    lis r3, smArg__Q23ipl6System@ha
    addi r3, r3, smArg__Q23ipl6System@l
    lbz r0, 0x2bc(r3)
    cmpwi r0, 0
    beq getErrCode_L1
    li r3, 0
    b getErrCode_L2
getErrCode_L1:
    lwz r3, 0x8c(r3)
getErrCode_L2:
    b getErrCode__Q33ipl5nwc247ManagerFv
}

extern "C" asm void fin__Q33ipl5scene15FriendListCacheFv() {
    nofralloc
    addis r3, r3, 1
    lbz r0, -0x6288(r3)
    cmpwi r0, 0
    beqlr
    lis r3, smArg__Q23ipl6System@ha
    addi r3, r3, smArg__Q23ipl6System@l
    lbz r0, 0x2bc(r3)
    cmpwi r0, 0
    beq fin_L1
    li r3, 0
    b fin_L2
fin_L1:
    lwz r3, 0x8c(r3)
fin_L2:
    b close__Q33ipl5nwc247ManagerFv
    blr
}

extern "C" asm void del__Q33ipl5scene15FriendListCacheFUl() {
    nofralloc
    add r5, r3, r4
    li r0, 0
    stb r0, 0x7d00(r5)
    lis r5, smArg__Q23ipl6System@ha
    addi r5, r5, smArg__Q23ipl6System@l
    lwz r6, 0x7d70(r3)
    addi r0, r6, -1
    stw r0, 0x7d70(r3)
    lbz r0, 0x2bc(r5)
    cmpwi r0, 0
    beq del_L1
    li r3, 0
    b del_L2
del_L1:
    lwz r3, 0x8c(r5)
del_L2:
    b deleteFriendInfo__Q33ipl5nwc247ManagerFUl
}

extern "C" asm void initCalcFadeout__Q33ipl5scene7AddressFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r3, smArg__Q23ipl6System@ha
    li r4, 5
    stw r0, 0x14(r1)
    addi r3, r3, smArg__Q23ipl6System@l
    lwz r3, 0x64(r3)
    bl getScene__Q33ipl5scene7ManagerFi
    li r4, 0
    li r5, 0
    bl setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" ipl::scene::FaderSceneCommand calcFadeout__Q33ipl5scene7AddressFv(
    ipl::scene::Address* self) {
    bool animationsStopped;
    int result;
    if (ipl::System::getFader()->getStatus() == EGG::Fader::PREPARE_OUT) {
        result = 0;
        animationsStopped = false;
        if (*reinterpret_cast<int*>(static_cast<char*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                static_cast<char*>(*reinterpret_cast<void**>(reinterpret_cast<char*>(self) + 0x8c)) +
                    0x28c,
                1)) +
                0x14) != 1 &&
            *reinterpret_cast<int*>(static_cast<char*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                static_cast<char*>(*reinterpret_cast<void**>(reinterpret_cast<char*>(self) + 0x8c)) +
                    0x28c,
                3)) +
                0x14) != 1) {
            animationsStopped = true;
        }
        if (animationsStopped &&
            *reinterpret_cast<int*>(static_cast<char*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                static_cast<char*>(*reinterpret_cast<void**>(reinterpret_cast<char*>(self) + 0xa0)) +
                    0x28c,
                1)) +
                0x14) != 1) {
            result = 1;
        }
    } else {
        result = ipl::System::getFader()->getStatus() == EGG::Fader::PREPARE_IN;
    }
    return static_cast<ipl::scene::FaderSceneCommand>(result);
}

extern "C" asm void calcCommonAfter__Q33ipl5scene7AddressFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r3, 0x8c(r3)
    bl calc__Q33ipl6layout6ObjectFv
    lwz r3, 0x9c(r31)
    bl calc__Q33ipl6layout6ObjectFv
    lwz r3, 0xa0(r31)
    bl calc__Q33ipl6layout6ObjectFv
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

void ipl::scene::Address::draw() {
    char* stringPool = lbl_81647538;
    int drawLayer = *reinterpret_cast<int*>(
        reinterpret_cast<char*>(ipl::System::getSceneManager()) + 0x100);
    if (drawLayer == ipl::scene::DRAW_LAYER_2) {
        ipl::utility::Graphics::setOrtho(0);
        nw4r::lyt::Pane* pane = mLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(
            stringPool + 0x4d4, true);
        for (int index = mPageCount; index >= 1; index--) {
            ipl::math::VEC2 translate;
            translate.y = sAddressVEC2.y * static_cast<float>(index);
            translate.x = sAddressVEC2.x * static_cast<float>(index);
            nw4r::math::VEC2 paneTranslate(reinterpret_cast<const float*>(&translate));
            SetTranslate__Q34nw4r3lyt4PaneFRCQ34nw4r4math4VEC2(pane, &paneTranslate);
            pane->CalculateMtx(*mLayout->getDrawInfo());
            mLayout->draw(pane);
        }
        mLayout->draw(stringPool + 0x4dd);
        if (static_cast<unsigned int>(mState - 5) <= 1) {
            mLayout->draw(stringPool + 0x4e6);
        }
        int startIndex = 0;
        int state = mState;
        if (state == 4) {
            goto start_index_done;
        }
        if (state < 4) {
            if (state >= 2) {
                goto start_index_set;
            }
            goto start_index_done;
        }
        if (state >= 7) {
            goto start_index_done;
        }
    start_index_set:
        startIndex = 1;
    start_index_done:
        pane = mLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(stringPool + 0x4ef, true);
        for (int index = startIndex; index < mFriendCount + startIndex;
             index++) {
            ipl::math::VEC2 translate = sAddressVEC2 * static_cast<float>(-index);
            SetTranslate__Q34nw4r3lyt4PaneFRCQ34nw4r4math4VEC2(pane, &translate);
            pane->CalculateMtx(*mLayout->getDrawInfo());
            mLayout->draw(pane);
        }
        pane = mLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(stringPool + 0x4f8, true);
        state = mState;
        if (state >= 9) {
            goto draw_last_pane;
        }
        if (state >= 7) {
            goto draw_repeated_panes;
        }
        goto draw_last_pane;
    draw_repeated_panes:
        for (int index = 1; index < 20; index++) {
            pane->SetTranslate(sAddressVEC2 * static_cast<float>(-index));
            pane->CalculateMtx(*mLayout->getDrawInfo());
            mLayout->draw(pane);
        }
        goto draw_panes_done;
    draw_last_pane:
        pane->SetTranslate(sAddressVEC2 * static_cast<float>(
                               -(mFriendCount + startIndex)));
        pane->CalculateMtx(*mLayout->getDrawInfo());
        mLayout->draw(stringPool + 0x4f8);
    draw_panes_done:
        mPaneLayout->draw();
        mCursorLayout->draw();
    } else if (drawLayer == ipl::scene::DRAW_LAYER_3) {
        ipl::utility::Graphics::setOrtho(0);
        int state = mState;
        if (state == 9) {
            goto no_text;
        }
        if (state < 9) {
            if (state == 4) {
                goto no_text;
            }
            if (state >= 4) {
                goto draw_text;
            }
            if (state >= 1) {
                goto draw_text;
            }
            goto no_text;
        }
        if (state >= 11) {
            goto no_text;
        }
    draw_text:
        mLayout->draw(stringPool + 0x44a);
    no_text:;
    }
}

extern "C" asm void __ct__Q43ipl5scene7Address6MiiObjFv() {
    nofralloc
    li r0, 0
    stw r0, 0x20(r3)
    blr
}

extern "C" asm void __dt__Q43ipl5scene7Address6MiiObjFv() {
    stwu r1, -0x10(r1)
    mflr r0
    cmpwi r3, 0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 8(r1)
    mr r30, r3
    beq miio_dt_done
    lwz r3, 0x20(r3)
    cmpwi r3, 0
    beq miio_dt_skip_object
    li r4, 1
    bl __dt__Q33ipl6nigaoe6ObjectFv
miio_dt_skip_object:
    cmpwi r31, 0
    ble miio_dt_done
    mr r3, r30
    bl __dl__FPv
miio_dt_done:
    mr r3, r30
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void init__Q43ipl5scene7Address6MiiObjFPQ34nw4r3lyt4Pane(
    void*, nw4r::lyt::Pane*) {
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    mr r3, r4
    lwz r12, 0(r4)
    lwz r12, 0x5c(r12)
    mtctr r12
    bctrl
    stw r3, 0x24(r31)
    mr r4, r31
    li r5, 0
    bl GetTexture__Q34nw4r3lyt8MaterialCFP9_GXTexObjUc
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void reset__Q43ipl5scene7Address6MiiObjFv(void* self) {
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r0, 0x20(r3)
    cmpwi r0, 0
    beq miio_reset_done
    lwz r3, 0x24(r3)
    mr r5, r31
    li r4, 0
    bl SetTexture__Q34nw4r3lyt8MaterialFUcRC9_GXTexObj
    lwz r3, 0x20(r31)
    li r4, 1
    bl __dt__Q33ipl6nigaoe6ObjectFv
    li r0, 0
    stw r0, 0x20(r31)
miio_reset_done:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void create_callback__Q43ipl5scene7Address6MiiObjFPQ33ipl6nigaoe6ObjectPv() {
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 8(r1)
    mr r30, r3
    lwz r0, 0x20(r4)
    cmpwi r0, 0
    beq miio_create_store
    mr r3, r0
    li r4, 1
    bl __dt__Q33ipl6nigaoe6ObjectFv
miio_create_store:
    stw r30, 0x20(r31)
    addi r5, r30, 0x18
    lwz r3, 0x24(r31)
    li r4, 0
    bl SetTexture__Q34nw4r3lyt8MaterialFUcRC9_GXTexObj
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void set__Q43ipl5scene7Address6MiiObjFUx(void* self,
                                                           unsigned long long id) {
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    addi r4, r1, 8
    stw r31, 0x2c(r1)
    mr r31, r3
    addi r3, r1, 0x12
    stw r5, 8(r1)
    li r5, 8
    stw r6, 0xc(r1)
    bl memcpy
    addi r3, r1, 0x12
    addi r4, r1, 0x10
    bl RFLSearchOfficialData
    cmpwi r3, 0
    beq miio_set_reset
    lis r4, smArg__Q23ipl6System@ha
    lis r8, create_callback__Q43ipl5scene7Address6MiiObjFPQ33ipl6nigaoe6ObjectPv@ha
    addi r4, r4, smArg__Q23ipl6System@l
    lha r7, 0x10(r1)
    lwz r3, 0x70(r4)
    mr r9, r31
    lwz r4, 0x28(r4)
    addi r8, r8, create_callback__Q43ipl5scene7Address6MiiObjFPQ33ipl6nigaoe6ObjectPv@l
    li r5, 0x4c
    li r6, 0x4c
    bl create__Q33ipl6nigaoe7ManagerFPQ23EGG4HeapiiiPFPQ33ipl6nigaoe6ObjectPvPv
    b miio_set_done
miio_set_reset:
    mr r3, r31
    bl reset__Q43ipl5scene7Address6MiiObjFv
miio_set_done:
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

extern "C" int get_button_no__Q33ipl5scene7AddressFPCc(void*, const char* paneName) {
    int result = -1;
    for (int i = 0; i < 5; i++) {
        if (strcmp(lbl_81647614[i], paneName) == 0) {
            result = i;
            break;
        }
    }
    return result;
}

extern "C" int get_button_space_no__Q33ipl5scene7AddressFPCc(void*, const char* paneName) {
    int result = -1;
    for (int i = 0; i < 4; i++) {
        if (strcmp(lbl_81647664[i], paneName) == 0) {
            result = i;
            break;
        }
    }
    return result;
}

extern "C" void reset_gui__Q33ipl5scene7AddressFb(ipl::scene::Address* self, bool reset) {
    static_cast<ipl::gui::PaneManager*>(
        *reinterpret_cast<void**>(reinterpret_cast<char*>(self) + 0x98))->init();
    int friendOffset = 0;
    int animationIndex = 0;
    do {
        ipl::layout::Animator* animator = static_cast<ipl::layout::Animator*>(
            List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(*reinterpret_cast<char**>(reinterpret_cast<char*>(self) + 0x8c) + 0x28c, animationIndex + 6));
        animator->initAnmFrame();
        static_cast<ipl::layout::Animator*>(
            List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(*reinterpret_cast<char**>(reinterpret_cast<char*>(self) + 0x8c) + 0x28c, animationIndex + 6))
            ->calc();

        animator = static_cast<ipl::layout::Animator*>(
            List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(*reinterpret_cast<char**>(reinterpret_cast<char*>(self) + 0x8c) + 0x28c, animationIndex + 0xb));
        animator->initAnmFrame();
        static_cast<ipl::layout::Animator*>(
            List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(*reinterpret_cast<char**>(reinterpret_cast<char*>(self) + 0x8c) + 0x28c, animationIndex + 0xb))
            ->calc();

        animator = static_cast<ipl::layout::Animator*>(
            List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(*reinterpret_cast<char**>(reinterpret_cast<char*>(self) + 0x8c) + 0x28c, animationIndex + 0x10));
        animator->initAnmFrame();
        static_cast<ipl::layout::Animator*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            *reinterpret_cast<char**>(reinterpret_cast<char*>(self) + 0x8c) + 0x28c, animationIndex + 0x10))->calc();

        animator = static_cast<ipl::layout::Animator*>(
            List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(*reinterpret_cast<char**>(reinterpret_cast<char*>(self) + 0x8c) + 0x28c, animationIndex + 0x15));
        animator->initAnmFrame();
        static_cast<ipl::layout::Animator*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            *reinterpret_cast<char**>(reinterpret_cast<char*>(self) + 0x8c) + 0x28c, animationIndex + 0x15))->calc();

        animator = static_cast<ipl::layout::Animator*>(
            List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(*reinterpret_cast<char**>(reinterpret_cast<char*>(self) + 0x8c) + 0x28c, animationIndex + 0x1a));
        animator->initAnmFrame();
        static_cast<ipl::layout::Animator*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            *reinterpret_cast<char**>(reinterpret_cast<char*>(self) + 0x8c) + 0x28c, animationIndex + 0x1a))->calc();

        animator = static_cast<ipl::layout::Animator*>(
            List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(*reinterpret_cast<char**>(reinterpret_cast<char*>(self) + 0x8c) + 0x28c, animationIndex + 0x1f));
        animator->initAnmFrame();
        static_cast<ipl::layout::Animator*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            *reinterpret_cast<char**>(reinterpret_cast<char*>(self) + 0x8c) + 0x28c, animationIndex + 0x1f))->calc();

        char* friendData = reinterpret_cast<char*>(self) + friendOffset;
        if (*reinterpret_cast<int*>(friendData + 0xcc) != 0 && reset) {
            if (*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(self) + animationIndex + 0xc4) != 0) {
                ipl::utility::FrameController* frame = static_cast<ipl::utility::FrameController*>(
                    List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                        *reinterpret_cast<char**>(reinterpret_cast<char*>(self) + 0x8c) + 0x28c,
                        animationIndex + 0xb));
                frame->initFrame();
                frame->restart();
            } else {
                ipl::utility::FrameController* frame = static_cast<ipl::utility::FrameController*>(
                    List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                        *reinterpret_cast<char**>(reinterpret_cast<char*>(self) + 0x8c) + 0x28c,
                        animationIndex + 0x1a));
                frame->initFrame();
                frame->restart();
            }
        } else {
            if (*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(self) + animationIndex + 0xc4) != 0) {
                animator = static_cast<ipl::layout::Animator*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    *reinterpret_cast<char**>(reinterpret_cast<char*>(self) + 0x8c) + 0x28c,
                    animationIndex + 6));
                animator->initAnmFrame();
                static_cast<ipl::layout::Animator*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    *reinterpret_cast<char**>(reinterpret_cast<char*>(self) + 0x8c) + 0x28c,
                    animationIndex + 6))->calc();
            } else {
                animator = static_cast<ipl::layout::Animator*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    *reinterpret_cast<char**>(reinterpret_cast<char*>(self) + 0x8c) + 0x28c,
                    animationIndex + 0x15));
                animator->initAnmFrame();
                static_cast<ipl::layout::Animator*>(List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    *reinterpret_cast<char**>(reinterpret_cast<char*>(self) + 0x8c) + 0x28c,
                    animationIndex + 0x15))->calc();
            }
        }
        animationIndex++;
        *reinterpret_cast<int*>(friendData + 0xcc) = 0;
        friendOffset += 4;
    } while (animationIndex < 5);
}

extern "C" bool isReleasableArea__Q33ipl5scene7AddressFii(ipl::scene::Address* self, int page,
                                                          int index) {
    char* address = reinterpret_cast<char*>(self);
    if (page < 0 || page >= 20) {
        return false;
    }
    if (reinterpret_cast<unsigned char*>(address)[0xe1] != 0) {
        return false;
    }
    if (index < 0) {
        goto address_invalid;
    }
    if (index < 5) {
        goto address_valid;
    }
address_invalid:
    return false;
address_valid:
    if (page == *reinterpret_cast<int*>(address + 0x70) &&
        index == *reinterpret_cast<int*>(address + 0x74)) {
        return true;
    }
    unsigned char* cachedFriends =
        *reinterpret_cast<unsigned char**>(address + 0x274);
    if (cachedFriends[index + page * 5 + 32000] != 0) {
        return false;
    }
    return static_cast<unsigned char>(address[0x84]) == 1;
}

extern "C" unsigned int is_selectable__Q33ipl5scene7AddressFUl(ipl::scene::Address* self,
                                                                 unsigned int index) {
    char* address = reinterpret_cast<char*>(self);
    int mode = *reinterpret_cast<int*>(address + 0x88);
    if (mode == 1) {
        goto selectable_mode_one;
    }
    if (mode < 1) {
        if (mode >= 0) {
            goto selectable_mode_zero;
        }
        goto selectable_invalid;
    }
    if (mode >= 3) {
        goto selectable_invalid;
    }
    goto selectable_mode_two;
selectable_mode_zero:
    {
        unsigned char* friends = *reinterpret_cast<unsigned char**>(address + 0x274);
        return *(friends + index + 32000);
    }
selectable_mode_one:
    {
        unsigned char* friends = *reinterpret_cast<unsigned char**>(address + 0x274);
        if (*(friends + index + 32000) != 0) {
            int* info = reinterpret_cast<int*>(friends + index * 0x140);
            return static_cast<unsigned int>(__cntlzw(info[1] - 2)) >> 5;
        }
        return 0;
    }
selectable_mode_two:
    {
        unsigned char* friends = *reinterpret_cast<unsigned char**>(address + 0x274);
        if (*(friends + index + 32000) != 0) {
            unsigned int* info = reinterpret_cast<unsigned int*>(friends + index * 0x140);
            unsigned int result = 0;
            if (info[1] == 2U) {
                if (info[0] == 1U) {
                    result = 1;
                }
            }
            return result;
        }
        return 0;
    }
selectable_invalid:
    return 0;
}

extern "C" void onEventDerived__Q33ipl5scene7AddressFUlUlPCQ33ipl10controller9Interface(
    ipl::scene::Address* self, unsigned int componentId, int event,
    const ipl::controller::Interface* controller) {
    char* address = reinterpret_cast<char*>(self);
    gui::Manager* manager = *reinterpret_cast<gui::Manager**>(address + 0x5c);
    gui::Component* component = manager->getComponent(componentId);
    const char* paneName =
        static_cast<gui::PaneComponent*>(component)->getPane()->GetName();

    if (event == 1) {
        goto address_drag_event;
    }
    if (event < 1) {
        if (event >= 0) {
            goto address_trig_event;
        }
        goto address_event_done;
    }
    if (event >= 3) {
        goto address_event_done;
    }
    goto address_clear_drag;

address_trig_event:
    if (controller == NULL) {
        goto address_event_done;
    }
    if (!controller->downTrg(0x00100800)) {
        goto address_drag_event;
    }
        ipl::scene::Button* button =
            static_cast<ipl::scene::Button*>(ipl::System::getScene(5));
        int state = *reinterpret_cast<int*>(address + 0xac);
        if (state == 1 || state == 4) {
            if (ipl::scene::Button::cmpButtonName(paneName, 5) == 0) {
                ipl::scene::MailAddressSelect* mail =
                    static_cast<ipl::scene::MailAddressSelect*>(ipl::System::getScene(8));
                button->animation(0x1b);
                int mode = *reinterpret_cast<int*>(address + 0x88);
                ipl::utility::FrameController* frameZero;
                ipl::utility::FrameController* frameMain;
                if (mode == 1) {
                    goto address_mode_one;
                }
                if (mode >= 1) {
                    goto address_mode_two_check;
                }
                if (mode >= 0) {
                    goto address_mode_zero;
                }
                goto address_mode_common;

address_mode_two_check:
                if (mode >= 3) {
                    goto address_mode_common;
                }
                goto address_mode_two;

address_mode_zero:
                if (mail != NULL) {
                    mail->finishAddress();
                }
                frameZero = static_cast<ipl::utility::FrameController*>(
                    List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                        reinterpret_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) +
                            0x28c,
                        1));
                frameZero->initFrame();
                *reinterpret_cast<int*>(reinterpret_cast<char*>(frameZero) + 0x14) = 1;
                button->reserveAnm(0x10);
                button->reserveAnm(0xb);
                goto address_mode_common;

address_mode_one:
                frameMain = static_cast<ipl::utility::FrameController*>(
                    List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                        reinterpret_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) +
                            0x28c,
                        3));
                frameMain->initFrame();
                *reinterpret_cast<int*>(reinterpret_cast<char*>(frameMain) + 0x14) = 1;
                frameMain = static_cast<ipl::utility::FrameController*>(
                    List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                        reinterpret_cast<char*>(*reinterpret_cast<void**>(address + 0xa0)) +
                            0x28c,
                        1));
                frameMain->initFrame();
                *reinterpret_cast<int*>(reinterpret_cast<char*>(frameMain) + 0x14) = 1;
                button->reserveAnm(0xc);
                button->reserveAnm(0xb);
                goto address_mode_common;

address_mode_two:
                frameMain = static_cast<ipl::utility::FrameController*>(
                    List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                        reinterpret_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) +
                            0x28c,
                        3));
                frameMain->initFrame();
                *reinterpret_cast<int*>(reinterpret_cast<char*>(frameMain) + 0x14) = 1;
                frameMain = static_cast<ipl::utility::FrameController*>(
                    List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                        reinterpret_cast<char*>(*reinterpret_cast<void**>(address + 0xa0)) +
                            0x28c,
                        1));
                frameMain->initFrame();
                *reinterpret_cast<int*>(reinterpret_cast<char*>(frameMain) + 0x14) = 1;
                button->reserveAnm(0xc);
                button->reserveText(0, 0x13b);
                button->reserveText(1, 0x33);
                button->reserveAnm(0xf);

address_mode_common:
                button->animation(0x19);
                button->animation(0x1a);
                ipl::snd::sSystem.startSE(lbl_81647538 + 0x5a1);
                *reinterpret_cast<int*>(address + 0xac) = 0x1a;
            } else if (ipl::scene::Button::cmpButtonName(paneName, 7) == 0) {
                *reinterpret_cast<int*>(address + 0xc0) = -1;
                entry_friend__Q33ipl5scene7AddressFv(self);
            } else if (ipl::scene::Button::cmpButtonName(paneName, 9) == 0) {
                button->animation(0x13);
                ipl::snd::sSystem.startSE(lbl_8164798E);
                onNextPage__Q33ipl5scene7AddressFv(self);
            } else if (ipl::scene::Button::cmpButtonName(paneName, 10) == 0) {
                button->animation(0x14);
                ipl::snd::sSystem.startSE(lbl_81647A4D);
                onPreviousPage__Q33ipl5scene7AddressFv(self);
            }
        }

address_drag_event:
    if (*reinterpret_cast<unsigned char*>(address + 0x84) != 0 &&
        (controller == NULL ||
         controller == ipl::System::getControllerManager()->getController(
                            *reinterpret_cast<int*>(address + 0x6c)))) {
        if (ipl::scene::Button::cmpButtonName(paneName, 10) == 0) {
            if (*reinterpret_cast<int*>(address + 0x7c) < 0) {
                *reinterpret_cast<int*>(address + 0x7c) = 0;
            }
        } else if (ipl::scene::Button::cmpButtonName(paneName, 9) == 0 &&
                   *reinterpret_cast<int*>(address + 0x78) < 0) {
            *reinterpret_cast<int*>(address + 0x78) = 0;
        }
    }
    goto address_event_done;

address_clear_drag:
    if (*reinterpret_cast<unsigned char*>(address + 0x84) != 0 &&
        (controller == NULL ||
         controller == ipl::System::getControllerManager()->getController(
                            *reinterpret_cast<int*>(address + 0x6c)))) {
        if (ipl::scene::Button::cmpButtonName(paneName, 10) == 0) {
            *reinterpret_cast<int*>(address + 0x7c) = -1;
        } else if (ipl::scene::Button::cmpButtonName(paneName, 9) == 0) {
            *reinterpret_cast<int*>(address + 0x78) = -1;
        }
    }

address_event_done:
    return;
}

extern "C" void onNextPage__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    char* dataBase = lbl_81647538;
    int state = *reinterpret_cast<int*>(address + 0xac);
    if (state != 4) {
        if (state < 4) {
            if (state >= 2) {
                goto on_next_page_done;
            }
            if (state >= 0) {
                goto on_next_page_first;
            }
            goto on_next_page_done;
        }
        if (state == 10) {
            goto on_next_page_normal;
        }
        goto on_next_page_done;
    }

on_next_page_normal:
    if (*reinterpret_cast<int*>(address + 0xb0) < 0x13) {
        *reinterpret_cast<unsigned int*>(address + 0xb0) += 1;
        *reinterpret_cast<int*>(address + 0xb4) -= 1;
        nw4r::lyt::Pane* pane =
            static_cast<ipl::layout::Object*>(*reinterpret_cast<void**>(address + 0x8c))
                ->GetRootPane()
                ->FindPaneByName(dataBase + 0x529, true);
        add_translate__Q33ipl5scene7AddressFPQ34nw4r3lyt4PaneRCQ33ipl4math4VEC2(
            self, pane, sAddressVEC2);
        void* animator = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c, 5);
        *reinterpret_cast<int*>(reinterpret_cast<char*>(animator) + 0x18) = 0;
        animator = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c, 5);
        initFrame__Q33ipl7utility15FrameControllerFv(animator);
        *reinterpret_cast<int*>(reinterpret_cast<char*>(animator) + 0x14) = 1;
        set_page_text__Q33ipl5scene7AddressFPCci(
            self, dataBase + 0x50c, *reinterpret_cast<int*>(address + 0xb0) + 1);
        set_page_text__Q33ipl5scene7AddressFPCci(
            self, dataBase + 0x5b0, *reinterpret_cast<int*>(address + 0xb0));
        reset_gui__Q33ipl5scene7AddressFb(self, false);

        unsigned int index = 0;
        const char* const* names = reinterpret_cast<const char* const*>(dataBase + 0x3c);
        const char* const* otherNames = reinterpret_cast<const char* const*>(dataBase + 0x8c);
        int objectOffset = 0;
        do {
            set_friend__Q33ipl5scene7AddressFPCcUlUlRQ43ipl5scene7Address6MiiObjb(
                self, names[index],
                index + *reinterpret_cast<int*>(address + 0xb0) * 5, index,
                address + objectOffset + 0xe4, false);
            set_friend__Q33ipl5scene7AddressFPCcUlUlRQ43ipl5scene7Address6MiiObjb(
                self, otherNames[index],
                index + (*reinterpret_cast<int*>(address + 0xb0) - 1) * 5, index,
                address + objectOffset + 0x1ac, true);
            index++;
            objectOffset += 0x28;
        } while (index < 5);
        *reinterpret_cast<int*>(address + 0xac) = 5;
    } else {
        *reinterpret_cast<unsigned int*>(address + 0xb0) = 0;
        *reinterpret_cast<unsigned int*>(address + 0xb8) = 0;
        *reinterpret_cast<unsigned char*>(address + 0xe1) = 1;
        void* animator = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c, 4);
        *reinterpret_cast<int*>(reinterpret_cast<char*>(animator) + 0x18) = 1;
        animator = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c, 4);
        initFrame__Q33ipl7utility15FrameControllerFv(animator);
        *reinterpret_cast<int*>(reinterpret_cast<char*>(animator) + 0x14) = 1;
        reset_gui__Q33ipl5scene7AddressFb(self, true);
        *reinterpret_cast<int*>(address + 0xac) = 7;
    }

    goto on_next_page_done;

on_next_page_first:
    *reinterpret_cast<int*>(address + 0xb4) -= 1;
    nw4r::lyt::Pane* pane =
        static_cast<ipl::layout::Object*>(*reinterpret_cast<void**>(address + 0x8c))
            ->GetRootPane()
            ->FindPaneByName(dataBase + 0x529, true);
    add_translate__Q33ipl5scene7AddressFPQ34nw4r3lyt4PaneRCQ33ipl4math4VEC2(
        self, pane, sAddressVEC2);
    void* animator = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
        reinterpret_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c, 4);
    *reinterpret_cast<int*>(reinterpret_cast<char*>(animator) + 0x18) = 0;
    animator = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
        reinterpret_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c, 4);
    initFrame__Q33ipl7utility15FrameControllerFv(animator);
    *reinterpret_cast<int*>(reinterpret_cast<char*>(animator) + 0x14) = 1;
    reset_gui__Q33ipl5scene7AddressFb(self, true);

    unsigned int index = 0;
    const char* const* names = reinterpret_cast<const char* const*>(dataBase + 0x3c);
    int objectOffset = 0;
    do {
        set_friend__Q33ipl5scene7AddressFPCcUlUlRQ43ipl5scene7Address6MiiObjb(
            self, names[index],
            index + *reinterpret_cast<int*>(address + 0xb0) * 5, index,
            address + objectOffset + 0xe4, false);
        index++;
        objectOffset += 0x28;
    } while (index < 5);
    *reinterpret_cast<int*>(address + 0xac) = 2;

on_next_page_done:
    return;
}

extern "C" void onPreviousPage__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* dataBase = lbl_81647538;
    char* address = reinterpret_cast<char*>(self);
    int state = *reinterpret_cast<int*>(address + 0xac);
    if (state != 4) {
        if (state < 4) {
            if (state == 1) {
                goto on_previous_page_wrap;
            }
            goto on_previous_page_done;
        }
        if (state != 10) {
            goto on_previous_page_done;
        }
    }

    if (*reinterpret_cast<int*>(address + 0xb0) < 1) {
        void* animator = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c, 4);
        *reinterpret_cast<int*>(reinterpret_cast<char*>(animator) + 0x18) = 1;
        animator = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c, 4);
        initFrame__Q33ipl7utility15FrameControllerFv(animator);
        *reinterpret_cast<int*>(reinterpret_cast<char*>(animator) + 0x14) = 1;
        reset_gui__Q33ipl5scene7AddressFb(self, true);
        *reinterpret_cast<int*>(address + 0xac) = 3;
    } else {
        *reinterpret_cast<int*>(address + 0xb0) -= 1;
        *reinterpret_cast<int*>(address + 0xb8) -= 1;
        void* animator = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c, 5);
        *reinterpret_cast<int*>(reinterpret_cast<char*>(animator) + 0x18) = 1;
        animator = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
            reinterpret_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c, 5);
        initFrame__Q33ipl7utility15FrameControllerFv(animator);
        *reinterpret_cast<int*>(reinterpret_cast<char*>(animator) + 0x14) = 1;
        set_page_text__Q33ipl5scene7AddressFPCci(
            self, dataBase + 0x5b0, *reinterpret_cast<int*>(address + 0xb0) + 1);
        reset_gui__Q33ipl5scene7AddressFb(self, true);

        unsigned int index = 0;
        const char* const* names = reinterpret_cast<const char* const*>(dataBase + 0x8c);
        int objectOffset = 0;
        do {
            set_friend__Q33ipl5scene7AddressFPCcUlUlRQ43ipl5scene7Address6MiiObjb(
                self, names[index],
                index + *reinterpret_cast<int*>(address + 0xb0) * 5, index,
                address + objectOffset + 0x1ac, true);
            index++;
            objectOffset += 0x28;
        } while (index < 5);
        *reinterpret_cast<int*>(address + 0xac) = 6;
    }
    goto on_previous_page_done;

on_previous_page_wrap:
    *reinterpret_cast<int*>(address + 0xb0) = 0x13;
    *reinterpret_cast<int*>(address + 0xb4) = 0;
    *reinterpret_cast<unsigned char*>(address + 0xe1) = 0;
    float scale = lbl_816947DC;
    float* axes = &lbl_81698B50;
    nw4r::math::_VEC2 rawOffset;
    rawOffset.y = axes[1] * scale;
    rawOffset.x = axes[0] * scale;
    ipl::math::VEC2 offset(rawOffset);
    nw4r::lyt::Pane* pane =
        static_cast<ipl::layout::Object*>(*reinterpret_cast<void**>(address + 0x8c))
            ->GetRootPane()
            ->FindPaneByName(dataBase + 0x529, true);
    add_translate__Q33ipl5scene7AddressFPQ34nw4r3lyt4PaneRCQ33ipl4math4VEC2(self, pane, offset);
    void* animator = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
        reinterpret_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c, 4);
    *reinterpret_cast<int*>(reinterpret_cast<char*>(animator) + 0x18) = 0;
    animator = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
        reinterpret_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) + 0x28c, 4);
    initFrame__Q33ipl7utility15FrameControllerFv(animator);
    *reinterpret_cast<int*>(reinterpret_cast<char*>(animator) + 0x14) = 1;
    set_page_text__Q33ipl5scene7AddressFPCci(
        self, dataBase + 0x50c, *reinterpret_cast<int*>(address + 0xb0) + 1);
    reset_gui__Q33ipl5scene7AddressFb(self, false);

    unsigned int index = 0;
    const char* const* names = reinterpret_cast<const char* const*>(dataBase + 0x3c);
    int objectOffset = 0;
    do {
        set_friend__Q33ipl5scene7AddressFPCcUlUlRQ43ipl5scene7Address6MiiObjb(
            self, names[index],
            index + *reinterpret_cast<int*>(address + 0xb0) * 5, index,
            address + objectOffset + 0xe4, false);
        index++;
        objectOffset += 0x28;
    } while (index < 5);
    *reinterpret_cast<int*>(address + 0xac) = 8;

on_previous_page_done:
    return;
}

extern "C" void set_err_msg__Q33ipl5scene7AddressFPwUl8NWC24Err(
    ipl::scene::Address*, wchar_t* outErrMsg, unsigned int outErrMsgLen, int nwc24Err) {
    memset(outErrMsg, 0, outErrMsgLen * sizeof(wchar_t));
    const wchar_t* message = ipl::System::getMessage(400);
    wcsncat(outErrMsg, message, outErrMsgLen - wcslen(outErrMsg));

    wchar_t nwc24ErrStr[32];
    memset(nwc24ErrStr, 0, sizeof(nwc24ErrStr));
    swprintf(nwc24ErrStr, sizeof(nwc24ErrStr) / sizeof(wchar_t), lbl_81647AF2,
             ipl::System::getNwc24Manager()->getErrCode());
    wcsncat(outErrMsg, nwc24ErrStr, outErrMsgLen - wcslen(outErrMsg));

    unsigned int errMsgId = 400;
    if (nwc24Err == -31) {
        errMsgId = 0x19a;
    } else if (nwc24Err < -31) {
        if (nwc24Err >= -32) {
            errMsgId = 0x1c5;
        }
    } else if (nwc24Err == -6) {
        errMsgId = 0x1c5;
    }
    wcsncat(outErrMsg, ipl::System::getMessage(errMsgId),
            outErrMsgLen - wcslen(outErrMsg));
}

extern "C" void entry_friend__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    if (*reinterpret_cast<int*>(address + 0x88) == 0) {
        ipl::scene::Button* button =
            static_cast<ipl::scene::Button*>(ipl::System::getScene(5));
        SCParentalControlsInfo parental;
        BOOL parentalInfoAvailable = SCGetParentalControl(&parental);
        unsigned int registeredFriendCount =
            *reinterpret_cast<unsigned int*>(
                *reinterpret_cast<char**>(address + 0x274) + 0x7d70);
        ipl::snd::sSystem.startSE(lbl_81647A78);
        if (*reinterpret_cast<unsigned int*>(address + 0xc0) == 0xffffffffU) {
            button->animation(0x1d);
        }
        if (!ipl::ncd::NCDSetting::getConnectEnableFlag()) {
            ipl::System::getDialog()->callBtn2(0x145, 0x146, 0x25, false);
            *reinterpret_cast<int*>(address + 0xac) = 0xf;
        } else if ((SCGetWCFlags() & 1) == 0) {
            ipl::System::getDialog()->callBtn2(0x17e, 0x146, 0x25, false);
            *reinterpret_cast<int*>(address + 0xac) = 0x12;
        } else if (parentalInfoAvailable && (parental.enable & SC_PARENTAL_FLAG_ENABLED) &&
                   (SCGetNetContentRestrictions() & 2) != 0) {
            ipl::System::getDialog()->callBtn1(0x14c, 0x2e);
            *reinterpret_cast<int*>(address + 0xac) = 0x17;
        } else {
            int checkResult = check__Q33ipl5scene15FriendListCacheFv(
                *reinterpret_cast<ipl::scene::FriendListCache**>(address + 0x274));
            if (checkResult == -31 ||
                *reinterpret_cast<int*>(
                    *reinterpret_cast<char**>(address + 0x274) + 0x9d74) == -32 ||
                *reinterpret_cast<int*>(
                    *reinterpret_cast<char**>(address + 0x274) + 0x9d74) == -6) {
                wchar_t errorMessage[0x400] = {};
                set_err_msg__Q33ipl5scene7AddressFPwUl8NWC24Err(
                    self, errorMessage, 0x400,
                    *reinterpret_cast<int*>(
                        *reinterpret_cast<char**>(address + 0x274) + 0x9d74));
                ipl::System::getDialog()->callBtn1(errorMessage, 0x2e);
                *reinterpret_cast<int*>(address + 0xac) = 0x15;
            } else if (registeredFriendCount >= 100) {
                ipl::System::getDialog()->callBtn1(0x50, 0x2e);
                *reinterpret_cast<int*>(address + 0xac) = 0x16;
            } else {
                createChildScene__Q33ipl5scene4BaseFiPQ33ipl5scene4BasePQ33ipl5scene4BasePv(
                    self, 0x18, self, 0, 0);
                button->reserveAnm(0x10);
                button->reserveText(0, 0x13b);
                button->reserveAnm(0xb);
                button->setEventHandler(0, 0);
                void* frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                    *reinterpret_cast<char**>(address + 0x9c) + 0x28c, 0);
                initFrame__Q33ipl7utility15FrameControllerFv(frame);
                *reinterpret_cast<int*>(reinterpret_cast<char*>(frame) + 0x14) = 1;
                *reinterpret_cast<int*>(address + 0xac) = 0xc;
            }
        }
        button->animation(0x19);
        button->animation(0x1a);
    }
}

extern "C" void add_translate__Q33ipl5scene7AddressFPQ34nw4r3lyt4PaneRCQ33ipl4math4VEC2(
    void*, nw4r::lyt::Pane* pane, const ipl::math::VEC2& offset) {
    nw4r::ut::Rect projection;
    nw4r::ut::Rect projection4x3;
    ipl::System::getProjectionRect(&projection);
    ipl::System::getProjectionRect4x3(&projection4x3);
    nw4r::math::VEC3 translate;
    translate.x = pane->GetTranslate().x;
    translate.y = pane->GetTranslate().y;
    translate.z = pane->GetTranslate().z;
    translate.x += offset.x * projection4x3.GetWidth() / projection.GetWidth();
    translate.y += offset.y;
    SetTranslate__Q34nw4r3lyt4PaneFRCQ34nw4r4math4VEC3(pane, &translate);
}

#pragma dont_inline on
extern "C" void set_page_text__Q33ipl5scene7AddressFPCci(ipl::scene::Address* self,
                                                              const char* paneName, int page) {
    wchar_t digits[10];
    const wchar_t* digitSource = lbl_8160F650 - 1;
    wchar_t* digitDest = digits - 1;
    for (int i = 0; i < 5; i++) {
        digitDest[1] = digitSource[1];
        digitDest[2] = digitSource[2];
        digitDest += 2;
        digitSource += 2;
    }
    wchar_t text[6] = {};
    int textIndex = 0;
    if (page >= 10) {
        text[textIndex++] = digits[page / 10];
    }
    text[textIndex++] = digits[page % 10];
    text[textIndex++] = '/';
    text[textIndex++] = digits[2];
    text[textIndex++] = digits[0];
    text[textIndex] = 0;
    set_textbox__Q33ipl5scene7AddressFPCcPCw(self, paneName, text);
}
extern "C" void set_textbox__Q33ipl5scene7AddressFPCcPCw(ipl::scene::Address* self,
                                                          const char* paneName,
                                                          const wchar_t* text) {
    char* address = reinterpret_cast<char*>(self);
    void* layout = *reinterpret_cast<void**>(address + 0x8c);
    nw4r::lyt::Pane* root =
        *reinterpret_cast<nw4r::lyt::Pane**>(reinterpret_cast<char*>(layout) + 0x14);
    nw4r::lyt::TextBox* textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(
        root->FindPaneByName(paneName, true));
    textBox->SetString(text, 0);
}
#pragma dont_inline reset

extern "C" void reset_friend__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    int objectOffset = 0;
    unsigned int buttonIndex = 0;
    do {
        unsigned int page = *reinterpret_cast<unsigned int*>(address + 0xb0);
        unsigned int friendIndex = buttonIndex + page * 5;
        const char* buttonName = lbl_81647614[buttonIndex];
        char* object = address + objectOffset + 0xe4;
        set_friend__Q33ipl5scene7AddressFPCcUlUlRQ43ipl5scene7Address6MiiObjb(
            self, buttonName, friendIndex, buttonIndex, object, false);
        buttonIndex++;
        objectOffset += 0x28;
    } while (buttonIndex < 5);
}

extern "C" void start_trig_event__Q33ipl5scene7AddressFPCc(
    ipl::scene::Address* self, const char* paneName) {
    char* address = reinterpret_cast<char*>(self);
    ipl::scene::Button* button =
        static_cast<ipl::scene::Button*>(ipl::System::getScene(5));
    int buttonNo = get_button_no__Q33ipl5scene7AddressFPCc(self, paneName);
    if (*reinterpret_cast<int*>(address + 0xac) == 4) {
        int mode = *reinterpret_cast<int*>(address + 0x88);
        unsigned int page = *reinterpret_cast<unsigned int*>(address + 0xb0);
        if (mode == 0) {
            if (buttonNo == -1 ||
                is_selectable__Q33ipl5scene7AddressFUl(self, buttonNo + page * 5) == 0) {
                if (buttonNo != -1) {
                    *reinterpret_cast<int*>(address + 0xbc) = buttonNo;
                    *reinterpret_cast<int*>(address + 0xc0) = buttonNo + page * 5;
                    entry_friend__Q33ipl5scene7AddressFv(self);
                }
            } else {
                button->animation(0x19);
                button->animation(0x1a);
                button->animation(0x10);
                button->reserveText(0, 0x13b);
                button->reserveAnm(0xb);
                button->setEventHandler(0, 0);
                unsigned int animationIndex =
                    *reinterpret_cast<unsigned char*>(address + buttonNo + 0xc4) == 0
                        ? buttonNo + 0x1f
                        : buttonNo + 0x10;
                ipl::utility::FrameController* animator =
                    static_cast<ipl::utility::FrameController*>(
                        List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                            static_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) +
                                0x28c,
                            animationIndex));
                animator->play();
                *reinterpret_cast<int*>(address + 0xbc) = buttonNo;
                *reinterpret_cast<int*>(address + 0xc0) = buttonNo + page * 5;
                ipl::snd::sSystem.startSE(lbl_81647A78);
                *reinterpret_cast<int*>(address + buttonNo * 4 + 0xcc) += 1;
                *reinterpret_cast<int*>(address + 0xac) = 9;
            }
        } else if (mode >= 0 && mode < 3) {
            if (buttonNo == -1 ||
                is_selectable__Q33ipl5scene7AddressFUl(self, buttonNo + page * 5) == 0) {
                if (buttonNo != -1) {
                    unsigned int friendIndex = buttonNo + page * 5;
                    ipl::scene::FriendListCache* cache =
                        *reinterpret_cast<ipl::scene::FriendListCache**>(address + 0x274);
                    if (*(reinterpret_cast<unsigned char*>(cache) + friendIndex + 32000) != 0) {
                        const NWC24FriendInfo& info = cache->getInfo(friendIndex);
                        if (mode == 1) {
                            callBtn1__Q23ipl12DialogWindowFUlUl(ipl::System::getDialog(),
                                                                0x57, 0x2e);
                        } else if (info.attr.type == 1) {
                            callBtn1__Q23ipl12DialogWindowFUlUl(ipl::System::getDialog(),
                                                                0x57, 0x2e);
                        } else {
                            callBtn1__Q23ipl12DialogWindowFUlUl(ipl::System::getDialog(),
                                                                0x22, 0x2e);
                        }
                        *reinterpret_cast<int*>(address + 0xac) = 0x19;
                    }
                }
            } else {
                button->animation(0xc);
                button->reserveText(0, 0x25);
                button->reserveText(1, 0x33);
                button->reserveAnm(0xf);
                button->animation(0x19);
                button->animation(0x1a);
                ipl::utility::FrameController* animator =
                    static_cast<ipl::utility::FrameController*>(
                        List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                            static_cast<char*>(*reinterpret_cast<void**>(address + 0x8c)) +
                                0x28c,
                            buttonNo + 0x10));
                animator->play();
                *reinterpret_cast<int*>(address + 0xbc) = buttonNo;
                *reinterpret_cast<int*>(address + 0xc0) = buttonNo + page * 5;
                ipl::snd::sSystem.startSE(lbl_81647A78);
                *reinterpret_cast<int*>(address + 0xac) = 9;
            }
        }
    }
}

extern "C" void start_point_event__Q33ipl5scene7AddressFPCcPQ33ipl10controller9Interface(
    ipl::scene::Address* self, const char* paneName, void* controller) {
    char* address = reinterpret_cast<char*>(self);
    int buttonNo = get_button_no__Q33ipl5scene7AddressFPCc(self, paneName);
    if (buttonNo != -1) {
        int mode = *reinterpret_cast<int*>(address + 0x88);
        if (mode == 0 ||
            (mode == 1 && is_selectable__Q33ipl5scene7AddressFUl(
                              self, buttonNo + *reinterpret_cast<int*>(address + 0xb0) * 5))) {
        on_point_event__Q33ipl5scene7AddressFiPQ33ipl10controller9Interface(self, buttonNo,
                                                                             controller);
        }
    }
}

extern "C" void start_left_event__Q33ipl5scene7AddressFPCc(ipl::scene::Address* self,
                                                            const char* paneName) {
    char* address = reinterpret_cast<char*>(self);
    int buttonNo = get_button_no__Q33ipl5scene7AddressFPCc(self, paneName);
    if (buttonNo != -1) {
        int mode = *reinterpret_cast<int*>(address + 0x88);
        if (mode == 0 ||
            (mode == 1 && is_selectable__Q33ipl5scene7AddressFUl(
                              self, buttonNo + *reinterpret_cast<int*>(address + 0xb0) * 5))) {
            left_point_event__Q33ipl5scene7AddressFi(self, buttonNo);
        }
    }
}

extern "C" void start_drag_point_event__Q33ipl5scene7AddressFPCcPQ33ipl10controller9Interface(
    ipl::scene::Address* self, const char* paneName, void* controller) {
    int buttonNo = get_button_no__Q33ipl5scene7AddressFPCc(self, paneName);
    if (buttonNo != -1 &&
        isReleasableArea__Q33ipl5scene7AddressFii(
            self, *reinterpret_cast<int*>(reinterpret_cast<char*>(self) + 0xb0), buttonNo)) {
        on_point_event__Q33ipl5scene7AddressFiPQ33ipl10controller9Interface(self, buttonNo,
                                                                             controller);
        *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(self) + 0x84) = 1;
    }
}

extern "C" void start_drag_left_event__Q33ipl5scene7AddressFPCc(ipl::scene::Address* self,
                                                                 const char* paneName) {
    int buttonNo = get_button_no__Q33ipl5scene7AddressFPCc(self, paneName);
    if (buttonNo != -1) {
        left_point_event__Q33ipl5scene7AddressFi(self, buttonNo);
        *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(self) + 0x84) = 1;
    }
}

extern "C" void start_release_event__Q33ipl5scene7AddressFPCc(ipl::scene::Address* self,
                                                               const char* paneName) {
    char* address = reinterpret_cast<char*>(self);
    int buttonNo;
    const char* dataBase = lbl_81647538;
    ipl::System::getScene(5);
    buttonNo = -1;
    if (paneName != 0) {
        buttonNo = get_button_no__Q33ipl5scene7AddressFPCc(self, paneName);
        if (buttonNo == -1) {
            buttonNo = get_button_space_no__Q33ipl5scene7AddressFPCc(self, paneName);
        }
    }
    switch (*reinterpret_cast<int*>(address + 0x88)) {
    case 0: {
        if (isReleasableArea__Q33ipl5scene7AddressFii(
                self, *reinterpret_cast<unsigned int*>(address + 0xb0), buttonNo)) {
            *reinterpret_cast<int*>(address + 0xbc) = buttonNo;
            unsigned int friendIndex =
                buttonNo + *reinterpret_cast<unsigned int*>(address + 0xb0) * 5;
            *reinterpret_cast<int*>(address + 0xc0) = friendIndex;
            unsigned int selectedIndex = *reinterpret_cast<unsigned int*>(address + 0x74) +
                                         *reinterpret_cast<unsigned int*>(address + 0x70) * 5;
            if (friendIndex != selectedIndex) {
                ipl::scene::FriendListCache* cache =
                    *reinterpret_cast<ipl::scene::FriendListCache**>(address + 0x274);
                swap__Q33ipl5scene15FriendListCacheFUlUl(cache, friendIndex, selectedIndex);
            }
            ipl::snd::sSystem.startSEwithPos(dataBase + 0x568,
                                              *reinterpret_cast<float*>(address + 0x64));
        } else {
            ipl::snd::sSystem.startSEwithPos(dataBase + 0x577,
                                              *reinterpret_cast<float*>(address + 0x64));
        }
        ipl::System::getPointer()->changeType(*reinterpret_cast<int*>(address + 0x6c), 0);
        static_cast<ipl::scene::Button*>(ipl::System::getScene(5))->enableBtn();
        void* layout = *reinterpret_cast<void**>(address + 0x8c);
        nw4r::lyt::Pane* root =
            *reinterpret_cast<nw4r::lyt::Pane**>(reinterpret_cast<char*>(layout) + 0x14);
        const char* const* buttonNames =
            reinterpret_cast<const char* const*>(dataBase + 0x3c);
        const char* paneName = buttonNames[*reinterpret_cast<unsigned int*>(address + 0x74)];
        nw4r::lyt::Pane* pane = root->FindPaneByName(paneName, true);
        SetVisible__Q34nw4r3lyt4PaneFb(pane, true);
        *reinterpret_cast<unsigned char*>(address + 0x84) = 0;
        *reinterpret_cast<int*>(address + 0xac) = 0xb;
        reset_friend__Q33ipl5scene7AddressFv(self);
        break;
    }
    default:
        break;
    }
}

extern "C" void stt_wait_dialog__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* dialog = reinterpret_cast<char*>(ipl::System::getDialog());
    if (*reinterpret_cast<int*>(dialog + 0x24) >= 0) {
        reset_gui__Q33ipl5scene7AddressFb(self, true);
        *reinterpret_cast<int*>(reinterpret_cast<char*>(self) + 0xac) = 4;
    }
}

extern "C" void on_point_event__Q33ipl5scene7AddressFiPQ33ipl10controller9Interface(
    ipl::scene::Address* self, int index, void* controller) {
    char* address = reinterpret_cast<char*>(self);
    int* count = reinterpret_cast<int*>(address + index * 4 + 0xcc);
    if (*count == 0) {
        if (*(reinterpret_cast<unsigned char*>(address) + index + 0xc4) != 0) {
            void* layout = *reinterpret_cast<void**>(address + 0x8c);
            unsigned short animationIndex = index + 6;
            void* frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<char*>(layout) + 0x28c, animationIndex);
            initFrame__Q33ipl7utility15FrameControllerFv(frame);
            *reinterpret_cast<int*>(reinterpret_cast<char*>(frame) + 0x14) = 1;
        } else {
            void* layout = *reinterpret_cast<void**>(address + 0x8c);
            unsigned short animationIndex = index + 0x15;
            void* frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<char*>(layout) + 0x28c, animationIndex);
            initFrame__Q33ipl7utility15FrameControllerFv(frame);
            *reinterpret_cast<int*>(reinterpret_cast<char*>(frame) + 0x14) = 1;
        }
        ipl::snd::sSystem.startSE(lbl_81647AC3);
        static_cast<ipl::controller::Interface*>(controller)->rumble(1);
    }
    *count += 1;
}

extern "C" void left_point_event__Q33ipl5scene7AddressFi(ipl::scene::Address* self, int index) {
    char* address = reinterpret_cast<char*>(self);
    int* count = reinterpret_cast<int*>(address + index * 4 + 0xcc);
    if (*count == 1) {
        if (*(reinterpret_cast<unsigned char*>(address) + index + 0xc4) != 0) {
            void* layout = *reinterpret_cast<void**>(address + 0x8c);
            unsigned short animationIndex = index + 0xb;
            void* frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<char*>(layout) + 0x28c, animationIndex);
            initFrame__Q33ipl7utility15FrameControllerFv(frame);
            *reinterpret_cast<int*>(reinterpret_cast<char*>(frame) + 0x14) = 1;
        } else {
            void* layout = *reinterpret_cast<void**>(address + 0x8c);
            unsigned short animationIndex = index + 0x1a;
            void* frame = List_GetNth__Q24nw4r2utFPCQ34nw4r2ut4ListUs(
                reinterpret_cast<char*>(layout) + 0x28c, animationIndex);
            initFrame__Q33ipl7utility15FrameControllerFv(frame);
            *reinterpret_cast<int*>(reinterpret_cast<char*>(frame) + 0x14) = 1;
        }
    }
    if (*count > 0) {
        *count = *count - 1;
    }
}

extern "C" bool isDupId__Q33ipl5scene15FriendListCacheFRCUx(
    const ipl::scene::FriendListCache* self, const unsigned long long* id) {
    const unsigned char* cache = reinterpret_cast<const unsigned char*>(self);
    for (int i = 0; i < 100; i++) {
        if (cache[i + 32000] != 0 && self->getInfo(i).attr.type == 1) {
            const NWC24FriendInfo& info = self->getInfo(i);
            if (*id == info.addr.wiiId) {
                return true;
            }
        }
    }
    return false;
}

extern "C" int init__Q33ipl5scene15FriendListCacheFv(ipl::scene::FriendListCache* self) {
    char* address = reinterpret_cast<char*>(self);
    ipl::nwc24::Manager* manager = ipl::System::getNwc24Manager();
    if (!manager->open()) {
        return 0;
    }
    manager->getMyUserId(reinterpret_cast<NWC24UserId*>(address + 0x7d68));
    u32 friendInfoCount;
    manager->getNumFriendInfos(&friendInfoCount);
    manager->getNumRegFriendInfos(reinterpret_cast<u32*>(address + 0x7d70));
    u32 index = 0;
    int infoOffset = 0;
    for (; index < 100; index++, infoOffset += 0x140) {
        unsigned char* flagAddress = reinterpret_cast<unsigned char*>(self) + index;
        u8 there = manager->isFriendInfoThere(index);
        flagAddress[0x7d00] = there;
        if (there) {
            manager->readFriendInfo(reinterpret_cast<NWC24FriendInfo*>(address + infoOffset), index);
        }
    }
    *reinterpret_cast<int*>(address + 0x9d74) = 0;
    *reinterpret_cast<unsigned char*>(address + 0x9d78) = 1;
    return 1;
}

extern "C" void add__Q33ipl5scene15FriendListCacheFUlRC15NWC24FriendInfo(
    ipl::scene::FriendListCache* self, unsigned int index, const NWC24FriendInfo* info) {
    char* address = reinterpret_cast<char*>(self);
    NWC24FriendInfo* records = reinterpret_cast<NWC24FriendInfo*>(self);
    memcpy(&records[index], info, 0x140);
    *(reinterpret_cast<unsigned char*>(address) + index + 32000) = 1;
    int* friendCount = reinterpret_cast<int*>(address + 0x7d70);
    *friendCount += 1;
    writeFriendInfo__Q33ipl5nwc247ManagerFPC15NWC24FriendInfoUl(
        ipl::System::getNwc24Manager(), &records[index], index);
}

extern "C" void update__Q33ipl5scene15FriendListCacheFUlPCwUx(
    ipl::scene::FriendListCache* self, unsigned int index, const wchar_t* name,
    unsigned long long id) {
    reinterpret_cast<NWC24FriendInfo*>(self)[index].attr.fdId = id;
    memset(reinterpret_cast<NWC24FriendInfo*>(self)[index].attr.name, 0, 0x18);
    wcsncpy(reinterpret_cast<wchar_t*>(reinterpret_cast<NWC24FriendInfo*>(self)[index].attr.name),
            name, 10);
    updateFriendInfo__Q33ipl5nwc247ManagerFPC15NWC24FriendInfoUl(
        ipl::System::getNwc24Manager(), &reinterpret_cast<NWC24FriendInfo*>(self)[index], index);
}

extern "C" void swap__Q33ipl5scene15FriendListCacheFUlUl(
    ipl::scene::FriendListCache* self, unsigned int first, unsigned int second) {
    NWC24FriendInfo temp __attribute__((aligned(32)));
    memcpy(&temp, &reinterpret_cast<NWC24FriendInfo*>(self)[first], 0x140);
    memcpy(&reinterpret_cast<NWC24FriendInfo*>(self)[first],
           &reinterpret_cast<NWC24FriendInfo*>(self)[second], 0x140);
    memcpy(&reinterpret_cast<NWC24FriendInfo*>(self)[second], &temp, 0x140);
    unsigned char flag = *(reinterpret_cast<unsigned char*>(self) + first + 32000);
    *(reinterpret_cast<unsigned char*>(self) + first + 32000) =
        *(reinterpret_cast<unsigned char*>(self) + second + 32000);
    *(reinterpret_cast<unsigned char*>(self) + second + 32000) = flag;
    swapFriendInfo__Q33ipl5nwc247ManagerFUlUl(ipl::System::getNwc24Manager(), first, second);
}

extern "C" bool isDupMail__Q33ipl5scene15FriendListCacheFPCc(const void* self,
                                                               const char* mail) {
    const unsigned char* cache = reinterpret_cast<const unsigned char*>(self);
    const NWC24FriendInfo* records = reinterpret_cast<const NWC24FriendInfo*>(self);
    int infoOffset;
    int flagOffset;
    flagOffset = 0;
    infoOffset = 0;
    for (; flagOffset < 100; flagOffset++, infoOffset += 0x140) {
        if (cache[flagOffset + 32000] != 0 && records[flagOffset].attr.type == 2 &&
            strcmp(records[flagOffset].addr.mailAddr, mail) == 0) {
            return true;
        }
    }
    return false;
}

extern "C" int check__Q33ipl5scene15FriendListCacheFv(ipl::scene::FriendListCache* self) {
    int result = check__Q33ipl5nwc247ManagerFUl(ipl::System::getNwc24Manager(), 1);
    *reinterpret_cast<int*>(reinterpret_cast<char*>(self) + 0x9d74) = result;
    return result;
}

extern "C" asm void __ml__Q33ipl4math4VEC2CFf() {
    stwu r1, -0x10(r1)
    mflr r0
    mr r4, r3
    lfs f2, 0(r3)
    fmr f3, f1
    lfs f0, 4(r4)
    fmuls f1, f2, f1
    stw r0, 0x14(r1)
    addi r3, r1, 8
    fmuls f2, f0, f3
    bl __ct__Q33ipl4math4VEC2Fff
    lwz r0, 0x14(r1)
    mr r4, r3
    lwz r3, 0(r3)
    lwz r4, 4(r4)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void SetTranslate__Q34nw4r3lyt4PaneFRCQ34nw4r4math4VEC3(
    nw4r::lyt::Pane* pane, const nw4r::math::VEC3* translate) {
    nofralloc
    lfs f2, 0(r4)
    lfs f1, 4(r4)
    lfs f0, 8(r4)
    stfs f2, 0x2c(r3)
    stfs f1, 0x30(r3)
    stfs f0, 0x34(r3)
    blr
}
