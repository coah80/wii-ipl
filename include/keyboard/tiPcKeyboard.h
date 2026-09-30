#ifndef TEXTINPUT_PC_KEYBOARD_H
#define TEXTINPUT_PC_KEYBOARD_H

#if defined(TI_PC_KEYBOARD_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION) || defined(TISIGNWINDOW_IMPLEMENTATION)
#include "tiPcKeyboardImpl.h"
#else

#include "tiNw4rManager.h"
#include "tiTextInputBase.h"
#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION)
#include "tiKeyboard.h"
#endif

namespace textinput {
    class Manager;

    namespace keyboard {

        namespace pctype {

#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION)
            class UIObj {
            public:
                class Listener {
                public:
                    virtual void onEvent(UIObj*, u32, void*);
                };
            };
#endif

            // TODO
#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION)
            class Base : public textinput::keyboard::KeyboardBase {
#else
            class Base : public CommandSender {
#endif
            public:
                enum TranslateMode {
                    TM_00,
#ifdef TIINPUTFORM_IMPLEMENTATION
                    TM_Kana,
                    TM_Roman,
#endif
                };

                enum InputType {
                    IT_00,
                    IT_01,
                    IT_02,
                    IT_03,
                    IT_04,
                };

#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION)
                enum InputMode {
                    IM_00,
                    IM_01,
                    IM_02,
                    IM_03,
                    IM_04,
                };

                virtual ~Base();
                virtual void create(MEMAllocator* allocator) override;
                virtual void init() override;
                virtual void updateFromReceiver(u32, void*) override;
                virtual void onKey(u32, void*) override;
                virtual void getType() override;
                virtual void setLanguage(Language) override;
                virtual void onActive() override;
                virtual void inputCharCode(u16);
                virtual void getState();
                virtual bool isShiftOn() const;
                virtual bool isCapsOn() const;
                virtual bool isABC();
                virtual void setABC(bool);
                virtual InputMode getABCInputMode() const;
                virtual InputMode getAIUInputMode() const;
                virtual TranslateMode getTranslateMode() const;
                virtual void setTranslateMode(TranslateMode);
                virtual void onlyQwerty(bool);
                virtual void setLangKeyActive(bool);
                virtual void setInputModeJP(bool, u32, u32);
                virtual void setInputModeCK(u32);
                virtual void refreshState();
                virtual void changeABCInputMode(InputMode);
                virtual void changeAIUInputMode(InputMode);
                virtual void onClose();
                virtual void getWCCode(char*);
                virtual void getControlKey(char*);
                virtual void sendInputWChar(u16, bool);
                virtual void goSignInputMode();
                virtual void changePredictLanguage();
                virtual void updateFixMode();
#else
                virtual ~Base();
                virtual void create(MEMAllocator* allocator);
                virtual void init();
                virtual void setCommandReceiver(textinput::CommandReceiver*);
                virtual void updateFromReceiver(u32, void*);
                virtual void onKey();
                virtual void getType();
                virtual void setLanguage();
                virtual void getLanguage();
                virtual void update();
                virtual void onActive();
                virtual void inputCharCode();
                virtual void getState();
                virtual void isShiftOn();
                virtual void isCapsOn();
                virtual void isABC();
                virtual void setABC();
                virtual void getABCInputMode();
                virtual void getAIUInputMode();
                virtual TranslateMode getTranslateMode();
                virtual void setTranslateMode(TranslateMode);
                virtual void onlyQwerty();
                virtual void setLangKeyActive(bool);
                virtual void setInputModeJP();
                virtual void setInputModeCK();
                virtual void refreshState();
                virtual void changeABCInputMode();
                virtual void changeAIUInputMode();
                virtual void onClose();
                virtual void getWCCode();
                virtual void getControlKey();
                virtual void sendInputWChar();
                virtual void goSignInputMode();
                virtual void changePredictLanguage();
                virtual void updateFixMode();
#endif

#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION)
            private:
                u8 mKeyboardInputFlags[8];
                const void* mpKeyStateTable;
                u32 mTranslateMode;
                u32 mABCInputMode;
                u32 mAIUInputMode;
                u32 mCurrentInputType;
                u32 mInputState;
                const void* mpLanguageData;
#ifdef TIINPUTFORM_IMPLEMENTATION
                MEMAllocator* mpAllocator;
#endif
                bool mbOnlyQwerty;
                bool mbLanguageKeyActive;
                u16 mKeyboardFlags;
                void* mpInputSettings;
                void* mpCurrentKeyState;

            public:
#ifdef TIINPUTFORM_IMPLEMENTATION
                bool isQwertyOnly() const { return mbOnlyQwerty; }
                bool isLanguageKeyActive() const { return mbLanguageKeyActive; }
#endif
                u32 getTranslateModeForMemo() const { return mTranslateMode; }
                u32 getABCInputModeForMemo() const { return mABCInputMode; }
                u32 getAIUInputModeForMemo() const { return mAIUInputMode; }
#endif
            };

            // TODO
            class LayoutByNW4R : public Base, public nw4rmanager::Layout
#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION)
                                , public UIObj::Listener
#endif
            {
            public:
                // TODO - ...

#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION)
                virtual void draw();
                virtual void calc();
                virtual void setPredictLanguageDialog(void*);
                virtual void setSignWindow(void*);
                virtual void setLineFeedButton(bool);
                virtual void setPredictLanguageButton(bool);
                virtual void setSignWindowButton(bool);
#endif
                virtual void onClose();

                void onPressedShift(bool shift);
                void onReleasedShift();
#ifdef TIINPUTFORM_IMPLEMENTATION
                bool hasLineFeedButton() const { return mbLineFeedButton; }
            private:
                void* mpPredictLanguageDialog;
                void* mpSignWindow;
                bool mbLineFeedButton;
            public:
#endif
#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION)
                virtual bool updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release, void* data) override;
                virtual bool updateInput(input::HKBManager& hkbManager) override;
#endif
            };

        }  // namespace pctype

    }  // namespace keyboard

}  // namespace textinput

#endif
#endif  // TEXTINPUT_HW_KEYBOARD_H
