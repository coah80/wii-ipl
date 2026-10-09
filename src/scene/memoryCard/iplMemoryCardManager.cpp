#define IPL_MEMORY_CARD_MANAGER_CPP
#include "scene/memoryCard/iplMemoryCardManager.h"
#include "utility/iplCharacterCode.h"
#include <revolution/sc.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

struct MemoryCardSortEntry {
    u32 fileNo;
    u32 flags;
    s64 key;
};

extern "C" int compareMemoryCardSortEntries(const void* first, const void* second) {
    const MemoryCardSortEntry* a = static_cast<const MemoryCardSortEntry*>(first);
    const MemoryCardSortEntry* b = static_cast<const MemoryCardSortEntry*>(second);
    s64 bKey = b->key;
    s64 aKey = a->key;
    if (bKey < aKey) {
        return 1;
    }
    if (aKey < bKey) {
        return -1;
    }
    u32 bIndex = b->fileNo;
    u32 aIndex = a->fileNo;
    if (aIndex > bIndex) {
        return 1;
    }
    return -(int)(aIndex < bIndex);
}

namespace ipl {
namespace scene {

typedef memorycard::FileInfo CardDirectory[CARD_MAX_FILE];
typedef memorycard::IconState CardIcons[CARD_MAX_FILE];

void MemoryCardManager::calc() {
    memorycard::probeCard();
    update_change_cardstate(0);
    update_change_cardstate(1);
    update_icon_anm();
}

bool MemoryCardManager::isSlotReady(u8 slot) {
    memorycard::CardState* states = memorycard::getCardSlotState();
    return states[slot].state == 4;
}

bool MemoryCardManager::isSlotNoCard(u8 slot) {
    memorycard::CardState* states = memorycard::getCardSlotState();
    return states[slot].state == 0;
}

long MemoryCardManager::isSlotWrongDevice(u8 slot) {
    memorycard::CardState* states = memorycard::getCardSlotState();
    int result = 1;
    memorycard::CardState* state = &states[slot];
    bool isWrong = true;
    bool isUnsupported = true;
    bool isUnformatted = true;
    bool isInvalid = true;
    if (state->state != 5 && state->state != 6) {
        isInvalid = false;
    }
    if (!isInvalid && state->state != 7) {
        isUnformatted = false;
    }
    if (!isUnformatted && state->state != 8) {
        isUnsupported = false;
    }
    if (!isUnsupported && state->state != 9) {
        isWrong = false;
    }
    if (!isWrong && state->state != 10) {
        result = 0;
    }
    return result;
}

void MemoryCardManager::sort_file_array(u8 slot) {
    CardDirectory* dirs = reinterpret_cast<CardDirectory*>(memorycard::getCardDirState());
    for (long file = 0; file < CARD_MAX_FILE; file++) {
        if (dirs[slot][file].fileNo != 0) {
            mFile[slot][file].fileNo = file;
            mFile[slot][file].sortKey = dirs[slot][file].key;
            mFile[slot][file].sortKeyHigh = 0;
        } else {
            mFile[slot][file].fileNo = file;
            mFile[slot][file].sortKey = -1 - file;
            mFile[slot][file].sortKeyHigh = 0;
        }
    }
    qsort(mFile[slot], CARD_MAX_FILE, sizeof(MCFile), compareMemoryCardSortEntries);
}

void MemoryCardManager::sendCardCmdMove(u8 slot, s16 index) {
    u32 file = mFile[slot][index].fileNo;
    mLastCmd = 2;
    if (isDistSlot(slot, NULL)) {
        memorycard::sendCardMoveCmd(slot, file);
        mLastResult = -0x15;
        mLastCmd = 3;
    } else {
        mLastResult = -0x17;
    }
}

void MemoryCardManager::sendCardCmdCopy(u8 slot, s16 index) {
    u32 file = mFile[slot][index].fileNo;
    if (isDistSlot(slot, NULL)) {
        memorycard::sendCardCopyCmd(slot, file);
        mLastResult = -0x15;
        mLastCmd = 2;
    } else {
        mLastResult = -0x17;
    }
}

void MemoryCardManager::sendCardCmdDelete(u8 slot, s16 index) {
    memorycard::sendCardDeleteCmd(slot, mFile[slot][index].fileNo);
    mLastResult = -0x15;
    mLastCmd = 4;
}

void MemoryCardManager::sendCardCmdFormat(u8 slot) {
    memorycard::sendCardFormatCmd(slot);
    mLastResult = -0x15;
    mLastCmd = 1;
}

bool MemoryCardManager::isDistSlot(u8 slot, long* state) {
    u32 other = slot ^ 1;
    memorycard::CardState* states = memorycard::getCardSlotState();
    if (state != NULL) {
        *state = states[other].state;
    }
    if (states[other].state == 4) {
        return true;
    }
    return false;
}

bool MemoryCardManager::isMoveEnable(u8 slot, u32 index, long* code) {
    CardDirectory* dirs = reinterpret_cast<CardDirectory*>(memorycard::getCardDirState());
    memorycard::CardState* states = memorycard::getCardSlotState();
    u32 file = mFile[slot][index].fileNo;
    long result = file;
    bool enabled = false;
    if (isDistSlot(slot, NULL) &&
        dirs[slot][file].canMove != 0 &&
        states[slot].key == states[slot ^ 1].key &&
        states[slot ^ 1].freeBlocks >= dirs[slot][file].size && states[slot ^ 1].freeFiles != 0 &&
        dirs[slot][file].transferBlocked == 0) {
        result = -0x15;
        enabled = true;
    } else {
        long destinationState;
        if (!isDistSlot(slot, &destinationState)) {
            if (destinationState == 0) {
                result = -0x17;
            } else if (destinationState == 5 || destinationState == 7 || destinationState == 9) {
                result = -0x16;
            } else {
                result = -0x1c;
            }
        } else if (dirs[slot][file].canMove == 0) {
            result = -0x1a;
        } else if (states[slot].key != states[slot ^ 1].key) {
            result = -0x1b;
        } else if (states[slot ^ 1].freeBlocks < dirs[slot][file].size || states[slot ^ 1].freeFiles == 0) {
            result = -0x19;
        } else if (dirs[slot][file].transferBlocked != 0) {
            result = -0x18;
        }
    }
    if (code != NULL) {
        *code = result;
    }
    return enabled;
}

bool MemoryCardManager::isCopyEnable(u8 slot, u32 index, long* code) {
    CardDirectory* dirs = reinterpret_cast<CardDirectory*>(memorycard::getCardDirState());
    memorycard::CardState* states = memorycard::getCardSlotState();
    u32 file = mFile[slot][index].fileNo;
    long result = file;
    bool enabled = false;
    if (isDistSlot(slot, NULL) &&
        dirs[slot][file].canCopy != 0 &&
        states[slot].key == states[slot ^ 1].key &&
        states[slot ^ 1].freeBlocks >= dirs[slot][file].size && states[slot ^ 1].freeFiles != 0 &&
        dirs[slot][file].transferBlocked == 0) {
        result = -0x15;
        enabled = true;
    } else {
        long destinationState;
        if (!isDistSlot(slot, &destinationState)) {
            if (destinationState == 0) {
                result = -0x17;
            } else if (destinationState == 5 || destinationState == 7 || destinationState == 9) {
                result = -0x16;
            } else {
                result = -0x1c;
            }
        } else if (dirs[slot][file].canCopy == 0) {
            result = -0x1a;
        } else if (states[slot].key != states[slot ^ 1].key) {
            result = -0x1b;
        } else if (states[slot ^ 1].freeBlocks < dirs[slot][file].size || states[slot ^ 1].freeFiles == 0) {
            result = -0x19;
        } else if (dirs[slot][file].transferBlocked != 0) {
            result = -0x18;
        }
    }
    if (code != NULL) {
        *code = result;
    }
    return enabled;
}

bool MemoryCardManager::isIconValidate(u8 slot, s16 index) {
    u32 cardSlot = slot;
    if (cardSlot > 1 || index < 0 || index >= CARD_MAX_FILE) {
        return false;
    }
    CardDirectory* dirs = reinterpret_cast<CardDirectory*>(memorycard::getCardDirState());
    if (mFile[cardSlot][index].fileNo >= CARD_MAX_FILE) {
        return false;
    }
    return dirs[cardSlot][mFile[cardSlot][index].fileNo].fileNo != 0;
}

bool MemoryCardManager::isBannerEnable(u8 slot, s16 index) {
    CardIcons* icons = reinterpret_cast<CardIcons*>(memorycard::getIconStateArray());
    return icons[slot][mFile[slot][index].fileNo].bannerEnable != 0;
}

void MemoryCardManager::update_icon_anm() {
    CardIcons* icons = reinterpret_cast<CardIcons*>(memorycard::getIconStateArray());
    CardDirectory* dirs = reinterpret_cast<CardDirectory*>(memorycard::getCardDirState());
    int slot = 0;
    do {
        int index = 0;
        for (int remaining = CARD_MAX_FILE; remaining > 0; remaining--, index++) {
            u32 file = mFile[slot][index].fileNo;
            if (file < CARD_MAX_FILE && dirs[slot][file].fileNo != 0) {
                memorycard::IconState* icon = icons[slot] + file;
                s8 delta = icon->anmDelta;
                s16 currentFrame = mFileCell[slot][file].iconAnmCounter;
                s32 frame = currentFrame + delta;
                mFileCell[slot][file].iconAnmCounter = frame;
                if ((s16)frame >= icons[slot][file].anmMax) {
                    if (icon->anmType == 4) {
                        mFileCell[slot][file].iconAnmCounter = icons[slot][file].anmMax - icon->anmLastFrameDuration - 1;
                        icon->anmDelta = -1;
                    } else {
                        mFileCell[slot][file].iconAnmCounter = 0;
                        icon->anmDelta = 1;
                    }
                }
                if (mFileCell[slot][file].iconAnmCounter < 0) {
                    if (icon->anmType == 4) {
                        mFileCell[slot][file].iconAnmCounter = icon->anmFirstFrameDuration;
                    } else {
                        mFileCell[slot][file].iconAnmCounter = 0;
                    }
                    icon->anmDelta = 1;
                }
            }
        }
        slot++;
    } while (slot < 2);
}

void MemoryCardManager::update_file_array(u8 slot) {
    memorycard::CardState* states = memorycard::getCardSlotState();
    states[slot].changed = 0;
    sort_file_array(slot);
    enum CardCommand {
        NoCommand, Format, Copy, Move, Delete,
        CopyComplete, MoveComplete, DeleteComplete, FormatComplete
    };
    CardCommand command = static_cast<CardCommand>(mLastCmd);
    if ((u32)(command - 1) <= 3) {
        if (mLastResult == -0x15) {
            mLastResult = memorycard::getCardLastCMDFCmdResult();
        }
        if (mLastResult == 0) {
            switch (mLastCmd) {
            case Move:
                mpEventHandler->onMemEvent(2, slot);
                mLastCmd = MoveComplete;
                break;
            case Copy:
                mpEventHandler->onMemEvent(1, slot);
                mLastCmd = CopyComplete;
                break;
            case Delete:
                mpEventHandler->onMemEvent(3, slot);
                mLastCmd = DeleteComplete;
                break;
            case Format:
                mpEventHandler->onMemEvent(4, slot);
                mLastCmd = FormatComplete;
                break;
            }
        }
    }
}

void MemCardEventHandler::onMemEvent(long event, u8 slot) {
}

void MemoryCardManager::update_change_cardstate(u8 slot) {
    memorycard::CardState* states = memorycard::getCardSlotState();
    if (states[slot].changed == 1) {
        if (states[slot].state == 4) {
            update_file_array(slot);
        } else if (states[slot].state == 8 || states[slot].state == 6) {
            mpEventHandler->onMemEvent(0, slot);
            states[slot].changed = 0;
        }
        if (mLastResult == 0 && memorycard::getCardLastSendCmd() == 9 &&
            slot == memorycard::getCardLastSrcSlot()) {
            mpEventHandler->onMemEvent(5, slot);
            states[slot].changed = 0;
            for (int file = 0; file < CARD_MAX_FILE; file++) {
                mFile[slot][file].fileNo = -1;
                mFile[slot][file].sortKey = -1;
                mFile[slot][file].sortKeyHigh = 0;
                mFileCell[slot][file].iconAnmCounter = 0;
                wmemset(mFileCell[slot][file].comment[0], 0, 0x40);
            }
        }
    }
    if (states[slot].state != 4 && states[slot].state != 6 && states[slot].state != 8) {
        mpEventHandler->onMemEvent(6, slot);
    }
}

const GXTexObj* MemoryCardManager::create_icon(u8 slot, s16 index) {
    memorycard::IconState (*icons)[CARD_MAX_FILE] = reinterpret_cast<memorycard::IconState(*)[CARD_MAX_FILE]>(memorycard::getIconStateArray());
    int total = 0;
    s16 frame = 0;
    u32 file = mFile[slot][index].fileNo;
    do {
        total += ((icons[slot][file].anmFrameBits >> (frame++ << 1)) & 3) * 4;
        if (mFileCell[slot][file].iconAnmCounter <= total) {
            break;
        }
    } while (frame <= 8);
    return _create_icon(slot, file, frame - 1);
}

const GXTexObj* MemoryCardManager::create_icon(u8 slot, s16 index, long start) {
    memorycard::getIconStateArray();
    u32 file = mFile[slot][index].fileNo;
    return _create_icon(slot, file, 0);
}

const GXTexObj* MemoryCardManager::_create_icon(u8 slot, s16 file, long start) {
    CardDirectory* dirs = reinterpret_cast<CardDirectory*>(memorycard::getCardDirState());
    if (dirs[slot][file].fileNo == 0) {
        return NULL;
    }
    CardIcons* icons = reinterpret_cast<CardIcons*>(memorycard::getIconStateArray());
    if ((int)icons[slot][file].iconFmt[start] == GX_TF_RGB5A3) {
        GXLoadTexObj(initIconTexture(slot, file, reinterpret_cast<u8*>(&icons[slot][file]) + icons[slot][file].iconOffset[start]), GX_TEXMAP0);
    } else if ((int)icons[slot][file].iconFmt[start] == GX_TF_C8) {
        initIconTextureCI(slot, file, reinterpret_cast<u8*>(&icons[slot][file]) + icons[slot][file].iconOffset[start]);
        GXTlutObj* tlut = initIconPalette(slot, file, reinterpret_cast<u8*>(&icons[slot][file]) + icons[slot][file].iconTlutOffset);
        GXLoadTlut(tlut, GX_TLUT0);
        GXLoadTexObj(&mFileCell[slot][file].icon, GX_TEXMAP0);
    } else {
        return NULL;
    }
    return &mFileCell[slot][file].icon;
}

static inline const u8* trimCardComment(char* comment) {
    const u8* encoded = reinterpret_cast<const u8*>(comment);
    for (int position = 0x1f;
         comment[position] == ' ' || comment[position] == '\n' || comment[position] == 0;) {
        comment[position--] = 0;
    }
    return encoded;
}

const wchar_t* MemoryCardManager::getComment(u8 slot, s16 index, int which) {
    u32 file = mFile[slot][index].fileNo;
    wmemset(mFileCell[slot][file].comment[which], 0, 0x40);
    char comment[33] = {0};
    const char* comments = memorycard::getIconComment(slot, file);
    memcpy(comment, comments + which * 0x20, 0x20);
    const u8* encoded = trimCardComment(comment);
    if (SCGetLanguage() == SC_LANG_JAPANESE) {
        utility::CharacterCode::shiftJISToUTF16(mFileCell[slot][file].comment[which], encoded, 0x20);
        for (int pos = 0x1f;
             mFileCell[slot][file].comment[which][pos] == 0x20 ||
             mFileCell[slot][file].comment[which][pos] == 0x3000 ||
             mFileCell[slot][file].comment[which][pos] == 10 ||
             mFileCell[slot][file].comment[which][pos] == 0;) {
            mFileCell[slot][file].comment[which][pos--] = 0;
        }
    } else {
        utility::CharacterCode::ANSIToUTF16(mFileCell[slot][file].comment[which], encoded, 0x20);
    }
    bool found = false;
    int count = 0;
    while (mFileCell[slot][file].comment[which][count] != 0 && count < 0x20) {
        if (found) {
            mFileCell[slot][file].comment[which][count] = 0;
        } else if (mFileCell[slot][file].comment[which][count] == 10 || mFileCell[slot][file].comment[which][count] == 0xd0a) {
            mFileCell[slot][file].comment[which][count] = 0;
            found = true;
        }
        count++;
    }
    return mFileCell[slot][file].comment[which];
}

const GXTexObj* MemoryCardManager::create_banner(u8 slot, s16 index) {
    CardDirectory* dirs = reinterpret_cast<CardDirectory*>(memorycard::getCardDirState());
    CardIcons* icons = reinterpret_cast<CardIcons*>(memorycard::getIconStateArray());
    u32 file = mFile[slot][index].fileNo;
    if (dirs[slot][file].fileNo == 0 || !icons[slot][file].bannerEnable) {
        return NULL;
    }
    if ((int)icons[slot][file].bannerType == GX_TF_RGB5A3) {
        const GXTexObj* banner = initBannerTexture(slot, file,
            reinterpret_cast<u8*>(&icons[slot][file]) + icons[slot][file].bannerOffset);
        GXLoadTexObj(banner, GX_TEXMAP0);
    } else if ((int)icons[slot][file].bannerType == GX_TF_C8) {
        initBannerTextureCI(slot, file,
            reinterpret_cast<u8*>(&icons[slot][file]) + icons[slot][file].bannerOffset);
        GXTlutObj* tlut = initBannerPalette(slot, file,
            reinterpret_cast<u8*>(&icons[slot][file]) + icons[slot][file].bannerTlutOffset);
        GXLoadTlut(tlut, GX_TLUT0);
        GXLoadTexObj(&mFileCell[slot][(s32)file].banner, GX_TEXMAP0);
    }
    return &mFileCell[slot][file].banner;
}

u16 MemoryCardManager::getBlocks(u8 slot, s16 index) {
    CardDirectory* dirs = reinterpret_cast<CardDirectory*>(memorycard::getCardDirState());
    return dirs[slot][mFile[slot][index].fileNo].size;
}

u16 MemoryCardManager::getFreeBlocks(u8 slot) {
    memorycard::CardState* states = memorycard::getCardSlotState();
    return states[slot].freeBlocks;
}

}
}
