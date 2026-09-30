#ifndef TEXTINPUT_PC_KEYBOARD_IMPL_H
#define TEXTINPUT_PC_KEYBOARD_IMPL_H

#include "tiKeyboard.h"
#include "tiNw4rManager.h"
#include "tiPkData.h"

namespace textinput {
    class Manager;
    namespace predictlang {
        class LayoutByNW4R;
    }
    namespace keyboard {
        namespace signwindow {
            class LayoutByNW4R;
        }
    }
    namespace keyboard {
        namespace signwindow {
            class Base : public KeyboardBase {
            public:
                virtual bool isLocked();
                virtual void setPage(u8 page);
                virtual u8 getPage();
                virtual void movePrevSignPage();
                virtual void moveNextSignPage();
                virtual void close();
            };
            class LayoutByNW4R : public Base, public nw4rmanager::Layout, public nw4rmanager::AnmObserver {
            public:
                virtual void draw();
                virtual void open(KeyboardBase* keyboard, bool repeat);
                virtual bool isActive();
            };
        }
        namespace pctype {

            struct GridKey {
                char paneName[18];
                wchar_t codes[4];
            };
            struct ControlKey {
                char paneName[20];
                u32 key;
            };
            struct VisiblePanes {
                u16 visibleCount;
                u16 hiddenCount;
                const char* visible[24];
                const char* hidden[24];
            };
            struct Ablaut {
                wchar_t code;
                wchar_t alternatives[7];
            };
            struct LanguageData {
                const PaneNameToCharCodeWithModeAscii* ascii;
                const GridKey* grid;
                const ControlKey* controls;
                const VisiblePanes* panes;
                const Ablaut* ablaut;
            };

            class Base : public KeyboardBase {
            public:
                enum TranslateMode {
                    TM_Direct,
                    TM_Roman,
                    TM_Kana
                };
                enum InputMode {
                    IM_Direct,
                    IM_01,
                    IM_02,
                    IM_03,
                    IM_04,
                    IM_05,
                    IM_Hiragana,
                    IM_Katakana
                };
                enum InputType {
                    IT_00,
                    IT_01,
                    IT_02,
                    IT_03,
                    IT_04
                };
                struct State {
                    bool rejected;
                    u8 inputFlags[7];
                };
                class KeyState {
                public:
                    void refresh_();
                    void refreshText(nw4r::lyt::Pane* root);
                    void setABCFlag(u32 flags);
                    u32 getABCFlag() const { return abcFlags & ~15; }
                    u32 getABCMode() const { return abcFlags & 15; }
                    wchar_t getWCCode(u32 index);
                    wchar_t getWCCode(char* paneName) NO_INLINE;
                    void setABCMode(u32 mode) {
                        if ((abcFlags & 15) != mode) {
                            abcFlags = (abcFlags & ~15) | (mode & 15);
                            refresh_();
                        }
                    }
                    void setAIUMode(u32 mode) {
                        if ((aiuFlags & 15) != mode) {
                            aiuFlags = (aiuFlags & ~15) | (mode & 15);
                            refresh_();
                        }
                    }
                    u32 abcFlags;
                    u32 inputType;
                    u32 aiuFlags;
                    Language language;
                    const LanguageData* data;
                    Base* owner;
                };
                virtual ~Base();
                virtual void create(MEMAllocator* allocator);
                virtual inline void init();
                virtual void updateFromReceiver(u32 command, void* data);
                virtual void onKey(u32 event, void* data);
                virtual int getType();
                virtual void setLanguage(Language language);
                virtual void onActive();
                virtual void inputCharCode(wchar_t code);
                virtual State* getState();
                virtual bool isShiftOn() const;
                virtual bool isCapsOn() const;
                virtual bool isABC();
                virtual void setABC(bool abc);
                virtual InputMode getABCInputMode() const;
                virtual InputMode getAIUInputMode() const;
                virtual TranslateMode getTranslateMode() const;
                virtual void setTranslateMode(TranslateMode mode);
                virtual void onlyQwerty(bool only);
                virtual void setLangKeyActive(bool active);
                virtual void setInputModeJP(bool, u32, u32);
                virtual void setInputModeCK(u32);
                virtual void refreshState();
                virtual void changeABCInputMode(InputMode mode);
                virtual void changeAIUInputMode(InputMode mode);
                virtual void onClose();
                virtual wchar_t getWCCode(char* paneName);
                virtual u32 getControlKey(char* paneName);
                virtual void sendInputWChar(wchar_t code, bool repeat);
                virtual void goSignInputMode();
                virtual void changePredictLanguage();
                virtual void updateFixMode();

            protected:
                State mState;
                const LanguageData* mpInitialLanguageData;
                KeyState mKeyState;
                MEMAllocator* mpAllocator;
                bool mbOnlyQwerty;
                bool mbLanguageKeyActive;
                Manager* mpManager;
            };

            class LayoutByNW4R;
            class AnmPane;
            class EventHandler : public nw4rmanager::TiEventHandler {
            public:
                EventHandler(LayoutByNW4R* layout) : mpKeyboard(layout) {}
                virtual ~EventHandler();
                virtual void onTiEvent(gui::PaneComponent* component, u32 event, Input* input);

            private:
                LayoutByNW4R* mpKeyboard;
            };
            class UIObj : public gui::EventHandler {
            public:
                class Listener {
                public:
                    virtual void onEvent(UIObj*, u32, void*) = 0;
                };
                UIObj(u32 id, LayoutByNW4R* layout, Listener* listener) : mId(id), mpLayout(layout), mpListener(listener) {}
                virtual ~UIObj();
                virtual void onEvent(gui::GUIComponent& component, u32 event, void* data);
                virtual void onGUIEvent(gui::PaneComponent& component, u32 event, nw4rmanager::TiEventHandler::Input* input);

            protected:
                u32 mId;
                LayoutByNW4R* mpLayout;
                Listener* mpListener;
            };
            class UIModifierButton : public UIObj {
            public:
                UIModifierButton(u32 id, LayoutByNW4R* layout, Listener* listener);
                inline void Create(nw4rmanager::Layout* layout, const char* pane, const char* bounding);
                inline void SetState(bool enabled, u32 inactiveAnimation);
                virtual ~UIModifierButton();
                virtual void onGUIEvent(gui::PaneComponent& component, u32 event, nw4rmanager::TiEventHandler::Input* input);
                gui::PaneComponent* mpPaneComponent;
                gui::PaneComponent* mpBoundingComponent;
                AnmPane* mpAnimation;
                bool mbOn;
            };
            class UIModePanel : public UIObj {
            public:
                UIModePanel(u32 id, LayoutByNW4R* layout, Listener* listener);
                virtual ~UIModePanel();
                virtual void onGUIEvent(gui::PaneComponent& component, u32 event, nw4rmanager::TiEventHandler::Input* input);
                void Create(nw4rmanager::Layout* layout);
                u32 mMode;
                gui::PaneComponent* mpPaneComponents[5];
                gui::PaneComponent* mpBoundingComponents[5];
                AnmPane* mpAnimations[5];
                nw4r::lyt::Pane* mpEnglishText;
                nw4r::lyt::Pane* mpHangulText;
                nw4r::lyt::Pane* mpModeSelect;
                GXTexObj mDirectTexture;
                GXTexObj mPinyinTexture;
                GXTexObj mEnglishTexture;
                GXTexObj mHangulTexture;
            };
            class LayoutByNW4R : public Base, public nw4rmanager::Layout, public UIObj::Listener {
            public:
                virtual ~LayoutByNW4R();
                virtual void create(MEMAllocator* allocator);
                virtual void init();
                virtual void updateFromReceiver(u32 command, void* data);
                virtual void onKey(u32 event, void* data);
                virtual void setLanguage(Language language);
                virtual void onActive();
                virtual void inputCharCode(wchar_t code);
                virtual void setABC(bool abc);
                virtual void setTranslateMode(TranslateMode mode);
                virtual void onlyQwerty(bool only);
                virtual void setLangKeyActive(bool active);
                virtual void setInputModeJP(bool abc, u32 abcMode, u32 aiuMode);
                virtual void setInputModeCK(u32 mode);
                virtual void refreshState();
                virtual void onClose();
                virtual void sendInputWChar(wchar_t code, bool repeat);
                virtual void goSignInputMode();
                virtual void changePredictLanguage();
                virtual void draw();
                virtual void calc();
                virtual void setPredictLanguageDialog(predictlang::LayoutByNW4R* dialog);
                virtual void setSignWindow(signwindow::LayoutByNW4R* window);
                virtual void setLineFeedButton(bool visible);
                virtual void setPredictLanguageButton(bool visible);
                virtual void setSignWindowButton(bool visible);
                virtual bool updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release, void* data);
                virtual bool updateInput(input::HKBManager& hkb);
                virtual void changeAnimationAllToNormal();
                virtual void throwReleaseForAll();
                virtual void cancelStateFocusIn();
                virtual void updatePredictLanguage(CommandReceiver::ChangePredictMode* mode);
                virtual void updateDakuten();
                virtual void initLayout();
                virtual void onEvent(UIObj* object, u32 event, void* data);
                void onPressedCaps();
                void onPressedShift(bool shift);
                void onReleasedShift();
                void createAnmPane_(MEMAllocator* allocator);

            private:
                EventHandler* mpKeyboardEventHandler;
                predictlang::LayoutByNW4R* mpPredictDialog;
                signwindow::LayoutByNW4R* mpSignWindow;
                bool mbLineFeed;
                UIModifierButton mShiftButton;
                UIModifierButton mCapsButton;
                UIModePanel mModePanel;
            };

            class AnmPane : public nw4rmanager::AnmPane {
            public:
                AnmPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer) : nw4rmanager::AnmPane(pane, observer), mAnimation(0) {}
                virtual void init();
                virtual void changeAnimation(u32 animation);
                virtual ~AnmPane();
                virtual int getState() const { return mAnimation; }
                virtual int getKeyType() const { return mKeyType; }

            protected:
                int mAnimation;
                int mKeyType;
            };
            class NormalButtonAnmPane : public AnmPane {
            public:
                NormalButtonAnmPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer) : AnmPane(pane, observer) { mKeyType = 0; }
                virtual ~NormalButtonAnmPane();
                virtual void onAnmEvent(AnmPaneEvent event);
            };
            class ShiftCapsAnmPane : public AnmPane {
            public:
                ShiftCapsAnmPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer) : AnmPane(pane, observer), mbOn(false) { mKeyType = 1; }
                virtual ~ShiftCapsAnmPane();
                virtual void onAnmEvent(AnmPaneEvent event);
                bool isFocused() const;

            private:
                bool mbOn;
            };
            class ToggleButtonAnmPane : public AnmPane {
            public:
                ToggleButtonAnmPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer) : AnmPane(pane, observer) { mKeyType = 2; }
                virtual ~ToggleButtonAnmPane();
                virtual void onAnmEvent(AnmPaneEvent event);
            };
            class OnOffButtonAnmPane : public AnmPane {
            public:
                OnOffButtonAnmPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer) : AnmPane(pane, observer) { mKeyType = 3; }
                virtual ~OnOffButtonAnmPane();
                virtual void onAnmEvent(AnmPaneEvent event);
            };

        }
    }
}
#endif
