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
    FileInfo files[2][CARD_MAX_FILE];
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
    IconState icons[2][CARD_MAX_FILE];
    u8* images[2][CARD_MAX_FILE];
    char* comments[2][CARD_MAX_FILE];
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
    case CARD_RESULT_READY:
        return 0;
    case CARD_RESULT_WRONGDEVICE:
        return -28;
    case CARD_RESULT_NOCARD:
        return -28;
    case CARD_RESULT_NOFILE:
        return -28;
    case CARD_RESULT_IOERROR:
        return -28;
    case CARD_RESULT_BROKEN:
        return -28;
    case CARD_RESULT_EXIST:
        return -24;
    case CARD_RESULT_NOENT:
        return -25;
    case CARD_RESULT_INSSPACE:
        return -25;
    case CARD_RESULT_NOPERM:
        return -28;
    case CARD_RESULT_LIMIT:
        return -28;
    case CARD_RESULT_NAMETOOLONG:
        return -28;
    case CARD_RESULT_ENCODING:
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
            case CARD_RESULT_EXIST:
            case CARD_RESULT_READY:
                OSReport("ready or exit\n");

                sThread->slots[slot].state = 4;
                break;
            case CARD_RESULT_INSSPACE:
            case CARD_RESULT_NOENT:
                OSReport("Card hasn't enough space\n");

                sThread->slots[slot].state = 4;
                break;
            case CARD_RESULT_WRONGDEVICE:
                OSReport("Wrong Device\n");

                sThread->slots[slot].state = 5;
                break;
            case CARD_RESULT_BROKEN:
                OSReport("Broken Card\n");

                sThread->slots[slot].state = 6;
                break;
            case CARD_RESULT_ENCODING:
                OSReport("Other Language\n");

                sThread->slots[slot].state = 8;
                break;
            case CARD_RESULT_NOCARD:
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
        sThread = static_cast<CardThreadState*>(MEMAllocFromAllocator(&sAllocator_, sizeof(CardThreadState)));
        memset(sThread, 0, sizeof(CardThreadState));
        sThread->images[0][0] = static_cast<u8*>(MEMAllocFromAllocator(&sAllocator_, 0x594C00));
        sThread->comments[0][0] = static_cast<char*>(MEMAllocFromAllocator(&sAllocator_, 0x3F80));
        sThread->imageReadBuffer = static_cast<u8*>(MEMAllocFromAllocator(&sAllocator_, 0x5A00));
        sThread->transferBuffer = MEMAllocFromAllocator(&sAllocator_, 0x40000);
        sThread->mountBuffers[0] = MEMAllocFromAllocator(&sAllocator_, CARD_WORKAREA_SIZE);
        sThread->mountBuffers[1] = MEMAllocFromAllocator(&sAllocator_, CARD_WORKAREA_SIZE);
    }

    for (index = 0; index < CARD_MAX_FILE; index++) {
        sThread->images[0][index] = sThread->images[0][0] + index * 0x5A00;
        sThread->comments[0][index] = sThread->comments[0][0] + index * CARD_COMMENT_SIZE;
    }
    for (index = 0; index < CARD_MAX_FILE; index++) {
        sThread->images[1][index] = sThread->images[0][0] + (index + CARD_MAX_FILE) * 0x5A00;
        sThread->comments[1][index] = sThread->comments[0][0] + (index + CARD_MAX_FILE) * CARD_COMMENT_SIZE;
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
            MEMDestroyExpHeap(static_cast<MEMHeapHandle>(sAllocator_.heap));
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
    if (result < CARD_RESULT_READY) {
        OSReport("Get Memsize Error-%d: %d: %d\n", slot, result, memSize);
    }
    result = CARDGetSectorSize(slot, &sectorSize);
    if (result < CARD_RESULT_READY) {
        OSReport("Get Sector Error- %d: %d\n", result, sectorSize);
    }
    result = CARDFreeBlocks(slot, &freeBytes, &freeFiles);
    if (result < CARD_RESULT_READY) {
        OSReport("Get FreeBlocks Error- %d %d\n", result, freeBytes);
    }
    if (CARDGetResultCode(slot) >= CARD_RESULT_READY) {
        BOOL interrupts = OSDisableInterrupts();

        sThread->slots[slot].unk_0x0C = ((u32)memSize << 17) / sectorSize - CARD_NUM_SYSTEM_BLOCK;
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
    reply.value = valid << 8;
    reply.fields.command = command;
    OSSendMessage(&sThread->responses, (OSMessage)reply.value, OS_MESSAGE_BLOCK);
}

static inline u8 getCardCommandSlot(u32 message) {
    u8 slot = message >> 16;
    slot &= 1;
    return slot;
}

static inline s32 countCardTitleBlocks(s32 slot, CARDDir* dir) {
    s32 fileNo;
    s32 result;
    s32 blocks;
    blocks = 0;
    for (fileNo = 0; fileNo < CARD_MAX_FILE; ++fileNo) {
        result = __CARDGetStatusEx(slot, fileNo, dir);
        if (result < CARD_RESULT_READY && result != CARD_RESULT_NOFILE) {
            blocks = -1;
            break;
        }
        if (result == CARD_RESULT_READY &&
            memcmp(dir->gameName, (void*)0x80000000, 4) == 0 &&
            memcmp(dir->company, (void*)0x80000004, 2) == 0) {
            blocks += dir->length;
        }
    }
    return blocks;
}

static inline void listCardFiles(u8 slot, CARDDir& dir, char* fileName) {
    u32 fileNo;
    for (fileNo = 0; fileNo < CARD_MAX_FILE; ++fileNo) {
        if (__CARDGetStatusEx(slot, (u16)fileNo, &dir) == CARD_RESULT_READY) {
            memcpy(fileName, dir.fileName, CARD_FILENAME_MAX);
            fileName[CARD_FILENAME_MAX] = 0;
            OSReport("%d - %s: %d blocks\n", (u16)fileNo, fileName, dir.length);
        }
    }
}

static inline void deleteCardFile(u8 slot, s16 fileNo) {
    s32 result = CARDFastDelete(slot, fileNo);
    if (result < CARD_RESULT_READY) {
        reportCardThreadError(slot, 4, result);
    } else {
        clearCardFileEntry(slot, fileNo);
        refreshCardSlotInfo(slot);
        sendCardSlotState(slot, 4, (u8)fileNo);
    }
}

extern "C" void* cardThreadMain(void*) {
    char fileName[33];
    CARDDir listingDir;
    CARDDir mountDir;
    CARDDir freeDir;
    u32 message;
    s32 result;
    u8 slot;
    BOOL brokenFile;
    s32 scanResult;
    s32 file;
    s32 freeBlocks;
    s32 outerSlot;
    u32 validState = TRUE;
    BOOL exitThread = FALSE;
    u32 command;

    sThread->mounted[0] = 0;
    sThread->mounted[1] = 0;
    goto loopCheck;
loopStart:
        OSReceiveMessage(&sThread->requests, (OSMessage*)&message, OS_MESSAGE_BLOCK);
        OSReport("CARD THREAD: Message received %d\n", (s8)(u8)message);
        if (validState != TRUE) {
            goto loopCheck;
        }
        command = message & 0xFF;

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
            slot = getCardCommandSlot(message);
            command = (message >> 14) & 4;
            result = CARDMount(slot, sThread->mountBuffers[command / 4], 0);
            if (result < CARD_RESULT_READY) {
                result = handleCardMountResult(slot, result);
                if (result != CARD_RESULT_READY) {
                    goto mountContinue;
                }
                break;
            }
            scanResult = CARDCheck(slot);
            if (scanResult < CARD_RESULT_READY) {
                goto mountError;
            }

        mountContinue:
            clearAllCardFileEntries(slot);
            for (file = 0; file < CARD_MAX_FILE; ++file) {
                result = __CARDGetStatusEx(slot, (s16)file, &mountDir);
                if (result < CARD_RESULT_READY) {
                    result = handleCardMountResult(slot, result);
                    if (result != CARD_RESULT_READY) {
                        continue;
                    }
                    goto loopCheck;
                } else {
                    u8 company[2];
                    u8 gameName[4];
                    company[0] = 0;
                    company[1] = 0;
                    gameName[0] = 0;
                    gameName[1] = 0;
                    gameName[2] = 0;
                    gameName[3] = 0;
                    if (strncmp((const char*)mountDir.fileName, "Broken File", 0xB) == 0 &&
                        memcmp(mountDir.gameName, gameName, 4) == 0 &&
                        memcmp(mountDir.company, company, 2) == 0) {
                        brokenFile = TRUE;
                    } else {
                        brokenFile = FALSE;
                    }
                    if (brokenFile) {
                        scanResult = CARDFastDelete(slot, (s16)file);
                        if (scanResult < CARD_RESULT_READY) {
                            goto mountError;
                        }
                    } else {
                        scanResult = loadCardFileIcons(slot, (s16)file, &mountDir);
                        if (scanResult < CARD_RESULT_READY) {
                            goto mountError;
                        }
                    }
                }
            }
            refreshCardSlotInfo(slot);
            sThread->mounted[command / 4] = 1;
            sendCardSlotState(slot, 0, 0);
            OSReport("Slot %c\n", sCardSlotName[slot]);
            listCardFiles(slot, listingDir, fileName);
            break;

        mountError:
            OSReport("MountError\n");
            reportCardThreadError(slot, 0, scanResult);
            break;
        }
        case 9:
            reportCardThreadError(getCardCommandSlot(message), 9, CARD_RESULT_NOCARD);
            break;
        case 1: {
            slot = getCardCommandSlot(message);
            result = CARDFormat(slot);
            if (result < CARD_RESULT_READY) {
                reportCardThreadError(slot, 1, result);
            } else {
                sThread->mounted[slot] = 1;
                refreshCardSlotInfo(slot);
                sendCardSlotState(slot, 1, 0);
            }
            break;
        }
        case 2:
            runCardMoveOrCopy(getCardCommandSlot(message),
                                   (s16)(u8)(message >> 24), (s8)command);
            break;
        case 3:
            runCardMoveOrCopy(getCardCommandSlot(message),
                                   (s16)(u8)(message >> 24), (s8)command);
            break;
        case 4:
            deleteCardFile(getCardCommandSlot(message), (s16)(message >> 24));
            break;
        case 12:
            outerSlot = 0;

            do {
                if (sThread->mounted[outerSlot] != 0) {
                    freeBlocks = countCardTitleBlocks(outerSlot, &freeDir);
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

        } while (fileNo < CARD_MAX_FILE);
        ++slot;

    } while ((s32)slot < 2);
}

extern "C" s32 handleCardMountResult(s32 slot, s32 result) {
    if (result == CARD_RESULT_IOERROR) {
        goto reportError;
    }
    if (result >= CARD_RESULT_IOERROR) {
        goto positiveResult;
    }
    if (result >= CARD_RESULT_BROKEN) {
        goto repairedCard;
    }
    goto reportError;

positiveResult:
    if (result < CARD_RESULT_NOCARD) {
        return 1;
    }
    goto reportError;

repairedCard:
    {
        result = CARDCheck(slot);
        if (result < CARD_RESULT_READY) {
            return reportCardThreadError(slot, 0, result);
        }
        OSReport("CardThread:Broken Card Repaired\n");
        return 1;
    }

reportError:
    return reportCardThreadError(slot, 0, result);
}

extern "C" s32 reportCardThreadError(s32 slot, s32 state, s32 result) {
    if (result != CARD_RESULT_EXIST && result != -27 && result != CARD_RESULT_NOENT && result != CARD_RESULT_INSSPACE &&
        (clearAllCardFileEntries(slot), result != CARD_RESULT_BROKEN) && result != CARD_RESULT_ENCODING) {
        OSReport("DEBUG: UnmountCard %d \n", slot);
        CARDUnmount(slot);
        sThread->mounted[slot & 0xFF] = 0;
    }
    OSReport("DEBUG: CardThread error %d %d\n", state, result);
    markAllCardFilesDirty();
    OSSendMessage(&sThread->responses,
                  (OSMessage)(((slot & 1) << 16) | ((result & 0xFF) << 8) | (state & 0xFF)), OS_MESSAGE_BLOCK);
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
    OSSendMessage(queue, (OSMessage)message.value, OS_MESSAGE_BLOCK);
}

extern "C" void clearAllCardFileEntries(s32 slot) {
    s32 file = 0;
    do {
        clearCardFileEntry(slot, (s16)file);
        file = file + 1;
    } while (file < CARD_MAX_FILE);
}

static inline s32 readCardImages(s32 slot, s32 fileNo, CARDDir* dir, CARDFileInfo* fileInfo,
                                 u32 address, s32 offset, s32 imageSize, u32 transferSize) {
    s32 sectorSize;
    if (CARDGetSectorSize(slot, (u32*)&sectorSize) < CARD_RESULT_READY) {
        sThread->icons[slot][fileNo].bannerEnable = 0;
        sThread->icons[slot][fileNo].unk_0x01 = 0;
        return 0;
    }

    u32 fileSize = (u32)dir->length * sectorSize;
    if (address > fileSize) {
        sThread->icons[slot][fileNo].bannerEnable = 0;
        sThread->icons[slot][fileNo].unk_0x01 = 0;
        return 0;
    }
    if (address + transferSize > fileSize) {
        sThread->icons[slot][fileNo].bannerEnable = 0;
        sThread->icons[slot][fileNo].unk_0x01 = 0;
        return 0;
    }

    if (imageSize > 0) {
        s32 result = CARDRead(fileInfo, sThread->imageReadBuffer, transferSize, address);
        if (result < CARD_RESULT_READY) {
            return result;
        }
        memcpy(sThread->images[slot][fileNo], sThread->imageReadBuffer + offset, imageSize);
        DCStoreRange(sThread->images[slot][fileNo], transferSize);
    }
    return 0;
}

static inline s32 readCardComment(s32 slot, s32 fileNo, CARDDir* dir, CARDFileInfo* fileInfo) {
    u32 address;
    s32 result;
    u32 base;
    s32 readSize;
    u32 end;
    u32 fileSize;
    s32 offset;
    s32 sectorSize;
    address = dir->commentAddr;
    base = address & 0xFFFFFE00;
    offset = address - base;
    readSize = ((address + 0x23F) & 0xFFFFFE00) - base;
    result = CARDGetSectorSize(slot, (u32*)&sectorSize);
    if (result >= CARD_RESULT_READY) {
        if ((s32)base < 0 || base > (fileSize = (u32)dir->length * sectorSize)) {
            result = 0;
        } else {
            end = base + readSize;
            if ((s32)end < 0 || end > fileSize) {
                result = 0;
            } else {
                result = CARDRead(fileInfo, sThread->commentBuffer, readSize, base);
                if (result >= CARD_RESULT_READY) {
                    memset(sThread->comments[slot][fileNo], 0, CARD_COMMENT_SIZE);
                    memcpy(sThread->comments[slot][fileNo], sThread->commentBuffer + offset,
                           CARD_COMMENT_SIZE);
                    return 0;
                }
            }
        }
    }

    memset(sThread->comments[slot][fileNo], 0, CARD_COMMENT_SIZE);
    return result;
}

static inline s32 loadCardIconImages(s32 slot, s32 fileNo, CARDDir* dir, CARDFileInfo* fileInfo) {
    s32 imageSize;
    s32 bannerImageSize = 0;
    u8 format = dir->bannerFormat & CARD_STAT_BANNER_MASK;
    u32 iconAddress = dir->iconAddr;
    u32 transferSize;
    s32 iconAddressOffset = iconAddress - (iconAddress & 0xFFFFFE00);

    switch (format) {
    case CARD_STAT_BANNER_C8: {
        bannerImageSize = 0xE00;
        sThread->icons[slot][fileNo].bannerEnable = 1;
        sThread->icons[slot][fileNo].bannerType = GX_TF_C8;
        sThread->icons[slot][fileNo].bannerOffset =
            (s32)sThread->images[slot][fileNo] -
            (s32)&sThread->icons[slot][fileNo];
        sThread->icons[slot][fileNo].bannerTlutOffset =
            sThread->icons[slot][fileNo].bannerOffset + 0xC00;
        sThread->icons[slot][fileNo].iconOffset[0] =
            sThread->icons[slot][fileNo].bannerTlutOffset + 0x200;
        break;
    }
    case CARD_STAT_BANNER_RGB5A3: {
        bannerImageSize = 0x1800;
        sThread->icons[slot][fileNo].bannerEnable = 1;
        sThread->icons[slot][fileNo].bannerType = GX_TF_RGB5A3;
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

    s32 iconImageSize;
    s32 paletteSize;
    s32 icon;
    BOOL hasTlut;
    s32 iconCount;
    s32 shift;

    shift = 0;
    hasTlut = FALSE;
    iconImageSize = 0;
    iconCount = 0;
    sThread->icons[slot][fileNo].unk_0x02 = 0;
    sThread->icons[slot][fileNo].anmMax = 0;
    sThread->icons[slot][fileNo].anmFrameBits = dir->iconSpeed;
    sThread->icons[slot][fileNo].unk_0x06 = (dir->iconSpeed & CARD_STAT_SPEED_MASK) << 2;
    for (icon = 0; icon < CARD_ICON_MAX; ++icon) {
        s32 iconSpeed = (dir->iconSpeed >> shift) & CARD_STAT_SPEED_MASK;
        if (iconSpeed != 0) {
            sThread->icons[slot][fileNo].anmMax += iconSpeed << 2;
        } else {
            sThread->icons[slot][fileNo].unk_0x07 =
                (u8)(((dir->iconSpeed >> ((iconCount - 1) * 2)) << 2) & 0xC);
            goto animationDone;
        }
        iconCount = iconCount + 1;
        shift = shift + 2;
    }
    sThread->icons[slot][fileNo].unk_0x07 = (dir->iconSpeed >> 0xC) & 0xC;
animationDone:
    if ((dir->iconSpeed & CARD_STAT_SPEED_MASK) == 0 || (dir->iconFormat & CARD_STAT_ICON_MASK) == 0) {
        sThread->icons[slot][fileNo].unk_0x01 = 0;
        iconImageSize = 0;
    } else {
        for (iconCount = 0; iconCount < CARD_ICON_MAX; ++iconCount) {
            if (((dir->iconSpeed >> (iconCount * 2)) & CARD_STAT_SPEED_MASK) != 0) {
                s32 iconFormat = (dir->iconFormat >> (iconCount * 2)) & CARD_STAT_ICON_MASK;
                switch (iconFormat) {
                case CARD_STAT_ICON_C8:
                    paletteSize = 0x400;
                    hasTlut = TRUE;
                    sThread->icons[slot][fileNo].iconFmt[iconCount] = GX_TF_C8;
                    break;
                case CARD_STAT_ICON_RGB5A3:
                    paletteSize = 0x800;
                    sThread->icons[slot][fileNo].iconFmt[iconCount] = GX_TF_RGB5A3;
                    break;
                case CARD_STAT_ICON_NONE: {
                    paletteSize = 0;
                    u8* previous = &sThread->icons[slot][fileNo].iconFmt[iconCount - 1];
                    sThread->icons[slot][fileNo].iconFmt[iconCount] = *previous;
                    break;
                }
                default:
                    break;
                }
                u32* iconOffsets = &sThread->icons[slot][fileNo].iconOffset[0];
                s32 nextIcon = iconCount + 1;
                if (iconCount < 7) {
                    sThread->icons[slot][fileNo].iconOffset[(u32)(iconCount + 1)] =
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
        }
        if (hasTlut) {
            iconImageSize += 0x200;
        }
        sThread->icons[slot][fileNo].unk_0x01 = 1;
        sThread->icons[slot][fileNo].anmType = dir->bannerFormat & 4;
        sThread->icons[slot][fileNo].anmDelta = 1;
    }

    imageSize = bannerImageSize + iconImageSize;
    transferSize = (imageSize + iconAddressOffset + 0x1FF) & 0xFFFFFE00;
    return readCardImages(slot, fileNo, dir, fileInfo, iconAddress & 0xFFFFFE00, iconAddressOffset,
                          imageSize, transferSize);
}

extern "C" s32 loadCardFileIcons(s32 slot, s32 fileNo, CARDDir* dir) {
    CARDFileInfo fileInfo;
    s32 result = CARDFastOpen(slot, fileNo, &fileInfo);
    if (result < CARD_RESULT_READY) {
        return result;
    }

    result = loadCardIconImages(slot, fileNo, dir, &fileInfo);
    if (result < CARD_RESULT_READY) {
        return result;
    }

    result = readCardComment(slot, fileNo, dir, &fileInfo);
    if (result < CARD_RESULT_READY) {
        return result;
    }

    result = CARDClose(&fileInfo);
    if (result < CARD_RESULT_READY) {
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
    if (result < CARD_RESULT_READY) {
        return result;
    }

    s32 file = 0;
    do {
        s32 otherResult = __CARDGetStatusEx(slot ^ 1, file, &otherDir);
        if (otherResult < CARD_RESULT_READY && otherResult != CARD_RESULT_NOFILE) {
            return otherResult;
        }
        if (otherResult == CARD_RESULT_READY && memcmp(sourceDir.gameName, otherDir.gameName, 4) == 0 &&
            memcmp(sourceDir.company, otherDir.company, 2) == 0 &&
            memcmp(sourceDir.fileName, otherDir.fileName, CARD_FILENAME_MAX) == 0) {
            return CARD_RESULT_EXIST;
        }
        file = file + 1;
    } while (file < CARD_MAX_FILE);
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
        if (result < CARD_RESULT_READY && result != CARD_RESULT_EXIST) {
            OSReport("Can't Create temp File with Error.");
            return (s16)result;
        }
        ++attempt;
    } while (result != CARD_RESULT_READY && attempt < 0x80);
    if (attempt < 0x80) {
        destinationFileNo = sThread->destinationFile.fileNo;
    } else {
        destinationFileNo = CARD_RESULT_FATAL_ERROR;
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

    if (result < CARD_RESULT_READY) {
        reportCardThreadError(slot, command, result);
        goto finish;
    }

    commonSectorSize = 0;
    result = CARDGetSectorSize(0, &sourceSectorSize);
    if (result < CARD_RESULT_READY) {
        sectorError = result;
        goto sectorSizeCheck;
    }
    result = CARDGetSectorSize(1, &destinationSectorSize);
    if (result < CARD_RESULT_READY) {
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
    if (sectorError >= CARD_RESULT_READY) {
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
        if (statusResult >= CARD_RESULT_READY) {
            switch (command) {
            case 2:
                if (checkedStatus.permission & CARD_ATTR_NO_COPY) {
                    permissionResult = CARD_RESULT_NOPERM;
                }
                break;
            case 3:
                if (checkedStatus.permission & CARD_ATTR_NO_MOVE) {
                    permissionResult = CARD_RESULT_NOPERM;
                }
                break;
            }
        } else {
            permissionResult = CARDGetResultCode(slot);
        }
        if (permissionResult < CARD_RESULT_READY) {
            reportCardThreadError(slot, command, permissionResult);
            goto finish;
        }
    }

    result = __CARDGetStatusEx(slot, fileNo, &createStatus);
    if (result < CARD_RESULT_READY) {
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
        if (ioResult < CARD_RESULT_READY) {
            goto copyIoFailure;
        }
        stage = 1;
        ioResult = CARDGetSectorSize(slot, &sectorSize);
        if (ioResult < CARD_RESULT_READY) {
            goto copyIoFailure;
        }
        maxBlocks = 0x40000 / sectorSize;
        stage = 2;
        ioResult = CARDFastOpen(slot, fileNo, &sThread->sourceFile);
        if (ioResult < CARD_RESULT_READY) {
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
            if (ioResult < CARD_RESULT_READY) {
                goto copyIoFailure;
            }
            sThread->writePending = 1;
            ioResult = CARDWriteAsync(&sThread->destinationFile,
                                      sThread->transferBuffer, size, offset,
                                      clearCardWritePending);
            if (ioResult < CARD_RESULT_READY) {
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
        if (ioResult < CARD_RESULT_READY) {
            goto copyIoFailure;
        }
        stage = 5;
        ioResult = CARDClose(&sThread->destinationFile);
        if (ioResult >= CARD_RESULT_READY) {
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

    if (result < CARD_RESULT_READY) {
        goto cleanup;
    }
    if (command == 2) {
        copyResult = __CARDGetStatusEx(slot, fileNo, &sourceStatus);
        if (copyResult < CARD_RESULT_READY) {
            OSReport("Can't get status for src file\n");
        } else {
            ++sourceStatus.copyTimes;
            copyResult = __CARDSetStatusEx(slot, fileNo, &sourceStatus);
            if (copyResult < CARD_RESULT_READY) {
                OSReport("Can't set status for src file %d\n", copyResult);
            } else {
                oldTime = sourceStatus.time;
                sourceStatus.time = (u32)(OSGetTime() / (*(u32*)0x800000F8 >> 2));
                copyResult = __CARDSetStatusEx(destinationSlot, destinationFileNo,
                                                    &sourceStatus);
                if (copyResult < CARD_RESULT_READY) {
                    OSReport("Can't set status for dst file (src file copyTimes--)\n");
                    if (copyResult != CARD_RESULT_NOCARD) {
                        --sourceStatus.copyTimes;
                    }
                    sourceStatus.time = oldTime;
                    s32 restoreResult = __CARDSetStatusEx(slot, fileNo, &sourceStatus);
                    if (restoreResult < CARD_RESULT_READY) {
                        OSReport("Can't set status for src file(src file copyTimes--)\n");
                    }
                } else {
                    metadataCopied = TRUE;
                    copyResult = loadCardFileIcons(destinationSlot, destinationFileNo,
                                                       &sourceStatus);
                    if (copyResult < CARD_RESULT_READY) {
                        OSReport("Can't read icon for move dstfile\n");
                    } else {
                        copyResult = 0;
                    }
                }
            }
        }
        result = copyResult;
        if (result < CARD_RESULT_READY) {
            goto cleanup;
        }
    } else if (command == 3) {
        renameAttempt = 0;
        moveStage = 0;
        moveResult = __CARDGetStatusEx(slot, fileNo, &moveStatus);
        if (moveResult >= CARD_RESULT_READY) {
            ++moveStage;
            renamedStatus = moveStatus;
            memset(renamedStatus.company, 0, 2);
            memset(renamedStatus.gameName, 0, 4);
            do {
                memset(renamedStatus.fileName, 0, CARD_FILENAME_MAX);
                sprintf((char*)renamedStatus.fileName, "Broken File%03d", renameAttempt);
                moveResult = __CARDSetStatusEx(slot, fileNo, &renamedStatus);
                if (moveResult < CARD_RESULT_READY && moveResult != CARD_RESULT_EXIST) {
                    goto moveStatusError;
                }
                ++renameAttempt;
            } while (moveResult != CARD_RESULT_READY && renameAttempt < 0x80);
            moveStage = 2;
            moveResult = __CARDSetStatusEx(destinationSlot, destinationFileNo,
                                       &moveStatus);
            if (moveResult < CARD_RESULT_READY) {
                s32 setResult = moveResult;
                if (moveResult == CARD_RESULT_NOCARD) {
                    CARDFastDelete(slot, fileNo);
                    clearCardFileEntry(slot, fileNo);
                } else {
                    s32 restoreResult = __CARDSetStatusEx(slot, fileNo, &moveStatus);
                    if (restoreResult < CARD_RESULT_READY) {
                        OSReport("Can't repair src file - carddir\n");
                    }
                }
                moveResult = setResult;
            } else {
                metadataCopied = TRUE;
                moveStage = 3;
                moveResult = CARDFastDelete(slot, fileNo);
                if (moveResult >= CARD_RESULT_READY) {
                    clearCardFileEntry(slot, fileNo);
                    moveStage = 4;
                    moveResult = __CARDGetStatusEx(destinationSlot,
                                                  destinationFileNo, &moveStatus);
                    if (moveResult >= CARD_RESULT_READY) {
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
        if (moveResult < CARD_RESULT_READY) {
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
    if (result < CARD_RESULT_READY) {
        reportCardThreadError(destinationSlot, command, result);
    } else {
        if (temporaryCreated && !metadataCopied) {
            CARDFastDelete(destinationSlot, destinationFileNo);
        }
        if (metadataCopied) {
            if (__CARDGetStatusEx(destinationSlot, destinationFileNo,
                                  &createStatus) == CARD_RESULT_READY) {
                loadCardFileIcons(destinationSlot, destinationFileNo, &createStatus);
            }
        }
        refreshCardSlotInfo(destinationSlot);
        sendCardSlotState(destinationSlot, 0, fileNo & 0xFF);
    }
    result = CARDGetResultCode(slot);
    if (result < CARD_RESULT_READY) {
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
