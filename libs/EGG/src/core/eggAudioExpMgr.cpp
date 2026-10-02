#define EGG_AUDIO_EXPMGR_NO_INLINE_VIRTUALS

#include <egg/core.h>

namespace EGG {
    class Sample : public SimpleAudioMgrWithFx {
    public:
        Sample();
        virtual ~Sample();
    };

    Sample::Sample() {
    }

    Sample::~Sample() {
    }

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
