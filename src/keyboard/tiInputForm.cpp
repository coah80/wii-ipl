#include "keyboard/tiInputForm.h"
#include "keyboard/tiManager.h"

#include <revolution/mtx.h>

namespace textinput {
namespace inputform {

#pragma push
#pragma section const_type ".data"
extern "C" const char lbl_8165C820[] = "P_txtScrll_UP";
extern "C" const char lbl_8165C830[] = "P_txtScrll_DOWN";
extern "C" const char lbl_8165C8C0[] = "N_JPNUSAEUR";
extern "C" const char lbl_8165C8CC[] = "N_separateBarAll";
extern "C" const char lbl_8165C8E0[] = "T_2l_TextBox";
extern "C" const char lbl_8165C8F0[] = "T_title_textJPN";
extern "C" const char lbl_8165C900[] = "N_separateBarKOR";
extern "C" const char lbl_8165C918[] = "T_2l_TextBoxKOR";
extern "C" const char lbl_8165C928[] = "T_title_textKOR";
extern "C" const char lbl_8165C938[] = "N_separateBarCHN";
extern "C" const char lbl_8165C950[] = "T_2l_TextBoxCHN";
extern "C" const char lbl_8165C960[] = "T_title_textCHN";
extern "C" const char lbl_8165CBE0[] = "T_2l_TextBox";
extern "C" const char lbl_8165D258[] = "RevoIpl_RodinNTLGProM_32_I4.brfnt";
extern "C" const char lbl_8165D27C[] = "P_txtScrll_UP";
extern "C" const char lbl_8165D28C[] = "P_txtScrll_DOWN";
extern "C" const char lbl_8165D2A0[] = "N_separateBarAll";
extern "C" const char lbl_8165D2B0[] = "T_title_text";
extern "C" const char lbl_8165D2C0[] = "OutOfLength\n";
extern "C" const char lbl_8165D2D0[] = "Error#004\nAn error has occurred.\nThe system files are corrupted.";
#pragma pop

enum Animation {
    ANM_Normal
};

enum KeyType {
    KT_NormalButton
};

class AnmPane : public nw4rmanager::AnmPane {
public:
    virtual void init();
    virtual void changeAnimation(u32 id);
    virtual KeyType getKeyType() const;
    virtual Animation getState();

protected:
    Animation meState;
    KeyType meKeyType;
};

class NormalButtonAnmPane : public AnmPane {
public:
    virtual ~NormalButtonAnmPane();
};

class EventHandler : public nw4rmanager::TiEventHandler {
public:
    virtual ~EventHandler();
};

void Base::enableSpaceByRight(bool rightWithSpace) {
    mbRightWithSpace = rightWithSpace;
}

void Base::setDestination(Destination destination) {
    meDestination = destination;
}

void Base::setLineDrawInfo(bool lineDraw, u32 lineCount) {
    mbLineDraw = lineDraw;
    muSpecifyLineDrawCount = lineCount;
}

void Base::doWordWrap(bool wordWrap) {
    mbDoWordWrap = wordWrap;
}

void Base::limitStringLength(u32 limitStringLength) {
    muLimitStringLength = limitStringLength;
}

void Base::makeUpCursorPos(CursorPos* cursorPos, u32 pos, s32 startLine, s32 endLine) {
    u32 wordWrapCounter = muWordWrapCounter;
    muWordWrapCounter = pos;
    textdrawer::Base::makeUpCursorPos(cursorPos, pos, startLine, endLine);
    muWordWrapCounter = wordWrapCounter;
}

void Base::setFont(const nw4r::ut::Font& font) {
    textdrawer::Base::setFont(font);
}

void Base::clear() {
    static_cast<CommandReceiver*>(this)->clearSender();
    mpString->clear();
}

nw4r::math::VEC2 Base::getGlobalLeftTopPos() const {
    nw4r::math::VEC3 position;
    position.x = mRect.left;
    position.y = mRect.bottom;
    position.z = 0.0f;
    PSMTXMultVec(mMtx, position, position);
    return nw4r::math::VEC2(position.x, -position.y);
}

void Base::doAfterDrawProcess(const wchar_t*, u32, const DrawInfo&) {}

void Base::finishDraw(u32) {}

void Base::onSE(sound::SE) {}

void Base::setString(const wchar_t* string) {
    mpString->set(string);
}

void AnmPane::changeAnimation(u32 id) {
    meState = static_cast<Animation>(id);
    nw4rmanager::AnmPane::changeAnimation(id);
}

void AnmPane::init() {
    meState = ANM_Normal;
}

KeyType AnmPane::getKeyType() const {
    return meKeyType;
}

Animation AnmPane::getState() {
    return meState;
}

NormalButtonAnmPane::~NormalButtonAnmPane() {}

EventHandler::~EventHandler() {}

wchar_t Base::getCandidate() const {
    return mpString->getCandidate();
}

void* Base::getAtokString() {
    return mpUnfixString;
}

wchar_t* Base::getWCString() const {
    return mpString->getWCString();
}

bool Base::isInScroll() {
    return mScrollAnm.isActive();
}

nw4r::math::VEC2 Base::getScale() const {
    return nw4r::math::VEC2(1.0f, 1.0f);
}

bool LayoutByNW4R::isAbleToUp() {
    return unk_0x2C0[0x0C];
}

bool LayoutByNW4R::isAbleToDown() {
    return unk_0x2C0[0x0D];
}

bool LayoutByNW4R::updateInput(textinput::input::HKBManager& hkbManager) {
    return nw4rmanager::Layout::updateInput(hkbManager);
}

void LayoutByNW4R::visibleSeparator(bool flag) {
    unk_0x2C0[0x0E] = flag;
}

void LayoutByNW4R::setRootPaneScaleFor16x9() {
    nw4rmanager::Layout::setRootPaneScaleFor16x9();
    textdrawer::Base::setAspectRatio(false);
}

void LayoutByNW4R::setRootPaneScaleFor4x3() {
    nw4rmanager::Layout::setRootPaneScaleFor4x3();
    textdrawer::Base::setAspectRatio(true);
}

}
}

void textinput::Base::create(MEMAllocator*) {}
