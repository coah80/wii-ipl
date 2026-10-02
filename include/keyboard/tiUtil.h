#ifndef TEXTINPUT_UTIL_H
#define TEXTINPUT_UTIL_H

#include <revolution/types.h>

#include <nw4r/ut/Rect.h>

namespace textinput {
    namespace util {
#ifdef TIINPUTFORM_IMPLEMENTATION
        wchar_t HankakuToZenkaku(wchar_t ch);
#endif
        wchar_t toWLower(wchar_t ch);
        wchar_t toWUpper(wchar_t ch);

        wchar_t reverseLetterCaseW(wchar_t ch);

        wchar_t KBD_ConvertDakuten(wchar_t ch);
        wchar_t KBD_ConvertHandaku(wchar_t ch);
        wchar_t KBD_ConvertSmall(wchar_t ch);
        wchar_t KBD_ConvertAll(wchar_t ch);

#ifdef TISTRING_IMPLEMENTATION
        u32     KBD_IsDakuten(wchar_t ch);
        u32     KBD_IsHandaku(wchar_t ch);
        u32     KBD_IsSmall(wchar_t ch);
#else
        bool    KBD_IsDakuten(wchar_t ch);
        bool    KBD_IsHandaku(wchar_t ch);
        bool    KBD_IsSmall(wchar_t ch);
#endif

        bool    strcmp(const char* s1, const char* s2);
        void    replaceChar(char* dest, u32 destLen, const char* src, int replaceIdx, char newCh);
        bool    isAlphabet(wchar_t ch);

        f32     hermiteInterporation(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
    
        void    getProjectionRect4x3(nw4r::ut::Rect* rect);
        void    getProjectionRect16x9(nw4r::ut::Rect* rect);

        class AnimObserver {
            public:
            enum AnmEvent {
                AE_0,
                AE_1,
                // ...
                AE_Last
            };

            virtual void onAnmEvent(AnmEvent event, void*) = 0;
        };

        class Animation {
        public:
            Animation() : mfAnimationTime(0.0f), mbInAnimation(false), mbSE(false), mpAnimObserver(NULL) {}

#if defined(TIINPUTFORM_IMPLEMENTATION) || defined(MYTIMANAGER_IMPLEMENTATION)
            virtual void startAnm(f32 start, f32 end, f32 duration, AnimObserver* observer, void* data);
#else
            virtual void startAnm(AnimObserver*, f32, f32, f32, void*);
#endif  // 0x08
            virtual void calc();                                         // 0x0C
            virtual f32 getValue();                                      // 0x10
            virtual bool isActive();                                     // 0x14
            virtual void setSEFlag(bool);                                // 0x18
            virtual bool isSEFlag();                                     // 0x1C
            virtual void stop();                                         // 0x20

        private:
            f32 mfStartPoint;              // 0x04
            f32 mfEndPoint;                // 0x08
            f32 mfCurrentFrame;            // 0x0C
            f32 mfAnimationTime;           // 0x10
            bool mbInAnimation;            // 0x14
            bool mbSE;                     // 0x15
            AnimObserver* mpAnimObserver;  // 0x18
            void* mpData;                  // 0x1C
        };
    }  // namespace util
}  // namespace textinput

#endif  // TEXTINPUT_UTIL_H
