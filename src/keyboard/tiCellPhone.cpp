#include <new>
#include <cstring>
#include <revolution/mem.h>
#include <nw4r/lyt/Pane.h>
#include <nw4r/lyt/TextBox.h>

#include "keyboard/tiCellPhone.h"
#include "keyboard/tiUtil.h"
#include "keyboard/tiManager.h"
#include "keyboard/tiPredictLang.h"
#include "keyboard/tiSignWindow.h"
#include "keyboard/tiHKBManager.h"
#include "keyboard/tiTextInputBase.h"
#include "keyboard/tiGUIManager.h"
#include "keyboard/tiKeyboard.h"
#include "keyboard/tiCpData.h"
#include "keyboard/tiToolBar.h"
#include "keyboard/tiInputForm.h"
#include "keyboard/tiLayout.h"
#include "keyboard/tiString.h"

namespace textinput {
    namespace keyboard {
        namespace cellphonetype {

            struct LanguageDependency {
                u32           unk_0x00;             // 0x00
                const KeySet* mpKeySets[5];         // 0x04
            };

            typedef struct PaneNameToLinkedAnm {
                char        szPaneName[0x14];
                const char* uLinkedAnm;
            } PaneNameToLinkedAnm;

            typedef struct PaneNameToControlKey {
                char szPaneName[0x14];
                u32  uCode;
            } PaneNameToControlKey;

            typedef struct AninationFileForControlKey {
                u32  uType;
                char szFileName[0x40];
            } AninationFileForControlKey;

            typedef struct SendCharCommand {
                u16                        mWChar;
                u16                        mMode;
                u8                         mbFlag;
                u8                         pad_0x05;
                u16                        mX;
                const PaneNameToCharCode*  mpPane;
            } SendCharCommand;

            typedef struct InputWCharCommand {
                u16 mWChar;
                u16 mPad;
                u32 mFlags;
                u32 mX;
                u32 mY;
            } InputWCharCommand;

            static const wchar_t* csszPredictLanguage[13] = {
                L"", L"", L"Eng", L"Fra", L"Esp", L"EN", L"DE", L"FR", L"ES", L"IT", L"NL", L"CN", L"KR"
            };

            static const char* csPaneNameNormalKey[0x1A] = {
                "B_CPkey_00", "B_CPkey_01", "B_CPkey_02", "B_CPkey_03", "B_CPkey_04", "B_CPkey_05",
                "B_CPkey_06", "B_CPkey_07", "B_CPkey_08", "B_CPkey_09", "B_CPkey_10", "B_CPkey_11",
                "B_CPkey_LF", "B_CPkey_DELETE", "B_othersBT_JP", "B_othersBT_EU", "B_spaceBT_JP",
                "B_ChngTag_00", "B_ChngTag_01", "B_ChngTag_02", "B_ChngTag_03",
                "B_SGNkey_close", "B_SGNkey_prev", "B_SGNkey_next",
                "B_CPkey_Prdc_JP", "B_prdcModeBT_EU",
            };

            static const char* const csNormalAnim   = "W_CPkey_00";
            static const char* const csToggleAnim   = "W_ChngTag_00";
            static const char* const csOthersEuAnim = "W_othersBT_EU";

            static const PaneNameToLinkedAnm csPaneNameNormalAnimationKey[0x13] = {
                { "W_CPkey_00",         NULL },
                { "W_CPkey_01",         csNormalAnim },
                { "W_CPkey_02",         csNormalAnim },
                { "W_CPkey_03",         csNormalAnim },
                { "W_CPkey_04",         csNormalAnim },
                { "W_CPkey_05",         csNormalAnim },
                { "W_CPkey_06",         csNormalAnim },
                { "W_CPkey_07",         csNormalAnim },
                { "W_CPkey_08",         csNormalAnim },
                { "W_CPkey_09",         csNormalAnim },
                { "W_CPkey_10",         csNormalAnim },
                { "W_CPkey_11",         csNormalAnim },
                { "W_CPkey_LF",         csNormalAnim },
                { "W_CPkey_DELETE",     csNormalAnim },
                { "W_spaceBT_JP",       csNormalAnim },
                { "W_othersBT_JP",      csOthersEuAnim },
                { "W_othersBT_EU",      NULL },
                { "W_prdcModeBT_EU",    NULL },
                { "W_smlCptChngeBT",    NULL },
            };

            static const PaneNameToLinkedAnm csPaneNameToggleAnimationKey[4] = {
                { "W_ChngTag_00", NULL },
                { "W_ChngTag_01", csToggleAnim },
                { "W_ChngTag_02", csToggleAnim },
                { "W_ChngTag_03", csToggleAnim },
            };

            static const PaneNameToControlKey csPaneNameToControlKey[0xC] = {
                { "B_CPkey_LF",       VK_LF },
                { "B_CPkey_DELETE",   VK_DELETE },
                { "B_othersBT_JP",    VK_OTHERS },
                { "B_ChngTag_00",     VK_TAG_00 },
                { "B_ChngTag_01",     VK_TAG_01 },
                { "B_ChngTag_02",     VK_TAG_02 },
                { "B_ChngTag_03",     VK_TAG_03 },
                { "B_othersBT_EU",    VK_OTHERS },
                { "B_CPkey_Prdc_JP",  VK_PRDC },
                { "B_prdcModeBT_EU",  VK_PRDC },
                { "B_smlCptChngeBT",  VK_SML_CPT },
                { "B_spaceBT_JP",     VK_SPACE },
            };

            static const AninationFileForControlKey csAninationFileForControlKey[5] = {
                { 0, "fs_VK_cellPhone_a_normal.brlan" },
                { 1, "fs_VK_cellPhone_a_Focus-IN.brlan" },
                { 2, "fs_VK_cellPhone_a_Focus-OUT.brlan" },
                { 4, "fs_VK_cellPhone_a_Pushed.brlan" },
                { 3, "fs_VK_cellPhone_a_Roll_over.brlan" },
            };

            static const AninationFileForControlKey csAninationFileForToggleKey[6] = {
                { 0, "fs_VK_cellPhone_a_normal.brlan" },
                { 1, "fs_VK_cellPhone_a_Focus-IN.brlan" },
                { 2, "fs_VK_cellPhone_a_Focus-OUT.brlan" },
                { 4, "fs_VK_cellPhone_a_Pushed.brlan" },
                { 5, "fs_VK_cellPhone_a_toggle-ON.brlan" },
                { 6, "fs_VK_cellPhone_a_toggle-OFF.brlan" },
            };

            static const LanguageDependency csLanguageDependencyData[10] = {
                { 0x40000, { &csKeySetHiragana, &csKeySetKatakana, &csKeySetABCJP, &csKeySetNumber, &csKeySetabcJP } },
                { 0x40000, { &csKeySetUSAbc, &csKeySetUSabc, &csKeySetUSABC, &csKeySetNumber, NULL } },
                { 0x40000, { &csKeySetUKAbc, &csKeySetUKabc, &csKeySetUKABC, &csKeySetNumber, NULL } },
                { 0x40000, { &csKeySetFRAbc, &csKeySetFRabc, &csKeySetFRABC, &csKeySetNumber, NULL } },
                { 0x40000, { &csKeySetDEAbc, &csKeySetDEabc, &csKeySetDEABC, &csKeySetNumber, NULL } },
                { 0x40000, { &csKeySetITAbc, &csKeySetITabc, &csKeySetITABC, &csKeySetNumber, NULL } },
                { 0x40000, { &csKeySetSPAbc, &csKeySetSPabc, &csKeySetSPABC, &csKeySetNumber, NULL } },
                { 0x40000, { &csKeySetNLAbc, &csKeySetNLabc, &csKeySetNLABC, &csKeySetNumber, NULL } },
                { 0x40000, { &csKeySetCNPinyin, &csKeySetCNabc, &csKeySetCNABC, &csKeySetNumber, NULL } },
                { 0x40000, { &csKeySetHangul, &csKeySetUSabc, &csKeySetUSABC, &csKeySetNumber, NULL } },
            };

            static const SendCharCommand csSendCharSpace = { 0x20, 0, 1, 0, 0x100, NULL };
            static const SendCharCommand csSendCharRelease = { 0, 0, 0, 0, 0x100, NULL };
            static const InputWCharCommand csInputSpaceChar = { 0x20, 0, 0, 0x10000, 0 };

            static bool csb20 = true;
            static bool csb24 = true;

            typedef struct InputModeReply {
                s32 mMode;      // 0x00
                u8  mbEnabled;  // 0x04
            } InputModeReply;

            typedef struct SendKeyData {
                const char* paneName;   // 0x00
                u8          flag;       // 0x04
                u8          flag2;      // 0x05
                u16         pad_0x06;   // 0x06
            } SendKeyData;

            typedef struct QueryReply {
                u8  mbAvailable;    // 0x00
                u8  pad_0x01[3];
            } QueryReply;

            void Base::create(MEMAllocator* allocator) {
                mpAllocator = allocator;
                mTapIndex = 0;
                mInputMode = 0;
                mpHoldingPane = NULL;
                mbLocked = 0;
                mbNumericWithDot = 0;
                mbNumeric = 0;
                mbUpperCase = 1;
                mbShiftHeld = 1;
                unk_0x21 = 0;
                mpLanguageDep = &csLanguageDependencyData[getLanguage()];

                u32 data[3] = { 0, 0, 0 };
                sendCommand(3, &data);
            }

            void Base::init() {
                mTapIndex = 0;
                mInputMode = 0;
                mpHoldingPane = NULL;
                mbLocked = 0;
                mbNumericWithDot = 0;
                mbNumeric = 0;
                mbUpperCase = 1;
                mbShiftHeld = 1;
                unk_0x21 = 0;
                mpLanguageDep = &csLanguageDependencyData[getLanguage()];

                u32 data[3] = { 0, 0, 0 };
                sendCommand(3, &data);
            }

            void Base::calc() {}

            void Base::onKey(u32 command, void* data) {
                if (mbLocked != 0) {
                    return;
                }

                const char* paneName = *(const char**)data;

                if (command == 4) {
                    u8 flag = ((u8*)data)[4];

                    VKeyCode code = VK_NONE;
                    for (u16 i = 0; i < 0xC; i++) {
                        if (util::strcmp(csPaneNameToControlKey[i].szPaneName, paneName)) {
                            code = (VKeyCode)csPaneNameToControlKey[i].uCode;
                            break;
                        }
                    }

                    if (code != VK_NONE) {
                        onCtrlKey_(code);
                    } else {
                        bool ziKey = false;
                        if (isZiActive() && getLanguage() != CN &&
                            (getLanguage() != KR || mInputMode == 0)) {
                            if (getInputType() != 1) {
                                ziKey = true;
                            }
                        }

                        if (!ziKey) {
                            if (mpHoldingPane == NULL) {
                                u32 mode = mInputMode;
                                if (getLanguage() == JP && mode == IM_02) {
                                    if (mbUpperCase == 0) {
                                        mode = IM_04;
                                    }
                                } else if (mpLanguageDep->mpKeySets[mode]->uType == 1 && mbUpperCase == 0) {
                                    mode = IM_01;
                                }

                                const PaneNameToCharCode* table = mpLanguageDep->mpKeySets[mode]->pPaneNameToCharCode;
                                const PaneNameToCharCode* found = NULL;
                                for (u16 i = 0; i < 0xC; i++) {
                                    if (util::strcmp(table[i].szPaneName, paneName)) {
                                        found = &table[i];
                                        break;
                                    }
                                }
                                mpHoldingPane = found;

                                if (flag != 0) {
                                    mTapIndex = 0xF;
                                    while (mpHoldingPane->wc[mTapIndex] == 0) {
                                        mTapIndex--;
                                    }
                                } else {
                                    mTapIndex = 0;
                                }
                            } else {
                                if (flag != 0) {
                                    mTapIndex--;
                                } else {
                                    mTapIndex++;
                                }

                                if (mTapIndex == 0x10) {
                                    mTapIndex = 0;
                                } else if (mTapIndex < 0) {
                                    mTapIndex = 0xF;
                                    while (mpHoldingPane->wc[mTapIndex] == 0) {
                                        mTapIndex--;
                                    }
                                }

                                if (mpHoldingPane->wc[mTapIndex] == 0) {
                                    mTapIndex = 0;
                                }
                            }

                            if (mpHoldingPane != NULL) {
                                SendCharCommand cmd = { 0, 0, 0, 0, 0, NULL };
                                cmd.mWChar = mpHoldingPane->wc[mTapIndex];
                                cmd.mpPane = mpHoldingPane;

                                int type = getInputType();
                                if (type == 1) {
                                    if (mpHoldingPane->wc[1] != 0x30 && mpHoldingPane->wc[0] != 0x20) {
                                        cmd.mbFlag = 1;
                                    }
                                }
                                if (getLanguage() == KR && mInputMode != 0) {
                                    cmd.mbFlag = 1;
                                }
                                if (getLanguage() == CN && mInputMode != 0) {
                                    cmd.mbFlag = 1;
                                }

                                if (mpHoldingPane->wc[1] == 0) {
                                    if (mbNumericWithDot != 0 && cmd.mWChar == 0x2A) {
                                        cmd.mWChar = 0x2E;
                                    }
                                    sendCommand(5, &cmd);
                                    mTapIndex = 0;
                                    mpHoldingPane = NULL;
                                } else {
                                    if (getLanguage() == JP && cmd.mWChar == 0x20 &&
                                        getInputMode() != IM_04 && getInputMode() != IM_02) {
                                        cmd.mWChar = 0x3000;
                                    }
                                    sendCommand(3, &cmd);
                                }
                            }
                        } else {
                            const PaneNameToCharCode* table = csKeySetNumber.pPaneNameToCharCode;
                            for (u16 i = 0; i < 0xC; i++) {
                                if (util::strcmp(table[i].szPaneName, paneName)) {
                                    u16 wc = table[i].wc[0];

                                    SendCharCommand cmd = { 0, 0, 0, 0, 0, NULL };
                                    cmd.mWChar = wc;
                                    cmd.mMode = mInputMode;
                                    cmd.mpPane = mpHoldingPane;

                                    QueryReply reply;
                                    sendCommand(0x20, &reply);

                                    if (wc == 0x30 && getLanguage() != KR) {
                                        if (reply.mbAvailable != 0) {
                                            sendCommand(6, NULL);
                                        }

                                        SendCharCommand cmd2 = csSendCharSpace;
                                        cmd2.mMode = mInputMode;
                                        cmd2.mpPane = mpHoldingPane;
                                        sendCommand(5, &cmd2);
                                        mTapIndex = 0;
                                        mpHoldingPane = NULL;
                                    } else {
                                        cmd.mpPane = NULL;
                                        for (u16 j = 0; j < 0xC; j++) {
                                            const PaneNameToCharCode* cur =
                                                mpLanguageDep->mpKeySets[mInputMode]->pPaneNameToCharCode;
                                            if (util::strcmp(cur[j].szPaneName, paneName)) {
                                                cmd.mpPane = &cur[j];
                                                break;
                                            }
                                        }

                                        if (mpLanguageDep->mpKeySets[mInputMode]->uType == 1 && mbShiftHeld == 0) {
                                            cmd.mMode = 1;
                                            const PaneNameToCharCode* lower =
                                                mpLanguageDep->mpKeySets[1]->pPaneNameToCharCode;
                                            for (u16 j = 0; j < 0xC; j++) {
                                                if (util::strcmp(lower[j].szPaneName, paneName)) {
                                                    cmd.mpPane = &lower[j];
                                                    break;
                                                }
                                            }
                                        }

                                        cmd.mWChar = convertToZiCellphoneInput_(cmd.mWChar);
                                        sendCommand(5, &cmd);
                                    }
                                }
                            }
                        }
                    }
                }

                if (command == 1) {
                    if (mpHoldingPane != NULL && util::strcmp(mpHoldingPane->szPaneName, paneName)) {
                        u16 wc = mpHoldingPane->wc[mTapIndex];
                        if (wc != 0x309B && wc != 0x309C) {
                            if (getLanguage() == JP && wc == 0x20 &&
                                getInputMode() != IM_04 && getInputMode() != IM_02) {
                                wc = 0x3000;
                            }

                            SendCharCommand cmd = csSendCharRelease;
                            cmd.mWChar = wc;
                            cmd.mpPane = mpHoldingPane;

                            if (getInputType() == 1) {
                                cmd.mbFlag = 1;
                            }
                            if (getLanguage() == KR && mInputMode != 0) {
                                cmd.mbFlag = 1;
                            }
                            if (getLanguage() == CN && mInputMode != 0) {
                                cmd.mbFlag = 1;
                            }

                            sendCommand(5, &cmd);
                        }
                        mTapIndex = 0;
                        mpHoldingPane = NULL;
                    }
                }
            }

            int Base::getInputMode() const {
                return mInputMode;
            }

            void Base::onCtrlKey_(VKeyCode code) {
                switch (code) {
                    case VK_LF:
                        sendCommand(7, NULL);
                        break;
                    case VK_DELETE:
                        sendCommand(1, NULL);
                        break;
                    case VK_TAG_00:
                        sendCommand(6, NULL);
                        setInputMode(IM_00);
                        break;
                    case VK_TAG_01:
                        sendCommand(6, NULL);
                        setInputMode(IM_01);
                        break;
                    case VK_TAG_02:
                        sendCommand(6, NULL);
                        setInputMode(IM_02);
                        break;
                    case VK_TAG_03:
                        sendCommand(6, NULL);
                        setInputMode(IM_03);
                        break;
                    case VK_OTHERS:
                        goSignInputMode();
                        break;
                    case VK_PRDC:
                        changePredictLanguage();
                        break;
                    case VK_SML_CPT:
                        setAbcMode(mbUpperCase == 0);
                        break;
                }
            }

            void Base::goSignInputMode() {}

            void Base::changePredictLanguage() {}

            void Base::updateFromReceiver(u32 command, void* data) {
                if (getLanguage() != JP) {
                    if ((s32)command == 0x21) {
                        setAbcMode(true);
                    }
                    if ((s32)command == 5 && ((u8*)data)[5] == 0) {
                        setAbcMode(false);
                        mbShiftHeld = 0;
                    }
                }
            }

            void Base::onActive() {
                u32 data = 0;
                sendCommand(0x12, &data);
                if (mInputMode == 0) {
                    u8 flag = csb20;
                    sendCommand(0x13, &flag);
                }
                if (mInputMode == 1) {
                    u8 flag = 0;
                    sendCommand(0x13, &flag);
                }
                if (mInputMode == 0) {
                    sendCommand(6, NULL);
                    changeInputMode((InputMode)mInputMode);
                }
                updateFixMode();
            }

            void Base::onClose() {}

            void Base::changeInputMode(InputMode mode) {
                mInputMode = mode;
                if (getLanguage() != JP) {
                    mbUpperCase = 1;
                    mbShiftHeld = 1;
                }
                if (mgr()->getCandidateBox() != NULL) {
                    mgr()->getCandidateBox()->checkValidation();
                }
                if (mode == IM_00) {
                    u8 flag = csb24;
                    sendCommand(0x13, &flag);
                }
                if (mode == IM_01) {
                    u8 flag = 0;
                    sendCommand(0x13, &flag);
                }
                updateFixMode();
                sendCommand(0x29, NULL);
            }

            bool Base::isZiActive() {
                InputModeReply reply = { 0, 0 };
                sendCommand(0x1F, &reply);
                s32 mode = reply.mMode;
                if (reply.mbEnabled != 0) {
                    return mode != 1;
                }
                return false;
            }

            bool Base::isAtokActive() {
                InputModeReply reply = { 0, 0 };
                sendCommand(0x1F, &reply);
                s32 mode = reply.mMode;
                if (reply.mbEnabled != 0 && mode == 1) {
                    return true;
                }
                return false;
            }

            void Base::setAbcMode(bool flag) {
                mbUpperCase = flag;
                if (flag != 0) {
                    mbShiftHeld = 1;
                }
            }

            void Base::doNumericMode(bool flag) {
                mbNumeric = flag;
                if (flag != 0) {
                    input::HKBManager::getInstance().SetModifierState(0x100, 0x100);
                    getLanguage();
                    changeInputMode(IM_03);
                    if (mgr()->getToolBar() != NULL) {
                        mgr()->getToolBar()->setQwerty(0);
                    }
                }
            }

            void Base::updateFixMode() {
                if (mgr()->getToolBar() != NULL && mgr()->getToolBar()->isQwerty() != 0) {
                    return;
                }
                switch (getLanguage()) {
                case JP: {
                    u8 flag = 0;
                    if (mInputMode == IM_04 || mInputMode == IM_02) {
                        flag = 1;
                    } else {
                        flag = 0;
                    }
                    sendCommand(0x14, &flag);
                    break;
                }
                }
            }

            wchar_t Base::convertToZiCellphoneInput_(wchar_t wc) {
                switch (wc) {
                    case 0x30: return 0xEFF1;
                    case 0x31: return 0xEFF2;
                    case 0x32: return 0xEFF3;
                    case 0x33: return 0xEFF4;
                    case 0x34: return 0xEFF5;
                    case 0x35: return 0xEFF6;
                    case 0x36: return 0xEFF7;
                    case 0x37: return 0xEFF8;
                    case 0x38: return 0xEFF9;
                    case 0x39: return 0xEFFA;
                }
                return wc;
            }

            int Base::getInputType() const {
                const KeySet* keySet = mpLanguageDep->mpKeySets[mInputMode];
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

            void Base::setLangKeyActive(bool flag) {
                mbLangKeyActive = flag;
                if (getLanguage() == KR || getLanguage() == CN) {
                    if (flag) {
                        setInputMode(IM_00);
                    } else if (getInputMode() == 0) {
                        setInputMode(IM_01);
                    }
                }
            }

            void Base::setInputMode(InputMode mode) {}

            LayoutByNW4R::~LayoutByNW4R() {
                mpEventHandler->~EventHandler();
                MEMFreeToAllocator(mpAllocator, mpEventHandler);
                nw4rmanager::AnmPane* pane;
                for (pane = (nw4rmanager::AnmPane*)nw4r::ut::List_GetNext(&mAnmPanes, NULL);
                     pane != NULL;
                     pane = (nw4rmanager::AnmPane*)nw4r::ut::List_GetNext(&mAnmPanes, NULL)) {
                    nw4r::ut::List_Remove(&mAnmPanes, pane);
                    pane->destroy(mpAllocator);
                }
            }


            void LayoutByNW4R::create(MEMAllocator* allocator) {
                mpAllocator = allocator;
                mTapIndex = 0;
                mInputMode = 0;
                mpHoldingPane = NULL;
                mbLocked = 0;
                mbNumericWithDot = 0;
                mbNumeric = 0;
                mbUpperCase = 1;
                mbShiftHeld = 1;
                unk_0x21 = 0;
                mpLanguageDep = &csLanguageDependencyData[getLanguage()];

                {
                    u32 data[3] = { 0, 0, 0 };
                    sendCommand(3, &data);
                }

                mpEventHandler = new (MEMAllocFromAllocator(allocator, sizeof(EventHandler))) EventHandler(this);
                nw4rmanager::Layout::createWithEventHandler(allocator, mpEventHandler);
                mpPaneManager->setAllComponentTriggerTarget(false);
                mpPaneManager->setAllBoundingBoxComponentTriggerTarget(true);

                for (u16 i = 0; i < 0x13; i++) {
                    CellPhoneAnmPane* pane = new (MEMAllocFromAllocator(allocator, sizeof(CellPhoneAnmPane)))
                        CellPhoneAnmPane(getPane(csPaneNameNormalAnimationKey[i].szPaneName), NULL, 0);
                    nw4r::ut::List_Append(&mAnmPanes, pane);

                    for (u16 j = 0; j < 5; j++) {
                        void* resBuf = mpMultiArcResourceAccessor->GetResource(0, csAninationFileForControlKey[j].szFileName, 0);
                        AnimTransformPane* anim = (AnimTransformPane*)
                            getLayout()->CreateAnimTransform(resBuf, mpMultiArcResourceAccessor);
                        if (csPaneNameNormalAnimationKey[i].uLinkedAnm != NULL) {
                            pane->forceAddAnimation(allocator, csAninationFileForControlKey[j].uType, anim,
                                                    csPaneNameNormalAnimationKey[i].uLinkedAnm, false, true);
                        } else {
                            pane->addAnimation(allocator, csAninationFileForControlKey[j].uType, anim, false, true);
                        }
                    }
                }

                for (u16 i = 0; i < 4; i++) {
                    CellPhoneControlAnmPane* pane = new (MEMAllocFromAllocator(allocator, sizeof(CellPhoneControlAnmPane)))
                        CellPhoneControlAnmPane(getPane(csPaneNameToggleAnimationKey[i].szPaneName), NULL, 1);
                    nw4r::ut::List_Append(&mAnmPanes, pane);

                    for (u16 j = 0; j < 6; j++) {
                        void* resBuf = mpMultiArcResourceAccessor->GetResource(0, csAninationFileForToggleKey[j].szFileName, 0);
                        AnimTransformPane* anim = (AnimTransformPane*)
                            getLayout()->CreateAnimTransform(resBuf, mpMultiArcResourceAccessor);
                        if (csPaneNameToggleAnimationKey[i].uLinkedAnm != NULL) {
                            pane->forceAddAnimation(allocator, csAninationFileForToggleKey[j].uType, anim,
                                                    csPaneNameToggleAnimationKey[i].uLinkedAnm, false, true);
                        } else {
                            pane->addAnimation(allocator, csAninationFileForToggleKey[j].uType, anim, false, true);
                        }
                    }
                }

                nw4r::lyt::Pane* rootPane = mpLayout->GetRootPane();
                rootPane->FindPaneByName("P_spaceBT_JP", true)->GetMaterial()->GetTexture(&mSpaceTexObjJP, 0);
                rootPane->FindPaneByName("P_spaceBT_CN", true)->GetMaterial()->GetTexture(&mSpaceTexObjCN, 0);
                rootPane->FindPaneByName("P_spaceBT_KR", true)->GetMaterial()->GetTexture(&mSpaceTexObjKR, 0);

                init();
                setLanguage(getLanguage());
            }

            void CellPhoneAnmPane::init() {
                mState = 0;
            }

            void LayoutByNW4R::init() {
                mTapIndex = 0;
                mInputMode = 0;
                mpHoldingPane = NULL;
                mbLocked = 0;
                mbNumericWithDot = 0;
                mbNumeric = 0;
                mbUpperCase = 1;
                mbShiftHeld = 1;
                unk_0x21 = 0;
                mpLanguageDep = &csLanguageDependencyData[getLanguage()];

                {
                    u32 data[3] = { 0, 0, 0 };
                    sendCommand(3, &data);
                }

                getAnmPane(IM_00)->changeAnimation(0);
                getAnmPane(IM_01)->changeAnimation(0);
                getAnmPane(IM_02)->changeAnimation(0);
                getAnmPane(IM_03)->changeAnimation(0);
                getAnmPane((InputMode)mInputMode)->changeAnimation(5);

                setLineFeedButton(true);
                doNumericMode(0);
                setPredictLanguageButton(true);
                setSignWindowButton(true);

                setVisible("W_ChngTag_00", true);
                setVisible("W_ChngTag_01", true);
                setVisible("W_ChngTag_02", true);
                setVisible("W_ChngTag_03", true);

                const PaneNameToLinkedAnm* pAnm = csPaneNameToggleAnimationKey;
                for (int i = 0; i < 4; i++, pAnm++) {
                    char name[0x11];
                    memset(name, 0, 0x11);
                    strncpy(name, pAnm->szPaneName, strlen(pAnm->szPaneName));
                    name[0] = 'T';
                    nw4r::lyt::Pane* textPane = getPane(name);
                    nw4r::lyt::Pane* pane = getPane(pAnm->szPaneName);
                    if (mpLanguageDep->mpKeySets[i] == NULL) {
                        pane->SetVisible(false);
                    } else {
                        pane->SetVisible(true);
                        ((nw4r::lyt::TextBox*)textPane)->SetString(mpLanguageDep->mpKeySets[i]->szKeySetName, 0);
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

                changeInputMode((InputMode)mInputMode);
                setLangKeyActive(true);

                u32 data[2] = { 0, 0 };
                sendCommand(0x1F, &data);
                updatePredictLanguage((CommandReceiver::ChangePredictMode*)&data);

                initPaneLastDrawReceived();
                mpLayout->Animate(0);
                mpLayout->CalculateMtx(mDrawInfo);
                nw4r::lyt::Pane* spacePane = mpLayout->GetRootPane()->FindPaneByName("P_spaceBT_JP", true);
                nw4r::lyt::Pane* henkanPane = mpLayout->GetRootPane()->FindPaneByName("P_HENKAN_JP", true);
                spacePane->SetVisible(true);
                henkanPane->SetVisible(false);
            }

            void LayoutByNW4R::draw() {
                nw4rmanager::Layout::draw();
            }

            void LayoutByNW4R::calc() {
                nw4rmanager::Layout::calc();

                nw4r::lyt::Pane* spacePane = mpLayout->GetRootPane()->FindPaneByName("P_spaceBT_JP", true);
                nw4r::lyt::Pane* henkanPane = mpLayout->GetRootPane()->FindPaneByName("P_HENKAN_JP", true);
                if (mgr()->getInputForm()->canConvert()) {
                    spacePane->SetVisible(false);
                    henkanPane->SetVisible(true);
                } else {
                    spacePane->SetVisible(true);
                    henkanPane->SetVisible(false);
                }
            }

            void LayoutByNW4R::update() {}

            void LayoutByNW4R::onKey(u32 command, void* data) {
                Base::onKey(command, data);
                const char* paneName = *(const char**)data;
                if (mbLocked != 0) {
                    return;
                }
                if (command != 4) {
                    return;
                }

                VKeyCode code = VK_NONE;
                for (u16 i = 0; i < 0xC; i++) {
                    if (util::strcmp(csPaneNameToControlKey[i].szPaneName, paneName)) {
                        code = (VKeyCode)csPaneNameToControlKey[i].uCode;
                        break;
                    }
                }
                if (code == VK_NONE) {
                    return;
                }

                switch (code) {
                    case VK_TAG_02:
                    case VK_TAG_03:
                    case VK_TAG_00:
                    case VK_TAG_01:
                        mpEventObserver->onSE((sound::SE)0xD);
                        break;
                    case VK_SML_CPT:
                        if (mbUpperCase == 0) {
                            mpEventObserver->onSE((sound::SE)0x15);
                        } else {
                            mpEventObserver->onSE((sound::SE)0x14);
                        }
                        break;
                    case VK_SPACE:
                        if (mgr()->getInputForm()->canConvert()) {
                            sendCommand(0x28, NULL);
                        } else {
                            InputWCharCommand cmd = csInputSpaceChar;
                            sendCommand(0, &cmd);
                        }
                        break;
                }
            }

            void LayoutByNW4R::onActive() {
                u32 data = 0;
                sendCommand(0x12, &data);
                if (mInputMode == 0) {
                    u8 flag = csb20;
                    sendCommand(0x13, &flag);
                }
                if (mInputMode == 1) {
                    u8 flag = 0;
                    sendCommand(0x13, &flag);
                }
                if (mInputMode == 0) {
                    sendCommand(6, NULL);
                    changeInputMode((InputMode)mInputMode);
                }
                updateFixMode();
                nw4rmanager::Layout::init();
            }

            void LayoutByNW4R::onClose() {
                initPaneLastDrawReceived();
                changeAnimationAllToNormal();
            }

            void LayoutByNW4R::updateFromReceiver(u32 command, void* data) {
                if (getLanguage() != JP) {
                    if ((s32)command == 0x21) {
                        setAbcMode(true);
                    }
                    if ((s32)command == 5 && ((u8*)data)[5] == 0) {
                        setAbcMode(false);
                        mbShiftHeld = 0;
                    }
                }
                switch ((s32)command) {
                case 0x1D:
                    updatePredictLanguage((CommandReceiver::ChangePredictMode*)data);
                }
            }

            void LayoutByNW4R::changeInputMode(InputMode mode) {
                mInputMode = mode;
                if (getLanguage() != JP) {
                    mbUpperCase = 1;
                    mbShiftHeld = 1;
                }
                if (mgr()->getCandidateBox() != NULL) {
                    mgr()->getCandidateBox()->checkValidation();
                }
                if (mode == IM_00) {
                    u8 flag = csb24;
                    sendCommand(0x13, &flag);
                }
                if (mode == IM_01) {
                    u8 flag = 0;
                    sendCommand(0x13, &flag);
                }
                updateFixMode();
                sendCommand(0x29, NULL);

                if (getLanguage() == JP) {
                    if (mbUpperCase == 0 && mode == IM_02) {
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
                    }
                } else {
                    setVisible("P_CPkey_dakuten", false);
                }
                changeKeyTop(mpLanguageDep->mpKeySets[mode]->pPaneNameToCharCode);
                initPaneLastDrawReceived();
            }

            void LayoutByNW4R::changeKeyTop(const PaneNameToCharCode* table) {
                for (u16 i = 0; i < 0xC; i++) {
                    char name[0x11];
                    util::replaceChar(name, 0x11, table[i].szPaneName, 0, 'T');
                    nw4r::lyt::TextBox* textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(
                        mpLayout->GetRootPane()->FindPaneByName(name, true));
                    if (textBox != NULL) {
                        textBox->SetString(&table[i].szPaneDisp[0], 0);
                    }
                }
                changeSpaceKeyTop(table);
            }

            void LayoutByNW4R::changeSpaceKeyTop(const PaneNameToCharCode* table) {
                if (getLanguage() == JP) {
                    char name[0x11];
                    util::replaceChar(name, 0x11, table[10].szPaneName, 0, 'T');
                    nw4r::lyt::TextBox* textBox = (nw4r::lyt::TextBox*)
                        mpLayout->GetRootPane()->FindPaneByName(name, true);
                    if (table[10].wc[0] == 0xE057) {
                        if (unk_0x21 == 0) {
                            textBox->SetString(csSpaceZero, 0);
                        } else {
                            textBox->SetString(csSpace, 0);
                        }
                    }
                }
            }

            nw4rmanager::AnmPane* LayoutByNW4R::getAnmPane(InputMode mode) {
                switch (mode) {
                    case IM_02: return searchAnmPane(csPaneNameToggleAnimationKey[2].szPaneName);
                    case IM_03: return searchAnmPane(csPaneNameToggleAnimationKey[3].szPaneName);
                    case IM_00: return searchAnmPane(csPaneNameToggleAnimationKey[0].szPaneName);
                    case IM_01: return searchAnmPane(csPaneNameToggleAnimationKey[1].szPaneName);
                }
                return NULL;
            }

            void LayoutByNW4R::throwReleaseForAll() {
                for (nw4rmanager::AnmPane* pane = (nw4rmanager::AnmPane*)nw4r::ut::List_GetNext(&mAnmPanes, NULL);
                     pane != NULL;
                     pane = (nw4rmanager::AnmPane*)nw4r::ut::List_GetNext(&mAnmPanes, pane)) {
                    if (((CellPhoneAnmPane*)pane)->getKeyType() == 0) {
                        pane->onAnmEvent((nw4rmanager::AnmPane::AnmPaneEvent)2);
                    }
                }
            }

            u32 CellPhoneAnmPane::getKeyType() const {
                return mKeyType;
            }

            void LayoutByNW4R::changeAnimationAllToNormal() {
                for (nw4rmanager::AnmPane* pane = (nw4rmanager::AnmPane*)nw4r::ut::List_GetNext(&mAnmPanes, NULL);
                     pane != NULL;
                     pane = (nw4rmanager::AnmPane*)nw4r::ut::List_GetNext(&mAnmPanes, pane)) {
                    if (((CellPhoneAnmPane*)pane)->getKeyType() == 0) {
                        pane->changeAnimation(0);
                    }
                }
            }

            void LayoutByNW4R::setLanguage(Language language) {
                meLanguage = language;
                nw4r::lyt::Pane* rootPane = mpLayout->GetRootPane();
                if (language == JP) {
                    rootPane->FindPaneByName("P_spaceBT_JP", true)->GetMaterial()->SetTexture(0, mSpaceTexObjJP);
                } else if (language == CN) {
                    rootPane->FindPaneByName("P_spaceBT_JP", true)->GetMaterial()->SetTexture(0, mSpaceTexObjCN);
                } else if (language == KR) {
                    rootPane->FindPaneByName("P_spaceBT_JP", true)->GetMaterial()->SetTexture(0, mSpaceTexObjKR);
                }
                if (mpLayout != NULL) {
                    init();
                    initPaneLastDrawReceived();
                }
            }

        }  // namespace cellphonetype

        void KeyboardBase::setLanguage(Language language) {
            meLanguage = language;
        }

        namespace cellphonetype {

            void LayoutByNW4R::changePredictLanguage() {
                throwReleaseForAll();
                InputModeReply reply = { 0, 0 };
                sendCommand(0x1F, &reply);
                mpPredictLanguageDialog->open((inputform::Base::PredictMode)reply.mMode, this);
            }

            void LayoutByNW4R::updatePredictLanguage(CommandReceiver::ChangePredictMode* mode) {
                if (getLanguage() != JP) {
                    return;
                }
                if (mode->mbPredictOn == 0) {
                    setVisible("N_prdc_EU_ON", false);
                    setVisible("N_prdc_EU_OFF", true);
                    unk_0x21 = 0;
                } else {
                    setVisible("N_prdc_EU_ON", true);
                    setVisible("N_prdc_EU_OFF", false);
                    unk_0x21 = 1;
                }
                ((nw4r::lyt::TextBox*)getPane("N_prdc_EU_lang"))->SetString(csszPredictLanguage[mode->muLanguage], 0);
                changeSpaceKeyTop(mpLanguageDep->mpKeySets[mInputMode]->pPaneNameToCharCode);
            }

            void LayoutByNW4R::setAbcMode(bool flag) {
                mbUpperCase = flag;
                if (flag != 0) {
                    mbShiftHeld = 1;
                }
                if (getLanguage() == JP) {
                    InputMode mode = IM_02;
                    if (mbUpperCase == 0) {
                        mode = IM_04;
                    }
                    changeKeyTop(mpLanguageDep->mpKeySets[mode]->pPaneNameToCharCode);
                    mpEventObserver->onSE((sound::SE)0x12);
                } else {
                    const KeySet* keySet = mpLanguageDep->mpKeySets[mInputMode];
                    if (keySet->uType == 1) {
                        InputMode mode = IM_00;
                        if (mbUpperCase == 0) {
                            mode = IM_01;
                        }
                        changeKeyTop(mpLanguageDep->mpKeySets[mode]->pPaneNameToCharCode);
                    }
                }
            }

            void LayoutByNW4R::goSignInputMode() {
                bool flag = false;
                if (mInputMode == IM_03) {
                    flag = true;
                }
                mpSignWindow->open(this, flag);
                throwReleaseForAll();
            }

            void LayoutByNW4R::doNumericMode(bool flag) {
                mbNumeric = flag;
                if (flag != 0) {
                    input::HKBManager::getInstance().SetModifierState(0x100, 0x100);
                    getLanguage();
                    changeInputMode(IM_03);
                    if (mgr()->getToolBar() != NULL) {
                        mgr()->getToolBar()->setQwerty(0);
                    }
                }
                if (flag != 0) {
                    bool visible = !flag;
                    setVisible("W_smlCptChngeBT", visible);
                    setVisible("W_CPkey_09", visible);
                    setVisible("P_CPkey_dakuten", visible);
                    setVisible("W_smlCptChngeBT", visible);
                    setVisible("W_prdcModeBT_EU", visible);
                    setVisible("W_othersBT_EU", visible);
                    setVisible("W_spaceBT_JP", visible);
                    setVisible("W_smlCptChngeBT", visible);
                    setVisible("W_othersBT_JP", visible);
                    setVisible("W_CPkey_Prdc_JP", visible);
                    setVisible("W_CPkey_09", visible);
                    setVisible("W_CPkey_11", visible);
                    setVisible("W_ChngTag_00", visible);
                    setVisible("W_ChngTag_01", visible);
                    setVisible("W_ChngTag_02", visible);
                    setVisible("W_ChngTag_03", visible);
                }
            }

            void LayoutByNW4R::doNumericWithDotMode(bool flag) {
                doNumericMode(flag);
                setString("T_CPkey_11", L".");
                setVisible("W_CPkey_11", flag);
                mbNumericWithDot = 1;
            }

            void LayoutByNW4R::setLineFeedButton(bool flag) {
                mbLineFeed = flag;
                setVisible("W_CPkey_LF", mbLineFeed);
            }

            void LayoutByNW4R::setPredictLanguageButton(bool flag) {
                setVisible("W_prdcModeBT_EU", flag);
            }

            void LayoutByNW4R::setSignWindowButton(bool flag) {
                if (!flag) {
                    setVisible("W_othersBT_EU", flag);
                    setVisible("W_othersBT_JP", flag);
                } else {
                    setVisible("W_othersBT_EU", false);
                    setVisible("W_othersBT_JP", false);
                    if (getLanguage() == JP) {
                        setVisible("W_othersBT_JP", true);
                    } else {
                        setVisible("W_othersBT_EU", true);
                    }
                }
            }

            void LayoutByNW4R::setInputMode(InputMode mode) {
                if (mpLanguageDep->mpKeySets[mInputMode] == NULL) {
                    mode = IM_03;
                }
                changeInputMode(mode);
                getAnmPane(IM_00)->changeAnimation(0);
                getAnmPane(IM_01)->changeAnimation(0);
                getAnmPane(IM_02)->changeAnimation(0);
                getAnmPane(IM_03)->changeAnimation(0);
                getAnmPane((InputMode)mInputMode)->changeAnimation(5);
                mpLayout->Animate(0);
                mpLayout->CalculateMtx(mDrawInfo);
            }

            void LayoutByNW4R::setUpperCaseJP(bool flag) {
                if (getLanguage() == JP) {
                    mbUpperCase = flag;
                }
            }

            bool LayoutByNW4R::updateInput(textinput::input::HKBManager& hkbManager) {
                if (mgr()->getToolBar()->isEnableKeytopChange() != 0) {
                    input::HKBManager::KeySet keySet = hkbManager.GetTriggeredKeySet();
                    if (keySet.IsValid()) {
                        if (mpHoldingPane != NULL) {
                            u32 data[3] = { 0, 0, 0 };
                            data[0] = (u32)mpHoldingPane->szPaneName;
                            onKey(1, &data);
                        }
                        changeAnimationAllToNormal();
                        mgr()->getToolBar()->setQwertyWithSE(1);
                        if (mgr()->getPCKeyboard()->isABC() == 0) {
                            mgr()->getPCKeyboard()->setABC(1);
                        }
                    }
                } else {
                    input::HKBManager::KeySet keySet = hkbManager.GetTriggeredKeySet();
                    for (; keySet.IsValid(); keySet = keySet.GetNext()) {
                        nw4rmanager::AnmPane* pane = NULL;
                        u8 key = keySet.GetKey();
                        wchar_t wc = keySet.GetWChar();
                        if (key == 0x58 || key == 0x28) {
                            if ((hkbManager.GetModifierState() & 4) == 0) {
                                pane = searchAnmPane("W_CPkey_LF");
                            }
                        } else {
                            pane = searchAnmPane(wc);
                        }
                        if (pane != NULL) {
                            pane->onAnmEvent((nw4rmanager::AnmPane::AnmPaneEvent)0);
                        }
                    }

                    keySet = hkbManager.GetRepeatedKeySet();
                    for (; keySet.IsValid(); keySet = keySet.GetNext()) {
                        nw4rmanager::AnmPane* pane = NULL;
                        u8 key = keySet.GetKey();
                        wchar_t wc = keySet.GetWChar();
                        if (key == 0x4C || key == 0x2A) {
                            if ((hkbManager.GetModifierState() & 4) == 0) {
                                pane = searchAnmPane("W_CPkey_DELETE");
                            }
                        } else {
                            pane = searchAnmPane(wc);
                        }
                        if (pane != NULL) {
                            pane->onAnmEvent((nw4rmanager::AnmPane::AnmPaneEvent)0);
                        }
                    }
                }
                return false;
            }

        }  // namespace cellphonetype
    }  // namespace keyboard

    namespace toolbar {

        bool LayoutByNW4R::isEnableKeytopChange() const {
            return mbIsEnableQwertyChg;
        }

    }  // namespace toolbar

    namespace keyboard {

        keyboard::pctype::LayoutByNW4R* Manager::getPCKeyboard() {
            return mpPCKeyboard;
        }

        namespace cellphonetype {

            void LayoutByNW4R::setLangKeyActive(bool flag) {
                mbLangKeyActive = flag;
                if (getLanguage() == KR || getLanguage() == CN) {
                    if (flag) {
                        setInputMode(IM_00);
                    } else if (getInputMode() == 0) {
                        setInputMode(IM_01);
                    }
                }
                if (getLanguage() == KR || getLanguage() == CN) {
                    setVisible("W_ChngTag_00", flag);
                    setVisible("T_ChngTag_00", flag);
                }
            }

            void LayoutByNW4R::resetHoldingButton() {
                mpHoldingPane = NULL;
                mTapIndex = 0;
            }

            void CellPhoneAnmPane::changeAnimation(u32 id) {
                mState = id;
                nw4rmanager::AnmPane::changeAnimation(id == 7 ? 2 : id);
            }

            void CellPhoneAnmPane::onAnmEvent(nw4rmanager::AnmPane::AnmPaneEvent paneEvent) {
                switch (mState) {
                    case 0: {
                        if (paneEvent == 1) changeAnimation(1);
                        if (paneEvent == 0) changeAnimation(7);
                        break;
                    }
                    case 1: {
                        if (paneEvent == 4) changeAnimation(3);
                        if (paneEvent == 2) changeAnimation(2);
                        if (paneEvent == 0) changeAnimation(4);
                        break;
                    }
                    case 3: {
                        if (paneEvent == 2) changeAnimation(2);
                        if (paneEvent == 0) changeAnimation(4);
                        break;
                    }
                    case 2: {
                        if (paneEvent == 4) changeAnimation(0);
                        if (paneEvent == 1) changeAnimation(1);
                        if (paneEvent == 0) changeAnimation(7);
                        break;
                    }
                    case 4: {
                        if (paneEvent == 4) changeAnimation(3);
                        if (paneEvent == 2) changeAnimation(2);
                        if (paneEvent == 0) changeAnimation(4);
                        break;
                    }
                    case 7: {
                        if (paneEvent == 4) changeAnimation(0);
                        if (paneEvent == 1) changeAnimation(1);
                        if (paneEvent == 0) changeAnimation(7);
                        break;
                    }
                }
            }

            void CellPhoneControlAnmPane::onAnmEvent(nw4rmanager::AnmPane::AnmPaneEvent paneEvent) {
                if (paneEvent == 5) {
                    if (mState != 6) {
                        if (mState == 5) {
                            changeAnimation(6);
                            return;
                        }
                        if (mState != 0 && mState != 2) {
                            changeAnimation(2);
                            return;
                        }
                    }
                }
                if (paneEvent == 0) {
                    changeAnimation(4);
                    return;
                }
                switch (mState) {
                    case 0: {
                        if (paneEvent == 1) changeAnimation(1);
                        break;
                    }
                    case 1: {
                        if (paneEvent == 4) changeAnimation(3);
                        if (paneEvent == 2) changeAnimation(2);
                        if (paneEvent == 0) changeAnimation(4);
                        break;
                    }
                    case 3: {
                        if (paneEvent == 2) changeAnimation(2);
                        if (paneEvent == 0) changeAnimation(4);
                        break;
                    }
                    case 2: {
                        if (paneEvent == 4) changeAnimation(0);
                        break;
                    }
                    case 6: {
                        if (paneEvent == 4) changeAnimation(0);
                        if (paneEvent == 1) changeAnimation(1);
                        break;
                    }
                    case 4: {
                        if (paneEvent == 4) changeAnimation(5);
                        break;
                    }
                }
            }

            void EventHandler::onTiEvent(gui::PaneComponent* paneComponent, u32 event, TiEventHandler::Input* input) {
                nw4r::lyt::Pane* pane = paneComponent->getPane();
                const char* paneName = pane->GetName();

                if (paneName[0] == 'B') {
                    char name[0x11];
                    util::replaceChar(name, 0x11, paneName, 0, 'W');
                    nw4rmanager::AnmPane* anmPane = mpLayout->searchAnmPane(name);
                    if (anmPane != NULL) {
                        switch (event) {
                            case 4: {
                                bool normal = false;
                                if ((input->field_0x0C & 0x800) != 0) {
                                    normal = true;
                                } else if ((input->field_0x0C & 0x400) != 0) {
                                    const char** pp = csPaneNameNormalKey;
                                    for (u16 i = 0; i < 0xC; i++, pp++) {
                                        if (util::strcmp(*pp, paneName)) {
                                            normal = true;
                                            break;
                                        }
                                    }
                                }
                                if (normal) {
                                    if (((CellPhoneAnmPane*)anmPane)->getKeyType() == 1) {
                                        nw4r::ut::List& list = mpLayout->getAnmPaneList();
                                        for (nw4rmanager::AnmPane* p = (nw4rmanager::AnmPane*)nw4r::ut::List_GetNext(&list, NULL);
                                             p != NULL;
                                             p = (nw4rmanager::AnmPane*)nw4r::ut::List_GetNext(&list, p)) {
                                            if (p != anmPane && ((CellPhoneAnmPane*)p)->getKeyType() == 1) {
                                                p->onAnmEvent((nw4rmanager::AnmPane::AnmPaneEvent)5);
                                            }
                                        }
                                    }
                                    anmPane->onAnmEvent((nw4rmanager::AnmPane::AnmPaneEvent)0);
                                }
                                break;
                            }
                            case 1:
                                anmPane->onAnmEvent((nw4rmanager::AnmPane::AnmPaneEvent)2);
                                break;
                            case 0:
                                mpEventObserver->onSE((sound::SE)4);
                                mpLayout->setPaneLastDrawReceived(anmPane->getPane());
                                anmPane->onAnmEvent((nw4rmanager::AnmPane::AnmPaneEvent)1);
                                break;
                        }
                    }
                }

                SendKeyData sendData = { 0, 0, 0, 0 };
                sendData.paneName = paneName;

                if (event == 4) {
                    if ((input->field_0x0C & 0x800) != 0) {
                        sendData.flag = 0;
                        mpLayout->onKey(4, &sendData);
                    } else if ((input->field_0x0C & 0x400) != 0) {
                        bool normal = false;
                        const char** pp = csPaneNameNormalKey;
                        for (u16 i = 0; i < 0xC; i++, pp++) {
                            if (util::strcmp(*pp, paneName)) {
                                normal = true;
                                break;
                            }
                        }
                        if (normal) {
                            sendData.flag = 1;
                            mpLayout->onKey(4, &sendData);
                            paneComponent->setFlightDuration(input->field_0x00, 0);
                        }
                    }
                }
                if (event == 1) {
                    mpLayout->onKey(1, &sendData);
                }
                if (event == 2) {
                    if ((input->field_0x10 & 0x800) != 0 && (input->field_0x0C & 0x800) == 0) {
                        if (util::strcmp(csPaneNameNormalKey[0xD], paneName) ||
                            util::strcmp(csPaneNameNormalKey[0x10], paneName)) {
                            if (paneComponent->isDragging(input->field_0x00)) {
                                u32 duration = mpLayout->getFlightDuration(input->field_0x00, paneName);
                                if (duration >= 0x1E && duration % 9 == 0) {
                                    char name2[0x11];
                                    util::replaceChar(name2, 0x11, paneName, 0, 'W');
                                    mpLayout->searchAnmPane(name2)->onAnmEvent((nw4rmanager::AnmPane::AnmPaneEvent)0);
                                    mpLayout->onKey(4, &sendData);
                                }
                            }
                        }
                    }
                    if (mpLayout->getFlightDuration(input->field_0x00, paneName) == 0x5A) {
                        sendData.flag2 = 1;
                        mpLayout->onKey(1, &sendData);
                    }
                }
            }

        }  // namespace cellphonetype
    }  // namespace keyboard

    namespace gui {

        void GUIComponent::setFlightDuration(int point, u16 flightDir) {
            mFlightDuration[point] = flightDir;
        }

    }  // namespace gui

    namespace keyboard {
        namespace cellphonetype {

            bool LayoutByNW4R::updateInput(int point, f32 x, f32 y, u32 trig, u32 hold, u32 release, void* data) {
                return nw4rmanager::Layout::updateInput(point, x, y, trig, hold, release, data);
            }

            void Base::doInput() {}

            bool Base::isUpperCase() {
                return mbUpperCase;
            }

            bool Base::isHoldingButton() const {
                return mpHoldingPane != NULL;
            }

            bool Base::isNumericWithDot() const {
                return mbNumericWithDot;
            }

            bool Base::isNumeric() const {
                return mbNumeric;
            }

            bool Base::isLocked() const {
                return mbLocked;
            }

            int Base::getType() {
                return 1;
            }

            void LayoutByNW4R::setSignWindow(signwindow::LayoutByNW4R* window) {
                mpSignWindow = window;
            }

            void LayoutByNW4R::setPredictLanguageDialog(predictlang::LayoutByNW4R* dialog) {
                mpPredictLanguageDialog = dialog;
            }

            void LayoutByNW4R::setCommandReceiver(CommandReceiver* receiver) {
                CommandSender::setCommandReceiver(receiver);
                init();
            }

            void Base::setUpperCaseJP(bool flag) {}

            void Base::draw() {}

        }  // namespace cellphonetype
    }  // namespace keyboard
}  // namespace textinput
