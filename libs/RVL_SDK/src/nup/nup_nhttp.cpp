#include <revolution/os.h>
#include <revolution/ncd.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

namespace nup {
void* __nupMalloc(unsigned long size);
void __nupFree(void* block);
}

enum NHTTPReqMethod { NHTTP_GET, NHTTP_POST };
typedef void (*ProgressCallback)(void*, unsigned long);
typedef long (*FlushCallback)(u8*, unsigned long, unsigned long, void*);
struct HttpState {
    int error;
    unsigned long limit;
    unsigned long received;
    ProgressCallback progress;
    void* progressContext;
    FlushCallback flush;
    void* flushContext;
    void* response;
    int done;
    int result;
    OSTime lastActivity;
};
struct HttpString {
    u8* buffer;
    unsigned long capacity;
    unsigned long length;
    unsigned long growth;
    unsigned long maximumGrowth;
};
extern "C" {
void* NHTTPCreateRequestEx(char*, NHTTPReqMethod, void*, u32, void (*)(int, void*, HttpState*), HttpState*, u8* (*)(u8**, unsigned long*, unsigned long, void*, void*, HttpState*), void (*)(void*));
int NHTTPGetError();
int NHTTPSetSocketBufferSize(void*, u32);
int NHTTPAddHeaderField(void*, const char*, const char*);
int NHTTPSetClientCertDefault(void*);
int NHTTPSetRootCADefault(void*);
int NHTTPSetVerifyOption(void*, u32);
int NHTTPSetProxyDefault(void*);
int NHTTPAddPostDataRaw(void*, u8*, unsigned long);
int NHTTPSendRequestAsync(void*);
void NHTTPDeleteRequest(void*);
int NHTTPGetProgress(unsigned long*, unsigned long*);
int NHTTPGetBodyAll(void*, u8**);
int NHTTPGetHeaderAll(void*, char**);
void NHTTPCancelRequestAsync(int);
void NHTTPDestroyResponse(void*);

static u8* __nupNhttpBufFull(u8** buffer, unsigned long* length, unsigned long requested, void*, void*, HttpState* state) {
    u8* next = NULL;
    if (state->progress != NULL && *length != 0) {
        state->progress(state->progressContext, *length);
    }
    if (state->received + *length < state->received) {
        if (state->error == 0) state->error = -5012;
    }
    state->received += *length;
    if (state->error == 0) {
        if (state->limit != 0 && state->received > state->limit) {
            state->error = -5012;
            goto done;
        } else {
            if (*buffer != NULL && state->flush != NULL) {
                state->error = state->flush(*buffer, *length, requested, state->flushContext);
                if (state->error != 0) goto done;
            }
            next = *buffer;
            if (next == NULL) {
                if (requested == 0 || requested >= 0x8000) requested = 0x8000;
                next = (u8*)nup::__nupMalloc(requested);
                if (next == NULL) {
                    state->error = -5000;
                    goto done;
                }
                *length = requested;
            }
            if (*length != 0) state->lastActivity = OSGetTime();
        }
    }
done:
    if (state->error != 0) {
        *length = 0;
        next = NULL;
    }
    return next;
}
static void __nupNhttpBufFree(void* block) {
    if (block != NULL) nup::__nupFree(block);
}
static void __nupNhttpReqDone(int result, void* response, HttpState* state) {
    if (state != NULL) {
        state->response = response;
        state->done = 1;
        state->result = result;
    }
}
}

static int __nupNhttpOp(char* url, NHTTPReqMethod method, char* headers, u8* body, unsigned long bodyLength, unsigned long limit, ProgressCallback progress, void* progressContext, FlushCallback flush, void* flushContext) {
    int result = 0;
    int status;
    u8* responseBody = NULL;
    char* responseHeaders = NULL;
    int length;
    unsigned long expected, transferred;
    HttpState state;
    state.error = 0;
    state.limit = limit;
    state.received = 0;
    state.progress = progress;
    state.progressContext = progressContext;
    state.flush = flush;
    state.flushContext = flushContext;
    state.response = NULL;
    state.done = 0;
    state.result = 0;
    state.lastActivity = 0;
    int requestId;
    char* headerCopy = NULL;
    void* request = NHTTPCreateRequestEx(url, method, NULL, 0, __nupNhttpReqDone, &state, __nupNhttpBufFull, __nupNhttpBufFree);
    if (request == NULL) { result = -7000 - NHTTPGetError(); goto cleanup; }
    if (NHTTPSetSocketBufferSize(request, 0x8000) != 0) { result = -7000 - NHTTPGetError(); goto cleanup; }
    if (headers != NULL) {
        unsigned long size = strlen(headers) + 1;
        headerCopy = (char*)nup::__nupMalloc(size);
        if (headerCopy == NULL) { result = -5000; goto cleanup; }
        memcpy(headerCopy, headers, size);
        char* field = headerCopy;
        char* colon;
        char* end;
        while (*field != 0 && (colon = strchr(field, ':')) != NULL && (end = strstr(colon, "\r\n")) != NULL) {
            *colon = 0;
            *end = 0;
            while (*field && isspace(*field)) field++;
            char* value = colon + 1;
            while (*value && isspace(*value)) value++;
            if (NHTTPAddHeaderField(request, field, value) != 0) { result = -7000 - NHTTPGetError(); goto cleanup; }
            field = end + 2;
        }
    }
    if (NHTTPAddHeaderField(request, "Accept", "text/html, image/gif, image/jpeg, */*") != 0) { result = -7000 - NHTTPGetError(); goto cleanup; }
    if (NHTTPAddHeaderField(request, "Content-type", "text/xml; charset=utf-8") != 0) { result = -7000 - NHTTPGetError(); goto cleanup; }
    if (NHTTPAddHeaderField(request, "Connection", "Keep-Alive") != 0) { result = -7000 - NHTTPGetError(); goto cleanup; }
    if (NHTTPSetClientCertDefault(request) != 0) { result = -7000 - NHTTPGetError(); goto cleanup; }
    if (NHTTPSetRootCADefault(request) != 0) { result = -7000 - NHTTPGetError(); goto cleanup; }
    if (NHTTPSetVerifyOption(request, 11) != 0) { result = -7000 - NHTTPGetError(); goto cleanup; }
    NHTTPSetProxyDefault(request);
    if (method == NHTTP_POST && body != NULL && bodyLength != 0 && NHTTPAddPostDataRaw(request, body, bodyLength) != 0) { result = -7000 - NHTTPGetError(); goto cleanup; }
    requestId = NHTTPSendRequestAsync(request);
    if (requestId < 0) {
        result = -7000 - NHTTPGetError();
        NHTTPDeleteRequest(request);
        goto cleanup;
    }
    state.lastActivity = OSGetTime();
    while (NHTTPGetProgress(&expected, &transferred) == 0 || state.done == 0) {
        if (OSGetTime() - state.lastActivity >= OSMillisecondsToTicks(90000LL)) {
            if (requestId >= 0) {
                NHTTPCancelRequestAsync(requestId);
                NCDSleep(OSMillisecondsToTicks(100));
            }
            result = -5009;
            goto cleanup;
        }
        NCDSleep(OSMillisecondsToTicks(100));
    }
    if (state.result != 0) { result = -7000 - state.result; goto cleanup; }
    if (state.response != NULL) {
        length = NHTTPGetBodyAll(state.response, &responseBody);
        if (length < 0) { result = -5007; goto cleanup; }
        __nupNhttpBufFull(&responseBody, (unsigned long*)&length, 0, NULL, NULL, &state);
    }
    if (state.error != 0) { result = state.error; goto cleanup; }
    if (state.response == NULL) goto cleanup;
    length = NHTTPGetHeaderAll(state.response, &responseHeaders);
    if (length < 0) { result = -5007; goto cleanup; }
    {
        char* protocol = strstr(responseHeaders, "HTTP/");
        if (protocol == NULL || sscanf(protocol, "HTTP/%*d.%*d %d", &status) != 1) {
            result = -5007;
            goto cleanup;
        }
        if (status != 200 && status != 202) result = -5000 - status;
    }
cleanup:
    if (state.response != NULL || result == -5009) NHTTPDestroyResponse(state.response);
    if (headerCopy != NULL) nup::__nupFree(headerCopy);
    return result;
}

extern "C" {
static long __nupHttpStringFlush(u8* data, unsigned long length, unsigned long requested, void* context) {
    HttpString* text = (HttpString*)context;
    unsigned long dataLength = length;
    unsigned long total = length + text->length;
    long result = 0;
    if (total > text->capacity) {
        if (requested < total) {
            requested = text->growth + total;
            text->growth <<= 1;
            if (text->growth >= text->maximumGrowth) {
                text->growth = text->maximumGrowth;
            }
        }
        u8* next = (u8*)nup::__nupMalloc(requested);
        if (next == NULL) { result = -5000; goto done; }
        if (text->buffer != NULL) {
            memcpy(next, text->buffer, text->length);
            nup::__nupFree(text->buffer);
        }
        text->buffer = next;
    }
    memcpy(text->buffer + text->length, data, dataLength);
    text->length += dataLength;
done:
    return result;
}
}
static int __nupNhttpOpString(u8** output, unsigned long* outputLength, char* url, NHTTPReqMethod method, char* headers, u8* body, unsigned long bodyLength, unsigned long limit, ProgressCallback progress, void* context) NO_INLINE;
static int __nupNhttpOpString(u8** output, unsigned long* outputLength, char* url, NHTTPReqMethod method, char* headers, u8* body, unsigned long bodyLength, unsigned long limit, ProgressCallback progress, void* context) {
    HttpString text;
    text.buffer = *output;
    text.capacity = *outputLength;
    text.growth = 0x400;
    text.maximumGrowth = 0x10000;
    text.length = 0;
    int result = __nupNhttpOp(url, method, headers, body, bodyLength, limit, progress, context, __nupHttpStringFlush, &text);
    if (result == 0) {
        *output = text.buffer;
        *outputLength = text.length;
    }
    if (result != 0) {
        if (text.buffer != NULL) nup::__nupFree(text.buffer);
        *output = NULL;
        *outputLength = 0;
    }
    return result;
}
int __nupHttpGetFull(char* url, u8** output, unsigned long* length, unsigned long limit, ProgressCallback progress, void* context) {
    return __nupNhttpOpString(output, length, url, NHTTP_GET, NULL, NULL, 0, limit, progress, context);
}
int __nupHttpPostFull(char* url, char* headers, char* body, u8** output, unsigned long* length, unsigned long limit, ProgressCallback progress, void* context) {
    int result = __nupNhttpOpString(output, length, url, NHTTP_POST, headers, (u8*)body, strlen(body), limit, progress, context);
    if (result != 0) {
        if (*output != NULL) nup::__nupFree(*output);
        *output = NULL;
        *length = 0;
    }
    return result;
}
int __nupHttpGetIncr(char* url, unsigned long limit, ProgressCallback progress, void* progressContext, FlushCallback flush, void* context) {
    return __nupNhttpOp(url, NHTTP_GET, NULL, NULL, 0, limit, progress, progressContext, flush, context);
}
