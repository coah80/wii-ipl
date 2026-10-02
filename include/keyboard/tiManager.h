#ifndef TEXTINPUT_MANAGER_H
#define TEXTINPUT_MANAGER_H

#include "tiTextInputBase.h"
#include "tiInputForm.h"
#include "tiSaveData.h"
#include "tiHKBManager.h"
#include "tiHWKeyboard.h"
#include "tiToolBar.h"
#include "tiPcKeyboard.h"
#include "tiCellPhone.h"

#include <nw4r/lyt/pane.h>
#include <nw4r/lyt/arcResourceAccessor.h>

#include <revolution/types.h>
#include <revolution/mem/allocator.h>

#include <stdio.h>

#include "tiSEId.h"

namespace textinput {
    class EventObserver {
        public:
            virtual void    onInput(CommandReceiver::INPUT_COMMAND command, void* data);      // 0x08
            virtual void    onCommand(CommandReceiver::INPUT_COMMAND command, void* data);    // 0x0C
            virtual void    onEvent(nw4r::lyt::Pane* pane, u32 event);                        // 0x10

            virtual void    onSE(sound::SE seId);
            virtual void onOK();
            virtual void onCancel();
            virtual void onOutOfLength();
    };
    
#ifdef TIMANAGER_IMPLEMENTATION
    namespace predictlang { class LayoutByNW4R; }
#endif
    class Manager : public Base {
        public:
            Manager(MEMAllocator* allocator, nw4r::lyt::MultiArcResourceAccessor* multiArc, textinput::EventObserver* event);
            virtual ~Manager();

            virtual void                                create(MEMAllocator* allocator);

            virtual void                                init();

            virtual void                                calc();

            virtual void                                draw();

            virtual bool                                updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release);
            virtual bool                                updateInput(input::HKBManager& hkbManager);

            virtual void                                SetFont(nw4r::lyt::FontRefLink* fontLink);

            virtual wchar_t*                            getWCString() const;
            virtual void                                setWCString(const wchar_t* string);

            virtual void                                setLanguage(Language language);
            virtual Language                            getLanguage() const;
#ifdef MYTIMANAGER_IMPLEMENTATION
            Language                                    getLanguageForMemo() const { return meLanguage; }
#endif

            virtual void                                setDestination(Destination destination);

            virtual void                                limitStringLength(u32 limitStringLength);
            virtual void                                limitRowNum(u32 limitRowNum);

            virtual void                                setAnimationOn(bool flag);
            
            virtual void                                setAspectRatio(bool b4x3);

#ifdef MYTIMANAGER_IMPLEMENTATION
            MEMAllocator* getAllocatorForMemo() const { return mpAllocator; }
            inputform::EditBuffer* getEditBufferForMemo() const { return mpEditBuffer; }
            void setEditBufferForMemo(inputform::EditBuffer* editBuffer) { mpEditBuffer = editBuffer; }
            void setHWKeyboardForMemo(keyboard::hwkey::HWKeyboard* keyboard) { mpHWKeyboard = keyboard; }
            nw4r::lyt::MultiArcResourceAccessor* getMultiArcForMemo() const { return mpMultiArcResourceAccessor; }
            EventObserver* getEventObserverForMemo() const { return mpEventObserver; }
            InputForm* getInputFormForMemo() const { return mpInputForm; }
            void setInputFormForMemo(InputForm* inputForm) { mpInputForm = inputForm; }
            toolbar::LayoutByNW4R* getToolBarForMemo() const { return mpToolBar; }
            candidatebox::LayoutByNW4R* getCandidateBoxForMemo() const { return mpCandidateBox; }
            void setPCKeyboardForMemo(keyboard::pctype::LayoutByNW4R* keyboard) { mpPCKeyboard = keyboard; }
            void setCellPhoneKeyboardForMemo(keyboard::cellphonetype::LayoutByNW4R* keyboard) { mpCellPhoneKeyboard = keyboard; }
            void setCandidateBoxForMemo(candidatebox::LayoutByNW4R* candidateBox) { mpCandidateBox = candidateBox; }
            void setToolBarForMemo(toolbar::LayoutByNW4R* toolBar) { mpToolBar = toolBar; }
            void setPredictLanguageDialogForMemo(void* dialog) { mpPredictLanguageDialog = dialog; }
            void setSignWindowForMemo(void* signWindow) { mpSignWindow = signWindow; }
            void* getSignWindowForMemo() const { return mpSignWindow; }
            keyboard::pctype::LayoutByNW4R* getPCKeyboardForMemo() const { return mpPCKeyboard; }
            keyboard::cellphonetype::LayoutByNW4R* getCellPhoneKeyboardForMemo() const { return mpCellPhoneKeyboard; }
            Destination getDestinationForMemo() const { return meDestination; }
            void initAspect();
#endif

            virtual void                                setSecretInputMode(bool secretInputMode) { mpInputForm->setSecretModeOn(secretInputMode); }
#if defined(IPL_ADDRESS_EDIT_CPP) || defined(TIMANAGER_IMPLEMENTATION)
            void enableKSXFilter(bool compatibleFilter);
#endif

            virtual void                                setDefaultPredictionJP(int num, const char** predicts);
            virtual void                                setFixedPredictionJP(int num, const char** predicts);

#ifdef TIMANAGER_IMPLEMENTATION
            virtual void setTitleText(wchar_t* titleText);
            void initAspect();
#elif defined(MYTIMANAGER_IMPLEMENTATION)
            virtual void setTitleText(wchar_t* titleText);
#else
            virtual void                                setTitleText(const wchar_t* titleText);
#endif

            virtual void                                start() {}
            virtual void                                end()   {}

#ifdef TIHWKEYBOARD_IMPLEMENTATION
            EventObserver* getEventObserverForHardware() const { return mpEventObserver; }
#endif
            virtual InputForm*                          getInputForm();
            virtual const InputForm*                    getInputForm() const;
            
            virtual keyboard::hwkey::HWKeyboard*        getHWKeyboard();
            virtual const keyboard::hwkey::HWKeyboard*  getHWKeyboard() const;
            
            virtual keyboard::pctype::LayoutByNW4R*       getPCKeyboard();
            virtual const keyboard::pctype::LayoutByNW4R* getPCKeyboard() const;
            
            virtual keyboard::cellphonetype::LayoutByNW4R*       getCellPhoneKeyboard();
            virtual const keyboard::cellphonetype::LayoutByNW4R* getCellPhoneKeyboard() const;
            
            virtual void*                               getSignKeyboard();
            virtual const void*                         getSignKeyboard() const;
            
            virtual candidatebox::LayoutByNW4R*         getCandidateBox();
            virtual const candidatebox::LayoutByNW4R*   getCandidateBox() const;
            
            virtual toolbar::LayoutByNW4R*              getToolBar();
            virtual const toolbar::LayoutByNW4R*        getToolBar() const;
            
            virtual void*                               getPredictLanguageSelectDialog();
            virtual const void*                         getPredictLanguageSelectDialog() const;

            virtual inputform::EditBuffer*              createEditBuffer();
            virtual keyboard::hwkey::HWKeyboard*        createHWKeyboard();
            virtual void*                               createPCTypeKeyboard();
            virtual void*                               createCellPhoneTypeKeyboard();
            virtual InputForm*                          createInputForm();
            virtual void*                               createCandidateBox();
            virtual void*                               createToolBar();
            virtual void*                               createPredictLanguageDialog();
            virtual void*                               createSignWindow();

            virtual void                                setLayoutScaleFor16x9();
            virtual void                                setLayoutScaleFor4x3();

            void                                        enableCompatibleFilter(bool compatibleFilter);

            bool                                        isVacancy() const;
#if defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
            bool isPredictTurning() const;
            void startPredictTurnOn(bool enabled);
#endif

        private:
            MEMAllocator*                           mpAllocator;                // 0x04
            nw4r::lyt::MultiArcResourceAccessor*    mpMultiArcResourceAccessor; // 0x08

            inputform::EditBuffer*                  mpEditBuffer;               // 0x0C

            keyboard::hwkey::HWKeyboard*            mpHWKeyboard;               // 0x10
            keyboard::pctype::LayoutByNW4R*         mpPCKeyboard;               // 0x14
            keyboard::cellphonetype::LayoutByNW4R*  mpCellPhoneKeyboard;        // 0x18
            InputForm*                              mpInputForm;                // 0x1C
            candidatebox::LayoutByNW4R*             mpCandidateBox;             // 0x20
            toolbar::LayoutByNW4R*                  mpToolBar;                  // 0x24
#ifdef TIMANAGER_IMPLEMENTATION
            predictlang::LayoutByNW4R* mpPredictLanguageDialog;
            keyboard::signwindow::LayoutByNW4R* mpSignWindow;
#else
            void*                                   mpPredictLanguageDialog;    // 0x28
            void*                                   mpSignWindow;               // 0x2C

#endif
            EventObserver*                          mpEventObserver;            // 0x30

            Destination                             meDestination;              // 0x34
            Language                                meLanguage;                 // 0x38

            bool                                    mbAspectRatio4x3;           // 0x3C
    };
}

#endif // TEXTINPUT_MANAGER_H
