#include "scene/address/iplAddress.h"

#include "system/MESGEntries.h"
#include "system/iplSystem.h"

#include <string.h>

extern "C" const char* sTextNameB[5] = {
    "T_name_b_00", "T_name_b_01", "T_name_b_02", "T_name_b_03", "T_name_b_04",
};

extern "C" const char* sTextNameC[5] = {
    "T_name_c_00", "T_name_c_01", "T_name_c_02", "T_name_c_03", "T_name_c_04",
};

extern "C" const char* sButtonNameB[5] = {
    "B_name_b_00", "B_name_b_01", "B_name_b_02", "B_name_b_03", "B_name_b_04",
};

extern "C" const char* sButtonSpaceName[4] = {
    "B_name_b_00_01", "B_name_b_01_02", "B_name_b_02_03", "B_name_b_03_04",
};

extern "C" const char* sNameB[5] = {
    "name_b_00", "name_b_01", "name_b_02", "name_b_03", "name_b_04",
};

extern "C" const char* sNameC[5] = {
    "G_name_c_00", "G_name_c_01", "G_name_c_02", "G_name_c_03", "G_name_c_04",
};

extern "C" char sAddressStringPoolA[] =
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
    "T_wii_msg\0"
    "N_note_move\0"
    "WIPL_SE_FL_PAGE_INC\0"
    "\0";

extern "C" void calc__Q33ipl6layout6ObjectFv();

extern "C" void (*sAddressJumpTable[26])() = {
    calc__Q33ipl6layout6ObjectFv,
    calc__Q33ipl6layout6ObjectFv,
    calc__Q33ipl6layout6ObjectFv,
    calc__Q33ipl6layout6ObjectFv,
    calc__Q33ipl6layout6ObjectFv,
    calc__Q33ipl6layout6ObjectFv,
    calc__Q33ipl6layout6ObjectFv,
    calc__Q33ipl6layout6ObjectFv,
    calc__Q33ipl6layout6ObjectFv,
    calc__Q33ipl6layout6ObjectFv,
    calc__Q33ipl6layout6ObjectFv,
    calc__Q33ipl6layout6ObjectFv,
    calc__Q33ipl6layout6ObjectFv,
    calc__Q33ipl6layout6ObjectFv,
    calc__Q33ipl6layout6ObjectFv,
    calc__Q33ipl6layout6ObjectFv,
    calc__Q33ipl6layout6ObjectFv,
    calc__Q33ipl6layout6ObjectFv,
    calc__Q33ipl6layout6ObjectFv,
    calc__Q33ipl6layout6ObjectFv,
    calc__Q33ipl6layout6ObjectFv,
    calc__Q33ipl6layout6ObjectFv,
    calc__Q33ipl6layout6ObjectFv,
    calc__Q33ipl6layout6ObjectFv,
    calc__Q33ipl6layout6ObjectFv,
    calc__Q33ipl6layout6ObjectFv,
};

extern "C" char sAddressStringPoolB[] =
    "N_note_a\0"
    "N_note_b\0"
    "N_note_c\0"
    "N_note_d\0"
    "N_note_e\0"
    "T_wii_name\0"
    "T_nmbr_b\0"
    "WIPL_SE_FL_PAGE_DEC\0"
    "N_note_base\0"
    "T_CalAdd_R\0"
    "WIPL_SE_DECIDE\0"
    "mii_move\0"
    "WIPL_SE_CH_HOLD\0"
    "WIPL_SE_CH_SET\0"
    "WIPL_SE_CH_NOT_MOVE\0"
    "WIPL_SE_BT_TARGETTING\0"
    "WIPL_SE_CANCEL\0"
    "T_nmbr_c\0"
    "\0\0%"
    "\0"
    "0\0"
    "6\0"
    "d\0"
    "\n\0\0"
    "T_name_move\0"
    "WIPL_SE_CH_DRAG\0"
    "N_base_move\0"
    "\x00\x31\x00\x32\x00\x33\x00\x34\x00\x35\x00\x36\x00\x37\x00\x38"
    "\x00\x39\x00\x30\x00\x31\x00\x32\x00\x33\x00\x34\x00\x35\x00\x36"
    "\x00\x00\x00\x25\x00\x30\x00\x31\x00\x36\x00\x6c\x00\x6c\x00\x64"
    "\x00";

extern "C" char smArg__Q23ipl6System;
extern "C" void checkUserId__Q33ipl5nwc247ManagerFUx();
extern "C" void getErrCode__Q33ipl5nwc247ManagerFv();
extern "C" void close__Q33ipl5nwc247ManagerFv();
extern "C" void deleteFriendInfo__Q33ipl5nwc247ManagerFUl();
extern "C" void getScene__Q33ipl5scene7ManagerFi();
extern "C" void setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler();
extern "C" void calc__Q33ipl6layout6ObjectFv();
extern "C" void __ct__Q33ipl4math4VEC2Fff();
extern "C" void __dt__Q33ipl6nigaoe6ObjectFv();
extern "C" void __dl__FPv();
extern "C" void GetTexture__Q34nw4r3lyt8MaterialCFP9_GXTexObjUc();
extern "C" void SetTexture__Q34nw4r3lyt8MaterialFUcRC9_GXTexObj();
extern "C" void create__Q33ipl6nigaoe7ManagerFPQ23EGG4HeapiiiPFPQ33ipl6nigaoe6ObjectPvPv();
extern "C" int init__Q33ipl5scene15FriendListCacheFv(void*);
extern "C" void onInitFriendList__Q33ipl5scene7AddressFv(void*);
extern "C" void callBtn1__Q23ipl12DialogWindowFUlUl(void*, unsigned int, unsigned int);

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

extern "C" asm void calcCommon__Q33ipl5scene14FaderSceneBaseFv() {
    nofralloc
    blr
}

extern "C" void fistt_wait_open__Q33ipl5scene7AddressFv(ipl::scene::Address* self) {
    char* address = reinterpret_cast<char*>(self);
    if (init__Q33ipl5scene15FriendListCacheFv(*reinterpret_cast<void**>(address + 0x274))) {
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

extern "C" asm void init__Q43ipl5scene7Address6MiiObjFPQ34nw4r3lyt4Pane() {
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

extern "C" asm void reset__Q43ipl5scene7Address6MiiObjFv() {
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

extern "C" asm void set__Q43ipl5scene7Address6MiiObjFUx() {
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
        if (strcmp(sButtonNameB[i], paneName) == 0) {
            result = i;
            break;
        }
    }
    return result;
}

extern "C" int get_button_space_no__Q33ipl5scene7AddressFPCc(void*, const char* paneName) {
    int result = -1;
    for (int i = 0; i < 4; i++) {
        if (strcmp(sButtonSpaceName[i], paneName) == 0) {
            result = i;
            break;
        }
    }
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

extern "C" asm void SetTranslate__Q34nw4r3lyt4PaneFRCQ34nw4r4math4VEC3() {
    nofralloc
    lfs f2, 0(r4)
    lfs f1, 4(r4)
    lfs f0, 8(r4)
    stfs f2, 0x2c(r3)
    stfs f1, 0x30(r3)
    stfs f0, 0x34(r3)
    blr
}
