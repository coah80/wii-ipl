#ifndef IPL_SOUND_H
#define IPL_SOUND_H

#include <revolution/types.h>

#include "bannerSound/BannerSoundPlayer.h"

#include <egg/core.h>

#include "IplSound.rsid"

namespace ipl {
    namespace snd {
        enum EAudioOutputMode {
            AUDIO_OUTPUT_MODE_STEREO = 0,
            AUDIO_OUTPUT_MODE_SURROUND = 1,
            AUDIO_OUTPUT_MODE_MONO = 2,
        };

        struct tagSSeInfo;

        class System : EGG::SimpleAudioMgrWithFx {
        public:
            System();

            void initOnMemory(const void* data, EGG::Heap* heap, u32 soundSize);
            void initFx() NO_INLINE;

            void shutup(BOOL shutUpDMA);

            virtual void calc();  // 0x0C

            nw4r::snd::SoundHandle* startBGM(const char* bgmName);
            nw4r::snd::SoundHandle* startSE(const char* sndName);
            int startSEIndex(u32 sndIndex);
            int startSEwithPos(const char* sndName, f32 pos);

            int holdSE(const char* sndName);
            int holdSEwithPosDis(const char* sndName, f32 x, f32 y);

#ifdef IPL_SOUND_MATCHING
            void stopBGM(int unk = 0);
#else
            int stopBGM(int unk = 0);
#endif
            int stopBGM(nw4r::snd::SoundHandle* handle, int unk = 0);
            void stopSE(nw4r::snd::SoundHandle* handle, int unk = 0);
            void stopAllSound(int unk = 0);

#ifdef IPL_SOUND_MATCHING
            void resetAllSound();
#else
            int resetAllSound();
#endif

#ifdef IPL_SOUND_MATCHING
            void muteOffBGM(int);
#else
            int muteOffBGM(int);
#endif
#ifdef IPL_SOUND_MATCHING
            void muteOnBGM(int);
#else
            int muteOnBGM(int);
#endif

#ifdef IPL_SOUND_MATCHING
            void pauseOnBGM();
#else
            int pauseOnBGM();
#endif
#ifdef IPL_SOUND_MATCHING
            void pauseOffBGM();
#else
            int pauseOffBGM();
#endif

#ifdef IPL_SOUND_MATCHING
            void pauseOnSE();
#else
            int pauseOnSE();
#endif
#ifdef IPL_SOUND_MATCHING
            void pauseOffSE();
#else
            int pauseOffSE();
#endif

            void setOutputMode(EAudioOutputMode mode);

            BOOL isSEActive(const char* sndName);
            BOOL isSEActive(u32 id);

            tagSSeInfo* FIsSEActive(const char* sndName);
            tagSSeInfo* FIsSEActive(u32 id);
            tagSSeInfo* getFreeSEBlock(bool force);

            BOOL startBannerSound(void*, u32, bool ignoreSize = false);
            void stopBannerSound(int unk = 0);

            BOOL checkTmpSoundFile(void*, u32);

            long clipGELT_S32(long value, long lo, long hi);

        private:
            u32 unk_0x620[3];
        };

        // use getSystem() and getBannerPlayer() instead
        extern System sSystem;
        extern BannerSoundPlayer sBannerSoundPlayer;

        static System* getSystem() {
            return &sSystem;
        }

        static BannerSoundPlayer* getBannerPlayer() {
            return &sBannerSoundPlayer;
        }
    }  // namespace snd
}  // namespace ipl

#endif  // IPL_SOUND_H
