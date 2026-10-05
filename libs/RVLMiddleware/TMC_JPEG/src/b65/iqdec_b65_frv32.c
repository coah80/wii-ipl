#include <string.h>
#include <tmc_jpeg_internal.h>

typedef struct {
    u16 bitLength;
    u16 symbol;
} TMCHuffmanEntry;

static TMCHuffmanEntry readHuffmanEntry(const TMCHuffmanEntry* entries, u32 index) {
    return entries[index];
}

static void readHuffmanLimit(const TMCHuffmanEntry* entries, TMCHuffmanEntry* limit) {
    limit->bitLength = entries->bitLength;
    limit->symbol = entries->symbol;
}

static inline s32 decodeLongHuffman(s32 bitCount, u32* huff_tbl, u8* symbols, TMCCJPEGDecWork* work, TMCHuffmanEntry* limit, TMCHuffmanEntry* decoded) {
    u16* entry;
    u32 bitData;
    u32 code;
    u32 length;

    if (bitCount <= 17) {
        s32 result = TMCJPEGDEC_load_buff(work);
        if (result < 0) {
            return result;
        }
    }
    bitCount = work->bitCount;
    entry = (u16*)(huff_tbl + 9);
    bitData = work->bitBuf;
    length = 9;
    bitCount -= 9;
    code = (bitData >> bitCount) & 0x1FF;
    work->bitCount = bitCount;
    goto read_entry;
    while (1) {
        length++;
        entry += 2;
        if (length > 16) {
            return TMCC_ERROR_OVERFLOW;
        }
        bitCount = work->bitCount;
        code <<= 1;
        bitData = work->bitBuf;
        bitCount--;
        work->bitCount = bitCount;
        code |= (bitData >> bitCount) & 1;
    read_entry:
        {
            limit->bitLength = entry[0];
            limit->symbol = entry[1];
            *decoded = *limit;
            if (code > (u32)decoded->bitLength) {
                continue;
            }
            {
                u32 relativeCode = code - limit->bitLength;
                u32 symbolIndex = relativeCode + limit->symbol;
                return symbols[symbolIndex & 0xFF];
            }
        }
    }
}

static inline s32 decodeACHuffman(s32 bitCount, u32* huff_tbl, u8* symbols, TMCCJPEGDecWork* work, TMCHuffmanEntry* limit, TMCHuffmanEntry* decoded) {
    u16* entry;
    u32 bitData;
    u32 code;
    u32 length;

    if (bitCount <= 17) {
        s32 result = TMCJPEGDEC_load_buff(work);
        if (result < 0) {
            return result;
        }
    }
    bitCount = work->bitCount;
    entry = (u16*)(huff_tbl + 9);
    bitData = work->bitBuf;
    length = 9;
    bitCount -= 9;
    code = (bitData >> bitCount) & 0x1FF;
    work->bitCount = bitCount;
    goto read_entry;
    while (1) {
        length++;
        entry += 2;
        if (length > 16) {
            return TMCC_ERROR_OVERFLOW;
        }
        bitCount = work->bitCount;
        code <<= 1;
        bitData = work->bitBuf;
        bitCount--;
        work->bitCount = bitCount;
        code |= (bitData >> bitCount) & 1;
    read_entry:
        {
            limit->bitLength = entry[0];
            limit->symbol = entry[1];
            *decoded = *limit;
            if (code > (u32)decoded->bitLength) {
                continue;
            }
            {
                u32 relativeCode = code - limit->bitLength;
                u32 symbolIndex = relativeCode + limit->symbol;
                return symbols[symbolIndex & 0xFF];
            }
        }
    }
}


s32 TMCJPEGDEC_decode_iquant(s32* block, u8* conv_row_ptr, u32* dc_predict_row_ptr, TMCCJPEGDecWork* work) {
    TMCHuffmanEntry dcEntry;
    TMCHuffmanEntry dcDecoded;
    TMCHuffmanEntry dcLimit;
    TMCHuffmanEntry acDecoded;
    TMCHuffmanEntry acLimit;
    s32 zz;
    const u8* zztbl;
    u8* huff_sym;
    u16* ac_fast;
    s32 idx;
    u32* huff_tbl;
    s32 bit_pos;
    u32 bit_data;
    u32 tmp;
    s32 r;
    s32 blk0;
    TMCHuffmanEntry acEntry;
    s32 extra;
    s32 t;
    s32 q;
    u16* dc_fast;
    s32* conv_row;

    conv_row = (s32*)conv_row_ptr;
    bit_pos = work->bitCount;
    dc_fast = work->pDCFast;

    if (bit_pos <= 8) {
        r = TMCJPEGDEC_load_buff(work);
        if (r < 0) {
            return r;
        }
    }

    bit_pos = work->bitCount;
    bit_data = work->bitBuf;
    {
        dcEntry = readHuffmanEntry((const TMCHuffmanEntry*)dc_fast, (bit_data >> (bit_pos - 8)) & 0xFF);
        r = dcEntry.bitLength;
        extra = dcEntry.symbol;
    }

    if (r != 0) {
        work->bitCount = bit_pos - r;
        r = extra;
    } else {
        huff_sym = work->pDCHuffSym;
        huff_tbl = work->pDCHuffTbl;
        r = decodeLongHuffman(bit_pos, huff_tbl, huff_sym, work, &dcLimit, &dcDecoded);
        if (r < 0) {
            return r;
        }
    }

    blk0 = conv_row[0];
    if (r != 0) {
        if (work->bitCount <= r) {
            s32 load_ret;
            if (load_ret = TMCJPEGDEC_load_buff(work), load_ret < 0) {
                return load_ret;
            }
        }
        tmp = 1UL << r;
        bit_pos = work->bitCount - r;
        work->bitCount = bit_pos;
        bit_data = work->bitBuf;
        extra = tmp - 1;
        extra = extra & (bit_data >> bit_pos);
        if (((s32)tmp >> 1) > extra) {
            extra -= (tmp - 1);
        }
        dc_predict_row_ptr[0] += extra;
    }

    *block = dc_predict_row_ptr[0] * blk0;

    {
        u32* ac_huff_tbl;
        u8* ac_huff_sym;

        ac_fast = work->pACFast;
        ac_huff_tbl = work->pACHuffTbl;
        ac_huff_sym = work->pACHuffSym;

        memset(block + 1, 0, 0xFC);

        bit_pos = work->bitCount;
        idx = 1;
        if (bit_pos <= 8) {
            r = TMCJPEGDEC_load_buff(work);
            if (r < 0)
                return r;
        }

        bit_pos = work->bitCount;
        zztbl = TMCJPEGDEC_Zigzag_data;
        bit_data = work->bitBuf;
        t = bit_pos - 8;
        acEntry = readHuffmanEntry((const TMCHuffmanEntry*)ac_fast, (bit_data >> t) & 0xFF);

        do {
            s32 ac_thresh = acEntry.bitLength;
            if (ac_thresh != 0) {
                bit_pos = work->bitCount;
                bit_pos -= ac_thresh;
                work->bitCount = bit_pos;
                r = acEntry.symbol;
            } else {
                bit_pos = work->bitCount;
                r = decodeACHuffman(bit_pos, ac_huff_tbl, ac_huff_sym, work, &acLimit, &acDecoded);
                if (r < 0) {
                    return r;
                }
            }

            t = r & 0x0F;
            if (t != 0) {
                r >>= 4;
                idx += r;

                if (idx >= 64) {
                    return TMCC_ERROR_OVERFLOW;
                }

                zz = zztbl[idx];

                bit_pos = work->bitCount;
                if (bit_pos <= t + 8) {
                    r = TMCJPEGDEC_load_buff(work);
                    if (r < 0) {
                        return r;
                    }
                }
                tmp = 1UL << t;
                bit_pos = work->bitCount - t;
                work->bitCount = bit_pos;
                bit_data = work->bitBuf;
                extra = (tmp - 1) & (bit_data >> bit_pos);
                t = bit_pos - 8;
                q = conv_row[(u8)zz];
                acEntry = readHuffmanEntry((const TMCHuffmanEntry*)ac_fast, (bit_data >> t) & 0xFF);

                if (((s32)tmp >> 1) > extra) {
                    extra -= (tmp - 1);
                }

                block[(u8)zz] = extra * q;

                idx++;
            } else {
                if (r == 0) {
                    break;
                }
                bit_pos = work->bitCount;
                if (bit_pos <= 8) {
                    r = TMCJPEGDEC_load_buff(work);
                    if (r < 0) {
                        return r;
                    }
                }
                bit_data = work->bitBuf;
                bit_pos = work->bitCount;
                t = bit_pos - 8;
                tmp = ((bit_data >> t) & 0xFF) << 2;
                acEntry = readHuffmanEntry((const TMCHuffmanEntry*)ac_fast, tmp >> 2);

                idx += 16;
            }
        } while (idx < 64);

        if (idx > 64) {
            return TMCC_ERROR_OVERFLOW;
        }

        idx--;
        return TMCJPEGDEC_Zigzag_loop[idx];
    }
}
