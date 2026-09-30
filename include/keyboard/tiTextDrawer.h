#ifndef TEXTINPUT_TEXT_DRAWER_H
#define TEXTINPUT_TEXT_DRAWER_H

#include <revolution/types.h>
#include <revolution/mem/allocator.h>

#include <nw4r/ut/CharWriter.h>
#include <nw4r/ut/Rect.h>

namespace textinput {
    namespace textdrawer {
        class Base : nw4r::ut::CharWriter {
            public:
                typedef struct ViewPort {
                    f32 xOrig;  // 0x00
                    f32 yOrig;  // 0x04
                    f32 wd;     // 0x08
                    f32 ht;     // 0x0C
                    f32 nearZ;  // 0x10
                    f32 farZ;   // 0x14
                } ViewPort;

                typedef struct CursorPos {
                    u32 uCursorPos; // 0x00
                    f32 fCursorX;   // 0x04
                    f32 fCursorY;   // 0x08
                } CursorPos;

                typedef struct DrawInfo {
                    nw4r::ut::Rect rect;      // 0x00
                    wchar_t character;        // 0x10
                    u8  unk_0x12[14];         // 0x12
                } DrawInfo;

                virtual void                create(MEMAllocator* allocator);
                virtual void                draw(CursorPos* cursorPos);
                virtual void                draw();

                virtual void                setDrawString(const wchar_t* wcString, u32 startPos, u32 endPos);

                virtual void                setAspectRatio(bool aspect4x3);
                virtual void                setVIWidth(float fVIWidth);

                virtual void                beginDraw(const nw4r::ut::Rect& rect);
                virtual void                endDraw();

                virtual f32                 getLineHeight();

                virtual void                setFont(const nw4r::ut::Font& font);

                virtual f32                 getWidth(const wchar_t* sz);
                virtual int                 getLine();

                virtual nw4r::math::VEC2    getScale() const = 0;

                virtual void                setSecretModeOn(bool secretMode);

                virtual void                doBeforeDrawProcess(const wchar_t*, u32, const DrawInfo& drawInfo);
                virtual void                doAfterDrawProcess(const wchar_t*, u32, const DrawInfo& drawInfo);
                virtual void                preDraw(u32);
                virtual void                finishDraw(u32);

                virtual void                doLineFeed();

                virtual void                put(wchar_t wc);
                virtual void                procCursor(CursorPos* cursorPos, s32);
                virtual bool                onCursor(CursorPos* cursorPos);

                virtual void                makeUpCursorPos(CursorPos* cursorPos, u32 pos, s32 startLine, s32 endLine);
                virtual void                drawCursor(f32 x, f32 y);

                virtual void                calcRect(DrawInfo& drawInfo);

                virtual u32                 getStartPos() const;
                virtual u32                 getEndPos() const;

                // todo
                virtual void                setDrawModifyScopeLine(s32, s32);
                virtual void                setDrawCacheScopeLine(s32, s32);
                virtual void                modifyCursorCache(s32, u32, f32, f32, f32, f32);
                virtual bool                isEnableCursorCache() const;
                virtual s32                 getDrawModifyStartLine() const;
                virtual s32                 getDrawModifyEndLine() const;
                virtual u32                 getDrawCacheStartPos() const;
                virtual void                dirtyDrawCache();
                virtual void                dirtyCursorCache();

            protected:
                const wchar_t* mpDrawString;           // 0x50
                ViewPort mSavedViewport;               // 0x54
                f32 mSavedProjection[7];               // 0x6C
                nw4r::ut::Rect mProjectionRect;        // 0x88
                f32 mfVIWidth;                         // 0x98
                bool mbAspect4x3;                      // 0x9C
                bool mbDrawClipped;                    // 0x9D
                s32 muLine;                            // 0xA0
                f32 mfLineSpacing;                     // 0xA4
                f32 mfCharacterSpacing;                // 0xA8
                f32 mfFontWidth;                       // 0xAC
                f32 mfFontHeight;                      // 0xB0
                f32 mfModifyStartY;                    // 0xB4
                f32 mfMinScrollY;                      // 0xB8
                u32 muDrawStartPos;                    // 0xBC
                u32 muDrawEndPos;                      // 0xC0
                u32 muDrawCacheStartPos;               // 0xC4
                bool    mbSecretMode;                  // 0xC8
                s32 muDrawModifyStartLine;             // 0xCC
                s32 muDrawModifyEndLine;               // 0xD0
                s32 muDrawModifyStartPos;              // 0xD4
                s32 muDrawModifyEndPos;                // 0xD8
                u32 muCachedStartPos;                  // 0xDC
                u32 muCachedEndPos;                    // 0xE0
                bool mbDrawCache;                      // 0xE4
                f32 mfCachedCursorX;                   // 0xE8
                f32 mfCachedCursorY;                   // 0xEC
                f32 mfDrawScrollY;                     // 0xF0
                s32 mnCachedCursorLine;                // 0xF4
                CursorPos mCachedCursor;               // 0xF8
                bool mbCursorCache;                    // 0x104
                bool mbMaintainCursorCache;            // 0x105
        };
    }
}

#endif // TEXTINPUT_TEXT_DRAWER_H
