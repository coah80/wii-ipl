#ifndef IPL_SCENE_ADDRESS_EDIT_H
#define IPL_SCENE_ADDRESS_EDIT_H

#include "iplSceneHeader.h"
#include "scene/button/iplButton.h"

#include <RFL_Types.h>

namespace ipl {
    namespace nigaoe {
        class Object;
    }

    namespace scene {
        class AddressEditEvent;
        class AddressInputEvent;
        class FriendListCache;

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
            void update_friendinfo();
            void requestSceneChange(int sceneId, void* args) { reserveSceneChange(sceneId, args); }
            u32 getPreviousScene() const { return getPrevSceneID(); }
            EGG::Heap* getHeap() { return getSceneHeap(); }
            ::gui::Manager* getGuiManager() { return mpManager; }

            class String {
            public:
                void clear();
                const wchar_t* getDispCodeLong() const;
                void setName(const wchar_t* value);
                void setEMail(const wchar_t* value);
                void setWiiNo(const wchar_t* value);

                wchar_t mValue[0x102];
                wchar_t mName[0x0c];
                wchar_t mDisplayText[0x102];
                bool mbValidMail;
                bool mbNameNotEmpty;
                bool mbHasWiiNo;
            };

            enum {
                SCENE_ADD_WII = 1,
                SCENE_ADD_EMAIL,
            };

            int mState;
            layout::Object* mpCodeLayout;
            AddressEditEvent* mpEditEvent;
            gui::PaneManager* mpEditGui;
            layout::Object* mpNameLayout;
            AddressInputEvent* mpInputEvent;
            gui::PaneManager* mpInputGui;
            layout::Object* mpBackgroundLayout;
            int mMode;
            int mSelectedButton;
            int mSubState;
            s32 mPointCount[5];
            u32 mSelectedFriend;
            TextBalloon* mpBalloon;
            nand::LayoutFile* mpBalloonFile;
            String mString;
            AddressEdit* mpCallbackOwner;
            bool mbParentalOK;
            nigaoe::Object* mpNigaoe;
            RFLCreateID mCreateID;
            int mNigaoeState;
            FriendListCache* mpFriendCache;
        };
    }  // namespace scene
}  // namespace ipl

#endif  // IPL_SCENE_ADDRESS_EDIT_H
