#ifndef IPL_SCENE_BALLOON_H
#define IPL_SCENE_BALLOON_H

#include <revolution/mtx.h>
#include <revolution/types.h>

#include "layout/iplLayout.h"

namespace ipl {
    namespace scene {
        class TextBalloon {
        public:
            enum {
                WAIT_UNTIL_FADE_IN = 15
            };

            TextBalloon(EGG::Heap* heap, nand::LayoutFile* layoutFile, const char* directory, const char* fileName, const ipl::math::VEC3& initialPos,
                        f32 margin16x9 = 120.0f, f32 margin4x3 = 30.0f);
            ~TextBalloon();

            void calc();
            void draw();

            void init(const wchar_t* text, u32 texLen = 0);

            void terminate();

            void fadein();
            void fadeinNoSetTextbox();

            void fadeout();
            void fadeoutForce();

            void setPos(const math::VEC3& pos, bool use16x9X, int hAlign);
            void updatePos(const math::VEC3& pos);

            void set_translate(const math::VEC3& trans);
            void set_textbox(const wchar_t* text, BOOL bNoLimit = FALSE);

            void init_textbox(BOOL bNoLimit = FALSE) { set_textbox(mpText, bNoLimit); }

            layout::Object* get_layout() { return mpLayout; }

        private:
            void on_pre_fadein();
            void anm_fadein();

            void set_size(const char* paneName, const nw4r::lyt::Size& size);
            const nw4r::lyt::Size* get_size(const char* paneName);

            undefined4 mReserved;
            undefined4 mReservedState;
            BOOL mbWaitingFadeIn;  // 0x08

            layout::Object* mpLayout;  // 0x0C

            undefined4 unused_0x10;

            wchar_t* mpText;  // 0x14

            u32 mTextLen;            // 0x18
            math::VEC3 mBalloonPos;  // 0x1C
            undefined4 mHAlign;  // 0x28
            undefined mbUse16x9X;  // 0x2C
            f32 mMargin16x9;  // 0x30
            f32 mMargin4x3;  // 0x34

            int mWaitUntilFadeIn;  // 0x38

            static const int MAX_STRING_LENGTH = 32;
        };
    }  // namespace scene
}  // namespace ipl

#endif  // IPL_SCENE_TEXT_BALLOON_H
