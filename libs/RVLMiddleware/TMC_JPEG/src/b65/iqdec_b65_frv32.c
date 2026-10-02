#include <string.h>
#include <tmc_jpeg_internal.h>

typedef struct {
    u16 bitLength;
    u16 symbol;
} TMCHuffmanEntry;

static TMCHuffmanEntry readHuffmanEntry(const TMCHuffmanEntry* entries, u32 index) {
    return entries[index];
}

static TMCHuffmanEntry readHuffmanLimit(const TMCHuffmanEntry* entries) {
    TMCHuffmanEntry limit;
    limit.bitLength = entries->bitLength;
    limit.symbol = entries->symbol;
    return limit;
}

static inline s32 decodeLongHuffman(s32 bitCount, const TMCHuffmanEntry* table, const u8* symbols, TMCCJPEGDecWork* work) {
    u32 bitData;
    u32 code;
    u32 length;
    const TMCHuffmanEntry* entry;

    if (bitCount <= 17) {
        s32 result = TMCJPEGDEC_load_buff(work);
        if (result < 0) {
            return result;
        }
    }
    bitCount = work->bitCount;
    bitData = work->bitBuf;
    bitCount -= 9;
    code = (bitData >> bitCount) & 0x1FF;
    work->bitCount = bitCount;
    length = 9;
    entry = table + 9;
    goto read_entry;
    while (1) {
        length++;
        entry++;
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
            TMCHuffmanEntry decoded = readHuffmanLimit(entry);
            if (code > (u32)decoded.bitLength) {
                continue;
            }
            code = code - entry->bitLength + entry->symbol;
            return symbols[code & 0xFF];
        }
    }
}

static inline s32 decodeACHuffman(s32 bitCount, const TMCHuffmanEntry* entry, const u8* symbols, TMCCJPEGDecWork* work) {
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
    bitData = work->bitBuf;
    bitCount -= 9;
    code = (bitData >> bitCount) & 0x1FF;
    work->bitCount = bitCount;
    length = 9;
    entry += 9;
    goto read_entry;
    while (1) {
        length++;
        entry++;
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
            TMCHuffmanEntry decoded = readHuffmanLimit(entry);
            if (code > (u32)decoded.bitLength) {
                continue;
            }
            code = code - entry->bitLength + entry->symbol;
            return symbols[code & 0xFF];
        }
    }
}

s32 TMCJPEGDEC_decode_iquant(s32* block, u8* conv_row_ptr, u32* dc_predict_row_ptr, TMCCJPEGDecWork* work) {
    TMCHuffmanEntry dcEntry;
    u8* huff_sym;
    const TMCHuffmanEntry* ac_fast;
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
    s32 zz;
    s32 q;
    const TMCHuffmanEntry* dc_fast;
    const u8* zztbl;

    bit_pos = work->bitCount;
    dc_fast = (const TMCHuffmanEntry*)work->pDCFast;

    if (bit_pos <= 8) {
        r = TMCJPEGDEC_load_buff(work);
        if (r < 0) {
            return r;
        }
    }

    bit_pos = work->bitCount;
    bit_data = work->bitBuf;
    {
        dcEntry = readHuffmanEntry(dc_fast, (bit_data >> (bit_pos - 8)) & 0xFF);
        r = dcEntry.bitLength;
        extra = dcEntry.symbol;
    }

    if (r != 0) {
        work->bitCount = bit_pos - r;
        r = extra;
    } else {
        huff_sym = work->pDCHuffSym;
        huff_tbl = work->pDCHuffTbl;
        r = decodeLongHuffman(bit_pos, (const TMCHuffmanEntry*)huff_tbl, huff_sym, work);
        if (r < 0) {
            return r;
        }
    }

    blk0 = ((s32*)conv_row_ptr)[0];
    if (r != 0) {
        bit_pos = work->bitCount;
        if (bit_pos <= r) {
            s32 load_ret = TMCJPEGDEC_load_buff(work);
            if (load_ret < 0) {
                return load_ret;
            }
        }
        bit_pos = work->bitCount;
        bit_data = work->bitBuf;
        tmp = 1 << r;
        extra = tmp - 1;
        bit_pos -= r;
        work->bitCount = bit_pos;
        extra = extra & (bit_data >> bit_pos);
        if (((s32)tmp >> 1) > extra) {
            extra -= tmp - 1;
        }
        dc_predict_row_ptr[0] += extra;
    }

    *block = dc_predict_row_ptr[0] * blk0;

    {
        ac_fast = (const TMCHuffmanEntry*)work->pACFast;
        huff_tbl = work->pACHuffTbl;
        huff_sym = work->pACHuffSym;

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
        acEntry = readHuffmanEntry(ac_fast, (bit_data >> t) & 0xFF);

        do {
            s32 ac_thresh = acEntry.bitLength;
            if (ac_thresh != 0) {
                bit_pos = work->bitCount;
                bit_pos -= ac_thresh;
                work->bitCount = bit_pos;
                r = acEntry.symbol;
            } else {
                bit_pos = work->bitCount;
                r = decodeACHuffman(bit_pos, (const TMCHuffmanEntry*)huff_tbl, huff_sym, work);
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
                bit_pos = work->bitCount;
                tmp = 1 << t;
                bit_data = work->bitBuf;
                extra = tmp - 1;
                bit_pos -= t;
                work->bitCount = bit_pos;
                t = bit_pos - 8;
                extra = extra & (bit_data >> bit_pos);
                q = ((s32*)conv_row_ptr)[(u8)zz];
                acEntry = readHuffmanEntry(ac_fast, (bit_data >> t) & 0xFF);

                if (((s32)tmp >> 1) > extra) {
                    extra -= tmp - 1;
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
                acEntry = readHuffmanEntry(ac_fast, tmp >> 2);

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
