#ifndef TEXTINPUT_CELL_PHONE_H
#define TEXTINPUT_CELL_PHONE_H

#include "tiNw4rManager.h"
#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
#include "tiKeyboard.h"
#endif

namespace textinput {
    namespace keyboard {
        namespace cellphonetype {
#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
            class Base : public textinput::keyboard::KeyboardBase {
#else
            class Base {
#endif
            public:
#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
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
#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
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
#if defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
                void resetHoldingButton();
#endif

#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
            private:
                u32 mPreviousInputMode;
                u32 mCurrentInputMode;
                bool mbInputModeLocked;
                bool mbNumericMode;
                bool mbNumericWithDotMode;
                bool mbUpperCaseMode;
                bool mbAbcMode;
                bool mbLanguageKeyMode;
                u32 mHoldingButton;
                void* mpInputModeTable;
                MEMAllocator* mpAllocator;
#ifdef TIMANAGER_IMPLEMENTATION
                Manager* mpManager;
#else
                void* mpInputSettings;
#endif
                u32 mInputState;
#endif
            };

            class LayoutByNW4R : public Base, public nw4rmanager::Layout {
            public:
#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
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
                virtual void doNumericMode(bool);
                virtual void setPredictLanguageDialog(void*);
                virtual void setSignWindow(void*);
#endif
                virtual void doNumericWithDotMode(bool);
                virtual void setLineFeedButton(bool);
                virtual void setPredictLanguageButton(bool);
                virtual void setSignWindowButton(bool);
#endif
                virtual bool onClose();

                void onPressedShift(bool shift);
                void onReleasedShift();
#if defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
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
#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIMANAGER_IMPLEMENTATION)
                virtual bool updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release, void* data) override;
                virtual bool updateInput(input::HKBManager& hkbManager) override;
#endif
#ifdef TIMANAGER_IMPLEMENTATION
                virtual nw4rmanager::AnmPane* getAnmPane(InputMode mode);
                virtual void throwReleaseForAll();
                virtual void changeAnimationAllToNormal();
                virtual void updatePredictLanguage(CommandReceiver::ChangePredictMode* mode);
                virtual void changeKeyTop(const struct PaneNameToCharCode* table);
                virtual void changeSpaceKeyTop(const struct PaneNameToCharCode* table);
#endif
            };

        }  // namespace cellphonetype
    }  // namespace keyboard
}  // namespace textinput

#endif  // TEXTINPUT_CELL_PHONE_H
