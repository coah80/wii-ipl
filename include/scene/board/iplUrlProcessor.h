#ifndef IPL_SCENE_URL_PROCESSOR_H
#define IPL_SCENE_URL_PROCESSOR_H

#include <revolution/types.h>

#include <nw4r/math/types.h>
#include <nw4r/ut/LinkList.h>
#include <nw4r/ut/List.h>
#include <nw4r/ut/WideTagProcessor.h>

#include <revolution/wpad.h>

namespace ipl {
    namespace scene {
        class UrlProcessor : public nw4r::ut::WideTagProcessor {
        public:
            static const wchar_t SEPERATOR = 0x1A;

            class line_collision {
            public:
                line_collision() : mLeft(0.0f), mRight(0.0f), mY(0.0f) {}

                f32 mLeft;
                f32 mRight;
                f32 mY;
                nw4r::ut::Link mLinkList;  // 0x0C
            };

            class url_collision {
            public:
                url_collision();
                ~url_collision();

                int mTagNo;
                wchar_t* mpStart;
                wchar_t* mpEnd;
                nw4r::ut::Link mLinkList;        // 0x0C
                nw4r::ut::List mLineCollisions;  // 0x14
            };

            UrlProcessor();

            nw4r::ut::Operation Process(u16 code, nw4r::ut::PrintContext<wchar_t>* context);

            void init();
            void update();

            void destroy();

            void clear_prev_drawing();

            void make_collision(nw4r::ut::PrintContext<wchar_t>* context, u16 code);
            void parse(nw4r::ut::PrintContext<wchar_t>* context);

            BOOL is_focused() const;
            void select(int tagNo);

            int get_focused_tagno(int chan) const;
            url_collision* get_selected_col();

            void get_url(char* urlOut, u32 urlLen);

            void setHitYOffset(f32 val) { mHitYOffset = val; }
            void setMemoTranslateY(f32 val) { mMemoTranslateY = val; }
            void setFocusEnabled(bool val) { mbFocusEnabled = val; }

            u8 getColorPass() const { return mbColorPass; }
            void setColorPass(u8 val) { mbColorPass = val; }

        private:
            typedef struct {
                nw4r::math::VEC2 pos;
                bool valid;
            } con_data;

            con_data mConData[WPAD_MAX_CONTROLLERS];  // 0x00
            nw4r::ut::List mUrlCollisions;            // 0x34
            f32 mHitYOffset;
            f32 mMemoTranslateY;
            int mCurTagNo;
            int mSelectedTagNo;
            u8 mbColorPass;
            u8 mbInTag;
            u8 mbHoverOffset;
            u8 mbFocusEnabled;
        };
    }  // namespace scene
}  // namespace ipl

#endif  // IPL_SCENE_URL_PROCESSOR_H
