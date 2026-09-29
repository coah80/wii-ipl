#ifndef IPL_SCENE_ADDRESS_EDIT_H
#define IPL_SCENE_ADDRESS_EDIT_H

#include "iplSceneUIHeader.h"

#include "scene/button/iplButton.h"

#include "system/iplNigaoe.h"

#include <revolution/nwc24.h>
#include <revolution/nwc24/NWC24Friend.h>

namespace ipl {
    namespace scene {
        FADER_SCENE_CLASS(AddressEdit), public ButtonEventHandlerBase {
        public:
            AddressEdit(EGG::Heap* heap, int friendCode);
            virtual ~AddressEdit();  // 0x08

            virtual void prepare();
            virtual void create();
            virtual void draw();
            virtual void destroy();

            virtual void initCalcNormal();
            virtual void initCalcFadeout();

            virtual FaderSceneCommand calcFadein();
            virtual FaderSceneCommand calcNormal();
            virtual FaderSceneCommand calcFadeout();

            virtual void calcCommonAfter();

            virtual void onEventDerived(u32 compId, u32 event, const controller::Interface* con);  // 0x88

            class String {
            public:
                void clear();
                const wchar_t* getDispCodeLong() const;
                void setEMail(const wchar_t* email);
                bool isDupCode() const;
                bool isMyCode() const;

            private:
                u8 unk_0x00[0x424];
            };

            enum {
                SCENE_ADD_WII = 1,
                SCENE_ADD_EMAIL,
            };

            void stt_normal();
            void stt_wait_decide_anm();
            void stt_wait_btn_fadein();
            void stt_wait_btn_fadeout();
            void stt_wait_del_msg_fadein();
            void stt_wait_del_msg_fadeout();
            void stt_wait_delete();
            void stt_wait_del_msg_fadeout_to_rlt();
            void stt_msg_del_rlt();
            void stt_ipt_wait_fadein();
            void stt_ipt_normal();
            void stt_ipt_input();
            void stt_ipt_wait_fadeout();
            void stt_add_code_fadein();
            void stt_add_code_normal();
            void stt_add_code_input();
            void stt_msg_code_invalid();
            void stt_msg_dup_wii_no();
            void stt_msg_dup_email();
            void stt_msg_my_wii_no();
            void stt_add_code_fadeout();
            void stt_add_name_fadein();
            void stt_add_name_normal();
            void stt_add_name_input();
            void stt_add_name_fadeout();
            void stt_add_mii_fadein();
            void stt_add_mii_normal();
            void stt_add_mii_input();
            void stt_msg_no_mii_add();
            void stt_add_mii_fadeout();
            void stt_add_confirm_fadein();
            void stt_add_confirm_normal();
            void stt_add_confirm_fadeout();
            void stt_wait_decide_anm_add();
            void stt_msg_code_add();
            void stt_msg_code_edit();
            void stt_msg_no_mii();
            void stt_select_mii();
            void stt_msg_add_rlt();
            void stt_msg_net();
            void stt_wait_parental();
            void stt_wait_parental_dst();
            void stt_msg_wc();
            void stt_wait_parental_wc();
            void stt_wait_parental_dst_wc();
            void stt_msg_parental();
            void stt_msg_nwc24_error();
            void stt_msg_no_established();

            void set_textbox(nw4r::lyt::Pane* pane, const wchar_t* text);

            static void nigaoe_create_callback_edit(nigaoe::Object* nigaoe, void* work);
            static void nigaoe_create_callback_add(nigaoe::Object* nigaoe, void* work);

            void start_point_event(const char* paneName, controller::Interface* con);
            void start_left_event(const char* paneName);
            void start_trig_event(const char* paneName);
            void start_ipt_trig_event(const char* paneName, int chan);
            void start_ipt_point_event(const char* paneName, int chan);
            void start_ipt_left_event(const char* paneName, int chan);

            int get_button_no(const char* paneName);

            void reset_gui();
            void add_friendinfo();
            void get_friendinfo();
            void delete_friendinfo();
            void update_friendinfo();

            u64 utf16_wiiid(const wchar_t* text);
            void wiiid_utf16(u64 userId, wchar_t* text);

            void setDefaultTitleText(const wchar_t* text, bool flag);

            void set_err_msg(wchar_t* buf, u32 bufLen, NWC24Err err);

        private:
            u8 unk_0x64[0x48c];
        };

        class AddressEditEvent : public ::gui::EventHandler {
        public:
            AddressEditEvent(void* instance) : mpInstance(instance) {}
            virtual void onEvent(u32 compId, u32 event, void* data);  // 0x08

        private:
            void* mpInstance;  // 0x0C
        };

        class AddressInputEvent : public ::gui::EventHandler {
        public:
            AddressInputEvent(void* instance) : mpInstance(instance) {}

            virtual void onEvent(u32 compId, u32 event, void* data);  // 0x08

        private:
            void* mpInstance;  // 0x0C
        };


    }  // namespace scene
}  // namespace ipl

#endif  // IPL_SCENE_ADDRESS_EDIT_H
