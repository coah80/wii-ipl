#include <revolution/os.h>
#include <private/nand.h>
#include <revolution/nand.h>
#include <private/es.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char scCntCacheStrs[0xd0] = {
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
char scCntCacheTitleDataFmt[0x16] = {
    0x2f, 0x74, 0x69, 0x74, 0x6c, 0x65, 0x2f, 0x25, 0x30, 0x38, 0x78, 0x2f, 0x25, 0x30, 0x38, 0x78,
    0x2f, 0x64, 0x61, 0x74, 0x61, 0x00,
};
const char* __CNTCACHEVersion = scCntCacheStrs;
char scCntCacheSpaceNl[3] = {0x20, 0x0a, 0x00};

extern void _savegpr_23();
extern void _restgpr_23();

OSMutex _CNTCACHEMutex;
long long _CNTCACHEUnused816997A8;
int _CNTCACHEUnused816997A4;
BOOL _CNTCACHEInitialized;

void CNTCACHEClear();
BOOL _CNTCACHEIsTitleRemovable(ESTitleId titleId);
void _CNTCACHEDeleteTitle();
void _CNTCACHEDeleteContent();


void CNTCACHEInit(int cacheValue, int cacheHighWord) {
    if (!_CNTCACHEInitialized) {
        BOOL old;

        OSRegisterVersion(__CNTCACHEVersion);

        OSInitMutex(&_CNTCACHEMutex);
        ES_InitLib();

        old = OSDisableInterrupts();
        _CNTCACHEInitialized = TRUE;
        OSRestoreInterrupts(old);
    }
    CNTCACHEClear();

    _CNTCACHEUnused816997A4 = cacheValue;
    *((int*)&_CNTCACHEUnused816997A8) = cacheHighWord;
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
    lis r30, scCntCacheStrs@ha
    lis r3, _CNTCACHEMutex@ha
    addi r30, r30, scCntCacheStrs@l
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
    la r4, scCntCacheSpaceNl
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

void _CNTCACHEDeleteTitle() {
    char* token = strtok(NULL, scCntCacheSpaceNl);

    while (token != NULL) {
        ESTitleId titleId;
        int removable;

        errno = 0;
        titleId = strtoull(token, NULL, 16);
        if (errno == 0 && (u32)ES_TITLE_TYPE(titleId) != 1) {
            removable = _CNTCACHEIsTitleRemovable(titleId);
            if (removable == 1) {
                ES_DeleteTitle(titleId);
            } else if (removable == 0) {
                ES_DeleteTitleContent(titleId);
            }
        }
        token = strtok(NULL, scCntCacheSpaceNl);
    }
}

static s32 GetSaveDataUsage(ESTitleId titleId) {
    s32 ret = -1;
    char nandPath[64] ALIGN32;
    u32 usedBlocks = 1;
    u32 usedINodes = 1;

    snprintf(nandPath, (int)sizeof(nandPath), scCntCacheTitleDataFmt, NANDTitleIdHi(titleId), NANDTitleIdLo(titleId));
    ret = NANDSecretGetUsage(nandPath, &usedBlocks, &usedINodes);

    if (ret == NAND_RESULT_NOEXISTS) {
        ret = 2;
    } else if (ret >= NAND_RESULT_OK) {
        if (usedINodes == 1 && usedBlocks == 0) {
            ret = 1;
        } else {
            ret = 0;
        }
    }
    return ret;
}

BOOL _CNTCACHEIsTitleRemovable(ESTitleId titleId) {
    u8 tmdBuf[OSRoundUp32B(sizeof(ESTmdView))] ALIGN32;
    u32 tmdSize;
    ESTmdView* tmd;
    s32 ret;

    ret = GetSaveDataUsage(titleId);
    if (ret == 1) {
        tmd = (ESTmdView*)tmdBuf;
        ret = ES_GetTmdView(titleId, NULL, &tmdSize);
        if (ret != ES_ERR_OK) {
            return ret;
        }
        if (tmdSize > sizeof(tmdBuf)) {
            return ES_ERR_MEMORY_ERROR;
        }
        ret = ES_GetTmdView(titleId, tmd, &tmdSize);
        if (ret != ES_ERR_OK) {
            return ret;
        }

        if (((tmd->head.titleVersion >> 8) & 0xFF) == 0) {
            ret = 1;
        } else {
            ret = 0;
        }
    }

    return ret;
}

void _CNTCACHEDeleteContent() {
    u8 buf[OSRoundUp32B(sizeof(ESTmdView))] ALIGN32;
    u32 numOnCard;
    u32 size;
    ESTitleId titleId;
    ESTmdView* tmd;
    ESError result;
    char* token;

    token = strtok(NULL, scCntCacheSpaceNl);
    errno = 0;
    titleId = strtoull(token, NULL, 16);
    if (errno == 0 && NANDTitleIdHi(titleId) == 0x00010005) {
        tmd = (ESTmdView*)buf;
        result = ES_GetTmdView(titleId, NULL, &size);
        if (result == ES_ERR_DONT_EXISTS) {
            return;
        }
        if (result == ES_ERR_OK && ES_GetTmdView(titleId, tmd, &size) == ES_ERR_OK) {
            if ((tmd->head.titleType & 8) && (tmd->head.titleType & 0x10)) {
                token = strtok(NULL, scCntCacheSpaceNl);
                while (token) {
                    u32 index;
                    u32 i;

                    errno = 0;
                    index = strtoul(token, NULL, 10);
                    if (errno == 0 && index <= 510) {
                        for (i = 0; i < tmd->head.numContents; i++) {
                            if (index == tmd->contents[i].index) {
                                if (!(tmd->contents[i].type & 0x8000) &&
                                    ES_DeleteContent(titleId, tmd->contents[i].cid) == ES_ERR_OK &&
                                    ES_ListTitleContentsOnCard(titleId, NULL, &numOnCard) == ES_ERR_OK &&
                                    numOnCard == 0 && GetSaveDataUsage(titleId) == 1) {
                                    ES_DeleteTitle(titleId);
                                }
                                break;
                            }
                        }
                    }
                    token = strtok(NULL, scCntCacheSpaceNl);
                }
            }
            memset(buf, 0, OSRoundUp32B(size));
        }
    }
}
