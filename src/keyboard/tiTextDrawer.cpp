#define TITEXTDRAWER_IMPLEMENTATION
#include "keyboard/tiTextDrawer.h"
#include "keyboard/tiUtil.h"

#include <revolution/gx/GXCull.h>
#include <revolution/gx/GXGet.h>
#include <revolution/gx/GXTransform.h>
#include <revolution/mtx.h>

namespace textinput {
    namespace textdrawer {
        s32 snWidthTable[0x160];

        void Base::create(MEMAllocator*) {
            for (s32 index = 0; index < 0x160; ++index) {
                snWidthTable[index] = -1;
            }
            mfVIWidth = 640.0f;
        }

        void Base::setAspectRatio(bool aspect4x3) {
            mbAspect4x3 = aspect4x3;
            if (aspect4x3) {
                util::getProjectionRect4x3(&mProjectionRect);
            } else {
                util::getProjectionRect16x9(&mProjectionRect);
            }
        }

        void Base::setDrawString(const wchar_t* wcString, u32 startPos, u32 endPos) {
            mpDrawString = wcString;
            muDrawStartPos = startPos;
            muDrawEndPos = endPos;
        }

        void Base::modifyCursorCache(s32 line, u32 pos, f32 left, f32 top, f32 right, f32 bottom) {
            f32 height = mfDrawScrollY;
            mnCachedCursorLine = line;
            mCachedCursor.uCursorPos = pos;
            mCachedCursor.fCursorX = left;
            mCachedCursor.fCursorY = top - height;
            mfCachedCursorX = right;
            mfCachedCursorY = bottom - height;
            mbCursorCache = true;
        }

        void Base::setDrawModifyScopeLine(s32 startLine, s32 endLine) {
            muDrawModifyStartLine = startLine;
            muDrawModifyEndLine = endLine;
        }

        void Base::setDrawCacheScopeLine(s32 startLine, s32 endLine) {
            if (startLine < 0) {
                startLine = 0;
            }
            if (muDrawModifyStartPos != startLine) {
                dirtyDrawCache();
            }
            muDrawModifyStartPos = startLine;
            muDrawModifyEndPos = endLine;
        }

        void Base::procCursor(CursorPos* cursorPos, s32) {
            GetCursorX();
            GetCursorY();
            if (!onCursor(cursorPos)) {
                cursorPos->fCursorX = GetCursorX();
                cursorPos->fCursorY = GetCursorY();
            }
        }

        bool Base::onCursor(CursorPos*) {
            return false;
        }

        void Base::makeUpCursorPos(CursorPos* cursorPos, u32 pos, s32 line, s32) {
            const wchar_t* drawString = mpDrawString;
            if (drawString != NULL) {
                const wchar_t* ch = drawString + pos;
                f32 y = GetCursorY();
                while (*ch != 0) {
                    DrawInfo drawInfo;
                    drawInfo.rect.left = 0.0f;
                    drawInfo.rect.top = 0.0f;
                    drawInfo.rect.right = 0.0f;
                    drawInfo.rect.bottom = 0.0f;
                    drawInfo.character = *ch;
                    calcRect(drawInfo);
                    doBeforeDrawProcess(drawString, pos, drawInfo);
                    if (cursorPos != NULL && cursorPos->uCursorPos == pos) {
                        procCursor(cursorPos, line + (y == GetCursorY() ? 0 : 1));
                    }
                    if (*ch == L'\n') {
                        doLineFeed();
                        break;
                    }
                    MoveCursorX((drawInfo.rect.right - drawInfo.rect.left) * getScale().x);
                    doAfterDrawProcess(drawString, pos, drawInfo);
                    if (y != GetCursorY()) {
                        line++;
                    }
                    y = GetCursorY();
                    ++ch;
                    ++pos;
                }
                if (cursorPos != NULL && *ch == 0 && cursorPos->uCursorPos == pos) {
                    procCursor(cursorPos, line);
                }
            }
        }

        void Base::doBeforeDrawProcess(const wchar_t*, u32, const DrawInfo&) {}

        void Base::doLineFeed() {
            ++muLine;
        }

        void Base::doAfterDrawProcess(const wchar_t*, u32, const DrawInfo&) {}

        void Base::put(wchar_t wc) {
            if (!mbSecretMode) {
                Print(wc);
            } else {
                Print(L'*');
            }
        }

        void Base::draw(CursorPos* cursorPos) {
            u32 startPos;
            const wchar_t* drawString = mpDrawString;
            u32 endPos;
            if (GetFont() != NULL) {
                startPos = muDrawStartPos;
                endPos = muDrawEndPos;
                muCachedStartPos = startPos;
                muDrawCacheStartPos = startPos;
                preDraw(startPos);
                drawString += startPos;
                SetFontSize(mfFontWidth * getScale().x,
                            mfFontHeight * getScale().y);
                SetupGX();
                while (*drawString != 0 && muDrawCacheStartPos < endPos) {
                    DrawInfo drawInfo;
                    drawInfo.rect.left = 0.0f;
                    drawInfo.rect.top = 0.0f;
                    drawInfo.rect.right = 0.0f;
                    drawInfo.rect.bottom = 0.0f;
                    drawInfo.character = *drawString;
                    calcRect(drawInfo);
                    doBeforeDrawProcess(mpDrawString,
                                        muDrawCacheStartPos,
                                        drawInfo);
                    if (cursorPos != NULL && cursorPos->uCursorPos == muDrawCacheStartPos) {
                        procCursor(cursorPos, 0);
                    }
                    if (*drawString == L'\n') {
                        nw4r::ut::Color color = GetTextColor();
                        SetTextColor(nw4r::ut::Color(200, 200, 200, color.a));
                        Print(0xe056);
                        SetTextColor(color);
                        doLineFeed();
                    } else if (*drawString != static_cast<wchar_t>(-1)) {
                        put(*drawString);
                        MoveCursorX(mfCharacterSpacing * getScale().x);
                    }
                    doAfterDrawProcess(mpDrawString,
                                       muDrawCacheStartPos,
                                       drawInfo);
                    ++drawString;
                    ++muDrawCacheStartPos;
                }
                if (cursorPos != NULL && cursorPos->uCursorPos == muDrawCacheStartPos) {
                    procCursor(cursorPos, 0);
                }
                finishDraw(muDrawCacheStartPos);
            }
        }

        void Base::preDraw(u32) {}

        void Base::finishDraw(u32) {}

        f32 Base::getLineHeight() {
            if (getScale().y == 0.0f) {
                return 1.0f;
            }
            f32 height = getScale().y * (mfFontHeight +
                                         mfLineSpacing);
            return height >= 1.0f ? height : 1.0f;
        }

        void Base::setFont(const nw4r::ut::Font& font) {
            nw4r::ut::CharWriter::SetFont(font);
            for (s32 index = 0; index < 0x160; ++index) {
                snWidthTable[index] = -1;
            }
            u32 ch = 0x20;
            do {
                DrawInfo drawInfo;
                drawInfo.rect.left = 0.0f;
                drawInfo.rect.top = 0.0f;
                drawInfo.rect.right = 0.0f;
                drawInfo.rect.bottom = 0.0f;
                drawInfo.character = static_cast<wchar_t>(ch);
                calcRect(drawInfo);
                u16 index = static_cast<u16>(ch);
                snWidthTable[index - 0x20] = static_cast<s32>(drawInfo.rect.right - drawInfo.rect.left);
                ch++;
            } while (ch <= 0x17f);
        }

        void Base::calcRect(DrawInfo& drawInfo) {
            drawInfo.rect.left = 0.0f;
            u16 ch = drawInfo.character;
            drawInfo.rect.right = 0.0f;
            drawInfo.rect.top = 0.0f;
            drawInfo.rect.bottom = getLineHeight();
            f32 width = 0.0f;
            width += mfCharacterSpacing;
            if (IsWidthFixed()) {
                width += GetFixedWidth();
            } else {
                f32 height = getScale().x;
                if (height == 0.0f) {
                    height = 0.0001f;
                }
                f32 scale = GetScaleH();
                const nw4r::ut::Font* font = GetFont();
                s32 charWidth = font->GetCharWidth(ch);
                f32 widthOffset = static_cast<f32>(charWidth) * scale / height;
                width += widthOffset;
            }
            drawInfo.rect.right = drawInfo.rect.right < width ? width : drawInfo.rect.right;
        }

        f32 Base::getWidth(const wchar_t* sz) {
            f32 width = 0.0f;
            DrawInfo drawInfo;
            drawInfo.rect.left = 0.0f;
            drawInfo.rect.top = 0.0f;
            drawInfo.rect.right = 0.0f;
            drawInfo.rect.bottom = 0.0f;
            u16 ch;
            goto check;
            body:
                drawInfo.character = ch;
                calcRect(drawInfo);
                width += drawInfo.rect.right - drawInfo.rect.left;
                ++sz;
            check:
                ch = *sz;
                if (ch != 0) {
                    goto body;
                }
            return width;
        }

        void Base::beginDraw(const nw4r::ut::Rect& rect) {
            Mtx44 projection;
            Mtx matrix;
            f32 viewport[6];
            muDrawCacheStartPos = 0;
            GXGetViewportv(&mSavedViewport.xOrig);
            GXGetProjectionv(mSavedProjection);
            C_MTXOrtho(projection, 0.0f, rect.top - rect.bottom, -50.0f, 50.0f + (rect.right - rect.left), -1.0f, 1.0f);
            GXSetProjection(projection, GX_ORTHOGRAPHIC);
            f32 width = mProjectionRect.right -
                        mProjectionRect.left;
            f32 scale = mfVIWidth / width;
            f32 halfWidth = width;
            halfWidth *= 0.5f;
            f32 left = (rect.left + halfWidth) - 50.0f;
            f32 xOffset = left;
            xOffset *= scale - 1.0f;
            viewport[0] = left + xOffset;
            f32 height = (mProjectionRect.bottom -
                          mProjectionRect.top) / 2.0f;
            viewport[1] = rect.bottom + height;
            viewport[2] = scale * (100.0f + (rect.right - rect.left));
            viewport[3] = rect.top - rect.bottom;
            viewport[4] = mSavedViewport.nearZ;
            viewport[5] = mSavedViewport.farZ;
            GXSetViewport(viewport[0], viewport[1], viewport[2], viewport[3], viewport[4], viewport[5]);
            u32 x = static_cast<u32>(viewport[0]);
            u32 y = static_cast<u32>(viewport[1]);
            u32 viewportWidth = static_cast<u32>(viewport[2]);
            if (viewportWidth >= 0x5dc) {
                viewportWidth = 0x5dc;
            }
            u32 viewportHeight = static_cast<u32>(viewport[3]);
            if (viewportHeight >= 0x5dc) {
                viewportHeight = 0x5dc;
            }
            GXSetScissor(x, y, viewportWidth, viewportHeight);
            PSMTXIdentity(matrix);
            GXLoadPosMtxImm(matrix, GX_PNMTX0);
            mfMinScrollY = GetCursorY();
            muLine = 0;
        }

        void Base::endDraw() {
            f32* viewport = &mSavedViewport.xOrig;
            GXSetViewport(viewport[0], viewport[1], viewport[2], viewport[3], viewport[4], viewport[5]);
            GXSetScissor(static_cast<u32>(viewport[0]), static_cast<u32>(viewport[1]),
                         static_cast<u32>(viewport[2]), static_cast<u32>(viewport[3]));
            mfModifyStartY = GetCursorX();
            mfMinScrollY =
                (mfMinScrollY - GetCursorY()) + getLineHeight();
        }

        void Base::drawCursor(f32, f32) {}

        void Base::draw() {}
    }
}
