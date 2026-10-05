#include "scene/channelSelect/iplChannelObj.h"

#include <private/es.h>
#include <revolution/os.h>
#include <revolution/sc.h>

#include "iplSound.h"
#include "iplSystem.h"

namespace ipl {
    namespace scene {
        // clang-format off
        extern "C" char scCursur_a[] = "Cursur_a";

        static const char* scCursur = scCursur_a;

        static const char* scCursorAnims[] = {
            "my_IplTop_d_FocusOff.brlan",
            "my_IplTop_d_FocusOn.brlan",
            "my_IplTop_d_Select.brlan",
        };

        extern "C" const char* scPaneName_T_Balloon = "T_Balloon";

        extern "C" const char* scPaneName_W_Base = "W_Base";
        extern "C" const char* scPaneName_W_Shade = "W_Shade";

        static const char* scLangGroups[] = {
            "JPN",
            "ENG",
            "GER",
            "FRA",
            "SPA",
            "ITA",
            "NED",
            "CHN",
            "ENG",
            "KOR",
        };

        extern "C" char scExport_Calc[] = "Calc";
        extern "C" char scExport_Create[] = "Create";

        #pragma pack(1)
        struct ModuleData {
            const char* langGroupLookup[SC_PRODUCT_AREA_MAX][16];
            char resolved[40];
            char unresolved[45];
            char threadCalc[11];
            char iconBrlyt[11];
            char iconBrlan[11];
            char iconWholeBrlan[17];
        };
        #pragma pack()

        extern "C" ModuleData scModuleData = {
            {
                {
                    "JPN",
                    NULL,
                },
                {
                    "ENG",
                    "FRA",
                    "SPA",
                    NULL,
                },
                {
                    "ENG",
                    "FRA",
                    "GER",
                    "SPA",
                    "ITA",
                    "NED",
                    NULL,
                },
                {
                    NULL,
                },
                {
                    NULL,
                },
                {
                    NULL,
                },
                {
                    "KOR",
                    NULL,
                },
                {
                    NULL,
                },
                {
                    NULL,
                },
                {
                    NULL,
                },
                {
                    NULL,
                },
                {
                    "CHN",
                    NULL,
                },
            },
            "Module's ImportSymbol is resolved all.\n",
            "%d module's ImportSymbols are not resolved.\n",
            "ThreadCalc",
            "icon.brlyt",
            "icon.brlan",
            "icon_Whole.brlan",
        };

        extern "C" char scBrlan_RsoFmt[] = "%s_Rso%d.brlan";
        extern "C" char scBrlan_icon_Start[] = "icon_Start.brlan";
        extern "C" char scArc[] = "arc";

        static const u32 scLangLookup[SC_PRODUCT_AREA_MAX][16] = {
            // Japan
            {
                SC_LANG_JAPANESE,
                -1
            },
            // USA
            {
                SC_LANG_ENGLISH,
                SC_LANG_FRENCH,
                SC_LANG_SPANISH,
                -1
            },
            // Europe
            {
                SC_LANG_ENGLISH,
                SC_LANG_FRENCH,
                SC_LANG_GERMAN,
                SC_LANG_SPANISH,
                SC_LANG_ITALIAN,
                SC_LANG_DUTCH,
                -1
            },
            {
                -1
            },
            {
                -1
            },
            {
                -1
            },
            // Korean
            {
                SC_LANG_KOREAN,
                -1
            },
            {
                -1
            },
            {
                -1
            },
            {
                -1
            },
            {
                -1
            },
            // China
            {
                SC_PRODUCT_AREA_HKG,
                -1
            },
        };
        
        const float cfChanThumbOfss[][2] = {
            {
                64.0f, 48.0f
            },
            {
                85.0f, 48.0f
            }
        };
        // clang-format on

        ChannelObj::ChannelObj(EGG::Heap* heap, int page, int index)
            : mpMainHeap(heap), mpCursorHeap(NULL), mpBalloonHeap(NULL), mpDiskHeap(NULL), mState(STATE_LOAD_THUMBNAIL), mChanPage(page),
              mChanIndex(index), mpBasePane(NULL), mpNoDiskLayout(NULL), mpNoDiskAnim(NULL), mpDiskLayout(NULL), mpDiskAnim(NULL),
              mpCursorLayout(NULL), mCursorState(0), mPendingCursorState(0), mpBalloonLayout(NULL), mBalloonState(0), mPendingBalloonState(0), mBalloonWaitFrame(0), mPointCount(0),
              mpNwc24NewGroup(NULL), mpNwc24NewAnim(NULL), mpNwc24NewPlayAnim(false), mNewMessageState(0), mNewMessageFrame(0),
              mThumbWidth(cfChanThumbOfss[SCGetAspectRatio()][0]), mThumbHeight(cfChanThumbOfss[SCGetAspectRatio()][1]), mpExtModuleWorkHeap(NULL),
              mpModuleHeap(NULL), mpPrevModuleHeap(NULL), mbModuleTerminated(false), mpModuleThread(NULL),
              mExtModuleState(EXT_MODULE_STATE_UNAVAILABLE), mbModuleFlag(false), mModuleCount(MAX_MODULE_COUNT), mMaxModuleCount(MAX_MODULE_COUNT),
              mpRSOHeader(NULL), mpRSOBss(NULL), mpCSHeap(NULL) {
            if (SCGetAspectRatio() == SC_ASPECT_RATIO_16x9) {
                nw4r::ut::Rect projRect4x3;
                System::getProjectionRect4x3(&projRect4x3);
                nw4r::ut::Rect projRect16x9;
                System::getProjectionRect16x9(&projRect16x9);

                mLocationAdjust = projRect16x9.GetWidth() / projRect4x3.GetWidth();
            } else {
                mLocationAdjust = 1.0f;
            }

            memset(mpModuleAnims, 0, sizeof(mpModuleAnims));
        }

        ChannelObj::~ChannelObj() {
            if (mpThumbFile != NULL) {
                delete mpThumbFile;
            }

            if (isDiskChannel()) {
                destroyDiskLayout();
            } else {
                mpThumbLayout->destroyHeap();
            }

            if (mpCursorLayout != NULL) {
                delete mpCursorLayout;
            }

            if (mpBalloonLayout != NULL) {
                delete mpBalloonLayout;
            }
        }

        void ChannelObj::prepare() {
            if (mState == STATE_LOAD_THUMBNAIL) {
                mState = loadThumbnailAsync();
            }
        }

        void ChannelObj::setHeaps(EGG::Heap* cursorHeap, EGG::Heap* balloonHeap) {
            mpCursorHeap = cursorHeap;
            mpBalloonHeap = balloonHeap;
        }

        void ChannelObj::setDiskLayouts(layout::Object* diskLyt, layout::Animator* diskAnim, EGG::Heap* diskHeap) {
            mpNoDiskLayout = diskLyt;
            mpNoDiskAnim = diskAnim;
            mpDiskHeap = diskHeap;
        }

        void ChannelObj::setBasePane(const nw4r::lyt::Pane* basePane) {
            mpBasePane = (nw4r::lyt::Pane*)basePane;
        }

        void ChannelObj::initExtModule(EGG::Heap* workHeap, channel::RsoThread* thread) {
            mpExtModuleWorkHeap = workHeap;
            mpModuleThread = thread;
        }

        void ChannelObj::create(nand::LayoutFile* sysLayoutFile) {
            if (!isLayoutCreated()) {
                mpSysLayoutFile = sysLayoutFile;

                if (mpCursorLayout == NULL) {
                    initCursor();
                }

                if (mpBalloonLayout == NULL && System::getChannelManager()->isLoaded(mChanPage, mChanIndex)) {
                    initBalloon();
                }

                if (mState == STATE_CREATE_THUMBNAIL || mState == STATE_WAIT_LOAD_THUMBNAIL && mpThumbFile->isFinished()) {
                    createThumbnail();
                    mState = STATE_NORMAL;
                }
            }
        }

        void ChannelObj::calc() {
            switch (mState) {
                case STATE_LOAD_THUMBNAIL: {
                    mState = loadThumbnailAsync();
                    break;
                }
                case STATE_WAIT_LOAD_THUMBNAIL: {
                    if (!mpThumbFile->isFinished()) {
                        break;
                    }
                    mState = STATE_CREATE_THUMBNAIL;
                }
                case STATE_CREATE_THUMBNAIL: {
                    createThumbnail();
                    mState = STATE_NORMAL;
                    break;
                }
                case STATE_NORMAL: {
                    calcNormal();
                    break;
                }
            }
        }

        int ChannelObj::calcExtModule(EGG::ExpHeap* expHeap, bool canStartModule, bool onSceneChange) {
            int result = EXT_MODULE_RESULT_WAIT;
            const char* dataBase = scCursur_a;

            if (mExtModuleState == EXT_MODULE_STATE_UNAVAILABLE) {
                return EXT_MODULE_RESULT_UNAVAILABLE;
            }

            switch (mExtModuleState) {
                case EXT_MODULE_STATE_BEGIN: {
                    if (System::getFader()->getStatus() == EGG::Fader::PREPARE_OUT) {
                        mModuleCount++;
                        if (canStartModule && mModuleCount > mMaxModuleCount) {
                            mpPrevModuleHeap = mpModuleHeap;
                            mpModuleHeap = expHeap;

                            // Load icon module (RSO or CS)
                            mpModuleFile = System::getChannelManager()->loadThumbnailRsoAsync(mpExtModuleWorkHeap, mChanPage, mChanIndex);
                            if (mpModuleFile == NULL) {
                                mpModuleFile = System::getChannelManager()->loadThumbnailCSAsync(mpExtModuleWorkHeap, mChanPage, mChanIndex);
                                mExtModuleState = EXT_MODULE_STATE_PREPARE_CS;
                            } else {
                                mExtModuleState = EXT_MODULE_STATE_PREPARE_RSO;
                            }

                            result = EXT_MODULE_RESULT_CALC;
                        } else {
                            result = EXT_MODULE_RESULT_WAIT;
                        }
                    }
                    break;
                }
                case EXT_MODULE_STATE_PREPARE_RSO: {
                    if (mpModuleFile->isFinished()) {
                        // Check if we properly read the module file
                        if (mpModuleFile->checkData() != nand::RESULT_SUCCESS && mpModuleFile->checkData() != nand::RESULT_NONE) {
                            clearModuleParam();
                            result = EXT_MODULE_RESULT_DESTROY;
                            break;
                        }

                        // Setup RSO module
                        mpRSOHeader = (RSOObjectHeader*)mpModuleFile->getBuffer();
                        mpRSOBss = NULL;

                        if (mpRSOHeader->bssSize != 0) {
                            mpRSOBss = new (mpExtModuleWorkHeap, DEFAULT_ALIGN) u8[mpRSOHeader->bssSize];
                            memset(mpRSOBss, 0, mpRSOHeader->bssSize);
                        }

                        RSOLinkList(mpRSOHeader, mpRSOBss);

                        if (RSOIsImportSymbolResolvedAll(mpRSOHeader)) {
                            OSReport(dataBase + 0x398);
                        } else {
                            OSReport(dataBase + 0x3C0, RSOGetNumImportSymbolsUnresolved(mpRSOHeader));
                        }

                        // Import `int Calc(int)`
                        // This is during ChannelObj's loop.
                        mpRSOCalc = (channel::CalcFunc)RSOFindExportSymbolAddr(mpRSOHeader, scExport_Calc);

                        // Import `void ThreadCalc()`
                        // This is executed on a seperate thread.
                        mpModuleThread->setCalcFunc((channel::ThreadCalcFunc)RSOFindExportSymbolAddr(mpRSOHeader, dataBase + 0x3ED));

                        ((void (*)())mpRSOHeader->prolog)();

                        // Import `void Create(nw4r::lyt::Layout*)`
                        // This is the initialization of the module.
                        channel::CreateFunc createFunc = (channel::CreateFunc)RSOFindExportSymbolAddr(mpRSOHeader, scExport_Create);
                        if (createFunc != NULL) {
                            createFunc(mpThumbLayout->getNW4RLyt());
                        }

                        mpModuleThread->start();

                        mbRSODoneCalc = false;
                        mbRSOThreadExit = false;

                        mExtModuleState = EXT_MODULE_STATE_RSO_CALC;
                    }

                    result = EXT_MODULE_RESULT_CALC;
                    break;
                }
                case EXT_MODULE_STATE_RSO_CALC: {
                    // Don't do anything until the thread is destroyed.
                    if (!mbRSOThreadExit && mpModuleThread->IsThreadTerminated()) {
                        mpModuleThread->WaitForThreadExit();
                        mbRSOThreadExit = true;
                    }

                    // If the calc function requested to exit (by returning a non-zero value)
                    if (!mbRSODoneCalc && mpRSOCalc(onSceneChange == true)) {
                        mbRSODoneCalc = true;
                    }

                    if (mbRSOThreadExit && mbRSODoneCalc) {
                        mbModuleTerminated = true;

                        ((void (*)())mpRSOHeader->epilog)();

                        RSOUnLinkList(mpRSOHeader);

                        mpRSOCalc = NULL;

                        mpModuleThread->setCalcFunc(NULL);

                        clearModuleParam();

                        result = EXT_MODULE_RESULT_DESTROY;
                    } else {
                        result = EXT_MODULE_RESULT_CALC;
                    }

                    break;
                }
                case EXT_MODULE_STATE_PREPARE_CS: {
                    if (mpModuleFile->isFinished()) {
                        // Check if we properly read the module file
                        if (mpModuleFile->checkData() != nand::RESULT_SUCCESS && mpModuleFile->checkData() != nand::RESULT_NONE) {
                            clearModuleParam();
                            result = EXT_MODULE_RESULT_DESTROY;
                            break;
                        }

                        if (mpCSHeap == NULL) {
                            mpCSHeap = EGG::ExpHeap::create(-1, mpExtModuleWorkHeap, 0);
                        }

                        // Start up CHANSVm system
                        System::getCSManager()->create(mpCSHeap);

                        // Module settings (for iplCS)
                        channel::ChannelScriptManager::CSData data;
                        data.heap = mpModuleHeap;
                        data.layout = mpThumbLayout;
                        data.anims = mpModuleAnims;
                        data.titleId = System::getChannelManager()->getTitleID(mChanPage, mChanIndex);
                        data.threadTerminated = mbModuleTerminated;
                        data.isThumbnail = true;
                        data.mbHasNewMessage = true;

                        if (!(System::getNwc24Manager() != NULL && System::getNwc24Manager()->isNewMessageThere(ES_TITLE_CODE(data.titleId)))) {
                            data.mbHasNewMessage = false;
                        }

                        System::getCSManager()->setData(data);

                        // Start up module
                        if (!System::getCSManager()->init(mpModuleFile, mpModuleThread)) {
                            mExtModuleState = EXT_MODULE_STATE_DESTROY_CS;
                        } else {
                            mExtModuleState = EXT_MODULE_STATE_CS_CALC;
                        }

                        delete mpModuleFile;
                        mpModuleFile = NULL;
                    }

                    result = EXT_MODULE_RESULT_CALC;
                    break;
                }
                case EXT_MODULE_STATE_CS_CALC: {
                    System::getCSManager()->calc();

                    if (mpModuleThread->IsThreadTerminated()) {
                        System::getCSManager()->finish();
                        mbModuleTerminated = true;
                        mExtModuleState = EXT_MODULE_STATE_DESTROY_CS;
                    }

                    result = EXT_MODULE_RESULT_CALC;
                    break;
                }
                case EXT_MODULE_STATE_DESTROY_CS: {
                    System::getCSManager()->destroy();
                    clearModuleParam();
                    result = EXT_MODULE_RESULT_DESTROY;
                    break;
                }
                default: {
                    break;
                }
            }

            return result;
        }

        void ChannelObj::drawThumbnail() {
            if (isLayoutCreated()) {
                mpThumbLayout->draw();
            }
        }

        void ChannelObj::drawCursor() {
            mpCursorLayout->draw();
        }

        void ChannelObj::drawBalloon() {
            if (mpBalloonLayout != NULL) {
                mpBalloonLayout->draw();
            }
        }

        void ChannelObj::createDiskLayout(void* data) {
            const ModuleData* moduleData = reinterpret_cast<const ModuleData*>(scCursur_a + 0x98);
            mpDiskLayout = layout::Object::create(mpDiskHeap, 0x19000, data, scArc, moduleData->iconBrlyt);
            setLangPane(mpDiskLayout);

            if (mpDiskLayout->searchFile(moduleData->iconBrlan)) {
                mpDiskAnim = mpDiskLayout->bind(moduleData->iconBrlan);
            } else if (mpDiskLayout->searchFile(moduleData->iconWholeBrlan)) {
                mpDiskAnim = mpDiskLayout->bind(moduleData->iconWholeBrlan);
            } else {
                mpDiskAnim = NULL;
            }

            changeDisk();

            bindNewAnm(mpDiskLayout);

            mNewMessageState = 1;

            mpDiskLayout->finishBinding();
        }

        void ChannelObj::destroyDiskLayout() {
            if (mpDiskLayout != NULL) {
                mpDiskLayout->destroyHeap();
                mpDiskLayout = NULL;

                mpDiskAnim = NULL;

                mpNwc24NewPlayAnim = false;
                mNewMessageState = 0;
            }
        }

        void ChannelObj::changeDisk() {
            if (isDiskChannel() && (mBalloonState == 1 || mBalloonState == 2 || mBalloonState == 3)) {
                setBalloonAnim(4);
                setBalloonAnim(1);
            }
        }

        void ChannelObj::resetDiskTitleName() {
            if (isDiskChannel()) {
                if (mpDiskLayout != NULL) {
                    setBalloonText((wchar_t*)System::getChannelManager()->getTitleName(mChanPage, mChanIndex, 0));
                } else {
                    setBalloonText(System::getMessage(0));
                }
            }
        }

        nw4r::math::VEC3& ChannelObj::getTranslate() const {
            return (nw4r::math::VEC3&)mpThumbLayout->GetRootPane()->GetTranslate();
        }

        BOOL ChannelObj::isDiskChannel() const {
            if (isValid() && System::getChannelManager()->getSceneID(mChanPage, mChanIndex) == SCENE_DISK_CHANNEL) {
                return TRUE;
            } else {
                return FALSE;
            }
        }

        BOOL ChannelObj::isValid() const {
            return System::getChannelManager()->hasLoadedBnr(mChanPage, mChanIndex);
        }

        void ChannelObj::onPoint(int eventFlags) {
            if (eventFlags & 0x10000U) {
                mPointCount = 0;
            } else if (eventFlags & 0x20000U) {
                mPointCount = 1;
            } else if ((mPointCount += 1) > 1) {
                return;
            }

            if (!(eventFlags & 1)) {
                setCursorAnim(1);
            }
            if (!(eventFlags & 2)) {
                setBalloonAnim(1);
            }
        }

        void ChannelObj::onLeft(int eventFlags) {
            if (eventFlags & 0x10000U) {
                mPointCount = 0;
            } else if (eventFlags & 0x20000U) {
                mPointCount = 1;
            } else if ((mPointCount -= 1) > 0) {
                return;
            }

            if (!(eventFlags & 1)) {
                setCursorAnim(3);
            }
            if (!(eventFlags & 2)) {
                setBalloonAnim(4);
            }
        }

        void ChannelObj::onPinch(bool pinched) {
            if (pinched) {
                setCursorAnim(1);
                mPointCount = 1;
            } else {
                setCursorAnim(0);
                mPointCount = 0;
            }

            setBalloonAnim(0);
        }

        void ChannelObj::setCursorDecideAnim() {
            setCursorAnim(4);
        }

        void ChannelObj::initCursorAnim(bool resetPointCount) {
            setCursorAnim(0);
            if (resetPointCount) {
                mPointCount = 0;
            }
        }

        void ChannelObj::initBalloonAnim(bool resetPointCount) {
            setBalloonAnim(0);
            if (resetPointCount) {
                mPointCount = 0;
            }
        }

        void ChannelObj::FillModuleCount() {
            mModuleCount = MAX_MODULE_COUNT;
        }

        void ChannelObj::setLangPane(const layout::Object* layout) {
            int lang = System::getLanguage();
            const char* langGroup = scLangGroups[lang];
            char langCodeBuf[10][4] = {""};

            bool foundLangGroup = false;

            for (nw4r::lyt::GroupList::Iterator it = layout->GetGroupList().GetBeginIter(); it != layout->GetGroupList().GetEndIter(); it++) {
                if (strcmp(it->GetName(), langGroup) == 0) {
                    foundLangGroup = true;
                } else {
                    bool isNonRsoGroup = true;
                    for (int i = 0; i < channel::MAX_ANIMS; i++) {
                        char name[8];
                        sprintf(name, "Rso%d", i);
                        if (strncmp(it->GetName(), name, 5) == 0) {
                            isNonRsoGroup = false;
                            break;
                        }
                    }

                    if (isNonRsoGroup) {
                        for (nw4r::lyt::PaneLinkList::Iterator it2 = it->GetPaneList().GetBeginIter(); it2 != it->GetPaneList().GetEndIter(); it2++) {
                            it2->mTarget->SetVisible(false);
                        }

                        for (int i = 0; i < 10; i++) {
                            if (strncmp(it->GetName(), scLangGroups[i], 3) == 0) {
                                memcpy(langCodeBuf[i], it->GetName(), 3);
                                langCodeBuf[i][3] = 0;
                                break;
                            }
                        }
                    }
                }
            }

            if (foundLangGroup) {
                nw4r::lyt::Group* group = layout->FindGroupByName(langGroup);
                nw4r::lyt::Group* const& groupView = group;
                for (nw4r::lyt::PaneLinkList::Iterator it = groupView->GetPaneList().GetBeginIter(); it != groupView->GetPaneList().GetEndIter(); it++) {
                    it->mTarget->SetVisible(true);
                }
            } else {
                s32 region = System::getRegion();
                for (int i = 0; i < channel::MAX_ANIMS; i++) {
                    if (scModuleData.langGroupLookup[region][i] == NULL) {
                        break;
                    }
                    if (strcmp(scModuleData.langGroupLookup[region][i], langCodeBuf[scLangLookup[region][i]]) == 0) {
                        nw4r::lyt::Group* group = layout->FindGroupByName(scModuleData.langGroupLookup[region][i]);
                        nw4r::lyt::Group* const& groupView = group;
                        for (nw4r::lyt::PaneLinkList::Iterator it = groupView->GetPaneList().GetBeginIter(); it != groupView->GetPaneList().GetEndIter(); it++) {
                            it->mTarget->SetVisible(true);
                        }
                        break;
                    }
                }
            }
        }

        void ChannelObj::bindRsoAnm(layout::Object* layout, layout::Animator** anims, const char* layoutFile) {
            for (int i = 0; i < channel::MAX_ANIMS; i++) {
                char fileName[20];
                sprintf(fileName, scBrlan_RsoFmt, layoutFile, i);

                if (layout->searchFile(fileName)) {
                    char groupName[8];
                    sprintf(groupName, "Rso%d", i);

                    bool found = false;
                    for (nw4r::lyt::GroupList::Iterator it = layout->GetGroupList().GetBeginIter(); it != layout->GetGroupList().GetEndIter(); it++) {
                        if (strcmp(it->GetName(), groupName) == 0) {
                            anims[i] = layout->bindToGroup(fileName, groupName, false, false);
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        anims[i] = layout->bind(fileName, false);
                    }
                }
            }
        }

        BOOL ChannelObj::loadThumbnailAsync() {
            if (!System::getChannelManager()->isLoaded(mChanPage, mChanIndex)) {
                return FALSE;
            }

            mpThumbFile = System::getChannelManager()->loadThumbnailAsync(mpMainHeap, mChanPage, mChanIndex);
            return (mpThumbFile == NULL) + 1;
        }

        void ChannelObj::createThumbnail() {
            bool shouldAdjustHeap = false;

            if (mpBalloonLayout == NULL && System::getChannelManager()->isLoaded(mChanPage, mChanIndex)) {
                initBalloon();
            }

            f32 frame;

            if (isValid()) {
                if (System::getChannelManager()->getSceneID(mChanPage, mChanIndex) == SCENE_DISK_CHANNEL) {
                    frame = 0.0f;
                } else {
                    if (mpThumbFile->checkData() == nand::RESULT_SUCCESS) {
                        frame = createWadThumbnail();
                    } else {
                        frame = createWrongThumbnail();
                        shouldAdjustHeap = true;
                    }
                }
            } else {
                frame = createEmptyThumbnail();
                shouldAdjustHeap = true;
            }

            calcNormal();

            if (mpThumbAnim != NULL) {
                mpThumbAnim->play();
            }
            mpThumbLayout->finishBinding();
            if (mpThumbAnim != NULL) {
                mpThumbAnim->setCurrentFrame(frame);
            }

            if (shouldAdjustHeap) {
                mpThumbLayout->adjustHeap();
            }
        }

        f32 ChannelObj::createWadThumbnail() {
            f32 frame = 0.0f;

            mpThumbLayout = layout::Object::create(mpMainHeap, 0x8000, mpThumbFile->getBuffer(), scArc, scCursur_a + 0x3F8);
            setLangPane(mpThumbLayout);

            const char* dataBase = scCursur_a;
            u32 rsoIdx = System::getChannelManager()->getIconRSOIdx(mChanPage, mChanIndex);
            u32 csIdx = System::getChannelManager()->getIconCSIdx(mChanPage, mChanIndex);

            if (rsoIdx != 0) {
                if (mpThumbLayout->searchFile(dataBase + 0x42E)) {
                    mpThumbAnim = mpThumbLayout->bind(dataBase + 0x42E);
                } else {
                    mpThumbAnim = NULL;
                }
            } else {
                if (csIdx != 0) {
                    if (mpThumbLayout->searchFile(dataBase + 0x42E)) {
                        mpThumbAnim = mpThumbLayout->bind(dataBase + 0x42E);
                    } else {
                        mpThumbAnim = NULL;
                    }
                } else {
                    if (mpThumbLayout->searchFile(dataBase + 0x403)) {
                        mpThumbAnim = mpThumbLayout->bind(dataBase + 0x403);
                    } else {
                        if (mpThumbLayout->searchFile(dataBase + 0x40E)) {
                            mpThumbAnim = mpThumbLayout->bind(dataBase + 0x40E);
                        } else {
                            mpThumbAnim = NULL;
                        }
                    }
                }
            }

            if (mpThumbAnim != NULL) {
                if (rsoIdx != 0 || csIdx != 0) {
                    frame = mpThumbAnim->getMinFrame();
                } else {
                    frame =
                        mpThumbAnim->getMinFrame() + (System::getRndm()->get_u16() % (u16)(mpThumbAnim->getMaxFrame() - mpThumbAnim->getMinFrame()));
                }
            }

            if (rsoIdx != 0 || csIdx != 0) {
                mExtModuleState = EXT_MODULE_STATE_BEGIN;
                bindRsoAnm(mpThumbLayout, mpModuleAnims, "icon");
            }

            bindNewAnm(mpThumbLayout);

            mNewMessageState = 1;

            return frame;
        }

        extern "C" char scBrlyt_my_IplTop_b[] = "my_IplTop_b.brlyt";
        extern "C" char scBrlan_my_IplTop_b[] = "my_IplTop_b.brlan";

        f32 ChannelObj::createWrongThumbnail() {
            mpThumbLayout = layout::Object::create(mpMainHeap, 0x8000, mpSysLayoutFile, scArc, scBrlyt_my_IplTop_b);

            mpThumbLayout->FindPaneByName("Ch0")->SetVisible(false);
            mpThumbLayout->FindPaneByName("Ch1")->GetMaterial()->SetTevColor(0, (GXColorS10){0, 0, 0, 255});

            mpThumbAnim = NULL;

            return 0.0f;
        }

        f32 ChannelObj::createEmptyThumbnail() {
            mpThumbLayout = layout::Object::create(mpMainHeap, 0x8000, mpSysLayoutFile, scArc, scBrlyt_my_IplTop_b);
            mpThumbAnim = mpThumbLayout->bind(scBrlan_my_IplTop_b);

            return System::getRndm()->get_u16() % 2000;
        }

        void ChannelObj::calcNormal() {
            if (isDiskChannel()) {
                if (mpDiskLayout != NULL) {
                    mpThumbLayout = mpDiskLayout;
                    mpThumbAnim = mpDiskAnim;
                } else {
                    mpThumbLayout = mpNoDiskLayout;
                    mpThumbAnim = mpNoDiskAnim;
                }
            }

            updateNew();

            nw4r::math::VEC3 pos(0, 0, 0);

            MTXMultVec(mpBasePane->GetGlobalMtx(), pos, pos);
            mpThumbLayout->GetRootPane()->SetTranslate(pos);

            mpThumbLayout->calc();

            calcCursor(pos);
            calcBalloon(pos);
        }

        extern "C" char scBrlyt_my_IplTop_d[] = "my_IplTop_d.brlyt";
        extern "C" char scBrlyt_my_IplTopBalloon_a[] = "my_IplTopBalloon_a.brlyt";
        extern "C" char scBrlan_BalloonInOut[] = "my_IplTopBalloon_a_BalloonInOut.brlan";

        void ChannelObj::initCursor() {
            mpCursorLayout = new (mpCursorHeap, 4) layout::Object(mpCursorHeap, mpSysLayoutFile, scArc, scBrlyt_my_IplTop_d);

            for (int i = 0; i < ANIM_CURSOR_MAX; i++) {
                mpCursorAnims[i] = mpCursorLayout->bind(scCursorAnims[i], scCursur, false);
            }

            setCursorAnim(0);
            mpCursorLayout->finishBinding();
        }

        void ChannelObj::calcCursor(const nw4r::math::VEC3& vec) {
            mpCursorLayout->GetRootPane()->SetTranslate(vec);
            calcCursorAnim();
            mpCursorLayout->calc();
        }

        void ChannelObj::setCursorAnim(int state) {
            if (state == 0) {
                mCursorState = 0;
                mPendingCursorState = 0;

                for (int i = 0; i < ANIM_CURSOR_MAX; i++) {
                    mpCursorAnims[i]->initFrame();
                }

                mpCursorLayout->getAnim(1)->initAnmFrame();
                mpCursorLayout->GetRootPane()->SetVisible(false);
            } else if (state == 4) {
                mCursorState = 4;
                mPendingCursorState = 0;
                mpCursorLayout->GetRootPane()->SetVisible(true);
                startCursorAnim(2);
            } else {
                switch (mCursorState) {
                    case 0: {
                        if (state == 1) {
                            mCursorState = 1;
                            mpCursorLayout->GetRootPane()->SetVisible(true);
                            startCursorAnim(1);
                        }
                        break;
                    }
                    case 1: {
                        if (state == 2) {
                            mCursorState = 2;
                        } else if (state == 3) {
                            mPendingCursorState = 3;
                        } else if (state == 1) {
                            mPendingCursorState = 0;
                        }
                        break;
                    }
                    case 2: {
                        if (state == 3) {
                            mCursorState = 3;
                            startCursorAnim(0);
                        }
                        break;
                    }
                    case 3: {
                        if (state == 1) {
                            mPendingCursorState = 1;
                        } else if (state == 3) {
                            mPendingCursorState = 0;
                        }
                        break;
                    }
                }
            }
        }

        void ChannelObj::calcCursorAnim() {
            switch (mCursorState) {
                case 1: {
                    if (!mpCursorAnims[ANIM_CURSOR_FOCUS_ON]->isPlaying()) {
                        int prev = mPendingCursorState;
                        switch (mCursorState) {
                            case 0:
                                break;
                            case 1:
                                mCursorState = 2;
                                break;
                            case 2:
                                break;
                            case 3:
                                break;
                            default:
                                break;
                        }
                        if (prev == 3) {
                            setCursorAnim(3);
                            mPendingCursorState = 0;
                        }
                    }
                    break;
                }
                case 3: {
                    if (!mpCursorAnims[ANIM_CURSOR_FOCUS_OFF]->isPlaying()) {
                        int prev = mPendingCursorState;
                        setCursorAnim(0);
                        if (prev == 1) {
                            setCursorAnim(1);
                        }
                    }
                    break;
                }
                case 4: {
                    if (!mpCursorAnims[ANIM_CURSOR_SELECT]->isPlaying()) {
                        setCursorAnim(0);
                    }
                    break;
                }
            }
        }

        void ChannelObj::startCursorAnim(int animationIndex) {
            mpCursorAnims[animationIndex]->setAnmType(ANIM_TYPE_FORWARD);
            mpCursorAnims[animationIndex]->play();
        }

        void ChannelObj::initBalloon() {
            if (!isValid()) {
                mpBalloonLayout = NULL;
                return;
            }
            mpBalloonLayout = new (mpBalloonHeap, 4) layout::Object(mpBalloonHeap, mpSysLayoutFile, scArc, scBrlyt_my_IplTopBalloon_a);

            setBalloonText((wchar_t*)System::getChannelManager()->getTitleName(mChanPage, mChanIndex, 0));

            mpBalloonAnim = mpBalloonLayout->bind(scBrlan_BalloonInOut);
            setBalloonAnim(0);
            mpBalloonLayout->finishBinding();
        }

        extern "C" char scSE_BALLOON[] = "WIPL_SE_BALLOON";

        void ChannelObj::setBalloonText(const wchar_t* text) {
            nw4r::lyt::TextBox* textPane = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpBalloonLayout->FindPaneByName(scPaneName_T_Balloon));

            wchar_t fullStr[channel::META_CHANNEL_NAME_LENGTH + 3] = L"";
            u32 strLen;

            wcsncpy(fullStr, text, channel::META_CHANNEL_NAME_LENGTH);
            strLen = wcslen(fullStr);

            f32 temp1 = 0.0f;
            int extraLen = 0;

            if (strLen == 0) {
                textPane->SetString(fullStr, 0, 1);
            } else {
                for (u32 i = strLen; i != 0; i--) {
                    textPane->SetString(fullStr, 0, i + extraLen);
                    textPane->CalculateMtx(*mpBalloonLayout->getDrawInfo());

                    nw4r::ut::Rect textRect = textPane->GetTextDrawRect(*mpBalloonLayout->getDrawInfo());
                    if (textRect.GetWidth() <= temp1 + 391.5f) {
                        break;
                    }

                    if (System::getRegion() == SC_PRODUCT_AREA_JPN) {
                        fullStr[i - 1] = NULL;
                        fullStr[i - 2] = L'…';
                    } else {
                        temp1 = -1.179962f;
                        extraLen = 2;
                        fullStr[i + 1] = NULL;
                        fullStr[i] = '.';
                        fullStr[i - 1] = '.';
                        fullStr[i - 2] = '.';
                    }
                }
            }

            nw4r::ut::Rect textRect = textPane->GetTextDrawRect(*mpBalloonLayout->getDrawInfo());

            nw4r::lyt::Size newSize(mpBalloonLayout->FindPaneByName(scPaneName_W_Base)->GetSize());
            newSize.width = textRect.right - textRect.left + 40.0f;

            if (newSize.width < mLocationAdjust * 160.0f) {
                newSize.width = mLocationAdjust * 160.0f;
            }

            mpBalloonLayout->FindPaneByName(scPaneName_W_Shade)->SetSize(newSize);
            mpBalloonLayout->FindPaneByName(scPaneName_W_Base)->SetSize(newSize);
        }

        void ChannelObj::calcBalloon(const nw4r::math::VEC3& vec) {
            if (mpBalloonLayout != NULL) {
                nw4r::lyt::Size size;

                size = mpBalloonLayout->FindPaneByName(scPaneName_W_Base)->GetSize();

                f32 val = -2.0f + ((size.height / 2) + mThumbHeight);
                val *= -1.0f;

                nw4r::ut::Rect projRect;
                System::getProjectionRect(&projRect);

                f32 anchorX = vec.x;
                f32 halfWidth = size.width / 2;
                f32 horizontalOffset = 0.0f;
                f32 leftMargin = (anchorX - halfWidth) - projRect.left;
                f32 rightMargin = projRect.right - (anchorX + halfWidth);
                if (leftMargin < 60.0f) {
                    horizontalOffset = 60.0f - leftMargin;
                } else if (rightMargin < 60.0f) {
                    horizontalOffset = rightMargin - 60.0f;
                }

                const nw4r::math::VEC3 pos(vec.x + horizontalOffset, vec.y + val, 0.0f);
                mpBalloonLayout->GetRootPane()->SetTranslate(pos);

                calcBalloonAnim();
                mpBalloonLayout->calc();
            }
        }

        void ChannelObj::setBalloonAnim(int state) {
            if (mpBalloonLayout != NULL) {
                if (state == 0) {
                    mBalloonState = 0;
                    mPendingBalloonState = 0;

                    mpBalloonLayout->setMinFrame(0.0f);
                    mpBalloonLayout->GetRootPane()->SetVisible(false);
                } else {
                    switch (mBalloonState) {
                        case 0: {
                            if (state == 1) {
                                mBalloonWaitFrame = 0;
                                mBalloonState = 1;
                            }
                            break;
                        }
                        case 1: {
                            if (state == 2) {
                                mBalloonState = 2;
                                mpBalloonLayout->GetRootPane()->SetVisible(true);
                                mpBalloonLayout->setAnmType(ANIM_TYPE_FORWARD);
                                mpBalloonLayout->start();
                                snd::getSystem()->startSE(scSE_BALLOON);
                            } else if (state == 4) {
                                mBalloonState = 0;
                            }
                            break;
                        }
                        case 2: {
                            if (state == 3) {
                                mBalloonState = 3;
                            } else if (state == 4) {
                                mPendingBalloonState = 4;
                            } else if (state == 1) {
                                mPendingBalloonState = 0;
                            }
                            break;
                        }
                        case 3: {
                            if (state == 4) {
                                mBalloonState = 4;
                                mpBalloonLayout->setAnmType(ANIM_TYPE_BACKWARD);
                                mpBalloonLayout->start();
                            }
                            break;
                        }
                        case 4: {
                            if (state == 1) {
                                mPendingBalloonState = 1;
                            } else if (state == 4) {
                                mPendingBalloonState = 0;
                            }
                            break;
                        }
                    }
                }
            }
        }

        void ChannelObj::calcBalloonAnim() {
            switch (mBalloonState) {
                case 1: {
                    if ((reinterpret_cast<u32&>(mBalloonWaitFrame) += 1) >= 20.0f) {
                        setBalloonAnim(2);
                        break;
                    }
                }
                case 3: {
                    break;
                }
                case 2: {
                    if (!mpBalloonLayout->isPlaying(0)) {
                        int prev = mPendingBalloonState;
                        setBalloonAnim(3);
                        if (prev == 4) {
                            setBalloonAnim(4);
                            mPendingBalloonState = 0;
                        }
                    }
                    break;
                }
                case 4: {
                    if (!mpBalloonLayout->isPlaying(0)) {
                        int prev = mPendingBalloonState;
                        setBalloonAnim(0);
                        if (prev == 1) {
                            setBalloonAnim(1);
                        }
                    }
                    break;
                }
            }
        }

        void ChannelObj::clearModuleParam() {
            if (mpRSOBss != NULL) {
                delete[] mpRSOBss;
                mpRSOBss = NULL;
            }

            mpRSOHeader = NULL;
            if (mpCSHeap != NULL) {
                mpCSHeap->destroy();
                mpCSHeap = NULL;
            }

            mModuleCount = 0;
            if (mpModuleFile != NULL) {
                delete mpModuleFile;
                mpModuleFile = NULL;
            }

            mExtModuleState = EXT_MODULE_STATE_BEGIN;
        }

        void ChannelObj::bindNewAnm(layout::Object* layout) {
            char grpName[20];
            char** lookup;
            nw4r::lyt::Group* group;

            // Look for "New" group first.
            // If that doesn't exist, look for "New_%d" group based on the System language.
            // If That doesn't exist, look for "New_%d" group based on the System region.
            // If THAT doesn't exist, uhhh oh well.
            group = layout->FindGroupByName("New");
            if (group != NULL) {
                mpNwc24NewGroup = group;
            } else {
                sprintf(grpName, "New_%s", scLangGroups[System::getLanguage()]);

                group = layout->FindGroupByName(grpName);
                if (group != NULL) {
                    mpNwc24NewGroup = group;
                } else {
                    lookup = (char**)scModuleData.langGroupLookup[System::getRegion()];

                    for (int i = 0; lookup[i] != NULL; i++) {
                        sprintf(grpName, "New_%s", lookup[i]);

                        group = layout->FindGroupByName(grpName);
                        if (group != NULL) {
                            mpNwc24NewGroup = group;
                            break;
                        }
                    }
                }
            }

            if (group != NULL) {
                for (nw4r::lyt::PaneLinkList::Iterator it = group->GetPaneList().GetBeginIter(); it != group->GetPaneList().GetEndIter(); it++) {
                    it->mTarget->UnbindAllAnimation();
                }

                if (layout->searchFile("icon_New.brlan")) {
                    mpNwc24NewAnim = layout->bindToGroup("icon_New.brlan", group);
                }
            }
        }

        void ChannelObj::updateNew() {
            if (System::getNwc24Manager() != NULL) {
                switch (mNewMessageState) {
                    case 1: {
                        if (setupNew()) {
                            mNewMessageState = 2;
                            mNewMessageFrame = 0;
                        }
                        break;
                    }
                    case 2: {
                        if (++mNewMessageFrame >= 4200) {
                            mNewMessageState = 1;
                        }
                        break;
                    }
                }
            }
        }

        BOOL ChannelObj::setupNew() {
            if (System::getNwc24Manager() == NULL || !System::getNwc24Manager()->getNewTitleTbl(NULL)) {
                return FALSE;
            }

            if (isDiskChannel()) {
                u32* pDiskID;
                char* diskMaker;
                System::getBS2Manager()->getDiskInfo((char**)&pDiskID, &diskMaker);

                u32 diskID = *pDiskID;
                if (!System::getNwc24Manager()->isNewMessageThere(diskID)) {
                    return TRUE;
                }
            } else {
                if (!System::getNwc24Manager()->isNewMessageThere(ES_TITLE_CODE(System::getChannelManager()->getTitleID(mChanPage, mChanIndex)))) {
                    return TRUE;
                }
            }

            if (!mpNwc24NewPlayAnim) {
                if (mpNwc24NewGroup != NULL) {
                    for (nw4r::lyt::PaneLinkList::Iterator it = mpNwc24NewGroup->GetPaneList().GetBeginIter();
                         it != mpNwc24NewGroup->GetPaneList().GetEndIter(); it++) {
                        it->mTarget->SetVisible(true);
                    }

                    if (mpNwc24NewAnim != NULL) {
                        mpNwc24NewAnim->play();
                    }
                }

                mpNwc24NewPlayAnim = true;
            }

            return TRUE;
        }
    }  // namespace scene
}  // namespace ipl
