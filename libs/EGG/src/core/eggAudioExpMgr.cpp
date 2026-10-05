#define EGG_AUDIO_EXPMGR_NO_INLINE_VIRTUALS

#include <egg/core.h>

namespace EGG {
    SimpleAudioMgrWithFx::SimpleAudioMgrWithFx() {
    }

    SimpleAudioMgrWithFx::~SimpleAudioMgrWithFx() {
    }

    SimpleAudioMgrWithFx::ArgWithFx::ArgWithFx() : fxArg() {
        // auto generates constructors
        SimpleAudioMgrArg unused0;
        AudioFxMgr::AudioFxMgrArg unused1;
    }

    void SimpleAudioMgrWithFx::initialize(IAudioMgr::Arg* audioArgs) {
        SimpleAudioMgr::initialize(audioArgs);

        if (audioArgs != NULL) {
            audioArgs = (IAudioMgr::Arg*)&((ArgWithFx*)audioArgs)->fxArg;
        }

        initializeFx(&mHeap, (AudioFxMgrArg*)audioArgs);

        setFxReverbHi(nw4r::snd::AUX_A, AudioFxMgr::getDefaultFxReverbHi());
        setFxChorus(nw4r::snd::AUX_B, AudioFxMgr::getDefaultFxChorus());

        mHeap.SaveState();
    }

    ExpAudioMgr::ExpAudioMgr() {
    }

    ExpAudioMgr::~ExpAudioMgr() {
    }
}  // namespace EGG
