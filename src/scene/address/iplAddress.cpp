#include "scene/address/iplAddress.h"

extern "C" char smArg__Q23ipl6System;
extern "C" void checkUserId__Q33ipl5nwc247ManagerFUx();
extern "C" void getErrCode__Q33ipl5nwc247ManagerFv();
extern "C" void close__Q33ipl5nwc247ManagerFv();

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
