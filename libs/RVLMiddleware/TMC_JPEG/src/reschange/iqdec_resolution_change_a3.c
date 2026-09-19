#include <tmc_jpeg_internal.h>

extern void* memset(void* dest, int value, unsigned long size);

static s32 TMCJPEGDEC_vl_decode_rc(u32* huff_tbl, u8* huff_sym, TMCCJPEGDecWork* work);

#ifdef __MWERKS__
asm s32 TMCJPEGDEC_decode_iquant_rc(register s32* block, register u8* conv_row_ptr, register u32* dc_predict_row_ptr, register TMCCJPEGDecWork* work) {
    nofralloc

    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stmw r21, 0x14(r1)
    mr r22, r3
    mr r23, r4
    mr r25, r5
    mr r24, r6
    lwz r0, 4(r6)
    lwz r21, 0x498(r6)
    cmpwi r0, 8
    bgt _decode_iquant_rc_have_dc_bits
    mr r3, r24
    bl TMCJPEGDEC_load_buff
    cmpwi r3, 0
    bge _decode_iquant_rc_have_dc_bits
    b _decode_iquant_rc_return

_decode_iquant_rc_have_dc_bits:
    lwz r4, 4(r24)
    lwz r3, 0(r24)
    addi r0, r4, -8
    srw r0, r3, r0
    rlwinm r0, r0, 2, 0x16, 0x1d
    lhzx r5, r21, r0
    cmpwi r5, 0
    beq _decode_iquant_rc_decode_dc
    add r3, r21, r0
    subf r0, r5, r4
    lhz r21, 2(r3)
    stw r0, 4(r24)
    b _decode_iquant_rc_have_dc_value

_decode_iquant_rc_decode_dc:
    lwz r3, 0x49c(r24)
    mr r5, r24
    lwz r4, 0x4a0(r24)
    bl TMCJPEGDEC_vl_decode_rc
    cmpwi r3, 0
    mr r21, r3
    bge _decode_iquant_rc_have_dc_value
    b _decode_iquant_rc_return

_decode_iquant_rc_have_dc_value:
    cmpwi r21, 0
    beq _decode_iquant_rc_store_dc
    lwz r0, 4(r24)
    cmpw r0, r21
    bgt _decode_iquant_rc_read_dc_bits
    mr r3, r24
    bl TMCJPEGDEC_load_buff
    cmpwi r3, 0
    bge _decode_iquant_rc_read_dc_bits
    b _decode_iquant_rc_return

_decode_iquant_rc_read_dc_bits:
    lwz r0, 4(r24)
    li r4, 1
    lwz r3, 0(r24)
    slw r6, r4, r21
    subf r4, r21, r0
    addi r5, r6, -1
    srwi r0, r6, 1
    srw r3, r3, r4
    stw r4, 4(r24)
    and r3, r5, r3
    cmplw r0, r3
    ble _decode_iquant_rc_store_dc_bits
    subf r3, r5, r3

_decode_iquant_rc_store_dc_bits:
    lwz r0, 0(r25)
    add r0, r0, r3
    stw r0, 0(r25)

_decode_iquant_rc_store_dc:
    lwz r5, 0(r25)
    addi r3, r22, 4
    lwz r0, 0(r23)
    li r4, 0
    mullw r0, r5, r0
    stw r0, 0(r22)
    lwz r30, 0x4a8(r24)
    lwz r26, 0x4ac(r24)
    lwz r25, 0x4b0(r24)
    lwz r27, 0x1834(r24)
    lwz r5, 0x1838(r24)
    bl memset
    lis r21, TMCJPEGDEC_Zigzag_data@ha
    li r28, 1
    addi r21, r21, TMCJPEGDEC_Zigzag_data@l
    li r31, 1

_decode_iquant_rc_ac_loop:
    lwz r0, 4(r24)
    cmpwi r0, 8
    bgt _decode_iquant_rc_have_ac_bits
    mr r3, r24
    bl TMCJPEGDEC_load_buff
    cmpwi r3, 0
    bge _decode_iquant_rc_have_ac_bits
    b _decode_iquant_rc_return

_decode_iquant_rc_have_ac_bits:
    lwz r4, 4(r24)
    lwz r3, 0(r24)
    addi r0, r4, -8
    srw r0, r3, r0
    rlwinm r0, r0, 2, 0x16, 0x1d
    add r3, r30, r0
    lhzx r0, r30, r0
    cmpwi r0, 0
    beq _decode_iquant_rc_decode_ac
    lhz r3, 2(r3)
    subf r0, r0, r4
    stw r0, 4(r24)
    b _decode_iquant_rc_have_ac_value

_decode_iquant_rc_decode_ac:
    mr r3, r26
    mr r4, r25
    mr r5, r24
    bl TMCJPEGDEC_vl_decode_rc
    cmpwi r3, 0
    bge _decode_iquant_rc_have_ac_value
    b _decode_iquant_rc_return

_decode_iquant_rc_have_ac_value:
    clrlwi. r29, r3, 0x1c
    beq _decode_iquant_rc_no_ac_bits
    lwz r0, 4(r24)
    srawi r3, r3, 4
    add r28, r28, r3
    cmpw r0, r29
    bgt _decode_iquant_rc_read_ac_bits
    mr r3, r24
    bl TMCJPEGDEC_load_buff
    cmpwi r3, 0
    bge _decode_iquant_rc_read_ac_bits
    b _decode_iquant_rc_return

_decode_iquant_rc_read_ac_bits:
    cmpw r28, r27
    ble _decode_iquant_rc_store_ac
    lwz r0, 4(r24)
    cmpwi r28, 0x40
    subf r0, r29, r0
    stw r0, 4(r24)
    blt _decode_iquant_rc_increment
    li r3, -0x64
    b _decode_iquant_rc_return

_decode_iquant_rc_increment:
    addi r28, r28, 1
    b _decode_iquant_rc_loop_check

_decode_iquant_rc_store_ac:
    lwz r0, 4(r24)
    slw r6, r31, r29
    lwz r3, 0(r24)
    addi r5, r6, -1
    subf r4, r29, r0
    srwi r0, r6, 1
    srw r3, r3, r4
    stw r4, 4(r24)
    and r4, r5, r3
    cmplw r0, r4
    ble _decode_iquant_rc_have_extra
    subf r4, r5, r4

_decode_iquant_rc_have_extra:
    cmpwi r28, 0x40
    blt _decode_iquant_rc_store_coeff
    li r3, -0x64
    b _decode_iquant_rc_return

_decode_iquant_rc_store_coeff:
    lbzx r0, r21, r28
    addi r28, r28, 1
    slwi r3, r0, 2
    lwzx r0, r23, r3
    mullw r0, r4, r0
    stwx r0, r22, r3
    b _decode_iquant_rc_loop_check

_decode_iquant_rc_no_ac_bits:
    cmpwi r3, 0
    bne _decode_iquant_rc_zrl
    li r3, 0
    b _decode_iquant_rc_return

_decode_iquant_rc_zrl:
    addi r28, r28, 0x10

_decode_iquant_rc_loop_check:
    cmpwi r28, 0x40
    blt _decode_iquant_rc_ac_loop
    li r3, 0

_decode_iquant_rc_return:
    lmw r21, 0x14(r1)
    lwz r0, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}
#else
s32 TMCJPEGDEC_decode_iquant_rc(s32* block, u8* conv_row_ptr, u32* dc_predict_row_ptr, TMCCJPEGDecWork* work) {
    const u8* zztbl;
    u16* ac_fast;
    s32 t;
    s32 idx;
    s32 blk_size;

    u32 tmp;
    u32* ac_vl;
    u8* ac_sym;
    s32 r;
    s32 extra;
    s32 val;

    s32 blk_mul;
    s32 bit_pos;
    u32 bit_data;

    u16* dcf;
    s32* conv_row;

    conv_row = (s32*)conv_row_ptr;
    dcf = work->pDCFast;
    if (work->bitCount <= 8) {
        if (r = TMCJPEGDEC_load_buff(work), r < 0) {
            return r;
        }
    }

    bit_pos = work->bitCount;
    tmp = (work->bitBuf >> (bit_pos - 8) & 0xFF) << 2;
    val = dcf[tmp >> 1];
    if (val != 0) {
        tmp = *(u16*)((u8*)dcf + tmp + 2);
        work->bitCount -= val;
        val = tmp;
    } else {
        val = TMCJPEGDEC_vl_decode_rc(work->pDCHuffTbl, work->pDCHuffSym, work);
        if (val < 0) {
            return val;
        }
    }

    if (val != 0) {
        if (work->bitCount <= val) {
            if (r = TMCJPEGDEC_load_buff(work), r < 0) {
                return r;
            }
        }
        tmp = 1UL << val;
        bit_pos = work->bitCount - val;
        work->bitCount = bit_pos;
        bit_data = work->bitBuf;

        extra = tmp - 1;
        extra = extra & (bit_data >> bit_pos);
        if (tmp >> 1 > (u32)extra) {
            extra -= (tmp - 1);
        }
        dc_predict_row_ptr[0] += extra;
    }

    *block = dc_predict_row_ptr[0] * conv_row[0];

    ac_fast = work->pACFast;
    ac_vl = work->pACHuffTbl;
    ac_sym = work->pACHuffSym;
    blk_size = work->blockSize;
    blk_mul = work->blockSizeMul;

    memset((u8*)block + 4, 0, blk_mul);

    zztbl = TMCJPEGDEC_Zigzag_data;
    idx = 1;
    do {
        if (work->bitCount <= 8) {
            if (r = TMCJPEGDEC_load_buff(work), r < 0) {
                return r;
            }
        }

        {
            u16* ac_entry = (u16*)((u8*)ac_fast + ((work->bitBuf >> (work->bitCount - 8) & 0xFF) << 2));
            val = *ac_entry;
            if (val != 0) {
                tmp = val;
                val = *(ac_entry + 1);
                work->bitCount -= tmp;
            } else {
                if (val = TMCJPEGDEC_vl_decode_rc(ac_vl, ac_sym, work), val < 0) {
                    return val;
                }
            }
        }

        t = val & 0x0F;
        if (t != 0) {
            val = val >> 4;
            idx += val;

            if (work->bitCount <= t) {
                if (r = TMCJPEGDEC_load_buff(work), r < 0) {
                    return r;
                }
            }

            if (idx > blk_size) {
                work->bitCount -= t;
                if (idx >= 64) {
                    return TMCC_ERROR_OVERFLOW;
                }
                idx++;
            } else {
                bit_pos = work->bitCount - t;
                work->bitCount = bit_pos;
                bit_data = work->bitBuf;

                tmp = 1UL << t;
                extra = tmp - 1;
                extra = extra & (bit_data >> bit_pos);
                if (tmp >> 1 > extra) {
                    extra -= tmp - 1;
                }

                if (idx >= 64) {
                    return TMCC_ERROR_OVERFLOW;
                }
                *(s32*)((u8*)block + zztbl[idx] * 4) = extra * conv_row[zztbl[idx]];
                idx++;
            }
        } else {
            if (val == 0) {
                return 0;
            }
            idx += 16;
        }
    } while (idx < 64);

    return 0;
}
#endif

static s32 TMCJPEGDEC_vl_decode_rc(u32* huff_tbl, u8* huff_sym, TMCCJPEGDecWork* work) {
    s32 bit_pos;
    u32 bit_data;
    u16* entry;
    u32 code;
    unsigned int i;
    s32 r;

    bit_pos = work->bitCount;

    if (bit_pos <= 17) {
        r = TMCJPEGDEC_load_buff(work);
        if (r < 0) {
            return r;
        }
    }

    bit_pos = work->bitCount;
    entry = (u16*)((u8*)huff_tbl + 0x24);
    bit_data = work->bitBuf;
    i = 9;
    bit_pos -= 9;
    code = (bit_data >> bit_pos) & 0x1FF;
    work->bitCount = bit_pos;

    goto entry_check;

    do {
        i++;
        entry += 2;
        if (i > 16) {
            return TMCC_ERROR_OVERFLOW;
        }

        bit_pos = work->bitCount;
        code <<= 1;
        bit_data = work->bitBuf;
        bit_pos--;
        work->bitCount = bit_pos;
        code |= (bit_data >> bit_pos) & 1;

    entry_check: {
        typedef struct {
            u16 t;
            u16 o;
        } HuffEnt;
        HuffEnt local = *(HuffEnt*)entry;
        u32 combined = *(u32*)&local;
        u32 combined2 = combined;
        u16 th = *(u16*)&combined2;
        s32 tmp;

        if (code > (u32)th) {
            continue;
        }

        tmp = code - local.t;
        code = tmp + (u32)local.o;
    }
        return huff_sym[code & 0xFF];
    } while (1);
}
