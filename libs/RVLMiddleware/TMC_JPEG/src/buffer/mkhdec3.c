#include <tmc_jpeg_internal.h>

extern void* memcpy(void* dest, const void* src, unsigned long size);
extern void* memset(void* dest, int value, unsigned long size);

#ifdef __MWERKS__
asm s32 TMCJPEGDEC_make_huffdec(register const u8* dht, register const u8* tb, register TMCHuffParam* hp) {
    nofralloc

    stwu r1, -0x840(r1)
    mflr r0
    li r6, 1
    li r7, 1
    stw r0, 0x844(r1)
    stmw r20, 0x810(r1)
    mr r26, r3
    mr r27, r4
    addi r4, r1, 0x408
    addi r3, r3, 1
    lwz r31, 0(r5)
    lwz r30, 4(r5)
    lwz r29, 8(r5)
    lbz r28, 0xc(r5)
    li r5, 0

_make_huffdec_count_loop:
    lbz r0, 0(r3)
    cmpw r7, r0
    ble _make_huffdec_count_store
    addi r6, r6, 1
    li r7, 1
    cmpwi r6, 0x10
    addi r3, r3, 1
    ble _make_huffdec_count_loop
    slwi r0, r5, 2
    addi r7, r1, 0x408
    li r3, 0
    stwx r3, r7, r0
    b _make_huffdec_count_done

_make_huffdec_count_store:
    addi r5, r5, 1
    stw r6, 0(r4)
    cmpw r5, r28
    addi r4, r4, 4
    ble _make_huffdec_count_next
    li r3, -0x40
    b _make_huffdec_return

_make_huffdec_count_next:
    addi r7, r7, 1
    b _make_huffdec_count_loop

_make_huffdec_count_done:
    lwz r0, 0x408(r1)
    addi r6, r1, 8
    li r9, 0
    li r8, 0
    clrlwi r10, r0, 24
    li r4, 1
    b _make_huffdec_values_loop

_make_huffdec_values_inner:
    clrlwi r5, r10, 24
    slwi r3, r8, 2
    b _make_huffdec_values_store_check

_make_huffdec_values_store:
    clrlwi r0, r9, 16
    addi r7, r7, 4
    stwx r0, r6, r3
    addi r8, r8, 1
    addi r3, r3, 4
    addi r9, r9, 1

_make_huffdec_values_store_check:
    lwz r0, 0(r7)
    clrlwi r0, r0, 24
    cmplw r5, r0
    beq _make_huffdec_values_store
    clrlwi r3, r9, 16
    slw r0, r4, r5
    cmpw r3, r0
    blt _make_huffdec_values_next
    li r3, -0x40
    b _make_huffdec_return

_make_huffdec_values_next:
    clrlslwi r9, r9, 17, 1
    addi r10, r10, 1

_make_huffdec_values_loop:
    lwz r0, 0(r7)
    cmpwi r0, 0
    bne _make_huffdec_values_inner
    mr r3, r30
    li r4, 0
    li r5, 0x44
    bl memset
    addi r4, r1, 0x408
    addi r5, r1, 8
    li r6, 0
    mtctr r28
    cmpwi r28, 0
    ble _make_huffdec_valptr_done

_make_huffdec_valptr_loop:
    lwz r0, 0(r4)
    cmplwi r0, 0x10
    bgt _make_huffdec_valptr_next
    slwi r3, r0, 2
    lwz r0, 0(r5)
    add r3, r30, r3
    sth r6, 2(r3)
    sth r0, 0(r3)

_make_huffdec_valptr_next:
    addi r4, r4, 4
    addi r5, r5, 4
    addi r6, r6, 1
    bdnz _make_huffdec_valptr_loop

_make_huffdec_valptr_done:
    addi r4, r1, 8
    addi r12, r26, 1
    li r6, 0
    li r7, 1
    lis r3, 0x8000

_make_huffdec_table_loop:
    subfic r0, r7, 8
    li r8, 1
    slw r5, r8, r0
    b _make_huffdec_table_count

_make_huffdec_table_store:
    lwz r10, 0(r4)
    cmpwi cr1, r5, 0
    mr r9, r5
    slw r10, r10, r0
    ble cr1, _make_huffdec_table_next
    cmpwi r5, 8
    ble _make_huffdec_table_short
    li r21, 0
    blt cr1, _make_huffdec_table_short_check
    addi r11, r3, 1
    cmpw r5, r11
    blt _make_huffdec_table_short_check
    li r21, 1

_make_huffdec_table_short_check:
    cmpwi r21, 0
    beq _make_huffdec_table_short
    subi r11, r5, 1
    slwi r26, r10, 2
    srwi r11, r11, 3
    mtctr r11
    cmpwi r5, 8
    ble _make_huffdec_table_short

_make_huffdec_table_unrolled:
    sthx r7, r31, r26
    add r25, r31, r26
    addi r11, r10, 1
    addi r22, r10, 2
    lbzx r24, r27, r6
    slwi r21, r11, 2
    addi r11, r10, 3
    addi r30, r10, 6
    sth r24, 2(r25)
    slwi r23, r11, 2
    addi r11, r10, 4
    add r20, r31, r21
    sthx r7, r31, r21
    slwi r24, r11, 2
    addi r11, r10, 5
    slwi r22, r22, 2
    lbzx r21, r27, r6
    slwi r25, r11, 2
    addi r11, r10, 7
    slwi r30, r30, 2
    sth r21, 2(r20)
    add r20, r31, r23
    add r21, r31, r24
    slwi r11, r11, 2
    sthux r7, r22, r31
    add r23, r31, r25
    add r25, r31, r11
    add r24, r31, r30
    lbzx r11, r27, r6
    addi r10, r10, 8
    addi r26, r26, 0x20
    subi r9, r9, 8
    sth r11, 2(r22)
    sth r7, 0(r20)
    lbzx r11, r27, r6
    sth r11, 2(r20)
    sth r7, 0(r21)
    lbzx r11, r27, r6
    sth r11, 2(r21)
    sth r7, 0(r23)
    lbzx r11, r27, r6
    sth r11, 2(r23)
    sthx r7, r31, r30
    lbzx r11, r27, r6
    sth r11, 2(r24)
    sth r7, 0(r25)
    lbzx r11, r27, r6
    sth r11, 2(r25)
    bdnz _make_huffdec_table_unrolled

_make_huffdec_table_short:
    slwi r10, r10, 2
    add r11, r31, r10
    mtctr r9
    cmpwi r9, 0
    ble _make_huffdec_table_next

_make_huffdec_table_short_loop:
    sth r7, 0(r11)
    subi r9, r9, 1
    lbzx r10, r27, r6
    sth r10, 2(r11)
    addi r11, r11, 4
    bdnz _make_huffdec_table_short_loop

_make_huffdec_table_next:
    addi r8, r8, 1
    addi r4, r4, 4
    addi r6, r6, 1

_make_huffdec_table_count:
    lbz r9, 0(r12)
    cmpw r8, r9
    ble _make_huffdec_table_store
    addi r7, r7, 1
    addi r12, r12, 1
    cmpwi r7, 8
    ble _make_huffdec_table_loop
    mr r3, r29
    mr r4, r27
    mr r5, r28
    bl memcpy
    li r3, 0

_make_huffdec_return:
    lmw r20, 0x810(r1)
    lwz r0, 0x844(r1)
    mtlr r0
    addi r1, r1, 0x840
    blr
}
#else
s32 TMCJPEGDEC_make_huffdec(const u8* dht, const u8* tb, TMCHuffParam* hp) {
    u32 huffCount[256];
    u32 huffVal[256];
    u32* huffTable;
    u32* destTable;
    u8* valptr;
    u32 count;

    {
        u32* dest = huffCount;
        s32 bit_len = 1;
        s32 remaining = 1;
        const u8* bits = dht + 1;
        s32 sym_idx;

        huffTable = hp->huffTable;
        valptr = hp->valptr;
        destTable = hp->maxCode;
        count = hp->count;

        sym_idx = 0;

        for (;;) {
            s32 cnt = *bits;

            if (remaining > cnt) {
                bit_len++;
                remaining = 1;
                bits++;
                if (bit_len > 16) {
                    huffCount[sym_idx] = 0;
                    break;
                }
            } else {
                *dest = bit_len;
                dest++;
                sym_idx++;
                if (sym_idx > (s32)count) {
                    return -0x40;
                }
                remaining++;
            }
        }
    }

    {
        s32 sv_idx = 0;
        s32 i = 0;
        u32 cur = huffCount[0] & 0xFF;

        while (cur != 0) {
            while (i < (s32)count && (huffCount[i] & 0xFF) == cur) {
                huffVal[i] = sv_idx & 0xFFFF;
                sv_idx++;
                i++;
            }
            if (sv_idx > (1 << cur)) {
                return -0x40;
            }
            sv_idx <<= 1;
            cur = huffCount[i] & 0xFF;
        }
    }

    memset(valptr, 0, 0x44);

    {
        s32 i;

        for (i = 0; i < (s32)count; i++) {
            u32 bl = huffCount[i];

            if (bl <= 16) {
                valptr[bl] = (i << 16) | (huffVal[i] & 0xFFFF);
            }
        }
    }

    {
        const u8* bits_ptr = dht + 1;
        u32* hv_ptr = huffVal;
        s32 sym = 0;
        u32 bl;
        u32 cnt;
        u32 step;
        u32 n;
        u32 code;
        u32 base;
        s32 kk;

        for (bl = 1; bl <= 8; bl++) {
            cnt = *bits_ptr;
            step = 1 << (8 - bl);

            for (n = 0; n < cnt; n++) {
                code = *hv_ptr;
                hv_ptr++;
                base = code << (8 - bl);

                for (kk = 0; kk < (s32)step; kk++) {
                    ((u16*)huffTable)[(base + kk) * 2] = bl;
                    ((u16*)huffTable)[(base + kk) * 2 + 1] = tb[sym];
                }

                sym++;
            }

            bits_ptr++;
        }
    }

    memcpy(destTable, tb, count);

    return 0;
}
#endif

void TMCJPEGDEC_set_HuffmanTable(TMCHuffParam* tbl, s32 tblType, s32 tblID, TMCUnknownInfo* info) {
    TMCCJPEGDecWork* work = (TMCCJPEGDecWork*)info;
    void* hufftable;
    void* maxcode;
    void* valptr;

    if (tblType == 0) {
        switch (tblID) {
            case 0: {
                hufftable = &work->zigzagData[8];
                maxcode = work->maxCodeDC0;
                tbl->huffTable = hufftable;
                tbl->maxCode = maxcode;
                tbl->valptr = work->valPtrDC0;
                work->huffTblInitFlag[0] = 1;
                memset(hufftable, 0, 0x400);
                memset(work->maxCodeDC0, 0, 0x10);
                memset(work->valPtrDC0, 0, 0x44);
                break;
            }
            case 1: {
                hufftable = work->huffDecTblDC1;
                maxcode = work->maxCodeDC1;
                valptr = work->valPtrDC1;
                tbl->huffTable = hufftable;
                tbl->maxCode = maxcode;
                tbl->valptr = valptr;
                work->huffTblInitFlag[1] = 1;
                memset(hufftable, 0, 0x400);
                memset(work->maxCodeDC1, 0, 0x10);
                memset(work->valPtrDC1, 0, 0x44);
                break;
            }
        }
    } else {
        switch (tblID) {
            case 0: {
                hufftable = work->huffDecTblAC0;
                maxcode = work->maxCodeAC0;
                valptr = work->valPtrAC0;
                tbl->huffTable = hufftable;
                tbl->maxCode = maxcode;
                tbl->valptr = valptr;
                work->huffTblInitFlag[2] = 1;
                memset(hufftable, 0, 0x400);
                memset(work->maxCodeAC0, 0, 0x100);
                memset(work->valPtrAC0, 0, 0x44);
                break;
            }
            case 1: {
                hufftable = work->huffDecTblAC1;
                maxcode = work->maxCodeAC1;
                valptr = work->valPtrAC1;
                tbl->huffTable = hufftable;
                tbl->maxCode = maxcode;
                tbl->valptr = valptr;
                work->huffTblInitFlag[3] = 1;
                memset(hufftable, 0, 0x400);
                memset(work->maxCodeAC1, 0, 0x100);
                memset(work->valPtrAC1, 0, 0x44);
                break;
            }
        }
    }
}
