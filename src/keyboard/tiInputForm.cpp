#define TIINPUTFORM_IMPLEMENTATION
#include "keyboard/tiInputForm.h"
#include "keyboard/tiManager.h"
#include "keyboard/tiDebug.h"
#include "keyboard/tiLayoutGather.h"

#include <revolution/mtx.h>
#include <nw4r/math/triangular.h>
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

class EventHandler : public nw4rmanager::TiEventHandler {
public:
    EventHandler(LayoutByNW4R* form) : mpInputForm(form) {}
    virtual ~EventHandler();
    virtual void onTiEvent(gui::PaneComponent* component, u32 event, Input* input);
private:
    LayoutByNW4R* mpInputForm;
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
extern "C" void KPRInitQueue(KPRQueue* queue);
extern "C" void KPRSetMode(KPRQueue* queue, KPRMode mode);
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
extern "C" int wcsnicmp(const wchar_t* left, const wchar_t* right, u32 length);
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
extern "C" char scP_txtScrll_UP[];
extern "C" char scP_txtScrll_DOWN[];
extern "C" char scN_JPNUSAEUR[];
extern "C" char scN_separateBarAll[];
extern "C" char scT_2l_TextBox[];
extern "C" char scT_title_textJPN[];
extern "C" char scN_separateBarKOR[];
extern "C" char scT_2l_TextBoxKOR[];
extern "C" char scT_title_textKOR[];
extern "C" char scN_separateBarCHN[];
extern "C" char scT_2l_TextBoxCHN[];
extern "C" char scT_title_textCHN[];
extern "C" const char scN_KOR[];
extern "C" const char scN_CHN[];
extern "C" const f32 scInputFormZeroF;
extern "C" void _savegpr_20();
extern "C" void _restgpr_20();
extern "C" void _savegpr_27();
extern "C" void _restgpr_27();
extern "C" asm void __ct__Q34nw4r2ut10CharWriterFv();




extern "C" asm void __vt__Q29textinput15CommandReceiver();
extern "C" asm void __vt__Q39textinput10textdrawer4Base();
extern "C" asm void __vt__Q39textinput9inputform4Base();
extern "C" asm void __vt__Q39textinput9inputform12LayoutByNW4R();
extern "C" asm void __vt__Q39textinput4util9Animation();
extern "C" asm void __vt__Q39textinput9inputform10EditBuffer();
extern "C" asm void __vt__Q39textinput8tistring9Decolated();
extern "C" asm void __vt__Q39textinput8tistring8WithAtok();
extern "C" asm void __vt__Q39textinput8tistring6WithZi();
void Base::moveCandidateToIdx(s32 index) {
    if (mbPredictOn) {
        if (mpManager->getCandidateBox()->isInScroll()) return;
        if (mePredictMode == PM_Atok) {
            if (mpUnfixString->getFixedPredictionNum() && !mpUnfixString->isConverting()) {
                mpUnfixString->confirm(NULL);
                wchar_t* confirmed = mpUnfixString->getConfirmedWCString();
                mpString->getCursorPos();
                mpString->confirm(confirmed);
                mpString->getCursorPos();
                mpUnfixString->enableConfirmedString(false);
            }
            mpUnfixString->setSelectedCandidate(index);
        } else {
            mpZiString->setSelectedCandidate(index);
        }
        mpManager->getCandidateBox()->getTextArea().ChangeSelectedText(index);
    } else {
        meScrollFlag = SF_ScrollOn;
    }
}
void Base::confirmInput_() {
    if (!mbPredictOn) {
        if (!mpString->isKanaFix()) {
            mpString->getCursorPos();
            mpString->confirmKana();
            mpString->getCursorPos();
        }
    } else if (mePredictMode == PM_Atok) {
        if (mpUnfixString->isCandidateSelected()) {
            s32 selected = mpUnfixString->getSelectedCandidate();
            onCommand(static_cast<INPUT_COMMAND>(21), &selected);
        } else {
            mpUnfixString->confirm(NULL);
            wchar_t* confirmed = mpUnfixString->getConfirmedWCString();
            mpString->getCursorPos();
            mpString->confirm(confirmed);
            mpString->getCursorPos();
            mpUnfixString->enableConfirmedString(false);
        }
    } else {
        const wchar_t* selected = mpZiString->getCurrentSelected();
        if (mpZiString->getInputStringLength()) {
            mpString->getCursorPos();
            mpString->inputString(selected);
            mpString->getCursorPos();
            if (meLanguage == CN) mpZiString->setCurrentWord(selected);
        }
        mpZiString->clearCandidates();
        mbZuSelected = false;
        if (meLanguage == CN) mpZiString->update();
    }
}
void Base::inputInputting_(wchar_t character) {
    tistring::Decolated* current = getCurrentString(false);
    if (static_cast<u16>(character + 0xcf65) <= 1) {
        onCommand(static_cast<INPUT_COMMAND>(27), NULL);
    } else if (mbPredictOn && mePredictMode == PM_Atok) {
        if (mpUnfixString->isCandidateSelected()) onCommand(static_cast<INPUT_COMMAND>(6), NULL);
        mpUnfixString->setInputting(character);
    } else {
        if (mbPredictOn && getPredictMode() == PM_11 && !mpManager->getCandidateBox()->isInvalid()) {
            if (util::isAlphabet(character) || (character >= L'1' && character <= L'5')) {
                mpZiString->setInputting(character);
            } else {
                bool predictions;
                if (!mbPredictOn) predictions = false;
                else if (mePredictMode != PM_Atok && mpZiString->getCurrentNumPredicted() > 0) predictions = true;
                else predictions = false;
                if (predictions && mpZiString->getInputStringLength() != 0 && (meLanguage != CN || !mpZiString->hasCandidate())) confirmInput_();
                mpZiString->setInputting(character);
                mpZiString->setSelectedCandidate(-1);
                return;
            }
        } else {
            current->setCandidate(character);
        }
    }
    if (character != 0) onSE(sound::SE_CHAR_INPUT);
    meScrollFlag = SF_ScrollOn;
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
    if (character == L' ') onSE(sound::SE_CHAR_DECIDE);
    else if (character != L'\n') onSE(sound::SE_CHAR_INPUT);
    meScrollFlag = SF_ScrollOn;
}

void LayoutByNW4R::draw() {
    nw4rmanager::Layout::draw();
    muGlobalAlpha = getLayout()->GetRootPane()->GetAlpha();
    nw4r::lyt::Pane* textBox = mpLayout->GetRootPane()->FindPaneByName(static_cast<const char*>(mpLayoutData), true);
    AdjustPaneMtx(mMtx.m, mDrawInfo, textBox->GetGlobalMtx());
    Base::draw();
}
void Base::calcCursorTimer() {
    muCursorTimer += 8;
}
bool Base::isAtokActive() const {
    u32 enabled = mbPredictOn;
    if (enabled == 0) return false;
    return mePredictMode == PM_Atok;
}
void Base::dirtyCacheAll() {
    dirtyCursorCache();
    dirtyDrawCache();
}
void Base::initZiString() {
    mpZiString->clearCandidates();
    mbZuSelected = false;
}
void Base::resetContextPredict_() {
    getCurrentString(false);
    resetPredictionContext();
}

static GXColor kanaBackground = {128, 255, 128, 255};
static GXColor candidateBackground = {255, 210, 12, 255};
const char* csScrollButtonAnimationTarget = scP_txtScrll_UP;

struct InputFormAnimationFile {
    u32 id;
    char fileName[0x40];
};

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

extern "C" const VisiblePanes csVisiblePaneUEJ__Q29textinput9inputform = {
    1, 2,
    {scN_JPNUSAEUR, NULL, NULL, NULL},
    {"N_KOR", "N_CHN", NULL, NULL},
};

extern "C" const VisiblePanes csVisiblePaneKOR__Q29textinput9inputform = {
    1, 2,
    {"N_KOR", NULL, NULL, NULL},
    {"N_CHN", scN_JPNUSAEUR, NULL, NULL},
};

extern "C" const void* const csVisiblePaneCHN__Q29textinput9inputform[10] = {
    (const void*)0x00010002,
    "N_CHN",
    0,
    0,
    0,
    "N_KOR",
    scN_JPNUSAEUR,
    0,
    0,
    0,
};

extern "C" const LanguagePaneData csLanguageDependencyDataUEJ__Q29textinput9inputform = {
    &csVisiblePaneUEJ__Q29textinput9inputform,
    scN_separateBarAll,
    scT_2l_TextBox,
    scT_title_textJPN,
};

extern "C" const LanguagePaneData csLanguageDependencyDataKOR__Q29textinput9inputform = {
    &csVisiblePaneKOR__Q29textinput9inputform,
    scN_separateBarKOR,
    scT_2l_TextBoxKOR,
    scT_title_textKOR,
};

extern "C" const LanguagePaneData csLanguageDependencyDataCHN__Q29textinput9inputform = {
    reinterpret_cast<const VisiblePanes*>(csVisiblePaneCHN__Q29textinput9inputform),
    scN_separateBarCHN,
    scT_2l_TextBoxCHN,
    scT_title_textCHN,
};

extern "C" const wchar_t pppURLCheck[2][10] = {L"http://", L"https://"};


extern "C" const f32 scInputFormZeroF = 0.0f;
extern "C" const f32 scInputForm640F = 640.0f;
extern "C" const f64 scInputFormF32ConvertMagic = 4503601774854144.0;
extern "C" const f32 scInputFormOneF = 1.0f;
extern "C" const f32 scInputFormHalfF = 0.5f;
extern "C" const f32 scInputFormDegToFIdxF = 0.7111111f;
extern "C" const f32 scInputForm150F = 150.0f;
extern "C" const f32 scInputForm30F = 30.0f;
extern "C" const f32 scInputForm50F = 50.0f;
extern "C" const f32 scInputForm10F = 10.0f;
extern "C" const f32 scInputForm52F = 52.0f;
extern "C" const f32 scInputFormTwoF = 2.0f;
extern "C" const f32 scInputForm140F = 140.0f;
extern "C" const f32 scInputForm90F = 90.0f;
extern "C" const f32 scInputForm253F = 253.0f;
extern "C" const f32 scInputForm20F = 20.0f;
extern "C" const u8 scInputFormColorRU8 = 0xff;
extern "C" const u8 scInputFormColorGU8 = 0x32;
extern "C" const u8 scInputFormColorBU8 = 0x32;
extern "C" const u8 scInputFormColorAU8 = 0;
extern "C" const f32 scInputForm255F = 255.0f;
extern "C" const f32 scInputForm127F = 127.0f;
extern "C" const f32 scInputForm14592F = 14592.0f;
extern "C" const f64 scInputFormF64ConvertMagic = 4503599627370496.0;
extern "C" const f32 scInputForm15F = 15.0f;
f32 sfColorPhase;

bool mbHyphen = true;

extern "C" char scP_txtScrll_UP[] = "P_txtScrll_UP";
extern "C" char scP_txtScrll_DOWN[] = "P_txtScrll_DOWN";
struct ButtonAnimations {
    KeyType type;
    const char* paneName;
    u32 count;
    const char* bindingName;
    const InputFormAnimationFile* files[12];
};

const ButtonAnimations csButtonAnimations[] = {
    {KT_NormalButton, scP_txtScrll_UP, 8, NULL, {
        &csAninationFile__Q29textinput9inputform[0], &csAninationFile__Q29textinput9inputform[1],
        &csAninationFile__Q29textinput9inputform[2], &csAninationFile__Q29textinput9inputform[3],
        &csAninationFile__Q29textinput9inputform[4], &csAninationFile__Q29textinput9inputform[5],
        &csAninationFile__Q29textinput9inputform[6], &csAninationFile__Q29textinput9inputform[7]}},
    {KT_NormalButton, scP_txtScrll_DOWN, 8, csScrollButtonAnimationTarget, {
        &csAninationFile__Q29textinput9inputform[0], &csAninationFile__Q29textinput9inputform[1],
        &csAninationFile__Q29textinput9inputform[2], &csAninationFile__Q29textinput9inputform[3],
        &csAninationFile__Q29textinput9inputform[4], &csAninationFile__Q29textinput9inputform[5],
        &csAninationFile__Q29textinput9inputform[6], &csAninationFile__Q29textinput9inputform[7]}}
};
extern "C" char scN_JPNUSAEUR[] = "N_JPNUSAEUR";
extern "C" char scN_separateBarAll[] = "N_separateBarAll";
extern "C" char scT_2l_TextBox[] = "T_2l_TextBox";
extern "C" char scT_title_textJPN[] = "T_title_textJPN";
extern "C" char scN_separateBarKOR[] = "N_separateBarKOR";
extern "C" char scT_2l_TextBoxKOR[] = "T_2l_TextBoxKOR";
extern "C" char scT_title_textKOR[] = "T_title_textKOR";
extern "C" char scN_separateBarCHN[] = "N_separateBarCHN";
extern "C" char scT_2l_TextBoxCHN[] = "T_2l_TextBoxCHN";
extern "C" char scT_title_textCHN[] = "T_title_textCHN";
bool DeadKeyStream::sbCompatibleFilterEnabled = true;

#pragma push
#pragma section const_type ".data"
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
#pragma pop

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
        case DE:
            setPredictMode(PM_De);
            break;
        case IT:
            setPredictMode(PM_It);
            break;
        case NL:
            setPredictMode(PM_Nl);
            break;
        case SP:
            if (meDestination == DST_EU) {
                setPredictMode(PM_Sp);
            } else {
                setPredictMode(PM_USSp);
            }
            break;
        case FR:
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
    u32 data;
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
    wchar_t atokPrediction[64];
    wchar_t ziPrediction[64];
    wchar_t ziInput[64];
    switch (command) {
    case 40:
        if (current == mpUnfixString) {
            if (LayoutGather::Singleton::getInstance().isHoldingShift()) onPressUp();
            else onPressDown();
            return;
        }
        if (mDKStream.lookAhead()) mDKStream.putChar(0xffff);
        else mDKStream.putChar(L' ');
        if (mDKStream.isEmpty()) onSE(sound::SE_CHAR_INPUT);
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
        struct InputModeState {
            tistring::Decolated::TranslateMode mode;
            bool kana;
            bool direct;
        };
        InputModeState savedState;
        InputModeState keyboardState;

        if (input->keyboardMode) {
            keyboardState.mode = static_cast<tistring::Decolated::TranslateMode>(mpManager->getPCKeyboard()->getTranslateMode());
            keyboardState.direct = mpManager->getPCKeyboard()->getTranslateMode() == keyboard::pctype::Base::TM_00;
            keyboardState.kana = mpManager->getPCKeyboard()->getTranslateMode() == keyboard::pctype::Base::TM_Kana;
            tistring::Decolated* active = getCurrentString(false);
            savedState.mode = active->getTranslateMode();
            if (active == mpString) {
                tistring::Decolated::TranslateMode mode = keyboardState.mode;
                if (meLanguage == KR) {
                    if (mode != tistring::Decolated::TM_Direct) mode = tistring::Decolated::TM_Hangul;
                } else if (meLanguage == CN) mode = tistring::Decolated::TM_Direct;
                mpString->getCursorPos();
                mpString->setTranslateMode(mode);
                mpString->getCursorPos();
            } else active->setTranslateMode(keyboardState.mode);
            bool useAtok = isAtokActive();
            if (useAtok) {
                savedState.direct = false;
                savedState.kana = false;
                mpUnfixString->setFixMode(keyboardState.direct);
                mpUnfixString->changeKanaMode(keyboardState.kana);
            }
        }
        if (input->deadKey) character = DeadKeyStream::ToCombineClass(meLanguage, character);
        if (character == L' ' && mDKStream.lookAhead()) mDKStream.putChar(0xffff);
        else mDKStream.putChar(character);
        if (mDKStream.isEmpty()) onSE(sound::SE_CHAR_INPUT);
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
                tistring::Decolated::TranslateMode mode = savedState.mode;
                if (meLanguage == KR) {
                    if (mode != tistring::Decolated::TM_Direct) mode = tistring::Decolated::TM_Hangul;
                } else if (meLanguage == CN) mode = tistring::Decolated::TM_Direct;
                mpString->getCursorPos();
                mpString->setTranslateMode(mode);
                mpString->getCursorPos();
            } else active->setTranslateMode(savedState.mode);
            bool useAtok = isAtokActive();
            if (useAtok) {
                mpUnfixString->setFixMode(savedState.direct);
                mpUnfixString->changeKanaMode(savedState.kana);
            }
        }
        if (checkHeadOfSentence(true)) onCommand(static_cast<INPUT_COMMAND>(33), NULL);
        break;
    }
    case 1:
        if (current->canBackSpace()) onSE(sound::SE_CHAR_DELETE);
        else onSE(sound::SE_CHAR_DELETE_ERROR);
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
        if (current != fixed) {
            onSE(sound::SE_CHAR_DELETE_ERROR);
            return;
        }
        if (!fixed->deleteForward()) onSE(sound::SE_CHAR_DELETE_ERROR);
        else onSE(sound::SE_CHAR_DELETE);
        break;
    case 7:
        if (current == fixed) {
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
            if (mpManager->getToolBar()->isQwerty()) lineFeed = mpManager->getPCKeyboard()->hasLineFeedButton();
            else lineFeed = mpManager->getCellPhoneKeyboard()->hasLineFeedButton();
            bool allowed = true;
            if (mpString->isKanaFix()) {
                bool withinLimit = false;
                if (lineFeed && muLimitRowNum >= static_cast<u32>(getLine() + 1)) withinLimit = true;
                if (!withinLimit) allowed = false;
            }
            bool atLimit = true;
            if (muLimitRowNum >= static_cast<u32>(getLine() + 1) && !mpManager->getCandidateBox()->isActive()) atLimit = false;
            if (allowed) {
                onSE(sound::SE_CHAR_DECIDE);
                mpString->getCursorPos();
                mpString->inputChar(L'\n');
                mpString->getCursorPos();
                if (meLanguage == CN && hasZiPredictions()) {
                    mpZiString->setCurrentWord(NULL);
                    mpZiString->update();
                }
            } else {
                if (atLimit) {
                    onSE(sound::SE_CHAR_DELETE_ERROR);
                    return;
                } else return;
            }
        } else if (current == mpZiString) {
            onSE(sound::SE_CHAR_DECIDE);
            if (getPredictMode() == PM_11 || getPredictMode() == PM_12) confirmInput_();
            else if (!(mbCursorSelected | mbZuSelected) && mpManager->getToolBar()->isQwerty()) {
                if (mbPredictOn && mePredictMode != PM_Atok) {
                    mpZiString->getCurrentInput(ziInput, 64);
                    mpString->getCursorPos();
                    mpString->inputString(ziInput);
                    mpString->getCursorPos();
                    mpZiString->clearCandidates();
                    mbZuSelected = false;
                    getCurrentString(false);
                    resetPredictionContext();
                }
            } else confirmInput_();
        } else {
            onSE(sound::SE_CHAR_DECIDE);
            if (mpUnfixString->isConverting()) {
                mpUnfixString->commitPredicted(mpUnfixString->getSelectedConverting());
                updateCandidateState_();
            } else confirmInput_();
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
            if (input->confirmOnly) onSE(sound::SE_CHAR_DECIDE);
            else onSE(sound::SE_CHAR_INPUT);
        }
        meScrollFlag = SF_ScrollOn;
        if (checkHeadOfSentence(true)) onCommand(static_cast<INPUT_COMMAND>(33), NULL);
        break;
    }
    case 8:
        if (current == fixed) onPressLeft();
        else onHKBCtrlCode(static_cast<HVKCode>(31), 0);
        return;
    case 9:
        if (current == fixed) onPressRight();
        else onHKBCtrlCode(static_cast<HVKCode>(32), 0);
        return;
    case 10: onPressUp(); return;
    case 11: onPressDown(); return;
    case 24: doScroll(static_cast<Scroll*>(data)); return;
    case 14:
        if (currentIsFixed && current->isKanaFix()) {
            nw4r::math::VEC2 origin = getGlobalLeftTopPos();
            nw4r::math::VEC2* cursor = static_cast<nw4r::math::VEC2*>(data);
            current->setCursorPos(calcCursorPos(cursor->x - origin.x, cursor->y - origin.y));
            onSE(sound::SE_CHAR_CURSOR);
            onCommand(static_cast<INPUT_COMMAND>(12), NULL);
            resetInputRelation();
        } else {
            onSE(sound::SE_CHAR_DECIDE);
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
            if (previous != position) onSE(sound::SE_CHAR_CURSOR);
            meScrollFlag = SF_ScrollOn;
        }
        return;
    case 17:
        if (data && *static_cast<bool*>(data)) {
            mpUnfixString->confirm(NULL);
            onCommand(static_cast<INPUT_COMMAND>(6), NULL);
            candidatebox::CandidateBoxCaller::resetCandidate();
            candidatebox::CandidateBoxCaller::updateCandidate();
        }
        break;
    case 21: {
        if (mbPredictOn) {
            if (mePredictMode == PM_Atok) {
                if (mpUnfixString->isConverting()) mpUnfixString->commitPredicted(*static_cast<s32*>(data));
                else {
                    mpUnfixString->getPredicted(*static_cast<s32*>(data), atokPrediction);
                    mpString->getCursorPos();
                    mpString->inputString(atokPrediction, tistring::Decolated::TM_Direct);
                    mpString->getCursorPos();
                    mpUnfixString->commitPredicted(*static_cast<s32*>(data));
                }
            } else {
                mpZiString->getPredicted(*static_cast<s32*>(data), ziPrediction);
                mpString->getCursorPos();
                mpString->inputString(ziPrediction);
                mpString->getCursorPos();
                mpZiString->clearCandidates();
                mbZuSelected = false;
                if (meLanguage == CN) {
                    mpZiString->setCurrentWord(ziPrediction);
                    mpZiString->update();
                }
            }
        }
        meScrollFlag = SF_ScrollOn;
        break;
    }
    case 18: {
        tistring::Decolated::TranslateMode fixedMode;
        tistring::Decolated::TranslateMode mode = *static_cast<tistring::Decolated::TranslateMode*>(data);
        if (meLanguage != JP && meLanguage != KR) mode = tistring::Decolated::TM_Direct;
        fixedMode = mode;
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
    case 25: current->converDakuten(); onSE(sound::SE_CHAR_INPUT); break;
    case 26: current->converHandaku(); onSE(sound::SE_CHAR_INPUT); break;
    case 27: current->convertAll(); break;
    case 28: current->converSmall(); onSE(sound::SE_CHAR_INPUT); break;
    case 29: {
        PredictionState* prediction = static_cast<PredictionState*>(data);
        mePredictMode = prediction->mode;
        bool enabled = prediction->enabled != false;
        if (mbPredictOn != enabled) {
            mbPredictOn = enabled;
            if (meLanguage == KR) mpManager->getPCKeyboard()->refreshState();
        }
        s32 predictionFixedMode = mpString->getTranslateMode();
        s32 predictionUnfixMode = mpUnfixString->getTranslateMode();
        mpString->initKanaConverter();
        mpUnfixString->initKanaConverter();
        if (meLanguage == KR) {
            if (predictionFixedMode != tistring::Decolated::TM_Direct) predictionFixedMode = tistring::Decolated::TM_Hangul;
        } else if (meLanguage == CN) predictionFixedMode = tistring::Decolated::TM_Direct;
        mpString->getCursorPos();
        mpString->setTranslateMode(static_cast<tistring::Decolated::TranslateMode>(predictionFixedMode));
        mpString->getCursorPos();
        mpUnfixString->setTranslateMode(static_cast<tistring::Decolated::TranslateMode>(predictionUnfixMode));
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
        case PM_12: {
            bool qwerty = mpManager->getToolBar()->isQwerty();
            tistring::WithZi::PredictLanguage language = static_cast<tistring::WithZi::PredictLanguage>(11);
            if (qwerty) language = static_cast<tistring::WithZi::PredictLanguage>(10);
            mpZiString->setPredictLaunguage(language);
            break;
        }
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
        candidatebox::CandidateBoxCaller::resetCandidate();
        return;
    }
    case 31: {
        PredictionState* prediction = static_cast<PredictionState*>(data);
        prediction->mode = mePredictMode;
        prediction->enabled = mbPredictOn;
        return;
    }
    case 32: *static_cast<bool*>(data) = hasZiPredictions(); return;
    case 38: {
        ControlInput* input = static_cast<ControlInput*>(data);
        onHKBCtrlCode(input->code, input->modifiers);
        return;
    }
    case 41: notifyChangeMode(); return;
    case 42: onPressLeftHWKB(); return;
    case 43: onPressRightHWKB(); return;
    case 44: onPressUp(); return;
    case 45: onPressDownHWKB(); return;
    case 39: mDKStream.clear(); return;
    case 47: return;
    case 36: {
        u32 length = *static_cast<u32*>(data);
        if (fixed->getLength() > length) mpString->getLength();
        mpString->setLength(static_cast<u16>(length));
        return;
    }
    case 46:
        if (meLanguage == CN && !mpManager->getPCKeyboard()->isQwertyOnly() && mpManager->getPCKeyboard()->isLanguageKeyActive()) {
            if (mpManager->getPCKeyboard()->getTranslateMode() == keyboard::pctype::Base::TM_00) mpManager->getPCKeyboard()->setTranslateMode(keyboard::pctype::Base::TM_Kana);
            else mpManager->getPCKeyboard()->setTranslateMode(keyboard::pctype::Base::TM_00);
        }
        break;
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
                if (!mpManager->getPCKeyboard()->isQwertyOnly()) onSE(sound::SE_CHAR_CURSOR_FIX);
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
      mpLanguageData(&csLanguageDependencyDataUEJ__Q29textinput9inputform), mpFontName(fontName),
      mbUpVisible(false), mbDownVisible(false), mbRepeat(false), mpInputEventHandler(NULL) {}

static inline const char* selectInputTextName(const nw4rmanager::Layout& layout, const void* const& languageData) {
    if (layout.getPane(static_cast<const LanguagePaneData*>(languageData)->textBox)) {
        return static_cast<const LanguagePaneData*>(languageData)->textBox;
    }
    return "T_2l_TextBox";
}

inline nw4r::lyt::TextBox* LayoutByNW4R::getTextBox() const {
    nw4r::lyt::TextBox* textBox = static_cast<nw4r::lyt::TextBox*>(mpLayout->GetRootPane()->FindPaneByName(static_cast<const char*>(mpLayoutData), true));
    return textBox;
}

void LayoutByNW4R::create(MEMAllocator* allocator, EditBuffer* editBuffer) {
    nw4r::lyt::Pane* pane;
    void* handlerMemory;
    mpAllocator = allocator;
    textdrawer::Base::create(allocator);
    mpString = static_cast<tistring::Decolated*>(editBuffer->mpString);
    mpUnfixString = static_cast<tistring::WithAtok*>(editBuffer->mpUnfixString);
    mpZiString = static_cast<tistring::WithZi*>(editBuffer->mpZiString);
    mriManager.mpAllocator = allocator;
    mriManager.mpInfo = static_cast<Info_*>(MEMAllocFromAllocator(allocator, (mriManager.mMaxLength + 2) * sizeof(Info_)));
    mriManager.init();
    Info_* rows;
    Info_* row;
    u16 next;
    u16 previous;
    u16 selectedIndex;
    Info_* listEnd;
    Info_* info;
    rows = mriManager.mpInfo;
    row = &rows[mriManager.mMaxLength];
    row = &rows[row->Next];
    next = row->Next;
    previous = row->Back;
    selectedIndex = rows[next].Back;
    rows[next].Back = previous;
    rows[previous].Next = next;
    row->Back = selectedIndex;
    row->Next = selectedIndex;
    info = mriManager.mpInfo;
    listEnd = &info[info[static_cast<u16>(mriManager.mMaxLength + 1)].Back];
    if (row->Back == row->Next) {
        u16 head = listEnd->Next;
        row->Back = info[head].Back;
        row->Next = head;
        listEnd->Next = selectedIndex;
        info[head].Back = selectedIndex;
    }
    row->StrCount = 0;
    row->DispRowCount = 1;
    mpCursorLine = row;
    handlerMemory = MEMAllocFromAllocator(allocator, sizeof(EventHandler));
    mpInputEventHandler = new (handlerMemory) EventHandler(this);
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
    nw4r::lyt::TextBox* textBox = getTextBox();
    textBox->SetString(L"", 0);
    mfCharacterSpacing = textBox->GetCharSpace();
    mfLineSpacing = textBox->GetLineSpace();
    mfFontWidth = textBox->GetFontSize().width;
    mfFontHeight = textBox->GetFontSize().height;
    mRect = textBox->GetPaneRect(mDrawInfo);
    AdjustPaneMtx(mMtx.m, mDrawInfo, textBox->GetGlobalMtx());
    csCharColor = textBox->GetTextColor(nw4r::lyt::TEXTCOLOR_TOP);
    setVisible("N_2line", true);
    mpPaneManager->setAllComponentTriggerTarget(false);
    mpPaneManager->setAllBoundingBoxComponentTriggerTarget(true);
    pane = mpLayout->GetRootPane()->FindPaneByName(static_cast<const LanguagePaneData*>(mpLanguageData)->textBox, true);
    if (!pane) pane = mpLayout->GetRootPane()->FindPaneByName(selectInputTextName(*this, mpLanguageData), true);
    mpPaneManager->getPaneComponentByPane(pane)->setTriggerTarget(true);
    for (u16 buttonIndex = 0; buttonIndex < 2; buttonIndex++) {
        const ButtonAnimations& button = csButtonAnimations[buttonIndex];
        nw4rmanager::AnmPane* animationPane = NULL;
        switch (button.type) {
        case KT_NormalButton: {
            void* memory = MEMAllocFromAllocator(allocator, sizeof(NormalButtonAnmPane));
            animationPane = new (memory) NormalButtonAnmPane(getPane(button.paneName), NULL);
            break;
        }
        }
        nw4r::ut::List_Append(&mAnmPanes, animationPane);
        for (u16 animationIndex = 0; animationIndex < button.count; animationIndex++) {
            void* resource = mpMultiArcResourceAccessor->GetResource(0, button.files[animationIndex]->fileName);
            AnimTransformPane* transform = static_cast<AnimTransformPane*>(getLayout()->CreateAnimTransform(resource, mpMultiArcResourceAccessor));
            if (button.bindingName == NULL) {
                animationPane->addAnimation(allocator, button.files[animationIndex]->id, transform, false, true);
            } else {
                animationPane->forceAddAnimation(allocator, button.files[animationIndex]->id, transform, button.bindingName, false, true);
            }
        }
    }
    init();
}
inline const nw4r::lyt::Pane* LayoutByNW4R::getLanguageTextPane() const {
    return getPane(static_cast<const LanguagePaneData*>(mpLanguageData)->textBox);
}

void LayoutByNW4R::init() {
    Base::init();
    searchAnmPane("P_txtScrll_UP")->changeAnimation(ANM_Off);
    searchAnmPane("P_txtScrll_DOWN")->changeAnimation(ANM_Off);
    mbUpVisible = false;
    mbDownVisible = false;
    mUpRepeat = 0;
    mDownRepeat = 0;
    mLeftRepeat = 0;
    mRightRepeat = 0;
    mRepeatButtons = 0;
    mCharColor = csCharColor;
    visibleSeparator(false);
    nw4r::lyt::TextBox* textBox = getTextBox();
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
void LayoutByNW4R::calc() {
    Base::calc();
    nw4rmanager::Layout::calc();
    bool up = false;
    bool down = false;
    const char* separator = static_cast<const LanguagePaneData*>(mpLanguageData)->separator;
    if (getPane(separator)) setVisible(static_cast<const LanguagePaneData*>(mpLanguageData)->separator, mbRepeat);
    else setVisible("N_separateBarAll", mbRepeat);
    if (!mScrollAnm.isActive()) {
        if (0.0f > mfScrollY) up = true;
        if (mfMinScrollY < mfScrollY) down = true;
        if (mbUpVisible != up) {
            mbUpVisible = up;
            if (up) {
                searchAnmPane("P_txtScrll_UP")->onAnmEvent(nw4rmanager::AnmPane::PE_6);
                mpPaneManager->searchPaneComponent("P_txtScrll_UP")->init();
            } else searchAnmPane("P_txtScrll_UP")->onAnmEvent(nw4rmanager::AnmPane::PE_7);
        }
        if (mbDownVisible != down) {
            mbDownVisible = down;
            if (down) {
                searchAnmPane("P_txtScrll_DOWN")->onAnmEvent(nw4rmanager::AnmPane::PE_6);
                mpPaneManager->searchPaneComponent("P_txtScrll_DOWN")->init();
            } else searchAnmPane("P_txtScrll_DOWN")->onAnmEvent(nw4rmanager::AnmPane::PE_7);
        }
    }
}

void LayoutByNW4R::setLanguage(Language language) {
    Base::setLanguage(language);
    if (language == CN) mpLanguageData = &csLanguageDependencyDataCHN__Q29textinput9inputform;
    else if (language == KR) mpLanguageData = &csLanguageDependencyDataKOR__Q29textinput9inputform;
    else mpLanguageData = &csLanguageDependencyDataUEJ__Q29textinput9inputform;
    const char* textName;
    if (!getLanguageTextPane()) textName = "T_2l_TextBox";
    else textName = static_cast<const LanguagePaneData*>(mpLanguageData)->textBox;
    mpLayoutData = textName;
    if (::strcmp(static_cast<const char*>(mpLayoutData), "T_2l_TextBox") != 0) setVisible("T_2l_TextBox", false);
    nw4r::lyt::Pane* pane = mpLayout->GetRootPane()->FindPaneByName(selectInputTextName(*this, mpLanguageData), true);
    static_cast<nw4r::lyt::TextBox*>(pane)->SetString(L"", 0);
    const VisiblePanes* visibility = static_cast<const LanguagePaneData*>(mpLanguageData)->visibility;
    for (u16 index = 0; index < visibility->visibleCount; ++index) setVisible(visibility->visibleNames[index], true);
    for (u16 index = 0; index < visibility->hiddenCount; ++index) setVisible(visibility->hiddenNames[index], false);
    pane = mpLayout->GetRootPane()->FindPaneByName(selectInputTextName(*this, mpLanguageData), true);
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
            onSE(sound::SE_CHAR_DELETE_ERROR);
        }
        if (!mpString->isKanaFix()) limit = muLimitStringLength - 1;
    }
    if (limit < mpString->getLength()) {
        u32 start, end;
        mpString->getCursorPos(&start, &end);
        if (start > limit || end > limit) {
            onSE(sound::SE_CHAR_DELETE_ERROR);
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
                    onSE(sound::SE_CHAR_DELETE_ERROR);
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
        onSE(sound::SE_CHAR_DELETE_ERROR);
        Base::onCommand(static_cast<INPUT_COMMAND>(36), &rowLimit);
        if (meLanguage == KR && !mpString->isKanaFix()) {
            rowLimit = isOverRowLimit(muLimitRowNum, mpString->getWCString());
            if (rowLimit) mpString->clearKana();
        }
    }
}



void EventHandler::onTiEvent(gui::PaneComponent* component, u32 event, Input* input) {
    char animationName[17];
    const char* name = component->getPane()->GetName();
    nw4r::math::VEC2 cursor;
    cursor.x = input->x;
    cursor.y = -input->y;
    if (name[0] == 'B') {
        util::replaceChar(animationName, 17, name, 0, 'P');
        if (event == gui::EventHandler::ON_TRIG && (input->trigger & WPAD_BUTTON_A) && !mpInputForm->isInScroll()) {
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
        if (event == gui::EventHandler::ON_MOVE && (input->hold & WPAD_BUTTON_A) && !(input->trigger & WPAD_BUTTON_A)) {
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
            case gui::EventHandler::ON_LEFT: animation->onAnmEvent(nw4rmanager::AnmPane::PE_2); break;
            case gui::EventHandler::ON_POINT:
                if (animation->getState() != ANM_Off) {
                    mpEventObserver->onSE(sound::SE_SELECT);
                    animation->onAnmEvent(nw4rmanager::AnmPane::PE_1);
                }
                break;
            }
        }
    } else if (name[0] == 'P') {
        AnmPane* animation = static_cast<AnmPane*>(mpInputForm->searchAnmPane(name));
        if (animation) {
            switch (event) {
            case gui::EventHandler::ON_POINT:
                if (animation->getState() != ANM_Off) {
                    mpEventObserver->onSE(sound::SE_SELECT);
                    animation->onAnmEvent(nw4rmanager::AnmPane::PE_1);
                }
                break;
            case gui::EventHandler::ON_LEFT:
                if (animation->getState() != ANM_Off) {
                    mpEventObserver->onSE(sound::SE_SELECT);
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
            if (event == gui::EventHandler::ON_TRIG && (input->trigger & WPAD_BUTTON_A)) mpInputForm->onCommand(static_cast<CommandReceiver::INPUT_COMMAND>(14), &cursor);
            if (event == gui::EventHandler::ON_RELEASE && (input->release & WPAD_BUTTON_A)) mpInputForm->onCommand(static_cast<CommandReceiver::INPUT_COMMAND>(15), &cursor);
            if (event == gui::EventHandler::ON_MOVE && (input->hold & WPAD_BUTTON_A)) mpInputForm->onCommand(static_cast<CommandReceiver::INPUT_COMMAND>(16), &cursor);
        }
    }
}

void Base::enableSpaceByRight(bool rightWithSpace) {
    mbRightWithSpace = rightWithSpace;
}

void Base::setDestination(Destination destination) {
    meDestination = destination;
}

bool Base::findURL(u32* start, u32* end, const wchar_t* string, u32 from, u32 to) {
    const wchar_t* prefix;
    const wchar_t* current;
    bool found;
    bool wordStart;
    const wchar_t* prefixes = pppURLCheck[0];
    u32 position;
    u32 prefixIndex;
    u32 length;
    found = false;
    wordStart = true;
    for (position = from; position < to; ++position) {
        wchar_t character = string[position];
        if (s32(character) < L'A') {
            if (s32(character) == L'\r') goto separator;
            if (s32(character) < L'\r') {
                if (s32(character) == L'\n') goto separator;
                if (s32(character) >= L'\n') goto punctuation;
                if (!character) goto endString;
                goto punctuation;
            }
            if (s32(character) < L'0') {
                if (s32(character) == L' ') goto separator;
                goto punctuation;
            }
            if (s32(character) >= L':') goto punctuation;
            goto wordCharacter;
        }
        if (s32(character) == L'h') goto prefixStart;
        if (s32(character) < L'h') {
            if (s32(character) < L'[') {
                if (s32(character) == L'H') goto prefixStart;
                goto wordCharacter;
            }
            if (s32(character) >= L'a') goto wordCharacter;
            goto punctuation;
        }
        if (s32(character) == 0x3000) goto separator;
        if (s32(character) >= 0x3000) goto punctuation;
        if (s32(character) >= L'{') goto punctuation;
        goto wordCharacter;
    endString:
        if (found && end) *end = position;
        return found;
    separator: {
            if (!found) wordStart = true;
            else {
                if (end) *end = position;
                return true;
            }
            goto nextCharacter;
        }
    prefixStart: {
            if (wordStart && !found) {
                prefix = prefixes;
                current = &string[position];
                wordStart = false;
                for (prefixIndex = 0; prefixIndex < 2; ++prefixIndex, prefix += 10) {
                    length = wcslen(prefix);
                    if (!wcsnicmp(current, prefix, length)) {
                        if (start) *start = position;
                        found = true;
                        position += length - 1;
                        break;
                    }
                }
            }
            goto nextCharacter;
        }
    wordCharacter:
        wordStart = false;
        goto nextCharacter;
    punctuation:
        wordStart = true;
    nextCharacter:
        continue;
    }
    return found;
}

void Base::autoScroll() {
    if (mScrollAnm.isActive()) return;
    if (u32(meScrollFlag - SF_ScrollOn) > 1) return;
    f32 cursorY = mfCursorY + getLineHeight() / 2.0f;
    if (cursorY < 0.0f) {
        s32 lines = s32(cursorY / getLineHeight() - 1.0f);
        mScrollAnm.startAnm(mfScrollY, mfScrollY - lines * getLineHeight(), 15.0f, NULL, NULL);
        onSE(sound::SE_LINE_SCROLL);
    }
    if (cursorY >= (mRect.top - mRect.bottom) * getScale().y) {
        s32 lines = s32((cursorY - (mRect.top - mRect.bottom) * getScale().y) / getLineHeight()) + 1;
        mScrollAnm.startAnm(mfScrollY, mfScrollY - lines * getLineHeight(), 15.0f, NULL, NULL);
        onSE(sound::SE_LINE_SCROLL);
    }
    meScrollFlag = SF_NoScroll;
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

void Base::deselectCandidate() {
    if (!mbPredictOn) return;
    if (mePredictMode != PM_Atok) return;
    mpUnfixString->setSelectedCandidate(-1);
}

void Base::resetRelation() {
    mpManager->getHWKeyboard()->resetQuoteState();
    mpUnfixString->resetRelation();
}

inline void DeadKeyStream::init() {
    KPRInitQueue(&mKPRQueue);
    KPRSetMode(&mKPRQueue, KPR_MODE_DEADKEY);
}

void Base::init() {
    meInputMode = IM_Direct;
    mfCursorX = 0.0f;
    mfCursorY = 0.0f;
    mfScrollX = 0.0f;
    mfScrollY = 0.0f;
    mfSustainTimer = 0.0f;
    mfCursorTimer = 0.0f;
    muGlobalAlpha = 255;
    mDKStream.init();
    SetFixedWidth(GetFont()->GetWidth());
    EnableFixedWidth(false);
    enableSpaceByRight(true);
    mpManager->getHWKeyboard()->resetQuoteState();
    mpUnfixString->resetRelation();
    updateCandidateState_();
    dirtyDrawCache();
    dirtyCursorCache();
    mfDrawScrollY = mfScrollY;
}

void Base::create(MEMAllocator* allocator, EditBuffer* editBuffer) {
    mpAllocator = allocator;
    textdrawer::Base::create(allocator);
    mpString = static_cast<tistring::Decolated*>(editBuffer->mpString);
    mpUnfixString = static_cast<tistring::WithAtok*>(editBuffer->mpUnfixString);
    mpZiString = static_cast<tistring::WithZi*>(editBuffer->mpZiString);
    mriManager.mpAllocator = allocator;
    mriManager.mpInfo = static_cast<Info_*>(MEMAllocFromAllocator(allocator, (mriManager.mMaxLength + 2) * sizeof(Info_)));
    mriManager.init();
    Info_* rows;
    Info_* row;
    u16 next;
    u16 previous;
    u16 selectedIndex;
    Info_* listEnd;
    Info_* info;
    rows = mriManager.mpInfo;
    row = &rows[mriManager.mMaxLength];
    row = &rows[row->Next];
    next = row->Next;
    previous = row->Back;
    selectedIndex = rows[next].Back;
    rows[next].Back = previous;
    rows[previous].Next = next;
    row->Back = selectedIndex;
    row->Next = selectedIndex;
    info = mriManager.mpInfo;
    listEnd = &info[info[static_cast<u16>(mriManager.mMaxLength + 1)].Back];
    if (row->Back == row->Next) {
        u16 head = listEnd->Next;
        row->Back = info[head].Back;
        row->Next = head;
        listEnd->Next = selectedIndex;
        info[head].Back = selectedIndex;
    }
    row->StrCount = 0;
    row->DispRowCount = 1;
    mpCursorLine = row;
}

tistring::Decolated* Base::getCurrentString(bool inputting) {
    if (!mbPredictOn) return mpString;
    if (meLanguage == KR) {
        if (mpManager->getToolBar()->isQwerty()) {
            if (mpManager->getPCKeyboard()->getTranslateMode() == 0) return mpString;
        } else {
            if (mpManager->getCellPhoneKeyboard()->getInputMode() != 0) return mpString;
        }
    }
    if (meLanguage == CN) {
        if (mpManager->getCandidateBox()->isInvalid() || !mpManager->getCandidateBox()->isActive()) return mpString;
    }
    switch (mePredictMode) {
    case PM_Atok:
        if (!mpUnfixString->isFix() || inputting) return mpUnfixString;
        break;
    default:
        if (!mpZiString->isFix() || inputting) return mpZiString;
        break;
    }
    return mpString;
}

bool Base::isVacancy() const {
    if (mpString->getLength() != 0 || !mpString->isKanaFix()) return false;
    if (mePredictMode == PM_Atok) {
        if (!mpUnfixString->isFix()) return false;
        if (mpString->getLength() != 0) return false;
        if (mpUnfixString->isCandidateSelected()) return false;
    } else {
        if (mePredictMode == PM_12) return true;
        if (mePredictMode != PM_Off) {
            if (mpZiString->getLength() != 0) return false;
            wchar_t input[16];
            if (mpZiString->getCurrentInput(input, 16) > 0) return false;
            if (mbCursorSelected | mbZuSelected) {
                const wchar_t* selected = mpZiString->getCurrentSelected();
                if (selected && *selected != 0xfffe) return false;
            }
        }
    }
    return true;
}

void Base::notifyChangeMode() {
    if (mePredictMode == PM_Atok) {
        if (mpManager->getToolBar()->isQwerty()) {
            if (mpManager->getPCKeyboard()->isABC()) {
                if (!mpManager->getPCKeyboard()->getTranslateMode()) goto checkInput;
            }
        }
        if (!mpManager->getToolBar()->isQwerty()) mpManager->getCellPhoneKeyboard()->getInputMode();
checkInput:
        if (mpUnfixString->getInputStringLength() == 0) updateCandidateState_();
    } else if (mePredictMode == PM_12) {
        tistring::WithZi::PredictLanguage language;
        if (mpManager->getToolBar()->isQwerty()) language = static_cast<tistring::WithZi::PredictLanguage>(10);
        else language = static_cast<tistring::WithZi::PredictLanguage>(11);
        mpZiString->setPredictLaunguage(language);
    } else if (mePredictMode == PM_11) {
        if (mbPredictOn) mpZiString->setCurrentWord(NULL);
    }
}

void Base::updateCandidateState_() {
    if (!mbPredictOn) return;
    wchar_t prediction[64];
    if (mePredictMode == PM_Atok) {
        if (mpUnfixString->hasConfirmedString()) {
            const wchar_t* confirmed = mpUnfixString->getConfirmedWCString();
            mpString->getCursorPos();
            mpString->confirm(confirmed);
            mpString->getCursorPos();
            mpUnfixString->enableConfirmedString(false);
            onSE(sound::SE_CHAR_DECIDE);
        }
        bool suppress = false;
        CommandReceiver::onCommand(static_cast<INPUT_COMMAND>(35), &suppress);
        candidatebox::CandidateBoxCaller::resetCandidate();
        if (!suppress) {
            int count = mpUnfixString->getCurrentNumPredicted();
            for (int index = 0; index < count; ++index) {
                mpUnfixString->getPredicted(index, prediction);
                candidatebox::CandidateBoxCaller::addCandidate(prediction);
            }
            candidatebox::CandidateBoxCaller::updateCandidate();
        }
    } else {
        candidatebox::CandidateBoxCaller::resetCandidate();
        int count = mpZiString->getCurrentNumPredicted();
        for (int index = 0; index < count; ++index) {
            mpZiString->getPredicted(index, prediction);
            candidatebox::CandidateBoxCaller::addCandidate(prediction);
        }
        candidatebox::CandidateBoxCaller::updateCandidate();
    }
}

void Base::moveCursorUp() {
    f32 y = mfCursorY;
    if (-(mfCursorY - mfScrollY) >= 0.0f) {
        u32 start, end;
        mpString->getCursorPos(&start, &end);
        if (start == 0 && end == 0) onSE(sound::SE_CHAR_CURSOR_FIX);
        else onSE(sound::SE_CHAR_CURSOR);
        mpString->setCursorPos(0);
    } else {
        y = mfCursorY >= 0.0f ? mfCursorY : 0.0f;
        f32 lineHeight = getLineHeight();
        f32 targetY = 1.0f + (y - lineHeight);
        u32 position = calcCursorPos(mfCursorX, targetY);
        mpString->setCursorPos(position);
        onSE(sound::SE_CHAR_CURSOR);
    }
    meScrollFlag = SF_ScrollOn;
}

void Base::moveCursorDown() {
    if (-(mfCursorY - mfScrollY) < mfMinScrollY) {
        u32 start, end;
        mpString->getCursorPos(&start, &end);
        if (start == mpString->getLength() && end == mpString->getLength()) onSE(sound::SE_CHAR_CURSOR_FIX);
        else onSE(sound::SE_CHAR_CURSOR);
        mpString->setCursorPos(mpString->getLength());
    } else {
        f32 lineHeight = getLineHeight();
        f32 y = mfCursorY + lineHeight;
        mpString->setCursorPos(calcCursorPos(mfCursorX, 1.0f + y));
        onSE(sound::SE_CHAR_CURSOR);
    }
    meScrollFlag = SF_ScrollOn;
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
                onSE(sound::SE_CHAR_DECIDE);
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
        onSE(sound::SE_CHAR_INPUT);
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
        onSE(sound::SE_CHAR_DECIDE);
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
        u32 enabled = mbPredictOn;
        if (enabled == 0) useAtok = false;
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
                    onSE(sound::SE_CHAR_CURSOR_FIX);
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
                onSE(sound::SE_CHAR_CURSOR_FIX);
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
        if (current->hasCandidate() || !current->isKanaFix()) return;
        mpManager->getHWKeyboard()->resetQuoteState();
        mpUnfixString->resetRelation();
        updateCandidateState_();
        if (mpUnfixString->getCandidate() != L' ') {
            moveCursorUp();
            onCommand(static_cast<INPUT_COMMAND>(47), NULL);
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
                onSE(sound::SE_CHAR_CURSOR_FIX);
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
        if (current->hasCandidate() || !current->isKanaFix()) return;
        mpManager->getHWKeyboard()->resetQuoteState();
        mpUnfixString->resetRelation();
        updateCandidateState_();
        if (mpUnfixString->getCandidate() != L' ') {
            moveCursorDown();
            onCommand(static_cast<INPUT_COMMAND>(47), NULL);
        }
    }
}

void Base::onPressDownHWKB() {
    s32 selected;
    tistring::Decolated* current = getCurrentString(false);
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
        if (current->hasCandidate() || !current->isKanaFix()) return;
            if (mpUnfixString->getCandidate() == L' ') return;
            moveCursorDown();
            onCommand(static_cast<INPUT_COMMAND>(47), NULL);

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
                    onSE(sound::SE_CHAR_CURSOR_FIX);
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
 else if (mpZiString == current) {
        return;
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
        if (current->hasCandidate() || !current->isKanaFix()) return;
        mpManager->getHWKeyboard()->resetQuoteState();
        mpUnfixString->resetRelation();
        updateCandidateState_();
        if (current->moveCursorLeft()) onSE(sound::SE_CHAR_CURSOR);
        else onSE(sound::SE_CHAR_CURSOR_FIX);
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
        onSE(sound::SE_CHAR_CURSOR_FIX);
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
        onSE(sound::SE_CHAR_CURSOR_FIX);
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
        if (current->hasCandidate() || !current->isKanaFix()) return;
        mpManager->getHWKeyboard()->resetQuoteState();
        mpUnfixString->resetRelation();
        updateCandidateState_();
        if (current->moveCursorRight()) onSE(sound::SE_CHAR_CURSOR_FIX);
        else onSE(sound::SE_CHAR_CURSOR);
    } else if (current == mpUnfixString) {
        if (mpManager->getCandidateBox()->isInScroll()) return;
        if (mpUnfixString->getCurrentNumPredicted() <= 0) return;
        if (mpUnfixString->isConverting()) {
            current->moveCursorRight();
            onSE(sound::SE_CHAR_CURSOR_FIX);
            updateCandidateState_();
        } else {
            s32 selected = static_cast<s16>(mpUnfixString->getSelectedCandidate() + 1);
            if (selected >= mpUnfixString->getCurrentNumPredicted()) selected = 0;
            moveCandidateToIdx(selected);
            mpManager->getCandidateBox()->getTextArea().ScrollToSelectedText();
            onSE(sound::SE_CHAR_CURSOR_FIX);
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
        onSE(sound::SE_CHAR_CURSOR_FIX);
    }
    meScrollFlag = SF_ScrollOn;
}

void Base::onPressLeft() {
    tistring::Decolated* current = getCurrentString(false);
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
        if (current->hasCandidate() || !current->isKanaFix()) return;
        resetInputRelation();
        if (mpUnfixString->getCandidate() == L' ') return;
    }
    if (current->moveCursorLeft()) onSE(sound::SE_CHAR_CURSOR);
    else onSE(sound::SE_CHAR_CURSOR_FIX);
    if (current == mpUnfixString) updateCandidateState_();
    meScrollFlag = SF_ScrollOn;
}

void Base::onPressRight() {
    tistring::Decolated* current = getCurrentString(false);
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
        if (current->hasCandidate() || !current->isKanaFix()) return;
        resetInputRelation();
        if (mpUnfixString->getCandidate() == L' ') return;
    }
    if (current->moveCursorRight() && mbRightWithSpace) {
        CharacterInput space = {L' ', 0, false, false, 0};
        onCommand(static_cast<INPUT_COMMAND>(0), &space);
        onSE(sound::SE_CHAR_CURSOR);
    }
    if (current == mpZiString || current == mpUnfixString) onSE(sound::SE_CHAR_CURSOR_FIX);
    else onSE(sound::SE_CHAR_CURSOR);
    if (current == mpUnfixString) updateCandidateState_();
    meScrollFlag = SF_ScrollOn;
}

inline f32 nextColorPhase(f32 phase) { phase += 2.0f; return phase; }
inline f32 colorSine(f32 phase) { return nw4r::math::SinFIdx(phase * 0.7111111f); }
void Base::calc() {
    if (mScrollAnm.isActive()) {
        f32 scroll = mScrollAnm.getValue();
        mfScrollY = scroll;
        mfDrawScrollY = mfScrollY;
    }
    if (!mScrollAnm.isActive()) autoScroll();
    if (!mpString->isOnSustain()) mfSustainTimer = 1.0f + mfSustainTimer;
    mScrollAnm.calc();
    f32 wave = colorSine(sfColorPhase);
    mSelectedColor.r = 2;
    mSelectedColor.g = 90;
    mSelectedColor.b = 253;
    mSelectedColor.a = static_cast<u8>(150.0f + 30.0f * wave);
    if (mpString->isOnSustain()) {
        mSelectedColor.r = 52;
        mSelectedColor.g = 140;
        mSelectedColor.b = 253;
        mSelectedColor.a = static_cast<u8>(50.0f + 10.0f * wave);
    } else if (mfSustainTimer <= 50.0f) {
        mSelectedColor.r = static_cast<u8>(util::hermiteInterporation(mfSustainTimer, 0.0f, 52.0f, 0.0f, 50.0f, 2.0f, 0.0f));
        mSelectedColor.g = static_cast<u8>(util::hermiteInterporation(mfSustainTimer, 0.0f, 140.0f, 0.0f, 50.0f, 90.0f, 0.0f));
        u8 blue = static_cast<u8>(util::hermiteInterporation(mfSustainTimer, 0.0f, 253.0f, 0.0f, 50.0f, 253.0f, 0.0f));
        f32 phase = sfColorPhase;
        f32 angle = phase * 0.7111111f;
        mSelectedColor.b = blue;
        wave = nw4r::math::SinFIdx(angle);
        f32 alpha = util::hermiteInterporation(mfSustainTimer, 0.0f, 50.0f, 0.0f, 50.0f, 150.0f, 0.0f);
        mSelectedColor.a = static_cast<u8>(alpha + 20.0f * wave);
    }
    u32 cursorTimer = muCursorTimer + 8;
    f32 phase = sfColorPhase;
    muCursorTimer = cursorTimer;
    sfColorPhase = nextColorPhase(phase);
}

Base::RowInfoManager::~RowInfoManager() {
    MEMFreeToAllocator(mpAllocator, mpInfo);
}

Base::~Base() {}

Base::Base(Manager* manager) : CommandReceiver(), textdrawer::Base(), candidatebox::CandidateBoxCaller(),
    mpString(NULL), mpUnfixString(NULL), mpZiString(NULL), meInputMode(IM_Direct), mePredictMode(PM_USEn),
    mbPredictOn(false), mbDoWordWrap(true), mbRightWithSpace(true), mfCursorX(0.0f), mfCursorY(0.0f),
    mfScrollX(0.0f), mfScrollY(0.0f), mScrollAnm(), mfSustainTimer(0.0f), meScrollFlag(SF_NoScroll),
    muWordWrapCounter(0), muLimitStringLength(1024), muLimitRowNum(9999), mfCursorTimer(0.0f), muGlobalAlpha(255),
    mCharColor(0xffffffff), mpAllocator(NULL), mpManager(manager), mDKStream(), meLanguage(USA),
    mbZuSelected(false), mbCursorSelected(false), mriManager(muLimitStringLength), mpCursorLine(NULL),
    mCursorLinePos(0), mbLineDraw(true), muSpecifyLineDrawCount(0), muCursorTimer(0) {
}













}

void Base::init() {}

namespace inputform {



















}

int textdrawer::Base::getLine() {
    return muLine + 1;
}

namespace inputform {












}

bool textinput::util::Animation::isActive() {
    return mbInAnimation;
}

namespace inputform {
}

wchar_t* tistring::Decolated::getKanaBuffer() {
    return mKanaStream.mOutput;
}

namespace inputform {





}

bool tistring::StringBase::hasCandidate() const {
    return mwcCandidate != 0;
}

namespace inputform {








void Base::create(MEMAllocator*) {}

}

void textdrawer::Base::setVIWidth(f32 width) {
    mfVIWidth = width;
}

namespace inputform {



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

void LayoutByNW4R::onSE(sound::SE seId) {
    mpEventObserver->onSE(seId);
}
}

void CommandReceiver::addSender(CommandSender* sender) {
    nw4r::ut::List_Append(&mSenderList, sender);
}

namespace inputform {
}

bool candidatebox::LayoutByNW4R::isInScroll() {
    return mTextArea.IsScrolling();
}

namespace inputform {
}

tistring::Decolated::~Decolated() {}

namespace inputform {
}

tistring::WithAtok::~WithAtok() {}

namespace inputform {
}

CommandReceiver::~CommandReceiver() {}

namespace inputform {
}

bool tistring::Decolated::isKanaFix() const {
    if (static_cast<s32>(mTranslateMode) == TM_Hangul) return true;
    return KPRLookAhead(const_cast<KPRQueue*>(&mKanaStream.mQueue), NULL, NULL) == 0;
}

namespace inputform {
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
}

void tistring::Decolated::set(const wchar_t* string) {
    StringBase::set(string);
    u32 length = getLength();
    mCursorStart = length;
    mCursorEnd = length;
}

namespace inputform {
}

void tistring::Decolated::clear() {
    StringBase::clear();
    mCursorStart = 0;
    mCursorEnd = 0;
    mbSustain = false;
    initKanaConverter();
}

namespace inputform {
inline u16 initializeRowLinks(Base::Info_* const& rows, const u16& capacity) {
    for (u16 index = 0; index < capacity; ++index) {
        Base::Info_* row = &rows[index];
        row->Back = index - 1;
        row->Next = index + 1;
        row->StrCount = 0;
        row->DispRowCount = 0;
    }
    return capacity;
}
void Base::RowInfoManager::init() {
    u16 capacity = initializeRowLinks(mpInfo, mMaxLength);
    Info_* freeHead = &mpInfo[mMaxLength];
    u16 last = capacity - 1;
    freeHead->Back = last;
    freeHead->Next = 0;
    Info_* rows = mpInfo;
    rows[last].Next = mMaxLength;
    rows[0].Back = mMaxLength;
    u16 activeIndex = mMaxLength + 1;
    Info_* activeHead = &mpInfo[activeIndex];
    activeHead->Back = activeIndex;
    activeHead->Next = mMaxLength + 1;
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

void EditBuffer::create(MEMAllocator* allocator) {
    mpAllocator = allocator;
    void* memory = MEMAllocFromAllocator(allocator, sizeof(tistring::Decolated));
    tistring::Decolated* fixed = static_cast<tistring::Decolated*>(memory);
    fixed = new (memory) tistring::Decolated(1024);
    mpString = fixed;
    fixed->create(allocator);
    memory = MEMAllocFromAllocator(allocator, sizeof(tistring::WithAtok));
    tistring::WithAtok* atok = static_cast<tistring::WithAtok*>(memory);
    atok = new (memory) tistring::WithAtok(1024);
    mpUnfixString = atok;
    atok->create(allocator);
    memory = MEMAllocFromAllocator(allocator, sizeof(tistring::WithZi));
    tistring::WithZi* zi = static_cast<tistring::WithZi*>(memory);
    zi = new (memory) tistring::WithZi(1024);
    mpZiString = zi;
    zi->create(allocator);
}
EditBuffer::~EditBuffer() {
    if (mpString) {
        static_cast<tistring::Decolated*>(mpString)->~Decolated();
        MEMFreeToAllocator(mpAllocator, mpString);
    }
    if (mpUnfixString) {
        static_cast<tistring::WithAtok*>(mpUnfixString)->~WithAtok();
        MEMFreeToAllocator(mpAllocator, mpUnfixString);
    }
    if (mpZiString) {
        static_cast<tistring::WithZi*>(mpZiString)->~WithZi();
        MEMFreeToAllocator(mpAllocator, mpZiString);
    }
    mpString = NULL;
    mpUnfixString = NULL;
    mpZiString = NULL;
}
void LayoutByNW4R::updateInputCommon(int chan, u32 trig, u32 hold, u32 release, void* data) {
    updateRepeatInput(trig, hold);
    if (mRepeatButtons & WPAD_BUTTON_MINUS) onCommand(static_cast<INPUT_COMMAND>(1), NULL);
}
void LayoutByNW4R::updateRepeatInput(u32 trig, u32 hold) {
    mRepeatButtons = trig;
    if (hold & WPAD_BUTTON_LEFT) {
        if (--mLeftRepeat == 0) {
            mRepeatButtons |= WPAD_BUTTON_LEFT;
            mLeftRepeat = 9;
        }
    } else mLeftRepeat = 30;
    if (hold & WPAD_BUTTON_RIGHT) {
        if (--mRightRepeat == 0) {
            trig = mRepeatButtons;
            mRightRepeat = 9;
            mRepeatButtons = trig | WPAD_BUTTON_RIGHT;
        }
    } else mRightRepeat = 30;
    if (hold & WPAD_BUTTON_UP) {
        if (--mUpRepeat == 0) {
            trig = mRepeatButtons;
            mUpRepeat = 9;
            mRepeatButtons = trig | WPAD_BUTTON_UP;
        }
    } else mUpRepeat = 30;
    if (hold & WPAD_BUTTON_DOWN) {
        if (--mDownRepeat == 0) {
            trig = mRepeatButtons;
            mDownRepeat = 9;
            mRepeatButtons = trig | WPAD_BUTTON_DOWN;
        }
    } else mDownRepeat = 30;
    if (hold & WPAD_BUTTON_MINUS) {
        if (--mDeleteRepeat == 0) {
            trig = mRepeatButtons;
            mDeleteRepeat = 9;
            mRepeatButtons = trig | WPAD_BUTTON_MINUS;
        }
    } else mDeleteRepeat = 30;
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
}
void gui::GUIComponent::init() {
    if (mbInitialize) return;
    for (int point = 0; point < GUI_POINTS_MAX; ++point) {
        mbPointed[point] = false;
        mDraggingPos[point].x = 0.0f;
        mDraggingPos[point].y = 0.0f;
        mDraggingPos[point].z = 0.0f;
        mbDragging[point] = false;
        mFlightDuration[point] = 0;
    }
}
namespace inputform {

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
    const wchar_t* current;
    u32 rows;
    bool kanaHandled;
    bool kana;
    const wchar_t* character;
    u32 pos;
    f32 cursorX;
    u32 cursorStart;
    u32 cursorEnd;
    current = string;
    if (!*string) return 0;
    cursorX = getScale().x;
    nw4r::math::VEC2 scale = getScale();
    pos = 0;
    rows = 0;
    muWordWrapCounter = 0;
    kanaHandled = false;
    mbHyphen = false;
    mpString->getCursorPos(&cursorStart, &cursorEnd);
    for (;;) {
        DrawInfo info;
        info.rect.left = 0.0f;
        info.rect.top = 0.0f;
        info.rect.right = 0.0f;
        info.rect.bottom = 0.0f;
        kana = false;
        if (meLanguage == KR && !kanaHandled && cursorStart == pos) {
            kanaHandled = true;
            character = mpString->getKanaBuffer();
            if (*character) kana = true;
        }
        if (!kana) {
            if (!*current) break;
            character = current;
        }
        info.character = *character;
        calcRect(info);
        f32 right = cursorX + scale.x * info.rect.GetWidth();
        if (kana) {
            if (right >= scale.x * mRect.GetWidth()) {
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
                    f32 advance;
                    f32 nextCursorX;
                    advance = scale.x * info.rect.GetWidth();
                    nextCursorX = cursorX + advance;
                    if (nextCursorX >= scale.x * mRect.GetWidth()) return pos;
                    ++current;
                    cursorX += advance;
                    info.character = *current;
                    calcRect(info);
                    ++pos;
                }
                return muWordWrapCounter - 1;
            }
            cursorX = getScale().x;
        } else if (right >= scale.x * mRect.GetWidth()) {
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
            cursorX += scale.x * info.rect.GetWidth();
        }
        ++pos;
        ++current;
    }
    return 0;
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
                f32 width = glyph.rect.GetWidth();
                f32 fieldWidth = mRect.GetWidth();
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
        f32 left = glyph.rect.left + GetCursorX();
        f32 top = glyph.rect.top + GetCursorY();
        f32 right = glyph.rect.right + GetCursorX();
        f32 cursorY = GetCursorY();
        f32 fontHeight = GetFontHeight();
        f32 bottomEdge = fontHeight + cursorY;
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
            f32 offset = ((space.rect.GetWidth() - marker.rect.GetWidth()) / 2.0f) * getScale().x;
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
            f32 left = glyph.rect.left + GetCursorX();
            f32 top = glyph.rect.top + GetCursorY();
            f32 right = glyph.rect.right + GetCursorX();
            f32 cursorY = GetCursorY();
            f32 fontHeight = GetFontHeight();
            f32 bottomEdge = fontHeight + cursorY;
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

static inline f32 scaledExtent(f32 scale, f32 start, f32 end) {
    f32 extent = end - start;
    return scale * extent;
}

static inline f32 glyphBottom(f32 origin, const Base::DrawInfo& glyph, const nw4r::math::VEC2& scale) {
    f32 extent = glyph.rect.GetHeight();
    return origin + scale.y * extent;
}

u32 Base::calcCursorPos(f32 x, f32 y) {
    f32 zero;
    f32 cursorX;
    f32 lineTop;
    f32 lineBottom;
    f32 localY = y - mfScrollY;
    const wchar_t* string = mpString->getWCString();
    if (!*string) return 0;
    cursorX = getScale().x;
    lineTop = 0.0f;
    lineBottom = lineTop;
    nw4r::math::VEC2 scale = getScale();
    u32 pos = 0;
    muWordWrapCounter = 0;
    mbHyphen = false;
    zero = 0.0f;
    while (*string) {
        DrawInfo info;
        info.rect.left = zero;
        info.rect.top = zero;
        info.rect.right = zero;
        info.rect.bottom = zero;
        info.character = *string;
        calcRect(info);
        lineBottom = glyphBottom(lineTop, info, scale);
        f32 right = cursorX + scaledExtent(scale.x, info.rect.left, info.rect.right);
        if (doWordWrap(mpString->getWCString(), pos, cursorX)) {
            if (localY >= lineTop && localY <= lineBottom) {
                if (pos != 0) return pos - 1;
                return pos;
            }
            lineTop += scale.y * getLineHeight();
            cursorX = getScale().x;
            lineBottom = glyphBottom(lineTop, info, scale);
            right = cursorX + scaledExtent(scale.x, info.rect.left, info.rect.right);
        }
        if (right >= scaledExtent(scale.x, mRect.left, mRect.right)) {
            if (localY >= lineTop && localY <= lineBottom) return pos;
            lineTop += scale.y * getLineHeight();
            cursorX = getScale().x;
            lineBottom = glyphBottom(lineTop, info, scale);
            right = cursorX + scaledExtent(scale.x, info.rect.left, info.rect.right);
        }
        if (x <= info.rect.left && localY >= lineTop && localY <= lineBottom) return pos;
        if (*string == L'\n') {
            if (localY >= lineTop && localY <= lineBottom) return pos;
            lineTop += scale.y * getLineHeight();
            cursorX = getScale().x;
            lineBottom = glyphBottom(lineTop, info, scale);
            if (!string[1] && localY >= lineTop && localY <= lineBottom) return pos + 1;
        } else {
            if (x >= cursorX && x < right && localY >= lineTop && localY < lineBottom) {
                if (cursorX + (right - cursorX) / 2.0f > x) return pos;
                return pos + 1;
            }
            cursorX += scaledExtent(scale.x, info.rect.left, info.rect.right);
        }
        ++string;
        ++pos;
        if (!*string && localY >= lineTop && localY <= lineBottom) return pos;
    }
    if (lineTop + (lineBottom - lineTop) / 2.0f <= localY) {
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

void Base::doLineFeed() {
    ++muLine;
    f32 height = getLineHeight();
    f32 cursorY = GetCursorY();
    SetCursorY(cursorY + height);
    SetCursorX(getScale().x);
}

bool Base::isOverLine(const DrawInfo& drawInfo) {
    return GetCursorX() + drawInfo.rect.GetWidth() * getScale().x >= mRect.GetWidth() * getScale().x;
}

void Base::drawFixString(u32 position) {
    CursorPos cursor;
    cursor.fCursorX = 0.0f;
    cursor.fCursorY = 0.0f;
    cursor.uCursorPos = position;
    mCharColor.a = muGlobalAlpha;
    SetTextColor(mCharColor);
    u32 length = mpString->getLength();
    textdrawer::Base::setDrawString(mpString->getWCString(), 0, length);
    textdrawer::Base::draw(&cursor);
    drawCursor(cursor.fCursorX, cursor.fCursorY);
}

void Base::draw() {
    SetCursor(getScale().x, mfScrollY);
    nw4r::math::VEC2 scale = getScale();
    nw4r::ut::Rect clip(0.0f, 0.0f, 0.0f, 0.0f);
    nw4r::math::VEC2 origin = getGlobalLeftTopPos();
    clip.left = origin.x;
    clip.bottom = origin.y;
    clip.right = origin.x + scale.x * (mRect.right - mRect.left);
    clip.top = origin.y + scale.y * (mRect.top - mRect.bottom);
    u32 position = mpString->getCursorPos();
    beginDraw(clip);
    drawFixString(position);
    endDraw();
}

void Base::drawCursor(f32 x, f32 y) {
    f32 opacity = static_cast<u32>(muGlobalAlpha) / 255.0f;
    mfCursorX = x;
    mfCursorY = y;
    GXColor color = {scInputFormColorRU8, scInputFormColorGU8, scInputFormColorBU8, scInputFormColorAU8};
    f32 pulse = nw4r::math::SinFIdx(0.7111111f * muCursorTimer);
    color.a = static_cast<s32>(opacity * (127.0f + 127.0f * pulse));
    f32 width = mfViewWidth - mfViewX;
    debug::drawLine_(mfCursorX, 2.0f + mfCursorY, mfCursorX, (mfCursorY + GetFontHeight()) - 2.0f, 0.0f, static_cast<u8>(14592.0f / width), color);
}

void Base::doScroll(Scroll* scroll) {
    if (mScrollAnm.isActive()) return;
    if (scroll->absY) {
        mfScrollX = scroll->x;
        mfScrollY = scroll->y;
        mfDrawScrollY = mfScrollY;
    } else {
        mfScrollX += scroll->x;
        mScrollAnm.startAnm(mfScrollY, mfScrollY + scroll->y, 15.0f, NULL, NULL);
    }
    onSE(sound::SE_LINE_SCROLL);
}

void Base::doBeforeDrawProcess(const wchar_t* string, u32 position, const DrawInfo& info) {
    f32 cursorX = GetCursorX();
    if (doWordWrap(string, position, cursorX)) doLineFeed();
    if (isOverLine(info)) {
        ++muLine;
        f32 height = getLineHeight();
        f32 cursorY = GetCursorY();
        SetCursorY(cursorY + height);
        SetCursorX(getScale().x);
    }
    u32 start, end;
    mpString->getSelected(start, end);
    if (position >= start && position < end) {
        f32 left = info.rect.left + GetCursorX();
        f32 top = info.rect.top + GetCursorY();
        f32 right = info.rect.right + GetCursorX();
        f32 bottom = info.rect.bottom + GetCursorY();
        debug::drawBox_(left, top, right, bottom, 0.0f, 1.0f, mSelectedColor);
    }
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
        case ANM_FadeIn:
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
        case ANM_FocusOut:
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
    if (buttons & WPAD_BUTTON_LEFT) onCommand(static_cast<INPUT_COMMAND>(8), NULL);
    if (buttons & WPAD_BUTTON_RIGHT) onCommand(static_cast<INPUT_COMMAND>(9), NULL);
    if (buttons & WPAD_BUTTON_UP) onCommand(static_cast<INPUT_COMMAND>(10), NULL);
    if (buttons & WPAD_BUTTON_DOWN) onCommand(static_cast<INPUT_COMMAND>(11), NULL);
    bool handled = nw4rmanager::Layout::updateInput(chan, x, y, trig, hold, release, data);
    if ((release & WPAD_BUTTON_A) && mpString->isOnSustain()) {
        onCommand(static_cast<INPUT_COMMAND>(13), NULL);
    }
    if (!handled && (hold & WPAD_BUTTON_A) && mpString->isOnSustain()) {
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
s32 WithAtok::getFixedPredictionNum() { return 0; }
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
