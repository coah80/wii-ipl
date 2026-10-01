// Matching build uses MyTiInputForm.s (C++ Matching breaks DOL SHA1).
#define MYTIINPUTFORM_IMPLEMENTATION
#include "keyboard/MyTiInputForm.h"
#include "keyboard/tiUtil.h"
#include <nw4r/lyt/group.h>
#include <nw4r/lyt/material.h>
#include <nw4r/lyt/textbox.h>
#include <new>

namespace textinput {
namespace inputform {
class EventHandler : public nw4rmanager::TiEventHandler {
public:
    EventHandler(textinput::InputForm* form) : mpInputForm(form) {}
    virtual ~EventHandler() {}
    virtual void onTiEvent(gui::PaneComponent*, u32, Input*);
protected:
    textinput::InputForm* mpInputForm;
};
}
namespace extend {
namespace memo {

class EventHandler : public inputform::EventHandler {
public:
    EventHandler(InputForm* form) : inputform::EventHandler(form), mpMemoForm(form) {}
    virtual ~EventHandler() {}
    virtual void onTiEvent(gui::PaneComponent*, u32, Input*);
private:
    InputForm* mpMemoForm;
};


class AnmPane : public nw4rmanager::AnmPane {
protected:
    AnmPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer)
        : nw4rmanager::AnmPane(pane, observer), meState(0) {}
public:
    virtual ~AnmPane();
    virtual void init();
    virtual void changeAnimation(u32 id);
    virtual u32 getKeyType() const;
    virtual u32 getState();
protected:
    u32 meState;
    u32 meKeyType;
};

class WholePane : public AnmPane {
public:
    WholePane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer) : AnmPane(pane, observer) { meKeyType = 0; }
    virtual ~WholePane() {}
    virtual void onAnmEvent(AnmPaneEvent event);
};

class NigaoePane : public AnmPane {
public:
    NigaoePane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer) : AnmPane(pane, observer) { meKeyType = 1; }
    virtual ~NigaoePane() {}
    virtual void onAnmEvent(AnmPaneEvent event);
};


class ScrollButton {
public:
    ScrollButton(TiLayout* layout) : muGroup(0), muAnimation(0), mpLayout(layout), mbLeftPressed(false), mbRightPressed(false) {}
    virtual void create(MEMAllocator*, nw4r::lyt::MultiArcResourceAccessor*);
    virtual void init();
    virtual void calc();
    virtual void changeAnimation(bool left, u32 id);
private:
    u32 muGroup;
    u32 muAnimation;
    TiLayout* mpLayout;
    nw4rmanager::AnimPaneGroup* mGroups[9];
    bool mbGroupChanged[9];
    bool mbLeftPressed;
    bool mbRightPressed;
};


class SimpleAnmPane : public nw4rmanager::AnmPane {
public:
    SimpleAnmPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer) : nw4rmanager::AnmPane(pane, observer) {}
    virtual ~SimpleAnmPane() {}
    virtual void init();
    virtual void changeAnimation(u32 id);
};


static const char* scPaneName[] = {
    "N_Header", "N_Body", "B_Body", "N_Footer", "Nigaoe",
    "T_Nigaoe", "B_Nigaoe", "T_Letter", "T_TouchLetter"
};

struct AnimationFile {
    u32 id;
    char name[64];
};
static const AnimationFile csAninationFile[] = {
    {0, "my_Memo_a_normal.brlan"},
    {1, "my_Memo_a_MailIn.brlan"},
    {2, "my_Memo_a_MailOut.brlan"},
    {3, "my_Memo_a_SendOut.brlan"},
    {4, "my_Memo_a_NigaoeFoucusIn.brlan"},
    {5, "my_Memo_a_NigaoeFoucusOut.brlan"}
};
struct PaneAnimations {
    u32 type;
    const char* paneName;
    u32 count;
    const AnimationFile* animations[12];
};
static const PaneAnimations csPaneToAnimation[] = {
    {0, "N_Memo", 4, {&csAninationFile[0], &csAninationFile[1], &csAninationFile[2], &csAninationFile[3]}},
    {1, "Nigaoe", 2, {&csAninationFile[4], &csAninationFile[5]}}
};
static const AnimationFile csGroupAninationFile[] = {
    {0, "my_Memo_a_Off.brlan"},
    {1, "my_Memo_a_Appear.brlan"},
    {2, "my_Memo_a_Lost.brlan"},
    {3, "my_Memo_a_HDActionEnd.brlan"},
    {4, "my_Memo_a_HDActionStart.brlan"},
    {5, "my_Memo_a_Loop.brlan"},
    {6, "my_Memo_a_Select.brlan"},
    {7, "my_Memo_a_FocusOff.brlan"},
    {8, "my_Memo_a_FocusOn.brlan"}
};
struct GroupAnimations {
    u32 group;
    u32 animations[3];
};
static const GroupAnimations csGroupToAnimation[] = {
    {0, {5, 9, 9}}, {1, {8, 7, 9}}, {2, {8, 7, 9}},
    {3, {6, 9, 9}}, {4, {6, 9, 9}}, {5, {2, 1, 9}},
    {6, {2, 1, 9}}, {7, {4, 3, 9}}, {8, {4, 3, 9}}
};

InputForm::~InputForm() {
    mpSendString->~Decolated();
    MEMFreeToAllocator(mpAllocator, mpSendString);
    MEMFreeToAllocator(mpAllocator, mpDefaultNigaoe);
}

void InputForm::setAddScroll(f32 scroll, bool up, bool down) {
    setScroll(mfScroll + scroll);
    if (up && !mbScrollUp) {
        mpScrollButton->changeAnimation(false, 4);
    } else if (down && !mbScrollDown) {
        mpScrollButton->changeAnimation(true, 4);
    }
    if (!up && mbScrollUp) {
        mpScrollButton->changeAnimation(false, 3);
    } else if (!down && mbScrollDown) {
        mpScrollButton->changeAnimation(true, 3);
    }
    mbScrollUp = up;
    mbScrollDown = down;
}

void InputForm::moveCursorUp() {
    f32 y = 1.0f + (mfCursorY - getLineHeight());
    if (y <= 0.0f) {
        u32 start, end;
        mpString->getCursorPos(&start, &end);
        if (start == 0 && end == 0) onSE(sound::SE_CHAR_CURSOR_FIX);
        else onSE(sound::SE_CHAR_CURSOR);
        setCursorPos(mpString, 0);
    } else {
        setCursorPos(mpString, calcCursorPos(mfCursorX, y - mfScroll));
        onSE(sound::SE_CHAR_CURSOR);
    }
    meScrollFlag = SF_ScrollOn;
}

void InputForm::moveCursorDown() {
    f32 y = 1.0f + (mfCursorY + getLineHeight());
    if (y / getLineHeight() >= getLine()) {
        u32 start, end;
        mpString->getCursorPos(&start, &end);
        if (start == mpString->getLength() && end == mpString->getLength()) onSE(sound::SE_CHAR_CURSOR_FIX);
        else onSE(sound::SE_CHAR_CURSOR);
        setCursorPos(mpString, mpString->getLength());
    } else {
        setCursorPos(mpString, calcCursorPos(mfCursorX, y - mfScroll));
        onSE(sound::SE_CHAR_CURSOR);
    }
    meScrollFlag = SF_ScrollOn;
}

void InputForm::onCommand(INPUT_COMMAND command, void* data) {
    if (meEditMode == EM_Edit) onCommandOnEditMode(command, data);
    else if (meEditMode == EM_Disp) onCommandOnDispMode(command, data);
    else {
        switch (command) {
        case 6: case 21: case 29: case 31:
            textinput::InputForm::onCommand(command, data);
            break;
        case 7: case 8: case 9: case 10: case 11: case 12: case 13:
        case 14: case 15: case 16: case 17: case 18: case 19: case 20:
        case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 30:
            break;
        }
    }
}

void InputForm::onCommandOnEditMode(INPUT_COMMAND command, void* data) {
    switch (command) {
    case 24:
        if (!mExScrollAnm.isActive()) {
            if (static_cast<Scroll*>(data)->y < 0.0f)
                mExScrollAnm.startAnm(NULL, mfScroll, mfScroll + getLineHeight(), 15.0f, NULL);
            else
                mExScrollAnm.startAnm(NULL, mfScroll, mfScroll - getLineHeight(), 15.0f, NULL);
            onSE(sound::SE_LINE_SCROLL);
        }
        break;
    default:
        textinput::InputForm::onCommand(command, data);
        break;
    }
}

void InputForm::onCommandOnDispMode(INPUT_COMMAND command, void* data) {
    switch (command) {
    case 14: {
        nw4r::math::VEC2 position = getGlobalLeftTopPos();
        nw4r::math::VEC2* point = static_cast<nw4r::math::VEC2*>(data);
        int line = (point->y - position.y) / getLineHeight();
        if (line > getLine() - 1) line = getLine() - 1;
        if (getLine() > 1 && line >= getLine() - 1) line = getLine() - 2;
        mfScrollFrom = mfScroll;
        mfScrollTo = line * getLineHeight();
        nw4r::math::VEC2 editPoint;
        editPoint.x = point->x;
        editPoint.y = point->y - mfScroll;
        textinput::InputForm::onCommand(static_cast<INPUT_COMMAND>(14), &editPoint);
        int relationLine = line;
        struct Relation { int type; int* line; } relation = {0, &relationLine};
        textinput::InputForm::onCommand(INPUT_COMMAND_37, &relation);
        mbEdited = true;
        candidatebox::CandidateBoxCaller::resetCandidate();
        candidatebox::CandidateBoxCaller::makeEmptyCandidate();
        break;
    }
    case 29: case 31: case 41:
        textinput::InputForm::onCommand(command, data);
        break;
    }
}

void InputForm::create(MEMAllocator* allocator, inputform::EditBuffer* editBuffer) {
    textinput::InputForm::create(allocator, editBuffer);
    void* stringMemory = MEMAllocFromAllocator(allocator, sizeof(tistring::Decolated));
    mpSendString = new (stringMemory) tistring::Decolated(1024);
    mpSendString->create(allocator);
    MEMFreeToAllocator(allocator, mpInputEventHandler);
    void* handlerMemory = MEMAllocFromAllocator(allocator, sizeof(EventHandler));
    mpInputEventHandler = new (handlerMemory) EventHandler(this);
    mpInputEventHandler->setEventObserver(mpEventObserver);
    mpPaneManager->changeEventHandler(mpInputEventHandler);
    mpDefaultNigaoe = static_cast<GXTexObj*>(MEMAllocFromAllocator(allocator, sizeof(GXTexObj)));
    getNigaoePaneMaterial()->GetTexture(mpDefaultNigaoe, 0);
    setVisible("P_2l_TextBox", true);
    mpBoundPane = mpLayout->GetRootPane()->FindPaneByName("T_2l_TextBox", true);
    mDefaultBoundTrans = mpBoundPane->GetTranslate();
    mDefaultBoundSize = mpBoundPane->GetSize();
    mpDrawPane = mpLayout->GetRootPane()->FindPaneByName("B_2l_TextBox", true);
    mpPaneManager->getPaneComponentByPane(mpDrawPane)->setTriggerTarget(false);
    mDrawRect = mpDrawPane->GetPaneRect(mDrawInfo);
    mDefaultDrawTrans = mpDrawPane->GetTranslate();
    mDefaultDrawSize = mpDrawPane->GetSize();
    mpMemoPane = mpLayout->GetRootPane()->FindPaneByName("N_Memo", true);
    mpMemoRootPane = mpLayout->GetRootPane()->FindPaneByName("N_MemoRoot", true);
    setScroll(0.0f);
    mnLine = 1;
    mfScrollFrom = 0.0f;
    mfScrollTo = 0.0f;
    PSMTXIdentity(mDrawMtx);
    PSMTXIdentity(mBoundMtx);
    createAnimation(allocator);
    void* scrollMemory = MEMAllocFromAllocator(allocator, sizeof(ScrollButton));
    mpScrollButton = new (scrollMemory) ScrollButton(mpLayout);
    mpScrollButton->create(allocator, mpMultiArcResourceAccessor);
}

void InputForm::createAnimation(MEMAllocator* allocator) {
    for (u16 i = 0; i < 2; i++) {
        const PaneAnimations& entry = csPaneToAnimation[i];
        AnmPane* pane = NULL;
        switch (entry.type) {
        case 0: {
            void* memory = MEMAllocFromAllocator(allocator, sizeof(WholePane));
            pane = new (memory) WholePane(getPane(entry.paneName), NULL);
            break;
        }
        case 1: {
            void* memory = MEMAllocFromAllocator(allocator, sizeof(NigaoePane));
            pane = new (memory) NigaoePane(getPane(entry.paneName), NULL);
            break;
        }
        }
        nw4r::ut::List_Append(&mAnmPanes, pane);
        for (u16 j = 0; j < entry.count; j++) {
            const void* resource = mpMultiArcResourceAccessor->GetResource(0, entry.animations[j]->name, NULL);
            AnimTransformPane* transform = static_cast<AnimTransformPane*>(getLayout()->CreateAnimTransform(resource, mpMultiArcResourceAccessor));
            pane->addAnimation(allocator, entry.animations[j]->id, transform, false, true);
        }
    }
}

AnmPane::~AnmPane() {}

static const char* csGroupName[] = {
    "G_ArwRoop", "G_ArwR_Focus", "G_ArwL_Focus", "G_ArwR_Ac", "G_ArwL_Ac",
    "G_ArwL_End", "G_ArwR_End", "G_ArwL_HDAc", "G_ArwR_HDAc"
};

void ScrollButton::create(MEMAllocator* allocator, nw4r::lyt::MultiArcResourceAccessor* accessor) {
    for (int i = 0; i < 9; i++) {
        mbGroupChanged[i] = false;
        nw4r::lyt::Group* group = mpLayout->GetGroupContainer()->FindGroupByName(csGroupName[i]);
        void* groupMemory = MEMAllocFromAllocator(allocator, sizeof(nw4rmanager::AnimPaneGroup));
        mGroups[i] = new (groupMemory) nw4rmanager::AnimPaneGroup(group);
        nw4r::lyt::PaneLinkList& panes = group->GetPaneList();
        for (nw4r::lyt::PaneLinkList::Iterator it = panes.GetBeginIter(); it != panes.GetEndIter(); ++it) {
            void* memory = MEMAllocFromAllocator(allocator, sizeof(SimpleAnmPane));
            SimpleAnmPane* pane = new (memory) SimpleAnmPane(it->mTarget, NULL);
            for (u16 j = 0; j < 3; j++) {
                int id = csGroupToAnimation[i].animations[j];
                if (id != 9) {
                    const void* resource = accessor->GetResource(0, csGroupAninationFile[id].name, NULL);
                    AnimTransformPane* transform = static_cast<AnimTransformPane*>(mpLayout->CreateAnimTransform(resource, accessor));
                    bool loop = false;
                    if (id == 5) loop = true;
                    pane->addAnimation(allocator, id, transform, loop, false);
                }
            }
            mGroups[i]->addAnimPane(pane);
        }
    }
    changeAnimation(true, 5);
    changeAnimation(false, 5);
    changeAnimation(true, 2);
    changeAnimation(false, 2);
    for (int i = 0; i < 10; i++) calc();
}

void ScrollButton::calc() {
    for (int i = 0; i < 9; i++) mGroups[i]->calc();
}

void ScrollButton::changeAnimation(bool left, u32 id) {
    muAnimation = id;
    if (left) {
        switch (id) {
        case 0: muGroup = 0; break;
        case 1: muGroup = 5; break;
        case 2: muGroup = 5; break;
        case 3: if (!mbLeftPressed) return; muGroup = 8; mbLeftPressed = false; break;
        case 4: if (mbLeftPressed) return; muGroup = 8; mbLeftPressed = true; break;
        case 5: muGroup = 0; break;
        case 6: muGroup = 4; break;
        case 7: muGroup = 2; break;
        case 8: muGroup = 2; break;
        }
    } else {
        switch (id) {
        case 0: muGroup = 0; break;
        case 1: muGroup = 6; break;
        case 2: muGroup = 6; break;
        case 3: if (!mbRightPressed) return; muGroup = 7; mbRightPressed = false; break;
        case 4: if (mbRightPressed) return; muGroup = 7; mbRightPressed = true; break;
        case 5: muGroup = 0; break;
        case 6: muGroup = 3; break;
        case 7: muGroup = 1; break;
        case 8: muGroup = 1; break;
        }
    }
    mbGroupChanged[muGroup] = true;
    mGroups[muGroup]->changeAnimation(id);
}

void InputForm::onArrowRPoint() {
    if (meEditMode == EM_Disp) {
        mpScrollButton->changeAnimation(false, 8);
        onSE(sound::SE_BT_TARGETTING);
    }
}
void InputForm::onArrowRLeft() {
    if (meEditMode == EM_Disp) mpScrollButton->changeAnimation(false, 7);
}
void InputForm::onArrowLPoint() {
    if (meEditMode == EM_Disp) {
        mpScrollButton->changeAnimation(true, 8);
        onSE(sound::SE_BT_TARGETTING);
    }
}
void InputForm::onArrowLLeft() {
    if (meEditMode == EM_Disp) mpScrollButton->changeAnimation(true, 7);
}
void InputForm::onArrowRTrig() {
    if (meEditMode == EM_Disp && !mExScrollAnm.isActive()) {
        mpScrollButton->changeAnimation(false, 6);
        f32 scroll = mfScroll - 3.0f * getLineHeight();
        if (scroll <= getScrollMin()) scroll = getScrollMin();
        mExScrollAnm.startAnm(NULL, mfScroll, scroll, 15.0f, NULL);
        onSE(sound::SE_LINE_SCROLL);
    }
}
void InputForm::onArrowLTrig() {
    if (meEditMode == EM_Disp && !mExScrollAnm.isActive()) {
        mpScrollButton->changeAnimation(true, 6);
        f32 scroll = mfScroll + 3.0f * getLineHeight();
        if (scroll >= getScrollMax()) scroll = getScrollMax();
        mExScrollAnm.startAnm(NULL, mfScroll, scroll, 15.0f, NULL);
        onSE(sound::SE_LINE_SCROLL);
    }
}

bool InputForm::updateInput(int chan, f32 x, f32 y, u32 trig, u32 hold, u32 release, void* data) {
    if (meEditMode == EM_Disp) {
        if (hold & 0x400) return textinput::InputForm::updateInput(chan, 0.0f, 0.0f, 0, 0, 0, data);
        if (trig & 8) mpScrollButton->changeAnimation(false, 4);
        if (release & 8) mpScrollButton->changeAnimation(false, 3);
        if (trig & 4) mpScrollButton->changeAnimation(true, 4);
        if (release & 4) mpScrollButton->changeAnimation(true, 3);
        if (hold & 8) {
            if (getScrollMin() <= mfScroll) {
                setScroll(mfScroll - 3.5f);
                if (mfScroll <= getScrollMin()) setScroll(getScrollMin());
                else onSE(sound::SE_MESSAGE_SCROLL);
            }
            mpScrollButton->changeAnimation(false, 4);
        } else mpScrollButton->changeAnimation(false, 3);
        if (hold & 4) {
            if (getScrollMax() >= mfScroll) {
                setScroll(3.5f + mfScroll);
                if (mfScroll >= getScrollMax()) setScroll(getScrollMax());
                else onSE(sound::SE_MESSAGE_SCROLL);
            }
            mpScrollButton->changeAnimation(true, 4);
        } else mpScrollButton->changeAnimation(true, 3);
    }
    return textinput::InputForm::updateInput(chan, x, y, trig, hold, release, data);
}

bool InputForm::updateInput(input::HKBManager& hkbManager) {
    return textinput::InputForm::updateInput(hkbManager);
}

void InputForm::init() {
    if (mpBoundPane != NULL) mCharColor.Set(20, 20, 20, 255);
    mbUpVisible = false;
    mbDownVisible = false;
    searchAnmPane("P_txtScrll_UP")->changeAnimation(7);
    searchAnmPane("P_txtScrll_DOWN")->changeAnimation(7);
    mbGoodBye = false;
    mbEditScrollUp = false;
    mbEditScrollDown = false;
    setScroll(0.0f);
    mfScrollFrom = 0.0f;
    mfScrollTo = 0.0f;
    resetRelation();
    updateCandidateState_();
    setLineDrawInfo(true, 10);
}

void InputForm::draw() {
    setProjectionMtx();
    drawHeader();
    drawBody();
    drawFooter();
    if (meEditMode == EM_Edit) getPane("N_txt_scrl")->Draw(mDrawInfo);
    inputform::Base::draw();
    if (meEditMode == EM_Disp) {
        setProjectionMtx();
        getPane("N_TopBtn_00")->Animate(0);
        getPane("N_TopBtn_00")->CalculateMtx(mDrawInfo);
        getPane("N_TopBtn_00")->Draw(mDrawInfo);
    }
    mnLine = getLine();
    if (mnLine <= 4) mnLine = 4;
}

void InputForm::setScroll(f32 scroll) {
    mfScroll = scroll;
    mfDrawScrollY = meEditMode == EM_Edit ? -mfScroll : 0.0f;
}

static nw4r::math::VEC2 transformedOrigin(const nw4r::ut::Rect& rect, const Mtx& matrix) {
    nw4r::math::VEC3 position;
    position.x = rect.left;
    position.y = rect.bottom;
    position.z = 0.0f;
    PSMTXMultVec(matrix, reinterpret_cast<const Vec*>(&position), reinterpret_cast<Vec*>(&position));
    return nw4r::math::VEC2(position.x, -position.y);
}

void InputForm::calc() {
    nw4rmanager::Layout::calc();
    muGlobalAlpha = getLayout()->GetRootPane()->GetAlpha();
    mpLayout->Animate(0);
    mpLayout->CalculateMtx(mDrawInfo);
    mpLayout->GetRootPane()->FindPaneByName("N_Memo", true)->SetTranslate(nw4r::math::VEC2(0.0f, mfScroll));
    f32 height = mnLine * getLineHeight();
    f32 drawY = mDefaultDrawTrans.y - (height - mDefaultDrawSize.height) / 2.0f;
    mpDrawPane->SetSize(nw4r::lyt::Size(mpDrawPane->GetSize().width, height));
    mpDrawPane->SetTranslate(nw4r::math::VEC2(mDefaultDrawTrans.x, drawY));
    mpDrawPane->CalculateMtx(mDrawInfo);
    AdjustPaneMtx(mDrawMtx, mDrawInfo, mpDrawPane->GetGlobalMtx());
    nw4r::ut::Rect rect;
    rect = mpDrawPane->GetPaneRect(mDrawInfo);
    nw4r::math::VEC2 scale(getScale().x, 1.0f);
    nw4r::math::VEC2 position = transformedOrigin(rect, mDrawMtx);
    mDrawRect.left = position.x;
    mDrawRect.bottom = position.y;
    mDrawRect.right = position.x + scale.x * (rect.right - rect.left);
    mDrawRect.top = position.y + scale.y * (rect.top - rect.bottom);
    height = mnLine * getLineHeight();
    f32 halfHeight = height - mDefaultBoundSize.height;
    halfHeight *= 0.5f;
    f32 boundY = mDefaultBoundTrans.y - halfHeight;
    if (meEditMode == EM_Edit) {
        height = 2.0f * getLineHeight();
        boundY = (mDefaultBoundTrans.y - (height - mDefaultBoundSize.height) / 2.0f) - mfScroll;
    } else mfDrawScrollY = 0.0f;
    mpBoundPane->SetSize(nw4r::lyt::Size(mpBoundPane->GetSize().width, height));
    mpBoundPane->SetTranslate(nw4r::math::VEC2(mDefaultBoundTrans.x, boundY));
    mpBoundPane->CalculateMtx(mDrawInfo);
    AdjustPaneMtx(mBoundMtx, mDrawInfo, mpBoundPane->GetGlobalMtx());
    AdjustPaneMtx(mMtx.m, mDrawInfo, mpBoundPane->GetGlobalMtx());
    mRect = mpBoundPane->GetPaneRect(mDrawInfo);
    muGlobalAlpha = mpBoundPane->GetAlpha();
    mExScrollAnm.calc();
    if (mExScrollAnm.isActive()) {
        setScroll(mExScrollAnm.getValue());
    } else if (meEditMode == EM_Edit) {
        doAutoScroll();
        if (!mExScrollAnm.isActive()) {
            f32 halfLine = getLineHeight();
            halfLine *= 0.5f;
            if (mfScroll - halfLine > 0.0f) {
                if (!mbUpVisible) {
                    searchAnmPane("P_txtScrll_UP")->changeAnimation(5);
                    mpPaneManager->getPaneComponentByPane(getPane("B_txtScrll_UP"))->init();
                }
                mbUpVisible = true;
            } else {
                if (mbUpVisible) searchAnmPane("P_txtScrll_UP")->changeAnimation(6);
                mbUpVisible = false;
            }
            f32 textHeight = getLine() * getLineHeight();
            f32 lowerHalfLine = getLineHeight();
            lowerHalfLine *= 0.5f;
            f32 lowerEdge = mfScroll + height;
            lowerEdge += lowerHalfLine;
            if (lowerEdge < textHeight) {
                if (!mbDownVisible) {
                    searchAnmPane("P_txtScrll_DOWN")->changeAnimation(5);
                    mpPaneManager->getPaneComponentByPane(getPane("B_txtScrll_DOWN"))->init();
                }
                mbDownVisible = true;
            } else {
                if (mbDownVisible) searchAnmPane("P_txtScrll_DOWN")->changeAnimation(6);
                mbDownVisible = false;
            }
        }
    } else {
        mbUpVisible = false;
    mbDownVisible = false;
        searchAnmPane("P_txtScrll_UP")->changeAnimation(7);
        searchAnmPane("P_txtScrll_DOWN")->changeAnimation(7);
        getPane("N_txt_scrl")->Animate(0);
        getPane("N_txt_scrl")->CalculateMtx(mDrawInfo);
    }
    nw4r::lyt::Pane* scrollPane = getPane("N_txt_scrl");
    scrollPane->SetTranslate(nw4r::math::VEC2(scrollPane->GetTranslate().x, 0.0f));
    if (meEditMode == EM_Disp) {
        mpScrollButton->calc();
        if (!mbGoodBye) {
            if (mbEditScrollUp && getScrollMin() >= mfScroll) {
                mbEditScrollUp = false;
                mpScrollButton->changeAnimation(false, 2);
            } else if (!mbEditScrollUp && getScrollMin() < mfScroll) {
                mbEditScrollUp = true;
                mpScrollButton->changeAnimation(false, 1);
            }
            if (mbEditScrollDown && getScrollMax() <= mfScroll) {
                mbEditScrollDown = false;
                mpScrollButton->changeAnimation(true, 2);
            }
            if (!mbEditScrollDown && getScrollMax() > mfScroll) {
                mbEditScrollDown = true;
                mpScrollButton->changeAnimation(true, 1);
            }
            if (mpNigaoeObserver != NULL) mpNigaoeObserver->moveNigaoeButton();
        }
    }
    calcCursorTimer();
}

void InputForm::doAutoScroll() {
    if (!mExScrollAnm.isActive() && (meScrollFlag == SF_ScrollOn || meScrollFlag == SF_ScrollByBS)) {
        if (meEditMode == EM_Edit) {
            f32 lineHeight = getLineHeight();
            lineHeight *= 0.5f;
            f32 cursorBottom = mfCursorY + lineHeight;
            if (mfScroll > cursorBottom) {
                int lines = (mfScroll - mfCursorY) / getLineHeight();
                mExScrollAnm.startAnm(NULL, mfScroll, mfScroll - lines * getLineHeight(), 15.0f, NULL);
                onSE(sound::SE_LINE_SCROLL);
            }
            if (mfScroll + 2.0f * getLineHeight() < cursorBottom) {
                f32 lineHeight = getLineHeight();
                int lines = static_cast<int>((cursorBottom - (mfScroll + 2.0f * getLineHeight())) / lineHeight) + 1;
                mExScrollAnm.startAnm(NULL, mfScroll, mfScroll + lines * getLineHeight(), 15.0f, NULL);
                onSE(sound::SE_LINE_SCROLL);
            }
        }
        meScrollFlag = SF_NoScroll;
    }
}

void InputForm::beginDraw(const nw4r::ut::Rect&) {
    if (mDrawRect.left == mDrawRect.right) mDrawRect.right += 0.1f;
    if (mDrawRect.top == mDrawRect.bottom) mDrawRect.top += 0.1f;
    textdrawer::Base::beginDraw(mDrawRect);
}
void InputForm::doScroll(Scroll*) {}

u32 InputForm::calcCursorPos(f32 x, f32 y) {
    u32 lines = getLine();
    if (lines > muLimitRowNum) lines = muLimitRowNum;
    f32 lineHeight = getLineHeight();
    f32 cursorY = y + mfScroll;
    if (cursorY > lines * lineHeight) return inputform::Base::calcCursorPos(x, lines * getLineHeight());
    return inputform::Base::calcCursorPos(x, cursorY);
}
void InputForm::drawCursor(f32 x, f32 y) {
    if (meEditMode != EM_Disp) inputform::Base::drawCursor(x, y);
}
nw4r::math::VEC2 InputForm::getScale() const {
    if (mpMemoRootPane == NULL) return nw4r::math::VEC2(1.0f, 1.0f);
    return mpMemoRootPane->GetScale();
}

void InputForm::drawHeader() {
    getPane(scPaneName[0])->Draw(mDrawInfo);
    getPane("Nigaoe")->Draw(mDrawInfo);
    getPane("T_Nigaoe")->Draw(mDrawInfo);
}
void InputForm::drawBody() {
    nw4r::lyt::Pane* body = getPane(scPaneName[1]);
    f32 y = 0.0f;
    for (int i = 0; i < mnLine; i++) {
        body->SetTranslate(nw4r::math::VEC2(0.0f, y));
        body->CalculateMtx(mDrawInfo);
        body->Draw(mDrawInfo);
        y -= body->GetSize().height;
    }
    if (!mbEdited) getPane("T_TouchLetter")->Draw(mDrawInfo);
}
void InputForm::drawFooter() {
    f32 y = (mnLine - 1) * (-1.0f * getPane(scPaneName[1])->GetSize().height);
    nw4r::lyt::Pane* footer = getPane(scPaneName[3]);
    footer->SetTranslate(nw4r::math::VEC2(0.0f, y));
    footer->CalculateMtx(mDrawInfo);
    footer->Draw(mDrawInfo);
}

void InputForm::open() {
    setScroll(0.0f);
    mfScrollFrom = 0.0f;
    mfScrollTo = 0.0f;
    mpLayout->GetRootPane()->SetTranslate(nw4r::math::VEC2(0.0f, 0.0f));
    searchAnmPane("N_Memo")->changeAnimation(1);
    searchAnmPane("P_txtScrll_UP")->changeAnimation(7);
    searchAnmPane("P_txtScrll_DOWN")->changeAnimation(7);
}
void InputForm::close() {
    if (!mbCloseWithSend) searchAnmPane("N_Memo")->changeAnimation(2);
    else searchAnmPane("N_Memo")->changeAnimation(3);
    if (mbEditScrollUp) {
        mpScrollButton->changeAnimation(false, 2);
        mbEditScrollUp = false;
    }
    if (mbEditScrollDown) {
        mpScrollButton->changeAnimation(true, 2);
        mbEditScrollDown = false;
    }
    mbGoodBye = true;
}
bool InputForm::isWholePaneInAnimation() {
    return searchAnmPane("N_Memo")->isInAnimation();
}
void InputForm::setHeaderCaption(const wchar_t* caption) {
    static_cast<nw4r::lyt::TextBox*>(mpLayout->GetRootPane()->FindPaneByName("T_Header", true))->SetString(caption, 0);
}
void InputForm::setMiiName(const wchar_t* name) {
    static_cast<nw4r::lyt::TextBox*>(mpLayout->GetRootPane()->FindPaneByName("T_Nigaoe", true))->SetString(name, 0);
}
void InputForm::setTouchLetterCaption(const wchar_t* caption) {
    static_cast<nw4r::lyt::TextBox*>(mpLayout->GetRootPane()->FindPaneByName("T_TouchLetter", true))->SetString(caption, 0);
    mbEdited = false;
}
nw4r::lyt::Pane* InputForm::getNigaoePane() {
    return getPane("Nigaoe");
}
nw4r::lyt::Material* InputForm::getNigaoePaneMaterial() {
    return getPane("Nigaoe")->FindMaterialByName("Nigaoe", true);
}
f32 InputForm::getScrollMin() { return 0.0f; }
f32 InputForm::getScrollMax() { return getDrawBoxHeight() - 100.0f; }
f32 InputForm::getDrawBoxHeight() { return mnLine * getLineHeight(); }

void InputForm::onNigaoeButtonTrig() {
    if (meEditMode == EM_Disp && mpNigaoeObserver != NULL && mpNigaoeObserver->onNigaoeButton()) onSE(sound::SE_DECIDE);
}
void InputForm::onNigaoeButtonPoint() {
    if (meEditMode == EM_Disp) {
        searchAnmPane("Nigaoe")->changeAnimation(4);
        if (mpNigaoeObserver != NULL) mpNigaoeObserver->pointNigaoeButton();
        onSE(sound::SE_BT_TARGETTING);
    }
}
void InputForm::onNigaoeButtonLeft() {
    if (meEditMode == EM_Disp) {
        if (mpNigaoeObserver != NULL) mpNigaoeObserver->leftNigaoeButton();
        searchAnmPane("Nigaoe")->changeAnimation(5);
    }
}
void InputForm::setDefaultNigaoe() {
    getNigaoePaneMaterial()->SetTexture(0, *mpDefaultNigaoe);
}
void InputForm::setEditMode(EditMode mode) {
    meEditMode = mode;
    switch (mode) {
    case EM_Disp: getPane("N_txt_scrl")->SetVisible(false); break;
    case EM_Edit: getPane("N_txt_scrl")->SetVisible(true); break;
    case EM_Disappear:
        onCommand(static_cast<INPUT_COMMAND>(6), NULL);
        candidatebox::CandidateBoxCaller::resetCandidate();
        candidatebox::CandidateBoxCaller::makeEmptyCandidate();
        break;
    }
}
void InputForm::preDraw(u32 pos) {
    if (meEditMode == EM_Disp) mpSendString->clear();
    inputform::Base::preDraw(pos);
}
void InputForm::doLineFeed() {
    if (meEditMode == EM_Disp) mpSendString->pushBack(L'\n');
    inputform::Base::doLineFeed();
}
void InputForm::put(wchar_t ch) {
    if (meEditMode == EM_Disp) mpSendString->pushBack(ch);
    textdrawer::Base::put(ch);
}
void InputForm::finishDraw(u32) {
    if (meEditMode == EM_Disp) mpSendString->pushBack(0);
}
void WholePane::onAnmEvent(AnmPaneEvent) {}

void EventHandler::onTiEvent(gui::PaneComponent* component, u32 event, Input* input) {
    inputform::EventHandler::onTiEvent(component, event, input);
    const char* name = component->getPane()->GetName();
    if (name[0] == 'B') {
        if (event == 4 && (input->field_0x0C & 0x800)) {
            if (util::strcmp("B_Nigaoe", name)) mpMemoForm->onNigaoeButtonTrig();
            if (util::strcmp("B_ArwR", name)) mpMemoForm->onArrowRTrig();
            if (util::strcmp("B_ArwL", name)) mpMemoForm->onArrowLTrig();
        }
        if (event == 0) {
            if (util::strcmp("B_Nigaoe", name)) mpMemoForm->onNigaoeButtonPoint();
            if (util::strcmp("B_ArwR", name)) mpMemoForm->onArrowRPoint();
            if (util::strcmp("B_ArwL", name)) mpMemoForm->onArrowLPoint();
        }
        if (event == 1) {
            if (util::strcmp("B_Nigaoe", name)) mpMemoForm->onNigaoeButtonLeft();
            if (util::strcmp("B_ArwR", name)) mpMemoForm->onArrowRLeft();
            if (util::strcmp("B_ArwL", name)) mpMemoForm->onArrowLLeft();
        }
    }
}
void SimpleAnmPane::changeAnimation(u32 id) { nw4rmanager::AnmPane::changeAnimation(id); }
void SimpleAnmPane::init() {}
void ScrollButton::init() {}
u32 AnmPane::getState() { return meState; }
void AnmPane::changeAnimation(u32 id) {
    meState = id;
    nw4rmanager::AnmPane::changeAnimation(id);
}
u32 AnmPane::getKeyType() const { return meKeyType; }
void AnmPane::init() { meState = 0; }
void NigaoePane::onAnmEvent(AnmPaneEvent) {}
bool InputForm::isInScroll() { return mExScrollAnm.isActive(); }

}
}
}
