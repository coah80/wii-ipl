#include <iplMemoryCardLib.h>
#include <global/decomp/utils.h>

#include <cstring>
#include <cstdio>

#include <revolution/card.h>
#include <private/card.h>

#include <revolution/os.h>

#include <revolution/mem.h>

#include <revolution/dvd.h>

#include <system/iplSystem.h>

namespace ipl {
    namespace memorycard {
        enum {
            MSG_CMD_PROBE = 0,
            MSG_CMD_FORMAT = 1,
            MSG_CMD_COPY = 2,
            MSG_CMD_MOVE = 3,
            MSG_CMD_DELETE = 4,
            MSG_CMD_DETACH = 9,
            MSG_CMD_STATE = 10,
            MSG_CMD_EXIT = 11,
            MSG_CMD_BLOCKS = 12,
        };

        typedef struct CardThreadData {
            /* 0x0000 */ CardState      cardState[2];
            /* 0x0028 */ FileInfo       dirState[2][0x7F];
            /* 0x0C10 */ void*          workBuf[2];
            /* 0x0C18 */ u32            mounted[2];
            /* 0x0C20 */ OSMessageQueue replyQueue;
            /* 0x0C40 */ OSMessageQueue cmdQueue;
            /* 0x0C60 */ OSMessage      replyMsgBuf[0x10];
            /* 0x0CA0 */ OSMessage      cmdMsgBuf[0x10];
            /* 0x0CE0 */ OSThread       thread;
            /* 0x0FF8 */ u8             threadStack[0x8000];
            /* 0x8FF8 */ char           fileNameBuf[0x20];
            /* 0x9018 */ CARDFileInfo   srcFile;
            /* 0x902C */ CARDFileInfo   dstFile;
            /* 0x9040 */ u8*            copyBuf;
            /* 0x9044 */ IconState      iconState[2][0x7F];
            /* 0xCFC4 */ u8*            iconDataPtr[2][0x7F];
            /* 0xD3BC */ char*          commentPtr[2][0x7F];
            /* 0xD7B4 */ u32            unk_D7B4[3];
            /* 0xD7C0 */ u8             commentTmp[0x400];
            /* 0xDBC0 */ u8*            dirFileBuf;
            /* 0xDBC4 */ s32            sendCmd;
            /* 0xDBC8 */ s32            lastError;
            /* 0xDBCC */ s32            cmdResult;
            /* 0xDBD0 */ u32            blockInfoDone;
            /* 0xDBD4 */ u32            scanDone;
            /* 0xDBD8 */ u32            writePending;
            /* 0xDBDC */ u8             srcSlot;
            /* 0xDBDD */ u8             threadValid;
            /* 0xDBDE */ u8             replyStatus;
            /* 0xDBDF */ u8             stopSent;
        } CardThreadData;  // 0xDBE0

        MEMAllocator sAllocator_;

        static CardThreadData* sThread;
        u32 sUnkFlag;

        extern "C" s32 CardSequence_813D233C(s32 result);
        extern "C" BOOL   CardSequence_813D205C(u8 slot);
        extern "C" void CardSequence_813D222C(u8 slot);
        extern "C" void CardSequence_813D2A74(u8 slot, s16 fileNo);
        extern "C" void CardSequence_813D2B40(u8 slot);
        extern "C" void* CardSequence_813D2C8C(void* arg);
        extern "C" void CardSequence_813D3140();
        extern "C" s32 CardSequence_813D320C(u8 slot, s32 result);
        extern "C" s32 CardSequence_813D32A8(u8 slot, s32 cmd, s32 result);
        extern "C" void CardSequence_813D3380(u8 slot, s32 cmd, u8 status) NO_INLINE;
        extern "C" void CardSequence_813D33D8(u8 slot);
        extern "C" s32 CardSequence_813D3424(u8 slot, s16 fileNo, CARDDir* dir);
        extern "C" void CardSequence_813D3C24(s32 chan, s32 result);
        extern "C" s32 CardSequence_813D3C38(u8 slot, s16 fileNo);
        extern "C" void CardSequence_813D3D14(u8 slot, s16 fileNo, s32 cmd);

        FileInfo* getCardDirState() {
            return &sThread->dirState[0][0];
        }

        CardState* getCardSlotState() {
            return sThread->cardState;
        }

        long getCardLastSrcSlot() {
            return sThread->srcSlot;
        }

        long getCardLastSendCmd() {
            return sThread->sendCmd;
        }

        long getCardLastCMDFCmdResult() {
            return sThread->cmdResult;
        }

        extern "C" BOOL CardSequence_813D205C(u8 slot) {
            sThread->srcSlot = slot;
            sThread->sendCmd = MSG_CMD_DETACH;
            sThread->lastError = -0x15;
            return OSSendMessage(&sThread->cmdQueue, (OSMessage)((slot << 16) | MSG_CMD_DETACH), 0);
        }

        void sendCardFormatCmd(u8 slot) {
            sThread->srcSlot = slot;
            sThread->sendCmd = MSG_CMD_FORMAT;
            sThread->lastError = -0x15;
            sThread->cmdResult = -0x15;
            OSSendMessage(&sThread->cmdQueue, (OSMessage)((slot << 16) | MSG_CMD_FORMAT), 0);
        }

        void sendCardCopyCmd(u8 slot, s16 fileNo) {
            u32 msg = (fileNo << 24) | ((slot & 1) << 16);
            msg |= MSG_CMD_COPY;
            sThread->srcSlot = slot;
            sThread->sendCmd = MSG_CMD_COPY;
            sThread->lastError = -0x15;
            sThread->cmdResult = -0x15;
            OSSendMessage(&sThread->cmdQueue, (OSMessage)msg, 0);
        }

        void sendCardMoveCmd(u8 slot, s16 fileNo) {
            u32 msg = (fileNo << 24) | ((slot & 1) << 16);
            msg |= MSG_CMD_MOVE;
            sThread->srcSlot = slot;
            sThread->sendCmd = MSG_CMD_MOVE;
            sThread->lastError = -0x15;
            sThread->cmdResult = -0x15;
            OSSendMessage(&sThread->cmdQueue, (OSMessage)msg, 0);
        }

        void sendCardDeleteCmd(u8 slot, s16 fileNo) {
            u32 msg = (fileNo << 24) | ((slot & 1) << 16);
            msg |= MSG_CMD_DELETE;
            sThread->srcSlot = slot;
            sThread->sendCmd = MSG_CMD_DELETE;
            sThread->lastError = -0x15;
            sThread->cmdResult = -0x15;
            OSSendMessage(&sThread->cmdQueue, (OSMessage)msg, 0);
        }

        void sendCardThreadStopCmd() __attribute__((never_inline)) {
            CardSequence_813D205C(0);
            CardSequence_813D205C(1);
            OSSendMessage(&sThread->cmdQueue, (OSMessage)MSG_CMD_EXIT, 0);
        }

        extern "C" void CardSequence_813D222C(u8 slot) {
            s32 probed;

            if (sThread->threadValid != 1) {
                return;
            }
            probed = CARDProbe(slot);
            if (probed) {
                if (sThread->cardState[slot].state < 2) {
                    sThread->srcSlot = slot;
                    sThread->sendCmd = 0;
                    sThread->lastError = -0x15;
                    if (OSSendMessage(&sThread->cmdQueue, (OSMessage)((slot << 16) | MSG_CMD_PROBE), 0)) {
                        sThread->cardState[slot].state = 3;
                        sThread->cardState[slot].changed = 0;
                    }
                    return;
                }
            }
            if (!probed && sThread->cardState[slot].state > 2) {
                if (CardSequence_813D205C(slot)) {
                    sThread->cardState[slot].changed = 0;
                }
            }
        }

        extern "C" s32 CardSequence_813D233C(s32 result) {
            switch (result) {
            case 0:
                return 0;
            case -2:
                return -0x1C;
            case -3:
                return -0x1C;
            case -4:
                return -0x1C;
            case -5:
                return -0x1C;
            case -6:
                return -0x1C;
            case -7:
                return -0x18;
            case -8:
                return -0x19;
            case -9:
                return -0x19;
            case -0xA:
                return -0x1C;
            case -0xB:
                return -0x1C;
            case -0xC:
                return -0x1C;
            case -0xD:
                return -0x1C;
            case -0x1B:
                return -0x1B;
            default:
                return -0x1C;
            }
        }

        void probeCard() {
            OSMessage msg;

            CardSequence_813D222C(0);
            CardSequence_813D222C(1);

            while (OSReceiveMessage(&sThread->replyQueue, &msg, 0)) {
                s16 slot = (s16)(((u32)msg >> 16) & 1);

                if ((s8)((u32)msg & 0xFF) == MSG_CMD_STATE || (s8)((u32)msg & 0xFF) == MSG_CMD_EXIT) {
                    sThread->threadValid = (u8)(((u32)msg >> 8) & 0xFF);
                    continue;
                }
                if ((s8)((u32)msg & 0xFF) == MSG_CMD_BLOCKS) {
                    sThread->blockInfoDone = 1;
                    sThread->scanDone = 1;
                    continue;
                }

                switch ((s8)(((u32)msg >> 8) & 0xFF)) {
                case 0:
                case -0x1B:
                case -7:
                    OSReport("ready or exit\n");
                    sThread->cardState[slot].state = 4;
                    break;
                case -9:
                case -8:
                    OSReport("Card hasn't enough space\n");
                    sThread->cardState[slot].state = 4;
                    break;
                case -2:
                    OSReport("Wrong Device\n");
                    sThread->cardState[slot].state = 5;
                    break;
                case -6:
                    OSReport("Broken Card\n");
                    sThread->cardState[slot].state = 6;
                    break;
                case -0xD:
                    OSReport("Other Language\n");
                    sThread->cardState[slot].state = 8;
                    break;
                case -3:
                    OSReport("Detach Card\n");
                    sThread->cardState[slot].state = 0;
                    break;
                default:
                    OSReport("Other Error\n");
                    sThread->cardState[slot].state = 10;
                    break;
                }

                sThread->lastError = CardSequence_813D233C((s8)(((u32)msg >> 8) & 0xFF));

                if ((s8)((u32)msg & 0xFF) != 0 && (s8)((u32)msg & 0xFF) != MSG_CMD_DETACH) {
                    sThread->cmdResult = CardSequence_813D233C((s8)(((u32)msg >> 8) & 0xFF));
                    if (sThread->srcSlot != (s16)(((u32)msg >> 16) & 1)) {
                        sThread->replyStatus = (u8)((u32)msg >> 24);
                    }
                }

                OSReport("set slot state : ErrorCode: %d\n", sThread->lastError);
                sThread->cardState[slot].changed = 1;
                sThread->scanDone = 0;
            }
        }

        void initCardThread() {
            if (sThread == NULL) {
                u32           size = System::createMem1AppHeap()->getAllocatableSize(4);
                void*         buf  = System::createMem1AppHeap()->alloc(size, 4);
                MEMHeapHandle hh   = MEMCreateExpHeapEx(buf, size, 0);
                MEMInitAllocatorForExpHeap(&sAllocator_, hh, 0x20);
                sAllocator_.heapParam2 = (u32)buf;
                OSReport("HEAP CREATE: %p %d\n", buf, size);

                sThread = (CardThreadData*)MEMAllocFromAllocator(&sAllocator_, sizeof(CardThreadData));
                memset(sThread, 0, sizeof(CardThreadData));

                sThread->iconDataPtr[0][0] = (u8*)MEMAllocFromAllocator(&sAllocator_, 0x594C00);
                sThread->commentPtr[0][0]  = (char*)MEMAllocFromAllocator(&sAllocator_, 0x3F80);
                sThread->dirFileBuf        = (u8*)MEMAllocFromAllocator(&sAllocator_, 0x5A00);
                sThread->copyBuf           = (u8*)MEMAllocFromAllocator(&sAllocator_, 0x40000);
                sThread->workBuf[0]        = MEMAllocFromAllocator(&sAllocator_, 0xA000);
                sThread->workBuf[1]        = MEMAllocFromAllocator(&sAllocator_, 0xA000);
            }

            for (int i = 0; i < 0x7F; i++) {
                sThread->iconDataPtr[0][i] = sThread->iconDataPtr[0][0] + i * 0x5A00;
                sThread->commentPtr[0][i]  = sThread->commentPtr[0][0] + i * 0x40;
            }
            for (int i = 0; i < 0x7F; i++) {
                sThread->iconDataPtr[1][i] = sThread->iconDataPtr[0][0] + (i + 0x7F) * 0x5A00;
                sThread->commentPtr[1][i]  = sThread->commentPtr[0][0] + (i + 0x7F) * 0x40;
            }

            OSInitMessageQueue(&sThread->replyQueue, sThread->replyMsgBuf, 0x10);
            OSInitMessageQueue(&sThread->cmdQueue, sThread->cmdMsgBuf, 0x10);
            OSCreateThread(&sThread->thread, CardSequence_813D2C8C, NULL,
                           sThread->threadStack + sizeof(sThread->threadStack),
                           sizeof(sThread->threadStack), 0x11, 0);
            OSResumeThread(&sThread->thread);

            OSSendMessage(&sThread->cmdQueue, (OSMessage)MSG_CMD_STATE, 0);
            OSReport("initCardThread successfully\n");
        }

        bool shutdownCardThread() {
            bool ret = true;

            if (sThread != NULL) {
                ret = false;
                if (sThread->stopSent == 0) {
                    sendCardThreadStopCmd();
                    sThread->stopSent = 1;
                }
                if (OSIsThreadTerminated(&sThread->thread)) {
                    void* val;
                    OSJoinThread(&sThread->thread, &val);

                    MEMFreeToAllocator(&sAllocator_, sThread->workBuf[1]);
                    MEMFreeToAllocator(&sAllocator_, sThread->workBuf[0]);
                    MEMFreeToAllocator(&sAllocator_, sThread->copyBuf);
                    MEMFreeToAllocator(&sAllocator_, sThread->dirFileBuf);
                    MEMFreeToAllocator(&sAllocator_, sThread->iconDataPtr[0][0]);
                    MEMFreeToAllocator(&sAllocator_, sThread->commentPtr[0][0]);
                    MEMFreeToAllocator(&sAllocator_, sThread);
                    sThread = NULL;

                    MEMDestroyExpHeap((MEMHeapHandle)sAllocator_.heap);
                    System::createMem1AppHeap()->free((void*)sAllocator_.heapParam2);
                    System::destroyMem1AppHeap();
                    OSReport("HEAP DESTROY\n");
                    ret = true;
                }
            }

            return ret;
        }

        IconState* getIconStateArray() {
            return &sThread->iconState[0][0];
        }

        const char* getIconComment(u8 slot, s16 fileNo) {
            return sThread->commentPtr[slot][fileNo];
        }

        extern "C" void CardSequence_813D2A74(u8 slot, s16 fileNo) {
            int intr = OSDisableInterrupts();
            sThread->dirState[slot][fileNo].fileNo = 0;
            sThread->dirState[slot][fileNo].size = 0;
            sThread->dirState[slot][fileNo].canCopy = 1;
            sThread->dirState[slot][fileNo].canMove = 1;
            sThread->dirState[slot][fileNo].unk_0x06 = 0;
            sThread->iconState[slot][fileNo].unk_0x01 = 0;
            sThread->iconState[slot][fileNo].bannerEnable = 0;
            OSRestoreInterrupts(intr);
        }

        extern "C" void CardSequence_813D2B40(u8 slot) {
            u32 sectorSize;
            s32 bytes;
            s32 files;
            u16 memSize;
            s32 result;

            result = CARDGetMemSize(slot, &memSize);
            if (result < 0) {
                OSReport("Get Memsize Error-%d: %d: %d\n", slot, result, memSize);
            }

            result = CARDGetSectorSize(slot, &sectorSize);
            if (result < 0) {
                OSReport("Get Sector Error- %d: %d\n", result, sectorSize);
            }

            result = CARDFreeBlocks(slot, &bytes, &files);
            if (result < 0) {
                OSReport("Get FreeBlocks Error- %d %d\n", result, bytes);
            }

            if (CARDGetResultCode(slot) >= 0) {
                int intr = OSDisableInterrupts();
                sThread->cardState[slot].unk_0x0C = (u16)((memSize << 17) / sectorSize - 5);
                sThread->cardState[slot].key = sectorSize;
                sThread->cardState[slot].unk_0x0E = (u16)files;
                sThread->cardState[slot].freeBlocks = (u16)(bytes / sectorSize);
                OSRestoreInterrupts(intr);
                OSReport("%d:%dbytes sectorsize , %d blocks , %d freeEntry\n", slot,
                         sThread->cardState[slot].key, sThread->cardState[slot].freeBlocks,
                         sThread->cardState[slot].unk_0x0E);
            }
        }

        extern "C" void* CardSequence_813D2C8C(void* arg) {
            OSMessage msg;
            u8        zero[8];
            int       done = 0;
            u8        valid = 1;

            sThread->mounted[0] = 0;
            sThread->mounted[1] = 0;

            while (done == 0) {
                OSReceiveMessage(&sThread->cmdQueue, &msg, OS_MESSAGE_BLOCK);
                OSReport("CARD THREAD: Message received %d\n", (s8)((u32)msg & 0xFF));

                if (valid == 1) {
                    u8 cmd = (u8)((u32)msg & 0xFF);
                    switch ((s8)cmd) {
                    case MSG_CMD_STATE:
                        OSReport("card thread valid state changed:%d\n", 1);
                        OSSendMessage(&sThread->replyQueue, (OSMessage)((valid << 8) | cmd), 1);
                        valid = 1;
                        break;
                    case MSG_CMD_EXIT:
                        done = 1;
                        break;
                    case MSG_CMD_PROBE: {
                        char    name[CARD_FILENAME_MAX + 1];
                        CARDDir dir2;
                        CARDDir dir;
                        u8  slot   = (u8)(((u32)msg >> 16) & 1);
                        s32 result = CARDMount(slot, sThread->workBuf[slot], 0);
                        if (result < 0) {
                            if (CardSequence_813D320C(slot, result) != 0) {
                                goto scan;
                            }
                            goto next;
                        }
                        else {
                            result = CARDCheck(slot);
                            if (result < 0) {
                                goto mount_error;
                            }
                        }
                    scan:

                        CardSequence_813D33D8(slot);
                        for (s16 i = 0; i < 0x7F; i++) {
                            result = __CARDGetStatusEx(slot, i, &dir);
                            if (result < 0) {
                                if (CardSequence_813D320C(slot, result) != 0) {
                                    continue;
                                }
                                goto next;
                            }
                            else {
                                s32 isBrokenFile;
                                zero[0] = 0;
                                zero[1] = 0;
                                zero[2] = 0;
                                zero[3] = 0;
                                zero[4] = 0;
                                zero[5] = 0;
                                isBrokenFile = strncmp((const char*)dir.fileName, "Broken File", 0xB) == 0 &&
                                               memcmp(dir.gameName, zero + 2, 4) == 0 &&
                                               memcmp(dir.company, zero, 2) == 0;
                                if (isBrokenFile) {
                                    result = CARDFastDelete(slot, i);
                                    if (result < 0) {
                                        goto mount_error;
                                    }
                                }
                                else {
                                    result = CardSequence_813D3424(slot, i, &dir);
                                    if (result < 0) {
                                        goto mount_error;
                                    }
                                }
                            }
                        }

                        CardSequence_813D2B40(slot);
                        sThread->mounted[slot] = 1;
                        CardSequence_813D3380(slot, 0, 0);
                        OSReport("Slot %c\n", (s8)("AB"[slot]));

                        for (u16 i = 0; i < 0x7F; i++) {
                            if (__CARDGetStatusEx(slot, i, &dir2) == 0) {
                                memcpy(name, dir2.fileName, CARD_FILENAME_MAX);
                                name[CARD_FILENAME_MAX] = 0;
                                OSReport("%d - %s: %d blocks\n", i, name, dir2.length);
                            }
                        }
                        break;
                    mount_error:
                        OSReport("MountError\n");
                        CardSequence_813D32A8(slot, 0, result);
                        break;
                    }
                    case MSG_CMD_DETACH:
                        CardSequence_813D32A8((u8)(((u32)msg >> 16) & 1), MSG_CMD_DETACH, -3);
                        break;
                    case MSG_CMD_FORMAT: {
                        u8  slot   = (u8)(((u32)msg >> 16) & 1);
                        s32 result = CARDFormat(slot);
                        if (result < 0) {
                            CardSequence_813D32A8(slot, MSG_CMD_FORMAT, result);
                        }
                        else {
                            sThread->mounted[slot & 1] = 1;
                            CardSequence_813D2B40(slot);
                            CardSequence_813D3380(slot, MSG_CMD_FORMAT, 0);
                        }
                        break;
                    }
                    case MSG_CMD_COPY:
                        CardSequence_813D3D14((u8)(((u32)msg >> 16) & 1), (s16)((u32)msg >> 24), MSG_CMD_COPY);
                        break;
                    case MSG_CMD_MOVE:
                        CardSequence_813D3D14((u8)(((u32)msg >> 16) & 1), (s16)((u32)msg >> 24), MSG_CMD_MOVE);
                        break;
                    case MSG_CMD_DELETE: {
                        u8  slot   = (u8)(((u32)msg >> 16) & 1);
                        s16 fileNo = (s16)((u32)msg >> 24);
                        s32 result = CARDFastDelete(slot, fileNo);
                        if (result < 0) {
                            CardSequence_813D32A8(slot, MSG_CMD_DELETE, result);
                        }
                        else {
                            CardSequence_813D2A74(slot, fileNo);
                            CardSequence_813D2B40(slot);
                            CardSequence_813D3380(slot, MSG_CMD_DELETE, (u8)fileNo);
                        }
                        break;
                    }
                    case MSG_CMD_BLOCKS: {
                        for (s32 s = 0; s < 2; s++) {
                            if (sThread->mounted[s] != 0) {
                                s32 used = 0;
                                for (s32 i = 0; i < 0x7F; i++) {
                                    CARDDir dir;
                                    s32     result = __CARDGetStatusEx(s, i, &dir);
                                    if (result < 0 && result != -4) {
                                        used = -1;
                                        break;
                                    }
                                    if (result == 0 &&
                                        memcmp(dir.gameName, (void*)0x80000000, 4) == 0 &&
                                        memcmp(dir.company, (void*)0x80000004, 2) == 0) {
                                        used += dir.length;
                                    }
                                }
                                sThread->cardState[s].unk_0x12 = used;
                            }
                        }
                        CardSequence_813D3380(0, MSG_CMD_BLOCKS, 0);
                        break;
                    }
                    default:
                        break;
                    }
                }
            next:;
            }
            return NULL;
        }

        extern "C" void CardSequence_813D3140() {
            for (s32 slot = 0; slot < 2; slot++) {
                for (s32 fileNo = 0; fileNo < 0x7F; fileNo++) {
                    sThread->dirState[slot][fileNo].unk_0x06 = 0;
                    if (sThread->mounted[slot] == 0 || sThread->mounted[slot ^ 1] == 0)
                        continue;
                    if (CardSequence_813D3C38((u8)slot, (s16)fileNo) >= 0)
                        continue;
                    sThread->dirState[slot][fileNo].unk_0x06 = 1;
                }
            }
        }

        extern "C" s32 CardSequence_813D320C(u8 slot, s32 result) {
            if (result == -5) {
                goto reply;
            }
            if (result >= -5) {
                goto upper;
            }
            if (result >= -6) {
                goto check;
            }
            goto reply;
        upper:
            if (result >= -3) {
                goto reply;
            }
            return 1;
        check:
            result = CARDCheck(slot);
            if (result < 0) {
                return CardSequence_813D32A8(slot, 0, result);
            }
            OSReport("CardThread:Broken Card Repaired\n");
            return 1;
        reply:
            return CardSequence_813D32A8(slot, 0, result);
        }

        extern "C" s32 CardSequence_813D32A8(u8 slot, s32 cmd, s32 result) {
            if (result != -7 && result != -0x1B && result != -8 && result != -9) {
                CardSequence_813D33D8(slot);
                if (result != -6 && result != -0xD) {
                    OSReport("DEBUG: UnmountCard %d \n", slot);
                    CARDUnmount(slot);
                    sThread->mounted[slot] = 0;
                }
            }
            OSReport("DEBUG: CardThread error %d %d\n", cmd, result);
            CardSequence_813D3140();
            OSSendMessage(&sThread->replyQueue,
                          (OSMessage)(((slot & 1) << 16) | ((result & 0xFF) << 8) | (cmd & 0xFF)), 1);
            return 0;
        }

        extern "C" void CardSequence_813D3380(u8 slot, s32 cmd, u8 status) NO_INLINE {
            CardSequence_813D3140();
            OSSendMessage(&sThread->replyQueue,
                          (OSMessage)(((status & 0xFF) << 24) | ((slot & 1) << 16) | (cmd & 0xFF)), 1);
        }

        extern "C" void CardSequence_813D33D8(u8 slot) {
            for (s16 i = 0; i < 0x7F; i++) {
                CardSequence_813D2A74(slot, i);
            }
        }

        extern "C" s32 CardSequence_813D3424(u8 slot, s16 fileNo, CARDDir* dir) {
            CARDFileInfo file;
            s32          result;
            u32          dataSize;
            u32          iconBytes;
            u32          iconAddrBase;
            u32          iconAddrOff;
            u32          fileSize;
            s32          readLen;
            s32          commentBase;
            s32          commentOff;
            s32          tlut;

            result = CARDFastOpen(slot, fileNo, &file);
            if (result < 0) {
                return result;
            }

            iconAddrBase = dir->iconAddr & ~0x1FF;
            iconAddrOff = dir->iconAddr - iconAddrBase;

            dataSize = 0;
            switch (dir->bannerFormat & CARD_STAT_BANNER_MASK) {
            case CARD_STAT_BANNER_C8:
                sThread->iconState[slot][fileNo].bannerEnable = 1;
                sThread->iconState[slot][fileNo].bannerType = 9;
                sThread->iconState[slot][fileNo].bannerOffset = (u32)(sThread->iconDataPtr[slot][fileNo] - (u8*)&sThread->iconState[slot][fileNo]);
                sThread->iconState[slot][fileNo].bannerTlutOffset = sThread->iconState[slot][fileNo].bannerOffset + 0xC00;
                sThread->iconState[slot][fileNo].iconOffset[0] = sThread->iconState[slot][fileNo].bannerTlutOffset + 0x200;
                dataSize = 0xE00;
                break;
            case CARD_STAT_BANNER_RGB5A3:
                sThread->iconState[slot][fileNo].bannerEnable = 1;
                sThread->iconState[slot][fileNo].bannerType = 5;
                sThread->iconState[slot][fileNo].bannerOffset = (u32)(sThread->iconDataPtr[slot][fileNo] - (u8*)&sThread->iconState[slot][fileNo]);
                sThread->iconState[slot][fileNo].iconOffset[0] = sThread->iconState[slot][fileNo].bannerOffset + 0x1800;
                dataSize = 0x1800;
                break;
            default:
                sThread->iconState[slot][fileNo].bannerEnable = 0;
                sThread->iconState[slot][fileNo].bannerType = 0;
                sThread->iconState[slot][fileNo].iconOffset[0] = (u32)(sThread->iconDataPtr[slot][fileNo] - (u8*)&sThread->iconState[slot][fileNo]);
                break;
            }

            sThread->iconState[slot][fileNo].unk_0x02 = 0;
            tlut = 0;
            iconBytes = 0;
            sThread->iconState[slot][fileNo].anmMax = 0;
            sThread->iconState[slot][fileNo].anmFrameBits = dir->iconSpeed;
            sThread->iconState[slot][fileNo].unk_0x06 = (dir->iconSpeed & 3) << 2;

            for (int i = 0; i < CARD_ICON_MAX; i++) {
                if ((dir->iconSpeed >> (i * 2)) & 3) {
                    sThread->iconState[slot][fileNo].anmMax += (((dir->iconSpeed >> (i * 2)) & 3) << 2);
                }
                else {
                    sThread->iconState[slot][fileNo].unk_0x07 = (((dir->iconSpeed >> ((i - 1) * 2)) & 3) << 2);
                    goto icons_done;
                }
            }
            sThread->iconState[slot][fileNo].unk_0x07 = ((dir->iconSpeed >> 14) & 3) << 2;
        icons_done:;

            if ((dir->iconSpeed & 3) == 0 || (dir->iconFormat & 3) == 0) {
                sThread->iconState[slot][fileNo].unk_0x01 = 0;
            }
            else {
                for (int i = 0; i < CARD_ICON_MAX; i++) {
                    s32 size;
                    if ((dir->iconSpeed >> (i * 2)) & 3) {
                    switch ((dir->iconFormat >> (i * 2)) & 3) {
                    case CARD_STAT_ICON_C8:
                        sThread->iconState[slot][fileNo].iconFmt[i] = 9;
                        size = 0x400;
                        tlut = 1;
                        break;
                    case CARD_STAT_ICON_RGB5A3:
                        sThread->iconState[slot][fileNo].iconFmt[i] = 5;
                        size = 0x800;
                        break;
                    case 0:
                        sThread->iconState[slot][fileNo].iconFmt[i] = sThread->iconState[slot][fileNo].iconFmt[i - 1];
                        size = 0;
                        break;
                    }
                    if (i < CARD_ICON_MAX - 1) {
                        sThread->iconState[slot][fileNo].iconOffset[i + 1] = sThread->iconState[slot][fileNo].iconOffset[i] + size;
                    }
                    else {
                        sThread->iconState[slot][fileNo].iconTlutOffset = sThread->iconState[slot][fileNo].iconOffset[i] + size;
                    }
                    iconBytes += size;
                    sThread->iconState[slot][fileNo].unk_0x02++;
                    }
                    else {
                        sThread->iconState[slot][fileNo].iconTlutOffset = sThread->iconState[slot][fileNo].iconOffset[i];
                        goto icons_tail;
                    }
                }
            icons_tail:
                if (tlut) {
                    iconBytes += 0x200;
                }
                sThread->iconState[slot][fileNo].unk_0x01 = 1;
                sThread->iconState[slot][fileNo].anmType = dir->bannerFormat & 4;
                sThread->iconState[slot][fileNo].anmDelta = 1;
            }

            {
                u32 sectorSize;
                s32 total = dataSize + iconBytes;
                readLen = ((total + iconAddrOff + 0x1FF) & ~0x1FF);
                result = CARDGetSectorSize(slot, &sectorSize);
                if (result < 0) {
                    sThread->iconState[slot][fileNo].bannerEnable = 0;
                    sThread->iconState[slot][fileNo].unk_0x01 = 0;
                    result = 0;
                }
                else {
                    fileSize = dir->length * sectorSize;
                    if (iconAddrBase > fileSize) {
                        sThread->iconState[slot][fileNo].bannerEnable = 0;
                        sThread->iconState[slot][fileNo].unk_0x01 = 0;
                        result = 0;
                    }
                    else if (iconAddrBase + readLen > fileSize) {
                        sThread->iconState[slot][fileNo].bannerEnable = 0;
                        sThread->iconState[slot][fileNo].unk_0x01 = 0;
                        result = 0;
                    }
                    else if (total > 0) {
                        result = CARDRead(&file, sThread->dirFileBuf, readLen, iconAddrBase);
                        if (result >= 0) {
                            memcpy(sThread->iconDataPtr[slot][fileNo], sThread->dirFileBuf + iconAddrOff, total);
                            DCStoreRange(sThread->iconDataPtr[slot][fileNo], readLen);
                            result = 0;
                        }
                    }
                    else {
                        result = 0;
                    }
                }
            }
            if (result < 0) {
                return result;
            }

            {
                u32 sectorSize;
                u32 caddr = dir->commentAddr;
                commentBase = caddr & ~0x1FF;
                commentOff = caddr - commentBase;
                readLen = ((caddr + 0x23F) & ~0x1FF) - commentBase;
                result = CARDGetSectorSize(slot, &sectorSize);
                if (result >= 0) {
                    fileSize = dir->length * sectorSize;
                    if (commentBase < 0 || commentBase > fileSize) {
                        result = 0;
                    }
                    else if (commentBase + readLen < 0 || commentBase + readLen > fileSize) {
                        result = 0;
                    }
                    else {
                        result = CARDRead(&file, sThread->commentTmp, readLen, commentBase);
                        if (result >= 0) {
                            memset(sThread->commentPtr[slot][fileNo], 0, 0x40);
                            memcpy(sThread->commentPtr[slot][fileNo], sThread->commentTmp + commentOff, 0x40);
                            result = 0;
                        }
                    }
                }
                if (result < 0) {
                    memset(sThread->commentPtr[slot][fileNo], 0, 0x40);
                    return result;
                }
            }

            result = CARDClose(&file);
            if (result < 0) {
                return result;
            }

            sThread->dirState[slot][fileNo].fileNo = 1;
            sThread->dirState[slot][fileNo].size = dir->length;
            sThread->dirState[slot][fileNo].key = dir->time;
            sThread->dirState[slot][fileNo].canCopy = ((dir->permission >> 3) & 1) ^ 1;
            sThread->dirState[slot][fileNo].canMove = ((dir->permission >> 4) & 1) ^ 1;
            return 0;
        }

        extern "C" void CardSequence_813D3C24(s32 chan, s32 result) {
            sThread->writePending = 0;
        }

        extern "C" s32 CardSequence_813D3C38(u8 slot, s16 fileNo) {
            CARDDir dir;
            CARDDir otherDir;
            s32     result;

            result = __CARDGetStatusEx(slot, fileNo, &dir);
            if (result < 0) {
                return result;
            }

            slot ^= 1;
            for (int i = 0; i < 0x7F; i++) {
                result = __CARDGetStatusEx(slot, i, &otherDir);
                if (result < 0) {
                    if (result != -4) {
                        return result;
                    }
                }
                if (result != 0) {
                    continue;
                }
                if (memcmp(dir.gameName, otherDir.gameName, 4) == 0 &&
                    memcmp(dir.company, otherDir.company, 2) == 0 &&
                    memcmp(dir.fileName, otherDir.fileName, CARD_FILENAME_MAX) == 0) {
                    return -7;
                }
            }
            return 0;
        }

        extern "C" void CardSequence_813D3D14(u8 slot, s16 fileNo, s32 cmd) {
            s32     result;
            s32     dstFileNo = -1;
            s32     srcOpened = 0;
            s32     srcKept = 0;
            CARDDir dir2;
            CARDDir dir;
            CARDDir dir3;
            CARDDir dir4;
            CARDDir marker;
            CARDDir dir5;
            u32     sectorSize1, sectorSize0;
            u32     sectorSize;
            u32     sectorSize2;
            s32     stage;
            s32     err;
            BOOL    cancelled;
            u32     per;

            result = CardSequence_813D3C38(slot, fileNo);
            if (result < 0) {
                CardSequence_813D32A8(slot, cmd, result);
                return;
            }

            sectorSize = 0;
            result = CARDGetSectorSize(0, &sectorSize0);
            if (result < 0) {
                err = result;
            }
            else {
                result = CARDGetSectorSize(1, &sectorSize1);
                if (result < 0) {
                    err = result;
                }
                else if (sectorSize0 != sectorSize1) {
                    err = -0x1B;
                }
                else {
                    sectorSize = sectorSize0;
                    err = 0;
                }
            }
            if (err < 0) {
                CardSequence_813D32A8(slot, cmd, err);
                return;
            }

            err = 0;
            result = __CARDGetStatusEx(slot, fileNo, &dir);
            if (result >= 0) {
                switch (cmd) {
                case MSG_CMD_COPY:
                    if (dir.permission & 8) {
                        err = -0xA;
                    }
                    break;
                case MSG_CMD_MOVE:
                    if (dir.permission & 0x10) {
                        err = -0xA;
                    }
                    break;
                }
            }
            else {
                err = CARDGetResultCode(slot);
            }
            if (err < 0) {
                CardSequence_813D32A8(slot, cmd, err);
                return;
            }

            result = __CARDGetStatusEx(slot, fileNo, &dir2);
            if (result < 0) {
                goto cleanup;
            }

            {
                u32 blocks = dir2.length * sectorSize;
                int  i;
                for (i = 0; ; ) {
                    sprintf(sThread->fileNameBuf, "Broken File%03d", i);
                    result = CARDCreate((u8)(slot ^ 1), sThread->fileNameBuf, blocks, &sThread->dstFile);
                    if (result < 0 && result != -7) {
                        OSReport("Can't Create temp File with Error.");
                        dstFileNo = (s16)result;
                        goto have_file;
                    }
                    i++;
                    if (result != 0 && i < 0x80) {
                        continue;
                    }
                    break;
                }
                if (i < 0x80) {
                    dstFileNo = (s16)sThread->dstFile.fileNo;
                }
                else {
                    dstFileNo = -0x80;
                }
            }
        have_file:
            if (dstFileNo < 0) {
                CardSequence_813D32A8((u8)(slot ^ 1), cmd, dstFileNo);
                return;
            }

            srcOpened = 1;
            stage = 0;
            cancelled = FALSE;
            result = __CARDGetStatusEx(slot, fileNo, &dir3);
            if (result >= 0) {
                stage = 1;
                result = CARDGetSectorSize(slot, &sectorSize2);
            }
            if (result >= 0) {
                stage = 2;
                per = 0x40000 / sectorSize2;
                result = CARDFastOpen(slot, fileNo, &sThread->srcFile);
            }
            if (result >= 0) {
                stage = 3;
                {
                    s32  offset = 0;

                    while (offset < dir3.length) {
                        u32 count = dir3.length - offset;
                        u32 bytes;
                        if (count > per) {
                            count = per;
                        }
                        bytes = count * sectorSize2;
                        {
                            u32 addr = offset * sectorSize2;
                            result = CARDRead(&sThread->srcFile, sThread->copyBuf, bytes, addr);
                            if (result < 0) {
                                break;
                            }
                            sThread->writePending = 1;
                            result = CARDWriteAsync(&sThread->dstFile, sThread->copyBuf, bytes,
                                                    addr, CardSequence_813D3C24);
                        }
                        if (result < 0) {
                            break;
                        }
                        while (sThread->writePending != 0) {
                            if (CARDProbe(slot) == 0 && !cancelled) {
                                CARDCancel(&sThread->dstFile);
                                cancelled = TRUE;
                            }
                        }
                        offset += per;
                    }
                }
            }
            stage = 4;
            result = CARDClose(&sThread->srcFile);
            if (result >= 0) {
                stage = 5;
                result = CARDClose(&sThread->dstFile);
            }
            if (result >= 0) {
                result = 0;
            }
            else {
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
                CARDFastDelete((u8)(slot ^ 1), sThread->dstFile.fileNo);
            }

            if (result < 0) {
                goto cleanup;
            }

            if (cmd == MSG_CMD_COPY) {
                u32 savedTime;

                result = __CARDGetStatusEx(slot, fileNo, &dir4);
                if (result < 0) {
                    OSReport("Can't get status for src file\n");
                    goto err_tail;
                }
                dir4.copyTimes++;
                result = __CARDSetStatusEx(slot, fileNo, &dir4);
                if (result < 0) {
                    OSReport("Can't set status for src file %d\n", result);
                    goto err_tail;
                }
                savedTime = dir4.time;
                dir4.time = OSGetTime() / (*(u32*)0x800000F8 >> 2);
                result = __CARDSetStatusEx((u8)(slot ^ 1), dstFileNo, &dir4);
                if (result < 0) {
                    OSReport("Can't set status for dst file (src file copyTimes--)\n");
                    if (result != -3) {
                        dir4.copyTimes--;
                    }
                    dir4.time = savedTime;
                    result = __CARDSetStatusEx(slot, fileNo, &dir4);
                    if (result < 0) {
                        OSReport("Can't set status for src file(src file copyTimes--)\n");
                    }
                    goto err_tail;
                }
                srcKept = 1;
                result = CardSequence_813D3424((u8)(slot ^ 1), dstFileNo, &dir4);
                if (result < 0) {
                    OSReport("Can't read icon for move dstfile\n");
                    goto err_tail;
                }
                result = 0;
            err_tail:
                if (result < 0) {
                    goto cleanup;
                }
                goto success;
            }

            if (cmd == MSG_CMD_MOVE) {
                s16 i;

                stage = 0;
                result = __CARDGetStatusEx(slot, fileNo, &dir5);
                if (result < 0) {
                    goto move_err;
                }
                marker = dir5;
                memset(marker.company, 0, 2);
                memset(marker.gameName, 0, 4);
                memset(marker.fileName, 0, CARD_FILENAME_MAX);

                stage = 1;
                for (i = 0; ; ) {
                    sprintf((char*)marker.fileName, "Broken File%03d", i);
                    result = __CARDSetStatusEx(slot, fileNo, &marker);
                    if (result >= 0 || result == -7) {
                        i++;
                        if (result != 0 && i < 0x80) {
                            continue;
                        }
                        break;
                    }
                    goto move_err;
                }

                stage = 2;
                result = __CARDSetStatusEx((u8)(slot ^ 1), dstFileNo, &dir5);
                if (result < 0) {
                    if (result == -3) {
                        CARDFastDelete(slot, fileNo);
                        CardSequence_813D2A74(slot, fileNo);
                        goto move_err;
                    }
                    if (__CARDSetStatusEx(slot, fileNo, &dir5) < 0) {
                        OSReport("Can't repair src file - carddir\n");
                    }
                    goto move_err;
                }

                stage = 3;
                srcKept = 1;
                result = CARDFastDelete(slot, fileNo);
                if (result < 0) {
                    goto move_err;
                }
                CardSequence_813D2A74(slot, fileNo);

                stage = 4;
                result = __CARDGetStatusEx((u8)(slot ^ 1), dstFileNo, &dir5);
                if (result < 0) {
                    goto move_err;
                }

                stage = 5;
                result = CardSequence_813D3424((u8)(slot ^ 1), dstFileNo, &dir5);
                if (result < 0) {
                    goto move_err;
                }
                result = 0;
                goto move_done;

            move_err:
                switch (stage) {
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
            move_done:
                if (result < 0) {
                    goto cleanup;
                }
            }

        success:
            CardSequence_813D2B40(slot);
            CardSequence_813D2B40(slot ^ 1);
            CardSequence_813D3380(slot, 0, (u8)fileNo);
            CardSequence_813D3380((u8)(slot ^ 1), cmd, (u8)dstFileNo);
            return;

        cleanup:
            {
                u8  other = slot ^ 1;
                s32 code = CARDGetResultCode(other);
                if (code < 0) {
                    CardSequence_813D32A8(other, cmd, code);
                }
                else {
                    if (srcOpened && !srcKept) {
                        CARDFastDelete(other, dstFileNo);
                    }
                    if (srcKept) {
                        if (__CARDGetStatusEx(other, dstFileNo, &dir2) == 0) {
                            CardSequence_813D3424(other, dstFileNo, &dir2);
                        }
                    }
                    CardSequence_813D2B40(other);
                    CardSequence_813D3380(other, 0, (u8)fileNo);
                }
            }
            {
                s32 code = CARDGetResultCode(slot);
                if (code < 0) {
                    CardSequence_813D32A8(slot, cmd, code);
                    return;
                }
                CardSequence_813D2B40(slot);
                CardSequence_813D3380(slot, 0, (u8)fileNo);
            }
        }
    }  // namespace memorycard
}  // namespace ipl
