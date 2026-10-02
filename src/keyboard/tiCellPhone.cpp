#define TI_CELLPHONE_MATCH_LAYOUT
#define TI_CELLPHONE_HKB_KEYSET
#define TI_CELLPHONE_IMPLEMENTATION
#define TI_CELLPHONE_SAMPLE_CLASS
#define MYTIMANAGER_IMPLEMENTATION
#include "keyboard/tiCellPhone.h"

#include "keyboard/tiPredictLang.h"
#include "keyboard/tiManager.h"
#include "keyboard/tiCandidateBox.h"
#include "keyboard/tiCpData.h"
#include "keyboard/tiUtil.h"

#include <new>

namespace textinput {
    struct CommandReceiver::ChangePredictMode {
        u32 predictMode;
        bool enabled;
    };
}

namespace textinput {
    namespace keyboard {
        namespace signwindow {
            class SignWindowBase : public KeyboardBase {
            public:
                virtual bool isLocked();
                virtual void setPage(u8 page);
                virtual u8 getPage();
                virtual void movePrevSignPage();
                virtual void moveNextSignPage();
                virtual void close();
            };

            class LayoutByNW4R : public SignWindowBase, public nw4rmanager::Layout, public nw4rmanager::AnmObserver {
            public:
                virtual ~LayoutByNW4R();
                virtual void create(MEMAllocator* allocator);
                virtual void init();
                virtual void draw();
                virtual void open(KeyboardBase* keyboard, bool enabled);
                virtual bool isActive();
                virtual void onChangeAnmState(nw4rmanager::AnmObserver::AnmEvent event,
                                              nw4rmanager::AnmPane* pane, nw4rmanager::Anim* animation);
                virtual bool updateInput(int point, f32 x, f32 y, u32 trig, u32 hold, u32 release, void* data);
                virtual bool updateInput(input::HKBManager& hkbManager);
            };
        }
    }
}

namespace textinput {
    namespace keyboard {
        namespace cellphonetype {

            struct InputModeEnabled { bool enabled; };

            struct LanguageDependencyData {
                u32 flags;
                const KeySet* keySets[5];
            };

            static const wchar_t* csszPredictLanguage[] = {
                L"", L"", L"Eng", L"Fra", L"Esp", L"EN", L"DE",
                L"FR", L"ES", L"IT", L"NL", L"CN", L"KR"
            };

            struct PaneNameToControlKey {
                char name[20];
                u32 controlKey;
            };

            struct AnimationFileForControlKey {
                u32 animation;
                char filename[64];
            };

            static const char* csPaneNameNormalKey[] = {
                "B_CPkey_00", "B_CPkey_01", "B_CPkey_02", "B_CPkey_03",
                "B_CPkey_04", "B_CPkey_05", "B_CPkey_06", "B_CPkey_07",
                "B_CPkey_08", "B_CPkey_09", "B_CPkey_10", "B_CPkey_11",
                "B_CPkey_LF", "B_CPkey_DELETE", "B_othersBT_JP", "B_othersBT_EU",
                "B_spaceBT_JP", "B_ChngTag_00", "B_ChngTag_01", "B_ChngTag_02",
                "B_ChngTag_03", "B_SGNkey_close", "B_SGNkey_prev", "B_SGNkey_next",
                "B_CPkey_Prdc_JP", "B_prdcModeBT_EU",
            };

            struct PaneNameToAnimationKey {
                char name[20];
                const char* animationKey;
            };

            static const char* csNormalAnimationKey = "W_CPkey_00";
            static const char* csToggleAnimationKey = "W_ChngTag_00";
            static const char* csEuropeanAnimationKey = "W_othersBT_EU";

            static PaneNameToAnimationKey csPaneNameNormalAnimationKey[] = {
                {"W_CPkey_00", NULL}, {"W_CPkey_01", csNormalAnimationKey}, {"W_CPkey_02", csNormalAnimationKey},
                {"W_CPkey_03", csNormalAnimationKey}, {"W_CPkey_04", csNormalAnimationKey}, {"W_CPkey_05", csNormalAnimationKey},
                {"W_CPkey_06", csNormalAnimationKey}, {"W_CPkey_07", csNormalAnimationKey}, {"W_CPkey_08", csNormalAnimationKey},
                {"W_CPkey_09", csNormalAnimationKey}, {"W_CPkey_10", csNormalAnimationKey}, {"W_CPkey_11", csNormalAnimationKey},
                {"W_CPkey_LF", csNormalAnimationKey}, {"W_CPkey_DELETE", csNormalAnimationKey}, {"W_spaceBT_JP", csNormalAnimationKey},
                {"W_othersBT_JP", csEuropeanAnimationKey}, {"W_othersBT_EU", NULL},
                {"W_prdcModeBT_EU", NULL}, {"W_smlCptChngeBT", NULL},
            };

            static PaneNameToAnimationKey csPaneNameToggleAnimationKey[] = {
                {"W_ChngTag_00", NULL}, {"W_ChngTag_01", csToggleAnimationKey},
                {"W_ChngTag_02", csToggleAnimationKey}, {"W_ChngTag_03", csToggleAnimationKey},
            };

            static const PaneNameToControlKey csPaneNameToControlKey[] = {
                {"B_CPkey_LF", 0},
                {"B_CPkey_DELETE", 1},
                {"B_othersBT_JP", 9},
                {"B_ChngTag_00", 0x12},
                {"B_ChngTag_01", 0x13},
                {"B_ChngTag_02", 0x0B},
                {"B_ChngTag_03", 0x0D},
                {"B_othersBT_EU", 9},
                {"B_CPkey_Prdc_JP", 0x0A},
                {"B_prdcModeBT_EU", 0x0A},
                {"B_smlCptChngeBT", 0x17},
                {"B_spaceBT_JP", 2},
            };

            static const AnimationFileForControlKey csAninationFileForControlKey[] = {
                {0, "fs_VK_cellPhone_a_normal.brlan"},
                {1, "fs_VK_cellPhone_a_Focus-IN.brlan"},
                {2, "fs_VK_cellPhone_a_Focus-OUT.brlan"},
                {4, "fs_VK_cellPhone_a_Pushed.brlan"},
                {3, "fs_VK_cellPhone_a_Roll_over.brlan"},
            };

            static const AnimationFileForControlKey csAnimationFileForToggleKey[] = {
                {0, "fs_VK_cellPhone_a_normal.brlan"},
                {1, "fs_VK_cellPhone_a_Focus-IN.brlan"},
                {2, "fs_VK_cellPhone_a_Focus-OUT.brlan"},
                {4, "fs_VK_cellPhone_a_Pushed.brlan"},
                {5, "fs_VK_cellPhone_a_toggle-ON.brlan"},
                {6, "fs_VK_cellPhone_a_toggle-OFF.brlan"},
            };

            static const LanguageDependencyData csLanguageDependencyData[] = {
                {0x00040000, {&csKeySetHiragana, &csKeySetKatakana, &csKeySetABCJP, &csKeySetNumber, &csKeySetabcJP}},
                {0x00040000, {&csKeySetUSAbc, &csKeySetUSabc, &csKeySetUSABC, &csKeySetNumber, NULL}},
                {0x00040000, {&csKeySetUKAbc, &csKeySetUKabc, &csKeySetUKABC, &csKeySetNumber, NULL}},
                {0x00040000, {&csKeySetFRAbc, &csKeySetFRabc, &csKeySetFRABC, &csKeySetNumber, NULL}},
                {0x00040000, {&csKeySetDEAbc, &csKeySetDEabc, &csKeySetDEABC, &csKeySetNumber, NULL}},
                {0x00040000, {&csKeySetITAbc, &csKeySetITabc, &csKeySetITABC, &csKeySetNumber, NULL}},
                {0x00040000, {&csKeySetSPAbc, &csKeySetSPabc, &csKeySetSPABC, &csKeySetNumber, NULL}},
                {0x00040000, {&csKeySetNLAbc, &csKeySetNLabc, &csKeySetNLABC, &csKeySetNumber, NULL}},
                {0x00040000, {&csKeySetCNPinyin, &csKeySetCNabc, &csKeySetCNABC, &csKeySetNumber, NULL}},
                {0x00040000, {&csKeySetHangul, &csKeySetUSabc, &csKeySetUSABC, &csKeySetNumber, NULL}},
            };

            void Base::create(MEMAllocator* allocator) {
                mpAllocator = allocator;
                mPreviousInputMode = 0;
                mCurrentInputMode = 0;
                mHoldingButton = 0;
                mbInputModeLocked = false;
                mbNumericWithDotMode = false;
                mbNumericMode = false;
                mbUpperCaseMode = true;
                mbAbcMode = true;
                mbLanguageKeyMode = false;
                mpInputModeTable = const_cast<LanguageDependencyData*>(&csLanguageDependencyData[getLanguage()]);

                u32 inputData[3] = {0, 0, 0};
                sendCommand(3, inputData);
            }

            void Base::init() {
                mPreviousInputMode = 0;
                mCurrentInputMode = 0;
                mHoldingButton = 0;
                mbInputModeLocked = false;
                mbNumericWithDotMode = false;
                mbNumericMode = false;
                mbUpperCaseMode = true;
                mbAbcMode = true;
                mbLanguageKeyMode = false;
                mpInputModeTable = const_cast<LanguageDependencyData*>(&csLanguageDependencyData[getLanguage()]);

                u32 inputData[3] = {0, 0, 0};
                sendCommand(3, inputData);
            }

            void Base::calc() {}

            static inline const PaneNameToCharCode* findKeyForPane(const PaneNameToCharCode* keys, const char* paneName) {
                for (u16 index = 0; index < 12; index++) {
                    if (util::strcmp(keys[index].szPaneName, paneName)) { return &keys[index]; }
                }
                return NULL;
            }

            static inline s32 findCellPhoneControlKey(const char* paneName) {
                for (u16 index = 0; index < 12; ++index) {
                    if (util::strcmp(csPaneNameToControlKey[index].name, paneName)) {
                        return csPaneNameToControlKey[index].controlKey;
                    }
                }
                return 0x1B;
            }


            void Base::onKey(u32 event, void* data) {
                struct KeyEvent { const char* paneName; u8 state; };
                struct ConfirmInput {
                    wchar_t character;
                    u16 letterMode;
                    bool direct;
                    bool held;
                    bool confirmOnly;
                    bool silent;
                    const PaneNameToCharCode* holdingKey;
                };
                if (mbInputModeLocked) { return; }
                const char* paneName = static_cast<KeyEvent*>(data)->paneName;
                if (event == gui::EventHandler::ON_TRIG) {
                    u8 state = static_cast<KeyEvent*>(data)->state;
                    s32 controlKey = findCellPhoneControlKey(paneName);
                    if (controlKey != 0x1B) {
                        onCtrlKey_(static_cast<VKeyCode>(controlKey));
                    } else if (!isZiActive() || getLanguage() == CN ||
                        (getLanguage() == KR && mCurrentInputMode != 0) || getInputType() == 1) {
                        if (mHoldingButton == NULL) {
                            u32 inputMode = mCurrentInputMode;
                            if (getLanguage() == JP && static_cast<s32>(inputMode) == IM_02) {
                                if (!mbUpperCaseMode) { inputMode = IM_04; }
                            } else if (static_cast<const LanguageDependencyData*>(mpInputModeTable)->keySets[inputMode]->uType == KEY_TYPE_ABC_UPPER && !mbUpperCaseMode) {
                                inputMode = IM_01;
                            }
                            const PaneNameToCharCode* keys = static_cast<const LanguageDependencyData*>(mpInputModeTable)->keySets[inputMode]->pPaneNameToCharCode;
                            mHoldingButton = findKeyForPane(keys, paneName);
                            if (state) {
                                mPreviousInputMode = 15;
                                while (mHoldingButton->wc[mPreviousInputMode] == 0) { mPreviousInputMode--; }
                            } else { mPreviousInputMode = 0; }
                        } else {
                            if (state) { mPreviousInputMode--; }
                            else { mPreviousInputMode++; }
                            if (static_cast<s32>(mPreviousInputMode) == 16) { mPreviousInputMode = 0; }
                            else if (static_cast<s32>(mPreviousInputMode) < 0) {
                                mPreviousInputMode = 15;
                                while (mHoldingButton->wc[mPreviousInputMode] == 0) { mPreviousInputMode--; }
                            }
                            if (mHoldingButton->wc[mPreviousInputMode] == 0) { mPreviousInputMode = 0; }
                        }
                        if (mHoldingButton) {
                            ConfirmInput commandData = {0};
                            commandData.character = mHoldingButton->wc[mPreviousInputMode];
                            commandData.holdingKey = mHoldingButton;
                            if (getInputType() == 1 && mHoldingButton->wc[1] != L'0' && mHoldingButton->wc[0] != L' ') {
                                commandData.direct = true;
                            }
                            if (getLanguage() == KR && mCurrentInputMode != 0) { commandData.direct = true; }
                            if (getLanguage() == CN && mCurrentInputMode != 0) { commandData.direct = true; }
                            if (mHoldingButton->wc[1] == 0) {
                                if (mbNumericWithDotMode && commandData.character == L'*') { commandData.character = L'.'; }
                                sendCommand(5, &commandData);
                                mPreviousInputMode = 0;
                                mHoldingButton = NULL;
                            } else {
                                if (getLanguage() == JP && commandData.character == L' ' &&
                                    getInputMode() != IM_04 && getInputMode() != IM_02) { commandData.character = 0x3000; }
                                sendCommand(3, &commandData);
                            }
                        }
                    } else {
                        const PaneNameToCharCode* keys = csKeySetNumber.pPaneNameToCharCode;
                        for (u16 index = 0; index < 12; index++) {
                            const PaneNameToCharCode* pane = &keys[index];
                            if (util::strcmp(pane->szPaneName, paneName)) {
                                wchar_t character = pane->wc[0];
                                ConfirmInput commandData = {0};
                                commandData.character = character;
                                commandData.letterMode = mCurrentInputMode;
                                commandData.holdingKey = mHoldingButton;
                                bool convertSpace;
                                sendCommand(0x20, &convertSpace);
                                if (character == L'0' && getLanguage() != KR) {
                                    if (convertSpace) { sendCommand(6, NULL); }
                                    ConfirmInput spaceInput = {L' ', 0, true, false, true, false, NULL};
                                    spaceInput.letterMode = mCurrentInputMode;
                                    spaceInput.holdingKey = mHoldingButton;
                                    sendCommand(5, &spaceInput);
                                    mPreviousInputMode = 0;
                                    mHoldingButton = NULL;
                                } else {
                                    const PaneNameToCharCode* currentKeys = static_cast<const LanguageDependencyData*>(mpInputModeTable)->keySets[mCurrentInputMode]->pPaneNameToCharCode;
                                    commandData.holdingKey = findKeyForPane(currentKeys, paneName);
                                    if (static_cast<const LanguageDependencyData*>(mpInputModeTable)->keySets[mCurrentInputMode]->uType == KEY_TYPE_ABC_UPPER && !mbAbcMode) {
                                        commandData.letterMode = IM_01;
                                        currentKeys = static_cast<const LanguageDependencyData*>(mpInputModeTable)->keySets[IM_01]->pPaneNameToCharCode;
                                        commandData.holdingKey = findKeyForPane(currentKeys, paneName);
                                    }
                                    commandData.character = convertToZiCellphoneInput_(commandData.character);
                                    sendCommand(5, &commandData);
                                }
                            }
                        }
                    }
                }
                if (event == gui::EventHandler::ON_LEFT && mHoldingButton != NULL) {
                    if (util::strcmp(paneName, mHoldingButton->szPaneName)) {
                        wchar_t character = mHoldingButton->wc[mPreviousInputMode];
                        if (character != 0x309B && character != 0x309C) {
                            if (getLanguage() == JP && character == L' ' && getInputMode() != IM_04 && getInputMode() != IM_02) {
                                character = 0x3000;
                            }
                            ConfirmInput commandData = {0, 0, false, false, true, false, NULL};
                            commandData.character = character;
                            commandData.holdingKey = mHoldingButton;
                            if (getInputType() == 1) { commandData.direct = true; }
                            if (getLanguage() == KR && mCurrentInputMode != 0) { commandData.direct = true; }
                            if (getLanguage() == CN && mCurrentInputMode != 0) { commandData.direct = true; }
                            sendCommand(5, &commandData);
                        }
                        mPreviousInputMode = 0;
                        mHoldingButton = NULL;
                    }
                }
            }

            Base::~Base() {}

            Base::InputMode Base::getInputMode() const {
                return static_cast<InputMode>(mCurrentInputMode);
            }

            void Base::onCtrlKey_(VKeyCode keyCode) {
                switch (keyCode) {
                case VK_LINE_FEED:
                    sendCommand(7, NULL);
                    break;
                case VK_DELETE:
                    sendCommand(1, NULL);
                    break;
                case VK_INPUT_MODE_00:
                    sendCommand(6, NULL);
                    changeInputMode(IM_00);
                    break;
                case VK_INPUT_MODE_01:
                    sendCommand(6, NULL);
                    changeInputMode(IM_01);
                    break;
                case VK_INPUT_MODE_02:
                    sendCommand(6, NULL);
                    changeInputMode(IM_02);
                    break;
                case VK_INPUT_MODE_03:
                    sendCommand(6, NULL);
                    changeInputMode(IM_03);
                    break;
                case VK_SIGN_INPUT:
                    goSignInputMode();
                    break;
                case VK_PREDICT_LANGUAGE:
                    changePredictLanguage();
                    break;
                case VK_TOGGLE_ABC_MODE:
                    setAbcMode(!mbUpperCaseMode);
                    break;
                default:
                    break;
                }
            }

            void Base::goSignInputMode() {}

            void Base::changePredictLanguage() {}

            void Base::updateFromReceiver(u32 command, void* data) {
                if (getLanguage()) {
                    if (static_cast<s32>(command) == 0x21) {
                        setAbcMode(true);
                    }
                    if (static_cast<s32>(command) == 5 && !static_cast<u8*>(data)[5]) {
                        setAbcMode(false);
                        mbAbcMode = false;
                    }
                }
            }

            bool Base::onClose() {}

            void Base::changeInputMode(InputMode mode) {
                mCurrentInputMode = mode;
                if (getLanguage()) {
                    mbUpperCaseMode = true;
                    mbAbcMode = true;
                }

                if (mpManager->getCandidateBox()) {
                    mpManager->getCandidateBox()->checkValidation();
                }

                if (mode == IM_00) {
                    InputModeEnabled activeData = {true};
                    sendCommand(0x13, &activeData);
                }
                if (mode == IM_01) {
                    struct InactiveMode { bool enabled; } inactiveData = {false};
                    sendCommand(0x13, &inactiveData);
                }

                updateFixMode();
                sendCommand(0x29, NULL);
            }

            void Base::setInputMode(InputMode) {}

            void Base::setUpperCaseJP(bool) {}

            void Base::draw() {}

            void Base::doInput() {}

            bool Base::isUpperCase() {
                return mbUpperCaseMode;
            }

            bool Base::isHoldingButton() const {
                return mHoldingButton != 0;
            }

            bool Base::isNumericWithDot() const {
                return mbNumericWithDotMode;
            }

            bool Base::isNumeric() const {
                return mbNumericMode;
            }

            bool Base::isLocked() const {
                return mbInputModeLocked;
            }

            u32 Base::getType() {
                return 1;
            }

            bool Base::isZiActive() {
                struct ActiveMode {
                    u32 mode;
                    bool active;
                } input = {0, false};
                sendCommand(0x1F, &input);
                s32 mode = static_cast<s32>(input.mode);
                if (!input.active) {
                    return false;
                }
                return mode != 1;
            }

            bool Base::isAtokActive() {
                struct ActiveMode {
                    u32 mode;
                    bool active;
                } input = {0, false};
                sendCommand(0x1F, &input);
                s32 mode = static_cast<s32>(input.mode);
                if (input.active) {
                    if (mode == 1) {
                        return true;
                    }
                }
                return false;
            }

            void Base::setAbcMode(bool enabled) {
                mbUpperCaseMode = enabled;
                if (enabled) {
                    mbAbcMode = true;
                }
            }

            void Base::onActive() {
                u32 commandData = 0;
                sendCommand(0x12, &commandData);

                if (mCurrentInputMode == IM_00) {
                    InputModeEnabled activeData = {true};
                    sendCommand(0x13, &activeData);
                }

                if (static_cast<s32>(mCurrentInputMode) == IM_01) {
                    struct InactiveMode { bool enabled; } inactiveData = {false};
                    sendCommand(0x13, &inactiveData);
                }

                if (mCurrentInputMode == IM_00) {
                    sendCommand(6, NULL);
                    changeInputMode(static_cast<InputMode>(mCurrentInputMode));
                }

                updateFixMode();
            }

            void Base::doNumericMode(bool enabled) {
                mbNumericMode = enabled;
                if (enabled) {
                    input::HKBManager::getInstance().SetModifierState(0x100, 0x100);
                    getLanguage();
                    changeInputMode(IM_03);

                    if (mpManager->getToolBar()) {
                        mpManager->getToolBar()->setQwerty(false);
                    }
                }
            }

            void Base::updateFixMode() {
                if ((mpManager->getToolBar() && mpManager->getToolBar()->isQwerty()) || getLanguage()) {
                    return;
                }

                u8 fixMode = 0;
                if (static_cast<s32>(mCurrentInputMode) == IM_04 || static_cast<s32>(mCurrentInputMode) == IM_02) {
                    fixMode = 1;
                } else {
                    fixMode = 0;
                }
                sendCommand(0x14, &fixMode);
            }

            wchar_t Base::convertToZiCellphoneInput_(wchar_t value) {
                switch (value) {
                    case L'1': return 0xEFF1;
                    case L'2': return 0xEFF2;
                    case L'3': return 0xEFF3;
                    case L'4': return 0xEFF4;
                    case L'5': return 0xEFF5;
                    case L'6': return 0xEFF6;
                    case L'7': return 0xEFF7;
                    case L'8': return 0xEFF8;
                    case L'9': return 0xEFF9;
                    case L'0': return 0xEFFA;
                    default: return value;
                }
            }

            int Base::getInputType() const {
                const LanguageDependencyData* inputModeTable = static_cast<const LanguageDependencyData*>(mpInputModeTable);
                const KeySet* keySet = inputModeTable->keySets[mCurrentInputMode];

                if (getLanguage() == KR && keySet->uType == 5) {
                    return 3;
                }
                if (getLanguage() == CN && keySet->uType == 4) {
                    return 4;
                }
                if (keySet->uType == 3) {
                    return 1;
                }
                if (keySet->uType == 0) {
                    switch (getLanguage()) {
                    case JP:
                        return 2;
                    default:
                        return 0;
                    }
                }
                return 0;
            }

            void Base::setLangKeyActive(bool enabled) {
                mInputState = enabled;
                if (getLanguage() == KR || getLanguage() == CN) {
                    if (enabled) {
                        setInputMode(IM_00);
                    } else if (getInputMode() == IM_00) {
                        setInputMode(IM_01);
                    }
                }
            }

            LayoutByNW4R::~LayoutByNW4R() {
                mpEventHandler->~EventHandler();
                MEMFreeToAllocator(mpAllocator, mpEventHandler);

                nw4rmanager::AnmPane* pane = static_cast<nw4rmanager::AnmPane*>(
                    nw4r::ut::List_GetNext(&nw4rmanager::Layout::getAnmPaneList(), NULL));
                while (pane) {
                    nw4r::ut::List_Remove(&nw4rmanager::Layout::getAnmPaneList(), pane);
                    pane->destroy(mpAllocator);
                    pane = static_cast<nw4rmanager::AnmPane*>(
                        nw4r::ut::List_GetNext(&nw4rmanager::Layout::getAnmPaneList(), NULL));
                }
            }

            EventHandler::~EventHandler() {}

            void LayoutByNW4R::create(MEMAllocator* allocator) {
                Base::create(allocator);
                mpEventHandler = new (MEMAllocFromAllocator(allocator, sizeof(EventHandler))) EventHandler(this);
                nw4rmanager::Layout::createWithEventHandler(allocator, mpEventHandler);
                mpPaneManager->setAllComponentTriggerTarget(false);
                mpPaneManager->setAllBoundingBoxComponentTriggerTarget(true);

                for (u16 i = 0; i < sizeof(csPaneNameNormalAnimationKey) / sizeof(csPaneNameNormalAnimationKey[0]); ++i) {
                    CellPhoneAnmPane* pane = new (MEMAllocFromAllocator(allocator, sizeof(CellPhoneAnmPane)))
                        CellPhoneAnmPane(getPane(csPaneNameNormalAnimationKey[i].name), NULL);
                    nw4r::ut::List_Append(&mAnmPanes, pane);
                    const char* animationKey;
                    const PaneNameToAnimationKey& paneName = csPaneNameNormalAnimationKey[i];
                    animationKey = paneName.animationKey;

                    for (u16 j = 0; j < 5; ++j) {
                        void* resource = mpMultiArcResourceAccessor->GetResource(0, csAninationFileForControlKey[j].filename);
                        AnimTransformPane* transform = static_cast<AnimTransformPane*>(
                            getLayout()->CreateAnimTransform(resource, mpMultiArcResourceAccessor));
                        if (animationKey) {
                            pane->forceAddAnimation(allocator, csAninationFileForControlKey[j].animation, transform,
                                                    paneName.animationKey, false, true);
                        } else {
                            pane->addAnimation(allocator, csAninationFileForControlKey[j].animation, transform, false, true);
                        }
                    }
                }

                for (u16 i = 0; i < sizeof(csPaneNameToggleAnimationKey) / sizeof(csPaneNameToggleAnimationKey[0]); ++i) {
                    CellPhoneControlAnmPane* pane = new (MEMAllocFromAllocator(allocator, sizeof(CellPhoneControlAnmPane)))
                        CellPhoneControlAnmPane(getPane(csPaneNameToggleAnimationKey[i].name), NULL);
                    nw4r::ut::List_Append(&mAnmPanes, pane);
                    const PaneNameToAnimationKey& paneName = csPaneNameToggleAnimationKey[i];
                    const char* animationKey = paneName.animationKey;

                    for (u16 j = 0; j < 6; ++j) {
                        void* resource = mpMultiArcResourceAccessor->GetResource(0, csAnimationFileForToggleKey[j].filename);
                        AnimTransformPane* transform = static_cast<AnimTransformPane*>(
                            getLayout()->CreateAnimTransform(resource, mpMultiArcResourceAccessor));
                        if (animationKey) {
                            pane->forceAddAnimation(allocator, csAnimationFileForToggleKey[j].animation, transform,
                                                    paneName.animationKey, false, true);
                        } else {
                            pane->addAnimation(allocator, csAnimationFileForToggleKey[j].animation, transform, false, true);
                        }
                    }
                }

                nw4r::lyt::Pane* rootPane = mpLayout->GetRootPane();
                rootPane->FindPaneByName("P_spaceBT_JP", true)->GetMaterial()->GetTexture(&mTextures[0], 0);
                rootPane->FindPaneByName("P_spaceBT_CN", true)->GetMaterial()->GetTexture(&mTextures[1], 0);
                rootPane->FindPaneByName("P_spaceBT_KR", true)->GetMaterial()->GetTexture(&mTextures[2], 0);
                init();
                setLanguage(getLanguage());
            }

            void LayoutByNW4R::init() {
                Base::init();

                getAnmPane(IM_00)->changeAnimation(ANM_Normal);
                getAnmPane(IM_01)->changeAnimation(ANM_Normal);
                getAnmPane(IM_02)->changeAnimation(ANM_Normal);
                getAnmPane(IM_03)->changeAnimation(ANM_Normal);
                getAnmPane(static_cast<InputMode>(mCurrentInputMode))->changeAnimation(ANM_05);

                setLineFeedButton(true);
                doNumericMode(false);
                setPredictLanguageButton(true);
                setSignWindowButton(true);
                setVisible("W_ChngTag_00", true);
                setVisible("W_ChngTag_01", true);
                setVisible("W_ChngTag_02", true);
                setVisible("W_ChngTag_03", true);

                for (int i = 0; i < 4; ++i) {
                    const char* paneName = csPaneNameToggleAnimationKey[i].name;
                    char textPaneName[17];
                    memset(textPaneName, 0, sizeof(textPaneName));
                    strncpy(textPaneName, paneName, strlen(paneName));
                    textPaneName[0] = 'T';

                    nw4r::lyt::TextBox* textPane = static_cast<nw4r::lyt::TextBox*>(getPane(textPaneName));
                    nw4r::lyt::Pane* buttonPane = getPane(paneName);
                    const KeySet* keySet = static_cast<const LanguageDependencyData*>(mpInputModeTable)->keySets[i];
                    if (keySet == NULL) {
                        buttonPane->SetVisible(false);
                    } else {
                        buttonPane->SetVisible(true);
                        textPane->SetString(static_cast<const LanguageDependencyData*>(mpInputModeTable)->keySets[i]->szKeySetName, 0);
                    }
                }

                if (getLanguage() == JP) {
                    setVisible("W_prdcModeBT_EU", false);
                    setVisible("W_othersBT_EU", false);
                    setVisible("W_smlCptChngeBT", true);
                    setVisible("W_othersBT_JP", true);
                    setVisible("W_CPkey_Prdc_JP", true);
                    setVisible("W_spaceBT_JP", true);
                    setVisible("W_CPkey_09", true);
                    setVisible("W_CPkey_11", true);
                } else if (getLanguage() == CN) {
                    setVisible("W_prdcModeBT_EU", true);
                    setVisible("W_othersBT_EU", true);
                    setVisible("W_smlCptChngeBT", false);
                    setVisible("W_othersBT_JP", false);
                    setVisible("W_CPkey_Prdc_JP", false);
                    setVisible("W_spaceBT_JP", true);
                    setVisible("W_CPkey_09", true);
                    setVisible("W_CPkey_11", false);
                    setPredictLanguageButton(false);
                } else if (getLanguage() == KR) {
                    setVisible("W_prdcModeBT_EU", true);
                    setVisible("W_othersBT_EU", true);
                    setVisible("W_smlCptChngeBT", false);
                    setVisible("W_othersBT_JP", false);
                    setVisible("W_CPkey_Prdc_JP", false);
                    setVisible("W_spaceBT_JP", true);
                    setVisible("W_CPkey_09", false);
                    setVisible("W_CPkey_11", false);
                    setPredictLanguageButton(false);
                } else {
                    setVisible("W_prdcModeBT_EU", true);
                    setVisible("W_othersBT_EU", true);
                    setVisible("W_smlCptChngeBT", false);
                    setVisible("W_othersBT_JP", false);
                    setVisible("W_CPkey_Prdc_JP", false);
                    setVisible("W_spaceBT_JP", false);
                    setVisible("W_CPkey_09", false);
                    setVisible("W_CPkey_11", false);
                }

                changeInputMode(static_cast<InputMode>(mCurrentInputMode));
                setLangKeyActive(true);

                CommandReceiver::ChangePredictMode predictMode = {0, false};
                sendCommand(0x1F, &predictMode);
                updatePredictLanguage(&predictMode);

                initPaneLastDrawReceived();
                mpLayout->Animate(0);
                mpLayout->CalculateMtx(mDrawInfo);

                nw4r::lyt::Pane* spacePane = mpLayout->GetRootPane()->FindPaneByName("P_spaceBT_JP", true);
                nw4r::lyt::Pane* henkanPane = mpLayout->GetRootPane()->FindPaneByName("P_HENKAN_JP", true);
                spacePane->SetVisible(true);
                henkanPane->SetVisible(false);
            }

            void LayoutByNW4R::setSignWindow(signwindow::LayoutByNW4R* signWindow) {
                mpSignWindow = signWindow;
            }

            void LayoutByNW4R::setPredictLanguageDialog(predictlang::LayoutByNW4R* dialog) {
                mpPredictLanguageDialog = dialog;
            }

            void gui::GUIComponent::setFlightDuration(int point, u16 duration) {
                mFlightDuration[point] = duration;
            }

            bool LayoutByNW4R::updateInput(int channel, f32 x, f32 y, u32 trig, u32 hold, u32 release, void* data) {
                return nw4rmanager::Layout::updateInput(channel, x, y, trig, hold, release, data);
            }

            void LayoutByNW4R::update() {}


            void LayoutByNW4R::onKey(u32 event, void* data) {
                Base::onKey(event, data);

                if (!mbInputModeLocked) {
                    s32 controlKey;
                    bool isTrigger = event == gui::EventHandler::ON_TRIG;
                    const char* paneName = *static_cast<const char**>(data);
                    if (isTrigger) {
                        controlKey = findCellPhoneControlKey(paneName);
                        if (controlKey != 0x1B) {
                            switch (controlKey) {
                            case 11:
                            case 13:
                            case 18:
                            case 19:
                                mpEventObserver->onSE(static_cast<sound::SE>(0x0D));
                                break;
                            case 23:
                                if (!mbUpperCaseMode) {
                                    mpEventObserver->onSE(static_cast<sound::SE>(0x15));
                                } else {
                                    mpEventObserver->onSE(static_cast<sound::SE>(0x14));
                                }
                                break;
                            case 2:
                                if (mpManager->getInputForm()->canConvert()) {
                                    sendCommand(0x28, NULL);
                                } else {
                                    u32 commandData[4] = {0x00200000, 0, 0x00010000, 0};
                                    sendCommand(0, commandData);
                                }
                                break;
                            default:
                                break;
                            }
                        }
                    }
                }
            }
            void LayoutByNW4R::onActive() {
                Base::onActive();
                nw4rmanager::Layout::init();
            }

            void LayoutByNW4R::draw() {
                nw4rmanager::Layout::draw();
            }

            void LayoutByNW4R::calc() {
                nw4rmanager::Layout::calc();

                nw4r::lyt::Pane* spacePane = mpLayout->GetRootPane()->FindPaneByName("P_spaceBT_JP");
                nw4r::lyt::Pane* henkanPane = mpLayout->GetRootPane()->FindPaneByName("P_HENKAN_JP");
                bool canConvert = mpManager->getInputForm()->canConvert();
                if (canConvert) {
                    spacePane->SetVisible(false);
                    henkanPane->SetVisible(true);
                } else {
                    spacePane->SetVisible(true);
                    henkanPane->SetVisible(false);
                }
            }

            void LayoutByNW4R::doNumericMode(bool enabled) {
                mbNumericMode = enabled;
                if (enabled) {
                    input::HKBManager::getInstance().SetModifierState(0x100, 0x100);
                    getLanguage();
                    changeInputMode(IM_03);

                    if (mpManager->getToolBar()) {
                        mpManager->getToolBar()->setQwerty(false);
                    }
                }

                if (!enabled) { return; }
                {
                    setVisible("W_smlCptChngeBT", !enabled);
                    setVisible("W_CPkey_09", !enabled);
                    setVisible("P_CPkey_dakuten", !enabled);
                    setVisible("W_smlCptChngeBT", !enabled);
                    setVisible("W_prdcModeBT_EU", !enabled);
                    setVisible("W_othersBT_EU", !enabled);
                    setVisible("W_spaceBT_JP", !enabled);
                    setVisible("W_smlCptChngeBT", !enabled);
                    setVisible("W_othersBT_JP", !enabled);
                    setVisible("W_CPkey_Prdc_JP", !enabled);
                    setVisible("W_CPkey_09", !enabled);
                    setVisible("W_CPkey_11", !enabled);
                    setVisible("W_ChngTag_00", !enabled);
                    setVisible("W_ChngTag_01", !enabled);
                    setVisible("W_ChngTag_02", !enabled);
                    setVisible("W_ChngTag_03", !enabled);
                }
            }

            void LayoutByNW4R::updatePredictLanguage(CommandReceiver::ChangePredictMode* mode) {
                if (!getLanguage()) {
                    return;
                }

                if (!mode->enabled) {
                    setVisible("N_prdc_EU_ON", false);
                    setVisible("N_prdc_EU_OFF", true);
                    mbLanguageKeyMode = false;
                } else {
                    setVisible("N_prdc_EU_ON", true);
                    setVisible("N_prdc_EU_OFF", false);
                    mbLanguageKeyMode = true;
                }

                nw4r::lyt::TextBox* textBox = static_cast<nw4r::lyt::TextBox*>(getPane("N_prdc_EU_lang"));
                textBox->SetString(csszPredictLanguage[mode->predictMode], 0);

                const LanguageDependencyData* inputModeTable = static_cast<const LanguageDependencyData*>(mpInputModeTable);
                const KeySet* keySet = inputModeTable->keySets[mCurrentInputMode];
                changeSpaceKeyTop(keySet->pPaneNameToCharCode);
            }

            void LayoutByNW4R::doNumericWithDotMode(bool enabled) {
                doNumericMode(enabled);
                setString("T_CPkey_11", L".");
                setVisible("W_CPkey_11", enabled);
                mbNumericWithDotMode = true;
            }

            void LayoutByNW4R::setLineFeedButton(bool enabled) {
                mbLineFeedButton = enabled;
                setVisible("W_CPkey_LF", mbLineFeedButton);
            }
            bool LayoutByNW4R::updateInput(input::HKBManager& hkbManager) {
                if (mpManager->getToolBar()->isEnableKeytopChange()) {
                    const input::HKBManager::KeySet& triggeredKey = hkbManager.GetTriggeredKeySet();
                    if (triggeredKey.IsValid()) {
                        if (mHoldingButton) {
                            struct KeyEvent { const char* paneName; u32 state; } keyEvent = {NULL, 0};
                            keyEvent.paneName = mHoldingButton->szPaneName;
                            onKey(gui::EventHandler::ON_LEFT, &keyEvent);
                        }
                        changeAnimationAllToNormal();
                        mpManager->getToolBar()->setQwertyWithSE(true);
                        if (!mpManager->getPCKeyboard()->isABC()) { mpManager->getPCKeyboard()->setABC(true); }
                    }
                } else {
                    input::HKBManager::KeySet keySet(hkbManager.GetTriggeredKeySet());
                    while (keySet.IsValid()) {
                        nw4rmanager::AnmPane* pane = NULL;
                        u8 key = keySet.GetKey();
                        u32 character = keySet.GetWChar();
                        switch (key) {
                        case 0x58:
                        case 0x28:
                            if (!(hkbManager.GetModifierState() & 4)) { pane = searchAnmPane("W_CPkey_LF"); }
                            break;
                        default:
                            pane = searchAnmPane(static_cast<wchar_t>(character));
                            break;
                        }
                        if (pane) { pane->onAnmEvent(nw4rmanager::AnmPane::PE_0); }
                        keySet = keySet.GetNext();
                    }
                    keySet = hkbManager.GetRepeatedKeySet();
                    while (keySet.IsValid()) {
                        nw4rmanager::AnmPane* pane = NULL;
                        u8 key = keySet.GetKey();
                        keySet.GetWChar();
                        switch (key) {
                        case 0x2A:
                            if (hkbManager.GetModifierState() & 4) { break; }
                        case 0x4C:
                            pane = searchAnmPane("W_CPkey_DELETE");
                            break;
                        default:
                            break;
                        }
                        if (pane) { pane->onAnmEvent(nw4rmanager::AnmPane::PE_0); }
                        keySet = keySet.GetNext();
                    }
                }
                return false;
            }


            void LayoutByNW4R::setPredictLanguageButton(bool enabled) {
                setVisible("W_prdcModeBT_EU", enabled);
            }

            void LayoutByNW4R::setSignWindowButton(bool enabled) {
                if (!enabled) {
                    setVisible("W_othersBT_EU", enabled);
                    setVisible("W_othersBT_JP", enabled);
                    return;
                }
                {
                    setVisible("W_othersBT_EU", false);
                    setVisible("W_othersBT_JP", false);
                    if (getLanguage() == JP) {
                        setVisible("W_othersBT_JP", true);
                    } else {
                        setVisible("W_othersBT_EU", true);
                    }
                }
            }

            bool toolbar::LayoutByNW4R::isEnableKeytopChange() const { return mbIsEnableQwertyChg; }

            keyboard::pctype::LayoutByNW4R* Manager::getPCKeyboard() { return mpPCKeyboard; }

            void LayoutByNW4R::setLangKeyActive(bool enabled) {
                Base::setLangKeyActive(enabled);
                if (getLanguage() == KR || getLanguage() == CN) {
                    setVisible("W_ChngTag_00", enabled);
                    setVisible("T_ChngTag_00", enabled);
                }
            }

            void LayoutByNW4R::setInputMode(InputMode mode) {
                const LanguageDependencyData* inputModeTable = static_cast<const LanguageDependencyData*>(mpInputModeTable);
                if (!inputModeTable->keySets[mCurrentInputMode]) {
                    mode = IM_03;
                }

                changeInputMode(mode);
                getAnmPane(IM_00)->changeAnimation(ANM_Normal);
                getAnmPane(IM_01)->changeAnimation(ANM_Normal);
                getAnmPane(IM_02)->changeAnimation(ANM_Normal);
                getAnmPane(IM_03)->changeAnimation(ANM_Normal);
                getAnmPane(static_cast<InputMode>(mCurrentInputMode))->changeAnimation(ANM_05);
                mpLayout->Animate();
                mpLayout->CalculateMtx(mDrawInfo);
            }

            void LayoutByNW4R::setUpperCaseJP(bool enabled) {
                if (getLanguage() == JP) {
                    mbUpperCaseMode = enabled;
                }
            }

            void LayoutByNW4R::resetHoldingButton() {
                mHoldingButton = 0;
                mPreviousInputMode = 0;
            }

            void LayoutByNW4R::setCommandReceiver(CommandReceiver* receiver) {
                KeyboardBase::setCommandReceiver(receiver);
                init();
            }

            bool LayoutByNW4R::onClose() {
                initPaneLastDrawReceived();
                changeAnimationAllToNormal();
            }

            void LayoutByNW4R::updateFromReceiver(u32 command, void* data) {
                if (getLanguage()) {
                    if (static_cast<s32>(command) == 0x21) {
                        setAbcMode(true);
                    }
                    if (static_cast<s32>(command) == 5 && !static_cast<u8*>(data)[5]) {
                        setAbcMode(false);
                        mbAbcMode = false;
                    }
                }
                switch (static_cast<s32>(command)) {
                case 0x1D:
                    updatePredictLanguage(static_cast<CommandReceiver::ChangePredictMode*>(data));
                    break;
                default:
                    break;
                }
            }

            CellPhoneAnmPane* LayoutByNW4R::getAnmPane(InputMode mode) {
                switch (mode) {
                case IM_02:
                    return static_cast<CellPhoneAnmPane*>(searchAnmPane(csPaneNameToggleAnimationKey[2].name));
                case IM_03:
                    return static_cast<CellPhoneAnmPane*>(searchAnmPane(csPaneNameToggleAnimationKey[3].name));
                case IM_00:
                    return static_cast<CellPhoneAnmPane*>(searchAnmPane(csPaneNameToggleAnimationKey[0].name));
                case IM_01:
                    return static_cast<CellPhoneAnmPane*>(searchAnmPane(csPaneNameToggleAnimationKey[1].name));
                default:
                    return NULL;
                }
            }

            void LayoutByNW4R::changeInputMode(InputMode mode) {
                Base::changeInputMode(mode);

                if (getLanguage() == JP) {
                    if (!mbUpperCaseMode && mode == IM_02) {
                        mode = IM_04;
                    }

                    switch (mode) {
                    case IM_00:
                    case IM_01:
                        setVisible("W_smlCptChngeBT", false);
                        setVisible("W_CPkey_09", true);
                        setVisible("P_CPkey_dakuten", true);
                        setVisible("W_smlCptChngeBT", false);
                        break;
                    case IM_02:
                    case IM_04:
                        setVisible("W_smlCptChngeBT", true);
                        setVisible("W_CPkey_09", false);
                        setVisible("P_CPkey_dakuten", false);
                        setVisible("W_smlCptChngeBT", true);
                        break;
                    case IM_03:
                        setVisible("W_smlCptChngeBT", false);
                        setVisible("W_CPkey_09", true);
                        setVisible("P_CPkey_dakuten", false);
                        setVisible("W_smlCptChngeBT", false);
                        break;
                    default:
                        break;
                    }
                } else {
                    setVisible("P_CPkey_dakuten", false);
                }

                changeKeyTop(static_cast<const LanguageDependencyData*>(mpInputModeTable)
                                 ->keySets[mode]->pPaneNameToCharCode);
                initPaneLastDrawReceived();
            }

            void LayoutByNW4R::changeKeyTop(const PaneNameToCharCode* keys) {
                for (u16 i = 0; i < 12; ++i) {
                    char textPaneName[17];
                    util::replaceChar(textPaneName, sizeof(textPaneName), keys[i].szPaneName, 0, 'T');
                    nw4r::lyt::TextBox* textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(
                        mpLayout->GetRootPane()->FindPaneByName(textPaneName, true));
                    if (textBox) {
                        textBox->SetString(keys[i].szPaneDisp, 0);
                    }
                }
                changeSpaceKeyTop(keys);
            }

            void LayoutByNW4R::changeSpaceKeyTop(const PaneNameToCharCode* keys) {
                if (getLanguage() == JP) { return; }
                {
                    char textPaneName[17];
                    util::replaceChar(textPaneName, sizeof(textPaneName), keys[10].szPaneName, 0, 'T');
                    nw4r::lyt::Pane* pane = mpLayout->GetRootPane()->FindPaneByName(textPaneName, true);
                    if (keys[10].wc[0] == 0xE057) {
                        nw4r::lyt::TextBox* textBox = static_cast<nw4r::lyt::TextBox*>(pane);
                        if (!mbLanguageKeyMode) {
                            textBox->SetString(csSpaceZero, 0);
                        } else {
                            textBox->SetString(csSpace, 0);
                        }
                    }
                }
            }

            void LayoutByNW4R::throwReleaseForAll() {
                CellPhoneAnmPane* pane = static_cast<CellPhoneAnmPane*>(nw4r::ut::List_GetNext(&nw4rmanager::Layout::getAnmPaneList(), NULL));
                while (pane) {
                    if (pane->getKeyType() == KT_NormalButton) {
                        pane->onAnmEvent(nw4rmanager::AnmPane::PE_2);
                    }
                    pane = static_cast<CellPhoneAnmPane*>(nw4r::ut::List_GetNext(&nw4rmanager::Layout::getAnmPaneList(), pane));
                }
            }

            void LayoutByNW4R::changeAnimationAllToNormal() {
                CellPhoneAnmPane* pane = static_cast<CellPhoneAnmPane*>(nw4r::ut::List_GetNext(&nw4rmanager::Layout::getAnmPaneList(), NULL));
                while (pane) {
                    if (pane->getKeyType() == KT_NormalButton) {
                        pane->changeAnimation(ANM_Normal);
                    }
                    pane = static_cast<CellPhoneAnmPane*>(nw4r::ut::List_GetNext(&nw4rmanager::Layout::getAnmPaneList(), pane));
                }
            }

            void LayoutByNW4R::setLanguage(Language language) {
                KeyboardBase::setLanguage(language);
                nw4r::lyt::Pane* rootPane = mpLayout->GetRootPane();
                if (language == JP) {
                    rootPane->FindPaneByName("P_spaceBT_JP", true)->GetMaterial()->SetTexture(0, mTextures[0]);
                } else if (language == CN) {
                    rootPane->FindPaneByName("P_spaceBT_JP", true)->GetMaterial()->SetTexture(0, mTextures[1]);
                } else if (language == KR) {
                    rootPane->FindPaneByName("P_spaceBT_JP", true)->GetMaterial()->SetTexture(0, mTextures[2]);
                }

                if (mpLayout) {
                    init();
                    initPaneLastDrawReceived();
                }
            }

            void LayoutByNW4R::changePredictLanguage() {
                throwReleaseForAll();
                u32 commandData[2] = {0, 0};
                sendCommand(0x1F, commandData);
                mpPredictLanguageDialog->open(
                    static_cast<inputform::Base::PredictMode>(commandData[0]), this);
            }

            void LayoutByNW4R::setAbcMode(bool enabled) {
                mbUpperCaseMode = enabled;
                if (enabled) {
                    mbAbcMode = true;
                }

                if (getLanguage() == JP) {
                    u32 keySetIndex = 2;
                    if (!mbUpperCaseMode) {
                        keySetIndex = 4;
                    }
                    const KeySet* const* keySets = static_cast<const LanguageDependencyData*>(mpInputModeTable)->keySets;
                    const KeySet* keySet = keySets[keySetIndex];
                    changeKeyTop(keySet->pPaneNameToCharCode);
                    mpEventObserver->onSE(static_cast<sound::SE>(0x12));
                } else {
                    const KeySet* const* keySets = static_cast<const LanguageDependencyData*>(mpInputModeTable)->keySets;
                    const KeySet* keySet = keySets[mCurrentInputMode];
                    if (keySet->uType == 1) {
                        u32 keySetIndex = 0;
                        if (!mbUpperCaseMode) {
                            keySetIndex = 1;
                        }
                        const KeySet* alphabetKeySet = keySets[keySetIndex];
                        changeKeyTop(alphabetKeySet->pPaneNameToCharCode);
                    }
                }
            }

            void LayoutByNW4R::goSignInputMode() {
                bool isNumericMode = false;
                if (static_cast<s32>(mCurrentInputMode) == IM_03) {
                    isNumericMode = true;
                }
                mpSignWindow->open(static_cast<KeyboardBase*>(this), isNumericMode);
                throwReleaseForAll();
            }
            static inline bool isNormalCellPhoneKey(const char* paneName) {
                for (int index = 0; index < 12; ++index) {
                    if (util::strcmp(paneName, csPaneNameNormalKey[index])) { return true; }
                }
                return false;
            }
            void EventHandler::onTiEvent(gui::PaneComponent* paneComponent, u32 event, Input* input) {
                const char* paneName = paneComponent->getPane()->GetName();
                if (paneName[0] == 'B') {
                    char animationName[17];
                    util::replaceChar(animationName, sizeof(animationName), paneName, 0, 'W');
                    CellPhoneAnmPane* animation = static_cast<CellPhoneAnmPane*>(mpLayoutByNW4R->searchAnmPane(animationName));
                    if (animation) {
                        switch (static_cast<s32>(event)) {
                        case gui::EventHandler::ON_TRIG:
                            if ((input->field_0x0C & 0x800) ||
                                ((input->field_0x0C & 0x400) && isNormalCellPhoneKey(paneName))) {
                                if (animation->getKeyType() == KT_ControlButton) {
                                    nw4r::ut::List& panes = mpLayoutByNW4R->getAnmPaneList();
                                    CellPhoneAnmPane* other = static_cast<CellPhoneAnmPane*>(nw4r::ut::List_GetNext(&panes, NULL));
                                    while (other) {
                                        if (other != animation && other->getKeyType() == KT_ControlButton) {
                                            other->onAnmEvent(nw4rmanager::AnmPane::PE_5);
                                        }
                                        other = static_cast<CellPhoneAnmPane*>(nw4r::ut::List_GetNext(&panes, other));
                                    }
                                }
                                animation->onAnmEvent(nw4rmanager::AnmPane::PE_0);
                            }
                            break;
                        case gui::EventHandler::ON_LEFT:
                            animation->onAnmEvent(nw4rmanager::AnmPane::PE_2);
                            break;
                        case gui::EventHandler::ON_POINT:
                            mpEventObserver->onSE(static_cast<sound::SE>(4));
                            mpLayoutByNW4R->setPaneLastDrawReceived(animation->getPane());
                            animation->onAnmEvent(nw4rmanager::AnmPane::PE_1);
                            break;
                        default:
                            break;
                        }
                    }
                }
                struct KeyEvent {
                    const char* paneName;
                    u8 state;
                    u8 repeat;
                } keyEvent = {paneName, 0, 0};
                if (event == gui::EventHandler::ON_TRIG) {
                    if (input->field_0x0C & 0x800) {
                        keyEvent.state = 0;
                        mpLayoutByNW4R->onKey(gui::EventHandler::ON_TRIG, &keyEvent);
                    } else if ((input->field_0x0C & 0x400) && isNormalCellPhoneKey(paneName)) {
                        keyEvent.state = 1;
                        mpLayoutByNW4R->onKey(gui::EventHandler::ON_TRIG, &keyEvent);
                        paneComponent->setFlightDuration(input->field_0x00, 0);
                    }
                }
                if (event == gui::EventHandler::ON_LEFT) {
                    mpLayoutByNW4R->onKey(gui::EventHandler::ON_LEFT, &keyEvent);
                }
                if (event == gui::EventHandler::ON_MOVE && (input->field_0x10 & 0x800) &&
                    !(input->field_0x0C & 0x800) &&
                    (util::strcmp(csPaneNameNormalKey[13], paneName) || util::strcmp(csPaneNameNormalKey[16], paneName)) &&
                    paneComponent->isDragging(input->field_0x00)) {
                    u32 duration = mpLayoutByNW4R->getFlightDuration(input->field_0x00, paneName);
                    if (duration >= 30 && duration % 9 == 0) {
                        char animationName[17];
                        util::replaceChar(animationName, sizeof(animationName), paneName, 0, 'W');
                        CellPhoneAnmPane* animation = static_cast<CellPhoneAnmPane*>(mpLayoutByNW4R->searchAnmPane(animationName));
                        animation->onAnmEvent(nw4rmanager::AnmPane::PE_0);
                        mpLayoutByNW4R->onKey(gui::EventHandler::ON_TRIG, &keyEvent);
                    }
                }
                if (event == gui::EventHandler::ON_MOVE && mpLayoutByNW4R->getFlightDuration(input->field_0x00, paneName) == 90) {
                    keyEvent.repeat = 1;
                    mpLayoutByNW4R->onKey(gui::EventHandler::ON_LEFT, &keyEvent);
                }
            }





            void CellPhoneAnmPane::init() {
                meState = ANM_Normal;
            }

            KeyType CellPhoneAnmPane::getKeyType() const {
                return meKeyType;
            }

            void CellPhoneAnmPane::changeAnimation(u32 id) {
                meState = static_cast<Animation>(id);
                nw4rmanager::AnmPane::changeAnimation(id == ANM_ToggleOff ? ANM_FocusOut : id);
            }

            void CellPhoneAnmPane::onAnmEvent(AnmPaneEvent event) {
                switch (meState) {
                case ANM_Normal:
                    if (event == PE_1) {
                        changeAnimation(ANM_FocusIn);
                    }
                    if (event == PE_0) {
                        changeAnimation(ANM_ToggleOff);
                    }
                    break;
                case ANM_FocusIn:
                    if (event == PE_4) {
                        changeAnimation(ANM_RollOver);
                    }
                    if (event == PE_2) {
                        changeAnimation(ANM_FocusOut);
                    }
                    if (event == PE_0) {
                        changeAnimation(ANM_Pushed);
                    }
                    break;
                case ANM_RollOver:
                    if (event == PE_2) {
                        changeAnimation(ANM_FocusOut);
                    }
                    if (event == PE_0) {
                        changeAnimation(ANM_Pushed);
                    }
                    break;
                case ANM_FocusOut:
                    if (event == PE_4) {
                        changeAnimation(ANM_Normal);
                    }
                    if (event == PE_1) {
                        changeAnimation(ANM_FocusIn);
                    }
                    if (event == PE_0) {
                        changeAnimation(ANM_ToggleOff);
                    }
                    break;
                case ANM_Pushed:
                    if (event == PE_4) {
                        changeAnimation(ANM_RollOver);
                    }
                    if (event == PE_2) {
                        changeAnimation(ANM_FocusOut);
                    }
                    if (event == PE_0) {
                        changeAnimation(ANM_Pushed);
                    }
                    break;
                case ANM_05:
                case ANM_06:
                    break;
                case ANM_ToggleOff:
                    if (event == PE_4) {
                        changeAnimation(ANM_Normal);
                    }
                    if (event == PE_1) {
                        changeAnimation(ANM_FocusIn);
                    }
                    if (event == PE_0) {
                        changeAnimation(ANM_ToggleOff);
                    }
                    break;
                default:
                    break;
                }
            }

            void CellPhoneControlAnmPane::onAnmEvent(AnmPaneEvent event) {
                if (event == PE_5) {
                    if (meState == ANM_06) {
                    } else if (meState == ANM_05) {
                        changeAnimation(ANM_06);
                        return;
                    } else if (meState != ANM_Normal && meState != ANM_FocusOut) {
                        changeAnimation(ANM_FocusOut);
                        return;
                    }
                }

                if (event == PE_0) {
                    changeAnimation(ANM_Pushed);
                    return;
                }

                switch (meState) {
                case ANM_Normal:
                    if (event == PE_1) {
                        changeAnimation(ANM_FocusIn);
                    }
                    break;
                case ANM_FocusIn:
                    if (event == PE_4) {
                        changeAnimation(ANM_RollOver);
                    }
                    if (event == PE_2) {
                        changeAnimation(ANM_FocusOut);
                    }
                    if (event == PE_0) {
                        changeAnimation(ANM_Pushed);
                    }
                    break;
                case ANM_RollOver:
                    if (event == PE_2) {
                        changeAnimation(ANM_FocusOut);
                    }
                    if (event == PE_0) {
                        changeAnimation(ANM_Pushed);
                    }
                    break;
                case ANM_FocusOut:
                    if (event == PE_4) {
                        changeAnimation(ANM_Normal);
                    }
                    break;
                case ANM_06:
                    if (event == PE_4) {
                        changeAnimation(ANM_Normal);
                    }
                    if (event == PE_1) {
                        changeAnimation(ANM_FocusIn);
                    }
                    break;
                case ANM_Pushed:
                    if (event == PE_4) {
                        changeAnimation(ANM_05);
                    }
                    break;
                case ANM_05:
                default:
                    break;
                }
            }

            CellPhoneAnmPane::~CellPhoneAnmPane() {}

            CellPhoneControlAnmPane::~CellPhoneControlAnmPane() {}

        }
    }
}
