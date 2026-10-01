#define TIMANAGER_IMPLEMENTATION
#include "keyboard/tiPcKeyboard.h"
#include "keyboard/tiCellPhone.h"
#include "keyboard/tiInputForm.h"
#include <revolution/sc.h>
#include <new>

namespace textinput {
namespace keyboard {
namespace pctype {
class Sample : public LayoutByNW4R {
public:
    Sample(Manager* manager, nw4r::lyt::MultiArcResourceAccessor* accessor, EventObserver* observer, const char* layoutName)
        : LayoutByNW4R(manager, accessor, observer, layoutName) {}
    virtual ~Sample();
};
}
}
}
namespace textinput {
namespace keyboard {
namespace cellphonetype {
class Sample : public LayoutByNW4R {
public:
    Sample(Manager* manager, nw4r::lyt::MultiArcResourceAccessor* accessor, EventObserver* observer, const char* layoutName)
        : LayoutByNW4R(manager, accessor, observer, layoutName) {}
    virtual ~Sample();
};
}
}
}
namespace textinput {
namespace candidatebox {
class Sample : public LayoutByNW4R {
public:
    Sample(Manager* manager, nw4r::lyt::MultiArcResourceAccessor* accessor, EventObserver* observer, const char* layoutName)
        : LayoutByNW4R(manager, accessor, observer, layoutName) {}
    virtual ~Sample();
};
}
}
namespace textinput {
namespace inputform {
class Sample : public LayoutByNW4R {
public:
    Sample(Manager* manager, nw4r::lyt::MultiArcResourceAccessor* accessor, EventObserver* observer, const char* layoutName)
        : LayoutByNW4R(manager, accessor, layoutName, observer, NULL) {}
    virtual ~Sample();
};
}
}
#include "keyboard/tiToolBar.h"
#include "keyboard/tiPredictLang.h"
namespace textinput { namespace keyboard {
namespace signwindow {
class Sample : public LayoutByNW4R {
public:
    Sample(Manager* manager, nw4r::lyt::MultiArcResourceAccessor* accessor, EventObserver* observer, const char* layoutName)
        : LayoutByNW4R(manager, accessor, observer, layoutName) {}
    virtual ~Sample();
};
}
}}
#include "keyboard/tiManager.h"
namespace textinput {
static EventObserver defaultEventObserver;

Manager::Manager(MEMAllocator* allocator, nw4r::lyt::MultiArcResourceAccessor* accessor, EventObserver* observer)
    : mpAllocator(allocator), mpMultiArcResourceAccessor(accessor), mpEditBuffer(NULL), mpHWKeyboard(NULL), mpPCKeyboard(NULL),
      mpCellPhoneKeyboard(NULL), mpInputForm(NULL), mpCandidateBox(NULL), mpToolBar(NULL), mpPredictLanguageDialog(NULL),
      mpSignWindow(NULL), mpEventObserver(observer), meDestination(DST_JP), meLanguage(JP), mbAspectRatio4x3(true) {
    if (observer == NULL) mpEventObserver = &defaultEventObserver;
}

Manager::~Manager() {
    if (mpPCKeyboard) { mpPCKeyboard->~LayoutByNW4R(); MEMFreeToAllocator(mpAllocator, mpPCKeyboard); }
    if (mpCellPhoneKeyboard) { mpCellPhoneKeyboard->~LayoutByNW4R(); MEMFreeToAllocator(mpAllocator, mpCellPhoneKeyboard); }
    if (mpInputForm) { mpInputForm->~LayoutByNW4R(); MEMFreeToAllocator(mpAllocator, mpInputForm); }
    if (mpCandidateBox) { mpCandidateBox->~LayoutByNW4R(); MEMFreeToAllocator(mpAllocator, mpCandidateBox); }
    if (mpToolBar) { mpToolBar->~LayoutByNW4R(); MEMFreeToAllocator(mpAllocator, mpToolBar); }
    if (mpPredictLanguageDialog) { mpPredictLanguageDialog->~LayoutByNW4R(); MEMFreeToAllocator(mpAllocator, mpPredictLanguageDialog); }
    if (mpSignWindow) { mpSignWindow->~LayoutByNW4R(); MEMFreeToAllocator(mpAllocator, mpSignWindow); }
    if (mpHWKeyboard) { mpHWKeyboard->~HWKeyboard(); MEMFreeToAllocator(mpAllocator, mpHWKeyboard); }
    if (mpEditBuffer) { mpEditBuffer->~EditBuffer(); MEMFreeToAllocator(mpAllocator, mpEditBuffer); }

}

keyboard::hwkey::HWKeyboard::~HWKeyboard() {}

void Manager::create(MEMAllocator*) {
    mpEditBuffer = createEditBuffer();
    mpEditBuffer->create(mpAllocator);
    mpHWKeyboard = createHWKeyboard();
    mpPCKeyboard = static_cast<keyboard::pctype::LayoutByNW4R*>(createPCTypeKeyboard());
    mpPCKeyboard->create(mpAllocator);
    mpCellPhoneKeyboard = static_cast<keyboard::cellphonetype::LayoutByNW4R*>(createCellPhoneTypeKeyboard());
    mpCellPhoneKeyboard->create(mpAllocator);
    mpInputForm = createInputForm();
    mpInputForm->create(mpAllocator, mpEditBuffer);
    mpCandidateBox = static_cast<candidatebox::LayoutByNW4R*>(createCandidateBox());
    mpCandidateBox->create(mpAllocator);
    mpToolBar = static_cast<toolbar::LayoutByNW4R*>(createToolBar());
    mpToolBar->create(mpAllocator);
    mpPredictLanguageDialog = static_cast<predictlang::LayoutByNW4R*>(createPredictLanguageDialog());
    mpPredictLanguageDialog->create(mpAllocator);
    mpSignWindow = static_cast<keyboard::signwindow::LayoutByNW4R*>(createSignWindow());
    mpSignWindow->create(mpAllocator);
    if (SCGetAspectRatio() == 1) { setLayoutScaleFor16x9(); mbAspectRatio4x3 = false; }
    else { setLayoutScaleFor4x3(); mbAspectRatio4x3 = true; }
    init();
}

void Manager::initAspect() {
    if (SCGetAspectRatio() == 1) { setLayoutScaleFor16x9(); mbAspectRatio4x3 = false; }
    else { setLayoutScaleFor4x3(); mbAspectRatio4x3 = true; }
}

void Manager::init() {
    input::HKBManager::getInstance().ClearState();
    mpInputForm->clearSender();
    mpHWKeyboard->setCommandReceiver(mpInputForm);
    mpPCKeyboard->setCommandReceiver(mpInputForm);
    mpCellPhoneKeyboard->setCommandReceiver(mpInputForm);
    mpCandidateBox->setCommandReceiver(mpInputForm);
    mpPredictLanguageDialog->setCommandReceiver(mpInputForm);
    mpSignWindow->setCommandReceiver(mpInputForm);
    mpInputForm->setCandidateBox(mpCandidateBox);
    mpPCKeyboard->setPredictLanguageDialog(mpPredictLanguageDialog);
    mpPCKeyboard->setSignWindow(mpSignWindow);
    mpCellPhoneKeyboard->setPredictLanguageDialog(mpPredictLanguageDialog);
    mpCellPhoneKeyboard->setSignWindow(mpSignWindow);
    if (mbAspectRatio4x3 == true) setLayoutScaleFor4x3();
    else setLayoutScaleFor16x9();
    mpPredictLanguageDialog->setDestination(meDestination);
    mpInputForm->setDestination(meDestination);
    mpInputForm->setLanguage(meLanguage);
    mpPCKeyboard->setLanguage(meLanguage);
    mpCellPhoneKeyboard->setLanguage(meLanguage);
    mpSignWindow->setLanguage(meLanguage);
    mpCandidateBox->setLanguage(meLanguage);
    mpToolBar->setLanguage(meLanguage);
    mpPredictLanguageDialog->setLanguage(meLanguage);
    mpHWKeyboard->setLanguage(meDestination, meLanguage);
    mpHWKeyboard->init();
    mpPCKeyboard->init();
    mpCellPhoneKeyboard->init();
    mpInputForm->init();
    mpCandidateBox->init();
    mpToolBar->init();
    mpPredictLanguageDialog->init();
    mpSignWindow->init();
    setFixedPredictionJP(0, NULL);
    setSecretInputMode(false);
}

void Manager::setFixedPredictionJP(int count, const char** predictions) {
    static_cast<tistring::WithAtok*>(getInputForm()->getAtokString())->setFixPrediction(count, predictions);
}

void Manager::calc() {
    if (mpToolBar->isQwerty()) mpPCKeyboard->calc();
    else mpCellPhoneKeyboard->calc();
    static_cast<nw4rmanager::Layout&>(*mpToolBar).calc();
    mpCandidateBox->calc();
    mpInputForm->calc();
    if (mpPredictLanguageDialog->isActive()) static_cast<nw4rmanager::Layout&>(*mpPredictLanguageDialog).calc();
    if (mpSignWindow->isActive()) static_cast<nw4rmanager::Layout&>(*mpSignWindow).calc();
}

void Manager::draw() {
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    mpToolBar->draw();
    mpInputForm->draw();
    if (mpToolBar->isQwerty()) mpPCKeyboard->draw();
    else mpCellPhoneKeyboard->draw();
    mpCandidateBox->draw();
    if (mpPredictLanguageDialog->isActive()) mpPredictLanguageDialog->draw();
    if (mpSignWindow->isActive()) mpSignWindow->draw();
}

bool Manager::updateInput(int channel, f32 x, f32 y, u32 trigger, u32 hold, u32 release) {
    bool wasQwerty = mpToolBar->isQwerty();
    nw4rmanager::TiEventHandler::Input input;
    input.controller = channel;
    input.x = x;
    input.y = y;
    input.trigger = trigger;
    input.hold = hold;
    input.release = release;
    mpHWKeyboard->updateInput(channel, x, y, trigger, hold, release, &input);
    bool handled;
    if (mpPredictLanguageDialog->isActive()) {
        return static_cast<nw4rmanager::Layout&>(*mpPredictLanguageDialog).updateInput(channel, x, y, trigger, hold, release, &input);
    }
    mpInputForm->updateInputCommon(channel, trigger, hold, release, &input);
    if (mpSignWindow->isActive()) {
        return mpSignWindow->updateInput(channel, x, y, trigger, hold, release, &input);
    } else {
        bool keyboardHandled;
        if (wasQwerty) keyboardHandled = mpPCKeyboard->updateInput(channel, x, y, trigger, hold, release, &input);
        else keyboardHandled = mpCellPhoneKeyboard->updateInput(channel, x, y, trigger, hold, release, &input);
        bool toolbarHandled = static_cast<nw4rmanager::Layout&>(*mpToolBar).updateInput(channel, x, y, trigger, hold, release, &input);
        bool candidateHandled = static_cast<nw4rmanager::Layout&>(*mpCandidateBox).updateInput(channel, x, y, trigger, hold, release, &input);
        bool formHandled = mpInputForm->updateInput(channel, x, y, trigger, hold, release, &input);
        handled = (keyboardHandled | candidateHandled) | (formHandled | toolbarHandled);
    }
    if (wasQwerty != mpToolBar->isQwerty()) {
        getInputForm()->onCommand(static_cast<CommandReceiver::INPUT_COMMAND>(6), NULL);
        mpCandidateBox->checkValidation();
        if (mpToolBar->isQwerty()) mpPCKeyboard->onActive();
        else mpCellPhoneKeyboard->onActive();
    }
    return handled;
}

bool Manager::updateInput(input::HKBManager& keyboard) {
    bool wasQwerty = mpToolBar->isQwerty();
    bool handled;
    if (mpPredictLanguageDialog->isActive()) return static_cast<nw4rmanager::Layout&>(*mpPredictLanguageDialog).updateInput(keyboard);
    else if (mpSignWindow->isActive()) return mpSignWindow->updateInput(keyboard);
    else {
        bool keyboardHandled;
        if (wasQwerty) keyboardHandled = mpPCKeyboard->updateInput(keyboard);
        else keyboardHandled = mpCellPhoneKeyboard->updateInput(keyboard);
        bool toolbarHandled = static_cast<nw4rmanager::Layout&>(*mpToolBar).updateInput(keyboard);
        bool candidateHandled = static_cast<nw4rmanager::Layout&>(*mpCandidateBox).updateInput(keyboard);
        bool formHandled = mpInputForm->updateInput(keyboard);
        handled = (keyboardHandled | candidateHandled) | (formHandled | toolbarHandled);
    }
    if (wasQwerty != mpToolBar->isQwerty()) {
        getInputForm()->onCommand(static_cast<CommandReceiver::INPUT_COMMAND>(6), NULL);
        mpCandidateBox->checkValidation();
        if (mpToolBar->isQwerty()) mpPCKeyboard->onActive();
        else mpCellPhoneKeyboard->onActive();
    }
    return handled;
}

wchar_t* Manager::getWCString() const { return mpInputForm->getWCString(); }
void Manager::setWCString(const wchar_t* string) { mpInputForm->inputform::Base::setString(string); }
void Manager::setLanguage(Language language) { meLanguage = language; }
void Manager::setDestination(Destination destination) { meDestination = destination; }
void Manager::limitStringLength(u32 length) { mpInputForm->limitStringLength(length); }
void Manager::limitRowNum(u32 rows) { mpInputForm->limitRowNum(rows); }

void Manager::setAnimationOn(bool enabled) {
    static_cast<nw4rmanager::Layout&>(*mpPCKeyboard).setAnimOn(enabled);
    static_cast<nw4rmanager::Layout&>(*mpCellPhoneKeyboard).setAnimOn(enabled);
    static_cast<nw4rmanager::Layout&>(*mpInputForm).setAnimOn(enabled);
    static_cast<nw4rmanager::Layout&>(*mpCandidateBox).setAnimOn(enabled);
    static_cast<nw4rmanager::Layout&>(*mpToolBar).setAnimOn(enabled);
    static_cast<nw4rmanager::Layout&>(*mpPredictLanguageDialog).setAnimOn(enabled);
    static_cast<nw4rmanager::Layout&>(*mpSignWindow).setAnimOn(enabled);
}
void Manager::setAspectRatio(bool standard) {
    mbAspectRatio4x3 = standard;
    if (static_cast<u8>(standard) == true) setLayoutScaleFor4x3();
    else setLayoutScaleFor16x9();
}
void Manager::setTitleText(wchar_t* title) {
    nw4r::lyt::TextBox* text = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(static_cast<nw4rmanager::Layout&>(*mpInputForm).getPane("T_title_text"));
    if (text != NULL) text->SetString(title, 0);
}
void Manager::setLayoutScaleFor16x9() {
    static_cast<nw4rmanager::Layout&>(*mpPCKeyboard).setRootPaneScaleFor16x9();
    static_cast<nw4rmanager::Layout&>(*mpCellPhoneKeyboard).setRootPaneScaleFor16x9();
    mpInputForm->setRootPaneScaleFor16x9();
    mpCandidateBox->setRootPaneScaleFor16x9();
    static_cast<nw4rmanager::Layout&>(*mpToolBar).setRootPaneScaleFor16x9();
    static_cast<nw4rmanager::Layout&>(*mpPredictLanguageDialog).setRootPaneScaleFor16x9();
    static_cast<nw4rmanager::Layout&>(*mpSignWindow).setRootPaneScaleFor16x9();
}
void Manager::setLayoutScaleFor4x3() {
    static_cast<nw4rmanager::Layout&>(*mpPCKeyboard).setRootPaneScaleFor4x3();
    static_cast<nw4rmanager::Layout&>(*mpCellPhoneKeyboard).setRootPaneScaleFor4x3();
    mpInputForm->setRootPaneScaleFor4x3();
    mpCandidateBox->setRootPaneScaleFor4x3();
    static_cast<nw4rmanager::Layout&>(*mpToolBar).setRootPaneScaleFor4x3();
    static_cast<nw4rmanager::Layout&>(*mpPredictLanguageDialog).setRootPaneScaleFor4x3();
    static_cast<nw4rmanager::Layout&>(*mpSignWindow).setRootPaneScaleFor4x3();
}
inputform::EditBuffer* Manager::createEditBuffer() { return new (MEMAllocFromAllocator(mpAllocator, sizeof(inputform::EditBuffer))) inputform::EditBuffer; }
keyboard::hwkey::HWKeyboard* Manager::createHWKeyboard() { return new (MEMAllocFromAllocator(mpAllocator, sizeof(keyboard::hwkey::HWKeyboard))) keyboard::hwkey::HWKeyboard(this); }
void* Manager::createPCTypeKeyboard() { return new (MEMAllocFromAllocator(mpAllocator, sizeof(keyboard::pctype::Sample))) keyboard::pctype::Sample(this, mpMultiArcResourceAccessor, mpEventObserver, "fs_VK_ascii_keytop_a.brlyt"); }
void* Manager::createCellPhoneTypeKeyboard() { return new (MEMAllocFromAllocator(mpAllocator, sizeof(keyboard::cellphonetype::Sample))) keyboard::cellphonetype::Sample(this, mpMultiArcResourceAccessor, mpEventObserver, "fs_VK_cellPhone_a.brlyt"); }
InputForm* Manager::createInputForm() { return new (MEMAllocFromAllocator(mpAllocator, sizeof(inputform::Sample))) inputform::Sample(this, mpMultiArcResourceAccessor, mpEventObserver, "fs_VK_textBox_a.brlyt"); }
void* Manager::createCandidateBox() { return new (MEMAllocFromAllocator(mpAllocator, sizeof(candidatebox::Sample))) candidatebox::Sample(this, mpMultiArcResourceAccessor, mpEventObserver, "fs_VK_predictInput_a.brlyt"); }
void* Manager::createToolBar() { return new (MEMAllocFromAllocator(mpAllocator, sizeof(toolbar::Sample))) toolbar::Sample(this, mpMultiArcResourceAccessor, mpEventObserver, "fs_VK_toolbar_a.brlyt"); }
void* Manager::createPredictLanguageDialog() { return new (MEMAllocFromAllocator(mpAllocator, sizeof(predictlang::Sample))) predictlang::Sample(this, mpMultiArcResourceAccessor, mpEventObserver, "fs_prdicSelWidw_a.brlyt"); }
predictlang::Base::~Base() {}
void* Manager::createSignWindow() { return new (MEMAllocFromAllocator(mpAllocator, sizeof(keyboard::signwindow::Sample))) keyboard::signwindow::Sample(this, mpMultiArcResourceAccessor, mpEventObserver, "fs_signWindow_a.brlyt"); }
void Manager::startPredictTurnOn(bool enabled) {
    if (getInputForm()->mbPredictOn != enabled) getCandidateBox()->startTurnOn(enabled);
}
bool Manager::isPredictTurning() const { return getCandidateBox()->getOnOffButton().IsTurning(); }
void Manager::enableCompatibleFilter(bool enabled) { inputform::DeadKeyStream::sbCompatibleFilterEnabled = enabled; }
void Manager::enableKSXFilter(bool enabled) {
    static_cast<tistring::Decolated*>(mpEditBuffer->mpString)->EnableKSXFilter(enabled);
    static_cast<tistring::Decolated*>(mpEditBuffer->mpZiString)->EnableKSXFilter(enabled);
}
bool Manager::isVacancy() const {
    if (!getInputForm() || !getToolBar()) return true;
    if (!getToolBar()->isQwerty() && getCellPhoneKeyboard()->isHoldingButton()) return false;
    return getInputForm()->inputform::Base::isVacancy();
}
void Manager::SetFont(nw4r::lyt::FontRefLink* link) {
    nw4r::ut::Font* font = link->GetFont();
    if (mpToolBar) static_cast<nw4rmanager::Layout&>(*mpToolBar).SetFontForce(font);
    if (mpPCKeyboard) static_cast<nw4rmanager::Layout&>(*mpPCKeyboard).SetFontForce(font);
    if (mpCandidateBox) static_cast<nw4rmanager::Layout&>(*mpCandidateBox).SetFontForce(font);
    if (mpSignWindow) static_cast<nw4rmanager::Layout&>(*mpSignWindow).SetFontForce(font);
    if (mpInputForm) mpInputForm->nw4r::ut::CharWriter::SetFont(*font);
    if (mpCellPhoneKeyboard) static_cast<nw4rmanager::Layout&>(*mpCellPhoneKeyboard).SetFontForce(font);
}
void* Manager::getPredictLanguageSelectDialog() { return mpPredictLanguageDialog; }
const void* Manager::getPredictLanguageSelectDialog() const { return mpPredictLanguageDialog; }
void* Manager::getSignKeyboard() { return mpSignWindow; }
const void* Manager::getSignKeyboard() const { return mpSignWindow; }
void Manager::setDefaultPredictionJP(int count, const char** predictions) {
    static_cast<tistring::WithAtok*>(getInputForm()->getAtokString())->setDefaultPrediction(count, predictions);
}
void predictlang::Base::init() {}
void predictlang::Base::create(MEMAllocator* allocator) { mpAllocator = allocator; }
keyboard::pctype::Sample::~Sample() {}
keyboard::cellphonetype::Sample::~Sample() {}
candidatebox::Sample::~Sample() {}
inputform::Sample::~Sample() {}
toolbar::Sample::~Sample() {}
predictlang::Sample::~Sample() {}
keyboard::signwindow::Sample::~Sample() {}
}
