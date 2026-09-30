#define IPL_MEMORYCARD_BASE_IMPLEMENTATION
#include "scene/memoryCard/iplMemoryCardBase.h"
#include "scene/settingSelect/iplSettingSelect.h"
#include "scene/settingSelect/iplSettingButton.h"
#include "scene/textBalloon/iplBalloon.h"
#include "iplSystem.h"
#include <cstring>
#include <wchar.h>

namespace ipl {
namespace scene {

void MemoryBaseEvent::onEvent(u32 componentID, u32 event, void* data) {
    nw4r::lyt::Pane* pane = static_cast< ::gui::PaneComponent*>(mpManager->getComponent(componentID))->getPane();
    const char* name = pane->GetName();
    switch (event) {
    case ::gui::EventHandler::ON_POINT:
        mpBase->onPoint(name, static_cast<controller::Interface*>(data));
        break;
    case ::gui::EventHandler::ON_LEFT:
        mpBase->onLeft(name);
        break;
    case ::gui::EventHandler::ON_MOVE:
        mpBase->onMove(name);
        break;
    case ::gui::EventHandler::ON_TRIG:
        if (static_cast<controller::Interface*>(data)->downTrg(0x100800)) {
            mpBase->onTrig(name);
        }
        break;
    }
}

void MemoryBase::onPoint(const char*, controller::Interface*) {}
void MemoryBase::onLeft(const char*) {}
void MemoryBase::onTrig(const char*) {}

void MemoryBase::add_button(const char** paneNames, int count) {
    for (int index = 0; index < count; index++) {
        nw4r::lyt::Pane* pane = mpLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(paneNames[index], true);
        Button* button = new Button(pane);
        nw4r::ut::List_Append(&mButtonList, button);
    }
}

void MemoryBase::add_anmbutton(const char* paneName, Anm* first, Anm* second, Anm* third) {
    AnmButton* button = new AnmButton(paneName, first, second, third);
    nw4r::ut::List_Append(&mAnmButtonList, button);
}

void MemoryBase::clear_button(const char* paneName) {
    AnmButton* button = get_anmbutton(paneName);
    nw4r::lyt::Pane* pane = mpLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(paneName, true);
    mpPaneManager->initPane(pane);
    if (button->unk_0x04 >= 1) {
        button->onCmdRecv(2);
    }
    button->unk_0x04 = 0;
}

MemoryBase::Button* MemoryBase::get_button(const char* paneName) {
    Button* button = static_cast<Button*>(nw4r::ut::List_GetNext(&mButtonList, NULL));
    while (button != NULL) {
        if (strcmp(button->mPane->GetName(), paneName) == 0) {
            return button;
        }
        button = static_cast<Button*>(nw4r::ut::List_GetNext(&mButtonList, button));
    }
    return button;
}

MemoryBase::AnmButton* MemoryBase::get_anmbutton(const char* paneName) {
    AnmButton* button = static_cast<AnmButton*>(nw4r::ut::List_GetNext(&mAnmButtonList, NULL));
    while (button != NULL) {
        if (strcmp(button->mName, paneName) == 0) {
            return button;
        }
        button = static_cast<AnmButton*>(nw4r::ut::List_GetNext(&mAnmButtonList, button));
    }
    return button;
}

void MemoryBase::add_animation(const AnmName* names, int count) {
    for (int index = 0; index < count; index++) {
        layout::GroupAnimator* animator = mpLayout->bindToGroup(names[index].anmFile, names[index].groupName, false, true);
        Anm* animation = new Anm(animator);
        nw4r::ut::List_Append(&mAnmList, animation);
    }
}

MemoryBase::Anm* MemoryBase::get_animation(int index) {
    return static_cast<Anm*>(nw4r::ut::List_GetNth(&mAnmList, index));
}

void MemoryBase::do_animation(int index) {
    Anm* animation = static_cast<Anm*>(nw4r::ut::List_GetNth(&mAnmList, index));
    animation->mAnim->play();
    mpLayout->calc();
}

void MemoryBase::do_animation(int index, bool flag) {
    Anm* animation = static_cast<Anm*>(nw4r::ut::List_GetNth(&mAnmList, index));
    if (flag) {
        animation->mAnim->setAnmType(1);
    } else {
        animation->mAnim->setAnmType(0);
    }
    animation->mAnim->play();
    mpLayout->calc();
}

void MemoryBase::stop_animation(int index) {
    Anm* animation = static_cast<Anm*>(nw4r::ut::List_GetNth(&mAnmList, index));
    animation->mAnim->stop();
}

bool MemoryBase::is_animation(int index) {
    Anm* animation = static_cast<Anm*>(nw4r::ut::List_GetNth(&mAnmList, index));
    return animation->mAnim->isPlaying();
}

bool MemoryBase::is_fadein_enable() {
    return static_cast<SettingSelect*>(System::getScene(SCENE_SETTING_SELECT))->getMemoryCardTransitionState() == 14;
}

void MemoryBase::set_textbox(const char* paneName, u32 message) {
    nw4r::lyt::TextBox* textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(paneName, true));
    textBox->SetString(System::getMessage(message), 0);
}

void MemoryBase::set_textbox(const char* paneName, u32 message, int animationIndex, int frame) {
    Anm* animation = get_animation(animationIndex);
    if (animation->mAnim->getCurrentFrame() >= frame) {
        set_textbox(paneName, message);
    }
}

void MemoryBase::set_textbox(const char* paneName, const wchar_t* text, f32 width, f32 height) {
    int length = wcslen(text);
    nw4r::lyt::TextBox* textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(paneName, true));
    while (length != 0) {
        textBox->SetString(text, 0, length);
        textBox->CalculateMtx(*mpLayout->getDrawInfo());
        nw4r::ut::Rect bounds = textBox->GetTextDrawRect(*mpLayout->getDrawInfo());
        if (bounds.right - bounds.left < width &&
            -1.0f * (bounds.bottom - bounds.top) < height) {
            break;
        }
        length--;
    }
}

void MemoryBase::set_textbox(const char* paneName, const wchar_t* text) {
    nw4r::lyt::TextBox* textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(paneName, true));
    textBox->SetString(text, 0);
}

void MemoryBase::set_visible(const char* paneName, bool flag) {
    mpLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(paneName, true)->SetVisible(flag);
}

SettingButton* MemoryBase::get_setting_button() {
    return static_cast<SettingButton*>(System::getScene(SCENE_SETTING_BUTTON));
}

void MemoryBase::change_button_text_close() {
    static_cast<SettingButton*>(System::getScene(SCENE_SETTING_BUTTON))->reserve(2, 0);
    static_cast<SettingButton*>(System::getScene(SCENE_SETTING_BUTTON))->reserve(3, 0xFC);
    static_cast<SettingButton*>(System::getScene(SCENE_SETTING_BUTTON))->reserve(1, 0);
}

void MemoryBase::change_button_text_return() {
    static_cast<SettingButton*>(System::getScene(SCENE_SETTING_BUTTON))->reserve(2, 0);
    static_cast<SettingButton*>(System::getScene(SCENE_SETTING_BUTTON))->reserve(3, 0x13B);
    static_cast<SettingButton*>(System::getScene(SCENE_SETTING_BUTTON))->reserve(1, 0);
}

void MemoryBase::change_button_text_ok() {
    static_cast<SettingButton*>(System::getScene(SCENE_SETTING_BUTTON))->reserve(2, 0);
    static_cast<SettingButton*>(System::getScene(SCENE_SETTING_BUTTON))->reserve(3, 0x2E);
    static_cast<SettingButton*>(System::getScene(SCENE_SETTING_BUTTON))->reserve(1, 0);
}

void MemoryBase::show_button_return() {
    static_cast<SettingButton*>(System::getScene(SCENE_SETTING_BUTTON))->setText(0x13B);
    static_cast<SettingButton*>(System::getScene(SCENE_SETTING_BUTTON))->showBtn();
}

void MemoryBase::show_button_ok() {
    static_cast<SettingButton*>(System::getScene(SCENE_SETTING_BUTTON))->setText(0x2E);
    static_cast<SettingButton*>(System::getScene(SCENE_SETTING_BUTTON))->showBtn();
}

void MemoryBase::AnmButton::calc() {
    if (mCurrentAnm != NULL && !mCurrentAnm->mAnim->isPlaying()) {
        mCurrentAnm = NULL;
        onCmdRecv(4);
    }
    onCmdRecv(mLastCmd);
}

void MemoryBase::AnmButton::onCmdRecv(int command) {
    if (static_cast<u32>(command - 1) <= 2) {
        mLastCmd = command;
    }
    if (mLastCmd == 3) {
        mCurrentAnm = mAnm3;
        mCurrentAnm->mAnim->play();
        unk_0x24 = 3;
    }
    switch (unk_0x24) {
    case 0:
        if (command == 1) {
            mCurrentAnm = mAnm1;
            mCurrentAnm->mAnim->play();
            unk_0x24 = 1;
        } else if (command == 2) {
            mCurrentAnm = mAnm2;
            mCurrentAnm->mAnim->play();
            unk_0x24 = 2;
        }
        break;
    case 1:
        if (command == 4) {
            if (mLastCmd == 1) mLastCmd = 0;
            if (mpBalloon != NULL) mpBalloon->fadein();
            unk_0x24 = 0;
        }
        break;
    case 2:
        if (command == 4) {
            if (mLastCmd == 2) mLastCmd = 0;
            if (mpBalloon != NULL) mpBalloon->fadeout();
            unk_0x24 = 0;
        }
        break;
    case 3:
        if (command == 4) {
            if (mLastCmd == 3) mLastCmd = 0;
            unk_0x24 = 0;
        }
        break;
    }
}

void MemoryBase::AnmButton::setBalloon(TextBalloon* balloon) {
    mpBalloon = balloon;
}

MemoryBase::AnmButton::~AnmButton() {}
MemoryBase::Button::~Button() {}
MemoryBase::Anm::~Anm() {}
MemoryBaseEvent::~MemoryBaseEvent() {}

}
}
