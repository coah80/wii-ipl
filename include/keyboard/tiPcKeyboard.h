#ifndef TEXTINPUT_PC_KEYBOARD_H
#define TEXTINPUT_PC_KEYBOARD_H

#include "tiKeyboard.h"
#include "tiNw4rManager.h"
#include "tiGUIManager.h"

namespace textinput {
    class Manager;

    namespace predictlang {
        class LayoutByNW4R;
    }

    namespace keyboard {
        namespace signwindow {
            class LayoutByNW4R;
        }

        namespace pctype {

            class LayoutByNW4R;
            class AnmPane;

            class UIObj : public gui::EventHandler {
            public:
                class Listener {
                public:
                    virtual void onEvent(UIObj* uiObj, u32, void*) = 0;  // 0x08
                };

                UIObj(u32 ctrlNo, LayoutByNW4R* layout, Listener* listener) : mCtrlNo(ctrlNo), mpLayout(layout) {
                    mpListener = listener;
                }

                virtual ~UIObj();                                                                       // 0x08
                virtual void onEvent(gui::GUIComponent& comp, u32 event, void* data);                   // 0x0C
                virtual void onGUIEvent(gui::PaneComponent& pane, u32 event, nw4rmanager::TiEventHandler::Input* input);  // 0x18

            protected:
                u32 mCtrlNo;             // 0x08
                LayoutByNW4R* mpLayout;  // 0x0C
                Listener* mpListener;    // 0x10
            };

            class UIModifierButton : public UIObj {
                friend class LayoutByNW4R;

            public:
                UIModifierButton(u32 ctrlNo, LayoutByNW4R* layout, Listener* listener);

                virtual ~UIModifierButton();
                virtual void onGUIEvent(gui::PaneComponent& pane, u32 event, nw4rmanager::TiEventHandler::Input* input);

            private:
                gui::PaneComponent* mpPaneComp1;   // 0x14
                gui::PaneComponent* mpPaneComp2;   // 0x18
                nw4rmanager::AnmPane* mpAnmPane;    // 0x1C
                u8 mbFocused;                      // 0x20
            };

            class UIModePanel : public UIObj {
                friend class LayoutByNW4R;

            public:
                UIModePanel(u32 ctrlNo, LayoutByNW4R* layout, Listener* listener);

                virtual ~UIModePanel();
                virtual void onGUIEvent(gui::PaneComponent& pane, u32 event, nw4rmanager::TiEventHandler::Input* input);

                void Create(nw4rmanager::Layout* layout);

            private:
                u32 unk_0x14;                        // 0x14
                gui::PaneComponent* mpComps1[5];     // 0x18
                gui::PaneComponent* mpComps2[5];     // 0x2C
                nw4rmanager::AnmPane* mpAnmPanes[5];  // 0x40
                nw4r::lyt::Pane* mExtraPanes[3];     // 0x54
                GXTexObj mTexObjs[4];                // 0x60
            };

            class AnmPane : public nw4rmanager::AnmPane {
            public:
                AnmPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer)
                    : nw4rmanager::AnmPane(pane, observer) {
                    mState = 0;
                }

                virtual void init();                                                            // 0x08
                virtual void changeAnimation(u32 id);                                           // 0x14
                virtual ~AnmPane();                                                             // 0x20
                virtual u32 getState() const { return mState; }                                 // 0x24
                virtual u32 getKeyType() const { return mKeyType; }                             // 0x28

            protected:
                s32 mState;    // 0x2C
                u32 mKeyType;  // 0x30
            };

            class NormalButtonAnmPane : public AnmPane {
            public:
                NormalButtonAnmPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer) : AnmPane(pane, observer) {
                    mKeyType = 0;
                }

                virtual void onAnmEvent(AnmPaneEvent paneEvent);  // 0x10
                virtual ~NormalButtonAnmPane();
            };

            class ShiftCapsAnmPane : public AnmPane {
            public:
                ShiftCapsAnmPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer) : AnmPane(pane, observer) {
                    mKeyType = 1;
                    mbFocused = false;
                }

                virtual void onAnmEvent(AnmPaneEvent paneEvent);  // 0x10
                virtual ~ShiftCapsAnmPane();

                virtual bool isFocused() const;                   // 0x2C

            private:
                u8 mbFocused;  // 0x34
            };

            class ToggleButtonAnmPane : public AnmPane {
            public:
                ToggleButtonAnmPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer) : AnmPane(pane, observer) {
                    mKeyType = 2;
                }

                virtual void onAnmEvent(AnmPaneEvent paneEvent);  // 0x10
                virtual ~ToggleButtonAnmPane();
            };

            class OnOffButtonAnmPane : public AnmPane {
            public:
                OnOffButtonAnmPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer) : AnmPane(pane, observer) {
                    mKeyType = 3;
                }

                virtual void onAnmEvent(AnmPaneEvent paneEvent);  // 0x10
                virtual ~OnOffButtonAnmPane();
            };

            class EventHandler : public nw4rmanager::TiEventHandler {
            public:
                EventHandler(LayoutByNW4R* layout) : mpLayout(layout) {}

                virtual ~EventHandler();                                                                            // 0x08
                virtual void onTiEvent(gui::PaneComponent* paneComponent, u32 event, TiEventHandler::Input* input);  // 0x18

            private:
                LayoutByNW4R* mpLayout;  // 0x0C
            };

            class Base : public KeyboardBase {
            public:
                typedef enum TranslateMode {
                    TM_00,
                    TM_01,
                    TM_02,
                    TM_03,
                } TranslateMode;

                typedef enum InputMode {
                    IM_00,
                    IM_01,
                    IM_02,
                    IM_03,
                    IM_04,
                    IM_05,
                    IM_06,
                    IM_07,
                    IM_08,
                } InputMode;

                typedef enum InputType {
                    IT_00,
                    IT_01,
                    IT_02,
                    IT_03,
                    IT_04,
                } InputType;

                struct KeyState {
#ifdef TI_PCTYPE_SAMPLE_CLASS
                    KeyState() : mFlags(0), mIsABC(0), mAIUFlags(0), mLanguage((Language)1) {}
#endif

                    void refresh_();
                    void refreshText(nw4r::lyt::Pane* pane);
                    void setABCFlag(u32 flag);
                    wchar_t getWCCode(u32 keyType);
                    wchar_t getWCCode(char* out);

                    u32 mFlags;              // 0x00
                    u32 mIsABC;              // 0x04
                    u32 mAIUFlags;           // 0x08
                    Language mLanguage;      // 0x0C
                    const void* mpLanguageDep;  // 0x10
                    Base* mpBase;            // 0x14
                };

#ifdef TI_PCTYPE_SAMPLE_CLASS
                Base(Manager* manager) {
                    mKeyState.mpLanguageDep = NULL;
                    mKeyState.mpBase = this;
                    mpAllocator = NULL;
                    mbOnlyQwerty = false;
                    mpManager = manager;
                }
#endif

                virtual ~Base();
                virtual void create(MEMAllocator* allocator) override;                 // 0x0C
                virtual void init() override;                                        // 0x10
                virtual void updateFromReceiver(u32, void*) override;                // 0x1C
                virtual void onKey(u32, void*);                                      // 0x20
                virtual int getType();                                               // 0x24
                virtual void setLanguage(Language language) override;                // 0x28
                virtual void onActive() override;                                    // 0x34
                virtual void inputCharCode(wchar_t wc);                              // 0x38
                virtual void* getState();                                            // 0x3C
                virtual bool isShiftOn() const;                                      // 0x40
                virtual bool isCapsOn() const;                                       // 0x44
                virtual bool isABC();                                                // 0x48
                virtual void setABC(bool);                                           // 0x4C
                virtual int getABCInputMode() const;                                 // 0x50
                virtual int getAIUInputMode() const;                                 // 0x54
                virtual TranslateMode getTranslateMode() const;                      // 0x58
                virtual void setTranslateMode(TranslateMode mode);                   // 0x5C
                virtual void onlyQwerty(bool);                                       // 0x60
                virtual void setLangKeyActive(bool);                                 // 0x64
                virtual void setInputModeJP(bool, u32, u32);                         // 0x68
                virtual void setInputModeCK(u32);                                    // 0x6C
                virtual void refreshState();                                         // 0x70
                virtual void changeABCInputMode(InputMode mode);                     // 0x74
                virtual void changeAIUInputMode(InputMode mode);                     // 0x78
                virtual void onClose();                                              // 0x7C
                virtual wchar_t getWCCode(char* out);                                // 0x80
                virtual u32 getControlKey(char* out);                                // 0x84
                virtual void sendInputWChar(wchar_t wc, bool flag);                  // 0x88
                virtual void goSignInputMode();                                      // 0x8C
                virtual void changePredictLanguage();                                // 0x90
                virtual void updateFixMode();                                        // 0x94

            protected:
                Manager* mgr() { return mpManager; }

            public:
                u8   unk_0x14;         // 0x14
                u8   unk_0x15[3];      // 0x15
                u32  unk_0x18;         // 0x18
                const void* mpLanguageDep;  // 0x1C
                KeyState mKeyState;    // 0x20
                MEMAllocator* mpAllocator;  // 0x38
                u8   mbOnlyQwerty;     // 0x3C
                u8   mbLangKeyActive;  // 0x3D
                u8   unk_0x3E[2];      // 0x3E
                Manager* mpManager;    // 0x40
            };

            class LayoutByNW4R : public Base, public nw4rmanager::Layout, public UIObj::Listener {
            public:
#ifdef TI_PCTYPE_SAMPLE_CLASS
                LayoutByNW4R(Manager* manager, nw4r::lyt::MultiArcResourceAccessor* resAccessor, const char* arcName, EventObserver* observer)
                    : Base(manager), nw4rmanager::Layout(resAccessor, arcName, observer), mpEventHandler(NULL),
                      mShiftButton(1, this, this), mCapsButton(0, this, this), mModePanel(2, this, this) {}
#endif

                virtual ~LayoutByNW4R();
                virtual void create(MEMAllocator* allocator) override;
                virtual void init() override;
                virtual void updateFromReceiver(u32, void*) override;
                virtual void onKey(u32, void*) override;
                virtual void setLanguage(Language language) override;
                virtual void onActive() override;
                virtual void inputCharCode(wchar_t wc) override;
                virtual void setABC(bool) override;
                virtual void setTranslateMode(TranslateMode mode) override;
                virtual void onlyQwerty(bool) override;
                virtual void setLangKeyActive(bool) override;
                virtual void setInputModeJP(bool, u32, u32) override;
                virtual void setInputModeCK(u32) override;
                virtual void refreshState() override;
                virtual void onClose() override;
                virtual void sendInputWChar(wchar_t wc, bool flag) override;
                virtual void goSignInputMode() override;
                virtual void changePredictLanguage() override;

                virtual void draw();                                                                     // 0x11C
                virtual void calc();                                                                     // 0x120
                virtual void setPredictLanguageDialog(predictlang::LayoutByNW4R* dialog);                  // 0x124
                virtual void setSignWindow(signwindow::LayoutByNW4R* window);                              // 0x128
                virtual void setLineFeedButton(bool);                                                      // 0x12C
                virtual void setPredictLanguageButton(bool);                                               // 0x130
                virtual void setSignWindowButton(bool);                                                    // 0x134
                virtual bool updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release, void* data);  // 0x138
                virtual bool updateInput(textinput::input::HKBManager& hkbManager);                           // 0x13C
                virtual void changeAnimationAllToNormal();                                                  // 0x140
                virtual void throwReleaseForAll();                                                          // 0x144
                virtual void cancelStateFocusIn();                                                          // 0x148
                virtual void updatePredictLanguage(CommandReceiver::ChangePredictMode* mode);               // 0x14C
                virtual void updateDakuten();                                                               // 0x150
                virtual void initLayout();                                                                  // 0x154
                virtual void onEvent(UIObj* uiObj, u32, void*);                                             // 0x158

                void createAnmPane_(MEMAllocator* allocator);
                void onPressedCaps();
                void onPressedShift(bool);
                void onReleasedShift();

            private:
                EventHandler* mpEventHandler;                        // 0xF0
                predictlang::LayoutByNW4R* mpPredictLanguageDialog;  // 0xF4
                signwindow::LayoutByNW4R* mpSignWindow;              // 0xF8
                bool mbLineFeed;                                     // 0xFC
                u8 unk_0xFD[3];                                      // 0xFD
                UIModifierButton mShiftButton;           // 0x100
                UIModifierButton mCapsButton;            // 0x124
                UIModePanel mModePanel;                  // 0x148
            };

#ifdef TI_PCTYPE_SAMPLE_CLASS
            class Sample : public LayoutByNW4R {
            public:
                Sample(Manager* manager, nw4r::lyt::MultiArcResourceAccessor* resAccessor, const char* arcName, EventObserver* observer)
                    : LayoutByNW4R(manager, resAccessor, arcName, observer) {}
                virtual ~Sample();
            };
#else
            class Sample {};
#endif

        }  // namespace pctype
    }  // namespace keyboard
}  // namespace textinput

#endif  // TEXTINPUT_PC_KEYBOARD_H
