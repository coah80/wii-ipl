#include <revolution/os.h>
#include <private/nand.h>
#include <revolution/nand.h>
#include <private/es.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char lbl_81693350[0xd0] = {
    0x3c, 0x3c, 0x20, 0x52, 0x56, 0x4c, 0x5f, 0x53, 0x44, 0x4b, 0x20, 0x2d, 0x20, 0x43, 0x4e, 0x54,
    0x43, 0x41, 0x43, 0x48, 0x45, 0x20, 0x09, 0x72, 0x65, 0x6c, 0x65, 0x61, 0x73, 0x65, 0x20, 0x62,
    0x75, 0x69, 0x6c, 0x64, 0x3a, 0x20, 0x41, 0x70, 0x72, 0x20, 0x32, 0x30, 0x20, 0x32, 0x30, 0x31,
    0x30, 0x20, 0x31, 0x34, 0x3a, 0x31, 0x35, 0x3a, 0x32, 0x38, 0x20, 0x28, 0x30, 0x78, 0x34, 0x31,
    0x39, 0x39, 0x5f, 0x36, 0x30, 0x38, 0x33, 0x31, 0x29, 0x20, 0x3e, 0x3e, 0x00, 0x00, 0x00, 0x00,
    0x2f, 0x73, 0x68, 0x61, 0x72, 0x65, 0x64, 0x32, 0x2f, 0x63, 0x6e, 0x74, 0x63, 0x61, 0x63, 0x68,
    0x65, 0x2e, 0x74, 0x78, 0x74, 0x00, 0x00, 0x00, 0x44, 0x65, 0x6c, 0x65, 0x74, 0x65, 0x54, 0x69,
    0x74, 0x6c, 0x65, 0x20, 0x00, 0x00, 0x00, 0x00, 0x25, 0x30, 0x31, 0x36, 0x6c, 0x6c, 0x78, 0x20,
    0x00, 0x00, 0x00, 0x00, 0x2f, 0x74, 0x6d, 0x70, 0x2f, 0x63, 0x6e, 0x74, 0x63, 0x61, 0x63, 0x68,
    0x65, 0x2e, 0x74, 0x78, 0x74, 0x00, 0x00, 0x00, 0x2f, 0x73, 0x68, 0x61, 0x72, 0x65, 0x64, 0x32,
    0x00, 0x00, 0x00, 0x00, 0x44, 0x65, 0x6c, 0x65, 0x74, 0x65, 0x43, 0x6f, 0x6e, 0x74, 0x65, 0x6e,
    0x74, 0x20, 0x00, 0x00, 0x44, 0x65, 0x6c, 0x65, 0x74, 0x65, 0x54, 0x69, 0x74, 0x6c, 0x65, 0x00,
    0x44, 0x65, 0x6c, 0x65, 0x74, 0x65, 0x43, 0x6f, 0x6e, 0x74, 0x65, 0x6e, 0x74, 0x00, 0x00, 0x00
};
char lbl_81693420[0x16] = {
    0x2f, 0x74, 0x69, 0x74, 0x6c, 0x65, 0x2f, 0x25, 0x30, 0x38, 0x78, 0x2f, 0x25, 0x30, 0x38, 0x78,
    0x2f, 0x64, 0x61, 0x74, 0x61, 0x00,
};
const char* __CNTCACHEVersion = lbl_81693350;
char lbl_816985DC[3] = {0x20, 0x0a, 0x00};

extern void _savegpr_23();
extern void _restgpr_23();
extern void _savegpr_26();
extern void _restgpr_26();

OSMutex _CNTCACHEMutex;
long long _CNTCACHEUnused816997A8;
int _CNTCACHEUnused816997A4;
BOOL _CNTCACHEInitialized;

void CNTCACHEClear();
BOOL _CNTCACHEIsTitleRemovable(ESTitleId titleId);
void _CNTCACHEDeleteTitle();
void _CNTCACHEDeleteContent();


void CNTCACHEInit(int unk0, int unk1) {
    if (_CNTCACHEInitialized == FALSE) {
        BOOL old;

        OSRegisterVersion(__CNTCACHEVersion);

        OSInitMutex(&_CNTCACHEMutex);
        ES_InitLib();

        old = OSDisableInterrupts();
        _CNTCACHEInitialized = TRUE;
        OSRestoreInterrupts(old);
    }
    CNTCACHEClear();

    _CNTCACHEUnused816997A4 = unk0;
    *((int*)&_CNTCACHEUnused816997A8) = unk1;
}
asm void CNTCACHEClear() {
    clrlwi r11, r1, 0x1b
    mr r12, r1
    subfic r11, r11, -0x500
    stwux r1, r1, r11
    mflr r0
    mr r11, r12
    stw r0, 4(r12)
    bl _savegpr_23
    lis r30, lbl_81693350@ha
    lis r3, _CNTCACHEMutex@ha
    addi r30, r30, lbl_81693350@l
    li r29, 0
    addi r3, r3, _CNTCACHEMutex@l
    bl OSLockMutex
    addi r3, r30, 0x50
    addi r4, r1, 0x24
    li r27, 1
    li r5, 3
    bl NANDPrivateOpen
    cmpwi r3, -0xc
    mr r28, r3
    bne L_d4
    li r28, 0
    b L_28c
L_d4:
    cmpwi r3, 0
    beq L_e0
    b L_268
L_e0:
    addi r3, r1, 0x24
    addi r4, r1, 0x20
    bl NANDGetLength
    cmpwi r3, 0
    mr r28, r3
    beq L_fc
    b L_268
L_fc:
    li r26, 0
    li r31, 0
    b L_25c
L_108:
    lwz r25, 0x20(r1)
    cmplwi r25, 0x400
    ble L_118
    li r25, 0x400
L_118:
    addi r24, r1, 0xc0
    addi r0, r25, 0x1f
    addi r3, r1, 0x24
    mr r4, r24
    rlwinm r5, r0, 0, 0, 0x1a
    bl NANDRead
    cmpw r3, r25
    beq L_140
    li r28, -0x14b3
    b L_268
L_140:
    mr r4, r24
    li r28, 0
    mtctr r25
    cmplwi r25, 0
    ble L_16c
L_154:
    lbz r0, 0(r4)
    cmpwi r0, 0xa
    bne L_164
    b L_170
L_164:
    addi r4, r4, 1
    bdnz L_154
L_16c:
    li r4, 0
L_170:
    cmpwi r4, 0
    bne L_224
    li r28, 0
    b L_268
    b L_224
L_184:
    stb r31, 0(r4)
    subf r23, r24, r4
    mr r3, r24
    la r4, lbl_816985DC
    bl strtok
    cmpwi r3, 0
    mr r29, r3
    beq L_1d4
    addi r4, r30, 0xb4
    bl strcmp
    cmpwi r3, 0
    bne L_1bc
    bl _CNTCACHEDeleteTitle
    b L_1d4
L_1bc:
    mr r3, r29
    addi r4, r30, 0xc0
    bl strcmp
    cmpwi r3, 0
    bne L_1d4
    bl _CNTCACHEDeleteContent
L_1d4:
    lwz r0, 0x20(r1)
    addi r23, r23, 1
    add r24, r24, r23
    subf r0, r23, r0
    subf r25, r23, r25
    mr r4, r24
    stw r0, 0x20(r1)
    add r26, r26, r23
    mtctr r25
    cmplwi r25, 0
    ble L_218
L_200:
    lbz r0, 0(r4)
    cmpwi r0, 0xa
    bne L_210
    b L_21c
L_210:
    addi r4, r4, 1
    bdnz L_200
L_218:
    li r4, 0
L_21c:
    cmpwi r4, 0
    beq L_22c
L_224:
    cmpwi r25, 0
    bgt L_184
L_22c:
    lwz r0, 0x20(r1)
    cmpwi r0, 0
    beq L_25c
    mr r4, r26
    addi r3, r1, 0x24
    li r5, 0
    bl NANDSeek
    cmplw r3, r26
    beq L_258
    li r28, -0x14b3
    b L_268
L_258:
    li r28, 0
L_25c:
    lwz r0, 0x20(r1)
    cmpwi r0, 0
    bne L_108
L_268:
    addi r3, r1, 0x24
    bl NANDClose
    addi r3, r30, 0x50
    li r29, 0
    bl NANDPrivateDelete
    cmpwi r3, 0
    addi r3, r30, 0x84
    bl NANDPrivateDelete
    cmpwi r3, 0
L_28c:
    cmpwi r29, 0
    beq L_29c
    addi r3, r1, 0x24
    bl NANDClose
L_29c:
    cmpwi r27, 0
    beq L_2b0
    lis r3, _CNTCACHEMutex@ha
    addi r3, r3, _CNTCACHEMutex@l
    bl OSUnlockMutex
L_2b0:
    mr r3, r28
    lwz r10, 0(r1)
    mr r11, r10
    bl _restgpr_23
    lwz r0, 4(r10)
    mtlr r0
    mr r1, r10
    blr
}

asm void _CNTCACHEDeleteTitle() {
    stwu r1, -0x20(r1)
    mflr r0
    li r3, 0
    la r4, lbl_816985DC
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    stw r28, 0x10(r1)
    bl strtok
    li r30, 0
    li r31, -1
    b L_370
L_304:
    stw r30, errno(r0)
    li r4, 0
    li r5, 0x10
    bl strtoull
    lwz r0, errno(r0)
    mr r28, r4
    mr r29, r3
    cmpwi r0, 0
    bne L_364
    and r0, r3, r31
    cmplwi r0, 1
    beq L_364
    bl _CNTCACHEIsTitleRemovable
    cmpwi r3, 1
    bne L_350
    mr r4, r28
    mr r3, r29
    bl ES_DeleteTitle
    b L_364
L_350:
    cmpwi r3, 0
    bne L_364
    mr r4, r28
    mr r3, r29
    bl ES_DeleteTitleContent
L_364:
    li r3, 0
    la r4, lbl_816985DC
    bl strtok
L_370:
    cmpwi r3, 0
    bne L_304
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

asm int _CNTCACHEIsTitleRemovable(ESTitleId titleId) {
    clrlwi r11, r1, 0x1b
    mr r12, r1
    subfic r11, r11, -0x2100
    stwux r1, r1, r11
    mflr r0
    lis r5, lbl_81693420@ha
    stw r0, 4(r12)
    li r0, 1
    addi r5, r5, lbl_81693420@l
    stw r31, -4(r12)
    stw r30, -8(r12)
    mr r30, r3
    addi r3, r1, 0x40
    stw r29, -0xc(r12)
    mr r29, r4
    li r4, -1
    stw r0, 0x20(r1)
    and r6, r30, r4
    and r7, r29, r4
    li r4, 0x40
    stw r0, 0x24(r1)
    crclr 4*cr1+eq
    bl snprintf
    addi r3, r1, 0x40
    addi r4, r1, 0x20
    addi r5, r1, 0x24
    bl NANDSecretGetUsage
    cmpwi r3, -0xc
    mr r4, r3
    bne L_418
    li r4, 2
    b L_444
L_418:
    cmpwi r3, 0
    blt L_444
    lwz r0, 0x24(r1)
    cmplwi r0, 1
    bne L_440
    lwz r0, 0x20(r1)
    cmpwi r0, 0
    bne L_440
    li r4, 1
    b L_444
L_440:
    li r4, 0
L_444:
    cmpwi r4, 1
    bne L_4bc
    mr r4, r29
    mr r3, r30
    addi r31, r1, 0x80
    addi r6, r1, 0x28
    li r5, 0
    bl ES_GetTmdView
    cmpwi r3, 0
    beq L_470
    b L_4c0
L_470:
    lwz r0, 0x28(r1)
    cmplwi r0, 0x2060
    ble L_484
    li r3, -0x400
    b L_4c0
L_484:
    mr r4, r29
    mr r3, r30
    mr r5, r31
    addi r6, r1, 0x28
    bl ES_GetTmdView
    cmpwi r3, 0
    beq L_4a4
    b L_4c0
L_4a4:
    lhz r0, 0xd8(r1)
    rlwinm. r0, r0, 0x18, 0x18, 0x1f
    bne L_4b8
    li r4, 1
    b L_4bc
L_4b8:
    li r4, 0
L_4bc:
    mr r3, r4
L_4c0:
    lwz r10, 0(r1)
    lwz r0, 4(r10)
    lwz r31, -4(r10)
    lwz r30, -8(r10)
    lwz r29, -0xc(r10)
    mtlr r0
    mr r1, r10
    blr
}

asm void _CNTCACHEDeleteContent() {
    clrlwi r11, r1, 0x1b
    mr r12, r1
    subfic r11, r11, -0x2100
    stwux r1, r1, r11
    mflr r0
    mr r11, r12
    stw r0, 4(r12)
    bl _savegpr_26
    li r3, 0
    la r4, lbl_816985DC
    bl strtok
    li r31, 0
    li r4, 0
    stw r31, errno(r0)
    li r5, 0x10
    bl strtoull
    lwz r0, errno(r0)
    mr r29, r4
    mr r30, r3
    cmpwi r0, 0
    bne L_708
    li r0, -1
    and r5, r3, r0
    addis r0, r5, -1
    cmplwi r0, 5
    bne L_708
    addi r28, r1, 0x80
    addi r6, r1, 0x28
    li r5, 0
    bl ES_GetTmdView
    cmpwi r3, -0x6a
    beq L_708
    cmpwi r3, 0
    bne L_708
    mr r4, r29
    mr r3, r30
    mr r5, r28
    addi r6, r1, 0x28
    bl ES_GetTmdView
    cmpwi r3, 0
    bne L_708
    lwz r3, 0x94(r1)
    rlwinm. r0, r3, 0, 0x1c, 0x1c
    beq L_6f0
    rlwinm. r0, r3, 0, 0x1b, 0x1b
    beq L_6f0
    li r3, 0
    la r4, lbl_816985DC
    bl strtok
    li r26, 1
    lis r27, lbl_81693420@ha
    b L_6e8
L_5b0:
    stw r31, errno(r0)
    li r4, 0
    li r5, 0xa
    bl strtoul
    lwz r0, errno(r0)
    cmpwi r0, 0
    bne L_6dc
    cmplwi r3, 0x1fe
    bgt L_6dc
    lhz r0, 0xda(r1)
    li r4, 0
    mtctr r0
    cmplwi r0, 0
    ble L_6dc
L_5e8:
    add r5, r28, r4
    lhz r0, 0x60(r5)
    cmplw r3, r0
    bne L_6d4
    lhz r0, 0x62(r5)
    rlwinm. r0, r0, 0, 0x10, 0x10
    bne L_6dc
    lwz r5, 0x5c(r5)
    mr r4, r29
    mr r3, r30
    bl ES_DeleteContent
    cmpwi r3, 0
    bne L_6dc
    mr r4, r29
    mr r3, r30
    addi r6, r1, 0x2c
    li r5, 0
    bl ES_ListTitleContentsOnCard
    cmpwi r3, 0
    bne L_6dc
    lwz r0, 0x2c(r1)
    cmpwi r0, 0
    bne L_6dc
    li r0, -1
    stw r26, 0x20(r1)
    addi r3, r1, 0x40
    addi r5, r27, lbl_81693420@l
    stw r26, 0x24(r1)
    and r6, r30, r0
    and r7, r29, r0
    li r4, 0x40
    crclr 4*cr1+eq
    bl snprintf
    addi r3, r1, 0x40
    addi r4, r1, 0x20
    addi r5, r1, 0x24
    bl NANDSecretGetUsage
    cmpwi r3, -0xc
    mr r0, r3
    bne L_690
    li r0, 2
    b L_6bc
L_690:
    cmpwi r3, 0
    blt L_6bc
    lwz r0, 0x24(r1)
    cmplwi r0, 1
    bne L_6b8
    lwz r0, 0x20(r1)
    cmpwi r0, 0
    bne L_6b8
    li r0, 1
    b L_6bc
L_6b8:
    li r0, 0
L_6bc:
    cmpwi r0, 1
    bne L_6dc
    mr r4, r29
    mr r3, r30
    bl ES_DeleteTitle
    b L_6dc
L_6d4:
    addi r4, r4, 0x10
    bdnz L_5e8
L_6dc:
    li r3, 0
    la r4, lbl_816985DC
    bl strtok
L_6e8:
    cmpwi r3, 0
    bne L_5b0
L_6f0:
    lwz r5, 0x28(r1)
    addi r3, r1, 0x80
    li r4, 0
    addi r0, r5, 0x1f
    rlwinm r5, r0, 0, 0, 0x1a
    bl memset
L_708:
    lwz r10, 0(r1)
    mr r11, r10
    bl _restgpr_26
    lwz r0, 4(r10)
    mtlr r0
    mr r1, r10
    blr
}
