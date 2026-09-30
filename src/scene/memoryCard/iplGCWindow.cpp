#define IPL_MEMORYCARD_BASE_CTOR_OUT_OF_LINE
#define IPL_MEMORYCARD_BASE_EVENT_OUT_OF_LINE
#define IPL_GCW_PANEMANAGER_CTOR_OUT_OF_LINE
#define IPL_GCW_INTP_CTOR_OUT_OF_LINE
#define IPL_GC_WINDOW_CPP
#include "scene/memoryCard/iplGCWindow.h"
#include "scene/memoryCard/iplMemoryCard.h"
#include "scene/settingSelect/iplSettingButton.h"
#include "iplSound.h"
#include "iplSystem.h"
#include "system/iplDialogWindow.h"
#include "system/iplHomeButton.h"
#include <wchar.h>
#include <cstring>

namespace ipl {
namespace math {
template <typename T>
LinearIntp<T>::LinearIntp() {}
}
namespace scene {
struct TextboxToMessageID {
    const char* name;
    u32 id;
};

static const MemoryBase::AnmName scAnmName[16] = {
    {"it_CubeDetail_a_SeenIn.brlan", "G_Mask"},
    {"it_CubeDetail_a_SeenOut.brlan", "G_Mask"},
    {"it_CubeDetail_a_MoveFoucusIn.brlan", "G_Move"},
    {"it_CubeDetail_a_MoveFoucusOut.brlan", "G_Move"},
    {"it_CubeDetail_a_MoveFlash.brlan", "G_MoveFlash"},
    {"it_CubeDetail_a_CopyFoucusIn.brlan", "G_Copy"},
    {"it_CubeDetail_a_CopyFoucusOut.brlan", "G_Copy"},
    {"it_CubeDetail_a_CopyFlash.brlan", "G_CopyFlash"},
    {"it_CubeDetail_a_DelFoucusIn.brlan", "G_Del"},
    {"it_CubeDetail_a_DelFoucusOut.brlan", "G_Del"},
    {"it_CubeDetail_a_DelFlash.brlan", "G_DelFlash"},
    {"it_CubeDetail_a_SelectOut.brlan", "G_Select"},
    {"it_CubeDetail_a_SeenOutYes.brlan", "G_Mask"},
    {"it_CubeDetail_a_SeenOutYesOk.brlan", "G_Mask"},
    {"it_CubeDetail_a_SeenOutNo.brlan", "G_Mask"},
    {"it_CubeDetail_a_Wait.brlan", "G_Wait"},
};

static const TextboxToMessageID scTextboxToMessageID[3] = {
    {"T_Move_00", 0xA7},
    {"T_Copy_00", 0xB2},
    {"T_Del_00", 0xBD},
};

static const char* scButtonName[3] = {"B_Move_00", "B_Copy_00", "B_Del_00"};
GCWindow::GCWindow(EGG::Heap* heap, nand::LayoutFile* layoutFile, const char* directory, const char* fileName)
    : MemoryBase(), MemCardEventHandler(), mState(0), mLinearInterp(), mCardState(0), mCardIndex(0), mOperation(0), mActive(false),
      mWaiting(false) {
    mpLayout = new layout::Object(heap, layoutFile, directory, fileName);
    add_animation(scAnmName, 0x10);
    mpLayout->finishBinding();
    set_visible("N_Wait", false);
    mpEvent = new MemoryBaseEvent(this);
    mpPaneManager = new gui::PaneManager(mpEvent, mpLayout->getDrawInfo(), NULL, NULL, true);
    mpPaneManager->createLayoutScene(*mpLayout->getNW4RLyt());
    mpPaneManager->setAllComponentTriggerTarget(false);
    for (int i = 0; i < 3; i++) {
        mpPaneManager->setTriggerTarget(mpLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(scButtonName[i], true), true);
    }
    add_anmbutton(scButtonName[0], get_animation(2), get_animation(3), get_animation(4));
    add_anmbutton(scButtonName[1], get_animation(5), get_animation(6), get_animation(7));
    add_anmbutton(scButtonName[2], get_animation(8), get_animation(9), get_animation(10));
    for (int i = 0; i < 3; i++) {
        set_textbox(scTextboxToMessageID[i].name, scTextboxToMessageID[i].id);
    }
    for (int i = 0; i < 2; i++) {
        mFlags0[i] = 0;
        mFlags1[i] = 0;
    }
}


MemoryBase::MemoryBase() : mpLayout(NULL), unk_0x08(NULL) {
    nw4r::ut::List_Init(&mAnmList, offsetof(Anm, mLink));
    nw4r::ut::List_Init(&mButtonList, offsetof(Button, mLink));
    nw4r::ut::List_Init(&mAnmButtonList, offsetof(AnmButton, mLink));
}

MemCardEventHandler::~MemCardEventHandler() {}

MemoryBaseEvent::MemoryBaseEvent(MemoryBase* memoryBase) : mpBase(memoryBase) {}

void GCWindow::init(const math::VEC3& translate, MemoryCardManager* manager, u8 cardState, short cardIndex) {
    mActive = true;
    mFlags1[cardState] = 0;
    set_visible("N_Banner", true);
    mpMemoryCardManager = manager;
    mpMemoryCardManager->setEventHandler(this);
    mCardState = cardState;
    mCardIndex = cardIndex;
    set_textbox("T_Title_00", mpMemoryCardManager->getComment(cardState, cardIndex, 0), 450.0f, 31.0f);
    set_textbox("T_Title_01", mpMemoryCardManager->getComment(cardState, cardIndex, 1), 450.0f, 31.0f);
    int i = 0;
    for (i = 0; i < 3; i++) {
        mpPaneManager->initPane(mpLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(scButtonName[i], true));
    }
    int blocks = mpMemoryCardManager->getBlocks(cardState, cardIndex);
    wchar_t digits[10] = {L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9'};
    int blockCount = static_cast<u16>(blocks);
    wchar_t decimal[5] = {0};
    int skipCount = 0;
    wchar_t blockText[5] = {0};
    decimal[0] = digits[blockCount / 1000];
    decimal[1] = digits[(blockCount / 100) % 10];
    decimal[2] = digits[(blockCount / 10) % 10];
    decimal[3] = digits[blockCount % 10];
    for (i = 0; i < 3; i++) {
        if (decimal[i] != L'0') {
            break;
        }
        skipCount++;
    }
    wcscpy(blockText, decimal + skipCount);
    set_textbox("T_Block_00", blockText);
    mTranslate = translate;
    math::VEC3 zero(0.0f, 0.0f, 0.0f);
    mLinearInterp.init(ANIM_TYPE_FORWARD, 12.0f, 0.0f, mTranslate, zero, 1.0f);
    mLinearInterp.initFrame();
    mLinearInterp.restart();
    math::VEC3 position = mLinearInterp.get();
    mpLayout->FindPaneByName("N_Window")->SetTranslate(position);
    do_animation(0);
    mState = 1;
}

void GCWindow::calc() {
    mpLayout->calc();
    mpPaneManager->calc();
    void* button = NULL;
    while ((button = nw4r::ut::List_GetNext(&mAnmButtonList, button)) != NULL) {
        ((MemoryBase::AnmButton*)button)->calc();
    }
    switch (mState) {
    case 0:
        on_wait();
        break;
    case 1:
        on_fadein();
        break;
    case 2:
        on_normal();
        break;
    case 3:
        on_fadeout1st();
        break;
    case 4:
        if (!is_animation(1)) {
            destroy();
        }
        break;
    case 5:
        on_fadeout_yes1st();
        break;
    case 6:
        if (!is_animation(0xd)) {
            destroy();
        }
        break;
    case 7:
        if (!is_animation(0xe)) {
            destroy();
        }
        break;
    case 8:
        on_focus_move();
        break;
    case 9:
        on_focus_copy();
        break;
    case 10:
        on_focus_del();
        break;
    case 0xb:
        on_select_out();
        break;
    case 0xc:
        on_dialog();
        break;
    case 0xd:
        on_error_message();
        break;
    case 0xe:
        on_error_message1st();
        break;
    case 0xf:
        on_error_message2nd();
        break;
    case 0x10:
        on_error_message3rd();
        break;
    case 0x11:
        on_process();
        break;
    case 0x12:
        on_format1st();
        break;
    case 0x13:
        on_format2nd();
        break;
    case 0x14:
        on_format3rd();
        break;
    case 0x15:
        on_format4th();
        break;
    case 0x16:
        on_format_error();
        break;
    }
}

void GCWindow::draw() {
    mpLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("Banner_00", true)->SetVisible(false);
    mpLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("Banner_01", true)->SetVisible(false);
    if (mpMemoryCardManager->isIconValidate(mCardState, mCardIndex)) {
        if (mpMemoryCardManager->isBannerEnable(mCardState, mCardIndex)) {
            const GXTexObj* banner = mpMemoryCardManager->create_banner(mCardState, mCardIndex);
            if (banner != NULL) {
                set_texture("Banner_00", *banner);
                mpLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("Banner_00", true)->SetVisible(true);
            }
        } else {
            const GXTexObj* icon = mpMemoryCardManager->create_icon(mCardState, mCardIndex, 0);
            if (icon != NULL) {
                set_texture("Banner_01", *icon);
                mpLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("Banner_01", true)->SetVisible(true);
            }
        }
    }
    mpLayout->draw();
}

void GCWindow::destroy() {
    ((MemoryCard*)System::getScene(0xe))->onRelease();
    for (int i = 0; i < 3; i++) {
        clear_button(scButtonName[i]);
    }
    System::getHomeButtonMenu()->enable();
    mWaiting = false;
    show_button_return();
    mActive = false;
    mState = 0;
}

void GCWindow::onPoint(const char* name, controller::Interface* controller) {
    MemoryBase::AnmButton* button = get_anmbutton(name);
    if (button != NULL) {
        if (button->unk_0x04 == 0) {
            button->onCmdRecv(1);
            snd::sSystem.startSE("WIPL_SE_BT_TARGETTING");
            if (controller != NULL) {
                controller->rumble(0);
            }
        }
        button->unk_0x04++;
    }
}

void GCWindow::onLeft(const char* name) {
    MemoryBase::AnmButton* button = get_anmbutton(name);
    if (button != NULL) {
        if (button->unk_0x04 == 1) {
            button->onCmdRecv(2);
        }
        button->unk_0x04--;
    }
}

void GCWindow::onTrig(const char* name) {
    MemoryBase::AnmButton* button = get_anmbutton(name);
    if (button != NULL) {
        if (strcmp(name, scButtonName[0]) == 0) {
            do_animation(4);
            mState = 8;
        } else if (strcmp(name, scButtonName[1]) == 0) {
            do_animation(7);
            mState = 9;
        } else if (strcmp(name, scButtonName[2]) == 0) {
            do_animation(10);
            set_textbox("T_Message_00", 0xf7);
            mState = 10;
        }
        snd::sSystem.startSE("WIPL_SE_DECIDE");
    }
}

void GCWindow::on_wait() {
    for (int i = 0; i < 2; i++) {
        if (mFlags0[i] != 0) {
            ((MemoryCard*)System::getScene(0xe))->onFocus(NULL);
            System::getDialog()->callBtn2(i == 0 ? 0xec : 0xed, 0x142, 0x141, true);
            mFlags0[i] = 0;
            mCardState = i;
            mState = 0x12;
            break;
        }
    }
}

void GCWindow::on_fadein() {
    mLinearInterp.calc();
    mpLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("N_Window", true)->SetTranslate(mLinearInterp.get());
    if (!is_animation(0)) {
        mState = 2;
    }
}

void GCWindow::on_normal() {
    if (mActive) {
        if (get_setting_button()->update()) {
            change_button_text_return();
            mState = 3;
        } else {
            mpPaneManager->update();
        }
    }
}

void GCWindow::on_fadeout1st() {
    if (!get_setting_button()->isPlaying()) {
        math::VEC3 zero(0.0f, 0.0f, 0.0f);
        mLinearInterp.init(ANIM_TYPE_FORWARD, 20.0f, 0.0f, mTranslate, zero);
        mLinearInterp.setAnmType(ANIM_TYPE_BACKWARD);
        mLinearInterp.initFrame();
        mLinearInterp.restart();
        do_animation(1);
        mState = 4;
    }
}

void GCWindow::on_fadeout_yes1st() {
    change_textbox_done();
    if (!is_animation(0xc)) {
        math::VEC3 zero(0.0f, 0.0f, 0.0f);
        mLinearInterp.init(ANIM_TYPE_FORWARD, 20.0f, 0.0f, mTranslate, zero);
        mLinearInterp.setAnmType(ANIM_TYPE_BACKWARD);
        mLinearInterp.initFrame();
        mLinearInterp.restart();
        show_button_return();
        do_animation(0xd);
        mState = 6;
    }
}

void GCWindow::on_focus_move() {
    if (!is_animation(4)) {
        do_animation(0xb, false);
        long error;
        if (mpMemoryCardManager->isMoveEnable(mCardState, mCardIndex, &error)) {
            set_textbox("T_Message_00", mCardState == 0 ? 0xf5 : 0xf3);
            mOperation = 2;
            mState = 0xb;
        } else {
            switch (error) {
            case -26:
                set_textbox("T_Message_00", 0xcd);
                break;
            case -23:
                set_textbox("T_Message_00", 0xce + (mCardState == 0));
                break;
            case -28:
            case -22:
                set_textbox("T_Message_00", 0xd0 + (mCardState == 0));
                break;
            case -27:
                set_textbox("T_Message_00", 0xd4);
                break;
            case -24:
                set_textbox("T_Message_00", 0xd5);
                break;
            case -25:
                set_textbox("T_Message_00", 0xd6);
                break;
            }
            change_button_text_ok();
            mState = 0xf;
        }
    }
}

void GCWindow::on_focus_copy() {
    if (!is_animation(7)) {
        do_animation(0xb, false);
        long error;
        if (mpMemoryCardManager->isCopyEnable(mCardState, mCardIndex, &error)) {
            set_textbox("T_Message_00", mCardState == 0 ? 0xf6 : 0xf4);
            mOperation = 1;
            mState = 0xb;
        } else {
            switch (error) {
            case -26:
                set_textbox("T_Message_00", 0xd9);
                break;
            case -23:
                set_textbox("T_Message_00", 0xda + (mCardState == 0));
                break;
            case -28:
            case -22:
                set_textbox("T_Message_00", 0xdc + (mCardState == 0));
                break;
            case -27:
                set_textbox("T_Message_00", 0xe0);
                break;
            case -24:
                set_textbox("T_Message_00", 0xe1);
                break;
            case -25:
                set_textbox("T_Message_00", 0xe2);
                break;
            }
            change_button_text_ok();
            mState = 0xf;
        }
    }
}

void GCWindow::on_focus_del() {
    if (!is_animation(10)) {
        mOperation = 3;
        do_animation(0xb, false);
        mState = 0xb;
    }
}

void GCWindow::on_select_out() {
    if (!is_animation(0xb)) {
        System::getDialog()->callS2Btn2(0x142, 0x141, true);
        get_setting_button()->hideBtn();
        mState = 0xc;
    }
}

void GCWindow::on_dialog() {
    int result = System::getDialog()->getLastResult();
    long error;
    if (result != 2) {
        if (result < 2) {
            if (result < 1) {
                return;
            }
        } else if (result != 6) {
            return;
        }
        goto cancel_dialog;
    }
    {
        switch (mOperation) {
        case 1:
            if (mpMemoryCardManager->isCopyEnable(mCardState, mCardIndex, &error)) {
                set_visible("N_Wait", true);
                do_animation(0xf);
                snd::sSystem.startSE("WIPL_SE_COPYING");
                mpMemoryCardManager->sendCardCmdCopy(mCardState, mCardIndex);
            } else {
                switch (error) {
                case -26:
                    set_textbox("T_Message_00", 0xd9);
                    break;
                case -23:
                    set_textbox("T_Message_00", 0xda + (mCardState == 0));
                    break;
                case -28:
                case -22:
                    set_textbox("T_Message_00", 0xdc + (mCardState == 0));
                    break;
                case -27:
                    set_textbox("T_Message_00", 0xe0);
                    break;
                case -24:
                    set_textbox("T_Message_00", 0xe1);
                    break;
                case -25:
                    set_textbox("T_Message_00", 0xe2);
                    break;
                }
                change_button_text_ok();
                mState = 0xf;
                return;
            }
            break;
        case 3:
            set_visible("N_Banner", false);
            mpMemoryCardManager->sendCardCmdDelete(mCardState, mCardIndex);
            break;
        case 2:
            if (mpMemoryCardManager->isMoveEnable(mCardState, mCardIndex, &error)) {
                set_visible("N_Banner", false);
                set_visible("N_Wait", true);
                do_animation(0xf);
                snd::sSystem.startSE("WIPL_SE_COPYING");
                mpMemoryCardManager->sendCardCmdMove(mCardState, mCardIndex);
            } else {
                switch (error) {
                case -26:
                    set_textbox("T_Message_00", 0xcd);
                    break;
                case -23:
                    set_textbox("T_Message_00", 0xce + (mCardState == 0));
                    break;
                case -28:
                case -22:
                    set_textbox("T_Message_00", 0xd0 + (mCardState == 0));
                    break;
                case -27:
                    set_textbox("T_Message_00", 0xd4);
                    break;
                case -24:
                    set_textbox("T_Message_00", 0xd5);
                    break;
                case -25:
                    set_textbox("T_Message_00", 0xd6);
                    break;
                }
                change_button_text_ok();
                mState = 0xf;
                return;
            }
            break;
        }
        if ((u32)mOperation - 1 <= 1) {
            do_animation(0xc);
        }
        System::getHomeButtonMenu()->disable();
        mWaiting = true;
        mState = 0x11;
        return;
    }

cancel_dialog:
    do_animation(0xb, true);
    mState = 2;
    get_setting_button()->showBtn();
}

void GCWindow::on_error_message() {
    if (System::getDialog()->getLastResult() >= 0) {
        destroy();
    }
}

void GCWindow::on_process() {
    change_textbox_doing();
    if (!is_animation(0xc) && !mWaiting) {
        stop_wait_anim();
        System::getHomeButtonMenu()->enable();
        mWaiting = false;
        do_animation(0xc);
        mState = 5;
    }
}

void GCWindow::on_error_message1st() {
    if (!is_animation(0xb) && get_setting_button()->update()) {
        for (int i = 0; i < 3; i++) {
            clear_button(scButtonName[i]);
        }
        do_animation(0xb, true);
        mState = 0x10;
        change_button_text_close();
    }
}

void GCWindow::on_error_message2nd() {
    if (!is_animation(0xb) && get_setting_button()->update()) {
        for (int i = 0; i < 3; i++) {
            clear_button(scButtonName[i]);
        }
        do_animation(0xb, true);
        mState = 0x10;
        change_button_text_close();
    }
}

void GCWindow::on_error_message3rd() {
    if (mFlags1[mCardState] != 0) {
        goto fadeout;
    }
    if (mOperation != 2) {
        goto check_animation;
    }

fadeout:
    mState = 3;
    return;

check_animation:
    if (!is_animation(0xb)) {
        mState = 2;
    }
}

void GCWindow::on_format1st() {
    int result = System::getDialog()->getLastResult();
    switch (result) {
    case 1:
    case 6:
        destroy();
        break;
    case 2:
        System::getDialog()->callBtn2(0xee, 0x142, 0x141, true);
        mState = 0x13;
        break;
    }
}

void GCWindow::on_format2nd() {
    int result = System::getDialog()->getLastResult();
    switch (result) {
    case 1:
    case 6:
        destroy();
        break;
    case 2:
        mOperation = 4;
        mpMemoryCardManager->sendCardCmdFormat(mCardState);
        System::getHomeButtonMenu()->disable();
        mWaiting = true;
        mState = 0x14;
        break;
    }
}

void GCWindow::on_format3rd() {
    if (!mWaiting) {
        System::getDialog()->callBtn0(0xf0, 0xb4, false);
        mState = 0x15;
    }
}

void GCWindow::on_format4th() {
    if (System::getDialog()->getLastResult() >= 0) {
        destroy();
    }
}

void GCWindow::on_format_error() {
    if (System::getDialog()->getLastResult() >= 0) {
        destroy();
    }
}

void GCWindow::change_textbox_doing() {
    switch (mOperation) {
    case 2:
        set_textbox("T_Message_00", 0xfa, 0xc, 0x14);
        break;
    case 1:
        set_textbox("T_Message_00", 0xf9, 0xc, 0x14);
        break;
    case 3:
        set_textbox("T_Message_00", 0xfb, 0xc, 0x14);
        break;
    }
}

void GCWindow::change_textbox_done() {
    switch (mOperation) {
    case 2:
        set_textbox("T_Message_00", 0x10d, 0xc, 0x14);
        break;
    case 1:
        set_textbox("T_Message_00", 0x107, 0xc, 0x14);
        break;
    case 3:
        set_textbox("T_Message_00", 0xf8, 0xc, 0x14);
        break;
    }
}

void GCWindow::set_texture(const char* name, const GXTexObj& texture) {
    nw4r::lyt::Pane* pane = mpLayout->getNW4RLyt()->GetRootPane()->FindPaneByName(name, true);
    nw4r::lyt::Material* material = pane->FindMaterialByName(name, true);
    material->SetTexture(0, texture);
}

void GCWindow::onMemEvent(long event, u8 cardState) {
    if (event - 1U <= 3) {
        System::getHomeButtonMenu()->enable();
        mWaiting = false;
    } else if (event == 0) {
        mFlags0[cardState] = 1;
    } else if (event == 6) {
        mFlags1[cardState] = 1;
        mFlags0[cardState] = 0;
        switch (mState) {
        case 0xe:
        case 0xf:
            if (mCardState == cardState) {
                set_visible("N_Banner", false);
            }
            break;
        case 0x12:
        case 0x13:
            if (mCardState == cardState) {
                System::getDialog()->terminate();
                mState = 3;
            }
            break;
        case 0xc:
            if (mCardState == cardState) {
                System::getDialog()->terminate();
                mState = 3;
            } else if (mState - 1U <= 1) {
                System::getDialog()->terminate();
                set_textbox("T_Message_00", 0xda + (mCardState == 0));
                show_button_ok();
                mState = 0xe;
            }
            break;
        case 0x14:
            if (mCardState == cardState) {
                System::getDialog()->callBtn0(0xf1, 0xb4, false);
                mState = 0x16;
            }
            break;
        case 2:
        case 8:
        case 9:
        case 10:
            if (mCardState == cardState) {
                mState = 3;
            }
            break;
        case 0x11:
            switch (mOperation) {
            case 2:
                stop_wait_anim();
                set_textbox("T_Message_00", 0xd7);
                break;
            case 1:
                stop_wait_anim();
                set_textbox("T_Message_00", 0xe3);
                break;
            case 3:
                if (mCardState != cardState) {
                    return;
                }
                set_textbox("T_Message_00", 0xe5);
                break;
            }
            goto process_complete;
        case 0x15:
            return;

        process_complete:
            System::getHomeButtonMenu()->enable();
            mWaiting = false;
            show_button_ok();
            mState = 0xe;
            break;
        }
    }
}

bool GCWindow::isProcess() {
    return mWaiting;
}

void GCWindow::stop_wait_anim() {
    set_visible("N_Wait", false);
    MemoryBase::Anm* animation = get_animation(0xf);
    animation->mAnim->stop();
    snd::sSystem.startSE("WIPL_SE_COPY_FINISH");
}

SavedataEditWindow::SavedataEditWindow(EGG::Heap* heap, nand::LayoutFile* layoutFile,
                                         const char* directory, const char* fileName)
    : mState(0), mActive(false) {
    mpLayout = new layout::Object(heap, layoutFile, directory, fileName);
    add_animation("it_DataDetail_a_SeenIn.brlan", scAnmName[0].groupName);
    add_animation("it_DataDetail_a_SeenOut.brlan", scAnmName[0].groupName);
    add_animation("it_DataDetail_a_DelFoucusIn.brlan", scAnmName[8].groupName);
    add_animation("it_DataDetail_a_DelFoucusOut.brlan", scAnmName[8].groupName);
    add_animation("it_DataDetail_a_DelFlash.brlan", scAnmName[10].groupName);
    add_animation("it_DataDetail_a_SelectOut.brlan", scAnmName[11].groupName);
    add_animation("it_DataDetail_a_SeenOutYes.brlan", scAnmName[0].groupName);
    add_animation("it_DataDetail_a_SeenOutYesOk.brlan", scAnmName[0].groupName);
    add_animation("it_DataDetail_a_SeenOutNo.brlan", scAnmName[0].groupName);
    add_animation("it_DataDetail_a_Wait.brlan", scAnmName[15].groupName);
    mpLayout->finishBinding();
    set_visible("N_Wait", false);
    set_visible("T_Block_01", false);
    mpEvent = new MemoryBaseEvent(this);
    mpPaneManager = new gui::PaneManager(mpEvent, mpLayout->getDrawInfo(), NULL, NULL, true);
    mpPaneManager->setupScene(mpLayout);
    mpPaneManager->setAllComponentTriggerTarget(false);
    mpPaneManager->setTriggerTarget(mpLayout->FindPaneByName(scButtonName[2]), true);
    add_anmbutton(scButtonName[2], get_animation(2), get_animation(3), get_animation(4));
    set_textbox("T_Del_00", 0xbd);
}

void SavedataEditWindow::calc() {
    mpLayout->calc();
    mpPaneManager->calc();
    void* button = NULL;
    while ((button = nw4r::ut::List_GetNext(&mAnmButtonList, button)) != NULL) {
        ((MemoryBase::AnmButton*)button)->calc();
    }
    switch (mState) {
    case 0:
        on_normal();
        break;
    case 1:
        on_fadein();
        break;
    case 2:
        on_fadeout1st();
        break;
    case 3:
        if (!is_animation(1)) {
            destroy();
        }
        break;
    case 4:
        on_fadeout_yes1st();
        break;
    case 5:
        if (!is_animation(7)) {
            destroy();
        }
        break;
    case 6:
        if (!is_animation(8)) {
            destroy();
        }
        break;
    case 7:
        on_focus_del();
        break;
    case 8:
        on_select_out();
        break;
    case 9:
    case 10:
    case 11:
    case 12:
        break;
    }
}

void SavedataEditWindow::on_normal() {
    if (mActive) {
        if (get_setting_button()->update()) {
            change_button_text_return();
            mState = 2;
        } else {
            mpPaneManager->update();
        }
    }
}

void SavedataEditWindow::on_fadein() {
    mLinearInterp.calc();
    mpLayout->getNW4RLyt()->GetRootPane()->FindPaneByName("N_Window", true)->SetTranslate(mLinearInterp.get());
    if (!is_animation(0)) {
        mState = 0;
    }
}

void SavedataEditWindow::on_fadeout1st() {
    if (!get_setting_button()->isPlaying()) {
        math::VEC3 zero(0.0f, 0.0f, 0.0f);
        mLinearInterp.init(ANIM_TYPE_FORWARD, 20.0f, 0.0f, mTranslate, zero);
        mLinearInterp.setAnmType(ANIM_TYPE_BACKWARD);
        mLinearInterp.initFrame();
        mLinearInterp.restart();
        do_animation(1);
        mState = 3;
    }
}

void SavedataEditWindow::on_focus_del() {
    if (!is_animation(4)) {
        do_animation(5, false);
        mState = 8;
    }
}

void SavedataEditWindow::on_select_out() {
    if (!is_animation(5)) {
        System::getDialog()->callS2Btn2(0x142, 0x141, true);
        get_setting_button()->hideBtn();
        mState = 9;
    }
}

void SavedataEditWindow::on_fadeout_yes1st() {
    set_textbox("T_Message_00", 0xf8, 6, 0x14);
    if (!is_animation(6)) {
        math::VEC3 zero(0.0f, 0.0f, 0.0f);
        mLinearInterp.init(ANIM_TYPE_FORWARD, 20.0f, 0.0f, mTranslate, zero);
        mLinearInterp.setAnmType(ANIM_TYPE_BACKWARD);
        mLinearInterp.initFrame();
        mLinearInterp.restart();
        get_setting_button()->setText(0x13b);
        get_setting_button()->showBtn();
        do_animation(7);
        mState = 5;
    }
}

GCWindow::~GCWindow() {}

}
}
