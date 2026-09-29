#ifndef IPL_MEMORY_CARD_LIB_H
#define IPL_MEMORY_CARD_LIB_H

#include <revolution/types.h>

namespace ipl {
    namespace memorycard {
        typedef struct FileInfo {
            u16 fileNo;    // 0x00
            u16 size;      // 0x02
            u8  canCopy;   // 0x04
            u8  canMove;   // 0x05
            u16 unk_0x06;  // 0x06
            u32 key;       // 0x08
        } FileInfo;            // 0x0C

        typedef struct CardState {
            vu8  unk_0x00;    // 0x00
            vu8  changed;     // 0x01
            vs16 state;       // 0x02
            vu16 unk_0x04;    // 0x04
            vu16 unk_0x06;    // 0x06
            vu32 key;         // 0x08
            vu16 unk_0x0C;    // 0x0C
            vu16 unk_0x0E;    // 0x0E
            vu16 freeBlocks;  // 0x10
            vu16 unk_0x12;    // 0x12
        } CardState;              // 0x14

        typedef struct IconState {
            u8  bannerEnable;      // 0x00
            u8  unk_0x01;          // 0x01
            u8  unk_0x02;          // 0x02
            u8  bannerType;        // 0x03
            s8  anmDelta;          // 0x04
            u8  anmType;           // 0x05
            u8  unk_0x06;          // 0x06
            u8  unk_0x07;          // 0x07
            u8  iconFmt[8];        // 0x08
            u16 anmFrameBits;      // 0x10
            s16 anmMax;            // 0x12
            u32 bannerOffset;      // 0x14
            u32 bannerTlutOffset;  // 0x18
            u32 iconOffset[8];     // 0x1C
            u32 iconTlutOffset;    // 0x3C
        } IconState;                   // 0x40

        void       probeCard();
        CardState* getCardSlotState();
        FileInfo*  getCardDirState();
        IconState* getIconStateArray();
        long       getCardLastSendCmd();
        long       getCardLastSrcSlot();
        long       getCardLastCMDFCmdResult();

        void       sendCardFormatCmd(u8 slot);
        void       sendCardCopyCmd(u8 slot, s16 fileNo);
        void       sendCardMoveCmd(u8 slot, s16 fileNo);
        void       sendCardDeleteCmd(u8 slot, s16 fileNo);

        const char* getIconComment(u8 slot, s16 fileNo);

        void          initCardThread();
        bool          shutdownCardThread();
    }  // namespace memorycard
}  // namespace ipl

#endif  // IPL_MEMORY_CARD_LIB_H
