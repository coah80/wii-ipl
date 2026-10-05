#include <private/card.h>
#include <revolution/card.h>

#include <string.h>

static void WriteCallback(s32 chan, s32 result);
static void EraseCallback(s32 chan, s32 result);

CARDDir* __CARDGetDirBlock(CARDControl* card) {
    return card->currentDir;
}

static void WriteCallback(s32 chan, s32 result) {
    CARDControl* card = &__CARDBlock[chan];
    CARDCallback callback;

    if (result >= CARD_RESULT_READY) {
        CARDDir* dir0 = (CARDDir*)((u8*)card->workArea + CARD_SYSTEM_BLOCK_SIZE);
        CARDDir* dir1 = (CARDDir*)((u8*)card->workArea + 0x4000);

        if (card->currentDir == dir0) {
            card->currentDir = dir1;
            memcpy(dir1, dir0, CARD_SYSTEM_BLOCK_SIZE);
        } else {
            card->currentDir = dir0;
            memcpy(dir0, dir1, CARD_SYSTEM_BLOCK_SIZE);
        }
    }

    if (!card->apiCallback) {
        __CARDPutControlBlock(card, result);
    }

    callback = card->eraseCallback;
    if (callback) {
        card->eraseCallback = NULL;
        callback(chan, result);
    }
}

static void EraseCallback(s32 chan, s32 result) {
    CARDControl* card = &__CARDBlock[chan];
    CARDCallback callback;
    CARDDir* dir;
    u32 addr;

    if (result >= CARD_RESULT_READY) {
        dir = __CARDGetDirBlock(card);
        addr = ((u32)dir - (u32)card->workArea) / CARD_SYSTEM_BLOCK_SIZE * card->sectorSize;
        result = __CARDWrite(chan, addr, CARD_SYSTEM_BLOCK_SIZE, dir, WriteCallback);
        if (result >= CARD_RESULT_READY) {
            return;
        }
    }

    if (!card->apiCallback) {
        __CARDPutControlBlock(card, result);
    }

    callback = card->eraseCallback;
    if (callback) {
        card->eraseCallback = NULL;
        callback(chan, result);
    }
}

s32 __CARDUpdateDir(s32 chan, CARDCallback callback) {
    CARDControl* card;
    CARDDirCheck* check;
    u32 addr;
    CARDDir* dir;

    card = &__CARDBlock[chan];
    if (!card->attached) {
        return CARD_RESULT_NOCARD;
    }

    dir = __CARDGetDirBlock(card);
    check = CARDGetDirCheck(dir);
    ++check->checkCode;
    __CARDCheckSum(dir, CARD_SYSTEM_BLOCK_SIZE - sizeof(u32), &check->checkSum, &check->checkSumInv);
    DCStoreRange(dir, CARD_SYSTEM_BLOCK_SIZE);

    card->eraseCallback = callback;
    addr = ((u32)dir - (u32)card->workArea) / CARD_SYSTEM_BLOCK_SIZE * card->sectorSize;
    return __CARDEraseSector(chan, addr, EraseCallback);
}
