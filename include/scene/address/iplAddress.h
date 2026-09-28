#ifndef IPL_SCENE_ADDRESS_H
#define IPL_SCENE_ADDRESS_H

#include "iplSceneUIHeader.h"

#include "scene/button/iplButton.h"

#include <revolution/nwc24.h>

namespace ipl {
    namespace nigaoe {
        class Object;
    }

    namespace scene {
        class AddressEvent;

        class FriendListCache {
        public:
            enum {
                FRIEND_MAX = 100,
            };

            FriendListCache() : mbOpened(false) {}

            BOOL init();
            void fin();

            void add(u32 index, const NWC24FriendInfo& info);
            void update(u32 index, const wchar_t* name, u64 fdId);
            void del(u32 index);
            void swap(u32 index1, u32 index2);

            BOOL isValidId(const NWC24UserId& userId);
            BOOL isDupId(const NWC24UserId& userId);
            BOOL isDupMail(const char* mailAddr);

            void sendRegisterMail(u32 index);

            s32 check();
            s32 getErrCode() const;

            const NWC24FriendInfo& getInfo(int index) const { return mInfos[index]; }
            bool isThere(u32 index) const { return mbThere[index]; }
            u32 getRegFriendNum() const { return mRegFriendNum; }
            NWC24UserId getMyUserId() const { return mMyUserId; }
            s32 getLastErr() const { return mErrCode; }

        private:
            NWC24FriendInfo mInfos[FRIEND_MAX];  // 0x0000
            bool mbThere[FRIEND_MAX];            // 0x7D00
            NWC24UserId mMyUserId;               // 0x7D68
            u32 mRegFriendNum;                   // 0x7D70
            u8 mSendWork[0x2000];                // 0x7D74
            s32 mErrCode;                        // 0x9D74
            bool mbOpened;                       // 0x9D78
        };

        FADER_SCENE_CLASS(Address), public ButtonEventHandlerBase {
        public:
            Address(EGG::Heap * heap, int mode);
            virtual ~Address();

            virtual void prepare();
            virtual void create();
            virtual void draw();
            virtual void destroy();

            virtual FaderSceneCommand calcFadein();

            virtual void initCalcNormal();
            virtual FaderSceneCommand calcNormal();

            virtual void initCalcFadeout();
            virtual FaderSceneCommand calcFadeout();

            virtual void calcCommonAfter();

            virtual void onEventDerived(u32 compId, u32 event, const controller::Interface* con);

            enum {
                SCENE_ADD_WII = 1,
                SCENE_ADD_EMAIL,
            };

            enum {
                BTN_MAX = 5,
                BTN_SPACE_MAX = BTN_MAX - 1,
                PAGE_MAX = 20,
            };

            int getChosenFriendIndex() {
                return mChosenFriend;
            }
            FriendListCache* getFriendCache() {
                return mpFriendCache;
            }

        private:
            enum {
                FADEIN_STATE_WAIT_OPEN = 0,
                FADEIN_STATE_FADEIN,
                FADEIN_STATE_DONE,
            };

            enum {
                STATE_INIT = 0,
                STATE_COVER_NORMAL,
                STATE_COVER_FORWARD,
                STATE_COVER_BACKWARD,
                STATE_NORMAL,
                STATE_FORWARD,
                STATE_BACKWARD,
                STATE_LOOP_FORWARD,
                STATE_LOOP_BACKWARD,
                STATE_DECIDE,
                STATE_DRAG,
                STATE_RELEASE,
                STATE_WAIT_CHILD_CST,
                STATE_WAIT_CHILD_DST,
                STATE_WAIT_CHILD_FADEOUT,
                STATE_MSG_NET,
                STATE_WAIT_PARENTAL,
                STATE_WAIT_PARENTAL_DST,
                STATE_MSG_WC,
                STATE_WAIT_PARENTAL_WC,
                STATE_WAIT_PARENTAL_DST_WC,
                STATE_MSG_NWC24_ERROR,
                STATE_MSG_FI_FULL,
                STATE_MSG_PARENTAL,
                STATE_MSG_OPEN_FAILURE,
                STATE_WAIT_DIALOG,
                STATE_DONE,
            };

            class MiiObj {
            public:
                MiiObj();
                ~MiiObj();

                void init(nw4r::lyt::Pane* pane);
                void set(u64 fdId);
                void reset();

                static void create_callback(nigaoe::Object* object, void* work);

                GXTexObj mTexObj;                 // 0x00
                nigaoe::Object* mpNigaoe;         // 0x20
                nw4r::lyt::Material* mpMaterial;  // 0x24
            };

            struct DragInfo {
                nw4r::math::VEC2 mPos;  // 0x00
                int mChan;        // 0x08
                int mPage;        // 0x0C
                int mButton;      // 0x10
                int mNextCount;   // 0x14
                int mPrevCount;   // 0x18
                int unk_0x1C;     // 0x1C
                bool mbDragging;  // 0x20
            };

            void fistt_wait_open();
            void fistt_fadein();

            void onInitFriendList();

            void stt_cover_normal();
            void stt_cover_forward();
            void stt_cover_backward();
            void stt_normal();
            void stt_forward();
            void stt_backward();
            void stt_loop_forward();
            void stt_loop_backward();
            void stt_decide();
            void stt_drag();
            void stt_release();
            void stt_wait_child_cst();
            void stt_wait_child_dst();
            void stt_wait_child_fadeout();
            void stt_msg_net();
            void stt_wait_parental();
            void stt_wait_parental_dst();
            void stt_msg_wc();
            void stt_wait_parental_wc();
            void stt_wait_parental_dst_wc();
            void stt_msg_nwc24_error();
            void stt_msg_fi_full();
            void stt_msg_parental();
            void stt_msg_open_failure();
            void stt_wait_dialog();

            void add_translate(nw4r::lyt::Pane* pane, const math::VEC2& offset);
            void set_friend(const char* paneName, u32 friendNo, u32 buttonNo, MiiObj& miiObj, bool bDrag);
            void set_page_text(const char* paneName, int page);
            void set_textbox(const char* paneName, const wchar_t* text);
            void set_textbox(const char* paneName, u32 msgId);
            void reset_friend();

            void start_point_event(const char* paneName, controller::Interface* con);
            void start_left_event(const char* paneName);
            void start_trig_event(const char* paneName);
            void start_drag_event(const char* paneName, const controller::Interface* con);
            void start_drag_point_event(const char* paneName, controller::Interface* con);
            void start_drag_left_event(const char* paneName);
            void start_release_event(const char* paneName);

            void on_point_event(int buttonNo, controller::Interface* con);
            void left_point_event(int buttonNo);

            int get_button_no(const char* paneName);
            int get_button_space_no(const char* paneName);

            void reset_gui(bool bKeepPointed);

            BOOL is_selectable(u32 friendNo);

            void onNextPage();
            void onPreviousPage();

            void set_err_msg(wchar_t* errMsg, u32 errMsgLen, NWC24Err err);

            void entry_friend();

            bool isReleasableArea(int page, int buttonNo);

            void changePage_onDrag();
            void movePane_onDrag();

            DragInfo mDrag;                     // 0x64
            int mMode;                          // 0x88
            layout::Object* mpLayout;           // 0x8C
            int unk_0x90;                       // 0x90
            AddressEvent* mpEvent;              // 0x94
            gui::PaneManager* mpGui;            // 0x98
            layout::Object* mpBackLayout;       // 0x9C
            layout::Object* mpDialogLayout;     // 0xA0
            int mFadeinState;                   // 0xA4
            int mWaitOpenCount;                 // 0xA8
            int mState;                         // 0xAC
            u32 mPage;                          // 0xB0
            int mNextPageNum;                   // 0xB4
            int mPrevPageNum;                   // 0xB8
            int mSelectedButton;                // 0xBC
            u32 mChosenFriend;                  // 0xC0
            bool mbFaceValid[BTN_MAX];          // 0xC4
            int mPointCount[BTN_MAX];           // 0xCC
            bool mbParentalOK;                  // 0xE0
            bool mbCover;                       // 0xE1
            MiiObj mMiiObj[BTN_MAX];            // 0xE4
            MiiObj mNextMiiObj[BTN_MAX];        // 0x1AC
            FriendListCache* mpFriendCache;     // 0x274
            GXTexObj mDragTexObj;               // 0x278
            u8* mpWork;                         // 0x298
            f32 mDragOffsetX;                   // 0x29C

            static const math::VEC2 smcPageOffset;

            friend class AddressEvent;
        };

        class AddressEvent : public ::gui::EventHandler {
        public:
            AddressEvent(Address* instance) : ::gui::EventHandler(), mpInstance(instance) {}

            virtual void onEvent(u32 compId, u32 event, void* data);

        private:
            Address* mpInstance;  // 0x0C
            int mTrigChan;        // 0x10
        };
    }  // namespace scene
}  // namespace ipl

#endif  // IPL_SCENE_ADDRESS_H
