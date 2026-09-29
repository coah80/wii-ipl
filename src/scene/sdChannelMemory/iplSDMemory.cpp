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
            mpDialogLayout->getAnim(16)->initFrame();
            mpDialogLayout->getAnim(16)->restart();
            mpDialogLayout->getAnim(14)->initAnmFrame();
            mpDialogLayout->getAnim(14)->initFrame();
            mpDialogLayout->getAnim(14)->restart();
            if (!mScroller.isDownEnd()) {
                showUpArrow();
            }
        }

        void SDMemory::showDownArrow() {
            if (mControllerFlags[0] == 0) {
                mpDialogLayout->getAnim(16)->initAnmFrame();
                mpDialogLayout->getAnim(16)->initFrame();
                mpDialogLayout->getAnim(16)->restart();
                mControllerFlags[0] = 1;
            }
        }

        void SDMemory::showUpArrow() {
            if (mControllerFlags[1] == 0) {
                mpDialogLayout->getAnim(14)->initAnmFrame();
                mpDialogLayout->getAnim(14)->initFrame();
                mpDialogLayout->getAnim(14)->restart();
                mControllerFlags[1] = 1;
            }
        }

        void SDMemory::hideDownArrow() {
            if (mControllerFlags[0] != 0) {
                mpDialogLayout->getAnim(17)->initAnmFrame();
                mpDialogLayout->getAnim(17)->initFrame();
                mpDialogLayout->getAnim(17)->restart();
                mControllerFlags[0] = 0;
            }
        }

        void SDMemory::hideUpArrow() {
            if (mControllerFlags[1] != 0) {
                mpDialogLayout->getAnim(15)->initAnmFrame();
                mpDialogLayout->getAnim(15)->initFrame();
                mpDialogLayout->getAnim(15)->restart();
                mControllerFlags[1] = 0;
            }
        }

        void SDMemory::showLeftArrow() {
            if (mControllerFlags[2] == 0) {
                mpDialogLayout->getAnim(19)->initFrame();
                mpDialogLayout->getAnim(19)->restart();
                mControllerFlags[2] = 1;
            }
        }

        void SDMemory::showRightArrow() {
            if (mControllerFlags[3] == 0) {
                mpDialogLayout->getAnim(21)->initFrame();
                mpDialogLayout->getAnim(21)->restart();
                mControllerFlags[3] = 1;
            }
        }

        void SDMemory::hideLeftArrow() {
            if (mControllerFlags[2] != 0) {
                mpDialogLayout->getAnim(20)->initFrame();
                mpDialogLayout->getAnim(20)->restart();
                mControllerFlags[2] = 0;
            }
        }

        void SDMemory::hideRightArrow() {
            if (mControllerFlags[3] != 0) {
                mpDialogLayout->getAnim(22)->initFrame();
                mpDialogLayout->getAnim(22)->restart();
                mControllerFlags[3] = 0;
            }
        }
    }
}
