#include <private/nwc24.h>
#include <revolution/nwc24.h>

#include <string.h>

#define MBOX_CTRL_MAGIC 'WcTf'
#define MBOX_CTRL_VERSION 4
#define MBOX_CTRL_BROKEN 'BRKN'

#define MBOX_SEND_CAPACITY 0x7F
#define MBOX_RECV_CAPACITY 0xFF

#define MBOX_SEND_FREE_SPACE 0x200000
#define MBOX_RECV_FREE_SPACE 0x700000

#define MBOX_ENTRY_SIZE sizeof(NWC24iMBCEntry)
#define MBOX_HEADER_SIZE sizeof(NWC24iMBCHeader)

#define MBOX_DIR_MAX 0x40
#define MBOX_PATH_MAX 0x100

#define MBOX_UIDL_SIZE 0x28

#define MSG_ID_MIN 1
#define MSG_ID_MAX 1000000
#define MSG_ID_WRAP_LOW 100000
#define MSG_ID_WRAP_HIGH 900000

#define MBOX_CHECK_MAX_SIZE 0x31C00
#define MBOX_CHECK_EXTRA_SPACE 0x4000

#define NWC24_APP_ID_IPL 'HAEA'

enum {
    MSG_OBJ_FOR_RECIPIENT = (1 << 0),
    MSG_OBJ_FOR_PUBLIC = (1 << 1),
    MSG_OBJ_FOR_MENU = (1 << 2),
    MSG_OBJ_INITIALIZED = (1 << 8),
    MSG_OBJ_DELIVERING = (1 << 9),
    MSG_OBJ_STORED = (1 << 21)
};

typedef struct MountInfo {
    s32 count;
    NWC24MsgBoxId id;
} MountInfo;

static MountInfo mountInfo;

static NWC24Err GetCtrlFilePath(NWC24MsgBoxId id, char* pPath);
static NWC24Err GetMBoxFilePath(const char* name, char* pPath);
static NWC24Err GetMailPath(NWC24MsgBoxId id, u32 msgId, char* pPath);
static NWC24Err IsFileThere(const char* pPath);

static s32 CreateCtrlFile(NWC24MsgBoxId id, BOOL force);
static NWC24Err DeleteMsg(NWC24MsgBoxId id, u32 msgId, BOOL checkPermission);
static NWC24Err DeleteMsgFile(NWC24MsgBoxId id, u32 msgId);
static NWC24Err DuplicationCheck(NWC24iMBCHeader* pHeader, const NWC24iMsgObj* pMsg,
                                 NWC24File* pFile, NWC24MsgBoxId id);
static NWC24Err GetCachedMBCHeader(NWC24MsgBoxId id, NWC24iMBCHeader** ppHeader);
static void InitMBCHeader(NWC24iMBCHeader* pHeader, NWC24MsgBoxId id);
static NWC24Err AddMBCEntry(NWC24iMBCHeader* pHeader, const NWC24iMsgObj* pMsg,
                            NWC24File* pFile);
static NWC24Err ClearMBCEntry(NWC24iMBCHeader* pHeader, NWC24File* pFile, u32 offset);
static NWC24Err MountVFMBox(NWC24MsgBoxId id);
static NWC24Err UnmountVFMBox(void);
static NWC24Err UnmountVFMBoxForced(void);
static u32 PackNWC24Data(const NWC24Data* pData);
static NWC24Err CopyMsgObjToMBCFmt(const NWC24iMsgObj* pSrc, NWC24iMBCEntry* pDst);
static NWC24Err CopyMsgObjToPrvFmt(const NWC24iMBCEntry* pSrc, NWC24iMsgObj* pDst);

NWC24Err NWC24GetNumMsgs(NWC24MBoxType msgBoxType, u32* numMsgs) {
    NWC24iMBCHeader* pHeader;
    NWC24Err result;

    if (!NWC24IsMsgLibOpened() && !NWC24IsMsgLibOpenedByTool()) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }

    result = GetCachedMBCHeader(msgBoxType, &pHeader);
    if (result != NWC24_OK) {
        *numMsgs = 0;
        return result;
    }

    *numMsgs = pHeader->numMsgs;
    return NWC24_OK;
}

NWC24Err NWC24GetMsgObj(NWC24MsgObj* msg, NWC24MBoxType msgBoxType, u32 index) {
    NWC24iMBCHeader* pHeader;
    NWC24iMBCEntry* pEntry;
    NWC24Err result;
    NWC24Err fileResult;
    NWC24File file;
    u32 offset;
    u32 numFound = 0;
    char* pPath;

    if (!NWC24IsMsgLibOpened() && !NWC24IsMsgLibOpenedByTool()) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }

    pEntry = (NWC24iMBCEntry*)NWC24WorkP->unk_0x1800;
    memset(pEntry, 0, sizeof(NWC24iMBCEntry));

    if (index == 0) {
        return NWC24_ERR_HIDDEN;
    }

    result = GetCachedMBCHeader(msgBoxType, &pHeader);
    if (result != NWC24_OK) {
        return result;
    }

    pPath = NWC24WorkP->pathWork;
    result = GetCtrlFilePath(msgBoxType, pPath);
    if (result != NWC24_OK) {
        return result;
    }

    result = NWC24FOpen(&file, pPath, NWC24_OPEN_NAND_RW);
    if (result != NWC24_OK) {
        return result;
    }

    result = NWC24_ERR_NOT_FOUND;

    for (offset = MBOX_HEADER_SIZE; offset < pHeader->fileSize;
         offset += MBOX_ENTRY_SIZE) {
        fileResult = NWC24FSeek(&file, offset, NWC24_SEEK_BEG);
        if (fileResult != NWC24_OK) {
            result = fileResult;
            break;
        }

        fileResult = NWC24FRead(pEntry, sizeof(NWC24iMBCEntry), &file);
        if (fileResult != NWC24_OK) {
            result = fileResult;
            break;
        }

        if (pEntry->id == 0) {
            continue;
        }

        numFound++;

        if (pEntry->id != index) {
            continue;
        }

        result = NWC24_ERR_HIDDEN;
        if (NWC24IsMsgLibOpenedByTool()) {
            result = NWC24_OK;
        } else if (NWC24iIsMsgObjReadable(pEntry)) {
            result = NWC24_OK;
        }
        break;
    }

    if (result == NWC24_ERR_NOT_FOUND && pHeader->numMsgs != numFound) {
        pHeader->numMsgs = numFound;
        if (NWC24FSeek(&file, 0, NWC24_SEEK_BEG) == NWC24_OK) {
            fileResult = NWC24FWrite(pHeader, sizeof(NWC24iMBCHeader), &file);
        }
    }

    fileResult = NWC24FClose(&file);

    if (result != NWC24_OK) {
        if (index == 0) {
            result = NWC24_ERR_INVALID_VALUE;
        }
        return result;
    }

    if (fileResult != NWC24_OK) {
        return fileResult;
    }

    CopyMsgObjToPrvFmt(pEntry, (NWC24iMsgObj*)msg);
    return result;
}

#pragma dont_inline on
BOOL NWC24iIsMsgObjReadable(const NWC24iMBCEntry* entry) {
    if (!(entry->flags & MSG_OBJ_STORED)) {
        return FALSE;
    }

    if (entry->flags & 0xFE000000) {
        return FALSE;
    }

    if (entry->command & 0xFFF80000) {
        return FALSE;
    }

    if (entry->flags & MSG_OBJ_FOR_PUBLIC) {
        if (entry->appId == 0) {
            return TRUE;
        }

        return (entry->appId & 0xFFFFFF00) == (NWC24GetAppId() & 0xFFFFFF00);
    }

    if (NWC24GetAppId() == NWC24_APP_ID_IPL) {
        return TRUE;
    }

    if (entry->flags & MSG_OBJ_FOR_MENU) {
        return TRUE;
    }

    return (entry->appId & 0xFFFFFF00) == (NWC24GetAppId() & 0xFFFFFF00);
}
#pragma dont_inline reset

NWC24Err NWC24GetMsgIdList(NWC24MBoxType msgBoxType, u32* msgIds,
                           u32 maxLength) {
    NWC24iMBCHeader* pHeader;
    NWC24Err result;
    NWC24Err fileResult;
    NWC24File file;
    u32 offset;
    char* pPath;
    u32 count;
    u32 i;
    u32* pList;
    NWC24iMBCEntry* pEntry;

    if (!NWC24IsMsgLibOpened() && !NWC24IsMsgLibOpenedByTool()) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }

    pEntry = (NWC24iMBCEntry*)NWC24WorkP->unk_0x1800;

    result = GetCachedMBCHeader(msgBoxType, &pHeader);
    if (result != NWC24_OK) {
        return result;
    }

    pPath = NWC24WorkP->pathWork;
    result = GetCtrlFilePath(msgBoxType, pPath);
    if (result != NWC24_OK) {
        return result;
    }

    result = NWC24FOpen(&file, pPath, NWC24_OPEN_NAND_R);
    if (result != NWC24_OK) {
        return result;
    }

    count = 0;
    pList = msgIds;

    for (offset = MBOX_HEADER_SIZE; offset < pHeader->fileSize;
         offset += MBOX_ENTRY_SIZE) {
        fileResult = NWC24FSeek(&file, offset, NWC24_SEEK_BEG);
        if (fileResult != NWC24_OK) {
            result = fileResult;
            break;
        }

        fileResult = NWC24FRead(pEntry, 0x40, &file);
        if (fileResult != NWC24_OK) {
            result = fileResult;
            break;
        }

        if (pEntry->id == 0) {
            continue;
        }

        if (pEntry->id > MSG_ID_MAX) {
            continue;
        }

        *pList++ = pEntry->id;
        count++;

        if (count == pHeader->numMsgs) {
            result = NWC24_OK;
            break;
        }

        if (count >= maxLength) {
            result = NWC24_ERR_FULL;
            break;
        }
    }

    fileResult = NWC24FClose(&file);
    if (fileResult != NWC24_OK) {
        result = fileResult;
    }

    while (count < maxLength) {
        msgIds[count] = 0;
        count++;
    }

    return result;
}

NWC24Err NWC24DeleteMsg(NWC24MBoxType msgBoxType, u32 index) {
    BOOL checkPermission = TRUE;

    if (NWC24IsMsgLibOpenedByTool()) {
        checkPermission = FALSE;
    }

    return DeleteMsg(msgBoxType, index, checkPermission);
}

NWC24Err NWC24iOpenMBox(void) {
    NWC24Err result;
    NWC24iMBCHeader* pHeader;
    char* pPath;

    pPath = NWC24WorkP->pathWork;

    Mail_memset(&NWC24WorkP->unk_0x1700, 0, sizeof(NWC24iMBCHeader));
    result = GetCachedMBCHeader(NWC24_MSGBOX_SEND, &pHeader);
    if (result != NWC24_OK) {
        return result;
    }

    Mail_memset(&NWC24WorkP->unk_0x1780, 0, sizeof(NWC24iMBCHeader));
    result = GetCachedMBCHeader(NWC24_MSGBOX_RECV, &pHeader);
    if (result != NWC24_OK) {
        return result;
    }

    result = GetCtrlFilePath(NWC24_MSGBOX_SEND, pPath);
    if (result != NWC24_OK) {
        return result;
    }

    result = IsFileThere(pPath);
    if (result != NWC24_OK) {
        return result;
    }

    result = GetCtrlFilePath(NWC24_MSGBOX_RECV, pPath);
    if (result != NWC24_OK) {
        return result;
    }

    result = IsFileThere(pPath);
    if (result != NWC24_OK) {
        return result;
    }

    mountInfo.count = 0;
    mountInfo.id = NWC24_MSGBOX_SEND;

    return NWC24_OK;
}

NWC24Err NWC24iInitMBox(void) {
    NWC24Err result;
    s32 createdSend;
    s32 createdRecv;
    char* pPath;

    pPath = NWC24WorkP->pathWork;

    Mail_memset(&NWC24WorkP->unk_0x1700, 0, sizeof(NWC24iMBCHeader));
    createdSend = CreateCtrlFile(NWC24_MSGBOX_SEND, FALSE);
    if (createdSend < 0) {
        return createdSend;
    }

    Mail_memset(&NWC24WorkP->unk_0x1780, 0, sizeof(NWC24iMBCHeader));
    createdRecv = CreateCtrlFile(NWC24_MSGBOX_RECV, FALSE);
    if (createdRecv < 0) {
        return createdRecv;
    }

    {
        NWC24File file1;
        NWC24Err fileResult;
        const char* pDir;

        pDir = NWC24GetMBoxDir();
        if (STD_strnlen(pDir, MBOX_DIR_MAX) + 0xE > MBOX_PATH_MAX) {
            fileResult = NWC24_ERR_NOMEM;
        } else {
            Mail_sprintf(pPath, "%s%s", pDir, "/wc24recv.mbx");
            fileResult = NWC24_OK;
        }
        if (fileResult != NWC24_OK) {
            return fileResult;
        }

        fileResult = NWC24FOpen(&file1, pPath, NWC24_OPEN_NAND_R);
        if (fileResult == NWC24_OK) {
            fileResult = NWC24FClose(&file1);
        }

        if (fileResult == NWC24_ERR_FILE_NOEXISTS || createdRecv != 0) {
            fileResult = NWC24CreateVF(pPath, MBOX_RECV_FREE_SPACE);
        }

        if (fileResult != NWC24_OK) {
            return fileResult;
        }
    }

    {
        NWC24File file;
        const char* pDir;

        pDir = NWC24GetMBoxDir();
        if (STD_strnlen(pDir, MBOX_DIR_MAX) + 0xE > MBOX_PATH_MAX) {
            result = NWC24_ERR_NOMEM;
        } else {
            Mail_sprintf(pPath, "%s%s", pDir, "/wc24send.mbx");
            result = NWC24_OK;
        }
        if (result != NWC24_OK) {
            return result;
        }

        result = NWC24FOpen(&file, pPath, NWC24_OPEN_NAND_R);
        if (result == NWC24_OK) {
            result = NWC24FClose(&file);
        }

        if (result == NWC24_ERR_FILE_NOEXISTS || createdSend != 0) {
            result = NWC24CreateVF(pPath, MBOX_SEND_FREE_SPACE);
        }

        if (result != NWC24_OK) {
            return result;
        }
    }

    mountInfo.count = 0;
    mountInfo.id = NWC24_MSGBOX_SEND;

    NWC24FDelete("/shared2/wc24/mbox/recvtmp.msg");
    NWC24FDelete("/shared2/wc24/mbox/dlcnt.bin");

    return result;
}

NWC24Err NWC24iMBoxOpenNewMsg(NWC24MsgBoxId id, NWC24File* pFile,
                              u32* pMsgId) {
    NWC24Err result;
    NWC24iMBCHeader* pHeader;
    char* pPath;

    result = GetCachedMBCHeader(id, &pHeader);
    if (result != NWC24_OK) {
        return result;
    }

    if (pHeader->magic != MBOX_CTRL_MAGIC) {
        result = NWC24_ERR_INVALID_VALUE;
    } else {
        if (pHeader->nextMsgId > MSG_ID_MAX) {
            pHeader->nextMsgId = MSG_ID_MIN;
        }

        *pMsgId = pHeader->nextMsgId;
        pHeader->nextMsgId++;
        result = NWC24_OK;
    }

    if (result != NWC24_OK) {
        return result;
    }

    result = MountVFMBox(id);
    if (result != NWC24_OK) {
        return result;
    }

    pPath = NWC24WorkP->pathWork;

    result = GetMailPath(id, *pMsgId, pPath);
    if (result == NWC24_OK) {
        result = NWC24FOpen(pFile, pPath, NWC24_OPEN_VF_WBUFF);
    }

    if (result != NWC24_OK) {
        UnmountVFMBox();
    }

    return result;
}

NWC24Err NWC24iMBoxOpenStoredMsg(NWC24MsgBoxId id, u32 msgId,
                                 NWC24File* pFile) {
    NWC24Err result;
    char* pPath;

    result = MountVFMBox(id);
    if (result != NWC24_OK) {
        return result;
    }

    pPath = NWC24WorkP->pathWork;

    result = GetMailPath(id, msgId, pPath);
    if (result == NWC24_OK) {
        result = NWC24FOpen(pFile, pPath, NWC24_OPEN_VF_RBUFF);
    }

    if (result != NWC24_OK) {
        UnmountVFMBox();
    }

    return result;
}

NWC24Err NWC24iMBoxCloseMsg(NWC24File* pFile) {
    NWC24Err closeResult;
    NWC24Err unmountResult;

    closeResult = NWC24FClose(pFile);
    unmountResult = UnmountVFMBox();

    if (closeResult != NWC24_OK && unmountResult != NWC24_OK) {
        return unmountResult;
    }

    return closeResult;
}

NWC24Err NWC24iMBoxCancelMsg(NWC24File* pFile, NWC24MsgBoxId id, u32 msgId) {
    NWC24Err closeResult;
    NWC24Err result;
    NWC24Err deleteResult;
    NWC24Err unmountResult;
    NWC24Err forcedResult;
    char* pPath;

    closeResult = NWC24FClose(pFile);

    result = MountVFMBox(id);
    if (result == NWC24_OK) {
        pPath = NWC24WorkP->pathWork;

        result = GetMailPath(id, msgId, pPath);
        if (result == NWC24_OK) {
            deleteResult = NWC24FDeleteVF(pPath);
            unmountResult = UnmountVFMBox();
            result = unmountResult;
            if (deleteResult != NWC24_OK) {
                result = deleteResult;
            }
        }
    }

    forcedResult = UnmountVFMBoxForced();

    if (closeResult != NWC24_OK) {
        return closeResult;
    }

    if (result != NWC24_OK) {
        return result;
    }

    return forcedResult != NWC24_OK ? forcedResult : NWC24_OK;
}

NWC24Err NWC24iMBoxAddMsgObj(NWC24MsgBoxId id, const NWC24iMsgObj* pMsg) {
    NWC24Err result;
    NWC24Err closeResult;
    NWC24Err saveResult;
    NWC24iMBCHeader* pHeader;
    NWC24File file;
    char* pPath;

    result = GetCachedMBCHeader(id, &pHeader);
    if (result != NWC24_OK) {
        return result;
    }

    if (pHeader->numMsgs == pHeader->capacity) {
        return NWC24_ERR_FULL;
    }

    pPath = NWC24WorkP->pathWork;
    result = GetCtrlFilePath(id, pPath);
    if (result != NWC24_OK) {
        return result;
    }

    result = NWC24FOpen(&file, pPath, NWC24_OPEN_NAND_RW);
    if (result != NWC24_OK) {
        return result;
    }

    result = AddMBCEntry(pHeader, pMsg, &file);
    if (result == NWC24_OK) {
        result = DuplicationCheck(pHeader, pMsg, &file, id);
        if (result != NWC24_OK) {
            goto done;
        }
    } else {
        if (result != NWC24_ERR_BROKEN) {
            goto done;
        }
        pHeader->magic = MBOX_CTRL_BROKEN;
    }

    saveResult = NWC24FSeek(&file, 0, NWC24_SEEK_BEG);
    if (saveResult != NWC24_OK) {
        result = saveResult;
        goto done;
    }
    result = NWC24FWrite(pHeader, sizeof(NWC24iMBCHeader), &file);

done:
    closeResult = NWC24FClose(&file);
    if (result != NWC24_OK) {
        return result;
    }

    return closeResult;
}

NWC24Err NWC24iMBoxFlushHeader(NWC24MsgBoxId id) {
    NWC24Err result;
    NWC24Err fileResult;
    NWC24Err closeResult;
    NWC24iMBCHeader* pHeader;
    NWC24File file;
    char* pPath;

    result = GetCachedMBCHeader(id, &pHeader);
    if (result != NWC24_OK) {
        return result;
    }

    pPath = NWC24WorkP->pathWork;
    result = GetCtrlFilePath(id, pPath);
    if (result != NWC24_OK) {
        return result;
    }

    result = NWC24FOpen(&file, pPath, NWC24_OPEN_NAND_RW);
    if (result != NWC24_OK) {
        return result;
    }

    fileResult = NWC24FSeek(&file, 0, NWC24_SEEK_BEG);
    if (fileResult != NWC24_OK) {
        result = fileResult;
        goto done;
    }
    result = NWC24FWrite(pHeader, sizeof(NWC24iMBCHeader), &file);

done:
    closeResult = NWC24FClose(&file);
    if (result != NWC24_OK) {
        return result;
    }

    return closeResult;
}

NWC24Err NWC24iMBoxCheck(NWC24MsgBoxId id, u32 size) {
    NWC24Err result;
    NWC24iMBCHeader* pHeader;
    u32 freeSpaceNeed;
    u32 msgId;

    if (size >= MBOX_CHECK_MAX_SIZE) {
        return NWC24_ERR_OVERFLOW;
    }

    freeSpaceNeed = size + MBOX_CHECK_EXTRA_SPACE;

    result = GetCachedMBCHeader(id, &pHeader);
    if (result != NWC24_OK) {
        return result;
    }

    if (id == NWC24_MSGBOX_SEND) {
        if (pHeader->numMsgs >= pHeader->capacity) {
            return NWC24_ERR_FULL;
        }

        if (pHeader->freeSpace <= freeSpaceNeed) {
            return NWC24_ERR_FULL;
        }

        return NWC24_OK;
    }

    if (id == NWC24_MSGBOX_RECV) {
        while (pHeader->numMsgs >= pHeader->capacity ||
               pHeader->freeSpace <= freeSpaceNeed) {
            msgId = pHeader->oldestMsgId;

            result = DeleteMsg(id, msgId, FALSE);
            if (result != NWC24_OK) {
                return result;
            }

            result = GetCachedMBCHeader(id, &pHeader);
            if (result != NWC24_OK) {
                return result;
            }
        }

        return NWC24_OK;
    }

    return NWC24_ERR_INVALID_VALUE;
}

NWC24Err NWC24iMBoxSetLastUIDL(NWC24MsgBoxId id, const char* uidl) {
    NWC24Err result;
    NWC24iMBCHeader* pHeader;

    result = GetCachedMBCHeader(id, &pHeader);
    if (result != NWC24_OK) {
        return result;
    }

    Mail_memset(pHeader->uidl, 0, sizeof(pHeader->uidl));
    Mail_strncpy(pHeader->uidl, uidl, sizeof(pHeader->uidl));

    return NWC24_OK;
}

static NWC24Err GetCtrlFilePath(NWC24MsgBoxId id, char* pPath) {
    const char* pDir;

    pDir = NWC24GetMBoxDir();
    if (STD_strnlen(pDir, MBOX_DIR_MAX) + 0xE > MBOX_PATH_MAX) {
        return NWC24_ERR_NOMEM;
    }

    switch (id) {
    case NWC24_MSGBOX_SEND:
        Mail_sprintf(pPath, "%s%s", pDir, "/wc24send.ctl");
        break;
    case NWC24_MSGBOX_RECV:
        Mail_sprintf(pPath, "%s%s", pDir, "/wc24recv.ctl");
        break;
    default:
        return NWC24_ERR_INVALID_VALUE;
    }

    return NWC24_OK;
}

static NWC24Err GetMBoxFilePath(const char* name, char* pPath) {
    const char* pDir;

    pDir = NWC24GetMBoxDir();
    if (STD_strnlen(pDir, MBOX_DIR_MAX) + 0xE > MBOX_PATH_MAX) {
        return NWC24_ERR_NOMEM;
    }

    Mail_sprintf(pPath, "%s%s", pDir, name);
    return NWC24_OK;
}

static NWC24Err GetMailPath(NWC24MsgBoxId id, u32 msgId, char* pPath) {
    switch (id) {
    case NWC24_MSGBOX_SEND:
        Mail_sprintf(pPath, NWC24_VF_DRIVE ":/mb/s%07d.msg", msgId);
        break;
    case NWC24_MSGBOX_RECV:
        Mail_sprintf(pPath, NWC24_VF_DRIVE ":/mb/r%07d.msg", msgId);
        break;
    default:
        return NWC24_ERR_INVALID_VALUE;
    }

    return NWC24_OK;
}

static NWC24Err IsFileThere(const char* pPath) {
    NWC24Err result;
    NWC24File file;

    result = NWC24FOpen(&file, pPath, NWC24_OPEN_NAND_R);
    if (result == NWC24_OK) {
        result = NWC24FClose(&file);
    }

    return result;
}

static s32 CreateCtrlFile(NWC24MsgBoxId id, BOOL force) {
    NWC24Err result;
    NWC24Err fileResult;
    NWC24iMBCHeader* pHeader;
    NWC24iMBCEntry* pEntry;
    NWC24File file;
    char* pPath;
    u32 offset;

    result = GetCachedMBCHeader(id, &pHeader);
    if (result == NWC24_OK && force == 0) {
        return result;
    }

    pPath = NWC24WorkP->pathWork;
    Mail_memset(pPath, 0, MBOX_PATH_MAX);

    result = GetCtrlFilePath(id, pPath);
    if (result != NWC24_OK) {
        return result;
    }

    pEntry = (NWC24iMBCEntry*)NWC24WorkP->unk_0x1800;

    if (id == NWC24_MSGBOX_SEND) {
        pHeader = (NWC24iMBCHeader*)NWC24WorkP->unk_0x1700;
    } else if (id == NWC24_MSGBOX_RECV) {
        pHeader = (NWC24iMBCHeader*)NWC24WorkP->unk_0x1780;
    } else {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (NWC24FOpen(&file, pPath, NWC24_OPEN_NAND_W) != NWC24_OK) {
        return NWC24_ERR_FATAL;
    }

    InitMBCHeader(pHeader, id);
    fileResult = NWC24FWrite(pHeader, MBOX_HEADER_SIZE, &file);
    if (result != NWC24_OK) {
        fileResult = result;
    }
    result = fileResult;

    Mail_memset(pEntry, 0, MBOX_ENTRY_SIZE);

    for (offset = MBOX_HEADER_SIZE; offset < pHeader->fileSize;
         offset += MBOX_ENTRY_SIZE) {
        pEntry->appId = (offset + MBOX_ENTRY_SIZE) % pHeader->fileSize;
        fileResult = NWC24FWrite(pEntry, MBOX_ENTRY_SIZE, &file);
        if (result != NWC24_OK) {
            fileResult = result;
        }
        result = fileResult;
    }

    fileResult = NWC24FClose(&file);
    if (result != NWC24_OK) {
        fileResult = result;
    }
    if (fileResult != NWC24_OK) {
        return fileResult;
    }

    return 1;
}

static NWC24Err DeleteMsg(NWC24MsgBoxId id, u32 msgId, BOOL checkPermission) {
    NWC24Err result;
    NWC24Err fileResult;
    NWC24iMBCHeader* pHeader;
    char* pathWork;
    u32 lastId;
    u32 offset;
    u32 clearOffset;
    u32 oldestMsgId;
    NWC24iMBCEntry* pEntry;
    NWC24File file;

    lastId = 0;
    clearOffset = 0;
    oldestMsgId = 0;

    if (!NWC24IsMsgLibOpened() && !NWC24IsMsgLibOpenedByTool()) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }

    pEntry = (NWC24iMBCEntry*)NWC24WorkP->unk_0x1800;

    result = GetCachedMBCHeader(id, &pHeader);
    if (result != NWC24_OK) {
        return result;
    }

    pathWork = NWC24WorkP->pathWork;
    result = GetCtrlFilePath(id, pathWork);
    if (result != NWC24_OK) {
        return result;
    }

    result = NWC24FOpen(&file, pathWork, NWC24_OPEN_NAND_RW);
    if (result != NWC24_OK) {
        return result;
    }

    result = NWC24_ERR_NOT_FOUND;

    for (offset = MBOX_HEADER_SIZE; offset < pHeader->fileSize;
         offset += MBOX_ENTRY_SIZE) {
        fileResult = NWC24FSeek(&file, offset, NWC24_SEEK_BEG);
        if (fileResult != NWC24_OK) {
            result = fileResult;
            break;
        }

        fileResult = NWC24FRead(pEntry, sizeof(NWC24iMBCEntry), &file);
        if (fileResult != NWC24_OK) {
            result = fileResult;
            break;
        }

        if (pEntry->id == 0) {
            continue;
        }

        lastId++;

        if (pEntry->id == msgId) {
            if (checkPermission) {
                if (pEntry->flags & MSG_OBJ_FOR_PUBLIC) {
                    if (pEntry->appId == 0 &&
                        NWC24GetAppId() != NWC24_APP_ID_IPL) {
                        result = NWC24_ERR_PROTECTED;
                        break;
                    }
                } else if ((pEntry->appId & 0xFFFFFF00) !=
                               (NWC24GetAppId() & 0xFFFFFF00) &&
                           (!(pEntry->flags & MSG_OBJ_FOR_MENU) ||
                            NWC24GetAppId() != NWC24_APP_ID_IPL)) {
                    result = NWC24_ERR_PROTECTED;
                    break;
                }
            }

            clearOffset = offset;
            result = NWC24_OK;
            continue;
        }

        if (oldestMsgId != 0) {
            if (CompareMsgId(oldestMsgId, pEntry->id) <= 0) {
                continue;
            }
        }

        oldestMsgId = pEntry->id;
    }

    if (result == NWC24_ERR_NOT_FOUND && pHeader->numMsgs != lastId) {
        pHeader->numMsgs = lastId;
        fileResult = NWC24FSeek(&file, 0, NWC24_SEEK_BEG);
        if (fileResult == NWC24_OK) {
            NWC24FWrite(pHeader, sizeof(NWC24iMBCHeader), &file);
        }
    }

    if (result != NWC24_OK) {
        NWC24FClose(&file);

        if (msgId == 0) {
            result = NWC24_ERR_INVALID_VALUE;
        }

        return result;
    }

    pHeader->oldestMsgId = oldestMsgId;
    result = ClearMBCEntry(pHeader, &file, clearOffset);

    fileResult = DeleteMsgFile(id, msgId);
    result = result != NWC24_OK ? result : fileResult;

    fileResult = NWC24FSeek(&file, 0, NWC24_SEEK_BEG);
    if (fileResult == NWC24_OK) {
        fileResult = NWC24FWrite(pHeader, sizeof(NWC24iMBCHeader), &file);
    }
    result = result != NWC24_OK ? result : fileResult;

    fileResult = NWC24FClose(&file);
    result = result != NWC24_OK ? result : fileResult;

    return result;
}

static NWC24Err DeleteMsgFile(NWC24MsgBoxId id, u32 msgId) {
    char* pPath;
    NWC24Err mountResult;
    NWC24Err result;

    mountResult = MountVFMBox(id);
    if (mountResult != NWC24_OK) {
        return mountResult;
    }

    pPath = NWC24WorkP->pathWork;

    result = GetMailPath(id, msgId, pPath);
    if (result != NWC24_OK) {
        return result;
    }

    result = NWC24FDeleteVF(pPath);
    mountResult = UnmountVFMBox();

    result = result != NWC24_OK ? result : mountResult;
    return result;
}

static NWC24Err DuplicationCheck(NWC24iMBCHeader* pHeader,
                                 const NWC24iMsgObj* pMsg, NWC24File* pFile,
                                 NWC24MsgBoxId id) {
    NWC24Err result;
    NWC24Err deleteErr;
    u32 offset;
    u32 checkedCount;
    u32 bestMsgId;
    u32 bestOffset;
    u32 oldestMsgId;
    NWC24iMBCEntry* pEntry;

    result = NWC24_OK;
    checkedCount = 0;
    bestMsgId = 0;
    bestOffset = 0;
    oldestMsgId = 0;

    if (id == NWC24_MSGBOX_SEND) {
        return NWC24_OK;
    }

    pEntry = (NWC24iMBCEntry*)NWC24WorkP->unk_0x1800;

    for (offset = MBOX_HEADER_SIZE; offset < pHeader->fileSize;
         offset += MBOX_ENTRY_SIZE) {
        BOOL isDuplicate = FALSE;

        if (checkedCount >= pHeader->numMsgs) {
            break;
        }

        result = NWC24FSeek(pFile, offset, NWC24_SEEK_BEG);
        if (result != NWC24_OK) {
            break;
        }

        result = NWC24FRead(pEntry, sizeof(NWC24iMBCEntry), pFile);
        if (result != NWC24_OK) {
            break;
        }

        if (pEntry->id == 0) {
            continue;
        }

        checkedCount++;
        isDuplicate = TRUE;

        if (pEntry->id == pMsg->id) {
            isDuplicate = FALSE;
        }

        if (pEntry->flags & pMsg->flags & MSG_OBJ_FOR_RECIPIENT) {
            if (pEntry->appId != pMsg->appId) {
                isDuplicate = FALSE;
            }

            if (pEntry->from != pMsg->from) {
                isDuplicate = FALSE;
            }
        }

        if (isDuplicate) {
            if ((pMsg->tag & 0xFFFF) != 0 &&
                (pEntry->tag & 0xFFFF) == (pMsg->tag & 0xFFFF)) {
                bestMsgId = pEntry->id;
                bestOffset = offset;
                continue;
            }

            if (pMsg->unk1C != 0 && pEntry->unk1C == pMsg->unk1C &&
                pEntry->flags == pMsg->flags && pEntry->length == pMsg->length &&
                pEntry->unk10 == pMsg->unk10 &&
                pEntry->createTime == pMsg->createTime) {
                bestMsgId = pEntry->id;
                bestOffset = offset;
                continue;
            }
        }

        if (oldestMsgId != 0) {
            if (CompareMsgId(oldestMsgId, pEntry->id) <= 0) {
                continue;
            }
        }

        oldestMsgId = pEntry->id;
    }

    if (result != NWC24_OK) {
        return result;
    }

    pHeader->oldestMsgId = oldestMsgId;

    if (bestMsgId != 0) {
        result = ClearMBCEntry(pHeader, pFile, bestOffset);
        deleteErr = DeleteMsgFile(id, bestMsgId);
        result = result != NWC24_OK ? result : deleteErr;
    }

    return result;
}

static int CompareMsgId(u32 lhs, u32 rhs) {
    if (lhs == rhs) {
        return 0;
    }

    if (lhs > MSG_ID_WRAP_HIGH && rhs < MSG_ID_WRAP_LOW) {
        return -1;
    }

    if (lhs < MSG_ID_WRAP_LOW && rhs > MSG_ID_WRAP_HIGH) {
        return 1;
    }

    return lhs > rhs ? 1 : -1;
}

static NWC24Err GetCachedMBCHeader(NWC24MsgBoxId id,
                                   NWC24iMBCHeader** ppHeader) {
    NWC24iMBCHeader* pHeader;
    NWC24Err result;
    NWC24Err fileResult;
    NWC24Err closeResult;
    NWC24File file;
    char* pPath;

    result = NWC24_OK;

    if (id == NWC24_MSGBOX_SEND) {
        *ppHeader = (NWC24iMBCHeader*)NWC24WorkP->unk_0x1700;
    } else if (id == NWC24_MSGBOX_RECV) {
        *ppHeader = (NWC24iMBCHeader*)NWC24WorkP->unk_0x1780;
    } else {
        *ppHeader = NULL;
        return NWC24_ERR_INVALID_VALUE;
    }

    if ((*ppHeader)->magic != MBOX_CTRL_MAGIC) {
        pPath = NWC24WorkP->pathWork;

        result = GetCtrlFilePath(id, pPath);
        if (result != NWC24_OK) {
            return result;
        }

        result = NWC24FOpen(&file, pPath, NWC24_OPEN_NAND_R);
        if (result != NWC24_OK) {
            return result;
        }

        pHeader = *ppHeader;

        fileResult = NWC24FSeek(&file, 0, NWC24_SEEK_BEG);
        if (fileResult != NWC24_OK) {
            result = fileResult;
        } else {
            fileResult = NWC24FRead(pHeader, MBOX_HEADER_SIZE, &file);
            if (fileResult != NWC24_OK) {
                result = fileResult;
            } else {
                result = NWC24_OK;
                if (pHeader->magic != MBOX_CTRL_MAGIC) {
                    result = NWC24_ERR_BROKEN;
                }
            }
        }

        closeResult = NWC24FClose(&file);
        if (result == NWC24_OK && closeResult != NWC24_OK) {
            result = closeResult;
        }
    }

    if ((*ppHeader)->version != MBOX_CTRL_VERSION) {
        return NWC24_ERR_VER_MISMATCH;
    }

    if ((*ppHeader)->freeChain & 0x1F) {
        result = NWC24_ERR_BROKEN;
    }

    return result;
}

static void InitMBCHeader(NWC24iMBCHeader* pHeader, NWC24MsgBoxId id) {
    u32 i;

    Mail_memset(pHeader, 0, sizeof(NWC24iMBCHeader));

    if (id == NWC24_MSGBOX_SEND) {
        pHeader->capacity = MBOX_SEND_CAPACITY;
        pHeader->freeSpace = MBOX_SEND_FREE_SPACE;
    } else if (id == NWC24_MSGBOX_RECV) {
        pHeader->capacity = MBOX_RECV_CAPACITY;
        pHeader->freeSpace = MBOX_RECV_FREE_SPACE;
    }

    pHeader->magic = MBOX_CTRL_MAGIC;
    pHeader->version = MBOX_CTRL_VERSION;
    pHeader->numMsgs = 0;
    pHeader->totalMsgSize = 0;
    pHeader->fileSize = pHeader->capacity * MBOX_ENTRY_SIZE + MBOX_HEADER_SIZE;
    pHeader->nextMsgId = MSG_ID_MIN;
    pHeader->freeChain = MBOX_HEADER_SIZE;
    pHeader->oldestMsgId = 0;

    for (i = 0; i < MBOX_UIDL_SIZE - 1; i++) {
        pHeader->uidl[i] = '0';
    }
}

static NWC24Err AddMBCEntry(NWC24iMBCHeader* pHeader, const NWC24iMsgObj* pMsg,
                            NWC24File* pFile) {
    u32 offset;
    NWC24iMBCEntry* pEntry;
    NWC24Err result;

    offset = pHeader->freeChain;
    pEntry = (NWC24iMBCEntry*)NWC24WorkP->unk_0x1800;

    if (offset == 0) {
        return NWC24_ERR_FULL;
    }

    if (offset >= pHeader->fileSize || (offset - MBOX_HEADER_SIZE) & 0x7F) {
        return NWC24_ERR_BROKEN;
    }

    result = NWC24FSeek(pFile, offset, NWC24_SEEK_BEG);
    if (result != NWC24_OK) {
        return result;
    }

    result = NWC24FRead(pEntry, MBOX_ENTRY_SIZE, pFile);
    if (result != NWC24_OK) {
        return result;
    }

    if (pEntry->appId >= pHeader->fileSize ||
        (pEntry->appId - MBOX_HEADER_SIZE) & 0x7F) {
        return NWC24_ERR_BROKEN;
    }

    pHeader->freeChain = pEntry->appId;

    CopyMsgObjToMBCFmt(pMsg, pEntry);

    result = NWC24FSeek(pFile, offset, NWC24_SEEK_BEG);
    if (result != NWC24_OK) {
        return result;
    }

    result = NWC24FWrite(pEntry, MBOX_ENTRY_SIZE, pFile);
    if (result != NWC24_OK) {
        return result;
    }

    if (pHeader->numMsgs == 0) {
        pHeader->oldestMsgId = pMsg->id;
    }

    pHeader->numMsgs++;
    pHeader->totalMsgSize += pMsg->length;

    return NWC24_OK;
}

static NWC24Err ClearMBCEntry(NWC24iMBCHeader* pHeader, NWC24File* pFile,
                              u32 offset) {
    NWC24iMBCEntry* pEntry;
    NWC24Err result;

    pEntry = (NWC24iMBCEntry*)NWC24WorkP->unk_0x1800;

    result = NWC24FSeek(pFile, offset, NWC24_SEEK_BEG);
    if (result != NWC24_OK) {
        return result;
    }

    result = NWC24FRead(pEntry, MBOX_ENTRY_SIZE, pFile);
    if (result != NWC24_OK) {
        return result;
    }

    pHeader->numMsgs--;
    pHeader->totalMsgSize -= pEntry->length;

    memset(pEntry, 0, MBOX_ENTRY_SIZE);
    pEntry->appId = pHeader->freeChain;
    pHeader->freeChain = offset;

    result = NWC24FSeek(pFile, offset, NWC24_SEEK_BEG);
    if (result != NWC24_OK) {
        return result;
    }

    return NWC24FWrite(pEntry, MBOX_ENTRY_SIZE, pFile);
}

static NWC24Err MountVFMBox(NWC24MsgBoxId id) {
    NWC24Err result;
    const char* pDir;
    char* pPath;

    if (mountInfo.count != 0 && mountInfo.id != id) {
        UnmountVFMBoxForced();
        return NWC24_ERR_FATAL;
    }

    if (++mountInfo.count > 1) {
        return NWC24_OK;
    }

    pPath = NWC24WorkP->pathWork;

    pPath = NWC24WorkP->pathWork;

    pDir = NWC24GetMBoxDir();
    if (STD_strnlen(pDir, MBOX_DIR_MAX) + 0xE > MBOX_PATH_MAX) {
        result = NWC24_ERR_NOMEM;
        goto mountCheck;
    }

    switch (id) {
    case NWC24_MSGBOX_SEND:
        Mail_sprintf(pPath, "%s%s", pDir, "/wc24send.mbx");
        break;
    case NWC24_MSGBOX_RECV:
        Mail_sprintf(pPath, "%s%s", pDir, "/wc24recv.mbx");
        break;
    default:
        result = NWC24_ERR_INVALID_VALUE;
        goto mountCheck;
    }
    result = NWC24_OK;

mountCheck:
    if (result != NWC24_OK) {
        return result;
    }

    result = NWC24MountVF(NWC24_VF_DRIVE, pPath);
    if (result != NWC24_OK) {
        return result;
    }

    mountInfo.id = id;
    return NWC24_OK;
}

static NWC24Err UnmountVFMBox(void) {
    NWC24iMBCHeader* pHeader;
    u32 freeSpace;
    NWC24Err result;

    if (mountInfo.count == 0) {
        return NWC24_OK;
    }

    if (--mountInfo.count > 0) {
        return NWC24_OK;
    }

    result = GetCachedMBCHeader(mountInfo.id, &pHeader);
    if (result != NWC24_OK) {
        return result;
    }

    result = NWC24CheckSizeVF(NWC24_VF_DRIVE, &freeSpace);
    if (result != NWC24_OK) {
        return result;
    }

    pHeader->freeSpace = freeSpace;
    return NWC24UnmountVF(NWC24_VF_DRIVE);
}

static NWC24Err UnmountVFMBoxForced(void) {
    mountInfo.count = 1;
    return UnmountVFMBox();
}

static u32 PackNWC24Data(const NWC24Data* pData) {
    return ((u32)pData->ptr & 0x000FFFFF) | (pData->size << 20);
}

static NWC24Err CopyMsgObjToMBCFmt(const NWC24iMsgObj* pSrc,
                                   NWC24iMBCEntry* pDst) {
    int i;

    u32 fromFieldPacked = PackNWC24Data(&pSrc->fromField);
    u32 toFieldPacked = PackNWC24Data(&pSrc->toField);
    u32 subjectPacked = PackNWC24Data(&pSrc->subject);
    u32 contentPacked = PackNWC24Data(&pSrc->contentType);
    u32 txEncodingPacked = PackNWC24Data(&pSrc->txEncoding);

    pDst->id = pSrc->id;
    pDst->flags = pSrc->flags;
    pDst->length = pSrc->length;
    pDst->appId = pSrc->appId;
    pDst->unk10 = pSrc->unk10;
    pDst->tag = pSrc->tag;
    pDst->command = pSrc->command;
    pDst->unk1C = pSrc->unk1C;
    pDst->from = pSrc->from;
    pDst->createTime = pSrc->createTime;
    pDst->unk2C = pSrc->unk2C;
    pDst->numTo = pSrc->numTo;
    pDst->numAttached = pSrc->numAttached;
    pDst->groupId = pSrc->groupId;

    pDst->fromField = fromFieldPacked;
    pDst->toField = toFieldPacked;
    pDst->subject = subjectPacked;
    pDst->contentType = contentPacked;
    pDst->txEncoding = txEncodingPacked;

    pDst->text = pSrc->text;
    pDst->dwcId = pSrc->dwcId;

    pDst->iconNew = pSrc->iconNew;

    for (i = 0; i < NWC24_MSG_ATTACHMENT_MAX_; i++) {
        pDst->attached[i] = pSrc->attached[i];
        pDst->attachedSize[i] = pSrc->attachedSize[i];
        pDst->attachedType[i] = pSrc->attachedType[i];
    }

    return NWC24_OK;
}

static NWC24Err CopyMsgObjToPrvFmt(const NWC24iMBCEntry* pSrc,
                                   NWC24iMsgObj* pDst) {
    int i;

    pDst->id = pSrc->id;
    pDst->flags = pSrc->flags;
    pDst->length = pSrc->length;
    pDst->appId = pSrc->appId;
    pDst->unk10 = pSrc->unk10;
    pDst->tag = pSrc->tag;
    pDst->command = pSrc->command;
    pDst->unk1C = pSrc->unk1C;
    pDst->from = pSrc->from;
    pDst->createTime = pSrc->createTime;
    pDst->unk2C = pSrc->unk2C;
    pDst->numTo = pSrc->numTo;
    pDst->numAttached = pSrc->numAttached;
    pDst->groupId = pSrc->groupId;

    pDst->fromField.ptr = (const void*)(pSrc->fromField & 0xFFFFF);
    pDst->fromField.size = pSrc->fromField >> 20;

    pDst->toField.ptr = (const void*)(pSrc->toField & 0xFFFFF);
    pDst->toField.size = pSrc->toField >> 20;

    pDst->subject.ptr = (const void*)(pSrc->subject & 0xFFFFF);
    pDst->subject.size = pSrc->subject >> 20;

    pDst->contentType.ptr = (const void*)(pSrc->contentType & 0xFFFFF);
    pDst->contentType.size = pSrc->contentType >> 20;

    pDst->txEncoding.ptr = (const void*)(pSrc->txEncoding & 0xFFFFF);
    pDst->txEncoding.size = pSrc->txEncoding >> 20;

    pDst->text = pSrc->text;
    pDst->dwcId = pSrc->dwcId;
    pDst->iconNew = pSrc->iconNew;

    for (i = 0; i < NWC24_MSG_ATTACHMENT_MAX_; i++) {
        pDst->attached[i] = pSrc->attached[i];
        pDst->attachedSize[i] = pSrc->attachedSize[i];
        pDst->attachedType[i] = pSrc->attachedType[i];
    }

    for (i = 0; i < NWC24_MSG_RECIPIENT_MAX_; i++) {
        pDst->to[i] = 0;
    }

    return NWC24_OK;
}
