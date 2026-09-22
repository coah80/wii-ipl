#include <private/nwc24.h>
#include <revolution/nwc24.h>

#define ALT_NAME_MAX 35
#define SMTP_LINE_MAX 1000

typedef enum {
    MSG_OBJ_FOR_RECIPIENT = (1 << 0),
    MSG_OBJ_FOR_PUBLIC = (1 << 1),
    MSG_OBJ_FOR_APP = (1 << 2),
    MSG_OBJ_FOR_MENU = (1 << 3),
    MSG_OBJ_INITIALIZED = (1 << 8),
    MSG_OBJ_DELIVERING = (1 << 9)
} NWC24MsgObjFlags;

NWC24Err NWC24InitMsgObj(NWC24MsgObj* msg, NWC24MsgType type) {
    u32 i;
    NWC24MsgObjPrivate* msgObj = (NWC24MsgObjPrivate*)msg;

    Mail_memset(msgObj, 0, sizeof(NWC24MsgObj));

    msgObj->msgId = 0;
    msgObj->type = MSG_OBJ_INITIALIZED;
    msgObj->appId = NWC24GetAppId();
    msgObj->ledPattern = 0;
    msgObj->tag = 0;
    msgObj->groupId = NWC24GetGroupId();

    switch (type) {
        case NWC24_MSGTYPE_RVL_MENU_SHARED:
            msgObj->type |= MSG_OBJ_FOR_RECIPIENT | MSG_OBJ_FOR_APP | MSG_OBJ_FOR_MENU;
            break;
        case NWC24_MSGTYPE_RVL:
            msgObj->type |= MSG_OBJ_FOR_RECIPIENT | MSG_OBJ_FOR_APP;
            break;
        case NWC24_MSGTYPE_RVL_MENU:
            msgObj->type |= MSG_OBJ_FOR_RECIPIENT | MSG_OBJ_FOR_MENU;
            break;
        case NWC24_MSGTYPE_RVL_HIDDEN:
            msgObj->type |= MSG_OBJ_FOR_RECIPIENT;
            break;
        case NWC24_MSGTYPE_PUBLIC:
            msgObj->type |= MSG_OBJ_FOR_PUBLIC;
            break;
        default:
            return NWC24_ERR_INVALID_VALUE;
    }

    msgObj->unk_0x28 = 0;
    msgObj->type |= 0x200000;
    msgObj->unk_0x2C = 0;

    NWC24GetMyUserId(&msgObj->fromId);
    msgObj->numTo = 0;

    for (i = 0; i < NWC24_MSG_RECIPIENT_MAX; i++) {
        if (type == NWC24_MSGTYPE_PUBLIC) {
            NWC24Data_Init(&msgObj->toAddrs[i]);
        } else {
            msgObj->toIds[i] = 0;
        }
    }

    NWC24Data_Init(&msgObj->subject);
    NWC24Data_Init(&msgObj->text);
    msgObj->charset = NWC24_US_ASCII;
    msgObj->encoding = NWC24_ENC_7BIT;
    msgObj->numAttached = 0;

    for (i = 0; i < NWC24_MSG_ATTACHMENT_MAX; i++) {
        NWC24Data_Init(&msgObj->attached[i]);
        msgObj->attachedSize[i] = 0;
        msgObj->attachedType[i] = NWC24_TEXT_PLAIN;
    }

    NWC24Data_Init(&msgObj->unk_0x30);
    NWC24Data_Init(&msgObj->unk_0x38);
    NWC24Data_Init(&msgObj->unk_0x50);
    NWC24Data_Init(&msgObj->unk_0x58);
    NWC24Data_Init(&msgObj->unk_0xD0);
    NWC24Data_Init(&msgObj->faceData);
    NWC24Data_Init(&msgObj->altName);

    msgObj->msgBoardFlags.raw = 0;
    msgObj->dwcId = 0;
    msgObj->iconNew = (1 << 31);

    return NWC24_OK;
}

NWC24Err NWC24SetMsgToId(NWC24MsgObj* msg, NWC24UserId id) {
    NWC24MsgObjPrivate* msgObj = (NWC24MsgObjPrivate*)msg;
    if (!(msgObj->type & MSG_OBJ_INITIALIZED) || (msgObj->type & MSG_OBJ_DELIVERING)) {
        return NWC24_ERR_PROTECTED;
    }

    if (!(msgObj->type & MSG_OBJ_FOR_RECIPIENT)) {
        return NWC24_ERR_NOT_SUPPORTED;
    }

    if (msgObj->numTo >= NWC24_MSG_RECIPIENT_MAX) {
        return NWC24_ERR_FULL;
    }

    msgObj->toIds[msgObj->numTo] = id;
    msgObj->numTo++;

    return NWC24_OK;
}

NWC24Err NWC24SetMsgToAddr(NWC24MsgObj* msg, const char* addr, u32 length) {
    NWC24MsgObjPrivate* msgObj = (NWC24MsgObjPrivate*)msg;

    if (!(msgObj->type & MSG_OBJ_INITIALIZED) || (msgObj->type & MSG_OBJ_DELIVERING)) {
        return NWC24_ERR_PROTECTED;
    }

    if (addr == NULL || addr[0] == '\0') {
        return NWC24_ERR_NULL;
    }

    if (!(msgObj->type & MSG_OBJ_FOR_PUBLIC)) {
        return NWC24_ERR_NOT_SUPPORTED;
    }

    if (msgObj->numTo >= NWC24_MSG_RECIPIENT_MAX) {
        return NWC24_ERR_FULL;
    }

    if (length >= NWC24_MSG_SUBJECT_LENGTH) {
        return NWC24_ERR_OVERFLOW;
    }

    if (addr[length] != '\0') {
        return NWC24_ERR_STRING_END;
    }

    NWC24Data_SetDataP(&msgObj->toAddrs[msgObj->numTo], addr, length);
    msgObj->numTo++;
    return NWC24_OK;
}

NWC24Err NWC24SetMsgSubject(NWC24MsgObj* msg, const char* subject, u32 length) {
    NWC24MsgObjPrivate* msgObj = (NWC24MsgObjPrivate*)msg;

    if (!(msgObj->type & MSG_OBJ_INITIALIZED) || (msgObj->type & MSG_OBJ_DELIVERING)) {
        return NWC24_ERR_PROTECTED;
    }

    if (subject == NULL || subject[0] == '\0') {
        return NWC24_ERR_NULL;
    }

    if (subject[length] != '\0') {
        return NWC24_ERR_STRING_END;
    }

    NWC24Data_SetDataP(&msgObj->subject, subject, length);
    return NWC24_OK;
}

NWC24Err NWC24SetMsgText(NWC24MsgObj* msg, const char* text, u32 len, NWC24Charset charset, NWC24Encoding encoding) {
    NWC24MsgObjPrivate* msgObj = (NWC24MsgObjPrivate*)msg;

    if (!(msgObj->type & MSG_OBJ_INITIALIZED) || (msgObj->type & MSG_OBJ_DELIVERING)) {
        return NWC24_ERR_PROTECTED;
    }

    if (NWC24GetCharsetStr(charset) == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (NWC24GetEncodingStr(encoding) == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (text == NULL) {
        NWC24Data_Init(&msgObj->text);
        return NWC24_OK;
    }

    if (encoding == NWC24_ENC_8BIT && (msgObj->type & MSG_OBJ_FOR_PUBLIC)) {
        return NWC24_ERR_NOT_SUPPORTED;
    }

    // Lines are limited to at most 1000 characters
    if (encoding == NWC24_ENC_7BIT) {
        u32 lineLength = 0;
        const char* it;
        const char* end = text + len;
        for (it = text; it < end; it++) {
            if (it[0] == '\r' && it[1] == '\n') {
                lineLength = 0;
                it++;
            }
            // Include "\r\n" in line length
            else if (++lineLength > SMTP_LINE_MAX - 2) {
                return NWC24_ERR_FORMAT;
            }
        }
    }

    NWC24Data_SetDataP(&msgObj->text, text, len);
    msgObj->charset = charset;
    msgObj->encoding = encoding;
    return NWC24_OK;
}

NWC24Err NWC24SetMsgAttached(NWC24MsgObj* msg, const void* attachData, u32 attachSize, NWC24MIMEType type) {
    NWC24MsgObjPrivate* msgObj = (NWC24MsgObjPrivate*)msg;
    u32 i;
    u32 totalSize = 0;

    if (!(msgObj->type & MSG_OBJ_INITIALIZED) || (msgObj->type & MSG_OBJ_DELIVERING)) {
        return NWC24_ERR_PROTECTED;
    }

    if (attachData == NULL || attachSize == 0) {
        return NWC24_ERR_NULL;
    }

    if (msgObj->numAttached >= NWC24_MSG_ATTACHMENT_MAX) {
        return NWC24_ERR_FULL;
    }

    if (NWC24GetMIMETypeStr(type) == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if ((msgObj->type & MSG_OBJ_FOR_PUBLIC) && type != NWC24_TEXT_PLAIN && type != NWC24_TEXT_HTML && type != NWC24_IMAGE_JPEG &&
        type != NWC24_APPLICATION_OCTET_STREAM) {
        return NWC24_ERR_NOT_SUPPORTED;
    }

    if (type == NWC24_X_WII_MINIDATA && attachSize > 0x80) {
        return NWC24_ERR_INVALID_VALUE;
    }

    for (i = 0; i < msgObj->numAttached; i++) {
        totalSize += msgObj->attachedSize[i];
    }

    totalSize += attachSize;
    if (totalSize >= 0x245B0) {
        return NWC24_ERR_OVERFLOW;
    }

    NWC24Data_SetDataP(&msgObj->attached[msgObj->numAttached], attachData, attachSize);
    msgObj->attachedSize[msgObj->numAttached] = attachSize;
    msgObj->attachedType[msgObj->numAttached] = type;
    msgObj->numAttached++;
    msgObj->type |= 0x10000;

    return NWC24_OK;
}

NWC24Err NWC24SetMsgFaceData(NWC24MsgObj* msg, const void* faceData) {
    NWC24MsgObjPrivate* msgObj = (NWC24MsgObjPrivate*)msg;

    if (!(msgObj->type & MSG_OBJ_INITIALIZED) || (msgObj->type & MSG_OBJ_DELIVERING)) {
        return NWC24_ERR_PROTECTED;
    }

    if (msgObj->faceData.size != 0) {
        return NWC24_ERR_FULL;
    }

    NWC24Data_SetDataP(&msgObj->faceData, faceData, NWC24_FACE_DATA_SIZE);
    return NWC24_OK;
}

NWC24Err NWC24SetMsgMBNoReply(NWC24MsgObj* msg, BOOL mbNoReplyFlag) {
    NWC24MsgObjPrivate* msgObj = (NWC24MsgObjPrivate*)msg;

    if (!(msgObj->type & MSG_OBJ_INITIALIZED) || (msgObj->type & MSG_OBJ_DELIVERING)) {
        return NWC24_ERR_PROTECTED;
    }

    if (!(msgObj->type & MSG_OBJ_FOR_MENU)) {
        return NWC24_ERR_NOT_SUPPORTED;
    }

    if (mbNoReplyFlag) {
        msgObj->msgBoardFlags.noreply = 1;
    } else {
        msgObj->msgBoardFlags.noreply = 0;
    }

    return NWC24_OK;
}

NWC24Err NWC24SetMsgMBRegDate(NWC24MsgObj* msg, u16 year, u8 month, u8 day) {
    NWC24MsgObjPrivate* msgObj = (NWC24MsgObjPrivate*)msg;
    NWC24Err err;

    if (!(msgObj->type & MSG_OBJ_INITIALIZED) || (msgObj->type & MSG_OBJ_DELIVERING)) {
        return NWC24_ERR_PROTECTED;
    }

    if (!(msgObj->type & MSG_OBJ_FOR_MENU)) {
        return NWC24_ERR_NOT_SUPPORTED;
    }

    if (year < 2000 || year > 2035) {
        return NWC24_ERR_INVALID_VALUE;
    }

    err = NWC24iIsValidDate(year, month, day);
    if (err != NWC24_OK) {
        return err;
    }

    msgObj->msgBoardFlags.raw = (msgObj->msgBoardFlags.raw & 0xFFFF0000) |
                                ((((year - 2000) << 9) | (month << 5) | day) & 0xFFFF);
    return NWC24_OK;
}

NWC24Err NWC24SetMsgAppId(NWC24MsgObj* msg, u32 appId) {
    NWC24MsgObjPrivate* msgObj = (NWC24MsgObjPrivate*)msg;

    if (!(msgObj->type & MSG_OBJ_INITIALIZED) || (msgObj->type & MSG_OBJ_DELIVERING)) {
        return NWC24_ERR_PROTECTED;
    }

    if (!NWC24IsMsgLibOpenedByTool() && NWC24GetAppId() != 0x48414541) {
        return NWC24_ERR_PROTECTED;
    }

    msgObj->appId = appId;
    return NWC24_OK;
}

NWC24Err NWC24SetMsgLedPattern(NWC24MsgObj* msg, int ledPattern) {
    NWC24MsgObjPrivate* msgObj = (NWC24MsgObjPrivate*)msg;

    if (!(msgObj->type & MSG_OBJ_INITIALIZED) || (msgObj->type & MSG_OBJ_DELIVERING)) {
        return NWC24_ERR_PROTECTED;
    }

    if (ledPattern == 0) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (!(msgObj->type & MSG_OBJ_FOR_RECIPIENT) || !(msgObj->type & MSG_OBJ_FOR_MENU)) {
        return NWC24_ERR_NOT_SUPPORTED;
    }

    if (msgObj->ledPattern != 0 && !(msgObj->ledPattern & (1 << 18))) {
        return NWC24_ERR_NOT_SUPPORTED;
    }

    if (!NWC24IsMsgLibOpenedByTool() && NWC24GetAppId() != 0x48414541 && (u32)ledPattern >= 0x4000) {
        return NWC24_ERR_INVALID_VALUE;
    }

    msgObj->ledPattern = ledPattern | (1 << 18);
    return NWC24_OK;
}

NWC24Err NWC24GetMsgType(const NWC24MsgObj* msg, NWC24MsgType* type) {
    const NWC24MsgObjPrivate* msgObj = (const NWC24MsgObjPrivate*)msg;
    u32 flags = msgObj->type;

    if (flags & MSG_OBJ_FOR_RECIPIENT) {
        if (flags & MSG_OBJ_FOR_APP) {
            if (flags & MSG_OBJ_FOR_MENU) {
                *type = NWC24_MSGTYPE_RVL_MENU_SHARED;
            } else {
                *type = NWC24_MSGTYPE_RVL;
            }
        } else if (flags & MSG_OBJ_FOR_MENU) {
            *type = NWC24_MSGTYPE_RVL_MENU;
        } else {
            *type = NWC24_MSGTYPE_RVL_HIDDEN;
        }
    } else if (flags & MSG_OBJ_FOR_PUBLIC) {
        *type = NWC24_MSGTYPE_PUBLIC;
    } else {
        return NWC24_ERR_INVALID_VALUE;
    }

    return NWC24_OK;
}

NWC24Err NWC24GetMsgSubjectSize(const NWC24MsgObj* msg, u32* subjectSize) {
    const NWC24MsgObjPrivate* msgObj = (const NWC24MsgObjPrivate*)msg;
    u32 size = msgObj->subject.size;
    if (size != 0) {
        *subjectSize = size + 1;
    } else {
        *subjectSize = 0;
    }
    return NWC24_OK;
}

NWC24Err NWC24GetMsgTextSize(const NWC24MsgObj* msg, u32* textSize) {
    const NWC24MsgObjPrivate* msgObj = (const NWC24MsgObjPrivate*)msg;
    u32 size = msgObj->textSize;
    if (size != 0) {
        *textSize = size + 1;
    } else {
        size = msgObj->text.size;
        if (size != 0) {
            *textSize = size + 1;
        } else {
            *textSize = 0;
        }
    }
    return NWC24_OK;
}

NWC24Err NWC24GetMsgNumAttached(const NWC24MsgObj* msg, u32* numAttach) {
    const NWC24MsgObjPrivate* msgObj = (const NWC24MsgObjPrivate*)msg;
    u8 numAttached = msgObj->numAttached;
    *numAttach = numAttached;
    if (numAttached > NWC24_MSG_ATTACHMENT_MAX) {
        return NWC24_ERR_BROKEN;
    }
    return NWC24_OK;
}

NWC24Err NWC24GetMsgAttachedSize(const NWC24MsgObj* msg, u32 attachIndex, u32* attachSize) {
    const NWC24MsgObjPrivate* msgObj = (const NWC24MsgObjPrivate*)msg;

    if (attachIndex >= NWC24_MSG_ATTACHMENT_MAX || attachIndex >= msgObj->numAttached) {
        return NWC24_ERR_INVALID_VALUE;
    }

    *attachSize = msgObj->attachedSize[attachIndex];
    return NWC24_OK;
}

NWC24Err NWC24GetMsgAttachedType(const NWC24MsgObj* msg, u32 attachIndex, NWC24MIMEType* attachType) {
    const NWC24MsgObjPrivate* msgObj = (const NWC24MsgObjPrivate*)msg;
    u32 flags;
    NWC24MIMEType type;

    if (attachIndex >= NWC24_MSG_ATTACHMENT_MAX || attachIndex >= msgObj->numAttached) {
        return NWC24_ERR_INVALID_VALUE;
    }

    flags = msgObj->type;
    type = msgObj->attachedType[attachIndex];
    *attachType = type;
    if ((flags & MSG_OBJ_FOR_PUBLIC) && !(flags & (1 << 12))) {
        if (type != NWC24_TEXT_PLAIN && type != NWC24_TEXT_HTML && type != NWC24_IMAGE_JPEG && type != NWC24_APPLICATION_OCTET_STREAM) {
            *attachType = 0;
        }
    }

    return NWC24_OK;
}

NWC24Err NWC24GetMsgAppId(const NWC24MsgObj* msg, u32* appId) {
    const NWC24MsgObjPrivate* msgObj = (const NWC24MsgObjPrivate*)msg;
    *appId = msgObj->appId;
    return NWC24_OK;
}

NWC24Err NWC24GetMsgGroupId(const NWC24MsgObj* msg, u16* groupId) {
    const NWC24MsgObjPrivate* msgObj = (const NWC24MsgObjPrivate*)msg;
    *groupId = msgObj->groupId;
    return NWC24_OK;
}

NWC24Err NWC24GetMsgFromId(const NWC24MsgObj* msg, NWC24UserId* fromId) {
    const NWC24MsgObjPrivate* msgObj = (const NWC24MsgObjPrivate*)msg;

    if (!(msgObj->type & MSG_OBJ_FOR_RECIPIENT)) {
        return NWC24_ERR_NOT_SUPPORTED;
    }

    *fromId = msgObj->fromId;
    return NWC24_OK;
}

NWC24Err NWC24GetMsgDate(const NWC24MsgObj* msg, OSCalendarTime* msgDate) {
    const NWC24MsgObjPrivate* msgObj = (const NWC24MsgObjPrivate*)msg;

    NWC24iMinutesToOSCalendarTime(msgDate, msgObj->unk_0x28);
    return NWC24_OK;
}

NWC24Err NWC24GetMsgIconNewSign(const NWC24MsgObj* msg, u32* iconNewSign) {
    const NWC24MsgObjPrivate* msgObj = (const NWC24MsgObjPrivate*)msg;
    u32 flags = msgObj->type;
    u32 iconNew;

    if ((flags & MSG_OBJ_FOR_MENU) || (flags & MSG_OBJ_FOR_PUBLIC)) {
        return NWC24_ERR_NOT_FOUND;
    }

    iconNew = msgObj->iconNew;
    *iconNewSign = iconNew;
    if (iconNew == 0 || iconNew == (1 << 31)) {
        return NWC24_ERR_NOT_FOUND;
    }

    return NWC24_OK;
}
