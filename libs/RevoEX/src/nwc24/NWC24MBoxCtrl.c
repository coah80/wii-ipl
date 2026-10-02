#define NWC24_MBOX_CTRL
#include <private/nwc24.h>
#include <revolution/enc.h>
#include <revolution/nwc24.h>
#include <string.h>

typedef struct MBCHeader {
    u32 magic;
    u32 version;
    u32 numMessages;
    u32 capacity;
    u32 messageBytes;
    u32 fileSize;
    u32 nextId;
    u32 freeOffset;
    u32 oldestId;
    u32 freeBytes;
    u8 reserved[48];
    char lastUIDL[40];
} MBCHeader;

typedef struct MBCEntry {
    u32 msgId;
    u32 type;
    u32 length;
    u32 appId;
    u32 flags;
    u32 tag;
    u32 ledPattern;
    u32 crc;
    union {
        NWC24UserId fromId;
        struct {
            u32 fromIdHigh, fromIdLow;
        };
    };
    u32 date;
    u32 receivedDate;
    u8 numTo;
    u8 numAttached;
    u16 groupId;
    u32 fields[5];
    NWC24Data text;
    NWC24Data attached[2];
    u32 attachedSize[2];
    NWC24MIMEType attachedType[2];
    u32 textSize;
    u32 dwcId;
    u32 iconNew;
    u32 reserved;
} MBCEntry;

static struct {
    s32 count;
    NWC24MBoxType type;
} MountInfo;
static NWC24Err CreateCtrlFile(NWC24MBoxType type, BOOL force);
static NWC24Err DeleteMsg(NWC24MBoxType type, u32 id, BOOL protect);
static NWC24Err DuplicationCheck(MBCHeader* header, const NWC24MsgObjPrivate* msg, NWC24File* file, NWC24MBoxType type);
static NWC24Err GetCachedMBCHeader(NWC24MBoxType type, MBCHeader** header);
static NWC24Err InitMBCHeader(MBCHeader* header, NWC24MBoxType type);
static NWC24Err AddMBCEntry(MBCHeader* header, const NWC24MsgObjPrivate* msg, NWC24File* file);
static NWC24Err ClearMBCEntry(MBCHeader* header, NWC24File* file, u32 offset);
static NWC24Err MountVFMBox(NWC24MBoxType type);
static NWC24Err CopyMsgObjToMBCFmt(const NWC24MsgObjPrivate* msg, MBCEntry* entry);
static NWC24Err CopyMsgObjToPrvFmt(const MBCEntry* entry, NWC24MsgObjPrivate* msg) NO_INLINE;
BOOL NWC24iIsMsgObjReadable(MBCEntry* entry) NO_INLINE;
NWC24Err NWC24CreateVF(const char* path, u32 size);

static inline NWC24Err MakeCtrlPath(char* path, NWC24MBoxType type) {
    const char* dir = NWC24GetMBoxDir();
    if (STD_strnlen(dir, 64) + 14 > 256)
        return NWC24_ERR_NOMEM;
    switch (type) {
        case NWC24_MBOX_TYPE_SEND:
            Mail_sprintf(path, "%s%s", dir, "/wc24send.ctl");
            break;
        case NWC24_MBOX_TYPE_RECV:
            Mail_sprintf(path, "%s%s", dir, "/wc24recv.ctl");
            break;
        default:
            return NWC24_ERR_INVALID_VALUE;
    }
    return NWC24_OK;
}

static inline NWC24Err MakeBoxPath(char* path, NWC24MBoxType type) {
    const char* dir = NWC24GetMBoxDir();
    if (STD_strnlen(dir, 64) + 14 > 256)
        return NWC24_ERR_NOMEM;
    switch (type) {
        case NWC24_MBOX_TYPE_RECV:
            Mail_sprintf(path, "%s%s", dir, "/wc24recv.mbx");
            break;
        case NWC24_MBOX_TYPE_SEND:
            Mail_sprintf(path, "%s%s", dir, "/wc24send.mbx");
            break;
        default:
            return NWC24_ERR_INVALID_VALUE;
    }
    return NWC24_OK;
}

static inline NWC24Err UnmountVFMBox(void) {
    MBCHeader* header;
    u32 size;
    NWC24Err err;
    if (MountInfo.count == 0)
        return NWC24_OK;
    --MountInfo.count;
    if (MountInfo.count > 0)
        return NWC24_OK;
    err = GetCachedMBCHeader(MountInfo.type, &header);
    if (err != NWC24_OK)
        return err;
    err = NWC24CheckSizeVF("@24", &size);
    if (err != NWC24_OK)
        return err;
    header->freeBytes = size;
    return NWC24UnmountVF("@24");
}
static inline NWC24Err ForceUnmountVFMBox(void) {
    u32 size;
    MBCHeader* header;
    NWC24Err err;
    MountInfo.count = 1;
    if (MountInfo.count == 0)
        return NWC24_OK;
    --MountInfo.count;
    if (MountInfo.count > 0)
        return NWC24_OK;
    err = GetCachedMBCHeader(MountInfo.type, &header);
    if (err != NWC24_OK)
        return err;
    err = NWC24CheckSizeVF("@24", &size);
    if (err != NWC24_OK)
        return err;
    header->freeBytes = size;
    return NWC24UnmountVF("@24");
}

static inline NWC24Err WriteMBCHeader(MBCHeader* header, NWC24File* file) {
    NWC24Err err = NWC24FSeek(file, 0, NWC24_SEEK_BEG);
    if (err != NWC24_OK)
        return err;
    return NWC24FWrite(header, 128, file);
}

NWC24Err NWC24GetNumMsgs(NWC24MBoxType type, u32* count) {
    MBCHeader* header;
    NWC24Err err;
    if (!NWC24IsMsgLibOpened() && !NWC24IsMsgLibOpenedByTool())
        return NWC24_ERR_LIB_NOT_OPENED;
    err = GetCachedMBCHeader(type, &header);
    if (err != NWC24_OK) {
        *count = 0;
        return err;
    }
    *count = header->numMessages;
    return NWC24_OK;
}

NWC24Err NWC24GetMsgObj(NWC24MsgObj* msg, NWC24MBoxType type, u32 id) {
    MBCHeader* header;
    NWC24File file;
    char* path;
    MBCEntry* entry;
    NWC24Err result, err, closeResult;
    u32 offset;
    u32 count = 0;
    if (!NWC24IsMsgLibOpened() && !NWC24IsMsgLibOpenedByTool())
        return NWC24_ERR_LIB_NOT_OPENED;
    entry = (MBCEntry*)NWC24WorkP->unk_0x1800;
    memset(entry, 0, sizeof(*entry));
    if (id == 0)
        return NWC24_ERR_HIDDEN;
    err = GetCachedMBCHeader(type, &header);
    if (err != NWC24_OK)
        return err;
    path = NWC24WorkP->pathWork;
    err = MakeCtrlPath(path, type);
    if (err != NWC24_OK)
        return err;
    err = NWC24FOpen(&file, path, NWC24_OPEN_NAND_RW);
    if (err != NWC24_OK)
        return err;
    result = NWC24_ERR_NOT_FOUND;
    for (offset = 128; offset < header->fileSize; offset += 128) {
        err = NWC24FSeek(&file, offset, NWC24_SEEK_BEG);
        if (err != NWC24_OK) {
            result = err;
            break;
        }
        err = NWC24FRead(entry, 128, &file);
        if (err != NWC24_OK) {
            result = err;
            break;
        }
        if (entry->msgId == 0)
            continue;
        ++count;
        if (entry->msgId == id) {
            result = NWC24_ERR_HIDDEN;
            if (NWC24IsMsgLibOpenedByTool())
                result = NWC24_OK;
            else if (NWC24iIsMsgObjReadable(entry))
                result = NWC24_OK;
            break;
        }
    }
    if (result == NWC24_ERR_NOT_FOUND && header->numMessages != count) {
        header->numMessages = count;
        WriteMBCHeader(header, &file);
    }
    closeResult = NWC24FClose(&file);
    if (result != NWC24_OK)
        return id == 0 ? NWC24_ERR_INVALID_VALUE : result;
    if (closeResult != NWC24_OK)
        return closeResult;
    CopyMsgObjToPrvFmt(entry, (NWC24MsgObjPrivate*)msg);
    return result;
}

BOOL NWC24iIsMsgObjReadable(MBCEntry* entry) {
    if (!(entry->type & 0x200000))
        return FALSE;
    if (entry->type & 0xFE000000)
        return FALSE;
    if (entry->ledPattern & 0xFFF80000)
        return FALSE;
    if (entry->type & 2) {
        if (entry->appId == 0)
            return TRUE;
        return (NWC24GetAppId() & 0xFFFFFF00) == (entry->appId & 0xFFFFFF00);
    }
    if (NWC24GetAppId() == 0x48414541)
        return TRUE;
    if (entry->type & 4)
        return TRUE;
    return (NWC24GetAppId() & 0xFFFFFF00) == (entry->appId & 0xFFFFFF00);
}

NWC24Err NWC24GetMsgIdList(NWC24MBoxType type, u32* ids, u32 maxLength) {
    MBCHeader* header;
    NWC24File file;
    NWC24Err result;
    char* path;
    NWC24Err err, closeResult;
    u32 offset;
    u32 count;
    MBCEntry* entry;
    if (!NWC24IsMsgLibOpened() && !NWC24IsMsgLibOpenedByTool())
        return NWC24_ERR_LIB_NOT_OPENED;
    entry = (MBCEntry*)NWC24WorkP->unk_0x1800;
    err = GetCachedMBCHeader(type, &header);
    if (err != NWC24_OK)
        return err;
    path = NWC24WorkP->pathWork;
    err = MakeCtrlPath(path, type);
    if (err != NWC24_OK)
        return err;
    result = NWC24FOpen(&file, path, NWC24_OPEN_NAND_R);
    if (result != NWC24_OK)
        return result;
    count = 0;
    for (offset = 128; offset < header->fileSize; offset += 128) {
        err = NWC24FSeek(&file, offset, NWC24_SEEK_BEG);
        if (err != NWC24_OK) {
            result = err;
            break;
        }
        err = NWC24FRead(entry, 64, &file);
        if (err != NWC24_OK) {
            result = err;
            break;
        }
        if (entry->msgId != 0 && entry->msgId <= 1000000) {
            ids[count] = entry->msgId;
            ++count;
            if (count == header->numMessages) {
                result = NWC24_OK;
                break;
            }
            if (count >= maxLength) {
                result = NWC24_ERR_FULL;
                break;
            }
        }
    }
    closeResult = NWC24FClose(&file);
    if (closeResult != NWC24_OK)
        result = closeResult;
    for (; count < maxLength; ++count)
        ids[count] = 0;
    return result;
}

NWC24Err NWC24DeleteMsg(NWC24MBoxType type, u32 id) {
    BOOL protect = TRUE;
    if (NWC24IsMsgLibOpenedByTool())
        protect = FALSE;
    return DeleteMsg(type, id, protect);
}

NWC24Err NWC24iOpenMBox(void) {
    MBCHeader* header;
    NWC24File recvFile, sendFile;
    char* path = NWC24WorkP->pathWork;
    NWC24Err err;
    Mail_memset(NWC24WorkP->unk_0x1700, 0, 128);
    err = GetCachedMBCHeader(NWC24_MBOX_TYPE_SEND, &header);
    if (err != NWC24_OK)
        return err;
    Mail_memset(NWC24WorkP->unk_0x1780, 0, 128);
    err = GetCachedMBCHeader(NWC24_MBOX_TYPE_RECV, &header);
    if (err != NWC24_OK)
        return err;
    err = MakeBoxPath(path, NWC24_MBOX_TYPE_RECV);
    if (err != NWC24_OK)
        return err;
    err = NWC24FOpen(&recvFile, path, NWC24_OPEN_NAND_R);
    if (err == NWC24_OK)
        err = NWC24FClose(&recvFile);
    if (err != NWC24_OK)
        return err;
    err = MakeBoxPath(path, NWC24_MBOX_TYPE_SEND);
    if (err != NWC24_OK)
        return err;
    err = NWC24FOpen(&sendFile, path, NWC24_OPEN_NAND_R);
    if (err == NWC24_OK)
        err = NWC24FClose(&sendFile);
    if (err != NWC24_OK)
        return err;
    MountInfo.count = 0;
    MountInfo.type = 0;
    return NWC24_OK;
}

NWC24Err NWC24iInitMBox(void) {
    NWC24File recvFile, sendFile;
    NWC24Err recvResult, sendResult, err, sendStatus;
    char* path = NWC24WorkP->pathWork;
    Mail_memset(NWC24WorkP->unk_0x1700, 0, 128);
    sendResult = CreateCtrlFile(NWC24_MBOX_TYPE_SEND, FALSE);
    if (sendResult < 0)
        return sendResult;
    Mail_memset(NWC24WorkP->unk_0x1780, 0, 128);
    recvResult = CreateCtrlFile(NWC24_MBOX_TYPE_RECV, FALSE);
    if (recvResult < 0)
        return recvResult;
    err = MakeBoxPath(path, NWC24_MBOX_TYPE_RECV);
    if (err != NWC24_OK)
        return err;
    err = NWC24FOpen(&recvFile, path, NWC24_OPEN_NAND_R);
    if (err == NWC24_OK)
        err = NWC24FClose(&recvFile);
    if (err == -20 || recvResult != 0)
        err = NWC24CreateVF(path, 0x700000);
    if (err != NWC24_OK)
        return err;
    err = MakeBoxPath(path, NWC24_MBOX_TYPE_SEND);
    if (err != NWC24_OK)
        return err;
    sendStatus = NWC24FOpen(&sendFile, path, NWC24_OPEN_NAND_R);
    if (sendStatus == NWC24_OK)
        sendStatus = NWC24FClose(&sendFile);
    err = sendStatus;
    if (sendStatus == -20 || sendResult != 0)
        err = NWC24CreateVF(path, 0x200000);
    if (err != NWC24_OK)
        return err;
    MountInfo.count = 0;
    MountInfo.type = 0;
    NWC24FDelete("/shared2/wc24/mbox/recvtmp.msg");
    NWC24FDelete("/shared2/wc24/mbox/dlcnt.bin");
    return err;
}

static inline NWC24Err MakeMountPath(char* path, NWC24MBoxType type) {
    const char* dir = NWC24GetMBoxDir();
    if (STD_strnlen(dir, 64) + 14 > 256)
        return NWC24_ERR_NOMEM;
    switch (type) {
        case NWC24_MBOX_TYPE_SEND:
            Mail_sprintf(path, "%s%s", dir, "/wc24send.mbx");
            break;
        case NWC24_MBOX_TYPE_RECV:
            Mail_sprintf(path, "%s%s", dir, "/wc24recv.mbx");
            break;
        default:
            return NWC24_ERR_INVALID_VALUE;
    }
    return NWC24_OK;
}

static inline NWC24Err MakeMsgPath(char* path, NWC24MBoxType type, u32 id) {
    switch (type) {
        case NWC24_MBOX_TYPE_SEND:
            Mail_sprintf(path, "@24:/mb/s%07d.msg", id);
            break;
        case NWC24_MBOX_TYPE_RECV:
            Mail_sprintf(path, "@24:/mb/r%07d.msg", id);
            break;
        default:
            return NWC24_ERR_INVALID_VALUE;
    }
    return NWC24_OK;
}

NWC24Err NWC24iMBoxOpenNewMsg(NWC24MBoxType type, NWC24File* file, u32* id) {
    MBCHeader* header;
    NWC24Err err;
    char* path;
    err = GetCachedMBCHeader(type, &header);
    if (err != NWC24_OK)
        return err;
    if (header->magic != 0x57635466)
        err = NWC24_ERR_INVALID_VALUE;
    else {
        MBCHeader* cached = header;
        if (cached->nextId > 1000000)
            cached->nextId = 1;
        *id = cached->nextId;
        ++cached->nextId;
        err = NWC24_OK;
    }
    if (err != NWC24_OK)
        return err;
    err = MountVFMBox(type);
    if (err != NWC24_OK)
        return err;
    path = NWC24WorkP->pathWork;
    err = MakeMsgPath(path, type, *id);
    if (err == NWC24_OK)
        err = NWC24FOpen(file, path, NWC24_OPEN_VF_WBUFF);
    if (err != NWC24_OK)
        UnmountVFMBox();
    return err;
}

NWC24Err NWC24iMBoxOpenStoredMsg(NWC24MBoxType type, u32 id, NWC24File* file) {
    NWC24Err err;
    char* path;
    err = MountVFMBox(type);
    if (err != NWC24_OK)
        return err;
    path = NWC24WorkP->pathWork;
    err = MakeMsgPath(path, type, id);
    if (err == NWC24_OK)
        err = NWC24FOpen(file, path, NWC24_OPEN_VF_RBUFF);
    if (err != NWC24_OK)
        UnmountVFMBox();
    return err;
}

NWC24Err NWC24iMBoxCloseMsg(NWC24File* file) {
    NWC24Err err = NWC24FClose(file);
    NWC24Err unmount = UnmountVFMBox();
    if (err != NWC24_OK && unmount != NWC24_OK)
        return unmount;
    return err;
}

static inline NWC24Err DeleteMsgFile(NWC24MBoxType type, u32 id) {
    NWC24Err err, unmount;
    char* path;
    err = MountVFMBox(type);
    if (err != NWC24_OK)
        return err;
    path = NWC24WorkP->pathWork;
    err = MakeMsgPath(path, type, id);
    if (err != NWC24_OK)
        return err;
    err = NWC24FDeleteVF(path);
    unmount = UnmountVFMBox();
    return err != NWC24_OK ? err : unmount;
}

NWC24Err NWC24iMBoxCancelMsg(NWC24File* file, NWC24MBoxType type, u32 id) {
    NWC24Err err = NWC24FClose(file);
    NWC24Err deletion = DeleteMsgFile(type, id);
    NWC24Err unmount;
    unmount = ForceUnmountVFMBox();
    if (err != NWC24_OK)
        return err;
    if (deletion != NWC24_OK)
        return deletion;
    if (unmount != NWC24_OK)
        return unmount;
    return NWC24_OK;
}

NWC24Err NWC24iMBoxAddMsgObj(NWC24MBoxType type, const NWC24MsgObjPrivate* msg) {
    MBCHeader* header;
    MBCHeader* cached;
    NWC24File file;
    char* path;
    NWC24Err err, closeResult;
    err = GetCachedMBCHeader(type, &header);
    if (err != NWC24_OK)
        return err;
    if (header->numMessages == header->capacity)
        return NWC24_ERR_FULL;
    path = NWC24WorkP->pathWork;
    err = MakeCtrlPath(path, type);
    if (err != NWC24_OK)
        return err;
    err = NWC24FOpen(&file, path, NWC24_OPEN_NAND_RW);
    if (err != NWC24_OK)
        return err;
    err = AddMBCEntry(header, msg, &file);
    if (err == NWC24_OK) {
        err = DuplicationCheck(header, msg, &file, type);
        if (err != NWC24_OK)
            goto close;
    } else {
        if (err != NWC24_ERR_BROKEN)
            goto close;
        header->magic = 0x42524B4E;
    }
    cached = header;
    closeResult = NWC24FSeek(&file, 0, NWC24_SEEK_BEG);
    if (closeResult != NWC24_OK)
        err = closeResult;
    else
        err = NWC24FWrite(cached, 128, &file);
close:
    closeResult = NWC24FClose(&file);
    return err != NWC24_OK ? err : closeResult;
}

NWC24Err NWC24iMBoxFlushHeader(NWC24MBoxType type) {
    MBCHeader* header;
    MBCHeader* cached;
    NWC24File file;
    char* path;
    NWC24Err err, result, closeResult;
    err = GetCachedMBCHeader(type, &header);
    if (err != NWC24_OK)
        return err;
    path = NWC24WorkP->pathWork;
    err = MakeCtrlPath(path, type);
    if (err != NWC24_OK)
        return err;
    err = NWC24FOpen(&file, path, NWC24_OPEN_NAND_RW);
    if (err != NWC24_OK)
        return err;
    cached = header;
    err = NWC24FSeek(&file, 0, NWC24_SEEK_BEG);
    if (err != NWC24_OK)
        result = err;
    else
        result = NWC24FWrite(cached, 128, &file);
    closeResult = NWC24FClose(&file);
    return result != NWC24_OK ? result : closeResult;
}

static inline void GetOldestMsgId(const MBCHeader* header, volatile u32* id) {
    *id = header->oldestId;
}

NWC24Err NWC24iMBoxCheck(NWC24MBoxType type, u32 size) {
    u32 required;
    struct {
        volatile u32 oldestId;
        MBCHeader* header;
    } mailbox;
    NWC24Err err;
    if (size >= 0x31C00)
        return NWC24_ERR_OVERFLOW;
    required = size + 0x4000;
    err = GetCachedMBCHeader(type, &mailbox.header);
    if (err != NWC24_OK)
        return err;
    if (type == NWC24_MBOX_TYPE_SEND) {
        if (mailbox.header->numMessages >= mailbox.header->capacity)
            return NWC24_ERR_FULL;
        if (mailbox.header->freeBytes <= required)
            return NWC24_ERR_FULL;
    } else if (type == NWC24_MBOX_TYPE_RECV) {
        while (mailbox.header->numMessages >= mailbox.header->capacity || mailbox.header->freeBytes <= required) {
            GetOldestMsgId(mailbox.header, &mailbox.oldestId);
            err = DeleteMsg(type, mailbox.oldestId, FALSE);
            if (err != NWC24_OK)
                return err;
            err = GetCachedMBCHeader(type, &mailbox.header);
            if (err != NWC24_OK)
                return err;
        }
    } else
        return NWC24_ERR_INVALID_VALUE;
    return NWC24_OK;
}

NWC24Err NWC24iMBoxSetLastUIDL(u32 type, const char* uidl) {
    MBCHeader* header;
    NWC24Err err = GetCachedMBCHeader(type, &header);
    if (err != NWC24_OK)
        return err;
    Mail_memset(header->lastUIDL, 0, sizeof(header->lastUIDL));
    Mail_strncpy(header->lastUIDL, uidl, sizeof(header->lastUIDL));
    return NWC24_OK;
}

static NWC24Err CreateCtrlFile(NWC24MBoxType type, BOOL force) {
    MBCHeader* header;
    NWC24File file;
    MBCEntry* entry;
    char* path;
    u32 offset;
    NWC24Err err, result, writeResult, closeResult;
    err = GetCachedMBCHeader(type, &header);
    if (err != NWC24_OK || force) {
        path = NWC24WorkP->pathWork;
        Mail_memset(path, 0, 256);
        err = MakeCtrlPath(path, type);
        if (err != NWC24_OK)
            return err;
        entry = (MBCEntry*)NWC24WorkP->unk_0x1800;
        if (type == NWC24_MBOX_TYPE_SEND)
            header = (MBCHeader*)NWC24WorkP->unk_0x1700;
        else if (type == NWC24_MBOX_TYPE_RECV)
            header = (MBCHeader*)NWC24WorkP->unk_0x1780;
        else
            return NWC24_ERR_INVALID_VALUE;
        result = err;
        err = NWC24FOpen(&file, path, NWC24_OPEN_NAND_W);
        if (err == NWC24_OK) {
            InitMBCHeader(header, type);
            writeResult = NWC24FWrite(header, 128, &file);
            if (result != NWC24_OK)
                writeResult = result;
            result = writeResult;
            Mail_memset(entry, 0, 128);
            for (offset = 128; offset < header->fileSize; offset += 128) {
                entry->appId = (offset + 128) % header->fileSize;
                writeResult = NWC24FWrite(entry, 128, &file);
                if (result != NWC24_OK)
                    writeResult = result;
                result = writeResult;
            }
            closeResult = NWC24FClose(&file);
            if (result != NWC24_OK)
                closeResult = result;
            if (closeResult == NWC24_OK)
                closeResult = 1;
            return closeResult;
        } else
            return NWC24_ERR_FATAL;
    }
    return err;
}

static inline int CompareMsgId(u32 left, u32 right) {
    if (left == right)
        return 0;
    if (left > 900000 && right < 100000)
        return -1;
    if (left < 100000 && right > 900000)
        return 1;
    if (left > right)
        return 1;
    return -1;
}

static NWC24Err DeleteMsg(NWC24MBoxType type, u32 id, BOOL protect) {
    MBCHeader* header;
    NWC24File file;
    NWC24Err result;
    u32 count = 0;
    u32 offset;
    u32 foundOffset = 0;
    u32 oldest = 0;
    MBCEntry* entry;
    char* path;
    NWC24Err err, deleteResult, closeResult;
    if (!NWC24IsMsgLibOpened() && !NWC24IsMsgLibOpenedByTool())
        return NWC24_ERR_LIB_NOT_OPENED;
    entry = (MBCEntry*)NWC24WorkP->unk_0x1800;
    err = GetCachedMBCHeader(type, &header);
    if (err != NWC24_OK)
        return err;
    path = NWC24WorkP->pathWork;
    err = MakeCtrlPath(path, type);
    if (err != NWC24_OK)
        return err;
    err = NWC24FOpen(&file, path, NWC24_OPEN_NAND_RW);
    if (err != NWC24_OK)
        return err;
    result = NWC24_ERR_NOT_FOUND;
    for (offset = 128; offset < header->fileSize; offset += 128) {
        err = NWC24FSeek(&file, offset, NWC24_SEEK_BEG);
        if (err != NWC24_OK) {
            result = err;
            break;
        }
        err = NWC24FRead(entry, 128, &file);
        if (err != NWC24_OK) {
            result = err;
            break;
        }
        if (entry->msgId == 0)
            continue;
        ++count;
        if (entry->msgId == id) {
            if (protect) {
                if ((entry->type & 2) && entry->appId == 0) {
                    if (NWC24GetAppId() != 0x48414541) {
                        result = NWC24_ERR_PROTECTED;
                        break;
                    }
                } else if ((entry->appId & 0xFFFFFF00) != (NWC24GetAppId() & 0xFFFFFF00)) {
                    if (!(entry->type & 8) || NWC24GetAppId() != 0x48414541) {
                        result = NWC24_ERR_PROTECTED;
                        break;
                    }
                }
            }
            result = NWC24_OK;
            foundOffset = offset;
        } else if (oldest == 0 || CompareMsgId(oldest, entry->msgId) > 0)
            oldest = entry->msgId;
    }
    err = result;
    if (err == NWC24_ERR_NOT_FOUND && header->numMessages != count) {
        header->numMessages = count;
        WriteMBCHeader(header, &file);
    }
    if (err != NWC24_OK) {
        NWC24FClose(&file);
        return id == 0 ? NWC24_ERR_INVALID_VALUE : err;
    }
    header->oldestId = oldest;
    protect = ClearMBCEntry(header, &file, foundOffset);
    deleteResult = DeleteMsgFile(type, id);
    if (protect != NWC24_OK)
        deleteResult = protect;
    type = WriteMBCHeader(header, &file);
    if (deleteResult != NWC24_OK)
        type = deleteResult;
    closeResult = NWC24FClose(&file);
    return type != NWC24_OK ? type : closeResult;
}

static NWC24Err DuplicationCheck(MBCHeader* header, const NWC24MsgObjPrivate* msg, NWC24File* file, NWC24MBoxType type) {
    NWC24Err err = NWC24_OK;
    u32 offset;
    u32 count = 0;
    u32 duplicateId = 0;
    u32 duplicateOffset = 0;
    u32 oldest = 0;
    MBCEntry* entry;
    BOOL candidate;
    NWC24Err clearResult, deleteResult;
    if (type == NWC24_MBOX_TYPE_SEND)
        return NWC24_OK;
    entry = (MBCEntry*)NWC24WorkP->unk_0x1800;
    for (offset = 128; offset < header->fileSize; offset += 128) {
        if (count >= header->numMessages)
            break;
        err = NWC24FSeek(file, offset, NWC24_SEEK_BEG);
        if (err != NWC24_OK)
            break;
        err = NWC24FRead(entry, 128, file);
        if (err != NWC24_OK)
            break;
        if (entry->msgId == 0)
            continue;
        ++count;
        candidate = TRUE;
        if (entry->msgId == msg->msgId)
            candidate = FALSE;
        if (entry->type & msg->type & 1) {
            if (entry->appId != msg->appId)
                candidate = FALSE;
            if (entry->fromId != msg->fromId)
                candidate = FALSE;
        }
        if (candidate) {
            if ((msg->tag & 0xFFFF) && (entry->tag & 0xFFFF) == (msg->tag & 0xFFFF)) {
                duplicateId = entry->msgId;
                duplicateOffset = offset;
                continue;
            }
            if (msg->unk_0x1C != 0 && entry->crc == msg->unk_0x1C && entry->type == msg->type && entry->length == msg->length &&
                entry->flags == msg->flags && (s32)entry->date == (s32)msg->date) {
                duplicateId = entry->msgId;
                duplicateOffset = offset;
                continue;
            }
        }
        if (oldest == 0 || CompareMsgId(oldest, entry->msgId) > 0)
            oldest = entry->msgId;
    }
    if (err != NWC24_OK)
        return err;
    header->oldestId = oldest;
    if (duplicateId != 0) {
        clearResult = ClearMBCEntry(header, file, duplicateOffset);
        deleteResult = DeleteMsgFile(type, duplicateId);
        return clearResult != NWC24_OK ? clearResult : deleteResult;
    }
    return err;
}

static NWC24Err GetCachedMBCHeader(NWC24MBoxType type, MBCHeader** header) {
    NWC24File file;
    MBCHeader* cached;
    char* path;
    NWC24Err err = NWC24_OK, closeResult;
    if (type == NWC24_MBOX_TYPE_SEND)
        *header = (MBCHeader*)NWC24WorkP->unk_0x1700;
    else if (type == NWC24_MBOX_TYPE_RECV)
        *header = (MBCHeader*)NWC24WorkP->unk_0x1780;
    else {
        *header = NULL;
        return NWC24_ERR_INVALID_VALUE;
    }
    if ((*header)->magic != 0x57635466) {
        path = NWC24WorkP->pathWork;
        err = MakeCtrlPath(path, type);
        if (err != NWC24_OK)
            return err;
        err = NWC24FOpen(&file, path, NWC24_OPEN_NAND_R);
        if (err != NWC24_OK)
            return err;
        cached = *header;
        closeResult = NWC24FSeek(&file, 0, NWC24_SEEK_BEG);
        if (closeResult != NWC24_OK)
            err = closeResult;
        else {
            closeResult = NWC24FRead(cached, 128, &file);
            if (closeResult != NWC24_OK)
                err = closeResult;
            else {
                err = NWC24_OK;
                if (cached->magic != 0x57635466)
                    err = NWC24_ERR_BROKEN;
            }
        }
        closeResult = NWC24FClose(&file);
        if (err == NWC24_OK && closeResult != NWC24_OK)
            err = closeResult;
    }
    if ((*header)->version != 4)
        return NWC24_ERR_VER_MISMATCH;
    if ((*header)->freeOffset & 31)
        return NWC24_ERR_BROKEN;
    return err;
}

static NWC24Err InitMBCHeader(MBCHeader* header, NWC24MBoxType type) {
    u32 i;
    Mail_memset(header, 0, 128);
    if (type == NWC24_MBOX_TYPE_SEND) {
        header->capacity = 127;
        header->freeBytes = 0x200000;
    } else if (type == NWC24_MBOX_TYPE_RECV) {
        header->capacity = 255;
        header->freeBytes = 0x700000;
    }
    header->magic = 0x57635466;
    header->version = 4;
    header->numMessages = 0;
    header->messageBytes = 0;
    header->fileSize = header->capacity * 128 + 128;
    header->nextId = 1;
    header->freeOffset = 128;
    header->oldestId = 0;
    for (i = 0; i < 39; ++i)
        header->lastUIDL[i] = '0';
    return NWC24_OK;
}

static NWC24Err AddMBCEntry(MBCHeader* header, const NWC24MsgObjPrivate* msg, NWC24File* file) {
    u32 offset = header->freeOffset;
    MBCEntry* entry = (MBCEntry*)NWC24WorkP->unk_0x1800;
    u32 next;
    NWC24Err err;
    if (offset == 0)
        return NWC24_ERR_FULL;
    if (offset >= header->fileSize || (offset - 128) % 128 != 0)
        return NWC24_ERR_BROKEN;
    err = NWC24FSeek(file, offset, NWC24_SEEK_BEG);
    if (err != NWC24_OK)
        return err;
    err = NWC24FRead(entry, 128, file);
    if (err != NWC24_OK)
        return err;
    next = entry->appId;
    if (next >= header->fileSize || (next - 128) % 128 != 0)
        return NWC24_ERR_BROKEN;
    header->freeOffset = next;
    CopyMsgObjToMBCFmt(msg, entry);
    err = NWC24FSeek(file, offset, NWC24_SEEK_BEG);
    if (err != NWC24_OK)
        return err;
    err = NWC24FWrite(entry, 128, file);
    if (err != NWC24_OK)
        return err;
    if (header->numMessages == 0)
        header->oldestId = msg->msgId;
    ++header->numMessages;
    header->messageBytes += msg->length;
    return NWC24_OK;
}

static NWC24Err ClearMBCEntry(MBCHeader* header, NWC24File* file, u32 offset) {
    MBCEntry* entry = (MBCEntry*)NWC24WorkP->unk_0x1800;
    NWC24Err err = NWC24FSeek(file, offset, NWC24_SEEK_BEG);
    if (err != NWC24_OK)
        return err;
    err = NWC24FRead(entry, 128, file);
    if (err != NWC24_OK)
        return err;
    --header->numMessages;
    header->messageBytes -= entry->length;
    memset(entry, 0, 128);
    entry->appId = header->freeOffset;
    header->freeOffset = offset;
    err = NWC24FSeek(file, offset, NWC24_SEEK_BEG);
    if (err != NWC24_OK)
        return err;
    err = NWC24FWrite(entry, 128, file);
    return err;
}

static NWC24Err MountVFMBox(NWC24MBoxType type) {
    char* path;
    NWC24Err err;
    if (MountInfo.count != 0 && MountInfo.type != type) {
        ForceUnmountVFMBox();
        return NWC24_ERR_FATAL;
    }
    ++MountInfo.count;
    if (MountInfo.count > 1)
        return NWC24_OK;
    path = NWC24WorkP->pathWork;
    err = MakeMountPath(path, type);
    if (err != NWC24_OK)
        return err;
    err = NWC24MountVF("@24", path);
    if (err != NWC24_OK)
        return err;
    MountInfo.type = type;
    return NWC24_OK;
}

static NWC24Err CopyMsgObjToMBCFmt(const NWC24MsgObjPrivate* msg, MBCEntry* entry) {
    u32 field1 = ((u32)msg->unk_0x30.ptr & 0xFFFFF) | (msg->unk_0x30.size << 20);
    u32 field2 = ((u32)msg->unk_0x38.ptr & 0xFFFFF) | (msg->unk_0x38.size << 20);
    u32 field3 = ((u32)msg->subject.ptr & 0xFFFFF) | (msg->subject.size << 20);
    u32 field4 = ((u32)msg->unk_0x50.ptr & 0xFFFFF) | (msg->unk_0x50.size << 20);
    u32 field5 = ((u32)msg->unk_0x58.ptr & 0xFFFFF) | (msg->unk_0x58.size << 20);
    entry->msgId = msg->msgId;
    entry->type = msg->type;
    entry->length = msg->length;
    entry->appId = msg->appId;
    entry->flags = msg->flags;
    entry->tag = msg->tag;
    entry->ledPattern = msg->ledPattern;
    entry->crc = msg->unk_0x1C;
    entry->fromIdHigh = msg->fromIdHigh;
    entry->fromIdLow = msg->fromIdLow;
    entry->date = msg->date;
    entry->receivedDate = msg->receivedDate;
    entry->numTo = msg->numTo;
    entry->numAttached = msg->numAttached;
    entry->groupId = msg->groupId;
    entry->fields[0] = field1;
    entry->fields[1] = field2;
    entry->fields[2] = field3;
    entry->fields[3] = field4;
    entry->fields[4] = field5;
    entry->text.ptr = msg->text.ptr;
    entry->text.size = msg->text.size;
    entry->textSize = msg->textSize;
    entry->dwcId = msg->dwcId;
    entry->iconNew = msg->iconNew;
    entry->attached[0].ptr = msg->attached[0].ptr;
    entry->attached[0].size = msg->attached[0].size;
    entry->attachedSize[0] = msg->attachedSize[0];
    entry->attachedType[0] = msg->attachedType[0];
    entry->attached[1].ptr = msg->attached[1].ptr;
    entry->attached[1].size = msg->attached[1].size;
    entry->attachedSize[1] = msg->attachedSize[1];
    entry->attachedType[1] = msg->attachedType[1];
    return NWC24_OK;
}

static NWC24Err CopyMsgObjToPrvFmt(const MBCEntry* entry, NWC24MsgObjPrivate* msg) {
    u32 offset1 = entry->fields[0] & 0xFFFFF;
    u32 size1 = entry->fields[0] >> 20;
    u32 offset2 = entry->fields[1] & 0xFFFFF;
    u32 size2 = entry->fields[1] >> 20;
    u32 offset3 = entry->fields[2] & 0xFFFFF;
    u32 size3 = entry->fields[2] >> 20;
    u32 offset4 = entry->fields[3] & 0xFFFFF;
    u32 size4 = entry->fields[3] >> 20;
    u32 offset5 = entry->fields[4] & 0xFFFFF;
    u32 size5 = entry->fields[4] >> 20;
    msg->msgId = entry->msgId;
    msg->type = entry->type;
    msg->length = entry->length;
    msg->appId = entry->appId;
    msg->flags = entry->flags;
    msg->tag = entry->tag;
    msg->ledPattern = entry->ledPattern;
    msg->unk_0x1C = entry->crc;
    msg->fromIdHigh = entry->fromIdHigh;
    msg->fromIdLow = entry->fromIdLow;
    msg->date = entry->date;
    msg->receivedDate = entry->receivedDate;
    msg->numTo = entry->numTo;
    msg->numAttached = entry->numAttached;
    msg->groupId = entry->groupId;
    msg->text.ptr = entry->text.ptr;
    msg->text.size = entry->text.size;
    msg->textSize = entry->textSize;
    msg->dwcId = entry->dwcId;
    msg->iconNew = entry->iconNew;
    msg->unk_0x30.ptr = (void*)offset1;
    msg->unk_0x30.size = size1;
    msg->unk_0x38.ptr = (void*)offset2;
    msg->unk_0x38.size = size2;
    msg->subject.ptr = (void*)offset3;
    msg->subject.size = size3;
    msg->unk_0x50.ptr = (void*)offset4;
    msg->unk_0x50.size = size4;
    msg->unk_0x58.ptr = (void*)offset5;
    msg->unk_0x58.size = size5;
    msg->attached[0].ptr = entry->attached[0].ptr;
    msg->attached[0].size = entry->attached[0].size;
    msg->attachedSize[0] = entry->attachedSize[0];
    msg->attachedType[0] = entry->attachedType[0];
    msg->attached[1].ptr = entry->attached[1].ptr;
    msg->attached[1].size = entry->attached[1].size;
    msg->attachedSize[1] = entry->attachedSize[1];
    msg->attachedType[1] = entry->attachedType[1];
    msg->toIds[0] = 0;
    msg->toIds[1] = 0;
    msg->toIds[2] = 0;
    msg->toIds[3] = 0;
    msg->toIds[4] = 0;
    msg->toIds[5] = 0;
    msg->toIds[6] = 0;
    msg->toIds[7] = 0;
    return NWC24_OK;
}
