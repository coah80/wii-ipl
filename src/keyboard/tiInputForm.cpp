#include "keyboard/tiUtil.h"
#include "keyboard/tiInputForm.h"
#include "keyboard/tiManager.h"

#include <revolution/mtx.h>

extern "C" void __dl__FPv(void*);

namespace textinput {
namespace tistring {
extern "C" asm void __dt__Q39textinput8tistring10StringBaseFv();
}
namespace util {
extern "C" const f32 lbl_81694D28;
}
namespace inputform {

extern "C" const f32 lbl_81694D28;
extern "C" const f32 lbl_81694D2C;
extern "C" const f64 lbl_81694D30;
extern "C" const f32 lbl_81694D38;
extern "C" const f32 lbl_81694D3C;
extern "C" const f32 lbl_81694D40;
extern "C" const f32 lbl_81694D44;
extern "C" const f32 lbl_81694D48;
extern "C" const f32 lbl_81694D4C;
extern "C" const f32 lbl_81694D50;
extern "C" const f32 lbl_81694D54;
extern "C" const f32 lbl_81694D58;
extern "C" const f32 lbl_81694D5C;
extern "C" const f32 lbl_81694D60;
extern "C" const f32 lbl_81694D64;
extern "C" const f32 lbl_81694D68;
extern "C" const u8 lbl_81694D6C;
extern "C" const u8 lbl_81694D6D;
extern "C" const u8 lbl_81694D6E;
extern "C" const u8 lbl_81694D6F;
extern "C" const f32 lbl_81694D70;
extern "C" const f32 lbl_81694D74;
extern "C" const f32 lbl_81694D78;
extern "C" const f64 lbl_81694D80;
extern "C" const f32 lbl_81694D88;
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
extern "C" char lbl_816973A4[];
extern "C" char lbl_816973AC[];
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
extern "C" asm void __vt__Q39textinput11nw4rmanager7AnmPane();
extern "C" asm void __vt__Q39textinput9inputform19NormalButtonAnmPane();
extern "C" asm void __vt__Q39textinput9inputform12EventHandler();
extern "C" asm void GetModifierState__Q39textinput5input10HKBManagerCFv();
extern "C" asm void GetPaneRect__Q34nw4r3lyt4PaneCFRCQ34nw4r3lyt8DrawInfo();
extern "C" asm void GetTextColor__Q34nw4r2ut10CharWriterCFv();
extern "C" asm void GetTextColor__Q34nw4r3lyt7TextBoxCFUl();
extern "C" asm void HankakuToZenkaku__Q29textinput4utilFw();
extern "C" asm void KPRClearQueue();
extern "C" asm void KPRGetChar();
extern "C" asm void KPRPutChar();
extern "C" asm void List_Init__Q24nw4r2utFPQ34nw4r2ut4ListUs();
extern "C" asm void MoveCursorX__Q34nw4r2ut10CharWriterFf();
extern "C" asm void Print__Q34nw4r2ut10CharWriterFUs();
extern "C" asm void ScrollToSelectedText__Q39textinput12candidatebox10UITextAreaFv();
extern "C" asm void SetResource__Q34nw4r2ut7ResFontFPv();
extern "C" asm void SetupGX__Q34nw4r2ut10CharWriterFv();
extern "C" asm void addAnimation__Q39textinput11nw4rmanager7AnmPaneFP12MEMAllocatorUlPQ29textinput17AnimTransformPanebb();
extern "C" asm void calcCursorPos__Q39textinput9inputform4BaseFff();
extern "C" asm void createWithEventHandler__Q39textinput11nw4rmanager6LayoutFP12MEMAllocatorPQ39textinput11nw4rmanager14TiEventHandler();
extern "C" asm void forceAddAnimation__Q39textinput11nw4rmanager7AnmPaneFP12MEMAllocatorUlPQ29textinput17AnimTransformPanePCcbb();
extern "C" asm void getCurrentInput__Q39textinput8tistring6WithZiFv();
extern "C" asm void inputCharZi___Q39textinput9inputform4BaseFwUl();
extern "C" asm void inputString__Q39textinput8tistring9DecolatedFPCwQ49textinput8tistring9Decolated13TranslateMode();
extern "C" asm void isPredictTurning__Q29textinput7ManagerCFv();
extern "C" asm void onCommand__Q39textinput9inputform4BaseFQ39textinput15CommandReceiver13INPUT_COMMANDPv();
extern "C" asm void onHKBCtrlCode__Q39textinput9inputform4BaseFQ29textinput7HVKCodeUl();
extern "C" asm void onPressDownHWKB__Q39textinput9inputform4BaseFv();
extern "C" asm void onPressLeftHWKB__Q39textinput9inputform4BaseFv();
extern "C" asm void onPressRightHWKB__Q39textinput9inputform4BaseFv();
extern "C" asm void onSpaceKeyHWKB__Q39textinput9inputform4BaseFUl();
extern "C" asm void partialConfirmForKR__Q39textinput8tistring6WithZiFv();
extern "C" asm void replaceChar__Q29textinput4utilFPcUlPCcic();
extern "C" asm void resetHoldingButton__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv();
extern "C" asm void setLanguage__Q39textinput9inputform4BaseFQ29textinput8Language();
extern "C" asm void setTranslateMode__Q39textinput8tistring9DecolatedFQ49textinput8tistring9Decolated13TranslateMode();
extern "C" asm void startPredictTurnOn__Q29textinput7ManagerFb();
extern "C" asm void strcmp();
extern "C" asm void strcmp__Q29textinput4utilFPCcPCc();
extern "C" asm void toWLower__Q29textinput4utilFw();
extern "C" asm void toggleAtokMode___Q39textinput9inputform4BaseFUc();
extern "C" asm void updateInput__Q39textinput11nw4rmanager6LayoutFiffUlUlUlPv();
extern "C" void _savegpr_18();
extern "C" void _restgpr_18();
extern "C" void _savegpr_19();
extern "C" void _restgpr_19();
extern "C" void _savegpr_21();
extern "C" void _restgpr_21();
extern "C" void _savegpr_23();
extern "C" void _restgpr_23();
extern "C" void _savegpr_25();
extern "C" void _restgpr_25();
extern "C" void _savegpr_26();
extern "C" void _restgpr_26();
extern "C" void __register_global_object();
extern "C" asm void __dt__Q29textinput12LayoutGatherFv();
extern "C" asm void __ct__Q29textinput12LayoutGatherFv();
#pragma push
#pragma section const_type ".data"
extern "C" const u8 jumptable_8165CA58[];
extern "C" const u8 jumptable_8165CA8C[];
extern "C" const u8 jumptable_8165CB4C[];
extern "C" const u8 jumptable_8165CC5C[];
extern "C" const char lbl_8165CC14[];
extern "C" const char lbl_8165CC28[];
extern "C" const char lbl_8165CC4C[];
#pragma pop
extern "C" u8 csUnInputedWCharColor__Q29textinput9inputform[4];
extern "C" u8 csCharColor__Q29textinput9inputform[4];
extern "C" u8 csZiStringColorLeft__Q29textinput9inputform[4];
extern "C" u8 csZiStringNonSelectColorRight__Q29textinput9inputform[4];
extern "C" u8 csZiStringColorRight__Q29textinput9inputform[4];
extern "C" u8 csUnderlateColor__Q29textinput9inputform[4];
extern "C" u8 csUnInputedWCharColorSpace__Q29textinput9inputform[4];
extern "C" u8 sInstance__Q39textinput5input10HKBManager;
extern "C" u8 typeInfo__Q34nw4r3lyt7TextBox;
/* @GUARD@/@LOCAL@ local-static names for LayoutGather::getInstance()s sGather
   are not spellable in MWCC inline asm; these are stand-ins. */
extern "C" u8 sGather_guard__Q39textinput12LayoutGather;
extern "C" u8 sGather_local__Q39textinput12LayoutGather;
extern "C" u8 mbHyphen__Q29textinput9inputform;
extern "C" u8 sbCompatibleFilterEnabled__Q39textinput9inputform13DeadKeyStream;
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

extern "C" f32 lbl_81698D1C;

#pragma push
#pragma section data_type ".sdata"
#pragma explicit_zero_data on
extern "C" u32 lbl_81697398 = 0x80ff80ff;
extern "C" u32 lbl_8169739C = 0xffd20cff;
extern "C" const char* lbl_816973A0 = lbl_8165C820;
extern "C" char lbl_816973A4[] = "N_KOR";
extern "C" char lbl_816973AC[] = "N_CHN";
bool DeadKeyStream::sbCompatibleFilterEnabled = true;
bool mbHyphen = true;
extern "C" char lbl_816973B4[4] = {0, 0, 0, 0};
extern "C" char lbl_816973B8[8] = "N_2line";
#pragma explicit_zero_data off
#pragma pop

extern "C" {
u8 lbl_810C6590[0xc];
}

nw4r::ut::Color csUnInputedWCharColor(0xc8, 0x32, 0x32, 0xff);
nw4r::ut::Color csCharColor(0x14, 0x14, 0x14, 0xff);
nw4r::ut::Color csZiStringColorLeft(0xff, 0x32, 0x32, 0xff);
nw4r::ut::Color csZiStringNonSelectColorRight(0xc0, 0xc0, 0xc0, 0xff);
nw4r::ut::Color csZiStringColorRight(0x32, 0x64, 0x32, 0xff);
nw4r::ut::Color csUnderlateColor(0x64, 0xc8, 0xc8, 0xff);
nw4r::ut::Color csUnInputedWCharColorSpace(0xff, 0x14, 0x14, 0xff);

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
    csAninationFile__Q29textinput9inputform + 7,
    0,
    0,
    0,
    0,
    0,
    lbl_8165C830,
    (const void*)0x00000008,
    lbl_816973A0,
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

#pragma push
#pragma explicit_zero_data on
extern "C" const u8 jumptable_8165CA58[0x34] = {};
extern "C" const u8 jumptable_8165CA8C[0x5c] = {};
extern "C" const u8 lbl_8165CAC8[0x64] = {};
extern "C" const u8 jumptable_8165CB4C[0x94] = {};
#pragma explicit_zero_data off
#pragma pop
void textinput::Base::create(MEMAllocator*) {}

extern "C" const char lbl_8165CBE0[] = "T_2l_TextBox\0\0\0\0" "RevoIpl_RodinNTLGProM_32_I4.brfnt\0\0";
extern "C" const char lbl_8165CC14[] = "P_txtScrll_UP";
extern "C" const char ATTRIBUTE_ALIGN(8) lbl_8165CC28[0x24] = "P_txtScrll_DOWN\0N_separateBarAll";
extern "C" const char lbl_8165CC4C[] = "T_title_text";
#pragma push
#pragma explicit_zero_data on
extern "C" const u8 jumptable_8165CC5C[0x1c] = {};
#pragma explicit_zero_data off
#pragma pop

enum Animation {
    ANM_Normal
};

enum KeyType {
    KT_NormalButton
};

class EventHandler : public nw4rmanager::TiEventHandler {
public:
    virtual ~EventHandler();
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

asm void util::Animation::startAnm(f32, f32, f32, util::AnimObserver*, void*) {
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

asm Base::~Base() {
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
extern "C" asm u32 getDrawCacheStartPos__Q39textinput10textdrawer4BaseCFv() {
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
asm tistring::WithAtok::~WithAtok() {
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
asm LayoutByNW4R::~LayoutByNW4R() {
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
asm EditBuffer::~EditBuffer() {
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
    position.z = *(&lbl_81694D28);
    PSMTXMultVec(mMtx, position, position);
    return nw4r::math::VEC2(position.x, -position.y);
}

void Base::doAfterDrawProcess(const wchar_t*, u32, const DrawInfo&) {}

void Base::preDraw(u32 pos) {
    muWordWrapCounter = pos;
    mbHyphen = false;
}

bool Base::doWordWrap(const wchar_t* string, u32 pos, f32 width) {
    struct WordWrapDrawInfo {
        f32 left;
        f32 top;
        f32 right;
        f32 bottom;
        u16 character;
    };

    if (!mbDoWordWrap) {
        return false;
    }

    bool characterWrap;
    const wchar_t* stringPtr = string;
    u32 current;
    u32 wordWrapCounter = muWordWrapCounter;
    if (pos < wordWrapCounter) {
        return false;
    }

    s32 hyphenType = 0;
    if (wordWrapCounter != 0 && getDrawCacheStartPos() != wordWrapCounter) {
        wchar_t previous = stringPtr[wordWrapCounter - 1];
        if (previous == L'-') {
            hyphenType = 1;
        } else if (previous != L' ') {
            hyphenType = 2;
        }
    }

    f32 stringWidth = *(&lbl_81694D28);
    f32 zero = stringWidth;
    u32 index;
    u32 hyphenPos;
    bool wrap;
    hyphenPos = 0;
    current = muWordWrapCounter;
    wrap = false;
    index = current;
    stringPtr = string + current;
    do {
        if (*stringPtr == L' ' || *stringPtr == L'\n') {
            break;
        }
        WordWrapDrawInfo drawInfo;
        drawInfo.left = lbl_81694D28;
        drawInfo.top = lbl_81694D28;
        drawInfo.right = lbl_81694D28;
        drawInfo.bottom = lbl_81694D28;
        drawInfo.character = *stringPtr;
        calcRect(reinterpret_cast<DrawInfo&>(drawInfo));
        characterWrap = false;
        stringWidth += drawInfo.right - drawInfo.left;

        if (width != getScale().x) {
            if (width + stringWidth * getScale().x >= getWordWrapRectWidth() * getScale().x) {
                characterWrap = true;
            }
        }
        if (characterWrap) {
            wrap = true;
        }

        if (index != current && *stringPtr == L'-') {
            hyphenPos = index;
            mbHyphen = true;
        }

        ++stringPtr;
        ++index;
    } while (*stringPtr != L'\0');

    if (index == current) {
        mbHyphen = false;
    }

    if (stringWidth * getScale().x >= getWordWrapRectWidth() * getScale().x) {
        wrap = false;
        if (mbHyphen) {
            wrap = true;
        }
        if (hyphenType == 1) {
            wrap = true;
        }
    }

    if (wrap) {
        if (!findURL(0, 0, string, current, index)) {
            if (hyphenPos == 0) {
                mbHyphen = false;
                ++index;
                muWordWrapCounter = index;
                return true;
            }

            index = hyphenPos;
        }
    } else {
        mbHyphen = false;
    }

    ++index;
    muWordWrapCounter = index;
    return false;
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
    return nw4r::math::VEC2(*(&lbl_81694D38), *(&lbl_81694D38));
}

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
extern "C" const f32 lbl_81694D8C = 0.0f;

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

extern "C" asm void isEnableCursorCache__Q39textinput10textdrawer4BaseCFvgetStartPos__Q39textinput10textdrawer4BaseCFv() {
    nofralloc
    lbz r3, 0x104(r3)
    blr 
}

extern "C" asm void toggleAtokMode___Q39textinput9inputform4BaseFUc() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r30, r4
    stw r29, 0x14(r1)
    mr r29, r3
    lwz r3, 0x1d4(r3)
    lwz r12, 0(r3)
    lwz r12, 0x94(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0xac(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_8a14
    lwz r3, 0x1d4(r29)
    lwz r12, 0(r3)
    lwz r12, 0x94(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_8a14
    li r0, 0
    b L_8a34
L_8a14:
    lwz r3, 0x1d4(r29)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lbz r0, 0x3c(r3)
    cntlzw r0, r0
    srwi r0, r0, 5
L_8a34:
    cmpwi r0, 0
    beq L_8be0
    lwz r3, 0x1d4(r29)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x10c(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_8ab8
    lwz r3, 0x1d4(r29)
L_8a6c:
    bl isPredictTurning__Q29textinput7ManagerCFv
    cmpwi r3, 0
    bne L_8be0
    lwz r3, 0x1d4(r29)
    lbz r0, 0x178(r29)
    lwz r12, 0(r3)
    cntlzw r0, r0
    lwz r12, 0x74(r12)
    srwi r31, r0, 5
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x58(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_8ae4
    li r31, 1
    b L_8ae4
L_8ab8:
    lwz r3, 0x1d4(r29)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x58(r12)
    mtctr r12
    bctrl 
    cntlzw r0, r3
    srwi r31, r0, 5
L_8ae4:
    cmpwi r31, 0
    beq L_8afc
    cmplwi r30, 2
    bne L_8afc
    li r31, 0
    b L_8b10
L_8afc:
    cmpwi r31, 0
    bne L_8b10
    cmplwi r30, 1
    bne L_8b10
    li r31, 1
L_8b10:
    cmpwi r31, 0
    beq L_8b70
    lwz r3, 0x1d4(r29)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x58(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_8b98
    lwz r3, 0x1d4(r29)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    li r4, 1
    lwz r12, 0x5c(r12)
    mtctr r12
    bctrl 
    b L_8b98
L_8b70:
    lwz r3, 0x1d4(r29)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    li r4, 0
    lwz r12, 0x5c(r12)
    mtctr r12
    bctrl 
L_8b98:
    lwz r3, 0x1d4(r29)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x10c(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_8be0
    lbz r0, 0x178(r29)
    cmplw r0, r31
    beq L_8be0
    cntlzw r0, r0
    lwz r3, 0x1d4(r29)
    srwi r4, r0, 5
L_8bdc:
    bl startPredictTurnOn__Q29textinput7ManagerFb
L_8be0:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr 
}

extern "C" asm void inputCharZi___Q39textinput9inputform4BaseFwUl() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    mr r29, r5
    stw r28, 0x10(r1)
    mr r28, r4
    lwz r0, 0x1f0(r3)
    cmpwi r0, 9
    beq L_5ea8
    clrlwi. r0, r5, 0x1e
    beq L_5ea8
    mr r3, r28
L_5ea0:
    bl toWLower__Q29textinput4utilFw
    mr r28, r3
L_5ea8:
    clrlwi r0, r28, 0x10
    li r30, 0
    cmplwi r0, 0x20
    bne L_5ebc
    li r30, 1
L_5ebc:
    lwz r0, 0x1f0(r31)
    cmpwi r0, 8
    bne L_5f10
    clrlwi r3, r28, 0x10
L_5ecc:
    bl isAlphabet__Q29textinput4utilFw
    cmpwi r3, 0
    bne L_5f5c
    clrlwi r0, r28, 0x10
    cmplwi r0, 0x31
    blt L_5f08
    cmplwi r0, 0x35
    bgt L_5f08
    lwz r3, 0x16c(r31)
    lwz r12, 0(r3)
    lwz r12, 0xe4(r12)
    mtctr r12
    bctrl 
    clrlwi. r0, r3, 0x10
    bne L_5f5c
L_5f08:
    li r30, 1
    b L_5f5c
L_5f10:
    cmpwi r0, 9
    bne L_5f5c
    clrlwi r3, r28, 0x10
L_5f1c:
    bl isAlphabet__Q29textinput4utilFw
    cmpwi r3, 0
    beq L_5f58
    mr r3, r31
    li r4, 1
L_5f30:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r0, 0x16c(r31)
    cmplw r3, r0
    bne L_5f5c
    rlwinm. r0, r29, 0, 0x1e, 0x1e
    beq L_5f5c
    clrlwi r3, r28, 0x10
L_5f4c:
    bl reverseLetterCaseW__Q29textinput4utilFw
    mr r28, r3
    b L_5f5c
L_5f58:
    li r30, 1
L_5f5c:
    cmpwi r30, 0
    beq L_6088
    lbz r0, 0x178(r31)
    cmpwi r0, 0
    bne L_5f78
    li r0, 0
    b L_5fac
L_5f78:
    lwz r0, 0x174(r31)
    cmpwi r0, 1
    beq L_5fa8
    lwz r3, 0x16c(r31)
    lwz r12, 0(r3)
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    ble L_5fa8
    li r0, 1
    b L_5fac
L_5fa8:
    li r0, 0
L_5fac:
    cmpwi r0, 0
    beq L_5fbc
    mr r3, r31
L_5fb8:
    bl confirmInput___Q39textinput9inputform4BaseFv
L_5fbc:
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r31)
    clrlwi r4, r28, 0x10
    lwz r12, 0(r3)
    lwz r12, 0x50(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r0, 0x1f0(r31)
    cmpwi r0, 8
    bne L_606c
    lbz r0, 0x178(r31)
    cmpwi r0, 0
    bne L_601c
    li r0, 0
    b L_6050
L_601c:
    lwz r0, 0x174(r31)
    cmpwi r0, 1
    beq L_604c
    lwz r3, 0x16c(r31)
    lwz r12, 0(r3)
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    ble L_604c
    li r0, 1
    b L_6050
L_604c:
    li r0, 0
L_6050:
    cmpwi r0, 0
    beq L_606c
    lwz r3, 0x16c(r31)
    li r4, 0
L_6060:
    bl setCurrentWord__Q39textinput8tistring6WithZiFPCw
    lwz r3, 0x16c(r31)
L_6068:
    bl update__Q39textinput8tistring6WithZiFv
L_606c:
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 9
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    b L_60d0
L_6088:
    clrlwi r0, r29, 0x1e
    cmpwi r0, 2
    beq L_60ac
    bge L_60b4
    cmpwi r0, 1
    bge L_60a4
    b L_60b4
L_60a4:
    li r6, 0
    b L_60b8
L_60ac:
    li r6, 2
    b L_60b8
L_60b4:
    li r6, 1
L_60b8:
    mr r3, r31
    clrlwi r4, r28, 0x10
    li r5, 0
    li r7, 0
    li r8, 0
L_60cc:
    bl confirmInputting___Q39textinput9inputform4BaseFwbUsbPv
L_60d0:
    li r0, 1
    stw r0, 0x1b0(r31)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr 
}

extern "C" asm void onPressUp__Q39textinput9inputform4BaseFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    stw r30, 8(r1)
    mr r30, r3
L_6e54:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r0, 0x16c(r30)
    mr r31, r3
    cmplw r0, r3
    beq L_71f8
    lwz r0, 0x168(r30)
    cmplw r0, r3
    bne L_7038
    mr r3, r0
    lwz r12, 0(r3)
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_6ea4
    lwz r3, 0x168(r30)
    lwz r12, 0(r3)
    lwz r12, 0xc4(r12)
    mtctr r12
    bctrl 
L_6ea4:
    lwz r3, 0x168(r30)
    lwz r12, 0(r3)
    lwz r12, 0xdc(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_6fac
    lwz r3, 0x1d4(r30)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x104(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_71f8
    mr r3, r30
    li r4, 0
L_6ef4:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r0, 0x168(r30)
    cmplw r3, r0
    bne L_6f90
    mr r3, r0
    lwz r12, 0(r3)
    lwz r12, 0x138(r12)
    mtctr r12
    bctrl 
    addi r0, r3, -1
    lwz r3, 0x168(r30)
    extsh r31, r0
    lwz r12, 0(r3)
    lwz r12, 0xe4(r12)
    mtctr r12
    bctrl 
    cmpw r31, r3
    blt L_6f44
    li r31, 0
    b L_6f68
L_6f44:
    cmpwi r31, 0
    bge L_6f68
    lwz r3, 0x168(r30)
    lwz r12, 0(r3)
    lwz r12, 0xe4(r12)
    mtctr r12
    bctrl 
    addi r0, r3, -1
    extsh r31, r0
L_6f68:
    mr r3, r30
    mr r4, r31
L_6f70:
    bl moveCandidateToIdx__Q39textinput9inputform4BaseFl
    lwz r3, 0x1d4(r30)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    addi r3, r3, 0xe4
L_6f8c:
    bl ScrollToSelectedText__Q39textinput12candidatebox10UITextAreaFv
L_6f90:
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 6
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    b L_71f8
L_6fac:
    lwz r3, 0x168(r30)
    lwz r12, 0(r3)
    lwz r12, 0x124(r12)
    mtctr r12
    bctrl 
    clrlwi. r0, r3, 0x10
    beq L_71f8
    lwz r3, 0x168(r30)
    lwz r12, 0(r3)
    lwz r12, 0x118(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r30)
    mr r3, r30
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    mr r3, r30
    li r4, 0
L_6ff8:
    bl moveCandidateToIdx__Q39textinput9inputform4BaseFl
    lwz r3, 0x1d4(r30)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    addi r3, r3, 0xe4
L_7014:
    bl ScrollToSelectedText__Q39textinput12candidatebox10UITextAreaFv
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 0x2f
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
    b L_71f8
L_7038:
    lwz r0, 0x164(r30)
    cmplw r3, r0
    bne L_71f8
    lwz r0, 0x1f0(r30)
    cmpwi r0, 9
    bne L_7124
    mr r3, r30
    li r4, 0
L_7058:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r12, 0(r3)
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_7124
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
    bne L_7124
    lbz r0, 0x178(r30)
    cmpwi r0, 0
    bne L_70d4
    li r0, 0
    b L_7108
L_70d4:
    lwz r0, 0x174(r30)
    cmpwi r0, 1
    beq L_7104
    lwz r3, 0x16c(r30)
    lwz r12, 0(r3)
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    ble L_7104
    li r0, 1
    b L_7108
L_7104:
    li r0, 0
L_7108:
    cmpwi r0, 0
    beq L_7124
    lwz r3, 0x16c(r30)
    li r4, 0
L_7118:
    bl setCurrentWord__Q39textinput8tistring6WithZiFPCw
    lwz r3, 0x16c(r30)
L_7120:
    bl update__Q39textinput8tistring6WithZiFv
L_7124:
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0x48(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_71f8
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_7160
    b L_71f8
L_7160:
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
    clrlwi r0, r3, 0x10
    cmplwi r0, 0x20
    beq L_71f8
    lwz r12, 0(r30)
    mr r3, r30
    lwz r12, 0x18c(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 0x2f
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
L_71f8:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr 
}

extern "C" asm void onPressDown__Q39textinput9inputform4BaseFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    stw r30, 8(r1)
    mr r30, r3
L_7234:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r0, 0x16c(r30)
    mr r31, r3
    cmplw r0, r3
    beq L_75d8
    lwz r0, 0x168(r30)
    cmplw r0, r3
    bne L_7418
    mr r3, r0
    lwz r12, 0(r3)
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_7284
    lwz r3, 0x168(r30)
    lwz r12, 0(r3)
    lwz r12, 0xc4(r12)
    mtctr r12
    bctrl 
L_7284:
    lwz r3, 0x168(r30)
    lwz r12, 0(r3)
    lwz r12, 0xdc(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_738c
    lwz r3, 0x1d4(r30)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x104(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_75d8
    mr r3, r30
    li r4, 0
L_72d4:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r0, 0x168(r30)
    cmplw r3, r0
    bne L_7370
    mr r3, r0
    lwz r12, 0(r3)
    lwz r12, 0x138(r12)
    mtctr r12
    bctrl 
    addi r0, r3, 1
    lwz r3, 0x168(r30)
    extsh r31, r0
    lwz r12, 0(r3)
    lwz r12, 0xe4(r12)
    mtctr r12
    bctrl 
    cmpw r31, r3
    blt L_7324
    li r31, 0
    b L_7348
L_7324:
    cmpwi r31, 0
    bge L_7348
    lwz r3, 0x168(r30)
    lwz r12, 0(r3)
    lwz r12, 0xe4(r12)
    mtctr r12
    bctrl 
    addi r0, r3, -1
    extsh r31, r0
L_7348:
    mr r3, r30
    mr r4, r31
L_7350:
    bl moveCandidateToIdx__Q39textinput9inputform4BaseFl
    lwz r3, 0x1d4(r30)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    addi r3, r3, 0xe4
L_736c:
    bl ScrollToSelectedText__Q39textinput12candidatebox10UITextAreaFv
L_7370:
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 6
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    b L_75d8
L_738c:
    lwz r3, 0x168(r30)
    lwz r12, 0(r3)
    lwz r12, 0x124(r12)
    mtctr r12
    bctrl 
    clrlwi. r0, r3, 0x10
    beq L_75d8
    lwz r3, 0x168(r30)
    lwz r12, 0(r3)
    lwz r12, 0x118(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r30)
    mr r3, r30
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    mr r3, r30
    li r4, 0
L_73d8:
    bl moveCandidateToIdx__Q39textinput9inputform4BaseFl
    lwz r3, 0x1d4(r30)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    addi r3, r3, 0xe4
L_73f4:
    bl ScrollToSelectedText__Q39textinput12candidatebox10UITextAreaFv
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 0x2f
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
    b L_75d8
L_7418:
    lwz r0, 0x164(r30)
    cmplw r3, r0
    bne L_75d8
    lwz r0, 0x1f0(r30)
    cmpwi r0, 9
    bne L_7504
    mr r3, r30
    li r4, 0
L_7438:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r12, 0(r3)
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_7504
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
    bne L_7504
    lbz r0, 0x178(r30)
    cmpwi r0, 0
    bne L_74b4
    li r0, 0
    b L_74e8
L_74b4:
    lwz r0, 0x174(r30)
    cmpwi r0, 1
    beq L_74e4
    lwz r3, 0x16c(r30)
    lwz r12, 0(r3)
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    ble L_74e4
    li r0, 1
    b L_74e8
L_74e4:
    li r0, 0
L_74e8:
    cmpwi r0, 0
    beq L_7504
    lwz r3, 0x16c(r30)
    li r4, 0
L_74f8:
    bl setCurrentWord__Q39textinput8tistring6WithZiFPCw
    lwz r3, 0x16c(r30)
L_7500:
    bl update__Q39textinput8tistring6WithZiFv
L_7504:
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0x48(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_75d8
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_7540
    b L_75d8
L_7540:
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
    clrlwi r0, r3, 0x10
    cmplwi r0, 0x20
    beq L_75d8
    lwz r12, 0(r30)
    mr r3, r30
    lwz r12, 0x190(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 0x2f
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
L_75d8:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr 
}

extern "C" asm void init__Q39textinput9inputform12LayoutByNW4RFv() {
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    mr r31, r3
    stw r30, 0x28(r1)
    stw r29, 0x24(r1)
L_a220:
    bl init__Q39textinput9inputform4BaseFv
    lwz r12, 0x218(r31)
    lis r4, lbl_8165CC14@l
    addi r3, r31, 0x218
    lwz r12, 0x60(r12)
    addi r4, r4, lbl_8165CC14@ha
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    li r4, 7
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl 
    lwz r12, 0x218(r31)
    lis r4, lbl_8165CC28@l
    addi r3, r31, 0x218
    lwz r12, 0x60(r12)
    addi r4, r4, lbl_8165CC28@ha
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    li r4, 7
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl 
    li r0, 0
    la r5, csCharColor__Q29textinput9inputform(r0)
    stb r0, 0x2cc(r31)
    mr r3, r31
    li r4, 0
    stb r0, 0x2cd(r31)
    stw r0, 0x2ec(r31)
    stw r0, 0x2f0(r31)
    stw r0, 0x2f4(r31)
    stw r0, 0x2f8(r31)
    stw r0, 0x304(r31)
    lbz r0, csCharColor__Q29textinput9inputform(r0)
    stb r0, 0x1cc(r31)
    lbz r0, 1(r5)
    stb r0, 0x1cd(r31)
    lbz r0, 2(r5)
    stb r0, 0x1ce(r31)
    lbz r0, 3(r5)
    stb r0, 0x1cf(r31)
    lwz r12, 0(r31)
    lwz r12, 0x23c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x21c(r31)
    li r5, 1
    lwz r4, 0x2c0(r31)
    lwz r3, 0x10(r3)
    lwz r12, 0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    mr r30, r3
    la r4, lbl_816973B4(r0)
    li r5, 0
    lwz r12, 0x6c(r12)
    mtctr r12
    bctrl 
    lfs f0, 0xf0(r30)
    mr r4, r30
    addi r3, r1, 8
    addi r5, r31, 0x230
    stfs f0, 0xb8(r31)
    lfs f0, 0xec(r30)
    stfs f0, 0xb4(r31)
    lfs f0, 0xe4(r30)
    stfs f0, 0xbc(r31)
    lfs f0, 0xe8(r30)
    stfs f0, 0xc0(r31)
L_a348:
    bl GetPaneRect__Q34nw4r3lyt4PaneCFRCQ34nw4r3lyt8DrawInfo
    lfs f0, 8(r1)
    addi r3, r31, 0x218
    addi r4, r31, 0x130
    addi r5, r31, 0x230
    stfs f0, 0x120(r31)
    addi r6, r30, 0x84
    lfs f0, 0xc(r1)
    stfs f0, 0x124(r31)
    lfs f0, 0x10(r1)
    stfs f0, 0x128(r31)
    lfs f0, 0x14(r1)
    stfs f0, 0x12c(r31)
    lwz r12, 0x218(r31)
    lwz r12, 0x70(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x21c(r31)
    li r4, 0
    lwz r12, 0(r3)
    lwz r12, 0x2c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x21c(r31)
    addi r4, r31, 0x230
    lwz r12, 0(r3)
    lwz r12, 0x24(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x2c4(r31)
    li r29, 0
    lwz r30, 0(r3)
    b L_a3f4
L_a3cc:
    lwz r12, 0x218(r31)
    rlwinm r0, r29, 2, 0xe, 0x1d
    add r4, r30, r0
    addi r3, r31, 0x218
    lwz r12, 0x54(r12)
    li r5, 1
    lwz r4, 4(r4)
    mtctr r12
    bctrl 
    addi r29, r29, 1
L_a3f4:
    lhz r0, 0(r30)
    clrlwi r3, r29, 0x10
    cmplw r3, r0
    blt L_a3cc
    li r29, 0
    b L_a434
L_a40c:
    lwz r12, 0x218(r31)
    rlwinm r0, r29, 2, 0xe, 0x1d
    add r4, r30, r0
    addi r3, r31, 0x218
    lwz r12, 0x54(r12)
    li r5, 0
    lwz r4, 0x14(r4)
    mtctr r12
    bctrl 
    addi r29, r29, 1
L_a434:
    lhz r0, 2(r30)
    clrlwi r3, r29, 0x10
    cmplw r3, r0
    blt L_a40c
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr 
}

extern "C" asm void updateInput__Q39textinput9inputform12LayoutByNW4RFiffUlUlUlPv() {
    nofralloc
    stwu r1, -0x70(r1)
    mflr r0
    stw r0, 0x74(r1)
    stfd f31, 0x60(r1)
    psq_st f31, 104(r1), 0, 0
    stfd f30, 0x50(r1)
    psq_st f30, 88(r1), 0, 0
    addi r11, r1, 0x50
L_ad5c:
    bl _savegpr_25
    lwz r31, 0x304(r3)
    fmr f30, f1
    fmr f31, f2
    mr r25, r3
    clrlwi. r0, r31, 0x1f
    mr r26, r4
    mr r27, r5
    mr r28, r6
    mr r29, r7
    mr r30, r8
    beq L_ada4
    lwz r12, 0(r3)
    li r4, 8
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
L_ada4:
    rlwinm. r0, r31, 0, 0x1e, 0x1e
    beq L_adc8
    lwz r12, 0(r25)
    mr r3, r25
    li r4, 9
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
L_adc8:
    rlwinm. r0, r31, 0, 0x1c, 0x1c
    beq L_adec
    lwz r12, 0(r25)
    mr r3, r25
    li r4, 0xa
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
L_adec:
    rlwinm. r0, r31, 0, 0x1d, 0x1d
    beq L_ae10
    lwz r12, 0(r25)
    mr r3, r25
    li r4, 0xb
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
L_ae10:
    fmr f1, f30
    mr r4, r26
    fmr f2, f31
    mr r5, r27
    mr r6, r28
    mr r7, r29
    mr r8, r30
    addi r3, r25, 0x218
L_ae30:
    bl updateInput__Q39textinput11nw4rmanager6LayoutFiffUlUlUlPv
    rlwinm. r0, r29, 0, 0x14, 0x14
    mr r31, r3
    beq L_ae78
    lwz r3, 0x164(r25)
    lwz r12, 0(r3)
    lwz r12, 0x78(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_ae78
    lwz r12, 0(r25)
    mr r3, r25
    li r4, 0xd
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
L_ae78:
    cmpwi r31, 0
    bne L_af78
    rlwinm. r0, r28, 0, 0x14, 0x14
    beq L_af78
    lwz r3, 0x164(r25)
    lwz r12, 0(r3)
    lwz r12, 0x78(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_af78
    stfs f30, 0x20(r1)
    mr r3, r25
    stfs f31, 0x24(r1)
    lwz r12, 0(r25)
    lwz r12, 0x184(r12)
    mtctr r12
    bctrl 
    lfs f1, 0x124(r25)
    fneg f3, f31
    lfs f0, 0x12c(r25)
    stw r4, 0x1c(r1)
    fsubs f2, f1, f0
    lfs f1, lbl_81694D3C(r0)
    lfs f0, 0x1c(r1)
    stw r3, 0x18(r1)
    fmuls f1, f2, f1
    fadds f0, f1, f0
    fcmpo cr0, f3, f0
    bge L_af20
    lwz r12, 0(r25)
    mr r3, r25
    lwz r12, 0x184(r12)
    mtctr r12
    bctrl 
    stw r4, 0x14(r1)
    lfs f0, lbl_81694D38(r0)
    lfs f1, 0x14(r1)
    stw r3, 0x10(r1)
    fsubs f0, f1, f0
    stfs f0, 0x24(r1)
    b L_af5c
L_af20:
    lwz r12, 0(r25)
    mr r3, r25
    lwz r12, 0x184(r12)
    mtctr r12
    bctrl 
    lfs f1, 0x124(r25)
    lfs f0, 0x12c(r25)
    stw r4, 0xc(r1)
    fsubs f2, f1, f0
    lfs f0, lbl_81694D38(r0)
    lfs f1, 0xc(r1)
    stw r3, 8(r1)
    fadds f1, f2, f1
    fadds f0, f0, f1
    stfs f0, 0x24(r1)
L_af5c:
    lwz r12, 0(r25)
    mr r3, r25
    addi r5, r1, 0x20
    li r4, 0x10
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
L_af78:
    mr r3, r31
    psq_l f31, 104(r1), 0, 0
    lfd f31, 0x60(r1)
    psq_l f30, 88(r1), 0, 0
    lfd f30, 0x50(r1)
    addi r11, r1, 0x50
L_af90:
    bl _restgpr_25
    lwz r0, 0x74(r1)
    mtlr r0
    addi r1, r1, 0x70
    blr 
}

extern "C" asm void onCommand__Q39textinput9inputform4BaseFQ39textinput15CommandReceiver13INPUT_COMMANDPv() {
    nofralloc
    stwu r1, -0x250(r1)
    mflr r0
    stw r0, 0x254(r1)
    addi r11, r1, 0x250
L_e74:
    bl _savegpr_19
    mr r26, r3
    mr r19, r4
    mr r27, r5
L_e84:
    bl onCommand__Q29textinput15CommandReceiverFQ39textinput15CommandReceiver13INPUT_COMMANDPv
    mr r3, r26
    li r4, 0
L_e90:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r5, 0x164(r26)
    cmplwi r19, 0x2f
    mr r29, r3
    subf r0, r3, r5
    cntlzw r0, r0
    srwi r6, r0, 5
    bgt L_2e4c
    lis r4, jumptable_8165CA8C@l
    slwi r0, r19, 2
    addi r4, r4, jumptable_8165CA8C@ha
    lwzx r4, r4, r0
    mtctr r4
    bctr 
    lwz r0, 0x168(r26)
    cmplw r3, r0
    bne L_f64
    lbz r0, sGather_guard__Q39textinput12LayoutGather(r0)
    extsb. r0, r0
    bne L_f08
    la r3, sGather_local__Q39textinput12LayoutGather(r0)
L_ee4:
    bl __ct__Q29textinput12LayoutGatherFv
    lis r4, __dt__Q29textinput12LayoutGatherFv@l
    lis r5, lbl_810C6590@l
    addi r4, r4, __dt__Q29textinput12LayoutGatherFv@ha
    la r3, sGather_local__Q39textinput12LayoutGather(r0)
    addi r5, r5, lbl_810C6590@ha
L_efc:
    bl __register_global_object
    li r0, 1
    stb r0, sGather_guard__Q39textinput12LayoutGather(r0)
L_f08:
    lbz r0, sGather_local__Q39textinput12LayoutGather(r0)
    la r4, sGather_local__Q39textinput12LayoutGather(r0)
    li r3, 0
    rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
    bne L_f28
    lbz r0, 0(r4)
    rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
    beq L_f2c
L_f28:
    li r3, 1
L_f2c:
    cmpwi r3, 0
    beq L_f4c
    lwz r12, 0(r26)
    mr r3, r26
    lwz r12, 0x194(r12)
    mtctr r12
    bctrl 
    b L_2e60
L_f4c:
    lwz r12, 0(r26)
    mr r3, r26
    lwz r12, 0x198(r12)
    mtctr r12
    bctrl 
    b L_2e60
L_f64:
    addi r3, r26, 0x1d8
    li r4, 0
    li r5, 0
L_f70:
    bl KPRLookAhead
    clrlwi. r0, r3, 0x18
    beq L_f94
    lis r4, 1
    addi r3, r26, 0x1d8
    addi r0, r4, -1
    clrlwi r4, r0, 0x10
L_f8c:
    bl KPRPutChar
    b L_fa0
L_f94:
    addi r3, r26, 0x1d8
    li r4, 0x20
L_f9c:
    bl KPRPutChar
L_fa0:
    lbz r0, 0x1e8(r26)
    cmpwi r0, 0
    bne L_fc4
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 0xa
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
L_fc4:
    lwz r19, 0x168(r26)
    mr r3, r26
    li r4, 0
L_fd0:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    cmplw r3, r19
    bne L_ff0
    lwz r12, 0(r19)
    mr r3, r19
    lwz r12, 0xdc(r12)
    mtctr r12
    bctrl 
L_ff0:
    lis r31, lbl_8165C970@l
    li r25, 3
    addi r31, r31, lbl_8165C970@ha
L_ffc:
    addi r3, r26, 0x1d8
L_1000:
    bl KPRGetChar
    lbz r0, sbCompatibleFilterEnabled__Q39textinput9inputform13DeadKeyStream(r0)
    mr r30, r3
    cmpwi r0, 0
    beq L_1148
    b L_1024
L_1018:
    addi r3, r26, 0x1d8
L_101c:
    bl KPRGetChar
    mr r30, r3
L_1024:
    lhz r24, 0(r31)
    clrlwi r3, r30, 0x10
    lhz r23, 2(r31)
    lhz r22, 4(r31)
    cmplw r3, r24
    lhz r21, 6(r31)
    lhz r20, 8(r31)
    lhz r19, 0xa(r31)
    lhz r12, 0xc(r31)
    lhz r11, 0xe(r31)
    lhz r10, 0x10(r31)
    lhz r9, 0x12(r31)
    lhz r8, 0x14(r31)
    lhz r7, 0x16(r31)
    lhz r6, 0x18(r31)
    lhz r5, 0x1a(r31)
    lhz r4, 0x1c(r31)
    lhz r0, 0x1e(r31)
    sth r24, 0x70(r1)
    sth r23, 0x72(r1)
    sth r22, 0x74(r1)
    sth r21, 0x76(r1)
    sth r20, 0x78(r1)
    sth r19, 0x7a(r1)
    sth r12, 0x7c(r1)
    sth r11, 0x7e(r1)
    sth r10, 0x80(r1)
    sth r9, 0x82(r1)
    sth r8, 0x84(r1)
    sth r7, 0x86(r1)
    sth r6, 0x88(r1)
    sth r5, 0x8a(r1)
    sth r4, 0x8c(r1)
    sth r0, 0x8e(r1)
    blt L_10b8
    cmplw r3, r4
    ble L_10c0
L_10b8:
    li r0, 1
    b L_1140
L_10c0:
    addi r5, r1, 0x70
    li r4, 0
    mtctr r25
L_10cc:
    lhz r0, 0(r5)
    cmplw r3, r0
    bne L_10e0
    li r0, 0
    b L_1140
L_10e0:
    lhz r0, 2(r5)
    cmplw r3, r0
    bne L_10f4
    li r0, 0
    b L_1140
L_10f4:
    lhz r0, 4(r5)
    cmplw r3, r0
    bne L_1108
    li r0, 0
    b L_1140
L_1108:
    lhz r0, 6(r5)
    cmplw r3, r0
    bne L_111c
    li r0, 0
    b L_1140
L_111c:
    lhz r0, 8(r5)
    cmplw r3, r0
    bne L_1130
    li r0, 0
    b L_1140
L_1130:
    addi r5, r5, 0xa
    addi r4, r4, 4
    bdnz L_10cc
    li r0, 1
L_1140:
    cmpwi r0, 0
    beq L_1018
L_1148:
    clrlwi. r0, r30, 0x10
    beq L_2e4c
    lbz r0, 0x178(r26)
    cmpwi r0, 0
    bne L_1164
    li r0, 0
    b L_11bc
L_1164:
    lwz r0, 0x174(r26)
    cmpwi r0, 1
    bne L_1178
    li r0, 0
    b L_11bc
L_1178:
    lwz r0, 0x1f0(r26)
    cmpwi r0, 8
    bne L_11b8
    lwz r3, 0x1d4(r26)
    lwz r12, 0(r3)
    lwz r12, 0x90(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x4c(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_11b8
    li r0, 0
    b L_11bc
L_11b8:
    li r0, 1
L_11bc:
    cmpwi r0, 0
    beq L_11d8
    mr r3, r26
    clrlwi r4, r30, 0x10
    li r5, 0
L_11d0:
    bl inputCharZi___Q39textinput9inputform4BaseFwUl
    b L_ffc
L_11d8:
    mr r3, r26
    clrlwi r4, r30, 0x10
    li r5, 0
L_11e4:
    bl inputCharDefault___Q39textinput9inputform4BaseFwUl
    b L_ffc
    lbz r0, 8(r27)
    lhz r30, 0(r27)
    cmpwi r0, 0
    lwz r28, 4(r27)
    beq L_1380
    lwz r3, 0x1d4(r26)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x58(r12)
    mtctr r12
    bctrl 
    stw r3, 0x40(r1)
    lwz r3, 0x1d4(r26)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x58(r12)
    mtctr r12
    bctrl 
    cntlzw r0, r3
    lwz r3, 0x1d4(r26)
    srwi r0, r0, 5
    lwz r12, 0(r3)
    stb r0, 0x45(r1)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x58(r12)
    mtctr r12
    bctrl 
    addi r0, r3, -1
    mr r3, r26
    cntlzw r0, r0
    li r4, 0
    srwi r0, r0, 5
    stb r0, 0x44(r1)
L_1294:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r4, 0x164(r26)
    lwz r0, 0x24(r3)
    cmplw r3, r4
    stw r0, 0x48(r1)
    bne L_1310
    lwz r0, 0x1f0(r26)
    lwz r19, 0x40(r1)
    cmpwi r0, 9
    bne L_12cc
    cmpwi r19, 0
    beq L_12d8
    li r19, 3
    b L_12d8
L_12cc:
    cmpwi r0, 8
    bne L_12d8
    li r19, 0
L_12d8:
    lwz r12, 0(r4)
    mr r3, r4
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r26)
    mr r4, r19
L_12f4:
    bl setTranslateMode__Q39textinput8tistring9DecolatedFQ49textinput8tistring9Decolated13TranslateMode
    lwz r3, 0x164(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    b L_1318
L_1310:
    lwz r4, 0x40(r1)
L_1314:
    bl setTranslateMode__Q39textinput8tistring9DecolatedFQ49textinput8tistring9Decolated13TranslateMode
L_1318:
    lbz r0, 0x178(r26)
    cmpwi r0, 0
    bne L_132c
    li r0, 0
    b L_133c
L_132c:
    lwz r3, 0x174(r26)
    addi r0, r3, -1
    cntlzw r0, r0
    srwi r0, r0, 5
L_133c:
    cmpwi r0, 0
    beq L_1380
    lwz r3, 0x168(r26)
    li r0, 0
    stb r0, 0x4d(r1)
    lwz r12, 0(r3)
    stb r0, 0x4c(r1)
    lwz r12, 0x12c(r12)
    lbz r4, 0x45(r1)
    mtctr r12
    bctrl 
    lwz r3, 0x168(r26)
    lbz r4, 0x44(r1)
    lwz r12, 0(r3)
    lwz r12, 0x120(r12)
    mtctr r12
    bctrl 
L_1380:
    lbz r0, 9(r27)
    cmpwi r0, 0
    beq L_139c
    lwz r3, 0x1f0(r26)
    mr r4, r30
L_1394:
    bl ToCombineClass__Q39textinput9inputform13DeadKeyStreamFQ29textinput8Languagew
    mr r30, r3
L_139c:
    clrlwi r0, r30, 0x10
    cmplwi r0, 0x20
    bne L_13d8
    addi r3, r26, 0x1d8
    li r4, 0
    li r5, 0
L_13b4:
    bl KPRLookAhead
    clrlwi. r0, r3, 0x18
    beq L_13d8
    lis r4, 1
    addi r3, r26, 0x1d8
    addi r0, r4, -1
    clrlwi r4, r0, 0x10
L_13d0:
    bl KPRPutChar
    b L_13e4
L_13d8:
    addi r3, r26, 0x1d8
    clrlwi r4, r30, 0x10
L_13e0:
    bl KPRPutChar
L_13e4:
    lbz r0, 0x1e8(r26)
    cmpwi r0, 0
    bne L_1408
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 0xa
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
L_1408:
    lwz r19, 0x168(r26)
    mr r3, r26
    li r4, 0
L_1414:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    cmplw r3, r19
    bne L_1434
    lwz r12, 0(r19)
    mr r3, r19
    lwz r12, 0xdc(r12)
    mtctr r12
    bctrl 
L_1434:
    lis r31, lbl_8165C970@l
    li r25, 3
    addi r31, r31, lbl_8165C970@ha
L_1440:
    addi r3, r26, 0x1d8
L_1444:
    bl KPRGetChar
    lbz r0, sbCompatibleFilterEnabled__Q39textinput9inputform13DeadKeyStream(r0)
    mr r30, r3
    cmpwi r0, 0
    beq L_158c
    b L_1468
L_145c:
    addi r3, r26, 0x1d8
L_1460:
    bl KPRGetChar
    mr r30, r3
L_1468:
    lhz r19, 0(r31)
    clrlwi r3, r30, 0x10
    lhz r20, 2(r31)
    lhz r21, 4(r31)
    cmplw r3, r19
    lhz r22, 6(r31)
    lhz r23, 8(r31)
    lhz r24, 0xa(r31)
    lhz r12, 0xc(r31)
    lhz r11, 0xe(r31)
    lhz r10, 0x10(r31)
    lhz r9, 0x12(r31)
    lhz r8, 0x14(r31)
    lhz r7, 0x16(r31)
    lhz r6, 0x18(r31)
    lhz r5, 0x1a(r31)
    lhz r4, 0x1c(r31)
    lhz r0, 0x1e(r31)
    sth r19, 0x50(r1)
    sth r20, 0x52(r1)
    sth r21, 0x54(r1)
    sth r22, 0x56(r1)
    sth r23, 0x58(r1)
    sth r24, 0x5a(r1)
    sth r12, 0x5c(r1)
    sth r11, 0x5e(r1)
    sth r10, 0x60(r1)
    sth r9, 0x62(r1)
    sth r8, 0x64(r1)
    sth r7, 0x66(r1)
    sth r6, 0x68(r1)
    sth r5, 0x6a(r1)
    sth r4, 0x6c(r1)
    sth r0, 0x6e(r1)
    blt L_14fc
    cmplw r3, r4
    ble L_1504
L_14fc:
    li r0, 1
    b L_1584
L_1504:
    addi r5, r1, 0x50
    li r4, 0
    mtctr r25
L_1510:
    lhz r0, 0(r5)
    cmplw r3, r0
    bne L_1524
    li r0, 0
    b L_1584
L_1524:
    lhz r0, 2(r5)
    cmplw r3, r0
    bne L_1538
    li r0, 0
    b L_1584
L_1538:
    lhz r0, 4(r5)
    cmplw r3, r0
    bne L_154c
    li r0, 0
    b L_1584
L_154c:
    lhz r0, 6(r5)
    cmplw r3, r0
    bne L_1560
    li r0, 0
    b L_1584
L_1560:
    lhz r0, 8(r5)
    cmplw r3, r0
    bne L_1574
    li r0, 0
    b L_1584
L_1574:
    addi r5, r5, 0xa
    addi r4, r4, 4
    bdnz L_1510
    li r0, 1
L_1584:
    cmpwi r0, 0
    beq L_145c
L_158c:
    clrlwi. r0, r30, 0x10
    beq L_1630
    lbz r0, 0x178(r26)
    cmpwi r0, 0
    bne L_15a8
    li r0, 0
    b L_1600
L_15a8:
    lwz r0, 0x174(r26)
    cmpwi r0, 1
    bne L_15bc
    li r0, 0
    b L_1600
L_15bc:
    lwz r0, 0x1f0(r26)
    cmpwi r0, 8
    bne L_15fc
    lwz r3, 0x1d4(r26)
    lwz r12, 0(r3)
    lwz r12, 0x90(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x4c(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_15fc
    li r0, 0
    b L_1600
L_15fc:
    li r0, 1
L_1600:
    cmpwi r0, 0
    beq L_161c
    mr r3, r26
    mr r5, r28
    clrlwi r4, r30, 0x10
L_1614:
    bl inputCharZi___Q39textinput9inputform4BaseFwUl
    b L_1440
L_161c:
    mr r3, r26
    mr r5, r28
    clrlwi r4, r30, 0x10
L_1628:
    bl inputCharDefault___Q39textinput9inputform4BaseFwUl
    b L_1440
L_1630:
    lwz r0, 0x16c(r26)
    cmplw r29, r0
    bne L_1644
    li r0, 0
    stb r0, 0x1f4(r26)
L_1644:
    lbz r0, 8(r27)
    cmpwi r0, 0
    beq L_1730
    mr r3, r26
    li r4, 0
L_1658:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r4, 0x164(r26)
    cmplw r3, r4
    bne L_16cc
    lwz r0, 0x1f0(r26)
    lwz r19, 0x48(r1)
    cmpwi r0, 9
    bne L_1688
    cmpwi r19, 0
    beq L_1694
    li r19, 3
    b L_1694
L_1688:
    cmpwi r0, 8
    bne L_1694
    li r19, 0
L_1694:
    lwz r12, 0(r4)
    mr r3, r4
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r26)
    mr r4, r19
L_16b0:
    bl setTranslateMode__Q39textinput8tistring9DecolatedFQ49textinput8tistring9Decolated13TranslateMode
    lwz r3, 0x164(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    b L_16d4
L_16cc:
    lwz r4, 0x48(r1)
L_16d0:
    bl setTranslateMode__Q39textinput8tistring9DecolatedFQ49textinput8tistring9Decolated13TranslateMode
L_16d4:
    lbz r0, 0x178(r26)
    cmpwi r0, 0
    bne L_16e8
    li r0, 0
    b L_16f8
L_16e8:
    lwz r3, 0x174(r26)
    addi r0, r3, -1
    cntlzw r0, r0
    srwi r0, r0, 5
L_16f8:
    cmpwi r0, 0
    beq L_1730
    lwz r3, 0x168(r26)
    lbz r4, 0x4d(r1)
    lwz r12, 0(r3)
    lwz r12, 0x12c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x168(r26)
    lbz r4, 0x4c(r1)
    lwz r12, 0(r3)
    lwz r12, 0x120(r12)
    mtctr r12
    bctrl 
L_1730:
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 1
    lwz r12, 0xf4(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_2e4c
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 0x21
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
    b L_2e4c
    lwz r12, 0(r3)
    lwz r12, 0x84(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_17a4
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 7
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    b L_17bc
L_17a4:
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 8
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
L_17bc:
    lwz r0, 0x164(r26)
    cmplw r29, r0
    bne L_18cc
    lwz r3, 0x1d4(r26)
    lwz r12, 0(r3)
    lwz r12, 0x6c(r12)
    mtctr r12
    bctrl 
    li r0, 0
    stb r0, 0x15(r3)
    stb r0, 0x16(r3)
    lwz r3, 0x168(r26)
    lwz r12, 0(r3)
    lwz r12, 0x128(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r26)
    mr r3, r26
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r26)
    lwz r12, 0(r3)
    lwz r12, 0x5c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x1d4(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_186c
    lwz r3, 0x1d4(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
L_1868:
    bl resetHoldingButton__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv
L_186c:
    lwz r3, 0x164(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    mr r3, r26
    li r4, 0
L_1888:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r3, 0x16c(r26)
    cmpwi r3, 0
    beq L_19a4
    lwz r0, 0x1f0(r26)
    cmpwi r0, 8
    bne L_19a4
    li r4, 0
L_18a8:
    bl setCurrentWord__Q39textinput8tistring6WithZiFPCw
    lwz r3, 0x16c(r26)
L_18b0:
    bl update__Q39textinput8tistring6WithZiFv
    lwz r12, 0(r26)
    mr r3, r26
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    b L_19a4
L_18cc:
    lwz r0, 0x16c(r26)
    cmplw r29, r0
    bne L_192c
    li r0, 0
    mr r3, r29
    stb r0, 0x1f4(r26)
    lwz r12, 0(r29)
    lwz r12, 0x5c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x1d4(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_19a4
    lwz r3, 0x1d4(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
L_1924:
    bl resetHoldingButton__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv
    b L_19a4
L_192c:
    lwz r3, 0x168(r26)
    lwz r12, 0(r3)
    lwz r12, 0xdc(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_1990
    lwz r3, 0x168(r26)
    lwz r12, 0(r3)
    lwz r12, 0x5c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x1d4(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_1990
    lwz r3, 0x1d4(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
L_198c:
    bl resetHoldingButton__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv
L_1990:
    lwz r12, 0(r26)
    mr r3, r26
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
L_19a4:
    li r0, 2
    mr r3, r26
    stw r0, 0x1b0(r26)
    li r4, 1
    lwz r12, 0(r26)
    lwz r12, 0xf4(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_2e4c
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 0x21
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
    b L_2e4c
    cmplw r3, r5
    beq L_1a10
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 8
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    b L_2e60
L_1a10:
    lwz r12, 0(r5)
    mr r3, r5
    lwz r12, 0x88(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_1a48
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 8
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    b L_2e4c
L_1a48:
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 7
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    b L_2e4c
    cmplw r3, r5
    bne L_1da8
    lwz r0, 0x1f0(r26)
    cmpwi r0, 9
    bne L_1b4c
    mr r3, r26
    li r4, 0
L_1a80:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r12, 0(r3)
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_1b4c
    lwz r3, 0x164(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r26)
    li r4, 0xa
    lwz r12, 0(r3)
    lwz r12, 0x50(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r0, 0x1f0(r26)
    cmpwi r0, 8
    bne L_1b4c
    lbz r0, 0x178(r26)
    cmpwi r0, 0
    bne L_1afc
    li r0, 0
    b L_1b30
L_1afc:
    lwz r0, 0x174(r26)
    cmpwi r0, 1
    beq L_1b2c
    lwz r3, 0x16c(r26)
    lwz r12, 0(r3)
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    ble L_1b2c
    li r0, 1
    b L_1b30
L_1b2c:
    li r0, 0
L_1b30:
    cmpwi r0, 0
    beq L_1b4c
    lwz r3, 0x16c(r26)
    li r4, 0
L_1b40:
    bl setCurrentWord__Q39textinput8tistring6WithZiFPCw
    lwz r3, 0x16c(r26)
L_1b48:
    bl update__Q39textinput8tistring6WithZiFv
L_1b4c:
    lwz r3, 0x1d4(r26)
    lwz r12, 0(r3)
    lwz r12, 0x6c(r12)
    mtctr r12
    bctrl 
    li r0, 0
    stb r0, 0x15(r3)
    stb r0, 0x16(r3)
    lwz r3, 0x168(r26)
    lwz r12, 0(r3)
    lwz r12, 0x128(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r26)
    mr r3, r26
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x1d4(r26)
    lwz r12, 0(r3)
    lwz r12, 0x94(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_1bdc
    lwz r3, 0x1d4(r26)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lbz r19, 0xfc(r3)
    b L_1bf4
L_1bdc:
    lwz r3, 0x1d4(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lbz r19, 0xe0(r3)
L_1bf4:
    lwz r3, 0x164(r26)
    li r20, 1
    lwz r12, 0(r3)
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_1c54
    cmpwi r19, 0
    li r25, 0
    beq L_1c48
    lwz r12, 0x5c(r26)
    addi r3, r26, 0x10
    lwz r12, 0x34(r12)
    mtctr r12
    bctrl 
    lwz r0, 0x1bc(r26)
    addi r3, r3, 1
    cmplw r0, r3
    blt L_1c48
    li r25, 1
L_1c48:
    cmpwi r25, 0
    bne L_1c54
    li r20, 0
L_1c54:
    lwz r12, 0x5c(r26)
    addi r3, r26, 0x10
    li r19, 1
    lwz r12, 0x34(r12)
    mtctr r12
    bctrl 
    lwz r0, 0x1bc(r26)
    addi r3, r3, 1
    cmplw r0, r3
    blt L_1cac
    lwz r3, 0x1d4(r26)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x10c(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_1cac
    li r19, 0
L_1cac:
    cmpwi r20, 0
    beq L_1d80
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 9
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r26)
    li r4, 0xa
    lwz r12, 0(r3)
    lwz r12, 0x50(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r0, 0x1f0(r26)
    cmpwi r0, 8
    bne L_1f9c
    lbz r0, 0x178(r26)
    cmpwi r0, 0
    bne L_1d2c
    li r0, 0
    b L_1d60
L_1d2c:
    lwz r0, 0x174(r26)
    cmpwi r0, 1
    beq L_1d5c
    lwz r3, 0x16c(r26)
    lwz r12, 0(r3)
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    ble L_1d5c
    li r0, 1
    b L_1d60
L_1d5c:
    li r0, 0
L_1d60:
    cmpwi r0, 0
    beq L_1f9c
    lwz r3, 0x16c(r26)
    li r4, 0
L_1d70:
    bl setCurrentWord__Q39textinput8tistring6WithZiFPCw
    lwz r3, 0x16c(r26)
L_1d78:
    bl update__Q39textinput8tistring6WithZiFv
    b L_1f9c
L_1d80:
    cmpwi r19, 0
    beq L_2e60
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 8
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    b L_2e60
    b L_2e60
L_1da8:
    lwz r0, 0x16c(r26)
    cmplw r3, r0
    bne L_1f1c
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 9
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r26)
    mr r3, r26
    lwz r12, 0x114(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0xb
    beq L_1e04
    lwz r12, 0(r26)
    mr r3, r26
    lwz r12, 0x114(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0xc
    bne L_1e10
L_1e04:
    mr r3, r26
L_1e08:
    bl confirmInput___Q39textinput9inputform4BaseFv
    b L_1f9c
L_1e10:
    lbz r3, 0x1f5(r26)
    lbz r0, 0x1f4(r26)
    or. r0, r3, r0
    bne L_1f10
    lwz r3, 0x1d4(r26)
    lwz r12, 0(r3)
    lwz r12, 0x94(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_1f10
    lbz r0, 0x178(r26)
    cmpwi r0, 0
    beq L_1f9c
    lwz r0, 0x174(r26)
    cmpwi r0, 1
    beq L_1f9c
    lwz r3, 0x16c(r26)
    addi r4, r1, 0x90
    li r5, 0x40
L_1e70:
    bl getCurrentInput__Q39textinput8tistring6WithZiFPwUl
    lwz r3, 0x164(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r26)
    addi r4, r1, 0x90
    lwz r12, 0(r3)
    lwz r12, 0x54(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x16c(r26)
L_1eb8:
    bl clearCandidates__Q39textinput8tistring6WithZiFv
    li r0, 0
    mr r3, r26
    stb r0, 0x1f4(r26)
    li r4, 0
L_1ecc:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r3, 0x16c(r26)
    cmpwi r3, 0
    beq L_1f9c
    lwz r0, 0x1f0(r26)
    cmpwi r0, 8
    bne L_1f9c
    li r4, 0
L_1eec:
    bl setCurrentWord__Q39textinput8tistring6WithZiFPCw
    lwz r3, 0x16c(r26)
L_1ef4:
    bl update__Q39textinput8tistring6WithZiFv
    lwz r12, 0(r26)
    mr r3, r26
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    b L_1f9c
L_1f10:
    mr r3, r26
L_1f14:
    bl confirmInput___Q39textinput9inputform4BaseFv
    b L_1f9c
L_1f1c:
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 9
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x168(r26)
    lwz r12, 0(r3)
    lwz r12, 0xdc(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_1f94
    lwz r3, 0x168(r26)
    lwz r12, 0(r3)
    lwz r12, 0x138(r12)
    mtctr r12
    bctrl 
    extsh r4, r3
    lwz r3, 0x168(r26)
    lwz r12, 0(r3)
    lwz r12, 0xec(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r26)
    mr r3, r26
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    b L_1f9c
L_1f94:
    mr r3, r26
L_1f98:
    bl confirmInput___Q39textinput9inputform4BaseFv
L_1f9c:
    li r0, 1
    mr r3, r26
    stw r0, 0x1b0(r26)
    li r4, 1
    lwz r12, 0(r26)
    lwz r12, 0xf4(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_2e4c
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 0x21
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
    b L_2e4c
    mr r3, r26
L_1fe8:
    bl confirmInput___Q39textinput9inputform4BaseFv
    li r0, 1
    stw r0, 0x1b0(r26)
    b L_2e4c
    lwz r0, 0x174(r26)
    cmpwi r0, 0xb
    bne L_2018
    lwz r0, 0x16c(r26)
    cmplw r3, r0
    bne L_2018
    li r0, 0
    stb r0, 0x1f4(r26)
L_2018:
    lhz r4, 0(r27)
    mr r3, r26
L_2020:
    bl inputInputting___Q39textinput9inputform4BaseFw
    b L_2e4c
    lhz r4, 0(r27)
    cmpwi r4, 0
    beq L_2e60
    lbz r5, 4(r27)
    mr r3, r26
    lhz r6, 2(r27)
    lbz r7, 6(r27)
    lwz r8, 8(r27)
L_2048:
    bl confirmInputting___Q39textinput9inputform4BaseFwbUsbPv
    lbz r0, 7(r27)
    cmpwi r0, 0
    bne L_2098
    lbz r0, 6(r27)
    cmpwi r0, 0
    beq L_2080
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 9
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    b L_2098
L_2080:
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 0xa
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
L_2098:
    li r0, 1
    mr r3, r26
    stw r0, 0x1b0(r26)
    li r4, 1
    lwz r12, 0(r26)
    lwz r12, 0xf4(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_2e4c
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 0x21
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
    b L_2e4c
    cmplw r3, r5
    bne L_2100
    lwz r12, 0(r26)
    mr r3, r26
    lwz r12, 0x19c(r12)
    mtctr r12
    bctrl 
    b L_2e60
L_2100:
    mr r3, r26
    li r4, 0x1f
    li r5, 0
L_210c:
    bl onHKBCtrlCode__Q39textinput9inputform4BaseFQ29textinput7HVKCodeUl
    b L_2e60
    cmplw r3, r5
    bne L_2134
    lwz r12, 0(r26)
    mr r3, r26
    lwz r12, 0x1a0(r12)
    mtctr r12
    bctrl 
    b L_2e60
L_2134:
    mr r3, r26
    li r4, 0x20
    li r5, 0
L_2140:
    bl onHKBCtrlCode__Q39textinput9inputform4BaseFQ29textinput7HVKCodeUl
    b L_2e60
    lwz r12, 0(r26)
    mr r3, r26
    lwz r12, 0x194(r12)
    mtctr r12
    bctrl 
    b L_2e60
    lwz r12, 0(r26)
    mr r3, r26
    lwz r12, 0x198(r12)
    mtctr r12
    bctrl 
    b L_2e60
    lwz r12, 0(r26)
    mr r3, r26
    mr r4, r27
    lwz r12, 0x168(r12)
    mtctr r12
    bctrl 
    b L_2e60
    cmpwi r6, 0
    beq L_229c
    lwz r12, 0(r3)
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_229c
    lwz r12, 0(r26)
    mr r3, r26
    lwz r12, 0x184(r12)
    mtctr r12
    bctrl 
    stw r3, 0x38(r1)
    lwz r12, 0(r26)
    stw r4, 0x3c(r1)
    lfs f3, 0(r27)
    lfs f1, 0x38(r1)
    stw r3, 0x20(r1)
    mr r3, r26
    lfs f2, 4(r27)
    fsubs f1, f3, f1
    lfs f0, 0x3c(r1)
    lwz r12, 0x180(r12)
    fsubs f2, f2, f0
    stw r4, 0x24(r1)
    mtctr r12
    bctrl 
    lwz r12, 0(r29)
    mr r4, r3
    mr r3, r29
    lwz r12, 0x6c(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 5
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 0xc
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x1d4(r26)
    lwz r12, 0(r3)
    lwz r12, 0x6c(r12)
    mtctr r12
    bctrl 
    li r0, 0
    stb r0, 0x15(r3)
    stb r0, 0x16(r3)
    lwz r3, 0x168(r26)
    lwz r12, 0(r3)
    lwz r12, 0x128(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r26)
    mr r3, r26
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    b L_2e60
L_229c:
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 9
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 6
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
    b L_2e60
    lwz r12, 0(r3)
    lwz r12, 0x78(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_2e60
    lwz r12, 0(r26)
    mr r3, r26
    lwz r12, 0x184(r12)
    mtctr r12
    bctrl 
    stw r3, 0x30(r1)
    lwz r12, 0(r26)
    stw r4, 0x34(r1)
    lfs f3, 0(r27)
    lfs f1, 0x30(r1)
    stw r3, 0x18(r1)
    mr r3, r26
    lfs f2, 4(r27)
    fsubs f1, f3, f1
    lfs f0, 0x34(r1)
    lwz r12, 0x180(r12)
    fsubs f2, f2, f0
    stw r4, 0x1c(r1)
    mtctr r12
    bctrl 
    lwz r12, 0(r29)
    mr r4, r3
    mr r3, r29
    lwz r12, 0x6c(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 0xd
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
    b L_2e60
    lwz r12, 0(r3)
    lwz r12, 0x78(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_2e60
    lwz r12, 0(r26)
    mr r3, r26
    lwz r12, 0x184(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r29)
    addi r5, r1, 8
    stw r3, 0x10(r1)
    lwz r12, 0x80(r12)
    stw r3, 0x28(r1)
    mr r3, r29
    stw r4, 0x14(r1)
    stw r4, 0x2c(r1)
    addi r4, r1, 0xc
    mtctr r12
    bctrl 
    lwz r12, 0(r26)
    mr r3, r26
    lfs f3, 0(r27)
    lfs f1, 0x28(r1)
    lfs f2, 4(r27)
    lfs f0, 0x2c(r1)
    fsubs f1, f3, f1
    lwz r12, 0x180(r12)
    fsubs f2, f2, f0
    mtctr r12
    bctrl 
    lwz r12, 0(r29)
    mr r19, r3
    mr r3, r29
    lwz r12, 0x6c(r12)
    mr r4, r19
    mtctr r12
    bctrl 
    lwz r0, 0xc(r1)
    cmplw r0, r19
    beq L_2438
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 5
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
L_2438:
    li r0, 1
    stw r0, 0x1b0(r26)
    b L_2e60
    cmpwi r27, 0
    beq L_2e4c
    lbz r0, 0(r27)
    cmpwi r0, 0
    beq L_2e4c
    lwz r3, 0x168(r26)
    li r4, 0
    lwz r12, 0(r3)
    lwz r12, 0x60(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 6
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
    addi r3, r26, 0x118
L_2490:
    bl resetCandidate__Q39textinput12candidatebox18CandidateBoxCallerFv
    addi r3, r26, 0x118
L_2498:
    bl updateCandidate__Q39textinput12candidatebox18CandidateBoxCallerFv
    b L_2e4c
    lbz r0, 0x178(r26)
    cmpwi r0, 0
    beq L_25ec
    lwz r0, 0x174(r26)
    cmpwi r0, 1
    bne L_2560
    lwz r3, 0x168(r26)
    lwz r12, 0(r3)
    lwz r12, 0xdc(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_24f0
    lwz r3, 0x168(r26)
    lwz r4, 0(r27)
    lwz r12, 0(r3)
    lwz r12, 0xec(r12)
    mtctr r12
    bctrl 
    b L_25ec
L_24f0:
    lwz r3, 0x168(r26)
    addi r5, r1, 0x190
    lwz r4, 0(r27)
    lwz r12, 0(r3)
    lwz r12, 0xe8(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r26)
    addi r4, r1, 0x190
    li r5, 0
L_252c:
    bl inputString__Q39textinput8tistring9DecolatedFPCwQ49textinput8tistring9Decolated13TranslateMode
    lwz r3, 0x164(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x168(r26)
    lwz r4, 0(r27)
    lwz r12, 0(r3)
    lwz r12, 0xec(r12)
    mtctr r12
    bctrl 
    b L_25ec
L_2560:
    lwz r3, 0x16c(r26)
    addi r5, r1, 0x110
    lwz r4, 0(r27)
    lwz r12, 0(r3)
    lwz r12, 0xdc(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r26)
    addi r4, r1, 0x110
    lwz r12, 0(r3)
    lwz r12, 0x54(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x16c(r26)
L_25c0:
    bl clearCandidates__Q39textinput8tistring6WithZiFv
    lwz r0, 0x1f0(r26)
    li r3, 0
    stb r3, 0x1f4(r26)
    cmpwi r0, 8
    bne L_25ec
    lwz r3, 0x16c(r26)
    addi r4, r1, 0x110
L_25e0:
    bl setCurrentWord__Q39textinput8tistring6WithZiFPCw
    lwz r3, 0x16c(r26)
L_25e8:
    bl update__Q39textinput8tistring6WithZiFv
L_25ec:
    li r0, 1
    stw r0, 0x1b0(r26)
    b L_2e4c
    lwz r0, 0x1f0(r26)
    lwz r20, 0(r27)
    cmpwi r0, 0
    beq L_2614
    cmpwi r0, 9
    beq L_2614
    li r20, 0
L_2614:
    cmpwi r0, 9
    mr r19, r20
    bne L_2630
    cmpwi r20, 0
    beq L_263c
    li r19, 3
    b L_263c
L_2630:
    cmpwi r0, 8
    bne L_263c
    li r19, 0
L_263c:
    lwz r12, 0(r5)
    mr r3, r5
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r26)
    mr r4, r19
L_2658:
    bl setTranslateMode__Q39textinput8tistring9DecolatedFQ49textinput8tistring9Decolated13TranslateMode
    lwz r3, 0x164(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x168(r26)
    mr r4, r20
L_2678:
    bl setTranslateMode__Q39textinput8tistring9DecolatedFQ49textinput8tistring9Decolated13TranslateMode
    b L_2e4c
    lwz r3, 0x168(r26)
    lbz r4, 0(r27)
    lwz r12, 0(r3)
    lwz r12, 0x120(r12)
    mtctr r12
    bctrl 
    b L_2e4c
    lwz r3, 0x168(r26)
    lbz r4, 0(r27)
    lwz r12, 0(r3)
    lwz r12, 0x12c(r12)
    mtctr r12
    bctrl 
    b L_2e4c
    lwz r4, 0(r27)
    mr r3, r26
L_26c0:
    bl moveCandidateToIdx__Q39textinput9inputform4BaseFl
    li r0, 1
    stw r0, 0x1b0(r26)
    b L_2e60
    lbz r0, 0x178(r26)
    cmpwi r0, 0
    beq L_2e4c
    lwz r0, 0x174(r26)
    cmpwi r0, 1
    bne L_2704
    lwz r3, 0x168(r26)
    li r4, -1
    lwz r12, 0(r3)
    lwz r12, 0xf0(r12)
    mtctr r12
    bctrl 
    b L_272c
L_2704:
    cmpwi r0, 0xb
    bne L_272c
    lwz r3, 0x16c(r26)
    li r4, -1
    lwz r12, 0(r3)
    lwz r12, 0xe8(r12)
    mtctr r12
    bctrl 
    li r0, 0
    stb r0, 0x1f4(r26)
L_272c:
    li r0, 1
    stw r0, 0x1b0(r26)
    b L_2e60
    lwz r12, 0(r3)
    lwz r12, 0x9c(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 0xa
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    b L_2e4c
    lwz r12, 0(r3)
    lwz r12, 0xa4(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 0xa
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    b L_2e4c
    lwz r12, 0(r3)
    lwz r12, 0xa8(r12)
    mtctr r12
    bctrl 
    b L_2e4c
    lwz r12, 0(r3)
    lwz r12, 0xb0(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 0xa
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    b L_2e4c
    lwz r3, 0(r27)
    lbz r0, 0x178(r26)
    stw r3, 0x174(r26)
    lbz r4, 4(r27)
    neg r3, r4
    or r3, r3, r4
    srwi r3, r3, 0x1f
    cmplw r0, r3
    beq L_2828
    lwz r0, 0x1f0(r26)
    stb r3, 0x178(r26)
    cmpwi r0, 9
    bne L_2828
    lwz r3, 0x1d4(r26)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x70(r12)
    mtctr r12
    bctrl 
L_2828:
    lwz r3, 0x164(r26)
    lwz r4, 0x168(r26)
    lwz r12, 0(r3)
    lwz r19, 0x24(r3)
    lwz r12, 0xb8(r12)
    lwz r20, 0x24(r4)
    mtctr r12
    bctrl 
    lwz r3, 0x168(r26)
    lwz r12, 0(r3)
    lwz r12, 0xb8(r12)
    mtctr r12
    bctrl 
    lwz r0, 0x1f0(r26)
    cmpwi r0, 9
    bne L_2878
    cmpwi r19, 0
    beq L_2884
    li r19, 3
    b L_2884
L_2878:
    cmpwi r0, 8
    bne L_2884
    li r19, 0
L_2884:
    lwz r3, 0x164(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r26)
    mr r4, r19
L_28a0:
    bl setTranslateMode__Q39textinput8tistring9DecolatedFQ49textinput8tistring9Decolated13TranslateMode
    lwz r3, 0x164(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x168(r26)
    mr r4, r20
L_28c0:
    bl setTranslateMode__Q39textinput8tistring9DecolatedFQ49textinput8tistring9Decolated13TranslateMode
    lwz r0, 0x174(r26)
    cmplwi r0, 0xc
    bgt L_2b50
    lis r3, jumptable_8165CA58@l
    slwi r0, r0, 2
    addi r3, r3, jumptable_8165CA58@ha
    lwzx r3, r3, r0
    mtctr r3
    bctr 
    lbz r0, 0x178(r26)
    cmpwi r0, 0
    bne L_29a4
    lwz r3, 0x168(r26)
    lwz r12, 0(r3)
    lwz r12, 0x11c(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_2e60
    lwz r3, 0x168(r26)
    cmplw r29, r3
    bne L_2e60
    lwz r12, 0(r3)
    li r4, 0
    lwz r12, 0x60(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x168(r26)
    lwz r12, 0(r3)
    lwz r12, 0xe0(r12)
    mtctr r12
    bctrl 
    mr r19, r3
    lwz r3, 0x164(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r26)
    mr r4, r19
    lwz r12, 0(r3)
    lwz r12, 0x60(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x168(r26)
    li r4, 0
    lwz r12, 0(r3)
    lwz r12, 0x114(r12)
    mtctr r12
    bctrl 
    b L_2e60
L_29a4:
    lwz r3, 0x1d4(r26)
    lwz r12, 0(r3)
    lwz r12, 0x6c(r12)
    mtctr r12
    bctrl 
    li r0, 0
    stb r0, 0x15(r3)
    stb r0, 0x16(r3)
    lwz r3, 0x168(r26)
    lwz r12, 0(r3)
    lwz r12, 0x128(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r26)
    mr r3, r26
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    b L_2e60
    lwz r3, 0x16c(r26)
    li r4, 0
    lwz r12, 0(r3)
    lwz r12, 0xf0(r12)
    mtctr r12
    bctrl 
    b L_2b50
    lwz r3, 0x16c(r26)
    li r4, 1
    lwz r12, 0(r3)
    lwz r12, 0xf0(r12)
    mtctr r12
    bctrl 
    b L_2b50
    lwz r3, 0x16c(r26)
    li r4, 2
    lwz r12, 0(r3)
    lwz r12, 0xf0(r12)
    mtctr r12
    bctrl 
    b L_2b50
    lwz r3, 0x16c(r26)
    li r4, 3
    lwz r12, 0(r3)
    lwz r12, 0xf0(r12)
    mtctr r12
    bctrl 
    b L_2b50
    lwz r3, 0x16c(r26)
    li r4, 4
    lwz r12, 0(r3)
    lwz r12, 0xf0(r12)
    mtctr r12
    bctrl 
    b L_2b50
    lwz r3, 0x16c(r26)
    li r4, 5
    lwz r12, 0(r3)
    lwz r12, 0xf0(r12)
    mtctr r12
    bctrl 
    b L_2b50
    lwz r3, 0x16c(r26)
    li r4, 6
    lwz r12, 0(r3)
    lwz r12, 0xf0(r12)
    mtctr r12
    bctrl 
    b L_2b50
    lwz r3, 0x16c(r26)
    li r4, 7
    lwz r12, 0(r3)
    lwz r12, 0xf0(r12)
    mtctr r12
    bctrl 
    b L_2b50
    lwz r3, 0x16c(r26)
    li r4, 8
    lwz r12, 0(r3)
    lwz r12, 0xf0(r12)
    mtctr r12
    bctrl 
    b L_2b50
    lwz r3, 0x16c(r26)
    li r4, 9
    lwz r12, 0(r3)
    lwz r12, 0xf0(r12)
    mtctr r12
    bctrl 
    b L_2b50
    lwz r3, 0x1d4(r26)
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
    beq L_2b3c
    li r4, 0xa
L_2b3c:
    lwz r3, 0x16c(r26)
    lwz r12, 0(r3)
    lwz r12, 0xf0(r12)
    mtctr r12
    bctrl 
L_2b50:
    lwz r12, 0(r26)
    mr r3, r26
    li r4, 0x1e
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
    b L_2e60
    lwz r3, 0x168(r26)
    li r4, 0
    lwz r12, 0(r3)
    lwz r12, 0x60(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x168(r26)
    lwz r12, 0(r3)
    lwz r12, 0xe0(r12)
    mtctr r12
    bctrl 
    mr r19, r3
    lwz r3, 0x164(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r26)
    mr r4, r19
    lwz r12, 0(r3)
    lwz r12, 0x60(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r26)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x168(r26)
    li r4, 0
    lwz r12, 0(r3)
    lwz r12, 0x114(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x16c(r26)
L_2bfc:
    bl clearCandidates__Q39textinput8tistring6WithZiFv
    li r0, 0
    mr r3, r26
    stb r0, 0x1f4(r26)
    li r4, 0
L_2c10:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r3, 0x16c(r26)
    cmpwi r3, 0
    beq L_2c50
    lwz r0, 0x1f0(r26)
    cmpwi r0, 8
    bne L_2c50
    li r4, 0
L_2c30:
    bl setCurrentWord__Q39textinput8tistring6WithZiFPCw
    lwz r3, 0x16c(r26)
L_2c38:
    bl update__Q39textinput8tistring6WithZiFv
    lwz r12, 0(r26)
    mr r3, r26
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
L_2c50:
    addi r3, r26, 0x118
L_2c54:
    bl resetCandidate__Q39textinput12candidatebox18CandidateBoxCallerFv
    b L_2e60
    lwz r0, 0x174(r26)
    stw r0, 0(r27)
    lbz r0, 0x178(r26)
    stb r0, 4(r27)
    b L_2e60
    lbz r0, 0x178(r26)
    cmpwi r0, 0
    bne L_2c84
    li r0, 0
    b L_2cb8
L_2c84:
    lwz r0, 0x174(r26)
    cmpwi r0, 1
    beq L_2cb4
    lwz r3, 0x16c(r26)
    lwz r12, 0(r3)
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    ble L_2cb4
    li r0, 1
    b L_2cb8
L_2cb4:
    li r0, 0
L_2cb8:
    stb r0, 0(r27)
    b L_2e60
    lwz r4, 0(r27)
    mr r3, r26
    lwz r5, 4(r27)
L_2ccc:
    bl onHKBCtrlCode__Q39textinput9inputform4BaseFQ29textinput7HVKCodeUl
    b L_2e60
    mr r3, r26
L_2cd8:
    bl notifyChangeMode__Q39textinput9inputform4BaseFv
    b L_2e60
    mr r3, r26
L_2ce4:
    bl onPressLeftHWKB__Q39textinput9inputform4BaseFv
    b L_2e60
    mr r3, r26
L_2cf0:
    bl onPressRightHWKB__Q39textinput9inputform4BaseFv
    b L_2e60
    lwz r12, 0(r26)
    mr r3, r26
    lwz r12, 0x194(r12)
    mtctr r12
    bctrl 
    b L_2e60
    mr r3, r26
L_2d14:
    bl onPressDownHWKB__Q39textinput9inputform4BaseFv
    b L_2e60
    addi r3, r26, 0x1d8
L_2d20:
    bl KPRClearQueue
    b L_2e60
    b L_2e60
    lwz r12, 0(r5)
    mr r3, r5
    lwz r19, 0(r27)
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl 
    clrlwi r0, r3, 0x10
    cmplw r0, r19
    ble L_2d64
    lwz r3, 0x164(r26)
    lwz r12, 0(r3)
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl 
L_2d64:
    lwz r3, 0x164(r26)
    clrlwi r4, r19, 0x10
    lwz r12, 0(r3)
    lwz r12, 0x38(r12)
    mtctr r12
    bctrl 
    b L_2e60
    lwz r0, 0x1f0(r26)
    cmpwi r0, 8
    bne L_2e4c
    lwz r3, 0x1d4(r26)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lbz r0, 0x3c(r3)
    cmpwi r0, 0
    bne L_2e4c
    lwz r3, 0x1d4(r26)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lbz r0, 0x3d(r3)
    cmpwi r0, 0
    beq L_2e4c
    lwz r3, 0x1d4(r26)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x58(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_2e24
    lwz r3, 0x1d4(r26)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    li r4, 1
    lwz r12, 0x5c(r12)
    mtctr r12
    bctrl 
    b L_2e4c
L_2e24:
    lwz r3, 0x1d4(r26)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    li r4, 0
    lwz r12, 0x5c(r12)
    mtctr r12
    bctrl 
L_2e4c:
    lwz r12, 0(r26)
    mr r3, r26
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
L_2e60:
    addi r11, r1, 0x250
L_2e64:
    bl _restgpr_19
    lwz r0, 0x254(r1)
    mtlr r0
    addi r1, r1, 0x250
    blr 
}

extern "C" asm void onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos() {
    nofralloc
    stwu r1, -0x120(r1)
    mflr r0
    stw r0, 0x124(r1)
    stfd f31, 0x110(r1)
    psq_st f31, 280(r1), 0, 0
    stfd f30, 0x100(r1)
    psq_st f30, 264(r1), 0, 0
    stfd f29, 0xf0(r1)
    psq_st f29, 248(r1), 0, 0
    stfd f28, 0xe0(r1)
    psq_st f28, 232(r1), 0, 0
    stfd f27, 0xd0(r1)
    psq_st f27, 216(r1), 0, 0
    addi r11, r1, 0xd0
L_41dc:
    bl _savegpr_25
    mr r25, r3
    mr r26, r4
    addi r3, r1, 0x30
    li r30, 0
    addi r4, r25, 0x10
L_41f4:
    bl GetTextColor__Q34nw4r2ut10CharWriterCFv
    addi r3, r25, 0x10
L_41fc:
    bl SetupGX__Q34nw4r2ut10CharWriterFv
    lwz r3, 0x164(r25)
    lwz r12, 0(r3)
    lwz r12, 0xbc(r12)
    mtctr r12
    bctrl 
    mr r29, r3
    lwz r3, 0x164(r25)
    lwz r12, 0(r3)
    lwz r12, 0x44(r12)
    mtctr r12
    bctrl 
    lbz r0, 0x178(r25)
    mr r31, r3
    cmpwi r0, 0
    beq L_4460
    lwz r0, 0x174(r25)
    cmpwi r0, 1
    beq L_4460
    lwz r3, 0x16c(r25)
    lwz r12, 0(r3)
    lwz r12, 0xe0(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r25)
    mr r28, r3
    mr r3, r25
    lwz r12, 0x114(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0xb
    bne L_42ac
    lbz r0, 0x1f5(r25)
    cmpwi r0, 0
    beq L_4290
    li r0, 1
    stb r0, 0x1f4(r25)
L_4290:
    lbz r3, 0x1f5(r25)
    lbz r0, 0x1f4(r25)
    or. r0, r3, r0
    bne L_42ac
    lwz r3, 0x16c(r25)
L_42a4:
    bl getCurrentInput__Q39textinput8tistring6WithZiFv
    mr r28, r3
L_42ac:
    cmpwi r28, 0
    beq L_4460
    lwz r0, csZiStringColorLeft__Q29textinput9inputform(r0)
    addi r3, r25, 0x10
    addi r4, r1, 0x2c
    li r27, 0
    stw r0, 0x2c(r1)
L_42c8:
    bl SetTextColor__Q34nw4r2ut10CharWriterFQ34nw4r2ut5Color
    lfs f30, lbl_81694D28(r0)
    b L_4454
L_42d4:
    lbz r3, 0x1f5(r25)
    lbz r0, 0x1f4(r25)
    or. r0, r3, r0
    bne L_4324
    lwz r3, 0x16c(r25)
    lwz r12, 0(r3)
    lwz r12, 0xe4(r12)
    mtctr r12
    bctrl 
    clrlwi r3, r3, 0x10
    clrlwi r0, r27, 0x10
    cmplw r0, r3
    bne L_4324
    addi r3, r25, 0x10
    li r30, 1
L_4310:
    bl GetCursorX__Q34nw4r2ut10CharWriterCFv
    stfs f1, 4(r26)
    addi r3, r25, 0x10
L_431c:
    bl GetCursorY__Q34nw4r2ut10CharWriterCFv
    stfs f1, 8(r26)
L_4324:
    lwz r12, 0(r25)
    mr r3, r25
    lwz r12, 0x114(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0xb
    beq L_43a0
    lwz r3, 0x16c(r25)
    lwz r12, 0(r3)
    lwz r12, 0xe4(r12)
    mtctr r12
    bctrl 
    clrlwi r3, r3, 0x10
    clrlwi r0, r27, 0x10
    cmplw r3, r0
    bgt L_43a0
    lbz r3, 0x1f5(r25)
    lbz r0, 0x1f4(r25)
    or. r0, r3, r0
    beq L_438c
    lwz r0, csZiStringColorRight__Q29textinput9inputform(r0)
    addi r3, r25, 0x10
    addi r4, r1, 0x28
    stw r0, 0x28(r1)
L_4384:
    bl SetTextColor__Q34nw4r2ut10CharWriterFQ34nw4r2ut5Color
    b L_43a0
L_438c:
    lwz r0, csZiStringNonSelectColorRight__Q29textinput9inputform(r0)
    addi r3, r25, 0x10
    addi r4, r1, 0x24
    stw r0, 0x24(r1)
L_439c:
    bl SetTextColor__Q34nw4r2ut10CharWriterFQ34nw4r2ut5Color
L_43a0:
    lhz r0, 0(r28)
    cmplwi r0, 0xfffe
    bne L_43c0
    lwz r0, csZiStringColorLeft__Q29textinput9inputform(r0)
    addi r3, r25, 0x10
    addi r4, r1, 0x20
    stw r0, 0x20(r1)
L_43bc:
    bl SetTextColor__Q34nw4r2ut10CharWriterFQ34nw4r2ut5Color
L_43c0:
    stfs f30, 0x98(r1)
    addi r3, r25, 0x10
    addi r4, r1, 0x98
    stfs f30, 0x9c(r1)
    stfs f30, 0xa0(r1)
    stfs f30, 0xa4(r1)
    lhz r0, 0(r28)
    sth r0, 0xa8(r1)
    lwz r12, 0x5c(r25)
    lwz r12, 0x68(r12)
    mtctr r12
    bctrl 
    lfs f3, 0xa0(r1)
    addi r3, r25, 0x10
    lfs f2, 0x98(r1)
    lfs f1, 0x128(r25)
    lfs f0, 0x120(r25)
    fsubs f31, f3, f2
    fsubs f29, f1, f0
L_440c:
    bl GetCursorX__Q34nw4r2ut10CharWriterCFv
    fadds f0, f1, f31
    fcmpo cr0, f0, f29
    cror eq, gt, eq
    bne L_4434
    lwz r12, 0(r25)
    mr r3, r25
    lwz r12, 0x158(r12)
    mtctr r12
    bctrl 
L_4434:
    lhz r4, 0(r28)
    addi r3, r25, 0x10
L_443c:
    bl Print__Q34nw4r2ut10CharWriterFUs
    lfs f1, 0xb8(r25)
    addi r3, r25, 0x10
L_4448:
    bl MoveCursorX__Q34nw4r2ut10CharWriterFf
    addi r28, r28, 2
    addi r27, r27, 1
L_4454:
    lhz r0, 0(r28)
    cmpwi r0, 0
    bne L_42d4
L_4460:
    lwz r0, 0x160(r25)
    cmpwi r0, 0
    bne L_4654
    clrlwi. r0, r31, 0x10
    beq L_4654
    lfs f0, lbl_81694D28(r0)
    addi r3, r25, 0x10
    sth r31, 0x94(r1)
    addi r4, r1, 0x84
    stfs f0, 0x84(r1)
    stfs f0, 0x88(r1)
    stfs f0, 0x8c(r1)
    stfs f0, 0x90(r1)
    lwz r12, 0x5c(r25)
    lwz r12, 0x68(r12)
    mtctr r12
    bctrl 
    addi r3, r25, 0x10
L_44a8:
    bl GetCursorX__Q34nw4r2ut10CharWriterCFv
    lfs f0, 0x84(r1)
    addi r3, r25, 0x10
    fadds f29, f0, f1
L_44b8:
    bl GetCursorY__Q34nw4r2ut10CharWriterCFv
    lfs f0, 0x88(r1)
    addi r3, r25, 0x10
    fadds f31, f0, f1
L_44c8:
    bl GetCursorX__Q34nw4r2ut10CharWriterCFv
    lfs f0, 0x8c(r1)
    addi r3, r25, 0x10
    fadds f28, f0, f1
L_44d8:
    bl GetCursorY__Q34nw4r2ut10CharWriterCFv
    fmr f30, f1
    addi r3, r25, 0x10
L_44e4:
    bl GetFontHeight__Q34nw4r2ut10CharWriterCFv
    lbz r0, 0x1c8(r25)
    fadds f4, f1, f30
    la r3, lbl_8169739C(r0)
    fmr f1, f29
    stb r0, 3(r3)
    fmr f2, f31
    fmr f3, f28
    lfs f5, lbl_81694D28(r0)
    la r3, lbl_8169739C(r0)
    lfs f6, lbl_81694D38(r0)
L_4510:
    bl drawBox___Q29textinput5debugFffffffR8_GXColor
    addi r3, r25, 0x10
L_4518:
    bl SetupGX__Q34nw4r2ut10CharWriterFv
    lbz r0, 0x1cc(r25)
    addi r3, r25, 0x10
    addi r4, r1, 0x1c
    stb r0, 0x1c(r1)
    lbz r0, 0x1cd(r25)
    stb r0, 0x1d(r1)
    lbz r0, 0x1ce(r25)
    stb r0, 0x1e(r1)
    lbz r0, 0x1cf(r25)
    stb r0, 0x1f(r1)
L_4544:
    bl SetTextColor__Q34nw4r2ut10CharWriterFQ34nw4r2ut5Color
    clrlwi r0, r31, 0x10
    cmpwi r0, 0x3000
    beq L_4564
    bge L_463c
    cmpwi r0, 0x20
    beq L_4564
    b L_463c
L_4564:
    lfs f0, lbl_81694D28(r0)
    lis r26, 1
    addi r0, r26, -0x1fa9
    sth r31, 0x80(r1)
    addi r3, r25, 0x10
    addi r4, r1, 0x70
    stfs f0, 0x70(r1)
    stfs f0, 0x74(r1)
    stfs f0, 0x78(r1)
    stfs f0, 0x7c(r1)
    stfs f0, 0x5c(r1)
    stfs f0, 0x60(r1)
    stfs f0, 0x64(r1)
    stfs f0, 0x68(r1)
    sth r0, 0x6c(r1)
    lwz r12, 0x5c(r25)
    lwz r12, 0x68(r12)
    mtctr r12
    bctrl 
    lwz r12, 0x5c(r25)
    addi r3, r25, 0x10
    addi r4, r1, 0x5c
    lwz r12, 0x68(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r25)
    mr r3, r25
    lfs f3, 0x64(r1)
    lfs f2, 0x5c(r1)
    lfs f1, 0x78(r1)
    lfs f0, 0x70(r1)
    fsubs f29, f3, f2
    lwz r12, 0x188(r12)
    fsubs f30, f1, f0
    mtctr r12
    bctrl 
    fsubs f2, f30, f29
    stw r3, 0x40(r1)
    lfs f1, lbl_81694D3C(r0)
    addi r3, r25, 0x10
    lfs f0, 0x40(r1)
    fmuls f1, f2, f1
    stw r4, 0x44(r1)
    fmuls f28, f0, f1
    fmr f1, f28
L_4618:
    bl MoveCursorX__Q34nw4r2ut10CharWriterFf
    addi r0, r26, -0x1fa9
    addi r3, r25, 0x10
    clrlwi r4, r0, 0x10
L_4628:
    bl Print__Q34nw4r2ut10CharWriterFUs
    fmr f1, f28
    addi r3, r25, 0x10
L_4634:
    bl MoveCursorX__Q34nw4r2ut10CharWriterFf
    b L_4648
L_463c:
    addi r3, r25, 0x10
    clrlwi r4, r31, 0x10
L_4644:
    bl Print__Q34nw4r2ut10CharWriterFUs
L_4648:
    lfs f1, 0xb8(r25)
    addi r3, r25, 0x10
L_4650:
    bl MoveCursorX__Q34nw4r2ut10CharWriterFf
L_4654:
    lwz r0, 0x160(r25)
    cmpwi r0, 0
    beq L_46d4
    lwz r3, 0x164(r25)
    lwz r12, 0(r3)
    lwz r12, 0x44(r12)
    mtctr r12
    bctrl 
    clrlwi. r0, r3, 0x10
    mr r26, r3
    beq L_46d4
    lwz r0, csUnInputedWCharColor__Q29textinput9inputform(r0)
    addi r3, r25, 0x10
    addi r4, r1, 0x18
    stw r0, 0x18(r1)
L_4690:
    bl SetTextColor__Q34nw4r2ut10CharWriterFQ34nw4r2ut5Color
    clrlwi r0, r26, 0x10
    cmplwi r0, 0x20
    bne L_46bc
    lwz r0, csUnInputedWCharColorSpace__Q29textinput9inputform(r0)
    addi r3, r25, 0x10
    addi r4, r1, 0x14
    stw r0, 0x14(r1)
L_46b0:
    bl SetTextColor__Q34nw4r2ut10CharWriterFQ34nw4r2ut5Color
    lis r3, 1
    addi r26, r3, -0x1fa9
L_46bc:
    addi r3, r25, 0x10
    clrlwi r4, r26, 0x10
L_46c4:
    bl Print__Q34nw4r2ut10CharWriterFUs
    lfs f1, 0xb8(r25)
    addi r3, r25, 0x10
L_46d0:
    bl MoveCursorX__Q34nw4r2ut10CharWriterFf
L_46d4:
    lfs f30, lbl_81694D28(r0)
    la r26, lbl_81697398(r0)
    b L_48a4
L_46e0:
    lbz r0, 0x178(r25)
    cmpwi r0, 0
    beq L_46f8
    mr r3, r27
L_46f0:
    bl HankakuToZenkaku__Q29textinput4utilFw
    mr r27, r3
L_46f8:
    stfs f30, 0x48(r1)
    addi r3, r25, 0x10
    addi r4, r1, 0x48
    stfs f30, 0x4c(r1)
    stfs f30, 0x50(r1)
    stfs f30, 0x54(r1)
    sth r27, 0x58(r1)
    lwz r12, 0x5c(r25)
    lwz r12, 0x68(r12)
    mtctr r12
    bctrl 
    lwz r0, 0x1f0(r25)
    cmpwi r0, 0
    bne L_47dc
    addi r3, r25, 0x10
L_4734:
    bl GetCursorX__Q34nw4r2ut10CharWriterCFv
    lfs f0, 0x48(r1)
    addi r3, r25, 0x10
    fadds f28, f0, f1
L_4744:
    bl GetCursorY__Q34nw4r2ut10CharWriterCFv
    lfs f0, 0x4c(r1)
    addi r3, r25, 0x10
    fadds f29, f0, f1
L_4754:
    bl GetCursorX__Q34nw4r2ut10CharWriterCFv
    lfs f0, 0x50(r1)
    addi r3, r25, 0x10
    fadds f27, f0, f1
L_4764:
    bl GetCursorY__Q34nw4r2ut10CharWriterCFv
    fmr f31, f1
    addi r3, r25, 0x10
L_4770:
    bl GetFontHeight__Q34nw4r2ut10CharWriterCFv
    lbz r0, 0x1c8(r25)
    fadds f4, f1, f31
    fmr f1, f28
    lfs f5, lbl_81694D28(r0)
    fmr f2, f29
    stb r0, 3(r26)
    fmr f3, f27
    lfs f6, lbl_81694D38(r0)
    la r3, lbl_81697398(r0)
L_4798:
    bl drawBox___Q29textinput5debugFffffffR8_GXColor
    addi r3, r25, 0x10
L_47a0:
    bl SetupGX__Q34nw4r2ut10CharWriterFv
    lbz r5, 0x1c8(r25)
    addi r3, r25, 0x10
    lbz r0, 0x1cc(r25)
    addi r4, r1, 0x10
    stb r5, 0x1cf(r25)
    stb r0, 0x10(r1)
    lbz r0, 0x1cd(r25)
    stb r0, 0x11(r1)
    lbz r0, 0x1ce(r25)
    stb r0, 0x12(r1)
    lbz r0, 0x1cf(r25)
    stb r0, 0x13(r1)
L_47d4:
    bl SetTextColor__Q34nw4r2ut10CharWriterFQ34nw4r2ut5Color
    b L_4888
L_47dc:
    cmpwi r0, 9
    bne L_4888
    addi r3, r25, 0x10
L_47e8:
    bl SetupGX__Q34nw4r2ut10CharWriterFv
    lbz r0, 0x1c8(r25)
    addi r3, r25, 0x10
    addi r4, r1, 0xc
    stb r0, 0x1cf(r25)
    lwz r0, csZiStringColorLeft__Q29textinput9inputform(r0)
    stw r0, 0xc(r1)
L_4804:
    bl SetTextColor__Q34nw4r2ut10CharWriterFQ34nw4r2ut5Color
    lwz r12, 0(r25)
    mr r3, r25
    addi r4, r1, 0x48
    lwz r12, 0x160(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_4888
    lwz r4, 0xb0(r25)
    addi r3, r25, 0x10
    addi r0, r4, 1
    stw r0, 0xb0(r25)
    lwz r12, 0x5c(r25)
    lwz r12, 0x28(r12)
    mtctr r12
    bctrl 
    fmr f31, f1
    addi r3, r25, 0x10
L_4850:
    bl GetCursorY__Q34nw4r2ut10CharWriterCFv
    fadds f1, f1, f31
    addi r3, r25, 0x10
L_485c:
    bl SetCursorY__Q34nw4r2ut10CharWriterFf
    lwz r12, 0(r25)
    mr r3, r25
    lwz r12, 0x188(r12)
    mtctr r12
    bctrl 
    stw r3, 0x38(r1)
    addi r3, r25, 0x10
    stw r4, 0x3c(r1)
    lfs f1, 0x38(r1)
L_4884:
    bl SetCursorX__Q34nw4r2ut10CharWriterFf
L_4888:
    addi r3, r25, 0x10
    clrlwi r4, r27, 0x10
L_4890:
    bl Print__Q34nw4r2ut10CharWriterFUs
    lfs f1, 0xb8(r25)
    addi r3, r25, 0x10
L_489c:
    bl MoveCursorX__Q34nw4r2ut10CharWriterFf
    addi r29, r29, 2
L_48a4:
    lhz r27, 0(r29)
    cmpwi r27, 0
    bne L_46e0
    lwz r0, 0x30(r1)
    addi r3, r25, 0x10
    addi r4, r1, 8
    stw r0, 8(r1)
L_48c0:
    bl SetTextColor__Q34nw4r2ut10CharWriterFQ34nw4r2ut5Color
    mr r3, r30
    psq_l f31, 280(r1), 0, 0
    lfd f31, 0x110(r1)
    psq_l f30, 264(r1), 0, 0
    lfd f30, 0x100(r1)
    psq_l f29, 248(r1), 0, 0
    lfd f29, 0xf0(r1)
    psq_l f28, 232(r1), 0, 0
    lfd f28, 0xe0(r1)
    psq_l f27, 216(r1), 0, 0
    lfd f27, 0xd0(r1)
    addi r11, r1, 0xd0
L_48f4:
    bl _restgpr_25
    lwz r0, 0x124(r1)
    mtlr r0
    addi r1, r1, 0x120
    blr 
}

extern "C" asm void calcCursorPos__Q39textinput9inputform4BaseFff() {
    nofralloc
    stwu r1, -0xf0(r1)
    mflr r0
    stw r0, 0xf4(r1)
    stfd f31, 0xe0(r1)
    psq_st f31, 232(r1), 0, 0
    stfd f30, 0xd0(r1)
    psq_st f30, 216(r1), 0, 0
    stfd f29, 0xc0(r1)
    psq_st f29, 200(r1), 0, 0
    stfd f28, 0xb0(r1)
    psq_st f28, 184(r1), 0, 0
    stfd f27, 0xa0(r1)
    psq_st f27, 168(r1), 0, 0
    stfd f26, 0x90(r1)
    psq_st f26, 152(r1), 0, 0
    stfd f25, 0x80(r1)
    psq_st f25, 136(r1), 0, 0
    stfd f24, 0x70(r1)
    psq_st f24, 120(r1), 0, 0
    stfd f23, 0x60(r1)
    psq_st f23, 104(r1), 0, 0
    fmr f24, f1
    stw r31, 0x5c(r1)
    stw r30, 0x58(r1)
    stw r29, 0x54(r1)
    mr r29, r3
    lfs f0, 0x188(r3)
    lwz r3, 0x164(r3)
    fsubs f25, f2, f0
    lwz r12, 0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl 
    lhz r0, 0(r3)
    mr r31, r3
    cmpwi r0, 0
    bne L_4b44
    li r3, 0
    b L_4f5c
L_4b44:
    lwz r12, 0(r29)
    mr r3, r29
    lwz r12, 0x188(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r29)
    lfs f27, lbl_81694D28(r0)
    stw r3, 0x28(r1)
    mr r3, r29
    lwz r12, 0x188(r12)
    fmr f26, f27
    stw r4, 0x2c(r1)
    lfs f28, 0x28(r1)
    mtctr r12
    bctrl 
    li r30, 0
    stw r3, 0x30(r1)
    lfs f29, lbl_81694D28(r0)
    stw r4, 0x34(r1)
    lfs f30, 0x30(r1)
    stw r30, 0x1b4(r29)
    lfs f31, 0x34(r1)
    stw r4, 0x24(r1)
    stw r3, 0x20(r1)
    stb r30, mbHyphen__Q29textinput9inputform(r0)
    b L_4f04
L_4bac:
    stfs f29, 0x38(r1)
    addi r3, r29, 0x10
    addi r4, r1, 0x38
    stfs f29, 0x3c(r1)
    stfs f29, 0x40(r1)
    stfs f29, 0x44(r1)
    lhz r0, 0(r31)
    sth r0, 0x48(r1)
    lwz r12, 0x5c(r29)
    lwz r12, 0x68(r12)
    mtctr r12
    bctrl 
    lfs f1, 0x44(r1)
    lfs f0, 0x3c(r1)
    lwz r3, 0x164(r29)
    fsubs f0, f1, f0
    lfs f2, 0x40(r1)
    lfs f1, 0x38(r1)
    lwz r12, 0(r3)
    fmuls f0, f31, f0
    fsubs f1, f2, f1
    lwz r12, 0x3c(r12)
    fadds f26, f27, f0
    fmuls f0, f30, f1
    fadds f23, f28, f0
    mtctr r12
    bctrl 
    lwz r12, 0(r29)
    mr r4, r3
    fmr f1, f28
    mr r3, r29
    lwz r12, 0x170(r12)
    mr r5, r30
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_4ce0
    fcmpo cr0, f25, f27
    cror eq, gt, eq
    bne L_4c70
    fcmpo cr0, f25, f26
    cror eq, lt, eq
    bne L_4c70
    cmpwi r30, 0
    beq L_4c68
    addi r3, r30, -1
    b L_4f5c
L_4c68:
    mr r3, r30
    b L_4f5c
L_4c70:
    lwz r12, 0x5c(r29)
    addi r3, r29, 0x10
    lwz r12, 0x28(r12)
    mtctr r12
    bctrl 
    lfs f0, 0x34(r1)
    mr r3, r29
    lwz r12, 0(r29)
    fmuls f0, f0, f1
    lwz r12, 0x188(r12)
    fadds f27, f27, f0
    mtctr r12
    bctrl 
    lfs f1, 0x44(r1)
    lfs f0, 0x3c(r1)
    stw r3, 0x18(r1)
    fsubs f1, f1, f0
    lfs f0, 0x34(r1)
    lfs f3, 0x40(r1)
    lfs f2, 0x38(r1)
    fmuls f0, f0, f1
    lfs f1, 0x30(r1)
    fsubs f2, f3, f2
    lfs f28, 0x18(r1)
    stw r4, 0x1c(r1)
    fadds f26, f27, f0
    fmuls f0, f1, f2
    fadds f23, f28, f0
L_4ce0:
    lfs f1, 0x128(r29)
    lfs f0, 0x120(r29)
    fsubs f0, f1, f0
    fmuls f0, f30, f0
    fcmpo cr0, f23, f0
    cror eq, gt, eq
    bne L_4d8c
    fcmpo cr0, f25, f27
    cror eq, gt, eq
    bne L_4d1c
    fcmpo cr0, f25, f26
    cror eq, lt, eq
    bne L_4d1c
    mr r3, r30
    b L_4f5c
L_4d1c:
    lwz r12, 0x5c(r29)
    addi r3, r29, 0x10
    lwz r12, 0x28(r12)
    mtctr r12
    bctrl 
    lfs f0, 0x34(r1)
    mr r3, r29
    lwz r12, 0(r29)
    fmuls f0, f0, f1
    lwz r12, 0x188(r12)
    fadds f27, f27, f0
    mtctr r12
    bctrl 
    lfs f1, 0x44(r1)
    lfs f0, 0x3c(r1)
    stw r3, 0x10(r1)
    fsubs f1, f1, f0
    lfs f0, 0x34(r1)
    lfs f3, 0x40(r1)
    lfs f2, 0x38(r1)
    fmuls f0, f0, f1
    lfs f1, 0x30(r1)
    fsubs f2, f3, f2
    lfs f28, 0x10(r1)
    stw r4, 0x14(r1)
    fadds f26, f27, f0
    fmuls f0, f1, f2
    fadds f23, f28, f0
L_4d8c:
    lfs f0, 0x38(r1)
    fcmpo cr0, f24, f0
    cror eq, lt, eq
    bne L_4dbc
    fcmpo cr0, f25, f27
    cror eq, gt, eq
    bne L_4dbc
    fcmpo cr0, f25, f26
    cror eq, lt, eq
    bne L_4dbc
    mr r3, r30
    b L_4f5c
L_4dbc:
    lhz r0, 0(r31)
    cmplwi r0, 0xa
    bne L_4e6c
    fcmpo cr0, f25, f27
    cror eq, gt, eq
    bne L_4de8
    fcmpo cr0, f25, f26
    cror eq, lt, eq
    bne L_4de8
    mr r3, r30
    b L_4f5c
L_4de8:
    lwz r12, 0x5c(r29)
    addi r3, r29, 0x10
    lwz r12, 0x28(r12)
    mtctr r12
    bctrl 
    lfs f0, 0x34(r1)
    mr r3, r29
    lwz r12, 0(r29)
    fmuls f0, f0, f1
    lwz r12, 0x188(r12)
    fadds f27, f27, f0
    mtctr r12
    bctrl 
    lfs f1, 0x44(r1)
    lfs f0, 0x3c(r1)
    lhz r0, 2(r31)
    fsubs f1, f1, f0
    lfs f0, 0x34(r1)
    stw r3, 8(r1)
    cmpwi r0, 0
    fmuls f0, f0, f1
    stw r4, 0xc(r1)
    lfs f28, 8(r1)
    fadds f26, f27, f0
    bne L_4ed4
    fcmpo cr0, f25, f27
    cror eq, gt, eq
    bne L_4ed4
    fcmpo cr0, f25, f26
    cror eq, lt, eq
    bne L_4ed4
    addi r3, r30, 1
    b L_4f5c
L_4e6c:
    fcmpo cr0, f24, f28
    cror eq, gt, eq
    bne L_4ebc
    fcmpo cr0, f24, f23
    bge L_4ebc
    fcmpo cr0, f25, f27
    cror eq, gt, eq
    bne L_4ebc
    fcmpo cr0, f25, f26
    bge L_4ebc
    fsubs f1, f23, f28
    lfs f0, lbl_81694D3C(r0)
    fmuls f0, f1, f0
    fadds f0, f28, f0
    fcmpo cr0, f0, f24
    ble L_4eb4
    mr r3, r30
    b L_4f5c
L_4eb4:
    addi r3, r30, 1
    b L_4f5c
L_4ebc:
    lfs f2, 0x40(r1)
    lfs f1, 0x38(r1)
    lfs f0, 0x30(r1)
    fsubs f1, f2, f1
    fmuls f0, f0, f1
    fadds f28, f28, f0
L_4ed4:
    lhzu r0, 2(r31)
    addi r30, r30, 1
    cmpwi r0, 0
    bne L_4f04
    fcmpo cr0, f25, f27
    cror eq, gt, eq
    bne L_4f04
    fcmpo cr0, f25, f26
    cror eq, lt, eq
    bne L_4f04
    mr r3, r30
    b L_4f5c
L_4f04:
    lhz r0, 0(r31)
    cmpwi r0, 0
    bne L_4bac
    fsubs f1, f26, f27
    lfs f0, lbl_81694D3C(r0)
    fmuls f0, f1, f0
    fadds f0, f27, f0
    fcmpo cr0, f0, f25
    cror eq, lt, eq
    bne L_4f4c
    lfs f2, lbl_81694D38(r0)
    fmr f1, f24
    lfs f0, 0x188(r29)
    mr r3, r29
    fadds f2, f2, f27
    fadds f2, f2, f0
L_4f44:
    bl calcCursorPos__Q39textinput9inputform4BaseFff
    b L_4f5c
L_4f4c:
    fmr f1, f24
    lfs f2, lbl_81694D38(r0)
    mr r3, r29
L_4f58:
    bl calcCursorPos__Q39textinput9inputform4BaseFff
L_4f5c:
    psq_l f31, 232(r1), 0, 0
    lfd f31, 0xe0(r1)
    psq_l f30, 216(r1), 0, 0
    lfd f30, 0xd0(r1)
    psq_l f29, 200(r1), 0, 0
    lfd f29, 0xc0(r1)
    psq_l f28, 184(r1), 0, 0
    lfd f28, 0xb0(r1)
    psq_l f27, 168(r1), 0, 0
    lfd f27, 0xa0(r1)
    psq_l f26, 152(r1), 0, 0
    lfd f26, 0x90(r1)
    psq_l f25, 136(r1), 0, 0
    lfd f25, 0x80(r1)
    psq_l f24, 120(r1), 0, 0
    lfd f24, 0x70(r1)
    psq_l f23, 104(r1), 0, 0
    lfd f23, 0x60(r1)
    lwz r31, 0x5c(r1)
    lwz r30, 0x58(r1)
    lwz r0, 0xf4(r1)
    lwz r29, 0x54(r1)
    mtlr r0
    addi r1, r1, 0xf0
    blr 
}

extern "C" asm void confirmInputting___Q39textinput9inputform4BaseFwbUsbPv() {
    nofralloc
    stwu r1, -0xb0(r1)
    mflr r0
    stw r0, 0xb4(r1)
    addi r11, r1, 0xb0
L_58f8:
    bl _savegpr_25
    mr r25, r4
    mr r31, r3
    mr r26, r5
    mr r27, r6
    mr r28, r7
    mr r29, r8
    li r4, 1
L_5918:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    cmpwi r25, 0
    mr r30, r3
    beq L_5e38
    lbz r0, 0x178(r31)
    cmpwi r0, 0
    beq L_5a80
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0x114(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0xb
    bne L_5a80
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x4c(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_5a80
    mr r3, r25
L_5980:
    bl isAlphabet__Q29textinput4utilFw
    cmpwi r3, 0
    bne L_5a80
    cmplwi r25, 0x31
    blt L_599c
    cmplwi r25, 0x35
    ble L_5a80
L_599c:
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r31)
    mr r4, r25
    lwz r12, 0(r3)
    lwz r12, 0x50(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r0, 0x1f0(r31)
    cmpwi r0, 8
    bne L_5a4c
    lbz r0, 0x178(r31)
    cmpwi r0, 0
    bne L_59fc
    li r0, 0
    b L_5a30
L_59fc:
    lwz r0, 0x174(r31)
    cmpwi r0, 1
    beq L_5a2c
    lwz r3, 0x16c(r31)
    lwz r12, 0(r3)
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    ble L_5a2c
    li r0, 1
    b L_5a30
L_5a2c:
    li r0, 0
L_5a30:
    cmpwi r0, 0
    beq L_5a4c
    lwz r3, 0x16c(r31)
    li r4, 0
L_5a40:
    bl setCurrentWord__Q39textinput8tistring6WithZiFPCw
    lwz r3, 0x16c(r31)
L_5a48:
    bl update__Q39textinput8tistring6WithZiFv
L_5a4c:
    lwz r0, 0x1f0(r31)
    cmpwi r0, 8
    bne L_5a74
    lwz r3, 0x16c(r31)
L_5a5c:
    bl clearCandidates__Q39textinput8tistring6WithZiFv
    li r0, 0
    lwz r3, 0x16c(r31)
    stb r0, 0x1f4(r31)
L_5a6c:
    bl update__Q39textinput8tistring6WithZiFv
    b L_5e38
L_5a74:
    mr r3, r31
L_5a78:
    bl confirmInput___Q39textinput9inputform4BaseFv
    b L_5e38
L_5a80:
    cmpwi r26, 0
    beq L_5b3c
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r31)
    mr r4, r25
    lwz r12, 0(r3)
    lwz r12, 0x50(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r0, 0x1f0(r31)
    cmpwi r0, 8
    bne L_5e38
    lbz r0, 0x178(r31)
    cmpwi r0, 0
    bne L_5ae8
    li r0, 0
    b L_5b1c
L_5ae8:
    lwz r0, 0x174(r31)
    cmpwi r0, 1
    beq L_5b18
    lwz r3, 0x16c(r31)
    lwz r12, 0(r3)
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    ble L_5b18
    li r0, 1
    b L_5b1c
L_5b18:
    li r0, 0
L_5b1c:
    cmpwi r0, 0
    beq L_5e38
    lwz r3, 0x16c(r31)
    li r4, 0
L_5b2c:
    bl setCurrentWord__Q39textinput8tistring6WithZiFPCw
    lwz r3, 0x16c(r31)
L_5b34:
    bl update__Q39textinput8tistring6WithZiFv
    b L_5e38
L_5b3c:
    lwz r3, 0x16c(r31)
    cmplw r30, r3
    bne L_5c2c
    lwz r12, 0(r3)
    lwz r12, 0xe4(r12)
    mtctr r12
    bctrl 
    clrlwi. r0, r3, 0x10
    bne L_5b90
    lwz r3, 0x16c(r31)
    mr r4, r27
    lwz r12, 0(r3)
    lwz r12, 0xf4(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x16c(r31)
    mr r4, r29
    lwz r12, 0(r3)
    lwz r12, 0xfc(r12)
    mtctr r12
    bctrl 
L_5b90:
    lwz r3, 0x16c(r31)
    lwz r12, 0(r3)
    lwz r12, 0xe4(r12)
    mtctr r12
    bctrl 
    clrlwi r0, r3, 0x10
    cmplwi r0, 0x20
    blt L_5c98
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 6
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x16c(r31)
    mr r4, r27
    lwz r12, 0(r3)
    lwz r12, 0xf4(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x16c(r31)
    mr r4, r25
    lwz r12, 0(r3)
    lwz r12, 0x50(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 9
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    b L_5e38
L_5c2c:
    lwz r3, 0x168(r31)
    cmplw cr1, r30, r3
    bne L_5c5c
    cmpwi r28, 0
    beq L_5c98
    lwz r12, 0(r3)
    lwz r12, 0x48(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_5c98
    b L_5e38
L_5c5c:
    lbz r0, 0x178(r31)
    cmpwi r0, 0
    beq L_5c98
    lwz r0, 0x174(r31)
    cmpwi r0, 1
    bne L_5c98
    beq L_5c98
    cmplwi r25, 0x20
    bne L_5c98
    lwz r12, 0(r3)
    li r25, 0x3000
    li r4, 0
    lwz r12, 0x40(r12)
    mtctr r12
    bctrl 
L_5c98:
    lwz r3, 0x164(r31)
    cmplw r30, r3
    bne L_5d54
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r31)
    mr r4, r25
    lwz r12, 0(r3)
    lwz r12, 0x50(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r0, 0x1f0(r31)
    cmpwi r0, 8
    bne L_5e20
    lbz r0, 0x178(r31)
    cmpwi r0, 0
    bne L_5d00
    li r0, 0
    b L_5d34
L_5d00:
    lwz r0, 0x174(r31)
    cmpwi r0, 1
    beq L_5d30
    lwz r3, 0x16c(r31)
    lwz r12, 0(r3)
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    ble L_5d30
    li r0, 1
    b L_5d34
L_5d30:
    li r0, 0
L_5d34:
    cmpwi r0, 0
    beq L_5e20
    lwz r3, 0x16c(r31)
    li r4, 0
L_5d44:
    bl setCurrentWord__Q39textinput8tistring6WithZiFPCw
    lwz r3, 0x16c(r31)
L_5d4c:
    bl update__Q39textinput8tistring6WithZiFv
    b L_5e20
L_5d54:
    lwz r12, 0(r30)
    mr r3, r30
    mr r4, r25
    lwz r12, 0x50(r12)
    mtctr r12
    bctrl 
    lwz r0, 0x1f0(r31)
    cmpwi r0, 9
    bne L_5e20
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
    beq L_5e20
    lwz r3, 0x16c(r31)
    addi r5, r1, 8
    li r4, 0
    lwz r12, 0(r3)
    lwz r12, 0xdc(r12)
    mtctr r12
    bctrl 
    addi r3, r1, 8
L_5dc4:
    bl wcslen
    cmplwi r3, 2
    blt L_5e20
    li r0, 0
    sth r0, 0xa(r1)
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r31)
    addi r4, r1, 8
    lwz r12, 0(r3)
    lwz r12, 0x54(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x16c(r31)
L_5e1c:
    bl partialConfirmForKR__Q39textinput8tistring6WithZiFv
L_5e20:
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 0xa
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
L_5e38:
    addi r11, r1, 0xb0
L_5e3c:
    bl _restgpr_25
    lwz r0, 0xb4(r1)
    mtlr r0
    addi r1, r1, 0xb0
    blr 
}

extern "C" asm void onHKBCtrlCode__Q39textinput9inputform4BaseFQ29textinput7HVKCodeUl() {
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
    li r4, 0
L_65a4:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    cmplwi r29, 0x24
    bgt L_6b3c
    lis r4, jumptable_8165CB4C@l
    slwi r0, r29, 2
    addi r4, r4, jumptable_8165CB4C@ha
    lwzx r4, r4, r0
    mtctr r4
    bctr 
    lwz r0, 0x174(r31)
    cmpwi r0, 1
    bne L_6b3c
    mr r3, r31
    li r4, 0
L_65dc:
    bl toggleAtokMode___Q39textinput9inputform4BaseFUc
    b L_6b3c
    lwz r0, 0x174(r31)
    cmpwi r0, 1
    bne L_66ac
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x58(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 1
    bne L_6648
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    li r4, 2
    lwz r12, 0x5c(r12)
    mtctr r12
    bctrl 
    b L_669c
L_6648:
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x58(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 2
    bne L_669c
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    li r4, 1
    lwz r12, 0x5c(r12)
    mtctr r12
    bctrl 
L_669c:
    mr r3, r31
    li r4, 1
L_66a4:
    bl toggleAtokMode___Q39textinput9inputform4BaseFUc
    b L_6b3c
L_66ac:
    lwz r0, 0x1f0(r31)
    cmpwi r0, 9
    bne L_6b3c
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lbz r0, 0x3c(r3)
    cmpwi r0, 0
    bne L_6b3c
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lbz r0, 0x3d(r3)
    cmpwi r0, 0
    beq L_6b3c
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
    bne L_6750
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    li r4, 1
    lwz r12, 0x5c(r12)
    mtctr r12
    bctrl 
    b L_6b3c
L_6750:
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    li r4, 0
    lwz r12, 0x5c(r12)
    mtctr r12
    bctrl 
    b L_6b3c
    lwz r0, 0x174(r31)
    cmpwi r0, 1
    bne L_6b3c
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
    bne L_67fc
    lbz r0, 0x178(r31)
    cmpwi r0, 0
    bne L_67fc
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lbz r0, 0x3c(r3)
    cmpwi r0, 0
    bne L_6b3c
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 6
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    b L_6b3c
L_67fc:
    mr r3, r31
    li r4, 2
L_6804:
    bl toggleAtokMode___Q39textinput9inputform4BaseFUc
    b L_6b3c
    lwz r4, 0x174(r31)
    cmpwi r4, 1
    bne L_6828
    mr r3, r31
    li r4, 0
L_6820:
    bl toggleAtokMode___Q39textinput9inputform4BaseFUc
    b L_6b3c
L_6828:
    lwz r3, 0x1f0(r31)
    addi r0, r3, -8
    cmplwi r0, 1
    bgt L_68fc
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lbz r0, 0x3c(r3)
    cmpwi r0, 0
    bne L_6b3c
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lbz r0, 0x3d(r3)
    cmpwi r0, 0
    beq L_6b3c
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
    bne L_68d0
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    li r4, 1
    lwz r12, 0x5c(r12)
    mtctr r12
    bctrl 
    b L_6b3c
L_68d0:
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    li r4, 0
    lwz r12, 0x5c(r12)
    mtctr r12
    bctrl 
    b L_6b3c
L_68fc:
    cmpwi r4, 0
    beq L_6b3c
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x10c(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_6b3c
    lbz r0, 0x178(r31)
    lwz r3, 0x1d4(r31)
    cntlzw r0, r0
    srwi r4, r0, 5
L_6940:
    bl startPredictTurnOn__Q29textinput7ManagerFb
    b L_6b3c
    lwz r0, 0x168(r31)
    cmplw r3, r0
    bne L_6b3c
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    b L_6b3c
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 7
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 0x27
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
    b L_6b3c
    mr r3, r31
    mr r4, r30
L_69b0:
    bl onSpaceKeyHWKB__Q39textinput9inputform4BaseFUl
    b L_6b3c
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 0x2c
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
    b L_6b3c
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 0x2d
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
    b L_6b3c
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 0x2a
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
    b L_6b3c
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 0x2b
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
    b L_6b3c
    lwz r0, 0x174(r31)
    cmpwi r0, 1
    bne L_6b3c
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x58(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 1
    bne L_6a9c
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    li r4, 2
    lwz r12, 0x5c(r12)
    mtctr r12
    bctrl 
    b L_6b3c
L_6a9c:
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x58(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 2
    bne L_6af4
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    li r4, 1
    lwz r12, 0x5c(r12)
    mtctr r12
    bctrl 
    b L_6b3c
L_6af4:
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lbz r0, 0x3c(r3)
    cmpwi r0, 0
    bne L_6b3c
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    li r4, 1
    lwz r12, 0x5c(r12)
    mtctr r12
    bctrl 
L_6b3c:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr 
}

extern "C" asm void onPressDownHWKB__Q39textinput9inputform4BaseFv() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    li r4, 0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
L_7b5c:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lis r4, sInstance__Q39textinput5input10HKBManager@l
    mr r29, r3
    addi r3, r4, sInstance__Q39textinput5input10HKBManager@ha
L_7b6c:
    bl GetModifierState__Q39textinput5input10HKBManagerCFv
    lwz r0, 0x164(r31)
    mr r30, r3
    cmplw r29, r0
    bne L_7d38
    lwz r3, 0x1d4(r31)
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
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    lwz r0, 0x1f0(r31)
    cmpwi r0, 9
    bne L_7ca8
    mr r3, r31
    li r4, 0
L_7bdc:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r12, 0(r3)
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_7ca8
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r31)
    li r4, 0xa
    lwz r12, 0(r3)
    lwz r12, 0x50(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r0, 0x1f0(r31)
    cmpwi r0, 8
    bne L_7ca8
    lbz r0, 0x178(r31)
    cmpwi r0, 0
    bne L_7c58
    li r0, 0
    b L_7c8c
L_7c58:
    lwz r0, 0x174(r31)
    cmpwi r0, 1
    beq L_7c88
    lwz r3, 0x16c(r31)
    lwz r12, 0(r3)
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    ble L_7c88
    li r0, 1
    b L_7c8c
L_7c88:
    li r0, 0
L_7c8c:
    cmpwi r0, 0
    beq L_7ca8
    lwz r3, 0x16c(r31)
    li r4, 0
L_7c9c:
    bl setCurrentWord__Q39textinput8tistring6WithZiFPCw
    lwz r3, 0x16c(r31)
L_7ca4:
    bl update__Q39textinput8tistring6WithZiFv
L_7ca8:
    lwz r12, 0(r29)
    mr r3, r29
    lwz r12, 0x48(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_7f58
    lwz r12, 0(r29)
    mr r3, r29
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_7ce4
    b L_7f58
L_7ce4:
    lwz r3, 0x168(r31)
    lwz r12, 0(r3)
    lwz r12, 0x44(r12)
    mtctr r12
    bctrl 
    clrlwi r0, r3, 0x10
    cmplwi r0, 0x20
    beq L_7f58
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0x190(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 0x2f
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
    b L_7f58
L_7d38:
    lwz r3, 0x168(r31)
    cmplw r3, r29
    bne L_7f50
    lwz r12, 0(r3)
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_7d70
    lwz r3, 0x168(r31)
    lwz r12, 0(r3)
    lwz r12, 0xc4(r12)
    mtctr r12
    bctrl 
L_7d70:
    lwz r3, 0x168(r31)
    lwz r12, 0(r3)
    lwz r12, 0xdc(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_7ec4
    rlwinm. r0, r30, 0, 0x1e, 0x1e
    beq L_7dd8
    lwz r3, 0x168(r31)
    lwz r12, 0(r3)
    lwz r12, 0x138(r12)
    mtctr r12
    bctrl 
    extsh r4, r3
    lwz r3, 0x168(r31)
    lwz r12, 0(r3)
    lwz r12, 0xec(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    b L_7f58
L_7dd8:
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x104(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_7f58
    mr r3, r31
    li r4, 0
L_7e0c:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r0, 0x168(r31)
    cmplw r3, r0
    bne L_7ea8
    mr r3, r0
    lwz r12, 0(r3)
    lwz r12, 0x138(r12)
    mtctr r12
    bctrl 
    addi r0, r3, 1
    lwz r3, 0x168(r31)
    extsh r30, r0
    lwz r12, 0(r3)
    lwz r12, 0xe4(r12)
    mtctr r12
    bctrl 
    cmpw r30, r3
    blt L_7e5c
    li r30, 0
    b L_7e80
L_7e5c:
    cmpwi r30, 0
    bge L_7e80
    lwz r3, 0x168(r31)
    lwz r12, 0(r3)
    lwz r12, 0xe4(r12)
    mtctr r12
    bctrl 
    addi r0, r3, -1
    extsh r30, r0
L_7e80:
    mr r3, r31
    mr r4, r30
L_7e88:
    bl moveCandidateToIdx__Q39textinput9inputform4BaseFl
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    addi r3, r3, 0xe4
L_7ea4:
    bl ScrollToSelectedText__Q39textinput12candidatebox10UITextAreaFv
L_7ea8:
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 6
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    b L_7f58
L_7ec4:
    lwz r3, 0x168(r31)
    lwz r12, 0(r3)
    lwz r12, 0x124(r12)
    mtctr r12
    bctrl 
    clrlwi. r0, r3, 0x10
    beq L_7f58
    lwz r3, 0x168(r31)
    lwz r12, 0(r3)
    lwz r12, 0x118(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    mr r3, r31
    li r4, 0
L_7f10:
    bl moveCandidateToIdx__Q39textinput9inputform4BaseFl
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    addi r3, r3, 0xe4
L_7f2c:
    bl ScrollToSelectedText__Q39textinput12candidatebox10UITextAreaFv
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 0x2f
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
    b L_7f58
L_7f50:
    lwz r0, 0x16c(r31)
    cmplw r0, r29
L_7f58:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr 
}

extern "C" asm void onPressLeftHWKB__Q39textinput9inputform4BaseFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    stw r30, 8(r1)
    mr r30, r3
L_7f90:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lis r4, sInstance__Q39textinput5input10HKBManager@l
    mr r31, r3
    addi r3, r4, sInstance__Q39textinput5input10HKBManager@ha
L_7fa0:
    bl GetModifierState__Q39textinput5input10HKBManagerCFv
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r0, 0x164(r30)
    cmplw r31, r0
    bne L_8190
    lwz r0, 0x1f0(r30)
    cmpwi r0, 9
    bne L_80b8
    mr r3, r30
    li r4, 0
L_7fd8:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r12, 0(r3)
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_80a4
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
    bne L_80a4
    lbz r0, 0x178(r30)
    cmpwi r0, 0
    bne L_8054
    li r0, 0
    b L_8088
L_8054:
    lwz r0, 0x174(r30)
    cmpwi r0, 1
    beq L_8084
    lwz r3, 0x16c(r30)
    lwz r12, 0(r3)
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    ble L_8084
    li r0, 1
    b L_8088
L_8084:
    li r0, 0
L_8088:
    cmpwi r0, 0
    beq L_80a4
    lwz r3, 0x16c(r30)
    li r4, 0
L_8098:
    bl setCurrentWord__Q39textinput8tistring6WithZiFPCw
    lwz r3, 0x16c(r30)
L_80a0:
    bl update__Q39textinput8tistring6WithZiFv
L_80a4:
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
L_80b8:
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0x48(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_837c
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_80f4
    b L_837c
L_80f4:
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
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0x68(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_8174
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 5
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    b L_8374
L_8174:
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 6
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    b L_8374
L_8190:
    lwz r0, 0x168(r30)
    cmplw r31, r0
    bne L_82a8
    lwz r3, 0x1d4(r30)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x104(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_837c
    lwz r3, 0x168(r30)
    lwz r12, 0(r3)
    lwz r12, 0xe4(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    ble L_837c
    lwz r3, 0x168(r30)
    lwz r12, 0(r3)
    lwz r12, 0xdc(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_8218
    lwz r12, 0(r30)
    mr r3, r30
    lwz r12, 0x19c(r12)
    mtctr r12
    bctrl 
    b L_837c
L_8218:
    lwz r3, 0x168(r30)
    lwz r12, 0(r3)
    lwz r12, 0xf8(r12)
    mtctr r12
    bctrl 
    addi r0, r3, -1
    extsh r4, r0
    cmpwi r4, -1
    bge L_8244
    li r4, 0
    b L_8268
L_8244:
    cmpwi r4, 0
    bge L_8268
    lwz r3, 0x168(r30)
    lwz r12, 0(r3)
    lwz r12, 0xe4(r12)
    mtctr r12
    bctrl 
    addi r0, r3, -1
    extsh r4, r0
L_8268:
    mr r3, r30
L_826c:
    bl moveCandidateToIdx__Q39textinput9inputform4BaseFl
    lwz r3, 0x1d4(r30)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    addi r3, r3, 0xe4
L_8288:
    bl ScrollToSelectedText__Q39textinput12candidatebox10UITextAreaFv
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 6
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    b L_8374
L_82a8:
    lwz r0, 0x16c(r30)
    cmplw r31, r0
    bne L_8374
    lwz r3, 0x1d4(r30)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x104(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_837c
    lbz r31, 0x1f4(r30)
    li r0, 1
    lwz r3, 0x16c(r30)
    stb r0, 0x1f4(r30)
    lwz r12, 0(r3)
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    blt L_837c
    lwz r3, 0x16c(r30)
    cmpwi r31, 0
    lwz r4, 0x98(r3)
    beq L_831c
    addi r4, r4, -1
L_831c:
    cmpwi r4, 0
    bge L_8338
    lwz r12, 0(r3)
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    addi r4, r3, -1
L_8338:
    mr r3, r30
L_833c:
    bl moveCandidateToIdx__Q39textinput9inputform4BaseFl
    lwz r3, 0x1d4(r30)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    addi r3, r3, 0xe4
L_8358:
    bl ScrollToSelectedText__Q39textinput12candidatebox10UITextAreaFv
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 6
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
L_8374:
    li r0, 1
    stw r0, 0x1b0(r30)
L_837c:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr 
}

extern "C" asm void onPressRightHWKB__Q39textinput9inputform4BaseFv() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    stw r30, 8(r1)
L_83b0:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lis r4, sInstance__Q39textinput5input10HKBManager@l
    mr r30, r3
    addi r3, r4, sInstance__Q39textinput5input10HKBManager@ha
L_83c0:
    bl GetModifierState__Q39textinput5input10HKBManagerCFv
    lwz r12, 0(r30)
    mr r3, r30
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r0, 0x164(r31)
    cmplw r30, r0
    bne L_85b0
    lwz r0, 0x1f0(r31)
    cmpwi r0, 9
    bne L_84d8
    mr r3, r31
    li r4, 0
L_83f8:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r12, 0(r3)
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_84c4
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r31)
    li r4, 0xa
    lwz r12, 0(r3)
    lwz r12, 0x50(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r0, 0x1f0(r31)
    cmpwi r0, 8
    bne L_84c4
    lbz r0, 0x178(r31)
    cmpwi r0, 0
    bne L_8474
    li r0, 0
    b L_84a8
L_8474:
    lwz r0, 0x174(r31)
    cmpwi r0, 1
    beq L_84a4
    lwz r3, 0x16c(r31)
    lwz r12, 0(r3)
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    ble L_84a4
    li r0, 1
    b L_84a8
L_84a4:
    li r0, 0
L_84a8:
    cmpwi r0, 0
    beq L_84c4
    lwz r3, 0x16c(r31)
    li r4, 0
L_84b8:
    bl setCurrentWord__Q39textinput8tistring6WithZiFPCw
    lwz r3, 0x16c(r31)
L_84c0:
    bl update__Q39textinput8tistring6WithZiFv
L_84c4:
    lwz r12, 0(r30)
    mr r3, r30
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
L_84d8:
    lwz r12, 0(r30)
    mr r3, r30
    lwz r12, 0x48(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_87c8
    lwz r12, 0(r30)
    mr r3, r30
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_8514
    b L_87c8
L_8514:
    lwz r3, 0x1d4(r31)
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
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r30)
    mr r3, r30
    lwz r12, 0x64(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_8594
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 6
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    b L_87c0
L_8594:
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 5
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    b L_87c0
L_85b0:
    lwz r0, 0x168(r31)
    cmplw r30, r0
    bne L_86e4
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x104(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_87c8
    lwz r3, 0x168(r31)
    lwz r12, 0(r3)
    lwz r12, 0xe4(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    ble L_87c8
    lwz r3, 0x168(r31)
    lwz r12, 0(r3)
    lwz r12, 0xdc(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_8664
    lwz r12, 0(r30)
    mr r3, r30
    lwz r12, 0x64(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 6
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    b L_87c0
L_8664:
    lwz r3, 0x168(r31)
    lwz r12, 0(r3)
    lwz r12, 0xf8(r12)
    mtctr r12
    bctrl 
    addi r0, r3, 1
    lwz r3, 0x168(r31)
    extsh r30, r0
    lwz r12, 0(r3)
    lwz r12, 0xe4(r12)
    mtctr r12
    bctrl 
    cmpw r30, r3
    blt L_86a0
    li r30, 0
L_86a0:
    mr r3, r31
    mr r4, r30
L_86a8:
    bl moveCandidateToIdx__Q39textinput9inputform4BaseFl
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    addi r3, r3, 0xe4
L_86c4:
    bl ScrollToSelectedText__Q39textinput12candidatebox10UITextAreaFv
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 6
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    b L_87c0
L_86e4:
    lwz r0, 0x16c(r31)
    cmplw r30, r0
    bne L_87c0
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x104(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_87c8
    lbz r30, 0x1f4(r31)
    li r0, 1
    lwz r3, 0x16c(r31)
    stb r0, 0x1f4(r31)
    lwz r12, 0(r3)
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    blt L_87c8
    lwz r3, 0x16c(r31)
    cmpwi r30, 0
    lwz r30, 0x98(r3)
    beq L_8758
    addi r30, r30, 1
L_8758:
    lwz r12, 0(r3)
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    cmpw r30, r3
    blt L_8774
    li r30, 0
L_8774:
    cmpwi r30, 0
    bge L_8780
    li r30, 0
L_8780:
    mr r3, r31
    mr r4, r30
L_8788:
    bl moveCandidateToIdx__Q39textinput9inputform4BaseFl
    lwz r3, 0x1d4(r31)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    addi r3, r3, 0xe4
L_87a4:
    bl ScrollToSelectedText__Q39textinput12candidatebox10UITextAreaFv
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 6
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
L_87c0:
    li r0, 1
    stw r0, 0x1b0(r31)
L_87c8:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr 
}

extern "C" asm void onSpaceKeyHWKB__Q39textinput9inputform4BaseFUl() {
    nofralloc
    stwu r1, -0x100(r1)
    mflr r0
    stw r0, 0x104(r1)
    addi r11, r1, 0x100
L_8ff8:
    bl _savegpr_21
    mr r30, r4
    mr r29, r3
    li r4, 0
L_9008:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    rlwinm. r0, r30, 0, 0x1c, 0x1c
    mr r21, r3
    beq L_90ec
    lwz r3, 0x1f0(r29)
    addi r0, r3, -8
    cmplwi r0, 1
    bgt L_993c
    lwz r3, 0x1d4(r29)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lbz r0, 0x3c(r3)
    cmpwi r0, 0
    bne L_993c
    lwz r3, 0x1d4(r29)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lbz r0, 0x3d(r3)
    cmpwi r0, 0
    beq L_993c
    lwz r3, 0x1d4(r29)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x58(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_90c0
    lwz r3, 0x1d4(r29)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    li r4, 1
    lwz r12, 0x5c(r12)
    mtctr r12
    bctrl 
    b L_993c
L_90c0:
    lwz r3, 0x1d4(r29)
    lwz r12, 0(r3)
    lwz r12, 0x74(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    li r4, 0
    lwz r12, 0x5c(r12)
    mtctr r12
    bctrl 
    b L_993c
L_90ec:
    lbz r0, 0x178(r29)
    cmpwi r0, 0
    bne L_9100
    li r0, 0
    b L_9158
L_9100:
    lwz r0, 0x174(r29)
    cmpwi r0, 1
    bne L_9114
    li r0, 0
    b L_9158
L_9114:
    lwz r0, 0x1f0(r29)
    cmpwi r0, 8
    bne L_9154
    lwz r3, 0x1d4(r29)
    lwz r12, 0(r3)
    lwz r12, 0x90(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x4c(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_9154
    li r0, 0
    b L_9158
L_9154:
    li r0, 1
L_9158:
    cmpwi r0, 0
    beq L_92e4
    lbz r0, 0x178(r29)
    cmpwi r0, 0
    bne L_9174
    li r0, 0
    b L_91a8
L_9174:
    lwz r0, 0x174(r29)
    cmpwi r0, 1
    beq L_91a4
    lwz r3, 0x16c(r29)
    lwz r12, 0(r3)
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    ble L_91a4
    li r0, 1
    b L_91a8
L_91a4:
    li r0, 0
L_91a8:
    cmpwi r0, 0
    beq L_95a8
    lbz r3, 0x1f5(r29)
    lbz r0, 0x1f4(r29)
    or. r0, r3, r0
    bne L_92c4
    lwz r3, 0x1d4(r29)
    lwz r12, 0(r3)
    lwz r12, 0x94(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_92c4
    lwz r0, 0x1f0(r29)
    cmpwi r0, 8
    beq L_92cc
    cmpwi r0, 9
    beq L_92cc
    lbz r0, 0x178(r29)
    cmpwi r0, 0
    beq L_92cc
    lwz r0, 0x174(r29)
    cmpwi r0, 1
    beq L_92cc
    lwz r3, 0x16c(r29)
    addi r4, r1, 0x48
    li r5, 0x40
L_9224:
    bl getCurrentInput__Q39textinput8tistring6WithZiFPwUl
    lwz r3, 0x164(r29)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r29)
    addi r4, r1, 0x48
    lwz r12, 0(r3)
    lwz r12, 0x54(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x164(r29)
    lwz r12, 0(r3)
    lwz r12, 0x7c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x16c(r29)
L_926c:
    bl clearCandidates__Q39textinput8tistring6WithZiFv
    li r0, 0
    mr r3, r29
    stb r0, 0x1f4(r29)
    li r4, 0
L_9280:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r3, 0x16c(r29)
    cmpwi r3, 0
    beq L_92cc
    lwz r0, 0x1f0(r29)
    cmpwi r0, 8
    bne L_92cc
    li r4, 0
L_92a0:
    bl setCurrentWord__Q39textinput8tistring6WithZiFPCw
    lwz r3, 0x16c(r29)
L_92a8:
    bl update__Q39textinput8tistring6WithZiFv
    lwz r12, 0(r29)
    mr r3, r29
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    b L_92cc
L_92c4:
    mr r3, r29
L_92c8:
    bl confirmInput___Q39textinput9inputform4BaseFv
L_92cc:
    lwz r12, 0(r29)
    mr r3, r29
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    b L_95a8
L_92e4:
    lbz r0, 0x178(r29)
    cmpwi r0, 0
    bne L_92f8
    li r0, 0
    b L_9308
L_92f8:
    lwz r3, 0x174(r29)
    addi r0, r3, -1
    cntlzw r0, r0
    srwi r0, r0, 5
L_9308:
    cmpwi r0, 0
    beq L_95a8
    lwz r3, 0x168(r29)
    cmplw r21, r3
    bne L_95a8
    lwz r12, 0(r3)
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_9348
    lwz r3, 0x168(r29)
    lwz r12, 0(r3)
    lwz r12, 0xc4(r12)
    mtctr r12
    bctrl 
L_9348:
    lwz r3, 0x168(r29)
    lwz r12, 0(r3)
    lwz r12, 0xdc(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_951c
    lwz r3, 0x1d4(r29)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x104(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_993c
    rlwinm. r0, r30, 0, 0x1e, 0x1e
    beq L_9440
    mr r3, r29
    li r4, 0
L_93a0:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r0, 0x168(r29)
    cmplw r3, r0
    bne L_94e4
    mr r3, r0
    lwz r12, 0(r3)
    lwz r12, 0x138(r12)
    mtctr r12
    bctrl 
    addi r0, r3, -1
    lwz r3, 0x168(r29)
    extsh r21, r0
    lwz r12, 0(r3)
    lwz r12, 0xe4(r12)
    mtctr r12
    bctrl 
    cmpw r21, r3
    blt L_93f0
    li r21, 0
    b L_9414
L_93f0:
    cmpwi r21, 0
    bge L_9414
    lwz r3, 0x168(r29)
    lwz r12, 0(r3)
    lwz r12, 0xe4(r12)
    mtctr r12
    bctrl 
    addi r0, r3, -1
    extsh r21, r0
L_9414:
    mr r3, r29
    mr r4, r21
L_941c:
    bl moveCandidateToIdx__Q39textinput9inputform4BaseFl
    lwz r3, 0x1d4(r29)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    addi r3, r3, 0xe4
L_9438:
    bl ScrollToSelectedText__Q39textinput12candidatebox10UITextAreaFv
    b L_94e4
L_9440:
    mr r3, r29
    li r4, 0
L_9448:
    bl getCurrentString__Q39textinput9inputform4BaseFb
    lwz r0, 0x168(r29)
    cmplw r3, r0
    bne L_94e4
    mr r3, r0
    lwz r12, 0(r3)
    lwz r12, 0x138(r12)
    mtctr r12
    bctrl 
    addi r0, r3, 1
    lwz r3, 0x168(r29)
    extsh r21, r0
    lwz r12, 0(r3)
    lwz r12, 0xe4(r12)
    mtctr r12
    bctrl 
    cmpw r21, r3
    blt L_9498
    li r21, 0
    b L_94bc
L_9498:
    cmpwi r21, 0
    bge L_94bc
    lwz r3, 0x168(r29)
    lwz r12, 0(r3)
    lwz r12, 0xe4(r12)
    mtctr r12
    bctrl 
    addi r0, r3, -1
    extsh r21, r0
L_94bc:
    mr r3, r29
    mr r4, r21
L_94c4:
    bl moveCandidateToIdx__Q39textinput9inputform4BaseFl
    lwz r3, 0x1d4(r29)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    addi r3, r3, 0xe4
L_94e0:
    bl ScrollToSelectedText__Q39textinput12candidatebox10UITextAreaFv
L_94e4:
    lwz r12, 0(r29)
    mr r3, r29
    li r4, 6
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x1d4(r29)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    addi r3, r3, 0xe4
L_9514:
    bl ScrollToSelectedText__Q39textinput12candidatebox10UITextAreaFv
    b L_993c
L_951c:
    lwz r3, 0x168(r29)
    lwz r12, 0(r3)
    lwz r12, 0x124(r12)
    mtctr r12
    bctrl 
    clrlwi. r0, r3, 0x10
    beq L_993c
    lwz r3, 0x168(r29)
    lwz r12, 0(r3)
    lwz r12, 0x118(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r29)
    mr r3, r29
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
    mr r3, r29
    li r4, 0
L_9568:
    bl moveCandidateToIdx__Q39textinput9inputform4BaseFl
    lwz r3, 0x1d4(r29)
    lwz r12, 0(r3)
    lwz r12, 0x8c(r12)
    mtctr r12
    bctrl 
    addi r3, r3, 0xe4
L_9584:
    bl ScrollToSelectedText__Q39textinput12candidatebox10UITextAreaFv
    lwz r12, 0(r29)
    mr r3, r29
    li r4, 0x2f
    li r5, 0
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
    b L_993c
L_95a8:
    addi r3, r29, 0x1d8
    li r4, 0
    li r5, 0
L_95b4:
    bl KPRLookAhead
    clrlwi. r0, r3, 0x18
    beq L_95d8
    lis r4, 1
    addi r3, r29, 0x1d8
    addi r0, r4, -1
    clrlwi r4, r0, 0x10
L_95d0:
    bl KPRPutChar
    b L_95e4
L_95d8:
    addi r3, r29, 0x1d8
    li r4, 0x20
L_95e0:
    bl KPRPutChar
L_95e4:
    lbz r0, 0x178(r29)
    cmpwi r0, 0
    bne L_95f8
    li r0, 0
    b L_9650
L_95f8:
    lwz r0, 0x174(r29)
    cmpwi r0, 1
    bne L_960c
    li r0, 0
    b L_9650
L_960c:
    lwz r0, 0x1f0(r29)
    cmpwi r0, 8
    bne L_964c
    lwz r3, 0x1d4(r29)
    lwz r12, 0(r3)
    lwz r12, 0x90(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lwz r12, 0x4c(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_964c
    li r0, 0
    b L_9650
L_964c:
    li r0, 1
L_9650:
    cmpwi r0, 0
    beq L_97c0
    lis r31, lbl_8165C970@l
    li r28, 3
    addi r31, r31, lbl_8165C970@ha
L_9664:
    addi r3, r29, 0x1d8
L_9668:
    bl KPRGetChar
    lbz r0, sbCompatibleFilterEnabled__Q39textinput9inputform13DeadKeyStream(r0)
    cmpwi r0, 0
    beq L_97a8
    b L_9684
L_967c:
    addi r3, r29, 0x1d8
L_9680:
    bl KPRGetChar
L_9684:
    lhz r27, 0(r31)
    clrlwi r4, r3, 0x10
    lhz r26, 2(r31)
    lhz r25, 4(r31)
    cmplw r4, r27
    lhz r24, 6(r31)
    lhz r23, 8(r31)
    lhz r22, 0xa(r31)
    lhz r21, 0xc(r31)
    lhz r12, 0xe(r31)
    lhz r11, 0x10(r31)
    lhz r10, 0x12(r31)
    lhz r9, 0x14(r31)
    lhz r8, 0x16(r31)
    lhz r7, 0x18(r31)
    lhz r6, 0x1a(r31)
    lhz r5, 0x1c(r31)
    lhz r0, 0x1e(r31)
    sth r27, 0x28(r1)
    sth r26, 0x2a(r1)
    sth r25, 0x2c(r1)
    sth r24, 0x2e(r1)
    sth r23, 0x30(r1)
    sth r22, 0x32(r1)
    sth r21, 0x34(r1)
    sth r12, 0x36(r1)
    sth r11, 0x38(r1)
    sth r10, 0x3a(r1)
    sth r9, 0x3c(r1)
    sth r8, 0x3e(r1)
    sth r7, 0x40(r1)
    sth r6, 0x42(r1)
    sth r5, 0x44(r1)
    sth r0, 0x46(r1)
    blt L_9718
    cmplw r4, r5
    ble L_9720
L_9718:
    li r0, 1
    b L_97a0
L_9720:
    addi r6, r1, 0x28
    li r5, 0
    mtctr r28
L_972c:
    lhz r0, 0(r6)
    cmplw r4, r0
    bne L_9740
    li r0, 0
    b L_97a0
L_9740:
    lhz r0, 2(r6)
    cmplw r4, r0
    bne L_9754
    li r0, 0
    b L_97a0
L_9754:
    lhz r0, 4(r6)
    cmplw r4, r0
    bne L_9768
    li r0, 0
    b L_97a0
L_9768:
    lhz r0, 6(r6)
    cmplw r4, r0
    bne L_977c
    li r0, 0
    b L_97a0
L_977c:
    lhz r0, 8(r6)
    cmplw r4, r0
    bne L_9790
    li r0, 0
    b L_97a0
L_9790:
    addi r6, r6, 0xa
    addi r5, r5, 4
    bdnz L_972c
    li r0, 1
L_97a0:
    cmpwi r0, 0
    beq L_967c
L_97a8:
    clrlwi. r4, r3, 0x10
    beq L_9928
    mr r3, r29
    mr r5, r30
L_97b8:
    bl inputCharZi___Q39textinput9inputform4BaseFwUl
    b L_9664
L_97c0:
    lis r31, lbl_8165C970@l
    li r28, 3
    addi r31, r31, lbl_8165C970@ha
L_97cc:
    addi r3, r29, 0x1d8
L_97d0:
    bl KPRGetChar
    lbz r0, sbCompatibleFilterEnabled__Q39textinput9inputform13DeadKeyStream(r0)
    cmpwi r0, 0
    beq L_9910
    b L_97ec
L_97e4:
    addi r3, r29, 0x1d8
L_97e8:
    bl KPRGetChar
L_97ec:
    lhz r21, 0(r31)
    clrlwi r4, r3, 0x10
    lhz r22, 2(r31)
    lhz r23, 4(r31)
    cmplw r4, r21
    lhz r24, 6(r31)
    lhz r25, 8(r31)
    lhz r26, 0xa(r31)
    lhz r27, 0xc(r31)
    lhz r12, 0xe(r31)
    lhz r11, 0x10(r31)
    lhz r10, 0x12(r31)
    lhz r9, 0x14(r31)
    lhz r8, 0x16(r31)
    lhz r7, 0x18(r31)
    lhz r6, 0x1a(r31)
    lhz r5, 0x1c(r31)
    lhz r0, 0x1e(r31)
    sth r21, 8(r1)
    sth r22, 0xa(r1)
    sth r23, 0xc(r1)
    sth r24, 0xe(r1)
    sth r25, 0x10(r1)
    sth r26, 0x12(r1)
    sth r27, 0x14(r1)
    sth r12, 0x16(r1)
    sth r11, 0x18(r1)
    sth r10, 0x1a(r1)
    sth r9, 0x1c(r1)
    sth r8, 0x1e(r1)
    sth r7, 0x20(r1)
    sth r6, 0x22(r1)
    sth r5, 0x24(r1)
    sth r0, 0x26(r1)
    blt L_9880
    cmplw r4, r5
    ble L_9888
L_9880:
    li r0, 1
    b L_9908
L_9888:
    addi r6, r1, 8
    li r5, 0
    mtctr r28
L_9894:
    lhz r0, 0(r6)
    cmplw r4, r0
    bne L_98a8
    li r0, 0
    b L_9908
L_98a8:
    lhz r0, 2(r6)
    cmplw r4, r0
    bne L_98bc
    li r0, 0
    b L_9908
L_98bc:
    lhz r0, 4(r6)
    cmplw r4, r0
    bne L_98d0
    li r0, 0
    b L_9908
L_98d0:
    lhz r0, 6(r6)
    cmplw r4, r0
    bne L_98e4
    li r0, 0
    b L_9908
L_98e4:
    lhz r0, 8(r6)
    cmplw r4, r0
    bne L_98f8
    li r0, 0
    b L_9908
L_98f8:
    addi r6, r6, 0xa
    addi r5, r5, 4
    bdnz L_9894
    li r0, 1
L_9908:
    cmpwi r0, 0
    beq L_97e4
L_9910:
    clrlwi. r4, r3, 0x10
    beq L_9928
    mr r3, r29
    mr r5, r30
L_9920:
    bl inputCharDefault___Q39textinput9inputform4BaseFwUl
    b L_97cc
L_9928:
    lwz r12, 0(r29)
    mr r3, r29
    lwz r12, 0xd8(r12)
    mtctr r12
    bctrl 
L_993c:
    addi r11, r1, 0x100
L_9940:
    bl _restgpr_21
    lwz r0, 0x104(r1)
    mtlr r0
    addi r1, r1, 0x100
    blr 
}

extern "C" asm void create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer() {
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    addi r11, r1, 0x60
L_9c2c:
    bl _savegpr_18
    lis r30, lbl_8165C820@l
    stw r4, 0x1d0(r3)
    mr r23, r3
    mr r24, r4
    mr r18, r5
    addi r30, r30, lbl_8165C820@ha
    addi r3, r3, 0x10
L_9c4c:
    bl create__Q39textinput10textdrawer4BaseFP12MEMAllocator
    lwz r0, 4(r18)
    mr r3, r24
    lhz r4, 0x1fc(r23)
    stw r0, 0x164(r23)
    addi r0, r4, 2
    lwz r5, 8(r18)
    slwi r4, r0, 3
    stw r5, 0x168(r23)
    lwz r0, 0xc(r18)
    stw r0, 0x16c(r23)
    stw r24, 0x200(r23)
L_9c7c:
    bl MEMAllocFromAllocator
    stw r3, 0x1f8(r23)
    addi r3, r23, 0x1f8
L_9c88:
    bl init__Q49textinput9inputform4Base14RowInfoManagerFv
    lhz r0, 0x1fc(r23)
    lwz r6, 0x1f8(r23)
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
    lhz r3, 0x1fc(r23)
    lwz r6, 0x1f8(r23)
    addi r0, r3, 1
    rlwinm r0, r0, 3, 0xd, 0x1c
    lhzx r0, r6, r0
    slwi r0, r0, 3
    add r4, r6, r0
    bne L_9d10
    lhz r7, 2(r4)
    slwi r3, r7, 3
    lhzx r0, r6, r3
    sth r0, 0(r5)
    sth r7, 2(r5)
    sth r9, 2(r4)
    sthx r9, r6, r3
L_9d10:
    li r20, 0
    li r0, 1
    sth r20, 4(r5)
    mr r3, r24
    li r4, 0x10
    sth r0, 6(r5)
    stw r5, 0x204(r23)
L_9d2c:
    bl MEMAllocFromAllocator
    cmpwi r3, 0
    beq L_9d4c
    lis r4, __vt__Q39textinput9inputform12EventHandler@l
    stw r20, 4(r3)
    addi r4, r4, __vt__Q39textinput9inputform12EventHandler@ha
    stw r4, 0(r3)
    stw r23, 0xc(r3)
L_9d4c:
    stw r3, 0x2d0(r23)
    mr r5, r3
    mr r4, r24
    addi r3, r23, 0x218
L_9d5c:
    bl createWithEventHandler__Q39textinput11nw4rmanager6LayoutFP12MEMAllocatorPQ39textinput11nw4rmanager14TiEventHandler
    lwz r4, 0x2c8(r23)
    cmpwi r4, 0
    bne L_9dd8
    addi r5, r30, 0x3d0
    lwz r3, 0x224(r23)
    stw r5, 0x2c8(r23)
    li r4, 0
    li r6, 0
    lwz r12, 0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl 
    mr r4, r3
    addi r3, r23, 0x2d4
L_9d98:
    bl SetResource__Q34nw4r2ut7ResFontFPv
    lwz r12, 0x2d4(r23)
    lis r4, 1
    addi r0, r4, -0x1f95
    addi r3, r23, 0x2d4
    lwz r12, 0x40(r12)
    clrlwi r4, r0, 0x10
    mtctr r12
    bctrl 
    lwz r12, 0(r23)
    mr r3, r23
    addi r4, r23, 0x2d4
    lwz r12, 0xec(r12)
    mtctr r12
    bctrl 
    b L_9e38
L_9dd8:
    lwz r3, 0x224(r23)
    lwz r12, 0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    lis r4, 1
    addi r0, r4, -0x1f95
    lwz r12, 0x40(r12)
    clrlwi r4, r0, 0x10
    mtctr r12
    bctrl 
    lwz r3, 0x224(r23)
    lwz r4, 0x2c8(r23)
    lwz r12, 0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r23)
    mr r4, r3
    mr r3, r23
    lwz r12, 0xec(r12)
    mtctr r12
    bctrl 
L_9e38:
    lwz r3, 0x21c(r23)
    li r5, 1
    lwz r4, 0x2c0(r23)
    lwz r3, 0x10(r3)
    lwz r12, 0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    mr r20, r3
    la r4, lbl_816973B4(r0)
    li r5, 0
    lwz r12, 0x6c(r12)
    mtctr r12
    bctrl 
    lfs f0, 0xf0(r20)
    mr r4, r20
    addi r3, r1, 0x10
    addi r5, r23, 0x230
    stfs f0, 0xb8(r23)
    lfs f0, 0xec(r20)
    stfs f0, 0xb4(r23)
    lfs f0, 0xe4(r20)
    stfs f0, 0xbc(r23)
    lfs f0, 0xe8(r20)
    stfs f0, 0xc0(r23)
L_9ea0:
    bl GetPaneRect__Q34nw4r3lyt4PaneCFRCQ34nw4r3lyt8DrawInfo
    lfs f0, 0x10(r1)
    addi r3, r23, 0x218
    addi r4, r23, 0x130
    addi r5, r23, 0x230
    stfs f0, 0x120(r23)
    addi r6, r20, 0x84
    lfs f0, 0x14(r1)
    stfs f0, 0x124(r23)
    lfs f0, 0x18(r1)
    stfs f0, 0x128(r23)
    lfs f0, 0x1c(r1)
    stfs f0, 0x12c(r23)
    lwz r12, 0x218(r23)
    lwz r12, 0x70(r12)
    mtctr r12
    bctrl 
    mr r4, r20
    addi r3, r1, 8
    li r5, 0
L_9ef0:
    bl GetTextColor__Q34nw4r3lyt7TextBoxCFUl
    lbz r4, 8(r1)
    la r7, csCharColor__Q29textinput9inputform(r0)
    lbz r8, 9(r1)
    addi r3, r23, 0x218
    lbz r6, 0xa(r1)
    li r5, 1
    lbz r0, 0xb(r1)
    stb r4, csCharColor__Q29textinput9inputform(r0)
    la r4, lbl_816973B8(r0)
    stb r8, 1(r7)
    stb r6, 2(r7)
    stb r0, 3(r7)
    lwz r12, 0x218(r23)
    lwz r12, 0x54(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x228(r23)
    li r4, 0
    lwz r12, 0(r3)
    lwz r12, 0x38(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x228(r23)
    li r4, 1
    lwz r12, 0(r3)
    lwz r12, 0x58(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x21c(r23)
    li r5, 1
    lwz r4, 0x2c4(r23)
    lwz r3, 0x10(r3)
    lwz r4, 8(r4)
    lwz r12, 0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    mr r4, r3
    bne L_9fe8
    lwz r12, 0x218(r23)
    addi r3, r23, 0x218
    lwz r4, 0x2c4(r23)
    lwz r12, 0x30(r12)
    lwz r4, 8(r4)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_9fc4
    lwz r3, 0x2c4(r23)
    lwz r4, 8(r3)
    b L_9fc8
L_9fc4:
    addi r4, r30, 0x3c0
L_9fc8:
    lwz r3, 0x21c(r23)
    li r5, 1
    lwz r3, 0x10(r3)
    lwz r12, 0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl 
    mr r4, r3
L_9fe8:
    lwz r3, 0x228(r23)
    lwz r12, 0(r3)
    lwz r12, 0x4c(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    li r4, 1
    lwz r12, 0x54(r12)
    mtctr r12
    bctrl 
    lis r31, __vt__Q39textinput11nw4rmanager7AnmPane@l
    lis r21, __vt__Q39textinput9inputform19NormalButtonAnmPane@l
    addi r30, r30, 0x20
    li r28, 0
    addi r31, r31, __vt__Q39textinput11nw4rmanager7AnmPane@ha
    addi r21, r21, __vt__Q39textinput9inputform19NormalButtonAnmPane@ha
    li r20, 0
L_a02c:
    rlwinm r0, r28, 6, 0xa, 0x19
    li r26, 0
    add r27, r30, r0
    lwzx r0, r30, r0
    cmpwi r0, 0
    beq L_a048
    b L_a0a0
L_a048:
    mr r3, r24
    li r4, 0x34
L_a050:
    bl MEMAllocFromAllocator
    cmpwi r3, 0
    mr r26, r3
    beq L_a0a0
    lwz r12, 0x218(r23)
    addi r3, r23, 0x218
    lwz r4, 4(r27)
    lwz r12, 0x2c(r12)
    mtctr r12
    bctrl 
    stw r31, 0(r26)
    li r4, 0x10
    stw r3, 4(r26)
    addi r3, r26, 8
    stw r20, 0x14(r26)
    stw r20, 0x18(r26)
L_a090:
    bl List_Init__Q24nw4r2utFPQ34nw4r2ut4ListUs
    stw r20, 0x2c(r26)
    stw r21, 0(r26)
    stw r20, 0x30(r26)
L_a0a0:
    mr r4, r26
    addi r3, r23, 0x284
L_a0a8:
    bl List_Append__Q24nw4r2utFPQ34nw4r2ut4ListPv
    lwz r29, 0xc(r27)
    li r25, 0
    lwz r22, 8(r27)
    b L_a168
L_a0bc:
    lwz r3, 0x224(r23)
    rlwinm r0, r25, 2, 0xe, 0x1d
    add r19, r27, r0
    li r4, 0
    lwz r12, 0(r3)
    li r6, 0
    lwz r5, 0x10(r19)
    lwz r12, 0xc(r12)
    addi r5, r5, 4
    mtctr r12
    bctrl 
    lwz r12, 0x218(r23)
    mr r18, r3
    addi r3, r23, 0x218
    lwz r12, 0x28(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    mr r4, r18
    lwz r5, 0x224(r23)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl 
    cmpwi r29, 0
    mr r6, r3
    bne L_a144
    lwz r5, 0x10(r19)
    mr r3, r26
    mr r4, r24
    li r7, 0
    lwz r5, 0(r5)
    li r8, 1
L_a13c:
    bl addAnimation__Q39textinput11nw4rmanager7AnmPaneFP12MEMAllocatorUlPQ29textinput17AnimTransformPanebb
    b L_a164
L_a144:
    lwz r5, 0x10(r19)
    mr r3, r26
    mr r4, r24
    mr r7, r29
    lwz r5, 0(r5)
    li r8, 0
    li r9, 1
L_a160:
    bl forceAddAnimation__Q39textinput11nw4rmanager7AnmPaneFP12MEMAllocatorUlPQ29textinput17AnimTransformPanePCcbb
L_a164:
    addi r25, r25, 1
L_a168:
    clrlwi r0, r25, 0x10
    cmplw r0, r22
    blt L_a0bc
    addi r28, r28, 1
    cmplwi r28, 2
    blt L_a02c
    lwz r12, 0(r23)
    mr r3, r23
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl 
    addi r11, r1, 0x60
L_a198:
    bl _restgpr_18
    lwz r0, 0x64(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr 
}

extern "C" asm void setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language() {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    stw r30, 0x18(r1)
    lis r30, csAninationFile__Q29textinput9inputform@l
    addi r30, r30, csAninationFile__Q29textinput9inputform@ha
    stw r29, 0x14(r1)
    mr r29, r4
L_a954:
    bl setLanguage__Q39textinput9inputform4BaseFQ29textinput8Language
    cmpwi r29, 8
    bne L_a96c
    addi r0, r30, 0x2b0
    stw r0, 0x2c4(r31)
    b L_a988
L_a96c:
    cmpwi r29, 9
    bne L_a980
    addi r0, r30, 0x2a0
    stw r0, 0x2c4(r31)
    b L_a988
L_a980:
    addi r0, r30, 0x290
    stw r0, 0x2c4(r31)
L_a988:
    lwz r12, 0x218(r31)
    addi r3, r31, 0x218
    lwz r4, 0x2c4(r31)
    lwz r12, 0x30(r12)
    lwz r4, 8(r4)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_a9b8
    lwz r3, 0x2c4(r31)
    lwz r3, 8(r3)
    b L_a9c0
L_a9b8:
    lis r3, lbl_8165CBE0@l
    addi r3, r3, lbl_8165CBE0@ha
L_a9c0:
    lis r30, lbl_8165CBE0@l
    stw r3, 0x2c0(r31)
    addi r4, r30, lbl_8165CBE0@ha
L_a9cc:
    bl strcmp
    cmpwi r3, 0
    beq L_a9f4
    lwz r12, 0x218(r31)
    addi r3, r31, 0x218
    addi r4, r30, lbl_8165CBE0@ha
    li r5, 0
    lwz r12, 0x54(r12)
    mtctr r12
    bctrl 
L_a9f4:
    lwz r12, 0x218(r31)
    addi r3, r31, 0x218
    lwz r4, 0x2c4(r31)
    lwz r12, 0x30(r12)
    lwz r4, 8(r4)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_aa24
    lwz r3, 0x2c4(r31)
    lwz r4, 8(r3)
    b L_aa2c
L_aa24:
    lis r4, lbl_8165CBE0@l
    addi r4, r4, lbl_8165CBE0@ha
L_aa2c:
    lwz r3, 0x21c(r31)
    li r5, 1
    lwz r3, 0x10(r3)
    lwz r12, 0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    la r4, lbl_816973B4(r0)
    li r5, 0
    lwz r12, 0x6c(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x2c4(r31)
    li r30, 0
    lwz r29, 0(r3)
    b L_aa98
L_aa70:
    lwz r12, 0x218(r31)
    rlwinm r0, r30, 2, 0xe, 0x1d
    add r4, r29, r0
    addi r3, r31, 0x218
    lwz r12, 0x54(r12)
    li r5, 1
    lwz r4, 4(r4)
    mtctr r12
    bctrl 
    addi r30, r30, 1
L_aa98:
    lhz r0, 0(r29)
    clrlwi r3, r30, 0x10
    cmplw r3, r0
    blt L_aa70
    li r30, 0
    b L_aad8
L_aab0:
    lwz r12, 0x218(r31)
    rlwinm r0, r30, 2, 0xe, 0x1d
    add r4, r29, r0
    addi r3, r31, 0x218
    lwz r12, 0x54(r12)
    li r5, 0
    lwz r4, 0x14(r4)
    mtctr r12
    bctrl 
    addi r30, r30, 1
L_aad8:
    lhz r0, 2(r29)
    clrlwi r3, r30, 0x10
    cmplw r3, r0
    blt L_aab0
    lwz r12, 0x218(r31)
    addi r3, r31, 0x218
    lwz r4, 0x2c4(r31)
    lwz r12, 0x30(r12)
    lwz r4, 8(r4)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_ab18
    lwz r3, 0x2c4(r31)
    lwz r4, 8(r3)
    b L_ab20
L_ab18:
    lis r4, lbl_8165CBE0@l
    addi r4, r4, lbl_8165CBE0@ha
L_ab20:
    lwz r3, 0x21c(r31)
    li r5, 1
    lwz r3, 0x10(r3)
    lwz r12, 0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl 
    mr r4, r3
    lwz r3, 0x228(r31)
    lwz r12, 0(r3)
    lwz r12, 0x4c(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    li r4, 1
    lwz r12, 0x54(r12)
    mtctr r12
    bctrl 
    lwz r12, 0x218(r31)
    lis r30, lbl_8165CC4C@l
    addi r3, r31, 0x218
    lwz r12, 0x2c(r12)
    addi r4, r30, lbl_8165CC4C@ha
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_acc4
    lwz r12, 0x218(r31)
    addi r3, r31, 0x218
    addi r4, r30, lbl_8165CC4C@ha
    lwz r12, 0x2c(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    mr r30, r3
    la r29, typeInfo__Q34nw4r3lyt7TextBox(r0)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl 
    b L_abd4
L_abc0:
    cmplw r3, r29
    bne L_abd0
    li r0, 1
    b L_abe0
L_abd0:
    lwz r3, 0(r3)
L_abd4:
    cmpwi r3, 0
    bne L_abc0
    li r0, 0
L_abe0:
    cmpwi r0, 0
    beq L_abec
    b L_abf0
L_abec:
    li r30, 0
L_abf0:
    lwz r12, 0x218(r31)
    addi r3, r31, 0x218
    lwz r4, 0x2c4(r31)
    lwz r12, 0x2c(r12)
    lwz r4, 0xc(r4)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_acc4
    lwz r12, 0x218(r31)
    addi r3, r31, 0x218
    lwz r4, 0x2c4(r31)
    lwz r12, 0x2c(r12)
    lwz r4, 0xc(r4)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    mr r29, r3
    la r31, typeInfo__Q34nw4r3lyt7TextBox(r0)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl 
    b L_ac60
L_ac4c:
    cmplw r3, r31
    bne L_ac5c
    li r0, 1
    b L_ac6c
L_ac5c:
    lwz r3, 0(r3)
L_ac60:
    cmpwi r3, 0
    bne L_ac4c
    li r0, 0
L_ac6c:
    cmpwi r0, 0
    beq L_ac78
    b L_ac7c
L_ac78:
    li r29, 0
L_ac7c:
    lfs f0, 0xf0(r29)
    stfs f0, 0xf0(r30)
    lfs f0, 0xec(r29)
    stfs f0, 0xec(r30)
    lfs f0, 0xe4(r29)
    stfs f0, 0xe4(r30)
    lfs f0, 0xe8(r29)
    stfs f0, 0xe8(r30)
    lfs f0, 0x2c(r29)
    stfs f0, 0x2c(r30)
    lfs f0, 0x30(r29)
    stfs f0, 0x30(r30)
    lfs f0, 0x34(r29)
    stfs f0, 0x34(r30)
    lfs f0, 0x4c(r29)
    stfs f0, 0x4c(r30)
    lfs f0, 0x50(r29)
    stfs f0, 0x50(r30)
L_acc4:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr 
}

extern "C" asm void onCommand__Q39textinput9inputform12LayoutByNW4RFQ39textinput15CommandReceiver13INPUT_COMMANDPv() {
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    mr r31, r3
    stw r30, 0x28(r1)
    mr r30, r5
    stw r29, 0x24(r1)
    mr r29, r4
    lwz r3, 0x22c(r3)
    lwz r12, 0(r3)
    lwz r12, 8(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x22c(r31)
    mr r4, r29
    mr r5, r30
    lwz r12, 0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl 
    mr r3, r31
    mr r4, r29
    mr r5, r30
L_b170:
    bl onCommand__Q39textinput9inputform4BaseFQ39textinput15CommandReceiver13INPUT_COMMANDPv
    cmpwi r29, 0x1f
    beq L_b4e0
    lwz r0, 0x1b8(r31)
    stw r0, 0x1c(r1)
    lwz r0, 0x1f0(r31)
    cmpwi r0, 9
    bne L_b22c
    lwz r3, 0x164(r31)
    addi r4, r1, 0x18
    addi r5, r1, 0x14
    lwz r12, 0(r3)
    lwz r12, 0x80(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x18(r1)
    lwz r0, 0x1c(r1)
    cmplw r3, r0
    blt L_b204
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_b204
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0xc8(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 8
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
L_b204:
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_b22c
    lwz r3, 0x1b8(r31)
    addi r0, r3, -1
    stw r0, 0x1c(r1)
L_b22c:
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl 
    lwz r0, 0x1c(r1)
    clrlwi r3, r3, 0x10
    cmplw r0, r3
    bge L_b2b0
    lwz r3, 0x164(r31)
    addi r4, r1, 0x10
    addi r5, r1, 0xc
    lwz r12, 0(r3)
    lwz r12, 0x80(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x1c(r1)
    lwz r0, 0x10(r1)
    cmplw r0, r3
    bgt L_b288
    lwz r0, 0xc(r1)
    cmplw r0, r3
    ble L_b2b0
L_b288:
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 8
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    mr r3, r31
    addi r5, r1, 0x1c
    li r4, 0x24
L_b2ac:
    bl onCommand__Q39textinput9inputform4BaseFQ39textinput15CommandReceiver13INPUT_COMMANDPv
L_b2b0:
    cmpwi r29, 0x22
    beq L_b2d4
    bge L_b2c8
    cmpwi r29, 0x20
    bge L_b3a0
    b L_b2d4
L_b2c8:
    cmpwi r29, 0x24
    bge L_b2d4
    b L_b3a0
L_b2d4:
    lwz r3, 0x164(r31)
    lwz r30, 0x1c(r1)
    lwz r12, 0(r3)
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl 
    clrlwi r0, r3, 0x10
    cmplw r30, r0
    bge L_b3a0
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl 
    clrlwi r0, r3, 0x10
    cmplw r0, r30
    ble L_b32c
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl 
L_b32c:
    lwz r3, 0x164(r31)
    clrlwi r4, r30, 0x10
    lwz r12, 0(r3)
    lwz r12, 0x38(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x22c(r31)
    lwz r12, 0(r3)
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl 
    cmpwi r29, 6
    beq L_b388
    cmpwi r29, 5
    beq L_b388
    cmpwi r29, 0
    beq L_b388
    cmpwi r29, 0x26
    beq L_b388
    cmpwi r29, 0x15
    beq L_b388
    cmpwi r29, 7
    bne L_b3a0
L_b388:
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 8
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
L_b3a0:
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r31)
    mr r5, r3
    mr r3, r31
    lwz r4, 0x1bc(r31)
    lwz r12, 0x118(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    stw r3, 8(r1)
    mr r30, r3
    beq L_b4e0
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl 
    clrlwi r0, r3, 0x10
    cmplw r0, r30
    ble L_b414
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl 
L_b414:
    lwz r3, 0x164(r31)
    clrlwi r4, r30, 0x10
    lwz r12, 0(r3)
    lwz r12, 0x38(r12)
    mtctr r12
    bctrl 
    lwz r3, 0x22c(r31)
    lwz r12, 0(r3)
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r31)
    mr r3, r31
    li r4, 8
    lwz r12, 0x178(r12)
    mtctr r12
    bctrl 
    mr r3, r31
    addi r5, r1, 8
    li r4, 0x24
L_b464:
    bl onCommand__Q39textinput9inputform4BaseFQ39textinput15CommandReceiver13INPUT_COMMANDPv
    lwz r0, 0x1f0(r31)
    cmpwi r0, 9
    bne L_b4e0
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0xc0(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_b4e0
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0x3c(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r31)
    mr r5, r3
    mr r3, r31
    lwz r4, 0x1bc(r31)
    lwz r12, 0x118(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    stw r3, 8(r1)
    beq L_b4e0
    lwz r3, 0x164(r31)
    lwz r12, 0(r3)
    lwz r12, 0xc8(r12)
    mtctr r12
    bctrl 
L_b4e0:
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr 
}

extern "C" asm void isOverRowLimit__Q39textinput9inputform4BaseFUlPCw() {
    nofralloc
    stwu r1, -0xd0(r1)
    mflr r0
    stw r0, 0xd4(r1)
    stfd f31, 0xc0(r1)
    psq_st f31, 200(r1), 0, 0
    stfd f30, 0xb0(r1)
    psq_st f30, 184(r1), 0, 0
    stfd f29, 0xa0(r1)
    psq_st f29, 168(r1), 0, 0
    stfd f28, 0x90(r1)
    psq_st f28, 152(r1), 0, 0
    addi r11, r1, 0x90
L_b52c:
    bl _savegpr_23
    lhz r0, 0(r5)
    mr r24, r5
    mr r31, r3
    mr r23, r4
    cmpwi r0, 0
    mr r30, r24
    bne L_b554
    li r3, 0
    b L_b87c
L_b554:
    lwz r12, 0(r3)
    lwz r12, 0x188(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r31)
    stw r3, 0x38(r1)
    mr r3, r31
    lwz r12, 0x188(r12)
    stw r4, 0x3c(r1)
    lfs f31, 0x38(r1)
    mtctr r12
    bctrl 
    li r25, 0
    stw r3, 0x30(r1)
    addi r5, r1, 8
    li r29, 0
    stw r25, 0x1b4(r31)
    li r28, 0
    stb r25, mbHyphen__Q29textinput9inputform(r0)
    stw r3, 0x40(r1)
    lwz r3, 0x164(r31)
    stw r4, 0x34(r1)
    lwz r12, 0(r3)
    stw r4, 0x44(r1)
    addi r4, r1, 0xc
    lwz r12, 0x80(r12)
    mtctr r12
    bctrl 
    lfs f30, 0x40(r1)
    lfs f29, lbl_81694D28(r0)
L_b5cc:
    stfs f29, 0x48(r1)
    li r27, 0
    stfs f29, 0x4c(r1)
    stfs f29, 0x50(r1)
    stfs f29, 0x54(r1)
    lwz r0, 0x1f0(r31)
    cmpwi r0, 9
    bne L_b62c
    cmpwi r28, 0
    bne L_b62c
    lwz r0, 0xc(r1)
    cmplw r0, r25
    bne L_b62c
    lwz r3, 0x164(r31)
    li r28, 1
    lwz r12, 0(r3)
    lwz r12, 0xbc(r12)
    mtctr r12
    bctrl 
    lhz r0, 0(r3)
    mr r26, r3
    cmpwi r0, 0
    beq L_b62c
    li r27, 1
L_b62c:
    cmpwi r27, 0
    bne L_b644
    lhz r0, 0(r30)
    cmpwi r0, 0
    beq L_b878
    mr r26, r30
L_b644:
    lhz r0, 0(r26)
    addi r3, r31, 0x10
    addi r4, r1, 0x48
    sth r0, 0x58(r1)
    lwz r12, 0x5c(r31)
    lwz r12, 0x68(r12)
    mtctr r12
    bctrl 
    lfs f1, 0x50(r1)
    cmpwi r27, 0
    lfs f0, 0x48(r1)
    fsubs f0, f1, f0
    fmuls f0, f30, f0
    fadds f28, f31, f0
    beq L_b6d8
    lfs f1, 0x128(r31)
    lfs f0, 0x120(r31)
    fsubs f0, f1, f0
    fmuls f0, f30, f0
    fcmpo cr0, f28, f0
    cror eq, gt, eq
    bne L_b6d0
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0x188(r12)
    mtctr r12
    bctrl 
    stw r3, 0x28(r1)
    addi r29, r29, 1
    cmplw r29, r23
    stw r4, 0x2c(r1)
    lfs f31, 0x28(r1)
    blt L_b5cc
    mr r3, r25
    b L_b87c
L_b6d0:
    fmr f31, f28
    b L_b5cc
L_b6d8:
    lwz r12, 0(r31)
    fmr f1, f31
    mr r3, r31
    mr r4, r24
    lwz r12, 0x170(r12)
    mr r5, r25
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_b7ac
    addi r29, r29, 1
    cmplw r29, r23
    blt L_b788
    lfs f30, 0x40(r1)
    b L_b774
L_b714:
    lfs f2, 0x50(r1)
    lfs f0, 0x48(r1)
    lfs f1, 0x128(r31)
    fsubs f2, f2, f0
    lfs f0, 0x120(r31)
    fsubs f0, f1, f0
    fmuls f1, f30, f2
    fmuls f0, f30, f0
    fadds f2, f31, f1
    fcmpo cr0, f2, f0
    cror eq, gt, eq
    bne L_b74c
    mr r3, r25
    b L_b87c
L_b74c:
    lhzu r0, 2(r30)
    fadds f31, f31, f1
    addi r3, r31, 0x10
    addi r4, r1, 0x48
    sth r0, 0x58(r1)
    lwz r12, 0x5c(r31)
    lwz r12, 0x68(r12)
    mtctr r12
    bctrl 
    addi r25, r25, 1
L_b774:
    lwz r3, 0x1b4(r31)
    cmplw r25, r3
    blt L_b714
    addi r3, r3, -1
    b L_b87c
L_b788:
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0x188(r12)
    mtctr r12
    bctrl 
    stw r3, 0x20(r1)
    stw r4, 0x24(r1)
    lfs f31, 0x20(r1)
    b L_b800
L_b7ac:
    lfs f2, 0x128(r31)
    lfs f1, 0x120(r31)
    lfs f0, 0x40(r1)
    fsubs f1, f2, f1
    fmuls f0, f0, f1
    fcmpo cr0, f28, f0
    cror eq, gt, eq
    bne L_b800
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0x188(r12)
    mtctr r12
    bctrl 
    stw r3, 0x18(r1)
    addi r29, r29, 1
    cmplw r29, r23
    stw r4, 0x1c(r1)
    lfs f31, 0x18(r1)
    blt L_b800
    mr r3, r25
    b L_b87c
L_b800:
    lhz r0, 0(r30)
    cmplwi r0, 0xa
    bne L_b854
    lwz r12, 0(r31)
    mr r3, r31
    lwz r12, 0x188(r12)
    mtctr r12
    bctrl 
    stw r3, 0x10(r1)
    addi r29, r29, 1
    cmplw r29, r23
    stw r4, 0x14(r1)
    lfs f31, 0x10(r1)
    blt L_b840
    mr r3, r25
    b L_b87c
L_b840:
    lhz r0, 2(r30)
    cmpwi r0, 0
    bne L_b86c
    li r3, 0
    b L_b87c
L_b854:
    lfs f2, 0x50(r1)
    lfs f1, 0x48(r1)
    lfs f0, 0x40(r1)
    fsubs f1, f2, f1
    fmuls f0, f0, f1
    fadds f31, f31, f0
L_b86c:
    addi r25, r25, 1
    addi r30, r30, 2
    b L_b5cc
L_b878:
    li r3, 0
L_b87c:
    psq_l f31, 200(r1), 0, 0
    lfd f31, 0xc0(r1)
    psq_l f30, 184(r1), 0, 0
    lfd f30, 0xb0(r1)
    psq_l f29, 168(r1), 0, 0
    lfd f29, 0xa0(r1)
    psq_l f28, 152(r1), 0, 0
    addi r11, r1, 0x90
    lfd f28, 0x90(r1)
L_b8a0:
    bl _restgpr_23
    lwz r0, 0xd4(r1)
    mtlr r0
    addi r1, r1, 0xd0
    blr 
}

extern "C" asm void onTiEvent__Q39textinput9inputform12EventHandlerFPQ39textinput3gui13PaneComponentUlPQ49textinput11nw4rmanager14TiEventHandler5Input() {
    nofralloc
    stwu r1, -0x70(r1)
    mflr r0
    stw r0, 0x74(r1)
    addi r11, r1, 0x70
L_b950:
    bl _savegpr_26
    lwz r7, 0x9c(r4)
    lis r31, lbl_8165C820@l
    lfs f0, 4(r6)
    mr r26, r3
    addi r30, r7, 0xb4
    mr r27, r4
    stfs f0, 8(r1)
    mr r28, r5
    mr r29, r6
    addi r31, r31, lbl_8165C820@ha
    lfs f0, 8(r6)
    fneg f0, f0
    stfs f0, 0xc(r1)
    lbz r0, 0xb4(r7)
    extsb r0, r0
    cmpwi r0, 0x42
    bne L_be00
    mr r5, r30
    addi r3, r1, 0x40
    li r4, 0x11
    li r6, 0
    li r7, 0x50
L_b9ac:
    bl replaceChar__Q29textinput4utilFPcUlPCcic
    cmplwi r28, 4
    bne L_bb30
    lwz r0, 0xc(r29)
    rlwinm. r0, r0, 0, 0x14, 0x14
    beq L_bb30
    lwz r3, 0xc(r26)
    lwz r12, 0(r3)
    lwz r12, 0x120(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    bne L_bb30
    lwz r3, 0xc(r26)
    lwz r12, 0(r3)
    lwz r12, 0x22c(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_ba88
    addi r3, r31, 0x3f4
    addi r4, r1, 0x40
L_ba04:
    bl strcmp__Q29textinput4utilFPCcPCc
    cmpwi r3, 0
    beq L_ba88
    li r0, 0
    stw r0, 0x34(r1)
    stw r0, 0x38(r1)
    stw r0, 0x3c(r1)
    lwz r3, 0xc(r26)
    addi r3, r3, 0x10
    lwz r12, 0x4c(r3)
    lwz r12, 0x28(r12)
    mtctr r12
    bctrl 
    stfs f1, 0x3c(r1)
    addi r5, r1, 0x34
    li r4, 0x18
    lwz r3, 0xc(r26)
    lwz r12, 0(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
    lwz r3, 0xc(r26)
    addi r4, r1, 0x40
    lwzu r12, 0x218(r3)
    lwz r12, 0x60(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    li r4, 0
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl 
    b L_bb30
L_ba88:
    lwz r3, 0xc(r26)
    lwz r12, 0(r3)
    lwz r12, 0x230(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_bb30
    addi r3, r31, 0x408
    addi r4, r1, 0x40
L_baac:
    bl strcmp__Q29textinput4utilFPCcPCc
    cmpwi r3, 0
    beq L_bb30
    li r0, 0
    stw r0, 0x28(r1)
    stw r0, 0x2c(r1)
    stw r0, 0x30(r1)
    lwz r3, 0xc(r26)
    addi r3, r3, 0x10
    lwz r12, 0x4c(r3)
    lwz r12, 0x28(r12)
    mtctr r12
    bctrl 
    fneg f0, f1
    addi r5, r1, 0x28
    li r4, 0x18
    stfs f0, 0x30(r1)
    lwz r3, 0xc(r26)
    lwz r12, 0(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
    lwz r3, 0xc(r26)
    addi r4, r1, 0x40
    lwzu r12, 0x218(r3)
    lwz r12, 0x60(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    li r4, 0
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl 
L_bb30:
    cmplwi r28, 2
    bne L_bd60
    lwz r0, 0x10(r29)
    rlwinm. r0, r0, 0, 0x14, 0x14
    beq L_bd60
    lwz r0, 0xc(r29)
    rlwinm. r0, r0, 0, 0x14, 0x14
    bne L_bd60
    lwz r3, 0xc(r26)
    lwz r12, 0(r3)
    lwz r12, 0x22c(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_bc58
    addi r3, r31, 0x3f4
    addi r4, r1, 0x40
L_bb74:
    bl strcmp__Q29textinput4utilFPCcPCc
    cmpwi r3, 0
    beq L_bc58
    lwz r12, 0(r27)
    mr r3, r27
    lwz r4, 0(r29)
    lwz r12, 0x28(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_bd60
    lwz r3, 0xc(r26)
    mr r5, r30
    lwzu r12, 0x218(r3)
    lwz r4, 0(r29)
    lwz r12, 0x34(r12)
    mtctr r12
    bctrl 
    cmplwi r3, 0x3c
    blt L_bd60
    lis r4, -0x3333
    addi r0, r4, -0x3333
    mulhwu r0, r0, r3
    srwi r0, r0, 4
    mulli r0, r0, 0x14
    subf. r0, r0, r3
    bne L_bd60
    li r0, 0
    stw r0, 0x1c(r1)
    stw r0, 0x20(r1)
    stw r0, 0x24(r1)
    lwz r3, 0xc(r26)
    addi r3, r3, 0x10
    lwz r12, 0x4c(r3)
    lwz r12, 0x28(r12)
    mtctr r12
    bctrl 
    stfs f1, 0x24(r1)
    addi r5, r1, 0x1c
    li r4, 0x18
    lwz r3, 0xc(r26)
    lwz r12, 0(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
    lwz r3, 0xc(r26)
    addi r4, r1, 0x40
    lwzu r12, 0x218(r3)
    lwz r12, 0x60(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    li r4, 0
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl 
    b L_bd60
L_bc58:
    lwz r3, 0xc(r26)
    lwz r12, 0(r3)
    lwz r12, 0x230(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_bd60
    addi r3, r31, 0x408
    addi r4, r1, 0x40
L_bc7c:
    bl strcmp__Q29textinput4utilFPCcPCc
    cmpwi r3, 0
    beq L_bd60
    lwz r12, 0(r27)
    mr r3, r27
    lwz r4, 0(r29)
    lwz r12, 0x28(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_bd60
    lwz r3, 0xc(r26)
    mr r5, r30
    lwzu r12, 0x218(r3)
    lwz r4, 0(r29)
    lwz r12, 0x34(r12)
    mtctr r12
    bctrl 
    cmplwi r3, 0x3c
    blt L_bd60
    lis r4, -0x3333
    addi r0, r4, -0x3333
    mulhwu r0, r0, r3
    srwi r0, r0, 4
    mulli r0, r0, 0x14
    subf. r0, r0, r3
    bne L_bd60
    li r0, 0
    stw r0, 0x10(r1)
    stw r0, 0x14(r1)
    stw r0, 0x18(r1)
    lwz r3, 0xc(r26)
    addi r3, r3, 0x10
    lwz r12, 0x4c(r3)
    lwz r12, 0x28(r12)
    mtctr r12
    bctrl 
    fneg f0, f1
    addi r5, r1, 0x10
    li r4, 0x18
    stfs f0, 0x18(r1)
    lwz r3, 0xc(r26)
    lwz r12, 0(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
    lwz r3, 0xc(r26)
    addi r4, r1, 0x40
    lwzu r12, 0x218(r3)
    lwz r12, 0x60(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r3)
    li r4, 0
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl 
L_bd60:
    lwz r3, 0xc(r26)
    addi r4, r1, 0x40
    lwzu r12, 0x218(r3)
    lwz r12, 0x60(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    mr r27, r3
    beq L_bfb4
    cmpwi r28, 1
    beq L_bd9c
    bge L_bfb4
    cmpwi r28, 0
    bge L_bdb4
    b L_bfb4
L_bd9c:
    lwz r12, 0(r3)
    li r4, 2
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl 
    b L_bfb4
L_bdb4:
    lwz r12, 0(r3)
    lwz r12, 0x28(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 7
    beq L_bfb4
    lwz r3, 8(r26)
    li r4, 4
    lwz r12, 0(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r27)
    mr r3, r27
    li r4, 1
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl 
    b L_bfb4
L_be00:
    cmpwi r0, 0x50
    bne L_bedc
    lwz r3, 0xc(r3)
    mr r4, r30
    lwzu r12, 0x218(r3)
    lwz r12, 0x60(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    mr r27, r3
    beq L_bfb4
    cmpwi r28, 1
    beq L_be90
    bge L_bfb4
    cmpwi r28, 0
    bge L_be44
    b L_bfb4
L_be44:
    lwz r12, 0(r3)
    lwz r12, 0x28(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 7
    beq L_bfb4
    lwz r3, 8(r26)
    li r4, 4
    lwz r12, 0(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r27)
    mr r3, r27
    li r4, 1
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl 
    b L_bfb4
L_be90:
    lwz r12, 0(r3)
    lwz r12, 0x28(r12)
    mtctr r12
    bctrl 
    cmpwi r3, 7
    beq L_bfb4
    lwz r3, 8(r26)
    li r4, 4
    lwz r12, 0(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl 
    lwz r12, 0(r27)
    mr r3, r27
    li r4, 2
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl 
    b L_bfb4
L_bedc:
    lwz r27, 0xc(r3)
    lwz r12, 0x218(r27)
    addi r3, r27, 0x218
    lwz r4, 0x2c4(r27)
    lwz r12, 0x30(r12)
    lwz r4, 8(r4)
    mtctr r12
    bctrl 
    cmpwi r3, 0
    beq L_bf10
    lwz r3, 0x2c4(r27)
    lwz r4, 8(r3)
    b L_bf14
L_bf10:
    addi r4, r31, 0x3c0
L_bf14:
    mr r3, r30
L_bf18:
    bl strcmp__Q29textinput4utilFPCcPCc
    cmpwi r3, 0
    beq L_bfb4
    cmplwi r28, 4
    bne L_bf54
    lwz r0, 0xc(r29)
    rlwinm. r0, r0, 0, 0x14, 0x14
    beq L_bf54
    lwz r3, 0xc(r26)
    addi r5, r1, 8
    li r4, 0xe
    lwz r12, 0(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
L_bf54:
    cmplwi r28, 5
    bne L_bf84
    lwz r0, 0x14(r29)
    rlwinm. r0, r0, 0, 0x14, 0x14
    beq L_bf84
    lwz r3, 0xc(r26)
    addi r5, r1, 8
    li r4, 0xf
    lwz r12, 0(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
L_bf84:
    cmplwi r28, 2
    bne L_bfb4
    lwz r0, 0x10(r29)
    rlwinm. r0, r0, 0, 0x14, 0x14
    beq L_bfb4
    lwz r3, 0xc(r26)
    addi r5, r1, 8
    li r4, 0x10
    lwz r12, 0(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl 
L_bfb4:
    addi r11, r1, 0x70
L_bfb8:
    bl _restgpr_26
    lwz r0, 0x74(r1)
    mtlr r0
    addi r1, r1, 0x70
    blr 
}

extern "C" asm void onAnmEvent__Q39textinput9inputform19NormalButtonAnmPaneFQ49textinput11nw4rmanager7AnmPane12AnmPaneEvent() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    cmpwi r4, 6
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 8(r1)
    mr r30, r3
    bne L_c03c
    lwz r0, 0x2c(r3)
    cmpwi r0, 7
    bne L_c03c
    lwz r12, 0(r3)
    li r4, 5
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl 
    b L_c08c
L_c03c:
    cmpwi r4, 7
    bne L_c06c
    lwz r0, 0x2c(r3)
    cmpwi r0, 7
    beq L_c06c
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 6
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl 
    b L_c08c
L_c06c:
    cmpwi r4, 0
    bne L_c08c
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 4
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl 
L_c08c:
    lwz r0, 0x2c(r30)
    cmplwi r0, 6
    bgt L_c228
    lis r3, jumptable_8165CC5C@l
    slwi r0, r0, 2
    addi r3, r3, jumptable_8165CC5C@ha
    lwzx r3, r3, r0
    mtctr r3
    bctr 
    cmpwi r31, 4
    bne L_c0d0
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 0
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl 
L_c0d0:
    cmpwi r31, 1
    bne L_c228
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 1
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl 
    b L_c228
    cmpwi r31, 1
    bne L_c228
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 1
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl 
    b L_c228
    cmpwi r31, 4
    bne L_c138
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 3
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl 
L_c138:
    cmpwi r31, 2
    bne L_c228
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 2
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl 
    b L_c228
    cmpwi r31, 2
    bne L_c228
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 2
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl 
    b L_c228
    cmpwi r31, 4
    bne L_c1a0
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 0
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl 
L_c1a0:
    cmpwi r31, 1
    bne L_c228
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 1
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl 
    b L_c228
    cmpwi r31, 4
    bne L_c1e4
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 3
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl 
L_c1e4:
    cmpwi r31, 2
    bne L_c228
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 2
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl 
    b L_c228
    cmpwi r31, 4
    bne L_c228
    lwz r12, 0(r30)
    mr r3, r30
    li r4, 7
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl 
L_c228:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr 
}

extern "C" const char lbl_8165D258[] = "OutOfLength\n";
extern "C" const char lbl_8165D2D0[] = "Error#004\nAn error has occurred.\nThe system files are corrupted.";
}
}
