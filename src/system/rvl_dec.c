#include "system/rvl_dec.h"

#define SZS_SIGNATURE 0x0059617A /* 'Yaz */
#define ASH_SIGNATURE 0x00415348 /* 'ASH' */
#define ASR_SIGNATURE 0x00415352 /* 'ASR' */

static u8 work[0x9008];

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
int Rvl_decode_ash(u8* out, u8* in) {
    return 0;
}
int Rvl_decode_asr(u8* out, u8* in) {
    return 0;
}
