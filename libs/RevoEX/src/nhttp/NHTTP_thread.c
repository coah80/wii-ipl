#include <private/nhttp.h>
#include <revolution/ncd.h>

#pragma auto_inline off

static const char STR_POST_DISPOS[] = "Content-Disposition: form-data; name=\"";
static const char STR_POST_TYPE_BIN[] = "Content-Type: application/octet-stream\r\nContent-Transfer-Encoding: binary\r\n";
static const char STR_POST_TYPE_URLENCODE[] = "Content-Type: application/x-www-form-urlencoded\r\n";
static const char STR_POST_TYPE_MULTIPART[] = "Content-Type: multipart/form-data; boundary=";

typedef struct NHTTPThreadInfo
{
    OSMessageQueue messageQueue;
    OSMessage messages[3];
    OSThread thread;
    BOOL isCreateCommThreadMessageQueue;
    u8 reserved[0x14];
    char commBuf[0x100];
} NHTTPThreadInfo;

struct NHTTPBgnEndInfo
{
    NCDIpConfig ipConfig;
    NHTTPAlloc alloc;
    NHTTPFree free;
    BOOL started;
    s32 socket;
    s32 sslError;
    NHTTPErr error;
    BOOL stopping;
    void* threadStack;
    u32 reserved;
};

typedef struct NHTTPThreadContext
{
    s32 requestId;
    char hostname[0x100];
    char discard[0x200];
    char statusLine[0x10];
    u32 address;
    u32 previousAddress;
    s32 port;
    s32 previousPort;
    s32 sendLength;
    s32 recvLength;
    s32 contentLength;
    NHTTPErr error;
    BOOL retry;
    BOOL keepAlive;
    BOOL chunked;
} NHTTPThreadContext;

void* NHTTPi_GetSystemInfoP(void);
NHTTPBgnEndInfo* NHTTPi_GetBgnEndInfoP(void* system);
NHTTPThreadInfo* NHTTPi_GetThreadInfoP(void* system);
NHTTPReqInfo* NHTTPi_GetReqInfoP(void* system);
NHTTPListInfo* NHTTPi_GetListInfoP(void* system);
void* NHTTPi_GetMutexInfoP(void* system);
void NHTTPi_lockReqList(void* mutex);
void NHTTPi_unlockReqList(void* mutex);
void NHTTPi_idleCommThread(NHTTPThreadInfo* thread);
void* NHTTPi_alloc(u32 size, s32 alignment);
void NHTTPi_free(void* buffer);
void* NHTTPi_memcpy(void* destination, const void* source, u32 size);
void* NHTTPi_memclr(void* destination, u32 size);
s32 NHTTPi_strlen(const char* text);
s32 NHTTPi_strcmp(const char* first, const char* second);
s32 NHTTPi_strnicmp(const char* first, const char* second, s32 length);
s32 NHTTPi_intToStr(char* destination, s32 number);
s32 NHTTPi_strToInt(const char* text, s32 length);
s32 NHTTPi_strToHex(const char* text, s32 length);
s32 NHTTPi_encodeUrlChar(char* destination, char character);
s32 NHTTPi_getUrlEncodedSize(const char* text);
s32 NHTTPi_getUrlEncodedSize2(const char* text, u32 length);
NHTTPConnectionInfo* NHTTPi_Request2Connection(void* mutex, NHTTPRequestInfo* request);
NHTTPConnectionInfo* NHTTPi_Response2Connection(void* mutex, NHTTPResponseInfo* response);
s32 NHTTPi_PostSendCallback(void* mutex, NHTTPConnectionInfo* connection, const char* label, s32 offset);
s32 NHTTPi_BufferFullCallback(void* mutex, NHTTPConnectionInfo* connection);
s32 NHTTPi_CompleteCallback(void* mutex, NHTTPConnectionInfo* connection);
s32 NHTTPi_ReceivedCallback(void* mutex, NHTTPConnectionInfo* connection);
void NHTTPi_NotifyCompletion(NHTTPConnectionInfo* connection);
void NHTTPi_SetVirtualContentLength(NHTTPConnectionInfo* connection, u32 length);
BOOL NHTTPi_isRecvBufFull(NHTTPResponseInfo* response, s32 offset);
s32 NHTTPi_SocSend(const NHTTPRequestInfo* request, s32 socket, const void* buffer, s32 length, s32 flags);
s32 NHTTPi_SocRecv(void* mutex, NHTTPRequestInfo* request, s32 socket, void* buffer, s32 length, s32 flags);
s32 NHTTPi_SocClose(void* mutex, NHTTPRequestInfo* request, s32 socket);
s32 NHTTPi_SocOpen(NHTTPRequestInfo* request);
s32 NHTTPi_SocConnect(NHTTPBgnEndInfo* info, void* mutex, NHTTPRequestInfo* request, s32 socket, u32 address, u32 port);
s32 NHTTPi_SocSSLConnect(NHTTPBgnEndInfo* info, void* mutex, NHTTPRequestInfo* request, s32 socket);
u32 NHTTPi_resolveHostname(NHTTPRequestInfo* request, const char* host);
s32 NHTTPi_GetSSLError(NHTTPBgnEndInfo* info);
void NHTTPi_SetError(NHTTPBgnEndInfo* info, NHTTPErr error);
NHTTPReqQueue* NHTTPi_getReqFromReqQueue(NHTTPListInfo* list);
NHTTPHeader* NHTTPi_getHdrFromList(NHTTPHeader** list);
void NHTTPi_destroyRequestObject(void* mutex, NHTTPRequestInfo* request);
s32 NHTTPi_loadFromHdrRecvBuf(NHTTPResponseInfo* response, char* destination, s32 offset, s32 length);
s32 NHTTPi_findNextLineHdrRecvBuf(const NHTTPResponseInfo* response, s32 offset, s32 end, s32* length, s32* returnCodeSize);
s32 NHTTPi_getHeaderValue(const NHTTPResponseInfo* response, const char* label, s32* offset);
s32 NHTTPi_compareTokenN_HdrRecvBuf(const NHTTPResponseInfo* response, s32 start, s32 end, const char* token, char delimiter);
s32 NHTTPi_RecvBuf(void* mutex, NHTTPRequestInfo* request, s32 socket, s32 offset, s32 flags);
s32 NHTTPi_RecvBufN(void* mutex, NHTTPRequestInfo* request, s32 socket, s32 offset, s32 length, s32 flags);

void NHTTPi_InitThreadInfo(NHTTPThreadInfo* info)
{
    info->isCreateCommThreadMessageQueue = FALSE;
}

void NHTTPi_IsCreateCommThreadMessageQueueOn(NHTTPThreadInfo* info)
{
    info->isCreateCommThreadMessageQueue = TRUE;
}

BOOL NHTTPi_IsCreateCommThreadMessageQueue(NHTTPThreadInfo* info)
{
    return info->isCreateCommThreadMessageQueue;
}

BOOL NHTTP_GetProgress(void* system, u32* complete, u32* total)
{
    void* mutex = NHTTPi_GetMutexInfoP(system);
    NHTTPReqQueue* queue = NHTTPi_GetReqInfoP(system)->reqQueue;
    BOOL active;
    *complete = 0;
    *total = 0;
    NHTTPi_lockReqList(mutex);
    if (queue != NULL)
    {
        if (queue->request->response->contentLength != 0)
        {
            *complete = queue->request->response->bodyLen;
            *total = queue->request->response->contentLength == (u32)-1 ? 0 : queue->request->response->contentLength;
        }
        active = TRUE;
    }
    else
    {
        active = NHTTPi_GetListInfoP(system)->reqQueue != NULL;
    }
    NHTTPi_unlockReqList(mutex);
    return active;
}

static BOOL NHTTPi_CheckHeaderEnd(const char* recent, s32 length)
{
    u8 before = recent[(length - 2) & 3];
    if ((char)before == '\r' && recent[(length - 1) & 3] == '\r') return TRUE;
    if ((char)before == '\n' && recent[(length - 1) & 3] == '\n') return TRUE;
    if (recent[(length - 4) & 3] == '\r' && recent[(length - 3) & 3] == '\n'
        && (char)before == '\r' && recent[(length - 1) & 3] == '\n') return TRUE;
    return FALSE;
}

static s32 NHTTPi_SaveBuf(NHTTPRequestInfo* request, char* buffer, s32 socket,
    s32* used, const char* data, s32 length)
{
    s32 amount;
    s32 remaining = length;
    while (remaining > 0)
    {
        if (request->cancel) return -1;
        amount = remaining;
        if (amount > 0x100 - *used) amount = 0x100 - *used;
        NHTTPi_memcpy(buffer + *used, data, amount);
        data += amount;
        remaining -= amount;
        *used += amount;
        if (*used == 0x100)
        {
            s32 sent = NHTTPi_SocSend(request, socket, buffer, 0x100, 0);
            if (sent <= 0) return sent;
            *used -= sent;
        }
    }
    return length;
}

static BOOL NHTTPi_GetPostContentlength(void* mutex, NHTTPRequestInfo* request,
    const char* label, s32* length, s32 encoding)
{
    s32 offset = 0;
    NHTTPConnectionInfo* connection = NHTTPi_Request2Connection(mutex, request);
    if (connection == NULL) return FALSE;
    connection->postDataAddress = 0;
    for (;;)
    {
        s32 size;
        const char* data;
        if (request->cancel) return FALSE;
        connection->postDataSize = 0;
        if (NHTTPi_PostSendCallback(mutex, connection, label, offset) < 0) return FALSE;
        size = connection->postDataSize;
        data = (const char*)connection->postDataAddress;
        if (size == 0) break;
        if (data == NULL) return FALSE;
        offset += size;
        switch (encoding)
        {
        case 0:
        case 1: *length += size; break;
        case 2: *length += NHTTPi_getUrlEncodedSize2(data, size); break;
        }
    }
    return TRUE;
}

static s32 NHTTPi_SendPostData(void* mutex, NHTTPRequestInfo* request, char* buffer,
    const char* label, s32 socket, s32* used, s32 encoding)
{
    s32 offset = 0;
    u32 size;
    u32 index;
    NHTTPConnectionInfo* connection;
    const char* data;
    s32 result;
    connection = NHTTPi_Request2Connection(mutex, request);
    if (connection == NULL) return 3;
    connection->postDataAddress = 0;
    for (;;)
    {
        if (request->cancel) return 3;
        connection->postDataSize = 0;
        if (NHTTPi_PostSendCallback(mutex, connection, label, offset) < 0) return 3;
        size = connection->postDataSize;
        data = (const char*)connection->postDataAddress;
        if (size == 0) break;
        if (data == NULL) return 3;
        offset += size;
        switch (encoding)
        {
        case 0:
        case 1:
            result = NHTTPi_SaveBuf(request, buffer, socket, used, data, size);
            if (result < 0) return 1;
            if (result == 0) return 2;
            break;
        case 2:
        {

            for (index = 0; index < size; ++index)
            {
                char encoded[3];
                s32 count;
                NHTTPi_memclr(encoded, 3);
                count = NHTTPi_encodeUrlChar(encoded, data[index]);
                result = NHTTPi_SaveBuf(request, buffer, socket, used, encoded, count);
                if (result < 0) return 1;
                if (result == 0) return 2;
            }
            break;
        }
        }
    }
    return 0;
}

static BOOL NHTTPi_BufFull(void* mutex, NHTTPResponseInfo* response)
{
    BOOL result = FALSE;
    BOOL full = NHTTPi_isRecvBufFull(response, response->bodyLen);
    if (response->recvBufLen == 0 || response->recvBuf_p == NULL || full)
    {
        NHTTPConnectionInfo* connection = NHTTPi_Response2Connection(mutex, response);
        if (connection != NULL)
        {
            NHTTPi_BufferFullCallback(mutex, connection);
            if (response->recvBuf_p != NULL && response->recvBufLen != 0
                && !NHTTPi_isRecvBufFull(response, response->bodyLen)) result = TRUE;
        }
    }
    else if (!full) result = TRUE;
    return result;
}

static s32 NHTTPi_SendData(NHTTPThreadContext* context, const char* data, s32 length)
{
    void* system = NHTTPi_GetSystemInfoP();
    NHTTPBgnEndInfo* info = NHTTPi_GetBgnEndInfoP(system);
    NHTTPThreadInfo* thread = NHTTPi_GetThreadInfoP(system);
    NHTTPRequestInfo* request = NHTTPi_GetReqInfoP(system)->reqQueue->request;
    char* buffer = thread->commBuf;
    s32 result;
    if (length == 0) return 0;
    result = NHTTPi_SaveBuf(request, buffer,
        info->socket, &context->sendLength, data, length);
    if (result < 0) return 1;
    if (result == 0) return 2;
    return 0;
}

static inline s32 NHTTPi_SendProxyAuthorization(NHTTPThreadContext* context)
{
    NHTTPRequestInfo* request = NHTTPi_GetReqInfoP(NHTTPi_GetSystemInfoP())->reqQueue->request;
    s32 result;
    if (request->proxyAuthorizationLength == 0) return 0;
    result = NHTTPi_SendData(context, "Proxy-Authorization: Basic ", 27);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, request->proxyAuthorization, request->proxyAuthorizationLength);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, "\r\n", 2);
    if (result != 0) return result;
    return 0;
}

static s32 NHTTPi_SendProxyConnectMethod(NHTTPThreadContext* context)
{
    void* system = NHTTPi_GetSystemInfoP();
    NHTTPRequestInfo* request = NHTTPi_GetReqInfoP(system)->reqQueue->request;
    NHTTPThreadInfo* thread = NHTTPi_GetThreadInfoP(system);
    NHTTPBgnEndInfo* info = NHTTPi_GetBgnEndInfoP(system);
    char* buffer = thread->commBuf;
    char port[12];
    s32 length = NHTTPi_intToStr(port, request->port);
    s32 result;
    result = NHTTPi_SendData(context, "CONNECT ", 8);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, request->url + 8, request->hostEnd - 8);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, ":", 1);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, port, length);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, " HTTP/1.1\r\n", 11);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, "Host: ", 6);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, request->url + 8, request->hostEnd - 8);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, ":", 1);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, port, length);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, "\r\n", 2);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, "Content-Length: 0\r\nPragma: no-cache\r\n", 37);
    if (result != 0) return result;
    result = NHTTPi_SendProxyAuthorization(context);
    if (result != 0) return result;
    NHTTPi_SendData(context, "\r\n", 2);
    if (context->sendLength > 0)
    {
        s32 sent = NHTTPi_SocSend(request, info->socket, buffer, context->sendLength, 0);
        if (sent < 0) return 1;
        if (sent == 0) return 2;
    }
    context->sendLength = 0;
    NHTTPi_memclr(buffer, 0x100);
    return 0;
}

static BOOL NHTTPi_RecvProxyConnectHeader(NHTTPThreadContext* context)
{
    void* system = NHTTPi_GetSystemInfoP();
    NHTTPReqInfo* requests = NHTTPi_GetReqInfoP(system);
    NHTTPThreadInfo* thread = NHTTPi_GetThreadInfoP(system);
    NHTTPBgnEndInfo* info = NHTTPi_GetBgnEndInfoP(system);
    void* mutex = NHTTPi_GetMutexInfoP(system);
    char* buffer = thread->commBuf;
    NHTTPRequestInfo* request = requests->reqQueue->request;
    NHTTPResponseInfo* response = request->response;
    BOOL accepted = FALSE;
    s32 used = 0;
    char header[0x200];
    for (;;)
    {
        s32 received = NHTTPi_SocRecv(mutex, request, info->socket, header + used, 0x200 - used, 0);
        char* cursor;
        s32 index;
        BOOL ended;
        used += received;
        response->httpStatus = NHTTPi_strToInt(header + 9, 3);
        if (NHTTPi_strnicmp(header, "HTTP/", 5) == 0 && header[8] == ' '
            && response->httpStatus == 200) accepted = TRUE;
        cursor = header;
        index = 0;
        ended = FALSE;
        while (index < used)
        {
            if (index > 1 && cursor[-1] == '\r' && *cursor == '\r') ended = TRUE;
            else if (index > 1 && cursor[-1] == '\n' && *cursor == '\n') ended = TRUE;
            else if (index > 3 && cursor[-3] == '\r' && cursor[-2] == '\n'
                && cursor[-1] == '\r' && *cursor == '\n') ended = TRUE;
            ++cursor;
            ++index;
        }
        if (ended) return accepted ? TRUE : FALSE;
        if (received < 0) return FALSE;
        if (used >= 0x200)
        {
            received = NHTTPi_SocRecv(mutex, request, info->socket, buffer, 1, 0);
            if (received < 0) return FALSE;
            if (received != 0) return FALSE;
        }
    }
}

static s32 NHTTPi_SendHeaderList(NHTTPThreadContext* context)
{
    NHTTPRequestInfo* request = NHTTPi_GetReqInfoP(NHTTPi_GetSystemInfoP())->reqQueue->request;
    NHTTPHeader* header = NHTTPi_getHdrFromList(&request->headers);
    while (header != NULL)
    {
        s32 result = NHTTPi_SendData(context, header->name, NHTTPi_strlen(header->name));
        if (result != 0) return result;
        result = NHTTPi_SendData(context, ": ", 2);
        if (result != 0) return result;
        result = NHTTPi_SendData(context, header->value, NHTTPi_strlen(header->value));
        if (result != 0) return result;
        result = NHTTPi_SendData(context, "\r\n", 2);
        if (result != 0) return result;
        NHTTPi_free(header);
        header = NHTTPi_getHdrFromList(&request->headers);
    }
    return 0;
}

static s32 NHTTPi_SendProcPostDataRaw(NHTTPThreadContext* context)
{
    void* system = NHTTPi_GetSystemInfoP();
    void* mutex = NHTTPi_GetMutexInfoP(system);
    NHTTPRequestInfo* request = NHTTPi_GetReqInfoP(system)->reqQueue->request;
    NHTTPThreadInfo* thread = NHTTPi_GetThreadInfoP(system);
    NHTTPBgnEndInfo* info = NHTTPi_GetBgnEndInfoP(system);
    char* buffer = thread->commBuf;
    s32 length = 0;
    char number[12];
    s32 count;
    s32 result;
    if (request->postBuffer == NULL)
    {
        if (!NHTTPi_GetPostContentlength(mutex, request, NULL, &length, 0)) return 3;
    }
    else length = request->postBufferSize;
    count = NHTTPi_intToStr(number, length);
    result = NHTTPi_SendData(context, "Content-Length: ", 16);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, number, count);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, "\r\n", 2);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, "\r\n", 2);
    if (result != 0) return result;
    if (request->postBuffer == NULL)
    {
        result = NHTTPi_SendPostData(mutex, request, buffer, NULL, info->socket, &context->sendLength, 0);
        if (result != 0) return result;
    }
    else
    {
        result = NHTTPi_SendData(context, request->postBuffer, request->postBufferSize);
        if (result != 0) return result;
    }
    return 0;
}

static s32 NHTTPi_SendProcPostDataBinary(NHTTPThreadContext* context)
{
    void* system = NHTTPi_GetSystemInfoP();
    void* mutex = NHTTPi_GetMutexInfoP(system);
    NHTTPRequestInfo* request = NHTTPi_GetReqInfoP(system)->reqQueue->request;
    NHTTPThreadInfo* thread = NHTTPi_GetThreadInfoP(system);
    NHTTPBgnEndInfo* info = NHTTPi_GetBgnEndInfoP(system);
    NHTTPHeader* header;
    char* buffer = thread->commBuf;
    s32 length = 0;
    char number[12];
    s32 count;
    s32 result;
    for (header = request->postData; header != NULL; header = header->prev)
    {
        length += 22;
        length += NHTTPi_strlen(header->name) + 41;
        if (header->isBinary != 0) length += 75;
        length += 2;
        if (header->value == NULL)
        {
            if (!NHTTPi_GetPostContentlength(mutex, request, header->name, &length, 1)) return 3;
        }
        else length += header->length;
        length += 2;
        if (header == request->postData->next) break;
    }
    length += 24;
    count = NHTTPi_intToStr(number, length);
    result = NHTTPi_SendData(context, STR_POST_TYPE_MULTIPART, 44);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, request->multipartBoundary + 2, 18);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, "\r\n", 2);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, "Content-Length: ", 16);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, number, count);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, "\r\n", 2);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, "\r\n", 2);
    if (result != 0) return result;
    for (header = request->postData; header != NULL; header = header->prev)
    {
        result = NHTTPi_SendData(context, request->multipartBoundary, 20);
        if (result != 0) return result;
        result = NHTTPi_SendData(context, "\r\n", 2);
        if (result != 0) return result;
        result = NHTTPi_SendData(context, STR_POST_DISPOS, 38);
        if (result != 0) return result;
        result = NHTTPi_SendData(context, header->name, NHTTPi_strlen(header->name));
        if (result != 0) return result;
        result = NHTTPi_SendData(context, "\"\r\n", 3);
        if (result != 0) return result;
        if (header->isBinary != 0)
        {
            result = NHTTPi_SendData(context, STR_POST_TYPE_BIN, 75);
            if (result != 0) return result;
        }
        result = NHTTPi_SendData(context, "\r\n", 2);
        if (result != 0) return result;
        if (header->value == NULL)
        {
            result = NHTTPi_SendPostData(mutex, request, buffer, header->name, info->socket, &context->sendLength, 1);
            if (result != 0) return result;
        }
        else
        {
            result = NHTTPi_SendData(context, header->value, header->length);
            if (result != 0) return result;
        }
        result = NHTTPi_SendData(context, "\r\n", 2);
        if (result != 0) return result;
        if (header == request->postData->next) break;
    }
    result = NHTTPi_SendData(context, request->multipartBoundary, 20);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, "--\r\n", 4);
    if (result != 0) return result;
    return 0;
}

static s32 NHTTPi_SendProcPostDataAscii(NHTTPThreadContext* context)
{
    void* system = NHTTPi_GetSystemInfoP();
    void* mutex = NHTTPi_GetMutexInfoP(system);
    NHTTPRequestInfo* request = NHTTPi_GetReqInfoP(system)->reqQueue->request;
    NHTTPThreadInfo* thread = NHTTPi_GetThreadInfoP(system);
    NHTTPBgnEndInfo* info = NHTTPi_GetBgnEndInfoP(system);
    NHTTPHeader* header;
    char* buffer = thread->commBuf;
    s32 length = 0;
    char number[12];
    s32 count;
    s32 result;
    for (header = request->postData; header != NULL; header = header->prev)
    {
        length = length + NHTTPi_getUrlEncodedSize(header->name);
        ++length;
        if (header->value == NULL)
        {
            if (!NHTTPi_GetPostContentlength(mutex, request, header->name, &length, 2)) return 3;
        }
        else length += NHTTPi_getUrlEncodedSize(header->value);
        if (header == request->postData->next) break;
        ++length;
    }
    count = NHTTPi_intToStr(number, length);
    result = NHTTPi_SendData(context, STR_POST_TYPE_URLENCODE, 49);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, "Content-Length: ", 16);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, number, count);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, "\r\n", 2);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, "\r\n", 2);
    if (result != 0) return result;
    for (header = request->postData; header != NULL; header = header->prev)
    {
        s32 index;
        char character;
        for (index = 0; (character = header->name[index]) != 0; ++index)
        {
            count = NHTTPi_encodeUrlChar(number, character);
            result = NHTTPi_SendData(context, number, count);
            if (result != 0) return result;
        }
        result = NHTTPi_SendData(context, "=", 1);
        if (result != 0) return result;
        if (header->value == NULL)
        {
            result = NHTTPi_SendPostData(mutex, request, buffer, header->name, info->socket, &context->sendLength, 2);
            if (result != 0) return result;
        }
        else
        {
            for (index = 0; (character = header->value[index]) != 0; ++index)
            {
                count = NHTTPi_encodeUrlChar(number, character);
                result = NHTTPi_SendData(context, number, count);
                if (result != 0) return result;
            }
        }
        if (header == request->postData->next) break;
        result = NHTTPi_SendData(context, "&", 1);
        if (result != 0) return result;
    }
    return 0;
}

static void NHTTPi_ThreadReqEnd(NHTTPThreadContext* context)
{
    void* system = NHTTPi_GetSystemInfoP();
    NHTTPBgnEndInfo* info = NHTTPi_GetBgnEndInfoP(system);
    NHTTPReqInfo* requests = NHTTPi_GetReqInfoP(system);
    void* mutex = NHTTPi_GetMutexInfoP(system);
    NHTTPRequestInfo* request = requests->reqQueue->request;
    NHTTPResponseInfo* response = request->response;
    NHTTPConnectionInfo* connection = NHTTPi_Request2Connection(mutex, request);
    if (request->cancel)
    {
        context->error = 8;
        context->keepAlive = FALSE;
    }
    if (!context->keepAlive && info->socket >= 0)
    {
        if (NHTTPi_SocClose(mutex, request, info->socket) < 0) context->error = 10;
        info->socket = -1;
    }
    if (context->error == 0) response->isSuccess = TRUE;
    else
    {
        response->isSuccess = FALSE;
        NHTTPi_SetError(info, context->error);
        if (response->recvBuf_p == context->discard)
        {
            response->recvBuf_p = NULL;
            response->recvBufLen = 0;
        }
    }
    if (connection != NULL) connection->state = context->error;
    NHTTPi_lockReqList(mutex);
    NHTTPi_free(requests->reqQueue);
    requests->reqQueue = NULL;
    NHTTPi_unlockReqList(mutex);
    NHTTPi_destroyRequestObject(mutex, request);
    if (connection != NULL && response->isSuccess) connection->started = 5;
    NHTTPi_CompleteCallback(mutex, connection);
    if (connection != NULL) NHTTPi_NotifyCompletion(connection);
}

static BOOL NHTTPi_ThreadExecReqQueue(NHTTPThreadContext* context)
{
    void* system = NHTTPi_GetSystemInfoP();
    void* mutex = NHTTPi_GetMutexInfoP(system);
    NHTTPReqQueue* queue;
    NHTTPi_lockReqList(mutex);
    queue = NHTTPi_getReqFromReqQueue(NHTTPi_GetListInfoP(system));
    if (queue != NULL)
    {
        NHTTPReqInfo* requests = NHTTPi_GetReqInfoP(system);
        context->requestId = queue->requestId;
        requests->reqQueue = queue;
    }
    else context->requestId = -1;
    NHTTPi_unlockReqList(mutex);
    if (context->requestId < 0)
    {
        NHTTPi_idleCommThread(NHTTPi_GetThreadInfoP(system));
        return FALSE;
    }
    return TRUE;
}

static BOOL NHTTPi_ThreadHostAddrProc(NHTTPThreadContext* context)
{
    NHTTPRequestInfo* request = NHTTPi_GetReqInfoP(NHTTPi_GetSystemInfoP())->reqQueue->request;
    const char* host = request->host;
    if (request->proxyEnabled) host = request->proxyServer;
    if (NHTTPi_strlen(host) == 0 || NHTTPi_strcmp(host, context->hostname) != 0)
    {
        context->address = NHTTPi_resolveHostname(request, host);
        if (context->address == 0)
        {
            if (request->proxyEnabled) { context->error = 12; return FALSE; }
            context->error = 4;
            return FALSE;
        }
    }
    else context->address = context->previousAddress;
    NHTTPi_memclr(context->hostname, 0x100);
    NHTTPi_memcpy(context->hostname, host, NHTTPi_strlen(host));
    context->port = request->port;
    if (request->proxyEnabled) context->port = request->proxyPort;
    if (context->address != context->previousAddress || context->port != context->previousPort || request->secure == TRUE)
        context->keepAlive = FALSE;
    context->previousAddress = context->address;
    context->previousPort = context->port;
    return TRUE;
}

static BOOL NHTTPi_ThreadConnectProc(NHTTPThreadContext* context)
{
    void* system = NHTTPi_GetSystemInfoP();
    NHTTPBgnEndInfo* info = NHTTPi_GetBgnEndInfoP(system);
    NHTTPReqInfo* requests = NHTTPi_GetReqInfoP(system);
    NHTTPRequestInfo* request = requests->reqQueue->request;
    void* mutex = NHTTPi_GetMutexInfoP(system);
    if (!context->keepAlive)
    {
        if (info->socket >= 0 && NHTTPi_SocClose(mutex, request, info->socket) < 0)
        {
            info->socket = -1;
            context->error = 10;
            return FALSE;
        }
        info->socket = NHTTPi_SocOpen(request);
        if (info->socket < 0)
        {
            context->error = 3;
            return FALSE;
        }
        NHTTPi_lockReqList(mutex);
        requests->reqQueue->socket = info->socket;
        NHTTPi_unlockReqList(mutex);
        if (request->cancel) return FALSE;
        if (NHTTPi_SocConnect(info, mutex, request, info->socket, context->address, context->port) < 0)
        {
            if (request->proxyEnabled) { context->error = 13; return FALSE; }
            else
            {
                if (NHTTPi_GetSSLError(info) != 0) { context->error = 14; return FALSE; }
                context->error = 5; return FALSE;
            }
        }
    }
    else
    {
        NHTTPi_lockReqList(mutex);
        requests->reqQueue->socket = info->socket;
        NHTTPi_unlockReqList(mutex);
    }
    return TRUE;
}

static s32 NHTTPi_ThreadProxyProc(NHTTPThreadContext* context)
{
    void* system = NHTTPi_GetSystemInfoP();
    NHTTPBgnEndInfo* info = NHTTPi_GetBgnEndInfoP(system);
    NHTTPReqInfo* requests = NHTTPi_GetReqInfoP(system);
    void* mutex = NHTTPi_GetMutexInfoP(system);
    NHTTPRequestInfo* request = requests->reqQueue->request;
    context->error = 10;
    context->sendLength = 0;
    if (request->secure && request->proxyEnabled)
    {
        s32 result = NHTTPi_SendProxyConnectMethod(context);
        s32 sslResult;
        if (result != 0) return result;
        if (!NHTTPi_RecvProxyConnectHeader(context)) return 1;
        sslResult = NHTTPi_SocSSLConnect(info, mutex, request, info->socket);
        if (sslResult != 0)
        {
            if (sslResult == -1004)
            {
                if (NHTTPi_GetSSLError(info) != 0) context->error = 16;
                return 1;
            }
            if (sslResult == -1005)
            {
                if (NHTTPi_GetSSLError(info) != 0) context->error = 17;
                return 1;
            }
            if (NHTTPi_GetSSLError(info) != 0) context->error = 14;
            return 1;
        }
    }
    return 0;
}

static inline s32 NHTTPi_SendAuthorization(NHTTPThreadContext* context)
{
    NHTTPRequestInfo* request = NHTTPi_GetReqInfoP(NHTTPi_GetSystemInfoP())->reqQueue->request;
    s32 result;
    if (request->authorizationLength == 0) return 0;
    result = NHTTPi_SendData(context, "Authorization: Basic ", 21);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, request->authorization, request->authorizationLength);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, "\r\n", 2);
    if (result != 0) return result;
    return 0;
}

static s32 NHTTPi_ThreadSendProc(NHTTPThreadContext* context)
{
    s32 start;
    void* system = NHTTPi_GetSystemInfoP();
    NHTTPRequestInfo* request = NHTTPi_GetReqInfoP(system)->reqQueue->request;
    void* mutex = NHTTPi_GetMutexInfoP(system);
    NHTTPBgnEndInfo* info = NHTTPi_GetBgnEndInfoP(system);
    NHTTPConnectionInfo* connection = NHTTPi_Request2Connection(mutex, request);
    char* buffer = NHTTPi_GetThreadInfoP(system)->commBuf;
    s32 urlLength = NHTTPi_strlen(request->url);
    s32 result = 0;
    context->error = 10;
    if (connection != NULL) connection->started = 2;
    context->sendLength = 0;
    switch (request->method)
    {
    case 0: result = NHTTPi_SendData(context, "GET ", 4); break;
    case 1: result = NHTTPi_SendData(context, "POST ", 5); break;
    case 2: result = NHTTPi_SendData(context, "HEAD ", 5); break;
    }
    if (result != 0) return result;
    if (request->proxyEnabled && !request->secure)
    {
        result = NHTTPi_SendData(context, request->url, urlLength);
        if (result != 0) return result;
    }
    else if (urlLength > request->pathStart)
    {
        result = NHTTPi_SendData(context, request->url + request->pathStart, urlLength - request->pathStart);
        if (result != 0) return result;
    }
    else
    {
        result = NHTTPi_SendData(context, "/", 1);
        if (result != 0) return result;
    }
    result = NHTTPi_SendData(context, " HTTP/1.1\r\n", 11);
    if (result != 0) return result;
    start = (request->secure != 0) + 7;
    result = NHTTPi_SendData(context, "Host: ", 6);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, request->url + start, request->hostEnd - start);
    if (result != 0) return result;
    result = NHTTPi_SendData(context, "\r\n", 2);
    if (result != 0) return result;
    if (request->proxyEnabled && !request->secure)
    {
        result = NHTTPi_SendProxyAuthorization(context);
        if (result != 0) return result;
    }
    result = NHTTPi_SendAuthorization(context);
    if (result != 0) return result;
    result = NHTTPi_SendHeaderList(context);
    if (result != 0) return result;
    if (request->method == 1)
    {
        if (request->isRawData) result = NHTTPi_SendProcPostDataRaw(context);
        else
        {
            BOOL binary;
            if (request->encodingType == 0)
            {
                NHTTPHeader* header;
                binary = FALSE;
                for (header = request->postData; header != NULL; header = header->prev)
                {
                    if (header->isBinary != 0) { binary = TRUE; break; }
                    if (header == request->postData->next) break;
                }
            }
            else binary = request->encodingType == 2;
            if (!binary) result = NHTTPi_SendProcPostDataAscii(context);
            else result = NHTTPi_SendProcPostDataBinary(context);
        }
        if (result != 0)
        {
            if (result == 3) context->error = 3;
            return result;
        }
    }
    else
    {
        result = NHTTPi_SendData(context, "\r\n", 2);
        if (result != 0) return result;
    }
    result = 0;
    if (context->sendLength > 0)
    {
        s32 sent = NHTTPi_SocSend(request, info->socket, buffer, context->sendLength, 0);
        context->sendLength = 0;
        NHTTPi_memclr(buffer, 0x100);
        if (sent < 0) result = 1;
        if (sent == 0) result = 2;
    }
    context->sendLength = 0;
    NHTTPi_memclr(buffer, 0x100);
    return result;
}

static BOOL NHTTPi_ThreadRecvHeaderProc(NHTTPThreadContext* context)
{
    u32 index;
    void* system = NHTTPi_GetSystemInfoP();
    NHTTPRequestInfo* request = NHTTPi_GetReqInfoP(system)->reqQueue->request;
    NHTTPResponseInfo* response = request->response;
    void* mutex = NHTTPi_GetMutexInfoP(system);
    NHTTPConnectionInfo* connection = NHTTPi_Request2Connection(mutex, request);
    NHTTPBgnEndInfo* info = NHTTPi_GetBgnEndInfoP(system);
    char recent[4] = {0};
    NHTTPi_HDRBUFLIST* block;
    if (connection != NULL) connection->started = 3;
    response->headerLen = 0;
    NHTTPi_memclr(context->statusLine, 14);
    block = response->hdrBufBlock_p;
    context->recvLength = 0;
    for (;;)
    {
        s32 received;
        if (request->cancel) return FALSE;
        if (context->recvLength < 0x400)
        {
            received = NHTTPi_SocRecv(mutex, request, info->socket, response->hdrBufFirst + context->recvLength, 1, 0);
            recent[context->recvLength & 3] = response->hdrBufFirst[context->recvLength];
        }
        else
        {
            char* destination;
            index = context->recvLength & 0x1ff;
            if (index == 0)
            {
                if (block != NULL)
                {
                    NHTTPi_HDRBUFLIST* next = NHTTPi_alloc(sizeof(NHTTPi_HDRBUFLIST), 4);
                    block->next_p = next;
                    block = next;
                }
                else
                {
                    block = NHTTPi_alloc(sizeof(NHTTPi_HDRBUFLIST), 4);
                    response->hdrBufBlock_p = block;
                }
                if (block == NULL) { context->error = 1; return FALSE; }
                block->next_p = NULL;
            }
            destination = (char*)block->block + index;
            received = NHTTPi_SocRecv(mutex, request, info->socket, destination, 1, 0);
            recent[context->recvLength & 3] = *destination;
        }
        if (received <= 0) { context->error = 10; return FALSE; }
        context->recvLength += received;
        if (NHTTPi_CheckHeaderEnd(recent, context->recvLength)) break;
    }
    response->headerLen = context->recvLength;
    if (response->headerLen == 0) { context->error = 7; return FALSE; }
    return TRUE;
}

static BOOL NHTTPi_ThreadParseHeaderProc(NHTTPThreadContext* context)
{
    void* system = NHTTPi_GetSystemInfoP();
    NHTTPRequestInfo* request = NHTTPi_GetReqInfoP(system)->reqQueue->request;
    NHTTPResponseInfo* response = request->response;
    NHTTPThreadInfo* thread = NHTTPi_GetThreadInfoP(system);
    s32 lineLength;
    s32 offset;
    char* buffer = thread->commBuf;
    s32 length;
    if (!NHTTPi_loadFromHdrRecvBuf(response, context->statusLine, 0, 14)) { context->error = 7; return FALSE; }
    if (NHTTPi_strnicmp(context->statusLine, "HTTP/", 5) != 0) { context->error = 7; return FALSE; }
    if (context->statusLine[8] != ' ') { context->error = 7; return FALSE; }
    response->httpStatus = NHTTPi_strToInt(context->statusLine + 9, 3);
    if (response->httpStatus < 0) { context->error = 7; return FALSE; }
    if (NHTTPi_findNextLineHdrRecvBuf(response, 12, response->headerLen, &lineLength, 0) < 0) { context->error = 7; return FALSE; }
    context->contentLength = NHTTPi_getHeaderValue(response, "Content-Length", &offset);
    if (context->contentLength == 0) { context->error = 0; return FALSE; }
    if (context->contentLength > 0x100) { context->error = 7; return FALSE; }
    if (context->contentLength > 0)
    {
        if (!NHTTPi_loadFromHdrRecvBuf(response, buffer, offset, context->contentLength)) { context->error = 7; return FALSE; }
        context->contentLength = NHTTPi_strToInt(buffer, context->contentLength);
        if (context->contentLength < 0) { context->error = 7; return FALSE; }
        response->contentLength = context->contentLength;
    }
    else response->contentLength = -1;
    if (request->secure) context->keepAlive = FALSE;
    else
    {
        length = NHTTPi_getHeaderValue(response, "Connection", &offset);
        if (length == 0)
        {
            context->error = 7;
            context->keepAlive = FALSE;
            return FALSE;
        }
        if (length > 0x100) context->keepAlive = FALSE;
        else if (length > 0)
        {
            struct TokenMatch {
                BOOL matched;
            };
            struct TokenMatch match = {FALSE};
            if (NHTTPi_compareTokenN_HdrRecvBuf(response, offset, offset + length, "Keep-Alive", 0) == 0)
            {
                match.matched = TRUE;
                context->keepAlive = match.matched;
            }
            else context->keepAlive = match.matched;
        }
        else context->keepAlive = FALSE;
    }
    context->chunked = NHTTPi_getHeaderValue(response, "Transfer-Encoding", &offset);
    if (context->chunked == 0) { context->error = 7; return FALSE; }
    if (context->chunked > 0x100) context->chunked = FALSE;
    else
    {
        BOOL chunked;
        if (context->chunked > 0)
            chunked = NHTTPi_compareTokenN_HdrRecvBuf(response, offset, offset + context->chunked, "chunked", ';') == 0;
        else chunked = FALSE;
        context->chunked = chunked;
    }
    context->error = 0;
    response->isHeaderParse = TRUE;
    return TRUE;
}

static inline s32 NHTTPi_RecvChunkLine(void* mutex, NHTTPRequestInfo* request, s32 socket)
{
    u32 index;
    s32 total;
    char recent[2];
    total = 0;
    recent[0] = total;
    recent[1] = total;
    index = 0;
    while (recent[index & 1] != '\r' || recent[(index - 1) & 1] != '\n')
    {
        s32 received = NHTTPi_SocRecv(mutex, request, socket, &recent[index & 1], 1, 0);
        if (received <= 0) return received;
        total += received;
        ++index;
    }
    return total;
}

static BOOL NHTTPi_ThreadRecvBodyProc(NHTTPThreadContext* context)
{
    char* recentChars;
    s32 remaining;
    void* system = NHTTPi_GetSystemInfoP();
    NHTTPRequestInfo* request = NHTTPi_GetReqInfoP(system)->reqQueue->request;
    NHTTPResponseInfo* response = request->response;
    NHTTPBgnEndInfo* info = NHTTPi_GetBgnEndInfoP(system);
    void* mutex = NHTTPi_GetMutexInfoP(system);
    NHTTPConnectionInfo* connection = NHTTPi_Request2Connection(mutex, request);
    char* buffer = NHTTPi_GetThreadInfoP(system)->commBuf;
    s32 status;
    if (request->method == 2 || (status = response->httpStatus) == 204 || status == 304 || (status >= 100 && status < 200)) return TRUE;
    NHTTPi_SetVirtualContentLength(connection, 0);
    if (connection != NULL) connection->started = 4;
    if (context->contentLength >= 0)
    {
        NHTTPi_SetVirtualContentLength(connection, context->contentLength);
        while (context->contentLength > 0)
        {
            s32 received;
            if (context->error != 6 && !NHTTPi_BufFull(mutex, response))
            {
                context->error = 6;
                response->recvBuf_p = context->discard;
                response->recvBufLen = 0x200;
            }
            if (context->error == 6)
                received = NHTTPi_RecvBufN(mutex, request, info->socket, 0, context->contentLength, 0);
            else received = NHTTPi_RecvBufN(mutex, request, info->socket, response->bodyLen, context->contentLength, 0);
            if (received < 0) return FALSE;
            if (received == 0) break;
            if (context->error != 6)
            {
                response->bodyLen += received;
                response->totalBodyLen += received;
            }
            context->contentLength -= received;
        }
        if (context->error != 6)
        {
            if (context->contentLength != 0)
                context->error = NHTTPi_isRecvBufFull(response, response->bodyLen) ? 6 : 10;
            else context->error = 0;
        }
    }
    else
    {
        context->error = 10;
        if (context->chunked)
        {
            remaining = -1;
            for (;;)
            {
                char recent[2];
                s32 received;
                recentChars = recent;
                recentChars[0] = 0;
                recentChars[1] = 0;
                context->recvLength = 0;
                while (context->recvLength < 0x100)
                {
                    u32 length;
                    char character;
                    received = NHTTPi_SocRecv(mutex, request, info->socket, buffer + context->recvLength, 1, 0);
                    if (received < 0) return FALSE;
                    length = context->recvLength;
                    recentChars[length & 1] = buffer[length];
                    character = recentChars[length & 1];
                    if (character == ';' || (character == '\n' && recentChars[(length - 1) & 1] == '\r'))
                    {
                        if (character == '\n') --length;
                        else
                        {
                            if (NHTTPi_RecvChunkLine(mutex, request, info->socket) <= 0) return FALSE;
                        }
                        if (length == 0) return FALSE;
                        length = NHTTPi_strToHex(buffer, length);
                        remaining = length;
                        if ((s32)length < 0) return FALSE;
                        break;
                    }
                    ++context->recvLength;
                }
                if (context->recvLength == 0x100) { context->error = 7; return FALSE; }
                if (remaining > 0)
                {
                    NHTTPi_SetVirtualContentLength(connection, remaining);
                    while (remaining > 0)
                    {
                        if (context->error != 6 && !NHTTPi_BufFull(mutex, response))
                        {
                            context->error = 6;
                            response->recvBuf_p = context->discard;
                            response->recvBufLen = 0x200;
                        }
                        if (context->error == 6)
                            received = NHTTPi_RecvBufN(mutex, request, info->socket, 0, remaining, 0);
                        else received = NHTTPi_RecvBufN(mutex, request, info->socket, response->bodyLen, remaining, 0);
                        if (received <= 0) return FALSE;
                        remaining -= received;
                        response->bodyLen += received;
                        response->totalBodyLen += received;
                        if (remaining == 0 && NHTTPi_SocRecv(mutex, request, info->socket, buffer, 2, 0) <= 0) return FALSE;
                    }
                }
                else
                {
                    NHTTPi_RecvChunkLine(mutex, request, info->socket);
                    context->error = 0;
                    break;
                }
            }
        }
        else
        {
            for (;;)
            {
                s32 received;
                if (!NHTTPi_BufFull(mutex, response))
                {
                    context->error = 6;
                    response->recvBuf_p = context->discard;
                    response->recvBufLen = 0x200;
                }
                if (context->error == 6) received = NHTTPi_RecvBuf(mutex, request, info->socket, 0, 0);
                else received = NHTTPi_RecvBuf(mutex, request, info->socket, response->bodyLen, 0);
                if (received < 0) return FALSE;
                if (received == 0)
                {
                    if (context->error != 6) context->error = 0;
                    break;
                }
                response->bodyLen += received;
                response->totalBodyLen += received;
            }
        }
    }
    connection = NHTTPi_Response2Connection(mutex, response);
    if (context->error == 0 && connection != NULL) NHTTPi_ReceivedCallback(mutex, connection);
    return TRUE;
}

void NHTTPi_CommThreadProcMain(void* argument)
{
    void* system = NHTTPi_GetSystemInfoP();
    NHTTPBgnEndInfo* info = NHTTPi_GetBgnEndInfoP(system);
    NHTTPReqInfo* requests = NHTTPi_GetReqInfoP(system);
    NHTTPThreadContext context;
    context.requestId = -1;
    NHTTPi_memclr(context.hostname, 0x100);
    NHTTPi_memclr(context.discard, 0x200);
    context.address = -1;
    context.previousAddress = -1;
    context.sendLength = 0;
    context.keepAlive = FALSE;
    context.chunked = FALSE;
    context.retry = FALSE;
    context.contentLength = 0;
    context.error = 0;
    while (!info->stopping)
    {
        s32 result;
        if (!context.retry)
        {
            if (!NHTTPi_ThreadExecReqQueue(&context)) continue;
            if (requests->reqQueue->request->cancel) { NHTTPi_ThreadReqEnd(&context); continue; }
            if (!NHTTPi_ThreadHostAddrProc(&context)) { NHTTPi_ThreadReqEnd(&context); continue; }
        }
        if (context.retry == TRUE) context.retry = FALSE;
        if (!NHTTPi_ThreadConnectProc(&context)) { NHTTPi_ThreadReqEnd(&context); continue; }
        result = NHTTPi_ThreadProxyProc(&context);
        switch (result)
        {
        case 0: break;
        case 2: context.retry = TRUE; continue;
        case 1: NHTTPi_ThreadReqEnd(&context); continue;
        }
        result = NHTTPi_ThreadSendProc(&context);
        switch (result)
        {
        case 0: break;
        case 2: context.retry = TRUE; continue;
        case 1:
        case 3: NHTTPi_ThreadReqEnd(&context); continue;
        }
        if (requests->reqQueue->request->cancel) { NHTTPi_ThreadReqEnd(&context); continue; }
        if (!NHTTPi_ThreadRecvHeaderProc(&context)) { NHTTPi_ThreadReqEnd(&context); continue; }
        if (!NHTTPi_ThreadParseHeaderProc(&context)) { NHTTPi_ThreadReqEnd(&context); continue; }
        NHTTPi_ThreadRecvBodyProc(&context);
        NHTTPi_ThreadReqEnd(&context);
    }
}
