#ifndef PRIVATE_NWC24_MAIL_BOX_H
#define PRIVATE_NWC24_MAIL_BOX_H

#include <revolution/types.h>

#include <revolution/nwc24/NWC24Err.h>
#include <revolution/nwc24/NWC24Types.h>
#include <revolution/nwc24/NWC24MsgBoard.h>

#include <private/nwc24/NWC24File.h>
#include <private/nwc24/NWC24Private.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NWC24_MSG_RECIPIENT_MAX_ 8
#define NWC24_MSG_ATTACHMENT_MAX_ 2

typedef u64 NWC24iAddr;

typedef enum NWC24MsgBoxId {
    NWC24_MSGBOX_SEND = 0,
    NWC24_MSGBOX_RECV = 1,
    NWC24_MSGBOX_MAX
} NWC24MsgBoxId;

typedef struct NWC24iMBCHeader {
    u32 magic;         // at 0x0
    u32 version;       // at 0x4
    u32 numMsgs;       // at 0x8
    u32 capacity;      // at 0xC
    u32 totalMsgSize;  // at 0x10
    u32 fileSize;      // at 0x14
    u32 nextMsgId;     // at 0x18
    u32 freeChain;     // at 0x1C
    u32 oldestMsgId;   // at 0x20
    u32 freeSpace;     // at 0x24
    u8 reserved[0x30]; // at 0x28
    char uidl[0x28];   // at 0x58
} NWC24iMBCHeader;

typedef struct NWC24iMsgObj {
    u32 id;            // at 0x0
    u32 flags;         // at 0x4
    u32 length;        // at 0x8
    u32 appId;         // at 0xC
    u32 unk10;         // at 0x10
    u32 tag;           // at 0x14
    u32 command;       // at 0x18
    u32 unk1C;         // at 0x1C
    NWC24iAddr from;   // at 0x20
    s32 createTime;    // at 0x28
    u32 unk2C;         // at 0x2C
    NWC24Data fromField;      // at 0x30
    NWC24Data toField;        // at 0x38
    NWC24Data subject;        // at 0x40
    NWC24Data text;           // at 0x48
    NWC24Data contentType;    // at 0x50
    NWC24Data txEncoding;     // at 0x58
    NWC24Charset charset;     // at 0x60
    NWC24Encoding encoding;   // at 0x64
    NWC24Data attached[NWC24_MSG_ATTACHMENT_MAX_];       // at 0x68
    u32 attachedSize[NWC24_MSG_ATTACHMENT_MAX_];         // at 0x78
    NWC24MIMEType attachedType[NWC24_MSG_ATTACHMENT_MAX_]; // at 0x80
    union {
        NWC24iAddr to[NWC24_MSG_RECIPIENT_MAX_];
        NWC24Data toAddrs[NWC24_MSG_RECIPIENT_MAX_];
    };                         // at 0x88
    u8 numTo;                  // at 0xC8
    u8 numAttached;            // at 0xC9
    u16 groupId;               // at 0xCA
    u32 msgBoard;              // at 0xCC
    NWC24Data user;            // at 0xD0
    NWC24Data face;            // at 0xD8
    NWC24Data alt;             // at 0xE0
    NWC24Data dwcId;           // at 0xE8
    u32 iconNew;               // at 0xF0
    u8 unkF4[0x100 - 0xF4];    // at 0xF4
} NWC24iMsgObj;

typedef struct NWC24iMBCEntry {
    u32 id;          // at 0x0
    u32 flags;       // at 0x4
    u32 length;      // at 0x8
    u32 appId;       // at 0xC
    u32 unk10;       // at 0x10
    u32 tag;         // at 0x14
    u32 command;     // at 0x18
    u32 unk1C;       // at 0x1C
    NWC24iAddr from; // at 0x20
    s32 createTime;  // at 0x28
    u32 unk2C;       // at 0x2C
    u8 numTo;        // at 0x30
    u8 numAttached;  // at 0x31
    u16 groupId;     // at 0x32
    u32 fromField;   // at 0x34
    u32 toField;     // at 0x38
    u32 subject;     // at 0x3C
    u32 contentType; // at 0x40
    u32 txEncoding;  // at 0x44
    NWC24Data text;  // at 0x48
    NWC24Data attached[NWC24_MSG_ATTACHMENT_MAX_];       // at 0x50
    u32 attachedSize[NWC24_MSG_ATTACHMENT_MAX_];         // at 0x60
    NWC24MIMEType attachedType[NWC24_MSG_ATTACHMENT_MAX_]; // at 0x68
    NWC24Data dwcId; // at 0x70
    u32 iconNew;     // at 0x78
    u32 unk7C;       // at 0x7C
} NWC24iMBCEntry;

NWC24Err NWC24iOpenMBox();
NWC24Err NWC24iInitMBox();

NWC24Err NWC24iMBoxOpenNewMsg(NWC24MsgBoxId id, NWC24File* file, u32* msgId);
NWC24Err NWC24iMBoxOpenStoredMsg(NWC24MsgBoxId id, u32 msgId, NWC24File* file);
NWC24Err NWC24iMBoxCloseMsg(NWC24File* file);
NWC24Err NWC24iMBoxCancelMsg(NWC24File* file, NWC24MsgBoxId id, u32 msgId);
NWC24Err NWC24iMBoxAddMsgObj(NWC24MsgBoxId id, const NWC24iMsgObj* msg);
NWC24Err NWC24iMBoxFlushHeader(NWC24MsgBoxId id);
NWC24Err NWC24iMBoxCheck(NWC24MsgBoxId id, u32 size);
NWC24Err NWC24iMBoxSetLastUIDL(NWC24MsgBoxId id, const char* uidl);
BOOL NWC24iIsMsgObjReadable(const NWC24iMBCEntry* entry);

#ifdef __cplusplus
}
#endif

#endif  // PRIVATE_NWC24_MAIL_BOX_H
