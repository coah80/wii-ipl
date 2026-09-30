#ifndef TEXTINPUT_TEXT_DRAWER_H
#define TEXTINPUT_TEXT_DRAWER_H

#include <revolution/types.h>
#include <revolution/mem/allocator.h>

#include <nw4r/ut/CharWriter.h>
#include <nw4r/ut/Rect.h>
#ifdef TIINPUTFORM_IMPLEMENTATION
#include <string.h>
#endif

namespace textinput {
    namespace textdrawer {
#if defined(MYTIMANAGER_IMPLEMENTATION) || defined(MYTIINPUTFORM_IMPLEMENTATION) || defined(TIINPUTFORM_IMPLEMENTATION)
        class Base : public nw4r::ut::CharWriter {
#else
        class Base : nw4r::ut::CharWriter {
#endif
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
#ifdef TIINPUTFORM_IMPLEMENTATION
                    nw4r::ut::Rect rect;
                    wchar_t character;
#else
                    u8  unk_0x00[32];
#endif
                } DrawInfo;

#ifdef TIINPUTFORM_IMPLEMENTATION
                Base() : mpDrawAllocator(NULL), mfViewX(0.0f), mfViewY(0.0f), mfViewWidth(0.0f), mfViewHeight(0.0f),
                    mfVIWidth(640.0f), mbAspect4x3(false), mbDrawClipped(false), muLine(0), mfLineSpacing(0.0f),
                    mfCharacterSpacing(0.0f), mfFontWidth(0.0f), mfFontHeight(0.0f), mfModifyStartY(0.0f), mfMinScrollY(0.0f),
                    muDrawStartPos(0), muDrawEndPos(65535), mbSecretMode(false), muDrawModifyStartLine(0), muDrawModifyEndLine(0),
                    muDrawModifyStartPos(0), muDrawModifyEndPos(0), muCachedStartPos(0), muCachedEndPos(0), mbDrawCache(false),
                    mfCachedCursorX(0.0f), mfCachedCursorY(0.0f), mfDrawScrollY(0.0f), muCachedCursorPosition(0),
                    mbCursorCache(false), mbMaintainCursorCache(true) { memset(&mCachedCursor, 0, sizeof(mCachedCursor)); }
#endif
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

                virtual void                setSecretModeOn(bool secretMode)    { mbSecretMode = secretMode; }

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
#ifdef TIINPUTFORM_IMPLEMENTATION
                virtual void                setDrawModifyScopeLine(s32 startLine, s32 endLine);
                virtual void                setDrawCacheScopeLine(s32 startLine, s32 endLine);
                virtual void                modifyCursorCache(s32 line, u32 position, f32 x, f32 y, f32 width, f32 height);
#else
                virtual void                setDrawModifyScopeLine();
                virtual void                setDrawCacheScopeLine();
                virtual void                modifyCursorCache();
#endif
#ifdef TIINPUTFORM_IMPLEMENTATION
                virtual bool                isEnableCursorCache() const;
#else
                virtual void                isEnableCursorCache();
#endif
#ifdef TIINPUTFORM_IMPLEMENTATION
                virtual u32                 getDrawModifyStartLine() const;
                virtual u32                 getDrawModifyEndLine() const;
#else
                virtual void                getDrawModifyStartLine();
                virtual void                getDrawModifyEndLine();
#endif
                virtual u32                 getDrawCacheStartPos() const;
                virtual void                dirtyDrawCache();
                virtual void                dirtyCursorCache();

#ifdef TIINPUTFORM_IMPLEMENTATION
            protected:
                MEMAllocator* mpDrawAllocator;
                u8 mDrawConfiguration[0x34];
                f32 mfViewX;
                f32 mfViewY;
                f32 mfViewWidth;
                f32 mfViewHeight;
                f32 mfVIWidth;
                bool mbAspect4x3;
                bool mbDrawClipped;
                u32 muLine;
                f32 mfLineSpacing;
                f32 mfCharacterSpacing;
                f32 mfFontWidth;
                f32 mfFontHeight;
                f32 mfModifyStartY;
                f32 mfMinScrollY;
                u32 muDrawStartPos;
                u32 muDrawEndPos;
                u32 muDrawCacheStartPos;
#else
            private:
                u8      unk_0x50[0x78];
#endif
                bool    mbSecretMode;   // 0xC8
#ifdef TIINPUTFORM_IMPLEMENTATION
                u32 muDrawModifyStartLine;
                u32 muDrawModifyEndLine;
                u32 muDrawModifyStartPos;
                u32 muDrawModifyEndPos;
                u32 muCachedStartPos;
                u32 muCachedEndPos;
                bool mbDrawCache;
                f32 mfCachedCursorX;
                f32 mfCachedCursorY;
                f32 mfDrawScrollY;
                u32 muCachedCursorPosition;
                CursorPos mCachedCursor;
                bool mbCursorCache;
                bool mbMaintainCursorCache;
#elif defined(MYTIINPUTFORM_IMPLEMENTATION)
            protected:
                u8 mDrawState[0x27];
                f32 mfDrawScrollY;
                u8 mDrawCacheState[0x14];
#else
                u8      unk_0xCC[0x3C];
#endif
        };
    }
}

#endif // TEXTINPUT_TEXT_DRAWER_H
