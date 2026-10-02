#define TISIGNWINDOW_IMPLEMENTATION
#include "keyboard/tiSignWindow.h"
#include "keyboard/tiManager.h"
#include "keyboard/tiLanguageIndependentData.h"
#include "keyboard/tiUtil.h"

#include <new>
#include <string.h>
#include <wchar.h>



namespace textinput {
namespace keyboard {

namespace signwindow {

struct AnimationFile {
    u32 id;
    char name[64];
};

struct PaneAnimation {
    s32 type;
    char paneName[20];
    u32 animationCount;
    const char* forceName;
    const AnimationFile* animations[8];
};

struct PaneControlKey {
    char paneName[20];
    u32 key;
};

const char* csSgnKeys[20] = {
    "P_SGNkey_00", "P_SGNkey_01", "P_SGNkey_02", "P_SGNkey_03", "P_SGNkey_04",
    "P_SGNkey_05", "P_SGNkey_06", "P_SGNkey_07", "P_SGNkey_08", "P_SGNkey_09",
    "P_SGNkey_10", "P_SGNkey_11", "P_SGNkey_12", "P_SGNkey_13", "P_SGNkey_14",
    "P_SGNkey_15", "P_SGNkey_16", "P_SGNkey_17", "P_SGNkey_18", "P_SGNkey_19",
};

static const char* csSgnKeyBase = "P_SGNkey_00";
static const char* csSgnKeyClose = "P_SGNkey_close";

const AnimationFile csAninationFileForSign[9] = {
    {0, "fs_signWindow_a_SGN_normal.brlan"},
    {1, "fs_signWindow_a_SGN_FADE-IN.brlan"},
    {8, "fs_signWindow_a_Scroll_FADE-OUT.brlan"},
    {2, "fs_signWindow_a_SGN_Focus-IN.brlan"},
    {6, "fs_signWindow_a_SGN_Focus-OUT.brlan"},
    {3, "fs_signWindow_a_SGN_Roll_over.brlan"},
    {4, "fs_signWindow_a_SGN_Pushed.brlan"},
    {7, "fs_signWindow_a_SGN_scroll_next.brlan"},
    {5, "fs_signWindow_a_SGN_scroll_prev.brlan"},
};

static const PaneControlKey csPaneNameToControlKey[3] = {
    {"B_SGNkey_close", 0x18},
    {"B_SGNkey_prev", 0x1A},
    {"B_SGNkey_next", 0x19},
};

static const LanguageDependency csLanguageDependencyData[10] = {
    {4, csSignKeyJP}, {10, csSignKeyUS}, {10, csSignKeyUK}, {10, csSignKeyFR}, {10, csSignKeyDE},
    {10, csSignKeyIT}, {10, csSignKeySP}, {10, csSignKeyNL}, {4, csSignKeyCN}, {4, csSignKeyKR},
};

struct InputCharacter {
    wchar_t character;
    u16 type;
    bool repeat;
    u32 value;
};
static const InputCharacter inputCharacterTemplate = {0, 3, false, 0};

static PaneAnimation csPaneToAnimationInSign[25] = {
    {0, "N_SGNkeytop_all", 3, 0, {&csAninationFileForSign[0], &csAninationFileForSign[1], &csAninationFileForSign[2]}},
    {1, "N_SGNkeyall", 3, 0, {&csAninationFileForSign[0], &csAninationFileForSign[7], &csAninationFileForSign[8]}},
    {2, "P_SGNkey_00", 7, 0, {&csAninationFileForSign[0], &csAninationFileForSign[1], &csAninationFileForSign[2], &csAninationFileForSign[3], &csAninationFileForSign[4], &csAninationFileForSign[5], &csAninationFileForSign[6]}},
    {2, "P_SGNkey_01", 7, csSgnKeyBase, {&csAninationFileForSign[0], &csAninationFileForSign[1], &csAninationFileForSign[2], &csAninationFileForSign[3], &csAninationFileForSign[4], &csAninationFileForSign[5], &csAninationFileForSign[6]}},
    {2, "P_SGNkey_02", 7, csSgnKeyBase, {&csAninationFileForSign[0], &csAninationFileForSign[1], &csAninationFileForSign[2], &csAninationFileForSign[3], &csAninationFileForSign[4], &csAninationFileForSign[5], &csAninationFileForSign[6]}},
    {2, "P_SGNkey_03", 7, csSgnKeyBase, {&csAninationFileForSign[0], &csAninationFileForSign[1], &csAninationFileForSign[2], &csAninationFileForSign[3], &csAninationFileForSign[4], &csAninationFileForSign[5], &csAninationFileForSign[6]}},
    {2, "P_SGNkey_04", 7, csSgnKeyBase, {&csAninationFileForSign[0], &csAninationFileForSign[1], &csAninationFileForSign[2], &csAninationFileForSign[3], &csAninationFileForSign[4], &csAninationFileForSign[5], &csAninationFileForSign[6]}},
    {2, "P_SGNkey_05", 7, csSgnKeyBase, {&csAninationFileForSign[0], &csAninationFileForSign[1], &csAninationFileForSign[2], &csAninationFileForSign[3], &csAninationFileForSign[4], &csAninationFileForSign[5], &csAninationFileForSign[6]}},
    {2, "P_SGNkey_06", 7, csSgnKeyBase, {&csAninationFileForSign[0], &csAninationFileForSign[1], &csAninationFileForSign[2], &csAninationFileForSign[3], &csAninationFileForSign[4], &csAninationFileForSign[5], &csAninationFileForSign[6]}},
    {2, "P_SGNkey_07", 7, csSgnKeyBase, {&csAninationFileForSign[0], &csAninationFileForSign[1], &csAninationFileForSign[2], &csAninationFileForSign[3], &csAninationFileForSign[4], &csAninationFileForSign[5], &csAninationFileForSign[6]}},
    {2, "P_SGNkey_08", 7, csSgnKeyBase, {&csAninationFileForSign[0], &csAninationFileForSign[1], &csAninationFileForSign[2], &csAninationFileForSign[3], &csAninationFileForSign[4], &csAninationFileForSign[5], &csAninationFileForSign[6]}},
    {2, "P_SGNkey_09", 7, csSgnKeyBase, {&csAninationFileForSign[0], &csAninationFileForSign[1], &csAninationFileForSign[2], &csAninationFileForSign[3], &csAninationFileForSign[4], &csAninationFileForSign[5], &csAninationFileForSign[6]}},
    {2, "P_SGNkey_10", 7, csSgnKeyBase, {&csAninationFileForSign[0], &csAninationFileForSign[1], &csAninationFileForSign[2], &csAninationFileForSign[3], &csAninationFileForSign[4], &csAninationFileForSign[5], &csAninationFileForSign[6]}},
    {2, "P_SGNkey_11", 7, csSgnKeyBase, {&csAninationFileForSign[0], &csAninationFileForSign[1], &csAninationFileForSign[2], &csAninationFileForSign[3], &csAninationFileForSign[4], &csAninationFileForSign[5], &csAninationFileForSign[6]}},
    {2, "P_SGNkey_12", 7, csSgnKeyBase, {&csAninationFileForSign[0], &csAninationFileForSign[1], &csAninationFileForSign[2], &csAninationFileForSign[3], &csAninationFileForSign[4], &csAninationFileForSign[5], &csAninationFileForSign[6]}},
    {2, "P_SGNkey_13", 7, csSgnKeyBase, {&csAninationFileForSign[0], &csAninationFileForSign[1], &csAninationFileForSign[2], &csAninationFileForSign[3], &csAninationFileForSign[4], &csAninationFileForSign[5], &csAninationFileForSign[6]}},
    {2, "P_SGNkey_14", 7, csSgnKeyBase, {&csAninationFileForSign[0], &csAninationFileForSign[1], &csAninationFileForSign[2], &csAninationFileForSign[3], &csAninationFileForSign[4], &csAninationFileForSign[5], &csAninationFileForSign[6]}},
    {2, "P_SGNkey_15", 7, csSgnKeyBase, {&csAninationFileForSign[0], &csAninationFileForSign[1], &csAninationFileForSign[2], &csAninationFileForSign[3], &csAninationFileForSign[4], &csAninationFileForSign[5], &csAninationFileForSign[6]}},
    {2, "P_SGNkey_16", 7, csSgnKeyBase, {&csAninationFileForSign[0], &csAninationFileForSign[1], &csAninationFileForSign[2], &csAninationFileForSign[3], &csAninationFileForSign[4], &csAninationFileForSign[5], &csAninationFileForSign[6]}},
    {2, "P_SGNkey_17", 7, csSgnKeyBase, {&csAninationFileForSign[0], &csAninationFileForSign[1], &csAninationFileForSign[2], &csAninationFileForSign[3], &csAninationFileForSign[4], &csAninationFileForSign[5], &csAninationFileForSign[6]}},
    {2, "P_SGNkey_18", 7, csSgnKeyBase, {&csAninationFileForSign[0], &csAninationFileForSign[1], &csAninationFileForSign[2], &csAninationFileForSign[3], &csAninationFileForSign[4], &csAninationFileForSign[5], &csAninationFileForSign[6]}},
    {2, "P_SGNkey_19", 7, csSgnKeyBase, {&csAninationFileForSign[0], &csAninationFileForSign[1], &csAninationFileForSign[2], &csAninationFileForSign[3], &csAninationFileForSign[4], &csAninationFileForSign[5], &csAninationFileForSign[6]}},
    {2, "P_SGNkey_prev", 7, csSgnKeyClose, {&csAninationFileForSign[0], &csAninationFileForSign[1], &csAninationFileForSign[2], &csAninationFileForSign[3], &csAninationFileForSign[4], &csAninationFileForSign[5], &csAninationFileForSign[6]}},
    {2, "P_SGNkey_next", 7, csSgnKeyClose, {&csAninationFileForSign[0], &csAninationFileForSign[1], &csAninationFileForSign[2], &csAninationFileForSign[3], &csAninationFileForSign[4], &csAninationFileForSign[5], &csAninationFileForSign[6]}},
    {2, "P_SGNkey_close", 7, 0, {&csAninationFileForSign[0], &csAninationFileForSign[1], &csAninationFileForSign[2], &csAninationFileForSign[3], &csAninationFileForSign[4], &csAninationFileForSign[5], &csAninationFileForSign[6]}},
};

static inline s32 findControlKey(const char* paneName) {
    u32 index = 0;
    do {
        if (util::strcmp(csPaneNameToControlKey[index & 0xFFFF].paneName, paneName))
            return csPaneNameToControlKey[index & 0xFFFF].key;
        ++index;
    } while (index < 3);
    return 0x1B;
}

static inline wchar_t findSignCharacter(const PaneNameToCharCodeInSignMode* keys, u16 page, const char* paneName) {
    u32 index = 0;
    do {
        if (util::strcmp(keys[index & 0xFFFF].szPaneName, paneName))
            return keys[index & 0xFFFF].wc[page];
        ++index;
    } while (index < 20);
    return 0;
}

void Base::create(MEMAllocator*) {
    muPage = 0;
    mbLocked = 0;
    mbRepeat = 0;
    mpLanguageDependency = &csLanguageDependencyData[getLanguage()];
}

void Base::init() {
    muPage = 0;
    mbLocked = 0;
    mbRepeat = 0;
    mpLanguageDependency = &csLanguageDependencyData[getLanguage()];
}

void Base::onKey(u32 command, void* data) {
    s32 key;
    if (command != 4) {
        return;
    }

    key = findControlKey(static_cast<const char*>(data));

    if (key != 0x1B) {
        switch (key) {
        case 0x18:
            close();
            break;
        case 0x1A:
            movePrevSignPage();
            break;
        case 0x19:
            moveNextSignPage();
            break;
        }
        return;
    }

    u16 code = findSignCharacter(mpLanguageDependency->keys, muPage, static_cast<const char*>(data));

    if (code != 0) {
        InputCharacter input = inputCharacterTemplate;
        input.character = code;
        input.repeat = mbRepeat;
        if (mpManager->getInputForm()->isAtokActive()) {
            input.repeat = true;
        }
        if (meLanguage - 8U <= 1U) {
            input.repeat = 1;
        }
        sendCommand(5, &input);
    }
}

void Base::close() {}

void Base::movePrevSignPage() {
    if (muPage == 0) {
        muPage = mpLanguageDependency->count - 1;
        return;
    }
    muPage = muPage - 1;
    return;
}

void Base::moveNextSignPage() {
    u8 page = muPage + 1;
    muPage = page;
    if (page < mpLanguageDependency->count) {
        return;
    }
    muPage = 0;
    return;
}

LayoutByNW4R::~LayoutByNW4R() {
    mpEventHandler->~EventHandler();
    MEMFreeToAllocator(mpAllocator, mpEventHandler);
    AnmPane* pane = static_cast<AnmPane*>(nw4r::ut::List_GetNext(&mAnmPanes, NULL));
    while (pane != NULL) {
        nw4r::ut::List_Remove(&mAnmPanes, pane);
        pane->destroy(mpAllocator);
        pane = static_cast<AnmPane*>(nw4r::ut::List_GetNext(&mAnmPanes, NULL));
    }
}

Base::~Base() {}

EventHandler::~EventHandler() {}

void LayoutByNW4R::create(MEMAllocator* allocator) {
    mpAllocator = allocator;
    Base::create(allocator);
    void* eventBuffer = MEMAllocFromAllocator(allocator, sizeof(EventHandler));
    mpEventHandler = new (eventBuffer) EventHandler(this);
    Layout::createWithEventHandler(allocator, mpEventHandler);
    mpPaneManager->setAllComponentTriggerTarget(false);
    mpPaneManager->setAllBoundingBoxComponentTriggerTarget(true);

    const char* forceName;
    u32 animationCount;
    u32 paneIndex = 0;
    do {
        AnmPane* pane = NULL;
        const PaneAnimation& paneInfo = csPaneToAnimationInSign[paneIndex & 0xFFFF];
        switch (paneInfo.type) {
        case 2: {
            void* paneBuffer = MEMAllocFromAllocator(allocator, sizeof(CellPhoneSignButtonPane));
            pane = new (paneBuffer) CellPhoneSignButtonPane(getPane(paneInfo.paneName), this);
            break;
        }
        case 1: {
            void* paneBuffer = MEMAllocFromAllocator(allocator, sizeof(CellPhoneSignScrollAnmPane));
            pane = new (paneBuffer) CellPhoneSignScrollAnmPane(getPane(paneInfo.paneName), this);
            break;
        }
        case 0: {
            void* paneBuffer = MEMAllocFromAllocator(allocator, sizeof(CellPhoneSignAllAnmPane));
            pane = new (paneBuffer) CellPhoneSignAllAnmPane(getPane(paneInfo.paneName), this);
            break;
        }
        }

        nw4r::ut::List_Append(&mAnmPanes, pane);
        forceName = paneInfo.forceName;
        animationCount = paneInfo.animationCount;
        u16 animationIndex = 0;
        while (animationIndex < animationCount) {
            const AnimationFile* const& animation = paneInfo.animations[animationIndex];
            void* resource = mpMultiArcResourceAccessor->GetResource(0, animation->name);
            AnimTransformPane* transform = static_cast<AnimTransformPane*>(
                getLayout()->CreateAnimTransform(resource, mpMultiArcResourceAccessor));
            if (forceName != NULL) {
                pane->forceAddAnimation(allocator, animation->id, transform, forceName, false, true);
            } else {
                pane->addAnimation(allocator, animation->id, transform, false, true);
            }
            ++animationIndex;
        }
        ++paneIndex;
    } while (paneIndex < 25);
    init();
}

AnmPane::~AnmPane() {}

void LayoutByNW4R::init() {
    Base::init();
    searchAnmPane("N_SGNkeytop_all")->changeAnimation(0);
    setVisible("N_SGNkeytop_all", true);
    searchAnmPane("P_SGNkey_prev")->changeAnimation(0);
    searchAnmPane("P_SGNkey_next")->changeAnimation(0);
    setSignKeyTop(muPage, muPage);
    setPageNumber(muPage);
    mpLayout->Animate(0);
    mpLayout->CalculateMtx(mDrawInfo);
}

void LayoutByNW4R::onKey(u32 command, void* data) {
    Base::onKey(command, data);
    if (command == 4) {
        s32 key;
        const char* paneName = static_cast<const char*>(data);
        key = findControlKey(paneName);

        if (key == 0x1B) {
            goto character;
        }
        switch (key) {
        case 0x18:
            mpEventObserver->onSE(sound::SE_CHAR_DECIDE);
            break;
        case 0x19:
        case 0x1A:
            break;
        }
        return;

character:
        u16 code = findSignCharacter(mpLanguageDependency->keys, muPage, paneName);

        if ((code != 0) && (mpKeyboard->getType() == 0)) {
            sendCommand(0x27, NULL);
        }
    }
}

void LayoutByNW4R::open(KeyboardBase* keyboard, bool input) {
    resetAnmSignWindow();
    throwReleaseForAll();
    getPaneManager()->init();
    if (meLanguage - 8U <= 1U) {
        sendCommand(6, NULL);
    }
    mbActive = 1;
    mbInput = 0;
    mpKeyboard = keyboard;
    initPaneLastDrawReceived();
    mbRepeat = input;
    setSignKeyTop(muPage, muPage);
    setPageNumber(muPage);
    searchAnmPane("N_SGNkeytop_all")->onAnmEvent(nw4rmanager::AnmPane::PE_6);
    mpEventObserver->onSE(sound::SE_SYMBOL_PAGE_OPEN);
}

void LayoutByNW4R::close() {
    if (mpKeyboard->getType() == 0) {
        keyboard::pctype::LayoutByNW4R* keyboard = static_cast<keyboard::pctype::LayoutByNW4R*>(mpKeyboard);
        static_cast<nw4rmanager::Layout&>(*keyboard).getLayout()->GetRootPane()->SetVisible(true);
    }
    searchAnmPane("N_SGNkeytop_all")->onAnmEvent(nw4rmanager::AnmPane::PE_7);
    mbInput = 0;
}

void LayoutByNW4R::endToClose() {
    if (mpKeyboard != NULL) {
        mpKeyboard->update();
    }
    mbActive = 0;
    setVisible("N_SGNkeytop_all", false);
}

void LayoutByNW4R::startToInput() {
    mbInput = 1;
    if (mpKeyboard->getType() == 0) {
        keyboard::pctype::LayoutByNW4R* keyboard = static_cast<keyboard::pctype::LayoutByNW4R*>(mpKeyboard);
        static_cast<nw4rmanager::Layout&>(*keyboard).getLayout()->GetRootPane()->SetVisible(false);
    }
}

void LayoutByNW4R::onChangeAnmState(AnmEvent event, nw4rmanager::AnmPane* pane, nw4rmanager::Anim* anim) {
    if (util::strcmp("N_SGNkeyall", pane->getPane()->GetName()) &&
        ((anim->muID == 7 || anim->muID == 5) && event == nw4rmanager::AnmObserver::E_1)) {
        setSignKeyTop(muPage, muPage);
    }
    if (util::strcmp("N_SGNkeytop_all", pane->getPane()->GetName())) {
        if ((anim->muID == 8) && (event == nw4rmanager::AnmObserver::E_1)) {
            endToClose();
        }
        if ((anim->muID == 1) && (event == nw4rmanager::AnmObserver::E_1)) {
            startToInput();
        }
    }
    if (anim->muID == 7 || anim->muID == 5) {
        if (event == nw4rmanager::AnmObserver::E_0) {
            mbLocked = 1;
        }
        if (event == nw4rmanager::AnmObserver::E_1) {
            mbLocked = 0;
        }
    }
}

void LayoutByNW4R::throwReleaseForAll() {
    nw4rmanager::AnmPane* pane = static_cast<nw4rmanager::AnmPane*>(nw4r::ut::List_GetNext(&mAnmPanes, NULL));
    while (pane != NULL) {
        s32 keyType = static_cast<AnmPane*>(pane)->getKeyType();
        if (keyType == 2) {
            pane->onAnmEvent(nw4rmanager::AnmPane::PE_2);
        }
        pane = static_cast<nw4rmanager::AnmPane*>(nw4r::ut::List_GetNext(&mAnmPanes, pane));
    }
}

u32 AnmPane::getKeyType() const {
    return muKeyType;
}

void LayoutByNW4R::resetAnmSignWindow() {
    for (u16 i = 0; i < 25; i++) {
        searchAnmPane(csPaneToAnimationInSign[i].paneName)->init();
    }
}

void AnmPane::init() {
    muAnimation = 0;
}

void LayoutByNW4R::setSignKeyTop(u16 oldPage, u16 newPage) {
    char paneName[17];
    wchar_t oldCharacter[2];
    wchar_t newCharacter[2];
    for (u16 i = 0; i < 20; i++) {
        const char* sourcePaneName = mpLanguageDependency->keys[i].szPaneName;
        memset(paneName, 0, 0x11);
        strncpy(paneName, sourcePaneName, strlen(sourcePaneName));
        paneName[0] = 'T';
        oldCharacter[0] = mpLanguageDependency->keys[i].wc[oldPage];
        oldCharacter[1] = 0;
        const char* nextPaneName = mpLanguageDependency->keys[i].szNextPaneName;
        newCharacter[0] = mpLanguageDependency->keys[i].wc[newPage];
        newCharacter[1] = 0;
        nw4r::lyt::TextBox* textBox = static_cast<nw4r::lyt::TextBox*>(getPane(paneName));
        textBox->SetString(oldCharacter, 0);
        textBox = static_cast<nw4r::lyt::TextBox*>(getPane(nextPaneName));
        textBox->SetString(newCharacter, 0);
    }
    setString("T_SGNkey_prev", langindependent::cLanguageIndependentString[langindependent::LANG_STRID_PREV][getLanguage()]);
    setString("T_SGNkey_next", langindependent::cLanguageIndependentString[langindependent::LANG_STRID_NEXT][getLanguage()]);
    setString("T_SGNkey_close", langindependent::cLanguageIndependentString[langindependent::LANG_STRID_CLOSE][getLanguage()]);
}

void LayoutByNW4R::setPageNumber(u16 page) {
    wchar_t text[17];
    swprintf(text, 0x11, L"%d/%d", page + 1, mpLanguageDependency->count);
    nw4r::lyt::TextBox* textBox = static_cast<nw4r::lyt::TextBox*>(getPane("T_SGN_pageNumber"));
    textBox->SetString(text, 0);
}

void LayoutByNW4R::movePrevSignPage() {
    u8 oldPage = muPage;
    if (oldPage == 0) {
        muPage = mpLanguageDependency->count - 1;
    } else {
        muPage = oldPage - 1;
    }
    u8 newPage = muPage;
    setSignKeyTop(oldPage, newPage);
    setPageNumber(newPage);
    movePrevSignWindow();
    mpEventObserver->onSE(sound::SE_15);
}

void LayoutByNW4R::moveNextSignPage() {
    u8 oldPage = muPage;
    u8 page = oldPage + 1;
    muPage = page;
    if (page >= mpLanguageDependency->count) {
        muPage = 0;
    }
    u8 newPage = muPage;
    setSignKeyTop(oldPage, newPage);
    setPageNumber(newPage);
    moveNextSignWindow();
    mpEventObserver->onSE(sound::SE_15);
}

void LayoutByNW4R::movePrevSignWindow() {
    searchAnmPane("N_SGNkeyall")->onAnmEvent(static_cast<nw4rmanager::AnmPane::AnmPaneEvent>(8));
}

void LayoutByNW4R::moveNextSignWindow() {
    searchAnmPane("N_SGNkeyall")->onAnmEvent(static_cast<nw4rmanager::AnmPane::AnmPaneEvent>(9));
}

bool LayoutByNW4R::updateInput(int point, f32 x, f32 y, u32 trig, u32 hold, u32 release, void* data) {
    if (mbInput != 0) {
        return nw4rmanager::Layout::updateInput(point, x, y, trig, hold, release, data);
    }
    return false;
}

bool LayoutByNW4R::updateInput(input::HKBManager& manager) {
    if (mbInput == 0) {
        return false;
    }
    input::HKBManager::KeySet keySet = manager.GetTriggeredKeySet();
    if (keySet.IsValid()) {
        throwReleaseForAll();
        close();
        mpEventObserver->onSE(sound::SE_CHAR_DECIDE);
        return false;
    }
    return nw4rmanager::Layout::updateInput(manager);
}

void EventHandler::onTiEvent(gui::PaneComponent* paneComponent, u32 event, Input* input) {
    s32 eventType = event;
    const char* name = paneComponent->getPane()->GetName();
    if (!mpLayoutByNW4R->isLocked() || event != 4) {
        if (event == 4 && (input->trigger & 0x800) != 0) {
            mpLayoutByNW4R->onKey(4, const_cast<char*>(name));
        }
        if (name[0] == 'B') {
            char paneName[24];
            memset(paneName, 0, 0x11);
            strncpy(paneName, name, strlen(name));
            paneName[0] = 'P';
            AnmPane* pane = static_cast<AnmPane*>(mpLayoutByNW4R->searchAnmPane(paneName));
            if (pane != NULL) {
                switch (eventType) {
                case 4:
                    if ((input->trigger & 0x800) != 0) {
                        pane->onAnmEvent(nw4rmanager::AnmPane::PE_0);
                    }
                    break;
                case 1:
                    pane->onAnmEvent(nw4rmanager::AnmPane::PE_2);
                    break;
                case 0:
                    mpEventObserver->onSE(sound::SE_SELECT);
                    mpLayoutByNW4R->setPaneLastDrawReceived(pane->getPane());
                    pane->onAnmEvent(nw4rmanager::AnmPane::PE_1);
                    break;
                }
            }
        }
    }
}

bool Base::isLocked() {
    return mbLocked;
}

void CellPhoneSignAllAnmPane::onAnmEvent(AnmPaneEvent event) {
    if (event == 6) {
        getPane()->SetVisible(true);
        changeAnimation(1);
        return;
    }
    if (event == 7) {
        changeAnimation(8);
        return;
    }
    if (muAnimation != 8) {
        if (muAnimation >= 8) {
            return;
        }
        if (muAnimation != 1) {
            return;
        }
        if (event != 4) {
            return;
        }
        changeAnimation(0);
        return;
    }
    if (event == 4) {
        getPane()->SetVisible(false);
    }
}

void AnmPane::changeAnimation(u32 animation) {
    muAnimation = animation;
    nw4rmanager::AnmPane::changeAnimation(animation);
}

void CellPhoneSignScrollAnmPane::onAnmEvent(AnmPaneEvent event) {
    switch (muAnimation) {
    case 0:
        if (event == 9) {
            changeAnimation(5);
        }
        if (event != 8) {
            return;
        }
        changeAnimation(7);
        return;
    case 5:
    case 7:
        if (event != 4) {
            return;
        }
        changeAnimation(0);
        return;
    default:
        return;
    }
}

void CellPhoneSignButtonPane::onAnmEvent(AnmPaneEvent event) {
    if (event == 0) {
        changeAnimation(4);
    }
    switch (muAnimation) {
    case 0:
        if (event == 1) {
            changeAnimation(2);
        }
        break;
    case 2:
        if (event == 4) {
            changeAnimation(3);
        }
        if (event == 2) {
            changeAnimation(6);
        }
        break;
    case 3:
        if (event == 2) {
            changeAnimation(6);
        }
        break;
    case 6:
        if (event == 4) {
            changeAnimation(0);
        }
        if (event == 1) {
            changeAnimation(2);
        }
        break;
    case 4:
        if (event == 4) {
            changeAnimation(3);
        }
        if (event == 2) {
            changeAnimation(6);
        }
        break;
    }
}

void LayoutByNW4R::draw() {
    nw4rmanager::Layout::draw();
}

}
void KeyboardBase::onActive() {}
namespace signwindow {

u8 Base::getPage() {
    return muPage;
}

void Base::setPage(u8 page) {
    muPage = page;
    if (muPage < mpLanguageDependency->count) {
        return;
    }
    muPage = 0;
}

void Base::setLanguage(Language language) {
    meLanguage = language;
    init();
}

int Base::getType() {
    return 2;
}

bool LayoutByNW4R::isActive() {
    return mbActive;
}

CellPhoneSignButtonPane::~CellPhoneSignButtonPane() {}

void CellPhoneSignButtonPane::init() {
    muAnimation = 0;
}

void CellPhoneSignScrollAnmPane::init() {
    muAnimation = 0;
}

CellPhoneSignAllAnmPane::~CellPhoneSignAllAnmPane() {}

void CellPhoneSignAllAnmPane::init() {
    muAnimation = 0;
}

CellPhoneSignScrollAnmPane::~CellPhoneSignScrollAnmPane() {}

}
}
}
