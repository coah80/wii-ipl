#include "scene/sdChannelMemory/iplSDMemory.h"

namespace ipl {
    namespace scene {
        SDMemory::SDMemory() : mScroller() {}

        SDMemory::~SDMemory() {}

        void SDMemory::resetScrollArrows() {
            mControllerFlags[0] = 0;
            mControllerFlags[1] = 0;
            mControllerFlags[2] = 0;
            mControllerFlags[3] = 0;
            mpDialogLayout->getAnim(16)->initAnmFrame();
            mpDialogLayout->getAnim(14)->initAnmFrame();
            if (!mScroller.isDownEnd()) {
                showUpArrow();
            }
        }

        void SDMemory::updateScrollArrows(u32 previousDownEnd, u32 previousUpEnd, u32 downEnd, u32 upEnd) {
            if (previousDownEnd != 1 && downEnd == 1) {
                hideDownArrow();
            }
            if (previousDownEnd == 1 && downEnd != 1) {
                showDownArrow();
            }
            if (previousUpEnd != 1 && upEnd == 1) {
                hideUpArrow();
            }
            if (previousUpEnd == 1 && upEnd != 1) {
                showUpArrow();
            }
        }

        void SDMemory::showDownArrow() {
            if (mControllerFlags[0] == 0) {
                layout::Animator* initAnimation = mpDialogLayout->getAnim(16);
                initAnimation->initAnmFrame();
                layout::Animator* playAnimation = mpDialogLayout->getAnim(16);
                playAnimation->initFrame();
                playAnimation->restart();
                mControllerFlags[0] = 1;
            }
        }

        void SDMemory::showUpArrow() {
            if (mControllerFlags[1] == 0) {
                layout::Animator* initAnimation = mpDialogLayout->getAnim(14);
                initAnimation->initAnmFrame();
                layout::Animator* playAnimation = mpDialogLayout->getAnim(14);
                playAnimation->initFrame();
                playAnimation->restart();
                mControllerFlags[1] = 1;
            }
        }

        void SDMemory::hideDownArrow() {
            if (mControllerFlags[0] != 0) {
                layout::Animator* initAnimation = mpDialogLayout->getAnim(17);
                initAnimation->initAnmFrame();
                layout::Animator* playAnimation = mpDialogLayout->getAnim(17);
                playAnimation->initFrame();
                playAnimation->restart();
                mControllerFlags[0] = 0;
            }
        }

        void SDMemory::hideUpArrow() {
            if (mControllerFlags[1] != 0) {
                layout::Animator* initAnimation = mpDialogLayout->getAnim(15);
                initAnimation->initAnmFrame();
                layout::Animator* playAnimation = mpDialogLayout->getAnim(15);
                playAnimation->initFrame();
                playAnimation->restart();
                mControllerFlags[1] = 0;
            }
        }

        void SDMemory::showLeftArrow() {
            if (mControllerFlags[2] == 0) {
                layout::Animator* animation = mpDialogLayout->getAnim(19);
                animation->initFrame();
                animation->restart();
                mControllerFlags[2] = 1;
            }
        }

        void SDMemory::showRightArrow() {
            if (mControllerFlags[3] == 0) {
                layout::Animator* animation = mpDialogLayout->getAnim(21);
                animation->initFrame();
                animation->restart();
                mControllerFlags[3] = 1;
            }
        }

        void SDMemory::hideLeftArrow() {
            if (mControllerFlags[2] != 0) {
                layout::Animator* animation = mpDialogLayout->getAnim(20);
                animation->initFrame();
                animation->restart();
                mControllerFlags[2] = 0;
            }
        }

        void SDMemory::hideRightArrow() {
            if (mControllerFlags[3] != 0) {
                layout::Animator* animation = mpDialogLayout->getAnim(22);
                animation->initFrame();
                animation->restart();
                mControllerFlags[3] = 0;
            }
        }
    }
}
