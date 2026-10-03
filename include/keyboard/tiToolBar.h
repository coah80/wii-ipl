#ifndef TEXTINPUT_TOOLBAR_H
#define TEXTINPUT_TOOLBAR_H

#include "tiNw4rManager.h"
#include "tiTextInputBase.h"

namespace textinput {
    class Manager;

    namespace toolbar {
        class Base {
        public:
#if defined(TI_TOOLBAR_SAMPLE_CLASS) || defined(TIMANAGER_IMPLEMENTATION)
            Base(Manager* manager) : mQwerty(true), meLanguage(USA), mpAllocator(NULL), mpManager(manager) {}
#endif

            virtual void create(MEMAllocator* allocator) { mpAllocator = allocator; }
            virtual void init() {}
#ifdef TI_PC_KEYBOARD_IMPLEMENTATION
            virtual bool isQwerty() const;
#else
            virtual bool isQwerty() const { return mQwerty; }
#endif
            virtual void setQwerty(bool qwerty);
            virtual void setLanguage(Language language) { meLanguage = language; }
            virtual Language getLanguage() const { return meLanguage; }

        protected:
            Manager* mgr() { return mpManager; }

            bool mQwerty;               // 0x04
            Language meLanguage;        // 0x08
            MEMAllocator* mpAllocator;  // 0x0C
            Manager* mpManager;         // 0x10
        };

        class AnmPane;
        class EventHandler;

        class LayoutByNW4R : public Base, public nw4rmanager::Layout {
        public:
#ifdef TIMANAGER_IMPLEMENTATION
            LayoutByNW4R(Manager* manager, nw4r::lyt::MultiArcResourceAccessor* resAccessor, EventObserver* observer, const char* layoutName)
                : Base(manager), nw4rmanager::Layout(resAccessor, layoutName, observer), mpEventHandler(NULL),
                  mbIsEnableQwertyChg(false) {}
#elif defined(TI_TOOLBAR_SAMPLE_CLASS)
            LayoutByNW4R(Manager* manager, nw4r::lyt::MultiArcResourceAccessor* resAccessor, EventObserver* observer)
                : Base(manager), nw4rmanager::Layout(resAccessor, "fs_VK_toolbar_a.brlyt", observer), mpEventHandler(NULL),
                  mbIsEnableQwertyChg(false) {}
#endif

            virtual ~LayoutByNW4R();
            virtual void create(MEMAllocator* allocator) override;
            virtual void init() override;
            virtual void draw() override;

            virtual void setQwerty(bool qwerty) override;
            virtual void setLanguage(Language language) override;

            virtual void onOK();
            virtual void onCancel();
            virtual void setQwertyWithSE(bool qwerty);
            virtual bool isEnableKeytopChange() const;
            virtual void enableKeytopChange(bool enable);
#ifdef MYTIMANAGER_MATCHING
            virtual nw4r::lyt::Pane* getDownArea();
            virtual nw4r::lyt::Pane* getUpArea();
#else
            virtual nw4r::lyt::Pane* getUpArea();
            virtual nw4r::lyt::Pane* getDownArea();
#endif
            virtual void setOKButtonVisible(bool visible);
            virtual void setCancelButtonVisible(bool visible);
            virtual void setOKButtonCaption(const wchar_t* caption);
            virtual void setCancelButtonCaption(const wchar_t* caption);
            virtual void cancelStateFocusIn();

        private:
            EventHandler* mpEventHandler;  // 0xBC
            bool mbIsEnableQwertyChg;      // 0xC0
        };

        class EventHandler : public nw4rmanager::TiEventHandler {
        public:
            EventHandler(LayoutByNW4R* layout) : mpLayoutByNW4R(layout) {}
            virtual void onTiEvent(gui::PaneComponent* paneComponent, u32 event, Input* input) override;

        private:
            LayoutByNW4R* mpLayoutByNW4R;  // 0xC
        };

        enum Animation {
            ANM_Normal,
            ANM_FocusIn,
            ANM_FocusOut,
            ANM_RollOver,
            ANM_Pushed,
            ANM_ToggleOn,
            ANM_ToggleOff,
            // TODO: These do not appear to be ever set, but some of them are read...
            ANM_07,
            ANM_08,
            ANM_09,
            ANM_10,
            ANM_11,

            ANM_Last,
        };

        enum KeyType {
            KT_NormalButton,
            KT_ToggleButton,
            KT_Last,
        };

        class AnmPane : public nw4rmanager::AnmPane {
        public:
            AnmPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer) : nw4rmanager::AnmPane(pane, observer), meState(ANM_Normal) {}

            virtual void changeAnimation(u32 id) override {
                meState = static_cast<Animation>(id);
                nw4rmanager::AnmPane::changeAnimation(id);
            }
            virtual void init() override { meState = ANM_Normal; }
            virtual enum KeyType getKeyType() const { return meKeyType; }
            virtual enum Animation getState() { return meState; }

        protected:
            Animation meState;  // 0x2C
            KeyType meKeyType;  // 0x30
        };

#if defined(TI_TOOLBAR_SAMPLE_CLASS) || defined(TIMANAGER_IMPLEMENTATION)
        class Sample : public LayoutByNW4R {
        public:
#ifdef TIMANAGER_IMPLEMENTATION
            Sample(Manager* manager, nw4r::lyt::MultiArcResourceAccessor* resAccessor, EventObserver* observer, const char* layoutName)
                : LayoutByNW4R(manager, resAccessor, observer, layoutName) {}
#else
            Sample(Manager* manager, nw4r::lyt::MultiArcResourceAccessor* resAccessor, EventObserver* observer)
                : LayoutByNW4R(manager, resAccessor, observer) {}
#endif
#ifdef TIMANAGER_IMPLEMENTATION
            virtual ~Sample();
#else
            virtual ~Sample() {}
#endif
        };
#else
        class Sample {};
#endif

        class NormalButtonAnmPane : public AnmPane {
        public:
            NormalButtonAnmPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer) : AnmPane(pane, observer) { meKeyType = KT_NormalButton; }
            virtual ~NormalButtonAnmPane() {}

            virtual void onAnmEvent(AnmPaneEvent paneEvent) override;  // 0x10
        };

        class ToggleButtonAnmPane : public AnmPane {
        public:
            ToggleButtonAnmPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer) : AnmPane(pane, observer) { meKeyType = KT_ToggleButton; }
            virtual ~ToggleButtonAnmPane() {}

            virtual void onAnmEvent(AnmPaneEvent paneEvent) override;  // 0x10
        };

    }  // namespace toolbar
}  // namespace textinput

#endif
