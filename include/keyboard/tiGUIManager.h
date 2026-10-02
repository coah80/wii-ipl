#ifndef TEXTINPUT_GUI_MANAGER_H
#define TEXTINPUT_GUI_MANAGER_H

#include <revolution/types.h>

#include <revolution/kpad.h>
#include <revolution/mem.h>
#include <revolution/mtx.h>

#include <nw4r/lyt.h>
#include <nw4r/ut.h>

namespace textinput {
    namespace gui {
        /* GUI MANAGER */

#define GUI_POINTS_MAX 8

        class GUIInterface;
        class GUIComponent;
        class GUIManager;
        class EventHandler;

        class GUIPointer {
        public:
            GUIPointer(int point, f32 x, f32 y, u32 hold, u32 trig, u32 release)
                : mCtrlNo(point), mPosX(x), mPosY(y), mTrig(trig), mHold(hold), mRelease(release) {}

            int getCtrlNo() const { return mCtrlNo; }

            f32 getPosX() const { return mPosX; }
            f32 getPosY() const { return mPosY; }

            u32 isPressed(u32 btn) const { return (mHold & btn); }

        private:
            int mCtrlNo;  // 0x00

            f32 mPosX;  // 0x04
            f32 mPosY;  // 0x08

            u32 mTrig;     // 0x0C
            u32 mHold;     // 0x10
            u32 mRelease;  // 0x14
        };

        class GUIInterface {
        public:
            virtual ~GUIInterface() {}  // 0x08

#ifdef TIGUIMANAGER_IMPLEMENTATION
            virtual void create();  // 0x0C

            virtual void init();  // 0x10
            virtual void calc();  // 0x14

            virtual void draw(Mtx& mtx);  // 0x18
            virtual void draw();          // 0x1C
#else
            virtual void create() {}  // 0x0C

            virtual void init() {}  // 0x10
            virtual void calc() {}  // 0x14

            virtual void draw(Mtx& mtx) {}  // 0x18
            virtual void draw() {}          // 0x1C
#endif
        };

        class EventHandler {
        public:
            enum {
                ON_POINT = 0,
                ON_LEFT,
                ON_MOVE,
                ON_DRAG,
                ON_TRIG,
                ON_RELEASE,
            };

            EventHandler() : muLatestEventCtrlNo(0) {}

#ifdef TI_PC_KEYBOARD_IMPLEMENTATION
            virtual ~EventHandler();  // 0x08
#else
            virtual ~EventHandler() {}  // 0x08
#endif

#if defined(TI_PC_KEYBOARD_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION) || defined(TISIGNWINDOW_IMPLEMENTATION) || defined(TI_CANDIDATEBOX_IMPLEMENTATION) || defined(TI_CELLPHONE_IMPLEMENTATION)
            virtual void onEvent(GUIComponent& comp, u32 event, void* data);  // 0x0C

            virtual void setLatestEventCtrlNo(int ctrlNo);  // 0x10
            virtual int getLatestEventCtrlNo();              // 0x14
#else
            virtual void onEvent(GUIComponent& comp, u32 event, void* data) {}  // 0x0C

            virtual void setLatestEventCtrlNo(int ctrlNo) { muLatestEventCtrlNo = ctrlNo; }  // 0x10
            virtual int getLatestEventCtrlNo() { return muLatestEventCtrlNo; }               // 0x14
#endif

        protected:
            int muLatestEventCtrlNo;  // 0x04
        };

        class GUIComponent : public GUIInterface {
        public:
            enum {
                EVENT_NONE = 0,
                EVENT_POINT,
                EVENT_LEFT,
                EVENT_MOVE,
                EVENT_TRIG,
                EVENT_RELEASE
            };

#ifdef TIGUIMANAGER_IMPLEMENTATION
            virtual ~GUIComponent();  // 0x08
#else
            virtual ~GUIComponent() {}  // 0x08
#endif

#if defined(TIINPUTFORM_IMPLEMENTATION) || defined(TIGUIMANAGER_IMPLEMENTATION)
            virtual void init();  // 0x10
#else
            virtual void init() {  // 0x10
                for (int i = 0; i < GUI_POINTS_MAX; i++) {
                    mbPointed[i] = false;
                    mDraggingPos[i].z = mDraggingPos[i].y = mDraggingPos[i].x = 0;
                    mbDragging[i] = false;
                    mFlightDuration[i] = 0;
                }
            }
#endif

            GUIComponent(u32 id)
                : GUIInterface(), mbInitialize(false), mDraggingButton(0xFFFF), mID(id), mbTriggerTarget(false), mpManager(NULL), mpListener(NULL) {
                init();
            }

#ifdef TIGUIMANAGER_IMPLEMENTATION
            virtual u32 getID();  // 0x20

            virtual bool isPointed(int point);  // 0x24
#else
            virtual u32 getID() { return mID; }  // 0x20

            virtual bool isPointed(int point) { return mbPointed[point]; }    // 0x24
#endif
#if defined(TI_PC_KEYBOARD_IMPLEMENTATION) || defined(TIGUIMANAGER_IMPLEMENTATION)
            virtual bool isDragging(int point);  // 0x28
#else
            virtual bool isDragging(int point) { return mbDragging[point]; }  // 0x28
#endif

#ifdef TIGUIMANAGER_IMPLEMENTATION
            virtual void setPointed(int point, bool bEnable);  // 0x2C
#else
            virtual void setPointed(int point, bool bEnable) { mbPointed[point] = bEnable; }  // 0x2C
#endif

            void onEvent(u32 event, void* data) {
                if (mpListener) {
                    mpListener->onEvent(*this, event, data);
                }
            }

#ifdef TIGUIMANAGER_IMPLEMENTATION
            virtual void onPointIn(int point);   // 0x30
            virtual void onPointOut(int point);  // 0x34

            virtual void onDrag(f32 x, f32 y);
            virtual void onMove(int point, f32 x, f32 y);  // 0x38
            virtual void onTrig(int point, u32 trig, Vec& dragPos);

            virtual void setDraggingButton(u32 dragBtn);  // 0x3C

            virtual u32 updatePointer(const GUIPointer& pointer);  // 0x40
            virtual u32 updatePointer(int point, f32 x, f32 y, u32 trig, u32 hold, u32 release);  // 0x44

            virtual bool isTriggerTarget();  // 0x48
#else
            virtual void onPointIn(int point) { mFlightDuration[point] = 0; }   // 0x30
            virtual void onPointOut(int point) { mFlightDuration[point] = 0; }  // 0x34

            virtual void onDrag(f32 x, f32 y) {}
            virtual void onMove(int point, f32 x, f32 y) { mFlightDuration[point]++; }  // 0x38
            virtual void onTrig(int point, u32 trig, Vec& dragPos) {
                if (trig & mDraggingButton) {
                    mDraggingPos[point] = dragPos;
                    mbDragging[point] = true;
                    mFlightDuration[point] = 0;
                }
            }

            virtual void setDraggingButton(u32 dragBtn) { mDraggingButton = dragBtn; }  // 0x3C

            virtual u32 updatePointer(const GUIPointer& pointer) { return updatePointerImpl(pointer); }  // 0x40
            virtual u32 updatePointer(int point, f32 x, f32 y, u32 trig, u32 hold, u32 release) {        // 0x44
                GUIPointer pointer(point, x, y, hold, trig, release);
                return updatePointerImpl(pointer);
            }

            virtual bool isTriggerTarget() { return mbTriggerTarget; }                  // 0x48
#endif
#if defined(TI_PC_KEYBOARD_IMPLEMENTATION) || defined(TIGUIMANAGER_IMPLEMENTATION)
            virtual void setTriggerTarget(bool bEnable);  // 0x4C
#else
            virtual void setTriggerTarget(bool bEnable) { mbTriggerTarget = bEnable; }  // 0x4C
#endif

            void setParentManager(GUIManager* manager) { mpManager = manager; }
            GUIManager* getParentManager() { return mpManager; }

#ifdef TIGUIMANAGER_IMPLEMENTATION
            virtual bool isVisible();  // 0x50
#else
            virtual bool isVisible() { return true; }  // 0x50
#endif

#if defined(TI_CANDIDATEBOX_IMPLEMENTATION) || defined(TIGUIMANAGER_IMPLEMENTATION)
            virtual u16 getFlightDuration(int point);  // 0x54
#else
            virtual u16 getFlightDuration(int point) { return mFlightDuration[point]; }  // 0x54
#endif
#if defined(TI_CELLPHONE_IMPLEMENTATION) || defined(TIGUIMANAGER_IMPLEMENTATION)
            virtual void setFlightDuration(int point, u16 flightDir);  // 0x58
#else
            virtual void setFlightDuration(int point, u16 flightDir) { mFlightDuration[point] = flightDir; }  // 0x58
#endif

            virtual bool contain(f32 x, f32 y) = 0;  // 0x5C

            void setListener(EventHandler* listener) { mpListener = listener; }

            void lockInitialize(bool lockInit) { mbInitialize = lockInit; }

        protected:
            u32 updatePointerImpl(const GUIPointer& pointer);

            bool mbInitialize;  // 0x04

            bool mbPointed[GUI_POINTS_MAX];  // 0x08

            bool mbDragging[GUI_POINTS_MAX];   // 0x10
            Vec mDraggingPos[GUI_POINTS_MAX];  // 0x18
            int mDraggingButton;               // 0x78

            int mID;  // 0x7C

            u16 mFlightDuration[GUI_POINTS_MAX];  // 0x80

            bool mbTriggerTarget;  // 0x8A

            GUIManager* mpManager;     // 0x8C
            EventHandler* mpListener;  // 0x90
        };

        class GUIManager : public GUIInterface {
        public:
            virtual void init();  // 0x10
            virtual void calc();  // 0x14

            virtual void draw();  // 0x1C

            GUIManager(EventHandler* event, MEMAllocator* allocator) : GUIInterface(), mpEventHandler(event), mpAllocator(allocator) {
                nw4r::ut::List_Init(&mComponents, offsetof(IDToComponent, mLink));
            }

            virtual ~GUIManager() NO_INLINE;  // 0x08

            virtual void addComponent(GUIComponent* component);  // 0x20
            virtual GUIComponent* getComponent(u32 id);          // 0x24
            virtual GUIComponent* getComponent(u32 id) const;    // 0x28

#ifdef TIGUIMANAGER_IMPLEMENTATION
            virtual bool update(int point, const KPADStatus* kpad, f32, f32, void* data);  // 0x2C
#else
            virtual bool update(int point, const KPADStatus* kpad, f32, f32, void* data) { return false; }  // 0x2C
#endif
            virtual bool update(int point, f32 x, f32 y, u32 trig, u32 hold, u32 release, void* data);      // 0x30

#ifdef TIGUIMANAGER_IMPLEMENTATION
            virtual void onEvent(GUIComponent& comp, u32 event, int point, void* data);  // 0x34
#else
            virtual void onEvent(GUIComponent& comp, u32 event, int point, void* data) {  // 0x34
                if (mpEventHandler) {
                    mpEventHandler->setLatestEventCtrlNo(point);
                    mpEventHandler->onEvent(comp, event, data);
                }
                comp.onEvent(event, data);
            }
#endif

            virtual void setAllComponentTriggerTarget(bool bEnable);  // 0x38

#ifdef TIGUIMANAGER_IMPLEMENTATION
            virtual void setEventHandler(EventHandler* eventHandler);      // 0x3C
#else
            virtual void setEventHandler(EventHandler* eventHandler) {  // 0x3C
                mpEventHandler = eventHandler;
            }
#endif
#if defined(TIGUIMANAGER_IMPLEMENTATION) || defined(MYTIINPUTFORM_IMPLEMENTATION)
            virtual EventHandler* changeEventHandler(EventHandler* eventHandler);  // 0x40
#else
            virtual EventHandler* changeEventHandler(EventHandler* eventHandler) {  // 0x40
                EventHandler* prevHandler = mpEventHandler;
                mpEventHandler = eventHandler;
                return prevHandler;
            }
#endif

            virtual void setDraggingButton(u32 dragBtn);  // 0x44

        protected:
            class IDToComponent {
            public:
                IDToComponent(u32 id, GUIComponent* component) : mID(id), mpComponent(component) {}

                u32 mID;                    // 0x00
                GUIComponent* mpComponent;  // 0x04

                nw4r::ut::Link mLink;  // 0x08
            };

            EventHandler* mpEventHandler;  // 0x04
            MEMAllocator* mpAllocator;     // 0x08
            nw4r::ut::List mComponents;    // 0x0C
        };

        /* PANE GUI MANAGER */

        class PaneComponent;
        class PaneManager;

        class PaneManager : public GUIManager {
        public:
            PaneManager(EventHandler* event, MEMAllocator* allocator, const nw4r::lyt::DrawInfo* drawInfo)
                : GUIManager(event, allocator), mpDrawInfo(drawInfo) {
                mIDCounter = 0;
                nw4r::ut::List_Init(&mPaneComponents, offsetof(PaneToComponent, mLink));
            }

            virtual ~PaneManager();  // 0x08

            virtual void createLayoutScene(const nw4r::lyt::Layout& layout);  // 0x48

            virtual PaneComponent* getPaneComponentByPane(nw4r::lyt::Pane* pane);  // 0x4C

#ifdef TIGUIMANAGER_IMPLEMENTATION
            virtual const nw4r::lyt::DrawInfo* getDrawInfo();  // 0x50
            virtual void setDrawInfo(const nw4r::lyt::DrawInfo* drawInfo);  // 0x54
#else
            virtual const nw4r::lyt::DrawInfo* getDrawInfo() { return mpDrawInfo; }                   // 0x50
            virtual void setDrawInfo(const nw4r::lyt::DrawInfo* drawInfo) { mpDrawInfo = drawInfo; }  // 0x54
#endif

            virtual void setAllBoundingBoxComponentTriggerTarget(bool bEnable);  // 0x58
            void walkInChildren(nw4r::lyt::PaneList& paneList);

            void addPane_(nw4r::lyt::Pane* pane);
            PaneComponent* searchPaneComponent(const char* name);

        protected:
            class PaneToComponent {
            public:
                PaneToComponent(nw4r::lyt::Pane* pane, PaneComponent* component) : mpPane(pane), mpComponent(component) {}

                nw4r::lyt::Pane* getPane() { return mpPane; }
                const nw4r::lyt::Pane* getPane() const { return mpPane; }

                nw4r::lyt::Pane* mpPane;     // 0x00
                PaneComponent* mpComponent;  // 0x04

                nw4r::ut::Link mLink;  // 0x08
            };

            const nw4r::lyt::DrawInfo* mpDrawInfo;  // 0x18

            u16 mNumPoint;   // 0x1C
            u32 mIDCounter;  // 0x20

            nw4r::ut::List mPaneComponents;  // 0x24
        };

        class PaneComponent : public GUIComponent {
        public:
            PaneComponent(u32 id) : GUIComponent(id) { mpPane = NULL; }

            virtual ~PaneComponent();  // 0x08

            virtual void draw();  // 0x1C

            virtual bool isVisible();  // 0x50

            virtual bool contain(f32 x, f32 y);  // 0x5C

#ifdef TIGUIMANAGER_IMPLEMENTATION
            virtual void setPane(nw4r::lyt::Pane* pane);  // 0x60
#else
            virtual void setPane(nw4r::lyt::Pane* pane) { mpPane = pane; }  // 0x60
#endif
            nw4r::lyt::Pane* getPane() { return mpPane; }

            nw4r::lyt::TextBox* getTextPane() { return static_cast<nw4r::lyt::TextBox*>(mpPane); }
            nw4r::lyt::Picture* getPictPane() { return static_cast<nw4r::lyt::Picture*>(mpPane); }
            nw4r::lyt::Bounding* getBoundPane() { return static_cast<nw4r::lyt::Bounding*>(mpPane); }

        private:
            nw4r::lyt::Pane* mpPane;  // 0x9C
        };
    }  // namespace gui
}  // namespace textinput

#endif  // TEXTINPUT_GUI_MANAGER_H
