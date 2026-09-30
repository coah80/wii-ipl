#define TIINPUTFORM_IMPLEMENTATION
#include "keyboard/tiInputForm.h"
#include "keyboard/tiManager.h"
#include "keyboard/tiDebug.h"
#include "keyboard/tiLayoutGather.h"

#include <revolution/mtx.h>
#include <wchar.h>
#include <new>

namespace textinput {
namespace inputform {

struct VisiblePanes {
    u16 visibleCount;
    u16 hiddenCount;
    const char* visibleNames[4];
    const char* hiddenNames[4];
};

struct LanguagePaneData {
    const VisiblePanes* visibility;
    const char* separator;
    const char* textBox;
    const char* title;
};

enum Animation {
    ANM_Normal,
    ANM_FocusIn,
    ANM_FocusOut,
    ANM_RollOver,
    ANM_Pushed,
    ANM_FadeIn,
    ANM_FadeOut,
    ANM_Off
};

enum KeyType {
    KT_NormalButton
};

class AnmPane : public nw4rmanager::AnmPane {
public:
    AnmPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer) : nw4rmanager::AnmPane(pane, observer), meState(ANM_Normal) {}
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
    NormalButtonAnmPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer) : AnmPane(pane, observer) { meKeyType = KT_NormalButton; }
    virtual ~NormalButtonAnmPane();
    virtual void onAnmEvent(AnmPaneEvent event);
};

class EventHandler : public nw4rmanager::TiEventHandler {
public:
    EventHandler(LayoutByNW4R* form) : mpInputForm(form) {}
    virtual ~EventHandler();
    virtual void onTiEvent(gui::PaneComponent* component, u32 event, Input* input);
private:
    LayoutByNW4R* mpInputForm;
};

nw4r::ut::Color csUnInputedWCharColor(200, 50, 50, 255);
nw4r::ut::Color csCharColor(20, 20, 20, 255);
nw4r::ut::Color csZiStringColorLeft(255, 50, 50, 255);
nw4r::ut::Color csZiStringNonSelectColorRight(192, 192, 192, 255);
nw4r::ut::Color csZiStringColorRight(50, 100, 50, 255);
nw4r::ut::Color csUnderlateColor(100, 200, 200, 255);
nw4r::ut::Color csUnInputedWCharColorSpace(255, 20, 20, 255);

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
void Base::inputCharDefault_(wchar_t character, u32 modifiers) {
    tistring::WithAtok* unfix;
    tistring::Decolated* current = getCurrentString(true);
    unfix = mpUnfixString;
    if (getCurrentString(false) == unfix && !unfix->isConverting() && mpUnfixString->getSelectedCandidate() >= 0) {
        confirmInput_();
    }
    if (meLanguage == KR && mpManager->getPCKeyboard()->getTranslateMode() != keyboard::pctype::Base::TM_00) {
        if (util::isAlphabet(character) && (modifiers & 2)) character = util::reverseLetterCaseW(character);
    }
    if (mpString == current) {
        mpString->getCursorPos();
        mpString->inputChar(character);
        mpString->getCursorPos();
        if (meLanguage == CN) {
            bool predicted;
            if (!mbPredictOn) predicted = false;
            else if (mePredictMode != PM_Atok && mpZiString->getCurrentNumPredicted() > 0) predicted = true;
            else predicted = false;
            if (predicted) {
                mpZiString->setCurrentWord(NULL);
                mpZiString->update();
            }
        }
    } else current->inputChar(character);
    if (character == L' ') onSE(static_cast<sound::SE>(9));
    else if (character != L'\n') onSE(static_cast<sound::SE>(10));
    meScrollFlag = SF_ScrollOn;
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
void Base::calcCursorTimer() {
    muCursorTimer += 8;
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
void Base::dirtyCacheAll() {
    dirtyCursorCache();
    dirtyDrawCache();
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
struct ButtonAnimations {
    KeyType type;
    const char* paneName;
    u32 count;
    const char* bindingName;
    const InputFormAnimationFile* files[12];
};

const char* csScrollButtonAnimationTarget = lbl_8165C820;

const ButtonAnimations csButtonAnimations[] = {
    {KT_NormalButton, lbl_8165C820, 8, NULL, {
        &csAninationFile__Q29textinput9inputform[0], &csAninationFile__Q29textinput9inputform[1],
        &csAninationFile__Q29textinput9inputform[2], &csAninationFile__Q29textinput9inputform[3],
        &csAninationFile__Q29textinput9inputform[4], &csAninationFile__Q29textinput9inputform[5],
        &csAninationFile__Q29textinput9inputform[6], &csAninationFile__Q29textinput9inputform[7]}},
    {KT_NormalButton, lbl_8165C830, 8, csScrollButtonAnimationTarget, {
        &csAninationFile__Q29textinput9inputform[0], &csAninationFile__Q29textinput9inputform[1],
        &csAninationFile__Q29textinput9inputform[2], &csAninationFile__Q29textinput9inputform[3],
        &csAninationFile__Q29textinput9inputform[4], &csAninationFile__Q29textinput9inputform[5],
        &csAninationFile__Q29textinput9inputform[6], &csAninationFile__Q29textinput9inputform[7]}}
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
bool DeadKeyStream::sbCompatibleFilterEnabled = true;

inline bool DeadKeyStream::isCompatible(wchar_t character) {
    const wchar_t excluded[] = {
        0x00a4, 0x00ac, 0x00af, 0x00b2, 0x00b3, 0x00b6, 0x00b8, 0x00b9,
        0x00bc, 0x00bd, 0x00be, 0x00d0, 0x00de, 0x00f0, 0x00fe, 0x0000
    };
    if (character < excluded[0] || character > excluded[14]) return true;
    for (u32 index = 0; index < 15; ++index) {
        if (character == excluded[index]) return false;
    }
    return true;
}

inline wchar_t DeadKeyStream::getChar() {
    wchar_t character = KPRGetChar(&mKPRQueue);
    if (sbCompatibleFilterEnabled) {
        while (!isCompatible(character)) character = KPRGetChar(&mKPRQueue);
    }
    return character;
}

wchar_t DeadKeyStream::ToIndependentClass(wchar_t code) {
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

struct CharacterInput {
    wchar_t character;
    u32 modifiers;
    bool keyboardMode;
    bool deadKey;
};

struct ConfirmInput {
    wchar_t character;
    u16 letterMode;
    bool direct;
    bool held;
    bool confirmOnly;
    bool silent;
    void* holdingKey;
};

struct PredictionState {
    Base::PredictMode mode;
    bool enabled;
};

struct ControlInput {
    HVKCode code;
    u32 modifiers;
};

inline bool Base::hasZiPredictions() const {
    if (!mbPredictOn) return false;
    if (mePredictMode != PM_Atok && mpZiString->getCurrentNumPredicted() > 0) return true;
    return false;
}

inline bool Base::usesZiPrediction() const {
    if (!mbPredictOn) return false;
    if (mePredictMode == PM_Atok) return false;
    if (meLanguage == CN && static_cast<const Manager*>(mpManager)->getCandidateBox()->isInvalid()) return false;
    return true;
}

inline void Base::resetPredictionContext() {
    if (mpZiString && meLanguage == CN) {
        mpZiString->setCurrentWord(NULL);
        mpZiString->update();
        updateCandidateState_();
    }
}

inline void Base::resetInputRelation() {
    mpManager->getHWKeyboard()->resetQuoteState();
    mpUnfixString->resetRelation();
    updateCandidateState_();
}

void Base::onCommand(INPUT_COMMAND command, void* data) {
    CommandReceiver::onCommand(command, data);
    tistring::Decolated* current = getCurrentString(false);
    tistring::Decolated* fixed = mpString;
    bool currentIsFixed = current == fixed;
    switch (command) {
    case 40:
        if (current == mpUnfixString) {
            if (LayoutGather::Singleton::getInstance().isHoldingShift()) onPressUp();
            else onPressDown();
            return;
        }
        if (mDKStream.lookAhead()) mDKStream.putChar(0xffff);
        else mDKStream.putChar(L' ');
        if (mDKStream.isEmpty()) onSE(static_cast<sound::SE>(10));
        {
            tistring::WithAtok* unfix = mpUnfixString;
            if (getCurrentString(false) == unfix) unfix->isConverting();
        }
        for (;;) {
            wchar_t character = mDKStream.getChar();
            if (!character) break;
            if (usesZiPrediction()) inputCharZi_(character, 0);
            else inputCharDefault_(character, 0);
        }
        break;
    case 0: {
        CharacterInput* input = static_cast<CharacterInput*>(data);
        wchar_t character = input->character;
        u32 modifiers = input->modifiers;
        tistring::Decolated::TranslateMode savedMode = current->getTranslateMode();
        bool savedFix = false;
        bool savedKana = false;
        if (input->keyboardMode) {
            tistring::Decolated::TranslateMode keyboardMode = static_cast<tistring::Decolated::TranslateMode>(mpManager->getPCKeyboard()->getTranslateMode());
            bool direct = mpManager->getPCKeyboard()->getTranslateMode() == keyboard::pctype::Base::TM_00;
            bool kana = mpManager->getPCKeyboard()->getTranslateMode() == keyboard::pctype::Base::TM_Kana;
            tistring::Decolated* active = getCurrentString(false);
            savedMode = active->getTranslateMode();
            if (active == mpString) {
                tistring::Decolated::TranslateMode mode = keyboardMode;
                if (meLanguage == KR) {
                    if (mode != tistring::Decolated::TM_Direct) mode = tistring::Decolated::TM_Hangul;
                } else if (meLanguage == CN) mode = tistring::Decolated::TM_Direct;
                mpString->getCursorPos();
                mpString->setTranslateMode(mode);
                mpString->getCursorPos();
            } else active->setTranslateMode(keyboardMode);
            bool useAtok;
            if (!mbPredictOn) useAtok = false;
            else useAtok = mePredictMode == PM_Atok;
            if (useAtok) {
                mpUnfixString->setFixMode(direct);
                mpUnfixString->changeKanaMode(kana);
            }
        }
        if (input->deadKey) character = DeadKeyStream::ToCombineClass(meLanguage, character);
        if (character == L' ' && mDKStream.lookAhead()) mDKStream.putChar(0xffff);
        else mDKStream.putChar(character);
        if (mDKStream.isEmpty()) onSE(static_cast<sound::SE>(10));
        {
            tistring::WithAtok* unfix = mpUnfixString;
            if (getCurrentString(false) == unfix) unfix->isConverting();
        }
        for (;;) {
            wchar_t queued = mDKStream.getChar();
            if (!queued) break;
            if (usesZiPrediction()) inputCharZi_(queued, modifiers);
            else inputCharDefault_(queued, modifiers);
        }
        if (current == mpZiString) mbZuSelected = false;
        if (input->keyboardMode) {
            tistring::Decolated* active = getCurrentString(false);
            if (active == mpString) {
                tistring::Decolated::TranslateMode mode = savedMode;
                if (meLanguage == KR) {
                    if (mode != tistring::Decolated::TM_Direct) mode = tistring::Decolated::TM_Hangul;
                } else if (meLanguage == CN) mode = tistring::Decolated::TM_Direct;
                mpString->getCursorPos();
                mpString->setTranslateMode(mode);
                mpString->getCursorPos();
            } else active->setTranslateMode(savedMode);
            bool useAtok;
            if (!mbPredictOn) useAtok = false;
            else useAtok = mePredictMode == PM_Atok;
            if (useAtok) {
                mpUnfixString->setFixMode(savedFix);
                mpUnfixString->changeKanaMode(savedKana);
            }
        }
        if (checkHeadOfSentence(true)) onCommand(static_cast<INPUT_COMMAND>(33), NULL);
        break;
    }
    case 1:
        if (!current->canBackSpace()) onSE(static_cast<sound::SE>(8));
        else onSE(static_cast<sound::SE>(7));
        if (current == mpString) {
            resetInputRelation();
            mpString->getCursorPos();
            mpString->backSpace();
            if (mpManager->getCellPhoneKeyboard()) mpManager->getCellPhoneKeyboard()->resetHoldingButton();
            mpString->getCursorPos();
            getCurrentString(false);
            resetPredictionContext();
        } else if (current == mpZiString) {
            mbZuSelected = false;
            current->backSpace();
            if (mpManager->getCellPhoneKeyboard()) mpManager->getCellPhoneKeyboard()->resetHoldingButton();
        } else {
            if (!mpUnfixString->isConverting()) {
                mpUnfixString->backSpace();
                if (mpManager->getCellPhoneKeyboard()) mpManager->getCellPhoneKeyboard()->resetHoldingButton();
            }
            updateCandidateState_();
        }
        meScrollFlag = SF_ScrollByBS;
        if (checkHeadOfSentence(true)) onCommand(static_cast<INPUT_COMMAND>(33), NULL);
        break;
    case 2:
        if (!currentIsFixed) {
            onSE(static_cast<sound::SE>(8));
            return;
        }
        if (!fixed->deleteForward()) onSE(static_cast<sound::SE>(8));
        else onSE(static_cast<sound::SE>(7));
        break;
    case 7:
        if (currentIsFixed) {
            if (meLanguage == KR) {
                tistring::Decolated* active = getCurrentString(false);
                if (!active->isKanaFix()) {
                    mpString->getCursorPos();
                    mpString->inputChar(L'\n');
                    mpString->getCursorPos();
                    if (meLanguage == CN && hasZiPredictions()) {
                        mpZiString->setCurrentWord(NULL);
                        mpZiString->update();
                    }
                }
            }
            resetInputRelation();
            bool lineFeed;
            if (!mpManager->getToolBar()->isQwerty()) lineFeed = mpManager->getCellPhoneKeyboard()->hasLineFeedButton();
            else lineFeed = mpManager->getPCKeyboard()->hasLineFeedButton();
            bool allowed = true;
            if (mpString->isKanaFix()) {
                bool withinLimit = false;
                if (lineFeed && static_cast<u32>(getLine() + 1) <= muLimitRowNum) withinLimit = true;
                if (!withinLimit) allowed = false;
            }
            bool atLimit = true;
            if (static_cast<u32>(getLine() + 1) <= muLimitRowNum && !mpManager->getCandidateBox()->isActive()) atLimit = false;
            if (!allowed) {
                if (atLimit) onSE(static_cast<sound::SE>(8));
                return;
            }
            onSE(static_cast<sound::SE>(9));
            mpString->getCursorPos();
            mpString->inputChar(L'\n');
            mpString->getCursorPos();
            if (meLanguage == CN && hasZiPredictions()) {
                mpZiString->setCurrentWord(NULL);
                mpZiString->update();
            }
        } else if (current == mpZiString) {
            onSE(static_cast<sound::SE>(9));
            if (getPredictMode() == PM_11 || getPredictMode() == PM_12) confirmInput_();
            else if (!(mbCursorSelected | mbZuSelected) && mpManager->getToolBar()->isQwerty()) {
                if (mbPredictOn && mePredictMode != PM_Atok) {
                    wchar_t input[64];
                    mpZiString->getCurrentInput(input, 64);
                    mpString->getCursorPos();
                    mpString->inputString(input);
                    mpString->getCursorPos();
                    mpZiString->clearCandidates();
                    mbZuSelected = false;
                    getCurrentString(false);
                    resetPredictionContext();
                }
            } else confirmInput_();
        } else {
            onSE(static_cast<sound::SE>(9));
            if (!mpUnfixString->isConverting()) confirmInput_();
            else {
                mpUnfixString->commitPredicted(mpUnfixString->getSelectedConverting());
                updateCandidateState_();
            }
        }
        meScrollFlag = SF_ScrollOn;
        if (checkHeadOfSentence(true)) onCommand(static_cast<INPUT_COMMAND>(33), NULL);
        break;
    case 6:
        confirmInput_();
        meScrollFlag = SF_ScrollOn;
        break;
    case 3:
        if (mePredictMode == PM_11 && current == mpZiString) mbZuSelected = false;
        inputInputting_(*static_cast<wchar_t*>(data));
        break;
    case 5: {
        ConfirmInput* input = static_cast<ConfirmInput*>(data);
        if (!input->character) return;
        confirmInputting_(input->character, input->direct, input->letterMode, input->confirmOnly, input->holdingKey);
        if (!input->silent) {
            if (!input->confirmOnly) onSE(static_cast<sound::SE>(10));
            else onSE(static_cast<sound::SE>(9));
        }
        meScrollFlag = SF_ScrollOn;
        if (checkHeadOfSentence(true)) onCommand(static_cast<INPUT_COMMAND>(33), NULL);
        break;
    }
    case 8:
        if (currentIsFixed) onPressLeft();
        else onHKBCtrlCode(static_cast<HVKCode>(31), 0);
        return;
    case 9:
        if (currentIsFixed) onPressRight();
        else onHKBCtrlCode(static_cast<HVKCode>(32), 0);
        return;
    case 10: onPressUp(); return;
    case 11: onPressDown(); return;
    case 14:
        if (currentIsFixed && current->isKanaFix()) {
            nw4r::math::VEC2 origin = getGlobalLeftTopPos();
            nw4r::math::VEC2* cursor = static_cast<nw4r::math::VEC2*>(data);
            current->setCursorPos(calcCursorPos(cursor->x - origin.x, cursor->y - origin.y));
            onSE(static_cast<sound::SE>(5));
            onCommand(static_cast<INPUT_COMMAND>(12), NULL);
            resetInputRelation();
        } else {
            onSE(static_cast<sound::SE>(9));
            onCommand(static_cast<INPUT_COMMAND>(6), NULL);
        }
        return;
    case 15:
        if (current->isOnSustain()) {
            nw4r::math::VEC2 origin = getGlobalLeftTopPos();
            nw4r::math::VEC2* cursor = static_cast<nw4r::math::VEC2*>(data);
            current->setCursorPos(calcCursorPos(cursor->x - origin.x, cursor->y - origin.y));
            onCommand(static_cast<INPUT_COMMAND>(13), NULL);
        }
        return;
    case 16:
        if (current->isOnSustain()) {
            nw4r::math::VEC2 origin = getGlobalLeftTopPos();
            u32 previous, end;
            current->getCursorPos(&previous, &end);
            nw4r::math::VEC2* cursor = static_cast<nw4r::math::VEC2*>(data);
            u32 position = calcCursorPos(cursor->x - origin.x, cursor->y - origin.y);
            current->setCursorPos(position);
            if (previous != position) onSE(static_cast<sound::SE>(5));
            meScrollFlag = SF_ScrollOn;
        }
        return;
    case 17:
        if (data && *static_cast<bool*>(data)) {
            mpUnfixString->confirm(NULL);
            onCommand(static_cast<INPUT_COMMAND>(6), NULL);
            resetCandidate();
            updateCandidate();
        }
        break;
    case 18: {
        tistring::Decolated::TranslateMode mode = *static_cast<tistring::Decolated::TranslateMode*>(data);
        if (meLanguage != JP && meLanguage != KR) mode = tistring::Decolated::TM_Direct;
        tistring::Decolated::TranslateMode fixedMode = mode;
        if (meLanguage == KR) {
            if (mode != tistring::Decolated::TM_Direct) fixedMode = tistring::Decolated::TM_Hangul;
        } else if (meLanguage == CN) fixedMode = tistring::Decolated::TM_Direct;
        fixed->getCursorPos();
        mpString->setTranslateMode(fixedMode);
        mpString->getCursorPos();
        mpUnfixString->setTranslateMode(mode);
        break;
    }
    case 19: mpUnfixString->changeKanaMode(*static_cast<bool*>(data)); break;
    case 20: mpUnfixString->setFixMode(*static_cast<bool*>(data)); break;
    case 21: {
        s32 index = *static_cast<s32*>(data);
        if (mbPredictOn) {
            if (mePredictMode == PM_Atok) {
                if (!mpUnfixString->isConverting()) {
                    wchar_t predicted[96];
                    mpUnfixString->getPredicted(index, predicted);
                    mpString->getCursorPos();
                    mpString->inputString(predicted, tistring::Decolated::TM_Direct);
                    mpString->getCursorPos();
                    mpUnfixString->commitPredicted(index);
                } else mpUnfixString->commitPredicted(index);
            } else {
                wchar_t predicted[64];
                mpZiString->getPredicted(index, predicted);
                mpString->getCursorPos();
                mpString->inputString(predicted);
                mpString->getCursorPos();
                mpZiString->clearCandidates();
                mbZuSelected = false;
                if (meLanguage == CN) {
                    mpZiString->setCurrentWord(predicted);
                    mpZiString->update();
                }
            }
        }
        meScrollFlag = SF_ScrollOn;
        break;
    }
    case 22:
        moveCandidateToIdx(*static_cast<s32*>(data));
        meScrollFlag = SF_ScrollOn;
        return;
    case 23:
        if (!mbPredictOn) break;
        if (mePredictMode == PM_Atok) mpUnfixString->setSelectedCandidate(-1);
        else if (mePredictMode == PM_11) {
            mpZiString->setSelectedCandidate(-1);
            mbZuSelected = false;
        }
        meScrollFlag = SF_ScrollOn;
        return;
    case 24: doScroll(static_cast<Scroll*>(data)); return;
    case 25: current->converDakuten(); onSE(static_cast<sound::SE>(10)); break;
    case 26: current->converHandaku(); onSE(static_cast<sound::SE>(10)); break;
    case 27: current->convertAll(); break;
    case 28: current->converSmall(); onSE(static_cast<sound::SE>(10)); break;
    case 29: {
        PredictionState* prediction = static_cast<PredictionState*>(data);
        mePredictMode = prediction->mode;
        bool enabled = prediction->enabled != false;
        if (mbPredictOn != enabled) {
            mbPredictOn = enabled;
            if (meLanguage == KR) mpManager->getPCKeyboard()->refreshState();
        }
        tistring::Decolated::TranslateMode fixedMode = mpString->getTranslateMode();
        tistring::Decolated::TranslateMode unfixMode = mpUnfixString->getTranslateMode();
        mpString->initKanaConverter();
        mpUnfixString->initKanaConverter();
        if (meLanguage == KR) {
            if (fixedMode != tistring::Decolated::TM_Direct) fixedMode = tistring::Decolated::TM_Hangul;
        } else if (meLanguage == CN) fixedMode = tistring::Decolated::TM_Direct;
        mpString->getCursorPos();
        mpString->setTranslateMode(fixedMode);
        mpString->getCursorPos();
        mpUnfixString->setTranslateMode(unfixMode);
        switch (mePredictMode) {
        case PM_Atok:
            if (!mbPredictOn) {
                if (mpUnfixString->isDictionaryOpened() && current == mpUnfixString) {
                    mpUnfixString->confirm(NULL);
                    wchar_t* confirmed = mpUnfixString->getConfirmedWCString();
                    mpString->getCursorPos();
                    mpString->confirm(confirmed);
                    mpString->getCursorPos();
                    mpUnfixString->enableConfirmedString(false);
                }
            } else resetInputRelation();
            return;
        case PM_USEn: mpZiString->setPredictLaunguage(static_cast<tistring::WithZi::PredictLanguage>(0)); break;
        case PM_USFr: mpZiString->setPredictLaunguage(static_cast<tistring::WithZi::PredictLanguage>(1)); break;
        case PM_USSp: mpZiString->setPredictLaunguage(static_cast<tistring::WithZi::PredictLanguage>(2)); break;
        case PM_En: mpZiString->setPredictLaunguage(static_cast<tistring::WithZi::PredictLanguage>(3)); break;
        case PM_De: mpZiString->setPredictLaunguage(static_cast<tistring::WithZi::PredictLanguage>(4)); break;
        case PM_Fr: mpZiString->setPredictLaunguage(static_cast<tistring::WithZi::PredictLanguage>(5)); break;
        case PM_Sp: mpZiString->setPredictLaunguage(static_cast<tistring::WithZi::PredictLanguage>(6)); break;
        case PM_It: mpZiString->setPredictLaunguage(static_cast<tistring::WithZi::PredictLanguage>(7)); break;
        case PM_Nl: mpZiString->setPredictLaunguage(static_cast<tistring::WithZi::PredictLanguage>(8)); break;
        case PM_11: mpZiString->setPredictLaunguage(static_cast<tistring::WithZi::PredictLanguage>(9)); break;
        case PM_12:
            mpZiString->setPredictLaunguage(static_cast<tistring::WithZi::PredictLanguage>(mpManager->getToolBar()->isQwerty() ? 10 : 11));
            break;
        }
        onCommand(static_cast<INPUT_COMMAND>(30), NULL);
        return;
    }
    case 30: {
        mpUnfixString->confirm(NULL);
        wchar_t* confirmed = mpUnfixString->getConfirmedWCString();
        mpString->getCursorPos();
        mpString->confirm(confirmed);
        mpString->getCursorPos();
        mpUnfixString->enableConfirmedString(false);
        mpZiString->clearCandidates();
        mbZuSelected = false;
        getCurrentString(false);
        resetPredictionContext();
        resetCandidate();
        return;
    }
    case 31: {
        PredictionState* prediction = static_cast<PredictionState*>(data);
        prediction->mode = mePredictMode;
        prediction->enabled = mbPredictOn;
        return;
    }
    case 32: *static_cast<bool*>(data) = hasZiPredictions(); return;
    case 36: {
        u32 length = *static_cast<u32*>(data);
        if (length < fixed->getLength()) mpString->getLength();
        mpString->setLength(static_cast<u16>(length));
        return;
    }
    case 38: {
        ControlInput* input = static_cast<ControlInput*>(data);
        onHKBCtrlCode(input->code, input->modifiers);
        return;
    }
    case 39: mDKStream.clear(); return;
    case 41: notifyChangeMode(); return;
    case 42: onPressLeftHWKB(); return;
    case 43: onPressRightHWKB(); return;
    case 44: onPressUp(); return;
    case 45: onPressDownHWKB(); return;
    case 46:
        if (meLanguage == CN && !mpManager->getPCKeyboard()->isQwertyOnly() && mpManager->getPCKeyboard()->isLanguageKeyActive()) {
            if (mpManager->getPCKeyboard()->getTranslateMode() == keyboard::pctype::Base::TM_00) mpManager->getPCKeyboard()->setTranslateMode(keyboard::pctype::Base::TM_Kana);
            else mpManager->getPCKeyboard()->setTranslateMode(keyboard::pctype::Base::TM_00);
        }
        break;
    case 47: return;
    default: break;
    }
    updateCandidateState_();
}

void Base::onHKBCtrlCode(HVKCode code, u32 modifiers) {
    tistring::Decolated* current = getCurrentString(false);
    switch (code) {
    case 2:
        if (mePredictMode == PM_Atok) toggleAtokMode_(0);
        break;
    case 17:
        if (mePredictMode == PM_Atok) {
            if (mpManager->getPCKeyboard()->getTranslateMode() == keyboard::pctype::Base::TM_Kana) {
                mpManager->getPCKeyboard()->setTranslateMode(keyboard::pctype::Base::TM_Roman);
            } else if (mpManager->getPCKeyboard()->getTranslateMode() == keyboard::pctype::Base::TM_Roman) {
                mpManager->getPCKeyboard()->setTranslateMode(keyboard::pctype::Base::TM_Kana);
            }
            toggleAtokMode_(1);
        } else if (meLanguage == KR && !mpManager->getPCKeyboard()->isQwertyOnly() && mpManager->getPCKeyboard()->isLanguageKeyActive()) {
            if (mpManager->getPCKeyboard()->getTranslateMode() == keyboard::pctype::Base::TM_00) {
                mpManager->getPCKeyboard()->setTranslateMode(keyboard::pctype::Base::TM_Kana);
            } else {
                mpManager->getPCKeyboard()->setTranslateMode(keyboard::pctype::Base::TM_00);
            }
        }
        break;
    case 18:
        if (mePredictMode == PM_Atok) {
            if (mpManager->getPCKeyboard()->getTranslateMode() == keyboard::pctype::Base::TM_00 && !mbPredictOn) {
                if (!mpManager->getPCKeyboard()->isQwertyOnly()) onSE(static_cast<sound::SE>(6));
            } else toggleAtokMode_(2);
        }
        break;
    case 36:
        if (mePredictMode == PM_Atok) toggleAtokMode_(0);
        else if (static_cast<u32>(meLanguage) - CN <= 1) {
            if (!mpManager->getPCKeyboard()->isQwertyOnly() && mpManager->getPCKeyboard()->isLanguageKeyActive()) {
                if (mpManager->getPCKeyboard()->getTranslateMode() == keyboard::pctype::Base::TM_00) {
                    mpManager->getPCKeyboard()->setTranslateMode(keyboard::pctype::Base::TM_Kana);
                } else {
                    mpManager->getPCKeyboard()->setTranslateMode(keyboard::pctype::Base::TM_00);
                }
            }
        } else if (mePredictMode != PM_Off && mpManager->getCandidateBox()->isActive()) {
            mpManager->startPredictTurnOn(!mbPredictOn);
        }
        break;
    case 1:
        if (current == mpUnfixString) updateCandidateState_();
        break;
    case 9:
        onCommand(static_cast<INPUT_COMMAND>(7), NULL);
        onCommand(static_cast<INPUT_COMMAND>(39), NULL);
        break;
    case 8:
        onSpaceKeyHWKB(modifiers);
        break;
    case 29:
        onCommand(static_cast<INPUT_COMMAND>(44), NULL);
        break;
    case 30:
        onCommand(static_cast<INPUT_COMMAND>(45), NULL);
        break;
    case 31:
        onCommand(static_cast<INPUT_COMMAND>(42), NULL);
        break;
    case 32:
        onCommand(static_cast<INPUT_COMMAND>(43), NULL);
        break;
    case 16:
        if (mePredictMode == PM_Atok) {
            if (mpManager->getPCKeyboard()->getTranslateMode() == keyboard::pctype::Base::TM_Kana) {
                mpManager->getPCKeyboard()->setTranslateMode(keyboard::pctype::Base::TM_Roman);
            } else if (mpManager->getPCKeyboard()->getTranslateMode() == keyboard::pctype::Base::TM_Roman) {
                mpManager->getPCKeyboard()->setTranslateMode(keyboard::pctype::Base::TM_Kana);
            } else if (!mpManager->getPCKeyboard()->isQwertyOnly()) {
                mpManager->getPCKeyboard()->setTranslateMode(keyboard::pctype::Base::TM_Kana);
            }
        }
        break;
    }
}

LayoutByNW4R::LayoutByNW4R(Manager* manager, nw4r::lyt::MultiArcResourceAccessor* accessor, const char* layout, EventObserver* observer, const char* fontName)
    : Base(manager), nw4rmanager::Layout(accessor, layout, observer), mpLayoutData("T_2l_TextBox"),
      mpLanguageData(csLanguageDependencyDataUEJ__Q29textinput9inputform), mpFontName(fontName),
      mbUpVisible(false), mbDownVisible(false), mbRepeat(false), mpInputEventHandler(NULL) {}

void LayoutByNW4R::create(MEMAllocator* allocator, EditBuffer* editBuffer) {
    mpAllocator = allocator;
    textdrawer::Base::create(allocator);
    mpString = static_cast<tistring::Decolated*>(editBuffer->mpString);
    mpUnfixString = static_cast<tistring::WithAtok*>(editBuffer->mpUnfixString);
    mpZiString = static_cast<tistring::WithZi*>(editBuffer->mpZiString);
    mriManager.mpAllocator = allocator;
    mriManager.mpInfo = static_cast<Info_*>(MEMAllocFromAllocator(allocator, (mriManager.mMaxLength + 2) * sizeof(Info_)));
    mriManager.init();
    Info_* selected = &mriManager.mpInfo[mriManager.mpInfo[mriManager.mMaxLength].Next];
    u16 previous = selected->Back;
    u16 next = selected->Next;
    u16 selectedIndex = mriManager.mpInfo[next].Back;
    mriManager.mpInfo[next].Back = previous;
    mriManager.mpInfo[previous].Next = next;
    selected->Back = selectedIndex;
    selected->Next = selectedIndex;
    Info_* listEnd = &mriManager.mpInfo[mriManager.mpInfo[static_cast<u16>(mriManager.mMaxLength + 1)].Back];
    next = listEnd->Next;
    selected->Back = mriManager.mpInfo[next].Back;
    selected->Next = next;
    listEnd->Next = selectedIndex;
    mriManager.mpInfo[next].Back = selectedIndex;
    selected->StrCount = 0;
    selected->DispRowCount = 1;
    mpCursorLine = selected;
    void* handlerMemory = MEMAllocFromAllocator(allocator, sizeof(EventHandler));
    mpInputEventHandler = handlerMemory ? new (handlerMemory) EventHandler(this) : NULL;
    nw4rmanager::Layout::createWithEventHandler(allocator, mpInputEventHandler);
    if (!mpFontName) {
        mpFontName = "RevoIpl_RodinNTLGProM_32_I4.brfnt";
        mFont.SetResource(mpMultiArcResourceAccessor->GetResource(0, mpFontName, NULL));
        mFont.SetAlternateChar(0xe06b);
        setFont(mFont);
    } else {
        mpMultiArcResourceAccessor->GetFont(mpFontName)->SetAlternateChar(0xe06b);
        setFont(*mpMultiArcResourceAccessor->GetFont(mpFontName));
    }
    nw4r::lyt::TextBox* textBox = static_cast<nw4r::lyt::TextBox*>(mpLayout->GetRootPane()->FindPaneByName(static_cast<const char*>(mpLayoutData), true));
    textBox->SetString(L"", 0);
    mfCharacterSpacing = textBox->GetCharSpace();
    mfLineSpacing = textBox->GetLineSpace();
    mfFontWidth = textBox->GetFontSize().width;
    mfFontHeight = textBox->GetFontSize().height;
    mRect = textBox->GetPaneRect(mDrawInfo);
    AdjustPaneMtx(mMtx.m, mDrawInfo, textBox->GetGlobalMtx());
    csCharColor = textBox->GetTextColor(0);
    setVisible("N_2line", true);
    mpPaneManager->setAllComponentTriggerTarget(false);
    mpPaneManager->setAllBoundingBoxComponentTriggerTarget(true);
    nw4r::lyt::Pane* pane = mpLayout->GetRootPane()->FindPaneByName(static_cast<const LanguagePaneData*>(mpLanguageData)->textBox, true);
    if (!pane) pane = mpLayout->GetRootPane()->FindPaneByName(getLanguageTextPane() ? static_cast<const LanguagePaneData*>(mpLanguageData)->textBox : "T_2l_TextBox", true);
    mpPaneManager->getPaneComponentByPane(pane)->setTriggerTarget(true);
    for (u32 buttonIndex = 0; buttonIndex < 2; ++buttonIndex) {
        nw4rmanager::AnmPane* animationPane = NULL;
        if (csButtonAnimations[static_cast<u16>(buttonIndex)].type == KT_NormalButton) {
            void* memory = MEMAllocFromAllocator(allocator, sizeof(NormalButtonAnmPane));
            if (memory) animationPane = new (memory) NormalButtonAnmPane(getPane(csButtonAnimations[static_cast<u16>(buttonIndex)].paneName), NULL);
        }
        nw4r::ut::List_Append(&mAnmPanes, animationPane);
        const char* bindingName = csButtonAnimations[static_cast<u16>(buttonIndex)].bindingName;
        u32 count = csButtonAnimations[static_cast<u16>(buttonIndex)].count;
        for (u16 animationIndex = 0; animationIndex < count; ++animationIndex) {
            const InputFormAnimationFile* file = csButtonAnimations[static_cast<u16>(buttonIndex)].files[animationIndex];
            void* resource = mpMultiArcResourceAccessor->GetResource(0, file->fileName, NULL);
            AnimTransformPane* transform = static_cast<AnimTransformPane*>(getLayout()->CreateAnimTransform(resource, mpMultiArcResourceAccessor));
            if (!bindingName) animationPane->addAnimation(allocator, file->id, transform, false, true);
            else animationPane->forceAddAnimation(allocator, file->id, transform, bindingName, false, true);
        }
    }
    init();
}
inline const nw4r::lyt::Pane* LayoutByNW4R::getLanguageTextPane() const {
    return getPane(static_cast<const LanguagePaneData*>(mpLanguageData)->textBox);
}

void LayoutByNW4R::init() {
    Base::init();
    searchAnmPane("P_txtScrll_UP")->changeAnimation(7);
    searchAnmPane("P_txtScrll_DOWN")->changeAnimation(7);
    mbUpVisible = false;
    mbDownVisible = false;
    mUpRepeat = 0;
    mDownRepeat = 0;
    mLeftRepeat = 0;
    mRightRepeat = 0;
    mRepeatButtons = 0;
    mCharColor = csCharColor;
    visibleSeparator(false);
    nw4r::lyt::TextBox* textBox = static_cast<nw4r::lyt::TextBox*>(mpLayout->GetRootPane()->FindPaneByName(static_cast<const char*>(mpLayoutData), true));
    textBox->SetString(L"", 0);
    mfCharacterSpacing = textBox->GetCharSpace();
    mfLineSpacing = textBox->GetLineSpace();
    mfFontWidth = textBox->GetFontSize().width;
    mfFontHeight = textBox->GetFontSize().height;
    mRect = textBox->GetPaneRect(mDrawInfo);
    AdjustPaneMtx(mMtx.m, mDrawInfo, textBox->GetGlobalMtx());
    mpLayout->Animate(0);
    mpLayout->CalculateMtx(mDrawInfo);
    const VisiblePanes* visibility = static_cast<const LanguagePaneData*>(mpLanguageData)->visibility;
    for (u16 index = 0; index < visibility->visibleCount; ++index) setVisible(visibility->visibleNames[index], true);
    for (u16 index = 0; index < visibility->hiddenCount; ++index) setVisible(visibility->hiddenNames[index], false);
}
extern "C" const char lbl_8165D2A0[] = "N_separateBarAll";
void LayoutByNW4R::setLanguage(Language language) {
    Base::setLanguage(language);
    if (language == CN) mpLanguageData = csLanguageDependencyDataCHN__Q29textinput9inputform;
    else if (language == KR) mpLanguageData = csLanguageDependencyDataKOR__Q29textinput9inputform;
    else mpLanguageData = csLanguageDependencyDataUEJ__Q29textinput9inputform;
    const char* textName;
    if (!getLanguageTextPane()) textName = "T_2l_TextBox";
    else textName = static_cast<const LanguagePaneData*>(mpLanguageData)->textBox;
    mpLayoutData = textName;
    if (::strcmp(static_cast<const char*>(mpLayoutData), "T_2l_TextBox") != 0) setVisible("T_2l_TextBox", false);
    nw4r::lyt::Pane* pane = mpLayout->GetRootPane()->FindPaneByName(getLanguageTextPane() ? static_cast<const LanguagePaneData*>(mpLanguageData)->textBox : "T_2l_TextBox", true);
    static_cast<nw4r::lyt::TextBox*>(pane)->SetString(L"", 0);
    const VisiblePanes* visibility = static_cast<const LanguagePaneData*>(mpLanguageData)->visibility;
    for (u16 index = 0; index < visibility->visibleCount; ++index) setVisible(visibility->visibleNames[index], true);
    for (u16 index = 0; index < visibility->hiddenCount; ++index) setVisible(visibility->hiddenNames[index], false);
    pane = mpLayout->GetRootPane()->FindPaneByName(getLanguageTextPane() ? static_cast<const LanguagePaneData*>(mpLanguageData)->textBox : "T_2l_TextBox", true);
    mpPaneManager->getPaneComponentByPane(pane)->setTriggerTarget(true);
    if (getPane("T_title_text")) {
        nw4r::lyt::TextBox* title = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(getPane("T_title_text"));
        const char* titleName = static_cast<const LanguagePaneData*>(mpLanguageData)->title;
        if (getPane(titleName)) {
            nw4r::lyt::TextBox* languageTitle = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(getPane(static_cast<const LanguagePaneData*>(mpLanguageData)->title));
            title->SetCharSpace(languageTitle->GetCharSpace());
            title->SetLineSpace(languageTitle->GetLineSpace());
            title->SetFontSize(languageTitle->GetFontSize());
            title->SetTranslate(languageTitle->GetTranslate());
            title->SetSize(languageTitle->GetSize());
        }
    }
}

void LayoutByNW4R::onCommand(INPUT_COMMAND command, void* data) {
    mpEventObserver->onInput(command, data);
    mpEventObserver->onCommand(command, data);
    Base::onCommand(command, data);
    if (command == 31) return;
    u32 limit = muLimitStringLength;
    if (meLanguage == KR) {
        u32 start, end;
        mpString->getCursorPos(&start, &end);
        if (start >= limit && !mpString->isKanaFix()) {
            mpString->clearKana();
            onSE(static_cast<sound::SE>(8));
        }
        if (!mpString->isKanaFix()) limit = muLimitStringLength - 1;
    }
    if (limit < mpString->getLength()) {
        u32 start, end;
        mpString->getCursorPos(&start, &end);
        if (start > limit || end > limit) {
            onSE(static_cast<sound::SE>(8));
            Base::onCommand(static_cast<INPUT_COMMAND>(36), &limit);
        }
    }
    switch (command) {
        case 32:
        case 33:
        case 35:
            break;
        default: {
            u32 trimLimit = limit;
            if (trimLimit < mpString->getLength()) {
                if (mpString->getLength() > trimLimit) mpString->getLength();
                mpString->setLength(static_cast<u16>(trimLimit));
                mpEventObserver->onOutOfLength();
                if (command == 6 || command == 5 || command == 0 || command == 38 || command == 21 || command == 7) {
                    onSE(static_cast<sound::SE>(8));
                }
            }
            break;
        }
    }
    u32 excessPos = isOverRowLimit(muLimitRowNum, mpString->getWCString());
    u32 rowLimit = excessPos;
    if (excessPos) {
        if (mpString->getLength() > excessPos) mpString->getLength();
        mpString->setLength(static_cast<u16>(excessPos));
        mpEventObserver->onOutOfLength();
        onSE(static_cast<sound::SE>(8));
        Base::onCommand(static_cast<INPUT_COMMAND>(36), &rowLimit);
        if (meLanguage == KR && !mpString->isKanaFix()) {
            rowLimit = isOverRowLimit(muLimitRowNum, mpString->getWCString());
            if (rowLimit) mpString->clearKana();
        }
    }
}


#pragma pop

void EventHandler::onTiEvent(gui::PaneComponent* component, u32 event, Input* input) {
    char animationName[17];
    const char* name = component->getPane()->GetName();
    nw4r::math::VEC2 cursor;
    cursor.x = input->x;
    cursor.y = -input->y;
    if (name[0] == 'B') {
        util::replaceChar(animationName, 17, name, 0, 'P');
        if (event == 4 && (input->trigger & 0x800) && !mpInputForm->isInScroll()) {
            if (mpInputForm->isAbleToUp() && util::strcmp("P_txtScrll_UP", animationName)) {
                textdrawer::Base::CursorPos movement = {0, 0.0f, 0.0f};
                movement.fCursorY = mpInputForm->getLineHeight();
                mpInputForm->onCommand(static_cast<CommandReceiver::INPUT_COMMAND>(24), &movement);
                mpInputForm->searchAnmPane(animationName)->onAnmEvent(nw4rmanager::AnmPane::PE_0);
            } else if (mpInputForm->isAbleToDown() && util::strcmp("P_txtScrll_DOWN", animationName)) {
                textdrawer::Base::CursorPos movement = {0, 0.0f, 0.0f};
                movement.fCursorY = -mpInputForm->getLineHeight();
                mpInputForm->onCommand(static_cast<CommandReceiver::INPUT_COMMAND>(24), &movement);
                mpInputForm->searchAnmPane(animationName)->onAnmEvent(nw4rmanager::AnmPane::PE_0);
            }
        }
        if (event == 2 && (input->hold & 0x800) && !(input->trigger & 0x800)) {
            if (mpInputForm->isAbleToUp() && util::strcmp("P_txtScrll_UP", animationName)) {
                if (component->isDragging(input->controller)) {
                    u32 duration = mpInputForm->getFlightDuration(input->controller, name);
                    if (duration >= 60 && duration % 20 == 0) {
                        textdrawer::Base::CursorPos movement = {0, 0.0f, 0.0f};
                        movement.fCursorY = mpInputForm->getLineHeight();
                        mpInputForm->onCommand(static_cast<CommandReceiver::INPUT_COMMAND>(24), &movement);
                        mpInputForm->searchAnmPane(animationName)->onAnmEvent(nw4rmanager::AnmPane::PE_0);
                    }
                }
            } else if (mpInputForm->isAbleToDown() && util::strcmp("P_txtScrll_DOWN", animationName)) {
                if (component->isDragging(input->controller)) {
                    u32 duration = mpInputForm->getFlightDuration(input->controller, name);
                    if (duration >= 60 && duration % 20 == 0) {
                        textdrawer::Base::CursorPos movement = {0, 0.0f, 0.0f};
                        movement.fCursorY = -mpInputForm->getLineHeight();
                        mpInputForm->onCommand(static_cast<CommandReceiver::INPUT_COMMAND>(24), &movement);
                        mpInputForm->searchAnmPane(animationName)->onAnmEvent(nw4rmanager::AnmPane::PE_0);
                    }
                }
            }
        }
        AnmPane* animation = static_cast<AnmPane*>(mpInputForm->searchAnmPane(animationName));
        if (animation) {
            switch (event) {
            case 1: animation->onAnmEvent(nw4rmanager::AnmPane::PE_2); break;
            case 0:
                if (animation->getState() != ANM_Off) {
                    mpEventObserver->onSE(static_cast<sound::SE>(4));
                    animation->onAnmEvent(nw4rmanager::AnmPane::PE_1);
                }
                break;
            }
        }
    } else if (name[0] == 'P') {
        AnmPane* animation = static_cast<AnmPane*>(mpInputForm->searchAnmPane(name));
        if (animation) {
            switch (event) {
            case 0:
                if (animation->getState() != ANM_Off) {
                    mpEventObserver->onSE(static_cast<sound::SE>(4));
                    animation->onAnmEvent(nw4rmanager::AnmPane::PE_1);
                }
                break;
            case 1:
                if (animation->getState() != ANM_Off) {
                    mpEventObserver->onSE(static_cast<sound::SE>(4));
                    animation->onAnmEvent(nw4rmanager::AnmPane::PE_2);
                }
                break;
            }
        }
    } else {
        const char* textPane;
        LayoutByNW4R* form = mpInputForm;
        const nw4rmanager::Layout& layout = *form;
        if (layout.getPane(static_cast<const LanguagePaneData*>(form->mpLanguageData)->textBox)) textPane = static_cast<const LanguagePaneData*>(form->mpLanguageData)->textBox;
        else textPane = "T_2l_TextBox";
        if (util::strcmp(name, textPane)) {
            if (event == 4 && (input->trigger & 0x800)) mpInputForm->onCommand(static_cast<CommandReceiver::INPUT_COMMAND>(14), &cursor);
            if (event == 5 && (input->release & 0x800)) mpInputForm->onCommand(static_cast<CommandReceiver::INPUT_COMMAND>(15), &cursor);
            if (event == 2 && (input->hold & 0x800)) mpInputForm->onCommand(static_cast<CommandReceiver::INPUT_COMMAND>(16), &cursor);
        }
    }
}

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

}

void textinput::util::Animation::startAnm(f32 start, f32 end, f32 duration, AnimObserver* observer, void* data) {
    mfStartPoint = start;
    mfEndPoint = end;
    mfAnimationTime = duration;
    mfCurrentFrame = 0.0f;
    mbInAnimation = true;
    mpAnimObserver = observer;
    mpData = data;
    mbSE = false;
    if (observer) observer->onAnmEvent(AnimObserver::AE_0, data);
}

namespace inputform {

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

void Base::confirmInputting_(wchar_t character, bool direct, u16 letterMode, bool confirmOnly, void* holdingKey) {
    tistring::Decolated* current = getCurrentString(true);
    if (!character) return;
    if (mbPredictOn && getPredictMode() == PM_11) {
        if (!mpManager->getCandidateBox()->isInvalid() && !util::isAlphabet(character) && (character < L'1' || character > L'5')) {
            mpString->getCursorPos();
            mpString->inputChar(character);
            mpString->getCursorPos();
            if (meLanguage == CN) {
                bool predictions;
                if (!mbPredictOn) predictions = false;
                else if (mePredictMode != PM_Atok && mpZiString->getCurrentNumPredicted() > 0) predictions = true;
                else predictions = false;
                if (predictions) {
                    mpZiString->setCurrentWord(NULL);
                    mpZiString->update();
                }
            }
            if (meLanguage == CN) {
                mpZiString->clearCandidates();
                mbZuSelected = false;
                mpZiString->update();
            } else confirmInput_();
            return;
        }
    }
    if (direct) {
        mpString->getCursorPos();
        mpString->inputChar(character);
        mpString->getCursorPos();
        if (meLanguage == CN) {
            bool predictions;
            if (!mbPredictOn) predictions = false;
            else if (mePredictMode != PM_Atok && mpZiString->getCurrentNumPredicted() > 0) predictions = true;
            else predictions = false;
            if (predictions) {
                mpZiString->setCurrentWord(NULL);
                mpZiString->update();
            }
        }
    } else {
        if (current == mpZiString) {
            if (!mpZiString->getInputStringLength()) {
                mpZiString->changeLetterMode(static_cast<tistring::WithZi::LetterMode>(letterMode));
                mpZiString->setCellPhoneHoldingkey(holdingKey);
            }
            if (mpZiString->getInputStringLength() >= 32) {
                onCommand(static_cast<INPUT_COMMAND>(6), NULL);
                mpZiString->changeLetterMode(static_cast<tistring::WithZi::LetterMode>(letterMode));
                mpZiString->inputChar(character);
                onSE(static_cast<sound::SE>(9));
                updateCandidateState_();
                return;
            }
        } else if (current == mpUnfixString) {
            if (confirmOnly && !mpUnfixString->hasCandidate()) return;
        } else if (mbPredictOn && mePredictMode == PM_Atok && current != mpUnfixString && character == L' ') {
            character = 0x3000;
            mpUnfixString->setCandidate(0);
        }
        if (current == mpString) {
            mpString->getCursorPos();
            mpString->inputChar(character);
            mpString->getCursorPos();
            if (meLanguage == CN) {
                bool predictions;
                if (!mbPredictOn) predictions = false;
                else if (mePredictMode != PM_Atok && mpZiString->getCurrentNumPredicted() > 0) predictions = true;
                else predictions = false;
                if (predictions) {
                    mpZiString->setCurrentWord(NULL);
                    mpZiString->update();
                }
            }
        } else {
            current->inputChar(character);
            if (meLanguage == KR && mpManager->getToolBar()->isQwerty()) {
                wchar_t predicted[64];
                mpZiString->getPredicted(0, predicted);
                if (wcslen(predicted) >= 2) {
                    predicted[1] = 0;
                    mpString->getCursorPos();
                    mpString->inputString(predicted);
                    mpString->getCursorPos();
                    mpZiString->partialConfirmForKR();
                }
            }
        }
        onSE(static_cast<sound::SE>(10));
    }
}

void Base::inputCharZi_(wchar_t character, u32 modifiers) {
    if (meLanguage != KR && (modifiers & 3)) character = util::toWLower(character);
    bool direct = false;
    if (character == L' ') direct = true;
    if (meLanguage == CN) {
        if (!util::isAlphabet(character) && (character < L'1' || character > L'5' || !mpZiString->getInputStringLength())) direct = true;
    } else if (meLanguage == KR) {
        if (util::isAlphabet(character)) {
            if (getCurrentString(true) == mpZiString && (modifiers & 2)) character = util::reverseLetterCaseW(character);
        } else direct = true;
    }
    if (direct) {
        bool predictions;
        if (!mbPredictOn) predictions = false;
        else if (mePredictMode != PM_Atok && mpZiString->getCurrentNumPredicted() > 0) predictions = true;
        else predictions = false;
        if (predictions) confirmInput_();
        mpString->getCursorPos();
        mpString->inputChar(character);
        mpString->getCursorPos();
        if (meLanguage == CN) {
            if (!mbPredictOn) predictions = false;
            else if (mePredictMode != PM_Atok && mpZiString->getCurrentNumPredicted() > 0) predictions = true;
            else predictions = false;
            if (predictions) {
                mpZiString->setCurrentWord(NULL);
                mpZiString->update();
            }
        }
        onSE(static_cast<sound::SE>(9));
    } else {
        u16 letterMode;
        switch (modifiers & 3) {
        case 1: letterMode = 0; break;
        case 2: letterMode = 2; break;
        default: letterMode = 1; break;
        }
        confirmInputting_(character, false, letterMode, false, NULL);
    }
    meScrollFlag = SF_ScrollOn;
}

void Base::toggleAtokMode_(u8 operation) {
    bool allowed;
    if (!mpManager->getToolBar()->isEnableKeytopChange() && !mpManager->getToolBar()->isQwerty()) {
        allowed = false;
    } else allowed = !mpManager->getPCKeyboard()->isQwertyOnly();
    if (!allowed) return;
    bool enabled;
    if (mpManager->getCandidateBox()->isActive()) {
        if (mpManager->isPredictTurning()) return;
        enabled = !mbPredictOn;
        if (mpManager->getPCKeyboard()->getTranslateMode() == keyboard::pctype::Base::TM_00) enabled = true;
    } else {
        enabled = mpManager->getPCKeyboard()->getTranslateMode() == keyboard::pctype::Base::TM_00;
    }
    if (enabled && operation == 2) enabled = false;
    else if (!enabled && operation == 1) enabled = true;
    if (enabled) {
        if (mpManager->getPCKeyboard()->getTranslateMode() == keyboard::pctype::Base::TM_00) {
            mpManager->getPCKeyboard()->setTranslateMode(keyboard::pctype::Base::TM_Kana);
        }
    } else {
        mpManager->getPCKeyboard()->setTranslateMode(keyboard::pctype::Base::TM_00);
    }
    if (mpManager->getCandidateBox()->isActive() && mbPredictOn != enabled) {
        mpManager->startPredictTurnOn(!mbPredictOn);
    }
}

void Base::onSpaceKeyHWKB(u32 modifiers) {
    tistring::Decolated* current = getCurrentString(false);
    if (modifiers & 8) {
        if (static_cast<u32>(meLanguage) - CN <= 1 && !mpManager->getPCKeyboard()->isQwertyOnly() && mpManager->getPCKeyboard()->isLanguageKeyActive()) {
            if (mpManager->getPCKeyboard()->getTranslateMode() == keyboard::pctype::Base::TM_00) {
                mpManager->getPCKeyboard()->setTranslateMode(keyboard::pctype::Base::TM_Kana);
            } else mpManager->getPCKeyboard()->setTranslateMode(keyboard::pctype::Base::TM_00);
        }
        return;
    }
    bool useZi;
    if (!mbPredictOn) useZi = false;
    else if (mePredictMode == PM_Atok) useZi = false;
    else if (meLanguage == CN && static_cast<const Manager*>(mpManager)->getCandidateBox()->isInvalid()) useZi = false;
    else useZi = true;
    if (useZi) {
        bool predicted;
        if (!mbPredictOn) predicted = false;
        else if (mePredictMode != PM_Atok && mpZiString->getCurrentNumPredicted() > 0) predicted = true;
        else predicted = false;
        if (predicted) {
            if (!(mbCursorSelected | mbZuSelected) && mpManager->getToolBar()->isQwerty()) {
                if (meLanguage != CN && meLanguage != KR && mbPredictOn && mePredictMode != PM_Atok) {
                    wchar_t input[64];
                    mpZiString->getCurrentInput(input, 64);
                    mpString->getCursorPos();
                    mpString->inputString(input);
                    mpString->getCursorPos();
                    mpZiString->clearCandidates();
                    mbZuSelected = false;
                    getCurrentString(false);
                    if (mpZiString && meLanguage == CN) {
                        mpZiString->setCurrentWord(NULL);
                        mpZiString->update();
                        updateCandidateState_();
                    }
                }
            } else confirmInput_();
            updateCandidateState_();
        }
    } else {
        bool useAtok;
        if (!mbPredictOn) useAtok = false;
        else useAtok = mePredictMode == PM_Atok;
        if (useAtok && current == mpUnfixString) {
            if (!mpUnfixString->isKanaFix()) mpUnfixString->confirmKana();
            if (mpUnfixString->isConverting()) {
                if (!mpManager->getCandidateBox()->isInScroll()) {
                    if (modifiers & 2) {
                        tistring::Decolated* active = getCurrentString(false);
                        if (active == mpUnfixString) {
                            s32 selected = static_cast<s16>(mpUnfixString->getSelectedConverting() - 1);
                            if (selected >= mpUnfixString->getCurrentNumPredicted()) selected = 0;
                            else if (selected < 0) selected = static_cast<s16>(mpUnfixString->getCurrentNumPredicted() - 1);
                            moveCandidateToIdx(selected);
                            mpManager->getCandidateBox()->getTextArea().ScrollToSelectedText();
                        }
                    } else {
                        tistring::Decolated* active = getCurrentString(false);
                        if (active == mpUnfixString) {
                            s32 selected = static_cast<s16>(mpUnfixString->getSelectedConverting() + 1);
                            if (selected >= mpUnfixString->getCurrentNumPredicted()) selected = 0;
                            else if (selected < 0) selected = static_cast<s16>(mpUnfixString->getCurrentNumPredicted() - 1);
                            moveCandidateToIdx(selected);
                            mpManager->getCandidateBox()->getTextArea().ScrollToSelectedText();
                        }
                    }
                    onSE(static_cast<sound::SE>(6));
                    mpManager->getCandidateBox()->getTextArea().ScrollToSelectedText();
                }
            } else {
                if (mpUnfixString->getInputStringLength()) {
                    mpUnfixString->startConverting();
                    updateCandidateState_();
                    moveCandidateToIdx(0);
                    mpManager->getCandidateBox()->getTextArea().ScrollToSelectedText();
                    onCommand(static_cast<INPUT_COMMAND>(47), NULL);
                }
            }
            return;
        }
    }
    if (mDKStream.lookAhead()) mDKStream.putChar(0xffff);
    else mDKStream.putChar(L' ');
    if (!mbPredictOn) useZi = false;
    else if (mePredictMode == PM_Atok) useZi = false;
    else if (meLanguage == CN && static_cast<const Manager*>(mpManager)->getCandidateBox()->isInvalid()) useZi = false;
    else useZi = true;
    if (useZi) {
        wchar_t character;
        for (;;) {
            character = mDKStream.getChar();
            if (!character) break;
            inputCharZi_(character, modifiers);
        }
    } else {
        wchar_t character;
        for (;;) {
            character = mDKStream.getChar();
            if (!character) break;
            inputCharDefault_(character, modifiers);
        }
    }
    updateCandidateState_();
}


void Base::onPressUp() {
    tistring::Decolated* current = getCurrentString(false);
    if (mpZiString == current) return;
    if (mpUnfixString == current) {
        if (!mpUnfixString->isKanaFix()) mpUnfixString->confirmKana();
        if (mpUnfixString->isConverting()) {
            if (!mpManager->getCandidateBox()->isInScroll()) {
                tistring::Decolated* active = getCurrentString(false);
                if (active == mpUnfixString) {
                    s32 selected = static_cast<s16>(mpUnfixString->getSelectedConverting() - 1);
                    if (selected >= mpUnfixString->getCurrentNumPredicted()) selected = 0;
                    else if (selected < 0) selected = static_cast<s16>(mpUnfixString->getCurrentNumPredicted() - 1);
                    moveCandidateToIdx(selected);
                    mpManager->getCandidateBox()->getTextArea().ScrollToSelectedText();
                }
                onSE(static_cast<sound::SE>(6));
            }
        } else if (mpUnfixString->getInputStringLength()) {
            mpUnfixString->startConverting();
            updateCandidateState_();
            moveCandidateToIdx(0);
            mpManager->getCandidateBox()->getTextArea().ScrollToSelectedText();
            onCommand(static_cast<INPUT_COMMAND>(47), NULL);
        }
    } else if (current == mpString) {
        if (meLanguage == KR && !getCurrentString(false)->isKanaFix()) {
            mpString->getCursorPos();
            mpString->inputChar(L'\n');
            mpString->getCursorPos();
            if (meLanguage == CN) {
                bool predictions;
                if (!mbPredictOn) predictions = false;
                else if (mePredictMode != PM_Atok && mpZiString->getCurrentNumPredicted() > 0) predictions = true;
                else predictions = false;
                if (predictions) {
                    mpZiString->setCurrentWord(NULL);
                    mpZiString->update();
                }
            }
        }
        if (!current->hasCandidate()) {
            if (!current->isKanaFix()) return;
            mpManager->getHWKeyboard()->resetQuoteState();
            mpUnfixString->resetRelation();
            updateCandidateState_();
            if (mpUnfixString->getCandidate() != L' ') {
                moveCursorUp();
                onCommand(static_cast<INPUT_COMMAND>(47), NULL);
            }
        }
    }
}

void Base::onPressDown() {
    tistring::Decolated* current = getCurrentString(false);
    if (mpZiString == current) return;
    if (mpUnfixString == current) {
        if (!mpUnfixString->isKanaFix()) mpUnfixString->confirmKana();
        if (mpUnfixString->isConverting()) {
            if (!mpManager->getCandidateBox()->isInScroll()) {
                tistring::Decolated* active = getCurrentString(false);
                if (active == mpUnfixString) {
                    s32 selected = static_cast<s16>(mpUnfixString->getSelectedConverting() + 1);
                    if (selected >= mpUnfixString->getCurrentNumPredicted()) selected = 0;
                    else if (selected < 0) selected = static_cast<s16>(mpUnfixString->getCurrentNumPredicted() - 1);
                    moveCandidateToIdx(selected);
                    mpManager->getCandidateBox()->getTextArea().ScrollToSelectedText();
                }
                onSE(static_cast<sound::SE>(6));
            }
        } else if (mpUnfixString->getInputStringLength()) {
            mpUnfixString->startConverting();
            updateCandidateState_();
            moveCandidateToIdx(0);
            mpManager->getCandidateBox()->getTextArea().ScrollToSelectedText();
            onCommand(static_cast<INPUT_COMMAND>(47), NULL);
        }
    } else if (current == mpString) {
        if (meLanguage == KR && !getCurrentString(false)->isKanaFix()) {
            mpString->getCursorPos();
            mpString->inputChar(L'\n');
            mpString->getCursorPos();
            if (meLanguage == CN) {
                bool predictions;
                if (!mbPredictOn) predictions = false;
                else if (mePredictMode != PM_Atok && mpZiString->getCurrentNumPredicted() > 0) predictions = true;
                else predictions = false;
                if (predictions) {
                    mpZiString->setCurrentWord(NULL);
                    mpZiString->update();
                }
            }
        }
        if (!current->hasCandidate()) {
            if (!current->isKanaFix()) return;
            mpManager->getHWKeyboard()->resetQuoteState();
            mpUnfixString->resetRelation();
            updateCandidateState_();
            if (mpUnfixString->getCandidate() != L' ') {
                moveCursorDown();
                onCommand(static_cast<INPUT_COMMAND>(47), NULL);
            }
        }
    }
}

void Base::onPressDownHWKB() {
    tistring::Decolated* current = getCurrentString(false);
    s32 selected;
    u32 modifiers = input::HKBManager::getInstance().GetModifierState();
    if (current == mpString) {
        mpManager->getHWKeyboard()->resetQuoteState();
        mpUnfixString->resetRelation();
        updateCandidateState_();
        if (meLanguage == KR && !getCurrentString(false)->isKanaFix()) {
            mpString->getCursorPos();
            mpString->inputChar(L'\n');
            mpString->getCursorPos();
            if (meLanguage == CN) {
                bool predictions;
                if (!mbPredictOn) predictions = false;
                else if (mePredictMode != PM_Atok && mpZiString->getCurrentNumPredicted() > 0) predictions = true;
                else predictions = false;
                if (predictions) {
                    mpZiString->setCurrentWord(NULL);
                    mpZiString->update();
                }
            }
        }
        if (!current->hasCandidate()) {
            if (!current->isKanaFix()) return;
            if (mpUnfixString->getCandidate() == L' ') return;
            moveCursorDown();
            onCommand(static_cast<INPUT_COMMAND>(47), NULL);
        }
    } else if (mpUnfixString == current) {
        if (!mpUnfixString->isKanaFix()) mpUnfixString->confirmKana();
        if (mpUnfixString->isConverting()) {
            if (modifiers & 2) {
                mpUnfixString->commitPredicted(mpUnfixString->getSelectedConverting());
                updateCandidateState_();
            } else {
                if (!mpManager->getCandidateBox()->isInScroll()) {
                    tistring::Decolated* active = getCurrentString(false);
                    if (active == mpUnfixString) {
                        selected = static_cast<s16>(mpUnfixString->getSelectedConverting() + 1);
                        if (selected >= mpUnfixString->getCurrentNumPredicted()) selected = 0;
                        else if (selected < 0) selected = static_cast<s16>(mpUnfixString->getCurrentNumPredicted() - 1);
                        moveCandidateToIdx(selected);
                        mpManager->getCandidateBox()->getTextArea().ScrollToSelectedText();
                    }
                    onSE(static_cast<sound::SE>(6));
                }
            }
        } else {
            if (mpUnfixString->getInputStringLength()) {
                mpUnfixString->startConverting();
                updateCandidateState_();
                moveCandidateToIdx(0);
                mpManager->getCandidateBox()->getTextArea().ScrollToSelectedText();
                onCommand(static_cast<INPUT_COMMAND>(47), NULL);
            }
        }
    }
}

void Base::onPressLeftHWKB() {
    tistring::Decolated* current = getCurrentString(false);
    input::HKBManager::getInstance().GetModifierState();
    current->getCursorPos();
    if (current == mpString) {
        if (meLanguage == KR) {
            if (!getCurrentString(false)->isKanaFix()) {
                mpString->getCursorPos();
                mpString->inputChar(L'\n');
                mpString->getCursorPos();
                if (meLanguage == CN) {
                    bool predictions;
                    if (!mbPredictOn) predictions = false;
                    else if (mePredictMode != PM_Atok && mpZiString->getCurrentNumPredicted() > 0) predictions = true;
                    else predictions = false;
                    if (predictions) {
                        mpZiString->setCurrentWord(NULL);
                        mpZiString->update();
                    }
                }
            }
            current->getCursorPos();
        }
        if (current->hasCandidate()) return;
        switch (current->isKanaFix()) {
        case true: break;
        default: return;
        }
        mpManager->getHWKeyboard()->resetQuoteState();
        mpUnfixString->resetRelation();
        updateCandidateState_();
        if (current->moveCursorLeft()) onSE(static_cast<sound::SE>(5));
        else onSE(static_cast<sound::SE>(6));
    } else if (current == mpUnfixString) {
        if (mpManager->getCandidateBox()->isInScroll()) return;
        if (mpUnfixString->getCurrentNumPredicted() <= 0) return;
        if (mpUnfixString->isConverting()) {
            onPressLeft();
            return;
        }
        s32 selected = static_cast<s16>(mpUnfixString->getSelectedCandidate() - 1);
        if (selected < -1) selected = 0;
        else if (selected < 0) selected = static_cast<s16>(mpUnfixString->getCurrentNumPredicted() - 1);
        moveCandidateToIdx(selected);
        mpManager->getCandidateBox()->getTextArea().ScrollToSelectedText();
        onSE(static_cast<sound::SE>(6));
    } else if (current == mpZiString) {
        if (mpManager->getCandidateBox()->isInScroll()) return;
        bool selectedAlready = mbZuSelected;
        mbZuSelected = true;
        if (mpZiString->getCurrentNumPredicted() < 0) return;
        s32 selected = mpZiString->getSelectedCandidateIndex();
        if (selectedAlready) --selected;
        if (selected < 0) selected = mpZiString->getCurrentNumPredicted() - 1;
        moveCandidateToIdx(selected);
        mpManager->getCandidateBox()->getTextArea().ScrollToSelectedText();
        onSE(static_cast<sound::SE>(6));
    }
    meScrollFlag = SF_ScrollOn;
}

void Base::onPressRightHWKB() {
    tistring::Decolated* current = getCurrentString(false);
    input::HKBManager::getInstance().GetModifierState();
    current->getCursorPos();
    if (current == mpString) {
        if (meLanguage == KR) {
            if (!getCurrentString(false)->isKanaFix()) {
                mpString->getCursorPos();
                mpString->inputChar(L'\n');
                mpString->getCursorPos();
                if (meLanguage == CN) {
                    bool predictions;
                    if (!mbPredictOn) predictions = false;
                    else if (mePredictMode != PM_Atok && mpZiString->getCurrentNumPredicted() > 0) predictions = true;
                    else predictions = false;
                    if (predictions) {
                        mpZiString->setCurrentWord(NULL);
                        mpZiString->update();
                    }
                }
            }
            current->getCursorPos();
        }
        if (current->hasCandidate()) return;
        switch (current->isKanaFix()) {
        case true: break;
        default: return;
        }
        mpManager->getHWKeyboard()->resetQuoteState();
        mpUnfixString->resetRelation();
        updateCandidateState_();
        if (current->moveCursorRight()) onSE(static_cast<sound::SE>(6));
        else onSE(static_cast<sound::SE>(5));
    } else if (current == mpUnfixString) {
        if (mpManager->getCandidateBox()->isInScroll()) return;
        if (mpUnfixString->getCurrentNumPredicted() <= 0) return;
        if (mpUnfixString->isConverting()) {
            current->moveCursorRight();
            onSE(static_cast<sound::SE>(6));
            updateCandidateState_();
        } else {
            s32 selected = static_cast<s16>(mpUnfixString->getSelectedCandidate() + 1);
            if (selected >= mpUnfixString->getCurrentNumPredicted()) selected = 0;
            moveCandidateToIdx(selected);
            mpManager->getCandidateBox()->getTextArea().ScrollToSelectedText();
            onSE(static_cast<sound::SE>(6));
        }
    } else if (current == mpZiString) {
        if (mpManager->getCandidateBox()->isInScroll()) return;
        bool selectedAlready = mbZuSelected;
        mbZuSelected = true;
        if (mpZiString->getCurrentNumPredicted() < 0) return;
        s32 selected = mpZiString->getSelectedCandidateIndex();
        if (selectedAlready) ++selected;
        if (selected >= mpZiString->getCurrentNumPredicted()) selected = 0;
        if (selected < 0) selected = 0;
        moveCandidateToIdx(selected);
        mpManager->getCandidateBox()->getTextArea().ScrollToSelectedText();
        onSE(static_cast<sound::SE>(6));
    }
    meScrollFlag = SF_ScrollOn;
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

Base::RowInfoManager::~RowInfoManager() {
    MEMFreeToAllocator(mpAllocator, mpInfo);
}

Base::~Base() {}

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













extern "C" asm void init__Q29textinput4BaseFv() {
    nofralloc
    blr
}



















extern "C" asm void getLine__Q39textinput10textdrawer4BaseFv() {
    nofralloc
    lwz r3, 0xa0(r3)
    addi r3, r3, 1
    blr
}












}

bool textinput::util::Animation::isActive() {
    return mbInAnimation;
}

namespace inputform {
extern "C" asm void getKanaBuffer__Q39textinput8tistring9DecolatedFv() {
    nofralloc
    addi r3, r3, 0x42
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








extern "C" asm void create__Q39textinput9inputform4BaseFP12MEMAllocator() {
    nofralloc
    blr
}

extern "C" asm void setVIWidth__Q39textinput10textdrawer4BaseFf() {
    nofralloc
    stfs f1, 0x98(r3)
    blr
}



}

void textinput::util::Animation::stop() {
    mbInAnimation = false;
}

namespace inputform {
}

bool textinput::util::Animation::isSEFlag() {
    return mbSE;
}

namespace inputform {
}

void textinput::util::Animation::setSEFlag(bool flag) {
    mbSE = flag;
}

namespace inputform {
}

f32 textinput::util::Animation::getValue() {
    return hermiteInterporation(mfCurrentFrame, 0.0f, mfStartPoint, 0.0f, mfAnimationTime, mfEndPoint, 0.0f);
}

namespace inputform {

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
}

void textinput::util::Animation::calc() {
    if (mbInAnimation) {
        if (mfCurrentFrame < mfAnimationTime) {
            mfCurrentFrame = 1.0f + mfCurrentFrame;
        } else {
            if (mbInAnimation && mpAnimObserver) {
                mpAnimObserver->onAnmEvent(AnimObserver::AE_1, mpData);
            }
            mbInAnimation = false;
        }
    }
}

bool textdrawer::Base::isEnableCursorCache() const {
    return mbCursorCache;
}

u32 textdrawer::Base::getStartPos() const {
    return muDrawStartPos;
}

namespace inputform {
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
nw4r::math::VEC2 LayoutByNW4R::getScale() const {
    return mpLayout->GetRootPane()->FindPaneByName(static_cast<const char*>(mpLayoutData), true)->GetScale();
}
LayoutByNW4R::~LayoutByNW4R() {
    if (mpInputEventHandler) {
        mpInputEventHandler->~TiEventHandler();
        MEMFreeToAllocator(mpAllocator, mpInputEventHandler);
    }
    nw4rmanager::AnmPane* pane = static_cast<nw4rmanager::AnmPane*>(nw4r::ut::List_GetNext(&mAnmPanes, NULL));
    while (pane) {
        nw4r::ut::List_Remove(&mAnmPanes, pane);
        pane->destroy(mpAllocator);
        pane = static_cast<nw4rmanager::AnmPane*>(nw4r::ut::List_GetNext(&mAnmPanes, NULL));
    }
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
wchar_t DeadKeyStream::ToCombineClass(Language language, wchar_t code) {
    switch (language) {
        case DE:
            if (code == 0xb4) return 0x301;
            if (code == 0x60) return 0x300;
            break;
        case FR:
            if (code == 0x5e) return 0x302;
            if (code == 0xa8) return 0x308;
            break;
        case SP:
            if (code == 0x60) return 0x300;
            if (code == 0xb4) return 0x301;
            if (code == 0x5e) return 0x302;
            if (code == 0x7e) return 0x303;
            if (code == 0xa8) return 0x308;
            break;
        case NL:
            if (code == 0x60) return 0x300;
            if (code == 0x5e) return 0x302;
            if (code == 0x7e) return 0x303;
            if (code == 0x27) return 0x30d;
            if (code == 0x22) return 0x30e;
            break;
    }
    return code;
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

bool Base::isEditMode() {
    switch (mePredictMode) {
    case PM_Off:
    case PM_Atok:
        break;
    default:
        if (!mpZiString->isFix()) return false;
        break;
    }
    return true;
}

bool Base::checkHeadOfSentence(bool checkSpace) {
    bool externallyHandled;
    onCommand(static_cast<INPUT_COMMAND>(32), &externallyHandled);
    if (externallyHandled) return false;
    bool moved = false;
    if (mpString->getCursorPos() < 1) return true;
    if (checkSpace) {
        switch (mpString->getWCharAtCursor()) {
        case L' ':
        case L'\n':
            break;
        default:
            return false;
        }
        moved = mpString->moveCursorLeft();
    }
    bool beginning = mpString->atTheBeginningOfASentence();
    if (moved) mpString->moveCursorRight();
    return beginning;
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

void Base::setAtokDictionary(void* atok, int atokSize, void* apot, int apotSize, void* nintendo, int nintendoSize) {
    mpUnfixString->openDictionary(atok, atokSize, apot, apotSize, nintendo, nintendoSize);
}

void Base::setCursorPos(tistring::Decolated* string, u32 pos) {
    string->setCursorPos(pos);
}

void Base::closeAtokDictionary() {
    mpUnfixString->closeDictionary();
}

bool Base::isAtokDictionaryOpened() {
    return mpUnfixString->isDictionaryOpened();
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

u32 Base::isOverRowLimit(u32 limit, const wchar_t* string) {
    const wchar_t* current = string;
    if (!*string) return 0;
    f32 cursorX = getScale().x;
    nw4r::math::VEC2 scale = getScale();
    f32 scaleX = scale.x;
    u32 pos = 0;
    u32 rows = 0;
    muWordWrapCounter = 0;
    bool kanaHandled = false;
    mbHyphen = false;
    u32 cursorStart, cursorEnd;
    mpString->getCursorPos(&cursorStart, &cursorEnd);
    for (;;) {
        DrawInfo info;
        info.rect.left = 0.0f;
        info.rect.top = 0.0f;
        info.rect.right = 0.0f;
        info.rect.bottom = 0.0f;
        bool kana = false;
        const wchar_t* character = current;
        if (meLanguage == KR && !kanaHandled && cursorStart == pos) {
            kanaHandled = true;
            character = mpString->getKanaBuffer();
            if (*character) kana = true;
        }
        if (!kana) {
            if (!*current) return 0;
            character = current;
        }
        info.character = *character;
        calcRect(info);
        f32 right = cursorX + scaleX * (info.rect.right - info.rect.left);
        if (kana) {
            if (right >= scaleX * (mRect.right - mRect.left)) {
                cursorX = getScale().x;
                ++rows;
                if (rows >= limit) return pos;
            } else {
                cursorX = right;
            }
            continue;
        }
        if (doWordWrap(string, pos, cursorX)) {
            ++rows;
            if (rows >= limit) {
                while (pos < muWordWrapCounter) {
                    f32 advance = scaleX * (info.rect.right - info.rect.left);
                    if (cursorX + advance >= scaleX * (mRect.right - mRect.left)) return pos;
                    ++current;
                    cursorX += advance;
                    info.character = *current;
                    calcRect(info);
                    ++pos;
                }
                return muWordWrapCounter - 1;
            }
            cursorX = getScale().x;
        } else if (right >= scaleX * (mRect.right - mRect.left)) {
            cursorX = getScale().x;
            ++rows;
            if (rows >= limit) return pos;
        }
        if (*current == L'\n') {
            cursorX = getScale().x;
            ++rows;
            if (rows >= limit) return pos;
            if (!current[1]) return 0;
        } else {
            cursorX += scaleX * (info.rect.right - info.rect.left);
        }
        ++pos;
        ++current;
    }
}

bool Base::onCursor(CursorPos* cursor) {
    bool positioned = false;
    nw4r::ut::Color savedColor = GetTextColor();
    SetupGX();
    const wchar_t* kana = mpString->getKanaBuffer();
    wchar_t candidate = mpString->getCandidate();
    if (mbPredictOn && mePredictMode != PM_Atok) {
        const wchar_t* predicted = mpZiString->getCurrentSelected();
        if (getPredictMode() == PM_11) {
            if (mbCursorSelected) mbZuSelected = true;
            if (!(mbCursorSelected | mbZuSelected)) predicted = mpZiString->getCurrentInput();
        }
        if (predicted) {
            u16 index = 0;
            SetTextColor(csZiStringColorLeft);
            for (; *predicted;) {
                if (!(mbCursorSelected | mbZuSelected) && index == mpZiString->getInputStringLength()) {
                    positioned = true;
                    cursor->fCursorX = GetCursorX();
                    cursor->fCursorY = GetCursorY();
                }
                if (getPredictMode() != PM_11 && mpZiString->getInputStringLength() <= index) {
                    if (mbCursorSelected | mbZuSelected) SetTextColor(csZiStringColorRight);
                    else SetTextColor(csZiStringNonSelectColorRight);
                }
                if (*predicted == 0xFFFE) SetTextColor(csZiStringColorLeft);
                DrawInfo glyph;
                glyph.rect.left = 0.0f;
                glyph.rect.top = 0.0f;
                glyph.rect.right = 0.0f;
                glyph.rect.bottom = 0.0f;
                glyph.character = *predicted;
                calcRect(glyph);
                f32 width = glyph.rect.right - glyph.rect.left;
                f32 fieldWidth = mRect.right - mRect.left;
                f32 cursorX = GetCursorX();
                if (cursorX + width >= fieldWidth) doLineFeed();
                Print(*predicted);
                MoveCursorX(mfCharacterSpacing);
                ++predicted;
                ++index;
            }
        }
    }
    if (meDestination == DST_JP && candidate) {
        DrawInfo glyph;
        glyph.rect.left = 0.0f;
        glyph.rect.top = 0.0f;
        glyph.rect.right = 0.0f;
        glyph.rect.bottom = 0.0f;
        glyph.character = candidate;
        calcRect(glyph);
        static GXColor candidateBackground = {255, 210, 12, 255};
        f32 left = glyph.rect.left + GetCursorX();
        f32 top = glyph.rect.top + GetCursorY();
        f32 right = glyph.rect.right + GetCursorX();
        f32 bottomEdge = GetCursorY() + GetFontHeight();
        candidateBackground.a = muGlobalAlpha;
        debug::drawBox_(left, top, right, bottomEdge, 0.0f, 1.0f, candidateBackground);
        SetupGX();
        SetTextColor(mCharColor);
        switch (candidate) {
        case L' ':
        case 0x3000: {
            DrawInfo space;
            DrawInfo marker;
            space.rect.left = 0.0f;
            space.rect.top = 0.0f;
            space.rect.right = 0.0f;
            space.rect.bottom = 0.0f;
            marker.rect.left = 0.0f;
            marker.rect.top = 0.0f;
            marker.rect.right = 0.0f;
            marker.rect.bottom = 0.0f;
            space.character = candidate;
            marker.character = 0xE057;
            calcRect(space);
            calcRect(marker);
            f32 markerWidth = marker.rect.right - marker.rect.left;
            f32 spaceWidth = space.rect.right - space.rect.left;
            f32 offset = ((spaceWidth - markerWidth) * 0.5f) * getScale().x;
            MoveCursorX(offset);
            Print(0xE057);
            MoveCursorX(offset);
            break;
        }
        default:
            Print(candidate);
            break;
        }
        MoveCursorX(mfCharacterSpacing);
    }
    if (meDestination != DST_JP) {
        wchar_t pending = mpString->getCandidate();
        if (pending) {
            SetTextColor(csUnInputedWCharColor);
            if (pending == L' ') {
                SetTextColor(csUnInputedWCharColorSpace);
                pending = 0xE057;
            }
            Print(pending);
            MoveCursorX(mfCharacterSpacing);
        }
    }
    for (; *kana; ++kana) {
        wchar_t character = *kana;
        if (mbPredictOn) character = util::HankakuToZenkaku(character);
        DrawInfo glyph;
        glyph.rect.left = 0.0f;
        glyph.rect.top = 0.0f;
        glyph.rect.right = 0.0f;
        glyph.rect.bottom = 0.0f;
        glyph.character = character;
        calcRect(glyph);
        if (meLanguage == JP) {
            static GXColor kanaBackground = {128, 255, 128, 255};
            f32 left = glyph.rect.left + GetCursorX();
            f32 top = glyph.rect.top + GetCursorY();
            f32 right = glyph.rect.right + GetCursorX();
            f32 bottomEdge = GetCursorY() + GetFontHeight();
            kanaBackground.a = muGlobalAlpha;
            debug::drawBox_(left, top, right, bottomEdge, 0.0f, 1.0f, kanaBackground);
            SetupGX();
            mCharColor.a = muGlobalAlpha;
            SetTextColor(mCharColor);
        } else if (meLanguage == KR) {
            SetupGX();
            mCharColor.a = muGlobalAlpha;
            SetTextColor(csZiStringColorLeft);
            if (isOverLine(glyph)) {
                ++muLine;
                SetCursorY(GetCursorY() + getLineHeight());
                SetCursorX(getScale().x);
            }
        }
        Print(character);
        MoveCursorX(mfCharacterSpacing);
    }
    SetTextColor(savedColor);
    return positioned;
}

u32 Base::calcCursorPos(f32 x, f32 y) {
    f32 localY = y - mfScrollY;
    const wchar_t* string = mpString->getWCString();
    if (!*string) return 0;
    f32 cursorX = getScale().x;
    f32 lineTop = 0.0f;
    f32 lineBottom = lineTop;
    nw4r::math::VEC2 scale = getScale();
    u32 pos = 0;
    muWordWrapCounter = 0;
    mbHyphen = false;
    while (*string) {
        DrawInfo info;
        info.rect.left = 0.0f;
        info.rect.top = 0.0f;
        info.rect.right = 0.0f;
        info.rect.bottom = 0.0f;
        info.character = *string;
        calcRect(info);
        lineBottom = lineTop + scale.y * (info.rect.bottom - info.rect.top);
        f32 right = cursorX + scale.x * (info.rect.right - info.rect.left);
        if (doWordWrap(mpString->getWCString(), pos, cursorX)) {
            if (localY >= lineTop && localY <= lineBottom) {
                if (pos != 0) return pos - 1;
                return pos;
            }
            lineTop += scale.y * getLineHeight();
            cursorX = getScale().x;
            lineBottom = lineTop + scale.y * (info.rect.bottom - info.rect.top);
            right = cursorX + scale.x * (info.rect.right - info.rect.left);
        }
        if (right >= scale.x * (mRect.right - mRect.left)) {
            if (localY >= lineTop && localY <= lineBottom) return pos;
            lineTop += scale.y * getLineHeight();
            cursorX = getScale().x;
            lineBottom = lineTop + scale.y * (info.rect.bottom - info.rect.top);
            right = cursorX + scale.x * (info.rect.right - info.rect.left);
        }
        if (x <= info.rect.left && localY >= lineTop && localY <= lineBottom) return pos;
        if (*string == L'\n') {
            if (localY >= lineTop && localY <= lineBottom) return pos;
            lineTop += scale.y * getLineHeight();
            cursorX = getScale().x;
            lineBottom = lineTop + scale.y * (info.rect.bottom - info.rect.top);
            if (!string[1] && localY >= lineTop && localY <= lineBottom) return pos + 1;
        } else {
            if (cursorX <= x && x < right && localY >= lineTop && localY < lineBottom) {
                if (cursorX + (right - cursorX) * 0.5f > x) return pos;
                return pos + 1;
            }
            cursorX += scale.x * (info.rect.right - info.rect.left);
        }
        ++string;
        ++pos;
        if (!*string && localY >= lineTop && localY <= lineBottom) return pos;
    }
    if (lineTop + (lineBottom - lineTop) * 0.5f <= localY) {
        return Base::calcCursorPos(x, 1.0f + lineTop + mfScrollY);
    }
    return Base::calcCursorPos(x, 1.0f);
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

    f32 stringWidth = 0.0f;
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
        drawInfo.left = 0.0f;
        drawInfo.top = 0.0f;
        drawInfo.right = 0.0f;
        drawInfo.bottom = 0.0f;
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

void NormalButtonAnmPane::onAnmEvent(AnmPaneEvent event) {
    if (event == PE_6 && meState == ANM_Off) {
        changeAnimation(ANM_FadeIn);
    } else if (event == PE_7 && meState != ANM_Off) {
        changeAnimation(ANM_FadeOut);
    } else if (event == PE_0) {
        changeAnimation(ANM_Pushed);
    }
    switch (meState) {
        case ANM_FocusOut:
            if (event == PE_4) changeAnimation(ANM_Normal);
            if (event == PE_1) changeAnimation(ANM_FocusIn);
            break;
        case ANM_Normal:
            if (event == PE_1) changeAnimation(ANM_FocusIn);
            break;
        case ANM_FocusIn:
            if (event == PE_4) changeAnimation(ANM_RollOver);
            if (event == PE_2) changeAnimation(ANM_FocusOut);
            break;
        case ANM_RollOver:
            if (event == PE_2) changeAnimation(ANM_FocusOut);
            break;
        case ANM_FadeIn:
            if (event == PE_4) changeAnimation(ANM_Normal);
            if (event == PE_1) changeAnimation(ANM_FocusIn);
            break;
        case ANM_Pushed:
            if (event == PE_4) changeAnimation(ANM_RollOver);
            if (event == PE_2) changeAnimation(ANM_FocusOut);
            break;
        case ANM_FadeOut:
            if (event == PE_4) changeAnimation(ANM_Off);
            break;
    }
}

EventHandler::~EventHandler() {}

wchar_t Base::getCandidate() const {
    return mpString->getCandidate();
}

void* Base::getAtokString() {
    return mpUnfixString;
}

u32 Base::getCursorPos() {
    u32 fixedStart, unfixedStart, end;
    mpString->getCursorPos(&fixedStart, &end);
    mpUnfixString->getCursorPos(&unfixedStart, &end);
    return fixedStart + unfixedStart;
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

bool LayoutByNW4R::isAbleToUp() {
    return mbUpVisible;
}

bool LayoutByNW4R::isAbleToDown() {
    return mbDownVisible;
}

bool LayoutByNW4R::updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release, void* data) {
    u32 buttons = mRepeatButtons;
    if (buttons & 1) onCommand(static_cast<INPUT_COMMAND>(8), NULL);
    if (buttons & 2) onCommand(static_cast<INPUT_COMMAND>(9), NULL);
    if (buttons & 8) onCommand(static_cast<INPUT_COMMAND>(10), NULL);
    if (buttons & 4) onCommand(static_cast<INPUT_COMMAND>(11), NULL);
    bool handled = nw4rmanager::Layout::updateInput(chan, x, y, trig, hold, release, data);
    if ((release & 0x800) && mpString->isOnSustain()) {
        onCommand(static_cast<INPUT_COMMAND>(13), NULL);
    }
    if (!handled && (hold & 0x800) && mpString->isOnSustain()) {
        nw4r::math::VEC2 point;
        point.x = x;
        point.y = y;
        if (-y < getGlobalLeftTopPos().y + (mRect.top - mRect.bottom) / 2.0f) {
            point.y = getGlobalLeftTopPos().y - 1.0f;
        } else {
            point.y = 1.0f + ((mRect.top - mRect.bottom) + getGlobalLeftTopPos().y);
        }
        onCommand(static_cast<INPUT_COMMAND>(16), &point);
    }
    return handled;
}

bool LayoutByNW4R::updateInput(textinput::input::HKBManager& hkbManager) {
    return nw4rmanager::Layout::updateInput(hkbManager);
}

void LayoutByNW4R::visibleSeparator(bool flag) {
    mbRepeat = flag;
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

namespace textinput {
namespace tistring {

void WithAtok::backSpace() {}
void WithAtok::changeKanaMode(bool kana) {}
void WithAtok::closeDictionary() {}
void WithAtok::commitPredicted(int index) {}
void WithAtok::confirm(const wchar_t* string) {}
void WithAtok::enableConfirmedString(bool enable) {}
void WithAtok::getCursorPos(u32* start, u32* end) {}
void WithAtok::getDrawString(DrawInfo& info) {}
void WithAtok::getPredicted(int index, wchar_t* string) {}
void WithAtok::initConverting() {}
void WithAtok::init() {}
void WithAtok::inputChar(wchar_t ch) {}
void WithAtok::openDictionary(void* atok, int atokSize, void* apot, int apotSize, void* nintendo, int nintendoSize) {}
void WithAtok::popBack() {}
void WithAtok::pushBack(wchar_t ch) {}
void WithAtok::resetRelation() {}
void WithAtok::setDefaultPrediction(int count, const char** predictions) {}
void WithAtok::setFixMode(bool fixed) {}
void WithAtok::setFixPrediction(int count, const char** predictions) {}
void WithAtok::setFix(bool fix) {}
void WithAtok::setInputting(wchar_t ch) {}
void WithAtok::setSelectedCandidate(s32 index) {}
void WithAtok::startConverting() {}
bool WithAtok::isFix() { return true; }
bool WithAtok::isConverting() { return false; }
s16 WithAtok::getSelectedConverting() { return 0; }
bool WithAtok::isDictionaryOpened() { return false; }
wchar_t* WithAtok::getConfirmedWCString() const { return NULL; }
bool WithAtok::hasConfirmedString() { return false; }
int WithAtok::getCurrentNumPredicted() { return 0; }
bool WithAtok::isCandidateSelected() { return false; }
s32 WithAtok::getSelectedCandidate() { return 0; }
s16 WithAtok::getFixedPredictionNum() { return 0; }
wchar_t WithAtok::getInputStringLength() { return 0; }
bool WithAtok::moveCursorLeft() { return false; }
bool WithAtok::moveCursorRight() { return false; }
void Decolated::EnableKSXFilter(bool enable) {}
void Decolated::deleteChar() {}

}
}

namespace textinput {
namespace tistring {
u32 Decolated::getCursorPos() const { return mCursorStart; }
bool Decolated::isOnSustain() { return mbSustain; }
void WithZi::setSelectedCandidate(s32 index) { mSelectedCandidate = index; }
void WithZi::setPredictLaunguage(PredictLanguage language) { mPredictLanguage = language; }
int WithZi::getCurrentNumPredicted() { return mCandidateCount; }
u16 WithZi::getInputStringLength() { return mInputLength; }
void WithZi::changeLetterMode(LetterMode mode) { mLetterMode = mode; }
void WithZi::setCellPhoneHoldingkey(void* key) { mpHoldingKey = key; }
}
namespace candidatebox {
bool Base::isInvalid() const { return mbInvalid; }
}
namespace textdrawer {
u32 Base::getEndPos() const { return muDrawEndPos; }
u32 Base::getDrawModifyStartLine() const { return muDrawModifyStartLine; }
u32 Base::getDrawModifyEndLine() const { return muDrawModifyEndLine; }
void Base::dirtyDrawCache() { mbDrawCache = false; }
void Base::dirtyCursorCache() { mbCursorCache = false; }
u32 Base::getDrawCacheStartPos() const {
    if (mbDrawCache) return muCachedStartPos;
    return 0x7fffffff;
}
}
}
