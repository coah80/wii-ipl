#define MYTIMANAGER_IMPLEMENTATION
#define MYTIMANAGER_MATCHING
#include "keyboard/MyTiManager.h"
#include "keyboard/tiLanguageIndependentData.h"
#include "keyboard/tiPredictLang.h"
#include "keyboard/tiUtil.h"

#include <new>


namespace textinput {
namespace extend {
namespace memo {

namespace {

class SignWindowBase : public keyboard::KeyboardBase {
public:
    virtual bool isLocked();
    virtual void setPage(u8);
    virtual u8 getPage();
    virtual void movePrevSignPage();
    virtual void moveNextSignPage();
    virtual void close();

private:
    u8 mLockPadding;
    bool mbLocked;
    u8 mPagePadding;
    u8 mPage;
    const u8* mpPageCount;
    void* mpSignButton;
    void* mpEventObserver;
};

class SignWindowLayout : public SignWindowBase, public nw4rmanager::Layout, public nw4rmanager::AnmObserver {
public:
    virtual ~SignWindowLayout();
    virtual void create(MEMAllocator* allocator);
    virtual void init();
    virtual void draw();
    virtual void open(keyboard::KeyboardBase*, bool);
    virtual bool isActive();
    virtual void onChangeAnmState(nw4rmanager::AnmObserver::AnmEvent, nw4rmanager::AnmPane*, nw4rmanager::Anim*);
    virtual bool updateInput(int, f32, f32, u32, u32, u32, void*);
    virtual bool updateInput(input::HKBManager&);
};

}

class DispMemoState : public State {
public:
    Manager::StateType getStateType();
    void create();
    void init();
    void calc();
    void draw();
    void memoDraw();
    bool updateInput(int, f32, f32, u32, u32, u32);
    bool updateInput(input::HKBManager&);
    void start();
    void end();
};

class AppearMemoState : public State {
public:
    AppearMemoState() : mTime(0.0f) {}
    Manager::StateType getStateType();
    void create();
    void init();
    void draw();
    void memoDraw();
    void calc();
    bool updateInput(int, f32, f32, u32, u32, u32);
    bool updateInput(input::HKBManager&);
    void start();
    void end();

protected:
    f32 mTime;
};

class EditMemoState : public State {
public:
    Manager::StateType getStateType();
    void create();
    void init();
    void calc();
    void draw();
    bool updateInput(int, f32, f32, u32, u32, u32);
    bool updateInput(input::HKBManager&);
    void start();
    void memoDraw();
    void end();
};

class DisappearMemoState : public AppearMemoState {
public:
    DisappearMemoState() {}
    Manager::StateType getStateType();
    void start();
    void calc();

};

}
}
}

#include "keyboard/MyTiBg.h"

namespace textinput {
namespace extend {
namespace memo {

DispMemoState sDispMemoState;
EditMemoState sEditMemoState;
AppearMemoState sAppearMemoState;
DisappearMemoState sDisappearMemoState;

struct MemoPosition {
    f32 x;
    f32 y;
};

MemoPosition sHiddenMemoPosition = {-200.0f, 0.0f};
MemoPosition sAppearingMemoPosition = {0.0f, 255.0f};
MemoPosition sLetterMemoPosition = {0.0f, 145.0f};

Manager::~Manager() {
    if (mpDefaultPCKeyboard != NULL) {
        static_cast<keyboard::pctype::LayoutByNW4R*>(mpDefaultPCKeyboard)->~LayoutByNW4R();
        MEMFreeToAllocator(getAllocatorForMemo(), mpDefaultPCKeyboard);
    }
    if (mpDefaultCellPhoneKeyboard != NULL) {
        static_cast<keyboard::cellphonetype::LayoutByNW4R*>(mpDefaultCellPhoneKeyboard)->~LayoutByNW4R();
        MEMFreeToAllocator(getAllocatorForMemo(), mpDefaultCellPhoneKeyboard);
    }
    if (mpDefaultInputForm != NULL) {
        mpDefaultInputForm->~InputForm();
        MEMFreeToAllocator(getAllocatorForMemo(), mpDefaultInputForm);
    }
    if (mpDefaultCandidateBox != NULL) {
        static_cast<candidatebox::LayoutByNW4R*>(mpDefaultCandidateBox)->~LayoutByNW4R();
        MEMFreeToAllocator(getAllocatorForMemo(), mpDefaultCandidateBox);
    }
    if (mpDefaultToolBar != NULL) {
        static_cast<toolbar::LayoutByNW4R*>(mpDefaultToolBar)->~LayoutByNW4R();
        MEMFreeToAllocator(getAllocatorForMemo(), mpDefaultToolBar);
    }
    if (mpDefaultPredictLanguageDialog != NULL) {
        static_cast<predictlang::LayoutByNW4R*>(mpDefaultPredictLanguageDialog)->~LayoutByNW4R();
        MEMFreeToAllocator(getAllocatorForMemo(), mpDefaultPredictLanguageDialog);
    }
    if (mpDefaultSignWindow != NULL) {
        static_cast<SignWindowLayout*>(mpDefaultSignWindow)->~SignWindowLayout();
        MEMFreeToAllocator(getAllocatorForMemo(), mpDefaultSignWindow);
    }
    if (mpMemoInputForm != NULL) {
        mpMemoInputForm->~MemoInputForm();
        MEMFreeToAllocator(getAllocatorForMemo(), mpMemoInputForm);
    }
    if (mpLetterInputForm != NULL) {
        mpLetterInputForm->~LetterInputForm();
        MEMFreeToAllocator(getAllocatorForMemo(), mpLetterInputForm);
    }
    if (mpBigTextInputForm != NULL) {
        mpBigTextInputForm->~InputForm();
        MEMFreeToAllocator(getAllocatorForMemo(), mpBigTextInputForm);
    }
    if (mpBackGround != NULL) {
        static_cast<bg::LayoutByNW4R*>(mpBackGround)->~LayoutByNW4R();
        MEMFreeToAllocator(getAllocatorForMemo(), mpBackGround);
    }

    setPCKeyboardForMemo(NULL);
    setCellPhoneKeyboardForMemo(NULL);
    setInputFormForMemo(NULL);
    setCandidateBoxForMemo(NULL);
    setToolBarForMemo(NULL);
    setPredictLanguageDialogForMemo(NULL);
    setSignWindowForMemo(NULL);
}

inline void setPaneAlpha(nw4r::lyt::Pane* pane, s32 alpha) {
    pane->SetAlpha(alpha);
}

void Manager::create(MEMAllocator*) {
    setEditBufferForMemo(createEditBuffer());
    getEditBufferForMemo()->create(getAllocatorForMemo());

    setHWKeyboardForMemo(createHWKeyboard());

    mpDefaultPCKeyboard = createPCTypeKeyboard();
    static_cast<keyboard::pctype::LayoutByNW4R*>(mpDefaultPCKeyboard)->create(getAllocatorForMemo());

    mpDefaultCellPhoneKeyboard = createCellPhoneTypeKeyboard();
    static_cast<keyboard::cellphonetype::LayoutByNW4R*>(mpDefaultCellPhoneKeyboard)->create(getAllocatorForMemo());

    mpDefaultInputForm = createInputForm();
    mpDefaultInputForm->create(getAllocatorForMemo(), getEditBufferForMemo());

    mpDefaultCandidateBox = createCandidateBox();
    static_cast<candidatebox::LayoutByNW4R*>(mpDefaultCandidateBox)->create(getAllocatorForMemo());

    mpDefaultToolBar = createToolBar();
    static_cast<toolbar::LayoutByNW4R*>(mpDefaultToolBar)->create(getAllocatorForMemo());

    mpDefaultPredictLanguageDialog = createPredictLanguageDialog();
    static_cast<predictlang::LayoutByNW4R*>(mpDefaultPredictLanguageDialog)->create(getAllocatorForMemo());

    mpDefaultSignWindow = createSignWindow();
    static_cast<SignWindowLayout*>(mpDefaultSignWindow)->create(getAllocatorForMemo());

    mpMemoInputForm = createMemoInputForm();
    mpMemoInputForm->create(getAllocatorForMemo(), getEditBufferForMemo());

    mpLetterInputForm = createLetterInputForm();
    mpLetterInputForm->create(getAllocatorForMemo(), getEditBufferForMemo());

    mpBigTextInputForm = createBigTextInputForm();
    mpBigTextInputForm->create(getAllocatorForMemo(), getEditBufferForMemo());

    mpBackGround = createBG();
    static_cast<bg::LayoutByNW4R*>(mpBackGround)->create(getAllocatorForMemo());

    configDefault();

    sDispMemoState.setManager(this);
    sEditMemoState.setManager(this);
    sAppearMemoState.setManager(this);
    sDisappearMemoState.setManager(this);
    sDisappearMemoState.create();
    textinput::Manager::initAspect();

    mMemoSetting.uRevisionAndType = 0xF0;
    mMemoSetting.uRawData.val[0] = 0;
    mMemoSetting.uRawData.val[1] = 0;
    mMemoSetting.uRawData.val[2] = 0;
    mMemoSetting.uRawData.val[3] = 0;
    mMemoSetting.uRawData.val[4] = 0;
    mMemoSetting.uRawData.val[5] = 0;
    mMemoSetting.uRawData.val[6] = 0;
    init();
}

void Manager::init() {
    mpCurrentState = &sDispMemoState;
    mpCurrentState->start();
    mpCurrentState->init();

    static_cast<keyboard::pctype::LayoutByNW4R*>(mpDefaultPCKeyboard)
        ->getLayout()->GetRootPane()->SetInfluencedAlpha(true);
    static_cast<keyboard::cellphonetype::LayoutByNW4R*>(mpDefaultCellPhoneKeyboard)
        ->getLayout()->GetRootPane()->SetInfluencedAlpha(true);
    mpDefaultInputForm->getLayout()->GetRootPane()->SetInfluencedAlpha(true);
    mpMemoInputForm->getLayout()->GetRootPane()->SetInfluencedAlpha(true);
    mpLetterInputForm->getLayout()->GetRootPane()->SetInfluencedAlpha(true);
    mpBigTextInputForm->getLayout()->GetRootPane()->SetInfluencedAlpha(true);
    static_cast<candidatebox::LayoutByNW4R*>(mpDefaultCandidateBox)
        ->getLayout()->GetRootPane()->SetInfluencedAlpha(true);
    static_cast<toolbar::LayoutByNW4R*>(mpDefaultToolBar)
        ->getLayout()->GetRootPane()->SetInfluencedAlpha(true);
    static_cast<bg::LayoutByNW4R*>(mpBackGround)
        ->getLayout()->GetRootPane()->SetInfluencedAlpha(true);
}

void Manager::calc() {
    mpCurrentState->calc();
}

void Manager::draw() {
    mpCurrentState->draw();
}

void Manager::memoDraw() {
    mpCurrentState->memoDraw();
}

bool Manager::updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release) {
    return mpCurrentState->updateInput(chan, x, y, trig, hold, release);
}

bool Manager::updateInput(input::HKBManager& hkbManager) {
    return mpCurrentState->updateInput(hkbManager);
}

void Manager::changeState(StateTimeLine stateTimeLine) {
    if (stateTimeLine == STL_Transition) {
        setState(mpCurrentState->getStateType());
    }
}

void Manager::setState(StateType stateType) {
    switch (stateType) {
    case ST_Hidden:
        getEventObserverForMemo()->onSE(static_cast<sound::SE>(27));
        mpCurrentState->end();
        mpCurrentState = &sAppearMemoState;
        mpCurrentState->start();
        break;
    case ST_Appearing:
        getEventObserverForMemo()->onSE(static_cast<sound::SE>(28));
        mpCurrentState->end();
        mpCurrentState = &sEditMemoState;
        mpCurrentState->start();
        break;
    case ST_Visible:
        mpCurrentState->end();
        mpCurrentState = &sDisappearMemoState;
        mpCurrentState->start();
        break;
    case ST_Disappearing:
        getEventObserverForMemo()->onSE(static_cast<sound::SE>(29));
        mpCurrentState->end();
        mpCurrentState = &sDispMemoState;
        mpCurrentState->start();
        break;
    }
}

textinput::MemoInputForm* Manager::createMemoInputForm() {
    void* memory = MEMAllocFromAllocator(getAllocatorForMemo(), sizeof(textinput::MemoInputForm));
    return new (memory) textinput::MemoInputForm(this, getMultiArcForMemo(), "my_Memo_a.brlyt",
                                                 getEventObserverForMemo(), "WiiBitmapFontType2.brfnt");
}

textinput::LetterInputForm* Manager::createLetterInputForm() {
    void* memory = MEMAllocFromAllocator(getAllocatorForMemo(), sizeof(textinput::LetterInputForm));
    return new (memory) textinput::LetterInputForm(this, getMultiArcForMemo(), "my_LetterL.brlyt",
                                                   getEventObserverForMemo(), "WiiBitmapFontType2.brfnt");
}

textinput::InputForm* Manager::createInputForm() {
    return new (MEMAllocFromAllocator(getAllocatorForMemo(), sizeof(textinput::InputForm)))
        textinput::InputForm(this, getMultiArcForMemo(), "fs_VK_textBox_a.brlyt",
                             getEventObserverForMemo(), "WiiBitmapFontType1.brfnt");
}

textinput::InputForm* Manager::createBigTextInputForm() {
    return new (MEMAllocFromAllocator(getAllocatorForMemo(), sizeof(textinput::InputForm)))
        textinput::InputForm(this, getMultiArcForMemo(), "fs_VK_textBox_b.brlyt",
                             getEventObserverForMemo(), "WiiBitmapFontType1.brfnt");
}

void* Manager::createBG() {
    void* memory = MEMAllocFromAllocator(getAllocatorForMemo(), sizeof(bg::LayoutByNW4R));
    EventObserver* eventObserver;
    return new (memory) bg::LayoutByNW4R((eventObserver = getEventObserverForMemo(),
                                          getMultiArcForMemo()),
                                         "fs_VK_bg_a.brlyt", eventObserver);
}

void Manager::configDefault() {
    meConfigType = CT_Default;
    setPCKeyboardForMemo(static_cast<keyboard::pctype::LayoutByNW4R*>(mpDefaultPCKeyboard));
    setCellPhoneKeyboardForMemo(static_cast<keyboard::cellphonetype::LayoutByNW4R*>(mpDefaultCellPhoneKeyboard));
    setInputFormForMemo(mpDefaultInputForm);
    setCandidateBoxForMemo(static_cast<candidatebox::LayoutByNW4R*>(mpDefaultCandidateBox));
    setToolBarForMemo(static_cast<toolbar::LayoutByNW4R*>(mpDefaultToolBar));
    setPredictLanguageDialogForMemo(mpDefaultPredictLanguageDialog);
    setSignWindowForMemo(mpDefaultSignWindow);
    textinput::Manager::init();

    getToolBarForMemo()->setQwerty(true);
    getInputFormForMemo()->enableSpaceByRight(false);
    getInputFormForMemo()->doWordWrap(true);
    if (getDestinationForMemo() != DST_US && getDestinationForMemo() != DST_EU) {
        getInputFormForMemo()->doWordWrap(false);
    }
    getInputFormForMemo()->dirtyCacheAll();
}

void Manager::configNumeric() {
    meConfigType = CT_Numeric;
    setPCKeyboardForMemo(static_cast<keyboard::pctype::LayoutByNW4R*>(mpDefaultPCKeyboard));
    setCellPhoneKeyboardForMemo(static_cast<keyboard::cellphonetype::LayoutByNW4R*>(mpDefaultCellPhoneKeyboard));
    setInputFormForMemo(mpBigTextInputForm);
    setCandidateBoxForMemo(static_cast<candidatebox::LayoutByNW4R*>(mpDefaultCandidateBox));
    setToolBarForMemo(static_cast<toolbar::LayoutByNW4R*>(mpDefaultToolBar));
    setPredictLanguageDialogForMemo(mpDefaultPredictLanguageDialog);
    setSignWindowForMemo(mpDefaultSignWindow);
    textinput::Manager::init();

    getToolBarForMemo()->setQwerty(false);
    getToolBarForMemo()->enableKeytopChange(false);
    getCellPhoneKeyboardForMemo()->doNumericMode(true);
    getCellPhoneKeyboardForMemo()->setLineFeedButton(false);
    getCandidateBoxForMemo()->setActive(false);
    getCellPhoneKeyboardForMemo()->setPredictLanguageButton(false);
    getPCKeyboardForMemo()->setPredictLanguageButton(false);
    getInputFormForMemo()->doWordWrap(false);
    getInputFormForMemo()->enableSpaceByRight(false);
    getInputFormForMemo()->dirtyCacheAll();
}

void Manager::configNumericWithSeparator() {
    configNumeric();
    meConfigType = CT_NumericWithSeparator;
    getInputFormForMemo()->visibleSeparator(true);
}

void Manager::configLetter() {
    meConfigType = CT_Letter;
    setPCKeyboardForMemo(static_cast<keyboard::pctype::LayoutByNW4R*>(mpDefaultPCKeyboard));
    setCellPhoneKeyboardForMemo(static_cast<keyboard::cellphonetype::LayoutByNW4R*>(mpDefaultCellPhoneKeyboard));
    setInputFormForMemo(mpMemoInputForm);
    setCandidateBoxForMemo(static_cast<candidatebox::LayoutByNW4R*>(mpDefaultCandidateBox));
    setToolBarForMemo(static_cast<toolbar::LayoutByNW4R*>(mpDefaultToolBar));
    setPredictLanguageDialogForMemo(mpDefaultPredictLanguageDialog);
    setSignWindowForMemo(mpDefaultSignWindow);
    textinput::Manager::init();

    Language language = getToolBarForMemo()->getLanguage();
    const wchar_t* okCaption = langindependent::cLanguageIndependentString[langindependent::LANG_STRID_OK][language];
    const wchar_t* cancelCaption = langindependent::cLanguageIndependentString[langindependent::LANG_STRID_BACK][language];
    getToolBarForMemo()->setOKButtonVisible(true);
    getToolBarForMemo()->setOKButtonCaption(okCaption);
    getToolBarForMemo()->setCancelButtonCaption(cancelCaption);

    getInputFormForMemo()->doWordWrap(true);
    getInputFormForMemo()->enableSpaceByRight(true);
    if (getDestinationForMemo() != DST_US && getDestinationForMemo() != DST_EU) {
        getInputFormForMemo()->doWordWrap(false);
    }

    reflectSaveData();
    limitStringLength(0x100);
    limitRowNum(0x10);
    sLetterMemoPosition.y = 145.0f;
    getInputFormForMemo()->dirtyCacheAll();
}

void Manager::configPhotoLetter() {
    meConfigType = CT_PhotoLetter;
    setPCKeyboardForMemo(static_cast<keyboard::pctype::LayoutByNW4R*>(mpDefaultPCKeyboard));
    setCellPhoneKeyboardForMemo(static_cast<keyboard::cellphonetype::LayoutByNW4R*>(mpDefaultCellPhoneKeyboard));
    setInputFormForMemo(mpLetterInputForm);
    setCandidateBoxForMemo(static_cast<candidatebox::LayoutByNW4R*>(mpDefaultCandidateBox));
    setToolBarForMemo(static_cast<toolbar::LayoutByNW4R*>(mpDefaultToolBar));
    setPredictLanguageDialogForMemo(mpDefaultPredictLanguageDialog);
    setSignWindowForMemo(mpDefaultSignWindow);
    textinput::Manager::init();

    getToolBarForMemo()->setOKButtonVisible(true);
    const wchar_t* okCaption = langindependent::cLanguageIndependentString[
        langindependent::LANG_STRID_OK][getToolBarForMemo()->getLanguage()];
    getToolBarForMemo()->setOKButtonCaption(okCaption);
    const wchar_t* cancelCaption = langindependent::cLanguageIndependentString[
        langindependent::LANG_STRID_BACK][getToolBarForMemo()->getLanguage()];
    getToolBarForMemo()->setCancelButtonCaption(cancelCaption);

    getInputFormForMemo()->doWordWrap(true);
    getInputFormForMemo()->enableSpaceByRight(true);
    if (getDestinationForMemo() != DST_US && getDestinationForMemo() != DST_EU) {
        getInputFormForMemo()->doWordWrap(false);
    }

    reflectSaveData();
    limitStringLength(0x100);
    limitRowNum(0x10);
    sLetterMemoPosition.y = 151.0f;
    getInputFormForMemo()->dirtyCacheAll();
}

void Manager::configNormalWithoutLineFeed() {
    configDefault();
    meConfigType = CT_NormalWithoutLineFeed;
    getCellPhoneKeyboardForMemo()->setLineFeedButton(false);
    getPCKeyboardForMemo()->setLineFeedButton(false);
    getCandidateBoxForMemo()->setActive(false);
    getCellPhoneKeyboardForMemo()->setPredictLanguageButton(false);
    getPCKeyboardForMemo()->setPredictLanguageButton(false);
    getCellPhoneKeyboardForMemo()->setSignWindowButton(false);
    getPCKeyboardForMemo()->setSignWindowButton(false);
    getInputFormForMemo()->doWordWrap(false);
    getInputFormForMemo()->enableSpaceByRight(false);
}

void Manager::configNormalBigTextWithoutLineFeed() {
    configDefault();
    setInputFormForMemo(mpBigTextInputForm);
    textinput::Manager::init();
    meConfigType = CT_NormalBigTextWithoutLineFeed;
    getCellPhoneKeyboardForMemo()->setLineFeedButton(false);
    getPCKeyboardForMemo()->setLineFeedButton(false);
    getCandidateBoxForMemo()->setActive(false);
    getCellPhoneKeyboardForMemo()->setPredictLanguageButton(false);
    getPCKeyboardForMemo()->setPredictLanguageButton(false);
    getToolBarForMemo()->enableKeytopChange(true);
    getToolBarForMemo()->setQwerty(true);
    getCellPhoneKeyboardForMemo()->setSignWindowButton(false);
    getPCKeyboardForMemo()->setSignWindowButton(false);
    getInputFormForMemo()->doWordWrap(false);
    getInputFormForMemo()->enableSpaceByRight(false);
    getInputFormForMemo()->dirtyCacheAll();
}

void Manager::configOnlyQwertyWithoutLineFeedAndSign() {
    meConfigType = CT_OnlyQwertyWithoutLineFeedAndSign;
    setPCKeyboardForMemo(static_cast<keyboard::pctype::LayoutByNW4R*>(mpDefaultPCKeyboard));
    setCellPhoneKeyboardForMemo(static_cast<keyboard::cellphonetype::LayoutByNW4R*>(mpDefaultCellPhoneKeyboard));
    setInputFormForMemo(mpDefaultInputForm);
    setCandidateBoxForMemo(static_cast<candidatebox::LayoutByNW4R*>(mpDefaultCandidateBox));
    setToolBarForMemo(static_cast<toolbar::LayoutByNW4R*>(mpDefaultToolBar));
    setPredictLanguageDialogForMemo(mpDefaultPredictLanguageDialog);
    setSignWindowForMemo(mpDefaultSignWindow);
    textinput::Manager::init();

    getToolBarForMemo()->setQwerty(true);
    getPCKeyboardForMemo()->onlyQwerty(true);
    getToolBarForMemo()->enableKeytopChange(false);
    getPCKeyboardForMemo()->setLineFeedButton(false);
    getCellPhoneKeyboardForMemo()->setLineFeedButton(false);
    getCandidateBoxForMemo()->setActive(false);
    getCellPhoneKeyboardForMemo()->setPredictLanguageButton(false);
    getPCKeyboardForMemo()->setPredictLanguageButton(false);
    getCellPhoneKeyboardForMemo()->setSignWindowButton(false);
    getPCKeyboardForMemo()->setSignWindowButton(false);
    getInputFormForMemo()->doWordWrap(false);
    getInputFormForMemo()->enableSpaceByRight(false);
    getInputFormForMemo()->dirtyCacheAll();
}

void Manager::configOnlyQwertyBigTextWithoutLineFeedAndSign() {
    meConfigType = CT_OnlyQwertyBigTextWithoutLineFeedAndSign;
    setPCKeyboardForMemo(static_cast<keyboard::pctype::LayoutByNW4R*>(mpDefaultPCKeyboard));
    setCellPhoneKeyboardForMemo(static_cast<keyboard::cellphonetype::LayoutByNW4R*>(mpDefaultCellPhoneKeyboard));
    setInputFormForMemo(mpBigTextInputForm);
    setCandidateBoxForMemo(static_cast<candidatebox::LayoutByNW4R*>(mpDefaultCandidateBox));
    setToolBarForMemo(static_cast<toolbar::LayoutByNW4R*>(mpDefaultToolBar));
    setPredictLanguageDialogForMemo(mpDefaultPredictLanguageDialog);
    setSignWindowForMemo(mpDefaultSignWindow);
    textinput::Manager::init();

    getToolBarForMemo()->setQwerty(true);
    getPCKeyboardForMemo()->onlyQwerty(true);
    getToolBarForMemo()->enableKeytopChange(false);
    getPCKeyboardForMemo()->setLineFeedButton(false);
    getCellPhoneKeyboardForMemo()->setLineFeedButton(false);
    getCandidateBoxForMemo()->setActive(false);
    getCellPhoneKeyboardForMemo()->setPredictLanguageButton(false);
    getPCKeyboardForMemo()->setPredictLanguageButton(false);
    getCellPhoneKeyboardForMemo()->setSignWindowButton(false);
    getPCKeyboardForMemo()->setSignWindowButton(false);
    getInputFormForMemo()->doWordWrap(false);
    getInputFormForMemo()->enableSpaceByRight(false);
    getInputFormForMemo()->dirtyCacheAll();
}

void Manager::configNumericWithDot() {
    configNumeric();
    meConfigType = CT_NumericWithDot;
    getCellPhoneKeyboardForMemo()->doNumericWithDotMode(true);
}

void Manager::configNumericBigTextWithDot() {
    configNumericWithDot();
    meConfigType = CT_NumericBigTextWithDot;
}

void Manager::configNormalBigTextWithoutLineFeedWithSign() {
    configDefault();
    setInputFormForMemo(mpBigTextInputForm);
    textinput::Manager::init();
    meConfigType = CT_NormalBigTextWithoutLineFeedWithSign;
    getCellPhoneKeyboardForMemo()->setLineFeedButton(false);
    getPCKeyboardForMemo()->setLineFeedButton(false);
    getCandidateBoxForMemo()->setActive(false);
    getCellPhoneKeyboardForMemo()->setPredictLanguageButton(false);
    getPCKeyboardForMemo()->setPredictLanguageButton(false);
    getToolBarForMemo()->enableKeytopChange(true);
    getToolBarForMemo()->setQwerty(true);
    getCellPhoneKeyboardForMemo()->setSignWindowButton(true);
    getPCKeyboardForMemo()->setSignWindowButton(true);
    getInputFormForMemo()->doWordWrap(false);
    getInputFormForMemo()->enableSpaceByRight(false);
    getInputFormForMemo()->dirtyCacheAll();
}

void Manager::configNormalWithoutLineFeedWithSign() {
    configDefault();
    textinput::Manager::init();
    meConfigType = static_cast<ConfigType>(10);
    getCellPhoneKeyboardForMemo()->setLineFeedButton(false);
    getPCKeyboardForMemo()->setLineFeedButton(false);
    getCandidateBoxForMemo()->setActive(false);
    getCellPhoneKeyboardForMemo()->setPredictLanguageButton(false);
    getPCKeyboardForMemo()->setPredictLanguageButton(false);
    getToolBarForMemo()->enableKeytopChange(true);
    getToolBarForMemo()->setQwerty(true);
    getCellPhoneKeyboardForMemo()->setSignWindowButton(true);
    getPCKeyboardForMemo()->setSignWindowButton(true);
    getInputFormForMemo()->doWordWrap(false);
    getInputFormForMemo()->enableSpaceByRight(false);
    getInputFormForMemo()->dirtyCacheAll();
}

void Manager::configPredictWithoutLineFeed() {
    configDefault();
    meConfigType = CT_PredictWithoutLineFeed;
    getCellPhoneKeyboardForMemo()->setLineFeedButton(false);
    getPCKeyboardForMemo()->setLineFeedButton(false);
}

void Manager::configPredictBigText() {
    configPredictWithoutLineFeed();
    meConfigType = CT_PredictBigText;
    setInputFormForMemo(mpBigTextInputForm);
    textinput::Manager::init();
}

void Manager::start() {
    if (meConfigType >= CT_Numeric) return;
    if (meConfigType < CT_Letter) return;
    static_cast<textinput::extend::memo::InputForm*>(getInputFormForMemo())->open();
}

void Manager::end() {
    if (meConfigType >= CT_Numeric) return;
    if (meConfigType < CT_Letter) return;
    static_cast<textinput::extend::memo::InputForm*>(getInputFormForMemo())->close();
}

void Manager::setSaveData() {
    mMemoSetting.uRevisionAndType = getToolBarForMemo()->isQwerty() | 0x10;
    mMemoSetting.uDictionary = getInputFormForMemo()->getPredictMode();
    mMemoSetting.uPredictOnOff = getCandidateBoxForMemo()->isOn();
    mMemoSetting.uSignPage =
        static_cast<SignWindowLayout*>(getSignWindowForMemo())->getPage();
    mMemoSetting.uRev0.uKeitaiUpperCaseJP = getCellPhoneKeyboardForMemo()->isUpperCase();
    mMemoSetting.uRev0.uKeitaiInputMode = getCellPhoneKeyboardForMemo()->getInputMode();
    mMemoSetting.uRev0.uQwertyABC = getPCKeyboardForMemo()->isABC();
    mMemoSetting.uReserve2 = 0;
    mMemoSetting.uRev0.uABCInputMode = getPCKeyboardForMemo()->getTranslateModeForMemo();
    mMemoSetting.uRev0.uAIUInputMode = getPCKeyboardForMemo()->getAIUInputModeForMemo();
    mMemoSetting.uNumLockOff = !(
        input::HKBManager::getInstance().GetModifierState() & 0x100);
    mMemoSetting.uReserve3 = 0;
    mMemoSetting.uReserve4 = 0;
}

void Manager::reflectSaveData() {
    s32 revision = (mMemoSetting.uRevisionAndType >> 4) & 0xF;
    switch (revision) {
    case 0:
        break;
    case 1:
        reflectSaveDataRev1();
        return;
    }
    reflectSaveDataDefault();
}

void Manager::reflectSaveDataRev1() {
    s32 qwertyMode = mMemoSetting.uRevisionAndType & 1;
    if (qwertyMode == 1) {
        getToolBarForMemo()->setQwerty(true);
    } else {
        getToolBarForMemo()->setQwerty(false);
    }
    static_cast<SignWindowLayout*>(getSignWindowForMemo())->setPage(mMemoSetting.uSignPage);
    if (mMemoSetting.uPredictOnOff == 0) {
        getCandidateBoxForMemo()->turnOff();
    } else {
        getCandidateBoxForMemo()->turnOn();
    }
    if (mMemoSetting.uDictionary != 0xFA) {
        getInputFormForMemo()->setPredictMode(
            static_cast<textinput::InputForm::PredictMode>(mMemoSetting.uDictionary));
    }
    Language language = getLanguageForMemo();
    if (language == JP) {
        getPCKeyboardForMemo()->setInputModeJP(
            mMemoSetting.uRev0.uQwertyABC,
            mMemoSetting.uRev0.uABCInputMode,
            mMemoSetting.uRev0.uAIUInputMode);
    } else if (static_cast<u32>(language) - CN <= KR - CN) {
        getPCKeyboardForMemo()->setInputModeCK(mMemoSetting.uRev0.uABCInputMode);
    }
    getCellPhoneKeyboardForMemo()->setUpperCaseJP(mMemoSetting.uRev0.uKeitaiUpperCaseJP);
    getCellPhoneKeyboardForMemo()->setInputMode(
        static_cast<keyboard::cellphonetype::Base::InputMode>(mMemoSetting.uRev0.uKeitaiInputMode));
    getCandidateBoxForMemo()->checkValidation();
    u32 keyboardFlags = mMemoSetting.uRawData.val[3];
    u32 numLockOff = (keyboardFlags >> 1) & 1;
    u32 zeroCount = __cntlzw(numLockOff);
    u32 numLockBit = (zeroCount >> 5) & 1;
    s32 modifierValue = -static_cast<s32>(numLockBit);
    input::HKBManager::getInstance().SetModifierState(
        modifierValue & 0x100, 0x100);
}

void Manager::reflectSaveDataDefault() {
    getToolBarForMemo()->setQwerty(true);
    static_cast<SignWindowLayout*>(getSignWindowForMemo())->setPage(0);
    if (getLanguageForMemo() == JP) {
        getCandidateBoxForMemo()->turnOn();
    } else {
        getCandidateBoxForMemo()->turnOff();
    }
    Language language = getLanguageForMemo();
    if (language == JP) {
        getPCKeyboardForMemo()->setInputModeJP(false, 1, 0);
    } else if (static_cast<u32>(language) - CN <= KR - CN) {
        getPCKeyboardForMemo()->setInputModeCK(1);
    }
    getCellPhoneKeyboardForMemo()->setUpperCaseJP(true);
    getCellPhoneKeyboardForMemo()->setInputMode(
        static_cast<keyboard::cellphonetype::Base::InputMode>(2));
    getCandidateBoxForMemo()->checkValidation();
    input::HKBManager::getInstance().SetModifierState(0x100, 0x100);
}

void Manager::SetFont(nw4r::lyt::FontRefLink* fontLink) {
    textinput::Manager::SetFont(fontLink);
    const nw4r::ut::Font* font = fontLink->GetFont();
    textinput::InputForm* bigTextInputForm = mpBigTextInputForm;
    if (bigTextInputForm != NULL) {
        static_cast<nw4r::ut::CharWriter&>(*bigTextInputForm).SetFont(*font);
    }
    textinput::MemoInputForm* memoInputForm = mpMemoInputForm;
    if (memoInputForm != NULL) {
        static_cast<nw4r::ut::CharWriter&>(*memoInputForm).SetFont(*font);
    }
    textinput::LetterInputForm* letterInputForm = mpLetterInputForm;
    if (letterInputForm != NULL) {
        static_cast<nw4r::ut::CharWriter&>(*letterInputForm).SetFont(*font);
    }
}

void DispMemoState::create() {}

void DispMemoState::init() {
    getManager()->getConfigType();
}

void DispMemoState::calc() {
    Manager::ConfigType configType = getManager()->getConfigType();
    switch (configType) {
    case Manager::CT_Letter:
    case Manager::CT_PhotoLetter:
        InputForm()->calc();
        break;
    default:
        break;
    }
}

InputForm* State::InputForm() {
    return static_cast<textinput::extend::memo::InputForm*>(getManager()->getInputForm());
}

void DispMemoState::draw() {}

void DispMemoState::memoDraw() {
    if (getManager()->getConfigType() == Manager::CT_Letter ||
        getManager()->getConfigType() == Manager::CT_PhotoLetter) {
        InputForm()->draw();
    }
}

bool DispMemoState::updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release) {
    Manager::ConfigType configType = getManager()->getConfigType();
    switch (configType) {
    case Manager::CT_Letter:
    case Manager::CT_PhotoLetter: {
        InputForm();
        struct InputParameters {
            int chan;
            f32 x;
            f32 y;
            u32 trig;
            u32 hold;
            u32 release;
        } inputParameters = {chan, x, y, trig, hold, release};
        return InputForm()->updateInput(chan, x, y, trig, hold, release, &inputParameters);
    }
    default:
        return false;
    }
}

bool DispMemoState::updateInput(input::HKBManager& hkbManager) {
    Manager::ConfigType configType = getManager()->getConfigType();
    switch (configType) {
    case Manager::CT_Letter:
    case Manager::CT_PhotoLetter:
        InputForm();
        return InputForm()->updateInput(hkbManager);
    default:
        return false;
    }
}

void DispMemoState::start() {
    Manager::ConfigType configType = getManager()->getConfigType();
    switch (configType) {
    case Manager::CT_Letter:
    case Manager::CT_PhotoLetter:
        InputForm()->setEditMode(InputForm::EM_Disp);
        InputForm()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, sLetterMemoPosition.x));
        InputForm()->getLayout()->GetRootPane()->SetAlpha(255);
        break;
    default:
        InputForm()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, sHiddenMemoPosition.x));
        setPaneAlpha(InputForm()->getLayout()->GetRootPane(), static_cast<s32>(sAppearingMemoPosition.x));
        break;
    }
    PCKeyboard()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, sHiddenMemoPosition.x));
    CellPhoneKeyboard()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, sHiddenMemoPosition.x));
    CandidateBox()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, sHiddenMemoPosition.x));
    ToolBar()->getUpArea()->SetTranslate(nw4r::math::VEC2(0.0f, sHiddenMemoPosition.x / 3.0f));
    ToolBar()->getDownArea()->SetTranslate(nw4r::math::VEC2(0.0f, -sHiddenMemoPosition.x / 3.0f));
    static_cast<bg::LayoutByNW4R*>(BG())->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, 0.0f));
    setPaneAlpha(PCKeyboard()->getLayout()->GetRootPane(), static_cast<s32>(sAppearingMemoPosition.x));
    setPaneAlpha(CellPhoneKeyboard()->getLayout()->GetRootPane(), static_cast<s32>(sAppearingMemoPosition.x));
    setPaneAlpha(CandidateBox()->getLayout()->GetRootPane(), static_cast<s32>(sAppearingMemoPosition.x));
    setPaneAlpha(ToolBar()->getUpArea(), static_cast<s32>(sAppearingMemoPosition.x));
    setPaneAlpha(ToolBar()->getDownArea(), static_cast<s32>(sAppearingMemoPosition.x));
    setPaneAlpha(static_cast<bg::LayoutByNW4R*>(BG())->getLayout()->GetRootPane(), static_cast<s32>(sAppearingMemoPosition.x));
}

keyboard::pctype::LayoutByNW4R* State::PCKeyboard() {
    return getManager()->getPCKeyboard();
}

keyboard::cellphonetype::LayoutByNW4R* State::CellPhoneKeyboard() {
    return getManager()->getCellPhoneKeyboard();
}

candidatebox::LayoutByNW4R* State::CandidateBox() {
    return getManager()->getCandidateBox();
}

toolbar::LayoutByNW4R* State::ToolBar() {
    return getManager()->getToolBar();
}

void* State::BG() {
    return getManager()->getBackGround();
}

void AppearMemoState::create() {}

void AppearMemoState::init() {}

void AppearMemoState::calc() {
    InputForm()->calc();
    if (ToolBar()->isQwerty()) {
        PCKeyboard()->calc();
    } else {
        static_cast<keyboard::cellphonetype::Base*>(CellPhoneKeyboard())->calc();
    }
    if (CandidateBox()->isActive()) {
        CandidateBox()->calc();
    }
    ToolBar()->calc();
    static_cast<bg::LayoutByNW4R*>(BG())->calc();
    if (30.0f <= mTime) {
        getManager()->changeState(Manager::STL_Transition);
    }

    f32 offset = textinput::util::hermiteInterporation(
        mTime, 0.0f, sHiddenMemoPosition.x, 0.0f,
        30.0f, sHiddenMemoPosition.y, 0.0f);
    PCKeyboard()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, offset));
    CellPhoneKeyboard()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, offset));
    CandidateBox()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, offset));
    ToolBar()->getUpArea()->SetTranslate(
        nw4r::math::VEC2(0.0f, offset / 3.0f));
    ToolBar()->getDownArea()->SetTranslate(
        nw4r::math::VEC2(0.0f, -offset / 3.0f));
    static_cast<bg::LayoutByNW4R*>(BG())->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, 0.0f));

    f32 alpha = textinput::util::hermiteInterporation(
        mTime, 0.0f, sAppearingMemoPosition.x, 0.0f,
        30.0f, sAppearingMemoPosition.y, 0.0f);
    s32 alphaByte = static_cast<s32>(alpha);
    setPaneAlpha(PCKeyboard()->getLayout()->GetRootPane(), alphaByte);
    setPaneAlpha(CellPhoneKeyboard()->getLayout()->GetRootPane(), alphaByte);
    setPaneAlpha(CandidateBox()->getLayout()->GetRootPane(), alphaByte);
    setPaneAlpha(ToolBar()->getUpArea(), alphaByte);
    setPaneAlpha(static_cast<bg::LayoutByNW4R*>(BG())->getLayout()->GetRootPane(), alphaByte);

    Manager::ConfigType configType = getManager()->getConfigType();
    switch (configType) {
    case Manager::CT_Letter:
    case Manager::CT_PhotoLetter: {
        f32 letterOffset = textinput::util::hermiteInterporation(
            mTime, 0.0f, sLetterMemoPosition.x, 0.0f,
            30.0f, sLetterMemoPosition.y, 0.0f);
        InputForm()->getLayout()->GetRootPane()->SetTranslate(
            nw4r::math::VEC2(0.0f, letterOffset));
        setPaneAlpha(InputForm()->getLayout()->GetRootPane(), 0xff);
        MemoInputForm* inputForm = InputForm();
        inputForm->setScroll(textinput::util::hermiteInterporation(
            mTime, 0.0f, inputForm->getScrollFrom(), 0.0f,
            30.0f, inputForm->getScrollTo(), 0.0f));
        break;
    }
    default: {
        InputForm()->getLayout()->GetRootPane()->SetTranslate(
            nw4r::math::VEC2(0.0f, offset));
        setPaneAlpha(InputForm()->getLayout()->GetRootPane(), alphaByte);
    }
    }
    mTime += 1.0f;
}

f32 InputForm::getScrollFrom() {
    return mfScrollFrom;
}

f32 InputForm::getScrollTo() {
    return mfScrollTo;
}

void AppearMemoState::draw() {
    if (getManager()->getConfigType() != Manager::CT_Letter &&
        getManager()->getConfigType() != Manager::CT_PhotoLetter) {
        static_cast<bg::LayoutByNW4R*>(BG())->draw();
    }
    ToolBar()->draw();
    if (getManager()->getConfigType() != Manager::CT_Letter &&
        getManager()->getConfigType() != Manager::CT_PhotoLetter) {
        InputForm()->draw();
    }
    if (CandidateBox()->isActive()) {
        CandidateBox()->draw();
    }
    if (ToolBar()->isQwerty()) {
        PCKeyboard()->draw();
    } else {
        static_cast<keyboard::cellphonetype::Base*>(CellPhoneKeyboard())->draw();
    }
}

void bg::LayoutByNW4R::draw() {
    nw4rmanager::Layout::draw();
}

void AppearMemoState::memoDraw() {
    if (getManager()->getConfigType() == Manager::CT_Letter ||
        getManager()->getConfigType() == Manager::CT_PhotoLetter) {
        InputForm()->draw();
    }
}

bool AppearMemoState::updateInput(int, f32, f32, u32, u32, u32) {
    return false;
}

bool AppearMemoState::updateInput(input::HKBManager&) {
    return false;
}

void AppearMemoState::start() {
    mTime = 0.0f;
    Manager::ConfigType configType = getManager()->getConfigType();
    switch (configType) {
    case Manager::CT_Letter:
    case Manager::CT_PhotoLetter:
        InputForm()->setEditMode(InputForm::EM_Appear);
        break;
    default:
        break;
    }
}

void EditMemoState::create() {}

void EditMemoState::init() {}

void EditMemoState::calc() {
    if (ToolBar()->isQwerty()) {
        PCKeyboard()->calc();
    } else {
        static_cast<keyboard::cellphonetype::Base*>(CellPhoneKeyboard())->calc();
    }
    ToolBar()->calc();
    if (CandidateBox()->isActive()) {
        CandidateBox()->calc();
    }
    InputForm()->calc();
    if (static_cast<predictlang::LayoutByNW4R*>(PredictLanguageSelectDialog())->isActive()) {
        static_cast<predictlang::LayoutByNW4R*>(PredictLanguageSelectDialog())->calc();
    }
    if (static_cast<SignWindowLayout*>(SignKeyboard())->isActive()) {
        SignWindowLayout& signWindow = *static_cast<SignWindowLayout*>(SignKeyboard());
        static_cast<nw4rmanager::Layout&>(signWindow).calc();
    }
    if (getManager()->getConfigType() != Manager::CT_Letter &&
        getManager()->getConfigType() != Manager::CT_PhotoLetter) {
        static_cast<bg::LayoutByNW4R*>(BG())->calc();
    }
}

void* State::PredictLanguageSelectDialog() {
    return getManager()->getPredictLanguageSelectDialog();
}

void* State::SignKeyboard() {
    return getManager()->getSignKeyboard();
}

void EditMemoState::draw() {
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    if (getManager()->getConfigType() != Manager::CT_Letter &&
        getManager()->getConfigType() != Manager::CT_PhotoLetter) {
        static_cast<bg::LayoutByNW4R*>(BG())->draw();
    }
    ToolBar()->draw();
    if (getManager()->getConfigType() != Manager::CT_Letter &&
        getManager()->getConfigType() != Manager::CT_PhotoLetter) {
        InputForm()->draw();
    }
    if (CandidateBox()->isActive()) {
        CandidateBox()->draw();
    }
    if (ToolBar()->isQwerty()) {
        PCKeyboard()->draw();
    } else {
        static_cast<keyboard::cellphonetype::Base*>(CellPhoneKeyboard())->draw();
    }
    if (static_cast<predictlang::LayoutByNW4R*>(PredictLanguageSelectDialog())->isActive()) {
        static_cast<predictlang::LayoutByNW4R*>(PredictLanguageSelectDialog())->draw();
    }
    if (static_cast<SignWindowLayout*>(SignKeyboard())->isActive()) {
        static_cast<SignWindowLayout*>(SignKeyboard())->draw();
    }
}

void EditMemoState::memoDraw() {
    if (getManager()->getConfigType() == Manager::CT_Letter ||
        getManager()->getConfigType() == Manager::CT_PhotoLetter) {
        InputForm()->draw();
    }
}

bool EditMemoState::updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release) {
    bool wasQwerty = ToolBar()->isQwerty();
    struct InputParameters {
        int chan;
        f32 x;
        f32 y;
        u32 trig;
        u32 hold;
        u32 release;
    } inputParameters = {chan, x, y, trig, hold, release};
    HWKeyboard()->updateInput(chan, x, y, trig, hold, release, &inputParameters);
    if (static_cast<predictlang::LayoutByNW4R*>(PredictLanguageSelectDialog())->isActive()) {
        return static_cast<predictlang::LayoutByNW4R*>(PredictLanguageSelectDialog())->updateInput(chan, x, y, trig, hold, release, &inputParameters);
    }
    InputForm()->updateInputCommon(chan, trig, hold, release, &inputParameters);
    if (static_cast<SignWindowLayout*>(SignKeyboard())->isActive()) {
        return static_cast<SignWindowLayout*>(SignKeyboard())->updateInput(
            chan, x, y, trig, hold, release, &inputParameters);
    }
    bool handled;
    if (wasQwerty) {
        handled = PCKeyboard()->updateInput(chan, x, y, trig, hold, release, &inputParameters);
    } else {
        handled = CellPhoneKeyboard()->updateInput(chan, x, y, trig, hold, release, &inputParameters);
    }
    bool toolbarHandled = ToolBar()->updateInput(chan, x, y, trig, hold, release, &inputParameters);
    bool candidateHandled = false;
    if (CandidateBox()->isActive()) {
        candidateHandled = CandidateBox()->updateInput(chan, x, y, trig, hold, release, &inputParameters);
    }
    u32 inputHandled = 0;
    if (!candidateHandled) {
        inputHandled = InputForm()->updateInput(chan, x, y, trig, hold, release, &inputParameters);
    } else {
        InputForm()->updateInput(chan, (1.0f / 0.0f), (1.0f / 0.0f), trig, hold, release, &inputParameters);
    }
    handled = (handled | candidateHandled) | (inputHandled | toolbarHandled);
    if (wasQwerty != ToolBar()->isQwerty()) {
        InputForm()->onCommand(static_cast<CommandReceiver::INPUT_COMMAND>(6), NULL);
        CandidateBox()->checkValidation();
        if (ToolBar()->isQwerty()) {
            PCKeyboard()->onActive();
        } else {
            CellPhoneKeyboard()->onActive();
        }
    }
    return handled;
}

keyboard::hwkey::HWKeyboard* State::HWKeyboard() {
    return getManager()->getHWKeyboard();
}

bool EditMemoState::updateInput(input::HKBManager& hkbManager) {
    bool wasQwerty = ToolBar()->isQwerty();
    if (static_cast<predictlang::LayoutByNW4R*>(PredictLanguageSelectDialog())->isActive()) {
        return false;
    }
    HWKeyboard()->updateInput(hkbManager);
    if (static_cast<SignWindowLayout*>(SignKeyboard())->isActive()) {
        return static_cast<SignWindowLayout*>(SignKeyboard())->updateInput(hkbManager);
    }
    bool handled;
    if (wasQwerty) {
        handled = PCKeyboard()->updateInput(hkbManager);
    } else {
        handled = CellPhoneKeyboard()->updateInput(hkbManager);
    }
    if (wasQwerty != ToolBar()->isQwerty()) {
        InputForm()->onCommand(static_cast<CommandReceiver::INPUT_COMMAND>(6), NULL);
        CandidateBox()->checkValidation();
        if (ToolBar()->isQwerty()) {
            PCKeyboard()->onActive();
        } else {
            CellPhoneKeyboard()->onActive();
        }
    }
    return handled;
}

void EditMemoState::start() {
    if (getManager()->getConfigType() == Manager::CT_Letter ||
        getManager()->getConfigType() == Manager::CT_PhotoLetter) {
        InputForm()->setEditMode(InputForm::EM_Edit);
        InputForm()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, sLetterMemoPosition.y));
        InputForm()->getLayout()->GetRootPane()->SetAlpha(255);
    } else {
        InputForm()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, sHiddenMemoPosition.y));
        setPaneAlpha(InputForm()->getLayout()->GetRootPane(), static_cast<s32>(sAppearingMemoPosition.y));
    }
    PCKeyboard()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, sHiddenMemoPosition.y));
    CellPhoneKeyboard()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, sHiddenMemoPosition.y));
    CandidateBox()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, sHiddenMemoPosition.y));
    ToolBar()->getUpArea()->SetTranslate(nw4r::math::VEC2(0.0f, sHiddenMemoPosition.y / 3.0f));
    ToolBar()->getDownArea()->SetTranslate(nw4r::math::VEC2(0.0f, -sHiddenMemoPosition.y / 3.0f));
    static_cast<bg::LayoutByNW4R*>(BG())->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, 0.0f));
    setPaneAlpha(PCKeyboard()->getLayout()->GetRootPane(), static_cast<s32>(sAppearingMemoPosition.y));
    setPaneAlpha(CellPhoneKeyboard()->getLayout()->GetRootPane(), static_cast<s32>(sAppearingMemoPosition.y));
    setPaneAlpha(CandidateBox()->getLayout()->GetRootPane(), static_cast<s32>(sAppearingMemoPosition.y));
    setPaneAlpha(ToolBar()->getUpArea(), static_cast<s32>(sAppearingMemoPosition.y));
    setPaneAlpha(ToolBar()->getDownArea(), static_cast<s32>(sAppearingMemoPosition.y));
    setPaneAlpha(static_cast<bg::LayoutByNW4R*>(BG())->getLayout()->GetRootPane(), static_cast<s32>(sAppearingMemoPosition.y));
    PCKeyboard()->onActive();
    CellPhoneKeyboard()->onActive();
    if (ToolBar()->isQwerty()) PCKeyboard()->onActive();
    else CellPhoneKeyboard()->onActive();
}

void DisappearMemoState::calc() {
    if (30.0f <= mTime) {
        getManager()->changeState(Manager::STL_Transition);
    }
    InputForm()->calc();

    f32 offset = textinput::util::hermiteInterporation(
        mTime, 0.0f, sHiddenMemoPosition.y, 0.0f,
        30.0f, sHiddenMemoPosition.x, 0.0f);
    PCKeyboard()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, offset));
    CellPhoneKeyboard()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, offset));
    CandidateBox()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, offset));
    ToolBar()->getUpArea()->SetTranslate(
        nw4r::math::VEC2(0.0f, offset / 3.0f));
    ToolBar()->getDownArea()->SetTranslate(
        nw4r::math::VEC2(0.0f, -offset / 3.0f));
    static_cast<bg::LayoutByNW4R*>(BG())->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, 0.0f));

    f32 alpha = textinput::util::hermiteInterporation(
        mTime, 0.0f, sAppearingMemoPosition.y, 0.0f,
        30.0f, sAppearingMemoPosition.x, 0.0f);
    s32 alphaByte = static_cast<s32>(alpha);
    setPaneAlpha(PCKeyboard()->getLayout()->GetRootPane(), alphaByte);
    setPaneAlpha(CellPhoneKeyboard()->getLayout()->GetRootPane(), alphaByte);
    setPaneAlpha(CandidateBox()->getLayout()->GetRootPane(), alphaByte);
    setPaneAlpha(ToolBar()->getUpArea(), alphaByte);
    setPaneAlpha(ToolBar()->getDownArea(), alphaByte);
    setPaneAlpha(static_cast<bg::LayoutByNW4R*>(BG())->getLayout()->GetRootPane(), alphaByte);

    Manager::ConfigType configType = getManager()->getConfigType();
    switch (configType) {
    case Manager::CT_Letter:
    case Manager::CT_PhotoLetter: {
        f32 letterOffset = textinput::util::hermiteInterporation(
            mTime, 0.0f, sLetterMemoPosition.y, 0.0f,
            30.0f, sLetterMemoPosition.x, 0.0f);
        InputForm()->getLayout()->GetRootPane()->SetTranslate(
            nw4r::math::VEC2(0.0f, letterOffset));
        setPaneAlpha(InputForm()->getLayout()->GetRootPane(), 0xff);
        break;
    }
    default: {
        InputForm()->getLayout()->GetRootPane()->SetTranslate(
            nw4r::math::VEC2(0.0f, offset));
        setPaneAlpha(InputForm()->getLayout()->GetRootPane(), alphaByte);
    }
    }
    mTime += 1.0f;
}

void DisappearMemoState::start() {
    mTime = 0.0f;
    Manager::ConfigType configType = getManager()->getConfigType();
    switch (configType) {
    case Manager::CT_Letter:
    case Manager::CT_PhotoLetter:
        InputForm()->setEditMode(InputForm::EM_Disappear);
        getManager()->setSaveData();
        break;
    default:
        InputForm()->onClose();
        break;
    }
}

void bg::Base::init() {}

void bg::Base::create(MEMAllocator*) {}

void AppearMemoState::end() {}

Manager::StateType DisappearMemoState::getStateType() {
    return Manager::ST_Disappearing;
}

void EditMemoState::end() {}

Manager::StateType EditMemoState::getStateType() {
    return Manager::ST_Visible;
}

State::~State() {}

Manager::StateType AppearMemoState::getStateType() {
    return Manager::ST_Appearing;
}

void DispMemoState::end() {}

Manager::StateType DispMemoState::getStateType() {
    return Manager::ST_Hidden;
}

extern const f32 sZeroScale;
const f32 sZeroScale = 0.0f;

}
}
}
