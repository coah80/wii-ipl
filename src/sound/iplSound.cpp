#define AutoLock(x) AutoLock(x) NO_INLINE
#define IPL_SOUND_RECT_OUT_OF_LINE
#define IPL_SOUND_MATCHING
#include "iplSound.h"
#include "sound/iplSound.h"

#include <revolution/ai.h>

#include "system/iplSystem.h"
#undef IPL_SOUND_RECT_OUT_OF_LINE
#undef AutoLock

extern "C" void _seBlk__Q23ipl3snd();
extern "C" nw4r::snd::SoundHandle* _mainBGMHandle__Q23ipl3snd;
extern "C" const f32 scSoundZeroF;
extern "C" const f32 scSoundOneF;
extern "C" const f32 scSoundTwoF;
extern "C" const f32 scSoundThirtyF;
extern "C" const f32 scSoundSixtyF;
extern "C" void _savegpr_26();
extern "C" void _restgpr_26();
extern "C" void sBannerSoundPlayer__Q23ipl3snd();
extern "C" void GetInstance__Q44nw4r3snd6detail9AxManagerFv();
extern "C" void ClearEffect__Q44nw4r3snd6detail9AxManagerFQ34nw4r3snd6AuxBusi();
extern "C" void stop__17BannerSoundPlayerFUl();
extern "C" void setMasterVolume__17BannerSoundPlayerFf();
extern "C" void SetMasterVolume__Q44nw4r3snd6detail9AxManagerFfi();

namespace ipl {
    namespace snd {

        inline System::System() {
        }

        struct tagSSeInfo {
            tagSSeInfo();
            ~tagSSeInfo();

            nw4r::snd::SoundHandle handle;
            const char* name;
            u32 id;
        };

        inline tagSSeInfo::tagSSeInfo() {
        }

        struct tagSBgmInfo {
            nw4r::snd::SoundHandle handle;
            tagSBgmInfo();
            ~tagSBgmInfo();
        };

        inline tagSBgmInfo::tagSBgmInfo() {
        }

        inline tagSSeInfo::~tagSSeInfo() {
        }

        inline tagSBgmInfo::~tagSBgmInfo() {
        }

        tagSSeInfo _seBlk[16];
        tagSBgmInfo _bgmBlk;
        System sSystem;
        BannerSoundPlayer sBannerSoundPlayer;
        nw4r::snd::SoundHandle* _mainBGMHandle;
        BOOL m_isLocked;

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
            mSoundWork[0] = 0;
            mSoundWork[1] = 0;
            _mainBGMHandle = NULL;
            EGG::SimpleAudioMgrWithFx::ArgWithFx arg;
            int i;

            arg.pHeap = heap;
            arg.soundHeapSize = soundSize;
            arg.fxArg.heapSize[0] = 0x30000;
            arg.fxArg.heapSize[1] = 0;
            arg.fxArg.heapSize[2] = 0;
            initialize(&arg);
            mSoundWork[2] = reinterpret_cast<u32>(setupMemoryArchive(data, &getSoundHeap()));
            initFx();
            sBannerSoundPlayer.init(5);
            for (i = 0; i < 16; i++) {
                _seBlk[i].name = NULL;
                _seBlk[i].id = 0xffff;
            }
            sBannerSoundPlayer.setMasterVolume(0.9f);
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

            EGG::ArcPlayer::startSound(&_bgmBlk.handle, bgmName);
            _mainBGMHandle = &_bgmBlk.handle;
            return &_bgmBlk.handle;
        }

        nw4r::snd::SoundHandle* System::startSE(const char* sndName) {
            tagSSeInfo* block;

            if (m_isLocked) {
                return NULL;
            }

            block = FIsSEActive(sndName);
            if (block != NULL && block->handle.GetId() == WIPL_SE_GRAY_BUTTON) {
                goto return_block;
            }
            if (block == NULL) {
                goto continue_block;
            }
            if (block->handle.GetId() != WIPL_SE_ERROR) {
                goto continue_block;
            }

        return_block:
            return &block->handle;

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
            return &block->handle;
        }

        int System::startSEIndex(u32 sndIndex) {
            tagSSeInfo* block;

            if (m_isLocked) {
                return 0;
            }

            block = FIsSEActive(sndIndex);
            if (block != NULL && block->handle.GetId() == WIPL_SE_GRAY_BUTTON) {
                goto return_block_index;
            }
            if (block == NULL) {
                goto continue_block_index;
            }
            if (block->handle.GetId() != WIPL_SE_ERROR) {
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
            EGG::ArcPlayer::startSound(&block->handle, sndIndex);
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
            f32 pitch = scSoundTwoF * y / rect.right;
            if (scSoundOneF < pitch) {
                pitch = scSoundOneF;
            }
            if (block->handle.detail_GetAttachedSound() != NULL) {
                block->handle.detail_GetAttachedSound()->SetVolume(pitch, 0);
            }
            if (scSoundThirtyF < y) {
                f32 pitch2 = y / scSoundThirtyF;
                if (block->handle.detail_GetAttachedSound() != NULL) {
                    block->handle.detail_GetAttachedSound()->SetPitch(pitch2);
                }
            } else if (scSoundSixtyF < y) {
                if (block->handle.detail_GetAttachedSound() != NULL) {
                    block->handle.detail_GetAttachedSound()->SetPitch(scSoundTwoF);
                }
            }
            return (int)block;
        }

        void System::stopBGM(int frames) {
            if (_mainBGMHandle && _mainBGMHandle->IsAttachedSound()) {
                _mainBGMHandle->Stop(frames);
            }
        }

        void System::stopSE(nw4r::snd::SoundHandle* handle, int frames) {
            tagSSeInfo* block;
            int i;
            if (handle != NULL && handle->IsAttachedSound()) {
                for (i = 0; i < 16; i++) {
                    block = &_seBlk[i];
                    if (handle == &block->handle) {
                        block->handle.Stop(frames);
                        block->name = NULL;
                        block->id = 0xFFFF;
                    }
                }
            }
        }

        void System::stopAllSound(int fadeFrames) {
            int frame;
            tagSSeInfo* block;
            int i = 0;

            for (; i < 16; i++) {
                block = &_seBlk[i];
                block->handle.Stop(fadeFrames);
                block->name = NULL;
                block->id = 0xffff;
            }

            if (_mainBGMHandle != NULL) {
                _mainBGMHandle->Stop(fadeFrames);
            }

            sBannerSoundPlayer.stop(fadeFrames);
            frame = fadeFrames * 1000 / 60;
            nw4r::snd::detail::AxManager::GetInstance().ClearEffect(nw4r::snd::AUX_A, frame);
            nw4r::snd::detail::AxManager::GetInstance().ClearEffect(nw4r::snd::AUX_B, frame);
            nw4r::snd::detail::AxManager::GetInstance().ClearEffect(nw4r::snd::AUX_C, frame);
        }

        int System::resetAllSound() {
            tagSSeInfo* block;
            int i = 0;
            for (; i < 16; i++) {
                block = &_seBlk[i];
                block->handle.Stop(0);
                block->name = NULL;
                block->id = 0xFFFF;
            }
            if (_mainBGMHandle != NULL && _mainBGMHandle->IsAttachedSound()) {
                _mainBGMHandle->detail_GetAttachedSound()->Stop(0);
            }
            sBannerSoundPlayer.stop(0);
            nw4r::snd::detail::AxManager::GetInstance().ClearEffect(nw4r::snd::AUX_A, 0);
            nw4r::snd::detail::AxManager::GetInstance().ClearEffect(nw4r::snd::AUX_B, 0);
            nw4r::snd::detail::AxManager::GetInstance().ClearEffect(nw4r::snd::AUX_C, 0);
            nw4r::snd::detail::AxManager::GetInstance().SetMasterVolume(scSoundZeroF, 0);
            sBannerSoundPlayer.setMasterVolume(scSoundZeroF);
        }

    }
}
namespace nw4r {
namespace snd {
inline SoundHandle::SoundHandle() : mSound(NULL) {}
}
}
namespace ipl {
namespace snd {

        void System::muteOnBGM(int frames) {
            nw4r::snd::SoundHandle* handle = _mainBGMHandle;
            if (handle && handle->IsAttachedSound()) handle->SetVolume(scSoundZeroF, frames);
        }

        void System::muteOffBGM(int frames) {
            nw4r::snd::SoundHandle* handle = _mainBGMHandle;
            if (handle && handle->IsAttachedSound()) handle->SetVolume(scSoundOneF, frames);
        }

        void System::pauseOnBGM() {
            if (_mainBGMHandle) {
                if (_mainBGMHandle->IsAttachedSound()) _mainBGMHandle->Pause(true, 5);
                pauseOnSE();
                sBannerSoundPlayer.pause(true);
                nw4r::snd::detail::AxManager::GetInstance().ClearEffect(nw4r::snd::AUX_A, 250);
                nw4r::snd::detail::AxManager::GetInstance().ClearEffect(nw4r::snd::AUX_B, 250);
                nw4r::snd::detail::AxManager::GetInstance().ClearEffect(nw4r::snd::AUX_C, 250);
            }
        }

        void System::pauseOffBGM() {
            if (_mainBGMHandle) {
                initFx();
                if (_mainBGMHandle->IsAttachedSound()) _mainBGMHandle->Pause(false, 5);
                pauseOffSE();
                sBannerSoundPlayer.pause(false);
            }
        }

        void System::pauseOnSE() {
            for (int index = 0; index < 16; ++index) {
                if (_seBlk[index].handle.IsAttachedSound()) {
                    _seBlk[index].handle.Pause(true, 5);
                }
            }
        }

        void System::pauseOffSE() {
            for (int index = 0; index < 16; ++index) {
                if (_seBlk[index].handle.IsAttachedSound()) {
                    _seBlk[index].handle.Pause(false, 5);
                }
            }
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
            int index = clipGELT_S32(mSoundWork[0] + 1, 0, 16);
            mSoundWork[0] = index;
            int i = 0;
            for (; i < 16; i++) {
                index = clipGELT_S32(mSoundWork[0] + i, 0, 16);
                if (_seBlk[index].handle.IsAttachedSound()) {
                    continue;
                }
                mSoundWork[0] = index;
                return &_seBlk[mSoundWork[0]];
            }

            if (force) {
                return &_seBlk[mSoundWork[0]];
            }

            return NULL;
        }

        BOOL System::startBannerSound(void* data, u32 size, bool ignoreSize) {
            if (sBannerSoundPlayer.checkData(data, size, ignoreSize) == 0) {
                return 0;
            }
            return sBannerSoundPlayer.start(data, size);
        }

        void System::stopBannerSound(int fadeFrames) {
            sBannerSoundPlayer.stop(fadeFrames);
        }

        BOOL System::checkTmpSoundFile(void* data, u32 size) {
            return sBannerSoundPlayer.checkData(data, size, false);
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
        extern "C" const f32 scSoundZeroF = 0.0f;
        extern "C" const f32 scSoundTwoF = 2.0f;
        extern "C" const f32 scSoundOneF = 1.0f;
        extern "C" const f32 scSoundThirtyF = 30.0f;
        extern "C" const f32 scSoundSixtyF = 60.0f;
}  // namespace snd
}  // namespace ipl
