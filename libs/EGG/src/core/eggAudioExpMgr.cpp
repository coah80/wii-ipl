#define EGG_AUDIO_EXPMGR_NO_INLINE_VIRTUALS
#include <egg/core.h>
#undef EGG_AUDIO_EXPMGR_NO_INLINE_VIRTUALS

namespace EGG {

// Declaring this unused subclass makes the @52@ adjustor thunks emit in the
// original order (@52@__dt__ before @52@calc). All of its emissions strip.
class Sample : public SimpleAudioMgrWithFx {
public:
    Sample() : SimpleAudioMgrWithFx() {}
    virtual ~Sample() {}
};

SimpleAudioMgrWithFx::SimpleAudioMgrWithFx() {
}

SimpleAudioMgrWithFx::~SimpleAudioMgrWithFx() {
}

SimpleAudioMgrWithFx::ArgWithFx::ArgWithFx() : fxArg() {
    // auto generates constructors
    SimpleAudioMgrArg unused0;
    AudioFxMgr::AudioFxMgrArg unused1;
}

void SimpleAudioMgrWithFx::initialize(IAudioMgr::Arg* arg) {
    SimpleAudioMgr::initialize(arg);

    if (arg != NULL) {
        arg = (IAudioMgr::Arg*)&((ArgWithFx*)arg)->fxArg;
    }

    initializeFx(&mHeap, (AudioFxMgrArg*)arg);

    setFxReverbHi(nw4r::snd::AUX_A, AudioFxMgr::getDefaultFxReverbHi());
    setFxChorus(nw4r::snd::AUX_B, AudioFxMgr::getDefaultFxChorus());

    mHeap.SaveState();
}

}  // namespace EGG
