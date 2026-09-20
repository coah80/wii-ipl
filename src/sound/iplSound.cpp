#define IPL_SOUND_RECT_OUT_OF_LINE
#include "iplSound.h"
#include "sound/iplSound.h"

#include <revolution/ai.h>

#include "system/iplSystem.h"
#undef IPL_SOUND_RECT_OUT_OF_LINE

namespace ipl {
    namespace snd {
        struct tagSSeInfo {
            tagSSeInfo();

            nw4r::snd::SoundHandle handle;
            const char* name;
            u32 id;
        };

        tagSSeInfo::tagSSeInfo() {
        }

        BOOL m_isLocked;
        extern nw4r::snd::SoundHandle _bgmBlk;
        extern tagSSeInfo _seBlk[16];
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

        void System::initOnMemory(const void* data, EGG::Heap* heap, u32 soundSize) {
            unk_0x620[0] = 0;
            unk_0x620[1] = 0;
            _mainBGMHandle = NULL;
            EGG::SimpleAudioMgrWithFx::ArgWithFx arg;
            int i;

            arg.pHeap = heap;
            arg.soundHeapSize = soundSize;
            arg.fxArg.heapSize[0] = 0x30000;
            arg.fxArg.heapSize[1] = 0;
            arg.fxArg.heapSize[2] = 0;
            initialize(&arg);
            unk_0x620[2] = reinterpret_cast<u32>(setupMemoryArchive(data, &getSoundHeap()));
            initFx();
            sBannerSoundPlayer.init(5);
            for (i = 0; i < 16; i++) {
                _seBlk[i].name = NULL;
                _seBlk[i].id = 0xffff;
            }
            sBannerSoundPlayer.setMasterVolume(0.9f);
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

#pragma force_active on

        extern "C" asm void __ct__Q34nw4r3snd11SoundHandleFv() {
            nofralloc
            li r0, 0
            stw r0, 0(r3)
            blr
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

        int System::holdSE(const char* sndName) {
            tagSSeInfo* block;

            if (m_isLocked) {
                return 0;
            }

            block = FIsSEActive(sndName);
            if (block == NULL) {
                block = getFreeSEBlock(true);
            }
            if (block == NULL) {
                return 0;
            }

            EGG::ArcPlayer::holdSound(&block->handle, sndName);
            block->name = sndName;
            block->id = block->handle.GetId();
            return (int)block;
        }

        int System::holdSEwithPosDis(const char* sndName, f32 x, f32 y) {
            tagSSeInfo* block;

            if (m_isLocked) {
                return 0;
            }

            block = FIsSEActive(sndName);
            if (block == NULL) {
                block = getFreeSEBlock(true);
            }
            if (block == NULL) {
                return 0;
            }

            EGG::ArcPlayer::holdSound(&block->handle, sndName);
            block->name = sndName;
            block->id = block->handle.GetId();
            nw4r::ut::Rect rect;
            ipl::System::getProjectionRect4x3(&rect);
            f32 pan = x / rect.right;
            if (block->handle.detail_GetAttachedSound() != NULL) {
                block->handle.detail_GetAttachedSound()->SetPan(pan);
            }
            f32 pitch = 2.0f * y / rect.right;
            if (1.0f < pitch) {
                pitch = 1.0f;
            }
            if (block->handle.detail_GetAttachedSound() != NULL) {
                block->handle.detail_GetAttachedSound()->SetVolume(pitch, 0);
            }
            if (30.0f < y) {
                f32 pitch2 = y / 30.0f;
                if (block->handle.detail_GetAttachedSound() != NULL) {
                    block->handle.detail_GetAttachedSound()->SetPitch(pitch2);
                }
            } else if (60.0f < y) {
                if (block->handle.detail_GetAttachedSound() != NULL) {
                    block->handle.detail_GetAttachedSound()->SetPitch(1.0f);
                }
            }
            return (int)block;
        }

        void System::stopAllSound(int unk) {
            int frame;
            tagSSeInfo* block;
            int i = 0;

            for (; i < 16; i++) {
                block = &_seBlk[i];
                block->handle.Stop(unk);
                block->name = NULL;
                block->id = 0xffff;
            }

            if (_mainBGMHandle != NULL) {
                _mainBGMHandle->Stop(unk);
            }

            sBannerSoundPlayer.stop(unk);
            frame = unk * 1000 / 60;
            nw4r::snd::detail::AxManager::GetInstance().ClearEffect(nw4r::snd::AUX_A, frame);
            nw4r::snd::detail::AxManager::GetInstance().ClearEffect(nw4r::snd::AUX_B, frame);
            nw4r::snd::detail::AxManager::GetInstance().ClearEffect(nw4r::snd::AUX_C, frame);
        }

        void System::setOutputMode(EAudioOutputMode mode) {
            nw4r::snd::OutputMode outputMode;

            switch (mode) {
                case AUDIO_OUTPUT_MODE_STEREO:
                    outputMode = nw4r::snd::OUTPUT_MODE_STEREO;
                    break;
                case AUDIO_OUTPUT_MODE_SURROUND:
                    outputMode = nw4r::snd::OUTPUT_MODE_SURROUND;
                    break;
                case AUDIO_OUTPUT_MODE_MONO:
                    outputMode = nw4r::snd::OUTPUT_MODE_MONO;
                    break;
                default:
                    return;
            }

            nw4r::snd::detail::AxManager::GetInstance().SetOutputMode(outputMode);
        }

        BOOL System::isSEActive(const char* sndName) {
            return FIsSEActive(sndName) != NULL;
        }

        tagSSeInfo* System::FIsSEActive(const char* sndName) {
            int i;

            for (i = 0; i < 16; i++) {
                tagSSeInfo* block = &_seBlk[i];
                if (sndName == block->name && block->handle.IsAttachedSound()) {
                    return block;
                }
            }

            return NULL;
        }

        tagSSeInfo* System::FIsSEActive(u32 id) {
            int i;

            for (i = 0; i < 16; i++) {
                tagSSeInfo* block = &_seBlk[i];
                if (id == block->id && block->handle.IsAttachedSound()) {
                    return block;
                }
            }

            return NULL;
        }

        BOOL System::isSEActive(u32 id) {
            return FIsSEActive(id) != NULL;
        }

        tagSSeInfo* System::getFreeSEBlock(bool force) {
            int index = clipGELT_S32(unk_0x620[0] + 1, 0, 16);
            unk_0x620[0] = index;
            int i = 0;
            for (; i < 16; i++) {
                index = clipGELT_S32(unk_0x620[0] + i, 0, 16);
                if (_seBlk[index].handle.IsAttachedSound()) {
                    continue;
                }
                unk_0x620[0] = index;
                return &_seBlk[unk_0x620[0]];
            }

            if (force) {
                return &_seBlk[unk_0x620[0]];
            }

            return NULL;
        }

        BOOL System::startBannerSound(void* data, u32 size, bool ignoreSize) {
            if (sBannerSoundPlayer.checkData(data, size, ignoreSize) == 0) {
                return 0;
            }
            return sBannerSoundPlayer.start(data, size);
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
