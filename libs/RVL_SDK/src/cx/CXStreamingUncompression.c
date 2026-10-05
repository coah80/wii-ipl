#include <private/cx.h>
#include <revolution/cx.h>

static inline int CXiReadHeader(u8*, int*, const u8*, int, int);
static inline CXHuffmanDecodeTableEntry* GetNextNode(CXHuffmanDecodeTableEntry*, int);

void CXInitUncompContextRL(CXUncompContextRL* context, u8* data) {
    context->outData = data;
    context->outDataLen = 0;
    context->flags = 0;
    context->length = 0;
    context->hdrLen = 8;
    context->size = 0;
}

void CXInitUncompContextLZ(CXUncompContextLZ* context, u8* data) {
    context->outData = data;
    context->outDataLen = 0;
    context->flags = 0;
    context->flagsLeft = 0;
    context->length = 0;
    context->lengthBytesLeft = 3;
    context->hdrLen = 8;
    context->lzType = 0;
    context->size = 0;
}

void CXInitUncompContextHuffman(CXUncompContextHuffman* context, u8* data) {
    context->outData = (u32*)data;
    context->outDataLen = 0;
    context->depth = 0;
    context->decodeTableSize = -1;
    context->decodeTable = context->decodeTableData;
    context->wordBuffer = 0;
    context->wordBits = 0;
    context->bits = 0;
    context->bitsLeft = 0;
    context->hdrLen = 8;
    context->size = 0;
}

CXStreamingResult CXReadUncompRL(CXUncompContextRL* context, const void* src, u32 size) {
    const u8* pSrc = src;

    if (context->hdrLen) {
        int a;
        if (context->hdrLen == 8) {
            if ((*pSrc & CX_COMPRESSION_TYPE_MASK) != CX_COMPRESSION_TYPE_RUN_LENGTH) {
                return CX_STREAMING_ERR_BAD_FILE_TYPE;
            }

            if ((*pSrc & 0x0F) != 0) {
                return CX_STREAMING_ERR_BAD_FILE_TYPE;
            }
        }

        a = CXiReadHeader(&context->hdrLen, &context->outDataLen, pSrc, size, context->size);

        pSrc += a;
        size -= a;

        if (!size) {
            return !context->hdrLen ? context->outDataLen : CX_STREAMING_ERR_BAD_FILE_TYPE;
        }
    }

    while (context->outDataLen > 0) {
        if (!(context->flags & 0x80)) {
            while (context->length) {
                *context->outData++ = *pSrc++;

                context->length--;
                context->outDataLen--;
                size--;

                if (!size) {
                    return context->outDataLen;
                }
            }
        } else if (context->length) {
            u8 b = *pSrc++;
            size--;

            while (context->length) {
                *context->outData++ = b;

                context->length--;
                context->outDataLen--;
            }

            if (!size) {
                return context->outDataLen;
            }
        }

        context->flags = *pSrc++;
        size--;
        context->length = context->flags & 0x7f;

        if (context->flags & 0x80) {
            context->length += 3;
        } else {
            context->length += 1;
        }

        if (context->length > context->outDataLen) {
            if (!context->size) {
                return CX_STREAMING_ERR_BAD_FILE_SIZE;
            }

            context->length = context->outDataLen;
        }

        if (size) {
            continue;
        }

        return context->outDataLen;
    }

    if (!context->size && size > 32) {
        return CX_STREAMING_ERR_BUFFER_TOO_LARGE;
    }

    return CX_STREAMING_ERR_OK;
}

static int CXiReadHeader(u8* pHdrLen, int* pOutLen, const u8* pSrc, int srcSize, int maxOutLen) {
    int bytesParsed = 0;

    while (*pHdrLen) {
        (*pHdrLen)--;

        if (*pHdrLen <= 3) {
            *pOutLen |= *pSrc << ((3 - *pHdrLen) << 3);
        } else if (*pHdrLen <= 6) {
            *pOutLen |= *pSrc << ((6 - *pHdrLen) << 3);
        }

        pSrc++;
        bytesParsed++;

        if (*pHdrLen == 4 && *pOutLen > 0) {
            *pHdrLen = 0;
        }

        srcSize--;
        if (srcSize == 0 && *pHdrLen != 0) {
            return bytesParsed;
        }
    }

    if (maxOutLen > 0 && maxOutLen < *pOutLen) {
        *pOutLen = maxOutLen;
    }

    return bytesParsed;
}

CXStreamingResult CXReadUncompLZ(CXUncompContextLZ* context, const void* src, u32 size) {
    const u8* pSrc = src;

    if (context->hdrLen) {
        int a;
        if (context->hdrLen == 8) {
            if ((*pSrc & CX_COMPRESSION_TYPE_MASK) != CX_COMPRESSION_TYPE_LZ) {
                return CX_STREAMING_ERR_BAD_FILE_TYPE;
            }

            context->lzType = *pSrc & 0x0F;

            if (context->lzType != 0 && context->lzType != 1) {
                return CX_STREAMING_ERR_BAD_FILE_TYPE;
            }
        }

        a = CXiReadHeader(&context->hdrLen, &context->outDataLen, pSrc, size, context->size);

        pSrc += a;
        size -= a;

        if (!size) {
            return !context->hdrLen ? context->outDataLen : CX_STREAMING_ERR_BAD_FILE_TYPE;
        }
    }

    while (context->outDataLen > 0) {
        while (context->flagsLeft) {
            s32 a;

            if (!size) {
                return context->outDataLen;
            }

            if (!(context->flags & 0x80)) {
                *context->outData++ = *pSrc++;
                context->outDataLen--;

                size--;

                goto there;
            }

            while (context->lengthBytesLeft) {
                context->lengthBytesLeft--;

                if (!context->lzType) {
                    context->length = *pSrc++;
                    context->length += 0x30;
                    context->lengthBytesLeft = 0;
                } else {
                    switch (context->lengthBytesLeft) {
                        case 2: {
                            context->length = *pSrc++;

                            if (context->length >> 4 == 1) {
                                context->length = (context->length & 0x0F) << 16;
                                context->length += 0x1110;
                            } else if (context->length >> 4 == 0) {
                                context->length = (context->length & 0x0F) << 8;
                                context->length += 0x110;
                                context->lengthBytesLeft = 1;
                            } else {
                                context->length += 0x10;
                                context->lengthBytesLeft = 0;
                            }

                            break;
                        }
                        case 1: {
                            context->length += *pSrc++ << 8;
                            break;
                        }
                        case 0: {
                            context->length += *pSrc++;
                            break;
                        }
                    }
                }

                size--;
                if (!size) {
                    return context->outDataLen;
                }
            }

            a = (context->length & 0x0F) << 8;
            context->length >>= 4;

            a = (a | *pSrc++) + 1;
            size--;
            context->lengthBytesLeft = 3;

            if (context->length > context->outDataLen) {
                if (!context->size) {
                    return CX_STREAMING_ERR_BAD_FILE_SIZE;
                }

                context->length = context->outDataLen;
            }

            while (context->length > 0) {
                *context->outData = context->outData[-a];
                context->outData++;
                context->outDataLen--;
                context->length--;
            }

        there:
            if (!context->outDataLen) {
                goto out;
            }

            context->flags <<= 1;
            context->flagsLeft--;
        }

        if (!size) {
            return context->outDataLen;
        }

        context->flags = *pSrc++;
        context->flagsLeft = 8;
        size--;
    }

out:
    if (!context->size && size > 32)
        return CX_STREAMING_ERR_BUFFER_TOO_LARGE;

    return CX_STREAMING_ERR_OK;
}

CXStreamingResult CXReadUncompHuffman(CXUncompContextHuffman* context, const void* src, u32 size) {
    const u8* pSrc = src;

    if (context->hdrLen) {
        int a;
        if (context->hdrLen == 8) {
            context->depth = *pSrc & 0x0F;

            if ((*pSrc & CX_COMPRESSION_TYPE_MASK) != CX_COMPRESSION_TYPE_HUFFMAN) {
                return CX_STREAMING_ERR_BAD_FILE_TYPE;
            }

            if (context->depth != 4 && context->depth != 8) {
                return CX_STREAMING_ERR_BAD_FILE_TYPE;
            }
        }

        a = CXiReadHeader(&context->hdrLen, &context->outDataLen, pSrc, size, context->size);

        pSrc += a;
        size -= a;

        if (!size) {
            return !context->hdrLen ? context->outDataLen : CX_STREAMING_ERR_BAD_FILE_TYPE;
        }
    }

    if (context->decodeTableSize < 0) {
        context->decodeTableSize = ((*pSrc + 1) << 1) - 1;
        (context->decodeTable++)->raw = *pSrc++;
        size--;
    }

    while (context->decodeTableSize > 0) {
        if (!size) {
            return context->outDataLen;
        }

        (context->decodeTable++)->raw = *pSrc++;
        context->decodeTableSize--;
        size--;

        if (context->decodeTableSize) {
            continue;
        }

        // Done copying decodeTable
        context->decodeTable = context->decodeTableData + 1;

        if (!CXiVerifyHuffmanTable_(context->decodeTableData, context->depth)) {
            return CX_STREAMING_ERR_BAD_FILE_TABLE;
        }
    }

    while (context->outDataLen > 0) {
        while (context->bitsLeft < 32) {
            if (!size) {
                return context->outDataLen;
            }

            context->bits |= *pSrc++ << context->bitsLeft;

            size--;
            context->bitsLeft += 8;
        }

        while (context->bitsLeft) {
            BOOL currBit = context->bits >> 31;
            int c = (context->decodeTable->raw << currBit) & 0x80;

            context->decodeTable = GetNextNode((CXHuffmanDecodeTableEntry*)context->decodeTable, currBit);
            context->bits <<= 1;
            context->bitsLeft--;

            if (!c) {
                continue;
            }

            context->wordBuffer >>= context->depth;
            context->wordBuffer |= context->decodeTable->raw << (32 - context->depth);
            context->decodeTable = context->decodeTableData + 1;
            context->wordBits += context->depth;

            if (context->wordBits == 32) {
                *context->outData = CXiConvertEndian32_(context->wordBuffer);
                context->outData++;
                context->outDataLen -= 4;
                context->wordBits = 0;

                if (context->outDataLen <= 0) {
                    goto out;
                }
            }

            (void)currBit;
        }
    }

out:
    if (!context->size && size > 32) {
        return CX_STREAMING_ERR_BUFFER_TOO_LARGE;
    }

    return CX_STREAMING_ERR_OK;
}

static CXHuffmanDecodeTableEntry* GetNextNode(CXHuffmanDecodeTableEntry* pDecodeTable, BOOL currBit) {
    return (CXHuffmanDecodeTableEntry*)ROUNDDOWN((u32)pDecodeTable, 2) + (((*pDecodeTable).idxOffset + 1) << 1) + currBit;
}
