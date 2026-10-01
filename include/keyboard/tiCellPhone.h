#ifndef TEXTINPUT_CELL_PHONE_H
#define TEXTINPUT_CELL_PHONE_H

#include "tiKeyboard.h"
#include "tiNw4rManager.h"

#include <revolution/gx.h>

namespace textinput {
    class Manager;

    namespace predictlang {
        class LayoutByNW4R;
    }

    namespace keyboard {
        namespace signwindow {
            class LayoutByNW4R;
        }

        class KeyboardBase;

        typedef enum VKeyCode {
            VK_LF = 0,
            VK_DELETE = 1,
            VK_SPACE = 2,
            VK_OTHERS = 9,
            VK_PRDC = 0xA,
            VK_TAG_02 = 0xB,
            VK_TAG_03 = 0xD,
            VK_UNKNOWN_11 = 0x11,
            VK_TAG_00 = 0x12,
            VK_TAG_01 = 0x13,
            VK_SML_CPT = 0x17,
            VK_NONE = 0x1B,
        } VKeyCode;

        namespace cellphonetype {
            struct PaneNameToCharCode;
            struct KeySet;
            struct LanguageDependency;

            class LayoutByNW4R;

            class Base : public KeyboardBase {
            public:
                typedef enum InputMode {
                    IM_00,
                    IM_01,
                    IM_02,
                    IM_03,
                    IM_04,
                    IM_05,
                } InputMode;

#ifdef TI_CELLPHONE_SAMPLE_CLASS
                Base(Manager* manager) : mpManager(manager) {}
#endif

                virtual void create(MEMAllocator* allocator) override;                     // 0x0C
                virtual void init() override;                                            // 0x10
                virtual void setCommandReceiver(CommandReceiver* receiver) override;     // 0x14
                virtual void sendCommand(u32, void*) override;                           // 0x18
                virtual void updateFromReceiver(u32, void*) override;                    // 0x1C
                virtual void onKey(u32, void*);                                          // 0x20
                virtual int getType();                                                  // 0x24
                virtual void setLanguage(Language language) override;                    // 0x28
                virtual Language getLanguage() const override;                           // 0x2C
                virtual void onActive() override;                                        // 0x34
                virtual void calc();                                                     // 0x38
                virtual void draw();                                                     // 0x3C
                virtual int getInputMode() const;                                        // 0x40
                virtual bool isLocked() const;                                           // 0x44
                virtual bool isNumeric() const;                                          // 0x48
                virtual bool isNumericWithDot() const;                                   // 0x4C
                virtual bool isHoldingButton() const;                                    // 0x50
                virtual void doNumericMode(bool);                                        // 0x54
                virtual void changeInputMode(InputMode mode);                            // 0x58
                virtual bool isUpperCase();                                              // 0x5C
                virtual void setInputMode(InputMode mode);                               // 0x60
                virtual void setUpperCaseJP(bool);                                       // 0x64
                virtual void setLangKeyActive(bool);                                     // 0x68
                virtual void onClose();                                                  // 0x6C
                virtual void goSignInputMode();                                          // 0x70
                virtual void changePredictLanguage();                                    // 0x74
                virtual void setAbcMode(bool);                                           // 0x78
                virtual bool isZiActive();                                               // 0x7C
                virtual bool isAtokActive();                                             // 0x80
                virtual void doInput();                                                  // 0x84
                virtual void updateFixMode();                                            // 0x88

                void onCtrlKey_(VKeyCode code);
                wchar_t convertToZiCellphoneInput_(wchar_t wc);

                int getInputType() const;

            protected:
                Manager* mgr() { return mpManager; }

                s32 mTapIndex;                                       // 0x14
                s32 mInputMode;                                      // 0x18
                u8  mbLocked;                                        // 0x1C
                u8  mbNumeric;                                       // 0x1D
                u8  mbNumericWithDot;                                // 0x1E
                u8  mbUpperCase;                                     // 0x1F
                u8  mbShiftHeld;                                     // 0x20
                u8  unk_0x21;                                        // 0x21
                const PaneNameToCharCode* mpHoldingPane;             // 0x24
                const LanguageDependency* mpLanguageDep;             // 0x28
                MEMAllocator* mpAllocator;                           // 0x2C
                Manager* mpManager;                                  // 0x30
                u8  mbLangKeyActive;                                 // 0x34
                u8  unk_0x35[3];                                     // 0x35
            };
            class EventHandler : public nw4rmanager::TiEventHandler {
            public:
                EventHandler(LayoutByNW4R* layout) : mpLayout(layout) {}

                virtual void onTiEvent(gui::PaneComponent* paneComponent, u32 event, TiEventHandler::Input* input);  // 0x18

            private:
                LayoutByNW4R* mpLayout;  // 0x0C
            };

            class CellPhoneAnmPane : public nw4rmanager::AnmPane {
            public:
                CellPhoneAnmPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer, u32 keyType)
                    : nw4rmanager::AnmPane(pane, observer) {
                    mState = 0;
                    mKeyType = keyType;
                    init();
                    changeAnimation(mState);
                }

                virtual void init();                                // 0x08
                virtual void onAnmEvent(AnmPaneEvent paneEvent);    // 0x10
                virtual void changeAnimation(u32 id);               // 0x14
                virtual u32 getKeyType() const;                     // 0x24

            protected:
                s32 mState;    // 0x2C
                u32 mKeyType;  // 0x30
            };

            class CellPhoneControlAnmPane : public CellPhoneAnmPane {
            public:
                CellPhoneControlAnmPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer, u32 keyType)
                    : CellPhoneAnmPane(pane, observer, 0) {
                    mKeyType = keyType;
                }

                virtual void onAnmEvent(AnmPaneEvent paneEvent);    // 0x10
            };


            class LayoutByNW4R : public Base, public nw4rmanager::Layout {
            public:
#ifdef TI_CELLPHONE_SAMPLE_CLASS
                LayoutByNW4R(Manager* manager, nw4r::lyt::MultiArcResourceAccessor* resAccessor, const char* arcName, EventObserver* observer)
                    : Base(manager), nw4rmanager::Layout(resAccessor, arcName, observer),
                      mpEventHandler(NULL) {}
#endif

                virtual ~LayoutByNW4R();
                virtual void create(MEMAllocator* allocator) override;
                virtual void init() override;
                virtual void setCommandReceiver(CommandReceiver* receiver) override;
                virtual void updateFromReceiver(u32, void*) override;
                virtual void onKey(u32, void*) override;
                virtual void setLanguage(Language language) override;
                virtual void update() override;
                virtual void onActive() override;
                virtual void calc() override;
                virtual void draw() override;
                virtual void doNumericMode(bool) override;
                virtual void changeInputMode(InputMode mode) override;
                virtual void setInputMode(InputMode mode) override;
                virtual void setUpperCaseJP(bool) override;
                virtual void setLangKeyActive(bool) override;
                virtual void onClose() override;
                virtual void goSignInputMode() override;
                virtual void changePredictLanguage() override;
                virtual void setAbcMode(bool) override;

                virtual void setPredictLanguageDialog(predictlang::LayoutByNW4R*);                          // 0x104
                virtual void setSignWindow(signwindow::LayoutByNW4R*);                                      // 0x108
                virtual void doNumericWithDotMode(bool);                                                    // 0x10C
                virtual void setLineFeedButton(bool);                                                       // 0x110
                virtual void setPredictLanguageButton(bool);                                                // 0x114
                virtual void setSignWindowButton(bool);                                                     // 0x118
                virtual bool updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release, void* data);  // 0x11C
                virtual bool updateInput(textinput::input::HKBManager& hkbManager);                           // 0x120
                virtual nw4rmanager::AnmPane* getAnmPane(InputMode mode);                                     // 0x124
                virtual void throwReleaseForAll();                                                          // 0x128
                virtual void changeAnimationAllToNormal();                                                  // 0x12C
                virtual void updatePredictLanguage(CommandReceiver::ChangePredictMode* mode);               // 0x130
                virtual void changeKeyTop(const PaneNameToCharCode* table);                                 // 0x134
                virtual void changeSpaceKeyTop(const PaneNameToCharCode* table);                            // 0x138

                void onPressedShift(bool shift);
                void onReleasedShift();
                void resetHoldingButton();

            private:
                bool    mbLineFeed;     // 0xE0
                u8      unk_0xE1[3];    // 0xE1
                GXTexObj mSpaceTexObjJP;  // 0xE4
                GXTexObj mSpaceTexObjCN;  // 0x104
                GXTexObj mSpaceTexObjKR;  // 0x124
                EventHandler* mpEventHandler;                            // 0x144
                predictlang::LayoutByNW4R* mpPredictLanguageDialog;      // 0x148
                signwindow::LayoutByNW4R* mpSignWindow;                  // 0x14C
            };

#ifdef TI_CELLPHONE_SAMPLE_CLASS
            class Sample : public LayoutByNW4R {
            public:
                Sample(Manager* manager, nw4r::lyt::MultiArcResourceAccessor* resAccessor, const char* arcName, EventObserver* observer)
                    : LayoutByNW4R(manager, resAccessor, arcName, observer) {}
                virtual ~Sample();
            };
#else
            class Sample {};
#endif

        }  // namespace cellphonetype
    }  // namespace keyboard
}  // namespace textinput

#endif  // TEXTINPUT_CELL_PHONE_H
