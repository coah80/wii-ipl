#include "scene/address/iplAddress.h"

extern "C" char smArg__Q23ipl6System;
extern "C" void checkUserId__Q33ipl5nwc247ManagerFUx();
extern "C" void getErrCode__Q33ipl5nwc247ManagerFv();
extern "C" void close__Q33ipl5nwc247ManagerFv();
extern "C" void deleteFriendInfo__Q33ipl5nwc247ManagerFUl();
extern "C" void getScene__Q33ipl5scene7ManagerFi();
extern "C" void setEventHandler__Q33ipl5scene6ButtonFPQ23gui12EventHandlerPQ23gui12EventHandler();
extern "C" void calc__Q33ipl6layout6ObjectFv();

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
