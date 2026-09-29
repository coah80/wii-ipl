#ifndef IPL_SCENE_GC_SAVE_DATA_H
#define IPL_SCENE_GC_SAVE_DATA_H

#include <nw4r/ut.h>

#include "scene/memoryCard/iplMemoryCardBase.h"

#include "math/iplMathTypes.h"

namespace ipl {
    namespace scene {
        class GCSaveData : public MemoryBase {
            friend class MemoryCard;

        public:
            GCSaveData(EGG::Heap* heap, nand::LayoutFile* layoutFile, const char* directory, const char* fileName,
                       math::VEC3 translate);
            virtual ~GCSaveData();

            virtual void onPoint(const char* paneName, controller::Interface* controller);
            virtual void onLeft(const char* paneName);
            virtual void onTrig(const char* paneName);

            void calc();
            void draw();
            void update();
            void init();

            void                 setTranslate(const nw4r::math::VEC3& translate);
            const nw4r::math::VEC3* getTranslate();

            void setBalloon(TextBalloon* balloon);

        private:
            MemoryBaseEvent* mpEvent;   // 0x34
            TextBalloon*     mpBalloon; // 0x38
            u8               mSlot;     // 0x3C
            s16              mIndex;    // 0x3E
            nw4r::ut::Link   mLink;     // 0x40
        };
    }  // namespace scene
}  // namespace ipl

#endif  // IPL_SCENE_GC_SAVE_DATA_H
