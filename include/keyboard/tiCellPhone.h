#ifndef TEXTINPUT_CELL_PHONE_H
#define TEXTINPUT_CELL_PHONE_H

#include "tiNw4rManager.h"
#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIHWKEYBOARD_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
#include "tiKeyboard.h"
#endif

#ifdef TI_CELLPHONE_IMPLEMENTATION
#include <revolution/gx.h>
#endif

namespace textinput {
    class Manager;
#ifdef TI_CELLPHONE_SAMPLE_CLASS
    class EventObserver;
#endif
    namespace predictlang {
        class LayoutByNW4R;
    }
    namespace keyboard {
#ifdef TI_CELLPHONE_IMPLEMENTATION
        enum VKeyCode {
            VK_LINE_FEED = 0,
            VK_DELETE = 1,
            VK_SIGN_INPUT = 9,
            VK_PREDICT_LANGUAGE = 10,
            VK_INPUT_MODE_02 = 11,
            VK_INPUT_MODE_03 = 13,
            VK_INPUT_MODE_00 = 18,
            VK_INPUT_MODE_01 = 19,
            VK_TOGGLE_ABC_MODE = 23,
        };
#endif
        namespace signwindow {
            class LayoutByNW4R;
        }
    }

    namespace keyboard {
        namespace cellphonetype {
            class EventHandler;
#ifdef TI_CELLPHONE_IMPLEMENTATION
            class CellPhoneAnmPane;
            struct PaneNameToCharCode;
#endif
#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIHWKEYBOARD_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
            class Base : public textinput::keyboard::KeyboardBase {
#else
            class Base {
#endif
            public:
#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIHWKEYBOARD_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
#if defined(MYTIMANAGER_IMPLEMENTATION) && defined(TI_CELLPHONE_SAMPLE_CLASS)
                Base(Manager* manager) : mPreviousInputMode(0), mCurrentInputMode(0), mpManager(manager) {}
#endif
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
#ifdef TIMANAGER_IMPLEMENTATION
                Base(Manager* manager) : mpManager(manager) {}
#endif
#if defined(TI_CELLPHONE_IMPLEMENTATION)
                virtual u32 getType() override;
#elif defined(TI_PC_KEYBOARD_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION) || defined(TISIGNWINDOW_IMPLEMENTATION)
                virtual int getType() override;
#elif defined(TIHWKEYBOARD_IMPLEMENTATION)
                virtual int getType() override;
#else
                virtual void getType() override;
#endif
                virtual void onActive() override;
                virtual void calc();
                virtual void draw();
                virtual InputMode getInputMode() const;
                virtual bool isLocked() const;
                virtual bool isNumeric() const;
                virtual bool isNumericWithDot() const;
                virtual bool isHoldingButton() const;
                virtual void doNumericMode(bool);
                virtual void changeInputMode(InputMode);
                virtual bool isUpperCase();
                virtual void setInputMode(InputMode);
                virtual void setUpperCaseJP(bool);
                virtual void setLangKeyActive(bool);
                virtual bool onClose();
                virtual void goSignInputMode();
                virtual void changePredictLanguage();
                virtual void setAbcMode(bool);
                virtual bool isZiActive();
                virtual bool isAtokActive();
                virtual void doInput();
                virtual void updateFixMode();
#ifdef TI_CELLPHONE_IMPLEMENTATION
                wchar_t convertToZiCellphoneInput_(wchar_t value);
#endif
#else
                virtual void vt_0x08();
                virtual void vt_0x0C();
                virtual void vt_0x10();
                virtual void vt_0x14();
                virtual void vt_0x18();
                virtual void vt_0x1C();
                virtual void vt_0x20();
                virtual void vt_0x24();
                virtual void vt_0x28();
                virtual void vt_0x2C();
                virtual void vt_0x30();
                virtual void vt_0x34();
                virtual void vt_0x38();
                virtual void vt_0x3C();
                virtual void vt_0x40();
                virtual void vt_0x44();

                virtual bool isNumeric() const;

                virtual void vt_0x4C();
                virtual void vt_0x50();
#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIHWKEYBOARD_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
                virtual void doNumericMode(bool);
#else
                virtual void vt_0x54();
#endif
                virtual void vt_0x58();
                virtual void vt_0x5C();
                virtual void vt_0x60();
                virtual void vt_0x64();
                virtual void vt_0x68(bool);

                virtual bool onClose();
#endif

                // TODO enum?
                int getInputType() const;
#if defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIHWKEYBOARD_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
                void resetHoldingButton();
#endif

#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIHWKEYBOARD_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
#if defined(MYTIMANAGER_IMPLEMENTATION) && defined(TI_CELLPHONE_IMPLEMENTATION)
            protected:
#else
            private:
#endif
                u32 mPreviousInputMode;
                u32 mCurrentInputMode;
                bool mbInputModeLocked;
                bool mbNumericMode;
                bool mbNumericWithDotMode;
                bool mbUpperCaseMode;
                bool mbAbcMode;
                bool mbLanguageKeyMode;
#ifdef TI_CELLPHONE_IMPLEMENTATION
                const PaneNameToCharCode* mHoldingButton;
#else
                u32 mHoldingButton;
#endif
                void* mpInputModeTable;
                MEMAllocator* mpAllocator;
#ifdef TI_CELLPHONE_IMPLEMENTATION
                Manager* mpManager;
                bool mInputState;
#elif defined(TIMANAGER_IMPLEMENTATION)
                Manager* mpManager;
                u32 mInputState;
#else
                void* mpInputSettings;
                u32 mInputState;
#endif
#ifdef TI_CELLPHONE_IMPLEMENTATION
                void onCtrlKey_(VKeyCode keyCode);
#endif
#endif
            };

            class LayoutByNW4R : public Base, public nw4rmanager::Layout {
            public:
#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIHWKEYBOARD_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
#ifdef TIMANAGER_IMPLEMENTATION
                LayoutByNW4R(Manager* manager, nw4r::lyt::MultiArcResourceAccessor* accessor, EventObserver* observer, const char* layoutName)
                    : Base(manager), nw4rmanager::Layout(accessor, layoutName, observer), mpEventHandler(NULL) {}
                virtual ~LayoutByNW4R();
                virtual void create(MEMAllocator* allocator);
                virtual void init();
                virtual void setCommandReceiver(CommandReceiver* receiver);
                virtual void updateFromReceiver(u32 command, void* data);
                virtual void onKey(u32 event, void* data);
                virtual void setLanguage(Language language);
                virtual void update();
                virtual void onActive();
                virtual void calc();
                virtual void draw();
                virtual void changeInputMode(InputMode mode);
                virtual void setInputMode(InputMode mode);
                virtual void setUpperCaseJP(bool upper);
                virtual void setLangKeyActive(bool active);
                virtual void goSignInputMode();
                virtual void changePredictLanguage();
                virtual void setAbcMode(bool abc);
                virtual void doNumericMode(bool);
                virtual void setPredictLanguageDialog(predictlang::LayoutByNW4R* dialog);
                virtual void setSignWindow(signwindow::LayoutByNW4R* window);
#else
#if defined(MYTIMANAGER_IMPLEMENTATION) && defined(TI_CELLPHONE_SAMPLE_CLASS)
                LayoutByNW4R(Manager* manager, nw4r::lyt::MultiArcResourceAccessor* resAccessor, EventObserver* observer)
                    : Base(manager), nw4rmanager::Layout(resAccessor, "fs_VK_cellPhone_a.brlyt", observer), mpSignWindow(NULL) {}
#endif
                virtual void doNumericMode(bool);
#ifdef TI_CELLPHONE_IMPLEMENTATION
                virtual void setPredictLanguageDialog(predictlang::LayoutByNW4R*);
                virtual void setSignWindow(signwindow::LayoutByNW4R*);
#else
                virtual void setPredictLanguageDialog(void*);
                virtual void setSignWindow(void*);
#endif
#endif
                virtual void doNumericWithDotMode(bool);
                virtual void setLineFeedButton(bool);
                virtual void setPredictLanguageButton(bool);
                virtual void setSignWindowButton(bool);
#endif
                virtual bool onClose();

                void onPressedShift(bool shift);
                void onReleasedShift();
#if defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIHWKEYBOARD_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
                bool hasLineFeedButton() const { return mbLineFeedButton; }
            private:
                bool mbLineFeedButton;
#ifdef TIMANAGER_IMPLEMENTATION
                GXTexObj mSpaceTexture;
                GXTexObj mSpaceTextureCN;
                GXTexObj mSpaceTextureKR;
                nw4rmanager::TiEventHandler* mpEventHandler;
                predictlang::LayoutByNW4R* mpPredictDialog;
                signwindow::LayoutByNW4R* mpSignWindow;
#endif
            public:
#endif
#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIHWKEYBOARD_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
                virtual bool updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release, void* data) override;
                virtual bool updateInput(input::HKBManager& hkbManager) override;
#endif
#ifdef TI_CELLPHONE_IMPLEMENTATION
                virtual ~LayoutByNW4R();
                virtual void create(MEMAllocator* allocator) override;
                virtual void init() override;
                virtual void draw() override;
                virtual void calc() override;
                virtual void update() override;
                virtual void onKey(u32 key, void* data) override;
                virtual void onActive() override;
                virtual void updateFromReceiver(u32 command, void* data) override;
                virtual void changeInputMode(InputMode mode) override;
                virtual void changePredictLanguage() override;
                virtual void setAbcMode(bool enabled) override;
                virtual void goSignInputMode() override;
                virtual void setInputMode(InputMode mode) override;
                virtual void setLanguage(Language language) override;
                virtual void setCommandReceiver(CommandReceiver* receiver) override;

                virtual CellPhoneAnmPane* getAnmPane(InputMode mode);
                virtual void throwReleaseForAll();
                virtual void changeAnimationAllToNormal();
                virtual void updatePredictLanguage(CommandReceiver::ChangePredictMode* mode);
                virtual void changeKeyTop(const PaneNameToCharCode* keys);
                virtual void changeSpaceKeyTop(const PaneNameToCharCode* keys);
                void setUpperCaseJP(bool enabled);
                void setLangKeyActive(bool enabled);
                void resetHoldingButton();

            private:
                bool mbLineFeedButton;
                GXTexObj mTextures[3];
                EventHandler* mpEventHandler;
                predictlang::LayoutByNW4R* mpPredictLanguageDialog;
                signwindow::LayoutByNW4R* mpSignWindow;
#elif defined(TIMANAGER_IMPLEMENTATION)
                virtual nw4rmanager::AnmPane* getAnmPane(InputMode mode);
                virtual void throwReleaseForAll();
                virtual void changeAnimationAllToNormal();
                virtual void updatePredictLanguage(CommandReceiver::ChangePredictMode* mode);
                virtual void changeKeyTop(const struct PaneNameToCharCode* table);
                virtual void changeSpaceKeyTop(const struct PaneNameToCharCode* table);
#endif
            };

#ifdef TI_CELLPHONE_SAMPLE_CLASS
            class Sample : public LayoutByNW4R {
            public:
                Sample(Manager* manager, nw4r::lyt::MultiArcResourceAccessor* resAccessor, EventObserver* observer)
                    : LayoutByNW4R(manager, resAccessor, observer) {}
                virtual ~Sample() {}
            };
#endif

#ifdef TI_CELLPHONE_IMPLEMENTATION
            enum Animation {
                ANM_Normal,
                ANM_FocusIn,
                ANM_FocusOut,
                ANM_RollOver,
                ANM_Pushed,
                ANM_05,
                ANM_06,
                ANM_ToggleOff,
                ANM_Last,
            };

            enum KeyType {
                KT_NormalButton,
                KT_ControlButton,
            };

            class CellPhoneAnmPane : public nw4rmanager::AnmPane {
            public:
                CellPhoneAnmPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer)
#ifdef TI_CELLPHONE_MATCH_LAYOUT
                    : nw4rmanager::AnmPane(pane, observer), meState(ANM_Normal), meKeyType(KT_NormalButton) {
                    init();
                    changeAnimation(meState);
                }
#else
                    : nw4rmanager::AnmPane(pane, observer), meState(ANM_Normal), meKeyType(KT_NormalButton) {}
#endif

                virtual void init() override;
                virtual void onAnmEvent(AnmPaneEvent event) override;
                virtual void changeAnimation(u32 id) override;
                virtual KeyType getKeyType() const;
                u32 getAnimationState() const { return meState; }
                virtual ~CellPhoneAnmPane();

            protected:
                Animation meState;
                KeyType meKeyType;
            };

            class CellPhoneControlAnmPane : public CellPhoneAnmPane {
            public:
                CellPhoneControlAnmPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer)
                    : CellPhoneAnmPane(pane, observer) { meKeyType = KT_ControlButton; }

                virtual void onAnmEvent(AnmPaneEvent event) override;
                virtual ~CellPhoneControlAnmPane();
            };

            class EventHandler : public nw4rmanager::TiEventHandler {
            public:
                EventHandler(LayoutByNW4R* layout) : mpLayoutByNW4R(layout) {}
                virtual ~EventHandler();
                virtual void onTiEvent(gui::PaneComponent* pane, u32 event, Input* input) override;

            private:
                LayoutByNW4R* mpLayoutByNW4R;
            };

#endif

        }  // namespace cellphonetype
    }  // namespace keyboard
}  // namespace textinput

#endif  // TEXTINPUT_CELL_PHONE_H
