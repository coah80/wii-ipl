#ifndef IPL_SCENE_ADDRESS_H
#define IPL_SCENE_ADDRESS_H

#include "iplSceneHeader.h"
#include "scene/button/iplButton.h"

#include <revolution/nwc24.h>

namespace ipl {
    namespace layout {
        class Object;
    }

    namespace scene {
        class FriendListCache {
        public:
            void fin();
            const NWC24FriendInfo& getInfo(int index) const { return mInfos[index]; }

        private:
            NWC24FriendInfo mInfos[100];
        };

        FADER_SCENE_CLASS(Address), public ButtonEventHandlerBase {
        public:
            Address(EGG::Heap * heap, int);
            virtual ~Address();
            virtual void create();
            virtual void destroy() override;
            virtual void draw();

            enum {
                SCENE_ADD_WII = 1,
                SCENE_ADD_EMAIL,
            };

            int getChosenFriendIndex() {
                return unk_0xC0;
            }
            FriendListCache* getFriendCache() {
                return unk_0x274;
            }

        private:
            class MiiObj {
            public:
                u8 unk_0x0[0x20];
                void* unk_0x20;
                void* unk_0x24;
            };

            u8 unk_0x64[0x28];
            ipl::layout::Object* mLayout;
            u8 unk_0x90[0x0C];
            ipl::layout::Object* mPaneLayout;
            ipl::layout::Object* mCursorLayout;
            u8 unk_0xA4[8];
            int mState;
            int mPage;
            int mPageCount;
            int mFriendCount;
            int mSelectedButton;
            int unk_0xC0;
            u8 unk_0xC4[0x20];
            MiiObj mMiiObjA[5];
            MiiObj mMiiObjB[5];
            FriendListCache* unk_0x274;
            u8 unk_0x278[0x28];
        };
    }  // namespace scene
}  // namespace ipl

#endif  // IPL_SCENE_ADDRESS_H
