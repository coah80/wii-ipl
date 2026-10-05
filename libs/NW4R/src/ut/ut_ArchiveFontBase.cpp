#include <nw4r/ut/ArchiveFont.h>
#include <nw4r/ut/Font.h>
#include <nw4r/ut/fontResources.h>

#include <string.h>

namespace nw4r {
    namespace ut {
        namespace detail {
#define ENSURE_READER_HAS_SIZE(_ctx, _reader, _size)                                                                                                 \
    if ((_reader)->amtAvailableData() + (_reader)->amtAvailableCached() < (_size))                                                                   \
        return (_ctx)->requestNewData((_reader), (_size));
#define ENSURE_WORK_HAS_SIZE(_ctx, _size)                                                                                                            \
    if ((_ctx)->remWorkSpace() < (_size))                                                                                                            \
        return CONSTRUCT_STATE_FATAL_ERR;

            typedef union {
                u16 formatRaw;
                struct {
                    u16 isCmpr : 1;   // 0x00:1000000000000000
                    u16 format : 15;  // 0x01:0111111111111111
                };
            } FlaggedImageFormat;

            const char ArchiveFontBase::LOAD_GLYPH_ALL[1] = {0};

            void ArchiveFontBase::CachedStreamReader::memcpyToBuf(void* buf, u32 copyLen) {
                u32 cachedLen;
                u8* pBuf;
                u32 dataLen;

                pBuf = (u8*)buf;
                cachedLen = pCachedEnd - pCachedStart;
                if (cachedLen >= copyLen) {
                    memcpy(pBuf, pCachedStart, copyLen);
                    pCachedStart += copyLen;
                } else {
                    dataLen = copyLen - cachedLen;
                    memcpy(pBuf, pCachedStart, cachedLen);
                    memcpy(pBuf + cachedLen, pDataCurr, dataLen);
                    pCachedStart = pCachedEnd;
                    pDataCurr += dataLen;
                }
            }

            void ArchiveFontBase::CachedStreamReader::skip(u32 skipLen) {
                u32 dataLen, cachedLen;

                cachedLen = pCachedEnd - pCachedStart;
                if (cachedLen > skipLen) {
                    pCachedStart += skipLen;
                } else {
                    dataLen = skipLen - cachedLen;
                    pCachedStart = pCachedEnd;
                    pDataCurr += dataLen;
                }
            }

            ArchiveFontBase::ConstructState ArchiveFontBase::ConstructContext::requestNewData(CachedStreamReader* reader, u32 amt) {
                mDataOffset = getFullOffset(reader);
                bool requestSucceeded = reader->RequestData(this, amt);
                if (requestSucceeded) {
                    return CONSTRUCT_STATE_DATA_REQUESTED;
                } else {
                    return CONSTRUCT_STATE_FATAL_ERR;
                }
            }

            void ArchiveFontBase::ConstructContext::getNumSheetsToLoad(u16* sheetsToLoad) const {
                *sheetsToLoad = 0;
                for (int i = 0; i < mSheetCount; i++) {
                    if (pSheetOffsets[i] != GLYPH_INDEX_NOT_FOUND)
                        (*sheetsToLoad)++;
                }
            }

            // u32 ArchiveFontBase::ConstructContext::updateTextureBlockPtr() {
            //     u32 imgDataOffset;
            //     imgDataOffset = (u32)pFontInfo->pGlyph->sheetImage;

            //     pWorkCurr = (u8*)ROUNDUP((u32)pWorkCurr, 0x20);
            //     pFontInfo->pGlyph->sheetImage = pWorkCurr;

            //     return imgDataOffset;
            // }

            ArchiveFontBase::ArchiveFontBase() : pSheetOffsets(NULL) {
            }

            ArchiveFontBase::~ArchiveFontBase() {
            }

            CharWidths ArchiveFontBase::GetCharWidths(u16 charcode) const {
                u16 glyphIdx, adjGlyphIdx;

                glyphIdx = GetGlyphIndex(charcode);
                adjGlyphIdx = AdjustIndex(glyphIdx);
                if (adjGlyphIdx == GLYPH_INDEX_NOT_FOUND) {
                    glyphIdx = mFontInfo->alterCharIndex;
                }
                return GetCharWidthsFromIndex(glyphIdx);
            }

            void ArchiveFontBase::SetResourceBuffer(void* pUserBuffer, FontInformation* pFontInfo, u16* pSheetOffsets) {
                ResFontBase::SetResourceBuffer(pUserBuffer, pFontInfo);
                this->pSheetOffsets = pSheetOffsets;
            }

            u16 ArchiveFontBase::AdjustIndex(u16 glyphIdx) const {
                FontTextureGlyph* pTglp = mFontInfo->pGlyph;
                s32 glyphsPerSheet = (u32)pTglp->sheetRow * (u32)pTglp->sheetLine;
                u32 originalSheetIdx = (s32)glyphIdx / glyphsPerSheet;
                if (pSheetOffsets[originalSheetIdx] != GLYPH_INDEX_NOT_FOUND) {
                    return glyphIdx - pSheetOffsets[originalSheetIdx];
                } else {
                    return GLYPH_INDEX_NOT_FOUND;
                }
            }

            bool ArchiveFontBase::IncludeName(const char* groupList, const char* group) {
                u32 groupLen = strlen(group);
                const char* substr = groupList - 1;
                while (true) {
                    substr = strstr(substr + 1, group);
                    if (substr == NULL) {
                        return false;
                    }

                    // Check that there is nothing but spaces between the substr
                    // and the preceeding comma
                    // - Fails:
                    //   - groupList = "foo, BAD bar, baz"
                    //   - substr                ^
                    // - Succeeds:
                    //   - groupList = "foo, bar, baz"
                    //   - substr            ^
                    // - Succeeds:
                    //   - groupList = "foo,bar,baz"
                    //   - substr           ^
                    // - Succeeds:
                    //   - groupList = "foo,bar,baz"
                    //   - substr       ^
                    // - Fails (I think this is a bug):
                    //   - groupList = " foo, bar, baz"
                    //   - substr        ^
                    // @bug Should allow for leading spaces in groupList (maybe?)
                    if (substr != groupList) {
                        const char* backsearchStr = substr - 1;
                        while (backsearchStr > groupList && *backsearchStr == ' ') {
                            backsearchStr--;
                        }
                        if (*backsearchStr != ',') {
                            continue;
                        }
                    }

                    // Get the length of the section up until the next comma or
                    // the end
                    // - substr = "foo bar, baz"     -> sectionLen = 7
                    // - substr = "foo        , baz" -> sectionLen = 11
                    // - substr = "foo"              -> sectionLen = 3
                    const char* nextComma = strchr(substr, ',');
                    u32 sectionLen;
                    if (nextComma != NULL) {
                        sectionLen = nextComma - substr;
                    } else {
                        sectionLen = strlen(substr);
                    }

                    // Check to make sure there is nothing except spaces between
                    // the end of the group name and the next comma:
                    // - Fails:
                    //   - substr = "foo bar, baz"
                    //   - group = "foo"
                    // - Succeeds:
                    //   - substr = "foo     , baz"
                    //   - group = "foo"
                    // - Succeeds:
                    //   - substr = "foo, baz"
                    //   - group = "foo"
                    const char* sectionEnd = substr + groupLen;
                    while (sectionEnd < substr + sectionLen && (*sectionEnd == ' ')) {
                        sectionEnd++;
                    }

                    if (sectionEnd == substr + sectionLen) {
                        return true;
                    }
                }
            }

            bool ArchiveFontBase::IsValidResource(const void* data, u32 maxPreFinfSize) {
                const u8* fileBuf = (u8*)data;
                const BinaryFileHeader* hdr = (const BinaryFileHeader*)fileBuf;
                const BinaryBlockHeader* glgrHdr = (BinaryBlockHeader*)(fileBuf + sizeof(BinaryFileHeader));
                if (!IsValidBinaryFile((const BinaryFileHeader*)fileBuf, SIGNATURE_FONT_ARCHIVE, VERSION, 2)) {
                    return false;
                } else if (glgrHdr->kind != SIGNATURE_GLYPH_GROUPS) {
                    return false;
                } else {
                    return glgrHdr->size + 0x10 <= maxPreFinfSize;
                }
            }

            ArchiveFontBase::ConstructState ArchiveFontBase::ConstructOpDispatch(ConstructContext* ctx, CachedStreamReader* reader) {
                void* nextBlockHdr;

                if (ctx->mBlocksParsed >= ctx->mTotalBlocks) {
                    return CONSTRUCT_STATE_DONE;
                }

                ENSURE_READER_HAS_SIZE(ctx, reader, sizeof(BinaryBlockHeader));
                reader->memcpyToBuf(&ctx->mNextBlockHdr, sizeof(BinaryBlockHeader));
                switch (ctx->mNextBlockHdr.kind) {
                    case SIGNATURE_GLYPH_GROUPS: {
                        ctx->mNextCmd = CONSTRUCT_CMD_ANALYZE_GLGR;
                        break;
                    }
                    case SIGNATURE_FONT_INFO: {
                        ctx->mNextCmd = CONSTRUCT_CMD_ANALYZE_FINF;
                        break;
                    }
                    case SIGNATURE_CODE_MAP: {
                        ctx->mNextCmd = CONSTRUCT_CMD_ANALYZE_CMAP;
                        break;
                    }
                    case SIGNATURE_CHAR_WIDTH: {
                        ctx->mNextCmd = CONSTRUCT_CMD_ANALYZE_CWDH;
                        break;
                    }
                    case SIGNATURE_TEX_GLYPH: {
                        ctx->mNextCmd = CONSTRUCT_CMD_ANALYZE_TGLP;
                        break;
                    }
                    default: {
                        ctx->mNextCmd = CONSTRUCT_CMD_FATAL_ERR;
                        return CONSTRUCT_STATE_FATAL_ERR;
                    }
                }
                ctx->mBlocksParsed++;
                ctx->pWorkCurr = (u8*)(((u32)ctx->pWorkCurr + 3) & (~3));
                return CONSTRUCT_STATE_WORKING;
            }

            ArchiveFontBase::ConstructState ArchiveFontBase::ConstructOpAnalyzeFileHeader(ConstructContext* ctx, CachedStreamReader* reader) {
                ENSURE_READER_HAS_SIZE(ctx, reader, sizeof(BinaryFileHeader));
                ENSURE_WORK_HAS_SIZE(ctx, sizeof(BinaryFileHeader));

                reader->memcpyToBuf(ctx->pWorkCurr, sizeof(BinaryFileHeader));
                ctx->mNextCmd = CONSTRUCT_CMD_DISPATCH;
                return CONSTRUCT_STATE_WORKING;
            }

            inline void updateSheetFlags(const void* glgrHdr, u32 groupIdx, u16* sheetOffsets, u32 flagsStep, const u32* sheetFlags) {
                const GlyphGroups* glgr = (const GlyphGroups*)((const u8*)glgrHdr + sizeof(BinaryBlockHeader));
                int sheetIndex;
                u32 groupBitOffset;
                u16* sheetOffset = sheetOffsets;
                groupBitOffset = groupIdx * flagsStep * 8;
                for (sheetIndex = 0; sheetIndex < glgr->sheetCount; sheetOffset++, sheetIndex++) {
                    u32 groupBitIdx = sheetIndex + groupBitOffset;
                    const u32* bitBlockPtr = sheetFlags + (groupBitIdx & ~0x1F) / 32;
                    u32 bitBlock = *bitBlockPtr;
                    if (((bitBlock << (groupBitIdx & 0x1F)) & 0x80000000) != 0) {
                        *sheetOffset = 1;
                    }
                }
            }

            inline void setSheetOffsetBooleans(const ArchiveFontBase::ConstructContext* ctx, const void* glgrHdr, const void* hdr, u16* sheetOffsets,
                                               const u32* bitBlocksPtr, u32 sheetFlagsSize) {
                HeaderedGlyphGroups* pGlgr = (HeaderedGlyphGroups*)glgrHdr;

                int i;
                u16* sheetOffset;
                for (i = 0, sheetOffset = sheetOffsets; i < pGlgr->inner.sheetCount; sheetOffset++, i++) {
                    *sheetOffset = 0;
                }

                for (int i = 0; i < pGlgr->inner.nameCount; i++) {
                    const char* includedGroups = ctx->pIncludedGroups;
                    u16 offset = pGlgr->inner.nameOffsets[i];
                    char* name = (char*)(offset + (u32)hdr);
                    if (*includedGroups != 0) {
                        if (!ArchiveFontBase::IncludeName(includedGroups, name)) {
                            continue;
                        }
                    }

                    updateSheetFlags(glgrHdr, i, sheetOffsets, sheetFlagsSize, bitBlocksPtr);
                }
            }

            inline void convertSheetOffsetBooleansToOffsets(const void* glgrHdr, u16* sheetOffsets) {
                HeaderedGlyphGroups* pGlgr = (HeaderedGlyphGroups*)glgrHdr;
                int i;
                u16 glyphIdxOffset = 0;
                u16* sheetOffset;
                for (i = 0, sheetOffset = sheetOffsets; i < pGlgr->inner.sheetCount; sheetOffset++, i++) {
                    if (*sheetOffset == 1) {
                        *sheetOffset = glyphIdxOffset;
                    } else {
                        *sheetOffset = -1;
                        glyphIdxOffset += pGlgr->inner.sheetGlyphCount;
                    }
                }
            }

            inline void copyFlagOffsets(ArchiveFontBase::ConstructContext* ctx, u16* sheetOffsetsScratch, u32 workSize, const u16* sheetOffsetsScratchEnd) {
                u8* sheetOffsets = ctx->pWorkCurr;
                ctx->pWorkCurr = sheetOffsets + workSize;
                memmove(sheetOffsets, sheetOffsetsScratch, (sheetOffsetsScratchEnd - sheetOffsetsScratch) * sizeof(u16));
                ctx->pSheetOffsets = (u16*)sheetOffsets;
            }

            // inline u32 getOffsetSize(void* fontData, u32 remWorkSpace, u16 countSheet, u16** sheetOffsetsScratch) {
            //     u32 sheetOffsetsSize = ROUNDUP(countSheet * sizeof(u16), 4);
            //     *sheetOffsetsScratch = (u16*)ROUNDDOWN((u32)((u8*)fontData + remWorkSpace) - sheetOffsetsSize, 2);
            //     return sheetOffsetsSize;
            // }
            class FontGlyphGroupsAcs {
            public:
                explicit FontGlyphGroupsAcs(const ArchiveFontBinaryLayout* font)
                    : mFont(font), mGroups(&font->glgr) {}
                const GlyphGroups& GetGroups() const { return mGroups->inner; }
                void SetSheetFlags(u32 flagsStep, const u32* sheetFlags) {
                    mFlagsStep = flagsStep;
                    mSheetFlags = sheetFlags;
                }

                u16 GetNumSheet() const { return mGroups->inner.sheetCount; }
                int GetGlyphsPerSheet() const { return mGroups->inner.sheetGlyphCount; }
                u16 GetNumSet() const { return mGroups->inner.nameCount; }
                const char* GetSetName(int groupIndex) const {
                    const u16 nameOffset = mGroups->inner.nameOffsets[groupIndex];
                    return (const char*)(nameOffset + (u32)mFont);
                }
                bool IsUseSheet(int groupIndex, int sheetIndex) const {
                    const u32 groupBitIndex = sheetIndex + groupIndex * mFlagsStep * 8;
                    const u32* bitBlock = mSheetFlags + (groupBitIndex & ~0x1F) / 32;
                    return ((*bitBlock << (groupBitIndex & 0x1F)) & 0x80000000) != 0;
                }

            private:
                const ArchiveFontBinaryLayout* mFont;
                const HeaderedGlyphGroups* mGroups;
                u32 mFlagsStep;
                const u32* mSheetFlags;
            };

            ArchiveFontBase::ConstructState ArchiveFontBase::ConstructOpAnalyzeGLGR(ConstructContext* ctx, CachedStreamReader* reader) {
                const u32* flagsSheets;
                u32 sheetOffsetsSize;
                u32 flagsSheetsOff;
                u32 glgrInnerLen;
                const ArchiveFontBinaryLayout* font;
                u16 sheetGlyphCount;
                u32 countSheet;
                HeaderedGlyphGroups* pGlgr;
                u8* glgrEnd;
                u32 expectedMaxSize;
                u32 dataBlockCount;
                u16* sheetOffsetsScratch;
                int groupIndex;

                font = (ArchiveFontBinaryLayout*)ctx->pWorkCurr;

                glgrInnerLen = ctx->mNextBlockHdr.size - sizeof(BinaryBlockHeader);

                if (font->hdr.signature != SIGNATURE_FONT_ARCHIVE) {
                    return CONSTRUCT_STATE_FATAL_ERR;
                }

                ENSURE_READER_HAS_SIZE(ctx, reader, glgrInnerLen);
                ENSURE_WORK_HAS_SIZE(ctx, glgrInnerLen);

                expectedMaxSize = ctx->mNextBlockHdr.size + sizeof(BinaryFileHeader);

                {
                    pGlgr = (HeaderedGlyphGroups*)&font->glgr;
                    glgrEnd = (u8*)pGlgr + (u32)ctx->mNextBlockHdr.size;

                    memcpy(pGlgr, &ctx->mNextBlockHdr, sizeof(BinaryBlockHeader));
                    reader->memcpyToBuf(&pGlgr->inner, glgrInnerLen);
                }

                if (!ArchiveFontBase::IsValidResource(font, expectedMaxSize)) {
                    return CONSTRUCT_STATE_FATAL_ERR;
                }

                FontGlyphGroupsAcs gg(font);
                sheetGlyphCount = gg.GetGlyphsPerSheet();
                dataBlockCount = font->hdr.dataBlocks;
                countSheet = gg.GetNumSheet();
                const u32 stepSheetFlags = detail::CalcSizeFlagSet(countSheet);
                flagsSheetsOff = detail::CalcOffsetSheetFlags(gg.GetGroups().nameCount, countSheet, gg.GetGroups().smthCount_0x0a,
                                                              gg.GetGroups().smthCount_0x0c);
                flagsSheets = (const u32*)((flagsSheetsOff & ~3) + (u32)font);
                gg.SetSheetFlags(stepSheetFlags, flagsSheets);

                sheetOffsetsSize = (RoundUp)(countSheet * sizeof(u16), 4);
                sheetOffsetsScratch = (u16*)ROUNDDOWN((u32)((u8*)font + ctx->remWorkSpace()) - sheetOffsetsSize, 2);

                pGlgr = (HeaderedGlyphGroups*)&font->glgr;
                ENSURE_WORK_HAS_SIZE(ctx, glgrEnd - (u8*)font + sheetOffsetsSize);

                {
                    u16* sheetOffset;
                    int sheetIndex;
                    for (sheetIndex = 0, sheetOffset = sheetOffsetsScratch; sheetIndex < gg.GetNumSheet(); sheetOffset++, sheetIndex++) {
                        *sheetOffset = 0;
                    }
                    for (groupIndex = 0; groupIndex < gg.GetNumSet(); groupIndex++) {
                        const char* includedGroups = ctx->pIncludedGroups;
                        const char* name = gg.GetSetName(groupIndex);
                        if (*includedGroups && !ArchiveFontBase::IncludeName(includedGroups, name)) {
                            continue;
                        }
                        for (int sheetIndex = 0; sheetIndex < gg.GetNumSheet(); sheetIndex++) {
                            if (gg.IsUseSheet(groupIndex, sheetIndex)) {
                                sheetOffsetsScratch[sheetIndex] = 1;
                            }
                        }
                    }
                }

                convertSheetOffsetBooleansToOffsets(pGlgr, sheetOffsetsScratch);

                copyFlagOffsets(ctx, sheetOffsetsScratch, sheetOffsetsSize, sheetOffsetsScratch + (u16)countSheet);

                ctx->mSheetCount = countSheet;
                ctx->mGlyphsPerSheet = sheetGlyphCount;
                ctx->mTotalBlocks = dataBlockCount;
                ctx->mNextCmd = CONSTRUCT_CMD_DISPATCH;

                return CONSTRUCT_STATE_WORKING;
            }

            ArchiveFontBase::ConstructState ArchiveFontBase::ConstructOpAnalyzeFINF(ConstructContext* ctx, CachedStreamReader* reader) {
                u32 innerSize;

                innerSize = ctx->mNextBlockHdr.size - sizeof(BinaryBlockHeader);
                ENSURE_WORK_HAS_SIZE(ctx, innerSize);

                ctx->pFontInfo = (FontInformation*)ctx->pWorkCurr;

                ctx->enqueueCmds(CONSTRUCT_CMD_COPY, innerSize, CONSTRUCT_CMD_DISPATCH);
                return CONSTRUCT_STATE_WORKING;
            }

            ArchiveFontBase::ConstructState ArchiveFontBase::ConstructOpAnalyzeCMAP(ConstructContext* ctx, CachedStreamReader* reader) {
                u32 innerSize;

                ctx->pushCMAP();

                innerSize = ctx->mNextBlockHdr.size - sizeof(BinaryBlockHeader);
                ENSURE_WORK_HAS_SIZE(ctx, innerSize);

                ctx->enqueueCmds(CONSTRUCT_CMD_COPY, innerSize, CONSTRUCT_CMD_DISPATCH);
                return CONSTRUCT_STATE_WORKING;
            }

            ArchiveFontBase::ConstructState ArchiveFontBase::ConstructOpAnalyzeCWDH(ConstructContext* ctx, CachedStreamReader* reader) {
                u32 innerSize;

                ctx->pushCWDH();

                innerSize = ctx->mNextBlockHdr.size - sizeof(BinaryBlockHeader);
                ENSURE_WORK_HAS_SIZE(ctx, innerSize);

                ctx->enqueueCmds(CONSTRUCT_CMD_COPY, innerSize, CONSTRUCT_CMD_DISPATCH);
                return CONSTRUCT_STATE_WORKING;
            }

            ArchiveFontBase::ConstructState ArchiveFontBase::ConstructOpAnalyzeTGLP(ConstructContext* ctx, CachedStreamReader* reader) {
                ConstructCmd prepCmd;
                u16 isCmpr;
                u32 imgDataOffset;
                FlaggedImageFormat origSheetFormat;
                u16 sheetsToLoad;

                ENSURE_READER_HAS_SIZE(ctx, reader, sizeof(FontTextureGlyph));
                ENSURE_WORK_HAS_SIZE(ctx, sizeof(FontTextureGlyph));

                ctx->pFontInfo->pGlyph = (FontTextureGlyph*)ctx->pWorkCurr;

                {
                    u32 cachedLen;
                    u8* pBuf;
                    u32 dataLen;
                    u8* cachedStart;
                    u8* cachedEnd;

                    pBuf = ctx->pWorkCurr;
                    cachedStart = reader->pCachedStart;
                    cachedEnd = reader->pCachedEnd;
                    cachedLen = cachedEnd - cachedStart;
                    if (cachedLen >= sizeof(FontTextureGlyph)) {
                        memcpy(pBuf, cachedStart, sizeof(FontTextureGlyph));
                        reader->pCachedStart += sizeof(FontTextureGlyph);
                    } else {
                        dataLen = sizeof(FontTextureGlyph) - cachedLen;
                        memcpy(pBuf, cachedStart, cachedLen);
                        memcpy(pBuf + cachedLen, reader->pDataCurr, dataLen);
                        reader->pCachedStart = reader->pCachedEnd;
                        reader->pDataCurr += dataLen;
                    }
                }
                ctx->pWorkCurr += sizeof(FontTextureGlyph);

                origSheetFormat.formatRaw = ctx->pFontInfo->pGlyph->sheetFormat;
                ctx->pFontInfo->pGlyph->sheetFormat = origSheetFormat.format;
                isCmpr = origSheetFormat.isCmpr;

                ctx->getNumSheetsToLoad(&sheetsToLoad);
                ctx->pFontInfo->pGlyph->sheetNum = sheetsToLoad;

                imgDataOffset = (u32)ctx->pFontInfo->pGlyph->sheetImage;

                // Round up work pointer to multiple of 32 bytes
                ctx->pWorkCurr = (u8*)ROUNDUP((u32)ctx->pWorkCurr, 0x20);
                ctx->pFontInfo->pGlyph->sheetImage = ctx->pWorkCurr;

                prepCmd = isCmpr ? CONSTRUCT_CMD_PREPAIR_EXPAND_SHEET : CONSTRUCT_CMD_PREPAIR_COPY_SHEET;
                ctx->enqueueCmds(CONSTRUCT_CMD_SKIP, imgDataOffset - ctx->getFullOffset(reader), prepCmd);
                return CONSTRUCT_STATE_WORKING;
            }

            ArchiveFontBase::ConstructState ArchiveFontBase::ConstructOpPrepairCopySheet(ConstructContext* ctx, CachedStreamReader* reader) {
                u32 sheetSize;

                if (ctx->mSheetsHandled >= ctx->mSheetCount) {
                    ctx->mNextCmd = CONSTRUCT_CMD_DISPATCH;
                    return CONSTRUCT_STATE_WORKING;
                }
                sheetSize = ctx->pFontInfo->pGlyph->sheetSize;
                if (ctx->pSheetOffsets[ctx->mSheetsHandled] != GLYPH_INDEX_NOT_FOUND) {
                    ENSURE_WORK_HAS_SIZE(ctx, sheetSize);
                    ctx->enqueueCmds(CONSTRUCT_CMD_COPY, sheetSize, CONSTRUCT_CMD_PREPAIR_COPY_SHEET);
                } else {
                    ctx->enqueueCmds(CONSTRUCT_CMD_SKIP, sheetSize, CONSTRUCT_CMD_PREPAIR_COPY_SHEET);
                }
                ctx->mSheetsHandled++;
                return CONSTRUCT_STATE_WORKING;
            }

            ArchiveFontBase::ConstructState ArchiveFontBase::ConstructOpPrepairExpandSheet(ConstructContext* ctx, CachedStreamReader* reader) {
                u32 compressedSize, uncompressedSize;
                u8 compressedSizeBuf[4];
                u8 compressedDataHdr[4];

                if (ctx->mSheetsHandled >= ctx->mSheetCount) {
                    ctx->mNextCmd = CONSTRUCT_CMD_DISPATCH;
                    return CONSTRUCT_STATE_WORKING;
                }
                ENSURE_READER_HAS_SIZE(ctx, reader, sizeof(BinaryBlockHeader));
                reader->memcpyToBuf(compressedSizeBuf, 4);
                memcpy(compressedDataHdr, reader->pDataCurr, 4);
                compressedSize = *(u32*)(u8*)compressedSizeBuf;

                uncompressedSize = CXGetUncompressedSize(compressedDataHdr);
                if (ctx->pSheetOffsets[ctx->mSheetsHandled] != GLYPH_INDEX_NOT_FOUND) {
                    ENSURE_WORK_HAS_SIZE(ctx, compressedSize + sizeof(CXUncompContextHuffman));
                    CXInitUncompContextHuffman(ctx->pHuffmanCtx, ctx->pWorkCurr);

                    ctx->enqueueCmds(CONSTRUCT_CMD_EXPAND, compressedSize, CONSTRUCT_CMD_PREPAIR_EXPAND_SHEET);
                    ctx->pWorkCurr += uncompressedSize;
                } else {
                    ctx->enqueueCmds(CONSTRUCT_CMD_SKIP, compressedSize, CONSTRUCT_CMD_PREPAIR_EXPAND_SHEET);
                }
                ctx->mSheetsHandled++;
                return CONSTRUCT_STATE_WORKING;
            }

            ArchiveFontBase::ConstructState ArchiveFontBase::handleAdvanceDry(ConstructContext* ctx, CachedStreamReader* reader, u32 advanced) {
                advanced = ut::Min(advanced, ctx->mNextCmdParam);

                ctx->mNextCmdParam -= advanced;
                if (ctx->mNextCmdParam == 0) {
                    ctx->mNextCmd = ctx->mQueuedCmd;
                } else {
                    return ctx->requestNewData(reader, ctx->mNextCmdParam);
                }

                return ArchiveFontBase::CONSTRUCT_STATE_WORKING;
            }

            ArchiveFontBase::ConstructState ArchiveFontBase::ConstructOpCopy(ConstructContext* ctx, CachedStreamReader* reader) {
                u32 copySize;
                copySize = ut::Min((u32)(reader->pDataEnd - reader->pDataCurr), ctx->mNextCmdParam);

                memcpy(ctx->pWorkCurr, reader->pDataCurr, copySize);
                reader->pDataCurr += copySize;
                ctx->pWorkCurr += copySize;

                return handleAdvanceDry(ctx, reader, copySize);
            }

            ArchiveFontBase::ConstructState ArchiveFontBase::ConstructOpSkip(ConstructContext* ctx, CachedStreamReader* reader) {
                u32 skipSize;
                skipSize = ctx->getAdvanceSize(reader);
                reader->skip(skipSize);

                return handleAdvanceDry(ctx, reader, skipSize);
            }

            ArchiveFontBase::ConstructState ArchiveFontBase::ConstructOpExpand(ConstructContext* ctx, CachedStreamReader* reader) {
                u32 cmprSize;
                u8* src;

                // @bug I think this should be more like ConstructOpCopy where it checks the size of data rather than cached?
                cmprSize = ctx->getAdvanceSize(reader);

                src = reader->pDataCurr;
                reader->pDataCurr += cmprSize;
                CXReadUncompHuffman(ctx->pHuffmanCtx, src, cmprSize);

                return handleAdvanceDry(ctx, reader, cmprSize);
            }

            ArchiveFontBase::ConstructState ArchiveFontBase::ConstructOpFatalError(ConstructContext* ctx, CachedStreamReader* reader) {
                ctx->mNextCmd = CONSTRUCT_CMD_FATAL_ERR;
                return CONSTRUCT_STATE_FATAL_ERR;
            }

            void ArchiveFontBase::CachedStreamReader::Init() {
                pDataStart = NULL;
                pDataCurr = NULL;
                pDataEnd = NULL;

                pCachedBase = NULL;
                pCachedStart = NULL;
                pCachedEnd = NULL;

                cacheWorkspaceOffset = 0;
            }

            void ArchiveFontBase::CachedStreamReader::Attach(const void* data, u32 dataLen) {
                pDataStart = (u8*)data;
                pDataCurr = (u8*)data;
                pDataEnd = (u8*)data + dataLen;
            }

            bool ArchiveFontBase::CachedStreamReader::RequestData(ArchiveFontBase::ConstructContext* ctx, u32 offset) {
                size_t dataLen;
                size_t cachedLen;
                size_t available;

                u8* dst;

                available = amtAvailableData() + amtAvailableCached();
                if (available == 0) {
                    pCachedBase = NULL;
                    pCachedStart = NULL;
                    pCachedEnd = NULL;
                    cacheWorkspaceOffset = 0;
                } else {
                    if (ctx->remWorkSpace() < (offset << 1)) {
                        return false;
                    }

                    dst = ctx->pWorkCurr + offset;
                    cachedLen = pCachedEnd - pCachedStart;

                    if (cachedLen >= available) {
                        memmove(dst, pCachedStart, available);
                        pCachedStart += available;
                    } else {
                        dataLen = available - cachedLen;
                        memmove(dst, pCachedStart, cachedLen);
                        memmove(dst + cachedLen, pDataCurr, dataLen);
                        pCachedStart = pCachedEnd;
                        pDataCurr += dataLen;
                    }
                    pCachedBase = dst;
                    pCachedStart = dst;
                    pCachedEnd = dst + available;
                    cacheWorkspaceOffset = offset;
                }
                return true;
            }
        }  // namespace detail
    }  // namespace ut
}  // namespace nw4r
