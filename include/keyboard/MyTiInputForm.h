#ifndef TEXTINPUT_MY_INPUT_FORM_H
#define TEXTINPUT_MY_INPUT_FORM_H

#include "tiInputForm.h"
#include "tiString.h"

#include <nw4r/lyt/pane.h>

#include <revolution/gx/GXStruct.h>

namespace textinput {
    namespace extend {
        namespace memo {
            class NigaoeEventObserver {
                public :
                    virtual bool    onNigaoeButton()    { return false; }
                    
                    virtual void    pointNigaoeButton() {}
                    virtual void    leftNigaoeButton()  {}
                    virtual void    moveNigaoeButton()  {}
            };

#if defined(MYTIINPUTFORM_IMPLEMENTATION) || defined(MYTILETTERFORM_IMPLEMENTATION)
            class ScrollButton;
#endif

            class InputForm : public textinput::InputForm {
                public:
                    typedef enum EditMode {
                        EM_Appear = 0,
                        EM_Disp,
                        EM_Edit,
                        EM_Disappear,
                        EM_Last
                    } EditMode;

#ifdef MYTIMANAGER_IMPLEMENTATION
                    InputForm(textinput::Manager* manager, nw4r::lyt::MultiArcResourceAccessor* multiArc,
                              const char* layoutName, EventObserver* event, const char* fontName)
                        : textinput::InputForm(manager, multiArc, layoutName, event, fontName),
                          mpMemoPane(NULL), mpMemoRootPane(NULL), mpBoundPane(NULL), mpDrawPane(NULL),
                          mfScroll(0.0f), mfScrollFrom(0.0f), mfScrollTo(0.0f), mnLine(0),
                          mDrawRect(), mDefaultDrawSize(), mDefaultBoundSize(), mExScrollAnm(),
                          mpNigaoeObserver(NULL), mpDefaultNigaoe(NULL), mpSendString(NULL),
                          mbEdited(false), mbGoodBye(false), mbEditScrollUp(false), mbEditScrollDown(false),
                          mbCloseWithSend(false), mpScrollButton(NULL), mbScrollUp(false), mbScrollDown(false),
                          meEditMode(EM_Disp) {}
#endif

                    ~InputForm();
#if defined(MYTIINPUTFORM_IMPLEMENTATION) || defined(MYTILETTERFORM_IMPLEMENTATION)
                    virtual void moveCursorUp();
                    virtual void moveCursorDown();
                    virtual void onCommand(INPUT_COMMAND command, void* data);
                    virtual void create(MEMAllocator* allocator, inputform::EditBuffer* editBuffer);
                    virtual bool updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release, void* data);
                    virtual bool updateInput(input::HKBManager& hkbManager);
                    virtual void init();
                    virtual void draw();
                    virtual void calc();
                    virtual void doScroll(Scroll* scroll);
                    virtual u32 calcCursorPos(f32 x, f32 y);
                    virtual void drawCursor(f32 x, f32 y);
                    virtual nw4r::math::VEC2 getScale() const;
                    virtual void preDraw(u32 pos);
                    virtual void doLineFeed();
                    virtual void finishDraw(u32 pos);
                    virtual bool isInScroll();
#endif

                    virtual void                    setScroll(f32 scroll);
                    virtual void                    setAddScroll(f32 scroll, bool up, bool down);

                    virtual f32                     getScroll()     { return mfScroll; }
#ifdef MYTIMANAGER_IMPLEMENTATION
                    virtual f32                     getScrollFrom();
                    virtual f32                     getScrollTo();
#else
                    virtual f32                     getScrollFrom() { return mfScrollFrom; }
                    virtual f32                     getScrollTo()   { return mfScrollTo; }
#endif

                    virtual void                    open();
                    virtual void                    close();
                    virtual bool                    isWholePaneInAnimation();

                    virtual void                    setHeaderCaption(const wchar_t* headerCaption);
                    virtual void                    setMiiName(const wchar_t* miiName);
                    virtual void                    setTouchLetterCaption(const wchar_t* letterCaption);

                    virtual void                    onNigaoeButtonTrig();
                    virtual void                    onNigaoeButtonPoint();
                    virtual void                    onNigaoeButtonLeft();
                    virtual void                    setDefaultNigaoe();

                    virtual void                    onArrowRPoint();
                    virtual void                    onArrowRLeft();
                    virtual void                    onArrowLPoint();
                    virtual void                    onArrowLLeft();
                    virtual void                    onArrowRTrig();
                    virtual void                    onArrowLTrig();
                    
                    virtual void                    setNigaoeEventObserver(NigaoeEventObserver* nigaoeObserver) { mpNigaoeObserver = nigaoeObserver; }
                    virtual nw4r::lyt::Pane*        getNigaoePane();
                    virtual nw4r::lyt::Material*    getNigaoePaneMaterial();

                    virtual f32                     getDrawBoxHeight();

                    virtual f32                     getScrollMin();
                    virtual f32                     getScrollMax();

                    virtual void                    beginDraw(const nw4r::ut::Rect& rect);
                    virtual void                    put(wchar_t ch);

                    virtual void                    createAnimation(MEMAllocator* allocator);

                    virtual void                    drawHeader();
                    virtual void                    drawBody();
                    virtual void                    drawFooter();

                    virtual void                    onCommandOnDispMode(INPUT_COMMAND command, void* arg);
                    virtual void                    onCommandOnEditMode(INPUT_COMMAND command, void* arg);

                    virtual void                    doAutoScroll();
                    
                    /* For letter writing */
                    
                    void                            setEdited(bool edited)                  { mbEdited = edited; }
                    void                            setGoodBye(bool goodbye)                { mbGoodBye = goodbye; }
                    void                            setEditScrollUp(bool editScrollUp)      { mbEditScrollUp = editScrollUp; }
                    void                            setEditScrollDown(bool editScrollDown)  { mbEditScrollUp = editScrollDown; }
                    void                            setCloseWithSend(bool closeWithSend)    { mbCloseWithSend = closeWithSend; }

#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(MYTIINPUTFORM_IMPLEMENTATION) || defined(MYTILETTERFORM_IMPLEMENTATION)
                    void                            setEditMode(EditMode editMode);
#else
                    void                            setEditMode(EditMode editMode)          { meEditMode = editMode; }
#endif
                    
                    bool                            isEdited()                              { return mbEdited; }
                    bool                            isGoodBye()                             { return mbGoodBye; }
                    bool                            isEditScrollUp()                        { return mbEditScrollUp; }
                    bool                            isEditScrollDown()                      { return mbEditScrollDown; }
                    bool                            isCloseWithSend()                       { return mbCloseWithSend; }

                    EditMode                        getEditMode()                           { return meEditMode; }

                    tistring::Decolated*            getSendString()                         { return mpSendString; }

#ifdef MYTILETTERFORM_IMPLEMENTATION
                protected:
#else
                private:
#endif
#if defined(MYTIINPUTFORM_IMPLEMENTATION) || defined(MYTILETTERFORM_IMPLEMENTATION)
                    nw4r::lyt::Pane* mpMemoPane;
                    nw4r::lyt::Pane* mpMemoRootPane;
                    nw4r::lyt::Pane* mpBoundPane;
                    nw4r::lyt::Pane* mpDrawPane;
#else
#ifdef MYTIMANAGER_IMPLEMENTATION
                    undefined4*             mpMemoPane;
#endif
                    undefined4*             mpMemoRootPane;
                    undefined4*             mpBoundPane;
                    undefined4*             mpDrawPane;
#endif
                    f32                     mfScroll;           // 0x318
                    f32                     mfScrollFrom;       // 0x31C
                    f32                     mfScrollTo;         // 0x320
                    int                     mnLine;             // 0x324
                    nw4r::ut::Rect          mDrawRect;          // 0x328
                    nw4r::math::VEC3        mDefaultDrawTrans;  // 0x338
                    nw4r::lyt::Size         mDefaultDrawSize;   // 0x344
                    nw4r::math::VEC3        mDefaultBoundTrans; // 0x34C
                    nw4r::lyt::Size         mDefaultBoundSize;  // 0x358
                    Mtx                     mDrawMtx;           // 0x360
                    Mtx                     mBoundMtx;          // 0x390
#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(MYTIINPUTFORM_IMPLEMENTATION) || defined(MYTILETTERFORM_IMPLEMENTATION)
                    util::Animation         mExScrollAnm;       // 0x3C0
#else
                    u8 /*todo*/             mExScrollAnm[32];   // 0x3C0
#endif
                    NigaoeEventObserver*    mpNigaoeObserver;   // 0x3E0
                    GXTexObj*               mpDefaultNigaoe;    // 0x3E4
                    tistring::Decolated*    mpSendString;       // 0x3E8
                    bool                    mbEdited;           // 0x3EC
                    bool                    mbGoodBye;          // 0x3ED
                    bool                    mbEditScrollUp;     // 0x3EE
                    bool                    mbEditScrollDown;   // 0x3EF
                    bool                    mbCloseWithSend;    // 0x3F0
                    u8                      padding[3];         // 0x3F1
#if defined(MYTIINPUTFORM_IMPLEMENTATION) || defined(MYTILETTERFORM_IMPLEMENTATION)
                    ScrollButton* mpScrollButton;
#else
                    undefined4*             mpScrollButton;
#endif
                    bool                    mbScrollUp;         // 0x3F8
                    bool                    mbScrollDown;       // 0x3F9
                    EditMode                meEditMode;         // 0x3FC
            };
        }
    }
    typedef extend::memo::InputForm MemoInputForm;
}

#endif // TEXTINPUT_MY_INPUT_FORM_H
