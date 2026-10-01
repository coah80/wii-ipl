#ifndef TEXTINPUT_MY_INPUT_FORM_H
#define TEXTINPUT_MY_INPUT_FORM_H

#include "tiInputForm.h"
#include "tiString.h"
#include "tiUtil.h"

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

            class ScrollButton;

            class InputForm : public textinput::InputForm {
                public:
                    typedef enum EditMode {
                        EM_Appear = 0,
                        EM_Disp,
                        EM_Edit,
                        EM_Disappear,
                        EM_Last
                    } EditMode;

                    InputForm(Manager* manager, nw4r::lyt::MultiArcResourceAccessor* resAccessor, const char* arcName,
                              EventObserver* observer, const char* subName)
                        : textinput::InputForm(manager, resAccessor, arcName, observer, subName),
                          mpMemoPane(NULL), mpMemoRootPane(NULL), mpBoundPane(NULL), mpDrawPane(NULL),
                          mfScroll(0.0f), mfScrollFrom(0.0f), mfScrollTo(0.0f), mnLine(0),
                          mDrawRect(0.0f, 0.0f, 0.0f, 0.0f), mDefaultDrawSize(0.0f, 0.0f), mDefaultBoundSize(0.0f, 0.0f),
                          mpNigaoeObserver(NULL), mpDefaultNigaoe(NULL), mpSendString(NULL),
                          mbEdited(false), mbGoodBye(false), mbEditScrollUp(false), mbEditScrollDown(false), mbCloseWithSend(false),
                          mpScrollButton(NULL), mbScrollUp(false), mbScrollDown(false), meEditMode(EM_Disp) {}

                    ~InputForm();

                    virtual void                    setScroll(f32 scroll);
                    virtual void                    setAddScroll(f32 scroll, bool up, bool down);

                    virtual f32                     getScroll() { return mfScroll; }
                    virtual f32                     getScrollFrom() { return mfScrollFrom; }
                    virtual f32                     getScrollTo() { return mfScrollTo; }

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

#ifdef MYTIINPUTFORM_IMPLEMENTATION
                    virtual void                    pure_0() = 0;
                    virtual void                    pure_1() = 0;
                    virtual void                    pure_2() = 0;
                    virtual void                    pure_3() = 0;
                    virtual void                    pure_4() = 0;
                    virtual void                    pure_5() = 0;
#endif

                    virtual void                    create(MEMAllocator* allocator, inputform::EditBuffer* editBuffer);
                    virtual void                    moveCursorUp();
                    virtual void                    moveCursorDown();
                    virtual void                    onCommand(CommandReceiver::INPUT_COMMAND command, void* arg);
                    virtual bool                    updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release, void* data);
                    virtual bool                    updateInput(textinput::input::HKBManager& hkbManager);
                    virtual void                    init();
                    virtual void                    draw();
                    virtual void                    calc();
                    virtual void                    doScroll(CommandReceiver::Scroll* scroll);
                    virtual u32                     calcCursorPos(f32 x, f32 y);
                    virtual void                    drawCursor(f32 x, f32 y);
                    virtual nw4r::math::VEC2        getScale() const;
                    virtual void                    preDraw(u32);
                    virtual void                    doLineFeed();
                    virtual void                    finishDraw(u32);
                    virtual bool                    isInScroll();
                    
                    /* For letter writing */
                    
                    void                            setEdited(bool edited)                  { mbEdited = edited; }
                    void                            setGoodBye(bool goodbye)                { mbGoodBye = goodbye; }
                    void                            setEditScrollUp(bool editScrollUp)      { mbEditScrollUp = editScrollUp; }
                    void                            setEditScrollDown(bool editScrollDown)  { mbEditScrollUp = editScrollDown; }
                    void                            setCloseWithSend(bool closeWithSend)    { mbCloseWithSend = closeWithSend; }

                    void                            setEditMode(EditMode editMode);
                    
                    bool                            isEdited()                              { return mbEdited; }
                    bool                            isGoodBye()                             { return mbGoodBye; }
                    bool                            isEditScrollUp()                        { return mbEditScrollUp; }
                    bool                            isEditScrollDown()                      { return mbEditScrollDown; }
                    bool                            isCloseWithSend()                       { return mbCloseWithSend; }

                    EditMode                        getEditMode()                           { return meEditMode; }

                    tistring::Decolated*            getSendString()                         { return mpSendString; }

                protected:
                    nw4r::lyt::Pane*        mpMemoPane;         // 0x308
                    nw4r::lyt::Pane*        mpMemoRootPane;     // 0x30C
                    nw4r::lyt::Pane*        mpBoundPane;        // 0x310
                    nw4r::lyt::Pane*        mpDrawPane;         // 0x314
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
                    util::Animation         mExScrollAnm;       // 0x3C0
                    NigaoeEventObserver*    mpNigaoeObserver;   // 0x3E0
                    GXTexObj*               mpDefaultNigaoe;    // 0x3E4
                    tistring::Decolated*    mpSendString;       // 0x3E8
                    bool                    mbEdited;           // 0x3EC
                    bool                    mbGoodBye;          // 0x3ED
                    bool                    mbEditScrollUp;     // 0x3EE
                    bool                    mbEditScrollDown;   // 0x3EF
                    bool                    mbCloseWithSend;    // 0x3F0
                    u8                      padding[3];         // 0x3F1
                    ScrollButton*           mpScrollButton;     // 0x3F4
                    bool                    mbScrollUp;         // 0x3F8
                    bool                    mbScrollDown;       // 0x3F9
                    u8                      padding2[2];        // 0x3FA
                    EditMode                meEditMode;         // 0x3FC
            };
        }
    }
    typedef extend::memo::InputForm MemoInputForm;
}

#endif // TEXTINPUT_MY_INPUT_FORM_H
