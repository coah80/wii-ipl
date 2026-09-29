#define TI_PCTYPE_SAMPLE_CLASS
#define TI_CELLPHONE_SAMPLE_CLASS
#define TI_INPUTFORM_SAMPLE_CLASS
#define TI_CANDIDATEBOX_SAMPLE_CLASS
#define TI_TOOLBAR_SAMPLE_CLASS
#define TI_PREDICTLANG_SAMPLE_CLASS
#define TI_SIGNWINDOW_SAMPLE_CLASS

#include "keyboard/tiPcKeyboard.h"
#include "keyboard/tiCellPhone.h"
#include "keyboard/tiCandidateBox.h"
#include "keyboard/tiInputForm.h"
#include "keyboard/tiToolBar.h"
#include "keyboard/tiPredictLang.h"
#include "keyboard/tiSignWindow.h"
#include "keyboard/tiManager.h"
#include "keyboard/tiCandidateBox.h"
#include "keyboard/tiPredictLang.h"
#include "keyboard/tiSignWindow.h"

#include <revolution/gx.h>
#include <revolution/sc.h>

#include <new>

namespace textinput {

    static EventObserver sDefaultObserver;

    Manager::Manager(MEMAllocator* allocator, nw4r::lyt::MultiArcResourceAccessor* multiArc,
                     textinput::EventObserver* event)
        : mpAllocator(allocator), mpMultiArcResourceAccessor(multiArc), mpEditBuffer(NULL), mpHWKeyboard(NULL),
          mpPCKeyboard(NULL), mpCellPhoneKeyboard(NULL), mpInputForm(NULL), mpCandidateBox(NULL), mpToolBar(NULL),
          mpPredictLanguageDialog(NULL), mpSignWindow(NULL), mpEventObserver(event),
          meDestination(DST_JP), meLanguage(JP), mbAspectRatio4x3(true) {
    if (event == NULL) {
        mpEventObserver = &sDefaultObserver;
    }
}

    Manager::~Manager() {
        if (mpPCKeyboard != NULL) {
            mpPCKeyboard->~LayoutByNW4R();
            MEMFreeToAllocator(mpAllocator, mpPCKeyboard);
        }
        if (mpCellPhoneKeyboard != NULL) {
            mpCellPhoneKeyboard->~LayoutByNW4R();
            MEMFreeToAllocator(mpAllocator, mpCellPhoneKeyboard);
        }
        if (mpInputForm != NULL) {
            mpInputForm->~LayoutByNW4R();
            MEMFreeToAllocator(mpAllocator, mpInputForm);
        }
        if (mpCandidateBox != NULL) {
            mpCandidateBox->~LayoutByNW4R();
            MEMFreeToAllocator(mpAllocator, mpCandidateBox);
        }
        if (mpToolBar != NULL) {
            mpToolBar->~LayoutByNW4R();
            MEMFreeToAllocator(mpAllocator, mpToolBar);
        }
        if (mpPredictLanguageDialog != NULL) {
            mpPredictLanguageDialog->~LayoutByNW4R();
            MEMFreeToAllocator(mpAllocator, mpPredictLanguageDialog);
        }
        if (mpSignWindow != NULL) {
            mpSignWindow->~LayoutByNW4R();
            MEMFreeToAllocator(mpAllocator, mpSignWindow);
        }
        if (mpHWKeyboard != NULL) {
            mpHWKeyboard->~HWKeyboard();
            MEMFreeToAllocator(mpAllocator, mpHWKeyboard);
        }
        if (mpEditBuffer != NULL) {
            mpEditBuffer->~EditBuffer();
            MEMFreeToAllocator(mpAllocator, mpEditBuffer);
        }
    }

    keyboard::hwkey::HWKeyboard::~HWKeyboard() {}

    void Manager::create(MEMAllocator* allocator) {
        mpEditBuffer = createEditBuffer();
        mpEditBuffer->inputform::EditBuffer::create(mpAllocator);
        mpHWKeyboard = createHWKeyboard();
        mpPCKeyboard = (keyboard::pctype::LayoutByNW4R*)createPCTypeKeyboard();
        mpPCKeyboard->create(mpAllocator);
        mpCellPhoneKeyboard = (keyboard::cellphonetype::LayoutByNW4R*)createCellPhoneTypeKeyboard();
        mpCellPhoneKeyboard->create(mpAllocator);
        mpInputForm = createInputForm();
        mpInputForm->create(mpAllocator, mpEditBuffer);
        mpCandidateBox = (candidatebox::LayoutByNW4R*)createCandidateBox();
        mpCandidateBox->create(mpAllocator);
        mpToolBar = (toolbar::LayoutByNW4R*)createToolBar();
        mpToolBar->create(mpAllocator);
        mpPredictLanguageDialog = (predictlang::LayoutByNW4R*)createPredictLanguageDialog();
        mpPredictLanguageDialog->create(mpAllocator);
        mpSignWindow = (keyboard::signwindow::LayoutByNW4R*)createSignWindow();
        mpSignWindow->create(mpAllocator);
        initAspect();
        init();
    }

    void Manager::initAspect() {
        if (SCGetAspectRatio() == SC_ASPECT_RATIO_16x9) {
            setLayoutScaleFor16x9();
            mbAspectRatio4x3 = false;
        } else {
            setLayoutScaleFor4x3();
            mbAspectRatio4x3 = true;
        }
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

        if (mbAspectRatio4x3 == true) {
            setLayoutScaleFor4x3();
        } else {
            setLayoutScaleFor16x9();
        }

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

    void Manager::setFixedPredictionJP(int num, const char** predicts) {
        static_cast<tistring::WithAtok*>(getInputForm()->getAtokString())->setFixPrediction(num, predicts);
    }

    void Manager::calc() {
        if (mpToolBar->isQwerty()) {
            mpPCKeyboard->calc();
        } else {
            mpCellPhoneKeyboard->calc();
        }
        mpToolBar->calc();
        mpCandidateBox->calc();
        mpInputForm->calc();
        if (mpPredictLanguageDialog->isActive()) {
            mpPredictLanguageDialog->calc();
        }
        if (mpSignWindow->isActive()) {
            mpSignWindow->calc();
        }
    }

    void Manager::draw() {
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
        mpToolBar->draw();
        mpInputForm->draw();
        if (mpToolBar->isQwerty()) {
            mpPCKeyboard->draw();
        } else {
            mpCellPhoneKeyboard->draw();
        }
        mpCandidateBox->draw();
        if (mpPredictLanguageDialog->isActive()) {
            mpPredictLanguageDialog->draw();
        }
        if (mpSignWindow->isActive()) {
            mpSignWindow->draw();
        }
    }

    bool Manager::updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release) {
        bool qwerty = mpToolBar->isQwerty();
        nw4rmanager::TiEventHandler::Input input;
        input.field_0x00 = chan;
        input.mfX = x;
        input.mfY = y;
        input.field_0x0C = trig;
        input.field_0x10 = hold;
        input.field_0x14 = release;

        mpHWKeyboard->keyboard::hwkey::HWKeyboard::updateInput(chan, x, y, trig, hold, release, &input);

        if (mpPredictLanguageDialog->isActive()) {
            return mpPredictLanguageDialog
                ->updateInput(chan, x, y, trig, hold, release, &input);
        }

        mpInputForm->updateInputCommon(chan, trig, hold, release, &input);

        if (mpSignWindow->isActive()) {
            return mpSignWindow
                ->updateInput(chan, x, y, trig, hold, release, &input);
        }

        bool updatedKeyboard;
        if (qwerty) {
            updatedKeyboard = mpPCKeyboard->updateInput(chan, x, y, trig, hold, release, &input);
        } else {
            updatedKeyboard = mpCellPhoneKeyboard->updateInput(chan, x, y, trig, hold, release, &input);
        }
        bool updatedToolBar =
            mpToolBar->updateInput(chan, x, y, trig, hold, release, &input);
        bool updatedCandBox =
            mpCandidateBox->updateInput(chan, x, y, trig, hold, release, &input);
        bool updatedInputForm = mpInputForm->updateInput(chan, x, y, trig, hold, release, &input);

        bool result = (updatedKeyboard | updatedToolBar | updatedCandBox | updatedInputForm) != 0;

        if (mpToolBar->isQwerty() != qwerty) {
            getInputForm()->onCommand((CommandReceiver::INPUT_COMMAND)6, NULL);
            mpCandidateBox->checkValidation();
            if (mpToolBar->isQwerty()) {
                mpPCKeyboard->onActive();
            } else {
                mpCellPhoneKeyboard->onActive();
            }
        }
        return result;
    }

    bool Manager::updateInput(input::HKBManager& hkbManager) {
        bool qwerty = mpToolBar->isQwerty();

        if (mpPredictLanguageDialog->isActive()) {
            return mpPredictLanguageDialog
                ->updateInput(hkbManager);
        }
        if (mpSignWindow->isActive()) {
            return mpSignWindow->updateInput(hkbManager);
        }

        bool updatedKeyboard;
        if (qwerty) {
            updatedKeyboard = mpPCKeyboard->updateInput(hkbManager);
        } else {
            updatedKeyboard = mpCellPhoneKeyboard->updateInput(hkbManager);
        }
        bool updatedToolBar = mpToolBar->updateInput(hkbManager);
        bool updatedCandBox = mpCandidateBox->updateInput(hkbManager);
        bool updatedInputForm = mpInputForm->updateInput(hkbManager);

        bool result = (updatedKeyboard | updatedToolBar | updatedCandBox | updatedInputForm) != 0;

        if (mpToolBar->isQwerty() != qwerty) {
            getInputForm()->onCommand((CommandReceiver::INPUT_COMMAND)6, NULL);
            mpCandidateBox->checkValidation();
            if (mpToolBar->isQwerty()) {
                mpPCKeyboard->onActive();
            } else {
                mpCellPhoneKeyboard->onActive();
            }
        }
        return result;
    }

    wchar_t* Manager::getWCString() const {
        return mpInputForm->getWCString();
    }

    void Manager::setWCString(const wchar_t* string) {
        mpInputForm->inputform::Base::setString(string);
    }

    void Manager::setLanguage(Language language) {
        meLanguage = language;
    }

    void Manager::setDestination(Destination destination) {
        meDestination = destination;
    }

    void Manager::limitStringLength(u32 limitStringLength) {
        mpInputForm->limitStringLength(limitStringLength);
    }

    void Manager::limitRowNum(u32 limitRowNum) {
        mpInputForm->limitRowNum(limitRowNum);
    }

    void Manager::setAnimationOn(bool flag) {
        mpPCKeyboard->setAnimOn(flag);
        mpCellPhoneKeyboard->setAnimOn(flag);
        mpInputForm->setAnimOn(flag);
        mpCandidateBox->setAnimOn(flag);
        mpToolBar->setAnimOn(flag);
        mpPredictLanguageDialog
            ->setAnimOn(flag);
        mpSignWindow
            ->setAnimOn(flag);
    }

    void Manager::setAspectRatio(bool b4x3) {
        mbAspectRatio4x3 = b4x3;
        if (mbAspectRatio4x3 == true) {
            setLayoutScaleFor4x3();
        } else {
            setLayoutScaleFor16x9();
        }
    }

    void Manager::setTitleText(wchar_t* titleText) {
        nw4r::lyt::Pane* pane = mpInputForm->getPane("T_title_text");
        nw4r::lyt::TextBox* textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(pane);
        if (textBox != NULL) {
            textBox->SetString(titleText, 0);
        }
    }

    void Manager::setLayoutScaleFor16x9() {
        mpPCKeyboard->setRootPaneScaleFor16x9();
        mpCellPhoneKeyboard->setRootPaneScaleFor16x9();
        mpInputForm->setRootPaneScaleFor16x9();
        mpCandidateBox->setRootPaneScaleFor16x9();
        mpToolBar->setRootPaneScaleFor16x9();
        mpPredictLanguageDialog
            ->setRootPaneScaleFor16x9();
        mpSignWindow
            ->setRootPaneScaleFor16x9();
    }

    void Manager::setLayoutScaleFor4x3() {
        mpPCKeyboard->setRootPaneScaleFor4x3();
        mpCellPhoneKeyboard->setRootPaneScaleFor4x3();
        mpInputForm->setRootPaneScaleFor4x3();
        mpCandidateBox->setRootPaneScaleFor4x3();
        mpToolBar->setRootPaneScaleFor4x3();
        mpPredictLanguageDialog
            ->setRootPaneScaleFor4x3();
        mpSignWindow
            ->setRootPaneScaleFor4x3();
    }

    inputform::EditBuffer* Manager::createEditBuffer() {
        return new (MEMAllocFromAllocator(mpAllocator, sizeof(inputform::EditBuffer))) inputform::EditBuffer();
    }

    keyboard::hwkey::HWKeyboard* Manager::createHWKeyboard() {
        return new (MEMAllocFromAllocator(mpAllocator, sizeof(keyboard::hwkey::HWKeyboard))) keyboard::hwkey::HWKeyboard(this);
    }

    void* Manager::createPCTypeKeyboard() {
        return new (MEMAllocFromAllocator(mpAllocator, sizeof(keyboard::pctype::Sample))) keyboard::pctype::Sample(this, mpMultiArcResourceAccessor, "fs_VK_ascii_keytop_a.brlyt", mpEventObserver);
    }

    void* Manager::createCellPhoneTypeKeyboard() {
        return new (MEMAllocFromAllocator(mpAllocator, sizeof(keyboard::cellphonetype::Sample))) keyboard::cellphonetype::Sample(this, mpMultiArcResourceAccessor, "fs_VK_cellPhone_a.brlyt", mpEventObserver);
    }

    InputForm* Manager::createInputForm() {
        return new (MEMAllocFromAllocator(mpAllocator, sizeof(inputform::Sample)))
            inputform::Sample(this, mpMultiArcResourceAccessor, "fs_VK_textBox_a.brlyt", mpEventObserver, NULL);
    }

    void* Manager::createCandidateBox() {
        return new (MEMAllocFromAllocator(mpAllocator, sizeof(candidatebox::Sample))) candidatebox::Sample(this, mpMultiArcResourceAccessor, "fs_VK_predictInput_a.brlyt", mpEventObserver);
    }

    void* Manager::createToolBar() {
        return new (MEMAllocFromAllocator(mpAllocator, sizeof(toolbar::Sample))) toolbar::Sample(this, mpMultiArcResourceAccessor, "fs_VK_toolbar_a.brlyt", mpEventObserver);
    }

    void* Manager::createPredictLanguageDialog() {
        return new (MEMAllocFromAllocator(mpAllocator, sizeof(predictlang::Sample))) predictlang::Sample(this, mpMultiArcResourceAccessor, "fs_prdicSelWidw_a.brlyt", mpEventObserver);
    }

    void* Manager::createSignWindow() {
        return new (MEMAllocFromAllocator(mpAllocator, sizeof(keyboard::signwindow::Sample))) keyboard::signwindow::Sample(this, mpMultiArcResourceAccessor, "fs_signWindow_a.brlyt", mpEventObserver);
    }

    void Manager::startPredictTurnOn(bool flag) {
        if (getInputForm()->isPredictOn() != flag) {
            getCandidateBox()->startTurnOn(flag);
        }
    }

    bool Manager::isPredictTurning() const {
        return getCandidateBox()->getOnOffButton().IsTurning();
    }

    void Manager::enableCompatibleFilter(bool compatibleFilter) {
        inputform::DeadKeyStream::sbCompatibleFilterEnabled = compatibleFilter;
    }

    void Manager::enableKSXFilter(bool flag) {
        static_cast<tistring::Decolated*>(mpEditBuffer->getString())->EnableKSXFilter(flag);
        static_cast<tistring::Decolated*>(mpEditBuffer->getZiString())->EnableKSXFilter(flag);
    }

    bool Manager::isVacancy() const {
        if (getInputForm() == NULL || getToolBar() == NULL) {
            return true;
        }
        if (!getToolBar()->isQwerty()) {
            if (getCellPhoneKeyboard()->isHoldingButton()) {
                return false;
            }
        }
        return getInputForm()->inputform::Base::isVacancy();
    }

    const InputForm* Manager::getInputForm() const {
        return mpInputForm;
    }

    const keyboard::cellphonetype::LayoutByNW4R* Manager::getCellPhoneKeyboard() const {
        return mpCellPhoneKeyboard;
    }

    void Manager::SetFont(nw4r::lyt::FontRefLink* fontLink) {
        nw4r::ut::Font* font = fontLink->GetFont();
        if (mpToolBar != NULL) {
            mpToolBar->SetFontForce(font);
        }
        if (mpPCKeyboard != NULL) {
            mpPCKeyboard->SetFontForce(font);
        }
        if (mpCandidateBox != NULL) {
            mpCandidateBox->SetFontForce(font);
        }
        if (mpSignWindow != NULL) {
            mpSignWindow
                ->SetFontForce(font);
        }
        if (mpInputForm != NULL) {
            ((nw4r::ut::CharWriter*)((char*)mpInputForm + 0x10))->SetFont(*font);
        }
        if (mpCellPhoneKeyboard != NULL) {
            mpCellPhoneKeyboard->SetFontForce(font);
        }
    }

    void* Manager::getPredictLanguageSelectDialog() {
        return mpPredictLanguageDialog;
    }

    const void* Manager::getPredictLanguageSelectDialog() const {
        return mpPredictLanguageDialog;
    }

    void* Manager::getSignKeyboard() {
        return mpSignWindow;
    }

    const void* Manager::getSignKeyboard() const {
        return mpSignWindow;
    }

    void Manager::setDefaultPredictionJP(int num, const char** predicts) {
        static_cast<tistring::WithAtok*>(getInputForm()->getAtokString())->setDefaultPrediction(num, predicts);
    }

    void predictlang::Base::init() {}

    keyboard::pctype::Sample::~Sample() {}

    keyboard::cellphonetype::Sample::~Sample() {}

    candidatebox::Sample::~Sample() {}

    inputform::Sample::~Sample() {}

    keyboard::signwindow::Sample::~Sample() {}

}  // namespace textinput
