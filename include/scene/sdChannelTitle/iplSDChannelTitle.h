#ifndef IPL_SCENE_SD_CHANNEL_TITLE_H
#define IPL_SCENE_SD_CHANNEL_TITLE_H

#include "iplSceneHeader.h"

#ifdef IPL_SD_CHANNEL_TITLE_CPP
#include "math/iplInterporation.h"
#include "scene/sdChannelMemory/iplSDMemory.h"
#include "system/iplChannelRsoThread.h"
#include "utility/iplCapture.h"
#include <private/es.h>
#include <nw4r/snd/SoundHandle.h>
#endif

namespace ipl {
    namespace scene {
        class SDChannelSelect;
        class SDButtonEventHandlerBase;
        FADER_SCENE_CLASS(SDChannelTitle) {
        public:
            SDChannelTitle(EGG::Heap * heap, SDChannelSelect * chanSel);

#ifdef IPL_SD_CHANNEL_TITLE_CPP
            virtual ~SDChannelTitle();
            virtual void prepare();
            virtual void create();
            virtual void calcCommon();
            virtual FaderSceneCommand calcFadein();
            virtual FaderSceneCommand calcNormal();
            virtual void initCalcFadeout();
            virtual FaderSceneCommand calcFadeout();
            virtual void draw();
            virtual void destroy();
            BOOL isResetAcceptable();
            virtual void startResetting();

            using Base::reserveAllSceneDestruction;
            using Base::createChildScene;

            s32 mState;
            EGG::ExpHeap* mpBannerHeap;
            EGG::ExpHeap* mpCaptureHeap;
            s32 mPage;
            s32 mIndex;
            s32 mPageCount;
            s32 mNextScene;
            s32 mParentalResult;
            math::VEC3 mPosition;
            u32 mLaunchFrame;
            s32 mStartButtonState;
            bool mbBannerStarting;
            layout::Animator* mpButtonAnimations[7][6];
            math::HermiteIntp<f32>* mpFade;
            SDChannelSelect* mpChannelSelect;
            nand::LayoutFile* mpLayoutFile;
            layout::Object* mpLayout;
            gui::PaneManager* mpPaneManager;
            layout::Object* mpIconLayout;
            EGG::ExpHeap* mpIconHeap;
            layout::Object* mpProgressLayout;
            s32 mLoadedIndex;
            nand::LayoutFile* mpBannerFiles[2];
            nand::File* mpSoundFiles[2];
            layout::Object* mpBannerLayout;
            layout::Animator* mpBannerAnimations[3];
            nw4r::snd::SoundHandle* mpSoundHandle;
            nand::File* mpSaveFile;
            u32 mWpadStopTick;
            s32 mHoverCounts[2];
            SDButtonEventHandlerBase* mpButtonEventHandler;
            utility::Capture* mpScreenCapture;
            utility::Capture* mpBannerCapture;
            ESTmdView* mpTmd;
            u8 mbTmdReady;
            u8 mTitleFlags;
            u16 mMakerCode;
            u8 mbStartAnimation;
            s32 mScriptState;
            s32 mScriptEnabled;
            bool mbStopScript;
            u32 mScriptFrame;
            u32 mScriptDuration;
            nand::File* mpScriptFile;
            EGG::ExpHeap* mpScriptHeaps[2];
            s32 mScriptHeapIndex;
            channel::RsoThread* mpRsoThread;
            EGG::ExpHeap* mpRsoHeap;
            layout::Animator* mpScriptAnimations[16];
            bool mbScriptFailed;
            EGG::ExpHeap* mpScriptHeap;
            ESTitleId mTitleId;
            SDMemory::TitleRange mTitleRange;
            u8 mUnknownTitleWork[0x800];
            SDMemory mMemory;
            u32 mErrorMessage;
            s32 mChangeFrame;
            u8 mbCopiedTitle;
            u8 mbResetAcceptable;
            nw4r::snd::SoundHandle* mpCopySound;
#else
        private:
            u8 unk_0x58[0x3460];
#endif
        };
    }  // namespace scene
}  // namespace ipl

#endif  // IPL_SCENE_SD_CHANNEL_TITLE_H
