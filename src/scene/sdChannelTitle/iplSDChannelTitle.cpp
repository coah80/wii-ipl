#define IPL_CHANNEL_TITLE_NOVTABLE
#define IPL_SD_CHANNEL_TITLE_NOVTABLE

#include "scene/sdChannelTitle/iplSDChannelTitle.h"

#include <revolution.h>

#include <private/wpad/WPADInternal.h>
#include <private/os/OSExec.h>
#include <private/os/OSPlayRecord.h>
#include <private/os/OSSram.h>
#include <revolution/sc.h>
#include <revolution/vi.h>
#include <revolution/wpad.h>

#include <nw4r/lyt.h>
#include <nw4r/math.h>
#include <nw4r/ut.h>

#include <cstring>

#include "iplScene.h"
#include "iplSound.h"
#include "iplSystem.h"
#include "iplUtility.h"

#include "scene/parentalDialog/iplParentalDialog.h"
#include "scene/sdButton/iplSDButton.h"
#include "scene/setting/iplNCDSetting.h"

#include "system/iplChannelManager.h"
#include "system/iplChannelRsoThread.h"
#include "system/iplChannelScriptManager.h"
#include "system/iplDialogWindow.h"
#include "system/iplHomeButton.h"
#include "system/iplMessage.h"
#include "system/iplNandSDWorker.h"
#include "system/iplNandWall.h"

#include "utility/iplESMisc.h"

#pragma dont_instantiate ipl::math::HermiteIntp<float>



namespace ipl {
    namespace scene {
        // clang-format off
        extern "C" char lbl_81696E30[];
        extern "C" char lbl_81696E37[];
        // clang-format on

        static const wchar_t scUnknownTitle[] = L"???";

        static const char* scBtnPanes[] = {lbl_81696E30, lbl_81696E37};

        // clang-format off
        extern "C" char lbl_81654F98[] = "G_FocusBtnA";
        extern "C" char lbl_81654FA4[] = "G_FocusBtnB";
        extern "C" char lbl_81654FB0[] = "G_SelectBtnA";
        extern "C" char lbl_81654FBD[] = "G_SelectBtnB";
        extern "C" char lbl_81654FCA[] = "G_OnOffBtnA";
        extern "C" char lbl_81654FD6[] = "G_OnOffBtnB";
        extern "C" char lbl_81654FE2[] = "G_OutBtn";
        // clang-format on

        static const char* scAnimGroups[] = {
            lbl_81654F98, lbl_81654FA4, lbl_81654FB0, lbl_81654FBD,
            lbl_81654FCA, lbl_81654FD6, lbl_81654FE2,
        };

        // clang-format off
        extern "C" char lbl_81655008[] = "mn_SdcardMenuBanner_bc_FocusBtnA_off.brlan";
        extern "C" char lbl_81655033[] = "mn_SdcardMenuBanner_bc_FocusBtn_on.brlan";
        extern "C" char lbl_8165505C[] = "mn_SdcardMenuBanner_bc_SelectBtn_Ac.brlan";
        extern "C" char lbl_81655086[] = "mn_SdcardMenuBanner_bc_OffBtn.brlan";
        extern "C" char lbl_816550AA[] = "mn_SdcardMenuBanner_bc_OnBtn.brlan";
        extern "C" char lbl_816550CD[] = "mn_SdcardMenuBanner_bc_OutBtn.brlan";
        // clang-format on

        static const char* scAnimNames[] = {
            lbl_81655008, lbl_81655033, lbl_8165505C,
            lbl_81655086, lbl_816550AA, lbl_816550CD,
        };

        // clang-format off
        extern "C" char lbl_8165510C[] = "banner.brlan";
        extern "C" char lbl_81655119[] = "banner_Start.brlan";
        extern "C" char lbl_8165512C[] = "banner_Loop.brlan";
        // clang-format on

        static const char* scBannerAnims[] = {
            lbl_8165510C, lbl_81655119, lbl_8165512C,
        };

        static const char* scWidePanes[][4] = {
            {"Fre_a", "Fre_d", "Fre_i", "Fre_l"},
            {"Fre_e", "Fre_f", "Fre_g", "Fre_h"},
            {"Fre_b", "Fre_c", "Fre_j", "Fre_k"},
        };

        // clang-format off
        static const char* scBtnTextPanes[] = {"T_BtnA", "T_BtnB"};
        // clang-format on

        // clang-format off
        extern "C" char lbl_8165517C[] = "sdChanTtl.ash";
        extern "C" char lbl_8165518A[] = "mn_SdcardMenuBanner_bc.brlyt";
        extern "C" char lbl_816551A7[] = "Picture_04";
        extern "C" char lbl_816551B2[] = "Picture_05";
        extern "C" char lbl_816551BD[] = "Picture_06";
        extern "C" char lbl_816551C8[] = "mn_SdcardMenuBanner_a.brlyt";
        extern "C" char lbl_816551E4[] = "mn_SdcardMenuBanner_a_Ch_Fin.brlan";
        extern "C" char lbl_81655207[] = "mn_SdcardMenuBanner_a_T_Change.brlan";
        extern "C" char lbl_8165522C[] = "G_T_Change";
        extern "C" char lbl_81655237[] = "mn_SdcardMenuBanner_a_Bar.brlan";
        extern "C" char lbl_81655257[] = "mn_SdcardMenuBanner_a_Wait.brlan";
        extern "C" char lbl_81655278[] = "T_Comment_02";
        extern "C" char lbl_81655285[] = "Ch_Picture";
        extern "C" char lbl_81655290[] = "Chm_Picture";
        // clang-format on

        static const int scCaptureSize[][2] = {
            {0x80, 0x60},
            {0xB0, 0x60},
        };

        // clang-format off
        extern "C" void setEventHandler__Q33ipl5scene8SDButtonFPQ23gui12EventHandlerPQ23gui12EventHandler(
            ipl::scene::SDButton* button, ::gui::EventHandler* event);
        // clang-format on

        class SDChannelTitleBtnEvent : public ::gui::EventHandler {
        public:
            SDChannelTitleBtnEvent(SDChannelTitle* scene) : mpScene(scene) {}

        private:
            virtual void onEvent(u32 compId, u32 event, void* data);  // 0x08

            SDChannelTitle* mpScene;  // 0x0C
        };

        class SDChannelTitleEvent : public SDButtonEventHandlerBase {
        public:
            SDChannelTitleEvent(SDChannelTitle* scene) : mpScene(scene) {}

        private:
            virtual void onEventDerived(u32 compId, u32 event, const controller::Interface* con);  // 0x14

            SDChannelTitle* mpScene;  // 0x0C
        };

        SDChannelTitle::SDChannelTitle(EGG::Heap* heap, SDChannelSelect* chanSel)
            : FaderSceneBase(heap), mChanState(0), mLaunchKind(0), mChildSceneState(0), mWaitCounter(0), mGuiState(0),
              mbEnableStart(false), mpChanSelect(chanSel), mpThumbLayout(NULL), mpThumbHeap(NULL), mBannerSel(0),
              mpBannerLayout(NULL), mpSeHandle(NULL), mpSaveFile(NULL), mFadeoutTick(0),
              mpEvent(new SDChannelTitleEvent(this)), mpTmdView(NULL), mbTmdLoaded(false), unk_0x1A4(false),
              mCsState(0), mCsCalcFlag(0), mbLaunching(false), mCsFrame(0), mpCsFile(NULL), mCsHeapSel(0),
              mbCsThreadTerminated(false), mpCsHeap(NULL), mpSeHandle2(NULL) {
            mbHbmEnable = true;

            SDChannelObj* chanObj = chanSel->getChanObj(mChanPage = chanSel->mChanPage, mChanIndex = chanSel->mChanIndex);
            if (chanObj != NULL) {
                mTitleID = chanObj->getTitleID();
            }

            mChanCount = mpChanSelect->mChanCount;

            nw4r::math::VEC3 pos;
            nw4r::math::VEC3 pos2;
            SDChannelSelect::getChanPoint(&pos, mpChanSelect, mChanIndex);
            mChanPosX = pos.x;
            SDChannelSelect::getChanPoint(&pos2, mpChanSelect, mChanIndex);
            mChanPosY = pos2.y;
            mChanPosZ = 0.0f;

            mpBannerFiles[0] = NULL;
            mpBannerFiles[1] = NULL;
            mpBannerTasks[0] = NULL;
            mpBannerTasks[1] = NULL;

            for (int i = 0; i < 2; i++) {
                mBtnFocusCount[i] = 0;
            }

            setSceneParentFlags(SCN_PARENTFLAG_DRAW | SCN_PARENTFLAG_CALC);
            mpCsWorkHeap = mpChanSelect->mpCsHeap;
            mpRsoThread = mpChanSelect->mpRsoThread;
            memset(mCsAnims, 0, sizeof(mCsAnims));

            mpBannerHeap = EGG::ExpHeap::create(0x48000, getSceneHeap(), 6);
            mpThumbHeap = EGG::ExpHeap::create(0x8100, getSceneHeap(), 6);
        }

        SDChannelTitle::~SDChannelTitle() {
        }

        void SDChannelTitle::prepare() {
            mpLayoutFile = System::getNandManager()->readLayoutAsync(getSceneHeap(), lbl_8165517C, false);
        }

        void SDChannelTitle::create() {
            GXTexObj texObj[3];
            int i;
            int j;

            mpLayout = new layout::Object(getSceneHeap(), mpLayoutFile, "arc", lbl_8165518A);

            if (SCGetAspectRatio() == SC_ASPECT_RATIO_16x9) {
                mpLayout->FindPaneByName(lbl_816551A7)->GetMaterial()->GetTexture(&texObj[0], 0);
                mpLayout->FindPaneByName(lbl_816551B2)->GetMaterial()->GetTexture(&texObj[1], 0);
                mpLayout->FindPaneByName(lbl_816551BD)->GetMaterial()->GetTexture(&texObj[2], 0);

                for (i = 0; i < 3; i++) {
                    for (j = 0; j < 4; j++) {
                        mpLayout->FindPaneByName(scWidePanes[i][j])->GetMaterial()->SetTexture(0, texObj[i]);
                    }
                }
            }

            setMessage(mpLayout->FindPaneByName(scBtnTextPanes[0]), 0xA2, true);
            setMessage(mpLayout->FindPaneByName(scBtnTextPanes[1]), 2, true);

            mGuiState = 1;

            mpFocusAnimAOff = mpLayout->bindToGroup(scAnimNames[0], scAnimGroups[0], false, false);
            mpFocusAnimAOn = mpLayout->bindToGroup(scAnimNames[1], scAnimGroups[0], false, true);
            mpFocusAnimBOff = mpLayout->bindToGroup(scAnimNames[0], scAnimGroups[1], false, false);
            mpFocusAnimBOn = mpLayout->bindToGroup(scAnimNames[1], scAnimGroups[1], false, true);
            mpSelectAnimA = mpLayout->bindToGroup(scAnimNames[2], scAnimGroups[2], false, false);
            mpSelectAnimB = mpLayout->bindToGroup(scAnimNames[2], scAnimGroups[3], false, false);
            mpOffAnimA = mpLayout->bindToGroup(scAnimNames[3], scAnimGroups[4], false, false);
            mpOffAnimB = mpLayout->bindToGroup(scAnimNames[3], scAnimGroups[5], false, false);
            mpOnAnimA = mpLayout->bindToGroup(scAnimNames[4], scAnimGroups[4], false, false);
            mpOnAnimB = mpLayout->bindToGroup(scAnimNames[4], scAnimGroups[5], false, false);
            mpOutAnim = mpLayout->bindToGroup(scAnimNames[5], scAnimGroups[6], false, false);

            mpLayout->finishBinding();

            SDChannelTitleBtnEvent* btnEvent = new SDChannelTitleBtnEvent(this);

            mpPaneManager = new ipl::gui::PaneManager(btnEvent, mpLayout->getDrawInfo(), NULL, NULL);

            mpPaneManager->createLayoutScene(*mpLayout->getNW4RLyt());
            mpPaneManager->setAllComponentTriggerTarget(false);
            mpPaneManager->getPaneComponentByPane(mpLayout->FindPaneByName(scBtnPanes[0]))->setTriggerTarget(true);
            mpPaneManager->getPaneComponentByPane(mpLayout->FindPaneByName(scBtnPanes[1]))->setTriggerTarget(true);

            mpSubLayout = new layout::Object(getSceneHeap(), mpLayoutFile, "arc", lbl_816551C8);
            mpSubLayout->bind(lbl_816551E4, true);
            mpSubLayout->bindToGroup(lbl_81655207, lbl_8165522C, false, true);
            mpSubLayout->bindToGroup(lbl_81655237, "G_Prog", false, true);
            mpSubLayout->bindToGroup(lbl_81655257, "G_Wait", false, true);
            mpSubLayout->finishBinding();

            nw4r::lyt::TextBox* textPane = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(mpSubLayout->FindPaneByName(lbl_81655278));
            textPane->SetString(System::getMessage(0xAD), 0);

            createBanner();

            mpIntp = new math::HermiteIntp<f32>;
            mpIntp->init(0.0f, 255.0f, 28.0f, 0.0f, 0.0f, 0, 1.0f);
            mpIntp->setAnmType(0);

            mpCapture = new (System::getTreasureHeap(), 0x20) utility::Capture(
                System::getTreasureHeap(), 0, 0, System::getRenderModeObj()->fbWidth, System::getRenderModeObj()->efbHeight, GX_TF_RGB565);
            mpCaptureHeap = EGG::ExpHeap::create(0x20000, System::getMem2App(), 6);
            mpCapture2 = new (mpCaptureHeap, 0x20) utility::Capture(
                mpCaptureHeap, (System::getRenderModeObj()->fbWidth - scCaptureSize[SCGetAspectRatio()][0]) / 2,
                (System::getRenderModeObj()->efbHeight - scCaptureSize[SCGetAspectRatio()][1]) / 2,
                scCaptureSize[SCGetAspectRatio()][0], scCaptureSize[SCGetAspectRatio()][1], GX_TF_RGB565);

            mpSubLayout->FindPaneByName(lbl_81655285)->GetMaterial()->SetTexture(1, mpCapture2->getGXTex());
            mpSubLayout->FindPaneByName(lbl_81655290)->GetMaterial()->SetTexture(1, mpCapture2->getGXTex());

            mChanState = 2;
            mCsFrame = mCsFrameMax = 0x8CA0;

            resetTitleAnim();

            mpCsHeaps[0] = EGG::ExpHeap::create(0x80000, System::getMem2App(), 6);
            mpCsHeaps[1] = EGG::ExpHeap::create(0x80000, System::getMem2App(), 6);

            mSDMemory.create(getSceneHeap(), mpLayoutFile, mpChanSelect);
        }

        void SDChannelTitle::calcCommon() {
            mpPaneManager->calc();

            mpLayout->calc();

            if (mCsCalcFlag == 1) {
                calcChannelScript();
            }

            if (mChanState == 1 || mChanState == 0xD || mChanState == 4 || mChanState == 5) {
                if (!mbEnableStart && mpBannerAnims[1] != NULL && !mpBannerAnims[1]->isPlaying()) {
                    if (mpBannerAnims[2] != NULL) {
                        mpBannerAnims[2]->play();
                    } else if (mpBannerAnims[0] != NULL) {
                        mpBannerAnims[0]->play();
                    }
                    mpBannerAnims[1] = NULL;
                }
            }

            if (mChanState == 5 && !unk_0x1A4 && !mpSelectAnimB->isPlaying()) {
                mpFocusAnimBOff->play();
                unk_0x1A4 = true;
            }

            if (mpBannerLayout != NULL) {
                mpBannerLayout->calc();
            }
            if (mpThumbLayout != NULL) {
                mpThumbLayout->calc();
            }
            mpSubLayout->calc();
        }

        FaderSceneCommand SDChannelTitle::calcFadein() {
            if (mChanState == 2) {
                resetTitleAnim();
                return FADER_SCN_CONTINUE;
            } else if (!mpIntp->isPlaying()) {
                restartTitleAnim();

                SDButton* button = (SDButton*)System::getSceneManager()->getScene(0x24);
                setEventHandler__Q33ipl5scene8SDButtonFPQ23gui12EventHandlerPQ23gui12EventHandler(button, mpEvent);
                button->animation(0xD);
                button->animation(0xE);

                mChanState = 1;
                return FADER_SCN_NEXT;
            } else {
                mpIntp->calc();
                return FADER_SCN_CONTINUE;
            }
        }

        FaderSceneCommand SDChannelTitle::calcNormal() {
            switch (mChanState) {
                case 1:
                    calcNormalNormal();
                    break;
                case 4:
                    startChanSelectWork(mLaunchKind);
                    mChanState = 5;
                    break;
                case 8:
                    calcNormalChanRelease();
                    break;
                case 9:
                    calcNormalWait20();
                    break;
                case 10:
                    calcNormalButtonWait();
                    break;
                case 11:
                    calcNormalChildScene();
                    break;
                case 12:
                    calcNormalDialogResult();
                    break;
                case 13:
                    calcNormalCheckTmd();
                    break;
                case 14:
                    return FADER_SCN_CONTINUE;
                case 15:
                    calcNormalSelectDialog();
                    break;
                case 16:
                    calcNormalSetTitleId();
                    break;
                case 17:
                    SCSetTmpTitleID(mTitleID);
                    SCFlushAsync(NULL);
                    mChanState = 0x12;
                    break;
                case 18:
                    if (SCCheckStatus() != SC_STATUS_BUSY) {
                        mChanState = 0x15;
                    }
                    break;
                case 19:
                    calcNormalCheckStart();
                    break;
                case 20:
                    calcNormalStartChannel();
                    break;
                case 23:
                    calcNormalMemory();
                    break;
                case 21:
                    calcNormalMemoryWait();
                    break;
                case 22:
                    calcNormalLoadMeta();
                    break;
                case 24:
                    calcNormalBanner();
                    break;
                case 25:
                    calcNormalBannerEnd();
                    break;
                case 26:
                    calcNormalDialog();
                    break;
                case 27:
                    calcNormalFlushWait();
                    break;
                case 28:
                    calcNormalChanCheck();
                    break;
                case 29:
                    calcNormalWaitAnim();
                    break;
                case 30:
                    calcNormalResetGui();
                    break;
            }

            if (mChanState == 5) {
                mbLaunching = true;
                mWaitCounter++;
                System::getPointer()->setVisible(false);
                return (FaderSceneCommand)checkWaitEnd();
            }
            if (mChanState == 6 || mChanState == 7 || mChanState == 0x1F) {
                mbLaunching = true;
                return FADER_SCN_NEXT;
            }
            return FADER_SCN_CONTINUE;
        }

        // clang-format off
        extern "C" char lbl_81655318[] = "sound stopped\n";
        extern "C" char lbl_81655327[] = "NWC24 Scheduler stopped.\n";
        extern "C" char lbl_81655341[] = "Nand full! OSRebootSystem.\n";
        extern "C" char lbl_8165535D[] = "wait for WPAD\n";
        extern "C" char lbl_8165536C[] = "wait for BS2\n";
        extern "C" char lbl_8165537A[] = "NandSDWorker teminated.\n";
        extern "C" char lbl_81655393[] = "VI Black\n";
        extern "C" char lbl_8165539D[] = "sync sram\n";
        extern "C" char lbl_816553A8[] = "Create play recode\n";
        extern "C" char lbl_816553BC[] = "WIPL_BGM_MENU";
        // clang-format on

        void SDChannelTitle::initCalcFadeout() {
            SDButton* button = (SDButton*)System::getSceneManager()->getScene(0x24);
            if (mChanState == 5 || mChanState == 7 || mChanState == 0x1F) {
                System::getFader()->fadeOut();
                snd::getSystem()->stopAllSound(0x14);
                OSReport(lbl_81655318);
            } else if (mChanState == 6) {
                button->animation(0xF);
                button->animation(0x10);
            }
            setEventHandler__Q33ipl5scene8SDButtonFPQ23gui12EventHandlerPQ23gui12EventHandler(button, NULL);
        }

        FaderSceneCommand SDChannelTitle::calcFadeout() {
            FaderSceneCommand cmd = FADER_SCN_CONTINUE;
            if (mChanState == 5) {
                if (mFadeoutTick == 0 && !WPADGetStatus()) {
                    mFadeoutTick = (u32)OSGetTick();
                }

                if (System::getFader()->getStatus() == EGG::Fader::PREPARE_IN && System::isReceiveScheduleStopped()) {
                    if (System::getNwc24Manager() == NULL || System::getNwc24Manager()->isUnk0xA31()) {
                        OSReport(lbl_81655327);
                        NandSDWorker* worker = mpChanSelect->mpWorker;

                        if (mLaunchKind == 0x11) {
                            if (!nandwall::checkNandCapacityAppBootable()) {
                                OSReport(lbl_81655341);
                                doReboot();
                            }

                            for (;;) {
                                snd::getSystem()->calc();
                                System::getBS2Manager()->update();
                                VIWaitForRetrace();
                                if (mCsCalcFlag == 1) {
                                    calcChannelScript();
                                }
                                if (WPADGetStatus()) {
                                    OSReport(lbl_8165535D);
                                }
                                if (System::getBS2Manager()->getIPLState() != 8) {
                                    OSReport(lbl_8165536C);
                                }
                                if (WPADGetStatus()) {
                                    continue;
                                }
                                if (System::getBS2Manager()->getIPLState() != 8) {
                                    continue;
                                }
                                if (!System::getSaveData()->isFinished(mpSaveFile)) {
                                    continue;
                                }
                                if (mCsCalcFlag != 0 && mCsState != 4) {
                                    continue;
                                }
                                if (worker != NULL && worker->is_working()) {
                                    continue;
                                }
                                break;
                            }

                            if (worker != NULL) {
                                worker->terminate_async();
                                while (!worker->is_terminated()) {
                                    snd::getSystem()->calc();
                                    VIWaitForRetrace();
                                }
                                OSReport(lbl_8165537A);
                            }

                            delete mpSaveFile;

                            VISetBlack(true);
                            VIFlush();
                            VIWaitForRetrace();
                            OSReport(lbl_81655393);
                            while (!__OSSyncSram()) {
                                OSReport(lbl_8165539D);
                            }

                            SDChannelObj* chanObj = mpChanSelect->getChanObj(mChanPage, mChanIndex);
                            u64 titleId = chanObj->getTitleID();
                            wchar_t titleName[0x2A];
                            memcpy(&titleName[0], chanObj->getTitleName(0), 0x2A);
                            memcpy(&titleName[0x15], chanObj->getTitleName(1), 0x2A);
                            u8 makerCode[2];
                            makerCode[0] = ((u8*)&mTitleVersion)[0];
                            makerCode[1] = ((u8*)&mTitleVersion)[1];
                            __OSCreatePlayRecord(titleName, (char*)&titleId + 4, (char*)makerCode);
                            OSReport(lbl_816553A8);
                            BS2SetStateFlags();
                            OSReport("Launch\n");
                            __OSLaunchTitlevForSystem(titleId, 0, NULL);
                        } else {
                            math::VEC3 trans(0.0f, 0.0f, 0.0f);
                            math::VEC2 scale(1.0f, 1.0f);
                            utility::Graphics::setOrthoTrans(trans);
                            utility::Graphics::setOrthoScale(scale);
                        }

                        return FADER_SCN_NEXT;
                    }
                }
            } else if (mChanState == 6) {
                if (!mpIntp->isPlaying()) {
                    return FADER_SCN_NEXT;
                } else {
                    mpIntp->calc();
                }
            } else if (mChanState == 7 || mChanState == 0x1F) {
                if (System::getFader()->getStatus() == EGG::Fader::PREPARE_IN) {
                    math::VEC3 trans(0.0f, 0.0f, 0.0f);
                    utility::Graphics::setOrthoTrans(trans);
                    math::VEC2 scale(1.0f, 1.0f);
                    utility::Graphics::setOrthoScale(scale);
                    snd::getSystem()->initFx();
                    snd::getSystem()->startBGM(lbl_816553BC);
                    return FADER_SCN_NEXT;
                }
            }
            return cmd;
        }

        void SDChannelTitle::draw() {
            if (mChanState == 2) {
                return;
            }

            scene::Manager* manager = System::getSceneManager();
            if (manager->onDrawLayer(1)) {
                if (mChanState == 3 || mChanState == 6) {
                    utility::Graphics::setOrtho(0);
                    nw4r::ut::Rect rect(mChanPosX - mpChanSelect->mChanSizeX, mChanPosY + mpChanSelect->mChanSizeY,
                                        mChanPosX + mpChanSelect->mChanSizeX, mChanPosY - mpChanSelect->mChanSizeY);
                    GXColor textureColor = {255, 255, 255, 0};
                    textureColor.a = (u8)mpIntp->get();
                    utility::Graphics::drawTexture(rect, mpCapture->getGXTex(), textureColor, 1, utility::Graphics::ORI_NONE);
                    GXColor polygonColor = {0, 0, 0, 0};
                    polygonColor.a = (u8)mpIntp->get();
                    drawBorder(rect, polygonColor);
                } else {
                    if (mpThumbLayout != NULL) {
                        utility::Graphics::setOrthoProjection(0);
                        mpThumbLayout->draw();
                        mpCapture2->capture(0);
                    }
                    utility::Graphics::setDefaultOrtho(0);
                    if (mpBannerLayout != NULL) {
                        mpBannerLayout->draw();
                    } else {
                        mpSubLayout->draw();
                    }
                    mpLayout->draw();
                    if (mChanState == 0x17) {
                        mSDMemory.draw();
                    }
                }
            } else if (manager->onDrawLayer(0)) {
                if (mChanState == 3 || mChanState == 6) {
                    utility::Graphics::setDefaultOrtho(0);
                    if (mpBannerLayout != NULL) {
                        mpBannerLayout->draw();
                    } else {
                        mpSubLayout->draw();
                    }
                    mpLayout->draw();
                    mpCapture->capture(1);
                }
            }
        }

        void SDChannelTitle::destroy() {
            if (mpBannerFiles[0] != NULL) {
                delete mpBannerFiles[0];
            }
            if (mpBannerFiles[1] != NULL) {
                delete mpBannerFiles[1];
            }
            if (mpBannerLayout != NULL) {
                mpBannerLayout->destroyHeap();
            }
            if (mpBannerTasks[0] != NULL) {
                delete mpBannerTasks[0];
            }
            if (mpBannerTasks[1] != NULL) {
                delete mpBannerTasks[1];
            }
            delete mpCapture;
            if (mpCsFile != NULL) {
                delete mpCsFile;
            }
            mpCsHeaps[0]->destroy();
            mpCsHeaps[1]->destroy();
            mpBannerHeap->destroy();
            if (mpThumbLayout != NULL) {
                mpThumbLayout->destroyHeap();
            }
            mpThumbHeap->destroy();
            delete mpCapture2;
            mpCaptureHeap->destroy();
        }

        BOOL SDChannelTitle::isResetAcceptable() {
            if (mSDMemory.unk_0x29D0 != 0) {
                return mbHbmEnable;
            }
            return FALSE;
        }

        void SDChannelTitle::startResetting() {
            snd::getSystem()->resetAllSound();
        }

        void SDChannelTitle::createBanner() {
            createBannerLayout();
            if (mpBannerLayout != NULL) {
                mpBannerLayout->finishBinding();
            }
        }

        // clang-format off
        extern "C" char lbl_816553CA[] = "banner.brlyt";
        extern "C" char lbl_816553D7[] = "icon.brlyt";
        extern "C" char lbl_816553E2[] = "icon.brlan";
        extern "C" char lbl_816553ED[] = "icon_Whole.brlan";
        // clang-format on

        void SDChannelTitle::createBannerLayout() {
            if (mpThumbLayout != NULL) {
                mpThumbLayout->destroyHeap();
                mpThumbLayout = NULL;
            }

            if (mpBannerFiles[mBannerSel] != NULL && mpBannerFiles[mBannerSel]->checkData() == 1) {
                mpBannerLayout = layout::Object::create(mpBannerHeap, 0x40000, mpBannerFiles[mBannerSel], "arc", lbl_816553CA);
                SDChannelObj::setLangPane(mpBannerLayout);
                bindLanguageAnims();
            } else {
                mpBannerLayout = NULL;
                for (int i = 0; i < 3; i++) {
                    mpBannerAnims[i] = NULL;
                }
                createThumbnailLayout();
            }
        }

        void SDChannelTitle::createThumbnailLayout() {
            SDChannelObj* chanObj = mpChanSelect->getChanObj(mChanPage, mChanIndex);
            if (chanObj == NULL) {
                return;
            }

            mpThumbLayout = layout::Object::create(mpThumbHeap, 0x8000, chanObj->allocThumbBuffer(), "arc", lbl_816553D7);
            SDChannelObj::setLangPane(mpThumbLayout);

            if (mpThumbLayout->searchFile(lbl_816553E2)) {
                mpThumbLayout->bind(lbl_816553E2, true)->play();
            } else if (mpThumbLayout->searchFile(lbl_816553ED)) {
                mpThumbLayout->bind(lbl_816553ED, true)->play();
            }

            if (chanObj->getChanType() == 0) {
                nw4r::lyt::TextBox* textPane = (nw4r::lyt::TextBox*)mpSubLayout->GetRootPane()->FindPaneByName("T_title", true);
                textPane->SetString(chanObj->getTitleName(0), 0);
            } else {
                nw4r::lyt::TextBox* textPane = (nw4r::lyt::TextBox*)mpSubLayout->GetRootPane()->FindPaneByName("T_title", true);
                textPane->SetString(scUnknownTitle, 0);
            }

            mpSubLayout->getAnim(0)->stop();
            mpSubLayout->getAnim(0)->initAnmFrame();
            mpSubLayout->calc();
        }

        // clang-format off
        extern "C" char lbl_816553FE[] = "WSD_SELECT";
        // clang-format on

        void SDChannelTitle::calcNormalNormal() {
            SDButton* button = (SDButton*)System::getSceneManager()->getScene(0x24);
            if (button != NULL && button->isActive()) {
                button->update();
            }

            if (mChanState != 1) {
                return;
            }

            u32 selState = mpChanSelect->mSelState;
            if (selState == 1 || selState == 2) {
                mChanState = 10;
                calcNormalButtonWait();
                return;
            }

            controller::Interface* master = System::getMasterController();
            int page;
            int index;
            if (master->down(controller::BTN_NEXT_LEFT)) {
                mpChanSelect->getSelectChan(1, &page, &index);
                selectChannel(page, index);
                snd::getSystem()->startSE(lbl_816553FE);
            } else if (master->down(controller::BTN_NEXT_RIGHT)) {
                mpChanSelect->getSelectChan(0, &page, &index);
                selectChannel(page, index);
                snd::getSystem()->startSE(lbl_816553FE);
            } else {
                mpPaneManager->update();

                if (mGuiState == 0) {
                    mGuiState = 1;
                } else if (mGuiState == 1) {
                    mGuiState = 2;
                }
            }
        }

        void SDChannelTitle::calcNormalChanRelease() {
            if ((u32)(mpChanSelect->mSelState - 1) <= 1) {
                mChanState = 1;
                return;
            }

            SDChannelObj* chanObj = mpChanSelect->getChanObj(mChanPage, mChanIndex);
            mBannerTimer++;

            if (mpBannerFiles[1 - mBannerSel] != NULL && !mpBannerFiles[1 - mBannerSel]->isFinished()) {
                return;
            }
            if (mpBannerTasks[1 - mBannerSel] != NULL && !mpBannerTasks[1 - mBannerSel]->isFinished()) {
                return;
            }
            if (!chanObj->isValid()) {
                return;
            }
            if (mBannerTimer <= 10) {
                return;
            }
            if (mCsCalcFlag != 0 && mCsState != 4) {
                return;
            }

            if (mpBannerFiles[mBannerSel] != NULL) {
                delete mpBannerFiles[mBannerSel];
                if (mpBannerLayout != NULL) {
                    mpBannerLayout->destroyHeap();
                }
            }
            mpBannerFiles[mBannerSel] = NULL;
            mpBannerLayout = NULL;
            mpCsHeaps[mCsHeapSel]->freeAll();
            mCsHeapSel ^= 1;
            snd::getSystem()->stopBannerSound(0);
            snd::getSystem()->stopSE(mpSeHandle, 0);

            if (mpBannerTasks[mBannerSel] != NULL) {
                delete mpBannerTasks[mBannerSel];
            }
            mpBannerTasks[mBannerSel] = NULL;
            mBannerSel = 1 - mBannerSel;

            createBanner();
            resetBtnPane();
            mChanState = 9;
        }

        void SDChannelTitle::calcNormalWait20() {
            mBannerTimer++;
            if (mBannerTimer > 0x14) {
                restartTitleAnim();
                mChanState = 1;
            }
        }

        void SDChannelTitle::calcNormalChildScene() {
            ParentalDialog* dialog = (ParentalDialog*)System::getSceneManager()->getScene(SCENE_PARENTAL_DIALOG);
            if (dialog == NULL && System::getSceneManager()->getReservedScene() == NULL) {
                if (mChildSceneState == 1) {
                    if (mLaunchKind == 0x12) {
                        reserveAllSceneDestruction(0x12, (void*)1);
                        mChanState = 7;
                    } else {
                        mChanState = mbSDWorkDone ? 0x19 : 0xF;
                    }
                } else {
                    if (mbSDWorkDone) {
                        mChanState = 0x1D;
                    } else {
                        mpFocusAnimBOff->play();
                        ((SDButton*)System::getSceneManager()->getScene(SCENE_SD_BUTTON))->animation(0xD);
                        ((SDButton*)System::getSceneManager()->getScene(SCENE_SD_BUTTON))->animation(0xE);

                        for (int i = 0; i < 2; i++) {
                            mBtnFocusCount[i] = 0;
                            mpPaneManager->initPane(mpLayout->GetRootPane()->FindPaneByName(scBtnPanes[i], true));
                        }

                        System::startReceiveSchedule();
                        mChanState = 1;
                    }
                }
            } else if (dialog != NULL) {
                switch (dialog->getResult()) {
                    case ParentalDialog::RESULT_SUCCESS:
                        if (mChildSceneState == 0) {
                            stopControllers(mLaunchKind);
                            mChildSceneState = 1;
                        }
                        break;
                    case ParentalDialog::RESULT_OVER_ATTEMPTS:
                    case ParentalDialog::RESULT_CANCELLED:
                        mChildSceneState = 2;
                        break;
                }
            }
        }

        void SDChannelTitle::calcNormalDialogResult() {
            switch (System::getDialog()->getLastResult()) {
                case 2:
                    if (mbSDWorkDone) {
                        mChanState = 0x1D;
                    } else {
                        ((SDButton*)System::getSceneManager()->getScene(SCENE_SD_BUTTON))->animation(0xD);
                        ((SDButton*)System::getSceneManager()->getScene(SCENE_SD_BUTTON))->animation(0xE);
                        mpFocusAnimBOff->play();

                        for (int i = 0; i < 2; i++) {
                            mBtnFocusCount[i] = 0;
                            mpPaneManager->initPane(mpLayout->GetRootPane()->FindPaneByName(scBtnPanes[i], true));
                        }

                        System::startReceiveSchedule();
                        mChanState = 1;
                    }
                    break;
                case 1:
                    if (isParentalSet()) {
                        startDialog(1);
                    } else {
                        reserveAllSceneDestruction(0x12, (void*)1);
                        mChanState = 7;
                    }
                    break;
            }
        }

        void SDChannelTitle::calcNormalCheckStart() {
            if (mpChanSelect->mpWorker->is_working()) {
                return;
            }
            if (mpSubLayout->isPlaying(0)) {
                return;
            }
            if (mpSelectAnimB->isPlaying()) {
                return;
            }

            layout::Animator* animator = mpSubLayout->getAnim(1);
            animator->setAnmType(0);
            animator = mpSubLayout->getAnim(1);
            animator->initAnmFrame();
            animator = mpSubLayout->getAnim(1);
            animator->play();

            mpFocusAnimBOff->initAnmFrame();
            mpFocusAnimBOff->play();

            mpOutAnim->setAnmType(0);
            mpOutAnim->initAnmFrame();
            mpOutAnim->play();

            if (mpChanSelect->getChanObj(mChanPage, mChanIndex)->getChanType() == 3) {
                mChanState = 0x1A;
                mErrMsgId = 0xAF;
            } else if (mpChanSelect->startNandCheck(mTitleID, &mNandFree)) {
                mChanState = 0x14;
            } else {
                mChanState = 0x1A;
                mErrMsgId = 0xAE;
            }
        }

        void SDChannelTitle::calcNormalStartChannel() {
            if (mpChanSelect->mpWorker->is_working()) {
                return;
            }
            if (mpSubLayout->isPlaying(1)) {
                return;
            }

            int result = mpChanSelect->mpWorker->get_async_result();
            if (result == 0 || result == -6) {
                if (mpChanSelect->getNandFree(&mNandFree)) {
                    mChanState = 0xF;
                    return;
                }

                NandSDWorker::AppBlocksInfo needed;
                NandSDWorker::AppBlocksInfo freeArea;
                if (mNandFree.bytes < 0x3800000) {
                    needed.bytes = 0x3800000;
                    needed.blocks = mNandFree.blocks;
                    freeArea = mNandFree;
                } else {
                    freeArea = mNandFree;
                    needed = freeArea;
                }

                NandSDWorker::AppBlocksInfo neededArg = needed;
                NandSDWorker::AppBlocksInfo freeAreaArg = freeArea;
                mSDMemory.startCheck(&freeAreaArg, &neededArg);
                mSDMemory.waitEnd();
                mbHbmEnable = true;
                System::getHomeButtonMenu()->enable();
                mChanState = 0x17;
            } else {
                if (result == -15 || result == -16) {
                    mChanState = 0x1A;
                    mErrMsgId = 0xAF;
                } else if (result == -0x10) {
                    mChanState = 0x1A;
                    mErrMsgId = 0xC7;
                } else {
                    mChanState = 0x1A;
                    mErrMsgId = 0xAE;
                }
            }
        }

        void SDChannelTitle::calcNormalMemory() {
            if (!mSDMemory.waitEnd()) {
                return;
            }

            switch (mSDMemory.mState) {
                case 4:
                    reserveAllSceneDestruction(0x15, (void*)2);
                    mChanState = 0x1F;
                    break;
                case 1:
                case 2:
                case 3:
                case 5:
                case 6:
                    mbHbmEnable = false;
                    System::getHomeButtonMenu()->disable();
                    mChanState = 0x1D;
                    break;
                default:
                    mbHbmEnable = false;
                    System::getHomeButtonMenu()->disable();
                    mChanState = 0xF;
                    break;
            }
        }

        // clang-format off
        extern "C" char lbl_81655409[] = "WIPL_SE_COPYING";
        // clang-format on

        void SDChannelTitle::calcNormalSelectDialog() {
            if (mpChanSelect->mpWorker->is_working()) {
                return;
            }

            if (mbSDWorkDone) {
                if (!mpSubLayout->isPlaying(3)) {
                    layout::Animator* animator = mpSubLayout->getAnim(3);
                    animator->play();
                    mpSeHandle2 = snd::getSystem()->startSE(lbl_81655409);
                }
            }

            u64 tmpId = SCGetTmpTitleID();
            if (tmpId != 0 && mTitleID != tmpId) {
                if (System::isReceiveScheduleStopped()) {
                    if (mpChanSelect->startNandAsync(tmpId, 1)) {
                        mChanState = 0x10;
                    } else {
                        mChanState = 0x1A;
                        mErrMsgId = 0xAE;
                    }
                }
            } else if (mbSDWorkDone) {
                mChanState = 0x11;
            } else {
                mChanState = 0x18;
            }
        }

        void SDChannelTitle::calcNormalSetTitleId() {
            if (mpChanSelect->mpWorker->is_working()) {
                return;
            }

            SCSetTmpTitleID(0);
            System::getChannelManager()->fn_8133A9F0();

            if (mpChanSelect->mpWorker->get_async_result() == 0) {
                if (mbSDWorkDone) {
                    mChanState = 0x11;
                } else {
                    mChanState = 0x18;
                }
            } else {
                SCFlushAsync(NULL);
                mChanState = 0x1A;
                mErrMsgId = 0xAE;
            }
        }

        void SDChannelTitle::calcNormalMemoryWait() {
            if (mpChanSelect->mpWorker->is_working()) {
                return;
            }

            if (mpChanSelect->isAsyncDone((u32)mTitleID)) {
                mChanState = 0x16;
            } else {
                mChanState = 0x1A;
                mErrMsgId = 0xAE;
            }
        }

        // clang-format off
        extern "C" char lbl_81655419[] = "WIPL_SE_COPY_FINISH";
        // clang-format on

        void SDChannelTitle::calcNormalLoadMeta() {
            layout::Animator* animator = mpSubLayout->getAnim(2);
            animator->initAnmFrame(NandSDWorker::s_completion_pct);

            if (mpChanSelect->mpWorker->is_working()) {
                return;
            }

            int result = mpChanSelect->mpWorker->get_async_result();
            if (result == 0 || result == -6) {
                System::getChannelManager()->loadTmpMetaHeader(mTitleID);
                animator = mpSubLayout->getAnim(3);
                animator->stop();
                snd::getSystem()->stopSE(mpSeHandle2, 0);
                mpSeHandle2 = NULL;
                snd::getSystem()->startSE(lbl_81655419);
                System::getTask1()->request(getTmdView, this, NULL);
                mChanState = 0x18;
            } else {
                SCSetTmpTitleID(0);
                SCFlushAsync(NULL);
                mChanState = 0x1A;
                if (result == -0xF) {
                    mErrMsgId = 0xAF;
                } else if (result == -0x10) {
                    mErrMsgId = 0xC7;
                } else {
                    mErrMsgId = 0xAE;
                }
            }
        }

        void SDChannelTitle::calcNormalDialog() {
            layout::Animator* animator = mpSubLayout->getAnim(3);
            animator->stop();
            snd::getSystem()->stopSE(mpSeHandle2, 0);
            mpSeHandle2 = NULL;
            System::getDialog()->callBtn1(mErrMsgId, 0x2E);
            mChanState = 0x1B;
        }

        void SDChannelTitle::calcNormalFlushWait() {
            if (SCCheckStatus() != SC_STATUS_BUSY && System::getDialog()->getLastResult() != DialogWindow::RESULT_NONE) {
                mChanState = 0x1D;
            }
        }

        void SDChannelTitle::calcNormalWaitAnim() {
            if (mpSubLayout->isPlaying(1)) {
                return;
            }
            if (mpFocusAnimBOff->isPlaying()) {
                return;
            }
            if (mpOutAnim->isPlaying()) {
                return;
            }

            mbHbmEnable = true;
            System::getHomeButtonMenu()->enable();

            layout::Animator* animator = mpSubLayout->getAnim(1);
            animator->setAnmType(1);
            animator = mpSubLayout->getAnim(1);
            animator->initAnmFrame();
            animator = mpSubLayout->getAnim(1);
            animator->play();

            mpOutAnim->setAnmType(1);
            mpOutAnim->initAnmFrame();
            mpOutAnim->play();

            mpFocusAnimBOff->initAnmFrame();
            mpFocusAnimBOff->play();

            ((SDButton*)System::getSceneManager()->getScene(SCENE_SD_BUTTON))->animation(0xD);
            ((SDButton*)System::getSceneManager()->getScene(SCENE_SD_BUTTON))->animation(0xE);

            System::startReceiveSchedule();
            mChanState = 0x1E;
        }

        void SDChannelTitle::calcNormalResetGui() {
            if (mpSubLayout->isPlaying(1)) {
                return;
            }
            if (mpOutAnim->isPlaying()) {
                return;
            }

            for (int i = 0; i < 2; i++) {
                mBtnFocusCount[i] = 0;
                mpPaneManager->initPane(mpLayout->GetRootPane()->FindPaneByName(scBtnPanes[i], true));
            }

            mChanState = 1;
        }

        void SDChannelTitle::calcNormalBanner() {
            if (!System::getChannelManager()->isLoadedTmp()) {
                int index;
                int page;
                if (System::getChannelManager()->hasChannel(mTitleID, &index, &page) == 0) {
                    return;
                }
            }

            mpBannerFiles[mBannerSel] = createNandTask(mTitleID, &mpBannerTasks[mBannerSel]);
            if (mbSDWorkDone) {
                mChanState = 0xD;
            } else {
                mChanState = 0x19;
            }
        }

        void SDChannelTitle::calcNormalBannerEnd() {
            if (mpBannerFiles[mBannerSel] != NULL && !mpBannerFiles[mBannerSel]->isFinished()) {
                return;
            }

            releaseChannel(mTitleID);
            createBanner();
            mChanState = 4;
            restartTitleAnim();
        }

        void SDChannelTitle::calcNormalChanCheck() {
            if ((u32)(mpChanSelect->mSelState - 1) <= 1) {
                mChanState = 1;
                return;
            }

            SDChannelObj* chanObj = mpChanSelect->getChanObj(mChanPage, mChanIndex);
            if (chanObj->isValid()) {
                setTitleID(chanObj);
            }
        }

        void SDChannelTitle::calcNormalCheckTmd() {
            if (!mbTmdLoaded) {
                return;
            }

            if (!System::getChannelManager()->fn_8133A678(mTitleID) && !utility::ESMisc::CheckTmdCountryCode(mpTmdView)) {
                System::getErrorHandler()->set(ErrorHandler::DEFAULT, 3, NULL, 0, -1);
            }

            mTitleVersion = mpTmdView->head.groupId;
            if (!isNetEnable(mTitleID)) {
                startDialog2(0);
                mLaunchKind = 0x12;
            } else {
                if (checkParentalControl(mpTmdView)) {
                    stopControllers(mLaunchKind);
                    if (mbSDWorkDone) {
                        mChanState = 0x19;
                    } else {
                        mChanState = 0xF;
                    }
                } else {
                    startDialog(0);
                }
            }

            if (mpTmdView != NULL) {
                mpBannerHeap->free(mpTmdView);
            }
        }

        BOOL SDChannelTitle::resetTitleAnim() {
            if (!mpChanSelect->isAnyChanMoving()) {
                return false;
            }
            mpIntp->play();
            mChanState = 3;
            return true;
        }

        // clang-format off
        extern "C" char lbl_8165542D[] = "WIPL_SE_CH_UNSELECT";
        // clang-format on

        void SDChannelTitle::calcNormalButtonWait() {
            if (mCsCalcFlag != 0 && mCsState != 4) {
                mbLaunching = true;
                return;
            }
            if (!mpChanSelect->fn_813E05C0(mChanPage)) {
                return;
            }
            mpChanSelect->fn_813E0624(mChanPage, mChanIndex);

            mpIntp->init(0.0f, 255.0f, 28.0f, 0.0f, 0.0f, 0, 1.0f);
            mpIntp->setAnmType(1);
            mpIntp->play();

            mChanState = 6;
            snd::getSystem()->startSE(lbl_8165542D);
            if (snd::getBannerPlayer()->isStarted()) {
                snd::getSystem()->stopBannerSound(0x1C);
            }
            if (mpSeHandle != NULL && mpSeHandle->IsAttachedSound()) {
                snd::getSystem()->stopSE(mpSeHandle, 0x1C);
            }
        }

        void SDChannelTitle::releaseChannel(u64 titleId) {
            if (!System::isSafeMode()) {
                if (mCsCalcFlag != 0) {
                    if (mpCsFile != NULL) {
                        delete mpCsFile;
                    }
                    mpCsFile = NULL;
                }
                if (System::getChannelManager()->fn_8133A57C(titleId)) {
                    mpCsFile = System::getChannelManager()->fn_8133A924(mpCsWorkHeap, titleId);
                    mbCsThreadTerminated = false;
                    mCsCalcFlag = 1;
                    mCsState = 1;
                } else {
                    mCsCalcFlag = 0;
                    mCsState = 0;
                }
            }
        }

        void SDChannelTitle::calcChannelScript() {
            if (mCsCalcFlag != 1) {
                return;
            }
            if (mChanState == 2 || mChanState == 3 || mChanState == 9) {
                return;
            }

            switch (mCsState) {
                case 0:
                    initChannelScript();
                    break;
                case 1:
                    createChannelScript();
                    break;
                case 2:
                    System::getCSManager()->calc();
                    if (mpRsoThread->IsThreadTerminated()) {
                        if (System::getCSManager()->getAltSoundState() == 1) {
                            startBannerSound();
                            System::getCSManager()->setAltSoundState(0);
                        }
                        System::getCSManager()->finish();
                        mCsState = 3;
                    }
                    break;
                case 3:
                    destroyChannelScript();
                    break;
            }
        }

        void SDChannelTitle::initChannelScript() {
            if (mbLaunching) {
                mbLaunching = false;
                mCsFrame = 0;
                mCsState = 4;
            } else {
                mCsFrame++;
                if (mCsFrame > mCsFrameMax) {
                    mCsState = 1;
                    mCsHeapSel ^= 1;
                }
                if (System::getChannelManager()->fn_8133A634(mTitleID)) {
                    if (mCsFrame == mCsFrameMax - 0xF0) {
                        snd::getSystem()->stopBannerSound(0xB4);
                    }
                }
            }
        }

        void SDChannelTitle::createChannelScript() {
            if (!mpCsFile->isFinished()) {
                return;
            }

            if (mpCsFile->checkData() != 1 && mpCsFile->checkData() != 0) {
                mCsFrame = 0;
                mbCsThreadTerminated = true;
                mCsState = 0;
                return;
            }

            if (mpCsHeap == NULL) {
                mpCsHeap = EGG::ExpHeap::create(-1, mpCsWorkHeap, 0);
            }

            System::getCSManager()->create(mpCsHeap);

            channel::ChannelScriptManager::CSData data = {NULL, NULL, NULL, 0, false, false, true};
            data.heap = mpCsHeaps[mCsHeapSel];
            data.layout = mpBannerLayout;
            data.anims = mCsAnims;
            data.titleId = mTitleID;
            data.threadTerminated = mbCsThreadTerminated;
            if (System::getNwc24ManagerForce() == NULL || !System::getNwc24ManagerForce()->isNewMessageThere((u32)data.titleId)) {
                data.unk_0x1A = false;
            }

            System::getCSManager()->setData(data);
            if (!System::getCSManager()->init(mpCsFile, mpRsoThread)) {
                mCsState = 3;
            } else {
                mCsState = 2;
            }
        }

        void SDChannelTitle::destroyChannelScript() {
            mbCsThreadTerminated = true;
            System::getCSManager()->destroy();
            mCsFrame = 0;
            mpCsHeaps[1 - mCsHeapSel]->freeAll();
            mpCsHeap->destroy();
            mpCsHeap = NULL;
            mCsState = 0;
        }

        // clang-format off
        extern "C" char lbl_81655441[] = "WIPL_ME_SD_BANNER";
        // clang-format on

        void SDChannelTitle::restartTitleAnim() {
            if (mpBannerAnims[1] != NULL) {
                mpBannerAnims[1]->initFrame();
                mpBannerAnims[1]->play();
                mbEnableStart = false;
            } else if (mpBannerAnims[2] != NULL) {
                mpBannerAnims[2]->initFrame();
                mpBannerAnims[2]->play();
            } else if (mpBannerAnims[0] != NULL) {
                mpBannerAnims[0]->initFrame();
                mpBannerAnims[0]->play();
            }

            if (mChanState == 6) {
                return;
            }
            if (!System::getChannelManager()->fn_8133A634(mTitleID) || mCsCalcFlag == 0) {
                startBannerSound();
            }

            if (mpBannerLayout == NULL) {
                layout::Animator* animator = mpSubLayout->getAnim(0);
                animator->initAnmFrame();
                animator = mpSubLayout->getAnim(0);
                animator->play();
                mpSeHandle = snd::getSystem()->startSE(lbl_81655441);
            }
        }

        void SDChannelTitle::startBannerSound() {
            if (mpBannerTasks[mBannerSel] != NULL && mpBannerTasks[mBannerSel]->checkData() == 1) {
                void* sndData = mpBannerTasks[mBannerSel]->getBuffer();
                u32 sndLen = System::getChannelManager()->fn_8133A5B8(mTitleID);
                snd::getSystem()->startBannerSound(sndData, sndLen, false);
            }
        }

        void SDChannelTitle::bindLanguageAnims() {
            bindBannerAnims();
            if (mCsCalcFlag != 0) {
                memset(mCsAnims, 0, sizeof(mCsAnims));
                bindRsoAnims(mpBannerLayout, mCsAnims, "banner");
            }
        }

        // clang-format off
        extern "C" char lbl_81655453[] = "%s_Rso%d.brlan";
        // clang-format on

        void SDChannelTitle::bindRsoAnims(layout::Object* layoutObj, layout::Animator** anims, const char* prefix) {
            char fileName[0x40];
            char groupName[0x40];
            int found;

            for (int i = 0; i < 0x10; i++) {
                sprintf(fileName, lbl_81655453, prefix, i);
                if (layoutObj->searchFile(fileName) == NULL) {
                    continue;
                }

                sprintf(groupName, "Rso%d", i);
                found = 0;
                for (nw4r::lyt::GroupList::Iterator it = layoutObj->GetGroupList().GetBeginIter(); it != layoutObj->GetGroupList().GetEndIter();
                     it++) {
                    if (strcmp(it->GetName(), groupName) == 0) {
                        anims[i] = layoutObj->bindToGroup(fileName, groupName, false, false);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    anims[i] = layoutObj->bind(fileName, false);
                }
            }
        }

        void SDChannelTitle::bindBannerAnims() {
            for (int i = 0; i < 3; i++) {
                if (mpBannerLayout->searchFile(scBannerAnims[i]) != NULL) {
                    if (i == 0) {
                        mpBannerAnims[i] = mpBannerLayout->bind(scBannerAnims[i], true);
                        mpBannerAnims[i]->setAnmType(ANIM_TYPE_LOOP);
                    } else if (i == 1) {
                        mpBannerAnims[i] = mpBannerLayout->bind(scBannerAnims[i], true);
                        mpBannerAnims[i]->setAnmType(ANIM_TYPE_FORWARD);
                    } else {
                        if (mpBannerAnims[1] == NULL) {
                            mpBannerAnims[i] = mpBannerLayout->bind(scBannerAnims[i], true);
                        } else {
                            mpBannerAnims[i] = mpBannerLayout->bind(scBannerAnims[i], false);
                        }
                        mpBannerAnims[i]->setAnmType(ANIM_TYPE_LOOP);
                    }
                } else {
                    mpBannerAnims[i] = NULL;
                }
            }
        }

        bool SDChannelTitle::isNetEnable(u64 titleId) {
            if (System::getChannelManager()->fn_8133A5F0(titleId) == 0) {
                return true;
            }
            if (ncd::NCDSetting::getConnectEnableFlag()) {
                return true;
            }
            return false;
        }

        bool SDChannelTitle::isParentalSet() {
            SCParentalControlsInfo pcInfo;
            if (SCGetParentalControl(&pcInfo)) {
                if (pcInfo.enable & SC_PARENTAL_FLAG_ENABLED) {
                    return true;
                }
            }
            return false;
        }

        void SDChannelTitle::startDialog(int kind) {
            System::getHomeButtonMenu()->enable();
            mbHbmEnable = true;

            SDButton* button = (SDButton*)System::getSceneManager()->getScene(0x24);
            if (button->mbArrowVisible[SDButton::ARROW_BTN_LEFT]) {
                button->animation(0xF);
                button->animation(0x10);
            }

            createChildScene(SCENE_PARENTAL_DIALOG, this, NULL, (void*)kind);
            mChildSceneState = 0;
            mChanState = 0xB;
        }

        void SDChannelTitle::selectChannel(int page, int index) {
            SDChannelObj* chanObj = NULL;
            if (mpThumbLayout != NULL) {
                chanObj = mpChanSelect->getChanObj(mChanPage, mChanIndex);
            }

            mChanPage = page;
            mChanIndex = index;
            mpChanSelect->setSelectChan(page, index);

            chanObj = mpChanSelect->getChanObj(mChanPage, mChanIndex);

            nw4r::math::VEC3 pos;
            SDChannelSelect::getChanPoint(&pos, mpChanSelect, mChanIndex);
            mChanPosX = pos.x;
            SDChannelSelect::getChanPoint(&pos, mpChanSelect, mChanIndex);
            mChanPosY = pos.y;

            if (chanObj->isValid()) {
                setTitleID(chanObj);
            } else {
                mChanState = 0x1C;
            }
        }

        void SDChannelTitle::setTitleID(SDChannelObj* chanObj) {
            mTitleID = chanObj->getTitleID();
            if (mCsCalcFlag != 0) {
                mbLaunching = true;
            }
            mBannerTimer = 0;
            mChanState = 8;
        }

        void SDChannelTitle::launchChannel() {
            mChildSceneState = 0;
            unk_0x1A4 = false;

            SDButton* button = (SDButton*)System::getSceneManager()->getScene(0x24);
            button->animation(0xF);
            button->animation(0x10);

            if (mpBannerFiles[mBannerSel] != NULL) {
                delete mpBannerFiles[mBannerSel];
            }
            if (mpBannerTasks[mBannerSel] != NULL) {
                delete mpBannerTasks[mBannerSel];
            }
            if (mpBannerLayout != NULL) {
                mpBannerLayout->destroyHeap();
            }
            mpBannerFiles[mBannerSel] = NULL;
            mpBannerLayout = NULL;
            mpBannerTasks[mBannerSel] = NULL;

            int page;
            int index;
            BOOL hasChan = System::getChannelManager()->hasChannel(mTitleID, &page, &index) != 0;
            BOOL tmpLoaded = SCGetTmpTitleID() == mTitleID && System::getChannelManager()->isLoadedTmp();

            mLaunchKind = 0x11;
            mbTmdLoaded = false;
            mTitleVersion = 0;
            mbHbmEnable = false;
            System::getHomeButtonMenu()->disable();
            System::stopReceiveSchedule();

            if (hasChan || tmpLoaded) {
                System::getTask1()->request(getTmdView, this, NULL);
                mbSDWorkDone = false;
                mChanState = 0xD;
            } else {
                mpChanSelect->startNandAsync2();
                mpChanSelect->startNandAsync3();
                mbSDWorkDone = true;
                mChanState = 0x13;
            }
        }

        void SDChannelTitle::startDialog2(int kind) {
            if (kind != 0) {
                reserveAllSceneDestruction(0x12, (void*)1);
                mChanState = 7;
                return;
            }

            SDButton* button = (SDButton*)System::getSceneManager()->getScene(0x24);
            if (button->mbArrowVisible[SDButton::ARROW_BTN_LEFT]) {
                button->animation(0xF);
                button->animation(0x10);
            }

            System::getDialog()->callBtn2(0x143, 0x146, 0x25, false);
            mChanState = 0xC;
            System::getHomeButtonMenu()->enable();
            mbHbmEnable = true;
        }

        void SDChannelTitle::stopControllers(int kind) {
            for (int i = 0; i < 4; i++) {
                controller::Interface* con = System::getController(i);
                if (con != NULL) {
                    con->cancelRumbling();
                }
            }
            if (kind == 0x11) {
                System::getHomeButtonMenu()->disable();
                mbHbmEnable = false;
            }
        }

        void SDChannelTitle::startChanSelectWork(int kind) {
            int page;
            int index;
            if (System::getChannelManager()->hasChannel(mTitleID, &page, &index) != 0) {
                System::getSaveData()->iplSavedata_813596B8(mTitleID);
            }
            System::getSaveData()->mData.prevSDPage = mChanPage;
            mpSaveFile = System::getSaveData()->flushAsync(System::getMem2App());
            __WPADReconnect(TRUE);
        }

        void SDChannelTitle::doReboot() {
            snd::getSystem()->stopAllSound(0);
            snd::getSystem()->calc();
            VISetBlack(true);
            VIFlush();
            VIWaitForRetrace();
            while (!__OSSyncSram()) {
            }
            OSRebootSystem();
        }

        u32 SDChannelTitle::checkWaitEnd() {
            u32 wait = (u32)(120.0f / System::getAnimDelta());
            return mWaitCounter <= wait;
        }

        void SDChannelTitle::resetBtnPane() {
            if (mGuiState == 0) {
                mpOffAnimB->stop();
                mpOnAnimB->play();
                mpPaneManager->initPane(mpLayout->GetRootPane()->FindPaneByName(scBtnPanes[1], true));
                mBtnFocusCount[1] = 0;
            }
            mGuiState = 1;
        }

        void SDChannelTitle::drawBorder(const nw4r::ut::Rect& rect, GXColor color) {
            nw4r::ut::Rect projRect;
            System::getProjectionRect(&projRect);

            nw4r::ut::Rect drawRect[4];
            drawRect[0].left = projRect.left;
            drawRect[0].top = projRect.bottom;
            drawRect[0].right = projRect.right;
            drawRect[0].bottom = rect.top;

            drawRect[1].left = rect.right;
            drawRect[1].top = rect.top;
            drawRect[1].right = projRect.right;
            drawRect[1].bottom = projRect.top;

            drawRect[2].left = projRect.left;
            drawRect[2].top = rect.bottom;
            drawRect[2].right = rect.right;
            drawRect[2].bottom = projRect.top;

            drawRect[3].left = projRect.left;
            drawRect[3].top = rect.top;
            drawRect[3].right = rect.left;
            drawRect[3].bottom = rect.bottom;

            for (int i = 0; i < (int)ARRAY_LENGTH(drawRect); i++) {
                utility::Graphics::drawPolygon(drawRect[i], color);
            }
        }

        void SDChannelTitle::setMessage(nw4r::lyt::Pane* pane, u32 msgId, bool alloc) {
            wchar_t msg[0x100];
            wcsncpy(msg, System::getMessage(msgId), 0x100);
            msg[0xFF] = 0;

            nw4r::lyt::TextBox* textBox = nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(pane);
            if (alloc) {
                textBox->AllocStringBuffer(wcslen(msg) & 0xFFFF);
            }
            textBox->SetString(msg, 0);
        }

        nand::LayoutFile* SDChannelTitle::createNandTask(u64 titleId, nand::File** taskOut) {
            *taskOut = System::getChannelManager()->fn_8133A85C(System::getMem2App(), titleId);
            nand::MetaFile* file = System::getChannelManager()->fn_8133A7A4(System::getMem2App(), titleId);
            return new (System::getMem2App(), 4) nand::LayoutFile(file);
        }

        // clang-format off
        extern "C" char lbl_81655462[] = "iplSDChannelTitle.cpp";
        extern "C" char lbl_81655478[] = "WIPL_SE_BT_PUSH";
        extern "C" char lbl_81655488[] = "WIPL_SE_GRAY_BUTTON";
        extern "C" char lbl_8165549C[] = "WIPL_SE_DECIDE";
        extern "C" char lbl_816554AB[] = "WIPL_SE_BT_TARGETTING";
        // clang-format on

        void SDChannelTitle::getTmdView(void* arg) {
            SDChannelTitle* self = (SDChannelTitle*)arg;
            int result = utility::ESMisc::GetTmdView(self->mpBannerHeap, self->mTitleID, &self->mpTmdView);
            if (result != 0) {
                System::getErrorHandler()->log("ES", result, lbl_81655462, 0xC6D);
                System::getErrorHandler()->set(ErrorHandler::DEFAULT, 2, NULL, 0, -1);
            }
            self->mbTmdLoaded = true;
        }

        bool SDChannelTitle::checkParentalControl(ESTmdView* tmdView) {
            if (!utility::ESMisc::__IsPCEnable()) {
                return true;
            }

            SCParentalControlsInfo pcInfo;
            if (!SCGetParentalControl(&pcInfo)) {
                return true;
            }
            if (!(pcInfo.enable & SC_PARENTAL_FLAG_ENABLED)) {
                return true;
            }

            u32 ncRestriction = System::getChannelManager()->fn_8133A6B8(mTitleID);
            if ((SCGetNetContentRestrictions() & ncRestriction) != 0) {
                return false;
            }
            if (SCGetWwwRestriction() && System::getChannelManager()->fn_8133A73C(mTitleID)) {
                return false;
            }
            if (System::getChannelManager()->fn_8133A73C(mTitleID)) {
                return true;
            }
            return utility::ESMisc::CheckTmdParentalControl(tmdView);
        }

        void SDChannelTitleEvent::onEventDerived(u32 compId, u32 event, const controller::Interface* con) {
            gui::PaneComponent* component = static_cast<gui::PaneComponent*>(mpManager->getComponent(compId));
            nw4r::lyt::Pane* pane = component->getPane();
            const char* name = pane->GetName();

            if (event == ::gui::EventHandler::ON_TRIG && mpScene->mChanState == 1 && con->downTrg(controller::BTN_INTERACT)) {
                SDButton* button = (SDButton*)System::getSceneManager()->getScene(SCENE_SD_BUTTON);

                int page;
                int index;
                if (strcmp(name, SDButton::smButtonName[3]) == 0) {
                    mpScene->mpChanSelect->getSelectChan(1, &page, &index);
                    button->animation(7);
                    mpScene->selectChannel(page, index);
                    snd::getSystem()->startSE(lbl_816553FE);
                } else if (strcmp(name, SDButton::smButtonName[2]) == 0) {
                    mpScene->mpChanSelect->getSelectChan(0, &page, &index);
                    button->animation(8);
                    mpScene->selectChannel(page, index);
                    snd::getSystem()->startSE(lbl_816553FE);
                }
            }
        }

        void SDChannelTitleBtnEvent::onEvent(u32 compId, u32 event, void* data) {
            gui::PaneComponent* component = static_cast<gui::PaneComponent*>(mpManager->getComponent(compId));
            nw4r::lyt::Pane* pane = component->getPane();
            const char* name = pane->GetName();

            switch (event) {
                case ::gui::EventHandler::ON_TRIG:
                    if (mpScene->mChanState == 1) {
                        if (((controller::Interface*)data)->downTrg(controller::BTN_INTERACT)) {
                            if (strcmp(name, scBtnPanes[0]) == 0) {
                                mpScene->mpSelectAnimA->initFrame();
                                mpScene->mpSelectAnimA->play();
                                snd::getSystem()->startSE(lbl_81655478);
                                mpScene->mChanState = 0xA;
                                mpScene->calcNormalButtonWait();
                            } else if (strcmp(name, scBtnPanes[1]) == 0) {
                                if (mpScene->mGuiState != 2) {
                                    snd::getSystem()->startSE(lbl_81655488);
                                } else {
                                    mpScene->launchChannel();
                                    mpScene->mpSelectAnimB->initFrame();
                                    mpScene->mpSelectAnimB->play();
                                    snd::getSystem()->stopSE(mpScene->mpSeHandle, 0x1E);
                                    snd::getSystem()->startSE(lbl_8165549C);
                                }
                            }
                        }
                    }
                    break;
                case ::gui::EventHandler::ON_POINT:
                    for (int i = 0; i < 2; i++) {
                        if (strcmp(name, scBtnPanes[i]) == 0) {
                            if (i == 0 || mpScene->mGuiState > 0) {
                                ++mpScene->mBtnFocusCount[i];
                                if (mpScene->mBtnFocusCount[i] <= 1) {
                                    (&mpScene->mpFocusAnimAOn)[i * 6]->initFrame();
                                    (&mpScene->mpFocusAnimAOn)[i * 6]->play();
                                    snd::getSystem()->startSE(lbl_816554AB);
                                    ((controller::Interface*)data)->rumble(0);
                                }
                            }
                            break;
                        }
                    }
                    break;
                case ::gui::EventHandler::ON_LEFT:
                    for (int i = 0; i < 2; i++) {
                        if (strcmp(name, scBtnPanes[i]) == 0) {
                            if (i == 0 || mpScene->mGuiState > 0) {
                                if (mpScene->mBtnFocusCount[i] <= 0) {
                                    return;
                                }
                                --mpScene->mBtnFocusCount[i];
                                if (mpScene->mBtnFocusCount[i] <= 0) {
                                    (&mpScene->mpFocusAnimAOff)[i * 6]->initFrame();
                                    (&mpScene->mpFocusAnimAOff)[i * 6]->play();
                                }
                            }
                            break;
                        }
                    }
                    break;
            }
        }

    }  // namespace scene
}  // namespace ipl
