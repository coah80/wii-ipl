#define NWC24_MSG_COMMIT
#include <private/nwc24.h>
#include <revolution/net/NETMisc.h>
#include <revolution/nwc24.h>

static char MultiPartDivider[64];
BOOL LoopBackEnable[2] = {TRUE, FALSE};
static NWC24File* m_pFile;

static NWC24Err NWC24CommitMsgInternal(NWC24MsgObjPrivate* msg, NWC24MBoxType type);
static NWC24Err CheckMsgObject(const NWC24MsgObjPrivate* msg);
static NWC24Err CheckMsgBoxSpace(const NWC24MsgObjPrivate* msg, NWC24MBoxType type);
static NWC24Err SynthesizeAddrStr(const NWC24Data* address, u32 type, char* dest, s32 capacity, u32* length);
static NWC24Err WriteSMTP_MAILFROM(NWC24MsgObjPrivate* msg);
static NWC24Err WriteSMTP_RCPTTO(NWC24MsgObjPrivate* msg);
static NWC24Err WriteFromField(NWC24MsgObjPrivate* msg);
static NWC24Err WriteToField(NWC24MsgObjPrivate* msg);
static NWC24Err WriteDateField(NWC24MsgObjPrivate* msg);
static NWC24Err WriteXWiiAppIdField(NWC24MsgObjPrivate* msg);
static NWC24Err WriteXWiiFaceField(NWC24MsgObjPrivate* msg);
static NWC24Err WriteXWiiAltNameField(NWC24MsgObjPrivate* msg);
static NWC24Err WriteMIMEAttachHeader(NWC24MsgObjPrivate* msg, u32 index);
static NWC24Err WriteContentTypeField(NWC24MsgObjPrivate* msg);
static NWC24Err WritePlainText(NWC24MsgObjPrivate* msg);
static NWC24Err WriteBase64Data(const u8* data, s32 size, u32* length);
static NWC24Err WriteQPData(const u8* data, s32 size, u32* length);
NWC24Err NWC24iMBoxOpenNewMsg(NWC24MBoxType type, NWC24File* file, u32* id);
NWC24Err NWC24iMBoxCloseMsg(NWC24File* file);
NWC24Err NWC24iMBoxAddMsgObj(NWC24MBoxType type, NWC24MsgObjPrivate* msg);
NWC24Err NWC24iMBoxCancelMsg(NWC24File* file, NWC24MBoxType type, u32 id);
NWC24Err NWC24iMBoxFlushHeader(NWC24MBoxType type);
NWC24Err NWC24iMBoxCheck(NWC24MBoxType type, u32 size);
NWC24Err NWC24iDateToMinutes(u32* minutes, const NWC24Date* date);
NWC24Err NWC24iMinutesToDate(NWC24Date* date, u32 minutes);

static inline NWC24Err WriteString(NWC24MsgObjPrivate* msg, char* buffer) {
    NWC24Err err;
    s32 length;
    length = Mail_strlen(buffer);
    err = NWC24FWrite(buffer, length, m_pFile);
    if (err == NWC24_OK)
        msg->length += length;
    return err;
}

#define CHECK_WRITE(operation)                                                                                                                       \
    do {                                                                                                                                             \
        err = (operation);                                                                                                                           \
        if (err != NWC24_OK) {                                                                                                                       \
            NWC24FClose(&file);                                                                                                                      \
            result = err;                                                                                                                            \
            goto finish;                                                                                                                             \
        }                                                                                                                                            \
    } while (0)

static inline NWC24Err WriteSubjectField(NWC24MsgObjPrivate* msg) {
    char* buffer = NWC24WorkP->stringWork;
    s32 length;
    NWC24Err err;
    if (msg->subject.size == 0)
        return NWC24_ERR_NULL;
    Mail_memset(buffer, 0, 1024);
    Mail_strcpy(buffer, "Subject: ");
    Mail_strncat(buffer, msg->subject.ptr, 1021);
    Mail_strncat(buffer, "\r\n", 1024);
    length = STD_strnlen(buffer, 1024);
    err = NWC24FWrite(buffer, length, m_pFile);
    if (err == NWC24_OK)
        msg->length += length;
    return err;
}

static inline NWC24Err WriteSMTPData(NWC24MsgObjPrivate* msg, const char* text) {
    char* buffer = NWC24WorkP->stringWork;
    s32 length;
    NWC24Err err;
    Mail_strcpy(buffer, text);
    length = Mail_strlen(buffer);
    err = NWC24FWrite(buffer, length, m_pFile);
    if (err == NWC24_OK)
        msg->length += 6;
    return err;
}

static inline NWC24Err WriteCmdField(NWC24MsgObjPrivate* msg) {
    char* buffer;
    s32 length;
    NWC24Err err;
    if (msg->ledPattern == 0)
        return NWC24_OK;
    buffer = NWC24WorkP->stringWork;
    Mail_memset(buffer, 0, 1024);
    Mail_sprintf(buffer, "X-Wii-Cmd: %08X\r\n", msg->ledPattern);
    length = Mail_strlen(buffer);
    err = NWC24FWrite(buffer, length, m_pFile);
    if (err == NWC24_OK)
        msg->length += length;
    return err;
}

static inline NWC24Err WriteTagField(NWC24MsgObjPrivate* msg) {
    char* buffer;
    s32 length;
    NWC24Err err;
    if (msg->tag == 0)
        return NWC24_OK;
    buffer = NWC24WorkP->stringWork;
    Mail_memset(buffer, 0, 1024);
    Mail_sprintf(buffer, "X-Wii-Tag: %08X\r\n", msg->tag);
    length = Mail_strlen(buffer);
    err = NWC24FWrite(buffer, length, m_pFile);
    if (err == NWC24_OK)
        msg->length += length;
    return err;
}

static inline NWC24Err WriteDWCIdField(NWC24MsgObjPrivate* msg) {
    char* buffer;
    s32 length;
    NWC24Err err;
    if (!(msg->type & 0x2000))
        return NWC24_OK;
    buffer = NWC24WorkP->stringWork;
    Mail_memset(buffer, 0, 1024);
    Mail_sprintf(buffer, "X-Wii-DWCId: %08X\r\n", msg->dwcId);
    length = Mail_strlen(buffer);
    err = NWC24FWrite(buffer, length, m_pFile);
    if (err == NWC24_OK)
        msg->length += length;
    return err;
}

static inline NWC24Err WriteIconNewField(NWC24MsgObjPrivate* msg) {
    char* buffer;
    s32 length;
    NWC24Err err;
    if (msg->iconNew == 0 || msg->iconNew == 0x80000000)
        return NWC24_OK;
    buffer = NWC24WorkP->stringWork;
    Mail_memset(buffer, 0, 1024);
    Mail_sprintf(buffer, "X-Wii-IconNew: %08X\r\n", msg->iconNew);
    length = Mail_strlen(buffer);
    err = NWC24FWrite(buffer, length, m_pFile);
    if (err == NWC24_OK)
        msg->length += length;
    return err;
}

static inline NWC24Err WriteMessageIdField(NWC24MsgObjPrivate* msg) {
    char* buffer = NWC24WorkP->stringWork;
    const char* domain;
    NWC24UserId myId;
    char idText[32];
    NWC24Err err;
    s32 length;
    domain = NWC24GetAccountDomain();
    NWC24GetMyUserId(&myId);
    Mail_memset(buffer, 0, 1024);
    Mail_strcpy(buffer, "Message-Id: <");
    Mail_memset(idText, 0, 32);
    Mail_sprintf(idText, "%05X%08X%08X%08X", msg->msgId, (u32)(myId >> 32), (u32)myId, msg->date);
    Mail_strcat(buffer, idText);
    Mail_strcat(buffer, domain);
    Mail_strcat(buffer, ">\r\n");
    length = Mail_strlen(buffer);
    err = NWC24FWrite(buffer, length, m_pFile);
    if (err == NWC24_OK)
        msg->length += length;
    return err;
}

NWC24Err NWC24CommitMsg(NWC24MsgObj* object) {
    BOOL loopback = FALSE;
    NWC24MsgObjPrivate* msg = (NWC24MsgObjPrivate*)object;
    NWC24UserId myId;
    if (!NWC24IsMsgLibOpened() && !NWC24IsMsgLibOpenedByTool())
        return NWC24_ERR_LIB_NOT_OPENED;
    if (!(msg->type & 0x100) || (msg->type & 0x200))
        return NWC24_ERR_PROTECTED;
    if (LoopBackEnable[0] && (msg->type & 1)) {
        NWC24GetMyUserId(&myId);
        if (msg->numTo == 1 && msg->toIds[0] == myId)
            loopback = TRUE;
    }
    return NWC24CommitMsgInternal(msg, loopback);
}

static inline NWC24Err WriteMBNoReplyField(NWC24MsgObjPrivate* msg) {
    u32 flags = msg->msgBoardFlags.raw & 0x80000000;
    char* buffer;
    s32 length;
    NWC24Err err;
    if (!flags)
        return NWC24_OK;
    buffer = NWC24WorkP->stringWork;
    Mail_memset(buffer, 0, 1024);
    Mail_strcpy(buffer, "X-Wii-MB-NoReply: -\r\n");
    length = 21;
    err = NWC24FWrite(buffer, length, m_pFile);
    if (err == NWC24_OK)
        msg->length += length;
    return err;
}

typedef struct {
    u32 flags;
    char* buffer;
} MBFieldWork;

static inline NWC24Err WriteMBRegDateField(NWC24MsgObjPrivate* msg) {
    MBFieldWork field;
    NWC24Err err;
    s32 length;
    field.flags = msg->msgBoardFlags.raw & 0xFFFF;
    if (!field.flags)
        return NWC24_OK;
    field.buffer = NWC24WorkP->stringWork;
    Mail_memset(field.buffer, 0, 1024);
    Mail_sprintf(field.buffer, "X-Wii-MB-RegDate: %04X\r\n", field.flags);
    length = STD_strnlen(field.buffer, 1024);
    err = NWC24FWrite(field.buffer, length, m_pFile);
    if (err == NWC24_OK)
        msg->length += length;
    return err;
}

static inline NWC24Err WriteMBDelayField(NWC24MsgObjPrivate* msg) {
    MBFieldWork field;
    NWC24Err err;
    s32 length;
    field.flags = msg->msgBoardFlags.raw & 0xFF0000;
    if (!field.flags)
        return NWC24_OK;
    field.buffer = NWC24WorkP->stringWork;
    Mail_memset(field.buffer, 0, 1024);
    Mail_sprintf(field.buffer, "X-Wii-MB-Delay: %02X\r\n", field.flags >> 16);
    length = STD_strnlen(field.buffer, 1024);
    err = NWC24FWrite(field.buffer, length, m_pFile);
    if (err == NWC24_OK)
        msg->length += length;
    return err;
}

static inline NWC24Err WriteExtraFields(NWC24MsgObjPrivate* msg) {
    NWC24Err err;
    if (msg->extraData.size == 0)
        return NWC24_OK;
    err = NWC24FWrite(msg->extraData.ptr, msg->extraData.size, m_pFile);
    if (err == NWC24_OK)
        msg->length += msg->extraData.size;
    return err;
}

static NWC24Err NWC24CommitMsgInternal(NWC24MsgObjPrivate* msg, NWC24MBoxType type) {
    NWC24File file;
    NWC24Data attached[2];
    NWC24Data subject;
    NWC24Data text;
    u32 id, encodedLength;
    s32 initIndex;
    u32 index;
    char* buffer;
    NWC24Err result, err;
    NWC24Data_Init(&subject);
    NWC24Data_Init(&text);
    for (initIndex = 0; initIndex < 2; ++initIndex)
        NWC24Data_Init(&attached[initIndex]);
    NWC24iSetErrorCode(0);
    result = CheckMsgObject(msg);
    if (result != NWC24_OK)
        goto report;
    result = CheckMsgBoxSpace(msg, type);
    if (result != NWC24_OK)
        goto report;
    err = NWC24iMBoxOpenNewMsg(type, &file, &id);
    if (err != NWC24_OK) {
        result = err;
        goto finish;
    }
    {
        msg->msgId = id;
        msg->length = 0;
        m_pFile = &file;
        if (type == NWC24_MBOX_TYPE_SEND) {
            CHECK_WRITE(WriteSMTP_MAILFROM(msg));
            CHECK_WRITE(WriteSMTP_RCPTTO(msg));
            CHECK_WRITE(WriteSMTPData(msg, "DATA\r\n"));
        }
        CHECK_WRITE(WriteDateField(msg));
        CHECK_WRITE(WriteFromField(msg));
        CHECK_WRITE(WriteToField(msg));
        CHECK_WRITE(WriteMessageIdField(msg));
        subject.ptr = (const void*)(msg->length + 9);
        err = WriteSubjectField(msg);
        if (err == NWC24_OK)
            subject.size = msg->length - (u32)subject.ptr - 2;
        else if (err == NWC24_ERR_NULL) {
            err = NWC24_OK;
            subject.ptr = NULL;
        }
        if (err != NWC24_OK) {
            NWC24FClose(&file);
            result = err;
            goto finish;
        }
        if (msg->type & 1) {
            CHECK_WRITE(WriteXWiiAppIdField(msg));
            CHECK_WRITE(WriteCmdField(msg));
            CHECK_WRITE(WriteTagField(msg));
            CHECK_WRITE(WriteDWCIdField(msg));
            CHECK_WRITE(WriteXWiiAltNameField(msg));
            CHECK_WRITE(WriteXWiiFaceField(msg));
            CHECK_WRITE(WriteIconNewField(msg));
            if (msg->msgBoardFlags.raw != 0) {
                CHECK_WRITE(WriteMBNoReplyField(msg));
                CHECK_WRITE(WriteMBRegDateField(msg));
                CHECK_WRITE(WriteMBDelayField(msg));
            }
        }
        CHECK_WRITE(WriteExtraFields(msg));
        Mail_memset(MultiPartDivider, 0, 40);
        Mail_sprintf(MultiPartDivider, "Boundary-NWC24-%08X%05X", msg->date, msg->msgId);
        buffer = NWC24WorkP->stringWork;
        Mail_memset(buffer, 0, 1024);
        Mail_strcpy(buffer, "MIME-Version: 1.0\r\n");
        if (msg->type & 0x10000) {
            Mail_strcat(buffer, "Content-Type: multipart/mixed;\r\n boundary=\"");
            Mail_strcat(buffer, MultiPartDivider);
            Mail_strcat(buffer, "\"\r\n");
        }
        CHECK_WRITE(WriteString(msg, buffer));
        if (msg->type & 0x10000) {
            msg->flags = msg->length;
            buffer = NWC24WorkP->stringWork;
            Mail_memset(buffer, 0, 1024);
            Mail_sprintf(buffer, "\r\n--%s", MultiPartDivider);
            Mail_strcat(buffer, "\r\n\0");
            CHECK_WRITE(WriteString(msg, buffer));
        }
        CHECK_WRITE(WriteContentTypeField(msg));
        if (!(msg->type & 0x10000))
            msg->flags = msg->length;
        text.ptr = (const void*)msg->length;
        { NWC24Err textResult = WritePlainText(msg);
        err = textResult == NWC24_ERR_NULL ? NWC24_OK : textResult; }
        if (err != NWC24_OK) {
            NWC24FClose(&file);
            result = err;
            goto finish;
        }
        text.size = msg->length - (u32)text.ptr;
        for (index = 0; index < msg->numAttached; ++index) {
            buffer = NWC24WorkP->stringWork;
            Mail_memset(buffer, 0, 1024);
            Mail_sprintf(buffer, "\r\n--%s", MultiPartDivider);
            Mail_strcat(buffer, "\r\n\0");
            CHECK_WRITE(WriteString(msg, buffer));
            CHECK_WRITE(WriteMIMEAttachHeader(msg, index));
            attached[index].ptr = (const void*)msg->length;
            err = WriteBase64Data(msg->attached[index].ptr, msg->attached[index].size, &encodedLength);
            if (err == NWC24_OK)
                msg->length += encodedLength;
            if (err != NWC24_OK) {
                NWC24FClose(&file);
                result = err;
                goto finish;
            }
            attached[index].size = msg->length - (u32)attached[index].ptr;
            if ((s32)index == msg->numAttached - 1) {
                buffer = NWC24WorkP->stringWork;
                Mail_memset(buffer, 0, 1024);
                Mail_sprintf(buffer, "\r\n--%s", MultiPartDivider);
                Mail_strcat(buffer, "--\r\n");
                CHECK_WRITE(WriteString(msg, buffer));
            }
        }
    }
finish:
    if (result == NWC24_OK) {
        NWC24iMBoxCloseMsg(&file);
    } else {
        NWC24iMBoxCancelMsg(&file, type, id);
        NWC24iMBoxFlushHeader(type);
        goto report;
    }
    {
        msg->subject = subject;
        msg->text = text;
        msg->attached[0] = attached[0];
        msg->attached[1] = attached[1];
        msg->type |= 0x200;
        if (type == NWC24_MBOX_TYPE_RECV)
            msg->type |= 0x20;
        else if (type == NWC24_MBOX_TYPE_SEND)
            msg->type |= 0x10;
        err = NWC24iMBoxAddMsgObj(type, msg);
        if (result != NWC24_OK)
            err = result;
        result = err;
        if (type == NWC24_MBOX_TYPE_RECV) {
            u32 flags = 1;
            if (msg->type & 8)
                flags |= 2;
            NWC24iSetNewMsgArrived(flags);
        }
    }
report:
    if (result == NWC24_ERR_FULL || (result <= -16 && result >= -21) || result == -38 || result == -41 || result == -43 || result == -46)
        NWC24iSetErrorCode(result - 109300);
    return result;
}

static NWC24Err CheckMsgObject(const NWC24MsgObjPrivate* msg) {
    const char* subject;
    if (msg->numTo == 0)
        return NWC24_ERR_NULL;
    if (msg->numTo > 8)
        return NWC24_ERR_INVALID_VALUE;
    subject = msg->subject.ptr;
    if (subject != NULL) {
        for (; *subject != '\0'; ++subject) {
            if (*subject == '\r' && subject[1] != '\n')
                return NWC24_ERR_FORMAT;
            if (*subject == '\n' && subject[1] != ' ')
                return NWC24_ERR_FORMAT;
        }
    }
    if (msg->numAttached > 2)
        return NWC24_ERR_INVALID_VALUE;
    return NWC24_OK;
}

static inline u32 Base64StorageSize(const u32* byteCount) {
    return (*byteCount * 4 + 2) / 3 + *byteCount / 57 * 2 + 4;
}

static NWC24Err CheckMsgBoxSpace(const NWC24MsgObjPrivate* msg, NWC24MBoxType type) {
    u32 total = 0;
    u32 textSize = 0;
    s32 index;
    NWC24Err err;
    for (index = 0; index < msg->numAttached; ++index) {
        total += Base64StorageSize(&msg->attachedSize[index]);
    }
    switch (msg->encoding) {
        case NWC24_ENC_7BIT:
        case NWC24_ENC_8BIT:
            textSize = msg->text.size;
            break;
        case NWC24_ENC_BASE64:
            textSize = (msg->text.size * 4 + 2) / 3 + msg->text.size / 57 * 2 + 4;
            break;
        case NWC24_ENC_QUOTED_PRINTABLE:
            textSize = msg->text.size * 4 / 3;
            break;
        default:
            textSize = 0;
            break;
    }
    total += textSize;
    if (total >= 0x31C00)
        return NWC24_ERR_OVERFLOW;
    err = NWC24iMBoxCheck(type, total + 1024);
    if (err != NWC24_OK)
        return err;
    return NWC24_OK;
}

static NWC24Err SynthesizeAddrStr(const NWC24Data* address, u32 type, char* dest, s32 capacity, u32* length) {
    char id[32];
    NWC24Err err = NWC24_OK;
    const char* domain;
    s32 domainLength, written;
    if (type & 1) {
        domain = NWC24GetAccountDomain();
        domainLength = Mail_strlen(domain);
        if (domainLength <= 0)
            err = NWC24_ERR_CONFIG;
        else if (domainLength + 18 >= capacity)
            err = NWC24_ERR_NOMEM;
        else {
            NWC24iConvIdToStr(*(const NWC24UserId*)address, id);
            written = Mail_sprintf(dest, "%c%s%s", 'w', id, domain);
            if (written == 0)
                err = NWC24_ERR_FATAL;
            else
                *length = written;
        }
    } else if (type & 2) {
        if (address->size + 3 >= (u32)capacity)
            err = NWC24_ERR_NOMEM;
        else {
            written = Mail_sprintf(dest, "%s", address->ptr);
            if (written == 0)
                err = NWC24_ERR_FATAL;
            else
                *length = written;
        }
    } else
        err = NWC24_ERR_INVALID_VALUE;
    return err;
}

static NWC24Err WriteSMTP_MAILFROM(NWC24MsgObjPrivate* msg) {
    char* buffer = NWC24WorkP->stringWork;
    char* address;
    u32 length;
    s32 total;
    u32 type;
    NWC24Err err;
    Mail_memset(buffer, 0, 1024);
    Mail_strncat(buffer, "MAIL FROM: ", 1022);
    address = buffer + 11;
    type = 1;
    if (msg->type & 0x100000)
        type = 2;
    err = SynthesizeAddrStr(&msg->fromAddr, type, address, 1009, &length);
    if (err != NWC24_OK)
        return err;
    {
        address += length;
        address[0] = '\r';
        address[1] = '\n';
        total = length + 13;
        if ((s32)(1009 - length) <= 0)
            return NWC24_ERR_NOMEM;
    }
    if (err == NWC24_OK) {
        err = NWC24FWrite(NWC24WorkP->stringWork, total, m_pFile);
        if (err == NWC24_OK)
            msg->length += total;
    }
    return err;
}

static NWC24Err WriteSMTP_RCPTTO(NWC24MsgObjPrivate* msg) {
    char* cursor = NWC24WorkP->stringWork;
    u32 index;
    s32 total = 0, remaining;
    u32 length;
    NWC24Err err = NWC24_OK;
    Mail_memset(cursor, 0, 1024);
    remaining = 1022;
    for (index = 0; index < msg->numTo; ++index) {
        Mail_strncat(cursor, "RCPT TO: ", remaining);
        cursor += 9;
        remaining -= 11;
        err = SynthesizeAddrStr(&msg->toAddrs[index], msg->type, cursor, remaining, &length);
        if (err != NWC24_OK)
            break;
        cursor += length;
        cursor[0] = '\r';
        cursor[1] = '\n';
        cursor += 2;
        remaining -= length;
        total += length + 11;
        if (remaining <= 0) {
            err = NWC24_ERR_NOMEM;
            break;
        }
    }
    if (err == NWC24_OK) {
        err = NWC24FWrite(NWC24WorkP->stringWork, total, m_pFile);
        if (err == NWC24_OK)
            msg->length += total;
    }
    return err;
}

static NWC24Err WriteFromField(NWC24MsgObjPrivate* msg) {
    char* buffer = NWC24WorkP->stringWork;
    char* address;
    u32 length;
    s32 total;
    u32 type;
    NWC24Err err;
    Mail_memset(buffer, 0, 1024);
    Mail_strncat(buffer, "From: ", 1022);
    address = buffer + 6;
    msg->unk_0x30.ptr = (const void*)(msg->length + 6);
    type = 1;
    if (msg->type & 0x100000)
        type = 2;
    err = SynthesizeAddrStr(&msg->fromAddr, type, address, 1014, &length);
    if (err != NWC24_OK)
        return err;
    {
        address += length;
        address[0] = '\r';
        address[1] = '\n';
        total = length + 8;
        if ((s32)(1014 - length) <= 0)
            return NWC24_ERR_NOMEM;
    }
    if (err == NWC24_OK) {
        err = NWC24FWrite(NWC24WorkP->stringWork, total, m_pFile);
        if (err == NWC24_OK) {
            msg->length += total;
            msg->unk_0x30.size = msg->length - (u32)msg->unk_0x30.ptr - 2;
        }
    }
    return err;
}

static NWC24Err WriteToField(NWC24MsgObjPrivate* msg) {
    char* cursor = NWC24WorkP->stringWork;
    s32 index, total, remaining;
    u32 length;
    NWC24Err err = NWC24_OK;
    Mail_memset(cursor, 0, 1024);
    Mail_strncat(cursor, "To: ", 1022);
    cursor += 4;
    index = 0;
    total = 4;
    msg->unk_0x38.ptr = (const void*)(msg->length + 4);
    remaining = 1018;
    for (; index < msg->numTo; ++index) {
        err = SynthesizeAddrStr(&msg->toAddrs[index], msg->type, cursor, remaining, &length);
        if (err != NWC24_OK)
            break;
        remaining -= length;
        cursor += length;
        total += length;
        if (remaining <= 4) {
            err = NWC24_ERR_NOMEM;
            break;
        }
        if (index < msg->numTo - 1) {
            cursor[0] = ',';
            cursor[1] = '\r';
            cursor[2] = '\n';
            cursor[3] = ' ';
            total += 4;
            remaining -= 4;
            cursor += 4;
        }
    }
    cursor[0] = '\r';
    cursor[1] = '\n';
    if (err == NWC24_OK) {
        err = NWC24FWrite(NWC24WorkP->stringWork, total + 2, m_pFile);
        if (err == NWC24_OK) {
            msg->length += total + 2;
            msg->unk_0x38.size = msg->length - (u32)msg->unk_0x38.ptr - 2;
        }
    }
    return err;
}

static NWC24Err WriteDateField(NWC24MsgObjPrivate* msg) {
    static const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    NWC24Date date;
    OSCalendarTime calendar;
    char* buffer;
    s32 length;
    NWC24Err err;
    NWC24Date_Init(&date);
    NETGetUniversalCalendar(&calendar);
    date.year = calendar.year;
    date.month = calendar.mon + 1;
    date.day = calendar.mday;
    date.hour = calendar.hour;
    date.min = calendar.min;
    date.sec = calendar.sec;
    if (date.month > 12)
        return NWC24_ERR_FORMAT;
    NWC24iDateToMinutes(&msg->date, &date);
    if (msg->type & 0x1000000)
        NWC24iMinutesToDate(&date, msg->receivedDate);
    buffer = NWC24WorkP->stringWork;
    Mail_memset(buffer, 0, 1024);
    Mail_sprintf(buffer, "Date: %02d %s %d %02d:%02d:%02d -0000\r\n", date.day, months[date.month - 1], date.year, date.hour, date.min, date.sec);
    length = Mail_strlen(buffer);
    err = NWC24FWrite(buffer, length, m_pFile);
    if (err == NWC24_OK)
        msg->length += length;
    return err;
}

static NWC24Err WriteXWiiAppIdField(NWC24MsgObjPrivate* msg) {
    char* buffer = NWC24WorkP->stringWork;
    char appIdText[16];
    u32 type = 0;
    s32 length;
    NWC24Err err;
    Mail_memset(buffer, 0, 1024);
    Mail_strcpy(buffer, "X-Wii-AppId: ");
    if (!NWC24IsMsgLibOpenedByTool() && NWC24GetAppId() != 0x48414541 && msg->appId != 0x48414341)
        msg->appId = NWC24GetAppId();
    if (msg->type & 4)
        type |= 1;
    if (msg->type & 8)
        type |= 2;
    Mail_memset(appIdText, 0, 16);
    Mail_sprintf(appIdText, "%d-%08X-%04X\r\n", type, msg->appId, msg->groupId);
    Mail_strcat(buffer, appIdText);
    length = Mail_strlen(buffer);
    err = NWC24FWrite(buffer, length, m_pFile);
    if (err == NWC24_OK)
        msg->length += length;
    return err;
}

static NWC24Err WriteXWiiFaceField(NWC24MsgObjPrivate* msg) {
    char* buffer;
    const u8* data;
    s32 offset, remaining, chunk;
    u32 length;
    NWC24Err err;
    if (msg->faceData.size == 0)
        return NWC24_OK;
    buffer = NWC24WorkP->stringWork;
    Mail_memset(buffer, 0, 1024);
    Mail_strcpy(buffer, "X-WiiFace:");
    data = msg->faceData.ptr;
    offset = 10;
    for (remaining = msg->faceData.size; remaining > 0; remaining -= chunk) {
        buffer[offset++] = ' ';
        chunk = remaining;
        if (remaining > 42)
            chunk = 42;
        NWC24Base64Encode((u8*)data, chunk, (u8*)(buffer + offset), 76, &length);
        data += chunk;
        offset += length;
        buffer[offset++] = '\r';
        buffer[offset++] = '\n';
    }
    err = NWC24FWrite(buffer, offset, m_pFile);
    if (err == NWC24_OK)
        msg->length += offset;
    return err;
}

static NWC24Err WriteXWiiAltNameField(NWC24MsgObjPrivate* msg) {
    char* buffer;
    const u8* data;
    s32 offset, remaining, chunk;
    u32 length;
    NWC24Err err;
    if (msg->altName.size == 0)
        return NWC24_OK;
    buffer = NWC24WorkP->stringWork;
    Mail_memset(buffer, 0, 1024);
    Mail_strcpy(buffer, "X-Wii-AltName:");
    data = msg->altName.ptr;
    offset = 14;
    for (remaining = msg->altName.size; remaining > 0; remaining -= chunk) {
        buffer[offset++] = ' ';
        chunk = remaining;
        if (remaining > 42)
            chunk = 42;
        NWC24Base64Encode((u8*)data, chunk, (u8*)(buffer + offset), 76, &length);
        data += chunk;
        offset += length;
        buffer[offset++] = '\r';
        buffer[offset++] = '\n';
    }
    err = NWC24FWrite(buffer, offset, m_pFile);
    if (err == NWC24_OK)
        msg->length += offset;
    return err;
}

const char* ContentTypeA = "Content-Type: %s;\r\n name=%c%07d.%s\r\n";
const char* ContentTxEncA = "Content-Transfer-Encoding: base64\r\n";
const char* ContentDispA = "Content-Disposition: attachment;\r\n filename=%c%07d.%s\r\n\r\n";

static NWC24Err WriteMIMEAttachHeader(NWC24MsgObjPrivate* msg, u32 index) {
    char* buffer;
    const char* mime;
    const char* suffix;
    int mimeLength;
    s32 first, second, third, total;
    NWC24Err err;
    Mail_memset(NWC24WorkP->stringWork, 0, 1024);
    buffer = NWC24WorkP->stringWork;
    mime = NWC24GetMIMETypeStr(msg->attachedType[index]);
    suffix = NWC24iGetMIMETypeSuffix(msg->attachedType[index]);
    mimeLength = (Mail_strlen(ContentTypeA) + Mail_strlen(ContentTxEncA)) + Mail_strlen(ContentDispA) + Mail_strlen(mime) + 4;
    if (mimeLength >= 1024)
        return NWC24_ERR_NOMEM;
    first = Mail_sprintf(buffer, (char*)ContentTypeA, mime, (char)('a' + index), msg->msgId, suffix);
    if (first <= 0)
        return NWC24_ERR_FAILED;
    buffer += first;
    second = Mail_sprintf(buffer, (char*)ContentTxEncA);
    if (second <= 0)
        return NWC24_ERR_FAILED;
    buffer += second;
    total = first + second;
    third = Mail_sprintf(buffer, (char*)ContentDispA, (char)('a' + index), msg->msgId, suffix);
    if (third <= 0)
        return NWC24_ERR_FAILED;
    total += third;
    err = NWC24FWrite(NWC24WorkP->stringWork, total, m_pFile);
    if (err == NWC24_OK)
        msg->length += total;
    return err;
}

const char* ContentTypeTP = "Content-Type: text/plain; charset=%s\r\n";
const char* ContentTxEncT = "Content-Transfer-Encoding: %s\r\n\r\n";

static NWC24Err WriteContentTypeField(NWC24MsgObjPrivate* msg) {
    char* buffer = NWC24WorkP->stringWork;
    const char* name;
    const char* encoding;
    s32 total = 0;
    NWC24Err err;
    Mail_memset(buffer, 0, 1024);
    name = NWC24GetCharsetStr(msg->charset);
    if (name != NULL) {
        Mail_sprintf(buffer, (char*)ContentTypeTP, name);
        msg->unk_0x50.ptr = (const void*)(msg->length + 34);
        msg->unk_0x50.size = Mail_strlen(name) + 1;
        total = Mail_strlen(buffer);
        buffer += total;
    }
    encoding = NWC24GetEncodingStr(msg->encoding);
    if (encoding != NULL) {
        Mail_sprintf(buffer, (char*)ContentTxEncT, encoding);
        msg->unk_0x58.ptr = (const void*)(total + msg->length + 27);
        msg->unk_0x58.size = Mail_strlen(encoding) + 1;
        total += Mail_strlen(buffer);
    }
    if (total == 0)
        return NWC24_OK;
    err = NWC24FWrite(NWC24WorkP->stringWork, total, m_pFile);
    if (err == NWC24_OK)
        msg->length += total;
    return err;
}

static NWC24Err WritePlainText(NWC24MsgObjPrivate* msg) {
    u32 length;
    NWC24Err err;
    if (msg->text.size == 0)
        return NWC24_ERR_NULL;
    switch (msg->encoding) {
        case NWC24_ENC_7BIT:
        case NWC24_ENC_8BIT:
            err = NWC24FWrite(msg->text.ptr, msg->text.size, m_pFile);
            length = msg->text.size;
            break;
        case NWC24_ENC_BASE64:
            err = WriteBase64Data(msg->text.ptr, msg->text.size, &length);
            break;
        case NWC24_ENC_QUOTED_PRINTABLE:
            err = WriteQPData(msg->text.ptr, msg->text.size, &length);
            break;
        default:
            err = NWC24_ERR_INVALID_VALUE;
            break;
    }
    if (err == NWC24_OK) {
        msg->textSize = msg->text.size;
        msg->length += length;
    }
    return err;
}

static NWC24Err WriteBase64Data(const u8* data, s32 size, u32* totalLength) {
    const u8* cursor = data;
    char* buffer = NWC24WorkP->stringWork;
    u32 length;
    u32 total = 0;
    NWC24Err err = NWC24_OK;
    while (size >= 57) {
        Mail_memset(buffer, 0, 1024);
        err = NWC24Base64Encode((u8*)cursor, 57, (u8*)buffer, 76, &length);
        if (err != NWC24_OK)
            break;
        buffer[length++] = '\r';
        buffer[length++] = '\n';
        buffer[length] = '\0';
        err = NWC24FWrite(buffer, length, m_pFile);
        if (err != NWC24_OK)
            break;
        cursor += 57;
        size -= 57;
        total += length;
    }
    if (err == NWC24_OK) {
        Mail_memset(buffer, 0, 1024);
        err = NWC24Base64Encode((u8*)cursor, size, (u8*)buffer, 76, &length);
        if (err == NWC24_OK) {
            buffer[length++] = '\r';
            buffer[length++] = '\n';
            buffer[length++] = '\r';
            buffer[length++] = '\n';
            buffer[length] = '\0';
            err = NWC24FWrite(buffer, length, m_pFile);
            if (err == NWC24_OK)
                total += length;
        }
    }
    *totalLength = total;
    return err;
}

static NWC24Err WriteQPData(const u8* data, s32 size, u32* totalLength) {
    char* buffer = NWC24WorkP->stringWork;
    const u8* cursor = data;
    s32 remaining = size;
    s32 total = 0;
    u32 consumed, length;
    NWC24Err err = NWC24_OK;
    for (; remaining > 0; remaining -= consumed) {
        if (total > 0) {
            Mail_memcpy(buffer, "=\r\n", 3);
            err = NWC24FWrite(buffer, 3, m_pFile);
            if (err != NWC24_OK)
                break;
            total += 3;
        }
        Mail_memset(buffer, 0, 1024);
        err = NWC24EncodeQuotedPrintable(buffer, 1024, &length, (u8*)cursor, remaining, &consumed);
        if (err != NWC24_OK && err != NWC24_ERR_OVERFLOW)
            break;
        err = NWC24FWrite(buffer, length, m_pFile);
        if (err != NWC24_OK)
            break;
        cursor += consumed;
        total += length;
    }
    *totalLength = total;
    return err;
}
