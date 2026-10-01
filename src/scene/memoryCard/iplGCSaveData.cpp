#include "scene/memoryCard/iplGCSaveData.h"

#include "scene/memoryCard/iplMemoryCard.h"
#include "scene/textBalloon/iplBalloon.h"

#include "iplSound.h"
#include "iplSystem.h"

namespace ipl {
    namespace scene {
        static const MemoryBase::AnmName scAnmName[] = {
            {"it_ObjCubeEdit_b_SaveDataIn.brlan", "G_Data"},
            {"it_ObjCubeEdit_b_SaveDataOut.brlan", "G_Data"},
            {"it_ObjCubeEdit_b_SaveDataFoucusIn.brlan", "G_Data"},
            {"it_ObjCubeEdit_b_SaveDataFoucusOut.brlan", "G_Data"},
            {"it_ObjCubeEdit_b_SaveDataFlash.brlan", "G_DataFlash"},
        };
        static const char* scDataPaneName = "B_Data_00";


        GCSaveData::GCSaveData(EGG::Heap* heap, nand::LayoutFile* layoutFile, const char* directory, const char* fileName,
                               math::VEC3 translate) {
            mpBalloon = NULL;
            mpLayout = new layout::Object(heap, layoutFile, directory, fileName);
            add_animation(scAnmName, 5);
            mpLayout->finishBinding();

            mpEvent = new MemoryBaseEvent(this);
            mpPaneManager = new gui::PaneManager(mpEvent, mpLayout->getDrawInfo(), NULL, NULL, true);
            mpPaneManager->setupScene(mpLayout);
            mpPaneManager->setAllComponentTriggerTarget(false);

            mpPaneManager->setTriggerTarget(mpLayout->FindPaneByName(scDataPaneName), true);

            add_anmbutton(scDataPaneName, get_animation(2), get_animation(3), NULL);

            setTranslate(translate);
        }

        void GCSaveData::calc() {
            mpLayout->calc();
            mpPaneManager->calc();
            get_anmbutton(scDataPaneName)->calc();
        }

        void GCSaveData::draw() {
            nw4r::lyt::Pane* pane = mpLayout->FindPaneByName("DataBanner_00");
            nw4r::lyt::Material* material = pane->FindMaterialByName("DataBanner_00");
            pane->SetVisible(true);

            if (static_cast<MemoryCard*>(System::getScene(0xE))->getManager()->isIconValidate(mSlot, mIndex) &&
                static_cast<MemoryCard*>(System::getScene(0xE))->getManager()->create_icon(mSlot, mIndex) != NULL) {
                material->SetTexture(0, *static_cast<MemoryCard*>(System::getScene(0xE))
                                            ->getManager()
                                            ->create_icon(mSlot, mIndex));
            } else {
                pane->SetVisible(false);
            }

            if (mIndex >= 0 && mIndex < 0x7f) {
                mpLayout->draw();
            } else {
                if (mpBalloon != NULL) {
                    mpBalloon->terminate();
                }
            }
        }

        void GCSaveData::update() {
            if (mIndex < 0) {
                return;
            }
            if (mIndex >= 0x7f) {
                return;
            }
            mpPaneManager->update();
        }

        void GCSaveData::onPoint(const char* paneName, controller::Interface* controller) {
            AnmButton* button = get_anmbutton(paneName);
            if (button != NULL) {
                if (button->unk_0x04 == 0) {
                    if (System::getScene(0xE) != NULL) {
                        if (static_cast<MemoryCard*>(System::getScene(0xE))
                                ->getManager()
                                ->isIconValidate(mSlot, mIndex)) {
                            mpBalloon->init(static_cast<MemoryCard*>(System::getScene(0xE))
                                                ->getManager()
                                                ->getComment(mSlot, mIndex, 0),
                                            0);
                            get_anmbutton(scDataPaneName)->setBalloon(mpBalloon);
                        } else {
                            get_anmbutton(scDataPaneName)->setBalloon(NULL);
                        }
                    }
                    snd::getSystem()->startSE("WIPL_SE_BT_TARGETTING");
                    if (controller != NULL) {
                        controller->rumble(0);
                    }
                    button->onCmdRecv(1);
                }
                button->unk_0x04++;
            }
        }

        void GCSaveData::onLeft(const char* paneName) {
            AnmButton* button = get_anmbutton(paneName);
            if (button != NULL) {
                if (button->unk_0x04 == 1) {
                    button->onCmdRecv(2);
                }
                button->unk_0x04--;
            }
        }

        void GCSaveData::onTrig(const char* paneName) {
            if (static_cast<MemoryCard*>(System::getScene(0xE)) != NULL &&
                static_cast<MemoryCard*>(System::getScene(0xE))->getManager()->isIconValidate(mSlot, mIndex) &&
                get_anmbutton(paneName) != NULL) {
                static_cast<MemoryCard*>(System::getScene(0xE))->onFocus(this);
            }
        }

        void GCSaveData::setTranslate(const nw4r::math::VEC3& translate) {
            mpLayout->FindPaneByName("N_Data_00")->SetTranslate(translate);
        }

        const nw4r::math::VEC3* GCSaveData::getTranslate() {
            return &mpLayout->FindPaneByName("N_Data_00")->GetTranslate();
        }

        void GCSaveData::init() {
            clear_button(scDataPaneName);
            if (mpBalloon != NULL) {
                mpBalloon->terminate();
            }
        }

        void GCSaveData::setBalloon(TextBalloon* balloon) {
            mpBalloon = balloon;
        }

        GCSaveData::~GCSaveData() {}
    }  // namespace scene
}  // namespace ipl
