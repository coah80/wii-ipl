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
            virtual BOOL isResetAcceptable() const;
            virtual void startResetting();

            virtual void unkv_0x68() = 0;
            virtual void unkv_0x6C() = 0;
            virtual void unkv_0x70() = 0;
            virtual void unkv_0x74() = 0;
            virtual void unkv_0x78() = 0;
            virtual void unkv_0x7C() = 0;
            virtual void unkv_0x80() = 0;
            virtual void unkv_0x84() = 0;
            virtual void unkv_0x88() = 0;
            virtual void unkv_0x8C() = 0;
            virtual void unkv_0x90() = 0;
            virtual void unkv_0x94() = 0;
            virtual void unkv_0x98() = 0;
            virtual void unkv_0x9C() = 0;
            virtual void unkv_0xA0() = 0;
            virtual void unkv_0xA4() = 0;
            virtual void unkv_0xA8() = 0;
            virtual void unkv_0xAC() = 0;
            virtual void unkv_0xB0() = 0;
            virtual void unkv_0xB4() = 0;
            virtual void unkv_0xB8() = 0;
            virtual void unkv_0xBC() = 0;
            virtual void unkv_0xC0() = 0;
            virtual void unkv_0xC4() = 0;
            virtual void unkv_0xC8() = 0;
            virtual void unkv_0xCC() = 0;
            virtual void unkv_0xD0() = 0;
            virtual void unkv_0xD4() = 0;
            virtual void unkv_0xD8() = 0;
            virtual void unkv_0xDC() = 0;
            virtual void unkv_0xE0() = 0;
            virtual void unkv_0xE4() = 0;
            virtual void unkv_0xE8() = 0;
            virtual void unkv_0xEC() = 0;
            virtual void unkv_0xF0() = 0;
            virtual void unkv_0xF4() = 0;
            virtual void unkv_0xF8() = 0;
            virtual void unkv_0xFC() = 0;
            virtual void unkv_0x100() = 0;
            virtual void unkv_0x104() = 0;
            virtual void unkv_0x108() = 0;
            virtual void unkv_0x10C() = 0;
            virtual void unkv_0x110() = 0;
            virtual void unkv_0x114() = 0;
            virtual void unkv_0x118() = 0;
            virtual void unkv_0x11C() = 0;
            virtual void unkv_0x120() = 0;
            virtual void unkv_0x124() = 0;
            virtual void unkv_0x128() = 0;
            virtual void unkv_0x12C() = 0;
            virtual void unkv_0x130() = 0;
            virtual void unkv_0x134() = 0;
            virtual void unkv_0x138() = 0;
            virtual void unkv_0x13C() = 0;

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
