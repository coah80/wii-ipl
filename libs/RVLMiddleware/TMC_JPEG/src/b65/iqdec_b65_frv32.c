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

s32 TMCJPEGDEC_decode_iquant(s32* block, u8* conv_row_ptr, u32* dc_predict_row_ptr, TMCCJPEGDecWork* work) {
    TMCHuffmanEntry acEntry;
    const TMCHuffmanEntry* ac_fast;
    u8* huff_sym;
    u32* huff_tbl;
    s32 bit_pos;
    u32 bit_data;
    const TMCHuffmanEntry* dc_fast;
    s32 r;
    s32 blk0;
    s32 idx;
    s32 extra;
    s32 t;
    s32 zz;
    s32 q;
    u32 tmp;
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
    tmp = bit_pos - 8;
    tmp = ((bit_data >> tmp) & 0xFF) << 2;
    {
        TMCHuffmanEntry dcEntry = readHuffmanEntry(dc_fast, tmp >> 2);
        r = dcEntry.bitLength;
        extra = dcEntry.symbol;
    }

    if (r != 0) {
        bit_pos -= r;
        work->bitCount = bit_pos;
        r = extra;
    } else {
        u32 code;
        unsigned int i;
        const TMCHuffmanEntry* entry;
        s32 thresh;
        s32 offs;

        huff_sym = work->pDCHuffSym;
        huff_tbl = work->pDCHuffTbl;

        if (bit_pos <= 17) {
            r = TMCJPEGDEC_load_buff(work);
            if (r < 0) {
                return r;
            }
        }
        bit_pos = work->bitCount;
        bit_data = work->bitBuf;
        bit_pos -= 9;
        code = (bit_data >> bit_pos) & 0x1FF;
        work->bitCount = bit_pos;

        i = 9;
        entry = (const TMCHuffmanEntry*)huff_tbl + 9;

        goto dc_entry;

        while (1) {
            i++;
            entry++;
            if (i > 16) {
                r = TMCC_ERROR_OVERFLOW;
                goto dc_end;
            }

            bit_pos = work->bitCount;
            code <<= 1;
            bit_data = work->bitBuf;
            bit_pos--;
            work->bitCount = bit_pos;
            code |= (bit_data >> bit_pos) & 1;

        dc_entry:
            {
                TMCHuffmanEntry decoded = readHuffmanLimit(entry);
                thresh = decoded.bitLength;
                offs = decoded.symbol;
            }

            if (code > (u32)thresh) {
                continue;
            }

            code = code - entry->bitLength + offs;
            r = huff_sym[code & 0xFF];
            break;
        }

    dc_end:
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
            bit_pos = work->bitCount;
        }
        bit_data = work->bitBuf;
        tmp = 1 << r;
        extra = tmp - 1;
        bit_pos -= r;
        work->bitCount = bit_pos;
        extra = extra & (bit_data >> bit_pos);
        if (extra < (s32)tmp >> 1) {
            extra -= tmp - 1;
        }
        dc_predict_row_ptr[0] += extra;
    }

    *block = dc_predict_row_ptr[0] * blk0;

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

    while (idx < 64) {
        s32 ac_thresh = acEntry.bitLength;
        if (ac_thresh != 0) {
            bit_pos = work->bitCount;
            bit_pos -= ac_thresh;
            work->bitCount = bit_pos;
            r = acEntry.symbol;
        } else {
            u32 code;
            unsigned int i;
            const TMCHuffmanEntry* entry;
            s32 thresh;
            s32 offs;

            bit_pos = work->bitCount;
            if (bit_pos <= 17) {
                r = TMCJPEGDEC_load_buff(work);
                if (r < 0) {
                    return r;
                }
                bit_pos = work->bitCount;
            }
            bit_data = work->bitBuf;
            bit_pos -= 9;
            code = (bit_data >> bit_pos) & 0x1FF;
            work->bitCount = bit_pos;

            i = 9;
            entry = (const TMCHuffmanEntry*)huff_tbl + 9;

            goto ac_entry_huff;

            while (1) {
                i++;
                entry++;
                if (i > 16) {
                    r = TMCC_ERROR_OVERFLOW;
                    goto ac_end;
                }

                bit_pos = work->bitCount;
                code <<= 1;
                bit_data = work->bitBuf;
                bit_pos--;
                work->bitCount = bit_pos;
                code |= (bit_data >> bit_pos) & 1;

            ac_entry_huff:
                {
                    TMCHuffmanEntry decoded = readHuffmanLimit(entry);
                    thresh = decoded.bitLength;
                    offs = decoded.symbol;
                }

                if (code > (u32)thresh) {
                    continue;
                }

                code = code - entry->bitLength + offs;
                r = huff_sym[code & 0xFF];
                break;
            }

        ac_end:
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
                bit_pos = work->bitCount;
            }
            tmp = 1 << t;
            bit_data = work->bitBuf;
            extra = tmp - 1;
            bit_pos -= t;
            work->bitCount = bit_pos;
            t = bit_pos - 8;
            extra = extra & (bit_data >> bit_pos);
            acEntry = readHuffmanEntry(ac_fast, (bit_data >> t) & 0xFF);

            if (extra < (s32)tmp >> 1) {
                extra -= tmp - 1;
            }

            q = ((s32*)conv_row_ptr)[zz];
            block[zz] = extra * q;

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
    }

    if (idx > 64) {
        return TMCC_ERROR_OVERFLOW;
    }

    idx--;
    return TMCJPEGDEC_Zigzag_loop[idx];
}
