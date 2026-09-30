#ifndef TEXTINPUT_SIGN_WINDOW_H
#define TEXTINPUT_SIGN_WINDOW_H

#include "tiKeyboard.h"
#include "tiNw4rManager.h"
#include "tiTextInputBase.h"
#include "tiSwData.h"

namespace textinput {
    class Manager;

    namespace keyboard {
        namespace signwindow {
            struct LanguageDependency {
                u8 count;
                const PaneNameToCharCodeInSignMode* keys;
            };

            class Base : public KeyboardBase {
            public:
#ifdef TI_SIGNWINDOW_SAMPLE_CLASS
                Base(Manager* manager) : mpAllocator(NULL), mpManager(manager) {}
#endif

                virtual ~Base();
                virtual void create(MEMAllocator* allocator) override;
                virtual void init() override;
                virtual void onKey(u32, void*);
                virtual int getType();
                virtual void setLanguage(Language language) override;
                virtual bool isLocked();  // 0x38
                virtual void setPage(u8 page);            // 0x3C
                virtual u8 getPage();                     // 0x40
                virtual void movePrevSignPage();          // 0x44
                virtual void moveNextSignPage();          // 0x48
                virtual void close();                     // 0x4C

            protected:
                u8 mInputFlags;                                // 0x14
                bool mbLocked;                                 // 0x15
                bool mbRepeat;                                 // 0x16
                u8 muPage;                                     // 0x17
                const LanguageDependency* mpLanguageDependency; // 0x18
                MEMAllocator* mpAllocator;                     // 0x1C
                Manager* mpManager;                            // 0x20
            };

            class AnmPane;
            class EventHandler;

            class LayoutByNW4R : public Base, public nw4rmanager::Layout, public nw4rmanager::AnmObserver {
            public:
#ifdef TI_SIGNWINDOW_SAMPLE_CLASS
                LayoutByNW4R(Manager* manager, nw4r::lyt::MultiArcResourceAccessor* resAccessor, const char* arcName, EventObserver* observer)
                    : Base(manager), nw4rmanager::Layout(resAccessor, arcName, observer), mbActive(false), mbInput(false),
                      mpEventHandler(NULL), mpKeyboard(NULL) {}
#endif

                virtual ~LayoutByNW4R();
                virtual void create(MEMAllocator* allocator) override;
                virtual void init() override;
                virtual void onKey(u32, void*) override;
                virtual void movePrevSignPage() override;          // 0x44
                virtual void moveNextSignPage() override;          // 0x48
                virtual void close() override;                     // 0x4C

                virtual void draw();                                                          // 0xD4
                virtual void open(KeyboardBase* keyboard, bool flag);                         // 0xD8
                virtual bool isActive();                                                      // 0xDC
                virtual void onChangeAnmState(nw4rmanager::AnmObserver::AnmEvent anmEvent,
                                              nw4rmanager::AnmPane* anmPane, nw4rmanager::Anim* anim);          // 0xE0
                virtual bool updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release, void* data);  // 0xE4
                virtual bool updateInput(textinput::input::HKBManager& hkbManager);           // 0xE8
                virtual void throwReleaseForAll();                                            // 0xEC
                virtual void resetAnmSignWindow();                                            // 0xF0
                virtual void setSignKeyTop(u16, u16);                                         // 0xF4
                virtual void setPageNumber(u16);                                              // 0xF8
                virtual void endToClose();                                                    // 0xFC
                virtual void startToInput();                                                  // 0x100
                virtual void movePrevSignWindow();                                            // 0x104
                virtual void moveNextSignWindow();                                            // 0x108

            private:
                bool mbActive;               // 0xD0
                bool mbInput;                // 0xD1
                EventHandler* mpEventHandler;  // 0xD4
                KeyboardBase* mpKeyboard;    // 0xD8
            };

#ifdef TI_SIGNWINDOW_SAMPLE_CLASS
            class Sample : public LayoutByNW4R {
            public:
                Sample(Manager* manager, nw4r::lyt::MultiArcResourceAccessor* resAccessor, const char* arcName, EventObserver* observer)
                    : LayoutByNW4R(manager, resAccessor, arcName, observer) {}
                virtual ~Sample();
            };
#else
            class Sample {};
#endif

            class EventHandler : public nw4rmanager::TiEventHandler {
            public:
                explicit EventHandler(LayoutByNW4R* layout) : mpLayoutByNW4R(layout) {}
                virtual ~EventHandler();
                virtual void onTiEvent(gui::PaneComponent*, u32, Input*) override;
                LayoutByNW4R* mpLayoutByNW4R;
            };

            class AnmPane : public nw4rmanager::AnmPane {
            public:
                AnmPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer)
                    : nw4rmanager::AnmPane(pane, observer), muAnimation(0) {}
                inline virtual ~AnmPane();
                virtual void init() override;
                virtual void changeAnimation(u32) override;
                virtual u32 getKeyType() const;

            protected:
                s32 muAnimation;
                u32 muKeyType;
            };

            class CellPhoneSignAllAnmPane : public AnmPane {
            public:
                CellPhoneSignAllAnmPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer)
                    : AnmPane(pane, observer) { muKeyType = 0; }
                virtual ~CellPhoneSignAllAnmPane();
                virtual void init() override;
                virtual void onAnmEvent(AnmPaneEvent) override;
            };

            class CellPhoneSignScrollAnmPane : public AnmPane {
            public:
                CellPhoneSignScrollAnmPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer)
                    : AnmPane(pane, observer) { muKeyType = 1; }
                virtual ~CellPhoneSignScrollAnmPane();
                virtual void init() override;
                virtual void onAnmEvent(AnmPaneEvent) override;
            };

            class CellPhoneSignButtonPane : public AnmPane {
            public:
                CellPhoneSignButtonPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer)
                    : AnmPane(pane, observer) { muKeyType = 2; }
                virtual ~CellPhoneSignButtonPane();
                virtual void init() override;
                virtual void onAnmEvent(AnmPaneEvent) override;
            };

        }  // namespace signwindow
    }  // namespace keyboard
}  // namespace textinput

#endif  // TEXTINPUT_SIGN_WINDOW_H
