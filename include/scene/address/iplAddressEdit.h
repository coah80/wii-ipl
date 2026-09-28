#ifndef IPL_SCENE_ADDRESS_EDIT_H
#define IPL_SCENE_ADDRESS_EDIT_H

#include "iplSceneHeader.h"
#include "scene/button/iplButton.h"

namespace ipl {
    namespace scene {
        FADER_SCENE_CLASS(AddressEdit), public ButtonEventHandlerBase {
        public:
            AddressEdit(EGG::Heap * heap, int friendCode);
            virtual ~AddressEdit();

            virtual void prepare();
            virtual void create();
            virtual void draw();

            virtual void initCalcNormal();
            virtual void initCalcFadeout();
            virtual void calcCommonAfter();

            virtual FaderSceneCommand calcFadein();
            virtual FaderSceneCommand calcNormal();
            virtual FaderSceneCommand calcFadeout();
            virtual void onEventDerived(u32 compId, u32 event, const controller::Interface* con);

            void stt_msg_code_add();
            void stt_msg_code_edit();
            void stt_msg_parental();
            void stt_msg_nwc24_error();

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
            u8 unk_0x64[0x48c];
        };
    }  // namespace scene
}  // namespace ipl

#endif  // IPL_SCENE_ADDRESS_EDIT_H
