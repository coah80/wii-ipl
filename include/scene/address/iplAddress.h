#ifndef IPL_SCENE_ADDRESS_H
#define IPL_SCENE_ADDRESS_H

#include "iplSceneUIHeader.h"

#include "scene/button/iplButton.h"

#include "system/iplNigaoe.h"

#include <revolution/nwc24.h>
#include <revolution/nwc24/NWC24Friend.h>

namespace ipl {
    namespace scene {
        class Address;

        class FriendListCache {
        public:
            FriendListCache() {
                mbOpened = FALSE;
            }

            BOOL    init();
            void    fin();

            void    add(u32 index, const NWC24FriendInfo& info);
            void    update(u32 index, const wchar_t* name, NWC24UserId userId);
            void    del(u32 index);
            void    swap(u32 indexA, u32 indexB);

            BOOL    isValidId(const NWC24UserId& userId);
            BOOL    isDupId(const NWC24UserId& userId);
            BOOL    isDupMail(const char* mail);

            void    sendRegisterMail(u32 index);

            int     check();

            int     getErrCode() const;

            const NWC24FriendInfo& getInfo(int index) const { return mInfos[index]; }

            friend class Address;

        private:
            NWC24FriendInfo mInfos[100];        // 0x0000
            u8              mbHasInfo[100];     // 0x7D00
            u8              unk_0x7D64[4];      // 0x7D64
            NWC24UserId     mMyUserId;          // 0x7D68
            u32             mNumRegInfos;       // 0x7D70
            u8              unk_0x7D74[0x2000]; // 0x7D74
            int             mUnk_0x9D74;        // 0x9D74
            bool            mbOpened;           // 0x9D78
        };

        class AddressEvent : public ::gui::EventHandler {
        public:
            AddressEvent(Address* instance) : mpInstance(instance) {}

            virtual void onEvent(u32 compId, u32 event, void* data);  // 0x08

        private:
            Address*    mpInstance;    // 0x0C
            int         mDragChannel;  // 0x10
        };

        FADER_SCENE_CLASS(Address), public ButtonEventHandlerBase {
            friend class AddressEvent;

        public:
            enum {
                SCENE_ADD_WII = 1,
                SCENE_ADD_EMAIL,
            };

            class MiiObj {
            public:
                MiiObj() {
                    mpNigaoeObj = NULL;
                }
                ~MiiObj();

                void init(nw4r::lyt::Pane* pane);
                void reset();
                void set(NWC24UserId userId);

                static void create_callback(nigaoe::Object* nigaoe, void* work);

                friend class Address;

            private:
                GXTexObj             mMiiTexObj;      // 0x00
                nigaoe::Object*      mpNigaoeObj;     // 0x20
                nw4r::lyt::Material* mpMaterial;      // 0x24
            };

            Address(EGG::Heap* heap, int arg2);
            virtual ~Address();  // 0x08

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

            int getChosenFriendIndex() const { return mChosenFriendIndex; }
            FriendListCache* getFriendCache() const { return mpFriendList; }

        protected:
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

            void add_translate(nw4r::lyt::Pane* pane, const math::VEC2& pos);

            void set_friend(const char* paneName, u32 index, u32 buttonNo, MiiObj& mii, bool bBackup);
            void set_page_text(const char* paneName, int page);
            void set_textbox(const char* paneName, const wchar_t* text);
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

            void reset_gui(bool bPage);
            BOOL is_selectable(u32 index);
            BOOL isReleasableArea(int page, int buttonNo);

            void changePage_onDrag();
            void movePane_onDrag();

            void set_err_msg(wchar_t* buf, u32 bufLen, NWC24Err err);
            void entry_friend();

            void onNextPage();
            void onPreviousPage();

        private:
            nw4r::math::VEC2 mDragPos;          // 0x64
            int             mDragChannel;       // 0x6C
            int             mDragPageNo;        // 0x70
            int             mDragButtonNo;      // 0x74
            int             mRightPageNo;       // 0x78
            int             mLeftPageNo;        // 0x7C
            int             mUnk_0x80;          // 0x80
            u8              mbDragging;         // 0x84
            u8              unk_0x85[3];        // 0x85
            int             mArg2;              // 0x88
            layout::Object* mpLayout;           // 0x8C
            layout::Object* mpLayoutUnused;     // 0x90
            AddressEvent*   mpEvent;            // 0x94
            gui::PaneManager* mpGui;            // 0x98
            layout::Object* mpBackLayout;       // 0x9C
            layout::Object* mpDialogLayout;     // 0xA0
            int             mFisttState;        // 0xA4
            int             mCounter;           // 0xA8
            int             mState;             // 0xAC
            int             mPageNo;            // 0xB0
            int             mMaxPage;           // 0xB4
            int             mUnk_0xb8;          // 0xB8
            int             mUnk_0xbc;          // 0xBC
            int             mChosenFriendIndex; // 0xC0
            u8              mbHovered[5];       // 0xC4
            u8              unk_0xC9[3];        // 0xC9
            int             mPaneFlags[5];      // 0xCC
            u8              mbFlagE0;           // 0xE0
            u8              mbFlagE1;           // 0xE1
            u8              unk_0xE2[2];        // 0xE2
            MiiObj          mMiiB[5];           // 0xE4
            MiiObj          mMiiC[5];           // 0x1AC
            FriendListCache* mpFriendList;      // 0x274
            GXTexObj        mMiiTexObj;         // 0x278
            u8*             mpWork;             // 0x298
            f32             mUnk_0x29C;         // 0x29C
        };

    }  // namespace scene
}  // namespace ipl

#endif  // IPL_SCENE_ADDRESS_H
