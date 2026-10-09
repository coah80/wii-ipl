#include "homebutton/HBMFrameController.h"

namespace homebutton {
    void FrameController::init(int type, f32 maxFrame, f32 minFrame, f32 delta) {
        mAnmType = type;

        mMaxFrame = maxFrame;
        mMinFrame = minFrame;

        mDelta = delta;

        mState = ANIM_STATE_STOP;

        mbAlternateBack = false;

        initFrame();
    }

    void FrameController::initFrame() {
        float frame;
        if (mAnmType == ANIM_TYPE_BACKWARD) {
            frame = mMaxFrame;
        } else {
            frame = mMinFrame;
        }
        mFrame = frame;
    }

    void FrameController::calc() {
        if (mState == ANIM_STATE_PLAY) {
            switch (mAnmType) {
                // Animate normally; Once reaching the maximum frame, the animation stops.
                case ANIM_TYPE_FORWARD: {
                    f32 lastFrame = getLastFrame();
                    mFrame += mDelta;
                    if (mFrame >= lastFrame) {
                        mFrame = lastFrame;
                        mState = ANIM_STATE_STOP;
                    }
                    break;
                }
                // Animate in reverse; Once reaching the minimum frame, the animation stops.
                case ANIM_TYPE_BACKWARD: {
                    mFrame -= mDelta;
                    if (mFrame <= mMinFrame) {
                        mFrame = mMinFrame;
                        mState = ANIM_STATE_STOP;
                    }
                    break;
                }
                // Animate forever; Once reaching the maximum frame, the animation repeats.
                case ANIM_TYPE_LOOP: {
                    mFrame += mDelta;
                    if (mFrame >= mMaxFrame) {
                        mFrame -= (mMaxFrame - mMinFrame);
                    }
                    break;
                }
                // Animate and alternate direction; Once reaching the maximum frame, it then animates forwards.
                // And once reaching the minimum frame, it animates backwards. Then repeat.
                case ANIM_TYPE_ALTERNATE: {
                    if (!mbAlternateBack) {
                        f32 lastFrame = getLastFrame();
                        mFrame += mDelta;
                        if (mFrame >= lastFrame) {
                            mFrame = lastFrame;
                            mbAlternateBack = true;
                        }
                    } else {
                        mFrame -= mDelta;
                        if (mFrame <= mMinFrame) {
                            mFrame = mMinFrame;
                            mbAlternateBack = false;
                        }
                    }
                    break;
                }
            }
        }
    }
}  // namespace homebutton
