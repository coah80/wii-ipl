#ifndef EGG_AUDIO_HEAP_MGR_H
#define EGG_AUDIO_HEAP_MGR_H

#include <egg/core/eggAllocator.h>
#include <egg/core/eggHeap.h>

#include <nw4r/snd.h>

#include <revolution/os.h>

namespace EGG {
    // Forward declarations
    class Allocator;
    class Heap;

    class SoundHeapMgr {
    public:
        SoundHeapMgr();

        ~SoundHeapMgr() { destroySoundHeap(); }

        virtual bool loadState(s32 id) NO_INLINE {
            if (id > 0 && mHeap.GetCurrentLevel() >= id) {
                mHeap.LoadState(id);
                return true;
            }
            return false;
        }
        virtual s32 getCurrentLevel() NO_INLINE { return mHeap.GetCurrentLevel(); }

        s32 saveState() { return mHeap.SaveState(); }

        nw4r::snd::SoundHeap& getSoundHeap() { return mHeap; }

        void createSoundHeap(Heap* pHeap, u32 size);
        void createSoundHeap(Allocator* pAllocator, u32 size);
        void destroySoundHeap();

    protected:
        nw4r::snd::SoundHeap mHeap;  // 0x04
    };
}  // namespace EGG

#endif  // EGG_AUDIO_HEAP_MGR_H
