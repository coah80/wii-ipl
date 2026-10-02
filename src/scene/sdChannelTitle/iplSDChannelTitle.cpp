#define IPL_SD_CHANNEL_TITLE_CPP
#define IPL_SD_CHANNEL_SELECT_ACCESS
#define IPL_SDMEMORY_DIALOG_STATE_ACCESSOR
#define IPL_SDMEMORY_COMPLETION_PCT_ACCESSOR

#include "scene/sdChannelTitle/iplSDChannelTitle.h"
#include "scene/sdChannelSelect/iplSDChannelSelect.h"
#include "system/iplSystem.h"
#include "sound/iplSound.h"
#include "scene/setting/iplNCDSetting.h"
#include "utility/iplESMisc.h"
#include <private/os.h>
#include <private/wpad.h>
#include "scene/parentalDialog/iplParentalDialog.h"
#include "system/iplNandWall.h"
#include <stdio.h>
#include <string.h>
#include <wchar.h>

namespace ipl {
namespace scene {

class SDTitlePaneEventHandler;
class SDTitleButtonEventHandler;

extern "C" void iplSDChannelTitle_rebootSystem(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_drawDimOverlay(SDChannelTitle* scene, const nw4r::ut::Rect& bounds, GXColor color);
extern "C" void iplSDChannelTitle_bindBannerAnimations(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_createBannerLayout(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_createIconLayout(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_playBannerIntro(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_startBannerSound(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_bindBannerAnims(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_bindRsoAnimations(SDChannelTitle* scene, layout::Object* layout,
                                          layout::Animator** animations, const char* prefix);
extern "C" void iplSDChannelTitle_updateScript(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_updateScriptIdle(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_updateScriptLoad(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_destroyScript(SDChannelTitle* scene);

extern "C" void iplSDChannelTitle_rebuildBannerLayout(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_updateChangeWait(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_updateMemoryCalc(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_updateAfterClearTmp(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_updateEnqueueNotice(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_showCopyError(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_updateCopyErrorDialog(SDChannelTitle* scene);
extern "C" bool iplSDChannelTitle_startZoomFade(SDChannelTitle* scene);
extern "C" BOOL iplSDChannelTitle_isNetworkAllowed(SDChannelTitle*, ESTmdView*, ESTitleId titleId);
extern "C" BOOL iplSDChannelTitle_isParentalEnabled();
extern "C" void iplSDChannelTitle_beginLaunch(SDChannelTitle* scene, SDChannelObj* channel);
extern "C" void iplSDChannelTitle_prepareSceneExit(SDChannelTitle* scene, int nextScene);
extern "C" void iplSDChannelTitle_rebootSystem(SDChannelTitle*);
extern "C" bool iplSDChannelTitle_isLaunchDelayDone(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_setStartButtonPressed(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_drawDimOverlay(SDChannelTitle*, const nw4r::ut::Rect& bounds, GXColor color);
extern "C" void iplSDChannelTitle_setPaneMessage(SDChannelTitle*, nw4r::lyt::Pane* pane, u32 message, bool allocate);
extern "C" nand::LayoutFile* iplSDChannelTitle_loadBannerMetaFiles(SDChannelTitle*, ESTitleId title, nand::File** sound);
extern "C" void iplSDChannelTitle_fetchTmdViewTask(void* argument);
extern "C" BOOL iplSDChannelTitle_passesParentalCheck(SDChannelTitle* scene, ESTmdView* tmd);
extern "C" void iplSDChannelTitle_updateIdleState(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_updateChangeState(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_updateParentalResult(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_updateDialogResult(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_startCopyProgress(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_updateCopyPrepare(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_updateCopyStart(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_updateCopyProgress(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_finishProgressHide(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_returnToIdle(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_loadTitleBanner(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_updateBannerLoad(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_tryLaunchSelected(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_updateTmdReady(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_preparePageRestart(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_loadBannerScript(SDChannelTitle* scene, ESTitleId title);
extern "C" void iplSDChannelTitle_openParentalDialog(SDChannelTitle* scene, void* arguments);
extern "C" void iplSDChannelTitle_setPageAndIndex(SDChannelTitle* scene, int page, int index);
extern "C" void iplSDChannelTitle_cleanupAndLeave(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_confirmLeaveToSettings(SDChannelTitle* scene, bool settings);
extern "C" void iplSDChannelTitle_flushSaveBeforeExit(SDChannelTitle* scene, int nextScene);
extern "C" SDMemory::TitleRange* iplSDChannelTitle_copyTitleRange(SDMemory::TitleRange*, const SDMemory::TitleRange*);

static inline void setMemoryTitleLists(SDMemory* memory, SDMemory::TitleRange sdRange,
                                      SDMemory::TitleRange nandRange) {
    memory->setTitleLists(sdRange, nandRange);
}

static const char* sButtonNames[2] = {"B_BtnA", "B_BtnB"};

static const int sCaptureSizes[2][2] = {{128, 96}, {176, 96}};

static const wchar_t sMissingTitle[] = L"???";

static const char* sButtonGroups[7] = {
    "G_FocusBtnA", "G_FocusBtnB", "G_SelectBtnA", "G_SelectBtnB",
    "G_OnOffBtnA", "G_OnOffBtnB", "G_OutBtn"
};
static const char* sButtonAnimationNames[6] = {
    "mn_SdcardMenuBanner_bc_FocusBtnA_off.brlan",
    "mn_SdcardMenuBanner_bc_FocusBtn_on.brlan",
    "mn_SdcardMenuBanner_bc_SelectBtn_Ac.brlan",
    "mn_SdcardMenuBanner_bc_OffBtn.brlan",
    "mn_SdcardMenuBanner_bc_OnBtn.brlan",
    "mn_SdcardMenuBanner_bc_OutBtn.brlan"
};
static const char* sBannerAnimationNames[3] = {
    "banner.brlan", "banner_Start.brlan", "banner_Loop.brlan"
};
static const char* sTexturePaneNames[3][4] = {
    {"Fre_a", "Fre_d", "Fre_i", "Fre_l"},
    {"Fre_e", "Fre_f", "Fre_g", "Fre_h"},
    {"Fre_b", "Fre_c", "Fre_j", "Fre_k"}
};
static const char* sTextNames[2] = {"T_BtnA", "T_BtnB"};

class SDTitlePaneEventHandler : public ::gui::EventHandler {
public:
    SDTitlePaneEventHandler(SDChannelTitle* scene) : mpScene(scene) {}
    virtual void onEvent(u32 component, u32 event, void* data);
    nw4r::lyt::Pane* getPane(u32 component) {
        return static_cast< ::gui::PaneComponent*>(mpManager->getComponent(component))->getPane();
    }
    SDChannelTitle* mpScene;
};

class SDTitleButtonEventHandler : public SDButtonEventHandlerBase {
public:
    SDTitleButtonEventHandler(SDChannelTitle* scene) : mpScene(scene) {}
    virtual void onEventDerived(u32 component, u32 event, const controller::Interface* controller);
    nw4r::lyt::Pane* getPane(u32 component) {
        return static_cast< ::gui::PaneComponent*>(mpManager->getComponent(component))->getPane();
    }
    SDChannelTitle* mpScene;
};

extern "C" void iplSDChannelObj_applyLanguageGroups(layout::Object* layout);
extern "C" const wchar_t* iplSDChannelObj_getLocalizedName(SDChannelObj* channel, int nameIndex);
extern "C" bool iplSDChannelTitle_startZoomFade(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_rebuildBannerLayout(SDChannelTitle* scene);
extern "C" void iplSDChannelTitle_setPaneMessage(SDChannelTitle* scene, nw4r::lyt::Pane* pane, u32 message, bool allocate);

SDChannelTitle::SDChannelTitle(EGG::Heap* heap, SDChannelSelect* channelSelect)
    : FaderSceneBase(heap), mState(0), mNextScene(0), mParentalResult(0),
      mLaunchFrame(0), mStartButtonState(0), mbBannerStarting(false),
      mpChannelSelect(channelSelect), mpIconLayout(NULL), mpIconHeap(NULL),
      mLoadedIndex(0), mpBannerLayout(NULL), mpSoundHandle(NULL), mpSaveFile(NULL),
      mWpadStopTick(0), mpButtonEventHandler(new SDTitleButtonEventHandler(this)),
      mpTmd(NULL), mbTmdReady(false), mbStartAnimation(false), mScriptState(0),
      mScriptEnabled(0), mbStopScript(false), mScriptFrame(0), mpScriptFile(NULL),
      mScriptHeapIndex(0), mbScriptFailed(false), mpScriptHeap(NULL),
      mbResetAcceptable(true), mpCopySound(NULL) {
    mPage = channelSelect->mCurrentPage;
    mIndex = channelSelect->mCurrentChannelIndex;
    SDChannelObj* channel = channelSelect->findChannelObject(mPage, mIndex);
    if (channel) {
        mTitleId = channel->mAppMeta.titleId;
    }
    mPageCount = mpChannelSelect->mPageCount;
    mPosition.x = SDChannelSelect::getChannelPanePosition(mpChannelSelect, mIndex).x;
    mPosition.y = SDChannelSelect::getChannelPanePosition(mpChannelSelect, mIndex).y;
    mPosition.z = 0.0f;
    mpBannerFiles[0] = NULL;
    mpBannerFiles[1] = NULL;
    mpSoundFiles[0] = NULL;
    mpSoundFiles[1] = NULL;
    for (int button = 0; button < 2; ++button) {
        mHoverCounts[button] = 0;
    }
    setSceneParentFlags(3);
    mpRsoHeap = mpChannelSelect->mpRsoHeap;
    mpRsoThread = mpChannelSelect->mpRsoThread;
    memset(mpScriptAnimations, 0, sizeof(mpScriptAnimations));
    mpBannerHeap = EGG::ExpHeap::create(0x48000, getSceneHeap(), 6);
    mpIconHeap = EGG::ExpHeap::create(0x8100, getSceneHeap(), 6);
}

SDChannelTitle::~SDChannelTitle() {}

void SDChannelTitle::prepare() {
    mpLayoutFile = System::getNandManager()->readLayoutAsync(getSceneHeap(), "sdChanTtl.ash", false);
}

void SDChannelTitle::create() {
    mpLayout = new layout::Object(getSceneHeap(), mpLayoutFile, "arc", "mn_SdcardMenuBanner_bc.brlyt");
    if (SCGetAspectRatio() == SC_ASPECT_RATIO_16x9) {
        GXTexObj textures[3];
        mpLayout->FindPaneByName("Picture_04")->GetMaterial()->GetTexture(&textures[0], 0);
        mpLayout->FindPaneByName("Picture_05")->GetMaterial()->GetTexture(&textures[1], 0);
        mpLayout->FindPaneByName("Picture_06")->GetMaterial()->GetTexture(&textures[2], 0);
        for (int row = 0; row < 3; ++row) {
            for (int column = 0; column < 4; ++column) {
                mpLayout->FindPaneByName(sTexturePaneNames[row][column])->GetMaterial()->SetTexture(0, textures[row]);
            }
        }
    }
    iplSDChannelTitle_setPaneMessage(this, mpLayout->FindPaneByName(sTextNames[0]), 0xa2, true);
    iplSDChannelTitle_setPaneMessage(this, mpLayout->FindPaneByName(sTextNames[1]), 2, true);
    mStartButtonState = 1;
    mpButtonAnimations[0][0] = mpLayout->bindToGroup(sButtonAnimationNames[0], sButtonGroups[0], false, false);
    mpButtonAnimations[0][1] = mpLayout->bindToGroup(sButtonAnimationNames[1], sButtonGroups[0], false, true);
    mpButtonAnimations[1][0] = mpLayout->bindToGroup(sButtonAnimationNames[0], sButtonGroups[1], false, false);
    mpButtonAnimations[1][1] = mpLayout->bindToGroup(sButtonAnimationNames[1], sButtonGroups[1], false, true);
    mpButtonAnimations[2][2] = mpLayout->bindToGroup(sButtonAnimationNames[2], sButtonGroups[2], false, false);
    mpButtonAnimations[3][2] = mpLayout->bindToGroup(sButtonAnimationNames[2], sButtonGroups[3], false, false);
    mpButtonAnimations[4][3] = mpLayout->bindToGroup(sButtonAnimationNames[3], sButtonGroups[4], false, false);
    mpButtonAnimations[5][3] = mpLayout->bindToGroup(sButtonAnimationNames[3], sButtonGroups[5], false, false);
    mpButtonAnimations[4][4] = mpLayout->bindToGroup(sButtonAnimationNames[4], sButtonGroups[4], false, false);
    mpButtonAnimations[5][4] = mpLayout->bindToGroup(sButtonAnimationNames[4], sButtonGroups[5], false, false);
    mpButtonAnimations[6][5] = mpLayout->bindToGroup(sButtonAnimationNames[5], sButtonGroups[6], false, false);
    mpLayout->finishBinding();
    SDTitlePaneEventHandler* paneHandler = new SDTitlePaneEventHandler(this);
    mpPaneManager = new gui::PaneManager(paneHandler, mpLayout->getDrawInfo(), NULL, NULL);
    mpPaneManager->setupScene(mpLayout);
    mpPaneManager->setAllComponentTriggerTarget(false);
    mpPaneManager->getPaneComponentByPane(mpLayout->FindPaneByName(sButtonNames[0]))->setTriggerTarget(true);
    mpPaneManager->getPaneComponentByPane(mpLayout->FindPaneByName(sButtonNames[1]))->setTriggerTarget(true);
    mpProgressLayout = new layout::Object(getSceneHeap(), mpLayoutFile, "arc", "mn_SdcardMenuBanner_a.brlyt");
    mpProgressLayout->bind("mn_SdcardMenuBanner_a_Ch_Fin.brlan");
    mpProgressLayout->bindToGroup("mn_SdcardMenuBanner_a_T_Change.brlan", "G_T_Change", false, true);
    mpProgressLayout->bindToGroup("mn_SdcardMenuBanner_a_Bar.brlan", "G_Prog", false, true);
    mpProgressLayout->bindToGroup("mn_SdcardMenuBanner_a_Wait.brlan", "G_Wait", false, true);
    mpProgressLayout->finishBinding();
    nw4r::lyt::TextBox* comment = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpProgressLayout->FindPaneByName("T_Comment_02"));
    comment->SetString(System::getMessage(0xad));
    iplSDChannelTitle_rebuildBannerLayout(this);
    mpFade = new math::HermiteIntp<f32>();
    mpFade->init(0.0f, 255.0f, 28.0f, 0.0f, 0.0f);
    mpFade->setAnmType(ANIM_TYPE_FORWARD);
    mpScreenCapture = new (System::getTreasureHeap(), 32) utility::Capture(System::getTreasureHeap(), 0, 0,
        System::getRenderModeObj()->fbWidth, System::getRenderModeObj()->efbHeight, GX_TF_RGB565);
    mpCaptureHeap = EGG::ExpHeap::create(0x20000, System::getMem2App(), 6);
    mpBannerCapture = new (mpCaptureHeap, 32) utility::Capture(mpCaptureHeap,
        (System::getRenderModeObj()->fbWidth - sCaptureSizes[SCGetAspectRatio()][0]) / 2,
        (System::getRenderModeObj()->efbHeight - sCaptureSizes[SCGetAspectRatio()][1]) / 2,
        sCaptureSizes[SCGetAspectRatio()][0], sCaptureSizes[SCGetAspectRatio()][1], GX_TF_RGB565);
    mpProgressLayout->FindPaneByName("Ch_Picture")->GetMaterial()->SetTexture(1, mpBannerCapture->getGXTex());
    mpProgressLayout->FindPaneByName("Chm_Picture")->GetMaterial()->SetTexture(1, mpBannerCapture->getGXTex());
    u32 duration = 36000;
    mScriptDuration = duration;
    mState = 2;
    mScriptFrame = duration;
    iplSDChannelTitle_startZoomFade(this);
    mpScriptHeaps[0] = EGG::ExpHeap::create(0x80000, System::getMem2App(), 6);
    mpScriptHeaps[1] = EGG::ExpHeap::create(0x80000, System::getMem2App(), 6);
    mMemory.create(getSceneHeap(), mpLayoutFile, mpChannelSelect);
}

void SDChannelTitle::calcCommon() {
    mpPaneManager->calc();
    mpLayout->calc();
    if (mScriptEnabled == 1) {
        iplSDChannelTitle_updateScript(this);
    }
    if ((mState == 1 || mState == 13 || static_cast<u32>(mState - 4) <= 1) &&
        !mbBannerStarting && mpBannerAnimations[1] && !mpBannerAnimations[1]->isPlaying()) {
        if (mpBannerAnimations[2]) {
            mpBannerAnimations[2]->play();
        } else if (mpBannerAnimations[0]) {
            mpBannerAnimations[0]->play();
        }
        mpBannerAnimations[1] = NULL;
    }
    if (mState == 5 && !mbStartAnimation && !mpButtonAnimations[3][2]->isPlaying()) {
        mpButtonAnimations[1][0]->play();
        mbStartAnimation = true;
    }
    if (mpBannerLayout) {
        mpBannerLayout->calc();
    }
    if (mpIconLayout) {
        mpIconLayout->calc();
    }
    mpProgressLayout->calc();
}

FaderSceneCommand SDChannelTitle::calcFadein() {
    if (mState == 2) {
        iplSDChannelTitle_startZoomFade(this);
        return FADER_SCN_CONTINUE;
    }
    if (!mpFade->isPlaying()) {
        iplSDChannelTitle_playBannerIntro(this);
        SDButton* button = static_cast<SDButton*>(System::getScene(0x24));
        button->setEventHandler(mpButtonEventHandler);
        button->animation(13);
        button->animation(14);
        mState = 1;
        return FADER_SCN_NEXT;
    } else {
        mpFade->calc();
        return FADER_SCN_CONTINUE;
    }
}

FaderSceneCommand SDChannelTitle::calcNormal() {
    switch (mState) {
    case 1: iplSDChannelTitle_updateIdleState(this); break;
    case 4: iplSDChannelTitle_flushSaveBeforeExit(this, mNextScene); mState = 5; break;
    case 8: iplSDChannelTitle_updateChangeState(this); break;
    case 9: iplSDChannelTitle_updateChangeWait(this); break;
    case 10: iplSDChannelTitle_preparePageRestart(this); break;
    case 11: iplSDChannelTitle_updateParentalResult(this); break;
    case 12: iplSDChannelTitle_updateDialogResult(this); break;
    case 13: iplSDChannelTitle_updateTmdReady(this); break;
    case 14: return FADER_SCN_CONTINUE;
    case 15: iplSDChannelTitle_updateCopyStart(this); break;
    case 16: iplSDChannelTitle_updateAfterClearTmp(this); break;
    case 17: SCSetTmpTitleID(mTitleId); SCFlushAsync(NULL); mState = 18; break;
    case 18: if (SCCheckStatus() != 1) { mState = 21; } break;
    case 19: iplSDChannelTitle_startCopyProgress(this); break;
    case 20: iplSDChannelTitle_updateCopyPrepare(this); break;
    case 23: iplSDChannelTitle_updateMemoryCalc(this); break;
    case 21: iplSDChannelTitle_updateEnqueueNotice(this); break;
    case 22: iplSDChannelTitle_updateCopyProgress(this); break;
    case 24: iplSDChannelTitle_loadTitleBanner(this); break;
    case 25: iplSDChannelTitle_updateBannerLoad(this); break;
    case 26: iplSDChannelTitle_showCopyError(this); break;
    case 27: iplSDChannelTitle_updateCopyErrorDialog(this); break;
    case 28: iplSDChannelTitle_tryLaunchSelected(this); break;
    case 29: iplSDChannelTitle_finishProgressHide(this); break;
    case 30: iplSDChannelTitle_returnToIdle(this); break;
    }
    if (mState == 5) {
        mbStopScript = true;
        ++mLaunchFrame;
        System::getPointer()->setVisible(false);
        return static_cast<FaderSceneCommand>(iplSDChannelTitle_isLaunchDelayDone(this));
    }
    if (mState == 6 || mState == 7 || mState == 31) {
        mbStopScript = true;
        return FADER_SCN_NEXT;
    }
    return FADER_SCN_CONTINUE;
}

void SDChannelTitle::initCalcFadeout() {
    SDButton* button = static_cast<SDButton*>(System::getScene(0x24));
    if (mState == 5 || mState == 7 || mState == 31) {
        System::getFader()->fadeOut();
        snd::getSystem()->stopAllSound(20);
        OSReport("sound stopped\n");
    } else if (mState == 6) {
        button->animation(15);
        button->animation(16);
    }
    button->setEventHandler(NULL);
}

FaderSceneCommand SDChannelTitle::calcFadeout() {
    if (mState == 5) {
        if (!mWpadStopTick && WPADGetStatus() == 0) {
            mWpadStopTick = OSGetTick();
        }
        if (System::getFader()->getStatus() == EGG::Fader::PREPARE_IN && System::isReceiveScheduleStopped() &&
            (!System::getNwc24Manager() || System::getNwc24Manager()->isReceivingIdle())) {
            OSReport("NWC24 Scheduler stopped.\n");
            NandSDWorker* worker = mpChannelSelect->getWorker();
            if (mNextScene == 17) {
                if (!nandwall::checkNandCapacityAppBootable()) {
                    OSReport("Nand full! OSRebootSystem.\n");
                    iplSDChannelTitle_rebootSystem(this);
                }
                while (WPADGetStatus() != 0 || System::getBS2Manager()->getIPLState() != bs2::IPL_STATE_8 ||
                       !System::getSaveData()->isFinished(mpSaveFile) ||
                       (mScriptEnabled && mScriptState != 4) || (worker && worker->is_working())) {
                    snd::getSystem()->calc();
                    System::getBS2Manager()->update();
                    VIWaitForRetrace();
                    if (mScriptEnabled == 1) {
                        iplSDChannelTitle_updateScript(this);
                    }
                    if (WPADGetStatus() != 0) {
                        OSReport("wait for WPAD\n");
                    }
                    if (System::getBS2Manager()->getIPLState() != bs2::IPL_STATE_8) {
                        OSReport("wait for BS2\n");
                    }
                }
                if (worker) {
                    worker->terminate_async();
                    while (!worker->is_terminated()) {
                        snd::getSystem()->calc();
                        VIWaitForRetrace();
                    }
                    OSReport("NandSDWorker teminated.\n");
                }
                delete mpSaveFile;
                VISetBlack(TRUE);
                VIFlush();
                VIWaitForRetrace();
                OSReport("VI Black\n");
                while (!__OSSyncSram()) {
                    OSReport("sync sram\n");
                }
                SDChannelObj* channel = mpChannelSelect->findChannelObject(mPage, mIndex);
                union TitleCode {
                    ESTitleId id;
                    struct { u32 type; char code[4]; } parts;
                } title;
                title.id = channel->mAppMeta.titleId;
                wchar_t names[2][21];
                memcpy(names[0], iplSDChannelObj_getLocalizedName(channel, 0), sizeof(names[0]));
                memcpy(names[1], iplSDChannelObj_getLocalizedName(channel, 1), sizeof(names[1]));
                union MakerCode {
                    u16 code;
                    char bytes[2];
                } maker;
                const u8* makerBytes = reinterpret_cast<const u8*>(&mMakerCode);
                maker.bytes[0] = makerBytes[0];
                maker.bytes[1] = makerBytes[1];
                __OSCreatePlayRecord(names[0], title.parts.code, maker.bytes);
                OSReport("Create play recode\n");
                BS2SetStateFlags();
                OSReport("Launch\n");
                __OSLaunchTitlevForSystem(title.id, FALSE, NULL);
            } else {
                math::VEC3 position(0.0f, 0.0f, 0.0f);
                math::VEC2 scale(1.0f, 1.0f);
                utility::Graphics::setOrthoTrans(position);
                utility::Graphics::setOrthoScale(scale);
            }
            return FADER_SCN_NEXT;
        }
    } else if (mState == 6) {
        if (!mpFade->isPlaying()) {
            return FADER_SCN_NEXT;
        }
        mpFade->calc();
    } else if ((mState == 7 || mState == 31) && System::getFader()->getStatus() == EGG::Fader::PREPARE_IN) {
        math::VEC3 position(0.0f, 0.0f, 0.0f);
        utility::Graphics::setOrthoTrans(position);
        math::VEC2 scale(1.0f, 1.0f);
        utility::Graphics::setOrthoScale(scale);
        snd::getSystem()->initFx();
        snd::getSystem()->startBGM("WIPL_BGM_MENU");
        return FADER_SCN_NEXT;
    }
    return FADER_SCN_CONTINUE;
}

void SDChannelTitle::draw() {
    if (mState == 2) {
        return;
    }
    if (System::onDrawLayer(1)) {
        if (mState == 3 || mState == 6) {
            utility::Graphics::setOrtho(0);
            nw4r::ut::Rect bounds(mPosition.x - mpChannelSelect->mThumbOffsetX,
                                  mPosition.y + mpChannelSelect->mThumbOffsetY,
                                  mPosition.x + mpChannelSelect->mThumbOffsetX,
                                  mPosition.y - mpChannelSelect->mThumbOffsetY);
            GXColor color = {255, 255, 255, static_cast<u8>(mpFade->get())};
            utility::Graphics::drawTexture(bounds, mpScreenCapture->getGXTex(), color, 1);
            GXColor mask = {0, 0, 0, static_cast<u8>(mpFade->get())};
            iplSDChannelTitle_drawDimOverlay(this, bounds, mask);
        } else {
            if (mpIconLayout) {
                utility::Graphics::setOrthoProjection(0);
                mpIconLayout->draw();
                mpBannerCapture->capture(FALSE);
            }
            utility::Graphics::setDefaultOrtho(0);
            if (mpBannerLayout) {
                mpBannerLayout->draw();
            } else {
                mpProgressLayout->draw();
            }
            mpLayout->draw();
            if (mState == 23) {
                mMemory.draw();
            }
        }
    } else if (System::onDrawLayer(0) && (mState == 3 || mState == 6)) {
        utility::Graphics::setDefaultOrtho(0);
        if (mpBannerLayout) {
            mpBannerLayout->draw();
        } else {
            mpProgressLayout->draw();
        }
        mpLayout->draw();
        mpScreenCapture->capture(TRUE);
    }
}

void SDChannelTitle::destroy() {
    if (mpBannerFiles[0]) {
        delete mpBannerFiles[0];
    }
    if (mpBannerFiles[1]) {
        delete mpBannerFiles[1];
    }
    if (mpBannerLayout) {
        mpBannerLayout->destroyHeap();
    }
    if (mpSoundFiles[0]) {
        delete mpSoundFiles[0];
    }
    if (mpSoundFiles[1]) {
        delete mpSoundFiles[1];
    }
    delete mpScreenCapture;
    if (mpScriptFile) {
        delete mpScriptFile;
    }
    mpScriptHeaps[0]->destroy();
    mpScriptHeaps[1]->destroy();
    mpBannerHeap->destroy();
    if (mpIconLayout) {
        mpIconLayout->destroyHeap();
    }
    mpIconHeap->destroy();
    delete mpBannerCapture;
    mpCaptureHeap->destroy();
}

BOOL SDChannelTitle::isResetAcceptable() {
    if (mMemory.mTransferFlags[0]) {
        return mbResetAcceptable;
    }
    return FALSE;
}

extern "C" void iplSDChannelTitle_rebuildBannerLayout(SDChannelTitle* scene) {
    iplSDChannelTitle_createBannerLayout(scene);
    if (scene->mpBannerLayout) {
        scene->mpBannerLayout->finishBinding();
    }
}

extern "C" void iplSDChannelTitle_createBannerLayout(SDChannelTitle* scene) {
    if (scene->mpIconLayout) {
        scene->mpIconLayout->destroyHeap();
        scene->mpIconLayout = NULL;
    }
    if (scene->mpBannerFiles[scene->mLoadedIndex] && scene->mpBannerFiles[scene->mLoadedIndex]->checkData() == 1) {
        scene->mpBannerLayout = layout::Object::create(scene->mpBannerHeap, 0x40000,
            scene->mpBannerFiles[scene->mLoadedIndex], "arc", "banner.brlyt");
        iplSDChannelObj_applyLanguageGroups(scene->mpBannerLayout);
        iplSDChannelTitle_bindBannerAnimations(scene);
    } else {
        scene->mpBannerLayout = NULL;
        for (int index = 0; index < 3; ++index) {
            scene->mpBannerAnimations[index] = NULL;
        }
        iplSDChannelTitle_createIconLayout(scene);
    }
}

extern "C" void iplSDChannelTitle_createIconLayout(SDChannelTitle* scene) {
    SDChannelObj* channel = scene->mpChannelSelect->findChannelObject(scene->mPage, scene->mIndex);
    if (channel) {
        scene->mpIconLayout = layout::Object::create(scene->mpIconHeap, 0x8000,
            iplSDChannelObj_getOrAllocThumbnailData(channel), "arc", "icon.brlyt");
        iplSDChannelObj_applyLanguageGroups(scene->mpIconLayout);
        if (scene->mpIconLayout->searchFile("icon.brlan")) {
            scene->mpIconLayout->bind("icon.brlan")->play();
        } else if (scene->mpIconLayout->searchFile("icon_Whole.brlan")) {
            scene->mpIconLayout->bind("icon_Whole.brlan")->play();
        }
        if (channel->mStateFlags == 0) {
            static_cast<nw4r::lyt::TextBox*>(scene->mpProgressLayout->FindPaneByName("T_title"))->SetString(iplSDChannelObj_getLocalizedName(channel, 0));
        } else {
            static_cast<nw4r::lyt::TextBox*>(scene->mpProgressLayout->FindPaneByName("T_title"))->SetString(sMissingTitle);
        }
        scene->mpProgressLayout->getAnim(0)->stop();
        scene->mpProgressLayout->getAnim(0)->initAnmFrame();
        scene->mpProgressLayout->calc();
    }
}

extern "C" void iplSDChannelTitle_updateIdleState(SDChannelTitle* scene) {
    SDButton* button = static_cast<SDButton*>(System::getScene(0x24));
    if (button && button->isActive()) {
        button->update();
    }
    if (scene->mState == 1) {
        if (static_cast<u32>(scene->mpChannelSelect->mCurrentSDState - 1) <= 1) {
            scene->mState = 10;
            iplSDChannelTitle_preparePageRestart(scene);
        } else {
            controller::Interface* controller = System::getMasterController();
            int page;
            int index;
            if (controller->down(0x30001000)) {
                scene->mpChannelSelect->findAdjacentChannel(1, &page, &index);
                iplSDChannelTitle_setPageAndIndex(scene, page, index);
                snd::getSystem()->startSE("WSD_SELECT");
            } else if (controller->down(0x6000010)) {
                scene->mpChannelSelect->findAdjacentChannel(0, &page, &index);
                iplSDChannelTitle_setPageAndIndex(scene, page, index);
                snd::getSystem()->startSE("WSD_SELECT");
            } else {
                scene->mpPaneManager->update();
                if (scene->mStartButtonState == 0) {
                    scene->mStartButtonState = 1;
                } else if (scene->mStartButtonState == 1) {
                    scene->mStartButtonState = 2;
                }
            }
        }
    }
}

extern "C" void iplSDChannelTitle_updateChangeState(SDChannelTitle* scene) {
    if (static_cast<u32>(scene->mpChannelSelect->mCurrentSDState - 1) <= 1) {
        scene->mState = 1;
    } else {
        SDChannelObj* channel = scene->mpChannelSelect->findChannelObject(scene->mPage, scene->mIndex);
        ++scene->mChangeFrame;
        if ((!scene->mpBannerFiles[1 - scene->mLoadedIndex] || scene->mpBannerFiles[1 - scene->mLoadedIndex]->isFinished()) &&
            (!scene->mpSoundFiles[1 - scene->mLoadedIndex] || scene->mpSoundFiles[1 - scene->mLoadedIndex]->isFinished()) &&
            iplSDChannelObj_hasAppMeta(channel) && scene->mChangeFrame > 10 &&
            (!scene->mScriptEnabled || scene->mScriptState == 4)) {
            if (scene->mpBannerFiles[scene->mLoadedIndex]) {
                delete scene->mpBannerFiles[scene->mLoadedIndex];
                if (scene->mpBannerLayout) {
                    scene->mpBannerLayout->destroyHeap();
                }
            }
            scene->mpBannerFiles[scene->mLoadedIndex] = NULL;
            scene->mpBannerLayout = NULL;
            scene->mpScriptHeaps[scene->mScriptHeapIndex]->freeAll();
            scene->mScriptHeapIndex ^= 1;
            snd::getSystem()->stopBannerSound(0);
            snd::getSystem()->stopSE(scene->mpSoundHandle, 0);
            if (scene->mpSoundFiles[scene->mLoadedIndex]) {
                delete scene->mpSoundFiles[scene->mLoadedIndex];
            }
            scene->mpSoundFiles[scene->mLoadedIndex] = NULL;
            scene->mLoadedIndex = 1 - scene->mLoadedIndex;
            iplSDChannelTitle_rebuildBannerLayout(scene);
            iplSDChannelTitle_setStartButtonPressed(scene);
            scene->mState = 9;
        }
    }
}

extern "C" void iplSDChannelTitle_updateChangeWait(SDChannelTitle* scene) {
    if (++scene->mChangeFrame > 20) {
        iplSDChannelTitle_playBannerIntro(scene);
        scene->mState = 1;
    }
}

extern "C" void iplSDChannelTitle_updateParentalResult(SDChannelTitle* scene) {
    ParentalDialog* parental = static_cast<ParentalDialog*>(System::getScene(0x1b));
    if (!parental && !System::getReservedScene()) {
        if (scene->mParentalResult == 1) {
            if (scene->mNextScene == 0x12) {
                scene->reserveAllSceneDestruction(0x12, reinterpret_cast<void*>(1));
                scene->mState = 7;
            } else if (scene->mbCopiedTitle) {
                scene->mState = 25;
            } else {
                scene->mState = 15;
            }
        } else if (scene->mbCopiedTitle) {
            scene->mState = 29;
        } else {
            scene->mpButtonAnimations[1][0]->play();
            static_cast<SDButton*>(System::getScene(0x24))->animation(13);
            static_cast<SDButton*>(System::getScene(0x24))->animation(14);
            for (int button = 0; button < 2; ++button) {
                scene->mHoverCounts[button] = 0;
                scene->mpPaneManager->initPane(scene->mpLayout->FindPaneByName(sButtonNames[button]));
            }
            System::startReceiveSchedule();
            scene->mState = 1;
        }
    } else if (parental) {
        int result = parental->getResult();
        switch (result) {
        case 1:
            if (!scene->mParentalResult) {
                iplSDChannelTitle_prepareSceneExit(scene, scene->mNextScene);
                scene->mParentalResult = 1;
            }
            break;
        case 2:
            scene->mParentalResult = 2;
            break;
        case 3:
            scene->mParentalResult = 2;
            break;
        }
    }
}

extern "C" void iplSDChannelTitle_updateDialogResult(SDChannelTitle* scene) {
    int result = System::getDialog()->getLastResult();
    switch (result) {
    case 2: {
        if (scene->mbCopiedTitle) {
            scene->mState = 29;
        } else {
            static_cast<SDButton*>(System::getScene(0x24))->animation(13);
            static_cast<SDButton*>(System::getScene(0x24))->animation(14);
            scene->mpButtonAnimations[1][0]->play();
            for (int button = 0; button < 2; ++button) {
                scene->mHoverCounts[button] = 0;
                scene->mpPaneManager->initPane(scene->mpLayout->FindPaneByName(sButtonNames[button]));
            }
            System::startReceiveSchedule();
            scene->mState = 1;
        }
        break;
    }
    case 1: {
        if (iplSDChannelTitle_isParentalEnabled()) {
            iplSDChannelTitle_openParentalDialog(scene, reinterpret_cast<void*>(1));
        } else {
            scene->reserveAllSceneDestruction(0x12, reinterpret_cast<void*>(1));
            scene->mState = 7;
        }
        break;
    }
    }
}

extern "C" void iplSDChannelTitle_startCopyProgress(SDChannelTitle* scene) {
    if (scene->mpChannelSelect->getWorker()->is_working() || scene->mpProgressLayout->isPlaying(0) ||
        scene->mpButtonAnimations[3][2]->isPlaying()) {
        return;
    }
    {
        scene->mpProgressLayout->getAnim(1)->setAnmType(ANIM_TYPE_FORWARD);
        scene->mpProgressLayout->getAnim(1)->initAnmFrame();
        scene->mpProgressLayout->getAnim(1)->play();
        scene->mpButtonAnimations[1][0]->initAnmFrame();
        scene->mpButtonAnimations[1][0]->play();
        scene->mpButtonAnimations[6][5]->setAnmType(ANIM_TYPE_FORWARD);
        scene->mpButtonAnimations[6][5]->initAnmFrame();
        scene->mpButtonAnimations[6][5]->play();
        SDChannelObj* channel = scene->mpChannelSelect->findChannelObject(scene->mPage, scene->mIndex);
        if (channel->mStateFlags == 3) {
            scene->mState = 26;
            scene->mErrorMessage = 0xaf;
        } else if (scene->mpChannelSelect->enqueueChannelNotice(scene->mTitleId, reinterpret_cast<u32>(&scene->mTitleRange))) {
            scene->mState = 20;
        } else {
            scene->mState = 26;
            scene->mErrorMessage = 0xae;
        }
    }
}

extern "C" void iplSDChannelTitle_updateCopyPrepare(SDChannelTitle* scene) {
    if (scene->mpChannelSelect->getWorker()->is_working() || scene->mpProgressLayout->isPlaying(1)) {
        return;
    }
    {
        int result = scene->mpChannelSelect->getWorker()->get_async_result();
        if (result == 0 || result == -6) {
            if (scene->mpChannelSelect->isCurrentTitleUsageEnough(reinterpret_cast<const s32*>(&scene->mTitleRange))) {
                scene->mState = 15;
            } else {
                SDMemory::TitleRange sdRange;
                SDMemory::TitleRange nandRange;
                if (static_cast<u32>(scene->mTitleRange.mByteSize) < 0x3800000) {
                    nandRange.mByteSize = 0x3800000;
                    nandRange.mCount = scene->mTitleRange.mCount;
                    iplSDChannelTitle_copyTitleRange(&sdRange, &scene->mTitleRange);
                } else {
                    iplSDChannelTitle_copyTitleRange(&nandRange, iplSDChannelTitle_copyTitleRange(&sdRange, &scene->mTitleRange));
                }
                SDMemory* memory = &scene->mMemory;
                setMemoryTitleLists(memory, sdRange, nandRange);
                scene->mMemory.calc();
                scene->mbResetAcceptable = true;
                System::getHomeButtonMenu()->enable();
                scene->mState = 23;
            }
        } else if (static_cast<u32>(result + 15) <= 1) {
            scene->mState = 26;
            scene->mErrorMessage = 0xaf;
        } else if (result == -16) {
            scene->mState = 26;
            scene->mErrorMessage = 199;
        } else {
            scene->mState = 26;
            scene->mErrorMessage = 0xae;
        }
    }
}

extern "C" SDMemory::TitleRange* iplSDChannelTitle_copyTitleRange(
    SDMemory::TitleRange* target, const SDMemory::TitleRange* source) {
    s32 bytes = source->mByteSize;
    target->mCount = source->mCount;
    target->mByteSize = bytes;
    return target;
}

extern "C" void iplSDChannelTitle_updateMemoryCalc(SDChannelTitle* scene) {
    if (!scene->mMemory.calc()) {
        return;
    }
    switch (static_cast<s32>(scene->mMemory.mErrorCode)) {
    case 4:
        scene->reserveAllSceneDestruction(0x15, reinterpret_cast<void*>(2));
        scene->mState = 31;
        return;
    case 1:
    case 2:
    case 3:
    case 5:
    case 6:
        scene->mbResetAcceptable = false;
        System::getHomeButtonMenu()->disable();
        scene->mState = 29;
        return;
    }
    scene->mbResetAcceptable = false;
    System::getHomeButtonMenu()->disable();
    scene->mState = 15;
}

extern "C" void iplSDChannelTitle_updateCopyStart(SDChannelTitle* scene) {
    if (!scene->mpChannelSelect->getWorker()->is_working()) {
        if (scene->mbCopiedTitle && !scene->mpProgressLayout->isPlaying(3)) {
            scene->mpProgressLayout->getAnim(3)->play();
            scene->mpCopySound = snd::getSystem()->startSE("WIPL_SE_COPYING");
        }
        ESTitleId temporaryTitle = SCGetTmpTitleID();
        if (temporaryTitle && scene->mTitleId != temporaryTitle) {
            if (System::isReceiveScheduleStopped()) {
                if (scene->mpChannelSelect->enqueueStateNotice(temporaryTitle, 1)) {
                    scene->mState = 16;
                } else {
                    scene->mState = 26;
                    scene->mErrorMessage = 0xae;
                }
            }
        } else if (scene->mbCopiedTitle) {
            scene->mState = 17;
        } else {
            scene->mState = 24;
        }
    }
}

extern "C" void iplSDChannelTitle_updateAfterClearTmp(SDChannelTitle* scene) {
    if (!scene->mpChannelSelect->getWorker()->is_working()) {
        SCSetTmpTitleID(0);
        System::getChannelManager()->clearTmpChannel();
        int result = scene->mpChannelSelect->getWorker()->get_async_result();
        if (!result) {
            if (scene->mbCopiedTitle) {
                scene->mState = 17;
            } else {
                scene->mState = 24;
            }
        } else {
            SCFlushAsync(NULL);
            scene->mState = 26;
            scene->mErrorMessage = 0xae;
        }
    }
}

extern "C" void iplSDChannelTitle_updateEnqueueNotice(SDChannelTitle* scene) {
    if (!scene->mpChannelSelect->getWorker()->is_working()) {
        if (scene->mpChannelSelect->enqueueResultNotice(static_cast<u32>(scene->mTitleId))) {
            scene->mState = 22;
        } else {
            scene->mState = 26;
            scene->mErrorMessage = 0xae;
        }
    }
}

extern "C" void iplSDChannelTitle_updateCopyProgress(SDChannelTitle* scene) {
    scene->mpProgressLayout->getAnim(2)->initAnmFrame(NandSDWorker::getCompletionPct());
    if (!scene->mpChannelSelect->getWorker()->is_working()) {
        int result = scene->mpChannelSelect->getWorker()->get_async_result();
        if (result == 0 || result == -6) {
            System::getChannelManager()->loadTmpMetaHeader(scene->mTitleId);
            scene->mpProgressLayout->getAnim(3)->stop();
            snd::getSystem()->stopSE(scene->mpCopySound, 0);
            scene->mpCopySound = NULL;
            snd::getSystem()->startSE("WIPL_SE_COPY_FINISH");
            System::getTask1()->request(iplSDChannelTitle_fetchTmdViewTask, scene, NULL);
            scene->mState = 24;
        } else {
            SCSetTmpTitleID(0);
            SCFlushAsync(NULL);
            scene->mState = 26;
            if (result == -15) {
                scene->mErrorMessage = 0xaf;
            } else if (result == -16) {
                scene->mErrorMessage = 199;
            } else {
                scene->mErrorMessage = 0xae;
            }
        }
    }
}

extern "C" void iplSDChannelTitle_showCopyError(SDChannelTitle* scene) {
    scene->mpProgressLayout->getAnim(3)->stop();
    snd::getSystem()->stopSE(scene->mpCopySound, 0);
    scene->mpCopySound = NULL;
    System::getDialog()->callBtn1(scene->mErrorMessage, 0x2e);
    scene->mState = 27;
}

extern "C" void iplSDChannelTitle_updateCopyErrorDialog(SDChannelTitle* scene) {
    if (SCCheckStatus() != 1 && System::getDialog()->getLastResult() != -1) {
        scene->mState = 29;
    }
}

extern "C" void iplSDChannelTitle_finishProgressHide(SDChannelTitle* scene) {
    if (!scene->mpProgressLayout->isPlaying(1) && !scene->mpButtonAnimations[1][0]->isPlaying() &&
        !scene->mpButtonAnimations[6][5]->isPlaying()) {
        scene->mbResetAcceptable = true;
        System::getHomeButtonMenu()->enable();
        scene->mpProgressLayout->getAnim(1)->setAnmType(ANIM_TYPE_BACKWARD);
        scene->mpProgressLayout->getAnim(1)->initAnmFrame();
        scene->mpProgressLayout->getAnim(1)->play();
        scene->mpButtonAnimations[6][5]->setAnmType(ANIM_TYPE_BACKWARD);
        scene->mpButtonAnimations[6][5]->initAnmFrame();
        scene->mpButtonAnimations[6][5]->play();
        scene->mpButtonAnimations[1][0]->initAnmFrame();
        scene->mpButtonAnimations[1][0]->play();
        static_cast<SDButton*>(System::getScene(0x24))->animation(13);
        static_cast<SDButton*>(System::getScene(0x24))->animation(14);
        System::startReceiveSchedule();
        scene->mState = 30;
    }
}

extern "C" void iplSDChannelTitle_returnToIdle(SDChannelTitle* scene) {
    if (!scene->mpProgressLayout->isPlaying(1) && !scene->mpButtonAnimations[6][5]->isPlaying()) {
        for (int button = 0; button < 2; ++button) {
            scene->mHoverCounts[button] = 0;
            scene->mpPaneManager->initPane(scene->mpLayout->FindPaneByName(sButtonNames[button]));
        }
        scene->mState = 1;
    }
}

extern "C" void iplSDChannelTitle_loadTitleBanner(SDChannelTitle* scene) {
    int page;
    int index;
    if (System::getChannelManager()->isLoadedTmp() || System::getChannelManager()->hasChannel(scene->mTitleId, &page, &index)) {
        scene->mpBannerFiles[scene->mLoadedIndex] = iplSDChannelTitle_loadBannerMetaFiles(scene, scene->mTitleId,
                                                                         &scene->mpSoundFiles[scene->mLoadedIndex]);
        if (scene->mbCopiedTitle) {
            scene->mState = 13;
        } else {
            scene->mState = 25;
        }
    }
}

extern "C" void iplSDChannelTitle_updateBannerLoad(SDChannelTitle* scene) {
    if (!scene->mpBannerFiles[scene->mLoadedIndex] || scene->mpBannerFiles[scene->mLoadedIndex]->isFinished()) {
        iplSDChannelTitle_loadBannerScript(scene, scene->mTitleId);
        iplSDChannelTitle_rebuildBannerLayout(scene);
        scene->mState = 4;
        iplSDChannelTitle_playBannerIntro(scene);
    }
}

extern "C" void iplSDChannelTitle_tryLaunchSelected(SDChannelTitle* scene) {
    if (static_cast<u32>(scene->mpChannelSelect->mCurrentSDState - 1) <= 1) {
        scene->mState = 1;
    } else {
        SDChannelObj* channel = scene->mpChannelSelect->findChannelObject(scene->mPage, scene->mIndex);
        if (iplSDChannelObj_hasAppMeta(channel)) {
            iplSDChannelTitle_beginLaunch(scene, channel);
        }
    }
}

extern "C" void iplSDChannelTitle_updateTmdReady(SDChannelTitle* scene) {
    if (scene->mbTmdReady) {
        if (!System::getChannelManager()->isMissingTicket(scene->mTitleId) && !utility::ESMisc::CheckTmdCountryCode(scene->mpTmd)) {
            System::getErrorHandler()->set(ErrorHandler::DEFAULT, 3, NULL, 0, -1);
        }
        scene->mMakerCode = scene->mpTmd->head.groupId;
        if (!iplSDChannelTitle_isNetworkAllowed(scene, scene->mpTmd, scene->mTitleId)) {
            iplSDChannelTitle_confirmLeaveToSettings(scene, false);
            scene->mNextScene = 18;
        } else if (iplSDChannelTitle_passesParentalCheck(scene, scene->mpTmd)) {
            iplSDChannelTitle_prepareSceneExit(scene, scene->mNextScene);
            if (scene->mbCopiedTitle) {
                scene->mState = 25;
            } else {
                scene->mState = 15;
            }
        } else {
            iplSDChannelTitle_openParentalDialog(scene, NULL);
        }
        if (scene->mpTmd) {
            scene->mpBannerHeap->free(scene->mpTmd);
        }
    }
}

extern "C" bool iplSDChannelTitle_startZoomFade(SDChannelTitle* scene) {
    if (!scene->mpChannelSelect->tellStartingZoomAnm()) {
        return false;
    }
    scene->mpFade->play();
    scene->mState = 3;
    return true;
}

extern "C" void iplSDChannelTitle_preparePageRestart(SDChannelTitle* scene) {
    if (!scene->mScriptEnabled || scene->mScriptState == 4) {
        if (scene->mpChannelSelect->prepareRestarting(scene->mPage)) {
            scene->mpChannelSelect->startPageTransition(scene->mPage, scene->mIndex);
            scene->mpFade->init(0.0f, 255.0f, 28.0f, 0.0f, 0.0f);
            scene->mpFade->setAnmType(ANIM_TYPE_BACKWARD);
            scene->mpFade->play();
            scene->mState = 6;
            snd::getSystem()->startSE("WIPL_SE_CH_UNSELECT");
            if (snd::getBannerPlayer()->isStarted()) {
                snd::getSystem()->stopBannerSound(28);
            }
            if (scene->mpSoundHandle && scene->mpSoundHandle->IsAttachedSound()) {
                snd::getSystem()->stopSE(scene->mpSoundHandle, 28);
            }
        }
    } else {
        scene->mbStopScript = true;
    }
}

extern "C" void iplSDChannelTitle_loadBannerScript(SDChannelTitle* scene, ESTitleId title) {
    if (!System::isSafeMode()) {
        if (scene->mScriptEnabled) {
            delete scene->mpScriptFile;
            scene->mpScriptFile = NULL;
        }
        if (System::getChannelManager()->getBannerCSIdx(title)) {
            scene->mpScriptFile = System::getChannelManager()->readBannerCSAsync(scene->mpRsoHeap, title);
            scene->mbScriptFailed = false;
            scene->mScriptEnabled = 1;
            scene->mScriptState = 1;
        } else {
            scene->mScriptEnabled = 0;
            scene->mScriptState = 0;
        }
    }
}

extern "C" void iplSDChannelTitle_updateScript(SDChannelTitle* scene) {
    if (scene->mScriptEnabled != 1) {
        return;
    }
    if (scene->mState == 2 || scene->mState == 3 || scene->mState == 9) {
        return;
    }
    switch (scene->mScriptState) {
    case 0:
        iplSDChannelTitle_updateScriptIdle(scene);
        break;
    case 1:
        iplSDChannelTitle_updateScriptLoad(scene);
        break;
    case 2:
        System::getCSManager()->calc();
        if (scene->mpRsoThread->IsThreadTerminated()) {
            if (System::getCSManager()->getAltSoundState() == 1) {
                iplSDChannelTitle_startBannerSound(scene);
                System::getCSManager()->setAltSoundState(0);
            }
            System::getCSManager()->finish();
            scene->mScriptState = 3;
        }
        break;
    case 3:
        iplSDChannelTitle_destroyScript(scene);
        break;
    }
}

extern "C" void iplSDChannelTitle_updateScriptIdle(SDChannelTitle* scene) {
    if (scene->mbStopScript) {
        scene->mbStopScript = false;
        scene->mScriptFrame = 0;
        scene->mScriptState = 4;
    } else {
        if (++scene->mScriptFrame > scene->mScriptDuration) {
            int nextHeap = scene->mScriptHeapIndex ^ 1;
            scene->mScriptState = 1;
            scene->mScriptHeapIndex = nextHeap;
        }
        if (System::getChannelManager()->usesAltSound(scene->mTitleId) &&
            scene->mScriptFrame == scene->mScriptDuration - 240) {
            snd::getSystem()->stopBannerSound(180);
        }
    }
}

extern "C" void iplSDChannelTitle_updateScriptLoad(SDChannelTitle* scene) {
    if (!scene->mpScriptFile->isFinished()) {
        return;
    }
    if (scene->mpScriptFile->checkData() != 1 && scene->mpScriptFile->checkData() != 0) {
        scene->mScriptFrame = 0;
        scene->mbScriptFailed = true;
        scene->mScriptState = 0;
        return;
    }
    if (!scene->mpScriptHeap) {
        scene->mpScriptHeap = EGG::ExpHeap::create(-1, scene->mpRsoHeap, 0);
    }
    System::getCSManager()->create(scene->mpScriptHeap);
    channel::ChannelScriptManager::CSData data = {NULL, NULL, NULL, 0, false, false, true};
    data.heap = scene->mpScriptHeaps[scene->mScriptHeapIndex];
    data.layout = scene->mpBannerLayout;
    data.anims = scene->mpScriptAnimations;
    data.titleId = scene->mTitleId;
    data.threadTerminated = scene->mbScriptFailed;
    if (!System::getNwc24Manager() || !System::getNwc24Manager()->isNewMessageThere(static_cast<u32>(data.titleId & 0xffffffffULL))) {
        data.unk_0x1A = false;
    }
    System::getCSManager()->setData(data);
    if (!System::getCSManager()->init(scene->mpScriptFile, scene->mpRsoThread)) {
        scene->mScriptState = 3;
    } else {
        scene->mScriptState = 2;
    }
}

extern "C" void iplSDChannelTitle_destroyScript(SDChannelTitle* scene) {
    scene->mbScriptFailed = true;
    System::getCSManager()->destroy();
    scene->mScriptFrame = 0;
    scene->mpScriptHeaps[1 - scene->mScriptHeapIndex]->freeAll();
    scene->mpScriptHeap->destroy();
    scene->mpScriptHeap = NULL;
    scene->mScriptState = 0;
}

extern "C" void iplSDChannelTitle_playBannerIntro(SDChannelTitle* scene) {
    if (scene->mpBannerAnimations[1]) {
        scene->mpBannerAnimations[1]->play();
        scene->mbBannerStarting = false;
    } else if (scene->mpBannerAnimations[2]) {
        scene->mpBannerAnimations[2]->play();
    } else if (scene->mpBannerAnimations[0]) {
        scene->mpBannerAnimations[0]->play();
    }
    if (scene->mState != 6) {
        if (!System::getChannelManager()->usesAltSound(scene->mTitleId) || !scene->mScriptEnabled) {
            iplSDChannelTitle_startBannerSound(scene);
        }
        if (!scene->mpBannerLayout) {
            scene->mpProgressLayout->getAnim(0)->initAnmFrame();
            scene->mpProgressLayout->getAnim(0)->play();
            scene->mpSoundHandle = snd::getSystem()->startSE("WIPL_ME_SD_BANNER");
        }
    }
}

extern "C" void iplSDChannelTitle_startBannerSound(SDChannelTitle* scene) {
    if (scene->mpSoundFiles[scene->mLoadedIndex] && scene->mpSoundFiles[scene->mLoadedIndex]->checkData() == 1) {
        void* sound = scene->mpSoundFiles[scene->mLoadedIndex]->getBuffer();
        u32 size = System::getChannelManager()->getSoundSize(scene->mTitleId);
        snd::getSystem()->startBannerSound(sound, size, false);
    }
}

extern "C" void iplSDChannelTitle_bindBannerAnimations(SDChannelTitle* scene) {
    iplSDChannelTitle_bindBannerAnims(scene);
    if (scene->mScriptEnabled) {
        memset(scene->mpScriptAnimations, 0, sizeof(scene->mpScriptAnimations));
        iplSDChannelTitle_bindRsoAnimations(scene, scene->mpBannerLayout, scene->mpScriptAnimations, "banner");
    }
}

extern "C" void iplSDChannelTitle_bindRsoAnimations(SDChannelTitle*, layout::Object* layout,
                                         layout::Animator** animations, const char* prefix) {
    char groupName[8];
    char animationName[20];
    for (int index = 0; index < 16; ++index) {
        sprintf(animationName, "%s_Rso%d.brlan", prefix, index);
        if (layout->searchFile(animationName)) {
            sprintf(groupName, "Rso%d", index);
            bool bound = false;
            nw4r::lyt::GroupList& groups = layout->GetGroupList();
            for (nw4r::lyt::GroupList::Iterator group = groups.GetBeginIter(); group != groups.GetEndIter(); ++group) {
                if (strcmp(group->GetName(), groupName) == 0) {
                    animations[index] = layout->bindToGroup(animationName, groupName, false, false);
                    bound = true;
                    break;
                }
            }
            if (!bound) {
                animations[index] = layout->bind(animationName, false);
            }
        }
    }
}

extern "C" void iplSDChannelTitle_bindBannerAnims(SDChannelTitle* scene) {
    for (int index = 0; index < 3; ++index) {
        if (scene->mpBannerLayout->searchFile(sBannerAnimationNames[index])) {
            if (index == 0) {
                scene->mpBannerAnimations[index] = scene->mpBannerLayout->bind(sBannerAnimationNames[index]);
                scene->mpBannerAnimations[index]->setAnmType(ANIM_TYPE_LOOP);
            } else if (index == 1) {
                scene->mpBannerAnimations[index] = scene->mpBannerLayout->bind(sBannerAnimationNames[index]);
                scene->mpBannerAnimations[index]->setAnmType(ANIM_TYPE_FORWARD);
            } else {
                if (!scene->mpBannerAnimations[1]) {
                    scene->mpBannerAnimations[index] = scene->mpBannerLayout->bind(sBannerAnimationNames[index], true);
                } else {
                    scene->mpBannerAnimations[index] = scene->mpBannerLayout->bind(sBannerAnimationNames[index], false);
                }
                scene->mpBannerAnimations[index]->setAnmType(ANIM_TYPE_LOOP);
            }
        } else {
            scene->mpBannerAnimations[index] = NULL;
        }
    }
}

extern "C" BOOL iplSDChannelTitle_isNetworkAllowed(SDChannelTitle*, ESTmdView*, ESTitleId titleId) {
    if (!System::getChannelManager()->needsNetSetting(titleId) || ncd::NCDSetting::getConnectEnableFlag()) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL iplSDChannelTitle_isParentalEnabled() {
    SCParentalControlsInfo parental;
    if (SCGetParentalControl(&parental) && (parental.enable & SC_PARENTAL_FLAG_ENABLED)) {
        return TRUE;
    }
    return FALSE;
}

extern "C" void iplSDChannelTitle_openParentalDialog(SDChannelTitle* scene, void* arguments) {
    System::getHomeButtonMenu()->enable();
    scene->mbResetAcceptable = true;
    if (static_cast<SDButton*>(System::getScene(0x24))->isLeftArrowVisible()) {
        static_cast<SDButton*>(System::getScene(0x24))->animation(15);
        static_cast<SDButton*>(System::getScene(0x24))->animation(16);
    }
    scene->createChildScene(0x1b, scene, NULL, arguments);
    scene->mParentalResult = 0;
    scene->mState = 11;
}

extern "C" void iplSDChannelTitle_setPageAndIndex(SDChannelTitle* scene, int page, int index) {
    SDChannelObj* keep = NULL;
    if (scene->mpIconLayout) {
        keep = scene->mpChannelSelect->findChannelObject(scene->mPage, scene->mIndex);
    }
    scene->mPage = page;
    scene->mIndex = index;
    scene->mpChannelSelect->setCurrentPageAndRefresh(page, index, keep);
    SDChannelObj* channel = scene->mpChannelSelect->findChannelObject(scene->mPage, scene->mIndex);
    scene->mPosition.x = SDChannelSelect::getChannelPanePosition(scene->mpChannelSelect, scene->mIndex).x;
    scene->mPosition.y = SDChannelSelect::getChannelPanePosition(scene->mpChannelSelect, scene->mIndex).y;
    if (iplSDChannelObj_hasAppMeta(channel)) {
        iplSDChannelTitle_beginLaunch(scene, channel);
    } else {
        scene->mState = 28;
    }
}

extern "C" void iplSDChannelTitle_beginLaunch(SDChannelTitle* scene, SDChannelObj* channel) {
    scene->mTitleId = channel->mAppMeta.titleId;
    if (scene->mScriptEnabled) {
        scene->mbStopScript = true;
    }
    scene->mChangeFrame = 0;
    scene->mState = 8;
}

extern "C" void iplSDChannelTitle_cleanupAndLeave(SDChannelTitle* scene) {
    scene->mParentalResult = 0;
    scene->mbStartAnimation = false;
    static_cast<SDButton*>(System::getScene(0x24))->animation(15);
    static_cast<SDButton*>(System::getScene(0x24))->animation(16);
    if (scene->mpBannerFiles[scene->mLoadedIndex]) {
        delete scene->mpBannerFiles[scene->mLoadedIndex];
    }
    if (scene->mpSoundFiles[scene->mLoadedIndex]) {
        delete scene->mpSoundFiles[scene->mLoadedIndex];
    }
    if (scene->mpBannerLayout) {
        scene->mpBannerLayout->destroyHeap();
    }
    scene->mpBannerFiles[scene->mLoadedIndex] = NULL;
    scene->mpBannerLayout = NULL;
    scene->mpSoundFiles[scene->mLoadedIndex] = NULL;
    int page;
    int index;
    bool hasTitle = System::getChannelManager()->hasChannel(scene->mTitleId, &page, &index) != 0;
    bool hasTemporaryTitle = false;
    if (scene->mTitleId == SCGetTmpTitleID() && System::getChannelManager()->isLoadedTmp()) {
        hasTemporaryTitle = true;
    }
    scene->mNextScene = 17;
    scene->mbTmdReady = false;
    scene->mMakerCode = 0;
    scene->mbResetAcceptable = false;
    System::getHomeButtonMenu()->disable();
    System::stopReceiveSchedule();
    if (hasTitle || hasTemporaryTitle) {
        System::getTask1()->request(iplSDChannelTitle_fetchTmdViewTask, scene, NULL);
        scene->mbCopiedTitle = false;
        scene->mState = 13;
    } else {
        scene->mpChannelSelect->clearCommandQueue();
        scene->mpChannelSelect->clearNoticeQueue();
        scene->mbCopiedTitle = true;
        scene->mState = 19;
    }
}

extern "C" void iplSDChannelTitle_confirmLeaveToSettings(SDChannelTitle* scene, bool settings) {
    if (settings) {
        scene->reserveAllSceneDestruction(0x12, reinterpret_cast<void*>(1));
        scene->mState = 7;
    } else {
        if (static_cast<SDButton*>(System::getScene(0x24))->isLeftArrowVisible()) {
            static_cast<SDButton*>(System::getScene(0x24))->animation(15);
            static_cast<SDButton*>(System::getScene(0x24))->animation(16);
        }
        System::getDialog()->callBtn2(0x143, 0x146, 0x25, false);
        scene->mState = 12;
        System::getHomeButtonMenu()->enable();
        scene->mbResetAcceptable = true;
    }
}

extern "C" void iplSDChannelTitle_prepareSceneExit(SDChannelTitle* scene, int nextScene) {
    for (int index = 0; index < 4; ++index) {
        controller::Interface* controller = System::getController(index);
        if (controller) {
            controller->cancelRumbling();
        }
    }
    if (nextScene == 17) {
        System::getHomeButtonMenu()->disable();
        scene->mbResetAcceptable = false;
    }
}

extern "C" void iplSDChannelTitle_flushSaveBeforeExit(SDChannelTitle* scene, int nextScene) {
    int page;
    int index;
    if (System::getChannelManager()->hasChannel(scene->mTitleId, &page, &index)) {
        System::getSaveData()->pushTitleCache(scene->mTitleId);
    }
    System::getSaveData()->getSDPrevPage() = scene->mPage;
    EGG::Heap* saveHeap = System::getMem2App();
    scene->mpSaveFile = System::getSaveData()->flushAsync(saveHeap);
    __WPADReconnect(TRUE);
}

extern "C" void iplSDChannelTitle_rebootSystem(SDChannelTitle*) {
    snd::getSystem()->stopAllSound(0);
    snd::getSystem()->calc();
    VISetBlack(TRUE);
    VIFlush();
    VIWaitForRetrace();
    while (!__OSSyncSram()) {
    }
    OSRebootSystem();
}

extern "C" bool iplSDChannelTitle_isLaunchDelayDone(SDChannelTitle* scene) {
    return static_cast<u32>(120.0f / System::getAnimDelta()) < scene->mLaunchFrame;
}

extern "C" void iplSDChannelTitle_setStartButtonPressed(SDChannelTitle* scene) {
    if (!scene->mStartButtonState) {
        scene->mpButtonAnimations[5][3]->stop();
        scene->mpButtonAnimations[5][4]->play();
        scene->mpPaneManager->initPane(scene->mpLayout->FindPaneByName(sButtonNames[1]));
        scene->mHoverCounts[1] = 0;
    }
    scene->mStartButtonState = 1;
}

extern "C" void iplSDChannelTitle_drawDimOverlay(SDChannelTitle*, const nw4r::ut::Rect& bounds, GXColor color) {
    nw4r::ut::Rect screen;
    System::getProjectionRect(&screen);
    nw4r::ut::Rect rectangles[4];
    rectangles[0].left = screen.left;
    rectangles[0].top = screen.bottom;
    rectangles[0].right = screen.right;
    rectangles[0].bottom = bounds.top;
    rectangles[1].left = bounds.right;
    rectangles[1].top = bounds.top;
    rectangles[1].right = screen.right;
    rectangles[1].bottom = screen.top;
    rectangles[2].left = screen.left;
    rectangles[2].top = bounds.bottom;
    rectangles[2].right = bounds.right;
    rectangles[2].bottom = screen.top;
    rectangles[3].left = screen.left;
    rectangles[3].top = bounds.top;
    rectangles[3].right = bounds.left;
    rectangles[3].bottom = bounds.bottom;
    for (int index = 0; index < 4; ++index) {
        utility::Graphics::drawPolygon(rectangles[index], color);
    }
}

extern "C" void iplSDChannelTitle_setPaneMessage(SDChannelTitle*, nw4r::lyt::Pane* pane, u32 message, bool allocate) {
    wchar_t text[256];
    wcsncpy(text, System::getMessage(message), 256);
    text[255] = 0;
    nw4r::lyt::TextBox* textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(pane);
    if (allocate) {
        size_t length = wcslen(text);
        textBox->AllocStringBuffer(static_cast<u16>(length));
    }
    textBox->SetString(text);
}

extern "C" nand::LayoutFile* iplSDChannelTitle_loadBannerMetaFiles(SDChannelTitle*, ESTitleId title, nand::File** sound) {
    *sound = System::getChannelManager()->readSoundMetaAsync(System::getMem2App(), title);
    nand::MetaFile* banner = System::getChannelManager()->readBannerMetaAsync(System::getMem2App(), title);
    return new (System::getMem2App(), 4) nand::LayoutFile(banner, NULL);
}

extern "C" void iplSDChannelTitle_fetchTmdViewTask(void* argument) {
    SDChannelTitle* scene = static_cast<SDChannelTitle*>(argument);
    ESError result = utility::ESMisc::GetTmdView(scene->mpBannerHeap, scene->mTitleId, &scene->mpTmd);
    if (result) {
        System::getErrorHandler()->log("ES", result, "iplSDChannelTitle.cpp", 0xc6d);
        System::getErrorHandler()->set(ErrorHandler::DEFAULT, 2, NULL, 0, -1);
    }
    scene->mbTmdReady = true;
}

extern "C" BOOL iplSDChannelTitle_passesParentalCheck(SDChannelTitle* scene, ESTmdView* tmd) {
    if (!utility::ESMisc::__IsPCEnable()) {
        return TRUE;
    }
    SCParentalControlsInfo parental;
    if (!SCGetParentalControl(&parental)) {
        return TRUE;
    }
    if (parental.enable & SC_PARENTAL_FLAG_ENABLED) {
        u32 restrictions = System::getChannelManager()->isNewsChannelV6Plus(scene->mTitleId);
        u32 networkRestrictions = SCGetNetContentRestrictions();
        if (networkRestrictions & restrictions) {
            return FALSE;
        }
        if (SCGetWwwRestriction() && System::getChannelManager()->isOperaChannel(scene->mTitleId)) {
            return FALSE;
        }
        if (System::getChannelManager()->isOperaChannel(scene->mTitleId)) {
            return TRUE;
        } else {
            return utility::ESMisc::CheckTmdParentalControl(tmd);
        }
    }
    return TRUE;
}

void SDTitlePaneEventHandler::onEvent(u32 component, u32 event, void* data) {
    SDTitlePaneEventHandler* handler = this;
    const controller::Interface* controller = static_cast<const controller::Interface*>(data);
    const char* paneName = handler->getPane(component)->GetName();
    switch (event) {
    case ::gui::EventHandler::ON_TRIG: {
        if (handler->mpScene->mState == 1 && controller->downTrg(0x100800)) {
            if (strcmp(paneName, sButtonNames[0]) == 0) {
                handler->mpScene->mpButtonAnimations[2][2]->play();
                snd::getSystem()->startSE("WIPL_SE_BT_PUSH");
                handler->mpScene->mState = 10;
                iplSDChannelTitle_preparePageRestart(handler->mpScene);
            } else if (strcmp(paneName, sButtonNames[1]) == 0) {
                if (handler->mpScene->mStartButtonState != 2) {
                    snd::getSystem()->startSE("WIPL_SE_GRAY_BUTTON");
                } else {
                    iplSDChannelTitle_cleanupAndLeave(handler->mpScene);
                    handler->mpScene->mpButtonAnimations[3][2]->play();
                    snd::getSystem()->stopSE(handler->mpScene->mpSoundHandle, 30);
                    snd::getSystem()->startSE("WIPL_SE_DECIDE");
                }
            }
        }
        break;
    }
    case ::gui::EventHandler::ON_POINT: {
        for (int button = 0; button < 2; ++button) {
            if (strcmp(paneName, sButtonNames[button]) == 0 &&
                (button == 0 || handler->mpScene->mStartButtonState > 0)) {
                ++handler->mpScene->mHoverCounts[button];
                if (handler->mpScene->mHoverCounts[button] <= 1) {
                    handler->mpScene->mpButtonAnimations[button][1]->play();
                    snd::getSystem()->startSE("WIPL_SE_BT_TARGETTING");
                    const_cast<controller::Interface*>(controller)->rumble(0);
                    break;
                }
            }
        }
        break;
    }
    case ::gui::EventHandler::ON_LEFT: {
        for (int button = 0; button < 2; ++button) {
            if (strcmp(paneName, sButtonNames[button]) == 0 &&
                (button == 0 || handler->mpScene->mStartButtonState > 0)) {
                s32& count = handler->mpScene->mHoverCounts[button];
                if (count <= 0) {
                    break;
                }
                --count;
                if (handler->mpScene->mHoverCounts[button] <= 0) {
                    handler->mpScene->mpButtonAnimations[button][0]->play();
                    break;
                }
            }
        }
        break;
    }
    }
}

void SDTitleButtonEventHandler::onEventDerived(u32 component, u32 event, const controller::Interface* controller) {
    SDTitleButtonEventHandler* handler = this;
    const char* name = handler->getPane(component)->GetName();
    switch (event) {
    case 0:
        if (handler->mpScene->mState == 1 && controller->downTrg(0x100800)) {
            SDButton* button = static_cast<SDButton*>(System::getScene(0x24));
            if (strcmp(name, SDButton::getButtonName(SDButton::BTN_ARROW_LEFT)) == 0) {
                int page;
                int index;
                handler->mpScene->mpChannelSelect->findAdjacentChannel(1, &page, &index);
                button->animation(7);
                iplSDChannelTitle_setPageAndIndex(handler->mpScene, page, index);
                snd::getSystem()->startSE("WSD_SELECT");
            } else if (strcmp(name, SDButton::getButtonName(SDButton::BTN_ARROW_RIGHT)) == 0) {
                int page;
                int index;
                handler->mpScene->mpChannelSelect->findAdjacentChannel(0, &page, &index);
                button->animation(8);
                iplSDChannelTitle_setPageAndIndex(handler->mpScene, page, index);
                snd::getSystem()->startSE("WSD_SELECT");
            }
        }
        break;
    }
}

void SDChannelTitle::startResetting() {
    snd::getSystem()->resetAllSound();
}

extern "C" void iplSDChannelTitle_onTitleButtonEvent(SDTitleButtonEventHandler* handler, u32 component,
                                         u32 event, const controller::Interface* controller) {
    handler->onEventDerived(component, event, controller);
}

extern "C" void iplSDChannelTitle_onTitlePaneEvent(SDTitlePaneEventHandler* handler, u32 component,
                                         u32 event, const controller::Interface* controller) {
    handler->onEvent(component, event, const_cast<controller::Interface*>(controller));
}

}
}
