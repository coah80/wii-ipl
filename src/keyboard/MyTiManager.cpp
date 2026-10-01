#include "keyboard/MyTiManager.h"

#include "keyboard/tiUtil.h"
#include "keyboard/tiLanguageIndependentData.h"

#include <new>

#include <revolution/GX.h>

namespace textinput {
    namespace extend {
        namespace memo {
            DispMemoState             sDispMemoState;
            EditMemoState             sEditMemoState;
            AppearMemoState           sAppearMemoState;
            DisappearMemoState        sDisappearMemoState;

            static f32 scPosAnimParam[2] = {-200.0f, 0.0f};
            static f32 scAlphaAnimParam[2] = {0.0f, 255.0f};
            static f32 scMemoAnimParam[2] = {0.0f, 145.0f};

            DisappearMemoState::~DisappearMemoState() {
            }

            Manager::~Manager() {
                if (mpDefaultPCKeyboard != NULL) {
                    mpDefaultPCKeyboard->~LayoutByNW4R();
                    MEMFreeToAllocator(mpAllocator, mpDefaultPCKeyboard);
                }
                if (mpDefaultCellPhoneKeyboard != NULL) {
                    mpDefaultCellPhoneKeyboard->~LayoutByNW4R();
                    MEMFreeToAllocator(mpAllocator, mpDefaultCellPhoneKeyboard);
                }
                if (mpDefaultInputForm != NULL) {
                    mpDefaultInputForm->~InputForm();
                    MEMFreeToAllocator(mpAllocator, mpDefaultInputForm);
                }
                if (mpDefaultCandidateBox != NULL) {
                    mpDefaultCandidateBox->~LayoutByNW4R();
                    MEMFreeToAllocator(mpAllocator, mpDefaultCandidateBox);
                }
                if (mpDefaultToolBar != NULL) {
                    mpDefaultToolBar->~LayoutByNW4R();
                    MEMFreeToAllocator(mpAllocator, mpDefaultToolBar);
                }
                if (mpDefaultPredictLanguageDialog != NULL) {
                    mpDefaultPredictLanguageDialog->~LayoutByNW4R();
                    MEMFreeToAllocator(mpAllocator, mpDefaultPredictLanguageDialog);
                }
                if (mpDefaultSignWindow != NULL) {
                    mpDefaultSignWindow->~LayoutByNW4R();
                    MEMFreeToAllocator(mpAllocator, mpDefaultSignWindow);
                }
                if (mpMemoInputForm != NULL) {
                    mpMemoInputForm->~InputForm();
                    MEMFreeToAllocator(mpAllocator, mpMemoInputForm);
                }
                if (mpLetterInputForm != NULL) {
                    mpLetterInputForm->~InputForm();
                    MEMFreeToAllocator(mpAllocator, mpLetterInputForm);
                }
                if (mpBigTextInputForm != NULL) {
                    mpBigTextInputForm->~InputForm();
                    MEMFreeToAllocator(mpAllocator, mpBigTextInputForm);
                }
                if (mpBackGround != NULL) {
                    mpBackGround->~LayoutByNW4R();
                    MEMFreeToAllocator(mpAllocator, mpBackGround);
                }
                mpPCKeyboard        = NULL;
                mpCellPhoneKeyboard = NULL;
                mpInputForm         = NULL;
                mpCandidateBox      = NULL;
                mpToolBar           = NULL;
                mpPredictLanguageDialog = NULL;
                mpSignWindow        = NULL;
            }

            void Manager::create(MEMAllocator* allocator) {
                mpEditBuffer = createEditBuffer();
                mpEditBuffer->inputform::EditBuffer::create(mpAllocator);

                mpHWKeyboard = createHWKeyboard();

                mpDefaultPCKeyboard = (keyboard::pctype::LayoutByNW4R*)createPCTypeKeyboard();
                mpDefaultPCKeyboard->create(mpAllocator);

                mpDefaultCellPhoneKeyboard = (keyboard::cellphonetype::LayoutByNW4R*)createCellPhoneTypeKeyboard();
                mpDefaultCellPhoneKeyboard->create(mpAllocator);

                mpDefaultInputForm = createInputForm();
                mpDefaultInputForm->create(mpAllocator, mpEditBuffer);

                mpDefaultCandidateBox = (candidatebox::LayoutByNW4R*)createCandidateBox();
                mpDefaultCandidateBox->create(mpAllocator);

                mpDefaultToolBar = (toolbar::LayoutByNW4R*)createToolBar();
                mpDefaultToolBar->create(mpAllocator);

                mpDefaultPredictLanguageDialog = (predictlang::LayoutByNW4R*)createPredictLanguageDialog();
                mpDefaultPredictLanguageDialog->create(mpAllocator);

                mpDefaultSignWindow = (keyboard::signwindow::LayoutByNW4R*)createSignWindow();
                mpDefaultSignWindow->create(mpAllocator);

                mpMemoInputForm = createMemoInputForm();
                mpMemoInputForm->create(mpAllocator, mpEditBuffer);

                mpLetterInputForm = createLetterInputForm();
                mpLetterInputForm->create(mpAllocator, mpEditBuffer);

                mpBigTextInputForm = createBigTextInputForm();
                mpBigTextInputForm->create(mpAllocator, mpEditBuffer);

                mpBackGround = createBG();
                mpBackGround->create(mpAllocator);

                configDefault();

                sDispMemoState.mpManager      = this;
                sEditMemoState.mpManager      = this;
                sAppearMemoState.mpManager    = this;
                sDisappearMemoState.mpManager = this;
                sDisappearMemoState.create();

                initAspect();

                mMemoSetting.uRevisionAndType = 0xf0;
                mMemoSetting.uRawData.val[0]  = 0;
                mMemoSetting.uRawData.val[1]  = 0;
                mMemoSetting.uRawData.val[2]  = 0;
                mMemoSetting.uRawData.val[3]  = 0;
                mMemoSetting.uRawData.val[4]  = 0;
                mMemoSetting.uRawData.val[5]  = 0;
                mMemoSetting.uRawData.val[6]  = 0;

                init();
            }

            void Manager::init() {
                mpCurrentState = &sDispMemoState;
                mpCurrentState->start();
                mpCurrentState->init();

                mpDefaultPCKeyboard->getLayout()->GetRootPane()->SetInfluencedAlpha(true);
                mpDefaultCellPhoneKeyboard->getLayout()->GetRootPane()->SetInfluencedAlpha(true);
                mpDefaultInputForm->getLayout()->GetRootPane()->SetInfluencedAlpha(true);
                mpMemoInputForm->getLayout()->GetRootPane()->SetInfluencedAlpha(true);
                mpLetterInputForm->getLayout()->GetRootPane()->SetInfluencedAlpha(true);
                mpBigTextInputForm->getLayout()->GetRootPane()->SetInfluencedAlpha(true);
                mpDefaultCandidateBox->getLayout()->GetRootPane()->SetInfluencedAlpha(true);
                mpDefaultToolBar->getLayout()->GetRootPane()->SetInfluencedAlpha(true);
                mpBackGround->getLayout()->GetRootPane()->SetInfluencedAlpha(true);
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
                    case ST_Hidden: {
                        mpEventObserver->onSE(sound::SE_OPEN);
                        mpCurrentState->end();
                        mpCurrentState = &sAppearMemoState;
                        mpCurrentState->start();
                        break;
                    }
                    case ST_Appearing: {
                        mpEventObserver->onSE(sound::SE_APPEARED);
                        mpCurrentState->end();
                        mpCurrentState = &sEditMemoState;
                        mpCurrentState->start();
                        break;
                    }
                    case ST_Visible: {
                        mpCurrentState->end();
                        mpCurrentState = &sDisappearMemoState;
                        mpCurrentState->start();
                        break;
                    }
                    case ST_Disappearing: {
                        mpEventObserver->onSE(sound::SE_DISAPPEARD);
                        mpCurrentState->end();
                        mpCurrentState = &sDispMemoState;
                        mpCurrentState->start();
                        break;
                    }
                }
            }

            InputForm* Manager::createMemoInputForm() {
                MemoInputForm* inputForm = (MemoInputForm*)MEMAllocFromAllocator(mpAllocator, sizeof(MemoInputForm));
                inputForm = new (inputForm) MemoInputForm(this, mpMultiArcResourceAccessor, "my_Memo_a.brlyt", mpEventObserver, "WiiBitmapFontType2.brfnt");
                return inputForm;
            }

            letter::InputForm* Manager::createLetterInputForm() {
                LetterInputForm* inputForm = (LetterInputForm*)MEMAllocFromAllocator(mpAllocator, sizeof(LetterInputForm));
                inputForm = new (inputForm) LetterInputForm(this, mpMultiArcResourceAccessor, "my_LetterL.brlyt", mpEventObserver, "WiiBitmapFontType2.brfnt");
                return inputForm;
            }

            textinput::InputForm* Manager::createInputForm() {
                textinput::InputForm* inputForm = (textinput::InputForm*)MEMAllocFromAllocator(mpAllocator, sizeof(inputform::LayoutByNW4R));
                inputForm = new (inputForm) inputform::LayoutByNW4R(this, mpMultiArcResourceAccessor, "fs_VK_textBox_a.brlyt", mpEventObserver, "WiiBitmapFontType1.brfnt");
                return inputForm;
            }

            textinput::InputForm* Manager::createBigTextInputForm() {
                textinput::InputForm* inputForm = (textinput::InputForm*)MEMAllocFromAllocator(mpAllocator, sizeof(inputform::LayoutByNW4R));
                inputForm = new (inputForm) inputform::LayoutByNW4R(this, mpMultiArcResourceAccessor, "fs_VK_textBox_b.brlyt", mpEventObserver, "WiiBitmapFontType1.brfnt");
                return inputForm;
            }

            bg::LayoutByNW4R* Manager::createBG() {
                bg::LayoutByNW4R* backGround = (bg::LayoutByNW4R*)MEMAllocFromAllocator(mpAllocator, sizeof(bg::LayoutByNW4R));
                backGround = new (backGround) bg::LayoutByNW4R(mpMultiArcResourceAccessor, "fs_VK_bg_a.brlyt", mpEventObserver);
                return backGround;
            }

            void Manager::configDefault() {
                meConfigType = CT_Default;

                mpPCKeyboard              = mpDefaultPCKeyboard;
                mpCellPhoneKeyboard       = mpDefaultCellPhoneKeyboard;
                mpInputForm               = mpDefaultInputForm;
                mpCandidateBox            = mpDefaultCandidateBox;
                mpToolBar                 = mpDefaultToolBar;
                mpPredictLanguageDialog   = mpDefaultPredictLanguageDialog;
                mpSignWindow              = mpDefaultSignWindow;

                textinput::Manager::init();

                mpToolBar->setQwerty(true);
                mpInputForm->enableSpaceByRight(false);
                mpInputForm->doWordWrap(true);
                if (meDestination != DST_US && meDestination != DST_EU) {
                    mpInputForm->doWordWrap(false);
                }
                mpInputForm->dirtyCacheAll();
            }

            void Manager::configNumeric() {
                meConfigType = CT_Numeric;

                mpPCKeyboard              = mpDefaultPCKeyboard;
                mpCellPhoneKeyboard       = mpDefaultCellPhoneKeyboard;
                mpInputForm               = mpBigTextInputForm;
                mpCandidateBox            = mpDefaultCandidateBox;
                mpToolBar                 = mpDefaultToolBar;
                mpPredictLanguageDialog   = mpDefaultPredictLanguageDialog;
                mpSignWindow              = mpDefaultSignWindow;

                textinput::Manager::init();

                mpToolBar->setQwerty(false);
                mpToolBar->enableKeytopChange(false);
                mpCellPhoneKeyboard->doNumericMode(true);
                mpCellPhoneKeyboard->setLineFeedButton(false);
                mpCandidateBox->setActive(false);
                mpCellPhoneKeyboard->setPredictLanguageButton(false);
                mpPCKeyboard->setPredictLanguageButton(false);
                mpInputForm->doWordWrap(false);
                mpInputForm->enableSpaceByRight(false);
                mpInputForm->dirtyCacheAll();
            }

            void Manager::configNumericWithSeparator() {
                configNumeric();
                meConfigType = CT_NumericWithSeparator;
                mpInputForm->visibleSeparator(true);
            }

            void Manager::configLetter() {
                meConfigType = CT_Letter;

                mpPCKeyboard              = mpDefaultPCKeyboard;
                mpCellPhoneKeyboard       = mpDefaultCellPhoneKeyboard;
                mpInputForm               = mpMemoInputForm;
                mpCandidateBox            = mpDefaultCandidateBox;
                mpToolBar                 = mpDefaultToolBar;
                mpPredictLanguageDialog   = mpDefaultPredictLanguageDialog;
                mpSignWindow              = mpDefaultSignWindow;

                textinput::Manager::init();

                Language language = mpToolBar->getLanguage();
                const wchar_t* okCaption = langindependent::cLanguageIndependentString[langindependent::LANG_STRID_OK][language];
                const wchar_t* backCaption = langindependent::cLanguageIndependentString[langindependent::LANG_STRID_BACK][language];
                mpToolBar->setOKButtonVisible(true);
                mpToolBar->setOKButtonCaption(okCaption);
                mpToolBar->setCancelButtonCaption(backCaption);
                mpInputForm->doWordWrap(true);
                mpInputForm->enableSpaceByRight(true);
                if (meDestination != DST_US && meDestination != DST_EU) {
                    mpInputForm->doWordWrap(false);
                }
                reflectSaveData();
                limitStringLength(0x100);
                limitRowNum(0x10);
                scMemoAnimParam[1] = 145.0f;
                mpInputForm->dirtyCacheAll();
            }

            void Manager::configPhotoLetter() {
                meConfigType = CT_PhotoLetter;

                mpPCKeyboard              = mpDefaultPCKeyboard;
                mpCellPhoneKeyboard       = mpDefaultCellPhoneKeyboard;
                mpInputForm               = mpLetterInputForm;
                mpCandidateBox            = mpDefaultCandidateBox;
                mpToolBar                 = mpDefaultToolBar;
                mpPredictLanguageDialog   = mpDefaultPredictLanguageDialog;
                mpSignWindow              = mpDefaultSignWindow;

                textinput::Manager::init();

                mpToolBar->setOKButtonVisible(true);
                mpToolBar->setOKButtonCaption(langindependent::cLanguageIndependentString[langindependent::LANG_STRID_OK][mpToolBar->getLanguage()]);
                mpToolBar->setCancelButtonCaption(langindependent::cLanguageIndependentString[langindependent::LANG_STRID_BACK][mpToolBar->getLanguage()]);
                mpInputForm->doWordWrap(true);
                mpInputForm->enableSpaceByRight(true);
                if (meDestination != DST_US && meDestination != DST_EU) {
                    mpInputForm->doWordWrap(false);
                }
                reflectSaveData();
                limitStringLength(0x100);
                limitRowNum(0x10);
                scMemoAnimParam[1] = 151.0f;
                mpInputForm->dirtyCacheAll();
            }

            void Manager::configNormalWithoutLineFeed() {
                configDefault();
                meConfigType = CT_NormalWithoutLineFeed;

                mpCellPhoneKeyboard->setLineFeedButton(false);
                mpPCKeyboard->setLineFeedButton(false);
                mpCandidateBox->setActive(false);
                mpCellPhoneKeyboard->setPredictLanguageButton(false);
                mpPCKeyboard->setPredictLanguageButton(false);
                mpCellPhoneKeyboard->setSignWindowButton(false);
                mpPCKeyboard->setSignWindowButton(false);
                mpInputForm->doWordWrap(false);
                mpInputForm->enableSpaceByRight(false);
            }

            void Manager::configNormalBigTextWithoutLineFeed() {
                configDefault();
                mpInputForm = mpBigTextInputForm;
                textinput::Manager::init();
                meConfigType = CT_NormalBigTextWithoutLineFeed;

                mpCellPhoneKeyboard->setLineFeedButton(false);
                mpPCKeyboard->setLineFeedButton(false);
                mpCandidateBox->setActive(false);
                mpCellPhoneKeyboard->setPredictLanguageButton(false);
                mpPCKeyboard->setPredictLanguageButton(false);
                mpToolBar->enableKeytopChange(true);
                mpToolBar->setQwerty(true);
                mpCellPhoneKeyboard->setSignWindowButton(false);
                mpPCKeyboard->setSignWindowButton(false);
                mpInputForm->doWordWrap(false);
                mpInputForm->enableSpaceByRight(false);
                mpInputForm->dirtyCacheAll();
            }

            void Manager::configOnlyQwertyWithoutLineFeedAndSign() {
                meConfigType = CT_OnlyQwertyWithoutLineFeedAndSign;

                mpPCKeyboard              = mpDefaultPCKeyboard;
                mpCellPhoneKeyboard       = mpDefaultCellPhoneKeyboard;
                mpInputForm               = mpDefaultInputForm;
                mpCandidateBox            = mpDefaultCandidateBox;
                mpToolBar                 = mpDefaultToolBar;
                mpPredictLanguageDialog   = mpDefaultPredictLanguageDialog;
                mpSignWindow              = mpDefaultSignWindow;

                textinput::Manager::init();

                mpToolBar->setQwerty(true);
                mpPCKeyboard->onlyQwerty(true);
                mpToolBar->enableKeytopChange(false);
                mpPCKeyboard->setLineFeedButton(false);
                mpCellPhoneKeyboard->setLineFeedButton(false);
                mpCandidateBox->setActive(false);
                mpCellPhoneKeyboard->setPredictLanguageButton(false);
                mpPCKeyboard->setPredictLanguageButton(false);
                mpCellPhoneKeyboard->setSignWindowButton(false);
                mpPCKeyboard->setSignWindowButton(false);
                mpInputForm->doWordWrap(false);
                mpInputForm->enableSpaceByRight(false);
                mpInputForm->dirtyCacheAll();
            }

            void Manager::configOnlyQwertyBigTextWithoutLineFeedAndSign() {
                meConfigType = CT_OnlyQwertyBigTextWithoutLineFeedAndSign;

                mpPCKeyboard              = mpDefaultPCKeyboard;
                mpCellPhoneKeyboard       = mpDefaultCellPhoneKeyboard;
                mpInputForm               = mpBigTextInputForm;
                mpCandidateBox            = mpDefaultCandidateBox;
                mpToolBar                 = mpDefaultToolBar;
                mpPredictLanguageDialog   = mpDefaultPredictLanguageDialog;
                mpSignWindow              = mpDefaultSignWindow;

                textinput::Manager::init();

                mpToolBar->setQwerty(true);
                mpPCKeyboard->onlyQwerty(true);
                mpToolBar->enableKeytopChange(false);
                mpPCKeyboard->setLineFeedButton(false);
                mpCellPhoneKeyboard->setLineFeedButton(false);
                mpCandidateBox->setActive(false);
                mpCellPhoneKeyboard->setPredictLanguageButton(false);
                mpPCKeyboard->setPredictLanguageButton(false);
                mpCellPhoneKeyboard->setSignWindowButton(false);
                mpPCKeyboard->setSignWindowButton(false);
                mpInputForm->doWordWrap(false);
                mpInputForm->enableSpaceByRight(false);
                mpInputForm->dirtyCacheAll();
            }

            void Manager::configNumericWithDot() {
                configNumeric();
                meConfigType = CT_NumericWithDot;
                mpCellPhoneKeyboard->doNumericWithDotMode(true);
            }

            void Manager::configNumericBigTextWithDot() {
                configNumericWithDot();
                meConfigType = CT_NumericBigTextWithDot;
            }

            void Manager::configNormalBigTextWithoutLineFeedWithSign() {
                configDefault();
                mpInputForm = mpBigTextInputForm;
                textinput::Manager::init();
                meConfigType = CT_NormalBigTextWithoutLineFeedWithSign;

                mpCellPhoneKeyboard->setLineFeedButton(false);
                mpPCKeyboard->setLineFeedButton(false);
                mpCandidateBox->setActive(false);
                mpCellPhoneKeyboard->setPredictLanguageButton(false);
                mpPCKeyboard->setPredictLanguageButton(false);
                mpToolBar->enableKeytopChange(true);
                mpToolBar->setQwerty(true);
                mpCellPhoneKeyboard->setSignWindowButton(true);
                mpPCKeyboard->setSignWindowButton(true);
                mpInputForm->doWordWrap(false);
                mpInputForm->enableSpaceByRight(false);
                mpInputForm->dirtyCacheAll();
            }

            void Manager::configNormalWithoutLineFeedWithSign() {
                configDefault();
                textinput::Manager::init();
                meConfigType = CT_NormalBigTextWithoutLineFeedWithSign;

                mpCellPhoneKeyboard->setLineFeedButton(false);
                mpPCKeyboard->setLineFeedButton(false);
                mpCandidateBox->setActive(false);
                mpCellPhoneKeyboard->setPredictLanguageButton(false);
                mpPCKeyboard->setPredictLanguageButton(false);
                mpToolBar->enableKeytopChange(true);
                mpToolBar->setQwerty(true);
                mpCellPhoneKeyboard->setSignWindowButton(true);
                mpPCKeyboard->setSignWindowButton(true);
                mpInputForm->doWordWrap(false);
                mpInputForm->enableSpaceByRight(false);
                mpInputForm->dirtyCacheAll();
            }

            void Manager::configPredictWithoutLineFeed() {
                configDefault();
                meConfigType = CT_PredictWithoutLineFeed;

                mpCellPhoneKeyboard->setLineFeedButton(false);
                mpPCKeyboard->setLineFeedButton(false);
            }

            void Manager::configPredictBigText() {
                configPredictWithoutLineFeed();
                meConfigType = CT_PredictBigText;
                mpInputForm = mpBigTextInputForm;
                textinput::Manager::init();
            }

            void Manager::start() {
                if (meConfigType < CT_Numeric && meConfigType >= CT_Letter) {
                    ((memo::InputForm*)mpInputForm)->open();
                }
            }

            void Manager::end() {
                if (meConfigType < CT_Numeric && meConfigType >= CT_Letter) {
                    ((memo::InputForm*)mpInputForm)->close();
                }
            }

            void Manager::setSaveData() {
                savedata::MemoSetting* saveData = &mMemoSetting;

                saveData->uRevisionAndType  = mpToolBar->isQwerty() | 0x10;
                saveData->uDictionary       = mpInputForm->getPredictMode();
                saveData->uPredictOnOff     = mpCandidateBox->isOn();
                saveData->uSignPage         = mpSignWindow->getPage();
                saveData->uKeitaiUpperCaseJP = mpCellPhoneKeyboard->isUpperCase();
                saveData->uKeitaiInputMode  = mpCellPhoneKeyboard->getInputMode();
                saveData->uQwertyABC        = mpPCKeyboard->isABC();
                saveData->uReserve2         = 0;
                saveData->uABCInputMode     = mpPCKeyboard->mKeyState.mFlags;
                saveData->uAIUInputMode     = mpPCKeyboard->mKeyState.mAIUFlags;
                saveData->uNumLockOff       = !(input::HKBManager::getInstance().GetModifierState() & 0x100);
                saveData->uReserve3         = 0;
                saveData->uReserve4         = 0;
            }

            void Manager::reflectSaveData() {
                switch (mMemoSetting.uType) {
                    case 1:
                        reflectSaveDataRev1();
                        break;
                    case 0:
                    default:
                        reflectSaveDataDefault();
                        break;
                }
            }

            void Manager::reflectSaveDataRev1() {
                if ((mMemoSetting.uRevisionAndType & 1) == 1) {
                    mpToolBar->setQwerty(true);
                } else {
                    mpToolBar->setQwerty(false);
                }
                mpSignWindow->setPage(mMemoSetting.uSignPage);
                if (mMemoSetting.uPredictOnOff == 0) {
                    mpCandidateBox->turnOff();
                } else {
                    mpCandidateBox->turnOn();
                }
                if (mMemoSetting.uDictionary != 0xFA) {
                    mpInputForm->setPredictMode((inputform::Base::PredictMode)mMemoSetting.uDictionary);
                }
                if (meLanguage == JP) {
                    mpPCKeyboard->setInputModeJP(mMemoSetting.uQwertyABC != 0, mMemoSetting.uABCInputMode, mMemoSetting.uAIUInputMode);
                } else if (meLanguage == CN || meLanguage == KR) {
                    mpPCKeyboard->setInputModeCK(mMemoSetting.uABCInputMode);
                }
                mpCellPhoneKeyboard->setUpperCaseJP(mMemoSetting.uKeitaiUpperCaseJP != 0);
                mpCellPhoneKeyboard->setInputMode((keyboard::cellphonetype::Base::InputMode)mMemoSetting.uKeitaiInputMode);
                mpCandidateBox->checkValidation();
                input::HKBManager::getInstance().SetModifierState((mMemoSetting.uNumLockOff == 0) ? 0x100 : 0, 0x100);
            }

            void Manager::reflectSaveDataDefault() {
                mpToolBar->setQwerty(true);
                mpSignWindow->setPage(0);
                if (meLanguage == JP) {
                    mpCandidateBox->turnOn();
                } else {
                    mpCandidateBox->turnOff();
                }
                if (meLanguage == JP) {
                    mpPCKeyboard->setInputModeJP(false, 1, 0);
                } else if (meLanguage == CN || meLanguage == KR) {
                    mpPCKeyboard->setInputModeCK(1);
                }
                mpCellPhoneKeyboard->setUpperCaseJP(true);
                mpCellPhoneKeyboard->setInputMode((keyboard::cellphonetype::Base::InputMode)2);
                mpCandidateBox->checkValidation();
                input::HKBManager::getInstance().SetModifierState(0x100, 0x100);
            }

            void Manager::SetFont(nw4r::lyt::FontRefLink* fontLink) {
                textinput::Manager::SetFont(fontLink);

                nw4r::ut::Font* font = fontLink->GetFont();
                if (mpBigTextInputForm != NULL) {
                    ((nw4r::ut::CharWriter*)((char*)mpBigTextInputForm + 0x10))->SetFont(*font);
                }
                if (mpMemoInputForm != NULL) {
                    ((nw4r::ut::CharWriter*)((char*)mpMemoInputForm + 0x10))->SetFont(*font);
                }
                if (mpLetterInputForm != NULL) {
                    ((nw4r::ut::CharWriter*)((char*)mpLetterInputForm + 0x10))->SetFont(*font);
                }
            }

            void DispMemoState::create() {
            }

            void DispMemoState::init() {
                mpManager->getConfigType();
            }

            void DispMemoState::calc() {
                Manager::ConfigType configType = (Manager::ConfigType)mpManager->getConfigType();
                if (configType >= Manager::CT_Numeric || configType < Manager::CT_Letter) {
                    return;
                }
                InputForm()->calc();
            }

            InputForm* State::InputForm() {
                return (memo::InputForm*)mpManager->getInputForm();
            }

            void DispMemoState::draw() {
            }

            void DispMemoState::memoDraw() {
                if (mpManager->getConfigType() == Manager::CT_Letter || mpManager->getConfigType() == Manager::CT_PhotoLetter) {
                    InputForm()->draw();
                }
            }

            bool DispMemoState::updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release) {
                Manager::ConfigType configType = (Manager::ConfigType)mpManager->getConfigType();
                switch (configType) {
                case Manager::CT_Letter:
                case Manager::CT_PhotoLetter:
                    InputForm();
                    gui::GUIPointer point(chan, x, y, hold, trig, release);
                    return InputForm()->updateInput(chan, x, y, trig, hold, release, &point);
                default:
                    break;
                }
                return false;
            }

            bool DispMemoState::updateInput(input::HKBManager& hkbManager) {
                Manager::ConfigType configType = (Manager::ConfigType)mpManager->getConfigType();
                switch (configType) {
                case Manager::CT_Letter:
                case Manager::CT_PhotoLetter:
                    InputForm();
                    return InputForm()->updateInput(hkbManager);
                default:
                    break;
                }
                return false;
            }

            void DispMemoState::start() {
                Manager::ConfigType configType = (Manager::ConfigType)mpManager->getConfigType();
                switch (configType) {
                case Manager::CT_Letter:
                case Manager::CT_PhotoLetter:
                    InputForm()->setEditMode(memo::InputForm::EM_Disp);
                    InputForm()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, scMemoAnimParam[0]));
                    InputForm()->getLayout()->GetRootPane()->SetAlpha(0xff);
                    break;
                default:
                    InputForm()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, scPosAnimParam[0]));
                    InputForm()->getLayout()->GetRootPane()->SetAlpha((u8)scAlphaAnimParam[0]);
                    break;
                }
                PCKeyboard()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, scPosAnimParam[0]));
                CellPhoneKeyboard()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, scPosAnimParam[0]));
                CandidateBox()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, scPosAnimParam[0]));
                ToolBar()->getDownArea()->SetTranslate(nw4r::math::VEC2(0.0f, scPosAnimParam[0] / 3.0f));
                ToolBar()->getUpArea()->SetTranslate(nw4r::math::VEC2(0.0f, -scPosAnimParam[0] / 3.0f));
                BG()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, 0.0f));
                PCKeyboard()->getLayout()->GetRootPane()->SetAlpha((u8)scAlphaAnimParam[0]);
                CellPhoneKeyboard()->getLayout()->GetRootPane()->SetAlpha((u8)scAlphaAnimParam[0]);
                CandidateBox()->getLayout()->GetRootPane()->SetAlpha((u8)scAlphaAnimParam[0]);
                ToolBar()->getDownArea()->SetAlpha((u8)scAlphaAnimParam[0]);
                ToolBar()->getUpArea()->SetAlpha((u8)scAlphaAnimParam[0]);
                BG()->getLayout()->GetRootPane()->SetAlpha((u8)scAlphaAnimParam[0]);
            }

            keyboard::pctype::LayoutByNW4R* State::PCKeyboard() {
                return mpManager->getPCKeyboard();
            }

            keyboard::cellphonetype::LayoutByNW4R* State::CellPhoneKeyboard() {
                return mpManager->getCellPhoneKeyboard();
            }

            candidatebox::LayoutByNW4R* State::CandidateBox() {
                return mpManager->getCandidateBox();
            }

            toolbar::LayoutByNW4R* State::ToolBar() {
                return mpManager->getToolBar();
            }

            bg::LayoutByNW4R* State::BG() {
                return mpManager->mpBackGround;
            }

            void AppearMemoState::create() {
            }

            void AppearMemoState::init() {
            }

            void AppearMemoState::calc() {
                InputForm()->calc();

                if (ToolBar()->isQwerty()) {
                    PCKeyboard()->calc();
                } else {
                    CellPhoneKeyboard()->calc();
                }
                if (CandidateBox()->isActive()) {
                    CandidateBox()->calc();
                }
                ToolBar()->calc();
                BG()->calc();

                if (30.0f <= mfAnim) {
                    mpManager->changeState(Manager::STL_Transition);
                }

                f32 transY = util::hermiteInterporation(mfAnim, 0.0f, scPosAnimParam[0], 0.0f, 30.0f, scPosAnimParam[1], 0.0f);

                PCKeyboard()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, transY));
                CellPhoneKeyboard()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, transY));
                CandidateBox()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, transY));
                ToolBar()->getDownArea()->SetTranslate(nw4r::math::VEC2(0.0f, transY / 3.0f));
                ToolBar()->getUpArea()->SetTranslate(nw4r::math::VEC2(0.0f, -transY / 3.0f));
                BG()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, 0.0f));

                u8 alpha = (u8)util::hermiteInterporation(mfAnim, 0.0f, scAlphaAnimParam[0], 0.0f, 30.0f, scAlphaAnimParam[1], 0.0f);

                PCKeyboard()->getLayout()->GetRootPane()->SetAlpha(alpha);
                CellPhoneKeyboard()->getLayout()->GetRootPane()->SetAlpha(alpha);
                CandidateBox()->getLayout()->GetRootPane()->SetAlpha(alpha);
                ToolBar()->getDownArea()->SetAlpha(alpha);
                BG()->getLayout()->GetRootPane()->SetAlpha(alpha);

                Manager::ConfigType configType = (Manager::ConfigType)mpManager->getConfigType();
                switch (configType) {
                case Manager::CT_Letter:
                case Manager::CT_PhotoLetter: {
                    f32 transY2 = util::hermiteInterporation(mfAnim, 0.0f, scMemoAnimParam[0], 0.0f, 30.0f, scMemoAnimParam[1], 0.0f);
                    InputForm()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, transY2));
                    InputForm()->getLayout()->GetRootPane()->SetAlpha(0xff);
                    memo::InputForm* inputForm = InputForm();
                    inputForm->setScroll(util::hermiteInterporation(mfAnim, 0.0f, inputForm->getScrollFrom(), 0.0f, 30.0f, inputForm->getScrollTo(), 0.0f));
                    break;
                }
                default:
                    InputForm()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, transY));
                    InputForm()->getLayout()->GetRootPane()->SetAlpha(alpha);
                    break;
                }

                mfAnim += 1.0f;
            }

            void AppearMemoState::draw() {
                if (mpManager->getConfigType() != Manager::CT_Letter && mpManager->getConfigType() != Manager::CT_PhotoLetter) {
                    BG()->draw();
                }
                ToolBar()->draw();
                if (mpManager->getConfigType() != Manager::CT_Letter && mpManager->getConfigType() != Manager::CT_PhotoLetter) {
                    InputForm()->draw();
                }
                if (CandidateBox()->isActive()) {
                    CandidateBox()->draw();
                }
                if (ToolBar()->isQwerty()) {
                    PCKeyboard()->draw();
                } else {
                    CellPhoneKeyboard()->draw();
                }
            }

            void bg::LayoutByNW4R::draw() {
                nw4rmanager::Layout::draw();
            }

            void AppearMemoState::memoDraw() {
                if (mpManager->getConfigType() == Manager::CT_Letter || mpManager->getConfigType() == Manager::CT_PhotoLetter) {
                    InputForm()->draw();
                }
            }

            bool AppearMemoState::updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release) {
                return false;
            }

            bool AppearMemoState::updateInput(input::HKBManager& hkbManager) {
                return false;
            }

            void AppearMemoState::start() {
                mfAnim = 0.0f;
                Manager::ConfigType configType = (Manager::ConfigType)mpManager->getConfigType();
                if (configType >= Manager::CT_Numeric || configType < Manager::CT_Letter) {
                    return;
                }
                InputForm()->setEditMode(memo::InputForm::EM_Appear);
            }

            void EditMemoState::create() {
            }

            void EditMemoState::init() {
            }

            void EditMemoState::calc() {
                if (ToolBar()->isQwerty()) {
                    PCKeyboard()->calc();
                } else {
                    CellPhoneKeyboard()->calc();
                }
                ToolBar()->calc();
                if (CandidateBox()->isActive()) {
                    CandidateBox()->calc();
                }
                InputForm()->calc();
                if (PredictLanguageSelectDialog()->isActive()) {
                    PredictLanguageSelectDialog()->calc();
                }
                if (SignKeyboard()->isActive()) {
                    SignKeyboard()->calc();
                }
                if (mpManager->getConfigType() != Manager::CT_Letter && mpManager->getConfigType() != Manager::CT_PhotoLetter) {
                    BG()->calc();
                }
            }

            predictlang::LayoutByNW4R* State::PredictLanguageSelectDialog() {
                return (predictlang::LayoutByNW4R*)mpManager->getPredictLanguageSelectDialog();
            }

            keyboard::signwindow::LayoutByNW4R* State::SignKeyboard() {
                return (keyboard::signwindow::LayoutByNW4R*)mpManager->getSignKeyboard();
            }

            void EditMemoState::draw() {
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);

                if (mpManager->getConfigType() != Manager::CT_Letter && mpManager->getConfigType() != Manager::CT_PhotoLetter) {
                    BG()->draw();
                }
                ToolBar()->draw();
                if (mpManager->getConfigType() != Manager::CT_Letter && mpManager->getConfigType() != Manager::CT_PhotoLetter) {
                    InputForm()->draw();
                }
                if (CandidateBox()->isActive()) {
                    CandidateBox()->draw();
                }
                if (ToolBar()->isQwerty()) {
                    PCKeyboard()->draw();
                } else {
                    CellPhoneKeyboard()->draw();
                }
                if (PredictLanguageSelectDialog()->isActive()) {
                    PredictLanguageSelectDialog()->draw();
                }
                if (SignKeyboard()->isActive()) {
                    SignKeyboard()->draw();
                }
            }

            void EditMemoState::memoDraw() {
                if (mpManager->getConfigType() == Manager::CT_Letter || mpManager->getConfigType() == Manager::CT_PhotoLetter) {
                    InputForm()->draw();
                }
            }

            bool EditMemoState::updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release) {
                bool qwerty = ToolBar()->isQwerty();
                gui::GUIPointer point(chan, x, y, hold, trig, release);

                HWKeyboard()->updateInput(chan, x, y, trig, hold, release, &point);

                if (PredictLanguageSelectDialog()->isActive()) {
                    return PredictLanguageSelectDialog()->updateInput(chan, x, y, trig, hold, release, &point);
                }

                InputForm()->updateInputCommon(chan, trig, hold, release, &point);

                if (SignKeyboard()->isActive()) {
                    return SignKeyboard()->updateInput(chan, x, y, trig, hold, release, &point);
                }

                bool keyUpdate;
                if (qwerty) {
                    keyUpdate = PCKeyboard()->updateInput(chan, x, y, trig, hold, release, &point);
                } else {
                    keyUpdate = CellPhoneKeyboard()->updateInput(chan, x, y, trig, hold, release, &point);
                }

                bool toolUpdate = ToolBar()->updateInput(chan, x, y, trig, hold, release, &point);

                bool ret;
                bool candUpdate = false;
                if (CandidateBox()->isActive()) {
                    candUpdate = CandidateBox()->updateInput(chan, x, y, trig, hold, release, &point);
                }

                bool formUpdate = false;
                if (!candUpdate) {
                    formUpdate = InputForm()->updateInput(chan, x, y, trig, hold, release, &point);
                } else {
                    InputForm()->updateInput(chan, 1.0f / 0.0f, 1.0f / 0.0f, trig, hold, release, &point);
                }

                ret = toolUpdate | candUpdate | formUpdate | keyUpdate;

                if (qwerty != ToolBar()->isQwerty()) {
                    InputForm()->onCommand(CommandReceiver::IC_TRANSLATE_MODE, NULL);
                    CandidateBox()->checkValidation();
                    if (ToolBar()->isQwerty()) {
                        PCKeyboard()->onActive();
                    } else {
                        CellPhoneKeyboard()->onActive();
                    }
                }

                return ret;
            }

            keyboard::hwkey::HWKeyboard* State::HWKeyboard() {
                return mpManager->getHWKeyboard();
            }

            bool EditMemoState::updateInput(input::HKBManager& hkbManager) {
                bool qwerty = ToolBar()->isQwerty();

                if (PredictLanguageSelectDialog()->isActive()) {
                    return false;
                }

                HWKeyboard()->updateInput(hkbManager);

                if (SignKeyboard()->isActive()) {
                    return SignKeyboard()->updateInput(hkbManager);
                }

                bool keyUpdate;
                if (qwerty) {
                    keyUpdate = PCKeyboard()->updateInput(hkbManager);
                } else {
                    keyUpdate = CellPhoneKeyboard()->updateInput(hkbManager);
                }

                if (qwerty != ToolBar()->isQwerty()) {
                    InputForm()->onCommand(CommandReceiver::IC_TRANSLATE_MODE, NULL);
                    CandidateBox()->checkValidation();
                    if (ToolBar()->isQwerty()) {
                        PCKeyboard()->onActive();
                    } else {
                        CellPhoneKeyboard()->onActive();
                    }
                }

                return keyUpdate;
            }

            void EditMemoState::start() {
                if (mpManager->getConfigType() == Manager::CT_Letter || mpManager->getConfigType() == Manager::CT_PhotoLetter) {
                    InputForm()->setEditMode(memo::InputForm::EM_Edit);
                    InputForm()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, scMemoAnimParam[1]));
                    InputForm()->getLayout()->GetRootPane()->SetAlpha(0xff);
                } else {
                    InputForm()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, scPosAnimParam[1]));
                    InputForm()->getLayout()->GetRootPane()->SetAlpha((u8)scAlphaAnimParam[1]);
                }
                PCKeyboard()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, scPosAnimParam[1]));
                CellPhoneKeyboard()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, scPosAnimParam[1]));
                CandidateBox()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, scPosAnimParam[1]));
                ToolBar()->getDownArea()->SetTranslate(nw4r::math::VEC2(0.0f, scPosAnimParam[1] / 3.0f));
                ToolBar()->getUpArea()->SetTranslate(nw4r::math::VEC2(0.0f, -scPosAnimParam[1] / 3.0f));
                BG()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, 0.0f));
                PCKeyboard()->getLayout()->GetRootPane()->SetAlpha((u8)scAlphaAnimParam[1]);
                CellPhoneKeyboard()->getLayout()->GetRootPane()->SetAlpha((u8)scAlphaAnimParam[1]);
                CandidateBox()->getLayout()->GetRootPane()->SetAlpha((u8)scAlphaAnimParam[1]);
                ToolBar()->getDownArea()->SetAlpha((u8)scAlphaAnimParam[1]);
                ToolBar()->getUpArea()->SetAlpha((u8)scAlphaAnimParam[1]);
                BG()->getLayout()->GetRootPane()->SetAlpha((u8)scAlphaAnimParam[1]);
                PCKeyboard()->onActive();
                CellPhoneKeyboard()->onActive();
                if (ToolBar()->isQwerty()) {
                    PCKeyboard()->onActive();
                } else {
                    CellPhoneKeyboard()->onActive();
                }
            }

            void DisappearMemoState::calc() {
                if (30.0f <= mfAnim) {
                    mpManager->changeState(Manager::STL_Transition);
                }

                InputForm()->calc();

                f32 transY = util::hermiteInterporation(mfAnim, 0.0f, scPosAnimParam[1], 0.0f, 30.0f, scPosAnimParam[0], 0.0f);

                PCKeyboard()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, transY));
                CellPhoneKeyboard()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, transY));
                CandidateBox()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, transY));
                ToolBar()->getDownArea()->SetTranslate(nw4r::math::VEC2(0.0f, transY / 3.0f));
                ToolBar()->getUpArea()->SetTranslate(nw4r::math::VEC2(0.0f, -transY / 3.0f));
                BG()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, 0.0f));

                u8 alpha = (u8)util::hermiteInterporation(mfAnim, 0.0f, scAlphaAnimParam[1], 0.0f, 30.0f, scAlphaAnimParam[0], 0.0f);

                PCKeyboard()->getLayout()->GetRootPane()->SetAlpha(alpha);
                CellPhoneKeyboard()->getLayout()->GetRootPane()->SetAlpha(alpha);
                CandidateBox()->getLayout()->GetRootPane()->SetAlpha(alpha);
                ToolBar()->getDownArea()->SetAlpha(alpha);
                ToolBar()->getUpArea()->SetAlpha(alpha);
                BG()->getLayout()->GetRootPane()->SetAlpha(alpha);

                Manager::ConfigType configType = (Manager::ConfigType)mpManager->getConfigType();
                switch (configType) {
                case Manager::CT_Letter:
                case Manager::CT_PhotoLetter: {
                    f32 transY2 = util::hermiteInterporation(mfAnim, 0.0f, scMemoAnimParam[1], 0.0f, 30.0f, scMemoAnimParam[0], 0.0f);
                    InputForm()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, transY2));
                    InputForm()->getLayout()->GetRootPane()->SetAlpha(0xff);
                    break;
                }
                default:
                    InputForm()->getLayout()->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, transY));
                    InputForm()->getLayout()->GetRootPane()->SetAlpha(alpha);
                    break;
                }

                mfAnim += 1.0f;
            }

            void DisappearMemoState::start() {
                mfAnim = 0.0f;
                Manager::ConfigType configType = (Manager::ConfigType)mpManager->getConfigType();
                switch (configType) {
                case Manager::CT_Letter:
                case Manager::CT_PhotoLetter:
                    InputForm()->setEditMode(memo::InputForm::EM_Disappear);
                    mpManager->setSaveData();
                    break;
                default:
                    InputForm()->onClose();
                    break;
                }
            }

            void AppearMemoState::end() {
            }

            Manager::StateType DisappearMemoState::getStateType() {
                return Manager::ST_Disappearing;
            }

            void EditMemoState::end() {
            }

            Manager::StateType EditMemoState::getStateType() {
                return Manager::ST_Visible;
            }

            AppearMemoState::~AppearMemoState() {
            }

            State::~State() {
            }

            Manager::StateType AppearMemoState::getStateType() {
                return Manager::ST_Appearing;
            }

            void DispMemoState::end() {
            }

            Manager::StateType DispMemoState::getStateType() {
                return Manager::ST_Hidden;
            }

        }

        namespace bg {
            void Base::init() {
            }

            void Base::create(MEMAllocator* allocator) {
            }
        }

        namespace memo {
            DispMemoState::~DispMemoState() {
            }

            EditMemoState::~EditMemoState() {
            }

        }
    }

}