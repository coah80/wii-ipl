#ifndef TEXTINPUT_SIGN_WINDOW_H
#define TEXTINPUT_SIGN_WINDOW_H

#include "tiKeyboard.h"
#include "tiNw4rManager.h"
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
    virtual ~Base();
    virtual void create(MEMAllocator*) override;
    virtual void init() override;
    virtual void onKey(u32, void*) override;
    virtual bool isLocked();
    virtual void setPage(u8);
    virtual u8 getPage();
    virtual void movePrevSignPage();
    virtual void moveNextSignPage();
    virtual void close();
    virtual int getType() override;
    virtual void setLanguage(Language) override;

protected:
    u8 mInputFlags;
    bool mbLocked;
    bool mbRepeat;
    u8 muPage;
    const LanguageDependency* mpLanguageDependency;
    MEMAllocator* mpAllocator;
    Manager* mpManager;
};

class EventHandler;

class LayoutByNW4R : public Base, public nw4rmanager::Layout, public nw4rmanager::AnmObserver {
public:
    virtual ~LayoutByNW4R();
    virtual void create(MEMAllocator*) override;
    virtual void init() override;
    virtual void onKey(u32, void*) override;
    virtual void movePrevSignPage() override;
    virtual void moveNextSignPage() override;
    virtual void close() override;
    virtual void draw() override;
    virtual void open(KeyboardBase*, bool);
    virtual bool isActive();
    virtual void onChangeAnmState(AnmEvent, nw4rmanager::AnmPane*, nw4rmanager::Anim*) override;
    virtual bool updateInput(int, f32, f32, u32, u32, u32, void*) override;
    virtual bool updateInput(input::HKBManager&) override;
    virtual void throwReleaseForAll();
    virtual void resetAnmSignWindow();
    virtual void setSignKeyTop(u16, u16);
    virtual void setPageNumber(u16);
    virtual void endToClose();
    virtual void startToInput();
    virtual void movePrevSignWindow();
    virtual void moveNextSignWindow();
#ifdef TISIGNWINDOW_IMPLEMENTATION
    virtual void vt_0x10C() = 0;
#endif

    bool mbActive;
    bool mbInput;
    EventHandler* mpEventHandler;
    KeyboardBase* mpKeyboard;
};

class Sample : public LayoutByNW4R {
public:
    virtual ~Sample();
};

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

}
}
}

#endif
