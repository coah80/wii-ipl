#include <nw4r/ut/ArchiveFont.h>
#include <nw4r/ut/Font.h>
#include <nw4r/ut/fontResources.h>

#include <nw4r/math/arithmetic.h>

#include <revolution/os.h>

#include <string.h>

namespace nw4r {
    namespace ut {
        ArchiveFont::ArchiveFont() {
        }

        ArchiveFont::~ArchiveFont() {
        }

        u32 ArchiveFont::GetRequireBufferSize(const void* fontData, const char* includedGroups) {
            const HeaderedGlyphGroups* pGlgr;
            const ArchiveFontBinaryLayout* font;

            u16 countName, countSheet, countCWDH, countCMAP;

            u32 stepSheets, stepCWDH, stepCMAP;

            u32 dataSheetsOff, dataCWDHOff, dataCMAPOff;
            const u32* dataCWDH;
            const u32* dataCMAP;

            u32 flagsSheetsOff, flagsCWDHOff, flagsCMAPOff;
            const u32* flagsSheets;
            const u32* flagsCWDH;
            const u32* flagsCMAP;

            int i;
            int entryI;
            const HeaderedGlyphGroups* groupHeaderCursor;
            const u8* offsetFlags;
            u32 loadedSheetCount, loadedCWDHSize, loadedCMAPSize;
            u32 flagWord;
            const char* groupName;
            const u32* offsetData;
            int j;

            u32 sheetOffsetsSize;
            u32 loadedSheetsSize;
            u32 neededCharacterSize;
            u32 baseSize;

            // MWCC needs this widened CMAP count for the original temporary allocation.
            u32 cmapCountForLayout;

            u32 loadedCharacterSize;

            u32 groupOffset;

            if (!ArchiveFontBase::IsValidResource(fontData, 0x4000)) {
                return 0;
            }

            font = static_cast<const ArchiveFontBinaryLayout*>(fontData);
            pGlgr = &font->glgr;

            countName = pGlgr->inner.nameCount;
            countSheet = pGlgr->inner.sheetCount;
            countCWDH = pGlgr->inner.cwdhCount;
            countCMAP = pGlgr->inner.cmapCount;
            cmapCountForLayout = countCMAP;

            stepSheets = ((s32)countSheet + 0x1f) / 32 * 4;
            stepCWDH = ((s32)countCWDH + 0x1f) / 32 * 4;
            stepCMAP = ((s32)cmapCountForLayout + 0x1f) / 32 * 4;

            dataSheetsOff = ROUNDUP(offsetof(ArchiveFontBinaryLayout, glgr.inner.nameOffsets) + countName * sizeof(u16), 4);
            dataCWDHOff = ROUNDUP(dataSheetsOff + countSheet * sizeof(u32), 4);
            dataCMAPOff = ROUNDUP(dataCWDHOff + countCWDH * sizeof(u32), 4);
            dataCWDH = (const u32*)(dataCWDHOff + (u32)fontData);
            dataCMAP = (const u32*)(dataCMAPOff + (u32)fontData);

            flagsSheetsOff = ROUNDUP(dataCMAPOff + cmapCountForLayout * sizeof(u32), 4);
            flagsCWDHOff = ROUNDUP(flagsSheetsOff + stepSheets * countName, 4);
            flagsCMAPOff = ROUNDUP(flagsCWDHOff + stepCWDH * countName, 4);

            flagsSheets = (const u32*)(flagsSheetsOff + (u32)fontData);
            flagsCWDH = (const u32*)(flagsCWDHOff + (u32)fontData);
            flagsCMAP = (const u32*)(flagsCMAPOff + (u32)fontData);

            loadedSheetCount = 0;
            loadedCWDHSize = 0;
            loadedCMAPSize = 0;

            for (i = 0, entryI = 0; entryI < pGlgr->inner.sheetCount; entryI += 0x20, i++) {
                offsetFlags = (const u8*)flagsSheets + i * sizeof(u32);

                flagWord = 0;
                // MWCC needs the header as the induction base for the name-offset loads.
                for (j = 0, groupHeaderCursor = pGlgr; j < pGlgr->inner.nameCount;
                     groupHeaderCursor = (const HeaderedGlyphGroups*)((const u8*)groupHeaderCursor + 2), j++) {
                    groupName = (const char*)((u32)groupHeaderCursor->inner.nameOffsets[0] + (u32)fontData);
                    if (*includedGroups == '\0' || detail::ArchiveFontBase::IncludeName(includedGroups, groupName)) {
                        flagWord |= *(const u32*)(offsetFlags + ROUNDDOWN(j * stepSheets, 4));
                    }
                }

                loadedSheetCount += math::CntBit1(flagWord);
            }

            for (i = 0; i * 32 < pGlgr->inner.cwdhCount; i++) {
                offsetFlags = (const u8*)flagsCWDH + i * sizeof(u32);

                flagWord = 0;
                for (j = 0; j < pGlgr->inner.nameCount; j++) {
                    groupOffset = pGlgr->inner.nameOffsets[j];
                    groupName = (const char*)(groupOffset + (u32)fontData);
                    if (*includedGroups == '\0' || detail::ArchiveFontBase::IncludeName(includedGroups, groupName)) {
                        flagWord |= *(const u32*)(offsetFlags + ROUNDDOWN(j * stepCWDH, 4));
                    }
                }

                offsetData = dataCWDH + i * 32;
                for (j = 0; j < 32; j++) {
                    if ((flagWord << j) & 0x80000000U) {
                        loadedCWDHSize += offsetData[j] - sizeof(BinaryBlockHeader);
                    }
                }
            }

            for (i = 0; i * 32 < pGlgr->inner.cmapCount; i++) {
                offsetFlags = (const u8*)flagsCMAP + i * sizeof(u32);

                flagWord = 0;
                for (j = 0; j < pGlgr->inner.nameCount; j++) {
                    groupOffset = pGlgr->inner.nameOffsets[j];
                    groupName = (const char*)(groupOffset + (u32)fontData);
                    if (*includedGroups == '\0' || detail::ArchiveFontBase::IncludeName(includedGroups, groupName)) {
                        flagWord |= *(const u32*)(offsetFlags + ROUNDDOWN(j * stepCMAP, 4));
                    }
                }

                offsetData = dataCMAP + i * 32;
                for (j = 0; j < 32; j++) {
                    if ((flagWord << j) & 0x80000000U) {
                        loadedCMAPSize += offsetData[j] - sizeof(BinaryBlockHeader);
                    }
                }
            }

            sheetOffsetsSize = ROUNDUP(pGlgr->inner.sheetCount * 2, 4);
            loadedSheetsSize = ROUNDUP(loadedSheetCount * pGlgr->inner.uncompSheetSize, 4);

            loadedCharacterSize = loadedCWDHSize + loadedCMAPSize;
            neededCharacterSize = ut::Max<u32>(loadedCharacterSize, sizeof(CXUncompContextHuffman));

            baseSize = OSRoundUp32B(sizeof(FontInformation) + sizeof(FontTextureGlyph) + sheetOffsetsSize);
            return (baseSize + loadedSheetsSize) + neededCharacterSize;
        }

        detail::ArchiveFontBase::ConstructState ArchiveFont::StreamingConstruct(ConstructContext* ctx, const void* fontData, u32 fontDataSize) {
            ConstructState state;
            CachedStreamReader* reader;

            // If there's already data bound, exit early
            if (mFontInfo != NULL) {
                return ctx->mBlocksParsed < ctx->mTotalBlocks ? CONSTRUCT_STATE_FATAL_ERR : CONSTRUCT_STATE_DONE;
            }

            state = CONSTRUCT_STATE_WORKING;
            CachedStreamReader& readerRef = ctx->mReader;
            reader = &readerRef;
            readerRef.Attach(fontData, fontDataSize);

            while (state == CONSTRUCT_STATE_WORKING) {
                switch (ctx->mNextCmd) {
                    case CONSTRUCT_CMD_DISPATCH: {
                        state = detail::ArchiveFontBase::ConstructOpDispatch(ctx, reader);
                        break;
                    }
                    case CONSTRUCT_CMD_ANALYZE_FILE_HEADER: {
                        state = detail::ArchiveFontBase::ConstructOpAnalyzeFileHeader(ctx, reader);
                        break;
                    }
                    case CONSTRUCT_CMD_ANALYZE_GLGR: {
                        state = detail::ArchiveFontBase::ConstructOpAnalyzeGLGR(ctx, reader);
                        break;
                    }
                    case CONSTRUCT_CMD_ANALYZE_FINF: {
                        state = detail::ArchiveFontBase::ConstructOpAnalyzeFINF(ctx, reader);
                        break;
                    }
                    case CONSTRUCT_CMD_ANALYZE_CMAP: {
                        state = detail::ArchiveFontBase::ConstructOpAnalyzeCMAP(ctx, reader);
                        break;
                    }
                    case CONSTRUCT_CMD_ANALYZE_CWDH: {
                        state = detail::ArchiveFontBase::ConstructOpAnalyzeCWDH(ctx, reader);
                        break;
                    }
                    case CONSTRUCT_CMD_ANALYZE_TGLP: {
                        state = detail::ArchiveFontBase::ConstructOpAnalyzeTGLP(ctx, reader);
                        break;
                    }
                    case CONSTRUCT_CMD_PREPAIR_COPY_SHEET: {
                        state = detail::ArchiveFontBase::ConstructOpPrepairCopySheet(ctx, reader);
                        break;
                    }
                    case CONSTRUCT_CMD_PREPAIR_EXPAND_SHEET: {
                        state = detail::ArchiveFontBase::ConstructOpPrepairExpandSheet(ctx, reader);
                        break;
                    }
                    case CONSTRUCT_CMD_COPY: {
                        state = detail::ArchiveFontBase::ConstructOpCopy(ctx, reader);
                        break;
                    }
                    case CONSTRUCT_CMD_SKIP: {
                        state = detail::ArchiveFontBase::ConstructOpSkip(ctx, reader);
                        break;
                    }
                    case CONSTRUCT_CMD_EXPAND: {
                        state = detail::ArchiveFontBase::ConstructOpExpand(ctx, reader);
                        break;
                    }
                    case CONSTRUCT_CMD_FATAL_ERR: {
                        state = detail::ArchiveFontBase::ConstructOpFatalError(ctx, reader);
                        break;
                    }
                    default: {
                        ctx->mNextCmd = CONSTRUCT_CMD_FATAL_ERR;
                        state = CONSTRUCT_STATE_FATAL_ERR;
                    }
                }
            }

            // If everything went well, bind the work data to the resource
            // buffer, adjust the alternate character index to respect unloaded
            // sheets, and set the reader function (for displaying strings) to
            // use the encoding in mFontInfo
            if (state == CONSTRUCT_STATE_DONE && mFontInfo == NULL) {
                DCFlushRange(ctx->pWorkStart, ctx->pWorkEnd - ctx->pWorkStart);
                SetResourceBuffer(ctx->pWorkStart, ctx->pFontInfo, ctx->pSheetOffsets);
                if (AdjustIndex(mFontInfo->alterCharIndex) == detail::GLYPH_INDEX_NOT_FOUND) {
                    mFontInfo->alterCharIndex = 0;
                }
                Font::InitReaderFunc(GetEncoding());
            }
            return state;
        }

        bool ArchiveFont::Construct(void* work, u32 workSize, const void* fontData, const char* includedGroups) {
            u32 fontDataSize = ((BinaryFileHeader*)fontData)->fileSize;

            detail::ArchiveFontBase::ConstructContext ctx;
            ctx.mReader.Init();

            // Set up data outlining which groups should be loaded and how they
            // should be used
            ctx.pIncludedGroups = includedGroups;
            ctx.pSheetOffsets = NULL;

            // Set up work pointers
            ctx.pWorkStart = (u8*)work;
            ctx.pWorkEnd = ctx.pWorkStart + workSize;
            ctx.pWorkCurr = ctx.pWorkStart;

            // Setup huffman context at the end of the work buffer
            ctx.pHuffmanCtx = (CXUncompContextHuffman*)ROUNDDOWN((u32)(ctx.pWorkEnd - sizeof(CXUncompContextHuffman)), 4);

            // Queued command params (set up only by other commands, and won't
            // be relevant otherwise)
            ctx.mQueuedCmd = CONSTRUCT_CMD_INVALID;
            ctx.mNextCmdParam = 0;

            ctx.mTotalBlocks = 1;
            ctx.mBlocksParsed = 0;

            // Clear sheet expansion/copy variables
            ctx.mSheetsHandled = 0;
            ctx.mSheetCount = 0;
            ctx.mGlyphsPerSheet = 0;

            // Clear pointers
            ctx.mDataOffset = 0;
            ctx.pFontInfo = NULL;
            ctx.pLastWidth = NULL;
            ctx.pLastMap = NULL;

            // Clear other stuff???
            ctx.mNextCmd = CONSTRUCT_CMD_ANALYZE_FILE_HEADER;

            return StreamingConstruct(&ctx, fontData, fontDataSize) == CONSTRUCT_STATE_DONE;
        }

        void ArchiveFont::GetGlyph(Glyph* glyph, u16 c) const {
            u16 idx = ResFontBase::GetGlyphIndex(c);
            GetGlyphFromIndex(glyph, idx);
        }

        void ArchiveFont::GetGlyphFromIndex(Glyph* glyph, u16 index) const {
            FontTextureGlyph& tg = *mFontInfo->pGlyph;

            u16 realIndex = ArchiveFontBase::AdjustIndex(index);
            if (realIndex == detail::GLYPH_INDEX_NOT_FOUND) {
                index = mFontInfo->alterCharIndex;
                realIndex = ArchiveFontBase::AdjustIndex(index);
            }

            u32 cellsInASheet = tg.sheetRow * tg.sheetLine;
            u32 sheetNo = realIndex / cellsInASheet;

            u32 cellNo = realIndex % cellsInASheet;
            u32 cellUnitX = cellNo % tg.sheetRow;
            u32 cellUnitY = cellNo / tg.sheetRow;
            u32 cellPixelX = cellUnitX * (tg.cellWidth + 1);
            u32 cellPixelY = cellUnitY * (tg.cellHeight + 1);

            u32 offsetBytes = sheetNo * tg.sheetSize;

            void* pSheet = tg.sheetImage + offsetBytes;

            glyph->pTexture = pSheet;
            glyph->widths = GetCharWidthsFromIndex(index);
            glyph->height = static_cast<u8>(tg.cellHeight);
            glyph->texFormat = static_cast<GXTexFmt>(tg.sheetFormat);
            glyph->texWidth = static_cast<u16>(tg.sheetWidth);
            glyph->texHeight = static_cast<u16>(tg.sheetHeight);
            glyph->cellX = cellPixelX + 1;
            glyph->cellY = cellPixelY + 1;
        }
    }  // namespace ut
}  // namespace nw4r
