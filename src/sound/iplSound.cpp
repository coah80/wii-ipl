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

        extern "C" asm void resetAllSound__Q33ipl3snd6SystemFv() {
            nofralloc
            stwu r1, -0x20(r1)
            mflr r0
            stw r0, 0x24(r1)
            addi r11, r1, 0x20
            bl _savegpr_26
            li r26, 0
            lis r28, _seBlk__Q23ipl3snd@ha
            lis r3, 1
            li r31, 0
            mr r29, r26
            addi r28, r28, _seBlk__Q23ipl3snd@l
            subi r30, r3, 1
        resetAllSound_loop:
            lwzx r3, r28, r31
            add r27, r28, r31
            cmpwi r3, 0
            beq resetAllSound_clear
            lwz r12, 0(r3)
            li r4, 0
            lwz r12, 0x18(r12)
            mtctr r12
            bctrl
        resetAllSound_clear:
            stw r29, 0x4(r27)
            addi r26, r26, 1
            cmpwi r26, 0x10
            addi r31, r31, 0xc
            stw r30, 0x8(r27)
            blt resetAllSound_loop
            lwz r3, _mainBGMHandle__Q23ipl3snd
            cmpwi r3, 0
            beq resetAllSound_banner
            lwz r0, 0(r3)
            cmpwi r0, 0
            beq resetAllSound_banner
            lwz r3, 0(r3)
            li r4, 0
            lwz r12, 0(r3)
            lwz r12, 0x18(r12)
            mtctr r12
            bctrl
        resetAllSound_banner:
            lis r31, sBannerSoundPlayer__Q23ipl3snd@ha
            li r4, 0
            addi r3, r31, sBannerSoundPlayer__Q23ipl3snd@l
            bl stop__17BannerSoundPlayerFUl
            bl GetInstance__Q44nw4r3snd6detail9AxManagerFv
            li r4, 0
            li r5, 0
            bl ClearEffect__Q44nw4r3snd6detail9AxManagerFQ34nw4r3snd6AuxBusi
            bl GetInstance__Q44nw4r3snd6detail9AxManagerFv
            li r4, 1
            li r5, 0
            bl ClearEffect__Q44nw4r3snd6detail9AxManagerFQ34nw4r3snd6AuxBusi
            bl GetInstance__Q44nw4r3snd6detail9AxManagerFv
            li r4, 2
            li r5, 0
            bl ClearEffect__Q44nw4r3snd6detail9AxManagerFQ34nw4r3snd6AuxBusi
            bl GetInstance__Q44nw4r3snd6detail9AxManagerFv
            lfs f1, scSoundZeroF
            li r4, 0
            bl SetMasterVolume__Q44nw4r3snd6detail9AxManagerFfi
            lfs f1, scSoundZeroF
            addi r3, r31, sBannerSoundPlayer__Q23ipl3snd@l
            bl setMasterVolume__17BannerSoundPlayerFf
            addi r11, r1, 0x20
            bl _restgpr_26
            lwz r0, 0x24(r1)
            mtlr r0
            addi r1, r1, 0x20
            blr
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

        void System::stopBannerSound(int unk) {
            sBannerSoundPlayer.stop(unk);
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
