#define IPL_SOUND_RECT_OUT_OF_LINE
#include "iplSound.h"
#include "sound/iplSound.h"

#include <revolution/ai.h>

#include "system/iplSystem.h"
#undef IPL_SOUND_RECT_OUT_OF_LINE

namespace ipl {
    namespace snd {
        struct tagSSeInfo {
            nw4r::snd::SoundHandle handle;
            const char* name;
            u32 id;
        };

        BOOL m_isLocked;
        extern nw4r::snd::SoundHandle _bgmBlk;
        extern nw4r::snd::SoundHandle* _mainBGMHandle;

        static const nw4r::snd::FxReverbHi::ReverbHiParam reverbHiParam = {
            0.0f,
            2.5f,
            0.5f,
            0.0f,
            0.0f,
            1.0f,
        };

        void System::shutup(BOOL shutUpDMA) {
            if (m_isLocked == shutUpDMA) {
                return;
            }

            m_isLocked = shutUpDMA;
            if (shutUpDMA) {
                AIStopDMA();
            } else {
                AIStartDMA();
            }
        }

        void System::stopBannerSound(int unk) {
            sBannerSoundPlayer.stop(unk);
        }

        BOOL System::checkTmpSoundFile(void* data, u32 size) {
            return sBannerSoundPlayer.checkData(data, size, false);
        }

        void System::initFx() {
            setFxReverbHi(nw4r::snd::AUX_A, &reverbHiParam);
        }

        void System::calc() {
            EGG::SimpleAudioMgr::calc();
            sBannerSoundPlayer.calc();
        }

        nw4r::snd::SoundHandle* System::startBGM(const char* bgmName) {
            if (m_isLocked) {
                return NULL;
            }

            EGG::ArcPlayer::startSound(&_bgmBlk, bgmName);
            _mainBGMHandle = &_bgmBlk;
            return &_bgmBlk;
        }

        nw4r::snd::SoundHandle* System::startSE(const char* sndName) {
            tagSSeInfo* block;

            if (m_isLocked) {
                return NULL;
            }

            block = FIsSEActive(sndName);
            if (block != NULL && block->handle.GetId() == 0x39) {
                goto return_block;
            }
            if (block == NULL) {
                goto continue_block;
            }
            if (block->handle.GetId() != 0x35) {
                goto continue_block;
            }

        return_block:
            return reinterpret_cast<nw4r::snd::SoundHandle*>(block);

        continue_block:
            if (block == NULL) {
                block = getFreeSEBlock(true);
            }
            if (block == NULL) {
                return NULL;
            }

            block->handle.Stop(0);
            EGG::ArcPlayer::startSound(&block->handle, sndName);
            block->name = sndName;
            block->id = block->handle.GetId();
            return reinterpret_cast<nw4r::snd::SoundHandle*>(block);
        }

        int System::startSEIndex(u32 sndIndex) {
            tagSSeInfo* block;

            if (m_isLocked) {
                return 0;
            }

            block = FIsSEActive(sndIndex);
            if (block != NULL && block->handle.GetId() == 0x39) {
                goto return_block_index;
            }
            if (block == NULL) {
                goto continue_block_index;
            }
            if (block->handle.GetId() != 0x35) {
                goto continue_block_index;
            }

        return_block_index:
            return (int)block;

        continue_block_index:
            if (block == NULL) {
                block = getFreeSEBlock(true);
            }
            if (block == NULL) {
                return 0;
            }

            block->handle.Stop(0);
            mSoundArchivePlayer.StartSound(&block->handle, sndIndex);
            block->id = sndIndex;
            return (int)block;
        }

        int System::startSEwithPos(const char* sndName, f32 pos) {
            tagSSeInfo* block;
            tagSSeInfo* active;

            if (m_isLocked) {
                return 0;
            }

            active = FIsSEActive(sndName);
            block = getFreeSEBlock(active == NULL);
            if (block == NULL) {
                return 0;
            }

            block->handle.Stop(0);
            EGG::ArcPlayer::startSound(&block->handle, sndName);
            block->name = sndName;
            block->id = block->handle.GetId();
            nw4r::ut::Rect rect;
            ipl::System::getProjectionRect(&rect);
            f32 pan = pos / rect.right;
            nw4r::snd::detail::BasicSound* sound = block->handle.detail_GetAttachedSound();
            if (sound != NULL) {
                sound->SetPan(pan);
            }
            return (int)block;
        }

        long System::clipGELT_S32(long value, long lo, long hi) {
            long range = hi - lo;

            if (range < 0) {
                long temp = lo;
                lo = hi;
                hi = temp;
                range = temp - lo;
            }

            if (value < lo) {
                value += range;
            } else if (value >= hi) {
                value -= range;
            }

            return value;
        }
}  // namespace snd
}  // namespace ipl
