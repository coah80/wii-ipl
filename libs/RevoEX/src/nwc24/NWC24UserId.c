#include <private/nwc24.h>
#include <revolution/nwc24.h>

static const u8 TtableInv[] = {13, 5, 9, 7, 0, 15, 10, 2, 12, 3, 14, 1, 8, 6, 11, 4};
extern void _savegpr_27(void);
extern void _restgpr_27(void);
extern void __shr2u(void);
extern void __shl2i(void);

static NWC24UserId getUnScrambleId(NWC24UserId id);
asm NWC24Err NWC24CheckUserId(register NWC24UserId id) {
    stwu r1,-0x30(r1)
    mfspr r0,LR
    stw r0,0x34(r1)
    addi r11,r1,0x30
    bl _savegpr_27
    or r28,r3,r3
    or r27,r4,r4
    addi r3,r1,0x8
    bl NWC24GetMyUserId
    lwz r3,0x8(r1)
    lwz r4,0xc(r1)
    xor r0,r3,r28
    xor r5,r4,r27
    or. r0,r5,r0
    bne NWC24CheckUserId_not_same
    li r3,-0x23
    b NWC24CheckUserId_return
NWC24CheckUserId_not_same:
    bl getUnScrambleId
    or r4,r27,r27
    rlwinm r27,r3,0x11,0x1d,0x1f
    or r3,r28,r28
    bl getUnScrambleId
    or r30,r4,r4
    or r31,r3,r3
    rlwinm r28,r3,0x11,0x1d,0x1f
    li r29,0
NWC24CheckUserId_crc_loop:
    addi r0,r29,1
    or r3,r31,r31
    or r4,r30,r30
    subfic r5,r0,0x35
    bl __shr2u
    rlwinm. r0,r4,0,0x1f,0x1f
    beq NWC24CheckUserId_crc_next
    subfic r5,r29,0x2a
    li r4,0x635
    li r3,0
    bl __shl2i
    xor r30,r30,r4
    xor r31,r31,r3
NWC24CheckUserId_crc_next:
    addi r29,r29,1
    cmpwi r29,0x2b
    blt NWC24CheckUserId_crc_loop
    or. r0,r30,r31
    beq NWC24CheckUserId_crc_ok
    li r3,-0x25
    b NWC24CheckUserId_return
NWC24CheckUserId_crc_ok:
    cmpwi r27,0
    bne NWC24CheckUserId_return_ok
    cmpwi r28,0
    beq NWC24CheckUserId_return_ok
    li r3,-0x7
    b NWC24CheckUserId_return
NWC24CheckUserId_return_ok:
    li r3,0
NWC24CheckUserId_return:
    addi r11,r1,0x30
    bl _restgpr_27
    lwz r0,0x34(r1)
    mtspr LR,r0
    addi r1,r1,0x30
    blr
}

NWC24Err NWC24iCheckUserIdCRC(NWC24UserId id) {
    u64 value = getUnScrambleId(id);
    int i;

    for (i = 0; i < 0x2B; i++) {
        if ((value >> (0x35 - (i + 1))) & 1) {
            value ^= (u64)0x635 << (0x2A - i);
        }
    }

    if (value != 0) {
        return NWC24_ERR_ID_CRC;
    }
    return NWC24_OK;
}

static asm NWC24UserId getUnScrambleId(register NWC24UserId id) {
    li r9,-1
    lis r7,0x20
    lis r6,0x5e5e
    stwu r1,-0x20(r1)
    subi r7,r7,1
    and r8,r4,r9
    addi r0,r6,0x5e5e
    stw r31,0x1c(r1)
    and r3,r3,r7
    lis r5,-1
    xor r8,r8,r0
    stw r30,0x18(r1)
    and r8,r8,r9
    xori r3,r3,0x5e5e
    rlwinm r0,r8,0x15,0xa,0xa
    li r6,-0x100
    and r3,r3,r7
    rlwinm r8,r8,0x1f,0,0x1f
    or r3,r3,r0
    stw r29,0x14(r1)
    rlwimi r8,r3,0x1f,0,0
    lis r4,-0xff
    rlwinm r7,r3,0x1f,1,0x1f
    addi r5,r5,0xff
    rlwinm r30,r8,0x18,0,0x1f
    rlwinm r29,r3,0x17,0x18,0x1f
    and r12,r7,r9
    li r0,0
    rlwimi r30,r3,0x17,0,7
    and r31,r8,r6
    rlwimi r31,r30,0,0x18,0x1f
    rlwinm r11,r3,0x1f,0x10,0x17
    and r30,r31,r5
    and r12,r12,r9
    rlwimi r0,r29,8,0x18,0x1f
    subi r4,r4,1
    or r12,r12,r0
    or r11,r30,r11
    and r30,r11,r4
    rlwinm r31,r8,0,0x18,0x1f
    li r0,0
    rlwinm r11,r8,0x10,8,0xf
    lis r10,0x100
    and r12,r12,r9
    rlwimi r0,r31,0x10,0x10,0x1f
    or r30,r30,r11
    or r29,r12,r0
    rlwinm r12,r3,0x1f,0x18,0x1f
    subi r0,r10,1
    li r10,0
    rlwimi r10,r12,0x18,8,0x1f
    and r11,r29,r9
    and r12,r30,r0
    rlwinm r3,r3,0x17,0,7
    or r3,r12,r3
    or r12,r11,r10
    and r10,r3,r9
    lis r3,TtableInv@ha
    and r31,r10,r9
    rlwinm r30,r8,0x10,0,0x1f
    rlwinm r11,r31,0x1c,0x1c,0x1f
    addi r3,r3,TtableInv@l
    rlwimi r30,r7,0x10,0,0xf
    rlwinm r10,r31,0,0x1c,0x1f
    and r29,r12,r6
    rlwinm r12,r8,8,0,0x1f
    lbzx r11,r3,r11
    rlwimi r12,r7,8,0,0x17
    lbzx r7,r3,r10
    rlwimi r29,r30,0,0x18,0x1f
    rlwinm r8,r11,4,0,0x1b
    rlwinm r10,r12,8,0x10,0x17
    and r11,r29,r5
    or r10,r11,r10
    or r7,r8,r7
    and r11,r31,r6
    li r8,0
    rlwimi r11,r7,0,0x18,0x1f
    and r12,r10,r9
    rlwinm r10,r11,0x18,0,0x1f
    li r7,0
    rlwimi r10,r12,0x18,0,7
    and r31,r11,r5
    rlwinm r11,r10,0x1c,0x1c,0x1f
    and r12,r12,r9
    rlwinm r10,r10,0,0x1c,0x1f
    lbzx r11,r3,r11
    lbzx r10,r3,r10
    rlwinm r11,r11,4,0,0x1b
    or r10,r11,r10
    rlwinm r11,r10,0,0x18,0x1f
    rlwinm r10,r10,8,0x10,0x17
    rlwimi r8,r11,8,0x18,0x1f
    or r10,r31,r10
    or r8,r12,r8
    rlwinm r12,r10,0x10,0,0x1f
    and r11,r10,r4
    rlwimi r12,r8,0x10,0,0xf
    and r10,r8,r9
    rlwinm r8,r12,0x1c,0x1c,0x1f
    rlwinm r4,r12,0,0x1c,0x1f
    lbzx r8,r3,r8
    lbzx r4,r3,r4
    rlwinm r8,r8,4,0,0x1b
    or r4,r8,r4
    rlwinm r8,r4,0,0x18,0x1f
    rlwinm r4,r4,0x10,8,0xf
    or r29,r11,r4
    rlwimi r7,r8,0x10,0x10,0x1f
    or r11,r10,r7
    lis r4,1
    rlwinm r8,r29,8,0,0x1f
    and r31,r29,r0
    rlwimi r8,r11,8,0,0x17
    and r12,r11,r9
    rlwinm r10,r8,0x1c,0x1c,0x1f
    subi r0,r4,0x4c4d
    lbzx r11,r3,r10
    rlwinm r8,r8,0,0x1c,0x1f
    lbzx r10,r3,r8
    li r8,0
    rlwinm r11,r11,4,0,0x1b
    lis r7,-0x4c4c
    or r11,r11,r10
    rlwinm r10,r11,0,0x18,0x1f
    subi r7,r7,0x4c4d
    rlwimi r8,r10,0x18,8,0x1f
    rlwinm r4,r11,0x18,0,7
    or r10,r12,r8
    rlwinm r8,r10,0x1c,0x1c,0x1f
    or r12,r31,r4
    rlwinm r4,r10,0,0x1c,0x1f
    lbzx r8,r3,r8
    and r11,r10,r6
    lbzx r4,r3,r4
    rlwinm r6,r8,4,0,0x1b
    and r8,r12,r9
    or r4,r6,r4
    rlwimi r11,r4,0,0x18,0x1f
    and r10,r8,r9
    rlwinm r6,r11,0x14,0x1c,0x1f
    rlwinm r4,r11,0x18,0x1c,0x1f
    lbzx r6,r3,r6
    lbzx r3,r3,r4
    and r8,r11,r5
    rlwinm r5,r6,4,0,0x1b
    and r4,r10,r9
    or r3,r5,r3
    rlwinm r3,r3,8,0x10,0x17
    or r3,r8,r3
    rlwinm r5,r3,0xa,0xb,0x15
    rlwinm r3,r3,0x15,0x16,0x1f
    rlwimi r5,r4,0xa,0x16,0x1f
    rlwimi r3,r4,0xa,0,0x15
    xor r4,r3,r7
    xor r3,r5,r0
    lwz r31,0x1c(r1)
    lwz r30,0x18(r1)
    lwz r29,0x14(r1)
    addi r1,r1,0x20
    blr
}
