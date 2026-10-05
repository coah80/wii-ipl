#include <egg/core.h>
#include <egg/prim.h>

#include <nw4r/snd.h>

#include <revolution/ai.h>
#include <revolution/ax.h>

namespace EGG {
    IAudioMgr::Arg::Arg() {
        pHeap = NULL;

        soundThreadPrio = nw4r::snd::SoundSystem::DEFAULT_SOUND_THREAD_PRIORITY;
        dvdThreadPrio = nw4r::snd::SoundSystem::DEFAULT_DVD_THREAD_PRIORITY;

        reserved = 0;
    }

    SimpleAudioMgr::SimpleAudioMgrArg::SimpleAudioMgrArg() {
        soundHeapSize = DEFAULT_SOUND_HEAP_SIZE;
    }

    SimpleAudioMgr::SimpleAudioMgr() : ArcPlayer(&getSoundHeap()) {
    }

    SoundHeapMgr::SoundHeapMgr() {}

    SimpleAudioMgr::~SimpleAudioMgr() {
    }

    void SimpleAudioMgr::initialize(Arg* arg_) {
        SimpleAudioMgrArg* pArg = static_cast<SimpleAudioMgrArg*>(arg_);

        AIInit(NULL);
        AXInit();

        nw4r::snd::SoundSystem::InitSoundSystem(pArg->soundThreadPrio, pArg->dvdThreadPrio);

        if (pArg->soundHeapSize > 0 && pArg->pHeap != NULL) {
            Allocator allocator(pArg->pHeap);
            createSoundHeap(&allocator, pArg->soundHeapSize);
        }
    }

    void SimpleAudioMgr::calc() {
        ArcPlayer::calc();
    }
}  // namespace EGG
