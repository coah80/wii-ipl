#include "keyboard/MyTiLetterForm.h"
#include "keyboard/tiHwKeyboard.h"
#include "keyboard/tiUtil.h"
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
protected:
    InputForm* mpMemoForm;
};
}
namespace letter {
class EventHandler : public memo::EventHandler {
public:
    EventHandler(InputForm* form) : memo::EventHandler(form) {}
    virtual ~EventHandler();
    virtual void onTiEvent(gui::PaneComponent*, u32, Input*);
};
class AnmPane : public nw4rmanager::AnmPane {
protected:
    enum KeyType { KT_Whole, KT_Pic };
    u32 meState;
    KeyType meKeyType;

public:
    AnmPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer)
        : nw4rmanager::AnmPane(pane, observer), meState(0), meKeyType(KT_Whole) {}
    virtual ~AnmPane();
    virtual void init();
    virtual void changeAnimation(u32 id);
    virtual KeyType getKeyType() const;
    virtual u32 getState();
};

class WholePane : public AnmPane {
public:
    WholePane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer)
        : AnmPane(pane, observer) { meKeyType = KT_Whole; }
    virtual ~WholePane();
    virtual void onAnmEvent(AnmPaneEvent paneEvent);
};

class PicPane : public AnmPane {
public:
    PicPane(nw4r::lyt::Pane* pane, nw4rmanager::AnmObserver* observer)
        : AnmPane(pane, observer) { meKeyType = KT_Pic; }
    virtual ~PicPane();
    virtual void onAnmEvent(AnmPaneEvent paneEvent);
};

static const char* paneNames[] = {
    "N_Header", "N_Body", "B_Body", "N_Footer", "Nigaoe",
    "T_Nigaoe", "B_Nigaoe", "T_Letter", "T_TouchLetter"
};
typedef keyboard::hwkey::HWKeyboard::AnimationFile AnimationFile;
const AnimationFile keyboard::hwkey::HWKeyboard::csAninationFile[8] = {
    {0, "my_LetterL_PicFocusIn.brlan"},
    {1, "my_LetterL_SelectPic.brlan"},
    {2, "my_LetterL_ExitPic.brlan"},
    {3, "my_LetterL_PicFocusOut.brlan"},
    {4, "my_LetterL_ReturnIn.brlan"},
    {5, "my_LetterL_SendOut.brlan"},
    {6, "my_LetterL_MailIn.brlan"},
    {7, "my_LetterL_MailOut.brlan"},
};
struct PaneToAnimationGroup {
    s32 type;
    const char* paneName;
    u32 count;
    const AnimationFile* animations[12];
};
static const PaneToAnimationGroup animationGroups[2] = {
    {0, "N_MemoRoot", 4, {&keyboard::hwkey::HWKeyboard::csAninationFile[4], &keyboard::hwkey::HWKeyboard::csAninationFile[5], &keyboard::hwkey::HWKeyboard::csAninationFile[6], &keyboard::hwkey::HWKeyboard::csAninationFile[7]}},
    {0, "SendPic", 4, {&keyboard::hwkey::HWKeyboard::csAninationFile[4], &keyboard::hwkey::HWKeyboard::csAninationFile[5], &keyboard::hwkey::HWKeyboard::csAninationFile[6], &keyboard::hwkey::HWKeyboard::csAninationFile[7]}}
};
struct PaneToAnimationGroup2 {
    s32 type;
    const char* paneName;
    u32 count;
    const AnimationFile* animations[11];
};
static const PaneToAnimationGroup2 groupN_Pic = {
    1, "N_Pic", 5, {&keyboard::hwkey::HWKeyboard::csAninationFile[0], &keyboard::hwkey::HWKeyboard::csAninationFile[1], &keyboard::hwkey::HWKeyboard::csAninationFile[2], &keyboard::hwkey::HWKeyboard::csAninationFile[3], &keyboard::hwkey::HWKeyboard::csAninationFile[4]}
};
char scN_SendMes[0xC] = "N_SendMes";
char scT_TouchLetter[0x10] = "T_TouchLetter";
char scN_SendMes2[0xC] = "N_SendMes";
char scN_txt_scrl[0xC] = "N_txt_scrl";
char scN_MemoRoot[0xC] = "N_MemoRoot";
char scT_SendMes[0xA] = "T_SendMes";
static const wchar_t* scEmptyPane = L"\0\0";
void InputForm::create(MEMAllocator* allocator, textinput::inputform::EditBuffer* editBuffer) {
    memo::InputForm::create(allocator, editBuffer);
    MEMFreeToAllocator(allocator, mpInputEventHandler);
    mpInputEventHandler = new (MEMAllocFromAllocator(allocator, sizeof(EventHandler))) EventHandler(this);
    mpInputEventHandler->setEventObserver(mpEventObserver);
    mpPaneManager->changeEventHandler(mpInputEventHandler);

    (void)&groupN_Pic;
    for (u16 i = 0; i < 4; i++) {
        const PaneToAnimationGroup* group = &animationGroups[i];
        AnmPane* pane = NULL;
        switch (group->type) {
        case 1:
            pane = new (MEMAllocFromAllocator(allocator, sizeof(PicPane))) PicPane(
                getPane(group->paneName), NULL);
            break;
        case 0:
            pane = new (MEMAllocFromAllocator(allocator, sizeof(WholePane))) WholePane(
                getPane(group->paneName), NULL);
            break;
        }
        nw4r::ut::List_Append(&mAnmPanes, pane);

        for (u16 j = 0; j < group->count; j++) {
            void* resource = mpMultiArcResourceAccessor->GetResource(0, group->animations[j]->mFileName);
            AnimTransformPane* transform = static_cast<AnimTransformPane*>(
                getLayout()->CreateAnimTransform(resource, mpMultiArcResourceAccessor));
            pane->addAnimation(allocator, group->animations[j]->mAnimationNo, transform, false, true);
        }
    }

    searchAnmPane("N_Pic")->changeAnimation(3);
    mpLayout->Animate(0);
    mpLayout->CalculateMtx(mDrawInfo);
    mbPhotoScaledUp = 0;
    mbPhotoDraw = false;
    mbCloseWithSend = false;
}

AnmPane::~AnmPane() {}

void InputForm::drawBody() {
    nw4r::lyt::Pane* bodyPane = getPane(paneNames[1]);
    f32 y = 0.0f;
    for (int row = 0; row < (mnLine - 1) / 4 + 1; row++) {
        bodyPane->SetTranslate(nw4r::math::VEC2(0.0f, y));
        bodyPane->CalculateMtx(mDrawInfo);
        bodyPane->Draw(mDrawInfo);
        y -= bodyPane->GetSize().height;
    }

    if (!mbEdited) {
        getPane(scT_TouchLetter)->Draw(mDrawInfo);
    }
    getPane("SendPic")->Draw(mDrawInfo);
    getPane(scN_SendMes2)->Draw(mDrawInfo);

    nw4r::lyt::Pane* scrollPane = getPane(scN_txt_scrl);
    f32 x = scrollPane->GetTranslate().x;
    getPane(scN_txt_scrl)->SetTranslate(nw4r::math::VEC2(x, -6.0f));
}

void InputForm::drawFooter() {
    nw4r::lyt::Pane* bodyPane = getPane(paneNames[1]);
    int row = (mnLine - 1) / 4;
    f32 y = static_cast<f32>(row) * (bodyPane->GetSize().height * -1.0f);
    nw4r::lyt::Pane* footerPane = getPane(paneNames[3]);
    footerPane->SetTranslate(nw4r::math::VEC2(0.0f, y));
    footerPane->CalculateMtx(mDrawInfo);
    footerPane->Draw(mDrawInfo);

    if (mbPhotoDraw) {
        getPane("N_Pic")->Draw(mDrawInfo);
    }
}

nw4r::lyt::Material* InputForm::getPhotoPaneMaterial() {
    return getPane("Pic")->FindMaterialByName("Pic", true);
}

void InputForm::onPhotoTrig() {
    if (getEditMode() != memo::InputForm::EM_Disp || !mbPhotoDraw) {
        return;
    }
}

void InputForm::onPhotoPoint() {
    if (getEditMode() != memo::InputForm::EM_Disp || mbPhotoScaledUp || !mbPhotoDraw) {
        return;
    }
}

void InputForm::onPhotoLeft() {
    if (getEditMode() != memo::InputForm::EM_Disp || mbPhotoScaledUp || !mbPhotoDraw) {
        return;
    }
}

void InputForm::open() {
    memo::InputForm::open();
    switch (meType) {
    case T_MailAddressSel:
        searchAnmPane(scN_MemoRoot)->changeAnimation(6);
        break;
    case T_Address:
    case T_Picture:
    case T_Reply:
    default:
        searchAnmPane(scN_MemoRoot)->changeAnimation(4);
        break;
    }
}

void InputForm::close() {
    memo::InputForm::close();
    if (mbCloseWithSend) {
        searchAnmPane(scN_MemoRoot)->changeAnimation(5);
        searchAnmPane("SendPic")->changeAnimation(5);
        searchAnmPane(scN_SendMes2)->changeAnimation(5);
    } else {
        searchAnmPane(scN_MemoRoot)->changeAnimation(7);
        searchAnmPane("SendPic")->changeAnimation(7);
    }
}

bool InputForm::isWholePaneInAnimation() {
    return searchAnmPane(scN_MemoRoot)->isInAnimation();
}

void InputForm::resizePhotoPane(f32 width, f32 height) {
    nw4r::lyt::Pane* pane = getPane("Pic");
    pane->SetSize(nw4r::lyt::Size(412.0f, 309.0f));
    nw4r::lyt::Size bounds(pane->GetSize());
    nw4r::lyt::Size result(bounds);
    if (0.0f == width) {
        return;
    }
    if (0.0f == height) {
        return;
    }
    if (width > height) {
        result.height = bounds.width * height / width;
        if (result.height > bounds.height) {
            result.width = bounds.width * (bounds.height / result.height);
            result.height = bounds.height;
        }
    } else {
        result.width = bounds.height * width / height;
        if (result.width > bounds.width) {
            result.height = bounds.height * (bounds.width / result.width);
            result.width = bounds.width;
        }
    }
    pane->SetSize(result);
}

void InputForm::setSendOutMessage(const wchar_t* sendOutMessage) {
    nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(
        mpLayout->GetRootPane()->FindPaneByName(scT_SendMes, true))->SetString(sendOutMessage);
}

void EventHandler::onTiEvent(gui::PaneComponent* paneComponent, u32 event, Input* input) {
    if (!static_cast<InputForm*>(mpMemoForm)->isPhotoScaledUp()) {
        memo::EventHandler::onTiEvent(paneComponent, event, input);
    }
    nw4r::lyt::Pane* pane = paneComponent->getPane();
    const char* paneName = pane->GetName();
    if (paneName[0] == 'B') {
        if (event == gui::GUIComponent::EVENT_TRIG && (input->field_0x0C & 0x800) &&
            util::strcmp("B_Pic", paneName)) {
            static_cast<InputForm*>(mpMemoForm)->onPhotoTrig();
        }
        if (event == 0 && util::strcmp("B_Pic", paneName)) {
            static_cast<InputForm*>(mpMemoForm)->onPhotoPoint();
        }
        if (event == 1 && util::strcmp("B_Pic", paneName)) {
            static_cast<InputForm*>(mpMemoForm)->onPhotoLeft();
        }
    }
}

bool InputForm::isPhotoScaledUp() {
    return mbPhotoScaledUp;
}

u32 AnmPane::getState() {
    return meState;
}

void AnmPane::changeAnimation(u32 id) {
    meState = id;
    nw4rmanager::AnmPane::changeAnimation(id);
}

AnmPane::KeyType AnmPane::getKeyType() const {
    return meKeyType;
}

void AnmPane::init() {
    meState = 0;
}

PicPane::~PicPane() {}

void PicPane::onAnmEvent(AnmPaneEvent paneEvent) {}

WholePane::~WholePane() {}

void WholePane::onAnmEvent(AnmPaneEvent paneEvent) {}

InputForm::~InputForm() {}

EventHandler::~EventHandler() {}

}
}
}
