#define IPL_CARD_SEQUENCE_CPP
#include "iplSystem.h"
#include "iplMemoryCardLib.h"

#include <revolution.h>
#include <revolution/card.h>
#include <revolution/mem/allocator.h>
#include <private/card.h>
#include <egg/core/eggHeap.h>

namespace ipl {
namespace memorycard {

struct CardThreadState {
    CardState slots[2];
    FileInfo files[2][127];
    void* mountBuffers[2];
    s32 mounted[2];
    OSMessageQueue responses;
    OSMessageQueue requests;
    OSMessage responseMessages[16];
    OSMessage requestMessages[16];
    OSThread thread;
    u8 stack[0x8000];
    char temporaryFileName[32];
    CARDFileInfo sourceFile;
    CARDFileInfo destinationFile;
    void* transferBuffer;
    IconState icons[2][127];
    u8* images[2][127];
    char* comments[2][127];
    u8 commentBuffer[0x400] ATTRIBUTE_ALIGN(32);
    u8* imageReadBuffer;
    s32 lastCommand;
    s32 lastResult;
    s32 completionResult;
    s32 scanComplete;
    s32 scanPending;
    s32 writePending;
    u8 sourceSlot;
    u8 valid;
    u8 destinationFileNo;
    u8 stopRequested;
};

MEMAllocator sAllocator_;
static CardThreadState* sThread;
extern "C" void* cardThreadMain(void*);
static char sCardSlotName[3] = "AB";

FileInfo* getCardDirState() {
    return sThread->files[0];
}

CardState* getCardSlotState() {
    return sThread->slots;
}

long getCardLastSrcSlot() {
    return sThread->sourceSlot;
}

long getCardLastSendCmd() {
    return sThread->lastCommand;
}

long getCardLastCMDFCmdResult() {
    return sThread->completionResult;
}

extern "C" s32 sendCardUnmountCmd(u8 slot) {
    sThread->sourceSlot = slot;
    sThread->lastCommand = 9;
    sThread->lastResult = -21;
    return OSSendMessage(&sThread->requests, (OSMessage)(slot << 16 | 9), 0);
}

void sendCardFormatCmd(u8 slot) {
    sThread->sourceSlot = slot;
    sThread->lastCommand = 1;
    sThread->lastResult = -21;
    sThread->completionResult = -21;
    OSSendMessage(&sThread->requests, (OSMessage)(slot << 16 | 1), 0);
}

void sendCardCopyCmd(u8 slot, s16 fileNo) {
    u32 message = ((u32)fileNo & 0xFF) << 24 | ((slot & 1) << 16);
    sThread->sourceSlot = slot;
    sThread->lastCommand = 2;
    sThread->lastResult = -21;
    sThread->completionResult = -21;
    message |= 2;
    OSSendMessage(&sThread->requests, (OSMessage)message, 0);
}

void sendCardMoveCmd(u8 slot, s16 fileNo) {
    u32 message = ((u32)fileNo & 0xFF) << 24 | ((slot & 1) << 16);
    sThread->sourceSlot = slot;
    sThread->lastCommand = 3;
    sThread->lastResult = -21;
    sThread->completionResult = -21;
    message |= 3;
    OSSendMessage(&sThread->requests, (OSMessage)message, 0);
}

void sendCardDeleteCmd(u8 slot, s16 fileNo) {
    u32 message = ((u32)fileNo & 0xFF) << 24 | ((slot & 1) << 16);
    sThread->sourceSlot = slot;
    sThread->lastCommand = 4;
    sThread->lastResult = -21;
    sThread->completionResult = -21;
    message |= 4;
    OSSendMessage(&sThread->requests, (OSMessage)message, 0);
}

void sendCardThreadStopCmd() NO_INLINE {
    sendCardUnmountCmd(0);
    sendCardUnmountCmd(1);
    OSSendMessage(&sThread->requests, (OSMessage)0xB, 0);
}

extern "C" void pollCardSlot(u8 slot) {
    s32 result;

    if (sThread->valid == 1) {
        result = CARDProbe(slot);
        if (result != 0) {

            if (sThread->slots[slot].state < 2) {
                sThread->sourceSlot = slot;
                sThread->lastCommand = 0;
                sThread->lastResult = -21;
                if (OSSendMessage(&sThread->requests,
                                  (OSMessage)(slot << 16), 0)) {
                    sThread->slots[slot].state = 3;
                    sThread->slots[slot].changed = 0;
                }
                goto done;
            }
        }
        if (result == 0) {
            if (sThread->slots[slot].state > 2 && sendCardUnmountCmd(slot)) {
                sThread->slots[slot].changed = 0;
            }
        }
    }
done:
    return;
}

extern "C" s32 mapCardErrorCode(s32 result) {
    switch (result) {
    case 0:
        return 0;
    case -2:
        return -28;
    case -3:
        return -28;
    case -4:
        return -28;
    case -5:
        return -28;
    case -6:
        return -28;
    case -7:
        return -24;
    case -8:
        return -25;
    case -9:
        return -25;
    case -10:
        return -28;
    case -11:
        return -28;
    case -12:
        return -28;
    case -13:
        return -28;
    case -27:
        return -27;
    default:
        return -28;
    }
}

void probeCard() {
    OSMessage message;

    pollCardSlot(0);
    pollCardSlot(1);
    while (OSReceiveMessage(&sThread->responses, &message, 0)) {
        s16 slot = (s16)(((u32)message >> 16) & 1);
        s8 command = (u8)(u32)message;

        if (command == 10) {
            goto updateSlotState;
        }
        if (command != 11) {
            goto checkCommand;
        }
updateSlotState:
        {
            sThread->valid = (u32)message >> 8;
            continue;
        }
checkCommand:
        if (command == 12) {
            sThread->scanComplete = 1;
            sThread->scanPending = 1;
            continue;
        } else {

            switch ((s8)(((u32)message << 16) >> 24)) {
            case -27:
            case -7:
            case 0:
                OSReport("ready or exit\n");

                sThread->slots[slot].state = 4;
                break;
            case -9:
            case -8:
                OSReport("Card hasn't enough space\n");

                sThread->slots[slot].state = 4;
                break;
            case -2:
                OSReport("Wrong Device\n");

                sThread->slots[slot].state = 5;
                break;
            case -6:
                OSReport("Broken Card\n");

                sThread->slots[slot].state = 6;
                break;
            case -13:
                OSReport("Other Language\n");

                sThread->slots[slot].state = 8;
                break;
            case -3:
                OSReport("Detach Card\n");

                sThread->slots[slot].state = 0;
                break;
            default:
                OSReport("Other Error\n");

                sThread->slots[slot].state = 10;
                break;
            }

            sThread->lastResult = mapCardErrorCode((s8)(((u32)message << 16) >> 24));
            if ((s8)(u8)(u32)message != 0 && (s8)(u8)(u32)message != 9) {
                sThread->completionResult = mapCardErrorCode((s8)(((u32)message << 16) >> 24));
                if (sThread->sourceSlot != (s16)(((u32)message >> 16) & 1)) {
                    sThread->destinationFileNo = (u32)message >> 24;
                }
            }
            OSReport("set slot state : ErrorCode: %d\n", sThread->lastResult);
            sThread->slots[slot].changed = 1;
            sThread->scanPending = 0;
        }
    }
}

void initCardThread() {
    EGG::Heap* heap;
    u32 size;
    void* memory;
    MEMHeapHandle handle;
    u32 index;

    if (sThread == 0) {
        heap = System::createMem1AppHeap();
        size = heap->getAllocatableSize(4);
        heap = System::createMem1AppHeap();
        memory = heap->alloc(size, 4);
        handle = MEMCreateExpHeapEx(memory, size, 0);
        MEMInitAllocatorForExpHeap(&sAllocator_, handle, 32);
        sAllocator_.heapParam2 = (u32)memory;
        OSReport("HEAP CREATE: %p %d\n", memory, size);
        sThread = (CardThreadState*)MEMAllocFromAllocator(&sAllocator_, sizeof(CardThreadState));
        memset(sThread, 0, sizeof(CardThreadState));
        sThread->images[0][0] = (u8*)MEMAllocFromAllocator(&sAllocator_, 0x594C00);
        sThread->comments[0][0] = (char*)MEMAllocFromAllocator(&sAllocator_, 0x3F80);
        sThread->imageReadBuffer = (u8*)MEMAllocFromAllocator(&sAllocator_, 0x5A00);
        sThread->transferBuffer = MEMAllocFromAllocator(&sAllocator_, 0x40000);
        sThread->mountBuffers[0] = MEMAllocFromAllocator(&sAllocator_, 0xA000);
        sThread->mountBuffers[1] = MEMAllocFromAllocator(&sAllocator_, 0xA000);
    }

    for (index = 0; index < 127; index++) {
        sThread->images[0][index] = sThread->images[0][0] + index * 0x5A00;
        sThread->comments[0][index] = sThread->comments[0][0] + index * 0x40;
    }
    for (index = 0; index < 127; index++) {
        sThread->images[1][index] = sThread->images[0][0] + (index + 127) * 0x5A00;
        sThread->comments[1][index] = sThread->comments[0][0] + (index + 127) * 0x40;
    }

    OSInitMessageQueue(&sThread->responses, sThread->responseMessages, 0x10);
    OSInitMessageQueue(&sThread->requests, sThread->requestMessages, 0x10);
    OSCreateThread(&sThread->thread, cardThreadMain, 0,
                   sThread->stack + sizeof(sThread->stack), 0x8000, 0x11, 0);
    OSResumeThread(&sThread->thread);
    OSSendMessage(&sThread->requests, (OSMessage)10, 0);
    OSReport("initCardThread successfully\n");
}

BOOL shutdownCardThread() {
    s32 result = 1;

    if (sThread != 0) {
        result = 0;
        if (sThread->stopRequested == 0) {
            sendCardThreadStopCmd();
            sThread->stopRequested = 1;
        }
        if (OSIsThreadTerminated(&sThread->thread)) {
            void* threadResult;
            OSJoinThread(&sThread->thread, &threadResult);
            MEMFreeToAllocator(&sAllocator_, sThread->mountBuffers[1]);
            MEMFreeToAllocator(&sAllocator_, sThread->mountBuffers[0]);
            MEMFreeToAllocator(&sAllocator_, sThread->transferBuffer);
            MEMFreeToAllocator(&sAllocator_, sThread->imageReadBuffer);
            MEMFreeToAllocator(&sAllocator_, sThread->images[0][0]);
            MEMFreeToAllocator(&sAllocator_, sThread->comments[0][0]);
            MEMFreeToAllocator(&sAllocator_, sThread);
            sThread = 0;
            MEMDestroyExpHeap((MEMHeapHandle)sAllocator_.heap);
            System::createMem1AppHeap()->free((void*)sAllocator_.heapParam2);
            System::destroyMem1AppHeap();
            OSReport("HEAP DESTROY\n");
            result = 1;
        }
    }

    return result;
}

IconState* getIconStateArray() {
    return sThread->icons[0];
}

const char* getIconComment(u8 slot, s16 index) {
    return sThread->comments[slot][index];
}

extern "C" void clearCardFileEntry(s32 slot, s32 index) {
    BOOL interrupts = OSDisableInterrupts();
    sThread->files[slot][index].fileNo = 0;
    sThread->files[slot][index].size = 0;
    sThread->files[slot][index].canCopy = 1;
    sThread->files[slot][index].canMove = 1;
    sThread->files[slot][index].unk_0x06 = 0;
    sThread->icons[slot][index].unk_0x01 = 0;
    sThread->icons[slot][index].bannerEnable = 0;
    OSRestoreInterrupts(interrupts);
}

extern "C" void refreshCardSlotInfo(s32 slot) {
    u16 memSize;
    u32 sectorSize;
    s32 freeBytes;
    s32 freeFiles;
    s32 result = CARDGetMemSize(slot, &memSize);
    if (result < 0) {
        OSReport("Get Memsize Error-%d: %d: %d\n", slot, result, memSize);
    }
    result = CARDGetSectorSize(slot, &sectorSize);
    if (result < 0) {
        OSReport("Get Sector Error- %d: %d\n", result, sectorSize);
    }
    result = CARDFreeBlocks(slot, &freeBytes, &freeFiles);
    if (result < 0) {
        OSReport("Get FreeBlocks Error- %d %d\n", result, freeBytes);
    }
    if (CARDGetResultCode(slot) >= 0) {
        BOOL interrupts = OSDisableInterrupts();

        sThread->slots[slot].unk_0x0C = ((u32)memSize << 17) / sectorSize - 5;
        sThread->slots[slot].key = sectorSize;
        sThread->slots[slot].unk_0x0E = freeFiles;
        sThread->slots[slot].freeBlocks = freeBytes / sectorSize;
        OSRestoreInterrupts(interrupts);
        OSReport("%d:%dbytes sectorsize , %d blocks , %d freeEntry\n", slot,
                 sThread->slots[slot].key, sThread->slots[slot].freeBlocks,
                 sThread->slots[slot].unk_0x0E);
    }
}

extern "C" s32 handleCardMountResult(s32 slot, s32 result);
extern "C" s32 reportCardThreadError(s32 slot, s32 state, s32 result);
extern "C" void sendCardSlotState(s32 slot, s32 state, s32 fileNo);
extern "C" void clearAllCardFileEntries(s32 slot);
extern "C" s32 loadCardFileIcons(s32 slot, s32 fileNo, CARDDir* dir);
extern "C" void runCardMoveOrCopy(u8 slot, s16 fileNo, s32 command);

static inline void sendValidityResponse(u32 command, u32 valid) {
    union {
        u32 value;
        struct { u32 upper : 16; u32 valid : 8; u32 command : 8; } fields;
    } reply;
    reply.value = command;
    reply.fields.valid = valid;
    OSSendMessage(&sThread->responses, (OSMessage)reply.value, 1);
}

extern "C" void* cardThreadMain(void*) {
    struct CardThreadLocals {
        u8 compareName[6];
        u32 message;
        CARDDir freeDir;
        CARDDir mountDir;
        CARDDir listingDir;
        char fileName[33];
    } local;
    BOOL brokenFile;
    BOOL exitThread = FALSE;
    u32 validState = TRUE;
    u32 command;
    s16 fileNo;
    u8 slot;
    s32 result;
    s32 file;
    u32 listingFile;
    s32 outerSlot;
    s32 freeFile;
    s32 freeBlocks;

    sThread->mounted[0] = 0;
    sThread->mounted[1] = 0;
    goto loopCheck;
loopStart:
        OSReceiveMessage(&sThread->requests, (OSMessage*)&local.message, 1);
        OSReport("CARD THREAD: Message received %d\n", (s8)(u8)local.message);
        if (validState != TRUE) {
            goto loopCheck;
        }
        command = local.message & 0xFF;

        switch ((s8)command) {
        case 10:
            validState = TRUE;
            OSReport("card thread valid state changed:%d\n", 1);
            sendValidityResponse(command, validState);
            break;
        case 11:
            exitThread = TRUE;
            break;
        case 0: {
            slot = (local.message >> 16) & 1;
            command = (local.message >> 14) & 4;
            result = CARDMount(slot, sThread->mountBuffers[command / 4], 0);
            if (result < 0) {
                result = handleCardMountResult(slot, result);
                if (result != 0) {
                    goto mountContinue;
                }
                break;
            }
            result = CARDCheck(slot);
            if (result < 0) {
                goto mountError;
            }

        mountContinue:
            clearAllCardFileEntries(slot);
            for (file = 0; file < 0x7F; ++file) {
                result = __CARDGetStatusEx(slot, (s16)file, &local.mountDir);
                if (result < 0) {
                    result = handleCardMountResult(slot, result);
                    if (result != 0) {
                        continue;
                    }
                    goto loopCheck;
                } else {
                    local.compareName[0] = 0;
                    local.compareName[1] = 0;
                    local.compareName[2] = 0;
                    local.compareName[3] = 0;
                    local.compareName[4] = 0;
                    local.compareName[5] = 0;
                    if (strncmp((const char*)local.mountDir.fileName, "Broken File", 0xB) == 0 &&
                        memcmp(local.mountDir.gameName, local.compareName + 2, 4) == 0 &&
                        memcmp(local.mountDir.company, local.compareName, 2) == 0) {
                        brokenFile = TRUE;
                    } else {
                        brokenFile = FALSE;
                    }
                    if (brokenFile) {
                        result = CARDFastDelete(slot, (s16)file);
                        if (result < 0) {
                            goto mountError;
                        }
                    } else {
                        result = loadCardFileIcons(slot, (s16)file, &local.mountDir);
                        if (result < 0) {
                            goto mountError;
                        }
                    }
                }
            }
            refreshCardSlotInfo(slot);
            sThread->mounted[command / 4] = 1;
            sendCardSlotState(slot, 0, 0);
            OSReport("Slot %c\n", sCardSlotName[slot]);
            for (listingFile = 0; listingFile < 0x7F; ++listingFile) {
                if (__CARDGetStatusEx(slot, (u16)listingFile, &local.listingDir) == 0) {
                    memcpy(local.fileName, local.listingDir.fileName, 0x20);
                    local.fileName[0x20] = 0;
                    OSReport("%d - %s: %d blocks\n", (u16)listingFile, local.fileName,
                             local.listingDir.length);
                }
            }
            break;

        mountError:
            OSReport("MountError\n");
            reportCardThreadError(slot, 0, result);
            break;
        }
        case 9:
            reportCardThreadError((local.message >> 16) & 1, 9, -3);
            break;
        case 1: {
            slot = (local.message >> 16) & 1;
            result = CARDFormat(slot);
            if (result < 0) {
                reportCardThreadError(slot, 1, result);
            } else {
                sThread->mounted[slot] = 1;
                refreshCardSlotInfo(slot);
                sendCardSlotState(slot, 1, 0);
            }
            break;
        }
        case 2:
            runCardMoveOrCopy((local.message >> 16) & 1,
                                   (s16)(u8)(local.message >> 24), (s8)command);
            break;
        case 3:
            runCardMoveOrCopy((local.message >> 16) & 1,
                                   (s16)(u8)(local.message >> 24), (s8)command);
            break;
        case 4: {
            slot = (local.message >> 16) & 1;
            fileNo = (s16)(local.message >> 24);
            result = CARDFastDelete(slot, fileNo);
            if (result < 0) {
                reportCardThreadError(slot, 4, result);
            } else {
                clearCardFileEntry(slot, fileNo);
                refreshCardSlotInfo(slot);
                sendCardSlotState(slot, 4, (u8)fileNo);
            }
            break;
        }
        case 12:
            outerSlot = 0;

            do {
                if (sThread->mounted[outerSlot] != 0) {
                    freeBlocks = 0;
                    for (freeFile = 0; freeFile < 0x7F; ++freeFile) {
                        result = __CARDGetStatusEx(outerSlot, freeFile, &local.freeDir);
                        if (result < 0 && result != -4) {
                            freeBlocks = -1;
                            break;
                        }
                        if (result == 0 &&
                            memcmp(local.freeDir.gameName, (void*)0x80000000, 4) == 0 &&
                            memcmp(local.freeDir.company, (void*)0x80000004, 2) == 0) {
                            freeBlocks += local.freeDir.length;
                        }
                    }
                    sThread->slots[outerSlot].unk_0x12 = freeBlocks;
                }
                ++outerSlot;

            } while (outerSlot < 2);
            sendCardSlotState(0, 0xC, 0);
            break;
        default:
            break;
        }
loopCheck:
    if (!exitThread) {
        goto loopStart;
    }
    return 0;
}

extern "C" s32 checkCardFileDuplicate(s32 slot, s16 fileNo);

extern "C" void markAllCardFilesDirty() {
    u32 slot = 0;
    s32 fileNo;

    s32 flagValue = 1;
    do {
        fileNo = 0;

        do {
            sThread->files[slot][fileNo].unk_0x06 = 0;
            if (sThread->mounted[slot] != 0 &&
                sThread->mounted[slot ^ 1] != 0 &&
                checkCardFileDuplicate((u8)slot, (s16)fileNo) < 0) {
                sThread->files[slot][fileNo].unk_0x06 = flagValue;
            }
            ++fileNo;

        } while (fileNo < 0x7F);
        ++slot;

    } while ((s32)slot < 2);
}

extern "C" s32 handleCardMountResult(s32 slot, s32 result) {
    if (result == -5) {
        goto reportError;
    }
    if (result >= -5) {
        goto positiveResult;
    }
    if (result >= -6) {
        goto repairedCard;
    }
    goto reportError;

positiveResult:
    if (result < -3) {
        return 1;
    }
    goto reportError;

repairedCard:
    {
        result = CARDCheck(slot);
        if (result < 0) {
            return reportCardThreadError(slot, 0, result);
        }
        OSReport("CardThread:Broken Card Repaired\n");
        return 1;
    }

reportError:
    return reportCardThreadError(slot, 0, result);
}

extern "C" s32 reportCardThreadError(s32 slot, s32 state, s32 result) {
    if (result != -7 && result != -27 && result != -8 && result != -9 &&
        (clearAllCardFileEntries(slot), result != -6) && result != -13) {
        OSReport("DEBUG: UnmountCard %d \n", slot);
        CARDUnmount(slot);
        sThread->mounted[slot & 0xFF] = 0;
    }
    OSReport("DEBUG: CardThread error %d %d\n", state, result);
    markAllCardFilesDirty();
    OSSendMessage(&sThread->responses,
                  (OSMessage)(((slot & 1) << 16) | ((result & 0xFF) << 8) | (state & 0xFF)), 1);
    return 0;
}

extern "C" void sendCardSlotState(s32 slot, s32 state, s32 fileNo) {
    markAllCardFilesDirty();
    OSMessageQueue* queue = &sThread->responses;
    union CardThreadMessage {
        u32 value;
        struct {
            u32 fileNo : 8;
            u32 padding0 : 7;
            u32 slot : 1;
            u32 padding1 : 8;
            u32 state : 8;
        } fields;
    } message;
    message.value = (u32)fileNo << 24;
    message.fields.slot = slot;
    message.fields.state = state;
    OSSendMessage(queue, (OSMessage)message.value, 1);
}

extern "C" void clearAllCardFileEntries(s32 slot) {
    s32 file = 0;
    do {
        clearCardFileEntry(slot, (s16)file);
        file = file + 1;
    } while (file < 0x7F);
}

extern "C" s32 loadCardFileIcons(s32 slot, s32 fileNo, CARDDir* dir) {
    struct CardSequenceFileData {
        s32 commentSectorSize;
        s32 sectorSize;
        CARDFileInfo fileInfo;
    } local;
    s32 iconAddressOffset;
    u32 iconAddressBase;
    s32 result;
    result = CARDFastOpen(slot, fileNo, &local.fileInfo);
    if (result < 0) {
        return result;
    }

    s32 bannerImageSize = 0;
    u8 format = dir->bannerFormat & 3;
    u32 iconAddress = dir->iconAddr;
    iconAddressBase = iconAddress & 0xFFFFFE00;
    iconAddressOffset = iconAddress - iconAddressBase;

    switch (format) {
    case 1: {
        bannerImageSize = 0xE00;
        sThread->icons[slot][fileNo].bannerEnable = 1;
        sThread->icons[slot][fileNo].bannerType = 9;
        sThread->icons[slot][fileNo].bannerOffset =
            (s32)sThread->images[slot][fileNo] -
            (s32)&sThread->icons[slot][fileNo];
        sThread->icons[slot][fileNo].bannerTlutOffset =
            sThread->icons[slot][fileNo].bannerOffset + 0xC00;
        sThread->icons[slot][fileNo].iconOffset[0] =
            sThread->icons[slot][fileNo].bannerTlutOffset + 0x200;
        break;
    }
    case 2: {
        bannerImageSize = 0x1800;
        sThread->icons[slot][fileNo].bannerEnable = 1;
        sThread->icons[slot][fileNo].bannerType = 5;
        sThread->icons[slot][fileNo].bannerOffset =
            (s32)sThread->images[slot][fileNo] -
            (s32)&sThread->icons[slot][fileNo];
        sThread->icons[slot][fileNo].iconOffset[0] =
            sThread->icons[slot][fileNo].bannerOffset + 0x1800;
        break;
    }
    default: {
        sThread->icons[slot][fileNo].bannerEnable = 0;
        sThread->icons[slot][fileNo].bannerType = 0;
        sThread->icons[slot][fileNo].iconOffset[0] =
            (s32)sThread->images[slot][fileNo] -
            (s32)&sThread->icons[slot][fileNo];
        break;
    }
    }

    s32 shift = 0;
    s32 iconImageSize = 0;
    s32 iconCount = 0;
    s32 icon;
    sThread->icons[slot][fileNo].unk_0x02 = 0;
    sThread->icons[slot][fileNo].anmMax = 0;
    sThread->icons[slot][fileNo].anmFrameBits = dir->iconSpeed;
    sThread->icons[slot][fileNo].unk_0x06 =
        (dir->iconSpeed & 3) << 2;
    for (icon = 0; icon < 8; ++icon) {
        s32 iconSpeed = (dir->iconSpeed >> shift) & 3;
        if (iconSpeed != 0) {
            sThread->icons[slot][fileNo].anmMax =
                sThread->icons[slot][fileNo].anmMax + (iconSpeed << 2);
        } else {
            sThread->icons[slot][fileNo].unk_0x07 =
                (u8)(((dir->iconSpeed >> ((iconCount - 1) * 2)) << 2) & 0xC);
            goto iconSpeedDone;
        }
        iconCount = iconCount + 1;
        shift = shift + 2;
    }
    sThread->icons[slot][fileNo].unk_0x07 =
        ((u16)dir->iconSpeed >> 0xC) & 0xC;

iconSpeedDone:
    if ((dir->iconSpeed & 3) == 0 || (dir->iconFormat & 3) == 0) {
        iconImageSize = 0;
        sThread->icons[slot][fileNo].unk_0x01 = 0;
    } else {
        BOOL hasTlut = FALSE;
        iconCount = 0;
        shift = 0;
        for (icon = 0; icon < 8; ++icon) {
            if (((dir->iconSpeed >> shift) & 3) != 0) {
                s32 iconFormat = (dir->iconFormat >> shift) & 3;
                s32 paletteSize;
                switch (iconFormat) {
                case 1:
                    paletteSize = 0x400;
                    hasTlut = TRUE;
                    sThread->icons[slot][fileNo].iconFmt[iconCount] = 9;
                    break;
                case 2:
                    paletteSize = 0x800;
                    sThread->icons[slot][fileNo].iconFmt[iconCount] = 5;
                    break;
                case 0: {
                    paletteSize = 0;
                    u8* iconPalette =
                        &sThread->icons[slot][fileNo].iconFmt[iconCount];
                    *iconPalette = iconPalette[-1];
                    break;
                }
                default:
                    paletteSize = 0;
                    break;
                }
                if (iconCount < 7) {
                    sThread->icons[slot][fileNo].iconOffset[iconCount + 1] =
                        paletteSize + sThread->icons[slot][fileNo].iconOffset[iconCount];
                } else {
                    sThread->icons[slot][fileNo].iconTlutOffset =
                        paletteSize + sThread->icons[slot][fileNo].iconOffset[iconCount];
                }
                iconImageSize += paletteSize;
                sThread->icons[slot][fileNo].unk_0x02 =
                    sThread->icons[slot][fileNo].unk_0x02 + 1;
            } else {
                sThread->icons[slot][fileNo].iconTlutOffset =
                    sThread->icons[slot][fileNo].iconOffset[iconCount];
                break;
            }
            ++iconCount;
            shift += 2;
        }
        if (hasTlut) {
            iconImageSize += 0x200;
        }
        sThread->icons[slot][fileNo].unk_0x01 = 1;
        sThread->icons[slot][fileNo].anmType = dir->bannerFormat & 4;
        sThread->icons[slot][fileNo].anmDelta = 1;
    }

    s32 totalImageSize = iconImageSize + bannerImageSize;
    u32 transferSize = (totalImageSize + iconAddressOffset + 0x1FF) & 0xFFFFFE00;
    result = CARDGetSectorSize(slot, (u32*)&local.sectorSize);
    if (result < 0) {
        result = 0;
        sThread->icons[slot][fileNo].bannerEnable = 0;
        sThread->icons[slot][fileNo].unk_0x01 = 0;
    } else {
        u32 fileSize = (u32)dir->length * local.sectorSize;
        if (iconAddressBase > fileSize) {
            result = 0;
            sThread->icons[slot][fileNo].bannerEnable = 0;
            sThread->icons[slot][fileNo].unk_0x01 = 0;
        } else if (iconAddressBase + transferSize > fileSize) {
            result = 0;
            sThread->icons[slot][fileNo].bannerEnable = 0;
            sThread->icons[slot][fileNo].unk_0x01 = 0;
        } else if (totalImageSize > 0) {
            result = CARDRead(&local.fileInfo, sThread->imageReadBuffer,
                              transferSize, iconAddressBase);
            if (result < 0) {
                goto closeFile;
            }
            memcpy(sThread->images[slot][fileNo],
                   (u8*)sThread->imageReadBuffer + iconAddressOffset,
                   totalImageSize);
            DCStoreRange(sThread->images[slot][fileNo], transferSize);
            result = 0;
        }
    }

    if (result < 0) {
        goto closeFile;
    }

    iconAddress = dir->commentAddr;
    iconAddressBase = iconAddress & 0xFFFFFE00;
    s32 commentDataOffset = iconAddress - iconAddressBase;
    s32 imageSize = ((iconAddress + 0x23F) & 0xFFFFFE00) - iconAddressBase;
    result = CARDGetSectorSize(slot, (u32*)&local.commentSectorSize);
    if (result < 0) {
        goto clearComment;
    }
    {
        u32 fileSize;
        if ((s32)iconAddressBase < 0 ||
            iconAddressBase > (fileSize = (u32)dir->length * local.commentSectorSize)) {
            result = 0;
        } else {
            u32 endOffset = iconAddressBase + imageSize;
            if ((s32)endOffset < 0 || endOffset > fileSize) {
                result = 0;
                goto clearComment;
            }
            result = CARDRead(&local.fileInfo, sThread->commentBuffer, imageSize,
                              iconAddressBase);
            if (result < 0) {
                goto clearComment;
            }
            memset(sThread->comments[slot][fileNo], 0, 0x40);
            memcpy(sThread->comments[slot][fileNo],
                   sThread->commentBuffer + commentDataOffset, 0x40);
            result = 0;
            goto commentDone;
        }
    }

clearComment:
    memset(sThread->comments[slot][fileNo], 0, 0x40);

commentDone:
    if (result >= 0) {
        goto closeFileSuccess;
    }
closeFile:
    return result;

closeFileSuccess:
    result = CARDClose(&local.fileInfo);
    if (result < 0) {
        return result;
    }

    sThread->files[slot][fileNo].fileNo = 1;
    sThread->files[slot][fileNo].size = dir->length;
    sThread->files[slot][fileNo].key = dir->time;
    sThread->files[slot][fileNo].canCopy = ((dir->permission >> 3) & 1) ^ 1;
    sThread->files[slot][fileNo].canMove = ((dir->permission >> 4) & 1) ^ 1;
    return 0;
}

extern "C" void clearCardWritePending(s32, s32) {
    sThread->writePending = 0;
}

extern "C" s32 checkCardFileDuplicate(s32 slot, s16 fileNo) {
    CARDDir sourceDir;
    CARDDir otherDir;
    s32 result = __CARDGetStatusEx(slot, fileNo, &sourceDir);
    if (result < 0) {
        return result;
    }

    s32 file = 0;
    do {
        s32 otherResult = __CARDGetStatusEx(slot ^ 1, file, &otherDir);
        if (otherResult < 0 && otherResult != -4) {
            return otherResult;
        }
        if (otherResult == 0 && memcmp(sourceDir.gameName, otherDir.gameName, 4) == 0 &&
            memcmp(sourceDir.company, otherDir.company, 2) == 0 &&
            memcmp(sourceDir.fileName, otherDir.fileName, 0x20) == 0) {
            return -7;
        }
        file = file + 1;
    } while (file < 0x7F);
    return 0;
}

static inline u32 clampCardTransferBlocks(u32 remaining, u32 maximum) {
    return remaining > maximum ? maximum : remaining;
}

static inline s16 createCardTemporaryFile(s32 destinationSlot, const CARDDir& source, s32 sectorSize) {
    s16 destinationFileNo = -1;
    s32 result;
    s32 attempt = 0;
    u32 fileSize = (u32)source.length * sectorSize;
    do {
        sprintf(sThread->temporaryFileName, "Broken File%03d", attempt);
        result = CARDCreate(destinationSlot, sThread->temporaryFileName,
                            fileSize, &sThread->destinationFile);
        if (result < 0 && result != -7) {
            OSReport("Can't Create temp File with Error.");
            return (s16)result;
        }
        ++attempt;
    } while (result != 0 && attempt < 0x80);
    if (attempt < 0x80) {
        destinationFileNo = sThread->destinationFile.fileNo;
    } else {
        destinationFileNo = -0x80;
    }
    return destinationFileNo;
}

extern "C" void runCardMoveOrCopy(u8 slot, s16 fileNo, s32 command) {
    CARDDir createStatus;
    CARDDir checkedStatus;
    CARDDir ioStatus;
    CARDDir sourceStatus;
    CARDDir renamedStatus;
    CARDDir moveStatus;
    u32 destinationSectorSize;
    u32 sourceSectorSize;
    s32 commonSectorSize;
    s32 result;
    s32 sectorError;
    s32 statusResult;
    u32 oldTime;
    BOOL cancelSent;
    s32 stage;
    s32 offset;
    s32 size;
    u32 maxBlocks;
    s32 block;
    s32 ioResult;
    s32 copyResult;
    s32 moveResult;
    s32 moveStage;
    s16 renameAttempt;
    s32 destinationSlot;
    s16 destinationFileNo = -1;
    BOOL temporaryCreated = FALSE;
    BOOL metadataCopied = FALSE;

    result = checkCardFileDuplicate(slot, fileNo);

    if (result < 0) {
        reportCardThreadError(slot, command, result);
        goto finish;
    }

    commonSectorSize = 0;
    result = CARDGetSectorSize(0, &sourceSectorSize);
    if (result < 0) {
        sectorError = result;
        goto sectorSizeCheck;
    }
    result = CARDGetSectorSize(1, &destinationSectorSize);
    if (result < 0) {
        sectorError = result;
        goto sectorSizeCheck;
    }
    if (sourceSectorSize != destinationSectorSize) {
        sectorError = -27;
    } else {
        commonSectorSize = sourceSectorSize;
        sectorError = 0;
    }
sectorSizeCheck:
    if (sectorError >= 0) {
        goto sectorSizeDone;
    }
sectorSizeError:
    reportCardThreadError(slot, command, sectorError);
    goto finish;
sectorSizeDone:
    ;

    {
        s32 permissionResult = 0;
        statusResult = __CARDGetStatusEx(slot, fileNo, &checkedStatus);
        if (statusResult >= 0) {
            switch (command) {
            case 2:
                if (checkedStatus.permission & 8) {
                    permissionResult = -10;
                }
                break;
            case 3:
                if (checkedStatus.permission & 0x10) {
                    permissionResult = -10;
                }
                break;
            }
        } else {
            permissionResult = CARDGetResultCode(slot);
        }
        if (permissionResult < 0) {
            reportCardThreadError(slot, command, permissionResult);
            goto finish;
        }
    }

    result = __CARDGetStatusEx(slot, fileNo, &createStatus);
    if (result < 0) {
        goto cleanup;
    }

    destinationSlot = slot ^ 1;
    destinationFileNo = createCardTemporaryFile(destinationSlot, createStatus, commonSectorSize);
    if (destinationFileNo < 0) {
        reportCardThreadError(destinationSlot, command, destinationFileNo);
        goto finish;
    }

    temporaryCreated = TRUE;
    stage = 0;
    cancelSent = FALSE;
    {
        u32 sectorSize;

        ioResult = __CARDGetStatusEx(slot, fileNo, &ioStatus);
        if (ioResult < 0) {
            goto copyIoFailure;
        }
        stage = 1;
        ioResult = CARDGetSectorSize(slot, &sectorSize);
        if (ioResult < 0) {
            goto copyIoFailure;
        }
        maxBlocks = 0x40000 / sectorSize;
        stage = 2;
        ioResult = CARDFastOpen(slot, fileNo, &sThread->sourceFile);
        if (ioResult < 0) {
            goto copyIoFailure;
        }
        block = 0;
        stage = 3;
        for (; block < ioStatus.length; block += maxBlocks) {
            u32 blocks = clampCardTransferBlocks((u32)ioStatus.length - block, maxBlocks);
            offset = block * sectorSize;
            size = blocks * sectorSize;
            ioResult = CARDRead(&sThread->sourceFile,
                                sThread->transferBuffer, size, offset);
            if (ioResult < 0) {
                goto copyIoFailure;
            }
            sThread->writePending = 1;
            ioResult = CARDWriteAsync(&sThread->destinationFile,
                                      sThread->transferBuffer, size, offset,
                                      clearCardWritePending);
            if (ioResult < 0) {
                goto copyIoFailure;
            }
            while (sThread->writePending != 0) {
                if (CARDProbe(slot) == 0 && !cancelSent) {
                    CARDCancel(&sThread->destinationFile);
                    cancelSent = TRUE;
                }
            }
        }
        stage = 4;
        ioResult = CARDClose(&sThread->sourceFile);
        if (ioResult < 0) {
            goto copyIoFailure;
        }
        stage = 5;
        ioResult = CARDClose(&sThread->destinationFile);
        if (ioResult >= 0) {
            result = 0;
            goto copyIoDone;
        }

copyIoFailure:
        switch (stage) {
        case 0:
            OSReport("Can't get status of Copy source File.\n");
            break;
        case 1:
            OSReport("Can't get sector size of Copy source card.\n");
            break;
        case 2:
            OSReport("Can't Open Copy source File.\n");
            break;
        case 3:
            OSReport("Can't read or write data.\n");
            break;
        case 4:
            OSReport("Can't Close Copy src File.\n");
            break;
        case 5:
            OSReport("Can't Close Copy dst File.\n");
            break;
        }
        CARDFastDelete(destinationSlot, sThread->destinationFile.fileNo);
        result = ioResult;
copyIoDone:
        ;
    }

    if (result < 0) {
        goto cleanup;
    }
    if (command == 2) {
        copyResult = __CARDGetStatusEx(slot, fileNo, &sourceStatus);
        if (copyResult < 0) {
            OSReport("Can't get status for src file\n");
        } else {
            ++sourceStatus.copyTimes;
            copyResult = __CARDSetStatusEx(slot, fileNo, &sourceStatus);
            if (copyResult < 0) {
                OSReport("Can't set status for src file %d\n", copyResult);
            } else {
                oldTime = sourceStatus.time;
                sourceStatus.time = (u32)(OSGetTime() / (*(u32*)0x800000F8 >> 2));
                copyResult = __CARDSetStatusEx(destinationSlot, destinationFileNo,
                                                    &sourceStatus);
                if (copyResult < 0) {
                    OSReport("Can't set status for dst file (src file copyTimes--)\n");
                    if (copyResult != -3) {
                        --sourceStatus.copyTimes;
                    }
                    sourceStatus.time = oldTime;
                    s32 restoreResult = __CARDSetStatusEx(slot, fileNo, &sourceStatus);
                    if (restoreResult < 0) {
                        OSReport("Can't set status for src file(src file copyTimes--)\n");
                    }
                } else {
                    metadataCopied = TRUE;
                    copyResult = loadCardFileIcons(destinationSlot, destinationFileNo,
                                                       &sourceStatus);
                    if (copyResult < 0) {
                        OSReport("Can't read icon for move dstfile\n");
                    } else {
                        copyResult = 0;
                    }
                }
            }
        }
        result = copyResult;
        if (result < 0) {
            goto cleanup;
        }
    } else if (command == 3) {
        renameAttempt = 0;
        moveStage = 0;
        moveResult = __CARDGetStatusEx(slot, fileNo, &moveStatus);
        if (moveResult >= 0) {
            ++moveStage;
            renamedStatus = moveStatus;
            memset(renamedStatus.company, 0, 2);
            memset(renamedStatus.gameName, 0, 4);
            do {
                memset(renamedStatus.fileName, 0, 0x20);
                sprintf((char*)renamedStatus.fileName, "Broken File%03d", renameAttempt);
                moveResult = __CARDSetStatusEx(slot, fileNo, &renamedStatus);
                if (moveResult < 0 && moveResult != -7) {
                    goto moveStatusError;
                }
                ++renameAttempt;
            } while (moveResult != 0 && renameAttempt < 0x80);
            moveStage = 2;
            moveResult = __CARDSetStatusEx(destinationSlot, destinationFileNo,
                                       &moveStatus);
            if (moveResult < 0) {
                s32 setResult = moveResult;
                if (moveResult == -3) {
                    CARDFastDelete(slot, fileNo);
                    clearCardFileEntry(slot, fileNo);
                } else {
                    s32 restoreResult = __CARDSetStatusEx(slot, fileNo, &moveStatus);
                    if (restoreResult < 0) {
                        OSReport("Can't repair src file - carddir\n");
                    }
                }
                moveResult = setResult;
            } else {
                metadataCopied = TRUE;
                moveStage = 3;
                moveResult = CARDFastDelete(slot, fileNo);
                if (moveResult >= 0) {
                    clearCardFileEntry(slot, fileNo);
                    moveStage = 4;
                    moveResult = __CARDGetStatusEx(destinationSlot,
                                                  destinationFileNo, &moveStatus);
                    if (moveResult >= 0) {
                        moveStage = 5;
                        if ((moveResult = loadCardFileIcons(
                                 destinationSlot, destinationFileNo, &moveStatus)) < 0) {
                            goto moveStatusError;
                        }
                        moveResult = 0;
                        goto moveStatusDone;
                    }
                }
            }
        }
moveStatusError:
        switch (moveStage) {
        case 0:
            OSReport("Cant' get status for src file.\n");
            break;
        case 1:
            OSReport("Can't set status for src file\n");
            break;
        case 2:
            OSReport("Can't rename dst file\n");
            break;
        case 3:
            OSReport("Can't Delete src file\n");
            break;
        case 4:
            OSReport("Cant' get status for dst file.\n");
            break;
        case 5:
            OSReport("Can't read icon for move dstfile\n");
            break;
        }
moveStatusDone:
        if (moveResult < 0) {
            goto cleanup;
        }
    }

    refreshCardSlotInfo(slot);
    refreshCardSlotInfo(destinationSlot);
    sendCardSlotState(slot, 0, fileNo & 0xFF);
    sendCardSlotState(destinationSlot, command, destinationFileNo & 0xFF);
    goto finish;

cleanup:
    destinationSlot = slot ^ 1;
    result = CARDGetResultCode(destinationSlot);
    if (result < 0) {
        reportCardThreadError(destinationSlot, command, result);
    } else {
        if (temporaryCreated && !metadataCopied) {
            CARDFastDelete(destinationSlot, destinationFileNo);
        }
        if (metadataCopied) {
            if (__CARDGetStatusEx(destinationSlot, destinationFileNo,
                                  &createStatus) == 0) {
                loadCardFileIcons(destinationSlot, destinationFileNo, &createStatus);
            }
        }
        refreshCardSlotInfo(destinationSlot);
        sendCardSlotState(destinationSlot, 0, fileNo & 0xFF);
    }
    result = CARDGetResultCode(slot);
    if (result < 0) {
        reportCardThreadError(slot, command, result);
    } else {
        refreshCardSlotInfo(slot);
        sendCardSlotState(slot, 0, fileNo & 0xFF);
    }

finish:
    return;
}

}
}
