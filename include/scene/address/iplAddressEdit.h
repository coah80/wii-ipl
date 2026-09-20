#ifndef IPL_SCENE_ADDRESS_EDIT_H
#define IPL_SCENE_ADDRESS_EDIT_H

#include "iplSceneHeader.h"

namespace ipl {
    namespace scene {
        FADER_SCENE_CLASS(AddressEdit) {
        public:
            AddressEdit(EGG::Heap * heap, int friendCode);

            void stt_msg_code_add();

            class String {
            public:
                void clear();
                const wchar_t* getDispCodeLong() const;
            };

            enum {
                SCENE_ADD_WII = 1,
                SCENE_ADD_EMAIL,
            };

        private:
            u8 unk_0x58[0x498];
        };
    }  // namespace scene
}  // namespace ipl

#endif  // IPL_SCENE_ADDRESS_EDIT_H
