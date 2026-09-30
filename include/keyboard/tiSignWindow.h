#ifndef TEXTINPUT_SIGN_WINDOW_H
#define TEXTINPUT_SIGN_WINDOW_H

#include "tiKeyboard.h"
#include "tiNw4rManager.h"
#include "tiTextInputBase.h"

namespace textinput {
    class Manager;

    namespace keyboard {
        namespace signwindow {
            class Base : public KeyboardBase {
            public:
#ifdef TI_SIGNWINDOW_SAMPLE_CLASS
                Base(Manager* manager) : unk_0x1C(0), mpManager(manager) {}
#endif

                virtual ~Base() {}
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
                u32 unk_0x14;         // 0x14
                u32 unk_0x18;         // 0x18
                u32 unk_0x1C;         // 0x1C
                Manager* mpManager;   // 0x20
            };

            class AnmPane;
            class EventHandler;

            class LayoutByNW4R : public Base, public nw4rmanager::Layout, public nw4rmanager::AnmObserver {
            public:
#ifdef TI_SIGNWINDOW_SAMPLE_CLASS
                LayoutByNW4R(Manager* manager, nw4r::lyt::MultiArcResourceAccessor* resAccessor, const char* arcName, EventObserver* observer)
                    : Base(manager), nw4rmanager::Layout(resAccessor, arcName, observer), unk_0xD0(0), unk_0xD1(0),
                      mpEventHandler(NULL), unk_0xD8(0) {}
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
                bool unk_0xD0;               // 0xD0
                bool unk_0xD1;               // 0xD1
                EventHandler* mpEventHandler;  // 0xD4
                u32 unk_0xD8;                // 0xD8
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

        }  // namespace signwindow
    }  // namespace keyboard
}  // namespace textinput

#endif  // TEXTINPUT_SIGN_WINDOW_H
