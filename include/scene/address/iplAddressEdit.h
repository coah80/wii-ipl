#ifndef IPL_SCENE_ADDRESS_EDIT_H
#define IPL_SCENE_ADDRESS_EDIT_H

#include "iplSceneHeader.h"
#include "scene/button/iplButton.h"

#include <RFL_Types.h>
#include <revolution/nwc24.h>

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
            void reset_gui();
            void start_point_event(const char* paneName, controller::Interface* controller);
            void start_left_event(const char* paneName);
            void start_trig_event(const char* paneName);
            void start_ipt_point_event(const char* paneName, int channel);
            void start_ipt_left_event(const char* paneName, int channel);
            void start_ipt_trig_event(const char* paneName, int channel);
            int get_button_no(const char*);
            void add_friendinfo();
            void delete_friendinfo();
            void set_textbox(nw4r::lyt::Pane*, const wchar_t*);
            void setDefaultTitleText(const wchar_t*, bool);
            static void wiiid_utf16(u64, wchar_t*);
            static void nigaoe_create_callback_add(ipl::nigaoe::Object*, void*);
            static void nigaoe_create_callback_edit(ipl::nigaoe::Object*, void*);
            void set_err_msg(wchar_t*, u32, NWC24Err);
            void get_friendinfo();
            static u64 utf16_wiiid(const wchar_t*);
            void stt_add_code_fadein();
            void stt_add_code_fadeout();
            void stt_add_code_input();
            void stt_add_code_normal();
            void stt_add_confirm_fadein();
            void stt_add_confirm_fadeout();
            void stt_add_confirm_normal();
            void stt_add_mii_fadein();
            void stt_add_mii_fadeout();
            void stt_add_mii_input();
            void stt_add_mii_normal();
            void stt_add_name_fadein();
            void stt_add_name_fadeout();
            void stt_add_name_input();
            void stt_add_name_normal();
            void stt_ipt_input();
            void stt_ipt_normal();
            void stt_ipt_wait_fadein();
            void stt_ipt_wait_fadeout();
            void stt_msg_add_rlt();
            void stt_msg_code_invalid();
            void stt_msg_del_rlt();
            void stt_msg_dup_email();
            void stt_msg_dup_wii_no();
            void stt_msg_my_wii_no();
            void stt_msg_net();
            void stt_msg_no_established();
            void stt_msg_no_mii();
            void stt_msg_no_mii_add();
            void stt_msg_wc();
            void stt_select_mii();
            void stt_wait_btn_fadein();
            void stt_wait_btn_fadeout();
            void stt_wait_del_msg_fadein();
            void stt_wait_del_msg_fadeout();
            void stt_wait_del_msg_fadeout_to_rlt();
            void stt_wait_delete();
            void stt_wait_decide_anm_add();
            void stt_wait_parental();
            void stt_wait_parental_dst();
            void stt_wait_parental_dst_wc();
            void stt_wait_parental_wc();
            void stt_normal();
            void stt_wait_decide_anm();
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
                BOOL isDupCode() const;

                wchar_t mValue[0x102];
                wchar_t mName[0x0c];
                wchar_t mDisplayText[0x102];
                bool mbValidMail;
                bool mbNameNotEmpty;
                bool mbHasWiiNo;
                AddressEdit* mpCallbackOwner;
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
            bool mbParentalOK;
            nigaoe::Object* mpNigaoe;
            RFLCreateID mCreateID;
            int mNigaoeState;
            FriendListCache* mpFriendCache;
        };
    }  // namespace scene
}  // namespace ipl

#endif  // IPL_SCENE_ADDRESS_EDIT_H
