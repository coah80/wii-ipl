#include "keyboard/tiInputForm.h"
#include "keyboard/tiManager.h"

#include <revolution/mtx.h>

namespace textinput {
namespace inputform {

extern "C" asm void GetCursorY__Q34nw4r2ut10CharWriterCFv();
extern "C" asm void GetCursorX__Q34nw4r2ut10CharWriterCFv();
extern "C" asm void SetCursor__Q34nw4r2ut10CharWriterFff();
extern "C" asm void SetCursorY__Q34nw4r2ut10CharWriterFf();
extern "C" asm void SetCursorX__Q34nw4r2ut10CharWriterFf();
extern "C" asm void SetTextColor__Q34nw4r2ut10CharWriterFQ34nw4r2ut5Color();
extern "C" asm void GetFontHeight__Q34nw4r2ut10CharWriterCFv();
extern "C" asm void GetFont__Q34nw4r2ut10CharWriterCFv();
extern "C" asm void SetFixedWidth__Q34nw4r2ut10CharWriterFf();
extern "C" asm void EnableFixedWidth__Q34nw4r2ut10CharWriterFb();
extern "C" asm void KPRInitQueue();
extern "C" asm void KPRSetMode();
extern "C" asm void create__Q39textinput10textdrawer4BaseFP12MEMAllocator();
extern "C" asm void init__Q49textinput9inputform4Base14RowInfoManagerFv();
extern "C" asm void MEMAllocFromAllocator();
extern "C" asm void MEMFreeToAllocator();
extern "C" asm void __dt__Q34nw4r2ut10CharWriterFv();
extern "C" asm void __dl__FPv();
extern "C" asm void SinFIdx__Q24nw4r4mathFf();
extern "C" asm void drawLine___Q29textinput5debugFfffffUcR8_GXColor();
extern "C" asm void setDrawString__Q39textinput10textdrawer4BaseFPCwUlUl();
extern "C" asm void draw__Q39textinput10textdrawer4BaseFPQ49textinput10textdrawer4Base9CursorPos();
extern "C" asm void drawBox___Q29textinput5debugFffffffR8_GXColor();
extern "C" asm void clearCandidates__Q39textinput8tistring6WithZiFv();
extern "C" asm void getCurrentInput__Q39textinput8tistring6WithZiFPwUl();
extern "C" asm void hermiteInterporation__Q29textinput4utilFfffffff();
extern "C" asm void getCurrentString__Q39textinput9inputform4BaseFb();
extern "C" asm void onCommand__Q29textinput15CommandReceiverFQ39textinput15CommandReceiver13INPUT_COMMANDPv();
extern "C" asm void resetCandidate__Q39textinput12candidatebox18CandidateBoxCallerFv();
extern "C" asm void addCandidate__Q39textinput12candidatebox18CandidateBoxCallerFPCw();
extern "C" asm void updateCandidate__Q39textinput12candidatebox18CandidateBoxCallerFv();
extern "C" asm void setCurrentWord__Q39textinput8tistring6WithZiFPCw();
extern "C" asm void update__Q39textinput8tistring6WithZiFv();
extern "C" asm void wcslen();
extern "C" asm void wcsnicmp();
extern "C" asm void List_Append__Q24nw4r2utFPQ34nw4r2ut4ListPv();
extern "C" asm void List_GetNext__Q24nw4r2utFPCQ34nw4r2ut4ListPCv();
extern "C" asm void List_Remove__Q24nw4r2utFPQ34nw4r2ut4ListPv();
extern "C" asm void IsScrolling__Q39textinput12candidatebox10UITextAreaFv();
extern "C" asm void destroy__Q39textinput11nw4rmanager7AnmPaneFP12MEMAllocator();
extern "C" asm void __dt__Q34nw4r2ut7ResFontFv();
extern "C" asm void __dt__Q39textinput11nw4rmanager6LayoutFv();
extern "C" asm void __dt__Q34nw4r2ut10CharWriterFv();
extern "C" asm void __ct__Q39textinput11nw4rmanager6LayoutFPQ34nw4r3lyt24MultiArcResourceAccessorPCcPQ29textinput13EventObserver();
extern "C" asm void __ct__Q34nw4r2ut7ResFontFv();
extern "C" asm void __dt__Q39textinput8tistring10StringBaseFv();
extern "C" asm void KPRLookAhead();
extern "C" asm void set__Q39textinput8tistring10StringBaseFPCw();
extern "C" asm void clear__Q39textinput8tistring10StringBaseFv();
extern "C" asm void updateRepeatInput__Q39textinput9inputform12LayoutByNW4RFUlUl();
extern "C" asm void ChangeSelectedText__Q39textinput12candidatebox10UITextAreaFl();
extern "C" asm void confirmInput___Q39textinput9inputform4BaseFv();
extern "C" asm void isAlphabet__Q29textinput4utilFw();
extern "C" asm void reverseLetterCaseW__Q29textinput4utilFw();
extern "C" asm void confirmInputting___Q39textinput9inputform4BaseFwbUsbPv();
extern "C" asm void calc__Q39textinput9inputform4BaseFv();
extern "C" asm void calc__Q39textinput11nw4rmanager6LayoutFv();
extern "C" asm void draw__Q39textinput11nw4rmanager6LayoutFv();
extern "C" asm void searchPaneComponent__Q39textinput3gui11PaneManagerFPCc();
#pragma push
#pragma section const_type ".data"
extern "C" const char lbl_8165C820[];
extern "C" const char lbl_8165C830[];
extern "C" const char lbl_8165C8C0[];
extern "C" const char lbl_8165C8CC[];
extern "C" const char lbl_8165C8E0[];
extern "C" const char lbl_8165C8F0[];
extern "C" const char lbl_8165C900[];
extern "C" const char lbl_8165C918[];
extern "C" const char lbl_8165C928[];
extern "C" const char lbl_8165C938[];
extern "C" const char lbl_8165C950[];
extern "C" const char lbl_8165C960[];
extern "C" const char lbl_816973A4[];
extern "C" const char lbl_816973AC[];
#pragma pop
extern "C" const f32 lbl_81694D28;
extern "C" void _savegpr_20();
extern "C" void _restgpr_20();
extern "C" void _savegpr_27();
extern "C" void _restgpr_27();
extern "C" asm void __ct__Q34nw4r2ut10CharWriterFv();
extern "C" asm void memset();
extern "C" asm void KPRInitRegionUS();
extern "C" asm void __vt__Q29textinput15CommandReceiver();
extern "C" asm void __vt__Q39textinput10textdrawer4Base();
extern "C" asm void __vt__Q39textinput9inputform4Base();
extern "C" asm void __vt__Q39textinput9inputform12LayoutByNW4R();
extern "C" asm void __vt__Q39textinput4util9Animation();
extern "C" asm void __vt__Q39textinput9inputform10EditBuffer();
extern "C" asm void __vt__Q39textinput8tistring9Decolated();
extern "C" asm void __vt__Q39textinput8tistring8WithAtok();
extern "C" asm void __vt__Q39textinput8tistring6WithZi();
extern "C" asm void moveCandidateToIdx__Q39textinput9inputform4BaseFl() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r30, r4
    stw r29, 0x14(r1)
    mr r29, r3
    lbz r0, 0x178(r3)
    cmpwi r0, 0
    beq moveCandidateToIdx_L_set
    lwz r3, 0x1d4(r3)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r3)
    lwz r12, 0x104(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    bne moveCandidateToIdx_L_done
    lwz r0, 0x174(r29)
    cmpwi r0, 1
    bne moveCandidateToIdx_L_mid
    lwz r3, 0x168(r29)
    lwz r12, 0(r3)
    lwz r12, 0x13c(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq moveCandidateToIdx_L_select
    lwz r3, 0x168(r29)
    lwz r12, 0(r3)
    lwz r12, 0xdc(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    bne moveCandidateToIdx_L_select
    lwz r3, 0x168(r29)
    li r4, 0
    lwz r12, 0(r3)
    lwz r12, 0x60(r12)
    mtctr r12
    bctrl
    lwz r3, 0x168(r29)
    lwz r12, 0(r3)
    lwz r12, 0xe0(r12)
    mtctr r12
    bctrl
    mr r31, r3
    lwz r3, 0x164(r29)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl
    lwz r3, 0x164(r29)
    mr r4, r31
    lwz r12, 0(r3)
    lwz r12, 0x60(r12)
    mtctr r12
    bctrl
    lwz r3, 0x164(r29)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl
    lwz r3, 0x168(r29)
    li r4, 0
    lwz r12, 0(r3)
    lwz r12, 0x114(r12)
    mtctr r12
    bctrl
moveCandidateToIdx_L_select:
    lwz r3, 0x168(r29)
    mr r4, r30
    lwz r12, 0(r3)
    lwz r12, 0xf0(r12)
    mtctr r12
    bctrl
    b moveCandidateToIdx_L_after
moveCandidateToIdx_L_mid:
    lwz r3, 0x16c(r29)
    mr r4, r30
    lwz r12, 0(r3)
    lwz r12, 0xe8(r12)
    mtctr r12
    bctrl
moveCandidateToIdx_L_after:
    lwz r3, 0x1d4(r29)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl
    mr r4, r30
    addi r3, r3, 0xe4
    bl ChangeSelectedText__Q39textinput12candidatebox10UITextAreaFl
    b moveCandidateToIdx_L_done
moveCandidateToIdx_L_set:
    li r0, 1
    stw r0, 0x1b0(r3)
moveCandidateToIdx_L_done:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
extern "C" asm void confirmInput___Q39textinput9inputform4BaseFv() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r30, r3
    lbz r0, 0x178(r3)
    cmpwi r0, 0
    bne confirmInput_L_atok
    lwz r3, 0x164(r3)
    lwz r12, 0(r3)
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    bne confirmInput_L_end
    lwz r3, 0x164(r30)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl
    lwz r3, 0x164(r30)
    lwz r12, 0(r3)
    lwz r12, 0xc4(r12)
    mtctr r12
    bctrl
    lwz r3, 0x164(r30)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl
    b confirmInput_L_end
confirmInput_L_atok:
    lwz r0, 0x174(r3)
    cmpwi r0, 1
    bne confirmInput_L_zi
    lwz r3, 0x168(r3)
    lwz r12, 0(r3)
    lwz r12, 0xf4(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq confirmInput_L_atok_empty
    lwz r3, 0x168(r30)
    lwz r12, 0(r3)
    lwz r12, 0xf8(r12)
    mtctr r12
    bctrl
    stw r3, 8(r1)
    mr r3, r30
    addi r5, r1, 8
    li r4, 0x15
    lwz r12, 0(r30)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    b confirmInput_L_end
confirmInput_L_atok_empty:
    lwz r3, 0x168(r30)
    li r4, 0
    lwz r12, 0(r3)
    lwz r12, 0x60(r12)
    mtctr r12
    bctrl
    lwz r3, 0x168(r30)
    lwz r12, 0(r3)
    lwz r12, 0xe0(r12)
    mtctr r12
    bctrl
    mr r31, r3
    lwz r3, 0x164(r30)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl
    lwz r3, 0x164(r30)
    mr r4, r31
    lwz r12, 0(r3)
    lwz r12, 0x60(r12)
    mtctr r12
    bctrl
    lwz r3, 0x164(r30)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl
    lwz r3, 0x168(r30)
    li r4, 0
    lwz r12, 0(r3)
    lwz r12, 0x114(r12)
    mtctr r12
    bctrl
    b confirmInput_L_end
confirmInput_L_zi:
    lwz r3, 0x16c(r3)
    lwz r12, 0(r3)
    lwz r12, 0xe0(r12)
    mtctr r12
    bctrl
    mr r31, r3
    lwz r3, 0x16c(r30)
    lwz r12, 0(r3)
    lwz r12, 0xe4(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 0x10
    beq confirmInput_L_clear
    lwz r3, 0x164(r30)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl
    lwz r3, 0x164(r30)
    mr r4, r31
    lwz r12, 0(r3)
    lwz r12, 0x54(r12)
    mtctr r12
    bctrl
    lwz r3, 0x164(r30)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl
    lwz r0, 0x1f0(r30)
    cmpwi r0, 8
    bne confirmInput_L_clear
    lwz r3, 0x16c(r30)
    mr r4, r31
    bl setCurrentWord__Q39textinput8tistring6WithZiFPCw
confirmInput_L_clear:
    lwz r3, 0x16c(r30)
    bl clearCandidates__Q39textinput8tistring6WithZiFv
    lwz r0, 0x1f0(r30)
    li r3, 0
    stb r3, 0x1f4(r30)
    cmpwi r0, 8
    bne confirmInput_L_end
    lwz r3, 0x16c(r30)
    bl update__Q39textinput8tistring6WithZiFv
confirmInput_L_end:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
extern "C" asm void inputInputting___Q39textinput9inputform4BaseFw() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r30, r4
    li r4, 0
    stw r29, 0x14(r1)
    mr r29, r3
    bl getCurrentString__Q39textinput9inputform4BaseFb
    addis r4, r30, 1
    mr r31, r3
    addi r0, r4, -0x309b
    clrlwi r0, r0, 0x10
    cmplwi r0, 1
    bgt inputInputting_L_command
    lwz r12, 0(r29)
    mr r3, r29
    li r4, 0x1b
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    b inputInputting_L_end
inputInputting_L_command:
    lbz r3, 0x178(r29)
    cmpwi r3, 0
    beq inputInputting_L_atok_empty
    lwz r0, 0x174(r29)
    cmpwi r0, 1
    bne inputInputting_L_atok_empty
    lwz r3, 0x168(r29)
    lwz r12, 0(r3)
    lwz r12, 0xf4(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq inputInputting_L_direct_input
    lwz r12, 0(r29)
    mr r3, r29
    li r4, 6
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
inputInputting_L_direct_input:
    lwz r3, 0x168(r29)
    mr r4, r30
    lwz r12, 0(r3)
    lwz r12, 0x100(r12)
    mtctr r12
    bctrl
    b inputInputting_L_end
inputInputting_L_atok_empty:
    cmpwi r3, 0
    beq inputInputting_L_skip_atok
    lwz r12, 0(r29)
    mr r3, r29
    lwz r12, 0x114(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0xb
    bne inputInputting_L_skip_atok
    lwz r3, 0x1d4(r29)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r3)
    lwz r12, 0x4c(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    bne inputInputting_L_skip_atok
    mr r3, r30
    bl isAlphabet__Q29textinput4utilFw
    cmpwi r3, 0
    bne inputInputting_L_zi_input
    cmplwi r30, 0x31
    blt inputInputting_L_keyboard_mode
    cmplwi r30, 0x35
    bgt inputInputting_L_keyboard_mode
inputInputting_L_zi_input:
    lwz r3, 0x16c(r29)
    mr r4, r30
    lwz r12, 0(r3)
    lwz r12, 0xd4(r12)
    mtctr r12
    bctrl
    b inputInputting_L_end
inputInputting_L_keyboard_mode:
    lbz r0, 0x178(r29)
    cmpwi r0, 0
    bne inputInputting_L_predict_mode
    li r0, 0
    b inputInputting_L_input_check
inputInputting_L_predict_mode:
    lwz r0, 0x174(r29)
    cmpwi r0, 1
    beq inputInputting_L_input_false
    lwz r3, 0x16c(r29)
    lwz r12, 0(r3)
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    ble inputInputting_L_input_false
    li r0, 1
    b inputInputting_L_input_check
inputInputting_L_input_false:
    li r0, 0
inputInputting_L_input_check:
    cmpwi r0, 0
    beq inputInputting_L_manager
    lwz r3, 0x16c(r29)
    lwz r12, 0(r3)
    lwz r12, 0xe4(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 0x10
    beq inputInputting_L_manager
    lwz r0, 0x1f0(r29)
    cmpwi r0, 8
    bne inputInputting_L_get_current
    lwz r3, 0x16c(r29)
    lwz r12, 0(r3)
    lwz r12, 0x48(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    bne inputInputting_L_manager
inputInputting_L_get_current:
    mr r3, r29
    bl getCurrentString__Q39textinput9inputform4BaseFb
inputInputting_L_manager:
    lwz r3, 0x16c(r29)
    mr r4, r30
    lwz r12, 0(r3)
    lwz r12, 0xd4(r12)
    mtctr r12
    bctrl
    lwz r3, 0x16c(r29)
    li r4, -1
    lwz r12, 0(r3)
    lwz r12, 0xe8(r12)
    mtctr r12
    bctrl
    b inputInputting_L_done
inputInputting_L_skip_atok:
    lwz r12, 0(r31)
    mr r3, r31
    mr r4, r30
    lwz r12, 0x40(r12)
    mtctr r12
    bctrl
inputInputting_L_end:
    cmpwi r30, 0
    beq inputInputting_L_return
    lwz r12, 0(r29)
    mr r3, r29
    li r4, 0xa
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl
inputInputting_L_return:
    li r0, 1
    stw r0, 0x1b0(r29)
inputInputting_L_done:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
extern "C" asm void inputCharDefault___Q39textinput9inputform4BaseFwUl() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_27
    mr r28, r4
    mr r27, r3
    mr r29, r5
    li r4, 1
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r31, 0x168(r27)
    mr r30, r3
    mr r3, r27
    li r4, 0
    bl getCurrentString__Q39textinput9inputform4BaseFb
    cmplw r3, r31
    bne inputCharDefault_L_language
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0xdc(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    bne inputCharDefault_L_language
    lwz r3, 0x168(r27)
    lwz r12, 0(r3)
    lwz r12, 0xf8(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    blt inputCharDefault_L_language
    mr r3, r27
    bl confirmInputting___Q39textinput9inputform4BaseFwbUsbPv
inputCharDefault_L_language:
    lwz r0, 0x1f0(r27)
    cmpwi r0, 9
    bne inputCharDefault_L_string
    lwz r3, 0x1d4(r27)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r3)
    lwz r12, 0x58(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq inputCharDefault_L_string
    mr r3, r28
    bl reverseLetterCaseW__Q29textinput4utilFw
    cmpwi r3, 0
    beq inputCharDefault_L_string
    rlwinm. r0, r29, 0, 0x1e, 0x1e
    beq inputCharDefault_L_string
    mr r3, r28
    bl reverseLetterCaseW__Q29textinput4utilFw
    mr r28, r3
inputCharDefault_L_string:
    lwz r3, 0x164(r27)
    cmplw r3, r30
    bne inputCharDefault_L_post_string
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl
    lwz r3, 0x164(r27)
    clrlwi r4, r28, 0x10
    lwz r12, 0(r3)
    lwz r12, 0x50(r12)
    mtctr r12
    bctrl
    lwz r3, 0x164(r27)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl
    lwz r0, 0x1f0(r27)
    cmpwi r0, 8
    bne inputCharDefault_L_post_string_cont
    lbz r0, 0x178(r27)
    cmpwi r0, 0
    bne inputCharDefault_L_predict
    li r0, 0
    b inputCharDefault_L_predict_check
inputCharDefault_L_predict:
    lwz r0, 0x174(r27)
    cmpwi r0, 1
    beq inputCharDefault_L_predict_false
    lwz r3, 0x16c(r27)
    lwz r12, 0(r3)
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    ble inputCharDefault_L_predict_false
    li r0, 1
    b inputCharDefault_L_predict_check
inputCharDefault_L_predict_false:
    li r0, 0
inputCharDefault_L_predict_check:
    cmpwi r0, 0
    beq inputCharDefault_L_post_string_cont
    lwz r3, 0x16c(r27)
    li r4, 0
    bl setCurrentWord__Q39textinput8tistring6WithZiFPCw
    lwz r3, 0x16c(r27)
    bl update__Q39textinput8tistring6WithZiFv
    b inputCharDefault_L_post_string_cont
inputCharDefault_L_post_string:
    lwz r12, 0(r30)
    mr r3, r30
    clrlwi r4, r28, 0x10
    lwz r12, 0x50(r12)
    mtctr r12
    bctrl
inputCharDefault_L_post_string_cont:
    clrlwi r0, r28, 0x10
    cmplwi r0, 0x20
    bne inputCharDefault_L_newline
    lwz r12, 0(r27)
    mr r3, r27
    li r4, 9
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl
    b inputCharDefault_L_set
inputCharDefault_L_newline:
    cmplwi r0, 0xa
    beq inputCharDefault_L_set
    lwz r12, 0(r27)
    mr r3, r27
    li r4, 0xa
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl
inputCharDefault_L_set:
    li r0, 1
    addi r11, r1, 0x20
    stw r0, 0x1b0(r27)
    bl _restgpr_27
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
extern "C" asm void calc__Q39textinput9inputform12LayoutByNW4RFv() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    lis r31, lbl_8165C820@ha
    addi r31, r31, lbl_8165C820@l
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    stw r28, 0x10(r1)
    mr r28, r3
    bl calc__Q39textinput9inputform4BaseFv
    addi r3, r28, 0x218
    bl calc__Q39textinput11nw4rmanager6LayoutFv
    lwz r12, 0x218(r28)
    addi r3, r28, 0x218
    lwz r4, 0x2c4(r28)
    li r30, 0
    lwz r12, 0x2c(r12)
    li r29, 0
    lwz r4, 4(r4)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq calcLayout_L_text
    lwz r12, 0x218(r28)
    addi r3, r28, 0x218
    lwz r4, 0x2c4(r28)
    lwz r12, 0x54(r12)
    lwz r4, 4(r4)
    lbz r5, 0x2ce(r28)
    mtctr r12
    bctrl
    b calcLayout_L_animation
calcLayout_L_text:
    lwz r12, 0x218(r28)
    addi r3, r28, 0x218
    addi r4, r31, 0x418
    lbz r5, 0x2ce(r28)
    lwz r12, 0x54(r12)
    mtctr r12
    bctrl
calcLayout_L_animation:
    lwz r12, 0x18c(r28)
    addi r3, r28, 0x18c
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    bne calcLayout_L_done
    lfs f1, lbl_81694D28(r0)
    lfs f0, 0x188(r28)
    fcmpo cr0, f1, f0
    ble calcLayout_L_scroll_x
    li r30, 1
calcLayout_L_scroll_x:
    lfs f1, 0xc8(r28)
    lfs f0, 0x188(r28)
    fcmpo cr0, f1, f0
    bge calcLayout_L_scroll_y
    li r29, 1
calcLayout_L_scroll_y:
    lbz r0, 0x2cc(r28)
    cmplw r0, r30
    beq calcLayout_L_second_flag
    cmpwi r30, 0
    stb r30, 0x2cc(r28)
    beq calcLayout_L_first_disable
    lwz r12, 0x218(r28)
    addi r3, r28, 0x218
    addi r4, r31, 0x3f4
    lwz r12, 0x60(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r3)
    li r4, 6
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lwz r3, 0x228(r28)
    addi r4, r31, 0x3f4
    bl searchPaneComponent__Q39textinput3gui11PaneManagerFPCc
    lwz r12, 0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    b calcLayout_L_second_flag
calcLayout_L_first_disable:
    lwz r12, 0x218(r28)
    addi r3, r28, 0x218
    addi r4, r31, 0x3f4
    lwz r12, 0x60(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r3)
    li r4, 7
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
calcLayout_L_second_flag:
    lbz r0, 0x2cd(r28)
    cmplw r0, r29
    beq calcLayout_L_done
    cmpwi r29, 0
    stb r29, 0x2cd(r28)
    beq calcLayout_L_second_disable
    lwz r12, 0x218(r28)
    addi r3, r28, 0x218
    addi r4, r31, 0x408
    lwz r12, 0x60(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r3)
    li r4, 6
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lwz r3, 0x228(r28)
    addi r4, r31, 0x408
    bl searchPaneComponent__Q39textinput3gui11PaneManagerFPCc
    lwz r12, 0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    b calcLayout_L_done
calcLayout_L_second_disable:
    lwz r12, 0x218(r28)
    addi r3, r28, 0x218
    addi r4, r31, 0x408
    lwz r12, 0x60(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r3)
    li r4, 7
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
calcLayout_L_done:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
extern "C" asm void draw__Q39textinput9inputform12LayoutByNW4RFv() {
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stw r31, 0x4c(r1)
    stw r30, 0x48(r1)
    mr r30, r3
    addi r3, r3, 0x218
    bl draw__Q39textinput11nw4rmanager6LayoutFv
    lwz r12, 0x218(r30)
    addi r3, r30, 0x218
    lwz r12, 0x28(r12)
    mtctr r12
    bctrl
    lwz r4, 0x10(r3)
    li r5, 1
    lwz r3, 0x21c(r30)
    lbz r0, 0xcd(r4)
    lwz r4, 0x2c0(r30)
    stb r0, 0x1c8(r30)
    lwz r3, 0x10(r3)
    lwz r12, 0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    lwz r12, 0x218(r30)
    mr r6, r3
    addi r3, r30, 0x218
    addi r4, r30, 0x130
    lwz r12, 0x70(r12)
    addi r5, r30, 0x230
    addi r6, r6, 0x84
    mtctr r12
    bctrl
    lwz r12, 0(r30)
    mr r3, r30
    lwz r12, 0x188(r12)
    mtctr r12
    bctrl
    stw r3, 0x18(r1)
    addi r3, r30, 0x10
    lfs f2, 0x188(r30)
    stw r4, 0x1c(r1)
    lfs f1, 0x18(r1)
    bl SetCursor__Q34nw4r2ut10CharWriterFff
    lwz r12, 0(r30)
    mr r3, r30
    lwz r12, 0x188(r12)
    mtctr r12
    bctrl
    lfs f0, lbl_81694D28(r0)
    stw r3, 0x20(r1)
    stfs f0, 0x30(r1)
    stfs f0, 0x34(r1)
    stfs f0, 0x38(r1)
    stfs f0, 0x3c(r1)
    lwz r12, 0(r30)
    stw r3, 8(r1)
    mr r3, r30
    lwz r12, 0x184(r12)
    stw r4, 0x24(r1)
    stw r4, 0xc(r1)
    mtctr r12
    bctrl
    stw r3, 0x10(r1)
    lfs f1, 8(r1)
    stw r4, 0x14(r1)
    lfs f5, 0x10(r1)
    lfs f4, 0x14(r1)
    stfs f5, 0x30(r1)
    lfs f0, 0xc(r1)
    stfs f4, 0x3c(r1)
    lfs f3, 0x128(r30)
    lfs f2, 0x120(r30)
    stw r3, 0x28(r1)
    fsubs f2, f3, f2
    stw r4, 0x2c(r1)
    fmuls f1, f1, f2
    fadds f1, f5, f1
    stfs f1, 0x38(r1)
    lfs f2, 0x124(r30)
    lfs f1, 0x12c(r30)
    fsubs f1, f2, f1
    fmuls f0, f0, f1
    fadds f0, f4, f0
    stfs f0, 0x34(r1)
    lwz r3, 0x164(r30)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl
    lwz r12, 0x5c(r30)
    mr r31, r3
    addi r3, r30, 0x10
    addi r4, r1, 0x30
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r30)
    mr r3, r30
    mr r4, r31
    lwz r12, 0x174(r12)
    mtctr r12
    bctrl
    lwz r12, 0x5c(r30)
    addi r3, r30, 0x10
    lwz r12, 0x24(r12)
    mtctr r12
    bctrl
    lwz r0, 0x54(r1)
    lwz r31, 0x4c(r1)
    lwz r30, 0x48(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}
extern "C" asm void calcCursorTimer__Q39textinput9inputform4BaseFv() {
    nofralloc
    lwz r4, 0x214(r3)
    addi r0, r4, 8
    stw r0, 0x214(r3)
    blr
}
extern "C" asm bool isAtokActive__Q39textinput9inputform4BaseCFv() {
    nofralloc
    lbz r0, 0x178(r3)
    cmpwi r0, 0
    bne isAtokActive_L1
    li r3, 0
    blr
isAtokActive_L1:
    lwz r3, 0x174(r3)
    addi r0, r3, -1
    cntlzw r0, r0
    srwi r3, r0, 5
    blr
}
extern "C" asm void dirtyCacheAll__Q39textinput9inputform4BaseFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r12, 0x5c(r3)
    lwz r12, 0x94(r12)
    mtctr r12
    addi r3, r3, 0x10
    bctrl
    lwz r12, 0x5c(r31)
    addi r3, r31, 0x10
    lwz r12, 0x90(r12)
    mtctr r12
    bctrl
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
extern "C" asm void initZiString__Q39textinput9inputform4BaseFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r3, 0x16c(r3)
    bl clearCandidates__Q39textinput8tistring6WithZiFv
    li r0, 0
    stb r0, 0x1f4(r31)
    lwz r31, 0xc(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
extern "C" asm void resetContextPredict___Q39textinput9inputform4BaseFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r3, 0x16c(r31)
    cmpwi r3, 0
    beq resetContextPredict_L1
    lwz r0, 0x1f0(r31)
    cmpwi r0, 8
    bne resetContextPredict_L1
    li r4, 0
    bl setCurrentWord__Q39textinput8tistring6WithZiFPCw
    lwz r3, 0x16c(r31)
    bl update__Q39textinput8tistring6WithZiFv
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl
resetContextPredict_L1:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

struct InputFormAnimationFile {
    u32 id;
    char fileName[0x40];
};

#pragma push
#pragma section const_type ".rodata"
extern "C" const InputFormAnimationFile csAninationFile__Q29textinput9inputform[8] = {
    {0, "fs_VK_textBox_a_normal.brlan"},
    {1, "fs_VK_textBox_a_Foucus_IN.brlan"},
    {2, "fs_VK_textBox_a_Focus-OUT.brlan"},
    {3, "fs_VK_textBox_a_Roll_over.brlan"},
    {4, "fs_VK_textBox_a_Pushed.brlan"},
    {5, "fs_VK_textBox_a_Fade_IN.brlan"},
    {6, "fs_VK_textBox_a_Fade_OUT.brlan"},
    {7, "fs_VK_textBox_a_Off.brlan"},
};

#pragma section data_type ".rodata"
extern "C" const void* csVisiblePaneUEJ__Q29textinput9inputform[9] = {
    (const void*)0x00010002,
    lbl_8165C8C0,
    0,
    0,
    0,
    lbl_816973A4,
    lbl_816973AC,
    0,
    0,
};

extern "C" const void* csVisiblePaneKOR__Q29textinput9inputform[9] = {
    (const void*)0x00010002,
    lbl_816973A4,
    0,
    0,
    0,
    lbl_816973AC,
    lbl_8165C8C0,
    0,
    0,
};

extern "C" const void* csVisiblePaneCHN__Q29textinput9inputform[10] = {
    (const void*)0x00010002,
    lbl_816973AC,
    0,
    0,
    0,
    lbl_816973A4,
    lbl_8165C8C0,
    0,
    0,
    0,
};

extern "C" const void* csLanguageDependencyDataUEJ__Q29textinput9inputform[4] = {
    csVisiblePaneUEJ__Q29textinput9inputform,
    lbl_8165C8CC,
    lbl_8165C8E0,
    lbl_8165C8F0,
};

extern "C" const void* csLanguageDependencyDataKOR__Q29textinput9inputform[4] = {
    csVisiblePaneKOR__Q29textinput9inputform,
    lbl_8165C900,
    lbl_8165C918,
    lbl_8165C928,
};

extern "C" const void* csLanguageDependencyDataCHN__Q29textinput9inputform[4] = {
    csVisiblePaneCHN__Q29textinput9inputform,
    lbl_8165C938,
    lbl_8165C950,
    lbl_8165C960,
};
#pragma section data_type ".data"

extern "C" const u32 pppURLCheck[10] = {
    0x00680074, 0x00740070, 0x003A002F, 0x002F0000, 0x00000000,
    0x00680074, 0x00740070, 0x0073003A, 0x002F002F, 0x00000000
};

extern "C" const u32 lbl_816152D0[4] = {0x00200000, 0, 0, 0};
#pragma pop

extern "C" const f32 lbl_81694D28 = 0.0f;
extern "C" const f32 lbl_81694D2C = 640.0f;
extern "C" const f64 lbl_81694D30 = 4503601774854144.0;
extern "C" const f32 lbl_81694D38 = 1.0f;
extern "C" const f32 lbl_81694D3C = 0.5f;
extern "C" const f32 lbl_81694D40 = 0.7111111f;
extern "C" const f32 lbl_81694D44 = 150.0f;
extern "C" const f32 lbl_81694D48 = 30.0f;
extern "C" const f32 lbl_81694D4C = 50.0f;
extern "C" const f32 lbl_81694D50 = 10.0f;
extern "C" const f32 lbl_81694D54 = 52.0f;
extern "C" const f32 lbl_81694D58 = 2.0f;
extern "C" const f32 lbl_81694D5C = 140.0f;
extern "C" const f32 lbl_81694D60 = 90.0f;
extern "C" const f32 lbl_81694D64 = 253.0f;
extern "C" const f32 lbl_81694D68 = 20.0f;
extern "C" const u8 lbl_81694D6C = 0xff;
extern "C" const u8 lbl_81694D6D = 0x32;
extern "C" const u8 lbl_81694D6E = 0x32;
extern "C" const u8 lbl_81694D6F = 0;
extern "C" const f32 lbl_81694D70 = 255.0f;
extern "C" const f32 lbl_81694D74 = 127.0f;
extern "C" const f32 lbl_81694D78 = 14592.0f;
extern "C" const f64 lbl_81694D80 = 4503599627370496.0;
extern "C" const f32 lbl_81694D88 = 15.0f;
extern "C" f32 lbl_81698D1C;

bool mbHyphen;

#pragma push
#pragma section const_type ".data"
extern "C" const char lbl_8165C820[] = "P_txtScrll_UP";
extern "C" const char lbl_8165C830[] = "P_txtScrll_DOWN";
extern "C" const void* lbl_8165C840[32] = {
    0,
    lbl_8165C820,
    (const void*)0x00000008,
    0,
    csAninationFile__Q29textinput9inputform,
    csAninationFile__Q29textinput9inputform + 1,
    csAninationFile__Q29textinput9inputform + 2,
    csAninationFile__Q29textinput9inputform + 3,
    csAninationFile__Q29textinput9inputform + 4,
    csAninationFile__Q29textinput9inputform + 5,
    csAninationFile__Q29textinput9inputform + 6,
    0,
    0,
    0,
    0,
    0,
    lbl_8165C830,
    (const void*)0x00000008,
    0,
    csAninationFile__Q29textinput9inputform,
    csAninationFile__Q29textinput9inputform + 1,
    csAninationFile__Q29textinput9inputform + 2,
    csAninationFile__Q29textinput9inputform + 3,
    csAninationFile__Q29textinput9inputform + 4,
    csAninationFile__Q29textinput9inputform + 5,
    csAninationFile__Q29textinput9inputform + 6,
    0,
    0,
    0,
    0,
    0,
    0,
};
extern "C" const char lbl_8165C8C0[] = "N_JPNUSAEUR";
extern "C" const char lbl_8165C8CC[] = "N_separateBarAll";
extern "C" const char lbl_8165C8E0[] = "T_2l_TextBox";
extern "C" const char lbl_8165C8F0[] = "T_title_textJPN";
extern "C" const char lbl_8165C900[] = "N_separateBarKOR";
extern "C" const char lbl_8165C918[] = "T_2l_TextBoxKOR";
extern "C" const char lbl_8165C928[] = "T_title_textKOR";
extern "C" const char lbl_8165C938[] = "N_separateBarCHN";
extern "C" const char lbl_8165C950[] = "T_2l_TextBoxCHN";
extern "C" const char lbl_8165C960[] = "T_title_textCHN";
extern "C" const u16 lbl_8165C970[16] = {
    0x00a4, 0x00ac, 0x00af, 0x00b2, 0x00b3, 0x00b6, 0x00b8, 0x00b9,
    0x00bc, 0x00bd, 0x00be, 0x00d0, 0x00de, 0x00f0, 0x00fe, 0x0000,
};

extern "C" u16 ToIndependentClass__Q39textinput9inputform13DeadKeyStreamFw(u16 code) {
    if (code < 0x300 || code > 0x330) {
        return code;
    }
    switch (code) {
        case 0x300:
            return 0x60;
        case 0x301:
            return 0xb4;
        case 0x302:
            return 0x5e;
        case 0x303:
            return 0x7e;
        case 0x308:
            return 0xa8;
        case 0x30d:
            return 0x27;
        case 0x30e:
            return 0x22;
        case 0x327:
            return 0xb8;
        default:
            return code;
    }
}

void Base::setLanguage(Language language) {
    meLanguage = language;
    switch (language) {
        case JP:
            setPredictMode(PM_Atok);
            break;
        case USA:
            setPredictMode(PM_USEn);
            break;
        case UK:
            setPredictMode(PM_En);
            break;
        case FR:
            setPredictMode(PM_De);
            break;
        case DE:
            setPredictMode(PM_It);
            break;
        case IT:
            setPredictMode(PM_Nl);
            break;
        case SP:
            if (meDestination == DST_EU) {
                setPredictMode(PM_Sp);
            } else {
                setPredictMode(PM_USSp);
            }
            break;
        case NL:
            if (meDestination == DST_EU) {
                setPredictMode(PM_Fr);
            } else {
                setPredictMode(PM_USFr);
            }
            break;
        case CN:
            setPredictMode(PM_11);
            break;
        case KR:
            setPredictMode(PM_12);
            break;
        default:
            break;
    }
}

extern "C" const char lbl_8165CBE0[] = "T_2l_TextBox";
extern "C" const char lbl_8165D258[] = "RevoIpl_RodinNTLGProM_32_I4.brfnt";
extern "C" const char lbl_8165D27C[] = "P_txtScrll_UP";
extern "C" const char lbl_8165D28C[] = "P_txtScrll_DOWN";
extern "C" const char lbl_8165D2A0[] = "N_separateBarAll";
extern "C" const char lbl_8165D2B0[] = "T_title_text";
extern "C" const char lbl_8165D2C0[] = "OutOfLength\n";
extern "C" const char lbl_8165D2D0[] = "Error#004\nAn error has occurred.\nThe system files are corrupted.";
#pragma pop

enum Animation {
    ANM_Normal
};

enum KeyType {
    KT_NormalButton
};

class AnmPane : public nw4rmanager::AnmPane {
public:
    virtual void init();
    virtual void changeAnimation(u32 id);
    virtual KeyType getKeyType() const;
    virtual Animation getState();

protected:
    Animation meState;
    KeyType meKeyType;
};

class NormalButtonAnmPane : public AnmPane {
public:
    virtual ~NormalButtonAnmPane();
};

class EventHandler : public nw4rmanager::TiEventHandler {
public:
    virtual ~EventHandler();
};

void Base::enableSpaceByRight(bool rightWithSpace) {
    mbRightWithSpace = rightWithSpace;
}

void Base::setDestination(Destination destination) {
    meDestination = destination;
}

extern "C" asm bool findURL__Q39textinput9inputform4BaseFPUlPUlPCwUlUl() {
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    addi r11, r1, 0x40
    bl _savegpr_20
    lis r27, pppURLCheck@ha
    mr r20, r4
    mr r21, r5
    mr r22, r6
    mr r26, r7
    mr r23, r8
    addi r27, r27, pppURLCheck@l
    li r29, 0
    li r28, 1
    b findURL_L8
findURL_L1:
    slwi r3, r26, 1
    lhzx r0, r22, r3
    cmpwi r0, 0x41
    bge findURL_L2
    cmpwi r0, 0xd
    beq findURL_L4
    bge findURL_L3
    cmpwi r0, 0xa
    beq findURL_L4
    bge findURL_L7
    cmpwi r0, 0
    beq findURL_L5
    b findURL_L7
findURL_L3:
    cmpwi r0, 0x30
    bge findURL_L6
    cmpwi r0, 0x20
    beq findURL_L4
    b findURL_L7
findURL_L6:
    cmpwi r0, 0x3a
    bge findURL_L7
    b findURL_L10
findURL_L2:
    cmpwi r0, 0x68
    beq findURL_L9
    bge findURL_L11
    cmpwi r0, 0x5b
    bge findURL_L12
    cmpwi r0, 0x48
    beq findURL_L9
    b findURL_L10
findURL_L12:
    cmpwi r0, 0x61
    bge findURL_L10
    b findURL_L7
findURL_L11:
    cmpwi r0, 0x3000
    beq findURL_L4
    bge findURL_L7
    cmpwi r0, 0x7b
    bge findURL_L7
    b findURL_L10
findURL_L5:
    cmpwi r29, 0
    beq findURL_L13
    cmpwi r21, 0
    beq findURL_L13
    stw r26, 0(r21)
findURL_L13:
    mr r3, r29
    b findURL_L14
findURL_L4:
    cmpwi r29, 0
    bne findURL_L15
    li r28, 1
    b findURL_L16
findURL_L15:
    cmpwi r21, 0
    beq findURL_L17
    stw r26, 0(r21)
findURL_L17:
    li r3, 1
    b findURL_L14
findURL_L9:
    cmpwi r28, 0
    beq findURL_L16
    cmpwi r29, 0
    bne findURL_L16
    mr r31, r27
    add r30, r22, r3
    li r28, 0
    li r25, 0
findURL_L18:
    mr r3, r31
    bl wcslen
    mr r24, r3
    mr r3, r30
    mr r4, r31
    mr r5, r24
    bl wcsnicmp
    cmpwi r3, 0
    bne findURL_L19
    cmpwi r20, 0
    beq findURL_L20
    stw r26, 0(r20)
findURL_L20:
    add r3, r26, r24
    li r29, 1
    subi r26, r3, 1
    b findURL_L16
findURL_L19:
    addi r25, r25, 1
    addi r31, r31, 0x14
    cmplwi r25, 2
    blt findURL_L18
    b findURL_L16
findURL_L10:
    li r28, 0
    b findURL_L16
findURL_L7:
    li r28, 1
findURL_L16:
    addi r26, r26, 1
findURL_L8:
    cmplw r26, r23
    blt findURL_L1
    mr r3, r29
findURL_L14:
    addi r11, r1, 0x40
    bl _restgpr_20
    lwz r0, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}

extern "C" asm void autoScroll__Q39textinput9inputform4BaseFv() {
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stfd f31, 0x30(r1)
    psq_st f31, 0x38(r1), 0, 0
    stw r31, 0x2c(r1)
    stw r30, 0x28(r1)
    mr r30, r3
    lwz r12, 0x18c(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    addi r3, r3, 0x18c
    bctrl
    cmpwi r3, 0
    bne autoScroll_Lend
    lwz r3, 0x1b0(r30)
    subi r0, r3, 1
    cmplwi r0, 1
    bgt autoScroll_Lend
    lwz r12, 0x5c(r30)
    addi r3, r30, 0x10
    lwz r12, 0x28(r12)
    mtctr r12
    bctrl
    lfs f0, lbl_81694D3C(r0)
    lfs f2, 0x180(r30)
    fmuls f1, f1, f0
    lfs f0, lbl_81694D28(r0)
    fadds f31, f2, f1
    fcmpo cr0, f31, f0
    bge autoScroll_L2
    lwz r12, 0x5c(r30)
    addi r3, r30, 0x10
    lwz r12, 0x28(r12)
    mtctr r12
    bctrl
    fdivs f1, f31, f1
    lfs f0, lbl_81694D38(r0)
    lwz r12, 0x5c(r30)
    addi r3, r30, 0x10
    lwz r12, 0x28(r12)
    fsubs f0, f1, f0
    fctiwz f0, f0
    stfd f0, 0x18(r1)
    lwz r31, 0x1c(r1)
    mtctr r12
    bctrl
    xoris r3, r31, 0x8000
    lis r0, 0x4330
    stw r3, 0x24(r1)
    addi r3, r30, 0x18c
    lwz r12, 0x18c(r30)
    li r4, 0
    stw r0, 0x20(r1)
    li r5, 0
    lfd f3, lbl_81694D30(r0)
    lfd f2, 0x20(r1)
    lfs f0, 0x188(r30)
    fsubs f2, f2, f3
    lwz r12, 8(r12)
    lfs f3, lbl_81694D88(r0)
    fmuls f2, f2, f1
    fmr f1, f0
    fsubs f2, f0, f2
    mtctr r12
    bctrl
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 0xb
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl
autoScroll_L2:
    lwz r12, 0(r30)
    mr r3, r30
    lwz r12, 0x188(r12)
    mtctr r12
    bctrl
    lfs f1, 0x124(r30)
    lfs f0, 0x12c(r30)
    stw r4, 0x14(r1)
    fsubs f1, f1, f0
    lfs f0, 0x14(r1)
    stw r3, 0x10(r1)
    fmuls f0, f1, f0
    fcmpo cr0, f31, f0
    cror eq, gt, eq
    bne autoScroll_L3
    lwz r12, 0(r30)
    mr r3, r30
    lwz r12, 0x188(r12)
    mtctr r12
    bctrl
    lwz r12, 0x5c(r30)
    stw r3, 8(r1)
    addi r3, r30, 0x10
    lwz r12, 0x28(r12)
    stw r4, 0xc(r1)
    mtctr r12
    bctrl
    lfs f2, 0x124(r30)
    addi r3, r30, 0x10
    lfs f0, 0x12c(r30)
    lwz r12, 0x5c(r30)
    fsubs f2, f2, f0
    lfs f0, 0xc(r1)
    lwz r12, 0x28(r12)
    fmuls f0, f2, f0
    fsubs f0, f31, f0
    fdivs f0, f0, f1
    fctiwz f0, f0
    stfd f0, 0x20(r1)
    lwz r4, 0x24(r1)
    addi r31, r4, 1
    mtctr r12
    bctrl
    xoris r3, r31, 0x8000
    lis r0, 0x4330
    stw r3, 0x1c(r1)
    addi r3, r30, 0x18c
    lwz r12, 0x18c(r30)
    li r4, 0
    stw r0, 0x18(r1)
    li r5, 0
    lfd f3, lbl_81694D30(r0)
    lfd f2, 0x18(r1)
    lfs f0, 0x188(r30)
    fsubs f2, f2, f3
    lwz r12, 8(r12)
    lfs f3, lbl_81694D88(r0)
    fmuls f2, f2, f1
    fmr f1, f0
    fsubs f2, f0, f2
    mtctr r12
    bctrl
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 0xb
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl
autoScroll_L3:
    li r0, 0
    stw r0, 0x1b0(r30)
autoScroll_Lend:
    psq_l f31, 0x38(r1), 0, 0
    lwz r0, 0x44(r1)
    lfd f31, 0x30(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}

extern "C" asm void startAnm__Q39textinput4util9AnimationFfffPQ39textinput4util12AnimObserverPv() {
    nofralloc
    lfs f0, lbl_81694D28(r0)
    li r6, 1
    li r0, 0
    cmpwi r4, 0
    stfs f1, 4(r3)
    stfs f2, 8(r3)
    stfs f3, 0x10(r3)
    stfs f0, 0xc(r3)
    stb r6, 0x14(r3)
    stw r4, 0x18(r3)
    stw r5, 0x1c(r3)
    stb r0, 0x15(r3)
    beqlr
    mr r3, r4
    li r4, 0
    lwz r12, 0(r3)
    lwz r12, 8(r12)
    mtctr r12
    bctr
    blr
}

extern "C" asm void deselectCandidate__Q39textinput9inputform4BaseFv() {
    nofralloc
    lbz r0, 0x178(r3)
    cmpwi r0, 0
    beqlr
    lwz r0, 0x174(r3)
    cmpwi r0, 1
    bnelr
    lwz r3, 0x168(r3)
    li r4, -1
    lwz r12, 0(r3)
    lwz r12, 0xf0(r12)
    mtctr r12
    bctr
    blr
}

extern "C" asm void resetRelation__Q39textinput9inputform4BaseFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r3, 0x1d4(r3)
    lwz r12, 0(r3)
    lwz r12, 0x6c(r12)
    mtctr r12
    bctrl
    li r0, 0
    stb r0, 0x15(r3)
    stb r0, 0x16(r3)
    lwz r3, 0x168(r31)
    lwz r12, 0(r3)
    lwz r12, 0x128(r12)
    mtctr r12
    bctrl
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void init__Q39textinput9inputform4BaseFv() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    lfs f0, lbl_81694D28(r0)
    stw r0, 0x24(r1)
    li r0, 0xff
    stw r31, 0x1c(r1)
    li r31, 0
    stw r30, 0x18(r1)
    mr r30, r3
    stw r31, 0x170(r3)
    stfs f0, 0x17c(r3)
    stfs f0, 0x180(r3)
    stfs f0, 0x184(r3)
    stfs f0, 0x188(r3)
    stfs f0, 0x1ac(r3)
    stfs f0, 0x1c4(r3)
    stb r0, 0x1c8(r3)
    addi r3, r3, 0x1d8
    bl KPRInitQueue
    addi r3, r30, 0x1d8
    li r4, 2
    bl KPRSetMode
    addi r3, r30, 0x10
    bl GetFont__Q34nw4r2ut10CharWriterCFv
    lwz r12, 0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    xoris r3, r3, 0x8000
    lis r0, 0x4330
    stw r3, 0xc(r1)
    addi r3, r30, 0x10
    lfd f1, lbl_81694D30(r0)
    stw r0, 8(r1)
    lfd f0, 8(r1)
    fsubs f1, f0, f1
    bl SetFixedWidth__Q34nw4r2ut10CharWriterFf
    addi r3, r30, 0x10
    li r4, 0
    bl EnableFixedWidth__Q34nw4r2ut10CharWriterFb
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 1
    lwz r12, 0x130(r12)
    mtctr r12
    bctrl
    lwz r3, 0x1d4(r30)
    lwz r12, 0(r3)
    lwz r12, 0x6c(r12)
    mtctr r12
    bctrl
    stb r31, 0x15(r3)
    stb r31, 0x16(r3)
    lwz r3, 0x168(r30)
    lwz r12, 0(r3)
    lwz r12, 0x128(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r30)
    mr r3, r30
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl
    lwz r12, 0x5c(r30)
    addi r3, r30, 0x10
    lwz r12, 0x90(r12)
    mtctr r12
    bctrl
    lwz r12, 0x5c(r30)
    addi r3, r30, 0x10
    lwz r12, 0x94(r12)
    mtctr r12
    bctrl
    lfs f0, 0x188(r30)
    stfs f0, 0x100(r30)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    stw r30, 0x18(r1)
    mr r30, r5
    stw r29, 0x14(r1)
    mr r29, r4
    stw r4, 0x1d0(r3)
    addi r3, r3, 0x10
    bl create__Q39textinput10textdrawer4BaseFP12MEMAllocator
    lwz r0, 4(r30)
    mr r3, r29
    lhz r4, 0x1fc(r31)
    stw r0, 0x164(r31)
    addi r0, r4, 2
    lwz r5, 8(r30)
    slwi r4, r0, 3
    stw r5, 0x168(r31)
    lwz r0, 0xc(r30)
    stw r0, 0x16c(r31)
    stw r29, 0x200(r31)
    bl MEMAllocFromAllocator
    stw r3, 0x1f8(r31)
    addi r3, r31, 0x1f8
    bl init__Q49textinput9inputform4Base14RowInfoManagerFv
    lhz r0, 0x1fc(r31)
    lwz r6, 0x1f8(r31)
    slwi r0, r0, 3
    add r3, r6, r0
    lhz r0, 2(r3)
    slwi r0, r0, 3
    add r5, r6, r0
    lhzx r8, r6, r0
    lhz r7, 2(r5)
    slwi r0, r8, 3
    slwi r4, r7, 3
    lhzx r9, r6, r4
    add r3, r6, r0
    sthx r8, r6, r4
    cmplw r9, r9
    sth r7, 2(r3)
    sth r9, 0(r5)
    sth r9, 2(r5)
    lhz r3, 0x1fc(r31)
    lwz r6, 0x1f8(r31)
    addi r0, r3, 1
    clrlslwi r0, r0, 16, 3
    lhzx r0, r6, r0
    slwi r0, r0, 3
    add r4, r6, r0
    bne create_L1
    lhz r7, 2(r4)
    slwi r3, r7, 3
    lhzx r0, r6, r3
    sth r0, 0(r5)
    sth r7, 2(r5)
    sth r9, 2(r4)
    sthx r9, r6, r3
create_L1:
    li r3, 0
    li r0, 1
    sth r3, 4(r5)
    sth r0, 6(r5)
    stw r5, 0x204(r31)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void getCurrentString__Q39textinput9inputform4BaseFb() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 8(r1)
    mr r30, r3
    lbz r0, 0x178(r3)
    cmpwi r0, 0
    bne getCurrentString_L1
    lwz r3, 0x164(r3)
    b getCurrentString_Lend
getCurrentString_L1:
    lwz r0, 0x1f0(r3)
    cmpwi r0, 9
    bne getCurrentString_L2
    lwz r3, 0x1d4(r3)
    lwz r12, 0(r3)
    lwz r12, 0x94(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq getCurrentString_L3
    lwz r3, 0x1d4(r30)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r3)
    lwz r12, 0x58(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    bne getCurrentString_L2
    lwz r3, 0x164(r30)
    b getCurrentString_Lend
getCurrentString_L3:
    lwz r3, 0x1d4(r30)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r3)
    lwz r12, 0x40(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq getCurrentString_L2
    lwz r3, 0x164(r30)
    b getCurrentString_Lend
getCurrentString_L2:
    lwz r0, 0x1f0(r30)
    cmpwi r0, 8
    bne getCurrentString_L4
    lwz r3, 0x1d4(r30)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r3)
    lwz r12, 0x4c(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    bne getCurrentString_L5
    lwz r3, 0x1d4(r30)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r3)
    lwz r12, 0x10c(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    bne getCurrentString_L4
getCurrentString_L5:
    lwz r3, 0x164(r30)
    b getCurrentString_Lend
getCurrentString_L4:
    lwz r0, 0x174(r30)
    cmpwi r0, 1
    beq getCurrentString_L6
    b getCurrentString_L7
getCurrentString_L6:
    lwz r3, 0x168(r30)
    lwz r12, 0(r3)
    lwz r12, 0xd0(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq getCurrentString_L8
    cmpwi r31, 0
    beq getCurrentString_L9
getCurrentString_L8:
    lwz r3, 0x168(r30)
    b getCurrentString_Lend
getCurrentString_L7:
    lwz r3, 0x16c(r30)
    lwz r12, 0(r3)
    lwz r12, 0xec(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq getCurrentString_L10
    cmpwi r31, 0
    beq getCurrentString_L9
getCurrentString_L10:
    lwz r3, 0x16c(r30)
    b getCurrentString_Lend
getCurrentString_L9:
    lwz r3, 0x164(r30)
getCurrentString_Lend:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm bool isVacancy__Q39textinput9inputform4BaseCFv() {
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    mr r31, r3
    lwz r3, 0x164(r3)
    lwz r12, 0(r3)
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 16
    bne isVacancy_L1
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    bne isVacancy_L2
isVacancy_L1:
    li r3, 0
    b isVacancy_Lend
isVacancy_L2:
    lwz r0, 0x174(r31)
    cmpwi r0, 1
    bne isVacancy_L3
    lwz r3, 0x168(r31)
    lwz r12, 0(r3)
    lwz r12, 0xd0(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    bne isVacancy_L4
    li r3, 0
    b isVacancy_Lend
isVacancy_L4:
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 16
    beq isVacancy_L5
    li r3, 0
    b isVacancy_Lend
isVacancy_L5:
    lwz r3, 0x168(r31)
    lwz r12, 0(r3)
    lwz r12, 0xf4(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq isVacancy_L6
    li r3, 0
    b isVacancy_Lend
isVacancy_L3:
    cmpwi r0, 0xc
    bne isVacancy_L7
    li r3, 1
    b isVacancy_Lend
isVacancy_L7:
    cmpwi r0, 0
    beq isVacancy_L6
    lwz r3, 0x16c(r31)
    lwz r12, 0(r3)
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 16
    beq isVacancy_L8
    li r3, 0
    b isVacancy_Lend
isVacancy_L8:
    lwz r3, 0x16c(r31)
    addi r4, r1, 8
    li r5, 0x10
    bl getCurrentInput__Q39textinput8tistring6WithZiFPwUl
    cmpwi r3, 0
    ble isVacancy_L9
    li r3, 0
    b isVacancy_Lend
isVacancy_L9:
    lbz r3, 0x1f5(r31)
    lbz r0, 0x1f4(r31)
    or. r0, r3, r0
    beq isVacancy_L6
    lwz r3, 0x16c(r31)
    lwz r12, 0(r3)
    lwz r12, 0xe0(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq isVacancy_L6
    lhz r0, 0(r3)
    cmplwi r0, 0xfffe
    beq isVacancy_L6
    li r3, 0
    b isVacancy_Lend
isVacancy_L6:
    li r3, 1
isVacancy_Lend:
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

extern "C" asm void notifyChangeMode__Q39textinput9inputform4BaseFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r0, 0x174(r3)
    cmpwi r0, 1
    bne notifyChangeMode_L1
    lwz r3, 0x1d4(r3)
    lwz r12, 0(r3)
    lwz r12, 0x94(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq notifyChangeMode_L2
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r3)
    lwz r12, 0x48(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq notifyChangeMode_L2
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r3)
    lwz r12, 0x58(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq notifyChangeMode_L3
notifyChangeMode_L2:
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x94(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    bne notifyChangeMode_L3
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r3)
    lwz r12, 0x40(r12)
    mtctr r12
    bctrl
notifyChangeMode_L3:
    lwz r3, 0x168(r31)
    lwz r12, 0(r3)
    lwz r12, 0x124(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 16
    bne notifyChangeMode_L4
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl
    b notifyChangeMode_L4
notifyChangeMode_L1:
    cmpwi r0, 0xc
    bne notifyChangeMode_L5
    lwz r3, 0x1d4(r3)
    lwz r12, 0(r3)
    lwz r12, 0x94(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    li r4, 0xb
    beq notifyChangeMode_L6
    li r4, 0xa
notifyChangeMode_L6:
    lwz r3, 0x16c(r31)
    lwz r12, 0(r3)
    lwz r12, 0xf0(r12)
    mtctr r12
    bctrl
    b notifyChangeMode_L4
notifyChangeMode_L5:
    cmpwi r0, 0xb
    bne notifyChangeMode_L4
    lbz r0, 0x178(r3)
    cmpwi r0, 0
    beq notifyChangeMode_L4
    lwz r3, 0x16c(r3)
    li r4, 0
    bl setCurrentWord__Q39textinput8tistring6WithZiFPCw
notifyChangeMode_L4:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void updateCandidateState___Q39textinput9inputform4BaseFv() {
    nofralloc
    stwu r1, -0xa0(r1)
    mflr r0
    stw r0, 0xa4(r1)
    stw r31, 0x9c(r1)
    stw r30, 0x98(r1)
    stw r29, 0x94(r1)
    mr r29, r3
    lbz r0, 0x178(r3)
    cmpwi r0, 0
    beq updateCandidateState_Lend
    lwz r0, 0x174(r3)
    cmpwi r0, 1
    bne updateCandidateState_L1
    lwz r3, 0x168(r3)
    lwz r12, 0(r3)
    lwz r12, 0x110(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq updateCandidateState_L2
    lwz r3, 0x168(r29)
    lwz r12, 0(r3)
    lwz r12, 0xe0(r12)
    mtctr r12
    bctrl
    mr r31, r3
    lwz r3, 0x164(r29)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl
    lwz r3, 0x164(r29)
    mr r4, r31
    lwz r12, 0(r3)
    lwz r12, 0x60(r12)
    mtctr r12
    bctrl
    lwz r3, 0x164(r29)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl
    lwz r3, 0x168(r29)
    li r4, 0
    lwz r12, 0(r3)
    lwz r12, 0x114(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r29)
    mr r3, r29
    li r4, 9
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl
updateCandidateState_L2:
    li r0, 0
    mr r3, r29
    stb r0, 8(r1)
    addi r5, r1, 8
    li r4, 0x23
    bl onCommand__Q29textinput15CommandReceiverFQ39textinput15CommandReceiver13INPUT_COMMANDPv
    addi r3, r29, 0x118
    bl resetCandidate__Q39textinput12candidatebox18CandidateBoxCallerFv
    lbz r0, 8(r1)
    cmpwi r0, 0
    bne updateCandidateState_Lend
    lwz r3, 0x168(r29)
    lwz r12, 0(r3)
    lwz r12, 0xe4(r12)
    mtctr r12
    bctrl
    mr r31, r3
    li r30, 0
    b updateCandidateState_L3
updateCandidateState_L4:
    lwz r3, 0x168(r29)
    mr r4, r30
    addi r5, r1, 0x10
    lwz r12, 0(r3)
    lwz r12, 0xe8(r12)
    mtctr r12
    bctrl
    addi r3, r29, 0x118
    addi r4, r1, 0x10
    bl addCandidate__Q39textinput12candidatebox18CandidateBoxCallerFPCw
    addi r30, r30, 1
updateCandidateState_L3:
    cmpw r30, r31
    blt updateCandidateState_L4
    addi r3, r29, 0x118
    bl updateCandidate__Q39textinput12candidatebox18CandidateBoxCallerFv
    b updateCandidateState_Lend
updateCandidateState_L1:
    addi r3, r3, 0x118
    bl resetCandidate__Q39textinput12candidatebox18CandidateBoxCallerFv
    lwz r3, 0x16c(r29)
    lwz r12, 0(r3)
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl
    mr r31, r3
    li r30, 0
    b updateCandidateState_L5
updateCandidateState_L6:
    lwz r3, 0x16c(r29)
    mr r4, r30
    addi r5, r1, 0x10
    lwz r12, 0(r3)
    lwz r12, 0xdc(r12)
    mtctr r12
    bctrl
    addi r3, r29, 0x118
    addi r4, r1, 0x10
    bl addCandidate__Q39textinput12candidatebox18CandidateBoxCallerFPCw
    addi r30, r30, 1
updateCandidateState_L5:
    cmpw r30, r31
    blt updateCandidateState_L6
    addi r3, r29, 0x118
    bl updateCandidate__Q39textinput12candidatebox18CandidateBoxCallerFv
updateCandidateState_Lend:
    lwz r0, 0xa4(r1)
    lwz r31, 0x9c(r1)
    lwz r30, 0x98(r1)
    lwz r29, 0x94(r1)
    mtlr r0
    addi r1, r1, 0xa0
    blr
}

extern "C" asm void moveCursorUp__Q39textinput9inputform4BaseFv() {
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stfd f31, 0x20(r1)
    psq_st f31, 0x28(r1), 0, 0
    lfs f0, lbl_81694D28(r0)
    stw r31, 0x1c(r1)
    mr r31, r3
    lfs f31, 0x180(r3)
    lfs f1, 0x188(r3)
    fsubs f1, f31, f1
    fneg f1, f1
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne moveCursorUp_L1
    lwz r3, 0x164(r3)
    addi r4, r1, 0xc
    addi r5, r1, 8
    lwz r12, 0(r3)
    lwz r12, 0x80(r12)
    mtctr r12
    bctrl
    lwz r0, 0xc(r1)
    cmpwi r0, 0
    bne moveCursorUp_L2
    lwz r0, 8(r1)
    cmpwi r0, 0
    bne moveCursorUp_L2
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 6
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl
    b moveCursorUp_L3
moveCursorUp_L2:
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 5
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl
moveCursorUp_L3:
    lwz r3, 0x164(r31)
    li r4, 0
    lwz r12, 0(r3)
    lwz r12, 0x6c(r12)
    mtctr r12
    bctrl
    b moveCursorUp_L4
moveCursorUp_L1:
    fcmpo cr0, f31, f0
    cror eq, gt, eq
    bne moveCursorUp_L5
    b moveCursorUp_L6
moveCursorUp_L5:
    fmr f31, f0
moveCursorUp_L6:
    lwz r12, 0x5c(r3)
    lwz r12, 0x28(r12)
    mtctr r12
    addi r3, r3, 0x10
    bctrl
    fsubs f2, f31, f1
    lwz r12, 0(r31)
    lfs f0, lbl_81694D38(r0)
    mr r3, r31
    lwz r12, 0x180(r12)
    fadds f2, f0, f2
    lfs f1, 0x17c(r31)
    mtctr r12
    bctrl
    mr r4, r3
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x6c(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 5
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl
moveCursorUp_L4:
    li r0, 1
    stw r0, 0x1b0(r31)
    psq_l f31, 0x28(r1), 0, 0
    lfd f31, 0x20(r1)
    lwz r31, 0x1c(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

extern "C" asm void moveCursorDown__Q39textinput9inputform4BaseFv() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    lfs f2, 0x180(r3)
    lfs f1, 0x188(r3)
    lfs f0, 0xc8(r3)
    fsubs f1, f2, f1
    fneg f1, f1
    fcmpo cr0, f1, f0
    bge moveCursorDown_L1
    lwz r3, 0x164(r3)
    addi r4, r1, 0xc
    addi r5, r1, 8
    lwz r12, 0(r3)
    lwz r12, 0x80(r12)
    mtctr r12
    bctrl
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl
    lwz r0, 0xc(r1)
    clrlwi r3, r3, 16
    cmplw r0, r3
    bne moveCursorDown_L2
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl
    lwz r0, 8(r1)
    clrlwi r3, r3, 16
    cmplw r0, r3
    bne moveCursorDown_L2
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 6
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl
    b moveCursorDown_L3
moveCursorDown_L2:
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 5
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl
moveCursorDown_L3:
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl
    clrlwi r4, r3, 16
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x6c(r12)
    mtctr r12
    bctrl
    b moveCursorDown_L4
moveCursorDown_L1:
    lwz r12, 0x5c(r3)
    lwz r12, 0x28(r12)
    mtctr r12
    addi r3, r3, 0x10
    bctrl
    lfs f0, 0x180(r31)
    mr r3, r31
    lwz r12, 0(r31)
    fadds f2, f0, f1
    lfs f0, lbl_81694D38(r0)
    lwz r12, 0x180(r12)
    lfs f1, 0x17c(r31)
    fadds f2, f0, f2
    mtctr r12
    bctrl
    mr r4, r3
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x6c(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 5
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl
moveCursorDown_L4:
    li r0, 1
    stw r0, 0x1b0(r31)
    lwz r31, 0x1c(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void onPressLeft__Q39textinput9inputform4BaseFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    stw r30, 8(r1)
    mr r30, r3
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r12, 0(r3)
    mr r31, r3
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl
    lwz r0, 0x164(r30)
    cmplw r31, r0
    bne onPressLeft_L1
    lwz r0, 0x1f0(r30)
    cmpwi r0, 9
    bne onPressLeft_L2
    mr r3, r30
    li r4, 0
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r12, 0(r3)
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    bne onPressLeft_L3
    lwz r3, 0x164(r30)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl
    lwz r3, 0x164(r30)
    li r4, 0xa
    lwz r12, 0(r3)
    lwz r12, 0x50(r12)
    mtctr r12
    bctrl
    lwz r3, 0x164(r30)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl
    lwz r0, 0x1f0(r30)
    cmpwi r0, 8
    bne onPressLeft_L3
    lbz r0, 0x178(r30)
    cmpwi r0, 0
    bne onPressLeft_L4
    li r0, 0
    b onPressLeft_L5
onPressLeft_L4:
    lwz r0, 0x174(r30)
    cmpwi r0, 1
    beq onPressLeft_L6
    lwz r3, 0x16c(r30)
    lwz r12, 0(r3)
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    ble onPressLeft_L6
    li r0, 1
    b onPressLeft_L5
onPressLeft_L6:
    li r0, 0
onPressLeft_L5:
    cmpwi r0, 0
    beq onPressLeft_L3
    lwz r3, 0x16c(r30)
    li r4, 0
    bl setCurrentWord__Q39textinput8tistring6WithZiFPCw
    lwz r3, 0x16c(r30)
    bl update__Q39textinput8tistring6WithZiFv
onPressLeft_L3:
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl
onPressLeft_L2:
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0x48(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    bne onPressLeft_Lend
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    bne onPressLeft_L13
    b onPressLeft_Lend
onPressLeft_L13:
    lwz r3, 0x1d4(r30)
    lwz r12, 0(r3)
    lwz r12, 0x6c(r12)
    mtctr r12
    bctrl
    li r0, 0
    stb r0, 0x15(r3)
    stb r0, 0x16(r3)
    lwz r3, 0x168(r30)
    lwz r12, 0(r3)
    lwz r12, 0x128(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r30)
    mr r3, r30
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl
    lwz r3, 0x168(r30)
    lwz r12, 0(r3)
    lwz r12, 0x44(r12)
    mtctr r12
    bctrl
    clrlwi r0, r3, 16
    cmplwi r0, 0x20
    beq onPressLeft_Lend
onPressLeft_L1:
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0x68(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq onPressLeft_L10
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 5
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl
    b onPressLeft_L11
onPressLeft_L10:
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 6
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl
onPressLeft_L11:
    lwz r0, 0x168(r30)
    cmplw r31, r0
    bne onPressLeft_L12
    lwz r12, 0(r30)
    mr r3, r30
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl
onPressLeft_L12:
    li r0, 1
    stw r0, 0x1b0(r30)
onPressLeft_Lend:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void onPressRight__Q39textinput9inputform4BaseFv() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    li r4, 0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r30, r3
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r12, 0(r3)
    mr r31, r3
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl
    lwz r0, 0x164(r30)
    cmplw r31, r0
    bne onPressRight_L1
    lwz r0, 0x1f0(r30)
    cmpwi r0, 9
    bne onPressRight_L2
    mr r3, r30
    li r4, 0
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r12, 0(r3)
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    bne onPressRight_L3
    lwz r3, 0x164(r30)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl
    lwz r3, 0x164(r30)
    li r4, 0xa
    lwz r12, 0(r3)
    lwz r12, 0x50(r12)
    mtctr r12
    bctrl
    lwz r3, 0x164(r30)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl
    lwz r0, 0x1f0(r30)
    cmpwi r0, 8
    bne onPressRight_L3
    lbz r0, 0x178(r30)
    cmpwi r0, 0
    bne onPressRight_L4
    li r0, 0
    b onPressRight_L5
onPressRight_L4:
    lwz r0, 0x174(r30)
    cmpwi r0, 1
    beq onPressRight_L6
    lwz r3, 0x16c(r30)
    lwz r12, 0(r3)
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    ble onPressRight_L6
    li r0, 1
    b onPressRight_L5
onPressRight_L6:
    li r0, 0
onPressRight_L5:
    cmpwi r0, 0
    beq onPressRight_L3
    lwz r3, 0x16c(r30)
    li r4, 0
    bl setCurrentWord__Q39textinput8tistring6WithZiFPCw
    lwz r3, 0x16c(r30)
    bl update__Q39textinput8tistring6WithZiFv
onPressRight_L3:
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl
onPressRight_L2:
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0x48(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    bne onPressRight_Lend
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    bne onPressRight_L13
    b onPressRight_Lend
onPressRight_L13:
    lwz r3, 0x1d4(r30)
    lwz r12, 0(r3)
    lwz r12, 0x6c(r12)
    mtctr r12
    bctrl
    li r0, 0
    stb r0, 0x15(r3)
    stb r0, 0x16(r3)
    lwz r3, 0x168(r30)
    lwz r12, 0(r3)
    lwz r12, 0x128(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r30)
    mr r3, r30
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl
    lwz r3, 0x168(r30)
    lwz r12, 0(r3)
    lwz r12, 0x44(r12)
    mtctr r12
    bctrl
    clrlwi r0, r3, 16
    cmplwi r0, 0x20
    beq onPressRight_Lend
onPressRight_L1:
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0x64(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq onPressRight_L8
    lbz r0, 0x17a(r30)
    cmpwi r0, 0
    beq onPressRight_L8
    lis r9, lbl_816152D0@ha
    lwzu r8, lbl_816152D0@l(r9)
    mr r3, r30
    addi r5, r1, 8
    lwz r7, 4(r9)
    li r4, 0
    lwz r6, 8(r9)
    lwz r0, 0xc(r9)
    stw r8, 8(r1)
    stw r7, 0xc(r1)
    stw r6, 0x10(r1)
    stw r0, 0x14(r1)
    lwz r12, 0(r30)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 5
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl
onPressRight_L8:
    lwz r0, 0x16c(r30)
    cmplw r31, r0
    beq onPressRight_L9
    lwz r0, 0x168(r30)
    cmplw r31, r0
    bne onPressRight_L10
onPressRight_L9:
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 6
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl
    b onPressRight_L11
onPressRight_L10:
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 5
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl
onPressRight_L11:
    lwz r0, 0x168(r30)
    cmplw r31, r0
    bne onPressRight_L12
    lwz r12, 0(r30)
    mr r3, r30
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl
onPressRight_L12:
    li r0, 1
    stw r0, 0x1b0(r30)
onPressRight_Lend:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void calc__Q39textinput9inputform4BaseFv() {
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stfd f31, 0x30(r1)
    psq_st f31, 0x38(r1), 0, 0
    stw r31, 0x2c(r1)
    stw r30, 0x28(r1)
    mr r30, r3
    lwz r12, 0x18c(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    addi r3, r3, 0x18c
    bctrl
    cmpwi r3, 0
    beq calc_L1
    lwz r12, 0x18c(r30)
    addi r3, r30, 0x18c
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    frsp f0, f1
    stfs f1, 0x188(r30)
    stfs f0, 0x100(r30)
calc_L1:
    lwz r12, 0x18c(r30)
    addi r3, r30, 0x18c
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    bne calc_L2
    lwz r12, 0(r30)
    mr r3, r30
    lwz r12, 0x16c(r12)
    mtctr r12
    bctrl
calc_L2:
    lwz r3, 0x164(r30)
    lwz r12, 0(r3)
    lwz r12, 0x78(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    bne calc_L3
    lfs f1, lbl_81694D38(r0)
    lfs f0, 0x1ac(r30)
    fadds f0, f1, f0
    stfs f0, 0x1ac(r30)
calc_L3:
    lwz r12, 0x18c(r30)
    addi r3, r30, 0x18c
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    lfs f1, lbl_81698D1C(r0)
    lfs f0, lbl_81694D40(r0)
    fmuls f1, f0, f1
    bl SinFIdx__Q24nw4r4mathFf
    lfs f0, lbl_81694D48(r0)
    li r0, 0x5a
    li r3, 2
    li r31, 0xfd
    fmuls f2, f0, f1
    lfs f0, lbl_81694D44(r0)
    stb r3, 0x1c0(r30)
    fmr f31, f1
    lwz r3, 0x164(r30)
    fadds f0, f0, f2
    stb r0, 0x1c1(r30)
    fctiwz f0, f0
    stb r31, 0x1c2(r30)
    stfd f0, 8(r1)
    lwz r0, 0xc(r1)
    stb r0, 0x1c3(r30)
    lwz r12, 0(r3)
    lwz r12, 0x78(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq calc_L4
    lfs f1, lbl_81694D50(r0)
    li r0, 0x8c
    li r3, 0x34
    lfs f0, lbl_81694D4C(r0)
    fmuls f1, f1, f31
    stb r0, 0x1c1(r30)
    stb r3, 0x1c0(r30)
    fadds f0, f0, f1
    stb r31, 0x1c2(r30)
    fctiwz f0, f0
    stfd f0, 8(r1)
    lwz r0, 0xc(r1)
    stb r0, 0x1c3(r30)
    b calc_L7
calc_L4:
    lfs f1, 0x1ac(r30)
    lfs f5, lbl_81694D4C(r0)
    fcmpo cr0, f1, f5
    cror eq, lt, eq
    bne calc_L7
    lfs f2, lbl_81694D28(r0)
    lfs f3, lbl_81694D54(r0)
    fmr f4, f2
    lfs f6, lbl_81694D58(r0)
    fmr f7, f2
    bl hermiteInterporation__Q29textinput4utilFfffffff
    fctiwz f0, f1
    lfs f2, lbl_81694D28(r0)
    lfs f1, 0x1ac(r30)
    fmr f4, f2
    lfs f3, lbl_81694D5C(r0)
    stfd f0, 8(r1)
    fmr f7, f2
    lfs f5, lbl_81694D4C(r0)
    lwz r0, 0xc(r1)
    lfs f6, lbl_81694D60(r0)
    stb r0, 0x1c0(r30)
    bl hermiteInterporation__Q29textinput4utilFfffffff
    fctiwz f0, f1
    lfs f2, lbl_81694D28(r0)
    lfs f3, lbl_81694D64(r0)
    fmr f4, f2
    lfs f1, 0x1ac(r30)
    stfd f0, 0x10(r1)
    fmr f6, f3
    lfs f5, lbl_81694D4C(r0)
    lwz r0, 0x14(r1)
    fmr f7, f2
    stb r0, 0x1c1(r30)
    bl hermiteInterporation__Q29textinput4utilFfffffff
    fctiwz f1, f1
    lfs f2, lbl_81698D1C(r0)
    lfs f0, lbl_81694D40(r0)
    stfd f1, 0x18(r1)
    fmuls f1, f0, f2
    lwz r0, 0x1c(r1)
    stb r0, 0x1c2(r30)
    bl SinFIdx__Q24nw4r4mathFf
    lfs f2, lbl_81694D28(r0)
    fmr f31, f1
    lfs f3, lbl_81694D4C(r0)
    fmr f4, f2
    lfs f1, 0x1ac(r30)
    fmr f5, f3
    lfs f6, lbl_81694D44(r0)
    fmr f7, f2
    bl hermiteInterporation__Q29textinput4utilFfffffff
    lfs f0, lbl_81694D68(r0)
    fmuls f0, f0, f31
    fadds f0, f1, f0
    fctiwz f0, f0
    stfd f0, 0x20(r1)
    lwz r0, 0x24(r1)
    stb r0, 0x1c3(r30)
calc_L7:
    lwz r3, 0x214(r30)
    lfs f1, lbl_81698D1C(r0)
    lfs f0, lbl_81694D58(r0)
    addi r0, r3, 8
    stw r0, 0x214(r30)
    fadds f0, f1, f0
    stfs f0, lbl_81698D1C(r0)
    psq_l f31, 0x38(r1), 0, 0
    lfd f31, 0x30(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r0, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}

extern "C" asm void __dt__Q39textinput9inputform4BaseFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    cmpwi r3, 0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 8(r1)
    mr r30, r3
    beq baseDestructor_L1
    addic. r0, r3, 0x1f8
    beq baseDestructor_L2
    lwz r3, 0x200(r3)
    lwz r4, 0x1f8(r30)
    bl MEMFreeToAllocator
baseDestructor_L2:
    addic. r3, r30, 0x10
    beq baseDestructor_L3
    li r4, 0
    bl __dt__Q34nw4r2ut10CharWriterFv
baseDestructor_L3:
    cmpwi r31, 0
    ble baseDestructor_L1
    mr r3, r30
    bl __dl__FPv
baseDestructor_L1:
    mr r3, r30
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void __ct__Q39textinput9inputform4BaseFPQ29textinput7Manager() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_27
    lis r12, __vt__Q29textinput15CommandReceiver@ha
    mr r31, r3
    addi r12, r12, __vt__Q29textinput15CommandReceiver@l
    mr r27, r4
    stw r12, 0(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    addi r28, r31, 0x10
    mr r3, r28
    bl __ct__Q34nw4r2ut10CharWriterFv
    lfs f1, lbl_81694D28(r0)
    lis r4, __vt__Q39textinput10textdrawer4Base@ha
    li r29, 0
    lfs f0, lbl_81694D2C(r0)
    lis r3, 1
    addi r4, r4, __vt__Q39textinput10textdrawer4Base@l
    subi r0, r3, 1
    li r30, 1
    stw r4, 0x4c(r28)
    addi r3, r28, 0xf8
    li r4, 0
    li r5, 0xc
    stw r29, 0x50(r28)
    stfs f1, 0x88(r28)
    stfs f1, 0x8c(r28)
    stfs f1, 0x90(r28)
    stfs f1, 0x94(r28)
    stfs f0, 0x98(r28)
    stb r29, 0x9c(r28)
    stb r29, 0x9d(r28)
    stw r29, 0xa0(r28)
    stfs f1, 0xa4(r28)
    stfs f1, 0xa8(r28)
    stfs f1, 0xac(r28)
    stfs f1, 0xb0(r28)
    stfs f1, 0xb4(r28)
    stfs f1, 0xb8(r28)
    stw r29, 0xbc(r28)
    stw r0, 0xc0(r28)
    stb r29, 0xc8(r28)
    stw r29, 0xcc(r28)
    stw r29, 0xd0(r28)
    stw r29, 0xd4(r28)
    stw r29, 0xd8(r28)
    stw r29, 0xdc(r28)
    stw r29, 0xe0(r28)
    stb r29, 0xe4(r28)
    stfs f1, 0xe8(r28)
    stfs f1, 0xec(r28)
    stfs f1, 0xf0(r28)
    stw r29, 0xf4(r28)
    stb r29, 0x104(r28)
    stb r30, 0x105(r28)
    bl memset
    lis r10, __vt__Q39textinput9inputform4Base@ha
    lfs f0, lbl_81694D28(r0)
    addi r10, r10, __vt__Q39textinput9inputform4Base@l
    lis r6, __vt__Q39textinput4util9Animation@ha
    addi r9, r10, 0x20
    li r7, 2
    addi r8, r10, 0xb8
    addi r6, r6, __vt__Q39textinput4util9Animation@l
    li r5, 0x400
    li r4, 0x270f
    li r3, 0xff
    li r0, -1
    stw r29, 0x11c(r31)
    stw r10, 0(r31)
    stw r9, 0x5c(r31)
    stw r8, 0x118(r31)
    stfs f0, 0x120(r31)
    stfs f0, 0x124(r31)
    stfs f0, 0x128(r31)
    stfs f0, 0x12c(r31)
    stw r29, 0x164(r31)
    stw r29, 0x168(r31)
    stw r29, 0x16c(r31)
    stw r29, 0x170(r31)
    stw r7, 0x174(r31)
    stb r29, 0x178(r31)
    stb r30, 0x179(r31)
    stb r30, 0x17a(r31)
    stfs f0, 0x17c(r31)
    stfs f0, 0x180(r31)
    stfs f0, 0x184(r31)
    stfs f0, 0x188(r31)
    stw r6, 0x18c(r31)
    stfs f0, 0x19c(r31)
    stb r29, 0x1a0(r31)
    stb r29, 0x1a1(r31)
    stw r29, 0x1a4(r31)
    stfs f0, 0x1ac(r31)
    stw r29, 0x1b0(r31)
    stw r29, 0x1b4(r31)
    stw r5, 0x1b8(r31)
    stw r4, 0x1bc(r31)
    stfs f0, 0x1c4(r31)
    stb r3, 0x1c8(r31)
    stw r0, 0x1cc(r31)
    stw r29, 0x1d0(r31)
    stw r27, 0x1d4(r31)
    bl KPRInitRegionUS
    addi r3, r31, 0x1d8
    bl KPRInitQueue
    addi r3, r31, 0x1d8
    li r4, 2
    bl KPRSetMode
    lwz r0, 0x1b8(r31)
    addi r11, r1, 0x20
    stw r30, 0x1f0(r31)
    mr r3, r31
    stb r29, 0x1f4(r31)
    stb r29, 0x1f5(r31)
    stw r29, 0x1f8(r31)
    sth r0, 0x1fc(r31)
    stw r29, 0x200(r31)
    stw r29, 0x204(r31)
    sth r29, 0x20c(r31)
    stb r30, 0x20e(r31)
    stw r29, 0x210(r31)
    stw r29, 0x214(r31)
    bl _restgpr_27
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void EnableKSXFilter__Q39textinput8tistring9DecolatedFb() {
    nofralloc
    blr
}
extern "C" asm void backSpace__Q39textinput8tistring8WithAtokFv() {
    nofralloc
    blr
}
extern "C" asm void changeKanaMode__Q39textinput8tistring8WithAtokFb() {
    nofralloc
    blr
}
extern "C" asm void closeDictionary__Q39textinput8tistring8WithAtokFv() {
    nofralloc
    blr
}
extern "C" asm void commitPredicted__Q39textinput8tistring8WithAtokFi() {
    nofralloc
    blr
}
extern "C" asm void confirm__Q39textinput8tistring8WithAtokFPCw() {
    nofralloc
    blr
}
extern "C" asm void deleteChar__Q39textinput8tistring9DecolatedFv() {
    nofralloc
    blr
}
extern "C" asm void enableConfirmedString__Q39textinput8tistring8WithAtokFb() {
    nofralloc
    blr
}
extern "C" asm void getCursorPos__Q39textinput8tistring8WithAtokFPUlPUl() {
    nofralloc
    blr
}
extern "C" asm void getDrawString__Q39textinput8tistring8WithAtokFRQ49textinput8tistring8WithAtok8DrawInfo() {
    nofralloc
    blr
}
extern "C" asm void getPredicted__Q39textinput8tistring8WithAtokFiPw() {
    nofralloc
    blr
}
extern "C" asm void initConverting__Q39textinput8tistring8WithAtokFv() {
    nofralloc
    blr
}
extern "C" asm void init__Q29textinput4BaseFv() {
    nofralloc
    blr
}
extern "C" asm void init__Q39textinput8tistring8WithAtokFv() {
    nofralloc
    blr
}
extern "C" asm void inputChar__Q39textinput8tistring8WithAtokFw() {
    nofralloc
    blr
}
extern "C" asm void openDictionary__Q39textinput8tistring8WithAtokFPviPviPvi() {
    nofralloc
    blr
}
extern "C" asm void popBack__Q39textinput8tistring8WithAtokFv() {
    nofralloc
    blr
}
extern "C" asm void pushBack__Q39textinput8tistring8WithAtokFw() {
    nofralloc
    blr
}
extern "C" asm void resetRelation__Q39textinput8tistring8WithAtokFv() {
    nofralloc
    blr
}
extern "C" asm void setDefaultPrediction__Q39textinput8tistring8WithAtokFiPPCc() {
    nofralloc
    blr
}
extern "C" asm void setFixMode__Q39textinput8tistring8WithAtokFb() {
    nofralloc
    blr
}
extern "C" asm void setFixPrediction__Q39textinput8tistring8WithAtokFiPPCc() {
    nofralloc
    blr
}
extern "C" asm void setFix__Q39textinput8tistring8WithAtokFb() {
    nofralloc
    blr
}
extern "C" asm void setInputting__Q39textinput8tistring8WithAtokFw() {
    nofralloc
    blr
}
extern "C" asm void setSelectedCandidate__Q39textinput8tistring8WithAtokFl() {
    nofralloc
    blr
}
extern "C" asm void startConverting__Q39textinput8tistring8WithAtokFv() {
    nofralloc
    blr
}

extern "C" asm void dirtyDrawCache__Q39textinput10textdrawer4BaseFv() {
    nofralloc
    li r0, 0
    stb r0, 0xe4(r3)
    blr
}
extern "C" asm void dirtyCursorCache__Q39textinput10textdrawer4BaseFv() {
    nofralloc
    li r0, 0
    stb r0, 0x104(r3)
    blr
}
extern "C" asm void getCursorPos__Q39textinput8tistring9DecolatedCFv() {
    nofralloc
    lwz r3, 0x18(r3)
    blr
}
extern "C" asm void getCellPhoneKeyboard__Q29textinput7ManagerFv() {
    nofralloc
    lwz r3, 0x18(r3)
    blr
}
extern "C" asm void isConverting__Q39textinput8tistring8WithAtokFv() {
    nofralloc
    li r3, 0
    blr
}
extern "C" asm void getLine__Q39textinput10textdrawer4BaseFv() {
    nofralloc
    lwz r3, 0xa0(r3)
    addi r3, r3, 1
    blr
}
extern "C" asm void getSelectedConverting__Q39textinput8tistring8WithAtokFv() {
    nofralloc
    li r3, 0
    blr
}
extern "C" asm void isOnSustain__Q39textinput8tistring9DecolatedFv() {
    nofralloc
    lbz r3, 0x20(r3)
    blr
}
extern "C" asm void setSelectedCandidate__Q39textinput8tistring6WithZiFl() {
    nofralloc
    stw r4, 0x98(r3)
    blr
}
extern "C" asm void isDictionaryOpened__Q39textinput8tistring8WithAtokFv() {
    nofralloc
    li r3, 0
    blr
}
extern "C" asm void getConfirmedWCString__Q39textinput8tistring8WithAtokCFv() {
    nofralloc
    li r3, 0
    blr
}
extern "C" asm void setPredictLaunguage__Q39textinput8tistring6WithZiFQ49textinput8tistring6WithZi15PredictLanguage() {
    nofralloc
    stw r4, 0x9c(r3)
    blr
}
extern "C" asm void hasConfirmedString__Q39textinput8tistring8WithAtokFv() {
    nofralloc
    li r3, 0
    blr
}
extern "C" asm void getCurrentNumPredicted__Q39textinput8tistring8WithAtokFv() {
    nofralloc
    li r3, 0
    blr
}
extern "C" asm void getCurrentNumPredicted__Q39textinput8tistring6WithZiFv() {
    nofralloc
    lwz r3, 0x8c(r3)
    blr
}
extern "C" asm void getDrawModifyEndLine__Q39textinput10textdrawer4BaseCFv() {
    nofralloc
    lwz r3, 0xd0(r3)
    blr
}
extern "C" asm void getEndPos__Q39textinput10textdrawer4BaseCFv() {
    nofralloc
    lwz r3, 0xc0(r3)
    blr
}
extern "C" asm void getLength__Q39textinput8tistring10StringBaseCFv() {
    nofralloc
    lhz r3, 0x6(r3)
    blr
}
extern "C" asm void isActive__Q39textinput4util9AnimationFv() {
    nofralloc
    lbz r3, 0x14(r3)
    blr
}
extern "C" asm void getKanaBuffer__Q39textinput8tistring9DecolatedFv() {
    nofralloc
    addi r3, r3, 0x42
    blr
}
extern "C" asm void getCandidate__Q39textinput8tistring10StringBaseCFv() {
    nofralloc
    lhz r3, 0x10(r3)
    blr
}
extern "C" asm void getInputStringLength__Q39textinput8tistring6WithZiFv() {
    nofralloc
    lhz r3, 0x88(r3)
    blr
}
extern "C" asm void isCandidateSelected__Q39textinput8tistring8WithAtokFv() {
    nofralloc
    li r3, 0
    blr
}
extern "C" asm void getSelectedCandidate__Q39textinput8tistring8WithAtokFv() {
    nofralloc
    li r3, 0
    blr
}
extern "C" asm void isInvalid__Q39textinput12candidatebox4BaseCFv() {
    nofralloc
    lbz r3, 0x19(r3)
    blr
}
extern "C" asm void hasCandidate__Q39textinput8tistring10StringBaseCFv() {
    nofralloc
    lhz r3, 0x10(r3)
    neg r0, r3
    or r0, r0, r3
    srwi r3, r0, 31
    blr
}
extern "C" asm void setCandidate__Q39textinput8tistring10StringBaseFw() {
    nofralloc
    sth r4, 0x10(r3)
    blr
}
extern "C" asm void changeLetterMode__Q39textinput8tistring6WithZiFQ49textinput8tistring6WithZi10LetterMode() {
    nofralloc
    stw r4, 0xa0(r3)
    blr
}
extern "C" asm void setCellPhoneHoldingkey__Q39textinput8tistring6WithZiFPv() {
    nofralloc
    stw r4, 0xa4(r3)
    blr
}
extern "C" asm void isFix__Q39textinput8tistring8WithAtokFv() {
    nofralloc
    li r3, 1
    blr
}
extern "C" asm void getCandidateBox__Q29textinput7ManagerCFv() {
    nofralloc
    lwz r3, 0x20(r3)
    blr
}
extern "C" asm void getFixedPredictionNum__Q39textinput8tistring8WithAtokFv() {
    nofralloc
    li r3, 0
    blr
}
extern "C" asm void getInputStringLength__Q39textinput8tistring8WithAtokFv() {
    nofralloc
    li r3, 0
    blr
}
extern "C" asm void getHWKeyboard__Q29textinput7ManagerFv() {
    nofralloc
    lwz r3, 0x10(r3)
    blr
}
extern "C" asm void create__Q39textinput9inputform4BaseFP12MEMAllocator() {
    nofralloc
    blr
}
extern "C" asm void getDrawModifyStartLine__Q39textinput10textdrawer4BaseCFv() {
    nofralloc
    lwz r3, 0xcc(r3)
    blr
}
extern "C" asm void getStartPos__Q39textinput10textdrawer4BaseCFv() {
    nofralloc
    lwz r3, 0xbc(r3)
    blr
}
extern "C" asm void setVIWidth__Q39textinput10textdrawer4BaseFf() {
    nofralloc
    stfs f1, 0x98(r3)
    blr
}
extern "C" asm void setCandidateBox__Q39textinput12candidatebox18CandidateBoxCallerFPQ39textinput12candidatebox4Base() {
    nofralloc
    stw r4, 4(r3)
    blr
}
extern "C" asm void moveCursorLeft__Q39textinput8tistring8WithAtokFv() {
    nofralloc
    li r3, 0
    blr
}
extern "C" asm void moveCursorRight__Q39textinput8tistring8WithAtokFv() {
    nofralloc
    li r3, 0
    blr
}
extern "C" asm void stop__Q39textinput4util9AnimationFv() {
    nofralloc
    li r0, 0
    stb r0, 0x14(r3)
    blr
}
extern "C" asm void isSEFlag__Q39textinput4util9AnimationFv() {
    nofralloc
    lbz r3, 0x15(r3)
    blr
}
extern "C" asm void setSEFlag__Q39textinput4util9AnimationFb() {
    nofralloc
    stb r4, 0x15(r3)
    blr
}
extern "C" asm void getValue__Q39textinput4util9AnimationFv() {
    nofralloc
    lfs f2, lbl_81694D28(r0)
    lfs f1, 0xc(r3)
    fmr f4, f2
    lfs f3, 0x4(r3)
    fmr f7, f2
    lfs f5, 0x10(r3)
    lfs f6, 0x8(r3)
    b hermiteInterporation__Q29textinput4utilFfffffff
}
extern "C" asm void getDrawCacheStartPos__Q39textinput10textdrawer4BaseCFv() {
    nofralloc
    lbz r0, 0xe4(r3)
    cmpwi r0, 0
    beq getDrawCacheStartPos_L1
    lwz r3, 0xdc(r3)
    blr
getDrawCacheStartPos_L1:
    lis r3, 0x8000
    subi r3, r3, 1
    blr
}
extern "C" asm void onSE__Q39textinput9inputform12LayoutByNW4RFQ39textinput5sound2SE() {
    nofralloc
    lwz r3, 0x22c(r3)
    lwz r12, 0(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctr
}
extern "C" asm void addSender__Q29textinput15CommandReceiverFPQ29textinput13CommandSender() {
    nofralloc
    addi r3, r3, 4
    b List_Append__Q24nw4r2utFPQ34nw4r2ut4ListPv
}
extern "C" asm void isInScroll__Q39textinput12candidatebox12LayoutByNW4RFv() {
    nofralloc
    addi r3, r3, 0xe4
    b IsScrolling__Q39textinput12candidatebox10UITextAreaFv
}
extern "C" asm void __dt__Q39textinput8tistring9DecolatedFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    cmpwi r3, 0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 8(r1)
    mr r30, r3
    beq __dt_Decolated_L1
    li r4, 0
    bl __dt__Q39textinput8tistring10StringBaseFv
    cmpwi r31, 0
    ble __dt_Decolated_L1
    mr r3, r30
    bl __dl__FPv
__dt_Decolated_L1:
    mr r3, r30
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
extern "C" asm void __dt__Q39textinput8tistring8WithAtokFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    cmpwi r3, 0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 8(r1)
    mr r30, r3
    beq __dt_WithAtok_L1
    beq __dt_WithAtok_L2
    li r4, 0
    bl __dt__Q39textinput8tistring10StringBaseFv
__dt_WithAtok_L2:
    cmpwi r31, 0
    ble __dt_WithAtok_L1
    mr r3, r30
    bl __dl__FPv
__dt_WithAtok_L1:
    mr r3, r30
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
extern "C" asm void __dt__Q29textinput15CommandReceiverFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    cmpwi r3, 0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    beq __dt_CommandReceiver_L1
    cmpwi r4, 0
    ble __dt_CommandReceiver_L1
    bl __dl__FPv
__dt_CommandReceiver_L1:
    mr r3, r31
    lwz r31, 0xc(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
extern "C" asm bool isKanaFix__Q39textinput8tistring9DecolatedCFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    lwz r0, 0x24(r3)
    cmpwi r0, 3
    bne isKanaFix_L1
    li r3, 1
    b isKanaFix_L2
isKanaFix_L1:
    li r4, 0
    li r5, 0
    addi r3, r3, 0x28
    bl KPRLookAhead
    clrlwi r0, r3, 24
    cntlzw r0, r0
    srwi r3, r0, 5
isKanaFix_L2:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
extern "C" asm void calc__Q39textinput4util9AnimationFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lbz r0, 0x14(r3)
    cmpwi cr1, r0, 0
    beq cr1, calc_Animation_L4
    lfs f1, 0xc(r3)
    lfs f0, 0x10(r3)
    fcmpo cr0, f1, f0
    bge calc_Animation_L1
    lfs f0, lbl_81694D38(r0)
    fadds f0, f0, f1
    stfs f0, 0xc(r3)
    b calc_Animation_L4
calc_Animation_L1:
    beq cr1, calc_Animation_L3
    lwz r3, 0x18(r3)
    cmpwi r3, 0
    beq calc_Animation_L3
    lwz r12, 0(r3)
    li r4, 1
    lwz r5, 0x1c(r31)
    lwz r12, 8(r12)
    mtctr r12
    bctrl
calc_Animation_L3:
    li r0, 0
    stb r0, 0x14(r31)
calc_Animation_L4:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
extern "C" asm void set__Q39textinput8tistring9DecolatedFPCw() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    bl set__Q39textinput8tistring10StringBaseFPCw
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl
    clrlwi r0, r3, 16
    stw r0, 0x18(r31)
    stw r0, 0x1c(r31)
    lwz r31, 0xc(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
extern "C" asm void clear__Q39textinput8tistring9DecolatedFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    bl clear__Q39textinput8tistring10StringBaseFv
    li r0, 0
    mr r3, r31
    stw r0, 0x18(r31)
    stw r0, 0x1c(r31)
    stb r0, 0x20(r31)
    lwz r12, 0(r31)
    lwz r12, 0xb8(r12)
    mtctr r12
    bctrl
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
extern "C" asm void init__Q49textinput9inputform4Base14RowInfoManagerFv() {
    nofralloc
    li r8, 0
    li r4, 0
    b init_RowInfo_L1
init_RowInfo_L2:
    lwz r7, 0(r3)
    subi r5, r8, 1
    clrlslwi r6, r8, 16, 3
    addi r0, r8, 1
    sthux r5, r6, r7
    addi r8, r8, 1
    sth r0, 2(r6)
    sth r4, 4(r6)
    sth r4, 6(r6)
init_RowInfo_L1:
    lhz r5, 4(r3)
    clrlwi r0, r8, 16
    cmplw r0, r5
    blt init_RowInfo_L2
    lhz r0, 4(r3)
    subi r5, r5, 1
    lwz r7, 0(r3)
    li r4, 0
    slwi r6, r0, 3
    clrlslwi r0, r5, 16, 3
    sthux r5, r6, r7
    sth r4, 2(r6)
    lwz r6, 0(r3)
    lhz r5, 4(r3)
    add r4, r6, r0
    sth r5, 2(r4)
    lhz r0, 4(r3)
    sth r0, 0(r6)
    lhz r5, 4(r3)
    lwz r4, 0(r3)
    addi r5, r5, 1
    clrlslwi r0, r5, 16, 3
    sthux r5, r4, r0
    lhz r3, 4(r3)
    addi r0, r3, 1
    sth r0, 2(r4)
    blr
}
asm nw4r::math::VEC2 LayoutByNW4R::getScale() const {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lwz r6, 0x21c(r3)
    li r5, 1
    stw r0, 0x14(r1)
    lwz r4, 0x2c0(r3)
    lwz r3, 0x10(r6)
    lwz r12, 0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    lwz r0, 0x14(r1)
    mr r4, r3
    lwz r3, 0x44(r3)
    lwz r4, 0x48(r4)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
extern "C" asm void __dt__Q39textinput9inputform12LayoutByNW4RFv() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    cmpwi r3, 0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r30, r4
    stw r29, 0x14(r1)
    mr r29, r3
    beq __dt_Layout_L1
    lwz r7, 0x2d0(r3)
    lis r6, __vt__Q39textinput9inputform12LayoutByNW4R@ha
    addi r6, r6, __vt__Q39textinput9inputform12LayoutByNW4R@l
    addi r5, r6, 0x20
    cmpwi r7, 0
    addi r4, r6, 0xb8
    addi r0, r6, 0x1a8
    stw r6, 0(r3)
    stw r5, 0x5c(r3)
    stw r4, 0x118(r3)
    stw r0, 0x218(r3)
    beq __dt_Layout_L2
    lwz r12, 0(r7)
    mr r3, r7
    li r4, -1
    lwz r12, 8(r12)
    mtctr r12
    bctrl
    lwz r3, 0x1d0(r29)
    lwz r4, 0x2d0(r29)
    bl MEMFreeToAllocator
__dt_Layout_L2:
    addi r3, r29, 0x284
    li r4, 0
    bl List_GetNext__Q24nw4r2utFPCQ34nw4r2ut4ListPCv
    mr r31, r3
    b __dt_Layout_L4
__dt_Layout_L3:
    mr r4, r31
    addi r3, r29, 0x284
    bl List_Remove__Q24nw4r2utFPQ34nw4r2ut4ListPv
    lwz r4, 0x1d0(r29)
    mr r3, r31
    bl destroy__Q39textinput11nw4rmanager7AnmPaneFP12MEMAllocator
    addi r3, r29, 0x284
    li r4, 0
    bl List_GetNext__Q24nw4r2utFPCQ34nw4r2ut4ListPCv
    mr r31, r3
__dt_Layout_L4:
    cmpwi r31, 0
    bne __dt_Layout_L3
    addi r3, r29, 0x2d4
    li r4, -1
    bl __dt__Q34nw4r2ut7ResFontFv
    addi r3, r29, 0x218
    li r4, 0
    bl __dt__Q39textinput11nw4rmanager6LayoutFv
    cmpwi r29, 0
    beq __dt_Layout_L5
    addic. r0, r29, 0x1f8
    beq __dt_Layout_L6
    lwz r3, 0x200(r29)
    lwz r4, 0x1f8(r29)
    bl MEMFreeToAllocator
__dt_Layout_L6:
    addic. r3, r29, 0x10
    beq __dt_Layout_L5
    li r4, 0
    bl __dt__Q34nw4r2ut10CharWriterFv
__dt_Layout_L5:
    cmpwi r30, 0
    ble __dt_Layout_L1
    mr r3, r29
    bl __dl__FPv
__dt_Layout_L1:
    lwz r31, 0x1c(r1)
    mr r3, r29
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
extern "C" asm void __ct__Q39textinput9inputform12LayoutByNW4RFPQ29textinput7ManagerPQ34nw4r3lyt24MultiArcResourceAccessorPCcPQ29textinput13EventObserverPCc() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r11, r1, 0x20
    bl _savegpr_27
    mr r27, r3
    mr r28, r5
    mr r29, r6
    mr r30, r7
    mr r31, r8
    bl __ct__Q39textinput9inputform4BaseFPQ29textinput7Manager
    mr r4, r28
    mr r5, r29
    mr r6, r30
    addi r3, r27, 0x218
    bl __ct__Q39textinput11nw4rmanager6LayoutFPQ34nw4r3lyt24MultiArcResourceAccessorPCcPQ29textinput13EventObserver
    lis r6, __vt__Q39textinput9inputform12LayoutByNW4R@ha
    li r0, 0
    addi r6, r6, __vt__Q39textinput9inputform12LayoutByNW4R@l
    lis r5, lbl_8165CBE0@ha
    lis r4, csLanguageDependencyDataUEJ__Q29textinput9inputform@ha
    stw r6, 0(r27)
    addi r3, r6, 0x20
    addi r7, r6, 0xb8
    addi r6, r6, 0x1a8
    addi r5, r5, lbl_8165CBE0@l
    addi r4, r4, csLanguageDependencyDataUEJ__Q29textinput9inputform@l
    stw r3, 0x5c(r27)
    addi r3, r27, 0x2d4
    stw r7, 0x118(r27)
    stw r6, 0x218(r27)
    stw r5, 0x2c0(r27)
    stw r4, 0x2c4(r27)
    stw r31, 0x2c8(r27)
    stb r0, 0x2cc(r27)
    stb r0, 0x2cd(r27)
    stb r0, 0x2ce(r27)
    stw r0, 0x2d0(r27)
    bl __ct__Q34nw4r2ut7ResFontFv
    addi r11, r1, 0x20
    mr r3, r27
    bl _restgpr_27
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
extern "C" asm void create__Q39textinput9inputform10EditBufferFP12MEMAllocator() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    mr r29, r4
    stw r28, 0x10(r1)
    mr r28, r3
    stw r4, 0x10(r3)
    li r4, 0x4c
    mr r3, r29
    bl MEMAllocFromAllocator
    cmpwi r3, 0
    mr r30, r3
    beq create_EditBuffer_L1
    li r0, 0x400
    lis r12, __vt__Q39textinput8tistring9Decolated@ha
    sth r0, 4(r3)
    li r0, 0
    addi r12, r12, __vt__Q39textinput8tistring9Decolated@l
    sth r0, 6(r3)
    stw r0, 8(r3)
    stw r0, 0xc(r3)
    sth r0, 0x10(r3)
    stw r0, 0x14(r3)
    stw r12, 0(r3)
    stw r0, 0x18(r3)
    stw r0, 0x1c(r3)
    stb r0, 0x20(r3)
    stw r0, 0x24(r3)
    lwz r12, 0xb8(r12)
    mtctr r12
    bctrl
create_EditBuffer_L1:
    stw r30, 4(r28)
    mr r3, r30
    mr r4, r29
    lwz r12, 0(r30)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    mr r3, r29
    li r4, 0x4c
    bl MEMAllocFromAllocator
    cmpwi r3, 0
    mr r30, r3
    beq create_EditBuffer_L2
    li r0, 0x400
    lis r12, __vt__Q39textinput8tistring9Decolated@ha
    sth r0, 4(r3)
    li r0, 0
    addi r12, r12, __vt__Q39textinput8tistring9Decolated@l
    sth r0, 6(r3)
    stw r0, 8(r3)
    stw r0, 0xc(r3)
    sth r0, 0x10(r3)
    stw r0, 0x14(r3)
    stw r12, 0(r3)
    stw r0, 0x18(r3)
    stw r0, 0x1c(r3)
    stb r0, 0x20(r3)
    stw r0, 0x24(r3)
    lwz r12, 0xb8(r12)
    mtctr r12
    bctrl
    lis r3, __vt__Q39textinput8tistring8WithAtok@ha
    addi r3, r3, __vt__Q39textinput8tistring8WithAtok@l
    stw r3, 0(r30)
create_EditBuffer_L2:
    stw r30, 8(r28)
    mr r3, r30
    mr r4, r29
    lwz r12, 0(r30)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    mr r3, r29
    li r4, 0xac
    bl MEMAllocFromAllocator
    cmpwi r3, 0
    mr r30, r3
    beq create_EditBuffer_L3
    li r0, 0x400
    lis r12, __vt__Q39textinput8tistring9Decolated@ha
    sth r0, 4(r3)
    li r31, 0
    addi r12, r12, __vt__Q39textinput8tistring9Decolated@l
    sth r31, 6(r3)
    stw r31, 8(r3)
    stw r31, 0xc(r3)
    sth r31, 0x10(r3)
    stw r31, 0x14(r3)
    stw r12, 0(r3)
    stw r31, 0x18(r3)
    stw r31, 0x1c(r3)
    stb r31, 0x20(r3)
    stw r31, 0x24(r3)
    lwz r12, 0xb8(r12)
    mtctr r12
    bctrl
    lis r4, __vt__Q39textinput8tistring6WithZi@ha
    li r3, 0xff
    addi r4, r4, __vt__Q39textinput8tistring6WithZi@l
    li r0, 2
    stw r4, 0(r30)
    stb r31, 0x78(r30)
    stb r31, 0x79(r30)
    stw r31, 0x7c(r30)
    stw r31, 0x80(r30)
    stw r31, 0x84(r30)
    sth r31, 0x88(r30)
    stw r31, 0x8c(r30)
    stw r31, 0x90(r30)
    stb r3, 0x94(r30)
    stw r31, 0x98(r30)
    stw r31, 0x9c(r30)
    stw r0, 0xa0(r30)
    stw r31, 0xa4(r30)
    stb r31, 0xa8(r30)
create_EditBuffer_L3:
    stw r30, 0xc(r28)
    mr r3, r30
    mr r4, r29
    lwz r12, 0(r30)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
extern "C" asm void __dt__Q39textinput9inputform10EditBufferFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    cmpwi r3, 0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 8(r1)
    mr r30, r3
    beq __dt_EditBuffer_L1
    lwz r0, 4(r3)
    lis r4, __vt__Q39textinput9inputform10EditBuffer@ha
    addi r4, r4, __vt__Q39textinput9inputform10EditBuffer@l
    cmpwi r0, 0
    stw r4, 0(r3)
    beq __dt_EditBuffer_L2
    mr r3, r0
    li r4, -1
    lwz r12, 0(r3)
    lwz r12, 8(r12)
    mtctr r12
    bctrl
    lwz r3, 0x10(r30)
    lwz r4, 4(r30)
    bl MEMFreeToAllocator
__dt_EditBuffer_L2:
    lwz r3, 8(r30)
    cmpwi r3, 0
    beq __dt_EditBuffer_L3
    lwz r12, 0(r3)
    li r4, -1
    lwz r12, 8(r12)
    mtctr r12
    bctrl
    lwz r3, 0x10(r30)
    lwz r4, 8(r30)
    bl MEMFreeToAllocator
__dt_EditBuffer_L3:
    lwz r3, 0xc(r30)
    cmpwi r3, 0
    beq __dt_EditBuffer_L4
    lwz r12, 0(r3)
    li r4, -1
    lwz r12, 8(r12)
    mtctr r12
    bctrl
    lwz r3, 0x10(r30)
    lwz r4, 0xc(r30)
    bl MEMFreeToAllocator
__dt_EditBuffer_L4:
    li r0, 0
    cmpwi r31, 0
    stw r0, 4(r30)
    stw r0, 8(r30)
    stw r0, 0xc(r30)
    ble __dt_EditBuffer_L1
    mr r3, r30
    bl __dl__FPv
__dt_EditBuffer_L1:
    mr r3, r30
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
extern "C" asm void updateInputCommon__Q39textinput9inputform12LayoutByNW4RFiUlUlUlPv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    mr r4, r5
    mr r5, r6
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    bl updateRepeatInput__Q39textinput9inputform12LayoutByNW4RFUlUl
    lwz r0, 0x304(r31)
    rlwinm. r0, r0, 0, 19, 19
    beq updateInputCommon_L1
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 1
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
updateInputCommon_L1:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
extern "C" asm void updateRepeatInput__Q39textinput9inputform12LayoutByNW4RFUlUl() {
    nofralloc
    clrlwi. r0, r5, 31
    stw r4, 0x304(r3)
    beq updateRepeatInput_L1
    lwz r0, 0x2f4(r3)
    subic. r0, r0, 1
    stw r0, 0x2f4(r3)
    bne updateRepeatInput_L2
    ori r4, r4, 1
    li r0, 9
    stw r4, 0x304(r3)
    stw r0, 0x2f4(r3)
    b updateRepeatInput_L2
updateRepeatInput_L1:
    li r0, 0x1e
    stw r0, 0x2f4(r3)
updateRepeatInput_L2:
    rlwinm. r0, r5, 0, 30, 30
    beq updateRepeatInput_L3
    lwz r0, 0x2f8(r3)
    subic. r0, r0, 1
    stw r0, 0x2f8(r3)
    bne updateRepeatInput_L4
    lwz r4, 0x304(r3)
    li r0, 9
    stw r0, 0x2f8(r3)
    ori r0, r4, 2
    stw r0, 0x304(r3)
    b updateRepeatInput_L4
updateRepeatInput_L3:
    li r0, 0x1e
    stw r0, 0x2f8(r3)
updateRepeatInput_L4:
    rlwinm. r0, r5, 0, 28, 28
    beq updateRepeatInput_L5
    lwz r0, 0x2ec(r3)
    subic. r0, r0, 1
    stw r0, 0x2ec(r3)
    bne updateRepeatInput_L6
    lwz r4, 0x304(r3)
    li r0, 9
    stw r0, 0x2ec(r3)
    ori r0, r4, 8
    stw r0, 0x304(r3)
    b updateRepeatInput_L6
updateRepeatInput_L5:
    li r0, 0x1e
    stw r0, 0x2ec(r3)
updateRepeatInput_L6:
    rlwinm. r0, r5, 0, 29, 29
    beq updateRepeatInput_L7
    lwz r0, 0x2f0(r3)
    subic. r0, r0, 1
    stw r0, 0x2f0(r3)
    bne updateRepeatInput_L8
    lwz r4, 0x304(r3)
    li r0, 9
    stw r0, 0x2f0(r3)
    ori r0, r4, 4
    stw r0, 0x304(r3)
    b updateRepeatInput_L8
updateRepeatInput_L7:
    li r0, 0x1e
    stw r0, 0x2f0(r3)
updateRepeatInput_L8:
    rlwinm. r0, r5, 0, 19, 19
    beq updateRepeatInput_L9
    lwz r0, 0x2fc(r3)
    subic. r0, r0, 1
    stw r0, 0x2fc(r3)
    bnelr
    lwz r4, 0x304(r3)
    li r0, 9
    stw r0, 0x2fc(r3)
    ori r0, r4, 0x1000
    stw r0, 0x304(r3)
    blr
updateRepeatInput_L9:
    li r0, 0x1e
    stw r0, 0x2fc(r3)
    blr
}
extern "C" asm void ToCombineClass__Q39textinput9inputform13DeadKeyStreamFQ29textinput8Languagew() {
    nofralloc
    cmpwi r3, 5
    beq ToCombineClass_L9
    bge ToCombineClass_L1
    cmpwi r3, 3
    beq ToCombineClass_L2
    bge ToCombineClass_L3
    b ToCombineClass_L9
ToCombineClass_L1:
    cmpwi r3, 7
    beq ToCombineClass_L8
    bge ToCombineClass_L9
    b ToCombineClass_L4
ToCombineClass_L3:
    cmplwi r4, 0xb4
    bne ToCombineClass_L3a
    li r3, 0x301
    blr
ToCombineClass_L3a:
    cmplwi r4, 0x60
    bne ToCombineClass_L9
    li r3, 0x300
    blr
ToCombineClass_L2:
    cmplwi r4, 0x5e
    bne ToCombineClass_L2a
    li r3, 0x302
    blr
ToCombineClass_L2a:
    cmplwi r4, 0xa8
    bne ToCombineClass_L9
    li r3, 0x308
    blr
ToCombineClass_L4:
    cmplwi r4, 0x60
    bne ToCombineClass_L4a
    li r3, 0x300
    blr
ToCombineClass_L4a:
    cmplwi r4, 0xb4
    bne ToCombineClass_L4b
    li r3, 0x301
    blr
ToCombineClass_L4b:
    cmplwi r4, 0x5e
    bne ToCombineClass_L4c
    li r3, 0x302
    blr
ToCombineClass_L4c:
    cmplwi r4, 0x7e
    bne ToCombineClass_L4d
    li r3, 0x303
    blr
ToCombineClass_L4d:
    cmplwi r4, 0xa8
    bne ToCombineClass_L9
    li r3, 0x308
    blr
ToCombineClass_L8:
    cmplwi r4, 0x60
    bne ToCombineClass_L8a
    li r3, 0x300
    blr
ToCombineClass_L8a:
    cmplwi r4, 0x5e
    bne ToCombineClass_L8b
    li r3, 0x302
    blr
ToCombineClass_L8b:
    cmplwi r4, 0x7e
    bne ToCombineClass_L8c
    li r3, 0x303
    blr
ToCombineClass_L8c:
    cmplwi r4, 0x27
    bne ToCombineClass_L8d
    li r3, 0x30d
    blr
ToCombineClass_L8d:
    cmplwi r4, 0x22
    bne ToCombineClass_L9
    li r3, 0x30e
    blr
ToCombineClass_L9:
    mr r3, r4
    blr
}
extern "C" asm void init__Q39textinput3gui12GUIComponentFv() {
    nofralloc
    lbz r0, 4(r3)
    cmpwi r0, 0
    bnelr
    lfs f0, lbl_81694D28(r0)
    li r0, 0
    stb r0, 5(r3)
    stfs f0, 0x18(r3)
    stfs f0, 0x1c(r3)
    stfs f0, 0x20(r3)
    stb r0, 0xd(r3)
    sth r0, 0x80(r3)
    stb r0, 6(r3)
    stfs f0, 0x24(r3)
    stfs f0, 0x28(r3)
    stfs f0, 0x2c(r3)
    stb r0, 0xe(r3)
    sth r0, 0x82(r3)
    stb r0, 7(r3)
    stfs f0, 0x30(r3)
    stfs f0, 0x34(r3)
    stfs f0, 0x38(r3)
    stb r0, 0xf(r3)
    sth r0, 0x84(r3)
    stb r0, 8(r3)
    stfs f0, 0x3c(r3)
    stfs f0, 0x40(r3)
    stfs f0, 0x44(r3)
    stb r0, 0x10(r3)
    sth r0, 0x86(r3)
    stb r0, 9(r3)
    stfs f0, 0x48(r3)
    stfs f0, 0x4c(r3)
    stfs f0, 0x50(r3)
    stb r0, 0x11(r3)
    sth r0, 0x88(r3)
    stb r0, 0xa(r3)
    stfs f0, 0x54(r3)
    stfs f0, 0x58(r3)
    stfs f0, 0x5c(r3)
    stb r0, 0x12(r3)
    sth r0, 0x8a(r3)
    stb r0, 0xb(r3)
    stfs f0, 0x60(r3)
    stfs f0, 0x64(r3)
    stfs f0, 0x68(r3)
    stb r0, 0x13(r3)
    sth r0, 0x8c(r3)
    stb r0, 0xc(r3)
    stfs f0, 0x6c(r3)
    stfs f0, 0x70(r3)
    stfs f0, 0x74(r3)
    stb r0, 0x14(r3)
    sth r0, 0x8e(r3)
    blr
}

asm bool Base::isEditMode() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    lwz r0, 0x174(r3)
    cmpwi r0, 2
    bge isEditMode_L1
    cmpwi r0, 0
    bge isEditMode_L2
isEditMode_L1:
    lwz r3, 0x16c(r3)
    lwz r12, 0(r3)
    lwz r12, 0xec(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    bne isEditMode_L2
    li r3, 0
    b isEditMode_L3
isEditMode_L2:
    li r3, 1
isEditMode_L3:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

asm bool Base::checkHeadOfSentence(bool checkSpace) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r5, r1, 8
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r30, r4
    li r4, 0x20
    stw r29, 0x14(r1)
    mr r29, r3
    lwz r12, 0(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    lbz r0, 8(r1)
    cmpwi r0, 0
    beq checkHeadOfSentence_L1
    li r3, 0
    b checkHeadOfSentence_L7
checkHeadOfSentence_L1:
    lwz r3, 0x164(r29)
    li r31, 0
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl
    cmplwi r3, 1
    bge checkHeadOfSentence_L2
    li r3, 1
    b checkHeadOfSentence_L7
checkHeadOfSentence_L2:
    cmpwi r30, 0
    beq checkHeadOfSentence_L5
    lwz r3, 0x164(r29)
    lwz r12, 0(r3)
    lwz r12, 0x90(r12)
    mtctr r12
    bctrl
    clrlwi r0, r3, 0x10
    cmpwi r0, 0x20
    beq checkHeadOfSentence_L4
    bge checkHeadOfSentence_L3
    cmpwi r0, 0xa
    beq checkHeadOfSentence_L4
checkHeadOfSentence_L3:
    li r3, 0
    b checkHeadOfSentence_L7
checkHeadOfSentence_L4:
    lwz r3, 0x164(r29)
    lwz r12, 0(r3)
    lwz r12, 0x68(r12)
    mtctr r12
    bctrl
    mr r31, r3
checkHeadOfSentence_L5:
    lwz r3, 0x164(r29)
    lwz r12, 0(r3)
    lwz r12, 0xb4(r12)
    mtctr r12
    bctrl
    cmpwi r31, 0
    mr r31, r3
    beq checkHeadOfSentence_L6
    lwz r3, 0x164(r29)
    lwz r12, 0(r3)
    lwz r12, 0x64(r12)
    mtctr r12
    bctrl
checkHeadOfSentence_L6:
    mr r3, r31
checkHeadOfSentence_L7:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

void Base::setLineDrawInfo(bool lineDraw, u32 lineCount) {
    mbLineDraw = lineDraw;
    muSpecifyLineDrawCount = lineCount;
}

void Base::doWordWrap(bool wordWrap) {
    mbDoWordWrap = wordWrap;
}

void Base::limitStringLength(u32 limitStringLength) {
    muLimitStringLength = limitStringLength;
}

asm void Base::setAtokDictionary(void*, int, void*, int, void*, int) {
    nofralloc
    lwz r3, 0x168(r3)
    lwz r12, 0(r3)
    lwz r12, 0x108(r12)
    mtctr r12
    bctr
}

extern "C" asm void setCursorPos__Q39textinput9inputform4BaseFPQ39textinput8tistring9DecolatedUl() {
    nofralloc
    mr r3, r4
    mr r4, r5
    lwz r12, 0(r3)
    lwz r12, 0x6c(r12)
    mtctr r12
    bctr
}

asm void Base::closeAtokDictionary() {
    nofralloc
    lwz r3, 0x168(r3)
    lwz r12, 0(r3)
    lwz r12, 0x10c(r12)
    mtctr r12
    bctr
}

asm bool Base::isAtokDictionaryOpened() {
    nofralloc
    lwz r3, 0x168(r3)
    lwz r12, 0(r3)
    lwz r12, 0x11c(r12)
    mtctr r12
    bctr
}

void Base::limitRowNum(u32 limitRowNum) {
    muLimitRowNum = limitRowNum;
    if (limitRowNum == 1) {
        doWordWrap(false);
    }
}

void Base::makeUpCursorPos(CursorPos* cursorPos, u32 pos, s32 startLine, s32 endLine) {
    u32 wordWrapCounter = muWordWrapCounter;
    muWordWrapCounter = pos;
    textdrawer::Base::makeUpCursorPos(cursorPos, pos, startLine, endLine);
    muWordWrapCounter = wordWrapCounter;
}

void Base::setFont(const nw4r::ut::Font& font) {
    textdrawer::Base::setFont(font);
}

void Base::clear() {
    init();
    mpString->clear();
}

nw4r::math::VEC2 Base::getGlobalLeftTopPos() const {
    nw4r::math::VEC3 position;
    position.x = mRect.left;
    position.y = mRect.bottom;
    position.z = 0.0f;
    PSMTXMultVec(mMtx, position, position);
    return nw4r::math::VEC2(position.x, -position.y);
}

void Base::doAfterDrawProcess(const wchar_t*, u32, const DrawInfo&) {}

void Base::preDraw(u32 pos) {
    muWordWrapCounter = pos;
    mbHyphen = false;
}

asm void Base::doLineFeed() {
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stfd f31, 0x20(r1)
    psq_st f31, 0x28(r1), 0, 0
    stw r31, 0x1c(r1)
    mr r31, r3
    lwz r4, 0xb0(r3)
    addi r0, r4, 1
    stw r0, 0xb0(r3)
    lwz r12, 0x5c(r3)
    lwz r12, 0x28(r12)
    mtctr r12
    addi r3, r3, 0x10
    bctrl
    fmr f31, f1
    addi r3, r31, 0x10
    bl GetCursorY__Q34nw4r2ut10CharWriterCFv
    fadds f1, f1, f31
    addi r3, r31, 0x10
    bl SetCursorY__Q34nw4r2ut10CharWriterFf
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0x188(r12)
    mtctr r12
    bctrl
    stw r3, 8(r1)
    addi r3, r31, 0x10
    stw r4, 0xc(r1)
    lfs f1, 8(r1)
    bl SetCursorX__Q34nw4r2ut10CharWriterFf
    psq_l f31, 0x28(r1), 0, 0
    lwz r0, 0x34(r1)
    lfd f31, 0x20(r1)
    lwz r31, 0x1c(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

asm bool Base::isOverLine(const DrawInfo& drawInfo) {
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stfd f31, 0x30(r1)
    psq_st f31, 0x38(r1), 0, 0
    stfd f30, 0x20(r1)
    psq_st f30, 0x28(r1), 0, 0
    stw r31, 0x1c(r1)
    mr r31, r4
    stw r30, 0x18(r1)
    mr r30, r3
    lwz r12, 0(r3)
    lwz r12, 0x188(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r30)
    lfs f1, 0x128(r30)
    lfs f0, 0x120(r30)
    lwz r12, 0x188(r12)
    stw r3, 8(r1)
    fsubs f31, f1, f0
    mr r3, r30
    stw r4, 0xc(r1)
    mtctr r12
    bctrl
    lfs f1, 8(r31)
    lfs f0, 0(r31)
    stw r3, 0x10(r1)
    addi r3, r30, 0x10
    fsubs f30, f1, f0
    stw r4, 0x14(r1)
    bl GetCursorX__Q34nw4r2ut10CharWriterCFv
    lfs f2, 0x10(r1)
    lfs f0, 8(r1)
    fmuls f2, f30, f2
    fmuls f0, f31, f0
    fadds f1, f1, f2
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    mfcr r3
    extrwi r3, r3, 1, 2
    psq_l f31, 0x38(r1), 0, 0
    lfd f31, 0x30(r1)
    psq_l f30, 0x28(r1), 0, 0
    lfd f30, 0x20(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r0, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}

asm void Base::drawFixString(u32) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    lfs f0, lbl_81694D28(r0)
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r30, r3
    stw r4, 0xc(r1)
    addi r4, r1, 8
    stfs f0, 0x10(r1)
    stfs f0, 0x14(r1)
    lbz r5, 0x1c8(r3)
    lbz r0, 0x1cc(r3)
    stb r5, 0x1cf(r3)
    stb r0, 8(r1)
    lbz r0, 0x1cd(r3)
    stb r0, 9(r1)
    lbz r0, 0x1ce(r3)
    stb r0, 0xa(r1)
    lbz r0, 0x1cf(r3)
    addi r3, r3, 0x10
    stb r0, 0xb(r1)
    bl SetTextColor__Q34nw4r2ut10CharWriterFQ34nw4r2ut5Color
    lwz r3, 0x164(r30)
    lwz r12, 0(r3)
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl
    clrlwi r31, r3, 16
    lwz r3, 0x164(r30)
    lwz r12, 0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl
    mr r4, r3
    mr r6, r31
    addi r3, r30, 0x10
    li r5, 0
    bl setDrawString__Q39textinput10textdrawer4BaseFPCwUlUl
    addi r3, r30, 0x10
    addi r4, r1, 0xc
    bl draw__Q39textinput10textdrawer4BaseFPQ49textinput10textdrawer4Base9CursorPos
    lwz r12, 0(r30)
    mr r3, r30
    lfs f1, 0x10(r1)
    lwz r12, 0x164(r12)
    lfs f2, 0x14(r1)
    mtctr r12
    bctrl
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

asm void Base::draw() {
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stw r31, 0x4c(r1)
    stw r30, 0x48(r1)
    mr r30, r3
    lwz r12, 0(r3)
    lwz r12, 0x188(r12)
    mtctr r12
    bctrl
    stw r3, 0x18(r1)
    addi r3, r30, 0x10
    lfs f2, 0x188(r30)
    stw r4, 0x1c(r1)
    lfs f1, 0x18(r1)
    bl SetCursor__Q34nw4r2ut10CharWriterFff
    lwz r12, 0(r30)
    mr r3, r30
    lwz r12, 0x188(r12)
    mtctr r12
    bctrl
    lfs f0, lbl_81694D28(r0)
    stw r3, 0x10(r1)
    stfs f0, 0x30(r1)
    stfs f0, 0x34(r1)
    stfs f0, 0x38(r1)
    stfs f0, 0x3c(r1)
    lwz r12, 0(r30)
    stw r3, 0x28(r1)
    mr r3, r30
    lwz r12, 0x184(r12)
    stw r4, 0x14(r1)
    stw r4, 0x2c(r1)
    mtctr r12
    bctrl
    stw r3, 0x20(r1)
    lfs f1, 0x28(r1)
    stw r4, 0x24(r1)
    lfs f5, 0x20(r1)
    lfs f4, 0x24(r1)
    stfs f5, 0x30(r1)
    lfs f0, 0x2c(r1)
    stfs f4, 0x3c(r1)
    lfs f3, 0x128(r30)
    lfs f2, 0x120(r30)
    stw r3, 8(r1)
    fsubs f2, f3, f2
    stw r4, 0xc(r1)
    fmuls f1, f1, f2
    fadds f1, f5, f1
    stfs f1, 0x38(r1)
    lfs f2, 0x124(r30)
    lfs f1, 0x12c(r30)
    fsubs f1, f2, f1
    fmuls f0, f0, f1
    fadds f0, f4, f0
    stfs f0, 0x34(r1)
    lwz r3, 0x164(r30)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl
    lwz r12, 0x5c(r30)
    mr r31, r3
    addi r3, r30, 0x10
    addi r4, r1, 0x30
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    lwz r12, 0(r30)
    mr r3, r30
    mr r4, r31
    lwz r12, 0x174(r12)
    mtctr r12
    bctrl
    lwz r12, 0x5c(r30)
    addi r3, r30, 0x10
    lwz r12, 0x24(r12)
    mtctr r12
    bctrl
    lwz r0, 0x54(r1)
    lwz r31, 0x4c(r1)
    lwz r30, 0x48(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}

asm void Base::drawCursor(f32, f32) {
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stfd f31, 0x40(r1)
    psq_st f31, 0x48(r1), 0, 0
    lis r7, 0x4330
    lfd f4, lbl_81694D80(r0)
    stw r31, 0x3c(r1)
    mr r31, r3
    lfs f3, lbl_81694D70(r0)
    lbz r0, 0x1c8(r3)
    stw r7, 0x10(r1)
    stw r0, 0x14(r1)
    lfd f0, 0x10(r1)
    stfs f1, 0x17c(r3)
    fsubs f1, f0, f4
    lfs f0, lbl_81694D40(r0)
    stfs f2, 0x180(r3)
    lbz r6, lbl_81694D6C(r0)
    fdivs f31, f1, f3
    lbz r5, lbl_81694D6D(r0)
    lbz r4, lbl_81694D6E(r0)
    lbz r0, lbl_81694D6F(r0)
    stb r6, 8(r1)
    stb r5, 9(r1)
    stb r4, 0xa(r1)
    stb r0, 0xb(r1)
    lwz r0, 0x214(r3)
    stw r7, 0x18(r1)
    stw r0, 0x1c(r1)
    lfd f1, 0x18(r1)
    fsubs f1, f1, f4
    fmuls f1, f0, f1
    bl SinFIdx__Q24nw4r4mathFf
    lfs f2, lbl_81694D74(r0)
    addi r3, r31, 0x10
    fmuls f0, f2, f1
    fadds f0, f2, f0
    fmuls f0, f31, f0
    fctiwz f0, f0
    stfd f0, 0x20(r1)
    lwz r0, 0x24(r1)
    stb r0, 0xb(r1)
    lfs f1, 0xa0(r31)
    lfs f0, 0x98(r31)
    fsubs f31, f1, f0
    bl GetFontHeight__Q34nw4r2ut10CharWriterCFv
    lfs f0, lbl_81694D78(r0)
    addi r4, r1, 8
    lfs f6, 0x180(r31)
    fdivs f0, f0, f31
    lfs f2, lbl_81694D58(r0)
    lfs f5, lbl_81694D28(r0)
    fctiwz f0, f0
    fadds f4, f6, f1
    lfs f1, 0x17c(r31)
    stfd f0, 0x28(r1)
    fmr f3, f1
    fsubs f4, f4, f2
    lwz r3, 0x2c(r1)
    fadds f2, f2, f6
    clrlwi r3, r3, 24
    bl drawLine___Q29textinput5debugFfffffUcR8_GXColor
    psq_l f31, 0x48(r1), 0, 0
    lwz r0, 0x54(r1)
    lfd f31, 0x40(r1)
    lwz r31, 0x3c(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}

extern "C" asm void doScroll__Q39textinput9inputform4BaseFPQ39textinput15CommandReceiver6Scroll() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 8(r1)
    mr r30, r3
    lwz r12, 0x18c(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    addi r3, r3, 0x18c
    bctrl
    cmpwi r3, 0
    bne doScroll_L1
    lbz r0, 0(r31)
    cmpwi r0, 0
    beq doScroll_L2
    lfs f0, 4(r31)
    stfs f0, 0x184(r30)
    lfs f0, 8(r31)
    stfs f0, 0x188(r30)
    stfs f0, 0x100(r30)
    b doScroll_L3
doScroll_L2:
    lfs f2, 0x184(r30)
    addi r3, r30, 0x18c
    lfs f0, 4(r31)
    li r4, 0
    lfs f1, 0x188(r30)
    li r5, 0
    fadds f0, f2, f0
    lfs f3, lbl_81694D88(r0)
    stfs f0, 0x184(r30)
    lwz r12, 0x18c(r30)
    lfs f0, 8(r31)
    lwz r12, 8(r12)
    fadds f2, f1, f0
    mtctr r12
    bctrl
doScroll_L3:
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 0xb
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl
doScroll_L1:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

asm void Base::doBeforeDrawProcess(const wchar_t*, u32, const DrawInfo&) {
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    stfd f31, 0x50(r1)
    psq_st f31, 0x58(r1), 0, 0
    stfd f30, 0x40(r1)
    psq_st f30, 0x48(r1), 0, 0
    stfd f29, 0x30(r1)
    psq_st f29, 0x38(r1), 0, 0
    stw r31, 0x2c(r1)
    mr r31, r6
    stw r30, 0x28(r1)
    mr r30, r5
    stw r29, 0x24(r1)
    mr r29, r4
    stw r28, 0x20(r1)
    mr r28, r3
    addi r3, r3, 0x10
    bl GetCursorX__Q34nw4r2ut10CharWriterCFv
    lwz r12, 0(r28)
    mr r3, r28
    mr r4, r29
    mr r5, r30
    lwz r12, 0x170(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq doBeforeDrawProcess_L1
    lwz r12, 0(r28)
    mr r3, r28
    lwz r12, 0x158(r12)
    mtctr r12
    bctrl
doBeforeDrawProcess_L1:
    lwz r12, 0(r28)
    mr r3, r28
    mr r4, r31
    lwz r12, 0x160(r12)
    mtctr r12
    bctrl
    cmpwi r3, 0
    beq doBeforeDrawProcess_L2
    lwz r4, 0xb0(r28)
    addi r3, r28, 0x10
    addi r0, r4, 1
    stw r0, 0xb0(r28)
    lwz r12, 0x5c(r28)
    lwz r12, 0x28(r12)
    mtctr r12
    bctrl
    fmr f31, f1
    addi r3, r28, 0x10
    bl GetCursorY__Q34nw4r2ut10CharWriterCFv
    fadds f1, f1, f31
    addi r3, r28, 0x10
    bl SetCursorY__Q34nw4r2ut10CharWriterFf
    lwz r12, 0(r28)
    mr r3, r28
    lwz r12, 0x188(r12)
    mtctr r12
    bctrl
    stw r3, 0x10(r1)
    addi r3, r28, 0x10
    stw r4, 0x14(r1)
    lfs f1, 0x10(r1)
    bl SetCursorX__Q34nw4r2ut10CharWriterFf
doBeforeDrawProcess_L2:
    lwz r3, 0x164(r28)
    addi r4, r1, 0xc
    addi r5, r1, 8
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl
    lwz r0, 0xc(r1)
    cmplw r30, r0
    blt doBeforeDrawProcess_L3
    lwz r0, 8(r1)
    cmplw r30, r0
    bge doBeforeDrawProcess_L3
    addi r3, r28, 0x10
    bl GetCursorX__Q34nw4r2ut10CharWriterCFv
    lfs f0, 0(r31)
    addi r3, r28, 0x10
    fadds f31, f0, f1
    bl GetCursorY__Q34nw4r2ut10CharWriterCFv
    lfs f0, 4(r31)
    addi r3, r28, 0x10
    fadds f30, f0, f1
    bl GetCursorX__Q34nw4r2ut10CharWriterCFv
    lfs f0, 8(r31)
    addi r3, r28, 0x10
    fadds f29, f0, f1
    bl GetCursorY__Q34nw4r2ut10CharWriterCFv
    lfs f0, 0xc(r31)
    fmr f2, f30
    fmr f3, f29
    lfs f5, lbl_81694D28(r0)
    fadds f4, f0, f1
    lfs f6, lbl_81694D38(r0)
    fmr f1, f31
    addi r3, r28, 0x1c0
    bl drawBox___Q29textinput5debugFffffffR8_GXColor
doBeforeDrawProcess_L3:
    psq_l f31, 0x58(r1), 0, 0
    lfd f31, 0x50(r1)
    psq_l f30, 0x48(r1), 0, 0
    lfd f30, 0x40(r1)
    psq_l f29, 0x38(r1), 0, 0
    lfd f29, 0x30(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    lwz r0, 0x64(r1)
    lwz r28, 0x20(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}

void Base::finishDraw(u32) {}

void Base::onSE(sound::SE) {}

void Base::setString(const wchar_t* string) {
    mpString->set(string);
}

void Base::onClose() {
    onCommand(static_cast<INPUT_COMMAND>(6), NULL);
    candidatebox::CandidateBoxCaller::makeEmptyCandidate();
    static_cast<textdrawer::Base&>(*this).dirtyDrawCache();
    static_cast<textdrawer::Base&>(*this).dirtyCursorCache();
}

void AnmPane::changeAnimation(u32 id) {
    meState = static_cast<Animation>(id);
    nw4rmanager::AnmPane::changeAnimation(id);
}

void AnmPane::init() {
    meState = ANM_Normal;
}

KeyType AnmPane::getKeyType() const {
    return meKeyType;
}

Animation AnmPane::getState() {
    return meState;
}

NormalButtonAnmPane::~NormalButtonAnmPane() {}

EventHandler::~EventHandler() {}

wchar_t Base::getCandidate() const {
    return mpString->getCandidate();
}

void* Base::getAtokString() {
    return mpUnfixString;
}

asm u32 Base::getCursorPos() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    addi r4, r1, 0x10
    addi r5, r1, 8
    stw r31, 0x1c(r1)
    mr r31, r3
    lwz r3, 0x164(r3)
    lwz r12, 0(r3)
    lwz r12, 0x80(r12)
    mtctr r12
    bctrl
    lwz r3, 0x168(r31)
    addi r4, r1, 0xc
    addi r5, r1, 8
    lwz r12, 0(r3)
    lwz r12, 0x80(r12)
    mtctr r12
    bctrl
    lwz r3, 0x10(r1)
    lwz r0, 0xc(r1)
    lwz r31, 0x1c(r1)
    add r3, r3, r0
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

wchar_t* Base::getWCString() const {
    return mpString->getWCString();
}

bool Base::isInScroll() {
    return mScrollAnm.isActive();
}

Base::PredictMode Base::getPredictMode() {
    Base::PredictMode mode;
    onCommand(static_cast<INPUT_COMMAND>(31), &mode);
    return mode;
}

void Base::setPredictMode(PredictMode predictMode) {
    switch (meDestination) {
        case DST_EU:
            if (predictMode == PM_En || predictMode == PM_De || predictMode == PM_Fr || predictMode == PM_Sp || predictMode == PM_It || predictMode == PM_Nl) {
                break;
            }
            return;
        case DST_JP:
            if (predictMode == PM_Atok) {
                break;
            }
            return;
        case DST_US:
            if (predictMode == PM_USEn || predictMode == PM_USFr || predictMode == PM_USSp) {
                break;
            }
            return;
        case DST_CN:
            if (predictMode == PM_11) {
                break;
            }
            return;
        case DST_KR:
            if (predictMode != PM_12) {
                return;
            }
            break;
    }
    PredictMode mode;
    onCommand(static_cast<INPUT_COMMAND>(31), &mode);
    mode = predictMode;
    onCommand(static_cast<INPUT_COMMAND>(29), &mode);
}

nw4r::math::VEC2 Base::getScale() const {
    return nw4r::math::VEC2(1.0f, 1.0f);
}

asm bool LayoutByNW4R::isAbleToUp() {
    nofralloc
    lbz r3, 0x2cc(r3)
    blr
}

asm bool LayoutByNW4R::isAbleToDown() {
    nofralloc
    lbz r3, 0x2cd(r3)
    blr
}

bool LayoutByNW4R::updateInput(textinput::input::HKBManager& hkbManager) {
    return nw4rmanager::Layout::updateInput(hkbManager);
}

void LayoutByNW4R::visibleSeparator(bool flag) {
    unk_0x2C0[0x0E] = flag;
}

void LayoutByNW4R::setRootPaneScaleFor16x9() {
    nw4rmanager::Layout::setRootPaneScaleFor16x9();
    textdrawer::Base::setAspectRatio(false);
}

void LayoutByNW4R::setRootPaneScaleFor4x3() {
    nw4rmanager::Layout::setRootPaneScaleFor4x3();
    textdrawer::Base::setAspectRatio(true);
}

}
}

void textinput::Base::create(MEMAllocator*) {}
