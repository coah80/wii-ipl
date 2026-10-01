#ifndef IPL_SCENE_MEMORY_CARD_BASE_H
#define IPL_SCENE_MEMORY_CARD_BASE_H

#include <nw4r/ut.h>

#include "layout/iplLayout.h"
#include "layout/iplGuiManager.h"

#include "system/iplController.h"

namespace ipl {
    namespace scene {
        class TextBalloon;
        class SettingButton;
        class MemoryBase;
    }
    namespace nand {
        class LayoutFile;
    }
    namespace scene {

        class MemoryBaseEvent : public ::gui::EventHandler {
        public:
#ifdef IPL_MEMORYCARD_BASE_EVENT_OUT_OF_LINE
            MemoryBaseEvent(MemoryBase* base);
#else
            MemoryBaseEvent(MemoryBase* base) : mpBase(base) {}
#endif

            virtual ~MemoryBaseEvent();

            virtual void onEvent(u32 componentID, u32 event, void* data);

        private:
            MemoryBase* mpBase;  // 0x0C
        };

#ifdef IPL_CHANNEL_TITLE_NOVTABLE
        class __declspec(novtable) MemoryBase {
#else
        class MemoryBase {
#endif
        public:
            class Anm {
            public:
                Anm(layout::GroupAnimator* anim) : mAnim(anim) {}
                virtual ~Anm();

                layout::GroupAnimator* mAnim;  // 0x04
                nw4r::ut::Link         mLink;  // 0x08
            };

            class Button {
            public:
                Button(nw4r::lyt::Pane* pane) : unk_0x04(0), mPane(pane) {}
                virtual ~Button();

                u32              unk_0x04;  // 0x04
                nw4r::lyt::Pane* mPane;     // 0x08
                nw4r::ut::Link   mLink;     // 0x0C
            };

            class AnmButton {
            public:
                AnmButton(const char* name, Anm* anm1, Anm* anm2, Anm* anm3)
                    : unk_0x04(0), mName(name), mCurrentAnm(NULL), mAnm1(anm1), mAnm2(anm2), mAnm3(anm3),
                      unk_0x24(0), mLastCmd(0), mpBalloon(NULL) {}
                virtual ~AnmButton();

                void calc();
                void onCmdRecv(int command);

                void setBalloon(TextBalloon* balloon);

                int              unk_0x04;     // 0x04
                const char*      mName;        // 0x08
                Anm*             mCurrentAnm;  // 0x0C
                Anm*             mAnm1;        // 0x10
                Anm*             mAnm2;        // 0x14
                Anm*             mAnm3;        // 0x18
                nw4r::ut::Link   mLink;        // 0x1C
                u32              unk_0x24;     // 0x24
                int              mLastCmd;     // 0x28
                TextBalloon*     mpBalloon;    // 0x2C
            };

            struct AnmName {
                const char* anmFile;
                const char* groupName;
            };

#ifdef IPL_MEMORYCARD_BASE_CTOR_OUT_OF_LINE
            MemoryBase();
#else
            MemoryBase() : mpLayout(NULL), unk_0x08(NULL) {
                nw4r::ut::List_Init(&mAnmList, offsetof(Anm, mLink));
                nw4r::ut::List_Init(&mButtonList, offsetof(Button, mLink));
                nw4r::ut::List_Init(&mAnmButtonList, offsetof(AnmButton, mLink));
            }
#endif
#ifdef IPL_MEMORYCARD_BASE_OUT_OF_LINE
            virtual ~MemoryBase();
#else
            virtual ~MemoryBase() {}
#endif

            virtual void onPoint(const char* paneName, controller::Interface* controller);
            virtual void onLeft(const char* paneName);
            virtual void onMove(const char* paneName);
            virtual void onTrig(const char* paneName);

            virtual void add_button(const char** paneNames, int count);
            virtual void add_anmbutton(const char* paneName, Anm* anm1, Anm* anm2, Anm* anm3);
            virtual Button* get_button(const char* paneName);
            virtual AnmButton* get_anmbutton(const char* paneName);
            virtual void clear_button(const char* paneName);
            virtual void add_animation(const AnmName* anmNames, int count);
            virtual Anm* get_animation(int index);
            virtual void do_animation(int index);
            virtual void do_animation(int index, bool flag);
            virtual void stop_animation(int index);
            virtual bool is_animation(int index);
            virtual bool is_fadein_enable();
            virtual void set_visible(const char* paneName, bool flag);

            void set_textbox(const char* paneName, u32 message);
            void set_textbox(const char* paneName, u32 message, int x, int y);
            void set_textbox(const char* paneName, const wchar_t* text, f32 x, f32 y);
            void set_textbox(const char* paneName, const wchar_t* text);
            SettingButton* get_setting_button();
            void change_button_text_close();
            void change_button_text_return();
            void change_button_text_ok();
            void show_button_return();
            void show_button_ok();

        protected:
            layout::Object*    mpLayout;        // 0x04
            nand::LayoutFile*  unk_0x08;        // 0x08
            gui::PaneManager*  mpPaneManager;   // 0x0C
            nw4r::ut::List     mAnmList;        // 0x10
            nw4r::ut::List     mButtonList;     // 0x1C
            nw4r::ut::List     mAnmButtonList;  // 0x28
        };
    }  // namespace scene
}  // namespace ipl

#endif  // IPL_SCENE_MEMORY_CARD_BASE_H
