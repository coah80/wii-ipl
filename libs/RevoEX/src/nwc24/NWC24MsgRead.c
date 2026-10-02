#define NWC24_MSG_READ
#include <private/nwc24.h>

NWC24Err NWC24iMBoxOpenStoredMsg(NWC24MBoxType type, u32 id, NWC24File* file);
NWC24Err NWC24iMBoxCloseMsg(NWC24File* file);
BOOL Mail_isdigit(int character);
static NWC24Err ReadMsgTextInternal(const NWC24MsgObj* msg, char* text, u32 capacity, char* charset, u32 charsetCapacity, NWC24Encoding* encoding);
NWC24Err ReadBase64Data(NWC24File* file, const NWC24Data* data, u8* output, u32 capacity, u32* outputSize);
NWC24Err ReadQPText(const NWC24MsgObjPrivate* msg, NWC24File* file, char* output, u32 capacity);

static inline NWC24Err SelectMBox(const NWC24MsgObjPrivate* msg, NWC24MBoxType* type) {
    if (msg->type & 0x10)
        *type = NWC24_MBOX_TYPE_SEND;
    else if (msg->type & 0x20)
        *type = NWC24_MBOX_TYPE_RECV;
    else
        return NWC24_ERR_INVALID_VALUE;
    return NWC24_OK;
}

NWC24Err NWC24ReadMsgField(const NWC24MsgObj* msg, char* fieldName, u8* output, u32 capacity) {
    const NWC24MsgObjPrivate* privateMsg = (const NWC24MsgObjPrivate*)msg;
    NWC24File file;
    NWC24FileStream stream;
    char* field;
    u32 offset;
    u32 length;
    NWC24MBoxType type;
    NWC24Err result;
    NWC24Err closeResult;
    if (!NWC24IsMsgLibOpened() && !NWC24IsMsgLibOpenedByTool())
        return NWC24_ERR_LIB_NOT_OPENED;
    if (!(privateMsg->type & 0x200))
        return NWC24_ERR_PROTECTED;
    result = SelectMBox(privateMsg, &type);
    switch (result) {
        case NWC24_OK:
            break;
        default:
            return result;
    }
    result = NWC24iMBoxOpenStoredMsg(type, privateMsg->msgId, &file);
    switch (result) {
        case NWC24_OK:
            break;
        default:
            return result;
    }
    result = NWC24FStreamInit(&stream, &file, 0, privateMsg->length, NWC24WorkP->mainWork, 1024);
    if (result == NWC24_OK) {
        result = NWC24iSearchHeaderF(&stream, fieldName, privateMsg->headerSize, &offset, &length);
        if (result == NWC24_OK) {
            if (length > capacity)
                result = NWC24_ERR_OVERFLOW;
            else {
                result = NWC24FStreamSeek(&stream, offset);
                if (result == NWC24_OK) {
                    result = NWC24FStreamGetPtr(&stream, &field, length);
                    if (result == NWC24_OK) {
                        Mail_strncpy((char*)output, field, length);
                        output[length - 2] = 0;
                    }
                }
            }
        }
    }
    closeResult = NWC24iMBoxCloseMsg(&file);
    if (result == NWC24_OK)
        result = closeResult;
    return result;
}

NWC24Err NWC24ReadMsgFaceData(const NWC24MsgObj* msg, u8* faceData) {
    const NWC24MsgObjPrivate* privateMsg = (const NWC24MsgObjPrivate*)msg;
    char* buffer;
    u32 length;
    NWC24Err result;
    if ((privateMsg->type & 2) && !(privateMsg->type & 0x1000))
        return NWC24_ERR_NOT_FOUND;
    buffer = NWC24WorkP->stringWork;
    Mail_memset(buffer, 0, 1024);
    result = NWC24ReadMsgField(msg, "x-wiiface", (u8*)buffer, 1024);
    switch (result) {
        default:
            return result;
        case NWC24_OK:
            result = NWC24Base64Decode((u8*)buffer, STD_strnlen(buffer, 1024), faceData, 74, &length);
            switch (result) {
                default:
                    return result;
                case NWC24_OK:
                    if (length != 74)
                        return NWC24_ERR_FORMAT;
                    return NWC24_OK;
            }
    }
    return result;
}

NWC24Err NWC24ReadMsgAltName(const NWC24MsgObj* msg, u16* name, u32 capacity) {
    char* buffer = NWC24WorkP->stringWork;
    u32 length;
    NWC24Err result;
    NWC24Err decodeResult;
    Mail_memset(buffer, 0, 1024);
    result = NWC24ReadMsgField(msg, "x-wii-altname:", (u8*)buffer, 1024);
    switch (result) {
        default:
            return result;
        case NWC24_OK:
            decodeResult = NWC24Base64Decode((u8*)buffer, STD_strnlen(buffer, 1024), (u8*)name, capacity * 2, &length);
            result = NWC24_OK;
            if (decodeResult != NWC24_OK)
                result = decodeResult;
    }
    return result;
}

NWC24Err NWC24ReadMsgMBNoReply(const NWC24MsgObj* msg, BOOL* noReply) {
    char* buffer;
    NWC24Err result;
    *noReply = FALSE;
    buffer = NWC24WorkP->stringWork;
    Mail_memset(buffer, 0, 1024);
    result = NWC24ReadMsgField(msg, "x-wii-mb-noreply:", (u8*)buffer, 1024);
    if (result == NWC24_OK)
        *noReply = TRUE;
    else if (result == NWC24_ERR_NOT_FOUND)
        result = NWC24_OK;
    return result;
}

NWC24Err NWC24ReadMsgMBRegDate(const NWC24MsgObj* msg, u16* year, u8* month, u8* day) {
    NWC24Err result;
    u32 offset = 0;
    u32 digits = 0;
    u32 value = 0;
    s32 digit;
    char* buffer = NWC24WorkP->stringWork;
    Mail_memset(buffer, 0, 1024);
    result = NWC24ReadMsgField(msg, "x-wii-mb-regdate:", (u8*)buffer, 1023);
    switch (result) {
        default:
            return result;
        case NWC24_OK:
            break;
    }
    while (*buffer == '\t' || *buffer == ' ') {
        buffer++;
        offset++;
    }
    for (; offset < 1024; offset++, digits++) {
        digit = Util_xtoi(*buffer);
        if (digit < 0)
            break;
        value = (value << 4) | digit;
        buffer++;
    }
    if (digits != 4)
        result = NWC24_ERR_FORMAT;
    *year = ((value >> 9) & 127) + 2000;
    *month = (value >> 5) & 15;
    *day = value & 31;
    return result;
}

NWC24Err NWC24ReadMsgMBDelay(const NWC24MsgObj* msg, u8* delay) {
    NWC24Err result;
    u32 offset = 0;
    u32 digits = 0;
    u32 value = 0;
    s32 digit;
    char* buffer = NWC24WorkP->stringWork;
    Mail_memset(buffer, 0, 1024);
    result = NWC24ReadMsgField(msg, "x-wii-mb-delay:", (u8*)buffer, 1023);
    switch (result) {
        default:
            return result;
        case NWC24_OK:
            break;
    }
    while (*buffer == '\t' || *buffer == ' ') {
        buffer++;
        offset++;
    }
    for (; offset < 1024; offset++, digits++) {
        digit = Util_xtoi(*buffer);
        if (digit < 0)
            break;
        value = (value << 4) | digit;
        buffer++;
    }
    if (digits != 2)
        result = NWC24_ERR_FORMAT;
    *delay = value;
    return result;
}

NWC24Err NWC24ReadMsgMBUpdateSW(const NWC24MsgObj* msg, u32* update) {
    NWC24Err result;
    const NWC24MsgObjPrivate* privateMsg = (const NWC24MsgObjPrivate*)msg;
    u32 value = 0;
    char* buffer;
    if (!(privateMsg->type & 0x1000)) {
        *update = 0;
        return NWC24_ERR_NOT_FOUND;
    }
    buffer = NWC24WorkP->stringWork;
    Mail_memset(buffer, 0, 1024);
    result = NWC24ReadMsgField(msg, "x-wii-mb-updatesw:", (u8*)buffer, 1023);
    switch (result) {
        default:
            return result;
        case NWC24_OK:
            while (*buffer == '\t' || *buffer == ' ')
                buffer++;
            if (Mail_isdigit(*buffer))
                value = *buffer - '0';
            *update = value;
    }
    return result;
}

NWC24Err NWC24ReadMsgMBOptOutFlag(const NWC24MsgObj* msg, BOOL* optOut, u32* appId) {
    NWC24Err result;
    u32 offset = 0;
    u32 digits = 0;
    u32 value = 0;
    s32 digit;
    char* buffer = NWC24WorkP->stringWork;
    Mail_memset(buffer, 0, 1024);
    *optOut = FALSE;
    *appId = 0;
    result = NWC24ReadMsgField(msg, "x-wii-mb-optout:", (u8*)buffer, 1023);
    if (result == NWC24_ERR_NOT_FOUND)
        return NWC24_OK;
    switch (result) {
        default:
            return result;
        case NWC24_OK:
            while (*buffer == '\t' || *buffer == ' ') {
                buffer++;
                offset++;
            }
            if (*buffer == '1')
                *optOut = TRUE;
            {
                char separator = buffer[1];
                buffer += 2;
                if (separator != '-')
                    return NWC24_OK;
                {
                    offset += 2;
                    for (; offset < 1024; offset++, digits++) {
                        digit = Util_xtoi(*buffer);
                        if (digit < 0)
                            break;
                        value = (value << 4) | digit;
                        buffer++;
                    }
                    if (digits != 8)
                        result = NWC24_ERR_FORMAT;
                    *appId = value;
                }
            }
    }
    return result;
}

NWC24Err NWC24ReadMsgFromAddr(const NWC24MsgObj* msg, char* address, u32 capacity) {
    const NWC24MsgObjPrivate* privateMsg = (const NWC24MsgObjPrivate*)msg;
    NWC24MBoxType type;
    NWC24File file;
    NWC24FileStream stream;
    char* buffer;
    NWC24Err result, closeResult;
    if (!NWC24IsMsgLibOpened() && !NWC24IsMsgLibOpenedByTool())
        return NWC24_ERR_LIB_NOT_OPENED;
    if (!(privateMsg->type & 0x200))
        return NWC24_ERR_PROTECTED;
    buffer = NWC24WorkP->stringWork;
    Mail_memset(buffer, 0, 1024);
    if (!(privateMsg->type & 2))
        return NWC24_ERR_NOT_SUPPORTED;
    result = SelectMBox(privateMsg, &type);
    switch (result) {
        case NWC24_OK:
            break;
        default:
            return result;
    }
    if (privateMsg->unk_0x30.size == 0)
        return NWC24_ERR_NULL;
    result = NWC24iMBoxOpenStoredMsg(type, privateMsg->msgId, &file);
    switch (result) {
        case NWC24_OK:
            break;
        default:
            return result;
    }
    result = NWC24FStreamInit(&stream, &file, 0, privateMsg->length, buffer, 1024);
    if (result == NWC24_OK) {
        result = NWC24FStreamSeek(&stream, (u32)privateMsg->unk_0x30.ptr);
        if (result == NWC24_OK)
            result = NWC24iExtractAddrSpec(&stream, privateMsg->unk_0x30.size, 0, address, capacity);
    }
    closeResult = NWC24iMBoxCloseMsg(&file);
    if (result != NWC24_OK)
        closeResult = result;
    return closeResult;
    return result;
}

NWC24Err NWC24ReadMsgSubject(const NWC24MsgObj* msg, char* subject, u32 capacity) {
    const NWC24MsgObjPrivate* privateMsg = (const NWC24MsgObjPrivate*)msg;
    NWC24MBoxType type;
    NWC24File file;
    u32 length;
    NWC24Err result, closeResult;
    if (!NWC24IsMsgLibOpened() && !NWC24IsMsgLibOpenedByTool())
        return NWC24_ERR_LIB_NOT_OPENED;
    if (!(privateMsg->type & 0x200))
        return NWC24_ERR_PROTECTED;
    result = SelectMBox(privateMsg, &type);
    switch (result) {
        case NWC24_OK:
            break;
        default:
            return result;
    }
    length = privateMsg->subject.size;
    if (length == 0)
        return NWC24_ERR_NULL;
    result = NWC24iMBoxOpenStoredMsg(type, privateMsg->msgId, &file);
    switch (result) {
        case NWC24_OK:
            break;
        default:
            return result;
    }
    if (length > capacity - 1)
        length = capacity - 1;
    NWC24FSeek(&file, (u32)privateMsg->subject.ptr, NWC24_SEEK_BEG);
    result = NWC24FRead(subject, length, &file);
    if (result == NWC24_OK) {
        subject[length] = 0;
        if (privateMsg->subject.size > capacity - 1)
            result = NWC24_ERR_OVERFLOW;
    }
    closeResult = NWC24iMBoxCloseMsg(&file);
    if (result == NWC24_OK)
        result = closeResult;
    return result;
}

NWC24Err NWC24ReadMsgText(const NWC24MsgObj* msg, char* text, u32 capacity, NWC24Charset* charset, NWC24Encoding* encoding) {
    char* name = NWC24WorkP->stringWork + 32;
    NWC24Err result = ReadMsgTextInternal(msg, text, capacity, name, 64, encoding);
    if (result == NWC24_OK)
        result = NWC24ParseCharsetStr(charset, name);
    return result;
}

NWC24Err NWC24ReadMsgTextEx(const NWC24MsgObj* msg, char* text, u32 capacity, char* charset, u32 charsetCapacity) {
    u32 i;
    NWC24Encoding encoding;
    NWC24Err result = ReadMsgTextInternal(msg, text, capacity, charset, charsetCapacity, &encoding);
    if (result == NWC24_OK) {
        for (i = 0; i < charsetCapacity; i++) {
            switch (*charset) {
                case ' ':
                case '\t':
                case '\n':
                case '\r':
                case ';':
                case '"':
                    *charset = 0;
                    break;
            }
            if (*charset == 0)
                break;
            charset++;
        }
    }
    return result;
}

static NWC24Err ReadMsgTextInternal(const NWC24MsgObj* msg, char* text, u32 capacity, char* charset, u32 charsetCapacity, NWC24Encoding* encoding) {
    const NWC24MsgObjPrivate* privateMsg = (const NWC24MsgObjPrivate*)msg;
    NWC24MBoxType type;
    NWC24File file;
    NWC24Err result, closeResult;
    NWC24Err overflow = NWC24_OK;
    u32 length;
    u32 decodedSize;
    char* buffer;
    if (!NWC24IsMsgLibOpened() && !NWC24IsMsgLibOpenedByTool())
        return NWC24_ERR_LIB_NOT_OPENED;
    if (!(privateMsg->type & 0x200))
        return NWC24_ERR_PROTECTED;
    buffer = NWC24WorkP->stringWork;
    *encoding = 0;
    result = SelectMBox(privateMsg, &type);
    switch (result) {
        case NWC24_OK:
            break;
        default:
            return result;
    }
    length = privateMsg->textSize;
    switch (length) {
        case 0: length = privateMsg->text.size; break;
        default: break;
    }
    if (length == 0)
        return NWC24_ERR_NULL;
    if (length > capacity - 1) {
        overflow = NWC24_ERR_OVERFLOW;
        length = capacity - 1;
    }
    result = NWC24iMBoxOpenStoredMsg(type, privateMsg->msgId, &file);
    switch (result) {
        case NWC24_OK:
            break;
        default:
            return result;
    }
    Mail_memset(charset, 0, charsetCapacity);
    if (privateMsg->unk_0x50.size >= charsetCapacity)
        result = NWC24_ERR_FORMAT;
    else {
        if (privateMsg->unk_0x50.size != 0) {
            NWC24FSeek(&file, (u32)privateMsg->unk_0x50.ptr, NWC24_SEEK_BEG);
            result = NWC24FRead(charset, privateMsg->unk_0x50.size, &file);
            if (result != NWC24_OK)
                goto close;
        }
        if (privateMsg->unk_0x58.size != 0 && privateMsg->unk_0x58.size < 32) {
            Mail_memset(buffer, 0, 32);
            NWC24FSeek(&file, (u32)privateMsg->unk_0x58.ptr, NWC24_SEEK_BEG);
            result = NWC24FRead(buffer, privateMsg->unk_0x58.size, &file);
            if (result != NWC24_OK)
                goto close;
            result = NWC24ParseEncodingStr(encoding, buffer);
            if (result != NWC24_OK)
                goto close;
        }
        NWC24FSeek(&file, (u32)privateMsg->text.ptr, NWC24_SEEK_BEG);
        switch (*encoding) {
            case 0:
            case 1:
                result = NWC24FRead(text, length, &file);
                text[length] = 0;
                break;
            case 2:
                decodedSize = 0;
                result = ReadBase64Data(&file, &privateMsg->text, (u8*)text, length, &decodedSize);
                if (result == NWC24_OK && decodedSize != privateMsg->textSize)
                    result = NWC24_ERR_FORMAT;
                text[length] = 0;
                break;
            case 3:
                result = ReadQPText(privateMsg, &file, text, length);
                break;
            default:
                result = NWC24_ERR_NOT_SUPPORTED;
                *text = 0;
                break;
        }
    }
close:
    closeResult = NWC24iMBoxCloseMsg(&file);
    if (result != NWC24_OK)
        closeResult = result;
    if (closeResult != NWC24_OK)
        overflow = closeResult;
    return overflow;
}

NWC24Err NWC24ReadMsgAttached(const NWC24MsgObj* msg, u32 index, u8* output, u32 capacity) {
    const NWC24MsgObjPrivate* privateMsg = (const NWC24MsgObjPrivate*)msg;
    NWC24File file;
    NWC24MBoxType type;
    u32 decodedSize;
    NWC24Err result, closeResult;
    if (!NWC24IsMsgLibOpened() && !NWC24IsMsgLibOpenedByTool())
        return NWC24_ERR_LIB_NOT_OPENED;
    if (!(privateMsg->type & 0x200))
        return NWC24_ERR_PROTECTED;
    if (index >= privateMsg->numAttached)
        return NWC24_ERR_NOT_FOUND;
    result = SelectMBox(privateMsg, &type);
    switch (result) {
        case NWC24_OK:
            break;
        default:
            return result;
    }
    if (privateMsg->attached[index].size == 0 || privateMsg->attachedSize[index] == 0)
        return NWC24_ERR_NULL;
    result = NWC24iMBoxOpenStoredMsg(type, privateMsg->msgId, &file);
    switch (result) {
        case NWC24_OK:
            break;
        default:
            return result;
    }
    decodedSize = 0;
    result = ReadBase64Data(&file, &privateMsg->attached[index], output, capacity, &decodedSize);
    switch (result) {
        case NWC24_OK:
            if (decodedSize != privateMsg->attachedSize[index]) { result = NWC24_ERR_FORMAT; }
            break;
        default: break;
    }
    closeResult = NWC24iMBoxCloseMsg(&file);
    if (result == NWC24_OK)
        result = closeResult;
    return result;
}

NWC24Err ReadBase64Data(NWC24File* file, const NWC24Data* data, u8* output, u32 capacity, u32* outputSize) {
    int remaining = data->size;
    int offset = (u32)data->ptr;
    char* buffer = NWC24WorkP->mainWork;
    u8* outPtr = output;
    int total = 0;
    int readSize;
    int end;
    char* cursor;
    int i;
    u32 decodedSize;
    NWC24Err result = NWC24_OK;
    BOOL finished = FALSE;
    while (remaining > 0 && !finished) {
        readSize = remaining > 1024 ? 1024 : remaining;
        NWC24FSeek(file, offset, NWC24_SEEK_BEG);
        result = NWC24FRead(buffer, readSize, file);
        if (result != NWC24_OK)
            break;
        end = 0;
        cursor = buffer;
        for (i = 0; i < readSize; cursor++, i++) {
            if (*cursor == '\r')
                end = i;
            if (*cursor == '=') {
                end = i + 1;
                finished = TRUE;
                result = NWC24_OK;
                break;
            }
        }
        if (end == 0)
            break;
        result = NWC24Base64Decode((u8*)buffer, end, outPtr, capacity - total, &decodedSize);
        if (result != NWC24_OK)
            break;
        offset += end;
        remaining -= end;
        total += decodedSize;
        outPtr += decodedSize;
    }
    if (result == NWC24_OK)
        *outputSize = total;
    return result;
}

NWC24Err ReadQPText(const NWC24MsgObjPrivate* msg, NWC24File* file, char* output, u32 capacity) {
    int remaining = msg->text.size;
    int offset = (u32)msg->text.ptr;
    char* buffer = NWC24WorkP->mainWork;
    char* cursor = output;
    int readSize;
    u32 total = 0;
    u32 consumedSize;
    u32 decodedSize;
    NWC24Err result = NWC24_OK;
    while (remaining > 0) {
        readSize = remaining > 1024 ? 1024 : remaining;
        NWC24FSeek(file, offset, NWC24_SEEK_BEG);
        result = NWC24FRead(buffer, readSize, file);
        if (result != NWC24_OK)
            break;
        consumedSize = readSize;
        if (readSize == 1024) {
            if (buffer[readSize - 1] == '=')
                consumedSize = readSize - 1;
            else if (buffer[readSize - 2] == '=')
                consumedSize = readSize - 2;
        }
        result = NWC24DecodeQuotedPrintable(cursor, capacity - total, &decodedSize, (u8*)buffer, consumedSize, &consumedSize);
        if (result != NWC24_OK && result != NWC24_ERR_OVERFLOW)
            break;
        total += decodedSize;
        cursor += decodedSize;
        if (result == NWC24_ERR_OVERFLOW)
            break;
        offset += consumedSize;
        remaining -= consumedSize;
    }
    *cursor = 0;
    if (result == NWC24_OK && total > msg->textSize)
        result = NWC24_ERR_FORMAT;
    return result;
}
