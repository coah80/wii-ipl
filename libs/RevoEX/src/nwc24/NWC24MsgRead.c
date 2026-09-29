#include <private/nwc24.h>
#include <revolution/nwc24.h>

#include <string.h>

#define NWC24i_STRING_WORK_SIZE 1024

enum {
    MSG_OBJ_FOR_RECIPIENT = (1 << 0),
    MSG_OBJ_FOR_PUBLIC = (1 << 1),
    MSG_OBJ_FOR_APP = (1 << 2),
    MSG_OBJ_FOR_MENU = (1 << 3),
    MSG_OBJ_TO_SEND = (1 << 4),
    MSG_OBJ_TO_RECV = (1 << 5),
    MSG_OBJ_INITIALIZED = (1 << 8),
    MSG_OBJ_DELIVERING = (1 << 9),
    MSG_OBJ_FLAG_12 = (1 << 12),
};

static NWC24Err ReadMsgTextInternal(const NWC24MsgObj* msg, char* text,
                                    u32 textLen, char* name, u32 nameLen,
                                    NWC24Encoding* encoding);
static NWC24Err ReadBase64Data(NWC24File* file, const NWC24Data* data,
                               u8* out, u32 outSize, u32* outLen);
static NWC24Err ReadQPText(const NWC24MsgObj* msg, NWC24File* file, char* text,
                           u32 textSize);

NWC24Err NWC24ReadMsgField(const NWC24MsgObj* msg, char* fieldName,
                           u8* fieldBuf, u32 fieldBufLen) {
    const NWC24MsgObjPrivate* pMsg = (const NWC24MsgObjPrivate*)msg;
    NWC24Err result;
    NWC24Err closeResult;
    NWC24MsgBoxId id;
    u32 flags;
    u32 fieldLength;
    u32 fieldOffset;
    char* pField;
    NWC24FileStream stream;
    NWC24File file;

    if (!NWC24IsMsgLibOpened() && !NWC24IsMsgLibOpenedByTool()) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }

    if (!(msg->data[1] & MSG_OBJ_DELIVERING)) {
        return NWC24_ERR_PROTECTED;
    }

    flags = pMsg->type;
    if (flags & MSG_OBJ_TO_SEND) {
        id = NWC24_MSGBOX_SEND;
    } else if (flags & MSG_OBJ_TO_RECV) {
        id = NWC24_MSGBOX_RECV;
    } else {
        result = NWC24_ERR_INVALID_VALUE;
        goto select_done;
    }
    result = NWC24_OK;
select_done:

    if (result != NWC24_OK) {
        return result;
    }

    result = NWC24iMBoxOpenStoredMsg(id, pMsg->msgId, &file);
    if (result != NWC24_OK) {
        return result;
    }

    result = NWC24FStreamInit(&stream, &file, 0, pMsg->length,
                              NWC24WorkP->mainWork, NWC24i_STRING_WORK_SIZE);
    if (result == NWC24_OK) {
        result = NWC24iSearchHeaderF(&stream, fieldName, pMsg->unk_0x10,
                                   &fieldOffset, &fieldLength);
    }

    if (result == NWC24_OK) {
        if (fieldLength > fieldBufLen) {
            result = NWC24_ERR_OVERFLOW;
        } else {
            result = NWC24FStreamSeek(&stream, fieldOffset);
            if (result == NWC24_OK) {
                result = NWC24FStreamGetPtr(&stream, &pField, fieldLength);
                if (result == NWC24_OK) {
                    Mail_strncpy((char*)fieldBuf, pField, fieldLength);
                    fieldBuf[fieldLength - 2] = 0;
                }
            }
        }
    }

    closeResult = NWC24iMBoxCloseMsg(&file);
    if (result == NWC24_OK) {
        result = closeResult;
    }

    return result;
}

NWC24Err NWC24ReadMsgFaceData(const NWC24MsgObj* msg, u8* faceData) {
    const NWC24MsgObjPrivate* pMsg = (const NWC24MsgObjPrivate*)msg;
    char* pWork;
    NWC24Err result;
    u32 decodeSize;
    u32 length;

    if ((pMsg->type & MSG_OBJ_FOR_PUBLIC) && !(pMsg->type & MSG_OBJ_FLAG_12)) {
        return NWC24_ERR_NOT_FOUND;
    }

    pWork = NWC24WorkP->stringWork;
    Mail_memset(pWork, 0, NWC24i_STRING_WORK_SIZE);

    result = NWC24ReadMsgField(msg, "x-wiiface", (u8*)pWork,
                               NWC24i_STRING_WORK_SIZE);
    if (result != NWC24_OK) {
        return result;
    }

    length = STD_strnlen(pWork, NWC24i_STRING_WORK_SIZE);
    result = NWC24Base64Decode((u8*)pWork, length, faceData, NWC24_FACE_DATA_SIZE,
                               &decodeSize);
    if (result != NWC24_OK) {
        return result;
    }

    if (decodeSize != NWC24_FACE_DATA_SIZE) {
        return NWC24_ERR_FORMAT;
    }

    return NWC24_OK;
}

NWC24Err NWC24ReadMsgAltName(const NWC24MsgObj* msg, u16* altName,
                             u32 altNameLen) {
    char* pWork = NWC24WorkP->stringWork;
    NWC24Err result;
    u32 decodeSize;
    u32 length;

    Mail_memset(pWork, 0, NWC24i_STRING_WORK_SIZE);

    result = NWC24ReadMsgField(msg, "x-wii-altname:", (u8*)pWork,
                               NWC24i_STRING_WORK_SIZE);
    if (result != NWC24_OK) {
        return result;
    }

    length = STD_strnlen(pWork, NWC24i_STRING_WORK_SIZE);
    result = NWC24Base64Decode((u8*)pWork, length, (u8*)altName, altNameLen * 2,
                               &decodeSize);

    return result == NWC24_OK ? NWC24_OK : result;
}

NWC24Err NWC24ReadMsgMBNoReply(const NWC24MsgObj* msg, BOOL* mbNoReplyFlag) {
    char* pWork;
    NWC24Err result;

    *mbNoReplyFlag = FALSE;

    pWork = NWC24WorkP->stringWork;
    Mail_memset(pWork, 0, NWC24i_STRING_WORK_SIZE);

    result = NWC24ReadMsgField(msg, "x-wii-mb-noreply:", (u8*)pWork,
                               NWC24i_STRING_WORK_SIZE);
    if (result == NWC24_OK) {
        *mbNoReplyFlag = TRUE;
    } else if (result == NWC24_ERR_NOT_FOUND) {
        result = NWC24_OK;
    }

    return result;
}

NWC24Err NWC24ReadMsgMBRegDate(const NWC24MsgObj* msg, u16* year, u8* month,
                               u8* day) {
    NWC24Err result;
    char* pWork = NWC24WorkP->stringWork;
    s32 digit;
    u32 i;
    u32 digits;
    u32 value;
    char* p;

    i = 0;
    digits = 0;
    value = 0;

    Mail_memset(pWork, 0, NWC24i_STRING_WORK_SIZE);

    result = NWC24ReadMsgField(msg, "x-wii-mb-regdate:", (u8*)pWork,
                               NWC24i_STRING_WORK_SIZE - 1);
    if (result != NWC24_OK) {
        return result;
    }

    p = pWork;
    while (*p == '\t' || *p == ' ') {
        p++;
        i++;
    }

    while (i < NWC24i_STRING_WORK_SIZE) {
        digit = Util_xtoi(*p);
        if (digit < 0) {
            break;
        }

        value = (value << 4) | digit;
        p++;
        i++;
        digits++;

    }

    if (digits != 4) {
        result = NWC24_ERR_FORMAT;
    }

    *year = ((value >> 9) & 0x7F) + 2000;
    *month = (value >> 5) & 0xF;
    *day = value & 0x1F;

    return result;
}

NWC24Err NWC24ReadMsgMBDelay(const NWC24MsgObj* msg, u8* mbDelay) {
    NWC24Err result;
    char* pWork = NWC24WorkP->stringWork;
    s32 digit;
    u32 i;
    u32 digits;
    u32 value;
    char* p;

    i = 0;
    digits = 0;
    value = 0;

    Mail_memset(pWork, 0, NWC24i_STRING_WORK_SIZE);

    result = NWC24ReadMsgField(msg, "x-wii-mb-delay:", (u8*)pWork,
                               NWC24i_STRING_WORK_SIZE - 1);
    if (result != NWC24_OK) {
        return result;
    }

    p = pWork;
    while (*p == '\t' || *p == ' ') {
        p++;
        i++;
    }

    while (i < NWC24i_STRING_WORK_SIZE) {
        digit = Util_xtoi(*p);
        if (digit < 0) {
            break;
        }

        value = (value << 4) | digit;
        p++;
        i++;
        digits++;

    }

    if (digits != 2) {
        result = NWC24_ERR_FORMAT;
    }

    *mbDelay = value;

    return result;
}

NWC24Err NWC24ReadMsgMBUpdateSW(const NWC24MsgObj* msg, u32* mbUpdateSW) {
    const NWC24MsgObjPrivate* pMsg = (const NWC24MsgObjPrivate*)msg;
    NWC24Err result;
    u32 value;
    char* pWork;

    value = 0;

    if (!(pMsg->type & MSG_OBJ_FLAG_12)) {
        *mbUpdateSW = 0;
        return NWC24_ERR_NOT_FOUND;
    }

    pWork = NWC24WorkP->stringWork;
    Mail_memset(pWork, 0, NWC24i_STRING_WORK_SIZE);

    result = NWC24ReadMsgField(msg, "x-wii-mb-updatesw:", (u8*)pWork,
                               NWC24i_STRING_WORK_SIZE - 1);
    if (result != NWC24_OK) {
        return result;
    }

    while (*pWork == '\t' || *pWork == ' ') {
        pWork++;
    }

    if (Mail_isdigit(*pWork)) {
        value = *pWork - '0';
    }

    *mbUpdateSW = value;

    return result;
}

NWC24Err NWC24ReadMsgMBOptOutFlag(const NWC24MsgObj* msg, BOOL* mbOptOutFlag,
                                  u32* appId) {
    NWC24Err result;
    char* pWork = NWC24WorkP->stringWork;
    s32 digit;
    u32 i;
    u32 digits;
    u32 value;
    char* p;

    i = 0;
    digits = 0;
    value = 0;

    Mail_memset(pWork, 0, NWC24i_STRING_WORK_SIZE);

    *mbOptOutFlag = FALSE;
    *appId = 0;

    result = NWC24ReadMsgField(msg, "x-wii-mb-optout:", (u8*)pWork,
                               NWC24i_STRING_WORK_SIZE - 1);
    if (result == NWC24_ERR_NOT_FOUND) {
        return NWC24_OK;
    }
    if (result != NWC24_OK) {
        return result;
    }

    p = pWork;
    while (*p == '\t' || *p == ' ') {
        p++;
        i++;
    }

    if (*p == '1') {
        *mbOptOutFlag = TRUE;
    }

    p += 2;
    if (p[-1] != '-') {
        return NWC24_OK;
    }
    i += 2;

    while (i < NWC24i_STRING_WORK_SIZE) {
        digit = Util_xtoi(*p);
        if (digit < 0) {
            break;
        }

        value = (value << 4) | digit;
        p++;
        i++;
        digits++;

    }

    if (digits != 8) {
        result = NWC24_ERR_FORMAT;
    }

    *appId = value;

    return result;
}

NWC24Err NWC24ReadMsgFromAddr(const NWC24MsgObj* msg, char* addr,
                              u32 addrLen) {
    const NWC24MsgObjPrivate* pMsg = (const NWC24MsgObjPrivate*)msg;
    NWC24Err result;
    NWC24Err closeResult;
    NWC24MsgBoxId id;
    u32 flags;
    char* pWork;
    NWC24FileStream stream;
    NWC24File file;

    if (!NWC24IsMsgLibOpened() && !NWC24IsMsgLibOpenedByTool()) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }

    if (!(pMsg->type & MSG_OBJ_DELIVERING)) {
        return NWC24_ERR_PROTECTED;
    }

    pWork = NWC24WorkP->stringWork;
    Mail_memset(pWork, 0, NWC24i_STRING_WORK_SIZE);

    if (!(pMsg->type & MSG_OBJ_FOR_PUBLIC)) {
        return NWC24_ERR_NOT_SUPPORTED;
    }

    flags = pMsg->type;
    if (flags & MSG_OBJ_TO_SEND) {
        id = NWC24_MSGBOX_SEND;
        result = NWC24_OK;
    } else if (flags & MSG_OBJ_TO_RECV) {
        id = NWC24_MSGBOX_RECV;
        result = NWC24_OK;
    } else {
        result = NWC24_ERR_INVALID_VALUE;
    }

    if (result != NWC24_OK) {
        return result;
    }

    if (pMsg->unk_0x30.size == 0) {
        return NWC24_ERR_NULL;
    }

    if (result == NWC24_OK) {
        result = NWC24iMBoxOpenStoredMsg(id, pMsg->msgId, &file);
    }

    if (result != NWC24_OK) {
        return result;
    }

    result = NWC24FStreamInit(&stream, &file, 0, pMsg->length, pWork,
                              NWC24i_STRING_WORK_SIZE);
    if (result == NWC24_OK) {
        result = NWC24FStreamSeek(&stream, pMsg->unk_0x30.offset);
        if (result == NWC24_OK) {
            result = NWC24iExtractAddrSpec(&stream, pMsg->unk_0x30.size, 0,
                                           addr, addrLen);
        }
    }

    closeResult = NWC24iMBoxCloseMsg(&file);
    if (result == NWC24_OK) {
        result = closeResult;
    }

    return result;
}

NWC24Err NWC24ReadMsgSubject(const NWC24MsgObj* msg, char* subject,
                             u32 subjectLen) {
    const NWC24MsgObjPrivate* pMsg = (const NWC24MsgObjPrivate*)msg;
    NWC24Err result;
    NWC24Err closeResult;
    NWC24MsgBoxId id;
    u32 flags;
    u32 length;
    NWC24File file;

    if (!NWC24IsMsgLibOpened() && !NWC24IsMsgLibOpenedByTool()) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }

    if (!(pMsg->type & MSG_OBJ_DELIVERING)) {
        return NWC24_ERR_PROTECTED;
    }

    flags = pMsg->type;
    if (flags & MSG_OBJ_TO_SEND) {
        id = NWC24_MSGBOX_SEND;
        result = NWC24_OK;
    } else if (flags & MSG_OBJ_TO_RECV) {
        id = NWC24_MSGBOX_RECV;
        result = NWC24_OK;
    } else {
        result = NWC24_ERR_INVALID_VALUE;
    }

    if (result != NWC24_OK) {
        return result;
    }

    length = pMsg->subject.size;
    if (length == 0) {
        return NWC24_ERR_NULL;
    }

    if (result == NWC24_OK) {
        result = NWC24iMBoxOpenStoredMsg(id, pMsg->msgId, &file);
    }

    if (result != NWC24_OK) {
        return result;
    }

    if (length > subjectLen - 1) {
        length = subjectLen - 1;
    }

    NWC24FSeek(&file, pMsg->subject.offset, NWC24_SEEK_BEG);
    result = NWC24FRead(subject, length, &file);
    if (result == NWC24_OK) {
        subject[length] = '\0';
        if (pMsg->subject.size > subjectLen - 1) {
            result = NWC24_ERR_OVERFLOW;
        }
    }

    closeResult = NWC24iMBoxCloseMsg(&file);
    if (result == NWC24_OK) {
        result = closeResult;
    }

    return result;
}

NWC24Err NWC24ReadMsgText(const NWC24MsgObj* msg, char* text, u32 textLen,
                          NWC24Charset* charset, NWC24Encoding* encoding) {
    NWC24Err result;
    char* charsetStr = (char*)NWC24WorkP + 0x20;

    result = ReadMsgTextInternal(msg, text, textLen, charsetStr, 0x40,
                                 encoding);
    if (result == NWC24_OK) {
        result = NWC24ParseCharsetStr(charset, charsetStr);
    }

    return result;
}

NWC24Err NWC24ReadMsgTextEx(const NWC24MsgObj* msg, char* text, u32 textLen,
                            const char* name, u32 nameLen,
                            NWC24Charset* charset, NWC24Encoding* encoding) {
    NWC24Err result;
    NWC24Encoding enc;
    char* pName;
    char c;
    u32 i;

    result = ReadMsgTextInternal(msg, text, textLen, (char*)name, nameLen,
                                 &enc);
    if (result != NWC24_OK) {
        return result;
    }

    pName = (char*)name;
    for (i = 0; i < nameLen; i++) {
        c = pName[i];
        if (c == ' ' || c == '\r' || (c >= '\t' && c < '\v') || c == ';' ||
            c == '"') {
            pName[i] = '\0';
        }

        if (pName[i] == '\0') {
            break;
        }
    }

    return NWC24_OK;
}

static NWC24Err ReadMsgTextInternal(const NWC24MsgObj* msg, char* text,
                                    u32 textLen, char* name, u32 nameLen,
                                    NWC24Encoding* encoding) {
    const NWC24MsgObjPrivate* pMsg = (const NWC24MsgObjPrivate*)msg;
    NWC24Err retCode;
    NWC24Err result;
    NWC24Err closeResult;
    NWC24MsgBoxId id;
    u32 flags;
    u32 length;
    u32 decodeSize;
    char* pWork;
    NWC24File file;

    retCode = NWC24_OK;

    if (!NWC24IsMsgLibOpened() && !NWC24IsMsgLibOpenedByTool()) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }

    if (!(pMsg->type & MSG_OBJ_DELIVERING)) {
        return NWC24_ERR_PROTECTED;
    }

    *encoding = NWC24_ENC_7BIT;

    flags = pMsg->type;
    if (flags & MSG_OBJ_TO_SEND) {
        id = NWC24_MSGBOX_SEND;
        result = NWC24_OK;
    } else if (flags & MSG_OBJ_TO_RECV) {
        id = NWC24_MSGBOX_RECV;
        result = NWC24_OK;
    } else {
        result = NWC24_ERR_INVALID_VALUE;
    }

    if (result != NWC24_OK) {
        return result;
    }

    length = pMsg->textSize;
    if (length == 0) {
        length = pMsg->text.size;
    }
    if (length == 0) {
        return NWC24_ERR_NULL;
    }

    if (length > textLen - 1) {
        length = textLen - 1;
        retCode = NWC24_ERR_OVERFLOW;
    }

    if (result == NWC24_OK) {
        result = NWC24iMBoxOpenStoredMsg(id, pMsg->msgId, &file);
    }

    if (result != NWC24_OK) {
        return result;
    }

    Mail_memset(name, 0, nameLen);

    if (pMsg->unk_0x50.size >= nameLen) {
        result = NWC24_ERR_FORMAT;
    } else {
        if (pMsg->unk_0x50.size != 0) {
            NWC24FSeek(&file, pMsg->unk_0x50.offset, NWC24_SEEK_BEG);
            result = NWC24FRead(name, pMsg->unk_0x50.size, &file);
        }

        pWork = NWC24WorkP->stringWork;
        if (result == NWC24_OK && pMsg->unk_0x58.size != 0 &&
            pMsg->unk_0x58.size < 0x20) {
            Mail_memset(pWork, 0, 0x20);
            NWC24FSeek(&file, pMsg->unk_0x58.offset, NWC24_SEEK_BEG);
            result = NWC24FRead(pWork, pMsg->unk_0x58.size, &file);
            if (result == NWC24_OK) {
                result = NWC24ParseEncodingStr(encoding, pWork);
            }
        }

        if (result == NWC24_OK) {
            NWC24FSeek(&file, pMsg->text.offset, NWC24_SEEK_BEG);
            switch (*encoding) {
            case NWC24_ENC_7BIT:
            case NWC24_ENC_8BIT:
                result = NWC24FRead(text, length, &file);
                text[length] = '\0';
                break;

            case NWC24_ENC_BASE64:
                decodeSize = 0;
                result = ReadBase64Data(&file, &pMsg->text, (u8*)text, length,
                                        &decodeSize);
                if (result == NWC24_OK && decodeSize != pMsg->textSize) {
                    result = NWC24_ERR_FORMAT;
                }
                text[length] = '\0';
                break;

            case NWC24_ENC_QUOTED_PRINTABLE:
                result = ReadQPText(msg, &file, text, length);
                break;

            default:
                result = NWC24_ERR_NOT_SUPPORTED;
                text[0] = '\0';
                break;
            }
        }
    }

    closeResult = NWC24iMBoxCloseMsg(&file);
    if (result != NWC24_OK) {
        closeResult = result;
    }
    if (closeResult != NWC24_OK) {
        retCode = closeResult;
    }

    return retCode;
}

NWC24Err NWC24ReadMsgAttached(const NWC24MsgObj* msg, u32 attachIndex,
                              u8* attachData, u32 attachSize) {
    const NWC24MsgObjPrivate* pMsg = (const NWC24MsgObjPrivate*)msg;
    NWC24Err result;
    NWC24Err closeResult;
    NWC24MsgBoxId id;
    u32 flags;
    u32 decodeSize;
    NWC24File file;

    if (!NWC24IsMsgLibOpened() && !NWC24IsMsgLibOpenedByTool()) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }

    if (!(pMsg->type & MSG_OBJ_DELIVERING)) {
        return NWC24_ERR_PROTECTED;
    }

    if (attachIndex >= pMsg->numAttached) {
        return NWC24_ERR_NOT_FOUND;
    }

    flags = pMsg->type;
    if (flags & MSG_OBJ_TO_SEND) {
        id = NWC24_MSGBOX_SEND;
        result = NWC24_OK;
    } else if (flags & MSG_OBJ_TO_RECV) {
        id = NWC24_MSGBOX_RECV;
        result = NWC24_OK;
    } else {
        result = NWC24_ERR_INVALID_VALUE;
    }

    if (result != NWC24_OK) {
        return result;
    }

    if (pMsg->attached[attachIndex].size == 0) {
        return NWC24_ERR_NULL;
    }
    if (pMsg->attachedSize[attachIndex] == 0) {
        return NWC24_ERR_NULL;
    }

    if (result == NWC24_OK) {
        result = NWC24iMBoxOpenStoredMsg(id, pMsg->msgId, &file);
    }

    if (result != NWC24_OK) {
        return result;
    }

    decodeSize = 0;
    result = ReadBase64Data(&file, &pMsg->attached[attachIndex], attachData,
                            attachSize, &decodeSize);
    if (result == NWC24_OK && decodeSize != pMsg->attachedSize[attachIndex]) {
        result = NWC24_ERR_FORMAT;
    }

    closeResult = NWC24iMBoxCloseMsg(&file);
    if (result == NWC24_OK) {
        result = closeResult;
    }

    return result;
}

static NWC24Err ReadBase64Data(NWC24File* file, const NWC24Data* data,
                               u8* out, u32 outSize, u32* outLen) {
    char* pWork;
    NWC24Err result;
    u32 remaining;
    u32 offset;
    u32 written;
    u32 chunk;
    u32 decodeLen;
    u32 decodeSize;
    BOOL done;
    int i;

    pWork = NWC24WorkP->mainWork;

    remaining = data->size;
    offset = data->offset;
    written = 0;
    result = NWC24_OK;
    done = FALSE;

    while (remaining > 0 && !done) {
        chunk = remaining > NWC24i_STRING_WORK_SIZE
                    ? NWC24i_STRING_WORK_SIZE
                    : remaining;

        NWC24FSeek(file, offset, NWC24_SEEK_BEG);
        result = NWC24FRead(pWork, chunk, file);
        if (result != NWC24_OK) {
            break;
        }

        decodeLen = 0;
        for (i = 0; i < chunk; i++) {
            if (pWork[i] == '\r') {
                decodeLen = i;
            }
            if (pWork[i] == '=') {
                decodeLen = i + 1;
                done = TRUE;
                result = NWC24_OK;
                break;
            }
        }

        if (decodeLen == 0) {
            break;
        }

        result = NWC24Base64Decode((u8*)pWork, decodeLen, out, outSize - written,
                                   &decodeSize);
        if (result != NWC24_OK) {
            break;
        }

        offset += decodeLen;
        remaining -= decodeLen;
        written += decodeSize;
        out += decodeSize;
    }

    if (result == NWC24_OK) {
        *outLen = written;
    }

    return result;
}

static NWC24Err ReadQPText(const NWC24MsgObj* msg, NWC24File* file, char* text,
                           u32 textSize) {
    const NWC24MsgObjPrivate* pMsg = (const NWC24MsgObjPrivate*)msg;
    char* pWork;
    NWC24Err result;
    u32 remaining;
    u32 offset;
    u32 written;
    u32 chunk;
    u32 decLen;
    u32 encLen;

    pWork = NWC24WorkP->mainWork;

    remaining = pMsg->text.size;
    offset = pMsg->text.offset;
    written = 0;
    result = NWC24_OK;

    while (remaining > 0) {
        chunk = remaining > NWC24i_STRING_WORK_SIZE
                    ? NWC24i_STRING_WORK_SIZE
                    : remaining;

        NWC24FSeek(file, offset, NWC24_SEEK_BEG);
        result = NWC24FRead(pWork, chunk, file);
        if (result != NWC24_OK) {
            break;
        }

        encLen = chunk;
        if (chunk == NWC24i_STRING_WORK_SIZE) {
            if (pWork[chunk - 1] == '=') {
                encLen = chunk - 1;
            } else if (pWork[chunk - 2] == '=') {
                encLen = chunk - 2;
            }
        }

        result = NWC24DecodeQuotedPrintable(text, textSize - written, &decLen,
                                            (u8*)pWork, encLen, &encLen);
        if (result != NWC24_OK && result != NWC24_ERR_OVERFLOW) {
            break;
        }

        written += decLen;
        text += decLen;

        if (result == NWC24_ERR_OVERFLOW) {
            break;
        }

        offset += encLen;
        remaining -= encLen;
    }

    *text = '\0';

    if (result == NWC24_OK && written > pMsg->textSize) {
        result = NWC24_ERR_FORMAT;
    }

    return result;
}
