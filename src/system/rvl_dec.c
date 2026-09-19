#include "system/rvl_dec.h"

#define SZS_SIGNATURE 0x0059617A /* 'Yaz */
#define ASH_SIGNATURE 0x00415348 /* 'ASH' */
#define ASR_SIGNATURE 0x00415352 /* 'ASR' */

static u8 work[0x9008];
extern u8 _f_bss[];

int Rvl_decode(u8* out, u8* in) {
#ifdef TARGET_RVL
    // Original ASM Implementation

    register u8* dataIn = in;

    // clang-format off
#ifdef __MWERKS__
    asm volatile {
        // Get magic
        lwz     r5, 0(dataIn)
        lis     r6, SZS_SIGNATURE@h
        srwi    r5, r5, 8

        // Check is it's SZS with the magic 'Yaz'
        ori     r6, r6, SZS_SIGNATURE@l
        cmpl    r5, r6
        beq     Rvl_decode_szs

        // Check is it's ASH with the magic 'ASH'
        lis     r6, ASH_SIGNATURE@h
        ori     r6, r6, ASH_SIGNATURE@l
        cmpl    r5, r6
        beq     Rvl_decode_ash

        // Check is it's ASR with the magic 'ASR'
        lis     r6, ASR_SIGNATURE@h
        ori     r6, r6, ASR_SIGNATURE@l
        cmpl    r5, r6
        beq     Rvl_decode_asr
    };
#endif // __MWERKS__
    // clang-format on

    // Otherwise
    return 0;
#else
    // Custom C Implementation

    // Get magic
    u32 magic = Rvl_decode_get_magic(in);
    switch (magic) {
        // Check is it's SZS with the magic 'Yaz'
        case SZS_SIGNATURE: {
            return Rvl_decode_szs(out, in);
        }
        // Check is it's ASH with the magic 'ASH'
        case ASH_SIGNATURE: {
            return Rvl_decode_ash(out, in);
        }
        // Check is it's ASR with the magic 'ASR'
        case ASR_SIGNATURE: {
            return Rvl_decode_asr(out, in);
        }
        // Otherwise
        default: {
            return 0;
        }
    }
#endif  // TARGET_RVL
}

#ifdef __MWERKS__
asm int Rvl_decode_szs(register u8* out, register u8* in) {
    nofralloc
    lwz r5, 0x4(r4)
    li r6, 0x0
    or r0, r5, r5
    addi r4, r4, 0x10
Rvl_decode_szs_bit_loop:
    rlwinm. r6, r6, 0x1f, 0x1, 0x1f
    bne Rvl_decode_szs_bit_loop_body
    lbz r7, 0x0(r4)
    li r6, 0x80
    addi r4, r4, 0x1
Rvl_decode_szs_bit_loop_body:
    and. r8, r6, r7
    lbz r8, 0x0(r4)
    beq Rvl_decode_szs_backref
    addi r4, r4, 0x1
    subic. r5, r5, 0x1
    stb r8, 0x0(r3)
    addi r3, r3, 0x1
    bne Rvl_decode_szs_bit_loop
    b Rvl_decode_szs_done
Rvl_decode_szs_backref:
    lbz r9, 0x1(r4)
    rlwinm. r10, r8, 0x1c, 0x4, 0x1f
    addi r4, r4, 0x2
    bne Rvl_decode_szs_copy_length
    lbz r10, 0x0(r4)
    addi r4, r4, 0x1
    addi r10, r10, 0x10
Rvl_decode_szs_copy_length:
    rlwimi r9, r8, 0x8, 0x14, 0x17
    subf r5, r10, r5
    subf r8, r9, r3
    lbz r9, -0x1(r8)
    subi r5, r5, 0x2
    stb r9, 0x0(r3)
    lbz r9, 0x0(r8)
    stb r9, 0x1(r3)
    addi r8, r8, 0x2
    rlwinm. r9, r10, 0x1d, 0x3, 0x1f
    addi r3, r3, 0x2
    beq Rvl_decode_szs_tail
    mtspr CTR, r9
Rvl_decode_szs_copy_loop:
    lbz r9, -0x1(r8)
    stb r9, 0x0(r3)
    lbz r9, 0x0(r8)
    stb r9, 0x1(r3)
    lbz r9, 0x1(r8)
    stb r9, 0x2(r3)
    lbz r9, 0x2(r8)
    stb r9, 0x3(r3)
    lbz r9, 0x3(r8)
    stb r9, 0x4(r3)
    lbz r9, 0x4(r8)
    stb r9, 0x5(r3)
    lbz r9, 0x5(r8)
    stb r9, 0x6(r3)
    lbz r9, 0x6(r8)
    stb r9, 0x7(r3)
    addi r8, r8, 0x8
    addi r3, r3, 0x8
    bdnz Rvl_decode_szs_copy_loop
    andi. r10, r10, 0x7
    beq Rvl_decode_szs_done_copy
Rvl_decode_szs_tail:
    mtspr CTR, r10
Rvl_decode_szs_tail_loop:
    lbz r9, -0x1(r8)
    addi r8, r8, 0x1
    stb r9, 0x0(r3)
    addi r3, r3, 0x1
    bdnz Rvl_decode_szs_tail_loop
Rvl_decode_szs_done_copy:
    cmpwi r5, 0x0
    bgt Rvl_decode_szs_bit_loop
Rvl_decode_szs_done:
    or r3, r0, r0
    blr
}
#else
int Rvl_decode_szs(u8* out, u8* in) {
    register u8* pbVar1;
    register u8 bVar2;
    register u8 bVar3;
    register u8* pbVar5;
    register int iVar6;
    register int iVar7;
    register u32 uVar8;
    register u32 uVar9;
    register u32 uVar10;
    register u32 param_5;
    iVar6 = *(int*)(in + 4);
    uVar8 = 0;
    in += 0x10;
    iVar7 = iVar6;
    do {
next:
        while (1) {
            uVar8 >>= 1;
            pbVar5 = in;
            if (uVar8 == 0) {
                param_5 = *in;
                uVar8 = 0x80;
                pbVar5 = in + 1;
            }
            bVar2 = *pbVar5;
            if ((uVar8 & param_5) == 0) {
                break;
            }
            in = pbVar5 + 1;
            iVar7--;
            *out = bVar2;
            out++;
            if (iVar7 != 0) {
                goto next;
            }
            goto done;
        }
        uVar9 = bVar2 >> 4;
        in = pbVar5 + 2;
        if (uVar9 == 0) {
            bVar3 = *in;
            in = pbVar5 + 3;
            uVar9 = bVar3 + 0x10;
        }
        pbVar5 = out - (((bVar2 & 0xf) << 8) | pbVar5[1]);
        iVar7 = (iVar7 - uVar9) - 2;
        *out = pbVar5[-1];
        out[1] = *pbVar5;
        pbVar5 += 2;
        uVar10 = uVar9 >> 3;
        out += 2;
        if (uVar10 != 0) {
            do {
                *out = pbVar5[-1];
                out[1] = *pbVar5;
                out[2] = pbVar5[1];
                out[3] = pbVar5[2];
                out[4] = pbVar5[3];
                out[5] = pbVar5[4];
                out[6] = pbVar5[5];
                out[7] = pbVar5[6];
                pbVar5 += 8;
                out += 8;
                uVar10--;
            } while (uVar10 != 0);
        }
        for (uVar9 &= 7; uVar9 != 0; uVar9--) {
            pbVar1 = pbVar5 - 1;
            pbVar5++;
            *out = *pbVar1;
            out++;
        }
    } while (0 < iVar7);
done:
    return iVar6;
}
#endif
#ifdef __MWERKS__
asm int Rvl_decode_ash(register u8* out, register u8* in) {
    nofralloc
    stwu r1, -0x40(r1)
    stmw r21, 0x10(r1)
    lwz r5, 0x4(r4)
    clrlwi r5, r5, 8
    li r24, 0x10
    lwz r28, 0x8(r4)
    li r25, 0x0
    li r29, 0x0
    lwz r26, 0xc(r4)
    lwzx r30, r28, r4
    addi r28, r28, 0x4
    lis r8, _f_bss@h
    ori r8, r8, _f_bss@l
    addi r9, r8, 0x7fe
    addi r10, r9, 0x7fe
    addi r11, r10, 0x1ffe
    addi r31, r11, 0x1ffe
    li r23, 0x200
    li r22, 0x200
    li r27, 0x0
L_Rvl_decode_ash_primary_bit:
    cmpwi r25, 0x1f
    bne L_Rvl_decode_ash_primary_shift
    srwi. r0, r26, 31
    lwzx r26, r4, r24
    li r25, 0x0
    addi r24, r24, 0x4
    b L_Rvl_decode_ash_primary_bit_test
L_Rvl_decode_ash_primary_shift:
    srwi. r0, r26, 31
    addi r25, r25, 0x1
    slwi r26, r26, 1
L_Rvl_decode_ash_primary_bit_test:
    beq L_Rvl_decode_ash_primary_symbol
    ori r0, r23, 0x8000
    sth r0, 0x0(r31)
    ori r0, r23, 0x4000
    sth r0, 0x2(r31)
    addi r31, r31, 0x4
    addi r27, r27, 0x2
    addi r23, r23, 0x1
    addi r22, r22, 0x1
    b L_Rvl_decode_ash_primary_bit
L_Rvl_decode_ash_primary_symbol:
    li r12, 0x9
    add r21, r25, r12
    cmpwi r21, 0x20
    bgt L_Rvl_decode_ash_primary_cross
    subfic r21, r12, 0x20
    srw r6, r26, r21
    beq L_Rvl_decode_ash_primary_reload
    slw r26, r26, r12
    add r25, r25, r12
    b L_Rvl_decode_ash_primary_tree
L_Rvl_decode_ash_primary_reload:
    lwzx r26, r4, r24
    li r25, 0x0
    addi r24, r24, 0x4
    b L_Rvl_decode_ash_primary_tree
L_Rvl_decode_ash_primary_cross:
    subfic r0, r12, 0x20
    srw r6, r26, r0
    lwzx r26, r4, r24
    subfic r0, r21, 0x40
    addi r24, r24, 0x4
    srw r0, r26, r0
    or r6, r6, r0
    subi r25, r21, 0x20
    slw r26, r26, r25
L_Rvl_decode_ash_primary_tree:
    lhzu r12, -0x2(r31)
    subi r27, r27, 0x1
    andi. r0, r12, 0x8000
    clrlslwi r12, r12, 18, 1
    beq L_Rvl_decode_ash_primary_leaf
    sthx r6, r9, r12
    extrwi r6, r12, 14, 17
    cmpwi r27, 0x0
    bne L_Rvl_decode_ash_primary_tree
    b L_Rvl_decode_ash_secondary_init
L_Rvl_decode_ash_primary_leaf:
    sthx r6, r8, r12
    mr r23, r22
    b L_Rvl_decode_ash_primary_bit
L_Rvl_decode_ash_secondary_init:
    li r23, 0x800
    li r22, 0x800
L_Rvl_decode_ash_secondary_bit:
    cmpwi r29, 0x1f
    bne L_Rvl_decode_ash_secondary_shift
    srwi. r0, r30, 31
    lwzx r30, r4, r28
    li r29, 0x0
    addi r28, r28, 0x4
    b L_Rvl_decode_ash_secondary_bit_test
L_Rvl_decode_ash_secondary_shift:
    srwi. r0, r30, 31
    addi r29, r29, 0x1
    slwi r30, r30, 1
L_Rvl_decode_ash_secondary_bit_test:
    beq L_Rvl_decode_ash_secondary_symbol
    ori r0, r23, 0x8000
    sth r0, 0x0(r31)
    ori r0, r23, 0x4000
    sth r0, 0x2(r31)
    addi r31, r31, 0x4
    addi r27, r27, 0x2
    addi r23, r23, 0x1
    addi r22, r22, 0x1
    b L_Rvl_decode_ash_secondary_bit
L_Rvl_decode_ash_secondary_symbol:
    li r12, 0xb
    add r21, r29, r12
    cmpwi r21, 0x20
    bgt L_Rvl_decode_ash_secondary_cross
    subfic r21, r12, 0x20
    srw r7, r30, r21
    beq L_Rvl_decode_ash_secondary_reload
    slw r30, r30, r12
    add r29, r29, r12
    b L_Rvl_decode_ash_secondary_tree
L_Rvl_decode_ash_secondary_reload:
    lwzx r30, r4, r28
    li r29, 0x0
    addi r28, r28, 0x4
    b L_Rvl_decode_ash_secondary_tree
L_Rvl_decode_ash_secondary_cross:
    subfic r0, r12, 0x20
    srw r7, r30, r0
    lwzx r30, r4, r28
    subfic r0, r21, 0x40
    addi r28, r28, 0x4
    srw r0, r30, r0
    or r7, r7, r0
    subi r29, r21, 0x20
    slw r30, r30, r29
L_Rvl_decode_ash_secondary_tree:
    lhzu r12, -0x2(r31)
    subi r27, r27, 0x1
    andi. r0, r12, 0x8000
    clrlslwi r12, r12, 18, 1
    beq L_Rvl_decode_ash_secondary_leaf
    sthx r7, r11, r12
    extrwi r7, r12, 14, 17
    cmpwi r27, 0x0
    bne L_Rvl_decode_ash_secondary_tree
    b L_Rvl_decode_ash_decode_init
L_Rvl_decode_ash_secondary_leaf:
    sthx r7, r10, r12
    mr r23, r22
    b L_Rvl_decode_ash_secondary_bit
L_Rvl_decode_ash_decode_init:
    mr r0, r5
L_Rvl_decode_ash_decode_symbol:
    mr r12, r6
L_Rvl_decode_ash_decode_primary:
    cmpwi r12, 0x200
    blt L_Rvl_decode_ash_decode_literal
    cmpwi r25, 0x1f
    bne L_Rvl_decode_ash_decode_primary_shift
    srwi. r31, r26, 31
    lwzx r26, r4, r24
    addi r24, r24, 0x4
    li r25, 0x0
    b L_Rvl_decode_ash_decode_primary_bit_test
L_Rvl_decode_ash_decode_primary_shift:
    srwi. r31, r26, 31
    addi r25, r25, 0x1
    slwi r26, r26, 1
L_Rvl_decode_ash_decode_primary_bit_test:
    slwi r27, r12, 1
    bne L_Rvl_decode_ash_decode_primary_table
    lhzx r12, r8, r27
    b L_Rvl_decode_ash_decode_primary
L_Rvl_decode_ash_decode_primary_table:
    lhzx r12, r9, r27
    b L_Rvl_decode_ash_decode_primary
L_Rvl_decode_ash_decode_literal:
    cmpwi r12, 0x100
    bge L_Rvl_decode_ash_decode_copy
    stb r12, 0x0(r3)
    addi r3, r3, 0x1
    subi r5, r5, 0x1
    cmpwi r5, 0x0
    bne L_Rvl_decode_ash_decode_symbol
    b L_Rvl_decode_ash_return
L_Rvl_decode_ash_decode_copy:
    mr r23, r7
L_Rvl_decode_ash_copy_distance:
    cmpwi r23, 0x800
    blt L_Rvl_decode_ash_copy_start
    cmpwi r29, 0x1f
    bne L_Rvl_decode_ash_copy_bit_shift
    srwi. r31, r30, 31
    lwzx r30, r4, r28
    addi r28, r28, 0x4
    li r29, 0x0
    b L_Rvl_decode_ash_copy_bit_test
L_Rvl_decode_ash_copy_bit_shift:
    srwi. r31, r30, 31
    addi r29, r29, 0x1
    slwi r30, r30, 1
L_Rvl_decode_ash_copy_bit_test:
    slwi r27, r23, 1
    bne L_Rvl_decode_ash_copy_secondary_table
    lhzx r23, r10, r27
    b L_Rvl_decode_ash_copy_distance
L_Rvl_decode_ash_copy_secondary_table:
    lhzx r23, r11, r27
    b L_Rvl_decode_ash_copy_distance
L_Rvl_decode_ash_copy_start:
    subi r12, r12, 0xfd
    subf r23, r23, r3
    subf r5, r12, r5
    srwi. r31, r12, 3
    beq L_Rvl_decode_ash_copy_tail
    mtctr r31
L_Rvl_decode_ash_copy_block:
    lbz r31, -0x1(r23)
    stb r31, 0x0(r3)
    lbz r31, 0x0(r23)
    stb r31, 0x1(r3)
    lbz r31, 0x1(r23)
    stb r31, 0x2(r3)
    lbz r31, 0x2(r23)
    stb r31, 0x3(r3)
    lbz r31, 0x3(r23)
    stb r31, 0x4(r3)
    lbz r31, 0x4(r23)
    stb r31, 0x5(r3)
    lbz r31, 0x5(r23)
    stb r31, 0x6(r3)
    lbz r31, 0x6(r23)
    stb r31, 0x7(r3)
    addi r23, r23, 0x8
    addi r3, r3, 0x8
    bdnz L_Rvl_decode_ash_copy_block
    andi. r12, r12, 0x7
    beq L_Rvl_decode_ash_copy_done
L_Rvl_decode_ash_copy_tail:
    mtctr r12
L_Rvl_decode_ash_copy_tail_loop:
    lbz r31, -0x1(r23)
    addi r23, r23, 0x1
    stb r31, 0x0(r3)
    addi r3, r3, 0x1
    bdnz L_Rvl_decode_ash_copy_tail_loop
L_Rvl_decode_ash_copy_done:
    cmpwi r5, 0x0
    bne L_Rvl_decode_ash_decode_symbol
L_Rvl_decode_ash_return:
    mr r3, r0
    lmw r21, 0x10(r1)
    addi r1, r1, 0x40
    blr
}
#else
int Rvl_decode_ash(u8* out, u8* in) {
    u8* puVar1;
    u32* puVar2;
    u32 uVar3;
    u32 uVar4;
    u32 uVar5;
    u32 uVar6;
    int iVar7;
    u16 uVar8;
    u16 uVar10;
    u8* puVar9;
    int iVar11;
    u32 uVar12;
    u32 uVar13;
    u32 uVar14;
    u32 uVar15;
    int iVar16;
    int iVar17;
    u32 uVar18;
    u32 uVar19;
    u32 uVar20;
    u16* puVar21;

    uVar3 = *(u32*)(in + 4) & 0xffffff;
    iVar11 = 0x10;
    uVar12 = 0;
    uVar18 = 0;
    uVar19 = *(u32*)(*(int*)(in + 8) + in);
    iVar17 = *(int*)(in + 8) + 4;
    puVar21 = (u16*)&work[0x4ff8];
    uVar8 = 0x200;
    iVar16 = 0;
    uVar14 = *(u32*)(in + 0xc);
    uVar10 = 0x200;
    do {
        while (1) {
            if (uVar12 == 0x1f) {
                uVar13 = *(u32*)(in + iVar11);
                uVar12 = 0;
                iVar11 = iVar11 + 4;
            } else {
                uVar12 = uVar12 + 1;
                uVar13 = uVar14 << 1;
            }
            if (-1 < (int)uVar14) {
                break;
            }
            *puVar21 = uVar10 | 0x8000;
            puVar21[1] = uVar10 | 0x4000;
            puVar21 = puVar21 + 2;
            iVar16 = iVar16 + 2;
            uVar8 = uVar8 + 1;
            uVar14 = uVar13;
            uVar10 = uVar10 + 1;
        }
        iVar7 = uVar12 + 9;
        if (iVar7 < 0x21) {
            uVar4 = uVar13 >> 0x17;
            if (iVar7 == 0x20) {
                uVar14 = *(u32*)(in + iVar11);
                uVar12 = 0;
                iVar11 = iVar11 + 4;
            } else {
                uVar14 = uVar13 << 9;
                uVar12 = uVar12 + 9;
            }
        } else {
            puVar2 = (u32*)(in + iVar11);
            iVar11 = iVar11 + 4;
            uVar4 = uVar13 >> 0x17 | *puVar2 >> (0x40U - iVar7 & 0x3f);
            uVar12 = uVar12 - 0x17;
            uVar14 = *puVar2 << (uVar12 & 0x3f);
        }
        while (1) {
            puVar21 = puVar21 - 1;
            uVar10 = *puVar21;
            iVar16 = iVar16 - 1;
            iVar7 = (uVar10 & 0x3fff) * 2;
            if ((uVar10 & 0x8000) == 0) {
                break;
            }
            *(u16*)(&work[0x7fe] + iVar7) = (u16)uVar4;
            uVar4 = uVar10 & 0x3fff;
            if (iVar16 == 0) {
                uVar8 = 0x800;
                iVar16 = 0;
                uVar10 = 0x800;
                do {
                    while (1) {
                        if (uVar18 == 0x1f) {
                            uVar13 = *(u32*)(in + iVar17);
                            uVar18 = 0;
                            iVar17 = iVar17 + 4;
                        } else {
                            uVar18 = uVar18 + 1;
                            uVar13 = uVar19 << 1;
                        }
                        if (-1 < (int)uVar19) {
                            break;
                        }
                        *puVar21 = uVar10 | 0x8000;
                        puVar21[1] = uVar10 | 0x4000;
                        puVar21 = puVar21 + 2;
                        iVar16 = iVar16 + 2;
                        uVar8 = uVar8 + 1;
                        uVar19 = uVar13;
                        uVar10 = uVar10 + 1;
                    }
                    iVar7 = uVar18 + 0xb;
                    if (iVar7 < 0x21) {
                        uVar5 = uVar13 >> 0x15;
                        if (iVar7 == 0x20) {
                            uVar19 = *(u32*)(in + iVar17);
                            uVar18 = 0;
                            iVar17 = iVar17 + 4;
                        } else {
                            uVar19 = uVar13 << 0xb;
                            uVar18 = uVar18 + 0xb;
                        }
                    } else {
                        puVar2 = (u32*)(in + iVar17);
                        iVar17 = iVar17 + 4;
                        uVar5 = uVar13 >> 0x15 | *puVar2 >> (0x40U - iVar7 & 0x3f);
                        uVar18 = uVar18 - 0x15;
                        uVar19 = *puVar2 << (uVar18 & 0x3f);
                    }
                    while (1) {
                        puVar21 = puVar21 - 1;
                        uVar10 = *puVar21;
                        iVar16 = iVar16 - 1;
                        iVar7 = (uVar10 & 0x3fff) * 2;
                        if ((uVar10 & 0x8000) == 0) {
                            break;
                        }
                        *(u16*)(&work[0x2ffa] + iVar7) = (u16)uVar5;
                        uVar5 = uVar10 & 0x3fff;
                        uVar6 = uVar4;
                        uVar13 = uVar3;
                        if (iVar16 == 0) {
                            do {
                                while (0x1ff < uVar6) {
                                    if (uVar12 == 0x1f) {
                                        uVar15 = *(u32*)(in + iVar11);
                                        iVar11 = iVar11 + 4;
                                        uVar12 = 0;
                                    } else {
                                        uVar12 = uVar12 + 1;
                                        uVar15 = uVar14 << 1;
                                    }
                                    if ((int)uVar14 < 0) {
                                        uVar6 = *(u16*)(&work[0x7fe] + uVar6 * 2);
                                        uVar14 = uVar15;
                                    } else {
                                        uVar6 = *(u16*)((u8*)work + uVar6 * 2);
                                        uVar14 = uVar15;
                                    }
                                }
                                uVar15 = uVar5;
                                if (uVar6 < 0x100) {
                                    *out = (char)uVar6;
                                    out = out + 1;
                                    uVar13 = uVar13 - 1;
                                } else {
                                    while (0x7ff < uVar15) {
                                        if (uVar18 == 0x1f) {
                                            uVar20 = *(u32*)(in + iVar17);
                                            iVar17 = iVar17 + 4;
                                            uVar18 = 0;
                                        } else {
                                            uVar18 = uVar18 + 1;
                                            uVar20 = uVar19 << 1;
                                        }
                                        if ((int)uVar19 < 0) {
                                            uVar15 = *(u16*)(&work[0x2ffa] + uVar15 * 2);
                                            uVar19 = uVar20;
                                        } else {
                                            uVar15 = *(u16*)(&work[0xffc] + uVar15 * 2);
                                            uVar19 = uVar20;
                                        }
                                    }
                                    uVar6 = uVar6 - 0xfd;
                                    puVar9 = out - uVar15;
                                    uVar13 = uVar13 - uVar6;
                                    uVar15 = uVar6 >> 3;
                                    if (uVar15 == 0) {
                                        goto LAB_813325b8;
                                    }
                                    do {
                                        *out = puVar9[-1];
                                        out[1] = *puVar9;
                                        out[2] = puVar9[1];
                                        out[3] = puVar9[2];
                                        out[4] = puVar9[3];
                                        out[5] = puVar9[4];
                                        out[6] = puVar9[5];
                                        out[7] = puVar9[6];
                                        puVar9 = puVar9 + 8;
                                        out = out + 8;
                                        uVar15 = uVar15 - 1;
                                    } while (uVar15 != 0);
                                    for (uVar6 = uVar6 & 7; uVar6 != 0; uVar6 = uVar6 - 1) {
LAB_813325b8:
                                        puVar1 = puVar9 - 1;
                                        puVar9 = puVar9 + 1;
                                        *out = *puVar1;
                                        out = out + 1;
                                    }
                                }
                                uVar6 = uVar4;
                            } while (uVar13 != 0);
                            return uVar3;
                        }
                    }
                    *(u16*)(&work[0xffc] + iVar7) = (u16)uVar5;
                    uVar10 = uVar8;
                } while (1);
            }
        }
        *(u16*)((u8*)work + iVar7) = (u16)uVar4;
        uVar10 = uVar8;
    } while (1);
}
#endif

int Rvl_decode_asr(u8* out, u8* in) {
    return 0;
}
